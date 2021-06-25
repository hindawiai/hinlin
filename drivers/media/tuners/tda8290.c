<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

   i2c tv tuner chip device driver
   controls the philips tda8290+75 tuner chip combo.


   This "tda8290" module was split apart from the original "tuner" module.
*/

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश "tuner-i2c.h"
#समावेश "tda8290.h"
#समावेश "tda827x.h"
#समावेश "tda18271.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

अटल पूर्णांक deemphasis_50;
module_param(deemphasis_50, पूर्णांक, 0644);
MODULE_PARM_DESC(deemphasis_50, "0 - 75us deemphasis; 1 - 50us deemphasis");

/* ---------------------------------------------------------------------- */

काष्ठा tda8290_priv अणु
	काष्ठा tuner_i2c_props i2c_props;

	अचिन्हित अक्षर tda8290_easy_mode;

	अचिन्हित अक्षर tda827x_addr;

	अचिन्हित अक्षर ver;
#घोषणा TDA8290   1
#घोषणा TDA8295   2
#घोषणा TDA8275   4
#घोषणा TDA8275A  8
#घोषणा TDA18271 16

	काष्ठा tda827x_config cfg;
	काष्ठा tda18271_std_map *tda18271_std_map;
पूर्ण;

/*---------------------------------------------------------------------*/

अटल पूर्णांक tda8290_i2c_bridge(काष्ठा dvb_frontend *fe, पूर्णांक बंद)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अटल अचिन्हित अक्षर  enable[2] = अणु 0x21, 0xC0 पूर्ण;
	अटल अचिन्हित अक्षर disable[2] = अणु 0x21, 0x00 पूर्ण;
	अचिन्हित अक्षर *msg;

	अगर (बंद) अणु
		msg = enable;
		tuner_i2c_xfer_send(&priv->i2c_props, msg, 2);
		/* let the bridge stabilize */
		msleep(20);
	पूर्ण अन्यथा अणु
		msg = disable;
		tuner_i2c_xfer_send(&priv->i2c_props, msg, 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda8295_i2c_bridge(काष्ठा dvb_frontend *fe, पूर्णांक बंद)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अटल अचिन्हित अक्षर  enable[2] = अणु 0x45, 0xc1 पूर्ण;
	अटल अचिन्हित अक्षर disable[2] = अणु 0x46, 0x00 पूर्ण;
	अटल अचिन्हित अक्षर buf[3] = अणु 0x45, 0x01, 0x00 पूर्ण;
	अचिन्हित अक्षर *msg;

	अगर (बंद) अणु
		msg = enable;
		tuner_i2c_xfer_send(&priv->i2c_props, msg, 2);
		/* let the bridge stabilize */
		msleep(20);
	पूर्ण अन्यथा अणु
		msg = disable;
		tuner_i2c_xfer_send_recv(&priv->i2c_props, msg, 1, &msg[1], 1);

		buf[2] = msg[1];
		buf[2] &= ~0x04;
		tuner_i2c_xfer_send(&priv->i2c_props, buf, 3);
		msleep(5);

		msg[1] |= 0x04;
		tuner_i2c_xfer_send(&priv->i2c_props, msg, 2);
	पूर्ण

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------*/

अटल व्योम set_audio(काष्ठा dvb_frontend *fe,
		      काष्ठा analog_parameters *params)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	अक्षर* mode;

	अगर (params->std & V4L2_STD_MN) अणु
		priv->tda8290_easy_mode = 0x01;
		mode = "MN";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_B) अणु
		priv->tda8290_easy_mode = 0x02;
		mode = "B";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_GH) अणु
		priv->tda8290_easy_mode = 0x04;
		mode = "GH";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_I) अणु
		priv->tda8290_easy_mode = 0x08;
		mode = "I";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_DK) अणु
		priv->tda8290_easy_mode = 0x10;
		mode = "DK";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_L) अणु
		priv->tda8290_easy_mode = 0x20;
		mode = "L";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_LC) अणु
		priv->tda8290_easy_mode = 0x40;
		mode = "LC";
	पूर्ण अन्यथा अणु
		priv->tda8290_easy_mode = 0x10;
		mode = "xx";
	पूर्ण

	अगर (params->mode == V4L2_TUNER_RADIO) अणु
		/* Set TDA8295 to FM radio; Start TDA8290 with MN values */
		priv->tda8290_easy_mode = (priv->ver & TDA8295) ? 0x80 : 0x01;
		tuner_dbg("setting to radio FM\n");
	पूर्ण अन्यथा अणु
		tuner_dbg("setting tda829x to system %s\n", mode);
	पूर्ण
