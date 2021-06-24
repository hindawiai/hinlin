<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI TRF7970a RFID/NFC Transceiver Driver
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com
 *
 * Author: Erick Macias <emacias@ti.com>
 * Author: Felipe Balbi <balbi@ti.com>
 * Author: Mark A. Greer <mgreer@animalcreek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/nfc.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <net/nfc/nfc.h>
#समावेश <net/nfc/digital.h>

/* There are 3 ways the host can communicate with the trf7970a:
 * parallel mode, SPI with Slave Select (SS) mode, and SPI without
 * SS mode.  The driver only supports the two SPI modes.
 *
 * The trf7970a is very timing sensitive and the VIN, EN2, and EN
 * pins must निश्चितed in that order and with specअगरic delays in between.
 * The delays used in the driver were provided by TI and have been
 * confirmed to work with this driver.  There is a bug with the current
 * version of the trf7970a that requires that EN2 reमुख्य low no matter
 * what.  If it goes high, it will generate an RF field even when in
 * passive target mode.  TI has indicated that the chip will work okay
 * when EN2 is left low.  The 'en2-rf-quirk' device tree property
 * indicates that trf7970a currently being used has the erratum and
 * that EN2 must be kept low.
 *
 * Timeouts are implemented using the delayed workqueue kernel facility.
 * Timeouts are required so things करोn't hang when there is no response
 * from the trf7970a (or tag).  Using this mechanism creates a race with
 * पूर्णांकerrupts, however.  That is, an पूर्णांकerrupt and a समयout could occur
 * बंदly enough together that one is blocked by the mutex जबतक the other
 * executes.  When the समयout handler executes first and blocks the
 * पूर्णांकerrupt handler, it will eventually set the state to IDLE so the
 * पूर्णांकerrupt handler will check the state and निकास with no harm करोne.
 * When the पूर्णांकerrupt handler executes first and blocks the समयout handler,
 * the cancel_delayed_work() call will know that it didn't cancel the
 * work item (i.e., समयout) and will वापस zero.  That वापस code is
 * used by the समयr handler to indicate that it should ignore the समयout
 * once its unblocked.
 *
 * Aborting an active command isn't as simple as it seems because the only
 * way to पात a command that's alपढ़ोy been sent to the tag is so turn
 * off घातer to the tag.  If we करो that, though, we'd have to go through
 * the entire anticollision procedure again but the digital layer करोesn't
 * support that.  So, अगर an पात is received beक्रमe trf7970a_send_cmd()
 * has sent the command to the tag, it simply वापसs -ECANCELED.  If the
 * command has alपढ़ोy been sent to the tag, then the driver जारीs
 * normally and recieves the response data (or error) but just beक्रमe
 * sending the data upstream, it मुक्तs the rx_skb and sends -ECANCELED
 * upstream instead.  If the command failed, that error will be sent
 * upstream.
 *
 * When recieving data from a tag and the पूर्णांकerrupt status रेजिस्टर has
 * only the SRX bit set, it means that all of the data has been received
 * (once what's in the fअगरo has been पढ़ो).  However, depending on timing
 * an पूर्णांकerrupt status with only the SRX bit set may not be recived.  In
 * those हालs, the समयout mechanism is used to रुको 20 ms in हाल more
 * data arrives.  After 20 ms, it is assumed that all of the data has been
 * received and the accumulated rx data is sent upstream.  The
 * 'TRF7970A_ST_WAIT_FOR_RX_DATA_CONT' state is used क्रम this purpose
 * (i.e., it indicates that some data has been received but we're not sure
 * अगर there is more coming so a समयout in this state means all data has
 * been received and there isn't an error).  The delay is 20 ms since delays
 * of ~16 ms have been observed during testing.
 *
 * When transmitting a frame larger than the FIFO size (127 bytes), the
 * driver will रुको 20 ms क्रम the FIFO to drain past the low-watermark
 * and generate an पूर्णांकerrupt.  The low-watermark set to 32 bytes so the
 * पूर्णांकerrupt should fire after 127 - 32 = 95 bytes have been sent.  At
 * the lowest possible bit rate (6.62 kbps क्रम 15693), it will take up
 * to ~14.35 ms so 20 ms is used क्रम the समयout.
 *
 * Type 2 ग_लिखो and sector select commands respond with a 4-bit ACK or NACK.
 * Having only 4 bits in the FIFO won't normally generate an पूर्णांकerrupt so
 * driver enables the '4_bit_RX' bit of the Special Functions रेजिस्टर 1
 * to cause an पूर्णांकerrupt in that हाल.  Leaving that bit क्रम a पढ़ो command
 * messes up the data वापसed so it is only enabled when the framing is
 * 'NFC_DIGITAL_FRAMING_NFCA_T2T' and the command is not a पढ़ो command.
 * Unक्रमtunately, that means that the driver has to peek पूर्णांकo tx frames
 * when the framing is 'NFC_DIGITAL_FRAMING_NFCA_T2T'.  This is करोne by
 * the trf7970a_per_cmd_config() routine.
 *
 * ISO/IEC 15693 frames specअगरy whether to use single or द्विगुन sub-carrier
 * frequencies and whether to use low or high data rates in the flags byte
 * of the frame.  This means that the driver has to peek at all 15693 frames
 * to determine what speed to set the communication to.  In addition, ग_लिखो
 * and lock commands use the OPTION flag to indicate that an खातापूर्ण must be
 * sent to the tag beक्रमe it will send its response.  So the driver has to
 * examine all frames क्रम that reason too.
 *
 * It is unclear how दीर्घ to रुको beक्रमe sending the खातापूर्ण.  According to the
 * Note under Table 1-1 in section 1.6 of
 * http://www.ti.com/lit/ug/scbu011/scbu011.pdf, that रुको should be at least
 * 10 ms क्रम TI Tag-it HF-I tags; however testing has shown that is not दीर्घ
 * enough so 20 ms is used.  So the समयr is set to 40 ms - 20 ms to drain
 * up to 127 bytes in the FIFO at the lowest bit rate plus another 20 ms to
 * ensure the रुको is दीर्घ enough beक्रमe sending the खातापूर्ण.  This seems to work
 * reliably.
 */

#घोषणा TRF7970A_SUPPORTED_PROTOCOLS \
		(NFC_PROTO_MIFARE_MASK | NFC_PROTO_ISO14443_MASK |	\
		 NFC_PROTO_ISO14443_B_MASK | NFC_PROTO_FELICA_MASK | \
		 NFC_PROTO_ISO15693_MASK | NFC_PROTO_NFC_DEP_MASK)

#घोषणा TRF7970A_AUTOSUSPEND_DELAY		30000	/* 30 seconds */
#घोषणा TRF7970A_13MHZ_CLOCK_FREQUENCY		13560000
#घोषणा TRF7970A_27MHZ_CLOCK_FREQUENCY		27120000

#घोषणा TRF7970A_RX_SKB_ALLOC_SIZE		256

#घोषणा TRF7970A_FIFO_SIZE			127

/* TX length is 3 nibbles दीर्घ ==> 4KB - 1 bytes max */
#घोषणा TRF7970A_TX_MAX				(4096 - 1)

#घोषणा TRF7970A_WAIT_FOR_TX_IRQ		20
#घोषणा TRF7970A_WAIT_FOR_RX_DATA_TIMEOUT	20
#घोषणा TRF7970A_WAIT_FOR_FIFO_DRAIN_TIMEOUT	20
#घोषणा TRF7970A_WAIT_TO_ISSUE_ISO15693_खातापूर्ण	40

/* Guard बार क्रम various RF technologies (in us) */
#घोषणा TRF7970A_GUARD_TIME_NFCA		5000
#घोषणा TRF7970A_GUARD_TIME_NFCB		5000
#घोषणा TRF7970A_GUARD_TIME_NFCF		20000
#घोषणा TRF7970A_GUARD_TIME_15693		1000

/* Quirks */
/* Erratum: When पढ़ोing IRQ Status रेजिस्टर on trf7970a, we must issue a
 * पढ़ो continuous command क्रम IRQ Status and Collision Position रेजिस्टरs.
 */
#घोषणा TRF7970A_QUIRK_IRQ_STATUS_READ		BIT(0)
#घोषणा TRF7970A_QUIRK_EN2_MUST_STAY_LOW	BIT(1)

/* Direct commands */
#घोषणा TRF7970A_CMD_IDLE			0x00
#घोषणा TRF7970A_CMD_SOFT_INIT			0x03
#घोषणा TRF7970A_CMD_RF_COLLISION		0x04
#घोषणा TRF7970A_CMD_RF_COLLISION_RESPONSE_N	0x05
#घोषणा TRF7970A_CMD_RF_COLLISION_RESPONSE_0	0x06
#घोषणा TRF7970A_CMD_FIFO_RESET			0x0f
#घोषणा TRF7970A_CMD_TRANSMIT_NO_CRC		0x10
#घोषणा TRF7970A_CMD_TRANSMIT			0x11
#घोषणा TRF7970A_CMD_DELAY_TRANSMIT_NO_CRC	0x12
#घोषणा TRF7970A_CMD_DELAY_TRANSMIT		0x13
#घोषणा TRF7970A_CMD_खातापूर्ण			0x14
#घोषणा TRF7970A_CMD_CLOSE_SLOT			0x15
#घोषणा TRF7970A_CMD_BLOCK_RX			0x16
#घोषणा TRF7970A_CMD_ENABLE_RX			0x17
#घोषणा TRF7970A_CMD_TEST_INT_RF		0x18
#घोषणा TRF7970A_CMD_TEST_EXT_RF		0x19
#घोषणा TRF7970A_CMD_RX_GAIN_ADJUST		0x1a

/* Bits determining whether its a direct command or रेजिस्टर R/W,
 * whether to use a continuous SPI transaction or not, and the actual
 * direct cmd opcode or रेजिस्टर address.
 */
#घोषणा TRF7970A_CMD_BIT_CTRL			BIT(7)
#घोषणा TRF7970A_CMD_BIT_RW			BIT(6)
#घोषणा TRF7970A_CMD_BIT_CONTINUOUS		BIT(5)
#घोषणा TRF7970A_CMD_BIT_OPCODE(opcode)		((opcode) & 0x1f)

/* Registers addresses */
#घोषणा TRF7970A_CHIP_STATUS_CTRL		0x00
#घोषणा TRF7970A_ISO_CTRL			0x01
#घोषणा TRF7970A_ISO14443B_TX_OPTIONS		0x02
#घोषणा TRF7970A_ISO14443A_HIGH_BITRATE_OPTIONS	0x03
#घोषणा TRF7970A_TX_TIMER_SETTING_H_BYTE	0x04
#घोषणा TRF7970A_TX_TIMER_SETTING_L_BYTE	0x05
#घोषणा TRF7970A_TX_PULSE_LENGTH_CTRL		0x06
#घोषणा TRF7970A_RX_NO_RESPONSE_WAIT		0x07
#घोषणा TRF7970A_RX_WAIT_TIME			0x08
#घोषणा TRF7970A_MODULATOR_SYS_CLK_CTRL		0x09
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS		0x0a
#घोषणा TRF7970A_REG_IO_CTRL			0x0b
#घोषणा TRF7970A_IRQ_STATUS			0x0c
#घोषणा TRF7970A_COLLISION_IRQ_MASK		0x0d
#घोषणा TRF7970A_COLLISION_POSITION		0x0e
#घोषणा TRF7970A_RSSI_OSC_STATUS		0x0f
#घोषणा TRF7970A_SPECIAL_FCN_REG1		0x10
#घोषणा TRF7970A_SPECIAL_FCN_REG2		0x11
#घोषणा TRF7970A_RAM1				0x12
#घोषणा TRF7970A_RAM2				0x13
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS	0x14
#घोषणा TRF7970A_NFC_LOW_FIELD_LEVEL		0x16
#घोषणा TRF7970A_NFCID1				0x17
#घोषणा TRF7970A_NFC_TARGET_LEVEL		0x18
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL		0x19
#घोषणा TRF7970A_TEST_REGISTER1			0x1a
#घोषणा TRF7970A_TEST_REGISTER2			0x1b
#घोषणा TRF7970A_FIFO_STATUS			0x1c
#घोषणा TRF7970A_TX_LENGTH_BYTE1		0x1d
#घोषणा TRF7970A_TX_LENGTH_BYTE2		0x1e
#घोषणा TRF7970A_FIFO_IO_REGISTER		0x1f

