<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#अगर_अघोषित _SMU73_DISCRETE_H_
#घोषणा _SMU73_DISCRETE_H_

#समावेश "smu73.h"

#आशय pack(push, 1)

काष्ठा SMIO_Pattern
अणु
  uपूर्णांक16_t Voltage;
  uपूर्णांक8_t  Smio;
  uपूर्णांक8_t  padding;
पूर्ण;

प्रकार काष्ठा SMIO_Pattern SMIO_Pattern;

काष्ठा SMIO_Table
अणु
  SMIO_Pattern Pattern[SMU_MAX_SMIO_LEVELS];
पूर्ण;

प्रकार काष्ठा SMIO_Table SMIO_Table;

काष्ठा SMU73_Discrete_GraphicsLevel अणु
	uपूर्णांक32_t    MinVoltage;

	uपूर्णांक32_t    SclkFrequency;

	uपूर्णांक8_t     pcieDpmLevel;
	uपूर्णांक8_t     DeepSleepDivId;
	uपूर्णांक16_t    ActivityLevel;
	uपूर्णांक32_t    CgSpllFuncCntl3;
	uपूर्णांक32_t    CgSpllFuncCntl4;
	uपूर्णांक32_t    SpllSpपढ़ोSpectrum;
	uपूर्णांक32_t    SpllSpपढ़ोSpectrum2;
	uपूर्णांक32_t    CcPwrDynRm;
	uपूर्णांक32_t    CcPwrDynRm1;
	uपूर्णांक8_t     SclkDid;
	uपूर्णांक8_t     DisplayWatermark;
	uपूर्णांक8_t     EnabledForActivity;
	uपूर्णांक8_t     EnabledForThrottle;
	uपूर्णांक8_t     UpHyst;
	uपूर्णांक8_t     DownHyst;
	uपूर्णांक8_t     VoltageDownHyst;
	uपूर्णांक8_t     PowerThrottle;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_GraphicsLevel SMU73_Discrete_GraphicsLevel;

काष्ठा SMU73_Discrete_ACPILevel अणु
    uपूर्णांक32_t    Flags;
    uपूर्णांक32_t MinVoltage;
    uपूर्णांक32_t    SclkFrequency;
    uपूर्णांक8_t     SclkDid;
    uपूर्णांक8_t     DisplayWatermark;
    uपूर्णांक8_t     DeepSleepDivId;
    uपूर्णांक8_t     padding;
    uपूर्णांक32_t    CgSpllFuncCntl;
    uपूर्णांक32_t    CgSpllFuncCntl2;
    uपूर्णांक32_t    CgSpllFuncCntl3;
    uपूर्णांक32_t    CgSpllFuncCntl4;
    uपूर्णांक32_t    SpllSpपढ़ोSpectrum;
    uपूर्णांक32_t    SpllSpपढ़ोSpectrum2;
    uपूर्णांक32_t    CcPwrDynRm;
    uपूर्णांक32_t    CcPwrDynRm1;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_ACPILevel SMU73_Discrete_ACPILevel;

काष्ठा SMU73_Discrete_Ulv अणु
	uपूर्णांक32_t    CcPwrDynRm;
	uपूर्णांक32_t    CcPwrDynRm1;
	uपूर्णांक16_t    VddcOffset;
	uपूर्णांक8_t     VddcOffsetVid;
	uपूर्णांक8_t     VddcPhase;
	uपूर्णांक32_t    Reserved;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_Ulv SMU73_Discrete_Ulv;

काष्ठा SMU73_Discrete_MemoryLevel
अणु
    uपूर्णांक32_t MinVoltage;
    uपूर्णांक32_t    MinMvdd;

    uपूर्णांक32_t    MclkFrequency;

    uपूर्णांक8_t     StutterEnable;
    uपूर्णांक8_t     FreqRange;
    uपूर्णांक8_t     EnabledForThrottle;
    uपूर्णांक8_t     EnabledForActivity;

    uपूर्णांक8_t     UpHyst;
    uपूर्णांक8_t     DownHyst;
    uपूर्णांक8_t     VoltageDownHyst;
    uपूर्णांक8_t     padding;

    uपूर्णांक16_t    ActivityLevel;
    uपूर्णांक8_t     DisplayWatermark;
    uपूर्णांक8_t     MclkDivider;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_MemoryLevel SMU73_Discrete_MemoryLevel;

