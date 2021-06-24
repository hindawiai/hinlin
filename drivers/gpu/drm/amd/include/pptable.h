<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _PPTABLE_H
#घोषणा _PPTABLE_H

#आशय pack(1)

प्रकार काष्ठा _ATOM_PPLIB_THERMALCONTROLLER

अणु
    UCHAR ucType;           // one of ATOM_PP_THERMALCONTROLLER_*
    UCHAR ucI2cLine;        // as पूर्णांकerpreted by DAL I2C
    UCHAR ucI2cAddress;
    UCHAR ucFanParameters;  // Fan Control Parameters.
    UCHAR ucFanMinRPM;      // Fan Minimum RPM (hundreds) -- क्रम display purposes only.
    UCHAR ucFanMaxRPM;      // Fan Maximum RPM (hundreds) -- क्रम display purposes only.
    UCHAR ucReserved;       // ----
    UCHAR ucFlags;          // to be defined
पूर्ण ATOM_PPLIB_THERMALCONTROLLER;

#घोषणा ATOM_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK 0x0f
#घोषणा ATOM_PP_FANPARAMETERS_NOFAN                                 0x80    // No fan is connected to this controller.

#घोषणा ATOM_PP_THERMALCONTROLLER_NONE      0
#घोषणा ATOM_PP_THERMALCONTROLLER_LM63      1  // Not used by PPLib
#घोषणा ATOM_PP_THERMALCONTROLLER_ADM1032   2  // Not used by PPLib
#घोषणा ATOM_PP_THERMALCONTROLLER_ADM1030   3  // Not used by PPLib
#घोषणा ATOM_PP_THERMALCONTROLLER_MUA6649   4  // Not used by PPLib
#घोषणा ATOM_PP_THERMALCONTROLLER_LM64      5
#घोषणा ATOM_PP_THERMALCONTROLLER_F75375    6  // Not used by PPLib
#घोषणा ATOM_PP_THERMALCONTROLLER_RV6xx     7
#घोषणा ATOM_PP_THERMALCONTROLLER_RV770     8
#घोषणा ATOM_PP_THERMALCONTROLLER_ADT7473   9
#घोषणा ATOM_PP_THERMALCONTROLLER_KONG      10
#घोषणा ATOM_PP_THERMALCONTROLLER_EXTERNAL_GPIO     11
#घोषणा ATOM_PP_THERMALCONTROLLER_EVERGREEN 12
#घोषणा ATOM_PP_THERMALCONTROLLER_EMC2103   13  /* 0x0D */ // Only fan control will be implemented, करो NOT show this in PPGen.
#घोषणा ATOM_PP_THERMALCONTROLLER_SUMO      14  /* 0x0E */ // Sumo type, used पूर्णांकernally
#घोषणा ATOM_PP_THERMALCONTROLLER_NISLANDS  15
#घोषणा ATOM_PP_THERMALCONTROLLER_SISLANDS  16
#घोषणा ATOM_PP_THERMALCONTROLLER_LM96163   17
#घोषणा ATOM_PP_THERMALCONTROLLER_CISLANDS  18
#घोषणा ATOM_PP_THERMALCONTROLLER_KAVERI    19
#घोषणा ATOM_PP_THERMALCONTROLLER_ICELAND   20
#घोषणा ATOM_PP_THERMALCONTROLLER_TONGA     21
#घोषणा ATOM_PP_THERMALCONTROLLER_FIJI      22
#घोषणा ATOM_PP_THERMALCONTROLLER_POLARIS10 23
#घोषणा ATOM_PP_THERMALCONTROLLER_VEGA10    24


// Thermal controller 'combo type' to use an बाह्यal controller क्रम Fan control and an पूर्णांकernal controller क्रम thermal.
// We probably should reserve the bit 0x80 क्रम this use.
// To keep the number of these types low we should also use the same code क्रम all ASICs (i.e. करो not distinguish RV6xx and RV7xx Internal here).
// The driver can pick the correct पूर्णांकernal controller based on the ASIC.
#घोषणा ATOM_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL   0x89    // ADT7473 Fan Control + Internal Thermal Controller
#घोषणा ATOM_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL   0x8D    // EMC2103 Fan Control + Internal Thermal Controller

प्रकार काष्ठा _ATOM_PPLIB_STATE
अणु
    UCHAR ucNonClockStateIndex;
    UCHAR ucClockStateIndices[1]; // variable-sized
पूर्ण ATOM_PPLIB_STATE;


प्रकार काष्ठा _ATOM_PPLIB_FANTABLE
अणु
    UCHAR   ucFanTableFormat;                // Change this अगर the table क्रमmat changes or version changes so that the other fields are not the same.
    UCHAR   ucTHyst;                         // Temperature hysteresis. Integer.
    USHORT  usTMin;                          // The temperature, in 0.01 centigrades, below which we just run at a minimal PWM.
    USHORT  usTMed;                          // The middle temperature where we change slopes.
    USHORT  usTHigh;                         // The high poपूर्णांक above TMed क्रम adjusting the second slope.
    USHORT  usPWMMin;                        // The minimum PWM value in percent (0.01% increments).
    USHORT  usPWMMed;                        // The PWM value (in percent) at TMed.
    USHORT  usPWMHigh;                       // The PWM value at THigh.
