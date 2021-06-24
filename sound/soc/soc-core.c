<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-core.c  --  ALSA SoC Audio Layer
//
// Copyright 2005 Wolfson Microelectronics PLC.
// Copyright 2005 Openedhand Ltd.
// Copyright (C) 2010 Slimlogic Ltd.
// Copyright (C) 2010 Texas Instruments Inc.
//
// Author: Liam Girdwood <lrg@slimlogic.co.uk>
//         with code, comments and ideas from :-
//         Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
//
//  TODO:
//   o Add hw rules to enक्रमce rates, etc.
//   o More testing with other codecs/machines.
//   o Add more codecs and platक्रमms to ensure good API coverage.
//   o Support TDM on PCM and I2S

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dpcm.h>
#समावेश <sound/soc-topology.h>
#समावेश <sound/soc-link.h>
#समावेश <sound/initval.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/asoc.h>

अटल DEFINE_MUTEX(client_mutex);
अटल LIST_HEAD(component_list);
अटल LIST_HEAD(unbind_card_list);

#घोषणा क्रम_each_component(component)			\
	list_क्रम_each_entry(component, &component_list, list)

/*
 * This is used अगर driver करोn't need to have CPU/Codec/Platक्रमm
 * dai_link. see soc.h
 */
काष्ठा snd_soc_dai_link_component null_dailink_component[0];
EXPORT_SYMBOL_GPL(null_dailink_component);

/*
 * This is a समयout to करो a DAPM घातerकरोwn after a stream is बंदd().
 * It can be used to eliminate pops between dअगरferent playback streams, e.g.
 * between two audio tracks.
 */
अटल पूर्णांक pmकरोwn_समय = 5000;
module_param(pmकरोwn_समय, पूर्णांक, 0);
MODULE_PARM_DESC(pmकरोwn_समय, "DAPM stream powerdown time (msecs)");

अटल sमाप_प्रकार pmकरोwn_समय_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%ld\n", rtd->pmकरोwn_समय);
पूर्ण

अटल sमाप_प्रकार pmकरोwn_समय_set(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &rtd->pmकरोwn_समय);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(pmकरोwn_समय, 0644, pmकरोwn_समय_show, pmकरोwn_समय_set);

अटल काष्ठा attribute *soc_dev_attrs[] = अणु
	&dev_attr_pmकरोwn_समय.attr,
	शून्य
पूर्ण;

अटल umode_t soc_dev_attr_is_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा snd_soc_pcm_runसमय *rtd = dev_get_drvdata(dev);

	अगर (!rtd)
		वापस 0;

	अगर (attr == &dev_attr_pmकरोwn_समय.attr)
		वापस attr->mode; /* always visible */
	वापस rtd->num_codecs ? attr->mode : 0; /* enabled only with codec */
पूर्ण

अटल स्थिर काष्ठा attribute_group soc_dapm_dev_group = अणु
	.attrs = soc_dapm_dev_attrs,
	.is_visible = soc_dev_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group soc_dev_group = अणु
	.attrs = soc_dev_attrs,
	.is_visible = soc_dev_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *soc_dev_attr_groups[] = अणु
	&soc_dapm_dev_group,
	&soc_dev_group,
	शून्य
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dentry *snd_soc_debugfs_root;
EXPORT_SYMBOL_GPL(snd_soc_debugfs_root);

अटल व्योम soc_init_component_debugfs(काष्ठा snd_soc_component *component)
अणु
	अगर (!component->card->debugfs_card_root)
		वापस;

	अगर (component->debugfs_prefix) अणु
		अक्षर *name;

		name = kaप्र_लिखो(GFP_KERNEL, "%s:%s",
			component->debugfs_prefix, component->name);
		अगर (name) अणु
			component->debugfs_root = debugfs_create_dir(name,
				component->card->debugfs_card_root);
			kमुक्त(name);
		पूर्ण
	पूर्ण अन्यथा अणु
		component->debugfs_root = debugfs_create_dir(component->name,
				component->card->debugfs_card_root);
	पूर्ण

	snd_soc_dapm_debugfs_init(snd_soc_component_get_dapm(component),
		component->debugfs_root);
पूर्ण

अटल व्योम soc_cleanup_component_debugfs(काष्ठा snd_soc_component *component)
अणु
	अगर (!component->debugfs_root)
		वापस;
	debugfs_हटाओ_recursive(component->debugfs_root);
	component->debugfs_root = शून्य;
पूर्ण

अटल पूर्णांक dai_list_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *dai;

	mutex_lock(&client_mutex);

	क्रम_each_component(component)
		क्रम_each_component_dais(component, dai)
			seq_म_लिखो(m, "%s\n", dai->name);

	mutex_unlock(&client_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dai_list);

अटल पूर्णांक component_list_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा snd_soc_component *component;

	mutex_lock(&client_mutex);

	क्रम_each_component(component)
		seq_म_लिखो(m, "%s\n", component->name);

	mutex_unlock(&client_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(component_list);

अटल व्योम soc_init_card_debugfs(काष्ठा snd_soc_card *card)
अणु
	card->debugfs_card_root = debugfs_create_dir(card->name,
						     snd_soc_debugfs_root);

	debugfs_create_u32("dapm_pop_time", 0644, card->debugfs_card_root,
			   &card->pop_समय);

	snd_soc_dapm_debugfs_init(&card->dapm, card->debugfs_card_root);
पूर्ण

अटल व्योम soc_cleanup_card_debugfs(काष्ठा snd_soc_card *card)
अणु
	debugfs_हटाओ_recursive(card->debugfs_card_root);
	card->debugfs_card_root = शून्य;
पूर्ण

अटल व्योम snd_soc_debugfs_init(व्योम)
अणु
	snd_soc_debugfs_root = debugfs_create_dir("asoc", शून्य);

	debugfs_create_file("dais", 0444, snd_soc_debugfs_root, शून्य,
			    &dai_list_fops);

	debugfs_create_file("components", 0444, snd_soc_debugfs_root, शून्य,
			    &component_list_fops);
पूर्ण

अटल व्योम snd_soc_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(snd_soc_debugfs_root);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम soc_init_component_debugfs(
	काष्ठा snd_soc_component *component)
अणु
पूर्ण

अटल अंतरभूत व्योम soc_cleanup_component_debugfs(
	काष्ठा snd_soc_component *component)
अणु
पूर्ण

अटल अंतरभूत व्योम soc_init_card_debugfs(काष्ठा snd_soc_card *card)
अणु
पूर्ण

अटल अंतरभूत व्योम soc_cleanup_card_debugfs(काष्ठा snd_soc_card *card)
अणु
पूर्ण

अटल अंतरभूत व्योम snd_soc_debugfs_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम snd_soc_debugfs_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक snd_soc_rtd_add_component(काष्ठा snd_soc_pcm_runसमय *rtd,
				     काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_component *comp;
	पूर्णांक i;

	क्रम_each_rtd_components(rtd, i, comp) अणु
		/* alपढ़ोy connected */
		अगर (comp == component)
			वापस 0;
	पूर्ण

	/* see क्रम_each_rtd_components */
	rtd->components[rtd->num_components] = component;
	rtd->num_components++;

	वापस 0;
पूर्ण

काष्ठा snd_soc_component *snd_soc_rtdcom_lookup(काष्ठा snd_soc_pcm_runसमय *rtd,
						स्थिर अक्षर *driver_name)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	अगर (!driver_name)
		वापस शून्य;

	/*
	 * NOTE
	 *
	 * snd_soc_rtdcom_lookup() will find component from rtd by using
	 * specअगरied driver name.
	 * But, अगर many components which have same driver name are connected
	 * to 1 rtd, this function will वापस 1st found component.
	 */
	क्रम_each_rtd_components(rtd, i, component) अणु
		स्थिर अक्षर *component_name = component->driver->name;

		अगर (!component_name)
			जारी;

		अगर ((component_name == driver_name) ||
		    म_भेद(component_name, driver_name) == 0)
			वापस component;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_rtdcom_lookup);

काष्ठा snd_soc_component
*snd_soc_lookup_component_nolocked(काष्ठा device *dev, स्थिर अक्षर *driver_name)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_component *found_component;

	found_component = शून्य;
	क्रम_each_component(component) अणु
		अगर ((dev == component->dev) &&
		    (!driver_name ||
		     (driver_name == component->driver->name) ||
		     (म_भेद(component->driver->name, driver_name) == 0))) अणु
			found_component = component;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found_component;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_lookup_component_nolocked);

काष्ठा snd_soc_component *snd_soc_lookup_component(काष्ठा device *dev,
						   स्थिर अक्षर *driver_name)
अणु
	काष्ठा snd_soc_component *component;

	mutex_lock(&client_mutex);
	component = snd_soc_lookup_component_nolocked(dev, driver_name);
	mutex_unlock(&client_mutex);

	वापस component;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_lookup_component);

काष्ठा snd_soc_pcm_runसमय
*snd_soc_get_pcm_runसमय(काष्ठा snd_soc_card *card,
			 काष्ठा snd_soc_dai_link *dai_link)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;

	क्रम_each_card_rtds(card, rtd) अणु
		अगर (rtd->dai_link == dai_link)
			वापस rtd;
	पूर्ण
	dev_dbg(card->dev, "ASoC: failed to find rtd %s\n", dai_link->name);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_pcm_runसमय);

/*
 * Power करोwn the audio subप्रणाली pmकरोwn_समय msecs after बंद is called.
 * This is to ensure there are no pops or clicks in between any music tracks
 * due to DAPM घातer cycling.
 */
