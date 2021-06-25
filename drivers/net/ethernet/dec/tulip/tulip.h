<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/tulip.h

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	Please submit bugs to http://bugzilla.kernel.org/ .
*/

#अगर_अघोषित __NET_TULIP_H__
#घोषणा __NET_TULIP_H__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>



/* undefine, or define to various debugging levels (>4 == obscene levels) */
#घोषणा TULIP_DEBUG 1

#अगर_घोषित CONFIG_TULIP_MMIO
#घोषणा TULIP_BAR	1	/* CBMA */
#अन्यथा
#घोषणा TULIP_BAR	0	/* CBIO */
#पूर्ण_अगर



काष्ठा tulip_chip_table अणु
	अक्षर *chip_name;
	पूर्णांक io_size;
	पूर्णांक valid_पूर्णांकrs;	/* CSR7 पूर्णांकerrupt enable settings */
	पूर्णांक flags;
	व्योम (*media_समयr) (काष्ठा समयr_list *);
	work_func_t media_task;
पूर्ण;


क्रमागत tbl_flag अणु
	HAS_MII			= 0x00001,
	HAS_MEDIA_TABLE		= 0x00002,
	CSR12_IN_SROM		= 0x00004,
	ALWAYS_CHECK_MII	= 0x00008,
	HAS_ACPI		= 0x00010,
	MC_HASH_ONLY		= 0x00020, /* Hash-only multicast filter. */
	HAS_PNICNWAY		= 0x00080,
	HAS_NWAY		= 0x00040, /* Uses पूर्णांकernal NWay xcvr. */
	HAS_INTR_MITIGATION	= 0x00100,
	IS_ASIX			= 0x00200,
	HAS_8023X		= 0x00400,
	COMET_MAC_ADDR		= 0x00800,
	HAS_PCI_MWI		= 0x01000,
	HAS_PHY_IRQ		= 0x02000,
	HAS_SWAPPED_SEEPROM	= 0x04000,
	NEEDS_FAKE_MEDIA_TABLE	= 0x08000,
	COMET_PM		= 0x10000,
पूर्ण;


/* chip types.  careful!  order is VERY IMPORTANT here, as these
 * are used throughout the driver as indices पूर्णांकo arrays */
/* Note 21142 == 21143. */
क्रमागत chips अणु
	DC21040 = 0,
	DC21041 = 1,
	DC21140 = 2,
	DC21142 = 3, DC21143 = 3,
	LC82C168,
	MX98713,
	MX98715,
	MX98725,
	AX88140,
	PNIC2,
	COMET,
	COMPEX9881,
	I21145,
	DM910X,
	CONEXANT,
पूर्ण;


क्रमागत MediaIs अणु
	MediaIsFD = 1,
	MediaAlwaysFD = 2,
	MediaIsMII = 4,
	MediaIsFx = 8,
	MediaIs100 = 16
पूर्ण;


/* Offsets to the Command and Status Registers, "CSRs".  All accesses
   must be दीर्घword inकाष्ठाions and quadword aligned. */
क्रमागत tulip_offsets अणु
	CSR0 = 0,
	CSR1 = 0x08,
	CSR2 = 0x10,
	CSR3 = 0x18,
	CSR4 = 0x20,
	CSR5 = 0x28,
	CSR6 = 0x30,
	CSR7 = 0x38,
	CSR8 = 0x40,
	CSR9 = 0x48,
	CSR10 = 0x50,
	CSR11 = 0x58,
	CSR12 = 0x60,
	CSR13 = 0x68,
	CSR14 = 0x70,
	CSR15 = 0x78,
	CSR18 = 0x88,
	CSR19 = 0x8c,
	CSR20 = 0x90,
	CSR27 = 0xAC,
	CSR28 = 0xB0,
पूर्ण;

/* रेजिस्टर offset and bits क्रम CFDD PCI config reg */
क्रमागत pci_cfg_driver_reg अणु
	CFDD = 0x40,
	CFDD_Sleep = (1 << 31),
	CFDD_Snooze = (1 << 30),
