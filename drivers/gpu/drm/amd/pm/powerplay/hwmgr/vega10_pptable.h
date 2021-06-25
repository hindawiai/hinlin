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
#अगर_अघोषित _VEGA10_PPTABLE_H_
#घोषणा _VEGA10_PPTABLE_H_

#आशय pack(push, 1)

#घोषणा ATOM_VEGA10_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK 0x0f
#घोषणा ATOM_VEGA10_PP_FANPARAMETERS_NOFAN                                 0x80

#घोषणा ATOM_VEGA10_PP_THERMALCONTROLLER_NONE      0
#घोषणा ATOM_VEGA10_PP_THERMALCONTROLLER_LM96163   17
#घोषणा ATOM_VEGA10_PP_THERMALCONTROLLER_VEGA10    24

#घोषणा ATOM_VEGA10_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL   0x89
#घोषणा ATOM_VEGA10_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL   0x8D

#घोषणा ATOM_VEGA10_PP_PLATFORM_CAP_POWERPLAY                   0x1
#घोषणा ATOM_VEGA10_PP_PLATFORM_CAP_SBIOSPOWERSOURCE            0x2
#घोषणा ATOM_VEGA10_PP_PLATFORM_CAP_HARDWAREDC                  0x4
#घोषणा ATOM_VEGA10_PP_PLATFORM_CAP_BACO                        0x8
#घोषणा ATOM_VEGA10_PP_PLATFORM_COMBINE_PCC_WITH_THERMAL_SIGNAL 0x10


/* ATOM_PPLIB_NONCLOCK_INFO::usClassअगरication */
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_MASK               0x0007
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_SHIFT              0
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_NONE               0
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_BATTERY            1
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_BALANCED           3
#घोषणा ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE        5
/* 2, 4, 6, 7 are reserved */

#घोषणा ATOM_PPLIB_CLASSIFICATION_BOOT                  0x0008
#घोषणा ATOM_PPLIB_CLASSIFICATION_THERMAL               0x0010
#घोषणा ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE    0x0020
#घोषणा ATOM_PPLIB_CLASSIFICATION_REST                  0x0040
#घोषणा ATOM_PPLIB_CLASSIFICATION_FORCED                0x0080
#घोषणा ATOM_PPLIB_CLASSIFICATION_ACPI                  0x1000

/* ATOM_PPLIB_NONCLOCK_INFO::usClassअगरication2 */
#घोषणा ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2 0x0001

#घोषणा ATOM_Vega10_DISALLOW_ON_DC                   0x00004000
#घोषणा ATOM_Vega10_ENABLE_VARIBRIGHT                0x00008000

#घोषणा ATOM_Vega10_TABLE_REVISION_VEGA10         8

#घोषणा ATOM_Vega10_VoltageMode_AVFS_Interpolate     0
#घोषणा ATOM_Vega10_VoltageMode_AVFS_WorstCase       1
#घोषणा ATOM_Vega10_VoltageMode_Static               2

