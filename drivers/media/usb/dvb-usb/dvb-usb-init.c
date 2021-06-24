<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DVB USB library - provides a generic पूर्णांकerface क्रम a DVB USB device driver.
 *
 * dvb-usb-init.c
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "dvb-usb-common.h"

/* debug */
पूर्णांक dvb_usb_debug;
module_param_named(debug, dvb_usb_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,xfer=2,pll=4,ts=8,err=16,rc=32,fw=64,mem=128,uxfer=256  (or-able))." DVB_USB_DEBUG_STATUS);

पूर्णांक dvb_usb_disable_rc_polling;
module_param_named(disable_rc_polling, dvb_usb_disable_rc_polling, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_rc_polling, "disable remote control polling (default: 0).");

अटल पूर्णांक dvb_usb_क्रमce_pid_filter_usage;
module_param_named(क्रमce_pid_filter_usage, dvb_usb_क्रमce_pid_filter_usage, पूर्णांक, 0444);
MODULE_PARM_DESC(क्रमce_pid_filter_usage, "force all dvb-usb-devices to use a PID filter, if any (default: 0).");

अटल पूर्णांक dvb_usb_adapter_init(काष्ठा dvb_usb_device *d, लघु *adapter_nrs)
अणु
	काष्ठा dvb_usb_adapter *adap;
	पूर्णांक ret, n, o;

	क्रम (n = 0; n < d->props.num_adapters; n++) अणु
		adap = &d->adapter[n];
		adap->dev = d;
		adap->id  = n;

		स_नकल(&adap->props, &d->props.adapter[n], माप(काष्ठा dvb_usb_adapter_properties));

		क्रम (o = 0; o < adap->props.num_frontends; o++) अणु
			काष्ठा dvb_usb_adapter_fe_properties *props = &adap->props.fe[o];
			/* speed - when running at FULL speed we need a HW PID filter */
			अगर (d->udev->speed == USB_SPEED_FULL && !(props->caps & DVB_USB_ADAP_HAS_PID_FILTER)) अणु
				err("This USB2.0 device cannot be run on a USB1.1 port. (it lacks a hardware PID filter)");
				वापस -ENODEV;
			पूर्ण

			अगर ((d->udev->speed == USB_SPEED_FULL && props->caps & DVB_USB_ADAP_HAS_PID_FILTER) ||
				(props->caps & DVB_USB_ADAP_NEED_PID_FILTERING)) अणु
				info("will use the device's hardware PID filter (table count: %d).", props->pid_filter_count);
				adap->fe_adap[o].pid_filtering  = 1;
				adap->fe_adap[o].max_feed_count = props->pid_filter_count;
			पूर्ण अन्यथा अणु
				info("will pass the complete MPEG2 transport stream to the software demuxer.");
				adap->fe_adap[o].pid_filtering  = 0;
				adap->fe_adap[o].max_feed_count = 255;
			पूर्ण

			अगर (!adap->fe_adap[o].pid_filtering &&
				dvb_usb_क्रमce_pid_filter_usage &&
				props->caps & DVB_USB_ADAP_HAS_PID_FILTER) अणु
				info("pid filter enabled by module option.");
				adap->fe_adap[o].pid_filtering  = 1;
				adap->fe_adap[o].max_feed_count = props->pid_filter_count;
			पूर्ण

			अगर (props->size_of_priv > 0) अणु
				adap->fe_adap[o].priv = kzalloc(props->size_of_priv, GFP_KERNEL);
				अगर (adap->fe_adap[o].priv == शून्य) अणु
					err("no memory for priv for adapter %d fe %d.", n, o);
					वापस -ENOMEM;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (adap->props.size_of_priv > 0) अणु
			adap->priv = kzalloc(adap->props.size_of_priv, GFP_KERNEL);
			अगर (adap->priv == शून्य) अणु
				err("no memory for priv for adapter %d.", n);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		ret = dvb_usb_adapter_stream_init(adap);
		अगर (ret)
			वापस ret;

		ret = dvb_usb_adapter_dvb_init(adap, adapter_nrs);
		अगर (ret)
			जाओ dvb_init_err;

		ret = dvb_usb_adapter_frontend_init(adap);
		अगर (ret)
			जाओ frontend_init_err;

		/* use exclusive FE lock अगर there is multiple shared FEs */
		अगर (adap->fe_adap[1].fe)
			adap->dvb_adap.mfe_shared = 1;

		d->num_adapters_initialized++;
		d->state |= DVB_USB_STATE_DVB;
	पूर्ण

	/*
	 * when reloading the driver w/o replugging the device
	 * someबार a समयout occurs, this helps
	 */
	अगर (d->props.generic_bulk_ctrl_endpoपूर्णांक != 0) अणु
		usb_clear_halt(d->udev, usb_sndbulkpipe(d->udev, d->props.generic_bulk_ctrl_endpoपूर्णांक));
		usb_clear_halt(d->udev, usb_rcvbulkpipe(d->udev, d->props.generic_bulk_ctrl_endpoपूर्णांक));
	पूर्ण

	वापस 0;

