<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * रेजिस्टर description क्रम HopeRf rf69 radio module
 *
 * Copyright (C) 2016 Wolf-Entwicklungen
 *	Marcus Wolf <linux@wolf-entwicklungen.de>
 */

/*******************************************/
/* RF69 रेजिस्टर addresses		   */
/*******************************************/
#घोषणा  REG_FIFO			0x00
#घोषणा  REG_OPMODE			0x01
#घोषणा  REG_DATAMODUL			0x02
#घोषणा  REG_BITRATE_MSB		0x03
#घोषणा  REG_BITRATE_LSB		0x04
#घोषणा  REG_FDEV_MSB			0x05
#घोषणा  REG_FDEV_LSB			0x06
#घोषणा  REG_FRF_MSB			0x07
#घोषणा  REG_FRF_MID			0x08
#घोषणा  REG_FRF_LSB			0x09
#घोषणा  REG_OSC1			0x0A
#घोषणा  REG_AFCCTRL			0x0B
#घोषणा  REG_LOWBAT			0x0C
#घोषणा  REG_LISTEN1			0x0D
#घोषणा  REG_LISTEN2			0x0E
#घोषणा  REG_LISTEN3			0x0F
#घोषणा  REG_VERSION			0x10
#घोषणा  REG_PALEVEL			0x11
#घोषणा  REG_PARAMP			0x12
#घोषणा  REG_OCP			0x13
#घोषणा  REG_AGCREF			0x14 /* not available on RF69 */
#घोषणा  REG_AGCTHRESH1			0x15 /* not available on RF69 */
#घोषणा  REG_AGCTHRESH2			0x16 /* not available on RF69 */
#घोषणा  REG_AGCTHRESH3			0x17 /* not available on RF69 */
#घोषणा  REG_LNA			0x18
#घोषणा  REG_RXBW			0x19
#घोषणा  REG_AFCBW			0x1A
#घोषणा  REG_OOKPEAK			0x1B
#घोषणा  REG_OOKAVG			0x1C
#घोषणा  REG_OOKFIX			0x1D
#घोषणा  REG_AFCFEI			0x1E
#घोषणा  REG_AFCMSB			0x1F
#घोषणा  REG_AFCLSB			0x20
#घोषणा  REG_FEIMSB			0x21
#घोषणा  REG_FEILSB			0x22
#घोषणा  REG_RSSICONFIG			0x23
#घोषणा  REG_RSSIVALUE			0x24
#घोषणा  REG_DIOMAPPING1		0x25
#घोषणा  REG_DIOMAPPING2		0x26
#घोषणा  REG_IRQFLAGS1			0x27
#घोषणा  REG_IRQFLAGS2			0x28
#घोषणा  REG_RSSITHRESH			0x29
#घोषणा  REG_RXTIMEOUT1			0x2A
#घोषणा  REG_RXTIMEOUT2			0x2B
#घोषणा  REG_PREAMBLE_MSB		0x2C
#घोषणा  REG_PREAMBLE_LSB		0x2D
#घोषणा  REG_SYNC_CONFIG		0x2E
#घोषणा  REG_SYNCVALUE1			0x2F
#घोषणा  REG_SYNCVALUE2			0x30
#घोषणा  REG_SYNCVALUE3			0x31
#घोषणा  REG_SYNCVALUE4			0x32
#घोषणा  REG_SYNCVALUE5			0x33
#घोषणा  REG_SYNCVALUE6			0x34
#घोषणा  REG_SYNCVALUE7			0x35
#घोषणा  REG_SYNCVALUE8			0x36
#घोषणा  REG_PACKETCONFIG1		0x37
#घोषणा  REG_PAYLOAD_LENGTH		0x38
#घोषणा  REG_NODEADRS			0x39
#घोषणा  REG_BROADCASTADRS		0x3A
#घोषणा  REG_AUTOMODES			0x3B
#घोषणा  REG_FIFO_THRESH		0x3C
#घोषणा  REG_PACKETCONFIG2		0x3D
#घोषणा  REG_AESKEY1			0x3E
#घोषणा  REG_AESKEY2			0x3F
#घोषणा  REG_AESKEY3			0x40
#घोषणा  REG_AESKEY4			0x41
#घोषणा  REG_AESKEY5			0x42
#घोषणा  REG_AESKEY6			0x43
#घोषणा  REG_AESKEY7			0x44
#घोषणा  REG_AESKEY8			0x45
#घोषणा  REG_AESKEY9			0x46
#घोषणा  REG_AESKEY10			0x47
#घोषणा  REG_AESKEY11			0x48
#घोषणा  REG_AESKEY12			0x49
#घोषणा  REG_AESKEY13			0x4A
#घोषणा  REG_AESKEY14			0x4B
#घोषणा  REG_AESKEY15			0x4C
#घोषणा  REG_AESKEY16			0x4D
#घोषणा  REG_TEMP1			0x4E
#घोषणा  REG_TEMP2			0x4F
#घोषणा  REG_TESTPA1			0x5A /* only present on RFM69HW */
#घोषणा  REG_TESTPA2			0x5C /* only present on RFM69HW */
#घोषणा  REG_TESTDAGC			0x6F

