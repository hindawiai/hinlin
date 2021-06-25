<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_INCLUDE_MFD_IMX25_TSADC_H_
#घोषणा _LINUX_INCLUDE_MFD_IMX25_TSADC_H_

काष्ठा regmap;
काष्ठा clk;

काष्ठा mx25_tsadc अणु
	काष्ठा regmap *regs;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा MX25_TSC_TGCR			0x00
#घोषणा MX25_TSC_TGSR			0x04
#घोषणा MX25_TSC_TICR			0x08

/* The same रेजिस्टर layout क्रम TC and GC queue */
#घोषणा MX25_ADCQ_FIFO			0x00
#घोषणा MX25_ADCQ_CR			0x04
#घोषणा MX25_ADCQ_SR			0x08
#घोषणा MX25_ADCQ_MR			0x0c
#घोषणा MX25_ADCQ_ITEM_7_0		0x20
#घोषणा MX25_ADCQ_ITEM_15_8		0x24
#घोषणा MX25_ADCQ_CFG(n)		(0x40 + ((n) * 0x4))

#घोषणा MX25_ADCQ_MR_MASK		0xffffffff

/* TGCR */
#घोषणा MX25_TGCR_PDBTIME(x)		((x) << 25)
#घोषणा MX25_TGCR_PDBTIME_MASK		GENMASK(31, 25)
#घोषणा MX25_TGCR_PDBEN			BIT(24)
#घोषणा MX25_TGCR_PDEN			BIT(23)
#घोषणा MX25_TGCR_ADCCLKCFG(x)		((x) << 16)
#घोषणा MX25_TGCR_GET_ADCCLK(x)		(((x) >> 16) & 0x1f)
#घोषणा MX25_TGCR_INTREFEN		BIT(10)
#घोषणा MX25_TGCR_POWERMODE_MASK	GENMASK(9, 8)
#घोषणा MX25_TGCR_POWERMODE_SAVE	(1 << 8)
#घोषणा MX25_TGCR_POWERMODE_ON		(2 << 8)
#घोषणा MX25_TGCR_STLC			BIT(5)
#घोषणा MX25_TGCR_SLPC			BIT(4)
#घोषणा MX25_TGCR_FUNC_RST		BIT(2)
#घोषणा MX25_TGCR_TSC_RST		BIT(1)
#घोषणा MX25_TGCR_CLK_EN		BIT(0)

/* TGSR */
#घोषणा MX25_TGSR_SLP_INT		BIT(2)
#घोषणा MX25_TGSR_GCQ_INT		BIT(1)
#घोषणा MX25_TGSR_TCQ_INT		BIT(0)

/* ADCQ_ITEM_* */
#घोषणा _MX25_ADCQ_ITEM(item, x)	((x) << ((item) * 4))
#घोषणा MX25_ADCQ_ITEM(item, x)		((item) >= 8 ? \
		_MX25_ADCQ_ITEM((item) - 8, (x)) : _MX25_ADCQ_ITEM((item), (x)))

/* ADCQ_FIFO (TCQFIFO and GCQFIFO) */
#घोषणा MX25_ADCQ_FIFO_DATA(x)		(((x) >> 4) & 0xfff)
#घोषणा MX25_ADCQ_FIFO_ID(x)		((x) & 0xf)

/* ADCQ_CR (TCQR and GCQR) */
#घोषणा MX25_ADCQ_CR_PDCFG_LEVEL	BIT(19)
#घोषणा MX25_ADCQ_CR_PDMSK		BIT(18)
#घोषणा MX25_ADCQ_CR_FRST		BIT(17)
#घोषणा MX25_ADCQ_CR_QRST		BIT(16)
#घोषणा MX25_ADCQ_CR_RWAIT_MASK		GENMASK(15, 12)
#घोषणा MX25_ADCQ_CR_RWAIT(x)		((x) << 12)
#घोषणा MX25_ADCQ_CR_WMRK_MASK		GENMASK(11, 8)
#घोषणा MX25_ADCQ_CR_WMRK(x)		((x) << 8)
#घोषणा MX25_ADCQ_CR_LITEMID_MASK	(0xf << 4)
#घोषणा MX25_ADCQ_CR_LITEMID(x)		((x) << 4)
#घोषणा MX25_ADCQ_CR_RPT		BIT(3)
#घोषणा MX25_ADCQ_CR_FQS		BIT(2)
#घोषणा MX25_ADCQ_CR_QSM_MASK		GENMASK(1, 0)
#घोषणा MX25_ADCQ_CR_QSM_PD		0x1
#घोषणा MX25_ADCQ_CR_QSM_FQS		0x2
#घोषणा MX25_ADCQ_CR_QSM_FQS_PD		0x3

/* ADCQ_SR (TCQSR and GCQSR) */
#घोषणा MX25_ADCQ_SR_FDRY		BIT(15)
#घोषणा MX25_ADCQ_SR_FULL		BIT(14)
#घोषणा MX25_ADCQ_SR_EMPT		BIT(13)
#घोषणा MX25_ADCQ_SR_FDN(x)		(((x) >> 8) & 0x1f)
#घोषणा MX25_ADCQ_SR_FRR		BIT(6)
#घोषणा MX25_ADCQ_SR_FUR		BIT(5)
#घोषणा MX25_ADCQ_SR_FOR		BIT(4)
#घोषणा MX25_ADCQ_SR_EOQ		BIT(1)
#घोषणा MX25_ADCQ_SR_PD			BIT(0)

