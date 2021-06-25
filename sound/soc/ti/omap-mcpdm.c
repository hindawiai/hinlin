<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap-mcpdm.c  --  OMAP ALSA SoC DAI driver using McPDM port
 *
 * Copyright (C) 2009 - 2011 Texas Instruments
 *
 * Author: Misael Lopez Cruz <misael.lopez@ti.com>
 * Contact: Jorge Eduarकरो Candelaria <x0107209@ti.com>
 *          Margarita Olaya <magi.olaya@ti.com>
 *          Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "omap-mcpdm.h"
#समावेश "sdma-pcm.h"

काष्ठा mcpdm_link_config अणु
	u32 link_mask; /* channel mask क्रम the direction */
	u32 threshold; /* FIFO threshold */
पूर्ण;

काष्ठा omap_mcpdm अणु
	काष्ठा device *dev;
	अचिन्हित दीर्घ phys_base;
	व्योम __iomem *io_base;
	पूर्णांक irq;
	काष्ठा pm_qos_request pm_qos_req;
	पूर्णांक latency[2];

	काष्ठा mutex mutex;

	/* Playback/Capture configuration */
	काष्ठा mcpdm_link_config config[2];

	/* McPDM dn offsets क्रम rx1, and 2 channels */
	u32 dn_rx_offset;

	/* McPDM needs to be restarted due to runसमय reconfiguration */
	bool restart;

	/* pm state क्रम suspend/resume handling */
	पूर्णांक pm_active_count;

	काष्ठा snd_dmaengine_dai_dma_data dma_data[2];
पूर्ण;

/*
 * Stream DMA parameters
 */

अटल अंतरभूत व्योम omap_mcpdm_ग_लिखो(काष्ठा omap_mcpdm *mcpdm, u16 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, mcpdm->io_base + reg);
पूर्ण

अटल अंतरभूत पूर्णांक omap_mcpdm_पढ़ो(काष्ठा omap_mcpdm *mcpdm, u16 reg)
अणु
	वापस पढ़ोl_relaxed(mcpdm->io_base + reg);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम omap_mcpdm_reg_dump(काष्ठा omap_mcpdm *mcpdm)
