<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

#समावेश <linux/module.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/hda_i915.h>
#समावेश <sound/sof.h>
#समावेश "../ops.h"
#समावेश "hda.h"
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
#समावेश "../../codecs/hdac_hda.h"
#पूर्ण_अगर /* CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC */

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
#घोषणा IDISP_VID_INTEL	0x80860000

/* load the legacy HDA codec driver */
अटल पूर्णांक request_codec_module(काष्ठा hda_codec *codec)
अणु
#अगर_घोषित MODULE
	अक्षर alias[MODULE_NAME_LEN];
	स्थिर अक्षर *mod = शून्य;

	चयन (codec->probe_id) अणु
	हाल HDA_CODEC_ID_GENERIC:
#अगर IS_MODULE(CONFIG_SND_HDA_GENERIC)
		mod = "snd-hda-codec-generic";
#पूर्ण_अगर
		अवरोध;
	शेष:
		snd_hdac_codec_modalias(&codec->core, alias, माप(alias));
		mod = alias;
		अवरोध;
	पूर्ण

	अगर (mod) अणु
		dev_dbg(&codec->core.dev, "loading codec module: %s\n", mod);
		request_module(mod);
	पूर्ण
#पूर्ण_अगर /* MODULE */
	वापस device_attach(hda_codec_dev(codec));
पूर्ण

अटल पूर्णांक hda_codec_load_module(काष्ठा hda_codec *codec)
अणु
	पूर्णांक ret = request_codec_module(codec);

	अगर (ret <= 0) अणु
		codec->probe_id = HDA_CODEC_ID_GENERIC;
		ret = request_codec_module(codec);
	पूर्ण

	वापस ret;
पूर्ण

