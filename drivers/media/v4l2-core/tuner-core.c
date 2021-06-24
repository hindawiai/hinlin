<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2c tv tuner chip device driver
 * core core, i.e. kernel पूर्णांकerfaces, रेजिस्टरing and so on
 *
 * Copyright(c) by Ralph Metzler, Gerd Knorr, Gunther Mayer
 *
 * Copyright(c) 2005-2011 by Mauro Carvalho Chehab
 *	- Added support क्रम a separate Radio tuner
 *	- Major rework and cleanups at the code
 *
 * This driver supports many devices and the idea is to let the driver
 * detect which device is present. So rather than listing all supported
 * devices here, we pretend to support a single, fake device type that will
 * handle both radio and analog TV tuning.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/i2c.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/videodev2.h>
#समावेश <media/tuner.h>
#समावेश <media/tuner-types.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश "mt20xx.h"
#समावेश "tda8290.h"
#समावेश "tea5761.h"
#समावेश "tea5767.h"
#समावेश "tuner-xc2028.h"
#समावेश "tuner-simple.h"
#समावेश "tda9887.h"
#समावेश "xc5000.h"
#समावेश "tda18271.h"
#समावेश "xc4000.h"

#घोषणा UNSET (-1U)

/*
 * Driver modprobe parameters
 */

/* insmod options used at init समय => पढ़ो/only */
अटल अचिन्हित पूर्णांक addr;
अटल अचिन्हित पूर्णांक no_स्वतःdetect;
अटल अचिन्हित पूर्णांक show_i2c;

module_param(addr, पूर्णांक, 0444);
module_param(no_स्वतःdetect, पूर्णांक, 0444);
module_param(show_i2c, पूर्णांक, 0444);

/* insmod options used at runसमय => पढ़ो/ग_लिखो */
अटल पूर्णांक tuner_debug;
अटल अचिन्हित पूर्णांक tv_range[2] = अणु 44, 958 पूर्ण;
अटल अचिन्हित पूर्णांक radio_range[2] = अणु 65, 108 पूर्ण;
अटल अक्षर pal[] = "--";
अटल अक्षर secam[] = "--";
अटल अक्षर ntsc[] = "-";

module_param_named(debug, tuner_debug, पूर्णांक, 0644);
module_param_array(tv_range, पूर्णांक, शून्य, 0644);
module_param_array(radio_range, पूर्णांक, शून्य, 0644);
module_param_string(pal, pal, माप(pal), 0644);
module_param_string(secam, secam, माप(secam), 0644);
module_param_string(ntsc, ntsc, माप(ntsc), 0644);

/*
 * Static vars
 */

अटल LIST_HEAD(tuner_list);
अटल स्थिर काष्ठा v4l2_subdev_ops tuner_ops;

/*
 * Debug macros
 */

#अघोषित pr_fmt

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %d-%04x: " fmt,		\
	i2c_adapter_id(t->i2c->adapter), t->i2c->addr


#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (tuner_debug)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), __func__, ##arg);	\
पूर्ण जबतक (0)

/*
 * Internal क्रमागतs/काष्ठा used inside the driver
 */

/**
 * क्रमागत tuner_pad_index - tuner pad index क्रम MEDIA_ENT_F_TUNER
 *
 * @TUNER_PAD_RF_INPUT:
 *	Radiofrequency (RF) sink pad, usually linked to a RF connector entity.
 * @TUNER_PAD_OUTPUT:
 *	tuner video output source pad. Contains the video chrominance
 *	and luminance or the hole bandwidth of the संकेत converted to
 *	an Intermediate Frequency (IF) or to baseband (on zero-IF tuners).
 * @TUNER_PAD_AUD_OUT:
 *	Tuner audio output source pad. Tuners used to decode analog TV
 *	संकेतs have an extra pad क्रम audio output. Old tuners use an
 *	analog stage with a saw filter क्रम the audio IF frequency. The
 *	output of the pad is, in this हाल, the audio IF, with should be
 *	decoded either by the bridge chipset (that's the हाल of cx2388x
 *	chipsets) or may require an बाह्यal IF sound processor, like
 *	msp34xx. On modern silicon tuners, the audio IF decoder is usually
 *	incorporated at the tuner. On such हाल, the output of this pad
 *	is an audio sampled data.
 * @TUNER_NUM_PADS:
 *	Number of pads of the tuner.
 */
क्रमागत tuner_pad_index अणु
	TUNER_PAD_RF_INPUT,
	TUNER_PAD_OUTPUT,
	TUNER_PAD_AUD_OUT,
	TUNER_NUM_PADS
पूर्ण;

/**
 * क्रमागत अगर_vid_dec_pad_index - video IF-PLL pad index
 *	क्रम MEDIA_ENT_F_IF_VID_DECODER
 *
 * @IF_VID_DEC_PAD_IF_INPUT:
 *	video Intermediate Frequency (IF) sink pad
 * @IF_VID_DEC_PAD_OUT:
 *	IF-PLL video output source pad. Contains the video chrominance
 *	and luminance IF संकेतs.
 * @IF_VID_DEC_PAD_NUM_PADS:
 *	Number of pads of the video IF-PLL.
 */
क्रमागत अगर_vid_dec_pad_index अणु
	IF_VID_DEC_PAD_IF_INPUT,
	IF_VID_DEC_PAD_OUT,
	IF_VID_DEC_PAD_NUM_PADS
पूर्ण;

काष्ठा tuner अणु
	/* device */
	काष्ठा dvb_frontend fe;
	काष्ठा i2c_client   *i2c;
	काष्ठा v4l2_subdev  sd;
	काष्ठा list_head    list;

	/* keep track of the current settings */
	v4l2_std_id         std;
	अचिन्हित पूर्णांक        tv_freq;
	अचिन्हित पूर्णांक        radio_freq;
	अचिन्हित पूर्णांक        audmode;

	क्रमागत v4l2_tuner_type mode;
	अचिन्हित पूर्णांक        mode_mask; /* Combination of allowable modes */

	bool                standby;	/* Standby mode */

	अचिन्हित पूर्णांक        type; /* chip type id */
	व्योम                *config;
	स्थिर अक्षर          *name;

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_pad	pad[TUNER_NUM_PADS];
#पूर्ण_अगर
पूर्ण;

/*
 * Function prototypes
 */

अटल व्योम set_tv_freq(काष्ठा i2c_client *c, अचिन्हित पूर्णांक freq);
अटल व्योम set_radio_freq(काष्ठा i2c_client *c, अचिन्हित पूर्णांक freq);

