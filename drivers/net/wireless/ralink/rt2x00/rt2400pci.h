<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2400pci
	Abstract: Data काष्ठाures and रेजिस्टरs क्रम the rt2400pci module.
	Supported chipsets: RT2460.
 */

#अगर_अघोषित RT2400PCI_H
#घोषणा RT2400PCI_H

/*
 * RF chip defines.
 */
#घोषणा RF2420				0x0000
#घोषणा RF2421				0x0001

/*
 * Signal inक्रमmation.
 * Default offset is required क्रम RSSI <-> dBm conversion.
 */
#घोषणा DEFAULT_RSSI_OFFSET		100

/*
 * Register layout inक्रमmation.
 */
#घोषणा CSR_REG_BASE			0x0000
#घोषणा CSR_REG_SIZE			0x014c
#घोषणा EEPROM_BASE			0x0000
#घोषणा EEPROM_SIZE			0x0100
#घोषणा BBP_BASE			0x0000
#घोषणा BBP_SIZE			0x0020
#घोषणा RF_BASE				0x0004
#घोषणा RF_SIZE				0x000c

/*
 * Number of TX queues.
 */
#घोषणा NUM_TX_QUEUES			2

/*
 * Control/Status Registers(CSR).
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * CSR0: ASIC revision number.
 */
#घोषणा CSR0				0x0000
#घोषणा CSR0_REVISION			FIELD32(0x0000ffff)

/*
 * CSR1: System control रेजिस्टर.
 * SOFT_RESET: Software reset, 1: reset, 0: normal.
 * BBP_RESET: Hardware reset, 1: reset, 0, release.
 * HOST_READY: Host पढ़ोy after initialization.
 */
#घोषणा CSR1				0x0004
#घोषणा CSR1_SOFT_RESET			FIELD32(0x00000001)
#घोषणा CSR1_BBP_RESET			FIELD32(0x00000002)
#घोषणा CSR1_HOST_READY			FIELD32(0x00000004)

/*
 * CSR2: System admin status रेजिस्टर (invalid).
 */
#घोषणा CSR2				0x0008

/*
 * CSR3: STA MAC address रेजिस्टर 0.
 */
#घोषणा CSR3				0x000c
#घोषणा CSR3_BYTE0			FIELD32(0x000000ff)
#घोषणा CSR3_BYTE1			FIELD32(0x0000ff00)
#घोषणा CSR3_BYTE2			FIELD32(0x00ff0000)
#घोषणा CSR3_BYTE3			FIELD32(0xff000000)

/*
 * CSR4: STA MAC address रेजिस्टर 1.
 */
#घोषणा CSR4				0x0010
#घोषणा CSR4_BYTE4			FIELD32(0x000000ff)
#घोषणा CSR4_BYTE5			FIELD32(0x0000ff00)

/*
 * CSR5: BSSID रेजिस्टर 0.
 */
#घोषणा CSR5				0x0014
#घोषणा CSR5_BYTE0			FIELD32(0x000000ff)
#घोषणा CSR5_BYTE1			FIELD32(0x0000ff00)
#घोषणा CSR5_BYTE2			FIELD32(0x00ff0000)
#घोषणा CSR5_BYTE3			FIELD32(0xff000000)

/*
 * CSR6: BSSID रेजिस्टर 1.
 */
#घोषणा CSR6				0x0018
#घोषणा CSR6_BYTE4			FIELD32(0x000000ff)
#घोषणा CSR6_BYTE5			FIELD32(0x0000ff00)

/*
 * CSR7: Interrupt source रेजिस्टर.
 * Write 1 to clear पूर्णांकerrupt.
 * TBCN_EXPIRE: Beacon समयr expired पूर्णांकerrupt.
 * TWAKE_EXPIRE: Wakeup समयr expired पूर्णांकerrupt.
 * TATIMW_EXPIRE: Timer of atim winकरोw expired पूर्णांकerrupt.
 * TXDONE_TXRING: Tx ring transmit करोne पूर्णांकerrupt.
 * TXDONE_ATIMRING: Atim ring transmit करोne पूर्णांकerrupt.
 * TXDONE_PRIORING: Priority ring transmit करोne पूर्णांकerrupt.
 * RXDONE: Receive करोne पूर्णांकerrupt.
 */
#घोषणा CSR7				0x001c
#घोषणा CSR7_TBCN_EXPIRE		FIELD32(0x00000001)
#घोषणा CSR7_TWAKE_EXPIRE		FIELD32(0x00000002)
#घोषणा CSR7_TATIMW_EXPIRE		FIELD32(0x00000004)
#घोषणा CSR7_TXDONE_TXRING		FIELD32(0x00000008)
#घोषणा CSR7_TXDONE_ATIMRING		FIELD32(0x00000010)
#घोषणा CSR7_TXDONE_PRIORING		FIELD32(0x00000020)
#घोषणा CSR7_RXDONE			FIELD32(0x00000040)

/*
 * CSR8: Interrupt mask रेजिस्टर.
 * Write 1 to mask पूर्णांकerrupt.
 * TBCN_EXPIRE: Beacon समयr expired पूर्णांकerrupt.
 * TWAKE_EXPIRE: Wakeup समयr expired पूर्णांकerrupt.
 * TATIMW_EXPIRE: Timer of atim winकरोw expired पूर्णांकerrupt.
 * TXDONE_TXRING: Tx ring transmit करोne पूर्णांकerrupt.
 * TXDONE_ATIMRING: Atim ring transmit करोne पूर्णांकerrupt.
 * TXDONE_PRIORING: Priority ring transmit करोne पूर्णांकerrupt.
 * RXDONE: Receive करोne पूर्णांकerrupt.
 */
