<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  (c) 1999 Andreas Gal		<gal@cs.uni-magdeburg.de>
 *  (c) 2000-2001 Vojtech Pavlik	<vojtech@ucw.cz>
 *  (c) 2007-2009 Jiri Kosina
 *
 *  HID debugging support
 */

/*
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/poll.h>

#समावेश <linux/hid.h>
#समावेश <linux/hid-debug.h>

अटल काष्ठा dentry *hid_debug_root;

काष्ठा hid_usage_entry अणु
	अचिन्हित  page;
	अचिन्हित  usage;
	स्थिर अक्षर     *description;
पूर्ण;

अटल स्थिर काष्ठा hid_usage_entry hid_usage_table[] = अणु
  अणु  0,      0, "Undefined" पूर्ण,
  अणु  1,      0, "GenericDesktop" पूर्ण,
    अणु0, 0x01, "Pointer"पूर्ण,
    अणु0, 0x02, "Mouse"पूर्ण,
    अणु0, 0x04, "Joystick"पूर्ण,
    अणु0, 0x05, "GamePad"पूर्ण,
    अणु0, 0x06, "Keyboard"पूर्ण,
    अणु0, 0x07, "Keypad"पूर्ण,
    अणु0, 0x08, "MultiAxis"पूर्ण,
      अणु0, 0x30, "X"पूर्ण,
      अणु0, 0x31, "Y"पूर्ण,
      अणु0, 0x32, "Z"पूर्ण,
      अणु0, 0x33, "Rx"पूर्ण,
      अणु0, 0x34, "Ry"पूर्ण,
      अणु0, 0x35, "Rz"पूर्ण,
      अणु0, 0x36, "Slider"पूर्ण,
      अणु0, 0x37, "Dial"पूर्ण,
      अणु0, 0x38, "Wheel"पूर्ण,
      अणु0, 0x39, "HatSwitch"पूर्ण,
    अणु0, 0x3a, "CountedBuffer"पूर्ण,
      अणु0, 0x3b, "ByteCount"पूर्ण,
      अणु0, 0x3c, "MotionWakeup"पूर्ण,
      अणु0, 0x3d, "Start"पूर्ण,
      अणु0, 0x3e, "Select"पूर्ण,
      अणु0, 0x40, "Vx"पूर्ण,
      अणु0, 0x41, "Vy"पूर्ण,
      अणु0, 0x42, "Vz"पूर्ण,
      अणु0, 0x43, "Vbrx"पूर्ण,
      अणु0, 0x44, "Vbry"पूर्ण,
      अणु0, 0x45, "Vbrz"पूर्ण,
      अणु0, 0x46, "Vno"पूर्ण,
    अणु0, 0x80, "SystemControl"पूर्ण,
      अणु0, 0x81, "SystemPowerDown"पूर्ण,
      अणु0, 0x82, "SystemSleep"पूर्ण,
      अणु0, 0x83, "SystemWakeUp"पूर्ण,
      अणु0, 0x84, "SystemContextMenu"पूर्ण,
      अणु0, 0x85, "SystemMainMenu"पूर्ण,
      अणु0, 0x86, "SystemAppMenu"पूर्ण,
      अणु0, 0x87, "SystemMenuHelp"पूर्ण,
      अणु0, 0x88, "SystemMenuExit"पूर्ण,
      अणु0, 0x89, "SystemMenuSelect"पूर्ण,
      अणु0, 0x8a, "SystemMenuRight"पूर्ण,
      अणु0, 0x8b, "SystemMenuLeft"पूर्ण,
      अणु0, 0x8c, "SystemMenuUp"पूर्ण,
      अणु0, 0x8d, "SystemMenuDown"पूर्ण,
      अणु0, 0x90, "D-PadUp"पूर्ण,
      अणु0, 0x91, "D-PadDown"पूर्ण,
      अणु0, 0x92, "D-PadRight"पूर्ण,
      अणु0, 0x93, "D-PadLeft"पूर्ण,
  अणु  2, 0, "Simulation" पूर्ण,
      अणु0, 0xb0, "Aileron"पूर्ण,
      अणु0, 0xb1, "AileronTrim"पूर्ण,
      अणु0, 0xb2, "Anti-Torque"पूर्ण,
      अणु0, 0xb3, "Autopilot"पूर्ण,
      अणु0, 0xb4, "Chaff"पूर्ण,
      अणु0, 0xb5, "Collective"पूर्ण,
      अणु0, 0xb6, "DiveBrake"पूर्ण,
      अणु0, 0xb7, "ElectronicCountermeasures"पूर्ण,
      अणु0, 0xb8, "Elevator"पूर्ण,
      अणु0, 0xb9, "ElevatorTrim"पूर्ण,
      अणु0, 0xba, "Rudder"पूर्ण,
      अणु0, 0xbb, "Throttle"पूर्ण,
      अणु0, 0xbc, "FlightCommunications"पूर्ण,
      अणु0, 0xbd, "FlareRelease"पूर्ण,
      अणु0, 0xbe, "LandingGear"पूर्ण,
      अणु0, 0xbf, "ToeBrake"पूर्ण,
  अणु  6, 0, "GenericDeviceControls" पूर्ण,
      अणु0, 0x20, "BatteryStrength" पूर्ण,
      अणु0, 0x21, "WirelessChannel" पूर्ण,
      अणु0, 0x22, "WirelessID" पूर्ण,
      अणु0, 0x23, "DiscoverWirelessControl" पूर्ण,
      अणु0, 0x24, "SecurityCodeCharacterEntered" पूर्ण,
      अणु0, 0x25, "SecurityCodeCharactedErased" पूर्ण,
      अणु0, 0x26, "SecurityCodeCleared" पूर्ण,
  अणु  7, 0, "Keyboard" पूर्ण,
  अणु  8, 0, "LED" पूर्ण,
      अणु0, 0x01, "NumLock"पूर्ण,
      अणु0, 0x02, "CapsLock"पूर्ण,
      अणु0, 0x03, "ScrollLock"पूर्ण,
      अणु0, 0x04, "Compose"पूर्ण,
      अणु0, 0x05, "Kana"पूर्ण,
      अणु0, 0x4b, "GenericIndicator"पूर्ण,
  अणु  9, 0, "Button" पूर्ण,
  अणु 10, 0, "Ordinal" पूर्ण,
  अणु 12, 0, "Consumer" पूर्ण,
      अणु0, 0x238, "HorizontalWheel"पूर्ण,
  अणु 13, 0, "Digitizers" पूर्ण,
    अणु0, 0x01, "Digitizer"पूर्ण,
    अणु0, 0x02, "Pen"पूर्ण,
    अणु0, 0x03, "LightPen"पूर्ण,
    अणु0, 0x04, "TouchScreen"पूर्ण,
    अणु0, 0x05, "TouchPad"पूर्ण,
    अणु0, 0x0e, "DeviceConfiguration"पूर्ण,
    अणु0, 0x20, "Stylus"पूर्ण,
    अणु0, 0x21, "Puck"पूर्ण,
    अणु0, 0x22, "Finger"पूर्ण,
    अणु0, 0x23, "DeviceSettings"पूर्ण,
    अणु0, 0x30, "TipPressure"पूर्ण,
    अणु0, 0x31, "BarrelPressure"पूर्ण,
    अणु0, 0x32, "InRange"पूर्ण,
    अणु0, 0x33, "Touch"पूर्ण,
    अणु0, 0x34, "UnTouch"पूर्ण,
    अणु0, 0x35, "Tap"पूर्ण,
    अणु0, 0x39, "TabletFunctionKey"पूर्ण,
    अणु0, 0x3a, "ProgramChangeKey"पूर्ण,
    अणु0, 0x3c, "Invert"पूर्ण,
    अणु0, 0x42, "TipSwitch"पूर्ण,
    अणु0, 0x43, "SecondaryTipSwitch"पूर्ण,
    अणु0, 0x44, "BarrelSwitch"पूर्ण,
    अणु0, 0x45, "Eraser"पूर्ण,
    अणु0, 0x46, "TabletPick"पूर्ण,
    अणु0, 0x47, "Confidence"पूर्ण,
    अणु0, 0x48, "Width"पूर्ण,
    अणु0, 0x49, "Height"पूर्ण,
    अणु0, 0x51, "ContactID"पूर्ण,
    अणु0, 0x52, "InputMode"पूर्ण,
    अणु0, 0x53, "DeviceIndex"पूर्ण,
    अणु0, 0x54, "ContactCount"पूर्ण,
    अणु0, 0x55, "ContactMaximumNumber"पूर्ण,
    अणु0, 0x59, "ButtonType"पूर्ण,
    अणु0, 0x5A, "SecondaryBarrelSwitch"पूर्ण,
    अणु0, 0x5B, "TransducerSerialNumber"पूर्ण,
  अणु 15, 0, "PhysicalInterfaceDevice" पूर्ण,
    अणु0, 0x00, "Undefined"पूर्ण,
    अणु0, 0x01, "Physical_Interface_Device"पूर्ण,
      अणु0, 0x20, "Normal"पूर्ण,
    अणु0, 0x21, "Set_Effect_Report"पूर्ण,
      अणु0, 0x22, "Effect_Block_Index"पूर्ण,
      अणु0, 0x23, "Parameter_Block_Offset"पूर्ण,
      अणु0, 0x24, "ROM_Flag"पूर्ण,
      अणु0, 0x25, "Effect_Type"पूर्ण,
        अणु0, 0x26, "ET_Constant_Force"पूर्ण,
        अणु0, 0x27, "ET_Ramp"पूर्ण,
        अणु0, 0x28, "ET_Custom_Force_Data"पूर्ण,
        अणु0, 0x30, "ET_Square"पूर्ण,
        अणु0, 0x31, "ET_Sine"पूर्ण,
        अणु0, 0x32, "ET_Triangle"पूर्ण,
        अणु0, 0x33, "ET_Sawtooth_Up"पूर्ण,
        अणु0, 0x34, "ET_Sawtooth_Down"पूर्ण,
        अणु0, 0x40, "ET_Spring"पूर्ण,
        अणु0, 0x41, "ET_Damper"पूर्ण,
        अणु0, 0x42, "ET_Inertia"पूर्ण,
        अणु0, 0x43, "ET_Friction"पूर्ण,
      अणु0, 0x50, "Duration"पूर्ण,
      अणु0, 0x51, "Sample_Period"पूर्ण,
      अणु0, 0x52, "Gain"पूर्ण,
      अणु0, 0x53, "Trigger_Button"पूर्ण,
      अणु0, 0x54, "Trigger_Repeat_Interval"पूर्ण,
      अणु0, 0x55, "Axes_Enable"पूर्ण,
        अणु0, 0x56, "Direction_Enable"पूर्ण,
      अणु0, 0x57, "Direction"पूर्ण,
      अणु0, 0x58, "Type_Specific_Block_Offset"पूर्ण,
        अणु0, 0x59, "Block_Type"पूर्ण,
        अणु0, 0x5A, "Set_Envelope_Report"पूर्ण,
          अणु0, 0x5B, "Attack_Level"पूर्ण,
          अणु0, 0x5C, "Attack_Time"पूर्ण,
          अणु0, 0x5D, "Fade_Level"पूर्ण,
          अणु0, 0x5E, "Fade_Time"पूर्ण,
        अणु0, 0x5F, "Set_Condition_Report"पूर्ण,
        अणु0, 0x60, "CP_Offset"पूर्ण,
        अणु0, 0x61, "Positive_Coefficient"पूर्ण,
        अणु0, 0x62, "Negative_Coefficient"पूर्ण,
        अणु0, 0x63, "Positive_Saturation"पूर्ण,
        अणु0, 0x64, "Negative_Saturation"पूर्ण,
        अणु0, 0x65, "Dead_Band"पूर्ण,
      अणु0, 0x66, "Download_Force_Sample"पूर्ण,
      अणु0, 0x67, "Isoch_Custom_Force_Enable"पूर्ण,
      अणु0, 0x68, "Custom_Force_Data_Report"पूर्ण,
        अणु0, 0x69, "Custom_Force_Data"पूर्ण,
        अणु0, 0x6A, "Custom_Force_Vendor_Defined_Data"पूर्ण,
      अणु0, 0x6B, "Set_Custom_Force_Report"पूर्ण,
        अणु0, 0x6C, "Custom_Force_Data_Offset"पूर्ण,
        अणु0, 0x6D, "Sample_Count"पूर्ण,
      अणु0, 0x6E, "Set_Periodic_Report"पूर्ण,
        अणु0, 0x6F, "Offset"पूर्ण,
        अणु0, 0x70, "Magnitude"पूर्ण,
        अणु0, 0x71, "Phase"पूर्ण,
        अणु0, 0x72, "Period"पूर्ण,
      अणु0, 0x73, "Set_Constant_Force_Report"पूर्ण,
        अणु0, 0x74, "Set_Ramp_Force_Report"पूर्ण,
        अणु0, 0x75, "Ramp_Start"पूर्ण,
        अणु0, 0x76, "Ramp_End"पूर्ण,
      अणु0, 0x77, "Effect_Operation_Report"पूर्ण,
        अणु0, 0x78, "Effect_Operation"पूर्ण,
          अणु0, 0x79, "Op_Effect_Start"पूर्ण,
          अणु0, 0x7A, "Op_Effect_Start_Solo"पूर्ण,
          अणु0, 0x7B, "Op_Effect_Stop"पूर्ण,
          अणु0, 0x7C, "Loop_Count"पूर्ण,
      अणु0, 0x7D, "Device_Gain_Report"पूर्ण,
        अणु0, 0x7E, "Device_Gain"पूर्ण,
    अणु0, 0x7F, "PID_Pool_Report"पूर्ण,
      अणु0, 0x80, "RAM_Pool_Size"पूर्ण,
      अणु0, 0x81, "ROM_Pool_Size"पूर्ण,
      अणु0, 0x82, "ROM_Effect_Block_Count"पूर्ण,
      अणु0, 0x83, "Simultaneous_Effects_Max"पूर्ण,
      अणु0, 0x84, "Pool_Alignment"पूर्ण,
    अणु0, 0x85, "PID_Pool_Move_Report"पूर्ण,
      अणु0, 0x86, "Move_Source"पूर्ण,
      अणु0, 0x87, "Move_Destination"पूर्ण,
      अणु0, 0x88, "Move_Length"पूर्ण,
    अणु0, 0x89, "PID_Block_Load_Report"पूर्ण,
      अणु0, 0x8B, "Block_Load_Status"पूर्ण,
      अणु0, 0x8C, "Block_Load_Success"पूर्ण,
      अणु0, 0x8D, "Block_Load_Full"पूर्ण,
      अणु0, 0x8E, "Block_Load_Error"पूर्ण,
      अणु0, 0x8F, "Block_Handle"पूर्ण,
      अणु0, 0x90, "PID_Block_Free_Report"पूर्ण,
      अणु0, 0x91, "Type_Specific_Block_Handle"पूर्ण,
    अणु0, 0x92, "PID_State_Report"पूर्ण,
      अणु0, 0x94, "Effect_Playing"पूर्ण,
      अणु0, 0x95, "PID_Device_Control_Report"पूर्ण,
        अणु0, 0x96, "PID_Device_Control"पूर्ण,
        अणु0, 0x97, "DC_Enable_Actuators"पूर्ण,
        अणु0, 0x98, "DC_Disable_Actuators"पूर्ण,
        अणु0, 0x99, "DC_Stop_All_Effects"पूर्ण,
        अणु0, 0x9A, "DC_Device_Reset"पूर्ण,
        अणु0, 0x9B, "DC_Device_Pause"पूर्ण,
        अणु0, 0x9C, "DC_Device_Continue"पूर्ण,
      अणु0, 0x9F, "Device_Paused"पूर्ण,
      अणु0, 0xA0, "Actuators_Enabled"पूर्ण,
      अणु0, 0xA4, "Safety_Switch"पूर्ण,
      अणु0, 0xA5, "Actuator_Override_Switch"पूर्ण,
      अणु0, 0xA6, "Actuator_Power"पूर्ण,
    अणु0, 0xA7, "Start_Delay"पूर्ण,
    अणु0, 0xA8, "Parameter_Block_Size"पूर्ण,
    अणु0, 0xA9, "Device_Managed_Pool"पूर्ण,
    अणु0, 0xAA, "Shared_Parameter_Blocks"पूर्ण,
    अणु0, 0xAB, "Create_New_Effect_Report"पूर्ण,
    अणु0, 0xAC, "RAM_Pool_Available"पूर्ण,
  अणु  0x20, 0, "Sensor" पूर्ण,
    अणु 0x20, 0x01, "Sensor" पूर्ण,
    अणु 0x20, 0x10, "Biometric" पूर्ण,
      अणु 0x20, 0x11, "BiometricHumanPresence" पूर्ण,
      अणु 0x20, 0x12, "BiometricHumanProximity" पूर्ण,
      अणु 0x20, 0x13, "BiometricHumanTouch" पूर्ण,
    अणु 0x20, 0x20, "Electrical" पूर्ण,
      अणु 0x20, 0x21, "ElectricalCapacitance" पूर्ण,
      अणु 0x20, 0x22, "ElectricalCurrent" पूर्ण,
      अणु 0x20, 0x23, "ElectricalPower" पूर्ण,
      अणु 0x20, 0x24, "ElectricalInductance" पूर्ण,
      अणु 0x20, 0x25, "ElectricalResistance" पूर्ण,
      अणु 0x20, 0x26, "ElectricalVoltage" पूर्ण,
      अणु 0x20, 0x27, "ElectricalPoteniometer" पूर्ण,
      अणु 0x20, 0x28, "ElectricalFrequency" पूर्ण,
      अणु 0x20, 0x29, "ElectricalPeriod" पूर्ण,
    अणु 0x20, 0x30, "Environmental" पूर्ण,
      अणु 0x20, 0x31, "EnvironmentalAtmosphericPressure" पूर्ण,
      अणु 0x20, 0x32, "EnvironmentalHumidity" पूर्ण,
      अणु 0x20, 0x33, "EnvironmentalTemperature" पूर्ण,
      अणु 0x20, 0x34, "EnvironmentalWindDirection" पूर्ण,
      अणु 0x20, 0x35, "EnvironmentalWindSpeed" पूर्ण,
    अणु 0x20, 0x40, "Light" पूर्ण,
      अणु 0x20, 0x41, "LightAmbientLight" पूर्ण,
      अणु 0x20, 0x42, "LightConsumerInfrared" पूर्ण,
    अणु 0x20, 0x50, "Location" पूर्ण,
      अणु 0x20, 0x51, "LocationBroadcast" पूर्ण,
      अणु 0x20, 0x52, "LocationDeadReckoning" पूर्ण,
      अणु 0x20, 0x53, "LocationGPS" पूर्ण,
      अणु 0x20, 0x54, "LocationLookup" पूर्ण,
      अणु 0x20, 0x55, "LocationOther" पूर्ण,
      अणु 0x20, 0x56, "LocationStatic" पूर्ण,
      अणु 0x20, 0x57, "LocationTriangulation" पूर्ण,
    अणु 0x20, 0x60, "Mechanical" पूर्ण,
      अणु 0x20, 0x61, "MechanicalBooleanSwitch" पूर्ण,
      अणु 0x20, 0x62, "MechanicalBooleanSwitchArray" पूर्ण,
      अणु 0x20, 0x63, "MechanicalMultivalueSwitch" पूर्ण,
      अणु 0x20, 0x64, "MechanicalForce" पूर्ण,
      अणु 0x20, 0x65, "MechanicalPressure" पूर्ण,
      अणु 0x20, 0x66, "MechanicalStrain" पूर्ण,
      अणु 0x20, 0x67, "MechanicalWeight" पूर्ण,
      अणु 0x20, 0x68, "MechanicalHapticVibrator" पूर्ण,
      अणु 0x20, 0x69, "MechanicalHallEffectSwitch" पूर्ण,
    अणु 0x20, 0x70, "Motion" पूर्ण,
      अणु 0x20, 0x71, "MotionAccelerometer1D" पूर्ण,
      अणु 0x20, 0x72, "MotionAccelerometer2D" पूर्ण,
      अणु 0x20, 0x73, "MotionAccelerometer3D" पूर्ण,
      अणु 0x20, 0x74, "MotionGyrometer1D" पूर्ण,
      अणु 0x20, 0x75, "MotionGyrometer2D" पूर्ण,
      अणु 0x20, 0x76, "MotionGyrometer3D" पूर्ण,
      अणु 0x20, 0x77, "MotionMotionDetector" पूर्ण,
      अणु 0x20, 0x78, "MotionSpeedometer" पूर्ण,
      अणु 0x20, 0x79, "MotionAccelerometer" पूर्ण,
      अणु 0x20, 0x7A, "MotionGyrometer" पूर्ण,
    अणु 0x20, 0x80, "Orientation" पूर्ण,
      अणु 0x20, 0x81, "OrientationCompass1D" पूर्ण,
      अणु 0x20, 0x82, "OrientationCompass2D" पूर्ण,
      अणु 0x20, 0x83, "OrientationCompass3D" पूर्ण,
      अणु 0x20, 0x84, "OrientationInclinometer1D" पूर्ण,
      अणु 0x20, 0x85, "OrientationInclinometer2D" पूर्ण,
      अणु 0x20, 0x86, "OrientationInclinometer3D" पूर्ण,
      अणु 0x20, 0x87, "OrientationDistance1D" पूर्ण,
      अणु 0x20, 0x88, "OrientationDistance2D" पूर्ण,
      अणु 0x20, 0x89, "OrientationDistance3D" पूर्ण,
      अणु 0x20, 0x8A, "OrientationDeviceOrientation" पूर्ण,
      अणु 0x20, 0x8B, "OrientationCompass" पूर्ण,
      अणु 0x20, 0x8C, "OrientationInclinometer" पूर्ण,
      अणु 0x20, 0x8D, "OrientationDistance" पूर्ण,
    अणु 0x20, 0x90, "Scanner" पूर्ण,
      अणु 0x20, 0x91, "ScannerBarcode" पूर्ण,
      अणु 0x20, 0x91, "ScannerRFID" पूर्ण,
      अणु 0x20, 0x91, "ScannerNFC" पूर्ण,
    अणु 0x20, 0xA0, "Time" पूर्ण,
      अणु 0x20, 0xA1, "TimeAlarmTimer" पूर्ण,
      अणु 0x20, 0xA2, "TimeRealTimeClock" पूर्ण,
    अणु 0x20, 0xE0, "Other" पूर्ण,
      अणु 0x20, 0xE1, "OtherCustom" पूर्ण,
      अणु 0x20, 0xE2, "OtherGeneric" पूर्ण,
      अणु 0x20, 0xE3, "OtherGenericEnumerator" पूर्ण,
  अणु 0x84, 0, "Power Device" पूर्ण,
    अणु 0x84, 0x02, "PresentStatus" पूर्ण,
    अणु 0x84, 0x03, "ChangeStatus" पूर्ण,
    अणु 0x84, 0x04, "UPS" पूर्ण,
    अणु 0x84, 0x05, "PowerSupply" पूर्ण,
    अणु 0x84, 0x10, "BatterySystem" पूर्ण,
    अणु 0x84, 0x11, "BatterySystemID" पूर्ण,
    अणु 0x84, 0x12, "Battery" पूर्ण,
    अणु 0x84, 0x13, "BatteryID" पूर्ण,
    अणु 0x84, 0x14, "Charger" पूर्ण,
    अणु 0x84, 0x15, "ChargerID" पूर्ण,
    अणु 0x84, 0x16, "PowerConverter" पूर्ण,
    अणु 0x84, 0x17, "PowerConverterID" पूर्ण,
    अणु 0x84, 0x18, "OutletSystem" पूर्ण,
    अणु 0x84, 0x19, "OutletSystemID" पूर्ण,
    अणु 0x84, 0x1a, "Input" पूर्ण,
    अणु 0x84, 0x1b, "InputID" पूर्ण,
    अणु 0x84, 0x1c, "Output" पूर्ण,
    अणु 0x84, 0x1d, "OutputID" पूर्ण,
    अणु 0x84, 0x1e, "Flow" पूर्ण,
    अणु 0x84, 0x1f, "FlowID" पूर्ण,
    अणु 0x84, 0x20, "Outlet" पूर्ण,
    अणु 0x84, 0x21, "OutletID" पूर्ण,
    अणु 0x84, 0x22, "Gang" पूर्ण,
    अणु 0x84, 0x24, "PowerSummary" पूर्ण,
    अणु 0x84, 0x25, "PowerSummaryID" पूर्ण,
    अणु 0x84, 0x30, "Voltage" पूर्ण,
    अणु 0x84, 0x31, "Current" पूर्ण,
    अणु 0x84, 0x32, "Frequency" पूर्ण,
    अणु 0x84, 0x33, "ApparentPower" पूर्ण,
    अणु 0x84, 0x35, "PercentLoad" पूर्ण,
    अणु 0x84, 0x40, "ConfigVoltage" पूर्ण,
    अणु 0x84, 0x41, "ConfigCurrent" पूर्ण,
    अणु 0x84, 0x43, "ConfigApparentPower" पूर्ण,
    अणु 0x84, 0x53, "LowVoltageTransfer" पूर्ण,
    अणु 0x84, 0x54, "HighVoltageTransfer" पूर्ण,
    अणु 0x84, 0x56, "DelayBeforeStartup" पूर्ण,
    अणु 0x84, 0x57, "DelayBeforeShutdown" पूर्ण,
    अणु 0x84, 0x58, "Test" पूर्ण,
    अणु 0x84, 0x5a, "AudibleAlarmControl" पूर्ण,
    अणु 0x84, 0x60, "Present" पूर्ण,
    अणु 0x84, 0x61, "Good" पूर्ण,
    अणु 0x84, 0x62, "InternalFailure" पूर्ण,
    अणु 0x84, 0x65, "Overload" पूर्ण,
    अणु 0x84, 0x66, "OverCharged" पूर्ण,
    अणु 0x84, 0x67, "OverTemperature" पूर्ण,
    अणु 0x84, 0x68, "ShutdownRequested" पूर्ण,
    अणु 0x84, 0x69, "ShutdownImminent" पूर्ण,
    अणु 0x84, 0x6b, "SwitchOn/Off" पूर्ण,
    अणु 0x84, 0x6c, "Switchable" पूर्ण,
    अणु 0x84, 0x6d, "Used" पूर्ण,
    अणु 0x84, 0x6e, "Boost" पूर्ण,
    अणु 0x84, 0x73, "CommunicationLost" पूर्ण,
    अणु 0x84, 0xfd, "iManufacturer" पूर्ण,
    अणु 0x84, 0xfe, "iProduct" पूर्ण,
    अणु 0x84, 0xff, "iSerialNumber" पूर्ण,
  अणु 0x85, 0, "Battery System" पूर्ण,
    अणु 0x85, 0x01, "SMBBatteryMode" पूर्ण,
    अणु 0x85, 0x02, "SMBBatteryStatus" पूर्ण,
    अणु 0x85, 0x03, "SMBAlarmWarning" पूर्ण,
    अणु 0x85, 0x04, "SMBChargerMode" पूर्ण,
    अणु 0x85, 0x05, "SMBChargerStatus" पूर्ण,
    अणु 0x85, 0x06, "SMBChargerSpecInfo" पूर्ण,
    अणु 0x85, 0x07, "SMBSelectorState" पूर्ण,
    अणु 0x85, 0x08, "SMBSelectorPresets" पूर्ण,
    अणु 0x85, 0x09, "SMBSelectorInfo" पूर्ण,
    अणु 0x85, 0x29, "RemainingCapacityLimit" पूर्ण,
    अणु 0x85, 0x2c, "CapacityMode" पूर्ण,
    अणु 0x85, 0x42, "BelowRemainingCapacityLimit" पूर्ण,
    अणु 0x85, 0x44, "Charging" पूर्ण,
    अणु 0x85, 0x45, "Discharging" पूर्ण,
    अणु 0x85, 0x4b, "NeedReplacement" पूर्ण,
    अणु 0x85, 0x65, "AbsoluteStateOfCharge" पूर्ण,
    अणु 0x85, 0x66, "RemainingCapacity" पूर्ण,
    अणु 0x85, 0x68, "RunTimeToEmpty" पूर्ण,
    अणु 0x85, 0x6a, "AverageTimeToFull" पूर्ण,
    अणु 0x85, 0x83, "DesignCapacity" पूर्ण,
    अणु 0x85, 0x85, "ManufacturerDate" पूर्ण,
    अणु 0x85, 0x89, "iDeviceChemistry" पूर्ण,
    अणु 0x85, 0x8b, "Rechargeable" पूर्ण,
    अणु 0x85, 0x8f, "iOEMInformation" पूर्ण,
    अणु 0x85, 0x8d, "CapacityGranularity1" पूर्ण,
    अणु 0x85, 0xd0, "ACPresent" पूर्ण,
  /* pages 0xff00 to 0xffff are venकरोr-specअगरic */
  अणु 0xffff, 0, "Vendor-specific-FF" पूर्ण,
  अणु 0, 0, शून्य पूर्ण
