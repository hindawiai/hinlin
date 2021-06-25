<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#अगर_अघोषित SMU9_DRIVER_IF_H
#घोषणा SMU9_DRIVER_IF_H

#समावेश "smu9.h"

/**** IMPORTANT ***
 * SMU TEAM: Always increment the पूर्णांकerface version अगर
 * any काष्ठाure is changed in this file
 */
#घोषणा SMU9_DRIVER_IF_VERSION 0xE

#घोषणा PPTABLE_V10_SMU_VERSION 1

#घोषणा NUM_GFXCLK_DPM_LEVELS  8
#घोषणा NUM_UVD_DPM_LEVELS     8
#घोषणा NUM_VCE_DPM_LEVELS     8
#घोषणा NUM_MP0CLK_DPM_LEVELS  8
#घोषणा NUM_UCLK_DPM_LEVELS    4
#घोषणा NUM_SOCCLK_DPM_LEVELS  8
#घोषणा NUM_DCEFCLK_DPM_LEVELS 8
#घोषणा NUM_LINK_LEVELS        2

#घोषणा MAX_GFXCLK_DPM_LEVEL  (NUM_GFXCLK_DPM_LEVELS  - 1)
#घोषणा MAX_UVD_DPM_LEVEL     (NUM_UVD_DPM_LEVELS     - 1)
#घोषणा MAX_VCE_DPM_LEVEL     (NUM_VCE_DPM_LEVELS     - 1)
#घोषणा MAX_MP0CLK_DPM_LEVEL  (NUM_MP0CLK_DPM_LEVELS  - 1)
#घोषणा MAX_UCLK_DPM_LEVEL    (NUM_UCLK_DPM_LEVELS    - 1)
#घोषणा MAX_SOCCLK_DPM_LEVEL  (NUM_SOCCLK_DPM_LEVELS  - 1)
#घोषणा MAX_DCEFCLK_DPM_LEVEL (NUM_DCEFCLK_DPM_LEVELS - 1)
#घोषणा MAX_LINK_DPM_LEVEL    (NUM_LINK_LEVELS        - 1)

#घोषणा MIN_GFXCLK_DPM_LEVEL  0
#घोषणा MIN_UVD_DPM_LEVEL     0
#घोषणा MIN_VCE_DPM_LEVEL     0
#घोषणा MIN_MP0CLK_DPM_LEVEL  0
#घोषणा MIN_UCLK_DPM_LEVEL    0
#घोषणा MIN_SOCCLK_DPM_LEVEL  0
#घोषणा MIN_DCEFCLK_DPM_LEVEL 0
#घोषणा MIN_LINK_DPM_LEVEL    0

#घोषणा NUM_EVV_VOLTAGE_LEVELS 8
#घोषणा MAX_EVV_VOLTAGE_LEVEL (NUM_EVV_VOLTAGE_LEVELS - 1)
#घोषणा MIN_EVV_VOLTAGE_LEVEL 0

#घोषणा NUM_PSP_LEVEL_MAP 4

/* Gemini Modes */
#घोषणा PPSMC_GeminiModeNone   0  /* Single GPU board */
#घोषणा PPSMC_GeminiModeMaster 1  /* Master GPU on a Gemini board */
#घोषणा PPSMC_GeminiModeSlave  2  /* Slave GPU on a Gemini board */

/* Voltage Modes क्रम DPMs */
#घोषणा VOLTAGE_MODE_AVFS_INTERPOLATE 0
#घोषणा VOLTAGE_MODE_AVFS_WORST_CASE  1
#घोषणा VOLTAGE_MODE_STATIC           2

प्रकार काष्ठा अणु
  uपूर्णांक32_t FbMult; /* Feedback Multiplier, bit 8:0 पूर्णांक, bit 15:12 post_भाग, bit 31:16 frac */
  uपूर्णांक32_t SsFbMult; /* Spपढ़ो FB Mult: bit 8:0 पूर्णांक, bit 31:16 frac */
  uपूर्णांक16_t SsSlewFrac;
  uपूर्णांक8_t  SsOn;
  uपूर्णांक8_t  Did;      /* DID */
