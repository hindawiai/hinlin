<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>,
 *         Kristoffer Karlsson <kristoffer.karlsson@stericsson.com>
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/mutex.h>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "ux500_pcm.h"
#समावेश "ux500_msp_dai.h"
#समावेश "mop500_ab8500.h"
#समावेश "../codecs/ab8500-codec.h"

#घोषणा TX_SLOT_MONO	0x0008
#घोषणा TX_SLOT_STEREO	0x000a
#घोषणा RX_SLOT_MONO	0x0001
#घोषणा RX_SLOT_STEREO	0x0003
#घोषणा TX_SLOT_8CH	0x00FF
#घोषणा RX_SLOT_8CH	0x00FF

#घोषणा DEF_TX_SLOTS	TX_SLOT_STEREO
#घोषणा DEF_RX_SLOTS	RX_SLOT_MONO

#घोषणा DRIVERMODE_NORMAL	0
#घोषणा DRIVERMODE_CODEC_ONLY	1

/* Slot configuration */
अटल अचिन्हित पूर्णांक tx_slots = DEF_TX_SLOTS;
अटल अचिन्हित पूर्णांक rx_slots = DEF_RX_SLOTS;

/* Configuration consistency parameters */
अटल DEFINE_MUTEX(mop500_ab8500_params_lock);
अटल अचिन्हित दीर्घ mop500_ab8500_usage;
अटल पूर्णांक mop500_ab8500_rate;
अटल पूर्णांक mop500_ab8500_channels;

/* Clocks */
अटल स्थिर अक्षर * स्थिर क्रमागत_mclk[] = अणु
	"SYSCLK",
	"ULPCLK"
पूर्ण;
क्रमागत mclk अणु
	MCLK_SYSCLK,
	MCLK_ULPCLK,
पूर्ण;

अटल SOC_ENUM_SINGLE_EXT_DECL(soc_क्रमागत_mclk, क्रमागत_mclk);

/* Private data क्रम machine-part MOP500<->AB8500 */
काष्ठा mop500_ab8500_drvdata अणु
	/* Clocks */
	क्रमागत mclk mclk_sel;
	काष्ठा clk *clk_ptr_पूर्णांकclk;
	काष्ठा clk *clk_ptr_sysclk;
	काष्ठा clk *clk_ptr_ulpclk;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *get_mclk_str(क्रमागत mclk mclk_sel)
अणु
	चयन (mclk_sel) अणु
	हाल MCLK_SYSCLK:
		वापस "SYSCLK";
	हाल MCLK_ULPCLK:
		वापस "ULPCLK";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक mop500_ab8500_set_mclk(काष्ठा device *dev,
				काष्ठा mop500_ab8500_drvdata *drvdata)
अणु
	पूर्णांक status;
	काष्ठा clk *clk_ptr;

	अगर (IS_ERR(drvdata->clk_ptr_पूर्णांकclk)) अणु
		dev_err(dev,
			"%s: ERROR: intclk not initialized!\n", __func__);
		वापस -EIO;
	पूर्ण

	चयन (drvdata->mclk_sel) अणु
	हाल MCLK_SYSCLK:
		clk_ptr = drvdata->clk_ptr_sysclk;
		अवरोध;
	हाल MCLK_ULPCLK:
		clk_ptr = drvdata->clk_ptr_ulpclk;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(clk_ptr)) अणु
		dev_err(dev, "%s: ERROR: %s not initialized!\n", __func__,
			get_mclk_str(drvdata->mclk_sel));
		वापस -EIO;
	पूर्ण

	status = clk_set_parent(drvdata->clk_ptr_पूर्णांकclk, clk_ptr);
	अगर (status)
		dev_err(dev,
			"%s: ERROR: Setting intclk parent to %s failed (ret = %d)!",
			__func__, get_mclk_str(drvdata->mclk_sel), status);
	अन्यथा
		dev_dbg(dev,
			"%s: intclk parent changed to %s.\n",
			__func__, get_mclk_str(drvdata->mclk_sel));

	वापस status;