प्रकार काष्ठा _ATOM_Vega10_POWERPLAYTABLE अणु
	काष्ठा atom_common_table_header sHeader;
	UCHAR  ucTableRevision;
	USHORT usTableSize;                        /* the size of header काष्ठाure */
	ULONG  ulGoldenPPID;                       /* PPGen use only */
	ULONG  ulGoldenRevision;                   /* PPGen use only */
	USHORT usFormatID;                         /* PPGen use only */
	ULONG  ulPlatक्रमmCaps;                     /* See ATOM_Vega10_CAPS_* */
	ULONG  ulMaxODEngineClock;                 /* For Overdrive. */
	ULONG  ulMaxODMemoryClock;                 /* For Overdrive. */
	USHORT usPowerControlLimit;
	USHORT usUlvVoltageOffset;                 /* in mv units */
	USHORT usUlvSmnclkDid;
	USHORT usUlvMp1clkDid;
	USHORT usUlvGfxclkBypass;
	USHORT usGfxclkSlewRate;
	UCHAR  ucGfxVoltageMode;
	UCHAR  ucSocVoltageMode;
	UCHAR  ucUclkVoltageMode;
	UCHAR  ucUvdVoltageMode;
	UCHAR  ucVceVoltageMode;
	UCHAR  ucMp0VoltageMode;
	UCHAR  ucDcefVoltageMode;
	USHORT usStateArrayOffset;                 /* poपूर्णांकs to ATOM_Vega10_State_Array */
	USHORT usFanTableOffset;                   /* poपूर्णांकs to ATOM_Vega10_Fan_Table */
	USHORT usThermalControllerOffset;          /* poपूर्णांकs to ATOM_Vega10_Thermal_Controller */
	USHORT usSocclkDependencyTableOffset;      /* poपूर्णांकs to ATOM_Vega10_SOCCLK_Dependency_Table */
	USHORT usMclkDependencyTableOffset;        /* poपूर्णांकs to ATOM_Vega10_MCLK_Dependency_Table */
	USHORT usGfxclkDependencyTableOffset;      /* poपूर्णांकs to ATOM_Vega10_GFXCLK_Dependency_Table */
	USHORT usDcefclkDependencyTableOffset;     /* poपूर्णांकs to ATOM_Vega10_DCEFCLK_Dependency_Table */
	USHORT usVddcLookupTableOffset;            /* poपूर्णांकs to ATOM_Vega10_Voltage_Lookup_Table */
	USHORT usVddmemLookupTableOffset;          /* poपूर्णांकs to ATOM_Vega10_Voltage_Lookup_Table */
	USHORT usMMDependencyTableOffset;          /* poपूर्णांकs to ATOM_Vega10_MM_Dependency_Table */
	USHORT usVCEStateTableOffset;              /* poपूर्णांकs to ATOM_Vega10_VCE_State_Table */
	USHORT usReserve;                          /* No PPM Support क्रम Vega10 */
	USHORT usPowerTuneTableOffset;             /* poपूर्णांकs to ATOM_Vega10_PowerTune_Table */
	USHORT usHardLimitTableOffset;             /* poपूर्णांकs to ATOM_Vega10_Hard_Limit_Table */
	USHORT usVddciLookupTableOffset;           /* poपूर्णांकs to ATOM_Vega10_Voltage_Lookup_Table */
	USHORT usPCIETableOffset;                  /* poपूर्णांकs to ATOM_Vega10_PCIE_Table */
	USHORT usPixclkDependencyTableOffset;      /* poपूर्णांकs to ATOM_Vega10_PIXCLK_Dependency_Table */
	USHORT usDispClkDependencyTableOffset;     /* poपूर्णांकs to ATOM_Vega10_DISPCLK_Dependency_Table */
	USHORT usPhyClkDependencyTableOffset;      /* poपूर्णांकs to ATOM_Vega10_PHYCLK_Dependency_Table */
पूर्ण ATOM_Vega10_POWERPLAYTABLE;

प्रकार काष्ठा _ATOM_Vega10_State अणु
	UCHAR  ucSocClockIndexHigh;
	UCHAR  ucSocClockIndexLow;
	UCHAR  ucGfxClockIndexHigh;
	UCHAR  ucGfxClockIndexLow;
	UCHAR  ucMemClockIndexHigh;
	UCHAR  ucMemClockIndexLow;
	USHORT usClassअगरication;
	ULONG  ulCapsAndSettings;
	USHORT usClassअगरication2;
पूर्ण ATOM_Vega10_State;

प्रकार काष्ठा _ATOM_Vega10_State_Array अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;                                         /* Number of entries. */
	ATOM_Vega10_State states[1];                             /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_State_Array;