पूर्ण

अटल काष्ठा अणु
	अचिन्हित अक्षर seq[2];
पूर्ण fm_mode[] = अणु
	अणु अणु 0x01, 0x81पूर्ण पूर्ण,	/* Put device पूर्णांकo expert mode */
	अणु अणु 0x03, 0x48पूर्ण पूर्ण,	/* Disable NOTCH and VIDEO filters */
	अणु अणु 0x04, 0x04पूर्ण पूर्ण,	/* Disable color carrier filter (SSIF) */
	अणु अणु 0x05, 0x04पूर्ण पूर्ण,	/* ADC headroom */
	अणु अणु 0x06, 0x10पूर्ण पूर्ण,	/* group delay flat */

	अणु अणु 0x07, 0x00पूर्ण पूर्ण,	/* use the same radio DTO values as a tda8295 */
	अणु अणु 0x08, 0x00पूर्ण पूर्ण,
	अणु अणु 0x09, 0x80पूर्ण पूर्ण,
	अणु अणु 0x0a, 0xdaपूर्ण पूर्ण,
	अणु अणु 0x0b, 0x4bपूर्ण पूर्ण,
	अणु अणु 0x0c, 0x68पूर्ण पूर्ण,

	अणु अणु 0x0d, 0x00पूर्ण पूर्ण,	/* PLL off, no video carrier detect */
	अणु अणु 0x14, 0x00पूर्ण पूर्ण,	/* disable स्वतः mute अगर no video */
पूर्ण;