/* Chip Status Control Register Bits */
#घोषणा TRF7970A_CHIP_STATUS_VRS5_3		BIT(0)
#घोषणा TRF7970A_CHIP_STATUS_REC_ON		BIT(1)
#घोषणा TRF7970A_CHIP_STATUS_AGC_ON		BIT(2)
#घोषणा TRF7970A_CHIP_STATUS_PM_ON		BIT(3)
#घोषणा TRF7970A_CHIP_STATUS_RF_PWR		BIT(4)
#घोषणा TRF7970A_CHIP_STATUS_RF_ON		BIT(5)
#घोषणा TRF7970A_CHIP_STATUS_सूचीECT		BIT(6)
#घोषणा TRF7970A_CHIP_STATUS_STBY		BIT(7)

/* ISO Control Register Bits */
#घोषणा TRF7970A_ISO_CTRL_15693_SGL_1OF4_662	0x00
#घोषणा TRF7970A_ISO_CTRL_15693_SGL_1OF256_662	0x01
#घोषणा TRF7970A_ISO_CTRL_15693_SGL_1OF4_2648	0x02
#घोषणा TRF7970A_ISO_CTRL_15693_SGL_1OF256_2648	0x03
#घोषणा TRF7970A_ISO_CTRL_15693_DBL_1OF4_667a	0x04
#घोषणा TRF7970A_ISO_CTRL_15693_DBL_1OF256_667	0x05
#घोषणा TRF7970A_ISO_CTRL_15693_DBL_1OF4_2669	0x06
#घोषणा TRF7970A_ISO_CTRL_15693_DBL_1OF256_2669	0x07
#घोषणा TRF7970A_ISO_CTRL_14443A_106		0x08
#घोषणा TRF7970A_ISO_CTRL_14443A_212		0x09
#घोषणा TRF7970A_ISO_CTRL_14443A_424		0x0a
#घोषणा TRF7970A_ISO_CTRL_14443A_848		0x0b
#घोषणा TRF7970A_ISO_CTRL_14443B_106		0x0c
#घोषणा TRF7970A_ISO_CTRL_14443B_212		0x0d
#घोषणा TRF7970A_ISO_CTRL_14443B_424		0x0e
#घोषणा TRF7970A_ISO_CTRL_14443B_848		0x0f
#घोषणा TRF7970A_ISO_CTRL_FELICA_212		0x1a
#घोषणा TRF7970A_ISO_CTRL_FELICA_424		0x1b
#घोषणा TRF7970A_ISO_CTRL_NFC_NFCA_106		0x01
#घोषणा TRF7970A_ISO_CTRL_NFC_NFCF_212		0x02
#घोषणा TRF7970A_ISO_CTRL_NFC_NFCF_424		0x03
#घोषणा TRF7970A_ISO_CTRL_NFC_CE_14443A		0x00
#घोषणा TRF7970A_ISO_CTRL_NFC_CE_14443B		0x01
#घोषणा TRF7970A_ISO_CTRL_NFC_CE		BIT(2)
#घोषणा TRF7970A_ISO_CTRL_NFC_ACTIVE		BIT(3)
#घोषणा TRF7970A_ISO_CTRL_NFC_INITIATOR		BIT(4)
#घोषणा TRF7970A_ISO_CTRL_NFC_NFC_CE_MODE	BIT(5)
#घोषणा TRF7970A_ISO_CTRL_RFID			BIT(5)
#घोषणा TRF7970A_ISO_CTRL_सूची_MODE		BIT(6)
#घोषणा TRF7970A_ISO_CTRL_RX_CRC_N		BIT(7)	/* true == No CRC */

#घोषणा TRF7970A_ISO_CTRL_RFID_SPEED_MASK	0x1f

/* Modulator and SYS_CLK Control Register Bits */
#घोषणा TRF7970A_MODULATOR_DEPTH(n)		((n) & 0x7)
#घोषणा TRF7970A_MODULATOR_DEPTH_ASK10		(TRF7970A_MODULATOR_DEPTH(0))
#घोषणा TRF7970A_MODULATOR_DEPTH_OOK		(TRF7970A_MODULATOR_DEPTH(1))
#घोषणा TRF7970A_MODULATOR_DEPTH_ASK7		(TRF7970A_MODULATOR_DEPTH(2))
#घोषणा TRF7970A_MODULATOR_DEPTH_ASK8_5		(TRF7970A_MODULATOR_DEPTH(3))
#घोषणा TRF7970A_MODULATOR_DEPTH_ASK13		(TRF7970A_MODULATOR_DEPTH(4))
#घोषणा TRF7970A_MODULATOR_DEPTH_ASK16		(TRF7970A_MODULATOR_DEPTH(5))
#घोषणा TRF7970A_MODULATOR_DEPTH_ASK22		(TRF7970A_MODULATOR_DEPTH(6))
#घोषणा TRF7970A_MODULATOR_DEPTH_ASK30		(TRF7970A_MODULATOR_DEPTH(7))
#घोषणा TRF7970A_MODULATOR_EN_ANA		BIT(3)
#घोषणा TRF7970A_MODULATOR_CLK(n)		(((n) & 0x3) << 4)
#घोषणा TRF7970A_MODULATOR_CLK_DISABLED		(TRF7970A_MODULATOR_CLK(0))
#घोषणा TRF7970A_MODULATOR_CLK_3_6		(TRF7970A_MODULATOR_CLK(1))
#घोषणा TRF7970A_MODULATOR_CLK_6_13		(TRF7970A_MODULATOR_CLK(2))
#घोषणा TRF7970A_MODULATOR_CLK_13_27		(TRF7970A_MODULATOR_CLK(3))
#घोषणा TRF7970A_MODULATOR_EN_OOK		BIT(6)
#घोषणा TRF7970A_MODULATOR_27MHZ		BIT(7)

#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_NO_LIM	BIT(0)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_AGCR	BIT(1)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_GD_0DB	(0x0 << 2)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_GD_5DB	(0x1 << 2)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_GD_10DB	(0x2 << 2)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_GD_15DB	(0x3 << 2)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_HBT	BIT(4)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_M848	BIT(5)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_C424	BIT(6)
#घोषणा TRF7970A_RX_SPECIAL_SETTINGS_C212	BIT(7)

#घोषणा TRF7970A_REG_IO_CTRL_VRS(v)		((v) & 0x07)
#घोषणा TRF7970A_REG_IO_CTRL_IO_LOW		BIT(5)
#घोषणा TRF7970A_REG_IO_CTRL_EN_EXT_PA		BIT(6)
#घोषणा TRF7970A_REG_IO_CTRL_AUTO_REG		BIT(7)

/* IRQ Status Register Bits */
#घोषणा TRF7970A_IRQ_STATUS_NORESP		BIT(0)	/* ISO15693 only */
#घोषणा TRF7970A_IRQ_STATUS_NFC_COL_ERROR	BIT(0)
#घोषणा TRF7970A_IRQ_STATUS_COL			BIT(1)
#घोषणा TRF7970A_IRQ_STATUS_FRAMING_खातापूर्ण_ERROR	BIT(2)
#घोषणा TRF7970A_IRQ_STATUS_NFC_RF		BIT(2)
#घोषणा TRF7970A_IRQ_STATUS_PARITY_ERROR	BIT(3)
#घोषणा TRF7970A_IRQ_STATUS_NFC_SDD		BIT(3)
#घोषणा TRF7970A_IRQ_STATUS_CRC_ERROR		BIT(4)
#घोषणा TRF7970A_IRQ_STATUS_NFC_PROTO_ERROR	BIT(4)
#घोषणा TRF7970A_IRQ_STATUS_FIFO		BIT(5)
#घोषणा TRF7970A_IRQ_STATUS_SRX			BIT(6)
#घोषणा TRF7970A_IRQ_STATUS_TX			BIT(7)

#घोषणा TRF7970A_IRQ_STATUS_ERROR				\
		(TRF7970A_IRQ_STATUS_COL |			\
		 TRF7970A_IRQ_STATUS_FRAMING_खातापूर्ण_ERROR |	\
		 TRF7970A_IRQ_STATUS_PARITY_ERROR |		\
		 TRF7970A_IRQ_STATUS_CRC_ERROR)

#घोषणा TRF7970A_RSSI_OSC_STATUS_RSSI_MASK	(BIT(2) | BIT(1) | BIT(0))
#घोषणा TRF7970A_RSSI_OSC_STATUS_RSSI_X_MASK	(BIT(5) | BIT(4) | BIT(3))
#घोषणा TRF7970A_RSSI_OSC_STATUS_RSSI_OSC_OK	BIT(6)

#घोषणा TRF7970A_SPECIAL_FCN_REG1_COL_7_6		BIT(0)
#घोषणा TRF7970A_SPECIAL_FCN_REG1_14_ANTICOLL		BIT(1)
#घोषणा TRF7970A_SPECIAL_FCN_REG1_4_BIT_RX		BIT(2)
#घोषणा TRF7970A_SPECIAL_FCN_REG1_SP_सूची_MODE		BIT(3)
#घोषणा TRF7970A_SPECIAL_FCN_REG1_NEXT_SLOT_37US	BIT(4)
#घोषणा TRF7970A_SPECIAL_FCN_REG1_PAR43			BIT(5)

#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLH_124	(0x0 << 2)
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLH_120	(0x1 << 2)
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLH_112	(0x2 << 2)
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLH_96	(0x3 << 2)
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLL_4	0x0
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLL_8	0x1
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLL_16	0x2
#घोषणा TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLL_32	0x3

#घोषणा TRF7970A_NFC_LOW_FIELD_LEVEL_RFDET(v)	((v) & 0x07)
#घोषणा TRF7970A_NFC_LOW_FIELD_LEVEL_CLEX_DIS	BIT(7)

#घोषणा TRF7970A_NFC_TARGET_LEVEL_RFDET(v)	((v) & 0x07)
#घोषणा TRF7970A_NFC_TARGET_LEVEL_HI_RF		BIT(3)
#घोषणा TRF7970A_NFC_TARGET_LEVEL_SDD_EN	BIT(5)
#घोषणा TRF7970A_NFC_TARGET_LEVEL_LD_S_4BYTES	(0x0 << 6)
#घोषणा TRF7970A_NFC_TARGET_LEVEL_LD_S_7BYTES	(0x1 << 6)
#घोषणा TRF7970A_NFC_TARGET_LEVEL_LD_S_10BYTES	(0x2 << 6)

#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_NFCBR_106		BIT(0)
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_NFCBR_212		BIT(1)
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_NFCBR_424		(BIT(0) | BIT(1))
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_PAS_14443B	BIT(2)
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_PAS_106		BIT(3)
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_FELICA		BIT(4)
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_RF_L		BIT(6)
#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_RF_H		BIT(7)