/*
 * tuner attach/detach logic
 */

/* This macro allows us to probe dynamically, aव्योमing अटल links */
#अगर_घोषित CONFIG_MEDIA_ATTACH
#घोषणा tuner_symbol_probe(FUNCTION, ARGS...) (अणु \
	पूर्णांक __r = -EINVAL; \
	typeof(&FUNCTION) __a = symbol_request(FUNCTION); \
	अगर (__a) अणु \
		__r = (पूर्णांक) __a(ARGS); \
		symbol_put(FUNCTION); \
	पूर्ण अन्यथा अणु \
		prपूर्णांकk(KERN_ERR "TUNER: Unable to find " \
				"symbol "#FUNCTION"()\n"); \
	पूर्ण \
	__r; \
पूर्ण)

अटल व्योम tuner_detach(काष्ठा dvb_frontend *fe)
अणु
	अगर (fe->ops.tuner_ops.release) अणु
		fe->ops.tuner_ops.release(fe);
		symbol_put_addr(fe->ops.tuner_ops.release);
	पूर्ण
	अगर (fe->ops.analog_ops.release) अणु
		fe->ops.analog_ops.release(fe);
		symbol_put_addr(fe->ops.analog_ops.release);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा tuner_symbol_probe(FUNCTION, ARGS...) (अणु \
	FUNCTION(ARGS); \
पूर्ण)

अटल व्योम tuner_detach(काष्ठा dvb_frontend *fe)
अणु
	अगर (fe->ops.tuner_ops.release)
		fe->ops.tuner_ops.release(fe);
	अगर (fe->ops.analog_ops.release)
		fe->ops.analog_ops.release(fe);
पूर्ण
#पूर्ण_अगर


अटल अंतरभूत काष्ठा tuner *to_tuner(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tuner, sd);
पूर्ण

/*
 * काष्ठा analog_demod_ops callbacks
 */

अटल व्योम fe_set_params(काष्ठा dvb_frontend *fe,
			  काष्ठा analog_parameters *params)
अणु
	काष्ठा dvb_tuner_ops *fe_tuner_ops = &fe->ops.tuner_ops;
	काष्ठा tuner *t = fe->analog_demod_priv;

	अगर (शून्य == fe_tuner_ops->set_analog_params) अणु
		pr_warn("Tuner frontend module has no way to set freq\n");
		वापस;
	पूर्ण
	fe_tuner_ops->set_analog_params(fe, params);
पूर्ण

