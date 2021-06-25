<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt61pci
	Abstract: Data काष्ठाures and रेजिस्टरs क्रम the rt61pci module.
	Supported chipsets: RT2561, RT2561s, RT2661.
 */

#अगर_अघोषित RT61PCI_H
#घोषणा RT61PCI_H

/*
 * RT chip PCI IDs.
 */
#घोषणा RT2561s_PCI_ID			0x0301
#घोषणा RT2561_PCI_ID			0x0302
#घोषणा RT2661_PCI_ID			0x0401

/*
 * RF chip defines.
 */
#घोषणा RF5225				0x0001
#घोषणा RF5325				0x0002
#घोषणा RF2527				0x0003
#घोषणा RF2529				0x0004

/*
 * Signal inक्रमmation.
 * Default offset is required क्रम RSSI <-> dBm conversion.
 */
#घोषणा DEFAULT_RSSI_OFFSET		120

/*
 * Register layout inक्रमmation.
 */
#घोषणा CSR_REG_BASE			0x3000
#घोषणा CSR_REG_SIZE			0x04b0
#घोषणा EEPROM_BASE			0x0000
#घोषणा EEPROM_SIZE			0x0100
#घोषणा BBP_BASE			0x0000
#घोषणा BBP_SIZE			0x0080
#घोषणा RF_BASE				0x0004
#घोषणा RF_SIZE				0x0010

/*
 * Number of TX queues.
 */
#घोषणा NUM_TX_QUEUES			4

/*
 * PCI रेजिस्टरs.
 */

/*
 * HOST_CMD_CSR: For HOST to पूर्णांकerrupt embedded processor
 */
#घोषणा HOST_CMD_CSR			0x0008
#घोषणा HOST_CMD_CSR_HOST_COMMAND	FIELD32(0x0000007f)
#घोषणा HOST_CMD_CSR_INTERRUPT_MCU	FIELD32(0x00000080)

/*
 * MCU_CNTL_CSR
 * SELECT_BANK: Select 8051 program bank.
 * RESET: Enable 8051 reset state.
 * READY: Ready state क्रम 8051.
 */
#घोषणा MCU_CNTL_CSR			0x000c
#घोषणा MCU_CNTL_CSR_SELECT_BANK	FIELD32(0x00000001)
#घोषणा MCU_CNTL_CSR_RESET		FIELD32(0x00000002)
#घोषणा MCU_CNTL_CSR_READY		FIELD32(0x00000004)

/*
 * SOFT_RESET_CSR
 * FORCE_CLOCK_ON: Host क्रमce MAC घड़ी ON
 */
#घोषणा SOFT_RESET_CSR			0x0010
#घोषणा SOFT_RESET_CSR_FORCE_CLOCK_ON	FIELD32(0x00000002)

/*
 * MCU_INT_SOURCE_CSR: MCU पूर्णांकerrupt source/mask रेजिस्टर.
 */
#घोषणा MCU_INT_SOURCE_CSR		0x0014
#घोषणा MCU_INT_SOURCE_CSR_0		FIELD32(0x00000001)
#घोषणा MCU_INT_SOURCE_CSR_1		FIELD32(0x00000002)
#घोषणा MCU_INT_SOURCE_CSR_2		FIELD32(0x00000004)
#घोषणा MCU_INT_SOURCE_CSR_3		FIELD32(0x00000008)
#घोषणा MCU_INT_SOURCE_CSR_4		FIELD32(0x00000010)
#घोषणा MCU_INT_SOURCE_CSR_5		FIELD32(0x00000020)
#घोषणा MCU_INT_SOURCE_CSR_6		FIELD32(0x00000040)
#घोषणा MCU_INT_SOURCE_CSR_7		FIELD32(0x00000080)
#घोषणा MCU_INT_SOURCE_CSR_TWAKEUP	FIELD32(0x00000100)
#घोषणा MCU_INT_SOURCE_CSR_TBTT_EXPIRE	FIELD32(0x00000200)

/*
 * MCU_INT_MASK_CSR: MCU पूर्णांकerrupt source/mask रेजिस्टर.
 */
#घोषणा MCU_INT_MASK_CSR		0x0018
#घोषणा MCU_INT_MASK_CSR_0		FIELD32(0x00000001)
#घोषणा MCU_INT_MASK_CSR_1		FIELD32(0x00000002)
#घोषणा MCU_INT_MASK_CSR_2		FIELD32(0x00000004)
#घोषणा MCU_INT_MASK_CSR_3		FIELD32(0x00000008)
#घोषणा MCU_INT_MASK_CSR_4		FIELD32(0x00000010)
#घोषणा MCU_INT_MASK_CSR_5		FIELD32(0x00000020)
#घोषणा MCU_INT_MASK_CSR_6		FIELD32(0x00000040)
#घोषणा MCU_INT_MASK_CSR_7		FIELD32(0x00000080)
#घोषणा MCU_INT_MASK_CSR_TWAKEUP	FIELD32(0x00000100)
#घोषणा MCU_INT_MASK_CSR_TBTT_EXPIRE	FIELD32(0x00000200)

/*
 * PCI_USEC_CSR
 */
#घोषणा PCI_USEC_CSR			0x001c

/*
 * Security key table memory.
 * 16 entries 32-byte क्रम shared key table
 * 64 entries 32-byte क्रम pairwise key table
 * 64 entries 8-byte क्रम pairwise ta key table
 */
#घोषणा SHARED_KEY_TABLE_BASE		0x1000
#घोषणा PAIRWISE_KEY_TABLE_BASE		0x1200
#घोषणा PAIRWISE_TA_TABLE_BASE		0x1a00

#घोषणा SHARED_KEY_ENTRY(__idx) \
	(SHARED_KEY_TABLE_BASE + \
		((__idx) * माप(काष्ठा hw_key_entry)))
#घोषणा PAIRWISE_KEY_ENTRY(__idx) \
	(PAIRWISE_KEY_TABLE_BASE + \
		((__idx) * माप(काष्ठा hw_key_entry)))
#घोषणा PAIRWISE_TA_ENTRY(__idx) \
	(PAIRWISE_TA_TABLE_BASE + \
		((__idx) * माप(काष्ठा hw_pairwise_ta_entry)))

काष्ठा hw_key_entry अणु
	u8 key[16];
	u8 tx_mic[8];
	u8 rx_mic[8];
पूर्ण __packed;

काष्ठा hw_pairwise_ta_entry अणु
	u8 address[6];
	u8 cipher;
	u8 reserved;
पूर्ण __packed;

/*
 * Other on-chip shared memory space.
 */
#घोषणा HW_CIS_BASE			0x2000
#घोषणा HW_शून्य_BASE			0x2b00

/*
 * Since शून्य frame won't be that दीर्घ (256 byte),
 * We steal 16 tail bytes to save debugging settings.
 */
#घोषणा HW_DEBUG_SETTING_BASE		0x2bf0

/*
 * On-chip BEACON frame space.
 */
#घोषणा HW_BEACON_BASE0			0x2c00
#घोषणा HW_BEACON_BASE1			0x2d00
#घोषणा HW_BEACON_BASE2			0x2e00
#घोषणा HW_BEACON_BASE3			0x2f00

#घोषणा HW_BEACON_OFFSET(__index) \
	(HW_BEACON_BASE0 + (__index * 0x0100))

/*
 * HOST-MCU shared memory.
 */

/*
 * H2M_MAILBOX_CSR: Host-to-MCU Mailbox.
 */
#घोषणा H2M_MAILBOX_CSR			0x2100
#घोषणा H2M_MAILBOX_CSR_ARG0		FIELD32(0x000000ff)
#घोषणा H2M_MAILBOX_CSR_ARG1		FIELD32(0x0000ff00)
#घोषणा H2M_MAILBOX_CSR_CMD_TOKEN	FIELD32(0x00ff0000)
#घोषणा H2M_MAILBOX_CSR_OWNER		FIELD32(0xff000000)

/*
 * MCU_LEDCS: LED control क्रम MCU Mailbox.
 */
#घोषणा MCU_LEDCS_LED_MODE		FIELD16(0x001f)
#घोषणा MCU_LEDCS_RADIO_STATUS		FIELD16(0x0020)
#घोषणा MCU_LEDCS_LINK_BG_STATUS	FIELD16(0x0040)
#घोषणा MCU_LEDCS_LINK_A_STATUS		FIELD16(0x0080)
#घोषणा MCU_LEDCS_POLARITY_GPIO_0	FIELD16(0x0100)
#घोषणा MCU_LEDCS_POLARITY_GPIO_1	FIELD16(0x0200)
#घोषणा MCU_LEDCS_POLARITY_GPIO_2	FIELD16(0x0400)
#घोषणा MCU_LEDCS_POLARITY_GPIO_3	FIELD16(0x0800)
#घोषणा MCU_LEDCS_POLARITY_GPIO_4	FIELD16(0x1000)
#घोषणा MCU_LEDCS_POLARITY_ACT		FIELD16(0x2000)
#घोषणा MCU_LEDCS_POLARITY_READY_BG	FIELD16(0x4000)
#घोषणा MCU_LEDCS_POLARITY_READY_A	FIELD16(0x8000)

/*
 * M2H_CMD_DONE_CSR.
 */
#घोषणा M2H_CMD_DONE_CSR		0x2104

/*
 * MCU_TXOP_ARRAY_BASE.
 */
#घोषणा MCU_TXOP_ARRAY_BASE		0x2110

/*
 * MAC Control/Status Registers(CSR).
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * MAC_CSR0: ASIC revision number.
 */
