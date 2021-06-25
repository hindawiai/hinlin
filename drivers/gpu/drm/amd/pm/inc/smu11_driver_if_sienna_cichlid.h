<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __SMU11_DRIVER_IF_SIENNA_CICHLID_H__
#घोषणा __SMU11_DRIVER_IF_SIENNA_CICHLID_H__

// *** IMPORTANT ***
// SMU TEAM: Always increment the पूर्णांकerface version अगर 
// any काष्ठाure is changed in this file
#घोषणा SMU11_DRIVER_IF_VERSION 0x3B

#घोषणा PPTABLE_Sienna_Cichlid_SMU_VERSION 7

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
#घोषणा NUM_DTBCLK_DPM_LEVELS  8
#घोषणा NUM_UCLK_DPM_LEVELS    4 
#घोषणा NUM_MP1CLK_DPM_LEVELS  2
#घोषणा NUM_LINK_LEVELS        2
#घोषणा NUM_FCLK_DPM_LEVELS    8 
#घोषणा NUM_XGMI_LEVELS        2
#घोषणा NUM_XGMI_PSTATE_LEVELS 4
#घोषणा NUM_OD_FAN_MAX_POINTS  6

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
#घोषणा MAX_DTBCLK_DPM_LEVEL  (NUM_DTBCLK_DPM_LEVELS  - 1)
#घोषणा MAX_UCLK_DPM_LEVEL    (NUM_UCLK_DPM_LEVELS    - 1)
#घोषणा MAX_MP1CLK_DPM_LEVEL  (NUM_MP1CLK_DPM_LEVELS  - 1)
#घोषणा MAX_LINK_LEVEL        (NUM_LINK_LEVELS        - 1)
#घोषणा MAX_FCLK_DPM_LEVEL    (NUM_FCLK_DPM_LEVELS    - 1)

//Gemini Modes
#घोषणा PPSMC_GeminiModeNone   0  //Single GPU board
#घोषणा PPSMC_GeminiModeMaster 1  //Master GPU on a Gemini board
#घोषणा PPSMC_GeminiModeSlave  2  //Slave GPU on a Gemini board

// Feature Control Defines
// DPM
#घोषणा FEATURE_DPM_PREFETCHER_BIT      0
#घोषणा FEATURE_DPM_GFXCLK_BIT          1
#घोषणा FEATURE_DPM_GFX_GPO_BIT         2
#घोषणा FEATURE_DPM_UCLK_BIT            3
#घोषणा FEATURE_DPM_FCLK_BIT            4
#घोषणा FEATURE_DPM_SOCCLK_BIT          5
#घोषणा FEATURE_DPM_MP0CLK_BIT          6
#घोषणा FEATURE_DPM_LINK_BIT            7
#घोषणा FEATURE_DPM_DCEFCLK_BIT         8
#घोषणा FEATURE_DPM_XGMI_BIT            9
#घोषणा FEATURE_MEM_VDDCI_SCALING_BIT   10 
#घोषणा FEATURE_MEM_MVDD_SCALING_BIT    11
                                        
//Idle                                  
#घोषणा FEATURE_DS_GFXCLK_BIT           12
#घोषणा FEATURE_DS_SOCCLK_BIT           13
#घोषणा FEATURE_DS_FCLK_BIT             14
#घोषणा FEATURE_DS_LCLK_BIT             15
#घोषणा FEATURE_DS_DCEFCLK_BIT          16
#घोषणा FEATURE_DS_UCLK_BIT             17
#घोषणा FEATURE_GFX_ULV_BIT             18  
#घोषणा FEATURE_FW_DSTATE_BIT           19 
#घोषणा FEATURE_GFXOFF_BIT              20
#घोषणा FEATURE_BACO_BIT                21
#घोषणा FEATURE_MM_DPM_PG_BIT           22  
#घोषणा FEATURE_SPARE_23_BIT            23
//Throttler/Response                    
#घोषणा FEATURE_PPT_BIT                 24
#घोषणा FEATURE_TDC_BIT                 25
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
#घोषणा FEATURE_DF_SUPERV_BIT           43
#घोषणा FEATURE_RSMU_SMN_CG_BIT         44
#घोषणा FEATURE_DF_CSTATE_BIT           45
#घोषणा FEATURE_2_STEP_PSTATE_BIT       46
#घोषणा FEATURE_SMNCLK_DPM_BIT          47
#घोषणा FEATURE_PERLINK_GMIDOWN_BIT     48
#घोषणा FEATURE_GFX_EDC_BIT             49
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

//For use with feature control messages
प्रकार क्रमागत अणु
  FEATURE_PWR_ALL,
  FEATURE_PWR_S5,
  FEATURE_PWR_BACO,
  FEATURE_PWR_SOC,
  FEATURE_PWR_GFX,
  FEATURE_PWR_DOMAIN_COUNT,
पूर्ण FEATURE_PWR_DOMAIN_e;


// Debug Overrides Biपंचांगask
#घोषणा DPM_OVERRIDE_DISABLE_FCLK_PID                0x00000001
#घोषणा DPM_OVERRIDE_DISABLE_UCLK_PID                0x00000002
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_VCN_FCLK      0x00000004
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_VCLK_FCLK      0x00000008
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_DCLK_FCLK      0x00000010
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_SOCCLK  0x00000020
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_UCLK    0x00000040
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_DCE_FCLK      0x00000080
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_MP0_SOCCLK    0x00000100
#घोषणा DPM_OVERRIDE_DISABLE_DFLL_PLL_SHUTDOWN       0x00000200
#घोषणा DPM_OVERRIDE_DISABLE_MEMORY_TEMPERATURE_READ 0x00000400
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_VCN_DCEFCLK   0x00000800
#घोषणा DPM_OVERRIDE_DISABLE_FAST_FCLK_TIMER         0x00001000
#घोषणा DPM_OVERRIDE_DISABLE_VCN_PG                  0x00002000
#घोषणा DPM_OVERRIDE_DISABLE_FMAX_VMAX               0x00004000

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
#घोषणा THROTTLER_TDC_GFX_BIT      11
#घोषणा THROTTLER_TDC_SOC_BIT      12
#घोषणा THROTTLER_PPT0_BIT         13
#घोषणा THROTTLER_PPT1_BIT         14
#घोषणा THROTTLER_PPT2_BIT         15
#घोषणा THROTTLER_PPT3_BIT         16
#घोषणा THROTTLER_FIT_BIT          17
#घोषणा THROTTLER_PPM_BIT          18
#घोषणा THROTTLER_APCC_BIT         19

