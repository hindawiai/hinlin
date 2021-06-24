<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#अगर_अघोषित __REG_H__
#घोषणा __REG_H__

#समावेश <linux/bitops.h>

#घोषणा REGISTERS_BASE 0x00300000
#घोषणा DRPW_BASE      0x00310000

#घोषणा REGISTERS_DOWN_SIZE 0x00008800
#घोषणा REGISTERS_WORK_SIZE 0x0000b000

#घोषणा HW_ACCESS_ELP_CTRL_REG_ADDR         0x1FFFC

/* ELP रेजिस्टर commands */
#घोषणा ELPCTRL_WAKE_UP             0x1
#घोषणा ELPCTRL_WAKE_UP_WLAN_READY  0x5
#घोषणा ELPCTRL_SLEEP               0x0
/* ELP WLAN_READY bit */
#घोषणा ELPCTRL_WLAN_READY          0x2

/* Device Configuration रेजिस्टरs*/
#घोषणा SOR_CFG                        (REGISTERS_BASE + 0x0800)
#घोषणा ECPU_CTRL                      (REGISTERS_BASE + 0x0804)
#घोषणा HI_CFG                         (REGISTERS_BASE + 0x0808)

/* EEPROM रेजिस्टरs */
#घोषणा EE_START                       (REGISTERS_BASE + 0x080C)
#घोषणा EE_CTL                         (REGISTERS_BASE + 0x2000)
#घोषणा EE_DATA                        (REGISTERS_BASE + 0x2004)
#घोषणा EE_ADDR                        (REGISTERS_BASE + 0x2008)

#घोषणा EE_CTL_READ                   2

#घोषणा CHIP_ID_B                      (REGISTERS_BASE + 0x5674)

#घोषणा CHIP_ID_1251_PG10	           (0x7010101)
#घोषणा CHIP_ID_1251_PG11	           (0x7020101)
#घोषणा CHIP_ID_1251_PG12	           (0x7030101)

#घोषणा ENABLE                         (REGISTERS_BASE + 0x5450)

/* Power Management रेजिस्टरs */
#घोषणा ELP_CFG_MODE                   (REGISTERS_BASE + 0x5804)
#घोषणा ELP_CMD                        (REGISTERS_BASE + 0x5808)
#घोषणा PLL_CAL_TIME                   (REGISTERS_BASE + 0x5810)
#घोषणा CLK_REQ_TIME                   (REGISTERS_BASE + 0x5814)
#घोषणा CLK_BUF_TIME                   (REGISTERS_BASE + 0x5818)

#घोषणा CFG_PLL_SYNC_CNT               (REGISTERS_BASE + 0x5820)

/* Scratch Pad रेजिस्टरs*/
#घोषणा SCR_PAD0                       (REGISTERS_BASE + 0x5608)
#घोषणा SCR_PAD1                       (REGISTERS_BASE + 0x560C)
#घोषणा SCR_PAD2                       (REGISTERS_BASE + 0x5610)
#घोषणा SCR_PAD3                       (REGISTERS_BASE + 0x5614)
#घोषणा SCR_PAD4                       (REGISTERS_BASE + 0x5618)
#घोषणा SCR_PAD4_SET                   (REGISTERS_BASE + 0x561C)
#घोषणा SCR_PAD4_CLR                   (REGISTERS_BASE + 0x5620)
#घोषणा SCR_PAD5                       (REGISTERS_BASE + 0x5624)
#घोषणा SCR_PAD5_SET                   (REGISTERS_BASE + 0x5628)
#घोषणा SCR_PAD5_CLR                   (REGISTERS_BASE + 0x562C)
#घोषणा SCR_PAD6                       (REGISTERS_BASE + 0x5630)
#घोषणा SCR_PAD7                       (REGISTERS_BASE + 0x5634)
#घोषणा SCR_PAD8                       (REGISTERS_BASE + 0x5638)
#घोषणा SCR_PAD9                       (REGISTERS_BASE + 0x563C)

