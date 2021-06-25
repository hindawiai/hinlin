<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2c tv tuner chip device driver
 * controls all those simple 4-control-bytes style tuners.
 *
 * This "tuner-simple" module was split apart from the original "tuner" module.
 */
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/tuner.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner-types.h>
#समावेश "tuner-i2c.h"
#समावेश "tuner-simple.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

#घोषणा TUNER_SIMPLE_MAX 64
अटल अचिन्हित पूर्णांक simple_devcount;

अटल पूर्णांक offset;
module_param(offset, पूर्णांक, 0664);
MODULE_PARM_DESC(offset, "Allows to specify an offset for tuner");

अटल अचिन्हित पूर्णांक atv_input[TUNER_SIMPLE_MAX] = \
			अणु [0 ... (TUNER_SIMPLE_MAX-1)] = 0 पूर्ण;
अटल अचिन्हित पूर्णांक dtv_input[TUNER_SIMPLE_MAX] = \
			अणु [0 ... (TUNER_SIMPLE_MAX-1)] = 0 पूर्ण;
module_param_array(atv_input, पूर्णांक, शून्य, 0644);
module_param_array(dtv_input, पूर्णांक, शून्य, 0644);
MODULE_PARM_DESC(atv_input, "specify atv rf input, 0 for autoselect");
MODULE_PARM_DESC(dtv_input, "specify dtv rf input, 0 for autoselect");

/* ---------------------------------------------------------------------- */

/* tv standard selection क्रम Temic 4046 FM5
   this value takes the low bits of control byte 2
   from datasheet Rev.01, Feb.00
     standard     BG      I       L       L2      D
     picture IF   38.9    38.9    38.9    33.95   38.9
     sound 1      33.4    32.9    32.4    40.45   32.4
     sound 2      33.16
     NICAM        33.05   32.348  33.05           33.05
 */
#घोषणा TEMIC_SET_PAL_I         0x05
#घोषणा TEMIC_SET_PAL_DK        0x09
#घोषणा TEMIC_SET_PAL_L         0x0a /* SECAM ? */
#घोषणा TEMIC_SET_PAL_L2        0x0b /* change IF ! */
#घोषणा TEMIC_SET_PAL_BG        0x0c

/* tv tuner प्रणाली standard selection क्रम Philips FQ1216ME
   this value takes the low bits of control byte 2
   from datasheet "1999 Nov 16" (supersedes "1999 Mar 23")
     standard		BG	DK	I	L	L`
     picture carrier	38.90	38.90	38.90	38.90	33.95
     colour		34.47	34.47	34.47	34.47	38.38
     sound 1		33.40	32.40	32.90	32.40	40.45
     sound 2		33.16	-	-	-	-
     NICAM		33.05	33.05	32.35	33.05	39.80
 */
#घोषणा PHILIPS_SET_PAL_I	0x01 /* Bit 2 always zero !*/
#घोषणा PHILIPS_SET_PAL_BGDK	0x09
#घोषणा PHILIPS_SET_PAL_L2	0x0a
#घोषणा PHILIPS_SET_PAL_L	0x0b

/* प्रणाली चयनing क्रम Philips FI1216MF MK2
   from datasheet "1996 Jul 09",
    standard         BG     L      L'
    picture carrier  38.90  38.90  33.95
    colour	     34.47  34.37  38.38
    sound 1          33.40  32.40  40.45
    sound 2          33.16  -      -
    NICAM            33.05  33.05  39.80
 */
#घोषणा PHILIPS_MF_SET_STD_BG	0x01 /* Bit 2 must be zero, Bit 3 is प्रणाली output */
#घोषणा PHILIPS_MF_SET_STD_L	0x03 /* Used on Secam France */
#घोषणा PHILIPS_MF_SET_STD_LC	0x02 /* Used on SECAM L' */

/* Control byte */

#घोषणा TUNER_RATIO_MASK        0x06 /* Bit cb1:cb2 */
#घोषणा TUNER_RATIO_SELECT_50   0x00
#घोषणा TUNER_RATIO_SELECT_32   0x02
#घोषणा TUNER_RATIO_SELECT_166  0x04
#घोषणा TUNER_RATIO_SELECT_62   0x06

#घोषणा TUNER_CHARGE_PUMP       0x40  /* Bit cb6 */

/* Status byte */

#घोषणा TUNER_POR	  0x80
#घोषणा TUNER_FL          0x40
#घोषणा TUNER_MODE        0x38
#घोषणा TUNER_AFC         0x07
#घोषणा TUNER_SIGNAL      0x07
#घोषणा TUNER_STEREO      0x10

#घोषणा TUNER_PLL_LOCKED   0x40
#घोषणा TUNER_STEREO_MK3   0x04

अटल DEFINE_MUTEX(tuner_simple_list_mutex);
अटल LIST_HEAD(hybrid_tuner_instance_list);

काष्ठा tuner_simple_priv अणु
	अचिन्हित पूर्णांक nr;
	u16 last_भाग;

	काष्ठा tuner_i2c_props i2c_props;
	काष्ठा list_head hybrid_tuner_instance_list;

	अचिन्हित पूर्णांक type;
	काष्ठा tunertype *tun;

	u32 frequency;
	u32 bandwidth;
	bool radio_mode;
