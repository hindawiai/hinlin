<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STM32 ALSA SoC Digital Audio Interface (SPDIF-rx) driver.
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Olivier Moysan <olivier.moysan@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

/* SPDIF-rx Register Map */
#घोषणा STM32_SPDIFRX_CR	0x00
#घोषणा STM32_SPDIFRX_IMR	0x04
#घोषणा STM32_SPDIFRX_SR	0x08
#घोषणा STM32_SPDIFRX_IFCR	0x0C
#घोषणा STM32_SPDIFRX_DR	0x10
#घोषणा STM32_SPDIFRX_CSR	0x14
#घोषणा STM32_SPDIFRX_सूची	0x18
#घोषणा STM32_SPDIFRX_VERR	0x3F4
#घोषणा STM32_SPDIFRX_IDR	0x3F8
#घोषणा STM32_SPDIFRX_SIDR	0x3FC

/* Bit definition क्रम SPDIF_CR रेजिस्टर */
#घोषणा SPDIFRX_CR_SPDIFEN_SHIFT	0
#घोषणा SPDIFRX_CR_SPDIFEN_MASK	GENMASK(1, SPDIFRX_CR_SPDIFEN_SHIFT)
#घोषणा SPDIFRX_CR_SPDIFENSET(x)	((x) << SPDIFRX_CR_SPDIFEN_SHIFT)

#घोषणा SPDIFRX_CR_RXDMAEN	BIT(2)
#घोषणा SPDIFRX_CR_RXSTEO	BIT(3)

#घोषणा SPDIFRX_CR_DRFMT_SHIFT	4
#घोषणा SPDIFRX_CR_DRFMT_MASK	GENMASK(5, SPDIFRX_CR_DRFMT_SHIFT)
#घोषणा SPDIFRX_CR_DRFMTSET(x)	((x) << SPDIFRX_CR_DRFMT_SHIFT)

#घोषणा SPDIFRX_CR_PMSK		BIT(6)
#घोषणा SPDIFRX_CR_VMSK		BIT(7)
#घोषणा SPDIFRX_CR_CUMSK	BIT(8)
#घोषणा SPDIFRX_CR_PTMSK	BIT(9)
#घोषणा SPDIFRX_CR_CBDMAEN	BIT(10)
#घोषणा SPDIFRX_CR_CHSEL_SHIFT	11
#घोषणा SPDIFRX_CR_CHSEL	BIT(SPDIFRX_CR_CHSEL_SHIFT)

#घोषणा SPDIFRX_CR_NBTR_SHIFT	12
#घोषणा SPDIFRX_CR_NBTR_MASK	GENMASK(13, SPDIFRX_CR_NBTR_SHIFT)
#घोषणा SPDIFRX_CR_NBTRSET(x)	((x) << SPDIFRX_CR_NBTR_SHIFT)

#घोषणा SPDIFRX_CR_WFA		BIT(14)

#घोषणा SPDIFRX_CR_INSEL_SHIFT	16
#घोषणा SPDIFRX_CR_INSEL_MASK	GENMASK(18, PDIFRX_CR_INSEL_SHIFT)
#घोषणा SPDIFRX_CR_INSELSET(x)	((x) << SPDIFRX_CR_INSEL_SHIFT)

#घोषणा SPDIFRX_CR_CKSEN_SHIFT	20
#घोषणा SPDIFRX_CR_CKSEN	BIT(20)
#घोषणा SPDIFRX_CR_CKSBKPEN	BIT(21)

/* Bit definition क्रम SPDIFRX_IMR रेजिस्टर */
#घोषणा SPDIFRX_IMR_RXNEI	BIT(0)
#घोषणा SPDIFRX_IMR_CSRNEIE	BIT(1)
#घोषणा SPDIFRX_IMR_PERRIE	BIT(2)
#घोषणा SPDIFRX_IMR_OVRIE	BIT(3)
#घोषणा SPDIFRX_IMR_SBLKIE	BIT(4)
#घोषणा SPDIFRX_IMR_SYNCDIE	BIT(5)
#घोषणा SPDIFRX_IMR_IFEIE	BIT(6)

#घोषणा SPDIFRX_XIMR_MASK	GENMASK(6, 0)

/* Bit definition क्रम SPDIFRX_SR रेजिस्टर */
#घोषणा SPDIFRX_SR_RXNE		BIT(0)
#घोषणा SPDIFRX_SR_CSRNE	BIT(1)
#घोषणा SPDIFRX_SR_PERR		BIT(2)
#घोषणा SPDIFRX_SR_OVR		BIT(3)
#घोषणा SPDIFRX_SR_SBD		BIT(4)
#घोषणा SPDIFRX_SR_SYNCD	BIT(5)
#घोषणा SPDIFRX_SR_FERR		BIT(6)
#घोषणा SPDIFRX_SR_SERR		BIT(7)
#घोषणा SPDIFRX_SR_TERR		BIT(8)

#घोषणा SPDIFRX_SR_WIDTH5_SHIFT	16
#घोषणा SPDIFRX_SR_WIDTH5_MASK	GENMASK(30, PDIFRX_SR_WIDTH5_SHIFT)
#घोषणा SPDIFRX_SR_WIDTH5SET(x)	((x) << SPDIFRX_SR_WIDTH5_SHIFT)

