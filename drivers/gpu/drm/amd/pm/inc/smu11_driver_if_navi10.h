<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 *
 */
#अगर_अघोषित __SMU11_DRIVER_IF_NAVI10_H__
#घोषणा __SMU11_DRIVER_IF_NAVI10_H__

// *** IMPORTANT ***
// SMU TEAM: Always increment the पूर्णांकerface version अगर 
// any काष्ठाure is changed in this file
// Be aware of that the version should be updated in
// smu_v11_0.h, maybe नाम is also needed.
// #घोषणा SMU11_DRIVER_IF_VERSION 0x33

#घोषणा PPTABLE_NV10_SMU_VERSION 8

#घोषणा NUM_GFXCLK_DPM_LEVELS  16
#घोषणा NUM_SMNCLK_DPM_LEVELS  2
#घोषणा NUM_SOCCLK_DPM_LEVELS  8
#घोषणा NUM_MP0CLK_DPM_LEVELS  2
#घोषणा NUM_DCLK_DPM_LEVELS    8
#घोषणा NUM_VCLK_DPM_LEVELS    8
#घोषणा NUM_DCEFCLK_DPM_LEVELS 8
#घोषणा NUM_PHYCLK_DPM_LEVELS  8
#घोषणा NUM_DISPCLK_DPM_LEVELS 8
#घोषणा NUM_PIXCLK_DPM_LEVELS  8
#घोषणा NUM_UCLK_DPM_LEVELS    4 
#घोषणा NUM_MP1CLK_DPM_LEVELS  2
#घोषणा NUM_LINK_LEVELS        2


#घोषणा MAX_GFXCLK_DPM_LEVEL  (NUM_GFXCLK_DPM_LEVELS  - 1)
#घोषणा MAX_SMNCLK_DPM_LEVEL  (NUM_SMNCLK_DPM_LEVELS  - 1)
#घोषणा MAX_SOCCLK_DPM_LEVEL  (NUM_SOCCLK_DPM_LEVELS  - 1)
#घोषणा MAX_MP0CLK_DPM_LEVEL  (NUM_MP0CLK_DPM_LEVELS  - 1)
#घोषणा MAX_DCLK_DPM_LEVEL    (NUM_DCLK_DPM_LEVELS    - 1)
#घोषणा MAX_VCLK_DPM_LEVEL    (NUM_VCLK_DPM_LEVELS    - 1)
#घोषणा MAX_DCEFCLK_DPM_LEVEL (NUM_DCEFCLK_DPM_LEVELS - 1)
#घोषणा MAX_DISPCLK_DPM_LEVEL (NUM_DISPCLK_DPM_LEVELS - 1)
#घोषणा MAX_PIXCLK_DPM_LEVEL  (NUM_PIXCLK_DPM_LEVELS  - 1)
#घोषणा MAX_PHYCLK_DPM_LEVEL  (NUM_PHYCLK_DPM_LEVELS  - 1)
#घोषणा MAX_UCLK_DPM_LEVEL    (NUM_UCLK_DPM_LEVELS    - 1)
#घोषणा MAX_MP1CLK_DPM_LEVEL  (NUM_MP1CLK_DPM_LEVELS  - 1)
#घोषणा MAX_LINK_LEVEL        (NUM_LINK_LEVELS        - 1)

//Gemini Modes
#घोषणा PPSMC_GeminiModeNone   0  //Single GPU board
#घोषणा PPSMC_GeminiModeMaster 1  //Master GPU on a Gemini board
#घोषणा PPSMC_GeminiModeSlave  2  //Slave GPU on a Gemini board

// Feature Control Defines
// DPM
#घोषणा FEATURE_DPM_PREFETCHER_BIT      0
#घोषणा FEATURE_DPM_GFXCLK_BIT          1
#घोषणा FEATURE_DPM_GFX_PACE_BIT        2
#घोषणा FEATURE_DPM_UCLK_BIT            3
#घोषणा FEATURE_DPM_SOCCLK_BIT          4
#घोषणा FEATURE_DPM_MP0CLK_BIT          5
#घोषणा FEATURE_DPM_LINK_BIT            6
#घोषणा FEATURE_DPM_DCEFCLK_BIT         7
#घोषणा FEATURE_MEM_VDDCI_SCALING_BIT   8 
#घोषणा FEATURE_MEM_MVDD_SCALING_BIT    9
                                        
//Idle                                  
#घोषणा FEATURE_DS_GFXCLK_BIT           10
#घोषणा FEATURE_DS_SOCCLK_BIT           11
#घोषणा FEATURE_DS_LCLK_BIT             12
#घोषणा FEATURE_DS_DCEFCLK_BIT          13
#घोषणा FEATURE_DS_UCLK_BIT             14
#घोषणा FEATURE_GFX_ULV_BIT             15  
#घोषणा FEATURE_FW_DSTATE_BIT           16 
#घोषणा FEATURE_GFXOFF_BIT              17
#घोषणा FEATURE_BACO_BIT                18
#घोषणा FEATURE_VCN_PG_BIT              19  
#घोषणा FEATURE_JPEG_PG_BIT             20
#घोषणा FEATURE_USB_PG_BIT              21
#घोषणा FEATURE_RSMU_SMN_CG_BIT         22
//Throttler/Response                    
#घोषणा FEATURE_PPT_BIT                 23
#घोषणा FEATURE_TDC_BIT                 24
#घोषणा FEATURE_GFX_EDC_BIT             25
#घोषणा FEATURE_APCC_PLUS_BIT           26
#घोषणा FEATURE_GTHR_BIT                27
#घोषणा FEATURE_ACDC_BIT                28
#घोषणा FEATURE_VR0HOT_BIT              29
#घोषणा FEATURE_VR1HOT_BIT              30  
#घोषणा FEATURE_FW_CTF_BIT              31
#घोषणा FEATURE_FAN_CONTROL_BIT         32
#घोषणा FEATURE_THERMAL_BIT             33
#घोषणा FEATURE_GFX_DCS_BIT             34
//VF                                    
#घोषणा FEATURE_RM_BIT                  35
#घोषणा FEATURE_LED_DISPLAY_BIT         36
//Other                                 
#घोषणा FEATURE_GFX_SS_BIT              37
#घोषणा FEATURE_OUT_OF_BAND_MONITOR_BIT 38
#घोषणा FEATURE_TEMP_DEPENDENT_VMIN_BIT 39

#घोषणा FEATURE_MMHUB_PG_BIT            40
#घोषणा FEATURE_ATHUB_PG_BIT            41
#घोषणा FEATURE_APCC_DFLL_BIT           42
#घोषणा FEATURE_SPARE_43_BIT            43
#घोषणा FEATURE_SPARE_44_BIT            44
#घोषणा FEATURE_SPARE_45_BIT            45
#घोषणा FEATURE_SPARE_46_BIT            46
#घोषणा FEATURE_SPARE_47_BIT            47
#घोषणा FEATURE_SPARE_48_BIT            48
#घोषणा FEATURE_SPARE_49_BIT            49
#घोषणा FEATURE_SPARE_50_BIT            50
#घोषणा FEATURE_SPARE_51_BIT            51
#घोषणा FEATURE_SPARE_52_BIT            52
#घोषणा FEATURE_SPARE_53_BIT            53
#घोषणा FEATURE_SPARE_54_BIT            54
#घोषणा FEATURE_SPARE_55_BIT            55
#घोषणा FEATURE_SPARE_56_BIT            56
#घोषणा FEATURE_SPARE_57_BIT            57
#घोषणा FEATURE_SPARE_58_BIT            58
#घोषणा FEATURE_SPARE_59_BIT            59
#घोषणा FEATURE_SPARE_60_BIT            60
#घोषणा FEATURE_SPARE_61_BIT            61
#घोषणा FEATURE_SPARE_62_BIT            62
#घोषणा FEATURE_SPARE_63_BIT            63
#घोषणा NUM_FEATURES                    64

