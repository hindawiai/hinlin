<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale S/PDIF ALSA SoC Digital Audio Interface (DAI) driver
//
// Copyright (C) 2013 Freescale Semiconductor, Inc.
//
// Based on sपंचांगp3xxx_spdअगर_dai.c
// Vladimir Barinov <vbarinov@embeddedalley.com>
// Copyright 2008 SigmaTel, Inc
// Copyright 2008 Embedded Alley Solutions, Inc

#समावेश <linux/bitrev.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <sound/asoundef.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/soc.h>

#समावेश "fsl_spdif.h"
#समावेश "imx-pcm.h"

#घोषणा FSL_SPDIF_TXFIFO_WML	0x8
#घोषणा FSL_SPDIF_RXFIFO_WML	0x8

#घोषणा INTR_FOR_PLAYBACK	(INT_TXFIFO_RESYNC)
#घोषणा INTR_FOR_CAPTURE	(INT_SYM_ERR | INT_BIT_ERR | INT_URX_FUL |\
				INT_URX_OV | INT_QRX_FUL | INT_QRX_OV |\
				INT_UQ_SYNC | INT_UQ_ERR | INT_RXFIFO_RESYNC |\
				INT_LOSS_LOCK | INT_DPLL_LOCKED)

#घोषणा SIE_INTR_FOR(tx)	(tx ? INTR_FOR_PLAYBACK : INTR_FOR_CAPTURE)

/* Index list क्रम the values that has अगर (DPLL Locked) condition */
अटल u8 srpc_dpll_locked[] = अणु 0x0, 0x1, 0x2, 0x3, 0x4, 0xa, 0xb पूर्ण;
#घोषणा SRPC_NODPLL_START1	0x5
#घोषणा SRPC_NODPLL_START2	0xc

#घोषणा DEFAULT_RXCLK_SRC	1

/**
 * काष्ठा fsl_spdअगर_soc_data: soc specअगरic data
 *
 * @imx: क्रम imx platक्रमm
 * @shared_root_घड़ी: flag of sharing a घड़ी source with others;
 *                     so the driver shouldn't set root घड़ी rate
 * @पूर्णांकerrupts: पूर्णांकerrupt number
 * @tx_burst: tx maxburst size
 * @rx_burst: rx maxburst size
 * @tx_क्रमmats: tx supported data क्रमmat
 */
काष्ठा fsl_spdअगर_soc_data अणु
	bool imx;
	bool shared_root_घड़ी;
	u32 पूर्णांकerrupts;
	u32 tx_burst;
	u32 rx_burst;
	u64 tx_क्रमmats;
पूर्ण;

/*
 * SPDIF control काष्ठाure
 * Defines channel status, subcode and Q sub
 */
काष्ठा spdअगर_mixer_control अणु
	/* spinlock to access control data */
	spinlock_t ctl_lock;

	/* IEC958 channel tx status bit */
	अचिन्हित अक्षर ch_status[4];

	/* User bits */
	अचिन्हित अक्षर subcode[2 * SPDIF_UBITS_SIZE];

	/* Q subcode part of user bits */
	अचिन्हित अक्षर qsub[2 * SPDIF_QSUB_SIZE];

	/* Buffer offset क्रम U/Q */
	u32 upos;
	u32 qpos;

	/* Ready buffer index of the two buffers */
	u32 पढ़ोy_buf;
पूर्ण;

/**
 * काष्ठा fsl_spdअगर_priv - Freescale SPDIF निजी data
 * @soc: SPDIF soc data
 * @fsl_spdअगर_control: SPDIF control data
 * @cpu_dai_drv: cpu dai driver
 * @pdev: platक्रमm device poपूर्णांकer
 * @regmap: regmap handler
 * @dpll_locked: dpll lock flag
 * @txrate: the best rates क्रम playback
 * @txclk_df: STC_TXCLK_DF भागiders value क्रम playback
 * @sysclk_df: STC_SYSCLK_DF भागiders value क्रम playback
 * @txclk_src: STC_TXCLK_SRC values क्रम playback
 * @rxclk_src: SRPC_CLKSRC_SEL values क्रम capture
 * @txclk: tx घड़ी sources क्रम playback
 * @rxclk: rx घड़ी sources क्रम capture
 * @coreclk: core घड़ी क्रम रेजिस्टर access via DMA
 * @sysclk: प्रणाली घड़ी क्रम rx घड़ी rate measurement
 * @spbaclk: SPBA घड़ी (optional, depending on SoC design)
 * @dma_params_tx: DMA parameters क्रम transmit channel
 * @dma_params_rx: DMA parameters क्रम receive channel
 * @regcache_srpc: regcache क्रम SRPC
 */
काष्ठा fsl_spdअगर_priv अणु
	स्थिर काष्ठा fsl_spdअगर_soc_data *soc;
	काष्ठा spdअगर_mixer_control fsl_spdअगर_control;
	काष्ठा snd_soc_dai_driver cpu_dai_drv;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	bool dpll_locked;
	u32 txrate[SPDIF_TXRATE_MAX];
	u8 txclk_df[SPDIF_TXRATE_MAX];
	u16 sysclk_df[SPDIF_TXRATE_MAX];
	u8 txclk_src[SPDIF_TXRATE_MAX];
	u8 rxclk_src;
	काष्ठा clk *txclk[SPDIF_TXRATE_MAX];
	काष्ठा clk *rxclk;
	काष्ठा clk *coreclk;
	काष्ठा clk *sysclk;
	काष्ठा clk *spbaclk;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	/* regcache क्रम SRPC */
	u32 regcache_srpc;
पूर्ण;

अटल काष्ठा fsl_spdअगर_soc_data fsl_spdअगर_vf610 = अणु
	.imx = false,
	.shared_root_घड़ी = false,
	.पूर्णांकerrupts = 1,
	.tx_burst = FSL_SPDIF_TXFIFO_WML,
	.rx_burst = FSL_SPDIF_RXFIFO_WML,
	.tx_क्रमmats = FSL_SPDIF_FORMATS_PLAYBACK,
पूर्ण;

अटल काष्ठा fsl_spdअगर_soc_data fsl_spdअगर_imx35 = अणु
	.imx = true,
	.shared_root_घड़ी = false,
	.पूर्णांकerrupts = 1,
	.tx_burst = FSL_SPDIF_TXFIFO_WML,
	.rx_burst = FSL_SPDIF_RXFIFO_WML,
	.tx_क्रमmats = FSL_SPDIF_FORMATS_PLAYBACK,
पूर्ण;

