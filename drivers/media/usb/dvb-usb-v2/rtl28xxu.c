<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Realtek RTL28xxU DVB USB driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2012 Thomas Mair <thomas.mair86@googlemail.com>
 */

#समावेश "rtl28xxu.h"

अटल पूर्णांक rtl28xxu_disable_rc;
module_param_named(disable_rc, rtl28xxu_disable_rc, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_rc, "disable RTL2832U remote controller");
DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक rtl28xxu_ctrl_msg(काष्ठा dvb_usb_device *d, काष्ठा rtl28xxu_req *req)
अणु
	काष्ठा rtl28xxu_dev *dev = d->priv;
	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe;
	u8 requesttype;

	mutex_lock(&d->usb_mutex);

	अगर (req->size > माप(dev->buf)) अणु
		dev_err(&d->पूर्णांकf->dev, "too large message %u\n", req->size);
		ret = -EINVAL;
		जाओ err_mutex_unlock;
	पूर्ण

	अगर (req->index & CMD_WR_FLAG) अणु
		/* ग_लिखो */
		स_नकल(dev->buf, req->data, req->size);
		requesttype = (USB_TYPE_VENDOR | USB_सूची_OUT);
		pipe = usb_sndctrlpipe(d->udev, 0);
	पूर्ण अन्यथा अणु
		/* पढ़ो */
		requesttype = (USB_TYPE_VENDOR | USB_सूची_IN);
		pipe = usb_rcvctrlpipe(d->udev, 0);
	पूर्ण

	ret = usb_control_msg(d->udev, pipe, 0, requesttype, req->value,
			req->index, dev->buf, req->size, 1000);
	dvb_usb_dbg_usb_control_msg(d->udev, 0, requesttype, req->value,
			req->index, dev->buf, req->size);
	अगर (ret < 0)
		जाओ err_mutex_unlock;

	/* पढ़ो request, copy वापसed data to वापस buf */
	अगर (requesttype == (USB_TYPE_VENDOR | USB_सूची_IN))
		स_नकल(req->data, dev->buf, req->size);

	mutex_unlock(&d->usb_mutex);

	वापस 0;
err_mutex_unlock:
	mutex_unlock(&d->usb_mutex);
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl28xxu_wr_regs(काष्ठा dvb_usb_device *d, u16 reg, u8 *val, पूर्णांक len)
अणु
	काष्ठा rtl28xxu_req req;

	अगर (reg < 0x3000)
		req.index = CMD_USB_WR;
	अन्यथा अगर (reg < 0x4000)
		req.index = CMD_SYS_WR;
	अन्यथा
		req.index = CMD_IR_WR;

	req.value = reg;
	req.size = len;
	req.data = val;

	वापस rtl28xxu_ctrl_msg(d, &req);
पूर्ण

अटल पूर्णांक rtl28xxu_rd_regs(काष्ठा dvb_usb_device *d, u16 reg, u8 *val, पूर्णांक len)
अणु
	काष्ठा rtl28xxu_req req;

	अगर (reg < 0x3000)
		req.index = CMD_USB_RD;
	अन्यथा अगर (reg < 0x4000)
		req.index = CMD_SYS_RD;
	अन्यथा
		req.index = CMD_IR_RD;

	req.value = reg;
	req.size = len;
	req.data = val;

	वापस rtl28xxu_ctrl_msg(d, &req);
पूर्ण

अटल पूर्णांक rtl28xxu_wr_reg(काष्ठा dvb_usb_device *d, u16 reg, u8 val)
अणु
	वापस rtl28xxu_wr_regs(d, reg, &val, 1);
पूर्ण

अटल पूर्णांक rtl28xxu_rd_reg(काष्ठा dvb_usb_device *d, u16 reg, u8 *val)
अणु
	वापस rtl28xxu_rd_regs(d, reg, val, 1);
पूर्ण

अटल पूर्णांक rtl28xxu_wr_reg_mask(काष्ठा dvb_usb_device *d, u16 reg, u8 val,
		u8 mask)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	/* no need क्रम पढ़ो अगर whole reg is written */
	अगर (mask != 0xff) अणु
		ret = rtl28xxu_rd_reg(d, reg, &पंचांगp);
		अगर (ret)
			वापस ret;

		val &= mask;
		पंचांगp &= ~mask;
		val |= पंचांगp;
	पूर्ण

	वापस rtl28xxu_wr_reg(d, reg, val);
पूर्ण

/* I2C */
अटल पूर्णांक rtl28xxu_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
	पूर्णांक num)
अणु
	पूर्णांक ret;
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा rtl28xxu_dev *dev = d->priv;
	काष्ठा rtl28xxu_req req;

	/*
	 * It is not known which are real I2C bus xfer limits, but testing
	 * with RTL2831U + MT2060 gives max RD 24 and max WR 22 bytes.
	 * TODO: find out RTL2832U lens
	 */

	/*
	 * I2C adapter logic looks rather complicated due to fact it handles
	 * three dअगरferent access methods. Those methods are;
	 * 1) पूर्णांकegrated demod access
	 * 2) old I2C access
	 * 3) new I2C access
	 *
	 * Used method is selected in order 1, 2, 3. Method 3 can handle all
	 * requests but there is two reasons why not use it always;
	 * 1) It is most expensive, usually two USB messages are needed
	 * 2) At least RTL2831U करोes not support it
	 *
	 * Method 3 is needed in हाल of I2C ग_लिखो+पढ़ो (typical रेजिस्टर पढ़ो)
	 * where ग_लिखो is more than one byte.
	 */

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	अगर (num == 2 && !(msg[0].flags & I2C_M_RD) &&
		(msg[1].flags & I2C_M_RD)) अणु
		अगर (msg[0].len > 24 || msg[1].len > 24) अणु
			/* TODO: check msg[0].len max */
			ret = -EOPNOTSUPP;
			जाओ err_mutex_unlock;
		पूर्ण अन्यथा अगर (msg[0].addr == 0x10) अणु
			/* method 1 - पूर्णांकegrated demod */
			अगर (msg[0].buf[0] == 0x00) अणु
				/* वापस demod page from driver cache */
				msg[1].buf[0] = dev->page;
				ret = 0;
			पूर्ण अन्यथा अणु
				req.value = (msg[0].buf[0] << 8) | (msg[0].addr << 1);
				req.index = CMD_DEMOD_RD | dev->page;
				req.size = msg[1].len;
				req.data = &msg[1].buf[0];
				ret = rtl28xxu_ctrl_msg(d, &req);
			पूर्ण
		पूर्ण अन्यथा अगर (msg[0].len < 2) अणु
			/* method 2 - old I2C */
			req.value = (msg[0].buf[0] << 8) | (msg[0].addr << 1);
			req.index = CMD_I2C_RD;
			req.size = msg[1].len;
			req.data = &msg[1].buf[0];
			ret = rtl28xxu_ctrl_msg(d, &req);
		पूर्ण अन्यथा अणु
			/* method 3 - new I2C */
			req.value = (msg[0].addr << 1);
			req.index = CMD_I2C_DA_WR;
			req.size = msg[0].len;
			req.data = msg[0].buf;
			ret = rtl28xxu_ctrl_msg(d, &req);
			अगर (ret)
				जाओ err_mutex_unlock;

			req.value = (msg[0].addr << 1);
			req.index = CMD_I2C_DA_RD;
			req.size = msg[1].len;
			req.data = msg[1].buf;
			ret = rtl28xxu_ctrl_msg(d, &req);
		पूर्ण
	पूर्ण अन्यथा अगर (num == 1 && !(msg[0].flags & I2C_M_RD)) अणु
		अगर (msg[0].len > 22) अणु
			/* TODO: check msg[0].len max */
			ret = -EOPNOTSUPP;
			जाओ err_mutex_unlock;
		पूर्ण अन्यथा अगर (msg[0].addr == 0x10) अणु
			/* method 1 - पूर्णांकegrated demod */
			अगर (msg[0].buf[0] == 0x00) अणु
				/* save demod page क्रम later demod access */
				dev->page = msg[0].buf[1];
				ret = 0;
			पूर्ण अन्यथा अणु
				req.value = (msg[0].buf[0] << 8) |
					(msg[0].addr << 1);
				req.index = CMD_DEMOD_WR | dev->page;
				req.size = msg[0].len-1;
				req.data = &msg[0].buf[1];
				ret = rtl28xxu_ctrl_msg(d, &req);
			पूर्ण
		पूर्ण अन्यथा अगर ((msg[0].len < 23) && (!dev->new_i2c_ग_लिखो)) अणु
			/* method 2 - old I2C */
			req.value = (msg[0].buf[0] << 8) | (msg[0].addr << 1);
			req.index = CMD_I2C_WR;
			req.size = msg[0].len-1;
			req.data = &msg[0].buf[1];
			ret = rtl28xxu_ctrl_msg(d, &req);
		पूर्ण अन्यथा अणु
			/* method 3 - new I2C */
			req.value = (msg[0].addr << 1);
			req.index = CMD_I2C_DA_WR;
			req.size = msg[0].len;
			req.data = msg[0].buf;
			ret = rtl28xxu_ctrl_msg(d, &req);
		पूर्ण
	पूर्ण अन्यथा अगर (num == 1 && (msg[0].flags & I2C_M_RD)) अणु
		req.value = (msg[0].addr << 1);
		req.index = CMD_I2C_DA_RD;
		req.size = msg[0].len;
		req.data = msg[0].buf;
		ret = rtl28xxu_ctrl_msg(d, &req);
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP;
	पूर्ण

	/* Retry failed I2C messages */
	अगर (ret == -EPIPE)
		ret = -EAGAIN;

