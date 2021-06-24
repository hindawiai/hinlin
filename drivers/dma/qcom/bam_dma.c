<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 */
/*
 * QCOM BAM DMA engine driver
 *
 * QCOM BAM DMA blocks are distributed amongst a number of the on-chip
 * peripherals on the MSM 8x74.  The configuration of the channels are dependent
 * on the way they are hard wired to that specअगरic peripheral.  The peripheral
 * device tree entries specअगरy the configuration of each channel.
 *
 * The DMA controller requires the use of बाह्यal memory क्रम storage of the
 * hardware descriptors क्रम each channel.  The descriptor FIFO is accessed as a
 * circular buffer and operations are managed according to the offset within the
 * FIFO.  After pipe/channel reset, all of the pipe रेजिस्टरs and पूर्णांकernal state
 * are back to शेषs.
 *
 * During DMA operations, we ग_लिखो descriptors to the FIFO, being careful to
 * handle wrapping and then ग_लिखो the last FIFO offset to that channel's
 * P_EVNT_REG रेजिस्टर to kick off the transaction.  The P_SW_OFSTS रेजिस्टर
 * indicates the current FIFO offset that is being processed, so there is some
 * indication of where the hardware is currently working.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

काष्ठा bam_desc_hw अणु
	__le32 addr;		/* Buffer physical address */
	__le16 size;		/* Buffer size in bytes */
	__le16 flags;
पूर्ण;

#घोषणा BAM_DMA_AUTOSUSPEND_DELAY 100

#घोषणा DESC_FLAG_INT BIT(15)
#घोषणा DESC_FLAG_EOT BIT(14)
#घोषणा DESC_FLAG_EOB BIT(13)
#घोषणा DESC_FLAG_NWD BIT(12)
#घोषणा DESC_FLAG_CMD BIT(11)

काष्ठा bam_async_desc अणु
	काष्ठा virt_dma_desc vd;

	u32 num_desc;
	u32 xfer_len;

	/* transaction flags, EOT|EOB|NWD */
	u16 flags;

	काष्ठा bam_desc_hw *curr_desc;

	/* list node क्रम the desc in the bam_chan list of descriptors */
	काष्ठा list_head desc_node;
	क्रमागत dma_transfer_direction dir;
	माप_प्रकार length;
	काष्ठा bam_desc_hw desc[];
पूर्ण;

क्रमागत bam_reg अणु
	BAM_CTRL,
	BAM_REVISION,
	BAM_NUM_PIPES,
	BAM_DESC_CNT_TRSHLD,
	BAM_IRQ_SRCS,
	BAM_IRQ_SRCS_MSK,
	BAM_IRQ_SRCS_UNMASKED,
	BAM_IRQ_STTS,
	BAM_IRQ_CLR,
	BAM_IRQ_EN,
	BAM_CNFG_BITS,
	BAM_IRQ_SRCS_EE,
	BAM_IRQ_SRCS_MSK_EE,
	BAM_P_CTRL,
	BAM_P_RST,
	BAM_P_HALT,
	BAM_P_IRQ_STTS,
	BAM_P_IRQ_CLR,
	BAM_P_IRQ_EN,
	BAM_P_EVNT_DEST_ADDR,
	BAM_P_EVNT_REG,
	BAM_P_SW_OFSTS,
	BAM_P_DATA_FIFO_ADDR,
	BAM_P_DESC_FIFO_ADDR,
	BAM_P_EVNT_GEN_TRSHLD,
	BAM_P_FIFO_SIZES,
पूर्ण;

काष्ठा reg_offset_data अणु
	u32 base_offset;
	अचिन्हित पूर्णांक pipe_mult, evnt_mult, ee_mult;
पूर्ण;

अटल स्थिर काष्ठा reg_offset_data bam_v1_3_reg_info[] = अणु
	[BAM_CTRL]		= अणु 0x0F80, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_REVISION]		= अणु 0x0F84, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_NUM_PIPES]		= अणु 0x0FBC, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_DESC_CNT_TRSHLD]	= अणु 0x0F88, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS]		= अणु 0x0F8C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_MSK]	= अणु 0x0F90, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_UNMASKED]	= अणु 0x0FB0, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_STTS]		= अणु 0x0F94, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_CLR]		= अणु 0x0F98, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_EN]		= अणु 0x0F9C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_CNFG_BITS]		= अणु 0x0FFC, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_EE]	= अणु 0x1800, 0x00, 0x00, 0x80 पूर्ण,
	[BAM_IRQ_SRCS_MSK_EE]	= अणु 0x1804, 0x00, 0x00, 0x80 पूर्ण,
	[BAM_P_CTRL]		= अणु 0x0000, 0x80, 0x00, 0x00 पूर्ण,
	[BAM_P_RST]		= अणु 0x0004, 0x80, 0x00, 0x00 पूर्ण,
	[BAM_P_HALT]		= अणु 0x0008, 0x80, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_STTS]	= अणु 0x0010, 0x80, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_CLR]		= अणु 0x0014, 0x80, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_EN]		= अणु 0x0018, 0x80, 0x00, 0x00 पूर्ण,
	[BAM_P_EVNT_DEST_ADDR]	= अणु 0x102C, 0x00, 0x40, 0x00 पूर्ण,
	[BAM_P_EVNT_REG]	= अणु 0x1018, 0x00, 0x40, 0x00 पूर्ण,
	[BAM_P_SW_OFSTS]	= अणु 0x1000, 0x00, 0x40, 0x00 पूर्ण,
	[BAM_P_DATA_FIFO_ADDR]	= अणु 0x1024, 0x00, 0x40, 0x00 पूर्ण,
	[BAM_P_DESC_FIFO_ADDR]	= अणु 0x101C, 0x00, 0x40, 0x00 पूर्ण,
	[BAM_P_EVNT_GEN_TRSHLD]	= अणु 0x1028, 0x00, 0x40, 0x00 पूर्ण,
	[BAM_P_FIFO_SIZES]	= अणु 0x1020, 0x00, 0x40, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_offset_data bam_v1_4_reg_info[] = अणु
	[BAM_CTRL]		= अणु 0x0000, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_REVISION]		= अणु 0x0004, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_NUM_PIPES]		= अणु 0x003C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_DESC_CNT_TRSHLD]	= अणु 0x0008, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS]		= अणु 0x000C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_MSK]	= अणु 0x0010, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_UNMASKED]	= अणु 0x0030, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_STTS]		= अणु 0x0014, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_CLR]		= अणु 0x0018, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_EN]		= अणु 0x001C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_CNFG_BITS]		= अणु 0x007C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_EE]	= अणु 0x0800, 0x00, 0x00, 0x80 पूर्ण,
	[BAM_IRQ_SRCS_MSK_EE]	= अणु 0x0804, 0x00, 0x00, 0x80 पूर्ण,
	[BAM_P_CTRL]		= अणु 0x1000, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_RST]		= अणु 0x1004, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_HALT]		= अणु 0x1008, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_STTS]	= अणु 0x1010, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_CLR]		= अणु 0x1014, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_EN]		= अणु 0x1018, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_EVNT_DEST_ADDR]	= अणु 0x182C, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_EVNT_REG]	= अणु 0x1818, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_SW_OFSTS]	= अणु 0x1800, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_DATA_FIFO_ADDR]	= अणु 0x1824, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_DESC_FIFO_ADDR]	= अणु 0x181C, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_EVNT_GEN_TRSHLD]	= अणु 0x1828, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_FIFO_SIZES]	= अणु 0x1820, 0x00, 0x1000, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_offset_data bam_v1_7_reg_info[] = अणु
	[BAM_CTRL]		= अणु 0x00000, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_REVISION]		= अणु 0x01000, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_NUM_PIPES]		= अणु 0x01008, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_DESC_CNT_TRSHLD]	= अणु 0x00008, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS]		= अणु 0x03010, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_MSK]	= अणु 0x03014, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_UNMASKED]	= अणु 0x03018, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_STTS]		= अणु 0x00014, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_CLR]		= अणु 0x00018, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_EN]		= अणु 0x0001C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_CNFG_BITS]		= अणु 0x0007C, 0x00, 0x00, 0x00 पूर्ण,
	[BAM_IRQ_SRCS_EE]	= अणु 0x03000, 0x00, 0x00, 0x1000 पूर्ण,
	[BAM_IRQ_SRCS_MSK_EE]	= अणु 0x03004, 0x00, 0x00, 0x1000 पूर्ण,
	[BAM_P_CTRL]		= अणु 0x13000, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_RST]		= अणु 0x13004, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_HALT]		= अणु 0x13008, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_STTS]	= अणु 0x13010, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_CLR]		= अणु 0x13014, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_IRQ_EN]		= अणु 0x13018, 0x1000, 0x00, 0x00 पूर्ण,
	[BAM_P_EVNT_DEST_ADDR]	= अणु 0x1382C, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_EVNT_REG]	= अणु 0x13818, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_SW_OFSTS]	= अणु 0x13800, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_DATA_FIFO_ADDR]	= अणु 0x13824, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_DESC_FIFO_ADDR]	= अणु 0x1381C, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_EVNT_GEN_TRSHLD]	= अणु 0x13828, 0x00, 0x1000, 0x00 पूर्ण,
	[BAM_P_FIFO_SIZES]	= अणु 0x13820, 0x00, 0x1000, 0x00 पूर्ण,