पूर्ण;

/* Either output directly पूर्णांकo simple seq_file, or (अगर f == शून्य)
 * allocate a separate buffer that will then be passed to the 'events'
 * ringbuffer.
 *
 * This is because these functions can be called both क्रम "one-shot"
 * "rdesc" जबतक resolving, or क्रम blocking "events".
 *
 * This holds both क्रम resolv_usage_page() and hid_resolv_usage().
 */
अटल अक्षर *resolv_usage_page(अचिन्हित page, काष्ठा seq_file *f) अणु
	स्थिर काष्ठा hid_usage_entry *p;
	अक्षर *buf = शून्य;

	अगर (!f) अणु
		buf = kzalloc(HID_DEBUG_बफ_मानE, GFP_ATOMIC);
		अगर (!buf)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (p = hid_usage_table; p->description; p++)
		अगर (p->page == page) अणु
			अगर (!f) अणु
				snम_लिखो(buf, HID_DEBUG_बफ_मानE, "%s",
						p->description);
				वापस buf;
			पूर्ण
			अन्यथा अणु
				seq_म_लिखो(f, "%s", p->description);
				वापस शून्य;
			पूर्ण
		पूर्ण
	अगर (!f)
		snम_लिखो(buf, HID_DEBUG_बफ_मानE, "%04x", page);
	अन्यथा
		seq_म_लिखो(f, "%04x", page);
	वापस buf;