// FW DState Features Control Bits
// FW DState Features Control Bits
#घोषणा FW_DSTATE_SOC_ULV_BIT               0
#घोषणा FW_DSTATE_G6_HSR_BIT                1
#घोषणा FW_DSTATE_G6_PHY_VDDCI_OFF_BIT      2
#घोषणा FW_DSTATE_MP0_DS_BIT                3
#घोषणा FW_DSTATE_SMN_DS_BIT                4
#घोषणा FW_DSTATE_MP1_DS_BIT                5
#घोषणा FW_DSTATE_MP1_WHISPER_MODE_BIT      6
#घोषणा FW_DSTATE_SOC_LIV_MIN_BIT           7
#घोषणा FW_DSTATE_SOC_PLL_PWRDN_BIT         8
#घोषणा FW_DSTATE_MEM_PLL_PWRDN_BIT         9   
#घोषणा FW_DSTATE_OPTIMIZE_MALL_REFRESH_BIT 10
#घोषणा FW_DSTATE_MEM_PSI_BIT               11
#घोषणा FW_DSTATE_HSR_NON_STROBE_BIT        12
#घोषणा FW_DSTATE_MP0_ENTER_WFI_BIT         13

#घोषणा FW_DSTATE_SOC_ULV_MASK                    (1 << FW_DSTATE_SOC_ULV_BIT          )
#घोषणा FW_DSTATE_G6_HSR_MASK                     (1 << FW_DSTATE_G6_HSR_BIT           )
#घोषणा FW_DSTATE_G6_PHY_VDDCI_OFF_MASK           (1 << FW_DSTATE_G6_PHY_VDDCI_OFF_BIT )
#घोषणा FW_DSTATE_MP1_DS_MASK                     (1 << FW_DSTATE_MP1_DS_BIT           )  
#घोषणा FW_DSTATE_MP0_DS_MASK                     (1 << FW_DSTATE_MP0_DS_BIT           )   
#घोषणा FW_DSTATE_SMN_DS_MASK                     (1 << FW_DSTATE_SMN_DS_BIT           )
#घोषणा FW_DSTATE_MP1_WHISPER_MODE_MASK           (1 << FW_DSTATE_MP1_WHISPER_MODE_BIT )
#घोषणा FW_DSTATE_SOC_LIV_MIN_MASK                (1 << FW_DSTATE_SOC_LIV_MIN_BIT      )
#घोषणा FW_DSTATE_SOC_PLL_PWRDN_MASK              (1 << FW_DSTATE_SOC_PLL_PWRDN_BIT    )
#घोषणा FW_DSTATE_MEM_PLL_PWRDN_MASK              (1 << FW_DSTATE_MEM_PLL_PWRDN_BIT    )
#घोषणा FW_DSTATE_OPTIMIZE_MALL_REFRESH_MASK      (1 << FW_DSTATE_OPTIMIZE_MALL_REFRESH_BIT    )
#घोषणा FW_DSTATE_MEM_PSI_MASK                    (1 << FW_DSTATE_MEM_PSI_BIT    )
#घोषणा FW_DSTATE_HSR_NON_STROBE_MASK             (1 << FW_DSTATE_HSR_NON_STROBE_BIT    )
#घोषणा FW_DSTATE_MP0_ENTER_WFI_MASK              (1 << FW_DSTATE_MP0_ENTER_WFI_BIT    )

// GFX GPO Feature Contains PACE and DEM sub features
#घोषणा GFX_GPO_PACE_BIT                   0
#घोषणा GFX_GPO_DEM_BIT                    1

#घोषणा GFX_GPO_PACE_MASK                  (1 << GFX_GPO_PACE_BIT)
#घोषणा GFX_GPO_DEM_MASK                   (1 << GFX_GPO_DEM_BIT )

#घोषणा GPO_UPDATE_REQ_UCLKDPM_MASK  0x1
#घोषणा GPO_UPDATE_REQ_FCLKDPM_MASK  0x2
#घोषणा GPO_UPDATE_REQ_MALLHIT_MASK  0x4


//LED Display Mask & Control Bits
#घोषणा LED_DISPLAY_GFX_DPM_BIT            0
#घोषणा LED_DISPLAY_PCIE_BIT               1
#घोषणा LED_DISPLAY_ERROR_BIT              2

//RLC Pace Table total number of levels
#घोषणा RLC_PACE_TABLE_NUM_LEVELS 16

प्रकार क्रमागत अणु
  DRAM_BIT_WIDTH_DISABLED = 0,
  DRAM_BIT_WIDTH_X_8,
  DRAM_BIT_WIDTH_X_16,
  DRAM_BIT_WIDTH_X_32,
  DRAM_BIT_WIDTH_X_64, // NOT USED.
  DRAM_BIT_WIDTH_X_128,
  DRAM_BIT_WIDTH_COUNT,
पूर्ण DRAM_BIT_WIDTH_TYPE_e;

//I2C Interface
#घोषणा NUM_I2C_CONTROLLERS                16

#घोषणा I2C_CONTROLLER_ENABLED             1
#घोषणा I2C_CONTROLLER_DISABLED            0

#घोषणा MAX_SW_I2C_COMMANDS                24

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
  I2C_CONTROLLER_NAME_OTHER,
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
  I2C_CONTROLLER_THROTTLER_INA3221,
  I2C_CONTROLLER_THROTTLER_COUNT,  
पूर्ण I2cControllerThrottler_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_PROTOCOL_VR_XPDE132G5,
  I2C_CONTROLLER_PROTOCOL_VR_IR35217,
  I2C_CONTROLLER_PROTOCOL_TMP_TMP102A,
  I2C_CONTROLLER_PROTOCOL_INA3221,
  I2C_CONTROLLER_PROTOCOL_COUNT,  
पूर्ण I2cControllerProtocol_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t   Enabled;
  uपूर्णांक8_t   Speed;
  uपूर्णांक8_t   SlaveAddress;  
  uपूर्णांक8_t   ControllerPort;
  uपूर्णांक8_t   ControllerName;
  uपूर्णांक8_t   ThermalThrotter;
  uपूर्णांक8_t   I2cProtocol;
  uपूर्णांक8_t   PaddingConfig;  
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

