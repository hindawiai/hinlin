<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Auvitek USB bridge
 *
 *  Copyright (c) 2008 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "au0828.h"
#समावेश "au8522.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/mutex.h>

/* Due to क्रमागत tuner_pad_index */
#समावेश <media/tuner.h>

/*
 * 1 = General debug messages
 * 2 = USB handling
 * 4 = I2C related
 * 8 = Bridge related
 * 16 = IR related
 */
पूर्णांक au0828_debug;
module_param_named(debug, au0828_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		 "set debug bitmask: 1=general, 2=USB, 4=I2C, 8=bridge, 16=IR");

अटल अचिन्हित पूर्णांक disable_usb_speed_check;
module_param(disable_usb_speed_check, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_usb_speed_check,
		 "override min bandwidth requirement of 480M bps");

#घोषणा _AU0828_BULKPIPE 0x03
#घोषणा _BULKPIPESIZE 0xffff

अटल पूर्णांक send_control_msg(काष्ठा au0828_dev *dev, u16 request, u32 value,
			    u16 index);
अटल पूर्णांक recv_control_msg(काष्ठा au0828_dev *dev, u16 request, u32 value,
	u16 index, अचिन्हित अक्षर *cp, u16 size);

/* USB Direction */
#घोषणा CMD_REQUEST_IN		0x00
#घोषणा CMD_REQUEST_OUT		0x01

u32 au0828_पढ़ोreg(काष्ठा au0828_dev *dev, u16 reg)
अणु
	u8 result = 0;

	recv_control_msg(dev, CMD_REQUEST_IN, 0, reg, &result, 1);
	dprपूर्णांकk(8, "%s(0x%04x) = 0x%02x\n", __func__, reg, result);

	वापस result;
पूर्ण

u32 au0828_ग_लिखोreg(काष्ठा au0828_dev *dev, u16 reg, u32 val)
अणु
	dprपूर्णांकk(8, "%s(0x%04x, 0x%02x)\n", __func__, reg, val);
	वापस send_control_msg(dev, CMD_REQUEST_OUT, val, reg);
पूर्ण

अटल पूर्णांक send_control_msg(काष्ठा au0828_dev *dev, u16 request, u32 value,
	u16 index)
अणु
	पूर्णांक status = -ENODEV;

	अगर (dev->usbdev) अणु

		/* cp must be memory that has been allocated by kदो_स्मृति */
		status = usb_control_msg(dev->usbdev,
				usb_sndctrlpipe(dev->usbdev, 0),
				request,
				USB_सूची_OUT | USB_TYPE_VENDOR |
					USB_RECIP_DEVICE,
				value, index, शून्य, 0, 1000);

		status = min(status, 0);

		अगर (status < 0) अणु
			pr_err("%s() Failed sending control message, error %d.\n",
				__func__, status);
		पूर्ण

	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक recv_control_msg(काष्ठा au0828_dev *dev, u16 request, u32 value,
	u16 index, अचिन्हित अक्षर *cp, u16 size)
अणु
	पूर्णांक status = -ENODEV;
	mutex_lock(&dev->mutex);
	अगर (dev->usbdev) अणु
		status = usb_control_msg(dev->usbdev,
				usb_rcvctrlpipe(dev->usbdev, 0),
				request,
				USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				value, index,
				dev->ctrlmsg, size, 1000);

		status = min(status, 0);

		अगर (status < 0) अणु
			pr_err("%s() Failed receiving control message, error %d.\n",
				__func__, status);
		पूर्ण

		/* the host controller requires heap allocated memory, which
		   is why we didn't just pass "cp" पूर्णांकo usb_control_msg */
		स_नकल(cp, dev->ctrlmsg, size);
	पूर्ण
	mutex_unlock(&dev->mutex);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
अटल व्योम au0828_media_graph_notअगरy(काष्ठा media_entity *new,
				      व्योम *notअगरy_data);
#पूर्ण_अगर