व्योम snd_soc_बंद_delayed_work(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक playback = SNDRV_PCM_STREAM_PLAYBACK;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	dev_dbg(rtd->dev,
		"ASoC: pop wq checking: %s status: %s waiting: %s\n",
		codec_dai->driver->playback.stream_name,
		snd_soc_dai_stream_active(codec_dai, playback) ?
		"active" : "inactive",
		rtd->pop_रुको ? "yes" : "no");

	/* are we रुकोing on this codec DAI stream */
	अगर (rtd->pop_रुको == 1) अणु
		rtd->pop_रुको = 0;
		snd_soc_dapm_stream_event(rtd, playback,
					  SND_SOC_DAPM_STREAM_STOP);
	पूर्ण

	mutex_unlock(&rtd->card->pcm_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_बंद_delayed_work);

अटल व्योम soc_release_rtd_dev(काष्ठा device *dev)
अणु
	/* "dev" means "rtd->dev" */
	kमुक्त(dev);
पूर्ण

अटल व्योम soc_मुक्त_pcm_runसमय(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	अगर (!rtd)
		वापस;

	list_del(&rtd->list);

	अगर (delayed_work_pending(&rtd->delayed_work))
		flush_delayed_work(&rtd->delayed_work);
	snd_soc_pcm_component_मुक्त(rtd);

	/*
	 * we करोn't need to call kमुक्त() क्रम rtd->dev
	 * see
	 *	soc_release_rtd_dev()
	 *
	 * We करोn't need rtd->dev शून्य check, because
	 * it is alloced *beक्रमe* rtd.
	 * see
	 *	soc_new_pcm_runसमय()
	 *
	 * We करोn't need to mind मुक्तing क्रम rtd,
	 * because it was created from dev (= rtd->dev)
	 * see
	 *	soc_new_pcm_runसमय()
	 *
	 *		rtd = devm_kzalloc(dev, ...);
	 *		rtd->dev = dev
	 */
	device_unरेजिस्टर(rtd->dev);
पूर्ण

अटल व्योम बंद_delayed_work(काष्ठा work_काष्ठा *work) अणु
	काष्ठा snd_soc_pcm_runसमय *rtd =
			container_of(work, काष्ठा snd_soc_pcm_runसमय,
				     delayed_work.work);

	अगर (rtd->बंद_delayed_work_func)
		rtd->बंद_delayed_work_func(rtd);
पूर्ण

अटल काष्ठा snd_soc_pcm_runसमय *soc_new_pcm_runसमय(
	काष्ठा snd_soc_card *card, काष्ठा snd_soc_dai_link *dai_link)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_component *component;
	काष्ठा device *dev;
	पूर्णांक ret;
	पूर्णांक stream;

	/*
	 * क्रम rtd->dev
	 */
	dev = kzalloc(माप(काष्ठा device), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	dev->parent	= card->dev;
	dev->release	= soc_release_rtd_dev;

	dev_set_name(dev, "%s", dai_link->name);

	ret = device_रेजिस्टर(dev);
	अगर (ret < 0) अणु
		put_device(dev); /* soc_release_rtd_dev */
		वापस शून्य;
	पूर्ण

	/*
	 * क्रम rtd
	 */
	rtd = devm_kzalloc(dev,
			   माप(*rtd) +
			   माप(*component) * (dai_link->num_cpus +
						 dai_link->num_codecs +
						 dai_link->num_platक्रमms),
			   GFP_KERNEL);
	अगर (!rtd) अणु
		device_unरेजिस्टर(dev);
		वापस शून्य;
	पूर्ण

	rtd->dev = dev;
	INIT_LIST_HEAD(&rtd->list);
	क्रम_each_pcm_streams(stream) अणु
		INIT_LIST_HEAD(&rtd->dpcm[stream].be_clients);
		INIT_LIST_HEAD(&rtd->dpcm[stream].fe_clients);
	पूर्ण
	dev_set_drvdata(dev, rtd);
	INIT_DELAYED_WORK(&rtd->delayed_work, बंद_delayed_work);

	/*
	 * क्रम rtd->dais
	 */
	rtd->dais = devm_kसुस्मृति(dev, dai_link->num_cpus + dai_link->num_codecs,
					माप(काष्ठा snd_soc_dai *),
					GFP_KERNEL);
	अगर (!rtd->dais)
		जाओ मुक्त_rtd;

	/*
	 * dais = [][][][][][][][][][][][][][][][][][]
	 *	  ^cpu_dais         ^codec_dais
	 *	  |--- num_cpus ---|--- num_codecs --|
	 * see
	 *	asoc_rtd_to_cpu()
	 *	asoc_rtd_to_codec()
	 */
	rtd->num_cpus	= dai_link->num_cpus;
	rtd->num_codecs	= dai_link->num_codecs;
	rtd->card	= card;
	rtd->dai_link	= dai_link;
	rtd->num	= card->num_rtd++;

	/* see क्रम_each_card_rtds */
	list_add_tail(&rtd->list, &card->rtd_list);

	ret = device_add_groups(dev, soc_dev_attr_groups);
	अगर (ret < 0)
		जाओ मुक्त_rtd;

	वापस rtd;

मुक्त_rtd:
	soc_मुक्त_pcm_runसमय(rtd);
	वापस शून्य;
पूर्ण

अटल व्योम snd_soc_flush_all_delayed_work(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;

	क्रम_each_card_rtds(card, rtd)
		flush_delayed_work(&rtd->delayed_work);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम soc_playback_digital_mute(काष्ठा snd_soc_card *card, पूर्णांक mute)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक playback = SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक i;

	क्रम_each_card_rtds(card, rtd) अणु

		अगर (rtd->dai_link->ignore_suspend)
			जारी;

		क्रम_each_rtd_dais(rtd, i, dai) अणु
			अगर (snd_soc_dai_stream_active(dai, playback))
				snd_soc_dai_digital_mute(dai, mute, playback);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम soc_dapm_suspend_resume(काष्ठा snd_soc_card *card, पूर्णांक event)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	पूर्णांक stream;

	क्रम_each_card_rtds(card, rtd) अणु

		अगर (rtd->dai_link->ignore_suspend)
			जारी;

		क्रम_each_pcm_streams(stream)
			snd_soc_dapm_stream_event(rtd, stream, event);
	पूर्ण
पूर्ण

/* घातers करोwn audio subप्रणाली क्रम suspend */
पूर्णांक snd_soc_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card = dev_get_drvdata(dev);
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	पूर्णांक i;

	/* If the card is not initialized yet there is nothing to करो */
	अगर (!card->instantiated)
		वापस 0;

	/*
	 * Due to the resume being scheduled पूर्णांकo a workqueue we could
	 * suspend beक्रमe that's finished - रुको क्रम it to complete.
	 */
	snd_घातer_रुको(card->snd_card, SNDRV_CTL_POWER_D0);

	/* we're going to block userspace touching us until resume completes */
	snd_घातer_change_state(card->snd_card, SNDRV_CTL_POWER_D3hot);

	/* mute any active DACs */
	soc_playback_digital_mute(card, 1);

	/* suspend all pcms */
	क्रम_each_card_rtds(card, rtd) अणु
		अगर (rtd->dai_link->ignore_suspend)
			जारी;

		snd_pcm_suspend_all(rtd->pcm);
	पूर्ण

	snd_soc_card_suspend_pre(card);

	/* बंद any रुकोing streams */
	snd_soc_flush_all_delayed_work(card);

	soc_dapm_suspend_resume(card, SND_SOC_DAPM_STREAM_SUSPEND);

	/* Recheck all endpoपूर्णांकs too, their state is affected by suspend */
	dapm_mark_endpoपूर्णांकs_dirty(card);
	snd_soc_dapm_sync(&card->dapm);

	/* suspend all COMPONENTs */
	क्रम_each_card_rtds(card, rtd) अणु

		अगर (rtd->dai_link->ignore_suspend)
			जारी;

		क्रम_each_rtd_components(rtd, i, component) अणु
			काष्ठा snd_soc_dapm_context *dapm =
				snd_soc_component_get_dapm(component);

			/*
			 * ignore अगर component was alपढ़ोy suspended
			 */
			अगर (snd_soc_component_is_suspended(component))
				जारी;

			/*
			 * If there are paths active then the COMPONENT will be
			 * held with bias _ON and should not be suspended.
			 */
			चयन (snd_soc_dapm_get_bias_level(dapm)) अणु
			हाल SND_SOC_BIAS_STANDBY:
				/*
				 * If the COMPONENT is capable of idle
				 * bias off then being in STANDBY
				 * means it's करोing something,
				 * otherwise fall through.
				 */
				अगर (dapm->idle_bias_off) अणु
					dev_dbg(component->dev,
						"ASoC: idle_bias_off CODEC on over suspend\n");
					अवरोध;
				पूर्ण
				fallthrough;

			हाल SND_SOC_BIAS_OFF:
				snd_soc_component_suspend(component);
				अगर (component->regmap)
					regcache_mark_dirty(component->regmap);
				/* deactivate pins to sleep state */
				pinctrl_pm_select_sleep_state(component->dev);
				अवरोध;
			शेष:
				dev_dbg(component->dev,
					"ASoC: COMPONENT is on over suspend\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	snd_soc_card_suspend_post(card);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_suspend);

/*
 * deferred resume work, so resume can complete beक्रमe we finished
 * setting our codec back up, which can be very slow on I2C
 */
अटल व्योम soc_resume_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_soc_card *card =
			container_of(work, काष्ठा snd_soc_card,
				     deferred_resume_work);
	काष्ठा snd_soc_component *component;

	/*
	 * our घातer state is still SNDRV_CTL_POWER_D3hot from suspend समय,
	 * so userspace apps are blocked from touching us
	 */

	dev_dbg(card->dev, "ASoC: starting resume work\n");

	/* Bring us up पूर्णांकo D2 so that DAPM starts enabling things */
	snd_घातer_change_state(card->snd_card, SNDRV_CTL_POWER_D2);

	snd_soc_card_resume_pre(card);

	क्रम_each_card_components(card, component) अणु
		अगर (snd_soc_component_is_suspended(component))
			snd_soc_component_resume(component);
	पूर्ण

	soc_dapm_suspend_resume(card, SND_SOC_DAPM_STREAM_RESUME);

	/* unmute any active DACs */
	soc_playback_digital_mute(card, 0);

	snd_soc_card_resume_post(card);

	dev_dbg(card->dev, "ASoC: resume work completed\n");

	/* Recheck all endpoपूर्णांकs too, their state is affected by suspend */
	dapm_mark_endpoपूर्णांकs_dirty(card);
	snd_soc_dapm_sync(&card->dapm);

	/* userspace can access us now we are back as we were beक्रमe */
	snd_घातer_change_state(card->snd_card, SNDRV_CTL_POWER_D0);
पूर्ण

/* घातers up audio subप्रणाली after a suspend */
पूर्णांक snd_soc_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card = dev_get_drvdata(dev);
	काष्ठा snd_soc_component *component;

	/* If the card is not initialized yet there is nothing to करो */
	अगर (!card->instantiated)
		वापस 0;

	/* activate pins from sleep state */
	क्रम_each_card_components(card, component)
		अगर (snd_soc_component_active(component))
			pinctrl_pm_select_शेष_state(component->dev);

	dev_dbg(dev, "ASoC: Scheduling resume work\n");
	अगर (!schedule_work(&card->deferred_resume_work))
		dev_err(dev, "ASoC: resume work item may be lost\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_resume);

अटल व्योम soc_resume_init(काष्ठा snd_soc_card *card)
अणु
	/* deferred resume work */
	INIT_WORK(&card->deferred_resume_work, soc_resume_deferred);
पूर्ण
#अन्यथा
#घोषणा snd_soc_suspend शून्य
#घोषणा snd_soc_resume शून्य
अटल अंतरभूत व्योम soc_resume_init(काष्ठा snd_soc_card *card)
अणु
पूर्ण
#पूर्ण_अगर

अटल काष्ठा device_node
*soc_component_to_node(काष्ठा snd_soc_component *component)
अणु
	काष्ठा device_node *of_node;

	of_node = component->dev->of_node;
	अगर (!of_node && component->dev->parent)
		of_node = component->dev->parent->of_node;

	वापस of_node;
पूर्ण

अटल पूर्णांक snd_soc_is_matching_component(
	स्थिर काष्ठा snd_soc_dai_link_component *dlc,
	काष्ठा snd_soc_component *component)
अणु
	काष्ठा device_node *component_of_node;

	अगर (!dlc)
		वापस 0;

	component_of_node = soc_component_to_node(component);

	अगर (dlc->of_node && component_of_node != dlc->of_node)
		वापस 0;
	अगर (dlc->name && म_भेद(component->name, dlc->name))
		वापस 0;

	वापस 1;
पूर्ण

अटल काष्ठा snd_soc_component *soc_find_component(
	स्थिर काष्ठा snd_soc_dai_link_component *dlc)
अणु
	काष्ठा snd_soc_component *component;

	lockdep_निश्चित_held(&client_mutex);

	/*
	 * NOTE
	 *
	 * It वापसs *1st* found component, but some driver
	 * has few components by same of_node/name
	 * ex)
	 *	CPU component and generic DMAEngine component
	 */
	क्रम_each_component(component)
		अगर (snd_soc_is_matching_component(dlc, component))
			वापस component;

	वापस शून्य;
पूर्ण

/**
 * snd_soc_find_dai - Find a रेजिस्टरed DAI
 *
 * @dlc: name of the DAI or the DAI driver and optional component info to match
 *
 * This function will search all रेजिस्टरed components and their DAIs to
 * find the DAI of the same name. The component's of_node and name
 * should also match अगर being specअगरied.
 *
 * Return: poपूर्णांकer of DAI, or शून्य अगर not found.
 */
काष्ठा snd_soc_dai *snd_soc_find_dai(
	स्थिर काष्ठा snd_soc_dai_link_component *dlc)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *dai;

	lockdep_निश्चित_held(&client_mutex);

	/* Find CPU DAI from रेजिस्टरed DAIs */
	क्रम_each_component(component) अणु
		अगर (!snd_soc_is_matching_component(dlc, component))
			जारी;
		क्रम_each_component_dais(component, dai) अणु
			अगर (dlc->dai_name && म_भेद(dai->name, dlc->dai_name)
			    && (!dai->driver->name
				|| म_भेद(dai->driver->name, dlc->dai_name)))
				जारी;

			वापस dai;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_find_dai);

काष्ठा snd_soc_dai *snd_soc_find_dai_with_mutex(
	स्थिर काष्ठा snd_soc_dai_link_component *dlc)
अणु
	काष्ठा snd_soc_dai *dai;

	mutex_lock(&client_mutex);
	dai = snd_soc_find_dai(dlc);
	mutex_unlock(&client_mutex);

	वापस dai;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_find_dai_with_mutex);

अटल पूर्णांक soc_dai_link_sanity_check(काष्ठा snd_soc_card *card,
				     काष्ठा snd_soc_dai_link *link)
अणु
	पूर्णांक i;
	काष्ठा snd_soc_dai_link_component *cpu, *codec, *platक्रमm;

	क्रम_each_link_codecs(link, i, codec) अणु
		/*
		 * Codec must be specअगरied by 1 of name or OF node,
		 * not both or neither.
		 */
		अगर (!!codec->name == !!codec->of_node) अणु
			dev_err(card->dev, "ASoC: Neither/both codec name/of_node are set for %s\n",
				link->name);
			वापस -EINVAL;
		पूर्ण

		/* Codec DAI name must be specअगरied */
		अगर (!codec->dai_name) अणु
			dev_err(card->dev, "ASoC: codec_dai_name not set for %s\n",
				link->name);
			वापस -EINVAL;
		पूर्ण

		/*
		 * Defer card registration अगर codec component is not added to
		 * component list.
		 */
		अगर (!soc_find_component(codec)) अणु
			dev_dbg(card->dev,
				"ASoC: codec component %s not found for link %s\n",
				codec->name, link->name);
			वापस -EPROBE_DEFER;
		पूर्ण
	पूर्ण

	क्रम_each_link_platक्रमms(link, i, platक्रमm) अणु
		/*
		 * Platक्रमm may be specअगरied by either name or OF node, but it
		 * can be left unspecअगरied, then no components will be inserted
		 * in the rtdcom list
		 */
		अगर (!!platक्रमm->name == !!platक्रमm->of_node) अणु
			dev_err(card->dev,
				"ASoC: Neither/both platform name/of_node are set for %s\n",
				link->name);
			वापस -EINVAL;
		पूर्ण

		/*
		 * Defer card registration अगर platक्रमm component is not added to
		 * component list.
		 */
		अगर (!soc_find_component(platक्रमm)) अणु
			dev_dbg(card->dev,
				"ASoC: platform component %s not found for link %s\n",
				platक्रमm->name, link->name);
			वापस -EPROBE_DEFER;
		पूर्ण
	पूर्ण

	क्रम_each_link_cpus(link, i, cpu) अणु
		/*
		 * CPU device may be specअगरied by either name or OF node, but
		 * can be left unspecअगरied, and will be matched based on DAI
		 * name alone..
		 */
		अगर (cpu->name && cpu->of_node) अणु
			dev_err(card->dev,
				"ASoC: Neither/both cpu name/of_node are set for %s\n",
				link->name);
			वापस -EINVAL;
		पूर्ण

		/*
		 * Defer card registration अगर cpu dai component is not added to
		 * component list.
		 */
		अगर ((cpu->of_node || cpu->name) &&
		    !soc_find_component(cpu)) अणु
			dev_dbg(card->dev,
				"ASoC: cpu component %s not found for link %s\n",
				cpu->name, link->name);
			वापस -EPROBE_DEFER;
		पूर्ण

		/*
		 * At least one of CPU DAI name or CPU device name/node must be
		 * specअगरied
		 */
		अगर (!cpu->dai_name &&
		    !(cpu->name || cpu->of_node)) अणु
			dev_err(card->dev,
				"ASoC: Neither cpu_dai_name nor cpu_name/of_node are set for %s\n",
				link->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * snd_soc_हटाओ_pcm_runसमय - Remove a pcm_runसमय from card
 * @card: The ASoC card to which the pcm_runसमय has
 * @rtd: The pcm_runसमय to हटाओ
 *
 * This function हटाओs a pcm_runसमय from the ASoC card.
 */
व्योम snd_soc_हटाओ_pcm_runसमय(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	lockdep_निश्चित_held(&client_mutex);

	/* release machine specअगरic resources */
	snd_soc_link_निकास(rtd);

	/*
	 * Notअगरy the machine driver क्रम extra deकाष्ठाion
	 */
	snd_soc_card_हटाओ_dai_link(card, rtd->dai_link);

	soc_मुक्त_pcm_runसमय(rtd);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_हटाओ_pcm_runसमय);

/**
 * snd_soc_add_pcm_runसमय - Add a pcm_runसमय dynamically via dai_link
 * @card: The ASoC card to which the pcm_runसमय is added
 * @dai_link: The DAI link to find pcm_runसमय
 *
 * This function adds a pcm_runसमय ASoC card by using dai_link.
 *
 * Note: Topology can use this API to add pcm_runसमय when probing the
 * topology component. And machine drivers can still define अटल
 * DAI links in dai_link array.
 */
पूर्णांक snd_soc_add_pcm_runसमय(काष्ठा snd_soc_card *card,
			    काष्ठा snd_soc_dai_link *dai_link)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai_link_component *codec, *platक्रमm, *cpu;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	lockdep_निश्चित_held(&client_mutex);

	/*
	 * Notअगरy the machine driver क्रम extra initialization
	 */
	ret = snd_soc_card_add_dai_link(card, dai_link);
	अगर (ret < 0)
		वापस ret;

	अगर (dai_link->ignore)
		वापस 0;

	dev_dbg(card->dev, "ASoC: binding %s\n", dai_link->name);

	ret = soc_dai_link_sanity_check(card, dai_link);
	अगर (ret < 0)
		वापस ret;

	rtd = soc_new_pcm_runसमय(card, dai_link);
	अगर (!rtd)
		वापस -ENOMEM;

	क्रम_each_link_cpus(dai_link, i, cpu) अणु
		asoc_rtd_to_cpu(rtd, i) = snd_soc_find_dai(cpu);
		अगर (!asoc_rtd_to_cpu(rtd, i)) अणु
			dev_info(card->dev, "ASoC: CPU DAI %s not registered\n",
				 cpu->dai_name);
			जाओ _err_defer;
		पूर्ण
		snd_soc_rtd_add_component(rtd, asoc_rtd_to_cpu(rtd, i)->component);
	पूर्ण

	/* Find CODEC from रेजिस्टरed CODECs */
	क्रम_each_link_codecs(dai_link, i, codec) अणु
		asoc_rtd_to_codec(rtd, i) = snd_soc_find_dai(codec);
		अगर (!asoc_rtd_to_codec(rtd, i)) अणु
			dev_info(card->dev, "ASoC: CODEC DAI %s not registered\n",
				 codec->dai_name);
			जाओ _err_defer;
		पूर्ण

		snd_soc_rtd_add_component(rtd, asoc_rtd_to_codec(rtd, i)->component);
	पूर्ण

	/* Find PLATFORM from रेजिस्टरed PLATFORMs */
	क्रम_each_link_platक्रमms(dai_link, i, platक्रमm) अणु
		क्रम_each_component(component) अणु
			अगर (!snd_soc_is_matching_component(platक्रमm, component))
				जारी;

			snd_soc_rtd_add_component(rtd, component);
		पूर्ण
	पूर्ण

	वापस 0;

_err_defer:
	snd_soc_हटाओ_pcm_runसमय(card, rtd);
	वापस -EPROBE_DEFER;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_add_pcm_runसमय);

अटल पूर्णांक soc_init_pcm_runसमय(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai_link *dai_link = rtd->dai_link;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_component *component;
	पूर्णांक ret, num, i;

	/* set शेष घातer off समयout */
	rtd->pmकरोwn_समय = pmकरोwn_समय;

	/* करो machine specअगरic initialization */
	ret = snd_soc_link_init(rtd);
	अगर (ret < 0)
		वापस ret;

	अगर (dai_link->dai_fmt) अणु
		ret = snd_soc_runसमय_set_dai_fmt(rtd, dai_link->dai_fmt);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* add DPCM sysfs entries */
	soc_dpcm_debugfs_add(rtd);

	num = rtd->num;

	/*
	 * most drivers will रेजिस्टर their PCMs using DAI link ordering but
	 * topology based drivers can use the DAI link id field to set PCM
	 * device number and then use rtd + a base offset of the BEs.
	 */
	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (!component->driver->use_dai_pcm_id)
			जारी;

		अगर (rtd->dai_link->no_pcm)
			num += component->driver->be_pcm_base;
		अन्यथा
			num = rtd->dai_link->id;
	पूर्ण

	/* create compress_device अगर possible */
	ret = snd_soc_dai_compress_new(cpu_dai, rtd, num);
	अगर (ret != -ENOTSUPP)
		वापस ret;

	/* create the pcm */
	ret = soc_new_pcm(rtd, num);
	अगर (ret < 0) अणु
		dev_err(card->dev, "ASoC: can't create pcm %s :%d\n",
			dai_link->stream_name, ret);
		वापस ret;
	पूर्ण

	वापस snd_soc_pcm_dai_new(rtd);
पूर्ण

अटल व्योम soc_set_name_prefix(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_component *component)
अणु
	काष्ठा device_node *of_node = soc_component_to_node(component);
	स्थिर अक्षर *str;
	पूर्णांक ret, i;

	क्रम (i = 0; i < card->num_configs; i++) अणु
		काष्ठा snd_soc_codec_conf *map = &card->codec_conf[i];

		अगर (snd_soc_is_matching_component(&map->dlc, component) &&
		    map->name_prefix) अणु
			component->name_prefix = map->name_prefix;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * If there is no configuration table or no match in the table,
	 * check अगर a prefix is provided in the node
	 */
	ret = of_property_पढ़ो_string(of_node, "sound-name-prefix", &str);
	अगर (ret < 0)
		वापस;

	component->name_prefix = str;
पूर्ण

अटल व्योम soc_हटाओ_component(काष्ठा snd_soc_component *component,
				 पूर्णांक probed)
अणु

	अगर (!component->card)
		वापस;

	अगर (probed)
		snd_soc_component_हटाओ(component);

	/* For framework level robustness */
	snd_soc_component_set_jack(component, शून्य, शून्य);

	list_del_init(&component->card_list);
	snd_soc_dapm_मुक्त(snd_soc_component_get_dapm(component));
	soc_cleanup_component_debugfs(component);
	component->card = शून्य;
	snd_soc_component_module_put_when_हटाओ(component);
पूर्ण

अटल पूर्णांक soc_probe_component(काष्ठा snd_soc_card *card,
			       काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा snd_soc_dai *dai;
	पूर्णांक probed = 0;
	पूर्णांक ret;

	अगर (snd_soc_component_is_dummy(component))
		वापस 0;

	अगर (component->card) अणु
		अगर (component->card != card) अणु
			dev_err(component->dev,
				"Trying to bind component to card \"%s\" but is already bound to card \"%s\"\n",
				card->name, component->card->name);
			वापस -ENODEV;
		पूर्ण
		वापस 0;
	पूर्ण

	ret = snd_soc_component_module_get_when_probe(component);
	अगर (ret < 0)
		वापस ret;

	component->card = card;
	soc_set_name_prefix(card, component);

	soc_init_component_debugfs(component);

	snd_soc_dapm_init(dapm, card, component);

	ret = snd_soc_dapm_new_controls(dapm,
					component->driver->dapm_widमाला_लो,
					component->driver->num_dapm_widमाला_लो);

	अगर (ret != 0) अणु
		dev_err(component->dev,
			"Failed to create new controls %d\n", ret);
		जाओ err_probe;
	पूर्ण

	क्रम_each_component_dais(component, dai) अणु
		ret = snd_soc_dapm_new_dai_widमाला_लो(dapm, dai);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to create DAI widgets %d\n", ret);
			जाओ err_probe;
		पूर्ण
	पूर्ण

	ret = snd_soc_component_probe(component);
	अगर (ret < 0)
		जाओ err_probe;

	WARN(dapm->idle_bias_off &&
	     dapm->bias_level != SND_SOC_BIAS_OFF,
	     "codec %s can not start from non-off bias with idle_bias_off==1\n",
	     component->name);
	probed = 1;

	/*
	 * machine specअगरic init
	 * see
	 *	snd_soc_component_set_aux()
	 */
	ret = snd_soc_component_init(component);
	अगर (ret < 0)
		जाओ err_probe;

	ret = snd_soc_add_component_controls(component,
					     component->driver->controls,
					     component->driver->num_controls);
	अगर (ret < 0)
		जाओ err_probe;

	ret = snd_soc_dapm_add_routes(dapm,
				      component->driver->dapm_routes,
				      component->driver->num_dapm_routes);
	अगर (ret < 0) अणु
		अगर (card->disable_route_checks) अणु
			dev_info(card->dev,
				 "%s: disable_route_checks set, ignoring errors on add_routes\n",
				 __func__);
		पूर्ण अन्यथा अणु
			dev_err(card->dev,
				"%s: snd_soc_dapm_add_routes failed: %d\n",
				__func__, ret);
			जाओ err_probe;
		पूर्ण
	पूर्ण

	/* see क्रम_each_card_components */
	list_add(&component->card_list, &card->component_dev_list);

err_probe:
	अगर (ret < 0)
		soc_हटाओ_component(component, probed);

	वापस ret;
पूर्ण

अटल व्योम soc_हटाओ_link_dais(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	पूर्णांक order;

	क्रम_each_comp_order(order) अणु
		क्रम_each_card_rtds(card, rtd) अणु
			/* हटाओ all rtd connected DAIs in good order */
			snd_soc_pcm_dai_हटाओ(rtd, order);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक soc_probe_link_dais(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	पूर्णांक order, ret;

	क्रम_each_comp_order(order) अणु
		क्रम_each_card_rtds(card, rtd) अणु

			dev_dbg(card->dev,
				"ASoC: probe %s dai link %d late %d\n",
				card->name, rtd->num, order);

			/* probe all rtd connected DAIs in good order */
			ret = snd_soc_pcm_dai_probe(rtd, order);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम soc_हटाओ_link_components(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	पूर्णांक i, order;

	क्रम_each_comp_order(order) अणु
		क्रम_each_card_rtds(card, rtd) अणु
			क्रम_each_rtd_components(rtd, i, component) अणु
				अगर (component->driver->हटाओ_order != order)
					जारी;

				soc_हटाओ_component(component, 1);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक soc_probe_link_components(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	पूर्णांक i, ret, order;

	क्रम_each_comp_order(order) अणु
		क्रम_each_card_rtds(card, rtd) अणु
			क्रम_each_rtd_components(rtd, i, component) अणु
				अगर (component->driver->probe_order != order)
					जारी;

				ret = soc_probe_component(card, component);
				अगर (ret < 0)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम soc_unbind_aux_dev(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component, *_component;

	क्रम_each_card_auxs_safe(card, component, _component) अणु
		/* क्रम snd_soc_component_init() */
		snd_soc_component_set_aux(component, शून्य);
		list_del(&component->card_aux_list);
	पूर्ण
पूर्ण

अटल पूर्णांक soc_bind_aux_dev(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_aux_dev *aux;
	पूर्णांक i;

	क्रम_each_card_pre_auxs(card, i, aux) अणु
		/* codecs, usually analog devices */
		component = soc_find_component(&aux->dlc);
		अगर (!component)
			वापस -EPROBE_DEFER;

		/* क्रम snd_soc_component_init() */
		snd_soc_component_set_aux(component, aux);
		/* see क्रम_each_card_auxs */
		list_add(&component->card_aux_list, &card->aux_comp_list);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक soc_probe_aux_devices(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक order;
	पूर्णांक ret;

	क्रम_each_comp_order(order) अणु
		क्रम_each_card_auxs(card, component) अणु
			अगर (component->driver->probe_order != order)
				जारी;

			ret = soc_probe_component(card,	component);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम soc_हटाओ_aux_devices(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *comp, *_comp;
	पूर्णांक order;

	क्रम_each_comp_order(order) अणु
		क्रम_each_card_auxs_safe(card, comp, _comp) अणु
			अगर (comp->driver->हटाओ_order == order)
				soc_हटाओ_component(comp, 1);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * snd_soc_runसमय_set_dai_fmt() - Change DAI link क्रमmat क्रम a ASoC runसमय
 * @rtd: The runसमय क्रम which the DAI link क्रमmat should be changed
 * @dai_fmt: The new DAI link क्रमmat
 *
 * This function updates the DAI link क्रमmat क्रम all DAIs connected to the DAI
 * link क्रम the specअगरied runसमय.
 *
 * Note: For setups with a अटल क्रमmat set the dai_fmt field in the
 * corresponding snd_dai_link काष्ठा instead of using this function.
 *
 * Returns 0 on success, otherwise a negative error code.
 */
पूर्णांक snd_soc_runसमय_set_dai_fmt(काष्ठा snd_soc_pcm_runसमय *rtd,
	अचिन्हित पूर्णांक dai_fmt)
अणु
	काष्ठा snd_soc_dai *cpu_dai;
	काष्ठा snd_soc_dai *codec_dai;
	अचिन्हित पूर्णांक inv_dai_fmt;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_fmt(codec_dai, dai_fmt);
		अगर (ret != 0 && ret != -ENOTSUPP)
			वापस ret;
	पूर्ण

	/*
	 * Flip the polarity क्रम the "CPU" end of a CODEC<->CODEC link
	 * the component which has non_legacy_dai_naming is Codec
	 */
	inv_dai_fmt = dai_fmt & ~SND_SOC_DAIFMT_MASTER_MASK;
	चयन (dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		inv_dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		inv_dai_fmt |= SND_SOC_DAIFMT_CBS_CFM;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		inv_dai_fmt |= SND_SOC_DAIFMT_CBM_CFS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		inv_dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
		अवरोध;
	पूर्ण
	क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
		अचिन्हित पूर्णांक fmt = dai_fmt;

		अगर (cpu_dai->component->driver->non_legacy_dai_naming)
			fmt = inv_dai_fmt;

		ret = snd_soc_dai_set_fmt(cpu_dai, fmt);
		अगर (ret != 0 && ret != -ENOTSUPP)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_runसमय_set_dai_fmt);

#अगर_घोषित CONFIG_DMI
/*
 * If a DMI filed contain strings in this blacklist (e.g.
 * "Type2 - Board Manufacturer" or "Type1 - TBD by OEM"), it will be taken
 * as invalid and dropped when setting the card दीर्घ name from DMI info.
 */
अटल स्थिर अक्षर * स्थिर dmi_blacklist[] = अणु
	"To be filled by OEM",
	"TBD by OEM",
	"Default String",
	"Board Manufacturer",
	"Board Vendor Name",
	"Board Product Name",
	शून्य,	/* terminator */
पूर्ण;

/*
 * Trim special अक्षरacters, and replace '-' with '_' since '-' is used to
 * separate dअगरferent DMI fields in the card दीर्घ name. Only number and
 * alphabet अक्षरacters and a few separator अक्षरacters are kept.
 */
अटल व्योम cleanup_dmi_name(अक्षर *name)
अणु
	पूर्णांक i, j = 0;

	क्रम (i = 0; name[i]; i++) अणु
		अगर (है_अक्षर_अंक(name[i]) || (name[i] == '.')
		    || (name[i] == '_'))
			name[j++] = name[i];
		अन्यथा अगर (name[i] == '-')
			name[j++] = '_';
	पूर्ण

	name[j] = '\0';
पूर्ण

/*
 * Check अगर a DMI field is valid, i.e. not containing any string
 * in the black list.
 */
अटल पूर्णांक is_dmi_valid(स्थिर अक्षर *field)
अणु
	पूर्णांक i = 0;

	जबतक (dmi_blacklist[i]) अणु
		अगर (म_माला(field, dmi_blacklist[i]))
			वापस 0;
		i++;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Append a string to card->dmi_दीर्घname with अक्षरacter cleanups.
 */
अटल व्योम append_dmi_string(काष्ठा snd_soc_card *card, स्थिर अक्षर *str)
अणु
	अक्षर *dst = card->dmi_दीर्घname;
	माप_प्रकार dst_len = माप(card->dmi_दीर्घname);
	माप_प्रकार len;

	len = म_माप(dst);
	snम_लिखो(dst + len, dst_len - len, "-%s", str);

	len++;	/* skip the separator "-" */
	अगर (len < dst_len)
		cleanup_dmi_name(dst + len);
पूर्ण

/**
 * snd_soc_set_dmi_name() - Register DMI names to card
 * @card: The card to रेजिस्टर DMI names
 * @flavour: The flavour "differentiator" क्रम the card amongst its peers.
 *
 * An Intel machine driver may be used by many dअगरferent devices but are
 * dअगरficult क्रम userspace to dअगरferentiate, since machine drivers ususally
 * use their own name as the card लघु name and leave the card दीर्घ name
 * blank. To dअगरferentiate such devices and fix bugs due to lack of
 * device-specअगरic configurations, this function allows DMI info to be used
 * as the sound card दीर्घ name, in the क्रमmat of
 * "vendor-product-version-board"
 * (Character '-' is used to separate dअगरferent DMI fields here).
 * This will help the user space to load the device-specअगरic Use Case Manager
 * (UCM) configurations क्रम the card.
 *
 * Possible card दीर्घ names may be:
 * DellInc.-XPS139343-01-0310JH
 * ASUSTeKCOMPUTERINC.-T100TA-1.0-T100TA
 * Circuitco-MinnowboardMaxD0PLATFORM-D0-MinnowBoardMAX
 *
 * This function also supports flavoring the card दीर्घname to provide
 * the extra dअगरferentiation, like "vendor-product-version-board-flavor".
 *
 * We only keep number and alphabet अक्षरacters and a few separator अक्षरacters
 * in the card दीर्घ name since UCM in the user space uses the card दीर्घ names
 * as card configuration directory names and AuकरोConf cannot support special
 * अक्षरactors like SPACE.
 *
 * Returns 0 on success, otherwise a negative error code.
 */
पूर्णांक snd_soc_set_dmi_name(काष्ठा snd_soc_card *card, स्थिर अक्षर *flavour)
अणु
	स्थिर अक्षर *venकरोr, *product, *product_version, *board;

	अगर (card->दीर्घ_name)
		वापस 0; /* दीर्घ name alपढ़ोy set by driver or from DMI */

	अगर (!dmi_available)
		वापस 0;

	/* make up dmi दीर्घ name as: venकरोr-product-version-board */
	venकरोr = dmi_get_प्रणाली_info(DMI_BOARD_VENDOR);
	अगर (!venकरोr || !is_dmi_valid(venकरोr)) अणु
		dev_warn(card->dev, "ASoC: no DMI vendor name!\n");
		वापस 0;
	पूर्ण

	snम_लिखो(card->dmi_दीर्घname, माप(card->dmi_दीर्घname), "%s", venकरोr);
	cleanup_dmi_name(card->dmi_दीर्घname);

	product = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (product && is_dmi_valid(product)) अणु
		append_dmi_string(card, product);

		/*
		 * some venकरोrs like Lenovo may only put a self-explanatory
		 * name in the product version field
		 */
		product_version = dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION);
		अगर (product_version && is_dmi_valid(product_version))
			append_dmi_string(card, product_version);
	पूर्ण

	board = dmi_get_प्रणाली_info(DMI_BOARD_NAME);
	अगर (board && is_dmi_valid(board)) अणु
		अगर (!product || strहालcmp(board, product))
			append_dmi_string(card, board);
	पूर्ण अन्यथा अगर (!product) अणु
		/* fall back to using legacy name */
		dev_warn(card->dev, "ASoC: no DMI board/product name!\n");
		वापस 0;
	पूर्ण

	/* Add flavour to dmi दीर्घ name */
	अगर (flavour)
		append_dmi_string(card, flavour);

	/* set the card दीर्घ name */
	card->दीर्घ_name = card->dmi_दीर्घname;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_set_dmi_name);
#पूर्ण_अगर /* CONFIG_DMI */

अटल व्योम soc_check_tplg_fes(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;
	स्थिर काष्ठा snd_soc_component_driver *comp_drv;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक i;

	क्रम_each_component(component) अणु

		/* करोes this component override BEs ? */
		अगर (!component->driver->ignore_machine)
			जारी;

		/* क्रम this machine ? */
		अगर (!म_भेद(component->driver->ignore_machine,
			    card->dev->driver->name))
			जाओ match;
		अगर (म_भेद(component->driver->ignore_machine,
			   dev_name(card->dev)))
			जारी;
match:
		/* machine matches, so override the rtd data */
		क्रम_each_card_prelinks(card, i, dai_link) अणु

			/* ignore this FE */
			अगर (dai_link->dynamic) अणु
				dai_link->ignore = true;
				जारी;
			पूर्ण

			dev_dbg(card->dev, "info: override BE DAI link %s\n",
				card->dai_link[i].name);

			/* override platक्रमm component */
			अगर (!dai_link->platक्रमms) अणु
				dev_err(card->dev, "init platform error");
				जारी;
			पूर्ण

			अगर (component->dev->of_node)
				dai_link->platक्रमms->of_node = component->dev->of_node;
			अन्यथा
				dai_link->platक्रमms->name = component->name;

			/* convert non BE पूर्णांकo BE */
			अगर (!dai_link->no_pcm) अणु
				dai_link->no_pcm = 1;

				अगर (dai_link->dpcm_playback)
					dev_warn(card->dev,
						 "invalid configuration, dailink %s has flags no_pcm=0 and dpcm_playback=1\n",
						 dai_link->name);
				अगर (dai_link->dpcm_capture)
					dev_warn(card->dev,
						 "invalid configuration, dailink %s has flags no_pcm=0 and dpcm_capture=1\n",
						 dai_link->name);

				/* convert normal link पूर्णांकo DPCM one */
				अगर (!(dai_link->dpcm_playback ||
				      dai_link->dpcm_capture)) अणु
					dai_link->dpcm_playback = !dai_link->capture_only;
					dai_link->dpcm_capture = !dai_link->playback_only;
				पूर्ण
			पूर्ण

			/*
			 * override any BE fixups
			 * see
			 *	snd_soc_link_be_hw_params_fixup()
			 */
			dai_link->be_hw_params_fixup =
				component->driver->be_hw_params_fixup;

			/*
			 * most BE links करोn't set stream name, so set it to
			 * dai link name अगर it's शून्य to help bind widमाला_लो.
			 */
			अगर (!dai_link->stream_name)
				dai_link->stream_name = dai_link->name;
		पूर्ण

		/* Inक्रमm userspace we are using alternate topology */
		अगर (component->driver->topology_name_prefix) अणु

			/* topology लघुname created? */
			अगर (!card->topology_लघुname_created) अणु
				comp_drv = component->driver;

				snम_लिखो(card->topology_लघुname, 32, "%s-%s",
					 comp_drv->topology_name_prefix,
					 card->name);
				card->topology_लघुname_created = true;
			पूर्ण

			/* use topology लघुname */
			card->name = card->topology_लघुname;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा soc_setup_card_name(name, name1, name2, norm)		\
	__soc_setup_card_name(name, माप(name), name1, name2, norm)
अटल व्योम __soc_setup_card_name(अक्षर *name, पूर्णांक len,
				  स्थिर अक्षर *name1, स्थिर अक्षर *name2,
				  पूर्णांक normalization)
अणु
	पूर्णांक i;

	snम_लिखो(name, len, "%s", name1 ? name1 : name2);

	अगर (!normalization)
		वापस;

	/*
	 * Name normalization
	 *
	 * The driver name is somewhat special, as it's used as a key क्रम
	 * searches in the user-space.
	 *
	 * ex)
	 *	"abcd??efg" -> "abcd__efg"
	 */
	क्रम (i = 0; i < len; i++) अणु
		चयन (name[i]) अणु
		हाल '_':
		हाल '-':
		हाल '\0':
			अवरोध;
		शेष:
			अगर (!है_अक्षर_अंक(name[i]))
				name[i] = '_';
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम soc_cleanup_card_resources(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd, *n;

	अगर (card->snd_card)
		snd_card_disconnect_sync(card->snd_card);

	snd_soc_dapm_shutकरोwn(card);

	/* हटाओ and मुक्त each DAI */
	soc_हटाओ_link_dais(card);
	soc_हटाओ_link_components(card);

	क्रम_each_card_rtds_safe(card, rtd, n)
		snd_soc_हटाओ_pcm_runसमय(card, rtd);

	/* हटाओ auxiliary devices */
	soc_हटाओ_aux_devices(card);
	soc_unbind_aux_dev(card);

	snd_soc_dapm_मुक्त(&card->dapm);
	soc_cleanup_card_debugfs(card);

	/* हटाओ the card */
	snd_soc_card_हटाओ(card);

	अगर (card->snd_card) अणु
		snd_card_मुक्त(card->snd_card);
		card->snd_card = शून्य;
	पूर्ण
पूर्ण

अटल व्योम snd_soc_unbind_card(काष्ठा snd_soc_card *card, bool unरेजिस्टर)
अणु
	अगर (card->instantiated) अणु
		card->instantiated = false;
		snd_soc_flush_all_delayed_work(card);

		soc_cleanup_card_resources(card);
		अगर (!unरेजिस्टर)
			list_add(&card->list, &unbind_card_list);
	पूर्ण अन्यथा अणु
		अगर (unरेजिस्टर)
			list_del(&card->list);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_soc_bind_card(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक ret, i;

	mutex_lock(&client_mutex);
	mutex_lock_nested(&card->mutex, SND_SOC_CARD_CLASS_INIT);

	snd_soc_dapm_init(&card->dapm, card, शून्य);

	/* check whether any platक्रमm is ignore machine FE and using topology */
	soc_check_tplg_fes(card);

	/* bind aux_devs too */
	ret = soc_bind_aux_dev(card);
	अगर (ret < 0)
		जाओ probe_end;

	/* add predefined DAI links to the list */
	card->num_rtd = 0;
	क्रम_each_card_prelinks(card, i, dai_link) अणु
		ret = snd_soc_add_pcm_runसमय(card, dai_link);
		अगर (ret < 0)
			जाओ probe_end;
	पूर्ण

	/* card bind complete so रेजिस्टर a sound card */
	ret = snd_card_new(card->dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			card->owner, 0, &card->snd_card);
	अगर (ret < 0) अणु
		dev_err(card->dev,
			"ASoC: can't create sound card for card %s: %d\n",
			card->name, ret);
		जाओ probe_end;
	पूर्ण

	soc_init_card_debugfs(card);

	soc_resume_init(card);

	ret = snd_soc_dapm_new_controls(&card->dapm, card->dapm_widमाला_लो,
					card->num_dapm_widमाला_लो);
	अगर (ret < 0)
		जाओ probe_end;

	ret = snd_soc_dapm_new_controls(&card->dapm, card->of_dapm_widमाला_लो,
					card->num_of_dapm_widमाला_लो);
	अगर (ret < 0)
		जाओ probe_end;

	/* initialise the sound card only once */
	ret = snd_soc_card_probe(card);
	अगर (ret < 0)
		जाओ probe_end;

	/* probe all components used by DAI links on this card */
	ret = soc_probe_link_components(card);
	अगर (ret < 0) अणु
		dev_err(card->dev,
			"ASoC: failed to instantiate card %d\n", ret);
		जाओ probe_end;
	पूर्ण

	/* probe auxiliary components */
	ret = soc_probe_aux_devices(card);
	अगर (ret < 0) अणु
		dev_err(card->dev,
			"ASoC: failed to probe aux component %d\n", ret);
		जाओ probe_end;
	पूर्ण

	/* probe all DAI links on this card */
	ret = soc_probe_link_dais(card);
	अगर (ret < 0) अणु
		dev_err(card->dev,
			"ASoC: failed to instantiate card %d\n", ret);
		जाओ probe_end;
	पूर्ण

	क्रम_each_card_rtds(card, rtd) अणु
		ret = soc_init_pcm_runसमय(card, rtd);
		अगर (ret < 0)
			जाओ probe_end;
	पूर्ण

	snd_soc_dapm_link_dai_widमाला_लो(card);
	snd_soc_dapm_connect_dai_link_widमाला_लो(card);

	ret = snd_soc_add_card_controls(card, card->controls,
					card->num_controls);
	अगर (ret < 0)
		जाओ probe_end;

	ret = snd_soc_dapm_add_routes(&card->dapm, card->dapm_routes,
				      card->num_dapm_routes);
	अगर (ret < 0) अणु
		अगर (card->disable_route_checks) अणु
			dev_info(card->dev,
				 "%s: disable_route_checks set, ignoring errors on add_routes\n",
				 __func__);
		पूर्ण अन्यथा अणु
			dev_err(card->dev,
				 "%s: snd_soc_dapm_add_routes failed: %d\n",
				 __func__, ret);
			जाओ probe_end;
		पूर्ण
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, card->of_dapm_routes,
				      card->num_of_dapm_routes);
	अगर (ret < 0)
		जाओ probe_end;

	/* try to set some sane दीर्घname अगर DMI is available */
	snd_soc_set_dmi_name(card, शून्य);

	soc_setup_card_name(card->snd_card->लघुname,
			    card->name, शून्य, 0);
	soc_setup_card_name(card->snd_card->दीर्घname,
			    card->दीर्घ_name, card->name, 0);
	soc_setup_card_name(card->snd_card->driver,
			    card->driver_name, card->name, 1);

	अगर (card->components) अणु
		/* the current implementation of snd_component_add() accepts */
		/* multiple components in the string separated by space, */
		/* but the string collision (identical string) check might */
		/* not work correctly */
		ret = snd_component_add(card->snd_card, card->components);
		अगर (ret < 0) अणु
			dev_err(card->dev, "ASoC: %s snd_component_add() failed: %d\n",
				card->name, ret);
			जाओ probe_end;
		पूर्ण
	पूर्ण

	ret = snd_soc_card_late_probe(card);
	अगर (ret < 0)
		जाओ probe_end;

	snd_soc_dapm_new_widमाला_लो(card);

	ret = snd_card_रेजिस्टर(card->snd_card);
	अगर (ret < 0) अणु
		dev_err(card->dev, "ASoC: failed to register soundcard %d\n",
				ret);
		जाओ probe_end;
	पूर्ण

	card->instantiated = 1;
	dapm_mark_endpoपूर्णांकs_dirty(card);
	snd_soc_dapm_sync(&card->dapm);

	/* deactivate pins to sleep state */
	क्रम_each_card_components(card, component)
		अगर (!snd_soc_component_active(component))
			pinctrl_pm_select_sleep_state(component->dev);

probe_end:
	अगर (ret < 0)
		soc_cleanup_card_resources(card);

	mutex_unlock(&card->mutex);
	mutex_unlock(&client_mutex);

	वापस ret;
पूर्ण

/* probes a new socdev */
अटल पूर्णांक soc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	/*
	 * no card, so machine driver should be रेजिस्टरing card
	 * we should not be here in that हाल so ret error
	 */
	अगर (!card)
		वापस -EINVAL;

	dev_warn(&pdev->dev,
		 "ASoC: machine %s should use snd_soc_register_card()\n",
		 card->name);

	/* Bodge जबतक we unpick instantiation */
	card->dev = &pdev->dev;

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

पूर्णांक snd_soc_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card = dev_get_drvdata(dev);
	काष्ठा snd_soc_component *component;

	अगर (!card->instantiated)
		वापस 0;

	/*
	 * Flush out pmकरोwn_समय work - we actually करो want to run it
	 * now, we're shutting करोwn so no imminent restart.
	 */
	snd_soc_flush_all_delayed_work(card);

	snd_soc_dapm_shutकरोwn(card);

	/* deactivate pins to sleep state */
	क्रम_each_card_components(card, component)
		pinctrl_pm_select_sleep_state(component->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_घातeroff);

स्थिर काष्ठा dev_pm_ops snd_soc_pm_ops = अणु
	.suspend = snd_soc_suspend,
	.resume = snd_soc_resume,
	.मुक्तze = snd_soc_suspend,
	.thaw = snd_soc_resume,
	.घातeroff = snd_soc_घातeroff,
	.restore = snd_soc_resume,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_pm_ops);

/* ASoC platक्रमm driver */
अटल काष्ठा platक्रमm_driver soc_driver = अणु
	.driver		= अणु
		.name		= "soc-audio",
		.pm		= &snd_soc_pm_ops,
	पूर्ण,
	.probe		= soc_probe,
पूर्ण;

/**
 * snd_soc_cnew - create new control
 * @_ढाँचा: control ढाँचा
 * @data: control निजी data
 * @दीर्घ_name: control दीर्घ name
 * @prefix: control name prefix
 *
 * Create a new mixer control from a ढाँचा control.
 *
 * Returns 0 क्रम success, अन्यथा error.
 */
काष्ठा snd_kcontrol *snd_soc_cnew(स्थिर काष्ठा snd_kcontrol_new *_ढाँचा,
				  व्योम *data, स्थिर अक्षर *दीर्घ_name,
				  स्थिर अक्षर *prefix)
अणु
	काष्ठा snd_kcontrol_new ढाँचा;
	काष्ठा snd_kcontrol *kcontrol;
	अक्षर *name = शून्य;

	स_नकल(&ढाँचा, _ढाँचा, माप(ढाँचा));
	ढाँचा.index = 0;

	अगर (!दीर्घ_name)
		दीर्घ_name = ढाँचा.name;

	अगर (prefix) अणु
		name = kaप्र_लिखो(GFP_KERNEL, "%s %s", prefix, दीर्घ_name);
		अगर (!name)
			वापस शून्य;

		ढाँचा.name = name;
	पूर्ण अन्यथा अणु
		ढाँचा.name = दीर्घ_name;
	पूर्ण

	kcontrol = snd_ctl_new1(&ढाँचा, data);

	kमुक्त(name);

	वापस kcontrol;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_cnew);

अटल पूर्णांक snd_soc_add_controls(काष्ठा snd_card *card, काष्ठा device *dev,
	स्थिर काष्ठा snd_kcontrol_new *controls, पूर्णांक num_controls,
	स्थिर अक्षर *prefix, व्योम *data)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < num_controls; i++) अणु
		स्थिर काष्ठा snd_kcontrol_new *control = &controls[i];

		err = snd_ctl_add(card, snd_soc_cnew(control, data,
						     control->name, prefix));
		अगर (err < 0) अणु
			dev_err(dev, "ASoC: Failed to add %s: %d\n",
				control->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * snd_soc_add_component_controls - Add an array of controls to a component.
 *
 * @component: Component to add controls to
 * @controls: Array of controls to add
 * @num_controls: Number of elements in the array
 *
 * Return: 0 क्रम success, अन्यथा error.
 */
पूर्णांक snd_soc_add_component_controls(काष्ठा snd_soc_component *component,
	स्थिर काष्ठा snd_kcontrol_new *controls, अचिन्हित पूर्णांक num_controls)
अणु
	काष्ठा snd_card *card = component->card->snd_card;

	वापस snd_soc_add_controls(card, component->dev, controls,
			num_controls, component->name_prefix, component);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_add_component_controls);

/**
 * snd_soc_add_card_controls - add an array of controls to a SoC card.
 * Convenience function to add a list of controls.
 *
 * @soc_card: SoC card to add controls to
 * @controls: array of controls to add
 * @num_controls: number of elements in the array
 *
 * Return 0 क्रम success, अन्यथा error.
 */
पूर्णांक snd_soc_add_card_controls(काष्ठा snd_soc_card *soc_card,
	स्थिर काष्ठा snd_kcontrol_new *controls, पूर्णांक num_controls)
अणु
	काष्ठा snd_card *card = soc_card->snd_card;

	वापस snd_soc_add_controls(card, soc_card->dev, controls, num_controls,
			शून्य, soc_card);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_add_card_controls);

/**
 * snd_soc_add_dai_controls - add an array of controls to a DAI.
 * Convienience function to add a list of controls.
 *
 * @dai: DAI to add controls to
 * @controls: array of controls to add
 * @num_controls: number of elements in the array
 *
 * Return 0 क्रम success, अन्यथा error.
 */
पूर्णांक snd_soc_add_dai_controls(काष्ठा snd_soc_dai *dai,
	स्थिर काष्ठा snd_kcontrol_new *controls, पूर्णांक num_controls)
अणु
	काष्ठा snd_card *card = dai->component->card->snd_card;

	वापस snd_soc_add_controls(card, dai->dev, controls, num_controls,
			शून्य, dai);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_add_dai_controls);

/**
 * snd_soc_रेजिस्टर_card - Register a card with the ASoC core
 *
 * @card: Card to रेजिस्टर
 *
 */
पूर्णांक snd_soc_रेजिस्टर_card(काष्ठा snd_soc_card *card)
अणु
	अगर (!card->name || !card->dev)
		वापस -EINVAL;

	dev_set_drvdata(card->dev, card);

	INIT_LIST_HEAD(&card->widमाला_लो);
	INIT_LIST_HEAD(&card->paths);
	INIT_LIST_HEAD(&card->dapm_list);
	INIT_LIST_HEAD(&card->aux_comp_list);
	INIT_LIST_HEAD(&card->component_dev_list);
	INIT_LIST_HEAD(&card->list);
	INIT_LIST_HEAD(&card->rtd_list);
	INIT_LIST_HEAD(&card->dapm_dirty);
	INIT_LIST_HEAD(&card->करोbj_list);

	card->instantiated = 0;
	mutex_init(&card->mutex);
	mutex_init(&card->dapm_mutex);
	mutex_init(&card->pcm_mutex);
	spin_lock_init(&card->dpcm_lock);

	वापस snd_soc_bind_card(card);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_रेजिस्टर_card);

/**
 * snd_soc_unरेजिस्टर_card - Unरेजिस्टर a card with the ASoC core
 *
 * @card: Card to unरेजिस्टर
 *
 */
पूर्णांक snd_soc_unरेजिस्टर_card(काष्ठा snd_soc_card *card)
अणु
	mutex_lock(&client_mutex);
	snd_soc_unbind_card(card, true);
	mutex_unlock(&client_mutex);
	dev_dbg(card->dev, "ASoC: Unregistered card '%s'\n", card->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_unरेजिस्टर_card);

/*
 * Simplअगरy DAI link configuration by removing ".-1" from device names
 * and sanitizing names.
 */
अटल अक्षर *fmt_single_name(काष्ठा device *dev, पूर्णांक *id)
अणु
	स्थिर अक्षर *devname = dev_name(dev);
	अक्षर *found, *name;
	अचिन्हित पूर्णांक id1, id2;

	अगर (devname == शून्य)
		वापस शून्य;

	name = devm_kstrdup(dev, devname, GFP_KERNEL);
	अगर (!name)
		वापस शून्य;

	/* are we a "%s.%d" name (platक्रमm and SPI components) */
	found = म_माला(name, dev->driver->name);
	अगर (found) अणु
		/* get ID */
		अगर (माला_पूछो(&found[म_माप(dev->driver->name)], ".%d", id) == 1) अणु

			/* discard ID from name अगर ID == -1 */
			अगर (*id == -1)
				found[म_माप(dev->driver->name)] = '\0';
		पूर्ण

	/* I2C component devices are named "bus-addr" */
	पूर्ण अन्यथा अगर (माला_पूछो(name, "%x-%x", &id1, &id2) == 2) अणु

		/* create unique ID number from I2C addr and bus */
		*id = ((id1 & 0xffff) << 16) + id2;

		devm_kमुक्त(dev, name);

		/* sanitize component name क्रम DAI link creation */
		name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s.%s", dev->driver->name, devname);
	पूर्ण अन्यथा अणु
		*id = 0;
	पूर्ण

	वापस name;
पूर्ण

/*
 * Simplअगरy DAI link naming क्रम single devices with multiple DAIs by removing
 * any ".-1" and using the DAI name (instead of device name).
 */
अटल अंतरभूत अक्षर *fmt_multiple_name(काष्ठा device *dev,
		काष्ठा snd_soc_dai_driver *dai_drv)
अणु
	अगर (dai_drv->name == शून्य) अणु
		dev_err(dev,
			"ASoC: error - multiple DAI %s registered with no name\n",
			dev_name(dev));
		वापस शून्य;
	पूर्ण

	वापस devm_kstrdup(dev, dai_drv->name, GFP_KERNEL);
पूर्ण

व्योम snd_soc_unरेजिस्टर_dai(काष्ठा snd_soc_dai *dai)
अणु
	dev_dbg(dai->dev, "ASoC: Unregistered DAI '%s'\n", dai->name);
	list_del(&dai->list);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_unरेजिस्टर_dai);

/**
 * snd_soc_रेजिस्टर_dai - Register a DAI dynamically & create its widमाला_लो
 *
 * @component: The component the DAIs are रेजिस्टरed क्रम
 * @dai_drv: DAI driver to use क्रम the DAI
 * @legacy_dai_naming: अगर %true, use legacy single-name क्रमmat;
 * 	अगर %false, use multiple-name क्रमmat;
 *
 * Topology can use this API to रेजिस्टर DAIs when probing a component.
 * These DAIs's widमाला_लो will be मुक्तd in the card cleanup and the DAIs
 * will be मुक्तd in the component cleanup.
 */
काष्ठा snd_soc_dai *snd_soc_रेजिस्टर_dai(काष्ठा snd_soc_component *component,
					 काष्ठा snd_soc_dai_driver *dai_drv,
					 bool legacy_dai_naming)
अणु
	काष्ठा device *dev = component->dev;
	काष्ठा snd_soc_dai *dai;

	dev_dbg(dev, "ASoC: dynamically register DAI %s\n", dev_name(dev));

	lockdep_निश्चित_held(&client_mutex);

	dai = devm_kzalloc(dev, माप(*dai), GFP_KERNEL);
	अगर (dai == शून्य)
		वापस शून्य;

	/*
	 * Back in the old days when we still had component-less DAIs,
	 * instead of having a अटल name, component-less DAIs would
	 * inherit the name of the parent device so it is possible to
	 * रेजिस्टर multiple instances of the DAI. We still need to keep
	 * the same naming style even though those DAIs are not
	 * component-less anymore.
	 */
	अगर (legacy_dai_naming &&
	    (dai_drv->id == 0 || dai_drv->name == शून्य)) अणु
		dai->name = fmt_single_name(dev, &dai->id);
	पूर्ण अन्यथा अणु
		dai->name = fmt_multiple_name(dev, dai_drv);
		अगर (dai_drv->id)
			dai->id = dai_drv->id;
		अन्यथा
			dai->id = component->num_dai;
	पूर्ण
	अगर (!dai->name)
		वापस शून्य;

	dai->component = component;
	dai->dev = dev;
	dai->driver = dai_drv;

	/* see क्रम_each_component_dais */
	list_add_tail(&dai->list, &component->dai_list);
	component->num_dai++;

	dev_dbg(dev, "ASoC: Registered DAI '%s'\n", dai->name);
	वापस dai;
पूर्ण

/**
 * snd_soc_unरेजिस्टर_dais - Unरेजिस्टर DAIs from the ASoC core
 *
 * @component: The component क्रम which the DAIs should be unरेजिस्टरed
 */
अटल व्योम snd_soc_unरेजिस्टर_dais(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dai *dai, *_dai;

	क्रम_each_component_dais_safe(component, dai, _dai)
		snd_soc_unरेजिस्टर_dai(dai);
पूर्ण

/**
 * snd_soc_रेजिस्टर_dais - Register a DAI with the ASoC core
 *
 * @component: The component the DAIs are रेजिस्टरed क्रम
 * @dai_drv: DAI driver to use क्रम the DAIs
 * @count: Number of DAIs
 */
अटल पूर्णांक snd_soc_रेजिस्टर_dais(काष्ठा snd_soc_component *component,
				 काष्ठा snd_soc_dai_driver *dai_drv,
				 माप_प्रकार count)
अणु
	काष्ठा snd_soc_dai *dai;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < count; i++) अणु
		dai = snd_soc_रेजिस्टर_dai(component, dai_drv + i, count == 1 &&
				  !component->driver->non_legacy_dai_naming);
		अगर (dai == शून्य) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	snd_soc_unरेजिस्टर_dais(component);

	वापस ret;
पूर्ण

#घोषणा ENDIANNESS_MAP(name) \
	(SNDRV_PCM_FMTBIT_##name##LE | SNDRV_PCM_FMTBIT_##name##BE)
अटल u64 endianness_क्रमmat_map[] = अणु
	ENDIANNESS_MAP(S16_),
	ENDIANNESS_MAP(U16_),
	ENDIANNESS_MAP(S24_),
	ENDIANNESS_MAP(U24_),
	ENDIANNESS_MAP(S32_),
	ENDIANNESS_MAP(U32_),
	ENDIANNESS_MAP(S24_3),
	ENDIANNESS_MAP(U24_3),
	ENDIANNESS_MAP(S20_3),
	ENDIANNESS_MAP(U20_3),
	ENDIANNESS_MAP(S18_3),
	ENDIANNESS_MAP(U18_3),
	ENDIANNESS_MAP(FLOAT_),
	ENDIANNESS_MAP(FLOAT64_),
	ENDIANNESS_MAP(IEC958_SUBFRAME_),
पूर्ण;

/*
 * Fix up the DAI क्रमmats क्रम endianness: codecs करोn't actually see
 * the endianness of the data but we're using the CPU क्रमmat
 * definitions which करो need to include endianness so we ensure that
 * codec DAIs always have both big and little endian variants set.
 */
अटल व्योम convert_endianness_क्रमmats(काष्ठा snd_soc_pcm_stream *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(endianness_क्रमmat_map); i++)
		अगर (stream->क्रमmats & endianness_क्रमmat_map[i])
			stream->क्रमmats |= endianness_क्रमmat_map[i];
पूर्ण

अटल व्योम snd_soc_try_rebind_card(व्योम)
अणु
	काष्ठा snd_soc_card *card, *c;

	list_क्रम_each_entry_safe(card, c, &unbind_card_list, list)
		अगर (!snd_soc_bind_card(card))
			list_del(&card->list);
पूर्ण

अटल व्योम snd_soc_del_component_unlocked(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_card *card = component->card;

	snd_soc_unरेजिस्टर_dais(component);

	अगर (card)
		snd_soc_unbind_card(card, false);

	list_del(&component->list);
पूर्ण

पूर्णांक snd_soc_component_initialize(काष्ठा snd_soc_component *component,
				 स्थिर काष्ठा snd_soc_component_driver *driver,
				 काष्ठा device *dev)
अणु
	INIT_LIST_HEAD(&component->dai_list);
	INIT_LIST_HEAD(&component->करोbj_list);
	INIT_LIST_HEAD(&component->card_list);
	mutex_init(&component->io_mutex);

	component->name = fmt_single_name(dev, &component->id);
	अगर (!component->name) अणु
		dev_err(dev, "ASoC: Failed to allocate name\n");
		वापस -ENOMEM;
	पूर्ण

	component->dev		= dev;
	component->driver	= driver;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_initialize);

पूर्णांक snd_soc_add_component(काष्ठा snd_soc_component *component,
			  काष्ठा snd_soc_dai_driver *dai_drv,
			  पूर्णांक num_dai)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&client_mutex);

	अगर (component->driver->endianness) अणु
		क्रम (i = 0; i < num_dai; i++) अणु
			convert_endianness_क्रमmats(&dai_drv[i].playback);
			convert_endianness_क्रमmats(&dai_drv[i].capture);
		पूर्ण
	पूर्ण

	ret = snd_soc_रेजिस्टर_dais(component, dai_drv, num_dai);
	अगर (ret < 0) अणु
		dev_err(component->dev, "ASoC: Failed to register DAIs: %d\n",
			ret);
		जाओ err_cleanup;
	पूर्ण

	अगर (!component->driver->ग_लिखो && !component->driver->पढ़ो) अणु
		अगर (!component->regmap)
			component->regmap = dev_get_regmap(component->dev,
							   शून्य);
		अगर (component->regmap)
			snd_soc_component_setup_regmap(component);
	पूर्ण

	/* see क्रम_each_component */
	list_add(&component->list, &component_list);

err_cleanup:
	अगर (ret < 0)
		snd_soc_del_component_unlocked(component);

	mutex_unlock(&client_mutex);

	अगर (ret == 0)
		snd_soc_try_rebind_card();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_add_component);

पूर्णांक snd_soc_रेजिस्टर_component(काष्ठा device *dev,
			स्थिर काष्ठा snd_soc_component_driver *component_driver,
			काष्ठा snd_soc_dai_driver *dai_drv,
			पूर्णांक num_dai)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक ret;

	component = devm_kzalloc(dev, माप(*component), GFP_KERNEL);
	अगर (!component)
		वापस -ENOMEM;

	ret = snd_soc_component_initialize(component, component_driver, dev);
	अगर (ret < 0)
		वापस ret;

	वापस snd_soc_add_component(component, dai_drv, num_dai);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_रेजिस्टर_component);

/**
 * snd_soc_unरेजिस्टर_component_by_driver - Unरेजिस्टर component using a given driver
 * from the ASoC core
 *
 * @dev: The device to unरेजिस्टर
 * @component_driver: The component driver to unरेजिस्टर
 */
व्योम snd_soc_unरेजिस्टर_component_by_driver(काष्ठा device *dev,
					    स्थिर काष्ठा snd_soc_component_driver *component_driver)
अणु
	काष्ठा snd_soc_component *component;

	अगर (!component_driver)
		वापस;

	mutex_lock(&client_mutex);
	component = snd_soc_lookup_component_nolocked(dev, component_driver->name);
	अगर (!component)
		जाओ out;

	snd_soc_del_component_unlocked(component);

out:
	mutex_unlock(&client_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_unरेजिस्टर_component_by_driver);

/**
 * snd_soc_unरेजिस्टर_component - Unरेजिस्टर all related component
 * from the ASoC core
 *
 * @dev: The device to unरेजिस्टर
 */
व्योम snd_soc_unरेजिस्टर_component(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_component *component;

	mutex_lock(&client_mutex);
	जबतक (1) अणु
		component = snd_soc_lookup_component_nolocked(dev, शून्य);
		अगर (!component)
			अवरोध;

		snd_soc_del_component_unlocked(component);
	पूर्ण
	mutex_unlock(&client_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_unरेजिस्टर_component);

/* Retrieve a card's name from device tree */
पूर्णांक snd_soc_of_parse_card_name(काष्ठा snd_soc_card *card,
			       स्थिर अक्षर *propname)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret;

	अगर (!card->dev) अणु
		pr_err("card->dev is not set before calling %s\n", __func__);
		वापस -EINVAL;
	पूर्ण

	np = card->dev->of_node;

	ret = of_property_पढ़ो_string_index(np, propname, 0, &card->name);
	/*
	 * EINVAL means the property करोes not exist. This is fine providing
	 * card->name was previously set, which is checked later in
	 * snd_soc_रेजिस्टर_card.
	 */
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(card->dev,
			"ASoC: Property '%s' could not be read: %d\n",
			propname, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_parse_card_name);

अटल स्थिर काष्ठा snd_soc_dapm_widget simple_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("Microphone", शून्य),
	SND_SOC_DAPM_LINE("Line", शून्य),
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
पूर्ण;

पूर्णांक snd_soc_of_parse_audio_simple_widमाला_लो(काष्ठा snd_soc_card *card,
					  स्थिर अक्षर *propname)
अणु
	काष्ठा device_node *np = card->dev->of_node;
	काष्ठा snd_soc_dapm_widget *widमाला_लो;
	स्थिर अक्षर *ढाँचा, *wname;
	पूर्णांक i, j, num_widमाला_लो, ret;

	num_widमाला_लो = of_property_count_strings(np, propname);
	अगर (num_widमाला_लो < 0) अणु
		dev_err(card->dev,
			"ASoC: Property '%s' does not exist\n",	propname);
		वापस -EINVAL;
	पूर्ण
	अगर (num_widमाला_लो & 1) अणु
		dev_err(card->dev,
			"ASoC: Property '%s' length is not even\n", propname);
		वापस -EINVAL;
	पूर्ण

	num_widमाला_लो /= 2;
	अगर (!num_widमाला_लो) अणु
		dev_err(card->dev, "ASoC: Property '%s's length is zero\n",
			propname);
		वापस -EINVAL;
	पूर्ण

	widमाला_लो = devm_kसुस्मृति(card->dev, num_widमाला_लो, माप(*widमाला_लो),
			       GFP_KERNEL);
	अगर (!widमाला_लो) अणु
		dev_err(card->dev,
			"ASoC: Could not allocate memory for widgets\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < num_widमाला_लो; i++) अणु
		ret = of_property_पढ़ो_string_index(np, propname,
			2 * i, &ढाँचा);
		अगर (ret) अणु
			dev_err(card->dev,
				"ASoC: Property '%s' index %d read error:%d\n",
				propname, 2 * i, ret);
			वापस -EINVAL;
		पूर्ण

		क्रम (j = 0; j < ARRAY_SIZE(simple_widमाला_लो); j++) अणु
			अगर (!म_भेदन(ढाँचा, simple_widमाला_लो[j].name,
				     म_माप(simple_widमाला_लो[j].name))) अणु
				widमाला_लो[i] = simple_widमाला_लो[j];
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (j >= ARRAY_SIZE(simple_widमाला_लो)) अणु
			dev_err(card->dev,
				"ASoC: DAPM widget '%s' is not supported\n",
				ढाँचा);
			वापस -EINVAL;
		पूर्ण

		ret = of_property_पढ़ो_string_index(np, propname,
						    (2 * i) + 1,
						    &wname);
		अगर (ret) अणु
			dev_err(card->dev,
				"ASoC: Property '%s' index %d read error:%d\n",
				propname, (2 * i) + 1, ret);
			वापस -EINVAL;
		पूर्ण

		widमाला_लो[i].name = wname;
	पूर्ण

	card->of_dapm_widमाला_लो = widमाला_लो;
	card->num_of_dapm_widमाला_लो = num_widमाला_लो;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_parse_audio_simple_widमाला_लो);

पूर्णांक snd_soc_of_get_slot_mask(काष्ठा device_node *np,
			     स्थिर अक्षर *prop_name,
			     अचिन्हित पूर्णांक *mask)
अणु
	u32 val;
	स्थिर __be32 *of_slot_mask = of_get_property(np, prop_name, &val);
	पूर्णांक i;

	अगर (!of_slot_mask)
		वापस 0;
	val /= माप(u32);
	क्रम (i = 0; i < val; i++)
		अगर (be32_to_cpup(&of_slot_mask[i]))
			*mask |= (1 << i);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_get_slot_mask);

पूर्णांक snd_soc_of_parse_tdm_slot(काष्ठा device_node *np,
			      अचिन्हित पूर्णांक *tx_mask,
			      अचिन्हित पूर्णांक *rx_mask,
			      अचिन्हित पूर्णांक *slots,
			      अचिन्हित पूर्णांक *slot_width)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (tx_mask)
		snd_soc_of_get_slot_mask(np, "dai-tdm-slot-tx-mask", tx_mask);
	अगर (rx_mask)
		snd_soc_of_get_slot_mask(np, "dai-tdm-slot-rx-mask", rx_mask);

	अगर (of_property_पढ़ो_bool(np, "dai-tdm-slot-num")) अणु
		ret = of_property_पढ़ो_u32(np, "dai-tdm-slot-num", &val);
		अगर (ret)
			वापस ret;

		अगर (slots)
			*slots = val;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "dai-tdm-slot-width")) अणु
		ret = of_property_पढ़ो_u32(np, "dai-tdm-slot-width", &val);
		अगर (ret)
			वापस ret;

		अगर (slot_width)
			*slot_width = val;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_parse_tdm_slot);

व्योम snd_soc_of_parse_node_prefix(काष्ठा device_node *np,
				  काष्ठा snd_soc_codec_conf *codec_conf,
				  काष्ठा device_node *of_node,
				  स्थिर अक्षर *propname)
अणु
	स्थिर अक्षर *str;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string(np, propname, &str);
	अगर (ret < 0) अणु
		/* no prefix is not error */
		वापस;
	पूर्ण

	codec_conf->dlc.of_node	= of_node;
	codec_conf->name_prefix	= str;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_parse_node_prefix);

पूर्णांक snd_soc_of_parse_audio_routing(काष्ठा snd_soc_card *card,
				   स्थिर अक्षर *propname)
अणु
	काष्ठा device_node *np = card->dev->of_node;
	पूर्णांक num_routes;
	काष्ठा snd_soc_dapm_route *routes;
	पूर्णांक i, ret;

	num_routes = of_property_count_strings(np, propname);
	अगर (num_routes < 0 || num_routes & 1) अणु
		dev_err(card->dev,
			"ASoC: Property '%s' does not exist or its length is not even\n",
			propname);
		वापस -EINVAL;
	पूर्ण
	num_routes /= 2;

	routes = devm_kसुस्मृति(card->dev, num_routes, माप(*routes),
			      GFP_KERNEL);
	अगर (!routes) अणु
		dev_err(card->dev,
			"ASoC: Could not allocate DAPM route table\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_routes; i++) अणु
		ret = of_property_पढ़ो_string_index(np, propname,
			2 * i, &routes[i].sink);
		अगर (ret) अणु
			dev_err(card->dev,
				"ASoC: Property '%s' index %d could not be read: %d\n",
				propname, 2 * i, ret);
			वापस -EINVAL;
		पूर्ण
		ret = of_property_पढ़ो_string_index(np, propname,
			(2 * i) + 1, &routes[i].source);
		अगर (ret) अणु
			dev_err(card->dev,
				"ASoC: Property '%s' index %d could not be read: %d\n",
				propname, (2 * i) + 1, ret);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	card->num_of_dapm_routes = num_routes;
	card->of_dapm_routes = routes;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_parse_audio_routing);

पूर्णांक snd_soc_of_parse_aux_devs(काष्ठा snd_soc_card *card, स्थिर अक्षर *propname)
अणु
	काष्ठा device_node *node = card->dev->of_node;
	काष्ठा snd_soc_aux_dev *aux;
	पूर्णांक num, i;

	num = of_count_phandle_with_args(node, propname, शून्य);
	अगर (num == -ENOENT) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (num < 0) अणु
		dev_err(card->dev, "ASOC: Property '%s' could not be read: %d\n",
			propname, num);
		वापस num;
	पूर्ण

	aux = devm_kसुस्मृति(card->dev, num, माप(*aux), GFP_KERNEL);
	अगर (!aux)
		वापस -ENOMEM;
	card->aux_dev = aux;
	card->num_aux_devs = num;

	क्रम_each_card_pre_auxs(card, i, aux) अणु
		aux->dlc.of_node = of_parse_phandle(node, propname, i);
		अगर (!aux->dlc.of_node)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_parse_aux_devs);

