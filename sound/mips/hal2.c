<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम A2 audio प्रणाली used in SGI machines
 *  Copyright (c) 2008 Thomas Bogenकरोerfer <tsbogend@alpha.fanken.de>
 *
 *  Based on OSS code from Ladislav Michl <ladis@linux-mips.org>, which
 *  was based on code from Ulf Carlsson
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm-indirect.h>
#समावेश <sound/initval.h>

#समावेश "hal2.h"

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;  /* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;   /* ID क्रम this card */

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for SGI HAL2 soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for SGI HAL2 soundcard.");
MODULE_DESCRIPTION("ALSA driver for SGI HAL2 audio");
MODULE_AUTHOR("Thomas Bogendoerfer");
MODULE_LICENSE("GPL");


#घोषणा H2_BLOCK_SIZE	1024
#घोषणा H2_BUF_SIZE	16384

काष्ठा hal2_pbus अणु
	काष्ठा hpc3_pbus_dmacregs *pbus;
	पूर्णांक pbusnr;
	अचिन्हित पूर्णांक ctrl;		/* Current state of pbus->pbdma_ctrl */
पूर्ण;

काष्ठा hal2_desc अणु
	काष्ठा hpc_dma_desc desc;
	u32 pad;			/* padding */
पूर्ण;

काष्ठा hal2_codec अणु
	काष्ठा snd_pcm_indirect pcm_indirect;
	काष्ठा snd_pcm_substream *substream;

	अचिन्हित अक्षर *buffer;
	dma_addr_t buffer_dma;
	काष्ठा hal2_desc *desc;
	dma_addr_t desc_dma;
	पूर्णांक desc_count;
	काष्ठा hal2_pbus pbus;
	पूर्णांक voices;			/* mono/stereo */
	अचिन्हित पूर्णांक sample_rate;
	अचिन्हित पूर्णांक master;		/* Master frequency */
	अचिन्हित लघु mod;		/* MOD value */
	अचिन्हित लघु inc;		/* INC value */
पूर्ण;

#घोषणा H2_MIX_OUTPUT_ATT	0
#घोषणा H2_MIX_INPUT_GAIN	1

काष्ठा snd_hal2 अणु
	काष्ठा snd_card *card;

	काष्ठा hal2_ctl_regs *ctl_regs;	/* HAL2 ctl रेजिस्टरs */
	काष्ठा hal2_aes_regs *aes_regs;	/* HAL2 aes रेजिस्टरs */
	काष्ठा hal2_vol_regs *vol_regs;	/* HAL2 vol रेजिस्टरs */
	काष्ठा hal2_syn_regs *syn_regs;	/* HAL2 syn रेजिस्टरs */

	काष्ठा hal2_codec dac;
	काष्ठा hal2_codec adc;
पूर्ण;

#घोषणा H2_INसूचीECT_WAIT(regs)	जबतक (hal2_पढ़ो(&regs->isr) & H2_ISR_TSTATUS);

#घोषणा H2_READ_ADDR(addr)	(addr | (1<<7))
#घोषणा H2_WRITE_ADDR(addr)	(addr)

अटल अंतरभूत u32 hal2_पढ़ो(u32 *reg)
अणु
	वापस __raw_पढ़ोl(reg);
पूर्ण

अटल अंतरभूत व्योम hal2_ग_लिखो(u32 val, u32 *reg)
अणु
	__raw_ग_लिखोl(val, reg);
पूर्ण


अटल u32 hal2_i_पढ़ो32(काष्ठा snd_hal2 *hal2, u16 addr)
अणु
	u32 ret;
	काष्ठा hal2_ctl_regs *regs = hal2->ctl_regs;

	hal2_ग_लिखो(H2_READ_ADDR(addr), &regs->iar);
	H2_INसूचीECT_WAIT(regs);
	ret = hal2_पढ़ो(&regs->idr0) & 0xffff;
	hal2_ग_लिखो(H2_READ_ADDR(addr) | 0x1, &regs->iar);
	H2_INसूचीECT_WAIT(regs);
	ret |= (hal2_पढ़ो(&regs->idr0) & 0xffff) << 16;
	वापस ret;
पूर्ण