पूर्ण;

/* BAM CTRL */
#घोषणा BAM_SW_RST			BIT(0)
#घोषणा BAM_EN				BIT(1)
#घोषणा BAM_EN_ACCUM			BIT(4)
#घोषणा BAM_TESTBUS_SEL_SHIFT		5
#घोषणा BAM_TESTBUS_SEL_MASK		0x3F
#घोषणा BAM_DESC_CACHE_SEL_SHIFT	13
#घोषणा BAM_DESC_CACHE_SEL_MASK		0x3
#घोषणा BAM_CACHED_DESC_STORE		BIT(15)
#घोषणा IBC_DISABLE			BIT(16)

/* BAM REVISION */
#घोषणा REVISION_SHIFT		0
#घोषणा REVISION_MASK		0xFF
#घोषणा NUM_EES_SHIFT		8
#घोषणा NUM_EES_MASK		0xF
#घोषणा CE_BUFFER_SIZE		BIT(13)
#घोषणा AXI_ACTIVE		BIT(14)
#घोषणा USE_VMIDMT		BIT(15)
#घोषणा SECURED			BIT(16)
#घोषणा BAM_HAS_NO_BYPASS	BIT(17)
#घोषणा HIGH_FREQUENCY_BAM	BIT(18)
#घोषणा INACTIV_TMRS_EXST	BIT(19)
#घोषणा NUM_INACTIV_TMRS	BIT(20)
#घोषणा DESC_CACHE_DEPTH_SHIFT	21
#घोषणा DESC_CACHE_DEPTH_1	(0 << DESC_CACHE_DEPTH_SHIFT)
#घोषणा DESC_CACHE_DEPTH_2	(1 << DESC_CACHE_DEPTH_SHIFT)
#घोषणा DESC_CACHE_DEPTH_3	(2 << DESC_CACHE_DEPTH_SHIFT)
#घोषणा DESC_CACHE_DEPTH_4	(3 << DESC_CACHE_DEPTH_SHIFT)
#घोषणा CMD_DESC_EN		BIT(23)
#घोषणा INACTIV_TMR_BASE_SHIFT	24
#घोषणा INACTIV_TMR_BASE_MASK	0xFF

/* BAM NUM PIPES */
#घोषणा BAM_NUM_PIPES_SHIFT		0
#घोषणा BAM_NUM_PIPES_MASK		0xFF
#घोषणा PERIPH_NON_PIPE_GRP_SHIFT	16
#घोषणा PERIPH_NON_PIP_GRP_MASK		0xFF
#घोषणा BAM_NON_PIPE_GRP_SHIFT		24
#घोषणा BAM_NON_PIPE_GRP_MASK		0xFF

/* BAM CNFG BITS */
#घोषणा BAM_PIPE_CNFG		BIT(2)
#घोषणा BAM_FULL_PIPE		BIT(11)
#घोषणा BAM_NO_EXT_P_RST	BIT(12)
#घोषणा BAM_IBC_DISABLE		BIT(13)
#घोषणा BAM_SB_CLK_REQ		BIT(14)
#घोषणा BAM_PSM_CSW_REQ		BIT(15)
#घोषणा BAM_PSM_P_RES		BIT(16)
#घोषणा BAM_AU_P_RES		BIT(17)
#घोषणा BAM_SI_P_RES		BIT(18)
#घोषणा BAM_WB_P_RES		BIT(19)
#घोषणा BAM_WB_BLK_CSW		BIT(20)
#घोषणा BAM_WB_CSW_ACK_IDL	BIT(21)
#घोषणा BAM_WB_RETR_SVPNT	BIT(22)
#घोषणा BAM_WB_DSC_AVL_P_RST	BIT(23)
#घोषणा BAM_REG_P_EN		BIT(24)
#घोषणा BAM_PSM_P_HD_DATA	BIT(25)
#घोषणा BAM_AU_ACCUMED		BIT(26)
#घोषणा BAM_CMD_ENABLE		BIT(27)

#घोषणा BAM_CNFG_BITS_DEFAULT	(BAM_PIPE_CNFG |	\
				 BAM_NO_EXT_P_RST |	\
				 BAM_IBC_DISABLE |	\
				 BAM_SB_CLK_REQ |	\
				 BAM_PSM_CSW_REQ |	\
				 BAM_PSM_P_RES |	\
				 BAM_AU_P_RES |		\
				 BAM_SI_P_RES |		\
				 BAM_WB_P_RES |		\
				 BAM_WB_BLK_CSW |	\
				 BAM_WB_CSW_ACK_IDL |	\
				 BAM_WB_RETR_SVPNT |	\
				 BAM_WB_DSC_AVL_P_RST |	\
				 BAM_REG_P_EN |		\
				 BAM_PSM_P_HD_DATA |	\
				 BAM_AU_ACCUMED |	\
				 BAM_CMD_ENABLE)

