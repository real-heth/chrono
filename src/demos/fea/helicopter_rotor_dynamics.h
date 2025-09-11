// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2024 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Chrono Development Team
// =============================================================================
//
// Helicopter rotor dynamics system header file
//
// This header provides classes and utilities for helicopter rotor dynamics
// simulation including:
// - Multi-blade flexible rotor systems
// - Mass imbalance effects modeling
// - Pitch control rod mechanisms
// - Trailing edge tab aerodynamic effects
// - Multi-point fuselage vibration analysis
//
// =============================================================================

#ifndef HELICOPTER_ROTOR_DYNAMICS_H
#define HELICOPTER_ROTOR_DYNAMICS_H

#include "chrono/physics/ChSystem.h"
#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChLinkMotorRotationSpeed.h"
#include "chrono/fea/ChElementBeamEuler.h"
#include "chrono/fea/ChNodeFEAxyzrot.h"
#include "chrono/fea/ChMesh.h"

#include <vector>
#include <memory>
#include <string>
#include <complex>

namespace chrono {
namespace helicopter {

// =============================================================================
// Aerodynamic Coefficients and Constants
// =============================================================================

struct AerodynamicConstants {
    static constexpr double AIR_DENSITY = 1.225;           // kg/m³ at sea level
    static constexpr double LIFT_CURVE_SLOPE = 5.73;       // per radian
    static constexpr double DRAG_COEFFICIENT_0 = 0.01;     // Zero-lift drag coefficient
    static constexpr double MOMENT_COEFFICIENT_0 = 0.0;    // Zero-lift moment coefficient
    static constexpr double TAB_EFFECTIVENESS = 0.3;       // Tab effectiveness factor
};

// =============================================================================
// Blade Airfoil Properties
// =============================================================================

struct AirfoilProperties {
    double lift_curve_slope = AerodynamicConstants::LIFT_CURVE_SLOPE;
    double zero_lift_angle = 0.0;          // radians
    double drag_coefficient_0 = AerodynamicConstants::DRAG_COEFFICIENT_0;
    double moment_coefficient_0 = AerodynamicConstants::MOMENT_COEFFICIENT_0;
    double max_lift_coefficient = 1.4;
    double stall_angle = 0.26;              // radians (~15 degrees)
};

// =============================================================================
// Advanced Aerodynamic Force Model
// =============================================================================

class AdvancedAerodynamicModel {
public:
    struct SectionProperties {
        double chord;
        double twist;                       // Built-in twist angle [rad]
        double airfoil_thickness_ratio;
        AirfoilProperties airfoil;
    };

    struct FlightConditions {
        double forward_speed = 0.0;         // m/s
        double climb_rate = 0.0;            // m/s
        double air_density = AerodynamicConstants::AIR_DENSITY;
        ChVector3d wind_velocity = VNULL;
    };

private:
    double rotor_radius_;
    int num_blades_;
    double rotor_solidity_;
    FlightConditions flight_conditions_;
    std::vector<SectionProperties> section_properties_;

public:
    AdvancedAerodynamicModel(double rotor_radius, int num_blades);
    
    void SetFlightConditions(const FlightConditions& conditions);
    void SetSectionProperties(const std::vector<SectionProperties>& properties);
    
    // Calculate aerodynamic forces and moments
    ChVector3d CalculateSectionForces(
        const std::shared_ptr<fea::ChNodeFEAxyzrot>& node,
        double radius_ratio,
        double collective_pitch,
        double cyclic_pitch,
        double rotor_rpm,
        double time
    );
    
    ChVector3d CalculateSectionMoments(
        const std::shared_ptr<fea::ChNodeFEAxyzrot>& node,
        double radius_ratio,
        double collective_pitch,
        double tab_deflection,
        double rotor_rpm
    );
    
    // Unsteady aerodynamic effects
    ChVector3d CalculateUnsteadyEffects(
        const std::shared_ptr<fea::ChNodeFEAxyzrot>& node,
        double radius_ratio,
        double time,
        double rotor_rpm
    );
    
    // Dynamic stall model
    double CalculateDynamicStallEffect(double angle_of_attack, double pitch_rate);
};

// =============================================================================
// Mass Imbalance Model
// =============================================================================

class MassImbalanceModel {
public:
    struct ImbalanceProperties {
        double mass_magnitude = 0.0;        // kg
        double radial_position = 0.0;       // m from blade root
        double circumferential_angle = 0.0; // rad relative to blade chord line
    };

private:
    std::vector<ImbalanceProperties> imbalances_;

public:
    void AddMassImbalance(const ImbalanceProperties& imbalance);
    void ClearMassImbalances();
    
