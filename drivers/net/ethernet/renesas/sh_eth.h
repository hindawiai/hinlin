<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  SuperH Ethernet device driver
 *
 *  Copyright (C) 2006-2012 Nobuhiro Iwamatsu
 *  Copyright (C) 2008-2012 Renesas Solutions Corp.
 */

#अगर_अघोषित __SH_ETH_H__
#घोषणा __SH_ETH_H__

#घोषणा CARDNAME	"sh-eth"
#घोषणा TX_TIMEOUT	(5*HZ)
#घोषणा TX_RING_SIZE	64	/* Tx ring size */
#घोषणा RX_RING_SIZE	64	/* Rx ring size */
#घोषणा TX_RING_MIN	64
#घोषणा RX_RING_MIN	64
#घोषणा TX_RING_MAX	1024
#घोषणा RX_RING_MAX	1024
#घोषणा PKT_BUF_SZ	1538
#घोषणा SH_ETH_TSU_TIMEOUT_MS	500
#घोषणा SH_ETH_TSU_CAM_ENTRIES	32

क्रमागत अणु
	/* IMPORTANT: To keep ethtool रेजिस्टर dump working, add new
	 * रेजिस्टर names immediately beक्रमe SH_ETH_MAX_REGISTER_OFFSET.
	 */

	/* E-DMAC रेजिस्टरs */
	EDSR = 0,
	EDMR,
	EDTRR,
	EDRRR,
	EESR,
	EESIPR,
	TDLAR,
	TDFAR,
	TDFXR,
	TDFFR,
	RDLAR,
	RDFAR,
	RDFXR,
	RDFFR,
	TRSCER,
	RMFCR,
	TFTR,
	FDR,
	RMCR,
	EDOCR,
	TFUCR,
	RFOCR,
	RMIIMODE,
	FCFTR,
	RPAसूची,
	TRIMD,
	RBWAR,
	TBRAR,

	/* Ether रेजिस्टरs */
	ECMR,
	ECSR,
	ECSIPR,
	PIR,
	PSR,
	RDMLR,
	PIPR,
	RFLR,
	IPGR,
	APR,
	MPR,
	PFTCR,
	PFRCR,
	RFCR,
	RFCF,
	TPAUSER,
	TPAUSECR,
	BCFR,
	BCFRR,
	GECMR,
	BCULR,
	MAHR,
	MALR,
	TROCR,
	CDCR,
	LCCR,
	CNDCR,
	CEFCR,
	FRECR,
	TSFRCR,
	TLFRCR,
	CERCR,
	CEECR,
	MAFCR,
	RTRATE,
	CSMR,
	RMII_MII,

	/* TSU Absolute address */
	ARSTR,
	TSU_CTRST,
	TSU_FWEN0,
	TSU_FWEN1,
	TSU_FCM,
	TSU_BSYSL0,
	TSU_BSYSL1,
	TSU_PRISL0,
	TSU_PRISL1,
	TSU_FWSL0,
	TSU_FWSL1,
	TSU_FWSLC,
	TSU_QTAG0,			/* Same as TSU_QTAGM0 */
	TSU_QTAG1,			/* Same as TSU_QTAGM1 */
	TSU_QTAGM0,
	TSU_QTAGM1,
	TSU_FWSR,
	TSU_FWINMK,
	TSU_ADQT0,
	TSU_ADQT1,
	TSU_VTAG0,
	TSU_VTAG1,
	TSU_ADSBSY,
	TSU_TEN,
	TSU_POST1,
	TSU_POST2,
	TSU_POST3,
	TSU_POST4,
	TSU_ADRH0,
	/* TSU_ADRअणुH,Lपूर्णअणु0..31पूर्ण are assumed to be contiguous */

	TXNLCR0,
	TXALCR0,
	RXNLCR0,
	RXALCR0,
	FWNLCR0,
	FWALCR0,
	TXNLCR1,
	TXALCR1,
	RXNLCR1,
	RXALCR1,
	FWNLCR1,
	FWALCR1,

	/* This value must be written at last. */
	SH_ETH_MAX_REGISTER_OFFSET,
