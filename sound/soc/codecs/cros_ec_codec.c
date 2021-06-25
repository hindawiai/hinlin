<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Google, Inc.
 *
 * ChromeOS Embedded Controller codec driver.
 *
 * This driver uses the cros-ec पूर्णांकerface to communicate with the ChromeOS
 * EC क्रम audio function.
 */

#समावेश <crypto/sha2.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

काष्ठा cros_ec_codec_priv अणु
	काष्ठा device *dev;
	काष्ठा cros_ec_device *ec_device;

	/* common */
	uपूर्णांक32_t ec_capabilities;

	uपूर्णांक64_t ec_shm_addr;
	uपूर्णांक32_t ec_shm_len;

	uपूर्णांक64_t ap_shm_phys_addr;
	uपूर्णांक32_t ap_shm_len;
	uपूर्णांक64_t ap_shm_addr;
	uपूर्णांक64_t ap_shm_last_alloc;

	/* DMIC */
	atomic_t dmic_probed;

	/* I2S_RX */
	uपूर्णांक32_t i2s_rx_bclk_ratio;

	/* WoV */
	bool wov_enabled;
	uपूर्णांक8_t *wov_audio_shm_p;
	uपूर्णांक32_t wov_audio_shm_len;
	uपूर्णांक8_t wov_audio_shm_type;
	uपूर्णांक8_t *wov_lang_shm_p;
	uपूर्णांक32_t wov_lang_shm_len;
	uपूर्णांक8_t wov_lang_shm_type;

	काष्ठा mutex wov_dma_lock;
	uपूर्णांक8_t wov_buf[64000];
	uपूर्णांक32_t wov_rp, wov_wp;
	माप_प्रकार wov_dma_offset;
	bool wov_burst_पढ़ो;
	काष्ठा snd_pcm_substream *wov_substream;
	काष्ठा delayed_work wov_copy_work;
	काष्ठा notअगरier_block wov_notअगरier;
पूर्ण;

अटल पूर्णांक ec_codec_capable(काष्ठा cros_ec_codec_priv *priv, uपूर्णांक8_t cap)
अणु
	वापस priv->ec_capabilities & BIT(cap);
पूर्ण

अटल पूर्णांक send_ec_host_command(काष्ठा cros_ec_device *ec_dev, uपूर्णांक32_t cmd,
				uपूर्णांक8_t *out, माप_प्रकार outsize,
				uपूर्णांक8_t *in, माप_प्रकार insize)
अणु
	पूर्णांक ret;
	काष्ठा cros_ec_command *msg;

	msg = kदो_स्मृति(माप(*msg) + max(outsize, insize), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->version = 0;
	msg->command = cmd;
	msg->outsize = outsize;
	msg->insize = insize;

	अगर (outsize)
		स_नकल(msg->data, out, outsize);

	ret = cros_ec_cmd_xfer_status(ec_dev, msg);
	अगर (ret < 0)
		जाओ error;

	अगर (in && insize)
		स_नकल(in, msg->data, insize);

	ret = 0;
error:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक dmic_get_gain(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	काष्ठा ec_param_ec_codec_dmic p;
	काष्ठा ec_response_ec_codec_dmic_get_gain_idx r;
	पूर्णांक ret;

	p.cmd = EC_CODEC_DMIC_GET_GAIN_IDX;
	p.get_gain_idx_param.channel = EC_CODEC_DMIC_CHANNEL_0;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uपूर्णांक8_t *)&p, माप(p),
				   (uपूर्णांक8_t *)&r, माप(r));
	अगर (ret < 0)
		वापस ret;
	ucontrol->value.पूर्णांकeger.value[0] = r.gain;

	p.cmd = EC_CODEC_DMIC_GET_GAIN_IDX;
	p.get_gain_idx_param.channel = EC_CODEC_DMIC_CHANNEL_1;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uपूर्णांक8_t *)&p, माप(p),
				   (uपूर्णांक8_t *)&r, माप(r));
	अगर (ret < 0)
		वापस ret;
	ucontrol->value.पूर्णांकeger.value[1] = r.gain;

	वापस 0;
पूर्ण

