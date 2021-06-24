<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC McASP Audio Layer क्रम TI DAVINCI processor
 *
 * Multi-channel Audio Serial Port Driver
 *
 * Author: Nirmal Pandey <n-pandey@ti.com>,
 *         Suresh Rajashekara <suresh.r@ti.com>
 *         Steve Chen <schen@.mvista.com>
 *
 * Copyright:   (C) 2009 MontaVista Software, Inc., <source@mvista.com>
 * Copyright:   (C) 2009  Texas Instruments, India
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_data/davinci_asp.h>
#समावेश <linux/math64.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/gpio/driver.h>

#समावेश <sound/asoundef.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "edma-pcm.h"
#समावेश "sdma-pcm.h"
#समावेश "udma-pcm.h"
#समावेश "davinci-mcasp.h"

#घोषणा MCASP_MAX_AFIFO_DEPTH	64

#अगर_घोषित CONFIG_PM
अटल u32 context_regs[] = अणु
	DAVINCI_MCASP_TXFMCTL_REG,
	DAVINCI_MCASP_RXFMCTL_REG,
	DAVINCI_MCASP_TXFMT_REG,
	DAVINCI_MCASP_RXFMT_REG,
	DAVINCI_MCASP_ACLKXCTL_REG,
	DAVINCI_MCASP_ACLKRCTL_REG,
	DAVINCI_MCASP_AHCLKXCTL_REG,
	DAVINCI_MCASP_AHCLKRCTL_REG,
	DAVINCI_MCASP_Pसूची_REG,
	DAVINCI_MCASP_PFUNC_REG,
	DAVINCI_MCASP_RXMASK_REG,
	DAVINCI_MCASP_TXMASK_REG,
	DAVINCI_MCASP_RXTDM_REG,
	DAVINCI_MCASP_TXTDM_REG,
पूर्ण;

काष्ठा davinci_mcasp_context अणु
	u32	config_regs[ARRAY_SIZE(context_regs)];
	u32	afअगरo_regs[2]; /* क्रम पढ़ो/ग_लिखो fअगरo control रेजिस्टरs */
	u32	*xrsr_regs; /* क्रम serializer configuration */
	bool	pm_state;
पूर्ण;
#पूर्ण_अगर

काष्ठा davinci_mcasp_ruledata अणु
	काष्ठा davinci_mcasp *mcasp;
	पूर्णांक serializers;
पूर्ण;

काष्ठा davinci_mcasp अणु
	काष्ठा snd_dmaengine_dai_dma_data dma_data[2];
	काष्ठा davinci_mcasp_pdata *pdata;
	व्योम __iomem *base;
	u32 fअगरo_base;
	काष्ठा device *dev;
	काष्ठा snd_pcm_substream *substreams[2];
	अचिन्हित पूर्णांक dai_fmt;

	/* Audio can not be enabled due to missing parameter(s) */
	bool	missing_audio_param;

	/* McASP specअगरic data */
	पूर्णांक	tdm_slots;
	u32	tdm_mask[2];
	पूर्णांक	slot_width;
	u8	op_mode;
	u8	dismod;
	u8	num_serializer;
	u8	*serial_dir;
	u8	version;
	u8	bclk_भाग;
	पूर्णांक	streams;
	u32	irq_request[2];

	पूर्णांक	sysclk_freq;
	bool	bclk_master;
	u32	auxclk_fs_ratio;

	अचिन्हित दीर्घ pdir; /* Pin direction bitfield */

	/* McASP FIFO related */
	u8	txnumevt;
	u8	rxnumevt;

	bool	dat_port;

	/* Used क्रम comstraपूर्णांक setting on the second stream */
	u32	channels;
	पूर्णांक	max_क्रमmat_width;
	u8	active_serializers[2];

#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio_chip;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
	काष्ठा davinci_mcasp_context context;
#पूर्ण_अगर

	काष्ठा davinci_mcasp_ruledata ruledata[2];
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list chस्थिरr[2];
पूर्ण;

अटल अंतरभूत व्योम mcasp_set_bits(काष्ठा davinci_mcasp *mcasp, u32 offset,
				  u32 val)
अणु
	व्योम __iomem *reg = mcasp->base + offset;
	__raw_ग_लिखोl(__raw_पढ़ोl(reg) | val, reg);
पूर्ण

अटल अंतरभूत व्योम mcasp_clr_bits(काष्ठा davinci_mcasp *mcasp, u32 offset,
				  u32 val)
अणु
	व्योम __iomem *reg = mcasp->base + offset;
	__raw_ग_लिखोl((__raw_पढ़ोl(reg) & ~(val)), reg);
पूर्ण

अटल अंतरभूत व्योम mcasp_mod_bits(काष्ठा davinci_mcasp *mcasp, u32 offset,
				  u32 val, u32 mask)
अणु
	व्योम __iomem *reg = mcasp->base + offset;
	__raw_ग_लिखोl((__raw_पढ़ोl(reg) & ~mask) | val, reg);
पूर्ण

अटल अंतरभूत व्योम mcasp_set_reg(काष्ठा davinci_mcasp *mcasp, u32 offset,
				 u32 val)
अणु
	__raw_ग_लिखोl(val, mcasp->base + offset);
पूर्ण

अटल अंतरभूत u32 mcasp_get_reg(काष्ठा davinci_mcasp *mcasp, u32 offset)
अणु
	वापस (u32)__raw_पढ़ोl(mcasp->base + offset);
पूर्ण

अटल व्योम mcasp_set_ctl_reg(काष्ठा davinci_mcasp *mcasp, u32 ctl_reg, u32 val)
अणु
	पूर्णांक i = 0;

	mcasp_set_bits(mcasp, ctl_reg, val);

	/* programming GBLCTL needs to पढ़ो back from GBLCTL and verfiy */
	/* loop count is to aव्योम the lock-up */
	क्रम (i = 0; i < 1000; i++) अणु
		अगर ((mcasp_get_reg(mcasp, ctl_reg) & val) == val)
			अवरोध;
	पूर्ण

	अगर (i == 1000 && ((mcasp_get_reg(mcasp, ctl_reg) & val) != val))
		prपूर्णांकk(KERN_ERR "GBLCTL write error\n");
पूर्ण

अटल bool mcasp_is_synchronous(काष्ठा davinci_mcasp *mcasp)
अणु
	u32 rxfmctl = mcasp_get_reg(mcasp, DAVINCI_MCASP_RXFMCTL_REG);
	u32 aclkxctl = mcasp_get_reg(mcasp, DAVINCI_MCASP_ACLKXCTL_REG);

	वापस !(aclkxctl & TX_ASYNC) && rxfmctl & AFSRE;
पूर्ण

अटल अंतरभूत व्योम mcasp_set_clk_pdir(काष्ठा davinci_mcasp *mcasp, bool enable)
अणु
	u32 bit = PIN_BIT_AMUTE;

	क्रम_each_set_bit_from(bit, &mcasp->pdir, PIN_BIT_AFSR + 1) अणु
		अगर (enable)
			mcasp_set_bits(mcasp, DAVINCI_MCASP_Pसूची_REG, BIT(bit));
		अन्यथा
			mcasp_clr_bits(mcasp, DAVINCI_MCASP_Pसूची_REG, BIT(bit));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mcasp_set_axr_pdir(काष्ठा davinci_mcasp *mcasp, bool enable)
अणु
	u32 bit;

	क्रम_each_set_bit(bit, &mcasp->pdir, PIN_BIT_AMUTE) अणु
		अगर (enable)
			mcasp_set_bits(mcasp, DAVINCI_MCASP_Pसूची_REG, BIT(bit));
		अन्यथा
			mcasp_clr_bits(mcasp, DAVINCI_MCASP_Pसूची_REG, BIT(bit));
	पूर्ण
पूर्ण

अटल व्योम mcasp_start_rx(काष्ठा davinci_mcasp *mcasp)
अणु
	अगर (mcasp->rxnumevt) अणु	/* enable FIFO */
		u32 reg = mcasp->fअगरo_base + MCASP_RFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
		mcasp_set_bits(mcasp, reg, FIFO_ENABLE);
	पूर्ण

	/* Start घड़ीs */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXHCLKRST);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXCLKRST);
	/*
	 * When ASYNC == 0 the transmit and receive sections operate
	 * synchronously from the transmit घड़ी and frame sync. We need to make
	 * sure that the TX signlas are enabled when starting reception.
	 */
	अगर (mcasp_is_synchronous(mcasp)) अणु
		mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXHCLKRST);
		mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXCLKRST);
		mcasp_set_clk_pdir(mcasp, true);
	पूर्ण

	/* Activate serializer(s) */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, 0xFFFFFFFF);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXSERCLR);
	/* Release RX state machine */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXSMRST);
	/* Release Frame Sync generator */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXFSRST);
	अगर (mcasp_is_synchronous(mcasp))
		mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXFSRST);

	/* enable receive IRQs */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_EVTCTLR_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_CAPTURE]);
पूर्ण

अटल व्योम mcasp_start_tx(काष्ठा davinci_mcasp *mcasp)
अणु
	u32 cnt;

	अगर (mcasp->txnumevt) अणु	/* enable FIFO */
		u32 reg = mcasp->fअगरo_base + MCASP_WFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
		mcasp_set_bits(mcasp, reg, FIFO_ENABLE);
	पूर्ण

	/* Start घड़ीs */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXHCLKRST);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXCLKRST);
	mcasp_set_clk_pdir(mcasp, true);

	/* Activate serializer(s) */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, 0xFFFFFFFF);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXSERCLR);

	/* रुको क्रम XDATA to be cleared */
	cnt = 0;
	जबतक ((mcasp_get_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG) & XRDATA) &&
	       (cnt < 100000))
		cnt++;

	mcasp_set_axr_pdir(mcasp, true);

	/* Release TX state machine */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXSMRST);
	/* Release Frame Sync generator */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXFSRST);

	/* enable transmit IRQs */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_EVTCTLX_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_PLAYBACK]);