अटल व्योम tda8290_set_params(काष्ठा dvb_frontend *fe,
			       काष्ठा analog_parameters *params)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अटल अचिन्हित अक्षर soft_reset[]  = अणु 0x00, 0x00 पूर्ण;
	अचिन्हित अक्षर easy_mode[]   = अणु 0x01, priv->tda8290_easy_mode पूर्ण;
	अटल अचिन्हित अक्षर expert_mode[] = अणु 0x01, 0x80 पूर्ण;
	अटल अचिन्हित अक्षर agc_out_on[]  = अणु 0x02, 0x00 पूर्ण;
	अटल अचिन्हित अक्षर gainset_off[] = अणु 0x28, 0x14 पूर्ण;
	अटल अचिन्हित अक्षर अगर_agc_spd[]  = अणु 0x0f, 0x88 पूर्ण;
	अटल अचिन्हित अक्षर adc_head_6[]  = अणु 0x05, 0x04 पूर्ण;
	अटल अचिन्हित अक्षर adc_head_9[]  = अणु 0x05, 0x02 पूर्ण;
	अटल अचिन्हित अक्षर adc_head_12[] = अणु 0x05, 0x01 पूर्ण;
	अटल अचिन्हित अक्षर pll_bw_nom[]  = अणु 0x0d, 0x47 पूर्ण;
	अटल अचिन्हित अक्षर pll_bw_low[]  = अणु 0x0d, 0x27 पूर्ण;
	अटल अचिन्हित अक्षर gainset_2[]   = अणु 0x28, 0x64 पूर्ण;
	अटल अचिन्हित अक्षर agc_rst_on[]  = अणु 0x0e, 0x0b पूर्ण;
	अटल अचिन्हित अक्षर agc_rst_off[] = अणु 0x0e, 0x09 पूर्ण;
	अटल अचिन्हित अक्षर अगर_agc_set[]  = अणु 0x0f, 0x81 पूर्ण;
	अटल अचिन्हित अक्षर addr_adc_sat  = 0x1a;
	अटल अचिन्हित अक्षर addr_agc_stat = 0x1d;
	अटल अचिन्हित अक्षर addr_pll_stat = 0x1b;
	अटल अचिन्हित अक्षर adc_sat = 0, agc_stat = 0,
		      pll_stat;
	पूर्णांक i;

	set_audio(fe, params);

	अगर (priv->cfg.config)
		tuner_dbg("tda827xa config is 0x%02x\n", priv->cfg.config);
	tuner_i2c_xfer_send(&priv->i2c_props, easy_mode, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, agc_out_on, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, soft_reset, 2);
	msleep(1);

	अगर (params->mode == V4L2_TUNER_RADIO) अणु
		अचिन्हित अक्षर deemphasis[]  = अणु 0x13, 1 पूर्ण;

		/* FIXME: allow using a dअगरferent deemphasis */

		अगर (deemphasis_50)
			deemphasis[1] = 2;

		क्रम (i = 0; i < ARRAY_SIZE(fm_mode); i++)
			tuner_i2c_xfer_send(&priv->i2c_props, fm_mode[i].seq, 2);

		tuner_i2c_xfer_send(&priv->i2c_props, deemphasis, 2);
	पूर्ण अन्यथा अणु
		expert_mode[1] = priv->tda8290_easy_mode + 0x80;
		tuner_i2c_xfer_send(&priv->i2c_props, expert_mode, 2);
		tuner_i2c_xfer_send(&priv->i2c_props, gainset_off, 2);
		tuner_i2c_xfer_send(&priv->i2c_props, अगर_agc_spd, 2);
		अगर (priv->tda8290_easy_mode & 0x60)
			tuner_i2c_xfer_send(&priv->i2c_props, adc_head_9, 2);
		अन्यथा
			tuner_i2c_xfer_send(&priv->i2c_props, adc_head_6, 2);
		tuner_i2c_xfer_send(&priv->i2c_props, pll_bw_nom, 2);
	पूर्ण


	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);

	अगर (fe->ops.tuner_ops.set_analog_params)
		fe->ops.tuner_ops.set_analog_params(fe, params);

	क्रम (i = 0; i < 3; i++) अणु
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_pll_stat, 1, &pll_stat, 1);
		अगर (pll_stat & 0x80) अणु
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_adc_sat, 1,
						 &adc_sat, 1);
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_agc_stat, 1,
						 &agc_stat, 1);
			tuner_dbg("tda8290 is locked, AGC: %d\n", agc_stat);
			अवरोध;
		पूर्ण अन्यथा अणु
			tuner_dbg("tda8290 not locked, no signal?\n");
			msleep(100);
		पूर्ण
	पूर्ण
	/* adjust headroom resp. gain */
	अगर ((agc_stat > 115) || (!(pll_stat & 0x80) && (adc_sat < 20))) अणु
		tuner_dbg("adjust gain, step 1. Agc: %d, ADC stat: %d, lock: %d\n",
			   agc_stat, adc_sat, pll_stat & 0x80);
		tuner_i2c_xfer_send(&priv->i2c_props, gainset_2, 2);
		msleep(100);
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_agc_stat, 1, &agc_stat, 1);
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_pll_stat, 1, &pll_stat, 1);
		अगर ((agc_stat > 115) || !(pll_stat & 0x80)) अणु
			tuner_dbg("adjust gain, step 2. Agc: %d, lock: %d\n",
				   agc_stat, pll_stat & 0x80);
			अगर (priv->cfg.agcf)
				priv->cfg.agcf(fe);
			msleep(100);
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_agc_stat, 1,
						 &agc_stat, 1);
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_pll_stat, 1,
						 &pll_stat, 1);
			अगर((agc_stat > 115) || !(pll_stat & 0x80)) अणु
				tuner_dbg("adjust gain, step 3. Agc: %d\n", agc_stat);
				tuner_i2c_xfer_send(&priv->i2c_props, adc_head_12, 2);
				tuner_i2c_xfer_send(&priv->i2c_props, pll_bw_low, 2);
				msleep(100);
			पूर्ण
		पूर्ण
	पूर्ण

	/* l/ l' deadlock? */
	अगर(priv->tda8290_easy_mode & 0x60) अणु
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_adc_sat, 1,
					 &adc_sat, 1);
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_pll_stat, 1,
					 &pll_stat, 1);
		अगर ((adc_sat > 20) || !(pll_stat & 0x80)) अणु
			tuner_dbg("trying to resolve SECAM L deadlock\n");
			tuner_i2c_xfer_send(&priv->i2c_props, agc_rst_on, 2);
			msleep(40);
			tuner_i2c_xfer_send(&priv->i2c_props, agc_rst_off, 2);
		पूर्ण
	पूर्ण

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);
	tuner_i2c_xfer_send(&priv->i2c_props, अगर_agc_set, 2);
पूर्ण

/*---------------------------------------------------------------------*/