#घोषणा MAC_CSR0			0x3000
#घोषणा MAC_CSR0_REVISION		FIELD32(0x0000000f)
#घोषणा MAC_CSR0_CHIPSET		FIELD32(0x000ffff0)

/*
 * MAC_CSR1: System control रेजिस्टर.
 * SOFT_RESET: Software reset bit, 1: reset, 0: normal.
 * BBP_RESET: Hardware reset BBP.
 * HOST_READY: Host is पढ़ोy after initialization, 1: पढ़ोy.
 */
#घोषणा MAC_CSR1			0x3004
#घोषणा MAC_CSR1_SOFT_RESET		FIELD32(0x00000001)
#घोषणा MAC_CSR1_BBP_RESET		FIELD32(0x00000002)
#घोषणा MAC_CSR1_HOST_READY		FIELD32(0x00000004)

/*
 * MAC_CSR2: STA MAC रेजिस्टर 0.
 */
#घोषणा MAC_CSR2			0x3008
#घोषणा MAC_CSR2_BYTE0			FIELD32(0x000000ff)
#घोषणा MAC_CSR2_BYTE1			FIELD32(0x0000ff00)
#घोषणा MAC_CSR2_BYTE2			FIELD32(0x00ff0000)
#घोषणा MAC_CSR2_BYTE3			FIELD32(0xff000000)

/*
 * MAC_CSR3: STA MAC रेजिस्टर 1.
 * UNICAST_TO_ME_MASK:
 *	Used to mask off bits from byte 5 of the MAC address
 *	to determine the UNICAST_TO_ME bit क्रम RX frames.
 *	The full mask is complemented by BSS_ID_MASK:
 *		MASK = BSS_ID_MASK & UNICAST_TO_ME_MASK
 */
#घोषणा MAC_CSR3			0x300c
#घोषणा MAC_CSR3_BYTE4			FIELD32(0x000000ff)
#घोषणा MAC_CSR3_BYTE5			FIELD32(0x0000ff00)
#घोषणा MAC_CSR3_UNICAST_TO_ME_MASK	FIELD32(0x00ff0000)

/*
 * MAC_CSR4: BSSID रेजिस्टर 0.
 */
#घोषणा MAC_CSR4			0x3010
#घोषणा MAC_CSR4_BYTE0			FIELD32(0x000000ff)
#घोषणा MAC_CSR4_BYTE1			FIELD32(0x0000ff00)
#घोषणा MAC_CSR4_BYTE2			FIELD32(0x00ff0000)
#घोषणा MAC_CSR4_BYTE3			FIELD32(0xff000000)

/*
 * MAC_CSR5: BSSID रेजिस्टर 1.
 * BSS_ID_MASK:
 *	This mask is used to mask off bits 0 and 1 of byte 5 of the
 *	BSSID. This will make sure that those bits will be ignored
 *	when determining the MY_BSS of RX frames.
 *		0: 1-BSSID mode (BSS index = 0)
 *		1: 2-BSSID mode (BSS index: Byte5, bit 0)
 *		2: 2-BSSID mode (BSS index: byte5, bit 1)
 *		3: 4-BSSID mode (BSS index: byte5, bit 0 - 1)
 */
#घोषणा MAC_CSR5			0x3014
#घोषणा MAC_CSR5_BYTE4			FIELD32(0x000000ff)
#घोषणा MAC_CSR5_BYTE5			FIELD32(0x0000ff00)
#घोषणा MAC_CSR5_BSS_ID_MASK		FIELD32(0x00ff0000)

/*
 * MAC_CSR6: Maximum frame length रेजिस्टर.
 */
#घोषणा MAC_CSR6			0x3018
#घोषणा MAC_CSR6_MAX_FRAME_UNIT		FIELD32(0x00000fff)

/*
 * MAC_CSR7: Reserved
 */
#घोषणा MAC_CSR7			0x301c

/*
 * MAC_CSR8: SIFS/EIFS रेजिस्टर.
 * All units are in US.
 */
#घोषणा MAC_CSR8			0x3020
#घोषणा MAC_CSR8_SIFS			FIELD32(0x000000ff)
#घोषणा MAC_CSR8_SIFS_AFTER_RX_OFDM	FIELD32(0x0000ff00)
#घोषणा MAC_CSR8_EIFS			FIELD32(0xffff0000)

/*
 * MAC_CSR9: Back-Off control रेजिस्टर.
 * SLOT_TIME: Slot समय, शेष is 20us क्रम 802.11BG.
 * CWMIN: Bit क्रम Cwmin. शेष Cwmin is 31 (2^5 - 1).
 * CWMAX: Bit क्रम Cwmax, शेष Cwmax is 1023 (2^10 - 1).
 * CW_SELECT: 1: CWmin/Cwmax select from रेजिस्टर, 0:select from TxD.
 */
#घोषणा MAC_CSR9			0x3024
#घोषणा MAC_CSR9_SLOT_TIME		FIELD32(0x000000ff)
#घोषणा MAC_CSR9_CWMIN			FIELD32(0x00000f00)
#घोषणा MAC_CSR9_CWMAX			FIELD32(0x0000f000)
#घोषणा MAC_CSR9_CW_SELECT		FIELD32(0x00010000)

/*
 * MAC_CSR10: Power state configuration.
 */
#घोषणा MAC_CSR10			0x3028

/*
 * MAC_CSR11: Power saving transition समय रेजिस्टर.
 * DELAY_AFTER_TBCN: Delay after Tbcn expired in units of TU.
 * TBCN_BEFORE_WAKEUP: Number of beacon beक्रमe wakeup.
 * WAKEUP_LATENCY: In unit of TU.
 */
#घोषणा MAC_CSR11			0x302c
#घोषणा MAC_CSR11_DELAY_AFTER_TBCN	FIELD32(0x000000ff)
#घोषणा MAC_CSR11_TBCN_BEFORE_WAKEUP	FIELD32(0x00007f00)
#घोषणा MAC_CSR11_AUTOWAKE		FIELD32(0x00008000)
#घोषणा MAC_CSR11_WAKEUP_LATENCY	FIELD32(0x000f0000)

/*
 * MAC_CSR12: Manual घातer control / status रेजिस्टर (merge CSR20 & PWRCSR1).
 * CURRENT_STATE: 0:sleep, 1:awake.
 * FORCE_WAKEUP: This has higher priority than PUT_TO_SLEEP.
 * BBP_CURRENT_STATE: 0: BBP sleep, 1: BBP awake.
 */
#घोषणा MAC_CSR12			0x3030
#घोषणा MAC_CSR12_CURRENT_STATE		FIELD32(0x00000001)
#घोषणा MAC_CSR12_PUT_TO_SLEEP		FIELD32(0x00000002)
#घोषणा MAC_CSR12_FORCE_WAKEUP		FIELD32(0x00000004)
#घोषणा MAC_CSR12_BBP_CURRENT_STATE	FIELD32(0x00000008)

/*
 * MAC_CSR13: GPIO.
 *	MAC_CSR13_VALx: GPIO value
 *	MAC_CSR13_सूचीx: GPIO direction: 0 = output; 1 = input
 */
#घोषणा MAC_CSR13			0x3034
#घोषणा MAC_CSR13_VAL0			FIELD32(0x00000001)
#घोषणा MAC_CSR13_VAL1			FIELD32(0x00000002)
#घोषणा MAC_CSR13_VAL2			FIELD32(0x00000004)
#घोषणा MAC_CSR13_VAL3			FIELD32(0x00000008)
#घोषणा MAC_CSR13_VAL4			FIELD32(0x00000010)
#घोषणा MAC_CSR13_VAL5			FIELD32(0x00000020)
#घोषणा MAC_CSR13_सूची0			FIELD32(0x00000100)
#घोषणा MAC_CSR13_सूची1			FIELD32(0x00000200)
#घोषणा MAC_CSR13_सूची2			FIELD32(0x00000400)
#घोषणा MAC_CSR13_सूची3			FIELD32(0x00000800)
#घोषणा MAC_CSR13_सूची4			FIELD32(0x00001000)
#घोषणा MAC_CSR13_सूची5			FIELD32(0x00002000)

/*
 * MAC_CSR14: LED control रेजिस्टर.
 * ON_PERIOD: On period, शेष 70ms.
 * OFF_PERIOD: Off period, शेष 30ms.
 * HW_LED: HW TX activity, 1: normal OFF, 0: normal ON.
 * SW_LED: s/w LED, 1: ON, 0: OFF.
 * HW_LED_POLARITY: 0: active low, 1: active high.
 */
#घोषणा MAC_CSR14			0x3038
#घोषणा MAC_CSR14_ON_PERIOD		FIELD32(0x000000ff)
#घोषणा MAC_CSR14_OFF_PERIOD		FIELD32(0x0000ff00)
#घोषणा MAC_CSR14_HW_LED		FIELD32(0x00010000)
#घोषणा MAC_CSR14_SW_LED		FIELD32(0x00020000)
#घोषणा MAC_CSR14_HW_LED_POLARITY	FIELD32(0x00040000)
#घोषणा MAC_CSR14_SW_LED2		FIELD32(0x00080000)

/*
 * MAC_CSR15: NAV control.
 */
#घोषणा MAC_CSR15			0x303c

