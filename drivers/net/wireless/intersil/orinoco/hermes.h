<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* hermes.h
 *
 * Driver core क्रम the "Hermes" wireless MAC controller, as used in
 * the Lucent Orinoco and Cabletron RoamAbout cards. It should also
 * work on the hfa3841 and hfa3842 MAC controller chips used in the
 * Prism I & II chipsets.
 *
 * This is not a complete driver, just low-level access routines क्रम
 * the MAC controller itself.
 *
 * Based on the prism2 driver from Absolute Value Systems' linux-wlan
 * project, the Linux wvlan_cs driver, Lucent's HCF-Light
 * (wvlan_hcf.c) library, and the NetBSD wireless driver.
 *
 * Copyright (C) 2000, David Gibson, Linuxcare Australia.
 * (C) Copyright David Gibson, IBM Corp. 2001-2003.
 *
 * Portions taken from hfa384x.h.
 * Copyright (C) 1999 AbsoluteValue Systems, Inc. All Rights Reserved.
 */

#अगर_अघोषित _HERMES_H
#घोषणा _HERMES_H

/* Notes on locking:
 *
 * As a module of low level hardware access routines, there is no
 * locking. Users of this module should ensure that they serialize
 * access to the hermes काष्ठाure, and to the hardware
*/

#समावेश <linux/अगर_ether.h>
#समावेश <linux/पन.स>

/*
 * Limits and स्थिरants
 */
#घोषणा		HERMES_ALLOC_LEN_MIN		(4)
#घोषणा		HERMES_ALLOC_LEN_MAX		(2400)
#घोषणा		HERMES_LTV_LEN_MAX		(34)
#घोषणा		HERMES_BAP_DATALEN_MAX		(4096)
#घोषणा		HERMES_BAP_OFFSET_MAX		(4096)
#घोषणा		HERMES_PORTID_MAX		(7)
#घोषणा		HERMES_NUMPORTS_MAX		(HERMES_PORTID_MAX + 1)
#घोषणा		HERMES_PDR_LEN_MAX		(260)	/* in bytes, from EK */
#घोषणा		HERMES_PDA_RECS_MAX		(200)	/* a guess */
#घोषणा		HERMES_PDA_LEN_MAX		(1024)	/* in bytes, from EK */
#घोषणा		HERMES_SCANRESULT_MAX		(35)
#घोषणा		HERMES_CHINFORESULT_MAX		(8)
#घोषणा		HERMES_MAX_MULTICAST		(16)
#घोषणा		HERMES_MAGIC			(0x7d1f)

/*
 * Hermes रेजिस्टर offsets
 */
#घोषणा		HERMES_CMD			(0x00)
#घोषणा		HERMES_PARAM0			(0x02)
#घोषणा		HERMES_PARAM1			(0x04)
#घोषणा		HERMES_PARAM2			(0x06)
#घोषणा		HERMES_STATUS			(0x08)
#घोषणा		HERMES_RESP0			(0x0A)
#घोषणा		HERMES_RESP1			(0x0C)
#घोषणा		HERMES_RESP2			(0x0E)
#घोषणा		HERMES_INFOFID			(0x10)
#घोषणा		HERMES_RXFID			(0x20)
#घोषणा		HERMES_ALLOCFID			(0x22)
#घोषणा		HERMES_TXCOMPLFID		(0x24)
#घोषणा		HERMES_SELECT0			(0x18)
#घोषणा		HERMES_OFFSET0			(0x1C)
#घोषणा		HERMES_DATA0			(0x36)
#घोषणा		HERMES_SELECT1			(0x1A)
#घोषणा		HERMES_OFFSET1			(0x1E)
#घोषणा		HERMES_DATA1			(0x38)
#घोषणा		HERMES_EVSTAT			(0x30)
#घोषणा		HERMES_INTEN			(0x32)
#घोषणा		HERMES_EVACK			(0x34)
#घोषणा		HERMES_CONTROL			(0x14)
#घोषणा		HERMES_SWSUPPORT0		(0x28)
#घोषणा		HERMES_SWSUPPORT1		(0x2A)
#घोषणा		HERMES_SWSUPPORT2		(0x2C)
#घोषणा		HERMES_AUXPAGE			(0x3A)
#घोषणा		HERMES_AUXOFFSET		(0x3C)
#घोषणा		HERMES_AUXDATA			(0x3E)

/*
 * CMD रेजिस्टर biपंचांगasks
 */