/* PIPE CTRL */
#घोषणा P_EN			BIT(1)
#घोषणा P_सूचीECTION		BIT(3)
#घोषणा P_SYS_STRM		BIT(4)
#घोषणा P_SYS_MODE		BIT(5)
#घोषणा P_AUTO_EOB		BIT(6)
#घोषणा P_AUTO_EOB_SEL_SHIFT	7
#घोषणा P_AUTO_EOB_SEL_512	(0 << P_AUTO_EOB_SEL_SHIFT)
#घोषणा P_AUTO_EOB_SEL_256	(1 << P_AUTO_EOB_SEL_SHIFT)
#घोषणा P_AUTO_EOB_SEL_128	(2 << P_AUTO_EOB_SEL_SHIFT)
#घोषणा P_AUTO_EOB_SEL_64	(3 << P_AUTO_EOB_SEL_SHIFT)
#घोषणा P_PREFETCH_LIMIT_SHIFT	9
#घोषणा P_PREFETCH_LIMIT_32	(0 << P_PREFETCH_LIMIT_SHIFT)
#घोषणा P_PREFETCH_LIMIT_16	(1 << P_PREFETCH_LIMIT_SHIFT)
#घोषणा P_PREFETCH_LIMIT_4	(2 << P_PREFETCH_LIMIT_SHIFT)
#घोषणा P_WRITE_NWD		BIT(11)
#घोषणा P_LOCK_GROUP_SHIFT	16
#घोषणा P_LOCK_GROUP_MASK	0x1F

/* BAM_DESC_CNT_TRSHLD */
#घोषणा CNT_TRSHLD		0xffff
#घोषणा DEFAULT_CNT_THRSHLD	0x4

/* BAM_IRQ_SRCS */
#घोषणा BAM_IRQ			BIT(31)
#घोषणा P_IRQ			0x7fffffff

/* BAM_IRQ_SRCS_MSK */
#घोषणा BAM_IRQ_MSK		BAM_IRQ
#घोषणा P_IRQ_MSK		P_IRQ

/* BAM_IRQ_STTS */
#घोषणा BAM_TIMER_IRQ		BIT(4)
#घोषणा BAM_EMPTY_IRQ		BIT(3)
#घोषणा BAM_ERROR_IRQ		BIT(2)
#घोषणा BAM_HRESP_ERR_IRQ	BIT(1)

/* BAM_IRQ_CLR */
#घोषणा BAM_TIMER_CLR		BIT(4)
#घोषणा BAM_EMPTY_CLR		BIT(3)
#घोषणा BAM_ERROR_CLR		BIT(2)
#घोषणा BAM_HRESP_ERR_CLR	BIT(1)

/* BAM_IRQ_EN */
#घोषणा BAM_TIMER_EN		BIT(4)
#घोषणा BAM_EMPTY_EN		BIT(3)
#घोषणा BAM_ERROR_EN		BIT(2)
#घोषणा BAM_HRESP_ERR_EN	BIT(1)

/* BAM_P_IRQ_EN */
#घोषणा P_PRCSD_DESC_EN		BIT(0)
#घोषणा P_TIMER_EN		BIT(1)
#घोषणा P_WAKE_EN		BIT(2)
#घोषणा P_OUT_OF_DESC_EN	BIT(3)
#घोषणा P_ERR_EN		BIT(4)
#घोषणा P_TRNSFR_END_EN		BIT(5)
#घोषणा P_DEFAULT_IRQS_EN	(P_PRCSD_DESC_EN | P_ERR_EN | P_TRNSFR_END_EN)

/* BAM_P_SW_OFSTS */
#घोषणा P_SW_OFSTS_MASK		0xffff

#घोषणा BAM_DESC_FIFO_SIZE	SZ_32K
#घोषणा MAX_DESCRIPTORS (BAM_DESC_FIFO_SIZE / माप(काष्ठा bam_desc_hw) - 1)
#घोषणा BAM_FIFO_SIZE	(SZ_32K - 8)
#घोषणा IS_BUSY(chan)	(CIRC_SPACE(bchan->tail, bchan->head,\
			 MAX_DESCRIPTORS + 1) == 0)

काष्ठा bam_chan अणु
	काष्ठा virt_dma_chan vc;

	काष्ठा bam_device *bdev;

	/* configuration from device tree */
	u32 id;

	/* runसमय configuration */
	काष्ठा dma_slave_config slave;

	/* fअगरo storage */
	काष्ठा bam_desc_hw *fअगरo_virt;
	dma_addr_t fअगरo_phys;

	/* fअगरo markers */
	अचिन्हित लघु head;		/* start of active descriptor entries */
	अचिन्हित लघु tail;		/* end of active descriptor entries */

	अचिन्हित पूर्णांक initialized;	/* is the channel hw initialized? */
	अचिन्हित पूर्णांक छोड़ोd;		/* is the channel छोड़ोd? */
	अचिन्हित पूर्णांक reconfigure;	/* new slave config? */
	/* list of descriptors currently processed */
	काष्ठा list_head desc_list;

	काष्ठा list_head node;
पूर्ण;

अटल अंतरभूत काष्ठा bam_chan *to_bam_chan(काष्ठा dma_chan *common)
अणु
	वापस container_of(common, काष्ठा bam_chan, vc.chan);
पूर्ण

काष्ठा bam_device अणु
	व्योम __iomem *regs;
	काष्ठा device *dev;
	काष्ठा dma_device common;
	काष्ठा bam_chan *channels;
	u32 num_channels;
	u32 num_ees;

	/* execution environment ID, from DT */
	u32 ee;
	bool controlled_remotely;

	स्थिर काष्ठा reg_offset_data *layout;

	काष्ठा clk *bamclk;
	पूर्णांक irq;

	/* dma start transaction tasklet */
	काष्ठा tasklet_काष्ठा task;
पूर्ण;

/**
 * bam_addr - वापसs BAM रेजिस्टर address
 * @bdev: bam device
 * @pipe: pipe instance (ignored when रेजिस्टर करोesn't have multiple instances)
 * @reg:  रेजिस्टर क्रमागत
 */
अटल अंतरभूत व्योम __iomem *bam_addr(काष्ठा bam_device *bdev, u32 pipe,
		क्रमागत bam_reg reg)
अणु
	स्थिर काष्ठा reg_offset_data r = bdev->layout[reg];

	वापस bdev->regs + r.base_offset +
		r.pipe_mult * pipe +
		r.evnt_mult * pipe +
		r.ee_mult * bdev->ee;
पूर्ण

/**
 * bam_reset_channel - Reset inभागidual BAM DMA channel
 * @bchan: bam channel
 *
 * This function resets a specअगरic BAM channel
 */
