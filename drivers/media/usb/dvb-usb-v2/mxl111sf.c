<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010-2014 Michael Krufky (mkrufky@linuxtv.org)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/i2c.h>
#समावेश <media/tuner.h>

#समावेश "mxl111sf.h"
#समावेश "mxl111sf-reg.h"
#समावेश "mxl111sf-phy.h"
#समावेश "mxl111sf-i2c.h"
#समावेश "mxl111sf-gpio.h"

#समावेश "mxl111sf-demod.h"
#समावेश "mxl111sf-tuner.h"

#समावेश "lgdt3305.h"
#समावेश "lg2160.h"

पूर्णांक dvb_usb_mxl111sf_debug;
module_param_named(debug, dvb_usb_mxl111sf_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info, 2=xfer, 4=i2c, 8=reg, 16=adv (or-able)).");

अटल पूर्णांक dvb_usb_mxl111sf_isoc;
module_param_named(isoc, dvb_usb_mxl111sf_isoc, पूर्णांक, 0644);
MODULE_PARM_DESC(isoc, "enable usb isoc xfer (0=bulk, 1=isoc).");

अटल पूर्णांक dvb_usb_mxl111sf_spi;
module_param_named(spi, dvb_usb_mxl111sf_spi, पूर्णांक, 0644);
MODULE_PARM_DESC(spi, "use spi rather than tp for data xfer (0=tp, 1=spi).");

#घोषणा ANT_PATH_AUTO 0
#घोषणा ANT_PATH_EXTERNAL 1
#घोषणा ANT_PATH_INTERNAL 2

अटल पूर्णांक dvb_usb_mxl111sf_rfचयन =
#अगर 0
		ANT_PATH_AUTO;
#अन्यथा
		ANT_PATH_EXTERNAL;
#पूर्ण_अगर

module_param_named(rfचयन, dvb_usb_mxl111sf_rfचयन, पूर्णांक, 0644);
MODULE_PARM_DESC(rfचयन, "force rf switch position (0=auto, 1=ext, 2=int).");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

पूर्णांक mxl111sf_ctrl_msg(काष्ठा mxl111sf_state *state,
		      u8 cmd, u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा dvb_usb_device *d = state->d;
	पूर्णांक wo = (rbuf == शून्य || rlen == 0); /* ग_लिखो-only */
	पूर्णांक ret;

	अगर (1 + wlen > MXL_MAX_XFER_SIZE) अणु
		pr_warn("%s: len=%d is too big!\n", __func__, wlen);
		वापस -EOPNOTSUPP;
	पूर्ण

	pr_debug("%s(wlen = %d, rlen = %d)\n", __func__, wlen, rlen);

	mutex_lock(&state->msg_lock);
	स_रखो(state->sndbuf, 0, 1+wlen);
	स_रखो(state->rcvbuf, 0, rlen);

	state->sndbuf[0] = cmd;
	स_नकल(&state->sndbuf[1], wbuf, wlen);

	ret = (wo) ? dvb_usbv2_generic_ग_लिखो(d, state->sndbuf, 1+wlen) :
		dvb_usbv2_generic_rw(d, state->sndbuf, 1+wlen, state->rcvbuf,
				     rlen);

	अगर (rbuf)
		स_नकल(rbuf, state->rcvbuf, rlen);

	mutex_unlock(&state->msg_lock);

	mxl_fail(ret);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

#घोषणा MXL_CMD_REG_READ	0xaa
#घोषणा MXL_CMD_REG_WRITE	0x55

पूर्णांक mxl111sf_पढ़ो_reg(काष्ठा mxl111sf_state *state, u8 addr, u8 *data)
अणु
	u8 buf[2];
	पूर्णांक ret;

	ret = mxl111sf_ctrl_msg(state, MXL_CMD_REG_READ, &addr, 1, buf, 2);
	अगर (mxl_fail(ret)) अणु
		mxl_debug("error reading reg: 0x%02x", addr);
		जाओ fail;
	पूर्ण

	अगर (buf[0] == addr)
		*data = buf[1];
	अन्यथा अणु
		pr_err("invalid response reading reg: 0x%02x != 0x%02x, 0x%02x",
		    addr, buf[0], buf[1]);
		ret = -EINVAL;
	पूर्ण

	pr_debug("R: (0x%02x, 0x%02x)\n", addr, buf[1]);
fail:
	वापस ret;
पूर्ण

पूर्णांक mxl111sf_ग_लिखो_reg(काष्ठा mxl111sf_state *state, u8 addr, u8 data)
अणु
	u8 buf[] = अणु addr, data पूर्ण;
	पूर्णांक ret;

	pr_debug("W: (0x%02x, 0x%02x)\n", addr, data);

	ret = mxl111sf_ctrl_msg(state, MXL_CMD_REG_WRITE, buf, 2, शून्य, 0);
	अगर (mxl_fail(ret))
		pr_err("error writing reg: 0x%02x, val: 0x%02x", addr, data);
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

पूर्णांक mxl111sf_ग_लिखो_reg_mask(काष्ठा mxl111sf_state *state,
				   u8 addr, u8 mask, u8 data)
अणु
	पूर्णांक ret;
	u8 val = 0;

	अगर (mask != 0xff) अणु
		ret = mxl111sf_पढ़ो_reg(state, addr, &val);
#अगर 1
		/* करोn't know why this usually errors out on the first try */
		अगर (mxl_fail(ret))
			pr_err("error writing addr: 0x%02x, mask: 0x%02x, data: 0x%02x, retrying...",
			       addr, mask, data);

		ret = mxl111sf_पढ़ो_reg(state, addr, &val);
#पूर्ण_अगर
		अगर (mxl_fail(ret))
			जाओ fail;
	पूर्ण
	val &= ~mask;
	val |= data;

	ret = mxl111sf_ग_लिखो_reg(state, addr, val);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

पूर्णांक mxl111sf_ctrl_program_regs(काष्ठा mxl111sf_state *state,
			       काष्ठा mxl111sf_reg_ctrl_info *ctrl_reg_info)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0;  ctrl_reg_info[i].addr |
		     ctrl_reg_info[i].mask |
		     ctrl_reg_info[i].data;  i++) अणु

		ret = mxl111sf_ग_लिखो_reg_mask(state,
					      ctrl_reg_info[i].addr,
					      ctrl_reg_info[i].mask,
					      ctrl_reg_info[i].data);
		अगर (mxl_fail(ret)) अणु
			pr_err("failed on reg #%d (0x%02x)", i,
			    ctrl_reg_info[i].addr);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक mxl1x1sf_get_chip_info(काष्ठा mxl111sf_state *state)