पूर्ण ATOM_PPLIB_FANTABLE;

प्रकार काष्ठा _ATOM_PPLIB_FANTABLE2
अणु
    ATOM_PPLIB_FANTABLE basicTable;
    USHORT  usTMax;                          // The max temperature
पूर्ण ATOM_PPLIB_FANTABLE2;

प्रकार काष्ठा _ATOM_PPLIB_FANTABLE3
अणु
	ATOM_PPLIB_FANTABLE2 basicTable2;
	UCHAR ucFanControlMode;
	USHORT usFanPWMMax;
	USHORT usFanOutputSensitivity;
पूर्ण ATOM_PPLIB_FANTABLE3;

प्रकार काष्ठा _ATOM_PPLIB_FANTABLE4
अणु
    ATOM_PPLIB_FANTABLE3 basicTable3;
    USHORT  usFanRPMMax;
पूर्ण ATOM_PPLIB_FANTABLE4;

प्रकार काष्ठा _ATOM_PPLIB_FANTABLE5
अणु
    ATOM_PPLIB_FANTABLE4 basicTable4;
    USHORT  usFanCurrentLow;
    USHORT  usFanCurrentHigh;
    USHORT  usFanRPMLow;
    USHORT  usFanRPMHigh;
पूर्ण ATOM_PPLIB_FANTABLE5;

प्रकार काष्ठा _ATOM_PPLIB_EXTENDEDHEADER
अणु
    USHORT  usSize;
    ULONG   ulMaxEngineClock;   // For Overdrive.
    ULONG   ulMaxMemoryClock;   // For Overdrive.
    // Add extra प्रणाली parameters here, always adjust size to include all fields.
    USHORT  usVCETableOffset; //poपूर्णांकs to ATOM_PPLIB_VCE_Table
    USHORT  usUVDTableOffset;   //poपूर्णांकs to ATOM_PPLIB_UVD_Table
    USHORT  usSAMUTableOffset;  //poपूर्णांकs to ATOM_PPLIB_SAMU_Table
    USHORT  usPPMTableOffset;   //poपूर्णांकs to ATOM_PPLIB_PPM_Table
    USHORT  usACPTableOffset;  //poपूर्णांकs to ATOM_PPLIB_ACP_Table   
    /* poपूर्णांकs to ATOM_PPLIB_POWERTUNE_Table */
    USHORT  usPowerTuneTableOffset;
    /* poपूर्णांकs to ATOM_PPLIB_CLOCK_Voltage_Dependency_Table क्रम sclkVddgfxTable */
    USHORT  usSclkVddgfxTableOffset;
    USHORT  usVQBudgetingTableOffset; /* poपूर्णांकs to the vqBudgetingTable; */
पूर्ण ATOM_PPLIB_EXTENDEDHEADER;

//// ATOM_PPLIB_POWERPLAYTABLE::ulPlatक्रमmCaps
#घोषणा ATOM_PP_PLATFORM_CAP_BACKBIAS 1
#घोषणा ATOM_PP_PLATFORM_CAP_POWERPLAY 2
#घोषणा ATOM_PP_PLATFORM_CAP_SBIOSPOWERSOURCE 4
#घोषणा ATOM_PP_PLATFORM_CAP_ASPM_L0s 8
#घोषणा ATOM_PP_PLATFORM_CAP_ASPM_L1 16
#घोषणा ATOM_PP_PLATFORM_CAP_HARDWAREDC 32
#घोषणा ATOM_PP_PLATFORM_CAP_GEMINIPRIMARY 64
#घोषणा ATOM_PP_PLATFORM_CAP_STEPVDDC 128
#घोषणा ATOM_PP_PLATFORM_CAP_VOLTAGECONTROL 256
#घोषणा ATOM_PP_PLATFORM_CAP_SIDEPORTCONTROL 512
#घोषणा ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1 1024
#घोषणा ATOM_PP_PLATFORM_CAP_HTLINKCONTROL 2048
#घोषणा ATOM_PP_PLATFORM_CAP_MVDDCONTROL 4096
#घोषणा ATOM_PP_PLATFORM_CAP_GOTO_BOOT_ON_ALERT 0x2000              // Go to boot state on alerts, e.g. on an AC->DC transition.
#घोषणा ATOM_PP_PLATFORM_CAP_DONT_WAIT_FOR_VBLANK_ON_ALERT 0x4000   // Do NOT रुको क्रम VBLANK during an alert (e.g. AC->DC transition).
#घोषणा ATOM_PP_PLATFORM_CAP_VDDCI_CONTROL 0x8000                   // Does the driver control VDDCI independently from VDDC.
#घोषणा ATOM_PP_PLATFORM_CAP_REGULATOR_HOT 0x00010000               // Enable the 'regulator hot' feature.
#घोषणा ATOM_PP_PLATFORM_CAP_BACO          0x00020000               // Does the driver supports BACO state.
#घोषणा ATOM_PP_PLATFORM_CAP_NEW_CAC_VOLTAGE   0x00040000           // Does the driver supports new CAC voltage table.
#घोषणा ATOM_PP_PLATFORM_CAP_REVERT_GPIO5_POLARITY   0x00080000     // Does the driver supports revert GPIO5 polarity.
#घोषणा ATOM_PP_PLATFORM_CAP_OUTPUT_THERMAL2GPIO17   0x00100000     // Does the driver supports thermal2GPIO17.
#घोषणा ATOM_PP_PLATFORM_CAP_VRHOT_GPIO_CONFIGURABLE   0x00200000   // Does the driver supports VR HOT GPIO Configurable.
#घोषणा ATOM_PP_PLATFORM_CAP_TEMP_INVERSION   0x00400000            // Does the driver supports Temp Inversion feature.
#घोषणा ATOM_PP_PLATFORM_CAP_EVV    0x00800000
#घोषणा ATOM_PP_PLATFORM_COMBINE_PCC_WITH_THERMAL_SIGNAL    0x01000000
#घोषणा ATOM_PP_PLATFORM_LOAD_POST_PRODUCTION_FIRMWARE    0x02000000
#घोषणा ATOM_PP_PLATFORM_CAP_DISABLE_USING_ACTUAL_TEMPERATURE_FOR_POWER_CALC   0x04000000
#घोषणा ATOM_PP_PLATFORM_CAP_VRHOT_POLARITY_HIGH   0x08000000