अटल व्योम hal2_i_ग_लिखो16(काष्ठा snd_hal2 *hal2, u16 addr, u16 val)
अणु
	काष्ठा hal2_ctl_regs *regs = hal2->ctl_regs;

	hal2_ग_लिखो(val, &regs->idr0);
	hal2_ग_लिखो(0, &regs->idr1);
	hal2_ग_लिखो(0, &regs->idr2);
	hal2_ग_लिखो(0, &regs->idr3);
	hal2_ग_लिखो(H2_WRITE_ADDR(addr), &regs->iar);
	H2_INसूचीECT_WAIT(regs);
पूर्ण

अटल व्योम hal2_i_ग_लिखो32(काष्ठा snd_hal2 *hal2, u16 addr, u32 val)
अणु
	काष्ठा hal2_ctl_regs *regs = hal2->ctl_regs;

	hal2_ग_लिखो(val & 0xffff, &regs->idr0);
	hal2_ग_लिखो(val >> 16, &regs->idr1);
	hal2_ग_लिखो(0, &regs->idr2);
	hal2_ग_लिखो(0, &regs->idr3);
	hal2_ग_लिखो(H2_WRITE_ADDR(addr), &regs->iar);
	H2_INसूचीECT_WAIT(regs);
पूर्ण

अटल व्योम hal2_i_setbit16(काष्ठा snd_hal2 *hal2, u16 addr, u16 bit)
अणु
	काष्ठा hal2_ctl_regs *regs = hal2->ctl_regs;

	hal2_ग_लिखो(H2_READ_ADDR(addr), &regs->iar);
	H2_INसूचीECT_WAIT(regs);
	hal2_ग_लिखो((hal2_पढ़ो(&regs->idr0) & 0xffff) | bit, &regs->idr0);
	hal2_ग_लिखो(0, &regs->idr1);
	hal2_ग_लिखो(0, &regs->idr2);
	hal2_ग_लिखो(0, &regs->idr3);
	hal2_ग_लिखो(H2_WRITE_ADDR(addr), &regs->iar);
	H2_INसूचीECT_WAIT(regs);
पूर्ण

अटल व्योम hal2_i_clearbit16(काष्ठा snd_hal2 *hal2, u16 addr, u16 bit)
अणु
	काष्ठा hal2_ctl_regs *regs = hal2->ctl_regs;

	hal2_ग_लिखो(H2_READ_ADDR(addr), &regs->iar);
	H2_INसूचीECT_WAIT(regs);
	hal2_ग_लिखो((hal2_पढ़ो(&regs->idr0) & 0xffff) & ~bit, &regs->idr0);
	hal2_ग_लिखो(0, &regs->idr1);
	hal2_ग_लिखो(0, &regs->idr2);
	hal2_ग_लिखो(0, &regs->idr3);
	hal2_ग_लिखो(H2_WRITE_ADDR(addr), &regs->iar);
	H2_INसूचीECT_WAIT(regs);
पूर्ण

अटल पूर्णांक hal2_gain_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	चयन ((पूर्णांक)kcontrol->निजी_value) अणु
	हाल H2_MIX_OUTPUT_ATT:
		uinfo->value.पूर्णांकeger.max = 31;
		अवरोध;
	हाल H2_MIX_INPUT_GAIN:
		uinfo->value.पूर्णांकeger.max = 15;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hal2_gain_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_hal2 *hal2 = snd_kcontrol_chip(kcontrol);
	u32 पंचांगp;
	पूर्णांक l, r;

	चयन ((पूर्णांक)kcontrol->निजी_value) अणु
	हाल H2_MIX_OUTPUT_ATT:
		पंचांगp = hal2_i_पढ़ो32(hal2, H2I_DAC_C2);
		अगर (पंचांगp & H2I_C2_MUTE) अणु
			l = 0;
			r = 0;
		पूर्ण अन्यथा अणु
			l = 31 - ((पंचांगp >> H2I_C2_L_ATT_SHIFT) & 31);
			r = 31 - ((पंचांगp >> H2I_C2_R_ATT_SHIFT) & 31);
		पूर्ण
		अवरोध;
	हाल H2_MIX_INPUT_GAIN:
		पंचांगp = hal2_i_पढ़ो32(hal2, H2I_ADC_C2);
		l = (पंचांगp >> H2I_C2_L_GAIN_SHIFT) & 15;
		r = (पंचांगp >> H2I_C2_R_GAIN_SHIFT) & 15;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = l;
	ucontrol->value.पूर्णांकeger.value[1] = r;

	वापस 0;
