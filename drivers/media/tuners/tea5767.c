<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// For Philips TEA5767 FM Chip used on some TV Cards like Prolink Pixelview
// I2C address is always 0xC0.
//
// Copyright (c) 2005 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// tea5767 स्वतःdetection thanks to Torsten Seeboth and Atsushi Nakagawa
// from their contributions on DScaler.

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश "tuner-i2c.h"
#समावेश "tea5767.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

/*****************************************************************************/

काष्ठा tea5767_priv अणु
	काष्ठा tuner_i2c_props	i2c_props;
	u32			frequency;
	काष्ठा tea5767_ctrl	ctrl;
पूर्ण;

/*****************************************************************************/

/******************************
 * Write mode रेजिस्टर values *
 ******************************/

/* First रेजिस्टर */
#घोषणा TEA5767_MUTE		0x80	/* Mutes output */
#घोषणा TEA5767_SEARCH		0x40	/* Activates station search */
/* Bits 0-5 क्रम भागider MSB */

/* Second रेजिस्टर */
/* Bits 0-7 क्रम भागider LSB */

/* Third रेजिस्टर */

/* Station search from botton to up */
#घोषणा TEA5767_SEARCH_UP	0x80

/* Searches with ADC output = 10 */
#घोषणा TEA5767_SRCH_HIGH_LVL	0x60

/* Searches with ADC output = 10 */
#घोषणा TEA5767_SRCH_MID_LVL	0x40

/* Searches with ADC output = 5 */
#घोषणा TEA5767_SRCH_LOW_LVL	0x20

/* अगर on, भाग=4*(Frf+Fअगर)/Fref otherwise, भाग=4*(Frf-Fअगर)/Freq) */
#घोषणा TEA5767_HIGH_LO_INJECT	0x10

/* Disable stereo */
#घोषणा TEA5767_MONO		0x08

/* Disable right channel and turns to mono */
#घोषणा TEA5767_MUTE_RIGHT	0x04

/* Disable left channel and turns to mono */
#घोषणा TEA5767_MUTE_LEFT	0x02

#घोषणा TEA5767_PORT1_HIGH	0x01

/* Fourth रेजिस्टर */
#घोषणा TEA5767_PORT2_HIGH	0x80
/* Chips stops working. Only I2C bus reमुख्यs on */
#घोषणा TEA5767_STDBY		0x40

/* Japan freq (76-108 MHz. If disabled, 87.5-108 MHz */
#घोषणा TEA5767_JAPAN_BAND	0x20

/* Unselected means 32.768 KHz freq as reference. Otherwise Xtal at 13 MHz */
#घोषणा TEA5767_XTAL_32768	0x10

/* Cuts weak संकेतs */
#घोषणा TEA5767_SOFT_MUTE	0x08

/* Activates high cut control */
#घोषणा TEA5767_HIGH_CUT_CTRL	0x04

/* Activates stereo noise control */
#घोषणा TEA5767_ST_NOISE_CTL	0x02

/* If activate PORT 1 indicates SEARCH or अन्यथा it is used as PORT1 */
#घोषणा TEA5767_SRCH_IND	0x01

/* Fअगरth रेजिस्टर */

/* By activating, it will use Xtal at 13 MHz as reference क्रम भागider */
#घोषणा TEA5767_PLLREF_ENABLE	0x80

/* By activating, deemphasis=50, or अन्यथा, deemphasis of 50us */
#घोषणा TEA5767_DEEMPH_75	0X40

/*****************************
 * Read mode रेजिस्टर values *
 *****************************/

/* First रेजिस्टर */
#घोषणा TEA5767_READY_FLAG_MASK	0x80
#घोषणा TEA5767_BAND_LIMIT_MASK	0X40
/* Bits 0-5 क्रम भागider MSB after search or preset */

/* Second रेजिस्टर */
/* Bits 0-7 क्रम भागider LSB after search or preset */

/* Third रेजिस्टर */
#घोषणा TEA5767_STEREO_MASK	0x80
#घोषणा TEA5767_IF_CNTR_MASK	0x7f

/* Fourth रेजिस्टर */
#घोषणा TEA5767_ADC_LEVEL_MASK	0xf0

/* should be 0 */
#घोषणा TEA5767_CHIP_ID_MASK	0x0f