अटल व्योम au0828_unरेजिस्टर_media_device(काष्ठा au0828_dev *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *mdev = dev->media_dev;
	काष्ठा media_entity_notअगरy *notअगरy, *nextp;

	अगर (!mdev || !media_devnode_is_रेजिस्टरed(mdev->devnode))
		वापस;

	/* Remove au0828 entity_notअगरy callbacks */
	list_क्रम_each_entry_safe(notअगरy, nextp, &mdev->entity_notअगरy, list) अणु
		अगर (notअगरy->notअगरy != au0828_media_graph_notअगरy)
			जारी;
		media_device_unरेजिस्टर_entity_notअगरy(mdev, notअगरy);
	पूर्ण

	/* clear enable_source, disable_source */
	mutex_lock(&mdev->graph_mutex);
	dev->media_dev->source_priv = शून्य;
	dev->media_dev->enable_source = शून्य;
	dev->media_dev->disable_source = शून्य;
	mutex_unlock(&mdev->graph_mutex);

	media_device_delete(dev->media_dev, KBUILD_MODNAME, THIS_MODULE);
	dev->media_dev = शून्य;
#पूर्ण_अगर
पूर्ण

व्योम au0828_usb_release(काष्ठा au0828_dev *dev)
अणु
	au0828_unरेजिस्टर_media_device(dev);

	/* I2C */
	au0828_i2c_unरेजिस्टर(dev);

	kमुक्त(dev);
पूर्ण

अटल व्योम au0828_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा au0828_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* there is a small winकरोw after disconnect, beक्रमe
	   dev->usbdev is शून्य, क्रम poll (e.g: IR) try to access
	   the device and fill the dmesg with error messages.
	   Set the status so poll routines can check and aव्योम
	   access after disconnect.
	*/
	set_bit(DEV_DISCONNECTED, &dev->dev_state);

	au0828_rc_unरेजिस्टर(dev);
	/* Digital TV */
	au0828_dvb_unरेजिस्टर(dev);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	mutex_lock(&dev->mutex);
	dev->usbdev = शून्य;
	mutex_unlock(&dev->mutex);
	अगर (au0828_analog_unरेजिस्टर(dev)) अणु
		/*
		 * No need to call au0828_usb_release() अगर V4L2 is enabled,
		 * as this is alपढ़ोy called via au0828_usb_v4l2_release()
		 */
		वापस;
	पूर्ण
	au0828_usb_release(dev);
पूर्ण

अटल पूर्णांक au0828_media_device_init(काष्ठा au0828_dev *dev,
				    काष्ठा usb_device *udev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *mdev;

	mdev = media_device_usb_allocate(udev, KBUILD_MODNAME, THIS_MODULE);
	अगर (!mdev)
		वापस -ENOMEM;

	dev->media_dev = mdev;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
अटल व्योम au0828_media_graph_notअगरy(काष्ठा media_entity *new,
				      व्योम *notअगरy_data)
अणु
	काष्ठा au0828_dev *dev = (काष्ठा au0828_dev *) notअगरy_data;
	पूर्णांक ret;
	काष्ठा media_entity *entity, *mixer = शून्य, *decoder = शून्य;

	अगर (!new) अणु
		/*
		 * Called during au0828 probe समय to connect
		 * entities that were created prior to रेजिस्टरing
		 * the notअगरy handler. Find mixer and decoder.
		*/
		media_device_क्रम_each_entity(entity, dev->media_dev) अणु
			अगर (entity->function == MEDIA_ENT_F_AUDIO_MIXER)
				mixer = entity;
			अन्यथा अगर (entity->function == MEDIA_ENT_F_ATV_DECODER)
				decoder = entity;
		पूर्ण
		जाओ create_link;
	पूर्ण

	चयन (new->function) अणु
	हाल MEDIA_ENT_F_AUDIO_MIXER:
		mixer = new;
		अगर (dev->decoder)
			decoder = dev->decoder;
		अवरोध;
	हाल MEDIA_ENT_F_ATV_DECODER:
		/* In हाल, Mixer is added first, find mixer and create link */
		media_device_क्रम_each_entity(entity, dev->media_dev) अणु
			अगर (entity->function == MEDIA_ENT_F_AUDIO_MIXER)
				mixer = entity;
		पूर्ण
		decoder = new;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

create_link:
	अगर (decoder && mixer) अणु
		ret = media_get_pad_index(decoder, false,
					  PAD_SIGNAL_AUDIO);
		अगर (ret >= 0)
			ret = media_create_pad_link(decoder, ret,
						    mixer, 0,
						    MEDIA_LNK_FL_ENABLED);
		अगर (ret < 0)
			dev_err(&dev->usbdev->dev,
				"Mixer Pad Link Create Error: %d\n", ret);
	पूर्ण
पूर्ण

अटल bool au0828_is_link_shareable(काष्ठा media_entity *owner,
				     काष्ठा media_entity *entity)
अणु
	bool shareable = false;

	/* Tuner link can be shared by audio, video, and VBI */
	चयन (owner->function) अणु
	हाल MEDIA_ENT_F_IO_V4L:
	हाल MEDIA_ENT_F_AUDIO_CAPTURE:
	हाल MEDIA_ENT_F_IO_VBI:
		अगर (entity->function == MEDIA_ENT_F_IO_V4L ||
		    entity->function == MEDIA_ENT_F_AUDIO_CAPTURE ||
		    entity->function == MEDIA_ENT_F_IO_VBI)
			shareable = true;
		अवरोध;
	हाल MEDIA_ENT_F_DTV_DEMOD:
	शेष:
		अवरोध;
	पूर्ण
	वापस shareable;
पूर्ण

/* Callers should hold graph_mutex */
अटल पूर्णांक au0828_enable_source(काष्ठा media_entity *entity,
				काष्ठा media_pipeline *pipe)
अणु
	काष्ठा media_entity  *source, *find_source;
	काष्ठा media_entity *sink;
	काष्ठा media_link *link, *found_link = शून्य;
	पूर्णांक ret = 0;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	काष्ठा au0828_dev *dev;

	अगर (!mdev)
		वापस -ENODEV;

	dev = mdev->source_priv;

	/*
	 * For Audio and V4L2 entity, find the link to which decoder
	 * is the sink. Look क्रम an active link between decoder and
	 * source (tuner/s-video/Composite), अगर one exists, nothing
	 * to करो. If not, look क्रम any  active links between source
	 * and any other entity. If one exists, source is busy. If
	 * source is मुक्त, setup link and start pipeline from source.
	 * For DVB FE entity, the source क्रम the link is the tuner.
	 * Check अगर tuner is available and setup link and start
	 * pipeline.
	*/
	अगर (entity->function == MEDIA_ENT_F_DTV_DEMOD) अणु
		sink = entity;
		find_source = dev->tuner;
	पूर्ण अन्यथा अणु
		/* Analog isn't configured or रेजिस्टर failed */
		अगर (!dev->decoder) अणु
			ret = -ENODEV;
			जाओ end;
		पूर्ण

		sink = dev->decoder;

		/*
		 * Default input is tuner and शेष input_type
		 * is AU0828_VMUX_TELEVISION.
		 *
		 * There is a problem when s_input is called to
		 * change the शेष input. s_input will try to
		 * enable_source beक्रमe attempting to change the
		 * input on the device, and will end up enabling
		 * शेष source which is tuner.
		 *
		 * Additional logic is necessary in au0828 to detect
		 * that the input has changed and enable the right
		 * source. au0828 handles this हाल in its s_input.
		 * It will disable the old source and enable the new
		 * source.
		 *
		*/
		अगर (dev->input_type == AU0828_VMUX_TELEVISION)
			find_source = dev->tuner;
		अन्यथा अगर (dev->input_type == AU0828_VMUX_SVIDEO ||
			 dev->input_type == AU0828_VMUX_COMPOSITE)
			find_source = &dev->input_ent[dev->input_type];
		अन्यथा अणु
			/* unknown input - let user select input */
			ret = 0;
			जाओ end;
		पूर्ण
	पूर्ण

	/* Is there an active link between sink and source */
	अगर (dev->active_link) अणु
		अगर (dev->active_link_owner == entity) अणु
			/* This check is necessary to handle multiple
			 * enable_source calls from v4l_ioctls during
			 * the course of video/vbi application run-समय.
			*/
			pr_debug("%s already owns the tuner\n", entity->name);
			ret = 0;
			जाओ end;
		पूर्ण अन्यथा अगर (au0828_is_link_shareable(dev->active_link_owner,
			   entity)) अणु
			/* Either ALSA or Video own tuner. Sink is the same
			 * क्रम both. Allow sharing the active link between
			 * their common source (tuner) and sink (decoder).
			 * Starting pipeline between sharing entity and sink
			 * will fail with pipe mismatch, जबतक owner has an
			 * active pipeline. Switch pipeline ownership from
			 * user to owner when owner disables the source.
			 */
			dev->active_link_shared = true;
			/* save the user info to use from disable */
			dev->active_link_user = entity;
			dev->active_link_user_pipe = pipe;
			pr_debug("%s owns the tuner %s can share!\n",
				 dev->active_link_owner->name,
				 entity->name);
			ret = 0;
			जाओ end;
		पूर्ण अन्यथा अणु
			ret = -EBUSY;
			जाओ end;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(link, &sink->links, list) अणु
		/* Check sink, and source */
		अगर (link->sink->entity == sink &&
		    link->source->entity == find_source) अणु
			found_link = link;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found_link) अणु
		ret = -ENODEV;
		जाओ end;
	पूर्ण

	/* activate link between source and sink and start pipeline */
	source = found_link->source->entity;
	ret = __media_entity_setup_link(found_link, MEDIA_LNK_FL_ENABLED);
	अगर (ret) अणु
		pr_err("Activate link from %s->%s. Error %d\n",
			source->name, sink->name, ret);
		जाओ end;
	पूर्ण

	ret = __media_pipeline_start(entity, pipe);
	अगर (ret) अणु
		pr_err("Start Pipeline: %s->%s Error %d\n",
			source->name, entity->name, ret);
		ret = __media_entity_setup_link(found_link, 0);
		अगर (ret)
			pr_err("Deactivate link Error %d\n", ret);
		जाओ end;
	पूर्ण

	/* save link state to allow audio and video share the link
	 * and not disable the link जबतक the other is using it.
	 * active_link_owner is used to deactivate the link.
	*/
	dev->active_link = found_link;
	dev->active_link_owner = entity;
	dev->active_source = source;
	dev->active_sink = sink;

	pr_info("Enabled Source: %s->%s->%s Ret %d\n",
		 dev->active_source->name, dev->active_sink->name,
		 dev->active_link_owner->name, ret);
end:
	pr_debug("%s end: ent:%s fnc:%d ret %d\n",
		 __func__, entity->name, entity->function, ret);
	वापस ret;
पूर्ण

/* Callers should hold graph_mutex */
अटल व्योम au0828_disable_source(काष्ठा media_entity *entity)
अणु
	पूर्णांक ret = 0;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	काष्ठा au0828_dev *dev;

	अगर (!mdev)
		वापस;

	dev = mdev->source_priv;

	अगर (!dev->active_link)
		वापस;

	/* link is active - stop pipeline from source
	 * (tuner/s-video/Composite) to the entity
	 * When DVB/s-video/Composite owns tuner, it won't be in
	 * shared state.
	 */
	अगर (dev->active_link->sink->entity == dev->active_sink &&
	    dev->active_link->source->entity == dev->active_source) अणु
		/*
		 * Prevent video from deactivating link when audio
		 * has active pipeline and vice versa. In addition
		 * handle the हाल when more than one video/vbi
		 * application is sharing the link.
		*/
		bool owner_is_audio = false;

		अगर (dev->active_link_owner->function ==
		    MEDIA_ENT_F_AUDIO_CAPTURE)
			owner_is_audio = true;

		अगर (dev->active_link_shared) अणु
			pr_debug("Shared link owner %s user %s %d\n",
				 dev->active_link_owner->name,
				 entity->name, dev->users);

			/* Handle video device users > 1
			 * When audio owns the shared link with
			 * more than one video users, aव्योम
			 * disabling the source and/or चयनing
			 * the owner until the last disable_source
			 * call from video _बंद(). Use dev->users to
			 * determine when to चयन/disable.
			 */
			अगर (dev->active_link_owner != entity) अणु
				/* video device has users > 1 */
				अगर (owner_is_audio && dev->users > 1)
					वापस;

				dev->active_link_user = शून्य;
				dev->active_link_user_pipe = शून्य;
				dev->active_link_shared = false;
				वापस;
			पूर्ण

			/* video owns the link and has users > 1 */
			अगर (!owner_is_audio && dev->users > 1)
				वापस;

			/* stop pipeline */
			__media_pipeline_stop(dev->active_link_owner);
			pr_debug("Pipeline stop for %s\n",
				dev->active_link_owner->name);

			ret = __media_pipeline_start(
					dev->active_link_user,
					dev->active_link_user_pipe);
			अगर (ret) अणु
				pr_err("Start Pipeline: %s->%s %d\n",
					dev->active_source->name,
					dev->active_link_user->name,
					ret);
				जाओ deactivate_link;
			पूर्ण
			/* link user is now the owner */
			dev->active_link_owner = dev->active_link_user;
			dev->active_link_user = शून्य;
			dev->active_link_user_pipe = शून्य;
			dev->active_link_shared = false;

			pr_debug("Pipeline started for %s\n",
				dev->active_link_owner->name);
			वापस;
		पूर्ण अन्यथा अगर (!owner_is_audio && dev->users > 1)
			/* video/vbi owns the link and has users > 1 */
			वापस;

		अगर (dev->active_link_owner != entity)
			वापस;

		/* stop pipeline */
		__media_pipeline_stop(dev->active_link_owner);
		pr_debug("Pipeline stop for %s\n",
			dev->active_link_owner->name);

deactivate_link:
		ret = __media_entity_setup_link(dev->active_link, 0);
		अगर (ret)
			pr_err("Deactivate link Error %d\n", ret);

		pr_info("Disabled Source: %s->%s->%s Ret %d\n",
			 dev->active_source->name, dev->active_sink->name,
			 dev->active_link_owner->name, ret);

		dev->active_link = शून्य;
		dev->active_link_owner = शून्य;
		dev->active_source = शून्य;
		dev->active_sink = शून्य;
		dev->active_link_shared = false;
		dev->active_link_user = शून्य;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक au0828_media_device_रेजिस्टर(काष्ठा au0828_dev *dev,
					काष्ठा usb_device *udev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक ret;
	काष्ठा media_entity *entity, *demod = शून्य;
	काष्ठा media_link *link;

	अगर (!dev->media_dev)
		वापस 0;

	अगर (!media_devnode_is_रेजिस्टरed(dev->media_dev->devnode)) अणु

		/* रेजिस्टर media device */
		ret = media_device_रेजिस्टर(dev->media_dev);
		अगर (ret) अणु
			media_device_delete(dev->media_dev, KBUILD_MODNAME,
					    THIS_MODULE);
			dev->media_dev = शून्य;
			dev_err(&udev->dev,
				"Media Device Register Error: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Call au0828_media_graph_notअगरy() to connect
		 * audio graph to our graph. In this हाल, audio
		 * driver रेजिस्टरed the device and there is no
		 * entity_notअगरy to be called when new entities
		 * are added. Invoke it now.
		*/
		au0828_media_graph_notअगरy(शून्य, (व्योम *) dev);
	पूर्ण

	/*
	 * Find tuner, decoder and demod.
	 *
	 * The tuner and decoder should be cached, as they'll be used by
	 *	au0828_enable_source.
	 *
	 * It also needs to disable the link between tuner and
	 * decoder/demod, to aव्योम disable step when tuner is requested
	 * by video or audio. Note that this step can't be करोne until dvb
	 * graph is created during dvb रेजिस्टर.
	*/
	media_device_क्रम_each_entity(entity, dev->media_dev) अणु
		चयन (entity->function) अणु
		हाल MEDIA_ENT_F_TUNER:
			dev->tuner = entity;
			अवरोध;
		हाल MEDIA_ENT_F_ATV_DECODER:
			dev->decoder = entity;
			अवरोध;
		हाल MEDIA_ENT_F_DTV_DEMOD:
			demod = entity;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Disable link between tuner->demod and/or tuner->decoder */
	अगर (dev->tuner) अणु
		list_क्रम_each_entry(link, &dev->tuner->links, list) अणु
			अगर (demod && link->sink->entity == demod)
				media_entity_setup_link(link, 0);
			अगर (dev->decoder && link->sink->entity == dev->decoder)
				media_entity_setup_link(link, 0);
		पूर्ण
	पूर्ण

	/* रेजिस्टर entity_notअगरy callback */
	dev->entity_notअगरy.notअगरy_data = (व्योम *) dev;
	dev->entity_notअगरy.notअगरy = (व्योम *) au0828_media_graph_notअगरy;
	ret = media_device_रेजिस्टर_entity_notअगरy(dev->media_dev,
						  &dev->entity_notअगरy);
	अगर (ret) अणु
		dev_err(&udev->dev,
			"Media Device register entity_notify Error: %d\n",
			ret);
		वापस ret;
	पूर्ण
	/* set enable_source */
	mutex_lock(&dev->media_dev->graph_mutex);
	dev->media_dev->source_priv = (व्योम *) dev;
	dev->media_dev->enable_source = au0828_enable_source;
	dev->media_dev->disable_source = au0828_disable_source;
	mutex_unlock(&dev->media_dev->graph_mutex);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक au0828_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
	स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक अगरnum;
	पूर्णांक retval = 0;

	काष्ठा au0828_dev *dev;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	अगरnum = पूर्णांकerface->altsetting->desc.bInterfaceNumber;

	अगर (अगरnum != 0)
		वापस -ENODEV;

	dprपूर्णांकk(1, "%s() vendor id 0x%x device id 0x%x ifnum:%d\n", __func__,
		le16_to_cpu(usbdev->descriptor.idVenकरोr),
		le16_to_cpu(usbdev->descriptor.idProduct),
		अगरnum);

	/*
	 * Make sure we have 480 Mbps of bandwidth, otherwise things like
	 * video stream wouldn't likely work, since 12 Mbps is generally
	 * not enough even क्रम most Digital TV streams.
	 */
	अगर (usbdev->speed != USB_SPEED_HIGH && disable_usb_speed_check == 0) अणु
		pr_err("au0828: Device initialization failed.\n");
		pr_err("au0828: Device must be connected to a high-speed USB 2.0 port.\n");
		वापस -ENODEV;
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		pr_err("%s() Unable to allocate memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&dev->lock);
	mutex_lock(&dev->lock);
	mutex_init(&dev->mutex);
	mutex_init(&dev->dvb.lock);
	dev->usbdev = usbdev;
	dev->boardnr = id->driver_info;
	dev->board = au0828_boards[dev->boardnr];

	/* Initialize the media controller */
	retval = au0828_media_device_init(dev, usbdev);
	अगर (retval) अणु
		pr_err("%s() au0828_media_device_init failed\n",
		       __func__);
		mutex_unlock(&dev->lock);
		kमुक्त(dev);
		वापस retval;
	पूर्ण

	retval = au0828_v4l2_device_रेजिस्टर(पूर्णांकerface, dev);
	अगर (retval) अणु
		au0828_usb_v4l2_media_release(dev);
		mutex_unlock(&dev->lock);
		kमुक्त(dev);
		वापस retval;
	पूर्ण

	/* Power Up the bridge */
	au0828_ग_लिखो(dev, REG_600, 1 << 4);

	/* Bring up the GPIO's and supporting devices */
	au0828_gpio_setup(dev);

	/* I2C */
	au0828_i2c_रेजिस्टर(dev);

	/* Setup */
	au0828_card_setup(dev);

	/*
	 * Store the poपूर्णांकer to the au0828_dev so it can be accessed in
	 * au0828_usb_disconnect
	 */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	/* Analog TV */
	retval = au0828_analog_रेजिस्टर(dev, पूर्णांकerface);
	अगर (retval) अणु
		pr_err("%s() au0828_analog_register failed to register on V4L2\n",
			__func__);
		mutex_unlock(&dev->lock);
		जाओ करोne;
	पूर्ण

	/* Digital TV */
	retval = au0828_dvb_रेजिस्टर(dev);
	अगर (retval)
		pr_err("%s() au0828_dvb_register failed\n",
		       __func__);

	/* Remote controller */
	au0828_rc_रेजिस्टर(dev);

	pr_info("Registered device AU0828 [%s]\n",
		dev->board.name == शून्य ? "Unset" : dev->board.name);

	mutex_unlock(&dev->lock);

	retval = au0828_media_device_रेजिस्टर(dev, usbdev);

करोne:
	अगर (retval < 0)
		au0828_usb_disconnect(पूर्णांकerface);

	वापस retval;
पूर्ण

अटल पूर्णांक au0828_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				pm_message_t message)
अणु
	काष्ठा au0828_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	अगर (!dev)
		वापस 0;

	pr_info("Suspend\n");

	au0828_rc_suspend(dev);
	au0828_v4l2_suspend(dev);
	au0828_dvb_suspend(dev);

	/* FIXME: should suspend also ATV/DTV */

	वापस 0;
पूर्ण

अटल पूर्णांक au0828_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा au0828_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev)
		वापस 0;

	pr_info("Resume\n");

	/* Power Up the bridge */
	au0828_ग_लिखो(dev, REG_600, 1 << 4);

	/* Bring up the GPIO's and supporting devices */
	au0828_gpio_setup(dev);

	au0828_rc_resume(dev);
	au0828_v4l2_resume(dev);
	au0828_dvb_resume(dev);

	/* FIXME: should resume also ATV/DTV */

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver au0828_usb_driver = अणु
	.name		= KBUILD_MODNAME,
	.probe		= au0828_usb_probe,
	.disconnect	= au0828_usb_disconnect,
	.id_table	= au0828_usb_id_table,
	.suspend	= au0828_suspend,
	.resume		= au0828_resume,
	.reset_resume	= au0828_resume,
पूर्ण;

अटल पूर्णांक __init au0828_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (au0828_debug & 1)
		pr_info("%s() Debugging is enabled\n", __func__);

	अगर (au0828_debug & 2)
		pr_info("%s() USB Debugging is enabled\n", __func__);

	अगर (au0828_debug & 4)
		pr_info("%s() I2C Debugging is enabled\n", __func__);

	अगर (au0828_debug & 8)
		pr_info("%s() Bridge Debugging is enabled\n",
		       __func__);

	अगर (au0828_debug & 16)
		pr_info("%s() IR Debugging is enabled\n",
		       __func__);

	pr_info("au0828 driver loaded\n");

	ret = usb_रेजिस्टर(&au0828_usb_driver);
	अगर (ret)
		pr_err("usb_register failed, error = %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम __निकास au0828_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&au0828_usb_driver);
पूर्ण

module_init(au0828_init);
module_निकास(au0828_निकास);

MODULE_DESCRIPTION("Driver for Auvitek AU0828 based products");
MODULE_AUTHOR("Steven Toth <stoth@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.3");