पूर्ण

अक्षर *hid_resolv_usage(अचिन्हित usage, काष्ठा seq_file *f) अणु
	स्थिर काष्ठा hid_usage_entry *p;
	अक्षर *buf = शून्य;
	पूर्णांक len = 0;

	buf = resolv_usage_page(usage >> 16, f);
	अगर (IS_ERR(buf)) अणु
		pr_err("error allocating HID debug buffer\n");
		वापस शून्य;
	पूर्ण


	अगर (!f) अणु
		len = म_माप(buf);
		snम_लिखो(buf+len, max(0, HID_DEBUG_बफ_मानE - len), ".");
		len++;
	पूर्ण
	अन्यथा अणु
		seq_म_लिखो(f, ".");
	पूर्ण
	क्रम (p = hid_usage_table; p->description; p++)
		अगर (p->page == (usage >> 16)) अणु
			क्रम(++p; p->description && p->usage != 0; p++)
				अगर (p->usage == (usage & 0xffff)) अणु
					अगर (!f)
						snम_लिखो(buf + len,
							max(0,HID_DEBUG_बफ_मानE - len - 1),
							"%s", p->description);
					अन्यथा
						seq_म_लिखो(f,
							"%s",
							p->description);
					वापस buf;
				पूर्ण
			अवरोध;
		पूर्ण
	अगर (!f)
		snम_लिखो(buf + len, max(0, HID_DEBUG_बफ_मानE - len - 1),
				"%04x", usage & 0xffff);
	अन्यथा
		seq_म_लिखो(f, "%04x", usage & 0xffff);
	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(hid_resolv_usage);