अटल काष्ठा fsl_spdअगर_soc_data fsl_spdअगर_imx6sx = अणु
	.imx = true,
	.shared_root_घड़ी = true,
	.पूर्णांकerrupts = 1,
	.tx_burst = FSL_SPDIF_TXFIFO_WML,
	.rx_burst = FSL_SPDIF_RXFIFO_WML,
	.tx_क्रमmats = FSL_SPDIF_FORMATS_PLAYBACK,

पूर्ण;

अटल काष्ठा fsl_spdअगर_soc_data fsl_spdअगर_imx8qm = अणु
	.imx = true,
	.shared_root_घड़ी = true,
	.पूर्णांकerrupts = 2,
	.tx_burst = 2,		/* Applied क्रम EDMA */
	.rx_burst = 2,		/* Applied क्रम EDMA */
	.tx_क्रमmats = SNDRV_PCM_FMTBIT_S24_LE,  /* Applied क्रम EDMA */
पूर्ण;

/* Check अगर clk is a root घड़ी that करोes not share घड़ी source with others */
अटल अंतरभूत bool fsl_spdअगर_can_set_clk_rate(काष्ठा fsl_spdअगर_priv *spdअगर, पूर्णांक clk)
अणु
	वापस (clk == STC_TXCLK_SPDIF_ROOT) && !spdअगर->soc->shared_root_घड़ी;
पूर्ण

/* DPLL locked and lock loss पूर्णांकerrupt handler */
अटल व्योम spdअगर_irq_dpll_lock(काष्ठा fsl_spdअगर_priv *spdअगर_priv)
अणु
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	u32 locked;

	regmap_पढ़ो(regmap, REG_SPDIF_SRPC, &locked);
	locked &= SRPC_DPLL_LOCKED;

	dev_dbg(&pdev->dev, "isr: Rx dpll %s \n",
			locked ? "locked" : "loss lock");

	spdअगर_priv->dpll_locked = locked ? true : false;
पूर्ण

/* Receiver found illegal symbol पूर्णांकerrupt handler */
अटल व्योम spdअगर_irq_sym_error(काष्ठा fsl_spdअगर_priv *spdअगर_priv)
अणु
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;

	dev_dbg(&pdev->dev, "isr: receiver found illegal symbol\n");

	/* Clear illegal symbol अगर DPLL unlocked since no audio stream */
	अगर (!spdअगर_priv->dpll_locked)
		regmap_update_bits(regmap, REG_SPDIF_SIE, INT_SYM_ERR, 0);
पूर्ण

/* U/Q Channel receive रेजिस्टर full */
अटल व्योम spdअगर_irq_uqrx_full(काष्ठा fsl_spdअगर_priv *spdअगर_priv, अक्षर name)
अणु
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	u32 *pos, size, val, reg;

	चयन (name) अणु
	हाल 'U':
		pos = &ctrl->upos;
		size = SPDIF_UBITS_SIZE;
		reg = REG_SPDIF_SRU;
		अवरोध;
	हाल 'Q':
		pos = &ctrl->qpos;
		size = SPDIF_QSUB_SIZE;
		reg = REG_SPDIF_SRQ;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unsupported channel name\n");
		वापस;
	पूर्ण

	dev_dbg(&pdev->dev, "isr: %c Channel receive register full\n", name);

	अगर (*pos >= size * 2) अणु
		*pos = 0;
	पूर्ण अन्यथा अगर (unlikely((*pos % size) + 3 > size)) अणु
		dev_err(&pdev->dev, "User bit receive buffer overflow\n");
		वापस;
	पूर्ण

	regmap_पढ़ो(regmap, reg, &val);
	ctrl->subcode[*pos++] = val >> 16;
	ctrl->subcode[*pos++] = val >> 8;
	ctrl->subcode[*pos++] = val;
पूर्ण

/* U/Q Channel sync found */
अटल व्योम spdअगर_irq_uq_sync(काष्ठा fsl_spdअगर_priv *spdअगर_priv)
अणु
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;

	dev_dbg(&pdev->dev, "isr: U/Q Channel sync found\n");

	/* U/Q buffer reset */
	अगर (ctrl->qpos == 0)
		वापस;

	/* Set पढ़ोy to this buffer */
	ctrl->पढ़ोy_buf = (ctrl->qpos - 1) / SPDIF_QSUB_SIZE + 1;
पूर्ण

/* U/Q Channel framing error */
अटल व्योम spdअगर_irq_uq_err(काष्ठा fsl_spdअगर_priv *spdअगर_priv)
अणु
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	u32 val;

	dev_dbg(&pdev->dev, "isr: U/Q Channel framing error\n");

	/* Read U/Q data to clear the irq and करो buffer reset */
	regmap_पढ़ो(regmap, REG_SPDIF_SRU, &val);
	regmap_पढ़ो(regmap, REG_SPDIF_SRQ, &val);

	/* Drop this U/Q buffer */
	ctrl->पढ़ोy_buf = 0;
	ctrl->upos = 0;
	ctrl->qpos = 0;
पूर्ण

/* Get spdअगर पूर्णांकerrupt status and clear the पूर्णांकerrupt */
अटल u32 spdअगर_पूर्णांकr_status_clear(काष्ठा fsl_spdअगर_priv *spdअगर_priv)
अणु
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 val, val2;

	regmap_पढ़ो(regmap, REG_SPDIF_SIS, &val);
	regmap_पढ़ो(regmap, REG_SPDIF_SIE, &val2);

	regmap_ग_लिखो(regmap, REG_SPDIF_SIC, val & val2);

	वापस val;
पूर्ण