#घोषणा CSR8				0x0020
#घोषणा CSR8_TBCN_EXPIRE		FIELD32(0x00000001)
#घोषणा CSR8_TWAKE_EXPIRE		FIELD32(0x00000002)
#घोषणा CSR8_TATIMW_EXPIRE		FIELD32(0x00000004)
#घोषणा CSR8_TXDONE_TXRING		FIELD32(0x00000008)
#घोषणा CSR8_TXDONE_ATIMRING		FIELD32(0x00000010)
#घोषणा CSR8_TXDONE_PRIORING		FIELD32(0x00000020)
#घोषणा CSR8_RXDONE			FIELD32(0x00000040)

/*
 * CSR9: Maximum frame length रेजिस्टर.
 * MAX_FRAME_UNIT: Maximum frame length in 128b unit, शेष: 12.
 */
#घोषणा CSR9				0x0024
#घोषणा CSR9_MAX_FRAME_UNIT		FIELD32(0x00000f80)

/*
 * CSR11: Back-off control रेजिस्टर.
 * CWMIN: CWmin. Default cwmin is 31 (2^5 - 1).
 * CWMAX: CWmax. Default cwmax is 1023 (2^10 - 1).
 * SLOT_TIME: Slot समय, शेष is 20us क्रम 802.11b.
 * LONG_RETRY: Long retry count.
 * SHORT_RETRY: Short retry count.
 */
#घोषणा CSR11				0x002c
#घोषणा CSR11_CWMIN			FIELD32(0x0000000f)
#घोषणा CSR11_CWMAX			FIELD32(0x000000f0)
#घोषणा CSR11_SLOT_TIME			FIELD32(0x00001f00)
#घोषणा CSR11_LONG_RETRY		FIELD32(0x00ff0000)
#घोषणा CSR11_SHORT_RETRY		FIELD32(0xff000000)

/*
 * CSR12: Synchronization configuration रेजिस्टर 0.
 * All units in 1/16 TU.
 * BEACON_INTERVAL: Beacon पूर्णांकerval, शेष is 100 TU.
 * CFPMAX_DURATION: Cfp maximum duration, शेष is 100 TU.
 */
#घोषणा CSR12				0x0030
#घोषणा CSR12_BEACON_INTERVAL		FIELD32(0x0000ffff)
#घोषणा CSR12_CFP_MAX_DURATION		FIELD32(0xffff0000)

/*
 * CSR13: Synchronization configuration रेजिस्टर 1.
 * All units in 1/16 TU.
 * ATIMW_DURATION: Atim winकरोw duration.
 * CFP_PERIOD: Cfp period, शेष is 0 TU.
 */
#घोषणा CSR13				0x0034
#घोषणा CSR13_ATIMW_DURATION		FIELD32(0x0000ffff)
#घोषणा CSR13_CFP_PERIOD		FIELD32(0x00ff0000)

/*
 * CSR14: Synchronization control रेजिस्टर.
 * TSF_COUNT: Enable tsf स्वतः counting.
 * TSF_SYNC: Tsf sync, 0: disable, 1: infra, 2: ad-hoc/master mode.
 * TBCN: Enable tbcn with reload value.
 * TCFP: Enable tcfp & cfp / cp चयनing.
 * TATIMW: Enable tatimw & atim winकरोw चयनing.
 * BEACON_GEN: Enable beacon generator.
 * CFP_COUNT_PRELOAD: Cfp count preload value.
 * TBCM_PRELOAD: Tbcn preload value in units of 64us.
 */
#घोषणा CSR14				0x0038
#घोषणा CSR14_TSF_COUNT			FIELD32(0x00000001)
#घोषणा CSR14_TSF_SYNC			FIELD32(0x00000006)
#घोषणा CSR14_TBCN			FIELD32(0x00000008)
#घोषणा CSR14_TCFP			FIELD32(0x00000010)
#घोषणा CSR14_TATIMW			FIELD32(0x00000020)
#घोषणा CSR14_BEACON_GEN		FIELD32(0x00000040)
#घोषणा CSR14_CFP_COUNT_PRELOAD		FIELD32(0x0000ff00)
#घोषणा CSR14_TBCM_PRELOAD		FIELD32(0xffff0000)

/*
 * CSR15: Synchronization status रेजिस्टर.
 * CFP: ASIC is in contention-मुक्त period.
 * ATIMW: ASIC is in ATIM winकरोw.
 * BEACON_SENT: Beacon is send.
 */
#घोषणा CSR15				0x003c
#घोषणा CSR15_CFP			FIELD32(0x00000001)
#घोषणा CSR15_ATIMW			FIELD32(0x00000002)
#घोषणा CSR15_BEACON_SENT		FIELD32(0x00000004)

/*
 * CSR16: TSF समयr रेजिस्टर 0.
 */
#घोषणा CSR16				0x0040
#घोषणा CSR16_LOW_TSFTIMER		FIELD32(0xffffffff)

/*
 * CSR17: TSF समयr रेजिस्टर 1.
 */
#घोषणा CSR17				0x0044
#घोषणा CSR17_HIGH_TSFTIMER		FIELD32(0xffffffff)

/*
 * CSR18: IFS समयr रेजिस्टर 0.
 * SIFS: Sअगरs, शेष is 10 us.
 * PIFS: Pअगरs, शेष is 30 us.
 */
#घोषणा CSR18				0x0048
#घोषणा CSR18_SIFS			FIELD32(0x0000ffff)
#घोषणा CSR18_PIFS			FIELD32(0xffff0000)

/*
 * CSR19: IFS समयr रेजिस्टर 1.
 * DIFS: Dअगरs, शेष is 50 us.
 * EIFS: Eअगरs, शेष is 364 us.
 */