/*
 * TXRX control रेजिस्टरs.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * TXRX_CSR0: TX/RX configuration रेजिस्टर.
 * TSF_OFFSET: Default is 24.
 * AUTO_TX_SEQ: 1: ASIC स्वतः replace sequence nr in outgoing frame.
 * DISABLE_RX: Disable Rx engine.
 * DROP_CRC: Drop CRC error.
 * DROP_PHYSICAL: Drop physical error.
 * DROP_CONTROL: Drop control frame.
 * DROP_NOT_TO_ME: Drop not to me unicast frame.
 * DROP_TO_DS: Drop fram ToDs bit is true.
 * DROP_VERSION_ERROR: Drop version error frame.
 * DROP_MULTICAST: Drop multicast frames.
 * DROP_BORADCAST: Drop broadcast frames.
 * DROP_ACK_CTS: Drop received ACK and CTS.
 */
#घोषणा TXRX_CSR0			0x3040
#घोषणा TXRX_CSR0_RX_ACK_TIMEOUT	FIELD32(0x000001ff)
#घोषणा TXRX_CSR0_TSF_OFFSET		FIELD32(0x00007e00)
#घोषणा TXRX_CSR0_AUTO_TX_SEQ		FIELD32(0x00008000)
#घोषणा TXRX_CSR0_DISABLE_RX		FIELD32(0x00010000)
#घोषणा TXRX_CSR0_DROP_CRC		FIELD32(0x00020000)
#घोषणा TXRX_CSR0_DROP_PHYSICAL		FIELD32(0x00040000)
#घोषणा TXRX_CSR0_DROP_CONTROL		FIELD32(0x00080000)
#घोषणा TXRX_CSR0_DROP_NOT_TO_ME	FIELD32(0x00100000)
#घोषणा TXRX_CSR0_DROP_TO_DS		FIELD32(0x00200000)
#घोषणा TXRX_CSR0_DROP_VERSION_ERROR	FIELD32(0x00400000)
#घोषणा TXRX_CSR0_DROP_MULTICAST	FIELD32(0x00800000)
#घोषणा TXRX_CSR0_DROP_BROADCAST	FIELD32(0x01000000)
#घोषणा TXRX_CSR0_DROP_ACK_CTS		FIELD32(0x02000000)
#घोषणा TXRX_CSR0_TX_WITHOUT_WAITING	FIELD32(0x04000000)

/*
 * TXRX_CSR1
 */
#घोषणा TXRX_CSR1			0x3044
#घोषणा TXRX_CSR1_BBP_ID0		FIELD32(0x0000007f)
#घोषणा TXRX_CSR1_BBP_ID0_VALID		FIELD32(0x00000080)
#घोषणा TXRX_CSR1_BBP_ID1		FIELD32(0x00007f00)
#घोषणा TXRX_CSR1_BBP_ID1_VALID		FIELD32(0x00008000)
#घोषणा TXRX_CSR1_BBP_ID2		FIELD32(0x007f0000)
#घोषणा TXRX_CSR1_BBP_ID2_VALID		FIELD32(0x00800000)
#घोषणा TXRX_CSR1_BBP_ID3		FIELD32(0x7f000000)
#घोषणा TXRX_CSR1_BBP_ID3_VALID		FIELD32(0x80000000)

/*
 * TXRX_CSR2
 */
#घोषणा TXRX_CSR2			0x3048
#घोषणा TXRX_CSR2_BBP_ID0		FIELD32(0x0000007f)
#घोषणा TXRX_CSR2_BBP_ID0_VALID		FIELD32(0x00000080)
#घोषणा TXRX_CSR2_BBP_ID1		FIELD32(0x00007f00)
#घोषणा TXRX_CSR2_BBP_ID1_VALID		FIELD32(0x00008000)
#घोषणा TXRX_CSR2_BBP_ID2		FIELD32(0x007f0000)
#घोषणा TXRX_CSR2_BBP_ID2_VALID		FIELD32(0x00800000)
#घोषणा TXRX_CSR2_BBP_ID3		FIELD32(0x7f000000)
#घोषणा TXRX_CSR2_BBP_ID3_VALID		FIELD32(0x80000000)

/*
 * TXRX_CSR3
 */
#घोषणा TXRX_CSR3			0x304c
#घोषणा TXRX_CSR3_BBP_ID0		FIELD32(0x0000007f)
#घोषणा TXRX_CSR3_BBP_ID0_VALID		FIELD32(0x00000080)
#घोषणा TXRX_CSR3_BBP_ID1		FIELD32(0x00007f00)
#घोषणा TXRX_CSR3_BBP_ID1_VALID		FIELD32(0x00008000)
#घोषणा TXRX_CSR3_BBP_ID2		FIELD32(0x007f0000)
#घोषणा TXRX_CSR3_BBP_ID2_VALID		FIELD32(0x00800000)
#घोषणा TXRX_CSR3_BBP_ID3		FIELD32(0x7f000000)
#घोषणा TXRX_CSR3_BBP_ID3_VALID		FIELD32(0x80000000)

/*
 * TXRX_CSR4: Auto-Responder/Tx-retry रेजिस्टर.
 * AUTORESPOND_PREAMBLE: 0:दीर्घ, 1:लघु preamble.
 * OFDM_TX_RATE_DOWN: 1:enable.
 * OFDM_TX_RATE_STEP: 0:1-step, 1: 2-step, 2:3-step, 3:4-step.
 * OFDM_TX_FALLBACK_CCK: 0: Fallback to OFDM 6M only, 1: Fallback to CCK 1M,2M.
 */
#घोषणा TXRX_CSR4			0x3050
#घोषणा TXRX_CSR4_TX_ACK_TIMEOUT	FIELD32(0x000000ff)
#घोषणा TXRX_CSR4_CNTL_ACK_POLICY	FIELD32(0x00000700)
#घोषणा TXRX_CSR4_ACK_CTS_PSM		FIELD32(0x00010000)
#घोषणा TXRX_CSR4_AUTORESPOND_ENABLE	FIELD32(0x00020000)
#घोषणा TXRX_CSR4_AUTORESPOND_PREAMBLE	FIELD32(0x00040000)
#घोषणा TXRX_CSR4_OFDM_TX_RATE_DOWN	FIELD32(0x00080000)
#घोषणा TXRX_CSR4_OFDM_TX_RATE_STEP	FIELD32(0x00300000)
#घोषणा TXRX_CSR4_OFDM_TX_FALLBACK_CCK	FIELD32(0x00400000)
#घोषणा TXRX_CSR4_LONG_RETRY_LIMIT	FIELD32(0x0f000000)
#घोषणा TXRX_CSR4_SHORT_RETRY_LIMIT	FIELD32(0xf0000000)

/*
 * TXRX_CSR5
 */
#घोषणा TXRX_CSR5			0x3054

/*
 * TXRX_CSR6: ACK/CTS payload consumed समय
 */
#घोषणा TXRX_CSR6			0x3058

/*
 * TXRX_CSR7: OFDM ACK/CTS payload consumed समय क्रम 6/9/12/18 mbps.
 */
#घोषणा TXRX_CSR7			0x305c
#घोषणा TXRX_CSR7_ACK_CTS_6MBS		FIELD32(0x000000ff)
#घोषणा TXRX_CSR7_ACK_CTS_9MBS		FIELD32(0x0000ff00)
#घोषणा TXRX_CSR7_ACK_CTS_12MBS		FIELD32(0x00ff0000)
#घोषणा TXRX_CSR7_ACK_CTS_18MBS		FIELD32(0xff000000)

/*
 * TXRX_CSR8: OFDM ACK/CTS payload consumed समय क्रम 24/36/48/54 mbps.
 */
#घोषणा TXRX_CSR8			0x3060
#घोषणा TXRX_CSR8_ACK_CTS_24MBS		FIELD32(0x000000ff)
#घोषणा TXRX_CSR8_ACK_CTS_36MBS		FIELD32(0x0000ff00)
#घोषणा TXRX_CSR8_ACK_CTS_48MBS		FIELD32(0x00ff0000)
#घोषणा TXRX_CSR8_ACK_CTS_54MBS		FIELD32(0xff000000)

/*
 * TXRX_CSR9: Synchronization control रेजिस्टर.
 * BEACON_INTERVAL: In unit of 1/16 TU.
 * TSF_TICKING: Enable TSF स्वतः counting.
 * TSF_SYNC: Tsf sync, 0: disable, 1: infra, 2: ad-hoc/master mode.
 * BEACON_GEN: Enable beacon generator.
 */
#घोषणा TXRX_CSR9			0x3064
#घोषणा TXRX_CSR9_BEACON_INTERVAL	FIELD32(0x0000ffff)
#घोषणा TXRX_CSR9_TSF_TICKING		FIELD32(0x00010000)
#घोषणा TXRX_CSR9_TSF_SYNC		FIELD32(0x00060000)
#घोषणा TXRX_CSR9_TBTT_ENABLE		FIELD32(0x00080000)
#घोषणा TXRX_CSR9_BEACON_GEN		FIELD32(0x00100000)
#घोषणा TXRX_CSR9_TIMESTAMP_COMPENSATE	FIELD32(0xff000000)

/*
 * TXRX_CSR10: BEACON alignment.
 */
#घोषणा TXRX_CSR10			0x3068

/*
 * TXRX_CSR11: AES mask.
 */
#घोषणा TXRX_CSR11			0x306c

/*
 * TXRX_CSR12: TSF low 32.
 */
#घोषणा TXRX_CSR12			0x3070
#घोषणा TXRX_CSR12_LOW_TSFTIMER		FIELD32(0xffffffff)

/*
 * TXRX_CSR13: TSF high 32.
 */