/* Spare रेजिस्टरs*/
#घोषणा SPARE_A1                       (REGISTERS_BASE + 0x0994)
#घोषणा SPARE_A2                       (REGISTERS_BASE + 0x0998)
#घोषणा SPARE_A3                       (REGISTERS_BASE + 0x099C)
#घोषणा SPARE_A4                       (REGISTERS_BASE + 0x09A0)
#घोषणा SPARE_A5                       (REGISTERS_BASE + 0x09A4)
#घोषणा SPARE_A6                       (REGISTERS_BASE + 0x09A8)
#घोषणा SPARE_A7                       (REGISTERS_BASE + 0x09AC)
#घोषणा SPARE_A8                       (REGISTERS_BASE + 0x09B0)
#घोषणा SPARE_B1                       (REGISTERS_BASE + 0x5420)
#घोषणा SPARE_B2                       (REGISTERS_BASE + 0x5424)
#घोषणा SPARE_B3                       (REGISTERS_BASE + 0x5428)
#घोषणा SPARE_B4                       (REGISTERS_BASE + 0x542C)
#घोषणा SPARE_B5                       (REGISTERS_BASE + 0x5430)
#घोषणा SPARE_B6                       (REGISTERS_BASE + 0x5434)
#घोषणा SPARE_B7                       (REGISTERS_BASE + 0x5438)
#घोषणा SPARE_B8                       (REGISTERS_BASE + 0x543C)

क्रमागत wl12xx_acx_पूर्णांक_reg अणु
	ACX_REG_INTERRUPT_TRIG,
	ACX_REG_INTERRUPT_TRIG_H,

/*=============================================
  Host Interrupt Mask Register - 32bit (RW)
  ------------------------------------------
  Setting a bit in this रेजिस्टर masks the
  corresponding पूर्णांकerrupt to the host.
  0 - RX0		- Rx first dubble buffer Data Interrupt
  1 - TXD		- Tx Data Interrupt
  2 - TXXFR		- Tx Transfer Interrupt
  3 - RX1		- Rx second dubble buffer Data Interrupt
  4 - RXXFR		- Rx Transfer Interrupt
  5 - EVENT_A	- Event Mailbox पूर्णांकerrupt
  6 - EVENT_B	- Event Mailbox पूर्णांकerrupt
  7 - WNONHST	- Wake On Host Interrupt
  8 - TRACE_A	- Debug Trace पूर्णांकerrupt
  9 - TRACE_B	- Debug Trace पूर्णांकerrupt
 10 - CDCMP		- Command Complete Interrupt
 11 -
 12 -
 13 -
 14 - ICOMP		- Initialization Complete Interrupt
 16 - SG SE		- Soft Gemini - Sense enable पूर्णांकerrupt
 17 - SG SD		- Soft Gemini - Sense disable पूर्णांकerrupt
 18 -			-
 19 -			-
 20 -			-
 21-			-
 Default: 0x0001
*==============================================*/
	ACX_REG_INTERRUPT_MASK,

/*=============================================
  Host Interrupt Mask Set 16bit, (Write only)
  ------------------------------------------
 Setting a bit in this रेजिस्टर sets
 the corresponding bin in ACX_HINT_MASK रेजिस्टर
 without effecting the mask
 state of other bits (0 = no effect).
==============================================*/
	ACX_REG_HINT_MASK_SET,

/*=============================================
  Host Interrupt Mask Clear 16bit,(Write only)
  ------------------------------------------
 Setting a bit in this रेजिस्टर clears
 the corresponding bin in ACX_HINT_MASK रेजिस्टर
 without effecting the mask
 state of other bits (0 = no effect).
=============================================*/
	ACX_REG_HINT_MASK_CLR,

/*=============================================
  Host Interrupt Status Nondeकाष्ठाive Read
  16bit,(Read only)
  ------------------------------------------
 The host can पढ़ो this रेजिस्टर to determine
 which पूर्णांकerrupts are active.
 Reading this रेजिस्टर करोesn't
 effect its content.
=============================================*/
	ACX_REG_INTERRUPT_NO_CLEAR,

/*=============================================
  Host Interrupt Status Clear on Read  Register
  16bit,(Read only)
  ------------------------------------------
 The host can पढ़ो this रेजिस्टर to determine
 which पूर्णांकerrupts are active.
 Reading this रेजिस्टर clears it,
 thus making all पूर्णांकerrupts inactive.
==============================================*/
	ACX_REG_INTERRUPT_CLEAR,