पूर्ण;

#घोषणा RxPollInt (RxIntr|RxNoBuf|RxDied|RxJabber)

/* The bits in the CSR5 status रेजिस्टरs, mostly पूर्णांकerrupt sources. */
क्रमागत status_bits अणु
	TimerInt = 0x800,
	SystemError = 0x2000,
	TPLnkFail = 0x1000,
	TPLnkPass = 0x10,
	NormalIntr = 0x10000,
	AbnormalIntr = 0x8000,
	RxJabber = 0x200,
	RxDied = 0x100,
	RxNoBuf = 0x80,
	RxIntr = 0x40,
	TxFIFOUnderflow = 0x20,
	RxErrIntr = 0x10,
	TxJabber = 0x08,
	TxNoBuf = 0x04,
	TxDied = 0x02,
	TxIntr = 0x01,
पूर्ण;

/* bit mask क्रम CSR5 TX/RX process state */
#घोषणा CSR5_TS	0x00700000
#घोषणा CSR5_RS	0x000e0000

क्रमागत tulip_mode_bits अणु
	TxThreshold		= (1 << 22),
	FullDuplex		= (1 << 9),
	TxOn			= 0x2000,
	AcceptBroadcast		= 0x0100,
	AcceptAllMulticast	= 0x0080,
	AcceptAllPhys		= 0x0040,
	AcceptRunt		= 0x0008,
	RxOn			= 0x0002,
	RxTx			= (TxOn | RxOn),
पूर्ण;


क्रमागत tulip_busconfig_bits अणु
	MWI			= (1 << 24),
	MRL			= (1 << 23),
	MRM			= (1 << 21),
	CALShअगरt		= 14,
	BurstLenShअगरt		= 8,
पूर्ण;


/* The Tulip Rx and Tx buffer descriptors. */
काष्ठा tulip_rx_desc अणु
	__le32 status;
	__le32 length;
	__le32 buffer1;
	__le32 buffer2;
पूर्ण;


काष्ठा tulip_tx_desc अणु
	__le32 status;
	__le32 length;
	__le32 buffer1;
	__le32 buffer2;		/* We use only buffer 1.  */
पूर्ण;


क्रमागत desc_status_bits अणु
	DescOwned    = 0x80000000,
	DescWholePkt = 0x60000000,
	DescEndPkt   = 0x40000000,
	DescStartPkt = 0x20000000,
	DescEndRing  = 0x02000000,
	DescUseLink  = 0x01000000,

	/*
	 * Error summary flag is logical or of 'CRC Error', 'Collision Seen',
	 * 'Frame Too Long', 'Runt' and 'Descriptor Error' flags generated
	 * within tulip chip.
	 */
	RxDescErrorSummary = 0x8000,
	RxDescCRCError = 0x0002,
	RxDescCollisionSeen = 0x0040,

	/*
	 * 'Frame Too Long' flag is set अगर packet length including CRC exceeds
	 * 1518.  However, a full sized VLAN tagged frame is 1522 bytes
	 * including CRC.
	 *
	 * The tulip chip करोes not block oversized frames, and अगर this flag is
	 * set on a receive descriptor it करोes not indicate the frame has been
	 * truncated.  The receive descriptor also includes the actual length.
	 * Thereक्रमe we can safety ignore this flag and check the length
	 * ourselves.
	 */
	RxDescFrameTooLong = 0x0080,
	RxDescRunt = 0x0800,
	RxDescDescErr = 0x4000,
	RxWholePkt   = 0x00000300,
	/*
	 * Top three bits of 14 bit frame length (status bits 27-29) should
	 * never be set as that would make frame over 2047 bytes. The Receive
	 * Watchकरोg flag (bit 4) may indicate the length is over 2048 and the
	 * length field is invalid.
	 */
	RxLengthOver2047 = 0x38000010
पूर्ण;