अणु
	dev_dbg(mcpdm->dev, "***********************\n");
	dev_dbg(mcpdm->dev, "IRQSTATUS_RAW:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_IRQSTATUS_RAW));
	dev_dbg(mcpdm->dev, "IRQSTATUS:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_IRQSTATUS));
	dev_dbg(mcpdm->dev, "IRQENABLE_SET:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_IRQENABLE_SET));
	dev_dbg(mcpdm->dev, "IRQENABLE_CLR:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_IRQENABLE_CLR));
	dev_dbg(mcpdm->dev, "IRQWAKE_EN: 0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_IRQWAKE_EN));
	dev_dbg(mcpdm->dev, "DMAENABLE_SET: 0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_DMAENABLE_SET));
	dev_dbg(mcpdm->dev, "DMAENABLE_CLR:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_DMAENABLE_CLR));
	dev_dbg(mcpdm->dev, "DMAWAKEEN:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_DMAWAKEEN));
	dev_dbg(mcpdm->dev, "CTRL:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_CTRL));
	dev_dbg(mcpdm->dev, "DN_DATA:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_DN_DATA));
	dev_dbg(mcpdm->dev, "UP_DATA: 0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_UP_DATA));
	dev_dbg(mcpdm->dev, "FIFO_CTRL_DN: 0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_FIFO_CTRL_DN));
	dev_dbg(mcpdm->dev, "FIFO_CTRL_UP:  0x%04x\n",
			omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_FIFO_CTRL_UP));
	dev_dbg(mcpdm->dev, "***********************\n");
पूर्ण
#अन्यथा
अटल व्योम omap_mcpdm_reg_dump(काष्ठा omap_mcpdm *mcpdm) अणुपूर्ण
#पूर्ण_अगर

/*
 * Enables the transfer through the PDM पूर्णांकerface to/from the Phoenix
 * codec by enabling the corresponding UP or DN channels.
 */
अटल व्योम omap_mcpdm_start(काष्ठा omap_mcpdm *mcpdm)
अणु
	u32 ctrl = omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_CTRL);
	u32 link_mask = mcpdm->config[0].link_mask | mcpdm->config[1].link_mask;

	ctrl |= (MCPDM_SW_DN_RST | MCPDM_SW_UP_RST);
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, ctrl);

	ctrl |= link_mask;
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, ctrl);

	ctrl &= ~(MCPDM_SW_DN_RST | MCPDM_SW_UP_RST);
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, ctrl);
पूर्ण

/*
 * Disables the transfer through the PDM पूर्णांकerface to/from the Phoenix
 * codec by disabling the corresponding UP or DN channels.
 */
अटल व्योम omap_mcpdm_stop(काष्ठा omap_mcpdm *mcpdm)
अणु
	u32 ctrl = omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_CTRL);
	u32 link_mask = MCPDM_PDM_DN_MASK | MCPDM_PDM_UP_MASK;

	ctrl |= (MCPDM_SW_DN_RST | MCPDM_SW_UP_RST);
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, ctrl);

	ctrl &= ~(link_mask);
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, ctrl);

	ctrl &= ~(MCPDM_SW_DN_RST | MCPDM_SW_UP_RST);
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, ctrl);

पूर्ण

/*
 * Is the physical McPDM पूर्णांकerface active.
 */
अटल अंतरभूत पूर्णांक omap_mcpdm_active(काष्ठा omap_mcpdm *mcpdm)
अणु
	वापस omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_CTRL) &
					(MCPDM_PDM_DN_MASK | MCPDM_PDM_UP_MASK);
पूर्ण

/*
 * Configures McPDM uplink, and करोwnlink क्रम audio.
 * This function should be called beक्रमe omap_mcpdm_start.
 */
अटल व्योम omap_mcpdm_खोलो_streams(काष्ठा omap_mcpdm *mcpdm)
अणु
	u32 ctrl = omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_CTRL);

	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, ctrl | MCPDM_WD_EN);

	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_IRQENABLE_SET,
			MCPDM_DN_IRQ_EMPTY | MCPDM_DN_IRQ_FULL |
			MCPDM_UP_IRQ_EMPTY | MCPDM_UP_IRQ_FULL);

	/* Enable DN RX1/2 offset cancellation feature, अगर configured */
	अगर (mcpdm->dn_rx_offset) अणु
		u32 dn_offset = mcpdm->dn_rx_offset;

		omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_DN_OFFSET, dn_offset);
		dn_offset |= (MCPDM_DN_OFST_RX1_EN | MCPDM_DN_OFST_RX2_EN);
		omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_DN_OFFSET, dn_offset);
	पूर्ण

	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_FIFO_CTRL_DN,
			 mcpdm->config[SNDRV_PCM_STREAM_PLAYBACK].threshold);
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_FIFO_CTRL_UP,
			 mcpdm->config[SNDRV_PCM_STREAM_CAPTURE].threshold);

	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_DMAENABLE_SET,
			MCPDM_DMA_DN_ENABLE | MCPDM_DMA_UP_ENABLE);
पूर्ण

/*
 * Cleans McPDM uplink, and करोwnlink configuration.
 * This function should be called when the stream is बंदd.
 */
अटल व्योम omap_mcpdm_बंद_streams(काष्ठा omap_mcpdm *mcpdm)
अणु
	/* Disable irq request generation क्रम करोwnlink */
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_IRQENABLE_CLR,
			MCPDM_DN_IRQ_EMPTY | MCPDM_DN_IRQ_FULL);

	/* Disable DMA request generation क्रम करोwnlink */
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_DMAENABLE_CLR, MCPDM_DMA_DN_ENABLE);

	/* Disable irq request generation क्रम uplink */
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_IRQENABLE_CLR,
			MCPDM_UP_IRQ_EMPTY | MCPDM_UP_IRQ_FULL);

	/* Disable DMA request generation क्रम uplink */
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_DMAENABLE_CLR, MCPDM_DMA_UP_ENABLE);

	/* Disable RX1/2 offset cancellation */
	अगर (mcpdm->dn_rx_offset)
		omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_DN_OFFSET, 0);
पूर्ण

