<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम AzureWave 6007 DVB-C/T USB2.0 and clones
 *
 * Copyright (c) Henry Wang <Henry.wang@AzureWave.com>
 *
 * This driver was made खुलाly available by Terratec, at:
 *	http://linux.terratec.de/files/TERRATEC_H7/20110323_TERRATEC_H7_Linux.tar.gz
 * The original driver's license is GPL, as declared with MODULE_LICENSE()
 *
 * Copyright (c) 2010-2012 Mauro Carvalho Chehab
 *	Driver modअगरied by in order to work with upstream drxk driver, and
 *	tons of bugs got fixed, and converted to use dvb-usb-v2.
 */

#समावेश "drxk.h"
#समावेश "mt2063.h"
#समावेश <media/dvb_ca_en50221.h>
#समावेश "dvb_usb.h"
#समावेश "cypress_firmware.h"

#घोषणा AZ6007_FIRMWARE "dvb-usb-terratec-h7-az6007.fw"

अटल पूर्णांक az6007_xfer_debug;
module_param_named(xfer_debug, az6007_xfer_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(xfer_debug, "Enable xfer debug");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* Known requests (Cypress FX2 firmware + az6007 "private" ones*/

#घोषणा FX2_OED			0xb5
#घोषणा AZ6007_READ_DATA	0xb7
#घोषणा AZ6007_I2C_RD		0xb9
#घोषणा AZ6007_POWER		0xbc
#घोषणा AZ6007_I2C_WR		0xbd
#घोषणा FX2_SCON1		0xc0
#घोषणा AZ6007_TS_THROUGH	0xc7
#घोषणा AZ6007_READ_IR		0xb4

काष्ठा az6007_device_state अणु
	काष्ठा mutex		mutex;
	काष्ठा mutex		ca_mutex;
	काष्ठा dvb_ca_en50221	ca;
	अचिन्हित		warm:1;
	पूर्णांक			(*gate_ctrl) (काष्ठा dvb_frontend *, पूर्णांक);
	अचिन्हित अक्षर		data[4096];
पूर्ण;

अटल काष्ठा drxk_config terratec_h7_drxk = अणु
	.adr = 0x29,
	.parallel_ts = true,
	.dynamic_clk = true,
	.single_master = true,
	.enable_merr_cfg = true,
	.no_i2c_bridge = false,
	.chunk_size = 64,
	.mpeg_out_clk_strength = 0x02,
	.qam_demod_parameter_count = 2,
	.microcode_name = "dvb-usb-terratec-h7-drxk.fw",
पूर्ण;

अटल काष्ठा drxk_config cablestar_hdci_drxk = अणु
	.adr = 0x29,
	.parallel_ts = true,
	.dynamic_clk = true,
	.single_master = true,
	.enable_merr_cfg = true,
	.no_i2c_bridge = false,
	.chunk_size = 64,
	.mpeg_out_clk_strength = 0x02,
	.qam_demod_parameter_count = 2,
	.microcode_name = "dvb-usb-technisat-cablestar-hdci-drxk.fw",
पूर्ण;

अटल पूर्णांक drxk_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा az6007_device_state *st = fe_to_priv(fe);
	काष्ठा dvb_usb_adapter *adap = fe->sec_priv;
	पूर्णांक status = 0;

	pr_debug("%s: %s\n", __func__, enable ? "enable" : "disable");

	अगर (!adap || !st)
		वापस -EINVAL;

	अगर (enable)
		status = st->gate_ctrl(fe, 1);
	अन्यथा
		status = st->gate_ctrl(fe, 0);

	वापस status;
पूर्ण

अटल काष्ठा mt2063_config az6007_mt2063_config = अणु
	.tuner_address = 0x60,
	.refघड़ी = 36125000,
पूर्ण;

अटल पूर्णांक __az6007_पढ़ो(काष्ठा usb_device *udev, u8 req, u16 value,
			    u16 index, u8 *b, पूर्णांक blen)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(udev,
			      usb_rcvctrlpipe(udev, 0),
			      req,
			      USB_TYPE_VENDOR | USB_सूची_IN,
			      value, index, b, blen, 5000);
	अगर (ret < 0) अणु
		pr_warn("usb read operation failed. (%d)\n", ret);
		वापस -EIO;
	पूर्ण

	अगर (az6007_xfer_debug) अणु
		prपूर्णांकk(KERN_DEBUG "az6007: IN  req: %02x, value: %04x, index: %04x\n",
		       req, value, index);
		prपूर्णांक_hex_dump_bytes("az6007: payload: ",
				     DUMP_PREFIX_NONE, b, blen);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक az6007_पढ़ो(काष्ठा dvb_usb_device *d, u8 req, u16 value,
			    u16 index, u8 *b, पूर्णांक blen)
अणु
	काष्ठा az6007_device_state *st = d->priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&st->mutex) < 0)
		वापस -EAGAIN;

	ret = __az6007_पढ़ो(d->udev, req, value, index, b, blen);

	mutex_unlock(&st->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __az6007_ग_लिखो(काष्ठा usb_device *udev, u8 req, u16 value,
			     u16 index, u8 *b, पूर्णांक blen)
अणु
	पूर्णांक ret;

	अगर (az6007_xfer_debug) अणु
		prपूर्णांकk(KERN_DEBUG "az6007: OUT req: %02x, value: %04x, index: %04x\n",
		       req, value, index);
		prपूर्णांक_hex_dump_bytes("az6007: payload: ",
				     DUMP_PREFIX_NONE, b, blen);
	पूर्ण

	अगर (blen > 64) अणु
		pr_err("az6007: tried to write %d bytes, but I2C max size is 64 bytes\n",
		       blen);
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = usb_control_msg(udev,
			      usb_sndctrlpipe(udev, 0),
			      req,
			      USB_TYPE_VENDOR | USB_सूची_OUT,
			      value, index, b, blen, 5000);
	अगर (ret != blen) अणु
		pr_err("usb write operation failed. (%d)\n", ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक az6007_ग_लिखो(काष्ठा dvb_usb_device *d, u8 req, u16 value,
			    u16 index, u8 *b, पूर्णांक blen)
अणु
	काष्ठा az6007_device_state *st = d->priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&st->mutex) < 0)
		वापस -EAGAIN;

	ret = __az6007_ग_लिखो(d->udev, req, value, index, b, blen);

	mutex_unlock(&st->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक az6007_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);

	pr_debug("%s: %s\n", __func__, onoff ? "enable" : "disable");

	वापस az6007_ग_लिखो(d, 0xbc, onoff, 0, शून्य, 0);