err_mutex_unlock:
	mutex_unlock(&d->i2c_mutex);

	वापस ret ? ret : num;
पूर्ण

अटल u32 rtl28xxu_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm rtl28xxu_i2c_algo = अणु
	.master_xfer   = rtl28xxu_i2c_xfer,
	.functionality = rtl28xxu_i2c_func,
पूर्ण;

अटल पूर्णांक rtl2831u_पढ़ो_config(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	पूर्णांक ret;
	u8 buf[1];
	/* खोलो RTL2831U/RTL2830 I2C gate */
	काष्ठा rtl28xxu_req req_gate_खोलो = अणु0x0120, 0x0011, 0x0001, "\x08"पूर्ण;
	/* tuner probes */
	काष्ठा rtl28xxu_req req_mt2060 = अणु0x00c0, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_qt1010 = अणु0x0fc4, CMD_I2C_RD, 1, bufपूर्ण;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	/*
	 * RTL2831U GPIOs
	 * =========================================================
	 * GPIO0 | tuner#0 | 0 off | 1 on  | MXL5005S (?)
	 * GPIO2 | LED     | 0 off | 1 on  |
	 * GPIO4 | tuner#1 | 0 on  | 1 off | MT2060
	 */

	/* GPIO direction */
	ret = rtl28xxu_wr_reg(d, SYS_GPIO_सूची, 0x0a);
	अगर (ret)
		जाओ err;

	/* enable as output GPIO0, GPIO2, GPIO4 */
	ret = rtl28xxu_wr_reg(d, SYS_GPIO_OUT_EN, 0x15);
	अगर (ret)
		जाओ err;

	/*
	 * Probe used tuner. We need to know used tuner beक्रमe demod attach
	 * since there is some demod params needed to set according to tuner.
	 */

	/* demod needs some समय to wake up */
	msleep(20);

	dev->tuner_name = "NONE";

	/* खोलो demod I2C gate */
	ret = rtl28xxu_ctrl_msg(d, &req_gate_खोलो);
	अगर (ret)
		जाओ err;

	/* check QT1010 ID(?) रेजिस्टर; reg=0f val=2c */
	ret = rtl28xxu_ctrl_msg(d, &req_qt1010);
	अगर (ret == 0 && buf[0] == 0x2c) अणु
		dev->tuner = TUNER_RTL2830_QT1010;
		dev->tuner_name = "QT1010";
		जाओ found;
	पूर्ण

	/* खोलो demod I2C gate */
	ret = rtl28xxu_ctrl_msg(d, &req_gate_खोलो);
	अगर (ret)
		जाओ err;

	/* check MT2060 ID रेजिस्टर; reg=00 val=63 */
	ret = rtl28xxu_ctrl_msg(d, &req_mt2060);
	अगर (ret == 0 && buf[0] == 0x63) अणु
		dev->tuner = TUNER_RTL2830_MT2060;
		dev->tuner_name = "MT2060";
		जाओ found;
	पूर्ण

	/* assume MXL5005S */
	dev->tuner = TUNER_RTL2830_MXL5005S;
	dev->tuner_name = "MXL5005S";
	जाओ found;

found:
	dev_dbg(&d->पूर्णांकf->dev, "tuner=%s\n", dev->tuner_name);

	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832u_पढ़ो_config(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	पूर्णांक ret;
	u8 buf[2];
	/* खोलो RTL2832U/RTL2832 I2C gate */
	काष्ठा rtl28xxu_req req_gate_खोलो = अणु0x0120, 0x0011, 0x0001, "\x18"पूर्ण;
	/* बंद RTL2832U/RTL2832 I2C gate */
	काष्ठा rtl28xxu_req req_gate_बंद = अणु0x0120, 0x0011, 0x0001, "\x10"पूर्ण;
	/* tuner probes */
	काष्ठा rtl28xxu_req req_fc0012 = अणु0x00c6, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_fc0013 = अणु0x00c6, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_mt2266 = अणु0x00c0, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_fc2580 = अणु0x01ac, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_mt2063 = अणु0x00c0, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_max3543 = अणु0x00c0, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_tua9001 = अणु0x7ec0, CMD_I2C_RD, 2, bufपूर्ण;
	काष्ठा rtl28xxu_req req_mxl5007t = अणु0xd9c0, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_e4000 = अणु0x02c8, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_tda18272 = अणु0x00c0, CMD_I2C_RD, 2, bufपूर्ण;
	काष्ठा rtl28xxu_req req_r820t = अणु0x0034, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_r828d = अणु0x0074, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_mn88472 = अणु0xff38, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_mn88473 = अणु0xff38, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_cxd2837er = अणु0xfdd8, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_si2157 = अणु0x00c0, CMD_I2C_RD, 1, bufपूर्ण;
	काष्ठा rtl28xxu_req req_si2168 = अणु0x00c8, CMD_I2C_RD, 1, bufपूर्ण;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	/* enable GPIO3 and GPIO6 as output */
	ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_सूची, 0x00, 0x40);
	अगर (ret)
		जाओ err;

	ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_EN, 0x48, 0x48);
	अगर (ret)
		जाओ err;

	/*
	 * Probe used tuner. We need to know used tuner beक्रमe demod attach
	 * since there is some demod params needed to set according to tuner.
	 */

	/* खोलो demod I2C gate */
	ret = rtl28xxu_ctrl_msg(d, &req_gate_खोलो);
	अगर (ret)
		जाओ err;

	dev->tuner_name = "NONE";

	/* check FC0012 ID रेजिस्टर; reg=00 val=a1 */
	ret = rtl28xxu_ctrl_msg(d, &req_fc0012);
	अगर (ret == 0 && buf[0] == 0xa1) अणु
		dev->tuner = TUNER_RTL2832_FC0012;
		dev->tuner_name = "FC0012";
		जाओ tuner_found;
	पूर्ण

	/* check FC0013 ID रेजिस्टर; reg=00 val=a3 */
	ret = rtl28xxu_ctrl_msg(d, &req_fc0013);
	अगर (ret == 0 && buf[0] == 0xa3) अणु
		dev->tuner = TUNER_RTL2832_FC0013;
		dev->tuner_name = "FC0013";
		जाओ tuner_found;
	पूर्ण

	/* check MT2266 ID रेजिस्टर; reg=00 val=85 */
	ret = rtl28xxu_ctrl_msg(d, &req_mt2266);
	अगर (ret == 0 && buf[0] == 0x85) अणु
		dev->tuner = TUNER_RTL2832_MT2266;
		dev->tuner_name = "MT2266";
		जाओ tuner_found;
	पूर्ण

	/* check FC2580 ID रेजिस्टर; reg=01 val=56 */
	ret = rtl28xxu_ctrl_msg(d, &req_fc2580);
	अगर (ret == 0 && buf[0] == 0x56) अणु
		dev->tuner = TUNER_RTL2832_FC2580;
		dev->tuner_name = "FC2580";
		जाओ tuner_found;
	पूर्ण

	/* check MT2063 ID रेजिस्टर; reg=00 val=9e || 9c */
	ret = rtl28xxu_ctrl_msg(d, &req_mt2063);
	अगर (ret == 0 && (buf[0] == 0x9e || buf[0] == 0x9c)) अणु
		dev->tuner = TUNER_RTL2832_MT2063;
		dev->tuner_name = "MT2063";
		जाओ tuner_found;
	पूर्ण

	/* check MAX3543 ID रेजिस्टर; reg=00 val=38 */
	ret = rtl28xxu_ctrl_msg(d, &req_max3543);
	अगर (ret == 0 && buf[0] == 0x38) अणु
		dev->tuner = TUNER_RTL2832_MAX3543;
		dev->tuner_name = "MAX3543";
		जाओ tuner_found;
	पूर्ण

	/* check TUA9001 ID रेजिस्टर; reg=7e val=2328 */
	ret = rtl28xxu_ctrl_msg(d, &req_tua9001);
	अगर (ret == 0 && buf[0] == 0x23 && buf[1] == 0x28) अणु
		dev->tuner = TUNER_RTL2832_TUA9001;
		dev->tuner_name = "TUA9001";
		जाओ tuner_found;
	पूर्ण

	/* check MXL5007R ID रेजिस्टर; reg=d9 val=14 */
	ret = rtl28xxu_ctrl_msg(d, &req_mxl5007t);
	अगर (ret == 0 && buf[0] == 0x14) अणु
		dev->tuner = TUNER_RTL2832_MXL5007T;
		dev->tuner_name = "MXL5007T";
		जाओ tuner_found;
	पूर्ण

	/* check E4000 ID रेजिस्टर; reg=02 val=40 */
	ret = rtl28xxu_ctrl_msg(d, &req_e4000);
	अगर (ret == 0 && buf[0] == 0x40) अणु
		dev->tuner = TUNER_RTL2832_E4000;
		dev->tuner_name = "E4000";
		जाओ tuner_found;
	पूर्ण

	/* check TDA18272 ID रेजिस्टर; reg=00 val=c760  */
	ret = rtl28xxu_ctrl_msg(d, &req_tda18272);
	अगर (ret == 0 && (buf[0] == 0xc7 || buf[1] == 0x60)) अणु
		dev->tuner = TUNER_RTL2832_TDA18272;
		dev->tuner_name = "TDA18272";
		जाओ tuner_found;
	पूर्ण

	/* check R820T ID रेजिस्टर; reg=00 val=69 */
	ret = rtl28xxu_ctrl_msg(d, &req_r820t);
	अगर (ret == 0 && buf[0] == 0x69) अणु
		dev->tuner = TUNER_RTL2832_R820T;
		dev->tuner_name = "R820T";
		जाओ tuner_found;
	पूर्ण

	/* check R828D ID रेजिस्टर; reg=00 val=69 */
	ret = rtl28xxu_ctrl_msg(d, &req_r828d);
	अगर (ret == 0 && buf[0] == 0x69) अणु
		dev->tuner = TUNER_RTL2832_R828D;
		dev->tuner_name = "R828D";
		जाओ tuner_found;
	पूर्ण

	/* GPIO0 and GPIO5 to reset Si2157/Si2168 tuner and demod */
	ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x00, 0x21);
	अगर (ret)
		जाओ err;

	ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_EN, 0x00, 0x21);
	अगर (ret)
		जाओ err;

	msleep(50);

	ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x21, 0x21);
	अगर (ret)
		जाओ err;

	ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_EN, 0x21, 0x21);
	अगर (ret)
		जाओ err;

	msleep(50);

	/* check Si2157 ID रेजिस्टर; reg=c0 val=80 */
	ret = rtl28xxu_ctrl_msg(d, &req_si2157);
	अगर (ret == 0 && ((buf[0] & 0x80) == 0x80)) अणु
		dev->tuner = TUNER_RTL2832_SI2157;
		dev->tuner_name = "SI2157";
		जाओ tuner_found;
	पूर्ण