अटल व्योम bam_reset_channel(काष्ठा bam_chan *bchan)
अणु
	काष्ठा bam_device *bdev = bchan->bdev;

	lockdep_निश्चित_held(&bchan->vc.lock);

	/* reset channel */
	ग_लिखोl_relaxed(1, bam_addr(bdev, bchan->id, BAM_P_RST));
	ग_लिखोl_relaxed(0, bam_addr(bdev, bchan->id, BAM_P_RST));

	/* करोn't allow cpu to reorder BAM रेजिस्टर accesses करोne after this */
	wmb();

	/* make sure hw is initialized when channel is used the first समय  */
	bchan->initialized = 0;
पूर्ण

/**
 * bam_chan_init_hw - Initialize channel hardware
 * @bchan: bam channel
 * @dir: DMA transfer direction
 *
 * This function resets and initializes the BAM channel
 */
अटल व्योम bam_chan_init_hw(काष्ठा bam_chan *bchan,
	क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा bam_device *bdev = bchan->bdev;
	u32 val;

	/* Reset the channel to clear पूर्णांकernal state of the FIFO */
	bam_reset_channel(bchan);

	/*
	 * ग_लिखो out 8 byte aligned address.  We have enough space क्रम this
	 * because we allocated 1 more descriptor (8 bytes) than we can use
	 */
	ग_लिखोl_relaxed(ALIGN(bchan->fअगरo_phys, माप(काष्ठा bam_desc_hw)),
			bam_addr(bdev, bchan->id, BAM_P_DESC_FIFO_ADDR));
	ग_लिखोl_relaxed(BAM_FIFO_SIZE,
			bam_addr(bdev, bchan->id, BAM_P_FIFO_SIZES));

	/* enable the per pipe पूर्णांकerrupts, enable EOT, ERR, and INT irqs */
	ग_लिखोl_relaxed(P_DEFAULT_IRQS_EN,
			bam_addr(bdev, bchan->id, BAM_P_IRQ_EN));

	/* unmask the specअगरic pipe and EE combo */
	val = पढ़ोl_relaxed(bam_addr(bdev, 0, BAM_IRQ_SRCS_MSK_EE));
	val |= BIT(bchan->id);
	ग_लिखोl_relaxed(val, bam_addr(bdev, 0, BAM_IRQ_SRCS_MSK_EE));

	/* करोn't allow cpu to reorder the channel enable करोne below */
	wmb();

	/* set fixed direction and mode, then enable channel */
	val = P_EN | P_SYS_MODE;
	अगर (dir == DMA_DEV_TO_MEM)
		val |= P_सूचीECTION;

	ग_लिखोl_relaxed(val, bam_addr(bdev, bchan->id, BAM_P_CTRL));

	bchan->initialized = 1;

	/* init FIFO poपूर्णांकers */
	bchan->head = 0;
	bchan->tail = 0;
पूर्ण

/**
 * bam_alloc_chan - Allocate channel resources क्रम DMA channel.
 * @chan: specअगरied channel
 *
 * This function allocates the FIFO descriptor memory
 */
अटल पूर्णांक bam_alloc_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	काष्ठा bam_device *bdev = bchan->bdev;

	अगर (bchan->fअगरo_virt)
		वापस 0;

	/* allocate FIFO descriptor space, but only अगर necessary */
	bchan->fअगरo_virt = dma_alloc_wc(bdev->dev, BAM_DESC_FIFO_SIZE,
					&bchan->fअगरo_phys, GFP_KERNEL);

	अगर (!bchan->fअगरo_virt) अणु
		dev_err(bdev->dev, "Failed to allocate desc fifo\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bam_pm_runसमय_get_sync(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_enabled(dev))
		वापस pm_runसमय_get_sync(dev);

	वापस 0;
पूर्ण

/**
 * bam_मुक्त_chan - Frees dma resources associated with specअगरic channel
 * @chan: specअगरied channel
 *
 * Free the allocated fअगरo descriptor memory and channel resources
 *
 */
अटल व्योम bam_मुक्त_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	काष्ठा bam_device *bdev = bchan->bdev;
	u32 val;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = bam_pm_runसमय_get_sync(bdev->dev);
	अगर (ret < 0)
		वापस;

	vchan_मुक्त_chan_resources(to_virt_chan(chan));

	अगर (!list_empty(&bchan->desc_list)) अणु
		dev_err(bchan->bdev->dev, "Cannot free busy channel\n");
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&bchan->vc.lock, flags);
	bam_reset_channel(bchan);
	spin_unlock_irqrestore(&bchan->vc.lock, flags);

	dma_मुक्त_wc(bdev->dev, BAM_DESC_FIFO_SIZE, bchan->fअगरo_virt,
		    bchan->fअगरo_phys);
	bchan->fअगरo_virt = शून्य;

	/* mask irq क्रम pipe/channel */
	val = पढ़ोl_relaxed(bam_addr(bdev, 0, BAM_IRQ_SRCS_MSK_EE));
	val &= ~BIT(bchan->id);
	ग_लिखोl_relaxed(val, bam_addr(bdev, 0, BAM_IRQ_SRCS_MSK_EE));

	/* disable irq */
	ग_लिखोl_relaxed(0, bam_addr(bdev, bchan->id, BAM_P_IRQ_EN));

err:
	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);
पूर्ण

/**
 * bam_slave_config - set slave configuration क्रम channel
 * @chan: dma channel
 * @cfg: slave configuration
 *
 * Sets slave configuration क्रम channel
 *
 */
अटल पूर्णांक bam_slave_config(काष्ठा dma_chan *chan,
			    काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&bchan->vc.lock, flag);
	स_नकल(&bchan->slave, cfg, माप(*cfg));
	bchan->reconfigure = 1;
	spin_unlock_irqrestore(&bchan->vc.lock, flag);

	वापस 0;
पूर्ण

/**
 * bam_prep_slave_sg - Prep slave sg transaction
 *
 * @chan: dma channel
 * @sgl: scatter gather list
 * @sg_len: length of sg
 * @direction: DMA transfer direction
 * @flags: DMA flags
 * @context: transfer context (unused)
 */
अटल काष्ठा dma_async_tx_descriptor *bam_prep_slave_sg(काष्ठा dma_chan *chan,
	काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags,
	व्योम *context)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	काष्ठा bam_device *bdev = bchan->bdev;
	काष्ठा bam_async_desc *async_desc;
	काष्ठा scatterlist *sg;
	u32 i;
	काष्ठा bam_desc_hw *desc;
	अचिन्हित पूर्णांक num_alloc = 0;


	अगर (!is_slave_direction(direction)) अणु
		dev_err(bdev->dev, "invalid dma direction\n");
		वापस शून्य;
	पूर्ण

	/* calculate number of required entries */
	क्रम_each_sg(sgl, sg, sg_len, i)
		num_alloc += DIV_ROUND_UP(sg_dma_len(sg), BAM_FIFO_SIZE);

	/* allocate enough room to accomodate the number of entries */
	async_desc = kzalloc(काष्ठा_size(async_desc, desc, num_alloc),
			     GFP_NOWAIT);

	अगर (!async_desc)
		वापस शून्य;

	अगर (flags & DMA_PREP_FENCE)
		async_desc->flags |= DESC_FLAG_NWD;

	अगर (flags & DMA_PREP_INTERRUPT)
		async_desc->flags |= DESC_FLAG_EOT;

	async_desc->num_desc = num_alloc;
	async_desc->curr_desc = async_desc->desc;
	async_desc->dir = direction;

	/* fill in temporary descriptors */
	desc = async_desc->desc;
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		अचिन्हित पूर्णांक reमुख्यder = sg_dma_len(sg);
		अचिन्हित पूर्णांक curr_offset = 0;

		करो अणु
			अगर (flags & DMA_PREP_CMD)
				desc->flags |= cpu_to_le16(DESC_FLAG_CMD);

			desc->addr = cpu_to_le32(sg_dma_address(sg) +
						 curr_offset);

			अगर (reमुख्यder > BAM_FIFO_SIZE) अणु
				desc->size = cpu_to_le16(BAM_FIFO_SIZE);
				reमुख्यder -= BAM_FIFO_SIZE;
				curr_offset += BAM_FIFO_SIZE;
			पूर्ण अन्यथा अणु
				desc->size = cpu_to_le16(reमुख्यder);
				reमुख्यder = 0;
			पूर्ण

			async_desc->length += le16_to_cpu(desc->size);
			desc++;
		पूर्ण जबतक (reमुख्यder > 0);
	पूर्ण

	वापस vchan_tx_prep(&bchan->vc, &async_desc->vd, flags);