प्रकार काष्ठा _ATOM_PPLIB_POWERPLAYTABLE
अणु
      ATOM_COMMON_TABLE_HEADER sHeader;

      UCHAR ucDataRevision;

      UCHAR ucNumStates;
      UCHAR ucStateEntrySize;
      UCHAR ucClockInfoSize;
      UCHAR ucNonClockSize;

      // offset from start of this table to array of ucNumStates ATOM_PPLIB_STATE काष्ठाures
      USHORT usStateArrayOffset;

      // offset from start of this table to array of ASIC-specअगरic काष्ठाures,
      // currently ATOM_PPLIB_CLOCK_INFO.
      USHORT usClockInfoArrayOffset;

      // offset from start of this table to array of ATOM_PPLIB_NONCLOCK_INFO
      USHORT usNonClockInfoArrayOffset;

      USHORT usBackbiasTime;    // in microseconds
      USHORT usVoltageTime;     // in microseconds
      USHORT usTableSize;       //the size of this काष्ठाure, or the extended काष्ठाure

      ULONG ulPlatक्रमmCaps;            // See ATOM_PPLIB_CAPS_*

      ATOM_PPLIB_THERMALCONTROLLER    sThermalController;

      USHORT usBootClockInfoOffset;
      USHORT usBootNonClockInfoOffset;

पूर्ण ATOM_PPLIB_POWERPLAYTABLE;

प्रकार काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2
अणु
    ATOM_PPLIB_POWERPLAYTABLE basicTable;
    UCHAR   ucNumCustomThermalPolicy;
    USHORT  usCustomThermalPolicyArrayOffset;
पूर्णATOM_PPLIB_POWERPLAYTABLE2, *LPATOM_PPLIB_POWERPLAYTABLE2;

प्रकार काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3
अणु
    ATOM_PPLIB_POWERPLAYTABLE2 basicTable2;
    USHORT                     usFormatID;                      // To be used ONLY by PPGen.
    USHORT                     usFanTableOffset;
    USHORT                     usExtendendedHeaderOffset;
पूर्ण ATOM_PPLIB_POWERPLAYTABLE3, *LPATOM_PPLIB_POWERPLAYTABLE3;

प्रकार काष्ठा _ATOM_PPLIB_POWERPLAYTABLE4
अणु
    ATOM_PPLIB_POWERPLAYTABLE3 basicTable3;
    ULONG                      ulGoldenPPID;                    // PPGen use only     
    ULONG                      ulGoldenRevision;                // PPGen use only
    USHORT                     usVddcDependencyOnSCLKOffset;
    USHORT                     usVddciDependencyOnMCLKOffset;
    USHORT                     usVddcDependencyOnMCLKOffset;
    USHORT                     usMaxClockVoltageOnDCOffset;
    USHORT                     usVddcPhaseShedLimitsTableOffset;    // Poपूर्णांकs to ATOM_PPLIB_PhaseSheddingLimits_Table
    USHORT                     usMvddDependencyOnMCLKOffset;  
पूर्ण ATOM_PPLIB_POWERPLAYTABLE4, *LPATOM_PPLIB_POWERPLAYTABLE4;