पूर्ण PllSetting_t;

प्रकार काष्ठा अणु
  पूर्णांक32_t a0;
  पूर्णांक32_t a1;
  पूर्णांक32_t a2;

  uपूर्णांक8_t a0_shअगरt;
  uपूर्णांक8_t a1_shअगरt;
  uपूर्णांक8_t a2_shअगरt;
  uपूर्णांक8_t padding;
पूर्ण GbVdroopTable_t;

प्रकार काष्ठा अणु
  पूर्णांक32_t m1;
  पूर्णांक32_t m2;
  पूर्णांक32_t b;

  uपूर्णांक8_t m1_shअगरt;
  uपूर्णांक8_t m2_shअगरt;
  uपूर्णांक8_t b_shअगरt;
  uपूर्णांक8_t padding;
पूर्ण QuadraticInt_t;

#घोषणा NUM_DSPCLK_LEVELS 8

प्रकार क्रमागत अणु
  DSPCLK_DCEFCLK = 0,
  DSPCLK_DISPCLK,
  DSPCLK_PIXCLK,
  DSPCLK_PHYCLK,
  DSPCLK_COUNT,
पूर्ण DSPCLK_e;

प्रकार काष्ठा अणु
  uपूर्णांक16_t Freq; /* in MHz */
  uपूर्णांक16_t Vid;  /* min voltage in SVI2 VID */
पूर्ण DisplayClockTable_t;