tuner_found:
	dev_dbg(&d->पूर्णांकf->dev, "tuner=%s\n", dev->tuner_name);

	/* probe slave demod */
	अगर (dev->tuner == TUNER_RTL2832_R828D) अणु
		/* घातer off slave demod on GPIO0 to reset CXD2837ER */
		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x00, 0x01);
		अगर (ret)
			जाओ err;

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_EN, 0x00, 0x01);
		अगर (ret)
			जाओ err;

		msleep(50);

		/* घातer on slave demod on GPIO0 */
		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x01, 0x01);
		अगर (ret)
			जाओ err;

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_सूची, 0x00, 0x01);
		अगर (ret)
			जाओ err;

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_EN, 0x01, 0x01);
		अगर (ret)
			जाओ err;

		/* slave demod needs some समय to wake up */
		msleep(20);

		/* check slave answers */
		ret = rtl28xxu_ctrl_msg(d, &req_mn88472);
		अगर (ret == 0 && buf[0] == 0x02) अणु
			dev_dbg(&d->पूर्णांकf->dev, "MN88472 found\n");
			dev->slave_demod = SLAVE_DEMOD_MN88472;
			जाओ demod_found;
		पूर्ण

		ret = rtl28xxu_ctrl_msg(d, &req_mn88473);
		अगर (ret == 0 && buf[0] == 0x03) अणु
			dev_dbg(&d->पूर्णांकf->dev, "MN88473 found\n");
			dev->slave_demod = SLAVE_DEMOD_MN88473;
			जाओ demod_found;
		पूर्ण

		ret = rtl28xxu_ctrl_msg(d, &req_cxd2837er);
		अगर (ret == 0 && buf[0] == 0xb1) अणु
			dev_dbg(&d->पूर्णांकf->dev, "CXD2837ER found\n");
			dev->slave_demod = SLAVE_DEMOD_CXD2837ER;
			जाओ demod_found;
		पूर्ण
	पूर्ण
	अगर (dev->tuner == TUNER_RTL2832_SI2157) अणु
		/* check Si2168 ID रेजिस्टर; reg=c8 val=80 */
		ret = rtl28xxu_ctrl_msg(d, &req_si2168);
		अगर (ret == 0 && ((buf[0] & 0x80) == 0x80)) अणु
			dev_dbg(&d->पूर्णांकf->dev, "Si2168 found\n");
			dev->slave_demod = SLAVE_DEMOD_SI2168;
			जाओ demod_found;
		पूर्ण
	पूर्ण

demod_found:
	/* बंद demod I2C gate */
	ret = rtl28xxu_ctrl_msg(d, &req_gate_बंद);
	अगर (ret < 0)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl28xxu_पढ़ो_config(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);

	अगर (dev->chip_id == CHIP_ID_RTL2831U)
		वापस rtl2831u_पढ़ो_config(d);
	अन्यथा
		वापस rtl2832u_पढ़ो_config(d);
पूर्ण

अटल पूर्णांक rtl28xxu_identअगरy_state(काष्ठा dvb_usb_device *d, स्थिर अक्षर **name)
अणु
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	पूर्णांक ret;
	काष्ठा rtl28xxu_req req_demod_i2c = अणु0x0020, CMD_I2C_DA_RD, 0, शून्यपूर्ण;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	/*
	 * Detect chip type using I2C command that is not supported
	 * by old RTL2831U.
	 */
	ret = rtl28xxu_ctrl_msg(d, &req_demod_i2c);
	अगर (ret == -EPIPE) अणु
		dev->chip_id = CHIP_ID_RTL2831U;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		dev->chip_id = CHIP_ID_RTL2832U;
	पूर्ण अन्यथा अणु
		dev_err(&d->पूर्णांकf->dev, "chip type detection failed %d\n", ret);
		जाओ err;
	पूर्ण
	dev_dbg(&d->पूर्णांकf->dev, "chip_id=%u\n", dev->chip_id);

	/* Retry failed I2C messages */
	d->i2c_adap.retries = 3;
	d->i2c_adap.समयout = msecs_to_jअगरfies(10);

	वापस WARM;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtl2830_platक्रमm_data rtl2830_mt2060_platक्रमm_data = अणु
	.clk = 28800000,
	.spec_inv = 1,
	.vtop = 0x20,
	.krf = 0x04,
	.agc_targ_val = 0x2d,

पूर्ण;

अटल स्थिर काष्ठा rtl2830_platक्रमm_data rtl2830_qt1010_platक्रमm_data = अणु
	.clk = 28800000,
	.spec_inv = 1,
	.vtop = 0x20,
	.krf = 0x04,
	.agc_targ_val = 0x2d,
पूर्ण;

अटल स्थिर काष्ठा rtl2830_platक्रमm_data rtl2830_mxl5005s_platक्रमm_data = अणु
	.clk = 28800000,
	.spec_inv = 0,
	.vtop = 0x3f,
	.krf = 0x04,
	.agc_targ_val = 0x3e,
पूर्ण;

