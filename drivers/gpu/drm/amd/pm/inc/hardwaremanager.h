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
#अगर_अघोषित _HARDWARE_MANAGER_H_
#घोषणा _HARDWARE_MANAGER_H_



काष्ठा pp_hwmgr;
काष्ठा pp_hw_घातer_state;
काष्ठा pp_घातer_state;
क्रमागत amd_dpm_क्रमced_level;
काष्ठा PP_TemperatureRange;


काष्ठा phm_fan_speed_info अणु
	uपूर्णांक32_t min_percent;
	uपूर्णांक32_t max_percent;
	uपूर्णांक32_t min_rpm;
	uपूर्णांक32_t max_rpm;
	bool supports_percent_पढ़ो;
	bool supports_percent_ग_लिखो;
	bool supports_rpm_पढ़ो;
	bool supports_rpm_ग_लिखो;
पूर्ण;

/* Automatic Power State Throttling */
क्रमागत PHM_AutoThrottleSource
अणु
    PHM_AutoThrottleSource_Thermal,
    PHM_AutoThrottleSource_External
पूर्ण;

प्रकार क्रमागत PHM_AutoThrottleSource PHM_AutoThrottleSource;

क्रमागत phm_platक्रमm_caps अणु
	PHM_Platक्रमmCaps_AtomBiosPpV1 = 0,
	PHM_Platक्रमmCaps_PowerPlaySupport,
	PHM_Platक्रमmCaps_ACOverdriveSupport,
	PHM_Platक्रमmCaps_BacklightSupport,
	PHM_Platक्रमmCaps_ThermalController,
	PHM_Platक्रमmCaps_BiosPowerSourceControl,
	PHM_Platक्रमmCaps_DisableVoltageTransition,
	PHM_Platक्रमmCaps_DisableEngineTransition,
	PHM_Platक्रमmCaps_DisableMemoryTransition,
	PHM_Platक्रमmCaps_DynamicPowerManagement,
	PHM_Platक्रमmCaps_EnableASPML0s,
	PHM_Platक्रमmCaps_EnableASPML1,
	PHM_Platक्रमmCaps_OD5inACSupport,
	PHM_Platक्रमmCaps_OD5inDCSupport,
	PHM_Platक्रमmCaps_SoftStateOD5,
	PHM_Platक्रमmCaps_NoOD5Support,
	PHM_Platक्रमmCaps_ContinuousHardwarePerक्रमmanceRange,
	PHM_Platक्रमmCaps_ActivityReporting,
	PHM_Platक्रमmCaps_EnableBackbias,
	PHM_Platक्रमmCaps_OverdriveDisabledByPowerBudget,
	PHM_Platक्रमmCaps_ShowPowerBudgetWarning,
	PHM_Platक्रमmCaps_PowerBudgetWaiverAvailable,
	PHM_Platक्रमmCaps_GFXClockGatingSupport,
	PHM_Platक्रमmCaps_MMClockGatingSupport,
	PHM_Platक्रमmCaps_AutomaticDCTransition,
	PHM_Platक्रमmCaps_GeminiPrimary,
	PHM_Platक्रमmCaps_MemorySpपढ़ोSpectrumSupport,
	PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport,
	PHM_Platक्रमmCaps_StepVddc,
	PHM_Platक्रमmCaps_DynamicPCIEGen2Support,
	PHM_Platक्रमmCaps_SMC,
	PHM_Platक्रमmCaps_FaultyInternalThermalReading,          /* Internal thermal controller reports faulty temperature value when DAC2 is active */
	PHM_Platक्रमmCaps_EnableVoltageControl,                  /* indicates voltage can be controlled */
	PHM_Platक्रमmCaps_EnableSideportControl,                 /* indicates Sideport can be controlled */
	PHM_Platक्रमmCaps_VideoPlaybackEEUNotअगरication,          /* indicates EEU notअगरication of video start/stop is required */
	PHM_Platक्रमmCaps_TurnOffPll_ASPML1,                     /* PCIE Turn Off PLL in ASPM L1 */
	PHM_Platक्रमmCaps_EnableHTLinkControl,                   /* indicates HT Link can be controlled by ACPI or CLMC overridden/स्वतःmated mode. */
	PHM_Platक्रमmCaps_Perक्रमmanceStateOnly,                  /* indicates only perक्रमmance घातer state to be used on current प्रणाली. */
	PHM_Platक्रमmCaps_ExclusiveModeAlwaysHigh,               /* In Exclusive (3D) mode always stay in High state. */
	PHM_Platक्रमmCaps_DisableMGClockGating,                  /* to disable Medium Grain Clock Gating or not */
	PHM_Platक्रमmCaps_DisableMGCGTSSM,                       /* TO disable Medium Grain Clock Gating Shader Complex control */
	PHM_Platक्रमmCaps_UVDAlwaysHigh,                         /* In UVD mode always stay in High state */
	PHM_Platक्रमmCaps_DisablePowerGating,                    /* to disable घातer gating */
	PHM_Platक्रमmCaps_CustomThermalPolicy,                   /* indicates only perक्रमmance घातer state to be used on current प्रणाली. */
	PHM_Platक्रमmCaps_StayInBootState,                       /* Stay in Boot State, करो not करो घड़ी/voltage or PCIe Lane and Gen चयनing (RV7xx and up). */
	PHM_Platक्रमmCaps_SMCAllowSeparateSWThermalState,        /* SMC use separate SW thermal state, instead of the शेष SMC thermal policy. */
	PHM_Platक्रमmCaps_MultiUVDStateSupport,                  /* Powerplay state table supports multi UVD states. */
	PHM_Platक्रमmCaps_EnableSCLKDeepSleepForUVD,             /* With HW ECOs, we करोn't need to disable SCLK Deep Sleep क्रम UVD state. */
	PHM_Platक्रमmCaps_EnableMCUHTLinkControl,                /* Enable HT link control by MCU */
	PHM_Platक्रमmCaps_ABM,                                   /* ABM support.*/
	PHM_Platक्रमmCaps_KongThermalPolicy,                     /* A thermal policy specअगरic क्रम Kong */
	PHM_Platक्रमmCaps_SwitchVDDNB,                           /* अगर the users want to चयन VDDNB */
	PHM_Platक्रमmCaps_ULPS,                                  /* support ULPS mode either through ACPI state or ULPS state */
	PHM_Platक्रमmCaps_NativeULPS,                            /* hardware capable of ULPS state (other than through the ACPI state) */
	PHM_Platक्रमmCaps_EnableMVDDControl,                     /* indicates that memory voltage can be controlled */
	PHM_Platक्रमmCaps_ControlVDDCI,                          /* Control VDDCI separately from VDDC. */
	PHM_Platक्रमmCaps_DisableDCODT,                          /* indicates अगर DC ODT apply or not */
	PHM_Platक्रमmCaps_DynamicACTiming,                       /* अगर the SMC dynamically re-programs MC SEQ रेजिस्टर values */
	PHM_Platक्रमmCaps_EnableThermalIntByGPIO,                /* enable throttle control through GPIO */
	PHM_Platक्रमmCaps_BootStateOnAlert,                      /* Go to boot state on alerts, e.g. on an AC->DC transition. */
	PHM_Platक्रमmCaps_DontWaitForVBlankOnAlert,              /* Do NOT रुको क्रम VBLANK during an alert (e.g. AC->DC transition). */
	PHM_Platक्रमmCaps_Force3DClockSupport,                   /* indicates अगर the platक्रमm supports क्रमce 3D घड़ी. */
	PHM_Platक्रमmCaps_MicrocodeFanControl,                   /* Fan is controlled by the SMC microcode. */
	PHM_Platक्रमmCaps_AdjustUVDPriorityForSP,
	PHM_Platक्रमmCaps_DisableLightSleep,                     /* Light sleep क्रम evergreen family. */
	PHM_Platक्रमmCaps_DisableMCLS,                           /* MC Light sleep */
	PHM_Platक्रमmCaps_RegulatorHot,                          /* Enable throttling on 'regulator hot' events. */
	PHM_Platक्रमmCaps_BACO,                                  /* Support Bus Alive Chip Off mode */
	PHM_Platक्रमmCaps_DisableDPM,                            /* Disable DPM, supported from Llano */
	PHM_Platक्रमmCaps_DynamicM3Arbiter,                      /* support dynamically change m3 arbitor parameters */
	PHM_Platक्रमmCaps_SclkDeepSleep,                         /* support sclk deep sleep */
	PHM_Platक्रमmCaps_DynamicPatchPowerState,                /* this ASIC supports to patch घातer state dynamically */
	PHM_Platक्रमmCaps_ThermalAutoThrottling,                 /* enabling स्वतः thermal throttling, */
	PHM_Platक्रमmCaps_SumoThermalPolicy,                     /* A thermal policy specअगरic क्रम Sumo */
	PHM_Platक्रमmCaps_PCIEPerक्रमmanceRequest,                /* support to change RC voltage */
	PHM_Platक्रमmCaps_BLControlledByGPU,                     /* support varibright */
	PHM_Platक्रमmCaps_PowerContainment,                      /* support DPM2 घातer containment (AKA TDP clamping) */
	PHM_Platक्रमmCaps_SQRamping,                             /* support DPM2 SQ घातer throttle */
	PHM_Platक्रमmCaps_CAC,                                   /* support Capacitance * Activity घातer estimation */
	PHM_Platक्रमmCaps_NIChipsets,                            /* Northern Island and beyond chipsets */
	PHM_Platक्रमmCaps_TrinityChipsets,                       /* Trinity chipset */
	PHM_Platक्रमmCaps_EvergreenChipsets,                     /* Evergreen family chipset */
	PHM_Platक्रमmCaps_PowerControl,                          /* Cayman and beyond chipsets */
	PHM_Platक्रमmCaps_DisableLSClockGating,                  /* to disable Light Sleep control क्रम HDP memories */
	PHM_Platक्रमmCaps_BoostState,                            /* this ASIC supports boost state */
	PHM_Platक्रमmCaps_UserMaxClockForMultiDisplays,          /* indicates अगर max memory घड़ी is used क्रम all status when multiple displays are connected */
	PHM_Platक्रमmCaps_RegWriteDelay,                         /* indicates अगर back to back reg ग_लिखो delay is required */
	PHM_Platक्रमmCaps_NonABMSupportInPPLib,                  /* ABM is not supported in PPLIB, (moved from PPLIB to DAL) */
	PHM_Platक्रमmCaps_GFXDynamicMGPowerGating,               /* Enable Dynamic MG PowerGating on Trinity */
	PHM_Platक्रमmCaps_DisableSMUUVDHandshake,                /* Disable SMU UVD Handshake */
	PHM_Platक्रमmCaps_DTE,                                   /* Support Digital Temperature Estimation */
	PHM_Platक्रमmCaps_W5100Specअगरc_SmuSkipMsgDTE,            /* This is क्रम the feature requested by David B., and Tonny W.*/
	PHM_Platक्रमmCaps_UVDPowerGating,                        /* enable UVD घातer gating, supported from Llano */
	PHM_Platक्रमmCaps_UVDDynamicPowerGating,                 /* enable UVD Dynamic घातer gating, supported from UVD5 */
	PHM_Platक्रमmCaps_VCEPowerGating,                        /* Enable VCE घातer gating, supported क्रम TN and later ASICs */
	PHM_Platक्रमmCaps_SamuPowerGating,                       /* Enable SAMU घातer gating, supported क्रम KV and later ASICs */
	PHM_Platक्रमmCaps_UVDDPM,                                /* UVD घड़ी DPM */
	PHM_Platक्रमmCaps_VCEDPM,                                /* VCE घड़ी DPM */
	PHM_Platक्रमmCaps_SamuDPM,                               /* SAMU घड़ी DPM */
	PHM_Platक्रमmCaps_AcpDPM,                                /* ACP घड़ी DPM */
	PHM_Platक्रमmCaps_SclkDeepSleepAboveLow,                 /* Enable SCLK Deep Sleep on all DPM states */
	PHM_Platक्रमmCaps_DynamicUVDState,                       /* Dynamic UVD State */
	PHM_Platक्रमmCaps_WantSAMClkWithDummyBackEnd,            /* Set SAM Clk With Dummy Back End */
	PHM_Platक्रमmCaps_WantUVDClkWithDummyBackEnd,            /* Set UVD Clk With Dummy Back End */
	PHM_Platक्रमmCaps_WantVCEClkWithDummyBackEnd,            /* Set VCE Clk With Dummy Back End */
	PHM_Platक्रमmCaps_WantACPClkWithDummyBackEnd,            /* Set SAM Clk With Dummy Back End */
	PHM_Platक्रमmCaps_OD6inACSupport,                        /* indicates that the ASIC/back end supports OD6 */
	PHM_Platक्रमmCaps_OD6inDCSupport,                        /* indicates that the ASIC/back end supports OD6 in DC */
	PHM_Platक्रमmCaps_EnablePlatक्रमmPowerManagement,         /* indicates that Platक्रमm Power Management feature is supported */
	PHM_Platक्रमmCaps_SurpriseRemoval,                       /* indicates that surprise removal feature is requested */
	PHM_Platक्रमmCaps_NewCACVoltage,                         /* indicates new CAC voltage table support */
	PHM_Platक्रमmCaps_DiDtSupport,                           /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_DBRamping,                             /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_TDRamping,                             /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_TCPRamping,                            /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_DBRRamping,                            /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_DiDtEDCEnable,                         /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_GCEDC,                                 /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_PSM,                                   /* क्रम dI/dT feature */
	PHM_Platक्रमmCaps_EnableSMU7ThermalManagement,           /* SMC will manage thermal events */
	PHM_Platक्रमmCaps_FPS,                                   /* FPS support */
	PHM_Platक्रमmCaps_ACP,                                   /* ACP support */
	PHM_Platक्रमmCaps_SclkThrottleLowNotअगरication,           /* SCLK Throttle Low Notअगरication */
	PHM_Platक्रमmCaps_XDMAEnabled,                           /* XDMA engine is enabled */
	PHM_Platक्रमmCaps_UseDummyBackEnd,                       /* use dummy back end */
	PHM_Platक्रमmCaps_EnableDFSBypass,                       /* Enable DFS bypass */
	PHM_Platक्रमmCaps_VddNBDirectRequest,
	PHM_Platक्रमmCaps_PauseMMSessions,
	PHM_Platक्रमmCaps_UnTabledHardwareInterface,             /* Tableless/direct call hardware पूर्णांकerface क्रम CI and newer ASICs */
	PHM_Platक्रमmCaps_SMU7,                                  /* indicates that vpuRecoveryBegin without SMU shutकरोwn */
	PHM_Platक्रमmCaps_RevertGPIO5Polarity,                   /* indicates revert GPIO5 plarity table support */
	PHM_Platक्रमmCaps_Thermal2GPIO17,                        /* indicates thermal2GPIO17 table support */
	PHM_Platक्रमmCaps_ThermalOutGPIO,                        /* indicates ThermalOutGPIO support, pin number is asचिन्हित by VBIOS */
	PHM_Platक्रमmCaps_DisableMclkSwitchingForFrameLock,      /* Disable memory घड़ी चयन during Framelock */
	PHM_Platक्रमmCaps_ForceMclkHigh,                         /* Disable memory घड़ी चयनing by क्रमcing memory घड़ी high */
	PHM_Platक्रमmCaps_VRHotGPIOConfigurable,                 /* indicates VR_HOT GPIO configurable */
	PHM_Platक्रमmCaps_TempInversion,                         /* enable Temp Inversion feature */
	PHM_Platक्रमmCaps_IOIC3,
	PHM_Platक्रमmCaps_ConnectedStandby,
	PHM_Platक्रमmCaps_EVV,
	PHM_Platक्रमmCaps_EnableLongIdleBACOSupport,
	PHM_Platक्रमmCaps_CombinePCCWithThermalSignal,
	PHM_Platक्रमmCaps_DisableUsingActualTemperatureForPowerCalc,
	PHM_Platक्रमmCaps_StablePState,
	PHM_Platक्रमmCaps_OD6PlusinACSupport,
	PHM_Platक्रमmCaps_OD6PlusinDCSupport,
	PHM_Platक्रमmCaps_ODThermalLimitUnlock,
	PHM_Platक्रमmCaps_ReducePowerLimit,
	PHM_Platक्रमmCaps_ODFuzzyFanControlSupport,
	PHM_Platक्रमmCaps_GeminiRegulatorFanControlSupport,
	PHM_Platक्रमmCaps_ControlVDDGFX,
	PHM_Platक्रमmCaps_BBBSupported,
	PHM_Platक्रमmCaps_DisableVoltageIsland,
	PHM_Platक्रमmCaps_FanSpeedInTableIsRPM,
	PHM_Platक्रमmCaps_GFXClockGatingManagedInCAIL,
	PHM_Platक्रमmCaps_IcelandULPSSWWorkAround,
	PHM_Platक्रमmCaps_FPSEnhancement,
	PHM_Platक्रमmCaps_LoadPostProductionFirmware,
	PHM_Platक्रमmCaps_VpuRecoveryInProgress,
	PHM_Platक्रमmCaps_Falcon_QuickTransition,
	PHM_Platक्रमmCaps_AVFS,
	PHM_Platक्रमmCaps_ClockStretcher,
	PHM_Platक्रमmCaps_TablelessHardwareInterface,
	PHM_Platक्रमmCaps_EnableDriverEVV,
	PHM_Platक्रमmCaps_SPLLShutकरोwnSupport,
	PHM_Platक्रमmCaps_VirtualBatteryState,
	PHM_Platक्रमmCaps_IgnoreForceHighClockRequestsInAPUs,
	PHM_Platक्रमmCaps_DisableMclkSwitchForVR,
	PHM_Platक्रमmCaps_SMU8,
	PHM_Platक्रमmCaps_VRHotPolarityHigh,
	PHM_Platक्रमmCaps_IPS_UlpsExclusive,
	PHM_Platक्रमmCaps_SMCtoPPLIBAcdcGpioScheme,
	PHM_Platक्रमmCaps_GeminiAsymmetricPower,
	PHM_Platक्रमmCaps_OCLPowerOptimization,
	PHM_Platक्रमmCaps_MaxPCIEBandWidth,
	PHM_Platक्रमmCaps_PerfPerWattOptimizationSupport,
	PHM_Platक्रमmCaps_UVDClientMCTuning,
	PHM_Platक्रमmCaps_ODNinACSupport,
	PHM_Platक्रमmCaps_ODNinDCSupport,
	PHM_Platक्रमmCaps_OD8inACSupport,
	PHM_Platक्रमmCaps_OD8inDCSupport,
	PHM_Platक्रमmCaps_UMDPState,
	PHM_Platक्रमmCaps_AutoWatपंचांगanSupport,
	PHM_Platक्रमmCaps_AutoWatपंचांगanEnable_CCCState,
	PHM_Platक्रमmCaps_FreeSyncActive,
	PHM_Platक्रमmCaps_EnableShaकरोwPstate,
	PHM_Platक्रमmCaps_customThermalManagement,
	PHM_Platक्रमmCaps_अटलFanControl,
	PHM_Platक्रमmCaps_Virtual_System,
	PHM_Platक्रमmCaps_LowestUclkReservedForUlv,
	PHM_Platक्रमmCaps_EnableBoostState,
	PHM_Platक्रमmCaps_AVFSSupport,
	PHM_Platक्रमmCaps_ThermalPolicyDelay,
	PHM_Platक्रमmCaps_CustomFanControlSupport,
	PHM_Platक्रमmCaps_BAMACO,
	PHM_Platक्रमmCaps_Max
