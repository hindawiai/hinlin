<शैली गुरु>
// SPDX-License-Identअगरier:  GPL-2.0
// (C) 2017-2018 Synopsys, Inc. (www.synopsys.com)

/*
 * Synopsys DesignWare AXI DMA Controller driver.
 *
 * Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>
 */

#अगर_अघोषित _AXI_DMA_PLATFORM_H
#घोषणा _AXI_DMA_PLATFORM_H

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/types.h>

#समावेश "../virt-dma.h"

#घोषणा DMAC_MAX_CHANNELS	8
#घोषणा DMAC_MAX_MASTERS	2
#घोषणा DMAC_MAX_BLK_SIZE	0x200000

काष्ठा dw_axi_dma_hcfg अणु
	u32	nr_channels;
	u32	nr_masters;
	u32	m_data_width;
	u32	block_size[DMAC_MAX_CHANNELS];
	u32	priority[DMAC_MAX_CHANNELS];
	/* maximum supported axi burst length */
	u32	axi_rw_burst_len;
	bool	restrict_axi_burst_len;
पूर्ण;

काष्ठा axi_dma_chan अणु
	काष्ठा axi_dma_chip		*chip;
	व्योम __iomem			*chan_regs;
	u8				id;
	u8				hw_handshake_num;
	atomic_t			descs_allocated;

	काष्ठा dma_pool			*desc_pool;
	काष्ठा virt_dma_chan		vc;

	काष्ठा axi_dma_desc		*desc;
	काष्ठा dma_slave_config		config;
	क्रमागत dma_transfer_direction	direction;
	bool				cyclic;
	/* these other elements are all रक्षित by vc.lock */
	bool				is_छोड़ोd;
पूर्ण;

काष्ठा dw_axi_dma अणु
	काष्ठा dma_device	dma;
	काष्ठा dw_axi_dma_hcfg	*hdata;
	काष्ठा device_dma_parameters	dma_parms;

	/* channels */
	काष्ठा axi_dma_chan	*chan;
पूर्ण;

काष्ठा axi_dma_chip अणु
	काष्ठा device		*dev;
	पूर्णांक			irq;
	व्योम __iomem		*regs;
	व्योम __iomem		*apb_regs;
	काष्ठा clk		*core_clk;
	काष्ठा clk		*cfgr_clk;
	काष्ठा dw_axi_dma	*dw;
पूर्ण;

/* LLI == Linked List Item */
काष्ठा __packed axi_dma_lli अणु
	__le64		sar;
	__le64		dar;
	__le32		block_ts_lo;
	__le32		block_ts_hi;
	__le64		llp;
	__le32		ctl_lo;
	__le32		ctl_hi;
	__le32		sstat;
	__le32		dstat;
	__le32		status_lo;
	__le32		status_hi;
	__le32		reserved_lo;
	__le32		reserved_hi;
पूर्ण;

काष्ठा axi_dma_hw_desc अणु
	काष्ठा axi_dma_lli	*lli;
	dma_addr_t		llp;
	u32			len;
पूर्ण;

काष्ठा axi_dma_desc अणु
	काष्ठा axi_dma_hw_desc	*hw_desc;

	काष्ठा virt_dma_desc		vd;
	काष्ठा axi_dma_chan		*chan;
	u32				completed_blocks;
	u32				length;
	u32				period_len;
पूर्ण;

अटल अंतरभूत काष्ठा device *dchan2dev(काष्ठा dma_chan *dchan)
अणु
	वापस &dchan->dev->device;
पूर्ण

अटल अंतरभूत काष्ठा device *chan2dev(काष्ठा axi_dma_chan *chan)
अणु
	वापस &chan->vc.chan.dev->device;
पूर्ण

अटल अंतरभूत काष्ठा axi_dma_desc *vd_to_axi_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा axi_dma_desc, vd);
पूर्ण

अटल अंतरभूत काष्ठा axi_dma_chan *vc_to_axi_dma_chan(काष्ठा virt_dma_chan *vc)
अणु
	वापस container_of(vc, काष्ठा axi_dma_chan, vc);
पूर्ण