/******************************************************/
/* RF69/SX1231 bit definition				*/
/******************************************************/
/* ग_लिखो bit */
#घोषणा WRITE_BIT				0x80

/* RegOpMode */
#घोषणा  MASK_OPMODE_SEQUENCER_OFF		0x80
#घोषणा  MASK_OPMODE_LISTEN_ON			0x40
#घोषणा  MASK_OPMODE_LISTEN_ABORT		0x20
#घोषणा  MASK_OPMODE_MODE			0x1C

#घोषणा  OPMODE_MODE_SLEEP			0x00
#घोषणा  OPMODE_MODE_STANDBY			0x04 /* शेष */
#घोषणा  OPMODE_MODE_SYNTHESIZER		0x08
#घोषणा  OPMODE_MODE_TRANSMIT			0x0C
#घोषणा  OPMODE_MODE_RECEIVE			0x10

/* RegDataModul */
#घोषणा  MASK_DATAMODUL_MODE			0x06
#घोषणा  MASK_DATAMODUL_MODULATION_TYPE		0x18
#घोषणा  MASK_DATAMODUL_MODULATION_SHAPE	0x03

#घोषणा  DATAMODUL_MODE_PACKET			0x00 /* शेष */
#घोषणा  DATAMODUL_MODE_CONTINUOUS		0x40
#घोषणा  DATAMODUL_MODE_CONTINUOUS_NOSYNC	0x60

#घोषणा  DATAMODUL_MODULATION_TYPE_FSK		0x00 /* शेष */
#घोषणा  DATAMODUL_MODULATION_TYPE_OOK		0x08

#घोषणा  DATAMODUL_MODULATION_SHAPE_NONE	0x00 /* शेष */
#घोषणा  DATAMODUL_MODULATION_SHAPE_1_0		0x01
#घोषणा  DATAMODUL_MODULATION_SHAPE_0_5		0x02
#घोषणा  DATAMODUL_MODULATION_SHAPE_0_3		0x03
#घोषणा  DATAMODUL_MODULATION_SHAPE_BR		0x01
#घोषणा  DATAMODUL_MODULATION_SHAPE_2BR		0x02

/* RegFDevMsb (0x05)*/
#घोषणा FDEVMASB_MASK				0x3f