अटल व्योम fe_standby(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_tuner_ops *fe_tuner_ops = &fe->ops.tuner_ops;

	अगर (fe_tuner_ops->sleep)
		fe_tuner_ops->sleep(fe);
पूर्ण

अटल पूर्णांक fe_set_config(काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा dvb_tuner_ops *fe_tuner_ops = &fe->ops.tuner_ops;
	काष्ठा tuner *t = fe->analog_demod_priv;

	अगर (fe_tuner_ops->set_config)
		वापस fe_tuner_ops->set_config(fe, priv_cfg);

	pr_warn("Tuner frontend module has no way to set config\n");

	वापस 0;
पूर्ण

अटल व्योम tuner_status(काष्ठा dvb_frontend *fe);

अटल स्थिर काष्ठा analog_demod_ops tuner_analog_ops = अणु
	.set_params     = fe_set_params,
	.standby        = fe_standby,
	.set_config     = fe_set_config,
	.tuner_status   = tuner_status
पूर्ण;

/*
 * Functions to select between radio and TV and tuner probe/हटाओ functions
 */

/**
 * set_type - Sets the tuner type क्रम a given device
 *
 * @c:			i2c_client descriptor
 * @type:		type of the tuner (e. g. tuner number)
 * @new_mode_mask:	Indicates अगर tuner supports TV and/or Radio
 * @new_config:		an optional parameter used by a few tuners to adjust
 *			पूर्णांकernal parameters, like LNA mode
 * @tuner_callback:	an optional function to be called when चयनing
 *			to analog mode
 *
 * This function applies the tuner config to tuner specअगरied
 * by tun_setup काष्ठाure. It contains several per-tuner initialization "magic"
 */
अटल व्योम set_type(काष्ठा i2c_client *c, अचिन्हित पूर्णांक type,
		     अचिन्हित पूर्णांक new_mode_mask, व्योम *new_config,
		     पूर्णांक (*tuner_callback) (व्योम *dev, पूर्णांक component, पूर्णांक cmd, पूर्णांक arg))
अणु
	काष्ठा tuner *t = to_tuner(i2c_get_clientdata(c));
	काष्ठा dvb_tuner_ops *fe_tuner_ops = &t->fe.ops.tuner_ops;
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;
	अचिन्हित अक्षर buffer[4];
	पूर्णांक tune_now = 1;

	अगर (type == UNSET || type == TUNER_ABSENT) अणु
		dprपूर्णांकk("tuner 0x%02x: Tuner type absent\n", c->addr);
		वापस;
	पूर्ण

	t->type = type;
	t->config = new_config;
	अगर (tuner_callback != शून्य) अणु
		dprपूर्णांकk("defining GPIO callback\n");
		t->fe.callback = tuner_callback;
	पूर्ण

	/* discard निजी data, in हाल set_type() was previously called */
	tuner_detach(&t->fe);
	t->fe.analog_demod_priv = शून्य;

	चयन (t->type) अणु
	हाल TUNER_MT2032:
		अगर (!dvb_attach(microtune_attach,
			   &t->fe, t->i2c->adapter, t->i2c->addr))
			जाओ attach_failed;
		अवरोध;
	हाल TUNER_PHILIPS_TDA8290:
	अणु
		अगर (!dvb_attach(tda829x_attach, &t->fe, t->i2c->adapter,
				t->i2c->addr, t->config))
			जाओ attach_failed;
		अवरोध;
	पूर्ण
	हाल TUNER_TEA5767:
		अगर (!dvb_attach(tea5767_attach, &t->fe,
				t->i2c->adapter, t->i2c->addr))
			जाओ attach_failed;
		t->mode_mask = T_RADIO;
		अवरोध;
	हाल TUNER_TEA5761:
		अगर (!dvb_attach(tea5761_attach, &t->fe,
				t->i2c->adapter, t->i2c->addr))
			जाओ attach_failed;
		t->mode_mask = T_RADIO;
		अवरोध;
	हाल TUNER_PHILIPS_FMD1216ME_MK3:
	हाल TUNER_PHILIPS_FMD1216MEX_MK3:
		buffer[0] = 0x0b;
		buffer[1] = 0xdc;
		buffer[2] = 0x9c;
		buffer[3] = 0x60;
		i2c_master_send(c, buffer, 4);
		mdelay(1);
		buffer[2] = 0x86;
		buffer[3] = 0x54;
		i2c_master_send(c, buffer, 4);
		अगर (!dvb_attach(simple_tuner_attach, &t->fe,
				t->i2c->adapter, t->i2c->addr, t->type))
			जाओ attach_failed;
		अवरोध;
	हाल TUNER_PHILIPS_TD1316:
		buffer[0] = 0x0b;
		buffer[1] = 0xdc;
		buffer[2] = 0x86;
		buffer[3] = 0xa4;
		i2c_master_send(c, buffer, 4);
		अगर (!dvb_attach(simple_tuner_attach, &t->fe,
				t->i2c->adapter, t->i2c->addr, t->type))
			जाओ attach_failed;
		अवरोध;
	हाल TUNER_XC2028:
	अणु
		काष्ठा xc2028_config cfg = अणु
			.i2c_adap  = t->i2c->adapter,
			.i2c_addr  = t->i2c->addr,
		पूर्ण;
		अगर (!dvb_attach(xc2028_attach, &t->fe, &cfg))
			जाओ attach_failed;
		tune_now = 0;
		अवरोध;
	पूर्ण
	हाल TUNER_TDA9887:
		अगर (!dvb_attach(tda9887_attach,
			   &t->fe, t->i2c->adapter, t->i2c->addr))
			जाओ attach_failed;
		अवरोध;
	हाल TUNER_XC5000:
	अणु
		काष्ठा xc5000_config xc5000_cfg = अणु
			.i2c_address = t->i2c->addr,
			/* अगर_khz will be set at dvb_attach() */
			.अगर_khz	  = 0,
		पूर्ण;

		अगर (!dvb_attach(xc5000_attach,
				&t->fe, t->i2c->adapter, &xc5000_cfg))
			जाओ attach_failed;
		tune_now = 0;
		अवरोध;
	पूर्ण
	हाल TUNER_XC5000C:
	अणु
		काष्ठा xc5000_config xc5000c_cfg = अणु
			.i2c_address = t->i2c->addr,
			/* अगर_khz will be set at dvb_attach() */
			.अगर_khz	  = 0,
			.chip_id  = XC5000C,
		पूर्ण;

		अगर (!dvb_attach(xc5000_attach,
				&t->fe, t->i2c->adapter, &xc5000c_cfg))
			जाओ attach_failed;
		tune_now = 0;
		अवरोध;
	पूर्ण
	हाल TUNER_NXP_TDA18271:
	अणु
		काष्ठा tda18271_config cfg = अणु
			.small_i2c = TDA18271_03_BYTE_CHUNK_INIT,
		पूर्ण;

		अगर (!dvb_attach(tda18271_attach, &t->fe, t->i2c->addr,
				t->i2c->adapter, &cfg))
			जाओ attach_failed;
		tune_now = 0;
		अवरोध;
	पूर्ण
	हाल TUNER_XC4000:
	अणु
		काष्ठा xc4000_config xc4000_cfg = अणु
			.i2c_address	  = t->i2c->addr,
			/* FIXME: the correct parameters will be set */
			/* only when the digital dvb_attach() occurs */
			.शेष_pm	  = 0,
			.dvb_amplitude	  = 0,
			.set_smoothedcvbs = 0,
			.अगर_khz		  = 0
		पूर्ण;
		अगर (!dvb_attach(xc4000_attach,
				&t->fe, t->i2c->adapter, &xc4000_cfg))
			जाओ attach_failed;
		tune_now = 0;
		अवरोध;
	पूर्ण
	शेष:
		अगर (!dvb_attach(simple_tuner_attach, &t->fe,
				t->i2c->adapter, t->i2c->addr, t->type))
			जाओ attach_failed;

		अवरोध;
	पूर्ण

	अगर ((शून्य == analog_ops->set_params) &&
	    (fe_tuner_ops->set_analog_params)) अणु

		t->name = fe_tuner_ops->info.name;

		t->fe.analog_demod_priv = t;
		स_नकल(analog_ops, &tuner_analog_ops,
		       माप(काष्ठा analog_demod_ops));

		अगर (fe_tuner_ops->get_rf_strength)
			analog_ops->has_संकेत = fe_tuner_ops->get_rf_strength;
		अगर (fe_tuner_ops->get_afc)
			analog_ops->get_afc = fe_tuner_ops->get_afc;

	पूर्ण अन्यथा अणु
		t->name = analog_ops->info.name;
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	t->sd.entity.name = t->name;
#पूर्ण_अगर

	dprपूर्णांकk("type set to %s\n", t->name);

	t->mode_mask = new_mode_mask;

	/* Some tuners require more initialization setup beक्रमe use,
	   such as firmware करोwnload or device calibration.
	   trying to set a frequency here will just fail
	   FIXME: better to move set_freq to the tuner code. This is needed
	   on analog tuners क्रम PLL to properly work
	 */
	अगर (tune_now) अणु
		अगर (V4L2_TUNER_RADIO == t->mode)
			set_radio_freq(c, t->radio_freq);
		अन्यथा
			set_tv_freq(c, t->tv_freq);
	पूर्ण

	dprपूर्णांकk("%s %s I2C addr 0x%02x with type %d used for 0x%02x\n",
		  c->adapter->name, c->dev.driver->name, c->addr << 1, type,
		  t->mode_mask);
	वापस;

attach_failed:
	dprपूर्णांकk("Tuner attach for type = %d failed.\n", t->type);
	t->type = TUNER_ABSENT;

	वापस;
पूर्ण

/**
 * tuner_s_type_addr - Sets the tuner type क्रम a device
 *
 * @sd:		subdev descriptor
 * @tun_setup:	type to be associated to a given tuner i2c address
 *
 * This function applies the tuner config to tuner specअगरied
 * by tun_setup काष्ठाure.
 * If tuner I2C address is UNSET, then it will only set the device
 * अगर the tuner supports the mode specअगरied in the call.
 * If the address is specअगरied, the change will be applied only अगर
 * tuner I2C address matches.
 * The call can change the tuner number and the tuner mode.
 */
अटल पूर्णांक tuner_s_type_addr(काष्ठा v4l2_subdev *sd,
			     काष्ठा tuner_setup *tun_setup)
अणु
	काष्ठा tuner *t = to_tuner(sd);
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);

	dprपूर्णांकk("Calling set_type_addr for type=%d, addr=0x%02x, mode=0x%02x, config=%p\n",
			tun_setup->type,
			tun_setup->addr,
			tun_setup->mode_mask,
			tun_setup->config);

	अगर ((t->type == UNSET && ((tun_setup->addr == ADDR_UNSET) &&
	    (t->mode_mask & tun_setup->mode_mask))) ||
	    (tun_setup->addr == c->addr)) अणु
		set_type(c, tun_setup->type, tun_setup->mode_mask,
			 tun_setup->config, tun_setup->tuner_callback);
	पूर्ण अन्यथा
		dprपूर्णांकk("set addr discarded for type %i, mask %x. Asked to change tuner at addr 0x%02x, with mask %x\n",
			  t->type, t->mode_mask,
			  tun_setup->addr, tun_setup->mode_mask);

	वापस 0;
पूर्ण

/**
 * tuner_s_config - Sets tuner configuration
 *
 * @sd:		subdev descriptor
 * @cfg:	tuner configuration
 *
 * Calls tuner set_config() निजी function to set some tuner-पूर्णांकernal
 * parameters
 */
अटल पूर्णांक tuner_s_config(काष्ठा v4l2_subdev *sd,
			  स्थिर काष्ठा v4l2_priv_tun_config *cfg)
अणु
	काष्ठा tuner *t = to_tuner(sd);
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	अगर (t->type != cfg->tuner)
		वापस 0;

	अगर (analog_ops->set_config) अणु
		analog_ops->set_config(&t->fe, cfg->priv);
		वापस 0;
	पूर्ण

	dprपूर्णांकk("Tuner frontend module has no way to set config\n");
	वापस 0;
पूर्ण

/**
 * tuner_lookup - Seek क्रम tuner adapters
 *
 * @adap:	i2c_adapter काष्ठा
 * @radio:	poपूर्णांकer to be filled अगर the adapter is radio
 * @tv:		poपूर्णांकer to be filled अगर the adapter is TV
 *
 * Search क्रम existing radio and/or TV tuners on the given I2C adapter,
 * discarding demod-only adapters (tda9887).
 *
 * Note that when this function is called from tuner_probe you can be
 * certain no other devices will be added/deleted at the same समय, I2C
 * core protects against that.
 */
अटल व्योम tuner_lookup(काष्ठा i2c_adapter *adap,
		काष्ठा tuner **radio, काष्ठा tuner **tv)
अणु
	काष्ठा tuner *pos;

	*radio = शून्य;
	*tv = शून्य;

	list_क्रम_each_entry(pos, &tuner_list, list) अणु
		पूर्णांक mode_mask;

		अगर (pos->i2c->adapter != adap ||
		    म_भेद(pos->i2c->dev.driver->name, "tuner"))
			जारी;

		mode_mask = pos->mode_mask;
		अगर (*radio == शून्य && mode_mask == T_RADIO)
			*radio = pos;
		/* Note: currently TDA9887 is the only demod-only
		   device. If other devices appear then we need to
		   make this test more general. */
		अन्यथा अगर (*tv == शून्य && pos->type != TUNER_TDA9887 &&
			 (pos->mode_mask & T_ANALOG_TV))
			*tv = pos;
	पूर्ण
पूर्ण

/**
 *tuner_probe - Probes the existing tuners on an I2C bus
 *
 * @client:	i2c_client descriptor
 * @id:		not used
 *
 * This routine probes क्रम tuners at the expected I2C addresses. On most
 * हालs, अगर a device answers to a given I2C address, it assumes that the
 * device is a tuner. On a few हालs, however, an additional logic is needed
 * to द्विगुन check अगर the device is really a tuner, or to identअगरy the tuner
 * type, like on tea5767/5761 devices.
 *
 * During client attach, set_type is called by adapter's attach_inक्रमm callback.
 * set_type must then be completed by tuner_probe.
 */
अटल पूर्णांक tuner_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tuner *t;
	काष्ठा tuner *radio;
	काष्ठा tuner *tv;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक ret;
#पूर्ण_अगर

	t = kzalloc(माप(काष्ठा tuner), GFP_KERNEL);
	अगर (शून्य == t)
		वापस -ENOMEM;
	v4l2_i2c_subdev_init(&t->sd, client, &tuner_ops);
	t->i2c = client;
	t->name = "(tuner unset)";
	t->type = UNSET;
	t->audmode = V4L2_TUNER_MODE_STEREO;
	t->standby = true;
	t->radio_freq = 87.5 * 16000;	/* Initial freq range */
	t->tv_freq = 400 * 16; /* Sets freq to VHF High - needed क्रम some PLL's to properly start */

	अगर (show_i2c) अणु
		अचिन्हित अक्षर buffer[16];
		पूर्णांक rc;

		स_रखो(buffer, 0, माप(buffer));
		rc = i2c_master_recv(client, buffer, माप(buffer));
		अगर (rc >= 0)
			pr_info("I2C RECV = %*ph\n", rc, buffer);
	पूर्ण

	/* स्वतःdetection code based on the i2c addr */
	अगर (!no_स्वतःdetect) अणु
		चयन (client->addr) अणु
		हाल 0x10:
			अगर (tuner_symbol_probe(tea5761_स्वतःdetection,
					       t->i2c->adapter,
					       t->i2c->addr) >= 0) अणु
				t->type = TUNER_TEA5761;
				t->mode_mask = T_RADIO;
				tuner_lookup(t->i2c->adapter, &radio, &tv);
				अगर (tv)
					tv->mode_mask &= ~T_RADIO;

				जाओ रेजिस्टर_client;
			पूर्ण
			kमुक्त(t);
			वापस -ENODEV;
		हाल 0x42:
		हाल 0x43:
		हाल 0x4a:
		हाल 0x4b:
			/* If chip is not tda8290, करोn't रेजिस्टर.
			   since it can be tda9887*/
			अगर (tuner_symbol_probe(tda829x_probe, t->i2c->adapter,
					       t->i2c->addr) >= 0) अणु
				dprपूर्णांकk("tda829x detected\n");
			पूर्ण अन्यथा अणु
				/* Default is being tda9887 */
				t->type = TUNER_TDA9887;
				t->mode_mask = T_RADIO | T_ANALOG_TV;
				जाओ रेजिस्टर_client;
			पूर्ण
			अवरोध;
		हाल 0x60:
			अगर (tuner_symbol_probe(tea5767_स्वतःdetection,
					       t->i2c->adapter, t->i2c->addr)
					>= 0) अणु
				t->type = TUNER_TEA5767;
				t->mode_mask = T_RADIO;
				/* Sets freq to FM range */
				tuner_lookup(t->i2c->adapter, &radio, &tv);
				अगर (tv)
					tv->mode_mask &= ~T_RADIO;

				जाओ रेजिस्टर_client;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* Initializes only the first TV tuner on this adapter. Why only the
	   first? Because there are some devices (notably the ones with TI
	   tuners) that have more than one i2c address क्रम the *same* device.
	   Experience shows that, except क्रम just one हाल, the first
	   address is the right one. The exception is a Russian tuner
	   (ACORP_Y878F). So, the desired behavior is just to enable the
	   first found TV tuner. */
	tuner_lookup(t->i2c->adapter, &radio, &tv);
	अगर (tv == शून्य) अणु
		t->mode_mask = T_ANALOG_TV;
		अगर (radio == शून्य)
			t->mode_mask |= T_RADIO;
		dprपूर्णांकk("Setting mode_mask to 0x%02x\n", t->mode_mask);
	पूर्ण

	/* Should be just beक्रमe वापस */
रेजिस्टर_client:
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	t->sd.entity.name = t->name;
	/*
	 * Handle the special हाल where the tuner has actually
	 * two stages: the PLL to tune पूर्णांकo a frequency and the
	 * IF-PLL demodulator (tda988x).
	 */
	अगर (t->type == TUNER_TDA9887) अणु
		t->pad[IF_VID_DEC_PAD_IF_INPUT].flags = MEDIA_PAD_FL_SINK;
		t->pad[IF_VID_DEC_PAD_IF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
		t->pad[IF_VID_DEC_PAD_OUT].flags = MEDIA_PAD_FL_SOURCE;
		t->pad[IF_VID_DEC_PAD_OUT].sig_type = PAD_SIGNAL_ANALOG;
		ret = media_entity_pads_init(&t->sd.entity,
					     IF_VID_DEC_PAD_NUM_PADS,
					     &t->pad[0]);
		t->sd.entity.function = MEDIA_ENT_F_IF_VID_DECODER;
	पूर्ण अन्यथा अणु
		t->pad[TUNER_PAD_RF_INPUT].flags = MEDIA_PAD_FL_SINK;
		t->pad[TUNER_PAD_RF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
		t->pad[TUNER_PAD_OUTPUT].flags = MEDIA_PAD_FL_SOURCE;
		t->pad[TUNER_PAD_OUTPUT].sig_type = PAD_SIGNAL_ANALOG;
		t->pad[TUNER_PAD_AUD_OUT].flags = MEDIA_PAD_FL_SOURCE;
		t->pad[TUNER_PAD_AUD_OUT].sig_type = PAD_SIGNAL_AUDIO;
		ret = media_entity_pads_init(&t->sd.entity, TUNER_NUM_PADS,
					     &t->pad[0]);
		t->sd.entity.function = MEDIA_ENT_F_TUNER;
	पूर्ण

	अगर (ret < 0) अणु
		pr_err("failed to initialize media entity!\n");
		kमुक्त(t);
		वापस ret;
	पूर्ण
#पूर्ण_अगर
	/* Sets a शेष mode */
	अगर (t->mode_mask & T_ANALOG_TV)
		t->mode = V4L2_TUNER_ANALOG_TV;
	अन्यथा
		t->mode = V4L2_TUNER_RADIO;
	set_type(client, t->type, t->mode_mask, t->config, t->fe.callback);
	list_add_tail(&t->list, &tuner_list);

	pr_info("Tuner %d found with type(s)%s%s.\n",
		   t->type,
		   t->mode_mask & T_RADIO ? " Radio" : "",
		   t->mode_mask & T_ANALOG_TV ? " TV" : "");
	वापस 0;
पूर्ण

/**
 * tuner_हटाओ - detaches a tuner
 *
 * @client:	i2c_client descriptor
 */

अटल पूर्णांक tuner_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tuner *t = to_tuner(i2c_get_clientdata(client));

	v4l2_device_unरेजिस्टर_subdev(&t->sd);
	tuner_detach(&t->fe);
	t->fe.analog_demod_priv = शून्य;

	list_del(&t->list);
	kमुक्त(t);
	वापस 0;
पूर्ण

/*
 * Functions to चयन between Radio and TV
 *
 * A few cards have a separate I2C tuner क्रम radio. Those routines
 * take care of चयनing between TV/Radio mode, filtering only the
 * commands that apply to the Radio or TV tuner.
 */

/**
 * check_mode - Verअगरy अगर tuner supports the requested mode
 * @t: a poपूर्णांकer to the module's पूर्णांकernal काष्ठा_tuner
 * @mode: mode of the tuner, as defined by &क्रमागत v4l2_tuner_type.
 *
 * This function checks अगर the tuner is capable of tuning analog TV,
 * digital TV or radio, depending on what the caller wants. If the
 * tuner can't support that mode, it वापसs -EINVAL. Otherwise, it
 * वापसs 0.
 * This function is needed क्रम boards that have a separate tuner क्रम
 * radio (like devices with tea5767).
 *
 * NOTE: mt20xx uses V4L2_TUNER_DIGITAL_TV and calls set_tv_freq to
 *       select a TV frequency. So, t_mode = T_ANALOG_TV could actually
 *	 be used to represent a Digital TV too.
 */
अटल अंतरभूत पूर्णांक check_mode(काष्ठा tuner *t, क्रमागत v4l2_tuner_type mode)
अणु
	पूर्णांक t_mode;
	अगर (mode == V4L2_TUNER_RADIO)
		t_mode = T_RADIO;
	अन्यथा
		t_mode = T_ANALOG_TV;

	अगर ((t_mode & t->mode_mask) == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * set_mode - Switch tuner to other mode.
 * @t:		a poपूर्णांकer to the module's पूर्णांकernal काष्ठा_tuner
 * @mode:	क्रमागत v4l2_type (radio or TV)
 *
 * If tuner करोesn't support the needed mode (radio or TV), prपूर्णांकs a
 * debug message and वापसs -EINVAL, changing its state to standby.
 * Otherwise, changes the mode and वापसs 0.
 */
अटल पूर्णांक set_mode(काष्ठा tuner *t, क्रमागत v4l2_tuner_type mode)
अणु
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	अगर (mode != t->mode) अणु
		अगर (check_mode(t, mode) == -EINVAL) अणु
			dprपूर्णांकk("Tuner doesn't support mode %d. Putting tuner to sleep\n",
				  mode);
			t->standby = true;
			अगर (analog_ops->standby)
				analog_ops->standby(&t->fe);
			वापस -EINVAL;
		पूर्ण
		t->mode = mode;
		dprपूर्णांकk("Changing to mode %d\n", mode);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * set_freq - Set the tuner to the desired frequency.
 * @t:		a poपूर्णांकer to the module's पूर्णांकernal काष्ठा_tuner
 * @freq:	frequency to set (0 means to use the current frequency)
 */
अटल व्योम set_freq(काष्ठा tuner *t, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&t->sd);

	अगर (t->mode == V4L2_TUNER_RADIO) अणु
		अगर (!freq)
			freq = t->radio_freq;
		set_radio_freq(client, freq);
	पूर्ण अन्यथा अणु
		अगर (!freq)
			freq = t->tv_freq;
		set_tv_freq(client, freq);
	पूर्ण
पूर्ण

/*
 * Functions that are specअगरic क्रम TV mode
 */

/**
 * set_tv_freq - Set tuner frequency,  freq in Units of 62.5 kHz = 1/16MHz
 *
 * @c:	i2c_client descriptor
 * @freq: frequency
 */
अटल व्योम set_tv_freq(काष्ठा i2c_client *c, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा tuner *t = to_tuner(i2c_get_clientdata(c));
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	काष्ठा analog_parameters params = अणु
		.mode      = t->mode,
		.audmode   = t->audmode,
		.std       = t->std
	पूर्ण;

	अगर (t->type == UNSET) अणु
		pr_warn("tuner type not set\n");
		वापस;
	पूर्ण
	अगर (शून्य == analog_ops->set_params) अणु
		pr_warn("Tuner has no way to set tv freq\n");
		वापस;
	पूर्ण
	अगर (freq < tv_range[0] * 16 || freq > tv_range[1] * 16) अणु
		dprपूर्णांकk("TV freq (%d.%02d) out of range (%d-%d)\n",
			   freq / 16, freq % 16 * 100 / 16, tv_range[0],
			   tv_range[1]);
		/* V4L2 spec: अगर the freq is not possible then the बंदst
		   possible value should be selected */
		अगर (freq < tv_range[0] * 16)
			freq = tv_range[0] * 16;
		अन्यथा
			freq = tv_range[1] * 16;
	पूर्ण
	params.frequency = freq;
	dprपूर्णांकk("tv freq set to %d.%02d\n",
			freq / 16, freq % 16 * 100 / 16);
	t->tv_freq = freq;
	t->standby = false;

	analog_ops->set_params(&t->fe, &params);
पूर्ण

/**
 * tuner_fixup_std - क्रमce a given video standard variant
 *
 * @t: tuner पूर्णांकernal काष्ठा
 * @std:	TV standard
 *
 * A few devices or drivers have problem to detect some standard variations.
 * On other operational प्रणालीs, the drivers generally have a per-country
 * code, and some logic to apply per-country hacks. V4L2 API करोesn't provide
 * such hacks. Instead, it relies on a proper video standard selection from
 * the userspace application. However, as some apps are buggy, not allowing
 * to distinguish all video standard variations, a modprobe parameter can
 * be used to क्रमce a video standard match.
 */
अटल v4l2_std_id tuner_fixup_std(काष्ठा tuner *t, v4l2_std_id std)
अणु
	अगर (pal[0] != '-' && (std & V4L2_STD_PAL) == V4L2_STD_PAL) अणु
		चयन (pal[0]) अणु
		हाल '6':
			वापस V4L2_STD_PAL_60;
		हाल 'b':
		हाल 'B':
		हाल 'g':
		हाल 'G':
			वापस V4L2_STD_PAL_BG;
		हाल 'i':
		हाल 'I':
			वापस V4L2_STD_PAL_I;
		हाल 'd':
		हाल 'D':
		हाल 'k':
		हाल 'K':
			वापस V4L2_STD_PAL_DK;
		हाल 'M':
		हाल 'm':
			वापस V4L2_STD_PAL_M;
		हाल 'N':
		हाल 'n':
			अगर (pal[1] == 'c' || pal[1] == 'C')
				वापस V4L2_STD_PAL_Nc;
			वापस V4L2_STD_PAL_N;
		शेष:
			pr_warn("pal= argument not recognised\n");
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (secam[0] != '-' && (std & V4L2_STD_SECAM) == V4L2_STD_SECAM) अणु
		चयन (secam[0]) अणु
		हाल 'b':
		हाल 'B':
		हाल 'g':
		हाल 'G':
		हाल 'h':
		हाल 'H':
			वापस V4L2_STD_SECAM_B |
			       V4L2_STD_SECAM_G |
			       V4L2_STD_SECAM_H;
		हाल 'd':
		हाल 'D':
		हाल 'k':
		हाल 'K':
			वापस V4L2_STD_SECAM_DK;
		हाल 'l':
		हाल 'L':
			अगर ((secam[1] == 'C') || (secam[1] == 'c'))
				वापस V4L2_STD_SECAM_LC;
			वापस V4L2_STD_SECAM_L;
		शेष:
			pr_warn("secam= argument not recognised\n");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ntsc[0] != '-' && (std & V4L2_STD_NTSC) == V4L2_STD_NTSC) अणु
		चयन (ntsc[0]) अणु
		हाल 'm':
		हाल 'M':
			वापस V4L2_STD_NTSC_M;
		हाल 'j':
		हाल 'J':
			वापस V4L2_STD_NTSC_M_JP;
		हाल 'k':
		हाल 'K':
			वापस V4L2_STD_NTSC_M_KR;
		शेष:
			pr_info("ntsc= argument not recognised\n");
			अवरोध;
		पूर्ण
	पूर्ण
	वापस std;
पूर्ण

/*
 * Functions that are specअगरic क्रम Radio mode
 */

/**
 * set_radio_freq - Set tuner frequency,  freq in Units of 62.5 Hz  = 1/16kHz
 *
 * @c:	i2c_client descriptor
 * @freq: frequency
 */
अटल व्योम set_radio_freq(काष्ठा i2c_client *c, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा tuner *t = to_tuner(i2c_get_clientdata(c));
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	काष्ठा analog_parameters params = अणु
		.mode      = t->mode,
		.audmode   = t->audmode,
		.std       = t->std
	पूर्ण;

	अगर (t->type == UNSET) अणु
		pr_warn("tuner type not set\n");
		वापस;
	पूर्ण
	अगर (शून्य == analog_ops->set_params) अणु
		pr_warn("tuner has no way to set radio frequency\n");
		वापस;
	पूर्ण
	अगर (freq < radio_range[0] * 16000 || freq > radio_range[1] * 16000) अणु
		dprपूर्णांकk("radio freq (%d.%02d) out of range (%d-%d)\n",
			   freq / 16000, freq % 16000 * 100 / 16000,
			   radio_range[0], radio_range[1]);
		/* V4L2 spec: अगर the freq is not possible then the बंदst
		   possible value should be selected */
		अगर (freq < radio_range[0] * 16000)
			freq = radio_range[0] * 16000;
		अन्यथा
			freq = radio_range[1] * 16000;
	पूर्ण
	params.frequency = freq;
	dprपूर्णांकk("radio freq set to %d.%02d\n",
			freq / 16000, freq % 16000 * 100 / 16000);
	t->radio_freq = freq;
	t->standby = false;

	analog_ops->set_params(&t->fe, &params);
	/*
	 * The tuner driver might decide to change the audmode अगर it only
	 * supports stereo, so update t->audmode.
	 */
	t->audmode = params.audmode;
पूर्ण

/*
 * Debug function क्रम reporting tuner status to userspace
 */

/**
 * tuner_status - Dumps the current tuner status at dmesg
 * @fe: poपूर्णांकer to काष्ठा dvb_frontend
 *
 * This callback is used only क्रम driver debug purposes, answering to
 * VIDIOC_LOG_STATUS. No changes should happen on this call.
 */
अटल व्योम tuner_status(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tuner *t = fe->analog_demod_priv;
	अचिन्हित दीर्घ freq, freq_fraction;
	काष्ठा dvb_tuner_ops *fe_tuner_ops = &fe->ops.tuner_ops;
	काष्ठा analog_demod_ops *analog_ops = &fe->ops.analog_ops;
	स्थिर अक्षर *p;

	चयन (t->mode) अणु
	हाल V4L2_TUNER_RADIO:
		p = "radio";
		अवरोध;
	हाल V4L2_TUNER_DIGITAL_TV: /* Used by mt20xx */
		p = "digital TV";
		अवरोध;
	हाल V4L2_TUNER_ANALOG_TV:
	शेष:
		p = "analog TV";
		अवरोध;
	पूर्ण
	अगर (t->mode == V4L2_TUNER_RADIO) अणु
		freq = t->radio_freq / 16000;
		freq_fraction = (t->radio_freq % 16000) * 100 / 16000;
	पूर्ण अन्यथा अणु
		freq = t->tv_freq / 16;
		freq_fraction = (t->tv_freq % 16) * 100 / 16;
	पूर्ण
	pr_info("Tuner mode:      %s%s\n", p,
		   t->standby ? " on standby mode" : "");
	pr_info("Frequency:       %lu.%02lu MHz\n", freq, freq_fraction);
	pr_info("Standard:        0x%08lx\n", (अचिन्हित दीर्घ)t->std);
	अगर (t->mode != V4L2_TUNER_RADIO)
		वापस;
	अगर (fe_tuner_ops->get_status) अणु
		u32 tuner_status;

		fe_tuner_ops->get_status(&t->fe, &tuner_status);
		अगर (tuner_status & TUNER_STATUS_LOCKED)
			pr_info("Tuner is locked.\n");
		अगर (tuner_status & TUNER_STATUS_STEREO)
			pr_info("Stereo:          yes\n");
	पूर्ण
	अगर (analog_ops->has_संकेत) अणु
		u16 संकेत;

		अगर (!analog_ops->has_संकेत(fe, &संकेत))
			pr_info("Signal strength: %hu\n", संकेत);
	पूर्ण
पूर्ण

/*
 * Function to splicitly change mode to radio. Probably not needed anymore
 */

अटल पूर्णांक tuner_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tuner *t = to_tuner(sd);

	अगर (set_mode(t, V4L2_TUNER_RADIO) == 0)
		set_freq(t, 0);
	वापस 0;
पूर्ण

/*
 * Tuner callbacks to handle userspace ioctl's
 */

/**
 * tuner_standby - places the tuner in standby mode
 * @sd: poपूर्णांकer to काष्ठा v4l2_subdev
 */
अटल पूर्णांक tuner_standby(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tuner *t = to_tuner(sd);
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	dprपूर्णांकk("Putting tuner to sleep\n");
	t->standby = true;
	अगर (analog_ops->standby)
		analog_ops->standby(&t->fe);
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा tuner *t = to_tuner(sd);

	अगर (set_mode(t, V4L2_TUNER_ANALOG_TV))
		वापस 0;

	t->std = tuner_fixup_std(t, std);
	अगर (t->std != std)
		dprपूर्णांकk("Fixup standard %llx to %llx\n", std, t->std);
	set_freq(t, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा tuner *t = to_tuner(sd);

	अगर (set_mode(t, f->type) == 0)
		set_freq(t, f->frequency);
	वापस 0;
पूर्ण

/**
 * tuner_g_frequency - Get the tuned frequency क्रम the tuner
 * @sd: poपूर्णांकer to काष्ठा v4l2_subdev
 * @f: poपूर्णांकer to काष्ठा v4l2_frequency
 *
 * At वापस, the काष्ठाure f will be filled with tuner frequency
 * अगर the tuner matches the f->type.
 * Note: f->type should be initialized beक्रमe calling it.
 * This is करोne by either video_ioctl2 or by the bridge driver.
 */
अटल पूर्णांक tuner_g_frequency(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा tuner *t = to_tuner(sd);
	काष्ठा dvb_tuner_ops *fe_tuner_ops = &t->fe.ops.tuner_ops;

	अगर (check_mode(t, f->type) == -EINVAL)
		वापस 0;
	अगर (f->type == t->mode && fe_tuner_ops->get_frequency && !t->standby) अणु
		u32 असल_freq;

		fe_tuner_ops->get_frequency(&t->fe, &असल_freq);
		f->frequency = (V4L2_TUNER_RADIO == t->mode) ?
			DIV_ROUND_CLOSEST(असल_freq * 2, 125) :
			DIV_ROUND_CLOSEST(असल_freq, 62500);
	पूर्ण अन्यथा अणु
		f->frequency = (V4L2_TUNER_RADIO == f->type) ?
			t->radio_freq : t->tv_freq;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * tuner_g_tuner - Fill in tuner inक्रमmation
 * @sd: poपूर्णांकer to काष्ठा v4l2_subdev
 * @vt: poपूर्णांकer to काष्ठा v4l2_tuner
 *
 * At वापस, the काष्ठाure vt will be filled with tuner inक्रमmation
 * अगर the tuner matches vt->type.
 * Note: vt->type should be initialized beक्रमe calling it.
 * This is करोne by either video_ioctl2 or by the bridge driver.
 */
अटल पूर्णांक tuner_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा tuner *t = to_tuner(sd);
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;
	काष्ठा dvb_tuner_ops *fe_tuner_ops = &t->fe.ops.tuner_ops;

	अगर (check_mode(t, vt->type) == -EINVAL)
		वापस 0;
	अगर (vt->type == t->mode && analog_ops->get_afc)
		analog_ops->get_afc(&t->fe, &vt->afc);
	अगर (vt->type == t->mode && analog_ops->has_संकेत) अणु
		u16 संकेत = (u16)vt->संकेत;

		अगर (!analog_ops->has_संकेत(&t->fe, &संकेत))
			vt->संकेत = संकेत;
	पूर्ण
	अगर (vt->type != V4L2_TUNER_RADIO) अणु
		vt->capability |= V4L2_TUNER_CAP_NORM;
		vt->rangelow = tv_range[0] * 16;
		vt->rangehigh = tv_range[1] * 16;
		वापस 0;
	पूर्ण

	/* radio mode */
	अगर (vt->type == t->mode) अणु
		vt->rxsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
		अगर (fe_tuner_ops->get_status) अणु
			u32 tuner_status;

			fe_tuner_ops->get_status(&t->fe, &tuner_status);
			vt->rxsubchans =
				(tuner_status & TUNER_STATUS_STEREO) ?
				V4L2_TUNER_SUB_STEREO :
				V4L2_TUNER_SUB_MONO;
		पूर्ण
		vt->audmode = t->audmode;
	पूर्ण
	vt->capability |= V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO;
	vt->rangelow = radio_range[0] * 16000;
	vt->rangehigh = radio_range[1] * 16000;

	वापस 0;
पूर्ण

/**
 * tuner_s_tuner - Set the tuner's audio mode
 * @sd: poपूर्णांकer to काष्ठा v4l2_subdev
 * @vt: poपूर्णांकer to काष्ठा v4l2_tuner
 *
 * Sets the audio mode अगर the tuner matches vt->type.
 * Note: vt->type should be initialized beक्रमe calling it.
 * This is करोne by either video_ioctl2 or by the bridge driver.
 */
अटल पूर्णांक tuner_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा tuner *t = to_tuner(sd);

	अगर (set_mode(t, vt->type))
		वापस 0;

	अगर (t->mode == V4L2_TUNER_RADIO) अणु
		t->audmode = vt->audmode;
		/*
		 * For radio audmode can only be mono or stereo. Map any
		 * other values to stereo. The actual tuner driver that is
		 * called in set_radio_freq can decide to limit the audmode to
		 * mono अगर only mono is supported.
		 */
		अगर (t->audmode != V4L2_TUNER_MODE_MONO &&
		    t->audmode != V4L2_TUNER_MODE_STEREO)
			t->audmode = V4L2_TUNER_MODE_STEREO;
	पूर्ण
	set_freq(t, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tuner_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tuner *t = to_tuner(sd);
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	अगर (analog_ops->tuner_status)
		analog_ops->tuner_status(&t->fe);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tuner_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *c = to_i2c_client(dev);
	काष्ठा tuner *t = to_tuner(i2c_get_clientdata(c));
	काष्ठा analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	dprपूर्णांकk("suspend\n");

	अगर (t->fe.ops.tuner_ops.suspend)
		t->fe.ops.tuner_ops.suspend(&t->fe);
	अन्यथा अगर (!t->standby && analog_ops->standby)
		analog_ops->standby(&t->fe);

	वापस 0;
पूर्ण

अटल पूर्णांक tuner_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *c = to_i2c_client(dev);
	काष्ठा tuner *t = to_tuner(i2c_get_clientdata(c));

	dprपूर्णांकk("resume\n");

	अगर (t->fe.ops.tuner_ops.resume)
		t->fe.ops.tuner_ops.resume(&t->fe);
	अन्यथा अगर (!t->standby)
		अगर (set_mode(t, t->mode) == 0)
			set_freq(t, 0);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tuner_command(काष्ठा i2c_client *client, अचिन्हित cmd, व्योम *arg)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	/* TUNER_SET_CONFIG is still called by tuner-simple.c, so we have
	   to handle it here.
	   There must be a better way of करोing this... */
	चयन (cmd) अणु
	हाल TUNER_SET_CONFIG:
		वापस tuner_s_config(sd, arg);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

/*
 * Callback काष्ठाs
 */

अटल स्थिर काष्ठा v4l2_subdev_core_ops tuner_core_ops = अणु
	.log_status = tuner_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops tuner_tuner_ops = अणु
	.standby = tuner_standby,
	.s_radio = tuner_s_radio,
	.g_tuner = tuner_g_tuner,
	.s_tuner = tuner_s_tuner,
	.s_frequency = tuner_s_frequency,
	.g_frequency = tuner_g_frequency,
	.s_type_addr = tuner_s_type_addr,
	.s_config = tuner_s_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops tuner_video_ops = अणु
	.s_std = tuner_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tuner_ops = अणु
	.core = &tuner_core_ops,
	.tuner = &tuner_tuner_ops,
	.video = &tuner_video_ops,
पूर्ण;

/*
 * I2C काष्ठाs and module init functions
 */

अटल स्थिर काष्ठा dev_pm_ops tuner_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tuner_suspend, tuner_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id tuner_id[] = अणु
	अणु "tuner", पूर्ण, /* स्वतःdetect */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tuner_id);

अटल काष्ठा i2c_driver tuner_driver = अणु
	.driver = अणु
		.name	= "tuner",
		.pm	= &tuner_pm_ops,
	पूर्ण,
	.probe		= tuner_probe,
	.हटाओ		= tuner_हटाओ,
	.command	= tuner_command,
	.id_table	= tuner_id,
पूर्ण;

module_i2c_driver(tuner_driver);

MODULE_DESCRIPTION("device driver for various TV and TV+FM radio tuners");
MODULE_AUTHOR("Ralph Metzler, Gerd Knorr, Gunther Mayer");
MODULE_LICENSE("GPL");
