<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __REG_H__
#घोषणा __REG_H__

#समावेश <linux/bitops.h>

#घोषणा REGISTERS_BASE 0x00300000
#घोषणा DRPW_BASE      0x00310000

#घोषणा REGISTERS_DOWN_SIZE 0x00008800
#घोषणा REGISTERS_WORK_SIZE 0x0000b000

#घोषणा FW_STATUS_ADDR                      (0x14FC0 + 0xA000)

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
#घोषणा WL12XX_SLV_SOFT_RESET		(REGISTERS_BASE + 0x0000)

#घोषणा WL1271_SLV_REG_DATA            (REGISTERS_BASE + 0x0008)
#घोषणा WL1271_SLV_REG_ADATA           (REGISTERS_BASE + 0x000c)
#घोषणा WL1271_SLV_MEM_DATA            (REGISTERS_BASE + 0x0018)

#घोषणा WL12XX_REG_INTERRUPT_TRIG         (REGISTERS_BASE + 0x0474)
#घोषणा WL12XX_REG_INTERRUPT_TRIG_H       (REGISTERS_BASE + 0x0478)

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
#घोषणा WL12XX_REG_INTERRUPT_MASK         (REGISTERS_BASE + 0x04DC)

/*=============================================
  Host Interrupt Mask Set 16bit, (Write only)
  ------------------------------------------
 Setting a bit in this रेजिस्टर sets
 the corresponding bin in ACX_HINT_MASK रेजिस्टर
 without effecting the mask
 state of other bits (0 = no effect).
==============================================*/
#घोषणा ACX_REG_HINT_MASK_SET          (REGISTERS_BASE + 0x04E0)

/*=============================================
  Host Interrupt Mask Clear 16bit,(Write only)
  ------------------------------------------
 Setting a bit in this रेजिस्टर clears
 the corresponding bin in ACX_HINT_MASK रेजिस्टर
 without effecting the mask
 state of other bits (0 = no effect).
=============================================*/
#घोषणा ACX_REG_HINT_MASK_CLR          (REGISTERS_BASE + 0x04E4)

/*=============================================
  Host Interrupt Status Nondeकाष्ठाive Read
  16bit,(Read only)
  ------------------------------------------
 The host can पढ़ो this रेजिस्टर to determine
 which पूर्णांकerrupts are active.
 Reading this रेजिस्टर करोesn't
 effect its content.
=============================================*/
#घोषणा WL12XX_REG_INTERRUPT_NO_CLEAR     (REGISTERS_BASE + 0x04E8)

/*=============================================
  Host Interrupt Status Clear on Read  Register
  16bit,(Read only)
  ------------------------------------------
 The host can पढ़ो this रेजिस्टर to determine
 which पूर्णांकerrupts are active.
 Reading this रेजिस्टर clears it,
 thus making all पूर्णांकerrupts inactive.
==============================================*/
#घोषणा ACX_REG_INTERRUPT_CLEAR        (REGISTERS_BASE + 0x04F8)

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
#घोषणा WL12XX_REG_INTERRUPT_ACK          (REGISTERS_BASE + 0x04F0)

#घोषणा WL12XX_REG_RX_DRIVER_COUNTER	(REGISTERS_BASE + 0x0538)

/* Device Configuration रेजिस्टरs*/
#घोषणा SOR_CFG                        (REGISTERS_BASE + 0x0800)

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
#घोषणा WL12XX_REG_ECPU_CONTROL           (REGISTERS_BASE + 0x0804)

#घोषणा WL12XX_HI_CFG			(REGISTERS_BASE + 0x0808)

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
#घोषणा ACX_REG_EE_START               (REGISTERS_BASE + 0x080C)

#घोषणा WL12XX_OCP_POR_CTR		(REGISTERS_BASE + 0x09B4)
#घोषणा WL12XX_OCP_DATA_WRITE		(REGISTERS_BASE + 0x09B8)
#घोषणा WL12XX_OCP_DATA_READ		(REGISTERS_BASE + 0x09BC)
#घोषणा WL12XX_OCP_CMD			(REGISTERS_BASE + 0x09C0)

#घोषणा WL12XX_HOST_WR_ACCESS		(REGISTERS_BASE + 0x09F8)

#घोषणा WL12XX_CHIP_ID_B		(REGISTERS_BASE + 0x5674)