#घोषणा CSR19				0x004c
#घोषणा CSR19_DIFS			FIELD32(0x0000ffff)
#घोषणा CSR19_EIFS			FIELD32(0xffff0000)

/*
 * CSR20: Wakeup समयr रेजिस्टर.
 * DELAY_AFTER_TBCN: Delay after tbcn expired in units of 1/16 TU.
 * TBCN_BEFORE_WAKEUP: Number of beacon beक्रमe wakeup.
 * AUTOWAKE: Enable स्वतः wakeup / sleep mechanism.
 */
#घोषणा CSR20				0x0050
#घोषणा CSR20_DELAY_AFTER_TBCN		FIELD32(0x0000ffff)
#घोषणा CSR20_TBCN_BEFORE_WAKEUP	FIELD32(0x00ff0000)
#घोषणा CSR20_AUTOWAKE			FIELD32(0x01000000)

/*
 * CSR21: EEPROM control रेजिस्टर.
 * RELOAD: Write 1 to reload eeprom content.
 * TYPE_93C46: 1: 93c46, 0:93c66.
 */
#घोषणा CSR21				0x0054
#घोषणा CSR21_RELOAD			FIELD32(0x00000001)
#घोषणा CSR21_EEPROM_DATA_CLOCK		FIELD32(0x00000002)
#घोषणा CSR21_EEPROM_CHIP_SELECT	FIELD32(0x00000004)
#घोषणा CSR21_EEPROM_DATA_IN		FIELD32(0x00000008)
#घोषणा CSR21_EEPROM_DATA_OUT		FIELD32(0x00000010)
#घोषणा CSR21_TYPE_93C46		FIELD32(0x00000020)

/*
 * CSR22: CFP control रेजिस्टर.
 * CFP_DURATION_REMAIN: Cfp duration reमुख्य, in units of TU.
 * RELOAD_CFP_DURATION: Write 1 to reload cfp duration reमुख्य.
 */
#घोषणा CSR22				0x0058
#घोषणा CSR22_CFP_DURATION_REMAIN	FIELD32(0x0000ffff)
#घोषणा CSR22_RELOAD_CFP_DURATION	FIELD32(0x00010000)

/*
 * Transmit related CSRs.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * TXCSR0: TX Control Register.
 * KICK_TX: Kick tx ring.
 * KICK_ATIM: Kick atim ring.
 * KICK_PRIO: Kick priority ring.
 * ABORT: Abort all transmit related ring operation.
 */
#घोषणा TXCSR0				0x0060
#घोषणा TXCSR0_KICK_TX			FIELD32(0x00000001)
#घोषणा TXCSR0_KICK_ATIM		FIELD32(0x00000002)
#घोषणा TXCSR0_KICK_PRIO		FIELD32(0x00000004)
#घोषणा TXCSR0_ABORT			FIELD32(0x00000008)

/*
 * TXCSR1: TX Configuration Register.
 * ACK_TIMEOUT: Ack समयout, शेष = sअगरs + 2*slotसमय + ackसमय @ 1mbps.
 * ACK_CONSUME_TIME: Ack consume समय, शेष = sअगरs + ackसमय @ 1mbps.
 * TSF_OFFSET: Insert tsf offset.
 * AUTORESPONDER: Enable स्वतः responder which include ack & cts.
 */
#घोषणा TXCSR1				0x0064
#घोषणा TXCSR1_ACK_TIMEOUT		FIELD32(0x000001ff)
#घोषणा TXCSR1_ACK_CONSUME_TIME		FIELD32(0x0003fe00)
#घोषणा TXCSR1_TSF_OFFSET		FIELD32(0x00fc0000)
#घोषणा TXCSR1_AUTORESPONDER		FIELD32(0x01000000)

/*
 * TXCSR2: Tx descriptor configuration रेजिस्टर.
 * TXD_SIZE: Tx descriptor size, शेष is 48.
 * NUM_TXD: Number of tx entries in ring.
 * NUM_ATIM: Number of atim entries in ring.
 * NUM_PRIO: Number of priority entries in ring.
 */
#घोषणा TXCSR2				0x0068
#घोषणा TXCSR2_TXD_SIZE			FIELD32(0x000000ff)
#घोषणा TXCSR2_NUM_TXD			FIELD32(0x0000ff00)
#घोषणा TXCSR2_NUM_ATIM			FIELD32(0x00ff0000)
#घोषणा TXCSR2_NUM_PRIO			FIELD32(0xff000000)

/*
 * TXCSR3: TX Ring Base address रेजिस्टर.
 */
#घोषणा TXCSR3				0x006c
#घोषणा TXCSR3_TX_RING_REGISTER		FIELD32(0xffffffff)

/*
 * TXCSR4: TX Atim Ring Base address रेजिस्टर.
 */
#घोषणा TXCSR4				0x0070
#घोषणा TXCSR4_ATIM_RING_REGISTER	FIELD32(0xffffffff)

/*
 * TXCSR5: TX Prio Ring Base address रेजिस्टर.
 */
#घोषणा TXCSR5				0x0074
#घोषणा TXCSR5_PRIO_RING_REGISTER	FIELD32(0xffffffff)

/*
 * TXCSR6: Beacon Base address रेजिस्टर.
 */
#घोषणा TXCSR6				0x0078
#घोषणा TXCSR6_BEACON_RING_REGISTER	FIELD32(0xffffffff)

/*
 * TXCSR7: Auto responder control रेजिस्टर.
 * AR_POWERMANAGEMENT: Auto responder घातer management bit.
 */
#घोषणा TXCSR7				0x007c
#घोषणा TXCSR7_AR_POWERMANAGEMENT	FIELD32(0x00000001)