/* Fअगरth रेजिस्टर */
/* Reserved क्रम future extensions */
#घोषणा TEA5767_RESERVED_MASK	0xff

/*****************************************************************************/

अटल व्योम tea5767_status_dump(काष्ठा tea5767_priv *priv,
				अचिन्हित अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक भाग, frq;

	अगर (TEA5767_READY_FLAG_MASK & buffer[0])
		tuner_info("Ready Flag ON\n");
	अन्यथा
		tuner_info("Ready Flag OFF\n");

	अगर (TEA5767_BAND_LIMIT_MASK & buffer[0])
		tuner_info("Tuner at band limit\n");
	अन्यथा
		tuner_info("Tuner not at band limit\n");

	भाग = ((buffer[0] & 0x3f) << 8) | buffer[1];

	चयन (priv->ctrl.xtal_freq) अणु
	हाल TEA5767_HIGH_LO_13MHz:
		frq = (भाग * 50000 - 700000 - 225000) / 4;	/* Freq in KHz */
		अवरोध;
	हाल TEA5767_LOW_LO_13MHz:
		frq = (भाग * 50000 + 700000 + 225000) / 4;	/* Freq in KHz */
		अवरोध;
	हाल TEA5767_LOW_LO_32768:
		frq = (भाग * 32768 + 700000 + 225000) / 4;	/* Freq in KHz */
		अवरोध;
	हाल TEA5767_HIGH_LO_32768:
	शेष:
		frq = (भाग * 32768 - 700000 - 225000) / 4;	/* Freq in KHz */
		अवरोध;
	पूर्ण
	buffer[0] = (भाग >> 8) & 0x3f;
	buffer[1] = भाग & 0xff;

	tuner_info("Frequency %d.%03d KHz (divider = 0x%04x)\n",
		   frq / 1000, frq % 1000, भाग);

	अगर (TEA5767_STEREO_MASK & buffer[2])
		tuner_info("Stereo\n");
	अन्यथा
		tuner_info("Mono\n");

	tuner_info("IF Counter = %d\n", buffer[2] & TEA5767_IF_CNTR_MASK);

	tuner_info("ADC Level = %d\n",
		   (buffer[3] & TEA5767_ADC_LEVEL_MASK) >> 4);

	tuner_info("Chip ID = %d\n", (buffer[3] & TEA5767_CHIP_ID_MASK));

	tuner_info("Reserved = 0x%02x\n",
		   (buffer[4] & TEA5767_RESERVED_MASK));
पूर्ण

/* Freq should be specअगरyed at 62.5 Hz */
अटल पूर्णांक set_radio_freq(काष्ठा dvb_frontend *fe,
			  काष्ठा analog_parameters *params)
अणु
	काष्ठा tea5767_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक frq = params->frequency;
	अचिन्हित अक्षर buffer[5];
	अचिन्हित भाग;
	पूर्णांक rc;

	tuner_dbg("radio freq = %d.%03d MHz\n", frq/16000,(frq/16)%1000);

	buffer[2] = 0;

	अगर (priv->ctrl.port1)
		buffer[2] |= TEA5767_PORT1_HIGH;

	अगर (params->audmode == V4L2_TUNER_MODE_MONO) अणु
		tuner_dbg("TEA5767 set to mono\n");
		buffer[2] |= TEA5767_MONO;
	पूर्ण अन्यथा अणु
		tuner_dbg("TEA5767 set to stereo\n");
	पूर्ण


	buffer[3] = 0;

	अगर (priv->ctrl.port2)
		buffer[3] |= TEA5767_PORT2_HIGH;

	अगर (priv->ctrl.high_cut)
		buffer[3] |= TEA5767_HIGH_CUT_CTRL;

	अगर (priv->ctrl.st_noise)
		buffer[3] |= TEA5767_ST_NOISE_CTL;

	अगर (priv->ctrl.soft_mute)
		buffer[3] |= TEA5767_SOFT_MUTE;

	अगर (priv->ctrl.japan_band)
		buffer[3] |= TEA5767_JAPAN_BAND;

	buffer[4] = 0;

	अगर (priv->ctrl.deemph_75)
		buffer[4] |= TEA5767_DEEMPH_75;

	अगर (priv->ctrl.pllref)
		buffer[4] |= TEA5767_PLLREF_ENABLE;


	/* Rounds freq to next decimal value - क्रम 62.5 KHz step */
	/* frq = 20*(frq/16)+radio_frq[frq%16]; */

	चयन (priv->ctrl.xtal_freq) अणु
	हाल TEA5767_HIGH_LO_13MHz:
		tuner_dbg("radio HIGH LO inject xtal @ 13 MHz\n");
		buffer[2] |= TEA5767_HIGH_LO_INJECT;
		भाग = (frq * (4000 / 16) + 700000 + 225000 + 25000) / 50000;
		अवरोध;
	हाल TEA5767_LOW_LO_13MHz:
		tuner_dbg("radio LOW LO inject xtal @ 13 MHz\n");

		भाग = (frq * (4000 / 16) - 700000 - 225000 + 25000) / 50000;
		अवरोध;
	हाल TEA5767_LOW_LO_32768:
		tuner_dbg("radio LOW LO inject xtal @ 32,768 MHz\n");
		buffer[3] |= TEA5767_XTAL_32768;
		/* स्थिर 700=4000*175 Khz - to adjust freq to right value */
		भाग = ((frq * (4000 / 16) - 700000 - 225000) + 16384) >> 15;
		अवरोध;
	हाल TEA5767_HIGH_LO_32768:
	शेष:
		tuner_dbg("radio HIGH LO inject xtal @ 32,768 MHz\n");

		buffer[2] |= TEA5767_HIGH_LO_INJECT;
		buffer[3] |= TEA5767_XTAL_32768;
		भाग = ((frq * (4000 / 16) + 700000 + 225000) + 16384) >> 15;
		अवरोध;
	पूर्ण
	buffer[0] = (भाग >> 8) & 0x3f;
	buffer[1] = भाग & 0xff;

	अगर (5 != (rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 5)))
		tuner_warn("i2c i/o error: rc == %d (should be 5)\n", rc);

	अगर (debug) अणु
		अगर (5 != (rc = tuner_i2c_xfer_recv(&priv->i2c_props, buffer, 5)))
			tuner_warn("i2c i/o error: rc == %d (should be 5)\n", rc);
		अन्यथा
			tea5767_status_dump(priv, buffer);
	पूर्ण

	priv->frequency = frq * 125 / 2;

	वापस 0;