प्रकार क्रमागत अणु
  FAN_MODE_AUTO = 0,
  FAN_MODE_MANUAL_LINEAR,
पूर्ण FanMode_e;

#घोषणा CMDCONFIG_STOP_BIT             0
#घोषणा CMDCONFIG_RESTART_BIT          1
#घोषणा CMDCONFIG_READWRITE_BIT        2 //bit should be 0 क्रम पढ़ो, 1 क्रम ग_लिखो

#घोषणा CMDCONFIG_STOP_MASK           (1 << CMDCONFIG_STOP_BIT)
#घोषणा CMDCONFIG_RESTART_MASK        (1 << CMDCONFIG_RESTART_BIT)
#घोषणा CMDCONFIG_READWRITE_MASK      (1 << CMDCONFIG_READWRITE_BIT)

प्रकार काष्ठा अणु
  uपूर्णांक8_t ReadWriteData;  //Return data क्रम पढ़ो. Data to send क्रम ग_लिखो
  uपूर्णांक8_t CmdConfig; //Includes whether associated command should have a stop or restart command, and is a पढ़ो or ग_लिखो
पूर्ण SwI2cCmd_t; //SW I2C Command Table

प्रकार काष्ठा अणु
  uपूर्णांक8_t     I2CcontrollerPort; //CKSVII2C0(0) or //CKSVII2C1(1)
  uपूर्णांक8_t     I2CSpeed;          //Use I2cSpeed_e to indicate speed to select
  uपूर्णांक8_t     SlaveAddress;      //Slave address of device
  uपूर्णांक8_t     NumCmds;           //Number of commands

  SwI2cCmd_t  SwI2cCmds[MAX_SW_I2C_COMMANDS];
पूर्ण SwI2cRequest_t; // SW I2C Request Table

प्रकार काष्ठा अणु
  SwI2cRequest_t SwI2cRequest;

  uपूर्णांक32_t Spare[8];
  uपूर्णांक32_t MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SwI2cRequestExternal_t;

//D3HOT sequences
प्रकार क्रमागत अणु
  BACO_SEQUENCE,
  MSR_SEQUENCE,
  BAMACO_SEQUENCE,
  ULPS_SEQUENCE,
  D3HOT_SEQUENCE_COUNT,
पूर्ण D3HOTSequence_e;

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
  uपूर्णांक32_t a;  // store in fixed poपूर्णांक, [31:20] चिन्हित पूर्णांकeger, [19:0] fractional bits
  uपूर्णांक32_t b;  // store in fixed poपूर्णांक, [31:20] चिन्हित पूर्णांकeger, [19:0] fractional bits
  uपूर्णांक32_t c;  // store in fixed poपूर्णांक, [31:20] चिन्हित पूर्णांकeger, [19:0] fractional bits
पूर्ण QuadraticFixedPoपूर्णांक_t;

प्रकार काष्ठा अणु            
  uपूर्णांक32_t m;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t b;  // store in IEEE भग्न क्रमmat in this variable
पूर्ण LinearInt_t;

प्रकार काष्ठा अणु            
  uपूर्णांक32_t a;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t b;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t c;  // store in IEEE भग्न क्रमmat in this variable
पूर्ण DroopInt_t;

//Piecewise linear droop model, Sienna_Cichlid currently used only क्रम GFX DFLL 
#घोषणा NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS 5
प्रकार क्रमागत अणु
  PIECEWISE_LINEAR_FUSED_MODEL = 0,
  PIECEWISE_LINEAR_PP_MODEL,
  QUADRATIC_PP_MODEL,
  PERPART_PIECEWISE_LINEAR_PP_MODEL,  
पूर्ण DfllDroopModelSelect_e;

प्रकार काष्ठा अणु
  uपूर्णांक32_t Fset[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS];    //in GHz, store in IEEE भग्न क्रमmat
  uपूर्णांक32_t Vdroop[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS];  //in V  , store in IEEE भग्न क्रमmat
पूर्णPiecewiseLinearDroopInt_t;

प्रकार क्रमागत अणु
  GFXCLK_SOURCE_PLL = 0, 
  GFXCLK_SOURCE_DFLL, 
  GFXCLK_SOURCE_COUNT, 
पूर्ण GFXCLK_SOURCE_e; 

//Only Clks that have DPM descriptors are listed here 
प्रकार क्रमागत अणु
  PPCLK_GFXCLK = 0,
  PPCLK_SOCCLK,
  PPCLK_UCLK,
  PPCLK_FCLK,  
  PPCLK_DCLK_0,
  PPCLK_VCLK_0,
  PPCLK_DCLK_1,
  PPCLK_VCLK_1,
  PPCLK_DCEFCLK,
  PPCLK_DISPCLK,
  PPCLK_PIXCLK,
  PPCLK_PHYCLK,
  PPCLK_DTBCLK,
  PPCLK_COUNT,
पूर्ण PPCLK_e;

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
  PWR_CONFIG_TDP = 0,
  PWR_CONFIG_TGP,
  PWR_CONFIG_TCP_ESTIMATED,
  PWR_CONFIG_TCP_MEASURED,
पूर्ण PwrConfig_e;

प्रकार क्रमागत अणु
  XGMI_LINK_RATE_2 = 2,    // 2Gbps
  XGMI_LINK_RATE_4 = 4,    // 4Gbps
  XGMI_LINK_RATE_8 = 8,    // 8Gbps
  XGMI_LINK_RATE_12 = 12,  // 12Gbps
  XGMI_LINK_RATE_16 = 16,  // 16Gbps
  XGMI_LINK_RATE_17 = 17,  // 17Gbps
  XGMI_LINK_RATE_18 = 18,  // 18Gbps
  XGMI_LINK_RATE_19 = 19,  // 19Gbps
  XGMI_LINK_RATE_20 = 20,  // 20Gbps
  XGMI_LINK_RATE_21 = 21,  // 21Gbps
  XGMI_LINK_RATE_22 = 22,  // 22Gbps
  XGMI_LINK_RATE_23 = 23,  // 23Gbps
  XGMI_LINK_RATE_24 = 24,  // 24Gbps
  XGMI_LINK_RATE_25 = 25,  // 25Gbps
  XGMI_LINK_RATE_COUNT
पूर्ण XGMI_LINK_RATE_e;