#घोषणा TXRX_CSR13			0x3074
#घोषणा TXRX_CSR13_HIGH_TSFTIMER	FIELD32(0xffffffff)

/*
 * TXRX_CSR14: TBTT समयr.
 */
#घोषणा TXRX_CSR14			0x3078

/*
 * TXRX_CSR15: TKIP MIC priority byte "AND" mask.
 */
#घोषणा TXRX_CSR15			0x307c

/*
 * PHY control रेजिस्टरs.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * PHY_CSR0: RF/PS control.
 */
#घोषणा PHY_CSR0			0x3080
#घोषणा PHY_CSR0_PA_PE_BG		FIELD32(0x00010000)
#घोषणा PHY_CSR0_PA_PE_A		FIELD32(0x00020000)

/*
 * PHY_CSR1
 */
#घोषणा PHY_CSR1			0x3084

/*
 * PHY_CSR2: Pre-TX BBP control.
 */
#घोषणा PHY_CSR2			0x3088

/*
 * PHY_CSR3: BBP serial control रेजिस्टर.
 * VALUE: Register value to program पूर्णांकo BBP.
 * REG_NUM: Selected BBP रेजिस्टर.
 * READ_CONTROL: 0: Write BBP, 1: Read BBP.
 * BUSY: 1: ASIC is busy execute BBP programming.
 */
#घोषणा PHY_CSR3			0x308c
#घोषणा PHY_CSR3_VALUE			FIELD32(0x000000ff)
#घोषणा PHY_CSR3_REGNUM			FIELD32(0x00007f00)
#घोषणा PHY_CSR3_READ_CONTROL		FIELD32(0x00008000)
#घोषणा PHY_CSR3_BUSY			FIELD32(0x00010000)

/*
 * PHY_CSR4: RF serial control रेजिस्टर
 * VALUE: Register value (include रेजिस्टर id) serial out to RF/IF chip.
 * NUMBER_OF_BITS: Number of bits used in RFRegValue (I:20, RFMD:22).
 * IF_SELECT: 1: select IF to program, 0: select RF to program.
 * PLL_LD: RF PLL_LD status.
 * BUSY: 1: ASIC is busy execute RF programming.
 */
#घोषणा PHY_CSR4			0x3090
#घोषणा PHY_CSR4_VALUE			FIELD32(0x00ffffff)
#घोषणा PHY_CSR4_NUMBER_OF_BITS		FIELD32(0x1f000000)
#घोषणा PHY_CSR4_IF_SELECT		FIELD32(0x20000000)
#घोषणा PHY_CSR4_PLL_LD			FIELD32(0x40000000)
#घोषणा PHY_CSR4_BUSY			FIELD32(0x80000000)

/*
 * PHY_CSR5: RX to TX संकेत चयन timing control.
 */
#घोषणा PHY_CSR5			0x3094
#घोषणा PHY_CSR5_IQ_FLIP		FIELD32(0x00000004)

/*
 * PHY_CSR6: TX to RX संकेत timing control.
 */
#घोषणा PHY_CSR6			0x3098
#घोषणा PHY_CSR6_IQ_FLIP		FIELD32(0x00000004)

/*
 * PHY_CSR7: TX DAC चयनing timing control.
 */
#घोषणा PHY_CSR7			0x309c

/*
 * Security control रेजिस्टर.
 */

/*
 * SEC_CSR0: Shared key table control.
 */
#घोषणा SEC_CSR0			0x30a0
#घोषणा SEC_CSR0_BSS0_KEY0_VALID	FIELD32(0x00000001)
#घोषणा SEC_CSR0_BSS0_KEY1_VALID	FIELD32(0x00000002)
#घोषणा SEC_CSR0_BSS0_KEY2_VALID	FIELD32(0x00000004)
#घोषणा SEC_CSR0_BSS0_KEY3_VALID	FIELD32(0x00000008)
#घोषणा SEC_CSR0_BSS1_KEY0_VALID	FIELD32(0x00000010)
#घोषणा SEC_CSR0_BSS1_KEY1_VALID	FIELD32(0x00000020)
#घोषणा SEC_CSR0_BSS1_KEY2_VALID	FIELD32(0x00000040)
#घोषणा SEC_CSR0_BSS1_KEY3_VALID	FIELD32(0x00000080)
#घोषणा SEC_CSR0_BSS2_KEY0_VALID	FIELD32(0x00000100)
#घोषणा SEC_CSR0_BSS2_KEY1_VALID	FIELD32(0x00000200)
#घोषणा SEC_CSR0_BSS2_KEY2_VALID	FIELD32(0x00000400)
#घोषणा SEC_CSR0_BSS2_KEY3_VALID	FIELD32(0x00000800)
#घोषणा SEC_CSR0_BSS3_KEY0_VALID	FIELD32(0x00001000)
#घोषणा SEC_CSR0_BSS3_KEY1_VALID	FIELD32(0x00002000)
#घोषणा SEC_CSR0_BSS3_KEY2_VALID	FIELD32(0x00004000)
#घोषणा SEC_CSR0_BSS3_KEY3_VALID	FIELD32(0x00008000)

/*
 * SEC_CSR1: Shared key table security mode रेजिस्टर.
 */
#घोषणा SEC_CSR1			0x30a4
#घोषणा SEC_CSR1_BSS0_KEY0_CIPHER_ALG	FIELD32(0x00000007)
#घोषणा SEC_CSR1_BSS0_KEY1_CIPHER_ALG	FIELD32(0x00000070)
#घोषणा SEC_CSR1_BSS0_KEY2_CIPHER_ALG	FIELD32(0x00000700)
#घोषणा SEC_CSR1_BSS0_KEY3_CIPHER_ALG	FIELD32(0x00007000)
#घोषणा SEC_CSR1_BSS1_KEY0_CIPHER_ALG	FIELD32(0x00070000)
#घोषणा SEC_CSR1_BSS1_KEY1_CIPHER_ALG	FIELD32(0x00700000)
#घोषणा SEC_CSR1_BSS1_KEY2_CIPHER_ALG	FIELD32(0x07000000)
#घोषणा SEC_CSR1_BSS1_KEY3_CIPHER_ALG	FIELD32(0x70000000)

/*
 * Pairwise key table valid biपंचांगap रेजिस्टरs.
 * SEC_CSR2: pairwise key table valid biपंचांगap 0.
 * SEC_CSR3: pairwise key table valid biपंचांगap 1.
 */
#घोषणा SEC_CSR2			0x30a8
#घोषणा SEC_CSR3			0x30ac

/*
 * SEC_CSR4: Pairwise key table lookup control.
 */
#घोषणा SEC_CSR4			0x30b0
#घोषणा SEC_CSR4_ENABLE_BSS0		FIELD32(0x00000001)
#घोषणा SEC_CSR4_ENABLE_BSS1		FIELD32(0x00000002)
#घोषणा SEC_CSR4_ENABLE_BSS2		FIELD32(0x00000004)
#घोषणा SEC_CSR4_ENABLE_BSS3		FIELD32(0x00000008)

/*
 * SEC_CSR5: shared key table security mode रेजिस्टर.
 */
#घोषणा SEC_CSR5			0x30b4
#घोषणा SEC_CSR5_BSS2_KEY0_CIPHER_ALG	FIELD32(0x00000007)
#घोषणा SEC_CSR5_BSS2_KEY1_CIPHER_ALG	FIELD32(0x00000070)
#घोषणा SEC_CSR5_BSS2_KEY2_CIPHER_ALG	FIELD32(0x00000700)
#घोषणा SEC_CSR5_BSS2_KEY3_CIPHER_ALG	FIELD32(0x00007000)
#घोषणा SEC_CSR5_BSS3_KEY0_CIPHER_ALG	FIELD32(0x00070000)
#घोषणा SEC_CSR5_BSS3_KEY1_CIPHER_ALG	FIELD32(0x00700000)
#घोषणा SEC_CSR5_BSS3_KEY2_CIPHER_ALG	FIELD32(0x07000000)
#घोषणा SEC_CSR5_BSS3_KEY3_CIPHER_ALG	FIELD32(0x70000000)

/*
 * STA control रेजिस्टरs.
 */

/*
 * STA_CSR0: RX PLCP error count & RX FCS error count.
 */
#घोषणा STA_CSR0			0x30c0
#घोषणा STA_CSR0_FCS_ERROR		FIELD32(0x0000ffff)
#घोषणा STA_CSR0_PLCP_ERROR		FIELD32(0xffff0000)

/*
 * STA_CSR1: RX False CCA count & RX LONG frame count.
 */
#घोषणा STA_CSR1			0x30c4
#घोषणा STA_CSR1_PHYSICAL_ERROR		FIELD32(0x0000ffff)
#घोषणा STA_CSR1_FALSE_CCA_ERROR	FIELD32(0xffff0000)

/*
 * STA_CSR2: TX Beacon count and RX FIFO overflow count.
 */
#घोषणा STA_CSR2			0x30c8
#घोषणा STA_CSR2_RX_FIFO_OVERFLOW_COUNT	FIELD32(0x0000ffff)
#घोषणा STA_CSR2_RX_OVERFLOW_COUNT	FIELD32(0xffff0000)

/*
 * STA_CSR3: TX Beacon count.
 */
#घोषणा STA_CSR3			0x30cc
#घोषणा STA_CSR3_TX_BEACON_COUNT	FIELD32(0x0000ffff)

/*
 * STA_CSR4: TX Result status रेजिस्टर.
 * VALID: 1:This रेजिस्टर contains a valid TX result.
 */