अटल व्योम tda8295_घातer(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	अचिन्हित अक्षर buf[] = अणु 0x30, 0x00 पूर्ण; /* clb_stdbt */

	tuner_i2c_xfer_send_recv(&priv->i2c_props, &buf[0], 1, &buf[1], 1);

	अगर (enable)
		buf[1] = 0x01;
	अन्यथा
		buf[1] = 0x03;

	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2);
पूर्ण

अटल व्योम tda8295_set_easy_mode(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	अचिन्हित अक्षर buf[] = अणु 0x01, 0x00 पूर्ण;

	tuner_i2c_xfer_send_recv(&priv->i2c_props, &buf[0], 1, &buf[1], 1);

	अगर (enable)
		buf[1] = 0x01; /* rising edge sets regs 0x02 - 0x23 */
	अन्यथा
		buf[1] = 0x00; /* reset active bit */

	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2);
पूर्ण

अटल व्योम tda8295_set_video_std(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	अचिन्हित अक्षर buf[] = अणु 0x00, priv->tda8290_easy_mode पूर्ण;

	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2);

	tda8295_set_easy_mode(fe, 1);
	msleep(20);
	tda8295_set_easy_mode(fe, 0);
पूर्ण

/*---------------------------------------------------------------------*/

अटल व्योम tda8295_agc1_out(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	अचिन्हित अक्षर buf[] = अणु 0x02, 0x00 पूर्ण; /* DIV_FUNC */

	tuner_i2c_xfer_send_recv(&priv->i2c_props, &buf[0], 1, &buf[1], 1);

	अगर (enable)
		buf[1] &= ~0x40;
	अन्यथा
		buf[1] |= 0x40;

	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2);
पूर्ण

अटल व्योम tda8295_agc2_out(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	अचिन्हित अक्षर set_gpio_cf[]    = अणु 0x44, 0x00 पूर्ण;
	अचिन्हित अक्षर set_gpio_val[]   = अणु 0x46, 0x00 पूर्ण;

	tuner_i2c_xfer_send_recv(&priv->i2c_props,
				 &set_gpio_cf[0], 1, &set_gpio_cf[1], 1);
	tuner_i2c_xfer_send_recv(&priv->i2c_props,
				 &set_gpio_val[0], 1, &set_gpio_val[1], 1);

	set_gpio_cf[1] &= 0xf0; /* clear GPIO_0 bits 3-0 */

	अगर (enable) अणु
		set_gpio_cf[1]  |= 0x01; /* config GPIO_0 as Open Drain Out */
		set_gpio_val[1] &= 0xfe; /* set GPIO_0 pin low */
	पूर्ण
	tuner_i2c_xfer_send(&priv->i2c_props, set_gpio_cf, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_gpio_val, 2);
पूर्ण

अटल पूर्णांक tda8295_has_संकेत(काष्ठा dvb_frontend *fe, u16 *संकेत)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अचिन्हित अक्षर hvpll_stat = 0x26;
	अचिन्हित अक्षर ret;

	tuner_i2c_xfer_send_recv(&priv->i2c_props, &hvpll_stat, 1, &ret, 1);
	*संकेत = (ret & 0x01) ? 65535 : 0;
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------*/

अटल व्योम tda8295_set_params(काष्ठा dvb_frontend *fe,
			       काष्ठा analog_parameters *params)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	u16 संकेत = 0;
	अचिन्हित अक्षर blanking_mode[]     = अणु 0x1d, 0x00 पूर्ण;

	set_audio(fe, params);

	tuner_dbg("%s: freq = %d\n", __func__, params->frequency);

	tda8295_घातer(fe, 1);
	tda8295_agc1_out(fe, 1);

	tuner_i2c_xfer_send_recv(&priv->i2c_props,
				 &blanking_mode[0], 1, &blanking_mode[1], 1);

	tda8295_set_video_std(fe);

	blanking_mode[1] = 0x03;
	tuner_i2c_xfer_send(&priv->i2c_props, blanking_mode, 2);
	msleep(20);

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);

	अगर (fe->ops.tuner_ops.set_analog_params)
		fe->ops.tuner_ops.set_analog_params(fe, params);

	अगर (priv->cfg.agcf)
		priv->cfg.agcf(fe);

	tda8295_has_संकेत(fe, &संकेत);
	अगर (संकेत)
		tuner_dbg("tda8295 is locked\n");
	अन्यथा
		tuner_dbg("tda8295 not locked, no signal?\n");

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);
पूर्ण

