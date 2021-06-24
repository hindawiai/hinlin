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

#अगर_अघोषित SMU13_DRIVER_IF_ALDEBARAN_H
#घोषणा SMU13_DRIVER_IF_ALDEBARAN_H

#घोषणा NUM_VCLK_DPM_LEVELS   8
#घोषणा NUM_DCLK_DPM_LEVELS   8
#घोषणा NUM_SOCCLK_DPM_LEVELS 8
#घोषणा NUM_LCLK_DPM_LEVELS   8
#घोषणा NUM_UCLK_DPM_LEVELS   4
#घोषणा NUM_FCLK_DPM_LEVELS   8
#घोषणा NUM_XGMI_DPM_LEVELS   4

// Feature Control Defines
#घोषणा FEATURE_DATA_CALCULATIONS       0
#घोषणा FEATURE_DPM_GFXCLK_BIT          1
#घोषणा FEATURE_DPM_UCLK_BIT            2
#घोषणा FEATURE_DPM_SOCCLK_BIT          3
#घोषणा FEATURE_DPM_FCLK_BIT            4
#घोषणा FEATURE_DPM_LCLK_BIT            5
#घोषणा FEATURE_DPM_XGMI_BIT            6
#घोषणा FEATURE_DS_GFXCLK_BIT           7
#घोषणा FEATURE_DS_SOCCLK_BIT           8
#घोषणा FEATURE_DS_LCLK_BIT             9
#घोषणा FEATURE_DS_FCLK_BIT             10
#घोषणा FEATURE_DS_UCLK_BIT             11
#घोषणा FEATURE_GFX_SS_BIT              12
#घोषणा FEATURE_DPM_VCN_BIT             13
#घोषणा FEATURE_RSMU_SMN_CG_BIT         14
#घोषणा FEATURE_WAFL_CG_BIT             15
#घोषणा FEATURE_PPT_BIT                 16
#घोषणा FEATURE_TDC_BIT                 17
#घोषणा FEATURE_APCC_PLUS_BIT           18
#घोषणा FEATURE_APCC_DFLL_BIT           19
#घोषणा FEATURE_FW_CTF_BIT              20
#घोषणा FEATURE_THERMAL_BIT             21
#घोषणा FEATURE_OUT_OF_BAND_MONITOR_BIT 22
#घोषणा FEATURE_SPARE_23_BIT            23
#घोषणा FEATURE_XGMI_PER_LINK_PWR_DWN   24
#घोषणा FEATURE_DF_CSTATE               25
#घोषणा FEATURE_FUSE_CG_BIT             26
#घोषणा FEATURE_MP1_CG_BIT              27
#घोषणा FEATURE_SMUIO_CG_BIT            28
#घोषणा FEATURE_THM_CG_BIT              29
#घोषणा FEATURE_CLK_CG_BIT              30
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

// I2C Config Bit Defines
#घोषणा I2C_CONTROLLER_ENABLED  1
#घोषणा I2C_CONTROLLER_DISABLED 0

// Throttler Status Bits.
// These are aligned with the out of band monitor alarm bits क्रम common throttlers
#घोषणा THROTTLER_PPT0_BIT         0
#घोषणा THROTTLER_PPT1_BIT         1
#घोषणा THROTTLER_TDC_GFX_BIT      2
#घोषणा THROTTLER_TDC_SOC_BIT      3
#घोषणा THROTTLER_TDC_HBM_BIT      4
#घोषणा THROTTLER_SPARE_5          5
#घोषणा THROTTLER_TEMP_GPU_BIT     6
#घोषणा THROTTLER_TEMP_MEM_BIT     7
#घोषणा THORTTLER_SPARE_8          8
#घोषणा THORTTLER_SPARE_9          9
#घोषणा THORTTLER_SPARE_10         10
#घोषणा THROTTLER_TEMP_VR_GFX_BIT  11
#घोषणा THROTTLER_TEMP_VR_SOC_BIT  12
#घोषणा THROTTLER_TEMP_VR_MEM_BIT  13
#घोषणा THORTTLER_SPARE_14         14
#घोषणा THORTTLER_SPARE_15         15
#घोषणा THORTTLER_SPARE_16         16
#घोषणा THORTTLER_SPARE_17         17
#घोषणा THORTTLER_SPARE_18         18
#घोषणा THROTTLER_APCC_BIT         19