पूर्ण

/*
 * Control-events
 */

अटल पूर्णांक mclk_input_control_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	काष्ठा mop500_ab8500_drvdata *drvdata =
				snd_soc_card_get_drvdata(card);

	ucontrol->value.क्रमागतerated.item[0] = drvdata->mclk_sel;

	वापस 0;
पूर्ण

अटल पूर्णांक mclk_input_control_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	काष्ठा mop500_ab8500_drvdata *drvdata =
				snd_soc_card_get_drvdata(card);
	अचिन्हित पूर्णांक val = ucontrol->value.क्रमागतerated.item[0];

	अगर (val > (अचिन्हित पूर्णांक)MCLK_ULPCLK)
		वापस -EINVAL;
	अगर (drvdata->mclk_sel == val)
		वापस 0;

	drvdata->mclk_sel = val;

	वापस 1;
पूर्ण

/*
 * Controls
 */

अटल काष्ठा snd_kcontrol_new mop500_ab8500_ctrls[] = अणु
	SOC_ENUM_EXT("Master Clock Select",
		soc_क्रमागत_mclk,
		mclk_input_control_get, mclk_input_control_put),
	SOC_DAPM_PIN_SWITCH("Headset Left"),
	SOC_DAPM_PIN_SWITCH("Headset Right"),
	SOC_DAPM_PIN_SWITCH("Earpiece"),
	SOC_DAPM_PIN_SWITCH("Speaker Left"),
	SOC_DAPM_PIN_SWITCH("Speaker Right"),
	SOC_DAPM_PIN_SWITCH("LineOut Left"),
	SOC_DAPM_PIN_SWITCH("LineOut Right"),
	SOC_DAPM_PIN_SWITCH("Vibra 1"),
	SOC_DAPM_PIN_SWITCH("Vibra 2"),
	SOC_DAPM_PIN_SWITCH("Mic 1"),
	SOC_DAPM_PIN_SWITCH("Mic 2"),
	SOC_DAPM_PIN_SWITCH("LineIn Left"),
	SOC_DAPM_PIN_SWITCH("LineIn Right"),
	SOC_DAPM_PIN_SWITCH("DMic 1"),
	SOC_DAPM_PIN_SWITCH("DMic 2"),
	SOC_DAPM_PIN_SWITCH("DMic 3"),
	SOC_DAPM_PIN_SWITCH("DMic 4"),
	SOC_DAPM_PIN_SWITCH("DMic 5"),
	SOC_DAPM_PIN_SWITCH("DMic 6"),
पूर्ण;

/* ASoC */

अटल पूर्णांक mop500_ab8500_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* Set audio-घड़ी source */
	वापस mop500_ab8500_set_mclk(rtd->card->dev,
				snd_soc_card_get_drvdata(rtd->card));
पूर्ण

अटल व्योम mop500_ab8500_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा device *dev = rtd->card->dev;

	dev_dbg(dev, "%s: Enter\n", __func__);

	/* Reset slots configuration to शेष(s) */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		tx_slots = DEF_TX_SLOTS;
	अन्यथा
		rx_slots = DEF_RX_SLOTS;
पूर्ण