#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_106A		\
	 (TRF79070A_NFC_TARGET_PROTOCOL_RF_H |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_RF_L |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_PAS_106 |	\
	  TRF79070A_NFC_TARGET_PROTOCOL_NFCBR_106)

#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_106B		\
	 (TRF79070A_NFC_TARGET_PROTOCOL_RF_H |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_RF_L |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_PAS_14443B |	\
	  TRF79070A_NFC_TARGET_PROTOCOL_NFCBR_106)

#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_212F		\
	 (TRF79070A_NFC_TARGET_PROTOCOL_RF_H |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_RF_L |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_FELICA |	\
	  TRF79070A_NFC_TARGET_PROTOCOL_NFCBR_212)

#घोषणा TRF79070A_NFC_TARGET_PROTOCOL_424F		\
	 (TRF79070A_NFC_TARGET_PROTOCOL_RF_H |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_RF_L |		\
	  TRF79070A_NFC_TARGET_PROTOCOL_FELICA |	\
	  TRF79070A_NFC_TARGET_PROTOCOL_NFCBR_424)

#घोषणा TRF7970A_FIFO_STATUS_OVERFLOW		BIT(7)

/* NFC (ISO/IEC 14443A) Type 2 Tag commands */
#घोषणा NFC_T2T_CMD_READ			0x30

/* ISO 15693 commands codes */
#घोषणा ISO15693_CMD_INVENTORY			0x01
#घोषणा ISO15693_CMD_READ_SINGLE_BLOCK		0x20
#घोषणा ISO15693_CMD_WRITE_SINGLE_BLOCK		0x21
#घोषणा ISO15693_CMD_LOCK_BLOCK			0x22
#घोषणा ISO15693_CMD_READ_MULTIPLE_BLOCK	0x23
#घोषणा ISO15693_CMD_WRITE_MULTIPLE_BLOCK	0x24
#घोषणा ISO15693_CMD_SELECT			0x25
#घोषणा ISO15693_CMD_RESET_TO_READY		0x26
#घोषणा ISO15693_CMD_WRITE_AFI			0x27
#घोषणा ISO15693_CMD_LOCK_AFI			0x28
#घोषणा ISO15693_CMD_WRITE_DSFID		0x29
#घोषणा ISO15693_CMD_LOCK_DSFID			0x2a
#घोषणा ISO15693_CMD_GET_SYSTEM_INFO		0x2b
#घोषणा ISO15693_CMD_GET_MULTIPLE_BLOCK_SECURITY_STATUS	0x2c

/* ISO 15693 request and response flags */
#घोषणा ISO15693_REQ_FLAG_SUB_CARRIER		BIT(0)
#घोषणा ISO15693_REQ_FLAG_DATA_RATE		BIT(1)
#घोषणा ISO15693_REQ_FLAG_INVENTORY		BIT(2)
#घोषणा ISO15693_REQ_FLAG_PROTOCOL_EXT		BIT(3)
#घोषणा ISO15693_REQ_FLAG_SELECT		BIT(4)
#घोषणा ISO15693_REQ_FLAG_AFI			BIT(4)
#घोषणा ISO15693_REQ_FLAG_ADDRESS		BIT(5)
#घोषणा ISO15693_REQ_FLAG_NB_SLOTS		BIT(5)
#घोषणा ISO15693_REQ_FLAG_OPTION		BIT(6)

#घोषणा ISO15693_REQ_FLAG_SPEED_MASK \
		(ISO15693_REQ_FLAG_SUB_CARRIER | ISO15693_REQ_FLAG_DATA_RATE)

क्रमागत trf7970a_state अणु
	TRF7970A_ST_PWR_OFF,
	TRF7970A_ST_RF_OFF,
	TRF7970A_ST_IDLE,
	TRF7970A_ST_IDLE_RX_BLOCKED,
	TRF7970A_ST_WAIT_FOR_TX_FIFO,
	TRF7970A_ST_WAIT_FOR_RX_DATA,
	TRF7970A_ST_WAIT_FOR_RX_DATA_CONT,
	TRF7970A_ST_WAIT_TO_ISSUE_खातापूर्ण,
	TRF7970A_ST_LISTENING,
	TRF7970A_ST_LISTENING_MD,
	TRF7970A_ST_MAX
पूर्ण;

काष्ठा trf7970a अणु
	क्रमागत trf7970a_state		state;
	काष्ठा device			*dev;
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*regulator;
	काष्ठा nfc_digital_dev		*ddev;
	u32				quirks;
	bool				is_initiator;
	bool				पातing;
	काष्ठा sk_buff			*tx_skb;
	काष्ठा sk_buff			*rx_skb;
	nfc_digital_cmd_complete_t	cb;
	व्योम				*cb_arg;
	u8				chip_status_ctrl;
	u8				iso_ctrl;
	u8				iso_ctrl_tech;
	u8				modulator_sys_clk_ctrl;
	u8				special_fcn_reg1;
	u8				io_ctrl;
	अचिन्हित पूर्णांक			guard_समय;
	पूर्णांक				technology;
	पूर्णांक				framing;
	u8				md_rf_tech;
	u8				tx_cmd;
	bool				issue_eof;
	काष्ठा gpio_desc		*en_gpiod;
	काष्ठा gpio_desc		*en2_gpiod;
	काष्ठा mutex			lock;
	अचिन्हित पूर्णांक			समयout;
	bool				ignore_समयout;
	काष्ठा delayed_work		समयout_work;
पूर्ण;

