<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम RTL818x hardware
 *
 * Copyright 2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on the r8187 driver, which is:
 * Copyright 2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 */

#अगर_अघोषित RTL818X_H
#घोषणा RTL818X_H

काष्ठा rtl818x_csr अणु

	u8	MAC[6];
	u8	reserved_0[2];

	जोड़ अणु
		__le32	MAR[2];  /* 0x8 */

		काष्ठाअणु /* rtl8187se */
			u8 rf_sw_config; /* 0x8 */
			u8 reserved_01[3];
			__le32 TMGDA; /* 0xc */
		पूर्ण __packed;
	पूर्ण __packed;

	जोड़ अणु /*  0x10  */
		काष्ठा अणु
			u8	RX_FIFO_COUNT;
			u8	reserved_1;
			u8	TX_FIFO_COUNT;
			u8	BQREQ;
		पूर्ण __packed;

		__le32 TBKDA; /* क्रम 8187se */
	पूर्ण __packed;

	__le32 TBEDA; /* 0x14 - क्रम rtl8187se */

	__le32	TSFT[2];

	जोड़ अणु /* 0x20 */
		__le32	TLPDA;
		__le32  TVIDA; /* क्रम 8187se */
	पूर्ण __packed;

	जोड़ अणु /* 0x24 */
		__le32	TNPDA;
		__le32  TVODA; /* क्रम 8187se */
	पूर्ण __packed;

	/* hi pri ring क्रम all cards */
	__le32	THPDA; /* 0x28 */

	जोड़ अणु /* 0x2c */
		काष्ठा अणु
			u8 reserved_2a;
			u8 EIFS_8187SE;
		पूर्ण __packed;

		__le16	BRSR;
	पूर्ण __packed;

	u8	BSSID[6]; /* 0x2e */

	जोड़ अणु /* 0x34 */
		काष्ठा अणु
			u8 RESP_RATE;
			u8 EIFS;
		पूर्ण __packed;
		__le16 BRSR_8187SE;
	पूर्ण __packed;

	u8	reserved_3[1]; /* 0x36 */
	u8	CMD; /* 0x37 */
#घोषणा RTL818X_CMD_TX_ENABLE		(1 << 2)
#घोषणा RTL818X_CMD_RX_ENABLE		(1 << 3)
#घोषणा RTL818X_CMD_RESET		(1 << 4)
	u8	reserved_4[4]; /* 0x38 */
	जोड़ अणु
		काष्ठा अणु
			__le16	INT_MASK;
			__le16	INT_STATUS;
		पूर्ण __packed;

		__le32	INT_STATUS_SE; /* 0x3c */
	पूर्ण __packed;