    // Calculate forces and moments due to mass imbalance
    ChVector3d CalculateImbalanceForces(
        const std::shared_ptr<fea::ChNodeFEAxyzrot>& node,
        double rotor_rpm,
        double time
    );
    
    ChVector3d CalculateImbalanceMoments(
        const std::shared_ptr<fea::ChNodeFEAxyzrot>& node,
        double rotor_rpm,
        double time
    );
};

// =============================================================================
// Pitch Control System
// =============================================================================

class PitchControlSystem {
public:
    struct ControlInputs {
        double collective_pitch = 0.0;      // rad
        double longitudinal_cyclic = 0.0;   // rad
        double lateral_cyclic = 0.0;        // rad
        double tab_deflection = 0.0;        // rad
    };

    struct ControlProperties {
        double pitch_rod_stiffness = 1e6;   // N/m
        double pitch_rod_damping = 1e3;     // N*s/m
        double actuator_bandwidth = 50.0;   // rad/s
        double control_lag = 0.01;          // seconds
    };

private:
    ControlInputs target_inputs_;
    ControlInputs current_inputs_;
    ControlProperties properties_;
    double last_update_time_ = 0.0;

public:
    PitchControlSystem(const ControlProperties& props) : properties_(props) {}
    
    void SetControlInputs(const ControlInputs& inputs);
    void UpdateControls(double time);
    
    // Get effective pitch angle for a blade at given azimuth
    double GetEffectivePitch(double azimuth_angle, double time) const;
    double GetEffectiveTabDeflection(double azimuth_angle) const;
    
    // Control system dynamics
    ChVector3d CalculateControlForces(
        const std::shared_ptr<fea::ChNodeFEAxyzrot>& node,
        double target_pitch,
        double current_pitch
    );
};

// =============================================================================
// Vibration Analysis System
// =============================================================================

class VibrationAnalysisSystem {
public:
    struct MeasurementPoint {
        std::string name;
        ChVector3d local_position;         // Position in body frame
        ChVector3d acceleration;
        ChVector3d velocity;
        ChVector3d displacement;
        
        // Time history storage
        std::vector<double> time_history;
        std::vector<ChVector3d> acceleration_history;
        std::vector<ChVector3d> velocity_history;
        std::vector<ChVector3d> displacement_history;
    };

    struct FrequencyData {
        std::vector<double> frequencies;    // Hz
        std::vector<double> magnitude_x;    // Magnitude spectrum X
        std::vector<double> magnitude_y;    // Magnitude spectrum Y
        std::vector<double> magnitude_z;    // Magnitude spectrum Z
        std::vector<double> phase_x;        // Phase spectrum X
        std::vector<double> phase_y;        // Phase spectrum Y
        std::vector<double> phase_z;        // Phase spectrum Z
    };

private:
    std::shared_ptr<ChBody> reference_body_;
    std::vector<MeasurementPoint> measurement_points_;
    double sampling_frequency_ = 1000.0;   // Hz
    double last_sample_time_ = 0.0;
    int fft_size_ = 1024;

public:
    VibrationAnalysisSystem(std::shared_ptr<ChBody> reference_body, double sampling_freq = 1000.0);
    
    void AddMeasurementPoint(const std::string& name, const ChVector3d& local_position);
    void UpdateMeasurements(double time);
    void ClearHistory();
    
    // Analysis functions
    FrequencyData PerformFFTAnalysis(const std::string& point_name) const;
    void CalculateRMSValues();
    void CalculateVibrationalPowerSpectralDensity();
    
    // Export functions
    void ExportTimeHistory(const std::string& filename) const;
    void ExportFrequencySpectrum(const std::string& filename) const;
    void ExportVibrationalMetrics(const std::string& filename) const;
    
    // Getters
    const std::vector<MeasurementPoint>& GetMeasurementPoints() const { return measurement_points_; }
    MeasurementPoint* GetMeasurementPoint(const std::string& name);
};

// =============================================================================
// Complete Helicopter Rotor System
// =============================================================================

class HelicopterRotorDynamicsSystem {
public:
    struct SystemConfiguration {
        // Rotor parameters
        double rotor_radius = 6.5;          // m
        double rotor_rpm = 350.0;           // RPM
        int num_blades = 4;
        double hub_height = 3.0;            // m above fuselage
        