#घोषणा STA_CSR4			0x30d0
#घोषणा STA_CSR4_VALID			FIELD32(0x00000001)
#घोषणा STA_CSR4_TX_RESULT		FIELD32(0x0000000e)
#घोषणा STA_CSR4_RETRY_COUNT		FIELD32(0x000000f0)
#घोषणा STA_CSR4_PID_SUBTYPE		FIELD32(0x00001f00)
#घोषणा STA_CSR4_PID_TYPE		FIELD32(0x0000e000)
#घोषणा STA_CSR4_TXRATE			FIELD32(0x000f0000)

/*
 * QOS control रेजिस्टरs.
 */

/*
 * QOS_CSR0: TXOP holder MAC address रेजिस्टर.
 */
#घोषणा QOS_CSR0			0x30e0
#घोषणा QOS_CSR0_BYTE0			FIELD32(0x000000ff)
#घोषणा QOS_CSR0_BYTE1			FIELD32(0x0000ff00)
#घोषणा QOS_CSR0_BYTE2			FIELD32(0x00ff0000)
#घोषणा QOS_CSR0_BYTE3			FIELD32(0xff000000)

/*
 * QOS_CSR1: TXOP holder MAC address रेजिस्टर.
 */
#घोषणा QOS_CSR1			0x30e4
#घोषणा QOS_CSR1_BYTE4			FIELD32(0x000000ff)
#घोषणा QOS_CSR1_BYTE5			FIELD32(0x0000ff00)

/*
 * QOS_CSR2: TXOP holder समयout रेजिस्टर.
 */
#घोषणा QOS_CSR2			0x30e8

/*
 * RX QOS-CFPOLL MAC address रेजिस्टर.
 * QOS_CSR3: RX QOS-CFPOLL MAC address 0.
 * QOS_CSR4: RX QOS-CFPOLL MAC address 1.
 */
#घोषणा QOS_CSR3			0x30ec
#घोषणा QOS_CSR4			0x30f0

/*
 * QOS_CSR5: "QosControl" field of the RX QOS-CFPOLL.
 */
#घोषणा QOS_CSR5			0x30f4

/*
 * Host DMA रेजिस्टरs.
 */

/*
 * AC0_BASE_CSR: AC_VO base address.
 */
#घोषणा AC0_BASE_CSR			0x3400
#घोषणा AC0_BASE_CSR_RING_REGISTER	FIELD32(0xffffffff)

/*
 * AC1_BASE_CSR: AC_VI base address.
 */
#घोषणा AC1_BASE_CSR			0x3404
#घोषणा AC1_BASE_CSR_RING_REGISTER	FIELD32(0xffffffff)

/*
 * AC2_BASE_CSR: AC_BE base address.
 */
#घोषणा AC2_BASE_CSR			0x3408
#घोषणा AC2_BASE_CSR_RING_REGISTER	FIELD32(0xffffffff)

/*
 * AC3_BASE_CSR: AC_BK base address.
 */
#घोषणा AC3_BASE_CSR			0x340c
#घोषणा AC3_BASE_CSR_RING_REGISTER	FIELD32(0xffffffff)

/*
 * MGMT_BASE_CSR: MGMT ring base address.
 */
#घोषणा MGMT_BASE_CSR			0x3410
#घोषणा MGMT_BASE_CSR_RING_REGISTER	FIELD32(0xffffffff)

/*
 * TX_RING_CSR0: TX Ring size क्रम AC_VO, AC_VI, AC_BE, AC_BK.
 */
#घोषणा TX_RING_CSR0			0x3418
#घोषणा TX_RING_CSR0_AC0_RING_SIZE	FIELD32(0x000000ff)
#घोषणा TX_RING_CSR0_AC1_RING_SIZE	FIELD32(0x0000ff00)
#घोषणा TX_RING_CSR0_AC2_RING_SIZE	FIELD32(0x00ff0000)
#घोषणा TX_RING_CSR0_AC3_RING_SIZE	FIELD32(0xff000000)

/*
 * TX_RING_CSR1: TX Ring size क्रम MGMT Ring, HCCA Ring
 * TXD_SIZE: In unit of 32-bit.
 */
#घोषणा TX_RING_CSR1			0x341c
#घोषणा TX_RING_CSR1_MGMT_RING_SIZE	FIELD32(0x000000ff)
#घोषणा TX_RING_CSR1_HCCA_RING_SIZE	FIELD32(0x0000ff00)
#घोषणा TX_RING_CSR1_TXD_SIZE		FIELD32(0x003f0000)

/*
 * AIFSN_CSR: AIFSN क्रम each EDCA AC.
 * AIFSN0: For AC_VO.
 * AIFSN1: For AC_VI.
 * AIFSN2: For AC_BE.
 * AIFSN3: For AC_BK.
 */
#घोषणा AIFSN_CSR			0x3420
#घोषणा AIFSN_CSR_AIFSN0		FIELD32(0x0000000f)
#घोषणा AIFSN_CSR_AIFSN1		FIELD32(0x000000f0)
#घोषणा AIFSN_CSR_AIFSN2		FIELD32(0x00000f00)
#घोषणा AIFSN_CSR_AIFSN3		FIELD32(0x0000f000)

/*
 * CWMIN_CSR: CWmin क्रम each EDCA AC.
 * CWMIN0: For AC_VO.
 * CWMIN1: For AC_VI.
 * CWMIN2: For AC_BE.
 * CWMIN3: For AC_BK.
 */
#घोषणा CWMIN_CSR			0x3424
#घोषणा CWMIN_CSR_CWMIN0		FIELD32(0x0000000f)
#घोषणा CWMIN_CSR_CWMIN1		FIELD32(0x000000f0)
#घोषणा CWMIN_CSR_CWMIN2		FIELD32(0x00000f00)
#घोषणा CWMIN_CSR_CWMIN3		FIELD32(0x0000f000)

/*
 * CWMAX_CSR: CWmax क्रम each EDCA AC.
 * CWMAX0: For AC_VO.
 * CWMAX1: For AC_VI.
 * CWMAX2: For AC_BE.
 * CWMAX3: For AC_BK.
 */
#घोषणा CWMAX_CSR			0x3428
#घोषणा CWMAX_CSR_CWMAX0		FIELD32(0x0000000f)
#घोषणा CWMAX_CSR_CWMAX1		FIELD32(0x000000f0)
#घोषणा CWMAX_CSR_CWMAX2		FIELD32(0x00000f00)
#घोषणा CWMAX_CSR_CWMAX3		FIELD32(0x0000f000)

/*
 * TX_DMA_DST_CSR: TX DMA destination
 * 0: TX ring0, 1: TX ring1, 2: TX ring2 3: invalid
 */
#घोषणा TX_DMA_DST_CSR			0x342c
#घोषणा TX_DMA_DST_CSR_DEST_AC0		FIELD32(0x00000003)
#घोषणा TX_DMA_DST_CSR_DEST_AC1		FIELD32(0x0000000c)
#घोषणा TX_DMA_DST_CSR_DEST_AC2		FIELD32(0x00000030)
#घोषणा TX_DMA_DST_CSR_DEST_AC3		FIELD32(0x000000c0)
#घोषणा TX_DMA_DST_CSR_DEST_MGMT	FIELD32(0x00000300)

/*
 * TX_CNTL_CSR: KICK/Abort TX.
 * KICK_TX_AC0: For AC_VO.
 * KICK_TX_AC1: For AC_VI.
 * KICK_TX_AC2: For AC_BE.
 * KICK_TX_AC3: For AC_BK.
 * ABORT_TX_AC0: For AC_VO.
 * ABORT_TX_AC1: For AC_VI.
 * ABORT_TX_AC2: For AC_BE.
 * ABORT_TX_AC3: For AC_BK.
 */
#घोषणा TX_CNTL_CSR			0x3430
#घोषणा TX_CNTL_CSR_KICK_TX_AC0		FIELD32(0x00000001)
#घोषणा TX_CNTL_CSR_KICK_TX_AC1		FIELD32(0x00000002)
#घोषणा TX_CNTL_CSR_KICK_TX_AC2		FIELD32(0x00000004)
#घोषणा TX_CNTL_CSR_KICK_TX_AC3		FIELD32(0x00000008)
#घोषणा TX_CNTL_CSR_KICK_TX_MGMT	FIELD32(0x00000010)
#घोषणा TX_CNTL_CSR_ABORT_TX_AC0	FIELD32(0x00010000)
#घोषणा TX_CNTL_CSR_ABORT_TX_AC1	FIELD32(0x00020000)
#घोषणा TX_CNTL_CSR_ABORT_TX_AC2	FIELD32(0x00040000)
#घोषणा TX_CNTL_CSR_ABORT_TX_AC3	FIELD32(0x00080000)
#घोषणा TX_CNTL_CSR_ABORT_TX_MGMT	FIELD32(0x00100000)

/*
 * LOAD_TX_RING_CSR: Load RX desriptor
 */
#घोषणा LOAD_TX_RING_CSR		0x3434
#घोषणा LOAD_TX_RING_CSR_LOAD_TXD_AC0	FIELD32(0x00000001)
#घोषणा LOAD_TX_RING_CSR_LOAD_TXD_AC1	FIELD32(0x00000002)
#घोषणा LOAD_TX_RING_CSR_LOAD_TXD_AC2	FIELD32(0x00000004)
#घोषणा LOAD_TX_RING_CSR_LOAD_TXD_AC3	FIELD32(0x00000008)
#घोषणा LOAD_TX_RING_CSR_LOAD_TXD_MGMT	FIELD32(0x00000010)