frontend_init_err:
	dvb_usb_adapter_dvb_निकास(adap);
dvb_init_err:
	dvb_usb_adapter_stream_निकास(adap);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_usb_adapter_निकास(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < d->num_adapters_initialized; n++) अणु
		dvb_usb_adapter_frontend_निकास(&d->adapter[n]);
		dvb_usb_adapter_dvb_निकास(&d->adapter[n]);
		dvb_usb_adapter_stream_निकास(&d->adapter[n]);
		kमुक्त(d->adapter[n].priv);
	पूर्ण
	d->num_adapters_initialized = 0;
	d->state &= ~DVB_USB_STATE_DVB;
	वापस 0;
पूर्ण


/* general initialization functions */
अटल पूर्णांक dvb_usb_निकास(काष्ठा dvb_usb_device *d)
अणु
	deb_info("state before exiting everything: %x\n", d->state);
	dvb_usb_remote_निकास(d);
	dvb_usb_adapter_निकास(d);
	dvb_usb_i2c_निकास(d);
	deb_info("state should be zero now: %x\n", d->state);
	d->state = DVB_USB_STATE_INIT;

	अगर (d->priv != शून्य && d->props.priv_destroy != शून्य)
		d->props.priv_destroy(d);

	kमुक्त(d->priv);
	kमुक्त(d);
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usb_init(काष्ठा dvb_usb_device *d, लघु *adapter_nums)
अणु
	पूर्णांक ret = 0;

	mutex_init(&d->data_mutex);
	mutex_init(&d->usb_mutex);
	mutex_init(&d->i2c_mutex);

	d->state = DVB_USB_STATE_INIT;

	अगर (d->props.size_of_priv > 0) अणु
		d->priv = kzalloc(d->props.size_of_priv, GFP_KERNEL);
		अगर (d->priv == शून्य) अणु
			err("no memory for priv in 'struct dvb_usb_device'");
			वापस -ENOMEM;
		पूर्ण

		अगर (d->props.priv_init != शून्य) अणु
			ret = d->props.priv_init(d);
			अगर (ret != 0)
				जाओ err_priv_init;
		पूर्ण
	पूर्ण

	/* check the capabilities and set appropriate variables */
	dvb_usb_device_घातer_ctrl(d, 1);

	ret = dvb_usb_i2c_init(d);
	अगर (ret)
		जाओ err_i2c_init;
	ret = dvb_usb_adapter_init(d, adapter_nums);
	अगर (ret)
		जाओ err_adapter_init;

	अगर ((ret = dvb_usb_remote_init(d)))
		err("could not initialize remote control.");

	dvb_usb_device_घातer_ctrl(d, 0);

	वापस 0;

err_adapter_init:
	dvb_usb_adapter_निकास(d);
err_i2c_init:
	dvb_usb_i2c_निकास(d);
	अगर (d->priv && d->props.priv_destroy)
		d->props.priv_destroy(d);
err_priv_init:
	kमुक्त(d->priv);
	d->priv = शून्य;
	वापस ret;
पूर्ण