पूर्ण

#अगर IS_ENABLED(CONFIG_RC_CORE)
/* remote control stuff (करोes not work with my box) */
अटल पूर्णांक az6007_rc_query(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा az6007_device_state *st = d_to_priv(d);
	अचिन्हित code;
	क्रमागत rc_proto proto;

	az6007_पढ़ो(d, AZ6007_READ_IR, 0, 0, st->data, 10);

	अगर (st->data[1] == 0x44)
		वापस 0;

	अगर ((st->data[3] ^ st->data[4]) == 0xff) अणु
		अगर ((st->data[1] ^ st->data[2]) == 0xff) अणु
			code = RC_SCANCODE_NEC(st->data[1], st->data[3]);
			proto = RC_PROTO_NEC;
		पूर्ण अन्यथा अणु
			code = RC_SCANCODE_NECX(st->data[1] << 8 | st->data[2],
						st->data[3]);
			proto = RC_PROTO_NECX;
		पूर्ण
	पूर्ण अन्यथा अणु
		code = RC_SCANCODE_NEC32(st->data[1] << 24 |
					 st->data[2] << 16 |
					 st->data[3] << 8  |
					 st->data[4]);
		proto = RC_PROTO_NEC32;
	पूर्ण

	rc_keyकरोwn(d->rc_dev, proto, code, st->data[5]);

	वापस 0;
पूर्ण

अटल पूर्णांक az6007_get_rc_config(काष्ठा dvb_usb_device *d, काष्ठा dvb_usb_rc *rc)
अणु
	pr_debug("Getting az6007 Remote Control properties\n");

	rc->allowed_protos = RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX |
						RC_PROTO_BIT_NEC32;
	rc->query          = az6007_rc_query;
	rc->पूर्णांकerval       = 400;

	वापस 0;
पूर्ण
#अन्यथा
	#घोषणा az6007_get_rc_config शून्य
#पूर्ण_अगर

अटल पूर्णांक az6007_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
					पूर्णांक slot,
					पूर्णांक address)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6007_device_state *state = d_to_priv(d);

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	अगर (slot != 0)
		वापस -EINVAL;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	mutex_lock(&state->ca_mutex);

	req = 0xC1;
	value = address;
	index = 0;
	blen = 1;

	ret = az6007_पढ़ो(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		pr_warn("usb in operation failed. (%d)\n", ret);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = b[0];
	पूर्ण

	mutex_unlock(&state->ca_mutex);
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक az6007_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
					 पूर्णांक slot,
					 पूर्णांक address,
					 u8 value)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6007_device_state *state = d_to_priv(d);

	पूर्णांक ret;
	u8 req;
	u16 value1;
	u16 index;
	पूर्णांक blen;

	pr_debug("%s(), slot %d\n", __func__, slot);
	अगर (slot != 0)
		वापस -EINVAL;

	mutex_lock(&state->ca_mutex);
	req = 0xC2;
	value1 = address;
	index = value;
	blen = 0;

	ret = az6007_ग_लिखो(d, req, value1, index, शून्य, blen);
	अगर (ret != 0)
		pr_warn("usb out operation failed. (%d)\n", ret);

	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक az6007_ci_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca,
				      पूर्णांक slot,
				      u8 address)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6007_device_state *state = d_to_priv(d);

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	अगर (slot != 0)
		वापस -EINVAL;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	mutex_lock(&state->ca_mutex);

	req = 0xC3;
	value = address;
	index = 0;
	blen = 2;

	ret = az6007_पढ़ो(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		pr_warn("usb in operation failed. (%d)\n", ret);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (b[0] == 0)
			pr_warn("Read CI IO error\n");

		ret = b[1];
		pr_debug("read cam data = %x from 0x%x\n", b[1], value);
	पूर्ण

	mutex_unlock(&state->ca_mutex);
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक az6007_ci_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca,
				       पूर्णांक slot,
				       u8 address,
				       u8 value)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6007_device_state *state = d_to_priv(d);

	पूर्णांक ret;
	u8 req;
	u16 value1;
	u16 index;
	पूर्णांक blen;

	अगर (slot != 0)
		वापस -EINVAL;

	mutex_lock(&state->ca_mutex);
	req = 0xC4;
	value1 = address;
	index = value;
	blen = 0;

	ret = az6007_ग_लिखो(d, req, value1, index, शून्य, blen);
	अगर (ret != 0) अणु
		pr_warn("usb out operation failed. (%d)\n", ret);
		जाओ failed;
	पूर्ण

