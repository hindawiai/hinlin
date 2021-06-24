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

#अगर_अघोषित TONGA_PPTABLE_H
#घोषणा TONGA_PPTABLE_H

/** \पile
 * This is a PowerPlay table header file
 */
#आशय pack(push, 1)

#समावेश "hwmgr.h"

#घोषणा ATOM_TONGA_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK 0x0f
#घोषणा ATOM_TONGA_PP_FANPARAMETERS_NOFAN                                 0x80    /* No fan is connected to this controller. */

#घोषणा ATOM_TONGA_PP_THERMALCONTROLLER_NONE      0
#घोषणा ATOM_TONGA_PP_THERMALCONTROLLER_LM96163   17
#घोषणा ATOM_TONGA_PP_THERMALCONTROLLER_TONGA     21
#घोषणा ATOM_TONGA_PP_THERMALCONTROLLER_FIJI      22

/*
 * Thermal controller 'combo type' to use an बाह्यal controller क्रम Fan control and an पूर्णांकernal controller क्रम thermal.
 * We probably should reserve the bit 0x80 क्रम this use.
 * To keep the number of these types low we should also use the same code क्रम all ASICs (i.e. करो not distinguish RV6xx and RV7xx Internal here).
 * The driver can pick the correct पूर्णांकernal controller based on the ASIC.
 */

#घोषणा ATOM_TONGA_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL   0x89    /* ADT7473 Fan Control + Internal Thermal Controller */
#घोषणा ATOM_TONGA_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL   0x8D    /* EMC2103 Fan Control + Internal Thermal Controller */

/*/* ATOM_TONGA_POWERPLAYTABLE::ulPlatक्रमmCaps */
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_VDDGFX_CONTROL              0x1            /* This cap indicates whether vddgfx will be a separated घातer rail. */
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_POWERPLAY                   0x2            /* This cap indicates whether this is a mobile part and CCC need to show Powerplay page. */
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_SBIOSPOWERSOURCE            0x4            /* This cap indicates whether घातer source notअगरicaiton is करोne by SBIOS directly. */
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_DISABLE_VOLTAGE_ISLAND      0x8            /* Enable the option to overग_लिखो voltage island feature to be disabled, regardless of VddGfx घातer rail support. */
#घोषणा ____RETIRE16____                                0x10
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_HARDWAREDC                 0x20            /* This cap indicates whether घातer source notअगरicaiton is करोne by GPIO directly. */
#घोषणा ____RETIRE64____                                0x40
#घोषणा ____RETIRE128____                               0x80
#घोषणा ____RETIRE256____                              0x100
#घोषणा ____RETIRE512____                              0x200
#घोषणा ____RETIRE1024____                             0x400
#घोषणा ____RETIRE2048____                             0x800
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_MVDD_CONTROL             0x1000            /* This cap indicates dynamic MVDD is required. Uncheck to disable it. */
#घोषणा ____RETIRE2000____                            0x2000
#घोषणा ____RETIRE4000____                            0x4000
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_VDDCI_CONTROL            0x8000            /* This cap indicates dynamic VDDCI is required. Uncheck to disable it. */
#घोषणा ____RETIRE10000____                          0x10000
#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_BACO                    0x20000            /* Enable to indicate the driver supports BACO state. */

#घोषणा ATOM_TONGA_PP_PLATFORM_CAP_OUTPUT_THERMAL2GPIO17         0x100000     /* Enable to indicate the driver supports thermal2GPIO17. */
#घोषणा ATOM_TONGA_PP_PLATFORM_COMBINE_PCC_WITH_THERMAL_SIGNAL  0x1000000     /* Enable to indicate अगर thermal and PCC are sharing the same GPIO */
#घोषणा ATOM_TONGA_PLATFORM_LOAD_POST_PRODUCTION_FIRMWARE       0x2000000

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