/* determine the name and the state of the just found USB device */
अटल स्थिर काष्ठा dvb_usb_device_description *dvb_usb_find_device(काष्ठा usb_device *udev, स्थिर काष्ठा dvb_usb_device_properties *props, पूर्णांक *cold)
अणु
	पूर्णांक i, j;
	स्थिर काष्ठा dvb_usb_device_description *desc = शून्य;

	*cold = -1;

	क्रम (i = 0; i < props->num_device_descs; i++) अणु

		क्रम (j = 0; j < DVB_USB_ID_MAX_NUM && props->devices[i].cold_ids[j] != शून्य; j++) अणु
			deb_info("check for cold %x %x\n", props->devices[i].cold_ids[j]->idVenकरोr, props->devices[i].cold_ids[j]->idProduct);
			अगर (props->devices[i].cold_ids[j]->idVenकरोr  == le16_to_cpu(udev->descriptor.idVenकरोr) &&
				props->devices[i].cold_ids[j]->idProduct == le16_to_cpu(udev->descriptor.idProduct)) अणु
				*cold = 1;
				desc = &props->devices[i];
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (desc != शून्य)
			अवरोध;

		क्रम (j = 0; j < DVB_USB_ID_MAX_NUM && props->devices[i].warm_ids[j] != शून्य; j++) अणु
			deb_info("check for warm %x %x\n", props->devices[i].warm_ids[j]->idVenकरोr, props->devices[i].warm_ids[j]->idProduct);
			अगर (props->devices[i].warm_ids[j]->idVenकरोr == le16_to_cpu(udev->descriptor.idVenकरोr) &&
				props->devices[i].warm_ids[j]->idProduct == le16_to_cpu(udev->descriptor.idProduct)) अणु
				*cold = 0;
				desc = &props->devices[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (desc != शून्य && props->identअगरy_state != शून्य)
		props->identअगरy_state(udev, props, &desc, cold);

	वापस desc;
पूर्ण

पूर्णांक dvb_usb_device_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	अगर (onoff)
		d->घातered++;
	अन्यथा
		d->घातered--;

	अगर (d->घातered == 0 || (onoff && d->घातered == 1)) अणु /* when चयनing from 1 to 0 or from 0 to 1 */
		deb_info("power control: %d\n", onoff);
		अगर (d->props.घातer_ctrl)
			वापस d->props.घातer_ctrl(d, onoff);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * USB
 */
पूर्णांक dvb_usb_device_init(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा dvb_usb_device_properties *props,
			काष्ठा module *owner, काष्ठा dvb_usb_device **du,
			लघु *adapter_nums)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा dvb_usb_device *d = शून्य;
	स्थिर काष्ठा dvb_usb_device_description *desc = शून्य;

	पूर्णांक ret = -ENOMEM, cold = 0;

	अगर (du != शून्य)
		*du = शून्य;

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		err("no memory for 'struct dvb_usb_device'");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&d->props, props, माप(काष्ठा dvb_usb_device_properties));

	desc = dvb_usb_find_device(udev, &d->props, &cold);
	अगर (!desc) अणु
		deb_err("something went very wrong, device was not found in current device list - let's see what comes next.\n");
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (cold) अणु
		info("found a '%s' in cold state, will try to load a firmware", desc->name);
		ret = dvb_usb_करोwnload_firmware(udev, props);
		अगर (!props->no_reconnect || ret != 0)
			जाओ error;
	पूर्ण

	info("found a '%s' in warm state.", desc->name);
	d->udev = udev;
	d->desc = desc;
	d->owner = owner;

	usb_set_पूर्णांकfdata(पूर्णांकf, d);

	ret = dvb_usb_init(d, adapter_nums);
	अगर (ret) अणु
		info("%s error while loading driver (%d)", desc->name, ret);
		जाओ error;
	पूर्ण

	अगर (du)
		*du = d;

	info("%s successfully initialized and connected.", desc->name);
	वापस 0;

 error:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	kमुक्त(d);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_usb_device_init);

व्योम dvb_usb_device_निकास(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	स्थिर अक्षर *शेष_name = "generic DVB-USB module";
	अक्षर name[40];

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (d != शून्य && d->desc != शून्य) अणु
		strscpy(name, d->desc->name, माप(name));
		dvb_usb_निकास(d);
	पूर्ण अन्यथा अणु
		strscpy(name, शेष_name, माप(name));
	पूर्ण
	info("%s successfully deinitialized and disconnected.", name);

पूर्ण
EXPORT_SYMBOL(dvb_usb_device_निकास);

MODULE_VERSION("1.0");
MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("A library module containing commonly used USB and DVB function USB DVB devices");
MODULE_LICENSE("GPL");