अटल पूर्णांक trf7970a_cmd(काष्ठा trf7970a *trf, u8 opcode)
अणु
	u8 cmd = TRF7970A_CMD_BIT_CTRL | TRF7970A_CMD_BIT_OPCODE(opcode);
	पूर्णांक ret;

	dev_dbg(trf->dev, "cmd: 0x%x\n", cmd);

	ret = spi_ग_लिखो(trf->spi, &cmd, 1);
	अगर (ret)
		dev_err(trf->dev, "%s - cmd: 0x%x, ret: %d\n", __func__, cmd,
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_पढ़ो(काष्ठा trf7970a *trf, u8 reg, u8 *val)
अणु
	u8 addr = TRF7970A_CMD_BIT_RW | reg;
	पूर्णांक ret;

	ret = spi_ग_लिखो_then_पढ़ो(trf->spi, &addr, 1, val, 1);
	अगर (ret)
		dev_err(trf->dev, "%s - addr: 0x%x, ret: %d\n", __func__, addr,
			ret);

	dev_dbg(trf->dev, "read(0x%x): 0x%x\n", addr, *val);

	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_पढ़ो_cont(काष्ठा trf7970a *trf, u8 reg, u8 *buf,
			      माप_प्रकार len)
अणु
	u8 addr = reg | TRF7970A_CMD_BIT_RW | TRF7970A_CMD_BIT_CONTINUOUS;
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	पूर्णांक ret;

	dev_dbg(trf->dev, "read_cont(0x%x, %zd)\n", addr, len);

	spi_message_init(&m);

	स_रखो(&t, 0, माप(t));

	t[0].tx_buf = &addr;
	t[0].len = माप(addr);
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = len;
	spi_message_add_tail(&t[1], &m);

	ret = spi_sync(trf->spi, &m);
	अगर (ret)
		dev_err(trf->dev, "%s - addr: 0x%x, ret: %d\n", __func__, addr,
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_ग_लिखो(काष्ठा trf7970a *trf, u8 reg, u8 val)
अणु
	u8 buf[2] = अणु reg, val पूर्ण;
	पूर्णांक ret;

	dev_dbg(trf->dev, "write(0x%x): 0x%x\n", reg, val);

	ret = spi_ग_लिखो(trf->spi, buf, 2);
	अगर (ret)
		dev_err(trf->dev, "%s - write: 0x%x 0x%x, ret: %d\n", __func__,
			buf[0], buf[1], ret);

	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_पढ़ो_irqstatus(काष्ठा trf7970a *trf, u8 *status)
अणु
	पूर्णांक ret;
	u8 buf[2];
	u8 addr;

	addr = TRF7970A_IRQ_STATUS | TRF7970A_CMD_BIT_RW;

	अगर (trf->quirks & TRF7970A_QUIRK_IRQ_STATUS_READ) अणु
		addr |= TRF7970A_CMD_BIT_CONTINUOUS;
		ret = spi_ग_लिखो_then_पढ़ो(trf->spi, &addr, 1, buf, 2);
	पूर्ण अन्यथा अणु
		ret = spi_ग_लिखो_then_पढ़ो(trf->spi, &addr, 1, buf, 1);
	पूर्ण

	अगर (ret)
		dev_err(trf->dev, "%s - irqstatus: Status read failed: %d\n",
			__func__, ret);
	अन्यथा
		*status = buf[0];

	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_पढ़ो_target_proto(काष्ठा trf7970a *trf, u8 *target_proto)
अणु
	पूर्णांक ret;
	u8 buf[2];
	u8 addr;

	addr = TRF79070A_NFC_TARGET_PROTOCOL | TRF7970A_CMD_BIT_RW |
	       TRF7970A_CMD_BIT_CONTINUOUS;

	ret = spi_ग_लिखो_then_पढ़ो(trf->spi, &addr, 1, buf, 2);
	अगर (ret)
		dev_err(trf->dev, "%s - target_proto: Read failed: %d\n",
			__func__, ret);
	अन्यथा
		*target_proto = buf[0];

	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_mode_detect(काष्ठा trf7970a *trf, u8 *rf_tech)
अणु
	पूर्णांक ret;
	u8 target_proto, tech;

	ret = trf7970a_पढ़ो_target_proto(trf, &target_proto);
	अगर (ret)
		वापस ret;

	चयन (target_proto) अणु
	हाल TRF79070A_NFC_TARGET_PROTOCOL_106A:
		tech = NFC_DIGITAL_RF_TECH_106A;
		अवरोध;
	हाल TRF79070A_NFC_TARGET_PROTOCOL_106B:
		tech = NFC_DIGITAL_RF_TECH_106B;
		अवरोध;
	हाल TRF79070A_NFC_TARGET_PROTOCOL_212F:
		tech = NFC_DIGITAL_RF_TECH_212F;
		अवरोध;
	हाल TRF79070A_NFC_TARGET_PROTOCOL_424F:
		tech = NFC_DIGITAL_RF_TECH_424F;
		अवरोध;
	शेष:
		dev_dbg(trf->dev, "%s - mode_detect: target_proto: 0x%x\n",
			__func__, target_proto);
		वापस -EIO;
	पूर्ण

	*rf_tech = tech;

	वापस ret;
पूर्ण

अटल व्योम trf7970a_send_upstream(काष्ठा trf7970a *trf)
अणु
	dev_kमुक्त_skb_any(trf->tx_skb);
	trf->tx_skb = शून्य;

	अगर (trf->rx_skb && !IS_ERR(trf->rx_skb) && !trf->पातing)
		prपूर्णांक_hex_dump_debug("trf7970a rx data: ", DUMP_PREFIX_NONE,
				     16, 1, trf->rx_skb->data, trf->rx_skb->len,
				     false);

	trf->state = TRF7970A_ST_IDLE;

	अगर (trf->पातing) अणु
		dev_dbg(trf->dev, "Abort process complete\n");

		अगर (!IS_ERR(trf->rx_skb)) अणु
			kमुक्त_skb(trf->rx_skb);
			trf->rx_skb = ERR_PTR(-ECANCELED);
		पूर्ण

		trf->पातing = false;
	पूर्ण

	trf->cb(trf->ddev, trf->cb_arg, trf->rx_skb);

	trf->rx_skb = शून्य;
पूर्ण

अटल व्योम trf7970a_send_err_upstream(काष्ठा trf7970a *trf, पूर्णांक त्रुटि_सं)
अणु
	dev_dbg(trf->dev, "Error - state: %d, errno: %d\n", trf->state, त्रुटि_सं);

	cancel_delayed_work(&trf->समयout_work);

	kमुक्त_skb(trf->rx_skb);
	trf->rx_skb = ERR_PTR(त्रुटि_सं);

	trf7970a_send_upstream(trf);
पूर्ण

अटल पूर्णांक trf7970a_transmit(काष्ठा trf7970a *trf, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक len, u8 *prefix,
			     अचिन्हित पूर्णांक prefix_len)
अणु
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक ret;

	prपूर्णांक_hex_dump_debug("trf7970a tx data: ", DUMP_PREFIX_NONE,
			     16, 1, skb->data, len, false);

	spi_message_init(&m);

	स_रखो(&t, 0, माप(t));

	t[0].tx_buf = prefix;
	t[0].len = prefix_len;
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = skb->data;
	t[1].len = len;
	spi_message_add_tail(&t[1], &m);

	ret = spi_sync(trf->spi, &m);
	अगर (ret) अणु
		dev_err(trf->dev, "%s - Can't send tx data: %d\n", __func__,
			ret);
		वापस ret;
	पूर्ण

	skb_pull(skb, len);

	अगर (skb->len > 0) अणु
		trf->state = TRF7970A_ST_WAIT_FOR_TX_FIFO;
		समयout = TRF7970A_WAIT_FOR_FIFO_DRAIN_TIMEOUT;
	पूर्ण अन्यथा अणु
		अगर (trf->issue_eof) अणु
			trf->state = TRF7970A_ST_WAIT_TO_ISSUE_खातापूर्ण;
			समयout = TRF7970A_WAIT_TO_ISSUE_ISO15693_खातापूर्ण;
		पूर्ण अन्यथा अणु
			trf->state = TRF7970A_ST_WAIT_FOR_RX_DATA;

			अगर (!trf->समयout)
				समयout = TRF7970A_WAIT_FOR_TX_IRQ;
			अन्यथा
				समयout = trf->समयout;
		पूर्ण
	पूर्ण

	dev_dbg(trf->dev, "Setting timeout for %d ms, state: %d\n", समयout,
		trf->state);

	schedule_delayed_work(&trf->समयout_work, msecs_to_jअगरfies(समयout));

	वापस 0;
पूर्ण

अटल व्योम trf7970a_fill_fअगरo(काष्ठा trf7970a *trf)
अणु
	काष्ठा sk_buff *skb = trf->tx_skb;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;
	u8 fअगरo_bytes;
	u8 prefix;

	ret = trf7970a_पढ़ो(trf, TRF7970A_FIFO_STATUS, &fअगरo_bytes);
	अगर (ret) अणु
		trf7970a_send_err_upstream(trf, ret);
		वापस;
	पूर्ण

	dev_dbg(trf->dev, "Filling FIFO - fifo_bytes: 0x%x\n", fअगरo_bytes);

	fअगरo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;

	/* Calculate how much more data can be written to the fअगरo */
	len = TRF7970A_FIFO_SIZE - fअगरo_bytes;
	अगर (!len) अणु
		schedule_delayed_work(&trf->समयout_work,
			msecs_to_jअगरfies(TRF7970A_WAIT_FOR_FIFO_DRAIN_TIMEOUT));
		वापस;
	पूर्ण

	len = min(skb->len, len);

	prefix = TRF7970A_CMD_BIT_CONTINUOUS | TRF7970A_FIFO_IO_REGISTER;

	ret = trf7970a_transmit(trf, skb, len, &prefix, माप(prefix));
	अगर (ret)
		trf7970a_send_err_upstream(trf, ret);
पूर्ण

अटल व्योम trf7970a_drain_fअगरo(काष्ठा trf7970a *trf, u8 status)
अणु
	काष्ठा sk_buff *skb = trf->rx_skb;
	पूर्णांक ret;
	u8 fअगरo_bytes;

	अगर (status & TRF7970A_IRQ_STATUS_ERROR) अणु
		trf7970a_send_err_upstream(trf, -EIO);
		वापस;
	पूर्ण

	ret = trf7970a_पढ़ो(trf, TRF7970A_FIFO_STATUS, &fअगरo_bytes);
	अगर (ret) अणु
		trf7970a_send_err_upstream(trf, ret);
		वापस;
	पूर्ण

	dev_dbg(trf->dev, "Draining FIFO - fifo_bytes: 0x%x\n", fअगरo_bytes);

	fअगरo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;

	अगर (!fअगरo_bytes)
		जाओ no_rx_data;

	अगर (fअगरo_bytes > skb_tailroom(skb)) अणु
		skb = skb_copy_expand(skb, skb_headroom(skb),
				      max_t(पूर्णांक, fअगरo_bytes,
					    TRF7970A_RX_SKB_ALLOC_SIZE),
				      GFP_KERNEL);
		अगर (!skb) अणु
			trf7970a_send_err_upstream(trf, -ENOMEM);
			वापस;
		पूर्ण

		kमुक्त_skb(trf->rx_skb);
		trf->rx_skb = skb;
	पूर्ण

	ret = trf7970a_पढ़ो_cont(trf, TRF7970A_FIFO_IO_REGISTER,
				 skb_put(skb, fअगरo_bytes), fअगरo_bytes);
	अगर (ret) अणु
		trf7970a_send_err_upstream(trf, ret);
		वापस;
	पूर्ण

	/* If received Type 2 ACK/NACK, shअगरt right 4 bits and pass up */
	अगर ((trf->framing == NFC_DIGITAL_FRAMING_NFCA_T2T) && (skb->len == 1) &&
	    (trf->special_fcn_reg1 == TRF7970A_SPECIAL_FCN_REG1_4_BIT_RX)) अणु
		skb->data[0] >>= 4;
		status = TRF7970A_IRQ_STATUS_SRX;
	पूर्ण अन्यथा अणु
		trf->state = TRF7970A_ST_WAIT_FOR_RX_DATA_CONT;

		ret = trf7970a_पढ़ो(trf, TRF7970A_FIFO_STATUS, &fअगरo_bytes);
		अगर (ret) अणु
			trf7970a_send_err_upstream(trf, ret);
			वापस;
		पूर्ण

		fअगरo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;

		/* If there are bytes in the FIFO, set status to '0' so
		 * the अगर sपंचांगt below करोesn't fire and the driver will रुको
		 * क्रम the trf7970a to generate another RX पूर्णांकerrupt.
		 */
		अगर (fअगरo_bytes)
			status = 0;
	पूर्ण

no_rx_data:
	अगर (status == TRF7970A_IRQ_STATUS_SRX) अणु	/* Receive complete */
		trf7970a_send_upstream(trf);
		वापस;
	पूर्ण

	dev_dbg(trf->dev, "Setting timeout for %d ms\n",
		TRF7970A_WAIT_FOR_RX_DATA_TIMEOUT);

	schedule_delayed_work(&trf->समयout_work,
			   msecs_to_jअगरfies(TRF7970A_WAIT_FOR_RX_DATA_TIMEOUT));
पूर्ण

अटल irqवापस_t trf7970a_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा trf7970a *trf = dev_id;
	पूर्णांक ret;
	u8 status, fअगरo_bytes, iso_ctrl;

	mutex_lock(&trf->lock);

	अगर (trf->state == TRF7970A_ST_RF_OFF) अणु
		mutex_unlock(&trf->lock);
		वापस IRQ_NONE;
	पूर्ण

	ret = trf7970a_पढ़ो_irqstatus(trf, &status);
	अगर (ret) अणु
		mutex_unlock(&trf->lock);
		वापस IRQ_NONE;
	पूर्ण

	dev_dbg(trf->dev, "IRQ - state: %d, status: 0x%x\n", trf->state,
		status);

	अगर (!status) अणु
		mutex_unlock(&trf->lock);
		वापस IRQ_NONE;
	पूर्ण

	चयन (trf->state) अणु
	हाल TRF7970A_ST_IDLE:
	हाल TRF7970A_ST_IDLE_RX_BLOCKED:
		/* If initiator and getting पूर्णांकerrupts caused by RF noise,
		 * turn off the receiver to aव्योम unnecessary पूर्णांकerrupts.
		 * It will be turned back on in trf7970a_send_cmd() when
		 * the next command is issued.
		 */
		अगर (trf->is_initiator && (status & TRF7970A_IRQ_STATUS_ERROR)) अणु
			trf7970a_cmd(trf, TRF7970A_CMD_BLOCK_RX);
			trf->state = TRF7970A_ST_IDLE_RX_BLOCKED;
		पूर्ण

		trf7970a_cmd(trf, TRF7970A_CMD_FIFO_RESET);
		अवरोध;
	हाल TRF7970A_ST_WAIT_FOR_TX_FIFO:
		अगर (status & TRF7970A_IRQ_STATUS_TX) अणु
			trf->ignore_समयout =
			    !cancel_delayed_work(&trf->समयout_work);
			trf7970a_fill_fअगरo(trf);
		पूर्ण अन्यथा अणु
			trf7970a_send_err_upstream(trf, -EIO);
		पूर्ण
		अवरोध;
	हाल TRF7970A_ST_WAIT_FOR_RX_DATA:
	हाल TRF7970A_ST_WAIT_FOR_RX_DATA_CONT:
		अगर (status & TRF7970A_IRQ_STATUS_SRX) अणु
			trf->ignore_समयout =
			    !cancel_delayed_work(&trf->समयout_work);
			trf7970a_drain_fअगरo(trf, status);
		पूर्ण अन्यथा अगर (status & TRF7970A_IRQ_STATUS_FIFO) अणु
			ret = trf7970a_पढ़ो(trf, TRF7970A_FIFO_STATUS,
					    &fअगरo_bytes);

			fअगरo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;

			अगर (ret)
				trf7970a_send_err_upstream(trf, ret);
			अन्यथा अगर (!fअगरo_bytes)
				trf7970a_cmd(trf, TRF7970A_CMD_FIFO_RESET);
		पूर्ण अन्यथा अगर ((status == TRF7970A_IRQ_STATUS_TX) ||
			   (!trf->is_initiator &&
			    (status == (TRF7970A_IRQ_STATUS_TX |
					TRF7970A_IRQ_STATUS_NFC_RF)))) अणु
			trf7970a_cmd(trf, TRF7970A_CMD_FIFO_RESET);

			अगर (!trf->समयout) अणु
				trf->ignore_समयout =
				    !cancel_delayed_work(&trf->समयout_work);
				trf->rx_skb = ERR_PTR(0);
				trf7970a_send_upstream(trf);
				अवरोध;
			पूर्ण

			अगर (trf->is_initiator)
				अवरोध;

			iso_ctrl = trf->iso_ctrl;

			चयन (trf->framing) अणु
			हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD:
				trf->tx_cmd = TRF7970A_CMD_TRANSMIT_NO_CRC;
				iso_ctrl |= TRF7970A_ISO_CTRL_RX_CRC_N;
				trf->iso_ctrl = 0xff; /* Force ISO_CTRL ग_लिखो */
				अवरोध;
			हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A:
				trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
				iso_ctrl &= ~TRF7970A_ISO_CTRL_RX_CRC_N;
				trf->iso_ctrl = 0xff; /* Force ISO_CTRL ग_लिखो */
				अवरोध;
			हाल NFC_DIGITAL_FRAMING_NFCA_ANTICOL_COMPLETE:
				ret = trf7970a_ग_लिखो(trf,
					 TRF7970A_SPECIAL_FCN_REG1,
					 TRF7970A_SPECIAL_FCN_REG1_14_ANTICOLL);
				अगर (ret)
					जाओ err_unlock_निकास;

				trf->special_fcn_reg1 =
				    TRF7970A_SPECIAL_FCN_REG1_14_ANTICOLL;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			अगर (iso_ctrl != trf->iso_ctrl) अणु
				ret = trf7970a_ग_लिखो(trf, TRF7970A_ISO_CTRL,
						     iso_ctrl);
				अगर (ret)
					जाओ err_unlock_निकास;

				trf->iso_ctrl = iso_ctrl;
			पूर्ण
		पूर्ण अन्यथा अणु
			trf7970a_send_err_upstream(trf, -EIO);
		पूर्ण
		अवरोध;
	हाल TRF7970A_ST_WAIT_TO_ISSUE_खातापूर्ण:
		अगर (status != TRF7970A_IRQ_STATUS_TX)
			trf7970a_send_err_upstream(trf, -EIO);
		अवरोध;
	हाल TRF7970A_ST_LISTENING:
		अगर (status & TRF7970A_IRQ_STATUS_SRX) अणु
			trf->ignore_समयout =
			    !cancel_delayed_work(&trf->समयout_work);
			trf7970a_drain_fअगरo(trf, status);
		पूर्ण अन्यथा अगर (!(status & TRF7970A_IRQ_STATUS_NFC_RF)) अणु
			trf7970a_send_err_upstream(trf, -EIO);
		पूर्ण
		अवरोध;
	हाल TRF7970A_ST_LISTENING_MD:
		अगर (status & TRF7970A_IRQ_STATUS_SRX) अणु
			trf->ignore_समयout =
			    !cancel_delayed_work(&trf->समयout_work);

			ret = trf7970a_mode_detect(trf, &trf->md_rf_tech);
			अगर (ret) अणु
				trf7970a_send_err_upstream(trf, ret);
			पूर्ण अन्यथा अणु
				trf->state = TRF7970A_ST_LISTENING;
				trf7970a_drain_fअगरo(trf, status);
			पूर्ण
		पूर्ण अन्यथा अगर (!(status & TRF7970A_IRQ_STATUS_NFC_RF)) अणु
			trf7970a_send_err_upstream(trf, -EIO);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(trf->dev, "%s - Driver in invalid state: %d\n",
			__func__, trf->state);
	पूर्ण

err_unlock_निकास:
	mutex_unlock(&trf->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम trf7970a_issue_eof(काष्ठा trf7970a *trf)
अणु
	पूर्णांक ret;

	dev_dbg(trf->dev, "Issuing EOF\n");

	ret = trf7970a_cmd(trf, TRF7970A_CMD_FIFO_RESET);
	अगर (ret)
		trf7970a_send_err_upstream(trf, ret);

	ret = trf7970a_cmd(trf, TRF7970A_CMD_खातापूर्ण);
	अगर (ret)
		trf7970a_send_err_upstream(trf, ret);

	trf->state = TRF7970A_ST_WAIT_FOR_RX_DATA;

	dev_dbg(trf->dev, "Setting timeout for %d ms, state: %d\n",
		trf->समयout, trf->state);

	schedule_delayed_work(&trf->समयout_work,
			      msecs_to_jअगरfies(trf->समयout));
पूर्ण

अटल व्योम trf7970a_समयout_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा trf7970a *trf = container_of(work, काष्ठा trf7970a,
					    समयout_work.work);

	dev_dbg(trf->dev, "Timeout - state: %d, ignore_timeout: %d\n",
		trf->state, trf->ignore_समयout);

	mutex_lock(&trf->lock);

	अगर (trf->ignore_समयout)
		trf->ignore_समयout = false;
	अन्यथा अगर (trf->state == TRF7970A_ST_WAIT_FOR_RX_DATA_CONT)
		trf7970a_drain_fअगरo(trf, TRF7970A_IRQ_STATUS_SRX);
	अन्यथा अगर (trf->state == TRF7970A_ST_WAIT_TO_ISSUE_खातापूर्ण)
		trf7970a_issue_eof(trf);
	अन्यथा
		trf7970a_send_err_upstream(trf, -ETIMEDOUT);

	mutex_unlock(&trf->lock);
पूर्ण

अटल पूर्णांक trf7970a_init(काष्ठा trf7970a *trf)
अणु
	पूर्णांक ret;

	dev_dbg(trf->dev, "Initializing device - state: %d\n", trf->state);

	ret = trf7970a_cmd(trf, TRF7970A_CMD_SOFT_INIT);
	अगर (ret)
		जाओ err_out;

	ret = trf7970a_cmd(trf, TRF7970A_CMD_IDLE);
	अगर (ret)
		जाओ err_out;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_REG_IO_CTRL,
			     trf->io_ctrl | TRF7970A_REG_IO_CTRL_VRS(0x1));
	अगर (ret)
		जाओ err_out;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_NFC_TARGET_LEVEL, 0);
	अगर (ret)
		जाओ err_out;

	usleep_range(1000, 2000);

	trf->chip_status_ctrl &= ~TRF7970A_CHIP_STATUS_RF_ON;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_MODULATOR_SYS_CLK_CTRL,
			     trf->modulator_sys_clk_ctrl);
	अगर (ret)
		जाओ err_out;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS,
			     TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLH_96 |
			     TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLL_32);
	अगर (ret)
		जाओ err_out;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_SPECIAL_FCN_REG1, 0);
	अगर (ret)
		जाओ err_out;

	trf->special_fcn_reg1 = 0;

	trf->iso_ctrl = 0xff;
	वापस 0;

