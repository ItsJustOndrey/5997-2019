/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/IterativeRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/drive/DifferentialDrive.h>
#include <WPILib.h>
#include <frc/XboxController.h>
#include <frc/Spark.h>
#include <frc/VictorSP.h>
#include <frc/Encoder.h>

class Robot : public frc::IterativeRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  
  
  int FRONT_LEFT = 0;
  int REAR_LEFT = 1;
  int FRONT_RIGHT = 2;
  int REAR_RIGHT = 3;
  //*****************************************ArcadeDrive***************************************//
  frc::VictorSP m_fLeft{FRONT_LEFT};
	frc::Spark m_rLeft{REAR_LEFT};
	frc::SpeedControllerGroup m_left{m_fLeft, m_rLeft};

	frc::Spark m_fRight{FRONT_RIGHT};
	frc::Spark m_rRight{REAR_RIGHT};
	frc::SpeedControllerGroup m_right{m_fRight, m_rRight};
	frc::DifferentialDrive m_robotDrive{m_left, m_right};
  //******************************************************************************************//

  // Controllers and Joysticks
  frc::Joystick m_controller{0};
  frc::Joystick m_stick{1};

  //Intake Motors and MotorControllers
  frc::Victor m_leftIntake{6}; //4
  frc::Victor m_rightIntake{7}; //5
  frc::Victor m_vertIntake{9};

  //Encoder
  frc::Encoder m_intakeEncoder{0,1,false,frc::Encoder::EncodingType::k4X};

  //Compressor
  frc::Compressor c{0};

  //Double Solonoid
  frc::DoubleSolenoid m_intakePiston{2,3};
  frc::DoubleSolenoid m_stageOneElevator{4,5};
  frc::DoubleSolenoid m_panel{0,1};

  //Camera
  cs::UsbCamera intakeCamera;
  cs::UsbCamera panelCamera;
  cs::VideoSink server;

  //PID Controls
  frc::AnalogInput m_input{0};
  frc::PIDController m_vertPID{0.1, 0.01, 0.0, &m_input, &m_vertIntake};

  //Timer
  frc::Timer timer;


};