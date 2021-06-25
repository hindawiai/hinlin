<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Maxim MAX2165 silicon tuner
 *
 *  Copyright (c) 2009 David T. L. Wong <davidtlwong@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>

#समावेश "max2165.h"
#समावेश "max2165_priv.h"
#समावेश "tuner-i2c.h"

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "max2165: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

अटल पूर्णांक max2165_ग_लिखो_reg(काष्ठा max2165_priv *priv, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .flags = 0, .buf = buf, .len = 2 पूर्ण;

	msg.addr = priv->config->i2c_address;

	अगर (debug >= 2)
		dprपूर्णांकk("%s: reg=0x%02X, data=0x%02X\n", __func__, reg, data);

	ret = i2c_transfer(priv->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: error reg=0x%x, data=0x%x, ret=%i\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? -EIO : 0;
पूर्ण

अटल पूर्णांक max2165_पढ़ो_reg(काष्ठा max2165_priv *priv, u8 reg, u8 *p_data)
अणु
	पूर्णांक ret;
	u8 dev_addr = priv->config->i2c_address;

	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = dev_addr, .flags = 0, .buf = b0, .len = 1 पूर्ण,
		अणु .addr = dev_addr, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण,
	पूर्ण;

	ret = i2c_transfer(priv->i2c, msg, 2);
	अगर (ret != 2) अणु
		dprपूर्णांकk("%s: error reg=0x%x, ret=%i\n", __func__, reg, ret);
		वापस -EIO;
	पूर्ण

	*p_data = b1[0];
	अगर (debug >= 2)
		dprपूर्णांकk("%s: reg=0x%02X, data=0x%02X\n",
			__func__, reg, b1[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक max2165_mask_ग_लिखो_reg(काष्ठा max2165_priv *priv, u8 reg,
	u8 mask, u8 data)
अणु
	पूर्णांक ret;
	u8 v;

	data &= mask;
	ret = max2165_पढ़ो_reg(priv, reg, &v);
	अगर (ret != 0)
		वापस ret;
	v &= ~mask;
	v |= data;
	ret = max2165_ग_लिखो_reg(priv, reg, v);

	वापस ret;
पूर्ण

अटल पूर्णांक max2165_पढ़ो_rom_table(काष्ठा max2165_priv *priv)
अणु
	u8 dat[3];
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		max2165_ग_लिखो_reg(priv, REG_ROM_TABLE_ADDR, i + 1);
		max2165_पढ़ो_reg(priv, REG_ROM_TABLE_DATA, &dat[i]);
	पूर्ण

	priv->tf_ntch_low_cfg = dat[0] >> 4;
	priv->tf_ntch_hi_cfg = dat[0] & 0x0F;
	priv->tf_balun_low_ref = dat[1] & 0x0F;
	priv->tf_balun_hi_ref = dat[1] >> 4;
	priv->bb_filter_7mhz_cfg = dat[2] & 0x0F;
	priv->bb_filter_8mhz_cfg = dat[2] >> 4;

	dprपूर्णांकk("tf_ntch_low_cfg = 0x%X\n", priv->tf_ntch_low_cfg);
	dprपूर्णांकk("tf_ntch_hi_cfg = 0x%X\n", priv->tf_ntch_hi_cfg);
	dprपूर्णांकk("tf_balun_low_ref = 0x%X\n", priv->tf_balun_low_ref);
	dprपूर्णांकk("tf_balun_hi_ref = 0x%X\n", priv->tf_balun_hi_ref);
	dprपूर्णांकk("bb_filter_7mhz_cfg = 0x%X\n", priv->bb_filter_7mhz_cfg);
	dprपूर्णांकk("bb_filter_8mhz_cfg = 0x%X\n", priv->bb_filter_8mhz_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक max2165_set_osc(काष्ठा max2165_priv *priv, u8 osc /*MHz*/)
अणु
	u8 v;

	v = (osc / 2);
	अगर (v == 2)
		v = 0x7;
	अन्यथा
		v -= 8;

	max2165_mask_ग_लिखो_reg(priv, REG_PLL_CFG, 0x07, v);

	वापस 0;
पूर्ण

अटल पूर्णांक max2165_set_bandwidth(काष्ठा max2165_priv *priv, u32 bw)
अणु
	u8 val;

	अगर (bw == 8000000)
		val = priv->bb_filter_8mhz_cfg;
	अन्यथा
		val = priv->bb_filter_7mhz_cfg;

	max2165_mask_ग_लिखो_reg(priv, REG_BASEBAND_CTRL, 0xF0, val << 4);

	वापस 0;
पूर्ण

अटल पूर्णांक fixpt_भाग32(u32 भागidend, u32 भागisor, u32 *quotient, u32 *fraction)
अणु
	u32 reमुख्यder;
	u32 q, f = 0;
	पूर्णांक i;

	अगर (0 == भागisor)
		वापस -EINVAL;

	q = भागidend / भागisor;
	reमुख्यder = भागidend - q * भागisor;

	क्रम (i = 0; i < 31; i++) अणु
		reमुख्यder <<= 1;
		अगर (reमुख्यder >= भागisor) अणु
			f += 1;
			reमुख्यder -= भागisor;
		पूर्ण
		f <<= 1;
	पूर्ण

	*quotient = q;
	*fraction = f;

	वापस 0;
पूर्ण

अटल पूर्णांक max2165_set_rf(काष्ठा max2165_priv *priv, u32 freq)
अणु
	u8 tf;
	u8 tf_ntch;
	u32 t;
	u32 quotient, fraction;
	पूर्णांक ret;

	/* Set PLL भागider according to RF frequency */
	ret = fixpt_भाग32(freq / 1000, priv->config->osc_clk * 1000,
			 &quotient, &fraction);
	अगर (ret != 0)
		वापस ret;

	/* 20-bit fraction */
	fraction >>= 12;

	max2165_ग_लिखो_reg(priv, REG_NDIV_INT, quotient);
	max2165_mask_ग_लिखो_reg(priv, REG_NDIV_FRAC2, 0x0F, fraction >> 16);
	max2165_ग_लिखो_reg(priv, REG_NDIV_FRAC1, fraction >> 8);
	max2165_ग_लिखो_reg(priv, REG_NDIV_FRAC0, fraction);

	/* Norch Filter */
	tf_ntch = (freq < 725000000) ?
		priv->tf_ntch_low_cfg : priv->tf_ntch_hi_cfg;

	/* Tracking filter balun */
	t = priv->tf_balun_low_ref;
	t += (priv->tf_balun_hi_ref - priv->tf_balun_low_ref)
		* (freq / 1000 - 470000) / (780000 - 470000);

	tf = t;
	dprपूर्णांकk("tf = %X\n", tf);
	tf |= tf_ntch << 4;

	max2165_ग_लिखो_reg(priv, REG_TRACK_FILTER, tf);

	वापस 0;
पूर्ण

अटल व्योम max2165_debug_status(काष्ठा max2165_priv *priv)
अणु
	u8 status, स्वतःtune;
	u8 स्वतः_vco_success, स्वतः_vco_active;
	u8 pll_locked;
	u8 dc_offset_low, dc_offset_hi;
	u8 संकेत_lv_over_threshold;
	u8 vco, vco_sub_band, adc;

	max2165_पढ़ो_reg(priv, REG_STATUS, &status);
	max2165_पढ़ो_reg(priv, REG_AUTOTUNE, &स्वतःtune);

	स्वतः_vco_success = (status >> 6) & 0x01;
	स्वतः_vco_active = (status >> 5) & 0x01;
	pll_locked = (status >> 4) & 0x01;
	dc_offset_low = (status >> 3) & 0x01;
	dc_offset_hi = (status >> 2) & 0x01;
	संकेत_lv_over_threshold = status & 0x01;

	vco = स्वतःtune >> 6;
	vco_sub_band = (स्वतःtune >> 3) & 0x7;
	adc = स्वतःtune & 0x7;

	dprपूर्णांकk("auto VCO active: %d, auto VCO success: %d\n",
		स्वतः_vco_active, स्वतः_vco_success);
	dprपूर्णांकk("PLL locked: %d\n", pll_locked);
	dprपूर्णांकk("DC offset low: %d, DC offset high: %d\n",
		dc_offset_low, dc_offset_hi);
	dprपूर्णांकk("Signal lvl over threshold: %d\n", संकेत_lv_over_threshold);
	dprपूर्णांकk("VCO: %d, VCO Sub-band: %d, ADC: %d\n", vco, vco_sub_band, adc);
पूर्ण

अटल पूर्णांक max2165_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा max2165_priv *priv = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	चयन (c->bandwidth_hz) अणु
	हाल 7000000:
	हाल 8000000:
		priv->frequency = c->frequency;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "MAX2165: bandwidth %d Hz not supported.\n",
		       c->bandwidth_hz);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk("%s() frequency=%d\n", __func__, c->frequency);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	max2165_set_bandwidth(priv, c->bandwidth_hz);
	ret = max2165_set_rf(priv, priv->frequency);
	mdelay(50);
	max2165_debug_status(priv);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (ret != 0)
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक max2165_get_frequency(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	काष्ठा max2165_priv *priv = fe->tuner_priv;
	dprपूर्णांकk("%s()\n", __func__);
	*freq = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक max2165_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bw)
अणु
	काष्ठा max2165_priv *priv = fe->tuner_priv;
	dprपूर्णांकk("%s()\n", __func__);

	*bw = priv->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक max2165_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा max2165_priv *priv = fe->tuner_priv;
	u16 lock_status = 0;

	dprपूर्णांकk("%s()\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

	max2165_debug_status(priv);
	*status = lock_status;

	अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक max2165_sleep(काष्ठा dvb_frontend *fe)
अणु
	dprपूर्णांकk("%s()\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक max2165_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा max2165_priv *priv = fe->tuner_priv;
	dprपूर्णांकk("%s()\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* Setup initial values */
	/* Fractional Mode on */
	max2165_ग_लिखो_reg(priv, REG_NDIV_FRAC2, 0x18);
	/* LNA on */
	max2165_ग_लिखो_reg(priv, REG_LNA, 0x01);
	max2165_ग_लिखो_reg(priv, REG_PLL_CFG, 0x7A);
	max2165_ग_लिखो_reg(priv, REG_TEST, 0x08);
	max2165_ग_लिखो_reg(priv, REG_SHUTDOWN, 0x40);
	max2165_ग_लिखो_reg(priv, REG_VCO_CTRL, 0x84);
	max2165_ग_लिखो_reg(priv, REG_BASEBAND_CTRL, 0xC3);
	max2165_ग_लिखो_reg(priv, REG_DC_OFFSET_CTRL, 0x75);
	max2165_ग_लिखो_reg(priv, REG_DC_OFFSET_DAC, 0x00);
	max2165_ग_लिखो_reg(priv, REG_ROM_TABLE_ADDR, 0x00);

	max2165_set_osc(priv, priv->config->osc_clk);

	max2165_पढ़ो_rom_table(priv);

	max2165_set_bandwidth(priv, 8000000);

	अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल व्योम max2165_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा max2165_priv *priv = fe->tuner_priv;
	dprपूर्णांकk("%s()\n", __func__);

	kमुक्त(priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops max2165_tuner_ops = अणु
	.info = अणु
		.name              = "Maxim MAX2165",
		.frequency_min_hz  = 470 * MHz,
		.frequency_max_hz  = 862 * MHz,
		.frequency_step_hz =  50 * kHz,
	पूर्ण,

	.release	   = max2165_release,
	.init		   = max2165_init,
	.sleep		   = max2165_sleep,

	.set_params	   = max2165_set_params,
	.set_analog_params = शून्य,
	.get_frequency	   = max2165_get_frequency,
	.get_bandwidth	   = max2165_get_bandwidth,
	.get_status	   = max2165_get_status
पूर्ण;

काष्ठा dvb_frontend *max2165_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा i2c_adapter *i2c,
				   काष्ठा max2165_config *cfg)
अणु
	काष्ठा max2165_priv *priv = शून्य;

	dprपूर्णांकk("%s(%d-%04x)\n", __func__,
		i2c ? i2c_adapter_id(i2c) : -1,
		cfg ? cfg->i2c_address : -1);

	priv = kzalloc(माप(काष्ठा max2165_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	स_नकल(&fe->ops.tuner_ops, &max2165_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));

	priv->config = cfg;
	priv->i2c = i2c;
	fe->tuner_priv = priv;

	max2165_init(fe);
	max2165_debug_status(priv);

	वापस fe;
पूर्ण
EXPORT_SYMBOL(max2165_attach);

MODULE_AUTHOR("David T. L. Wong <davidtlwong@gmail.com>");
MODULE_DESCRIPTION("Maxim MAX2165 silicon tuner driver");
MODULE_LICENSE("GPL");