पूर्ण

/**
 * bam_dma_terminate_all - terminate all transactions on a channel
 * @chan: bam dma channel
 *
 * Dequeues and मुक्तs all transactions
 * No callbacks are करोne
 *
 */
अटल पूर्णांक bam_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	काष्ठा bam_async_desc *async_desc, *पंचांगp;
	अचिन्हित दीर्घ flag;
	LIST_HEAD(head);

	/* हटाओ all transactions, including active transaction */
	spin_lock_irqsave(&bchan->vc.lock, flag);
	/*
	 * If we have transactions queued, then some might be committed to the
	 * hardware in the desc fअगरo.  The only way to reset the desc fअगरo is
	 * to करो a hardware reset (either by pipe or the entire block).
	 * bam_chan_init_hw() will trigger a pipe reset, and also reinit the
	 * pipe.  If the pipe is left disabled (शेष state after pipe reset)
	 * and is accessed by a connected hardware engine, a fatal error in
	 * the BAM will occur.  There is a small winकरोw where this could happen
	 * with bam_chan_init_hw(), but it is assumed that the caller has
	 * stopped activity on any attached hardware engine.  Make sure to करो
	 * this first so that the BAM hardware करोesn't cause memory corruption
	 * by accessing मुक्तd resources.
	 */
	अगर (!list_empty(&bchan->desc_list)) अणु
		async_desc = list_first_entry(&bchan->desc_list,
					      काष्ठा bam_async_desc, desc_node);
		bam_chan_init_hw(bchan, async_desc->dir);
	पूर्ण

	list_क्रम_each_entry_safe(async_desc, पंचांगp,
				 &bchan->desc_list, desc_node) अणु
		list_add(&async_desc->vd.node, &bchan->vc.desc_issued);
		list_del(&async_desc->desc_node);
	पूर्ण

	vchan_get_all_descriptors(&bchan->vc, &head);
	spin_unlock_irqrestore(&bchan->vc.lock, flag);

	vchan_dma_desc_मुक्त_list(&bchan->vc, &head);

	वापस 0;
पूर्ण

/**
 * bam_छोड़ो - Pause DMA channel
 * @chan: dma channel
 *
 */
अटल पूर्णांक bam_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	काष्ठा bam_device *bdev = bchan->bdev;
	अचिन्हित दीर्घ flag;
	पूर्णांक ret;

	ret = bam_pm_runसमय_get_sync(bdev->dev);
	अगर (ret < 0)
		वापस ret;

	spin_lock_irqsave(&bchan->vc.lock, flag);
	ग_लिखोl_relaxed(1, bam_addr(bdev, bchan->id, BAM_P_HALT));
	bchan->छोड़ोd = 1;
	spin_unlock_irqrestore(&bchan->vc.lock, flag);
	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);

	वापस 0;
पूर्ण

/**
 * bam_resume - Resume DMA channel operations
 * @chan: dma channel
 *
 */
अटल पूर्णांक bam_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	काष्ठा bam_device *bdev = bchan->bdev;
	अचिन्हित दीर्घ flag;
	पूर्णांक ret;

	ret = bam_pm_runसमय_get_sync(bdev->dev);
	अगर (ret < 0)
		वापस ret;

	spin_lock_irqsave(&bchan->vc.lock, flag);
	ग_लिखोl_relaxed(0, bam_addr(bdev, bchan->id, BAM_P_HALT));
	bchan->छोड़ोd = 0;
	spin_unlock_irqrestore(&bchan->vc.lock, flag);
	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);

	वापस 0;
पूर्ण

/**
 * process_channel_irqs - processes the channel पूर्णांकerrupts
 * @bdev: bam controller
 *
 * This function processes the channel पूर्णांकerrupts
 *
 */
अटल u32 process_channel_irqs(काष्ठा bam_device *bdev)
अणु
	u32 i, srcs, pipe_stts, offset, avail;
	अचिन्हित दीर्घ flags;
	काष्ठा bam_async_desc *async_desc, *पंचांगp;

	srcs = पढ़ोl_relaxed(bam_addr(bdev, 0, BAM_IRQ_SRCS_EE));

	/* वापस early अगर no pipe/channel पूर्णांकerrupts are present */
	अगर (!(srcs & P_IRQ))
		वापस srcs;

	क्रम (i = 0; i < bdev->num_channels; i++) अणु
		काष्ठा bam_chan *bchan = &bdev->channels[i];

		अगर (!(srcs & BIT(i)))
			जारी;

		/* clear pipe irq */
		pipe_stts = पढ़ोl_relaxed(bam_addr(bdev, i, BAM_P_IRQ_STTS));

		ग_लिखोl_relaxed(pipe_stts, bam_addr(bdev, i, BAM_P_IRQ_CLR));

		spin_lock_irqsave(&bchan->vc.lock, flags);

		offset = पढ़ोl_relaxed(bam_addr(bdev, i, BAM_P_SW_OFSTS)) &
				       P_SW_OFSTS_MASK;
		offset /= माप(काष्ठा bam_desc_hw);

		/* Number of bytes available to पढ़ो */
		avail = CIRC_CNT(offset, bchan->head, MAX_DESCRIPTORS + 1);

		अगर (offset < bchan->head)
			avail--;

		list_क्रम_each_entry_safe(async_desc, पंचांगp,
					 &bchan->desc_list, desc_node) अणु
			/* Not enough data to पढ़ो */
			अगर (avail < async_desc->xfer_len)
				अवरोध;

			/* manage FIFO */
			bchan->head += async_desc->xfer_len;
			bchan->head %= MAX_DESCRIPTORS;

			async_desc->num_desc -= async_desc->xfer_len;
			async_desc->curr_desc += async_desc->xfer_len;
			avail -= async_desc->xfer_len;

			/*
			 * अगर complete, process cookie. Otherwise
			 * push back to front of desc_issued so that
			 * it माला_लो restarted by the tasklet
			 */
			अगर (!async_desc->num_desc) अणु
				vchan_cookie_complete(&async_desc->vd);
			पूर्ण अन्यथा अणु
				list_add(&async_desc->vd.node,
					 &bchan->vc.desc_issued);
			पूर्ण
			list_del(&async_desc->desc_node);
		पूर्ण

		spin_unlock_irqrestore(&bchan->vc.lock, flags);
	पूर्ण

	वापस srcs;