/* Bit definition क्रम SPDIFRX_IFCR रेजिस्टर */
#घोषणा SPDIFRX_IFCR_PERRCF	BIT(2)
#घोषणा SPDIFRX_IFCR_OVRCF	BIT(3)
#घोषणा SPDIFRX_IFCR_SBDCF	BIT(4)
#घोषणा SPDIFRX_IFCR_SYNCDCF	BIT(5)

#घोषणा SPDIFRX_XIFCR_MASK	GENMASK(5, 2)

/* Bit definition क्रम SPDIFRX_DR रेजिस्टर (DRFMT = 0b00) */
#घोषणा SPDIFRX_DR0_DR_SHIFT	0
#घोषणा SPDIFRX_DR0_DR_MASK	GENMASK(23, SPDIFRX_DR0_DR_SHIFT)
#घोषणा SPDIFRX_DR0_DRSET(x)	((x) << SPDIFRX_DR0_DR_SHIFT)

#घोषणा SPDIFRX_DR0_PE		BIT(24)

#घोषणा SPDIFRX_DR0_V		BIT(25)
#घोषणा SPDIFRX_DR0_U		BIT(26)
#घोषणा SPDIFRX_DR0_C		BIT(27)

#घोषणा SPDIFRX_DR0_PT_SHIFT	28
#घोषणा SPDIFRX_DR0_PT_MASK	GENMASK(29, SPDIFRX_DR0_PT_SHIFT)
#घोषणा SPDIFRX_DR0_PTSET(x)	((x) << SPDIFRX_DR0_PT_SHIFT)

/* Bit definition क्रम SPDIFRX_DR रेजिस्टर (DRFMT = 0b01) */
#घोषणा  SPDIFRX_DR1_PE		BIT(0)
#घोषणा  SPDIFRX_DR1_V		BIT(1)
#घोषणा  SPDIFRX_DR1_U		BIT(2)
#घोषणा  SPDIFRX_DR1_C		BIT(3)

#घोषणा  SPDIFRX_DR1_PT_SHIFT	4
#घोषणा  SPDIFRX_DR1_PT_MASK	GENMASK(5, SPDIFRX_DR1_PT_SHIFT)
#घोषणा  SPDIFRX_DR1_PTSET(x)	((x) << SPDIFRX_DR1_PT_SHIFT)

#घोषणा SPDIFRX_DR1_DR_SHIFT	8
#घोषणा SPDIFRX_DR1_DR_MASK	GENMASK(31, SPDIFRX_DR1_DR_SHIFT)
#घोषणा SPDIFRX_DR1_DRSET(x)	((x) << SPDIFRX_DR1_DR_SHIFT)

/* Bit definition क्रम SPDIFRX_DR रेजिस्टर (DRFMT = 0b10) */
#घोषणा SPDIFRX_DR1_DRNL1_SHIFT	0
#घोषणा SPDIFRX_DR1_DRNL1_MASK	GENMASK(15, SPDIFRX_DR1_DRNL1_SHIFT)
#घोषणा SPDIFRX_DR1_DRNL1SET(x)	((x) << SPDIFRX_DR1_DRNL1_SHIFT)

#घोषणा SPDIFRX_DR1_DRNL2_SHIFT	16
#घोषणा SPDIFRX_DR1_DRNL2_MASK	GENMASK(31, SPDIFRX_DR1_DRNL2_SHIFT)
#घोषणा SPDIFRX_DR1_DRNL2SET(x)	((x) << SPDIFRX_DR1_DRNL2_SHIFT)

/* Bit definition क्रम SPDIFRX_CSR रेजिस्टर */
#घोषणा SPDIFRX_CSR_USR_SHIFT	0
#घोषणा SPDIFRX_CSR_USR_MASK	GENMASK(15, SPDIFRX_CSR_USR_SHIFT)
#घोषणा SPDIFRX_CSR_USRGET(x)	(((x) & SPDIFRX_CSR_USR_MASK)\
				>> SPDIFRX_CSR_USR_SHIFT)

#घोषणा SPDIFRX_CSR_CS_SHIFT	16
#घोषणा SPDIFRX_CSR_CS_MASK	GENMASK(23, SPDIFRX_CSR_CS_SHIFT)
#घोषणा SPDIFRX_CSR_CSGET(x)	(((x) & SPDIFRX_CSR_CS_MASK)\
				>> SPDIFRX_CSR_CS_SHIFT)

#घोषणा SPDIFRX_CSR_SOB		BIT(24)

/* Bit definition क्रम SPDIFRX_सूची रेजिस्टर */
#घोषणा SPDIFRX_सूची_THI_SHIFT	0
#घोषणा SPDIFRX_सूची_THI_MASK	GENMASK(12, SPDIFRX_सूची_THI_SHIFT)
#घोषणा SPDIFRX_सूची_THI_SET(x)	((x) << SPDIFRX_सूची_THI_SHIFT)

#घोषणा SPDIFRX_सूची_TLO_SHIFT	16
#घोषणा SPDIFRX_सूची_TLO_MASK	GENMASK(28, SPDIFRX_सूची_TLO_SHIFT)
#घोषणा SPDIFRX_सूची_TLO_SET(x)	((x) << SPDIFRX_सूची_TLO_SHIFT)

#घोषणा SPDIFRX_SPDIFEN_DISABLE	0x0
#घोषणा SPDIFRX_SPDIFEN_SYNC	0x1
#घोषणा SPDIFRX_SPDIFEN_ENABLE	0x3