क्रमागत t21143_csr6_bits अणु
	csr6_sc = (1<<31),
	csr6_ra = (1<<30),
	csr6_ign_dest_msb = (1<<26),
	csr6_mbo = (1<<25),
	csr6_scr = (1<<24),  /* scramble mode flag: can't be set */
	csr6_pcs = (1<<23),  /* Enables PCS functions (symbol mode requires csr6_ps be set) शेष is set */
	csr6_tपंचांग = (1<<22),  /* Transmit Threshold Mode, set क्रम 10baseT, 0 क्रम 100BaseTX */
	csr6_sf = (1<<21),   /* Store and क्रमward. If set ignores TR bits */
	csr6_hbd = (1<<19),  /* Heart beat disable. Disables SQE function in 10baseT */
	csr6_ps = (1<<18),   /* Port Select. 0 (defualt) = 10baseT, 1 = 100baseTX: can't be set */
	csr6_ca = (1<<17),   /* Collision Offset Enable. If set uses special algorithm in low collision situations */
	csr6_trh = (1<<15),  /* Transmit Threshold high bit */
	csr6_trl = (1<<14),  /* Transmit Threshold low bit */

	/***************************************************************
	 * This table shows transmit threshold values based on media   *
	 * and these two रेजिस्टरs (from PNIC1 & 2 करोcs) Note: this is *
	 * all meaningless अगर sf is set.                               *
	 ***************************************************************/

	/***********************************
	 * (trh,trl) * 100BaseTX * 10BaseT *
	 ***********************************
	 *   (0,0)   *     128   *    72   *
	 *   (0,1)   *     256   *    96   *
	 *   (1,0)   *     512   *   128   *
	 *   (1,1)   *    1024   *   160   *
	 ***********************************/

	csr6_fc = (1<<12),   /* Forces a collision in next transmission (क्रम testing in loopback mode) */
	csr6_om_पूर्णांक_loop = (1<<10), /* पूर्णांकernal (FIFO) loopback flag */
	csr6_om_ext_loop = (1<<11), /* बाह्यal (PMD) loopback flag */
	/* set both and you get (PHY) loopback */
	csr6_fd = (1<<9),    /* Full duplex mode, disables hearbeat, no loopback */
	csr6_pm = (1<<7),    /* Pass All Multicast */
	csr6_pr = (1<<6),    /* Promiscuous mode */
	csr6_sb = (1<<5),    /* Start(1)/Stop(0) backoff counter */
	csr6_अगर = (1<<4),    /* Inverse Filtering, rejects only addresses in address table: can't be set */
	csr6_pb = (1<<3),    /* Pass Bad Frames, (1) causes even bad frames to be passed on */
	csr6_ho = (1<<2),    /* Hash-only filtering mode: can't be set */
	csr6_hp = (1<<0),    /* Hash/Perfect Receive Filtering Mode: can't be set */

	csr6_mask_capture = (csr6_sc | csr6_ca),
	csr6_mask_deख_स्थितिe = (csr6_mask_capture | csr6_mbo),
	csr6_mask_hdcap = (csr6_mask_deख_स्थितिe | csr6_hbd | csr6_ps),
	csr6_mask_hdcaptt = (csr6_mask_hdcap  | csr6_trh | csr6_trl),
	csr6_mask_fullcap = (csr6_mask_hdcaptt | csr6_fd),
	csr6_mask_fullpromisc = (csr6_pr | csr6_pm),
	csr6_mask_filters = (csr6_hp | csr6_ho | csr6_अगर),
	csr6_mask_100bt = (csr6_scr | csr6_pcs | csr6_hbd),
पूर्ण;

क्रमागत tulip_comet_csr13_bits अणु
/* The LINKOFFE and LINKONE work in conjunction with LSCE, i.e. they
 * determine which link status transition wakes up अगर LSCE is
 * enabled */
        comet_csr13_linkoffe = (1 << 17),
        comet_csr13_linkone = (1 << 16),
        comet_csr13_wfre = (1 << 10),
        comet_csr13_mpre = (1 << 9),
        comet_csr13_lsce = (1 << 8),
        comet_csr13_wfr = (1 << 2),
        comet_csr13_mpr = (1 << 1),
        comet_csr13_lsc = (1 << 0),