पूर्ण;

#घोषणा PHM_MAX_NUM_CAPS_BITS_PER_FIELD (माप(uपूर्णांक32_t)*8)

/* Number of uपूर्णांक32_t entries used by CAPS table */
#घोषणा PHM_MAX_NUM_CAPS_ULONG_ENTRIES \
	((PHM_Platक्रमmCaps_Max + ((PHM_MAX_NUM_CAPS_BITS_PER_FIELD) - 1)) / (PHM_MAX_NUM_CAPS_BITS_PER_FIELD))

काष्ठा pp_hw_descriptor अणु
	uपूर्णांक32_t hw_caps[PHM_MAX_NUM_CAPS_ULONG_ENTRIES];
पूर्ण;

क्रमागत PHM_Perक्रमmanceLevelDesignation अणु
	PHM_Perक्रमmanceLevelDesignation_Activity,
	PHM_Perक्रमmanceLevelDesignation_PowerContainment
पूर्ण;

प्रकार क्रमागत PHM_Perक्रमmanceLevelDesignation PHM_Perक्रमmanceLevelDesignation;

काष्ठा PHM_Perक्रमmanceLevel अणु
    uपूर्णांक32_t    coreClock;
    uपूर्णांक32_t    memory_घड़ी;
    uपूर्णांक32_t  vddc;
    uपूर्णांक32_t  vddci;
    uपूर्णांक32_t    nonLocalMemoryFreq;
    uपूर्णांक32_t nonLocalMemoryWidth;