/*=============================================
  Host Interrupt Acknowledge Register
  16bit,(Write only)
  ------------------------------------------
 The host can set inभागidual bits in this
 रेजिस्टर to clear (acknowledge) the corresp.
 पूर्णांकerrupt status bits in the HINT_STS_CLR and
 HINT_STS_ND रेजिस्टरs, thus making the
 assotiated पूर्णांकerrupt inactive. (0-no effect)
==============================================*/
	ACX_REG_INTERRUPT_ACK,

/*===============================================
   Host Software Reset - 32bit RW
 ------------------------------------------
    [31:1] Reserved
    0  SOFT_RESET Soft Reset  - When this bit is set,
    it holds the Wlan hardware in a soft reset state.
    This reset disables all MAC and baseband processor
    घड़ीs except the CardBus/PCI पूर्णांकerface घड़ी.
    It also initializes all MAC state machines except
    the host पूर्णांकerface. It करोes not reload the
    contents of the EEPROM. When this bit is cleared
    (not self-clearing), the Wlan hardware
    निकासs the software reset state.
===============================================*/
	ACX_REG_SLV_SOFT_RESET,

/*===============================================
 EEPROM Burst Read Start  - 32bit RW
 ------------------------------------------
 [31:1] Reserved
 0  ACX_EE_START -  EEPROM Burst Read Start 0
 Setting this bit starts a burst पढ़ो from
 the बाह्यal EEPROM.
 If this bit is set (after reset) beक्रमe an EEPROM पढ़ो/ग_लिखो,
 the burst पढ़ो starts at EEPROM address 0.
 Otherwise, it starts at the address
 following the address of the previous access.
 TheWlan hardware hardware clears this bit स्वतःmatically.

 Default: 0x00000000
*================================================*/
	ACX_REG_EE_START,

/* Embedded ARM CPU Control */

/*===============================================
 Halt eCPU   - 32bit RW
 ------------------------------------------
 0 HALT_ECPU Halt Embedded CPU - This bit is the
 complement of bit 1 (MDATA2) in the SOR_CFG रेजिस्टर.
 During a hardware reset, this bit holds
 the inverse of MDATA2.
 When करोwnloading firmware from the host,
 set this bit (pull करोwn MDATA2).
 The host clears this bit after करोwnloading the firmware पूर्णांकo
 zero-रुको-state SSRAM.
 When loading firmware from Flash, clear this bit (pull up MDATA2)
 so that the eCPU can run the bootloader code in Flash
 HALT_ECPU eCPU State
 --------------------
 1 halt eCPU
 0 enable eCPU
 ===============================================*/
	ACX_REG_ECPU_CONTROL,

	ACX_REG_TABLE_LEN
पूर्ण;

#घोषणा ACX_SLV_SOFT_RESET_BIT   BIT(0)
#घोषणा ACX_REG_EEPROM_START_BIT BIT(0)

/* Command/Inक्रमmation Mailbox Poपूर्णांकers */

/*===============================================
  Command Mailbox Poपूर्णांकer - 32bit RW
 ------------------------------------------
 This रेजिस्टर holds the start address of
 the command mailbox located in the Wlan hardware memory.
 The host must पढ़ो this poपूर्णांकer after a reset to
 find the location of the command mailbox.
 The Wlan hardware initializes the command mailbox
 poपूर्णांकer with the शेष address of the command mailbox.
 The command mailbox poपूर्णांकer is not valid until after
 the host receives the Init Complete पूर्णांकerrupt from
 the Wlan hardware.
 ===============================================*/
#घोषणा REG_COMMAND_MAILBOX_PTR				(SCR_PAD0)

/*===============================================
  Inक्रमmation Mailbox Poपूर्णांकer - 32bit RW
 ------------------------------------------
 This रेजिस्टर holds the start address of
 the inक्रमmation mailbox located in the Wlan hardware memory.
 The host must पढ़ो this poपूर्णांकer after a reset to find
 the location of the inक्रमmation mailbox.
 The Wlan hardware initializes the inक्रमmation mailbox poपूर्णांकer
 with the शेष address of the inक्रमmation mailbox.
 The inक्रमmation mailbox poपूर्णांकer is not valid
 until after the host receives the Init Complete पूर्णांकerrupt from
 the Wlan hardware.
 ===============================================*/