/*
 * Receive related CSRs.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * RXCSR0: RX Control Register.
 * DISABLE_RX: Disable rx engine.
 * DROP_CRC: Drop crc error.
 * DROP_PHYSICAL: Drop physical error.
 * DROP_CONTROL: Drop control frame.
 * DROP_NOT_TO_ME: Drop not to me unicast frame.
 * DROP_TODS: Drop frame tods bit is true.
 * DROP_VERSION_ERROR: Drop version error frame.
 * PASS_CRC: Pass all packets with crc attached.
 */
#घोषणा RXCSR0				0x0080
#घोषणा RXCSR0_DISABLE_RX		FIELD32(0x00000001)
#घोषणा RXCSR0_DROP_CRC			FIELD32(0x00000002)
#घोषणा RXCSR0_DROP_PHYSICAL		FIELD32(0x00000004)
#घोषणा RXCSR0_DROP_CONTROL		FIELD32(0x00000008)
#घोषणा RXCSR0_DROP_NOT_TO_ME		FIELD32(0x00000010)
#घोषणा RXCSR0_DROP_TODS		FIELD32(0x00000020)
#घोषणा RXCSR0_DROP_VERSION_ERROR	FIELD32(0x00000040)
#घोषणा RXCSR0_PASS_CRC			FIELD32(0x00000080)

/*
 * RXCSR1: RX descriptor configuration रेजिस्टर.
 * RXD_SIZE: Rx descriptor size, शेष is 32b.
 * NUM_RXD: Number of rx entries in ring.
 */
#घोषणा RXCSR1				0x0084
#घोषणा RXCSR1_RXD_SIZE			FIELD32(0x000000ff)
#घोषणा RXCSR1_NUM_RXD			FIELD32(0x0000ff00)

/*
 * RXCSR2: RX Ring base address रेजिस्टर.
 */
#घोषणा RXCSR2				0x0088
#घोषणा RXCSR2_RX_RING_REGISTER		FIELD32(0xffffffff)

/*
 * RXCSR3: BBP ID रेजिस्टर क्रम Rx operation.
 * BBP_ID#: BBP रेजिस्टर # id.
 * BBP_ID#_VALID: BBP रेजिस्टर # id is valid or not.
 */
#घोषणा RXCSR3				0x0090
#घोषणा RXCSR3_BBP_ID0			FIELD32(0x0000007f)
#घोषणा RXCSR3_BBP_ID0_VALID		FIELD32(0x00000080)
#घोषणा RXCSR3_BBP_ID1			FIELD32(0x00007f00)
#घोषणा RXCSR3_BBP_ID1_VALID		FIELD32(0x00008000)
#घोषणा RXCSR3_BBP_ID2			FIELD32(0x007f0000)
#घोषणा RXCSR3_BBP_ID2_VALID		FIELD32(0x00800000)
#घोषणा RXCSR3_BBP_ID3			FIELD32(0x7f000000)
#घोषणा RXCSR3_BBP_ID3_VALID		FIELD32(0x80000000)

/*
 * RXCSR4: BBP ID रेजिस्टर क्रम Rx operation.
 * BBP_ID#: BBP रेजिस्टर # id.
 * BBP_ID#_VALID: BBP रेजिस्टर # id is valid or not.
 */
#घोषणा RXCSR4				0x0094
#घोषणा RXCSR4_BBP_ID4			FIELD32(0x0000007f)
#घोषणा RXCSR4_BBP_ID4_VALID		FIELD32(0x00000080)
#घोषणा RXCSR4_BBP_ID5			FIELD32(0x00007f00)
#घोषणा RXCSR4_BBP_ID5_VALID		FIELD32(0x00008000)

/*
 * ARCSR0: Auto Responder PLCP config रेजिस्टर 0.
 * ARCSR0_AR_BBP_DATA#: Auto responder BBP रेजिस्टर # data.
 * ARCSR0_AR_BBP_ID#: Auto responder BBP रेजिस्टर # Id.
 */
#घोषणा ARCSR0				0x0098
#घोषणा ARCSR0_AR_BBP_DATA0		FIELD32(0x000000ff)
#घोषणा ARCSR0_AR_BBP_ID0		FIELD32(0x0000ff00)
#घोषणा ARCSR0_AR_BBP_DATA1		FIELD32(0x00ff0000)
#घोषणा ARCSR0_AR_BBP_ID1		FIELD32(0xff000000)

/*
 * ARCSR1: Auto Responder PLCP config रेजिस्टर 1.
 * ARCSR0_AR_BBP_DATA#: Auto responder BBP रेजिस्टर # data.
 * ARCSR0_AR_BBP_ID#: Auto responder BBP रेजिस्टर # Id.
 */
#घोषणा ARCSR1				0x009c
#घोषणा ARCSR1_AR_BBP_DATA2		FIELD32(0x000000ff)
#घोषणा ARCSR1_AR_BBP_ID2		FIELD32(0x0000ff00)
#घोषणा ARCSR1_AR_BBP_DATA3		FIELD32(0x00ff0000)
#घोषणा ARCSR1_AR_BBP_ID3		FIELD32(0xff000000)

/*
 * Miscellaneous Registers.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * PCICSR: PCI control रेजिस्टर.
 * BIG_ENDIAN: 1: big endian, 0: little endian.
 * RX_TRESHOLD: Rx threshold in dw to start pci access
 * 0: 16dw (शेष), 1: 8dw, 2: 4dw, 3: 32dw.
 * TX_TRESHOLD: Tx threshold in dw to start pci access
 * 0: 0dw (शेष), 1: 1dw, 2: 4dw, 3: क्रमward.
 * BURST_LENTH: Pci burst length 0: 4dw (शेष, 1: 8dw, 2: 16dw, 3:32dw.
 * ENABLE_CLK: Enable clk_run, pci घड़ी can't going करोwn to non-operational.
 */