पूर्ण

अटल पूर्णांक hal2_gain_put(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_hal2 *hal2 = snd_kcontrol_chip(kcontrol);
	u32 old, new;
	पूर्णांक l, r;

	l = ucontrol->value.पूर्णांकeger.value[0];
	r = ucontrol->value.पूर्णांकeger.value[1];

	चयन ((पूर्णांक)kcontrol->निजी_value) अणु
	हाल H2_MIX_OUTPUT_ATT:
		old = hal2_i_पढ़ो32(hal2, H2I_DAC_C2);
		new = old & ~(H2I_C2_L_ATT_M | H2I_C2_R_ATT_M | H2I_C2_MUTE);
		अगर (l | r) अणु
			l = 31 - l;
			r = 31 - r;
			new |= (l << H2I_C2_L_ATT_SHIFT);
			new |= (r << H2I_C2_R_ATT_SHIFT);
		पूर्ण अन्यथा
			new |= H2I_C2_L_ATT_M | H2I_C2_R_ATT_M | H2I_C2_MUTE;
		hal2_i_ग_लिखो32(hal2, H2I_DAC_C2, new);
		अवरोध;
	हाल H2_MIX_INPUT_GAIN:
		old = hal2_i_पढ़ो32(hal2, H2I_ADC_C2);
		new = old & ~(H2I_C2_L_GAIN_M | H2I_C2_R_GAIN_M);
		new |= (l << H2I_C2_L_GAIN_SHIFT);
		new |= (r << H2I_C2_R_GAIN_SHIFT);
		hal2_i_ग_लिखो32(hal2, H2I_ADC_C2, new);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस old != new;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new hal2_ctrl_headphone = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "Headphone Playback Volume",
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = H2_MIX_OUTPUT_ATT,
	.info           = hal2_gain_info,
	.get            = hal2_gain_get,
	.put            = hal2_gain_put,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new hal2_ctrl_mic = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "Mic Capture Volume",
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = H2_MIX_INPUT_GAIN,
	.info           = hal2_gain_info,
	.get            = hal2_gain_get,
	.put            = hal2_gain_put,
पूर्ण;

अटल पूर्णांक hal2_mixer_create(काष्ठा snd_hal2 *hal2)
अणु
	पूर्णांक err;

	/* mute DAC */
	hal2_i_ग_लिखो32(hal2, H2I_DAC_C2,
		       H2I_C2_L_ATT_M | H2I_C2_R_ATT_M | H2I_C2_MUTE);
	/* mute ADC */
	hal2_i_ग_लिखो32(hal2, H2I_ADC_C2, 0);

	err = snd_ctl_add(hal2->card,
			  snd_ctl_new1(&hal2_ctrl_headphone, hal2));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(hal2->card,
			  snd_ctl_new1(&hal2_ctrl_mic, hal2));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल irqवापस_t hal2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_hal2 *hal2 = dev_id;
	irqवापस_t ret = IRQ_NONE;

	/* decide what caused this पूर्णांकerrupt */
	अगर (hal2->dac.pbus.pbus->pbdma_ctrl & HPC3_PDMACTRL_INT) अणु
		snd_pcm_period_elapsed(hal2->dac.substream);
		ret = IRQ_HANDLED;
	पूर्ण
	अगर (hal2->adc.pbus.pbus->pbdma_ctrl & HPC3_PDMACTRL_INT) अणु
		snd_pcm_period_elapsed(hal2->adc.substream);
		ret = IRQ_HANDLED;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक hal2_compute_rate(काष्ठा hal2_codec *codec, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित लघु mod;

	अगर (44100 % rate < 48000 % rate) अणु
		mod = 4 * 44100 / rate;
		codec->master = 44100;
	पूर्ण अन्यथा अणु
		mod = 4 * 48000 / rate;
		codec->master = 48000;
	पूर्ण

	codec->inc = 4;
	codec->mod = mod;
	rate = 4 * codec->master / mod;

	वापस rate;
पूर्ण

अटल व्योम hal2_set_dac_rate(काष्ठा snd_hal2 *hal2)
अणु
	अचिन्हित पूर्णांक master = hal2->dac.master;
	पूर्णांक inc = hal2->dac.inc;
	पूर्णांक mod = hal2->dac.mod;

	hal2_i_ग_लिखो16(hal2, H2I_BRES1_C1, (master == 44100) ? 1 : 0);
	hal2_i_ग_लिखो32(hal2, H2I_BRES1_C2,
		       ((0xffff & (inc - mod - 1)) << 16) | inc);
पूर्ण

अटल व्योम hal2_set_adc_rate(काष्ठा snd_hal2 *hal2)
अणु
	अचिन्हित पूर्णांक master = hal2->adc.master;
	पूर्णांक inc = hal2->adc.inc;
	पूर्णांक mod = hal2->adc.mod;

	hal2_i_ग_लिखो16(hal2, H2I_BRES2_C1, (master == 44100) ? 1 : 0);
	hal2_i_ग_लिखो32(hal2, H2I_BRES2_C2,
		       ((0xffff & (inc - mod - 1)) << 16) | inc);
पूर्ण

अटल व्योम hal2_setup_dac(काष्ठा snd_hal2 *hal2)
अणु
	अचिन्हित पूर्णांक fअगरobeg, fअगरoend, highwater, sample_size;
	काष्ठा hal2_pbus *pbus = &hal2->dac.pbus;

	/* Now we set up some PBUS inक्रमmation. The PBUS needs inक्रमmation about
	 * what portion of the fअगरo it will use. If it's receiving or
	 * transmitting, and finally whether the stream is little endian or big
	 * endian. The inक्रमmation is written later, on the start call.
	 */
	sample_size = 2 * hal2->dac.voices;
	/* Fअगरo should be set to hold exactly four samples. Highwater mark
	 * should be set to two samples. */
	highwater = (sample_size * 2) >> 1;	/* halfwords */
	fअगरobeg = 0;				/* playback is first */
	fअगरoend = (sample_size * 4) >> 3;	/* द्विगुनwords */
	pbus->ctrl = HPC3_PDMACTRL_RT | HPC3_PDMACTRL_LD |
		     (highwater << 8) | (fअगरobeg << 16) | (fअगरoend << 24);
	/* We disable everything beक्रमe we करो anything at all */
	pbus->pbus->pbdma_ctrl = HPC3_PDMACTRL_LD;
	hal2_i_clearbit16(hal2, H2I_DMA_PORT_EN, H2I_DMA_PORT_EN_CODECTX);
	/* Setup the HAL2 क्रम playback */
	hal2_set_dac_rate(hal2);
	/* Set endianess */
	hal2_i_clearbit16(hal2, H2I_DMA_END, H2I_DMA_END_CODECTX);
	/* Set DMA bus */
	hal2_i_setbit16(hal2, H2I_DMA_DRV, (1 << pbus->pbusnr));
	/* We are using 1st Bresenham घड़ी generator क्रम playback */
	hal2_i_ग_लिखो16(hal2, H2I_DAC_C1, (pbus->pbusnr << H2I_C1_DMA_SHIFT)
			| (1 << H2I_C1_CLKID_SHIFT)
			| (hal2->dac.voices << H2I_C1_DATAT_SHIFT));
पूर्ण

अटल व्योम hal2_setup_adc(काष्ठा snd_hal2 *hal2)
अणु
	अचिन्हित पूर्णांक fअगरobeg, fअगरoend, highwater, sample_size;
	काष्ठा hal2_pbus *pbus = &hal2->adc.pbus;

	sample_size = 2 * hal2->adc.voices;
	highwater = (sample_size * 2) >> 1;		/* halfwords */
	fअगरobeg = (4 * 4) >> 3;				/* record is second */
	fअगरoend = (4 * 4 + sample_size * 4) >> 3;	/* द्विगुनwords */
	pbus->ctrl = HPC3_PDMACTRL_RT | HPC3_PDMACTRL_RCV | HPC3_PDMACTRL_LD |
		     (highwater << 8) | (fअगरobeg << 16) | (fअगरoend << 24);
	pbus->pbus->pbdma_ctrl = HPC3_PDMACTRL_LD;
	hal2_i_clearbit16(hal2, H2I_DMA_PORT_EN, H2I_DMA_PORT_EN_CODECR);
	/* Setup the HAL2 क्रम record */
	hal2_set_adc_rate(hal2);
	/* Set endianess */
	hal2_i_clearbit16(hal2, H2I_DMA_END, H2I_DMA_END_CODECR);
	/* Set DMA bus */
	hal2_i_setbit16(hal2, H2I_DMA_DRV, (1 << pbus->pbusnr));
	/* We are using 2nd Bresenham घड़ी generator क्रम record */
	hal2_i_ग_लिखो16(hal2, H2I_ADC_C1, (pbus->pbusnr << H2I_C1_DMA_SHIFT)
			| (2 << H2I_C1_CLKID_SHIFT)
			| (hal2->adc.voices << H2I_C1_DATAT_SHIFT));
पूर्ण

अटल व्योम hal2_start_dac(काष्ठा snd_hal2 *hal2)
अणु
	काष्ठा hal2_pbus *pbus = &hal2->dac.pbus;

	pbus->pbus->pbdma_dptr = hal2->dac.desc_dma;
	pbus->pbus->pbdma_ctrl = pbus->ctrl | HPC3_PDMACTRL_ACT;
	/* enable DAC */
	hal2_i_setbit16(hal2, H2I_DMA_PORT_EN, H2I_DMA_PORT_EN_CODECTX);
पूर्ण

अटल व्योम hal2_start_adc(काष्ठा snd_hal2 *hal2)
अणु
	काष्ठा hal2_pbus *pbus = &hal2->adc.pbus;

	pbus->pbus->pbdma_dptr = hal2->adc.desc_dma;
	pbus->pbus->pbdma_ctrl = pbus->ctrl | HPC3_PDMACTRL_ACT;
	/* enable ADC */
	hal2_i_setbit16(hal2, H2I_DMA_PORT_EN, H2I_DMA_PORT_EN_CODECR);
पूर्ण

अटल अंतरभूत व्योम hal2_stop_dac(काष्ठा snd_hal2 *hal2)
अणु
	hal2->dac.pbus.pbus->pbdma_ctrl = HPC3_PDMACTRL_LD;
	/* The HAL2 itself may reमुख्य enabled safely */
पूर्ण

अटल अंतरभूत व्योम hal2_stop_adc(काष्ठा snd_hal2 *hal2)
अणु
	hal2->adc.pbus.pbus->pbdma_ctrl = HPC3_PDMACTRL_LD;
पूर्ण

अटल पूर्णांक hal2_alloc_dmabuf(काष्ठा snd_hal2 *hal2, काष्ठा hal2_codec *codec,
		क्रमागत dma_data_direction buffer_dir)
अणु
	काष्ठा device *dev = hal2->card->dev;
	काष्ठा hal2_desc *desc;
	dma_addr_t desc_dma, buffer_dma;
	पूर्णांक count = H2_BUF_SIZE / H2_BLOCK_SIZE;
	पूर्णांक i;

	codec->buffer = dma_alloc_noncoherent(dev, H2_BUF_SIZE, &buffer_dma,
					buffer_dir, GFP_KERNEL);
	अगर (!codec->buffer)
		वापस -ENOMEM;
	desc = dma_alloc_noncoherent(dev, count * माप(काष्ठा hal2_desc),
			&desc_dma, DMA_BIसूचीECTIONAL, GFP_KERNEL);
	अगर (!desc) अणु
		dma_मुक्त_noncoherent(dev, H2_BUF_SIZE, codec->buffer, buffer_dma,
				buffer_dir);
		वापस -ENOMEM;
	पूर्ण
	codec->buffer_dma = buffer_dma;
	codec->desc_dma = desc_dma;
	codec->desc = desc;
	क्रम (i = 0; i < count; i++) अणु
		desc->desc.pbuf = buffer_dma + i * H2_BLOCK_SIZE;
		desc->desc.cntinfo = HPCDMA_XIE | H2_BLOCK_SIZE;
		desc->desc.pnext = (i == count - 1) ?
		      desc_dma : desc_dma + (i + 1) * माप(काष्ठा hal2_desc);
		desc++;
	पूर्ण
	dma_sync_single_क्रम_device(dev, codec->desc_dma,
				   count * माप(काष्ठा hal2_desc),
				   DMA_BIसूचीECTIONAL);
	codec->desc_count = count;
	वापस 0;
पूर्ण

अटल व्योम hal2_मुक्त_dmabuf(काष्ठा snd_hal2 *hal2, काष्ठा hal2_codec *codec,
		क्रमागत dma_data_direction buffer_dir)
अणु
	काष्ठा device *dev = hal2->card->dev;

	dma_मुक्त_noncoherent(dev, codec->desc_count * माप(काष्ठा hal2_desc),
		       codec->desc, codec->desc_dma, DMA_BIसूचीECTIONAL);
	dma_मुक्त_noncoherent(dev, H2_BUF_SIZE, codec->buffer, codec->buffer_dma,
			buffer_dir);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware hal2_pcm_hw = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats =          SNDRV_PCM_FMTBIT_S16_BE,
	.rates =            SNDRV_PCM_RATE_8000_48000,
	.rate_min =         8000,
	.rate_max =         48000,
	.channels_min =     2,
	.channels_max =     2,
	.buffer_bytes_max = 65536,
	.period_bytes_min = 1024,
	.period_bytes_max = 65536,
	.periods_min =      2,
	.periods_max =      1024,
पूर्ण;

अटल पूर्णांक hal2_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	runसमय->hw = hal2_pcm_hw;
	वापस hal2_alloc_dmabuf(hal2, &hal2->dac, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक hal2_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	hal2_मुक्त_dmabuf(hal2, &hal2->dac, DMA_TO_DEVICE);
	वापस 0;
पूर्ण

अटल पूर्णांक hal2_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा hal2_codec *dac = &hal2->dac;

	dac->voices = runसमय->channels;
	dac->sample_rate = hal2_compute_rate(dac, runसमय->rate);
	स_रखो(&dac->pcm_indirect, 0, माप(dac->pcm_indirect));
	dac->pcm_indirect.hw_buffer_size = H2_BUF_SIZE;
	dac->pcm_indirect.hw_queue_size = H2_BUF_SIZE / 2;
	dac->pcm_indirect.hw_io = dac->buffer_dma;
	dac->pcm_indirect.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	dac->substream = substream;
	hal2_setup_dac(hal2);
	वापस 0;
पूर्ण

अटल पूर्णांक hal2_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		hal2_start_dac(hal2);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		hal2_stop_dac(hal2);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
hal2_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	काष्ठा hal2_codec *dac = &hal2->dac;

	वापस snd_pcm_indirect_playback_poपूर्णांकer(substream, &dac->pcm_indirect,
						 dac->pbus.pbus->pbdma_bptr);
पूर्ण

अटल व्योम hal2_playback_transfer(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर *buf = hal2->dac.buffer + rec->hw_data;

	स_नकल(buf, substream->runसमय->dma_area + rec->sw_data, bytes);
	dma_sync_single_क्रम_device(hal2->card->dev,
			hal2->dac.buffer_dma + rec->hw_data, bytes,
			DMA_TO_DEVICE);

पूर्ण

अटल पूर्णांक hal2_playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	काष्ठा hal2_codec *dac = &hal2->dac;

	वापस snd_pcm_indirect_playback_transfer(substream,
						  &dac->pcm_indirect,
						  hal2_playback_transfer);
पूर्ण

अटल पूर्णांक hal2_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	runसमय->hw = hal2_pcm_hw;
	वापस hal2_alloc_dmabuf(hal2, &hal2->adc, DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक hal2_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	hal2_मुक्त_dmabuf(hal2, &hal2->adc, DMA_FROM_DEVICE);
	वापस 0;
पूर्ण

अटल पूर्णांक hal2_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा hal2_codec *adc = &hal2->adc;

	adc->voices = runसमय->channels;
	adc->sample_rate = hal2_compute_rate(adc, runसमय->rate);
	स_रखो(&adc->pcm_indirect, 0, माप(adc->pcm_indirect));
	adc->pcm_indirect.hw_buffer_size = H2_BUF_SIZE;
	adc->pcm_indirect.hw_queue_size = H2_BUF_SIZE / 2;
	adc->pcm_indirect.hw_io = adc->buffer_dma;
	adc->pcm_indirect.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	adc->substream = substream;
	hal2_setup_adc(hal2);
	वापस 0;
पूर्ण

अटल पूर्णांक hal2_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		hal2_start_adc(hal2);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		hal2_stop_adc(hal2);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
hal2_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	काष्ठा hal2_codec *adc = &hal2->adc;

	वापस snd_pcm_indirect_capture_poपूर्णांकer(substream, &adc->pcm_indirect,
						adc->pbus.pbus->pbdma_bptr);
पूर्ण

अटल व्योम hal2_capture_transfer(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर *buf = hal2->adc.buffer + rec->hw_data;

	dma_sync_single_क्रम_cpu(hal2->card->dev,
			hal2->adc.buffer_dma + rec->hw_data, bytes,
			DMA_FROM_DEVICE);
	स_नकल(substream->runसमय->dma_area + rec->sw_data, buf, bytes);
पूर्ण

अटल पूर्णांक hal2_capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	काष्ठा hal2_codec *adc = &hal2->adc;

	वापस snd_pcm_indirect_capture_transfer(substream,
						 &adc->pcm_indirect,
						 hal2_capture_transfer);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops hal2_playback_ops = अणु
	.खोलो =        hal2_playback_खोलो,
	.बंद =       hal2_playback_बंद,
	.prepare =     hal2_playback_prepare,
	.trigger =     hal2_playback_trigger,
	.poपूर्णांकer =     hal2_playback_poपूर्णांकer,
	.ack =         hal2_playback_ack,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops hal2_capture_ops = अणु
	.खोलो =        hal2_capture_खोलो,
	.बंद =       hal2_capture_बंद,
	.prepare =     hal2_capture_prepare,
	.trigger =     hal2_capture_trigger,
	.poपूर्णांकer =     hal2_capture_poपूर्णांकer,
	.ack =         hal2_capture_ack,
पूर्ण;

अटल पूर्णांक hal2_pcm_create(काष्ठा snd_hal2 *hal2)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	/* create first pcm device with one outमाला_दो and one input */
	err = snd_pcm_new(hal2->card, "SGI HAL2 Audio", 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = hal2;
	म_नकल(pcm->name, "SGI HAL2");

	/* set चालकs */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&hal2_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&hal2_capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, 0, 1024 * 1024);

	वापस 0;
पूर्ण

अटल पूर्णांक hal2_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_hal2 *hal2 = device->device_data;

	मुक्त_irq(SGI_HPCDMA_IRQ, hal2);
	kमुक्त(hal2);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_device_ops hal2_ops = अणु
	.dev_मुक्त = hal2_dev_मुक्त,
पूर्ण;

अटल व्योम hal2_init_codec(काष्ठा hal2_codec *codec, काष्ठा hpc3_regs *hpc3,
			    पूर्णांक index)
अणु
	codec->pbus.pbusnr = index;
	codec->pbus.pbus = &hpc3->pbdma[index];
पूर्ण

अटल पूर्णांक hal2_detect(काष्ठा snd_hal2 *hal2)
अणु
	अचिन्हित लघु board, major, minor;
	अचिन्हित लघु rev;

	/* reset HAL2 */
	hal2_ग_लिखो(0, &hal2->ctl_regs->isr);

	/* release reset */
	hal2_ग_लिखो(H2_ISR_GLOBAL_RESET_N | H2_ISR_CODEC_RESET_N,
		   &hal2->ctl_regs->isr);


	hal2_i_ग_लिखो16(hal2, H2I_RELAY_C, H2I_RELAY_C_STATE);
	rev = hal2_पढ़ो(&hal2->ctl_regs->rev);
	अगर (rev & H2_REV_AUDIO_PRESENT)
		वापस -ENODEV;

	board = (rev & H2_REV_BOARD_M) >> 12;
	major = (rev & H2_REV_MAJOR_CHIP_M) >> 4;
	minor = (rev & H2_REV_MINOR_CHIP_M);

	prपूर्णांकk(KERN_INFO "SGI HAL2 revision %i.%i.%i\n",
	       board, major, minor);

	वापस 0;
पूर्ण

अटल पूर्णांक hal2_create(काष्ठा snd_card *card, काष्ठा snd_hal2 **rchip)
अणु
	काष्ठा snd_hal2 *hal2;
	काष्ठा hpc3_regs *hpc3 = hpc3c0;
	पूर्णांक err;

	hal2 = kzalloc(माप(*hal2), GFP_KERNEL);
	अगर (!hal2)
		वापस -ENOMEM;

	hal2->card = card;

	अगर (request_irq(SGI_HPCDMA_IRQ, hal2_पूर्णांकerrupt, IRQF_SHARED,
			"SGI HAL2", hal2)) अणु
		prपूर्णांकk(KERN_ERR "HAL2: Can't get irq %d\n", SGI_HPCDMA_IRQ);
		kमुक्त(hal2);
		वापस -EAGAIN;
	पूर्ण

	hal2->ctl_regs = (काष्ठा hal2_ctl_regs *)hpc3->pbus_extregs[0];
	hal2->aes_regs = (काष्ठा hal2_aes_regs *)hpc3->pbus_extregs[1];
	hal2->vol_regs = (काष्ठा hal2_vol_regs *)hpc3->pbus_extregs[2];
	hal2->syn_regs = (काष्ठा hal2_syn_regs *)hpc3->pbus_extregs[3];

	अगर (hal2_detect(hal2) < 0) अणु
		kमुक्त(hal2);
		वापस -ENODEV;
	पूर्ण

	hal2_init_codec(&hal2->dac, hpc3, 0);
	hal2_init_codec(&hal2->adc, hpc3, 1);

	/*
	 * All DMA channel पूर्णांकerfaces in HAL2 are deचिन्हित to operate with
	 * PBUS programmed क्रम 2 cycles in D3, 2 cycles in D4 and 2 cycles
	 * in D5. HAL2 is a 16-bit device which can accept both big and little
	 * endian क्रमmat. It assumes that even address bytes are on high
	 * portion of PBUS (15:8) and assumes that HPC3 is programmed to
	 * accept a live (unsynchronized) version of P_DREQ_N from HAL2.
	 */
#घोषणा HAL2_PBUS_DMACFG ((0 << HPC3_DMACFG_D3R_SHIFT) | \
			  (2 << HPC3_DMACFG_D4R_SHIFT) | \
			  (2 << HPC3_DMACFG_D5R_SHIFT) | \
			  (0 << HPC3_DMACFG_D3W_SHIFT) | \
			  (2 << HPC3_DMACFG_D4W_SHIFT) | \
			  (2 << HPC3_DMACFG_D5W_SHIFT) | \
				HPC3_DMACFG_DS16 | \
				HPC3_DMACFG_EVENHI | \
				HPC3_DMACFG_RTIME | \
			  (8 << HPC3_DMACFG_BURST_SHIFT) | \
				HPC3_DMACFG_DRQLIVE)
	/*
	 * Ignore what's mentioned in the specअगरication and ग_लिखो value which
	 * works in The Real World (TM)
	 */
	hpc3->pbus_dmacfg[hal2->dac.pbus.pbusnr][0] = 0x8208844;
	hpc3->pbus_dmacfg[hal2->adc.pbus.pbusnr][0] = 0x8208844;

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, hal2, &hal2_ops);
	अगर (err < 0) अणु
		मुक्त_irq(SGI_HPCDMA_IRQ, hal2);
		kमुक्त(hal2);
		वापस err;
	पूर्ण
	*rchip = hal2;
	वापस 0;
पूर्ण

अटल पूर्णांक hal2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_hal2 *chip;
	पूर्णांक err;

	err = snd_card_new(&pdev->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	err = hal2_create(card, &chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = hal2_pcm_create(chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	err = hal2_mixer_create(chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	म_नकल(card->driver, "SGI HAL2 Audio");
	म_नकल(card->लघुname, "SGI HAL2 Audio");
	प्र_लिखो(card->दीर्घname, "%s irq %i",
		card->लघुname,
		SGI_HPCDMA_IRQ);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	platक्रमm_set_drvdata(pdev, card);
	वापस 0;
पूर्ण

अटल पूर्णांक hal2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card = platक्रमm_get_drvdata(pdev);

	snd_card_मुक्त(card);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hal2_driver = अणु
	.probe	= hal2_probe,
	.हटाओ	= hal2_हटाओ,
	.driver = अणु
		.name	= "sgihal2",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(hal2_driver);