प्रकार काष्ठा _ATOM_Vega10_CLK_Dependency_Record अणु
	ULONG  ulClk;                                               /* Frequency of Clock */
	UCHAR  ucVddInd;                                            /* Base voltage */
पूर्ण ATOM_Vega10_CLK_Dependency_Record;

प्रकार काष्ठा _ATOM_Vega10_GFXCLK_Dependency_Record अणु
	ULONG  ulClk;                                               /* Clock Frequency */
	UCHAR  ucVddInd;                                            /* SOC_VDD index */
	USHORT usCKSVOffsetandDisable;                              /* Bits 0~30: Voltage offset क्रम CKS, Bit 31: Disable/enable क्रम the GFXCLK level. */
	USHORT usAVFSOffset;                                        /* AVFS Voltage offset */
पूर्ण ATOM_Vega10_GFXCLK_Dependency_Record;

प्रकार काष्ठा _ATOM_Vega10_GFXCLK_Dependency_Record_V2 अणु
	ULONG  ulClk;
	UCHAR  ucVddInd;
	USHORT usCKSVOffsetandDisable;
	USHORT usAVFSOffset;
	UCHAR  ucACGEnable;
	UCHAR  ucReserved[3];
पूर्ण ATOM_Vega10_GFXCLK_Dependency_Record_V2;

प्रकार काष्ठा _ATOM_Vega10_MCLK_Dependency_Record अणु
	ULONG  ulMemClk;                                            /* Clock Frequency */
	UCHAR  ucVddInd;                                            /* SOC_VDD index */
	UCHAR  ucVddMemInd;                                         /* MEM_VDD - only non zero क्रम MCLK record */
	UCHAR  ucVddciInd;                                          /* VDDCI   = only non zero क्रम MCLK record */
पूर्ण ATOM_Vega10_MCLK_Dependency_Record;

प्रकार काष्ठा _ATOM_Vega10_GFXCLK_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;					/* Number of entries. */
	ATOM_Vega10_GFXCLK_Dependency_Record entries[];		/* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_GFXCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_MCLK_Dependency_Table अणु
    UCHAR ucRevId;
    UCHAR ucNumEntries;                                         /* Number of entries. */
    ATOM_Vega10_MCLK_Dependency_Record entries[1];            /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_MCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_SOCCLK_Dependency_Table अणु
    UCHAR ucRevId;
    UCHAR ucNumEntries;                                         /* Number of entries. */
    ATOM_Vega10_CLK_Dependency_Record entries[1];            /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_SOCCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_DCEFCLK_Dependency_Table अणु
    UCHAR ucRevId;
    UCHAR ucNumEntries;                                         /* Number of entries. */
    ATOM_Vega10_CLK_Dependency_Record entries[1];            /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_DCEFCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_PIXCLK_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;                                         /* Number of entries. */
	ATOM_Vega10_CLK_Dependency_Record entries[1];            /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_PIXCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_DISPCLK_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;                                         /* Number of entries.*/
	ATOM_Vega10_CLK_Dependency_Record entries[1];            /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_DISPCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_PHYCLK_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;                                         /* Number of entries. */
	ATOM_Vega10_CLK_Dependency_Record entries[1];            /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_PHYCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_MM_Dependency_Record अणु
    UCHAR  ucVddcInd;                                           /* SOC_VDD voltage */
    ULONG  ulDClk;                                              /* UVD D-घड़ी */
    ULONG  ulVClk;                                              /* UVD V-घड़ी */
    ULONG  ulEClk;                                              /* VCE घड़ी */
    ULONG  ulPSPClk;                                            /* PSP घड़ी */
पूर्ण ATOM_Vega10_MM_Dependency_Record;

प्रकार काष्ठा _ATOM_Vega10_MM_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;                                         /* Number of entries */
	ATOM_Vega10_MM_Dependency_Record entries[1];             /* Dynamically allocate entries */
पूर्ण ATOM_Vega10_MM_Dependency_Table;