प्रकार क्रमागत अणु
  XGMI_LINK_WIDTH_1 = 0,  // x1
  XGMI_LINK_WIDTH_2,  // x2
  XGMI_LINK_WIDTH_4,  // x4
  XGMI_LINK_WIDTH_8,  // x8
  XGMI_LINK_WIDTH_9,  // x9
  XGMI_LINK_WIDTH_16, // x16
  XGMI_LINK_WIDTH_COUNT
पूर्ण XGMI_LINK_WIDTH_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t        VoltageMode;         // 0 - AVFS only, 1- min(AVFS,SS), 2-SS only
  uपूर्णांक8_t        SnapToDiscrete;      // 0 - Fine grained DPM, 1 - Discrete DPM
  uपूर्णांक8_t        NumDiscreteLevels;   // Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used
  uपूर्णांक8_t        Padding;         
  LinearInt_t    ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
  QuadraticInt_t SsCurve;             // Slow-slow curve (GHz->V)
  uपूर्णांक16_t       SsFmin;              // Fmin क्रम SS curve. If SS curve is selected, will use V@SSFmin क्रम F <= Fmin
  uपूर्णांक16_t       Padding16;    
पूर्ण DpmDescriptor_t;

प्रकार क्रमागत  अणु
  PPT_THROTTLER_PPT0,
  PPT_THROTTLER_PPT1,
  PPT_THROTTLER_PPT2,
  PPT_THROTTLER_PPT3,       
  PPT_THROTTLER_COUNT
पूर्ण PPT_THROTTLER_e;

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
  TEMP_COUNT,
पूर्ण TEMP_e;

प्रकार क्रमागत अणु
  TDC_THROTTLER_GFX,
  TDC_THROTTLER_SOC,
  TDC_THROTTLER_COUNT
पूर्ण TDC_THROTTLER_e;

प्रकार क्रमागत अणु
  CUSTOMER_VARIANT_ROW,
  CUSTOMER_VARIANT_FALCON,
  CUSTOMER_VARIANT_COUNT,
पूर्ण CUSTOMER_VARIANT_e;
	 
// Used क्रम 2-step UCLK DPM change workaround
प्रकार काष्ठा अणु
  uपूर्णांक16_t Fmin;
  uपूर्णांक16_t Fmax;
पूर्ण UclkDpmChangeRange_t;