अटल irqवापस_t omap_mcpdm_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_mcpdm *mcpdm = dev_id;
	पूर्णांक irq_status;

	irq_status = omap_mcpdm_पढ़ो(mcpdm, MCPDM_REG_IRQSTATUS);

	/* Acknowledge irq event */
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_IRQSTATUS, irq_status);

	अगर (irq_status & MCPDM_DN_IRQ_FULL)
		dev_dbg(mcpdm->dev, "DN (playback) FIFO Full\n");

	अगर (irq_status & MCPDM_DN_IRQ_EMPTY)
		dev_dbg(mcpdm->dev, "DN (playback) FIFO Empty\n");

	अगर (irq_status & MCPDM_DN_IRQ)
		dev_dbg(mcpdm->dev, "DN (playback) write request\n");

	अगर (irq_status & MCPDM_UP_IRQ_FULL)
		dev_dbg(mcpdm->dev, "UP (capture) FIFO Full\n");

	अगर (irq_status & MCPDM_UP_IRQ_EMPTY)
		dev_dbg(mcpdm->dev, "UP (capture) FIFO Empty\n");

	अगर (irq_status & MCPDM_UP_IRQ)
		dev_dbg(mcpdm->dev, "UP (capture) write request\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक omap_mcpdm_dai_startup(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);

	mutex_lock(&mcpdm->mutex);

	अगर (!snd_soc_dai_active(dai))
		omap_mcpdm_खोलो_streams(mcpdm);

	mutex_unlock(&mcpdm->mutex);

	वापस 0;
पूर्ण

अटल व्योम omap_mcpdm_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);
	पूर्णांक tx = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	पूर्णांक stream1 = tx ? SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
	पूर्णांक stream2 = tx ? SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;

	mutex_lock(&mcpdm->mutex);

	अगर (!snd_soc_dai_active(dai)) अणु
		अगर (omap_mcpdm_active(mcpdm)) अणु
			omap_mcpdm_stop(mcpdm);
			omap_mcpdm_बंद_streams(mcpdm);
			mcpdm->config[0].link_mask = 0;
			mcpdm->config[1].link_mask = 0;
		पूर्ण
	पूर्ण

	अगर (mcpdm->latency[stream2])
		cpu_latency_qos_update_request(&mcpdm->pm_qos_req,
					       mcpdm->latency[stream2]);
	अन्यथा अगर (mcpdm->latency[stream1])
		cpu_latency_qos_हटाओ_request(&mcpdm->pm_qos_req);

	mcpdm->latency[stream1] = 0;

	mutex_unlock(&mcpdm->mutex);
पूर्ण