पूर्ण;

/* ---------------------------------------------------------------------- */

अटल पूर्णांक tuner_पढ़ो_status(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर byte;

	अगर (1 != tuner_i2c_xfer_recv(&priv->i2c_props, &byte, 1))
		वापस 0;

	वापस byte;
पूर्ण

अटल अंतरभूत पूर्णांक tuner_संकेत(स्थिर पूर्णांक status)
अणु
	वापस (status & TUNER_SIGNAL) << 13;
पूर्ण

अटल अंतरभूत पूर्णांक tuner_stereo(स्थिर पूर्णांक type, स्थिर पूर्णांक status)
अणु
	चयन (type) अणु
	हाल TUNER_PHILIPS_FM1216ME_MK3:
	हाल TUNER_PHILIPS_FM1236_MK3:
	हाल TUNER_PHILIPS_FM1256_IH3:
	हाल TUNER_LG_NTSC_TAPE:
	हाल TUNER_TCL_MF02GIP_5N:
		वापस ((status & TUNER_SIGNAL) == TUNER_STEREO_MK3);
	हाल TUNER_PHILIPS_FM1216MK5:
		वापस status | TUNER_STEREO;
	शेष:
		वापस status & TUNER_STEREO;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक tuner_islocked(स्थिर पूर्णांक status)
अणु
	वापस (status & TUNER_FL);
पूर्ण

अटल अंतरभूत पूर्णांक tuner_afcstatus(स्थिर पूर्णांक status)
अणु
	वापस (status & TUNER_AFC) - 2;
पूर्ण


अटल पूर्णांक simple_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	पूर्णांक tuner_status;

	अगर (priv->i2c_props.adap == शून्य)
		वापस -EINVAL;

	tuner_status = tuner_पढ़ो_status(fe);

	*status = 0;

	अगर (tuner_islocked(tuner_status))
		*status = TUNER_STATUS_LOCKED;
	अगर (tuner_stereo(priv->type, tuner_status))
		*status |= TUNER_STATUS_STEREO;

	tuner_dbg("AFC Status: %d\n", tuner_afcstatus(tuner_status));

	वापस 0;
पूर्ण

अटल पूर्णांक simple_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	पूर्णांक संकेत;

	अगर (priv->i2c_props.adap == शून्य || !priv->radio_mode)
		वापस -EINVAL;

	संकेत = tuner_संकेत(tuner_पढ़ो_status(fe));

	*strength = संकेत;

	tuner_dbg("Signal strength: %d\n", संकेत);

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल अंतरभूत अक्षर *tuner_param_name(क्रमागत param_type type)
अणु
	अक्षर *name;

	चयन (type) अणु
	हाल TUNER_PARAM_TYPE_RADIO:
		name = "radio";
		अवरोध;
	हाल TUNER_PARAM_TYPE_PAL:
		name = "pal";
		अवरोध;
	हाल TUNER_PARAM_TYPE_SECAM:
		name = "secam";
		अवरोध;
	हाल TUNER_PARAM_TYPE_NTSC:
		name = "ntsc";
		अवरोध;
	हाल TUNER_PARAM_TYPE_DIGITAL:
		name = "digital";
		अवरोध;
	शेष:
		name = "unknown";
		अवरोध;
	पूर्ण
	वापस name;
पूर्ण

अटल काष्ठा tuner_params *simple_tuner_params(काष्ठा dvb_frontend *fe,
						क्रमागत param_type desired_type)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	काष्ठा tunertype *tun = priv->tun;
	पूर्णांक i;

	क्रम (i = 0; i < tun->count; i++)
		अगर (desired_type == tun->params[i].type)
			अवरोध;

	/* use शेष tuner params अगर desired_type not available */
	अगर (i == tun->count) अणु
		tuner_dbg("desired params (%s) undefined for tuner %d\n",
			  tuner_param_name(desired_type), priv->type);
		i = 0;
	पूर्ण

	tuner_dbg("using tuner params #%d (%s)\n", i,
		  tuner_param_name(tun->params[i].type));

	वापस &tun->params[i];
पूर्ण

अटल पूर्णांक simple_config_lookup(काष्ठा dvb_frontend *fe,
				काष्ठा tuner_params *t_params,
				अचिन्हित *frequency, u8 *config, u8 *cb)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	पूर्णांक i;

	क्रम (i = 0; i < t_params->count; i++) अणु
		अगर (*frequency > t_params->ranges[i].limit)
			जारी;
		अवरोध;
	पूर्ण
	अगर (i == t_params->count) अणु
		tuner_dbg("frequency out of range (%d > %d)\n",
			  *frequency, t_params->ranges[i - 1].limit);
		*frequency = t_params->ranges[--i].limit;
	पूर्ण
	*config = t_params->ranges[i].config;
	*cb     = t_params->ranges[i].cb;

	tuner_dbg("freq = %d.%02d (%d), range = %d, config = 0x%02x, cb = 0x%02x\n",
		  *frequency / 16, *frequency % 16 * 100 / 16, *frequency,
		  i, *config, *cb);

	वापस i;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम simple_set_rf_input(काष्ठा dvb_frontend *fe,
				u8 *config, u8 *cb, अचिन्हित पूर्णांक rf)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;

	चयन (priv->type) अणु
	हाल TUNER_PHILIPS_TUV1236D:
		चयन (rf) अणु
		हाल 1:
			*cb |= 0x08;
			अवरोध;
		शेष:
			*cb &= ~0x08;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल TUNER_PHILIPS_FCV1236D:
		चयन (rf) अणु
		हाल 1:
			*cb |= 0x01;
			अवरोध;
		शेष:
			*cb &= ~0x01;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक simple_std_setup(काष्ठा dvb_frontend *fe,
			    काष्ठा analog_parameters *params,
			    u8 *config, u8 *cb)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	पूर्णांक rc;

	/* tv norm specअगरic stuff क्रम multi-norm tuners */
	चयन (priv->type) अणु
	हाल TUNER_PHILIPS_SECAM: /* FI1216MF */
		/* 0x01 -> ??? no change ??? */
		/* 0x02 -> PAL BDGHI / SECAM L */
		/* 0x04 -> ??? PAL others / SECAM others ??? */
		*cb &= ~0x03;
		अगर (params->std & V4L2_STD_SECAM_L)
			/* also valid क्रम V4L2_STD_SECAM */
			*cb |= PHILIPS_MF_SET_STD_L;
		अन्यथा अगर (params->std & V4L2_STD_SECAM_LC)
			*cb |= PHILIPS_MF_SET_STD_LC;
		अन्यथा /* V4L2_STD_B|V4L2_STD_GH */
			*cb |= PHILIPS_MF_SET_STD_BG;
		अवरोध;

	हाल TUNER_TEMIC_4046FM5:
		*cb &= ~0x0f;

		अगर (params->std & V4L2_STD_PAL_BG) अणु
			*cb |= TEMIC_SET_PAL_BG;

		पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_I) अणु
			*cb |= TEMIC_SET_PAL_I;

		पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_DK) अणु
			*cb |= TEMIC_SET_PAL_DK;

		पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_L) अणु
			*cb |= TEMIC_SET_PAL_L;

		पूर्ण
		अवरोध;

	हाल TUNER_PHILIPS_FQ1216ME:
		*cb &= ~0x0f;

		अगर (params->std & (V4L2_STD_PAL_BG|V4L2_STD_PAL_DK)) अणु
			*cb |= PHILIPS_SET_PAL_BGDK;

		पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_I) अणु
			*cb |= PHILIPS_SET_PAL_I;

		पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_L) अणु
			*cb |= PHILIPS_SET_PAL_L;

		पूर्ण
		अवरोध;

	हाल TUNER_PHILIPS_FCV1236D:
		/* 0x00 -> ATSC antenna input 1 */
		/* 0x01 -> ATSC antenna input 2 */
		/* 0x02 -> NTSC antenna input 1 */
		/* 0x03 -> NTSC antenna input 2 */
		*cb &= ~0x03;
		अगर (!(params->std & V4L2_STD_ATSC))
			*cb |= 2;
		अवरोध;

	हाल TUNER_MICROTUNE_4042FI5:
		/* Set the अक्षरge pump क्रम fast tuning */
		*config |= TUNER_CHARGE_PUMP;
		अवरोध;

	हाल TUNER_PHILIPS_TUV1236D:
	अणु
		काष्ठा tuner_i2c_props i2c = priv->i2c_props;
		/* 0x40 -> ATSC antenna input 1 */
		/* 0x48 -> ATSC antenna input 2 */
		/* 0x00 -> NTSC antenna input 1 */
		/* 0x08 -> NTSC antenna input 2 */
		u8 buffer[4] = अणु 0x14, 0x00, 0x17, 0x00पूर्ण;
		*cb &= ~0x40;
		अगर (params->std & V4L2_STD_ATSC) अणु
			*cb |= 0x40;
			buffer[1] = 0x04;
		पूर्ण
		/* set to the correct mode (analog or digital) */
		i2c.addr = 0x0a;
		rc = tuner_i2c_xfer_send(&i2c, &buffer[0], 2);
		अगर (2 != rc)
			tuner_warn("i2c i/o error: rc == %d (should be 2)\n",
				   rc);
		rc = tuner_i2c_xfer_send(&i2c, &buffer[2], 2);
		अगर (2 != rc)
			tuner_warn("i2c i/o error: rc == %d (should be 2)\n",
				   rc);
		अवरोध;
	पूर्ण
	पूर्ण
	अगर (atv_input[priv->nr])
		simple_set_rf_input(fe, config, cb, atv_input[priv->nr]);

	वापस 0;