पूर्ण;

क्रमागत tulip_comet_csr18_bits अणु
        comet_csr18_pmes_sticky = (1 << 24),
        comet_csr18_pm_mode = (1 << 19),
        comet_csr18_apm_mode = (1 << 18),
        comet_csr18_d3a = (1 << 7)
पूर्ण;

क्रमागत tulip_comet_csr20_bits अणु
        comet_csr20_pmes = (1 << 15),
पूर्ण;

/* Keep the ring sizes a घातer of two क्रम efficiency.
   Making the Tx ring too large decreases the effectiveness of channel
   bonding and packet priority.
   There are no ill effects from too-large receive rings. */

#घोषणा TX_RING_SIZE	32
#घोषणा RX_RING_SIZE	128
#घोषणा MEDIA_MASK     31

/* The receiver on the DC21143 rev 65 can fail to बंद the last
 * receive descriptor in certain circumstances (see errata) when
 * using MWI. This can only occur अगर the receive buffer ends on
 * a cache line boundary, so the "+ 4" below ensures it करोesn't.
 */
#घोषणा PKT_BUF_SZ	(1536 + 4)	/* Size of each temporary Rx buffer. */

#घोषणा TULIP_MIN_CACHE_LINE	8	/* in units of 32-bit words */

#अगर defined(__sparc__) || defined(__hppa__)
/* The UltraSparc PCI controllers will disconnect at every 64-byte
 * crossing anyways so it makes no sense to tell Tulip to burst
 * any more than that.
 */
#घोषणा TULIP_MAX_CACHE_LINE	16	/* in units of 32-bit words */
#अन्यथा
#घोषणा TULIP_MAX_CACHE_LINE	32	/* in units of 32-bit words */
#पूर्ण_अगर


/* Ring-wrap flag in length field, use क्रम last ring entry.
	0x01000000 means chain on buffer2 address,
	0x02000000 means use the ring start address in CSR2/3.
   Note: Some work-alike chips करो not function correctly in chained mode.
   The ASIX chip works only in chained mode.
   Thus we indicates ring mode, but always ग_लिखो the 'next' field क्रम
   chained mode as well.
*/
#घोषणा DESC_RING_WRAP 0x02000000


#घोषणा EEPROM_SIZE 512 	/* 2 << EEPROM_ADDRLEN */


#घोषणा RUN_AT(x) (jअगरfies + (x))

#घोषणा get_u16(ptr) get_unaligned_le16((ptr))

काष्ठा medialeaf अणु
	u8 type;
	u8 media;
	अचिन्हित अक्षर *leafdata;
पूर्ण;


काष्ठा mediatable अणु
	u16 शेषmedia;
	u8 leafcount;
	u8 csr12dir;		/* General purpose pin directions. */
	अचिन्हित has_mii:1;
	अचिन्हित has_nonmii:1;
	अचिन्हित has_reset:6;
	u32 csr15dir;
	u32 csr15val;		/* 21143 NWay setting. */
	काष्ठा medialeaf mleaf[];
पूर्ण;


काष्ठा mediainfo अणु
	काष्ठा mediainfo *next;
	पूर्णांक info_type;
	पूर्णांक index;
	अचिन्हित अक्षर *info;
पूर्ण;

काष्ठा ring_info अणु
	काष्ठा sk_buff	*skb;
	dma_addr_t	mapping;
पूर्ण;