पूर्ण

अटल पूर्णांक tea5767_पढ़ो_status(काष्ठा dvb_frontend *fe, अक्षर *buffer)
अणु
	काष्ठा tea5767_priv *priv = fe->tuner_priv;
	पूर्णांक rc;

	स_रखो(buffer, 0, 5);
	अगर (5 != (rc = tuner_i2c_xfer_recv(&priv->i2c_props, buffer, 5))) अणु
		tuner_warn("i2c i/o error: rc == %d (should be 5)\n", rc);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tea5767_संकेत(काष्ठा dvb_frontend *fe, स्थिर अक्षर *buffer)
अणु
	काष्ठा tea5767_priv *priv = fe->tuner_priv;

	पूर्णांक संकेत = ((buffer[3] & TEA5767_ADC_LEVEL_MASK) << 8);

	tuner_dbg("Signal strength: %d\n", संकेत);

	वापस संकेत;
पूर्ण

अटल अंतरभूत पूर्णांक tea5767_stereo(काष्ठा dvb_frontend *fe, स्थिर अक्षर *buffer)
अणु
	काष्ठा tea5767_priv *priv = fe->tuner_priv;

	पूर्णांक stereo = buffer[2] & TEA5767_STEREO_MASK;

	tuner_dbg("Radio ST GET = %02x\n", stereo);

	वापस (stereo ? V4L2_TUNER_SUB_STEREO : 0);
पूर्ण

