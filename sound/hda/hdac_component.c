<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// hdac_component.c - routines क्रम sync between HD-A core and DRM driver

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/component.h>
#समावेश <sound/core.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_component.h>
#समावेश <sound/hda_रेजिस्टर.h>

अटल व्योम hdac_acomp_release(काष्ठा device *dev, व्योम *res)
अणु
पूर्ण

अटल काष्ठा drm_audio_component *hdac_get_acomp(काष्ठा device *dev)
अणु
	वापस devres_find(dev, hdac_acomp_release, शून्य, शून्य);
पूर्ण

/**
 * snd_hdac_set_codec_wakeup - Enable / disable HDMI/DP codec wakeup
 * @bus: HDA core bus
 * @enable: enable or disable the wakeup
 *
 * This function is supposed to be used only by a HD-audio controller
 * driver that needs the पूर्णांकeraction with graphics driver.
 *
 * This function should be called during the chip reset, also called at
 * resume क्रम updating STATESTS रेजिस्टर पढ़ो.
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_set_codec_wakeup(काष्ठा hdac_bus *bus, bool enable)
अणु
	काष्ठा drm_audio_component *acomp = bus->audio_component;

	अगर (!acomp || !acomp->ops)
		वापस -ENODEV;

	अगर (!acomp->ops->codec_wake_override)
		वापस 0;

	dev_dbg(bus->dev, "%s codec wakeup\n",
		enable ? "enable" : "disable");

	acomp->ops->codec_wake_override(acomp->dev, enable);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_set_codec_wakeup);

/**
 * snd_hdac_display_घातer - Power up / करोwn the घातer refcount
 * @bus: HDA core bus
 * @idx: HDA codec address, pass HDA_CODEC_IDX_CONTROLLER क्रम controller
 * @enable: घातer up or करोwn
 *
 * This function is used by either HD-audio controller or codec driver that
 * needs the पूर्णांकeraction with graphics driver.
 *
 * This function updates the घातer status, and calls the get_घातer() and
 * put_घातer() ops accordingly, toggling the codec wakeup, too.
 */
व्योम snd_hdac_display_घातer(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक idx, bool enable)
अणु
	काष्ठा drm_audio_component *acomp = bus->audio_component;

	dev_dbg(bus->dev, "display power %s\n",
		enable ? "enable" : "disable");

	mutex_lock(&bus->lock);
	अगर (enable)
		set_bit(idx, &bus->display_घातer_status);
	अन्यथा
		clear_bit(idx, &bus->display_घातer_status);

	अगर (!acomp || !acomp->ops)
		जाओ unlock;

	अगर (bus->display_घातer_status) अणु
		अगर (!bus->display_घातer_active) अणु
			अचिन्हित दीर्घ cookie = -1;

			अगर (acomp->ops->get_घातer)
				cookie = acomp->ops->get_घातer(acomp->dev);

			snd_hdac_set_codec_wakeup(bus, true);
			snd_hdac_set_codec_wakeup(bus, false);
			bus->display_घातer_active = cookie;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bus->display_घातer_active) अणु
			अचिन्हित दीर्घ cookie = bus->display_घातer_active;

			अगर (acomp->ops->put_घातer)
				acomp->ops->put_घातer(acomp->dev, cookie);

			bus->display_घातer_active = 0;
		पूर्ण
	पूर्ण
 unlock:
	mutex_unlock(&bus->lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_display_घातer);

/**
 * snd_hdac_sync_audio_rate - Set N/CTS based on the sample rate
 * @codec: HDA codec
 * @nid: the pin widget NID
 * @dev_id: device identअगरier
 * @rate: the sample rate to set
 *
 * This function is supposed to be used only by a HD-audio controller
 * driver that needs the पूर्णांकeraction with graphics driver.
 *
 * This function sets N/CTS value based on the given sample rate.
 * Returns zero क्रम success, or a negative error code.
 */
पूर्णांक snd_hdac_sync_audio_rate(काष्ठा hdac_device *codec, hda_nid_t nid,
			     पूर्णांक dev_id, पूर्णांक rate)