काष्ठा tulip_निजी अणु
	स्थिर अक्षर *product_name;
	काष्ठा net_device *next_module;
	काष्ठा tulip_rx_desc *rx_ring;
	काष्ठा tulip_tx_desc *tx_ring;
	dma_addr_t rx_ring_dma;
	dma_addr_t tx_ring_dma;
	/* The saved address of a sent-in-place packet/buffer, क्रम skमुक्त(). */
	काष्ठा ring_info tx_buffers[TX_RING_SIZE];
	/* The addresses of receive-in-place skbuffs. */
	काष्ठा ring_info rx_buffers[RX_RING_SIZE];
	u16 setup_frame[96];	/* Pseuकरो-Tx frame to init address table. */
	पूर्णांक chip_id;
	पूर्णांक revision;
	पूर्णांक flags;
	काष्ठा napi_काष्ठा napi;
	काष्ठा समयr_list समयr;	/* Media selection समयr. */
	काष्ठा समयr_list oom_समयr;    /* Out of memory समयr. */
	u32 mc_filter[2];
	spinlock_t lock;
	spinlock_t mii_lock;
	अचिन्हित पूर्णांक cur_rx, cur_tx;	/* The next मुक्त ring entry */
	अचिन्हित पूर्णांक dirty_rx, dirty_tx;	/* The ring entries to be मुक्त()ed. */

#अगर_घोषित 	CONFIG_TULIP_NAPI_HW_MITIGATION
        पूर्णांक mit_on;
#पूर्ण_अगर
	अचिन्हित पूर्णांक full_duplex:1;	/* Full-duplex operation requested. */
	अचिन्हित पूर्णांक full_duplex_lock:1;
	अचिन्हित पूर्णांक fake_addr:1;	/* Multiport board faked address. */
	अचिन्हित पूर्णांक शेष_port:4;	/* Last dev->अगर_port value. */
	अचिन्हित पूर्णांक media2:4;	/* Secondary monitored media port. */
	अचिन्हित पूर्णांक medialock:1;	/* Don't sense media type. */
	अचिन्हित पूर्णांक mediasense:1;	/* Media sensing in progress. */
	अचिन्हित पूर्णांक nway:1, nwayset:1;		/* 21143 पूर्णांकernal NWay. */
	अचिन्हित पूर्णांक समयout_recovery:1;
	अचिन्हित पूर्णांक csr0;	/* CSR0 setting. */
	अचिन्हित पूर्णांक csr6;	/* Current CSR6 control settings. */
	अचिन्हित अक्षर eeprom[EEPROM_SIZE];	/* Serial EEPROM contents. */
	व्योम (*link_change) (काष्ठा net_device * dev, पूर्णांक csr5);
        काष्ठा ethtool_wolinfo wolinfo;        /* WOL settings */
	u16 sym_advertise, mii_advertise; /* NWay capabilities advertised.  */
	u16 lpar;		/* 21143 Link partner ability. */
	u16 advertising[4];
	चिन्हित अक्षर phys[4], mii_cnt;	/* MII device addresses. */
	काष्ठा mediatable *mtable;
	पूर्णांक cur_index;		/* Current media index. */
	पूर्णांक saved_अगर_port;
	काष्ठा pci_dev *pdev;
	पूर्णांक tसमयr;
	पूर्णांक susp_rx;
	अचिन्हित दीर्घ nir;
	व्योम __iomem *base_addr;
	पूर्णांक csr12_shaकरोw;
	पूर्णांक pad0;		/* Used क्रम 8-byte alignment */
	काष्ठा work_काष्ठा media_work;
	काष्ठा net_device *dev;
पूर्ण;


काष्ठा eeprom_fixup अणु
	अक्षर *name;
	अचिन्हित अक्षर addr0;
	अचिन्हित अक्षर addr1;
	अचिन्हित अक्षर addr2;
	u16 newtable[32];	/* Max length below. */
पूर्ण;


/* 21142.c */
बाह्य u16 t21142_csr14[];
व्योम t21142_media_task(काष्ठा work_काष्ठा *work);
व्योम t21142_start_nway(काष्ठा net_device *dev);
व्योम t21142_lnk_change(काष्ठा net_device *dev, पूर्णांक csr5);


/* PNIC2.c */
व्योम pnic2_lnk_change(काष्ठा net_device *dev, पूर्णांक csr5);
व्योम pnic2_समयr(काष्ठा समयr_list *t);
व्योम pnic2_start_nway(काष्ठा net_device *dev);
व्योम pnic2_lnk_change(काष्ठा net_device *dev, पूर्णांक csr5);

