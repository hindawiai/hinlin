<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित SMU11_DRIVER_IF_H
#घोषणा SMU11_DRIVER_IF_H

// *** IMPORTANT ***
// SMU TEAM: Always increment the पूर्णांकerface version अगर
// any काष्ठाure is changed in this file
// Be aware of that the version should be updated in
// smu_v11_0.h, नाम is also needed.
// #घोषणा SMU11_DRIVER_IF_VERSION 0x13

#घोषणा PPTABLE_V20_SMU_VERSION 3

#घोषणा NUM_GFXCLK_DPM_LEVELS  16
#घोषणा NUM_VCLK_DPM_LEVELS    8
#घोषणा NUM_DCLK_DPM_LEVELS    8
#घोषणा NUM_ECLK_DPM_LEVELS    8
#घोषणा NUM_MP0CLK_DPM_LEVELS  2
#घोषणा NUM_SOCCLK_DPM_LEVELS  8
#घोषणा NUM_UCLK_DPM_LEVELS    4
#घोषणा NUM_FCLK_DPM_LEVELS    8
#घोषणा NUM_DCEFCLK_DPM_LEVELS 8
#घोषणा NUM_DISPCLK_DPM_LEVELS 8
#घोषणा NUM_PIXCLK_DPM_LEVELS  8
#घोषणा NUM_PHYCLK_DPM_LEVELS  8
#घोषणा NUM_LINK_LEVELS        2
#घोषणा NUM_XGMI_LEVELS        2

#घोषणा MAX_GFXCLK_DPM_LEVEL  (NUM_GFXCLK_DPM_LEVELS  - 1)
#घोषणा MAX_VCLK_DPM_LEVEL    (NUM_VCLK_DPM_LEVELS    - 1)
#घोषणा MAX_DCLK_DPM_LEVEL    (NUM_DCLK_DPM_LEVELS    - 1)
#घोषणा MAX_ECLK_DPM_LEVEL    (NUM_ECLK_DPM_LEVELS    - 1)
#घोषणा MAX_MP0CLK_DPM_LEVEL  (NUM_MP0CLK_DPM_LEVELS  - 1)
#घोषणा MAX_SOCCLK_DPM_LEVEL  (NUM_SOCCLK_DPM_LEVELS  - 1)
#घोषणा MAX_UCLK_DPM_LEVEL    (NUM_UCLK_DPM_LEVELS    - 1)
#घोषणा MAX_FCLK_DPM_LEVEL    (NUM_FCLK_DPM_LEVELS    - 1)
#घोषणा MAX_DCEFCLK_DPM_LEVEL (NUM_DCEFCLK_DPM_LEVELS - 1)
#घोषणा MAX_DISPCLK_DPM_LEVEL (NUM_DISPCLK_DPM_LEVELS - 1)
#घोषणा MAX_PIXCLK_DPM_LEVEL  (NUM_PIXCLK_DPM_LEVELS  - 1)
#घोषणा MAX_PHYCLK_DPM_LEVEL  (NUM_PHYCLK_DPM_LEVELS  - 1)
#घोषणा MAX_LINK_LEVEL        (NUM_LINK_LEVELS        - 1)
#घोषणा MAX_XGMI_LEVEL        (NUM_XGMI_LEVELS        - 1)

#घोषणा PPSMC_GeminiModeNone   0
#घोषणा PPSMC_GeminiModeMaster 1
#घोषणा PPSMC_GeminiModeSlave  2


#घोषणा FEATURE_DPM_PREFETCHER_BIT      0
#घोषणा FEATURE_DPM_GFXCLK_BIT          1
#घोषणा FEATURE_DPM_UCLK_BIT            2
#घोषणा FEATURE_DPM_SOCCLK_BIT          3
#घोषणा FEATURE_DPM_UVD_BIT             4
#घोषणा FEATURE_DPM_VCE_BIT             5
#घोषणा FEATURE_ULV_BIT                 6
#घोषणा FEATURE_DPM_MP0CLK_BIT          7
#घोषणा FEATURE_DPM_LINK_BIT            8
#घोषणा FEATURE_DPM_DCEFCLK_BIT         9
#घोषणा FEATURE_DS_GFXCLK_BIT           10
#घोषणा FEATURE_DS_SOCCLK_BIT           11
#घोषणा FEATURE_DS_LCLK_BIT             12
#घोषणा FEATURE_PPT_BIT                 13
#घोषणा FEATURE_TDC_BIT                 14
#घोषणा FEATURE_THERMAL_BIT             15
#घोषणा FEATURE_GFX_PER_CU_CG_BIT       16
#घोषणा FEATURE_RM_BIT                  17
#घोषणा FEATURE_DS_DCEFCLK_BIT          18
#घोषणा FEATURE_ACDC_BIT                19
#घोषणा FEATURE_VR0HOT_BIT              20
#घोषणा FEATURE_VR1HOT_BIT              21
#घोषणा FEATURE_FW_CTF_BIT              22
#घोषणा FEATURE_LED_DISPLAY_BIT         23
#घोषणा FEATURE_FAN_CONTROL_BIT         24
#घोषणा FEATURE_GFX_EDC_BIT             25
#घोषणा FEATURE_GFXOFF_BIT              26
#घोषणा FEATURE_CG_BIT                  27
#घोषणा FEATURE_DPM_FCLK_BIT            28
#घोषणा FEATURE_DS_FCLK_BIT             29
#घोषणा FEATURE_DS_MP1CLK_BIT           30
#घोषणा FEATURE_DS_MP0CLK_BIT           31
#घोषणा FEATURE_XGMI_BIT                32
#घोषणा FEATURE_ECC_BIT                 33
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

