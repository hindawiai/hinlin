<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Arnaud Pouliquen <arnaud.pouliquen@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/delay.h>

#समावेश "uniperif.h"

/*
 * User frame size shall be 2, 4, 6 or 8 32-bits words length
 * (i.e. 8, 16, 24 or 32 bytes)
 * This स्थिरraपूर्णांक comes from allowed values क्रम
 * UNIPERIF_I2S_FMT_NUM_CH रेजिस्टर
 */
#घोषणा UNIPERIF_MAX_FRAME_SZ 0x20
#घोषणा UNIPERIF_ALLOWED_FRAME_SZ (0x08 | 0x10 | 0x18 | UNIPERIF_MAX_FRAME_SZ)

काष्ठा sti_uniperiph_dev_data अणु
	अचिन्हित पूर्णांक id; /* Nb available player instances */
	अचिन्हित पूर्णांक version; /* player IP version */
	अचिन्हित पूर्णांक stream;
	स्थिर अक्षर *dai_names;
	क्रमागत uniperअगर_type type;
पूर्ण;

अटल स्थिर काष्ठा sti_uniperiph_dev_data sti_uniplayer_hdmi = अणु
	.id = 0,
	.version = SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0,
	.stream = SNDRV_PCM_STREAM_PLAYBACK,
	.dai_names = "Uni Player #0 (HDMI)",
	.type = SND_ST_UNIPERIF_TYPE_HDMI
पूर्ण;

अटल स्थिर काष्ठा sti_uniperiph_dev_data sti_uniplayer_pcm_out = अणु
	.id = 1,
	.version = SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0,
	.stream = SNDRV_PCM_STREAM_PLAYBACK,
	.dai_names = "Uni Player #1 (PCM OUT)",
	.type = SND_ST_UNIPERIF_TYPE_PCM | SND_ST_UNIPERIF_TYPE_TDM,
पूर्ण;

अटल स्थिर काष्ठा sti_uniperiph_dev_data sti_uniplayer_dac = अणु
	.id = 2,
	.version = SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0,
	.stream = SNDRV_PCM_STREAM_PLAYBACK,
	.dai_names = "Uni Player #2 (DAC)",
	.type = SND_ST_UNIPERIF_TYPE_PCM,
पूर्ण;

अटल स्थिर काष्ठा sti_uniperiph_dev_data sti_uniplayer_spdअगर = अणु
	.id = 3,
	.version = SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0,
	.stream = SNDRV_PCM_STREAM_PLAYBACK,
	.dai_names = "Uni Player #3 (SPDIF)",
	.type = SND_ST_UNIPERIF_TYPE_SPDIF
पूर्ण;

अटल स्थिर काष्ठा sti_uniperiph_dev_data sti_uniपढ़ोer_pcm_in = अणु
	.id = 0,
	.version = SND_ST_UNIPERIF_VERSION_UNI_RDR_1_0,
	.stream = SNDRV_PCM_STREAM_CAPTURE,
	.dai_names = "Uni Reader #0 (PCM IN)",
	.type = SND_ST_UNIPERIF_TYPE_PCM | SND_ST_UNIPERIF_TYPE_TDM,
पूर्ण;

अटल स्थिर काष्ठा sti_uniperiph_dev_data sti_uniपढ़ोer_hdmi_in = अणु
	.id = 1,
	.version = SND_ST_UNIPERIF_VERSION_UNI_RDR_1_0,
	.stream = SNDRV_PCM_STREAM_CAPTURE,
	.dai_names = "Uni Reader #1 (HDMI IN)",
	.type = SND_ST_UNIPERIF_TYPE_PCM,
पूर्ण;

अटल स्थिर काष्ठा of_device_id snd_soc_sti_match[] = अणु
	अणु .compatible = "st,stih407-uni-player-hdmi",
	  .data = &sti_uniplayer_hdmi
	पूर्ण,
	अणु .compatible = "st,stih407-uni-player-pcm-out",
	  .data = &sti_uniplayer_pcm_out
	पूर्ण,
	अणु .compatible = "st,stih407-uni-player-dac",
	  .data = &sti_uniplayer_dac
	पूर्ण,
	अणु .compatible = "st,stih407-uni-player-spdif",
	  .data = &sti_uniplayer_spdअगर
	पूर्ण,
	अणु .compatible = "st,stih407-uni-reader-pcm_in",
	  .data = &sti_uniपढ़ोer_pcm_in
	पूर्ण,
	अणु .compatible = "st,stih407-uni-reader-hdmi",
	  .data = &sti_uniपढ़ोer_hdmi_in
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, snd_soc_sti_match);