/* status bits क्रम rtl8187 and rtl8180/8185 */
#घोषणा RTL818X_INT_RX_OK		(1 <<  0)
#घोषणा RTL818X_INT_RX_ERR		(1 <<  1)
#घोषणा RTL818X_INT_TXL_OK		(1 <<  2)
#घोषणा RTL818X_INT_TXL_ERR		(1 <<  3)
#घोषणा RTL818X_INT_RX_DU		(1 <<  4)
#घोषणा RTL818X_INT_RX_FO		(1 <<  5)
#घोषणा RTL818X_INT_TXN_OK		(1 <<  6)
#घोषणा RTL818X_INT_TXN_ERR		(1 <<  7)
#घोषणा RTL818X_INT_TXH_OK		(1 <<  8)
#घोषणा RTL818X_INT_TXH_ERR		(1 <<  9)
#घोषणा RTL818X_INT_TXB_OK		(1 << 10)
#घोषणा RTL818X_INT_TXB_ERR		(1 << 11)
#घोषणा RTL818X_INT_ATIM		(1 << 12)
#घोषणा RTL818X_INT_BEACON		(1 << 13)
#घोषणा RTL818X_INT_TIME_OUT		(1 << 14)
#घोषणा RTL818X_INT_TX_FO		(1 << 15)
/* status bits क्रम rtl8187se */
#घोषणा RTL818X_INT_SE_TIMER3		(1 <<  0)
#घोषणा RTL818X_INT_SE_TIMER2		(1 <<  1)
#घोषणा RTL818X_INT_SE_RQ0SOR		(1 <<  2)
#घोषणा RTL818X_INT_SE_TXBED_OK		(1 <<  3)
#घोषणा RTL818X_INT_SE_TXBED_ERR	(1 <<  4)
#घोषणा RTL818X_INT_SE_TXBE_OK		(1 <<  5)
#घोषणा RTL818X_INT_SE_TXBE_ERR		(1 <<  6)
#घोषणा RTL818X_INT_SE_RX_OK		(1 <<  7)
#घोषणा RTL818X_INT_SE_RX_ERR		(1 <<  8)
#घोषणा RTL818X_INT_SE_TXL_OK		(1 <<  9)
#घोषणा RTL818X_INT_SE_TXL_ERR		(1 << 10)
#घोषणा RTL818X_INT_SE_RX_DU		(1 << 11)
#घोषणा RTL818X_INT_SE_RX_FIFO		(1 << 12)
#घोषणा RTL818X_INT_SE_TXN_OK		(1 << 13)
#घोषणा RTL818X_INT_SE_TXN_ERR		(1 << 14)
#घोषणा RTL818X_INT_SE_TXH_OK		(1 << 15)
#घोषणा RTL818X_INT_SE_TXH_ERR		(1 << 16)
#घोषणा RTL818X_INT_SE_TXB_OK		(1 << 17)
#घोषणा RTL818X_INT_SE_TXB_ERR		(1 << 18)
#घोषणा RTL818X_INT_SE_ATIM_TO		(1 << 19)
#घोषणा RTL818X_INT_SE_BK_TO		(1 << 20)
#घोषणा RTL818X_INT_SE_TIMER1		(1 << 21)
#घोषणा RTL818X_INT_SE_TX_FIFO		(1 << 22)
#घोषणा RTL818X_INT_SE_WAKEUP		(1 << 23)
#घोषणा RTL818X_INT_SE_BK_DMA		(1 << 24)
#घोषणा RTL818X_INT_SE_TMGD_OK		(1 << 30)
	__le32	TX_CONF; /* 0x40 */
#घोषणा RTL818X_TX_CONF_LOOPBACK_MAC	(1 << 17)
#घोषणा RTL818X_TX_CONF_LOOPBACK_CONT	(3 << 17)
#घोषणा RTL818X_TX_CONF_NO_ICV		(1 << 19)
#घोषणा RTL818X_TX_CONF_DISCW		(1 << 20)
#घोषणा RTL818X_TX_CONF_SAT_HWPLCP	(1 << 24)
#घोषणा RTL818X_TX_CONF_R8180_ABCD	(2 << 25)
#घोषणा RTL818X_TX_CONF_R8180_F		(3 << 25)
#घोषणा RTL818X_TX_CONF_R8185_ABC	(4 << 25)
#घोषणा RTL818X_TX_CONF_R8185_D		(5 << 25)
#घोषणा RTL818X_TX_CONF_R8187vD		(5 << 25)
#घोषणा RTL818X_TX_CONF_R8187vD_B	(6 << 25)
#घोषणा RTL818X_TX_CONF_RTL8187SE	(6 << 25)
#घोषणा RTL818X_TX_CONF_HWVER_MASK	(7 << 25)
#घोषणा RTL818X_TX_CONF_DISREQQSIZE	(1 << 28)
#घोषणा RTL818X_TX_CONF_PROBE_DTS	(1 << 29)
#घोषणा RTL818X_TX_CONF_HW_SEQNUM	(1 << 30)
#घोषणा RTL818X_TX_CONF_CW_MIN		(1 << 31)
	__le32	RX_CONF;