अटल पूर्णांक omap_mcpdm_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);
	पूर्णांक stream = substream->stream;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	u32 threshold;
	पूर्णांक channels, latency;
	पूर्णांक link_mask = 0;

	channels = params_channels(params);
	चयन (channels) अणु
	हाल 5:
		अगर (stream == SNDRV_PCM_STREAM_CAPTURE)
			/* up to 3 channels क्रम capture */
			वापस -EINVAL;
		link_mask |= 1 << 4;
		fallthrough;
	हाल 4:
		अगर (stream == SNDRV_PCM_STREAM_CAPTURE)
			/* up to 3 channels क्रम capture */
			वापस -EINVAL;
		link_mask |= 1 << 3;
		fallthrough;
	हाल 3:
		link_mask |= 1 << 2;
		fallthrough;
	हाल 2:
		link_mask |= 1 << 1;
		fallthrough;
	हाल 1:
		link_mask |= 1 << 0;
		अवरोध;
	शेष:
		/* unsupported number of channels */
		वापस -EINVAL;
	पूर्ण

	dma_data = snd_soc_dai_get_dma_data(dai, substream);

	threshold = mcpdm->config[stream].threshold;
	/* Configure McPDM channels, and DMA packet size */
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		link_mask <<= 3;

		/* If capture is not running assume a stereo stream to come */
		अगर (!mcpdm->config[!stream].link_mask)
			mcpdm->config[!stream].link_mask = 0x3;

		dma_data->maxburst =
				(MCPDM_DN_THRES_MAX - threshold) * channels;
		latency = threshold;
	पूर्ण अन्यथा अणु
		/* If playback is not running assume a stereo stream to come */
		अगर (!mcpdm->config[!stream].link_mask)
			mcpdm->config[!stream].link_mask = (0x3 << 3);

		dma_data->maxburst = threshold * channels;
		latency = (MCPDM_DN_THRES_MAX - threshold);
	पूर्ण

	/*
	 * The DMA must act to a DMA request within latency समय (usec) to aव्योम
	 * under/overflow
	 */
	mcpdm->latency[stream] = latency * USEC_PER_SEC / params_rate(params);

	अगर (!mcpdm->latency[stream])
		mcpdm->latency[stream] = 10;

	/* Check अगर we need to restart McPDM with this stream */
	अगर (mcpdm->config[stream].link_mask &&
	    mcpdm->config[stream].link_mask != link_mask)
		mcpdm->restart = true;

	mcpdm->config[stream].link_mask = link_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcpdm_prepare(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);
	काष्ठा pm_qos_request *pm_qos_req = &mcpdm->pm_qos_req;
	पूर्णांक tx = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	पूर्णांक stream1 = tx ? SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
	पूर्णांक stream2 = tx ? SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक latency = mcpdm->latency[stream2];

	/* Prevent omap hardware from hitting off between FIFO fills */
	अगर (!latency || mcpdm->latency[stream1] < latency)
		latency = mcpdm->latency[stream1];

	अगर (cpu_latency_qos_request_active(pm_qos_req))
		cpu_latency_qos_update_request(pm_qos_req, latency);
	अन्यथा अगर (latency)
		cpu_latency_qos_add_request(pm_qos_req, latency);

	अगर (!omap_mcpdm_active(mcpdm)) अणु
		omap_mcpdm_start(mcpdm);
		omap_mcpdm_reg_dump(mcpdm);
	पूर्ण अन्यथा अगर (mcpdm->restart) अणु
		omap_mcpdm_stop(mcpdm);
		omap_mcpdm_start(mcpdm);
		mcpdm->restart = false;
		omap_mcpdm_reg_dump(mcpdm);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops omap_mcpdm_dai_ops = अणु
	.startup	= omap_mcpdm_dai_startup,
	.shutकरोwn	= omap_mcpdm_dai_shutकरोwn,
	.hw_params	= omap_mcpdm_dai_hw_params,
	.prepare	= omap_mcpdm_prepare,
पूर्ण;

अटल पूर्णांक omap_mcpdm_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	pm_runसमय_enable(mcpdm->dev);

	/* Disable lines जबतक request is ongoing */
	pm_runसमय_get_sync(mcpdm->dev);
	omap_mcpdm_ग_लिखो(mcpdm, MCPDM_REG_CTRL, 0x00);

	ret = request_irq(mcpdm->irq, omap_mcpdm_irq_handler, 0, "McPDM",
			  (व्योम *)mcpdm);

	pm_runसमय_put_sync(mcpdm->dev);

	अगर (ret) अणु
		dev_err(mcpdm->dev, "Request for IRQ failed\n");
		pm_runसमय_disable(mcpdm->dev);
	पूर्ण

	/* Configure McPDM threshold values */
	mcpdm->config[SNDRV_PCM_STREAM_PLAYBACK].threshold = 2;
	mcpdm->config[SNDRV_PCM_STREAM_CAPTURE].threshold =
							MCPDM_UP_THRES_MAX - 3;

	snd_soc_dai_init_dma_data(dai,
				  &mcpdm->dma_data[SNDRV_PCM_STREAM_PLAYBACK],
				  &mcpdm->dma_data[SNDRV_PCM_STREAM_CAPTURE]);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_mcpdm_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);

	मुक्त_irq(mcpdm->irq, (व्योम *)mcpdm);
	pm_runसमय_disable(mcpdm->dev);

	अगर (cpu_latency_qos_request_active(&mcpdm->pm_qos_req))
		cpu_latency_qos_हटाओ_request(&mcpdm->pm_qos_req);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_mcpdm_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_component_get_drvdata(component);

	अगर (snd_soc_component_active(component)) अणु
		omap_mcpdm_stop(mcpdm);
		omap_mcpdm_बंद_streams(mcpdm);
	पूर्ण

	mcpdm->pm_active_count = 0;
	जबतक (pm_runसमय_active(mcpdm->dev)) अणु
		pm_runसमय_put_sync(mcpdm->dev);
		mcpdm->pm_active_count++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcpdm_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_component_get_drvdata(component);

	अगर (mcpdm->pm_active_count) अणु
		जबतक (mcpdm->pm_active_count--)
			pm_runसमय_get_sync(mcpdm->dev);

		अगर (snd_soc_component_active(component)) अणु
			omap_mcpdm_खोलो_streams(mcpdm);
			omap_mcpdm_start(mcpdm);
		पूर्ण
	पूर्ण


	वापस 0;
