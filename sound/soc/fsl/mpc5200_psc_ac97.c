<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// linux/sound/mpc5200-ac97.c -- AC97 support क्रम the Freescale MPC52xx chip.
//
// Copyright (C) 2009 Jon Smirl, Digispeaker
// Author: Jon Smirl <jonsmirl@gmail.com>

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/mpc52xx_psc.h>

#समावेश "mpc5200_dma.h"

#घोषणा DRV_NAME "mpc5200-psc-ac97"

/* ALSA only supports a single AC97 device so अटल is recommend here */
अटल काष्ठा psc_dma *psc_dma;

अटल अचिन्हित लघु psc_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक val;

	mutex_lock(&psc_dma->mutex);

	/* Wait क्रम command send status zero = पढ़ोy */
	status = spin_event_समयout(!(in_be16(&psc_dma->psc_regs->sr_csr.status) &
				MPC52xx_PSC_SR_CMDSEND), 100, 0);
	अगर (status == 0) अणु
		pr_err("timeout on ac97 bus (rdy)\n");
		mutex_unlock(&psc_dma->mutex);
		वापस -ENODEV;
	पूर्ण

	/* Force clear the data valid bit */
	in_be32(&psc_dma->psc_regs->ac97_data);

	/* Send the पढ़ो */
	out_be32(&psc_dma->psc_regs->ac97_cmd, (1<<31) | ((reg & 0x7f) << 24));

	/* Wait क्रम the answer */
	status = spin_event_समयout((in_be16(&psc_dma->psc_regs->sr_csr.status) &
				MPC52xx_PSC_SR_DATA_VAL), 100, 0);
	अगर (status == 0) अणु
		pr_err("timeout on ac97 read (val) %x\n",
				in_be16(&psc_dma->psc_regs->sr_csr.status));
		mutex_unlock(&psc_dma->mutex);
		वापस -ENODEV;
	पूर्ण
	/* Get the data */
	val = in_be32(&psc_dma->psc_regs->ac97_data);
	अगर (((val >> 24) & 0x7f) != reg) अणु
		pr_err("reg echo error on ac97 read\n");
		mutex_unlock(&psc_dma->mutex);
		वापस -ENODEV;
	पूर्ण
	val = (val >> 8) & 0xffff;

	mutex_unlock(&psc_dma->mutex);
	वापस (अचिन्हित लघु) val;
पूर्ण

अटल व्योम psc_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	पूर्णांक status;

	mutex_lock(&psc_dma->mutex);

	/* Wait क्रम command status zero = पढ़ोy */
	status = spin_event_समयout(!(in_be16(&psc_dma->psc_regs->sr_csr.status) &
				MPC52xx_PSC_SR_CMDSEND), 100, 0);
	अगर (status == 0) अणु
		pr_err("timeout on ac97 bus (write)\n");
		जाओ out;
	पूर्ण
	/* Write data */
	out_be32(&psc_dma->psc_regs->ac97_cmd,
			((reg & 0x7f) << 24) | (val << 8));

 out:
	mutex_unlock(&psc_dma->mutex);
पूर्ण

अटल व्योम psc_ac97_warm_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा mpc52xx_psc __iomem *regs = psc_dma->psc_regs;

	mutex_lock(&psc_dma->mutex);

	out_be32(&regs->sicr, psc_dma->sicr | MPC52xx_PSC_SICR_AWR);
	udelay(3);
	out_be32(&regs->sicr, psc_dma->sicr);

	mutex_unlock(&psc_dma->mutex);
पूर्ण

अटल व्योम psc_ac97_cold_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा mpc52xx_psc __iomem *regs = psc_dma->psc_regs;

	mutex_lock(&psc_dma->mutex);
	dev_dbg(psc_dma->dev, "cold reset\n");

	mpc5200_psc_ac97_gpio_reset(psc_dma->id);

	/* Notअगरy the PSC that a reset has occurred */
	out_be32(&regs->sicr, psc_dma->sicr | MPC52xx_PSC_SICR_ACRB);

	/* Re-enable RX and TX */
	out_8(&regs->command, MPC52xx_PSC_TX_ENABLE | MPC52xx_PSC_RX_ENABLE);

	mutex_unlock(&psc_dma->mutex);

	usleep_range(1000, 2000);
	psc_ac97_warm_reset(ac97);
पूर्ण

अटल काष्ठा snd_ac97_bus_ops psc_ac97_ops = अणु
	.पढ़ो		= psc_ac97_पढ़ो,
	.ग_लिखो		= psc_ac97_ग_लिखो,
	.reset		= psc_ac97_cold_reset,
	.warm_reset	= psc_ac97_warm_reset,
पूर्ण;

अटल पूर्णांक psc_ac97_hw_analog_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा psc_dma_stream *s = to_psc_dma_stream(substream, psc_dma);

	dev_dbg(psc_dma->dev, "%s(substream=%p) p_size=%i p_bytes=%i"
		" periods=%i buffer_size=%i  buffer_bytes=%i channels=%i"
		" rate=%i format=%i\n",
		__func__, substream, params_period_size(params),
		params_period_bytes(params), params_periods(params),
		params_buffer_size(params), params_buffer_bytes(params),
		params_channels(params), params_rate(params),
		params_क्रमmat(params));

	/* Determine the set of enable bits to turn on */
	s->ac97_slot_bits = (params_channels(params) == 1) ? 0x100 : 0x300;
	अगर (substream->pstr->stream != SNDRV_PCM_STREAM_CAPTURE)
		s->ac97_slot_bits <<= 16;
	वापस 0;
पूर्ण