#घोषणा		HERMES_CMD_BUSY			(0x8000)
#घोषणा		HERMES_CMD_AINFO		(0x7f00)
#घोषणा		HERMES_CMD_MACPORT		(0x0700)
#घोषणा		HERMES_CMD_RECL			(0x0100)
#घोषणा		HERMES_CMD_WRITE		(0x0100)
#घोषणा		HERMES_CMD_PROGMODE		(0x0300)
#घोषणा		HERMES_CMD_CMDCODE		(0x003f)

/*
 * STATUS रेजिस्टर biपंचांगasks
 */
#घोषणा		HERMES_STATUS_RESULT		(0x7f00)
#घोषणा		HERMES_STATUS_CMDCODE		(0x003f)

/*
 * OFFSET रेजिस्टर biपंचांगasks
 */
#घोषणा		HERMES_OFFSET_BUSY		(0x8000)
#घोषणा		HERMES_OFFSET_ERR		(0x4000)
#घोषणा		HERMES_OFFSET_DATAOFF		(0x0ffe)

/*
 * Event रेजिस्टर biपंचांगasks (INTEN, EVSTAT, EVACK)
 */
#घोषणा		HERMES_EV_TICK			(0x8000)
#घोषणा		HERMES_EV_WTERR			(0x4000)
#घोषणा		HERMES_EV_INFDROP		(0x2000)
#घोषणा		HERMES_EV_INFO			(0x0080)
#घोषणा		HERMES_EV_DTIM			(0x0020)
#घोषणा		HERMES_EV_CMD			(0x0010)
#घोषणा		HERMES_EV_ALLOC			(0x0008)
#घोषणा		HERMES_EV_TXEXC			(0x0004)
#घोषणा		HERMES_EV_TX			(0x0002)
#घोषणा		HERMES_EV_RX			(0x0001)

/*
 * Command codes
 */
/*--- Controller Commands ----------------------------*/
#घोषणा		HERMES_CMD_INIT			(0x0000)
#घोषणा		HERMES_CMD_ENABLE		(0x0001)
#घोषणा		HERMES_CMD_DISABLE		(0x0002)
#घोषणा		HERMES_CMD_DIAG			(0x0003)

/*--- Buffer Mgmt Commands ---------------------------*/
#घोषणा		HERMES_CMD_ALLOC		(0x000A)
#घोषणा		HERMES_CMD_TX			(0x000B)

/*--- Regulate Commands ------------------------------*/
#घोषणा		HERMES_CMD_NOTIFY		(0x0010)
#घोषणा		HERMES_CMD_INQUIRE		(0x0011)

/*--- Configure Commands -----------------------------*/
#घोषणा		HERMES_CMD_ACCESS		(0x0021)
#घोषणा		HERMES_CMD_DOWNLD		(0x0022)

/*--- Serial I/O Commands ----------------------------*/
#घोषणा		HERMES_CMD_READMIF		(0x0030)
#घोषणा		HERMES_CMD_WRITEMIF		(0x0031)

/*--- Debugging Commands -----------------------------*/
#घोषणा		HERMES_CMD_TEST			(0x0038)


/* Test command arguments */
#घोषणा		HERMES_TEST_SET_CHANNEL		0x0800
#घोषणा		HERMES_TEST_MONITOR		0x0b00
#घोषणा		HERMES_TEST_STOP		0x0f00

/* Authentication algorithms */
#घोषणा		HERMES_AUTH_OPEN		1
#घोषणा		HERMES_AUTH_SHARED_KEY		2

/* WEP settings */
#घोषणा		HERMES_WEP_PRIVACY_INVOKED	0x0001
#घोषणा		HERMES_WEP_EXCL_UNENCRYPTED	0x0002
#घोषणा		HERMES_WEP_HOST_ENCRYPT		0x0010
#घोषणा		HERMES_WEP_HOST_DECRYPT		0x0080

/* Symbol hostscan options */
#घोषणा		HERMES_HOSTSCAN_SYMBOL_5SEC	0x0001
#घोषणा		HERMES_HOSTSCAN_SYMBOL_ONCE	0x0002
#घोषणा		HERMES_HOSTSCAN_SYMBOL_PASSIVE	0x0040
#घोषणा		HERMES_HOSTSCAN_SYMBOL_BCAST	0x0080

/*
 * Frame काष्ठाures and स्थिरants
 */