// Debug Overrides Biपंचांगask
#घोषणा DPM_OVERRIDE_DISABLE_SOCCLK_PID             0x00000001
#घोषणा DPM_OVERRIDE_DISABLE_UCLK_PID               0x00000002
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_VCN_SOCCLK   0x00000004
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_VCLK_SOCCLK   0x00000008
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_DCLK_SOCCLK   0x00000010
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_SOCCLK 0x00000020
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_UCLK   0x00000040
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_DCE_SOCCLK   0x00000080
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_MP0_SOCCLK   0x00000100
#घोषणा DPM_OVERRIDE_DISABLE_DFLL_PLL_SHUTDOWN      0x00000200
#घोषणा DPM_OVERRIDE_DISABLE_MEMORY_TEMPERATURE_READ 0x00000400

// VR Mapping Bit Defines
#घोषणा VR_MAPPING_VR_SELECT_MASK  0x01
#घोषणा VR_MAPPING_VR_SELECT_SHIFT 0x00

#घोषणा VR_MAPPING_PLANE_SELECT_MASK  0x02
#घोषणा VR_MAPPING_PLANE_SELECT_SHIFT 0x01

// PSI Bit Defines
#घोषणा PSI_SEL_VR0_PLANE0_PSI0  0x01
#घोषणा PSI_SEL_VR0_PLANE0_PSI1  0x02
#घोषणा PSI_SEL_VR0_PLANE1_PSI0  0x04
#घोषणा PSI_SEL_VR0_PLANE1_PSI1  0x08
#घोषणा PSI_SEL_VR1_PLANE0_PSI0  0x10
#घोषणा PSI_SEL_VR1_PLANE0_PSI1  0x20
#घोषणा PSI_SEL_VR1_PLANE1_PSI0  0x40
#घोषणा PSI_SEL_VR1_PLANE1_PSI1  0x80

// Throttler Control/Status Bits
#घोषणा THROTTLER_PADDING_BIT      0
#घोषणा THROTTLER_TEMP_EDGE_BIT    1
#घोषणा THROTTLER_TEMP_HOTSPOT_BIT 2
#घोषणा THROTTLER_TEMP_MEM_BIT     3
#घोषणा THROTTLER_TEMP_VR_GFX_BIT  4
#घोषणा THROTTLER_TEMP_VR_MEM0_BIT 5
#घोषणा THROTTLER_TEMP_VR_MEM1_BIT 6
#घोषणा THROTTLER_TEMP_VR_SOC_BIT  7
#घोषणा THROTTLER_TEMP_LIQUID0_BIT 8
#घोषणा THROTTLER_TEMP_LIQUID1_BIT 9
#घोषणा THROTTLER_TEMP_PLX_BIT     10
#घोषणा THROTTLER_TEMP_SKIN_BIT    11
#घोषणा THROTTLER_TDC_GFX_BIT      12
#घोषणा THROTTLER_TDC_SOC_BIT      13
#घोषणा THROTTLER_PPT0_BIT         14
#घोषणा THROTTLER_PPT1_BIT         15
#घोषणा THROTTLER_PPT2_BIT         16
#घोषणा THROTTLER_PPT3_BIT         17
#घोषणा THROTTLER_FIT_BIT          18
#घोषणा THROTTLER_PPM_BIT          19
#घोषणा THROTTLER_APCC_BIT         20

// FW DState Features Control Bits
#घोषणा FW_DSTATE_SOC_ULV_BIT              0
#घोषणा FW_DSTATE_G6_HSR_BIT               1
#घोषणा FW_DSTATE_G6_PHY_VDDCI_OFF_BIT     2
#घोषणा FW_DSTATE_MP0_DS_BIT               3
#घोषणा FW_DSTATE_SMN_DS_BIT               4
#घोषणा FW_DSTATE_MP1_DS_BIT               5
#घोषणा FW_DSTATE_MP1_WHISPER_MODE_BIT     6
#घोषणा FW_DSTATE_LIV_MIN_BIT              7
#घोषणा FW_DSTATE_SOC_PLL_PWRDN_BIT        8   

#घोषणा FW_DSTATE_SOC_ULV_MASK             (1 << FW_DSTATE_SOC_ULV_BIT          )
#घोषणा FW_DSTATE_G6_HSR_MASK              (1 << FW_DSTATE_G6_HSR_BIT           )
#घोषणा FW_DSTATE_G6_PHY_VDDCI_OFF_MASK    (1 << FW_DSTATE_G6_PHY_VDDCI_OFF_BIT )
#घोषणा FW_DSTATE_MP1_DS_MASK              (1 << FW_DSTATE_MP1_DS_BIT           )  
#घोषणा FW_DSTATE_MP0_DS_MASK              (1 << FW_DSTATE_MP0_DS_BIT           )   
#घोषणा FW_DSTATE_SMN_DS_MASK              (1 << FW_DSTATE_SMN_DS_BIT           )
#घोषणा FW_DSTATE_MP1_WHISPER_MODE_MASK    (1 << FW_DSTATE_MP1_WHISPER_MODE_BIT )
#घोषणा FW_DSTATE_LIV_MIN_MASK             (1 << FW_DSTATE_LIV_MIN_BIT          )
#घोषणा FW_DSTATE_SOC_PLL_PWRDN_MASK       (1 << FW_DSTATE_SOC_PLL_PWRDN_BIT    )

//I2C Interface

#घोषणा NUM_I2C_CONTROLLERS                8

#घोषणा I2C_CONTROLLER_ENABLED             1
#घोषणा I2C_CONTROLLER_DISABLED            0

#घोषणा MAX_SW_I2C_COMMANDS                8

प्रकार क्रमागत अणु
  I2C_CONTROLLER_PORT_0 = 0,  //CKSVII2C0
  I2C_CONTROLLER_PORT_1 = 1,  //CKSVII2C1
  I2C_CONTROLLER_PORT_COUNT,
पूर्ण I2cControllerPort_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_NAME_VR_GFX = 0,
  I2C_CONTROLLER_NAME_VR_SOC,
  I2C_CONTROLLER_NAME_VR_VDDCI,
  I2C_CONTROLLER_NAME_VR_MVDD,
  I2C_CONTROLLER_NAME_LIQUID0,
  I2C_CONTROLLER_NAME_LIQUID1,  
  I2C_CONTROLLER_NAME_PLX,
  I2C_CONTROLLER_NAME_SPARE,
  I2C_CONTROLLER_NAME_COUNT,  
पूर्ण I2cControllerName_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_THROTTLER_TYPE_NONE = 0,
  I2C_CONTROLLER_THROTTLER_VR_GFX,
  I2C_CONTROLLER_THROTTLER_VR_SOC,
  I2C_CONTROLLER_THROTTLER_VR_VDDCI,
  I2C_CONTROLLER_THROTTLER_VR_MVDD,
  I2C_CONTROLLER_THROTTLER_LIQUID0,
  I2C_CONTROLLER_THROTTLER_LIQUID1,  
  I2C_CONTROLLER_THROTTLER_PLX,
  I2C_CONTROLLER_THROTTLER_COUNT,  
पूर्ण I2cControllerThrottler_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_PROTOCOL_VR_0,
  I2C_CONTROLLER_PROTOCOL_VR_1,
  I2C_CONTROLLER_PROTOCOL_TMP_0,
  I2C_CONTROLLER_PROTOCOL_TMP_1,
  I2C_CONTROLLER_PROTOCOL_SPARE_0,
  I2C_CONTROLLER_PROTOCOL_SPARE_1,
  I2C_CONTROLLER_PROTOCOL_COUNT,  
पूर्ण I2cControllerProtocol_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t   Enabled;
  uपूर्णांक8_t   Speed;
  uपूर्णांक8_t   Padding[2];
  uपूर्णांक32_t  SlaveAddress;
  uपूर्णांक8_t   ControllerPort;
  uपूर्णांक8_t   ControllerName;
  uपूर्णांक8_t   ThermalThrotter;
  uपूर्णांक8_t   I2cProtocol;
पूर्ण I2cControllerConfig_t;

प्रकार क्रमागत अणु
  I2C_PORT_SVD_SCL = 0,  
  I2C_PORT_GPIO,      
पूर्ण I2cPort_e; 