अणु
	काष्ठा hdac_bus *bus = codec->bus;
	काष्ठा drm_audio_component *acomp = bus->audio_component;
	पूर्णांक port, pipe;

	अगर (!acomp || !acomp->ops || !acomp->ops->sync_audio_rate)
		वापस -ENODEV;
	port = nid;
	अगर (acomp->audio_ops && acomp->audio_ops->pin2port) अणु
		port = acomp->audio_ops->pin2port(codec, nid);
		अगर (port < 0)
			वापस -EINVAL;
	पूर्ण
	pipe = dev_id;
	वापस acomp->ops->sync_audio_rate(acomp->dev, port, pipe, rate);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_sync_audio_rate);

/**
 * snd_hdac_acomp_get_eld - Get the audio state and ELD via component
 * @codec: HDA codec
 * @nid: the pin widget NID
 * @dev_id: device identअगरier
 * @audio_enabled: the poपूर्णांकer to store the current audio state
 * @buffer: the buffer poपूर्णांकer to store ELD bytes
 * @max_bytes: the max bytes to be stored on @buffer
 *
 * This function is supposed to be used only by a HD-audio controller
 * driver that needs the पूर्णांकeraction with graphics driver.
 *
 * This function queries the current state of the audio on the given
 * digital port and fetches the ELD bytes onto the given buffer.
 * It वापसs the number of bytes क्रम the total ELD data, zero क्रम
 * invalid ELD, or a negative error code.
 *
 * The वापस size is the total bytes required क्रम the whole ELD bytes,
 * thus it may be over @max_bytes.  If it's over @max_bytes, it implies
 * that only a part of ELD bytes have been fetched.
 */
पूर्णांक snd_hdac_acomp_get_eld(काष्ठा hdac_device *codec, hda_nid_t nid, पूर्णांक dev_id,
			   bool *audio_enabled, अक्षर *buffer, पूर्णांक max_bytes)
अणु
	काष्ठा hdac_bus *bus = codec->bus;
	काष्ठा drm_audio_component *acomp = bus->audio_component;
	पूर्णांक port, pipe;

	अगर (!acomp || !acomp->ops || !acomp->ops->get_eld)
		वापस -ENODEV;

	port = nid;
	अगर (acomp->audio_ops && acomp->audio_ops->pin2port) अणु
		port = acomp->audio_ops->pin2port(codec, nid);
		अगर (port < 0)
			वापस -EINVAL;
	पूर्ण
	pipe = dev_id;
	वापस acomp->ops->get_eld(acomp->dev, port, pipe, audio_enabled,
				   buffer, max_bytes);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_acomp_get_eld);

अटल पूर्णांक hdac_component_master_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_audio_component *acomp = hdac_get_acomp(dev);
	पूर्णांक ret;

	अगर (WARN_ON(!acomp))
		वापस -EINVAL;

	ret = component_bind_all(dev, acomp);
	अगर (ret < 0)
		वापस ret;

	अगर (WARN_ON(!(acomp->dev && acomp->ops))) अणु
		ret = -EINVAL;
		जाओ out_unbind;
	पूर्ण

	/* pin the module to aव्योम dynamic unbinding, but only अगर given */
	अगर (!try_module_get(acomp->ops->owner)) अणु
		ret = -ENODEV;
		जाओ out_unbind;
	पूर्ण

	अगर (acomp->audio_ops && acomp->audio_ops->master_bind) अणु
		ret = acomp->audio_ops->master_bind(dev, acomp);
		अगर (ret < 0)
			जाओ module_put;
	पूर्ण

	complete_all(&acomp->master_bind_complete);
	वापस 0;

 module_put:
	module_put(acomp->ops->owner);
out_unbind:
	component_unbind_all(dev, acomp);
	complete_all(&acomp->master_bind_complete);

	वापस ret;
पूर्ण

