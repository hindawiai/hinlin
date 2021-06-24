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

#अगर_अघोषित SMU11_DRIVER_IF_ARCTURUS_H
#घोषणा SMU11_DRIVER_IF_ARCTURUS_H

// *** IMPORTANT ***
// SMU TEAM: Always increment the पूर्णांकerface version अगर
// any काष्ठाure is changed in this file
//#घोषणा SMU11_DRIVER_IF_VERSION 0x09

#घोषणा PPTABLE_ARCTURUS_SMU_VERSION 4

#घोषणा NUM_GFXCLK_DPM_LEVELS  16
#घोषणा NUM_VCLK_DPM_LEVELS    8
#घोषणा NUM_DCLK_DPM_LEVELS    8
#घोषणा NUM_MP0CLK_DPM_LEVELS  2
#घोषणा NUM_SOCCLK_DPM_LEVELS  8
#घोषणा NUM_UCLK_DPM_LEVELS    4
#घोषणा NUM_FCLK_DPM_LEVELS    8
#घोषणा NUM_XGMI_LEVELS        2
#घोषणा NUM_XGMI_PSTATE_LEVELS 4

#घोषणा MAX_GFXCLK_DPM_LEVEL  (NUM_GFXCLK_DPM_LEVELS  - 1)
#घोषणा MAX_VCLK_DPM_LEVEL    (NUM_VCLK_DPM_LEVELS    - 1)
#घोषणा MAX_DCLK_DPM_LEVEL    (NUM_DCLK_DPM_LEVELS    - 1)
#घोषणा MAX_MP0CLK_DPM_LEVEL  (NUM_MP0CLK_DPM_LEVELS  - 1)
#घोषणा MAX_SOCCLK_DPM_LEVEL  (NUM_SOCCLK_DPM_LEVELS  - 1)
#घोषणा MAX_UCLK_DPM_LEVEL    (NUM_UCLK_DPM_LEVELS    - 1)
#घोषणा MAX_FCLK_DPM_LEVEL    (NUM_FCLK_DPM_LEVELS    - 1)
#घोषणा MAX_XGMI_LEVEL        (NUM_XGMI_LEVELS        - 1)
#घोषणा MAX_XGMI_PSTATE_LEVEL (NUM_XGMI_PSTATE_LEVELS - 1)

// Feature Control Defines
// DPM
#घोषणा FEATURE_DPM_PREFETCHER_BIT      0
#घोषणा FEATURE_DPM_GFXCLK_BIT          1
#घोषणा FEATURE_DPM_UCLK_BIT            2
#घोषणा FEATURE_DPM_SOCCLK_BIT          3
#घोषणा FEATURE_DPM_FCLK_BIT            4
#घोषणा FEATURE_DPM_MP0CLK_BIT          5
#घोषणा FEATURE_DPM_XGMI_BIT            6
// Idle
#घोषणा FEATURE_DS_GFXCLK_BIT           7
#घोषणा FEATURE_DS_SOCCLK_BIT           8
#घोषणा FEATURE_DS_LCLK_BIT             9
#घोषणा FEATURE_DS_FCLK_BIT             10
#घोषणा FEATURE_DS_UCLK_BIT             11
#घोषणा FEATURE_GFX_ULV_BIT             12
#घोषणा FEATURE_DPM_VCN_BIT             13
#घोषणा FEATURE_RSMU_SMN_CG_BIT         14
#घोषणा FEATURE_WAFL_CG_BIT             15
// Throttler/Response
#घोषणा FEATURE_PPT_BIT                 16
#घोषणा FEATURE_TDC_BIT                 17
#घोषणा FEATURE_APCC_PLUS_BIT           18
#घोषणा FEATURE_VR0HOT_BIT              19
#घोषणा FEATURE_VR1HOT_BIT              20
#घोषणा FEATURE_FW_CTF_BIT              21
#घोषणा FEATURE_FAN_CONTROL_BIT         22
#घोषणा FEATURE_THERMAL_BIT             23
// Other
#घोषणा FEATURE_OUT_OF_BAND_MONITOR_BIT 24
#घोषणा FEATURE_TEMP_DEPENDENT_VMIN_BIT 25
#घोषणा FEATURE_PER_PART_VMIN_BIT       26