#घोषणा FEATURE_DPM_PREFETCHER_MASK     (1 << FEATURE_DPM_PREFETCHER_BIT     )
#घोषणा FEATURE_DPM_GFXCLK_MASK         (1 << FEATURE_DPM_GFXCLK_BIT         )
#घोषणा FEATURE_DPM_UCLK_MASK           (1 << FEATURE_DPM_UCLK_BIT           )
#घोषणा FEATURE_DPM_SOCCLK_MASK         (1 << FEATURE_DPM_SOCCLK_BIT         )
#घोषणा FEATURE_DPM_UVD_MASK            (1 << FEATURE_DPM_UVD_BIT            )
#घोषणा FEATURE_DPM_VCE_MASK            (1 << FEATURE_DPM_VCE_BIT            )
#घोषणा FEATURE_ULV_MASK                (1 << FEATURE_ULV_BIT                )
#घोषणा FEATURE_DPM_MP0CLK_MASK         (1 << FEATURE_DPM_MP0CLK_BIT         )
#घोषणा FEATURE_DPM_LINK_MASK           (1 << FEATURE_DPM_LINK_BIT           )
#घोषणा FEATURE_DPM_DCEFCLK_MASK        (1 << FEATURE_DPM_DCEFCLK_BIT        )
#घोषणा FEATURE_DS_GFXCLK_MASK          (1 << FEATURE_DS_GFXCLK_BIT          )
#घोषणा FEATURE_DS_SOCCLK_MASK          (1 << FEATURE_DS_SOCCLK_BIT          )
#घोषणा FEATURE_DS_LCLK_MASK            (1 << FEATURE_DS_LCLK_BIT            )
#घोषणा FEATURE_PPT_MASK                (1 << FEATURE_PPT_BIT                )
#घोषणा FEATURE_TDC_MASK                (1 << FEATURE_TDC_BIT                )
#घोषणा FEATURE_THERMAL_MASK            (1 << FEATURE_THERMAL_BIT            )
#घोषणा FEATURE_GFX_PER_CU_CG_MASK      (1 << FEATURE_GFX_PER_CU_CG_BIT      )
#घोषणा FEATURE_RM_MASK                 (1 << FEATURE_RM_BIT                 )
#घोषणा FEATURE_DS_DCEFCLK_MASK         (1 << FEATURE_DS_DCEFCLK_BIT         )
#घोषणा FEATURE_ACDC_MASK               (1 << FEATURE_ACDC_BIT               )
#घोषणा FEATURE_VR0HOT_MASK             (1 << FEATURE_VR0HOT_BIT             )
#घोषणा FEATURE_VR1HOT_MASK             (1 << FEATURE_VR1HOT_BIT             )
#घोषणा FEATURE_FW_CTF_MASK             (1 << FEATURE_FW_CTF_BIT             )
#घोषणा FEATURE_LED_DISPLAY_MASK        (1 << FEATURE_LED_DISPLAY_BIT        )
#घोषणा FEATURE_FAN_CONTROL_MASK        (1 << FEATURE_FAN_CONTROL_BIT        )
#घोषणा FEATURE_GFX_EDC_MASK            (1 << FEATURE_GFX_EDC_BIT            )
#घोषणा FEATURE_GFXOFF_MASK             (1 << FEATURE_GFXOFF_BIT             )
#घोषणा FEATURE_CG_MASK                 (1 << FEATURE_CG_BIT                 )
#घोषणा FEATURE_DPM_FCLK_MASK           (1 << FEATURE_DPM_FCLK_BIT           )
#घोषणा FEATURE_DS_FCLK_MASK            (1 << FEATURE_DS_FCLK_BIT            )
#घोषणा FEATURE_DS_MP1CLK_MASK          (1 << FEATURE_DS_MP1CLK_BIT          )
#घोषणा FEATURE_DS_MP0CLK_MASK          (1 << FEATURE_DS_MP0CLK_BIT          )
#घोषणा FEATURE_XGMI_MASK               (1ULL << FEATURE_XGMI_BIT               )
#घोषणा FEATURE_ECC_MASK                (1ULL << FEATURE_ECC_BIT                )

#घोषणा DPM_OVERRIDE_DISABLE_SOCCLK_PID             0x00000001
#घोषणा DPM_OVERRIDE_DISABLE_UCLK_PID               0x00000002
#घोषणा DPM_OVERRIDE_ENABLE_VOLT_LINK_UVD_SOCCLK    0x00000004
#घोषणा DPM_OVERRIDE_ENABLE_VOLT_LINK_UVD_UCLK      0x00000008
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_VCLK_SOCCLK   0x00000010
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_VCLK_UCLK     0x00000020
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_DCLK_SOCCLK   0x00000040
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_DCLK_UCLK     0x00000080
#घोषणा DPM_OVERRIDE_ENABLE_VOLT_LINK_VCE_SOCCLK    0x00000100
#घोषणा DPM_OVERRIDE_ENABLE_VOLT_LINK_VCE_UCLK      0x00000200
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_ECLK_SOCCLK   0x00000400
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_ECLK_UCLK     0x00000800
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_SOCCLK 0x00001000
#घोषणा DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_UCLK   0x00002000
#घोषणा DPM_OVERRIDE_ENABLE_GFXOFF_GFXCLK_SWITCH    0x00004000
#घोषणा DPM_OVERRIDE_ENABLE_GFXOFF_SOCCLK_SWITCH    0x00008000
#घोषणा DPM_OVERRIDE_ENABLE_GFXOFF_UCLK_SWITCH      0x00010000
#घोषणा DPM_OVERRIDE_ENABLE_GFXOFF_FCLK_SWITCH      0x00020000

