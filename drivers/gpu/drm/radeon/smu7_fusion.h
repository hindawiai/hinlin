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
 *
 */

#अगर_अघोषित SMU7_FUSION_H
#घोषणा SMU7_FUSION_H

#समावेश "smu7.h"

#आशय pack(push, 1)

#घोषणा SMU7_DTE_ITERATIONS 5
#घोषणा SMU7_DTE_SOURCES 5
#घोषणा SMU7_DTE_SINKS 3
#घोषणा SMU7_NUM_CPU_TES 2
#घोषणा SMU7_NUM_GPU_TES 1
#घोषणा SMU7_NUM_NON_TES 2

// All 'soft registers' should be uपूर्णांक32_t.
काष्ठा SMU7_SoftRegisters
अणु
    uपूर्णांक32_t        RefClockFrequency;
    uपूर्णांक32_t        PmTimerP;
    uपूर्णांक32_t        FeatureEnables;
    uपूर्णांक32_t        HandshakeDisables;

    uपूर्णांक8_t         DisplayPhy1Config;
    uपूर्णांक8_t         DisplayPhy2Config;
    uपूर्णांक8_t         DisplayPhy3Config;
    uपूर्णांक8_t         DisplayPhy4Config;

    uपूर्णांक8_t         DisplayPhy5Config;
    uपूर्णांक8_t         DisplayPhy6Config;
    uपूर्णांक8_t         DisplayPhy7Config;
    uपूर्णांक8_t         DisplayPhy8Config;

    uपूर्णांक32_t        AverageGraphicsA;
    uपूर्णांक32_t        AverageMemoryA;
    uपूर्णांक32_t        AverageGioA;

    uपूर्णांक8_t         SClkDpmEnabledLevels;
    uपूर्णांक8_t         MClkDpmEnabledLevels;
    uपूर्णांक8_t         LClkDpmEnabledLevels;
    uपूर्णांक8_t         PCIeDpmEnabledLevels;

    uपूर्णांक8_t         UVDDpmEnabledLevels;
    uपूर्णांक8_t         SAMUDpmEnabledLevels;
    uपूर्णांक8_t         ACPDpmEnabledLevels;
    uपूर्णांक8_t         VCEDpmEnabledLevels;

    uपूर्णांक32_t        DRAM_LOG_ADDR_H;
    uपूर्णांक32_t        DRAM_LOG_ADDR_L;
    uपूर्णांक32_t        DRAM_LOG_PHY_ADDR_H;
    uपूर्णांक32_t        DRAM_LOG_PHY_ADDR_L;
    uपूर्णांक32_t        DRAM_LOG_BUFF_SIZE;
    uपूर्णांक32_t        UlvEnterC;
    uपूर्णांक32_t        UlvTime;
    uपूर्णांक32_t        Reserved[3];

पूर्ण;

प्रकार काष्ठा SMU7_SoftRegisters SMU7_SoftRegisters;

काष्ठा SMU7_Fusion_GraphicsLevel
अणु
    uपूर्णांक32_t    MinVddNb;

    uपूर्णांक32_t    SclkFrequency;

    uपूर्णांक8_t     Vid;
    uपूर्णांक8_t     VidOffset;
    uपूर्णांक16_t    AT;

    uपूर्णांक8_t     PowerThrottle;
    uपूर्णांक8_t     GnbSlow;
    uपूर्णांक8_t     ForceNbPs1;
    uपूर्णांक8_t     SclkDid;

    uपूर्णांक8_t     DisplayWatermark;
    uपूर्णांक8_t     EnabledForActivity;
    uपूर्णांक8_t     EnabledForThrottle;
    uपूर्णांक8_t     UpH;

    uपूर्णांक8_t     DownH;
    uपूर्णांक8_t     VoltageDownH;
    uपूर्णांक8_t     DeepSleepDivId;

    uपूर्णांक8_t     ClkBypassCntl;

    uपूर्णांक32_t    reserved;
पूर्ण;

प्रकार काष्ठा SMU7_Fusion_GraphicsLevel SMU7_Fusion_GraphicsLevel;