अचिन्हित पूर्णांक snd_soc_of_parse_daअगरmt(काष्ठा device_node *np,
				     स्थिर अक्षर *prefix,
				     काष्ठा device_node **bitclkmaster,
				     काष्ठा device_node **framemaster)
अणु
	पूर्णांक ret, i;
	अक्षर prop[128];
	अचिन्हित पूर्णांक क्रमmat = 0;
	पूर्णांक bit, frame;
	स्थिर अक्षर *str;
	काष्ठा अणु
		अक्षर *name;
		अचिन्हित पूर्णांक val;
	पूर्ण of_fmt_table[] = अणु
		अणु "i2s",	SND_SOC_DAIFMT_I2S पूर्ण,
		अणु "right_j",	SND_SOC_DAIFMT_RIGHT_J पूर्ण,
		अणु "left_j",	SND_SOC_DAIFMT_LEFT_J पूर्ण,
		अणु "dsp_a",	SND_SOC_DAIFMT_DSP_A पूर्ण,
		अणु "dsp_b",	SND_SOC_DAIFMT_DSP_B पूर्ण,
		अणु "ac97",	SND_SOC_DAIFMT_AC97 पूर्ण,
		अणु "pdm",	SND_SOC_DAIFMT_PDMपूर्ण,
		अणु "msb",	SND_SOC_DAIFMT_MSB पूर्ण,
		अणु "lsb",	SND_SOC_DAIFMT_LSB पूर्ण,
	पूर्ण;

	अगर (!prefix)
		prefix = "";

	/*
	 * check "dai-format = xxx"
	 * or    "[prefix]format = xxx"
	 * SND_SOC_DAIFMT_FORMAT_MASK area
	 */
	ret = of_property_पढ़ो_string(np, "dai-format", &str);
	अगर (ret < 0) अणु
		snम_लिखो(prop, माप(prop), "%sformat", prefix);
		ret = of_property_पढ़ो_string(np, prop, &str);
	पूर्ण
	अगर (ret == 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(of_fmt_table); i++) अणु
			अगर (म_भेद(str, of_fmt_table[i].name) == 0) अणु
				क्रमmat |= of_fmt_table[i].val;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * check "[prefix]continuous-clock"
	 * SND_SOC_DAIFMT_CLOCK_MASK area
	 */
	snम_लिखो(prop, माप(prop), "%scontinuous-clock", prefix);
	अगर (of_property_पढ़ो_bool(np, prop))
		क्रमmat |= SND_SOC_DAIFMT_CONT;
	अन्यथा
		क्रमmat |= SND_SOC_DAIFMT_GATED;

	/*
	 * check "[prefix]bitclock-inversion"
	 * check "[prefix]frame-inversion"
	 * SND_SOC_DAIFMT_INV_MASK area
	 */
	snम_लिखो(prop, माप(prop), "%sbitclock-inversion", prefix);
	bit = !!of_get_property(np, prop, शून्य);

	snम_लिखो(prop, माप(prop), "%sframe-inversion", prefix);
	frame = !!of_get_property(np, prop, शून्य);

	चयन ((bit << 4) + frame) अणु
	हाल 0x11:
		क्रमmat |= SND_SOC_DAIFMT_IB_IF;
		अवरोध;
	हाल 0x10:
		क्रमmat |= SND_SOC_DAIFMT_IB_NF;
		अवरोध;
	हाल 0x01:
		क्रमmat |= SND_SOC_DAIFMT_NB_IF;
		अवरोध;
	शेष:
		/* SND_SOC_DAIFMT_NB_NF is शेष */
		अवरोध;
	पूर्ण

	/*
	 * check "[prefix]bitclock-master"
	 * check "[prefix]frame-master"
	 * SND_SOC_DAIFMT_MASTER_MASK area
	 */
	snम_लिखो(prop, माप(prop), "%sbitclock-master", prefix);
	bit = !!of_get_property(np, prop, शून्य);
	अगर (bit && bitclkmaster)
		*bitclkmaster = of_parse_phandle(np, prop, 0);

	snम_लिखो(prop, माप(prop), "%sframe-master", prefix);
	frame = !!of_get_property(np, prop, शून्य);
	अगर (frame && framemaster)
		*framemaster = of_parse_phandle(np, prop, 0);

	चयन ((bit << 4) + frame) अणु
	हाल 0x11:
		क्रमmat |= SND_SOC_DAIFMT_CBM_CFM;
		अवरोध;
	हाल 0x10:
		क्रमmat |= SND_SOC_DAIFMT_CBM_CFS;
		अवरोध;
	हाल 0x01:
		क्रमmat |= SND_SOC_DAIFMT_CBS_CFM;
		अवरोध;
	शेष:
		क्रमmat |= SND_SOC_DAIFMT_CBS_CFS;
		अवरोध;
	पूर्ण

	वापस क्रमmat;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_parse_daअगरmt);

