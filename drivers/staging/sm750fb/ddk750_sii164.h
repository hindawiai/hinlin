<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DDK750_SII164_H__
#घोषणा DDK750_SII164_H__

#घोषणा USE_DVICHIP

/* Hot Plug detection mode काष्ठाure */
क्रमागत sii164_hot_plug_mode अणु
	SII164_HOTPLUG_DISABLE = 0,	/* Disable Hot Plug output bit
					 * (always high).
					 */

	SII164_HOTPLUG_USE_MDI,         /* Use Monitor Detect Interrupt bit. */
	SII164_HOTPLUG_USE_RSEN,        /* Use Receiver Sense detect bit. */
	SII164_HOTPLUG_USE_HTPLG        /* Use Hot Plug detect bit. */
पूर्ण;

/* Silicon Image SiI164 chip prototype */
दीर्घ sii164InitChip(अचिन्हित अक्षर edgeSelect,
		    अचिन्हित अक्षर busSelect,
		    अचिन्हित अक्षर dualEdgeClkSelect,
		    अचिन्हित अक्षर hsyncEnable,
		    अचिन्हित अक्षर vsyncEnable,
		    अचिन्हित अक्षर deskewEnable,
		    अचिन्हित अक्षर deskewSetting,
		    अचिन्हित अक्षर continuousSyncEnable,
		    अचिन्हित अक्षर pllFilterEnable,
		    अचिन्हित अक्षर pllFilterValue);

अचिन्हित लघु sii164GetVenकरोrID(व्योम);
अचिन्हित लघु sii164GetDeviceID(व्योम);

#अगर_घोषित SII164_FULL_FUNCTIONS
व्योम sii164ResetChip(व्योम);
अक्षर *sii164GetChipString(व्योम);
व्योम sii164SetPower(अचिन्हित अक्षर घातerUp);
व्योम sii164EnableHotPlugDetection(अचिन्हित अक्षर enableHotPlug);
अचिन्हित अक्षर sii164IsConnected(व्योम);
अचिन्हित अक्षर sii164CheckInterrupt(व्योम);
व्योम sii164ClearInterrupt(व्योम);
#पूर्ण_अगर
/*
 * below रेजिस्टर definition is used क्रम
 * Silicon Image SiI164 DVI controller chip
 */
/*
 * Venकरोr ID रेजिस्टरs
 */
#घोषणा SII164_VENDOR_ID_LOW                        0x00
#घोषणा SII164_VENDOR_ID_HIGH                       0x01

/*
 * Device ID रेजिस्टरs
 */
#घोषणा SII164_DEVICE_ID_LOW                        0x02
#घोषणा SII164_DEVICE_ID_HIGH                       0x03

/*
 * Device Revision
 */
#घोषणा SII164_DEVICE_REVISION                      0x04

/*
 * Frequency Limitation रेजिस्टरs
 */
#घोषणा SII164_FREQUENCY_LIMIT_LOW                  0x06
#घोषणा SII164_FREQUENCY_LIMIT_HIGH                 0x07

/*
 * Power Down and Input Signal Configuration रेजिस्टरs
 */
#घोषणा SII164_CONFIGURATION                        0x08

/* Power करोwn (PD) */
#घोषणा SII164_CONFIGURATION_POWER_DOWN             0x00
#घोषणा SII164_CONFIGURATION_POWER_NORMAL           0x01
#घोषणा SII164_CONFIGURATION_POWER_MASK             0x01

/* Input Edge Latch Select (EDGE) */
#घोषणा SII164_CONFIGURATION_LATCH_FALLING          0x00
#घोषणा SII164_CONFIGURATION_LATCH_RISING           0x02

/* Bus Select (BSEL) */
#घोषणा SII164_CONFIGURATION_BUS_12BITS             0x00
#घोषणा SII164_CONFIGURATION_BUS_24BITS             0x04

/* Dual Edge Clock Select (DSEL) */
#घोषणा SII164_CONFIGURATION_CLOCK_SINGLE           0x00
#घोषणा SII164_CONFIGURATION_CLOCK_DUAL             0x08

/* Horizontal Sync Enable (HEN) */
#घोषणा SII164_CONFIGURATION_HSYNC_FORCE_LOW        0x00
#घोषणा SII164_CONFIGURATION_HSYNC_AS_IS            0x10