#घोषणा RTL818X_RX_CONF_MONITOR		(1 <<  0)
#घोषणा RTL818X_RX_CONF_NICMAC		(1 <<  1)
#घोषणा RTL818X_RX_CONF_MULTICAST	(1 <<  2)
#घोषणा RTL818X_RX_CONF_BROADCAST	(1 <<  3)
#घोषणा RTL818X_RX_CONF_FCS		(1 <<  5)
#घोषणा RTL818X_RX_CONF_DATA		(1 << 18)
#घोषणा RTL818X_RX_CONF_CTRL		(1 << 19)
#घोषणा RTL818X_RX_CONF_MGMT		(1 << 20)
#घोषणा RTL818X_RX_CONF_ADDR3		(1 << 21)
#घोषणा RTL818X_RX_CONF_PM		(1 << 22)
#घोषणा RTL818X_RX_CONF_BSSID		(1 << 23)
#घोषणा RTL818X_RX_CONF_RX_AUTORESETPHY	(1 << 28)
#घोषणा RTL818X_RX_CONF_CSDM1		(1 << 29)
#घोषणा RTL818X_RX_CONF_CSDM2		(1 << 30)
#घोषणा RTL818X_RX_CONF_ONLYERLPKT	(1 << 31)
	__le32	INT_TIMEOUT;
	__le32	TBDA;
	u8	EEPROM_CMD;
#घोषणा RTL818X_EEPROM_CMD_READ		(1 << 0)
#घोषणा RTL818X_EEPROM_CMD_WRITE	(1 << 1)
#घोषणा RTL818X_EEPROM_CMD_CK		(1 << 2)
#घोषणा RTL818X_EEPROM_CMD_CS		(1 << 3)
#घोषणा RTL818X_EEPROM_CMD_NORMAL	(0 << 6)
#घोषणा RTL818X_EEPROM_CMD_LOAD		(1 << 6)
#घोषणा RTL818X_EEPROM_CMD_PROGRAM	(2 << 6)
#घोषणा RTL818X_EEPROM_CMD_CONFIG	(3 << 6)
	u8	CONFIG0;
	u8	CONFIG1;
	u8	CONFIG2;
#घोषणा RTL818X_CONFIG2_ANTENNA_DIV	(1 << 6)
	__le32	ANAPARAM;
	u8	MSR;
#घोषणा RTL818X_MSR_NO_LINK		(0 << 2)
#घोषणा RTL818X_MSR_ADHOC		(1 << 2)
#घोषणा RTL818X_MSR_INFRA		(2 << 2)
#घोषणा RTL818X_MSR_MASTER		(3 << 2)
#घोषणा RTL818X_MSR_ENEDCA		(4 << 2)
	u8	CONFIG3;
#घोषणा RTL818X_CONFIG3_ANAPARAM_WRITE	(1 << 6)
#घोषणा RTL818X_CONFIG3_GNT_SELECT	(1 << 7)
	u8	CONFIG4;
#घोषणा RTL818X_CONFIG4_POWEROFF	(1 << 6)
#घोषणा RTL818X_CONFIG4_VCOOFF		(1 << 7)
	u8	TESTR;
	u8	reserved_9[2];
	u8	PGSELECT;
	u8	SECURITY;
	__le32	ANAPARAM2;
	u8	reserved_10[8];
	__le32  IMR;		/* 0x6c	- Interrupt mask reg क्रम 8187se */