failed:
	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक CI_CamReady(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	req = 0xC8;
	value = 0;
	index = 0;
	blen = 1;

	ret = az6007_पढ़ो(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		pr_warn("usb in operation failed. (%d)\n", ret);
		ret = -EIO;
	पूर्ण अन्यथाअणु
		ret = b[0];
	पूर्ण
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक az6007_ci_slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6007_device_state *state = d_to_priv(d);

	पूर्णांक ret, i;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	mutex_lock(&state->ca_mutex);

	req = 0xC6;
	value = 1;
	index = 0;
	blen = 0;

	ret = az6007_ग_लिखो(d, req, value, index, शून्य, blen);
	अगर (ret != 0) अणु
		pr_warn("usb out operation failed. (%d)\n", ret);
		जाओ failed;
	पूर्ण

	msleep(500);
	req = 0xC6;
	value = 0;
	index = 0;
	blen = 0;

	ret = az6007_ग_लिखो(d, req, value, index, शून्य, blen);
	अगर (ret != 0) अणु
		pr_warn("usb out operation failed. (%d)\n", ret);
		जाओ failed;
	पूर्ण

	क्रम (i = 0; i < 15; i++) अणु
		msleep(100);

		अगर (CI_CamReady(ca, slot)) अणु
			pr_debug("CAM Ready\n");
			अवरोध;
		पूर्ण
	पूर्ण
	msleep(5000);

failed:
	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक az6007_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक az6007_ci_slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6007_device_state *state = d_to_priv(d);

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	pr_debug("%s()\n", __func__);
	mutex_lock(&state->ca_mutex);
	req = 0xC7;
	value = 1;
	index = 0;
	blen = 0;

	ret = az6007_ग_लिखो(d, req, value, index, शून्य, blen);
	अगर (ret != 0) अणु
		pr_warn("usb out operation failed. (%d)\n", ret);
		जाओ failed;
	पूर्ण

failed:
	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक az6007_ci_poll_slot_status(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6007_device_state *state = d_to_priv(d);
	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;
	mutex_lock(&state->ca_mutex);

	req = 0xC5;
	value = 0;
	index = 0;
	blen = 1;

	ret = az6007_पढ़ो(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		pr_warn("usb in operation failed. (%d)\n", ret);
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;

	अगर (!ret && b[0] == 1) अणु
		ret = DVB_CA_EN50221_POLL_CAM_PRESENT |
		      DVB_CA_EN50221_POLL_CAM_READY;
	पूर्ण

	mutex_unlock(&state->ca_mutex);
	kमुक्त(b);
	वापस ret;
पूर्ण


अटल व्योम az6007_ci_uninit(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा az6007_device_state *state;

	pr_debug("%s()\n", __func__);

	अगर (शून्य == d)
		वापस;

	state = d_to_priv(d);
	अगर (शून्य == state)
		वापस;

	अगर (शून्य == state->ca.data)
		वापस;

	dvb_ca_en50221_release(&state->ca);

	स_रखो(&state->ca, 0, माप(state->ca));
पूर्ण


अटल पूर्णांक az6007_ci_init(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा az6007_device_state *state = adap_to_priv(adap);
	पूर्णांक ret;

	pr_debug("%s()\n", __func__);

	mutex_init(&state->ca_mutex);
	state->ca.owner			= THIS_MODULE;
	state->ca.पढ़ो_attribute_mem	= az6007_ci_पढ़ो_attribute_mem;
	state->ca.ग_लिखो_attribute_mem	= az6007_ci_ग_लिखो_attribute_mem;
	state->ca.पढ़ो_cam_control	= az6007_ci_पढ़ो_cam_control;
	state->ca.ग_लिखो_cam_control	= az6007_ci_ग_लिखो_cam_control;
	state->ca.slot_reset		= az6007_ci_slot_reset;
	state->ca.slot_shutकरोwn		= az6007_ci_slot_shutकरोwn;
	state->ca.slot_ts_enable	= az6007_ci_slot_ts_enable;
	state->ca.poll_slot_status	= az6007_ci_poll_slot_status;
	state->ca.data			= d;

	ret = dvb_ca_en50221_init(&adap->dvb_adap,
				  &state->ca,
				  0, /* flags */
				  1);/* n_slots */
	अगर (ret != 0) अणु
		pr_err("Cannot initialize CI: Error %d.\n", ret);
		स_रखो(&state->ca, 0, माप(state->ca));
		वापस ret;
	पूर्ण

	pr_debug("CI initialized.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक az6007_पढ़ो_mac_addr(काष्ठा dvb_usb_adapter *adap, u8 mac[6])
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा az6007_device_state *st = adap_to_priv(adap);
	पूर्णांक ret;

	ret = az6007_पढ़ो(d, AZ6007_READ_DATA, 6, 0, st->data, 6);
	स_नकल(mac, st->data, 6);

	अगर (ret > 0)
		pr_debug("%s: mac is %pM\n", __func__, mac);

	वापस ret;
पूर्ण

अटल पूर्णांक az6007_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा az6007_device_state *st = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);

	pr_debug("attaching demod drxk\n");

	adap->fe[0] = dvb_attach(drxk_attach, &terratec_h7_drxk,
				 &d->i2c_adap);
	अगर (!adap->fe[0])
		वापस -EINVAL;

	adap->fe[0]->sec_priv = adap;
	st->gate_ctrl = adap->fe[0]->ops.i2c_gate_ctrl;
	adap->fe[0]->ops.i2c_gate_ctrl = drxk_gate_ctrl;

	az6007_ci_init(adap);

	वापस 0;
पूर्ण

अटल पूर्णांक az6007_cablestar_hdci_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा az6007_device_state *st = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);

	pr_debug("attaching demod drxk\n");

	adap->fe[0] = dvb_attach(drxk_attach, &cablestar_hdci_drxk,
				 &d->i2c_adap);
	अगर (!adap->fe[0])
		वापस -EINVAL;

	adap->fe[0]->sec_priv = adap;
	st->gate_ctrl = adap->fe[0]->ops.i2c_gate_ctrl;
	adap->fe[0]->ops.i2c_gate_ctrl = drxk_gate_ctrl;

	az6007_ci_init(adap);

	वापस 0;
पूर्ण

अटल पूर्णांक az6007_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);

	pr_debug("attaching tuner mt2063\n");

	/* Attach mt2063 to DVB-C frontend */
	अगर (adap->fe[0]->ops.i2c_gate_ctrl)
		adap->fe[0]->ops.i2c_gate_ctrl(adap->fe[0], 1);
	अगर (!dvb_attach(mt2063_attach, adap->fe[0],
			&az6007_mt2063_config,
			&d->i2c_adap))
		वापस -EINVAL;

	अगर (adap->fe[0]->ops.i2c_gate_ctrl)
		adap->fe[0]->ops.i2c_gate_ctrl(adap->fe[0], 0);

	वापस 0;
पूर्ण

अटल पूर्णांक az6007_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	काष्ठा az6007_device_state *state = d_to_priv(d);
	पूर्णांक ret;

	pr_debug("%s()\n", __func__);

	अगर (!state->warm) अणु
		mutex_init(&state->mutex);

		ret = az6007_ग_लिखो(d, AZ6007_POWER, 0, 2, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
		msleep(60);
		ret = az6007_ग_लिखो(d, AZ6007_POWER, 1, 4, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
		msleep(100);
		ret = az6007_ग_लिखो(d, AZ6007_POWER, 1, 3, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
		msleep(20);
		ret = az6007_ग_लिखो(d, AZ6007_POWER, 1, 4, शून्य, 0);
		अगर (ret < 0)
			वापस ret;

		msleep(400);
		ret = az6007_ग_लिखो(d, FX2_SCON1, 0, 3, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
		msleep(150);
		ret = az6007_ग_लिखो(d, FX2_SCON1, 1, 3, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
		msleep(430);
		ret = az6007_ग_लिखो(d, AZ6007_POWER, 0, 0, शून्य, 0);
		अगर (ret < 0)
			वापस ret;

		state->warm = true;

		वापस 0;
	पूर्ण

	अगर (!onoff)
		वापस 0;

	az6007_ग_लिखो(d, AZ6007_POWER, 0, 0, शून्य, 0);
	az6007_ग_लिखो(d, AZ6007_TS_THROUGH, 0, 0, शून्य, 0);

	वापस 0;
पूर्ण

/* I2C */
अटल पूर्णांक az6007_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[],
			   पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा az6007_device_state *st = d_to_priv(d);
	पूर्णांक i, j, len;
	पूर्णांक ret = 0;
	u16 index;
	u16 value;
	पूर्णांक length;
	u8 req, addr;

	अगर (mutex_lock_पूर्णांकerruptible(&st->mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		addr = msgs[i].addr << 1;
		अगर (((i + 1) < num)
		    && (msgs[i].len == 1)
		    && ((msgs[i].flags & I2C_M_RD) != I2C_M_RD)
		    && (msgs[i + 1].flags & I2C_M_RD)
		    && (msgs[i].addr == msgs[i + 1].addr)) अणु
			/*
			 * A ग_लिखो + पढ़ो xfer क्रम the same address, where
			 * the first xfer has just 1 byte length.
			 * Need to join both पूर्णांकo one operation
			 */
			अगर (az6007_xfer_debug)
				prपूर्णांकk(KERN_DEBUG "az6007: I2C W/R addr=0x%x len=%d/%d\n",
				       addr, msgs[i].len, msgs[i + 1].len);
			req = AZ6007_I2C_RD;
			index = msgs[i].buf[0];
			value = addr | (1 << 8);
			length = 6 + msgs[i + 1].len;
			len = msgs[i + 1].len;
			ret = __az6007_पढ़ो(d->udev, req, value, index,
					    st->data, length);
			अगर (ret >= len) अणु
				क्रम (j = 0; j < len; j++)
					msgs[i + 1].buf[j] = st->data[j + 5];
			पूर्ण अन्यथा
				ret = -EIO;
			i++;
		पूर्ण अन्यथा अगर (!(msgs[i].flags & I2C_M_RD)) अणु
			/* ग_लिखो bytes */
			अगर (az6007_xfer_debug)
				prपूर्णांकk(KERN_DEBUG "az6007: I2C W addr=0x%x len=%d\n",
				       addr, msgs[i].len);
			req = AZ6007_I2C_WR;
			index = msgs[i].buf[0];
			value = addr | (1 << 8);
			length = msgs[i].len - 1;
			len = msgs[i].len - 1;
			क्रम (j = 0; j < len; j++)
				st->data[j] = msgs[i].buf[j + 1];
			ret =  __az6007_ग_लिखो(d->udev, req, value, index,
					      st->data, length);
		पूर्ण अन्यथा अणु
			/* पढ़ो bytes */
			अगर (az6007_xfer_debug)
				prपूर्णांकk(KERN_DEBUG "az6007: I2C R addr=0x%x len=%d\n",
				       addr, msgs[i].len);
			req = AZ6007_I2C_RD;
			index = msgs[i].buf[0];
			value = addr;
			length = msgs[i].len + 6;
			len = msgs[i].len;
			ret = __az6007_पढ़ो(d->udev, req, value, index,
					    st->data, length);
			क्रम (j = 0; j < len; j++)
				msgs[i].buf[j] = st->data[j + 5];
		पूर्ण
		अगर (ret < 0)
			जाओ err;
	पूर्ण
err:
	mutex_unlock(&st->mutex);

	अगर (ret < 0) अणु
		pr_info("%s ERROR: %i\n", __func__, ret);
		वापस ret;
	पूर्ण
	वापस num;
पूर्ण

अटल u32 az6007_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm az6007_i2c_algo = अणु
	.master_xfer = az6007_i2c_xfer,
	.functionality = az6007_i2c_func,
पूर्ण;

अटल पूर्णांक az6007_identअगरy_state(काष्ठा dvb_usb_device *d, स्थिर अक्षर **name)
अणु
	पूर्णांक ret;
	u8 *mac;

	pr_debug("Identifying az6007 state\n");

	mac = kदो_स्मृति(6, GFP_ATOMIC);
	अगर (!mac)
		वापस -ENOMEM;

	/* Try to पढ़ो the mac address */
	ret = __az6007_पढ़ो(d->udev, AZ6007_READ_DATA, 6, 0, mac, 6);
	अगर (ret == 6)
		ret = WARM;
	अन्यथा
		ret = COLD;

	kमुक्त(mac);

	अगर (ret == COLD) अणु
		__az6007_ग_लिखो(d->udev, 0x09, 1, 0, शून्य, 0);
		__az6007_ग_लिखो(d->udev, 0x00, 0, 0, शून्य, 0);
		__az6007_ग_लिखो(d->udev, 0x00, 0, 0, शून्य, 0);
	पूर्ण

	pr_debug("Device is on %s state\n",
		 ret == WARM ? "warm" : "cold");
	वापस ret;
पूर्ण

अटल व्योम az6007_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	az6007_ci_uninit(d);
	dvb_usbv2_disconnect(पूर्णांकf);
पूर्ण

अटल पूर्णांक az6007_करोwnload_firmware(काष्ठा dvb_usb_device *d,
	स्थिर काष्ठा firmware *fw)
अणु
	pr_debug("Loading az6007 firmware\n");

	वापस cypress_load_firmware(d->udev, fw, CYPRESS_FX2);
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties az6007_props = अणु
	.driver_name         = KBUILD_MODNAME,
	.owner               = THIS_MODULE,
	.firmware            = AZ6007_FIRMWARE,

	.adapter_nr          = adapter_nr,
	.size_of_priv        = माप(काष्ठा az6007_device_state),
	.i2c_algo            = &az6007_i2c_algo,
	.tuner_attach        = az6007_tuner_attach,
	.frontend_attach     = az6007_frontend_attach,
	.streaming_ctrl      = az6007_streaming_ctrl,
	.get_rc_config       = az6007_get_rc_config,
	.पढ़ो_mac_address    = az6007_पढ़ो_mac_addr,
	.करोwnload_firmware   = az6007_करोwnload_firmware,
	.identअगरy_state	     = az6007_identअगरy_state,
	.घातer_ctrl          = az6007_घातer_ctrl,
	.num_adapters        = 1,
	.adapter             = अणु
		अणु .stream = DVB_USB_STREAM_BULK(0x02, 10, 4096), पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties az6007_cablestar_hdci_props = अणु
	.driver_name         = KBUILD_MODNAME,
	.owner               = THIS_MODULE,
	.firmware            = AZ6007_FIRMWARE,

	.adapter_nr          = adapter_nr,
	.size_of_priv        = माप(काष्ठा az6007_device_state),
	.i2c_algo            = &az6007_i2c_algo,
	.tuner_attach        = az6007_tuner_attach,
	.frontend_attach     = az6007_cablestar_hdci_frontend_attach,
	.streaming_ctrl      = az6007_streaming_ctrl,
/* ditch get_rc_config as it can't work (TS35 remote, I believe it's rc5) */
	.get_rc_config       = शून्य,
	.पढ़ो_mac_address    = az6007_पढ़ो_mac_addr,
	.करोwnload_firmware   = az6007_करोwnload_firmware,
	.identअगरy_state	     = az6007_identअगरy_state,
	.घातer_ctrl          = az6007_घातer_ctrl,
	.num_adapters        = 1,
	.adapter             = अणु
		अणु .stream = DVB_USB_STREAM_BULK(0x02, 10, 4096), पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id az6007_usb_table[] = अणु
	अणुDVB_USB_DEVICE(USB_VID_AZUREWAVE, USB_PID_AZUREWAVE_6007,
		&az6007_props, "Azurewave 6007", RC_MAP_EMPTY)पूर्ण,
	अणुDVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_H7,
		&az6007_props, "Terratec H7", RC_MAP_NEC_TERRATEC_CINERGY_XS)पूर्ण,
	अणुDVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_H7_2,
		&az6007_props, "Terratec H7", RC_MAP_NEC_TERRATEC_CINERGY_XS)पूर्ण,
	अणुDVB_USB_DEVICE(USB_VID_TECHNISAT, USB_PID_TECHNISAT_USB2_CABLESTAR_HDCI,
		&az6007_cablestar_hdci_props, "Technisat CableStar Combo HD CI", RC_MAP_EMPTY)पूर्ण,
	अणु0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, az6007_usb_table);

अटल पूर्णांक az6007_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t msg)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);

	az6007_ci_uninit(d);
	वापस dvb_usbv2_suspend(पूर्णांकf, msg);
पूर्ण

अटल पूर्णांक az6007_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा dvb_usb_adapter *adap = &d->adapter[0];

	az6007_ci_init(adap);
	वापस dvb_usbv2_resume(पूर्णांकf);
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver az6007_usb_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= az6007_usb_table,
	.probe		= dvb_usbv2_probe,
	.disconnect	= az6007_usb_disconnect,
	.no_dynamic_id	= 1,
	.soft_unbind	= 1,
	/*
	 * FIXME: need to implement reset_resume, likely with
	 * dvb-usb-v2 core support
	 */
	.suspend	= az6007_suspend,
	.resume		= az6007_resume,
पूर्ण;

module_usb_driver(az6007_usb_driver);

MODULE_AUTHOR("Henry Wang <Henry.wang@AzureWave.com>");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_DESCRIPTION("Driver for AzureWave 6007 DVB-C/T USB2.0 and clones");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(AZ6007_FIRMWARE);
