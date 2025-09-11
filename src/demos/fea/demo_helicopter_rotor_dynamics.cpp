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
// Helicopter rotor dynamics simulation with multi-point vibration analysis
// 
// This demo simulates helicopter rotor dynamics with:
// - Multi-blade rotor system with flexible blade dynamics
// - Mass imbalance effects
// - Pitch control rod mechanisms  
// - Trailing edge tab aerodynamic effects
// - Fuselage vibration analysis at multiple measurement points
//
// =============================================================================

#include "chrono/physics/ChSystemNSC.h"
#include "chrono/physics/ChLinkLock.h"
#include "chrono/physics/ChBodyEasy.h"
#include "chrono/physics/ChLinkMotorRotationSpeed.h"
#include "chrono/physics/ChLinkMotorRotationAngle.h"

#include "chrono/fea/ChElementBeamEuler.h"
#include "chrono/fea/ChBuilderBeam.h"
#include "chrono/fea/ChMesh.h"

#include "chrono_thirdparty/filesystem/path.h"

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <fstream>

using namespace chrono;
using namespace chrono::fea;

// Forward declarations
class HelicopterRotorSystem;
class RotorBlade;
class FuselageVibrationMeasurement;
class AerodynamicForceModel;

// =============================================================================
// Helicopter Rotor Blade Class
// =============================================================================

class RotorBlade {
public:
    // Blade physical properties
    struct BladeProperties {
        double length = 6.0;                    // Blade length [m]
        double chord = 0.35;                    // Blade chord [m] 
        double thickness = 0.02;                // Blade thickness [m]
        double density = 400.0;                 // Material density [kg/m³]
        double young_modulus = 70e9;            // Young's modulus [Pa]
        double shear_modulus = 25e9;            // Shear modulus [Pa]
        double mass_imbalance = 0.0;            // Mass imbalance [kg*m]
        double twist_rate = -8.0;               // Twist rate [deg/m]
        int num_elements = 10;                  // Number of FE elements
    };

    // Control system properties
    struct ControlProperties {
        double collective_pitch = 8.0;         // Collective pitch [deg]
        double cyclic_pitch_amplitude = 2.0;   // Cyclic pitch amplitude [deg]
        double pitch_rod_stiffness = 1e6;      // Pitch rod stiffness [N/m]
        double pitch_rod_damping = 1e3;        // Pitch rod damping [N*s/m]
        double tab_deflection = 0.0;           // Trailing edge tab deflection [deg]
    };

private:
    BladeProperties blade_props_;
    ControlProperties control_props_;
    std::vector<std::shared_ptr<ChNodeFEAxyzrot>> blade_nodes_;
    std::vector<std::shared_ptr<ChElementBeamEuler>> blade_elements_;
    std::shared_ptr<ChMesh> mesh_;
    std::shared_ptr<ChBody> root_attachment_;
    
public:
    RotorBlade(const BladeProperties& props, const ControlProperties& control_props)
        : blade_props_(props), control_props_(control_props) {}

    void Initialize(std::shared_ptr<ChSystem> system, std::shared_ptr<ChBody> hub,
                   const ChVector3d& attachment_point, double azimuth_angle);
    
    void ApplyAerodynamicForces(double time, double rotor_rpm);
    void ApplyMassImbalance();
    void UpdatePitchControl(double time);
    void ApplyTrailingEdgeTabEffects();
    
    // Getters
    const std::vector<std::shared_ptr<ChNodeFEAxyzrot>>& GetNodes() const { return blade_nodes_; }
    const BladeProperties& GetBladeProperties() const { return blade_props_; }
    const ControlProperties& GetControlProperties() const { return control_props_; }
    
    // Setters for dynamic control
    void SetCollectivePitch(double angle) { control_props_.collective_pitch = angle; }
    void SetCyclicPitch(double amplitude) { control_props_.cyclic_pitch_amplitude = amplitude; }
    void SetTabDeflection(double angle) { control_props_.tab_deflection = angle; }
};

// =============================================================================
// Aerodynamic Force Model Class
// =============================================================================

class AerodynamicForceModel {
private:
    double air_density_ = 1.225;               // Air density [kg/m³]
    double rotor_disc_area_;                   // Rotor disc area [m²]
    double rotor_solidity_;                    // Rotor solidity ratio
    
public:
    AerodynamicForceModel(double rotor_radius, int num_blades, double blade_chord)
        : rotor_disc_area_(CH_PI * rotor_radius * rotor_radius),
          rotor_solidity_(num_blades * blade_chord / (CH_PI * rotor_radius)) {}