// Table transfer status
#घोषणा TABLE_TRANSFER_OK         0x0
#घोषणा TABLE_TRANSFER_FAILED     0xFF
#घोषणा TABLE_TRANSFER_PENDING    0xAB

//I2C Interface
#घोषणा NUM_I2C_CONTROLLERS                8

#घोषणा I2C_CONTROLLER_ENABLED             1
#घोषणा I2C_CONTROLLER_DISABLED            0

#घोषणा MAX_SW_I2C_COMMANDS                24

प्रकार क्रमागत अणु
  I2C_CONTROLLER_PORT_0, //CKSVII2C0
  I2C_CONTROLLER_PORT_1, //CKSVII2C1
  I2C_CONTROLLER_PORT_COUNT,
पूर्ण I2cControllerPort_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_THROTTLER_TYPE_NONE,
  I2C_CONTROLLER_THROTTLER_VR_GFX0,
  I2C_CONTROLLER_THROTTLER_VR_GFX1,
  I2C_CONTROLLER_THROTTLER_VR_SOC,
  I2C_CONTROLLER_THROTTLER_VR_MEM,
  I2C_CONTROLLER_THROTTLER_COUNT,
पूर्ण I2cControllerThrottler_e;

प्रकार क्रमागत अणु
  I2C_CONTROLLER_PROTOCOL_VR_MP2855,
  I2C_CONTROLLER_PROTOCOL_COUNT,
पूर्ण I2cControllerProtocol_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t   Enabled;
  uपूर्णांक8_t   Speed;
  uपूर्णांक8_t   SlaveAddress;
  uपूर्णांक8_t   ControllerPort;
  uपूर्णांक8_t   ThermalThrotter;
  uपूर्णांक8_t   I2cProtocol;
  uपूर्णांक8_t   PaddingConfig[2];
पूर्ण I2cControllerConfig_t;

प्रकार क्रमागत अणु
  I2C_PORT_SVD_SCL,
  I2C_PORT_GPIO,
पूर्ण I2cPort_e;

प्रकार क्रमागत अणु
  I2C_SPEED_FAST_50K,     //50  Kbits/s
  I2C_SPEED_FAST_100K,    //100 Kbits/s
  I2C_SPEED_FAST_400K,    //400 Kbits/s
  I2C_SPEED_FAST_PLUS_1M, //1   Mbits/s (in fast mode)
  I2C_SPEED_HIGH_1M,      //1   Mbits/s (in high speed mode)
  I2C_SPEED_HIGH_2M,      //2.3 Mbits/s
  I2C_SPEED_COUNT,
पूर्ण I2cSpeed_e;

प्रकार क्रमागत अणु
  I2C_CMD_READ,
  I2C_CMD_WRITE,
  I2C_CMD_COUNT,
पूर्ण I2cCmdType_e;

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
  uपूर्णांक8_t    I2CcontrollerPort; //CKSVII2C0(0) or //CKSVII2C1(1)
  uपूर्णांक8_t    I2CSpeed;          //Use I2cSpeed_e to indicate speed to select
  uपूर्णांक8_t    SlaveAddress;      //Slave address of device
  uपूर्णांक8_t    NumCmds;           //Number of commands
  SwI2cCmd_t SwI2cCmds[MAX_SW_I2C_COMMANDS];
पूर्ण SwI2cRequest_t; // SW I2C Request Table