अटल पूर्णांक psc_ac97_hw_digital_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(cpu_dai);

	dev_dbg(psc_dma->dev, "%s(substream=%p)\n", __func__, substream);

	अगर (params_channels(params) == 1)
		out_be32(&psc_dma->psc_regs->ac97_slots, 0x01000000);
	अन्यथा
		out_be32(&psc_dma->psc_regs->ac97_slots, 0x03000000);

	वापस 0;
पूर्ण

अटल पूर्णांक psc_ac97_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
							काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(dai);
	काष्ठा psc_dma_stream *s = to_psc_dma_stream(substream, psc_dma);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dev_dbg(psc_dma->dev, "AC97 START: stream=%i\n",
			substream->pstr->stream);

		/* Set the slot enable bits */
		psc_dma->slots |= s->ac97_slot_bits;
		out_be32(&psc_dma->psc_regs->ac97_slots, psc_dma->slots);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(psc_dma->dev, "AC97 STOP: stream=%i\n",
			substream->pstr->stream);

		/* Clear the slot enable bits */
		psc_dma->slots &= ~(s->ac97_slot_bits);
		out_be32(&psc_dma->psc_regs->ac97_slots, psc_dma->slots);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक psc_ac97_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा mpc52xx_psc __iomem *regs = psc_dma->psc_regs;

	/* Go */
	out_8(&regs->command, MPC52xx_PSC_TX_ENABLE | MPC52xx_PSC_RX_ENABLE);
	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------
 * ALSA SoC Bindings
 *
 * - Digital Audio Interface (DAI) ढाँचा
 * - create/destroy dai hooks
 */

/**
 * psc_ac97_dai_ढाँचा: ढाँचा CPU Digital Audio Interface
 */
अटल स्थिर काष्ठा snd_soc_dai_ops psc_ac97_analog_ops = अणु
	.hw_params	= psc_ac97_hw_analog_params,
	.trigger	= psc_ac97_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops psc_ac97_digital_ops = अणु
	.hw_params	= psc_ac97_hw_digital_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver psc_ac97_dai[] = अणु
अणु
	.name = "mpc5200-psc-ac97.0",
	.probe	= psc_ac97_probe,
	.playback = अणु
		.stream_name	= "AC97 Playback",
		.channels_min   = 1,
		.channels_max   = 6,
		.rates          = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_BE,
	पूर्ण,
	.capture = अणु
		.stream_name	= "AC97 Capture",
		.channels_min   = 1,
		.channels_max   = 2,
		.rates          = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_BE,
	पूर्ण,
	.ops = &psc_ac97_analog_ops,
पूर्ण,
अणु
	.name = "mpc5200-psc-ac97.1",
	.playback = अणु
		.stream_name	= "AC97 SPDIF",
		.channels_min   = 1,
		.channels_max   = 2,
		.rates          = SNDRV_PCM_RATE_32000 | \
			SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_BE,
	पूर्ण,
	.ops = &psc_ac97_digital_ops,
पूर्ण पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver psc_ac97_component = अणु
	.name		= DRV_NAME,
पूर्ण;


/* ---------------------------------------------------------------------
 * OF platक्रमm bus binding code:
 * - Probe/हटाओ operations
 * - OF device match table
 */
अटल पूर्णांक psc_ac97_of_probe(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक rc;
	काष्ठा mpc52xx_psc __iomem *regs;

	rc = mpc5200_audio_dma_create(op);
	अगर (rc != 0)
		वापस rc;

	rc = snd_soc_set_ac97_ops(&psc_ac97_ops);
	अगर (rc != 0) अणु
		dev_err(&op->dev, "Failed to set AC'97 ops: %d\n", rc);
		वापस rc;
	पूर्ण

	rc = snd_soc_रेजिस्टर_component(&op->dev, &psc_ac97_component,
					psc_ac97_dai, ARRAY_SIZE(psc_ac97_dai));
	अगर (rc != 0) अणु
		dev_err(&op->dev, "Failed to register DAI\n");
		वापस rc;
	पूर्ण

	psc_dma = dev_get_drvdata(&op->dev);
	regs = psc_dma->psc_regs;

	psc_dma->imr = 0;
	out_be16(&psc_dma->psc_regs->isr_imr.imr, psc_dma->imr);

	/* Configure the serial पूर्णांकerface mode to AC97 */
	psc_dma->sicr = MPC52xx_PSC_SICR_SIM_AC97 | MPC52xx_PSC_SICR_ENAC97;
	out_be32(&regs->sicr, psc_dma->sicr);

	/* No slots active */
	out_be32(&regs->ac97_slots, 0x00000000);

	वापस 0;
पूर्ण

अटल पूर्णांक psc_ac97_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	mpc5200_audio_dma_destroy(op);
	snd_soc_unरेजिस्टर_component(&op->dev);
	snd_soc_set_ac97_ops(शून्य);
	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id psc_ac97_match[] = अणु
	अणु .compatible = "fsl,mpc5200-psc-ac97", पूर्ण,
	अणु .compatible = "fsl,mpc5200b-psc-ac97", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, psc_ac97_match);

अटल काष्ठा platक्रमm_driver psc_ac97_driver = अणु
	.probe = psc_ac97_of_probe,
	.हटाओ = psc_ac97_of_हटाओ,
	.driver = अणु
		.name = "mpc5200-psc-ac97",
		.of_match_table = psc_ac97_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(psc_ac97_driver);

MODULE_AUTHOR("Jon Smirl <jonsmirl@gmail.com>");
MODULE_DESCRIPTION("mpc5200 AC97 module");
MODULE_LICENSE("GPL");