#घोषणा FEATURE_SPARE_27_BIT            27
#घोषणा FEATURE_SPARE_28_BIT            28
#घोषणा FEATURE_SPARE_29_BIT            29
#घोषणा FEATURE_SPARE_30_BIT            30
#घोषणा FEATURE_SPARE_31_BIT            31
#घोषणा FEATURE_SPARE_32_BIT            32
#घोषणा FEATURE_SPARE_33_BIT            33
#घोषणा FEATURE_SPARE_34_BIT            34
#घोषणा FEATURE_SPARE_35_BIT            35
#घोषणा FEATURE_SPARE_36_BIT            36
#घोषणा FEATURE_SPARE_37_BIT            37
#घोषणा FEATURE_SPARE_38_BIT            38
#घोषणा FEATURE_SPARE_39_BIT            39
#घोषणा FEATURE_SPARE_40_BIT            40
#घोषणा FEATURE_SPARE_41_BIT            41
#घोषणा FEATURE_SPARE_42_BIT            42
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


#घोषणा FEATURE_DPM_PREFETCHER_MASK       (1 << FEATURE_DPM_PREFETCHER_BIT       )
#घोषणा FEATURE_DPM_GFXCLK_MASK           (1 << FEATURE_DPM_GFXCLK_BIT           )
#घोषणा FEATURE_DPM_UCLK_MASK             (1 << FEATURE_DPM_UCLK_BIT             )
#घोषणा FEATURE_DPM_SOCCLK_MASK           (1 << FEATURE_DPM_SOCCLK_BIT           )
#घोषणा FEATURE_DPM_FCLK_MASK             (1 << FEATURE_DPM_FCLK_BIT             )
#घोषणा FEATURE_DPM_MP0CLK_MASK           (1 << FEATURE_DPM_MP0CLK_BIT           )
#घोषणा FEATURE_DPM_XGMI_MASK             (1 << FEATURE_DPM_XGMI_BIT             )

#घोषणा FEATURE_DS_GFXCLK_MASK            (1 << FEATURE_DS_GFXCLK_BIT            )
#घोषणा FEATURE_DS_SOCCLK_MASK            (1 << FEATURE_DS_SOCCLK_BIT            )
#घोषणा FEATURE_DS_LCLK_MASK              (1 << FEATURE_DS_LCLK_BIT              )
#घोषणा FEATURE_DS_FCLK_MASK              (1 << FEATURE_DS_FCLK_BIT              )
#घोषणा FEATURE_DS_UCLK_MASK              (1 << FEATURE_DS_UCLK_BIT              )
#घोषणा FEATURE_GFX_ULV_MASK              (1 << FEATURE_GFX_ULV_BIT              )
#घोषणा FEATURE_DPM_VCN_MASK              (1 << FEATURE_DPM_VCN_BIT              )
#घोषणा FEATURE_RSMU_SMN_CG_MASK          (1 << FEATURE_RSMU_SMN_CG_BIT          )
#घोषणा FEATURE_WAFL_CG_MASK              (1 << FEATURE_WAFL_CG_BIT              )

#घोषणा FEATURE_PPT_MASK                  (1 << FEATURE_PPT_BIT                  )
#घोषणा FEATURE_TDC_MASK                  (1 << FEATURE_TDC_BIT                  )
#घोषणा FEATURE_APCC_PLUS_MASK            (1 << FEATURE_APCC_PLUS_BIT            )
#घोषणा FEATURE_VR0HOT_MASK               (1 << FEATURE_VR0HOT_BIT               )
#घोषणा FEATURE_VR1HOT_MASK               (1 << FEATURE_VR1HOT_BIT               )
#घोषणा FEATURE_FW_CTF_MASK               (1 << FEATURE_FW_CTF_BIT               )
#घोषणा FEATURE_FAN_CONTROL_MASK          (1 << FEATURE_FAN_CONTROL_BIT          )
#घोषणा FEATURE_THERMAL_MASK              (1 << FEATURE_THERMAL_BIT              )

#घोषणा FEATURE_OUT_OF_BAND_MONITOR_MASK  (1 << FEATURE_OUT_OF_BAND_MONITOR_BIT   )
#घोषणा FEATURE_TEMP_DEPENDENT_VMIN_MASK  (1 << FEATURE_TEMP_DEPENDENT_VMIN_BIT )
#घोषणा FEATURE_PER_PART_VMIN_MASK        (1 << FEATURE_PER_PART_VMIN_BIT        )