पूर्ण

अटल व्योम davinci_mcasp_start(काष्ठा davinci_mcasp *mcasp, पूर्णांक stream)
अणु
	mcasp->streams++;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		mcasp_start_tx(mcasp);
	अन्यथा
		mcasp_start_rx(mcasp);
पूर्ण

अटल व्योम mcasp_stop_rx(काष्ठा davinci_mcasp *mcasp)
अणु
	/* disable IRQ sources */
	mcasp_clr_bits(mcasp, DAVINCI_MCASP_EVTCTLR_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_CAPTURE]);

	/*
	 * In synchronous mode stop the TX घड़ीs अगर no other stream is
	 * running
	 */
	अगर (mcasp_is_synchronous(mcasp) && !mcasp->streams) अणु
		mcasp_set_clk_pdir(mcasp, false);
		mcasp_set_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, 0);
	पूर्ण

	mcasp_set_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, 0);
	mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, 0xFFFFFFFF);

	अगर (mcasp->rxnumevt) अणु	/* disable FIFO */
		u32 reg = mcasp->fअगरo_base + MCASP_RFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
	पूर्ण
पूर्ण

अटल व्योम mcasp_stop_tx(काष्ठा davinci_mcasp *mcasp)
अणु
	u32 val = 0;

	/* disable IRQ sources */
	mcasp_clr_bits(mcasp, DAVINCI_MCASP_EVTCTLX_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_PLAYBACK]);

	/*
	 * In synchronous mode keep TX घड़ीs running अगर the capture stream is
	 * still running.
	 */
	अगर (mcasp_is_synchronous(mcasp) && mcasp->streams)
		val =  TXHCLKRST | TXCLKRST | TXFSRST;
	अन्यथा
		mcasp_set_clk_pdir(mcasp, false);


	mcasp_set_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, val);
	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, 0xFFFFFFFF);

	अगर (mcasp->txnumevt) अणु	/* disable FIFO */
		u32 reg = mcasp->fअगरo_base + MCASP_WFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
	पूर्ण

	mcasp_set_axr_pdir(mcasp, false);
पूर्ण

अटल व्योम davinci_mcasp_stop(काष्ठा davinci_mcasp *mcasp, पूर्णांक stream)
अणु
	mcasp->streams--;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		mcasp_stop_tx(mcasp);
	अन्यथा
		mcasp_stop_rx(mcasp);
पूर्ण

अटल irqवापस_t davinci_mcasp_tx_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा davinci_mcasp *mcasp = (काष्ठा davinci_mcasp *)data;
	काष्ठा snd_pcm_substream *substream;
	u32 irq_mask = mcasp->irq_request[SNDRV_PCM_STREAM_PLAYBACK];
	u32 handled_mask = 0;
	u32 stat;

	stat = mcasp_get_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG);
	अगर (stat & XUNDRN & irq_mask) अणु
		dev_warn(mcasp->dev, "Transmit buffer underflow\n");
		handled_mask |= XUNDRN;

		substream = mcasp->substreams[SNDRV_PCM_STREAM_PLAYBACK];
		अगर (substream)
			snd_pcm_stop_xrun(substream);
	पूर्ण

	अगर (!handled_mask)
		dev_warn(mcasp->dev, "unhandled tx event. txstat: 0x%08x\n",
			 stat);

	अगर (stat & XRERR)
		handled_mask |= XRERR;

	/* Ack the handled event only */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, handled_mask);

	वापस IRQ_RETVAL(handled_mask);
पूर्ण

अटल irqवापस_t davinci_mcasp_rx_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा davinci_mcasp *mcasp = (काष्ठा davinci_mcasp *)data;
	काष्ठा snd_pcm_substream *substream;
	u32 irq_mask = mcasp->irq_request[SNDRV_PCM_STREAM_CAPTURE];
	u32 handled_mask = 0;
	u32 stat;

	stat = mcasp_get_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG);
	अगर (stat & ROVRN & irq_mask) अणु
		dev_warn(mcasp->dev, "Receive buffer overflow\n");
		handled_mask |= ROVRN;

		substream = mcasp->substreams[SNDRV_PCM_STREAM_CAPTURE];
		अगर (substream)
			snd_pcm_stop_xrun(substream);
	पूर्ण

	अगर (!handled_mask)
		dev_warn(mcasp->dev, "unhandled rx event. rxstat: 0x%08x\n",
			 stat);

	अगर (stat & XRERR)
		handled_mask |= XRERR;

	/* Ack the handled event only */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, handled_mask);

	वापस IRQ_RETVAL(handled_mask);
पूर्ण

अटल irqवापस_t davinci_mcasp_common_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा davinci_mcasp *mcasp = (काष्ठा davinci_mcasp *)data;
	irqवापस_t ret = IRQ_NONE;

	अगर (mcasp->substreams[SNDRV_PCM_STREAM_PLAYBACK])
		ret = davinci_mcasp_tx_irq_handler(irq, data);

	अगर (mcasp->substreams[SNDRV_PCM_STREAM_CAPTURE])
		ret |= davinci_mcasp_rx_irq_handler(irq, data);

	वापस ret;
पूर्ण

अटल पूर्णांक davinci_mcasp_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
					 अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret = 0;
	u32 data_delay;
	bool fs_pol_rising;
	bool inv_fs = false;

	अगर (!fmt)
		वापस 0;

	pm_runसमय_get_sync(mcasp->dev);
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* 1st data bit occur one ACLK cycle after the frame sync */
		data_delay = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
	हाल SND_SOC_DAIFMT_AC97:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* No delay after FS */
		data_delay = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		/* configure a full-word SYNC pulse (LRCLK) */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* 1st data bit occur one ACLK cycle after the frame sync */
		data_delay = 1;
		/* FS need to be inverted */
		inv_fs = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		/* configure a full-word SYNC pulse (LRCLK) */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* No delay after FS */
		data_delay = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, FSXDLY(data_delay),
		       FSXDLY(3));
	mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, FSRDLY(data_delay),
		       FSRDLY(3));

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* codec is घड़ी and frame slave */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		set_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		set_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		set_bit(PIN_BIT_AFSX, &mcasp->pdir);
		set_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		/* codec is घड़ी slave and frame master */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		set_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		set_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		clear_bit(PIN_BIT_AFSX, &mcasp->pdir);
		clear_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		/* codec is घड़ी master and frame slave */
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		clear_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		clear_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		set_bit(PIN_BIT_AFSX, &mcasp->pdir);
		set_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* codec is घड़ी and frame master */
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		clear_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		clear_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		clear_bit(PIN_BIT_AFSX, &mcasp->pdir);
		clear_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_NF:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = true;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (inv_fs)
		fs_pol_rising = !fs_pol_rising;

	अगर (fs_pol_rising) अणु
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXPOL);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRPOL);
	पूर्ण अन्यथा अणु
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXPOL);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRPOL);
	पूर्ण

	mcasp->dai_fmt = fmt;
out:
	pm_runसमय_put(mcasp->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक __davinci_mcasp_set_clkभाग(काष्ठा davinci_mcasp *mcasp, पूर्णांक भाग_id,
				      पूर्णांक भाग, bool explicit)
अणु
	pm_runसमय_get_sync(mcasp->dev);
	चयन (भाग_id) अणु
	हाल MCASP_CLKDIV_AUXCLK:			/* MCLK भागider */
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG,
			       AHCLKXDIV(भाग - 1), AHCLKXDIV_MASK);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_AHCLKRCTL_REG,
			       AHCLKRDIV(भाग - 1), AHCLKRDIV_MASK);
		अवरोध;

	हाल MCASP_CLKDIV_BCLK:			/* BCLK भागider */
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG,
			       ACLKXDIV(भाग - 1), ACLKXDIV_MASK);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG,
			       ACLKRDIV(भाग - 1), ACLKRDIV_MASK);
		अगर (explicit)
			mcasp->bclk_भाग = भाग;
		अवरोध;

	हाल MCASP_CLKDIV_BCLK_FS_RATIO:
		/*
		 * BCLK/LRCLK ratio descries how many bit-घड़ी cycles
		 * fit पूर्णांकo one frame. The घड़ी ratio is given क्रम a
		 * full period of data (क्रम I2S क्रमmat both left and
		 * right channels), so it has to be भागided by number
		 * of tdm-slots (क्रम I2S - भागided by 2).
		 * Instead of storing this ratio, we calculate a new
		 * tdm_slot width by भागiding the ratio by the
		 * number of configured tdm slots.
		 */
		mcasp->slot_width = भाग / mcasp->tdm_slots;
		अगर (भाग % mcasp->tdm_slots)
			dev_warn(mcasp->dev,
				 "%s(): BCLK/LRCLK %d is not divisible by %d tdm slots",
				 __func__, भाग, mcasp->tdm_slots);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_put(mcasp->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mcasp_set_clkभाग(काष्ठा snd_soc_dai *dai, पूर्णांक भाग_id,
				    पूर्णांक भाग)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(dai);

	वापस __davinci_mcasp_set_clkभाग(mcasp, भाग_id, भाग, 1);
पूर्ण

अटल पूर्णांक davinci_mcasp_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				    अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(dai);

	pm_runसमय_get_sync(mcasp->dev);

	अगर (dir == SND_SOC_CLOCK_IN) अणु
		चयन (clk_id) अणु
		हाल MCASP_CLK_HCLK_AHCLK:
			mcasp_clr_bits(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG,
				       AHCLKXE);
			mcasp_clr_bits(mcasp, DAVINCI_MCASP_AHCLKRCTL_REG,
				       AHCLKRE);
			clear_bit(PIN_BIT_AHCLKX, &mcasp->pdir);
			अवरोध;
		हाल MCASP_CLK_HCLK_AUXCLK:
			mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG,
				       AHCLKXE);
			mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCLKRCTL_REG,
				       AHCLKRE);
			set_bit(PIN_BIT_AHCLKX, &mcasp->pdir);
			अवरोध;
		शेष:
			dev_err(mcasp->dev, "Invalid clk id: %d\n", clk_id);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Select AUXCLK as HCLK */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG, AHCLKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCLKRCTL_REG, AHCLKRE);
		set_bit(PIN_BIT_AHCLKX, &mcasp->pdir);
	पूर्ण
	/*
	 * When AHCLK X/R is selected to be output it means that the HCLK is
	 * the same घड़ी - coming via AUXCLK.
	 */
	mcasp->sysclk_freq = freq;