पूर्ण;

क्रमागत अणु
	SH_ETH_REG_GIGABIT,
	SH_ETH_REG_FAST_RCAR,
	SH_ETH_REG_FAST_SH4,
	SH_ETH_REG_FAST_SH3_SH2
पूर्ण;

/* Driver's parameters */
#अगर defined(CONFIG_CPU_SH4) || defined(CONFIG_ARCH_RENESAS)
#घोषणा SH_ETH_RX_ALIGN		32
#अन्यथा
#घोषणा SH_ETH_RX_ALIGN		2
#पूर्ण_अगर

/* Register's bits
 */
/* EDSR : sh7734, sh7757, sh7763, r8a7740, and r7s72100 only */
क्रमागत EDSR_BIT अणु
	EDSR_ENT = 0x01, EDSR_ENR = 0x02,
पूर्ण;
#घोषणा EDSR_ENALL (EDSR_ENT|EDSR_ENR)

/* GECMR : sh7734, sh7763 and r8a7740 only */
क्रमागत GECMR_BIT अणु
	GECMR_10 = 0x0, GECMR_100 = 0x04, GECMR_1000 = 0x01,
पूर्ण;

/* EDMR */
क्रमागत EDMR_BIT अणु
	EDMR_NBST = 0x80,
	EDMR_EL = 0x40, /* Litte endian */
	EDMR_DL1 = 0x20, EDMR_DL0 = 0x10,
	EDMR_SRST_GETHER = 0x03,
	EDMR_SRST_ETHER = 0x01,
पूर्ण;

/* EDTRR */
क्रमागत EDTRR_BIT अणु
	EDTRR_TRNS_GETHER = 0x03,
	EDTRR_TRNS_ETHER = 0x01,
पूर्ण;

/* EDRRR */
क्रमागत EDRRR_BIT अणु
	EDRRR_R = 0x01,
पूर्ण;

/* TPAUSER */
क्रमागत TPAUSER_BIT अणु
	TPAUSER_TPAUSE = 0x0000ffff,
	TPAUSER_UNLIMITED = 0,
पूर्ण;

/* BCFR */
क्रमागत BCFR_BIT अणु
	BCFR_RPAUSE = 0x0000ffff,
	BCFR_UNLIMITED = 0,
पूर्ण;

/* PIR */
क्रमागत PIR_BIT अणु
	PIR_MDI = 0x08, PIR_MDO = 0x04, PIR_MMD = 0x02, PIR_MDC = 0x01,
पूर्ण;

/* PSR */
क्रमागत PSR_BIT अणु PSR_LMON = 0x01, पूर्ण;

/* EESR */
क्रमागत EESR_BIT अणु
	EESR_TWB1	= 0x80000000,
	EESR_TWB	= 0x40000000,	/* same as TWB0 */
	EESR_TC1	= 0x20000000,
	EESR_TUC	= 0x10000000,
	EESR_ROC	= 0x08000000,
	EESR_TABT	= 0x04000000,
	EESR_RABT	= 0x02000000,
	EESR_RFRMER	= 0x01000000,	/* same as RFCOF */
	EESR_ADE	= 0x00800000,
	EESR_ECI	= 0x00400000,
	EESR_FTC	= 0x00200000,	/* same as TC or TC0 */
	EESR_TDE	= 0x00100000,
	EESR_TFE	= 0x00080000,	/* same as TFUF */
	EESR_FRC	= 0x00040000,	/* same as FR */
	EESR_RDE	= 0x00020000,
	EESR_RFE	= 0x00010000,
	EESR_CND	= 0x00000800,
	EESR_DLC	= 0x00000400,
	EESR_CD		= 0x00000200,
	EESR_TRO	= 0x00000100,
	EESR_RMAF	= 0x00000080,
	EESR_CEEF	= 0x00000040,
	EESR_CELF	= 0x00000020,
	EESR_RRF	= 0x00000010,
	EESR_RTLF	= 0x00000008,
	EESR_RTSF	= 0x00000004,
	EESR_PRE	= 0x00000002,
	EESR_CERF	= 0x00000001,