काष्ठा SMU73_Discrete_LinkLevel
अणु
    uपूर्णांक8_t     PcieGenSpeed;           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3
    uपूर्णांक8_t     PcieLaneCount;          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16 
    uपूर्णांक8_t     EnabledForActivity;
    uपूर्णांक8_t     SPC;
    uपूर्णांक32_t    DownThreshold;
    uपूर्णांक32_t    UpThreshold;
    uपूर्णांक32_t    Reserved;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_LinkLevel SMU73_Discrete_LinkLevel;


// MC ARB DRAM Timing रेजिस्टरs.
काष्ठा SMU73_Discrete_MCArbDramTimingTableEntry
अणु
    uपूर्णांक32_t McArbDramTiming;
    uपूर्णांक32_t McArbDramTiming2;
    uपूर्णांक8_t  McArbBurstTime;
    uपूर्णांक8_t  TRRDS;
    uपूर्णांक8_t  TRRDL;
    uपूर्णांक8_t  padding;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_MCArbDramTimingTableEntry SMU73_Discrete_MCArbDramTimingTableEntry;

काष्ठा SMU73_Discrete_MCArbDramTimingTable
अणु
    SMU73_Discrete_MCArbDramTimingTableEntry entries[SMU__NUM_SCLK_DPM_STATE][SMU__NUM_MCLK_DPM_LEVELS];
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_MCArbDramTimingTable SMU73_Discrete_MCArbDramTimingTable;

// UVD VCLK/DCLK state (level) definition.
काष्ठा SMU73_Discrete_UvdLevel
अणु
    uपूर्णांक32_t VclkFrequency;
    uपूर्णांक32_t DclkFrequency;
    uपूर्णांक32_t MinVoltage;
    uपूर्णांक8_t  VclkDivider;
    uपूर्णांक8_t  DclkDivider;
    uपूर्णांक8_t  padding[2];
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_UvdLevel SMU73_Discrete_UvdLevel;

// Clocks क्रम other बाह्यal blocks (VCE, ACP, SAMU).
काष्ठा SMU73_Discrete_ExtClkLevel
अणु
    uपूर्णांक32_t Frequency;
    uपूर्णांक32_t MinVoltage;
    uपूर्णांक8_t  Divider;
    uपूर्णांक8_t  padding[3];
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_ExtClkLevel SMU73_Discrete_ExtClkLevel;

काष्ठा SMU73_Discrete_StateInfo
अणु
    uपूर्णांक32_t SclkFrequency;
    uपूर्णांक32_t MclkFrequency;
    uपूर्णांक32_t VclkFrequency;
    uपूर्णांक32_t DclkFrequency;
    uपूर्णांक32_t SamclkFrequency;
    uपूर्णांक32_t AclkFrequency;
    uपूर्णांक32_t EclkFrequency;
    uपूर्णांक16_t MvddVoltage;
    uपूर्णांक16_t padding16;
    uपूर्णांक8_t  DisplayWatermark;
    uपूर्णांक8_t  McArbIndex;
    uपूर्णांक8_t  McRegIndex;
    uपूर्णांक8_t  SeqIndex;
    uपूर्णांक8_t  SclkDid;
    पूर्णांक8_t   SclkIndex;
    पूर्णांक8_t   MclkIndex;
    uपूर्णांक8_t  PCIeGen;

पूर्ण;

प्रकार काष्ठा SMU73_Discrete_StateInfo SMU73_Discrete_StateInfo;