/*
 * // RegOsc1
 * #घोषणा  OSC1_RCCAL_START			0x80
 * #घोषणा  OSC1_RCCAL_DONE			0x40
 *
 * // RegLowBat
 * #घोषणा  LOWBAT_MONITOR				0x10
 * #घोषणा  LOWBAT_ON				0x08
 * #घोषणा  LOWBAT_OFF				0x00  // Default
 *
 * #घोषणा  LOWBAT_TRIM_1695			0x00
 * #घोषणा  LOWBAT_TRIM_1764			0x01
 * #घोषणा  LOWBAT_TRIM_1835			0x02  // Default
 * #घोषणा  LOWBAT_TRIM_1905			0x03
 * #घोषणा  LOWBAT_TRIM_1976			0x04
 * #घोषणा  LOWBAT_TRIM_2045			0x05
 * #घोषणा  LOWBAT_TRIM_2116			0x06
 * #घोषणा  LOWBAT_TRIM_2185			0x07
 *
 *
 * // RegListen1
 * #घोषणा  LISTEN1_RESOL_64			0x50
 * #घोषणा  LISTEN1_RESOL_4100			0xA0  // Default
 * #घोषणा  LISTEN1_RESOL_262000			0xF0
 *
 * #घोषणा  LISTEN1_CRITERIA_RSSI			0x00  // Default
 * #घोषणा  LISTEN1_CRITERIA_RSSIANDSYNC		0x08
 *
 * #घोषणा  LISTEN1_END_00				0x00
 * #घोषणा  LISTEN1_END_01				0x02  // Default
 * #घोषणा  LISTEN1_END_10				0x04
 *
 *
 * // RegListen2
 * #घोषणा  LISTEN2_COEFIDLE_VALUE			0xF5 // Default
 *
 * // RegListen3
 * #घोषणा  LISTEN3_COEFRX_VALUE			0x20 // Default
 */

// RegPaLevel
#घोषणा  MASK_PALEVEL_PA0			0x80
#घोषणा  MASK_PALEVEL_PA1			0x40
#घोषणा  MASK_PALEVEL_PA2			0x20
#घोषणा  MASK_PALEVEL_OUTPUT_POWER		0x1F

// RegPaRamp
#घोषणा  PARAMP_3400				0x00
#घोषणा  PARAMP_2000				0x01
#घोषणा  PARAMP_1000				0x02
#घोषणा  PARAMP_500				0x03
#घोषणा  PARAMP_250				0x04
#घोषणा  PARAMP_125				0x05
#घोषणा  PARAMP_100				0x06
#घोषणा  PARAMP_62				0x07
#घोषणा  PARAMP_50				0x08
#घोषणा  PARAMP_40				0x09 /* शेष */
#घोषणा  PARAMP_31				0x0A
#घोषणा  PARAMP_25				0x0B
#घोषणा  PARAMP_20				0x0C
#घोषणा  PARAMP_15				0x0D
#घोषणा  PARAMP_12				0x0E
#घोषणा  PARAMP_10				0x0F

#घोषणा  MASK_PARAMP				0x0F

/*
 * // RegOcp
 * #घोषणा  OCP_OFF				0x0F
 * #घोषणा  OCP_ON					0x1A  // Default
 *
 * #घोषणा  OCP_TRIM_45				0x00
 * #घोषणा  OCP_TRIM_50				0x01
 * #घोषणा  OCP_TRIM_55				0x02
 * #घोषणा  OCP_TRIM_60				0x03
 * #घोषणा  OCP_TRIM_65				0x04
 * #घोषणा  OCP_TRIM_70				0x05
 * #घोषणा  OCP_TRIM_75				0x06
 * #घोषणा  OCP_TRIM_80				0x07
 * #घोषणा  OCP_TRIM_85				0x08
 * #घोषणा  OCP_TRIM_90				0x09
 * #घोषणा  OCP_TRIM_95				0x0A
 * #घोषणा  OCP_TRIM_100				0x0B  // Default
 * #घोषणा  OCP_TRIM_105				0x0C
 * #घोषणा  OCP_TRIM_110				0x0D
 * #घोषणा  OCP_TRIM_115				0x0E
 * #घोषणा  OCP_TRIM_120				0x0F
 */

/* RegLna (0x18) */
#घोषणा  MASK_LNA_ZIN				0x80
#घोषणा  MASK_LNA_CURRENT_GAIN			0x38
#घोषणा  MASK_LNA_GAIN				0x07