प्रकार काष्ठा अणु
  SwI2cRequest_t SwI2cRequest;
  uपूर्णांक32_t       Spare[8];
  uपूर्णांक32_t       MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SwI2cRequestExternal_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t a;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t b;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t c;  // store in IEEE भग्न क्रमmat in this variable
पूर्ण QuadraticInt_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t m;  // store in IEEE भग्न क्रमmat in this variable
  uपूर्णांक32_t b;  // store in IEEE भग्न क्रमmat in this variable
पूर्ण LinearInt_t;

प्रकार क्रमागत अणु
  GFXCLK_SOURCE_PLL,
  GFXCLK_SOURCE_DFLL,
  GFXCLK_SOURCE_COUNT,
पूर्ण GfxclkSrc_e;

प्रकार क्रमागत अणु
  PPCLK_GFXCLK,
  PPCLK_VCLK,
  PPCLK_DCLK,
  PPCLK_SOCCLK,
  PPCLK_UCLK,
  PPCLK_FCLK,
  PPCLK_LCLK,
  PPCLK_COUNT,
पूर्ण PPCLK_e;

प्रकार क्रमागत अणु
  GPIO_INT_POLARITY_ACTIVE_LOW,
  GPIO_INT_POLARITY_ACTIVE_HIGH,
पूर्ण GpioIntPolarity_e;

//PPSMC_MSG_SetUclkDpmMode
प्रकार क्रमागत अणु
  UCLK_DPM_MODE_BANDWIDTH,
  UCLK_DPM_MODE_LATENCY,
पूर्ण UCLK_DPM_MODE_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t        StartupLevel;
  uपूर्णांक8_t        NumDiscreteLevels;   // Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used
  uपूर्णांक16_t       SsFmin;              // Fmin क्रम SS curve. If SS curve is selected, will use V@SSFmin क्रम F <= Fmin
  LinearInt_t    ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
  QuadraticInt_t SsCurve;             // Slow-slow curve (GHz->V)