पूर्ण;

प्रकार काष्ठा PHM_Perक्रमmanceLevel PHM_Perक्रमmanceLevel;

/* Function क्रम setting a platक्रमm cap */
अटल अंतरभूत व्योम phm_cap_set(uपूर्णांक32_t *caps,
			क्रमागत phm_platक्रमm_caps c)
अणु
	caps[c / PHM_MAX_NUM_CAPS_BITS_PER_FIELD] |= (1UL <<
			     (c & (PHM_MAX_NUM_CAPS_BITS_PER_FIELD - 1)));
पूर्ण

अटल अंतरभूत व्योम phm_cap_unset(uपूर्णांक32_t *caps,
			क्रमागत phm_platक्रमm_caps c)
अणु
	caps[c / PHM_MAX_NUM_CAPS_BITS_PER_FIELD] &= ~(1UL << (c & (PHM_MAX_NUM_CAPS_BITS_PER_FIELD - 1)));
पूर्ण

अटल अंतरभूत bool phm_cap_enabled(स्थिर uपूर्णांक32_t *caps, क्रमागत phm_platक्रमm_caps c)
अणु
	वापस (0 != (caps[c / PHM_MAX_NUM_CAPS_BITS_PER_FIELD] &
		  (1UL << (c & (PHM_MAX_NUM_CAPS_BITS_PER_FIELD - 1)))));