काष्ठा SMU7_Fusion_GIOLevel
अणु
    uपूर्णांक8_t     EnabledForActivity;
    uपूर्णांक8_t     LclkDid;
    uपूर्णांक8_t     Vid;
    uपूर्णांक8_t     VoltageDownH;

    uपूर्णांक32_t    MinVddNb;

    uपूर्णांक16_t    ResidencyCounter;
    uपूर्णांक8_t     UpH;
    uपूर्णांक8_t     DownH;

    uपूर्णांक32_t    LclkFrequency;

    uपूर्णांक8_t     ActivityLevel;
    uपूर्णांक8_t     EnabledForThrottle;

    uपूर्णांक8_t     ClkBypassCntl;

    uपूर्णांक8_t     padding;
पूर्ण;

प्रकार काष्ठा SMU7_Fusion_GIOLevel SMU7_Fusion_GIOLevel;

// UVD VCLK/DCLK state (level) definition.
काष्ठा SMU7_Fusion_UvdLevel
अणु
    uपूर्णांक32_t VclkFrequency;
    uपूर्णांक32_t DclkFrequency;
    uपूर्णांक16_t MinVddNb;
    uपूर्णांक8_t  VclkDivider;
    uपूर्णांक8_t  DclkDivider;

    uपूर्णांक8_t     VClkBypassCntl;
    uपूर्णांक8_t     DClkBypassCntl;

    uपूर्णांक8_t     padding[2];

पूर्ण;

प्रकार काष्ठा SMU7_Fusion_UvdLevel SMU7_Fusion_UvdLevel;

// Clocks क्रम other बाह्यal blocks (VCE, ACP, SAMU).
काष्ठा SMU7_Fusion_ExtClkLevel
अणु
    uपूर्णांक32_t Frequency;
    uपूर्णांक16_t MinVoltage;
    uपूर्णांक8_t  Divider;
    uपूर्णांक8_t  ClkBypassCntl;

    uपूर्णांक32_t Reserved;
पूर्ण;
प्रकार काष्ठा SMU7_Fusion_ExtClkLevel SMU7_Fusion_ExtClkLevel;

काष्ठा SMU7_Fusion_ACPILevel
अणु
    uपूर्णांक32_t    Flags;
    uपूर्णांक32_t    MinVddNb;
    uपूर्णांक32_t    SclkFrequency;
    uपूर्णांक8_t     SclkDid;
    uपूर्णांक8_t     GnbSlow;
    uपूर्णांक8_t     ForceNbPs1;
    uपूर्णांक8_t     DisplayWatermark;
    uपूर्णांक8_t     DeepSleepDivId;
    uपूर्णांक8_t     padding[3];
पूर्ण;

प्रकार काष्ठा SMU7_Fusion_ACPILevel SMU7_Fusion_ACPILevel;

काष्ठा SMU7_Fusion_NbDpm
अणु
    uपूर्णांक8_t DpmXNbPsHi;
    uपूर्णांक8_t DpmXNbPsLo;
    uपूर्णांक8_t Dpm0PgNbPsHi;
    uपूर्णांक8_t Dpm0PgNbPsLo;
    uपूर्णांक8_t EnablePsi1;
    uपूर्णांक8_t SkipDPM0;
    uपूर्णांक8_t SkipPG;
    uपूर्णांक8_t Hysteresis;
    uपूर्णांक8_t EnableDpmPstatePoll;
    uपूर्णांक8_t padding[3];
पूर्ण;

प्रकार काष्ठा SMU7_Fusion_NbDpm SMU7_Fusion_NbDpm;

काष्ठा SMU7_Fusion_StateInfo
अणु
    uपूर्णांक32_t SclkFrequency;
    uपूर्णांक32_t LclkFrequency;
    uपूर्णांक32_t VclkFrequency;
    uपूर्णांक32_t DclkFrequency;
    uपूर्णांक32_t SamclkFrequency;
    uपूर्णांक32_t AclkFrequency;
    uपूर्णांक32_t EclkFrequency;
    uपूर्णांक8_t  DisplayWatermark;
    uपूर्णांक8_t  McArbIndex;
    पूर्णांक8_t   SclkIndex;
    पूर्णांक8_t   MclkIndex;
पूर्ण;

प्रकार काष्ठा SMU7_Fusion_StateInfo SMU7_Fusion_StateInfo;