#घोषणा  LNA_GAIN_AUTO				0x00 /* शेष */
#घोषणा  LNA_GAIN_MAX				0x01
#घोषणा  LNA_GAIN_MAX_MINUS_6			0x02
#घोषणा  LNA_GAIN_MAX_MINUS_12			0x03
#घोषणा  LNA_GAIN_MAX_MINUS_24			0x04
#घोषणा  LNA_GAIN_MAX_MINUS_36			0x05
#घोषणा  LNA_GAIN_MAX_MINUS_48			0x06

/* RegRxBw (0x19) and RegAfcBw (0x1A) */
#घोषणा  MASK_BW_DCC_FREQ			0xE0
#घोषणा  MASK_BW_MANTISSE			0x18
#घोषणा  MASK_BW_EXPONENT			0x07

#घोषणा  BW_DCC_16_PERCENT			0x00
#घोषणा  BW_DCC_8_PERCENT			0x20
#घोषणा  BW_DCC_4_PERCENT			0x40 /* शेष */
#घोषणा  BW_DCC_2_PERCENT			0x60
#घोषणा  BW_DCC_1_PERCENT			0x80
#घोषणा  BW_DCC_0_5_PERCENT			0xA0
#घोषणा  BW_DCC_0_25_PERCENT			0xC0
#घोषणा  BW_DCC_0_125_PERCENT			0xE0

#घोषणा  BW_MANT_16				0x00
#घोषणा  BW_MANT_20				0x08
#घोषणा  BW_MANT_24				0x10 /* शेष */

/* RegOokPeak (0x1B) */
#घोषणा  MASK_OOKPEAK_THRESTYPE			0xc0
#घोषणा  MASK_OOKPEAK_THRESSTEP			0x38
#घोषणा  MASK_OOKPEAK_THRESDEC			0x07

#घोषणा  OOKPEAK_THRESHTYPE_FIXED		0x00
#घोषणा  OOKPEAK_THRESHTYPE_PEAK		0x40 /* शेष */
#घोषणा  OOKPEAK_THRESHTYPE_AVERAGE		0x80

#घोषणा  OOKPEAK_THRESHSTEP_0_5_DB		0x00 /* शेष */
#घोषणा  OOKPEAK_THRESHSTEP_1_0_DB		0x08
#घोषणा  OOKPEAK_THRESHSTEP_1_5_DB		0x10
#घोषणा  OOKPEAK_THRESHSTEP_2_0_DB		0x18
#घोषणा  OOKPEAK_THRESHSTEP_3_0_DB		0x20
#घोषणा  OOKPEAK_THRESHSTEP_4_0_DB		0x28
#घोषणा  OOKPEAK_THRESHSTEP_5_0_DB		0x30
#घोषणा  OOKPEAK_THRESHSTEP_6_0_DB		0x38

#घोषणा  OOKPEAK_THRESHDEC_ONCE			0x00 /* शेष */
#घोषणा  OOKPEAK_THRESHDEC_EVERY_2ND		0x01
#घोषणा  OOKPEAK_THRESHDEC_EVERY_4TH		0x02
#घोषणा  OOKPEAK_THRESHDEC_EVERY_8TH		0x03
#घोषणा  OOKPEAK_THRESHDEC_TWICE		0x04
#घोषणा  OOKPEAK_THRESHDEC_4_TIMES		0x05
#घोषणा  OOKPEAK_THRESHDEC_8_TIMES		0x06
#घोषणा  OOKPEAK_THRESHDEC_16_TIMES		0x07