पूर्ण

/**
 * bam_dma_irq - irq handler क्रम bam controller
 * @irq: IRQ of पूर्णांकerrupt
 * @data: callback data
 *
 * IRQ handler क्रम the bam controller
 */
अटल irqवापस_t bam_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bam_device *bdev = data;
	u32 clr_mask = 0, srcs = 0;
	पूर्णांक ret;

	srcs |= process_channel_irqs(bdev);

	/* kick off tasklet to start next dma transfer */
	अगर (srcs & P_IRQ)
		tasklet_schedule(&bdev->task);

	ret = bam_pm_runसमय_get_sync(bdev->dev);
	अगर (ret < 0)
		वापस IRQ_NONE;

	अगर (srcs & BAM_IRQ) अणु
		clr_mask = पढ़ोl_relaxed(bam_addr(bdev, 0, BAM_IRQ_STTS));

		/*
		 * करोn't allow reorder of the various accesses to the BAM
		 * रेजिस्टरs
		 */
		mb();

		ग_लिखोl_relaxed(clr_mask, bam_addr(bdev, 0, BAM_IRQ_CLR));
	पूर्ण

	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * bam_tx_status - वापसs status of transaction
 * @chan: dma channel
 * @cookie: transaction cookie
 * @txstate: DMA transaction state
 *
 * Return status of dma transaction
 */
अटल क्रमागत dma_status bam_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
		काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	काष्ठा bam_async_desc *async_desc;
	काष्ठा virt_dma_desc *vd;
	पूर्णांक ret;
	माप_प्रकार residue = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	अगर (!txstate)
		वापस bchan->छोड़ोd ? DMA_PAUSED : ret;

	spin_lock_irqsave(&bchan->vc.lock, flags);
	vd = vchan_find_desc(&bchan->vc, cookie);
	अगर (vd) अणु
		residue = container_of(vd, काष्ठा bam_async_desc, vd)->length;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(async_desc, &bchan->desc_list, desc_node) अणु
			अगर (async_desc->vd.tx.cookie != cookie)
				जारी;

			क्रम (i = 0; i < async_desc->num_desc; i++)
				residue += le16_to_cpu(
						async_desc->curr_desc[i].size);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&bchan->vc.lock, flags);

	dma_set_residue(txstate, residue);

	अगर (ret == DMA_IN_PROGRESS && bchan->छोड़ोd)
		ret = DMA_PAUSED;

	वापस ret;
पूर्ण

/**
 * bam_apply_new_config
 * @bchan: bam dma channel
 * @dir: DMA direction
 */
अटल व्योम bam_apply_new_config(काष्ठा bam_chan *bchan,
	क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा bam_device *bdev = bchan->bdev;
	u32 maxburst;

	अगर (!bdev->controlled_remotely) अणु
		अगर (dir == DMA_DEV_TO_MEM)
			maxburst = bchan->slave.src_maxburst;
		अन्यथा
			maxburst = bchan->slave.dst_maxburst;

		ग_लिखोl_relaxed(maxburst,
			       bam_addr(bdev, 0, BAM_DESC_CNT_TRSHLD));
	पूर्ण

	bchan->reconfigure = 0;
पूर्ण

/**
 * bam_start_dma - start next transaction
 * @bchan: bam dma channel
 */
अटल व्योम bam_start_dma(काष्ठा bam_chan *bchan)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&bchan->vc);
	काष्ठा bam_device *bdev = bchan->bdev;
	काष्ठा bam_async_desc *async_desc = शून्य;
	काष्ठा bam_desc_hw *desc;
	काष्ठा bam_desc_hw *fअगरo = PTR_ALIGN(bchan->fअगरo_virt,
					माप(काष्ठा bam_desc_hw));
	पूर्णांक ret;
	अचिन्हित पूर्णांक avail;
	काष्ठा dmaengine_desc_callback cb;

	lockdep_निश्चित_held(&bchan->vc.lock);

	अगर (!vd)
		वापस;

	ret = bam_pm_runसमय_get_sync(bdev->dev);
	अगर (ret < 0)
		वापस;

	जबतक (vd && !IS_BUSY(bchan)) अणु
		list_del(&vd->node);

		async_desc = container_of(vd, काष्ठा bam_async_desc, vd);

		/* on first use, initialize the channel hardware */
		अगर (!bchan->initialized)
			bam_chan_init_hw(bchan, async_desc->dir);

		/* apply new slave config changes, अगर necessary */
		अगर (bchan->reconfigure)
			bam_apply_new_config(bchan, async_desc->dir);

		desc = async_desc->curr_desc;
		avail = CIRC_SPACE(bchan->tail, bchan->head,
				   MAX_DESCRIPTORS + 1);

		अगर (async_desc->num_desc > avail)
			async_desc->xfer_len = avail;
		अन्यथा
			async_desc->xfer_len = async_desc->num_desc;

		/* set any special flags on the last descriptor */
		अगर (async_desc->num_desc == async_desc->xfer_len)
			desc[async_desc->xfer_len - 1].flags |=
						cpu_to_le16(async_desc->flags);

		vd = vchan_next_desc(&bchan->vc);

		dmaengine_desc_get_callback(&async_desc->vd.tx, &cb);

		/*
		 * An पूर्णांकerrupt is generated at this desc, अगर
		 *  - FIFO is FULL.
		 *  - No more descriptors to add.
		 *  - If a callback completion was requested क्रम this DESC,
		 *     In this हाल, BAM will deliver the completion callback
		 *     क्रम this desc and जारी processing the next desc.
		 */
		अगर (((avail <= async_desc->xfer_len) || !vd ||
		     dmaengine_desc_callback_valid(&cb)) &&
		    !(async_desc->flags & DESC_FLAG_EOT))
			desc[async_desc->xfer_len - 1].flags |=
				cpu_to_le16(DESC_FLAG_INT);

		अगर (bchan->tail + async_desc->xfer_len > MAX_DESCRIPTORS) अणु
			u32 partial = MAX_DESCRIPTORS - bchan->tail;

			स_नकल(&fअगरo[bchan->tail], desc,
			       partial * माप(काष्ठा bam_desc_hw));
			स_नकल(fअगरo, &desc[partial],
			       (async_desc->xfer_len - partial) *
				माप(काष्ठा bam_desc_hw));
		पूर्ण अन्यथा अणु
			स_नकल(&fअगरo[bchan->tail], desc,
			       async_desc->xfer_len *
			       माप(काष्ठा bam_desc_hw));
		पूर्ण

		bchan->tail += async_desc->xfer_len;
		bchan->tail %= MAX_DESCRIPTORS;
		list_add_tail(&async_desc->desc_node, &bchan->desc_list);
	पूर्ण

	/* ensure descriptor ग_लिखोs and dma start not reordered */
	wmb();
	ग_लिखोl_relaxed(bchan->tail * माप(काष्ठा bam_desc_hw),
			bam_addr(bdev, bchan->id, BAM_P_EVNT_REG));

	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);