अटल पूर्णांक dmic_put_gain(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *control =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक max_dmic_gain = control->max;
	पूर्णांक left = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक right = ucontrol->value.पूर्णांकeger.value[1];
	काष्ठा ec_param_ec_codec_dmic p;
	पूर्णांक ret;

	अगर (left > max_dmic_gain || right > max_dmic_gain)
		वापस -EINVAL;

	dev_dbg(component->dev, "set mic gain to %u, %u\n", left, right);

	p.cmd = EC_CODEC_DMIC_SET_GAIN_IDX;
	p.set_gain_idx_param.channel = EC_CODEC_DMIC_CHANNEL_0;
	p.set_gain_idx_param.gain = left;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	p.cmd = EC_CODEC_DMIC_SET_GAIN_IDX;
	p.set_gain_idx_param.channel = EC_CODEC_DMIC_CHANNEL_1;
	p.set_gain_idx_param.gain = right;
	वापस send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_DMIC,
				    (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dmic_gain_tlv, 0, 100, 0);

क्रमागत अणु
	DMIC_CTL_GAIN = 0,
पूर्ण;

अटल काष्ठा snd_kcontrol_new dmic_controls[] = अणु
	[DMIC_CTL_GAIN] =
		SOC_DOUBLE_EXT_TLV("EC Mic Gain", SND_SOC_NOPM, SND_SOC_NOPM,
				   0, 0, 0, dmic_get_gain, dmic_put_gain,
				   dmic_gain_tlv),
पूर्ण;

अटल पूर्णांक dmic_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = priv->dev;
	काष्ठा soc_mixer_control *control;
	काष्ठा ec_param_ec_codec_dmic p;
	काष्ठा ec_response_ec_codec_dmic_get_max_gain r;
	पूर्णांक ret;

	अगर (!atomic_add_unless(&priv->dmic_probed, 1, 1))
		वापस 0;

	p.cmd = EC_CODEC_DMIC_GET_MAX_GAIN;

	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uपूर्णांक8_t *)&p, माप(p),
				   (uपूर्णांक8_t *)&r, माप(r));
	अगर (ret < 0) अणु
		dev_warn(dev, "get_max_gain() unsupported\n");
		वापस 0;
	पूर्ण

	dev_dbg(dev, "max gain = %d\n", r.max_gain);

	control = (काष्ठा soc_mixer_control *)
		dmic_controls[DMIC_CTL_GAIN].निजी_value;
	control->max = r.max_gain;
	control->platक्रमm_max = r.max_gain;

	वापस snd_soc_add_component_controls(component,
			&dmic_controls[DMIC_CTL_GAIN], 1);
पूर्ण