#घोषणा ATOM_Tonga_DISALLOW_ON_DC                       0x00004000
#घोषणा ATOM_Tonga_ENABLE_VARIBRIGHT                    0x00008000

#घोषणा ATOM_Tonga_TABLE_REVISION_TONGA                 7

प्रकार काष्ठा _ATOM_Tonga_POWERPLAYTABLE अणु
	ATOM_COMMON_TABLE_HEADER sHeader;

	UCHAR  ucTableRevision;
	USHORT usTableSize;						/*the size of header काष्ठाure */

	ULONG	ulGoldenPPID;
	ULONG	ulGoldenRevision;
	USHORT	usFormatID;

	USHORT	usVoltageTime;					 /*in microseconds */
	ULONG	ulPlatक्रमmCaps;					  /*See ATOM_Tonga_CAPS_* */

	ULONG	ulMaxODEngineClock; 			   /*For Overdrive.  */
	ULONG	ulMaxODMemoryClock; 			   /*For Overdrive. */

	USHORT	usPowerControlLimit;
	USHORT	usUlvVoltageOffset;				  /*in mv units */

	USHORT	usStateArrayOffset;				  /*poपूर्णांकs to ATOM_Tonga_State_Array */
	USHORT	usFanTableOffset;				  /*poपूर्णांकs to ATOM_Tonga_Fan_Table */
	USHORT	usThermalControllerOffset;		   /*poपूर्णांकs to ATOM_Tonga_Thermal_Controller */
	USHORT	usReserv;						   /*CustomThermalPolicy हटाओd क्रम Tonga. Keep this filed as reserved. */

	USHORT	usMclkDependencyTableOffset;	   /*poपूर्णांकs to ATOM_Tonga_MCLK_Dependency_Table */
	USHORT	usSclkDependencyTableOffset;	   /*poपूर्णांकs to ATOM_Tonga_SCLK_Dependency_Table */
	USHORT	usVddcLookupTableOffset;		   /*poपूर्णांकs to ATOM_Tonga_Voltage_Lookup_Table */
	USHORT	usVddgfxLookupTableOffset; 		/*poपूर्णांकs to ATOM_Tonga_Voltage_Lookup_Table */

	USHORT	usMMDependencyTableOffset;		  /*poपूर्णांकs to ATOM_Tonga_MM_Dependency_Table */

	USHORT	usVCEStateTableOffset;			   /*poपूर्णांकs to ATOM_Tonga_VCE_State_Table; */

	USHORT	usPPMTableOffset;				  /*poपूर्णांकs to ATOM_Tonga_PPM_Table */
	USHORT	usPowerTuneTableOffset;			  /*poपूर्णांकs to ATOM_PowerTune_Table */

	USHORT	usHardLimitTableOffset; 		   /*poपूर्णांकs to ATOM_Tonga_Hard_Limit_Table */

	USHORT	usPCIETableOffset;				  /*poपूर्णांकs to ATOM_Tonga_PCIE_Table */

	USHORT	usGPIOTableOffset;				  /*poपूर्णांकs to ATOM_Tonga_GPIO_Table */

	USHORT	usReserved[6];					   /*TODO: modअगरy reserved size to fit काष्ठाure aligning */
पूर्ण ATOM_Tonga_POWERPLAYTABLE;

प्रकार काष्ठा _ATOM_Tonga_State अणु
	UCHAR  ucEngineClockIndexHigh;
	UCHAR  ucEngineClockIndexLow;

	UCHAR  ucMemoryClockIndexHigh;
	UCHAR  ucMemoryClockIndexLow;

	UCHAR  ucPCIEGenLow;
	UCHAR  ucPCIEGenHigh;

	UCHAR  ucPCIELaneLow;
	UCHAR  ucPCIELaneHigh;

	USHORT usClassअगरication;
	ULONG ulCapsAndSettings;
	USHORT usClassअगरication2;
	UCHAR  ucUnused[4];
पूर्ण ATOM_Tonga_State;