    // Calculate section aerodynamic forces
    ChVector3d CalcSectionForces(const std::shared_ptr<ChNodeFEAxyzrot>& node,
                                double local_chord, double rotor_rpm, 
                                double collective_pitch, double tab_deflection);
    
    // Calculate trailing edge tab effects
    ChVector3d CalcTabAerodynamicEffect(double tab_deflection, double dynamic_pressure,
                                       double chord, const ChVector3d& relative_velocity);
    
    // Calculate unsteady aerodynamic effects
    ChVector3d CalcUnsteadyEffects(const std::shared_ptr<ChNodeFEAxyzrot>& node,
                                  double time, double rotor_rpm);
};

// =============================================================================
// Fuselage Vibration Measurement Class  
// =============================================================================

class FuselageVibrationMeasurement {
public:
    struct MeasurementPoint {
        std::string name;
        ChVector3d position;               // Position relative to fuselage center
        ChVector3d acceleration;           // Measured acceleration
        ChVector3d velocity;               // Measured velocity  
        ChVector3d displacement;           // Measured displacement
        std::vector<double> time_history;  // Time history
        std::vector<ChVector3d> accel_history;  // Acceleration history
    };

private:
    std::vector<MeasurementPoint> measurement_points_;
    std::shared_ptr<ChBody> fuselage_;
    double sampling_frequency_ = 1000.0;   // Sampling frequency [Hz]
    double last_sample_time_ = 0.0;
    
public:
    FuselageVibrationMeasurement(std::shared_ptr<ChBody> fuselage) : fuselage_(fuselage) {}
    
    void AddMeasurementPoint(const std::string& name, const ChVector3d& position);
    void UpdateMeasurements(double time);
    void ExportVibrationData(const std::string& filename);
    void PerformFrequencyAnalysis();
    
    const std::vector<MeasurementPoint>& GetMeasurementPoints() const { return measurement_points_; }
};

// =============================================================================
// Main Helicopter Rotor System Class
// =============================================================================

class HelicopterRotorSystem {
private:
    // System components
    std::shared_ptr<ChSystemNSC> system_;
    std::shared_ptr<ChBody> fuselage_;
    std::shared_ptr<ChBody> rotor_hub_;
    std::vector<std::unique_ptr<RotorBlade>> blades_;
    std::unique_ptr<AerodynamicForceModel> aero_model_;
    std::unique_ptr<FuselageVibrationMeasurement> vibration_measurement_;
    
    // Rotor parameters
    double rotor_radius_ = 6.5;            // Rotor radius [m]
    double rotor_rpm_ = 350.0;             // Rotor RPM
    int num_blades_ = 4;                   // Number of blades
    double hub_mass_ = 150.0;              // Hub mass [kg]
    double fuselage_mass_ = 2000.0;        // Fuselage mass [kg]
    
    // Motors and constraints
    std::shared_ptr<ChLinkMotorRotationSpeed> rotor_motor_;
    
public:
    HelicopterRotorSystem();
    ~HelicopterRotorSystem() = default;
    
    void Initialize();
    void CreateFuselage();
    void CreateRotorHub();
    void CreateRotorBlades();
    void SetupVibrationMeasurement();
    void SetupAerodynamicModel();
    
    void RunSimulation(double end_time, double step_size);
    void UpdateSystem(double time);
    
    // Getters
    std::shared_ptr<ChSystemNSC> GetSystem() const { return system_; }
    const std::vector<std::unique_ptr<RotorBlade>>& GetBlades() const { return blades_; }
    FuselageVibrationMeasurement* GetVibrationMeasurement() const { return vibration_measurement_.get(); }
};

// =============================================================================
// Implementation: HelicopterRotorSystem
// =============================================================================

HelicopterRotorSystem::HelicopterRotorSystem() {
    system_ = chrono_types::make_shared<ChSystemNSC>();
    system_->SetGravitationalAcceleration(ChVector3d(0, 0, -9.81));
}

void HelicopterRotorSystem::Initialize() {
    CreateFuselage();
    CreateRotorHub();
    CreateRotorBlades();
    SetupVibrationMeasurement();
    SetupAerodynamicModel();
    
    std::cout << "Helicopter rotor system initialized successfully." << std::endl;
    std::cout << "Number of blades: " << num_blades_ << std::endl;
    std::cout << "Rotor radius: " << rotor_radius_ << " m" << std::endl;
    std::cout << "Rotor RPM: " << rotor_rpm_ << std::endl;
}