अटल पूर्णांक tea5767_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	अचिन्हित अक्षर buffer[5];

	*status = 0;

	अगर (0 == tea5767_पढ़ो_status(fe, buffer)) अणु
		अगर (tea5767_संकेत(fe, buffer))
			*status = TUNER_STATUS_LOCKED;
		अगर (tea5767_stereo(fe, buffer))
			*status |= TUNER_STATUS_STEREO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tea5767_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	अचिन्हित अक्षर buffer[5];

	*strength = 0;

	अगर (0 == tea5767_पढ़ो_status(fe, buffer))
		*strength = tea5767_संकेत(fe, buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक tea5767_standby(काष्ठा dvb_frontend *fe)
अणु
	अचिन्हित अक्षर buffer[5];
	काष्ठा tea5767_priv *priv = fe->tuner_priv;
	अचिन्हित भाग, rc;

	भाग = (87500 * 4 + 700 + 225 + 25) / 50; /* Set frequency to 87.5 MHz */
	buffer[0] = (भाग >> 8) & 0x3f;
	buffer[1] = भाग & 0xff;
	buffer[2] = TEA5767_PORT1_HIGH;
	buffer[3] = TEA5767_PORT2_HIGH | TEA5767_HIGH_CUT_CTRL |
		    TEA5767_ST_NOISE_CTL | TEA5767_JAPAN_BAND | TEA5767_STDBY;
	buffer[4] = 0;

	अगर (5 != (rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 5)))
		tuner_warn("i2c i/o error: rc == %d (should be 5)\n", rc);

	वापस 0;
पूर्ण

पूर्णांक tea5767_स्वतःdetection(काष्ठा i2c_adapter* i2c_adap, u8 i2c_addr)
अणु
	काष्ठा tuner_i2c_props i2c = अणु .adap = i2c_adap, .addr = i2c_addr पूर्ण;
	अचिन्हित अक्षर buffer[7] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

	पूर्णांक rc;

	अगर ((rc = tuner_i2c_xfer_recv(&i2c, buffer, 7))< 5) अणु
		pr_warn("It is not a TEA5767. Received %i bytes.\n", rc);
		वापस -EINVAL;
	पूर्ण

	/* If all bytes are the same then it's a TV tuner and not a tea5767 */
	अगर (buffer[0] == buffer[1] && buffer[0] == buffer[2] &&
	    buffer[0] == buffer[3] && buffer[0] == buffer[4]) अणु
		pr_warn("All bytes are equal. It is not a TEA5767\n");
		वापस -EINVAL;
	पूर्ण

	/*  Status bytes:
	 *  Byte 4: bit 3:1 : CI (Chip Identअगरication) == 0
	 *          bit 0   : पूर्णांकernally set to 0
	 *  Byte 5: bit 7:0 : == 0
	 */
	अगर (((buffer[3] & 0x0f) != 0x00) || (buffer[4] != 0x00)) अणु
		pr_warn("Chip ID is not zero. It is not a TEA5767\n");
		वापस -EINVAL;
	पूर्ण


	वापस 0;
पूर्ण

अटल व्योम tea5767_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक tea5767_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tea5767_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक tea5767_set_config (काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा tea5767_priv *priv = fe->tuner_priv;

	स_नकल(&priv->ctrl, priv_cfg, माप(priv->ctrl));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tea5767_tuner_ops = अणु
	.info = अणु
		.name           = "tea5767", // Philips TEA5767HN FM Radio
	पूर्ण,

	.set_analog_params = set_radio_freq,
	.set_config	   = tea5767_set_config,
	.sleep             = tea5767_standby,
	.release           = tea5767_release,
	.get_frequency     = tea5767_get_frequency,
	.get_status        = tea5767_get_status,
	.get_rf_strength   = tea5767_get_rf_strength,
पूर्ण;

काष्ठा dvb_frontend *tea5767_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter* i2c_adap,
				    u8 i2c_addr)
अणु
	काष्ठा tea5767_priv *priv = शून्य;

	priv = kzalloc(माप(काष्ठा tea5767_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	fe->tuner_priv = priv;

	priv->i2c_props.addr  = i2c_addr;
	priv->i2c_props.adap  = i2c_adap;
	priv->i2c_props.name  = "tea5767";

	priv->ctrl.xtal_freq  = TEA5767_HIGH_LO_32768;
	priv->ctrl.port1      = 1;
	priv->ctrl.port2      = 1;
	priv->ctrl.high_cut   = 1;
	priv->ctrl.st_noise   = 1;
	priv->ctrl.japan_band = 1;

	स_नकल(&fe->ops.tuner_ops, &tea5767_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	tuner_info("type set to %s\n", "Philips TEA5767HN FM Radio");

	वापस fe;
पूर्ण

EXPORT_SYMBOL_GPL(tea5767_attach);
EXPORT_SYMBOL_GPL(tea5767_स्वतःdetection);

MODULE_DESCRIPTION("Philips TEA5767 FM tuner driver");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL v2");