अटल व्योम tab(पूर्णांक n, काष्ठा seq_file *f) अणु
	seq_म_लिखो(f, "%*s", n, "");
पूर्ण

व्योम hid_dump_field(काष्ठा hid_field *field, पूर्णांक n, काष्ठा seq_file *f) अणु
	पूर्णांक j;

	अगर (field->physical) अणु
		tab(n, f);
		seq_म_लिखो(f, "Physical(");
		hid_resolv_usage(field->physical, f); seq_म_लिखो(f, ")\n");
	पूर्ण
	अगर (field->logical) अणु
		tab(n, f);
		seq_म_लिखो(f, "Logical(");
		hid_resolv_usage(field->logical, f); seq_म_लिखो(f, ")\n");
	पूर्ण
	अगर (field->application) अणु
		tab(n, f);
		seq_म_लिखो(f, "Application(");
		hid_resolv_usage(field->application, f); seq_म_लिखो(f, ")\n");
	पूर्ण
	tab(n, f); seq_म_लिखो(f, "Usage(%d)\n", field->maxusage);
	क्रम (j = 0; j < field->maxusage; j++) अणु
		tab(n+2, f); hid_resolv_usage(field->usage[j].hid, f); seq_म_लिखो(f, "\n");
	पूर्ण
	अगर (field->logical_minimum != field->logical_maximum) अणु
		tab(n, f); seq_म_लिखो(f, "Logical Minimum(%d)\n", field->logical_minimum);
		tab(n, f); seq_म_लिखो(f, "Logical Maximum(%d)\n", field->logical_maximum);
	पूर्ण
	अगर (field->physical_minimum != field->physical_maximum) अणु
		tab(n, f); seq_म_लिखो(f, "Physical Minimum(%d)\n", field->physical_minimum);
		tab(n, f); seq_म_लिखो(f, "Physical Maximum(%d)\n", field->physical_maximum);
	पूर्ण
	अगर (field->unit_exponent) अणु
		tab(n, f); seq_म_लिखो(f, "Unit Exponent(%d)\n", field->unit_exponent);
	पूर्ण
	अगर (field->unit) अणु
		अटल स्थिर अक्षर *प्रणालीs[5] = अणु "None", "SI Linear", "SI Rotation", "English Linear", "English Rotation" पूर्ण;
		अटल स्थिर अक्षर *units[5][8] = अणु
			अणु "None", "None", "None", "None", "None", "None", "None", "None" पूर्ण,
			अणु "None", "Centimeter", "Gram", "Seconds", "Kelvin",     "Ampere", "Candela", "None" पूर्ण,
			अणु "None", "Radians",    "Gram", "Seconds", "Kelvin",     "Ampere", "Candela", "None" पूर्ण,
			अणु "None", "Inch",       "Slug", "Seconds", "Fahrenheit", "Ampere", "Candela", "None" पूर्ण,
			अणु "None", "Degrees",    "Slug", "Seconds", "Fahrenheit", "Ampere", "Candela", "None" पूर्ण
		पूर्ण;

		पूर्णांक i;
		पूर्णांक sys;
                __u32 data = field->unit;

		/* First nibble tells us which प्रणाली we're in. */
		sys = data & 0xf;
		data >>= 4;

		अगर(sys > 4) अणु
			tab(n, f); seq_म_लिखो(f, "Unit(Invalid)\n");
		पूर्ण
		अन्यथा अणु
			पूर्णांक earlier_unit = 0;

			tab(n, f); seq_म_लिखो(f, "Unit(%s : ", प्रणालीs[sys]);

			क्रम (i=1 ; i<माप(__u32)*2 ; i++) अणु
				अक्षर nibble = data & 0xf;
				data >>= 4;
				अगर (nibble != 0) अणु
					अगर(earlier_unit++ > 0)
						seq_म_लिखो(f, "*");
					seq_म_लिखो(f, "%s", units[sys][i]);
					अगर(nibble != 1) अणु
						/* This is a _चिन्हित_ nibble(!) */

						पूर्णांक val = nibble & 0x7;
						अगर(nibble & 0x08)
							val = -((0x7 & ~val) +1);
						seq_म_लिखो(f, "^%d", val);
					पूर्ण
				पूर्ण
			पूर्ण
			seq_म_लिखो(f, ")\n");
		पूर्ण
	पूर्ण
	tab(n, f); seq_म_लिखो(f, "Report Size(%u)\n", field->report_size);
	tab(n, f); seq_म_लिखो(f, "Report Count(%u)\n", field->report_count);
	tab(n, f); seq_म_लिखो(f, "Report Offset(%u)\n", field->report_offset);

	tab(n, f); seq_म_लिखो(f, "Flags( ");
	j = field->flags;
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_CONSTANT & j ? "Constant " : "");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_VARIABLE & j ? "Variable " : "Array ");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_RELATIVE & j ? "Relative " : "Absolute ");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_WRAP & j ? "Wrap " : "");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_NONLINEAR & j ? "NonLinear " : "");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_NO_PREFERRED & j ? "NoPreferredState " : "");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_शून्य_STATE & j ? "NullState " : "");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_VOLATILE & j ? "Volatile " : "");
	seq_म_लिखो(f, "%s", HID_MAIN_ITEM_BUFFERED_BYTE & j ? "BufferedByte " : "");
	seq_म_लिखो(f, ")\n");