err_out:
	dev_dbg(trf->dev, "Couldn't init device: %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम trf7970a_चयन_rf_off(काष्ठा trf7970a *trf)
अणु
	अगर ((trf->state == TRF7970A_ST_PWR_OFF) ||
	    (trf->state == TRF7970A_ST_RF_OFF))
		वापस;

	dev_dbg(trf->dev, "Switching rf off\n");

	trf->chip_status_ctrl &= ~TRF7970A_CHIP_STATUS_RF_ON;

	trf7970a_ग_लिखो(trf, TRF7970A_CHIP_STATUS_CTRL, trf->chip_status_ctrl);

	trf->पातing = false;
	trf->state = TRF7970A_ST_RF_OFF;

	pm_runसमय_mark_last_busy(trf->dev);
	pm_runसमय_put_स्वतःsuspend(trf->dev);
पूर्ण

अटल पूर्णांक trf7970a_चयन_rf_on(काष्ठा trf7970a *trf)
अणु
	पूर्णांक ret;

	dev_dbg(trf->dev, "Switching rf on\n");

	pm_runसमय_get_sync(trf->dev);

	अगर (trf->state != TRF7970A_ST_RF_OFF) अणु	/* Power on, RF off */
		dev_err(trf->dev, "%s - Incorrect state: %d\n", __func__,
			trf->state);
		वापस -EINVAL;
	पूर्ण

	ret = trf7970a_init(trf);
	अगर (ret) अणु
		dev_err(trf->dev, "%s - Can't initialize: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	trf->state = TRF7970A_ST_IDLE;

	वापस 0;
पूर्ण

अटल पूर्णांक trf7970a_चयन_rf(काष्ठा nfc_digital_dev *ddev, bool on)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);
	पूर्णांक ret = 0;

	dev_dbg(trf->dev, "Switching RF - state: %d, on: %d\n", trf->state, on);

	mutex_lock(&trf->lock);

	अगर (on) अणु
		चयन (trf->state) अणु
		हाल TRF7970A_ST_PWR_OFF:
		हाल TRF7970A_ST_RF_OFF:
			ret = trf7970a_चयन_rf_on(trf);
			अवरोध;
		हाल TRF7970A_ST_IDLE:
		हाल TRF7970A_ST_IDLE_RX_BLOCKED:
			अवरोध;
		शेष:
			dev_err(trf->dev, "%s - Invalid request: %d %d\n",
				__func__, trf->state, on);
			trf7970a_चयन_rf_off(trf);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (trf->state) अणु
		हाल TRF7970A_ST_PWR_OFF:
		हाल TRF7970A_ST_RF_OFF:
			अवरोध;
		शेष:
			dev_err(trf->dev, "%s - Invalid request: %d %d\n",
				__func__, trf->state, on);
			ret = -EINVAL;
			fallthrough;
		हाल TRF7970A_ST_IDLE:
		हाल TRF7970A_ST_IDLE_RX_BLOCKED:
		हाल TRF7970A_ST_WAIT_FOR_RX_DATA:
		हाल TRF7970A_ST_WAIT_FOR_RX_DATA_CONT:
			trf7970a_चयन_rf_off(trf);
		पूर्ण
	पूर्ण

	mutex_unlock(&trf->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_in_config_rf_tech(काष्ठा trf7970a *trf, पूर्णांक tech)
अणु
	पूर्णांक ret = 0;

	dev_dbg(trf->dev, "rf technology: %d\n", tech);

	चयन (tech) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_14443A_106;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_OOK;
		trf->guard_समय = TRF7970A_GUARD_TIME_NFCA;
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_106B:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_14443B_106;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		trf->guard_समय = TRF7970A_GUARD_TIME_NFCB;
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_212F:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_FELICA_212;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		trf->guard_समय = TRF7970A_GUARD_TIME_NFCF;
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_424F:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_FELICA_424;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		trf->guard_समय = TRF7970A_GUARD_TIME_NFCF;
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_ISO15693:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_15693_SGL_1OF4_2648;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_OOK;
		trf->guard_समय = TRF7970A_GUARD_TIME_15693;
		अवरोध;
	शेष:
		dev_dbg(trf->dev, "Unsupported rf technology: %d\n", tech);
		वापस -EINVAL;
	पूर्ण

	trf->technology = tech;

	/* If in initiator mode and not changing the RF tech due to a
	 * PSL sequence (indicated by 'trf->iso_ctrl == 0xff' from
	 * trf7970a_init()), clear the NFC Target Detection Level रेजिस्टर
	 * due to erratum.
	 */
	अगर (trf->iso_ctrl == 0xff)
		ret = trf7970a_ग_लिखो(trf, TRF7970A_NFC_TARGET_LEVEL, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_is_rf_field(काष्ठा trf7970a *trf, bool *is_rf_field)
अणु
	पूर्णांक ret;
	u8 rssi;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_CHIP_STATUS_CTRL,
			     trf->chip_status_ctrl |
			     TRF7970A_CHIP_STATUS_REC_ON);
	अगर (ret)
		वापस ret;

	ret = trf7970a_cmd(trf, TRF7970A_CMD_TEST_EXT_RF);
	अगर (ret)
		वापस ret;

	usleep_range(50, 60);

	ret = trf7970a_पढ़ो(trf, TRF7970A_RSSI_OSC_STATUS, &rssi);
	अगर (ret)
		वापस ret;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_CHIP_STATUS_CTRL,
			     trf->chip_status_ctrl);
	अगर (ret)
		वापस ret;

	अगर (rssi & TRF7970A_RSSI_OSC_STATUS_RSSI_MASK)
		*is_rf_field = true;
	अन्यथा
		*is_rf_field = false;

	वापस 0;
पूर्ण

अटल पूर्णांक trf7970a_in_config_framing(काष्ठा trf7970a *trf, पूर्णांक framing)
अणु
	u8 iso_ctrl = trf->iso_ctrl_tech;
	bool is_rf_field = false;
	पूर्णांक ret;

	dev_dbg(trf->dev, "framing: %d\n", framing);

	चयन (framing) अणु
	हाल NFC_DIGITAL_FRAMING_NFCA_SHORT:
	हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT_NO_CRC;
		iso_ctrl |= TRF7970A_ISO_CTRL_RX_CRC_N;
		अवरोध;
	हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A:
	हाल NFC_DIGITAL_FRAMING_NFCA_T4T:
	हाल NFC_DIGITAL_FRAMING_NFCB:
	हाल NFC_DIGITAL_FRAMING_NFCB_T4T:
	हाल NFC_DIGITAL_FRAMING_NFCF:
	हाल NFC_DIGITAL_FRAMING_NFCF_T3T:
	हाल NFC_DIGITAL_FRAMING_ISO15693_INVENTORY:
	हाल NFC_DIGITAL_FRAMING_ISO15693_T5T:
	हाल NFC_DIGITAL_FRAMING_NFCA_NFC_DEP:
	हाल NFC_DIGITAL_FRAMING_NFCF_NFC_DEP:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl &= ~TRF7970A_ISO_CTRL_RX_CRC_N;
		अवरोध;
	हाल NFC_DIGITAL_FRAMING_NFCA_T2T:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl |= TRF7970A_ISO_CTRL_RX_CRC_N;
		अवरोध;
	शेष:
		dev_dbg(trf->dev, "Unsupported Framing: %d\n", framing);
		वापस -EINVAL;
	पूर्ण

	trf->framing = framing;

	अगर (!(trf->chip_status_ctrl & TRF7970A_CHIP_STATUS_RF_ON)) अणु
		ret = trf7970a_is_rf_field(trf, &is_rf_field);
		अगर (ret)
			वापस ret;

		अगर (is_rf_field)
			वापस -EBUSY;
	पूर्ण

	अगर (iso_ctrl != trf->iso_ctrl) अणु
		ret = trf7970a_ग_लिखो(trf, TRF7970A_ISO_CTRL, iso_ctrl);
		अगर (ret)
			वापस ret;

		trf->iso_ctrl = iso_ctrl;

		ret = trf7970a_ग_लिखो(trf, TRF7970A_MODULATOR_SYS_CLK_CTRL,
				     trf->modulator_sys_clk_ctrl);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!(trf->chip_status_ctrl & TRF7970A_CHIP_STATUS_RF_ON)) अणु
		ret = trf7970a_ग_लिखो(trf, TRF7970A_CHIP_STATUS_CTRL,
				     trf->chip_status_ctrl |
				     TRF7970A_CHIP_STATUS_RF_ON);
		अगर (ret)
			वापस ret;

		trf->chip_status_ctrl |= TRF7970A_CHIP_STATUS_RF_ON;

		usleep_range(trf->guard_समय, trf->guard_समय + 1000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक trf7970a_in_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type,
				    पूर्णांक param)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);
	पूर्णांक ret;

	dev_dbg(trf->dev, "Configure hw - type: %d, param: %d\n", type, param);

	mutex_lock(&trf->lock);

	trf->is_initiator = true;

	अगर ((trf->state == TRF7970A_ST_PWR_OFF) ||
	    (trf->state == TRF7970A_ST_RF_OFF)) अणु
		ret = trf7970a_चयन_rf_on(trf);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण

	चयन (type) अणु
	हाल NFC_DIGITAL_CONFIG_RF_TECH:
		ret = trf7970a_in_config_rf_tech(trf, param);
		अवरोध;
	हाल NFC_DIGITAL_CONFIG_FRAMING:
		ret = trf7970a_in_config_framing(trf, param);
		अवरोध;
	शेष:
		dev_dbg(trf->dev, "Unknown type: %d\n", type);
		ret = -EINVAL;
	पूर्ण