प्रकार काष्ठा _ATOM_PPLIB_POWERPLAYTABLE5
अणु
    ATOM_PPLIB_POWERPLAYTABLE4 basicTable4;
    ULONG                      ulTDPLimit;
    ULONG                      ulNearTDPLimit;
    ULONG                      ulSQRampingThreshold;
    USHORT                     usCACLeakageTableOffset;         // Poपूर्णांकs to ATOM_PPLIB_CAC_Leakage_Table
    ULONG                      ulCACLeakage;                    // The iLeakage क्रम driver calculated CAC leakage table
    USHORT                     usTDPODLimit;
    USHORT                     usLoadLineSlope;                 // in milliOhms * 100
पूर्ण ATOM_PPLIB_POWERPLAYTABLE5, *LPATOM_PPLIB_POWERPLAYTABLE5;

//// ATOM_PPLIB_NONCLOCK_INFO::usClassअगरication
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_MASK          0x0007
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_SHIFT         0
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_NONE          0
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_BATTERY       1
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_BALANCED      3
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE   5
// 2, 4, 6, 7 are reserved

#घोषणा ATOM_PPLIB_CLASSIFICATION_BOOT                   0x0008
#घोषणा ATOM_PPLIB_CLASSIFICATION_THERMAL                0x0010
#घोषणा ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE     0x0020
#घोषणा ATOM_PPLIB_CLASSIFICATION_REST                   0x0040
#घोषणा ATOM_PPLIB_CLASSIFICATION_FORCED                 0x0080
#घोषणा ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE          0x0100
#घोषणा ATOM_PPLIB_CLASSIFICATION_OVERDRIVETEMPLATE      0x0200
#घोषणा ATOM_PPLIB_CLASSIFICATION_UVDSTATE               0x0400
#घोषणा ATOM_PPLIB_CLASSIFICATION_3DLOW                  0x0800
#घोषणा ATOM_PPLIB_CLASSIFICATION_ACPI                   0x1000
#घोषणा ATOM_PPLIB_CLASSIFICATION_HD2STATE               0x2000
#घोषणा ATOM_PPLIB_CLASSIFICATION_HDSTATE                0x4000
#घोषणा ATOM_PPLIB_CLASSIFICATION_SDSTATE                0x8000

//// ATOM_PPLIB_NONCLOCK_INFO::usClassअगरication2
#घोषणा ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2     0x0001
#घोषणा ATOM_PPLIB_CLASSIFICATION2_ULV                      0x0002
#घोषणा ATOM_PPLIB_CLASSIFICATION2_MVC                      0x0004   //Multi-View Codec (BD-3D)

//// ATOM_PPLIB_NONCLOCK_INFO::ulCapsAndSettings
#घोषणा ATOM_PPLIB_SINGLE_DISPLAY_ONLY           0x00000001
#घोषणा ATOM_PPLIB_SUPPORTS_VIDEO_PLAYBACK         0x00000002

// 0 is 2.5Gb/s, 1 is 5Gb/s
#घोषणा ATOM_PPLIB_PCIE_LINK_SPEED_MASK            0x00000004
#घोषणा ATOM_PPLIB_PCIE_LINK_SPEED_SHIFT           2

// lanes - 1: 1, 2, 4, 8, 12, 16 permitted by PCIE spec
#घोषणा ATOM_PPLIB_PCIE_LINK_WIDTH_MASK            0x000000F8
#घोषणा ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT           3

// lookup पूर्णांकo reduced refresh-rate table
#घोषणा ATOM_PPLIB_LIMITED_REFRESHRATE_VALUE_MASK  0x00000F00
#घोषणा ATOM_PPLIB_LIMITED_REFRESHRATE_VALUE_SHIFT 8

#घोषणा ATOM_PPLIB_LIMITED_REFRESHRATE_UNLIMITED    0
#घोषणा ATOM_PPLIB_LIMITED_REFRESHRATE_50HZ         1
// 2-15 TBD as needed.

#घोषणा ATOM_PPLIB_SOFTWARE_DISABLE_LOADBALANCING        0x00001000
#घोषणा ATOM_PPLIB_SOFTWARE_ENABLE_SLEEP_FOR_TIMESTAMPS  0x00002000

#घोषणा ATOM_PPLIB_DISALLOW_ON_DC                       0x00004000

#घोषणा ATOM_PPLIB_ENABLE_VARIBRIGHT                     0x00008000

//memory related flags
#घोषणा ATOM_PPLIB_SWSTATE_MEMORY_DLL_OFF               0x000010000

//M3 Arb    //2bits, current 3 sets of parameters in total
#घोषणा ATOM_PPLIB_M3ARB_MASK                       0x00060000
#घोषणा ATOM_PPLIB_M3ARB_SHIFT                      17

#घोषणा ATOM_PPLIB_ENABLE_DRR                       0x00080000

// reमुख्यing 16 bits are reserved
प्रकार काष्ठा _ATOM_PPLIB_THERMAL_STATE
अणु
    UCHAR   ucMinTemperature;
    UCHAR   ucMaxTemperature;
    UCHAR   ucThermalAction;