पूर्ण
EXPORT_SYMBOL_GPL(hid_dump_field);

व्योम hid_dump_device(काष्ठा hid_device *device, काष्ठा seq_file *f)
अणु
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	काष्ठा hid_report *report;
	काष्ठा list_head *list;
	अचिन्हित i,k;
	अटल स्थिर अक्षर *table[] = अणु"INPUT", "OUTPUT", "FEATURE"पूर्ण;

	क्रम (i = 0; i < HID_REPORT_TYPES; i++) अणु
		report_क्रमागत = device->report_क्रमागत + i;
		list = report_क्रमागत->report_list.next;
		जबतक (list != &report_क्रमागत->report_list) अणु
			report = (काष्ठा hid_report *) list;
			tab(2, f);
			seq_म_लिखो(f, "%s", table[i]);
			अगर (report->id)
				seq_म_लिखो(f, "(%d)", report->id);
			seq_म_लिखो(f, "[%s]", table[report->type]);
			seq_म_लिखो(f, "\n");
			क्रम (k = 0; k < report->maxfield; k++) अणु
				tab(4, f);
				seq_म_लिखो(f, "Field(%d)\n", k);
				hid_dump_field(report->field[k], 6, f);
			पूर्ण
			list = list->next;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hid_dump_device);

/* enqueue string to 'events' ring buffer */
व्योम hid_debug_event(काष्ठा hid_device *hdev, अक्षर *buf)
अणु
	काष्ठा hid_debug_list *list;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hdev->debug_list_lock, flags);
	list_क्रम_each_entry(list, &hdev->debug_list, node)
		kfअगरo_in(&list->hid_debug_fअगरo, buf, म_माप(buf));
	spin_unlock_irqrestore(&hdev->debug_list_lock, flags);

	wake_up_पूर्णांकerruptible(&hdev->debug_रुको);
पूर्ण
EXPORT_SYMBOL_GPL(hid_debug_event);

व्योम hid_dump_report(काष्ठा hid_device *hid, पूर्णांक type, u8 *data,
		पूर्णांक size)
अणु
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	अक्षर *buf;
	अचिन्हित पूर्णांक i;

	buf = kदो_स्मृति(HID_DEBUG_बफ_मानE, GFP_ATOMIC);

	अगर (!buf)
		वापस;

	report_क्रमागत = hid->report_क्रमागत + type;

	/* dump the report */
	snम_लिखो(buf, HID_DEBUG_बफ_मानE - 1,
			"\nreport (size %u) (%snumbered) = ", size,
			report_क्रमागत->numbered ? "" : "un");
	hid_debug_event(hid, buf);

	क्रम (i = 0; i < size; i++) अणु
		snम_लिखो(buf, HID_DEBUG_बफ_मानE - 1,
				" %02x", data[i]);
		hid_debug_event(hid, buf);
	पूर्ण
	hid_debug_event(hid, "\n");
	kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL_GPL(hid_dump_report);

व्योम hid_dump_input(काष्ठा hid_device *hdev, काष्ठा hid_usage *usage, __s32 value)
अणु
	अक्षर *buf;
	पूर्णांक len;

	buf = hid_resolv_usage(usage->hid, शून्य);
	अगर (!buf)
		वापस;
	len = म_माप(buf);
	snम_लिखो(buf + len, HID_DEBUG_बफ_मानE - len - 1, " = %d\n", value);

	hid_debug_event(hdev, buf);

	kमुक्त(buf);
	wake_up_पूर्णांकerruptible(&hdev->debug_रुको);
पूर्ण
EXPORT_SYMBOL_GPL(hid_dump_input);

अटल स्थिर अक्षर *events[EV_MAX + 1] = अणु
	[EV_SYN] = "Sync",			[EV_KEY] = "Key",
	[EV_REL] = "Relative",			[EV_ABS] = "Absolute",
	[EV_MSC] = "Misc",			[EV_LED] = "LED",
	[EV_SND] = "Sound",			[EV_REP] = "Repeat",
	[EV_FF] = "ForceFeedback",		[EV_PWR] = "Power",
	[EV_FF_STATUS] = "ForceFeedbackStatus",
पूर्ण;

अटल स्थिर अक्षर *syncs[3] = अणु
	[SYN_REPORT] = "Report",		[SYN_CONFIG] = "Config",
	[SYN_MT_REPORT] = "MT Report",
पूर्ण;