#घोषणा HERMES_DESCRIPTOR_OFFSET	0
#घोषणा HERMES_802_11_OFFSET		(14)
#घोषणा HERMES_802_3_OFFSET		(14 + 32)
#घोषणा HERMES_802_2_OFFSET		(14 + 32 + 14)
#घोषणा HERMES_TXCNTL2_OFFSET		(HERMES_802_3_OFFSET - 2)

#घोषणा HERMES_RXSTAT_ERR		(0x0003)
#घोषणा	HERMES_RXSTAT_BADCRC		(0x0001)
#घोषणा	HERMES_RXSTAT_UNDECRYPTABLE	(0x0002)
#घोषणा	HERMES_RXSTAT_MIC		(0x0010)	/* Frame contains MIC */
#घोषणा	HERMES_RXSTAT_MACPORT		(0x0700)
#घोषणा HERMES_RXSTAT_PCF		(0x1000)	/* Frame was received in CF period */
#घोषणा	HERMES_RXSTAT_MIC_KEY_ID	(0x1800)	/* MIC key used */
#घोषणा	HERMES_RXSTAT_MSGTYPE		(0xE000)
#घोषणा	HERMES_RXSTAT_1042		(0x2000)	/* RFC-1042 frame */
#घोषणा	HERMES_RXSTAT_TUNNEL		(0x4000)	/* bridge-tunnel encoded frame */
#घोषणा	HERMES_RXSTAT_WMP		(0x6000)	/* Wavelan-II Management Protocol frame */

/* Shअगरt amount क्रम key ID in RXSTAT and TXCTRL */
#घोषणा	HERMES_MIC_KEY_ID_SHIFT		11

काष्ठा hermes_tx_descriptor अणु
	__le16 status;
	__le16 reserved1;
	__le16 reserved2;
	__le32 sw_support;
	u8 retry_count;
	u8 tx_rate;
	__le16 tx_control;
पूर्ण __packed;

#घोषणा HERMES_TXSTAT_RETRYERR		(0x0001)
#घोषणा HERMES_TXSTAT_AGEDERR		(0x0002)
#घोषणा HERMES_TXSTAT_DISCON		(0x0004)
#घोषणा HERMES_TXSTAT_FORMERR		(0x0008)

#घोषणा HERMES_TXCTRL_TX_OK		(0x0002)	/* ?? पूर्णांकerrupt on Tx complete */
#घोषणा HERMES_TXCTRL_TX_EX		(0x0004)	/* ?? पूर्णांकerrupt on Tx exception */
#घोषणा HERMES_TXCTRL_802_11		(0x0008)	/* We supply 802.11 header */
#घोषणा HERMES_TXCTRL_MIC		(0x0010)	/* 802.3 + TKIP */
#घोषणा HERMES_TXCTRL_MIC_KEY_ID	(0x1800)	/* MIC Key ID mask */
#घोषणा HERMES_TXCTRL_ALT_RTRY		(0x0020)

/* Inquiry स्थिरants and data types */

#घोषणा HERMES_INQ_TALLIES		(0xF100)
#घोषणा HERMES_INQ_SCAN			(0xF101)
#घोषणा HERMES_INQ_CHANNELINFO		(0xF102)
#घोषणा HERMES_INQ_HOSTSCAN		(0xF103)
#घोषणा HERMES_INQ_HOSTSCAN_SYMBOL	(0xF104)
#घोषणा HERMES_INQ_LINKSTATUS		(0xF200)
#घोषणा HERMES_INQ_SEC_STAT_AGERE	(0xF202)

काष्ठा hermes_tallies_frame अणु
	__le16 TxUnicastFrames;
	__le16 TxMulticastFrames;
	__le16 TxFragments;
	__le16 TxUnicastOctets;
	__le16 TxMulticastOctets;
	__le16 TxDeferredTransmissions;
	__le16 TxSingleRetryFrames;
	__le16 TxMultipleRetryFrames;
	__le16 TxRetryLimitExceeded;
	__le16 TxDiscards;
	__le16 RxUnicastFrames;
	__le16 RxMulticastFrames;
	__le16 RxFragments;
	__le16 RxUnicastOctets;
	__le16 RxMulticastOctets;
	__le16 RxFCSErrors;
	__le16 RxDiscards_NoBuffer;
	__le16 TxDiscardsWrongSA;
	__le16 RxWEPUndecryptable;
	__le16 RxMsgInMsgFragments;
	__le16 RxMsgInBadMsgFragments;
	/* Those last are probably not available in very old firmwares */
	__le16 RxDiscards_WEPICVError;
	__le16 RxDiscards_WEPExcluded;
पूर्ण __packed;