पूर्णATOM_PPLIB_THERMAL_STATE, *LPATOM_PPLIB_THERMAL_STATE;

// Contained in an array starting at the offset
// in ATOM_PPLIB_POWERPLAYTABLE::usNonClockInfoArrayOffset.
// referenced from ATOM_PPLIB_STATE_INFO::ucNonClockStateIndex
#घोषणा ATOM_PPLIB_NONCLOCKINFO_VER1      12
#घोषणा ATOM_PPLIB_NONCLOCKINFO_VER2      24
प्रकार काष्ठा _ATOM_PPLIB_NONCLOCK_INFO
अणु
      USHORT usClassअगरication;
      UCHAR  ucMinTemperature;
      UCHAR  ucMaxTemperature;
      ULONG  ulCapsAndSettings;
      UCHAR  ucRequiredPower;
      USHORT usClassअगरication2;
      ULONG  ulVCLK;
      ULONG  ulDCLK;
      UCHAR  ucUnused[5];
पूर्ण ATOM_PPLIB_NONCLOCK_INFO;

// Contained in an array starting at the offset
// in ATOM_PPLIB_POWERPLAYTABLE::usClockInfoArrayOffset.
// referenced from ATOM_PPLIB_STATE::ucClockStateIndices
प्रकार काष्ठा _ATOM_PPLIB_R600_CLOCK_INFO
अणु
      USHORT usEngineClockLow;
      UCHAR ucEngineClockHigh;

      USHORT usMemoryClockLow;
      UCHAR ucMemoryClockHigh;

      USHORT usVDDC;
      USHORT usUnused1;
      USHORT usUnused2;

      ULONG ulFlags; // ATOM_PPLIB_R600_FLAGS_*

पूर्ण ATOM_PPLIB_R600_CLOCK_INFO;

// ulFlags in ATOM_PPLIB_R600_CLOCK_INFO
#घोषणा ATOM_PPLIB_R600_FLAGS_PCIEGEN2          1
#घोषणा ATOM_PPLIB_R600_FLAGS_UVDSAFE           2
#घोषणा ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE    4
#घोषणा ATOM_PPLIB_R600_FLAGS_MEMORY_ODT_OFF    8
#घोषणा ATOM_PPLIB_R600_FLAGS_MEMORY_DLL_OFF   16
#घोषणा ATOM_PPLIB_R600_FLAGS_LOWPOWER         32   // On the RV770 use 'low power' setting (sequencer S0).

प्रकार काष्ठा _ATOM_PPLIB_RS780_CLOCK_INFO

अणु
      USHORT usLowEngineClockLow;         // Low Engine घड़ी in MHz (the same way as on the R600).
      UCHAR  ucLowEngineClockHigh;
      USHORT usHighEngineClockLow;        // High Engine घड़ी in MHz.
      UCHAR  ucHighEngineClockHigh;
      USHORT usMemoryClockLow;            // For now one of the ATOM_PPLIB_RS780_SPMCLK_XXXX स्थिरants.
      UCHAR  ucMemoryClockHigh;           // Currentyl unused.
      UCHAR  ucPadding;                   // For proper alignment and size.
      USHORT usVDDC;                      // For the 780, use: None, Low, High, Variable
      UCHAR  ucMaxHTLinkWidth;            // From SBIOS - अणु2, 4, 8, 16पूर्ण
      UCHAR  ucMinHTLinkWidth;            // From SBIOS - अणु2, 4, 8, 16पूर्ण. Effective only अगर CDLW enabled. Minimum करोwn stream width could 
      USHORT usHTLinkFreq;                // See definition ATOM_PPLIB_RS780_HTLINKFREQ_xxx or in MHz(>=200).
      ULONG  ulFlags; 
पूर्ण ATOM_PPLIB_RS780_CLOCK_INFO;

#घोषणा ATOM_PPLIB_RS780_VOLTAGE_NONE       0 
#घोषणा ATOM_PPLIB_RS780_VOLTAGE_LOW        1 
#घोषणा ATOM_PPLIB_RS780_VOLTAGE_HIGH       2 
#घोषणा ATOM_PPLIB_RS780_VOLTAGE_VARIABLE   3 

#घोषणा ATOM_PPLIB_RS780_SPMCLK_NONE        0   // We cannot change the side port memory घड़ी, leave it as it is.
#घोषणा ATOM_PPLIB_RS780_SPMCLK_LOW         1
#घोषणा ATOM_PPLIB_RS780_SPMCLK_HIGH        2

#घोषणा ATOM_PPLIB_RS780_HTLINKFREQ_NONE       0 
#घोषणा ATOM_PPLIB_RS780_HTLINKFREQ_LOW        1 
#घोषणा ATOM_PPLIB_RS780_HTLINKFREQ_HIGH       2 