काष्ठा SMU73_Discrete_DpmTable
अणु
    // Multi-DPM controller settings
    SMU73_PIDController                  GraphicsPIDController;
    SMU73_PIDController                  MemoryPIDController;
    SMU73_PIDController                  LinkPIDController;

    uपूर्णांक32_t                            SystemFlags;

    // SMIO masks क्रम voltage and phase controls
    uपूर्णांक32_t                            VRConfig;
    uपूर्णांक32_t                            SmioMask1;
    uपूर्णांक32_t                            SmioMask2;
    SMIO_Table                          SmioTable1;
    SMIO_Table                          SmioTable2;

    uपूर्णांक32_t                            MvddLevelCount;


    uपूर्णांक8_t                             BapmVddcVidHiSidd        [SMU73_MAX_LEVELS_VDDC];
    uपूर्णांक8_t                             BapmVddcVidLoSidd        [SMU73_MAX_LEVELS_VDDC];
    uपूर्णांक8_t                             BapmVddcVidHiSidd2       [SMU73_MAX_LEVELS_VDDC];

    uपूर्णांक8_t                             GraphicsDpmLevelCount;
    uपूर्णांक8_t                             MemoryDpmLevelCount;
    uपूर्णांक8_t                             LinkLevelCount;
    uपूर्णांक8_t                             MasterDeepSleepControl;

    uपूर्णांक8_t                             UvdLevelCount;
    uपूर्णांक8_t                             VceLevelCount;
    uपूर्णांक8_t                             AcpLevelCount;
    uपूर्णांक8_t                             SamuLevelCount;

    uपूर्णांक8_t                             ThermOutGpio;
    uपूर्णांक8_t                             ThermOutPolarity;
    uपूर्णांक8_t                             ThermOutMode;
    uपूर्णांक8_t                             BootPhases;
    uपूर्णांक32_t                            Reserved[4];

    // State table entries क्रम each DPM state
    SMU73_Discrete_GraphicsLevel        GraphicsLevel           [SMU73_MAX_LEVELS_GRAPHICS];
    SMU73_Discrete_MemoryLevel          MemoryACPILevel;
    SMU73_Discrete_MemoryLevel          MemoryLevel             [SMU73_MAX_LEVELS_MEMORY];
    SMU73_Discrete_LinkLevel            LinkLevel               [SMU73_MAX_LEVELS_LINK];
    SMU73_Discrete_ACPILevel            ACPILevel;
    SMU73_Discrete_UvdLevel             UvdLevel                [SMU73_MAX_LEVELS_UVD];
    SMU73_Discrete_ExtClkLevel          VceLevel                [SMU73_MAX_LEVELS_VCE];
    SMU73_Discrete_ExtClkLevel          AcpLevel                [SMU73_MAX_LEVELS_ACP];
    SMU73_Discrete_ExtClkLevel          SamuLevel               [SMU73_MAX_LEVELS_SAMU];
    SMU73_Discrete_Ulv                  Ulv;

    uपूर्णांक32_t                            SclkStepSize;
    uपूर्णांक32_t                            Smio                    [SMU73_MAX_ENTRIES_SMIO];

    uपूर्णांक8_t                             UvdBootLevel;
    uपूर्णांक8_t                             VceBootLevel;
    uपूर्णांक8_t                             AcpBootLevel;
    uपूर्णांक8_t                             SamuBootLevel;

    uपूर्णांक8_t                             GraphicsBootLevel;
    uपूर्णांक8_t                             GraphicsVoltageChangeEnable;
    uपूर्णांक8_t                             GraphicsThermThrottleEnable;
    uपूर्णांक8_t                             GraphicsInterval;

    uपूर्णांक8_t                             VoltageInterval;
    uपूर्णांक8_t                             ThermalInterval;
    uपूर्णांक16_t                            TemperatureLimitHigh;

    uपूर्णांक16_t                            TemperatureLimitLow;
    uपूर्णांक8_t                             MemoryBootLevel;
    uपूर्णांक8_t                             MemoryVoltageChangeEnable;

    uपूर्णांक16_t                            BootMVdd;
    uपूर्णांक8_t                             MemoryInterval;
    uपूर्णांक8_t                             MemoryThermThrottleEnable;

    uपूर्णांक16_t                            VoltageResponseTime;
    uपूर्णांक16_t                            PhaseResponseTime;

    uपूर्णांक8_t                             PCIeBootLinkLevel;
    uपूर्णांक8_t                             PCIeGenInterval;
    uपूर्णांक8_t                             DTEInterval;
    uपूर्णांक8_t                             DTEMode;

    uपूर्णांक8_t                             SVI2Enable;
    uपूर्णांक8_t                             VRHotGpio;
    uपूर्णांक8_t                             AcDcGpio;
    uपूर्णांक8_t                             ThermGpio;

    uपूर्णांक16_t                            PPM_PkgPwrLimit;
    uपूर्णांक16_t                            PPM_TemperatureLimit;

    uपूर्णांक16_t                            DefaultTdp;
    uपूर्णांक16_t                            TargetTdp;

    uपूर्णांक16_t                            FpsHighThreshold;
    uपूर्णांक16_t                            FpsLowThreshold;

    uपूर्णांक16_t                            TemperatureLimitEdge;
    uपूर्णांक16_t                            TemperatureLimitHotspot;
    uपूर्णांक16_t                            TemperatureLimitLiquid1;
    uपूर्णांक16_t                            TemperatureLimitLiquid2;
    uपूर्णांक16_t                            TemperatureLimitVrVddc;
    uपूर्णांक16_t                            TemperatureLimitVrMvdd;
    uपूर्णांक16_t                            TemperatureLimitPlx;

    uपूर्णांक16_t                            FanGainEdge;
    uपूर्णांक16_t                            FanGainHotspot;
    uपूर्णांक16_t                            FanGainLiquid;
    uपूर्णांक16_t                            FanGainVrVddc;
    uपूर्णांक16_t                            FanGainVrMvdd;
    uपूर्णांक16_t                            FanGainPlx;
    uपूर्णांक16_t                            FanGainHbm;

    uपूर्णांक8_t                             Liquid1_I2C_address;
    uपूर्णांक8_t                             Liquid2_I2C_address;
    uपूर्णांक8_t                             Vr_I2C_address;
    uपूर्णांक8_t                             Plx_I2C_address;

    uपूर्णांक8_t                             GeminiMode;
    uपूर्णांक8_t                             spare17[3];
    uपूर्णांक32_t                            GeminiApertureHigh;
    uपूर्णांक32_t                            GeminiApertureLow;

    uपूर्णांक8_t                             Liquid_I2C_LineSCL;
    uपूर्णांक8_t                             Liquid_I2C_LineSDA;
    uपूर्णांक8_t                             Vr_I2C_LineSCL;
    uपूर्णांक8_t                             Vr_I2C_LineSDA;
    uपूर्णांक8_t                             Plx_I2C_LineSCL;
    uपूर्णांक8_t                             Plx_I2C_LineSDA;

    uपूर्णांक8_t                             spare1253[2];
    uपूर्णांक32_t                            spare123[2];

    uपूर्णांक8_t                             DTEAmbientTempBase;
    uपूर्णांक8_t                             DTETjOffset;
    uपूर्णांक8_t                             GpuTjMax;
    uपूर्णांक8_t                             GpuTjHyst;

    uपूर्णांक16_t                            BootVddc;
    uपूर्णांक16_t                            BootVddci;

    uपूर्णांक32_t                            BAPM_TEMP_GRADIENT;

    uपूर्णांक32_t                            LowSclkInterruptThreshold;
    uपूर्णांक32_t                            VddGfxReChkWait;

    uपूर्णांक8_t                             ClockStretcherAmount;
    uपूर्णांक8_t                             Sclk_CKS_masterEn0_7;
    uपूर्णांक8_t                             Sclk_CKS_masterEn8_15;
    uपूर्णांक8_t                             DPMFreezeAndForced;

    uपूर्णांक8_t                             Sclk_voltageOffset[8];

    SMU_ClockStretcherDataTable         ClockStretcherDataTable;
    SMU_CKS_LOOKUPTable                 CKS_LOOKUPTable;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_DpmTable SMU73_Discrete_DpmTable;