#घोषणा WL12XX_ENABLE			(REGISTERS_BASE + 0x5450)

/* Power Management रेजिस्टरs */
#घोषणा WL12XX_ELP_CFG_MODE		(REGISTERS_BASE + 0x5804)
#घोषणा WL12XX_ELP_CMD			(REGISTERS_BASE + 0x5808)
#घोषणा WL12XX_PLL_CAL_TIME		(REGISTERS_BASE + 0x5810)
#घोषणा WL12XX_CLK_REQ_TIME		(REGISTERS_BASE + 0x5814)
#घोषणा WL12XX_CLK_BUF_TIME		(REGISTERS_BASE + 0x5818)

#घोषणा WL12XX_CFG_PLL_SYNC_CNT		(REGISTERS_BASE + 0x5820)

/* Scratch Pad रेजिस्टरs*/
#घोषणा WL12XX_SCR_PAD0			(REGISTERS_BASE + 0x5608)
#घोषणा WL12XX_SCR_PAD1			(REGISTERS_BASE + 0x560C)
#घोषणा WL12XX_SCR_PAD2			(REGISTERS_BASE + 0x5610)
#घोषणा WL12XX_SCR_PAD3			(REGISTERS_BASE + 0x5614)
#घोषणा WL12XX_SCR_PAD4			(REGISTERS_BASE + 0x5618)
#घोषणा WL12XX_SCR_PAD4_SET		(REGISTERS_BASE + 0x561C)
#घोषणा WL12XX_SCR_PAD4_CLR		(REGISTERS_BASE + 0x5620)
#घोषणा WL12XX_SCR_PAD5			(REGISTERS_BASE + 0x5624)
#घोषणा WL12XX_SCR_PAD5_SET		(REGISTERS_BASE + 0x5628)
#घोषणा WL12XX_SCR_PAD5_CLR		(REGISTERS_BASE + 0x562C)
#घोषणा WL12XX_SCR_PAD6			(REGISTERS_BASE + 0x5630)
#घोषणा WL12XX_SCR_PAD7			(REGISTERS_BASE + 0x5634)
#घोषणा WL12XX_SCR_PAD8			(REGISTERS_BASE + 0x5638)
#घोषणा WL12XX_SCR_PAD9			(REGISTERS_BASE + 0x563C)

/* Spare रेजिस्टरs*/
#घोषणा WL12XX_SPARE_A1			(REGISTERS_BASE + 0x0994)
#घोषणा WL12XX_SPARE_A2			(REGISTERS_BASE + 0x0998)
#घोषणा WL12XX_SPARE_A3			(REGISTERS_BASE + 0x099C)
#घोषणा WL12XX_SPARE_A4			(REGISTERS_BASE + 0x09A0)
#घोषणा WL12XX_SPARE_A5			(REGISTERS_BASE + 0x09A4)
#घोषणा WL12XX_SPARE_A6			(REGISTERS_BASE + 0x09A8)
#घोषणा WL12XX_SPARE_A7			(REGISTERS_BASE + 0x09AC)
#घोषणा WL12XX_SPARE_A8			(REGISTERS_BASE + 0x09B0)
#घोषणा WL12XX_SPARE_B1			(REGISTERS_BASE + 0x5420)
#घोषणा WL12XX_SPARE_B2			(REGISTERS_BASE + 0x5424)
#घोषणा WL12XX_SPARE_B3			(REGISTERS_BASE + 0x5428)
#घोषणा WL12XX_SPARE_B4			(REGISTERS_BASE + 0x542C)
#घोषणा WL12XX_SPARE_B5			(REGISTERS_BASE + 0x5430)
#घोषणा WL12XX_SPARE_B6			(REGISTERS_BASE + 0x5434)
#घोषणा WL12XX_SPARE_B7			(REGISTERS_BASE + 0x5438)
#घोषणा WL12XX_SPARE_B8			(REGISTERS_BASE + 0x543C)

#घोषणा WL12XX_PLL_PARAMETERS		(REGISTERS_BASE + 0x6040)
#घोषणा WL12XX_WU_COUNTER_PAUSE		(REGISTERS_BASE + 0x6008)
#घोषणा WL12XX_WELP_ARM_COMMAND		(REGISTERS_BASE + 0x6100)
#घोषणा WL12XX_DRPW_SCRATCH_START	(DRPW_BASE + 0x002C)