/*
 * // RegOokAvg
 * #घोषणा  OOKAVG_AVERAGETHRESHFILT_00		0x00
 * #घोषणा  OOKAVG_AVERAGETHRESHFILT_01		0x40
 * #घोषणा  OOKAVG_AVERAGETHRESHFILT_10		0x80  // Default
 * #घोषणा  OOKAVG_AVERAGETHRESHFILT_11		0xC0
 *
 *
 * // RegAfcFei
 * #घोषणा  AFCFEI_FEI_DONE			0x40
 * #घोषणा  AFCFEI_FEI_START			0x20
 * #घोषणा  AFCFEI_AFC_DONE			0x10
 * #घोषणा  AFCFEI_AFCAUTOCLEAR_ON			0x08
 * #घोषणा  AFCFEI_AFCAUTOCLEAR_OFF		0x00  // Default
 *
 * #घोषणा  AFCFEI_AFCAUTO_ON			0x04
 * #घोषणा  AFCFEI_AFCAUTO_OFF			0x00  // Default
 *
 * #घोषणा  AFCFEI_AFC_CLEAR			0x02
 * #घोषणा  AFCFEI_AFC_START			0x01
 *
 * // RegRssiConfig
 * #घोषणा  RSSI_FASTRX_ON				0x08
 * #घोषणा  RSSI_FASTRX_OFF			0x00  // Default
 * #घोषणा  RSSI_DONE				0x02
 * #घोषणा  RSSI_START				0x01
 */

/* RegDioMapping1 */
#घोषणा  MASK_DIO0				0xC0
#घोषणा  MASK_DIO1				0x30
#घोषणा  MASK_DIO2				0x0C
#घोषणा  MASK_DIO3				0x03
#घोषणा  SHIFT_DIO0				6
#घोषणा  SHIFT_DIO1				4
#घोषणा  SHIFT_DIO2				2
#घोषणा  SHIFT_DIO3				0

/* RegDioMapping2 */
#घोषणा  MASK_DIO4				0xC0
#घोषणा  MASK_DIO5				0x30
#घोषणा  SHIFT_DIO4				6
#घोषणा  SHIFT_DIO5				4

/* DIO numbers */
#घोषणा  DIO0					0
#घोषणा  DIO1					1
#घोषणा  DIO2					2
#घोषणा  DIO3					3
#घोषणा  DIO4					4
#घोषणा  DIO5					5

/* DIO Mapping values (packet mode) */
#घोषणा  DIO_MODE_READY_DIO4			0x00
#घोषणा  DIO_MODE_READY_DIO5			0x03
#घोषणा  DIO_CLK_OUT				0x00
#घोषणा  DIO_DATA				0x01
#घोषणा  DIO_TIMEOUT_DIO1			0x03
#घोषणा  DIO_TIMEOUT_DIO4			0x00
#घोषणा  DIO_RSSI_DIO0				0x03
#घोषणा  DIO_RSSI_DIO3_4			0x01
#घोषणा  DIO_RX_READY				0x02
#घोषणा  DIO_PLL_LOCK				0x03
#घोषणा  DIO_TX_READY				0x01
#घोषणा  DIO_FIFO_FULL_DIO1			0x01
#घोषणा  DIO_FIFO_FULL_DIO3			0x00
#घोषणा  DIO_SYNC_ADDRESS			0x02
#घोषणा  DIO_FIFO_NOT_EMPTY_DIO1		0x02
#घोषणा  DIO_FIFO_NOT_EMPTY_FIO2		0x00
#घोषणा  DIO_AUTOMODE				0x04
#घोषणा  DIO_FIFO_LEVEL				0x00
#घोषणा  DIO_CRC_OK				0x00
#घोषणा  DIO_PAYLOAD_READY			0x01
#घोषणा  DIO_PACKET_SENT			0x00
#घोषणा  DIO_DCLK				0x00

/* RegDioMapping2 CLK_OUT part */
#घोषणा  MASK_DIOMAPPING2_CLK_OUT		0x07