out:
	pm_runसमय_put(mcasp->dev);
	वापस 0;
पूर्ण

/* All serializers must have equal number of channels */
अटल पूर्णांक davinci_mcasp_ch_स्थिरraपूर्णांक(काष्ठा davinci_mcasp *mcasp, पूर्णांक stream,
				       पूर्णांक serializers)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *cl = &mcasp->chस्थिरr[stream];
	अचिन्हित पूर्णांक *list = (अचिन्हित पूर्णांक *) cl->list;
	पूर्णांक slots = mcasp->tdm_slots;
	पूर्णांक i, count = 0;

	अगर (mcasp->tdm_mask[stream])
		slots = hweight32(mcasp->tdm_mask[stream]);

	क्रम (i = 1; i <= slots; i++)
		list[count++] = i;

	क्रम (i = 2; i <= serializers; i++)
		list[count++] = i*slots;

	cl->count = count;

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mcasp_set_ch_स्थिरraपूर्णांकs(काष्ठा davinci_mcasp *mcasp)
अणु
	पूर्णांक rx_serializers = 0, tx_serializers = 0, ret, i;

	क्रम (i = 0; i < mcasp->num_serializer; i++)
		अगर (mcasp->serial_dir[i] == TX_MODE)
			tx_serializers++;
		अन्यथा अगर (mcasp->serial_dir[i] == RX_MODE)
			rx_serializers++;

	ret = davinci_mcasp_ch_स्थिरraपूर्णांक(mcasp, SNDRV_PCM_STREAM_PLAYBACK,
					  tx_serializers);
	अगर (ret)
		वापस ret;

	ret = davinci_mcasp_ch_स्थिरraपूर्णांक(mcasp, SNDRV_PCM_STREAM_CAPTURE,
					  rx_serializers);

	वापस ret;
पूर्ण


अटल पूर्णांक davinci_mcasp_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				      अचिन्हित पूर्णांक tx_mask,
				      अचिन्हित पूर्णांक rx_mask,
				      पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(dai);

	dev_dbg(mcasp->dev,
		 "%s() tx_mask 0x%08x rx_mask 0x%08x slots %d width %d\n",
		 __func__, tx_mask, rx_mask, slots, slot_width);

	अगर (tx_mask >= (1<<slots) || rx_mask >= (1<<slots)) अणु
		dev_err(mcasp->dev,
			"Bad tdm mask tx: 0x%08x rx: 0x%08x slots %d\n",
			tx_mask, rx_mask, slots);
		वापस -EINVAL;
	पूर्ण

	अगर (slot_width &&
	    (slot_width < 8 || slot_width > 32 || slot_width % 4 != 0)) अणु
		dev_err(mcasp->dev, "%s: Unsupported slot_width %d\n",
			__func__, slot_width);
		वापस -EINVAL;
	पूर्ण

	mcasp->tdm_slots = slots;
	mcasp->tdm_mask[SNDRV_PCM_STREAM_PLAYBACK] = tx_mask;
	mcasp->tdm_mask[SNDRV_PCM_STREAM_CAPTURE] = rx_mask;
	mcasp->slot_width = slot_width;

	वापस davinci_mcasp_set_ch_स्थिरraपूर्णांकs(mcasp);
पूर्ण

अटल पूर्णांक davinci_config_channel_size(काष्ठा davinci_mcasp *mcasp,
				       पूर्णांक sample_width)
अणु
	u32 fmt;
	u32 tx_rotate, rx_rotate, slot_width;
	u32 mask = (1ULL << sample_width) - 1;

	अगर (mcasp->slot_width)
		slot_width = mcasp->slot_width;
	अन्यथा अगर (mcasp->max_क्रमmat_width)
		slot_width = mcasp->max_क्रमmat_width;
	अन्यथा
		slot_width = sample_width;
	/*
	 * TX rotation:
	 * right aligned क्रमmats: rotate w/ slot_width
	 * left aligned क्रमmats: rotate w/ sample_width
	 *
	 * RX rotation:
	 * right aligned क्रमmats: no rotation needed
	 * left aligned क्रमmats: rotate w/ (slot_width - sample_width)
	 */
	अगर ((mcasp->dai_fmt & SND_SOC_DAIFMT_FORMAT_MASK) ==
	    SND_SOC_DAIFMT_RIGHT_J) अणु
		tx_rotate = (slot_width / 4) & 0x7;
		rx_rotate = 0;
	पूर्ण अन्यथा अणु
		tx_rotate = (sample_width / 4) & 0x7;
		rx_rotate = (slot_width - sample_width) / 4;
	पूर्ण

	/* mapping of the XSSZ bit-field as described in the datasheet */
	fmt = (slot_width >> 1) - 1;

	अगर (mcasp->op_mode != DAVINCI_MCASP_DIT_MODE) अणु
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, RXSSZ(fmt),
			       RXSSZ(0x0F));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, TXSSZ(fmt),
			       TXSSZ(0x0F));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, TXROT(tx_rotate),
			       TXROT(7));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, RXROT(rx_rotate),
			       RXROT(7));
		mcasp_set_reg(mcasp, DAVINCI_MCASP_RXMASK_REG, mask);
	पूर्ण

	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXMASK_REG, mask);

	वापस 0;
पूर्ण

अटल पूर्णांक mcasp_common_hw_param(काष्ठा davinci_mcasp *mcasp, पूर्णांक stream,
				 पूर्णांक period_words, पूर्णांक channels)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data = &mcasp->dma_data[stream];
	पूर्णांक i;
	u8 tx_ser = 0;
	u8 rx_ser = 0;
	u8 slots = mcasp->tdm_slots;
	u8 max_active_serializers = (channels + slots - 1) / slots;
	u8 max_rx_serializers, max_tx_serializers;
	पूर्णांक active_serializers, numevt;
	u32 reg;
	/* Default configuration */
	अगर (mcasp->version < MCASP_VERSION_3)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PWREMUMGT_REG, MCASP_SOFT);

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, 0xFFFFFFFF);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_XEVTCTL_REG, TXDATADMADIS);
		max_tx_serializers = max_active_serializers;
		max_rx_serializers =
			mcasp->active_serializers[SNDRV_PCM_STREAM_CAPTURE];
	पूर्ण अन्यथा अणु
		mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, 0xFFFFFFFF);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_REVTCTL_REG, RXDATADMADIS);
		max_tx_serializers =
			mcasp->active_serializers[SNDRV_PCM_STREAM_PLAYBACK];
		max_rx_serializers = max_active_serializers;
	पूर्ण

	क्रम (i = 0; i < mcasp->num_serializer; i++) अणु
		mcasp_set_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
			       mcasp->serial_dir[i]);
		अगर (mcasp->serial_dir[i] == TX_MODE &&
					tx_ser < max_tx_serializers) अणु
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
				       mcasp->dismod, DISMOD_MASK);
			set_bit(PIN_BIT_AXR(i), &mcasp->pdir);
			tx_ser++;
		पूर्ण अन्यथा अगर (mcasp->serial_dir[i] == RX_MODE &&
					rx_ser < max_rx_serializers) अणु
			clear_bit(PIN_BIT_AXR(i), &mcasp->pdir);
			rx_ser++;
		पूर्ण अन्यथा अणु
			/* Inactive or unused pin, set it to inactive */
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
				       SRMOD_INACTIVE, SRMOD_MASK);
			/* If unused, set DISMOD क्रम the pin */
			अगर (mcasp->serial_dir[i] != INACTIVE_MODE)
				mcasp_mod_bits(mcasp,
					       DAVINCI_MCASP_XRSRCTL_REG(i),
					       mcasp->dismod, DISMOD_MASK);
			clear_bit(PIN_BIT_AXR(i), &mcasp->pdir);
		पूर्ण
	पूर्ण

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		active_serializers = tx_ser;
		numevt = mcasp->txnumevt;
		reg = mcasp->fअगरo_base + MCASP_WFIFOCTL_OFFSET;
	पूर्ण अन्यथा अणु
		active_serializers = rx_ser;
		numevt = mcasp->rxnumevt;
		reg = mcasp->fअगरo_base + MCASP_RFIFOCTL_OFFSET;
	पूर्ण

	अगर (active_serializers < max_active_serializers) अणु
		dev_warn(mcasp->dev, "stream has more channels (%d) than are "
			 "enabled in mcasp (%d)\n", channels,
			 active_serializers * slots);
		वापस -EINVAL;
	पूर्ण

	/* AFIFO is not in use */
	अगर (!numevt) अणु
		/* Configure the burst size क्रम platक्रमm drivers */
		अगर (active_serializers > 1) अणु
			/*
			 * If more than one serializers are in use we have one
			 * DMA request to provide data क्रम all serializers.
			 * For example अगर three serializers are enabled the DMA
			 * need to transfer three words per DMA request.
			 */
			dma_data->maxburst = active_serializers;
		पूर्ण अन्यथा अणु
			dma_data->maxburst = 0;
		पूर्ण

		जाओ out;
	पूर्ण

	अगर (period_words % active_serializers) अणु
		dev_err(mcasp->dev, "Invalid combination of period words and "
			"active serializers: %d, %d\n", period_words,
			active_serializers);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Calculate the optimal AFIFO depth क्रम platक्रमm side:
	 * The number of words क्रम numevt need to be in steps of active
	 * serializers.
	 */
	numevt = (numevt / active_serializers) * active_serializers;

	जबतक (period_words % numevt && numevt > 0)
		numevt -= active_serializers;
	अगर (numevt <= 0)
		numevt = active_serializers;

	mcasp_mod_bits(mcasp, reg, active_serializers, NUMDMA_MASK);
	mcasp_mod_bits(mcasp, reg, NUMEVT(numevt), NUMEVT_MASK);

	/* Configure the burst size क्रम platक्रमm drivers */
	अगर (numevt == 1)
		numevt = 0;
	dma_data->maxburst = numevt;