पूर्ण

#घोषणा PP_CAP(c) phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, (c))

#घोषणा PP_PCIEGenInvalid  0xffff
क्रमागत PP_PCIEGen अणु
    PP_PCIEGen1 = 0,                /* PCIE 1.0 - Transfer rate of 2.5 GT/s */
    PP_PCIEGen2,                    /*PCIE 2.0 - Transfer rate of 5.0 GT/s */
    PP_PCIEGen3                     /*PCIE 3.0 - Transfer rate of 8.0 GT/s */
पूर्ण;

प्रकार क्रमागत PP_PCIEGen PP_PCIEGen;

#घोषणा PP_Min_PCIEGen     PP_PCIEGen1
#घोषणा PP_Max_PCIEGen     PP_PCIEGen3
#घोषणा PP_Min_PCIELane    1
#घोषणा PP_Max_PCIELane    16

क्रमागत phm_घड़ी_Type अणु
	PHM_DispClock = 1,
	PHM_SClock,
	PHM_MemClock
पूर्ण;

#घोषणा MAX_NUM_CLOCKS 16

काष्ठा PP_Clocks अणु
	uपूर्णांक32_t engineClock;
	uपूर्णांक32_t memoryClock;
	uपूर्णांक32_t BusBandwidth;
	uपूर्णांक32_t engineClockInSR;
	uपूर्णांक32_t dcefClock;
	uपूर्णांक32_t dcefClockInSR;