#घोषणा REG_EVENT_MAILBOX_PTR				(SCR_PAD1)


/* Misc */

#घोषणा REG_ENABLE_TX_RX				(ENABLE)
/*
 * Rx configuration (filter) inक्रमmation element
 * ---------------------------------------------
 */
#घोषणा REG_RX_CONFIG				(RX_CFG)
#घोषणा REG_RX_FILTER				(RX_FILTER_CFG)


#घोषणा RX_CFG_ENABLE_PHY_HEADER_PLCP	 0x0002

/* promiscuous - receives all valid frames */
#घोषणा RX_CFG_PROMISCUOUS		 0x0008

/* receives frames from any BSSID */
#घोषणा RX_CFG_BSSID			 0x0020

/* receives frames destined to any MAC address */
#घोषणा RX_CFG_MAC			 0x0010

#घोषणा RX_CFG_ENABLE_ONLY_MY_DEST_MAC	 0x0010
#घोषणा RX_CFG_ENABLE_ANY_DEST_MAC	 0x0000
#घोषणा RX_CFG_ENABLE_ONLY_MY_BSSID	 0x0020
#घोषणा RX_CFG_ENABLE_ANY_BSSID		 0x0000

/* discards all broadcast frames */
#घोषणा RX_CFG_DISABLE_BCAST		 0x0200

#घोषणा RX_CFG_ENABLE_ONLY_MY_SSID	 0x0400
#घोषणा RX_CFG_ENABLE_RX_CMPLT_FCS_ERROR 0x0800
#घोषणा RX_CFG_COPY_RX_STATUS		 0x2000
#घोषणा RX_CFG_TSF			 0x10000

#घोषणा RX_CONFIG_OPTION_ANY_DST_MY_BSS	 (RX_CFG_ENABLE_ANY_DEST_MAC | \
					  RX_CFG_ENABLE_ONLY_MY_BSSID)

#घोषणा RX_CONFIG_OPTION_MY_DST_ANY_BSS	 (RX_CFG_ENABLE_ONLY_MY_DEST_MAC\
					  | RX_CFG_ENABLE_ANY_BSSID)

#घोषणा RX_CONFIG_OPTION_ANY_DST_ANY_BSS (RX_CFG_ENABLE_ANY_DEST_MAC | \
					  RX_CFG_ENABLE_ANY_BSSID)

#घोषणा RX_CONFIG_OPTION_MY_DST_MY_BSS	 (RX_CFG_ENABLE_ONLY_MY_DEST_MAC\
					  | RX_CFG_ENABLE_ONLY_MY_BSSID)

#घोषणा RX_CONFIG_OPTION_FOR_SCAN  (RX_CFG_ENABLE_PHY_HEADER_PLCP \
				    | RX_CFG_ENABLE_RX_CMPLT_FCS_ERROR \
				    | RX_CFG_COPY_RX_STATUS | RX_CFG_TSF)

#घोषणा RX_CONFIG_OPTION_FOR_MEASUREMENT (RX_CFG_ENABLE_ANY_DEST_MAC)

#घोषणा RX_CONFIG_OPTION_FOR_JOIN	 (RX_CFG_ENABLE_ONLY_MY_BSSID | \
					  RX_CFG_ENABLE_ONLY_MY_DEST_MAC)

#घोषणा RX_CONFIG_OPTION_FOR_IBSS_JOIN   (RX_CFG_ENABLE_ONLY_MY_SSID | \
					  RX_CFG_ENABLE_ONLY_MY_DEST_MAC)

#घोषणा RX_FILTER_OPTION_DEF	      (CFG_RX_MGMT_EN | CFG_RX_DATA_EN\
				       | CFG_RX_CTL_EN | CFG_RX_BCN_EN\
				       | CFG_RX_AUTH_EN | CFG_RX_ASSOC_EN)

#घोषणा RX_FILTER_OPTION_FILTER_ALL	 0

#घोषणा RX_FILTER_OPTION_DEF_PRSP_BCN  (CFG_RX_PRSP_EN | CFG_RX_MGMT_EN\
					| CFG_RX_RCTS_ACK | CFG_RX_BCN_EN)