/* Grabbed from wlan-ng - Thanks Mark... - Jean II
 * This is the result of a scan inquiry command */
/* Structure describing info about an Access Poपूर्णांक */
काष्ठा prism2_scan_apinfo अणु
	__le16 channel;		/* Channel where the AP sits */
	__le16 noise;		/* Noise level */
	__le16 level;		/* Signal level */
	u8 bssid[ETH_ALEN];	/* MAC address of the Access Poपूर्णांक */
	__le16 beacon_पूर्णांकerv;	/* Beacon पूर्णांकerval */
	__le16 capabilities;	/* Capabilities */
	__le16 essid_len;	/* ESSID length */
	u8 essid[32];		/* ESSID of the network */
	u8 rates[10];		/* Bit rate supported */
	__le16 proberesp_rate;	/* Data rate of the response frame */
	__le16 atim;		/* ATIM winकरोw समय, Kus (hostscan only) */
पूर्ण __packed;

/* Same stuff क्रम the Lucent/Agere card.
 * Thanks to h1kari <h1kari AT dachb0den.com> - Jean II */
काष्ठा agere_scan_apinfo अणु
	__le16 channel;		/* Channel where the AP sits */
	__le16 noise;		/* Noise level */
	__le16 level;		/* Signal level */
	u8 bssid[ETH_ALEN];	/* MAC address of the Access Poपूर्णांक */
	__le16 beacon_पूर्णांकerv;	/* Beacon पूर्णांकerval */
	__le16 capabilities;	/* Capabilities */
	/* bits: 0-ess, 1-ibss, 4-privacy [wep] */
	__le16 essid_len;	/* ESSID length */
	u8 essid[32];		/* ESSID of the network */
पूर्ण __packed;

/* Moustafa: Scan काष्ठाure क्रम Symbol cards */
काष्ठा symbol_scan_apinfo अणु
	u8 channel;		/* Channel where the AP sits */
	u8 unknown1;		/* 8 in 2.9x and 3.9x f/w, 0 otherwise */
	__le16 noise;		/* Noise level */
	__le16 level;		/* Signal level */
	u8 bssid[ETH_ALEN];	/* MAC address of the Access Poपूर्णांक */
	__le16 beacon_पूर्णांकerv;	/* Beacon पूर्णांकerval */
	__le16 capabilities;	/* Capabilities */
	/* bits: 0-ess, 1-ibss, 4-privacy [wep] */
	__le16 essid_len;	/* ESSID length */
	u8 essid[32];		/* ESSID of the network */
	__le16 rates[5];	/* Bit rate supported */
	__le16 basic_rates;	/* Basic rates biपंचांगask */
	u8 unknown2[6];		/* Always FF:FF:FF:FF:00:00 */
	u8 unknown3[8];		/* Always 0, appeared in f/w 3.91-68 */
पूर्ण __packed;

जोड़ hermes_scan_info अणु
	काष्ठा agere_scan_apinfo	a;
	काष्ठा prism2_scan_apinfo	p;
	काष्ठा symbol_scan_apinfo	s;
पूर्ण;

/* Extended scan काष्ठा क्रम HERMES_INQ_CHANNELINFO.
 * wl_lkm calls this an ACS scan (Automatic Channel Select).
 * Keep out of जोड़ hermes_scan_info because it is much bigger than
 * the older scan काष्ठाures. */
काष्ठा agere_ext_scan_info अणु
	__le16	reserved0;

	u8	noise;
	u8	level;
	u8	rx_flow;
	u8	rate;
	__le16	reserved1[2];

	__le16	frame_control;
	__le16	dur_id;
	u8	addr1[ETH_ALEN];
	u8	addr2[ETH_ALEN];
	u8	bssid[ETH_ALEN];
	__le16	sequence;
	u8	addr4[ETH_ALEN];

	__le16	data_length;

	/* Next 3 fields करो not get filled in. */
	u8	daddr[ETH_ALEN];
	u8	saddr[ETH_ALEN];
	__le16	len_type;

	__le64	बारtamp;
	__le16	beacon_पूर्णांकerval;
	__le16	capabilities;
	u8	data[];
पूर्ण __packed;

#घोषणा HERMES_LINKSTATUS_NOT_CONNECTED   (0x0000)
#घोषणा HERMES_LINKSTATUS_CONNECTED       (0x0001)
#घोषणा HERMES_LINKSTATUS_DISCONNECTED    (0x0002)
#घोषणा HERMES_LINKSTATUS_AP_CHANGE       (0x0003)
#घोषणा HERMES_LINKSTATUS_AP_OUT_OF_RANGE (0x0004)
#घोषणा HERMES_LINKSTATUS_AP_IN_RANGE     (0x0005)
#घोषणा HERMES_LINKSTATUS_ASSOC_FAILED    (0x0006)