पूर्णांक snd_soc_get_dai_id(काष्ठा device_node *ep)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai_link_component dlc;
	पूर्णांक ret;

	dlc.of_node	= of_graph_get_port_parent(ep);
	dlc.name	= शून्य;
	/*
	 * For example HDMI हाल, HDMI has video/sound port,
	 * but ALSA SoC needs sound port number only.
	 * Thus counting HDMI DT port/endpoपूर्णांक करोesn't work.
	 * Then, it should have .of_xlate_dai_id
	 */
	ret = -ENOTSUPP;
	mutex_lock(&client_mutex);
	component = soc_find_component(&dlc);
	अगर (component)
		ret = snd_soc_component_of_xlate_dai_id(component, ep);
	mutex_unlock(&client_mutex);

	of_node_put(dlc.of_node);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_dai_id);

पूर्णांक snd_soc_get_dai_name(स्थिर काष्ठा of_phandle_args *args,
				स्थिर अक्षर **dai_name)
अणु
	काष्ठा snd_soc_component *pos;
	काष्ठा device_node *component_of_node;
	पूर्णांक ret = -EPROBE_DEFER;

	mutex_lock(&client_mutex);
	क्रम_each_component(pos) अणु
		component_of_node = soc_component_to_node(pos);

		अगर (component_of_node != args->np)
			जारी;

		ret = snd_soc_component_of_xlate_dai_name(pos, args, dai_name);
		अगर (ret == -ENOTSUPP) अणु
			काष्ठा snd_soc_dai *dai;
			पूर्णांक id = -1;

			चयन (args->args_count) अणु
			हाल 0:
				id = 0; /* same as dai_drv[0] */
				अवरोध;
			हाल 1:
				id = args->args[0];
				अवरोध;
			शेष:
				/* not supported */
				अवरोध;
			पूर्ण

			अगर (id < 0 || id >= pos->num_dai) अणु
				ret = -EINVAL;
				जारी;
			पूर्ण

			ret = 0;

			/* find target DAI */
			क्रम_each_component_dais(pos, dai) अणु
				अगर (id == 0)
					अवरोध;
				id--;
			पूर्ण

			*dai_name = dai->driver->name;
			अगर (!*dai_name)
				*dai_name = pos->name;
		पूर्ण अन्यथा अगर (ret) अणु
			/*
			 * अगर another error than ENOTSUPP is वापसed go on and
			 * check अगर another component is provided with the same
			 * node. This may happen अगर a device provides several
			 * components
			 */
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण
	mutex_unlock(&client_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_dai_name);

