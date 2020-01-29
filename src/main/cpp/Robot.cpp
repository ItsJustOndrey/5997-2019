/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  timer.Start();



  //Camera Code
  intakeCamera = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
  panelCamera = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);
  //server = frc::CameraServer::GetInstance()->GetServer();
  //intakeCamera.SetConnectionStrategy(cs::VideoSource::ConnectionStrategy::kConnectionKeepOpen);
  //panelCamera.SetConnectionStrategy(cs::VideoSource::ConnectionStrategy::kConnectionKeepOpen);
  
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }

}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
    if(timer.Get() < 2.0)
  {
    m_rightIntake.Set(.5);
  }
  } else {
    // Default Auto goes here
  }

  ///////////////////Code that made the robot drive in autonomous/////////////////////////
  c.SetClosedLoopControl(true);
	c.Start();
	c.GetPressureSwitchValue();

  //Code That Enables Robot To Drive In ArcadeDrive
  m_robotDrive.ArcadeDrive(m_controller.GetRawAxis(1), -m_controller.GetRawAxis(4));

  //When X is pressed, Piston will extend
  if(m_stick.GetRawButton(3))
  {
    m_panel.Set(frc::DoubleSolenoid::Value::kForward);
  }
  //When X is Released, Piston will retract
  else if(m_stick.GetRawButtonReleased(3))
  {
    m_panel.Set(frc::DoubleSolenoid::Value::kReverse);
  }
  ///////////////////////////////////////////////////////////////////////////////////////
  
}

void Robot::TeleopInit() 
{
   
}

void Robot::TeleopPeriodic() 
{
  //*****************************************Turns Compressor On and Off**************************************//
  c.SetClosedLoopControl(true);
	c.Start();
	c.GetPressureSwitchValue();
  //**********************************************************************************************************//

  //Code That Enables Robot To Drive In ArcadeDrive
  m_robotDrive.ArcadeDrive(m_controller.GetRawAxis(1), -m_controller.GetRawAxis(4));


  //***********************************************Intake Control*********************************************//
  //Right Bumper
  if(m_controller.GetRawButton(6))
  {
    m_leftIntake.Set(.5);
    m_rightIntake.Set(-.5);
  }
  //Left Bumper
  else if(m_controller.GetRawButton(5))
  {
    m_leftIntake.Set(-1);
    m_rightIntake.Set(1);
  }
  //Turns Motors Off
  else
  {
    m_leftIntake.Set(0);
    m_rightIntake.Set(0);
  }
  
  //Intake Axis Control On Second Controller
  double axis = -m_stick.GetRawAxis(1);
  m_vertIntake.Set(axis);
  //**********************************************************************************************************//


  //**********************************************Piston Controls*********************************************//
  //Controls for ball intake
  //Right Bumper Pressed Closes Intake
  if(m_stick.GetRawButtonPressed(5))
  {
    m_intakePiston.Set(frc::DoubleSolenoid::Value::kForward);
  }
  //Right Bumper Released Opens Intake
  else if(m_stick.GetRawButtonReleased(5))
  {
    m_intakePiston.Set(frc::DoubleSolenoid::Value::kReverse);
  }

  //Controls for Stage One Lifting Piston
  //When X is pressed, Big Bois go forward
  if(m_controller.GetRawButtonPressed(3))
  {
    m_stageOneElevator.Set(frc::DoubleSolenoid::Value::kForward);
  }
  //When X is released, Big Bois go back
  else if(m_controller.GetRawButtonReleased(3))
  {
    m_stageOneElevator.Set(frc::DoubleSolenoid::Value::kReverse);
  }

  //Controls for Panel Shooter
  //When X is pressed, Piston will extend
  if(m_stick.GetRawButtonPressed(3))
  {
    m_panel.Set(frc::DoubleSolenoid::Value::kForward);
  }
  //When X is Released, Piston will retract
  else if(m_stick.GetRawButtonReleased(3))
  {
    m_panel.Set(frc::DoubleSolenoid::Value::kReverse);
  }
  //**********************************************************************************************************//
}

void Robot::TestPeriodic() 
{
  
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
