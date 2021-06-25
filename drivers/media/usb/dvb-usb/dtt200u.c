<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB library compliant Linux driver क्रम the WideView/ Yakumo/ Hama/
 * Typhoon/ Yuan/ Miglia DVB-T USB2.0 receiver.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * Thanks to Steve Chang from WideView क्रम providing support क्रम the WT-220U.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "dtt200u.h"

/* debug */
पूर्णांक dvb_usb_dtt200u_debug;
module_param_named(debug,dvb_usb_dtt200u_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,xfer=2 (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा dtt200u_state अणु
	अचिन्हित अक्षर data[80];
पूर्ण;

अटल पूर्णांक dtt200u_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	काष्ठा dtt200u_state *st = d->priv;
	पूर्णांक ret = 0;

	mutex_lock(&d->data_mutex);

	st->data[0] = SET_INIT;

	अगर (onoff)
		ret = dvb_usb_generic_ग_लिखो(d, st->data, 2);

	mutex_unlock(&d->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा dtt200u_state *st = d->priv;
	पूर्णांक ret;

	mutex_lock(&d->data_mutex);
	st->data[0] = SET_STREAMING;
	st->data[1] = onoff;

	ret = dvb_usb_generic_ग_लिखो(adap->dev, st->data, 2);
	अगर (ret < 0)
		जाओ ret;

	अगर (onoff)
		जाओ ret;

	st->data[0] = RESET_PID_FILTER;
	ret = dvb_usb_generic_ग_लिखो(adap->dev, st->data, 1);

ret:
	mutex_unlock(&d->data_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index, u16 pid, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा dtt200u_state *st = d->priv;
	पूर्णांक ret;

	pid = onoff ? pid : 0;

	mutex_lock(&d->data_mutex);
	st->data[0] = SET_PID_FILTER;
	st->data[1] = index;
	st->data[2] = pid & 0xff;
	st->data[3] = (pid >> 8) & 0x1f;

	ret = dvb_usb_generic_ग_लिखो(adap->dev, st->data, 4);
	mutex_unlock(&d->data_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_rc_query(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा dtt200u_state *st = d->priv;
	u32 scancode;
	पूर्णांक ret;

	mutex_lock(&d->data_mutex);
	st->data[0] = GET_RC_CODE;

	ret = dvb_usb_generic_rw(d, st->data, 1, st->data, 5, 0);
	अगर (ret < 0)
		जाओ ret;

	अगर (st->data[0] == 1) अणु
		क्रमागत rc_proto proto = RC_PROTO_NEC;

		scancode = st->data[1];
		अगर ((u8) ~st->data[1] != st->data[2]) अणु
			/* Extended NEC */
			scancode = scancode << 8;
			scancode |= st->data[2];
			proto = RC_PROTO_NECX;
		पूर्ण
		scancode = scancode << 8;
		scancode |= st->data[3];

		/* Check command checksum is ok */
		अगर ((u8) ~st->data[3] == st->data[4])
			rc_keyकरोwn(d->rc_dev, proto, scancode, 0);
		अन्यथा
			rc_keyup(d->rc_dev);
	पूर्ण अन्यथा अगर (st->data[0] == 2) अणु
		rc_repeat(d->rc_dev);
	पूर्ण अन्यथा अणु
		rc_keyup(d->rc_dev);
	पूर्ण

	अगर (st->data[0] != 0)
		deb_info("st->data: %*ph\n", 5, st->data);

ret:
	mutex_unlock(&d->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	adap->fe_adap[0].fe = dtt200u_fe_attach(adap->dev);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties dtt200u_properties;
अटल काष्ठा dvb_usb_device_properties wt220u_fc_properties;
अटल काष्ठा dvb_usb_device_properties wt220u_properties;
अटल काष्ठा dvb_usb_device_properties wt220u_zl0353_properties;
अटल काष्ठा dvb_usb_device_properties wt220u_miglia_properties;

अटल पूर्णांक dtt200u_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (0 == dvb_usb_device_init(पूर्णांकf, &dtt200u_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &wt220u_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &wt220u_fc_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &wt220u_zl0353_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &wt220u_miglia_properties,
				     THIS_MODULE, शून्य, adapter_nr))
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल काष्ठा usb_device_id dtt200u_usb_table [] = अणु
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_DTT200U_COLD) पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_DTT200U_WARM) पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_WT220U_COLD)  पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_WT220U_WARM)  पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_WT220U_ZL0353_COLD)  पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_WT220U_ZL0353_WARM)  पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_WT220U_FC_COLD)  पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_WT220U_FC_WARM)  पूर्ण,
	अणु USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_WT220U_ZAP250_COLD)  पूर्ण,
	अणु USB_DEVICE(USB_VID_MIGLIA, USB_PID_WT220U_ZAP250_COLD)  पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, dtt200u_usb_table);