प्रकार काष्ठा _ATOM_Tonga_State_Array अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;		/* Number of entries. */
	ATOM_Tonga_State entries[1];	/* Dynamically allocate entries. */
पूर्ण ATOM_Tonga_State_Array;

प्रकार काष्ठा _ATOM_Tonga_MCLK_Dependency_Record अणु
	UCHAR  ucVddcInd;	/* Vddc voltage */
	USHORT usVddci;
	USHORT usVddgfxOffset;	/* Offset relative to Vddc voltage */
	USHORT usMvdd;
	ULONG ulMclk;
	USHORT usReserved;
पूर्ण ATOM_Tonga_MCLK_Dependency_Record;

प्रकार काष्ठा _ATOM_Tonga_MCLK_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries; 										/* Number of entries. */
	ATOM_Tonga_MCLK_Dependency_Record entries[1];				/* Dynamically allocate entries. */
पूर्ण ATOM_Tonga_MCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Tonga_SCLK_Dependency_Record अणु
	UCHAR  ucVddInd;											/* Base voltage */
	USHORT usVddcOffset;										/* Offset relative to base voltage */
	ULONG ulSclk;
	USHORT usEdcCurrent;
	UCHAR  ucReliabilityTemperature;
	UCHAR  ucCKSVOffsetandDisable;							  /* Bits 0~6: Voltage offset क्रम CKS, Bit 7: Disable/enable क्रम the SCLK level. */
पूर्ण ATOM_Tonga_SCLK_Dependency_Record;

प्रकार काष्ठा _ATOM_Tonga_SCLK_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries; 										/* Number of entries. */
	ATOM_Tonga_SCLK_Dependency_Record entries[1];				 /* Dynamically allocate entries. */
पूर्ण ATOM_Tonga_SCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Polaris_SCLK_Dependency_Record अणु
	UCHAR  ucVddInd;											/* Base voltage */
	USHORT usVddcOffset;										/* Offset relative to base voltage */
	ULONG ulSclk;
	USHORT usEdcCurrent;
	UCHAR  ucReliabilityTemperature;
	UCHAR  ucCKSVOffsetandDisable;			/* Bits 0~6: Voltage offset क्रम CKS, Bit 7: Disable/enable क्रम the SCLK level. */
	ULONG  ulSclkOffset;
पूर्ण ATOM_Polaris_SCLK_Dependency_Record;

प्रकार काष्ठा _ATOM_Polaris_SCLK_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;							/* Number of entries. */
	ATOM_Polaris_SCLK_Dependency_Record entries[1];				 /* Dynamically allocate entries. */
पूर्ण ATOM_Polaris_SCLK_Dependency_Table;

प्रकार काष्ठा _ATOM_Tonga_PCIE_Record अणु
	UCHAR ucPCIEGenSpeed;
	UCHAR usPCIELaneWidth;
	UCHAR ucReserved[2];
पूर्ण ATOM_Tonga_PCIE_Record;

प्रकार काष्ठा _ATOM_Tonga_PCIE_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries; 										/* Number of entries. */
	ATOM_Tonga_PCIE_Record entries[1];							/* Dynamically allocate entries. */
पूर्ण ATOM_Tonga_PCIE_Table;

प्रकार काष्ठा _ATOM_Polaris10_PCIE_Record अणु
	UCHAR ucPCIEGenSpeed;
	UCHAR usPCIELaneWidth;
	UCHAR ucReserved[2];
	ULONG ulPCIE_Sclk;
पूर्ण ATOM_Polaris10_PCIE_Record;

प्रकार काष्ठा _ATOM_Polaris10_PCIE_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;                                         /* Number of entries. */
	ATOM_Polaris10_PCIE_Record entries[1];                      /* Dynamically allocate entries. */
पूर्ण ATOM_Polaris10_PCIE_Table;