#घोषणा WL12XX_CMD_MBOX_ADDRESS		0x407B4

#घोषणा ACX_REG_EEPROM_START_BIT BIT(1)

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
#घोषणा WL12XX_REG_COMMAND_MAILBOX_PTR		(WL12XX_SCR_PAD0)

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
#घोषणा WL12XX_REG_EVENT_MAILBOX_PTR		(WL12XX_SCR_PAD1)

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
#घोषणा ACX_EE_CTL_REG                      EE_CTL
#घोषणा EE_WRITE                            0x00000001ul
#घोषणा EE_READ                             0x00000002ul

/*===============================================
  EEPROM Address  - 32bit RW
  ------------------------------------------
  This रेजिस्टर specअगरies the address
  within the EEPROM from/to which to पढ़ो/ग_लिखो data.
  ===============================================*/
#घोषणा ACX_EE_ADDR_REG                     EE_ADDR

/*===============================================
  EEPROM Data  - 32bit RW
  ------------------------------------------
  This रेजिस्टर either holds the पढ़ो 8 bits of
  data from the EEPROM or the ग_लिखो data
  to be written to the EEPROM.
  ===============================================*/
#घोषणा ACX_EE_DATA_REG                     EE_DATA

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

#घोषणा WL12XX_EEPROMLESS_IND		(WL12XX_SCR_PAD4)
#घोषणा USE_EEPROM                          0
#घोषणा NVS_DATA_BUNDARY_ALIGNMENT          4

/* Firmware image header size */
#घोषणा FW_HDR_SIZE 8

/******************************************************************************

    CHANNELS, BAND & REG DOMAINS definitions

******************************************************************************/

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

#घोषणा OCP_CMD_LOOP		32
#घोषणा OCP_CMD_WRITE		0x1
#घोषणा OCP_CMD_READ		0x2
#घोषणा OCP_READY_MASK		BIT(18)
#घोषणा OCP_STATUS_MASK		(BIT(16) | BIT(17))
#घोषणा OCP_STATUS_NO_RESP	0x00000
#घोषणा OCP_STATUS_OK		0x10000
#घोषणा OCP_STATUS_REQ_FAILED	0x20000
#घोषणा OCP_STATUS_RESP_ERROR	0x30000

#घोषणा OCP_REG_POLARITY     0x0064
#घोषणा OCP_REG_CLK_TYPE     0x0448
#घोषणा OCP_REG_CLK_POLARITY 0x0cb2
#घोषणा OCP_REG_CLK_PULL     0x0cb4

#घोषणा POLARITY_LOW         BIT(1)
#घोषणा NO_PULL              (BIT(14) | BIT(15))

#घोषणा FREF_CLK_TYPE_BITS     0xfffffe7f
#घोषणा CLK_REQ_PRCM           0x100
#घोषणा FREF_CLK_POLARITY_BITS 0xfffff8ff
#घोषणा CLK_REQ_OUTN_SEL       0x700

#घोषणा WU_COUNTER_PAUSE_VAL 0x3FF

/* PLL configuration algorithm क्रम wl128x */
#घोषणा SYS_CLK_CFG_REG              0x2200
/* Bit[0]   -  0-TCXO,  1-FREF */
#घोषणा MCS_PLL_CLK_SEL_FREF         BIT(0)
/* Bit[3:2] - 01-TCXO, 10-FREF */
#घोषणा WL_CLK_REQ_TYPE_FREF         BIT(3)
#घोषणा WL_CLK_REQ_TYPE_PG2          (BIT(3) | BIT(2))
/* Bit[4]   -  0-TCXO,  1-FREF */
#घोषणा PRCM_CM_EN_MUX_WLAN_FREF     BIT(4)

#घोषणा TCXO_ILOAD_INT_REG           0x2264
#घोषणा TCXO_CLK_DETECT_REG          0x2266

#घोषणा TCXO_DET_FAILED              BIT(4)

#घोषणा FREF_ILOAD_INT_REG           0x2084
#घोषणा FREF_CLK_DETECT_REG          0x2086
#घोषणा FREF_CLK_DETECT_FAIL         BIT(4)

/* Use this reg क्रम masking during driver access */
#घोषणा WL_SPARE_REG                 0x2320
#घोषणा WL_SPARE_VAL                 BIT(2)
/* Bit[6:5:3] -  mask wl ग_लिखो SYS_CLK_CFG[8:5:2:4] */
#घोषणा WL_SPARE_MASK_8526           (BIT(6) | BIT(5) | BIT(3))