पूर्ण;

काष्ठा pp_घड़ी_info अणु
	uपूर्णांक32_t min_mem_clk;
	uपूर्णांक32_t max_mem_clk;
	uपूर्णांक32_t min_eng_clk;
	uपूर्णांक32_t max_eng_clk;
	uपूर्णांक32_t min_bus_bandwidth;
	uपूर्णांक32_t max_bus_bandwidth;
पूर्ण;

काष्ठा phm_platक्रमm_descriptor अणु
	uपूर्णांक32_t platक्रमmCaps[PHM_MAX_NUM_CAPS_ULONG_ENTRIES];
	uपूर्णांक32_t vbiosInterruptId;
	काष्ठा PP_Clocks overdriveLimit;
	काष्ठा PP_Clocks घड़ीStep;
	uपूर्णांक32_t hardwareActivityPerक्रमmanceLevels;
	uपूर्णांक32_t minimumClocksReductionPercentage;
	uपूर्णांक32_t minOverdriveVDDC;
	uपूर्णांक32_t maxOverdriveVDDC;
	uपूर्णांक32_t overdriveVDDCStep;
	uपूर्णांक32_t hardwarePerक्रमmanceLevels;
	uपूर्णांक16_t घातerBudget;
	uपूर्णांक32_t TDPLimit;
	uपूर्णांक32_t nearTDPLimit;
	uपूर्णांक32_t nearTDPLimitAdjusted;
	uपूर्णांक32_t SQRampingThreshold;
	uपूर्णांक32_t CACLeakage;
	uपूर्णांक16_t TDPODLimit;
	uपूर्णांक32_t TDPAdjusपंचांगent;
	bool TDPAdjusपंचांगentPolarity;
	uपूर्णांक16_t LoadLineSlope;
	uपूर्णांक32_t  VidMinLimit;
	uपूर्णांक32_t  VidMaxLimit;
	uपूर्णांक32_t  VidStep;
	uपूर्णांक32_t  VidAdjusपंचांगent;
	bool VidAdjusपंचांगentPolarity;
