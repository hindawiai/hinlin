<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Tsi721 PCIExpress-to-SRIO bridge definitions
 *
 * Copyright 2011, Integrated Device Technology, Inc.
 */

#अगर_अघोषित __TSI721_H
#घोषणा __TSI721_H

/* Debug output filtering masks */
क्रमागत अणु
	DBG_NONE	= 0,
	DBG_INIT	= BIT(0), /* driver init */
	DBG_EXIT	= BIT(1), /* driver निकास */
	DBG_MPORT	= BIT(2), /* mport add/हटाओ */
	DBG_MAINT	= BIT(3), /* मुख्यtenance ops messages */
	DBG_DMA		= BIT(4), /* DMA transfer messages */
	DBG_DMAV	= BIT(5), /* verbose DMA transfer messages */
	DBG_IBW		= BIT(6), /* inbound winकरोw */
	DBG_EVENT	= BIT(7), /* event handling messages */
	DBG_OBW		= BIT(8), /* outbound winकरोw messages */
	DBG_DBELL	= BIT(9), /* करोorbell messages */
	DBG_OMSG	= BIT(10), /* करोorbell messages */
	DBG_IMSG	= BIT(11), /* करोorbell messages */
	DBG_ALL		= ~0,
पूर्ण;

#अगर_घोषित DEBUG
बाह्य u32 tsi_dbg_level;