अटल पूर्णांक rtl2831u_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	काष्ठा rtl2830_platक्रमm_data *pdata = &dev->rtl2830_platक्रमm_data;
	काष्ठा i2c_board_info board_info;
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	चयन (dev->tuner) अणु
	हाल TUNER_RTL2830_QT1010:
		*pdata = rtl2830_qt1010_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2830_MT2060:
		*pdata = rtl2830_mt2060_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2830_MXL5005S:
		*pdata = rtl2830_mxl5005s_platक्रमm_data;
		अवरोध;
	शेष:
		dev_err(&d->पूर्णांकf->dev, "unknown tuner %s\n", dev->tuner_name);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* attach demodulator */
	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "rtl2830", I2C_NAME_SIZE);
	board_info.addr = 0x10;
	board_info.platक्रमm_data = pdata;
	request_module("%s", board_info.type);
	client = i2c_new_client_device(&d->i2c_adap, &board_info);
	अगर (!i2c_client_has_driver(client)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	adap->fe[0] = pdata->get_dvb_frontend(client);
	dev->demod_i2c_adapter = pdata->get_i2c_adapter(client);

	dev->i2c_client_demod = client;

	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtl2832_platक्रमm_data rtl2832_fc2580_platक्रमm_data = अणु
	.clk = 28800000,
	.tuner = TUNER_RTL2832_FC2580,
पूर्ण;

अटल स्थिर काष्ठा rtl2832_platक्रमm_data rtl2832_fc0012_platक्रमm_data = अणु
	.clk = 28800000,
	.tuner = TUNER_RTL2832_FC0012
पूर्ण;

अटल स्थिर काष्ठा rtl2832_platक्रमm_data rtl2832_fc0013_platक्रमm_data = अणु
	.clk = 28800000,
	.tuner = TUNER_RTL2832_FC0013
पूर्ण;

अटल स्थिर काष्ठा rtl2832_platक्रमm_data rtl2832_tua9001_platक्रमm_data = अणु
	.clk = 28800000,
	.tuner = TUNER_RTL2832_TUA9001,
पूर्ण;

अटल स्थिर काष्ठा rtl2832_platक्रमm_data rtl2832_e4000_platक्रमm_data = अणु
	.clk = 28800000,
	.tuner = TUNER_RTL2832_E4000,
पूर्ण;

अटल स्थिर काष्ठा rtl2832_platक्रमm_data rtl2832_r820t_platक्रमm_data = अणु
	.clk = 28800000,
	.tuner = TUNER_RTL2832_R820T,
पूर्ण;

अटल स्थिर काष्ठा rtl2832_platक्रमm_data rtl2832_si2157_platक्रमm_data = अणु
	.clk = 28800000,
	.tuner = TUNER_RTL2832_SI2157,
पूर्ण;

अटल पूर्णांक rtl2832u_fc0012_tuner_callback(काष्ठा dvb_usb_device *d,
		पूर्णांक cmd, पूर्णांक arg)
अणु
	पूर्णांक ret;
	u8 val;

	dev_dbg(&d->पूर्णांकf->dev, "cmd=%d arg=%d\n", cmd, arg);

	चयन (cmd) अणु
	हाल FC_FE_CALLBACK_VHF_ENABLE:
		/* set output values */
		ret = rtl28xxu_rd_reg(d, SYS_GPIO_OUT_VAL, &val);
		अगर (ret)
			जाओ err;

		अगर (arg)
			val &= 0xbf; /* set GPIO6 low */
		अन्यथा
			val |= 0x40; /* set GPIO6 high */


		ret = rtl28xxu_wr_reg(d, SYS_GPIO_OUT_VAL, val);
		अगर (ret)
			जाओ err;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832u_tua9001_tuner_callback(काष्ठा dvb_usb_device *d,
		पूर्णांक cmd, पूर्णांक arg)
अणु
	पूर्णांक ret;
	u8 val;

	dev_dbg(&d->पूर्णांकf->dev, "cmd=%d arg=%d\n", cmd, arg);

	/*
	 * CEN     always enabled by hardware wiring
	 * RESETN  GPIO4
	 * RXEN    GPIO1
	 */

	चयन (cmd) अणु
	हाल TUA9001_CMD_RESETN:
		अगर (arg)
			val = (1 << 4);
		अन्यथा
			val = (0 << 4);

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, val, 0x10);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल TUA9001_CMD_RXEN:
		अगर (arg)
			val = (1 << 1);
		अन्यथा
			val = (0 << 1);

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, val, 0x02);
		अगर (ret)
			जाओ err;
		अवरोध;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832u_frontend_callback(व्योम *adapter_priv, पूर्णांक component,
		पूर्णांक cmd, पूर्णांक arg)