        // Blade parameters
        double blade_chord = 0.35;          // m
        double blade_thickness = 0.02;      // m
        double blade_density = 400.0;       // kg/m³
        double blade_young_modulus = 70e9;  // Pa
        int blade_elements = 12;            // Number of FE elements per blade
        
        // Fuselage parameters
        double fuselage_length = 8.0;       // m
        double fuselage_width = 2.0;        // m
        double fuselage_height = 2.5;       // m
        double fuselage_mass = 2000.0;      // kg
        bool fuselage_fixed = true;         // Fixed or free fuselage
        
        // Hub parameters
        double hub_radius = 0.3;            // m
        double hub_height = 0.2;            // m
        double hub_mass = 150.0;            // kg
    };

private:
    // Core system components
    std::shared_ptr<ChSystemNSC> system_;
    SystemConfiguration config_;
    
    // Physical components
    std::shared_ptr<ChBody> fuselage_;
    std::shared_ptr<ChBody> rotor_hub_;
    std::shared_ptr<ChLinkMotorRotationSpeed> rotor_motor_;
    
    // Blade system
    std::vector<std::shared_ptr<fea::ChMesh>> blade_meshes_;
    std::vector<std::vector<std::shared_ptr<fea::ChNodeFEAxyzrot>>> blade_nodes_;
    std::vector<std::vector<std::shared_ptr<fea::ChElementBeamEuler>>> blade_elements_;
    
    // Analysis systems
    std::unique_ptr<AdvancedAerodynamicModel> aerodynamic_model_;
    std::unique_ptr<MassImbalanceModel> mass_imbalance_model_;
    std::unique_ptr<PitchControlSystem> pitch_control_system_;
    std::unique_ptr<VibrationAnalysisSystem> vibration_analysis_;

public:
    HelicopterRotorDynamicsSystem(const SystemConfiguration& config);
    ~HelicopterRotorDynamicsSystem() = default;
    
    // Initialization
    void Initialize();
    void CreateFuselageAndHub();
    void CreateRotorBlades();
    void SetupControlSystems();
    void SetupMeasurementPoints();
    
    // Simulation control
    void RunSimulation(double end_time, double time_step);
    void UpdateSystemDynamics(double time);
    void ApplyAerodynamicLoads(double time);
    void ApplyControlLoads(double time);
    void ApplyMassImbalanceLoads(double time);
    
    // Configuration and control
    void SetRotorRPM(double rpm);
    void SetControlInputs(const PitchControlSystem::ControlInputs& inputs);
    void SetFlightConditions(const AdvancedAerodynamicModel::FlightConditions& conditions);
    void AddMassImbalance(int blade_index, const MassImbalanceModel::ImbalanceProperties& imbalance);
    
    // Analysis and output
    void ExportResults(const std::string& base_filename);
    void PrintSystemStatus();
    
    // Getters
    std::shared_ptr<ChSystemNSC> GetChronoSystem() const { return system_; }
    VibrationAnalysisSystem* GetVibrationAnalysis() const { return vibration_analysis_.get(); }
    PitchControlSystem* GetPitchControlSystem() const { return pitch_control_system_.get(); }
    const SystemConfiguration& GetConfiguration() const { return config_; }
};

// =============================================================================
// Utility Functions
// =============================================================================

namespace utils {
    // Mathematical utilities
    double LinearInterpolation(double x, const std::vector<double>& x_data, const std::vector<double>& y_data);
    std::vector<std::complex<double>> FFT(const std::vector<double>& input);
    double CalculateRMS(const std::vector<double>& data);
    
    // Coordinate transformations
    ChVector3d BladeToHub(const ChVector3d& blade_coords, double azimuth_angle);
    ChVector3d HubToFuselage(const ChVector3d& hub_coords, const ChFrame<>& hub_frame);
    
    // File I/O utilities
    void WriteMatrixToFile(const std::string& filename, const std::vector<std::vector<double>>& matrix);
    void WriteVectorToFile(const std::string& filename, const std::vector<ChVector3d>& vectors);
    
    // Unit conversions
    double RPMToRadPerSec(double rpm);
    double RadPerSecToRPM(double rad_per_sec);
    double DegToRad(double degrees);
    double RadToDeg(double radians);
}

}  // namespace helicopter
}  // namespace chrono

#endif  // HELICOPTER_ROTOR_DYNAMICS_H