/* Bit definition क्रम SPDIFRX_VERR रेजिस्टर */
#घोषणा SPDIFRX_VERR_MIN_MASK	GENMASK(3, 0)
#घोषणा SPDIFRX_VERR_MAJ_MASK	GENMASK(7, 4)

/* Bit definition क्रम SPDIFRX_IDR रेजिस्टर */
#घोषणा SPDIFRX_IDR_ID_MASK	GENMASK(31, 0)

/* Bit definition क्रम SPDIFRX_SIDR रेजिस्टर */
#घोषणा SPDIFRX_SIDR_SID_MASK	GENMASK(31, 0)

#घोषणा SPDIFRX_IPIDR_NUMBER	0x00130041

#घोषणा SPDIFRX_IN1		0x1
#घोषणा SPDIFRX_IN2		0x2
#घोषणा SPDIFRX_IN3		0x3
#घोषणा SPDIFRX_IN4		0x4
#घोषणा SPDIFRX_IN5		0x5
#घोषणा SPDIFRX_IN6		0x6
#घोषणा SPDIFRX_IN7		0x7
#घोषणा SPDIFRX_IN8		0x8

#घोषणा SPDIFRX_NBTR_NONE	0x0
#घोषणा SPDIFRX_NBTR_3		0x1
#घोषणा SPDIFRX_NBTR_15		0x2
#घोषणा SPDIFRX_NBTR_63		0x3

#घोषणा SPDIFRX_DRFMT_RIGHT	0x0
#घोषणा SPDIFRX_DRFMT_LEFT	0x1
#घोषणा SPDIFRX_DRFMT_PACKED	0x2

/* 192 CS bits in S/PDIF frame. i.e 24 CS bytes */
#घोषणा SPDIFRX_CS_BYTES_NB	24
#घोषणा SPDIFRX_UB_BYTES_NB	48

/*
 * CSR रेजिस्टर is retrieved as a 32 bits word
 * It contains 1 channel status byte and 2 user data bytes
 * 2 S/PDIF frames are acquired to get all CS/UB bits
 */
#घोषणा SPDIFRX_CSR_BUF_LENGTH	(SPDIFRX_CS_BYTES_NB * 4 * 2)

/**
 * काष्ठा sपंचांग32_spdअगरrx_data - निजी data of SPDIFRX
 * @pdev: device data poपूर्णांकer
 * @base: mmio रेजिस्टर base भव address
 * @regmap: SPDIFRX रेजिस्टर map poपूर्णांकer
 * @regmap_conf: SPDIFRX रेजिस्टर map configuration poपूर्णांकer
 * @cs_completion: channel status retrieving completion
 * @kclk: kernel घड़ी feeding the SPDIFRX घड़ी generator
 * @dma_params: dma configuration data क्रम rx channel
 * @substream: PCM substream data poपूर्णांकer
 * @dmab: dma buffer info poपूर्णांकer
 * @ctrl_chan: dma channel क्रम S/PDIF control bits
 * @desc:dma async transaction descriptor
 * @slave_config: dma slave channel runसमय config poपूर्णांकer
 * @phys_addr: SPDIFRX रेजिस्टरs physical base address
 * @lock: synchronization enabling lock
 * @irq_lock: prevent race condition with IRQ on stream state
 * @cs: channel status buffer
 * @ub: user data buffer
 * @irq: SPDIFRX पूर्णांकerrupt line
 * @refcount: keep count of खोलोed DMA channels
 */
काष्ठा sपंचांग32_spdअगरrx_data अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा regmap_config *regmap_conf;
	काष्ठा completion cs_completion;
	काष्ठा clk *kclk;
	काष्ठा snd_dmaengine_dai_dma_data dma_params;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_dma_buffer *dmab;
	काष्ठा dma_chan *ctrl_chan;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_slave_config slave_config;
	dma_addr_t phys_addr;
	spinlock_t lock;  /* Sync enabling lock */
	spinlock_t irq_lock; /* Prevent race condition on stream state */
	अचिन्हित अक्षर cs[SPDIFRX_CS_BYTES_NB];
	अचिन्हित अक्षर ub[SPDIFRX_UB_BYTES_NB];
	पूर्णांक irq;
	पूर्णांक refcount;
पूर्ण;