पूर्णांक  sti_uniperiph_reset(काष्ठा uniperअगर *uni)
अणु
	पूर्णांक count = 10;

	/* Reset uniperipheral uni */
	SET_UNIPERIF_SOFT_RST_SOFT_RST(uni);

	अगर (uni->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0) अणु
		जबतक (GET_UNIPERIF_SOFT_RST_SOFT_RST(uni) && count) अणु
			udelay(5);
			count--;
		पूर्ण
	पूर्ण

	अगर (!count) अणु
		dev_err(uni->dev, "Failed to reset uniperif\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sti_uniperiph_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			       अचिन्हित पूर्णांक rx_mask, पूर्णांक slots,
			       पूर्णांक slot_width)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *uni = priv->dai_data.uni;
	पूर्णांक i, frame_size, avail_slots;

	अगर (!UNIPERIF_TYPE_IS_TDM(uni)) अणु
		dev_err(uni->dev, "cpu dai not in tdm mode\n");
		वापस -EINVAL;
	पूर्ण

	/* store info in unip context */
	uni->tdm_slot.slots = slots;
	uni->tdm_slot.slot_width = slot_width;
	/* unip is unidirectionnal */
	uni->tdm_slot.mask = (tx_mask != 0) ? tx_mask : rx_mask;

	/* number of available बारlots */
	क्रम (i = 0, avail_slots = 0; i < uni->tdm_slot.slots; i++) अणु
		अगर ((uni->tdm_slot.mask >> i) & 0x01)
			avail_slots++;
	पूर्ण
	uni->tdm_slot.avail_slots = avail_slots;

	/* frame size in bytes */
	frame_size = uni->tdm_slot.avail_slots * uni->tdm_slot.slot_width / 8;

	/* check frame size is allowed */
	अगर ((frame_size > UNIPERIF_MAX_FRAME_SZ) ||
	    (frame_size & ~(पूर्णांक)UNIPERIF_ALLOWED_FRAME_SZ)) अणु
		dev_err(uni->dev, "frame size not allowed: %d bytes\n",
			frame_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sti_uniperiph_fix_tdm_chan(काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा uniperअगर *uni = rule->निजी;
	काष्ठा snd_पूर्णांकerval t;

	t.min = uni->tdm_slot.avail_slots;
	t.max = uni->tdm_slot.avail_slots;
	t.खोलोmin = 0;
	t.खोलोmax = 0;
	t.पूर्णांकeger = 0;

	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

पूर्णांक sti_uniperiph_fix_tdm_क्रमmat(काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा uniperअगर *uni = rule->निजी;
	काष्ठा snd_mask *maskp = hw_param_mask(params, rule->var);
	u64 क्रमmat;

	चयन (uni->tdm_slot.slot_width) अणु
	हाल 16:
		क्रमmat = SNDRV_PCM_FMTBIT_S16_LE;
		अवरोध;
	हाल 32:
		क्रमmat = SNDRV_PCM_FMTBIT_S32_LE;
		अवरोध;
	शेष:
		dev_err(uni->dev, "format not supported: %d bits\n",
			uni->tdm_slot.slot_width);
		वापस -EINVAL;
	पूर्ण

	maskp->bits[0] &= (u_पूर्णांक32_t)क्रमmat;
	maskp->bits[1] &= (u_पूर्णांक32_t)(क्रमmat >> 32);
	/* clear reमुख्यing indexes */
	स_रखो(maskp->bits + 2, 0, (SNDRV_MASK_MAX - 64) / 8);

	अगर (!maskp->bits[0] && !maskp->bits[1])
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक sti_uniperiph_get_tdm_word_pos(काष्ठा uniperअगर *uni,
				   अचिन्हित पूर्णांक *word_pos)
अणु
	पूर्णांक slot_width = uni->tdm_slot.slot_width / 8;
	पूर्णांक slots_num = uni->tdm_slot.slots;
	अचिन्हित पूर्णांक slots_mask = uni->tdm_slot.mask;
	पूर्णांक i, j, k;
	अचिन्हित पूर्णांक word16_pos[4];

	/* word16_pos:
	 * word16_pos[0] = WORDX_LSB
	 * word16_pos[1] = WORDX_MSB,
	 * word16_pos[2] = WORDX+1_LSB
	 * word16_pos[3] = WORDX+1_MSB
	 */

	/* set unip word position */
	क्रम (i = 0, j = 0, k = 0; (i < slots_num) && (k < WORD_MAX); i++) अणु
		अगर ((slots_mask >> i) & 0x01) अणु
			word16_pos[j] = i * slot_width;

			अगर (slot_width == 4) अणु
				word16_pos[j + 1] = word16_pos[j] + 2;
				j++;
			पूर्ण
			j++;

			अगर (j > 3) अणु
				word_pos[k] = word16_pos[1] |
					      (word16_pos[0] << 8) |
					      (word16_pos[3] << 16) |
					      (word16_pos[2] << 24);
				j = 0;
				k++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * sti_uniperiph_dai_create_ctrl
 * This function is used to create Ctrl associated to DAI but also pcm device.
 * Request is करोne by front end to associate ctrl with pcm device id
 */
अटल पूर्णांक sti_uniperiph_dai_create_ctrl(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *uni = priv->dai_data.uni;
	काष्ठा snd_kcontrol_new *ctrl;
	पूर्णांक i;

	अगर (!uni->num_ctrls)
		वापस 0;

	क्रम (i = 0; i < uni->num_ctrls; i++) अणु
		/*
		 * Several Control can have same name. Controls are indexed on
		 * Uniperipheral instance ID
		 */
		ctrl = &uni->snd_ctrls[i];
		ctrl->index = uni->id;
		ctrl->device = uni->id;
	पूर्ण

	वापस snd_soc_add_dai_controls(dai, uni->snd_ctrls, uni->num_ctrls);
पूर्ण

/*
 * DAI
 */
पूर्णांक sti_uniperiph_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *uni = priv->dai_data.uni;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	पूर्णांक transfer_size;

	अगर (uni->type == SND_ST_UNIPERIF_TYPE_TDM)
		/* transfer size = user frame size (in 32-bits FIFO cell) */
		transfer_size = snd_soc_params_to_frame_size(params) / 32;
	अन्यथा
		transfer_size = params_channels(params) * UNIPERIF_FIFO_FRAMES;

	dma_data = snd_soc_dai_get_dma_data(dai, substream);
	dma_data->maxburst = transfer_size;

	वापस 0;
पूर्ण

पूर्णांक sti_uniperiph_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);

	priv->dai_data.uni->daअगरmt = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक sti_uniperiph_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा uniperअगर *uni = priv->dai_data.uni;
	पूर्णांक ret;

	/* The uniperipheral should be in stopped state */
	अगर (uni->state != UNIPERIF_STATE_STOPPED) अणु
		dev_err(uni->dev, "%s: invalid uni state( %d)\n",
			__func__, (पूर्णांक)uni->state);
		वापस -EBUSY;
	पूर्ण

	/* Pinctrl: चयन pinstate to sleep */
	ret = pinctrl_pm_select_sleep_state(uni->dev);
	अगर (ret)
		dev_err(uni->dev, "%s: failed to select pinctrl state\n",
			__func__);

	वापस ret;
पूर्ण

अटल पूर्णांक sti_uniperiph_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा uniperअगर *uni = priv->dai_data.uni;
	पूर्णांक ret;

	अगर (priv->dai_data.stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = uni_player_resume(uni);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* pinctrl: चयन pinstate to शेष */
	ret = pinctrl_pm_select_शेष_state(uni->dev);
	अगर (ret)
		dev_err(uni->dev, "%s: failed to select pinctrl state\n",
			__func__);

	वापस ret;
पूर्ण

अटल पूर्णांक sti_uniperiph_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा sti_uniperiph_dai *dai_data = &priv->dai_data;

	/* DMA settings*/
	अगर (priv->dai_data.stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dai_init_dma_data(dai, &dai_data->dma_data, शून्य);
	अन्यथा
		snd_soc_dai_init_dma_data(dai, शून्य, &dai_data->dma_data);

	dai_data->dma_data.addr = dai_data->uni->fअगरo_phys_address;
	dai_data->dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	वापस sti_uniperiph_dai_create_ctrl(dai);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_driver sti_uniperiph_dai_ढाँचा = अणु
	.probe = sti_uniperiph_dai_probe,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sti_uniperiph_dai_component = अणु
	.name = "sti_cpu_dai",
	.suspend = sti_uniperiph_suspend,
	.resume = sti_uniperiph_resume
पूर्ण;

अटल पूर्णांक sti_uniperiph_cpu_dai_of(काष्ठा device_node *node,
				    काष्ठा sti_uniperiph_data *priv)
अणु
	काष्ठा device *dev = &priv->pdev->dev;
	काष्ठा sti_uniperiph_dai *dai_data = &priv->dai_data;
	काष्ठा snd_soc_dai_driver *dai = priv->dai;
	काष्ठा snd_soc_pcm_stream *stream;
	काष्ठा uniperअगर *uni;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा sti_uniperiph_dev_data *dev_data;
	स्थिर अक्षर *mode;
	पूर्णांक ret;

	/* Populate data काष्ठाure depending on compatibility */
	of_id = of_match_node(snd_soc_sti_match, node);
	अगर (!of_id->data) अणु
		dev_err(dev, "data associated to device is missing\n");
		वापस -EINVAL;
	पूर्ण
	dev_data = (काष्ठा sti_uniperiph_dev_data *)of_id->data;

	uni = devm_kzalloc(dev, माप(*uni), GFP_KERNEL);
	अगर (!uni)
		वापस -ENOMEM;

	uni->id = dev_data->id;
	uni->ver = dev_data->version;

	*dai = sti_uniperiph_dai_ढाँचा;
	dai->name = dev_data->dai_names;

	/* Get resources */
	uni->mem_region = platक्रमm_get_resource(priv->pdev, IORESOURCE_MEM, 0);

	अगर (!uni->mem_region) अणु
		dev_err(dev, "Failed to get memory resource\n");
		वापस -ENODEV;
	पूर्ण

	uni->base = devm_ioremap_resource(dev, uni->mem_region);

	अगर (IS_ERR(uni->base))
		वापस PTR_ERR(uni->base);

	uni->fअगरo_phys_address = uni->mem_region->start +
				     UNIPERIF_FIFO_DATA_OFFSET(uni);

	uni->irq = platक्रमm_get_irq(priv->pdev, 0);
	अगर (uni->irq < 0)
		वापस -ENXIO;

	uni->type = dev_data->type;

	/* check अगर player should be configured क्रम tdm */
	अगर (dev_data->type & SND_ST_UNIPERIF_TYPE_TDM) अणु
		अगर (!of_property_पढ़ो_string(node, "st,tdm-mode", &mode))
			uni->type = SND_ST_UNIPERIF_TYPE_TDM;
		अन्यथा
			uni->type = SND_ST_UNIPERIF_TYPE_PCM;
	पूर्ण

	dai_data->uni = uni;
	dai_data->stream = dev_data->stream;

	अगर (priv->dai_data.stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = uni_player_init(priv->pdev, uni);
		stream = &dai->playback;
	पूर्ण अन्यथा अणु
		ret = uni_पढ़ोer_init(priv->pdev, uni);
		stream = &dai->capture;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	dai->ops = uni->dai_ops;

	stream->stream_name = dai->name;
	stream->channels_min = uni->hw->channels_min;
	stream->channels_max = uni->hw->channels_max;
	stream->rates = uni->hw->rates;
	stream->क्रमmats = uni->hw->क्रमmats;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config dmaengine_pcm_config = अणु
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
पूर्ण;

अटल पूर्णांक sti_uniperiph_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sti_uniperiph_data *priv;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक ret;

	/* Allocate the निजी data and the CPU_DAI array */
	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dai = devm_kzalloc(&pdev->dev, माप(*priv->dai), GFP_KERNEL);
	अगर (!priv->dai)
		वापस -ENOMEM;

	priv->pdev = pdev;

	ret = sti_uniperiph_cpu_dai_of(node, priv);
	अगर (ret < 0)
		वापस ret;

	dev_set_drvdata(&pdev->dev, priv);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &sti_uniperiph_dai_component,
					      priv->dai, 1);
	अगर (ret < 0)
		वापस ret;

	वापस devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev,
					       &dmaengine_pcm_config, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver sti_uniperiph_driver = अणु
	.driver = अणु
		.name = "sti-uniperiph-dai",
		.of_match_table = snd_soc_sti_match,
	पूर्ण,
	.probe = sti_uniperiph_probe,
पूर्ण;
module_platक्रमm_driver(sti_uniperiph_driver);

MODULE_DESCRIPTION("uniperipheral DAI driver");
MODULE_AUTHOR("Arnaud Pouliquen <arnaud.pouliquen@st.com>");
MODULE_LICENSE("GPL v2");