प्रकार काष्ठा _ATOM_PPLIB_EVERGREEN_CLOCK_INFO
अणु
      USHORT usEngineClockLow;
      UCHAR  ucEngineClockHigh;

      USHORT usMemoryClockLow;
      UCHAR  ucMemoryClockHigh;

      USHORT usVDDC;
      USHORT usVDDCI;
      USHORT usUnused;

      ULONG ulFlags; // ATOM_PPLIB_R600_FLAGS_*

पूर्ण ATOM_PPLIB_EVERGREEN_CLOCK_INFO;

प्रकार काष्ठा _ATOM_PPLIB_SI_CLOCK_INFO
अणु
      USHORT usEngineClockLow;
      UCHAR  ucEngineClockHigh;

      USHORT usMemoryClockLow;
      UCHAR  ucMemoryClockHigh;

      USHORT usVDDC;
      USHORT usVDDCI;
      UCHAR  ucPCIEGen;
      UCHAR  ucUnused1;

      ULONG ulFlags; // ATOM_PPLIB_SI_FLAGS_*, no flag is necessary क्रम now

पूर्ण ATOM_PPLIB_SI_CLOCK_INFO;

प्रकार काष्ठा _ATOM_PPLIB_CI_CLOCK_INFO
अणु
      USHORT usEngineClockLow;
      UCHAR  ucEngineClockHigh;

      USHORT usMemoryClockLow;
      UCHAR  ucMemoryClockHigh;
      
      UCHAR  ucPCIEGen;
      USHORT usPCIELane;
पूर्ण ATOM_PPLIB_CI_CLOCK_INFO;

प्रकार काष्ठा _ATOM_PPLIB_SUMO_CLOCK_INFOअणु
      USHORT usEngineClockLow;  //घड़ीfrequency & 0xFFFF. The unit is in 10khz
      UCHAR  ucEngineClockHigh; //घड़ीfrequency >> 16. 
      UCHAR  vddcIndex;         //2-bit vddc index;
      USHORT tdpLimit;
      //please initalize to 0
      USHORT rsv1;
      //please initialize to 0s
      ULONG rsv2[2];
पूर्णATOM_PPLIB_SUMO_CLOCK_INFO;

प्रकार काष्ठा _ATOM_PPLIB_KV_CLOCK_INFO अणु
      USHORT usEngineClockLow;
      UCHAR  ucEngineClockHigh;
      UCHAR  vddcIndex;
      USHORT tdpLimit;
      USHORT rsv1;
      ULONG rsv2[2];
पूर्ण ATOM_PPLIB_KV_CLOCK_INFO;

प्रकार काष्ठा _ATOM_PPLIB_CZ_CLOCK_INFO अणु
      UCHAR index;
      UCHAR rsv[3];
पूर्ण ATOM_PPLIB_CZ_CLOCK_INFO;

प्रकार काष्ठा _ATOM_PPLIB_STATE_V2
अणु
      //number of valid dpm levels in this state; Driver uses it to calculate the whole 
      //size of the state: माप(ATOM_PPLIB_STATE_V2) + (ucNumDPMLevels - 1) * माप(UCHAR)
      UCHAR ucNumDPMLevels;
      
      //a index to the array of nonClockInfos
      UCHAR nonClockInfoIndex;
      /**
      * Driver will पढ़ो the first ucNumDPMLevels in this array
      */
      UCHAR घड़ीInfoIndex[1];
पूर्ण ATOM_PPLIB_STATE_V2;

प्रकार काष्ठा _StateArrayअणु
    //how many states we have 
    UCHAR ucNumEntries;
    
    ATOM_PPLIB_STATE_V2 states[1];
पूर्णStateArray;


प्रकार काष्ठा _ClockInfoArrayअणु
    //how many घड़ी levels we have
    UCHAR ucNumEntries;
    
    //माप(ATOM_PPLIB_CLOCK_INFO)
    UCHAR ucEntrySize;
    
    UCHAR घड़ीInfo[1];
पूर्णClockInfoArray;

प्रकार काष्ठा _NonClockInfoArrayअणु

    //how many non-घड़ी levels we have. normally should be same as number of states
    UCHAR ucNumEntries;
    //माप(ATOM_PPLIB_NONCLOCK_INFO)
    UCHAR ucEntrySize;
    
    ATOM_PPLIB_NONCLOCK_INFO nonClockInfo[1];
पूर्णNonClockInfoArray;

प्रकार काष्ठा _ATOM_PPLIB_Clock_Voltage_Dependency_Record
अणु
    USHORT usClockLow;
    UCHAR  ucClockHigh;
    USHORT usVoltage;
पूर्णATOM_PPLIB_Clock_Voltage_Dependency_Record;

प्रकार काष्ठा _ATOM_PPLIB_Clock_Voltage_Dependency_Table
अणु
    UCHAR ucNumEntries;                                                // Number of entries.
    ATOM_PPLIB_Clock_Voltage_Dependency_Record entries[1];             // Dynamically allocate entries.
पूर्णATOM_PPLIB_Clock_Voltage_Dependency_Table;