/*
 * Several पढ़ो-only रेजिस्टरs, क्रम debugging.
 */
#घोषणा AC0_TXPTR_CSR			0x3438
#घोषणा AC1_TXPTR_CSR			0x343c
#घोषणा AC2_TXPTR_CSR			0x3440
#घोषणा AC3_TXPTR_CSR			0x3444
#घोषणा MGMT_TXPTR_CSR			0x3448

/*
 * RX_BASE_CSR
 */
#घोषणा RX_BASE_CSR			0x3450
#घोषणा RX_BASE_CSR_RING_REGISTER	FIELD32(0xffffffff)

/*
 * RX_RING_CSR.
 * RXD_SIZE: In unit of 32-bit.
 */
#घोषणा RX_RING_CSR			0x3454
#घोषणा RX_RING_CSR_RING_SIZE		FIELD32(0x000000ff)
#घोषणा RX_RING_CSR_RXD_SIZE		FIELD32(0x00003f00)
#घोषणा RX_RING_CSR_RXD_WRITEBACK_SIZE	FIELD32(0x00070000)

/*
 * RX_CNTL_CSR
 */
#घोषणा RX_CNTL_CSR			0x3458
#घोषणा RX_CNTL_CSR_ENABLE_RX_DMA	FIELD32(0x00000001)
#घोषणा RX_CNTL_CSR_LOAD_RXD		FIELD32(0x00000002)

/*
 * RXPTR_CSR: Read-only, क्रम debugging.
 */
#घोषणा RXPTR_CSR			0x345c

/*
 * PCI_CFG_CSR
 */
#घोषणा PCI_CFG_CSR			0x3460

/*
 * BUF_FORMAT_CSR
 */
#घोषणा BUF_FORMAT_CSR			0x3464

/*
 * INT_SOURCE_CSR: Interrupt source रेजिस्टर.
 * Write one to clear corresponding bit.
 */
#घोषणा INT_SOURCE_CSR			0x3468
#घोषणा INT_SOURCE_CSR_TXDONE		FIELD32(0x00000001)
#घोषणा INT_SOURCE_CSR_RXDONE		FIELD32(0x00000002)
#घोषणा INT_SOURCE_CSR_BEACON_DONE	FIELD32(0x00000004)
#घोषणा INT_SOURCE_CSR_TX_ABORT_DONE	FIELD32(0x00000010)
#घोषणा INT_SOURCE_CSR_AC0_DMA_DONE	FIELD32(0x00010000)
#घोषणा INT_SOURCE_CSR_AC1_DMA_DONE	FIELD32(0x00020000)
#घोषणा INT_SOURCE_CSR_AC2_DMA_DONE	FIELD32(0x00040000)
#घोषणा INT_SOURCE_CSR_AC3_DMA_DONE	FIELD32(0x00080000)
#घोषणा INT_SOURCE_CSR_MGMT_DMA_DONE	FIELD32(0x00100000)
#घोषणा INT_SOURCE_CSR_HCCA_DMA_DONE	FIELD32(0x00200000)

/*
 * INT_MASK_CSR: Interrupt MASK रेजिस्टर. 1: the पूर्णांकerrupt is mask OFF.
 * MITIGATION_PERIOD: Interrupt mitigation in unit of 32 PCI घड़ी.
 */
#घोषणा INT_MASK_CSR			0x346c
#घोषणा INT_MASK_CSR_TXDONE		FIELD32(0x00000001)
#घोषणा INT_MASK_CSR_RXDONE		FIELD32(0x00000002)
#घोषणा INT_MASK_CSR_BEACON_DONE	FIELD32(0x00000004)
#घोषणा INT_MASK_CSR_TX_ABORT_DONE	FIELD32(0x00000010)
#घोषणा INT_MASK_CSR_ENABLE_MITIGATION	FIELD32(0x00000080)
#घोषणा INT_MASK_CSR_MITIGATION_PERIOD	FIELD32(0x0000ff00)
#घोषणा INT_MASK_CSR_AC0_DMA_DONE	FIELD32(0x00010000)
#घोषणा INT_MASK_CSR_AC1_DMA_DONE	FIELD32(0x00020000)
#घोषणा INT_MASK_CSR_AC2_DMA_DONE	FIELD32(0x00040000)
#घोषणा INT_MASK_CSR_AC3_DMA_DONE	FIELD32(0x00080000)
#घोषणा INT_MASK_CSR_MGMT_DMA_DONE	FIELD32(0x00100000)
#घोषणा INT_MASK_CSR_HCCA_DMA_DONE	FIELD32(0x00200000)

/*
 * E2PROM_CSR: EEPROM control रेजिस्टर.
 * RELOAD: Write 1 to reload eeprom content.
 * TYPE_93C46: 1: 93c46, 0:93c66.
 * LOAD_STATUS: 1:loading, 0:करोne.
 */
#घोषणा E2PROM_CSR			0x3470
#घोषणा E2PROM_CSR_RELOAD		FIELD32(0x00000001)
#घोषणा E2PROM_CSR_DATA_CLOCK		FIELD32(0x00000002)
#घोषणा E2PROM_CSR_CHIP_SELECT		FIELD32(0x00000004)
#घोषणा E2PROM_CSR_DATA_IN		FIELD32(0x00000008)
#घोषणा E2PROM_CSR_DATA_OUT		FIELD32(0x00000010)
#घोषणा E2PROM_CSR_TYPE_93C46		FIELD32(0x00000020)
#घोषणा E2PROM_CSR_LOAD_STATUS		FIELD32(0x00000040)

/*
 * AC_TXOP_CSR0: AC_VO/AC_VI TXOP रेजिस्टर.
 * AC0_TX_OP: For AC_VO, in unit of 32us.
 * AC1_TX_OP: For AC_VI, in unit of 32us.
 */
#घोषणा AC_TXOP_CSR0			0x3474
#घोषणा AC_TXOP_CSR0_AC0_TX_OP		FIELD32(0x0000ffff)
#घोषणा AC_TXOP_CSR0_AC1_TX_OP		FIELD32(0xffff0000)

/*
 * AC_TXOP_CSR1: AC_BE/AC_BK TXOP रेजिस्टर.
 * AC2_TX_OP: For AC_BE, in unit of 32us.
 * AC3_TX_OP: For AC_BK, in unit of 32us.
 */
#घोषणा AC_TXOP_CSR1			0x3478
#घोषणा AC_TXOP_CSR1_AC2_TX_OP		FIELD32(0x0000ffff)
#घोषणा AC_TXOP_CSR1_AC3_TX_OP		FIELD32(0xffff0000)

/*
 * DMA_STATUS_CSR
 */
#घोषणा DMA_STATUS_CSR			0x3480

/*
 * TEST_MODE_CSR
 */
#घोषणा TEST_MODE_CSR			0x3484

/*
 * UART0_TX_CSR
 */
#घोषणा UART0_TX_CSR			0x3488

/*
 * UART0_RX_CSR
 */
#घोषणा UART0_RX_CSR			0x348c

/*
 * UART0_FRAME_CSR
 */
#घोषणा UART0_FRAME_CSR			0x3490

/*
 * UART0_BUFFER_CSR
 */
#घोषणा UART0_BUFFER_CSR		0x3494

/*
 * IO_CNTL_CSR
 * RF_PS: Set RF पूर्णांकerface value to घातer save
 */
#घोषणा IO_CNTL_CSR			0x3498
#घोषणा IO_CNTL_CSR_RF_PS		FIELD32(0x00000004)

/*
 * UART_INT_SOURCE_CSR
 */
#घोषणा UART_INT_SOURCE_CSR		0x34a8

/*
 * UART_INT_MASK_CSR
 */
#घोषणा UART_INT_MASK_CSR		0x34ac

/*
 * PBF_QUEUE_CSR
 */
#घोषणा PBF_QUEUE_CSR			0x34b0

/*
 * Firmware DMA रेजिस्टरs.
 * Firmware DMA रेजिस्टरs are dedicated क्रम MCU usage
 * and should not be touched by host driver.
 * Thereक्रमe we skip the definition of these रेजिस्टरs.
 */
#घोषणा FW_TX_BASE_CSR			0x34c0
#घोषणा FW_TX_START_CSR			0x34c4
#घोषणा FW_TX_LAST_CSR			0x34c8
#घोषणा FW_MODE_CNTL_CSR		0x34cc
#घोषणा FW_TXPTR_CSR			0x34d0

/*
 * 8051 firmware image.
 */
#घोषणा FIRMWARE_RT2561			"rt2561.bin"
#घोषणा FIRMWARE_RT2561s		"rt2561s.bin"
#घोषणा FIRMWARE_RT2661			"rt2661.bin"
#घोषणा FIRMWARE_IMAGE_BASE		0x4000

/*
 * BBP रेजिस्टरs.
 * The wordsize of the BBP is 8 bits.
 */

/*
 * R2
 */
#घोषणा BBP_R2_BG_MODE			FIELD8(0x20)

/*
 * R3
 */
#घोषणा BBP_R3_SMART_MODE		FIELD8(0x01)

/*
 * R4: RX antenna control
 * FRAME_END: 1 - DPDT, 0 - SPDT (Only valid क्रम 802.11G, RF2527 & RF2529)
 */

/*
 * ANTENNA_CONTROL semantics (guessed):
 * 0x1: Software controlled antenna चयनing (fixed or SW भागersity)
 * 0x2: Hardware भागersity.
 */