प्रकार क्रमागत अणु
  I2C_SPEED_FAST_50K = 0,      //50  Kbits/s
  I2C_SPEED_FAST_100K,         //100 Kbits/s
  I2C_SPEED_FAST_400K,         //400 Kbits/s
  I2C_SPEED_FAST_PLUS_1M,      //1   Mbits/s (in fast mode)
  I2C_SPEED_HIGH_1M,           //1   Mbits/s (in high speed mode)
  I2C_SPEED_HIGH_2M,           //2.3 Mbits/s  
  I2C_SPEED_COUNT,  
पूर्ण I2cSpeed_e;

प्रकार क्रमागत अणु
  I2C_CMD_READ = 0,
  I2C_CMD_WRITE,
  I2C_CMD_COUNT,  
पूर्ण I2cCmdType_e;

#घोषणा CMDCONFIG_STOP_BIT      0
#घोषणा CMDCONFIG_RESTART_BIT   1

#घोषणा CMDCONFIG_STOP_MASK     (1 << CMDCONFIG_STOP_BIT)
#घोषणा CMDCONFIG_RESTART_MASK  (1 << CMDCONFIG_RESTART_BIT)

प्रकार काष्ठा अणु
  uपूर्णांक8_t RegisterAddr; ////only valid क्रम ग_लिखो, ignored क्रम पढ़ो
  uपूर्णांक8_t Cmd;  //Read(0) or Write(1) 
  uपूर्णांक8_t Data;  //Return data क्रम पढ़ो. Data to send क्रम ग_लिखो
  uपूर्णांक8_t CmdConfig; //Includes whether associated command should have a stop or restart command
पूर्ण SwI2cCmd_t; //SW I2C Command Table

प्रकार काष्ठा अणु
  uपूर्णांक8_t     I2CcontrollerPort; //CKSVII2C0(0) or //CKSVII2C1(1)
  uपूर्णांक8_t     I2CSpeed;          //Slow(0) or Fast(1)
  uपूर्णांक16_t    SlaveAddress;
  uपूर्णांक8_t     NumCmds;           //Number of commands
  uपूर्णांक8_t     Padding[3];

  SwI2cCmd_t  SwI2cCmds[MAX_SW_I2C_COMMANDS];

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
  
पूर्ण SwI2cRequest_t; // SW I2C Request Table

//D3HOT sequences
प्रकार क्रमागत अणु
  BACO_SEQUENCE,
  MSR_SEQUENCE,
  BAMACO_SEQUENCE,
  ULPS_SEQUENCE,
  D3HOT_SEQUENCE_COUNT,
पूर्णD3HOTSequence_e;

//THis is aligned with RSMU PGFSM Register Mapping
प्रकार क्रमागत अणु
  PG_DYNAMIC_MODE = 0,
  PG_STATIC_MODE,
पूर्ण PowerGatingMode_e;

//This is aligned with RSMU PGFSM Register Mapping
प्रकार क्रमागत अणु
  PG_POWER_DOWN = 0,
  PG_POWER_UP,
पूर्ण PowerGatingSettings_e;

प्रकार काष्ठा अणु            
  uपूर्णांक32_t a;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t b;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t c;  // store in IEEE भग्न क्रमmat in this variable
पूर्ण QuadraticInt_t;

प्रकार काष्ठा अणु            
  uपूर्णांक32_t m;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t b;  // store in IEEE भग्न क्रमmat in this variable
पूर्ण LinearInt_t;

प्रकार काष्ठा अणु            
  uपूर्णांक32_t a;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t b;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t c;  // store in IEEE भग्न क्रमmat in this variable
पूर्ण DroopInt_t;

प्रकार क्रमागत अणु
  GFXCLK_SOURCE_PLL = 0, 
  GFXCLK_SOURCE_DFLL, 
  GFXCLK_SOURCE_COUNT, 
पूर्ण GfxclkSrc_e; 

//Only Clks that have DPM descriptors are listed here 
प्रकार क्रमागत अणु
  PPCLK_GFXCLK = 0,
  PPCLK_SOCCLK,
  PPCLK_UCLK,
  PPCLK_DCLK,
  PPCLK_VCLK,
  PPCLK_DCEFCLK,
  PPCLK_DISPCLK,
  PPCLK_PIXCLK,
  PPCLK_PHYCLK,
  PPCLK_COUNT,
पूर्ण PPCLK_e;

प्रकार क्रमागत अणु
  POWER_SOURCE_AC,
  POWER_SOURCE_DC,
  POWER_SOURCE_COUNT,
पूर्ण POWER_SOURCE_e;

प्रकार क्रमागत  अणु
  PPT_THROTTLER_PPT0,
  PPT_THROTTLER_PPT1,
  PPT_THROTTLER_PPT2,
  PPT_THROTTLER_PPT3,       
  PPT_THROTTLER_COUNT
पूर्ण PPT_THROTTLER_e;

प्रकार क्रमागत अणु
  VOLTAGE_MODE_AVFS = 0,
  VOLTAGE_MODE_AVFS_SS,
  VOLTAGE_MODE_SS,
  VOLTAGE_MODE_COUNT,
पूर्ण VOLTAGE_MODE_e;


प्रकार क्रमागत अणु
  AVFS_VOLTAGE_GFX = 0,
  AVFS_VOLTAGE_SOC,
  AVFS_VOLTAGE_COUNT,
पूर्ण AVFS_VOLTAGE_TYPE_e;

प्रकार क्रमागत अणु
  UCLK_DIV_BY_1 = 0,
  UCLK_DIV_BY_2,
  UCLK_DIV_BY_4,
  UCLK_DIV_BY_8,
पूर्ण UCLK_DIV_e;

प्रकार क्रमागत अणु
  GPIO_INT_POLARITY_ACTIVE_LOW = 0,
  GPIO_INT_POLARITY_ACTIVE_HIGH,
पूर्ण GpioIntPolarity_e;

प्रकार क्रमागत अणु
  MEMORY_TYPE_GDDR6 = 0,
  MEMORY_TYPE_HBM,
पूर्ण MemoryType_e;

प्रकार क्रमागत अणु
  PWR_CONFIG_TDP = 0,
  PWR_CONFIG_TGP,
  PWR_CONFIG_TCP_ESTIMATED,
  PWR_CONFIG_TCP_MEASURED,
पूर्ण PwrConfig_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t        VoltageMode;         // 0 - AVFS only, 1- min(AVFS,SS), 2-SS only
  uपूर्णांक8_t        SnapToDiscrete;      // 0 - Fine grained DPM, 1 - Discrete DPM
  uपूर्णांक8_t        NumDiscreteLevels;   // Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used
  uपूर्णांक8_t        Padding;         
  LinearInt_t    ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
  QuadraticInt_t SsCurve;             // Slow-slow curve (GHz->V)
पूर्ण DpmDescriptor_t;

प्रकार क्रमागत  अणु
  TEMP_EDGE,
  TEMP_HOTSPOT,
  TEMP_MEM,
  TEMP_VR_GFX,
  TEMP_VR_MEM0,
  TEMP_VR_MEM1,
  TEMP_VR_SOC,  
  TEMP_LIQUID0,
  TEMP_LIQUID1,  
  TEMP_PLX,
  TEMP_COUNT
पूर्ण TEMP_e;

//Out of band monitor status defines
//see SPEC //gpu/करोc/soc_arch/spec/feature/SMBUS/SMBUS.xlsx
#घोषणा POWER_MANAGER_CONTROLLER_NOT_RUNNING 0
#घोषणा POWER_MANAGER_CONTROLLER_RUNNING     1

#घोषणा POWER_MANAGER_CONTROLLER_BIT                             0
#घोषणा MAXIMUM_DPM_STATE_GFX_ENGINE_RESTRICTED_BIT              8
#घोषणा GPU_DIE_TEMPERATURE_THROTTLING_BIT                       9
#घोषणा HBM_DIE_TEMPERATURE_THROTTLING_BIT                       10
#घोषणा TGP_THROTTLING_BIT                                       11
#घोषणा PCC_THROTTLING_BIT                                       12
#घोषणा HBM_TEMPERATURE_EXCEEDING_TEMPERATURE_LIMIT_BIT          13
#घोषणा HBM_TEMPERATURE_EXCEEDING_MAX_MEMORY_TEMPERATURE_BIT     14