// --------------------------------------------------- Fan Table -----------------------------------------------------------
काष्ठा SMU73_Discrete_FanTable
अणु
    uपूर्णांक16_t FकरोMode;
    पूर्णांक16_t  TempMin;
    पूर्णांक16_t  TempMed;
    पूर्णांक16_t  TempMax;
    पूर्णांक16_t  Slope1;
    पूर्णांक16_t  Slope2;
    पूर्णांक16_t  FकरोMin;
    पूर्णांक16_t  HystUp;
    पूर्णांक16_t  HystDown;
    पूर्णांक16_t  HystSlope;
    पूर्णांक16_t  TempRespLim;
    पूर्णांक16_t  TempCurr;
    पूर्णांक16_t  SlopeCurr;
    पूर्णांक16_t  PwmCurr;
    uपूर्णांक32_t RefreshPeriod;
    पूर्णांक16_t  FकरोMax;
    uपूर्णांक8_t  TempSrc;
    पूर्णांक8_t   Padding;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_FanTable SMU73_Discrete_FanTable;

#घोषणा SMU7_DISCRETE_GPIO_SCLK_DEBUG             4
#घोषणा SMU7_DISCRETE_GPIO_SCLK_DEBUG_BIT         (0x1 << SMU7_DISCRETE_GPIO_SCLK_DEBUG)