err_unlock:
	mutex_unlock(&trf->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_is_iso15693_ग_लिखो_or_lock(u8 cmd)
अणु
	चयन (cmd) अणु
	हाल ISO15693_CMD_WRITE_SINGLE_BLOCK:
	हाल ISO15693_CMD_LOCK_BLOCK:
	हाल ISO15693_CMD_WRITE_MULTIPLE_BLOCK:
	हाल ISO15693_CMD_WRITE_AFI:
	हाल ISO15693_CMD_LOCK_AFI:
	हाल ISO15693_CMD_WRITE_DSFID:
	हाल ISO15693_CMD_LOCK_DSFID:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक trf7970a_per_cmd_config(काष्ठा trf7970a *trf, काष्ठा sk_buff *skb)
अणु
	u8 *req = skb->data;
	u8 special_fcn_reg1, iso_ctrl;
	पूर्णांक ret;

	trf->issue_eof = false;

	/* When issuing Type 2 पढ़ो command, make sure the '4_bit_RX' bit in
	 * special functions रेजिस्टर 1 is cleared; otherwise, its a ग_लिखो or
	 * sector select command and '4_bit_RX' must be set.
	 *
	 * When issuing an ISO 15693 command, inspect the flags byte to see
	 * what speed to use.  Also, remember अगर the OPTION flag is set on
	 * a Type 5 ग_लिखो or lock command so the driver will know that it
	 * has to send an खातापूर्ण in order to get a response.
	 */
	अगर ((trf->technology == NFC_DIGITAL_RF_TECH_106A) &&
	    (trf->framing == NFC_DIGITAL_FRAMING_NFCA_T2T)) अणु
		अगर (req[0] == NFC_T2T_CMD_READ)
			special_fcn_reg1 = 0;
		अन्यथा
			special_fcn_reg1 = TRF7970A_SPECIAL_FCN_REG1_4_BIT_RX;

		अगर (special_fcn_reg1 != trf->special_fcn_reg1) अणु
			ret = trf7970a_ग_लिखो(trf, TRF7970A_SPECIAL_FCN_REG1,
					     special_fcn_reg1);
			अगर (ret)
				वापस ret;

			trf->special_fcn_reg1 = special_fcn_reg1;
		पूर्ण
	पूर्ण अन्यथा अगर (trf->technology == NFC_DIGITAL_RF_TECH_ISO15693) अणु
		iso_ctrl = trf->iso_ctrl & ~TRF7970A_ISO_CTRL_RFID_SPEED_MASK;

		चयन (req[0] & ISO15693_REQ_FLAG_SPEED_MASK) अणु
		हाल 0x00:
			iso_ctrl |= TRF7970A_ISO_CTRL_15693_SGL_1OF4_662;
			अवरोध;
		हाल ISO15693_REQ_FLAG_SUB_CARRIER:
			iso_ctrl |= TRF7970A_ISO_CTRL_15693_DBL_1OF4_667a;
			अवरोध;
		हाल ISO15693_REQ_FLAG_DATA_RATE:
			iso_ctrl |= TRF7970A_ISO_CTRL_15693_SGL_1OF4_2648;
			अवरोध;
		हाल (ISO15693_REQ_FLAG_SUB_CARRIER |
		      ISO15693_REQ_FLAG_DATA_RATE):
			iso_ctrl |= TRF7970A_ISO_CTRL_15693_DBL_1OF4_2669;
			अवरोध;
		पूर्ण

		अगर (iso_ctrl != trf->iso_ctrl) अणु
			ret = trf7970a_ग_लिखो(trf, TRF7970A_ISO_CTRL, iso_ctrl);
			अगर (ret)
				वापस ret;

			trf->iso_ctrl = iso_ctrl;
		पूर्ण

		अगर ((trf->framing == NFC_DIGITAL_FRAMING_ISO15693_T5T) &&
		    trf7970a_is_iso15693_ग_लिखो_or_lock(req[1]) &&
		    (req[0] & ISO15693_REQ_FLAG_OPTION))
			trf->issue_eof = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक trf7970a_send_cmd(काष्ठा nfc_digital_dev *ddev,
			     काष्ठा sk_buff *skb, u16 समयout,
			     nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);
	u8 prefix[5];
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;
	u8 status;

	dev_dbg(trf->dev, "New request - state: %d, timeout: %d ms, len: %d\n",
		trf->state, समयout, skb->len);

	अगर (skb->len > TRF7970A_TX_MAX)
		वापस -EINVAL;

	mutex_lock(&trf->lock);

	अगर ((trf->state != TRF7970A_ST_IDLE) &&
	    (trf->state != TRF7970A_ST_IDLE_RX_BLOCKED)) अणु
		dev_err(trf->dev, "%s - Bogus state: %d\n", __func__,
			trf->state);
		ret = -EIO;
		जाओ out_err;
	पूर्ण

	अगर (trf->पातing) अणु
		dev_dbg(trf->dev, "Abort process complete\n");
		trf->पातing = false;
		ret = -ECANCELED;
		जाओ out_err;
	पूर्ण

	अगर (समयout) अणु
		trf->rx_skb = nfc_alloc_recv_skb(TRF7970A_RX_SKB_ALLOC_SIZE,
						 GFP_KERNEL);
		अगर (!trf->rx_skb) अणु
			dev_dbg(trf->dev, "Can't alloc rx_skb\n");
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (trf->state == TRF7970A_ST_IDLE_RX_BLOCKED) अणु
		ret = trf7970a_cmd(trf, TRF7970A_CMD_ENABLE_RX);
		अगर (ret)
			जाओ out_err;

		trf->state = TRF7970A_ST_IDLE;
	पूर्ण

	अगर (trf->is_initiator) अणु
		ret = trf7970a_per_cmd_config(trf, skb);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	trf->ddev = ddev;
	trf->tx_skb = skb;
	trf->cb = cb;
	trf->cb_arg = arg;
	trf->समयout = समयout;
	trf->ignore_समयout = false;

	len = skb->len;

	/* TX data must be prefixed with a FIFO reset cmd, a cmd that depends
	 * on what the current framing is, the address of the TX length byte 1
	 * रेजिस्टर (0x1d), and the 2 byte length of the data to be transmitted.
	 * That totals 5 bytes.
	 */
	prefix[0] = TRF7970A_CMD_BIT_CTRL |
	    TRF7970A_CMD_BIT_OPCODE(TRF7970A_CMD_FIFO_RESET);
	prefix[1] = TRF7970A_CMD_BIT_CTRL |
	    TRF7970A_CMD_BIT_OPCODE(trf->tx_cmd);
	prefix[2] = TRF7970A_CMD_BIT_CONTINUOUS | TRF7970A_TX_LENGTH_BYTE1;

	अगर (trf->framing == NFC_DIGITAL_FRAMING_NFCA_SHORT) अणु
		prefix[3] = 0x00;
		prefix[4] = 0x0f;	/* 7 bits */
	पूर्ण अन्यथा अणु
		prefix[3] = (len & 0xf00) >> 4;
		prefix[3] |= ((len & 0xf0) >> 4);
		prefix[4] = ((len & 0x0f) << 4);
	पूर्ण

	len = min_t(पूर्णांक, skb->len, TRF7970A_FIFO_SIZE);

	/* Clear possible spurious पूर्णांकerrupt */
	ret = trf7970a_पढ़ो_irqstatus(trf, &status);
	अगर (ret)
		जाओ out_err;

	ret = trf7970a_transmit(trf, skb, len, prefix, माप(prefix));
	अगर (ret) अणु
		kमुक्त_skb(trf->rx_skb);
		trf->rx_skb = शून्य;
	पूर्ण

out_err:
	mutex_unlock(&trf->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_tg_config_rf_tech(काष्ठा trf7970a *trf, पूर्णांक tech)
अणु
	पूर्णांक ret = 0;

	dev_dbg(trf->dev, "rf technology: %d\n", tech);

	चयन (tech) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_NFC_NFC_CE_MODE |
		    TRF7970A_ISO_CTRL_NFC_CE | TRF7970A_ISO_CTRL_NFC_CE_14443A;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_OOK;
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_212F:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_NFC_NFC_CE_MODE |
		    TRF7970A_ISO_CTRL_NFC_NFCF_212;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_424F:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_NFC_NFC_CE_MODE |
		    TRF7970A_ISO_CTRL_NFC_NFCF_424;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		अवरोध;
	शेष:
		dev_dbg(trf->dev, "Unsupported rf technology: %d\n", tech);
		वापस -EINVAL;
	पूर्ण

	trf->technology = tech;

	/* Normally we ग_लिखो the ISO_CTRL रेजिस्टर in
	 * trf7970a_tg_config_framing() because the framing can change
	 * the value written.  However, when sending a PSL RES,
	 * digital_tg_send_psl_res_complete() करोesn't call
	 * trf7970a_tg_config_framing() so we must ग_लिखो the रेजिस्टर
	 * here.
	 */
	अगर ((trf->framing == NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED) &&
	    (trf->iso_ctrl_tech != trf->iso_ctrl)) अणु
		ret = trf7970a_ग_लिखो(trf, TRF7970A_ISO_CTRL,
				     trf->iso_ctrl_tech);

		trf->iso_ctrl = trf->iso_ctrl_tech;
	पूर्ण

	वापस ret;
पूर्ण

/* Since this is a target routine, several of the framing calls are
 * made between receiving the request and sending the response so they
 * should take effect until after the response is sent.  This is accomplished
 * by skipping the ISO_CTRL रेजिस्टर ग_लिखो here and करोing it in the पूर्णांकerrupt
 * handler.
 */
अटल पूर्णांक trf7970a_tg_config_framing(काष्ठा trf7970a *trf, पूर्णांक framing)
अणु
	u8 iso_ctrl = trf->iso_ctrl_tech;
	पूर्णांक ret;

	dev_dbg(trf->dev, "framing: %d\n", framing);

	चयन (framing) अणु
	हाल NFC_DIGITAL_FRAMING_NFCA_NFC_DEP:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT_NO_CRC;
		iso_ctrl |= TRF7970A_ISO_CTRL_RX_CRC_N;
		अवरोध;
	हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD:
	हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A:
	हाल NFC_DIGITAL_FRAMING_NFCA_ANTICOL_COMPLETE:
		/* These ones are applied in the पूर्णांकerrupt handler */
		iso_ctrl = trf->iso_ctrl; /* Don't ग_लिखो to ISO_CTRL yet */
		अवरोध;
	हाल NFC_DIGITAL_FRAMING_NFCF_NFC_DEP:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl &= ~TRF7970A_ISO_CTRL_RX_CRC_N;
		अवरोध;
	हाल NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl &= ~TRF7970A_ISO_CTRL_RX_CRC_N;
		अवरोध;
	शेष:
		dev_dbg(trf->dev, "Unsupported Framing: %d\n", framing);
		वापस -EINVAL;
	पूर्ण

	trf->framing = framing;

	अगर (iso_ctrl != trf->iso_ctrl) अणु
		ret = trf7970a_ग_लिखो(trf, TRF7970A_ISO_CTRL, iso_ctrl);
		अगर (ret)
			वापस ret;

		trf->iso_ctrl = iso_ctrl;

		ret = trf7970a_ग_लिखो(trf, TRF7970A_MODULATOR_SYS_CLK_CTRL,
				     trf->modulator_sys_clk_ctrl);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!(trf->chip_status_ctrl & TRF7970A_CHIP_STATUS_RF_ON)) अणु
		ret = trf7970a_ग_लिखो(trf, TRF7970A_CHIP_STATUS_CTRL,
				     trf->chip_status_ctrl |
				     TRF7970A_CHIP_STATUS_RF_ON);
		अगर (ret)
			वापस ret;

		trf->chip_status_ctrl |= TRF7970A_CHIP_STATUS_RF_ON;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक trf7970a_tg_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type,
				    पूर्णांक param)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);
	पूर्णांक ret;

	dev_dbg(trf->dev, "Configure hw - type: %d, param: %d\n", type, param);

	mutex_lock(&trf->lock);

	trf->is_initiator = false;

	अगर ((trf->state == TRF7970A_ST_PWR_OFF) ||
	    (trf->state == TRF7970A_ST_RF_OFF)) अणु
		ret = trf7970a_चयन_rf_on(trf);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण

	चयन (type) अणु
	हाल NFC_DIGITAL_CONFIG_RF_TECH:
		ret = trf7970a_tg_config_rf_tech(trf, param);
		अवरोध;
	हाल NFC_DIGITAL_CONFIG_FRAMING:
		ret = trf7970a_tg_config_framing(trf, param);
		अवरोध;
	शेष:
		dev_dbg(trf->dev, "Unknown type: %d\n", type);
		ret = -EINVAL;
	पूर्ण