प्रकार काष्ठा _ATOM_Tonga_MM_Dependency_Record अणु
	UCHAR   ucVddcInd;											 /* VDDC voltage */
	USHORT  usVddgfxOffset;									  /* Offset relative to VDDC voltage */
	ULONG  ulDClk;												/* UVD D-घड़ी */
	ULONG  ulVClk;												/* UVD V-घड़ी */
	ULONG  ulEClk;												/* VCE घड़ी */
	ULONG  ulAClk;												/* ACP घड़ी */
	ULONG  ulSAMUClk;											/* SAMU घड़ी */
पूर्ण ATOM_Tonga_MM_Dependency_Record;

प्रकार काष्ठा _ATOM_Tonga_MM_Dependency_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries; 										/* Number of entries. */
	ATOM_Tonga_MM_Dependency_Record entries[1]; 			   /* Dynamically allocate entries. */
पूर्ण ATOM_Tonga_MM_Dependency_Table;

प्रकार काष्ठा _ATOM_Tonga_Voltage_Lookup_Record अणु
	USHORT usVdd;											   /* Base voltage */
	USHORT usCACLow;
	USHORT usCACMid;
	USHORT usCACHigh;
पूर्ण ATOM_Tonga_Voltage_Lookup_Record;

प्रकार काष्ठा _ATOM_Tonga_Voltage_Lookup_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries; 										/* Number of entries. */
	ATOM_Tonga_Voltage_Lookup_Record entries[1];				/* Dynamically allocate entries. */
पूर्ण ATOM_Tonga_Voltage_Lookup_Table;

प्रकार काष्ठा _ATOM_Tonga_Fan_Table अणु
	UCHAR   ucRevId;						 /* Change this अगर the table क्रमmat changes or version changes so that the other fields are not the same. */
	UCHAR   ucTHyst;						 /* Temperature hysteresis. Integer. */
	USHORT  usTMin; 						 /* The temperature, in 0.01 centigrades, below which we just run at a minimal PWM. */
	USHORT  usTMed; 						 /* The middle temperature where we change slopes. */
	USHORT  usTHigh;						 /* The high poपूर्णांक above TMed क्रम adjusting the second slope. */
	USHORT  usPWMMin;						 /* The minimum PWM value in percent (0.01% increments). */
	USHORT  usPWMMed;						 /* The PWM value (in percent) at TMed. */
	USHORT  usPWMHigh;						 /* The PWM value at THigh. */
	USHORT  usTMax; 						 /* The max temperature */
	UCHAR   ucFanControlMode;				  /* Legacy or Fuzzy Fan mode */
	USHORT  usFanPWMMax;					  /* Maximum allowed fan घातer in percent */
	USHORT  usFanOutputSensitivity;		  /* Sensitivity of fan reaction to temepature changes */
	USHORT  usFanRPMMax;					  /* The शेष value in RPM */
	ULONG  ulMinFanSCLKAcousticLimit;	   /* Minimum Fan Controller SCLK Frequency Acoustic Limit. */
	UCHAR   ucTargetTemperature;			 /* Advanced fan controller target temperature. */
	UCHAR   ucMinimumPWMLimit; 			  /* The minimum PWM that the advanced fan controller can set.	This should be set to the highest PWM that will run the fan at its lowest RPM. */
	USHORT  usReserved;
पूर्ण ATOM_Tonga_Fan_Table;