अणु
	काष्ठा i2c_adapter *adapter = adapter_priv;
	काष्ठा device *parent = adapter->dev.parent;
	काष्ठा i2c_adapter *parent_adapter;
	काष्ठा dvb_usb_device *d;
	काष्ठा rtl28xxu_dev *dev;

	/*
	 * All tuners are connected to demod muxed I2C adapter. We have to
	 * resolve its parent adapter in order to get handle क्रम this driver
	 * निजी data. That is a bit hackish solution, GPIO or direct driver
	 * callback would be better...
	 */
	अगर (parent != शून्य && parent->type == &i2c_adapter_type)
		parent_adapter = to_i2c_adapter(parent);
	अन्यथा
		वापस -EINVAL;

	d = i2c_get_adapdata(parent_adapter);
	dev = d->priv;

	dev_dbg(&d->पूर्णांकf->dev, "component=%d cmd=%d arg=%d\n",
		component, cmd, arg);

	चयन (component) अणु
	हाल DVB_FRONTEND_COMPONENT_TUNER:
		चयन (dev->tuner) अणु
		हाल TUNER_RTL2832_FC0012:
			वापस rtl2832u_fc0012_tuner_callback(d, cmd, arg);
		हाल TUNER_RTL2832_TUA9001:
			वापस rtl2832u_tua9001_tuner_callback(d, cmd, arg);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832u_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	काष्ठा rtl2832_platक्रमm_data *pdata = &dev->rtl2832_platक्रमm_data;
	काष्ठा i2c_board_info board_info;
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	चयन (dev->tuner) अणु
	हाल TUNER_RTL2832_FC0012:
		*pdata = rtl2832_fc0012_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2832_FC0013:
		*pdata = rtl2832_fc0013_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2832_FC2580:
		*pdata = rtl2832_fc2580_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2832_TUA9001:
		*pdata = rtl2832_tua9001_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2832_E4000:
		*pdata = rtl2832_e4000_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2832_R820T:
	हाल TUNER_RTL2832_R828D:
		*pdata = rtl2832_r820t_platक्रमm_data;
		अवरोध;
	हाल TUNER_RTL2832_SI2157:
		*pdata = rtl2832_si2157_platक्रमm_data;
		अवरोध;
	शेष:
		dev_err(&d->पूर्णांकf->dev, "unknown tuner %s\n", dev->tuner_name);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* attach demodulator */
	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "rtl2832", I2C_NAME_SIZE);
	board_info.addr = 0x10;
	board_info.platक्रमm_data = pdata;
	request_module("%s", board_info.type);
	client = i2c_new_client_device(&d->i2c_adap, &board_info);
	अगर (!i2c_client_has_driver(client)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	adap->fe[0] = pdata->get_dvb_frontend(client);
	dev->demod_i2c_adapter = pdata->get_i2c_adapter(client);

	dev->i2c_client_demod = client;

	/* set fe callback */
	adap->fe[0]->callback = rtl2832u_frontend_callback;

	अगर (dev->slave_demod) अणु
		काष्ठा i2c_board_info info = अणुपूर्ण;

		/* attach slave demodulator */
		अगर (dev->slave_demod == SLAVE_DEMOD_MN88472) अणु
			काष्ठा mn88472_config mn88472_config = अणुपूर्ण;

			mn88472_config.fe = &adap->fe[1];
			mn88472_config.i2c_wr_max = 22;
			strscpy(info.type, "mn88472", I2C_NAME_SIZE);
			mn88472_config.xtal = 20500000;
			mn88472_config.ts_mode = SERIAL_TS_MODE;
			mn88472_config.ts_घड़ी = VARIABLE_TS_CLOCK;
			info.addr = 0x18;
			info.platक्रमm_data = &mn88472_config;
			request_module(info.type);
			client = i2c_new_client_device(&d->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client))
				जाओ err_slave_demod_failed;

			अगर (!try_module_get(client->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client);
				जाओ err_slave_demod_failed;
			पूर्ण

			dev->i2c_client_slave_demod = client;
		पूर्ण अन्यथा अगर (dev->slave_demod == SLAVE_DEMOD_MN88473) अणु
			काष्ठा mn88473_config mn88473_config = अणुपूर्ण;

			mn88473_config.fe = &adap->fe[1];
			mn88473_config.i2c_wr_max = 22;
			strscpy(info.type, "mn88473", I2C_NAME_SIZE);
			info.addr = 0x18;
			info.platक्रमm_data = &mn88473_config;
			request_module(info.type);
			client = i2c_new_client_device(&d->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client))
				जाओ err_slave_demod_failed;

			अगर (!try_module_get(client->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client);
				जाओ err_slave_demod_failed;
			पूर्ण

			dev->i2c_client_slave_demod = client;
		पूर्ण अन्यथा अगर (dev->slave_demod == SLAVE_DEMOD_CXD2837ER) अणु
			काष्ठा cxd2841er_config cxd2837er_config = अणुपूर्ण;

			cxd2837er_config.i2c_addr = 0xd8;
			cxd2837er_config.xtal = SONY_XTAL_20500;
			cxd2837er_config.flags = (CXD2841ER_AUTO_IFHZ |
				CXD2841ER_NO_AGCNEG | CXD2841ER_TSBITS |
				CXD2841ER_EARLY_TUNE | CXD2841ER_TS_SERIAL);
			adap->fe[1] = dvb_attach(cxd2841er_attach_t_c,
						 &cxd2837er_config,
						 &d->i2c_adap);
			अगर (!adap->fe[1])
				जाओ err_slave_demod_failed;
			adap->fe[1]->id = 1;
			dev->i2c_client_slave_demod = शून्य;
		पूर्ण अन्यथा अणु
			काष्ठा si2168_config si2168_config = अणुपूर्ण;
			काष्ठा i2c_adapter *adapter;

			si2168_config.i2c_adapter = &adapter;
			si2168_config.fe = &adap->fe[1];
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			si2168_config.ts_घड़ी_inv = false;
			si2168_config.ts_घड़ी_gapped = true;
			strscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addr = 0x64;
			info.platक्रमm_data = &si2168_config;
			request_module(info.type);
			client = i2c_new_client_device(&d->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client))
				जाओ err_slave_demod_failed;

			अगर (!try_module_get(client->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client);
				जाओ err_slave_demod_failed;
			पूर्ण

			dev->i2c_client_slave_demod = client;

			/* क्रम Si2168 devices use only new I2C ग_लिखो method */
			dev->new_i2c_ग_लिखो = true;
		पूर्ण
	पूर्ण
	वापस 0;

err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;

err_slave_demod_failed:
	/*
	 * We जारी on reduced mode, without DVB-T2/C, using master
	 * demod, when slave demod fails.
	 */
	dev->slave_demod = SLAVE_DEMOD_NONE;
	वापस 0;
पूर्ण

अटल पूर्णांक rtl28xxu_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा rtl28xxu_dev *dev = adap_to_priv(adap);

	अगर (dev->chip_id == CHIP_ID_RTL2831U)
		वापस rtl2831u_frontend_attach(adap);
	अन्यथा
		वापस rtl2832u_frontend_attach(adap);
पूर्ण

अटल पूर्णांक rtl28xxu_frontend_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	काष्ठा i2c_client *client;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	/* हटाओ I2C slave demod */
	client = dev->i2c_client_slave_demod;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* हटाओ I2C demod */
	client = dev->i2c_client_demod;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा qt1010_config rtl28xxu_qt1010_config = अणु
	.i2c_address = 0x62, /* 0xc4 */
पूर्ण;

अटल काष्ठा mt2060_config rtl28xxu_mt2060_config = अणु
	.i2c_address = 0x60, /* 0xc0 */
	.घड़ी_out = 0,
पूर्ण;

अटल काष्ठा mxl5005s_config rtl28xxu_mxl5005s_config = अणु
	.i2c_address     = 0x63, /* 0xc6 */
	.अगर_freq         = IF_FREQ_4570000HZ,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_C_H,
	.rssi_enable     = MXL_RSSI_ENABLE,
	.cap_select      = MXL_CAP_SEL_ENABLE,
	.भाग_out         = MXL_DIV_OUT_4,
	.घड़ी_out       = MXL_CLOCK_OUT_DISABLE,
	.output_load     = MXL5005S_IF_OUTPUT_LOAD_200_OHM,
	.top		 = MXL5005S_TOP_25P2,
	.mod_mode        = MXL_DIGITAL_MODE,
	.अगर_mode         = MXL_ZERO_IF,
	.AgcMasterByte   = 0x00,
पूर्ण;

अटल पूर्णांक rtl2831u_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	काष्ठा dvb_frontend *fe;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	चयन (dev->tuner) अणु
	हाल TUNER_RTL2830_QT1010:
		fe = dvb_attach(qt1010_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl28xxu_qt1010_config);
		अवरोध;
	हाल TUNER_RTL2830_MT2060:
		fe = dvb_attach(mt2060_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl28xxu_mt2060_config, 1220);
		अवरोध;
	हाल TUNER_RTL2830_MXL5005S:
		fe = dvb_attach(mxl5005s_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl28xxu_mxl5005s_config);
		अवरोध;
	शेष:
		fe = शून्य;
		dev_err(&d->पूर्णांकf->dev, "unknown tuner %d\n", dev->tuner);
	पूर्ण

	अगर (fe == शून्य) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fc0012_config rtl2832u_fc0012_config = अणु
	.i2c_address = 0x63, /* 0xc6 >> 1 */
	.xtal_freq = FC_XTAL_28_8_MHZ,
पूर्ण;

अटल स्थिर काष्ठा r820t_config rtl2832u_r820t_config = अणु
	.i2c_addr = 0x1a,
	.xtal = 28800000,
	.max_i2c_msg_len = 2,
	.rafael_chip = CHIP_R820T,
पूर्ण;

अटल स्थिर काष्ठा r820t_config rtl2832u_r828d_config = अणु
	.i2c_addr = 0x3a,
	.xtal = 16000000,
	.max_i2c_msg_len = 2,
	.rafael_chip = CHIP_R828D,
पूर्ण;

अटल पूर्णांक rtl2832u_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	काष्ठा dvb_frontend *fe = शून्य;
	काष्ठा i2c_board_info info;
	काष्ठा i2c_client *client;
	काष्ठा v4l2_subdev *subdev = शून्य;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा rtl2832_sdr_platक्रमm_data pdata;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	स_रखो(&pdata, 0, माप(pdata));

	चयन (dev->tuner) अणु
	हाल TUNER_RTL2832_FC0012:
		fe = dvb_attach(fc0012_attach, adap->fe[0],
			dev->demod_i2c_adapter, &rtl2832u_fc0012_config);

		/* since fc0012 includs पढ़ोing the संकेत strength delegate
		 * that to the tuner driver */
		adap->fe[0]->ops.पढ़ो_संकेत_strength =
				adap->fe[0]->ops.tuner_ops.get_rf_strength;
		अवरोध;
	हाल TUNER_RTL2832_FC0013:
		fe = dvb_attach(fc0013_attach, adap->fe[0],
			dev->demod_i2c_adapter, 0xc6>>1, 0, FC_XTAL_28_8_MHZ);

		/* fc0013 also supports संकेत strength पढ़ोing */
		adap->fe[0]->ops.पढ़ो_संकेत_strength =
				adap->fe[0]->ops.tuner_ops.get_rf_strength;
		अवरोध;
	हाल TUNER_RTL2832_E4000: अणु
			काष्ठा e4000_config e4000_config = अणु
				.fe = adap->fe[0],
				.घड़ी = 28800000,
			पूर्ण;

			strscpy(info.type, "e4000", I2C_NAME_SIZE);
			info.addr = 0x64;
			info.platक्रमm_data = &e4000_config;

			request_module(info.type);
			client = i2c_new_client_device(dev->demod_i2c_adapter,
						       &info);
			अगर (!i2c_client_has_driver(client))
				अवरोध;

			अगर (!try_module_get(client->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client);
				अवरोध;
			पूर्ण

			dev->i2c_client_tuner = client;
			subdev = i2c_get_clientdata(client);
		पूर्ण
		अवरोध;
	हाल TUNER_RTL2832_FC2580: अणु
			काष्ठा fc2580_platक्रमm_data fc2580_pdata = अणु
				.dvb_frontend = adap->fe[0],
			पूर्ण;
			काष्ठा i2c_board_info board_info = अणुपूर्ण;

			strscpy(board_info.type, "fc2580", I2C_NAME_SIZE);
			board_info.addr = 0x56;
			board_info.platक्रमm_data = &fc2580_pdata;
			request_module("fc2580");
			client = i2c_new_client_device(dev->demod_i2c_adapter,
						       &board_info);
			अगर (!i2c_client_has_driver(client))
				अवरोध;
			अगर (!try_module_get(client->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client);
				अवरोध;
			पूर्ण
			dev->i2c_client_tuner = client;
			subdev = fc2580_pdata.get_v4l2_subdev(client);
		पूर्ण
		अवरोध;
	हाल TUNER_RTL2832_TUA9001: अणु
		काष्ठा tua9001_platक्रमm_data tua9001_pdata = अणु
			.dvb_frontend = adap->fe[0],
		पूर्ण;
		काष्ठा i2c_board_info board_info = अणुपूर्ण;

		/* enable GPIO1 and GPIO4 as output */
		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_सूची, 0x00, 0x12);
		अगर (ret)
			जाओ err;

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_EN, 0x12, 0x12);
		अगर (ret)
			जाओ err;

		strscpy(board_info.type, "tua9001", I2C_NAME_SIZE);
		board_info.addr = 0x60;
		board_info.platक्रमm_data = &tua9001_pdata;
		request_module("tua9001");
		client = i2c_new_client_device(dev->demod_i2c_adapter,
					       &board_info);
		अगर (!i2c_client_has_driver(client))
			अवरोध;
		अगर (!try_module_get(client->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client);
			अवरोध;
		पूर्ण
		dev->i2c_client_tuner = client;
		अवरोध;
	पूर्ण
	हाल TUNER_RTL2832_R820T:
		fe = dvb_attach(r820t_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl2832u_r820t_config);

		/* Use tuner to get the संकेत strength */
		adap->fe[0]->ops.पढ़ो_संकेत_strength =
				adap->fe[0]->ops.tuner_ops.get_rf_strength;
		अवरोध;
	हाल TUNER_RTL2832_R828D:
		fe = dvb_attach(r820t_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl2832u_r828d_config);
		adap->fe[0]->ops.पढ़ो_संकेत_strength =
				adap->fe[0]->ops.tuner_ops.get_rf_strength;

		अगर (adap->fe[1]) अणु
			fe = dvb_attach(r820t_attach, adap->fe[1],
					dev->demod_i2c_adapter,
					&rtl2832u_r828d_config);
			adap->fe[1]->ops.पढ़ो_संकेत_strength =
					adap->fe[1]->ops.tuner_ops.get_rf_strength;
		पूर्ण
		अवरोध;
	हाल TUNER_RTL2832_SI2157: अणु
			काष्ठा si2157_config si2157_config = अणु
				.fe = adap->fe[0],
				.अगर_port = 0,
				.inversion = false,
			पूर्ण;

			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x60;
			info.platक्रमm_data = &si2157_config;
			request_module(info.type);
			client = i2c_new_client_device(&d->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client))
				अवरोध;

			अगर (!try_module_get(client->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client);
				अवरोध;
			पूर्ण

			dev->i2c_client_tuner = client;
			subdev = i2c_get_clientdata(client);

			/* copy tuner ops क्रम 2nd FE as tuner is shared */
			अगर (adap->fe[1]) अणु
				adap->fe[1]->tuner_priv =
						adap->fe[0]->tuner_priv;
				स_नकल(&adap->fe[1]->ops.tuner_ops,
						&adap->fe[0]->ops.tuner_ops,
						माप(काष्ठा dvb_tuner_ops));
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&d->पूर्णांकf->dev, "unknown tuner %d\n", dev->tuner);
	पूर्ण
	अगर (fe == शून्य && dev->i2c_client_tuner == शून्य) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* रेजिस्टर SDR */
	चयन (dev->tuner) अणु
	हाल TUNER_RTL2832_FC2580:
	हाल TUNER_RTL2832_FC0012:
	हाल TUNER_RTL2832_FC0013:
	हाल TUNER_RTL2832_E4000:
	हाल TUNER_RTL2832_R820T:
	हाल TUNER_RTL2832_R828D:
		pdata.clk = dev->rtl2832_platक्रमm_data.clk;
		pdata.tuner = dev->tuner;
		pdata.regmap = dev->rtl2832_platक्रमm_data.regmap;
		pdata.dvb_frontend = adap->fe[0];
		pdata.dvb_usb_device = d;
		pdata.v4l2_subdev = subdev;

		request_module("%s", "rtl2832_sdr");
		pdev = platक्रमm_device_रेजिस्टर_data(&d->पूर्णांकf->dev,
						     "rtl2832_sdr",
						     PLATFORM_DEVID_AUTO,
						     &pdata, माप(pdata));
		अगर (IS_ERR(pdev) || pdev->dev.driver == शून्य)
			अवरोध;
		dev->platक्रमm_device_sdr = pdev;
		अवरोध;
	शेष:
		dev_dbg(&d->पूर्णांकf->dev, "no SDR for tuner=%d\n", dev->tuner);
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl28xxu_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा rtl28xxu_dev *dev = adap_to_priv(adap);

	अगर (dev->chip_id == CHIP_ID_RTL2831U)
		वापस rtl2831u_tuner_attach(adap);
	अन्यथा
		वापस rtl2832u_tuner_attach(adap);
पूर्ण

अटल पूर्णांक rtl28xxu_tuner_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);
	काष्ठा i2c_client *client;
	काष्ठा platक्रमm_device *pdev;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	/* हटाओ platक्रमm SDR */
	pdev = dev->platक्रमm_device_sdr;
	अगर (pdev)
		platक्रमm_device_unरेजिस्टर(pdev);

	/* हटाओ I2C tuner */
	client = dev->i2c_client_tuner;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl28xxu_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	u8 val;

	dev_dbg(&d->पूर्णांकf->dev, "\n");

	/* init USB endpoपूर्णांकs */
	ret = rtl28xxu_rd_reg(d, USB_SYSCTL_0, &val);
	अगर (ret)
		जाओ err;

	/* enable DMA and Full Packet Mode*/
	val |= 0x09;
	ret = rtl28xxu_wr_reg(d, USB_SYSCTL_0, val);
	अगर (ret)
		जाओ err;

	/* set EPA maximum packet size to 0x0200 */
	ret = rtl28xxu_wr_regs(d, USB_EPA_MAXPKT, "\x00\x02\x00\x00", 4);
	अगर (ret)
		जाओ err;

	/* change EPA FIFO length */
	ret = rtl28xxu_wr_regs(d, USB_EPA_FIFO_CFG, "\x14\x00\x00\x00", 4);
	अगर (ret)
		जाओ err;

	वापस ret;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2831u_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	पूर्णांक ret;
	u8 gpio, sys0, epa_ctl[2];

	dev_dbg(&d->पूर्णांकf->dev, "onoff=%d\n", onoff);

	/* demod adc */
	ret = rtl28xxu_rd_reg(d, SYS_SYS0, &sys0);
	अगर (ret)
		जाओ err;

	/* tuner घातer, पढ़ो GPIOs */
	ret = rtl28xxu_rd_reg(d, SYS_GPIO_OUT_VAL, &gpio);
	अगर (ret)
		जाओ err;

	dev_dbg(&d->पूर्णांकf->dev, "RD SYS0=%02x GPIO_OUT_VAL=%02x\n", sys0, gpio);

	अगर (onoff) अणु
		gpio |= 0x01; /* GPIO0 = 1 */
		gpio &= (~0x10); /* GPIO4 = 0 */
		gpio |= 0x04; /* GPIO2 = 1, LED on */
		sys0 = sys0 & 0x0f;
		sys0 |= 0xe0;
		epa_ctl[0] = 0x00; /* clear stall */
		epa_ctl[1] = 0x00; /* clear reset */
	पूर्ण अन्यथा अणु
		gpio &= (~0x01); /* GPIO0 = 0 */
		gpio |= 0x10; /* GPIO4 = 1 */
		gpio &= (~0x04); /* GPIO2 = 1, LED off */
		sys0 = sys0 & (~0xc0);
		epa_ctl[0] = 0x10; /* set stall */
		epa_ctl[1] = 0x02; /* set reset */
	पूर्ण

	dev_dbg(&d->पूर्णांकf->dev, "WR SYS0=%02x GPIO_OUT_VAL=%02x\n", sys0, gpio);

	/* demod adc */
	ret = rtl28xxu_wr_reg(d, SYS_SYS0, sys0);
	अगर (ret)
		जाओ err;

	/* tuner घातer, ग_लिखो GPIOs */
	ret = rtl28xxu_wr_reg(d, SYS_GPIO_OUT_VAL, gpio);
	अगर (ret)
		जाओ err;

	/* streaming EP: stall & reset */
	ret = rtl28xxu_wr_regs(d, USB_EPA_CTL, epa_ctl, 2);
	अगर (ret)
		जाओ err;

	अगर (onoff)
		usb_clear_halt(d->udev, usb_rcvbulkpipe(d->udev, 0x81));

	वापस ret;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832u_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	पूर्णांक ret;

	dev_dbg(&d->पूर्णांकf->dev, "onoff=%d\n", onoff);

	अगर (onoff) अणु
		/* GPIO3=1, GPIO4=0 */
		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x08, 0x18);
		अगर (ret)
			जाओ err;

		/* suspend? */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL1, 0x00, 0x10);
		अगर (ret)
			जाओ err;

		/* enable PLL */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL, 0x80, 0x80);
		अगर (ret)
			जाओ err;

		/* disable reset */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL, 0x20, 0x20);
		अगर (ret)
			जाओ err;

		/* streaming EP: clear stall & reset */
		ret = rtl28xxu_wr_regs(d, USB_EPA_CTL, "\x00\x00", 2);
		अगर (ret)
			जाओ err;

		ret = usb_clear_halt(d->udev, usb_rcvbulkpipe(d->udev, 0x81));
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		/* GPIO4=1 */
		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x10, 0x10);
		अगर (ret)
			जाओ err;

		/* disable PLL */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL, 0x00, 0x80);
		अगर (ret)
			जाओ err;

		/* streaming EP: set stall & reset */
		ret = rtl28xxu_wr_regs(d, USB_EPA_CTL, "\x10\x02", 2);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस ret;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl28xxu_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);

	अगर (dev->chip_id == CHIP_ID_RTL2831U)
		वापस rtl2831u_घातer_ctrl(d, onoff);
	अन्यथा
		वापस rtl2832u_घातer_ctrl(d, onoff);