पूर्ण

/**
 * dma_tasklet - DMA IRQ tasklet
 * @t: tasklet argument (bam controller काष्ठाure)
 *
 * Sets up next DMA operation and then processes all completed transactions
 */
अटल व्योम dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा bam_device *bdev = from_tasklet(bdev, t, task);
	काष्ठा bam_chan *bchan;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/* go through the channels and kick off transactions */
	क्रम (i = 0; i < bdev->num_channels; i++) अणु
		bchan = &bdev->channels[i];
		spin_lock_irqsave(&bchan->vc.lock, flags);

		अगर (!list_empty(&bchan->vc.desc_issued) && !IS_BUSY(bchan))
			bam_start_dma(bchan);
		spin_unlock_irqrestore(&bchan->vc.lock, flags);
	पूर्ण

पूर्ण

/**
 * bam_issue_pending - starts pending transactions
 * @chan: dma channel
 *
 * Calls tasklet directly which in turn starts any pending transactions
 */
अटल व्योम bam_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा bam_chan *bchan = to_bam_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bchan->vc.lock, flags);

	/* अगर work pending and idle, start a transaction */
	अगर (vchan_issue_pending(&bchan->vc) && !IS_BUSY(bchan))
		bam_start_dma(bchan);

	spin_unlock_irqrestore(&bchan->vc.lock, flags);
पूर्ण

/**
 * bam_dma_मुक्त_desc - मुक्त descriptor memory
 * @vd: भव descriptor
 *
 */
अटल व्योम bam_dma_मुक्त_desc(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा bam_async_desc *async_desc = container_of(vd,
			काष्ठा bam_async_desc, vd);

	kमुक्त(async_desc);
पूर्ण

अटल काष्ठा dma_chan *bam_dma_xlate(काष्ठा of_phandle_args *dma_spec,
		काष्ठा of_dma *of)
अणु
	काष्ठा bam_device *bdev = container_of(of->of_dma_data,
					काष्ठा bam_device, common);
	अचिन्हित पूर्णांक request;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	request = dma_spec->args[0];
	अगर (request >= bdev->num_channels)
		वापस शून्य;

	वापस dma_get_slave_channel(&(bdev->channels[request].vc.chan));
पूर्ण

/**
 * bam_init
 * @bdev: bam device
 *
 * Initialization helper क्रम global bam रेजिस्टरs
 */
अटल पूर्णांक bam_init(काष्ठा bam_device *bdev)
अणु
	u32 val;

	/* पढ़ो revision and configuration inक्रमmation */
	अगर (!bdev->num_ees) अणु
		val = पढ़ोl_relaxed(bam_addr(bdev, 0, BAM_REVISION));
		bdev->num_ees = (val >> NUM_EES_SHIFT) & NUM_EES_MASK;
	पूर्ण

	/* check that configured EE is within range */
	अगर (bdev->ee >= bdev->num_ees)
		वापस -EINVAL;

	अगर (!bdev->num_channels) अणु
		val = पढ़ोl_relaxed(bam_addr(bdev, 0, BAM_NUM_PIPES));
		bdev->num_channels = val & BAM_NUM_PIPES_MASK;
	पूर्ण

	अगर (bdev->controlled_remotely)
		वापस 0;

	/* s/w reset bam */
	/* after reset all pipes are disabled and idle */
	val = पढ़ोl_relaxed(bam_addr(bdev, 0, BAM_CTRL));
	val |= BAM_SW_RST;
	ग_लिखोl_relaxed(val, bam_addr(bdev, 0, BAM_CTRL));
	val &= ~BAM_SW_RST;
	ग_लिखोl_relaxed(val, bam_addr(bdev, 0, BAM_CTRL));

	/* make sure previous stores are visible beक्रमe enabling BAM */
	wmb();

	/* enable bam */
	val |= BAM_EN;
	ग_लिखोl_relaxed(val, bam_addr(bdev, 0, BAM_CTRL));

	/* set descriptor threshhold, start with 4 bytes */
	ग_लिखोl_relaxed(DEFAULT_CNT_THRSHLD,
			bam_addr(bdev, 0, BAM_DESC_CNT_TRSHLD));

	/* Enable शेष set of h/w workarounds, ie all except BAM_FULL_PIPE */
	ग_लिखोl_relaxed(BAM_CNFG_BITS_DEFAULT, bam_addr(bdev, 0, BAM_CNFG_BITS));

	/* enable irqs क्रम errors */
	ग_लिखोl_relaxed(BAM_ERROR_EN | BAM_HRESP_ERR_EN,
			bam_addr(bdev, 0, BAM_IRQ_EN));

	/* unmask global bam पूर्णांकerrupt */
	ग_लिखोl_relaxed(BAM_IRQ_MSK, bam_addr(bdev, 0, BAM_IRQ_SRCS_MSK_EE));

	वापस 0;
पूर्ण

अटल व्योम bam_channel_init(काष्ठा bam_device *bdev, काष्ठा bam_chan *bchan,
	u32 index)
अणु
	bchan->id = index;
	bchan->bdev = bdev;

	vchan_init(&bchan->vc, &bdev->common);
	bchan->vc.desc_मुक्त = bam_dma_मुक्त_desc;
	INIT_LIST_HEAD(&bchan->desc_list);
पूर्ण

अटल स्थिर काष्ठा of_device_id bam_of_match[] = अणु
	अणु .compatible = "qcom,bam-v1.3.0", .data = &bam_v1_3_reg_info पूर्ण,
	अणु .compatible = "qcom,bam-v1.4.0", .data = &bam_v1_4_reg_info पूर्ण,
	अणु .compatible = "qcom,bam-v1.7.0", .data = &bam_v1_7_reg_info पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, bam_of_match);