#घोषणा RX_FILTER_OPTION_JOIN	     (CFG_RX_MGMT_EN | CFG_RX_DATA_EN\
				      | CFG_RX_BCN_EN | CFG_RX_AUTH_EN\
				      | CFG_RX_ASSOC_EN | CFG_RX_RCTS_ACK\
				      | CFG_RX_PRSP_EN)


/*===============================================
 EEPROM Read/Write Request 32bit RW
 ------------------------------------------
 1 EE_READ - EEPROM Read Request 1 - Setting this bit
 loads a single byte of data पूर्णांकo the EE_DATA
 रेजिस्टर from the EEPROM location specअगरied in
 the EE_ADDR रेजिस्टर.
 The Wlan hardware hardware clears this bit स्वतःmatically.
 EE_DATA is valid when this bit is cleared.

 0 EE_WRITE  - EEPROM Write Request  - Setting this bit
 ग_लिखोs a single byte of data from the EE_DATA रेजिस्टर पूर्णांकo the
 EEPROM location specअगरied in the EE_ADDR रेजिस्टर.
 The Wlan hardware hardware clears this bit स्वतःmatically.
*===============================================*/
#घोषणा EE_CTL                              (REGISTERS_BASE + 0x2000)
#घोषणा ACX_EE_CTL_REG                      EE_CTL
#घोषणा EE_WRITE                            0x00000001ul
#घोषणा EE_READ                             0x00000002ul

/*===============================================
  EEPROM Address  - 32bit RW
  ------------------------------------------
  This रेजिस्टर specअगरies the address
  within the EEPROM from/to which to पढ़ो/ग_लिखो data.
  ===============================================*/
#घोषणा EE_ADDR                             (REGISTERS_BASE + 0x2008)
#घोषणा ACX_EE_ADDR_REG                     EE_ADDR

/*===============================================
  EEPROM Data  - 32bit RW
  ------------------------------------------
  This रेजिस्टर either holds the पढ़ो 8 bits of
  data from the EEPROM or the ग_लिखो data
  to be written to the EEPROM.
  ===============================================*/
#घोषणा EE_DATA                             (REGISTERS_BASE + 0x2004)
#घोषणा ACX_EE_DATA_REG                     EE_DATA

#घोषणा EEPROM_ACCESS_TO                    10000   /* समयout counter */
#घोषणा START_EEPROM_MGR                    0x00000001

/*===============================================
  EEPROM Base Address  - 32bit RW
  ------------------------------------------
  This रेजिस्टर holds the upper nine bits
  [23:15] of the 24-bit Wlan hardware memory
  address क्रम burst पढ़ोs from EEPROM accesses.
  The EEPROM provides the lower 15 bits of this address.
  The MSB of the address from the EEPROM is ignored.
  ===============================================*/
#घोषणा ACX_EE_CFG                          EE_CFG

/*===============================================
  GPIO Output Values  -32bit, RW
  ------------------------------------------
  [31:16]  Reserved
  [15: 0]  Specअगरy the output values (at the output driver inमाला_दो) क्रम
  GPIO[15:0], respectively.
  ===============================================*/
#घोषणा ACX_GPIO_OUT_REG            GPIO_OUT
#घोषणा ACX_MAX_GPIO_LINES          15

/*===============================================
  Contention winकरोw  -32bit, RW
  ------------------------------------------
  [31:26]  Reserved
  [25:16]  Max (0x3ff)
  [15:07]  Reserved
  [06:00]  Current contention winकरोw value - शेष is 0x1F
  ===============================================*/
#घोषणा ACX_CONT_WIND_CFG_REG    CONT_WIND_CFG
#घोषणा ACX_CONT_WIND_MIN_MASK   0x0000007f
#घोषणा ACX_CONT_WIND_MAX        0x03ff0000

/*===============================================
  HI_CFG Interface Configuration Register Values
  ------------------------------------------
  ===============================================*/
#घोषणा HI_CFG_UART_ENABLE          0x00000004
#घोषणा HI_CFG_RST232_ENABLE        0x00000008
#घोषणा HI_CFG_CLOCK_REQ_SELECT     0x00000010
#घोषणा HI_CFG_HOST_INT_ENABLE      0x00000020
#घोषणा HI_CFG_VLYNQ_OUTPUT_ENABLE  0x00000040
#घोषणा HI_CFG_HOST_INT_ACTIVE_LOW  0x00000080
#घोषणा HI_CFG_UART_TX_OUT_GPIO_15  0x00000100
#घोषणा HI_CFG_UART_TX_OUT_GPIO_14  0x00000200
#घोषणा HI_CFG_UART_TX_OUT_GPIO_7   0x00000400