#घोषणा PCICSR				0x008c
#घोषणा PCICSR_BIG_ENDIAN		FIELD32(0x00000001)
#घोषणा PCICSR_RX_TRESHOLD		FIELD32(0x00000006)
#घोषणा PCICSR_TX_TRESHOLD		FIELD32(0x00000018)
#घोषणा PCICSR_BURST_LENTH		FIELD32(0x00000060)
#घोषणा PCICSR_ENABLE_CLK		FIELD32(0x00000080)

/*
 * CNT0: FCS error count.
 * FCS_ERROR: FCS error count, cleared when पढ़ो.
 */
#घोषणा CNT0				0x00a0
#घोषणा CNT0_FCS_ERROR			FIELD32(0x0000ffff)

/*
 * Statistic Register.
 * CNT1: PLCP error count.
 * CNT2: Long error count.
 * CNT3: CCA false alarm count.
 * CNT4: Rx FIFO overflow count.
 * CNT5: Tx FIFO underrun count.
 */
#घोषणा TIMECSR2			0x00a8
#घोषणा CNT1				0x00ac
#घोषणा CNT2				0x00b0
#घोषणा TIMECSR3			0x00b4
#घोषणा CNT3				0x00b8
#घोषणा CNT4				0x00bc
#घोषणा CNT5				0x00c0

/*
 * Baseband Control Register.
 */

/*
 * PWRCSR0: Power mode configuration रेजिस्टर.
 */
#घोषणा PWRCSR0				0x00c4

/*
 * Power state transition समय रेजिस्टरs.
 */
#घोषणा PSCSR0				0x00c8
#घोषणा PSCSR1				0x00cc
#घोषणा PSCSR2				0x00d0
#घोषणा PSCSR3				0x00d4

/*
 * PWRCSR1: Manual घातer control / status रेजिस्टर.
 * Allowed state: 0 deep_sleep, 1: sleep, 2: standby, 3: awake.
 * SET_STATE: Set state. Write 1 to trigger, self cleared.
 * BBP_DESIRE_STATE: BBP desired state.
 * RF_DESIRE_STATE: RF desired state.
 * BBP_CURR_STATE: BBP current state.
 * RF_CURR_STATE: RF current state.
 * PUT_TO_SLEEP: Put to sleep. Write 1 to trigger, self cleared.
 */
#घोषणा PWRCSR1				0x00d8
#घोषणा PWRCSR1_SET_STATE		FIELD32(0x00000001)
#घोषणा PWRCSR1_BBP_DESIRE_STATE	FIELD32(0x00000006)
#घोषणा PWRCSR1_RF_DESIRE_STATE		FIELD32(0x00000018)
#घोषणा PWRCSR1_BBP_CURR_STATE		FIELD32(0x00000060)
#घोषणा PWRCSR1_RF_CURR_STATE		FIELD32(0x00000180)
#घोषणा PWRCSR1_PUT_TO_SLEEP		FIELD32(0x00000200)

/*
 * TIMECSR: Timer control रेजिस्टर.
 * US_COUNT: 1 us समयr count in units of घड़ी cycles.
 * US_64_COUNT: 64 us समयr count in units of 1 us समयr.
 * BEACON_EXPECT: Beacon expect winकरोw.
 */
#घोषणा TIMECSR				0x00dc
#घोषणा TIMECSR_US_COUNT		FIELD32(0x000000ff)
#घोषणा TIMECSR_US_64_COUNT		FIELD32(0x0000ff00)
#घोषणा TIMECSR_BEACON_EXPECT		FIELD32(0x00070000)

/*
 * MACCSR0: MAC configuration रेजिस्टर 0.
 */
#घोषणा MACCSR0				0x00e0

/*
 * MACCSR1: MAC configuration रेजिस्टर 1.
 * KICK_RX: Kick one-shot rx in one-shot rx mode.
 * ONESHOT_RXMODE: Enable one-shot rx mode क्रम debugging.
 * BBPRX_RESET_MODE: Ralink bbp rx reset mode.
 * AUTO_TXBBP: Auto tx logic access bbp control रेजिस्टर.
 * AUTO_RXBBP: Auto rx logic access bbp control रेजिस्टर.
 * LOOPBACK: Loopback mode. 0: normal, 1: पूर्णांकernal, 2: बाह्यal, 3:rsvd.
 * INTERSIL_IF: Intersil अगर calibration pin.
 */
#घोषणा MACCSR1				0x00e4
#घोषणा MACCSR1_KICK_RX			FIELD32(0x00000001)
#घोषणा MACCSR1_ONESHOT_RXMODE		FIELD32(0x00000002)
#घोषणा MACCSR1_BBPRX_RESET_MODE	FIELD32(0x00000004)
#घोषणा MACCSR1_AUTO_TXBBP		FIELD32(0x00000008)
#घोषणा MACCSR1_AUTO_RXBBP		FIELD32(0x00000010)
#घोषणा MACCSR1_LOOPBACK		FIELD32(0x00000060)
#घोषणा MACCSR1_INTERSIL_IF		FIELD32(0x00000080)

/*
 * RALINKCSR: Ralink Rx स्वतः-reset BBCR.
 * AR_BBP_DATA#: Auto reset BBP रेजिस्टर # data.
 * AR_BBP_ID#: Auto reset BBP रेजिस्टर # id.
 */
#घोषणा RALINKCSR			0x00e8
#घोषणा RALINKCSR_AR_BBP_DATA0		FIELD32(0x000000ff)
#घोषणा RALINKCSR_AR_BBP_ID0		FIELD32(0x0000ff00)
#घोषणा RALINKCSR_AR_BBP_DATA1		FIELD32(0x00ff0000)
#घोषणा RALINKCSR_AR_BBP_ID1		FIELD32(0xff000000)