अटल काष्ठा dvb_usb_device_properties dtt200u_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-dtt200u-01.fw",

	.size_of_priv     = माप(काष्ठा dtt200u_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_NEED_PID_FILTERING,
			.pid_filter_count = 15,

	.streaming_ctrl  = dtt200u_streaming_ctrl,
	.pid_filter      = dtt200u_pid_filter,
	.frontend_attach = dtt200u_frontend_attach,
	/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
		.count = 7,
		.endpoपूर्णांक = 0x02,
		.u = अणु
			.bulk = अणु
				.buffersize = 4096,
			पूर्ण
		पूर्ण
	पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.घातer_ctrl      = dtt200u_घातer_ctrl,

	.rc.core = अणु
		.rc_पूर्णांकerval     = 300,
		.rc_codes        = RC_MAP_DTT200U,
		.rc_query        = dtt200u_rc_query,
		.allowed_protos  = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु .name = "WideView/Yuan/Yakumo/Hama/Typhoon DVB-T USB2.0 (WT-200U)",
		  .cold_ids = अणु &dtt200u_usb_table[0], शून्य पूर्ण,
		  .warm_ids = अणु &dtt200u_usb_table[1], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties wt220u_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-wt220u-02.fw",

	.size_of_priv     = माप(काष्ठा dtt200u_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_NEED_PID_FILTERING,
			.pid_filter_count = 15,

	.streaming_ctrl  = dtt200u_streaming_ctrl,
	.pid_filter      = dtt200u_pid_filter,
	.frontend_attach = dtt200u_frontend_attach,
	/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
		.count = 7,
		.endpoपूर्णांक = 0x02,
		.u = अणु
			.bulk = अणु
				.buffersize = 4096,
			पूर्ण
		पूर्ण
	पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.घातer_ctrl      = dtt200u_घातer_ctrl,

	.rc.core = अणु
		.rc_पूर्णांकerval     = 300,
		.rc_codes        = RC_MAP_DTT200U,
		.rc_query        = dtt200u_rc_query,
		.allowed_protos  = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु .name = "WideView WT-220U PenType Receiver (Typhoon/Freecom)",
		  .cold_ids = अणु &dtt200u_usb_table[2], &dtt200u_usb_table[8], शून्य पूर्ण,
		  .warm_ids = अणु &dtt200u_usb_table[3], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties wt220u_fc_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-wt220u-fc03.fw",

	.size_of_priv     = माप(काष्ठा dtt200u_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_NEED_PID_FILTERING,
			.pid_filter_count = 15,

	.streaming_ctrl  = dtt200u_streaming_ctrl,
	.pid_filter      = dtt200u_pid_filter,
	.frontend_attach = dtt200u_frontend_attach,
	/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
		.count = 7,
				.endpoपूर्णांक = 0x06,
		.u = अणु
			.bulk = अणु
				.buffersize = 4096,
			पूर्ण
		पूर्ण
	पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.घातer_ctrl      = dtt200u_घातer_ctrl,

	.rc.core = अणु
		.rc_पूर्णांकerval     = 300,
		.rc_codes        = RC_MAP_DTT200U,
		.rc_query        = dtt200u_rc_query,
		.allowed_protos  = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु .name = "WideView WT-220U PenType Receiver (Typhoon/Freecom)",
		  .cold_ids = अणु &dtt200u_usb_table[6], शून्य पूर्ण,
		  .warm_ids = अणु &dtt200u_usb_table[7], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties wt220u_zl0353_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-wt220u-zl0353-01.fw",

	.size_of_priv     = माप(काष्ठा dtt200u_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_NEED_PID_FILTERING,
			.pid_filter_count = 15,

			.streaming_ctrl  = dtt200u_streaming_ctrl,
			.pid_filter      = dtt200u_pid_filter,
			.frontend_attach = dtt200u_frontend_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 7,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.घातer_ctrl      = dtt200u_घातer_ctrl,

	.rc.core = अणु
		.rc_पूर्णांकerval     = 300,
		.rc_codes        = RC_MAP_DTT200U,
		.rc_query        = dtt200u_rc_query,
		.allowed_protos  = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु .name = "WideView WT-220U PenType Receiver (based on ZL353)",
		  .cold_ids = अणु &dtt200u_usb_table[4], शून्य पूर्ण,
		  .warm_ids = अणु &dtt200u_usb_table[5], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties wt220u_miglia_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-wt220u-miglia-01.fw",

	.size_of_priv     = माप(काष्ठा dtt200u_state),

	.num_adapters = 1,
	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु .name = "WideView WT-220U PenType Receiver (Miglia)",
		  .cold_ids = अणु &dtt200u_usb_table[9], शून्य पूर्ण,
		  /* This device turns पूर्णांकo WT220U_ZL0353_WARM when fw
		     has been uploaded */
		  .warm_ids = अणु शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver dtt200u_usb_driver = अणु
	.name		= "dvb_usb_dtt200u",
	.probe		= dtt200u_usb_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= dtt200u_usb_table,
पूर्ण;

module_usb_driver(dtt200u_usb_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for the WideView/Yakumo/Hama/Typhoon/Club3D/Miglia DVB-T USB2.0 devices");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