#घोषणा I2C_CONTROLLER_ENABLED     1
#घोषणा I2C_CONTROLLER_DISABLED    0

#घोषणा VR_MAPPING_VR_SELECT_MASK  0x01
#घोषणा VR_MAPPING_VR_SELECT_SHIFT 0x00

#घोषणा VR_MAPPING_PLANE_SELECT_MASK  0x02
#घोषणा VR_MAPPING_PLANE_SELECT_SHIFT 0x01


#घोषणा PSI_SEL_VR0_PLANE0_PSI0  0x01
#घोषणा PSI_SEL_VR0_PLANE0_PSI1  0x02
#घोषणा PSI_SEL_VR0_PLANE1_PSI0  0x04
#घोषणा PSI_SEL_VR0_PLANE1_PSI1  0x08
#घोषणा PSI_SEL_VR1_PLANE0_PSI0  0x10
#घोषणा PSI_SEL_VR1_PLANE0_PSI1  0x20
#घोषणा PSI_SEL_VR1_PLANE1_PSI0  0x40
#घोषणा PSI_SEL_VR1_PLANE1_PSI1  0x80


#घोषणा THROTTLER_STATUS_PADDING_BIT      0
#घोषणा THROTTLER_STATUS_TEMP_EDGE_BIT    1
#घोषणा THROTTLER_STATUS_TEMP_HOTSPOT_BIT 2
#घोषणा THROTTLER_STATUS_TEMP_HBM_BIT     3
#घोषणा THROTTLER_STATUS_TEMP_VR_GFX_BIT  4
#घोषणा THROTTLER_STATUS_TEMP_VR_SOC_BIT  5
#घोषणा THROTTLER_STATUS_TEMP_VR_MEM0_BIT 6
#घोषणा THROTTLER_STATUS_TEMP_VR_MEM1_BIT 7
#घोषणा THROTTLER_STATUS_TEMP_LIQUID_BIT  8
#घोषणा THROTTLER_STATUS_TEMP_PLX_BIT     9
#घोषणा THROTTLER_STATUS_TEMP_SKIN_BIT    10
#घोषणा THROTTLER_STATUS_TDC_GFX_BIT      11
#घोषणा THROTTLER_STATUS_TDC_SOC_BIT      12
#घोषणा THROTTLER_STATUS_PPT_BIT          13
#घोषणा THROTTLER_STATUS_FIT_BIT          14
#घोषणा THROTTLER_STATUS_PPM_BIT          15


#घोषणा TABLE_TRANSFER_OK         0x0
#घोषणा TABLE_TRANSFER_FAILED     0xFF


#घोषणा WORKLOAD_DEFAULT_BIT              0
#घोषणा WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 1
#घोषणा WORKLOAD_PPLIB_POWER_SAVING_BIT   2
#घोषणा WORKLOAD_PPLIB_VIDEO_BIT          3
#घोषणा WORKLOAD_PPLIB_VR_BIT             4
#घोषणा WORKLOAD_PPLIB_COMPUTE_BIT        5
#घोषणा WORKLOAD_PPLIB_CUSTOM_BIT         6
#घोषणा WORKLOAD_PPLIB_COUNT              7


#घोषणा XGMI_STATE_D0 1
#घोषणा XGMI_STATE_D3 0

प्रकार क्रमागत अणु
  I2C_CONTROLLER_PORT_0 = 0,
  I2C_CONTROLLER_PORT_1 = 1,
पूर्ण I2cControllerPort_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_NAME_VR_GFX = 0,
  I2C_CONTROLLER_NAME_VR_SOC,
  I2C_CONTROLLER_NAME_VR_VDDCI,
  I2C_CONTROLLER_NAME_VR_HBM,
  I2C_CONTROLLER_NAME_LIQUID_0,
  I2C_CONTROLLER_NAME_LIQUID_1,
  I2C_CONTROLLER_NAME_PLX,
  I2C_CONTROLLER_NAME_COUNT,
पूर्ण I2cControllerName_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_THROTTLER_TYPE_NONE = 0,
  I2C_CONTROLLER_THROTTLER_VR_GFX,
  I2C_CONTROLLER_THROTTLER_VR_SOC,
  I2C_CONTROLLER_THROTTLER_VR_VDDCI,
  I2C_CONTROLLER_THROTTLER_VR_HBM,
  I2C_CONTROLLER_THROTTLER_LIQUID_0,
  I2C_CONTROLLER_THROTTLER_LIQUID_1,
  I2C_CONTROLLER_THROTTLER_PLX,
पूर्ण I2cControllerThrottler_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_PROTOCOL_VR_XPDE132G5,
  I2C_CONTROLLER_PROTOCOL_VR_IR35217,
  I2C_CONTROLLER_PROTOCOL_TMP_TMP102A,
  I2C_CONTROLLER_PROTOCOL_SPARE_0,
  I2C_CONTROLLER_PROTOCOL_SPARE_1,
  I2C_CONTROLLER_PROTOCOL_SPARE_2,