अटल पूर्णांक i2s_rx_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	काष्ठा ec_param_ec_codec_i2s_rx p;
	क्रमागत ec_codec_i2s_rx_sample_depth depth;
	uपूर्णांक32_t bclk;
	पूर्णांक ret;

	अगर (params_rate(params) != 48000)
		वापस -EINVAL;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		depth = EC_CODEC_I2S_RX_SAMPLE_DEPTH_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		depth = EC_CODEC_I2S_RX_SAMPLE_DEPTH_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "set depth to %u\n", depth);

	p.cmd = EC_CODEC_I2S_RX_SET_SAMPLE_DEPTH;
	p.set_sample_depth_param.depth = depth;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_I2S_RX,
				   (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (priv->i2s_rx_bclk_ratio)
		bclk = params_rate(params) * priv->i2s_rx_bclk_ratio;
	अन्यथा
		bclk = snd_soc_params_to_bclk(params);

	dev_dbg(component->dev, "set bclk to %u\n", bclk);

	p.cmd = EC_CODEC_I2S_RX_SET_BCLK;
	p.set_bclk_param.bclk = bclk;
	वापस send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_I2S_RX,
				    (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
पूर्ण

अटल पूर्णांक i2s_rx_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);

	priv->i2s_rx_bclk_ratio = ratio;
	वापस 0;
पूर्ण

अटल पूर्णांक i2s_rx_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	काष्ठा ec_param_ec_codec_i2s_rx p;
	क्रमागत ec_codec_i2s_rx_daअगरmt daअगरmt;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		daअगरmt = EC_CODEC_I2S_RX_DAIFMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		daअगरmt = EC_CODEC_I2S_RX_DAIFMT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		daअगरmt = EC_CODEC_I2S_RX_DAIFMT_LEFT_J;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "set format to %u\n", daअगरmt);

	p.cmd = EC_CODEC_I2S_RX_SET_DAIFMT;
	p.set_daअगरmt_param.daअगरmt = daअगरmt;
	वापस send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_I2S_RX,
				    (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops i2s_rx_dai_ops = अणु
	.hw_params = i2s_rx_hw_params,
	.set_fmt = i2s_rx_set_fmt,
	.set_bclk_ratio = i2s_rx_set_bclk_ratio,
पूर्ण;

अटल पूर्णांक i2s_rx_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	काष्ठा ec_param_ec_codec_i2s_rx p = अणुपूर्ण;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		dev_dbg(component->dev, "enable I2S RX\n");
		p.cmd = EC_CODEC_I2S_RX_ENABLE;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		dev_dbg(component->dev, "disable I2S RX\n");
		p.cmd = EC_CODEC_I2S_RX_DISABLE;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_I2S_RX,
				    (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
पूर्ण

अटल काष्ठा snd_soc_dapm_widget i2s_rx_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("DMIC"),
	SND_SOC_DAPM_SUPPLY("I2S RX Enable", SND_SOC_NOPM, 0, 0, i2s_rx_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_AIF_OUT("I2S RX", "I2S Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल काष्ठा snd_soc_dapm_route i2s_rx_dapm_routes[] = अणु
	अणु"I2S RX", शून्य, "DMIC"पूर्ण,
	अणु"I2S RX", शून्य, "I2S RX Enable"पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver i2s_rx_dai_driver = अणु
	.name = "EC Codec I2S RX",
	.capture = अणु
		.stream_name = "I2S Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
	.ops = &i2s_rx_dai_ops,
पूर्ण;

अटल पूर्णांक i2s_rx_probe(काष्ठा snd_soc_component *component)
अणु
	वापस dmic_probe(component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver i2s_rx_component_driver = अणु
	.probe			= i2s_rx_probe,
	.dapm_widमाला_लो		= i2s_rx_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(i2s_rx_dapm_widमाला_लो),
	.dapm_routes		= i2s_rx_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(i2s_rx_dapm_routes),
पूर्ण;

अटल व्योम *wov_map_shm(काष्ठा cros_ec_codec_priv *priv,
			 uपूर्णांक8_t shm_id, uपूर्णांक32_t *len, uपूर्णांक8_t *type)
अणु
	काष्ठा ec_param_ec_codec p;
	काष्ठा ec_response_ec_codec_get_shm_addr r;
	uपूर्णांक32_t req, offset;

	p.cmd = EC_CODEC_GET_SHM_ADDR;
	p.get_shm_addr_param.shm_id = shm_id;
	अगर (send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC,
				 (uपूर्णांक8_t *)&p, माप(p),
				 (uपूर्णांक8_t *)&r, माप(r)) < 0) अणु
		dev_err(priv->dev, "failed to EC_CODEC_GET_SHM_ADDR\n");
		वापस शून्य;
	पूर्ण

	dev_dbg(priv->dev, "phys_addr=%#llx, len=%#x\n", r.phys_addr, r.len);

	*len = r.len;
	*type = r.type;

	चयन (r.type) अणु
	हाल EC_CODEC_SHM_TYPE_EC_RAM:
		वापस (व्योम __क्रमce *)devm_ioremap_wc(priv->dev,
				r.phys_addr + priv->ec_shm_addr, r.len);
	हाल EC_CODEC_SHM_TYPE_SYSTEM_RAM:
		अगर (r.phys_addr) अणु
			dev_err(priv->dev, "unknown status\n");
			वापस शून्य;
		पूर्ण

		req = round_up(r.len, PAGE_SIZE);
		dev_dbg(priv->dev, "round up from %u to %u\n", r.len, req);

		अगर (priv->ap_shm_last_alloc + req >
		    priv->ap_shm_phys_addr + priv->ap_shm_len) अणु
			dev_err(priv->dev, "insufficient space for AP SHM\n");
			वापस शून्य;
		पूर्ण

		dev_dbg(priv->dev, "alloc AP SHM addr=%#llx, len=%#x\n",
			priv->ap_shm_last_alloc, req);

		p.cmd = EC_CODEC_SET_SHM_ADDR;
		p.set_shm_addr_param.phys_addr = priv->ap_shm_last_alloc;
		p.set_shm_addr_param.len = req;
		p.set_shm_addr_param.shm_id = shm_id;
		अगर (send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC,
					 (uपूर्णांक8_t *)&p, माप(p),
					 शून्य, 0) < 0) अणु
			dev_err(priv->dev, "failed to EC_CODEC_SET_SHM_ADDR\n");
			वापस शून्य;
		पूर्ण

		/*
		 * Note: EC codec only requests क्रम `r.len' but we allocate
		 * round up PAGE_SIZE `req'.
		 */
		offset = priv->ap_shm_last_alloc - priv->ap_shm_phys_addr;
		priv->ap_shm_last_alloc += req;

		वापस (व्योम *)(uपूर्णांकptr_t)(priv->ap_shm_addr + offset);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल bool wov_queue_full(काष्ठा cros_ec_codec_priv *priv)
अणु
	वापस ((priv->wov_wp + 1) % माप(priv->wov_buf)) == priv->wov_rp;
पूर्ण

अटल माप_प्रकार wov_queue_size(काष्ठा cros_ec_codec_priv *priv)
अणु
	अगर (priv->wov_wp >= priv->wov_rp)
		वापस priv->wov_wp - priv->wov_rp;
	अन्यथा
		वापस माप(priv->wov_buf) - priv->wov_rp + priv->wov_wp;
पूर्ण

अटल व्योम wov_queue_dequeue(काष्ठा cros_ec_codec_priv *priv, माप_प्रकार len)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = priv->wov_substream->runसमय;
	माप_प्रकार req;

	जबतक (len) अणु
		req = min(len, runसमय->dma_bytes - priv->wov_dma_offset);
		अगर (priv->wov_wp >= priv->wov_rp)
			req = min(req, (माप_प्रकार)priv->wov_wp - priv->wov_rp);
		अन्यथा
			req = min(req, माप(priv->wov_buf) - priv->wov_rp);

		स_नकल(runसमय->dma_area + priv->wov_dma_offset,
		       priv->wov_buf + priv->wov_rp, req);

		priv->wov_dma_offset += req;
		अगर (priv->wov_dma_offset == runसमय->dma_bytes)
			priv->wov_dma_offset = 0;

		priv->wov_rp += req;
		अगर (priv->wov_rp == माप(priv->wov_buf))
			priv->wov_rp = 0;

		len -= req;
	पूर्ण

	snd_pcm_period_elapsed(priv->wov_substream);
पूर्ण

अटल व्योम wov_queue_try_dequeue(काष्ठा cros_ec_codec_priv *priv)
अणु
	माप_प्रकार period_bytes = snd_pcm_lib_period_bytes(priv->wov_substream);

	जबतक (period_bytes && wov_queue_size(priv) >= period_bytes) अणु
		wov_queue_dequeue(priv, period_bytes);
		period_bytes = snd_pcm_lib_period_bytes(priv->wov_substream);
	पूर्ण
पूर्ण

अटल व्योम wov_queue_enqueue(काष्ठा cros_ec_codec_priv *priv,
			      uपूर्णांक8_t *addr, माप_प्रकार len, bool iomem)
अणु
	माप_प्रकार req;

	जबतक (len) अणु
		अगर (wov_queue_full(priv)) अणु
			wov_queue_try_dequeue(priv);

			अगर (wov_queue_full(priv)) अणु
				dev_err(priv->dev, "overrun detected\n");
				वापस;
			पूर्ण
		पूर्ण

		अगर (priv->wov_wp >= priv->wov_rp)
			req = माप(priv->wov_buf) - priv->wov_wp;
		अन्यथा
			/* Note: waste 1-byte to dअगरferentiate full and empty */
			req = priv->wov_rp - priv->wov_wp - 1;
		req = min(req, len);

		अगर (iomem)
			स_नकल_fromio(priv->wov_buf + priv->wov_wp,
				      (व्योम __क्रमce __iomem *)addr, req);
		अन्यथा
			स_नकल(priv->wov_buf + priv->wov_wp, addr, req);

		priv->wov_wp += req;
		अगर (priv->wov_wp == माप(priv->wov_buf))
			priv->wov_wp = 0;

		addr += req;
		len -= req;
	पूर्ण

	wov_queue_try_dequeue(priv);
पूर्ण

अटल पूर्णांक wov_पढ़ो_audio_shm(काष्ठा cros_ec_codec_priv *priv)
अणु
	काष्ठा ec_param_ec_codec_wov p;
	काष्ठा ec_response_ec_codec_wov_पढ़ो_audio_shm r;
	पूर्णांक ret;

	p.cmd = EC_CODEC_WOV_READ_AUDIO_SHM;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_WOV,
				   (uपूर्णांक8_t *)&p, माप(p),
				   (uपूर्णांक8_t *)&r, माप(r));
	अगर (ret) अणु
		dev_err(priv->dev, "failed to EC_CODEC_WOV_READ_AUDIO_SHM\n");
		वापस ret;
	पूर्ण

	अगर (!r.len)
		dev_dbg(priv->dev, "no data, sleep\n");
	अन्यथा
		wov_queue_enqueue(priv, priv->wov_audio_shm_p + r.offset, r.len,
			priv->wov_audio_shm_type == EC_CODEC_SHM_TYPE_EC_RAM);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक wov_पढ़ो_audio(काष्ठा cros_ec_codec_priv *priv)
अणु
	काष्ठा ec_param_ec_codec_wov p;
	काष्ठा ec_response_ec_codec_wov_पढ़ो_audio r;
	पूर्णांक reमुख्य = priv->wov_burst_पढ़ो ? 16000 : 320;
	पूर्णांक ret;

	जबतक (reमुख्य >= 0) अणु
		p.cmd = EC_CODEC_WOV_READ_AUDIO;
		ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_WOV,
					   (uपूर्णांक8_t *)&p, माप(p),
					   (uपूर्णांक8_t *)&r, माप(r));
		अगर (ret) अणु
			dev_err(priv->dev,
				"failed to EC_CODEC_WOV_READ_AUDIO\n");
			वापस ret;
		पूर्ण

		अगर (!r.len) अणु
			dev_dbg(priv->dev, "no data, sleep\n");
			priv->wov_burst_पढ़ो = false;
			अवरोध;
		पूर्ण

		wov_queue_enqueue(priv, r.buf, r.len, false);
		reमुख्य -= r.len;
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल व्योम wov_copy_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा cros_ec_codec_priv *priv =
		container_of(w, काष्ठा cros_ec_codec_priv, wov_copy_work.work);
	पूर्णांक ret;

	mutex_lock(&priv->wov_dma_lock);
	अगर (!priv->wov_substream) अणु
		dev_warn(priv->dev, "no pcm substream\n");
		जाओ leave;
	पूर्ण

	अगर (ec_codec_capable(priv, EC_CODEC_CAP_WOV_AUDIO_SHM))
		ret = wov_पढ़ो_audio_shm(priv);
	अन्यथा
		ret = wov_पढ़ो_audio(priv);

	अगर (ret == -EAGAIN)
		schedule_delayed_work(&priv->wov_copy_work,
				      msecs_to_jअगरfies(10));
	अन्यथा अगर (ret)
		dev_err(priv->dev, "failed to read audio data\n");
leave:
	mutex_unlock(&priv->wov_dma_lock);
पूर्ण

अटल पूर्णांक wov_enable_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा cros_ec_codec_priv *priv = snd_soc_component_get_drvdata(c);

	ucontrol->value.पूर्णांकeger.value[0] = priv->wov_enabled;
	वापस 0;
पूर्ण

अटल पूर्णांक wov_enable_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा cros_ec_codec_priv *priv = snd_soc_component_get_drvdata(c);
	पूर्णांक enabled = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा ec_param_ec_codec_wov p;
	पूर्णांक ret;

	अगर (priv->wov_enabled != enabled) अणु
		अगर (enabled)
			p.cmd = EC_CODEC_WOV_ENABLE;
		अन्यथा
			p.cmd = EC_CODEC_WOV_DISABLE;

		ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_WOV,
					   (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
		अगर (ret) अणु
			dev_err(priv->dev, "failed to %s wov\n",
				enabled ? "enable" : "disable");
			वापस ret;
		पूर्ण

		priv->wov_enabled = enabled;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wov_set_lang_shm(काष्ठा cros_ec_codec_priv *priv,
			    uपूर्णांक8_t *buf, माप_प्रकार size, uपूर्णांक8_t *digest)
अणु
	काष्ठा ec_param_ec_codec_wov p;
	काष्ठा ec_param_ec_codec_wov_set_lang_shm *pp = &p.set_lang_shm_param;
	पूर्णांक ret;

	अगर (size > priv->wov_lang_shm_len) अणु
		dev_err(priv->dev, "no enough SHM size: %d\n",
			priv->wov_lang_shm_len);
		वापस -EIO;
	पूर्ण

	चयन (priv->wov_lang_shm_type) अणु
	हाल EC_CODEC_SHM_TYPE_EC_RAM:
		स_नकल_toio((व्योम __क्रमce __iomem *)priv->wov_lang_shm_p,
			    buf, size);
		स_रखो_io((व्योम __क्रमce __iomem *)priv->wov_lang_shm_p + size,
			  0, priv->wov_lang_shm_len - size);
		अवरोध;
	हाल EC_CODEC_SHM_TYPE_SYSTEM_RAM:
		स_नकल(priv->wov_lang_shm_p, buf, size);
		स_रखो(priv->wov_lang_shm_p + size, 0,
		       priv->wov_lang_shm_len - size);

		/* make sure ग_लिखो to memory beक्रमe calling host command */
		wmb();
		अवरोध;
	पूर्ण

	p.cmd = EC_CODEC_WOV_SET_LANG_SHM;
	स_नकल(pp->hash, digest, SHA256_DIGEST_SIZE);
	pp->total_len = size;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_WOV,
				   (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
	अगर (ret) अणु
		dev_err(priv->dev, "failed to EC_CODEC_WOV_SET_LANG_SHM\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wov_set_lang(काष्ठा cros_ec_codec_priv *priv,
			uपूर्णांक8_t *buf, माप_प्रकार size, uपूर्णांक8_t *digest)
अणु
	काष्ठा ec_param_ec_codec_wov p;
	काष्ठा ec_param_ec_codec_wov_set_lang *pp = &p.set_lang_param;
	माप_प्रकार i, req;
	पूर्णांक ret;

	क्रम (i = 0; i < size; i += req) अणु
		req = min(size - i, ARRAY_SIZE(pp->buf));

		p.cmd = EC_CODEC_WOV_SET_LANG;
		स_नकल(pp->hash, digest, SHA256_DIGEST_SIZE);
		pp->total_len = size;
		pp->offset = i;
		स_नकल(pp->buf, buf + i, req);
		pp->len = req;
		ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_WOV,
					   (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
		अगर (ret) अणु
			dev_err(priv->dev, "failed to EC_CODEC_WOV_SET_LANG\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wov_hotword_model_put(काष्ठा snd_kcontrol *kcontrol,
				 स्थिर अचिन्हित पूर्णांक __user *bytes,
				 अचिन्हित पूर्णांक size)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	काष्ठा ec_param_ec_codec_wov p;
	काष्ठा ec_response_ec_codec_wov_get_lang r;
	uपूर्णांक8_t digest[SHA256_DIGEST_SIZE];
	uपूर्णांक8_t *buf;
	पूर्णांक ret;

	/* Skips the TLV header. */
	bytes += 2;
	size -= 8;

	dev_dbg(priv->dev, "%s: size=%d\n", __func__, size);

	buf = memdup_user(bytes, size);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	sha256(buf, size, digest);
	dev_dbg(priv->dev, "hash=%*phN\n", SHA256_DIGEST_SIZE, digest);

	p.cmd = EC_CODEC_WOV_GET_LANG;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_WOV,
				   (uपूर्णांक8_t *)&p, माप(p),
				   (uपूर्णांक8_t *)&r, माप(r));
	अगर (ret)
		जाओ leave;

	अगर (स_भेद(digest, r.hash, SHA256_DIGEST_SIZE) == 0) अणु
		dev_dbg(priv->dev, "not updated");
		जाओ leave;
	पूर्ण

	अगर (ec_codec_capable(priv, EC_CODEC_CAP_WOV_LANG_SHM))
		ret = wov_set_lang_shm(priv, buf, size, digest);
	अन्यथा
		ret = wov_set_lang(priv, buf, size, digest);

leave:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल काष्ठा snd_kcontrol_new wov_controls[] = अणु
	SOC_SINGLE_BOOL_EXT("Wake-on-Voice Switch", 0,
			    wov_enable_get, wov_enable_put),
	SND_SOC_BYTES_TLV("Hotword Model", 0x11000, शून्य,
			  wov_hotword_model_put),
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wov_dai_driver = अणु
	.name = "Wake on Voice",
	.capture = अणु
		.stream_name = "WoV Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wov_host_event(काष्ठा notअगरier_block *nb,
			  अचिन्हित दीर्घ queued_during_suspend, व्योम *notअगरy)
अणु
	काष्ठा cros_ec_codec_priv *priv =
		container_of(nb, काष्ठा cros_ec_codec_priv, wov_notअगरier);
	u32 host_event;

	dev_dbg(priv->dev, "%s\n", __func__);

	host_event = cros_ec_get_host_event(priv->ec_device);
	अगर (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_WOV)) अणु
		schedule_delayed_work(&priv->wov_copy_work, 0);
		वापस NOTIFY_OK;
	पूर्ण अन्यथा अणु
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल पूर्णांक wov_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_init(&priv->wov_dma_lock);
	INIT_DELAYED_WORK(&priv->wov_copy_work, wov_copy_work);

	priv->wov_notअगरier.notअगरier_call = wov_host_event;
	ret = blocking_notअगरier_chain_रेजिस्टर(
			&priv->ec_device->event_notअगरier, &priv->wov_notअगरier);
	अगर (ret)
		वापस ret;

	अगर (ec_codec_capable(priv, EC_CODEC_CAP_WOV_LANG_SHM)) अणु
		priv->wov_lang_shm_p = wov_map_shm(priv,
				EC_CODEC_SHM_ID_WOV_LANG,
				&priv->wov_lang_shm_len,
				&priv->wov_lang_shm_type);
		अगर (!priv->wov_lang_shm_p)
			वापस -EFAULT;
	पूर्ण

	अगर (ec_codec_capable(priv, EC_CODEC_CAP_WOV_AUDIO_SHM)) अणु
		priv->wov_audio_shm_p = wov_map_shm(priv,
				EC_CODEC_SHM_ID_WOV_AUDIO,
				&priv->wov_audio_shm_len,
				&priv->wov_audio_shm_type);
		अगर (!priv->wov_audio_shm_p)
			वापस -EFAULT;
	पूर्ण

	वापस dmic_probe(component);
पूर्ण

अटल व्योम wov_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);

	blocking_notअगरier_chain_unरेजिस्टर(
			&priv->ec_device->event_notअगरier, &priv->wov_notअगरier);