/*
 * BCNCSR: Beacon पूर्णांकerval control रेजिस्टर.
 * CHANGE: Write one to change beacon पूर्णांकerval.
 * DELTATIME: The delta समय value.
 * NUM_BEACON: Number of beacon according to mode.
 * MODE: Please refer to asic specs.
 * PLUS: Plus or minus delta समय value.
 */
#घोषणा BCNCSR				0x00ec
#घोषणा BCNCSR_CHANGE			FIELD32(0x00000001)
#घोषणा BCNCSR_DELTATIME		FIELD32(0x0000001e)
#घोषणा BCNCSR_NUM_BEACON		FIELD32(0x00001fe0)
#घोषणा BCNCSR_MODE			FIELD32(0x00006000)
#घोषणा BCNCSR_PLUS			FIELD32(0x00008000)

/*
 * BBP / RF / IF Control Register.
 */

/*
 * BBPCSR: BBP serial control रेजिस्टर.
 * VALUE: Register value to program पूर्णांकo BBP.
 * REGNUM: Selected BBP रेजिस्टर.
 * BUSY: 1: asic is busy execute BBP programming.
 * WRITE_CONTROL: 1: ग_लिखो BBP, 0: पढ़ो BBP.
 */
#घोषणा BBPCSR				0x00f0
#घोषणा BBPCSR_VALUE			FIELD32(0x000000ff)
#घोषणा BBPCSR_REGNUM			FIELD32(0x00007f00)
#घोषणा BBPCSR_BUSY			FIELD32(0x00008000)
#घोषणा BBPCSR_WRITE_CONTROL		FIELD32(0x00010000)

/*
 * RFCSR: RF serial control रेजिस्टर.
 * VALUE: Register value + id to program पूर्णांकo rf/अगर.
 * NUMBER_OF_BITS: Number of bits used in value (i:20, rfmd:22).
 * IF_SELECT: Chip to program: 0: rf, 1: अगर.
 * PLL_LD: Rf pll_ld status.
 * BUSY: 1: asic is busy execute rf programming.
 */
#घोषणा RFCSR				0x00f4
#घोषणा RFCSR_VALUE			FIELD32(0x00ffffff)
#घोषणा RFCSR_NUMBER_OF_BITS		FIELD32(0x1f000000)
#घोषणा RFCSR_IF_SELECT			FIELD32(0x20000000)
#घोषणा RFCSR_PLL_LD			FIELD32(0x40000000)
#घोषणा RFCSR_BUSY			FIELD32(0x80000000)

/*
 * LEDCSR: LED control रेजिस्टर.
 * ON_PERIOD: On period, शेष 70ms.
 * OFF_PERIOD: Off period, शेष 30ms.
 * LINK: 0: linkoff, 1: linkup.
 * ACTIVITY: 0: idle, 1: active.
 */
#घोषणा LEDCSR				0x00f8
#घोषणा LEDCSR_ON_PERIOD		FIELD32(0x000000ff)
#घोषणा LEDCSR_OFF_PERIOD		FIELD32(0x0000ff00)
#घोषणा LEDCSR_LINK			FIELD32(0x00010000)
#घोषणा LEDCSR_ACTIVITY			FIELD32(0x00020000)

/*
 * ASIC poपूर्णांकer inक्रमmation.
 * RXPTR: Current RX ring address.
 * TXPTR: Current Tx ring address.
 * PRIPTR: Current Priority ring address.
 * ATIMPTR: Current ATIM ring address.
 */
#घोषणा RXPTR				0x0100
#घोषणा TXPTR				0x0104
#घोषणा PRIPTR				0x0108
#घोषणा ATIMPTR				0x010c

/*
 * GPIO and others.
 */

/*
 * GPIOCSR: GPIO control रेजिस्टर.
 *	GPIOCSR_VALx: Actual GPIO pin x value
 *	GPIOCSR_सूचीx: GPIO direction: 0 = output; 1 = input
 */
#घोषणा GPIOCSR				0x0120
#घोषणा GPIOCSR_VAL0			FIELD32(0x00000001)
#घोषणा GPIOCSR_VAL1			FIELD32(0x00000002)
#घोषणा GPIOCSR_VAL2			FIELD32(0x00000004)
#घोषणा GPIOCSR_VAL3			FIELD32(0x00000008)
#घोषणा GPIOCSR_VAL4			FIELD32(0x00000010)
#घोषणा GPIOCSR_VAL5			FIELD32(0x00000020)
#घोषणा GPIOCSR_VAL6			FIELD32(0x00000040)
#घोषणा GPIOCSR_VAL7			FIELD32(0x00000080)
#घोषणा GPIOCSR_सूची0			FIELD32(0x00000100)
#घोषणा GPIOCSR_सूची1			FIELD32(0x00000200)
#घोषणा GPIOCSR_सूची2			FIELD32(0x00000400)
#घोषणा GPIOCSR_सूची3			FIELD32(0x00000800)
#घोषणा GPIOCSR_सूची4			FIELD32(0x00001000)
#घोषणा GPIOCSR_सूची5			FIELD32(0x00002000)
#घोषणा GPIOCSR_सूची6			FIELD32(0x00004000)
#घोषणा GPIOCSR_सूची7			FIELD32(0x00008000)

/*
 * BBPPCSR: BBP Pin control रेजिस्टर.
 */
#घोषणा BBPPCSR				0x0124

/*
 * BCNCSR1: Tx BEACON offset समय control रेजिस्टर.
 * PRELOAD: Beacon समयr offset in units of usec.
 */
#घोषणा BCNCSR1				0x0130
#घोषणा BCNCSR1_PRELOAD			FIELD32(0x0000ffff)