//FIXME need updating
// Debug Overrides Biपंचांगask
#घोषणा DPM_OVERRIDE_DISABLE_UCLK_PID               0x00000001
#घोषणा DPM_OVERRIDE_DISABLE_VOLT_LINK_VCN_FCLK     0x00000002

// I2C Config Bit Defines
#घोषणा I2C_CONTROLLER_ENABLED           1
#घोषणा I2C_CONTROLLER_DISABLED          0

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
#घोषणा THROTTLER_TEMP_VR_MEM_BIT  5
#घोषणा THROTTLER_TEMP_VR_SOC_BIT  6
#घोषणा THROTTLER_TDC_GFX_BIT      7
#घोषणा THROTTLER_TDC_SOC_BIT      8
#घोषणा THROTTLER_PPT0_BIT         9
#घोषणा THROTTLER_PPT1_BIT         10
#घोषणा THROTTLER_PPT2_BIT         11
#घोषणा THROTTLER_PPT3_BIT         12
#घोषणा THROTTLER_PPM_BIT          13
#घोषणा THROTTLER_FIT_BIT          14
#घोषणा THROTTLER_APCC_BIT         15
#घोषणा THROTTLER_VRHOT0_BIT       16
#घोषणा THROTTLER_VRHOT1_BIT       17

// Table transfer status
#घोषणा TABLE_TRANSFER_OK         0x0
#घोषणा TABLE_TRANSFER_FAILED     0xFF
#घोषणा TABLE_TRANSFER_PENDING    0xAB

// Workload bits
#घोषणा WORKLOAD_PPLIB_DEFAULT_BIT        0
#घोषणा WORKLOAD_PPLIB_POWER_SAVING_BIT   1
#घोषणा WORKLOAD_PPLIB_VIDEO_BIT          2
#घोषणा WORKLOAD_PPLIB_COMPUTE_BIT        3
#घोषणा WORKLOAD_PPLIB_CUSTOM_BIT         4
#घोषणा WORKLOAD_PPLIB_COUNT              5

//XGMI perक्रमmance states
#घोषणा XGMI_STATE_D0 1
#घोषणा XGMI_STATE_D3 0

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
  I2C_CONTROLLER_NAME_VR_MEM,
  I2C_CONTROLLER_NAME_SPARE,
  I2C_CONTROLLER_NAME_COUNT,
पूर्ण I2cControllerName_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_THROTTLER_TYPE_NONE = 0,
  I2C_CONTROLLER_THROTTLER_VR_GFX,
  I2C_CONTROLLER_THROTTLER_VR_SOC,
  I2C_CONTROLLER_THROTTLER_VR_MEM,
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
  GFXCLK_SOURCE_AFLL,
  GFXCLK_SOURCE_COUNT,
पूर्ण GfxclkSrc_e;

प्रकार क्रमागत अणु
  PPCLK_GFXCLK,
  PPCLK_VCLK,
  PPCLK_DCLK,
  PPCLK_SOCCLK,
  PPCLK_UCLK,
  PPCLK_FCLK,
  PPCLK_COUNT,
पूर्ण PPCLK_e;

प्रकार क्रमागत अणु
  POWER_SOURCE_AC,
  POWER_SOURCE_DC,
  POWER_SOURCE_COUNT,
पूर्ण POWER_SOURCE_e;

प्रकार क्रमागत अणु
  TEMP_EDGE,
  TEMP_HOTSPOT,
  TEMP_MEM,
  TEMP_VR_GFX,
  TEMP_VR_SOC,
  TEMP_VR_MEM,
  TEMP_COUNT
पूर्ण TEMP_TYPE_e;

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
  XGMI_LINK_WIDTH_1 = 1,   // x1
  XGMI_LINK_WIDTH_2 = 2,   // x2
  XGMI_LINK_WIDTH_4 = 4,   // x4
  XGMI_LINK_WIDTH_8 = 8,   // x8
  XGMI_LINK_WIDTH_9 = 9,   // x9
  XGMI_LINK_WIDTH_16 = 16, // x16
  XGMI_LINK_WIDTH_COUNT