प्रकार काष्ठा _ATOM_PPLIB_Clock_Voltage_Limit_Record
अणु
    USHORT usSclkLow;
    UCHAR  ucSclkHigh;
    USHORT usMclkLow;
    UCHAR  ucMclkHigh;
    USHORT usVddc;
    USHORT usVddci;
पूर्णATOM_PPLIB_Clock_Voltage_Limit_Record;

प्रकार काष्ठा _ATOM_PPLIB_Clock_Voltage_Limit_Table
अणु
    UCHAR ucNumEntries;                                                // Number of entries.
    ATOM_PPLIB_Clock_Voltage_Limit_Record entries[1];                  // Dynamically allocate entries.
पूर्णATOM_PPLIB_Clock_Voltage_Limit_Table;

जोड़ _ATOM_PPLIB_CAC_Leakage_Record
अणु
    काष्ठा
    अणु
        USHORT usVddc;          // We use this field क्रम the "fake" standardized VDDC क्रम घातer calculations; For CI and newer, we use this as the real VDDC value. in CI we पढ़ो it as StdVoltageHiSidd
        ULONG  ulLeakageValue;  // For CI and newer we use this as the "fake" standar VDDC value. in CI we पढ़ो it as StdVoltageLoSidd

    पूर्ण;
    काष्ठा
     अणु
        USHORT usVddc1;
        USHORT usVddc2;
        USHORT usVddc3;
     पूर्ण;
पूर्ण;

प्रकार जोड़ _ATOM_PPLIB_CAC_Leakage_Record ATOM_PPLIB_CAC_Leakage_Record;

प्रकार काष्ठा _ATOM_PPLIB_CAC_Leakage_Table
अणु
    UCHAR ucNumEntries;                                                 // Number of entries.
    ATOM_PPLIB_CAC_Leakage_Record entries[1];                           // Dynamically allocate entries.
पूर्णATOM_PPLIB_CAC_Leakage_Table;

प्रकार काष्ठा _ATOM_PPLIB_PhaseSheddingLimits_Record
अणु
    USHORT usVoltage;
    USHORT usSclkLow;
    UCHAR  ucSclkHigh;
    USHORT usMclkLow;
    UCHAR  ucMclkHigh;
पूर्णATOM_PPLIB_PhaseSheddingLimits_Record;

प्रकार काष्ठा _ATOM_PPLIB_PhaseSheddingLimits_Table
अणु
    UCHAR ucNumEntries;                                                 // Number of entries.
    ATOM_PPLIB_PhaseSheddingLimits_Record entries[1];                   // Dynamically allocate entries.
पूर्णATOM_PPLIB_PhaseSheddingLimits_Table;

प्रकार काष्ठा _VCEClockInfoअणु
    USHORT usEVClkLow;
    UCHAR  ucEVClkHigh;
    USHORT usECClkLow;
    UCHAR  ucECClkHigh;
पूर्णVCEClockInfo;

प्रकार काष्ठा _VCEClockInfoArrayअणु
    UCHAR ucNumEntries;
    VCEClockInfo entries[1];
पूर्णVCEClockInfoArray;

प्रकार काष्ठा _ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record
अणु
    USHORT usVoltage;
    UCHAR  ucVCEClockInfoIndex;
पूर्णATOM_PPLIB_VCE_Clock_Voltage_Limit_Record;

प्रकार काष्ठा _ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table
अणु
    UCHAR numEntries;
    ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record entries[1];
पूर्णATOM_PPLIB_VCE_Clock_Voltage_Limit_Table;

प्रकार काष्ठा _ATOM_PPLIB_VCE_State_Record
अणु
    UCHAR  ucVCEClockInfoIndex;
    UCHAR  ucClockInfoIndex; //highest 2 bits indicates memory p-states, lower 6bits indicates index to ClockInfoArrary
पूर्णATOM_PPLIB_VCE_State_Record;

प्रकार काष्ठा _ATOM_PPLIB_VCE_State_Table
अणु
    UCHAR numEntries;
    ATOM_PPLIB_VCE_State_Record entries[1];
पूर्णATOM_PPLIB_VCE_State_Table;


प्रकार काष्ठा _ATOM_PPLIB_VCE_Table
अणु
      UCHAR revid;
//    VCEClockInfoArray array;
//    ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table limits;
//    ATOM_PPLIB_VCE_State_Table states;
पूर्णATOM_PPLIB_VCE_Table;


प्रकार काष्ठा _UVDClockInfoअणु
    USHORT usVClkLow;
    UCHAR  ucVClkHigh;
    USHORT usDClkLow;
    UCHAR  ucDClkHigh;
पूर्णUVDClockInfo;

प्रकार काष्ठा _UVDClockInfoArrayअणु
    UCHAR ucNumEntries;
    UVDClockInfo entries[1];
पूर्णUVDClockInfoArray;

प्रकार काष्ठा _ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record
अणु
    USHORT usVoltage;
    UCHAR  ucUVDClockInfoIndex;
पूर्णATOM_PPLIB_UVD_Clock_Voltage_Limit_Record;