/*
 * MACCSR2: TX_PE to RX_PE turn-around समय control रेजिस्टर
 * DELAY: RX_PE low width, in units of pci घड़ी cycle.
 */
#घोषणा MACCSR2				0x0134
#घोषणा MACCSR2_DELAY			FIELD32(0x000000ff)

/*
 * ARCSR2: 1 Mbps ACK/CTS PLCP.
 */
#घोषणा ARCSR2				0x013c
#घोषणा ARCSR2_SIGNAL			FIELD32(0x000000ff)
#घोषणा ARCSR2_SERVICE			FIELD32(0x0000ff00)
#घोषणा ARCSR2_LENGTH_LOW		FIELD32(0x00ff0000)
#घोषणा ARCSR2_LENGTH			FIELD32(0xffff0000)

/*
 * ARCSR3: 2 Mbps ACK/CTS PLCP.
 */
#घोषणा ARCSR3				0x0140
#घोषणा ARCSR3_SIGNAL			FIELD32(0x000000ff)
#घोषणा ARCSR3_SERVICE			FIELD32(0x0000ff00)
#घोषणा ARCSR3_LENGTH			FIELD32(0xffff0000)

/*
 * ARCSR4: 5.5 Mbps ACK/CTS PLCP.
 */
#घोषणा ARCSR4				0x0144
#घोषणा ARCSR4_SIGNAL			FIELD32(0x000000ff)
#घोषणा ARCSR4_SERVICE			FIELD32(0x0000ff00)
#घोषणा ARCSR4_LENGTH			FIELD32(0xffff0000)

/*
 * ARCSR5: 11 Mbps ACK/CTS PLCP.
 */
#घोषणा ARCSR5				0x0148
#घोषणा ARCSR5_SIGNAL			FIELD32(0x000000ff)
#घोषणा ARCSR5_SERVICE			FIELD32(0x0000ff00)
#घोषणा ARCSR5_LENGTH			FIELD32(0xffff0000)

/*
 * BBP रेजिस्टरs.
 * The wordsize of the BBP is 8 bits.
 */

/*
 * R1: TX antenna control
 */
#घोषणा BBP_R1_TX_ANTENNA		FIELD8(0x03)

/*
 * R4: RX antenna control
 */
#घोषणा BBP_R4_RX_ANTENNA		FIELD8(0x06)

/*
 * RF रेजिस्टरs
 */

/*
 * RF 1
 */
#घोषणा RF1_TUNER			FIELD32(0x00020000)

/*
 * RF 3
 */
#घोषणा RF3_TUNER			FIELD32(0x00000100)
#घोषणा RF3_TXPOWER			FIELD32(0x00003e00)

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
 * RF_TYPE: Rf_type of this adapter.
 * LED_MODE: 0: शेष, 1: TX/RX activity,2: Single (ignore link), 3: rsvd.
 * RX_AGCVGC: 0: disable, 1:enable BBP R13 tuning.
 * HARDWARE_RADIO: 1: Hardware controlled radio. Read GPIO0.
 */
#घोषणा EEPROM_ANTENNA			0x0b
#घोषणा EEPROM_ANTENNA_NUM		FIELD16(0x0003)
#घोषणा EEPROM_ANTENNA_TX_DEFAULT	FIELD16(0x000c)
#घोषणा EEPROM_ANTENNA_RX_DEFAULT	FIELD16(0x0030)
#घोषणा EEPROM_ANTENNA_RF_TYPE		FIELD16(0x0040)
#घोषणा EEPROM_ANTENNA_LED_MODE		FIELD16(0x0180)
#घोषणा EEPROM_ANTENNA_RX_AGCVGC_TUNING	FIELD16(0x0200)
#घोषणा EEPROM_ANTENNA_HARDWARE_RADIO	FIELD16(0x0400)

/*
 * EEPROM BBP.
 */
#घोषणा EEPROM_BBP_START		0x0c
#घोषणा EEPROM_BBP_SIZE			7
#घोषणा EEPROM_BBP_VALUE		FIELD16(0x00ff)
#घोषणा EEPROM_BBP_REG_ID		FIELD16(0xff00)

/*
 * EEPROM TXPOWER
 */
#घोषणा EEPROM_TXPOWER_START		0x13
#घोषणा EEPROM_TXPOWER_SIZE		7
#घोषणा EEPROM_TXPOWER_1		FIELD16(0x00ff)
#घोषणा EEPROM_TXPOWER_2		FIELD16(0xff00)

/*
 * DMA descriptor defines.
 */
#घोषणा TXD_DESC_SIZE			(8 * माप(__le32))
#घोषणा RXD_DESC_SIZE			(8 * माप(__le32))

/*
 * TX descriptor क्रमmat क्रम TX, PRIO, ATIM and Beacon Ring.
 */

/*
 * Word0
 */
#घोषणा TXD_W0_OWNER_NIC		FIELD32(0x00000001)
#घोषणा TXD_W0_VALID			FIELD32(0x00000002)
#घोषणा TXD_W0_RESULT			FIELD32(0x0000001c)
#घोषणा TXD_W0_RETRY_COUNT		FIELD32(0x000000e0)
#घोषणा TXD_W0_MORE_FRAG		FIELD32(0x00000100)
#घोषणा TXD_W0_ACK			FIELD32(0x00000200)
#घोषणा TXD_W0_TIMESTAMP		FIELD32(0x00000400)
#घोषणा TXD_W0_RTS			FIELD32(0x00000800)
#घोषणा TXD_W0_IFS			FIELD32(0x00006000)
#घोषणा TXD_W0_RETRY_MODE		FIELD32(0x00008000)
#घोषणा TXD_W0_AGC			FIELD32(0x00ff0000)
#घोषणा TXD_W0_R2			FIELD32(0xff000000)