#घोषणा BBP_R4_RX_ANTENNA_CONTROL	FIELD8(0x03)
#घोषणा BBP_R4_RX_FRAME_END		FIELD8(0x20)

/*
 * R77
 */
#घोषणा BBP_R77_RX_ANTENNA		FIELD8(0x03)

/*
 * RF रेजिस्टरs
 */

/*
 * RF 3
 */
#घोषणा RF3_TXPOWER			FIELD32(0x00003e00)

/*
 * RF 4
 */
#घोषणा RF4_FREQ_OFFSET			FIELD32(0x0003f000)

/*
 * EEPROM content.
 * The wordsize of the EEPROM is 16 bits.
 */

/*
 * HW MAC address.
 */
#घोषणा EEPROM_MAC_ADDR_0		0x0002
#घोषणा EEPROM_MAC_ADDR_BYTE0		FIELD16(0x00ff)
#घोषणा EEPROM_MAC_ADDR_BYTE1		FIELD16(0xff00)
#घोषणा EEPROM_MAC_ADDR1		0x0003
#घोषणा EEPROM_MAC_ADDR_BYTE2		FIELD16(0x00ff)
#घोषणा EEPROM_MAC_ADDR_BYTE3		FIELD16(0xff00)
#घोषणा EEPROM_MAC_ADDR_2		0x0004
#घोषणा EEPROM_MAC_ADDR_BYTE4		FIELD16(0x00ff)
#घोषणा EEPROM_MAC_ADDR_BYTE5		FIELD16(0xff00)

/*
 * EEPROM antenna.
 * ANTENNA_NUM: Number of antenna's.
 * TX_DEFAULT: Default antenna 0: भागersity, 1: A, 2: B.
 * RX_DEFAULT: Default antenna 0: भागersity, 1: A, 2: B.
 * FRAME_TYPE: 0: DPDT , 1: SPDT , noted this bit is valid क्रम g only.
 * DYN_TXAGC: Dynamic TX AGC control.
 * HARDWARE_RADIO: 1: Hardware controlled radio. Read GPIO0.
 * RF_TYPE: Rf_type of this adapter.
 */
#घोषणा EEPROM_ANTENNA			0x0010
#घोषणा EEPROM_ANTENNA_NUM		FIELD16(0x0003)
#घोषणा EEPROM_ANTENNA_TX_DEFAULT	FIELD16(0x000c)
#घोषणा EEPROM_ANTENNA_RX_DEFAULT	FIELD16(0x0030)
#घोषणा EEPROM_ANTENNA_FRAME_TYPE	FIELD16(0x0040)
#घोषणा EEPROM_ANTENNA_DYN_TXAGC	FIELD16(0x0200)
#घोषणा EEPROM_ANTENNA_HARDWARE_RADIO	FIELD16(0x0400)
#घोषणा EEPROM_ANTENNA_RF_TYPE		FIELD16(0xf800)

/*
 * EEPROM NIC config.
 * ENABLE_DIVERSITY: 1:enable, 0:disable.
 * EXTERNAL_LNA_BG: External LNA enable क्रम 2.4G.
 * CARDBUS_ACCEL: 0:enable, 1:disable.
 * EXTERNAL_LNA_A: External LNA enable क्रम 5G.
 */
#घोषणा EEPROM_NIC			0x0011
#घोषणा EEPROM_NIC_ENABLE_DIVERSITY	FIELD16(0x0001)
#घोषणा EEPROM_NIC_TX_DIVERSITY		FIELD16(0x0002)
#घोषणा EEPROM_NIC_RX_FIXED		FIELD16(0x0004)
#घोषणा EEPROM_NIC_TX_FIXED		FIELD16(0x0008)
#घोषणा EEPROM_NIC_EXTERNAL_LNA_BG	FIELD16(0x0010)
#घोषणा EEPROM_NIC_CARDBUS_ACCEL	FIELD16(0x0020)
#घोषणा EEPROM_NIC_EXTERNAL_LNA_A	FIELD16(0x0040)

/*
 * EEPROM geography.
 * GEO_A: Default geographical setting क्रम 5GHz band
 * GEO: Default geographical setting.
 */
#घोषणा EEPROM_GEOGRAPHY		0x0012
#घोषणा EEPROM_GEOGRAPHY_GEO_A		FIELD16(0x00ff)
#घोषणा EEPROM_GEOGRAPHY_GEO		FIELD16(0xff00)

/*
 * EEPROM BBP.
 */
#घोषणा EEPROM_BBP_START		0x0013
#घोषणा EEPROM_BBP_SIZE			16
#घोषणा EEPROM_BBP_VALUE		FIELD16(0x00ff)
#घोषणा EEPROM_BBP_REG_ID		FIELD16(0xff00)

/*
 * EEPROM TXPOWER 802.11G
 */
#घोषणा EEPROM_TXPOWER_G_START		0x0023
#घोषणा EEPROM_TXPOWER_G_SIZE		7
#घोषणा EEPROM_TXPOWER_G_1		FIELD16(0x00ff)
#घोषणा EEPROM_TXPOWER_G_2		FIELD16(0xff00)

/*
 * EEPROM Frequency
 */
#घोषणा EEPROM_FREQ			0x002f
#घोषणा EEPROM_FREQ_OFFSET		FIELD16(0x00ff)
#घोषणा EEPROM_FREQ_SEQ_MASK		FIELD16(0xff00)
#घोषणा EEPROM_FREQ_SEQ			FIELD16(0x0300)

/*
 * EEPROM LED.
 * POLARITY_RDY_G: Polarity RDY_G setting.
 * POLARITY_RDY_A: Polarity RDY_A setting.
 * POLARITY_ACT: Polarity ACT setting.
 * POLARITY_GPIO_0: Polarity GPIO0 setting.
 * POLARITY_GPIO_1: Polarity GPIO1 setting.
 * POLARITY_GPIO_2: Polarity GPIO2 setting.
 * POLARITY_GPIO_3: Polarity GPIO3 setting.
 * POLARITY_GPIO_4: Polarity GPIO4 setting.
 * LED_MODE: Led mode.
 */
#घोषणा EEPROM_LED			0x0030
#घोषणा EEPROM_LED_POLARITY_RDY_G	FIELD16(0x0001)
#घोषणा EEPROM_LED_POLARITY_RDY_A	FIELD16(0x0002)
#घोषणा EEPROM_LED_POLARITY_ACT		FIELD16(0x0004)
#घोषणा EEPROM_LED_POLARITY_GPIO_0	FIELD16(0x0008)
#घोषणा EEPROM_LED_POLARITY_GPIO_1	FIELD16(0x0010)
#घोषणा EEPROM_LED_POLARITY_GPIO_2	FIELD16(0x0020)
#घोषणा EEPROM_LED_POLARITY_GPIO_3	FIELD16(0x0040)
#घोषणा EEPROM_LED_POLARITY_GPIO_4	FIELD16(0x0080)
#घोषणा EEPROM_LED_LED_MODE		FIELD16(0x1f00)

/*
 * EEPROM TXPOWER 802.11A
 */
#घोषणा EEPROM_TXPOWER_A_START		0x0031
#घोषणा EEPROM_TXPOWER_A_SIZE		12
#घोषणा EEPROM_TXPOWER_A_1		FIELD16(0x00ff)
#घोषणा EEPROM_TXPOWER_A_2		FIELD16(0xff00)

/*
 * EEPROM RSSI offset 802.11BG
 */
#घोषणा EEPROM_RSSI_OFFSET_BG		0x004d
#घोषणा EEPROM_RSSI_OFFSET_BG_1		FIELD16(0x00ff)
#घोषणा EEPROM_RSSI_OFFSET_BG_2		FIELD16(0xff00)

/*
 * EEPROM RSSI offset 802.11A
 */
#घोषणा EEPROM_RSSI_OFFSET_A		0x004e
#घोषणा EEPROM_RSSI_OFFSET_A_1		FIELD16(0x00ff)
#घोषणा EEPROM_RSSI_OFFSET_A_2		FIELD16(0xff00)

/*
 * MCU mailbox commands.
 */
#घोषणा MCU_SLEEP			0x30
#घोषणा MCU_WAKEUP			0x31
#घोषणा MCU_LED				0x50
#घोषणा MCU_LED_STRENGTH		0x52

/*
 * DMA descriptor defines.
 */
#घोषणा TXD_DESC_SIZE			(16 * माप(__le32))
#घोषणा TXINFO_SIZE			(6 * माप(__le32))
#घोषणा RXD_DESC_SIZE			(16 * माप(__le32))

/*
 * TX descriptor क्रमmat क्रम TX, PRIO and Beacon Ring.
 */

/*
 * Word0
 * TKIP_MIC: ASIC appends TKIP MIC अगर TKIP is used.
 * KEY_TABLE: Use per-client pairwise KEY table.
 * KEY_INDEX:
 * Key index (0~31) to the pairwise KEY table.
 * 0~3 to shared KEY table 0 (BSS0).
 * 4~7 to shared KEY table 1 (BSS1).
 * 8~11 to shared KEY table 2 (BSS2).
 * 12~15 to shared KEY table 3 (BSS3).
 * BURST: Next frame beदीर्घs to same "burst" event.
 */