out:
	mcasp->active_serializers[stream] = active_serializers;

	वापस 0;
पूर्ण

अटल पूर्णांक mcasp_i2s_hw_param(काष्ठा davinci_mcasp *mcasp, पूर्णांक stream,
			      पूर्णांक channels)
अणु
	पूर्णांक i, active_slots;
	पूर्णांक total_slots;
	पूर्णांक active_serializers;
	u32 mask = 0;
	u32 busel = 0;

	total_slots = mcasp->tdm_slots;

	/*
	 * If more than one serializer is needed, then use them with
	 * all the specअगरied tdm_slots. Otherwise, one serializer can
	 * cope with the transaction using just as many slots as there
	 * are channels in the stream.
	 */
	अगर (mcasp->tdm_mask[stream]) अणु
		active_slots = hweight32(mcasp->tdm_mask[stream]);
		active_serializers = (channels + active_slots - 1) /
			active_slots;
		अगर (active_serializers == 1)
			active_slots = channels;
		क्रम (i = 0; i < total_slots; i++) अणु
			अगर ((1 << i) & mcasp->tdm_mask[stream]) अणु
				mask |= (1 << i);
				अगर (--active_slots <= 0)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		active_serializers = (channels + total_slots - 1) / total_slots;
		अगर (active_serializers == 1)
			active_slots = channels;
		अन्यथा
			active_slots = total_slots;

		क्रम (i = 0; i < active_slots; i++)
			mask |= (1 << i);
	पूर्ण

	mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, TX_ASYNC);

	अगर (!mcasp->dat_port)
		busel = TXSEL;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		mcasp_set_reg(mcasp, DAVINCI_MCASP_TXTDM_REG, mask);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, busel | TXORD);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG,
			       FSXMOD(total_slots), FSXMOD(0x1FF));
	पूर्ण अन्यथा अगर (stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		mcasp_set_reg(mcasp, DAVINCI_MCASP_RXTDM_REG, mask);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, busel | RXORD);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG,
			       FSRMOD(total_slots), FSRMOD(0x1FF));
		/*
		 * If McASP is set to be TX/RX synchronous and the playback is
		 * not running alपढ़ोy we need to configure the TX slots in
		 * order to have correct FSX on the bus
		 */
		अगर (mcasp_is_synchronous(mcasp) && !mcasp->channels)
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG,
				       FSXMOD(total_slots), FSXMOD(0x1FF));
	पूर्ण

	वापस 0;
पूर्ण

/* S/PDIF */
अटल पूर्णांक mcasp_dit_hw_param(काष्ठा davinci_mcasp *mcasp,
			      अचिन्हित पूर्णांक rate)
अणु
	u32 cs_value = 0;
	u8 *cs_bytes = (u8*) &cs_value;

	/* Set the TX क्रमmat : 24 bit right rotation, 32 bit slot, Pad 0
	   and LSB first */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, TXROT(6) | TXSSZ(15));

	/* Set TX frame synch : DIT Mode, 1 bit width, पूर्णांकernal, rising edge */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE | FSXMOD(0x180));

	/* Set the TX tdm : क्रम all the slots */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXTDM_REG, 0xFFFFFFFF);

	/* Set the TX घड़ी controls : भाग = 1 and पूर्णांकernal */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE | TX_ASYNC);

	mcasp_clr_bits(mcasp, DAVINCI_MCASP_XEVTCTL_REG, TXDATADMADIS);

	/* Only 44100 and 48000 are valid, both have the same setting */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG, AHCLKXDIV(3));

	/* Enable the DIT */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_TXDITCTL_REG, DITEN);

	/* Set S/PDIF channel status bits */
	cs_bytes[0] = IEC958_AES0_CON_NOT_COPYRIGHT;
	cs_bytes[1] = IEC958_AES1_CON_PCM_CODER;

	चयन (rate) अणु
	हाल 22050:
		cs_bytes[3] |= IEC958_AES3_CON_FS_22050;
		अवरोध;
	हाल 24000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_24000;
		अवरोध;
	हाल 32000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_32000;
		अवरोध;
	हाल 44100:
		cs_bytes[3] |= IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 48000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 88200:
		cs_bytes[3] |= IEC958_AES3_CON_FS_88200;
		अवरोध;
	हाल 96000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 176400:
		cs_bytes[3] |= IEC958_AES3_CON_FS_176400;
		अवरोध;
	हाल 192000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_192000;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "unsupported sampling rate: %d\n", rate);
		वापस -EINVAL;
	पूर्ण

	mcasp_set_reg(mcasp, DAVINCI_MCASP_DITCSRA_REG, cs_value);
	mcasp_set_reg(mcasp, DAVINCI_MCASP_DITCSRB_REG, cs_value);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mcasp_calc_clk_भाग(काष्ठा davinci_mcasp *mcasp,
				      अचिन्हित पूर्णांक sysclk_freq,
				      अचिन्हित पूर्णांक bclk_freq, bool set)
अणु
	u32 reg = mcasp_get_reg(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG);
	पूर्णांक भाग = sysclk_freq / bclk_freq;
	पूर्णांक rem = sysclk_freq % bclk_freq;
	पूर्णांक error_ppm;
	पूर्णांक aux_भाग = 1;

	अगर (भाग > (ACLKXDIV_MASK + 1)) अणु
		अगर (reg & AHCLKXE) अणु
			aux_भाग = भाग / (ACLKXDIV_MASK + 1);
			अगर (भाग % (ACLKXDIV_MASK + 1))
				aux_भाग++;

			sysclk_freq /= aux_भाग;
			भाग = sysclk_freq / bclk_freq;
			rem = sysclk_freq % bclk_freq;
		पूर्ण अन्यथा अगर (set) अणु
			dev_warn(mcasp->dev, "Too fast reference clock (%u)\n",
				 sysclk_freq);
		पूर्ण
	पूर्ण

	अगर (rem != 0) अणु
		अगर (भाग == 0 ||
		    ((sysclk_freq / भाग) - bclk_freq) >
		    (bclk_freq - (sysclk_freq / (भाग+1)))) अणु
			भाग++;
			rem = rem - bclk_freq;
		पूर्ण
	पूर्ण
	error_ppm = (भाग*1000000 + (पूर्णांक)भाग64_दीर्घ(1000000LL*rem,
		     (पूर्णांक)bclk_freq)) / भाग - 1000000;

	अगर (set) अणु
		अगर (error_ppm)
			dev_info(mcasp->dev, "Sample-rate is off by %d PPM\n",
				 error_ppm);

		__davinci_mcasp_set_clkभाग(mcasp, MCASP_CLKDIV_BCLK, भाग, 0);
		अगर (reg & AHCLKXE)
			__davinci_mcasp_set_clkभाग(mcasp, MCASP_CLKDIV_AUXCLK,
						   aux_भाग, 0);
	पूर्ण

	वापस error_ppm;
पूर्ण

अटल अंतरभूत u32 davinci_mcasp_tx_delay(काष्ठा davinci_mcasp *mcasp)
अणु
	अगर (!mcasp->txnumevt)
		वापस 0;

	वापस mcasp_get_reg(mcasp, mcasp->fअगरo_base + MCASP_WFIFOSTS_OFFSET);
पूर्ण

अटल अंतरभूत u32 davinci_mcasp_rx_delay(काष्ठा davinci_mcasp *mcasp)
अणु
	अगर (!mcasp->rxnumevt)
		वापस 0;

	वापस mcasp_get_reg(mcasp, mcasp->fअगरo_base + MCASP_RFIFOSTS_OFFSET);
पूर्ण

अटल snd_pcm_sframes_t davinci_mcasp_delay(
			काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);
	u32 fअगरo_use;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		fअगरo_use = davinci_mcasp_tx_delay(mcasp);
	अन्यथा
		fअगरo_use = davinci_mcasp_rx_delay(mcasp);

	/*
	 * Divide the used locations with the channel count to get the
	 * FIFO usage in samples (करोn't care about partial samples in the
	 * buffer).
	 */
	वापस fअगरo_use / substream->runसमय->channels;
पूर्ण