पूर्ण

अटल पूर्णांक wov_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	अटल स्थिर काष्ठा snd_pcm_hardware hw_param = अणु
		.info = SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_MMAP_VALID,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		.rates = SNDRV_PCM_RATE_16000,
		.channels_min = 1,
		.channels_max = 1,
		.period_bytes_min = PAGE_SIZE,
		.period_bytes_max = 0x20000 / 8,
		.periods_min = 8,
		.periods_max = 8,
		.buffer_bytes_max = 0x20000,
	पूर्ण;

	वापस snd_soc_set_runसमय_hwparams(substream, &hw_param);
पूर्ण

अटल पूर्णांक wov_pcm_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);

	mutex_lock(&priv->wov_dma_lock);
	priv->wov_substream = substream;
	priv->wov_rp = priv->wov_wp = 0;
	priv->wov_dma_offset = 0;
	priv->wov_burst_पढ़ो = true;
	mutex_unlock(&priv->wov_dma_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक wov_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);

	mutex_lock(&priv->wov_dma_lock);
	wov_queue_dequeue(priv, wov_queue_size(priv));
	priv->wov_substream = शून्य;
	mutex_unlock(&priv->wov_dma_lock);

	cancel_delayed_work_sync(&priv->wov_copy_work);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t wov_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cros_ec_codec_priv *priv =
		snd_soc_component_get_drvdata(component);

	वापस bytes_to_frames(runसमय, priv->wov_dma_offset);