#घोषणा PLL_LOCK_COUNTERS_REG        0xD8C
#घोषणा PLL_LOCK_COUNTERS_COEX       0x0F
#घोषणा PLL_LOCK_COUNTERS_MCS        0xF0
#घोषणा MCS_PLL_OVERRIDE_REG         0xD90
#घोषणा MCS_PLL_CONFIG_REG           0xD92
#घोषणा MCS_SEL_IN_FREQ_MASK         0x0070
#घोषणा MCS_SEL_IN_FREQ_SHIFT        4
#घोषणा MCS_PLL_CONFIG_REG_VAL       0x73
#घोषणा MCS_PLL_ENABLE_HP            (BIT(0) | BIT(1))

#घोषणा MCS_PLL_M_REG                0xD94
#घोषणा MCS_PLL_N_REG                0xD96
#घोषणा MCS_PLL_M_REG_VAL            0xC8
#घोषणा MCS_PLL_N_REG_VAL            0x07

#घोषणा SDIO_IO_DS                   0xd14

/* SDIO/wSPI DS configuration values */
क्रमागत अणु
	HCI_IO_DS_8MA = 0,
	HCI_IO_DS_4MA = 1, /* शेष */
	HCI_IO_DS_6MA = 2,
	HCI_IO_DS_2MA = 3,
पूर्ण;

/* end PLL configuration algorithm क्रम wl128x */

/*
 * Host Command Interrupt. Setting this bit masks
 * the पूर्णांकerrupt that the host issues to inक्रमm
 * the FW that it has sent a command
 * to the Wlan hardware Command Mailbox.
 */
#घोषणा WL12XX_INTR_TRIG_CMD		BIT(0)

/*
 * Host Event Acknowlegde Interrupt. The host
 * sets this bit to acknowledge that it received
 * the unsolicited inक्रमmation from the event
 * mailbox.
 */
#घोषणा WL12XX_INTR_TRIG_EVENT_ACK	BIT(1)

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

#घोषणा HI_CFG_DEF_VAL              \
	(HI_CFG_UART_ENABLE |        \
	HI_CFG_RST232_ENABLE |      \
	HI_CFG_CLOCK_REQ_SELECT |   \
	HI_CFG_HOST_INT_ENABLE)

#घोषणा WL127X_REG_FUSE_DATA_2_1	0x050a
#घोषणा WL128X_REG_FUSE_DATA_2_1	0x2152
#घोषणा PG_VER_MASK			0x3c
#घोषणा PG_VER_OFFSET			2

#घोषणा WL127X_PG_MAJOR_VER_MASK	0x3
#घोषणा WL127X_PG_MAJOR_VER_OFFSET	0x0
#घोषणा WL127X_PG_MINOR_VER_MASK	0xc
#घोषणा WL127X_PG_MINOR_VER_OFFSET	0x2

#घोषणा WL128X_PG_MAJOR_VER_MASK	0xc
#घोषणा WL128X_PG_MAJOR_VER_OFFSET	0x2
#घोषणा WL128X_PG_MINOR_VER_MASK	0x3
#घोषणा WL128X_PG_MINOR_VER_OFFSET	0x0

#घोषणा WL127X_PG_GET_MAJOR(pg_ver) ((pg_ver & WL127X_PG_MAJOR_VER_MASK) >> \
				     WL127X_PG_MAJOR_VER_OFFSET)
#घोषणा WL127X_PG_GET_MINOR(pg_ver) ((pg_ver & WL127X_PG_MINOR_VER_MASK) >> \
				     WL127X_PG_MINOR_VER_OFFSET)
#घोषणा WL128X_PG_GET_MAJOR(pg_ver) ((pg_ver & WL128X_PG_MAJOR_VER_MASK) >> \
				     WL128X_PG_MAJOR_VER_OFFSET)
#घोषणा WL128X_PG_GET_MINOR(pg_ver) ((pg_ver & WL128X_PG_MINOR_VER_MASK) >> \
				     WL128X_PG_MINOR_VER_OFFSET)

#घोषणा WL12XX_REG_FUSE_BD_ADDR_1	0x00310eb4
#घोषणा WL12XX_REG_FUSE_BD_ADDR_2	0x00310eb8

#पूर्ण_अगर