प्रकार काष्ठा अणु
  /* PowerTune */
  uपूर्णांक16_t SocketPowerLimit; /* Watts */
  uपूर्णांक16_t TdcLimit;         /* Amps */
  uपूर्णांक16_t EdcLimit;         /* Amps */
  uपूर्णांक16_t TedgeLimit;       /* Celcius */
  uपूर्णांक16_t ThotspotLimit;    /* Celcius */
  uपूर्णांक16_t ThbmLimit;        /* Celcius */
  uपूर्णांक16_t Tvr_socLimit;     /* Celcius */
  uपूर्णांक16_t Tvr_memLimit;     /* Celcius */
  uपूर्णांक16_t Tliquid1Limit;    /* Celcius */
  uपूर्णांक16_t Tliquid2Limit;    /* Celcius */
  uपूर्णांक16_t TplxLimit;        /* Celcius */
  uपूर्णांक16_t LoadLineResistance; /* in mOhms */
  uपूर्णांक32_t FitLimit;         /* Failures in समय (failures per million parts over the defined lअगरeसमय) */

  /* External Component Communication Settings */
  uपूर्णांक8_t  Liquid1_I2C_address;
  uपूर्णांक8_t  Liquid2_I2C_address;
  uपूर्णांक8_t  Vr_I2C_address;
  uपूर्णांक8_t  Plx_I2C_address;

  uपूर्णांक8_t  GeminiMode;
  uपूर्णांक8_t  spare17[3];
  uपूर्णांक32_t GeminiApertureHigh;
  uपूर्णांक32_t GeminiApertureLow;

  uपूर्णांक8_t  Liquid_I2C_LineSCL;
  uपूर्णांक8_t  Liquid_I2C_LineSDA;
  uपूर्णांक8_t  Vr_I2C_LineSCL;
  uपूर्णांक8_t  Vr_I2C_LineSDA;
  uपूर्णांक8_t  Plx_I2C_LineSCL;
  uपूर्णांक8_t  Plx_I2C_LineSDA;
  uपूर्णांक8_t  paddingx[2];

  /* ULV Settings */
  uपूर्णांक8_t  UlvOffsetVid;     /* SVI2 VID */
  uपूर्णांक8_t  UlvSmnclkDid;     /* DID क्रम ULV mode. 0 means CLK will not be modअगरied in ULV. */
  uपूर्णांक8_t  UlvMp1clkDid;     /* DID क्रम ULV mode. 0 means CLK will not be modअगरied in ULV. */
  uपूर्णांक8_t  UlvGfxclkBypass;  /* 1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV */

  /* VDDCR_SOC Voltages */
  uपूर्णांक8_t      SocVid[NUM_EVV_VOLTAGE_LEVELS];

  /* This is the minimum voltage needed to run the SOC. */
  uपूर्णांक8_t      MinVoltageVid; /* Minimum Voltage ("Vmin") of ASIC */
  uपूर्णांक8_t      MaxVoltageVid; /* Maximum Voltage allowable */
  uपूर्णांक8_t      MaxVidStep; /* Max VID step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value. */
  uपूर्णांक8_t      padding8;

  uपूर्णांक8_t      UlvPhaseSheddingPsi0; /* set this to 1 to set PSI0/1 to 1 in ULV mode */
  uपूर्णांक8_t      UlvPhaseSheddingPsi1; /* set this to 1 to set PSI0/1 to 1 in ULV mode */
  uपूर्णांक8_t      padding8_2[2];

  /* SOC Frequencies */
  PllSetting_t GfxclkLevel        [NUM_GFXCLK_DPM_LEVELS];

  uपूर्णांक8_t      SocclkDid          [NUM_SOCCLK_DPM_LEVELS];          /* DID */
  uपूर्णांक8_t      SocDpmVoltageIndex [NUM_SOCCLK_DPM_LEVELS];

  uपूर्णांक8_t      VclkDid            [NUM_UVD_DPM_LEVELS];            /* DID */
  uपूर्णांक8_t      DclkDid            [NUM_UVD_DPM_LEVELS];            /* DID */
  uपूर्णांक8_t      UvdDpmVoltageIndex [NUM_UVD_DPM_LEVELS];

  uपूर्णांक8_t      EclkDid            [NUM_VCE_DPM_LEVELS];            /* DID */
  uपूर्णांक8_t      VceDpmVoltageIndex [NUM_VCE_DPM_LEVELS];

  uपूर्णांक8_t      Mp0clkDid          [NUM_MP0CLK_DPM_LEVELS];          /* DID */
  uपूर्णांक8_t      Mp0DpmVoltageIndex [NUM_MP0CLK_DPM_LEVELS];

  DisplayClockTable_t DisplayClockTable[DSPCLK_COUNT][NUM_DSPCLK_LEVELS];
  QuadraticInt_t      DisplayClock2Gfxclk[DSPCLK_COUNT];

  uपूर्णांक8_t      GfxDpmVoltageMode;
  uपूर्णांक8_t      SocDpmVoltageMode;
  uपूर्णांक8_t      UclkDpmVoltageMode;
  uपूर्णांक8_t      UvdDpmVoltageMode;

  uपूर्णांक8_t      VceDpmVoltageMode;
  uपूर्णांक8_t      Mp0DpmVoltageMode;
  uपूर्णांक8_t      DisplayDpmVoltageMode;
  uपूर्णांक8_t      padding8_3;

  uपूर्णांक16_t     GfxclkSlewRate;
  uपूर्णांक16_t     padding;

  uपूर्णांक32_t     LowGfxclkInterruptThreshold;  /* in units of 10KHz */

  /* Alpha parameters क्रम घड़ी averages. ("255"=1) */
  uपूर्णांक8_t      GfxclkAverageAlpha;
  uपूर्णांक8_t      SocclkAverageAlpha;
  uपूर्णांक8_t      UclkAverageAlpha;
  uपूर्णांक8_t      GfxActivityAverageAlpha;

  /* UCLK States */
  uपूर्णांक8_t      MemVid[NUM_UCLK_DPM_LEVELS];    /* VID */
  PllSetting_t UclkLevel[NUM_UCLK_DPM_LEVELS];   /* Full PLL settings */
  uपूर्णांक8_t      MemSocVoltageIndex[NUM_UCLK_DPM_LEVELS];
  uपूर्णांक8_t      LowestUclkReservedForUlv; /* Set this to 1 अगर UCLK DPM0 is reserved क्रम ULV-mode only */
  uपूर्णांक8_t      paddingUclk[3];
  uपूर्णांक16_t     NumMemoryChannels;  /* Used क्रम memory bandwidth calculations */
  uपूर्णांक16_t     MemoryChannelWidth; /* Used क्रम memory bandwidth calculations */

  /* CKS Settings */
  uपूर्णांक8_t      CksEnable[NUM_GFXCLK_DPM_LEVELS];
  uपूर्णांक8_t      CksVidOffset[NUM_GFXCLK_DPM_LEVELS];

  /* MP0 Mapping Table */
  uपूर्णांक8_t      PspLevelMap[NUM_PSP_LEVEL_MAP];

  /* Link DPM Settings */
  uपूर्णांक8_t     PcieGenSpeed[NUM_LINK_LEVELS];           /* 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 */
  uपूर्णांक8_t     PcieLaneCount[NUM_LINK_LEVELS];          /* 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16 */
  uपूर्णांक8_t     LclkDid[NUM_LINK_LEVELS];                /* Leave at 0 to use hardcoded values in FW */
  uपूर्णांक8_t     paddingLinkDpm[2];

  /* Fan Control */
  uपूर्णांक16_t     FanStopTemp;          /* Celcius */
  uपूर्णांक16_t     FanStartTemp;         /* Celcius */

  uपूर्णांक16_t     FanGainEdge;
  uपूर्णांक16_t     FanGainHotspot;
  uपूर्णांक16_t     FanGainLiquid;
  uपूर्णांक16_t     FanGainVrVddc;
  uपूर्णांक16_t     FanGainVrMvdd;
  uपूर्णांक16_t     FanGainPlx;
  uपूर्णांक16_t     FanGainHbm;
  uपूर्णांक16_t     FanPwmMin;
  uपूर्णांक16_t     FanAcousticLimitRpm;
  uपूर्णांक16_t     FanThrottlingRpm;
  uपूर्णांक16_t     FanMaximumRpm;
  uपूर्णांक16_t     FanTargetTemperature;
  uपूर्णांक16_t     FanTargetGfxclk;
  uपूर्णांक8_t      FanZeroRpmEnable;
  uपूर्णांक8_t      FanSpare;

  /* The following are AFC override parameters. Leave at 0 to use FW शेषs. */
  पूर्णांक16_t      FuzzyFan_ErrorSetDelta;
  पूर्णांक16_t      FuzzyFan_ErrorRateSetDelta;
  पूर्णांक16_t      FuzzyFan_PwmSetDelta;
  uपूर्णांक16_t     FuzzyFan_Reserved;

  /* GPIO Settings */
  uपूर्णांक8_t      AcDcGpio;        /* GPIO pin configured क्रम AC/DC चयनing */
  uपूर्णांक8_t      AcDcPolarity;    /* GPIO polarity क्रम AC/DC चयनing */
  uपूर्णांक8_t      VR0HotGpio;      /* GPIO pin configured क्रम VR0 HOT event */
  uपूर्णांक8_t      VR0HotPolarity;  /* GPIO polarity क्रम VR0 HOT event */
  uपूर्णांक8_t      VR1HotGpio;      /* GPIO pin configured क्रम VR1 HOT event */
  uपूर्णांक8_t      VR1HotPolarity;  /* GPIO polarity क्रम VR1 HOT event */
  uपूर्णांक8_t      Padding1;       /* replace GPIO pin configured क्रम CTF */
  uपूर्णांक8_t      Padding2;       /* replace GPIO polarity क्रम CTF */

  /* LED Display Settings */
  uपूर्णांक8_t      LedPin0;         /* GPIO number क्रम LedPin[0] */
  uपूर्णांक8_t      LedPin1;         /* GPIO number क्रम LedPin[1] */
  uपूर्णांक8_t      LedPin2;         /* GPIO number क्रम LedPin[2] */
  uपूर्णांक8_t      padding8_4;

  /* AVFS */
  uपूर्णांक8_t      OverrideBtcGbCksOn;
  uपूर्णांक8_t      OverrideAvfsGbCksOn;
  uपूर्णांक8_t      PaddingAvfs8[2];

  GbVdroopTable_t BtcGbVdroopTableCksOn;
  GbVdroopTable_t BtcGbVdroopTableCksOff;

  QuadraticInt_t  AvfsGbCksOn;  /* Replacement equation */
  QuadraticInt_t  AvfsGbCksOff; /* Replacement equation */

  uपूर्णांक8_t      StaticVoltageOffsetVid[NUM_GFXCLK_DPM_LEVELS]; /* This values are added on to the final voltage calculation */

  /* Ageing Guardband Parameters */
  uपूर्णांक32_t     AConstant[3];
  uपूर्णांक16_t     DC_tol_sigma;
  uपूर्णांक16_t     Platक्रमm_mean;
  uपूर्णांक16_t     Platक्रमm_sigma;
  uपूर्णांक16_t     PSM_Age_CompFactor;

  uपूर्णांक32_t     DpmLevelPowerDelta;

  uपूर्णांक8_t      EnableBoostState;
  uपूर्णांक8_t      AConstant_Shअगरt;
  uपूर्णांक8_t      DC_tol_sigma_Shअगरt;
  uपूर्णांक8_t      PSM_Age_CompFactor_Shअगरt;

  uपूर्णांक16_t     BoostStartTemperature;
  uपूर्णांक16_t     BoostStopTemperature;

  PllSetting_t GfxBoostState;

  uपूर्णांक8_t      AcgEnable[NUM_GFXCLK_DPM_LEVELS];
  GbVdroopTable_t AcgBtcGbVdroopTable;
  QuadraticInt_t  AcgAvfsGb;

  /* ACG Frequency Table, in Mhz */
  uपूर्णांक32_t     AcgFreqTable[NUM_GFXCLK_DPM_LEVELS];

  /* Padding - ignore */
  uपूर्णांक32_t     MmHubPadding[3]; /* SMU पूर्णांकernal use */