काष्ठा SMU7_MclkDpmScoreboard
अणु

    uपूर्णांक32_t PercentageBusy;

    पूर्णांक32_t  PIDError;
    पूर्णांक32_t  PIDIntegral;
    पूर्णांक32_t  PIDOutput;

    uपूर्णांक32_t SigmaDeltaAccum;
    uपूर्णांक32_t SigmaDeltaOutput;
    uपूर्णांक32_t SigmaDeltaLevel;

    uपूर्णांक32_t UtilizationSetpoपूर्णांक;

    uपूर्णांक8_t  TdpClampMode;
    uपूर्णांक8_t  TdcClampMode;
    uपूर्णांक8_t  ThermClampMode;
    uपूर्णांक8_t  VoltageBusy;

    पूर्णांक8_t   CurrLevel;
    पूर्णांक8_t   TargLevel;
    uपूर्णांक8_t  LevelChangeInProgress;
    uपूर्णांक8_t  UpHyst;

    uपूर्णांक8_t  DownHyst;
    uपूर्णांक8_t  VoltageDownHyst;
    uपूर्णांक8_t  DpmEnable;
    uपूर्णांक8_t  DpmRunning;

    uपूर्णांक8_t  DpmForce;
    uपूर्णांक8_t  DpmForceLevel;
    uपूर्णांक8_t  DisplayWatermark;
    uपूर्णांक8_t  McArbIndex;

    uपूर्णांक32_t MinimumPerfMclk;

    uपूर्णांक8_t  AcpiReq;
    uपूर्णांक8_t  AcpiAck;
    uपूर्णांक8_t  MclkSwitchInProgress;
    uपूर्णांक8_t  MclkSwitchCritical;

    uपूर्णांक8_t  IgnoreVBlank;
    uपूर्णांक8_t  TargetMclkIndex;
    uपूर्णांक8_t  TargetMvddIndex;
    uपूर्णांक8_t  MclkSwitchResult;

    uपूर्णांक16_t VbiFailureCount;
    uपूर्णांक8_t  VbiWaitCounter;
    uपूर्णांक8_t  EnabledLevelsChange;

    uपूर्णांक16_t LevelResidencyCounters [SMU73_MAX_LEVELS_MEMORY];
    uपूर्णांक16_t LevelSwitchCounters [SMU73_MAX_LEVELS_MEMORY];

    व्योम     (*TargetStateCalculator)(uपूर्णांक8_t);
    व्योम     (*SavedTargetStateCalculator)(uपूर्णांक8_t);

    uपूर्णांक16_t AutoDpmInterval;
    uपूर्णांक16_t AutoDpmRange;

    uपूर्णांक16_t VbiTimeoutCount;
    uपूर्णांक16_t MclkSwitchingTime;

    uपूर्णांक8_t  fastSwitch;
    uपूर्णांक8_t  Save_PIC_VDDGFX_EXIT;
    uपूर्णांक8_t  Save_PIC_VDDGFX_ENTER;
    uपूर्णांक8_t  padding;

पूर्ण;

प्रकार काष्ठा SMU7_MclkDpmScoreboard SMU7_MclkDpmScoreboard;

काष्ठा SMU7_UlvScoreboard
अणु
    uपूर्णांक8_t     EnterUlv;
    uपूर्णांक8_t     ExitUlv;
    uपूर्णांक8_t     UlvActive;
    uपूर्णांक8_t     WaitingForUlv;
    uपूर्णांक8_t     UlvEnable;
    uपूर्णांक8_t     UlvRunning;
    uपूर्णांक8_t     UlvMasterEnable;
    uपूर्णांक8_t     padding;
    uपूर्णांक32_t    UlvAbortedCount;
    uपूर्णांक32_t    UlvTimeStamp;
पूर्ण;

प्रकार काष्ठा SMU7_UlvScoreboard SMU7_UlvScoreboard;

काष्ठा VddgfxSavedRegisters
अणु
  uपूर्णांक32_t GPU_DBG[3];
  uपूर्णांक32_t MEC_BaseAddress_Hi;
  uपूर्णांक32_t MEC_BaseAddress_Lo;
  uपूर्णांक32_t THM_TMON0_CTRL2__Rसूची_PRESENT;
  uपूर्णांक32_t THM_TMON1_CTRL2__Rसूची_PRESENT;
  uपूर्णांक32_t CP_INT_CNTL;
पूर्ण;

प्रकार काष्ठा VddgfxSavedRegisters VddgfxSavedRegisters;

काष्ठा SMU7_VddGfxScoreboard
अणु
    uपूर्णांक8_t     VddGfxEnable;
    uपूर्णांक8_t     VddGfxActive;
    uपूर्णांक8_t     VPUResetOccured;
    uपूर्णांक8_t     padding;

    uपूर्णांक32_t    VddGfxEnteredCount;
    uपूर्णांक32_t    VddGfxAbortedCount;

    uपूर्णांक32_t    VddGfxVid;

    VddgfxSavedRegisters SavedRegisters;
पूर्ण;

