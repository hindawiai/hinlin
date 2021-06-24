<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DVB USB framework
 *
 * Copyright (C) 2004-6 Patrick Boettcher <patrick.boettcher@posteo.de>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#समावेश "dvb_usb_common.h"
#समावेश <media/media-device.h>

अटल पूर्णांक dvb_usbv2_disable_rc_polling;
module_param_named(disable_rc_polling, dvb_usbv2_disable_rc_polling, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_rc_polling,
		"disable remote control polling (default: 0)");
अटल पूर्णांक dvb_usb_क्रमce_pid_filter_usage;
module_param_named(क्रमce_pid_filter_usage, dvb_usb_क्रमce_pid_filter_usage,
		पूर्णांक, 0444);
MODULE_PARM_DESC(क्रमce_pid_filter_usage,
		"force all DVB USB devices to use a PID filter, if any (default: 0)");

अटल पूर्णांक dvb_usbv2_करोwnload_firmware(काष्ठा dvb_usb_device *d,
		स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	अगर (!d->props->करोwnload_firmware) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = request_firmware(&fw, name, &d->udev->dev);
	अगर (ret < 0) अणु
		dev_err(&d->udev->dev,
				"%s: Did not find the firmware file '%s' (status %d). You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware\n",
				KBUILD_MODNAME, name, ret);
		जाओ err;
	पूर्ण

	dev_info(&d->udev->dev, "%s: downloading firmware from file '%s'\n",
			KBUILD_MODNAME, name);

	ret = d->props->करोwnload_firmware(d, fw);
	release_firmware(fw);
	अगर (ret < 0)
		जाओ err;

	वापस ret;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_i2c_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	अगर (!d->props->i2c_algo)
		वापस 0;

	strscpy(d->i2c_adap.name, d->name, माप(d->i2c_adap.name));
	d->i2c_adap.algo = d->props->i2c_algo;
	d->i2c_adap.dev.parent = &d->udev->dev;
	i2c_set_adapdata(&d->i2c_adap, d);

	ret = i2c_add_adapter(&d->i2c_adap);
	अगर (ret < 0) अणु
		d->i2c_adap.algo = शून्य;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_i2c_निकास(काष्ठा dvb_usb_device *d)
अणु
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	अगर (d->i2c_adap.algo)
		i2c_del_adapter(&d->i2c_adap);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_RC_CORE)
