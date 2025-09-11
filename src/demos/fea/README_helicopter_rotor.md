# Helicopter Rotor Dynamics Simulation

## Overview

This implementation provides a comprehensive helicopter rotor dynamics simulation system for analyzing vibrations at multiple measurement points on the fuselage. The simulation considers mass imbalance, pitch control rod, and trailing edge tab effects on both inertial and aerodynamic properties.

## 直升机旋翼动力学仿真

### 功能概述

本实现提供了一个全面的直升机旋翼动力学仿真系统，用于分析机身多个测点的振动。仿真考虑了质量不平衡、变距拉杆和后缘调整片对旋翼惯性效应和气动效应的影响。

## Implementation Architecture

### Core Components

1. **HelicopterRotorSystem** - Main system class coordinating all components
2. **RotorBlade** - Individual blade dynamics with FEA modeling
3. **AerodynamicForceModel** - Advanced aerodynamic calculations
4. **MassImbalanceModel** - Mass imbalance effects modeling
5. **PitchControlSystem** - Control system dynamics
6. **VibrationAnalysisSystem** - Multi-point vibration measurement

### Key Features

#### 1. Multi-Blade Rotor System (多旋翼系统)
- Flexible blade modeling using finite element analysis
- Individual blade dynamics with beam elements
- Rotor hub dynamics and coupling
- Configurable number of blades (typically 2-4)

#### 2. Mass Imbalance Effects (质量不平衡效应)
- Distributed mass imbalance along blade span
- Circumferential mass distribution variations
- Dynamic imbalance force and moment calculation
- Time-varying imbalance effects

#### 3. Pitch Control Rod Mechanism (变距拉杆机构)
- Collective pitch control
- Cyclic pitch control (longitudinal and lateral)
- Control system dynamics with lag and bandwidth
- Pitch rod stiffness and damping effects

#### 4. Trailing Edge Tab Effects (后缘调整片效应)
- Tab deflection aerodynamic modeling
- Modified section lift and moment characteristics
- Dynamic tab control capabilities
- Unsteady aerodynamic effects

#### 5. Aerodynamic Modeling (气动建模)
- Section-based aerodynamic calculations
- Dynamic pressure and angle of attack effects
- Lift, drag, and moment generation
- Forward flight and hover conditions
- Dynamic stall modeling

#### 6. Fuselage Vibration Analysis (机身振动分析)
- Multiple measurement points configuration
- Time-domain acceleration, velocity, displacement
- Frequency-domain analysis (FFT)
- RMS and spectral analysis
- Vibration transmission modeling

## File Structure

```
src/demos/fea/
├── demo_helicopter_rotor_dynamics.cpp     # Main comprehensive implementation
├── demo_helicopter_rotor_test.cpp         # Simplified test implementation
├── helicopter_rotor_dynamics.h            # Header with advanced classes
└── README_helicopter_rotor.md              # This documentation
```

## Usage Examples

### Basic Usage

```cpp
// Create helicopter rotor system
HelicopterRotorDynamicsSystem::SystemConfiguration config;
config.rotor_radius = 6.5;  // meters
config.rotor_rpm = 350.0;   // RPM
config.num_blades = 4;      // 4-blade rotor

HelicopterRotorDynamicsSystem helicopter(config);
helicopter.Initialize();

// Set control inputs
PitchControlSystem::ControlInputs controls;
controls.collective_pitch = 0.15;    // radians (~8.6 degrees)
controls.longitudinal_cyclic = 0.02; // radians
controls.lateral_cyclic = -0.01;     // radians
helicopter.SetControlInputs(controls);

// Add mass imbalance
MassImbalanceModel::ImbalanceProperties imbalance;
imbalance.mass_magnitude = 0.5;      // kg
imbalance.radial_position = 5.0;     // meters from root
helicopter.AddMassImbalance(0, imbalance);  // Blade 0

// Run simulation
helicopter.RunSimulation(10.0, 0.001);  // 10 seconds, 1ms time step

// Export results
helicopter.ExportResults("helicopter_simulation");
```

### Measurement Point Configuration