#घोषणा tsi_debug(level, dev, fmt, arg...)				\
	करो अणु								\
		अगर (DBG_##level & tsi_dbg_level)				\
			dev_dbg(dev, "%s: " fmt "\n", __func__, ##arg);	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा tsi_debug(level, dev, fmt, arg...) \
		no_prपूर्णांकk(KERN_DEBUG "%s: " fmt "\n", __func__, ##arg)
#पूर्ण_अगर

#घोषणा tsi_info(dev, fmt, arg...) \
	dev_info(dev, "%s: " fmt "\n", __func__, ##arg)

#घोषणा tsi_warn(dev, fmt, arg...) \
	dev_warn(dev, "%s: WARNING " fmt "\n", __func__, ##arg)

#घोषणा tsi_err(dev, fmt, arg...) \
	dev_err(dev, "%s: ERROR " fmt "\n", __func__, ##arg)

#घोषणा DRV_NAME	"tsi721"

#घोषणा DEFAULT_HOPCOUNT	0xff
#घोषणा DEFAULT_DESTID		0xff

/* PCI device ID */
#घोषणा PCI_DEVICE_ID_TSI721		0x80ab

#घोषणा BAR_0	0
#घोषणा BAR_1	1
#घोषणा BAR_2	2
#घोषणा BAR_4	4

#घोषणा TSI721_PC2SR_BARS	2
#घोषणा TSI721_PC2SR_WINS	8
#घोषणा TSI721_PC2SR_ZONES	8
#घोषणा TSI721_MAINT_WIN	0 /* Winकरोw क्रम outbound मुख्यtenance requests */
#घोषणा IDB_QUEUE		0 /* Inbound Doorbell Queue to use */
#घोषणा IDB_QSIZE		512 /* Inbound Doorbell Queue size */

/* Memory space sizes */
#घोषणा TSI721_REG_SPACE_SIZE		(512 * 1024) /* 512K */
#घोषणा TSI721_DB_WIN_SIZE		(16 * 1024 * 1024) /* 16MB */

#घोषणा  RIO_TT_CODE_8		0x00000000
#घोषणा  RIO_TT_CODE_16		0x00000001

#घोषणा TSI721_DMA_MAXCH	8
#घोषणा TSI721_DMA_MINSTSSZ	32
#घोषणा TSI721_DMA_STSBLKSZ	8

#घोषणा TSI721_SRIO_MAXCH	8

#घोषणा DBELL_SID(buf)		(((u8)buf[2] << 8) | (u8)buf[3])
#घोषणा DBELL_TID(buf)		(((u8)buf[4] << 8) | (u8)buf[5])
#घोषणा DBELL_INF(buf)		(((u8)buf[0] << 8) | (u8)buf[1])

#घोषणा TSI721_RIO_PW_MSG_SIZE	16  /* Tsi721 saves only 16 bytes of PW msg */

/* Register definitions */

/*
 * Registers in PCIe configuration space
 */

#घोषणा TSI721_PCIECFG_MSIXTBL	0x0a4
#घोषणा TSI721_MSIXTBL_OFFSET	0x2c000
#घोषणा TSI721_PCIECFG_MSIXPBA	0x0a8
#घोषणा TSI721_MSIXPBA_OFFSET	0x2a000
#घोषणा TSI721_PCIECFG_EPCTL	0x400

/*
 * Event Management Registers
 */

#घोषणा TSI721_RIO_EM_INT_STAT		0x10910
#घोषणा TSI721_RIO_EM_INT_STAT_PW_RX	0x00010000

#घोषणा TSI721_RIO_EM_INT_ENABLE	0x10914
#घोषणा TSI721_RIO_EM_INT_ENABLE_PW_RX	0x00010000

#घोषणा TSI721_RIO_EM_DEV_INT_EN	0x10930
#घोषणा TSI721_RIO_EM_DEV_INT_EN_INT	0x00000001

/*
 * Port-Write Block Registers
 */

#घोषणा TSI721_RIO_PW_CTL		0x10a04
#घोषणा TSI721_RIO_PW_CTL_PW_TIMER	0xf0000000
#घोषणा TSI721_RIO_PW_CTL_PWT_DIS	(0 << 28)
#घोषणा TSI721_RIO_PW_CTL_PWT_103	(1 << 28)
#घोषणा TSI721_RIO_PW_CTL_PWT_205	(1 << 29)
#घोषणा TSI721_RIO_PW_CTL_PWT_410	(1 << 30)
#घोषणा TSI721_RIO_PW_CTL_PWT_820	(1 << 31)
#घोषणा TSI721_RIO_PW_CTL_PWC_MODE	0x01000000
#घोषणा TSI721_RIO_PW_CTL_PWC_CONT	0x00000000
#घोषणा TSI721_RIO_PW_CTL_PWC_REL	0x01000000

#घोषणा TSI721_RIO_PW_RX_STAT		0x10a10
#घोषणा TSI721_RIO_PW_RX_STAT_WR_SIZE	0x0000f000
#घोषणा TSI_RIO_PW_RX_STAT_WDPTR	0x00000100
#घोषणा TSI721_RIO_PW_RX_STAT_PW_SHORT	0x00000008
#घोषणा TSI721_RIO_PW_RX_STAT_PW_TRUNC	0x00000004
#घोषणा TSI721_RIO_PW_RX_STAT_PW_DISC	0x00000002
#घोषणा TSI721_RIO_PW_RX_STAT_PW_VAL	0x00000001

#घोषणा TSI721_RIO_PW_RX_CAPT(x)	(0x10a20 + (x)*4)

/*
 * Inbound Doorbells
 */

#घोषणा TSI721_IDB_ENTRY_SIZE	64

#घोषणा TSI721_IDQ_CTL(x)	(0x20000 + (x) * 0x1000)
#घोषणा TSI721_IDQ_SUSPEND	0x00000002
#घोषणा TSI721_IDQ_INIT		0x00000001

#घोषणा TSI721_IDQ_STS(x)	(0x20004 + (x) * 0x1000)
#घोषणा TSI721_IDQ_RUN		0x00200000

#घोषणा TSI721_IDQ_MASK(x)	(0x20008 + (x) * 0x1000)
#घोषणा TSI721_IDQ_MASK_MASK	0xffff0000
#घोषणा TSI721_IDQ_MASK_PATT	0x0000ffff

#घोषणा TSI721_IDQ_RP(x)	(0x2000c + (x) * 0x1000)
#घोषणा TSI721_IDQ_RP_PTR	0x0007ffff

#घोषणा TSI721_IDQ_WP(x)	(0x20010 + (x) * 0x1000)
#घोषणा TSI721_IDQ_WP_PTR	0x0007ffff

#घोषणा TSI721_IDQ_BASEL(x)	(0x20014 + (x) * 0x1000)
#घोषणा TSI721_IDQ_BASEL_ADDR	0xffffffc0
#घोषणा TSI721_IDQ_BASEU(x)	(0x20018 + (x) * 0x1000)
#घोषणा TSI721_IDQ_SIZE(x)	(0x2001c + (x) * 0x1000)
#घोषणा TSI721_IDQ_SIZE_VAL(size)	(__fls(size) - 4)
#घोषणा TSI721_IDQ_SIZE_MIN	512
#घोषणा TSI721_IDQ_SIZE_MAX	(512 * 1024)

#घोषणा TSI721_SR_CHINT(x)	(0x20040 + (x) * 0x1000)
#घोषणा TSI721_SR_CHINTE(x)	(0x20044 + (x) * 0x1000)
#घोषणा TSI721_SR_CHINTSET(x)	(0x20048 + (x) * 0x1000)
#घोषणा TSI721_SR_CHINT_ODBOK	0x00000020
#घोषणा TSI721_SR_CHINT_IDBQRCV	0x00000010
#घोषणा TSI721_SR_CHINT_SUSP	0x00000008
#घोषणा TSI721_SR_CHINT_ODBTO	0x00000004
#घोषणा TSI721_SR_CHINT_ODBRTRY	0x00000002
#घोषणा TSI721_SR_CHINT_ODBERR	0x00000001
#घोषणा TSI721_SR_CHINT_ALL	0x0000003f

#घोषणा TSI721_IBWIN_NUM	8

#घोषणा TSI721_IBWIN_LB(x)	(0x29000 + (x) * 0x20)
#घोषणा TSI721_IBWIN_LB_BA	0xfffff000
#घोषणा TSI721_IBWIN_LB_WEN	0x00000001

#घोषणा TSI721_IBWIN_UB(x)	(0x29004 + (x) * 0x20)
#घोषणा TSI721_IBWIN_SZ(x)	(0x29008 + (x) * 0x20)
#घोषणा TSI721_IBWIN_SZ_SIZE	0x00001f00
#घोषणा TSI721_IBWIN_SIZE(size)	(__fls(size) - 12)

#घोषणा TSI721_IBWIN_TLA(x)	(0x2900c + (x) * 0x20)
#घोषणा TSI721_IBWIN_TLA_ADD	0xfffff000
#घोषणा TSI721_IBWIN_TUA(x)	(0x29010 + (x) * 0x20)

#घोषणा TSI721_SR2PC_GEN_INTE	0x29800
#घोषणा TSI721_SR2PC_PWE	0x29804
#घोषणा TSI721_SR2PC_GEN_INT	0x29808

#घोषणा TSI721_DEV_INTE		0x29840
#घोषणा TSI721_DEV_INT		0x29844
#घोषणा TSI721_DEV_INTSET	0x29848
#घोषणा TSI721_DEV_INT_BDMA_CH	0x00002000
#घोषणा TSI721_DEV_INT_BDMA_NCH	0x00001000
#घोषणा TSI721_DEV_INT_SMSG_CH	0x00000800
#घोषणा TSI721_DEV_INT_SMSG_NCH	0x00000400
#घोषणा TSI721_DEV_INT_SR2PC_CH	0x00000200
#घोषणा TSI721_DEV_INT_SRIO	0x00000020

#घोषणा TSI721_DEV_CHAN_INTE	0x2984c
#घोषणा TSI721_DEV_CHAN_INT	0x29850

#घोषणा TSI721_INT_SR2PC_CHAN_M	0xff000000
#घोषणा TSI721_INT_SR2PC_CHAN(x) (1 << (24 + (x)))
#घोषणा TSI721_INT_IMSG_CHAN_M	0x00ff0000
#घोषणा TSI721_INT_IMSG_CHAN(x)	(1 << (16 + (x)))
#घोषणा TSI721_INT_OMSG_CHAN_M	0x0000ff00
#घोषणा TSI721_INT_OMSG_CHAN(x)	(1 << (8 + (x)))
#घोषणा TSI721_INT_BDMA_CHAN_M	0x000000ff
#घोषणा TSI721_INT_BDMA_CHAN(x)	(1 << (x))

/*
 * PC2SR block रेजिस्टरs
 */
#घोषणा TSI721_OBWIN_NUM	TSI721_PC2SR_WINS

#घोषणा TSI721_OBWINLB(x)	(0x40000 + (x) * 0x20)
#घोषणा TSI721_OBWINLB_BA	0xffff8000
#घोषणा TSI721_OBWINLB_WEN	0x00000001

#घोषणा TSI721_OBWINUB(x)	(0x40004 + (x) * 0x20)

#घोषणा TSI721_OBWINSZ(x)	(0x40008 + (x) * 0x20)
#घोषणा TSI721_OBWINSZ_SIZE	0x00001f00
#घोषणा TSI721_OBWIN_SIZE(size)	(__fls(size) - 15)

#घोषणा TSI721_ZONE_SEL		0x41300
#घोषणा TSI721_ZONE_SEL_RD_WRB	0x00020000
#घोषणा TSI721_ZONE_SEL_GO	0x00010000
#घोषणा TSI721_ZONE_SEL_WIN	0x00000038
#घोषणा TSI721_ZONE_SEL_ZONE	0x00000007

#घोषणा TSI721_LUT_DATA0	0x41304
#घोषणा TSI721_LUT_DATA0_ADD	0xfffff000
#घोषणा TSI721_LUT_DATA0_RDTYPE	0x00000f00
#घोषणा TSI721_LUT_DATA0_NREAD	0x00000100
#घोषणा TSI721_LUT_DATA0_MNTRD	0x00000200
#घोषणा TSI721_LUT_DATA0_RDCRF	0x00000020
#घोषणा TSI721_LUT_DATA0_WRCRF	0x00000010
#घोषणा TSI721_LUT_DATA0_WRTYPE	0x0000000f
#घोषणा TSI721_LUT_DATA0_NWR	0x00000001
#घोषणा TSI721_LUT_DATA0_MNTWR	0x00000002
#घोषणा TSI721_LUT_DATA0_NWR_R	0x00000004

#घोषणा TSI721_LUT_DATA1	0x41308

#घोषणा TSI721_LUT_DATA2	0x4130c
#घोषणा TSI721_LUT_DATA2_HC	0xff000000
#घोषणा TSI721_LUT_DATA2_ADD65	0x000c0000
#घोषणा TSI721_LUT_DATA2_TT	0x00030000
#घोषणा TSI721_LUT_DATA2_DSTID	0x0000ffff

#घोषणा TSI721_PC2SR_INTE	0x41310

#घोषणा TSI721_DEVCTL		0x48004
#घोषणा TSI721_DEVCTL_SRBOOT_CMPL	0x00000004

#घोषणा TSI721_I2C_INT_ENABLE	0x49120

/*
 * Block DMA Engine Registers
 *   x = 0..7
 */

#घोषणा TSI721_DMAC_BASE(x)	(0x51000 + (x) * 0x1000)

#घोषणा TSI721_DMAC_DWRCNT	0x000
#घोषणा TSI721_DMAC_DRDCNT	0x004

#घोषणा TSI721_DMAC_CTL		0x008
#घोषणा TSI721_DMAC_CTL_SUSP	0x00000002
#घोषणा TSI721_DMAC_CTL_INIT	0x00000001

#घोषणा TSI721_DMAC_INT		0x00c
#घोषणा TSI721_DMAC_INT_STFULL	0x00000010
#घोषणा TSI721_DMAC_INT_DONE	0x00000008
#घोषणा TSI721_DMAC_INT_SUSP	0x00000004
#घोषणा TSI721_DMAC_INT_ERR	0x00000002
#घोषणा TSI721_DMAC_INT_IOFDONE	0x00000001
#घोषणा TSI721_DMAC_INT_ALL	0x0000001f

#घोषणा TSI721_DMAC_INTSET	0x010

#घोषणा TSI721_DMAC_STS		0x014
#घोषणा TSI721_DMAC_STS_ABORT	0x00400000
#घोषणा TSI721_DMAC_STS_RUN	0x00200000
#घोषणा TSI721_DMAC_STS_CS	0x001f0000

#घोषणा TSI721_DMAC_INTE	0x018

#घोषणा TSI721_DMAC_DPTRL	0x024
#घोषणा TSI721_DMAC_DPTRL_MASK	0xffffffe0

#घोषणा TSI721_DMAC_DPTRH	0x028

#घोषणा TSI721_DMAC_DSBL	0x02c
#घोषणा TSI721_DMAC_DSBL_MASK	0xffffffc0

#घोषणा TSI721_DMAC_DSBH	0x030

#घोषणा TSI721_DMAC_DSSZ	0x034
#घोषणा TSI721_DMAC_DSSZ_SIZE_M	0x0000000f
#घोषणा TSI721_DMAC_DSSZ_SIZE(size)	(__fls(size) - 4)

#घोषणा TSI721_DMAC_DSRP	0x038
#घोषणा TSI721_DMAC_DSRP_MASK	0x0007ffff

#घोषणा TSI721_DMAC_DSWP	0x03c
#घोषणा TSI721_DMAC_DSWP_MASK	0x0007ffff

#घोषणा TSI721_BDMA_INTE	0x5f000

/*
 * Messaging definitions
 */
#घोषणा TSI721_MSG_BUFFER_SIZE		RIO_MAX_MSG_SIZE
#घोषणा TSI721_MSG_MAX_SIZE		RIO_MAX_MSG_SIZE
#घोषणा TSI721_IMSG_MAXCH		8
#घोषणा TSI721_IMSG_CHNUM		TSI721_IMSG_MAXCH
#घोषणा TSI721_IMSGD_MIN_RING_SIZE	32
#घोषणा TSI721_IMSGD_RING_SIZE		512

#घोषणा TSI721_OMSG_CHNUM		4 /* One channel per MBOX */
#घोषणा TSI721_OMSGD_MIN_RING_SIZE	32
#घोषणा TSI721_OMSGD_RING_SIZE		512

/*
 * Outbound Messaging Engine Registers
 *   x = 0..7
 */

#घोषणा TSI721_OBDMAC_DWRCNT(x)		(0x61000 + (x) * 0x1000)

#घोषणा TSI721_OBDMAC_DRDCNT(x)		(0x61004 + (x) * 0x1000)

#घोषणा TSI721_OBDMAC_CTL(x)		(0x61008 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_CTL_MASK		0x00000007
#घोषणा TSI721_OBDMAC_CTL_RETRY_THR	0x00000004
#घोषणा TSI721_OBDMAC_CTL_SUSPEND	0x00000002
#घोषणा TSI721_OBDMAC_CTL_INIT		0x00000001

#घोषणा TSI721_OBDMAC_INT(x)		(0x6100c + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_INTSET(x)		(0x61010 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_INTE(x)		(0x61018 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_INT_MASK		0x0000001F
#घोषणा TSI721_OBDMAC_INT_ST_FULL	0x00000010
#घोषणा TSI721_OBDMAC_INT_DONE		0x00000008
#घोषणा TSI721_OBDMAC_INT_SUSPENDED	0x00000004
#घोषणा TSI721_OBDMAC_INT_ERROR		0x00000002
#घोषणा TSI721_OBDMAC_INT_IOF_DONE	0x00000001
#घोषणा TSI721_OBDMAC_INT_ALL		TSI721_OBDMAC_INT_MASK

#घोषणा TSI721_OBDMAC_STS(x)		(0x61014 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_STS_MASK		0x007f0000
#घोषणा TSI721_OBDMAC_STS_ABORT		0x00400000
#घोषणा TSI721_OBDMAC_STS_RUN		0x00200000
#घोषणा TSI721_OBDMAC_STS_CS		0x001f0000

#घोषणा TSI721_OBDMAC_PWE(x)		(0x6101c + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_PWE_MASK		0x00000002
#घोषणा TSI721_OBDMAC_PWE_ERROR_EN	0x00000002

#घोषणा TSI721_OBDMAC_DPTRL(x)		(0x61020 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_DPTRL_MASK	0xfffffff0

#घोषणा TSI721_OBDMAC_DPTRH(x)		(0x61024 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_DPTRH_MASK	0xffffffff

#घोषणा TSI721_OBDMAC_DSBL(x)		(0x61040 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_DSBL_MASK		0xffffffc0

#घोषणा TSI721_OBDMAC_DSBH(x)		(0x61044 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_DSBH_MASK		0xffffffff

#घोषणा TSI721_OBDMAC_DSSZ(x)		(0x61048 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_DSSZ_MASK		0x0000000f

#घोषणा TSI721_OBDMAC_DSRP(x)		(0x6104c + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_DSRP_MASK		0x0007ffff

#घोषणा TSI721_OBDMAC_DSWP(x)		(0x61050 + (x) * 0x1000)
#घोषणा TSI721_OBDMAC_DSWP_MASK		0x0007ffff

#घोषणा TSI721_RQRPTO			0x60010
#घोषणा TSI721_RQRPTO_MASK		0x00ffffff
#घोषणा TSI721_RQRPTO_VAL		400	/* Response TO value */

/*
 * Inbound Messaging Engine Registers
 *   x = 0..7
 */

#घोषणा TSI721_IB_DEVID_GLOBAL		0xffff
#घोषणा TSI721_IBDMAC_FQBL(x)		(0x61200 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_FQBL_MASK		0xffffffc0

#घोषणा TSI721_IBDMAC_FQBH(x)		(0x61204 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_FQBH_MASK		0xffffffff

#घोषणा TSI721_IBDMAC_FQSZ_ENTRY_INX	TSI721_IMSGD_RING_SIZE
#घोषणा TSI721_IBDMAC_FQSZ(x)		(0x61208 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_FQSZ_MASK		0x0000000f

#घोषणा TSI721_IBDMAC_FQRP(x)		(0x6120c + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_FQRP_MASK		0x0007ffff

#घोषणा TSI721_IBDMAC_FQWP(x)		(0x61210 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_FQWP_MASK		0x0007ffff

#घोषणा TSI721_IBDMAC_FQTH(x)		(0x61214 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_FQTH_MASK		0x0007ffff

#घोषणा TSI721_IB_DEVID			0x60020
#घोषणा TSI721_IB_DEVID_MASK		0x0000ffff

#घोषणा TSI721_IBDMAC_CTL(x)		(0x61240 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_CTL_MASK		0x00000003
#घोषणा TSI721_IBDMAC_CTL_SUSPEND	0x00000002
#घोषणा TSI721_IBDMAC_CTL_INIT		0x00000001

#घोषणा TSI721_IBDMAC_STS(x)		(0x61244 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_STS_MASK		0x007f0000
#घोषणा TSI721_IBSMAC_STS_ABORT		0x00400000
#घोषणा TSI721_IBSMAC_STS_RUN		0x00200000
#घोषणा TSI721_IBSMAC_STS_CS		0x001f0000

#घोषणा TSI721_IBDMAC_INT(x)		(0x61248 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_INTSET(x)		(0x6124c + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_INTE(x)		(0x61250 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_INT_MASK		0x0000100f
#घोषणा TSI721_IBDMAC_INT_SRTO		0x00001000
#घोषणा TSI721_IBDMAC_INT_SUSPENDED	0x00000008
#घोषणा TSI721_IBDMAC_INT_PC_ERROR	0x00000004
#घोषणा TSI721_IBDMAC_INT_FQ_LOW	0x00000002
#घोषणा TSI721_IBDMAC_INT_DQ_RCV	0x00000001
#घोषणा TSI721_IBDMAC_INT_ALL		TSI721_IBDMAC_INT_MASK

#घोषणा TSI721_IBDMAC_PWE(x)		(0x61254 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_PWE_MASK		0x00001700
#घोषणा TSI721_IBDMAC_PWE_SRTO		0x00001000
#घोषणा TSI721_IBDMAC_PWE_ILL_FMT	0x00000400
#घोषणा TSI721_IBDMAC_PWE_ILL_DEC	0x00000200
#घोषणा TSI721_IBDMAC_PWE_IMP_SP	0x00000100

#घोषणा TSI721_IBDMAC_DQBL(x)		(0x61300 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_DQBL_MASK		0xffffffc0
#घोषणा TSI721_IBDMAC_DQBL_ADDR		0xffffffc0

#घोषणा TSI721_IBDMAC_DQBH(x)		(0x61304 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_DQBH_MASK		0xffffffff

#घोषणा TSI721_IBDMAC_DQRP(x)		(0x61308 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_DQRP_MASK		0x0007ffff

#घोषणा TSI721_IBDMAC_DQWR(x)		(0x6130c + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_DQWR_MASK		0x0007ffff

#घोषणा TSI721_IBDMAC_DQSZ(x)		(0x61314 + (x) * 0x1000)
#घोषणा TSI721_IBDMAC_DQSZ_MASK		0x0000000f

/*
 * Messaging Engine Interrupts
 */

#घोषणा TSI721_SMSG_PWE			0x6a004

#घोषणा TSI721_SMSG_INTE		0x6a000
#घोषणा TSI721_SMSG_INT			0x6a008
#घोषणा TSI721_SMSG_INTSET		0x6a010
#घोषणा TSI721_SMSG_INT_MASK		0x0086ffff
#घोषणा TSI721_SMSG_INT_UNS_RSP		0x00800000
#घोषणा TSI721_SMSG_INT_ECC_NCOR	0x00040000
#घोषणा TSI721_SMSG_INT_ECC_COR		0x00020000
#घोषणा TSI721_SMSG_INT_ECC_NCOR_CH	0x0000ff00
#घोषणा TSI721_SMSG_INT_ECC_COR_CH	0x000000ff

#घोषणा TSI721_SMSG_ECC_LOG		0x6a014
#घोषणा TSI721_SMSG_ECC_LOG_MASK	0x00070007
#घोषणा TSI721_SMSG_ECC_LOG_ECC_NCOR_M	0x00070000
#घोषणा TSI721_SMSG_ECC_LOG_ECC_COR_M	0x00000007

#घोषणा TSI721_RETRY_GEN_CNT		0x6a100
#घोषणा TSI721_RETRY_GEN_CNT_MASK	0xffffffff

#घोषणा TSI721_RETRY_RX_CNT		0x6a104
#घोषणा TSI721_RETRY_RX_CNT_MASK	0xffffffff

#घोषणा TSI721_SMSG_ECC_COR_LOG(x)	(0x6a300 + (x) * 4)
#घोषणा TSI721_SMSG_ECC_COR_LOG_MASK	0x000000ff

#घोषणा TSI721_SMSG_ECC_NCOR(x)		(0x6a340 + (x) * 4)
#घोषणा TSI721_SMSG_ECC_NCOR_MASK	0x000000ff

/*
 * Block DMA Descriptors
 */

काष्ठा tsi721_dma_desc अणु
	__le32 type_id;

#घोषणा TSI721_DMAD_DEVID	0x0000ffff
#घोषणा TSI721_DMAD_CRF		0x00010000
#घोषणा TSI721_DMAD_PRIO	0x00060000
#घोषणा TSI721_DMAD_RTYPE	0x00780000
#घोषणा TSI721_DMAD_IOF		0x08000000
#घोषणा TSI721_DMAD_DTYPE	0xe0000000

	__le32 bcount;

#घोषणा TSI721_DMAD_BCOUNT1	0x03ffffff /* अगर DTYPE == 1 */
#घोषणा TSI721_DMAD_BCOUNT2	0x0000000f /* अगर DTYPE == 2 */
#घोषणा TSI721_DMAD_TT		0x0c000000
#घोषणा TSI721_DMAD_RADDR0	0xc0000000

	जोड़ अणु
		__le32 raddr_lo;	   /* अगर DTYPE == (1 || 2) */
		__le32 next_lo;		   /* अगर DTYPE == 3 */
	पूर्ण;

#घोषणा TSI721_DMAD_CFGOFF	0x00ffffff
#घोषणा TSI721_DMAD_HOPCNT	0xff000000

	जोड़ अणु
		__le32 raddr_hi;	   /* अगर DTYPE == (1 || 2) */
		__le32 next_hi;		   /* अगर DTYPE == 3 */
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु		   /* अगर DTYPE == 1 */
			__le32 bufptr_lo;
			__le32 bufptr_hi;
			__le32 s_dist;
			__le32 s_size;
		पूर्ण t1;
		__le32 data[4];		   /* अगर DTYPE == 2 */
		u32    reserved[4];	   /* अगर DTYPE == 3 */
	पूर्ण;
पूर्ण __aligned(32);

/*
 * Inbound Messaging Descriptor
 */
काष्ठा tsi721_imsg_desc अणु
	__le32 type_id;

#घोषणा TSI721_IMD_DEVID	0x0000ffff
#घोषणा TSI721_IMD_CRF		0x00010000
#घोषणा TSI721_IMD_PRIO		0x00060000
#घोषणा TSI721_IMD_TT		0x00180000
#घोषणा TSI721_IMD_DTYPE	0xe0000000

	__le32 msg_info;

#घोषणा TSI721_IMD_BCOUNT	0x00000ff8
#घोषणा TSI721_IMD_SSIZE	0x0000f000
#घोषणा TSI721_IMD_LETER	0x00030000
#घोषणा TSI721_IMD_XMBOX	0x003c0000
#घोषणा TSI721_IMD_MBOX		0x00c00000
#घोषणा TSI721_IMD_CS		0x78000000
#घोषणा TSI721_IMD_HO		0x80000000

	__le32 bufptr_lo;
	__le32 bufptr_hi;
	u32    reserved[12];

पूर्ण __aligned(64);

/*
 * Outbound Messaging Descriptor
 */
काष्ठा tsi721_omsg_desc अणु
	__le32 type_id;

#घोषणा TSI721_OMD_DEVID	0x0000ffff
#घोषणा TSI721_OMD_CRF		0x00010000
#घोषणा TSI721_OMD_PRIO		0x00060000
#घोषणा TSI721_OMD_IOF		0x08000000
#घोषणा TSI721_OMD_DTYPE	0xe0000000
#घोषणा TSI721_OMD_RSRVD	0x17f80000

	__le32 msg_info;

#घोषणा TSI721_OMD_BCOUNT	0x00000ff8
#घोषणा TSI721_OMD_SSIZE	0x0000f000
#घोषणा TSI721_OMD_LETER	0x00030000
#घोषणा TSI721_OMD_XMBOX	0x003c0000
#घोषणा TSI721_OMD_MBOX		0x00c00000
#घोषणा TSI721_OMD_TT		0x0c000000

	जोड़ अणु
		__le32 bufptr_lo;	/* अगर DTYPE == 4 */
		__le32 next_lo;		/* अगर DTYPE == 5 */
	पूर्ण;

	जोड़ अणु
		__le32 bufptr_hi;	/* अगर DTYPE == 4 */
		__le32 next_hi;		/* अगर DTYPE == 5 */
	पूर्ण;

पूर्ण __aligned(16);

काष्ठा tsi721_dma_sts अणु
	__le64	desc_sts[8];
पूर्ण __aligned(64);

काष्ठा tsi721_desc_sts_fअगरo अणु
	जोड़ अणु
		__le64	da64;
		काष्ठा अणु
			__le32	lo;
			__le32	hi;
		पूर्ण da32;
	पूर्ण stat[8];
पूर्ण __aligned(64);

/* Descriptor types क्रम BDMA and Messaging blocks */
क्रमागत dma_dtype अणु
	DTYPE1 = 1, /* Data Transfer DMA Descriptor */
	DTYPE2 = 2, /* Immediate Data Transfer DMA Descriptor */
	DTYPE3 = 3, /* Block Poपूर्णांकer DMA Descriptor */
	DTYPE4 = 4, /* Outbound Msg DMA Descriptor */
	DTYPE5 = 5, /* OB Messaging Block Poपूर्णांकer Descriptor */
	DTYPE6 = 6  /* Inbound Messaging Descriptor */
पूर्ण;

क्रमागत dma_rtype अणु
	NREAD = 0,
	LAST_NWRITE_R = 1,
	ALL_NWRITE = 2,
	ALL_NWRITE_R = 3,
	MAINT_RD = 4,
	MAINT_WR = 5
पूर्ण;

/*
 * mport Driver Definitions
 */
#घोषणा TSI721_DMA_CHNUM	TSI721_DMA_MAXCH

#घोषणा TSI721_DMACH_MAINT	7	/* DMA channel क्रम मुख्यt requests */
#घोषणा TSI721_DMACH_MAINT_NBD	32	/* Number of BDs क्रम मुख्यt requests */

#घोषणा TSI721_DMACH_DMA	1	/* DMA channel क्रम data transfers */

#घोषणा MSG_DMA_ENTRY_INX_TO_SIZE(x)	((0x10 << (x)) & 0xFFFF0)

क्रमागत tsi721_smsg_पूर्णांक_flag अणु
	SMSG_INT_NONE		= 0x00000000,
	SMSG_INT_ECC_COR_CH	= 0x000000ff,
	SMSG_INT_ECC_NCOR_CH	= 0x0000ff00,
	SMSG_INT_ECC_COR	= 0x00020000,
	SMSG_INT_ECC_NCOR	= 0x00040000,
	SMSG_INT_UNS_RSP	= 0x00800000,
	SMSG_INT_ALL		= 0x0006ffff
पूर्ण;

/* Structures */

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE

#घोषणा TSI721_BDMA_MAX_BCOUNT	(TSI721_DMAD_BCOUNT1 + 1)

काष्ठा tsi721_tx_desc अणु
	काष्ठा dma_async_tx_descriptor	txd;
	u16				destid;
	/* low 64-bits of 66-bit RIO address */
	u64				rio_addr;
	/* upper 2-bits of 66-bit RIO address */
	u8				rio_addr_u;
	क्रमागत dma_rtype			rtype;
	काष्ठा list_head		desc_node;
	काष्ठा scatterlist		*sg;
	अचिन्हित पूर्णांक			sg_len;
	क्रमागत dma_status			status;
पूर्ण;

काष्ठा tsi721_bdma_chan अणु
	पूर्णांक		id;
	व्योम __iomem	*regs;
	पूर्णांक		bd_num;		/* number of HW buffer descriptors */
	व्योम		*bd_base;	/* start of DMA descriptors */
	dma_addr_t	bd_phys;
	व्योम		*sts_base;	/* start of DMA BD status FIFO */
	dma_addr_t	sts_phys;
	पूर्णांक		sts_size;
	u32		sts_rdptr;
	u32		wr_count;
	u32		wr_count_next;

	काष्ठा dma_chan		dchan;
	काष्ठा tsi721_tx_desc	*tx_desc;
	spinlock_t		lock;
	काष्ठा tsi721_tx_desc	*active_tx;
	काष्ठा list_head	queue;
	काष्ठा list_head	मुक्त_list;
	काष्ठा tasklet_काष्ठा	tasklet;
	bool			active;
पूर्ण;

#पूर्ण_अगर /* CONFIG_RAPIDIO_DMA_ENGINE */

काष्ठा tsi721_bdma_मुख्यt अणु
	पूर्णांक		ch_id;		/* BDMA channel number */
	पूर्णांक		bd_num;		/* number of buffer descriptors */
	व्योम		*bd_base;	/* start of DMA descriptors */
	dma_addr_t	bd_phys;
	व्योम		*sts_base;	/* start of DMA BD status FIFO */
	dma_addr_t	sts_phys;
	पूर्णांक		sts_size;
पूर्ण;

काष्ठा tsi721_imsg_ring अणु
	u32		size;
	/* VA/PA of data buffers क्रम incoming messages */
	व्योम		*buf_base;
	dma_addr_t	buf_phys;
	/* VA/PA of circular मुक्त buffer list */
	व्योम		*imfq_base;
	dma_addr_t	imfq_phys;
	/* VA/PA of Inbound message descriptors */
	व्योम		*imd_base;
	dma_addr_t	imd_phys;
	 /* Inbound Queue buffer poपूर्णांकers */
	व्योम		*imq_base[TSI721_IMSGD_RING_SIZE];

	u32		rx_slot;
	व्योम		*dev_id;
	u32		fq_wrptr;
	u32		desc_rdptr;
	spinlock_t	lock;
पूर्ण;

काष्ठा tsi721_omsg_ring अणु
	u32		size;
	/* VA/PA of OB Msg descriptors */
	व्योम		*omd_base;
	dma_addr_t	omd_phys;
	/* VA/PA of OB Msg data buffers */
	व्योम		*omq_base[TSI721_OMSGD_RING_SIZE];
	dma_addr_t	omq_phys[TSI721_OMSGD_RING_SIZE];
	/* VA/PA of OB Msg descriptor status FIFO */
	व्योम		*sts_base;
	dma_addr_t	sts_phys;
	u32		sts_size; /* # of allocated status entries */
	u32		sts_rdptr;

	u32		tx_slot;
	व्योम		*dev_id;
	u32		wr_count;
	spinlock_t	lock;
पूर्ण;

क्रमागत tsi721_flags अणु
	TSI721_USING_MSI	= (1 << 0),
	TSI721_USING_MSIX	= (1 << 1),
	TSI721_IMSGID_SET	= (1 << 2),
पूर्ण;

#अगर_घोषित CONFIG_PCI_MSI
/*
 * MSI-X Table Entries (0 ... 69)
 */
#घोषणा TSI721_MSIX_DMACH_DONE(x)	(0 + (x))
#घोषणा TSI721_MSIX_DMACH_INT(x)	(8 + (x))
#घोषणा TSI721_MSIX_BDMA_INT		16
#घोषणा TSI721_MSIX_OMSG_DONE(x)	(17 + (x))
#घोषणा TSI721_MSIX_OMSG_INT(x)		(25 + (x))
#घोषणा TSI721_MSIX_IMSG_DQ_RCV(x)	(33 + (x))
#घोषणा TSI721_MSIX_IMSG_INT(x)		(41 + (x))
#घोषणा TSI721_MSIX_MSG_INT		49
#घोषणा TSI721_MSIX_SR2PC_IDBQ_RCV(x)	(50 + (x))
#घोषणा TSI721_MSIX_SR2PC_CH_INT(x)	(58 + (x))
#घोषणा TSI721_MSIX_SR2PC_INT		66
#घोषणा TSI721_MSIX_PC2SR_INT		67
#घोषणा TSI721_MSIX_SRIO_MAC_INT	68
#घोषणा TSI721_MSIX_I2C_INT		69

/* MSI-X vector and init table entry indexes */
क्रमागत tsi721_msix_vect अणु
	TSI721_VECT_IDB,
	TSI721_VECT_PWRX, /* PW_RX is part of SRIO MAC Interrupt reporting */
	TSI721_VECT_OMB0_DONE,
	TSI721_VECT_OMB1_DONE,
	TSI721_VECT_OMB2_DONE,
	TSI721_VECT_OMB3_DONE,
	TSI721_VECT_OMB0_INT,
	TSI721_VECT_OMB1_INT,
	TSI721_VECT_OMB2_INT,
	TSI721_VECT_OMB3_INT,
	TSI721_VECT_IMB0_RCV,
	TSI721_VECT_IMB1_RCV,
	TSI721_VECT_IMB2_RCV,
	TSI721_VECT_IMB3_RCV,
	TSI721_VECT_IMB0_INT,
	TSI721_VECT_IMB1_INT,
	TSI721_VECT_IMB2_INT,
	TSI721_VECT_IMB3_INT,
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	TSI721_VECT_DMA0_DONE,
	TSI721_VECT_DMA1_DONE,
	TSI721_VECT_DMA2_DONE,
	TSI721_VECT_DMA3_DONE,
	TSI721_VECT_DMA4_DONE,
	TSI721_VECT_DMA5_DONE,
	TSI721_VECT_DMA6_DONE,
	TSI721_VECT_DMA7_DONE,
	TSI721_VECT_DMA0_INT,
	TSI721_VECT_DMA1_INT,
	TSI721_VECT_DMA2_INT,
	TSI721_VECT_DMA3_INT,
	TSI721_VECT_DMA4_INT,
	TSI721_VECT_DMA5_INT,
	TSI721_VECT_DMA6_INT,
	TSI721_VECT_DMA7_INT,
#पूर्ण_अगर /* CONFIG_RAPIDIO_DMA_ENGINE */
	TSI721_VECT_MAX
पूर्ण;

#घोषणा IRQ_DEVICE_NAME_MAX	64

काष्ठा msix_irq अणु
	u16	vector;
	अक्षर	irq_name[IRQ_DEVICE_NAME_MAX];
पूर्ण;
#पूर्ण_अगर /* CONFIG_PCI_MSI */

काष्ठा tsi721_ib_win_mapping अणु
	काष्ठा list_head node;
	dma_addr_t	lstart;
पूर्ण;

काष्ठा tsi721_ib_win अणु
	u64		rstart;
	u32		size;
	dma_addr_t	lstart;
	bool		active;
	bool		xlat;
	काष्ठा list_head mappings;
पूर्ण;

काष्ठा tsi721_obw_bar अणु
	u64		base;
	u64		size;
	u64		मुक्त;
पूर्ण;

काष्ठा tsi721_ob_win अणु
	u64		base;
	u32		size;
	u16		destid;
	u64		rstart;
	bool		active;
	काष्ठा tsi721_obw_bar *pbar;
पूर्ण;

काष्ठा tsi721_device अणु
	काष्ठा pci_dev	*pdev;
	काष्ठा rio_mport mport;
	u32		flags;
	व्योम __iomem	*regs;
#अगर_घोषित CONFIG_PCI_MSI
	काष्ठा msix_irq	msix[TSI721_VECT_MAX];
#पूर्ण_अगर
	/* Doorbells */
	व्योम __iomem	*odb_base;
	व्योम		*idb_base;
	dma_addr_t	idb_dma;
	काष्ठा work_काष्ठा idb_work;
	u32		db_discard_count;

	/* Inbound Port-Write */
	काष्ठा work_काष्ठा pw_work;
	काष्ठा kfअगरo	pw_fअगरo;
	spinlock_t	pw_fअगरo_lock;
	u32		pw_discard_count;

	/* BDMA Engine */
	काष्ठा tsi721_bdma_मुख्यt mdma; /* Maपूर्णांकenance rd/wr request channel */

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	काष्ठा tsi721_bdma_chan bdma[TSI721_DMA_CHNUM];
#पूर्ण_अगर

	/* Inbound Messaging */
	पूर्णांक		imsg_init[TSI721_IMSG_CHNUM];
	काष्ठा tsi721_imsg_ring imsg_ring[TSI721_IMSG_CHNUM];

	/* Outbound Messaging */
	पूर्णांक		omsg_init[TSI721_OMSG_CHNUM];
	काष्ठा tsi721_omsg_ring	omsg_ring[TSI721_OMSG_CHNUM];

	/* Inbound Mapping Winकरोws */
	काष्ठा tsi721_ib_win ib_win[TSI721_IBWIN_NUM];
	पूर्णांक		ibwin_cnt;

	/* Outbound Mapping Winकरोws */
	काष्ठा tsi721_obw_bar p2r_bar[2];
	काष्ठा tsi721_ob_win  ob_win[TSI721_OBWIN_NUM];
	पूर्णांक		obwin_cnt;
पूर्ण;

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
बाह्य व्योम tsi721_bdma_handler(काष्ठा tsi721_bdma_chan *bdma_chan);
बाह्य पूर्णांक tsi721_रेजिस्टर_dma(काष्ठा tsi721_device *priv);
बाह्य व्योम tsi721_unरेजिस्टर_dma(काष्ठा tsi721_device *priv);
बाह्य व्योम tsi721_dma_stop_all(काष्ठा tsi721_device *priv);
#अन्यथा
#घोषणा tsi721_dma_stop_all(priv) करो अणुपूर्ण जबतक (0)
#घोषणा tsi721_unरेजिस्टर_dma(priv) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