अटल अंतरभूत काष्ठा axi_dma_chan *dchan_to_axi_dma_chan(काष्ठा dma_chan *dchan)
अणु
	वापस vc_to_axi_dma_chan(to_virt_chan(dchan));
पूर्ण


#घोषणा COMMON_REG_LEN		0x100
#घोषणा CHAN_REG_LEN		0x100

/* Common रेजिस्टरs offset */
#घोषणा DMAC_ID			0x000 /* R DMAC ID */
#घोषणा DMAC_COMPVER		0x008 /* R DMAC Component Version */
#घोषणा DMAC_CFG		0x010 /* R/W DMAC Configuration */
#घोषणा DMAC_CHEN		0x018 /* R/W DMAC Channel Enable */
#घोषणा DMAC_CHEN_L		0x018 /* R/W DMAC Channel Enable 00-31 */
#घोषणा DMAC_CHEN_H		0x01C /* R/W DMAC Channel Enable 32-63 */
#घोषणा DMAC_INTSTATUS		0x030 /* R DMAC Interrupt Status */
#घोषणा DMAC_COMMON_INTCLEAR	0x038 /* W DMAC Interrupt Clear */
#घोषणा DMAC_COMMON_INTSTATUS_ENA 0x040 /* R DMAC Interrupt Status Enable */
#घोषणा DMAC_COMMON_INTSIGNAL_ENA 0x048 /* R/W DMAC Interrupt Signal Enable */
#घोषणा DMAC_COMMON_INTSTATUS	0x050 /* R DMAC Interrupt Status */
#घोषणा DMAC_RESET		0x058 /* R DMAC Reset Register1 */

/* DMA channel रेजिस्टरs offset */
#घोषणा CH_SAR			0x000 /* R/W Chan Source Address */
#घोषणा CH_DAR			0x008 /* R/W Chan Destination Address */
#घोषणा CH_BLOCK_TS		0x010 /* R/W Chan Block Transfer Size */
#घोषणा CH_CTL			0x018 /* R/W Chan Control */
#घोषणा CH_CTL_L		0x018 /* R/W Chan Control 00-31 */
#घोषणा CH_CTL_H		0x01C /* R/W Chan Control 32-63 */
#घोषणा CH_CFG			0x020 /* R/W Chan Configuration */
#घोषणा CH_CFG_L		0x020 /* R/W Chan Configuration 00-31 */
#घोषणा CH_CFG_H		0x024 /* R/W Chan Configuration 32-63 */
#घोषणा CH_LLP			0x028 /* R/W Chan Linked List Poपूर्णांकer */
#घोषणा CH_STATUS		0x030 /* R Chan Status */
#घोषणा CH_SWHSSRC		0x038 /* R/W Chan SW Handshake Source */
#घोषणा CH_SWHSDST		0x040 /* R/W Chan SW Handshake Destination */
#घोषणा CH_BLK_TFR_RESUMEREQ	0x048 /* W Chan Block Transfer Resume Req */
#घोषणा CH_AXI_ID		0x050 /* R/W Chan AXI ID */
#घोषणा CH_AXI_QOS		0x058 /* R/W Chan AXI QOS */
#घोषणा CH_SSTAT		0x060 /* R Chan Source Status */
#घोषणा CH_DSTAT		0x068 /* R Chan Destination Status */
#घोषणा CH_SSTATAR		0x070 /* R/W Chan Source Status Fetch Addr */
#घोषणा CH_DSTATAR		0x078 /* R/W Chan Destination Status Fetch Addr */
#घोषणा CH_INTSTATUS_ENA	0x080 /* R/W Chan Interrupt Status Enable */
#घोषणा CH_INTSTATUS		0x088 /* R/W Chan Interrupt Status */
#घोषणा CH_INTSIGNAL_ENA	0x090 /* R/W Chan Interrupt Signal Enable */
#घोषणा CH_INTCLEAR		0x098 /* W Chan Interrupt Clear */