/* Vertical Sync Enable (VEN) */
#घोषणा SII164_CONFIGURATION_VSYNC_FORCE_LOW        0x00
#घोषणा SII164_CONFIGURATION_VSYNC_AS_IS            0x20

/*
 * Detection रेजिस्टरs
 */
#घोषणा SII164_DETECT                               0x09

/* Monitor Detect Interrupt (MDI) */
#घोषणा SII164_DETECT_MONITOR_STATE_CHANGE          0x00
#घोषणा SII164_DETECT_MONITOR_STATE_NO_CHANGE       0x01
#घोषणा SII164_DETECT_MONITOR_STATE_CLEAR           0x01
#घोषणा SII164_DETECT_MONITOR_STATE_MASK            0x01

/* Hot Plug detect Input (HTPLG) */
#घोषणा SII164_DETECT_HOT_PLUG_STATUS_OFF           0x00
#घोषणा SII164_DETECT_HOT_PLUG_STATUS_ON            0x02
#घोषणा SII164_DETECT_HOT_PLUG_STATUS_MASK          0x02

/* Receiver Sense (RSEN) */
#घोषणा SII164_DETECT_RECEIVER_SENSE_NOT_DETECTED   0x00
#घोषणा SII164_DETECT_RECEIVER_SENSE_DETECTED       0x04

/* Interrupt Generation Method (TSEL) */
#घोषणा SII164_DETECT_INTERRUPT_BY_RSEN_PIN         0x00
#घोषणा SII164_DETECT_INTERRUPT_BY_HTPLG_PIN        0x08
#घोषणा SII164_DETECT_INTERRUPT_MASK                0x08

/* Monitor Sense Output (MSEN) */
#घोषणा SII164_DETECT_MONITOR_SENSE_OUTPUT_HIGH     0x00
#घोषणा SII164_DETECT_MONITOR_SENSE_OUTPUT_MDI      0x10
#घोषणा SII164_DETECT_MONITOR_SENSE_OUTPUT_RSEN     0x20
#घोषणा SII164_DETECT_MONITOR_SENSE_OUTPUT_HTPLG    0x30
#घोषणा SII164_DETECT_MONITOR_SENSE_OUTPUT_FLAG     0x30

/*
 * Skewing रेजिस्टरs
 */
#घोषणा SII164_DESKEW                               0x0A

/* General Purpose Input (CTL[3:1]) */
#घोषणा SII164_DESKEW_GENERAL_PURPOSE_INPUT_MASK    0x0E

/* De-skewing Enable bit (DKEN) */
#घोषणा SII164_DESKEW_DISABLE                       0x00
#घोषणा SII164_DESKEW_ENABLE                        0x10

/* De-skewing Setting (DK[3:1])*/
#घोषणा SII164_DESKEW_1_STEP                        0x00
#घोषणा SII164_DESKEW_2_STEP                        0x20
#घोषणा SII164_DESKEW_3_STEP                        0x40
#घोषणा SII164_DESKEW_4_STEP                        0x60
#घोषणा SII164_DESKEW_5_STEP                        0x80
#घोषणा SII164_DESKEW_6_STEP                        0xA0
#घोषणा SII164_DESKEW_7_STEP                        0xC0
#घोषणा SII164_DESKEW_8_STEP                        0xE0

/*
 * User Configuration Data रेजिस्टरs (CFG 7:0)
 */
#घोषणा SII164_USER_CONFIGURATION                   0x0B

/*
 * PLL रेजिस्टरs
 */
#घोषणा SII164_PLL                                  0x0C

/* PLL Filter Value (PLLF) */
#घोषणा SII164_PLL_FILTER_VALUE_MASK                0x0E

/* PLL Filter Enable (PFEN) */
#घोषणा SII164_PLL_FILTER_DISABLE                   0x00
#घोषणा SII164_PLL_FILTER_ENABLE                    0x01

/* Sync Continuous (SCNT) */
#घोषणा SII164_PLL_FILTER_SYNC_CONTINUOUS_DISABLE   0x00
#घोषणा SII164_PLL_FILTER_SYNC_CONTINUOUS_ENABLE    0x80

#पूर्ण_अगर