प्रकार काष्ठा _ATOM_Vega10_PCIE_Record अणु
	ULONG ulLCLK;                                               /* LClock */
	UCHAR ucPCIEGenSpeed;                                       /* PCIE Speed */
	UCHAR ucPCIELaneWidth;                                      /* PCIE Lane Width */
पूर्ण ATOM_Vega10_PCIE_Record;

प्रकार काष्ठा _ATOM_Vega10_PCIE_Table अणु
	UCHAR  ucRevId;
	UCHAR  ucNumEntries;                                        /* Number of entries */
	ATOM_Vega10_PCIE_Record entries[1];                      /* Dynamically allocate entries. */
पूर्ण ATOM_Vega10_PCIE_Table;

प्रकार काष्ठा _ATOM_Vega10_Voltage_Lookup_Record अणु
	USHORT usVdd;                                               /* Base voltage */
पूर्ण ATOM_Vega10_Voltage_Lookup_Record;

प्रकार काष्ठा _ATOM_Vega10_Voltage_Lookup_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;                                          /* Number of entries */
	ATOM_Vega10_Voltage_Lookup_Record entries[1];             /* Dynamically allocate entries */
पूर्ण ATOM_Vega10_Voltage_Lookup_Table;

प्रकार काष्ठा _ATOM_Vega10_Fan_Table अणु
	UCHAR   ucRevId;                         /* Change this अगर the table क्रमmat changes or version changes so that the other fields are not the same. */
	USHORT  usFanOutputSensitivity;          /* Sensitivity of fan reaction to temepature changes. */
	USHORT  usFanRPMMax;                     /* The शेष value in RPM. */
	USHORT  usThrottlingRPM;
	USHORT  usFanAcousticLimit;              /* Minimum Fan Controller Frequency Acoustic Limit. */
	USHORT  usTargetTemperature;             /* The शेष ideal temperature in Celcius. */
	USHORT  usMinimumPWMLimit;               /* The minimum PWM that the advanced fan controller can set. */
	USHORT  usTargetGfxClk;                   /* The ideal Fan Controller GFXCLK Frequency Acoustic Limit. */
	USHORT  usFanGainEdge;
	USHORT  usFanGainHotspot;
	USHORT  usFanGainLiquid;
	USHORT  usFanGainVrVddc;
	USHORT  usFanGainVrMvdd;
	USHORT  usFanGainPlx;
	USHORT  usFanGainHbm;
	UCHAR   ucEnableZeroRPM;
	USHORT  usFanStopTemperature;
	USHORT  usFanStartTemperature;
पूर्ण ATOM_Vega10_Fan_Table;

प्रकार काष्ठा _ATOM_Vega10_Fan_Table_V2 अणु
	UCHAR   ucRevId;
	USHORT  usFanOutputSensitivity;
	USHORT  usFanAcousticLimitRpm;
	USHORT  usThrottlingRPM;
	USHORT  usTargetTemperature;
	USHORT  usMinimumPWMLimit;
	USHORT  usTargetGfxClk;
	USHORT  usFanGainEdge;
	USHORT  usFanGainHotspot;
	USHORT  usFanGainLiquid;
	USHORT  usFanGainVrVddc;
	USHORT  usFanGainVrMvdd;
	USHORT  usFanGainPlx;
	USHORT  usFanGainHbm;
	UCHAR   ucEnableZeroRPM;
	USHORT  usFanStopTemperature;
	USHORT  usFanStartTemperature;
	UCHAR   ucFanParameters;
	UCHAR   ucFanMinRPM;
	UCHAR   ucFanMaxRPM;
पूर्ण ATOM_Vega10_Fan_Table_V2;