/*
 * NOTE: USE_ACTIVE_HIGH compilation flag should be defined in makefile
 *       क्रम platक्रमms using active high पूर्णांकerrupt level
 */
#अगर_घोषित USE_ACTIVE_HIGH
#घोषणा HI_CFG_DEF_VAL              \
	(HI_CFG_UART_ENABLE |        \
	HI_CFG_RST232_ENABLE |      \
	HI_CFG_CLOCK_REQ_SELECT |   \
	HI_CFG_HOST_INT_ENABLE)
#अन्यथा
#घोषणा HI_CFG_DEF_VAL              \
	(HI_CFG_UART_ENABLE |        \
	HI_CFG_RST232_ENABLE |      \
	HI_CFG_CLOCK_REQ_SELECT |   \
	HI_CFG_HOST_INT_ENABLE)

#पूर्ण_अगर

#घोषणा REF_FREQ_19_2                       0
#घोषणा REF_FREQ_26_0                       1
#घोषणा REF_FREQ_38_4                       2
#घोषणा REF_FREQ_40_0                       3
#घोषणा REF_FREQ_33_6                       4
#घोषणा REF_FREQ_NUM                        5

#घोषणा LUT_PARAM_INTEGER_DIVIDER           0
#घोषणा LUT_PARAM_FRACTIONAL_DIVIDER        1
#घोषणा LUT_PARAM_ATTN_BB                   2
#घोषणा LUT_PARAM_ALPHA_BB                  3
#घोषणा LUT_PARAM_STOP_TIME_BB              4
#घोषणा LUT_PARAM_BB_PLL_LOOP_FILTER        5
#घोषणा LUT_PARAM_NUM                       6

#घोषणा ACX_EEPROMLESS_IND_REG              (SCR_PAD4)
#घोषणा USE_EEPROM                          0
#घोषणा SOFT_RESET_MAX_TIME                 1000000
#घोषणा SOFT_RESET_STALL_TIME               1000
#घोषणा NVS_DATA_BUNDARY_ALIGNMENT          4


/* Firmware image load chunk size */
#घोषणा CHUNK_SIZE          512

/* Firmware image header size */
#घोषणा FW_HDR_SIZE 8

#घोषणा ECPU_CONTROL_HALT					0x00000101


/******************************************************************************

    CHANNELS, BAND & REG DOMAINS definitions

******************************************************************************/


क्रमागत अणु
	RADIO_BAND_2_4GHZ = 0,  /* 2.4 Ghz band */
	RADIO_BAND_5GHZ = 1,    /* 5 Ghz band */
	RADIO_BAND_JAPAN_4_9_GHZ = 2,
	DEFAULT_BAND = RADIO_BAND_2_4GHZ,
	INVALID_BAND = 0xFE,
	MAX_RADIO_BANDS = 0xFF
पूर्ण;

क्रमागत अणु
	NO_RATE      = 0,
	RATE_1MBPS   = 0x0A,
	RATE_2MBPS   = 0x14,
	RATE_5_5MBPS = 0x37,
	RATE_6MBPS   = 0x0B,
	RATE_9MBPS   = 0x0F,
	RATE_11MBPS  = 0x6E,
	RATE_12MBPS  = 0x0A,
	RATE_18MBPS  = 0x0E,
	RATE_22MBPS  = 0xDC,
	RATE_24MBPS  = 0x09,
	RATE_36MBPS  = 0x0D,
	RATE_48MBPS  = 0x08,
	RATE_54MBPS  = 0x0C
पूर्ण;