काष्ठा hermes_linkstatus अणु
	__le16 linkstatus;         /* Link status */
पूर्ण __packed;

काष्ठा hermes_response अणु
	u16 status, resp0, resp1, resp2;
पूर्ण;

/* "ID" काष्ठाure - used क्रम ESSID and station nickname */
काष्ठा hermes_idstring अणु
	__le16 len;
	__le16 val[16];
पूर्ण __packed;

काष्ठा hermes_multicast अणु
	u8 addr[HERMES_MAX_MULTICAST][ETH_ALEN];
पूर्ण __packed;

/* Timeouts */
#घोषणा HERMES_BAP_BUSY_TIMEOUT (10000) /* In iterations of ~1us */

काष्ठा hermes;

/* Functions to access hardware */
काष्ठा hermes_ops अणु
	पूर्णांक (*init)(काष्ठा hermes *hw);
	पूर्णांक (*cmd_रुको)(काष्ठा hermes *hw, u16 cmd, u16 parm0,
			काष्ठा hermes_response *resp);
	पूर्णांक (*init_cmd_रुको)(काष्ठा hermes *hw, u16 cmd,
			     u16 parm0, u16 parm1, u16 parm2,
			     काष्ठा hermes_response *resp);
	पूर्णांक (*allocate)(काष्ठा hermes *hw, u16 size, u16 *fid);
	पूर्णांक (*पढ़ो_ltv)(काष्ठा hermes *hw, पूर्णांक bap, u16 rid, अचिन्हित buflen,
			u16 *length, व्योम *buf);
	पूर्णांक (*पढ़ो_ltv_pr)(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			      अचिन्हित buflen, u16 *length, व्योम *buf);
	पूर्णांक (*ग_लिखो_ltv)(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			 u16 length, स्थिर व्योम *value);
	पूर्णांक (*bap_pपढ़ो)(काष्ठा hermes *hw, पूर्णांक bap, व्योम *buf, पूर्णांक len,
			 u16 id, u16 offset);
	पूर्णांक (*bap_pग_लिखो)(काष्ठा hermes *hw, पूर्णांक bap, स्थिर व्योम *buf,
			  पूर्णांक len, u16 id, u16 offset);
	पूर्णांक (*पढ़ो_pda)(काष्ठा hermes *hw, __le16 *pda,
			u32 pda_addr, u16 pda_len);
	पूर्णांक (*program_init)(काष्ठा hermes *hw, u32 entry_poपूर्णांक);
	पूर्णांक (*program_end)(काष्ठा hermes *hw);
	पूर्णांक (*program)(काष्ठा hermes *hw, स्थिर अक्षर *buf,
		       u32 addr, u32 len);
	व्योम (*lock_irqsave)(spinlock_t *lock, अचिन्हित दीर्घ *flags);
	व्योम (*unlock_irqrestore)(spinlock_t *lock, अचिन्हित दीर्घ *flags);
	व्योम (*lock_irq)(spinlock_t *lock);
	व्योम (*unlock_irq)(spinlock_t *lock);
पूर्ण;

/* Basic control काष्ठाure */
काष्ठा hermes अणु
	व्योम __iomem *iobase;
	पूर्णांक reg_spacing;
#घोषणा HERMES_16BIT_REGSPACING	0
#घोषणा HERMES_32BIT_REGSPACING	1
	u16 पूर्णांकen; /* Which पूर्णांकerrupts should be enabled? */
	bool eeprom_pda;
	स्थिर काष्ठा hermes_ops *ops;
	व्योम *priv;
पूर्ण;

/* Register access convenience macros */
#घोषणा hermes_पढ़ो_reg(hw, off) \
	(ioपढ़ो16((hw)->iobase + ((off) << (hw)->reg_spacing)))
#घोषणा hermes_ग_लिखो_reg(hw, off, val) \
	(ioग_लिखो16((val), (hw)->iobase + ((off) << (hw)->reg_spacing)))