प्रकार काष्ठा _ATOM_Vega10_Fan_Table_V3 अणु
	UCHAR   ucRevId;
	USHORT  usFanOutputSensitivity;
	USHORT  usFanAcousticLimitRpm;
	USHORT  usThrottlingRPM;
	USHORT  usTargetTemperature;
	USHORT  usMinimumPWMLimit;
	USHORT  usTargetGfxClk;
	USHORT  usFanGainEdge;
	USHORT  usFanGainHotspot;
	USHORT  usFanGainLiquid;
	USHORT  usFanGainVrVddc;
	USHORT  usFanGainVrMvdd;
	USHORT  usFanGainPlx;
	USHORT  usFanGainHbm;
	UCHAR   ucEnableZeroRPM;
	USHORT  usFanStopTemperature;
	USHORT  usFanStartTemperature;
	UCHAR   ucFanParameters;
	UCHAR   ucFanMinRPM;
	UCHAR   ucFanMaxRPM;
	USHORT  usMGpuThrottlingRPM;
पूर्ण ATOM_Vega10_Fan_Table_V3;

प्रकार काष्ठा _ATOM_Vega10_Thermal_Controller अणु
	UCHAR ucRevId;
	UCHAR ucType;           /* one of ATOM_VEGA10_PP_THERMALCONTROLLER_*/
	UCHAR ucI2cLine;        /* as पूर्णांकerpreted by DAL I2C */
	UCHAR ucI2cAddress;
	UCHAR ucFanParameters;  /* Fan Control Parameters. */
	UCHAR ucFanMinRPM;      /* Fan Minimum RPM (hundreds) -- क्रम display purposes only.*/
	UCHAR ucFanMaxRPM;      /* Fan Maximum RPM (hundreds) -- क्रम display purposes only.*/
    UCHAR ucFlags;          /* to be defined */
पूर्ण ATOM_Vega10_Thermal_Controller;

प्रकार काष्ठा _ATOM_Vega10_VCE_State_Record
अणु
    UCHAR  ucVCEClockIndex;         /*index पूर्णांकo usVCEDependencyTableOffset of 'ATOM_Vega10_MM_Dependency_Table' type */
    UCHAR  ucFlag;                  /* 2 bits indicates memory p-states */
    UCHAR  ucSCLKIndex;             /* index पूर्णांकo ATOM_Vega10_SCLK_Dependency_Table */
    UCHAR  ucMCLKIndex;             /* index पूर्णांकo ATOM_Vega10_MCLK_Dependency_Table */
पूर्ण ATOM_Vega10_VCE_State_Record;

प्रकार काष्ठा _ATOM_Vega10_VCE_State_Table
अणु
    UCHAR ucRevId;
    UCHAR ucNumEntries;
    ATOM_Vega10_VCE_State_Record entries[1];
पूर्ण ATOM_Vega10_VCE_State_Table;

प्रकार काष्ठा _ATOM_Vega10_PowerTune_Table अणु
	UCHAR  ucRevId;
	USHORT usSocketPowerLimit;
	USHORT usBatteryPowerLimit;
	USHORT usSmallPowerLimit;
	USHORT usTdcLimit;
	USHORT usEdcLimit;
	USHORT usSoftwareShutकरोwnTemp;
	USHORT usTemperatureLimitHotSpot;
	USHORT usTemperatureLimitLiquid1;
	USHORT usTemperatureLimitLiquid2;
	USHORT usTemperatureLimitHBM;
	USHORT usTemperatureLimitVrSoc;
	USHORT usTemperatureLimitVrMem;
	USHORT usTemperatureLimitPlx;
	USHORT usLoadLineResistance;
	UCHAR  ucLiquid1_I2C_address;
	UCHAR  ucLiquid2_I2C_address;
	UCHAR  ucVr_I2C_address;
	UCHAR  ucPlx_I2C_address;
	UCHAR  ucLiquid_I2C_LineSCL;
	UCHAR  ucLiquid_I2C_LineSDA;
	UCHAR  ucVr_I2C_LineSCL;
	UCHAR  ucVr_I2C_LineSDA;
	UCHAR  ucPlx_I2C_LineSCL;
	UCHAR  ucPlx_I2C_LineSDA;
	USHORT usTemperatureLimitTedge;