पूर्ण

अटल पूर्णांक rtl28xxu_frontend_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा rtl28xxu_dev *dev = fe_to_priv(fe);
	काष्ठा rtl2832_platक्रमm_data *pdata = &dev->rtl2832_platक्रमm_data;
	पूर्णांक ret;
	u8 val;

	dev_dbg(&d->पूर्णांकf->dev, "fe=%d onoff=%d\n", fe->id, onoff);

	अगर (dev->chip_id == CHIP_ID_RTL2831U)
		वापस 0;

	अगर (fe->id == 0) अणु
		/* control पूर्णांकernal demod ADC */
		अगर (onoff)
			val = 0x48; /* enable ADC */
		अन्यथा
			val = 0x00; /* disable ADC */

		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL, val, 0x48);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (fe->id == 1) अणु
		/* bypass slave demod TS through master demod */
		ret = pdata->slave_ts_ctrl(dev->i2c_client_demod, onoff);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_RC_CORE)
अटल पूर्णांक rtl2831u_rc_query(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret, i;
	काष्ठा rtl28xxu_dev *dev = d->priv;
	u8 buf[5];
	u32 rc_code;
	अटल स्थिर काष्ठा rtl28xxu_reg_val rc_nec_tab[] = अणु
		अणु 0x3033, 0x80 पूर्ण,
		अणु 0x3020, 0x43 पूर्ण,
		अणु 0x3021, 0x16 पूर्ण,
		अणु 0x3022, 0x16 पूर्ण,
		अणु 0x3023, 0x5a पूर्ण,
		अणु 0x3024, 0x2d पूर्ण,
		अणु 0x3025, 0x16 पूर्ण,
		अणु 0x3026, 0x01 पूर्ण,
		अणु 0x3028, 0xb0 पूर्ण,
		अणु 0x3029, 0x04 पूर्ण,
		अणु 0x302c, 0x88 पूर्ण,
		अणु 0x302e, 0x13 पूर्ण,
		अणु 0x3030, 0xdf पूर्ण,
		अणु 0x3031, 0x05 पूर्ण,
	पूर्ण;

	/* init remote controller */
	अगर (!dev->rc_active) अणु
		क्रम (i = 0; i < ARRAY_SIZE(rc_nec_tab); i++) अणु
			ret = rtl28xxu_wr_reg(d, rc_nec_tab[i].reg,
					rc_nec_tab[i].val);
			अगर (ret)
				जाओ err;
		पूर्ण
		dev->rc_active = true;
	पूर्ण

	ret = rtl28xxu_rd_regs(d, SYS_IRRC_RP, buf, 5);
	अगर (ret)
		जाओ err;

	अगर (buf[4] & 0x01) अणु
		क्रमागत rc_proto proto;

		अगर (buf[2] == (u8) ~buf[3]) अणु
			अगर (buf[0] == (u8) ~buf[1]) अणु
				/* NEC standard (16 bit) */
				rc_code = RC_SCANCODE_NEC(buf[0], buf[2]);
				proto = RC_PROTO_NEC;
			पूर्ण अन्यथा अणु
				/* NEC extended (24 bit) */
				rc_code = RC_SCANCODE_NECX(buf[0] << 8 | buf[1],
							   buf[2]);
				proto = RC_PROTO_NECX;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* NEC full (32 bit) */
			rc_code = RC_SCANCODE_NEC32(buf[0] << 24 | buf[1] << 16 |
						    buf[2] << 8  | buf[3]);
			proto = RC_PROTO_NEC32;
		पूर्ण

		rc_keyकरोwn(d->rc_dev, proto, rc_code, 0);

		ret = rtl28xxu_wr_reg(d, SYS_IRRC_SR, 1);
		अगर (ret)
			जाओ err;

		/* repeated पूर्णांकentionally to aव्योम extra keypress */
		ret = rtl28xxu_wr_reg(d, SYS_IRRC_SR, 1);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस ret;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2831u_get_rc_config(काष्ठा dvb_usb_device *d,
		काष्ठा dvb_usb_rc *rc)
अणु
	rc->map_name = RC_MAP_EMPTY;
	rc->allowed_protos = RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX |
							RC_PROTO_BIT_NEC32;
	rc->query = rtl2831u_rc_query;
	rc->पूर्णांकerval = 400;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832u_rc_query(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret, i, len;
	काष्ठा rtl28xxu_dev *dev = d->priv;
	काष्ठा ir_raw_event ev = अणुपूर्ण;
	u8 buf[128];
	अटल स्थिर काष्ठा rtl28xxu_reg_val_mask refresh_tab[] = अणु
		अणुIR_RX_IF,               0x03, 0xffपूर्ण,
		अणुIR_RX_BUF_CTRL,         0x80, 0xffपूर्ण,
		अणुIR_RX_CTRL,             0x80, 0xffपूर्ण,
	पूर्ण;

	/* init remote controller */
	अगर (!dev->rc_active) अणु
		अटल स्थिर काष्ठा rtl28xxu_reg_val_mask init_tab[] = अणु
			अणुSYS_DEMOD_CTL1,         0x00, 0x04पूर्ण,
			अणुSYS_DEMOD_CTL1,         0x00, 0x08पूर्ण,
			अणुUSB_CTRL,               0x20, 0x20पूर्ण,
			अणुSYS_GPIO_सूची,           0x00, 0x08पूर्ण,
			अणुSYS_GPIO_OUT_EN,        0x08, 0x08पूर्ण,
			अणुSYS_GPIO_OUT_VAL,       0x08, 0x08पूर्ण,
			अणुIR_MAX_DURATION0,       0xd0, 0xffपूर्ण,
			अणुIR_MAX_DURATION1,       0x07, 0xffपूर्ण,
			अणुIR_IDLE_LEN0,           0xc0, 0xffपूर्ण,
			अणुIR_IDLE_LEN1,           0x00, 0xffपूर्ण,
			अणुIR_GLITCH_LEN,          0x03, 0xffपूर्ण,
			अणुIR_RX_CLK,              0x09, 0xffपूर्ण,
			अणुIR_RX_CFG,              0x1c, 0xffपूर्ण,
			अणुIR_MAX_H_TOL_LEN,       0x1e, 0xffपूर्ण,
			अणुIR_MAX_L_TOL_LEN,       0x1e, 0xffपूर्ण,
			अणुIR_RX_CTRL,             0x80, 0xffपूर्ण,
		पूर्ण;

		क्रम (i = 0; i < ARRAY_SIZE(init_tab); i++) अणु
			ret = rtl28xxu_wr_reg_mask(d, init_tab[i].reg,
					init_tab[i].val, init_tab[i].mask);
			अगर (ret)
				जाओ err;
		पूर्ण

		dev->rc_active = true;
	पूर्ण

	ret = rtl28xxu_rd_reg(d, IR_RX_IF, &buf[0]);
	अगर (ret)
		जाओ err;

	अगर (buf[0] != 0x83)
		जाओ निकास;

	ret = rtl28xxu_rd_reg(d, IR_RX_BC, &buf[0]);
	अगर (ret || buf[0] > माप(buf))
		जाओ err;

	len = buf[0];

	/* पढ़ो raw code from hw */
	ret = rtl28xxu_rd_regs(d, IR_RX_BUF, buf, len);
	अगर (ret)
		जाओ err;

	/* let hw receive new code */
	क्रम (i = 0; i < ARRAY_SIZE(refresh_tab); i++) अणु
		ret = rtl28xxu_wr_reg_mask(d, refresh_tab[i].reg,
				refresh_tab[i].val, refresh_tab[i].mask);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* pass data to Kernel IR decoder */
	क्रम (i = 0; i < len; i++) अणु
		ev.pulse = buf[i] >> 7;
		ev.duration = 51 * (buf[i] & 0x7f);
		ir_raw_event_store_with_filter(d->rc_dev, &ev);
	पूर्ण

	/* 'flush'त ir_raw_event_store_with_filter() */
	ir_raw_event_handle(d->rc_dev);
निकास:
	वापस ret;
err:
	dev_dbg(&d->पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832u_get_rc_config(काष्ठा dvb_usb_device *d,
		काष्ठा dvb_usb_rc *rc)
अणु
	/* disable IR पूर्णांकerrupts in order to aव्योम SDR sample loss */
	अगर (rtl28xxu_disable_rc)
		वापस rtl28xxu_wr_reg(d, IR_RX_IE, 0x00);

	/* load empty to enable rc */
	अगर (!rc->map_name)
		rc->map_name = RC_MAP_EMPTY;
	rc->allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->driver_type = RC_DRIVER_IR_RAW;
	rc->query = rtl2832u_rc_query;
	rc->पूर्णांकerval = 200;
	/* we program idle len to 0xc0, set समयout to one less */
	rc->समयout = 0xbf * 51;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl28xxu_get_rc_config(काष्ठा dvb_usb_device *d,
		काष्ठा dvb_usb_rc *rc)
अणु
	काष्ठा rtl28xxu_dev *dev = d_to_priv(d);

	अगर (dev->chip_id == CHIP_ID_RTL2831U)
		वापस rtl2831u_get_rc_config(d, rc);
	अन्यथा
		वापस rtl2832u_get_rc_config(d, rc);
पूर्ण
#अन्यथा
#घोषणा rtl28xxu_get_rc_config शून्य
#पूर्ण_अगर

अटल पूर्णांक rtl28xxu_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा rtl28xxu_dev *dev = adap_to_priv(adap);

	अगर (dev->chip_id == CHIP_ID_RTL2831U) अणु
		काष्ठा rtl2830_platक्रमm_data *pdata = &dev->rtl2830_platक्रमm_data;

		वापस pdata->pid_filter_ctrl(adap->fe[0], onoff);
	पूर्ण अन्यथा अणु
		काष्ठा rtl2832_platक्रमm_data *pdata = &dev->rtl2832_platक्रमm_data;

		वापस pdata->pid_filter_ctrl(adap->fe[0], onoff);
	पूर्ण
पूर्ण

अटल पूर्णांक rtl28xxu_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index,
			       u16 pid, पूर्णांक onoff)
अणु
	काष्ठा rtl28xxu_dev *dev = adap_to_priv(adap);

	अगर (dev->chip_id == CHIP_ID_RTL2831U) अणु
		काष्ठा rtl2830_platक्रमm_data *pdata = &dev->rtl2830_platक्रमm_data;

		वापस pdata->pid_filter(adap->fe[0], index, pid, onoff);
	पूर्ण अन्यथा अणु
		काष्ठा rtl2832_platक्रमm_data *pdata = &dev->rtl2832_platक्रमm_data;

		वापस pdata->pid_filter(adap->fe[0], index, pid, onoff);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dvb_usb_device_properties rtl28xxu_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा rtl28xxu_dev),

	.identअगरy_state = rtl28xxu_identअगरy_state,
	.घातer_ctrl = rtl28xxu_घातer_ctrl,
	.frontend_ctrl = rtl28xxu_frontend_ctrl,
	.i2c_algo = &rtl28xxu_i2c_algo,
	.पढ़ो_config = rtl28xxu_पढ़ो_config,
	.frontend_attach = rtl28xxu_frontend_attach,
	.frontend_detach = rtl28xxu_frontend_detach,
	.tuner_attach = rtl28xxu_tuner_attach,
	.tuner_detach = rtl28xxu_tuner_detach,
	.init = rtl28xxu_init,
	.get_rc_config = rtl28xxu_get_rc_config,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER |
				DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

			.pid_filter_count = 32,
			.pid_filter_ctrl = rtl28xxu_pid_filter_ctrl,
			.pid_filter = rtl28xxu_pid_filter,

			.stream = DVB_USB_STREAM_BULK(0x81, 6, 8 * 512),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id rtl28xxu_id_table[] = अणु
	/* RTL2831U devices: */
	अणु DVB_USB_DEVICE(USB_VID_REALTEK, USB_PID_REALTEK_RTL2831U,
		&rtl28xxu_props, "Realtek RTL2831U reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_FREECOM_DVBT,
		&rtl28xxu_props, "Freecom USB2.0 DVB-T", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_FREECOM_DVBT_2,
		&rtl28xxu_props, "Freecom USB2.0 DVB-T", शून्य) पूर्ण,

	/* RTL2832U devices: */
	अणु DVB_USB_DEVICE(USB_VID_REALTEK, 0x2832,
		&rtl28xxu_props, "Realtek RTL2832U reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_REALTEK, 0x2838,
		&rtl28xxu_props, "Realtek RTL2832U reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_T_STICK_BLACK_REV1,
		&rtl28xxu_props, "TerraTec Cinergy T Stick Black", RC_MAP_TERRATEC_SLIM) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_DELOCK_USB2_DVBT,
		&rtl28xxu_props, "G-Tek Electronics Group Lifeview LV5TDLX DVB-T", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_NOXON_DAB_STICK,
		&rtl28xxu_props, "TerraTec NOXON DAB Stick", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_NOXON_DAB_STICK_REV2,
		&rtl28xxu_props, "TerraTec NOXON DAB Stick (rev 2)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_NOXON_DAB_STICK_REV3,
		&rtl28xxu_props, "TerraTec NOXON DAB Stick (rev 3)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_TREKSTOR_TERRES_2_0,
		&rtl28xxu_props, "Trekstor DVB-T Stick Terres 2.0", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_DEXATEK, 0x1101,
		&rtl28xxu_props, "Dexatek DK DVB-T Dongle", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_LEADTEK, 0x6680,
		&rtl28xxu_props, "DigitalNow Quad DVB-T Receiver", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_LEADTEK, USB_PID_WINFAST_DTV_DONGLE_MINID,
		&rtl28xxu_props, "Leadtek Winfast DTV Dongle Mini D", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_LEADTEK, USB_PID_WINFAST_DTV2000DS_PLUS,
		&rtl28xxu_props, "Leadtek WinFast DTV2000DS Plus", RC_MAP_LEADTEK_Y04G0051) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, 0x00d3,
		&rtl28xxu_props, "TerraTec Cinergy T Stick RC (Rev. 3)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_DEXATEK, 0x1102,
		&rtl28xxu_props, "Dexatek DK mini DVB-T Dongle", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, 0x00d7,
		&rtl28xxu_props, "TerraTec Cinergy T Stick+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, 0xd3a8,
		&rtl28xxu_props, "ASUS My Cinema-U3100Mini Plus V2", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, 0xd393,
		&rtl28xxu_props, "GIGABYTE U7300", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_DEXATEK, 0x1104,
		&rtl28xxu_props, "MSI DIGIVOX Micro HD", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_COMPRO, 0x0620,
		&rtl28xxu_props, "Compro VideoMate U620F", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_COMPRO, 0x0650,
		&rtl28xxu_props, "Compro VideoMate U650F", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, 0xd394,
		&rtl28xxu_props, "MaxMedia HU394-T", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_LEADTEK, 0x6a03,
		&rtl28xxu_props, "Leadtek WinFast DTV Dongle mini", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_CPYTO_REDI_PC50A,
		&rtl28xxu_props, "Crypto ReDi PC 50 A", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KYE, 0x707f,
		&rtl28xxu_props, "Genius TVGo DVB-T03", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, 0xd395,
		&rtl28xxu_props, "Peak DVB-T USB", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_SVEON_STV20_RTL2832U,
		&rtl28xxu_props, "Sveon STV20", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_SVEON_STV21,
		&rtl28xxu_props, "Sveon STV21", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_SVEON_STV27,
		&rtl28xxu_props, "Sveon STV27", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_TURBOX_DTT_2000,
		&rtl28xxu_props, "TURBO-X Pure TV Tuner DTT-2000", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_PROLECTRIX_DV107669,
		&rtl28xxu_props, "PROlectrix DV107669", शून्य) पूर्ण,

	/* RTL2832P devices: */
	अणु DVB_USB_DEVICE(USB_VID_HANFTEK, 0x0131,
		&rtl28xxu_props, "Astrometa DVB-T2",
		RC_MAP_ASTROMETA_T2HYBRID) पूर्ण,
	अणु DVB_USB_DEVICE(0x5654, 0xca42,
		&rtl28xxu_props, "GoTView MasterHD 3", शून्य) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, rtl28xxu_id_table);

अटल काष्ठा usb_driver rtl28xxu_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = rtl28xxu_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(rtl28xxu_usb_driver);

MODULE_DESCRIPTION("Realtek RTL28xxU DVB USB driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_AUTHOR("Thomas Mair <thomas.mair86@googlemail.com>");
MODULE_LICENSE("GPL");