प्रकार काष्ठा _ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table
अणु
    UCHAR numEntries;
    ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record entries[1];
पूर्णATOM_PPLIB_UVD_Clock_Voltage_Limit_Table;

प्रकार काष्ठा _ATOM_PPLIB_UVD_Table
अणु
      UCHAR revid;
//    UVDClockInfoArray array;
//    ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table limits;
पूर्णATOM_PPLIB_UVD_Table;

प्रकार काष्ठा _ATOM_PPLIB_SAMClk_Voltage_Limit_Record
अणु
      USHORT usVoltage;
      USHORT usSAMClockLow;
      UCHAR  ucSAMClockHigh;
पूर्णATOM_PPLIB_SAMClk_Voltage_Limit_Record;

प्रकार काष्ठा _ATOM_PPLIB_SAMClk_Voltage_Limit_Tableअणु
    UCHAR numEntries;
    ATOM_PPLIB_SAMClk_Voltage_Limit_Record entries[1];
पूर्णATOM_PPLIB_SAMClk_Voltage_Limit_Table;

प्रकार काष्ठा _ATOM_PPLIB_SAMU_Table
अणु
      UCHAR revid;
      ATOM_PPLIB_SAMClk_Voltage_Limit_Table limits;
पूर्णATOM_PPLIB_SAMU_Table;

प्रकार काष्ठा _ATOM_PPLIB_ACPClk_Voltage_Limit_Record
अणु
      USHORT usVoltage;
      USHORT usACPClockLow;
      UCHAR  ucACPClockHigh;
पूर्णATOM_PPLIB_ACPClk_Voltage_Limit_Record;

प्रकार काष्ठा _ATOM_PPLIB_ACPClk_Voltage_Limit_Tableअणु
    UCHAR numEntries;
    ATOM_PPLIB_ACPClk_Voltage_Limit_Record entries[1];
पूर्णATOM_PPLIB_ACPClk_Voltage_Limit_Table;

प्रकार काष्ठा _ATOM_PPLIB_ACP_Table
अणु
      UCHAR revid;
      ATOM_PPLIB_ACPClk_Voltage_Limit_Table limits;
पूर्णATOM_PPLIB_ACP_Table;

प्रकार काष्ठा _ATOM_PowerTune_Tableअणु
    USHORT usTDP;
    USHORT usConfigurableTDP;
    USHORT usTDC;
    USHORT usBatteryPowerLimit;
    USHORT usSmallPowerLimit;
    USHORT usLowCACLeakage;
    USHORT usHighCACLeakage;
पूर्णATOM_PowerTune_Table;

प्रकार काष्ठा _ATOM_PPLIB_POWERTUNE_Table
अणु
      UCHAR revid;
      ATOM_PowerTune_Table घातer_tune_table;
पूर्णATOM_PPLIB_POWERTUNE_Table;

प्रकार काष्ठा _ATOM_PPLIB_POWERTUNE_Table_V1
अणु
      UCHAR revid;
      ATOM_PowerTune_Table घातer_tune_table;
      USHORT usMaximumPowerDeliveryLimit;
      USHORT usTjMax;
      USHORT usReserve[6];
पूर्ण ATOM_PPLIB_POWERTUNE_Table_V1;

#घोषणा ATOM_PPM_A_A    1
#घोषणा ATOM_PPM_A_I    2
प्रकार काष्ठा _ATOM_PPLIB_PPM_Table
अणु
      UCHAR  ucRevId;
      UCHAR  ucPpmDesign;          //A+I or A+A
      USHORT usCpuCoreNumber;
      ULONG  ulPlatक्रमmTDP;
      ULONG  ulSmallACPlatक्रमmTDP;
      ULONG  ulPlatक्रमmTDC;
      ULONG  ulSmallACPlatक्रमmTDC;
      ULONG  ulApuTDP;
      ULONG  ulDGpuTDP;  
      ULONG  ulDGpuUlvPower;
      ULONG  ulTjmax;
पूर्ण ATOM_PPLIB_PPM_Table;

#घोषणा    VQ_DisplayConfig_NoneAWD   1
#घोषणा    VQ_DisplayConfig_AWD       2

प्रकार काष्ठा ATOM_PPLIB_VQ_Budgeting_Recordअणु
    ULONG ulDeviceID;
    ULONG ulSustainableSOCPowerLimitLow; /* in mW */
    ULONG ulSustainableSOCPowerLimitHigh; /* in mW */

    ULONG ulDClk;
    ULONG ulEClk;
    ULONG ulDispSclk;
    UCHAR ucDispConfig;

पूर्ण ATOM_PPLIB_VQ_Budgeting_Record;

प्रकार काष्ठा ATOM_PPLIB_VQ_Budgeting_Table अणु
    UCHAR revid;
    UCHAR numEntries;
    ATOM_PPLIB_VQ_Budgeting_Record         entries[1];
पूर्ण ATOM_PPLIB_VQ_Budgeting_Table;

#आशय pack()

#पूर्ण_अगर