#घोषणा IMR_TMGDOK      ((1 << 30))
#घोषणा IMR_DOT11HINT	((1 << 25))	/* 802.11h Measurement Interrupt */
#घोषणा IMR_BCNDMAINT	((1 << 24))	/* Beacon DMA Interrupt */
#घोषणा IMR_WAKEINT	((1 << 23))	/* Wake Up Interrupt */
#घोषणा IMR_TXFOVW	((1 << 22))	/* Tx FIFO Overflow */
#घोषणा IMR_TIMEOUT1	((1 << 21))	/* Time Out Interrupt 1 */
#घोषणा IMR_BCNINT	((1 << 20))	/* Beacon Time out */
#घोषणा IMR_ATIMINT	((1 << 19))	/* ATIM Time Out */
#घोषणा IMR_TBDER	((1 << 18))	/* Tx Beacon Descriptor Error */
#घोषणा IMR_TBDOK	((1 << 17))	/* Tx Beacon Descriptor OK */
#घोषणा IMR_THPDER	((1 << 16))	/* Tx High Priority Descriptor Error */
#घोषणा IMR_THPDOK	((1 << 15))	/* Tx High Priority Descriptor OK */
#घोषणा IMR_TVODER	((1 << 14))	/* Tx AC_VO Descriptor Error Int */
#घोषणा IMR_TVODOK	((1 << 13))	/* Tx AC_VO Descriptor OK Interrupt */
#घोषणा IMR_FOVW	((1 << 12))	/* Rx FIFO Overflow Interrupt */
#घोषणा IMR_RDU		((1 << 11))	/* Rx Descriptor Unavailable */
#घोषणा IMR_TVIDER	((1 << 10))	/* Tx AC_VI Descriptor Error */
#घोषणा IMR_TVIDOK	((1 << 9))	/* Tx AC_VI Descriptor OK Interrupt */
#घोषणा IMR_RER		((1 << 8))	/* Rx Error Interrupt */
#घोषणा IMR_ROK		((1 << 7))	/* Receive OK Interrupt */
#घोषणा IMR_TBEDER	((1 << 6))	/* Tx AC_BE Descriptor Error */
#घोषणा IMR_TBEDOK	((1 << 5))	/* Tx AC_BE Descriptor OK */
#घोषणा IMR_TBKDER	((1 << 4))	/* Tx AC_BK Descriptor Error */
#घोषणा IMR_TBKDOK	((1 << 3))	/* Tx AC_BK Descriptor OK */
#घोषणा IMR_RQOSOK	((1 << 2))	/* Rx QoS OK Interrupt */
#घोषणा IMR_TIMEOUT2	((1 << 1))	/* Time Out Interrupt 2 */
#घोषणा IMR_TIMEOUT3	((1 << 0))	/* Time Out Interrupt 3 */
	__le16	BEACON_INTERVAL; /* 0x70 */
	__le16	ATIM_WND; /*  0x72 */
	__le16	BEACON_INTERVAL_TIME; /*  0x74 */
	__le16	ATIMTR_INTERVAL; /*  0x76 */
	u8	PHY_DELAY; /*  0x78 */
	u8	CARRIER_SENSE_COUNTER; /* 0x79 */
	u8	reserved_11[2]; /* 0x7a */
	u8	PHY[4]; /* 0x7c  */
	__le16	RFPinsOutput; /* 0x80 */
	__le16	RFPinsEnable; /* 0x82 */
	__le16	RFPinsSelect; /* 0x84 */
	__le16	RFPinsInput;  /* 0x86 */
	__le32	RF_PARA; /*  0x88 */
	__le32	RF_TIMING; /*  0x8c */
	u8	GP_ENABLE; /*  0x90 */
	u8	GPIO0; /*  0x91 */
	u8	GPIO1; /*  0x92 */
	u8	TPPOLL_STOP; /*  0x93 - rtl8187se only */
#घोषणा RTL818x_TPPOLL_STOP_BQ			(1 << 7)
#घोषणा RTL818x_TPPOLL_STOP_VI			(1 << 4)
#घोषणा RTL818x_TPPOLL_STOP_VO			(1 << 5)
#घोषणा RTL818x_TPPOLL_STOP_BE			(1 << 3)
#घोषणा RTL818x_TPPOLL_STOP_BK			(1 << 2)
#घोषणा RTL818x_TPPOLL_STOP_MG			(1 << 1)
#घोषणा RTL818x_TPPOLL_STOP_HI			(1 << 6)

	__le32	HSSI_PARA; /*  0x94 */
	u8	reserved_13[4]; /* 0x98 */
	u8	TX_AGC_CTL; /*  0x9c */