#घोषणा  DIOMAPPING2_CLK_OUT_NO_DIV		0x00
#घोषणा  DIOMAPPING2_CLK_OUT_DIV_2		0x01
#घोषणा  DIOMAPPING2_CLK_OUT_DIV_4		0x02
#घोषणा  DIOMAPPING2_CLK_OUT_DIV_8		0x03
#घोषणा  DIOMAPPING2_CLK_OUT_DIV_16		0x04
#घोषणा  DIOMAPPING2_CLK_OUT_DIV_32		0x05
#घोषणा  DIOMAPPING2_CLK_OUT_RC			0x06
#घोषणा  DIOMAPPING2_CLK_OUT_OFF		0x07 /* शेष */

/* RegIrqFlags1 */
#घोषणा  MASK_IRQFLAGS1_MODE_READY		0x80
#घोषणा  MASK_IRQFLAGS1_RX_READY		0x40
#घोषणा  MASK_IRQFLAGS1_TX_READY		0x20
#घोषणा  MASK_IRQFLAGS1_PLL_LOCK		0x10
#घोषणा  MASK_IRQFLAGS1_RSSI			0x08
#घोषणा  MASK_IRQFLAGS1_TIMEOUT			0x04
#घोषणा  MASK_IRQFLAGS1_AUTOMODE		0x02
#घोषणा  MASK_IRQFLAGS1_SYNC_ADDRESS_MATCH	0x01

/* RegIrqFlags2 */
#घोषणा  MASK_IRQFLAGS2_FIFO_FULL		0x80
#घोषणा  MASK_IRQFLAGS2_FIFO_NOT_EMPTY		0x40
#घोषणा  MASK_IRQFLAGS2_FIFO_LEVEL		0x20
#घोषणा  MASK_IRQFLAGS2_FIFO_OVERRUN		0x10
#घोषणा  MASK_IRQFLAGS2_PACKET_SENT		0x08
#घोषणा  MASK_IRQFLAGS2_PAYLOAD_READY		0x04
#घोषणा  MASK_IRQFLAGS2_CRC_OK			0x02
#घोषणा  MASK_IRQFLAGS2_LOW_BAT			0x01

/* RegSyncConfig */
#घोषणा  MASK_SYNC_CONFIG_SYNC_ON		0x80 /* शेष */
#घोषणा  MASK_SYNC_CONFIG_FIFO_FILL_CONDITION	0x40
#घोषणा  MASK_SYNC_CONFIG_SYNC_SIZE		0x38
#घोषणा  MASK_SYNC_CONFIG_SYNC_TOLERANCE	0x07

/* RegPacketConfig1 */
#घोषणा  MASK_PACKETCONFIG1_PACKET_FORMAT_VARIABLE	0x80
#घोषणा  MASK_PACKETCONFIG1_DCFREE			0x60
#घोषणा  MASK_PACKETCONFIG1_CRC_ON			0x10 /* शेष */
#घोषणा  MASK_PACKETCONFIG1_CRCAUTOCLEAR_OFF		0x08
#घोषणा  MASK_PACKETCONFIG1_ADDRESSFILTERING		0x06

#घोषणा  PACKETCONFIG1_DCFREE_OFF			0x00 /* शेष */
#घोषणा  PACKETCONFIG1_DCFREE_MANCHESTER		0x20
#घोषणा  PACKETCONFIG1_DCFREE_WHITENING			0x40
#घोषणा  PACKETCONFIG1_ADDRESSFILTERING_OFF		0x00 /* शेष */
#घोषणा  PACKETCONFIG1_ADDRESSFILTERING_NODE		0x02
#घोषणा  PACKETCONFIG1_ADDRESSFILTERING_NODEBROADCAST	0x04