प्रकार काष्ठा SMU7_VddGfxScoreboard SMU7_VddGfxScoreboard;

काष्ठा SMU7_TdcLimitScoreboard अणु
  uपूर्णांक8_t  Enable;
  uपूर्णांक8_t  Running;
  uपूर्णांक16_t Alpha;
  uपूर्णांक32_t FilteredIddc;
  uपूर्णांक32_t IddcLimit;
  uपूर्णांक32_t IddcHyst;
  SMU7_HystController_Data HystControllerData;
पूर्ण;

प्रकार काष्ठा SMU7_TdcLimitScoreboard SMU7_TdcLimitScoreboard;

काष्ठा SMU7_PkgPwrLimitScoreboard अणु
  uपूर्णांक8_t  Enable;
  uपूर्णांक8_t  Running;
  uपूर्णांक16_t Alpha;
  uपूर्णांक32_t FilteredPkgPwr;
  uपूर्णांक32_t Limit;
  uपूर्णांक32_t Hyst;
  uपूर्णांक32_t LimitFromDriver;
  SMU7_HystController_Data HystControllerData;
पूर्ण;

प्रकार काष्ठा SMU7_PkgPwrLimitScoreboard SMU7_PkgPwrLimitScoreboard;

काष्ठा SMU7_BapmScoreboard अणु
  uपूर्णांक32_t source_घातers[SMU73_DTE_SOURCES];
  uपूर्णांक32_t source_घातers_last[SMU73_DTE_SOURCES];
  पूर्णांक32_t entity_temperatures[SMU73_NUM_GPU_TES];
  पूर्णांक32_t initial_entity_temperatures[SMU73_NUM_GPU_TES];
  पूर्णांक32_t Limit;
  पूर्णांक32_t Hyst;
  पूर्णांक32_t therm_influence_coeff_table[SMU73_DTE_ITERATIONS * SMU73_DTE_SOURCES * SMU73_DTE_SINKS * 2];
  पूर्णांक32_t therm_node_table[SMU73_DTE_ITERATIONS * SMU73_DTE_SOURCES * SMU73_DTE_SINKS];
  uपूर्णांक16_t ConfigTDPPowerScalar;
  uपूर्णांक16_t FanSpeedPowerScalar;
  uपूर्णांक16_t OverDrivePowerScalar;
  uपूर्णांक16_t OverDriveLimitScalar;
  uपूर्णांक16_t FinalPowerScalar;
  uपूर्णांक8_t VariantID;
  uपूर्णांक8_t spare997;

  SMU7_HystController_Data HystControllerData;

  पूर्णांक32_t temperature_gradient_slope;
  पूर्णांक32_t temperature_gradient;
  uपूर्णांक32_t measured_temperature;
पूर्ण;


प्रकार काष्ठा SMU7_BapmScoreboard SMU7_BapmScoreboard;

काष्ठा SMU7_AcpiScoreboard अणु
  uपूर्णांक32_t SavedInterruptMask[2];
  uपूर्णांक8_t LastACPIRequest;
  uपूर्णांक8_t CgBअगरResp;
  uपूर्णांक8_t RequestType;
  uपूर्णांक8_t Padding;
  SMU73_Discrete_ACPILevel D0Level;
पूर्ण;

प्रकार काष्ठा SMU7_AcpiScoreboard SMU7_AcpiScoreboard;

काष्ठा SMU_QuadraticCoeffs अणु
  पूर्णांक32_t m1;
  uपूर्णांक32_t b;

  पूर्णांक16_t m2;
  uपूर्णांक8_t m1_shअगरt;
  uपूर्णांक8_t m2_shअगरt;
पूर्ण;

प्रकार काष्ठा SMU_QuadraticCoeffs SMU_QuadraticCoeffs;