#घोषणा RTL818X_TX_AGC_CTL_PERPACKET_GAIN	(1 << 0)
#घोषणा RTL818X_TX_AGC_CTL_PERPACKET_ANTSEL	(1 << 1)
#घोषणा RTL818X_TX_AGC_CTL_FEEDBACK_ANT		(1 << 2)
	u8	TX_GAIN_CCK;
	u8	TX_GAIN_OFDM;
	u8	TX_ANTENNA;
	u8	reserved_14[16];
	u8	WPA_CONF;
	u8	reserved_15[3];
	u8	SIFS;
	u8	DIFS;
	u8	SLOT;
	u8	reserved_16[5];
	u8	CW_CONF;
#घोषणा RTL818X_CW_CONF_PERPACKET_CW	(1 << 0)
#घोषणा RTL818X_CW_CONF_PERPACKET_RETRY	(1 << 1)
	u8	CW_VAL;
	u8	RATE_FALLBACK;
#घोषणा RTL818X_RATE_FALLBACK_ENABLE	(1 << 7)
	u8	ACM_CONTROL;
	u8	reserved_17[24];
	u8	CONFIG5;
	u8	TX_DMA_POLLING;
	u8	PHY_PR;
	u8	reserved_18;
	__le16	CWR;
	u8	RETRY_CTR;
	u8	reserved_19[3];
	__le16	INT_MIG;
/* RTL818X_R8187B_*: magic numbers from ioरेजिस्टरs */
#घोषणा RTL818X_R8187B_B	0
#घोषणा RTL818X_R8187B_D	1
#घोषणा RTL818X_R8187B_E	2
	__le32	RDSAR;
	__le16	TID_AC_MAP;
	u8	reserved_20[4];
	जोड़ अणु
		__le16	ANAPARAM3; /* 0xee */
		u8	ANAPARAM3A; /* क्रम rtl8187 */
	पूर्ण;

#घोषणा AC_PARAM_TXOP_LIMIT_SHIFT	16
#घोषणा AC_PARAM_ECW_MAX_SHIFT		12
#घोषणा AC_PARAM_ECW_MIN_SHIFT		8
#घोषणा AC_PARAM_AIFS_SHIFT		0

	__le32 AC_VO_PARAM; /* 0xf0 */

	जोड़ अणु /* 0xf4 */
		__le32 AC_VI_PARAM;
		__le16 FEMR;
	पूर्ण __packed;

	जोड़अणु /* 0xf8 */
		__le32  AC_BE_PARAM; /* rtl8187se */
		काष्ठाअणु
			u8      reserved_21[2];
			__le16	TALLY_CNT; /* 0xfa */
		पूर्ण __packed;
	पूर्ण __packed;

	जोड़ अणु
		u8	TALLY_SEL; /* 0xfc */
		__le32  AC_BK_PARAM;

	पूर्ण __packed;

पूर्ण __packed;

/* These are addresses with NON-standard usage.
 * They have offsets very far from this काष्ठा.
 * I करोn't like to पूर्णांकroduce a ton of "reserved"..
 * They are क्रम RTL8187SE
 */
#घोषणा REG_ADDR1(addr)	((u8 __iomem *)priv->map + (addr))
#घोषणा REG_ADDR2(addr)	((__le16 __iomem *)priv->map + ((addr) >> 1))
#घोषणा REG_ADDR4(addr)	((__le32 __iomem *)priv->map + ((addr) >> 2))

#घोषणा FEMR_SE		REG_ADDR2(0x1D4)
#घोषणा ARFR		REG_ADDR2(0x1E0)
#घोषणा RFSW_CTRL	REG_ADDR2(0x272)
#घोषणा SW_3W_DB0	REG_ADDR2(0x274)
#घोषणा SW_3W_DB0_4	REG_ADDR4(0x274)
#घोषणा SW_3W_DB1	REG_ADDR2(0x278)
#घोषणा SW_3W_DB1_4	REG_ADDR4(0x278)
#घोषणा SW_3W_CMD1	REG_ADDR1(0x27D)
#घोषणा PI_DATA_REG	REG_ADDR2(0x360)
#घोषणा SI_DATA_REG     REG_ADDR2(0x362)