#घोषणा POWER_MANAGER_CONTROLLER_MASK                            (1 << POWER_MANAGER_CONTROLLER_BIT                        ) 
#घोषणा MAXIMUM_DPM_STATE_GFX_ENGINE_RESTRICTED_MASK             (1 << MAXIMUM_DPM_STATE_GFX_ENGINE_RESTRICTED_BIT         )
#घोषणा GPU_DIE_TEMPERATURE_THROTTLING_MASK                      (1 << GPU_DIE_TEMPERATURE_THROTTLING_BIT                  ) 
#घोषणा HBM_DIE_TEMPERATURE_THROTTLING_MASK                      (1 << HBM_DIE_TEMPERATURE_THROTTLING_BIT                  )
#घोषणा TGP_THROTTLING_MASK                                      (1 << TGP_THROTTLING_BIT                                  )
#घोषणा PCC_THROTTLING_MASK                                      (1 << PCC_THROTTLING_BIT                                  )
#घोषणा HBM_TEMPERATURE_EXCEEDING_TEMPERATURE_LIMIT_MASK         (1 << HBM_TEMPERATURE_EXCEEDING_TEMPERATURE_LIMIT_BIT     )
#घोषणा HBM_TEMPERATURE_EXCEEDING_MAX_MEMORY_TEMPERATURE_MASK    (1 << HBM_TEMPERATURE_EXCEEDING_MAX_MEMORY_TEMPERATURE_BIT) 

//This काष्ठाure to be DMA to SMBUS Config रेजिस्टर space
प्रकार काष्ठा अणु
  uपूर्णांक8_t  MinorInfoVersion;
  uपूर्णांक8_t  MajorInfoVersion;
  uपूर्णांक8_t  TableSize;
  uपूर्णांक8_t  Reserved;

  uपूर्णांक8_t  Reserved1;
  uपूर्णांक8_t  RevID;
  uपूर्णांक16_t DeviceID;

  uपूर्णांक16_t DieTemperatureLimit;
  uपूर्णांक16_t FanTargetTemperature;

  uपूर्णांक16_t MemoryTemperatureLimit;
  uपूर्णांक16_t MemoryTemperatureLimit1;

  uपूर्णांक16_t TGP;
  uपूर्णांक16_t CardPower;

  uपूर्णांक32_t DieTemperatureRegisterOffset;

  uपूर्णांक32_t Reserved2;
  
  uपूर्णांक32_t Reserved3;

  uपूर्णांक32_t Status;

  uपूर्णांक16_t DieTemperature;
  uपूर्णांक16_t CurrentMemoryTemperature;

  uपूर्णांक16_t MemoryTemperature;
  uपूर्णांक8_t MemoryHotspotPosition;
  uपूर्णांक8_t Reserved4;

  uपूर्णांक32_t BoardLevelEnergyAccumulator;  
