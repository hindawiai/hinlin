<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// For Philips TEA5761 FM Chip
// I2C address is always 0x20 (0x10 at 7-bit mode).
//
// Copyright (c) 2005-2007 Mauro Carvalho Chehab <mchehab@kernel.org>

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <media/tuner.h>
#समावेश "tuner-i2c.h"
#समावेश "tea5761.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

काष्ठा tea5761_priv अणु
	काष्ठा tuner_i2c_props i2c_props;

	u32 frequency;
	bool standby;
पूर्ण;

/*****************************************************************************/

/***************************
 * TEA5761HN I2C रेजिस्टरs *
 ***************************/

/* INTREG - Read: bytes 0 and 1 / Write: byte 0 */

	/* first byte क्रम पढ़ोing */
#घोषणा TEA5761_INTREG_IFFLAG		0x10
#घोषणा TEA5761_INTREG_LEVFLAG		0x8
#घोषणा TEA5761_INTREG_FRRFLAG		0x2
#घोषणा TEA5761_INTREG_BLFLAG		0x1

	/* second byte क्रम पढ़ोing / byte क्रम writing */
#घोषणा TEA5761_INTREG_IFMSK		0x10
#घोषणा TEA5761_INTREG_LEVMSK		0x8
#घोषणा TEA5761_INTREG_FRMSK		0x2
#घोषणा TEA5761_INTREG_BLMSK		0x1

/* FRQSET - Read: bytes 2 and 3 / Write: byte 1 and 2 */

	/* First byte */
#घोषणा TEA5761_FRQSET_SEARCH_UP 0x80		/* 1=Station search from botton to up */
#घोषणा TEA5761_FRQSET_SEARCH_MODE 0x40		/* 1=Search mode */

	/* Bits 0-5 क्रम भागider MSB */

	/* Second byte */
	/* Bits 0-7 क्रम भागider LSB */

/* TNCTRL - Read: bytes 4 and 5 / Write: Bytes 3 and 4 */

	/* first byte */

#घोषणा TEA5761_TNCTRL_PUPD_0	0x40	/* Power UP/Power Down MSB */
#घोषणा TEA5761_TNCTRL_BLIM	0X20	/* 1= Japan Frequencies, 0= European frequencies */
#घोषणा TEA5761_TNCTRL_SWPM	0x10	/* 1= software port is FRRFLAG */
#घोषणा TEA5761_TNCTRL_IFCTC	0x08	/* 1= IF count समय 15.02 ms, 0= IF count समय 2.02 ms */
#घोषणा TEA5761_TNCTRL_AFM	0x04
#घोषणा TEA5761_TNCTRL_SMUTE	0x02	/* 1= Soft mute */
#घोषणा TEA5761_TNCTRL_SNC	0x01

	/* second byte */

#घोषणा TEA5761_TNCTRL_MU	0x80	/* 1=Hard mute */
#घोषणा TEA5761_TNCTRL_SSL_1	0x40
#घोषणा TEA5761_TNCTRL_SSL_0	0x20
#घोषणा TEA5761_TNCTRL_HLSI	0x10
#घोषणा TEA5761_TNCTRL_MST	0x08	/* 1 = mono */
#घोषणा TEA5761_TNCTRL_SWP	0x04
#घोषणा TEA5761_TNCTRL_DTC	0x02	/* 1 = deemphasis 50 us, 0 = deemphasis 75 us */
#घोषणा TEA5761_TNCTRL_AHLSI	0x01

/* FRQCHECK - Read: bytes 6 and 7  */
	/* First byte */

	/* Bits 0-5 क्रम भागider MSB */

	/* Second byte */
	/* Bits 0-7 क्रम भागider LSB */

/* TUNCHECK - Read: bytes 8 and 9  */

	/* First byte */
#घोषणा TEA5761_TUNCHECK_IF_MASK	0x7e	/* IF count */
#घोषणा TEA5761_TUNCHECK_TUNTO		0x01

	/* Second byte */
#घोषणा TEA5761_TUNCHECK_LEV_MASK	0xf0	/* Level Count */
#घोषणा TEA5761_TUNCHECK_LD		0x08
#घोषणा TEA5761_TUNCHECK_STEREO		0x04