/* These Apb रेजिस्टरs are used by Intel KeemBay SoC */
#घोषणा DMAC_APB_CFG		0x000 /* DMAC Apb Configuration Register */
#घोषणा DMAC_APB_STAT		0x004 /* DMAC Apb Status Register */
#घोषणा DMAC_APB_DEBUG_STAT_0	0x008 /* DMAC Apb Debug Status Register 0 */
#घोषणा DMAC_APB_DEBUG_STAT_1	0x00C /* DMAC Apb Debug Status Register 1 */
#घोषणा DMAC_APB_HW_HS_SEL_0	0x010 /* DMAC Apb HW HS रेजिस्टर 0 */
#घोषणा DMAC_APB_HW_HS_SEL_1	0x014 /* DMAC Apb HW HS रेजिस्टर 1 */
#घोषणा DMAC_APB_LPI		0x018 /* DMAC Apb Low Power Interface Reg */
#घोषणा DMAC_APB_BYTE_WR_CH_EN	0x01C /* DMAC Apb Byte Write Enable */
#घोषणा DMAC_APB_HALFWORD_WR_CH_EN	0x020 /* DMAC Halfword ग_लिखो enables */

#घोषणा UNUSED_CHANNEL		0x3F /* Set unused DMA channel to 0x3F */
#घोषणा MAX_BLOCK_SIZE		0x1000 /* 1024 blocks * 4 bytes data width */

/* DMAC_CFG */
#घोषणा DMAC_EN_POS			0
#घोषणा DMAC_EN_MASK			BIT(DMAC_EN_POS)

#घोषणा INT_EN_POS			1
#घोषणा INT_EN_MASK			BIT(INT_EN_POS)

#घोषणा DMAC_CHAN_EN_SHIFT		0
#घोषणा DMAC_CHAN_EN_WE_SHIFT		8

#घोषणा DMAC_CHAN_SUSP_SHIFT		16
#घोषणा DMAC_CHAN_SUSP_WE_SHIFT		24

/* CH_CTL_H */
#घोषणा CH_CTL_H_ARLEN_EN		BIT(6)
#घोषणा CH_CTL_H_ARLEN_POS		7
#घोषणा CH_CTL_H_AWLEN_EN		BIT(15)
#घोषणा CH_CTL_H_AWLEN_POS		16

क्रमागत अणु
	DWAXIDMAC_ARWLEN_1		= 0,
	DWAXIDMAC_ARWLEN_2		= 1,
	DWAXIDMAC_ARWLEN_4		= 3,
	DWAXIDMAC_ARWLEN_8		= 7,
	DWAXIDMAC_ARWLEN_16		= 15,
	DWAXIDMAC_ARWLEN_32		= 31,
	DWAXIDMAC_ARWLEN_64		= 63,
	DWAXIDMAC_ARWLEN_128		= 127,
	DWAXIDMAC_ARWLEN_256		= 255,
	DWAXIDMAC_ARWLEN_MIN		= DWAXIDMAC_ARWLEN_1,
	DWAXIDMAC_ARWLEN_MAX		= DWAXIDMAC_ARWLEN_256
पूर्ण;

#घोषणा CH_CTL_H_LLI_LAST		BIT(30)
#घोषणा CH_CTL_H_LLI_VALID		BIT(31)

/* CH_CTL_L */
#घोषणा CH_CTL_L_LAST_WRITE_EN		BIT(30)

#घोषणा CH_CTL_L_DST_MSIZE_POS		18
#घोषणा CH_CTL_L_SRC_MSIZE_POS		14

क्रमागत अणु
	DWAXIDMAC_BURST_TRANS_LEN_1	= 0,
	DWAXIDMAC_BURST_TRANS_LEN_4,
	DWAXIDMAC_BURST_TRANS_LEN_8,
	DWAXIDMAC_BURST_TRANS_LEN_16,
	DWAXIDMAC_BURST_TRANS_LEN_32,
	DWAXIDMAC_BURST_TRANS_LEN_64,
	DWAXIDMAC_BURST_TRANS_LEN_128,
	DWAXIDMAC_BURST_TRANS_LEN_256,
	DWAXIDMAC_BURST_TRANS_LEN_512,
	DWAXIDMAC_BURST_TRANS_LEN_1024
पूर्ण;

#घोषणा CH_CTL_L_DST_WIDTH_POS		11
#घोषणा CH_CTL_L_SRC_WIDTH_POS		8