अणु
	पूर्णांक ret;
	u8 id, ver;
	अक्षर *mxl_chip, *mxl_rev;

	अगर ((state->chip_id) && (state->chip_ver))
		वापस 0;

	ret = mxl111sf_पढ़ो_reg(state, CHIP_ID_REG, &id);
	अगर (mxl_fail(ret))
		जाओ fail;
	state->chip_id = id;

	ret = mxl111sf_पढ़ो_reg(state, TOP_CHIP_REV_ID_REG, &ver);
	अगर (mxl_fail(ret))
		जाओ fail;
	state->chip_ver = ver;

	चयन (id) अणु
	हाल 0x61:
		mxl_chip = "MxL101SF";
		अवरोध;
	हाल 0x63:
		mxl_chip = "MxL111SF";
		अवरोध;
	शेष:
		mxl_chip = "UNKNOWN MxL1X1";
		अवरोध;
	पूर्ण
	चयन (ver) अणु
	हाल 0x36:
		state->chip_rev = MXL111SF_V6;
		mxl_rev = "v6";
		अवरोध;
	हाल 0x08:
		state->chip_rev = MXL111SF_V8_100;
		mxl_rev = "v8_100";
		अवरोध;
	हाल 0x18:
		state->chip_rev = MXL111SF_V8_200;
		mxl_rev = "v8_200";
		अवरोध;
	शेष:
		state->chip_rev = 0;
		mxl_rev = "UNKNOWN REVISION";
		अवरोध;
	पूर्ण
	pr_info("%s detected, %s (0x%x)", mxl_chip, mxl_rev, ver);
fail:
	वापस ret;
पूर्ण

#घोषणा get_chip_info(state)						\
(अणु									\
	पूर्णांक ___ret;							\
	___ret = mxl1x1sf_get_chip_info(state);				\
	अगर (mxl_fail(___ret)) अणु						\
		mxl_debug("failed to get chip info"			\
			  " on first probe attempt");			\
		___ret = mxl1x1sf_get_chip_info(state);			\
		अगर (mxl_fail(___ret))					\
			pr_err("failed to get chip info during probe");	\
		अन्यथा							\
			mxl_debug("probe needed a retry "		\
				  "in order to succeed.");		\
	पूर्ण								\
	___ret;								\
पूर्ण)

/* ------------------------------------------------------------------------ */
#अगर 0
अटल पूर्णांक mxl111sf_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	/* घातer control depends on which adapter is being woken:
	 * save this क्रम init, instead, via mxl111sf_adap_fe_init */
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mxl111sf_adap_fe_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा mxl111sf_state *state = fe_to_priv(fe);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe->id];
	पूर्णांक err;

	/* निकास अगर we didn't initialize the driver yet */
	अगर (!state->chip_id) अणु
		mxl_debug("driver not yet initialized, exit.");
		जाओ fail;
	पूर्ण

	pr_debug("%s()\n", __func__);

	mutex_lock(&state->fe_lock);

	state->alt_mode = adap_state->alt_mode;

	अगर (usb_set_पूर्णांकerface(d->udev, 0, state->alt_mode) < 0)
		pr_err("set interface failed");

	err = mxl1x1sf_soft_reset(state);
	mxl_fail(err);
	err = mxl111sf_init_tuner_demod(state);
	mxl_fail(err);
	err = mxl1x1sf_set_device_mode(state, adap_state->device_mode);

	mxl_fail(err);
	err = mxl111sf_enable_usb_output(state);
	mxl_fail(err);
	err = mxl1x1sf_top_master_ctrl(state, 1);
	mxl_fail(err);

	अगर ((MXL111SF_GPIO_MOD_DVBT != adap_state->gpio_mode) &&
	    (state->chip_rev > MXL111SF_V6)) अणु
		mxl111sf_config_pin_mux_modes(state,
					      PIN_MUX_TS_SPI_IN_MODE_1);
		mxl_fail(err);
	पूर्ण
	err = mxl111sf_init_port_expander(state);
	अगर (!mxl_fail(err)) अणु
		state->gpio_mode = adap_state->gpio_mode;
		err = mxl111sf_gpio_mode_चयन(state, state->gpio_mode);
		mxl_fail(err);
#अगर 0
		err = fe->ops.init(fe);
#पूर्ण_अगर
		msleep(100); /* add लघु delay after enabling
			      * the demod beक्रमe touching it */
	पूर्ण

	वापस (adap_state->fe_init) ? adap_state->fe_init(fe) : 0;
fail:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक mxl111sf_adap_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl111sf_state *state = fe_to_priv(fe);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe->id];
	पूर्णांक err;

	/* निकास अगर we didn't initialize the driver yet */
	अगर (!state->chip_id) अणु
		mxl_debug("driver not yet initialized, exit.");
		जाओ fail;
	पूर्ण

	pr_debug("%s()\n", __func__);

	err = (adap_state->fe_sleep) ? adap_state->fe_sleep(fe) : 0;

	mutex_unlock(&state->fe_lock);

	वापस err;
fail:
	वापस -ENODEV;
पूर्ण


अटल पूर्णांक mxl111sf_ep6_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा mxl111sf_state *state = fe_to_priv(fe);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe->id];
	पूर्णांक ret = 0;

	pr_debug("%s(%d)\n", __func__, onoff);

	अगर (onoff) अणु
		ret = mxl111sf_enable_usb_output(state);
		mxl_fail(ret);
		ret = mxl111sf_config_mpeg_in(state, 1, 1,
					      adap_state->ep6_घड़ीphase,
					      0, 0);
		mxl_fail(ret);