#घोषणा hermes_पढ़ो_regn(hw, name) hermes_पढ़ो_reg((hw), HERMES_##name)
#घोषणा hermes_ग_लिखो_regn(hw, name, val) \
	hermes_ग_लिखो_reg((hw), HERMES_##name, (val))

/* Function prototypes */
व्योम hermes_काष्ठा_init(काष्ठा hermes *hw, व्योम __iomem *address,
			पूर्णांक reg_spacing);

/* Inline functions */

अटल अंतरभूत पूर्णांक hermes_present(काष्ठा hermes *hw)
अणु
	वापस hermes_पढ़ो_regn(hw, SWSUPPORT0) == HERMES_MAGIC;
पूर्ण

अटल अंतरभूत व्योम hermes_set_irqmask(काष्ठा hermes *hw, u16 events)
अणु
	hw->पूर्णांकen = events;
	hermes_ग_लिखो_regn(hw, INTEN, events);
पूर्ण

अटल अंतरभूत पूर्णांक hermes_enable_port(काष्ठा hermes *hw, पूर्णांक port)
अणु
	वापस hw->ops->cmd_रुको(hw, HERMES_CMD_ENABLE | (port << 8),
				 0, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक hermes_disable_port(काष्ठा hermes *hw, पूर्णांक port)
अणु
	वापस hw->ops->cmd_रुको(hw, HERMES_CMD_DISABLE | (port << 8),
				 0, शून्य);
पूर्ण

/* Initiate an INQUIRE command (tallies or scan).  The result will come as an
 * inक्रमmation frame in __orinoco_ev_info() */
अटल अंतरभूत पूर्णांक hermes_inquire(काष्ठा hermes *hw, u16 rid)
अणु
	वापस hw->ops->cmd_रुको(hw, HERMES_CMD_INQUIRE, rid, शून्य);
पूर्ण

#घोषणा HERMES_BYTES_TO_RECLEN(n) ((((n) + 1) / 2) + 1)
#घोषणा HERMES_RECLEN_TO_BYTES(n) (((n) - 1) * 2)

/* Note that क्रम the next two, the count is in 16-bit words, not bytes */
अटल अंतरभूत व्योम hermes_पढ़ो_words(काष्ठा hermes *hw, पूर्णांक off,
				     व्योम *buf, अचिन्हित count)
अणु
	off = off << hw->reg_spacing;
	ioपढ़ो16_rep(hw->iobase + off, buf, count);
पूर्ण

अटल अंतरभूत व्योम hermes_ग_लिखो_bytes(काष्ठा hermes *hw, पूर्णांक off,
				      स्थिर अक्षर *buf, अचिन्हित count)
अणु
	off = off << hw->reg_spacing;
	ioग_लिखो16_rep(hw->iobase + off, buf, count >> 1);
	अगर (unlikely(count & 1))
		ioग_लिखो8(buf[count - 1], hw->iobase + off);
पूर्ण

अटल अंतरभूत व्योम hermes_clear_words(काष्ठा hermes *hw, पूर्णांक off,
				      अचिन्हित count)
अणु
	अचिन्हित i;

	off = off << hw->reg_spacing;

	क्रम (i = 0; i < count; i++)
		ioग_लिखो16(0, hw->iobase + off);
पूर्ण

#घोषणा HERMES_READ_RECORD(hw, bap, rid, buf) \
	(hw->ops->पढ़ो_ltv((hw), (bap), (rid), माप(*buf), शून्य, (buf)))
#घोषणा HERMES_READ_RECORD_PR(hw, bap, rid, buf) \
	(hw->ops->पढ़ो_ltv_pr((hw), (bap), (rid), माप(*buf), शून्य, (buf)))
#घोषणा HERMES_WRITE_RECORD(hw, bap, rid, buf) \
	(hw->ops->ग_लिखो_ltv((hw), (bap), (rid), \
			    HERMES_BYTES_TO_RECLEN(माप(*buf)), (buf)))

अटल अंतरभूत पूर्णांक hermes_पढ़ो_wordrec(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
				      u16 *word)
अणु
	__le16 rec;
	पूर्णांक err;

	err = HERMES_READ_RECORD(hw, bap, rid, &rec);
	*word = le16_to_cpu(rec);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक hermes_पढ़ो_wordrec_pr(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
					 u16 *word)
अणु
	__le16 rec;
	पूर्णांक err;

	err = HERMES_READ_RECORD_PR(hw, bap, rid, &rec);
	*word = le16_to_cpu(rec);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक hermes_ग_लिखो_wordrec(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
				       u16 word)
अणु
	__le16 rec = cpu_to_le16(word);
	वापस HERMES_WRITE_RECORD(hw, bap, rid, &rec);
पूर्ण

#पूर्ण_अगर  /* _HERMES_H */