/*---------------------------------------------------------------------*/

अटल पूर्णांक tda8290_has_संकेत(काष्ठा dvb_frontend *fe, u16 *संकेत)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अचिन्हित अक्षर i2c_get_afc[1] = अणु 0x1B पूर्ण;
	अचिन्हित अक्षर afc = 0;

	tuner_i2c_xfer_send_recv(&priv->i2c_props,
				 i2c_get_afc, ARRAY_SIZE(i2c_get_afc), &afc, 1);
	*संकेत = (afc & 0x80) ? 65535 : 0;
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------*/

अटल व्योम tda8290_standby(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अटल अचिन्हित अक्षर cb1[] = अणु 0x30, 0xD0 पूर्ण;
	अटल अचिन्हित अक्षर tda8290_standby[] = अणु 0x00, 0x02 पूर्ण;
	अटल अचिन्हित अक्षर tda8290_agc_tri[] = अणु 0x02, 0x20 पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = priv->tda827x_addr, .flags=0, .buf=cb1, .len = 2पूर्ण;

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);
	अगर (priv->ver & TDA8275A)
		cb1[1] = 0x90;
	i2c_transfer(priv->i2c_props.adap, &msg, 1);
	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);
	tuner_i2c_xfer_send(&priv->i2c_props, tda8290_agc_tri, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, tda8290_standby, 2);
पूर्ण

अटल व्योम tda8295_standby(काष्ठा dvb_frontend *fe)
अणु
	tda8295_agc1_out(fe, 0); /* Put AGC in tri-state */

	tda8295_घातer(fe, 0);
पूर्ण