#अगर 0
	पूर्ण अन्यथा अणु
		ret = mxl111sf_disable_656_port(state);
		mxl_fail(ret);
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_ep5_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा mxl111sf_state *state = fe_to_priv(fe);
	पूर्णांक ret = 0;

	pr_debug("%s(%d)\n", __func__, onoff);

	अगर (onoff) अणु
		ret = mxl111sf_enable_usb_output(state);
		mxl_fail(ret);

		ret = mxl111sf_init_i2s_port(state, 200);
		mxl_fail(ret);
		ret = mxl111sf_config_i2s(state, 0, 15);
		mxl_fail(ret);
	पूर्ण अन्यथा अणु
		ret = mxl111sf_disable_i2s_port(state);
		mxl_fail(ret);
	पूर्ण
	अगर (state->chip_rev > MXL111SF_V6)
		ret = mxl111sf_config_spi(state, onoff);
	mxl_fail(ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_ep4_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा mxl111sf_state *state = fe_to_priv(fe);
	पूर्णांक ret = 0;

	pr_debug("%s(%d)\n", __func__, onoff);

	अगर (onoff) अणु
		ret = mxl111sf_enable_usb_output(state);
		mxl_fail(ret);
	पूर्ण

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल काष्ठा lgdt3305_config hauppauge_lgdt3305_config = अणु
	.i2c_addr           = 0xb2 >> 1,
	.mpeg_mode          = LGDT3305_MPEG_SERIAL,
	.tpclk_edge         = LGDT3305_TPCLK_RISING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_HIGH,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 0,
	.qam_अगर_khz         = 6000,
	.vsb_अगर_khz         = 6000,
पूर्ण;

अटल पूर्णांक mxl111sf_lgdt3305_frontend_attach(काष्ठा dvb_usb_adapter *adap, u8 fe_id)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा mxl111sf_state *state = d_to_priv(d);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe_id];
	पूर्णांक ret;

	pr_debug("%s()\n", __func__);

	/* save a poपूर्णांकer to the dvb_usb_device in device state */
	state->d = d;
	adap_state->alt_mode = (dvb_usb_mxl111sf_isoc) ? 2 : 1;
	state->alt_mode = adap_state->alt_mode;

	अगर (usb_set_पूर्णांकerface(d->udev, 0, state->alt_mode) < 0)
		pr_err("set interface failed");

	state->gpio_mode = MXL111SF_GPIO_MOD_ATSC;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXL_TUNER_MODE;
	adap_state->ep6_घड़ीphase = 1;

	ret = mxl1x1sf_soft_reset(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_init_tuner_demod(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl1x1sf_set_device_mode(state, adap_state->device_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_enable_usb_output(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_top_master_ctrl(state, 1);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_init_port_expander(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_gpio_mode_चयन(state, state->gpio_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	adap->fe[fe_id] = dvb_attach(lgdt3305_attach,
				 &hauppauge_lgdt3305_config,
				 &d->i2c_adap);
	अगर (adap->fe[fe_id]) अणु
		state->num_frontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxl111sf_adap_fe_init;
		adap_state->fe_sleep = adap->fe[fe_id]->ops.sleep;
		adap->fe[fe_id]->ops.sleep = mxl111sf_adap_fe_sleep;
		वापस 0;
	पूर्ण
	ret = -EIO;
fail:
	वापस ret;
पूर्ण

अटल काष्ठा lg2160_config hauppauge_lg2160_config = अणु
	.lg_chip            = LG2160,
	.i2c_addr           = 0x1c >> 1,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 0,
	.अगर_khz             = 6000,
पूर्ण;

अटल पूर्णांक mxl111sf_lg2160_frontend_attach(काष्ठा dvb_usb_adapter *adap, u8 fe_id)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा mxl111sf_state *state = d_to_priv(d);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe_id];
	पूर्णांक ret;

	pr_debug("%s()\n", __func__);

	/* save a poपूर्णांकer to the dvb_usb_device in device state */
	state->d = d;
	adap_state->alt_mode = (dvb_usb_mxl111sf_isoc) ? 2 : 1;
	state->alt_mode = adap_state->alt_mode;

	अगर (usb_set_पूर्णांकerface(d->udev, 0, state->alt_mode) < 0)
		pr_err("set interface failed");

	state->gpio_mode = MXL111SF_GPIO_MOD_MH;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXL_TUNER_MODE;
	adap_state->ep6_घड़ीphase = 1;

	ret = mxl1x1sf_soft_reset(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_init_tuner_demod(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl1x1sf_set_device_mode(state, adap_state->device_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_enable_usb_output(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_top_master_ctrl(state, 1);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_init_port_expander(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_gpio_mode_चयन(state, state->gpio_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = get_chip_info(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	adap->fe[fe_id] = dvb_attach(lg2160_attach,
			      &hauppauge_lg2160_config,
			      &d->i2c_adap);
	अगर (adap->fe[fe_id]) अणु
		state->num_frontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxl111sf_adap_fe_init;
		adap_state->fe_sleep = adap->fe[fe_id]->ops.sleep;
		adap->fe[fe_id]->ops.sleep = mxl111sf_adap_fe_sleep;
		वापस 0;
	पूर्ण
	ret = -EIO;
fail:
	वापस ret;
पूर्ण

अटल काष्ठा lg2160_config hauppauge_lg2161_1019_config = अणु
	.lg_chip            = LG2161_1019,
	.i2c_addr           = 0x1c >> 1,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 0,
	.अगर_khz             = 6000,
	.output_अगर          = 2, /* LG2161_OIF_SPI_MAS */
पूर्ण;

अटल काष्ठा lg2160_config hauppauge_lg2161_1040_config = अणु
	.lg_chip            = LG2161_1040,
	.i2c_addr           = 0x1c >> 1,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 0,
	.अगर_khz             = 6000,
	.output_अगर          = 4, /* LG2161_OIF_SPI_MAS */
पूर्ण;

अटल पूर्णांक mxl111sf_lg2161_frontend_attach(काष्ठा dvb_usb_adapter *adap, u8 fe_id)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा mxl111sf_state *state = d_to_priv(d);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe_id];
	पूर्णांक ret;

	pr_debug("%s()\n", __func__);

	/* save a poपूर्णांकer to the dvb_usb_device in device state */
	state->d = d;
	adap_state->alt_mode = (dvb_usb_mxl111sf_isoc) ? 2 : 1;
	state->alt_mode = adap_state->alt_mode;

	अगर (usb_set_पूर्णांकerface(d->udev, 0, state->alt_mode) < 0)
		pr_err("set interface failed");

	state->gpio_mode = MXL111SF_GPIO_MOD_MH;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXL_TUNER_MODE;
	adap_state->ep6_घड़ीphase = 1;

	ret = mxl1x1sf_soft_reset(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_init_tuner_demod(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl1x1sf_set_device_mode(state, adap_state->device_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_enable_usb_output(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_top_master_ctrl(state, 1);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_init_port_expander(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_gpio_mode_चयन(state, state->gpio_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = get_chip_info(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	adap->fe[fe_id] = dvb_attach(lg2160_attach,
			      (MXL111SF_V8_200 == state->chip_rev) ?
			      &hauppauge_lg2161_1040_config :
			      &hauppauge_lg2161_1019_config,
			      &d->i2c_adap);
	अगर (adap->fe[fe_id]) अणु
		state->num_frontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxl111sf_adap_fe_init;
		adap_state->fe_sleep = adap->fe[fe_id]->ops.sleep;
		adap->fe[fe_id]->ops.sleep = mxl111sf_adap_fe_sleep;
		वापस 0;
	पूर्ण
	ret = -EIO;
fail:
	वापस ret;
पूर्ण

अटल काष्ठा lg2160_config hauppauge_lg2161_1019_ep6_config = अणु
	.lg_chip            = LG2161_1019,
	.i2c_addr           = 0x1c >> 1,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 0,
	.अगर_khz             = 6000,
	.output_अगर          = 1, /* LG2161_OIF_SERIAL_TS */
पूर्ण;

अटल काष्ठा lg2160_config hauppauge_lg2161_1040_ep6_config = अणु
	.lg_chip            = LG2161_1040,
	.i2c_addr           = 0x1c >> 1,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 0,
	.अगर_khz             = 6000,
	.output_अगर          = 7, /* LG2161_OIF_SERIAL_TS */
पूर्ण;

अटल पूर्णांक mxl111sf_lg2161_ep6_frontend_attach(काष्ठा dvb_usb_adapter *adap, u8 fe_id)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा mxl111sf_state *state = d_to_priv(d);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe_id];
	पूर्णांक ret;

	pr_debug("%s()\n", __func__);

	/* save a poपूर्णांकer to the dvb_usb_device in device state */
	state->d = d;
	adap_state->alt_mode = (dvb_usb_mxl111sf_isoc) ? 2 : 1;
	state->alt_mode = adap_state->alt_mode;

	अगर (usb_set_पूर्णांकerface(d->udev, 0, state->alt_mode) < 0)
		pr_err("set interface failed");

	state->gpio_mode = MXL111SF_GPIO_MOD_MH;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXL_TUNER_MODE;
	adap_state->ep6_घड़ीphase = 0;

	ret = mxl1x1sf_soft_reset(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_init_tuner_demod(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl1x1sf_set_device_mode(state, adap_state->device_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_enable_usb_output(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_top_master_ctrl(state, 1);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_init_port_expander(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_gpio_mode_चयन(state, state->gpio_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = get_chip_info(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	adap->fe[fe_id] = dvb_attach(lg2160_attach,
			      (MXL111SF_V8_200 == state->chip_rev) ?
			      &hauppauge_lg2161_1040_ep6_config :
			      &hauppauge_lg2161_1019_ep6_config,
			      &d->i2c_adap);
	अगर (adap->fe[fe_id]) अणु
		state->num_frontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxl111sf_adap_fe_init;
		adap_state->fe_sleep = adap->fe[fe_id]->ops.sleep;
		adap->fe[fe_id]->ops.sleep = mxl111sf_adap_fe_sleep;
		वापस 0;
	पूर्ण
	ret = -EIO;
fail:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mxl111sf_demod_config mxl_demod_config = अणु
	.पढ़ो_reg        = mxl111sf_पढ़ो_reg,
	.ग_लिखो_reg       = mxl111sf_ग_लिखो_reg,
	.program_regs    = mxl111sf_ctrl_program_regs,
पूर्ण;

अटल पूर्णांक mxl111sf_attach_demod(काष्ठा dvb_usb_adapter *adap, u8 fe_id)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा mxl111sf_state *state = d_to_priv(d);
	काष्ठा mxl111sf_adap_state *adap_state = &state->adap_state[fe_id];
	पूर्णांक ret;

	pr_debug("%s()\n", __func__);

	/* save a poपूर्णांकer to the dvb_usb_device in device state */
	state->d = d;
	adap_state->alt_mode = (dvb_usb_mxl111sf_isoc) ? 1 : 2;
	state->alt_mode = adap_state->alt_mode;

	अगर (usb_set_पूर्णांकerface(d->udev, 0, state->alt_mode) < 0)
		pr_err("set interface failed");

	state->gpio_mode = MXL111SF_GPIO_MOD_DVBT;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXL_SOC_MODE;
	adap_state->ep6_घड़ीphase = 1;

	ret = mxl1x1sf_soft_reset(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_init_tuner_demod(state);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl1x1sf_set_device_mode(state, adap_state->device_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_enable_usb_output(state);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_top_master_ctrl(state, 1);
	अगर (mxl_fail(ret))
		जाओ fail;

	/* करोn't care अगर this fails */
	mxl111sf_init_port_expander(state);

	adap->fe[fe_id] = dvb_attach(mxl111sf_demod_attach, state,
			      &mxl_demod_config);
	अगर (adap->fe[fe_id]) अणु
		state->num_frontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxl111sf_adap_fe_init;
		adap_state->fe_sleep = adap->fe[fe_id]->ops.sleep;
		adap->fe[fe_id]->ops.sleep = mxl111sf_adap_fe_sleep;
		वापस 0;
	पूर्ण
	ret = -EIO;
fail:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक mxl111sf_set_ant_path(काष्ठा mxl111sf_state *state,
					पूर्णांक antpath)
अणु
	वापस mxl111sf_idac_config(state, 1, 1,
				    (antpath == ANT_PATH_INTERNAL) ?
				    0x3f : 0x00, 0);
पूर्ण

#घोषणा DbgAntHunt(x, pwr0, pwr1, pwr2, pwr3) \
	pr_err("%s(%d) FINAL input set to %s rxPwr:%d|%d|%d|%d\n", \
	    __func__, __LINE__, \
	    (ANT_PATH_EXTERNAL == x) ? "EXTERNAL" : "INTERNAL", \
	    pwr0, pwr1, pwr2, pwr3)

#घोषणा ANT_HUNT_SLEEP 90
#घोषणा ANT_EXT_TWEAK 0

अटल पूर्णांक mxl111sf_ant_hunt(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl111sf_state *state = fe_to_priv(fe);
	पूर्णांक antctrl = dvb_usb_mxl111sf_rfचयन;

	u16 rxPwrA, rxPwr0, rxPwr1, rxPwr2;

	/* FIXME: must क्रमce EXTERNAL क्रम QAM - करोne अन्यथाwhere */
	mxl111sf_set_ant_path(state, antctrl == ANT_PATH_AUTO ?
			      ANT_PATH_EXTERNAL : antctrl);

	अगर (antctrl == ANT_PATH_AUTO) अणु
#अगर 0
		msleep(ANT_HUNT_SLEEP);
#पूर्ण_अगर
		fe->ops.tuner_ops.get_rf_strength(fe, &rxPwrA);

		mxl111sf_set_ant_path(state, ANT_PATH_EXTERNAL);
		msleep(ANT_HUNT_SLEEP);
		fe->ops.tuner_ops.get_rf_strength(fe, &rxPwr0);

		mxl111sf_set_ant_path(state, ANT_PATH_EXTERNAL);
		msleep(ANT_HUNT_SLEEP);
		fe->ops.tuner_ops.get_rf_strength(fe, &rxPwr1);

		mxl111sf_set_ant_path(state, ANT_PATH_INTERNAL);
		msleep(ANT_HUNT_SLEEP);
		fe->ops.tuner_ops.get_rf_strength(fe, &rxPwr2);

		अगर (rxPwr1+ANT_EXT_TWEAK >= rxPwr2) अणु
			/* वापस with EXTERNAL enabled */
			mxl111sf_set_ant_path(state, ANT_PATH_EXTERNAL);
			DbgAntHunt(ANT_PATH_EXTERNAL, rxPwrA,
				   rxPwr0, rxPwr1, rxPwr2);
		पूर्ण अन्यथा अणु
			/* वापस with INTERNAL enabled */
			DbgAntHunt(ANT_PATH_INTERNAL, rxPwrA,
				   rxPwr0, rxPwr1, rxPwr2);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mxl111sf_tuner_config mxl_tuner_config = अणु
	.अगर_freq         = MXL_IF_6_0, /* applies to बाह्यal IF output, only */
	.invert_spectrum = 0,
	.पढ़ो_reg        = mxl111sf_पढ़ो_reg,
	.ग_लिखो_reg       = mxl111sf_ग_लिखो_reg,
	.program_regs    = mxl111sf_ctrl_program_regs,
	.top_master_ctrl = mxl1x1sf_top_master_ctrl,
	.ant_hunt        = mxl111sf_ant_hunt,
पूर्ण;

अटल पूर्णांक mxl111sf_attach_tuner(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा mxl111sf_state *state = adap_to_priv(adap);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	काष्ठा media_device *mdev = dvb_get_media_controller(&adap->dvb_adap);
	पूर्णांक ret;
#पूर्ण_अगर
	पूर्णांक i;

	pr_debug("%s()\n", __func__);

	क्रम (i = 0; i < state->num_frontends; i++) अणु
		अगर (dvb_attach(mxl111sf_tuner_attach, adap->fe[i], state,
				&mxl_tuner_config) == शून्य)
			वापस -EIO;
		adap->fe[i]->ops.पढ़ो_संकेत_strength = adap->fe[i]->ops.tuner_ops.get_rf_strength;
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	state->tuner.function = MEDIA_ENT_F_TUNER;
	state->tuner.name = "mxl111sf tuner";
	state->tuner_pads[MXL111SF_PAD_RF_INPUT].flags = MEDIA_PAD_FL_SINK;
	state->tuner_pads[MXL111SF_PAD_RF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
	state->tuner_pads[MXL111SF_PAD_OUTPUT].flags = MEDIA_PAD_FL_SOURCE;
	state->tuner_pads[MXL111SF_PAD_OUTPUT].sig_type = PAD_SIGNAL_ANALOG;

	ret = media_entity_pads_init(&state->tuner,
				     MXL111SF_NUM_PADS, state->tuner_pads);
	अगर (ret)
		वापस ret;

	ret = media_device_रेजिस्टर_entity(mdev, &state->tuner);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल u32 mxl111sf_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm mxl111sf_i2c_algo = अणु
	.master_xfer   = mxl111sf_i2c_xfer,
	.functionality = mxl111sf_i2c_func,
#अगर_घोषित NEED_ALGO_CONTROL
	.algo_control = dummy_algo_control,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mxl111sf_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा mxl111sf_state *state = d_to_priv(d);
	पूर्णांक ret;
	अटल u8 eeprom[256];
	u8 reg = 0;
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = 0xa0 >> 1, .len = 1, .buf = &reg पूर्ण,
		अणु .addr = 0xa0 >> 1, .flags = I2C_M_RD,
		  .len = माप(eeprom), .buf = eeprom पूर्ण,
	पूर्ण;

	mutex_init(&state->msg_lock);

	ret = get_chip_info(state);
	अगर (mxl_fail(ret))
		pr_err("failed to get chip info during probe");

	mutex_init(&state->fe_lock);

	अगर (state->chip_rev > MXL111SF_V6)
		mxl111sf_config_pin_mux_modes(state, PIN_MUX_TS_SPI_IN_MODE_1);

	ret = i2c_transfer(&d->i2c_adap, msg, 2);
	अगर (mxl_fail(ret))
		वापस 0;
	tveeprom_hauppauge_analog(&state->tv, (0x84 == eeprom[0xa0]) ?
				  eeprom + 0xa0 : eeprom + 0x80);
#अगर 0
	चयन (state->tv.model) अणु
	हाल 117001:
	हाल 126001:
	हाल 138001:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: warning: unknown hauppauge model #%d\n",
		       __func__, state->tv.model);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक mxl111sf_frontend_attach_dvbt(काष्ठा dvb_usb_adapter *adap)
अणु
	वापस mxl111sf_attach_demod(adap, 0);
पूर्ण

अटल पूर्णांक mxl111sf_frontend_attach_atsc(काष्ठा dvb_usb_adapter *adap)
अणु
	वापस mxl111sf_lgdt3305_frontend_attach(adap, 0);
पूर्ण

अटल पूर्णांक mxl111sf_frontend_attach_mh(काष्ठा dvb_usb_adapter *adap)
अणु
	वापस mxl111sf_lg2160_frontend_attach(adap, 0);
पूर्ण

अटल पूर्णांक mxl111sf_frontend_attach_atsc_mh(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	pr_debug("%s\n", __func__);

	ret = mxl111sf_lgdt3305_frontend_attach(adap, 0);
	अगर (ret < 0)
		वापस ret;

	ret = mxl111sf_attach_demod(adap, 1);
	अगर (ret < 0)
		वापस ret;

	ret = mxl111sf_lg2160_frontend_attach(adap, 2);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_frontend_attach_mercury(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	pr_debug("%s\n", __func__);

	ret = mxl111sf_lgdt3305_frontend_attach(adap, 0);
	अगर (ret < 0)
		वापस ret;

	ret = mxl111sf_attach_demod(adap, 1);
	अगर (ret < 0)
		वापस ret;

	ret = mxl111sf_lg2161_ep6_frontend_attach(adap, 2);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_frontend_attach_mercury_mh(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	pr_debug("%s\n", __func__);

	ret = mxl111sf_attach_demod(adap, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (dvb_usb_mxl111sf_spi)
		ret = mxl111sf_lg2161_frontend_attach(adap, 1);
	अन्यथा
		ret = mxl111sf_lg2161_ep6_frontend_attach(adap, 1);

	वापस ret;
पूर्ण

अटल व्योम mxl111sf_stream_config_bulk(काष्ठा usb_data_stream_properties *stream, u8 endpoपूर्णांक)
अणु
	pr_debug("%s: endpoint=%d size=8192\n", __func__, endpoपूर्णांक);
	stream->type = USB_BULK;
	stream->count = 5;
	stream->endpoपूर्णांक = endpoपूर्णांक;
	stream->u.bulk.buffersize = 8192;
पूर्ण

अटल व्योम mxl111sf_stream_config_isoc(काष्ठा usb_data_stream_properties *stream,
		u8 endpoपूर्णांक, पूर्णांक framesperurb, पूर्णांक framesize)
अणु
	pr_debug("%s: endpoint=%d size=%d\n", __func__, endpoपूर्णांक,
			framesperurb * framesize);
	stream->type = USB_ISOC;
	stream->count = 5;
	stream->endpoपूर्णांक = endpoपूर्णांक;
	stream->u.isoc.framesperurb = framesperurb;
	stream->u.isoc.framesize = framesize;
	stream->u.isoc.पूर्णांकerval = 1;
पूर्ण

/* DVB USB Driver stuff */

/* dvbt       mxl111sf
 * bulk       EP4/BULK/5/8192
 * isoc       EP4/ISOC/5/96/564
 */
अटल पूर्णांक mxl111sf_get_stream_config_dvbt(काष्ठा dvb_frontend *fe,
		u8 *ts_type, काष्ठा usb_data_stream_properties *stream)
अणु
	pr_debug("%s: fe=%d\n", __func__, fe->id);

	*ts_type = DVB_USB_FE_TS_TYPE_188;
	अगर (dvb_usb_mxl111sf_isoc)
		mxl111sf_stream_config_isoc(stream, 4, 96, 564);
	अन्यथा
		mxl111sf_stream_config_bulk(stream, 4);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties mxl111sf_props_dvbt = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा mxl111sf_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.i2c_algo          = &mxl111sf_i2c_algo,
	.frontend_attach   = mxl111sf_frontend_attach_dvbt,
	.tuner_attach      = mxl111sf_attach_tuner,
	.init              = mxl111sf_init,
	.streaming_ctrl    = mxl111sf_ep4_streaming_ctrl,
	.get_stream_config = mxl111sf_get_stream_config_dvbt,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_ISOC(6, 5, 24, 3072, 1),
		पूर्ण
	पूर्ण
पूर्ण;

/* atsc       lgdt3305
 * bulk       EP6/BULK/5/8192
 * isoc       EP6/ISOC/5/24/3072
 */
अटल पूर्णांक mxl111sf_get_stream_config_atsc(काष्ठा dvb_frontend *fe,
		u8 *ts_type, काष्ठा usb_data_stream_properties *stream)
अणु
	pr_debug("%s: fe=%d\n", __func__, fe->id);

	*ts_type = DVB_USB_FE_TS_TYPE_188;
	अगर (dvb_usb_mxl111sf_isoc)
		mxl111sf_stream_config_isoc(stream, 6, 24, 3072);
	अन्यथा
		mxl111sf_stream_config_bulk(stream, 6);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties mxl111sf_props_atsc = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा mxl111sf_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.i2c_algo          = &mxl111sf_i2c_algo,
	.frontend_attach   = mxl111sf_frontend_attach_atsc,
	.tuner_attach      = mxl111sf_attach_tuner,
	.init              = mxl111sf_init,
	.streaming_ctrl    = mxl111sf_ep6_streaming_ctrl,
	.get_stream_config = mxl111sf_get_stream_config_atsc,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_ISOC(6, 5, 24, 3072, 1),
		पूर्ण
	पूर्ण
पूर्ण;

/* mh         lg2160
 * bulk       EP5/BULK/5/8192/RAW
 * isoc       EP5/ISOC/5/96/200/RAW
 */
अटल पूर्णांक mxl111sf_get_stream_config_mh(काष्ठा dvb_frontend *fe,
		u8 *ts_type, काष्ठा usb_data_stream_properties *stream)
अणु
	pr_debug("%s: fe=%d\n", __func__, fe->id);

	*ts_type = DVB_USB_FE_TS_TYPE_RAW;
	अगर (dvb_usb_mxl111sf_isoc)
		mxl111sf_stream_config_isoc(stream, 5, 96, 200);
	अन्यथा
		mxl111sf_stream_config_bulk(stream, 5);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties mxl111sf_props_mh = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा mxl111sf_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.i2c_algo          = &mxl111sf_i2c_algo,
	.frontend_attach   = mxl111sf_frontend_attach_mh,
	.tuner_attach      = mxl111sf_attach_tuner,
	.init              = mxl111sf_init,
	.streaming_ctrl    = mxl111sf_ep5_streaming_ctrl,
	.get_stream_config = mxl111sf_get_stream_config_mh,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_ISOC(6, 5, 24, 3072, 1),
		पूर्ण
	पूर्ण
पूर्ण;

/* atsc mh    lgdt3305           mxl111sf          lg2160
 * bulk       EP6/BULK/5/8192    EP4/BULK/5/8192   EP5/BULK/5/8192/RAW
 * isoc       EP6/ISOC/5/24/3072 EP4/ISOC/5/96/564 EP5/ISOC/5/96/200/RAW
 */
अटल पूर्णांक mxl111sf_get_stream_config_atsc_mh(काष्ठा dvb_frontend *fe,
		u8 *ts_type, काष्ठा usb_data_stream_properties *stream)
अणु
	pr_debug("%s: fe=%d\n", __func__, fe->id);

	अगर (fe->id == 0) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 6, 24, 3072);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 6);
	पूर्ण अन्यथा अगर (fe->id == 1) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 4, 96, 564);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 4);
	पूर्ण अन्यथा अगर (fe->id == 2) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_RAW;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 5, 96, 200);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 5);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxl111sf_streaming_ctrl_atsc_mh(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	pr_debug("%s: fe=%d onoff=%d\n", __func__, fe->id, onoff);

	अगर (fe->id == 0)
		वापस mxl111sf_ep6_streaming_ctrl(fe, onoff);
	अन्यथा अगर (fe->id == 1)
		वापस mxl111sf_ep4_streaming_ctrl(fe, onoff);
	अन्यथा अगर (fe->id == 2)
		वापस mxl111sf_ep5_streaming_ctrl(fe, onoff);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties mxl111sf_props_atsc_mh = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा mxl111sf_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.i2c_algo          = &mxl111sf_i2c_algo,
	.frontend_attach   = mxl111sf_frontend_attach_atsc_mh,
	.tuner_attach      = mxl111sf_attach_tuner,
	.init              = mxl111sf_init,
	.streaming_ctrl    = mxl111sf_streaming_ctrl_atsc_mh,
	.get_stream_config = mxl111sf_get_stream_config_atsc_mh,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_ISOC(6, 5, 24, 3072, 1),
		पूर्ण
	पूर्ण
पूर्ण;

/* mercury    lgdt3305           mxl111sf          lg2161
 * tp bulk    EP6/BULK/5/8192    EP4/BULK/5/8192   EP6/BULK/5/8192/RAW
 * tp isoc    EP6/ISOC/5/24/3072 EP4/ISOC/5/96/564 EP6/ISOC/5/24/3072/RAW
 * spi bulk   EP6/BULK/5/8192    EP4/BULK/5/8192   EP5/BULK/5/8192/RAW
 * spi isoc   EP6/ISOC/5/24/3072 EP4/ISOC/5/96/564 EP5/ISOC/5/96/200/RAW
 */
अटल पूर्णांक mxl111sf_get_stream_config_mercury(काष्ठा dvb_frontend *fe,
		u8 *ts_type, काष्ठा usb_data_stream_properties *stream)
अणु
	pr_debug("%s: fe=%d\n", __func__, fe->id);

	अगर (fe->id == 0) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 6, 24, 3072);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 6);
	पूर्ण अन्यथा अगर (fe->id == 1) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 4, 96, 564);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 4);
	पूर्ण अन्यथा अगर (fe->id == 2 && dvb_usb_mxl111sf_spi) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_RAW;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 5, 96, 200);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 5);
	पूर्ण अन्यथा अगर (fe->id == 2 && !dvb_usb_mxl111sf_spi) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_RAW;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 6, 24, 3072);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 6);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxl111sf_streaming_ctrl_mercury(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	pr_debug("%s: fe=%d onoff=%d\n", __func__, fe->id, onoff);

	अगर (fe->id == 0)
		वापस mxl111sf_ep6_streaming_ctrl(fe, onoff);
	अन्यथा अगर (fe->id == 1)
		वापस mxl111sf_ep4_streaming_ctrl(fe, onoff);
	अन्यथा अगर (fe->id == 2 && dvb_usb_mxl111sf_spi)
		वापस mxl111sf_ep5_streaming_ctrl(fe, onoff);
	अन्यथा अगर (fe->id == 2 && !dvb_usb_mxl111sf_spi)
		वापस mxl111sf_ep6_streaming_ctrl(fe, onoff);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties mxl111sf_props_mercury = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा mxl111sf_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.i2c_algo          = &mxl111sf_i2c_algo,
	.frontend_attach   = mxl111sf_frontend_attach_mercury,
	.tuner_attach      = mxl111sf_attach_tuner,
	.init              = mxl111sf_init,
	.streaming_ctrl    = mxl111sf_streaming_ctrl_mercury,
	.get_stream_config = mxl111sf_get_stream_config_mercury,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_ISOC(6, 5, 24, 3072, 1),
		पूर्ण
	पूर्ण
पूर्ण;

/* mercury mh mxl111sf          lg2161
 * tp bulk    EP4/BULK/5/8192   EP6/BULK/5/8192/RAW
 * tp isoc    EP4/ISOC/5/96/564 EP6/ISOC/5/24/3072/RAW
 * spi bulk   EP4/BULK/5/8192   EP5/BULK/5/8192/RAW
 * spi isoc   EP4/ISOC/5/96/564 EP5/ISOC/5/96/200/RAW
 */
अटल पूर्णांक mxl111sf_get_stream_config_mercury_mh(काष्ठा dvb_frontend *fe,
		u8 *ts_type, काष्ठा usb_data_stream_properties *stream)
अणु
	pr_debug("%s: fe=%d\n", __func__, fe->id);

	अगर (fe->id == 0) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 4, 96, 564);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 4);
	पूर्ण अन्यथा अगर (fe->id == 1 && dvb_usb_mxl111sf_spi) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_RAW;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 5, 96, 200);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 5);
	पूर्ण अन्यथा अगर (fe->id == 1 && !dvb_usb_mxl111sf_spi) अणु
		*ts_type = DVB_USB_FE_TS_TYPE_RAW;
		अगर (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 6, 24, 3072);
		अन्यथा
			mxl111sf_stream_config_bulk(stream, 6);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxl111sf_streaming_ctrl_mercury_mh(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	pr_debug("%s: fe=%d onoff=%d\n", __func__, fe->id, onoff);

	अगर (fe->id == 0)
		वापस mxl111sf_ep4_streaming_ctrl(fe, onoff);
	अन्यथा अगर (fe->id == 1  && dvb_usb_mxl111sf_spi)
		वापस mxl111sf_ep5_streaming_ctrl(fe, onoff);
	अन्यथा अगर (fe->id == 1 && !dvb_usb_mxl111sf_spi)
		वापस mxl111sf_ep6_streaming_ctrl(fe, onoff);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties mxl111sf_props_mercury_mh = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा mxl111sf_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.i2c_algo          = &mxl111sf_i2c_algo,
	.frontend_attach   = mxl111sf_frontend_attach_mercury_mh,
	.tuner_attach      = mxl111sf_attach_tuner,
	.init              = mxl111sf_init,
	.streaming_ctrl    = mxl111sf_streaming_ctrl_mercury_mh,
	.get_stream_config = mxl111sf_get_stream_config_mercury_mh,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_ISOC(6, 5, 24, 3072, 1),
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id mxl111sf_id_table[] = अणु
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc600, &mxl111sf_props_atsc_mh, "Hauppauge 126xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc601, &mxl111sf_props_atsc, "Hauppauge 126xxx ATSC", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc602, &mxl111sf_props_mh, "HCW 126xxx", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc603, &mxl111sf_props_atsc_mh, "Hauppauge 126xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc604, &mxl111sf_props_dvbt, "Hauppauge 126xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc609, &mxl111sf_props_atsc, "Hauppauge 126xxx ATSC", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc60a, &mxl111sf_props_mh, "HCW 126xxx", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc60b, &mxl111sf_props_atsc_mh, "Hauppauge 126xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc60c, &mxl111sf_props_dvbt, "Hauppauge 126xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc653, &mxl111sf_props_atsc_mh, "Hauppauge 126xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc65b, &mxl111sf_props_atsc_mh, "Hauppauge 126xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb700, &mxl111sf_props_atsc_mh, "Hauppauge 117xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb701, &mxl111sf_props_atsc, "Hauppauge 126xxx ATSC", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb702, &mxl111sf_props_mh, "HCW 117xxx", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb703, &mxl111sf_props_atsc_mh, "Hauppauge 117xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb704, &mxl111sf_props_dvbt, "Hauppauge 117xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb753, &mxl111sf_props_atsc_mh, "Hauppauge 117xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb763, &mxl111sf_props_atsc_mh, "Hauppauge 117xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb764, &mxl111sf_props_dvbt, "Hauppauge 117xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd853, &mxl111sf_props_mercury, "Hauppauge Mercury", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd854, &mxl111sf_props_dvbt, "Hauppauge 138xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd863, &mxl111sf_props_mercury, "Hauppauge Mercury", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd864, &mxl111sf_props_dvbt, "Hauppauge 138xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8d3, &mxl111sf_props_mercury, "Hauppauge Mercury", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8d4, &mxl111sf_props_dvbt, "Hauppauge 138xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8e3, &mxl111sf_props_mercury, "Hauppauge Mercury", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8e4, &mxl111sf_props_dvbt, "Hauppauge 138xxx DVBT", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8ff, &mxl111sf_props_mercury, "Hauppauge Mercury", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc612, &mxl111sf_props_mercury_mh, "Hauppauge 126xxx", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc613, &mxl111sf_props_mercury, "Hauppauge WinTV-Aero-M", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc61a, &mxl111sf_props_mercury_mh, "Hauppauge 126xxx", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc61b, &mxl111sf_props_mercury, "Hauppauge WinTV-Aero-M", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb757, &mxl111sf_props_atsc_mh, "Hauppauge 117xxx ATSC+", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb767, &mxl111sf_props_atsc_mh, "Hauppauge 117xxx ATSC+", शून्य) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, mxl111sf_id_table);

अटल काष्ठा usb_driver mxl111sf_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = mxl111sf_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(mxl111sf_usb_driver);

MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_DESCRIPTION("Driver for MaxLinear MxL111SF");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