पूर्ण

अटल पूर्णांक simple_set_aux_byte(काष्ठा dvb_frontend *fe, u8 config, u8 aux)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	पूर्णांक rc;
	u8 buffer[2];

	buffer[0] = (config & ~0x38) | 0x18;
	buffer[1] = aux;

	tuner_dbg("setting aux byte: 0x%02x 0x%02x\n", buffer[0], buffer[1]);

	rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 2);
	अगर (2 != rc)
		tuner_warn("i2c i/o error: rc == %d (should be 2)\n", rc);

	वापस rc == 2 ? 0 : rc;
पूर्ण

अटल पूर्णांक simple_post_tune(काष्ठा dvb_frontend *fe, u8 *buffer,
			    u16 भाग, u8 config, u8 cb)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	पूर्णांक rc;

	चयन (priv->type) अणु
	हाल TUNER_LG_TDVS_H06XF:
		simple_set_aux_byte(fe, config, 0x20);
		अवरोध;
	हाल TUNER_PHILIPS_FQ1216LME_MK3:
		simple_set_aux_byte(fe, config, 0x60); /* External AGC */
		अवरोध;
	हाल TUNER_MICROTUNE_4042FI5:
	अणु
		/* FIXME - this may also work क्रम other tuners */
		अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1);
		u8 status_byte = 0;

		/* Wait until the PLL locks */
		क्रम (;;) अणु
			अगर (समय_after(jअगरfies, समयout))
				वापस 0;
			rc = tuner_i2c_xfer_recv(&priv->i2c_props,
						 &status_byte, 1);
			अगर (1 != rc) अणु
				tuner_warn("i2c i/o read error: rc == %d (should be 1)\n",
					   rc);
				अवरोध;
			पूर्ण
			अगर (status_byte & TUNER_PLL_LOCKED)
				अवरोध;
			udelay(10);
		पूर्ण

		/* Set the अक्षरge pump क्रम optimized phase noise figure */
		config &= ~TUNER_CHARGE_PUMP;
		buffer[0] = (भाग>>8) & 0x7f;
		buffer[1] = भाग      & 0xff;
		buffer[2] = config;
		buffer[3] = cb;
		tuner_dbg("tv 0x%02x 0x%02x 0x%02x 0x%02x\n",
			  buffer[0], buffer[1], buffer[2], buffer[3]);

		rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 4);
		अगर (4 != rc)
			tuner_warn("i2c i/o error: rc == %d (should be 4)\n",
				   rc);
		अवरोध;
	पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक simple_radio_bandचयन(काष्ठा dvb_frontend *fe, u8 *buffer)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;

	चयन (priv->type) अणु
	हाल TUNER_TENA_9533_DI:
	हाल TUNER_YMEC_TVF_5533MF:
		tuner_dbg("This tuner doesn't have FM. Most cards have a TEA5767 for FM\n");
		वापस -EINVAL;
	हाल TUNER_PHILIPS_FM1216ME_MK3:
	हाल TUNER_PHILIPS_FM1236_MK3:
	हाल TUNER_PHILIPS_FMD1216ME_MK3:
	हाल TUNER_PHILIPS_FMD1216MEX_MK3:
	हाल TUNER_LG_NTSC_TAPE:
	हाल TUNER_PHILIPS_FM1256_IH3:
	हाल TUNER_TCL_MF02GIP_5N:
		buffer[3] = 0x19;
		अवरोध;
	हाल TUNER_PHILIPS_FM1216MK5:
		buffer[2] = 0x88;
		buffer[3] = 0x09;
		अवरोध;
	हाल TUNER_TNF_5335MF:
		buffer[3] = 0x11;
		अवरोध;
	हाल TUNER_LG_PAL_FM:
		buffer[3] = 0xa5;
		अवरोध;
	हाल TUNER_THOMSON_DTT761X:
		buffer[3] = 0x39;
		अवरोध;
	हाल TUNER_PHILIPS_FQ1216LME_MK3:
	हाल TUNER_PHILIPS_FQ1236_MK5:
		tuner_err("This tuner doesn't have FM\n");
		/* Set the low band क्रम sanity, since it covers 88-108 MHz */
		buffer[3] = 0x01;
		अवरोध;
	हाल TUNER_MICROTUNE_4049FM5:
	शेष:
		buffer[3] = 0xa4;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल पूर्णांक simple_set_tv_freq(काष्ठा dvb_frontend *fe,
			      काष्ठा analog_parameters *params)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	u8 config, cb;
	u16 भाग;
	u8 buffer[4];
	पूर्णांक rc, IFPCoff, i;
	क्रमागत param_type desired_type;
	काष्ठा tuner_params *t_params;

	/* IFPCoff = Video Intermediate Frequency - Vअगर:
		940  =16*58.75  NTSC/J (Japan)
		732  =16*45.75  M/N STD
		704  =16*44     ATSC (at DVB code)
		632  =16*39.50  I U.K.
		622.4=16*38.90  B/G D/K I, L STD
		592  =16*37.00  D China
		590  =16.36.875 B Australia
		543.2=16*33.95  L' STD
		171.2=16*10.70  FM Radio (at set_radio_freq)
	*/

	अगर (params->std == V4L2_STD_NTSC_M_JP) अणु
		IFPCoff      = 940;
		desired_type = TUNER_PARAM_TYPE_NTSC;
	पूर्ण अन्यथा अगर ((params->std & V4L2_STD_MN) &&
		  !(params->std & ~V4L2_STD_MN)) अणु
		IFPCoff      = 732;
		desired_type = TUNER_PARAM_TYPE_NTSC;
	पूर्ण अन्यथा अगर (params->std == V4L2_STD_SECAM_LC) अणु
		IFPCoff      = 543;
		desired_type = TUNER_PARAM_TYPE_SECAM;
	पूर्ण अन्यथा अणु
		IFPCoff      = 623;
		desired_type = TUNER_PARAM_TYPE_PAL;
	पूर्ण

	t_params = simple_tuner_params(fe, desired_type);

	i = simple_config_lookup(fe, t_params, &params->frequency,
				 &config, &cb);

	भाग = params->frequency + IFPCoff + offset;

	tuner_dbg("Freq= %d.%02d MHz, V_IF=%d.%02d MHz, Offset=%d.%02d MHz, div=%0d\n",
		  params->frequency / 16, params->frequency % 16 * 100 / 16,
		  IFPCoff / 16, IFPCoff % 16 * 100 / 16,
		  offset / 16, offset % 16 * 100 / 16, भाग);

	/* tv norm specअगरic stuff क्रम multi-norm tuners */
	simple_std_setup(fe, params, &config, &cb);

	अगर (t_params->cb_first_अगर_lower_freq && भाग < priv->last_भाग) अणु
		buffer[0] = config;
		buffer[1] = cb;
		buffer[2] = (भाग>>8) & 0x7f;
		buffer[3] = भाग      & 0xff;
	पूर्ण अन्यथा अणु
		buffer[0] = (भाग>>8) & 0x7f;
		buffer[1] = भाग      & 0xff;
		buffer[2] = config;
		buffer[3] = cb;
	पूर्ण
	priv->last_भाग = भाग;
	अगर (t_params->has_tda9887) अणु
		काष्ठा v4l2_priv_tun_config tda9887_cfg;
		पूर्णांक tda_config = 0;
		पूर्णांक is_secam_l = (params->std & (V4L2_STD_SECAM_L |
						 V4L2_STD_SECAM_LC)) &&
			!(params->std & ~(V4L2_STD_SECAM_L |
					  V4L2_STD_SECAM_LC));

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv  = &tda_config;

		अगर (params->std == V4L2_STD_SECAM_LC) अणु
			अगर (t_params->port1_active ^ t_params->port1_invert_क्रम_secam_lc)
				tda_config |= TDA9887_PORT1_ACTIVE;
			अगर (t_params->port2_active ^ t_params->port2_invert_क्रम_secam_lc)
				tda_config |= TDA9887_PORT2_ACTIVE;
		पूर्ण अन्यथा अणु
			अगर (t_params->port1_active)
				tda_config |= TDA9887_PORT1_ACTIVE;
			अगर (t_params->port2_active)
				tda_config |= TDA9887_PORT2_ACTIVE;
		पूर्ण
		अगर (t_params->पूर्णांकercarrier_mode)
			tda_config |= TDA9887_INTERCARRIER;
		अगर (is_secam_l) अणु
			अगर (i == 0 && t_params->शेष_top_secam_low)
				tda_config |= TDA9887_TOP(t_params->शेष_top_secam_low);
			अन्यथा अगर (i == 1 && t_params->शेष_top_secam_mid)
				tda_config |= TDA9887_TOP(t_params->शेष_top_secam_mid);
			अन्यथा अगर (t_params->शेष_top_secam_high)
				tda_config |= TDA9887_TOP(t_params->शेष_top_secam_high);
		पूर्ण अन्यथा अणु
			अगर (i == 0 && t_params->शेष_top_low)
				tda_config |= TDA9887_TOP(t_params->शेष_top_low);
			अन्यथा अगर (i == 1 && t_params->शेष_top_mid)
				tda_config |= TDA9887_TOP(t_params->शेष_top_mid);
			अन्यथा अगर (t_params->शेष_top_high)
				tda_config |= TDA9887_TOP(t_params->शेष_top_high);
		पूर्ण
		अगर (t_params->शेष_pll_gating_18)
			tda_config |= TDA9887_GATING_18;
		i2c_clients_command(priv->i2c_props.adap, TUNER_SET_CONFIG,
				    &tda9887_cfg);
	पूर्ण
	tuner_dbg("tv 0x%02x 0x%02x 0x%02x 0x%02x\n",
		  buffer[0], buffer[1], buffer[2], buffer[3]);

	rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 4);
	अगर (4 != rc)
		tuner_warn("i2c i/o error: rc == %d (should be 4)\n", rc);

	simple_post_tune(fe, &buffer[0], भाग, config, cb);

	वापस 0;