प्रकार काष्ठा _ATOM_Fiji_Fan_Table अणु
	UCHAR   ucRevId;						 /* Change this अगर the table क्रमmat changes or version changes so that the other fields are not the same. */
	UCHAR   ucTHyst;						 /* Temperature hysteresis. Integer. */
	USHORT  usTMin; 						 /* The temperature, in 0.01 centigrades, below which we just run at a minimal PWM. */
	USHORT  usTMed; 						 /* The middle temperature where we change slopes. */
	USHORT  usTHigh;						 /* The high poपूर्णांक above TMed क्रम adjusting the second slope. */
	USHORT  usPWMMin;						 /* The minimum PWM value in percent (0.01% increments). */
	USHORT  usPWMMed;						 /* The PWM value (in percent) at TMed. */
	USHORT  usPWMHigh;						 /* The PWM value at THigh. */
	USHORT  usTMax; 						 /* The max temperature */
	UCHAR   ucFanControlMode;				  /* Legacy or Fuzzy Fan mode */
	USHORT  usFanPWMMax;					  /* Maximum allowed fan घातer in percent */
	USHORT  usFanOutputSensitivity;		  /* Sensitivity of fan reaction to temepature changes */
	USHORT  usFanRPMMax;					  /* The शेष value in RPM */
	ULONG  ulMinFanSCLKAcousticLimit;		/* Minimum Fan Controller SCLK Frequency Acoustic Limit. */
	UCHAR   ucTargetTemperature;			 /* Advanced fan controller target temperature. */
	UCHAR   ucMinimumPWMLimit; 			  /* The minimum PWM that the advanced fan controller can set.	This should be set to the highest PWM that will run the fan at its lowest RPM. */
	USHORT  usFanGainEdge;
	USHORT  usFanGainHotspot;
	USHORT  usFanGainLiquid;
	USHORT  usFanGainVrVddc;
	USHORT  usFanGainVrMvdd;
	USHORT  usFanGainPlx;
	USHORT  usFanGainHbm;
	USHORT  usReserved;
पूर्ण ATOM_Fiji_Fan_Table;

प्रकार काष्ठा _ATOM_Polaris_Fan_Table अणु
	UCHAR   ucRevId;						 /* Change this अगर the table क्रमmat changes or version changes so that the other fields are not the same. */
	UCHAR   ucTHyst;						 /* Temperature hysteresis. Integer. */
	USHORT  usTMin; 						 /* The temperature, in 0.01 centigrades, below which we just run at a minimal PWM. */
	USHORT  usTMed; 						 /* The middle temperature where we change slopes. */
	USHORT  usTHigh;						 /* The high poपूर्णांक above TMed क्रम adjusting the second slope. */
	USHORT  usPWMMin;						 /* The minimum PWM value in percent (0.01% increments). */
	USHORT  usPWMMed;						 /* The PWM value (in percent) at TMed. */
	USHORT  usPWMHigh;						 /* The PWM value at THigh. */
	USHORT  usTMax; 						 /* The max temperature */
	UCHAR   ucFanControlMode;				  /* Legacy or Fuzzy Fan mode */
	USHORT  usFanPWMMax;					  /* Maximum allowed fan घातer in percent */
	USHORT  usFanOutputSensitivity;		  /* Sensitivity of fan reaction to temepature changes */
	USHORT  usFanRPMMax;					  /* The शेष value in RPM */
	ULONG  ulMinFanSCLKAcousticLimit;		/* Minimum Fan Controller SCLK Frequency Acoustic Limit. */
	UCHAR   ucTargetTemperature;			 /* Advanced fan controller target temperature. */
	UCHAR   ucMinimumPWMLimit; 			  /* The minimum PWM that the advanced fan controller can set.	This should be set to the highest PWM that will run the fan at its lowest RPM. */
	USHORT  usFanGainEdge;
	USHORT  usFanGainHotspot;
	USHORT  usFanGainLiquid;
	USHORT  usFanGainVrVddc;
	USHORT  usFanGainVrMvdd;
	USHORT  usFanGainPlx;
	USHORT  usFanGainHbm;
	UCHAR   ucEnableZeroRPM;
	UCHAR   ucFanStopTemperature;
	UCHAR   ucFanStartTemperature;
	USHORT  usReserved;
पूर्ण ATOM_Polaris_Fan_Table;