/* TESTREG - Read: bytes 10 and 11 / Write: bytes 5 and 6 */

	/* All zero = no test mode */

/* MANID - Read: bytes 12 and 13 */

	/* First byte - should be 0x10 */
#घोषणा TEA5767_MANID_VERSION_MASK	0xf0	/* Version = 1 */
#घोषणा TEA5767_MANID_ID_MSB_MASK	0x0f	/* Manufacurer ID - should be 0 */

	/* Second byte - Should be 0x2b */

#घोषणा TEA5767_MANID_ID_LSB_MASK	0xfe	/* Manufacturer ID - should be 0x15 */
#घोषणा TEA5767_MANID_IDAV		0x01	/* 1 = Chip has ID, 0 = Chip has no ID */

/* Chip ID - Read: bytes 14 and 15 */

	/* First byte - should be 0x57 */

	/* Second byte - should be 0x61 */

/*****************************************************************************/

#घोषणा FREQ_OFFSET 0 /* क्रम TEA5767, it is 700 to give the right freq */
अटल व्योम tea5761_status_dump(अचिन्हित अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक भाग, frq;

	भाग = ((buffer[2] & 0x3f) << 8) | buffer[3];

	frq = 1000 * (भाग * 32768 / 1000 + FREQ_OFFSET + 225) / 4;	/* Freq in KHz */

	prपूर्णांकk(KERN_INFO "tea5761: Frequency %d.%03d KHz (divider = 0x%04x)\n",
	       frq / 1000, frq % 1000, भाग);
पूर्ण

/* Freq should be specअगरyed at 62.5 Hz */
अटल पूर्णांक __set_radio_freq(काष्ठा dvb_frontend *fe,
			    अचिन्हित पूर्णांक freq,
			    bool mono)
अणु
	काष्ठा tea5761_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक frq = freq;
	अचिन्हित अक्षर buffer[7] = अणु0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अचिन्हित भाग;
	पूर्णांक rc;

	tuner_dbg("radio freq counter %d\n", frq);

	अगर (priv->standby) अणु
		tuner_dbg("TEA5761 set to standby mode\n");
		buffer[5] |= TEA5761_TNCTRL_MU;
	पूर्ण अन्यथा अणु
		buffer[4] |= TEA5761_TNCTRL_PUPD_0;
	पूर्ण


	अगर (mono) अणु
		tuner_dbg("TEA5761 set to mono\n");
		buffer[5] |= TEA5761_TNCTRL_MST;
	पूर्ण अन्यथा अणु
		tuner_dbg("TEA5761 set to stereo\n");
	पूर्ण

	भाग = (1000 * (frq * 4 / 16 + 700 + 225) ) >> 15;
	buffer[1] = (भाग >> 8) & 0x3f;
	buffer[2] = भाग & 0xff;

	अगर (debug)
		tea5761_status_dump(buffer);

	अगर (7 != (rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 7)))
		tuner_warn("i2c i/o error: rc == %d (should be 5)\n", rc);

	priv->frequency = frq * 125 / 2;

	वापस 0;
पूर्ण

अटल पूर्णांक set_radio_freq(काष्ठा dvb_frontend *fe,
			  काष्ठा analog_parameters *params)
अणु
	काष्ठा tea5761_priv *priv = fe->analog_demod_priv;

	priv->standby = false;

	वापस __set_radio_freq(fe, params->frequency,
				params->audmode == V4L2_TUNER_MODE_MONO);
पूर्ण

अटल पूर्णांक set_radio_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tea5761_priv *priv = fe->analog_demod_priv;

	priv->standby = true;

	वापस __set_radio_freq(fe, priv->frequency, false);
पूर्ण

अटल पूर्णांक tea5761_पढ़ो_status(काष्ठा dvb_frontend *fe, अक्षर *buffer)
अणु
	काष्ठा tea5761_priv *priv = fe->tuner_priv;
	पूर्णांक rc;

	स_रखो(buffer, 0, 16);
	अगर (16 != (rc = tuner_i2c_xfer_recv(&priv->i2c_props, buffer, 16))) अणु
		tuner_warn("i2c i/o error: rc == %d (should be 16)\n", rc);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tea5761_संकेत(काष्ठा dvb_frontend *fe, स्थिर अक्षर *buffer)