/* ADCQ_MR (TCQMR and GCQMR) */
#घोषणा MX25_ADCQ_MR_FDRY_DMA		BIT(31)
#घोषणा MX25_ADCQ_MR_FER_DMA		BIT(22)
#घोषणा MX25_ADCQ_MR_FUR_DMA		BIT(21)
#घोषणा MX25_ADCQ_MR_FOR_DMA		BIT(20)
#घोषणा MX25_ADCQ_MR_EOQ_DMA		BIT(17)
#घोषणा MX25_ADCQ_MR_PD_DMA		BIT(16)
#घोषणा MX25_ADCQ_MR_FDRY_IRQ		BIT(15)
#घोषणा MX25_ADCQ_MR_FER_IRQ		BIT(6)
#घोषणा MX25_ADCQ_MR_FUR_IRQ		BIT(5)
#घोषणा MX25_ADCQ_MR_FOR_IRQ		BIT(4)
#घोषणा MX25_ADCQ_MR_EOQ_IRQ		BIT(1)
#घोषणा MX25_ADCQ_MR_PD_IRQ		BIT(0)

/* ADCQ_CFG (TICR, TCC0-7,GCC0-7) */
#घोषणा MX25_ADCQ_CFG_SETTLING_TIME(x)	((x) << 24)
#घोषणा MX25_ADCQ_CFG_IGS		(1 << 20)
#घोषणा MX25_ADCQ_CFG_NOS_MASK		GENMASK(19, 16)
#घोषणा MX25_ADCQ_CFG_NOS(x)		(((x) - 1) << 16)
#घोषणा MX25_ADCQ_CFG_WIPER		(1 << 15)
#घोषणा MX25_ADCQ_CFG_YNLR		(1 << 14)
#घोषणा MX25_ADCQ_CFG_YPLL_HIGH		(0 << 12)
#घोषणा MX25_ADCQ_CFG_YPLL_OFF		(1 << 12)
#घोषणा MX25_ADCQ_CFG_YPLL_LOW		(3 << 12)
#घोषणा MX25_ADCQ_CFG_XNUR_HIGH		(0 << 10)
#घोषणा MX25_ADCQ_CFG_XNUR_OFF		(1 << 10)
#घोषणा MX25_ADCQ_CFG_XNUR_LOW		(3 << 10)
#घोषणा MX25_ADCQ_CFG_XPUL_HIGH		(0 << 9)
#घोषणा MX25_ADCQ_CFG_XPUL_OFF		(1 << 9)
#घोषणा MX25_ADCQ_CFG_REFP(sel)		((sel) << 7)
#घोषणा MX25_ADCQ_CFG_REFP_YP		MX25_ADCQ_CFG_REFP(0)
#घोषणा MX25_ADCQ_CFG_REFP_XP		MX25_ADCQ_CFG_REFP(1)
#घोषणा MX25_ADCQ_CFG_REFP_EXT		MX25_ADCQ_CFG_REFP(2)
#घोषणा MX25_ADCQ_CFG_REFP_INT		MX25_ADCQ_CFG_REFP(3)
#घोषणा MX25_ADCQ_CFG_REFP_MASK		GENMASK(8, 7)
#घोषणा MX25_ADCQ_CFG_IN(sel)		((sel) << 4)
#घोषणा MX25_ADCQ_CFG_IN_XP		MX25_ADCQ_CFG_IN(0)
#घोषणा MX25_ADCQ_CFG_IN_YP		MX25_ADCQ_CFG_IN(1)
#घोषणा MX25_ADCQ_CFG_IN_XN		MX25_ADCQ_CFG_IN(2)
#घोषणा MX25_ADCQ_CFG_IN_YN		MX25_ADCQ_CFG_IN(3)
#घोषणा MX25_ADCQ_CFG_IN_WIPER		MX25_ADCQ_CFG_IN(4)
#घोषणा MX25_ADCQ_CFG_IN_AUX0		MX25_ADCQ_CFG_IN(5)
#घोषणा MX25_ADCQ_CFG_IN_AUX1		MX25_ADCQ_CFG_IN(6)
#घोषणा MX25_ADCQ_CFG_IN_AUX2		MX25_ADCQ_CFG_IN(7)
#घोषणा MX25_ADCQ_CFG_REFN(sel)		((sel) << 2)
#घोषणा MX25_ADCQ_CFG_REFN_XN		MX25_ADCQ_CFG_REFN(0)
#घोषणा MX25_ADCQ_CFG_REFN_YN		MX25_ADCQ_CFG_REFN(1)
#घोषणा MX25_ADCQ_CFG_REFN_NGND		MX25_ADCQ_CFG_REFN(2)
#घोषणा MX25_ADCQ_CFG_REFN_NGND2	MX25_ADCQ_CFG_REFN(3)
#घोषणा MX25_ADCQ_CFG_REFN_MASK		GENMASK(3, 2)
#घोषणा MX25_ADCQ_CFG_PENIACK		(1 << 1)

#पूर्ण_अगर  /* _LINUX_INCLUDE_MFD_IMX25_TSADC_H_ */