पूर्ण

अटल पूर्णांक wov_pcm_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_VMALLOC,
				       शून्य, 0, 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver wov_component_driver = अणु
	.probe		= wov_probe,
	.हटाओ		= wov_हटाओ,
	.controls	= wov_controls,
	.num_controls	= ARRAY_SIZE(wov_controls),
	.खोलो		= wov_pcm_खोलो,
	.hw_params	= wov_pcm_hw_params,
	.hw_मुक्त	= wov_pcm_hw_मुक्त,
	.poपूर्णांकer	= wov_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= wov_pcm_new,
पूर्ण;

अटल पूर्णांक cros_ec_codec_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_device *ec_device = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cros_ec_codec_priv *priv;
	काष्ठा ec_param_ec_codec p;
	काष्ठा ec_response_ec_codec_get_capabilities r;
	पूर्णांक ret;
#अगर_घोषित CONFIG_OF
	काष्ठा device_node *node;
	काष्ठा resource res;
	u64 ec_shm_size;
	स्थिर __be32 *regaddr_p;
#पूर्ण_अगर

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_OF
	regaddr_p = of_get_address(dev->of_node, 0, &ec_shm_size, शून्य);
	अगर (regaddr_p) अणु
		priv->ec_shm_addr = of_पढ़ो_number(regaddr_p, 2);
		priv->ec_shm_len = ec_shm_size;

		dev_dbg(dev, "ec_shm_addr=%#llx len=%#x\n",
			priv->ec_shm_addr, priv->ec_shm_len);
	पूर्ण

	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	अगर (node) अणु
		ret = of_address_to_resource(node, 0, &res);
		अगर (!ret) अणु
			priv->ap_shm_phys_addr = res.start;
			priv->ap_shm_len = resource_size(&res);
			priv->ap_shm_addr =
				(uपूर्णांक64_t)(uपूर्णांकptr_t)devm_ioremap_wc(
					dev, priv->ap_shm_phys_addr,
					priv->ap_shm_len);
			priv->ap_shm_last_alloc = priv->ap_shm_phys_addr;

			dev_dbg(dev, "ap_shm_phys_addr=%#llx len=%#x\n",
				priv->ap_shm_phys_addr, priv->ap_shm_len);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	priv->dev = dev;
	priv->ec_device = ec_device;
	atomic_set(&priv->dmic_probed, 0);

	p.cmd = EC_CODEC_GET_CAPABILITIES;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC,
				   (uपूर्णांक8_t *)&p, माप(p),
				   (uपूर्णांक8_t *)&r, माप(r));
	अगर (ret) अणु
		dev_err(dev, "failed to EC_CODEC_GET_CAPABILITIES\n");
		वापस ret;
	पूर्ण
	priv->ec_capabilities = r.capabilities;

	/* Reset EC codec i2s rx. */
	p.cmd = EC_CODEC_I2S_RX_RESET;
	ret = send_ec_host_command(priv->ec_device, EC_CMD_EC_CODEC_I2S_RX,
				   (uपूर्णांक8_t *)&p, माप(p), शून्य, 0);
	अगर (ret == -ENOPROTOOPT) अणु
		dev_info(dev,
			 "Missing reset command. Please update EC firmware.\n");
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(dev, "failed to EC_CODEC_I2S_RESET: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &i2s_rx_component_driver,
					      &i2s_rx_dai_driver, 1);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &wov_component_driver,
					       &wov_dai_driver, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cros_ec_codec_of_match[] = अणु
	अणु .compatible = "google,cros-ec-codec" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_codec_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cros_ec_codec_acpi_id[] = अणु
	अणु "GOOG0013", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_ec_codec_acpi_id);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver cros_ec_codec_platक्रमm_driver = अणु
	.driver = अणु
		.name = "cros-ec-codec",
		.of_match_table = of_match_ptr(cros_ec_codec_of_match),
		.acpi_match_table = ACPI_PTR(cros_ec_codec_acpi_id),
	पूर्ण,
	.probe = cros_ec_codec_platक्रमm_probe,
पूर्ण;

module_platक्रमm_driver(cros_ec_codec_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChromeOS EC codec driver");
MODULE_AUTHOR("Cheng-Yi Chiang <cychiang@chromium.org>");
MODULE_ALIAS("platform:cros-ec-codec");