err_unlock:
	mutex_unlock(&trf->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक _trf7970a_tg_listen(काष्ठा nfc_digital_dev *ddev, u16 समयout,
			       nfc_digital_cmd_complete_t cb, व्योम *arg,
			       bool mode_detect)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);
	पूर्णांक ret;

	mutex_lock(&trf->lock);

	अगर ((trf->state != TRF7970A_ST_IDLE) &&
	    (trf->state != TRF7970A_ST_IDLE_RX_BLOCKED)) अणु
		dev_err(trf->dev, "%s - Bogus state: %d\n", __func__,
			trf->state);
		ret = -EIO;
		जाओ out_err;
	पूर्ण

	अगर (trf->पातing) अणु
		dev_dbg(trf->dev, "Abort process complete\n");
		trf->पातing = false;
		ret = -ECANCELED;
		जाओ out_err;
	पूर्ण

	trf->rx_skb = nfc_alloc_recv_skb(TRF7970A_RX_SKB_ALLOC_SIZE,
					 GFP_KERNEL);
	अगर (!trf->rx_skb) अणु
		dev_dbg(trf->dev, "Can't alloc rx_skb\n");
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	ret = trf7970a_ग_लिखो(trf, TRF7970A_RX_SPECIAL_SETTINGS,
			     TRF7970A_RX_SPECIAL_SETTINGS_HBT |
			     TRF7970A_RX_SPECIAL_SETTINGS_M848 |
			     TRF7970A_RX_SPECIAL_SETTINGS_C424 |
			     TRF7970A_RX_SPECIAL_SETTINGS_C212);
	अगर (ret)
		जाओ out_err;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_REG_IO_CTRL,
			     trf->io_ctrl | TRF7970A_REG_IO_CTRL_VRS(0x1));
	अगर (ret)
		जाओ out_err;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_NFC_LOW_FIELD_LEVEL,
			     TRF7970A_NFC_LOW_FIELD_LEVEL_RFDET(0x3));
	अगर (ret)
		जाओ out_err;

	ret = trf7970a_ग_लिखो(trf, TRF7970A_NFC_TARGET_LEVEL,
			     TRF7970A_NFC_TARGET_LEVEL_RFDET(0x7));
	अगर (ret)
		जाओ out_err;

	trf->ddev = ddev;
	trf->cb = cb;
	trf->cb_arg = arg;
	trf->समयout = समयout;
	trf->ignore_समयout = false;

	ret = trf7970a_cmd(trf, TRF7970A_CMD_ENABLE_RX);
	अगर (ret)
		जाओ out_err;

	trf->state = mode_detect ? TRF7970A_ST_LISTENING_MD :
				   TRF7970A_ST_LISTENING;

	schedule_delayed_work(&trf->समयout_work, msecs_to_jअगरfies(समयout));

out_err:
	mutex_unlock(&trf->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_tg_listen(काष्ठा nfc_digital_dev *ddev, u16 समयout,
			      nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);

	dev_dbg(trf->dev, "Listen - state: %d, timeout: %d ms\n",
		trf->state, समयout);

	वापस _trf7970a_tg_listen(ddev, समयout, cb, arg, false);
पूर्ण

अटल पूर्णांक trf7970a_tg_listen_md(काष्ठा nfc_digital_dev *ddev,
				 u16 समयout, nfc_digital_cmd_complete_t cb,
				 व्योम *arg)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);
	पूर्णांक ret;

	dev_dbg(trf->dev, "Listen MD - state: %d, timeout: %d ms\n",
		trf->state, समयout);

	ret = trf7970a_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				       NFC_DIGITAL_RF_TECH_106A);
	अगर (ret)
		वापस ret;

	ret = trf7970a_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				       NFC_DIGITAL_FRAMING_NFCA_NFC_DEP);
	अगर (ret)
		वापस ret;

	वापस _trf7970a_tg_listen(ddev, समयout, cb, arg, true);
पूर्ण

अटल पूर्णांक trf7970a_tg_get_rf_tech(काष्ठा nfc_digital_dev *ddev, u8 *rf_tech)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);

	dev_dbg(trf->dev, "Get RF Tech - state: %d, rf_tech: %d\n",
		trf->state, trf->md_rf_tech);

	*rf_tech = trf->md_rf_tech;

	वापस 0;
पूर्ण