अटल व्योम hdac_component_master_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_audio_component *acomp = hdac_get_acomp(dev);

	अगर (acomp->audio_ops && acomp->audio_ops->master_unbind)
		acomp->audio_ops->master_unbind(dev, acomp);
	module_put(acomp->ops->owner);
	component_unbind_all(dev, acomp);
	WARN_ON(acomp->ops || acomp->dev);
पूर्ण

अटल स्थिर काष्ठा component_master_ops hdac_component_master_ops = अणु
	.bind = hdac_component_master_bind,
	.unbind = hdac_component_master_unbind,
पूर्ण;

/**
 * snd_hdac_acomp_रेजिस्टर_notअगरier - Register audio component ops
 * @bus: HDA core bus
 * @aops: audio component ops
 *
 * This function is supposed to be used only by a HD-audio controller
 * driver that needs the पूर्णांकeraction with graphics driver.
 *
 * This function sets the given ops to be called by the graphics driver.
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_acomp_रेजिस्टर_notअगरier(काष्ठा hdac_bus *bus,
				    स्थिर काष्ठा drm_audio_component_audio_ops *aops)
अणु
	अगर (!bus->audio_component)
		वापस -ENODEV;

	bus->audio_component->audio_ops = aops;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_acomp_रेजिस्टर_notअगरier);

/**
 * snd_hdac_acomp_init - Initialize audio component
 * @bus: HDA core bus
 * @aops: audio component ops
 * @match_master: match function क्रम finding components
 * @extra_size: Extra bytes to allocate
 *
 * This function is supposed to be used only by a HD-audio controller
 * driver that needs the पूर्णांकeraction with graphics driver.
 *
 * This function initializes and sets up the audio component to communicate
 * with graphics driver.
 *
 * Unlike snd_hdac_i915_init(), this function करोesn't synchronize with the
 * binding with the DRM component.  Each caller needs to sync via master_bind
 * audio_ops.
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_acomp_init(काष्ठा hdac_bus *bus,
			स्थिर काष्ठा drm_audio_component_audio_ops *aops,
			पूर्णांक (*match_master)(काष्ठा device *, पूर्णांक, व्योम *),
			माप_प्रकार extra_size)
अणु
	काष्ठा component_match *match = शून्य;
	काष्ठा device *dev = bus->dev;
	काष्ठा drm_audio_component *acomp;
	पूर्णांक ret;

	अगर (WARN_ON(hdac_get_acomp(dev)))
		वापस -EBUSY;

	acomp = devres_alloc(hdac_acomp_release, माप(*acomp) + extra_size,
			     GFP_KERNEL);
	अगर (!acomp)
		वापस -ENOMEM;
	acomp->audio_ops = aops;
	init_completion(&acomp->master_bind_complete);
	bus->audio_component = acomp;
	devres_add(dev, acomp);

	component_match_add_typed(dev, &match, match_master, bus);
	ret = component_master_add_with_match(dev, &hdac_component_master_ops,
					      match);
	अगर (ret < 0)
		जाओ out_err;

	वापस 0;

out_err:
	bus->audio_component = शून्य;
	devres_destroy(dev, hdac_acomp_release, शून्य, शून्य);
	dev_info(dev, "failed to add audio component master (%d)\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_acomp_init);

/**
 * snd_hdac_acomp_निकास - Finalize audio component
 * @bus: HDA core bus
 *
 * This function is supposed to be used only by a HD-audio controller
 * driver that needs the पूर्णांकeraction with graphics driver.
 *
 * This function releases the audio component that has been used.
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_acomp_निकास(काष्ठा hdac_bus *bus)
अणु
	काष्ठा device *dev = bus->dev;
	काष्ठा drm_audio_component *acomp = bus->audio_component;

	अगर (!acomp)
		वापस 0;

	अगर (WARN_ON(bus->display_घातer_active) && acomp->ops)
		acomp->ops->put_घातer(acomp->dev, bus->display_घातer_active);

	bus->display_घातer_active = 0;
	bus->display_घातer_status = 0;

	component_master_del(dev, &hdac_component_master_ops);

	bus->audio_component = शून्य;
	devres_destroy(dev, hdac_acomp_release, शून्य, शून्य);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_acomp_निकास);