अटल पूर्णांक mop500_ab8500_hw_params(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा device *dev = rtd->card->dev;
	अचिन्हित पूर्णांक fmt;
	पूर्णांक channels, ret = 0, driver_mode, slots;
	अचिन्हित पूर्णांक sw_codec, sw_cpu;
	bool is_playback;

	dev_dbg(dev, "%s: Enter\n", __func__);

	dev_dbg(dev, "%s: substream->pcm->name = %s\n"
		"substream->pcm->id = %s.\n"
		"substream->name = %s.\n"
		"substream->number = %d.\n",
		__func__,
		substream->pcm->name,
		substream->pcm->id,
		substream->name,
		substream->number);

	/* Ensure configuration consistency between DAIs */
	mutex_lock(&mop500_ab8500_params_lock);
	अगर (mop500_ab8500_usage) अणु
		अगर (mop500_ab8500_rate != params_rate(params) ||
		    mop500_ab8500_channels != params_channels(params)) अणु
			mutex_unlock(&mop500_ab8500_params_lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		mop500_ab8500_rate = params_rate(params);
		mop500_ab8500_channels = params_channels(params);
	पूर्ण
	__set_bit(cpu_dai->id, &mop500_ab8500_usage);
	mutex_unlock(&mop500_ab8500_params_lock);

	channels = params_channels(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S32_LE:
		sw_cpu = 32;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S16_LE:
		sw_cpu = 16;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Setup codec depending on driver-mode */
	अगर (channels == 8)
		driver_mode = DRIVERMODE_CODEC_ONLY;
	अन्यथा
		driver_mode = DRIVERMODE_NORMAL;
	dev_dbg(dev, "%s: Driver-mode: %s.\n", __func__,
		(driver_mode == DRIVERMODE_NORMAL) ? "NORMAL" : "CODEC_ONLY");

	/* Setup क्रमmat */

	अगर (driver_mode == DRIVERMODE_NORMAL) अणु
		fmt = SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_CBM_CFM |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CONT;
	पूर्ण अन्यथा अणु
		fmt = SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_CBM_CFM |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_GATED;
	पूर्ण

	ret = snd_soc_runसमय_set_dai_fmt(rtd, fmt);
	अगर (ret)
		वापस ret;

	/* Setup TDM-slots */

	is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	चयन (channels) अणु
	हाल 1:
		slots = 16;
		tx_slots = (is_playback) ? TX_SLOT_MONO : 0;
		rx_slots = (is_playback) ? 0 : RX_SLOT_MONO;
		अवरोध;
	हाल 2:
		slots = 16;
		tx_slots = (is_playback) ? TX_SLOT_STEREO : 0;
		rx_slots = (is_playback) ? 0 : RX_SLOT_STEREO;
		अवरोध;
	हाल 8:
		slots = 16;
		tx_slots = (is_playback) ? TX_SLOT_8CH : 0;
		rx_slots = (is_playback) ? 0 : RX_SLOT_8CH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (driver_mode == DRIVERMODE_NORMAL)
		sw_codec = sw_cpu;
	अन्यथा
		sw_codec = 20;

	dev_dbg(dev, "%s: CPU-DAI TDM: TX=0x%04X RX=0x%04x\n", __func__,
		tx_slots, rx_slots);
	ret = snd_soc_dai_set_tdm_slot(cpu_dai, tx_slots, rx_slots, slots,
				sw_cpu);
	अगर (ret)
		वापस ret;

	dev_dbg(dev, "%s: CODEC-DAI TDM: TX=0x%04X RX=0x%04x\n", __func__,
		tx_slots, rx_slots);
	ret = snd_soc_dai_set_tdm_slot(codec_dai, tx_slots, rx_slots, slots,
				sw_codec);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mop500_ab8500_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	mutex_lock(&mop500_ab8500_params_lock);
	__clear_bit(cpu_dai->id, &mop500_ab8500_usage);
	mutex_unlock(&mop500_ab8500_params_lock);

	वापस 0;
पूर्ण

काष्ठा snd_soc_ops mop500_ab8500_ops[] = अणु
	अणु
		.hw_params = mop500_ab8500_hw_params,
		.hw_मुक्त = mop500_ab8500_hw_मुक्त,
		.startup = mop500_ab8500_startup,
		.shutकरोwn = mop500_ab8500_shutकरोwn,
	पूर्ण
पूर्ण;

पूर्णांक mop500_ab8500_machine_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &rtd->card->dapm;
	काष्ठा device *dev = rtd->card->dev;
	काष्ठा mop500_ab8500_drvdata *drvdata;
	पूर्णांक ret;

	dev_dbg(dev, "%s Enter.\n", __func__);

	/* Create driver निजी-data काष्ठा */
	drvdata = devm_kzalloc(dev, माप(काष्ठा mop500_ab8500_drvdata),
			GFP_KERNEL);

	अगर (!drvdata)
		वापस -ENOMEM;

	snd_soc_card_set_drvdata(rtd->card, drvdata);

	/* Setup घड़ीs */

	drvdata->clk_ptr_sysclk = clk_get(dev, "sysclk");
	अगर (IS_ERR(drvdata->clk_ptr_sysclk))
		dev_warn(dev, "%s: WARNING: clk_get failed for 'sysclk'!\n",
			__func__);
	drvdata->clk_ptr_ulpclk = clk_get(dev, "ulpclk");
	अगर (IS_ERR(drvdata->clk_ptr_ulpclk))
		dev_warn(dev, "%s: WARNING: clk_get failed for 'ulpclk'!\n",
			__func__);
	drvdata->clk_ptr_पूर्णांकclk = clk_get(dev, "intclk");
	अगर (IS_ERR(drvdata->clk_ptr_पूर्णांकclk))
		dev_warn(dev, "%s: WARNING: clk_get failed for 'intclk'!\n",
			__func__);

	/* Set पूर्णांकclk शेष parent to ulpclk */
	drvdata->mclk_sel = MCLK_ULPCLK;
	ret = mop500_ab8500_set_mclk(dev, drvdata);
	अगर (ret < 0)
		dev_warn(dev, "%s: WARNING: mop500_ab8500_set_mclk!\n",
			__func__);

	drvdata->mclk_sel = MCLK_ULPCLK;

	/* Add controls */
	ret = snd_soc_add_card_controls(rtd->card, mop500_ab8500_ctrls,
			ARRAY_SIZE(mop500_ab8500_ctrls));
	अगर (ret < 0) अणु
		pr_err("%s: Failed to add machine-controls (%d)!\n",
				__func__, ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_disable_pin(dapm, "Earpiece");
	ret |= snd_soc_dapm_disable_pin(dapm, "Speaker Left");
	ret |= snd_soc_dapm_disable_pin(dapm, "Speaker Right");
	ret |= snd_soc_dapm_disable_pin(dapm, "LineOut Left");
	ret |= snd_soc_dapm_disable_pin(dapm, "LineOut Right");
	ret |= snd_soc_dapm_disable_pin(dapm, "Vibra 1");
	ret |= snd_soc_dapm_disable_pin(dapm, "Vibra 2");
	ret |= snd_soc_dapm_disable_pin(dapm, "Mic 1");
	ret |= snd_soc_dapm_disable_pin(dapm, "Mic 2");
	ret |= snd_soc_dapm_disable_pin(dapm, "LineIn Left");
	ret |= snd_soc_dapm_disable_pin(dapm, "LineIn Right");
	ret |= snd_soc_dapm_disable_pin(dapm, "DMic 1");
	ret |= snd_soc_dapm_disable_pin(dapm, "DMic 2");
	ret |= snd_soc_dapm_disable_pin(dapm, "DMic 3");
	ret |= snd_soc_dapm_disable_pin(dapm, "DMic 4");
	ret |= snd_soc_dapm_disable_pin(dapm, "DMic 5");
	ret |= snd_soc_dapm_disable_pin(dapm, "DMic 6");

	वापस ret;
पूर्ण

व्योम mop500_ab8500_हटाओ(काष्ठा snd_soc_card *card)
अणु
	काष्ठा mop500_ab8500_drvdata *drvdata = snd_soc_card_get_drvdata(card);

	अगर (drvdata->clk_ptr_sysclk != शून्य)
		clk_put(drvdata->clk_ptr_sysclk);
	अगर (drvdata->clk_ptr_ulpclk != शून्य)
		clk_put(drvdata->clk_ptr_ulpclk);
	अगर (drvdata->clk_ptr_पूर्णांकclk != शून्य)
		clk_put(drvdata->clk_ptr_पूर्णांकclk);

	snd_soc_card_set_drvdata(card, drvdata);
पूर्ण
