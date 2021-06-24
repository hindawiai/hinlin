<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* dvb-usb-dvb.c is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file contains functions क्रम initializing and handling the
 * linux-dvb API.
 */
#समावेश "dvb-usb-common.h"
#समावेश <media/media-device.h>

/* करोes the complete input transfer handling */
अटल पूर्णांक dvb_usb_ctrl_feed(काष्ठा dvb_demux_feed *dvbdmxfeed, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = dvbdmxfeed->demux->priv;
	पूर्णांक newfeedcount, ret;

	अगर (adap == शून्य)
		वापस -ENODEV;

	अगर ((adap->active_fe < 0) ||
	    (adap->active_fe >= adap->num_frontends_initialized)) अणु
		वापस -EINVAL;
	पूर्ण

	newfeedcount = adap->feedcount + (onoff ? 1 : -1);

	/* stop feed beक्रमe setting a new pid अगर there will be no pid anymore */
	अगर (newfeedcount == 0) अणु
		deb_ts("stop feeding\n");
		usb_urb_समाप्त(&adap->fe_adap[adap->active_fe].stream);

		अगर (adap->props.fe[adap->active_fe].streaming_ctrl != शून्य) अणु
			ret = adap->props.fe[adap->active_fe].streaming_ctrl(adap, 0);
			अगर (ret < 0) अणु
				err("error while stopping stream.");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	adap->feedcount = newfeedcount;

	/* activate the pid on the device specअगरic pid_filter */
	deb_ts("setting pid (%s): %5d %04x at index %d '%s'\n",
		adap->fe_adap[adap->active_fe].pid_filtering ?
		"yes" : "no", dvbdmxfeed->pid, dvbdmxfeed->pid,
		dvbdmxfeed->index, onoff ? "on" : "off");
	अगर (adap->props.fe[adap->active_fe].caps & DVB_USB_ADAP_HAS_PID_FILTER &&
		adap->fe_adap[adap->active_fe].pid_filtering &&
		adap->props.fe[adap->active_fe].pid_filter != शून्य)
		adap->props.fe[adap->active_fe].pid_filter(adap, dvbdmxfeed->index, dvbdmxfeed->pid, onoff);

	/* start the feed अगर this was the first feed and there is still a feed
	 * क्रम reception.
	 */
	अगर (adap->feedcount == onoff && adap->feedcount > 0) अणु
		deb_ts("controlling pid parser\n");
		अगर (adap->props.fe[adap->active_fe].caps & DVB_USB_ADAP_HAS_PID_FILTER &&
			adap->props.fe[adap->active_fe].caps &
			DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF &&
			adap->props.fe[adap->active_fe].pid_filter_ctrl != शून्य) अणु
			ret = adap->props.fe[adap->active_fe].pid_filter_ctrl(adap,
				adap->fe_adap[adap->active_fe].pid_filtering);
			अगर (ret < 0) अणु
				err("could not handle pid_parser");
				वापस ret;
			पूर्ण
		पूर्ण
		deb_ts("start feeding\n");
		अगर (adap->props.fe[adap->active_fe].streaming_ctrl != शून्य) अणु
			ret = adap->props.fe[adap->active_fe].streaming_ctrl(adap, 1);
			अगर (ret < 0) अणु
				err("error while enabling fifo.");
				वापस ret;
			पूर्ण
		पूर्ण

		deb_ts("submitting all URBs\n");
		usb_urb_submit(&adap->fe_adap[adap->active_fe].stream);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usb_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	deb_ts("start pid: 0x%04x, feedtype: %d\n", dvbdmxfeed->pid,
	       dvbdmxfeed->type);
	वापस dvb_usb_ctrl_feed(dvbdmxfeed, 1);
पूर्ण

अटल पूर्णांक dvb_usb_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	deb_ts("stop pid: 0x%04x, feedtype: %d\n", dvbdmxfeed->pid, dvbdmxfeed->type);
	वापस dvb_usb_ctrl_feed(dvbdmxfeed, 0);
पूर्ण

अटल पूर्णांक dvb_usb_media_device_init(काष्ठा dvb_usb_adapter *adap)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	काष्ठा media_device *mdev;
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा usb_device *udev = d->udev;

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	media_device_usb_init(mdev, udev, d->desc->name);

	dvb_रेजिस्टर_media_controller(&adap->dvb_adap, mdev);

	dev_info(&d->udev->dev, "media controller created\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक  dvb_usb_media_device_रेजिस्टर(काष्ठा dvb_usb_adapter *adap)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	वापस media_device_रेजिस्टर(adap->dvb_adap.mdev);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम dvb_usb_media_device_unरेजिस्टर(काष्ठा dvb_usb_adapter *adap)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	अगर (!adap->dvb_adap.mdev)
		वापस;

	mutex_lock(&adap->dvb_adap.mdev_lock);

	media_device_unरेजिस्टर(adap->dvb_adap.mdev);
	media_device_cleanup(adap->dvb_adap.mdev);
	kमुक्त(adap->dvb_adap.mdev);
	adap->dvb_adap.mdev = शून्य;

	mutex_unlock(&adap->dvb_adap.mdev_lock);
#पूर्ण_अगर
पूर्ण

पूर्णांक dvb_usb_adapter_dvb_init(काष्ठा dvb_usb_adapter *adap, लघु *adapter_nums)
अणु
	पूर्णांक i;
	पूर्णांक ret = dvb_रेजिस्टर_adapter(&adap->dvb_adap, adap->dev->desc->name,
				       adap->dev->owner, &adap->dev->udev->dev,
				       adapter_nums);

	अगर (ret < 0) अणु
		deb_info("dvb_register_adapter failed: error %d", ret);
		जाओ err;
	पूर्ण
	adap->dvb_adap.priv = adap;

	ret = dvb_usb_media_device_init(adap);
	अगर (ret < 0) अणु
		deb_info("dvb_usb_media_device_init failed: error %d", ret);
		जाओ err_mc;
	पूर्ण

	अगर (adap->dev->props.पढ़ो_mac_address) अणु
		अगर (adap->dev->props.पढ़ो_mac_address(adap->dev, adap->dvb_adap.proposed_mac) == 0)
			info("MAC address: %pM", adap->dvb_adap.proposed_mac);
		अन्यथा
			err("MAC address reading failed.");
	पूर्ण


	adap->demux.dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING;
	adap->demux.priv             = adap;

	adap->demux.filternum        = 0;
	क्रम (i = 0; i < adap->props.num_frontends; i++) अणु
		अगर (adap->demux.filternum < adap->fe_adap[i].max_feed_count)
			adap->demux.filternum = adap->fe_adap[i].max_feed_count;
	पूर्ण
	adap->demux.feednum          = adap->demux.filternum;
	adap->demux.start_feed       = dvb_usb_start_feed;
	adap->demux.stop_feed        = dvb_usb_stop_feed;
	adap->demux.ग_लिखो_to_decoder = शून्य;
	अगर ((ret = dvb_dmx_init(&adap->demux)) < 0) अणु
		err("dvb_dmx_init failed: error %d", ret);
		जाओ err_dmx;
	पूर्ण

	adap->dmxdev.filternum       = adap->demux.filternum;
	adap->dmxdev.demux           = &adap->demux.dmx;
	adap->dmxdev.capabilities    = 0;
	अगर ((ret = dvb_dmxdev_init(&adap->dmxdev, &adap->dvb_adap)) < 0) अणु
		err("dvb_dmxdev_init failed: error %d", ret);
		जाओ err_dmx_dev;
	पूर्ण

	अगर ((ret = dvb_net_init(&adap->dvb_adap, &adap->dvb_net,
						&adap->demux.dmx)) < 0) अणु
		err("dvb_net_init failed: error %d", ret);
		जाओ err_net_init;
	पूर्ण

	adap->state |= DVB_USB_ADAP_STATE_DVB;
	वापस 0;

err_net_init:
	dvb_dmxdev_release(&adap->dmxdev);
err_dmx_dev:
	dvb_dmx_release(&adap->demux);
err_dmx:
	dvb_usb_media_device_unरेजिस्टर(adap);
err_mc:
	dvb_unरेजिस्टर_adapter(&adap->dvb_adap);
err:
	वापस ret;
पूर्ण

पूर्णांक dvb_usb_adapter_dvb_निकास(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (adap->state & DVB_USB_ADAP_STATE_DVB) अणु
		deb_info("unregistering DVB part\n");
		dvb_net_release(&adap->dvb_net);
		adap->demux.dmx.बंद(&adap->demux.dmx);
		dvb_dmxdev_release(&adap->dmxdev);
		dvb_dmx_release(&adap->demux);
		dvb_usb_media_device_unरेजिस्टर(adap);
		dvb_unरेजिस्टर_adapter(&adap->dvb_adap);
		adap->state &= ~DVB_USB_ADAP_STATE_DVB;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usb_set_active_fe(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;

	पूर्णांक ret = (adap->props.frontend_ctrl) ?
		adap->props.frontend_ctrl(fe, onoff) : 0;

	अगर (ret < 0) अणु
		err("frontend_ctrl request failed");
		वापस ret;
	पूर्ण
	अगर (onoff)
		adap->active_fe = fe->id;

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usb_fe_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;

	dvb_usb_device_घातer_ctrl(adap->dev, 1);

	dvb_usb_set_active_fe(fe, 1);

	अगर (adap->fe_adap[fe->id].fe_init)
		adap->fe_adap[fe->id].fe_init(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_usb_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;

	अगर (adap->fe_adap[fe->id].fe_sleep)
		adap->fe_adap[fe->id].fe_sleep(fe);

	dvb_usb_set_active_fe(fe, 0);

	वापस dvb_usb_device_घातer_ctrl(adap->dev, 0);
पूर्ण

पूर्णांक dvb_usb_adapter_frontend_init(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret, i;

	/* रेजिस्टर all given adapter frontends */
	क्रम (i = 0; i < adap->props.num_frontends; i++) अणु

		अगर (adap->props.fe[i].frontend_attach == शून्य) अणु
			err("strange: '%s' #%d,%d doesn't want to attach a frontend.",
			    adap->dev->desc->name, adap->id, i);

			वापस 0;
		पूर्ण

		ret = adap->props.fe[i].frontend_attach(adap);
		अगर (ret || adap->fe_adap[i].fe == शून्य) अणु
			/* only prपूर्णांक error when there is no FE at all */
			अगर (i == 0)
				err("no frontend was attached by '%s'",
					adap->dev->desc->name);

			वापस 0;
		पूर्ण

		adap->fe_adap[i].fe->id = i;

		/* re-assign sleep and wakeup functions */
		adap->fe_adap[i].fe_init = adap->fe_adap[i].fe->ops.init;
		adap->fe_adap[i].fe->ops.init  = dvb_usb_fe_wakeup;
		adap->fe_adap[i].fe_sleep = adap->fe_adap[i].fe->ops.sleep;
		adap->fe_adap[i].fe->ops.sleep = dvb_usb_fe_sleep;

		अगर (dvb_रेजिस्टर_frontend(&adap->dvb_adap, adap->fe_adap[i].fe)) अणु
			err("Frontend %d registration failed.", i);
			dvb_frontend_detach(adap->fe_adap[i].fe);
			adap->fe_adap[i].fe = शून्य;
			/* In error हाल, करो not try रेजिस्टर more FEs,
			 * still leaving alपढ़ोy रेजिस्टरed FEs alive. */
			अगर (i == 0)
				वापस -ENODEV;
			अन्यथा
				वापस 0;
		पूर्ण

		/* only attach the tuner अगर the demod is there */
		अगर (adap->props.fe[i].tuner_attach != शून्य)
			adap->props.fe[i].tuner_attach(adap);

		adap->num_frontends_initialized++;
	पूर्ण

	ret = dvb_create_media_graph(&adap->dvb_adap, true);
	अगर (ret)
		वापस ret;

	ret = dvb_usb_media_device_रेजिस्टर(adap);

	वापस ret;
पूर्ण

पूर्णांक dvb_usb_adapter_frontend_निकास(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक i = adap->num_frontends_initialized - 1;

	/* unरेजिस्टर all given adapter frontends */
	क्रम (; i >= 0; i--) अणु
		अगर (adap->fe_adap[i].fe != शून्य) अणु
			dvb_unरेजिस्टर_frontend(adap->fe_adap[i].fe);
			dvb_frontend_detach(adap->fe_adap[i].fe);
		पूर्ण
	पूर्ण
	adap->num_frontends_initialized = 0;

	वापस 0;
पूर्ण