पूर्ण

अटल पूर्णांक simple_set_radio_freq(काष्ठा dvb_frontend *fe,
				 काष्ठा analog_parameters *params)
अणु
	काष्ठा tunertype *tun;
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	u8 buffer[4];
	u16 भाग;
	पूर्णांक rc, j;
	काष्ठा tuner_params *t_params;
	अचिन्हित पूर्णांक freq = params->frequency;
	bool mono = params->audmode == V4L2_TUNER_MODE_MONO;

	tun = priv->tun;

	क्रम (j = tun->count-1; j > 0; j--)
		अगर (tun->params[j].type == TUNER_PARAM_TYPE_RADIO)
			अवरोध;
	/* शेष t_params (j=0) will be used अगर desired type wasn't found */
	t_params = &tun->params[j];

	/* Select Radio 1st IF used */
	चयन (t_params->radio_अगर) अणु
	हाल 0: /* 10.7 MHz */
		freq += (अचिन्हित पूर्णांक)(10.7*16000);
		अवरोध;
	हाल 1: /* 33.3 MHz */
		freq += (अचिन्हित पूर्णांक)(33.3*16000);
		अवरोध;
	हाल 2: /* 41.3 MHz */
		freq += (अचिन्हित पूर्णांक)(41.3*16000);
		अवरोध;
	शेष:
		tuner_warn("Unsupported radio_if value %d\n",
			   t_params->radio_अगर);
		वापस 0;
	पूर्ण

	buffer[2] = (t_params->ranges[0].config & ~TUNER_RATIO_MASK) |
		    TUNER_RATIO_SELECT_50; /* 50 kHz step */

	/* Bandचयन byte */
	अगर (simple_radio_bandचयन(fe, &buffer[0]))
		वापस 0;

	/* Convert from 1/16 kHz V4L steps to 1/20 MHz (=50 kHz) PLL steps
	   freq * (1 Mhz / 16000 V4L steps) * (20 PLL steps / 1 MHz) =
	   freq * (1/800) */
	भाग = (freq + 400) / 800;

	अगर (t_params->cb_first_अगर_lower_freq && भाग < priv->last_भाग) अणु
		buffer[0] = buffer[2];
		buffer[1] = buffer[3];
		buffer[2] = (भाग>>8) & 0x7f;
		buffer[3] = भाग      & 0xff;
	पूर्ण अन्यथा अणु
		buffer[0] = (भाग>>8) & 0x7f;
		buffer[1] = भाग      & 0xff;
	पूर्ण

	tuner_dbg("radio 0x%02x 0x%02x 0x%02x 0x%02x\n",
	       buffer[0], buffer[1], buffer[2], buffer[3]);
	priv->last_भाग = भाग;

	अगर (t_params->has_tda9887) अणु
		पूर्णांक config = 0;
		काष्ठा v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &config;

		अगर (t_params->port1_active &&
		    !t_params->port1_fm_high_sensitivity)
			config |= TDA9887_PORT1_ACTIVE;
		अगर (t_params->port2_active &&
		    !t_params->port2_fm_high_sensitivity)
			config |= TDA9887_PORT2_ACTIVE;
		अगर (t_params->पूर्णांकercarrier_mode)
			config |= TDA9887_INTERCARRIER;
		अगर (t_params->port1_set_क्रम_fm_mono && mono)
			config &= ~TDA9887_PORT1_ACTIVE;
		अगर (t_params->fm_gain_normal)
			config |= TDA9887_GAIN_NORMAL;
		अगर (t_params->radio_अगर == 2)
			config |= TDA9887_RIF_41_3;
		i2c_clients_command(priv->i2c_props.adap, TUNER_SET_CONFIG,
				    &tda9887_cfg);
	पूर्ण
	rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 4);
	अगर (4 != rc)
		tuner_warn("i2c i/o error: rc == %d (should be 4)\n", rc);

	/* Write AUX byte */
	चयन (priv->type) अणु
	हाल TUNER_PHILIPS_FM1216ME_MK3:
		buffer[2] = 0x98;
		buffer[3] = 0x20; /* set TOP AGC */
		rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 4);
		अगर (4 != rc)
			tuner_warn("i2c i/o error: rc == %d (should be 4)\n", rc);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक simple_set_params(काष्ठा dvb_frontend *fe,
			     काष्ठा analog_parameters *params)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	पूर्णांक ret = -EINVAL;

	अगर (priv->i2c_props.adap == शून्य)
		वापस -EINVAL;

	चयन (params->mode) अणु
	हाल V4L2_TUNER_RADIO:
		priv->radio_mode = true;
		ret = simple_set_radio_freq(fe, params);
		priv->frequency = params->frequency * 125 / 2;
		अवरोध;
	हाल V4L2_TUNER_ANALOG_TV:
	हाल V4L2_TUNER_DIGITAL_TV:
		priv->radio_mode = false;
		ret = simple_set_tv_freq(fe, params);
		priv->frequency = params->frequency * 62500;
		अवरोध;
	पूर्ण
	priv->bandwidth = 0;

	वापस ret;