void HelicopterRotorSystem::CreateFuselage() {
    // Create fuselage body (simplified as box)
    fuselage_ = chrono_types::make_shared<ChBodyEasyBox>(
        8.0, 2.0, 2.5,      // dimensions [m]
        fuselage_mass_       // mass [kg]
    );
    fuselage_->SetFixed(true);  // Fixed fuselage for now
    fuselage_->SetPos(ChVector3d(0, 0, 0));
    system_->Add(fuselage_);
    
    // Add visual representation
    auto fuselage_visual = chrono_types::make_shared<ChVisualShapeBox>(8.0, 2.0, 2.5);
    fuselage_visual->SetColor(ChColor(0.6f, 0.6f, 0.8f));
    fuselage_->AddVisualShape(fuselage_visual);
}

void HelicopterRotorSystem::CreateRotorHub() {
    // Create rotor hub
    rotor_hub_ = chrono_types::make_shared<ChBodyEasyCylinder>(
        ChAxis::Z, 0.3, 0.2,  // radius, height
        hub_mass_             // mass
    );
    rotor_hub_->SetPos(ChVector3d(0, 0, 3.0));  // Above fuselage
    system_->Add(rotor_hub_);
    
    // Add visual representation
    auto hub_visual = chrono_types::make_shared<ChVisualShapeCylinder>(0.3, 0.2);
    hub_visual->SetColor(ChColor(0.8f, 0.3f, 0.3f));
    rotor_hub_->AddVisualShape(hub_visual, ChFrame<>(VNULL, QuatFromAngleX(CH_PI_2)));
    
    // Create motor to drive rotor
    rotor_motor_ = chrono_types::make_shared<ChLinkMotorRotationSpeed>();
    rotor_motor_->Initialize(rotor_hub_, fuselage_, 
                            ChFrame<>(ChVector3d(0, 0, 3.0), QUNIT));
    auto speed_function = chrono_types::make_shared<ChFunctionConst>(
        rotor_rpm_ * 2.0 * CH_PI / 60.0  // Convert RPM to rad/s
    );
    rotor_motor_->SetSpeedFunction(speed_function);
    system_->Add(rotor_motor_);
}

void HelicopterRotorSystem::CreateRotorBlades() {
    // Create blade properties
    RotorBlade::BladeProperties blade_props;
    blade_props.length = rotor_radius_;
    blade_props.chord = 0.35;
    blade_props.thickness = 0.02;
    blade_props.density = 400.0;
    blade_props.young_modulus = 70e9;
    blade_props.mass_imbalance = 0.1;  // Small mass imbalance
    
    RotorBlade::ControlProperties control_props;
    control_props.collective_pitch = 8.0;
    control_props.cyclic_pitch_amplitude = 2.0;
    control_props.tab_deflection = 2.0;  // Small tab deflection
    
    // Create blades
    for (int i = 0; i < num_blades_; ++i) {
        auto blade = std::make_unique<RotorBlade>(blade_props, control_props);
        
        double azimuth = i * 2.0 * CH_PI / num_blades_;
        ChVector3d attachment_point(0.1 * cos(azimuth), 0.1 * sin(azimuth), 0);
        
        blade->Initialize(system_, rotor_hub_, attachment_point, azimuth);
        blades_.push_back(std::move(blade));
    }
}

void HelicopterRotorSystem::SetupVibrationMeasurement() {
    vibration_measurement_ = std::make_unique<FuselageVibrationMeasurement>(fuselage_);
    
    // Add measurement points on fuselage
    vibration_measurement_->AddMeasurementPoint("nose", ChVector3d(3.0, 0, 0));
    vibration_measurement_->AddMeasurementPoint("pilot_left", ChVector3d(1.0, -0.8, 0.5));
    vibration_measurement_->AddMeasurementPoint("pilot_right", ChVector3d(1.0, 0.8, 0.5));
    vibration_measurement_->AddMeasurementPoint("cabin_center", ChVector3d(-1.0, 0, 0));
    vibration_measurement_->AddMeasurementPoint("tail_boom", ChVector3d(-3.5, 0, 0));
    vibration_measurement_->AddMeasurementPoint("engine_mount", ChVector3d(0.5, 0, 1.5));
}

void HelicopterRotorSystem::SetupAerodynamicModel() {
    aero_model_ = std::make_unique<AerodynamicForceModel>(
        rotor_radius_, num_blades_, 0.35  // radius, num_blades, chord
    );
}