पूर्ण OutOfBandMonitor_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t Version;

  // SECTION: Feature Enablement
  uपूर्णांक32_t FeaturesToRun[2];

  // SECTION: Infraकाष्ठाure Limits
  uपूर्णांक16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT];
  uपूर्णांक16_t SocketPowerLimitAcTau[PPT_THROTTLER_COUNT];
  uपूर्णांक16_t SocketPowerLimitDc[PPT_THROTTLER_COUNT];
  uपूर्णांक16_t SocketPowerLimitDcTau[PPT_THROTTLER_COUNT];  

  uपूर्णांक16_t TdcLimitSoc;             // Amps
  uपूर्णांक16_t TdcLimitSocTau;          // Time स्थिरant of LPF in ms
  uपूर्णांक16_t TdcLimitGfx;             // Amps
  uपूर्णांक16_t TdcLimitGfxTau;          // Time स्थिरant of LPF in ms
  
  uपूर्णांक16_t TedgeLimit;              // Celcius
  uपूर्णांक16_t ThotspotLimit;           // Celcius
  uपूर्णांक16_t TmemLimit;               // Celcius
  uपूर्णांक16_t Tvr_gfxLimit;            // Celcius
  uपूर्णांक16_t Tvr_mem0Limit;           // Celcius
  uपूर्णांक16_t Tvr_mem1Limit;           // Celcius  
  uपूर्णांक16_t Tvr_socLimit;            // Celcius
  uपूर्णांक16_t Tliquid0Limit;           // Celcius
  uपूर्णांक16_t Tliquid1Limit;           // Celcius
  uपूर्णांक16_t TplxLimit;               // Celcius
  uपूर्णांक32_t FitLimit;                // Failures in समय (failures per million parts over the defined lअगरeसमय)

  uपूर्णांक16_t PpmPowerLimit;           // Switch this this घातer limit when temperature is above PpmTempThreshold
  uपूर्णांक16_t PpmTemperatureThreshold;
  
  // SECTION: Throttler settings
  uपूर्णांक32_t ThrottlerControlMask;   // See Throtter masks defines

  // SECTION: FW DSTATE Settings  
  uपूर्णांक32_t FwDStateMask;           // See FW DState masks defines

  // SECTION: ULV Settings
  uपूर्णांक16_t  UlvVoltageOffsetSoc; // In mV(Q2)
  uपूर्णांक16_t  UlvVoltageOffsetGfx; // In mV(Q2)

  uपूर्णांक8_t   GceaLinkMgrIdleThreshold;        //Set by SMU FW during enablment of SOC_ULV. Controls delay क्रम GFX SDP port disconnection during idle events
  uपूर्णांक8_t   paddingRlcUlvParams[3];
  
  uपूर्णांक8_t  UlvSmnclkDid;     //DID क्रम ULV mode. 0 means CLK will not be modअगरied in ULV.
  uपूर्णांक8_t  UlvMp1clkDid;     //DID क्रम ULV mode. 0 means CLK will not be modअगरied in ULV.
  uपूर्णांक8_t  UlvGfxclkBypass;  // 1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV
  uपूर्णांक8_t  Padding234;

  uपूर्णांक16_t     MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode 
  uपूर्णांक16_t     MinVoltageUlvSoc; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_SOC in ULV mode


  // SECTION: Voltage Control Parameters
  uपूर्णांक16_t     MinVoltageGfx;     // In mV(Q2) Minimum Voltage ("Vmin") of VDD_GFX
  uपूर्णांक16_t     MinVoltageSoc;     // In mV(Q2) Minimum Voltage ("Vmin") of VDD_SOC
  uपूर्णांक16_t     MaxVoltageGfx;     // In mV(Q2) Maximum Voltage allowable of VDD_GFX
  uपूर्णांक16_t     MaxVoltageSoc;     // In mV(Q2) Maximum Voltage allowable of VDD_SOC

  uपूर्णांक16_t     LoadLineResistanceGfx;   // In mOhms with 8 fractional bits
  uपूर्णांक16_t     LoadLineResistanceSoc;   // In mOhms with 8 fractional bits

  //SECTION: DPM Config 1
  DpmDescriptor_t DpmDescriptor[PPCLK_COUNT];

  uपूर्णांक16_t       FreqTableGfx      [NUM_GFXCLK_DPM_LEVELS  ];     // In MHz
  uपूर्णांक16_t       FreqTableVclk     [NUM_VCLK_DPM_LEVELS    ];     // In MHz
  uपूर्णांक16_t       FreqTableDclk     [NUM_DCLK_DPM_LEVELS    ];     // In MHz
  uपूर्णांक16_t       FreqTableSocclk   [NUM_SOCCLK_DPM_LEVELS  ];     // In MHz
  uपूर्णांक16_t       FreqTableUclk     [NUM_UCLK_DPM_LEVELS    ];     // In MHz
  uपूर्णांक16_t       FreqTableDcefclk  [NUM_DCEFCLK_DPM_LEVELS ];     // In MHz
  uपूर्णांक16_t       FreqTableDispclk  [NUM_DISPCLK_DPM_LEVELS ];     // In MHz
  uपूर्णांक16_t       FreqTablePixclk   [NUM_PIXCLK_DPM_LEVELS  ];     // In MHz
  uपूर्णांक16_t       FreqTablePhyclk   [NUM_PHYCLK_DPM_LEVELS  ];     // In MHz
  uपूर्णांक32_t       Paddingclks[16];

  uपूर्णांक16_t       DcModeMaxFreq     [PPCLK_COUNT            ];     // In MHz
  uपूर्णांक16_t       Padding8_Clks;
  
  uपूर्णांक8_t        FreqTableUclkDiv  [NUM_UCLK_DPM_LEVELS    ];     // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8

  // SECTION: DPM Config 2
  uपूर्णांक16_t       Mp0clkFreq        [NUM_MP0CLK_DPM_LEVELS];       // in MHz
  uपूर्णांक16_t       Mp0DpmVoltage     [NUM_MP0CLK_DPM_LEVELS];       // mV(Q2)
  uपूर्णांक16_t       MemVddciVoltage   [NUM_UCLK_DPM_LEVELS];         // mV(Q2)
  uपूर्णांक16_t       MemMvddVoltage    [NUM_UCLK_DPM_LEVELS];         // mV(Q2)
  // GFXCLK DPM
  uपूर्णांक16_t        GfxclkFgfxoffEntry;   // in Mhz
  uपूर्णांक16_t        GfxclkFinit;          // in Mhz 
  uपूर्णांक16_t        GfxclkFidle;          // in MHz
  uपूर्णांक16_t        GfxclkSlewRate;       // क्रम PLL babystepping???
  uपूर्णांक16_t        GfxclkFopt;           // in Mhz
  uपूर्णांक8_t         Padding567[2]; 
  uपूर्णांक16_t        GfxclkDsMaxFreq;      // in MHz
  uपूर्णांक8_t         GfxclkSource;         // 0 = PLL, 1 = DFLL
  uपूर्णांक8_t         Padding456;

  // UCLK section
  uपूर्णांक8_t      LowestUclkReservedForUlv; // Set this to 1 अगर UCLK DPM0 is reserved क्रम ULV-mode only
  uपूर्णांक8_t      paddingUclk[3];
  
  uपूर्णांक8_t      MemoryType;          // 0-GDDR6, 1-HBM
  uपूर्णांक8_t      MemoryChannels;
  uपूर्णांक8_t      PaddingMem[2];

  // Link DPM Settings
  uपूर्णांक8_t      PcieGenSpeed[NUM_LINK_LEVELS];           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
  uपूर्णांक8_t      PcieLaneCount[NUM_LINK_LEVELS];          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
  uपूर्णांक16_t     LclkFreq[NUM_LINK_LEVELS];              

  // GFXCLK Thermal DPM (क्रमmerly 'Boost' Settings)
  uपूर्णांक16_t     EnableTdpm;      
  uपूर्णांक16_t     TdpmHighHystTemperature;
  uपूर्णांक16_t     TdpmLowHystTemperature;
  uपूर्णांक16_t     GfxclkFreqHighTempLimit; // High limit on GFXCLK when temperature is high, क्रम reliability.
 
  // SECTION: Fan Control
  uपूर्णांक16_t     FanStopTemp;          //Celcius
  uपूर्णांक16_t     FanStartTemp;         //Celcius

  uपूर्णांक16_t     FanGainEdge;
  uपूर्णांक16_t     FanGainHotspot;
  uपूर्णांक16_t     FanGainLiquid0;
  uपूर्णांक16_t     FanGainLiquid1;  
  uपूर्णांक16_t     FanGainVrGfx;
  uपूर्णांक16_t     FanGainVrSoc;
  uपूर्णांक16_t     FanGainVrMem0;
  uपूर्णांक16_t     FanGainVrMem1;  
  uपूर्णांक16_t     FanGainPlx;
  uपूर्णांक16_t     FanGainMem;
  uपूर्णांक16_t     FanPwmMin;
  uपूर्णांक16_t     FanAcousticLimitRpm;
  uपूर्णांक16_t     FanThrottlingRpm;
  uपूर्णांक16_t     FanMaximumRpm;
  uपूर्णांक16_t     FanTargetTemperature;
  uपूर्णांक16_t     FanTargetGfxclk;
  uपूर्णांक8_t      FanTempInputSelect;
  uपूर्णांक8_t      FanPadding;
  uपूर्णांक8_t      FanZeroRpmEnable; 
  uपूर्णांक8_t      FanTachEdgePerRev;
  //uपूर्णांक8_t      padding8_Fan[2];
    
  // The following are AFC override parameters. Leave at 0 to use FW शेषs.
  पूर्णांक16_t      FuzzyFan_ErrorSetDelta;
  पूर्णांक16_t      FuzzyFan_ErrorRateSetDelta;
  पूर्णांक16_t      FuzzyFan_PwmSetDelta;
  uपूर्णांक16_t     FuzzyFan_Reserved;


  // SECTION: AVFS 
  // Overrides
  uपूर्णांक8_t           OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t           Padding8_Avfs[2];

  QuadraticInt_t    qAvfsGb[AVFS_VOLTAGE_COUNT];              // GHz->V Override of fused curve 
  DroopInt_t        dBtcGbGfxPll;         // GHz->V BtcGb
  DroopInt_t        dBtcGbGfxDfll;        // GHz->V BtcGb
  DroopInt_t        dBtcGbSoc;            // GHz->V BtcGb
  LinearInt_t       qAgingGb[AVFS_VOLTAGE_COUNT];          // GHz->V 

  QuadraticInt_t    qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V 

  uपूर्णांक16_t          DcTol[AVFS_VOLTAGE_COUNT];            // mV Q2

  uपूर्णांक8_t           DcBtcEnabled[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t           Padding8_GfxBtc[2];

  uपूर्णांक16_t          DcBtcMin[AVFS_VOLTAGE_COUNT];       // mV Q2
  uपूर्णांक16_t          DcBtcMax[AVFS_VOLTAGE_COUNT];       // mV Q2

  // SECTION: Advanced Options
  uपूर्णांक32_t          DebugOverrides;
  QuadraticInt_t    ReservedEquation0; 
  QuadraticInt_t    ReservedEquation1; 
  QuadraticInt_t    ReservedEquation2; 
  QuadraticInt_t    ReservedEquation3; 
  
  // Total Power configuration, use defines from PwrConfig_e
  uपूर्णांक8_t      TotalPowerConfig;    //0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measured
  uपूर्णांक8_t      TotalPowerSpare1;  
  uपूर्णांक16_t     TotalPowerSpare2;

  // APCC Settings
  uपूर्णांक16_t     PccThresholdLow;
  uपूर्णांक16_t     PccThresholdHigh;
  uपूर्णांक32_t     MGpuFanBoostLimitRpm;
  uपूर्णांक32_t     PaddingAPCC[5];

  // Temperature Dependent Vmin
  uपूर्णांक16_t     VDDGFX_TVmin;       //Celcius
  uपूर्णांक16_t     VDDSOC_TVmin;       //Celcius
  uपूर्णांक16_t     VDDGFX_Vmin_HiTemp; // mV Q2
  uपूर्णांक16_t     VDDGFX_Vmin_LoTemp; // mV Q2
  uपूर्णांक16_t     VDDSOC_Vmin_HiTemp; // mV Q2
  uपूर्णांक16_t     VDDSOC_Vmin_LoTemp; // mV Q2
  
  uपूर्णांक16_t     VDDGFX_TVminHystersis; // Celcius
  uपूर्णांक16_t     VDDSOC_TVminHystersis; // Celcius

  // BTC Setting
  uपूर्णांक32_t     BtcConfig;
  
  uपूर्णांक16_t     SsFmin[10]; // PPtable value to function similar to VFTFmin क्रम SS Curve; Size is PPCLK_COUNT rounded to nearest multiple of 2
  uपूर्णांक16_t     DcBtcGb[AVFS_VOLTAGE_COUNT];

  // SECTION: Board Reserved
  uपूर्णांक32_t     Reserved[8];

  // SECTION: BOARD PARAMETERS
  // I2C Control
  I2cControllerConfig_t  I2cControllers[NUM_I2C_CONTROLLERS];     

  // SVI2 Board Parameters
  uपूर्णांक16_t     MaxVoltageStepGfx; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.
  uपूर्णांक16_t     MaxVoltageStepSoc; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.
  
  uपूर्णांक8_t      VddGfxVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddSocVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem0VrMapping;  // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem1VrMapping;  // Use VR_MAPPING* bitfields

  uपूर्णांक8_t      GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      ExternalSensorPresent; // External RDI connected to TMON (aka TEMP IN)
  uपूर्णांक8_t      Padding8_V; 

  // Telemetry Settings
  uपूर्णांक16_t     GfxMaxCurrent;   // in Amps
  पूर्णांक8_t       GfxOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryGfx;

  uपूर्णांक16_t     SocMaxCurrent;   // in Amps
  पूर्णांक8_t       SocOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetrySoc;

  uपूर्णांक16_t     Mem0MaxCurrent;   // in Amps
  पूर्णांक8_t       Mem0Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem0;
  
  uपूर्णांक16_t     Mem1MaxCurrent;   // in Amps
  पूर्णांक8_t       Mem1Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem1;
  
  // GPIO Settings
  uपूर्णांक8_t      AcDcGpio;        // GPIO pin configured क्रम AC/DC चयनing
  uपूर्णांक8_t      AcDcPolarity;    // GPIO polarity क्रम AC/DC चयनing
  uपूर्णांक8_t      VR0HotGpio;      // GPIO pin configured क्रम VR0 HOT event
  uपूर्णांक8_t      VR0HotPolarity;  // GPIO polarity क्रम VR0 HOT event

  uपूर्णांक8_t      VR1HotGpio;      // GPIO pin configured क्रम VR1 HOT event 
  uपूर्णांक8_t      VR1HotPolarity;  // GPIO polarity क्रम VR1 HOT event 
  uपूर्णांक8_t      GthrGpio;        // GPIO pin configured क्रम GTHR Event
  uपूर्णांक8_t      GthrPolarity;    // replace GPIO polarity क्रम GTHR

  // LED Display Settings
  uपूर्णांक8_t      LedPin0;         // GPIO number क्रम LedPin[0]
  uपूर्णांक8_t      LedPin1;         // GPIO number क्रम LedPin[1]
  uपूर्णांक8_t      LedPin2;         // GPIO number क्रम LedPin[2]
  uपूर्णांक8_t      padding8_4;
 
  // GFXCLK PLL Spपढ़ो Spectrum
  uपूर्णांक8_t      PllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      PllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     PllGfxclkSpपढ़ोFreq;      // kHz

  // GFXCLK DFLL Spपढ़ो Spectrum
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     DfllGfxclkSpपढ़ोFreq;      // kHz
  
  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      UclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      UclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     UclkSpपढ़ोFreq;      // kHz

  // SOCCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      SoclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      SocclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     SocclkSpपढ़ोFreq;      // kHz

  // Total board घातer
  uपूर्णांक16_t     TotalBoardPower;     //Only needed क्रम TCP Estimated हाल, where TCP = TGP+Total Board Power
  uपूर्णांक16_t     BoardPadding; 

  // Mvdd Svi2 Div Ratio Setting
  uपूर्णांक32_t     MvddRatio; // This is used क्रम MVDD Vid workaround. It has 16 fractional bits (Q16.16)

  uपूर्णांक8_t      RenesesLoadLineEnabled;
  uपूर्णांक8_t      GfxLoadlineResistance;
  uपूर्णांक8_t      SocLoadlineResistance;
  uपूर्णांक8_t      Padding8_Loadline;

  uपूर्णांक32_t     BoardReserved[8];

  // Padding क्रम MMHUB - करो not modअगरy this
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use

पूर्ण PPTable_t;

प्रकार काष्ठा अणु
  // Time स्थिरant parameters क्रम घड़ी averages in ms
  uपूर्णांक16_t     GfxclkAverageLpfTau;
  uपूर्णांक16_t     SocclkAverageLpfTau;
  uपूर्णांक16_t     UclkAverageLpfTau;
  uपूर्णांक16_t     GfxActivityLpfTau;
  uपूर्णांक16_t     UclkActivityLpfTau;
  uपूर्णांक16_t     SocketPowerLpfTau;

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण DriverSmuConfig_t;

प्रकार काष्ठा अणु
  
  uपूर्णांक16_t      GfxclkFmin;           // MHz
  uपूर्णांक16_t      GfxclkFmax;           // MHz
  uपूर्णांक16_t      GfxclkFreq1;          // MHz
  uपूर्णांक16_t      GfxclkVolt1;          // mV (Q2)
  uपूर्णांक16_t      GfxclkFreq2;          // MHz
  uपूर्णांक16_t      GfxclkVolt2;          // mV (Q2)
  uपूर्णांक16_t      GfxclkFreq3;          // MHz
  uपूर्णांक16_t      GfxclkVolt3;          // mV (Q2)
  uपूर्णांक16_t      UclkFmax;             // MHz
  पूर्णांक16_t       OverDrivePct;         // %
  uपूर्णांक16_t      FanMaximumRpm;
  uपूर्णांक16_t      FanMinimumPwm;
  uपूर्णांक16_t      FanTargetTemperature; // Degree Celcius 
  uपूर्णांक16_t      FanMode;
  uपूर्णांक16_t      FanMaxPwm;
  uपूर्णांक16_t      FanMinPwm;
  uपूर्णांक16_t      FanMaxTemp; // Degree Celcius
  uपूर्णांक16_t      FanMinTemp; // Degree Celcius
  uपूर्णांक16_t      MaxOpTemp;            // Degree Celcius
  uपूर्णांक16_t      FanZeroRpmEnable;

  uपूर्णांक32_t     MmHubPadding[6]; // SMU पूर्णांकernal use

पूर्ण OverDriveTable_t; 

प्रकार काष्ठा अणु
  uपूर्णांक16_t CurrClock[PPCLK_COUNT];
  uपूर्णांक16_t AverageGfxclkFrequency;
  uपूर्णांक16_t AverageSocclkFrequency;
  uपूर्णांक16_t AverageUclkFrequency  ;
  uपूर्णांक16_t AverageGfxActivity    ;
  uपूर्णांक16_t AverageUclkActivity   ;
  uपूर्णांक8_t  CurrSocVoltageOffset  ;
  uपूर्णांक8_t  CurrGfxVoltageOffset  ;
  uपूर्णांक8_t  CurrMemVidOffset      ;
  uपूर्णांक8_t  Padding8              ;
  uपूर्णांक16_t AverageSocketPower    ;
  uपूर्णांक16_t TemperatureEdge       ;
  uपूर्णांक16_t TemperatureHotspot    ;
  uपूर्णांक16_t TemperatureMem        ;
  uपूर्णांक16_t TemperatureVrGfx      ;
  uपूर्णांक16_t TemperatureVrMem0     ;
  uपूर्णांक16_t TemperatureVrMem1     ;  
  uपूर्णांक16_t TemperatureVrSoc      ;  
  uपूर्णांक16_t TemperatureLiquid0    ;
  uपूर्णांक16_t TemperatureLiquid1    ;  
  uपूर्णांक16_t TemperaturePlx        ;
  uपूर्णांक16_t Padding16             ;
  uपूर्णांक32_t ThrottlerStatus       ; 
 
  uपूर्णांक8_t  LinkDpmLevel;
  uपूर्णांक8_t  Padding8_2;
  uपूर्णांक16_t CurrFanSpeed;

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SmuMetrics_legacy_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t CurrClock[PPCLK_COUNT];
  uपूर्णांक16_t AverageGfxclkFrequencyPostDs;
  uपूर्णांक16_t AverageSocclkFrequency;
  uपूर्णांक16_t AverageUclkFrequencyPostDs;
  uपूर्णांक16_t AverageGfxActivity    ;
  uपूर्णांक16_t AverageUclkActivity   ;
  uपूर्णांक8_t  CurrSocVoltageOffset  ;
  uपूर्णांक8_t  CurrGfxVoltageOffset  ;
  uपूर्णांक8_t  CurrMemVidOffset      ;
  uपूर्णांक8_t  Padding8              ;
  uपूर्णांक16_t AverageSocketPower    ;
  uपूर्णांक16_t TemperatureEdge       ;
  uपूर्णांक16_t TemperatureHotspot    ;
  uपूर्णांक16_t TemperatureMem        ;
  uपूर्णांक16_t TemperatureVrGfx      ;
  uपूर्णांक16_t TemperatureVrMem0     ;
  uपूर्णांक16_t TemperatureVrMem1     ;  
  uपूर्णांक16_t TemperatureVrSoc      ;  
  uपूर्णांक16_t TemperatureLiquid0    ;
  uपूर्णांक16_t TemperatureLiquid1    ;  
  uपूर्णांक16_t TemperaturePlx        ;
  uपूर्णांक16_t Padding16             ;
  uपूर्णांक32_t ThrottlerStatus       ; 
 
  uपूर्णांक8_t  LinkDpmLevel;
  uपूर्णांक8_t  Padding8_2;
  uपूर्णांक16_t CurrFanSpeed;

  uपूर्णांक16_t AverageGfxclkFrequencyPreDs;
  uपूर्णांक16_t AverageUclkFrequencyPreDs;
  uपूर्णांक8_t  PcieRate;
  uपूर्णांक8_t  PcieWidth;
  uपूर्णांक8_t  Padding8_3[2];

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SmuMetrics_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t CurrClock[PPCLK_COUNT];
  uपूर्णांक16_t AverageGfxclkFrequency;
  uपूर्णांक16_t AverageSocclkFrequency;
  uपूर्णांक16_t AverageUclkFrequency  ;
  uपूर्णांक16_t AverageGfxActivity    ;
  uपूर्णांक16_t AverageUclkActivity   ;
  uपूर्णांक8_t  CurrSocVoltageOffset  ;
  uपूर्णांक8_t  CurrGfxVoltageOffset  ;
  uपूर्णांक8_t  CurrMemVidOffset      ;
  uपूर्णांक8_t  Padding8              ;
  uपूर्णांक16_t AverageSocketPower    ;
  uपूर्णांक16_t TemperatureEdge       ;
  uपूर्णांक16_t TemperatureHotspot    ;
  uपूर्णांक16_t TemperatureMem        ;
  uपूर्णांक16_t TemperatureVrGfx      ;
  uपूर्णांक16_t TemperatureVrMem0     ;
  uपूर्णांक16_t TemperatureVrMem1     ;
  uपूर्णांक16_t TemperatureVrSoc      ;
  uपूर्णांक16_t TemperatureLiquid0    ;
  uपूर्णांक16_t TemperatureLiquid1    ;
  uपूर्णांक16_t TemperaturePlx        ;
  uपूर्णांक16_t Padding16             ;
  uपूर्णांक32_t ThrottlerStatus       ;

  uपूर्णांक8_t  LinkDpmLevel;
  uपूर्णांक8_t  Padding8_2;
  uपूर्णांक16_t CurrFanSpeed;

  uपूर्णांक32_t EnergyAccumulator;
  uपूर्णांक16_t AverageVclkFrequency  ;
  uपूर्णांक16_t AverageDclkFrequency  ;
  uपूर्णांक16_t VcnActivityPercentage ;
  uपूर्णांक16_t padding16_2;

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SmuMetrics_NV12_legacy_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t CurrClock[PPCLK_COUNT];
  uपूर्णांक16_t AverageGfxclkFrequencyPostDs;
  uपूर्णांक16_t AverageSocclkFrequency;
  uपूर्णांक16_t AverageUclkFrequencyPostDs;
  uपूर्णांक16_t AverageGfxActivity    ;
  uपूर्णांक16_t AverageUclkActivity   ;
  uपूर्णांक8_t  CurrSocVoltageOffset  ;
  uपूर्णांक8_t  CurrGfxVoltageOffset  ;
  uपूर्णांक8_t  CurrMemVidOffset      ;
  uपूर्णांक8_t  Padding8              ;
  uपूर्णांक16_t AverageSocketPower    ;
  uपूर्णांक16_t TemperatureEdge       ;
  uपूर्णांक16_t TemperatureHotspot    ;
  uपूर्णांक16_t TemperatureMem        ;
  uपूर्णांक16_t TemperatureVrGfx      ;
  uपूर्णांक16_t TemperatureVrMem0     ;
  uपूर्णांक16_t TemperatureVrMem1     ;
  uपूर्णांक16_t TemperatureVrSoc      ;
  uपूर्णांक16_t TemperatureLiquid0    ;
  uपूर्णांक16_t TemperatureLiquid1    ;
  uपूर्णांक16_t TemperaturePlx        ;
  uपूर्णांक16_t Padding16             ;
  uपूर्णांक32_t ThrottlerStatus       ;

  uपूर्णांक8_t  LinkDpmLevel;
  uपूर्णांक8_t  Padding8_2;
  uपूर्णांक16_t CurrFanSpeed;

  uपूर्णांक16_t AverageVclkFrequency  ;
  uपूर्णांक16_t AverageDclkFrequency  ;
  uपूर्णांक16_t VcnActivityPercentage ;
  uपूर्णांक16_t AverageGfxclkFrequencyPreDs;
  uपूर्णांक16_t AverageUclkFrequencyPreDs;
  uपूर्णांक8_t  PcieRate;
  uपूर्णांक8_t  PcieWidth;

  uपूर्णांक32_t Padding32_1;
  uपूर्णांक64_t EnergyAccumulator;

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SmuMetrics_NV12_t;

प्रकार जोड़ SmuMetrics अणु
	SmuMetrics_legacy_t		nv10_legacy_metrics;
	SmuMetrics_t			nv10_metrics;
	SmuMetrics_NV12_legacy_t	nv12_legacy_metrics;
	SmuMetrics_NV12_t		nv12_metrics;
पूर्ण SmuMetrics_NV1X_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t MinClock; // This is either DCEFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MaxClock; // This is either DCEFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MinUclk;
  uपूर्णांक16_t MaxUclk;
  
  uपूर्णांक8_t  WmSetting;
  uपूर्णांक8_t  Padding[3];

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use  
पूर्ण WatermarkRowGeneric_t;

#घोषणा NUM_WM_RANGES 4

प्रकार क्रमागत अणु
  WM_SOCCLK = 0,
  WM_DCEFCLK,
  WM_COUNT,
पूर्ण WM_CLOCK_e;

प्रकार काष्ठा अणु
  // Watermarks
  WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण Watermarks_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t avgPsmCount[28];
  uपूर्णांक16_t minPsmCount[28];
  भग्न    avgPsmVoltage[28];
  भग्न    minPsmVoltage[28];

  uपूर्णांक32_t     MmHubPadding[32]; // SMU पूर्णांकernal use
पूर्ण AvfsDebugTable_t_NV14;

प्रकार काष्ठा अणु
  uपूर्णांक16_t avgPsmCount[36];
  uपूर्णांक16_t minPsmCount[36];
  भग्न    avgPsmVoltage[36]; 
  भग्न    minPsmVoltage[36];

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण AvfsDebugTable_t_NV10;

प्रकार काष्ठा अणु
  uपूर्णांक8_t  AvfsVersion;
  uपूर्णांक8_t  Padding;

  uपूर्णांक8_t  AvfsEn[AVFS_VOLTAGE_COUNT];
  
  uपूर्णांक8_t  OverrideVFT[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];

  uपूर्णांक8_t  OverrideTemperatures[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideVInversion[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideP2V[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideP2VCharzFreq[AVFS_VOLTAGE_COUNT];

  पूर्णांक32_t VFT0_m1[AVFS_VOLTAGE_COUNT]; // Q8.24
  पूर्णांक32_t VFT0_m2[AVFS_VOLTAGE_COUNT]; // Q12.12
  पूर्णांक32_t VFT0_b[AVFS_VOLTAGE_COUNT];  // Q32

  पूर्णांक32_t VFT1_m1[AVFS_VOLTAGE_COUNT]; // Q8.16
  पूर्णांक32_t VFT1_m2[AVFS_VOLTAGE_COUNT]; // Q12.12
  पूर्णांक32_t VFT1_b[AVFS_VOLTAGE_COUNT];  // Q32

  पूर्णांक32_t VFT2_m1[AVFS_VOLTAGE_COUNT]; // Q8.16
  पूर्णांक32_t VFT2_m2[AVFS_VOLTAGE_COUNT]; // Q12.12
  पूर्णांक32_t VFT2_b[AVFS_VOLTAGE_COUNT];  // Q32

  पूर्णांक32_t AvfsGb0_m1[AVFS_VOLTAGE_COUNT]; // Q8.24
  पूर्णांक32_t AvfsGb0_m2[AVFS_VOLTAGE_COUNT]; // Q12.12
  पूर्णांक32_t AvfsGb0_b[AVFS_VOLTAGE_COUNT];  // Q32

  पूर्णांक32_t AcBtcGb_m1[AVFS_VOLTAGE_COUNT]; // Q8.24
  पूर्णांक32_t AcBtcGb_m2[AVFS_VOLTAGE_COUNT]; // Q12.12
  पूर्णांक32_t AcBtcGb_b[AVFS_VOLTAGE_COUNT];  // Q32

  uपूर्णांक32_t AvfsTempCold[AVFS_VOLTAGE_COUNT];
  uपूर्णांक32_t AvfsTempMid[AVFS_VOLTAGE_COUNT];
  uपूर्णांक32_t AvfsTempHot[AVFS_VOLTAGE_COUNT];

  uपूर्णांक32_t VInversion[AVFS_VOLTAGE_COUNT]; // in mV with 2 fractional bits


  पूर्णांक32_t P2V_m1[AVFS_VOLTAGE_COUNT]; // Q8.24
  पूर्णांक32_t P2V_m2[AVFS_VOLTAGE_COUNT]; // Q12.12
  पूर्णांक32_t P2V_b[AVFS_VOLTAGE_COUNT];  // Q32

  uपूर्णांक32_t P2VCharzFreq[AVFS_VOLTAGE_COUNT]; // in 10KHz units

  uपूर्णांक32_t EnabledAvfsModules[2]; //NV10 - 36 AVFS modules

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण AvfsFuseOverride_t;

प्रकार काष्ठा अणु

  uपूर्णांक8_t   Gfx_ActiveHystLimit;
  uपूर्णांक8_t   Gfx_IdleHystLimit;
  uपूर्णांक8_t   Gfx_FPS;
  uपूर्णांक8_t   Gfx_MinActiveFreqType;
  uपूर्णांक8_t   Gfx_BoosterFreqType; 
  uपूर्णांक8_t   Gfx_MinFreqStep;                // Minimum delta between current and target frequeny in order क्रम FW to change घड़ी.
  uपूर्णांक16_t  Gfx_MinActiveFreq;              // MHz
  uपूर्णांक16_t  Gfx_BoosterFreq;                // MHz
  uपूर्णांक16_t  Gfx_PD_Data_समय_स्थिरant;      // Time स्थिरant of PD controller in ms
  uपूर्णांक32_t  Gfx_PD_Data_limit_a;            // Q16
  uपूर्णांक32_t  Gfx_PD_Data_limit_b;            // Q16
  uपूर्णांक32_t  Gfx_PD_Data_limit_c;            // Q16
  uपूर्णांक32_t  Gfx_PD_Data_error_coeff;        // Q16
  uपूर्णांक32_t  Gfx_PD_Data_error_rate_coeff;   // Q16
  
  uपूर्णांक8_t   Soc_ActiveHystLimit;
  uपूर्णांक8_t   Soc_IdleHystLimit;
  uपूर्णांक8_t   Soc_FPS;
  uपूर्णांक8_t   Soc_MinActiveFreqType;
  uपूर्णांक8_t   Soc_BoosterFreqType; 
  uपूर्णांक8_t   Soc_MinFreqStep;                // Minimum delta between current and target frequeny in order क्रम FW to change घड़ी.
  uपूर्णांक16_t  Soc_MinActiveFreq;              // MHz
  uपूर्णांक16_t  Soc_BoosterFreq;                // MHz
  uपूर्णांक16_t  Soc_PD_Data_समय_स्थिरant;      // Time स्थिरant of PD controller in ms
  uपूर्णांक32_t  Soc_PD_Data_limit_a;            // Q16
  uपूर्णांक32_t  Soc_PD_Data_limit_b;            // Q16
  uपूर्णांक32_t  Soc_PD_Data_limit_c;            // Q16
  uपूर्णांक32_t  Soc_PD_Data_error_coeff;        // Q16
  uपूर्णांक32_t  Soc_PD_Data_error_rate_coeff;   // Q16
  
  uपूर्णांक8_t   Mem_ActiveHystLimit;
  uपूर्णांक8_t   Mem_IdleHystLimit;
  uपूर्णांक8_t   Mem_FPS;
  uपूर्णांक8_t   Mem_MinActiveFreqType;
  uपूर्णांक8_t   Mem_BoosterFreqType;
  uपूर्णांक8_t   Mem_MinFreqStep;                // Minimum delta between current and target frequeny in order क्रम FW to change घड़ी.
  uपूर्णांक16_t  Mem_MinActiveFreq;              // MHz
  uपूर्णांक16_t  Mem_BoosterFreq;                // MHz
  uपूर्णांक16_t  Mem_PD_Data_समय_स्थिरant;      // Time स्थिरant of PD controller in ms
  uपूर्णांक32_t  Mem_PD_Data_limit_a;            // Q16
  uपूर्णांक32_t  Mem_PD_Data_limit_b;            // Q16
  uपूर्णांक32_t  Mem_PD_Data_limit_c;            // Q16
  uपूर्णांक32_t  Mem_PD_Data_error_coeff;        // Q16
  uपूर्णांक32_t  Mem_PD_Data_error_rate_coeff;   // Q16

  uपूर्णांक32_t  Mem_UpThreshold_Limit;          // Q16
  uपूर्णांक8_t   Mem_UpHystLimit;
  uपूर्णांक8_t   Mem_DownHystLimit;
  uपूर्णांक16_t  Mem_Fps;

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use  

पूर्ण DpmActivityMonitorCoeffInt_t;


// Workload bits
#घोषणा WORKLOAD_PPLIB_DEFAULT_BIT        0 
#घोषणा WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 1 
#घोषणा WORKLOAD_PPLIB_POWER_SAVING_BIT   2 
#घोषणा WORKLOAD_PPLIB_VIDEO_BIT          3 
#घोषणा WORKLOAD_PPLIB_VR_BIT             4 
#घोषणा WORKLOAD_PPLIB_COMPUTE_BIT        5 
#घोषणा WORKLOAD_PPLIB_CUSTOM_BIT         6 
#घोषणा WORKLOAD_PPLIB_COUNT              7 


// These defines are used with the following messages:
// SMC_MSG_TransferTableDram2Smu
// SMC_MSG_TransferTableSmu2Dram

// Table transfer status
#घोषणा TABLE_TRANSFER_OK         0x0
#घोषणा TABLE_TRANSFER_FAILED     0xFF

// Table types
#घोषणा TABLE_PPTABLE                 0
#घोषणा TABLE_WATERMARKS              1
#घोषणा TABLE_AVFS                    2
#घोषणा TABLE_AVFS_PSM_DEBUG          3
#घोषणा TABLE_AVFS_FUSE_OVERRIDE      4
#घोषणा TABLE_PMSTATUSLOG             5
#घोषणा TABLE_SMU_METRICS             6
#घोषणा TABLE_DRIVER_SMU_CONFIG       7
#घोषणा TABLE_ACTIVITY_MONITOR_COEFF  8
#घोषणा TABLE_OVERDRIVE               9
#घोषणा TABLE_I2C_COMMANDS           10
#घोषणा TABLE_PACE                   11
#घोषणा TABLE_COUNT                  12

//RLC Pace Table total number of levels
#घोषणा RLC_PACE_TABLE_NUM_LEVELS 16

प्रकार काष्ठा अणु
  भग्न FlopsPerByteTable[RLC_PACE_TABLE_NUM_LEVELS];
  
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use  
पूर्ण RlcPaceFlopsPerByteOverride_t;

// These defines are used with the SMC_MSG_SetUclkFastSwitch message.
#घोषणा UCLK_SWITCH_SLOW 0
#घोषणा UCLK_SWITCH_FAST 1
#पूर्ण_अगर