अटल व्योम tda8290_init_अगर(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अटल अचिन्हित अक्षर set_VS[] = अणु 0x30, 0x6F पूर्ण;
	अटल अचिन्हित अक्षर set_GP00_CF[] = अणु 0x20, 0x01 पूर्ण;
	अटल अचिन्हित अक्षर set_GP01_CF[] = अणु 0x20, 0x0B पूर्ण;

	अगर ((priv->cfg.config == TDA8290_LNA_GP0_HIGH_ON) ||
	    (priv->cfg.config == TDA8290_LNA_GP0_HIGH_OFF))
		tuner_i2c_xfer_send(&priv->i2c_props, set_GP00_CF, 2);
	अन्यथा
		tuner_i2c_xfer_send(&priv->i2c_props, set_GP01_CF, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_VS, 2);
पूर्ण

अटल व्योम tda8295_init_अगर(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	अटल अचिन्हित अक्षर set_adc_ctl[]       = अणु 0x33, 0x14 पूर्ण;
	अटल अचिन्हित अक्षर set_adc_ctl2[]      = अणु 0x34, 0x00 पूर्ण;
	अटल अचिन्हित अक्षर set_pll_reg6[]      = अणु 0x3e, 0x63 पूर्ण;
	अटल अचिन्हित अक्षर set_pll_reg0[]      = अणु 0x38, 0x23 पूर्ण;
	अटल अचिन्हित अक्षर set_pll_reg7[]      = अणु 0x3f, 0x01 पूर्ण;
	अटल अचिन्हित अक्षर set_pll_reg10[]     = अणु 0x42, 0x61 पूर्ण;
	अटल अचिन्हित अक्षर set_gpio_reg0[]     = अणु 0x44, 0x0b पूर्ण;

	tda8295_घातer(fe, 1);

	tda8295_set_easy_mode(fe, 0);
	tda8295_set_video_std(fe);

	tuner_i2c_xfer_send(&priv->i2c_props, set_adc_ctl, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_adc_ctl2, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg6, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg0, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg7, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg10, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_gpio_reg0, 2);

	tda8295_agc1_out(fe, 0);
	tda8295_agc2_out(fe, 0);
पूर्ण

अटल व्योम tda8290_init_tuner(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	अटल अचिन्हित अक्षर tda8275_init[]  =
		अणु 0x00, 0x00, 0x00, 0x40, 0xdC, 0x04, 0xAf,
		  0x3F, 0x2A, 0x04, 0xFF, 0x00, 0x00, 0x40 पूर्ण;
	अटल अचिन्हित अक्षर tda8275a_init[] =
		 अणु 0x00, 0x00, 0x00, 0x00, 0xdC, 0x05, 0x8b,
		   0x0c, 0x04, 0x20, 0xFF, 0x00, 0x00, 0x4b पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = priv->tda827x_addr, .flags=0,
			      .buf=tda8275_init, .len = 14पूर्ण;
	अगर (priv->ver & TDA8275A)
		msg.buf = tda8275a_init;

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(priv->i2c_props.adap, &msg, 1);
	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);
पूर्ण

/*---------------------------------------------------------------------*/

अटल व्योम tda829x_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;

	/* only try to release the tuner अगर we've
	 * attached it from within this module */
	अगर (priv->ver & (TDA18271 | TDA8275 | TDA8275A))
		अगर (fe->ops.tuner_ops.release)
			fe->ops.tuner_ops.release(fe);

	kमुक्त(fe->analog_demod_priv);
	fe->analog_demod_priv = शून्य;
पूर्ण

अटल काष्ठा tda18271_config tda829x_tda18271_config = अणु
	.gate    = TDA18271_GATE_ANALOG,
पूर्ण;

अटल पूर्णांक tda829x_find_tuner(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8290_priv *priv = fe->analog_demod_priv;
	पूर्णांक i, ret, tuners_found;
	u32 tuner_addrs;
	u8 data;
	काष्ठा i2c_msg msg = अणु .flags = I2C_M_RD, .buf = &data, .len = 1 पूर्ण;

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);

	/* probe क्रम tuner chip */
	tuners_found = 0;
	tuner_addrs = 0;
	क्रम (i = 0x60; i <= 0x63; i++) अणु
		msg.addr = i;
		ret = i2c_transfer(priv->i2c_props.adap, &msg, 1);
		अगर (ret == 1) अणु
			tuners_found++;
			tuner_addrs = (tuner_addrs << 8) + i;
		पूर्ण
	पूर्ण
	/* अगर there is more than one tuner, we expect the right one is
	   behind the bridge and we choose the highest address that करोesn't
	   give a response now
	 */

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);

	अगर (tuners_found > 1)
		क्रम (i = 0; i < tuners_found; i++) अणु
			msg.addr = tuner_addrs  & 0xff;
			ret = i2c_transfer(priv->i2c_props.adap, &msg, 1);
			अगर (ret == 1)
				tuner_addrs = tuner_addrs >> 8;
			अन्यथा
				अवरोध;
		पूर्ण

	अगर (tuner_addrs == 0) अणु
		tuner_addrs = 0x60;
		tuner_info("could not clearly identify tuner address, defaulting to %x\n",
			   tuner_addrs);
	पूर्ण अन्यथा अणु
		tuner_addrs = tuner_addrs & 0xff;
		tuner_info("setting tuner address to %x\n", tuner_addrs);
	पूर्ण
	priv->tda827x_addr = tuner_addrs;
	msg.addr = tuner_addrs;

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer(priv->i2c_props.adap, &msg, 1);

	अगर (ret != 1) अणु
		tuner_warn("tuner access failed!\n");
		अगर (fe->ops.analog_ops.i2c_gate_ctrl)
			fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);
		वापस -EREMOTEIO;
	पूर्ण

	अगर ((data == 0x83) || (data == 0x84)) अणु
		priv->ver |= TDA18271;
		tda829x_tda18271_config.config = priv->cfg.config;
		tda829x_tda18271_config.std_map = priv->tda18271_std_map;
		dvb_attach(tda18271_attach, fe, priv->tda827x_addr,
			   priv->i2c_props.adap, &tda829x_tda18271_config);
	पूर्ण अन्यथा अणु
		अगर ((data & 0x3c) == 0)
			priv->ver |= TDA8275;
		अन्यथा
			priv->ver |= TDA8275A;

		dvb_attach(tda827x_attach, fe, priv->tda827x_addr,
			   priv->i2c_props.adap, &priv->cfg);
		priv->cfg.चयन_addr = priv->i2c_props.addr;
	पूर्ण
	अगर (fe->ops.tuner_ops.init)
		fe->ops.tuner_ops.init(fe);

	अगर (fe->ops.tuner_ops.sleep)
		fe->ops.tuner_ops.sleep(fe);

	अगर (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tda8290_probe(काष्ठा tuner_i2c_props *i2c_props)
अणु
#घोषणा TDA8290_ID 0x89
	u8 reg = 0x1f, id;
	काष्ठा i2c_msg msg_पढ़ो[] = अणु
		अणु .addr = i2c_props->addr, .flags = 0, .len = 1, .buf = &reg पूर्ण,
		अणु .addr = i2c_props->addr, .flags = I2C_M_RD, .len = 1, .buf = &id पूर्ण,
	पूर्ण;

	/* detect tda8290 */
	अगर (i2c_transfer(i2c_props->adap, msg_पढ़ो, 2) != 2) अणु
		prपूर्णांकk(KERN_WARNING "%s: couldn't read register 0x%02x\n",
			       __func__, reg);
		वापस -ENODEV;
	पूर्ण

	अगर (id == TDA8290_ID) अणु
		अगर (debug)
			prपूर्णांकk(KERN_DEBUG "%s: tda8290 detected @ %d-%04x\n",
			       __func__, i2c_adapter_id(i2c_props->adap),
			       i2c_props->addr);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक tda8295_probe(काष्ठा tuner_i2c_props *i2c_props)
अणु
#घोषणा TDA8295_ID 0x8a
#घोषणा TDA8295C2_ID 0x8b
	u8 reg = 0x2f, id;
	काष्ठा i2c_msg msg_पढ़ो[] = अणु
		अणु .addr = i2c_props->addr, .flags = 0, .len = 1, .buf = &reg पूर्ण,
		अणु .addr = i2c_props->addr, .flags = I2C_M_RD, .len = 1, .buf = &id पूर्ण,
	पूर्ण;

	/* detect tda8295 */
	अगर (i2c_transfer(i2c_props->adap, msg_पढ़ो, 2) != 2) अणु
		prपूर्णांकk(KERN_WARNING "%s: couldn't read register 0x%02x\n",
			       __func__, reg);
		वापस -ENODEV;
	पूर्ण

	अगर ((id & 0xfe) == TDA8295_ID) अणु
		अगर (debug)
			prपूर्णांकk(KERN_DEBUG "%s: %s detected @ %d-%04x\n",
			       __func__, (id == TDA8295_ID) ?
			       "tda8295c1" : "tda8295c2",
			       i2c_adapter_id(i2c_props->adap),
			       i2c_props->addr);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा analog_demod_ops tda8290_ops = अणु
	.set_params     = tda8290_set_params,
	.has_संकेत     = tda8290_has_संकेत,
	.standby        = tda8290_standby,
	.release        = tda829x_release,
	.i2c_gate_ctrl  = tda8290_i2c_bridge,
पूर्ण;

अटल स्थिर काष्ठा analog_demod_ops tda8295_ops = अणु
	.set_params     = tda8295_set_params,
	.has_संकेत     = tda8295_has_संकेत,
	.standby        = tda8295_standby,
	.release        = tda829x_release,
	.i2c_gate_ctrl  = tda8295_i2c_bridge,
पूर्ण;

काष्ठा dvb_frontend *tda829x_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr,
				    काष्ठा tda829x_config *cfg)