प्रकार काष्ठा अणु
  // MAJOR SECTION: SKU PARAMETERS

  uपूर्णांक32_t Version;

  // SECTION: Feature Enablement
  uपूर्णांक32_t FeaturesToRun[NUM_FEATURES / 32];

  // SECTION: Infraकाष्ठाure Limits
  uपूर्णांक16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT]; // Watts
  uपूर्णांक16_t SocketPowerLimitAcTau[PPT_THROTTLER_COUNT]; // Time स्थिरant of LPF in ms
  uपूर्णांक16_t SocketPowerLimitDc[PPT_THROTTLER_COUNT];  // Watts
  uपूर्णांक16_t SocketPowerLimitDcTau[PPT_THROTTLER_COUNT];  // Time स्थिरant of LPF in ms

  uपूर्णांक16_t TdcLimit[TDC_THROTTLER_COUNT];             // Amps
  uपूर्णांक16_t TdcLimitTau[TDC_THROTTLER_COUNT];          // Time स्थिरant of LPF in ms

  uपूर्णांक16_t TemperatureLimit[TEMP_COUNT]; // Celcius
  
  uपूर्णांक32_t FitLimit;                // Failures in समय (failures per million parts over the defined lअगरeसमय)

  // SECTION: Power Configuration
  uपूर्णांक8_t      TotalPowerConfig;    //0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measured. Use defines from PwrConfig_e
  uपूर्णांक8_t      TotalPowerPadding[3];  

  // SECTION: APCC Settings
  uपूर्णांक32_t     ApccPlusResidencyLimit;

  //SECTION: SMNCLK DPM
  uपूर्णांक16_t       SmnclkDpmFreq        [NUM_SMNCLK_DPM_LEVELS];       // in MHz
  uपूर्णांक16_t       SmnclkDpmVoltage     [NUM_SMNCLK_DPM_LEVELS];       // mV(Q2)

  uपूर्णांक32_t       PaddingAPCC;
  uपूर्णांक16_t       PerPartDroopVsetGfxDfll[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS];  //In mV(Q2)
  uपूर्णांक16_t       PaddingPerPartDroop;

  // SECTION: Throttler settings
  uपूर्णांक32_t ThrottlerControlMask;   // See Throtter masks defines

  // SECTION: FW DSTATE Settings  
  uपूर्णांक32_t FwDStateMask;           // See FW DState masks defines

  // SECTION: ULV Settings
  uपूर्णांक16_t  UlvVoltageOffsetSoc; // In mV(Q2)
  uपूर्णांक16_t  UlvVoltageOffsetGfx; // In mV(Q2)

  uपूर्णांक16_t     MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode 
  uपूर्णांक16_t     MinVoltageUlvSoc; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_SOC in ULV mode

  uपूर्णांक16_t     SocLIVmin;        // In mV(Q2)  Long Idle Vmin (deep ULV), क्रम VDD_SOC
  uपूर्णांक16_t     PaddingLIVmin;

  uपूर्णांक8_t   GceaLinkMgrIdleThreshold;        //Set by SMU FW during enablment of GFXOFF. Controls delay क्रम GFX SDP port disconnection during idle events
  uपूर्णांक8_t   paddingRlcUlvParams[3];

  // SECTION: Voltage Control Parameters
  uपूर्णांक16_t     MinVoltageGfx;     // In mV(Q2) Minimum Voltage ("Vmin") of VDD_GFX
  uपूर्णांक16_t     MinVoltageSoc;     // In mV(Q2) Minimum Voltage ("Vmin") of VDD_SOC
  uपूर्णांक16_t     MaxVoltageGfx;     // In mV(Q2) Maximum Voltage allowable of VDD_GFX
  uपूर्णांक16_t     MaxVoltageSoc;     // In mV(Q2) Maximum Voltage allowable of VDD_SOC

  uपूर्णांक16_t     LoadLineResistanceGfx;   // In mOhms with 8 fractional bits
  uपूर्णांक16_t     LoadLineResistanceSoc;   // In mOhms with 8 fractional bits

  // SECTION: Temperature Dependent Vmin
  uपूर्णांक16_t     VDDGFX_TVmin;       //Celcius
  uपूर्णांक16_t     VDDSOC_TVmin;       //Celcius
  uपूर्णांक16_t     VDDGFX_Vmin_HiTemp; // mV Q2
  uपूर्णांक16_t     VDDGFX_Vmin_LoTemp; // mV Q2
  uपूर्णांक16_t     VDDSOC_Vmin_HiTemp; // mV Q2
  uपूर्णांक16_t     VDDSOC_Vmin_LoTemp; // mV Q2
  
  uपूर्णांक16_t     VDDGFX_TVminHystersis; // Celcius
  uपूर्णांक16_t     VDDSOC_TVminHystersis; // Celcius

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
  uपूर्णांक16_t       FreqTableDtbclk   [NUM_DTBCLK_DPM_LEVELS  ];     // In MHz
  uपूर्णांक16_t       FreqTableFclk     [NUM_FCLK_DPM_LEVELS    ];     // In MHz
  uपूर्णांक32_t       Paddingclks;

  DroopInt_t     PerPartDroopModelGfxDfll[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS]; //GHz ->Vstore in IEEE भग्न क्रमmat

  uपूर्णांक32_t       DcModeMaxFreq     [PPCLK_COUNT            ];     // In MHz
  
  uपूर्णांक8_t        FreqTableUclkDiv  [NUM_UCLK_DPM_LEVELS    ];     // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8
  
  // Used क्रम MALL perक्रमmance boost
  uपूर्णांक16_t       FclkBoostFreq;                                   // In Mhz
  uपूर्णांक16_t       FclkParamPadding;

  // SECTION: DPM Config 2
  uपूर्णांक16_t       Mp0clkFreq        [NUM_MP0CLK_DPM_LEVELS];       // in MHz
  uपूर्णांक16_t       Mp0DpmVoltage     [NUM_MP0CLK_DPM_LEVELS];       // mV(Q2)
  uपूर्णांक16_t       MemVddciVoltage   [NUM_UCLK_DPM_LEVELS];         // mV(Q2)
  uपूर्णांक16_t       MemMvddVoltage    [NUM_UCLK_DPM_LEVELS];         // mV(Q2)
  // GFXCLK DPM
  uपूर्णांक16_t        GfxclkFgfxoffEntry;   // in Mhz
  uपूर्णांक16_t        GfxclkFinit;          // in Mhz 
  uपूर्णांक16_t        GfxclkFidle;          // in MHz 
  uपूर्णांक8_t         GfxclkSource;         // 0 = PLL, 1 = DFLL
  uपूर्णांक8_t         GfxclkPadding;

  // GFX GPO 
  uपूर्णांक8_t         GfxGpoSubFeatureMask; // bit 0 = PACE, bit 1 = DEM
  uपूर्णांक8_t         GfxGpoEnabledWorkPolicyMask; //Any policy that GPO can be enabled
  uपूर्णांक8_t         GfxGpoDisabledWorkPolicyMask; //Any policy that GPO can be disabled
  uपूर्णांक8_t         GfxGpoPadding[1];
  uपूर्णांक32_t        GfxGpoVotingAllow;    //For indicating which feature changes should result in a GPO table recalculation

  uपूर्णांक32_t        GfxGpoPadding32[4];  

  uपूर्णांक16_t        GfxDcsFopt;           // Optimal GFXCLK क्रम DCS in Mhz
  uपूर्णांक16_t        GfxDcsFclkFopt;       // Optimal FCLK क्रम DCS in Mhz
  uपूर्णांक16_t        GfxDcsUclkFopt;       // Optimal UCLK क्रम DCS in Mhz
  
  uपूर्णांक16_t        DcsGfxOffVoltage;     //Voltage in mV(Q2) applied to VDDGFX when entering DCS GFXOFF phase  

  uपूर्णांक16_t        DcsMinGfxOffTime;     //Minimum amount of समय PMFW shuts GFX OFF as part of GFX DCS phase
  uपूर्णांक16_t        DcsMaxGfxOffTime;      //Maximum amount of समय PMFW can shut GFX OFF as part of GFX DCS phase at a stretch.

  uपूर्णांक32_t        DcsMinCreditAccum;    //Min amount of positive credit accumulation beक्रमe waking GFX up as part of DCS.

  uपूर्णांक16_t        DcsExitHysteresis;    //The min amount of समय घातer credit accumulator should have a value > 0 beक्रमe SMU निकासs the DCS throttling phase. 
  uपूर्णांक16_t        DcsTimeout;           //This is the amount of समय SMU FW रुकोs क्रम RLC to put GFX पूर्णांकo GFXOFF beक्रमe reverting to the fallback mechanism of throttling GFXCLK to Fmin.

  uपूर्णांक32_t        DcsParamPadding[5];

  uपूर्णांक16_t        FlopsPerByteTable[RLC_PACE_TABLE_NUM_LEVELS]; // Q8.8

  // UCLK section
  uपूर्णांक8_t      LowestUclkReservedForUlv; // Set this to 1 अगर UCLK DPM0 is reserved क्रम ULV-mode only
  uपूर्णांक8_t      PaddingMem[3];
  
  uपूर्णांक8_t      UclkDpmPstates     [NUM_UCLK_DPM_LEVELS];     // 4 DPM states, 0-P0, 1-P1, 2-P2, 3-P3.
  
  // Used क्रम 2-Step UCLK change workaround
  UclkDpmChangeRange_t UclkDpmSrcFreqRange;  // In Mhz
  UclkDpmChangeRange_t UclkDpmTargFreqRange; // In Mhz
  uपूर्णांक16_t UclkDpmMidstepFreq;               // In Mhz
  uपूर्णांक16_t UclkMidstepPadding;

  // Link DPM Settings
  uपूर्णांक8_t      PcieGenSpeed[NUM_LINK_LEVELS];           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
  uपूर्णांक8_t      PcieLaneCount[NUM_LINK_LEVELS];          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
  uपूर्णांक16_t     LclkFreq[NUM_LINK_LEVELS];              
 
  // SECTION: Fan Control
  uपूर्णांक16_t     FanStopTemp;          //Celcius
  uपूर्णांक16_t     FanStartTemp;         //Celcius

  uपूर्णांक16_t     FanGain[TEMP_COUNT];

  uपूर्णांक16_t     FanPwmMin;
  uपूर्णांक16_t     FanAcousticLimitRpm;
  uपूर्णांक16_t     FanThrottlingRpm;
  uपूर्णांक16_t     FanMaximumRpm;
  uपूर्णांक16_t     MGpuFanBoostLimitRpm;  
  uपूर्णांक16_t     FanTargetTemperature;
  uपूर्णांक16_t     FanTargetGfxclk;
  uपूर्णांक16_t     FanPadding16;
  uपूर्णांक8_t      FanTempInputSelect;
  uपूर्णांक8_t      FanPadding;
  uपूर्णांक8_t      FanZeroRpmEnable; 
  uपूर्णांक8_t      FanTachEdgePerRev;
    
  // The following are AFC override parameters. Leave at 0 to use FW शेषs.
  पूर्णांक16_t      FuzzyFan_ErrorSetDelta;
  पूर्णांक16_t      FuzzyFan_ErrorRateSetDelta;
  पूर्णांक16_t      FuzzyFan_PwmSetDelta;
  uपूर्णांक16_t     FuzzyFan_Reserved;

  // SECTION: AVFS 
  // Overrides
  uपूर्णांक8_t           OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t           dBtcGbGfxDfllModelSelect;  //0 -> fused piece-wise model, 1 -> piece-wise linear(PPTable), 2 -> quadratic model(PPTable)  
  uपूर्णांक8_t           Padding8_Avfs;

  QuadraticInt_t    qAvfsGb[AVFS_VOLTAGE_COUNT];              // GHz->V Override of fused curve 
  DroopInt_t        dBtcGbGfxPll;         // GHz->V BtcGb
  DroopInt_t        dBtcGbGfxDfll;        // GHz->V BtcGb
  DroopInt_t        dBtcGbSoc;            // GHz->V BtcGb
  LinearInt_t       qAgingGb[AVFS_VOLTAGE_COUNT];          // GHz->V 

  PiecewiseLinearDroopInt_t   PiecewiseLinearDroopIntGfxDfll; //GHz ->Vstore in IEEE भग्न क्रमmat

  QuadraticInt_t    qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V 

  uपूर्णांक16_t          DcTol[AVFS_VOLTAGE_COUNT];            // mV Q2

  uपूर्णांक8_t           DcBtcEnabled[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t           Padding8_GfxBtc[2];

  uपूर्णांक16_t          DcBtcMin[AVFS_VOLTAGE_COUNT];       // mV Q2
  uपूर्णांक16_t          DcBtcMax[AVFS_VOLTAGE_COUNT];       // mV Q2

  uपूर्णांक16_t          DcBtcGb[AVFS_VOLTAGE_COUNT];       // mV Q2
  
  // SECTION: XGMI
  uपूर्णांक8_t           XgmiDpmPstates[NUM_XGMI_LEVELS]; // 2 DPM states, high and low.  0-P0, 1-P1, 2-P2, 3-P3.
  uपूर्णांक8_t           XgmiDpmSpare[2];

  // SECTION: Advanced Options
  uपूर्णांक32_t          DebugOverrides;
  QuadraticInt_t    ReservedEquation0; 
  QuadraticInt_t    ReservedEquation1; 
  QuadraticInt_t    ReservedEquation2; 
  QuadraticInt_t    ReservedEquation3; 

  // SECTION: Sku Reserved
  uपूर्णांक8_t          CustomerVariant;

  //VC BTC parameters are only applicable to VDD_GFX करोमुख्य
  uपूर्णांक8_t          VcBtcEnabled;
  uपूर्णांक16_t         VcBtcVminT0;                 // T0_VMIN
  uपूर्णांक16_t         VcBtcFixedVminAgingOffset;   // FIXED_VMIN_AGING_OFFSET 
  uपूर्णांक16_t         VcBtcVmin2PsmDegrationGb;    // VMIN_TO_PSM_DEGRADATION_GB 
  uपूर्णांक32_t         VcBtcPsmA;                   // A_PSM
  uपूर्णांक32_t         VcBtcPsmB;                   // B_PSM
  uपूर्णांक32_t         VcBtcVminA;                  // A_VMIN
  uपूर्णांक32_t         VcBtcVminB;                  // B_VMIN  
  
  //GPIO Board feature
  uपूर्णांक16_t         LedGpio;            //GeneriA GPIO flag used to control the radeon LEDs
  uपूर्णांक16_t         GfxPowerStagesGpio; //Genlk_vsync GPIO flag used to control gfx घातer stages 
  
  uपूर्णांक32_t         SkuReserved[8];


  // MAJOR SECTION: BOARD PARAMETERS

  //SECTION: Gaming Clocks
  uपूर्णांक32_t     GamingClk[6];

  // SECTION: I2C Control
  I2cControllerConfig_t  I2cControllers[NUM_I2C_CONTROLLERS];     

  uपूर्णांक8_t      GpioScl;  // GPIO Number क्रम SCL Line, used only क्रम CKSVII2C1
  uपूर्णांक8_t      GpioSda;  // GPIO Number क्रम SDA Line, used only क्रम CKSVII2C1
  uपूर्णांक8_t      FchUsbPdSlaveAddr; //For requesting USB PD controller S-states via FCH I2C when entering PME turn off
  uपूर्णांक8_t      I2cSpare[1];

  // SECTION: SVI2 Board Parameters
  uपूर्णांक8_t      VddGfxVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddSocVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem0VrMapping;  // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem1VrMapping;  // Use VR_MAPPING* bitfields

  uपूर्णांक8_t      GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      VddciUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      MvddUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode

  // SECTION: Telemetry Settings
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

  uपूर्णांक32_t     MvddRatio; // This is used क्रम MVDD  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)
  
  // SECTION: GPIO Settings
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
  uपूर्णांक8_t      LedEnableMask;

  uपूर्णांक8_t      LedPcie;        // GPIO number क्रम PCIE results
  uपूर्णांक8_t      LedError;       // GPIO number क्रम Error Cases
  uपूर्णांक8_t      LedSpare1[2];

  // SECTION: Clock Spपढ़ो Spectrum
  
  // GFXCLK PLL Spपढ़ो Spectrum
  uपूर्णांक8_t      PllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      PllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     PllGfxclkSpपढ़ोFreq;      // kHz

  // GFXCLK DFLL Spपढ़ो Spectrum
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     DfllGfxclkSpपढ़ोFreq;      // kHz
  
  // UCLK Spपढ़ो Spectrum
  uपूर्णांक16_t     UclkSpपढ़ोPadding;
  uपूर्णांक16_t     UclkSpपढ़ोFreq;      // kHz

  // FCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      FclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      FclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     FclkSpपढ़ोFreq;      // kHz
  
  // Section: Memory Config
  uपूर्णांक32_t     MemoryChannelEnabled; // For DRAM use only, Max 32 channels enabled bit mask. 
  
  uपूर्णांक8_t      DramBitWidth; // For DRAM use only.  See Dram Bit width type defines
  uपूर्णांक8_t      PaddingMem1[3];

  // Section: Total Board Power
  uपूर्णांक16_t     TotalBoardPower;     //Only needed क्रम TCP Estimated हाल, where TCP = TGP+Total Board Power
  uपूर्णांक16_t     BoardPowerPadding; 
  
  // SECTION: XGMI Training
  uपूर्णांक8_t      XgmiLinkSpeed   [NUM_XGMI_PSTATE_LEVELS];
  uपूर्णांक8_t      XgmiLinkWidth   [NUM_XGMI_PSTATE_LEVELS];

  uपूर्णांक16_t     XgmiFclkFreq    [NUM_XGMI_PSTATE_LEVELS];
  uपूर्णांक16_t     XgmiSocVoltage  [NUM_XGMI_PSTATE_LEVELS];

  // SECTION: UMC feature flags
  uपूर्णांक8_t      HsrEnabled;
  uपूर्णांक8_t      VddqOffEnabled;
  uपूर्णांक8_t      PaddingUmcFlags[2];

  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      UclkSpपढ़ोPercent[16];   

  // SECTION: Board Reserved
  uपूर्णांक32_t     BoardReserved[11];

  // SECTION: Structure Padding

  // Padding क्रम MMHUB - करो not modअगरy this
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use

पूर्ण PPTable_t;

प्रकार काष्ठा अणु
  // Time स्थिरant parameters क्रम घड़ी averages in ms
  uपूर्णांक16_t     GfxclkAverageLpfTau;
  uपूर्णांक16_t     FclkAverageLpfTau;
  uपूर्णांक16_t     UclkAverageLpfTau;
  uपूर्णांक16_t     GfxActivityLpfTau;
  uपूर्णांक16_t     UclkActivityLpfTau;
  uपूर्णांक16_t     SocketPowerLpfTau;  
  uपूर्णांक16_t     VcnClkAverageLpfTau;
  uपूर्णांक16_t     padding16; 
पूर्ण DriverSmuConfig_t;

प्रकार काष्ठा अणु
  DriverSmuConfig_t DriverSmuConfig;

  uपूर्णांक32_t     Spare[7];  
  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण DriverSmuConfigExternal_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t               GfxclkFmin;           // MHz
  uपूर्णांक16_t               GfxclkFmax;           // MHz
  QuadraticInt_t         CustomGfxVfCurve;     // a: mV/MHz^2, b: mv/MHz, c: mV
  uपूर्णांक16_t               CustomCurveFmin;      // MHz 
  uपूर्णांक16_t               UclkFmin;             // MHz  
  uपूर्णांक16_t               UclkFmax;             // MHz
  पूर्णांक16_t                OverDrivePct;         // %
  uपूर्णांक16_t               FanMaximumRpm;
  uपूर्णांक16_t               FanMinimumPwm;
  uपूर्णांक16_t               FanAcousticLimitRpm;
  uपूर्णांक16_t               FanTargetTemperature; // Degree Celcius 
  uपूर्णांक8_t                FanLinearPwmPoपूर्णांकs[NUM_OD_FAN_MAX_POINTS];
  uपूर्णांक8_t                FanLinearTempPoपूर्णांकs[NUM_OD_FAN_MAX_POINTS];
  uपूर्णांक16_t               MaxOpTemp;            // Degree Celcius
  पूर्णांक16_t                VddGfxOffset;         // in mV
  uपूर्णांक8_t                FanZeroRpmEnable;
  uपूर्णांक8_t                FanZeroRpmStopTemp;
  uपूर्णांक8_t                FanMode;
  uपूर्णांक8_t                Padding[1];
पूर्ण OverDriveTable_t; 

प्रकार काष्ठा अणु
  OverDriveTable_t OverDriveTable;
  uपूर्णांक32_t      Spare[8];  

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use    
पूर्ण OverDriveTableExternal_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t CurrClock[PPCLK_COUNT];

  uपूर्णांक16_t AverageGfxclkFrequencyPreDs;
  uपूर्णांक16_t AverageGfxclkFrequencyPostDs;
  uपूर्णांक16_t AverageFclkFrequencyPreDs;
  uपूर्णांक16_t AverageFclkFrequencyPostDs;
  uपूर्णांक16_t AverageUclkFrequencyPreDs  ;
  uपूर्णांक16_t AverageUclkFrequencyPostDs  ;

  
  uपूर्णांक16_t AverageGfxActivity    ;
  uपूर्णांक16_t AverageUclkActivity   ;
  uपूर्णांक8_t  CurrSocVoltageOffset  ;
  uपूर्णांक8_t  CurrGfxVoltageOffset  ;
  uपूर्णांक8_t  CurrMemVidOffset      ;
  uपूर्णांक8_t  Padding8        ;
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
  uपूर्णांक8_t  CurrFanPwm;
  uपूर्णांक16_t CurrFanSpeed;

  //BACO metrics, PMFW-1721
  //metrics क्रम D3hot entry/निकास and driver ARM msgs
  uपूर्णांक8_t D3HotEntryCountPerMode[D3HOT_SEQUENCE_COUNT];
  uपूर्णांक8_t D3HotExitCountPerMode[D3HOT_SEQUENCE_COUNT];
  uपूर्णांक8_t ArmMsgReceivedCountPerMode[D3HOT_SEQUENCE_COUNT];

  //PMFW-4362
  uपूर्णांक32_t EnergyAccumulator;
  uपूर्णांक16_t AverageVclk0Frequency  ;
  uपूर्णांक16_t AverageDclk0Frequency  ;  
  uपूर्णांक16_t AverageVclk1Frequency  ;
  uपूर्णांक16_t AverageDclk1Frequency  ;  
  uपूर्णांक16_t VcnActivityPercentage  ; //place holder, David N. to provide full sequence
  uपूर्णांक8_t  PcieRate               ;
  uपूर्णांक8_t  PcieWidth              ;
  uपूर्णांक16_t AverageGfxclkFrequencyTarget;
  uपूर्णांक16_t Padding16_2;

पूर्ण SmuMetrics_t;

प्रकार काष्ठा अणु
  SmuMetrics_t SmuMetrics;
  uपूर्णांक32_t Spare[1];

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use  
पूर्ण SmuMetricsExternal_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t MinClock; // This is either DCEFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MaxClock; // This is either DCEFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MinUclk;
  uपूर्णांक16_t MaxUclk;
  
  uपूर्णांक8_t  WmSetting;
  uपूर्णांक8_t  Flags;
  uपूर्णांक8_t  Padding[2];

पूर्ण WatermarkRowGeneric_t;

#घोषणा NUM_WM_RANGES 4

प्रकार क्रमागत अणु
  WM_SOCCLK = 0,
  WM_DCEFCLK,
  WM_COUNT,
पूर्ण WM_CLOCK_e;

प्रकार क्रमागत अणु
  WATERMARKS_CLOCK_RANGE = 0,
  WATERMARKS_DUMMY_PSTATE,
  WATERMARKS_MALL,
  WATERMARKS_COUNT,
पूर्ण WATERMARKS_FLAGS_e;

प्रकार काष्ठा अणु
  // Watermarks
  WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];