अटल व्योम sपंचांग32_spdअगरrx_dma_complete(व्योम *data)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = (काष्ठा sपंचांग32_spdअगरrx_data *)data;
	काष्ठा platक्रमm_device *pdev = spdअगरrx->pdev;
	u32 *p_start = (u32 *)spdअगरrx->dmab->area;
	u32 *p_end = p_start + (2 * SPDIFRX_CS_BYTES_NB) - 1;
	u32 *ptr = p_start;
	u16 *ub_ptr = (लघु *)spdअगरrx->ub;
	पूर्णांक i = 0;

	regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
			   SPDIFRX_CR_CBDMAEN,
			   (अचिन्हित पूर्णांक)~SPDIFRX_CR_CBDMAEN);

	अगर (!spdअगरrx->dmab->area)
		वापस;

	जबतक (ptr <= p_end) अणु
		अगर (*ptr & SPDIFRX_CSR_SOB)
			अवरोध;
		ptr++;
	पूर्ण

	अगर (ptr > p_end) अणु
		dev_err(&pdev->dev, "Start of S/PDIF block not found\n");
		वापस;
	पूर्ण

	जबतक (i < SPDIFRX_CS_BYTES_NB) अणु
		spdअगरrx->cs[i] = (अचिन्हित अक्षर)SPDIFRX_CSR_CSGET(*ptr);
		*ub_ptr++ = SPDIFRX_CSR_USRGET(*ptr++);
		अगर (ptr > p_end) अणु
			dev_err(&pdev->dev, "Failed to get channel status\n");
			वापस;
		पूर्ण
		i++;
	पूर्ण

	complete(&spdअगरrx->cs_completion);
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_dma_ctrl_start(काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx)
अणु
	dma_cookie_t cookie;
	पूर्णांक err;

	spdअगरrx->desc = dmaengine_prep_slave_single(spdअगरrx->ctrl_chan,
						    spdअगरrx->dmab->addr,
						    SPDIFRX_CSR_BUF_LENGTH,
						    DMA_DEV_TO_MEM,
						    DMA_CTRL_ACK);
	अगर (!spdअगरrx->desc)
		वापस -EINVAL;

	spdअगरrx->desc->callback = sपंचांग32_spdअगरrx_dma_complete;
	spdअगरrx->desc->callback_param = spdअगरrx;
	cookie = dmaengine_submit(spdअगरrx->desc);
	err = dma_submit_error(cookie);
	अगर (err)
		वापस -EINVAL;

	dma_async_issue_pending(spdअगरrx->ctrl_chan);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_spdअगरrx_dma_ctrl_stop(काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx)
अणु
	dmaengine_terminate_async(spdअगरrx->ctrl_chan);
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_start_sync(काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx)
अणु
	पूर्णांक cr, cr_mask, imr, ret;
	अचिन्हित दीर्घ flags;

	/* Enable IRQs */
	imr = SPDIFRX_IMR_IFEIE | SPDIFRX_IMR_SYNCDIE | SPDIFRX_IMR_PERRIE;
	ret = regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_IMR, imr, imr);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&spdअगरrx->lock, flags);

	spdअगरrx->refcount++;

	regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_CR, &cr);

	अगर (!(cr & SPDIFRX_CR_SPDIFEN_MASK)) अणु
		/*
		 * Start sync अगर SPDIFRX is still in idle state.
		 * SPDIFRX reception enabled when sync करोne
		 */
		dev_dbg(&spdअगरrx->pdev->dev, "start synchronization\n");

		/*
		 * SPDIFRX configuration:
		 * Wait क्रम activity beक्रमe starting sync process. This aव्योम
		 * to issue sync errors when spdअगर संकेत is missing on input.
		 * Preamble, CS, user, validity and parity error bits not copied
		 * to DR रेजिस्टर.
		 */
		cr = SPDIFRX_CR_WFA | SPDIFRX_CR_PMSK | SPDIFRX_CR_VMSK |
		     SPDIFRX_CR_CUMSK | SPDIFRX_CR_PTMSK | SPDIFRX_CR_RXSTEO;
		cr_mask = cr;

		cr |= SPDIFRX_CR_NBTRSET(SPDIFRX_NBTR_63);
		cr_mask |= SPDIFRX_CR_NBTR_MASK;
		cr |= SPDIFRX_CR_SPDIFENSET(SPDIFRX_SPDIFEN_SYNC);
		cr_mask |= SPDIFRX_CR_SPDIFEN_MASK;
		ret = regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
					 cr_mask, cr);
		अगर (ret < 0)
			dev_err(&spdअगरrx->pdev->dev,
				"Failed to start synchronization\n");
	पूर्ण

	spin_unlock_irqrestore(&spdअगरrx->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_spdअगरrx_stop(काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx)
अणु
	पूर्णांक cr, cr_mask, reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spdअगरrx->lock, flags);

	अगर (--spdअगरrx->refcount) अणु
		spin_unlock_irqrestore(&spdअगरrx->lock, flags);
		वापस;
	पूर्ण

	cr = SPDIFRX_CR_SPDIFENSET(SPDIFRX_SPDIFEN_DISABLE);
	cr_mask = SPDIFRX_CR_SPDIFEN_MASK | SPDIFRX_CR_RXDMAEN;

	regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR, cr_mask, cr);

	regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_IMR,
			   SPDIFRX_XIMR_MASK, 0);

	regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_IFCR,
			   SPDIFRX_XIFCR_MASK, SPDIFRX_XIFCR_MASK);

	/* dummy पढ़ो to clear CSRNE and RXNE in status रेजिस्टर */
	regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_DR, &reg);
	regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_CSR, &reg);

	spin_unlock_irqrestore(&spdअगरrx->lock, flags);
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_dma_ctrl_रेजिस्टर(काष्ठा device *dev,
					   काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx)