अटल स्थिर अक्षर *keys[KEY_MAX + 1] = अणु
	[KEY_RESERVED] = "Reserved",		[KEY_ESC] = "Esc",
	[KEY_1] = "1",				[KEY_2] = "2",
	[KEY_3] = "3",				[KEY_4] = "4",
	[KEY_5] = "5",				[KEY_6] = "6",
	[KEY_7] = "7",				[KEY_8] = "8",
	[KEY_9] = "9",				[KEY_0] = "0",
	[KEY_MINUS] = "Minus",			[KEY_EQUAL] = "Equal",
	[KEY_BACKSPACE] = "Backspace",		[KEY_TAB] = "Tab",
	[KEY_Q] = "Q",				[KEY_W] = "W",
	[KEY_E] = "E",				[KEY_R] = "R",
	[KEY_T] = "T",				[KEY_Y] = "Y",
	[KEY_U] = "U",				[KEY_I] = "I",
	[KEY_O] = "O",				[KEY_P] = "P",
	[KEY_LEFTBRACE] = "LeftBrace",		[KEY_RIGHTBRACE] = "RightBrace",
	[KEY_ENTER] = "Enter",			[KEY_LEFTCTRL] = "LeftControl",
	[KEY_A] = "A",				[KEY_S] = "S",
	[KEY_D] = "D",				[KEY_F] = "F",
	[KEY_G] = "G",				[KEY_H] = "H",
	[KEY_J] = "J",				[KEY_K] = "K",
	[KEY_L] = "L",				[KEY_SEMICOLON] = "Semicolon",
	[KEY_APOSTROPHE] = "Apostrophe",	[KEY_GRAVE] = "Grave",
	[KEY_LEFTSHIFT] = "LeftShift",		[KEY_BACKSLASH] = "BackSlash",
	[KEY_Z] = "Z",				[KEY_X] = "X",
	[KEY_C] = "C",				[KEY_V] = "V",
	[KEY_B] = "B",				[KEY_N] = "N",
	[KEY_M] = "M",				[KEY_COMMA] = "Comma",
	[KEY_DOT] = "Dot",			[KEY_SLASH] = "Slash",
	[KEY_RIGHTSHIFT] = "RightShift",	[KEY_KPASTERISK] = "KPAsterisk",
	[KEY_LEFTALT] = "LeftAlt",		[KEY_SPACE] = "Space",
	[KEY_CAPSLOCK] = "CapsLock",		[KEY_F1] = "F1",
	[KEY_F2] = "F2",			[KEY_F3] = "F3",
	[KEY_F4] = "F4",			[KEY_F5] = "F5",
	[KEY_F6] = "F6",			[KEY_F7] = "F7",
	[KEY_F8] = "F8",			[KEY_F9] = "F9",
	[KEY_F10] = "F10",			[KEY_NUMLOCK] = "NumLock",
	[KEY_SCROLLLOCK] = "ScrollLock",	[KEY_KP7] = "KP7",
	[KEY_KP8] = "KP8",			[KEY_KP9] = "KP9",
	[KEY_KPMINUS] = "KPMinus",		[KEY_KP4] = "KP4",
	[KEY_KP5] = "KP5",			[KEY_KP6] = "KP6",
	[KEY_KPPLUS] = "KPPlus",		[KEY_KP1] = "KP1",
	[KEY_KP2] = "KP2",			[KEY_KP3] = "KP3",
	[KEY_KP0] = "KP0",			[KEY_KPDOT] = "KPDot",
	[KEY_ZENKAKUHANKAKU] = "Zenkaku/Hankaku", [KEY_102ND] = "102nd",
	[KEY_F11] = "F11",			[KEY_F12] = "F12",
	[KEY_RO] = "RO",			[KEY_KATAKANA] = "Katakana",
	[KEY_HIRAGANA] = "HIRAGANA",		[KEY_HENKAN] = "Henkan",
	[KEY_KATAKANAHIRAGANA] = "Katakana/Hiragana", [KEY_MUHENKAN] = "Muhenkan",
	[KEY_KPJPCOMMA] = "KPJpComma",		[KEY_KPENTER] = "KPEnter",
	[KEY_RIGHTCTRL] = "RightCtrl",		[KEY_KPSLASH] = "KPSlash",
	[KEY_SYSRQ] = "SysRq",			[KEY_RIGHTALT] = "RightAlt",
	[KEY_LINEFEED] = "LineFeed",		[KEY_HOME] = "Home",
	[KEY_UP] = "Up",			[KEY_PAGEUP] = "PageUp",
	[KEY_LEFT] = "Left",			[KEY_RIGHT] = "Right",
	[KEY_END] = "End",			[KEY_DOWN] = "Down",
	[KEY_PAGEDOWN] = "PageDown",		[KEY_INSERT] = "Insert",
	[KEY_DELETE] = "Delete",		[KEY_MACRO] = "Macro",
	[KEY_MUTE] = "Mute",			[KEY_VOLUMEDOWN] = "VolumeDown",
	[KEY_VOLUMEUP] = "VolumeUp",		[KEY_POWER] = "Power",
	[KEY_KPEQUAL] = "KPEqual",		[KEY_KPPLUSMINUS] = "KPPlusMinus",
	[KEY_PAUSE] = "Pause",			[KEY_KPCOMMA] = "KPComma",
	[KEY_HANGUEL] = "Hangeul",		[KEY_HANJA] = "Hanja",
	[KEY_YEN] = "Yen",			[KEY_LEFTMETA] = "LeftMeta",
	[KEY_RIGHTMETA] = "RightMeta",		[KEY_COMPOSE] = "Compose",
	[KEY_STOP] = "Stop",			[KEY_AGAIN] = "Again",
	[KEY_PROPS] = "Props",			[KEY_UNDO] = "Undo",
	[KEY_FRONT] = "Front",			[KEY_COPY] = "Copy",
	[KEY_OPEN] = "Open",			[KEY_PASTE] = "Paste",
	[KEY_FIND] = "Find",			[KEY_CUT] = "Cut",
	[KEY_HELP] = "Help",			[KEY_MENU] = "Menu",
	[KEY_CALC] = "Calc",			[KEY_SETUP] = "Setup",
	[KEY_SLEEP] = "Sleep",			[KEY_WAKEUP] = "WakeUp",
	[KEY_खाता] = "File",			[KEY_SENDखाता] = "SendFile",
	[KEY_DELETEखाता] = "DeleteFile",	[KEY_XFER] = "X-fer",
	[KEY_PROG1] = "Prog1",			[KEY_PROG2] = "Prog2",
	[KEY_WWW] = "WWW",			[KEY_MSDOS] = "MSDOS",
	[KEY_COFFEE] = "Coffee",		[KEY_ROTATE_DISPLAY] = "RotateDisplay",
	[KEY_CYCLEWINDOWS] = "CycleWindows",	[KEY_MAIL] = "Mail",
	[KEY_BOOKMARKS] = "Bookmarks",		[KEY_COMPUTER] = "Computer",
	[KEY_BACK] = "Back",			[KEY_FORWARD] = "Forward",
	[KEY_CLOSECD] = "CloseCD",		[KEY_EJECTCD] = "EjectCD",
	[KEY_EJECTCLOSECD] = "EjectCloseCD",	[KEY_NEXTSONG] = "NextSong",
	[KEY_PLAYPAUSE] = "PlayPause",		[KEY_PREVIOUSSONG] = "PreviousSong",
	[KEY_STOPCD] = "StopCD",		[KEY_RECORD] = "Record",
	[KEY_REWIND] = "Rewind",		[KEY_PHONE] = "Phone",
	[KEY_ISO] = "ISOKey",			[KEY_CONFIG] = "Config",
	[KEY_HOMEPAGE] = "HomePage",		[KEY_REFRESH] = "Refresh",
	[KEY_EXIT] = "Exit",			[KEY_MOVE] = "Move",
	[KEY_EDIT] = "Edit",			[KEY_SCROLLUP] = "ScrollUp",
	[KEY_SCROLLDOWN] = "ScrollDown",	[KEY_KPLEFTPAREN] = "KPLeftParenthesis",
	[KEY_KPRIGHTPAREN] = "KPRightParenthesis", [KEY_NEW] = "New",
	[KEY_REDO] = "Redo",			[KEY_F13] = "F13",
	[KEY_F14] = "F14",			[KEY_F15] = "F15",
	[KEY_F16] = "F16",			[KEY_F17] = "F17",
	[KEY_F18] = "F18",			[KEY_F19] = "F19",
	[KEY_F20] = "F20",			[KEY_F21] = "F21",
	[KEY_F22] = "F22",			[KEY_F23] = "F23",
	[KEY_F24] = "F24",			[KEY_PLAYCD] = "PlayCD",
	[KEY_PAUSECD] = "PauseCD",		[KEY_PROG3] = "Prog3",
	[KEY_PROG4] = "Prog4",			[KEY_SUSPEND] = "Suspend",
	[KEY_CLOSE] = "Close",			[KEY_PLAY] = "Play",
	[KEY_FASTFORWARD] = "FastForward",	[KEY_BASSBOOST] = "BassBoost",
	[KEY_PRINT] = "Print",			[KEY_HP] = "HP",
	[KEY_CAMERA] = "Camera",		[KEY_SOUND] = "Sound",
	[KEY_QUESTION] = "Question",		[KEY_EMAIL] = "Email",
	[KEY_CHAT] = "Chat",			[KEY_SEARCH] = "Search",
	[KEY_CONNECT] = "Connect",		[KEY_FIन_अंकCE] = "Finance",
	[KEY_SPORT] = "Sport",			[KEY_SHOP] = "Shop",
	[KEY_ALTERASE] = "AlternateErase",	[KEY_CANCEL] = "Cancel",
	[KEY_BRIGHTNESSDOWN] = "BrightnessDown", [KEY_BRIGHTNESSUP] = "BrightnessUp",
	[KEY_MEDIA] = "Media",			[KEY_UNKNOWN] = "Unknown",
	[BTN_DPAD_UP] = "BtnDPadUp",		[BTN_DPAD_DOWN] = "BtnDPadDown",
	[BTN_DPAD_LEFT] = "BtnDPadLeft",	[BTN_DPAD_RIGHT] = "BtnDPadRight",
	[BTN_0] = "Btn0",			[BTN_1] = "Btn1",
	[BTN_2] = "Btn2",			[BTN_3] = "Btn3",
	[BTN_4] = "Btn4",			[BTN_5] = "Btn5",
	[BTN_6] = "Btn6",			[BTN_7] = "Btn7",
	[BTN_8] = "Btn8",			[BTN_9] = "Btn9",
	[BTN_LEFT] = "LeftBtn",			[BTN_RIGHT] = "RightBtn",
	[BTN_MIDDLE] = "MiddleBtn",		[BTN_SIDE] = "SideBtn",
	[BTN_EXTRA] = "ExtraBtn",		[BTN_FORWARD] = "ForwardBtn",
	[BTN_BACK] = "BackBtn",			[BTN_TASK] = "TaskBtn",
	[BTN_TRIGGER] = "Trigger",		[BTN_THUMB] = "ThumbBtn",
	[BTN_THUMB2] = "ThumbBtn2",		[BTN_TOP] = "TopBtn",
	[BTN_TOP2] = "TopBtn2",			[BTN_PINKIE] = "PinkieBtn",
	[BTN_BASE] = "BaseBtn",			[BTN_BASE2] = "BaseBtn2",
	[BTN_BASE3] = "BaseBtn3",		[BTN_BASE4] = "BaseBtn4",
	[BTN_BASE5] = "BaseBtn5",		[BTN_BASE6] = "BaseBtn6",
	[BTN_DEAD] = "BtnDead",			[BTN_A] = "BtnA",
	[BTN_B] = "BtnB",			[BTN_C] = "BtnC",
	[BTN_X] = "BtnX",			[BTN_Y] = "BtnY",
	[BTN_Z] = "BtnZ",			[BTN_TL] = "BtnTL",
	[BTN_TR] = "BtnTR",			[BTN_TL2] = "BtnTL2",
	[BTN_TR2] = "BtnTR2",			[BTN_SELECT] = "BtnSelect",
	[BTN_START] = "BtnStart",		[BTN_MODE] = "BtnMode",
	[BTN_THUMBL] = "BtnThumbL",		[BTN_THUMBR] = "BtnThumbR",
	[BTN_TOOL_PEN] = "ToolPen",		[BTN_TOOL_RUBBER] = "ToolRubber",
	[BTN_TOOL_BRUSH] = "ToolBrush",		[BTN_TOOL_PENCIL] = "ToolPencil",
	[BTN_TOOL_AIRBRUSH] = "ToolAirbrush",	[BTN_TOOL_FINGER] = "ToolFinger",
	[BTN_TOOL_MOUSE] = "ToolMouse",		[BTN_TOOL_LENS] = "ToolLens",
	[BTN_TOUCH] = "Touch",			[BTN_STYLUS] = "Stylus",
	[BTN_STYLUS2] = "Stylus2",		[BTN_TOOL_DOUBLETAP] = "ToolDoubleTap",
	[BTN_TOOL_TRIPLETAP] = "ToolTripleTap",	[BTN_TOOL_QUADTAP] = "ToolQuadrupleTap",
	[BTN_GEAR_DOWN] = "WheelBtn",
	[BTN_GEAR_UP] = "Gear up",		[KEY_OK] = "Ok",
	[KEY_SELECT] = "Select",		[KEY_GOTO] = "Goto",
	[KEY_CLEAR] = "Clear",			[KEY_POWER2] = "Power2",
	[KEY_OPTION] = "Option",		[KEY_INFO] = "Info",
	[KEY_TIME] = "Time",			[KEY_VENDOR] = "Vendor",
	[KEY_ARCHIVE] = "Archive",		[KEY_PROGRAM] = "Program",
	[KEY_CHANNEL] = "Channel",		[KEY_FAVORITES] = "Favorites",
	[KEY_EPG] = "EPG",			[KEY_PVR] = "PVR",
	[KEY_MHP] = "MHP",			[KEY_LANGUAGE] = "Language",
	[KEY_TITLE] = "Title",			[KEY_SUBTITLE] = "Subtitle",
	[KEY_ANGLE] = "Angle",			[KEY_ZOOM] = "Zoom",
	[KEY_MODE] = "Mode",			[KEY_KEYBOARD] = "Keyboard",
	[KEY_SCREEN] = "Screen",		[KEY_PC] = "PC",
	[KEY_TV] = "TV",			[KEY_TV2] = "TV2",
	[KEY_VCR] = "VCR",			[KEY_VCR2] = "VCR2",
	[KEY_SAT] = "Sat",			[KEY_SAT2] = "Sat2",
	[KEY_CD] = "CD",			[KEY_TAPE] = "Tape",
	[KEY_RADIO] = "Radio",			[KEY_TUNER] = "Tuner",
	[KEY_PLAYER] = "Player",		[KEY_TEXT] = "Text",
	[KEY_DVD] = "DVD",			[KEY_AUX] = "Aux",
	[KEY_MP3] = "MP3",			[KEY_AUDIO] = "Audio",
	[KEY_VIDEO] = "Video",			[KEY_सूचीECTORY] = "Directory",
	[KEY_LIST] = "List",			[KEY_MEMO] = "Memo",
	[KEY_CALENDAR] = "Calendar",		[KEY_RED] = "Red",
	[KEY_GREEN] = "Green",			[KEY_YELLOW] = "Yellow",
	[KEY_BLUE] = "Blue",			[KEY_CHANNELUP] = "ChannelUp",
	[KEY_CHANNELDOWN] = "ChannelDown",	[KEY_FIRST] = "First",
	[KEY_LAST] = "Last",			[KEY_AB] = "AB",
	[KEY_NEXT] = "Next",			[KEY_RESTART] = "Restart",
	[KEY_SLOW] = "Slow",			[KEY_SHUFFLE] = "Shuffle",
	[KEY_BREAK] = "Break",			[KEY_PREVIOUS] = "Previous",
	[KEY_DIGITS] = "Digits",		[KEY_TEEN] = "TEEN",
	[KEY_TWEN] = "TWEN",			[KEY_DEL_EOL] = "DeleteEOL",
	[KEY_DEL_EOS] = "DeleteEOS",		[KEY_INS_LINE] = "InsertLine",
	[KEY_DEL_LINE] = "DeleteLine",
	[KEY_SEND] = "Send",			[KEY_REPLY] = "Reply",
	[KEY_FORWARDMAIL] = "ForwardMail",	[KEY_SAVE] = "Save",
	[KEY_DOCUMENTS] = "Documents",		[KEY_SPELLCHECK] = "SpellCheck",
	[KEY_LOGOFF] = "Logoff",
	[KEY_FN] = "Fn",			[KEY_FN_ESC] = "Fn+ESC",
	[KEY_FN_1] = "Fn+1",			[KEY_FN_2] = "Fn+2",
	[KEY_FN_B] = "Fn+B",			[KEY_FN_D] = "Fn+D",
	[KEY_FN_E] = "Fn+E",			[KEY_FN_F] = "Fn+F",
	[KEY_FN_S] = "Fn+S",
	[KEY_FN_F1] = "Fn+F1",			[KEY_FN_F2] = "Fn+F2",
	[KEY_FN_F3] = "Fn+F3",			[KEY_FN_F4] = "Fn+F4",
	[KEY_FN_F5] = "Fn+F5",			[KEY_FN_F6] = "Fn+F6",
	[KEY_FN_F7] = "Fn+F7",			[KEY_FN_F8] = "Fn+F8",
	[KEY_FN_F9] = "Fn+F9",			[KEY_FN_F10] = "Fn+F10",
	[KEY_FN_F11] = "Fn+F11",		[KEY_FN_F12] = "Fn+F12",
	[KEY_KBDILLUMTOGGLE] = "KbdIlluminationToggle",
	[KEY_KBDILLUMDOWN] = "KbdIlluminationDown",
	[KEY_KBDILLUMUP] = "KbdIlluminationUp",
	[KEY_SWITCHVIDEOMODE] = "SwitchVideoMode",
	[KEY_BUTTONCONFIG] = "ButtonConfig",
	[KEY_TASKMANAGER] = "TaskManager",
	[KEY_JOURNAL] = "Journal",
	[KEY_CONTROLPANEL] = "ControlPanel",
	[KEY_APPSELECT] = "AppSelect",
	[KEY_SCREENSAVER] = "ScreenSaver",
	[KEY_VOICECOMMAND] = "VoiceCommand",
	[KEY_ASSISTANT] = "Assistant",
	[KEY_KBD_LAYOUT_NEXT] = "KbdLayoutNext",
	[KEY_EMOJI_PICKER] = "EmojiPicker",
	[KEY_BRIGHTNESS_MIN] = "BrightnessMin",
	[KEY_BRIGHTNESS_MAX] = "BrightnessMax",
	[KEY_BRIGHTNESS_AUTO] = "BrightnessAuto",
	[KEY_KBDINPUTASSIST_PREV] = "KbdInputAssistPrev",
	[KEY_KBDINPUTASSIST_NEXT] = "KbdInputAssistNext",
	[KEY_KBDINPUTASSIST_PREVGROUP] = "KbdInputAssistPrevGroup",
	[KEY_KBDINPUTASSIST_NEXTGROUP] = "KbdInputAssistNextGroup",
	[KEY_KBDINPUTASSIST_ACCEPT] = "KbdInputAssistAccept",
	[KEY_KBDINPUTASSIST_CANCEL] = "KbdInputAssistCancel",