काष्ठा rtl818x_rf_ops अणु
	अक्षर *name;
	व्योम (*init)(काष्ठा ieee80211_hw *);
	व्योम (*stop)(काष्ठा ieee80211_hw *);
	व्योम (*set_chan)(काष्ठा ieee80211_hw *, काष्ठा ieee80211_conf *);
	u8 (*calc_rssi)(u8 agc, u8 sq);
पूर्ण;

/**
 * क्रमागत rtl818x_tx_desc_flags - Tx/Rx flags are common between RTL818X chips
 *
 * @RTL818X_TX_DESC_FLAG_NO_ENC: Disable hardware based encryption.
 * @RTL818X_TX_DESC_FLAG_TX_OK: TX frame was ACKed.
 * @RTL818X_TX_DESC_FLAG_SPLCP: Use लघु preamble.
 * @RTL818X_TX_DESC_FLAG_MOREFRAG: More fragments follow.
 * @RTL818X_TX_DESC_FLAG_CTS: Use CTS-to-self protection.
 * @RTL818X_TX_DESC_FLAG_RTS: Use RTS/CTS protection.
 * @RTL818X_TX_DESC_FLAG_LS: Last segment of the frame.
 * @RTL818X_TX_DESC_FLAG_FS: First segment of the frame.
 */
क्रमागत rtl818x_tx_desc_flags अणु
	RTL818X_TX_DESC_FLAG_NO_ENC	= (1 << 15),
	RTL818X_TX_DESC_FLAG_TX_OK	= (1 << 15),
	RTL818X_TX_DESC_FLAG_SPLCP	= (1 << 16),
	RTL818X_TX_DESC_FLAG_RX_UNDER	= (1 << 16),
	RTL818X_TX_DESC_FLAG_MOREFRAG	= (1 << 17),
	RTL818X_TX_DESC_FLAG_CTS	= (1 << 18),
	RTL818X_TX_DESC_FLAG_RTS	= (1 << 23),
	RTL818X_TX_DESC_FLAG_LS		= (1 << 28),
	RTL818X_TX_DESC_FLAG_FS		= (1 << 29),
	RTL818X_TX_DESC_FLAG_DMA	= (1 << 30),
	RTL818X_TX_DESC_FLAG_OWN	= (1 << 31)
पूर्ण;

क्रमागत rtl818x_rx_desc_flags अणु
	RTL818X_RX_DESC_FLAG_ICV_ERR	= (1 << 12),
	RTL818X_RX_DESC_FLAG_CRC32_ERR	= (1 << 13),
	RTL818X_RX_DESC_FLAG_PM		= (1 << 14),
	RTL818X_RX_DESC_FLAG_RX_ERR	= (1 << 15),
	RTL818X_RX_DESC_FLAG_BCAST	= (1 << 16),
	RTL818X_RX_DESC_FLAG_PAM	= (1 << 17),
	RTL818X_RX_DESC_FLAG_MCAST	= (1 << 18),
	RTL818X_RX_DESC_FLAG_QOS	= (1 << 19), /* RTL8187(B) only */
	RTL818X_RX_DESC_FLAG_TRSW	= (1 << 24), /* RTL8187(B) only */
	RTL818X_RX_DESC_FLAG_SPLCP	= (1 << 25),
	RTL818X_RX_DESC_FLAG_FOF	= (1 << 26),
	RTL818X_RX_DESC_FLAG_DMA_FAIL	= (1 << 27),
	RTL818X_RX_DESC_FLAG_LS		= (1 << 28),
	RTL818X_RX_DESC_FLAG_FS		= (1 << 29),
	RTL818X_RX_DESC_FLAG_EOR	= (1 << 30),
	RTL818X_RX_DESC_FLAG_OWN	= (1 << 31)
पूर्ण;

#पूर्ण_अगर /* RTL818X_H */