अणु
	पूर्णांक ret;

	spdअगरrx->ctrl_chan = dma_request_chan(dev, "rx-ctrl");
	अगर (IS_ERR(spdअगरrx->ctrl_chan)) अणु
		अगर (PTR_ERR(spdअगरrx->ctrl_chan) != -EPROBE_DEFER)
			dev_err(dev, "dma_request_slave_channel error %ld\n",
				PTR_ERR(spdअगरrx->ctrl_chan));
		वापस PTR_ERR(spdअगरrx->ctrl_chan);
	पूर्ण

	spdअगरrx->dmab = devm_kzalloc(dev, माप(काष्ठा snd_dma_buffer),
				     GFP_KERNEL);
	अगर (!spdअगरrx->dmab)
		वापस -ENOMEM;

	spdअगरrx->dmab->dev.type = SNDRV_DMA_TYPE_DEV_IRAM;
	spdअगरrx->dmab->dev.dev = dev;
	ret = snd_dma_alloc_pages(spdअगरrx->dmab->dev.type, dev,
				  SPDIFRX_CSR_BUF_LENGTH, spdअगरrx->dmab);
	अगर (ret < 0) अणु
		dev_err(dev, "snd_dma_alloc_pages returned error %d\n", ret);
		वापस ret;
	पूर्ण

	spdअगरrx->slave_config.direction = DMA_DEV_TO_MEM;
	spdअगरrx->slave_config.src_addr = (dma_addr_t)(spdअगरrx->phys_addr +
					 STM32_SPDIFRX_CSR);
	spdअगरrx->slave_config.dst_addr = spdअगरrx->dmab->addr;
	spdअगरrx->slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	spdअगरrx->slave_config.src_maxburst = 1;

	ret = dmaengine_slave_config(spdअगरrx->ctrl_chan,
				     &spdअगरrx->slave_config);
	अगर (ret < 0) अणु
		dev_err(dev, "dmaengine_slave_config returned error %d\n", ret);
		spdअगरrx->ctrl_chan = शून्य;
	पूर्ण

	वापस ret;
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगरrx_क्रमागत_input[] = अणु
	"in0", "in1", "in2", "in3"
पूर्ण;

/*  By शेष CS bits are retrieved from channel A */
अटल स्थिर अक्षर * स्थिर spdअगरrx_क्रमागत_cs_channel[] = अणु
	"A", "B"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ctrl_क्रमागत_input,
			    STM32_SPDIFRX_CR, SPDIFRX_CR_INSEL_SHIFT,
			    spdअगरrx_क्रमागत_input);

अटल SOC_ENUM_SINGLE_DECL(ctrl_क्रमागत_cs_channel,
			    STM32_SPDIFRX_CR, SPDIFRX_CR_CHSEL_SHIFT,
			    spdअगरrx_क्रमागत_cs_channel);

अटल पूर्णांक sपंचांग32_spdअगरrx_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_ub_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_get_ctrl_data(काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx)
अणु
	पूर्णांक ret = 0;

	स_रखो(spdअगरrx->cs, 0, SPDIFRX_CS_BYTES_NB);
	स_रखो(spdअगरrx->ub, 0, SPDIFRX_UB_BYTES_NB);

	ret = sपंचांग32_spdअगरrx_dma_ctrl_start(spdअगरrx);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(spdअगरrx->kclk);
	अगर (ret) अणु
		dev_err(&spdअगरrx->pdev->dev, "Enable kclk failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
				 SPDIFRX_CR_CBDMAEN, SPDIFRX_CR_CBDMAEN);
	अगर (ret < 0)
		जाओ end;

	ret = sपंचांग32_spdअगरrx_start_sync(spdअगरrx);
	अगर (ret < 0)
		जाओ end;

	अगर (रुको_क्रम_completion_पूर्णांकerruptible_समयout(&spdअगरrx->cs_completion,
						      msecs_to_jअगरfies(100))
						      <= 0) अणु
		dev_dbg(&spdअगरrx->pdev->dev, "Failed to get control data\n");
		ret = -EAGAIN;
	पूर्ण

	sपंचांग32_spdअगरrx_stop(spdअगरrx);
	sपंचांग32_spdअगरrx_dma_ctrl_stop(spdअगरrx);