पूर्ण

अटल व्योम simple_set_dvb(काष्ठा dvb_frontend *fe, u8 *buf,
			   स्थिर u32 delsys,
			   स्थिर u32 frequency,
			   स्थिर u32 bandwidth)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;

	चयन (priv->type) अणु
	हाल TUNER_PHILIPS_FMD1216ME_MK3:
	हाल TUNER_PHILIPS_FMD1216MEX_MK3:
		अगर (bandwidth == 8000000 &&
		    frequency >= 158870000)
			buf[3] |= 0x08;
		अवरोध;
	हाल TUNER_PHILIPS_TD1316:
		/* determine band */
		buf[3] |= (frequency < 161000000) ? 1 :
			  (frequency < 444000000) ? 2 : 4;

		/* setup PLL filter */
		अगर (bandwidth == 8000000)
			buf[3] |= 1 << 3;
		अवरोध;
	हाल TUNER_PHILIPS_TUV1236D:
	हाल TUNER_PHILIPS_FCV1236D:
	अणु
		अचिन्हित पूर्णांक new_rf;

		अगर (dtv_input[priv->nr])
			new_rf = dtv_input[priv->nr];
		अन्यथा
			चयन (delsys) अणु
			हाल SYS_DVBC_ANNEX_B:
				new_rf = 1;
				अवरोध;
			हाल SYS_ATSC:
			शेष:
				new_rf = 0;
				अवरोध;
			पूर्ण
		simple_set_rf_input(fe, &buf[2], &buf[3], new_rf);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 simple_dvb_configure(काष्ठा dvb_frontend *fe, u8 *buf,
				स्थिर u32 delsys,
				स्थिर u32 freq,
				स्थिर u32 bw)