काष्ठा SMU73_Discrete_PmFuses अणु
  /* dw0-dw1 */
  uपूर्णांक8_t BapmVddCVidHiSidd[8];

  /* dw2-dw3 */
  uपूर्णांक8_t BapmVddCVidLoSidd[8];

  /* dw4-dw5 */
  uपूर्णांक8_t VddCVid[8];

  /* dw1*/
  uपूर्णांक8_t SviLoadLineEn;
  uपूर्णांक8_t SviLoadLineVddC;
  uपूर्णांक8_t SviLoadLineTrimVddC;
  uपूर्णांक8_t SviLoadLineOffsetVddC;

  /* dw2 */
  uपूर्णांक16_t TDC_VDDC_PkgLimit;
  uपूर्णांक8_t TDC_VDDC_ThrottleReleaseLimitPerc;
  uपूर्णांक8_t TDC_MAWt;

  /* dw3 */
  uपूर्णांक8_t TdcWaterfallCtl;
  uपूर्णांक8_t LPMLTemperatureMin;
  uपूर्णांक8_t LPMLTemperatureMax;
  uपूर्णांक8_t Reserved;

  /* dw4-dw7 */
  uपूर्णांक8_t LPMLTemperatureScaler[16];

  /* dw8-dw9 */
  पूर्णांक16_t FuzzyFan_ErrorSetDelta;
  पूर्णांक16_t FuzzyFan_ErrorRateSetDelta;
  पूर्णांक16_t FuzzyFan_PwmSetDelta;
  uपूर्णांक16_t Reserved6;

  /* dw10-dw14 */
  uपूर्णांक8_t GnbLPML[16];

  /* dw15 */
  uपूर्णांक8_t GnbLPMLMaxVid;
  uपूर्णांक8_t GnbLPMLMinVid;
  uपूर्णांक8_t Reserved1[2];

  /* dw16 */
  uपूर्णांक16_t BapmVddCBaseLeakageHiSidd;
  uपूर्णांक16_t BapmVddCBaseLeakageLoSidd;

  /* AVFS */
  uपूर्णांक16_t  VFT_Temp[3];
  uपूर्णांक16_t  padding;

  SMU_QuadraticCoeffs VFT_ATE[3];

  SMU_QuadraticCoeffs AVFS_GB;
  SMU_QuadraticCoeffs ATE_ACBTC_GB;

  SMU_QuadraticCoeffs P2V;

  uपूर्णांक32_t PsmCharzFreq;

  uपूर्णांक16_t InversionVoltage;
  uपूर्णांक16_t PsmCharzTemp;

  uपूर्णांक32_t EnabledAvfsModules;
पूर्ण;

प्रकार काष्ठा SMU73_Discrete_PmFuses SMU73_Discrete_PmFuses;

काष्ठा SMU7_Discrete_Log_Header_Table अणु
  uपूर्णांक32_t    version;
  uपूर्णांक32_t    asic_id;
  uपूर्णांक16_t    flags;
  uपूर्णांक16_t    entry_size;
  uपूर्णांक32_t    total_size;
  uपूर्णांक32_t    num_of_entries;
  uपूर्णांक8_t     type;
  uपूर्णांक8_t     mode;
  uपूर्णांक8_t     filler_0[2];
  uपूर्णांक32_t    filler_1[2];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_Log_Header_Table SMU7_Discrete_Log_Header_Table;

काष्ठा SMU7_Discrete_Log_Cntl अणु
    uपूर्णांक8_t             Enabled;
    uपूर्णांक8_t             Type;
    uपूर्णांक8_t             padding[2];
    uपूर्णांक32_t            BufferSize;
    uपूर्णांक32_t            SamplesLogged;
    uपूर्णांक32_t            SampleSize;
    uपूर्णांक32_t            AddrL;
    uपूर्णांक32_t            AddrH;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_Log_Cntl SMU7_Discrete_Log_Cntl;

#घोषणा CAC_ACC_NW_NUM_OF_SIGNALS 87

काष्ठा SMU7_Discrete_Cac_Collection_Table अणु
  uपूर्णांक32_t temperature;
  uपूर्णांक32_t cac_acc_nw[CAC_ACC_NW_NUM_OF_SIGNALS];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_Cac_Collection_Table SMU7_Discrete_Cac_Collection_Table;

काष्ठा SMU7_Discrete_Cac_Verअगरication_Table अणु
  uपूर्णांक32_t VddcTotalPower;
  uपूर्णांक32_t VddcLeakagePower;
  uपूर्णांक32_t VddcConstantPower;
  uपूर्णांक32_t VddcGfxDynamicPower;
  uपूर्णांक32_t VddcUvdDynamicPower;
  uपूर्णांक32_t VddcVceDynamicPower;
  uपूर्णांक32_t VddcAcpDynamicPower;
  uपूर्णांक32_t VddcPcieDynamicPower;
  uपूर्णांक32_t VddcDceDynamicPower;
  uपूर्णांक32_t VddcCurrent;
  uपूर्णांक32_t VddcVoltage;
  uपूर्णांक32_t VddciTotalPower;
  uपूर्णांक32_t VddciLeakagePower;
  uपूर्णांक32_t VddciConstantPower;
  uपूर्णांक32_t VddciDynamicPower;
  uपूर्णांक32_t Vddr1TotalPower;
  uपूर्णांक32_t Vddr1LeakagePower;
  uपूर्णांक32_t Vddr1ConstantPower;
  uपूर्णांक32_t Vddr1DynamicPower;
  uपूर्णांक32_t spare[4];
  uपूर्णांक32_t temperature;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_Cac_Verअगरication_Table SMU7_Discrete_Cac_Verअगरication_Table;