#घोषणा CH_CTL_L_DST_INC_POS		6
#घोषणा CH_CTL_L_SRC_INC_POS		4
क्रमागत अणु
	DWAXIDMAC_CH_CTL_L_INC		= 0,
	DWAXIDMAC_CH_CTL_L_NOINC
पूर्ण;

#घोषणा CH_CTL_L_DST_MAST		BIT(2)
#घोषणा CH_CTL_L_SRC_MAST		BIT(0)

/* CH_CFG_H */
#घोषणा CH_CFG_H_PRIORITY_POS		17
#घोषणा CH_CFG_H_HS_SEL_DST_POS		4
#घोषणा CH_CFG_H_HS_SEL_SRC_POS		3
क्रमागत अणु
	DWAXIDMAC_HS_SEL_HW		= 0,
	DWAXIDMAC_HS_SEL_SW
पूर्ण;

#घोषणा CH_CFG_H_TT_FC_POS		0
क्रमागत अणु
	DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC	= 0,
	DWAXIDMAC_TT_FC_MEM_TO_PER_DMAC,
	DWAXIDMAC_TT_FC_PER_TO_MEM_DMAC,
	DWAXIDMAC_TT_FC_PER_TO_PER_DMAC,
	DWAXIDMAC_TT_FC_PER_TO_MEM_SRC,
	DWAXIDMAC_TT_FC_PER_TO_PER_SRC,
	DWAXIDMAC_TT_FC_MEM_TO_PER_DST,
	DWAXIDMAC_TT_FC_PER_TO_PER_DST
पूर्ण;

/* CH_CFG_L */
#घोषणा CH_CFG_L_DST_MULTBLK_TYPE_POS	2
#घोषणा CH_CFG_L_SRC_MULTBLK_TYPE_POS	0
क्रमागत अणु
	DWAXIDMAC_MBLK_TYPE_CONTIGUOUS	= 0,
	DWAXIDMAC_MBLK_TYPE_RELOAD,
	DWAXIDMAC_MBLK_TYPE_SHADOW_REG,
	DWAXIDMAC_MBLK_TYPE_LL
पूर्ण;

/**
 * DW AXI DMA channel पूर्णांकerrupts
 *
 * @DWAXIDMAC_IRQ_NONE: Biपंचांगask of no one पूर्णांकerrupt
 * @DWAXIDMAC_IRQ_BLOCK_TRF: Block transfer complete
 * @DWAXIDMAC_IRQ_DMA_TRF: Dma transfer complete
 * @DWAXIDMAC_IRQ_SRC_TRAN: Source transaction complete
 * @DWAXIDMAC_IRQ_DST_TRAN: Destination transaction complete
 * @DWAXIDMAC_IRQ_SRC_DEC_ERR: Source decode error
 * @DWAXIDMAC_IRQ_DST_DEC_ERR: Destination decode error
 * @DWAXIDMAC_IRQ_SRC_SLV_ERR: Source slave error
 * @DWAXIDMAC_IRQ_DST_SLV_ERR: Destination slave error
 * @DWAXIDMAC_IRQ_LLI_RD_DEC_ERR: LLI पढ़ो decode error
 * @DWAXIDMAC_IRQ_LLI_WR_DEC_ERR: LLI ग_लिखो decode error
 * @DWAXIDMAC_IRQ_LLI_RD_SLV_ERR: LLI पढ़ो slave error
 * @DWAXIDMAC_IRQ_LLI_WR_SLV_ERR: LLI ग_लिखो slave error
 * @DWAXIDMAC_IRQ_INVALID_ERR: LLI invalid error or Shaकरोw रेजिस्टर error
 * @DWAXIDMAC_IRQ_MULTIBLKTYPE_ERR: Slave Interface Multiblock type error
 * @DWAXIDMAC_IRQ_DEC_ERR: Slave Interface decode error
 * @DWAXIDMAC_IRQ_WR2RO_ERR: Slave Interface ग_लिखो to पढ़ो only error
 * @DWAXIDMAC_IRQ_RD2RWO_ERR: Slave Interface पढ़ो to ग_लिखो only error
 * @DWAXIDMAC_IRQ_WRONCHEN_ERR: Slave Interface ग_लिखो to channel error
 * @DWAXIDMAC_IRQ_SHADOWREG_ERR: Slave Interface shaकरोw reg error
 * @DWAXIDMAC_IRQ_WRONHOLD_ERR: Slave Interface hold error
 * @DWAXIDMAC_IRQ_LOCK_CLEARED: Lock Cleared Status
 * @DWAXIDMAC_IRQ_SRC_SUSPENDED: Source Suspended Status
 * @DWAXIDMAC_IRQ_SUSPENDED: Channel Suspended Status
 * @DWAXIDMAC_IRQ_DISABLED: Channel Disabled Status
 * @DWAXIDMAC_IRQ_ABORTED: Channel Aborted Status
 * @DWAXIDMAC_IRQ_ALL_ERR: Biपंचांगask of all error पूर्णांकerrupts
 * @DWAXIDMAC_IRQ_ALL: Biपंचांगask of all पूर्णांकerrupts
 */