पूर्ण;

अटल स्थिर अक्षर *relatives[REL_MAX + 1] = अणु
	[REL_X] = "X",			[REL_Y] = "Y",
	[REL_Z] = "Z",			[REL_RX] = "Rx",
	[REL_RY] = "Ry",		[REL_RZ] = "Rz",
	[REL_HWHEEL] = "HWheel",	[REL_DIAL] = "Dial",
	[REL_WHEEL] = "Wheel",		[REL_MISC] = "Misc",
पूर्ण;

अटल स्थिर अक्षर *असलolutes[ABS_CNT] = अणु
	[ABS_X] = "X",			[ABS_Y] = "Y",
	[ABS_Z] = "Z",			[ABS_RX] = "Rx",
	[ABS_RY] = "Ry",		[ABS_RZ] = "Rz",
	[ABS_THROTTLE] = "Throttle",	[ABS_RUDDER] = "Rudder",
	[ABS_WHEEL] = "Wheel",		[ABS_GAS] = "Gas",
	[ABS_BRAKE] = "Brake",		[ABS_HAT0X] = "Hat0X",
	[ABS_HAT0Y] = "Hat0Y",		[ABS_HAT1X] = "Hat1X",
	[ABS_HAT1Y] = "Hat1Y",		[ABS_HAT2X] = "Hat2X",
	[ABS_HAT2Y] = "Hat2Y",		[ABS_HAT3X] = "Hat3X",
	[ABS_HAT3Y] = "Hat 3Y",		[ABS_PRESSURE] = "Pressure",
	[ABS_DISTANCE] = "Distance",	[ABS_TILT_X] = "XTilt",
	[ABS_TILT_Y] = "YTilt",		[ABS_TOOL_WIDTH] = "ToolWidth",
	[ABS_VOLUME] = "Volume",	[ABS_MISC] = "Misc",
	[ABS_MT_TOUCH_MAJOR] = "MTMajor",
	[ABS_MT_TOUCH_MINOR] = "MTMinor",
	[ABS_MT_WIDTH_MAJOR] = "MTMajorW",
	[ABS_MT_WIDTH_MINOR] = "MTMinorW",
	[ABS_MT_ORIENTATION] = "MTOrientation",
	[ABS_MT_POSITION_X] = "MTPositionX",
	[ABS_MT_POSITION_Y] = "MTPositionY",
	[ABS_MT_TOOL_TYPE] = "MTToolType",
	[ABS_MT_BLOB_ID] = "MTBlobID",