पूर्ण I2cControllerProtocol_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_SPEED_SLOW = 0,
  I2C_CONTROLLER_SPEED_FAST = 1,
पूर्ण I2cControllerSpeed_e;

प्रकार काष्ठा अणु
  uपूर्णांक32_t Enabled;
  uपूर्णांक32_t SlaveAddress;
  uपूर्णांक32_t ControllerPort;
  uपूर्णांक32_t ControllerName;

  uपूर्णांक32_t ThermalThrottler;
  uपूर्णांक32_t I2cProtocol;
  uपूर्णांक32_t I2cSpeed;
पूर्ण I2cControllerConfig_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t a;
  uपूर्णांक32_t b;
  uपूर्णांक32_t c;
पूर्ण QuadraticInt_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t m;
  uपूर्णांक32_t b;
पूर्ण LinearInt_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t a;
  uपूर्णांक32_t b;
  uपूर्णांक32_t c;
पूर्ण DroopInt_t;

प्रकार क्रमागत अणु
  PPCLK_GFXCLK,
  PPCLK_VCLK,
  PPCLK_DCLK,
  PPCLK_ECLK,
  PPCLK_SOCCLK,
  PPCLK_UCLK,
  PPCLK_DCEFCLK,
  PPCLK_DISPCLK,
  PPCLK_PIXCLK,
  PPCLK_PHYCLK,
  PPCLK_FCLK,
  PPCLK_COUNT,
पूर्ण PPCLK_e;

प्रकार क्रमागत अणु
  POWER_SOURCE_AC,
  POWER_SOURCE_DC,
  POWER_SOURCE_COUNT,
पूर्ण POWER_SOURCE_e;

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


प्रकार काष्ठा अणु
  uपूर्णांक8_t        VoltageMode;
  uपूर्णांक8_t        SnapToDiscrete;
  uपूर्णांक8_t        NumDiscreteLevels;
  uपूर्णांक8_t        padding;
  LinearInt_t    ConversionToAvfsClk;
  QuadraticInt_t SsCurve;