पूर्ण PPTable_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t MinClock; // This is either DCEFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MaxClock; // This is either DCEFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MinUclk;
  uपूर्णांक16_t MaxUclk;

  uपूर्णांक8_t  WmSetting;
  uपूर्णांक8_t  Padding[3];
पूर्ण WatermarkRowGeneric_t;

#घोषणा NUM_WM_RANGES 4

प्रकार क्रमागत अणु
  WM_SOCCLK = 0,
  WM_DCEFCLK,
  WM_COUNT,
पूर्ण WM_CLOCK_e;

प्रकार काष्ठा अणु
  /* Watermarks */
  WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];

  uपूर्णांक32_t     MmHubPadding[7]; /* SMU पूर्णांकernal use */
पूर्ण Watermarks_t;

#अगर_घोषित PPTABLE_V10_SMU_VERSION
प्रकार काष्ठा अणु
  भग्न        AvfsGbCksOn[NUM_GFXCLK_DPM_LEVELS];
  भग्न        AcBtcGbCksOn[NUM_GFXCLK_DPM_LEVELS];
  भग्न        AvfsGbCksOff[NUM_GFXCLK_DPM_LEVELS];
  भग्न        AcBtcGbCksOff[NUM_GFXCLK_DPM_LEVELS];
  भग्न        DcBtcGb;

  uपूर्णांक32_t     MmHubPadding[7]; /* SMU पूर्णांकernal use */