अटल पूर्णांक davinci_mcasp_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params,
					काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक word_length;
	पूर्णांक channels = params_channels(params);
	पूर्णांक period_size = params_period_size(params);
	पूर्णांक ret;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_U8:
	हाल SNDRV_PCM_FORMAT_S8:
		word_length = 8;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_U16_LE:
	हाल SNDRV_PCM_FORMAT_S16_LE:
		word_length = 16;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_U24_3LE:
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		word_length = 24;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_U24_LE:
	हाल SNDRV_PCM_FORMAT_S24_LE:
		word_length = 24;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_U32_LE:
	हाल SNDRV_PCM_FORMAT_S32_LE:
		word_length = 32;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "davinci-mcasp: unsupported PCM format");
		वापस -EINVAL;
	पूर्ण

	ret = davinci_mcasp_set_dai_fmt(cpu_dai, mcasp->dai_fmt);
	अगर (ret)
		वापस ret;

	/*
	 * If mcasp is BCLK master, and a BCLK भागider was not provided by
	 * the machine driver, we need to calculate the ratio.
	 */
	अगर (mcasp->bclk_master && mcasp->bclk_भाग == 0 && mcasp->sysclk_freq) अणु
		पूर्णांक slots = mcasp->tdm_slots;
		पूर्णांक rate = params_rate(params);
		पूर्णांक sbits = params_width(params);

		अगर (mcasp->slot_width)
			sbits = mcasp->slot_width;

		davinci_mcasp_calc_clk_भाग(mcasp, mcasp->sysclk_freq,
					   rate * sbits * slots, true);
	पूर्ण

	ret = mcasp_common_hw_param(mcasp, substream->stream,
				    period_size * channels, channels);
	अगर (ret)
		वापस ret;

	अगर (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		ret = mcasp_dit_hw_param(mcasp, params_rate(params));
	अन्यथा
		ret = mcasp_i2s_hw_param(mcasp, substream->stream,
					 channels);

	अगर (ret)
		वापस ret;

	davinci_config_channel_size(mcasp, word_length);

	अगर (mcasp->op_mode == DAVINCI_MCASP_IIS_MODE) अणु
		mcasp->channels = channels;
		अगर (!mcasp->max_क्रमmat_width)
			mcasp->max_क्रमmat_width = word_length;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mcasp_trigger(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक cmd, काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		davinci_mcasp_start(mcasp, substream->stream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		davinci_mcasp_stop(mcasp, substream->stream);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक davinci_mcasp_hw_rule_slot_width(काष्ठा snd_pcm_hw_params *params,
					    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा davinci_mcasp_ruledata *rd = rule->निजी;
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_mask nfmt;
	पूर्णांक i, slot_width;

	snd_mask_none(&nfmt);
	slot_width = rd->mcasp->slot_width;

	क्रम (i = 0; i <= SNDRV_PCM_FORMAT_LAST; i++) अणु
		अगर (snd_mask_test(fmt, i)) अणु
			अगर (snd_pcm_क्रमmat_width(i) <= slot_width) अणु
				snd_mask_set(&nfmt, i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस snd_mask_refine(fmt, &nfmt);
पूर्ण

अटल पूर्णांक davinci_mcasp_hw_rule_क्रमmat_width(काष्ठा snd_pcm_hw_params *params,
					      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा davinci_mcasp_ruledata *rd = rule->निजी;
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_mask nfmt;
	पूर्णांक i, क्रमmat_width;

	snd_mask_none(&nfmt);
	क्रमmat_width = rd->mcasp->max_क्रमmat_width;

	क्रम (i = 0; i <= SNDRV_PCM_FORMAT_LAST; i++) अणु
		अगर (snd_mask_test(fmt, i)) अणु
			अगर (snd_pcm_क्रमmat_width(i) == क्रमmat_width) अणु
				snd_mask_set(&nfmt, i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस snd_mask_refine(fmt, &nfmt);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक davinci_mcasp_dai_rates[] = अणु
	8000, 11025, 16000, 22050, 32000, 44100, 48000, 64000,
	88200, 96000, 176400, 192000,
पूर्ण;

#घोषणा DAVINCI_MAX_RATE_ERROR_PPM 1000

अटल पूर्णांक davinci_mcasp_hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा davinci_mcasp_ruledata *rd = rule->निजी;
	काष्ठा snd_पूर्णांकerval *ri =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	पूर्णांक sbits = params_width(params);
	पूर्णांक slots = rd->mcasp->tdm_slots;
	काष्ठा snd_पूर्णांकerval range;
	पूर्णांक i;

	अगर (rd->mcasp->slot_width)
		sbits = rd->mcasp->slot_width;

	snd_पूर्णांकerval_any(&range);
	range.empty = 1;

	क्रम (i = 0; i < ARRAY_SIZE(davinci_mcasp_dai_rates); i++) अणु
		अगर (snd_पूर्णांकerval_test(ri, davinci_mcasp_dai_rates[i])) अणु
			uपूर्णांक bclk_freq = sbits * slots *
					 davinci_mcasp_dai_rates[i];
			अचिन्हित पूर्णांक sysclk_freq;
			पूर्णांक ppm;

			अगर (rd->mcasp->auxclk_fs_ratio)
				sysclk_freq =  davinci_mcasp_dai_rates[i] *
					       rd->mcasp->auxclk_fs_ratio;
			अन्यथा
				sysclk_freq = rd->mcasp->sysclk_freq;

			ppm = davinci_mcasp_calc_clk_भाग(rd->mcasp, sysclk_freq,
							 bclk_freq, false);
			अगर (असल(ppm) < DAVINCI_MAX_RATE_ERROR_PPM) अणु
				अगर (range.empty) अणु
					range.min = davinci_mcasp_dai_rates[i];
					range.empty = 0;
				पूर्ण
				range.max = davinci_mcasp_dai_rates[i];
			पूर्ण
		पूर्ण
	पूर्ण

	dev_dbg(rd->mcasp->dev,
		"Frequencies %d-%d -> %d-%d for %d sbits and %d tdm slots\n",
		ri->min, ri->max, range.min, range.max, sbits, slots);

	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var),
				   &range);
पूर्ण

अटल पूर्णांक davinci_mcasp_hw_rule_क्रमmat(काष्ठा snd_pcm_hw_params *params,
					काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा davinci_mcasp_ruledata *rd = rule->निजी;
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_mask nfmt;
	पूर्णांक rate = params_rate(params);
	पूर्णांक slots = rd->mcasp->tdm_slots;
	पूर्णांक i, count = 0;

	snd_mask_none(&nfmt);

	क्रम (i = 0; i <= SNDRV_PCM_FORMAT_LAST; i++) अणु
		अगर (snd_mask_test(fmt, i)) अणु
			uपूर्णांक sbits = snd_pcm_क्रमmat_width(i);
			अचिन्हित पूर्णांक sysclk_freq;
			पूर्णांक ppm;

			अगर (rd->mcasp->auxclk_fs_ratio)
				sysclk_freq =  rate *
					       rd->mcasp->auxclk_fs_ratio;
			अन्यथा
				sysclk_freq = rd->mcasp->sysclk_freq;

			अगर (rd->mcasp->slot_width)
				sbits = rd->mcasp->slot_width;

			ppm = davinci_mcasp_calc_clk_भाग(rd->mcasp, sysclk_freq,
							 sbits * slots * rate,
							 false);
			अगर (असल(ppm) < DAVINCI_MAX_RATE_ERROR_PPM) अणु
				snd_mask_set(&nfmt, i);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण
	dev_dbg(rd->mcasp->dev,
		"%d possible sample format for %d Hz and %d tdm slots\n",
		count, rate, slots);

	वापस snd_mask_refine(fmt, &nfmt);
पूर्ण

अटल पूर्णांक davinci_mcasp_hw_rule_min_periodsize(
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *period_size = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
	काष्ठा snd_पूर्णांकerval frames;

	snd_पूर्णांकerval_any(&frames);
	frames.min = 64;
	frames.पूर्णांकeger = 1;

	वापस snd_पूर्णांकerval_refine(period_size, &frames);
पूर्ण

अटल पूर्णांक davinci_mcasp_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा davinci_mcasp_ruledata *ruledata =
					&mcasp->ruledata[substream->stream];
	u32 max_channels = 0;
	पूर्णांक i, dir, ret;
	पूर्णांक tdm_slots = mcasp->tdm_slots;

	/* Do not allow more then one stream per direction */
	अगर (mcasp->substreams[substream->stream])
		वापस -EBUSY;

	mcasp->substreams[substream->stream] = substream;

	अगर (mcasp->tdm_mask[substream->stream])
		tdm_slots = hweight32(mcasp->tdm_mask[substream->stream]);

	अगर (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		वापस 0;

	/*
	 * Limit the maximum allowed channels क्रम the first stream:
	 * number of serializers क्रम the direction * tdm slots per serializer
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = TX_MODE;
	अन्यथा
		dir = RX_MODE;

	क्रम (i = 0; i < mcasp->num_serializer; i++) अणु
		अगर (mcasp->serial_dir[i] == dir)
			max_channels++;
	पूर्ण
	ruledata->serializers = max_channels;
	ruledata->mcasp = mcasp;
	max_channels *= tdm_slots;
	/*
	 * If the alपढ़ोy active stream has less channels than the calculated
	 * limit based on the seirializers * tdm_slots, and only one serializer
	 * is in use we need to use that as a स्थिरraपूर्णांक क्रम the second stream.
	 * Otherwise (first stream or less allowed channels or more than one
	 * serializer in use) we use the calculated स्थिरraपूर्णांक.
	 */
	अगर (mcasp->channels && mcasp->channels < max_channels &&
	    ruledata->serializers == 1)
		max_channels = mcasp->channels;
	/*
	 * But we can always allow channels upto the amount of
	 * the available tdm_slots.
	 */
	अगर (max_channels < tdm_slots)
		max_channels = tdm_slots;

	snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
				     SNDRV_PCM_HW_PARAM_CHANNELS,
				     0, max_channels);

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय,
				   0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &mcasp->chस्थिरr[substream->stream]);

	अगर (mcasp->max_क्रमmat_width) अणु
		/*
		 * Only allow क्रमmats which require same amount of bits on the
		 * bus as the currently running stream
		 */
		ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_FORMAT,
					  davinci_mcasp_hw_rule_क्रमmat_width,
					  ruledata,
					  SNDRV_PCM_HW_PARAM_FORMAT, -1);
		अगर (ret)
			वापस ret;
	पूर्ण
	अन्यथा अगर (mcasp->slot_width) अणु
		/* Only allow क्रमmats require <= slot_width bits on the bus */
		ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_FORMAT,
					  davinci_mcasp_hw_rule_slot_width,
					  ruledata,
					  SNDRV_PCM_HW_PARAM_FORMAT, -1);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * If we rely on implicit BCLK भागider setting we should
	 * set स्थिरraपूर्णांकs based on what we can provide.
	 */
	अगर (mcasp->bclk_master && mcasp->bclk_भाग == 0 && mcasp->sysclk_freq) अणु
		ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  davinci_mcasp_hw_rule_rate,
					  ruledata,
					  SNDRV_PCM_HW_PARAM_FORMAT, -1);
		अगर (ret)
			वापस ret;
		ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_FORMAT,
					  davinci_mcasp_hw_rule_क्रमmat,
					  ruledata,
					  SNDRV_PCM_HW_PARAM_RATE, -1);
		अगर (ret)
			वापस ret;
	पूर्ण

	snd_pcm_hw_rule_add(substream->runसमय, 0,
			    SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
			    davinci_mcasp_hw_rule_min_periodsize, शून्य,
			    SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);

	वापस 0;
पूर्ण

अटल व्योम davinci_mcasp_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);

	mcasp->substreams[substream->stream] = शून्य;
	mcasp->active_serializers[substream->stream] = 0;

	अगर (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		वापस;

	अगर (!snd_soc_dai_active(cpu_dai)) अणु
		mcasp->channels = 0;
		mcasp->max_क्रमmat_width = 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops davinci_mcasp_dai_ops = अणु
	.startup	= davinci_mcasp_startup,
	.shutकरोwn	= davinci_mcasp_shutकरोwn,
	.trigger	= davinci_mcasp_trigger,
	.delay		= davinci_mcasp_delay,
	.hw_params	= davinci_mcasp_hw_params,
	.set_fmt	= davinci_mcasp_set_dai_fmt,
	.set_clkभाग	= davinci_mcasp_set_clkभाग,
	.set_sysclk	= davinci_mcasp_set_sysclk,
	.set_tdm_slot	= davinci_mcasp_set_tdm_slot,
पूर्ण;

अटल पूर्णांक davinci_mcasp_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(dai);

	dai->playback_dma_data = &mcasp->dma_data[SNDRV_PCM_STREAM_PLAYBACK];
	dai->capture_dma_data = &mcasp->dma_data[SNDRV_PCM_STREAM_CAPTURE];

	वापस 0;
पूर्ण

#घोषणा DAVINCI_MCASP_RATES	SNDRV_PCM_RATE_8000_192000

#घोषणा DAVINCI_MCASP_PCM_FMTS (SNDRV_PCM_FMTBIT_S8 | \
				SNDRV_PCM_FMTBIT_U8 | \
				SNDRV_PCM_FMTBIT_S16_LE | \
				SNDRV_PCM_FMTBIT_U16_LE | \
				SNDRV_PCM_FMTBIT_S24_LE | \
				SNDRV_PCM_FMTBIT_U24_LE | \
				SNDRV_PCM_FMTBIT_S24_3LE | \
				SNDRV_PCM_FMTBIT_U24_3LE | \
				SNDRV_PCM_FMTBIT_S32_LE | \
				SNDRV_PCM_FMTBIT_U32_LE)

अटल काष्ठा snd_soc_dai_driver davinci_mcasp_dai[] = अणु
	अणु
		.name		= "davinci-mcasp.0",
		.probe		= davinci_mcasp_dai_probe,
		.playback	= अणु
			.stream_name = "IIS Playback",
			.channels_min	= 1,
			.channels_max	= 32 * 16,
			.rates 		= DAVINCI_MCASP_RATES,
			.क्रमmats	= DAVINCI_MCASP_PCM_FMTS,
		पूर्ण,
		.capture 	= अणु
			.stream_name = "IIS Capture",
			.channels_min 	= 1,
			.channels_max	= 32 * 16,
			.rates 		= DAVINCI_MCASP_RATES,
			.क्रमmats	= DAVINCI_MCASP_PCM_FMTS,
		पूर्ण,
		.ops 		= &davinci_mcasp_dai_ops,

		.symmetric_rate		= 1,
	पूर्ण,
	अणु
		.name		= "davinci-mcasp.1",
		.probe		= davinci_mcasp_dai_probe,
		.playback 	= अणु
			.stream_name = "DIT Playback",
			.channels_min	= 1,
			.channels_max	= 384,
			.rates		= DAVINCI_MCASP_RATES,
			.क्रमmats	= DAVINCI_MCASP_PCM_FMTS,
		पूर्ण,
		.ops 		= &davinci_mcasp_dai_ops,
	पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver davinci_mcasp_component = अणु
	.name		= "davinci-mcasp",
पूर्ण;

/* Some HW specअगरic values and शेषs. The rest is filled in from DT. */
अटल काष्ठा davinci_mcasp_pdata dm646x_mcasp_pdata = अणु
	.tx_dma_offset = 0x400,
	.rx_dma_offset = 0x400,
	.version = MCASP_VERSION_1,
पूर्ण;

अटल काष्ठा davinci_mcasp_pdata da830_mcasp_pdata = अणु
	.tx_dma_offset = 0x2000,
	.rx_dma_offset = 0x2000,
	.version = MCASP_VERSION_2,
पूर्ण;

अटल काष्ठा davinci_mcasp_pdata am33xx_mcasp_pdata = अणु
	.tx_dma_offset = 0,
	.rx_dma_offset = 0,
	.version = MCASP_VERSION_3,
पूर्ण;

अटल काष्ठा davinci_mcasp_pdata dra7_mcasp_pdata = अणु
	/* The CFG port offset will be calculated अगर it is needed */
	.tx_dma_offset = 0,
	.rx_dma_offset = 0,
	.version = MCASP_VERSION_4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mcasp_dt_ids[] = अणु
	अणु
		.compatible = "ti,dm646x-mcasp-audio",
		.data = &dm646x_mcasp_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,da830-mcasp-audio",
		.data = &da830_mcasp_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,am33xx-mcasp-audio",
		.data = &am33xx_mcasp_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,dra7-mcasp-audio",
		.data = &dra7_mcasp_pdata,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcasp_dt_ids);