पूर्ण;

काष्ठा phm_घड़ीs अणु
	uपूर्णांक32_t num_of_entries;
	uपूर्णांक32_t घड़ी[MAX_NUM_CLOCKS];
पूर्ण;

#घोषणा DPMTABLE_OD_UPDATE_SCLK     0x00000001
#घोषणा DPMTABLE_OD_UPDATE_MCLK     0x00000002
#घोषणा DPMTABLE_UPDATE_SCLK        0x00000004
#घोषणा DPMTABLE_UPDATE_MCLK        0x00000008
#घोषणा DPMTABLE_OD_UPDATE_VDDC     0x00000010
#घोषणा DPMTABLE_UPDATE_SOCCLK      0x00000020

काष्ठा phm_odn_perक्रमmance_level अणु
	uपूर्णांक32_t घड़ी;
	uपूर्णांक32_t vddc;
	bool enabled;
पूर्ण;

काष्ठा phm_odn_घड़ी_levels अणु
	uपूर्णांक32_t size;
	uपूर्णांक32_t options;
	uपूर्णांक32_t flags;
	uपूर्णांक32_t num_of_pl;
	/* variable-sized array, specअगरy by num_of_pl. */
	काष्ठा phm_odn_perक्रमmance_level entries[8];
पूर्ण;