/*
 * // RegAutoModes
 * #घोषणा  AUTOMODES_ENTER_OFF			0x00  // Default
 * #घोषणा  AUTOMODES_ENTER_FIFONOTEMPTY		0x20
 * #घोषणा  AUTOMODES_ENTER_FIFOLEVEL		0x40
 * #घोषणा  AUTOMODES_ENTER_CRCOK			0x60
 * #घोषणा  AUTOMODES_ENTER_PAYLOADREADY		0x80
 * #घोषणा  AUTOMODES_ENTER_SYNCADRSMATCH		0xA0
 * #घोषणा  AUTOMODES_ENTER_PACKETSENT		0xC0
 * #घोषणा  AUTOMODES_ENTER_FIFOEMPTY		0xE0
 *
 * #घोषणा  AUTOMODES_EXIT_OFF			0x00  // Default
 * #घोषणा  AUTOMODES_EXIT_FIFOEMPTY		0x04
 * #घोषणा  AUTOMODES_EXIT_FIFOLEVEL		0x08
 * #घोषणा  AUTOMODES_EXIT_CRCOK			0x0C
 * #घोषणा  AUTOMODES_EXIT_PAYLOADREADY		0x10
 * #घोषणा  AUTOMODES_EXIT_SYNCADRSMATCH		0x14
 * #घोषणा  AUTOMODES_EXIT_PACKETSENT		0x18
 * #घोषणा  AUTOMODES_EXIT_RXTIMEOUT		0x1C
 *
 * #घोषणा  AUTOMODES_INTERMEDIATE_SLEEP		0x00  // Default
 * #घोषणा  AUTOMODES_INTERMEDIATE_STANDBY		0x01
 * #घोषणा  AUTOMODES_INTERMEDIATE_RECEIVER	0x02
 * #घोषणा  AUTOMODES_INTERMEDIATE_TRANSMITTER	0x03
 *
 */
/* RegFअगरoThresh (0x3c) */
#घोषणा  MASK_FIFO_THRESH_TXSTART		0x80
#घोषणा  MASK_FIFO_THRESH_VALUE			0x7F

/*
 *
 * // RegPacketConfig2
 * #घोषणा  PACKET2_RXRESTARTDELAY_1BIT		0x00  // Default
 * #घोषणा  PACKET2_RXRESTARTDELAY_2BITS		0x10
 * #घोषणा  PACKET2_RXRESTARTDELAY_4BITS		0x20
 * #घोषणा  PACKET2_RXRESTARTDELAY_8BITS		0x30
 * #घोषणा  PACKET2_RXRESTARTDELAY_16BITS		0x40
 * #घोषणा  PACKET2_RXRESTARTDELAY_32BITS		0x50
 * #घोषणा  PACKET2_RXRESTARTDELAY_64BITS		0x60
 * #घोषणा  PACKET2_RXRESTARTDELAY_128BITS		0x70
 * #घोषणा  PACKET2_RXRESTARTDELAY_256BITS		0x80
 * #घोषणा  PACKET2_RXRESTARTDELAY_512BITS		0x90
 * #घोषणा  PACKET2_RXRESTARTDELAY_1024BITS	0xA0
 * #घोषणा  PACKET2_RXRESTARTDELAY_2048BITS	0xB0
 * #घोषणा  PACKET2_RXRESTARTDELAY_NONE		0xC0
 * #घोषणा  PACKET2_RXRESTART			0x04
 *
 * #घोषणा  PACKET2_AUTORXRESTART_ON		0x02  // Default
 * #घोषणा  PACKET2_AUTORXRESTART_OFF		0x00
 *
 * #घोषणा  PACKET2_AES_ON				0x01
 * #घोषणा  PACKET2_AES_OFF			0x00  // Default
 *
 *
 * // RegTemp1
 * #घोषणा  TEMP1_MEAS_START			0x08
 * #घोषणा  TEMP1_MEAS_RUNNING			0x04
 * #घोषणा  TEMP1_ADCLOWPOWER_ON			0x01  // Default
 * #घोषणा  TEMP1_ADCLOWPOWER_OFF			0x00
 */

// RegTestDagc (0x6F)
#घोषणा  DAGC_NORMAL				0x00 /* Reset value */
#घोषणा  DAGC_IMPROVED_LOWBETA1			0x20
#घोषणा  DAGC_IMPROVED_LOWBETA0			0x30 /* Recommended val */