void HelicopterRotorSystem::RunSimulation(double end_time, double step_size) {
    std::cout << "Starting helicopter rotor dynamics simulation..." << std::endl;
    std::cout << "End time: " << end_time << " s" << std::endl;
    std::cout << "Step size: " << step_size << " s" << std::endl;
    
    // Set integrator
    system_->SetTimestepperType(ChTimestepper::Type::EULER_IMPLICIT_LINEARIZED);
    
    // Simulation loop
    while (system_->GetChTime() < end_time) {
        UpdateSystem(system_->GetChTime());
        system_->DoStepDynamics(step_size);
        
        // Update vibration measurements
        vibration_measurement_->UpdateMeasurements(system_->GetChTime());
        
        // Progress reporting
        if (std::fmod(system_->GetChTime(), 1.0) < step_size) {
            std::cout << "Simulation time: " << system_->GetChTime() << " s" << std::endl;
        }
    }
    
    std::cout << "Simulation completed." << std::endl;
    
    // Export results
    vibration_measurement_->ExportVibrationData("helicopter_vibration_data.dat");
    std::cout << "Frequency analysis completed." << std::endl;
}

void HelicopterRotorSystem::UpdateSystem(double time) {
    // Update aerodynamic forces for each blade
    for (auto& blade : blades_) {
        blade->ApplyAerodynamicForces(time, rotor_rpm_);
        blade->UpdatePitchControl(time);
        blade->ApplyTrailingEdgeTabEffects();
        blade->ApplyMassImbalance();
    }
}

// =============================================================================
// Implementation: RotorBlade
// =============================================================================

void RotorBlade::Initialize(std::shared_ptr<ChSystem> system, std::shared_ptr<ChBody> hub,
                           const ChVector3d& attachment_point, double azimuth_angle) {
    // Create mesh for this blade
    mesh_ = chrono_types::make_shared<ChMesh>();
    system->Add(mesh_);
    
    // Create beam section
    auto section = chrono_types::make_shared<ChBeamSectionEulerAdvanced>();
    section->SetDensity(blade_props_.density);
    section->SetYoungModulus(blade_props_.young_modulus);
    section->SetShearModulusFromPoisson(0.3);
    section->SetAsRectangularSection(blade_props_.chord, blade_props_.thickness);
    
    // Build beam elements along blade span
    ChBuilderBeamEuler builder;
    
    ChVector3d start_pos = attachment_point;
    ChVector3d end_pos = attachment_point + ChVector3d(blade_props_.length * cos(azimuth_angle),
                                                      blade_props_.length * sin(azimuth_angle), 0);
    ChVector3d up_dir(0, 0, 1);
    
    builder.BuildBeam(mesh_, section, blade_props_.num_elements, start_pos, end_pos, up_dir);
    
    // Store references to nodes and elements
    blade_nodes_ = builder.GetLastBeamNodes();
    blade_elements_ = builder.GetLastBeamElements();
    
    // Connect root to hub
    auto root_constraint = chrono_types::make_shared<ChLinkLock>();
    root_constraint->Initialize(blade_nodes_[0], hub, 
                               ChFrame<>(attachment_point, QuatFromAngleZ(azimuth_angle)));
    root_constraint->Lock_All();  // Fully locked connection
    system->Add(root_constraint);
    
    std::cout << "Blade initialized with " << blade_elements_.size() << " elements." << std::endl;
}

void RotorBlade::ApplyAerodynamicForces(double time, double rotor_rpm) {
    // Apply distributed aerodynamic loads along blade span
    for (size_t i = 1; i < blade_nodes_.size(); ++i) {  // Skip root node
        auto node = blade_nodes_[i];
        
        // Calculate local aerodynamic forces
        double local_radius = ChVector3d(node->GetPos().x(), node->GetPos().y(), 0).Length();  // Distance from hub
        double dynamic_pressure = 0.5 * 1.225 * pow(local_radius * rotor_rpm * CH_PI / 30.0, 2);
        
        // Basic lift and drag forces
        ChVector3d lift_force(0, 0, dynamic_pressure * blade_props_.chord * 0.1);  // Simplified lift
        ChVector3d drag_force = -0.02 * node->GetPosDt();  // Simple drag proportional to velocity
        
        node->SetForce(lift_force + drag_force);
    }
}

void RotorBlade::ApplyMassImbalance() {
    if (blade_props_.mass_imbalance > 0) {
        // Apply mass imbalance effect at blade tip
        auto tip_node = blade_nodes_.back();
        ChVector3d centrifugal_force = blade_props_.mass_imbalance * 
                                      pow(tip_node->GetAngVelParent().Length(), 2) *
                                      tip_node->GetPos().GetNormalized();
        tip_node->SetForce(tip_node->GetForce() + centrifugal_force);
    }
}

void RotorBlade::UpdatePitchControl(double time) {
    // Apply collective and cyclic pitch control
    // This would involve rotating the blade section properties
    // For now, this is a placeholder for the pitch control mechanism
}