```cpp
// Add vibration measurement points
auto vibration_system = helicopter.GetVibrationAnalysis();
vibration_system->AddMeasurementPoint("pilot_seat", ChVector3d(1.0, 0, 0.5));
vibration_system->AddMeasurementPoint("cabin_center", ChVector3d(-1.0, 0, 0));
vibration_system->AddMeasurementPoint("tail_boom", ChVector3d(-3.5, 0, 0));
vibration_system->AddMeasurementPoint("engine_mount", ChVector3d(0.5, 0, 1.5));
```

## Physics Implementation Details

### 1. Blade Dynamics

The rotor blades are modeled using Chrono's finite element analysis (FEA) capabilities:

- **Beam Elements**: ChElementBeamEuler for flexible blade representation
- **Material Properties**: Density, Young's modulus, shear modulus
- **Geometric Properties**: Chord, thickness, twist distribution
- **Boundary Conditions**: Root attachment to hub

### 2. Aerodynamic Forces

Aerodynamic forces are calculated using:

```cpp
// Lift calculation
double alpha = atan2(velocity_z, velocity_x);  // Angle of attack
double lift_coefficient = lift_curve_slope * (alpha - zero_lift_angle);
double lift_force = 0.5 * air_density * velocity_squared * chord * lift_coefficient;

// Drag calculation  
double drag_coefficient = drag_coefficient_0 + induced_drag_factor * lift_coefficient^2;
double drag_force = 0.5 * air_density * velocity_squared * chord * drag_coefficient;
```

### 3. Mass Imbalance Forces

Mass imbalance effects are computed as:

```cpp
// Centrifugal force due to mass imbalance
ChVector3d centrifugal_force = mass_imbalance * omega^2 * radius_vector;

// Gyroscopic moment
ChVector3d gyroscopic_moment = Vcross(angular_velocity, angular_momentum_imbalance);
```

### 4. Control System Dynamics

The pitch control system includes:

- **Actuator Dynamics**: First-order lag with specified bandwidth
- **Control Authority**: Collective and cyclic pitch limits
- **Mechanical Coupling**: Pitch rod stiffness and damping
- **Tab Control**: Trailing edge tab deflection effects

### 5. Vibration Transmission

Forces from the rotor are transmitted to the fuselage through:

- **Hub Forces**: 6-DOF force and moment transmission
- **Structural Coupling**: Hub-to-fuselage mount stiffness
- **Dynamic Amplification**: Resonance and frequency response

## Validation and Testing

### Test Cases

1. **Static Balance Test**: Verify blade forces balance in hover
2. **Dynamic Response**: Validate frequency response characteristics
3. **Mass Imbalance**: Confirm imbalance force generation
4. **Control Response**: Test pitch control effectiveness
5. **Vibration Levels**: Compare with experimental data

### Output Data

The simulation generates:

- **Time History Data**: Acceleration, velocity, displacement at all measurement points
- **Frequency Spectra**: FFT analysis of vibration signals
- **RMS Levels**: Overall vibration magnitude metrics
- **Force/Moment Data**: Rotor hub loads for design analysis

## Applications

This simulation system can be used for:

1. **Design Optimization**: Blade geometry and material selection
2. **Vibration Reduction**: Active/passive vibration control design
3. **Structural Analysis**: Fuselage fatigue and loads analysis  
4. **Control System Design**: Flight control system development
5. **Certification**: Vibration limit compliance verification

## Technical References

1. Bramwell, A.R.S., "Helicopter Dynamics", Butterworth-Heinemann, 2001
2. Johnson, W., "Helicopter Theory", Princeton University Press, 1980
3. Prouty, R.W., "Helicopter Performance, Stability and Control", Krieger Publishing, 2002
4. Leishman, J.G., "Principles of Helicopter Aerodynamics", Cambridge University Press, 2006

## Future Enhancements

Potential improvements include:

1. **Advanced Aerodynamics**: Higher-fidelity unsteady aerodynamic modeling
2. **Ground Effect**: Near-ground aerodynamic interactions
3. **Engine Dynamics**: Engine-rotor coupling effects
4. **Active Control**: Active vibration control implementation
5. **Multi-Rotor**: Tandem and coaxial rotor configurations
6. **GUI Interface**: Real-time visualization and control panel