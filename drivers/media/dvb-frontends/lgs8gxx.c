<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम Legend Silicon GB20600 (a.k.a DMB-TH) demodulator
 *    LGS8913, LGS8GL5, LGS8G75
 *    experimental support LGS8G42, LGS8G52
 *
 *    Copyright (C) 2007-2009 David T.L. Wong <davidtlwong@gmail.com>
 *    Copyright (C) 2008 Sirius International (Hong Kong) Limited
 *    Timothy Lee <timothy.lee@siriushk.com> (क्रम initial work on LGS8GL5)
 */

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/firmware.h>

#समावेश <media/dvb_frontend.h>

#समावेश "lgs8gxx.h"
#समावेश "lgs8gxx_priv.h"

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "lgs8gxx: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक debug;
अटल पूर्णांक fake_संकेत_str = 1;

#घोषणा LGS8GXX_FIRMWARE "lgs8g75.fw"

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

module_param(fake_संकेत_str, पूर्णांक, 0644);
MODULE_PARM_DESC(fake_संकेत_str, "fake signal strength for LGS8913."
"Signal strength calculation is slow.(default:on).");

/* LGS8GXX पूर्णांकernal helper functions */

अटल पूर्णांक lgs8gxx_ग_लिखो_reg(काष्ठा lgs8gxx_state *priv, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .flags = 0, .buf = buf, .len = 2 पूर्ण;

	msg.addr = priv->config->demod_address;
	अगर (priv->config->prod != LGS8GXX_PROD_LGS8G75 && reg >= 0xC0)
		msg.addr += 0x02;

	अगर (debug >= 2)
		dprपूर्णांकk("%s: reg=0x%02X, data=0x%02X\n", __func__, reg, data);

	ret = i2c_transfer(priv->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: error reg=0x%x, data=0x%x, ret=%i\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल पूर्णांक lgs8gxx_पढ़ो_reg(काष्ठा lgs8gxx_state *priv, u8 reg, u8 *p_data)
अणु
	पूर्णांक ret;
	u8 dev_addr;

	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .flags = 0, .buf = b0, .len = 1 पूर्ण,
		अणु .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण,
	पूर्ण;

	dev_addr = priv->config->demod_address;
	अगर (priv->config->prod != LGS8GXX_PROD_LGS8G75 && reg >= 0xC0)
		dev_addr += 0x02;
	msg[1].addr =  msg[0].addr = dev_addr;

	ret = i2c_transfer(priv->i2c, msg, 2);
	अगर (ret != 2) अणु
		dprपूर्णांकk("%s: error reg=0x%x, ret=%i\n", __func__, reg, ret);
		वापस -1;
	पूर्ण

	*p_data = b1[0];
	अगर (debug >= 2)
		dprपूर्णांकk("%s: reg=0x%02X, data=0x%02X\n", __func__, reg, b1[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_soft_reset(काष्ठा lgs8gxx_state *priv)
अणु
	lgs8gxx_ग_लिखो_reg(priv, 0x02, 0x00);
	msleep(1);
	lgs8gxx_ग_लिखो_reg(priv, 0x02, 0x01);
	msleep(100);

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_reg_mask(काष्ठा lgs8gxx_state *priv, u8 reg, u8 mask,
	u8 val, u8 delay, u8 tries)
अणु
	u8 t;
	पूर्णांक i;

	क्रम (i = 0; i < tries; i++) अणु
		lgs8gxx_पढ़ो_reg(priv, reg, &t);

		अगर ((t & mask) == val)
			वापस 0;
		msleep(delay);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक lgs8gxx_set_ad_mode(काष्ठा lgs8gxx_state *priv)
अणु
	स्थिर काष्ठा lgs8gxx_config *config = priv->config;
	u8 अगर_conf;

	अगर_conf = 0x10; /* AGC output on, RF_AGC output off; */

	अगर_conf |=
		((config->ext_adc) ? 0x80 : 0x00) |
		((config->अगर_neg_center) ? 0x04 : 0x00) |
		((config->अगर_freq == 0) ? 0x08 : 0x00) | /* Baseband */
		((config->adc_चिन्हित) ? 0x02 : 0x00) |
		((config->अगर_neg_edge) ? 0x01 : 0x00);

	अगर (config->ext_adc &&
		(config->prod == LGS8GXX_PROD_LGS8G52)) अणु
		lgs8gxx_ग_लिखो_reg(priv, 0xBA, 0x40);
	पूर्ण

	lgs8gxx_ग_लिखो_reg(priv, 0x07, अगर_conf);

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_set_अगर_freq(काष्ठा lgs8gxx_state *priv, u32 freq /*in kHz*/)
अणु
	u64 val;
	u32 v32;
	u32 अगर_clk;

	अगर_clk = priv->config->अगर_clk_freq;

	val = freq;
	अगर (freq != 0) अणु
		val <<= 32;
		अगर (अगर_clk != 0)
			करो_भाग(val, अगर_clk);
		v32 = val & 0xFFFFFFFF;
		dprपूर्णांकk("Set IF Freq to %dkHz\n", freq);
	पूर्ण अन्यथा अणु
		v32 = 0;
		dprपूर्णांकk("Set IF Freq to baseband\n");
	पूर्ण
	dprपूर्णांकk("AFC_INIT_FREQ = 0x%08X\n", v32);

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		lgs8gxx_ग_लिखो_reg(priv, 0x08, 0xFF & (v32));
		lgs8gxx_ग_लिखो_reg(priv, 0x09, 0xFF & (v32 >> 8));
		lgs8gxx_ग_लिखो_reg(priv, 0x0A, 0xFF & (v32 >> 16));
		lgs8gxx_ग_लिखो_reg(priv, 0x0B, 0xFF & (v32 >> 24));
	पूर्ण अन्यथा अणु
		lgs8gxx_ग_लिखो_reg(priv, 0x09, 0xFF & (v32));
		lgs8gxx_ग_लिखो_reg(priv, 0x0A, 0xFF & (v32 >> 8));
		lgs8gxx_ग_लिखो_reg(priv, 0x0B, 0xFF & (v32 >> 16));
		lgs8gxx_ग_लिखो_reg(priv, 0x0C, 0xFF & (v32 >> 24));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_get_afc_phase(काष्ठा lgs8gxx_state *priv)
अणु
	u64 val;
	u32 v32 = 0;
	u8 reg_addr, t;
	पूर्णांक i;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		reg_addr = 0x23;
	अन्यथा
		reg_addr = 0x48;

	क्रम (i = 0; i < 4; i++) अणु
		lgs8gxx_पढ़ो_reg(priv, reg_addr, &t);
		v32 <<= 8;
		v32 |= t;
		reg_addr--;
	पूर्ण

	val = v32;
	val *= priv->config->अगर_clk_freq;
	val >>= 32;
	dprपूर्णांकk("AFC = %u kHz\n", (u32)val);
	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_set_mode_स्वतः(काष्ठा lgs8gxx_state *priv)
अणु
	u8 t;
	u8 prod = priv->config->prod;

	अगर (prod == LGS8GXX_PROD_LGS8913)
		lgs8gxx_ग_लिखो_reg(priv, 0xC6, 0x01);

	अगर (prod == LGS8GXX_PROD_LGS8G75) अणु
		lgs8gxx_पढ़ो_reg(priv, 0x0C, &t);
		t &= (~0x04);
		lgs8gxx_ग_लिखो_reg(priv, 0x0C, t | 0x80);
		lgs8gxx_ग_लिखो_reg(priv, 0x39, 0x00);
		lgs8gxx_ग_लिखो_reg(priv, 0x3D, 0x04);
	पूर्ण अन्यथा अगर (prod == LGS8GXX_PROD_LGS8913 ||
		prod == LGS8GXX_PROD_LGS8GL5 ||
		prod == LGS8GXX_PROD_LGS8G42 ||
		prod == LGS8GXX_PROD_LGS8G52 ||
		prod == LGS8GXX_PROD_LGS8G54) अणु
		lgs8gxx_पढ़ो_reg(priv, 0x7E, &t);
		lgs8gxx_ग_लिखो_reg(priv, 0x7E, t | 0x01);

		/* clear FEC self reset */
		lgs8gxx_पढ़ो_reg(priv, 0xC5, &t);
		lgs8gxx_ग_लिखो_reg(priv, 0xC5, t & 0xE0);
	पूर्ण

	अगर (prod == LGS8GXX_PROD_LGS8913) अणु
		/* FEC स्वतः detect */
		lgs8gxx_ग_लिखो_reg(priv, 0xC1, 0x03);

		lgs8gxx_पढ़ो_reg(priv, 0x7C, &t);
		t = (t & 0x8C) | 0x03;
		lgs8gxx_ग_लिखो_reg(priv, 0x7C, t);

		/* BER test mode */
		lgs8gxx_पढ़ो_reg(priv, 0xC3, &t);
		t = (t & 0xEF) |  0x10;
		lgs8gxx_ग_लिखो_reg(priv, 0xC3, t);
	पूर्ण

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G52)
		lgs8gxx_ग_लिखो_reg(priv, 0xD9, 0x40);

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_set_mode_manual(काष्ठा lgs8gxx_state *priv)
अणु
	u8 t;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		u8 t2;
		lgs8gxx_पढ़ो_reg(priv, 0x0C, &t);
		t &= (~0x80);
		lgs8gxx_ग_लिखो_reg(priv, 0x0C, t);

		lgs8gxx_पढ़ो_reg(priv, 0x0C, &t);
		lgs8gxx_पढ़ो_reg(priv, 0x19, &t2);

		अगर (((t&0x03) == 0x01) && (t2&0x01)) अणु
			lgs8gxx_ग_लिखो_reg(priv, 0x6E, 0x05);
			lgs8gxx_ग_लिखो_reg(priv, 0x39, 0x02);
			lgs8gxx_ग_लिखो_reg(priv, 0x39, 0x03);
			lgs8gxx_ग_लिखो_reg(priv, 0x3D, 0x05);
			lgs8gxx_ग_लिखो_reg(priv, 0x3E, 0x28);
			lgs8gxx_ग_लिखो_reg(priv, 0x53, 0x80);
		पूर्ण अन्यथा अणु
			lgs8gxx_ग_लिखो_reg(priv, 0x6E, 0x3F);
			lgs8gxx_ग_लिखो_reg(priv, 0x39, 0x00);
			lgs8gxx_ग_लिखो_reg(priv, 0x3D, 0x04);
		पूर्ण

		lgs8gxx_soft_reset(priv);
		वापस 0;
	पूर्ण

	/* turn off स्वतः-detect; manual settings */
	lgs8gxx_ग_लिखो_reg(priv, 0x7E, 0);
	अगर (priv->config->prod == LGS8GXX_PROD_LGS8913)
		lgs8gxx_ग_लिखो_reg(priv, 0xC1, 0);

	lgs8gxx_पढ़ो_reg(priv, 0xC5, &t);
	t = (t & 0xE0) | 0x06;
	lgs8gxx_ग_लिखो_reg(priv, 0xC5, t);

	lgs8gxx_soft_reset(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_is_locked(काष्ठा lgs8gxx_state *priv, u8 *locked)
अणु
	पूर्णांक ret = 0;
	u8 t;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		ret = lgs8gxx_पढ़ो_reg(priv, 0x13, &t);
	अन्यथा
		ret = lgs8gxx_पढ़ो_reg(priv, 0x4B, &t);
	अगर (ret != 0)
		वापस ret;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		*locked = ((t & 0x80) == 0x80) ? 1 : 0;
	अन्यथा
		*locked = ((t & 0xC0) == 0xC0) ? 1 : 0;
	वापस 0;
पूर्ण

/* Wait क्रम Code Acquisition Lock */
अटल पूर्णांक lgs8gxx_रुको_ca_lock(काष्ठा lgs8gxx_state *priv, u8 *locked)
अणु
	पूर्णांक ret = 0;
	u8 reg, mask, val;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		reg = 0x13;
		mask = 0x80;
		val = 0x80;
	पूर्ण अन्यथा अणु
		reg = 0x4B;
		mask = 0xC0;
		val = 0xC0;
	पूर्ण

	ret = रुको_reg_mask(priv, reg, mask, val, 50, 40);
	*locked = (ret == 0) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_is_स्वतःdetect_finished(काष्ठा lgs8gxx_state *priv,
					  u8 *finished)
अणु
	पूर्णांक ret = 0;
	u8 reg, mask, val;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		reg = 0x1f;
		mask = 0xC0;
		val = 0x80;
	पूर्ण अन्यथा अणु
		reg = 0xA4;
		mask = 0x03;
		val = 0x01;
	पूर्ण

	ret = रुको_reg_mask(priv, reg, mask, val, 10, 20);
	*finished = (ret == 0) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_स्वतःlock_gi(काष्ठा lgs8gxx_state *priv, u8 gi, u8 cpn,
	u8 *locked)
अणु
	पूर्णांक err = 0;
	u8 ad_fini = 0;
	u8 t1, t2;

	अगर (gi == GI_945)
		dprपूर्णांकk("try GI 945\n");
	अन्यथा अगर (gi == GI_595)
		dprपूर्णांकk("try GI 595\n");
	अन्यथा अगर (gi == GI_420)
		dprपूर्णांकk("try GI 420\n");
	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		lgs8gxx_पढ़ो_reg(priv, 0x0C, &t1);
		lgs8gxx_पढ़ो_reg(priv, 0x18, &t2);
		t1 &= ~(GI_MASK);
		t1 |= gi;
		t2 &= 0xFE;
		t2 |= cpn ? 0x01 : 0x00;
		lgs8gxx_ग_लिखो_reg(priv, 0x0C, t1);
		lgs8gxx_ग_लिखो_reg(priv, 0x18, t2);
	पूर्ण अन्यथा अणु
		lgs8gxx_ग_लिखो_reg(priv, 0x04, gi);
	पूर्ण
	lgs8gxx_soft_reset(priv);
	err = lgs8gxx_रुको_ca_lock(priv, locked);
	अगर (err || !(*locked))
		वापस err;
	err = lgs8gxx_is_स्वतःdetect_finished(priv, &ad_fini);
	अगर (err != 0)
		वापस err;
	अगर (ad_fini) अणु
		dprपूर्णांकk("auto detect finished\n");
	पूर्ण अन्यथा
		*locked = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_स्वतः_detect(काष्ठा lgs8gxx_state *priv,
			       u8 *detected_param, u8 *gi)
अणु
	पूर्णांक i, j;
	पूर्णांक err = 0;
	u8 locked = 0, पंचांगp_gi;

	dprपूर्णांकk("%s\n", __func__);

	lgs8gxx_set_mode_स्वतः(priv);
	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		lgs8gxx_ग_लिखो_reg(priv, 0x67, 0xAA);
		lgs8gxx_ग_लिखो_reg(priv, 0x6E, 0x3F);
	पूर्ण अन्यथा अणु
		/* Guard Interval */
		lgs8gxx_ग_लिखो_reg(priv, 0x03, 00);
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			पंचांगp_gi = GI_945;
			err = lgs8gxx_स्वतःlock_gi(priv, GI_945, j, &locked);
			अगर (err)
				जाओ out;
			अगर (locked)
				जाओ locked;
		पूर्ण
		क्रम (j = 0; j < 2; j++) अणु
			पंचांगp_gi = GI_420;
			err = lgs8gxx_स्वतःlock_gi(priv, GI_420, j, &locked);
			अगर (err)
				जाओ out;
			अगर (locked)
				जाओ locked;
		पूर्ण
		पंचांगp_gi = GI_595;
		err = lgs8gxx_स्वतःlock_gi(priv, GI_595, 1, &locked);
		अगर (err)
			जाओ out;
		अगर (locked)
			जाओ locked;
	पूर्ण

locked:
	अगर ((err == 0) && (locked == 1)) अणु
		u8 t;

		अगर (priv->config->prod != LGS8GXX_PROD_LGS8G75) अणु
			lgs8gxx_पढ़ो_reg(priv, 0xA2, &t);
			*detected_param = t;
		पूर्ण अन्यथा अणु
			lgs8gxx_पढ़ो_reg(priv, 0x1F, &t);
			*detected_param = t & 0x3F;
		पूर्ण

		अगर (पंचांगp_gi == GI_945)
			dprपूर्णांकk("GI 945 locked\n");
		अन्यथा अगर (पंचांगp_gi == GI_595)
			dprपूर्णांकk("GI 595 locked\n");
		अन्यथा अगर (पंचांगp_gi == GI_420)
			dprपूर्णांकk("GI 420 locked\n");
		*gi = पंचांगp_gi;
	पूर्ण
	अगर (!locked)
		err = -1;

out:
	वापस err;
पूर्ण

अटल व्योम lgs8gxx_स्वतः_lock(काष्ठा lgs8gxx_state *priv)
अणु
	s8 err;
	u8 gi = 0x2;
	u8 detected_param = 0;

	err = lgs8gxx_स्वतः_detect(priv, &detected_param, &gi);

	अगर (err != 0) अणु
		dprपूर्णांकk("lgs8gxx_auto_detect failed\n");
	पूर्ण अन्यथा
		dprपूर्णांकk("detected param = 0x%02X\n", detected_param);

	/* Apply detected parameters */
	अगर (priv->config->prod == LGS8GXX_PROD_LGS8913) अणु
		u8 पूर्णांकer_leave_len = detected_param & TIM_MASK ;
		/* Fix 8913 समय पूर्णांकerleaver detection bug */
		पूर्णांकer_leave_len = (पूर्णांकer_leave_len == TIM_MIDDLE) ? 0x60 : 0x40;
		detected_param &= CF_MASK | SC_MASK  | LGS_FEC_MASK;
		detected_param |= पूर्णांकer_leave_len;
	पूर्ण
	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		u8 t;
		lgs8gxx_पढ़ो_reg(priv, 0x19, &t);
		t &= 0x81;
		t |= detected_param << 1;
		lgs8gxx_ग_लिखो_reg(priv, 0x19, t);
	पूर्ण अन्यथा अणु
		lgs8gxx_ग_लिखो_reg(priv, 0x7D, detected_param);
		अगर (priv->config->prod == LGS8GXX_PROD_LGS8913)
			lgs8gxx_ग_लिखो_reg(priv, 0xC0, detected_param);
	पूर्ण
	/* lgs8gxx_soft_reset(priv); */

	/* Enter manual mode */
	lgs8gxx_set_mode_manual(priv);

	चयन (gi) अणु
	हाल GI_945:
		priv->curr_gi = 945; अवरोध;
	हाल GI_595:
		priv->curr_gi = 595; अवरोध;
	हाल GI_420:
		priv->curr_gi = 420; अवरोध;
	शेष:
		priv->curr_gi = 945; अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक lgs8gxx_set_mpeg_mode(काष्ठा lgs8gxx_state *priv,
	u8 serial, u8 clk_pol, u8 clk_gated)
अणु
	पूर्णांक ret = 0;
	u8 t, reg_addr;

	reg_addr = (priv->config->prod == LGS8GXX_PROD_LGS8G75) ? 0x30 : 0xC2;
	ret = lgs8gxx_पढ़ो_reg(priv, reg_addr, &t);
	अगर (ret != 0)
		वापस ret;

	t &= 0xF8;
	t |= serial ? TS_SERIAL : TS_PARALLEL;
	t |= clk_pol ? TS_CLK_INVERTED : TS_CLK_NORMAL;
	t |= clk_gated ? TS_CLK_GATED : TS_CLK_FREERUN;

	ret = lgs8gxx_ग_लिखो_reg(priv, reg_addr, t);
	अगर (ret != 0)
		वापस ret;

	वापस 0;
पूर्ण

/* A/D input peak-to-peak voltage range */
अटल पूर्णांक lgs8g75_set_adc_vpp(काष्ठा lgs8gxx_state *priv,
	u8 sel)
अणु
	u8 r26 = 0x73, r27 = 0x90;

	अगर (priv->config->prod != LGS8GXX_PROD_LGS8G75)
		वापस 0;

	r26 |= (sel & 0x01) << 7;
	r27 |= (sel & 0x02) >> 1;
	lgs8gxx_ग_लिखो_reg(priv, 0x26, r26);
	lgs8gxx_ग_लिखो_reg(priv, 0x27, r27);

	वापस 0;
पूर्ण

/* LGS8913 demod frontend functions */

अटल पूर्णांक lgs8913_init(काष्ठा lgs8gxx_state *priv)
अणु
	u8 t;

	/* LGS8913 specअगरic */
	lgs8gxx_ग_लिखो_reg(priv, 0xc1, 0x3);

	lgs8gxx_पढ़ो_reg(priv, 0x7c, &t);
	lgs8gxx_ग_लिखो_reg(priv, 0x7c, (t&0x8c) | 0x3);

	/* LGS8913 specअगरic */
	lgs8gxx_पढ़ो_reg(priv, 0xc3, &t);
	lgs8gxx_ग_लिखो_reg(priv, 0xc3, t&0x10);


	वापस 0;
पूर्ण

अटल पूर्णांक lgs8g75_init_data(काष्ठा lgs8gxx_state *priv)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक rc;
	पूर्णांक i;

	rc = request_firmware(&fw, LGS8GXX_FIRMWARE, &priv->i2c->dev);
	अगर (rc)
		वापस rc;

	lgs8gxx_ग_लिखो_reg(priv, 0xC6, 0x40);

	lgs8gxx_ग_लिखो_reg(priv, 0x3D, 0x04);
	lgs8gxx_ग_लिखो_reg(priv, 0x39, 0x00);

	lgs8gxx_ग_लिखो_reg(priv, 0x3A, 0x00);
	lgs8gxx_ग_लिखो_reg(priv, 0x38, 0x00);
	lgs8gxx_ग_लिखो_reg(priv, 0x3B, 0x00);
	lgs8gxx_ग_लिखो_reg(priv, 0x38, 0x00);

	क्रम (i = 0; i < fw->size; i++) अणु
		lgs8gxx_ग_लिखो_reg(priv, 0x38, 0x00);
		lgs8gxx_ग_लिखो_reg(priv, 0x3A, (u8)(i&0xff));
		lgs8gxx_ग_लिखो_reg(priv, 0x3B, (u8)(i>>8));
		lgs8gxx_ग_लिखो_reg(priv, 0x3C, fw->data[i]);
	पूर्ण

	lgs8gxx_ग_लिखो_reg(priv, 0x38, 0x00);

	release_firmware(fw);
	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgs8gxx_state *priv =
		(काष्ठा lgs8gxx_state *)fe->demodulator_priv;
	स्थिर काष्ठा lgs8gxx_config *config = priv->config;
	u8 data = 0;
	s8 err;
	dprपूर्णांकk("%s\n", __func__);

	lgs8gxx_पढ़ो_reg(priv, 0, &data);
	dprपूर्णांकk("reg 0 = 0x%02X\n", data);

	अगर (config->prod == LGS8GXX_PROD_LGS8G75)
		lgs8g75_set_adc_vpp(priv, config->adc_vpp);

	/* Setup MPEG output क्रमmat */
	err = lgs8gxx_set_mpeg_mode(priv, config->serial_ts,
				    config->ts_clk_pol,
				    config->ts_clk_gated);
	अगर (err != 0)
		वापस -EIO;

	अगर (config->prod == LGS8GXX_PROD_LGS8913)
		lgs8913_init(priv);
	lgs8gxx_set_अगर_freq(priv, priv->config->अगर_freq);
	lgs8gxx_set_ad_mode(priv);

	वापस 0;
पूर्ण

अटल व्योम lgs8gxx_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgs8gxx_state *state = fe->demodulator_priv;
	dprपूर्णांकk("%s\n", __func__);

	kमुक्त(state);
पूर्ण


अटल पूर्णांक lgs8gxx_ग_लिखो(काष्ठा dvb_frontend *fe, स्थिर u8 buf[], पूर्णांक len)
अणु
	काष्ठा lgs8gxx_state *priv = fe->demodulator_priv;

	अगर (len != 2)
		वापस -EINVAL;

	वापस lgs8gxx_ग_लिखो_reg(priv, buf[0], buf[1]);
पूर्ण

अटल पूर्णांक lgs8gxx_set_fe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fe_params = &fe->dtv_property_cache;
	काष्ठा lgs8gxx_state *priv = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	/* set frequency */
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* start स्वतः lock */
	lgs8gxx_स्वतः_lock(priv);

	msleep(10);

	/* TODO: get real पढ़ोings from device */

	/* bandwidth */
	fe_params->bandwidth_hz = 8000000;

	fe_params->code_rate_HP = FEC_AUTO;
	fe_params->code_rate_LP = FEC_AUTO;

	fe_params->modulation = QAM_AUTO;

	/* transmission mode */
	fe_params->transmission_mode = TRANSMISSION_MODE_AUTO;

	/* guard पूर्णांकerval */
	fe_params->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;

	/* hierarchy */
	fe_params->hierarchy = HIERARCHY_NONE;

	वापस 0;
पूर्ण

अटल
पूर्णांक lgs8gxx_get_tune_settings(काष्ठा dvb_frontend *fe,
			      काष्ठा dvb_frontend_tune_settings *fesettings)
अणु
	/* FIXME: copy from tda1004x.c */
	fesettings->min_delay_ms = 800;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *fe_status)
अणु
	काष्ठा lgs8gxx_state *priv = fe->demodulator_priv;
	s8 ret;
	u8 t, locked = 0;

	dprपूर्णांकk("%s\n", __func__);
	*fe_status = 0;

	lgs8gxx_get_afc_phase(priv);
	lgs8gxx_is_locked(priv, &locked);
	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		अगर (locked)
			*fe_status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		वापस 0;
	पूर्ण

	ret = lgs8gxx_पढ़ो_reg(priv, 0x4B, &t);
	अगर (ret != 0)
		वापस -EIO;

	dprपूर्णांकk("Reg 0x4B: 0x%02X\n", t);

	*fe_status = 0;
	अगर (priv->config->prod == LGS8GXX_PROD_LGS8913) अणु
		अगर ((t & 0x40) == 0x40)
			*fe_status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;
		अगर ((t & 0x80) == 0x80)
			*fe_status |= FE_HAS_VITERBI | FE_HAS_SYNC |
				FE_HAS_LOCK;
	पूर्ण अन्यथा अणु
		अगर ((t & 0x80) == 0x80)
			*fe_status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	पूर्ण

	/* success */
	dprपूर्णांकk("%s: fe_status=0x%x\n", __func__, *fe_status);
	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_पढ़ो_संकेत_agc(काष्ठा lgs8gxx_state *priv, u16 *संकेत)
अणु
	u16 v;
	u8 agc_lvl[2], cat;

	dprपूर्णांकk("%s()\n", __func__);
	lgs8gxx_पढ़ो_reg(priv, 0x3F, &agc_lvl[0]);
	lgs8gxx_पढ़ो_reg(priv, 0x3E, &agc_lvl[1]);

	v = agc_lvl[0];
	v <<= 8;
	v |= agc_lvl[1];

	dprपूर्णांकk("agc_lvl: 0x%04X\n", v);

	अगर (v < 0x100)
		cat = 0;
	अन्यथा अगर (v < 0x190)
		cat = 5;
	अन्यथा अगर (v < 0x2A8)
		cat = 4;
	अन्यथा अगर (v < 0x381)
		cat = 3;
	अन्यथा अगर (v < 0x400)
		cat = 2;
	अन्यथा अगर (v == 0x400)
		cat = 1;
	अन्यथा
		cat = 0;

	*संकेत = cat * 65535 / 5;

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8913_पढ़ो_संकेत_strength(काष्ठा lgs8gxx_state *priv, u16 *संकेत)
अणु
	u8 t; s8 ret;
	s16 max_strength = 0;
	u8 str;
	u16 i, gi = priv->curr_gi;

	dprपूर्णांकk("%s\n", __func__);

	ret = lgs8gxx_पढ़ो_reg(priv, 0x4B, &t);
	अगर (ret != 0)
		वापस -EIO;

	अगर (fake_संकेत_str) अणु
		अगर ((t & 0xC0) == 0xC0) अणु
			dprपूर्णांकk("Fake signal strength\n");
			*संकेत = 0x7FFF;
		पूर्ण अन्यथा
			*संकेत = 0;
		वापस 0;
	पूर्ण

	dprपूर्णांकk("gi = %d\n", gi);
	क्रम (i = 0; i < gi; i++) अणु

		अगर ((i & 0xFF) == 0)
			lgs8gxx_ग_लिखो_reg(priv, 0x84, 0x03 & (i >> 8));
		lgs8gxx_ग_लिखो_reg(priv, 0x83, i & 0xFF);

		lgs8gxx_पढ़ो_reg(priv, 0x94, &str);
		अगर (max_strength < str)
			max_strength = str;
	पूर्ण

	*संकेत = max_strength;
	dprपूर्णांकk("%s: signal=0x%02X\n", __func__, *संकेत);

	lgs8gxx_पढ़ो_reg(priv, 0x95, &t);
	dprपूर्णांकk("%s: AVG Noise=0x%02X\n", __func__, t);

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8g75_पढ़ो_संकेत_strength(काष्ठा lgs8gxx_state *priv, u16 *संकेत)
अणु
	u8 t;
	s16 v = 0;

	dprपूर्णांकk("%s\n", __func__);

	lgs8gxx_पढ़ो_reg(priv, 0xB1, &t);
	v |= t;
	v <<= 8;
	lgs8gxx_पढ़ो_reg(priv, 0xB0, &t);
	v |= t;

	*संकेत = v;
	dprपूर्णांकk("%s: signal=0x%02X\n", __func__, *संकेत);

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *संकेत)
अणु
	काष्ठा lgs8gxx_state *priv = fe->demodulator_priv;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8913)
		वापस lgs8913_पढ़ो_संकेत_strength(priv, संकेत);
	अन्यथा अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		वापस lgs8g75_पढ़ो_संकेत_strength(priv, संकेत);
	अन्यथा
		वापस lgs8gxx_पढ़ो_संकेत_agc(priv, संकेत);
पूर्ण

अटल पूर्णांक lgs8gxx_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा lgs8gxx_state *priv = fe->demodulator_priv;
	u8 t;
	*snr = 0;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		lgs8gxx_पढ़ो_reg(priv, 0x34, &t);
	अन्यथा
		lgs8gxx_पढ़ो_reg(priv, 0x95, &t);
	dprपूर्णांकk("AVG Noise=0x%02X\n", t);
	*snr = 256 - t;
	*snr <<= 8;
	dprपूर्णांकk("snr=0x%x\n", *snr);

	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	*ucblocks = 0;
	dprपूर्णांकk("%s: ucblocks=0x%x\n", __func__, *ucblocks);
	वापस 0;
पूर्ण

अटल व्योम packet_counter_start(काष्ठा lgs8gxx_state *priv)
अणु
	u8 orig, t;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		lgs8gxx_पढ़ो_reg(priv, 0x30, &orig);
		orig &= 0xE7;
		t = orig | 0x10;
		lgs8gxx_ग_लिखो_reg(priv, 0x30, t);
		t = orig | 0x18;
		lgs8gxx_ग_लिखो_reg(priv, 0x30, t);
		t = orig | 0x10;
		lgs8gxx_ग_लिखो_reg(priv, 0x30, t);
	पूर्ण अन्यथा अणु
		lgs8gxx_ग_लिखो_reg(priv, 0xC6, 0x01);
		lgs8gxx_ग_लिखो_reg(priv, 0xC6, 0x41);
		lgs8gxx_ग_लिखो_reg(priv, 0xC6, 0x01);
	पूर्ण
पूर्ण

अटल व्योम packet_counter_stop(काष्ठा lgs8gxx_state *priv)
अणु
	u8 t;

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		lgs8gxx_पढ़ो_reg(priv, 0x30, &t);
		t &= 0xE7;
		lgs8gxx_ग_लिखो_reg(priv, 0x30, t);
	पूर्ण अन्यथा अणु
		lgs8gxx_ग_लिखो_reg(priv, 0xC6, 0x81);
	पूर्ण
पूर्ण

अटल पूर्णांक lgs8gxx_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा lgs8gxx_state *priv = fe->demodulator_priv;
	u8 reg_err, reg_total, t;
	u32 total_cnt = 0, err_cnt = 0;
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	packet_counter_start(priv);
	msleep(200);
	packet_counter_stop(priv);

	अगर (priv->config->prod == LGS8GXX_PROD_LGS8G75) अणु
		reg_total = 0x28; reg_err = 0x2C;
	पूर्ण अन्यथा अणु
		reg_total = 0xD0; reg_err = 0xD4;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		total_cnt <<= 8;
		lgs8gxx_पढ़ो_reg(priv, reg_total+3-i, &t);
		total_cnt |= t;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		err_cnt <<= 8;
		lgs8gxx_पढ़ो_reg(priv, reg_err+3-i, &t);
		err_cnt |= t;
	पूर्ण
	dprपूर्णांकk("error=%d total=%d\n", err_cnt, total_cnt);

	अगर (total_cnt == 0)
		*ber = 0;
	अन्यथा
		*ber = err_cnt * 100 / total_cnt;

	dprपूर्णांकk("%s: ber=0x%x\n", __func__, *ber);
	वापस 0;
पूर्ण

अटल पूर्णांक lgs8gxx_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा lgs8gxx_state *priv = fe->demodulator_priv;

	अगर (priv->config->tuner_address == 0)
		वापस 0;
	अगर (enable) अणु
		u8 v = 0x80 | priv->config->tuner_address;
		वापस lgs8gxx_ग_लिखो_reg(priv, 0x01, v);
	पूर्ण
	वापस lgs8gxx_ग_लिखो_reg(priv, 0x01, 0);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops lgs8gxx_ops = अणु
	.delsys = अणु SYS_DTMB पूर्ण,
	.info = अणु
		.name = "Legend Silicon LGS8913/LGS8GXX DMB-TH",
		.frequency_min_hz = 474 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 10 * kHz,
		.caps =
			FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO
	पूर्ण,

	.release = lgs8gxx_release,

	.init = lgs8gxx_init,
	.ग_लिखो = lgs8gxx_ग_लिखो,
	.i2c_gate_ctrl = lgs8gxx_i2c_gate_ctrl,

	.set_frontend = lgs8gxx_set_fe,
	.get_tune_settings = lgs8gxx_get_tune_settings,

	.पढ़ो_status = lgs8gxx_पढ़ो_status,
	.पढ़ो_ber = lgs8gxx_पढ़ो_ber,
	.पढ़ो_संकेत_strength = lgs8gxx_पढ़ो_संकेत_strength,
	.पढ़ो_snr = lgs8gxx_पढ़ो_snr,
	.पढ़ो_ucblocks = lgs8gxx_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend *lgs8gxx_attach(स्थिर काष्ठा lgs8gxx_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा lgs8gxx_state *priv = शून्य;
	u8 data = 0;

	dprपूर्णांकk("%s()\n", __func__);

	अगर (config == शून्य || i2c == शून्य)
		वापस शून्य;

	priv = kzalloc(माप(काष्ठा lgs8gxx_state), GFP_KERNEL);
	अगर (priv == शून्य)
		जाओ error_out;

	priv->config = config;
	priv->i2c = i2c;

	/* check अगर the demod is there */
	अगर (lgs8gxx_पढ़ो_reg(priv, 0, &data) != 0) अणु
		dprपूर्णांकk("%s lgs8gxx not found at i2c addr 0x%02X\n",
			__func__, priv->config->demod_address);
		जाओ error_out;
	पूर्ण

	lgs8gxx_पढ़ो_reg(priv, 1, &data);

	स_नकल(&priv->frontend.ops, &lgs8gxx_ops,
	       माप(काष्ठा dvb_frontend_ops));
	priv->frontend.demodulator_priv = priv;

	अगर (config->prod == LGS8GXX_PROD_LGS8G75)
		lgs8g75_init_data(priv);

	वापस &priv->frontend;

error_out:
	dprपूर्णांकk("%s() error_out\n", __func__);
	kमुक्त(priv);
	वापस शून्य;

पूर्ण
EXPORT_SYMBOL(lgs8gxx_attach);

MODULE_DESCRIPTION("Legend Silicon LGS8913/LGS8GXX DMB-TH demodulator driver");
MODULE_AUTHOR("David T. L. Wong <davidtlwong@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(LGS8GXX_FIRMWARE);