पूर्ण DpmDescriptor_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t Version;

  // SECTION: Feature Enablement
  uपूर्णांक32_t FeaturesToRun[2];

  // SECTION: Infraकाष्ठाure Limits
  uपूर्णांक16_t PptLimit;      // Watts
  uपूर्णांक16_t TdcLimitGfx;   // Amps
  uपूर्णांक16_t TdcLimitSoc;   // Amps
  uपूर्णांक16_t TdcLimitHbm;   // Amps
  uपूर्णांक16_t ThotspotLimit; // Celcius
  uपूर्णांक16_t TmemLimit;     // Celcius
  uपूर्णांक16_t Tvr_gfxLimit;  // Celcius
  uपूर्णांक16_t Tvr_memLimit;  // Celcius
  uपूर्णांक16_t Tvr_socLimit;  // Celcius
  uपूर्णांक16_t PaddingLimit;

  // SECTION: Voltage Control Parameters
  uपूर्णांक16_t MaxVoltageGfx; // In mV(Q2) Maximum Voltage allowable of VDD_GFX
  uपूर्णांक16_t MaxVoltageSoc; // In mV(Q2) Maximum Voltage allowable of VDD_SOC

  //SECTION: DPM Config 1
  DpmDescriptor_t DpmDescriptor[PPCLK_COUNT];

  uपूर्णांक8_t  DidTableVclk[NUM_VCLK_DPM_LEVELS];     //PPCLK_VCLK
  uपूर्णांक8_t  DidTableDclk[NUM_DCLK_DPM_LEVELS];     //PPCLK_DCLK
  uपूर्णांक8_t  DidTableSocclk[NUM_SOCCLK_DPM_LEVELS]; //PPCLK_SOCCLK
  uपूर्णांक8_t  DidTableLclk[NUM_LCLK_DPM_LEVELS];     //PPCLK_LCLK
  uपूर्णांक32_t FidTableFclk[NUM_FCLK_DPM_LEVELS];     //PPCLK_FCLK
  uपूर्णांक8_t  DidTableFclk[NUM_FCLK_DPM_LEVELS];     //PPCLK_FCLK
  uपूर्णांक32_t FidTableUclk[NUM_UCLK_DPM_LEVELS];     //PPCLK_UCLK
  uपूर्णांक8_t  DidTableUclk[NUM_UCLK_DPM_LEVELS];     //PPCLK_UCLK

  uपूर्णांक32_t StartupFidPll0; //GFXAVFSCLK, SOCCLK, MP0CLK, MPIOCLK, DXIOCLK
  uपूर्णांक32_t StartupFidPll4; //VCLK, DCLK, WAFLCLK
  uपूर्णांक32_t StartupFidPll5; //SMNCLK, MP1CLK, LCLK

  uपूर्णांक8_t  StartupSmnclkDid;
  uपूर्णांक8_t  StartupMp0clkDid;
  uपूर्णांक8_t  StartupMp1clkDid;
  uपूर्णांक8_t  StartupWaflclkDid;
  uपूर्णांक8_t  StartupGfxavfsclkDid;
  uपूर्णांक8_t  StartupMpioclkDid;
  uपूर्णांक8_t  StartupDxioclkDid;
  uपूर्णांक8_t  spare123;

  uपूर्णांक8_t  StartupVidGpu0Svi0Plane0; //VDDCR_GFX0
  uपूर्णांक8_t  StartupVidGpu0Svi0Plane1; //VDDCR_SOC
  uपूर्णांक8_t  StartupVidGpu0Svi1Plane0; //VDDCR_HBM
  uपूर्णांक8_t  StartupVidGpu0Svi1Plane1; //UNUSED [0 = plane is not used and should not be programmed]

  uपूर्णांक8_t  StartupVidGpu1Svi0Plane0; //VDDCR_GFX1
  uपूर्णांक8_t  StartupVidGpu1Svi0Plane1; //UNUSED [0 = plane is not used and should not be programmed]
  uपूर्णांक8_t  StartupVidGpu1Svi1Plane0; //UNUSED [0 = plane is not used and should not be programmed]
  uपूर्णांक8_t  StartupVidGpu1Svi1Plane1; //UNUSED [0 = plane is not used and should not be programmed]

  // GFXCLK DPM
  uपूर्णांक16_t GfxclkFmax;   // In MHz
  uपूर्णांक16_t GfxclkFmin;   // In MHz
  uपूर्णांक16_t GfxclkFidle;  // In MHz
  uपूर्णांक16_t GfxclkFinit;  // In MHz
  uपूर्णांक8_t  GfxclkSource; // GfxclkSrc_e [0 = PLL, 1 = DFLL]
  uपूर्णांक8_t  spare1[2];
  uपूर्णांक8_t  StartupGfxclkDid;
  uपूर्णांक32_t StartupGfxclkFid;

  // SECTION: AVFS
  uपूर्णांक16_t GFX_Guardband_Freq[8];         // MHz [अचिन्हित]
  पूर्णांक16_t  GFX_Guardband_Voltage_Cold[8]; // mV [चिन्हित]
  पूर्णांक16_t  GFX_Guardband_Voltage_Mid[8];  // mV [चिन्हित]
  पूर्णांक16_t  GFX_Guardband_Voltage_Hot[8];  // mV [चिन्हित]

  uपूर्णांक16_t SOC_Guardband_Freq[8];         // MHz [अचिन्हित]
  पूर्णांक16_t  SOC_Guardband_Voltage_Cold[8]; // mV [चिन्हित]
  पूर्णांक16_t  SOC_Guardband_Voltage_Mid[8];  // mV [चिन्हित]
  पूर्णांक16_t  SOC_Guardband_Voltage_Hot[8];  // mV [चिन्हित]

  // VDDCR_GFX BTC
  uपूर्णांक16_t DcBtcEnabled;
  पूर्णांक16_t  DcBtcMin;       // mV [चिन्हित]
  पूर्णांक16_t  DcBtcMax;       // mV [चिन्हित]
  पूर्णांक16_t  DcBtcGb;        // mV [चिन्हित]

  // SECTION: XGMI
  uपूर्णांक8_t  XgmiLinkSpeed[NUM_XGMI_DPM_LEVELS]; //Gbps [EX: 32 = 32Gbps]
  uपूर्णांक8_t  XgmiLinkWidth[NUM_XGMI_DPM_LEVELS]; //Width [EX: 16 = x16]
  uपूर्णांक8_t  XgmiStartupLevel;
  uपूर्णांक8_t  spare12[3];

  // GFX Vmin
  uपूर्णांक16_t GFX_PPVmin_Enabled;
  uपूर्णांक16_t GFX_Vmin_Plat_Offset_Hot;  // mV
  uपूर्णांक16_t GFX_Vmin_Plat_Offset_Cold; // mV
  uपूर्णांक16_t GFX_Vmin_Hot_T0;           // mV
  uपूर्णांक16_t GFX_Vmin_Cold_T0;          // mV
  uपूर्णांक16_t GFX_Vmin_Hot_Eol;          // mV
  uपूर्णांक16_t GFX_Vmin_Cold_Eol;         // mV
  uपूर्णांक16_t GFX_Vmin_Aging_Offset;     // mV
  uपूर्णांक16_t GFX_Vmin_Temperature_Hot;  // 'C
  uपूर्णांक16_t GFX_Vmin_Temperature_Cold; // 'C

  // SOC Vmin
  uपूर्णांक16_t SOC_PPVmin_Enabled;
  uपूर्णांक16_t SOC_Vmin_Plat_Offset_Hot;  // mV
  uपूर्णांक16_t SOC_Vmin_Plat_Offset_Cold; // mV
  uपूर्णांक16_t SOC_Vmin_Hot_T0;           // mV
  uपूर्णांक16_t SOC_Vmin_Cold_T0;          // mV
  uपूर्णांक16_t SOC_Vmin_Hot_Eol;          // mV
  uपूर्णांक16_t SOC_Vmin_Cold_Eol;         // mV
  uपूर्णांक16_t SOC_Vmin_Aging_Offset;     // mV
  uपूर्णांक16_t SOC_Vmin_Temperature_Hot;  // 'C
  uपूर्णांक16_t SOC_Vmin_Temperature_Cold; // 'C

  // APCC Settings
  uपूर्णांक32_t ApccPlusResidencyLimit; //PCC residency % (0-100)

  // Determinism
  uपूर्णांक16_t DeterminismVoltageOffset; //mV
  uपूर्णांक16_t spare22;

  // reserved
  uपूर्णांक32_t spare3[14];

  // SECTION: BOARD PARAMETERS
  // Telemetry Settings
  uपूर्णांक16_t GfxMaxCurrent; // in Amps
  पूर्णांक8_t   GfxOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetryGfx;

  uपूर्णांक16_t SocMaxCurrent; // in Amps
  पूर्णांक8_t   SocOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetrySoc;

  uपूर्णांक16_t MemMaxCurrent; // in Amps
  पूर्णांक8_t   MemOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetryMem;

  uपूर्णांक16_t BoardMaxCurrent; // in Amps
  पूर्णांक8_t   BoardOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetryBoardInput;

  // Platक्रमm input telemetry voltage coefficient
  uपूर्णांक32_t BoardVoltageCoeffA; // decode by /1000
  uपूर्णांक32_t BoardVoltageCoeffB; // decode by /1000

  // GPIO Settings
  uपूर्णांक8_t  VR0HotGpio;     // GPIO pin configured क्रम VR0 HOT event
  uपूर्णांक8_t  VR0HotPolarity; // GPIO polarity क्रम VR0 HOT event
  uपूर्णांक8_t  VR1HotGpio;     // GPIO pin configured क्रम VR1 HOT event
  uपूर्णांक8_t  VR1HotPolarity; // GPIO polarity क्रम VR1 HOT event

  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t  UclkSpपढ़ोEnabled; // on or off
  uपूर्णांक8_t  UclkSpपढ़ोPercent; // Q4.4
  uपूर्णांक16_t UclkSpपढ़ोFreq;    // kHz

  // FCLK Spपढ़ो Spectrum
  uपूर्णांक8_t  FclkSpपढ़ोEnabled; // on or off
  uपूर्णांक8_t  FclkSpपढ़ोPercent; // Q4.4
  uपूर्णांक16_t FclkSpपढ़ोFreq;    // kHz

  // I2C Controller Structure
  I2cControllerConfig_t  I2cControllers[NUM_I2C_CONTROLLERS];

  // GPIO pins क्रम I2C communications with 2nd controller क्रम Input Telemetry Sequence
  uपूर्णांक8_t  GpioI2cScl; // Serial Clock
  uपूर्णांक8_t  GpioI2cSda; // Serial Data
  uपूर्णांक16_t spare5;

  uपूर्णांक16_t XgmiMaxCurrent; // in Amps
  पूर्णांक8_t   XgmiOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetryXgmi;

  //reserved
  uपूर्णांक32_t reserved[15];