अटल पूर्णांक mcasp_reparent_fck(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा clk *gfclk, *parent_clk;
	स्थिर अक्षर *parent_name;
	पूर्णांक ret;

	अगर (!node)
		वापस 0;

	parent_name = of_get_property(node, "fck_parent", शून्य);
	अगर (!parent_name)
		वापस 0;

	dev_warn(&pdev->dev, "Update the bindings to use assigned-clocks!\n");

	gfclk = clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(gfclk)) अणु
		dev_err(&pdev->dev, "failed to get fck\n");
		वापस PTR_ERR(gfclk);
	पूर्ण

	parent_clk = clk_get(शून्य, parent_name);
	अगर (IS_ERR(parent_clk)) अणु
		dev_err(&pdev->dev, "failed to get parent clock\n");
		ret = PTR_ERR(parent_clk);
		जाओ err1;
	पूर्ण

	ret = clk_set_parent(gfclk, parent_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to reparent fck\n");
		जाओ err2;
	पूर्ण

err2:
	clk_put(parent_clk);
err1:
	clk_put(gfclk);
	वापस ret;
पूर्ण

अटल bool davinci_mcasp_have_gpiochip(काष्ठा davinci_mcasp *mcasp)
अणु
#अगर_घोषित CONFIG_OF_GPIO
	अगर (mcasp->dev->of_node &&
	    of_property_पढ़ो_bool(mcasp->dev->of_node, "gpio-controller"))
		वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

अटल पूर्णांक davinci_mcasp_get_config(काष्ठा davinci_mcasp *mcasp,
				    काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match = of_match_device(mcasp_dt_ids, &pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा davinci_mcasp_pdata *pdata = शून्य;
	स्थिर u32 *of_serial_dir32;
	u32 val;
	पूर्णांक i;

	अगर (pdev->dev.platक्रमm_data) अणु
		pdata = pdev->dev.platक्रमm_data;
		pdata->dismod = DISMOD_LOW;
		जाओ out;
	पूर्ण अन्यथा अगर (match) अणु
		pdata = devm_kmemdup(&pdev->dev, match->data, माप(*pdata),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "No compatible match found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "op-mode", &val) == 0) अणु
		pdata->op_mode = val;
	पूर्ण अन्यथा अणु
		mcasp->missing_audio_param = true;
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "tdm-slots", &val) == 0) अणु
		अगर (val < 2 || val > 32) अणु
			dev_err(&pdev->dev, "tdm-slots must be in rage [2-32]\n");
			वापस -EINVAL;
		पूर्ण

		pdata->tdm_slots = val;
	पूर्ण अन्यथा अगर (pdata->op_mode == DAVINCI_MCASP_IIS_MODE) अणु
		mcasp->missing_audio_param = true;
		जाओ out;
	पूर्ण

	of_serial_dir32 = of_get_property(np, "serial-dir", &val);
	val /= माप(u32);
	अगर (of_serial_dir32) अणु
		u8 *of_serial_dir = devm_kzalloc(&pdev->dev,
						 (माप(*of_serial_dir) * val),
						 GFP_KERNEL);
		अगर (!of_serial_dir)
			वापस -ENOMEM;

		क्रम (i = 0; i < val; i++)
			of_serial_dir[i] = be32_to_cpup(&of_serial_dir32[i]);

		pdata->num_serializer = val;
		pdata->serial_dir = of_serial_dir;
	पूर्ण अन्यथा अणु
		mcasp->missing_audio_param = true;
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "tx-num-evt", &val) == 0)
		pdata->txnumevt = val;

	अगर (of_property_पढ़ो_u32(np, "rx-num-evt", &val) == 0)
		pdata->rxnumevt = val;

	अगर (of_property_पढ़ो_u32(np, "auxclk-fs-ratio", &val) == 0)
		mcasp->auxclk_fs_ratio = val;

	अगर (of_property_पढ़ो_u32(np, "dismod", &val) == 0) अणु
		अगर (val == 0 || val == 2 || val == 3) अणु
			pdata->dismod = DISMOD_VAL(val);
		पूर्ण अन्यथा अणु
			dev_warn(&pdev->dev, "Invalid dismod value: %u\n", val);
			pdata->dismod = DISMOD_LOW;
		पूर्ण
	पूर्ण अन्यथा अणु
		pdata->dismod = DISMOD_LOW;
	पूर्ण

