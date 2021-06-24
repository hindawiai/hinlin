<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HD-audio codec driver binding
 * Copyright (c) Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"

/*
 * find a matching codec id
 */
अटल पूर्णांक hda_codec_match(काष्ठा hdac_device *dev, काष्ठा hdac_driver *drv)
अणु
	काष्ठा hda_codec *codec = container_of(dev, काष्ठा hda_codec, core);
	काष्ठा hda_codec_driver *driver =
		container_of(drv, काष्ठा hda_codec_driver, core);
	स्थिर काष्ठा hda_device_id *list;
	/* check probe_id instead of venकरोr_id अगर set */
	u32 id = codec->probe_id ? codec->probe_id : codec->core.venकरोr_id;
	u32 rev_id = codec->core.revision_id;

	क्रम (list = driver->id; list->venकरोr_id; list++) अणु
		अगर (list->venकरोr_id == id &&
		    (!list->rev_id || list->rev_id == rev_id)) अणु
			codec->preset = list;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* process an unsolicited event */
अटल व्योम hda_codec_unsol_event(काष्ठा hdac_device *dev, अचिन्हित पूर्णांक ev)
अणु
	काष्ठा hda_codec *codec = container_of(dev, काष्ठा hda_codec, core);

	/* ignore unsol events during shutकरोwn */
	अगर (codec->bus->shutकरोwn)
		वापस;

	/* ignore unsol events during प्रणाली suspend/resume */
	अगर (codec->core.dev.घातer.घातer_state.event != PM_EVENT_ON)
		वापस;

	अगर (codec->patch_ops.unsol_event)
		codec->patch_ops.unsol_event(codec, ev);
पूर्ण

/**
 * snd_hda_codec_set_name - set the codec name
 * @codec: the HDA codec
 * @name: name string to set
 */
पूर्णांक snd_hda_codec_set_name(काष्ठा hda_codec *codec, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	अगर (!name)
		वापस 0;
	err = snd_hdac_device_set_chip_name(&codec->core, name);
	अगर (err < 0)
		वापस err;

	/* update the mixer name */
	अगर (!*codec->card->mixername ||
	    codec->bus->mixer_asचिन्हित >= codec->core.addr) अणु
		snम_लिखो(codec->card->mixername,
			 माप(codec->card->mixername), "%s %s",
			 codec->core.venकरोr_name, codec->core.chip_name);
		codec->bus->mixer_asचिन्हित = codec->core.addr;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_set_name);

अटल पूर्णांक hda_codec_driver_probe(काष्ठा device *dev)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(dev);
	काष्ठा module *owner = dev->driver->owner;
	hda_codec_patch_t patch;
	पूर्णांक err;

	अगर (codec->bus->core.ext_ops) अणु
		अगर (WARN_ON(!codec->bus->core.ext_ops->hdev_attach))
			वापस -EINVAL;
		वापस codec->bus->core.ext_ops->hdev_attach(&codec->core);
	पूर्ण

	अगर (WARN_ON(!codec->preset))
		वापस -EINVAL;

	err = snd_hda_codec_set_name(codec, codec->preset->name);
	अगर (err < 0)
		जाओ error;
	err = snd_hdac_regmap_init(&codec->core);
	अगर (err < 0)
		जाओ error;

	अगर (!try_module_get(owner)) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	patch = (hda_codec_patch_t)codec->preset->driver_data;
	अगर (patch) अणु
		err = patch(codec);
		अगर (err < 0)
			जाओ error_module_put;
	पूर्ण

	err = snd_hda_codec_build_pcms(codec);
	अगर (err < 0)
		जाओ error_module;
	err = snd_hda_codec_build_controls(codec);
	अगर (err < 0)
		जाओ error_module;
	/* only रेजिस्टर after the bus probe finished; otherwise it's racy */
	अगर (!codec->bus->bus_probing && codec->card->रेजिस्टरed) अणु
		err = snd_card_रेजिस्टर(codec->card);
		अगर (err < 0)
			जाओ error_module;
		snd_hda_codec_रेजिस्टर(codec);
	पूर्ण

	codec->core.lazy_cache = true;
	वापस 0;

 error_module:
	अगर (codec->patch_ops.मुक्त)
		codec->patch_ops.मुक्त(codec);
 error_module_put:
	module_put(owner);

 error:
	snd_hda_codec_cleanup_क्रम_unbind(codec);
	वापस err;
पूर्ण

अटल पूर्णांक hda_codec_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(dev);

	अगर (codec->bus->core.ext_ops) अणु
		अगर (WARN_ON(!codec->bus->core.ext_ops->hdev_detach))
			वापस -EINVAL;
		वापस codec->bus->core.ext_ops->hdev_detach(&codec->core);
	पूर्ण

	अगर (codec->patch_ops.मुक्त)
		codec->patch_ops.मुक्त(codec);
	snd_hda_codec_cleanup_क्रम_unbind(codec);
	module_put(dev->driver->owner);
	वापस 0;
पूर्ण

अटल व्योम hda_codec_driver_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(dev);

	अगर (!pm_runसमय_suspended(dev) && codec->patch_ops.reboot_notअगरy)
		codec->patch_ops.reboot_notअगरy(codec);
पूर्ण

पूर्णांक __hda_codec_driver_रेजिस्टर(काष्ठा hda_codec_driver *drv, स्थिर अक्षर *name,
			       काष्ठा module *owner)