अटल पूर्णांक bam_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bam_device *bdev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *iores;
	पूर्णांक ret, i;

	bdev = devm_kzalloc(&pdev->dev, माप(*bdev), GFP_KERNEL);
	अगर (!bdev)
		वापस -ENOMEM;

	bdev->dev = &pdev->dev;

	match = of_match_node(bam_of_match, pdev->dev.of_node);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Unsupported BAM module\n");
		वापस -ENODEV;
	पूर्ण

	bdev->layout = match->data;

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	bdev->regs = devm_ioremap_resource(&pdev->dev, iores);
	अगर (IS_ERR(bdev->regs))
		वापस PTR_ERR(bdev->regs);

	bdev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (bdev->irq < 0)
		वापस bdev->irq;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "qcom,ee", &bdev->ee);
	अगर (ret) अणु
		dev_err(bdev->dev, "Execution environment unspecified\n");
		वापस ret;
	पूर्ण

	bdev->controlled_remotely = of_property_पढ़ो_bool(pdev->dev.of_node,
						"qcom,controlled-remotely");

	अगर (bdev->controlled_remotely) अणु
		ret = of_property_पढ़ो_u32(pdev->dev.of_node, "num-channels",
					   &bdev->num_channels);
		अगर (ret)
			dev_err(bdev->dev, "num-channels unspecified in dt\n");

		ret = of_property_पढ़ो_u32(pdev->dev.of_node, "qcom,num-ees",
					   &bdev->num_ees);
		अगर (ret)
			dev_err(bdev->dev, "num-ees unspecified in dt\n");
	पूर्ण

	अगर (bdev->controlled_remotely)
		bdev->bamclk = devm_clk_get_optional(bdev->dev, "bam_clk");
	अन्यथा
		bdev->bamclk = devm_clk_get(bdev->dev, "bam_clk");

	अगर (IS_ERR(bdev->bamclk))
		वापस PTR_ERR(bdev->bamclk);

	ret = clk_prepare_enable(bdev->bamclk);
	अगर (ret) अणु
		dev_err(bdev->dev, "failed to prepare/enable clock\n");
		वापस ret;
	पूर्ण

	ret = bam_init(bdev);
	अगर (ret)
		जाओ err_disable_clk;

	tasklet_setup(&bdev->task, dma_tasklet);

	bdev->channels = devm_kसुस्मृति(bdev->dev, bdev->num_channels,
				माप(*bdev->channels), GFP_KERNEL);

	अगर (!bdev->channels) अणु
		ret = -ENOMEM;
		जाओ err_tasklet_समाप्त;
	पूर्ण

	/* allocate and initialize channels */
	INIT_LIST_HEAD(&bdev->common.channels);

	क्रम (i = 0; i < bdev->num_channels; i++)
		bam_channel_init(bdev, &bdev->channels[i], i);

	ret = devm_request_irq(bdev->dev, bdev->irq, bam_dma_irq,
			IRQF_TRIGGER_HIGH, "bam_dma", bdev);
	अगर (ret)
		जाओ err_bam_channel_निकास;

	/* set max dma segment size */
	bdev->common.dev = bdev->dev;
	ret = dma_set_max_seg_size(bdev->common.dev, BAM_FIFO_SIZE);
	अगर (ret) अणु
		dev_err(bdev->dev, "cannot set maximum segment size\n");
		जाओ err_bam_channel_निकास;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bdev);

	/* set capabilities */
	dma_cap_zero(bdev->common.cap_mask);
	dma_cap_set(DMA_SLAVE, bdev->common.cap_mask);

	/* initialize dmaengine apis */
	bdev->common.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	bdev->common.residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	bdev->common.src_addr_widths = DMA_SLAVE_BUSWIDTH_4_BYTES;
	bdev->common.dst_addr_widths = DMA_SLAVE_BUSWIDTH_4_BYTES;
	bdev->common.device_alloc_chan_resources = bam_alloc_chan;
	bdev->common.device_मुक्त_chan_resources = bam_मुक्त_chan;
	bdev->common.device_prep_slave_sg = bam_prep_slave_sg;
	bdev->common.device_config = bam_slave_config;
	bdev->common.device_छोड़ो = bam_छोड़ो;
	bdev->common.device_resume = bam_resume;
	bdev->common.device_terminate_all = bam_dma_terminate_all;
	bdev->common.device_issue_pending = bam_issue_pending;
	bdev->common.device_tx_status = bam_tx_status;
	bdev->common.dev = bdev->dev;

	ret = dma_async_device_रेजिस्टर(&bdev->common);
	अगर (ret) अणु
		dev_err(bdev->dev, "failed to register dma async device\n");
		जाओ err_bam_channel_निकास;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node, bam_dma_xlate,
					&bdev->common);
	अगर (ret)
		जाओ err_unरेजिस्टर_dma;

	अगर (!bdev->bamclk) अणु
		pm_runसमय_disable(&pdev->dev);
		वापस 0;
	पूर्ण

	pm_runसमय_irq_safe(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, BAM_DMA_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;

err_unरेजिस्टर_dma:
	dma_async_device_unरेजिस्टर(&bdev->common);
err_bam_channel_निकास:
	क्रम (i = 0; i < bdev->num_channels; i++)
		tasklet_समाप्त(&bdev->channels[i].vc.task);
err_tasklet_समाप्त:
	tasklet_समाप्त(&bdev->task);
err_disable_clk:
	clk_disable_unprepare(bdev->bamclk);

	वापस ret;
पूर्ण

अटल पूर्णांक bam_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bam_device *bdev = platक्रमm_get_drvdata(pdev);
	u32 i;

	pm_runसमय_क्रमce_suspend(&pdev->dev);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&bdev->common);

	/* mask all पूर्णांकerrupts क्रम this execution environment */
	ग_लिखोl_relaxed(0, bam_addr(bdev, 0,  BAM_IRQ_SRCS_MSK_EE));

	devm_मुक्त_irq(bdev->dev, bdev->irq, bdev);

	क्रम (i = 0; i < bdev->num_channels; i++) अणु
		bam_dma_terminate_all(&bdev->channels[i].vc.chan);
		tasklet_समाप्त(&bdev->channels[i].vc.task);

		अगर (!bdev->channels[i].fअगरo_virt)
			जारी;

		dma_मुक्त_wc(bdev->dev, BAM_DESC_FIFO_SIZE,
			    bdev->channels[i].fअगरo_virt,
			    bdev->channels[i].fअगरo_phys);
	पूर्ण

	tasklet_समाप्त(&bdev->task);

	clk_disable_unprepare(bdev->bamclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bam_dma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा bam_device *bdev = dev_get_drvdata(dev);

	clk_disable(bdev->bamclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bam_dma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा bam_device *bdev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(bdev->bamclk);
	अगर (ret < 0) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bam_dma_suspend(काष्ठा device *dev)
अणु
	काष्ठा bam_device *bdev = dev_get_drvdata(dev);

	अगर (bdev->bamclk) अणु
		pm_runसमय_क्रमce_suspend(dev);
		clk_unprepare(bdev->bamclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bam_dma_resume(काष्ठा device *dev)
अणु
	काष्ठा bam_device *bdev = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (bdev->bamclk) अणु
		ret = clk_prepare(bdev->bamclk);
		अगर (ret)
			वापस ret;

		pm_runसमय_क्रमce_resume(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops bam_dma_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(bam_dma_suspend, bam_dma_resume)
	SET_RUNTIME_PM_OPS(bam_dma_runसमय_suspend, bam_dma_runसमय_resume,
				शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver bam_dma_driver = अणु
	.probe = bam_dma_probe,
	.हटाओ = bam_dma_हटाओ,
	.driver = अणु
		.name = "bam-dma-engine",
		.pm = &bam_dma_pm_ops,
		.of_match_table = bam_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bam_dma_driver);

MODULE_AUTHOR("Andy Gross <agross@codeaurora.org>");
MODULE_DESCRIPTION("QCOM BAM DMA engine driver");
MODULE_LICENSE("GPL v2");