पूर्ण Watermarks_t;

प्रकार काष्ठा अणु
  Watermarks_t Watermarks;

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण WatermarksExternal_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t avgPsmCount[67];
  uपूर्णांक16_t minPsmCount[67];
  भग्न    avgPsmVoltage[67]; 
  भग्न    minPsmVoltage[67];
पूर्ण AvfsDebugTable_t;

प्रकार काष्ठा अणु
  AvfsDebugTable_t AvfsDebugTable;

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण AvfsDebugTableExternal_t;

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

  uपूर्णांक32_t EnabledAvfsModules[3]; //Sienna_Cichlid - 67 AVFS modules
पूर्ण AvfsFuseOverride_t;

प्रकार काष्ठा अणु
  AvfsFuseOverride_t AvfsFuseOverride;

  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण AvfsFuseOverrideExternal_t;

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
  
  uपूर्णांक8_t   Fclk_ActiveHystLimit;
  uपूर्णांक8_t   Fclk_IdleHystLimit;
  uपूर्णांक8_t   Fclk_FPS;
  uपूर्णांक8_t   Fclk_MinActiveFreqType;
  uपूर्णांक8_t   Fclk_BoosterFreqType; 
  uपूर्णांक8_t   Fclk_MinFreqStep;                // Minimum delta between current and target frequeny in order क्रम FW to change घड़ी.
  uपूर्णांक16_t  Fclk_MinActiveFreq;              // MHz
  uपूर्णांक16_t  Fclk_BoosterFreq;                // MHz
  uपूर्णांक16_t  Fclk_PD_Data_समय_स्थिरant;      // Time स्थिरant of PD controller in ms
  uपूर्णांक32_t  Fclk_PD_Data_limit_a;            // Q16
  uपूर्णांक32_t  Fclk_PD_Data_limit_b;            // Q16
  uपूर्णांक32_t  Fclk_PD_Data_limit_c;            // Q16
  uपूर्णांक32_t  Fclk_PD_Data_error_coeff;        // Q16
  uपूर्णांक32_t  Fclk_PD_Data_error_rate_coeff;   // Q16
  
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