क्रमागत अणु
	DWAXIDMAC_IRQ_NONE		= 0,
	DWAXIDMAC_IRQ_BLOCK_TRF		= BIT(0),
	DWAXIDMAC_IRQ_DMA_TRF		= BIT(1),
	DWAXIDMAC_IRQ_SRC_TRAN		= BIT(3),
	DWAXIDMAC_IRQ_DST_TRAN		= BIT(4),
	DWAXIDMAC_IRQ_SRC_DEC_ERR	= BIT(5),
	DWAXIDMAC_IRQ_DST_DEC_ERR	= BIT(6),
	DWAXIDMAC_IRQ_SRC_SLV_ERR	= BIT(7),
	DWAXIDMAC_IRQ_DST_SLV_ERR	= BIT(8),
	DWAXIDMAC_IRQ_LLI_RD_DEC_ERR	= BIT(9),
	DWAXIDMAC_IRQ_LLI_WR_DEC_ERR	= BIT(10),
	DWAXIDMAC_IRQ_LLI_RD_SLV_ERR	= BIT(11),
	DWAXIDMAC_IRQ_LLI_WR_SLV_ERR	= BIT(12),
	DWAXIDMAC_IRQ_INVALID_ERR	= BIT(13),
	DWAXIDMAC_IRQ_MULTIBLKTYPE_ERR	= BIT(14),
	DWAXIDMAC_IRQ_DEC_ERR		= BIT(16),
	DWAXIDMAC_IRQ_WR2RO_ERR		= BIT(17),
	DWAXIDMAC_IRQ_RD2RWO_ERR	= BIT(18),
	DWAXIDMAC_IRQ_WRONCHEN_ERR	= BIT(19),
	DWAXIDMAC_IRQ_SHADOWREG_ERR	= BIT(20),
	DWAXIDMAC_IRQ_WRONHOLD_ERR	= BIT(21),
	DWAXIDMAC_IRQ_LOCK_CLEARED	= BIT(27),
	DWAXIDMAC_IRQ_SRC_SUSPENDED	= BIT(28),
	DWAXIDMAC_IRQ_SUSPENDED		= BIT(29),
	DWAXIDMAC_IRQ_DISABLED		= BIT(30),
	DWAXIDMAC_IRQ_ABORTED		= BIT(31),
	DWAXIDMAC_IRQ_ALL_ERR		= (GENMASK(21, 16) | GENMASK(14, 5)),
	DWAXIDMAC_IRQ_ALL		= GENMASK(31, 0)
पूर्ण;

क्रमागत अणु
	DWAXIDMAC_TRANS_WIDTH_8		= 0,
	DWAXIDMAC_TRANS_WIDTH_16,
	DWAXIDMAC_TRANS_WIDTH_32,
	DWAXIDMAC_TRANS_WIDTH_64,
	DWAXIDMAC_TRANS_WIDTH_128,
	DWAXIDMAC_TRANS_WIDTH_256,
	DWAXIDMAC_TRANS_WIDTH_512,
	DWAXIDMAC_TRANS_WIDTH_MAX	= DWAXIDMAC_TRANS_WIDTH_512
पूर्ण;

#पूर्ण_अगर /* _AXI_DMA_PLATFORM_H */