पूर्णांक snd_soc_of_get_dai_name(काष्ठा device_node *of_node,
			    स्थिर अक्षर **dai_name)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	ret = of_parse_phandle_with_args(of_node, "sound-dai",
					 "#sound-dai-cells", 0, &args);
	अगर (ret)
		वापस ret;

	ret = snd_soc_get_dai_name(&args, dai_name);

	of_node_put(args.np);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_get_dai_name);

/*
 * snd_soc_of_put_dai_link_codecs - Dereference device nodes in the codecs array
 * @dai_link: DAI link
 *
 * Dereference device nodes acquired by snd_soc_of_get_dai_link_codecs().
 */
व्योम snd_soc_of_put_dai_link_codecs(काष्ठा snd_soc_dai_link *dai_link)
अणु
	काष्ठा snd_soc_dai_link_component *component;
	पूर्णांक index;

	क्रम_each_link_codecs(dai_link, index, component) अणु
		अगर (!component->of_node)
			अवरोध;
		of_node_put(component->of_node);
		component->of_node = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_put_dai_link_codecs);

/*
 * snd_soc_of_get_dai_link_codecs - Parse a list of CODECs in the devicetree
 * @dev: Card device
 * @of_node: Device node
 * @dai_link: DAI link
 *
 * Builds an array of CODEC DAI components from the DAI link property
 * 'sound-dai'.
 * The array is set in the DAI link and the number of DAIs is set accordingly.
 * The device nodes in the array (of_node) must be dereferenced by calling
 * snd_soc_of_put_dai_link_codecs() on @dai_link.
 *
 * Returns 0 क्रम success
 */