अणु
	/* This function वापसs the tuned frequency on success, 0 on error */
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	काष्ठा tunertype *tun = priv->tun;
	काष्ठा tuner_params *t_params;
	u8 config, cb;
	u32 भाग;
	पूर्णांक ret;
	u32 frequency = freq / 62500;

	अगर (!tun->stepsize) अणु
		/* tuner-core was loaded beक्रमe the digital tuner was
		 * configured and somehow picked the wrong tuner type */
		tuner_err("attempt to treat tuner %d (%s) as digital tuner without stepsize defined.\n",
			  priv->type, priv->tun->name);
		वापस 0; /* failure */
	पूर्ण

	t_params = simple_tuner_params(fe, TUNER_PARAM_TYPE_DIGITAL);
	ret = simple_config_lookup(fe, t_params, &frequency, &config, &cb);
	अगर (ret < 0)
		वापस 0; /* failure */

	भाग = ((frequency + t_params->अगरfreq) * 62500 + offset +
	       tun->stepsize/2) / tun->stepsize;

	buf[0] = भाग >> 8;
	buf[1] = भाग & 0xff;
	buf[2] = config;
	buf[3] = cb;

	simple_set_dvb(fe, buf, delsys, freq, bw);

	tuner_dbg("%s: div=%d | buf=0x%02x,0x%02x,0x%02x,0x%02x\n",
		  tun->name, भाग, buf[0], buf[1], buf[2], buf[3]);

	/* calculate the frequency we set it to */
	वापस (भाग * tun->stepsize) - t_params->अगरfreq;