अटल irqवापस_t spdअगर_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = (काष्ठा fsl_spdअगर_priv *)devid;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	u32 sis;

	sis = spdअगर_पूर्णांकr_status_clear(spdअगर_priv);

	अगर (sis & INT_DPLL_LOCKED)
		spdअगर_irq_dpll_lock(spdअगर_priv);

	अगर (sis & INT_TXFIFO_UNOV)
		dev_dbg(&pdev->dev, "isr: Tx FIFO under/overrun\n");

	अगर (sis & INT_TXFIFO_RESYNC)
		dev_dbg(&pdev->dev, "isr: Tx FIFO resync\n");

	अगर (sis & INT_CNEW)
		dev_dbg(&pdev->dev, "isr: cstatus new\n");

	अगर (sis & INT_VAL_NOGOOD)
		dev_dbg(&pdev->dev, "isr: validity flag no good\n");

	अगर (sis & INT_SYM_ERR)
		spdअगर_irq_sym_error(spdअगर_priv);

	अगर (sis & INT_BIT_ERR)
		dev_dbg(&pdev->dev, "isr: receiver found parity bit error\n");

	अगर (sis & INT_URX_FUL)
		spdअगर_irq_uqrx_full(spdअगर_priv, 'U');

	अगर (sis & INT_URX_OV)
		dev_dbg(&pdev->dev, "isr: U Channel receive register overrun\n");

	अगर (sis & INT_QRX_FUL)
		spdअगर_irq_uqrx_full(spdअगर_priv, 'Q');

	अगर (sis & INT_QRX_OV)
		dev_dbg(&pdev->dev, "isr: Q Channel receive register overrun\n");

	अगर (sis & INT_UQ_SYNC)
		spdअगर_irq_uq_sync(spdअगर_priv);

	अगर (sis & INT_UQ_ERR)
		spdअगर_irq_uq_err(spdअगर_priv);

	अगर (sis & INT_RXFIFO_UNOV)
		dev_dbg(&pdev->dev, "isr: Rx FIFO under/overrun\n");

	अगर (sis & INT_RXFIFO_RESYNC)
		dev_dbg(&pdev->dev, "isr: Rx FIFO resync\n");

	अगर (sis & INT_LOSS_LOCK)
		spdअगर_irq_dpll_lock(spdअगर_priv);

	/* FIXME: Write Tx FIFO to clear TxEm */
	अगर (sis & INT_TX_EM)
		dev_dbg(&pdev->dev, "isr: Tx FIFO empty\n");

	/* FIXME: Read Rx FIFO to clear RxFIFOFul */
	अगर (sis & INT_RXFIFO_FUL)
		dev_dbg(&pdev->dev, "isr: Rx FIFO full\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spdअगर_softreset(काष्ठा fsl_spdअगर_priv *spdअगर_priv)
अणु
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 val, cycle = 1000;

	regcache_cache_bypass(regmap, true);

	regmap_ग_लिखो(regmap, REG_SPDIF_SCR, SCR_SOFT_RESET);

	/*
	 * RESET bit would be cleared after finishing its reset procedure,
	 * which typically lasts 8 cycles. 1000 cycles will keep it safe.
	 */
	करो अणु
		regmap_पढ़ो(regmap, REG_SPDIF_SCR, &val);
	पूर्ण जबतक ((val & SCR_SOFT_RESET) && cycle--);

	regcache_cache_bypass(regmap, false);
	regcache_mark_dirty(regmap);
	regcache_sync(regmap);

	अगर (cycle)
		वापस 0;
	अन्यथा
		वापस -EBUSY;
पूर्ण

अटल व्योम spdअगर_set_cstatus(काष्ठा spdअगर_mixer_control *ctrl,
				u8 mask, u8 cstatus)
अणु
	ctrl->ch_status[3] &= ~mask;
	ctrl->ch_status[3] |= cstatus & mask;
पूर्ण

अटल व्योम spdअगर_ग_लिखो_channel_status(काष्ठा fsl_spdअगर_priv *spdअगर_priv)
अणु
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	u32 ch_status;

	ch_status = (bitrev8(ctrl->ch_status[0]) << 16) |
		    (bitrev8(ctrl->ch_status[1]) << 8) |
		    bitrev8(ctrl->ch_status[2]);
	regmap_ग_लिखो(regmap, REG_SPDIF_STCSCH, ch_status);

	dev_dbg(&pdev->dev, "STCSCH: 0x%06x\n", ch_status);

	ch_status = bitrev8(ctrl->ch_status[3]) << 16;
	regmap_ग_लिखो(regmap, REG_SPDIF_STCSCL, ch_status);

	dev_dbg(&pdev->dev, "STCSCL: 0x%06x\n", ch_status);
पूर्ण

/* Set SPDIF PhaseConfig रेजिस्टर क्रम rx घड़ी */
अटल पूर्णांक spdअगर_set_rx_clksrc(काष्ठा fsl_spdअगर_priv *spdअगर_priv,
				क्रमागत spdअगर_gainsel gainsel, पूर्णांक dpll_locked)
अणु
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u8 clksrc = spdअगर_priv->rxclk_src;

	अगर (clksrc >= SRPC_CLKSRC_MAX || gainsel >= GAINSEL_MULTI_MAX)
		वापस -EINVAL;

	regmap_update_bits(regmap, REG_SPDIF_SRPC,
			SRPC_CLKSRC_SEL_MASK | SRPC_GAINSEL_MASK,
			SRPC_CLKSRC_SEL_SET(clksrc) | SRPC_GAINSEL_SET(gainsel));

	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_set_sample_rate(काष्ठा snd_pcm_substream *substream,
				पूर्णांक sample_rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	अचिन्हित दीर्घ csfs = 0;
	u32 stc, mask, rate;
	u16 sysclk_df;
	u8 clk, txclk_df;
	पूर्णांक ret;

	चयन (sample_rate) अणु
	हाल 32000:
		rate = SPDIF_TXRATE_32000;
		csfs = IEC958_AES3_CON_FS_32000;
		अवरोध;
	हाल 44100:
		rate = SPDIF_TXRATE_44100;
		csfs = IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 48000:
		rate = SPDIF_TXRATE_48000;
		csfs = IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 88200:
		rate = SPDIF_TXRATE_88200;
		csfs = IEC958_AES3_CON_FS_88200;
		अवरोध;
	हाल 96000:
		rate = SPDIF_TXRATE_96000;
		csfs = IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 176400:
		rate = SPDIF_TXRATE_176400;
		csfs = IEC958_AES3_CON_FS_176400;
		अवरोध;
	हाल 192000:
		rate = SPDIF_TXRATE_192000;
		csfs = IEC958_AES3_CON_FS_192000;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unsupported sample rate %d\n", sample_rate);
		वापस -EINVAL;
	पूर्ण

	clk = spdअगर_priv->txclk_src[rate];
	अगर (clk >= STC_TXCLK_SRC_MAX) अणु
		dev_err(&pdev->dev, "tx clock source is out of range\n");
		वापस -EINVAL;
	पूर्ण

	txclk_df = spdअगर_priv->txclk_df[rate];
	अगर (txclk_df == 0) अणु
		dev_err(&pdev->dev, "the txclk_df can't be zero\n");
		वापस -EINVAL;
	पूर्ण

	sysclk_df = spdअगर_priv->sysclk_df[rate];

	अगर (!fsl_spdअगर_can_set_clk_rate(spdअगर_priv, clk))
		जाओ clk_set_bypass;

	/* The S/PDIF block needs a घड़ी of 64 * fs * txclk_df */
	ret = clk_set_rate(spdअगर_priv->txclk[rate],
			   64 * sample_rate * txclk_df);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to set tx clock rate\n");
		वापस ret;
	पूर्ण

clk_set_bypass:
	dev_dbg(&pdev->dev, "expected clock rate = %d\n",
			(64 * sample_rate * txclk_df * sysclk_df));
	dev_dbg(&pdev->dev, "actual clock rate = %ld\n",
			clk_get_rate(spdअगर_priv->txclk[rate]));

	/* set fs field in consumer channel status */
	spdअगर_set_cstatus(ctrl, IEC958_AES3_CON_FS, csfs);

	/* select घड़ी source and भागisor */
	stc = STC_TXCLK_ALL_EN | STC_TXCLK_SRC_SET(clk) |
	      STC_TXCLK_DF(txclk_df) | STC_SYSCLK_DF(sysclk_df);
	mask = STC_TXCLK_ALL_EN_MASK | STC_TXCLK_SRC_MASK |
	       STC_TXCLK_DF_MASK | STC_SYSCLK_DF_MASK;
	regmap_update_bits(regmap, REG_SPDIF_STC, mask, stc);

	dev_dbg(&pdev->dev, "set sample rate to %dHz for %dHz playback\n",
			spdअगर_priv->txrate[rate], sample_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spdअगर_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 scr, mask;
	पूर्णांक ret;

	/* Reset module and पूर्णांकerrupts only क्रम first initialization */
	अगर (!snd_soc_dai_active(cpu_dai)) अणु
		ret = spdअगर_softreset(spdअगर_priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to soft reset\n");
			वापस ret;
		पूर्ण

		/* Disable all the पूर्णांकerrupts */
		regmap_update_bits(regmap, REG_SPDIF_SIE, 0xffffff, 0);
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		scr = SCR_TXFIFO_AUTOSYNC | SCR_TXFIFO_CTRL_NORMAL |
			SCR_TXSEL_NORMAL | SCR_USRC_SEL_CHIP |
			SCR_TXFIFO_FSEL_IF8;
		mask = SCR_TXFIFO_AUTOSYNC_MASK | SCR_TXFIFO_CTRL_MASK |
			SCR_TXSEL_MASK | SCR_USRC_SEL_MASK |
			SCR_TXFIFO_FSEL_MASK;
	पूर्ण अन्यथा अणु
		scr = SCR_RXFIFO_FSEL_IF8 | SCR_RXFIFO_AUTOSYNC;
		mask = SCR_RXFIFO_FSEL_MASK | SCR_RXFIFO_AUTOSYNC_MASK|
			SCR_RXFIFO_CTL_MASK | SCR_RXFIFO_OFF_MASK;
	पूर्ण
	regmap_update_bits(regmap, REG_SPDIF_SCR, mask, scr);

	/* Power up SPDIF module */
	regmap_update_bits(regmap, REG_SPDIF_SCR, SCR_LOW_POWER, 0);

	वापस 0;
पूर्ण

अटल व्योम fsl_spdअगर_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 scr, mask;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		scr = 0;
		mask = SCR_TXFIFO_AUTOSYNC_MASK | SCR_TXFIFO_CTRL_MASK |
			SCR_TXSEL_MASK | SCR_USRC_SEL_MASK |
			SCR_TXFIFO_FSEL_MASK;
	पूर्ण अन्यथा अणु
		scr = SCR_RXFIFO_OFF | SCR_RXFIFO_CTL_ZERO;
		mask = SCR_RXFIFO_FSEL_MASK | SCR_RXFIFO_AUTOSYNC_MASK|
			SCR_RXFIFO_CTL_MASK | SCR_RXFIFO_OFF_MASK;
	पूर्ण
	regmap_update_bits(regmap, REG_SPDIF_SCR, mask, scr);

	/* Power करोwn SPDIF module only अगर tx&rx are both inactive */
	अगर (!snd_soc_dai_active(cpu_dai)) अणु
		spdअगर_पूर्णांकr_status_clear(spdअगर_priv);
		regmap_update_bits(regmap, REG_SPDIF_SCR,
				SCR_LOW_POWER, SCR_LOW_POWER);
	पूर्ण
पूर्ण

अटल पूर्णांक fsl_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	u32 sample_rate = params_rate(params);
	पूर्णांक ret = 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret  = spdअगर_set_sample_rate(substream, sample_rate);
		अगर (ret) अणु
			dev_err(&pdev->dev, "%s: set sample rate failed: %d\n",
					__func__, sample_rate);
			वापस ret;
		पूर्ण
		spdअगर_set_cstatus(ctrl, IEC958_AES3_CON_CLOCK,
				  IEC958_AES3_CON_CLOCK_1000PPM);
		spdअगर_ग_लिखो_channel_status(spdअगर_priv);
	पूर्ण अन्यथा अणु
		/* Setup rx घड़ी source */
		ret = spdअगर_set_rx_clksrc(spdअगर_priv, SPDIF_DEFAULT_GAINSEL, 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_spdअगर_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u32 पूर्णांकr = SIE_INTR_FOR(tx);
	u32 dmaen = SCR_DMA_xX_EN(tx);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		regmap_update_bits(regmap, REG_SPDIF_SIE, पूर्णांकr, पूर्णांकr);
		regmap_update_bits(regmap, REG_SPDIF_SCR, dmaen, dmaen);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		regmap_update_bits(regmap, REG_SPDIF_SCR, dmaen, 0);
		regmap_update_bits(regmap, REG_SPDIF_SIE, पूर्णांकr, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_spdअगर_dai_ops = अणु
	.startup = fsl_spdअगर_startup,
	.hw_params = fsl_spdअगर_hw_params,
	.trigger = fsl_spdअगर_trigger,
	.shutकरोwn = fsl_spdअगर_shutकरोwn,
पूर्ण;


/*
 * FSL SPDIF IEC958 controller(mixer) functions
 *
 *	Channel status get/put control
 *	User bit value get/put control
 *	Valid bit value get control
 *	DPLL lock status get control
 *	User bit sync mode selection control
 */

अटल पूर्णांक fsl_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spdअगर_pb_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;

	uvalue->value.iec958.status[0] = ctrl->ch_status[0];
	uvalue->value.iec958.status[1] = ctrl->ch_status[1];
	uvalue->value.iec958.status[2] = ctrl->ch_status[2];
	uvalue->value.iec958.status[3] = ctrl->ch_status[3];

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spdअगर_pb_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;

	ctrl->ch_status[0] = uvalue->value.iec958.status[0];
	ctrl->ch_status[1] = uvalue->value.iec958.status[1];
	ctrl->ch_status[2] = uvalue->value.iec958.status[2];
	ctrl->ch_status[3] = uvalue->value.iec958.status[3];

	spdअगर_ग_लिखो_channel_status(spdअगर_priv);

	वापस 0;
पूर्ण

/* Get channel status from SPDIF_RX_CCHAN रेजिस्टर */
अटल पूर्णांक fsl_spdअगर_capture_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 cstatus, val;

	regmap_पढ़ो(regmap, REG_SPDIF_SIS, &val);
	अगर (!(val & INT_CNEW))
		वापस -EAGAIN;

	regmap_पढ़ो(regmap, REG_SPDIF_SRCSH, &cstatus);
	ucontrol->value.iec958.status[0] = (cstatus >> 16) & 0xFF;
	ucontrol->value.iec958.status[1] = (cstatus >> 8) & 0xFF;
	ucontrol->value.iec958.status[2] = cstatus & 0xFF;

	regmap_पढ़ो(regmap, REG_SPDIF_SRCSL, &cstatus);
	ucontrol->value.iec958.status[3] = (cstatus >> 16) & 0xFF;
	ucontrol->value.iec958.status[4] = (cstatus >> 8) & 0xFF;
	ucontrol->value.iec958.status[5] = cstatus & 0xFF;

	/* Clear पूर्णांकr */
	regmap_ग_लिखो(regmap, REG_SPDIF_SIC, INT_CNEW);

	वापस 0;
पूर्ण

/*
 * Get User bits (subcode) from chip value which पढ़ोed out
 * in UChannel रेजिस्टर.
 */
अटल पूर्णांक fsl_spdअगर_subcode_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EAGAIN;

	spin_lock_irqsave(&ctrl->ctl_lock, flags);
	अगर (ctrl->पढ़ोy_buf) अणु
		पूर्णांक idx = (ctrl->पढ़ोy_buf - 1) * SPDIF_UBITS_SIZE;
		स_नकल(&ucontrol->value.iec958.subcode[0],
				&ctrl->subcode[idx], SPDIF_UBITS_SIZE);
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&ctrl->ctl_lock, flags);

	वापस ret;
पूर्ण

/* Q-subcode inक्रमmation. The byte size is SPDIF_UBITS_SIZE/8 */
अटल पूर्णांक fsl_spdअगर_qinfo(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = SPDIF_QSUB_SIZE;

	वापस 0;
पूर्ण

/* Get Q subcode from chip value which पढ़ोed out in QChannel रेजिस्टर */
अटल पूर्णांक fsl_spdअगर_qget(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा spdअगर_mixer_control *ctrl = &spdअगर_priv->fsl_spdअगर_control;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EAGAIN;

	spin_lock_irqsave(&ctrl->ctl_lock, flags);
	अगर (ctrl->पढ़ोy_buf) अणु
		पूर्णांक idx = (ctrl->पढ़ोy_buf - 1) * SPDIF_QSUB_SIZE;
		स_नकल(&ucontrol->value.bytes.data[0],
				&ctrl->qsub[idx], SPDIF_QSUB_SIZE);
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&ctrl->ctl_lock, flags);

	वापस ret;
पूर्ण

/* Get valid good bit from पूर्णांकerrupt status रेजिस्टर */
अटल पूर्णांक fsl_spdअगर_rx_vbit_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 val;

	regmap_पढ़ो(regmap, REG_SPDIF_SIS, &val);
	ucontrol->value.पूर्णांकeger.value[0] = (val & INT_VAL_NOGOOD) != 0;
	regmap_ग_लिखो(regmap, REG_SPDIF_SIC, INT_VAL_NOGOOD);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spdअगर_tx_vbit_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 val;

	regmap_पढ़ो(regmap, REG_SPDIF_SCR, &val);
	val = (val & SCR_VAL_MASK) >> SCR_VAL_OFFSET;
	val = 1 - val;
	ucontrol->value.पूर्णांकeger.value[0] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spdअगर_tx_vbit_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 val = (1 - ucontrol->value.पूर्णांकeger.value[0]) << SCR_VAL_OFFSET;

	regmap_update_bits(regmap, REG_SPDIF_SCR, SCR_VAL_MASK, val);

	वापस 0;
पूर्ण

/* DPLL lock inक्रमmation */
अटल पूर्णांक fsl_spdअगर_rxrate_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 16000;
	uinfo->value.पूर्णांकeger.max = 192000;

	वापस 0;
पूर्ण

अटल u32 gainsel_multi[GAINSEL_MULTI_MAX] = अणु
	24, 16, 12, 8, 6, 4, 3,
पूर्ण;

/* Get RX data घड़ी rate given the SPDIF bus_clk */
अटल पूर्णांक spdअगर_get_rxclk_rate(काष्ठा fsl_spdअगर_priv *spdअगर_priv,
				क्रमागत spdअगर_gainsel gainsel)
अणु
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	u64 पंचांगpval64, busclk_freq = 0;
	u32 freqmeas, phaseconf;
	u8 clksrc;

	regmap_पढ़ो(regmap, REG_SPDIF_SRFM, &freqmeas);
	regmap_पढ़ो(regmap, REG_SPDIF_SRPC, &phaseconf);

	clksrc = (phaseconf >> SRPC_CLKSRC_SEL_OFFSET) & 0xf;

	/* Get bus घड़ी from प्रणाली */
	अगर (srpc_dpll_locked[clksrc] && (phaseconf & SRPC_DPLL_LOCKED))
		busclk_freq = clk_get_rate(spdअगर_priv->sysclk);

	/* FreqMeas_CLK = (BUS_CLK * FreqMeas) / 2 ^ 10 / GAINSEL / 128 */
	पंचांगpval64 = (u64) busclk_freq * freqmeas;
	करो_भाग(पंचांगpval64, gainsel_multi[gainsel] * 1024);
	करो_भाग(पंचांगpval64, 128 * 1024);

	dev_dbg(&pdev->dev, "FreqMeas: %d\n", freqmeas);
	dev_dbg(&pdev->dev, "BusclkFreq: %lld\n", busclk_freq);
	dev_dbg(&pdev->dev, "RxRate: %lld\n", पंचांगpval64);

	वापस (पूर्णांक)पंचांगpval64;
पूर्ण

/*
 * Get DPLL lock or not info from stable पूर्णांकerrupt status रेजिस्टर.
 * User application must use this control to get locked,
 * then can करो next PCM operation
 */
अटल पूर्णांक fsl_spdअगर_rxrate_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक rate = 0;

	अगर (spdअगर_priv->dpll_locked)
		rate = spdअगर_get_rxclk_rate(spdअगर_priv, SPDIF_DEFAULT_GAINSEL);

	ucontrol->value.पूर्णांकeger.value[0] = rate;

	वापस 0;
पूर्ण

/*
 * User bit sync mode:
 * 1 CD User channel subcode
 * 0 Non-CD data
 */
अटल पूर्णांक fsl_spdअगर_usync_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 val;

	regmap_पढ़ो(regmap, REG_SPDIF_SRCD, &val);
	ucontrol->value.पूर्णांकeger.value[0] = (val & SRCD_CD_USER) != 0;

	वापस 0;
पूर्ण

/*
 * User bit sync mode:
 * 1 CD User channel subcode
 * 0 Non-CD data
 */
अटल पूर्णांक fsl_spdअगर_usync_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा regmap *regmap = spdअगर_priv->regmap;
	u32 val = ucontrol->value.पूर्णांकeger.value[0] << SRCD_CD_USER_OFFSET;

	regmap_update_bits(regmap, REG_SPDIF_SRCD, SRCD_CD_USER, val);

	वापस 0;
पूर्ण

/* FSL SPDIF IEC958 controller defines */
अटल काष्ठा snd_kcontrol_new fsl_spdअगर_ctrls[] = अणु
	/* Status cchanel controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_WRITE |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = fsl_spdअगर_info,
		.get = fsl_spdअगर_pb_get,
		.put = fsl_spdअगर_pb_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = fsl_spdअगर_info,
		.get = fsl_spdअगर_capture_get,
	पूर्ण,
	/* User bits controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 Subcode Capture Default",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = fsl_spdअगर_info,
		.get = fsl_spdअगर_subcode_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 Q-subcode Capture Default",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = fsl_spdअगर_qinfo,
		.get = fsl_spdअगर_qget,
	पूर्ण,
	/* Valid bit error controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 RX V-Bit Errors",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_ctl_boolean_mono_info,
		.get = fsl_spdअगर_rx_vbit_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 TX V-Bit",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_WRITE |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_ctl_boolean_mono_info,
		.get = fsl_spdअगर_tx_vbit_get,
		.put = fsl_spdअगर_tx_vbit_put,
	पूर्ण,
	/* DPLL lock info get controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "RX Sample Rate",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = fsl_spdअगर_rxrate_info,
		.get = fsl_spdअगर_rxrate_get,
	पूर्ण,
	/* User bit sync mode set/get controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "IEC958 USyncMode CDText",
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_WRITE |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_ctl_boolean_mono_info,
		.get = fsl_spdअगर_usync_get,
		.put = fsl_spdअगर_usync_put,
	पूर्ण,
पूर्ण;

अटल पूर्णांक fsl_spdअगर_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_spdअगर_priv *spdअगर_निजी = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &spdअगर_निजी->dma_params_tx,
				  &spdअगर_निजी->dma_params_rx);

	snd_soc_add_dai_controls(dai, fsl_spdअगर_ctrls, ARRAY_SIZE(fsl_spdअगर_ctrls));

	/*Clear the val bit क्रम Tx*/
	regmap_update_bits(spdअगर_निजी->regmap, REG_SPDIF_SCR,
			   SCR_VAL_MASK, SCR_VAL_CLEAR);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver fsl_spdअगर_dai = अणु
	.probe = &fsl_spdअगर_dai_probe,
	.playback = अणु
		.stream_name = "CPU-Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = FSL_SPDIF_RATES_PLAYBACK,
		.क्रमmats = FSL_SPDIF_FORMATS_PLAYBACK,
	पूर्ण,
	.capture = अणु
		.stream_name = "CPU-Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = FSL_SPDIF_RATES_CAPTURE,
		.क्रमmats = FSL_SPDIF_FORMATS_CAPTURE,
	पूर्ण,
	.ops = &fsl_spdअगर_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_spdअगर_component = अणु
	.name		= "fsl-spdif",
पूर्ण;

/* FSL SPDIF REGMAP */
अटल स्थिर काष्ठा reg_शेष fsl_spdअगर_reg_शेषs[] = अणु
	अणुREG_SPDIF_SCR,    0x00000400पूर्ण,
	अणुREG_SPDIF_SRCD,   0x00000000पूर्ण,
	अणुREG_SPDIF_SIE,	   0x00000000पूर्ण,
	अणुREG_SPDIF_STL,	   0x00000000पूर्ण,
	अणुREG_SPDIF_STR,	   0x00000000पूर्ण,
	अणुREG_SPDIF_STCSCH, 0x00000000पूर्ण,
	अणुREG_SPDIF_STCSCL, 0x00000000पूर्ण,
	अणुREG_SPDIF_STC,	   0x00020f00पूर्ण,
पूर्ण;

अटल bool fsl_spdअगर_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_SPDIF_SCR:
	हाल REG_SPDIF_SRCD:
	हाल REG_SPDIF_SRPC:
	हाल REG_SPDIF_SIE:
	हाल REG_SPDIF_SIS:
	हाल REG_SPDIF_SRL:
	हाल REG_SPDIF_SRR:
	हाल REG_SPDIF_SRCSH:
	हाल REG_SPDIF_SRCSL:
	हाल REG_SPDIF_SRU:
	हाल REG_SPDIF_SRQ:
	हाल REG_SPDIF_STCSCH:
	हाल REG_SPDIF_STCSCL:
	हाल REG_SPDIF_SRFM:
	हाल REG_SPDIF_STC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_spdअगर_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_SPDIF_SRPC:
	हाल REG_SPDIF_SIS:
	हाल REG_SPDIF_SRL:
	हाल REG_SPDIF_SRR:
	हाल REG_SPDIF_SRCSH:
	हाल REG_SPDIF_SRCSL:
	हाल REG_SPDIF_SRU:
	हाल REG_SPDIF_SRQ:
	हाल REG_SPDIF_SRFM:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_spdअगर_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_SPDIF_SCR:
	हाल REG_SPDIF_SRCD:
	हाल REG_SPDIF_SRPC:
	हाल REG_SPDIF_SIE:
	हाल REG_SPDIF_SIC:
	हाल REG_SPDIF_STL:
	हाल REG_SPDIF_STR:
	हाल REG_SPDIF_STCSCH:
	हाल REG_SPDIF_STCSCL:
	हाल REG_SPDIF_STC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_spdअगर_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.max_रेजिस्टर = REG_SPDIF_STC,
	.reg_शेषs = fsl_spdअगर_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(fsl_spdअगर_reg_शेषs),
	.पढ़ोable_reg = fsl_spdअगर_पढ़ोable_reg,
	.अस्थिर_reg = fsl_spdअगर_अस्थिर_reg,
	.ग_लिखोable_reg = fsl_spdअगर_ग_लिखोable_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल u32 fsl_spdअगर_txclk_caद_भाग(काष्ठा fsl_spdअगर_priv *spdअगर_priv,
				काष्ठा clk *clk, u64 savesub,
				क्रमागत spdअगर_txrate index, bool round)
अणु
	अटल स्थिर u32 rate[] = अणु 32000, 44100, 48000, 88200, 96000, 176400,
				    192000, पूर्ण;
	bool is_sysclk = clk_is_match(clk, spdअगर_priv->sysclk);
	u64 rate_ideal, rate_actual, sub;
	u32 arate;
	u16 sysclk_dfmin, sysclk_dfmax, sysclk_df;
	u8 txclk_df;

	/* The sysclk has an extra भागisor [2, 512] */
	sysclk_dfmin = is_sysclk ? 2 : 1;
	sysclk_dfmax = is_sysclk ? 512 : 1;

	क्रम (sysclk_df = sysclk_dfmin; sysclk_df <= sysclk_dfmax; sysclk_df++) अणु
		क्रम (txclk_df = 1; txclk_df <= 128; txclk_df++) अणु
			rate_ideal = rate[index] * txclk_df * 64ULL;
			अगर (round)
				rate_actual = clk_round_rate(clk, rate_ideal);
			अन्यथा
				rate_actual = clk_get_rate(clk);

			arate = rate_actual / 64;
			arate /= txclk_df * sysclk_df;

			अगर (arate == rate[index]) अणु
				/* We are lucky */
				savesub = 0;
				spdअगर_priv->txclk_df[index] = txclk_df;
				spdअगर_priv->sysclk_df[index] = sysclk_df;
				spdअगर_priv->txrate[index] = arate;
				जाओ out;
			पूर्ण अन्यथा अगर (arate / rate[index] == 1) अणु
				/* A little bigger than expect */
				sub = (u64)(arate - rate[index]) * 100000;
				करो_भाग(sub, rate[index]);
				अगर (sub >= savesub)
					जारी;
				savesub = sub;
				spdअगर_priv->txclk_df[index] = txclk_df;
				spdअगर_priv->sysclk_df[index] = sysclk_df;
				spdअगर_priv->txrate[index] = arate;
			पूर्ण अन्यथा अगर (rate[index] / arate == 1) अणु
				/* A little smaller than expect */
				sub = (u64)(rate[index] - arate) * 100000;
				करो_भाग(sub, rate[index]);
				अगर (sub >= savesub)
					जारी;
				savesub = sub;
				spdअगर_priv->txclk_df[index] = txclk_df;
				spdअगर_priv->sysclk_df[index] = sysclk_df;
				spdअगर_priv->txrate[index] = arate;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस savesub;
पूर्ण

अटल पूर्णांक fsl_spdअगर_probe_txclk(काष्ठा fsl_spdअगर_priv *spdअगर_priv,
				क्रमागत spdअगर_txrate index)
अणु
	अटल स्थिर u32 rate[] = अणु 32000, 44100, 48000, 88200, 96000, 176400,
				    192000, पूर्ण;
	काष्ठा platक्रमm_device *pdev = spdअगर_priv->pdev;
	काष्ठा device *dev = &pdev->dev;
	u64 savesub = 100000, ret;
	काष्ठा clk *clk;
	अक्षर पंचांगp[16];
	पूर्णांक i;

	क्रम (i = 0; i < STC_TXCLK_SRC_MAX; i++) अणु
		प्र_लिखो(पंचांगp, "rxtx%d", i);
		clk = devm_clk_get(dev, पंचांगp);
		अगर (IS_ERR(clk)) अणु
			dev_err(dev, "no rxtx%d clock in devicetree\n", i);
			वापस PTR_ERR(clk);
		पूर्ण
		अगर (!clk_get_rate(clk))
			जारी;

		ret = fsl_spdअगर_txclk_caद_भाग(spdअगर_priv, clk, savesub, index,
					     fsl_spdअगर_can_set_clk_rate(spdअगर_priv, i));
		अगर (savesub == ret)
			जारी;

		savesub = ret;
		spdअगर_priv->txclk[index] = clk;
		spdअगर_priv->txclk_src[index] = i;

		/* To quick catch a भागisor, we allow a 0.1% deviation */
		अगर (savesub < 100)
			अवरोध;
	पूर्ण

	dev_dbg(dev, "use rxtx%d as tx clock source for %dHz sample rate\n",
			spdअगर_priv->txclk_src[index], rate[index]);
	dev_dbg(dev, "use txclk df %d for %dHz sample rate\n",
			spdअगर_priv->txclk_df[index], rate[index]);
	अगर (clk_is_match(spdअगर_priv->txclk[index], spdअगर_priv->sysclk))
		dev_dbg(dev, "use sysclk df %d for %dHz sample rate\n",
				spdअगर_priv->sysclk_df[index], rate[index]);
	dev_dbg(dev, "the best rate for %dHz sample rate is %dHz\n",
			rate[index], spdअगर_priv->txrate[index]);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spdअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_spdअगर_priv *spdअगर_priv;
	काष्ठा spdअगर_mixer_control *ctrl;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक irq, ret, i;

	spdअगर_priv = devm_kzalloc(&pdev->dev, माप(*spdअगर_priv), GFP_KERNEL);
	अगर (!spdअगर_priv)
		वापस -ENOMEM;

	spdअगर_priv->pdev = pdev;

	spdअगर_priv->soc = of_device_get_match_data(&pdev->dev);

	/* Initialize this copy of the CPU DAI driver काष्ठाure */
	स_नकल(&spdअगर_priv->cpu_dai_drv, &fsl_spdअगर_dai, माप(fsl_spdअगर_dai));
	spdअगर_priv->cpu_dai_drv.name = dev_name(&pdev->dev);
	spdअगर_priv->cpu_dai_drv.playback.क्रमmats =
				spdअगर_priv->soc->tx_क्रमmats;

	/* Get the addresses and IRQ */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	spdअगर_priv->regmap = devm_regmap_init_mmio(&pdev->dev, regs, &fsl_spdअगर_regmap_config);
	अगर (IS_ERR(spdअगर_priv->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		वापस PTR_ERR(spdअगर_priv->regmap);
	पूर्ण

	क्रम (i = 0; i < spdअगर_priv->soc->पूर्णांकerrupts; i++) अणु
		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0) अणु
			dev_err(&pdev->dev, "no irq for node %s\n", pdev->name);
			वापस irq;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, irq, spdअगर_isr, 0,
				       dev_name(&pdev->dev), spdअगर_priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "could not claim irq %u\n", irq);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Get प्रणाली घड़ी क्रम rx घड़ी rate calculation */
	spdअगर_priv->sysclk = devm_clk_get(&pdev->dev, "rxtx5");
	अगर (IS_ERR(spdअगर_priv->sysclk)) अणु
		dev_err(&pdev->dev, "no sys clock (rxtx5) in devicetree\n");
		वापस PTR_ERR(spdअगर_priv->sysclk);
	पूर्ण

	/* Get core घड़ी क्रम data रेजिस्टर access via DMA */
	spdअगर_priv->coreclk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(spdअगर_priv->coreclk)) अणु
		dev_err(&pdev->dev, "no core clock in devicetree\n");
		वापस PTR_ERR(spdअगर_priv->coreclk);
	पूर्ण

	spdअगर_priv->spbaclk = devm_clk_get(&pdev->dev, "spba");
	अगर (IS_ERR(spdअगर_priv->spbaclk))
		dev_warn(&pdev->dev, "no spba clock in devicetree\n");

	/* Select घड़ी source क्रम rx/tx घड़ी */
	spdअगर_priv->rxclk = devm_clk_get(&pdev->dev, "rxtx1");
	अगर (IS_ERR(spdअगर_priv->rxclk)) अणु
		dev_err(&pdev->dev, "no rxtx1 clock in devicetree\n");
		वापस PTR_ERR(spdअगर_priv->rxclk);
	पूर्ण
	spdअगर_priv->rxclk_src = DEFAULT_RXCLK_SRC;

	क्रम (i = 0; i < SPDIF_TXRATE_MAX; i++) अणु
		ret = fsl_spdअगर_probe_txclk(spdअगर_priv, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Initial spinlock क्रम control data */
	ctrl = &spdअगर_priv->fsl_spdअगर_control;
	spin_lock_init(&ctrl->ctl_lock);

	/* Init tx channel status शेष value */
	ctrl->ch_status[0] = IEC958_AES0_CON_NOT_COPYRIGHT |
			     IEC958_AES0_CON_EMPHASIS_5015;
	ctrl->ch_status[1] = IEC958_AES1_CON_DIGDIGCONV_ID;
	ctrl->ch_status[2] = 0x00;
	ctrl->ch_status[3] = IEC958_AES3_CON_FS_44100 |
			     IEC958_AES3_CON_CLOCK_1000PPM;

	spdअगर_priv->dpll_locked = false;

	spdअगर_priv->dma_params_tx.maxburst = spdअगर_priv->soc->tx_burst;
	spdअगर_priv->dma_params_rx.maxburst = spdअगर_priv->soc->rx_burst;
	spdअगर_priv->dma_params_tx.addr = res->start + REG_SPDIF_STL;
	spdअगर_priv->dma_params_rx.addr = res->start + REG_SPDIF_SRL;

	/* Register with ASoC */
	dev_set_drvdata(&pdev->dev, spdअगर_priv);
	pm_runसमय_enable(&pdev->dev);
	regcache_cache_only(spdअगर_priv->regmap, true);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &fsl_spdअगर_component,
					      &spdअगर_priv->cpu_dai_drv, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register DAI: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = imx_pcm_dma_init(pdev, IMX_SPDIF_DMABUF_SIZE);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "imx_pcm_dma_init failed: %d\n", ret);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fsl_spdअगर_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = dev_get_drvdata(dev);
	पूर्णांक i;

	regmap_पढ़ो(spdअगर_priv->regmap, REG_SPDIF_SRPC,
			&spdअगर_priv->regcache_srpc);
	regcache_cache_only(spdअगर_priv->regmap, true);

	clk_disable_unprepare(spdअगर_priv->rxclk);

	क्रम (i = 0; i < SPDIF_TXRATE_MAX; i++)
		clk_disable_unprepare(spdअगर_priv->txclk[i]);

	अगर (!IS_ERR(spdअगर_priv->spbaclk))
		clk_disable_unprepare(spdअगर_priv->spbaclk);
	clk_disable_unprepare(spdअगर_priv->coreclk);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_spdअगर_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_spdअगर_priv *spdअगर_priv = dev_get_drvdata(dev);
	पूर्णांक ret;
	पूर्णांक i;

	ret = clk_prepare_enable(spdअगर_priv->coreclk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable core clock\n");
		वापस ret;
	पूर्ण

	अगर (!IS_ERR(spdअगर_priv->spbaclk)) अणु
		ret = clk_prepare_enable(spdअगर_priv->spbaclk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable spba clock\n");
			जाओ disable_core_clk;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SPDIF_TXRATE_MAX; i++) अणु
		ret = clk_prepare_enable(spdअगर_priv->txclk[i]);
		अगर (ret)
			जाओ disable_tx_clk;
	पूर्ण

	ret = clk_prepare_enable(spdअगर_priv->rxclk);
	अगर (ret)
		जाओ disable_tx_clk;

	regcache_cache_only(spdअगर_priv->regmap, false);
	regcache_mark_dirty(spdअगर_priv->regmap);

	regmap_update_bits(spdअगर_priv->regmap, REG_SPDIF_SRPC,
			SRPC_CLKSRC_SEL_MASK | SRPC_GAINSEL_MASK,
			spdअगर_priv->regcache_srpc);

	ret = regcache_sync(spdअगर_priv->regmap);
	अगर (ret)
		जाओ disable_rx_clk;

	वापस 0;

disable_rx_clk:
	clk_disable_unprepare(spdअगर_priv->rxclk);
disable_tx_clk:
	क्रम (i--; i >= 0; i--)
		clk_disable_unprepare(spdअगर_priv->txclk[i]);
	अगर (!IS_ERR(spdअगर_priv->spbaclk))
		clk_disable_unprepare(spdअगर_priv->spbaclk);
disable_core_clk:
	clk_disable_unprepare(spdअगर_priv->coreclk);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops fsl_spdअगर_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(fsl_spdअगर_runसमय_suspend, fsl_spdअगर_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_spdअगर_dt_ids[] = अणु
	अणु .compatible = "fsl,imx35-spdif", .data = &fsl_spdअगर_imx35, पूर्ण,
	अणु .compatible = "fsl,vf610-spdif", .data = &fsl_spdअगर_vf610, पूर्ण,
	अणु .compatible = "fsl,imx6sx-spdif", .data = &fsl_spdअगर_imx6sx, पूर्ण,
	अणु .compatible = "fsl,imx8qm-spdif", .data = &fsl_spdअगर_imx8qm, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_spdअगर_dt_ids);

अटल काष्ठा platक्रमm_driver fsl_spdअगर_driver = अणु
	.driver = अणु
		.name = "fsl-spdif-dai",
		.of_match_table = fsl_spdअगर_dt_ids,
		.pm = &fsl_spdअगर_pm,
	पूर्ण,
	.probe = fsl_spdअगर_probe,
पूर्ण;

module_platक्रमm_driver(fsl_spdअगर_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Freescale S/PDIF CPU DAI Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:fsl-spdif-dai");