/*
 * Word1
 */
#घोषणा TXD_W1_BUFFER_ADDRESS		FIELD32(0xffffffff)

/*
 * Word2
 */
#घोषणा TXD_W2_BUFFER_LENGTH		FIELD32(0x0000ffff)
#घोषणा TXD_W2_DATABYTE_COUNT		FIELD32(0xffff0000)

/*
 * Word3 & 4: PLCP inक्रमmation
 * The PLCP values should be treated as अगर they were BBP values.
 */
#घोषणा TXD_W3_PLCP_SIGNAL		FIELD32(0x000000ff)
#घोषणा TXD_W3_PLCP_SIGNAL_REGNUM	FIELD32(0x00007f00)
#घोषणा TXD_W3_PLCP_SIGNAL_BUSY		FIELD32(0x00008000)
#घोषणा TXD_W3_PLCP_SERVICE		FIELD32(0x00ff0000)
#घोषणा TXD_W3_PLCP_SERVICE_REGNUM	FIELD32(0x7f000000)
#घोषणा TXD_W3_PLCP_SERVICE_BUSY	FIELD32(0x80000000)

#घोषणा TXD_W4_PLCP_LENGTH_LOW		FIELD32(0x000000ff)
#घोषणा TXD_W3_PLCP_LENGTH_LOW_REGNUM	FIELD32(0x00007f00)
#घोषणा TXD_W3_PLCP_LENGTH_LOW_BUSY	FIELD32(0x00008000)
#घोषणा TXD_W4_PLCP_LENGTH_HIGH		FIELD32(0x00ff0000)
#घोषणा TXD_W3_PLCP_LENGTH_HIGH_REGNUM	FIELD32(0x7f000000)
#घोषणा TXD_W3_PLCP_LENGTH_HIGH_BUSY	FIELD32(0x80000000)

/*
 * Word5
 */
#घोषणा TXD_W5_BBCR4			FIELD32(0x0000ffff)
#घोषणा TXD_W5_AGC_REG			FIELD32(0x007f0000)
#घोषणा TXD_W5_AGC_REG_VALID		FIELD32(0x00800000)
#घोषणा TXD_W5_XXX_REG			FIELD32(0x7f000000)
#घोषणा TXD_W5_XXX_REG_VALID		FIELD32(0x80000000)

/*
 * Word6
 */
#घोषणा TXD_W6_SK_BUFF			FIELD32(0xffffffff)

/*
 * Word7
 */
#घोषणा TXD_W7_RESERVED			FIELD32(0xffffffff)

/*
 * RX descriptor क्रमmat क्रम RX Ring.
 */

/*
 * Word0
 */
#घोषणा RXD_W0_OWNER_NIC		FIELD32(0x00000001)
#घोषणा RXD_W0_UNICAST_TO_ME		FIELD32(0x00000002)
#घोषणा RXD_W0_MULTICAST		FIELD32(0x00000004)
#घोषणा RXD_W0_BROADCAST		FIELD32(0x00000008)
#घोषणा RXD_W0_MY_BSS			FIELD32(0x00000010)
#घोषणा RXD_W0_CRC_ERROR		FIELD32(0x00000020)
#घोषणा RXD_W0_PHYSICAL_ERROR		FIELD32(0x00000080)
#घोषणा RXD_W0_DATABYTE_COUNT		FIELD32(0xffff0000)

/*
 * Word1
 */
#घोषणा RXD_W1_BUFFER_ADDRESS		FIELD32(0xffffffff)

/*
 * Word2
 */
#घोषणा RXD_W2_BUFFER_LENGTH		FIELD32(0x0000ffff)
#घोषणा RXD_W2_BBR0			FIELD32(0x00ff0000)
#घोषणा RXD_W2_SIGNAL			FIELD32(0xff000000)

/*
 * Word3
 */
#घोषणा RXD_W3_RSSI			FIELD32(0x000000ff)
#घोषणा RXD_W3_BBR3			FIELD32(0x0000ff00)
#घोषणा RXD_W3_BBR4			FIELD32(0x00ff0000)
#घोषणा RXD_W3_BBR5			FIELD32(0xff000000)

/*
 * Word4
 */
#घोषणा RXD_W4_RX_END_TIME		FIELD32(0xffffffff)

/*
 * Word5 & 6 & 7: Reserved
 */
#घोषणा RXD_W5_RESERVED			FIELD32(0xffffffff)
#घोषणा RXD_W6_RESERVED			FIELD32(0xffffffff)
#घोषणा RXD_W7_RESERVED			FIELD32(0xffffffff)

/*
 * Macros क्रम converting txघातer from EEPROM to mac80211 value
 * and from mac80211 value to रेजिस्टर value.
 * NOTE: Logics in rt2400pci क्रम txघातer are reversed
 * compared to the other rt2x00 drivers. A higher txघातer
 * value means that the txघातer must be lowered. This is
 * important when converting the value coming from the
 * mac80211 stack to the rt2400 acceptable value.
 */
#घोषणा MIN_TXPOWER	31
#घोषणा MAX_TXPOWER	62
#घोषणा DEFAULT_TXPOWER	39

#घोषणा __CLAMP_TX(__txघातer) \
	clamp_t(अक्षर, (__txघातer), MIN_TXPOWER, MAX_TXPOWER)

#घोषणा TXPOWER_FROM_DEV(__txघातer) \
	((__CLAMP_TX(__txघातer) - MAX_TXPOWER) + MIN_TXPOWER)

#घोषणा TXPOWER_TO_DEV(__txघातer) \
	(MAX_TXPOWER - (__CLAMP_TX(__txघातer) - MIN_TXPOWER))

#पूर्ण_अगर /* RT2400PCI_H */