पूर्ण

अटल पूर्णांक simple_dvb_calc_regs(काष्ठा dvb_frontend *fe,
				u8 *buf, पूर्णांक buf_len)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_प्रणाली;
	u32 bw = c->bandwidth_hz;
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	u32 frequency;

	अगर (buf_len < 5)
		वापस -EINVAL;

	frequency = simple_dvb_configure(fe, buf+1, delsys, c->frequency, bw);
	अगर (frequency == 0)
		वापस -EINVAL;

	buf[0] = priv->i2c_props.addr;

	priv->frequency = frequency;
	priv->bandwidth = c->bandwidth_hz;

	वापस 5;
पूर्ण

अटल पूर्णांक simple_dvb_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_प्रणाली;
	u32 bw = c->bandwidth_hz;
	u32 freq = c->frequency;
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	u32 frequency;
	u32 prev_freq, prev_bw;
	पूर्णांक ret;
	u8 buf[5];

	अगर (priv->i2c_props.adap == शून्य)
		वापस -EINVAL;

	prev_freq = priv->frequency;
	prev_bw   = priv->bandwidth;

	frequency = simple_dvb_configure(fe, buf+1, delsys, freq, bw);
	अगर (frequency == 0)
		वापस -EINVAL;

	buf[0] = priv->i2c_props.addr;

	priv->frequency = frequency;
	priv->bandwidth = bw;

	/* put analog demod in standby when tuning digital */
	अगर (fe->ops.analog_ops.standby)
		fe->ops.analog_ops.standby(fe);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* buf[0] contains the i2c address, but *
	 * we alपढ़ोy have it in i2c_props.addr */
	ret = tuner_i2c_xfer_send(&priv->i2c_props, buf+1, 4);
	अगर (ret != 4)
		जाओ fail;

	वापस 0;
fail:
	/* calc_regs sets frequency and bandwidth. अगर we failed, unset them */
	priv->frequency = prev_freq;
	priv->bandwidth = prev_bw;

	वापस ret;
पूर्ण