अणु
	drv->core.driver.name = name;
	drv->core.driver.owner = owner;
	drv->core.driver.bus = &snd_hda_bus_type;
	drv->core.driver.probe = hda_codec_driver_probe;
	drv->core.driver.हटाओ = hda_codec_driver_हटाओ;
	drv->core.driver.shutकरोwn = hda_codec_driver_shutकरोwn;
	drv->core.driver.pm = &hda_codec_driver_pm;
	drv->core.type = HDA_DEV_LEGACY;
	drv->core.match = hda_codec_match;
	drv->core.unsol_event = hda_codec_unsol_event;
	वापस driver_रेजिस्टर(&drv->core.driver);
पूर्ण
EXPORT_SYMBOL_GPL(__hda_codec_driver_रेजिस्टर);

व्योम hda_codec_driver_unरेजिस्टर(काष्ठा hda_codec_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->core.driver);
पूर्ण
EXPORT_SYMBOL_GPL(hda_codec_driver_unरेजिस्टर);

अटल अंतरभूत bool codec_probed(काष्ठा hda_codec *codec)
अणु
	वापस device_attach(hda_codec_dev(codec)) > 0 && codec->preset;
पूर्ण

/* try to स्वतः-load codec module */
अटल व्योम request_codec_module(काष्ठा hda_codec *codec)
अणु
#अगर_घोषित MODULE
	अक्षर modalias[32];
	स्थिर अक्षर *mod = शून्य;

	चयन (codec->probe_id) अणु
	हाल HDA_CODEC_ID_GENERIC_HDMI:
#अगर IS_MODULE(CONFIG_SND_HDA_CODEC_HDMI)
		mod = "snd-hda-codec-hdmi";
#पूर्ण_अगर
		अवरोध;
	हाल HDA_CODEC_ID_GENERIC:
#अगर IS_MODULE(CONFIG_SND_HDA_GENERIC)
		mod = "snd-hda-codec-generic";
#पूर्ण_अगर
		अवरोध;
	शेष:
		snd_hdac_codec_modalias(&codec->core, modalias, माप(modalias));
		mod = modalias;
		अवरोध;
	पूर्ण

	अगर (mod)
		request_module(mod);
#पूर्ण_अगर /* MODULE */
पूर्ण

/* try to स्वतः-load and bind the codec module */
अटल व्योम codec_bind_module(काष्ठा hda_codec *codec)
अणु
#अगर_घोषित MODULE
	request_codec_module(codec);
	अगर (codec_probed(codec))
		वापस;
#पूर्ण_अगर
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_HDA_CODEC_HDMI)
/* अगर all audio out widमाला_लो are digital, let's assume the codec as a HDMI/DP */
अटल bool is_likely_hdmi_codec(काष्ठा hda_codec *codec)
अणु
	hda_nid_t nid;

	क्रम_each_hda_codec_node(nid, codec) अणु
		अचिन्हित पूर्णांक wcaps = get_wcaps(codec, nid);
		चयन (get_wcaps_type(wcaps)) अणु
		हाल AC_WID_AUD_IN:
			वापस false; /* HDMI parser supports only HDMI out */
		हाल AC_WID_AUD_OUT:
			अगर (!(wcaps & AC_WCAP_DIGITAL))
				वापस false;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण
#अन्यथा
/* no HDMI codec parser support */
#घोषणा is_likely_hdmi_codec(codec)	false
#पूर्ण_अगर /* CONFIG_SND_HDA_CODEC_HDMI */

अटल पूर्णांक codec_bind_generic(काष्ठा hda_codec *codec)
अणु
	अगर (codec->probe_id)
		वापस -ENODEV;

	अगर (is_likely_hdmi_codec(codec)) अणु
		codec->probe_id = HDA_CODEC_ID_GENERIC_HDMI;
		request_codec_module(codec);
		अगर (codec_probed(codec))
			वापस 0;
	पूर्ण

	codec->probe_id = HDA_CODEC_ID_GENERIC;
	request_codec_module(codec);
	अगर (codec_probed(codec))
		वापस 0;
	वापस -ENODEV;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_HDA_GENERIC)
#घोषणा is_generic_config(codec) \
	(codec->modelname && !म_भेद(codec->modelname, "generic"))
#अन्यथा
#घोषणा is_generic_config(codec)	0
#पूर्ण_अगर

/**
 * snd_hda_codec_configure - (Re-)configure the HD-audio codec
 * @codec: the HDA codec
 *
 * Start parsing of the given codec tree and (re-)initialize the whole
 * patch instance.
 *
 * Returns 0 अगर successful or a negative error code.
 */
पूर्णांक snd_hda_codec_configure(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	अगर (is_generic_config(codec))
		codec->probe_id = HDA_CODEC_ID_GENERIC;
	अन्यथा
		codec->probe_id = 0;

	err = snd_hdac_device_रेजिस्टर(&codec->core);
	अगर (err < 0)
		वापस err;

	अगर (!codec->preset)
		codec_bind_module(codec);
	अगर (!codec->preset) अणु
		err = codec_bind_generic(codec);
		अगर (err < 0) अणु
			codec_err(codec, "Unable to bind the codec\n");
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

 error:
	snd_hdac_device_unरेजिस्टर(&codec->core);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_configure);