पूर्ण AvfsTable_t;
#अन्यथा
प्रकार काष्ठा अणु
  uपूर्णांक32_t     AvfsGbCksOn[NUM_GFXCLK_DPM_LEVELS];
  uपूर्णांक32_t     AcBtcGbCksOn[NUM_GFXCLK_DPM_LEVELS];
  uपूर्णांक32_t     AvfsGbCksOff[NUM_GFXCLK_DPM_LEVELS];
  uपूर्णांक32_t     AcBtcGbCksOff[NUM_GFXCLK_DPM_LEVELS];
  uपूर्णांक32_t     DcBtcGb;

  uपूर्णांक32_t     MmHubPadding[7]; /* SMU पूर्णांकernal use */
पूर्ण AvfsTable_t;
#पूर्ण_अगर

प्रकार काष्ठा अणु
  uपूर्णांक16_t avgPsmCount[30];
  uपूर्णांक16_t minPsmCount[30];
  भग्न    avgPsmVoltage[30];
  भग्न    minPsmVoltage[30];

  uपूर्णांक32_t MmHubPadding[7]; /* SMU पूर्णांकernal use */
पूर्ण AvfsDebugTable_t;

प्रकार काष्ठा अणु
  uपूर्णांक8_t  AvfsEn;
  uपूर्णांक8_t  AvfsVersion;
  uपूर्णांक8_t  Padding[2];

  पूर्णांक32_t VFT0_m1; /* Q8.24 */
  पूर्णांक32_t VFT0_m2; /* Q12.12 */
  पूर्णांक32_t VFT0_b;  /* Q32 */

  पूर्णांक32_t VFT1_m1; /* Q8.16 */
  पूर्णांक32_t VFT1_m2; /* Q12.12 */
  पूर्णांक32_t VFT1_b;  /* Q32 */

  पूर्णांक32_t VFT2_m1; /* Q8.16 */
  पूर्णांक32_t VFT2_m2; /* Q12.12 */
  पूर्णांक32_t VFT2_b;  /* Q32 */

  पूर्णांक32_t AvfsGb0_m1; /* Q8.16 */
  पूर्णांक32_t AvfsGb0_m2; /* Q12.12 */
  पूर्णांक32_t AvfsGb0_b;  /* Q32 */

  पूर्णांक32_t AcBtcGb_m1; /* Q8.24 */
  पूर्णांक32_t AcBtcGb_m2; /* Q12.12 */
  पूर्णांक32_t AcBtcGb_b;  /* Q32 */

  uपूर्णांक32_t AvfsTempCold;
  uपूर्णांक32_t AvfsTempMid;
  uपूर्णांक32_t AvfsTempHot;

  uपूर्णांक32_t InversionVoltage; /*  in mV with 2 fractional bits */

  पूर्णांक32_t P2V_m1; /* Q8.24 */
  पूर्णांक32_t P2V_m2; /* Q12.12 */
  पूर्णांक32_t P2V_b;  /* Q32 */

  uपूर्णांक32_t P2VCharzFreq; /* in 10KHz units */

  uपूर्णांक32_t EnabledAvfsModules;

  uपूर्णांक32_t MmHubPadding[7]; /* SMU पूर्णांकernal use */
पूर्ण AvfsFuseOverride_t;

/* These defines are used with the following messages:
 * SMC_MSG_TransferTableDram2Smu
 * SMC_MSG_TransferTableSmu2Dram
 */
#घोषणा TABLE_PPTABLE            0
#घोषणा TABLE_WATERMARKS         1
#घोषणा TABLE_AVFS               2
#घोषणा TABLE_AVFS_PSM_DEBUG     3
#घोषणा TABLE_AVFS_FUSE_OVERRIDE 4
#घोषणा TABLE_PMSTATUSLOG        5
#घोषणा TABLE_COUNT              6

/* These defines are used with the SMC_MSG_SetUclkFastSwitch message. */
#घोषणा UCLK_SWITCH_SLOW 0
#घोषणा UCLK_SWITCH_FAST 1

/* GFX DIDT Configuration */
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