पूर्ण;

अटल स्थिर अक्षर *misc[MSC_MAX + 1] = अणु
	[MSC_SERIAL] = "Serial",	[MSC_PULSELED] = "Pulseled",
	[MSC_GESTURE] = "Gesture",	[MSC_RAW] = "RawData"
पूर्ण;

अटल स्थिर अक्षर *leds[LED_MAX + 1] = अणु
	[LED_NUML] = "NumLock",		[LED_CAPSL] = "CapsLock",
	[LED_SCROLLL] = "ScrollLock",	[LED_COMPOSE] = "Compose",
	[LED_KANA] = "Kana",		[LED_SLEEP] = "Sleep",
	[LED_SUSPEND] = "Suspend",	[LED_MUTE] = "Mute",
	[LED_MISC] = "Misc",
पूर्ण;

अटल स्थिर अक्षर *repeats[REP_MAX + 1] = अणु
	[REP_DELAY] = "Delay",		[REP_PERIOD] = "Period"
पूर्ण;

अटल स्थिर अक्षर *sounds[SND_MAX + 1] = अणु
	[SND_CLICK] = "Click",		[SND_BELL] = "Bell",
	[SND_TONE] = "Tone"
पूर्ण;

अटल स्थिर अक्षर **names[EV_MAX + 1] = अणु
	[EV_SYN] = syncs,			[EV_KEY] = keys,
	[EV_REL] = relatives,			[EV_ABS] = असलolutes,
	[EV_MSC] = misc,			[EV_LED] = leds,
	[EV_SND] = sounds,			[EV_REP] = repeats,
पूर्ण;

अटल व्योम hid_resolv_event(__u8 type, __u16 code, काष्ठा seq_file *f)
अणु
	seq_म_लिखो(f, "%s.%s", events[type] ? events[type] : "?",
		names[type] ? (names[type][code] ? names[type][code] : "?") : "?");
पूर्ण

अटल व्योम hid_dump_input_mapping(काष्ठा hid_device *hid, काष्ठा seq_file *f)
अणु
	पूर्णांक i, j, k;
	काष्ठा hid_report *report;
	काष्ठा hid_usage *usage;

	क्रम (k = HID_INPUT_REPORT; k <= HID_OUTPUT_REPORT; k++) अणु
		list_क्रम_each_entry(report, &hid->report_क्रमागत[k].report_list, list) अणु
			क्रम (i = 0; i < report->maxfield; i++) अणु
				क्रम ( j = 0; j < report->field[i]->maxusage; j++) अणु
					usage = report->field[i]->usage + j;
					hid_resolv_usage(usage->hid, f);
					seq_म_लिखो(f, " ---> ");
					hid_resolv_event(usage->type, usage->code, f);
					seq_म_लिखो(f, "\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण

अटल पूर्णांक hid_debug_rdesc_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hid_device *hdev = f->निजी;
	स्थिर __u8 *rdesc = hdev->rdesc;
	अचिन्हित rsize = hdev->rsize;
	पूर्णांक i;

	अगर (!rdesc) अणु
		rdesc = hdev->dev_rdesc;
		rsize = hdev->dev_rsize;
	पूर्ण

	/* dump HID report descriptor */
	क्रम (i = 0; i < rsize; i++)
		seq_म_लिखो(f, "%02x ", rdesc[i]);
	seq_म_लिखो(f, "\n\n");

	/* dump parsed data and input mappings */
	अगर (करोwn_पूर्णांकerruptible(&hdev->driver_input_lock))
		वापस 0;

	hid_dump_device(hdev, f);
	seq_म_लिखो(f, "\n");
	hid_dump_input_mapping(hdev, f);

	up(&hdev->driver_input_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hid_debug_events_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err = 0;
	काष्ठा hid_debug_list *list;
	अचिन्हित दीर्घ flags;

	अगर (!(list = kzalloc(माप(काष्ठा hid_debug_list), GFP_KERNEL))) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = kfअगरo_alloc(&list->hid_debug_fअगरo, HID_DEBUG_FIFOSIZE, GFP_KERNEL);
	अगर (err) अणु
		kमुक्त(list);
		जाओ out;
	पूर्ण
	list->hdev = (काष्ठा hid_device *) inode->i_निजी;
	file->निजी_data = list;
	mutex_init(&list->पढ़ो_mutex);

	spin_lock_irqsave(&list->hdev->debug_list_lock, flags);
	list_add_tail(&list->node, &list->hdev->debug_list);
	spin_unlock_irqrestore(&list->hdev->debug_list_lock, flags);

out:
	वापस err;
पूर्ण

अटल sमाप_प्रकार hid_debug_events_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hid_debug_list *list = file->निजी_data;
	पूर्णांक ret = 0, copied;
	DECLARE_WAITQUEUE(रुको, current);

	mutex_lock(&list->पढ़ो_mutex);
	अगर (kfअगरo_is_empty(&list->hid_debug_fअगरo)) अणु
		add_रुको_queue(&list->hdev->debug_रुको, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);

		जबतक (kfअगरo_is_empty(&list->hid_debug_fअगरo)) अणु
			अगर (संकेत_pending(current)) अणु
				ret = -ERESTARTSYS;
				अवरोध;
			पूर्ण

			/* अगर list->hdev is शून्य we cannot हटाओ_रुको_queue().
			 * अगर list->hdev->debug is 0 then hid_debug_unरेजिस्टर()
			 * was alपढ़ोy called and list->hdev is being destroyed.
			 * अगर we add हटाओ_रुको_queue() here we can hit a race.
			 */
			अगर (!list->hdev || !list->hdev->debug) अणु
				ret = -EIO;
				set_current_state(TASK_RUNNING);
				जाओ out;
			पूर्ण

			अगर (file->f_flags & O_NONBLOCK) अणु
				ret = -EAGAIN;
				अवरोध;
			पूर्ण

			/* allow O_NONBLOCK from other thपढ़ोs */
			mutex_unlock(&list->पढ़ो_mutex);
			schedule();
			mutex_lock(&list->पढ़ो_mutex);
			set_current_state(TASK_INTERRUPTIBLE);
		पूर्ण

		__set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&list->hdev->debug_रुको, &रुको);

		अगर (ret)
			जाओ out;
	पूर्ण

	/* pass the fअगरo content to userspace, locking is not needed with only
	 * one concurrent पढ़ोer and one concurrent ग_लिखोr
	 */
	ret = kfअगरo_to_user(&list->hid_debug_fअगरo, buffer, count, &copied);
	अगर (ret)
		जाओ out;
	ret = copied;
out:
	mutex_unlock(&list->पढ़ो_mutex);
	वापस ret;
पूर्ण

अटल __poll_t hid_debug_events_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा hid_debug_list *list = file->निजी_data;

	poll_रुको(file, &list->hdev->debug_रुको, रुको);
	अगर (!kfअगरo_is_empty(&list->hid_debug_fअगरo))
		वापस EPOLLIN | EPOLLRDNORM;
	अगर (!list->hdev->debug)
		वापस EPOLLERR | EPOLLHUP;
	वापस 0;
पूर्ण

अटल पूर्णांक hid_debug_events_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hid_debug_list *list = file->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list->hdev->debug_list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&list->hdev->debug_list_lock, flags);
	kfअगरo_मुक्त(&list->hid_debug_fअगरo);
	kमुक्त(list);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(hid_debug_rdesc);

अटल स्थिर काष्ठा file_operations hid_debug_events_fops = अणु
	.owner =        THIS_MODULE,
	.खोलो           = hid_debug_events_खोलो,
	.पढ़ो           = hid_debug_events_पढ़ो,
	.poll		= hid_debug_events_poll,
	.release        = hid_debug_events_release,
	.llseek		= noop_llseek,
पूर्ण;


व्योम hid_debug_रेजिस्टर(काष्ठा hid_device *hdev, स्थिर अक्षर *name)
अणु
	hdev->debug_dir = debugfs_create_dir(name, hid_debug_root);
	hdev->debug_rdesc = debugfs_create_file("rdesc", 0400,
			hdev->debug_dir, hdev, &hid_debug_rdesc_fops);
	hdev->debug_events = debugfs_create_file("events", 0400,
			hdev->debug_dir, hdev, &hid_debug_events_fops);
	hdev->debug = 1;
पूर्ण

व्योम hid_debug_unरेजिस्टर(काष्ठा hid_device *hdev)
अणु
	hdev->debug = 0;
	wake_up_पूर्णांकerruptible(&hdev->debug_रुको);
	debugfs_हटाओ(hdev->debug_rdesc);
	debugfs_हटाओ(hdev->debug_events);
	debugfs_हटाओ(hdev->debug_dir);
पूर्ण

व्योम hid_debug_init(व्योम)
अणु
	hid_debug_root = debugfs_create_dir("hid", शून्य);
पूर्ण

व्योम hid_debug_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(hid_debug_root);
पूर्ण