अटल व्योम trf7970a_पात_cmd(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा trf7970a *trf = nfc_digital_get_drvdata(ddev);

	dev_dbg(trf->dev, "Abort process initiated\n");

	mutex_lock(&trf->lock);

	चयन (trf->state) अणु
	हाल TRF7970A_ST_WAIT_FOR_TX_FIFO:
	हाल TRF7970A_ST_WAIT_FOR_RX_DATA:
	हाल TRF7970A_ST_WAIT_FOR_RX_DATA_CONT:
	हाल TRF7970A_ST_WAIT_TO_ISSUE_खातापूर्ण:
		trf->पातing = true;
		अवरोध;
	हाल TRF7970A_ST_LISTENING:
		trf->ignore_समयout = !cancel_delayed_work(&trf->समयout_work);
		trf7970a_send_err_upstream(trf, -ECANCELED);
		dev_dbg(trf->dev, "Abort process complete\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&trf->lock);
पूर्ण

अटल काष्ठा nfc_digital_ops trf7970a_nfc_ops = अणु
	.in_configure_hw	= trf7970a_in_configure_hw,
	.in_send_cmd		= trf7970a_send_cmd,
	.tg_configure_hw	= trf7970a_tg_configure_hw,
	.tg_send_cmd		= trf7970a_send_cmd,
	.tg_listen		= trf7970a_tg_listen,
	.tg_listen_md		= trf7970a_tg_listen_md,
	.tg_get_rf_tech		= trf7970a_tg_get_rf_tech,
	.चयन_rf		= trf7970a_चयन_rf,
	.पात_cmd		= trf7970a_पात_cmd,
पूर्ण;

अटल पूर्णांक trf7970a_घातer_up(काष्ठा trf7970a *trf)
अणु
	पूर्णांक ret;

	dev_dbg(trf->dev, "Powering up - state: %d\n", trf->state);

	अगर (trf->state != TRF7970A_ST_PWR_OFF)
		वापस 0;

	ret = regulator_enable(trf->regulator);
	अगर (ret) अणु
		dev_err(trf->dev, "%s - Can't enable VIN: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	usleep_range(5000, 6000);

	अगर (trf->en2_gpiod &&
	    !(trf->quirks & TRF7970A_QUIRK_EN2_MUST_STAY_LOW)) अणु
		gpiod_set_value_cansleep(trf->en2_gpiod, 1);
		usleep_range(1000, 2000);
	पूर्ण

	gpiod_set_value_cansleep(trf->en_gpiod, 1);

	usleep_range(20000, 21000);

	trf->state = TRF7970A_ST_RF_OFF;

	वापस 0;
पूर्ण

अटल पूर्णांक trf7970a_घातer_करोwn(काष्ठा trf7970a *trf)
अणु
	पूर्णांक ret;

	dev_dbg(trf->dev, "Powering down - state: %d\n", trf->state);

	अगर (trf->state == TRF7970A_ST_PWR_OFF)
		वापस 0;

	अगर (trf->state != TRF7970A_ST_RF_OFF) अणु
		dev_dbg(trf->dev, "Can't power down - not RF_OFF state (%d)\n",
			trf->state);
		वापस -EBUSY;
	पूर्ण

	gpiod_set_value_cansleep(trf->en_gpiod, 0);

	अगर (trf->en2_gpiod && !(trf->quirks & TRF7970A_QUIRK_EN2_MUST_STAY_LOW))
		gpiod_set_value_cansleep(trf->en2_gpiod, 0);

	ret = regulator_disable(trf->regulator);
	अगर (ret)
		dev_err(trf->dev, "%s - Can't disable VIN: %d\n", __func__,
			ret);

	trf->state = TRF7970A_ST_PWR_OFF;

	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_startup(काष्ठा trf7970a *trf)
अणु
	पूर्णांक ret;

	ret = trf7970a_घातer_up(trf);
	अगर (ret)
		वापस ret;

	pm_runसमय_set_active(trf->dev);
	pm_runसमय_enable(trf->dev);
	pm_runसमय_mark_last_busy(trf->dev);

	वापस 0;
पूर्ण

अटल व्योम trf7970a_shutकरोwn(काष्ठा trf7970a *trf)
अणु
	चयन (trf->state) अणु
	हाल TRF7970A_ST_WAIT_FOR_TX_FIFO:
	हाल TRF7970A_ST_WAIT_FOR_RX_DATA:
	हाल TRF7970A_ST_WAIT_FOR_RX_DATA_CONT:
	हाल TRF7970A_ST_WAIT_TO_ISSUE_खातापूर्ण:
	हाल TRF7970A_ST_LISTENING:
		trf7970a_send_err_upstream(trf, -ECANCELED);
		fallthrough;
	हाल TRF7970A_ST_IDLE:
	हाल TRF7970A_ST_IDLE_RX_BLOCKED:
		trf7970a_चयन_rf_off(trf);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	pm_runसमय_disable(trf->dev);
	pm_runसमय_set_suspended(trf->dev);

	trf7970a_घातer_करोwn(trf);
पूर्ण

अटल पूर्णांक trf7970a_get_स्वतःsuspend_delay(काष्ठा device_node *np)
अणु
	पूर्णांक स्वतःsuspend_delay, ret;

	ret = of_property_पढ़ो_u32(np, "autosuspend-delay", &स्वतःsuspend_delay);
	अगर (ret)
		स्वतःsuspend_delay = TRF7970A_AUTOSUSPEND_DELAY;

	वापस स्वतःsuspend_delay;
पूर्ण

अटल पूर्णांक trf7970a_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device_node *np = spi->dev.of_node;
	काष्ठा trf7970a *trf;
	पूर्णांक uvolts, स्वतःsuspend_delay, ret;
	u32 clk_freq = TRF7970A_13MHZ_CLOCK_FREQUENCY;

	अगर (!np) अणु
		dev_err(&spi->dev, "No Device Tree entry\n");
		वापस -EINVAL;
	पूर्ण

	trf = devm_kzalloc(&spi->dev, माप(*trf), GFP_KERNEL);
	अगर (!trf)
		वापस -ENOMEM;

	trf->state = TRF7970A_ST_PWR_OFF;
	trf->dev = &spi->dev;
	trf->spi = spi;

	spi->mode = SPI_MODE_1;
	spi->bits_per_word = 8;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(trf->dev, "Can't set up SPI Communication\n");
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "irq-status-read-quirk"))
		trf->quirks |= TRF7970A_QUIRK_IRQ_STATUS_READ;

	/* There are two enable pins - only EN must be present in the DT */
	trf->en_gpiod = devm_gpiod_get_index(trf->dev, "ti,enable", 0,
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(trf->en_gpiod)) अणु
		dev_err(trf->dev, "No EN GPIO property\n");
		वापस PTR_ERR(trf->en_gpiod);
	पूर्ण

	trf->en2_gpiod = devm_gpiod_get_index_optional(trf->dev, "ti,enable", 1,
						       GPIOD_OUT_LOW);
	अगर (!trf->en2_gpiod) अणु
		dev_info(trf->dev, "No EN2 GPIO property\n");
	पूर्ण अन्यथा अगर (IS_ERR(trf->en2_gpiod)) अणु
		dev_err(trf->dev, "Error getting EN2 GPIO property: %ld\n",
			PTR_ERR(trf->en2_gpiod));
		वापस PTR_ERR(trf->en2_gpiod);
	पूर्ण अन्यथा अगर (of_property_पढ़ो_bool(np, "en2-rf-quirk")) अणु
		trf->quirks |= TRF7970A_QUIRK_EN2_MUST_STAY_LOW;
	पूर्ण

	of_property_पढ़ो_u32(np, "clock-frequency", &clk_freq);
	अगर ((clk_freq != TRF7970A_27MHZ_CLOCK_FREQUENCY) &&
	    (clk_freq != TRF7970A_13MHZ_CLOCK_FREQUENCY)) अणु
		dev_err(trf->dev,
			"clock-frequency (%u Hz) unsupported\n", clk_freq);
		वापस -EINVAL;
	पूर्ण

	अगर (clk_freq == TRF7970A_27MHZ_CLOCK_FREQUENCY) अणु
		trf->modulator_sys_clk_ctrl = TRF7970A_MODULATOR_27MHZ;
		dev_dbg(trf->dev, "trf7970a configured for 27MHz crystal\n");
	पूर्ण अन्यथा अणु
		trf->modulator_sys_clk_ctrl = 0;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(trf->dev, spi->irq, शून्य,
					trf7970a_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"trf7970a", trf);
	अगर (ret) अणु
		dev_err(trf->dev, "Can't request IRQ#%d: %d\n", spi->irq, ret);
		वापस ret;
	पूर्ण

	mutex_init(&trf->lock);
	INIT_DELAYED_WORK(&trf->समयout_work, trf7970a_समयout_work_handler);

	trf->regulator = devm_regulator_get(&spi->dev, "vin");
	अगर (IS_ERR(trf->regulator)) अणु
		ret = PTR_ERR(trf->regulator);
		dev_err(trf->dev, "Can't get VIN regulator: %d\n", ret);
		जाओ err_destroy_lock;
	पूर्ण

	ret = regulator_enable(trf->regulator);
	अगर (ret) अणु
		dev_err(trf->dev, "Can't enable VIN: %d\n", ret);
		जाओ err_destroy_lock;
	पूर्ण

	uvolts = regulator_get_voltage(trf->regulator);
	अगर (uvolts > 4000000)
		trf->chip_status_ctrl = TRF7970A_CHIP_STATUS_VRS5_3;

	trf->regulator = devm_regulator_get(&spi->dev, "vdd-io");
	अगर (IS_ERR(trf->regulator)) अणु
		ret = PTR_ERR(trf->regulator);
		dev_err(trf->dev, "Can't get VDD_IO regulator: %d\n", ret);
		जाओ err_destroy_lock;
	पूर्ण

	ret = regulator_enable(trf->regulator);
	अगर (ret) अणु
		dev_err(trf->dev, "Can't enable VDD_IO: %d\n", ret);
		जाओ err_destroy_lock;
	पूर्ण

	अगर (regulator_get_voltage(trf->regulator) == 1800000) अणु
		trf->io_ctrl = TRF7970A_REG_IO_CTRL_IO_LOW;
		dev_dbg(trf->dev, "trf7970a config vdd_io to 1.8V\n");
	पूर्ण

	trf->ddev = nfc_digital_allocate_device(&trf7970a_nfc_ops,
						TRF7970A_SUPPORTED_PROTOCOLS,
						NFC_DIGITAL_DRV_CAPS_IN_CRC |
						NFC_DIGITAL_DRV_CAPS_TG_CRC, 0,
						0);
	अगर (!trf->ddev) अणु
		dev_err(trf->dev, "Can't allocate NFC digital device\n");
		ret = -ENOMEM;
		जाओ err_disable_regulator;
	पूर्ण

	nfc_digital_set_parent_dev(trf->ddev, trf->dev);
	nfc_digital_set_drvdata(trf->ddev, trf);
	spi_set_drvdata(spi, trf);

	स्वतःsuspend_delay = trf7970a_get_स्वतःsuspend_delay(np);

	pm_runसमय_set_स्वतःsuspend_delay(trf->dev, स्वतःsuspend_delay);
	pm_runसमय_use_स्वतःsuspend(trf->dev);

	ret = trf7970a_startup(trf);
	अगर (ret)
		जाओ err_मुक्त_ddev;

	ret = nfc_digital_रेजिस्टर_device(trf->ddev);
	अगर (ret) अणु
		dev_err(trf->dev, "Can't register NFC digital device: %d\n",
			ret);
		जाओ err_shutकरोwn;
	पूर्ण

	वापस 0;

err_shutकरोwn:
	trf7970a_shutकरोwn(trf);
err_मुक्त_ddev:
	nfc_digital_मुक्त_device(trf->ddev);
err_disable_regulator:
	regulator_disable(trf->regulator);
err_destroy_lock:
	mutex_destroy(&trf->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा trf7970a *trf = spi_get_drvdata(spi);

	mutex_lock(&trf->lock);

	trf7970a_shutकरोwn(trf);

	mutex_unlock(&trf->lock);

	nfc_digital_unरेजिस्टर_device(trf->ddev);
	nfc_digital_मुक्त_device(trf->ddev);

	regulator_disable(trf->regulator);

	mutex_destroy(&trf->lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक trf7970a_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा trf7970a *trf = spi_get_drvdata(spi);

	dev_dbg(dev, "Suspend\n");

	mutex_lock(&trf->lock);

	trf7970a_shutकरोwn(trf);

	mutex_unlock(&trf->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक trf7970a_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा trf7970a *trf = spi_get_drvdata(spi);
	पूर्णांक ret;

	dev_dbg(dev, "Resume\n");

	mutex_lock(&trf->lock);

	ret = trf7970a_startup(trf);

	mutex_unlock(&trf->lock);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक trf7970a_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा trf7970a *trf = spi_get_drvdata(spi);
	पूर्णांक ret;

	dev_dbg(dev, "Runtime suspend\n");

	mutex_lock(&trf->lock);

	ret = trf7970a_घातer_करोwn(trf);

	mutex_unlock(&trf->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक trf7970a_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा trf7970a *trf = spi_get_drvdata(spi);
	पूर्णांक ret;

	dev_dbg(dev, "Runtime resume\n");

	ret = trf7970a_घातer_up(trf);
	अगर (!ret)
		pm_runसमय_mark_last_busy(dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops trf7970a_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(trf7970a_suspend, trf7970a_resume)
	SET_RUNTIME_PM_OPS(trf7970a_pm_runसमय_suspend,
			   trf7970a_pm_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id trf7970a_of_match[] = अणु
	अणु.compatible = "ti,trf7970a",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, trf7970a_of_match);

अटल स्थिर काष्ठा spi_device_id trf7970a_id_table[] = अणु
	अणु"trf7970a", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, trf7970a_id_table);

अटल काष्ठा spi_driver trf7970a_spi_driver = अणु
	.probe		= trf7970a_probe,
	.हटाओ		= trf7970a_हटाओ,
	.id_table	= trf7970a_id_table,
	.driver	= अणु
		.name		= "trf7970a",
		.of_match_table	= of_match_ptr(trf7970a_of_match),
		.pm		= &trf7970a_pm_ops,
	पूर्ण,
पूर्ण;

module_spi_driver(trf7970a_spi_driver);

MODULE_AUTHOR("Mark A. Greer <mgreer@animalcreek.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI trf7970a RFID/NFC Transceiver Driver");