/* enable controller wake up event क्रम all codecs with jack connectors */
व्योम hda_codec_jack_wake_enable(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
	काष्ठा hda_bus *hbus = sof_to_hbus(sdev);
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hda_codec *codec;
	अचिन्हित पूर्णांक mask = 0;

	अगर (enable) अणु
		list_क्रम_each_codec(codec, hbus)
			अगर (codec->jacktbl.used)
				mask |= BIT(codec->core.addr);
	पूर्ण

	snd_hdac_chip_updatew(bus, WAKEEN, STATESTS_INT_MASK, mask);
पूर्ण

/* check jack status after resuming from suspend mode */
व्योम hda_codec_jack_check(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hda_bus *hbus = sof_to_hbus(sdev);
	काष्ठा hda_codec *codec;

	list_क्रम_each_codec(codec, hbus)
		/*
		 * Wake up all jack-detecting codecs regardless whether an event
		 * has been recorded in STATESTS
		 */
		अगर (codec->jacktbl.used)
			pm_request_resume(&codec->core.dev);
पूर्ण
#अन्यथा
व्योम hda_codec_jack_wake_enable(काष्ठा snd_sof_dev *sdev, bool enable) अणुपूर्ण
व्योम hda_codec_jack_check(काष्ठा snd_sof_dev *sdev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC */
EXPORT_SYMBOL_NS(hda_codec_jack_wake_enable, SND_SOC_SOF_HDA_AUDIO_CODEC);
EXPORT_SYMBOL_NS(hda_codec_jack_check, SND_SOC_SOF_HDA_AUDIO_CODEC);

#अगर IS_ENABLED(CONFIG_SND_HDA_GENERIC)
#घोषणा is_generic_config(bus) \
	((bus)->modelname && !म_भेद((bus)->modelname, "generic"))
#अन्यथा
#घोषणा is_generic_config(x)	0
#पूर्ण_अगर

/* probe inभागidual codec */
अटल पूर्णांक hda_codec_probe(काष्ठा snd_sof_dev *sdev, पूर्णांक address,
			   bool hda_codec_use_common_hdmi)
अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
	काष्ठा hdac_hda_priv *hda_priv;
	काष्ठा hda_codec *codec;
	पूर्णांक type = HDA_DEV_LEGACY;
#पूर्ण_अगर
	काष्ठा hda_bus *hbus = sof_to_hbus(sdev);
	काष्ठा hdac_device *hdev;
	u32 hda_cmd = (address << 28) | (AC_NODE_ROOT << 20) |
		(AC_VERB_PARAMETERS << 8) | AC_PAR_VENDOR_ID;
	u32 resp = -1;
	पूर्णांक ret;

	mutex_lock(&hbus->core.cmd_mutex);
	snd_hdac_bus_send_cmd(&hbus->core, hda_cmd);
	snd_hdac_bus_get_response(&hbus->core, address, &resp);
	mutex_unlock(&hbus->core.cmd_mutex);
	अगर (resp == -1)
		वापस -EIO;
	dev_dbg(sdev->dev, "HDA codec #%d probed OK: response: %x\n",
		address, resp);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
	hda_priv = devm_kzalloc(sdev->dev, माप(*hda_priv), GFP_KERNEL);
	अगर (!hda_priv)
		वापस -ENOMEM;

	hda_priv->codec.bus = hbus;
	hdev = &hda_priv->codec.core;
	codec = &hda_priv->codec;

	/* only probe ASoC codec drivers क्रम HDAC-HDMI */
	अगर (!hda_codec_use_common_hdmi && (resp & 0xFFFF0000) == IDISP_VID_INTEL)
		type = HDA_DEV_ASOC;

	ret = snd_hdac_ext_bus_device_init(&hbus->core, address, hdev, type);
	अगर (ret < 0)
		वापस ret;

	अगर ((resp & 0xFFFF0000) == IDISP_VID_INTEL) अणु
		अगर (!hdev->bus->audio_component) अणु
			dev_dbg(sdev->dev,
				"iDisp hw present but no driver\n");
			ret = -ENOENT;
			जाओ out;
		पूर्ण
		hda_priv->need_display_घातer = true;
	पूर्ण

	अगर (is_generic_config(hbus))
		codec->probe_id = HDA_CODEC_ID_GENERIC;
	अन्यथा
		codec->probe_id = 0;

	अगर (type == HDA_DEV_LEGACY) अणु
		ret = hda_codec_load_module(codec);
		/*
		 * handle ret==0 (no driver bound) as an error, but pass
		 * other वापस codes without modअगरication
		 */
		अगर (ret == 0)
			ret = -ENOENT;
	पूर्ण

out:
	अगर (ret < 0) अणु
		snd_hdac_device_unरेजिस्टर(hdev);
		put_device(&hdev->dev);
	पूर्ण
#अन्यथा
	hdev = devm_kzalloc(sdev->dev, माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;

	ret = snd_hdac_ext_bus_device_init(&hbus->core, address, hdev, HDA_DEV_ASOC);
#पूर्ण_अगर

	वापस ret;
पूर्ण

/* Codec initialization */
व्योम hda_codec_probe_bus(काष्ठा snd_sof_dev *sdev,
			 bool hda_codec_use_common_hdmi)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	पूर्णांक i, ret;

	/* probe codecs in avail slots */
	क्रम (i = 0; i < HDA_MAX_CODECS; i++) अणु

		अगर (!(bus->codec_mask & (1 << i)))
			जारी;

		ret = hda_codec_probe(sdev, i, hda_codec_use_common_hdmi);
		अगर (ret < 0) अणु
			dev_warn(bus->dev, "codec #%d probe error, ret: %d\n",
				 i, ret);
			bus->codec_mask &= ~BIT(i);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_NS(hda_codec_probe_bus, SND_SOC_SOF_HDA_AUDIO_CODEC);

#अगर IS_ENABLED(CONFIG_SND_HDA_CODEC_HDMI) || \
	IS_ENABLED(CONFIG_SND_SOC_HDAC_HDMI)

व्योम hda_codec_i915_display_घातer(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);

	अगर (HDA_IDISP_CODEC(bus->codec_mask)) अणु
		dev_dbg(bus->dev, "Turning i915 HDAC power %d\n", enable);
		snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, enable);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_NS(hda_codec_i915_display_घातer, SND_SOC_SOF_HDA_AUDIO_CODEC_I915);

पूर्णांक hda_codec_i915_init(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	पूर्णांक ret;

	/* i915 exposes a HDA codec क्रम HDMI audio */
	ret = snd_hdac_i915_init(bus);
	अगर (ret < 0)
		वापस ret;

	/* codec_mask not yet known, घातer up क्रम probe */
	snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, true);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_NS(hda_codec_i915_init, SND_SOC_SOF_HDA_AUDIO_CODEC_I915);

पूर्णांक hda_codec_i915_निकास(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);

	अगर (!bus->audio_component)
		वापस 0;

	/* घातer करोwn unconditionally */
	snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, false);

	वापस snd_hdac_i915_निकास(bus);
पूर्ण
EXPORT_SYMBOL_NS(hda_codec_i915_निकास, SND_SOC_SOF_HDA_AUDIO_CODEC_I915);

#पूर्ण_अगर

MODULE_LICENSE("Dual BSD/GPL");