काष्ठा SMU7_Discrete_Pm_Status_Table अणु
  //Thermal entities
  पूर्णांक32_t  T_meas_max[SMU73_THERMAL_INPUT_LOOP_COUNT];
  पूर्णांक32_t  T_meas_acc[SMU73_THERMAL_INPUT_LOOP_COUNT];
  पूर्णांक32_t  T_meas_acc_cnt[SMU73_THERMAL_INPUT_LOOP_COUNT];
  uपूर्णांक32_t T_hbm_acc;

  //Voltage करोमुख्यs
  uपूर्णांक32_t I_calc_max;
  uपूर्णांक32_t I_calc_acc;
  uपूर्णांक32_t P_meas_acc;
  uपूर्णांक32_t V_meas_load_acc;
  uपूर्णांक32_t I_meas_acc;
  uपूर्णांक32_t P_meas_acc_vddci;
  uपूर्णांक32_t V_meas_load_acc_vddci;
  uपूर्णांक32_t I_meas_acc_vddci;

  //Frequency
  uपूर्णांक16_t Sclk_dpm_residency[8];
  uपूर्णांक16_t Uvd_dpm_residency[8];
  uपूर्णांक16_t Vce_dpm_residency[8];

  //Chip
  uपूर्णांक32_t P_roc_acc;
  uपूर्णांक32_t PkgPwr_max;
  uपूर्णांक32_t PkgPwr_acc;
  uपूर्णांक32_t MclkSwitchingTime_max;
  uपूर्णांक32_t MclkSwitchingTime_acc;
  uपूर्णांक32_t FanPwm_acc;
  uपूर्णांक32_t FanRpm_acc;
  uपूर्णांक32_t Gfx_busy_acc;
  uपूर्णांक32_t Mc_busy_acc;
  uपूर्णांक32_t Fps_acc;

  uपूर्णांक32_t AccCnt;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_Pm_Status_Table SMU7_Discrete_Pm_Status_Table;

//FIXME THESE NEED TO BE UPDATED
#घोषणा SMU7_SCLK_CAC 0x561
#घोषणा SMU7_MCLK_CAC 0xF9
#घोषणा SMU7_VCLK_CAC 0x2DE
#घोषणा SMU7_DCLK_CAC 0x2DE
#घोषणा SMU7_ECLK_CAC 0x25E
#घोषणा SMU7_ACLK_CAC 0x25E
#घोषणा SMU7_SAMCLK_CAC 0x25E
#घोषणा SMU7_DISPCLK_CAC 0x100
#घोषणा SMU7_CAC_CONSTANT 0x2EE3430
#घोषणा SMU7_CAC_CONSTANT_SHIFT 18

#घोषणा SMU7_VDDCI_MCLK_CONST        1765
#घोषणा SMU7_VDDCI_MCLK_CONST_SHIFT  16
#घोषणा SMU7_VDDCI_VDDCI_CONST       50958
#घोषणा SMU7_VDDCI_VDDCI_CONST_SHIFT 14
#घोषणा SMU7_VDDCI_CONST             11781
#घोषणा SMU7_VDDCI_STROBE_PWR        1331

#घोषणा SMU7_VDDR1_CONST            693
#घोषणा SMU7_VDDR1_CAC_WEIGHT       20
#घोषणा SMU7_VDDR1_CAC_WEIGHT_SHIFT 19
#घोषणा SMU7_VDDR1_STROBE_PWR       512

#घोषणा SMU7_AREA_COEFF_UVD 0xA78
#घोषणा SMU7_AREA_COEFF_VCE 0x190A
#घोषणा SMU7_AREA_COEFF_ACP 0x22D1
#घोषणा SMU7_AREA_COEFF_SAMU 0x534

//ThermOutMode values
#घोषणा SMU7_THERM_OUT_MODE_DISABLE       0x0
#घोषणा SMU7_THERM_OUT_MODE_THERM_ONLY    0x1
#घोषणा SMU7_THERM_OUT_MODE_THERM_VRHOT   0x2

#आशय pack(pop)

#पूर्ण_अगर