end:
	clk_disable_unprepare(spdअगरrx->kclk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_capture_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = snd_soc_dai_get_drvdata(cpu_dai);

	sपंचांग32_spdअगरrx_get_ctrl_data(spdअगरrx);

	ucontrol->value.iec958.status[0] = spdअगरrx->cs[0];
	ucontrol->value.iec958.status[1] = spdअगरrx->cs[1];
	ucontrol->value.iec958.status[2] = spdअगरrx->cs[2];
	ucontrol->value.iec958.status[3] = spdअगरrx->cs[3];
	ucontrol->value.iec958.status[4] = spdअगरrx->cs[4];

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगर_user_bits_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = snd_soc_dai_get_drvdata(cpu_dai);

	sपंचांग32_spdअगरrx_get_ctrl_data(spdअगरrx);

	ucontrol->value.iec958.status[0] = spdअगरrx->ub[0];
	ucontrol->value.iec958.status[1] = spdअगरrx->ub[1];
	ucontrol->value.iec958.status[2] = spdअगरrx->ub[2];
	ucontrol->value.iec958.status[3] = spdअगरrx->ub[3];
	ucontrol->value.iec958.status[4] = spdअगरrx->ub[4];

	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new sपंचांग32_spdअगरrx_iec_ctrls[] = अणु
	/* Channel status control */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			  SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = sपंचांग32_spdअगरrx_info,
		.get = sपंचांग32_spdअगरrx_capture_get,
	पूर्ण,
	/* User bits control */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 User Bit Capture Default",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			  SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = sपंचांग32_spdअगरrx_ub_info,
		.get = sपंचांग32_spdअगर_user_bits_get,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_kcontrol_new sपंचांग32_spdअगरrx_ctrls[] = अणु
	SOC_ENUM("SPDIFRX input", ctrl_क्रमागत_input),
	SOC_ENUM("SPDIFRX CS channel", ctrl_क्रमागत_cs_channel),
पूर्ण;

अटल पूर्णांक sपंचांग32_spdअगरrx_dai_रेजिस्टर_ctrls(काष्ठा snd_soc_dai *cpu_dai)
अणु
	पूर्णांक ret;

	ret = snd_soc_add_dai_controls(cpu_dai, sपंचांग32_spdअगरrx_iec_ctrls,
				       ARRAY_SIZE(sपंचांग32_spdअगरrx_iec_ctrls));
	अगर (ret < 0)
		वापस ret;

	वापस snd_soc_add_component_controls(cpu_dai->component,
					      sपंचांग32_spdअगरrx_ctrls,
					      ARRAY_SIZE(sपंचांग32_spdअगरrx_ctrls));
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_dai_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = dev_get_drvdata(cpu_dai->dev);

	spdअगरrx->dma_params.addr = (dma_addr_t)(spdअगरrx->phys_addr +
				   STM32_SPDIFRX_DR);
	spdअगरrx->dma_params.maxburst = 1;

	snd_soc_dai_init_dma_data(cpu_dai, शून्य, &spdअगरrx->dma_params);

	वापस sपंचांग32_spdअगरrx_dai_रेजिस्टर_ctrls(cpu_dai);
पूर्ण

अटल bool sपंचांग32_spdअगरrx_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM32_SPDIFRX_CR:
	हाल STM32_SPDIFRX_IMR:
	हाल STM32_SPDIFRX_SR:
	हाल STM32_SPDIFRX_IFCR:
	हाल STM32_SPDIFRX_DR:
	हाल STM32_SPDIFRX_CSR:
	हाल STM32_SPDIFRX_सूची:
	हाल STM32_SPDIFRX_VERR:
	हाल STM32_SPDIFRX_IDR:
	हाल STM32_SPDIFRX_SIDR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sपंचांग32_spdअगरrx_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM32_SPDIFRX_DR:
	हाल STM32_SPDIFRX_CSR:
	हाल STM32_SPDIFRX_SR:
	हाल STM32_SPDIFRX_सूची:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sपंचांग32_spdअगरrx_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM32_SPDIFRX_CR:
	हाल STM32_SPDIFRX_IMR:
	हाल STM32_SPDIFRX_IFCR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config sपंचांग32_h7_spdअगरrx_regmap_conf = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = STM32_SPDIFRX_SIDR,
	.पढ़ोable_reg = sपंचांग32_spdअगरrx_पढ़ोable_reg,
	.अस्थिर_reg = sपंचांग32_spdअगरrx_अस्थिर_reg,
	.ग_लिखोable_reg = sपंचांग32_spdअगरrx_ग_लिखोable_reg,
	.num_reg_शेषs_raw = STM32_SPDIFRX_SIDR / माप(u32) + 1,
	.fast_io = true,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल irqवापस_t sपंचांग32_spdअगरrx_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = (काष्ठा sपंचांग32_spdअगरrx_data *)devid;
	काष्ठा platक्रमm_device *pdev = spdअगरrx->pdev;
	अचिन्हित पूर्णांक cr, mask, sr, imr;
	अचिन्हित पूर्णांक flags, sync_state;
	पूर्णांक err = 0, err_xrun = 0;

	regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_SR, &sr);
	regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_IMR, &imr);

	mask = imr & SPDIFRX_XIMR_MASK;
	/* SERR, TERR, FERR IRQs are generated अगर IFEIE is set */
	अगर (mask & SPDIFRX_IMR_IFEIE)
		mask |= (SPDIFRX_IMR_IFEIE << 1) | (SPDIFRX_IMR_IFEIE << 2);

	flags = sr & mask;
	अगर (!flags) अणु
		dev_err(&pdev->dev, "Unexpected IRQ. rflags=%#x, imr=%#x\n",
			sr, imr);
		वापस IRQ_NONE;
	पूर्ण

	/* Clear IRQs */
	regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_IFCR,
			   SPDIFRX_XIFCR_MASK, flags);

	अगर (flags & SPDIFRX_SR_PERR) अणु
		dev_dbg(&pdev->dev, "Parity error\n");
		err_xrun = 1;
	पूर्ण

	अगर (flags & SPDIFRX_SR_OVR) अणु
		dev_dbg(&pdev->dev, "Overrun error\n");
		err_xrun = 1;
	पूर्ण

	अगर (flags & SPDIFRX_SR_SBD)
		dev_dbg(&pdev->dev, "Synchronization block detected\n");

	अगर (flags & SPDIFRX_SR_SYNCD) अणु
		dev_dbg(&pdev->dev, "Synchronization done\n");

		/* Enable spdअगरrx */
		cr = SPDIFRX_CR_SPDIFENSET(SPDIFRX_SPDIFEN_ENABLE);
		regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
				   SPDIFRX_CR_SPDIFEN_MASK, cr);
	पूर्ण

	अगर (flags & SPDIFRX_SR_FERR) अणु
		dev_dbg(&pdev->dev, "Frame error\n");
		err = 1;
	पूर्ण

	अगर (flags & SPDIFRX_SR_SERR) अणु
		dev_dbg(&pdev->dev, "Synchronization error\n");
		err = 1;
	पूर्ण

	अगर (flags & SPDIFRX_SR_TERR) अणु
		dev_dbg(&pdev->dev, "Timeout error\n");
		err = 1;
	पूर्ण

	अगर (err) अणु
		regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_CR, &cr);
		sync_state = FIELD_GET(SPDIFRX_CR_SPDIFEN_MASK, cr) &&
			     SPDIFRX_SPDIFEN_SYNC;

		/* SPDIFRX is in STATE_STOP. Disable SPDIFRX to clear errors */
		cr = SPDIFRX_CR_SPDIFENSET(SPDIFRX_SPDIFEN_DISABLE);
		regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
				   SPDIFRX_CR_SPDIFEN_MASK, cr);

		/* If SPDIFRX was in STATE_SYNC, retry synchro */
		अगर (sync_state) अणु
			cr = SPDIFRX_CR_SPDIFENSET(SPDIFRX_SPDIFEN_SYNC);
			regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
					   SPDIFRX_CR_SPDIFEN_MASK, cr);
			वापस IRQ_HANDLED;
		पूर्ण

		spin_lock(&spdअगरrx->irq_lock);
		अगर (spdअगरrx->substream)
			snd_pcm_stop(spdअगरrx->substream,
				     SNDRV_PCM_STATE_DISCONNECTED);
		spin_unlock(&spdअगरrx->irq_lock);

		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&spdअगरrx->irq_lock);
	अगर (err_xrun && spdअगरrx->substream)
		snd_pcm_stop_xrun(spdअगरrx->substream);
	spin_unlock(&spdअगरrx->irq_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&spdअगरrx->irq_lock, flags);
	spdअगरrx->substream = substream;
	spin_unlock_irqrestore(&spdअगरrx->irq_lock, flags);

	ret = clk_prepare_enable(spdअगरrx->kclk);
	अगर (ret)
		dev_err(&spdअगरrx->pdev->dev, "Enable kclk failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक data_size = params_width(params);
	पूर्णांक fmt;

	चयन (data_size) अणु
	हाल 16:
		fmt = SPDIFRX_DRFMT_PACKED;
		अवरोध;
	हाल 32:
		fmt = SPDIFRX_DRFMT_LEFT;
		अवरोध;
	शेष:
		dev_err(&spdअगरrx->pdev->dev, "Unexpected data format\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set buswidth to 4 bytes क्रम all data क्रमmats.
	 * Packed क्रमmat: transfer 2 x 2 bytes samples
	 * Left क्रमmat: transfer 1 x 3 bytes samples + 1 dummy byte
	 */
	spdअगरrx->dma_params.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	snd_soc_dai_init_dma_data(cpu_dai, शून्य, &spdअगरrx->dma_params);

	वापस regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
				  SPDIFRX_CR_DRFMT_MASK,
				  SPDIFRX_CR_DRFMTSET(fmt));
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				 काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_IMR,
				   SPDIFRX_IMR_OVRIE, SPDIFRX_IMR_OVRIE);

		regmap_update_bits(spdअगरrx->regmap, STM32_SPDIFRX_CR,
				   SPDIFRX_CR_RXDMAEN, SPDIFRX_CR_RXDMAEN);

		ret = sपंचांग32_spdअगरrx_start_sync(spdअगरrx);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_STOP:
		sपंचांग32_spdअगरrx_stop(spdअगरrx);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_spdअगरrx_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spdअगरrx->irq_lock, flags);
	spdअगरrx->substream = शून्य;
	spin_unlock_irqrestore(&spdअगरrx->irq_lock, flags);

	clk_disable_unprepare(spdअगरrx->kclk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sपंचांग32_spdअगरrx_pcm_dai_ops = अणु
	.startup	= sपंचांग32_spdअगरrx_startup,
	.hw_params	= sपंचांग32_spdअगरrx_hw_params,
	.trigger	= sपंचांग32_spdअगरrx_trigger,
	.shutकरोwn	= sपंचांग32_spdअगरrx_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sपंचांग32_spdअगरrx_dai[] = अणु
	अणु
		.probe = sपंचांग32_spdअगरrx_dai_probe,
		.capture = अणु
			.stream_name = "CPU-Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE |
				   SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.ops = &sपंचांग32_spdअगरrx_pcm_dai_ops,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware sपंचांग32_spdअगरrx_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
	.buffer_bytes_max = 8 * PAGE_SIZE,
	.period_bytes_min = 1024,
	.period_bytes_max = 4 * PAGE_SIZE,
	.periods_min = 2,
	.periods_max = 8,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sपंचांग32_spdअगरrx_component = अणु
	.name = "stm32-spdifrx",
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config sपंचांग32_spdअगरrx_pcm_config = अणु
	.pcm_hardware = &sपंचांग32_spdअगरrx_pcm_hw,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_spdअगरrx_ids[] = अणु
	अणु
		.compatible = "st,stm32h7-spdifrx",
		.data = &sपंचांग32_h7_spdअगरrx_regmap_conf
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sपंचांग32_spdअगरrx_parse_of(काष्ठा platक्रमm_device *pdev,
				  काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा resource *res;

	अगर (!np)
		वापस -ENODEV;

	of_id = of_match_device(sपंचांग32_spdअगरrx_ids, &pdev->dev);
	अगर (of_id)
		spdअगरrx->regmap_conf =
			(स्थिर काष्ठा regmap_config *)of_id->data;
	अन्यथा
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	spdअगरrx->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(spdअगरrx->base))
		वापस PTR_ERR(spdअगरrx->base);

	spdअगरrx->phys_addr = res->start;

	spdअगरrx->kclk = devm_clk_get(&pdev->dev, "kclk");
	अगर (IS_ERR(spdअगरrx->kclk)) अणु
		अगर (PTR_ERR(spdअगरrx->kclk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get kclk: %ld\n",
				PTR_ERR(spdअगरrx->kclk));
		वापस PTR_ERR(spdअगरrx->kclk);
	पूर्ण

	spdअगरrx->irq = platक्रमm_get_irq(pdev, 0);
	अगर (spdअगरrx->irq < 0)
		वापस spdअगरrx->irq;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = platक्रमm_get_drvdata(pdev);

	अगर (spdअगरrx->ctrl_chan)
		dma_release_channel(spdअगरrx->ctrl_chan);

	अगर (spdअगरrx->dmab)
		snd_dma_मुक्त_pages(spdअगरrx->dmab);

	snd_dmaengine_pcm_unरेजिस्टर(&pdev->dev);
	snd_soc_unरेजिस्टर_component(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx;
	काष्ठा reset_control *rst;
	स्थिर काष्ठा snd_dmaengine_pcm_config *pcm_config = शून्य;
	u32 ver, idr;
	पूर्णांक ret;

	spdअगरrx = devm_kzalloc(&pdev->dev, माप(*spdअगरrx), GFP_KERNEL);
	अगर (!spdअगरrx)
		वापस -ENOMEM;

	spdअगरrx->pdev = pdev;
	init_completion(&spdअगरrx->cs_completion);
	spin_lock_init(&spdअगरrx->lock);
	spin_lock_init(&spdअगरrx->irq_lock);

	platक्रमm_set_drvdata(pdev, spdअगरrx);

	ret = sपंचांग32_spdअगरrx_parse_of(pdev, spdअगरrx);
	अगर (ret)
		वापस ret;

	spdअगरrx->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "kclk",
						    spdअगरrx->base,
						    spdअगरrx->regmap_conf);
	अगर (IS_ERR(spdअगरrx->regmap)) अणु
		अगर (PTR_ERR(spdअगरrx->regmap) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Regmap init error %ld\n",
				PTR_ERR(spdअगरrx->regmap));
		वापस PTR_ERR(spdअगरrx->regmap);
	पूर्ण

	ret = devm_request_irq(&pdev->dev, spdअगरrx->irq, sपंचांग32_spdअगरrx_isr, 0,
			       dev_name(&pdev->dev), spdअगरrx);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IRQ request returned %d\n", ret);
		वापस ret;
	पूर्ण

	rst = devm_reset_control_get_optional_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		अगर (PTR_ERR(rst) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Reset controller error %ld\n",
				PTR_ERR(rst));
		वापस PTR_ERR(rst);
	पूर्ण
	reset_control_निश्चित(rst);
	udelay(2);
	reset_control_deनिश्चित(rst);

	pcm_config = &sपंचांग32_spdअगरrx_pcm_config;
	ret = snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, pcm_config, 0);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "PCM DMA register error %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_रेजिस्टर_component(&pdev->dev,
					 &sपंचांग32_spdअगरrx_component,
					 sपंचांग32_spdअगरrx_dai,
					 ARRAY_SIZE(sपंचांग32_spdअगरrx_dai));
	अगर (ret) अणु
		snd_dmaengine_pcm_unरेजिस्टर(&pdev->dev);
		वापस ret;
	पूर्ण

	ret = sपंचांग32_spdअगरrx_dma_ctrl_रेजिस्टर(&pdev->dev, spdअगरrx);
	अगर (ret)
		जाओ error;

	ret = regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_IDR, &idr);
	अगर (ret)
		जाओ error;

	अगर (idr == SPDIFRX_IPIDR_NUMBER) अणु
		ret = regmap_पढ़ो(spdअगरrx->regmap, STM32_SPDIFRX_VERR, &ver);
		अगर (ret)
			जाओ error;

		dev_dbg(&pdev->dev, "SPDIFRX version: %lu.%lu registered\n",
			FIELD_GET(SPDIFRX_VERR_MAJ_MASK, ver),
			FIELD_GET(SPDIFRX_VERR_MIN_MASK, ver));
	पूर्ण

	वापस ret;