बाह्य पूर्णांक phm_disable_घड़ी_घातer_gatings(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_घातerकरोwn_uvd(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_setup_asic(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_enable_dynamic_state_management(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_disable_dynamic_state_management(काष्ठा pp_hwmgr *hwmgr);
बाह्य bool phm_is_hw_access_blocked(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_block_hw_access(काष्ठा pp_hwmgr *hwmgr, bool block);
बाह्य पूर्णांक phm_set_घातer_state(काष्ठा pp_hwmgr *hwmgr,
		    स्थिर काष्ठा pp_hw_घातer_state *pcurrent_state,
		 स्थिर काष्ठा pp_hw_घातer_state *pnew_घातer_state);

बाह्य पूर्णांक phm_apply_state_adjust_rules(काष्ठा pp_hwmgr *hwmgr,
				   काष्ठा pp_घातer_state *adjusted_ps,
			     स्थिर काष्ठा pp_घातer_state *current_ps);

बाह्य पूर्णांक phm_apply_घड़ी_adjust_rules(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक phm_क्रमce_dpm_levels(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_dpm_क्रमced_level level);
बाह्य पूर्णांक phm_pre_display_configuration_changed(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_display_configuration_changed(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_notअगरy_smc_display_config_after_ps_adjusपंचांगent(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_रेजिस्टर_irq_handlers(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_start_thermal_controller(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक phm_stop_thermal_controller(काष्ठा pp_hwmgr *hwmgr);
बाह्य bool phm_check_smc_update_required_क्रम_display_configuration(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक phm_check_states_equal(काष्ठा pp_hwmgr *hwmgr,
				 स्थिर काष्ठा pp_hw_घातer_state *pstate1,
				 स्थिर काष्ठा pp_hw_घातer_state *pstate2,
				 bool *equal);

बाह्य पूर्णांक phm_store_dal_configuration_data(काष्ठा pp_hwmgr *hwmgr,
		स्थिर काष्ठा amd_pp_display_configuration *display_config);

बाह्य पूर्णांक phm_get_dal_घातer_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा amd_pp_simple_घड़ी_info *info);

बाह्य पूर्णांक phm_set_cpu_घातer_state(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक phm_घातer_करोwn_asic(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक phm_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level);

बाह्य पूर्णांक phm_get_घड़ी_info(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
			काष्ठा pp_घड़ी_info *pघड़ी_info,
			PHM_Perक्रमmanceLevelDesignation designation);

बाह्य पूर्णांक phm_get_current_shallow_sleep_घड़ीs(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state, काष्ठा pp_घड़ी_info *घड़ी_info);

बाह्य पूर्णांक phm_get_घड़ी_by_type(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_pp_घड़ी_प्रकारype type, काष्ठा amd_pp_घड़ीs *घड़ीs);

बाह्य पूर्णांक phm_get_घड़ी_by_type_with_latency(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs);
बाह्य पूर्णांक phm_get_घड़ी_by_type_with_voltage(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs);
बाह्य पूर्णांक phm_set_watermarks_क्रम_घड़ीs_ranges(काष्ठा pp_hwmgr *hwmgr,
						व्योम *घड़ी_ranges);
बाह्य पूर्णांक phm_display_घड़ी_voltage_request(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_display_घड़ी_request *घड़ी);

बाह्य पूर्णांक phm_get_max_high_घड़ीs(काष्ठा pp_hwmgr *hwmgr, काष्ठा amd_pp_simple_घड़ी_info *घड़ीs);
बाह्य पूर्णांक phm_disable_smc_firmware_ctf(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक phm_set_active_display_count(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t count);

#पूर्ण_अगर /* _HARDWARE_MANAGER_H_ */