पूर्ण;

#घोषणा EESR_RX_CHECK		(EESR_FRC  | /* Frame recv */		\
				 EESR_RMAF | /* Multicast address recv */ \
				 EESR_RRF  | /* Bit frame recv */	\
				 EESR_RTLF | /* Long frame recv */	\
				 EESR_RTSF | /* Short frame recv */	\
				 EESR_PRE  | /* PHY-LSI recv error */	\
				 EESR_CERF)  /* Recv frame CRC error */

#घोषणा DEFAULT_TX_CHECK	(EESR_FTC | EESR_CND | EESR_DLC | EESR_CD | \
				 EESR_TRO)
#घोषणा DEFAULT_EESR_ERR_CHECK	(EESR_TWB | EESR_TABT | EESR_RABT | EESR_RFE | \
				 EESR_RDE | EESR_RFRMER | EESR_ADE | \
				 EESR_TFE | EESR_TDE)

/* EESIPR */
क्रमागत EESIPR_BIT अणु
	EESIPR_TWB1IP	= 0x80000000,
	EESIPR_TWBIP	= 0x40000000,	/* same as TWB0IP */
	EESIPR_TC1IP	= 0x20000000,
	EESIPR_TUCIP	= 0x10000000,
	EESIPR_ROCIP	= 0x08000000,
	EESIPR_TABTIP	= 0x04000000,
	EESIPR_RABTIP	= 0x02000000,
	EESIPR_RFCOFIP	= 0x01000000,
	EESIPR_ADEIP	= 0x00800000,
	EESIPR_ECIIP	= 0x00400000,
	EESIPR_FTCIP	= 0x00200000,	/* same as TC0IP */
	EESIPR_TDEIP	= 0x00100000,
	EESIPR_TFUFIP	= 0x00080000,
	EESIPR_FRIP	= 0x00040000,
	EESIPR_RDEIP	= 0x00020000,
	EESIPR_RFOFIP	= 0x00010000,
	EESIPR_CNDIP	= 0x00000800,
	EESIPR_DLCIP	= 0x00000400,
	EESIPR_CDIP	= 0x00000200,
	EESIPR_TROIP	= 0x00000100,
	EESIPR_RMAFIP	= 0x00000080,
	EESIPR_CEEFIP	= 0x00000040,
	EESIPR_CELFIP	= 0x00000020,
	EESIPR_RRFIP	= 0x00000010,
	EESIPR_RTLFIP	= 0x00000008,
	EESIPR_RTSFIP	= 0x00000004,
	EESIPR_PREIP	= 0x00000002,
	EESIPR_CERFIP	= 0x00000001,
पूर्ण;

/* FCFTR */
क्रमागत FCFTR_BIT अणु
	FCFTR_RFF2 = 0x00040000, FCFTR_RFF1 = 0x00020000,
	FCFTR_RFF0 = 0x00010000, FCFTR_RFD2 = 0x00000004,
	FCFTR_RFD1 = 0x00000002, FCFTR_RFD0 = 0x00000001,
पूर्ण;
#घोषणा DEFAULT_FIFO_F_D_RFF	(FCFTR_RFF2 | FCFTR_RFF1 | FCFTR_RFF0)
#घोषणा DEFAULT_FIFO_F_D_RFD	(FCFTR_RFD2 | FCFTR_RFD1 | FCFTR_RFD0)

/* RMCR */
क्रमागत RMCR_BIT अणु
	RMCR_RNC = 0x00000001,
पूर्ण;

/* ECMR */
क्रमागत ECMR_BIT अणु
	ECMR_TRCCM = 0x04000000, ECMR_RCSC = 0x00800000,
	ECMR_DPAD = 0x00200000, ECMR_RZPF = 0x00100000,
	ECMR_ZPF = 0x00080000, ECMR_PFR = 0x00040000, ECMR_RXF = 0x00020000,
	ECMR_TXF = 0x00010000, ECMR_MCT = 0x00002000, ECMR_PRCEF = 0x00001000,
	ECMR_MPDE = 0x00000200, ECMR_RE = 0x00000040, ECMR_TE = 0x00000020,
	ECMR_RTM = 0x00000010, ECMR_ILB = 0x00000008, ECMR_ELB = 0x00000004,
	ECMR_DM = 0x00000002, ECMR_PRM = 0x00000001,