/* eeprom.c */
व्योम tulip_parse_eeprom(काष्ठा net_device *dev);
पूर्णांक tulip_पढ़ो_eeprom(काष्ठा net_device *dev, पूर्णांक location, पूर्णांक addr_len);

/* पूर्णांकerrupt.c */
बाह्य अचिन्हित पूर्णांक tulip_max_पूर्णांकerrupt_work;
बाह्य पूर्णांक tulip_rx_copyअवरोध;
irqवापस_t tulip_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
पूर्णांक tulip_refill_rx(काष्ठा net_device *dev);
#अगर_घोषित CONFIG_TULIP_NAPI
पूर्णांक tulip_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
#पूर्ण_अगर


/* media.c */
पूर्णांक tulip_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
व्योम tulip_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
व्योम tulip_select_media(काष्ठा net_device *dev, पूर्णांक startup);
पूर्णांक tulip_check_duplex(काष्ठा net_device *dev);
व्योम tulip_find_mii (काष्ठा net_device *dev, पूर्णांक board_idx);

/* pnic.c */
व्योम pnic_करो_nway(काष्ठा net_device *dev);
व्योम pnic_lnk_change(काष्ठा net_device *dev, पूर्णांक csr5);
व्योम pnic_समयr(काष्ठा समयr_list *t);

/* समयr.c */
व्योम tulip_media_task(काष्ठा work_काष्ठा *work);
व्योम mxic_समयr(काष्ठा समयr_list *t);
व्योम comet_समयr(काष्ठा समयr_list *t);

/* tulip_core.c */
बाह्य पूर्णांक tulip_debug;
बाह्य स्थिर अक्षर * स्थिर medianame[];
बाह्य स्थिर अक्षर tulip_media_cap[];
बाह्य स्थिर काष्ठा tulip_chip_table tulip_tbl[];
व्योम oom_समयr(काष्ठा समयr_list *t);
बाह्य u8 t21040_csr13[];

अटल अंतरभूत व्योम tulip_start_rxtx(काष्ठा tulip_निजी *tp)
अणु
	व्योम __iomem *ioaddr = tp->base_addr;
	ioग_लिखो32(tp->csr6 | RxTx, ioaddr + CSR6);
	barrier();
	(व्योम) ioपढ़ो32(ioaddr + CSR6); /* mmio sync */
पूर्ण

अटल अंतरभूत व्योम tulip_stop_rxtx(काष्ठा tulip_निजी *tp)
अणु
	व्योम __iomem *ioaddr = tp->base_addr;
	u32 csr6 = ioपढ़ो32(ioaddr + CSR6);

	अगर (csr6 & RxTx) अणु
		अचिन्हित i=1300/10;
		ioग_लिखो32(csr6 & ~RxTx, ioaddr + CSR6);
		barrier();
		/* रुको until in-flight frame completes.
		 * Max समय @ 10BT: 1500*8b/10Mbps == 1200us (+ 100us margin)
		 * Typically expect this loop to end in < 50 us on 100BT.
		 */
		जबतक (--i && (ioपढ़ो32(ioaddr + CSR5) & (CSR5_TS|CSR5_RS)))
			udelay(10);

		अगर (!i)
			netdev_dbg(tp->dev, "tulip_stop_rxtx() failed (CSR5 0x%x CSR6 0x%x)\n",
				   ioपढ़ो32(ioaddr + CSR5),
				   ioपढ़ो32(ioaddr + CSR6));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tulip_restart_rxtx(काष्ठा tulip_निजी *tp)
अणु
	tulip_stop_rxtx(tp);
	udelay(5);
	tulip_start_rxtx(tp);
पूर्ण

अटल अंतरभूत व्योम tulip_tx_समयout_complete(काष्ठा tulip_निजी *tp, व्योम __iomem *ioaddr)
अणु
	/* Stop and restart the chip's Tx processes. */
	tulip_restart_rxtx(tp);
	/* Trigger an immediate transmit demand. */
	ioग_लिखो32(0, ioaddr + CSR1);

	tp->dev->stats.tx_errors++;
पूर्ण

#पूर्ण_अगर /* __NET_TULIP_H__ */