out:
	mcasp->pdata = pdata;

	अगर (mcasp->missing_audio_param) अणु
		अगर (davinci_mcasp_have_gpiochip(mcasp)) अणु
			dev_dbg(&pdev->dev, "Missing DT parameter(s) for audio\n");
			वापस 0;
		पूर्ण

		dev_err(&pdev->dev, "Insufficient DT parameter(s)\n");
		वापस -ENODEV;
	पूर्ण

	mcasp->op_mode = pdata->op_mode;
	/* sanity check क्रम tdm slots parameter */
	अगर (mcasp->op_mode == DAVINCI_MCASP_IIS_MODE) अणु
		अगर (pdata->tdm_slots < 2) अणु
			dev_warn(&pdev->dev, "invalid tdm slots: %d\n",
				 pdata->tdm_slots);
			mcasp->tdm_slots = 2;
		पूर्ण अन्यथा अगर (pdata->tdm_slots > 32) अणु
			dev_warn(&pdev->dev, "invalid tdm slots: %d\n",
				 pdata->tdm_slots);
			mcasp->tdm_slots = 32;
		पूर्ण अन्यथा अणु
			mcasp->tdm_slots = pdata->tdm_slots;
		पूर्ण
	पूर्ण

	mcasp->num_serializer = pdata->num_serializer;
#अगर_घोषित CONFIG_PM
	mcasp->context.xrsr_regs = devm_kसुस्मृति(&pdev->dev,
						mcasp->num_serializer, माप(u32),
						GFP_KERNEL);
	अगर (!mcasp->context.xrsr_regs)
		वापस -ENOMEM;
#पूर्ण_अगर
	mcasp->serial_dir = pdata->serial_dir;
	mcasp->version = pdata->version;
	mcasp->txnumevt = pdata->txnumevt;
	mcasp->rxnumevt = pdata->rxnumevt;
	mcasp->dismod = pdata->dismod;

	वापस 0;
पूर्ण

क्रमागत अणु
	PCM_EDMA,
	PCM_SDMA,
	PCM_UDMA,
पूर्ण;
अटल स्थिर अक्षर *sdma_prefix = "ti,omap";

अटल पूर्णांक davinci_mcasp_get_dma_type(काष्ठा davinci_mcasp *mcasp)
अणु
	काष्ठा dma_chan *chan;
	स्थिर अक्षर *पंचांगp;
	पूर्णांक ret = PCM_EDMA;

	अगर (!mcasp->dev->of_node)
		वापस PCM_EDMA;

	पंचांगp = mcasp->dma_data[SNDRV_PCM_STREAM_PLAYBACK].filter_data;
	chan = dma_request_chan(mcasp->dev, पंचांगp);
	अगर (IS_ERR(chan)) अणु
		अगर (PTR_ERR(chan) != -EPROBE_DEFER)
			dev_err(mcasp->dev,
				"Can't verify DMA configuration (%ld)\n",
				PTR_ERR(chan));
		वापस PTR_ERR(chan);
	पूर्ण
	अगर (WARN_ON(!chan->device || !chan->device->dev)) अणु
		dma_release_channel(chan);
		वापस -EINVAL;
	पूर्ण

	अगर (chan->device->dev->of_node)
		ret = of_property_पढ़ो_string(chan->device->dev->of_node,
					      "compatible", &पंचांगp);
	अन्यथा
		dev_dbg(mcasp->dev, "DMA controller has no of-node\n");

	dma_release_channel(chan);
	अगर (ret)
		वापस ret;

	dev_dbg(mcasp->dev, "DMA controller compatible = \"%s\"\n", पंचांगp);
	अगर (!म_भेदन(पंचांगp, sdma_prefix, म_माप(sdma_prefix)))
		वापस PCM_SDMA;
	अन्यथा अगर (म_माला(पंचांगp, "udmap"))
		वापस PCM_UDMA;

	वापस PCM_EDMA;
पूर्ण

अटल u32 davinci_mcasp_txdma_offset(काष्ठा davinci_mcasp_pdata *pdata)
अणु
	पूर्णांक i;
	u32 offset = 0;

	अगर (pdata->version != MCASP_VERSION_4)
		वापस pdata->tx_dma_offset;

	क्रम (i = 0; i < pdata->num_serializer; i++) अणु
		अगर (pdata->serial_dir[i] == TX_MODE) अणु
			अगर (!offset) अणु
				offset = DAVINCI_MCASP_TXBUF_REG(i);
			पूर्ण अन्यथा अणु
				pr_err("%s: Only one serializer allowed!\n",
				       __func__);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

अटल u32 davinci_mcasp_rxdma_offset(काष्ठा davinci_mcasp_pdata *pdata)
अणु
	पूर्णांक i;
	u32 offset = 0;

	अगर (pdata->version != MCASP_VERSION_4)
		वापस pdata->rx_dma_offset;

	क्रम (i = 0; i < pdata->num_serializer; i++) अणु
		अगर (pdata->serial_dir[i] == RX_MODE) अणु
			अगर (!offset) अणु
				offset = DAVINCI_MCASP_RXBUF_REG(i);
			पूर्ण अन्यथा अणु
				pr_err("%s: Only one serializer allowed!\n",
				       __func__);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक davinci_mcasp_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा davinci_mcasp *mcasp = gpiochip_get_data(chip);

	अगर (mcasp->num_serializer && offset < mcasp->num_serializer &&
	    mcasp->serial_dir[offset] != INACTIVE_MODE) अणु
		dev_err(mcasp->dev, "AXR%u pin is  used for audio\n", offset);
		वापस -EBUSY;
	पूर्ण

	/* Do not change the PIN yet */

	वापस pm_runसमय_get_sync(mcasp->dev);
पूर्ण

अटल व्योम davinci_mcasp_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा davinci_mcasp *mcasp = gpiochip_get_data(chip);

	/* Set the direction to input */
	mcasp_clr_bits(mcasp, DAVINCI_MCASP_Pसूची_REG, BIT(offset));

	/* Set the pin as McASP pin */
	mcasp_clr_bits(mcasp, DAVINCI_MCASP_PFUNC_REG, BIT(offset));

	pm_runसमय_put_sync(mcasp->dev);
पूर्ण

अटल पूर्णांक davinci_mcasp_gpio_direction_out(काष्ठा gpio_chip *chip,
					    अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 val;

	अगर (value)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PDOUT_REG, BIT(offset));
	अन्यथा
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_PDOUT_REG, BIT(offset));

	val = mcasp_get_reg(mcasp, DAVINCI_MCASP_PFUNC_REG);
	अगर (!(val & BIT(offset))) अणु
		/* Set the pin as GPIO pin */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PFUNC_REG, BIT(offset));

		/* Set the direction to output */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_Pसूची_REG, BIT(offset));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम davinci_mcasp_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset,
				  पूर्णांक value)
अणु
	काष्ठा davinci_mcasp *mcasp = gpiochip_get_data(chip);

	अगर (value)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PDOUT_REG, BIT(offset));
	अन्यथा
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_PDOUT_REG, BIT(offset));
पूर्ण

अटल पूर्णांक davinci_mcasp_gpio_direction_in(काष्ठा gpio_chip *chip,
					   अचिन्हित offset)
अणु
	काष्ठा davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 val;

	val = mcasp_get_reg(mcasp, DAVINCI_MCASP_PFUNC_REG);
	अगर (!(val & BIT(offset))) अणु
		/* Set the direction to input */
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_Pसूची_REG, BIT(offset));

		/* Set the pin as GPIO pin */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PFUNC_REG, BIT(offset));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mcasp_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 val;

	val = mcasp_get_reg(mcasp, DAVINCI_MCASP_PDSET_REG);
	अगर (val & BIT(offset))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mcasp_gpio_get_direction(काष्ठा gpio_chip *chip,
					    अचिन्हित offset)
अणु
	काष्ठा davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 val;

	val = mcasp_get_reg(mcasp, DAVINCI_MCASP_Pसूची_REG);
	अगर (val & BIT(offset))
		वापस 0;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा gpio_chip davinci_mcasp_ढाँचा_chip = अणु
	.owner			= THIS_MODULE,
	.request		= davinci_mcasp_gpio_request,
	.मुक्त			= davinci_mcasp_gpio_मुक्त,
	.direction_output	= davinci_mcasp_gpio_direction_out,
	.set			= davinci_mcasp_gpio_set,
	.direction_input	= davinci_mcasp_gpio_direction_in,
	.get			= davinci_mcasp_gpio_get,
	.get_direction		= davinci_mcasp_gpio_get_direction,
	.base			= -1,
	.ngpio			= 32,
पूर्ण;

अटल पूर्णांक davinci_mcasp_init_gpiochip(काष्ठा davinci_mcasp *mcasp)
अणु
	अगर (!davinci_mcasp_have_gpiochip(mcasp))
		वापस 0;

	mcasp->gpio_chip = davinci_mcasp_ढाँचा_chip;
	mcasp->gpio_chip.label = dev_name(mcasp->dev);
	mcasp->gpio_chip.parent = mcasp->dev;
#अगर_घोषित CONFIG_OF_GPIO
	mcasp->gpio_chip.of_node = mcasp->dev->of_node;
#पूर्ण_अगर

	वापस devm_gpiochip_add_data(mcasp->dev, &mcasp->gpio_chip, mcasp);
पूर्ण