पूर्ण XGMI_LINK_WIDTH_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t        VoltageMode;         // 0 - AVFS only, 1- min(AVFS,SS), 2-SS only
  uपूर्णांक8_t        SnapToDiscrete;      // 0 - Fine grained DPM, 1 - Discrete DPM
  uपूर्णांक8_t        NumDiscreteLevels;   // Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used
  uपूर्णांक8_t        padding;
  LinearInt_t    ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
  QuadraticInt_t SsCurve;             // Slow-slow curve (GHz->V)
  uपूर्णांक16_t       SsFmin;              // Fmin क्रम SS curve. If SS curve is selected, will use V@SSFmin क्रम F <= Fmin
  uपूर्णांक16_t       Padding16;
पूर्ण DpmDescriptor_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t Version;

  // SECTION: Feature Enablement
  uपूर्णांक32_t FeaturesToRun[2];

  // SECTION: Infraकाष्ठाure Limits
  uपूर्णांक16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT];
  uपूर्णांक16_t SocketPowerLimitAcTau[PPT_THROTTLER_COUNT];
  uपूर्णांक16_t TdcLimitSoc;             // Amps
  uपूर्णांक16_t TdcLimitSocTau;          // Time स्थिरant of LPF in ms
  uपूर्णांक16_t TdcLimitGfx;             // Amps
  uपूर्णांक16_t TdcLimitGfxTau;          // Time स्थिरant of LPF in ms

  uपूर्णांक16_t TedgeLimit;              // Celcius
  uपूर्णांक16_t ThotspotLimit;           // Celcius
  uपूर्णांक16_t TmemLimit;               // Celcius
  uपूर्णांक16_t Tvr_gfxLimit;            // Celcius
  uपूर्णांक16_t Tvr_memLimit;            // Celcius
  uपूर्णांक16_t Tvr_socLimit;            // Celcius
  uपूर्णांक32_t FitLimit;                // Failures in समय (failures per million parts over the defined lअगरeसमय)

  uपूर्णांक16_t PpmPowerLimit;           // Switch this this घातer limit when temperature is above PpmTempThreshold
  uपूर्णांक16_t PpmTemperatureThreshold;

  // SECTION: Throttler settings
  uपूर्णांक32_t ThrottlerControlMask;   // See Throtter masks defines

  // SECTION: ULV Settings
  uपूर्णांक16_t  UlvVoltageOffsetGfx; // In mV(Q2)
  uपूर्णांक16_t  UlvPadding;          // Padding

  uपूर्णांक8_t  UlvGfxclkBypass;  // 1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV
  uपूर्णांक8_t  Padding234[3];

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
  uपूर्णांक16_t       FreqTableFclk     [NUM_FCLK_DPM_LEVELS    ];     // In MHz

  uपूर्णांक32_t       Paddingclks[16];

  // SECTION: DPM Config 2
  uपूर्णांक16_t       Mp0clkFreq        [NUM_MP0CLK_DPM_LEVELS];       // in MHz
  uपूर्णांक16_t       Mp0DpmVoltage     [NUM_MP0CLK_DPM_LEVELS];       // mV(Q2)

  // GFXCLK DPM
  uपूर्णांक16_t        GfxclkFidle;          // In MHz
  uपूर्णांक16_t        GfxclkSlewRate;       // क्रम PLL babystepping???
  uपूर्णांक8_t         Padding567[4];
  uपूर्णांक16_t        GfxclkDsMaxFreq;      // In MHz
  uपूर्णांक8_t         GfxclkSource;         // 0 = PLL, 1 = AFLL
  uपूर्णांक8_t         Padding456;

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
  uपूर्णांक16_t     FanGainVrGfx;
  uपूर्णांक16_t     FanGainVrSoc;
  uपूर्णांक16_t     FanGainVrMem;
  uपूर्णांक16_t     FanGainHbm;
  uपूर्णांक16_t     FanPwmMin;
  uपूर्णांक16_t     FanAcousticLimitRpm;
  uपूर्णांक16_t     FanThrottlingRpm;
  uपूर्णांक16_t     FanMaximumRpm;
  uपूर्णांक16_t     FanTargetTemperature;
  uपूर्णांक16_t     FanTargetGfxclk;
  uपूर्णांक8_t      FanZeroRpmEnable;
  uपूर्णांक8_t      FanTachEdgePerRev;
  uपूर्णांक8_t      FanTempInputSelect;
  uपूर्णांक8_t      padding8_Fan;

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
  DroopInt_t        dBtcGbGfxPll;       // GHz->V BtcGb
  DroopInt_t        dBtcGbGfxAfll;        // GHz->V BtcGb
  DroopInt_t        dBtcGbSoc;            // GHz->V BtcGb
  LinearInt_t       qAgingGb[AVFS_VOLTAGE_COUNT];          // GHz->V

  QuadraticInt_t    qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V

  uपूर्णांक16_t          DcTol[AVFS_VOLTAGE_COUNT];            // mV Q2

  uपूर्णांक8_t           DcBtcEnabled[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t           Padding8_GfxBtc[2];

  uपूर्णांक16_t          DcBtcMin[AVFS_VOLTAGE_COUNT];       // mV Q2
  uपूर्णांक16_t          DcBtcMax[AVFS_VOLTAGE_COUNT];       // mV Q2

  uपूर्णांक16_t          DcBtcGb[AVFS_VOLTAGE_COUNT];        // mV Q2

  // SECTION: XGMI
  uपूर्णांक8_t           XgmiDpmPstates[NUM_XGMI_LEVELS]; // 2 DPM states, high and low.  0-P0, 1-P1, 2-P2, 3-P3.
  uपूर्णांक8_t           XgmiDpmSpare[2];

  // Temperature Dependent Vmin
  uपूर्णांक16_t     VDDGFX_TVmin;       //Celcius
  uपूर्णांक16_t     VDDSOC_TVmin;       //Celcius
  uपूर्णांक16_t     VDDGFX_Vmin_HiTemp; // mV Q2
  uपूर्णांक16_t     VDDGFX_Vmin_LoTemp; // mV Q2
  uपूर्णांक16_t     VDDSOC_Vmin_HiTemp; // mV Q2
  uपूर्णांक16_t     VDDSOC_Vmin_LoTemp; // mV Q2

  uपूर्णांक16_t     VDDGFX_TVminHystersis; // Celcius
  uपूर्णांक16_t     VDDSOC_TVminHystersis; // Celcius


  // SECTION: Advanced Options
  uपूर्णांक32_t          DebugOverrides;
  QuadraticInt_t    ReservedEquation0;
  QuadraticInt_t    ReservedEquation1;
  QuadraticInt_t    ReservedEquation2;
  QuadraticInt_t    ReservedEquation3;

  uपूर्णांक16_t     MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode
  uपूर्णांक16_t     PaddingUlv;       // Padding

  // Total Power configuration, use defines from PwrConfig_e
  uपूर्णांक8_t      TotalPowerConfig;    //0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measured
  uपूर्णांक8_t      TotalPowerSpare1;
  uपूर्णांक16_t     TotalPowerSpare2;

  // APCC Settings
  uपूर्णांक16_t     PccThresholdLow;
  uपूर्णांक16_t     PccThresholdHigh;
  uपूर्णांक32_t     PaddingAPCC[6];  //FIXME pending SPEC

  // OOB Settings
  uपूर्णांक16_t BasePerक्रमmanceCardPower;
  uपूर्णांक16_t MaxPerक्रमmanceCardPower;
  uपूर्णांक16_t BasePerक्रमmanceFrequencyCap;   //In Mhz
  uपूर्णांक16_t MaxPerक्रमmanceFrequencyCap;    //In Mhz

  // Per-Part Vmin
  uपूर्णांक16_t VDDGFX_VminLow;        // mv Q2
  uपूर्णांक16_t VDDGFX_TVminLow;       //Celcius
  uपूर्णांक16_t VDDGFX_VminLow_HiTemp; // mv Q2
  uपूर्णांक16_t VDDGFX_VminLow_LoTemp; // mv Q2

  // SECTION: Reserved
  uपूर्णांक32_t     Reserved[7];

  // SECTION: BOARD PARAMETERS

  // SVI2 Board Parameters
  uपूर्णांक16_t     MaxVoltageStepGfx; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.
  uपूर्णांक16_t     MaxVoltageStepSoc; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.

  uपूर्णांक8_t      VddGfxVrMapping;     // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddSocVrMapping;     // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMemVrMapping;     // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      BoardVrMapping;      // Use VR_MAPPING* bitfields

  uपूर्णांक8_t      GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      ExternalSensorPresent; // External RDI connected to TMON (aka TEMP IN)
  uपूर्णांक8_t      Padding8_V[2];

  // Telemetry Settings
  uपूर्णांक16_t     GfxMaxCurrent;   // in Amps
  पूर्णांक8_t       GfxOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryGfx;

  uपूर्णांक16_t     SocMaxCurrent;   // in Amps
  पूर्णांक8_t       SocOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetrySoc;

  uपूर्णांक16_t     MemMaxCurrent;   // in Amps
  पूर्णांक8_t       MemOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem;

  uपूर्णांक16_t     BoardMaxCurrent;   // in Amps
  पूर्णांक8_t       BoardOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryBoardInput;

  // GPIO Settings
  uपूर्णांक8_t      VR0HotGpio;      // GPIO pin configured क्रम VR0 HOT event
  uपूर्णांक8_t      VR0HotPolarity;  // GPIO polarity क्रम VR0 HOT event
  uपूर्णांक8_t      VR1HotGpio;      // GPIO pin configured क्रम VR1 HOT event
  uपूर्णांक8_t      VR1HotPolarity;  // GPIO polarity क्रम VR1 HOT event

  // GFXCLK PLL Spपढ़ो Spectrum
  uपूर्णांक8_t      PllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      PllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     PllGfxclkSpपढ़ोFreq;      // kHz

  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      UclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      UclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     UclkSpपढ़ोFreq;      // kHz

  // FCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      FclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      FclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     FclkSpपढ़ोFreq;      // kHz

  // GFXCLK Fll Spपढ़ो Spectrum
  uपूर्णांक8_t      FllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      FllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     FllGfxclkSpपढ़ोFreq;      // kHz

  // I2C Controller Structure
  I2cControllerConfig_t  I2cControllers[NUM_I2C_CONTROLLERS];

  // Memory section
  uपूर्णांक32_t     MemoryChannelEnabled; // For DRAM use only, Max 32 channels enabled bit mask.

  uपूर्णांक8_t      DramBitWidth; // For DRAM use only.  See Dram Bit width type defines
  uपूर्णांक8_t      PaddingMem[3];

  // Total board घातer
  uपूर्णांक16_t     TotalBoardPower;     //Only needed क्रम TCP Estimated हाल, where TCP = TGP+Total Board Power
  uपूर्णांक16_t     BoardPadding;

  // SECTION: XGMI Training
  uपूर्णांक8_t           XgmiLinkSpeed   [NUM_XGMI_PSTATE_LEVELS];
  uपूर्णांक8_t           XgmiLinkWidth   [NUM_XGMI_PSTATE_LEVELS];

  uपूर्णांक16_t          XgmiFclkFreq    [NUM_XGMI_PSTATE_LEVELS];
  uपूर्णांक16_t          XgmiSocVoltage  [NUM_XGMI_PSTATE_LEVELS];

  // GPIO pins क्रम I2C communications with 2nd controller क्रम Input Telemetry Sequence
  uपूर्णांक8_t      GpioI2cScl;          // Serial Clock
  uपूर्णांक8_t      GpioI2cSda;          // Serial Data
  uपूर्णांक16_t     GpioPadding;

  // Platक्रमm input telemetry voltage coefficient
  uपूर्णांक32_t     BoardVoltageCoeffA;    // decode by /1000
  uपूर्णांक32_t     BoardVoltageCoeffB;    // decode by /1000

  uपूर्णांक32_t     BoardReserved[7];

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

  uपूर्णांक16_t     VcnClkAverageLpfTau;
  uपूर्णांक16_t     padding16;

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण DriverSmuConfig_t;

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
  uपूर्णांक16_t TemperatureHBM        ;
  uपूर्णांक16_t TemperatureVrGfx      ;
  uपूर्णांक16_t TemperatureVrSoc      ;
  uपूर्णांक16_t TemperatureVrMem      ;
  uपूर्णांक32_t ThrottlerStatus       ;

  uपूर्णांक16_t CurrFanSpeed          ;
  uपूर्णांक16_t AverageVclkFrequency  ;
  uपूर्णांक16_t AverageDclkFrequency  ;
  uपूर्णांक16_t VcnActivityPercentage ;
  uपूर्णांक32_t EnergyAccumulator     ;

  uपूर्णांक32_t Padding[2];

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SmuMetrics_t;


प्रकार काष्ठा अणु
  uपूर्णांक16_t avgPsmCount[75];
  uपूर्णांक16_t minPsmCount[75];
  भग्न    avgPsmVoltage[75];
  भग्न    minPsmVoltage[75];

  uपूर्णांक32_t MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण AvfsDebugTable_t;

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

  uपूर्णांक32_t EnabledAvfsModules[3];

  uपूर्णांक32_t MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण AvfsFuseOverride_t;

प्रकार काष्ठा अणु
  uपूर्णांक8_t   Gfx_ActiveHystLimit;
  uपूर्णांक8_t   Gfx_IdleHystLimit;
  uपूर्णांक8_t   Gfx_FPS;
  uपूर्णांक8_t   Gfx_MinActiveFreqType;
  uपूर्णांक8_t   Gfx_BoosterFreqType;
  uपूर्णांक8_t   Gfx_MinFreqStep;                // Minimum delta between current and target frequeny in order क्रम FW to change घड़ी.
  uपूर्णांक8_t   Gfx_UseRlcBusy;
  uपूर्णांक8_t   PaddingGfx[3];
  uपूर्णांक16_t  Gfx_MinActiveFreq;              // MHz
  uपूर्णांक16_t  Gfx_BoosterFreq;                // MHz
  uपूर्णांक16_t  Gfx_PD_Data_समय_स्थिरant;      // Time स्थिरant of PD controller in ms
  uपूर्णांक32_t  Gfx_PD_Data_limit_a;            // Q16
  uपूर्णांक32_t  Gfx_PD_Data_limit_b;            // Q16
  uपूर्णांक32_t  Gfx_PD_Data_limit_c;            // Q16
  uपूर्णांक32_t  Gfx_PD_Data_error_coeff;        // Q16
  uपूर्णांक32_t  Gfx_PD_Data_error_rate_coeff;   // Q16

  uपूर्णांक8_t   Mem_ActiveHystLimit;
  uपूर्णांक8_t   Mem_IdleHystLimit;
  uपूर्णांक8_t   Mem_FPS;
  uपूर्णांक8_t   Mem_MinActiveFreqType;
  uपूर्णांक8_t   Mem_BoosterFreqType;
  uपूर्णांक8_t   Mem_MinFreqStep;                // Minimum delta between current and target frequeny in order क्रम FW to change घड़ी.
  uपूर्णांक8_t   Mem_UseRlcBusy;
  uपूर्णांक8_t   PaddingMem[3];
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

  uपूर्णांक32_t  BusyThreshold;                  // Q16
  uपूर्णांक32_t  BusyHyst;
  uपूर्णांक32_t  IdleHyst;

  uपूर्णांक32_t  MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण DpmActivityMonitorCoeffInt_t;

// These defines are used with the following messages:
// SMC_MSG_TransferTableDram2Smu
// SMC_MSG_TransferTableSmu2Dram
#घोषणा TABLE_PPTABLE                 0
#घोषणा TABLE_AVFS                    1
#घोषणा TABLE_AVFS_PSM_DEBUG          2
#घोषणा TABLE_AVFS_FUSE_OVERRIDE      3
#घोषणा TABLE_PMSTATUSLOG             4
#घोषणा TABLE_SMU_METRICS             5
#घोषणा TABLE_DRIVER_SMU_CONFIG       6
#घोषणा TABLE_OVERDRIVE               7
#घोषणा TABLE_WAFL_XGMI_TOPOLOGY      8
#घोषणा TABLE_I2C_COMMANDS            9
#घोषणा TABLE_ACTIVITY_MONITOR_COEFF  10
#घोषणा TABLE_COUNT                   11

// These defines are used with the SMC_MSG_SetUclkFastSwitch message.
प्रकार क्रमागत अणु
  DF_SWITCH_TYPE_FAST = 0,
  DF_SWITCH_TYPE_SLOW,
  DF_SWITCH_TYPE_COUNT,
पूर्ण DF_SWITCH_TYPE_e;

प्रकार क्रमागत अणु
  DRAM_BIT_WIDTH_DISABLED = 0,
  DRAM_BIT_WIDTH_X_8,
  DRAM_BIT_WIDTH_X_16,
  DRAM_BIT_WIDTH_X_32,
  DRAM_BIT_WIDTH_X_64, // NOT USED.
  DRAM_BIT_WIDTH_X_128,
  DRAM_BIT_WIDTH_COUNT,
पूर्ण DRAM_BIT_WIDTH_TYPE_e;

#घोषणा REMOVE_FMAX_MARGIN_BIT     0x0
#घोषणा REMOVE_DCTOL_MARGIN_BIT    0x1
#घोषणा REMOVE_PLATFORM_MARGIN_BIT 0x2

#पूर्ण_अगर