प्रकार काष्ठा _ATOM_Tonga_Thermal_Controller अणु
	UCHAR ucRevId;
	UCHAR ucType;		   /* one of ATOM_TONGA_PP_THERMALCONTROLLER_* */
	UCHAR ucI2cLine;		/* as पूर्णांकerpreted by DAL I2C */
	UCHAR ucI2cAddress;
	UCHAR ucFanParameters;	/* Fan Control Parameters. */
	UCHAR ucFanMinRPM; 	 /* Fan Minimum RPM (hundreds) -- क्रम display purposes only. */
	UCHAR ucFanMaxRPM; 	 /* Fan Maximum RPM (hundreds) -- क्रम display purposes only. */
	UCHAR ucReserved;
	UCHAR ucFlags;		   /* to be defined */
पूर्ण ATOM_Tonga_Thermal_Controller;

प्रकार काष्ठा _ATOM_Tonga_VCE_State_Record अणु
	UCHAR  ucVCEClockIndex;	/*index पूर्णांकo usVCEDependencyTableOffset of 'ATOM_Tonga_MM_Dependency_Table' type */
	UCHAR  ucFlag;		/* 2 bits indicates memory p-states */
	UCHAR  ucSCLKIndex;		/*index पूर्णांकo ATOM_Tonga_SCLK_Dependency_Table */
	UCHAR  ucMCLKIndex;		/*index पूर्णांकo ATOM_Tonga_MCLK_Dependency_Table */
पूर्ण ATOM_Tonga_VCE_State_Record;

प्रकार काष्ठा _ATOM_Tonga_VCE_State_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;
	ATOM_Tonga_VCE_State_Record entries[1];
पूर्ण ATOM_Tonga_VCE_State_Table;

प्रकार काष्ठा _ATOM_Tonga_PowerTune_Table अणु
	UCHAR  ucRevId;
	USHORT usTDP;
	USHORT usConfigurableTDP;
	USHORT usTDC;
	USHORT usBatteryPowerLimit;
	USHORT usSmallPowerLimit;
	USHORT usLowCACLeakage;
	USHORT usHighCACLeakage;
	USHORT usMaximumPowerDeliveryLimit;
	USHORT usTjMax;
	USHORT usPowerTuneDataSetID;
	USHORT usEDCLimit;
	USHORT usSoftwareShutकरोwnTemp;
	USHORT usClockStretchAmount;
	USHORT usReserve[2];
पूर्ण ATOM_Tonga_PowerTune_Table;

प्रकार काष्ठा _ATOM_Fiji_PowerTune_Table अणु
	UCHAR  ucRevId;
	USHORT usTDP;
	USHORT usConfigurableTDP;
	USHORT usTDC;
	USHORT usBatteryPowerLimit;
	USHORT usSmallPowerLimit;
	USHORT usLowCACLeakage;
	USHORT usHighCACLeakage;
	USHORT usMaximumPowerDeliveryLimit;
	USHORT usTjMax;  /* For Fiji, this is also usTemperatureLimitEdge; */
	USHORT usPowerTuneDataSetID;
	USHORT usEDCLimit;
	USHORT usSoftwareShutकरोwnTemp;
	USHORT usClockStretchAmount;
	USHORT usTemperatureLimitHotspot;  /*The following are added क्रम Fiji */
	USHORT usTemperatureLimitLiquid1;
	USHORT usTemperatureLimitLiquid2;
	USHORT usTemperatureLimitVrVddc;
	USHORT usTemperatureLimitVrMvdd;
	USHORT usTemperatureLimitPlx;
	UCHAR  ucLiquid1_I2C_address;  /*Liquid */
	UCHAR  ucLiquid2_I2C_address;
	UCHAR  ucLiquid_I2C_Line;
	UCHAR  ucVr_I2C_address;	/*VR */
	UCHAR  ucVr_I2C_Line;
	UCHAR  ucPlx_I2C_address;  /*PLX */
	UCHAR  ucPlx_I2C_Line;
	USHORT usReserved;