क्रमागत अणु
	RATE_INDEX_1MBPS   =  0,
	RATE_INDEX_2MBPS   =  1,
	RATE_INDEX_5_5MBPS =  2,
	RATE_INDEX_6MBPS   =  3,
	RATE_INDEX_9MBPS   =  4,
	RATE_INDEX_11MBPS  =  5,
	RATE_INDEX_12MBPS  =  6,
	RATE_INDEX_18MBPS  =  7,
	RATE_INDEX_22MBPS  =  8,
	RATE_INDEX_24MBPS  =  9,
	RATE_INDEX_36MBPS  =  10,
	RATE_INDEX_48MBPS  =  11,
	RATE_INDEX_54MBPS  =  12,
	RATE_INDEX_MAX     =  RATE_INDEX_54MBPS,
	MAX_RATE_INDEX,
	INVALID_RATE_INDEX = MAX_RATE_INDEX,
	RATE_INDEX_ENUM_MAX_SIZE = 0x7FFFFFFF
पूर्ण;

क्रमागत अणु
	RATE_MASK_1MBPS = 0x1,
	RATE_MASK_2MBPS = 0x2,
	RATE_MASK_5_5MBPS = 0x4,
	RATE_MASK_11MBPS = 0x20,
पूर्ण;

#घोषणा SHORT_PREAMBLE_BIT   BIT(0) /* CCK or Barker depending on the rate */
#घोषणा OFDM_RATE_BIT        BIT(6)
#घोषणा PBCC_RATE_BIT        BIT(7)

क्रमागत अणु
	CCK_LONG = 0,
	CCK_SHORT = SHORT_PREAMBLE_BIT,
	PBCC_LONG = PBCC_RATE_BIT,
	PBCC_SHORT = PBCC_RATE_BIT | SHORT_PREAMBLE_BIT,
	OFDM = OFDM_RATE_BIT
पूर्ण;

/******************************************************************************

Transmit-Descriptor RATE-SET field definitions...

Define a new "Rate-Set" क्रम TX path that incorporates the
Rate & Modulation info पूर्णांकo a single 16-bit field.

TxdRateSet_t:
b15   - Indicates Preamble type (1=SHORT, 0=LONG).
	Notes:
	Must be LONG (0) क्रम 1Mbps rate.
	Does not apply (set to 0) क्रम RevG-OFDM rates.
b14   - Indicates PBCC encoding (1=PBCC, 0=not).
	Notes:
	Does not apply (set to 0) क्रम rates 1 and 2 Mbps.
	Does not apply (set to 0) क्रम RevG-OFDM rates.
b13    - Unused (set to 0).
b12-b0 - Supported Rate indicator bits as defined below.

******************************************************************************/


/*************************************************************************

    Interrupt Trigger Register (Host -> WiLink)

**************************************************************************/

/* Hardware to Embedded CPU Interrupts - first 32-bit रेजिस्टर set */

/*
 * Host Command Interrupt. Setting this bit masks
 * the पूर्णांकerrupt that the host issues to inक्रमm
 * the FW that it has sent a command
 * to the Wlan hardware Command Mailbox.
 */
#घोषणा INTR_TRIG_CMD       BIT(0)

/*
 * Host Event Acknowlegde Interrupt. The host
 * sets this bit to acknowledge that it received
 * the unsolicited inक्रमmation from the event
 * mailbox.
 */
#घोषणा INTR_TRIG_EVENT_ACK BIT(1)

/*
 * The host sets this bit to inक्रमm the Wlan
 * FW that a TX packet is in the XFER
 * Buffer #0.
 */
#घोषणा INTR_TRIG_TX_PROC0 BIT(2)

/*
 * The host sets this bit to inक्रमm the FW
 * that it पढ़ो a packet from RX XFER
 * Buffer #0.
 */
#घोषणा INTR_TRIG_RX_PROC0 BIT(3)

#घोषणा INTR_TRIG_DEBUG_ACK BIT(4)

#घोषणा INTR_TRIG_STATE_CHANGED BIT(5)


/* Hardware to Embedded CPU Interrupts - second 32-bit रेजिस्टर set */

/*
 * The host sets this bit to inक्रमm the FW
 * that it पढ़ो a packet from RX XFER
 * Buffer #1.
 */
#घोषणा INTR_TRIG_RX_PROC1 BIT(17)

/*
 * The host sets this bit to inक्रमm the Wlan
 * hardware that a TX packet is in the XFER
 * Buffer #1.
 */
#घोषणा INTR_TRIG_TX_PROC1 BIT(18)

#पूर्ण_अगर