काष्ठा SMU7_Fusion_DpmTable
अणु
    uपूर्णांक32_t                            SystemFlags;

    SMU7_PIDController                  GraphicsPIDController;
    SMU7_PIDController                  GioPIDController;

    uपूर्णांक8_t                            GraphicsDpmLevelCount;
    uपूर्णांक8_t                            GIOLevelCount;
    uपूर्णांक8_t                            UvdLevelCount;
    uपूर्णांक8_t                            VceLevelCount;

    uपूर्णांक8_t                            AcpLevelCount;
    uपूर्णांक8_t                            SamuLevelCount;
    uपूर्णांक16_t                           FpsHighT;

    SMU7_Fusion_GraphicsLevel         GraphicsLevel           [SMU__NUM_SCLK_DPM_STATE];
    SMU7_Fusion_ACPILevel             ACPILevel;
    SMU7_Fusion_UvdLevel              UvdLevel                [SMU7_MAX_LEVELS_UVD];
    SMU7_Fusion_ExtClkLevel           VceLevel                [SMU7_MAX_LEVELS_VCE];
    SMU7_Fusion_ExtClkLevel           AcpLevel                [SMU7_MAX_LEVELS_ACP];
    SMU7_Fusion_ExtClkLevel           SamuLevel               [SMU7_MAX_LEVELS_SAMU];

    uपूर्णांक8_t                           UvdBootLevel;
    uपूर्णांक8_t                           VceBootLevel;
    uपूर्णांक8_t                           AcpBootLevel;
    uपूर्णांक8_t                           SamuBootLevel;
    uपूर्णांक8_t                           UVDInterval;
    uपूर्णांक8_t                           VCEInterval;
    uपूर्णांक8_t                           ACPInterval;
    uपूर्णांक8_t                           SAMUInterval;

    uपूर्णांक8_t                           GraphicsBootLevel;
    uपूर्णांक8_t                           GraphicsInterval;
    uपूर्णांक8_t                           GraphicsThermThrottleEnable;
    uपूर्णांक8_t                           GraphicsVoltageChangeEnable;

    uपूर्णांक8_t                           GraphicsClkSlowEnable;
    uपूर्णांक8_t                           GraphicsClkSlowDivider;
    uपूर्णांक16_t                          FpsLowT;

    uपूर्णांक32_t                          DisplayCac;
    uपूर्णांक32_t                          LowSclkInterruptT;

    uपूर्णांक32_t                          DRAM_LOG_ADDR_H;
    uपूर्णांक32_t                          DRAM_LOG_ADDR_L;
    uपूर्णांक32_t                          DRAM_LOG_PHY_ADDR_H;
    uपूर्णांक32_t                          DRAM_LOG_PHY_ADDR_L;
    uपूर्णांक32_t                          DRAM_LOG_BUFF_SIZE;

पूर्ण;

काष्ठा SMU7_Fusion_GIODpmTable
अणु

    SMU7_Fusion_GIOLevel              GIOLevel                [SMU7_MAX_LEVELS_GIO];

    SMU7_PIDController                GioPIDController;

    uपूर्णांक32_t                          GIOLevelCount;

    uपूर्णांक8_t                           Enable;
    uपूर्णांक8_t                           GIOVoltageChangeEnable;
    uपूर्णांक8_t                           GIOBootLevel;
    uपूर्णांक8_t                           padding;
    uपूर्णांक8_t                           padding1[2];
    uपूर्णांक8_t                           TargetState;
    uपूर्णांक8_t                           CurrenttState;
    uपूर्णांक8_t                           ThrottleOnHtc;
    uपूर्णांक8_t                           ThermThrottleStatus;
    uपूर्णांक8_t                           ThermThrottleTempSelect;
    uपूर्णांक8_t                           ThermThrottleEnable;
    uपूर्णांक16_t                          TemperatureLimitHigh;
    uपूर्णांक16_t                          TemperatureLimitLow;

पूर्ण;

प्रकार काष्ठा SMU7_Fusion_DpmTable SMU7_Fusion_DpmTable;
प्रकार काष्ठा SMU7_Fusion_GIODpmTable SMU7_Fusion_GIODpmTable;

#आशय pack(pop)

#पूर्ण_अगर