पूर्ण PPTable_t;

प्रकार काष्ठा अणु
  // Time स्थिरant parameters क्रम घड़ी averages in ms
  uपूर्णांक16_t     GfxclkAverageLpfTau;
  uपूर्णांक16_t     SocclkAverageLpfTau;
  uपूर्णांक16_t     UclkAverageLpfTau;
  uपूर्णांक16_t     GfxActivityLpfTau;
  uपूर्णांक16_t     UclkActivityLpfTau;

  uपूर्णांक16_t     SocketPowerLpfTau;

  uपूर्णांक32_t     Spare[8];
  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण DriverSmuConfig_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t CurrClock[PPCLK_COUNT];
  uपूर्णांक16_t Padding1              ;
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
  uपूर्णांक16_t TemperatureHBM        ;  // Max
  uपूर्णांक16_t TemperatureVrGfx      ;
  uपूर्णांक16_t TemperatureVrSoc      ;
  uपूर्णांक16_t TemperatureVrMem      ;
  uपूर्णांक32_t ThrottlerStatus       ;

  uपूर्णांक32_t PublicSerialNumLower32;
  uपूर्णांक32_t PublicSerialNumUpper32;
  uपूर्णांक16_t TemperatureAllHBM[4]  ;
  uपूर्णांक32_t GfxBusyAcc            ;
  uपूर्णांक32_t DramBusyAcc           ;
  uपूर्णांक32_t EnergyAcc64bitLow     ; //15.259uJ resolution
  uपूर्णांक32_t EnergyAcc64bitHigh    ;
  uपूर्णांक32_t TimeStampLow          ; //10ns resolution
  uपूर्णांक32_t TimeStampHigh         ;

  // Padding - ignore
  uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण SmuMetrics_t;


प्रकार काष्ठा अणु
  uपूर्णांक16_t avgPsmCount[76];
  uपूर्णांक16_t minPsmCount[76];
  भग्न    avgPsmVoltage[76];
  भग्न    minPsmVoltage[76];

  uपूर्णांक32_t MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण AvfsDebugTable_t;

// These defines are used with the following messages:
// SMC_MSG_TransferTableDram2Smu
// SMC_MSG_TransferTableSmu2Dram
#घोषणा TABLE_PPTABLE                 0
#घोषणा TABLE_AVFS_PSM_DEBUG          1
#घोषणा TABLE_AVFS_FUSE_OVERRIDE      2
#घोषणा TABLE_PMSTATUSLOG             3
#घोषणा TABLE_SMU_METRICS             4
#घोषणा TABLE_DRIVER_SMU_CONFIG       5
#घोषणा TABLE_I2C_COMMANDS            6
#घोषणा TABLE_COUNT                   7

#पूर्ण_अगर