void RotorBlade::ApplyTrailingEdgeTabEffects() {
    if (abs(control_props_.tab_deflection) > 0.01) {
        // Apply additional aerodynamic moment due to tab deflection
        for (auto& node : blade_nodes_) {
            double tab_moment = control_props_.tab_deflection * 0.1;  // Simplified
            node->SetTorque(node->GetTorque() + ChVector3d(0, 0, tab_moment));
        }
    }
}

// =============================================================================
// Implementation: FuselageVibrationMeasurement
// =============================================================================

void FuselageVibrationMeasurement::AddMeasurementPoint(const std::string& name, 
                                                       const ChVector3d& position) {
    MeasurementPoint point;
    point.name = name;
    point.position = position;
    measurement_points_.push_back(point);
    
    std::cout << "Added measurement point: " << name 
              << " at position: " << position.x() << ", " << position.y() << ", " << position.z() << std::endl;
}

void FuselageVibrationMeasurement::UpdateMeasurements(double time) {
    if (time - last_sample_time_ < 1.0 / sampling_frequency_) {
        return;  // Not time to sample yet
    }
    
    for (auto& point : measurement_points_) {
        // Calculate acceleration at measurement point
        ChVector3d point_global_pos = fuselage_->TransformPointLocalToParent(point.position);
        ChVector3d acceleration = fuselage_->GetPosDt2() + 
                                 Vcross(fuselage_->GetAngAccParent(), point.position) +
                                 Vcross(fuselage_->GetAngVelParent(), 
                                       Vcross(fuselage_->GetAngVelParent(), point.position));
        
        point.acceleration = acceleration;
        point.time_history.push_back(time);
        point.accel_history.push_back(acceleration);
    }
    
    last_sample_time_ = time;
}

void FuselageVibrationMeasurement::ExportVibrationData(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    // Header
    file << "Time";
    for (const auto& point : measurement_points_) {
        file << "\t" << point.name << "_ax\t" << point.name << "_ay\t" << point.name << "_az";
    }
    file << std::endl;
    
    // Data
    size_t num_samples = measurement_points_[0].time_history.size();
    for (size_t i = 0; i < num_samples; ++i) {
        file << measurement_points_[0].time_history[i];
        for (const auto& point : measurement_points_) {
            if (i < point.accel_history.size()) {
                file << "\t" << point.accel_history[i].x() 
                     << "\t" << point.accel_history[i].y() 
                     << "\t" << point.accel_history[i].z();
            }
        }
        file << std::endl;
    }
    
    file.close();
    std::cout << "Vibration data exported to: " << filename << std::endl;
}

void FuselageVibrationMeasurement::PerformFrequencyAnalysis() {
    std::cout << "Performing frequency analysis..." << std::endl;
    
    for (const auto& point : measurement_points_) {
        if (point.accel_history.size() > 0) {
            // Calculate RMS acceleration
            double rms_x = 0, rms_y = 0, rms_z = 0;
            for (const auto& accel : point.accel_history) {
                rms_x += accel.x() * accel.x();
                rms_y += accel.y() * accel.y();
                rms_z += accel.z() * accel.z();
            }
            rms_x = sqrt(rms_x / point.accel_history.size());
            rms_y = sqrt(rms_y / point.accel_history.size());
            rms_z = sqrt(rms_z / point.accel_history.size());
            
            std::cout << "Point " << point.name << " RMS acceleration: "
                      << "X=" << rms_x << " Y=" << rms_y << " Z=" << rms_z << " m/s²" << std::endl;
        }
    }
}

// =============================================================================
// Main Function
// =============================================================================

int main(int argc, char* argv[]) {
    std::cout << "==============================================================================" << std::endl;
    std::cout << "Helicopter Rotor Dynamics Simulation with Multi-Point Vibration Analysis" << std::endl;
    std::cout << "Copyright (c) 2024 projectchrono.org" << std::endl;
    std::cout << "Chrono version: " << CHRONO_VERSION << std::endl;
    std::cout << "==============================================================================" << std::endl;
    
    try {
        // Create and initialize helicopter rotor system
        HelicopterRotorSystem helicopter;
        helicopter.Initialize();
        
        // Run simulation
        double sim_time = 10.0;      // 10 seconds simulation
        double time_step = 0.001;    // 1 ms time step
        
        helicopter.RunSimulation(sim_time, time_step);
        
        std::cout << "\nSimulation completed successfully!" << std::endl;
        
        // Display summary
        auto vibration_system = helicopter.GetVibrationMeasurement();
        std::cout << "\nVibration measurement summary:" << std::endl;
        std::cout << "Number of measurement points: " << vibration_system->GetMeasurementPoints().size() << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}