पूर्ण DpmActivityMonitorCoeffInt_t;


प्रकार काष्ठा अणु
  DpmActivityMonitorCoeffInt_t DpmActivityMonitorCoeffInt;
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use  
पूर्ण DpmActivityMonitorCoeffIntExternal_t;

// Workload bits
#घोषणा WORKLOAD_PPLIB_DEFAULT_BIT        0 
#घोषणा WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 1 
#घोषणा WORKLOAD_PPLIB_POWER_SAVING_BIT   2 
#घोषणा WORKLOAD_PPLIB_VIDEO_BIT          3 
#घोषणा WORKLOAD_PPLIB_VR_BIT             4 
#घोषणा WORKLOAD_PPLIB_COMPUTE_BIT        5 
#घोषणा WORKLOAD_PPLIB_CUSTOM_BIT         6 
#घोषणा WORKLOAD_PPLIB_W3D_BIT            7 
#घोषणा WORKLOAD_PPLIB_COUNT              8 


// These defines are used with the following messages:
// SMC_MSG_TransferTableDram2Smu
// SMC_MSG_TransferTableSmu2Dram

// Table transfer status
#घोषणा TABLE_TRANSFER_OK         0x0
#घोषणा TABLE_TRANSFER_FAILED     0xFF

// Table types
#घोषणा TABLE_PPTABLE                 0
#घोषणा TABLE_WATERMARKS              1
#घोषणा TABLE_AVFS_PSM_DEBUG          2
#घोषणा TABLE_AVFS_FUSE_OVERRIDE      3
#घोषणा TABLE_PMSTATUSLOG             4
#घोषणा TABLE_SMU_METRICS             5
#घोषणा TABLE_DRIVER_SMU_CONFIG       6
#घोषणा TABLE_ACTIVITY_MONITOR_COEFF  7
#घोषणा TABLE_OVERDRIVE               8
#घोषणा TABLE_I2C_COMMANDS            9
#घोषणा TABLE_PACE                   10
#घोषणा TABLE_COUNT                  11

प्रकार काष्ठा अणु
  भग्न FlopsPerByteTable[RLC_PACE_TABLE_NUM_LEVELS];
पूर्ण RlcPaceFlopsPerByteOverride_t;

प्रकार काष्ठा अणु
  RlcPaceFlopsPerByteOverride_t RlcPaceFlopsPerByteOverride;
  
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use  
पूर्ण RlcPaceFlopsPerByteOverrideExternal_t;

// These defines are used with the SMC_MSG_SetUclkFastSwitch message.
#घोषणा UCLK_SWITCH_SLOW 0
#घोषणा UCLK_SWITCH_FAST 1
#पूर्ण_अगर