#घोषणा TXD_W0_OWNER_NIC		FIELD32(0x00000001)
#घोषणा TXD_W0_VALID			FIELD32(0x00000002)
#घोषणा TXD_W0_MORE_FRAG		FIELD32(0x00000004)
#घोषणा TXD_W0_ACK			FIELD32(0x00000008)
#घोषणा TXD_W0_TIMESTAMP		FIELD32(0x00000010)
#घोषणा TXD_W0_OFDM			FIELD32(0x00000020)
#घोषणा TXD_W0_IFS			FIELD32(0x00000040)
#घोषणा TXD_W0_RETRY_MODE		FIELD32(0x00000080)
#घोषणा TXD_W0_TKIP_MIC			FIELD32(0x00000100)
#घोषणा TXD_W0_KEY_TABLE		FIELD32(0x00000200)
#घोषणा TXD_W0_KEY_INDEX		FIELD32(0x0000fc00)
#घोषणा TXD_W0_DATABYTE_COUNT		FIELD32(0x0fff0000)
#घोषणा TXD_W0_BURST			FIELD32(0x10000000)
#घोषणा TXD_W0_CIPHER_ALG		FIELD32(0xe0000000)

/*
 * Word1
 * HOST_Q_ID: EDCA/HCCA queue ID.
 * HW_SEQUENCE: MAC overग_लिखोs the frame sequence number.
 * BUFFER_COUNT: Number of buffers in this TXD.
 */
#घोषणा TXD_W1_HOST_Q_ID		FIELD32(0x0000000f)
#घोषणा TXD_W1_AIFSN			FIELD32(0x000000f0)
#घोषणा TXD_W1_CWMIN			FIELD32(0x00000f00)
#घोषणा TXD_W1_CWMAX			FIELD32(0x0000f000)
#घोषणा TXD_W1_IV_OFFSET		FIELD32(0x003f0000)
#घोषणा TXD_W1_PIGGY_BACK		FIELD32(0x01000000)
#घोषणा TXD_W1_HW_SEQUENCE		FIELD32(0x10000000)
#घोषणा TXD_W1_BUFFER_COUNT		FIELD32(0xe0000000)

/*
 * Word2: PLCP inक्रमmation
 */
#घोषणा TXD_W2_PLCP_SIGNAL		FIELD32(0x000000ff)
#घोषणा TXD_W2_PLCP_SERVICE		FIELD32(0x0000ff00)
#घोषणा TXD_W2_PLCP_LENGTH_LOW		FIELD32(0x00ff0000)
#घोषणा TXD_W2_PLCP_LENGTH_HIGH		FIELD32(0xff000000)

/*
 * Word3
 */
#घोषणा TXD_W3_IV			FIELD32(0xffffffff)

/*
 * Word4
 */
#घोषणा TXD_W4_EIV			FIELD32(0xffffffff)

/*
 * Word5
 * FRAME_OFFSET: Frame start offset inside ASIC TXFIFO (after TXINFO field).
 * TXD_W5_PID_SUBTYPE: Driver asचिन्हित packet ID index क्रम txकरोne handler.
 * TXD_W5_PID_TYPE: Driver asचिन्हित packet ID type क्रम txकरोne handler.
 * WAITING_DMA_DONE_INT: TXD been filled with data
 * and रुकोing क्रम TxDoneISR housekeeping.
 */
#घोषणा TXD_W5_FRAME_OFFSET		FIELD32(0x000000ff)
#घोषणा TXD_W5_PID_SUBTYPE		FIELD32(0x00001f00)
#घोषणा TXD_W5_PID_TYPE			FIELD32(0x0000e000)
#घोषणा TXD_W5_TX_POWER			FIELD32(0x00ff0000)
#घोषणा TXD_W5_WAITING_DMA_DONE_INT	FIELD32(0x01000000)

/*
 * the above 24-byte is called TXINFO and will be DMAed to MAC block
 * through TXFIFO. MAC block use this TXINFO to control the transmission
 * behavior of this frame.
 * The following fields are not used by MAC block.
 * They are used by DMA block and HOST driver only.
 * Once a frame has been DMA to ASIC, all the following fields are useless
 * to ASIC.
 */

/*
 * Word6-10: Buffer physical address
 */
#घोषणा TXD_W6_BUFFER_PHYSICAL_ADDRESS	FIELD32(0xffffffff)
#घोषणा TXD_W7_BUFFER_PHYSICAL_ADDRESS	FIELD32(0xffffffff)
#घोषणा TXD_W8_BUFFER_PHYSICAL_ADDRESS	FIELD32(0xffffffff)
#घोषणा TXD_W9_BUFFER_PHYSICAL_ADDRESS	FIELD32(0xffffffff)
#घोषणा TXD_W10_BUFFER_PHYSICAL_ADDRESS	FIELD32(0xffffffff)

/*
 * Word11-13: Buffer length
 */
#घोषणा TXD_W11_BUFFER_LENGTH0		FIELD32(0x00000fff)
#घोषणा TXD_W11_BUFFER_LENGTH1		FIELD32(0x0fff0000)
#घोषणा TXD_W12_BUFFER_LENGTH2		FIELD32(0x00000fff)
#घोषणा TXD_W12_BUFFER_LENGTH3		FIELD32(0x0fff0000)
#घोषणा TXD_W13_BUFFER_LENGTH4		FIELD32(0x00000fff)

/*
 * Word14
 */
#घोषणा TXD_W14_SK_BUFFER		FIELD32(0xffffffff)

/*
 * Word15
 */
#घोषणा TXD_W15_NEXT_SK_BUFFER		FIELD32(0xffffffff)

/*
 * RX descriptor क्रमmat क्रम RX Ring.
 */

/*
 * Word0
 * CIPHER_ERROR: 1:ICV error, 2:MIC error, 3:invalid key.
 * KEY_INDEX: Decryption key actually used.
 */
#घोषणा RXD_W0_OWNER_NIC		FIELD32(0x00000001)
#घोषणा RXD_W0_DROP			FIELD32(0x00000002)
#घोषणा RXD_W0_UNICAST_TO_ME		FIELD32(0x00000004)
#घोषणा RXD_W0_MULTICAST		FIELD32(0x00000008)
#घोषणा RXD_W0_BROADCAST		FIELD32(0x00000010)
#घोषणा RXD_W0_MY_BSS			FIELD32(0x00000020)
#घोषणा RXD_W0_CRC_ERROR		FIELD32(0x00000040)
#घोषणा RXD_W0_OFDM			FIELD32(0x00000080)
#घोषणा RXD_W0_CIPHER_ERROR		FIELD32(0x00000300)
#घोषणा RXD_W0_KEY_INDEX		FIELD32(0x0000fc00)
#घोषणा RXD_W0_DATABYTE_COUNT		FIELD32(0x0fff0000)
#घोषणा RXD_W0_CIPHER_ALG		FIELD32(0xe0000000)

/*
 * Word1
 * SIGNAL: RX raw data rate reported by BBP.
 */
#घोषणा RXD_W1_SIGNAL			FIELD32(0x000000ff)
#घोषणा RXD_W1_RSSI_AGC			FIELD32(0x00001f00)
#घोषणा RXD_W1_RSSI_LNA			FIELD32(0x00006000)
#घोषणा RXD_W1_FRAME_OFFSET		FIELD32(0x7f000000)

/*
 * Word2
 * IV: Received IV of originally encrypted.
 */
#घोषणा RXD_W2_IV			FIELD32(0xffffffff)

/*
 * Word3
 * EIV: Received EIV of originally encrypted.
 */
#घोषणा RXD_W3_EIV			FIELD32(0xffffffff)

/*
 * Word4
 * ICV: Received ICV of originally encrypted.
 * NOTE: This is a guess, the official definition is "reserved"
 */
#घोषणा RXD_W4_ICV			FIELD32(0xffffffff)

/*
 * the above 20-byte is called RXINFO and will be DMAed to MAC RX block
 * and passed to the HOST driver.
 * The following fields are क्रम DMA block and HOST usage only.
 * Can't be touched by ASIC MAC block.
 */

/*
 * Word5
 */
#घोषणा RXD_W5_BUFFER_PHYSICAL_ADDRESS	FIELD32(0xffffffff)

/*
 * Word6-15: Reserved
 */
#घोषणा RXD_W6_RESERVED			FIELD32(0xffffffff)
#घोषणा RXD_W7_RESERVED			FIELD32(0xffffffff)
#घोषणा RXD_W8_RESERVED			FIELD32(0xffffffff)
#घोषणा RXD_W9_RESERVED			FIELD32(0xffffffff)
#घोषणा RXD_W10_RESERVED		FIELD32(0xffffffff)
#घोषणा RXD_W11_RESERVED		FIELD32(0xffffffff)
#घोषणा RXD_W12_RESERVED		FIELD32(0xffffffff)
#घोषणा RXD_W13_RESERVED		FIELD32(0xffffffff)
#घोषणा RXD_W14_RESERVED		FIELD32(0xffffffff)
#घोषणा RXD_W15_RESERVED		FIELD32(0xffffffff)

/*
 * Macros क्रम converting txघातer from EEPROM to mac80211 value
 * and from mac80211 value to रेजिस्टर value.
 */
#घोषणा MIN_TXPOWER	0
#घोषणा MAX_TXPOWER	31
#घोषणा DEFAULT_TXPOWER	24

#घोषणा TXPOWER_FROM_DEV(__txघातer) \
	(((u8)(__txघातer)) > MAX_TXPOWER) ? DEFAULT_TXPOWER : (__txघातer)

#घोषणा TXPOWER_TO_DEV(__txघातer) \
	clamp_t(अक्षर, __txघातer, MIN_TXPOWER, MAX_TXPOWER)

#पूर्ण_अगर /* RT61PCI_H */