अटल पूर्णांक simple_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;

	अगर (priv->i2c_props.adap == शून्य)
		वापस -EINVAL;

	अगर (priv->tun->initdata) अणु
		पूर्णांक ret;

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = tuner_i2c_xfer_send(&priv->i2c_props,
					  priv->tun->initdata + 1,
					  priv->tun->initdata[0]);
		अगर (ret != priv->tun->initdata[0])
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक simple_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;

	अगर (priv->i2c_props.adap == शून्य)
		वापस -EINVAL;

	अगर (priv->tun->sleepdata) अणु
		पूर्णांक ret;

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = tuner_i2c_xfer_send(&priv->i2c_props,
					  priv->tun->sleepdata + 1,
					  priv->tun->sleepdata[0]);
		अगर (ret != priv->tun->sleepdata[0])
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम simple_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;

	mutex_lock(&tuner_simple_list_mutex);

	अगर (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&tuner_simple_list_mutex);

	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक simple_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक simple_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा tuner_simple_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops simple_tuner_ops = अणु
	.init              = simple_init,
	.sleep             = simple_sleep,
	.set_analog_params = simple_set_params,
	.set_params        = simple_dvb_set_params,
	.calc_regs         = simple_dvb_calc_regs,
	.release           = simple_release,
	.get_frequency     = simple_get_frequency,
	.get_bandwidth     = simple_get_bandwidth,
	.get_status        = simple_get_status,
	.get_rf_strength   = simple_get_rf_strength,
पूर्ण;

काष्ठा dvb_frontend *simple_tuner_attach(काष्ठा dvb_frontend *fe,
					 काष्ठा i2c_adapter *i2c_adap,
					 u8 i2c_addr,
					 अचिन्हित पूर्णांक type)
अणु
	काष्ठा tuner_simple_priv *priv = शून्य;
	पूर्णांक instance;

	अगर (type >= tuner_count) अणु
		prपूर्णांकk(KERN_WARNING "%s: invalid tuner type: %d (max: %d)\n",
		       __func__, type, tuner_count-1);
		वापस शून्य;
	पूर्ण

	/* If i2c_adap is set, check that the tuner is at the correct address.
	 * Otherwise, अगर i2c_adap is शून्य, the tuner will be programmed directly
	 * by the digital demod via calc_regs.
	 */
	अगर (i2c_adap != शून्य) अणु
		u8 b[1];
		काष्ठा i2c_msg msg = अणु
			.addr = i2c_addr, .flags = I2C_M_RD,
			.buf = b, .len = 1,
		पूर्ण;

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		अगर (1 != i2c_transfer(i2c_adap, &msg, 1))
			prपूर्णांकk(KERN_WARNING "tuner-simple %d-%04x: unable to probe %s, proceeding anyway.",
			       i2c_adapter_id(i2c_adap), i2c_addr,
			       tuners[type].name);

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	mutex_lock(&tuner_simple_list_mutex);

	instance = hybrid_tuner_request_state(काष्ठा tuner_simple_priv, priv,
					      hybrid_tuner_instance_list,
					      i2c_adap, i2c_addr,
					      "tuner-simple");
	चयन (instance) अणु
	हाल 0:
		mutex_unlock(&tuner_simple_list_mutex);
		वापस शून्य;
	हाल 1:
		fe->tuner_priv = priv;

		priv->type = type;
		priv->tun  = &tuners[type];
		priv->nr   = simple_devcount++;
		अवरोध;
	शेष:
		fe->tuner_priv = priv;
		अवरोध;
	पूर्ण

	mutex_unlock(&tuner_simple_list_mutex);

	स_नकल(&fe->ops.tuner_ops, &simple_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	अगर (type != priv->type)
		tuner_warn("couldn't set type to %d. Using %d (%s) instead\n",
			    type, priv->type, priv->tun->name);
	अन्यथा
		tuner_info("type set to %d (%s)\n",
			   priv->type, priv->tun->name);

	अगर ((debug) || ((atv_input[priv->nr] > 0) ||
			(dtv_input[priv->nr] > 0))) अणु
		अगर (0 == atv_input[priv->nr])
			tuner_info("tuner %d atv rf input will be autoselected\n",
				   priv->nr);
		अन्यथा
			tuner_info("tuner %d atv rf input will be set to input %d (insmod option)\n",
				   priv->nr, atv_input[priv->nr]);
		अगर (0 == dtv_input[priv->nr])
			tuner_info("tuner %d dtv rf input will be autoselected\n",
				   priv->nr);
		अन्यथा
			tuner_info("tuner %d dtv rf input will be set to input %d (insmod option)\n",
				   priv->nr, dtv_input[priv->nr]);
	पूर्ण

	strscpy(fe->ops.tuner_ops.info.name, priv->tun->name,
		माप(fe->ops.tuner_ops.info.name));

	वापस fe;
पूर्ण
EXPORT_SYMBOL_GPL(simple_tuner_attach);

MODULE_DESCRIPTION("Simple 4-control-bytes style tuner driver");
MODULE_AUTHOR("Ralph Metzler, Gerd Knorr, Gunther Mayer");
MODULE_LICENSE("GPL");