अणु
	काष्ठा tda8290_priv *priv = शून्य;
	अक्षर *name;

	priv = kzalloc(माप(काष्ठा tda8290_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	fe->analog_demod_priv = priv;

	priv->i2c_props.addr     = i2c_addr;
	priv->i2c_props.adap     = i2c_adap;
	priv->i2c_props.name     = "tda829x";
	अगर (cfg) अणु
		priv->cfg.config = cfg->lna_cfg;
		priv->tda18271_std_map = cfg->tda18271_std_map;
	पूर्ण

	अगर (tda8290_probe(&priv->i2c_props) == 0) अणु
		priv->ver = TDA8290;
		स_नकल(&fe->ops.analog_ops, &tda8290_ops,
		       माप(काष्ठा analog_demod_ops));
	पूर्ण

	अगर (tda8295_probe(&priv->i2c_props) == 0) अणु
		priv->ver = TDA8295;
		स_नकल(&fe->ops.analog_ops, &tda8295_ops,
		       माप(काष्ठा analog_demod_ops));
	पूर्ण

	अगर (cfg && cfg->no_i2c_gate)
		fe->ops.analog_ops.i2c_gate_ctrl = शून्य;

	अगर (!(cfg) || (TDA829X_PROBE_TUNER == cfg->probe_tuner)) अणु
		tda8295_घातer(fe, 1);
		अगर (tda829x_find_tuner(fe) < 0)
			जाओ fail;
	पूर्ण

	चयन (priv->ver) अणु
	हाल TDA8290:
		name = "tda8290";
		अवरोध;
	हाल TDA8295:
		name = "tda8295";
		अवरोध;
	हाल TDA8290 | TDA8275:
		name = "tda8290+75";
		अवरोध;
	हाल TDA8295 | TDA8275:
		name = "tda8295+75";
		अवरोध;
	हाल TDA8290 | TDA8275A:
		name = "tda8290+75a";
		अवरोध;
	हाल TDA8295 | TDA8275A:
		name = "tda8295+75a";
		अवरोध;
	हाल TDA8290 | TDA18271:
		name = "tda8290+18271";
		अवरोध;
	हाल TDA8295 | TDA18271:
		name = "tda8295+18271";
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण
	tuner_info("type set to %s\n", name);

	fe->ops.analog_ops.info.name = name;

	अगर (priv->ver & TDA8290) अणु
		अगर (priv->ver & (TDA8275 | TDA8275A))
			tda8290_init_tuner(fe);
		tda8290_init_अगर(fe);
	पूर्ण अन्यथा अगर (priv->ver & TDA8295)
		tda8295_init_अगर(fe);

	वापस fe;

fail:
	स_रखो(&fe->ops.analog_ops, 0, माप(काष्ठा analog_demod_ops));

	tda829x_release(fe);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(tda829x_attach);

पूर्णांक tda829x_probe(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr)
अणु
	काष्ठा tuner_i2c_props i2c_props = अणु
		.adap = i2c_adap,
		.addr = i2c_addr,
	पूर्ण;

	अटल अचिन्हित अक्षर soft_reset[]   = अणु 0x00, 0x00 पूर्ण;
	अटल अचिन्हित अक्षर easy_mode_b[]  = अणु 0x01, 0x02 पूर्ण;
	अटल अचिन्हित अक्षर easy_mode_g[]  = अणु 0x01, 0x04 पूर्ण;
	अटल अचिन्हित अक्षर restore_9886[] = अणु 0x00, 0xd6, 0x30 पूर्ण;
	अटल अचिन्हित अक्षर addr_dto_lsb = 0x07;
	अचिन्हित अक्षर data;
#घोषणा PROBE_BUFFER_SIZE 8
	अचिन्हित अक्षर buf[PROBE_BUFFER_SIZE];
	पूर्णांक i;

	/* rule out tda9887, which would वापस the same byte repeatedly */
	tuner_i2c_xfer_send_recv(&i2c_props,
				 soft_reset, 1, buf, PROBE_BUFFER_SIZE);
	क्रम (i = 1; i < PROBE_BUFFER_SIZE; i++) अणु
		अगर (buf[i] != buf[0])
			अवरोध;
	पूर्ण

	/* all bytes are equal, not a tda829x - probably a tda9887 */
	अगर (i == PROBE_BUFFER_SIZE)
		वापस -ENODEV;

	अगर ((tda8290_probe(&i2c_props) == 0) ||
	    (tda8295_probe(&i2c_props) == 0))
		वापस 0;

	/* fall back to old probing method */
	tuner_i2c_xfer_send(&i2c_props, easy_mode_b, 2);
	tuner_i2c_xfer_send(&i2c_props, soft_reset, 2);
	tuner_i2c_xfer_send_recv(&i2c_props, &addr_dto_lsb, 1, &data, 1);
	अगर (data == 0) अणु
		tuner_i2c_xfer_send(&i2c_props, easy_mode_g, 2);
		tuner_i2c_xfer_send(&i2c_props, soft_reset, 2);
		tuner_i2c_xfer_send_recv(&i2c_props,
					 &addr_dto_lsb, 1, &data, 1);
		अगर (data == 0x7b) अणु
			वापस 0;
		पूर्ण
	पूर्ण
	tuner_i2c_xfer_send(&i2c_props, restore_9886, 3);
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(tda829x_probe);

MODULE_DESCRIPTION("Philips/NXP TDA8290/TDA8295 analog IF demodulator driver");
MODULE_AUTHOR("Gerd Knorr, Hartmut Hackmann, Michael Krufky");
MODULE_LICENSE("GPL");