पूर्ण DpmDescriptor_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t Version;


  uपूर्णांक32_t FeaturesToRun[2];


  uपूर्णांक16_t SocketPowerLimitAc0;
  uपूर्णांक16_t SocketPowerLimitAc0Tau;
  uपूर्णांक16_t SocketPowerLimitAc1;
  uपूर्णांक16_t SocketPowerLimitAc1Tau;
  uपूर्णांक16_t SocketPowerLimitAc2;
  uपूर्णांक16_t SocketPowerLimitAc2Tau;
  uपूर्णांक16_t SocketPowerLimitAc3;
  uपूर्णांक16_t SocketPowerLimitAc3Tau;
  uपूर्णांक16_t SocketPowerLimitDc;
  uपूर्णांक16_t SocketPowerLimitDcTau;
  uपूर्णांक16_t TdcLimitSoc;
  uपूर्णांक16_t TdcLimitSocTau;
  uपूर्णांक16_t TdcLimitGfx;
  uपूर्णांक16_t TdcLimitGfxTau;

  uपूर्णांक16_t TedgeLimit;
  uपूर्णांक16_t ThotspotLimit;
  uपूर्णांक16_t ThbmLimit;
  uपूर्णांक16_t Tvr_gfxLimit;
  uपूर्णांक16_t Tvr_memLimit;
  uपूर्णांक16_t Tliquid1Limit;
  uपूर्णांक16_t Tliquid2Limit;
  uपूर्णांक16_t TplxLimit;
  uपूर्णांक32_t FitLimit;

  uपूर्णांक16_t PpmPowerLimit;
  uपूर्णांक16_t PpmTemperatureThreshold;

  uपूर्णांक8_t  MemoryOnPackage;
  uपूर्णांक8_t  padding8_limits;
  uपूर्णांक16_t Tvr_SocLimit;

  uपूर्णांक16_t  UlvVoltageOffsetSoc;
  uपूर्णांक16_t  UlvVoltageOffsetGfx;

  uपूर्णांक8_t  UlvSmnclkDid;
  uपूर्णांक8_t  UlvMp1clkDid;
  uपूर्णांक8_t  UlvGfxclkBypass;
  uपूर्णांक8_t  Padding234;


  uपूर्णांक16_t     MinVoltageGfx;
  uपूर्णांक16_t     MinVoltageSoc;
  uपूर्णांक16_t     MaxVoltageGfx;
  uपूर्णांक16_t     MaxVoltageSoc;

  uपूर्णांक16_t     LoadLineResistanceGfx;
  uपूर्णांक16_t     LoadLineResistanceSoc;

  DpmDescriptor_t DpmDescriptor[PPCLK_COUNT];

  uपूर्णांक16_t       FreqTableGfx      [NUM_GFXCLK_DPM_LEVELS  ];
  uपूर्णांक16_t       FreqTableVclk     [NUM_VCLK_DPM_LEVELS    ];
  uपूर्णांक16_t       FreqTableDclk     [NUM_DCLK_DPM_LEVELS    ];
  uपूर्णांक16_t       FreqTableEclk     [NUM_ECLK_DPM_LEVELS    ];
  uपूर्णांक16_t       FreqTableSocclk   [NUM_SOCCLK_DPM_LEVELS  ];
  uपूर्णांक16_t       FreqTableUclk     [NUM_UCLK_DPM_LEVELS    ];
  uपूर्णांक16_t       FreqTableFclk     [NUM_FCLK_DPM_LEVELS    ];
  uपूर्णांक16_t       FreqTableDcefclk  [NUM_DCEFCLK_DPM_LEVELS ];
  uपूर्णांक16_t       FreqTableDispclk  [NUM_DISPCLK_DPM_LEVELS ];
  uपूर्णांक16_t       FreqTablePixclk   [NUM_PIXCLK_DPM_LEVELS  ];
  uपूर्णांक16_t       FreqTablePhyclk   [NUM_PHYCLK_DPM_LEVELS  ];

  uपूर्णांक16_t       DcModeMaxFreq     [PPCLK_COUNT            ];
  uपूर्णांक16_t       Padding8_Clks;

  uपूर्णांक16_t       Mp0clkFreq        [NUM_MP0CLK_DPM_LEVELS];
  uपूर्णांक16_t       Mp0DpmVoltage     [NUM_MP0CLK_DPM_LEVELS];


  uपूर्णांक16_t        GfxclkFidle;
  uपूर्णांक16_t        GfxclkSlewRate;
  uपूर्णांक16_t        CksEnableFreq;
  uपूर्णांक16_t        Padding789;
  QuadraticInt_t  CksVoltageOffset;
  uपूर्णांक8_t         Padding567[4];
  uपूर्णांक16_t        GfxclkDsMaxFreq;
  uपूर्णांक8_t         GfxclkSource;
  uपूर्णांक8_t         Padding456;

  uपूर्णांक8_t      LowestUclkReservedForUlv;
  uपूर्णांक8_t      Padding8_Uclk[3];


  uपूर्णांक8_t      PcieGenSpeed[NUM_LINK_LEVELS];
  uपूर्णांक8_t      PcieLaneCount[NUM_LINK_LEVELS];
  uपूर्णांक16_t     LclkFreq[NUM_LINK_LEVELS];


  uपूर्णांक16_t     EnableTdpm;
  uपूर्णांक16_t     TdpmHighHystTemperature;
  uपूर्णांक16_t     TdpmLowHystTemperature;
  uपूर्णांक16_t     GfxclkFreqHighTempLimit;


  uपूर्णांक16_t     FanStopTemp;
  uपूर्णांक16_t     FanStartTemp;

  uपूर्णांक16_t     FanGainEdge;
  uपूर्णांक16_t     FanGainHotspot;
  uपूर्णांक16_t     FanGainLiquid;
  uपूर्णांक16_t     FanGainVrGfx;
  uपूर्णांक16_t     FanGainVrSoc;
  uपूर्णांक16_t     FanGainPlx;
  uपूर्णांक16_t     FanGainHbm;
  uपूर्णांक16_t     FanPwmMin;
  uपूर्णांक16_t     FanAcousticLimitRpm;
  uपूर्णांक16_t     FanThrottlingRpm;
  uपूर्णांक16_t     FanMaximumRpm;
  uपूर्णांक16_t     FanTargetTemperature;
  uपूर्णांक16_t     FanTargetGfxclk;
  uपूर्णांक8_t      FanZeroRpmEnable;
  uपूर्णांक8_t      FanTachEdgePerRev;



  पूर्णांक16_t      FuzzyFan_ErrorSetDelta;
  पूर्णांक16_t      FuzzyFan_ErrorRateSetDelta;
  पूर्णांक16_t      FuzzyFan_PwmSetDelta;
  uपूर्णांक16_t     FuzzyFan_Reserved;


  uपूर्णांक8_t           OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t           Padding8_Avfs[2];

  QuadraticInt_t    qAvfsGb[AVFS_VOLTAGE_COUNT];
  DroopInt_t        dBtcGbGfxCksOn;
  DroopInt_t        dBtcGbGfxCksOff;
  DroopInt_t        dBtcGbGfxAfll;
  DroopInt_t        dBtcGbSoc;
  LinearInt_t       qAgingGb[AVFS_VOLTAGE_COUNT];

  QuadraticInt_t    qStaticVoltageOffset[AVFS_VOLTAGE_COUNT];

  uपूर्णांक16_t          DcTol[AVFS_VOLTAGE_COUNT];

  uपूर्णांक8_t           DcBtcEnabled[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t           Padding8_GfxBtc[2];

  पूर्णांक16_t           DcBtcMin[AVFS_VOLTAGE_COUNT];
  uपूर्णांक16_t          DcBtcMax[AVFS_VOLTAGE_COUNT];


  uपूर्णांक8_t           XgmiLinkSpeed   [NUM_XGMI_LEVELS];
  uपूर्णांक8_t           XgmiLinkWidth   [NUM_XGMI_LEVELS];
  uपूर्णांक16_t          XgmiFclkFreq    [NUM_XGMI_LEVELS];
  uपूर्णांक16_t          XgmiUclkFreq    [NUM_XGMI_LEVELS];
  uपूर्णांक16_t          XgmiSocclkFreq  [NUM_XGMI_LEVELS];
  uपूर्णांक16_t          XgmiSocVoltage  [NUM_XGMI_LEVELS];

  uपूर्णांक32_t          DebugOverrides;
  QuadraticInt_t    ReservedEquation0;
  QuadraticInt_t    ReservedEquation1;
  QuadraticInt_t    ReservedEquation2;
  QuadraticInt_t    ReservedEquation3;

  uपूर्णांक16_t     MinVoltageUlvGfx;
  uपूर्णांक16_t     MinVoltageUlvSoc;

  uपूर्णांक16_t     MGpuFanBoostLimitRpm;
  uपूर्णांक16_t     padding16_Fan;

  uपूर्णांक16_t     FanGainVrMem0;
  uपूर्णांक16_t     FanGainVrMem1;

  uपूर्णांक16_t     DcBtcGb[AVFS_VOLTAGE_COUNT];

  uपूर्णांक32_t     Reserved[11];

  uपूर्णांक32_t     Padding32[3];

  uपूर्णांक16_t     MaxVoltageStepGfx;
  uपूर्णांक16_t     MaxVoltageStepSoc;

  uपूर्णांक8_t      VddGfxVrMapping;
  uपूर्णांक8_t      VddSocVrMapping;
  uपूर्णांक8_t      VddMem0VrMapping;
  uपूर्णांक8_t      VddMem1VrMapping;

  uपूर्णांक8_t      GfxUlvPhaseSheddingMask;
  uपूर्णांक8_t      SocUlvPhaseSheddingMask;
  uपूर्णांक8_t      ExternalSensorPresent;
  uपूर्णांक8_t      Padding8_V;


  uपूर्णांक16_t     GfxMaxCurrent;
  पूर्णांक8_t       GfxOffset;
  uपूर्णांक8_t      Padding_TelemetryGfx;

  uपूर्णांक16_t     SocMaxCurrent;
  पूर्णांक8_t       SocOffset;
  uपूर्णांक8_t      Padding_TelemetrySoc;

  uपूर्णांक16_t     Mem0MaxCurrent;
  पूर्णांक8_t       Mem0Offset;
  uपूर्णांक8_t      Padding_TelemetryMem0;

  uपूर्णांक16_t     Mem1MaxCurrent;
  पूर्णांक8_t       Mem1Offset;
  uपूर्णांक8_t      Padding_TelemetryMem1;


  uपूर्णांक8_t      AcDcGpio;
  uपूर्णांक8_t      AcDcPolarity;
  uपूर्णांक8_t      VR0HotGpio;
  uपूर्णांक8_t      VR0HotPolarity;

  uपूर्णांक8_t      VR1HotGpio;
  uपूर्णांक8_t      VR1HotPolarity;
  uपूर्णांक8_t      Padding1;
  uपूर्णांक8_t      Padding2;



  uपूर्णांक8_t      LedPin0;
  uपूर्णांक8_t      LedPin1;
  uपूर्णांक8_t      LedPin2;
  uपूर्णांक8_t      padding8_4;


  uपूर्णांक8_t      PllGfxclkSpपढ़ोEnabled;
  uपूर्णांक8_t      PllGfxclkSpपढ़ोPercent;
  uपूर्णांक16_t     PllGfxclkSpपढ़ोFreq;

  uपूर्णांक8_t      UclkSpपढ़ोEnabled;
  uपूर्णांक8_t      UclkSpपढ़ोPercent;
  uपूर्णांक16_t     UclkSpपढ़ोFreq;

  uपूर्णांक8_t      FclkSpपढ़ोEnabled;
  uपूर्णांक8_t      FclkSpपढ़ोPercent;
  uपूर्णांक16_t     FclkSpपढ़ोFreq;

  uपूर्णांक8_t      FllGfxclkSpपढ़ोEnabled;
  uपूर्णांक8_t      FllGfxclkSpपढ़ोPercent;
  uपूर्णांक16_t     FllGfxclkSpपढ़ोFreq;

  I2cControllerConfig_t I2cControllers[I2C_CONTROLLER_NAME_COUNT];

  uपूर्णांक32_t     BoardReserved[10];


  uपूर्णांक32_t     MmHubPadding[8];

पूर्ण PPTable_t;

प्रकार काष्ठा अणु

  uपूर्णांक16_t     GfxclkAverageLpfTau;
  uपूर्णांक16_t     SocclkAverageLpfTau;
  uपूर्णांक16_t     UclkAverageLpfTau;
  uपूर्णांक16_t     GfxActivityLpfTau;
  uपूर्णांक16_t     UclkActivityLpfTau;
  uपूर्णांक16_t     SocketPowerLpfTau;


  uपूर्णांक32_t     MmHubPadding[8];
पूर्ण DriverSmuConfig_t;

प्रकार काष्ठा अणु

  uपूर्णांक16_t      GfxclkFmin;
  uपूर्णांक16_t      GfxclkFmax;
  uपूर्णांक16_t      GfxclkFreq1;
  uपूर्णांक16_t      GfxclkVolt1;
  uपूर्णांक16_t      GfxclkFreq2;
  uपूर्णांक16_t      GfxclkVolt2;
  uपूर्णांक16_t      GfxclkFreq3;
  uपूर्णांक16_t      GfxclkVolt3;
  uपूर्णांक16_t      UclkFmax;
  पूर्णांक16_t       OverDrivePct;
  uपूर्णांक16_t      FanMaximumRpm;
  uपूर्णांक16_t      FanMinimumPwm;
  uपूर्णांक16_t      FanTargetTemperature;
  uपूर्णांक16_t      MaxOpTemp;
  uपूर्णांक16_t      FanZeroRpmEnable;
  uपूर्णांक16_t      Padding;

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
  uपूर्णांक16_t CurrSocketPower       ;
  uपूर्णांक16_t TemperatureEdge       ;
  uपूर्णांक16_t TemperatureHotspot    ;
  uपूर्णांक16_t TemperatureHBM        ;
  uपूर्णांक16_t TemperatureVrGfx      ;
  uपूर्णांक16_t TemperatureVrSoc      ;
  uपूर्णांक16_t TemperatureVrMem0     ;
  uपूर्णांक16_t TemperatureVrMem1     ;
  uपूर्णांक16_t TemperatureLiquid     ;
  uपूर्णांक16_t TemperaturePlx        ;
  uपूर्णांक32_t ThrottlerStatus       ;

  uपूर्णांक8_t  LinkDpmLevel;
  uपूर्णांक16_t AverageSocketPower;
  uपूर्णांक8_t  Padding;


  uपूर्णांक32_t     MmHubPadding[7];
पूर्ण SmuMetrics_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t MinClock;
  uपूर्णांक16_t MaxClock;
  uपूर्णांक16_t MinUclk;
  uपूर्णांक16_t MaxUclk;

  uपूर्णांक8_t  WmSetting;
  uपूर्णांक8_t  Padding[3];
पूर्ण WatermarkRowGeneric_t;

#घोषणा NUM_WM_RANGES 4

प्रकार क्रमागत अणु
  WM_SOCCLK = 0,
  WM_DCEFCLK,
  WM_COUNT_PP,
पूर्ण WM_CLOCK_e;

प्रकार काष्ठा अणु

  WatermarkRowGeneric_t WatermarkRow[WM_COUNT_PP][NUM_WM_RANGES];

  uपूर्णांक32_t     MmHubPadding[7];
पूर्ण Watermarks_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t avgPsmCount[45];
  uपूर्णांक16_t minPsmCount[45];
  भग्न    avgPsmVoltage[45];
  भग्न    minPsmVoltage[45];

  uपूर्णांक16_t avgScsPsmCount;
  uपूर्णांक16_t minScsPsmCount;
  भग्न    avgScsPsmVoltage;
  भग्न    minScsPsmVoltage;


  uपूर्णांक32_t MmHubPadding[6];
पूर्ण AvfsDebugTable_t;

प्रकार काष्ठा अणु
  uपूर्णांक8_t  AvfsVersion;
  uपूर्णांक8_t  AvfsEn[AVFS_VOLTAGE_COUNT];

  uपूर्णांक8_t  OverrideVFT[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];

  uपूर्णांक8_t  OverrideTemperatures[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideVInversion[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideP2V[AVFS_VOLTAGE_COUNT];
  uपूर्णांक8_t  OverrideP2VCharzFreq[AVFS_VOLTAGE_COUNT];

  पूर्णांक32_t VFT0_m1[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t VFT0_m2[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t VFT0_b[AVFS_VOLTAGE_COUNT];

  पूर्णांक32_t VFT1_m1[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t VFT1_m2[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t VFT1_b[AVFS_VOLTAGE_COUNT];

  पूर्णांक32_t VFT2_m1[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t VFT2_m2[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t VFT2_b[AVFS_VOLTAGE_COUNT];

  पूर्णांक32_t AvfsGb0_m1[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t AvfsGb0_m2[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t AvfsGb0_b[AVFS_VOLTAGE_COUNT];

  पूर्णांक32_t AcBtcGb_m1[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t AcBtcGb_m2[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t AcBtcGb_b[AVFS_VOLTAGE_COUNT];

  uपूर्णांक32_t AvfsTempCold[AVFS_VOLTAGE_COUNT];
  uपूर्णांक32_t AvfsTempMid[AVFS_VOLTAGE_COUNT];
  uपूर्णांक32_t AvfsTempHot[AVFS_VOLTAGE_COUNT];

  uपूर्णांक32_t VInversion[AVFS_VOLTAGE_COUNT];


  पूर्णांक32_t P2V_m1[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t P2V_m2[AVFS_VOLTAGE_COUNT];
  पूर्णांक32_t P2V_b[AVFS_VOLTAGE_COUNT];

  uपूर्णांक32_t P2VCharzFreq[AVFS_VOLTAGE_COUNT];

  uपूर्णांक32_t EnabledAvfsModules;

  uपूर्णांक32_t MmHubPadding[7];
पूर्ण AvfsFuseOverride_t;

प्रकार काष्ठा अणु

  uपूर्णांक8_t   Gfx_ActiveHystLimit;
  uपूर्णांक8_t   Gfx_IdleHystLimit;
  uपूर्णांक8_t   Gfx_FPS;
  uपूर्णांक8_t   Gfx_MinActiveFreqType;
  uपूर्णांक8_t   Gfx_BoosterFreqType; 
  uपूर्णांक8_t   Gfx_UseRlcBusy; 
  uपूर्णांक16_t  Gfx_MinActiveFreq;
  uपूर्णांक16_t  Gfx_BoosterFreq;
  uपूर्णांक16_t  Gfx_PD_Data_समय_स्थिरant;
  uपूर्णांक32_t  Gfx_PD_Data_limit_a;
  uपूर्णांक32_t  Gfx_PD_Data_limit_b;
  uपूर्णांक32_t  Gfx_PD_Data_limit_c;
  uपूर्णांक32_t  Gfx_PD_Data_error_coeff;
  uपूर्णांक32_t  Gfx_PD_Data_error_rate_coeff;

  uपूर्णांक8_t   Soc_ActiveHystLimit;
  uपूर्णांक8_t   Soc_IdleHystLimit;
  uपूर्णांक8_t   Soc_FPS;
  uपूर्णांक8_t   Soc_MinActiveFreqType;
  uपूर्णांक8_t   Soc_BoosterFreqType; 
  uपूर्णांक8_t   Soc_UseRlcBusy;
  uपूर्णांक16_t  Soc_MinActiveFreq;
  uपूर्णांक16_t  Soc_BoosterFreq;
  uपूर्णांक16_t  Soc_PD_Data_समय_स्थिरant;
  uपूर्णांक32_t  Soc_PD_Data_limit_a;
  uपूर्णांक32_t  Soc_PD_Data_limit_b;
  uपूर्णांक32_t  Soc_PD_Data_limit_c;
  uपूर्णांक32_t  Soc_PD_Data_error_coeff;
  uपूर्णांक32_t  Soc_PD_Data_error_rate_coeff;

  uपूर्णांक8_t   Mem_ActiveHystLimit;
  uपूर्णांक8_t   Mem_IdleHystLimit;
  uपूर्णांक8_t   Mem_FPS;
  uपूर्णांक8_t   Mem_MinActiveFreqType;
  uपूर्णांक8_t   Mem_BoosterFreqType;
  uपूर्णांक8_t   Mem_UseRlcBusy; 
  uपूर्णांक16_t  Mem_MinActiveFreq;
  uपूर्णांक16_t  Mem_BoosterFreq;
  uपूर्णांक16_t  Mem_PD_Data_समय_स्थिरant;
  uपूर्णांक32_t  Mem_PD_Data_limit_a;
  uपूर्णांक32_t  Mem_PD_Data_limit_b;
  uपूर्णांक32_t  Mem_PD_Data_limit_c;
  uपूर्णांक32_t  Mem_PD_Data_error_coeff;
  uपूर्णांक32_t  Mem_PD_Data_error_rate_coeff;

  uपूर्णांक8_t   Fclk_ActiveHystLimit;
  uपूर्णांक8_t   Fclk_IdleHystLimit;
  uपूर्णांक8_t   Fclk_FPS;
  uपूर्णांक8_t   Fclk_MinActiveFreqType;
  uपूर्णांक8_t   Fclk_BoosterFreqType;
  uपूर्णांक8_t   Fclk_UseRlcBusy;
  uपूर्णांक16_t  Fclk_MinActiveFreq;
  uपूर्णांक16_t  Fclk_BoosterFreq;
  uपूर्णांक16_t  Fclk_PD_Data_समय_स्थिरant;
  uपूर्णांक32_t  Fclk_PD_Data_limit_a;
  uपूर्णांक32_t  Fclk_PD_Data_limit_b;
  uपूर्णांक32_t  Fclk_PD_Data_limit_c;
  uपूर्णांक32_t  Fclk_PD_Data_error_coeff;
  uपूर्णांक32_t  Fclk_PD_Data_error_rate_coeff;

पूर्ण DpmActivityMonitorCoeffInt_t;

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
#घोषणा TABLE_COUNT                  10


#घोषणा UCLK_SWITCH_SLOW 0
#घोषणा UCLK_SWITCH_FAST 1


#घोषणा SQ_Enable_MASK 0x1
#घोषणा SQ_IR_MASK 0x2
#घोषणा SQ_PCC_MASK 0x4
#घोषणा SQ_EDC_MASK 0x8

#घोषणा TCP_Enable_MASK 0x100
#घोषणा TCP_IR_MASK 0x200
#घोषणा TCP_PCC_MASK 0x400
#घोषणा TCP_EDC_MASK 0x800

#घोषणा TD_Enable_MASK 0x10000
#घोषणा TD_IR_MASK 0x20000
#घोषणा TD_PCC_MASK 0x40000
#घोषणा TD_EDC_MASK 0x80000

#घोषणा DB_Enable_MASK 0x1000000
#घोषणा DB_IR_MASK 0x2000000
#घोषणा DB_PCC_MASK 0x4000000
#घोषणा DB_EDC_MASK 0x8000000

#घोषणा SQ_Enable_SHIFT 0
#घोषणा SQ_IR_SHIFT 1
#घोषणा SQ_PCC_SHIFT 2
#घोषणा SQ_EDC_SHIFT 3

#घोषणा TCP_Enable_SHIFT 8
#घोषणा TCP_IR_SHIFT 9
#घोषणा TCP_PCC_SHIFT 10
#घोषणा TCP_EDC_SHIFT 11

#घोषणा TD_Enable_SHIFT 16
#घोषणा TD_IR_SHIFT 17
#घोषणा TD_PCC_SHIFT 18
#घोषणा TD_EDC_SHIFT 19

#घोषणा DB_Enable_SHIFT 24
#घोषणा DB_IR_SHIFT 25
#घोषणा DB_PCC_SHIFT 26
#घोषणा DB_EDC_SHIFT 27

#घोषणा REMOVE_FMAX_MARGIN_BIT     0x0
#घोषणा REMOVE_DCTOL_MARGIN_BIT    0x1
#घोषणा REMOVE_PLATFORM_MARGIN_BIT 0x2

#पूर्ण_अगर