पूर्ण ATOM_Vega10_PowerTune_Table;

प्रकार काष्ठा _ATOM_Vega10_PowerTune_Table_V2
अणु
	UCHAR  ucRevId;
	USHORT usSocketPowerLimit;
	USHORT usBatteryPowerLimit;
	USHORT usSmallPowerLimit;
	USHORT usTdcLimit;
	USHORT usEdcLimit;
	USHORT usSoftwareShutकरोwnTemp;
	USHORT usTemperatureLimitHotSpot;
	USHORT usTemperatureLimitLiquid1;
	USHORT usTemperatureLimitLiquid2;
	USHORT usTemperatureLimitHBM;
	USHORT usTemperatureLimitVrSoc;
	USHORT usTemperatureLimitVrMem;
	USHORT usTemperatureLimitPlx;
	USHORT usLoadLineResistance;
	UCHAR ucLiquid1_I2C_address;
	UCHAR ucLiquid2_I2C_address;
	UCHAR ucLiquid_I2C_Line;
	UCHAR ucVr_I2C_address;
	UCHAR ucVr_I2C_Line;
	UCHAR ucPlx_I2C_address;
	UCHAR ucPlx_I2C_Line;
	USHORT usTemperatureLimitTedge;
पूर्ण ATOM_Vega10_PowerTune_Table_V2;

प्रकार काष्ठा _ATOM_Vega10_PowerTune_Table_V3
अणु
	UCHAR  ucRevId;
	USHORT usSocketPowerLimit;
	USHORT usBatteryPowerLimit;
	USHORT usSmallPowerLimit;
	USHORT usTdcLimit;
	USHORT usEdcLimit;
	USHORT usSoftwareShutकरोwnTemp;
	USHORT usTemperatureLimitHotSpot;
	USHORT usTemperatureLimitLiquid1;
	USHORT usTemperatureLimitLiquid2;
	USHORT usTemperatureLimitHBM;
	USHORT usTemperatureLimitVrSoc;
	USHORT usTemperatureLimitVrMem;
	USHORT usTemperatureLimitPlx;
	USHORT usLoadLineResistance;
	UCHAR  ucLiquid1_I2C_address;
	UCHAR  ucLiquid2_I2C_address;
	UCHAR  ucLiquid_I2C_Line;
	UCHAR  ucVr_I2C_address;
	UCHAR  ucVr_I2C_Line;
	UCHAR  ucPlx_I2C_address;
	UCHAR  ucPlx_I2C_Line;
	USHORT usTemperatureLimitTedge;
	USHORT usBoostStartTemperature;
	USHORT usBoostStopTemperature;
	ULONG  ulBoostClock;
	ULONG  Reserved[2];
पूर्ण ATOM_Vega10_PowerTune_Table_V3;

प्रकार काष्ठा _ATOM_Vega10_Hard_Limit_Record अणु
    ULONG  ulSOCCLKLimit;
    ULONG  ulGFXCLKLimit;
    ULONG  ulMCLKLimit;
    USHORT usVddcLimit;
    USHORT usVddciLimit;
    USHORT usVddMemLimit;
पूर्ण ATOM_Vega10_Hard_Limit_Record;

प्रकार काष्ठा _ATOM_Vega10_Hard_Limit_Table
अणु
    UCHAR ucRevId;
    UCHAR ucNumEntries;
    ATOM_Vega10_Hard_Limit_Record entries[1];
पूर्ण ATOM_Vega10_Hard_Limit_Table;

प्रकार काष्ठा _Vega10_PPTable_Generic_SubTable_Header
अणु
    UCHAR  ucRevId;
पूर्ण Vega10_PPTable_Generic_SubTable_Header;

#आशय pack(pop)

#पूर्ण_अगर