अटल व्योम dvb_usb_पढ़ो_remote_control(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dvb_usb_device *d = container_of(work,
			काष्ठा dvb_usb_device, rc_query_work.work);
	पूर्णांक ret;

	/*
	 * When the parameter has been set to 1 via sysfs जबतक the
	 * driver was running, or when bulk mode is enabled after IR init.
	 */
	अगर (dvb_usbv2_disable_rc_polling || d->rc.bulk_mode) अणु
		d->rc_polling_active = false;
		वापस;
	पूर्ण

	ret = d->rc.query(d);
	अगर (ret < 0) अणु
		dev_err(&d->udev->dev, "%s: rc.query() failed=%d\n",
				KBUILD_MODNAME, ret);
		d->rc_polling_active = false;
		वापस; /* stop polling */
	पूर्ण

	schedule_delayed_work(&d->rc_query_work,
			msecs_to_jअगरfies(d->rc.पूर्णांकerval));
पूर्ण

अटल पूर्णांक dvb_usbv2_remote_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	काष्ठा rc_dev *dev;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	अगर (dvb_usbv2_disable_rc_polling || !d->props->get_rc_config)
		वापस 0;

	d->rc.map_name = d->rc_map;
	ret = d->props->get_rc_config(d, &d->rc);
	अगर (ret < 0)
		जाओ err;

	/* disable rc when there is no keymap defined */
	अगर (!d->rc.map_name)
		वापस 0;

	dev = rc_allocate_device(d->rc.driver_type);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->dev.parent = &d->udev->dev;
	dev->device_name = d->name;
	usb_make_path(d->udev, d->rc_phys, माप(d->rc_phys));
	strlcat(d->rc_phys, "/ir0", माप(d->rc_phys));
	dev->input_phys = d->rc_phys;
	usb_to_input_id(d->udev, &dev->input_id);
	dev->driver_name = d->props->driver_name;
	dev->map_name = d->rc.map_name;
	dev->allowed_protocols = d->rc.allowed_protos;
	dev->change_protocol = d->rc.change_protocol;
	dev->समयout = d->rc.समयout;
	dev->priv = d;

	ret = rc_रेजिस्टर_device(dev);
	अगर (ret < 0) अणु
		rc_मुक्त_device(dev);
		जाओ err;
	पूर्ण

	d->rc_dev = dev;

	/* start polling अगर needed */
	अगर (d->rc.query && !d->rc.bulk_mode) अणु
		/* initialize a work queue क्रम handling polling */
		INIT_DELAYED_WORK(&d->rc_query_work,
				dvb_usb_पढ़ो_remote_control);
		dev_info(&d->udev->dev,
				"%s: schedule remote query interval to %d msecs\n",
				KBUILD_MODNAME, d->rc.पूर्णांकerval);
		schedule_delayed_work(&d->rc_query_work,
				msecs_to_jअगरfies(d->rc.पूर्णांकerval));
		d->rc_polling_active = true;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_remote_निकास(काष्ठा dvb_usb_device *d)
अणु
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	अगर (d->rc_dev) अणु
		cancel_delayed_work_sync(&d->rc_query_work);
		rc_unरेजिस्टर_device(d->rc_dev);
		d->rc_dev = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
	#घोषणा dvb_usbv2_remote_init(args...) 0
	#घोषणा dvb_usbv2_remote_निकास(args...)
#पूर्ण_अगर

अटल व्योम dvb_usb_data_complete(काष्ठा usb_data_stream *stream, u8 *buf,
		माप_प्रकार len)
अणु
	काष्ठा dvb_usb_adapter *adap = stream->user_priv;
	dvb_dmx_swfilter(&adap->demux, buf, len);
पूर्ण

अटल व्योम dvb_usb_data_complete_204(काष्ठा usb_data_stream *stream, u8 *buf,
		माप_प्रकार len)
अणु
	काष्ठा dvb_usb_adapter *adap = stream->user_priv;
	dvb_dmx_swfilter_204(&adap->demux, buf, len);
पूर्ण

अटल व्योम dvb_usb_data_complete_raw(काष्ठा usb_data_stream *stream, u8 *buf,
		माप_प्रकार len)
अणु
	काष्ठा dvb_usb_adapter *adap = stream->user_priv;
	dvb_dmx_swfilter_raw(&adap->demux, buf, len);
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_stream_init(काष्ठा dvb_usb_adapter *adap)
अणु
	dev_dbg(&adap_to_d(adap)->udev->dev, "%s: adap=%d\n", __func__,
			adap->id);

	adap->stream.udev = adap_to_d(adap)->udev;
	adap->stream.user_priv = adap;
	adap->stream.complete = dvb_usb_data_complete;

	वापस usb_urb_initv2(&adap->stream, &adap->props->stream);
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_stream_निकास(काष्ठा dvb_usb_adapter *adap)
अणु
	dev_dbg(&adap_to_d(adap)->udev->dev, "%s: adap=%d\n", __func__,
			adap->id);

	वापस usb_urb_निकासv2(&adap->stream);
पूर्ण

अटल पूर्णांक dvb_usb_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_usb_adapter *adap = dvbdmxfeed->demux->priv;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	पूर्णांक ret = 0;
	काष्ठा usb_data_stream_properties stream_props;
	dev_dbg(&d->udev->dev,
			"%s: adap=%d active_fe=%d feed_type=%d setting pid [%s]: %04x (%04d) at index %d\n",
			__func__, adap->id, adap->active_fe, dvbdmxfeed->type,
			adap->pid_filtering ? "yes" : "no", dvbdmxfeed->pid,
			dvbdmxfeed->pid, dvbdmxfeed->index);

	/* रुको init is करोne */
	रुको_on_bit(&adap->state_bits, ADAP_INIT, TASK_UNINTERRUPTIBLE);

	अगर (adap->active_fe == -1)
		वापस -EINVAL;

	/* skip feed setup अगर we are alपढ़ोy feeding */
	अगर (adap->feed_count++ > 0)
		जाओ skip_feed_start;

	/* set 'streaming' status bit */
	set_bit(ADAP_STREAMING, &adap->state_bits);

	/* resolve input and output streaming parameters */
	अगर (d->props->get_stream_config) अणु
		स_नकल(&stream_props, &adap->props->stream,
				माप(काष्ठा usb_data_stream_properties));
		ret = d->props->get_stream_config(adap->fe[adap->active_fe],
				&adap->ts_type, &stream_props);
		अगर (ret)
			dev_err(&d->udev->dev,
					"%s: get_stream_config() failed=%d\n",
					KBUILD_MODNAME, ret);
	पूर्ण अन्यथा अणु
		stream_props = adap->props->stream;
	पूर्ण

	चयन (adap->ts_type) अणु
	हाल DVB_USB_FE_TS_TYPE_204:
		adap->stream.complete = dvb_usb_data_complete_204;
		अवरोध;
	हाल DVB_USB_FE_TS_TYPE_RAW:
		adap->stream.complete = dvb_usb_data_complete_raw;
		अवरोध;
	हाल DVB_USB_FE_TS_TYPE_188:
	शेष:
		adap->stream.complete = dvb_usb_data_complete;
		अवरोध;
	पूर्ण

	/* submit USB streaming packets */
	usb_urb_submitv2(&adap->stream, &stream_props);

	/* enable HW PID filter */
	अगर (adap->pid_filtering && adap->props->pid_filter_ctrl) अणु
		ret = adap->props->pid_filter_ctrl(adap, 1);
		अगर (ret)
			dev_err(&d->udev->dev,
					"%s: pid_filter_ctrl() failed=%d\n",
					KBUILD_MODNAME, ret);
	पूर्ण

	/* ask device to start streaming */
	अगर (d->props->streaming_ctrl) अणु
		ret = d->props->streaming_ctrl(adap->fe[adap->active_fe], 1);
		अगर (ret)
			dev_err(&d->udev->dev,
					"%s: streaming_ctrl() failed=%d\n",
					KBUILD_MODNAME, ret);
	पूर्ण
skip_feed_start:

	/* add PID to device HW PID filter */
	अगर (adap->pid_filtering && adap->props->pid_filter) अणु
		ret = adap->props->pid_filter(adap, dvbdmxfeed->index,
				dvbdmxfeed->pid, 1);
		अगर (ret)
			dev_err(&d->udev->dev, "%s: pid_filter() failed=%d\n",
					KBUILD_MODNAME, ret);
	पूर्ण

	अगर (ret)
		dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usb_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_usb_adapter *adap = dvbdmxfeed->demux->priv;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	पूर्णांक ret = 0;
	dev_dbg(&d->udev->dev,
			"%s: adap=%d active_fe=%d feed_type=%d setting pid [%s]: %04x (%04d) at index %d\n",
			__func__, adap->id, adap->active_fe, dvbdmxfeed->type,
			adap->pid_filtering ? "yes" : "no", dvbdmxfeed->pid,
			dvbdmxfeed->pid, dvbdmxfeed->index);

	अगर (adap->active_fe == -1)
		वापस -EINVAL;

	/* हटाओ PID from device HW PID filter */
	अगर (adap->pid_filtering && adap->props->pid_filter) अणु
		ret = adap->props->pid_filter(adap, dvbdmxfeed->index,
				dvbdmxfeed->pid, 0);
		अगर (ret)
			dev_err(&d->udev->dev, "%s: pid_filter() failed=%d\n",
					KBUILD_MODNAME, ret);
	पूर्ण

	/* we cannot stop streaming until last PID is हटाओd */
	अगर (--adap->feed_count > 0)
		जाओ skip_feed_stop;

	/* ask device to stop streaming */
	अगर (d->props->streaming_ctrl) अणु
		ret = d->props->streaming_ctrl(adap->fe[adap->active_fe], 0);
		अगर (ret)
			dev_err(&d->udev->dev,
					"%s: streaming_ctrl() failed=%d\n",
					KBUILD_MODNAME, ret);
	पूर्ण

	/* disable HW PID filter */
	अगर (adap->pid_filtering && adap->props->pid_filter_ctrl) अणु
		ret = adap->props->pid_filter_ctrl(adap, 0);
		अगर (ret)
			dev_err(&d->udev->dev,
					"%s: pid_filter_ctrl() failed=%d\n",
					KBUILD_MODNAME, ret);
	पूर्ण

	/* समाप्त USB streaming packets */
	usb_urb_समाप्तv2(&adap->stream);

	/* clear 'streaming' status bit */
	clear_bit(ADAP_STREAMING, &adap->state_bits);
	smp_mb__after_atomic();
	wake_up_bit(&adap->state_bits, ADAP_STREAMING);
skip_feed_stop:

	अगर (ret)
		dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_media_device_init(काष्ठा dvb_usb_adapter *adap)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	काष्ठा media_device *mdev;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_device *udev = d->udev;

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	media_device_usb_init(mdev, udev, d->name);

	dvb_रेजिस्टर_media_controller(&adap->dvb_adap, mdev);

	dev_info(&d->udev->dev, "media controller created\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usbv2_media_device_रेजिस्टर(काष्ठा dvb_usb_adapter *adap)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	वापस media_device_रेजिस्टर(adap->dvb_adap.mdev);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम dvb_usbv2_media_device_unरेजिस्टर(काष्ठा dvb_usb_adapter *adap)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB

	अगर (!adap->dvb_adap.mdev)
		वापस;

	media_device_unरेजिस्टर(adap->dvb_adap.mdev);
	media_device_cleanup(adap->dvb_adap.mdev);
	kमुक्त(adap->dvb_adap.mdev);
	adap->dvb_adap.mdev = शून्य;

#पूर्ण_अगर
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_dvb_init(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);

	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	ret = dvb_रेजिस्टर_adapter(&adap->dvb_adap, d->name, d->props->owner,
			&d->udev->dev, d->props->adapter_nr);
	अगर (ret < 0) अणु
		dev_dbg(&d->udev->dev, "%s: dvb_register_adapter() failed=%d\n",
				__func__, ret);
		जाओ err_dvb_रेजिस्टर_adapter;
	पूर्ण

	adap->dvb_adap.priv = adap;

	ret = dvb_usbv2_media_device_init(adap);
	अगर (ret < 0) अणु
		dev_dbg(&d->udev->dev, "%s: dvb_usbv2_media_device_init() failed=%d\n",
				__func__, ret);
		जाओ err_dvb_रेजिस्टर_mc;
	पूर्ण

	अगर (d->props->पढ़ो_mac_address) अणु
		ret = d->props->पढ़ो_mac_address(adap,
				adap->dvb_adap.proposed_mac);
		अगर (ret < 0)
			जाओ err_dvb_dmx_init;

		dev_info(&d->udev->dev, "%s: MAC address: %pM\n",
				KBUILD_MODNAME, adap->dvb_adap.proposed_mac);
	पूर्ण

	adap->demux.dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING;
	adap->demux.priv             = adap;
	adap->demux.filternum        = 0;
	adap->demux.filternum        = adap->max_feed_count;
	adap->demux.feednum          = adap->demux.filternum;
	adap->demux.start_feed       = dvb_usb_start_feed;
	adap->demux.stop_feed        = dvb_usb_stop_feed;
	adap->demux.ग_लिखो_to_decoder = शून्य;
	ret = dvb_dmx_init(&adap->demux);
	अगर (ret < 0) अणु
		dev_err(&d->udev->dev, "%s: dvb_dmx_init() failed=%d\n",
				KBUILD_MODNAME, ret);
		जाओ err_dvb_dmx_init;
	पूर्ण

	adap->dmxdev.filternum       = adap->demux.filternum;
	adap->dmxdev.demux           = &adap->demux.dmx;
	adap->dmxdev.capabilities    = 0;
	ret = dvb_dmxdev_init(&adap->dmxdev, &adap->dvb_adap);
	अगर (ret < 0) अणु
		dev_err(&d->udev->dev, "%s: dvb_dmxdev_init() failed=%d\n",
				KBUILD_MODNAME, ret);
		जाओ err_dvb_dmxdev_init;
	पूर्ण

	ret = dvb_net_init(&adap->dvb_adap, &adap->dvb_net, &adap->demux.dmx);
	अगर (ret < 0) अणु
		dev_err(&d->udev->dev, "%s: dvb_net_init() failed=%d\n",
				KBUILD_MODNAME, ret);
		जाओ err_dvb_net_init;
	पूर्ण

	वापस 0;
err_dvb_net_init:
	dvb_dmxdev_release(&adap->dmxdev);
err_dvb_dmxdev_init:
	dvb_dmx_release(&adap->demux);
err_dvb_dmx_init:
	dvb_usbv2_media_device_unरेजिस्टर(adap);
err_dvb_रेजिस्टर_mc:
	dvb_unरेजिस्टर_adapter(&adap->dvb_adap);
err_dvb_रेजिस्टर_adapter:
	adap->dvb_adap.priv = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_dvb_निकास(काष्ठा dvb_usb_adapter *adap)
अणु
	dev_dbg(&adap_to_d(adap)->udev->dev, "%s: adap=%d\n", __func__,
			adap->id);

	अगर (adap->dvb_adap.priv) अणु
		dvb_net_release(&adap->dvb_net);
		adap->demux.dmx.बंद(&adap->demux.dmx);
		dvb_dmxdev_release(&adap->dmxdev);
		dvb_dmx_release(&adap->demux);
		dvb_unरेजिस्टर_adapter(&adap->dvb_adap);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usbv2_device_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	पूर्णांक ret;

	अगर (onoff)
		d->घातered++;
	अन्यथा
		d->घातered--;

	अगर (d->घातered == 0 || (onoff && d->घातered == 1)) अणु
		/* when चयनing from 1 to 0 or from 0 to 1 */
		dev_dbg(&d->udev->dev, "%s: power=%d\n", __func__, onoff);
		अगर (d->props->घातer_ctrl) अणु
			ret = d->props->घातer_ctrl(d, onoff);
			अगर (ret < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usb_fe_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s: adap=%d fe=%d\n", __func__, adap->id,
			fe->id);

	अगर (!adap->suspend_resume_active) अणु
		adap->active_fe = fe->id;
		set_bit(ADAP_INIT, &adap->state_bits);
	पूर्ण

	ret = dvb_usbv2_device_घातer_ctrl(d, 1);
	अगर (ret < 0)
		जाओ err;

	अगर (d->props->frontend_ctrl) अणु
		ret = d->props->frontend_ctrl(fe, 1);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (adap->fe_init[fe->id]) अणु
		ret = adap->fe_init[fe->id](fe);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
err:
	अगर (!adap->suspend_resume_active) अणु
		clear_bit(ADAP_INIT, &adap->state_bits);
		smp_mb__after_atomic();
		wake_up_bit(&adap->state_bits, ADAP_INIT);
	पूर्ण

	dev_dbg(&d->udev->dev, "%s: ret=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usb_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s: adap=%d fe=%d\n", __func__, adap->id,
			fe->id);

	अगर (!adap->suspend_resume_active) अणु
		set_bit(ADAP_SLEEP, &adap->state_bits);
		रुको_on_bit(&adap->state_bits, ADAP_STREAMING,
				TASK_UNINTERRUPTIBLE);
	पूर्ण

	अगर (adap->fe_sleep[fe->id]) अणु
		ret = adap->fe_sleep[fe->id](fe);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (d->props->frontend_ctrl) अणु
		ret = d->props->frontend_ctrl(fe, 0);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	ret = dvb_usbv2_device_घातer_ctrl(d, 0);

err:
	अगर (!adap->suspend_resume_active) अणु
		adap->active_fe = -1;
		clear_bit(ADAP_SLEEP, &adap->state_bits);
		smp_mb__after_atomic();
		wake_up_bit(&adap->state_bits, ADAP_SLEEP);
	पूर्ण

	dev_dbg(&d->udev->dev, "%s: ret=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_frontend_init(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret, i, count_रेजिस्टरed = 0;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	स_रखो(adap->fe, 0, माप(adap->fe));
	adap->active_fe = -1;

	अगर (d->props->frontend_attach) अणु
		ret = d->props->frontend_attach(adap);
		अगर (ret < 0) अणु
			dev_dbg(&d->udev->dev,
					"%s: frontend_attach() failed=%d\n",
					__func__, ret);
			जाओ err_dvb_frontend_detach;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&d->udev->dev, "%s: frontend_attach() do not exists\n",
				__func__);
		ret = 0;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < MAX_NO_OF_FE_PER_ADAP && adap->fe[i]; i++) अणु
		adap->fe[i]->id = i;
		/* re-assign sleep and wakeup functions */
		adap->fe_init[i] = adap->fe[i]->ops.init;
		adap->fe[i]->ops.init = dvb_usb_fe_init;
		adap->fe_sleep[i] = adap->fe[i]->ops.sleep;
		adap->fe[i]->ops.sleep = dvb_usb_fe_sleep;

		ret = dvb_रेजिस्टर_frontend(&adap->dvb_adap, adap->fe[i]);
		अगर (ret < 0) अणु
			dev_err(&d->udev->dev,
					"%s: frontend%d registration failed\n",
					KBUILD_MODNAME, i);
			जाओ err_dvb_unरेजिस्टर_frontend;
		पूर्ण

		count_रेजिस्टरed++;
	पूर्ण

	अगर (d->props->tuner_attach) अणु
		ret = d->props->tuner_attach(adap);
		अगर (ret < 0) अणु
			dev_dbg(&d->udev->dev, "%s: tuner_attach() failed=%d\n",
					__func__, ret);
			जाओ err_dvb_unरेजिस्टर_frontend;
		पूर्ण
	पूर्ण

	ret = dvb_create_media_graph(&adap->dvb_adap, true);
	अगर (ret < 0)
		जाओ err_dvb_unरेजिस्टर_frontend;

	ret = dvb_usbv2_media_device_रेजिस्टर(adap);

	वापस ret;

err_dvb_unरेजिस्टर_frontend:
	क्रम (i = count_रेजिस्टरed - 1; i >= 0; i--)
		dvb_unरेजिस्टर_frontend(adap->fe[i]);

err_dvb_frontend_detach:
	क्रम (i = MAX_NO_OF_FE_PER_ADAP - 1; i >= 0; i--) अणु
		अगर (adap->fe[i]) अणु
			dvb_frontend_detach(adap->fe[i]);
			adap->fe[i] = शून्य;
		पूर्ण
	पूर्ण

err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_frontend_निकास(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret, i;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);

	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	क्रम (i = MAX_NO_OF_FE_PER_ADAP - 1; i >= 0; i--) अणु
		अगर (adap->fe[i]) अणु
			dvb_unरेजिस्टर_frontend(adap->fe[i]);
			dvb_frontend_detach(adap->fe[i]);
		पूर्ण
	पूर्ण

	अगर (d->props->tuner_detach) अणु
		ret = d->props->tuner_detach(adap);
		अगर (ret < 0) अणु
			dev_dbg(&d->udev->dev, "%s: tuner_detach() failed=%d\n",
					__func__, ret);
		पूर्ण
	पूर्ण

	अगर (d->props->frontend_detach) अणु
		ret = d->props->frontend_detach(adap);
		अगर (ret < 0) अणु
			dev_dbg(&d->udev->dev,
					"%s: frontend_detach() failed=%d\n",
					__func__, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा dvb_usb_adapter *adap;
	पूर्णांक ret, i, adapter_count;

	/* resolve adapter count */
	adapter_count = d->props->num_adapters;
	अगर (d->props->get_adapter_count) अणु
		ret = d->props->get_adapter_count(d);
		अगर (ret < 0)
			जाओ err;

		adapter_count = ret;
	पूर्ण

	क्रम (i = 0; i < adapter_count; i++) अणु
		adap = &d->adapter[i];
		adap->id = i;
		adap->props = &d->props->adapter[i];

		/* speed - when running at FULL speed we need a HW PID filter */
		अगर (d->udev->speed == USB_SPEED_FULL &&
				!(adap->props->caps & DVB_USB_ADAP_HAS_PID_FILTER)) अणु
			dev_err(&d->udev->dev,
					"%s: this USB2.0 device cannot be run on a USB1.1 port (it lacks a hardware PID filter)\n",
					KBUILD_MODNAME);
			ret = -ENODEV;
			जाओ err;
		पूर्ण अन्यथा अगर ((d->udev->speed == USB_SPEED_FULL &&
				adap->props->caps & DVB_USB_ADAP_HAS_PID_FILTER) ||
				(adap->props->caps & DVB_USB_ADAP_NEED_PID_FILTERING)) अणु
			dev_info(&d->udev->dev,
					"%s: will use the device's hardware PID filter (table count: %d)\n",
					KBUILD_MODNAME,
					adap->props->pid_filter_count);
			adap->pid_filtering  = 1;
			adap->max_feed_count = adap->props->pid_filter_count;
		पूर्ण अन्यथा अणु
			dev_info(&d->udev->dev,
					"%s: will pass the complete MPEG2 transport stream to the software demuxer\n",
					KBUILD_MODNAME);
			adap->pid_filtering  = 0;
			adap->max_feed_count = 255;
		पूर्ण

		अगर (!adap->pid_filtering && dvb_usb_क्रमce_pid_filter_usage &&
				adap->props->caps & DVB_USB_ADAP_HAS_PID_FILTER) अणु
			dev_info(&d->udev->dev,
					"%s: PID filter enabled by module option\n",
					KBUILD_MODNAME);
			adap->pid_filtering  = 1;
			adap->max_feed_count = adap->props->pid_filter_count;
		पूर्ण

		ret = dvb_usbv2_adapter_stream_init(adap);
		अगर (ret)
			जाओ err;

		ret = dvb_usbv2_adapter_dvb_init(adap);
		अगर (ret)
			जाओ err;

		ret = dvb_usbv2_adapter_frontend_init(adap);
		अगर (ret)
			जाओ err;

		/* use exclusive FE lock अगर there is multiple shared FEs */
		अगर (adap->fe[1])
			adap->dvb_adap.mfe_shared = 1;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usbv2_adapter_निकास(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक i;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	क्रम (i = MAX_NO_OF_ADAPTER_PER_DEVICE - 1; i >= 0; i--) अणु
		अगर (d->adapter[i].props) अणु
			dvb_usbv2_adapter_dvb_निकास(&d->adapter[i]);
			dvb_usbv2_adapter_stream_निकास(&d->adapter[i]);
			dvb_usbv2_adapter_frontend_निकास(&d->adapter[i]);
			dvb_usbv2_media_device_unरेजिस्टर(&d->adapter[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* general initialization functions */
अटल पूर्णांक dvb_usbv2_निकास(काष्ठा dvb_usb_device *d)
अणु
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	dvb_usbv2_remote_निकास(d);
	dvb_usbv2_adapter_निकास(d);
	dvb_usbv2_i2c_निकास(d);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usbv2_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	dvb_usbv2_device_घातer_ctrl(d, 1);

	अगर (d->props->पढ़ो_config) अणु
		ret = d->props->पढ़ो_config(d);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	ret = dvb_usbv2_i2c_init(d);
	अगर (ret < 0)
		जाओ err;

	ret = dvb_usbv2_adapter_init(d);
	अगर (ret < 0)
		जाओ err;

	अगर (d->props->init) अणु
		ret = d->props->init(d);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	ret = dvb_usbv2_remote_init(d);
	अगर (ret < 0)
		जाओ err;

	dvb_usbv2_device_घातer_ctrl(d, 0);

	वापस 0;
err:
	dvb_usbv2_device_घातer_ctrl(d, 0);
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

पूर्णांक dvb_usbv2_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा dvb_usb_device *d;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा dvb_usb_driver_info *driver_info =
			(काष्ठा dvb_usb_driver_info *) id->driver_info;

	dev_dbg(&udev->dev, "%s: bInterfaceNumber=%d\n", __func__,
			पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);

	अगर (!id->driver_info) अणु
		dev_err(&udev->dev, "%s: driver_info failed\n", KBUILD_MODNAME);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	d = kzalloc(माप(काष्ठा dvb_usb_device), GFP_KERNEL);
	अगर (!d) अणु
		dev_err(&udev->dev, "%s: kzalloc() failed\n", KBUILD_MODNAME);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	d->पूर्णांकf = पूर्णांकf;
	d->name = driver_info->name;
	d->rc_map = driver_info->rc_map;
	d->udev = udev;
	d->props = driver_info->props;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber !=
			d->props->bInterfaceNumber) अणु
		ret = -ENODEV;
		जाओ err_kमुक्त_d;
	पूर्ण

	mutex_init(&d->usb_mutex);
	mutex_init(&d->i2c_mutex);

	अगर (d->props->size_of_priv) अणु
		d->priv = kzalloc(d->props->size_of_priv, GFP_KERNEL);
		अगर (!d->priv) अणु
			dev_err(&d->udev->dev, "%s: kzalloc() failed\n",
					KBUILD_MODNAME);
			ret = -ENOMEM;
			जाओ err_kमुक्त_d;
		पूर्ण
	पूर्ण

	अगर (d->props->probe) अणु
		ret = d->props->probe(d);
		अगर (ret)
			जाओ err_kमुक्त_priv;
	पूर्ण

	अगर (d->props->identअगरy_state) अणु
		स्थिर अक्षर *name = शून्य;
		ret = d->props->identअगरy_state(d, &name);
		अगर (ret == COLD) अणु
			dev_info(&d->udev->dev,
					"%s: found a '%s' in cold state\n",
					KBUILD_MODNAME, d->name);

			अगर (!name)
				name = d->props->firmware;

			ret = dvb_usbv2_करोwnload_firmware(d, name);
			अगर (ret == 0) अणु
				/* device is warm, जारी initialization */
				;
			पूर्ण अन्यथा अगर (ret == RECONNECTS_USB) अणु
				/*
				 * USB core will call disconnect() and then
				 * probe() as device reconnects itself from the
				 * USB bus. disconnect() will release all driver
				 * resources and probe() is called क्रम 'new'
				 * device. As 'new' device is warm we should
				 * never go here again.
				 */
				जाओ निकास;
			पूर्ण अन्यथा अणु
				जाओ err_मुक्त_all;
			पूर्ण
		पूर्ण अन्यथा अगर (ret != WARM) अणु
			जाओ err_मुक्त_all;
		पूर्ण
	पूर्ण

	dev_info(&d->udev->dev, "%s: found a '%s' in warm state\n",
			KBUILD_MODNAME, d->name);

	ret = dvb_usbv2_init(d);
	अगर (ret < 0)
		जाओ err_मुक्त_all;

	dev_info(&d->udev->dev,
			"%s: '%s' successfully initialized and connected\n",
			KBUILD_MODNAME, d->name);
निकास:
	usb_set_पूर्णांकfdata(पूर्णांकf, d);

	वापस 0;
err_मुक्त_all:
	dvb_usbv2_निकास(d);
	अगर (d->props->disconnect)
		d->props->disconnect(d);
err_kमुक्त_priv:
	kमुक्त(d->priv);
err_kमुक्त_d:
	kमुक्त(d);
err:
	dev_dbg(&udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_probe);

व्योम dvb_usbv2_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	स्थिर अक्षर *devname = kstrdup(dev_name(&d->udev->dev), GFP_KERNEL);
	स्थिर अक्षर *drvname = d->name;

	dev_dbg(&d->udev->dev, "%s: bInterfaceNumber=%d\n", __func__,
			पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);

	अगर (d->props->निकास)
		d->props->निकास(d);

	dvb_usbv2_निकास(d);

	अगर (d->props->disconnect)
		d->props->disconnect(d);

	kमुक्त(d->priv);
	kमुक्त(d);

	pr_info("%s: '%s:%s' successfully deinitialized and disconnected\n",
		KBUILD_MODNAME, drvname, devname);
	kमुक्त(devname);
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_disconnect);

पूर्णांक dvb_usbv2_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t msg)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret = 0, i, active_fe;
	काष्ठा dvb_frontend *fe;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	/* stop remote controller poll */
	अगर (d->rc_polling_active)
		cancel_delayed_work_sync(&d->rc_query_work);

	क्रम (i = MAX_NO_OF_ADAPTER_PER_DEVICE - 1; i >= 0; i--) अणु
		active_fe = d->adapter[i].active_fe;
		अगर (d->adapter[i].dvb_adap.priv && active_fe != -1) अणु
			fe = d->adapter[i].fe[active_fe];
			d->adapter[i].suspend_resume_active = true;

			अगर (d->props->streaming_ctrl)
				d->props->streaming_ctrl(fe, 0);

			/* stop usb streaming */
			usb_urb_समाप्तv2(&d->adapter[i].stream);

			ret = dvb_frontend_suspend(fe);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_suspend);

अटल पूर्णांक dvb_usbv2_resume_common(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret = 0, i, active_fe;
	काष्ठा dvb_frontend *fe;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	क्रम (i = 0; i < MAX_NO_OF_ADAPTER_PER_DEVICE; i++) अणु
		active_fe = d->adapter[i].active_fe;
		अगर (d->adapter[i].dvb_adap.priv && active_fe != -1) अणु
			fe = d->adapter[i].fe[active_fe];

			ret = dvb_frontend_resume(fe);

			/* resume usb streaming */
			usb_urb_submitv2(&d->adapter[i].stream, शून्य);

			अगर (d->props->streaming_ctrl)
				d->props->streaming_ctrl(fe, 1);

			d->adapter[i].suspend_resume_active = false;
		पूर्ण
	पूर्ण

	/* start remote controller poll */
	अगर (d->rc_polling_active)
		schedule_delayed_work(&d->rc_query_work,
				msecs_to_jअगरfies(d->rc.पूर्णांकerval));

	वापस ret;
पूर्ण

पूर्णांक dvb_usbv2_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	वापस dvb_usbv2_resume_common(d);
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_resume);

पूर्णांक dvb_usbv2_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	dvb_usbv2_device_घातer_ctrl(d, 1);

	अगर (d->props->init)
		d->props->init(d);

	ret = dvb_usbv2_resume_common(d);

	dvb_usbv2_device_घातer_ctrl(d, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_reset_resume);

MODULE_VERSION("2.0");
MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("DVB USB common");
MODULE_LICENSE("GPL");