पूर्ण;

/* ECSR */
क्रमागत ECSR_BIT अणु
	ECSR_BRCRX = 0x20, ECSR_PSRTO = 0x10,
	ECSR_LCHNG = 0x04,
	ECSR_MPD = 0x02, ECSR_ICD = 0x01,
पूर्ण;

#घोषणा DEFAULT_ECSR_INIT	(ECSR_BRCRX | ECSR_PSRTO | ECSR_LCHNG | \
				 ECSR_ICD | ECSIPR_MPDIP)

/* ECSIPR */
क्रमागत ECSIPR_BIT अणु
	ECSIPR_BRCRXIP = 0x20, ECSIPR_PSRTOIP = 0x10,
	ECSIPR_LCHNGIP = 0x04,
	ECSIPR_MPDIP = 0x02, ECSIPR_ICDIP = 0x01,
पूर्ण;

#घोषणा DEFAULT_ECSIPR_INIT	(ECSIPR_BRCRXIP | ECSIPR_PSRTOIP | \
				 ECSIPR_LCHNGIP | ECSIPR_ICDIP | ECSIPR_MPDIP)

/* APR */
क्रमागत APR_BIT अणु
	APR_AP = 0x0000ffff,
पूर्ण;

/* MPR */
क्रमागत MPR_BIT अणु
	MPR_MP = 0x0000ffff,
पूर्ण;

/* TRSCER */
क्रमागत TRSCER_BIT अणु
	TRSCER_CNDCE	= 0x00000800,
	TRSCER_DLCCE	= 0x00000400,
	TRSCER_CDCE	= 0x00000200,
	TRSCER_TROCE	= 0x00000100,
	TRSCER_RMAFCE	= 0x00000080,
	TRSCER_RRFCE	= 0x00000010,
	TRSCER_RTLFCE	= 0x00000008,
	TRSCER_RTSFCE	= 0x00000004,
	TRSCER_PRECE	= 0x00000002,
	TRSCER_CERFCE	= 0x00000001,
पूर्ण;

#घोषणा DEFAULT_TRSCER_ERR_MASK (TRSCER_RMAFCE | TRSCER_RRFCE | TRSCER_CDCE)

/* RPAसूची */
क्रमागत RPAसूची_BIT अणु
	RPAसूची_PADS = 0x1f0000, RPAसूची_PADR = 0xffff,
पूर्ण;

/* FDR */
#घोषणा DEFAULT_FDR_INIT	0x00000707

/* ARSTR */
क्रमागत ARSTR_BIT अणु ARSTR_ARST = 0x00000001, पूर्ण;

/* TSU_FWEN0 */
क्रमागत TSU_FWEN0_BIT अणु
	TSU_FWEN0_0 = 0x00000001,
पूर्ण;

/* TSU_ADSBSY */
क्रमागत TSU_ADSBSY_BIT अणु
	TSU_ADSBSY_0 = 0x00000001,
पूर्ण;

/* TSU_TEN */
क्रमागत TSU_TEN_BIT अणु
	TSU_TEN_0 = 0x80000000,
पूर्ण;

/* TSU_FWSL0 */
क्रमागत TSU_FWSL0_BIT अणु
	TSU_FWSL0_FW50 = 0x1000, TSU_FWSL0_FW40 = 0x0800,
	TSU_FWSL0_FW30 = 0x0400, TSU_FWSL0_FW20 = 0x0200,
	TSU_FWSL0_FW10 = 0x0100, TSU_FWSL0_RMSA0 = 0x0010,
पूर्ण;