अणु
	काष्ठा tea5761_priv *priv = fe->tuner_priv;

	पूर्णांक संकेत = ((buffer[9] & TEA5761_TUNCHECK_LEV_MASK) << (13 - 4));

	tuner_dbg("Signal strength: %d\n", संकेत);

	वापस संकेत;
पूर्ण

अटल अंतरभूत पूर्णांक tea5761_stereo(काष्ठा dvb_frontend *fe, स्थिर अक्षर *buffer)
अणु
	काष्ठा tea5761_priv *priv = fe->tuner_priv;

	पूर्णांक stereo = buffer[9] & TEA5761_TUNCHECK_STEREO;

	tuner_dbg("Radio ST GET = %02x\n", stereo);

	वापस (stereo ? V4L2_TUNER_SUB_STEREO : 0);
पूर्ण

अटल पूर्णांक tea5761_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	अचिन्हित अक्षर buffer[16];

	*status = 0;

	अगर (0 == tea5761_पढ़ो_status(fe, buffer)) अणु
		अगर (tea5761_संकेत(fe, buffer))
			*status = TUNER_STATUS_LOCKED;
		अगर (tea5761_stereo(fe, buffer))
			*status |= TUNER_STATUS_STEREO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tea5761_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	अचिन्हित अक्षर buffer[16];

	*strength = 0;

	अगर (0 == tea5761_पढ़ो_status(fe, buffer))
		*strength = tea5761_संकेत(fe, buffer);

	वापस 0;
पूर्ण

पूर्णांक tea5761_स्वतःdetection(काष्ठा i2c_adapter* i2c_adap, u8 i2c_addr)
अणु
	अचिन्हित अक्षर buffer[16];
	पूर्णांक rc;
	काष्ठा tuner_i2c_props i2c = अणु .adap = i2c_adap, .addr = i2c_addr पूर्ण;

	अगर (16 != (rc = tuner_i2c_xfer_recv(&i2c, buffer, 16))) अणु
		prपूर्णांकk(KERN_WARNING "it is not a TEA5761. Received %i chars.\n", rc);
		वापस -EINVAL;
	पूर्ण

	अगर ((buffer[13] != 0x2b) || (buffer[14] != 0x57) || (buffer[15] != 0x061)) अणु
		prपूर्णांकk(KERN_WARNING "Manufacturer ID= 0x%02x, Chip ID = %02x%02x. It is not a TEA5761\n",
				    buffer[13], buffer[14], buffer[15]);
		वापस -EINVAL;
	पूर्ण
	prपूर्णांकk(KERN_WARNING "tea5761: TEA%02x%02x detected. Manufacturer ID= 0x%02x\n",
			    buffer[14], buffer[15], buffer[13]);

	वापस 0;
पूर्ण

अटल व्योम tea5761_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक tea5761_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tea5761_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tea5761_tuner_ops = अणु
	.info = अणु
		.name           = "tea5761", // Philips TEA5761HN FM Radio
	पूर्ण,
	.set_analog_params = set_radio_freq,
	.sleep		   = set_radio_sleep,
	.release           = tea5761_release,
	.get_frequency     = tea5761_get_frequency,
	.get_status        = tea5761_get_status,
	.get_rf_strength   = tea5761_get_rf_strength,
पूर्ण;

काष्ठा dvb_frontend *tea5761_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter* i2c_adap,
				    u8 i2c_addr)
अणु
	काष्ठा tea5761_priv *priv = शून्य;

	अगर (tea5761_स्वतःdetection(i2c_adap, i2c_addr) != 0)
		वापस शून्य;

	priv = kzalloc(माप(काष्ठा tea5761_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	fe->tuner_priv = priv;

	priv->i2c_props.addr = i2c_addr;
	priv->i2c_props.adap = i2c_adap;
	priv->i2c_props.name = "tea5761";

	स_नकल(&fe->ops.tuner_ops, &tea5761_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	tuner_info("type set to %s\n", "Philips TEA5761HN FM Radio");

	वापस fe;
पूर्ण


EXPORT_SYMBOL_GPL(tea5761_attach);
EXPORT_SYMBOL_GPL(tea5761_स्वतःdetection);

MODULE_DESCRIPTION("Philips TEA5761 FM tuner driver");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL v2");