#अन्यथा /* CONFIG_GPIOLIB */
अटल अंतरभूत पूर्णांक davinci_mcasp_init_gpiochip(काष्ठा davinci_mcasp *mcasp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_GPIOLIB */

अटल पूर्णांक davinci_mcasp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	काष्ठा resource *mem, *dat;
	काष्ठा davinci_mcasp *mcasp;
	अक्षर *irq_name;
	पूर्णांक irq;
	पूर्णांक ret;

	अगर (!pdev->dev.platक्रमm_data && !pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "No platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	mcasp = devm_kzalloc(&pdev->dev, माप(काष्ठा davinci_mcasp),
			   GFP_KERNEL);
	अगर (!mcasp)
		वापस	-ENOMEM;

	mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mpu");
	अगर (!mem) अणु
		dev_warn(&pdev->dev,
			 "\"mpu\" mem resource not found, using index 0\n");
		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (!mem) अणु
			dev_err(&pdev->dev, "no mem resource?\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	mcasp->base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(mcasp->base))
		वापस PTR_ERR(mcasp->base);

	dev_set_drvdata(&pdev->dev, mcasp);
	pm_runसमय_enable(&pdev->dev);

	mcasp->dev = &pdev->dev;
	ret = davinci_mcasp_get_config(mcasp, pdev);
	अगर (ret)
		जाओ err;

	/* All PINS as McASP */
	pm_runसमय_get_sync(mcasp->dev);
	mcasp_set_reg(mcasp, DAVINCI_MCASP_PFUNC_REG, 0x00000000);
	pm_runसमय_put(mcasp->dev);

	/* Skip audio related setup code अगर the configuration is not adequat */
	अगर (mcasp->missing_audio_param)
		जाओ no_audio;

	irq = platक्रमm_get_irq_byname_optional(pdev, "common");
	अगर (irq > 0) अणु
		irq_name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%s_common",
					  dev_name(&pdev->dev));
		अगर (!irq_name) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						davinci_mcasp_common_irq_handler,
						IRQF_ONESHOT | IRQF_SHARED,
						irq_name, mcasp);
		अगर (ret) अणु
			dev_err(&pdev->dev, "common IRQ request failed\n");
			जाओ err;
		पूर्ण

		mcasp->irq_request[SNDRV_PCM_STREAM_PLAYBACK] = XUNDRN;
		mcasp->irq_request[SNDRV_PCM_STREAM_CAPTURE] = ROVRN;
	पूर्ण

	irq = platक्रमm_get_irq_byname_optional(pdev, "rx");
	अगर (irq > 0) अणु
		irq_name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%s_rx",
					  dev_name(&pdev->dev));
		अगर (!irq_name) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						davinci_mcasp_rx_irq_handler,
						IRQF_ONESHOT, irq_name, mcasp);
		अगर (ret) अणु
			dev_err(&pdev->dev, "RX IRQ request failed\n");
			जाओ err;
		पूर्ण

		mcasp->irq_request[SNDRV_PCM_STREAM_CAPTURE] = ROVRN;
	पूर्ण

	irq = platक्रमm_get_irq_byname_optional(pdev, "tx");
	अगर (irq > 0) अणु
		irq_name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%s_tx",
					  dev_name(&pdev->dev));
		अगर (!irq_name) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						davinci_mcasp_tx_irq_handler,
						IRQF_ONESHOT, irq_name, mcasp);
		अगर (ret) अणु
			dev_err(&pdev->dev, "TX IRQ request failed\n");
			जाओ err;
		पूर्ण

		mcasp->irq_request[SNDRV_PCM_STREAM_PLAYBACK] = XUNDRN;
	पूर्ण

	dat = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dat");
	अगर (dat)
		mcasp->dat_port = true;

	dma_data = &mcasp->dma_data[SNDRV_PCM_STREAM_PLAYBACK];
	dma_data->filter_data = "tx";
	अगर (dat)
		dma_data->addr = dat->start;
	अन्यथा
		dma_data->addr = mem->start + davinci_mcasp_txdma_offset(mcasp->pdata);


	/* RX is not valid in DIT mode */
	अगर (mcasp->op_mode != DAVINCI_MCASP_DIT_MODE) अणु
		dma_data = &mcasp->dma_data[SNDRV_PCM_STREAM_CAPTURE];
		dma_data->filter_data = "rx";
		अगर (dat)
			dma_data->addr = dat->start;
		अन्यथा
			dma_data->addr =
				mem->start + davinci_mcasp_rxdma_offset(mcasp->pdata);
	पूर्ण

	अगर (mcasp->version < MCASP_VERSION_3) अणु
		mcasp->fअगरo_base = DAVINCI_MCASP_V2_AFIFO_BASE;
		/* dma_params->dma_addr is poपूर्णांकing to the data port address */
		mcasp->dat_port = true;
	पूर्ण अन्यथा अणु
		mcasp->fअगरo_base = DAVINCI_MCASP_V3_AFIFO_BASE;
	पूर्ण

	/* Allocate memory क्रम दीर्घ enough list क्रम all possible
	 * scenarios. Maximum number tdm slots is 32 and there cannot
	 * be more serializers than given in the configuration.  The
	 * serializer directions could be taken पूर्णांकo account, but it
	 * would make code much more complex and save only couple of
	 * bytes.
	 */
	mcasp->chस्थिरr[SNDRV_PCM_STREAM_PLAYBACK].list =
		devm_kसुस्मृति(mcasp->dev,
			     32 + mcasp->num_serializer - 1,
			     माप(अचिन्हित पूर्णांक),
			     GFP_KERNEL);

	mcasp->chस्थिरr[SNDRV_PCM_STREAM_CAPTURE].list =
		devm_kसुस्मृति(mcasp->dev,
			     32 + mcasp->num_serializer - 1,
			     माप(अचिन्हित पूर्णांक),
			     GFP_KERNEL);

	अगर (!mcasp->chस्थिरr[SNDRV_PCM_STREAM_PLAYBACK].list ||
	    !mcasp->chस्थिरr[SNDRV_PCM_STREAM_CAPTURE].list) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = davinci_mcasp_set_ch_स्थिरraपूर्णांकs(mcasp);
	अगर (ret)
		जाओ err;

	mcasp_reparent_fck(pdev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &davinci_mcasp_component,
					      &davinci_mcasp_dai[mcasp->op_mode], 1);

	अगर (ret != 0)
		जाओ err;

	ret = davinci_mcasp_get_dma_type(mcasp);
	चयन (ret) अणु
	हाल PCM_EDMA:
		ret = edma_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
		अवरोध;
	हाल PCM_SDMA:
		ret = sdma_pcm_platक्रमm_रेजिस्टर(&pdev->dev, "tx", "rx");
		अवरोध;
	हाल PCM_UDMA:
		ret = udma_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "No DMA controller found (%d)\n", ret);
	हाल -EPROBE_DEFER:
		जाओ err;
	पूर्ण

	अगर (ret) अणु
		dev_err(&pdev->dev, "register PCM failed: %d\n", ret);
		जाओ err;
	पूर्ण

no_audio:
	ret = davinci_mcasp_init_gpiochip(mcasp);
	अगर (ret) अणु
		dev_err(&pdev->dev, "gpiochip registration failed: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक davinci_mcasp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक davinci_mcasp_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा davinci_mcasp *mcasp = dev_get_drvdata(dev);
	काष्ठा davinci_mcasp_context *context = &mcasp->context;
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(context_regs); i++)
		context->config_regs[i] = mcasp_get_reg(mcasp, context_regs[i]);

	अगर (mcasp->txnumevt) अणु
		reg = mcasp->fअगरo_base + MCASP_WFIFOCTL_OFFSET;
		context->afअगरo_regs[0] = mcasp_get_reg(mcasp, reg);
	पूर्ण
	अगर (mcasp->rxnumevt) अणु
		reg = mcasp->fअगरo_base + MCASP_RFIFOCTL_OFFSET;
		context->afअगरo_regs[1] = mcasp_get_reg(mcasp, reg);
	पूर्ण

	क्रम (i = 0; i < mcasp->num_serializer; i++)
		context->xrsr_regs[i] = mcasp_get_reg(mcasp,
						DAVINCI_MCASP_XRSRCTL_REG(i));

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mcasp_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा davinci_mcasp *mcasp = dev_get_drvdata(dev);
	काष्ठा davinci_mcasp_context *context = &mcasp->context;
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(context_regs); i++)
		mcasp_set_reg(mcasp, context_regs[i], context->config_regs[i]);

	अगर (mcasp->txnumevt) अणु
		reg = mcasp->fअगरo_base + MCASP_WFIFOCTL_OFFSET;
		mcasp_set_reg(mcasp, reg, context->afअगरo_regs[0]);
	पूर्ण
	अगर (mcasp->rxnumevt) अणु
		reg = mcasp->fअगरo_base + MCASP_RFIFOCTL_OFFSET;
		mcasp_set_reg(mcasp, reg, context->afअगरo_regs[1]);
	पूर्ण

	क्रम (i = 0; i < mcasp->num_serializer; i++)
		mcasp_set_reg(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
			      context->xrsr_regs[i]);

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops davinci_mcasp_pm_ops = अणु
	SET_RUNTIME_PM_OPS(davinci_mcasp_runसमय_suspend,
			   davinci_mcasp_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver davinci_mcasp_driver = अणु
	.probe		= davinci_mcasp_probe,
	.हटाओ		= davinci_mcasp_हटाओ,
	.driver		= अणु
		.name	= "davinci-mcasp",
		.pm     = &davinci_mcasp_pm_ops,
		.of_match_table = mcasp_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(davinci_mcasp_driver);

MODULE_AUTHOR("Steve Chen");
MODULE_DESCRIPTION("TI DAVINCI McASP SoC Interface");
MODULE_LICENSE("GPL");