/* TSU_FWSLC */
क्रमागत TSU_FWSLC_BIT अणु
	TSU_FWSLC_POSTENU = 0x2000, TSU_FWSLC_POSTENL = 0x1000,
	TSU_FWSLC_CAMSEL03 = 0x0080, TSU_FWSLC_CAMSEL02 = 0x0040,
	TSU_FWSLC_CAMSEL01 = 0x0020, TSU_FWSLC_CAMSEL00 = 0x0010,
	TSU_FWSLC_CAMSEL13 = 0x0008, TSU_FWSLC_CAMSEL12 = 0x0004,
	TSU_FWSLC_CAMSEL11 = 0x0002, TSU_FWSLC_CAMSEL10 = 0x0001,
पूर्ण;

/* TSU_VTAGn */
#घोषणा TSU_VTAG_ENABLE		0x80000000
#घोषणा TSU_VTAG_VID_MASK	0x00000fff

/* The sh ether Tx buffer descriptors.
 * This काष्ठाure should be 20 bytes.
 */
काष्ठा sh_eth_txdesc अणु
	u32 status;		/* TD0 */
	u32 len;		/* TD1 */
	u32 addr;		/* TD2 */
	u32 pad0;		/* padding data */
पूर्ण __aligned(2) __packed;

/* Transmit descriptor 0 bits */
क्रमागत TD_STS_BIT अणु
	TD_TACT	= 0x80000000,
	TD_TDLE	= 0x40000000,
	TD_TFP1	= 0x20000000,
	TD_TFP0	= 0x10000000,
	TD_TFE	= 0x08000000,
	TD_TWBI	= 0x04000000,
पूर्ण;
#घोषणा TDF1ST	TD_TFP1
#घोषणा TDFEND	TD_TFP0
#घोषणा TD_TFP	(TD_TFP1 | TD_TFP0)

/* Transmit descriptor 1 bits */
क्रमागत TD_LEN_BIT अणु
	TD_TBL	= 0xffff0000,	/* transmit buffer length */
पूर्ण;

/* The sh ether Rx buffer descriptors.
 * This काष्ठाure should be 20 bytes.
 */
काष्ठा sh_eth_rxdesc अणु
	u32 status;		/* RD0 */
	u32 len;		/* RD1 */
	u32 addr;		/* RD2 */
	u32 pad0;		/* padding data */
पूर्ण __aligned(2) __packed;

/* Receive descriptor 0 bits */
क्रमागत RD_STS_BIT अणु
	RD_RACT	= 0x80000000,
	RD_RDLE	= 0x40000000,
	RD_RFP1	= 0x20000000,
	RD_RFP0	= 0x10000000,
	RD_RFE	= 0x08000000,
	RD_RFS10 = 0x00000200,
	RD_RFS9	= 0x00000100,
	RD_RFS8	= 0x00000080,
	RD_RFS7	= 0x00000040,
	RD_RFS6	= 0x00000020,
	RD_RFS5	= 0x00000010,
	RD_RFS4	= 0x00000008,
	RD_RFS3	= 0x00000004,
	RD_RFS2	= 0x00000002,
	RD_RFS1	= 0x00000001,
पूर्ण;
#घोषणा RDF1ST	RD_RFP1
#घोषणा RDFEND	RD_RFP0
#घोषणा RD_RFP	(RD_RFP1 | RD_RFP0)

/* Receive descriptor 1 bits */
क्रमागत RD_LEN_BIT अणु
	RD_RFL	= 0x0000ffff,	/* receive frame  length */
	RD_RBL	= 0xffff0000,	/* receive buffer length */
पूर्ण;