पूर्ण ATOM_Fiji_PowerTune_Table;

प्रकार काष्ठा _ATOM_Polaris_PowerTune_Table
अणु
    UCHAR  ucRevId;
    USHORT usTDP;
    USHORT usConfigurableTDP;
    USHORT usTDC;
    USHORT usBatteryPowerLimit;
    USHORT usSmallPowerLimit;
    USHORT usLowCACLeakage;
    USHORT usHighCACLeakage;
    USHORT usMaximumPowerDeliveryLimit;
    USHORT usTjMax;  // For Fiji, this is also usTemperatureLimitEdge;
    USHORT usPowerTuneDataSetID;
    USHORT usEDCLimit;
    USHORT usSoftwareShutकरोwnTemp;
    USHORT usClockStretchAmount;
    USHORT usTemperatureLimitHotspot;  //The following are added क्रम Fiji
    USHORT usTemperatureLimitLiquid1;
    USHORT usTemperatureLimitLiquid2;
    USHORT usTemperatureLimitVrVddc;
    USHORT usTemperatureLimitVrMvdd;
    USHORT usTemperatureLimitPlx;
    UCHAR  ucLiquid1_I2C_address;  //Liquid
    UCHAR  ucLiquid2_I2C_address;
    UCHAR  ucLiquid_I2C_Line;
    UCHAR  ucVr_I2C_address;  //VR
    UCHAR  ucVr_I2C_Line;
    UCHAR  ucPlx_I2C_address;  //PLX
    UCHAR  ucPlx_I2C_Line;
    USHORT usBoostPowerLimit;
    UCHAR  ucCKS_LDO_REFSEL;
    UCHAR  ucHotSpotOnly;
    UCHAR  ucReserve;
    USHORT usReserve;
पूर्ण ATOM_Polaris_PowerTune_Table;

#घोषणा ATOM_PPM_A_A    1
#घोषणा ATOM_PPM_A_I    2
प्रकार काष्ठा _ATOM_Tonga_PPM_Table अणु
	UCHAR   ucRevId;
	UCHAR   ucPpmDesign;		  /*A+I or A+A */
	USHORT  usCpuCoreNumber;
	ULONG  ulPlatक्रमmTDP;
	ULONG  ulSmallACPlatक्रमmTDP;
	ULONG  ulPlatक्रमmTDC;
	ULONG  ulSmallACPlatक्रमmTDC;
	ULONG  ulApuTDP;
	ULONG  ulDGpuTDP;
	ULONG  ulDGpuUlvPower;
	ULONG  ulTjmax;
पूर्ण ATOM_Tonga_PPM_Table;

प्रकार काष्ठा _ATOM_Tonga_Hard_Limit_Record अणु
	ULONG  ulSCLKLimit;
	ULONG  ulMCLKLimit;
	USHORT  usVddcLimit;
	USHORT  usVddciLimit;
	USHORT  usVddgfxLimit;
पूर्ण ATOM_Tonga_Hard_Limit_Record;

प्रकार काष्ठा _ATOM_Tonga_Hard_Limit_Table अणु
	UCHAR ucRevId;
	UCHAR ucNumEntries;
	ATOM_Tonga_Hard_Limit_Record entries[1];
पूर्ण ATOM_Tonga_Hard_Limit_Table;

प्रकार काष्ठा _ATOM_Tonga_GPIO_Table अणु
	UCHAR  ucRevId;
	UCHAR  ucVRHotTriggeredSclkDpmIndex;		/* If VRHot संकेत is triggered SCLK will be limited to this DPM level */
	UCHAR  ucReserve[5];
पूर्ण ATOM_Tonga_GPIO_Table;

प्रकार काष्ठा _PPTable_Generic_SubTable_Header अणु
	UCHAR  ucRevId;
पूर्ण PPTable_Generic_SubTable_Header;


#आशय pack(pop)


#पूर्ण_अगर