पूर्णांक snd_soc_of_get_dai_link_codecs(काष्ठा device *dev,
				   काष्ठा device_node *of_node,
				   काष्ठा snd_soc_dai_link *dai_link)
अणु
	काष्ठा of_phandle_args args;
	काष्ठा snd_soc_dai_link_component *component;
	अक्षर *name;
	पूर्णांक index, num_codecs, ret;

	/* Count the number of CODECs */
	name = "sound-dai";
	num_codecs = of_count_phandle_with_args(of_node, name,
						"#sound-dai-cells");
	अगर (num_codecs <= 0) अणु
		अगर (num_codecs == -ENOENT)
			dev_err(dev, "No 'sound-dai' property\n");
		अन्यथा
			dev_err(dev, "Bad phandle in 'sound-dai'\n");
		वापस num_codecs;
	पूर्ण
	component = devm_kसुस्मृति(dev,
				 num_codecs, माप(*component),
				 GFP_KERNEL);
	अगर (!component)
		वापस -ENOMEM;
	dai_link->codecs = component;
	dai_link->num_codecs = num_codecs;

	/* Parse the list */
	क्रम_each_link_codecs(dai_link, index, component) अणु
		ret = of_parse_phandle_with_args(of_node, name,
						 "#sound-dai-cells",
						 index, &args);
		अगर (ret)
			जाओ err;
		component->of_node = args.np;
		ret = snd_soc_get_dai_name(&args, &component->dai_name);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	snd_soc_of_put_dai_link_codecs(dai_link);
	dai_link->codecs = शून्य;
	dai_link->num_codecs = 0;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_of_get_dai_link_codecs);

अटल पूर्णांक __init snd_soc_init(व्योम)
अणु
	snd_soc_debugfs_init();
	snd_soc_util_init();

	वापस platक्रमm_driver_रेजिस्टर(&soc_driver);
पूर्ण
module_init(snd_soc_init);

अटल व्योम __निकास snd_soc_निकास(व्योम)
अणु
	snd_soc_util_निकास();
	snd_soc_debugfs_निकास();

	platक्रमm_driver_unरेजिस्टर(&soc_driver);
पूर्ण
module_निकास(snd_soc_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood, lrg@slimlogic.co.uk");
MODULE_DESCRIPTION("ALSA SoC Core");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:soc-audio");