/* This काष्ठाure is used by each CPU dependency handling. */
काष्ठा sh_eth_cpu_data अणु
	/* mandatory functions */
	पूर्णांक (*soft_reset)(काष्ठा net_device *ndev);

	/* optional functions */
	व्योम (*chip_reset)(काष्ठा net_device *ndev);
	व्योम (*set_duplex)(काष्ठा net_device *ndev);
	व्योम (*set_rate)(काष्ठा net_device *ndev);

	/* mandatory initialize value */
	पूर्णांक रेजिस्टर_type;
	u32 edtrr_trns;
	u32 eesipr_value;

	/* optional initialize value */
	u32 ecsr_value;
	u32 ecsipr_value;
	u32 fdr_value;
	u32 fcftr_value;

	/* पूर्णांकerrupt checking mask */
	u32 tx_check;
	u32 eesr_err_check;

	/* Error mask */
	u32 trscer_err_mask;

	/* hardware features */
	अचिन्हित दीर्घ irq_flags; /* IRQ configuration flags */
	अचिन्हित no_psr:1;	/* EtherC DOES NOT have PSR */
	अचिन्हित apr:1;		/* EtherC has APR */
	अचिन्हित mpr:1;		/* EtherC has MPR */
	अचिन्हित tछोड़ोr:1;	/* EtherC has TPAUSER */
	अचिन्हित gecmr:1;	/* EtherC has GECMR */
	अचिन्हित bculr:1;	/* EtherC has BCULR */
	अचिन्हित tsu:1;		/* EtherC has TSU */
	अचिन्हित hw_swap:1;	/* E-DMAC has DE bit in EDMR */
	अचिन्हित nbst:1;	/* E-DMAC has NBST bit in EDMR */
	अचिन्हित rpadir:1;	/* E-DMAC has RPAसूची */
	अचिन्हित no_trimd:1;	/* E-DMAC DOES NOT have TRIMD */
	अचिन्हित no_ade:1;	/* E-DMAC DOES NOT have ADE bit in EESR */
	अचिन्हित no_xdfar:1;	/* E-DMAC DOES NOT have RDFAR/TDFAR */
	अचिन्हित xdfar_rw:1;	/* E-DMAC has ग_लिखोable RDFAR/TDFAR */
	अचिन्हित csmr:1;	/* E-DMAC has CSMR */
	अचिन्हित rx_csum:1;	/* EtherC has ECMR.RCSC */
	अचिन्हित select_mii:1;	/* EtherC has RMII_MII (MII select रेजिस्टर) */
	अचिन्हित rmiimode:1;	/* EtherC has RMIIMODE रेजिस्टर */
	अचिन्हित rtrate:1;	/* EtherC has RTRATE रेजिस्टर */
	अचिन्हित magic:1;	/* EtherC has ECMR.MPDE and ECSR.MPD */
	अचिन्हित no_tx_cntrs:1;	/* EtherC DOES NOT have TX error counters */
	अचिन्हित cexcr:1;	/* EtherC has CERCR/CEECR */
	अचिन्हित dual_port:1;	/* Dual EtherC/E-DMAC */
पूर्ण;

काष्ठा sh_eth_निजी अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा sh_eth_cpu_data *cd;
	स्थिर u16 *reg_offset;
	व्योम __iomem *addr;
	व्योम __iomem *tsu_addr;
	काष्ठा clk *clk;
	u32 num_rx_ring;
	u32 num_tx_ring;
	dma_addr_t rx_desc_dma;
	dma_addr_t tx_desc_dma;
	काष्ठा sh_eth_rxdesc *rx_ring;
	काष्ठा sh_eth_txdesc *tx_ring;
	काष्ठा sk_buff **rx_skbuff;
	काष्ठा sk_buff **tx_skbuff;
	spinlock_t lock;		/* Register access lock */
	u32 cur_rx, dirty_rx;		/* Producer/consumer ring indices */
	u32 cur_tx, dirty_tx;
	u32 rx_buf_sz;			/* Based on MTU+slack. */
	काष्ठा napi_काष्ठा napi;
	bool irq_enabled;
	/* MII transceiver section. */
	u32 phy_id;			/* PHY ID */
	काष्ठा mii_bus *mii_bus;	/* MDIO bus control */
	पूर्णांक link;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	पूर्णांक msg_enable;
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक port;			/* क्रम TSU */
	पूर्णांक vlan_num_ids;		/* क्रम VLAN tag filter */

	अचिन्हित no_ether_link:1;
	अचिन्हित ether_link_active_low:1;
	अचिन्हित is_खोलोed:1;
	अचिन्हित wol_enabled:1;
पूर्ण;

#पूर्ण_अगर	/* #अगर_अघोषित __SH_ETH_H__ */