पूर्ण
#अन्यथा
#घोषणा omap_mcpdm_suspend शून्य
#घोषणा omap_mcpdm_resume शून्य
#पूर्ण_अगर

#घोषणा OMAP_MCPDM_RATES	(SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)
#घोषणा OMAP_MCPDM_FORMATS	SNDRV_PCM_FMTBIT_S32_LE

अटल काष्ठा snd_soc_dai_driver omap_mcpdm_dai = अणु
	.probe = omap_mcpdm_probe,
	.हटाओ = omap_mcpdm_हटाओ,
	.probe_order = SND_SOC_COMP_ORDER_LATE,
	.हटाओ_order = SND_SOC_COMP_ORDER_EARLY,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 5,
		.rates = OMAP_MCPDM_RATES,
		.क्रमmats = OMAP_MCPDM_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 3,
		.rates = OMAP_MCPDM_RATES,
		.क्रमmats = OMAP_MCPDM_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.ops = &omap_mcpdm_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver omap_mcpdm_component = अणु
	.name		= "omap-mcpdm",
	.suspend	= omap_mcpdm_suspend,
	.resume		= omap_mcpdm_resume,
पूर्ण;

व्योम omap_mcpdm_configure_dn_offsets(काष्ठा snd_soc_pcm_runसमय *rtd,
				    u8 rx1, u8 rx2)
अणु
	काष्ठा omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	mcpdm->dn_rx_offset = MCPDM_DNOFST_RX1(rx1) | MCPDM_DNOFST_RX2(rx2);
पूर्ण
EXPORT_SYMBOL_GPL(omap_mcpdm_configure_dn_offsets);

अटल पूर्णांक asoc_mcpdm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mcpdm *mcpdm;
	काष्ठा resource *res;
	पूर्णांक ret;

	mcpdm = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_mcpdm), GFP_KERNEL);
	अगर (!mcpdm)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mcpdm);

	mutex_init(&mcpdm->mutex);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dma");
	अगर (res == शून्य)
		वापस -ENOMEM;

	mcpdm->dma_data[0].addr = res->start + MCPDM_REG_DN_DATA;
	mcpdm->dma_data[1].addr = res->start + MCPDM_REG_UP_DATA;

	mcpdm->dma_data[0].filter_data = "dn_link";
	mcpdm->dma_data[1].filter_data = "up_link";

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mpu");
	mcpdm->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mcpdm->io_base))
		वापस PTR_ERR(mcpdm->io_base);

	mcpdm->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mcpdm->irq < 0)
		वापस mcpdm->irq;

	mcpdm->dev = &pdev->dev;

	ret =  devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					       &omap_mcpdm_component,
					       &omap_mcpdm_dai, 1);
	अगर (ret)
		वापस ret;

	वापस sdma_pcm_platक्रमm_रेजिस्टर(&pdev->dev, "dn_link", "up_link");
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_mcpdm_of_match[] = अणु
	अणु .compatible = "ti,omap4-mcpdm", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_mcpdm_of_match);

अटल काष्ठा platक्रमm_driver asoc_mcpdm_driver = अणु
	.driver = अणु
		.name	= "omap-mcpdm",
		.of_match_table = omap_mcpdm_of_match,
	पूर्ण,

	.probe	= asoc_mcpdm_probe,
पूर्ण;

module_platक्रमm_driver(asoc_mcpdm_driver);

MODULE_ALIAS("platform:omap-mcpdm");
MODULE_AUTHOR("Misael Lopez Cruz <misael.lopez@ti.com>");
MODULE_DESCRIPTION("OMAP PDM SoC Interface");
MODULE_LICENSE("GPL");