error:
	sपंचांग32_spdअगरrx_हटाओ(pdev);

	वापस ret;
पूर्ण

MODULE_DEVICE_TABLE(of, sपंचांग32_spdअगरrx_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_spdअगरrx_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = dev_get_drvdata(dev);

	regcache_cache_only(spdअगरrx->regmap, true);
	regcache_mark_dirty(spdअगरrx->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_spdअगरrx_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_spdअगरrx_data *spdअगरrx = dev_get_drvdata(dev);

	regcache_cache_only(spdअगरrx->regmap, false);

	वापस regcache_sync(spdअगरrx->regmap);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_spdअगरrx_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_spdअगरrx_suspend, sपंचांग32_spdअगरrx_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_spdअगरrx_driver = अणु
	.driver = अणु
		.name = "st,stm32-spdifrx",
		.of_match_table = sपंचांग32_spdअगरrx_ids,
		.pm = &sपंचांग32_spdअगरrx_pm_ops,
	पूर्ण,
	.probe = sपंचांग32_spdअगरrx_probe,
	.हटाओ = sपंचांग32_spdअगरrx_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_spdअगरrx_driver);

MODULE_DESCRIPTION("STM32 Soc spdifrx Interface");
MODULE_AUTHOR("Olivier Moysan, <olivier.moysan@st.com>");
MODULE_ALIAS("platform:stm32-spdifrx");
MODULE_LICENSE("GPL v2");
