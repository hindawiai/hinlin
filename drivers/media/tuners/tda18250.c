<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NXP TDA18250 silicon tuner driver
 *
 * Copyright (C) 2017 Olli Salonen <olli.salonen@iki.fi>
 */

#समावेश "tda18250_priv.h"
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा dvb_tuner_ops tda18250_ops;

अटल पूर्णांक tda18250_घातer_control(काष्ठा dvb_frontend *fe,
		अचिन्हित पूर्णांक घातer_state)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;

	dev_dbg(&client->dev, "power state: %d", घातer_state);

	चयन (घातer_state) अणु
	हाल TDA18250_POWER_NORMAL:
		ret = regmap_ग_लिखो_bits(dev->regmap, R06_POWER2, 0x07, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_ग_लिखो_bits(dev->regmap, R25_REF, 0xc0, 0xc0);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल TDA18250_POWER_STANDBY:
		अगर (dev->loopthrough) अणु
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R25_REF, 0xc0, 0x80);
			अगर (ret)
				जाओ err;
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R06_POWER2, 0x07, 0x02);
			अगर (ret)
				जाओ err;
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R10_LT1, 0x80, 0x00);
			अगर (ret)
				जाओ err;
		पूर्ण अन्यथा अणु
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R25_REF, 0xc0, 0x80);
			अगर (ret)
				जाओ err;
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R06_POWER2, 0x07, 0x01);
			अगर (ret)
				जाओ err;
			ret = regmap_पढ़ो(dev->regmap,
					R0D_AGC12, &uपंचांगp);
			अगर (ret)
				जाओ err;
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R0D_AGC12, 0x03, 0x03);
			अगर (ret)
				जाओ err;
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R10_LT1, 0x80, 0x80);
			अगर (ret)
				जाओ err;
			ret = regmap_ग_लिखो_bits(dev->regmap,
					R0D_AGC12, 0x03, uपंचांगp & 0x03);
			अगर (ret)
				जाओ err;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18250_रुको_क्रम_irq(काष्ठा dvb_frontend *fe,
		पूर्णांक maxरुको, पूर्णांक step, u8 irq)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	bool triggered;
	अचिन्हित पूर्णांक uपंचांगp;

	triggered = false;
	समयout = jअगरfies + msecs_to_jअगरfies(maxरुको);
	जबतक (!समय_after(jअगरfies, समयout)) अणु
		// check क्रम the IRQ
		ret = regmap_पढ़ो(dev->regmap, R08_IRQ1, &uपंचांगp);
		अगर (ret)
			जाओ err;
		अगर ((uपंचांगp & irq) == irq) अणु
			triggered = true;
			अवरोध;
		पूर्ण
		msleep(step);
	पूर्ण

	dev_dbg(&client->dev, "waited IRQ (0x%02x) %d ms, triggered: %s", irq,
			jअगरfies_to_msecs(jअगरfies) -
			(jअगरfies_to_msecs(समयout) - maxरुको),
			triggered ? "true" : "false");

	अगर (!triggered)
		वापस -ETIMEDOUT;

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18250_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret, i;

	/* शेष values क्रम various regs */
	अटल स्थिर u8 init_regs[][2] = अणु
		अणु R0C_AGC11, 0xc7 पूर्ण,
		अणु R0D_AGC12, 0x5d पूर्ण,
		अणु R0E_AGC13, 0x40 पूर्ण,
		अणु R0F_AGC14, 0x0e पूर्ण,
		अणु R10_LT1, 0x47 पूर्ण,
		अणु R11_LT2, 0x4e पूर्ण,
		अणु R12_AGC21, 0x26 पूर्ण,
		अणु R13_AGC22, 0x60 पूर्ण,
		अणु R18_AGC32, 0x37 पूर्ण,
		अणु R19_AGC33, 0x09 पूर्ण,
		अणु R1A_AGCK, 0x00 पूर्ण,
		अणु R1E_WI_FI, 0x29 पूर्ण,
		अणु R1F_RF_BPF, 0x06 पूर्ण,
		अणु R20_IR_MIX, 0xc6 पूर्ण,
		अणु R21_IF_AGC, 0x00 पूर्ण,
		अणु R2C_PS1, 0x75 पूर्ण,
		अणु R2D_PS2, 0x06 पूर्ण,
		अणु R2E_PS3, 0x07 पूर्ण,
		अणु R30_RSSI2, 0x0e पूर्ण,
		अणु R31_IRQ_CTRL, 0x00 पूर्ण,
		अणु R39_SD5, 0x00 पूर्ण,
		अणु R3B_REGU, 0x55 पूर्ण,
		अणु R3C_RCCAL1, 0xa7 पूर्ण,
		अणु R3F_IRCAL2, 0x85 पूर्ण,
		अणु R40_IRCAL3, 0x87 पूर्ण,
		अणु R41_IRCAL4, 0xc0 पूर्ण,
		अणु R43_PD1, 0x40 पूर्ण,
		अणु R44_PD2, 0xc0 पूर्ण,
		अणु R46_CPUMP, 0x0c पूर्ण,
		अणु R47_LNAPOL, 0x64 पूर्ण,
		अणु R4B_XTALOSC1, 0x30 पूर्ण,
		अणु R59_AGC2_UP2, 0x05 पूर्ण,
		अणु R5B_AGC_AUTO, 0x07 पूर्ण,
		अणु R5C_AGC_DEBUG, 0x00 पूर्ण,
	पूर्ण;

	/* crystal related regs depend on frequency */
	अटल स्थिर u8 xtal_regs[][5] = अणु
					/* reg:   4d    4e    4f    50    51 */
		[TDA18250_XTAL_FREQ_16MHZ]  = अणु 0x3e, 0x80, 0x50, 0x00, 0x20 पूर्ण,
		[TDA18250_XTAL_FREQ_24MHZ]  = अणु 0x5d, 0xc0, 0xec, 0x00, 0x18 पूर्ण,
		[TDA18250_XTAL_FREQ_25MHZ]  = अणु 0x61, 0xa8, 0xec, 0x80, 0x19 पूर्ण,
		[TDA18250_XTAL_FREQ_27MHZ]  = अणु 0x69, 0x78, 0x8d, 0x80, 0x1b पूर्ण,
		[TDA18250_XTAL_FREQ_30MHZ]  = अणु 0x75, 0x30, 0x8f, 0x00, 0x1e पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	ret = tda18250_घातer_control(fe, TDA18250_POWER_NORMAL);
	अगर (ret)
		जाओ err;

	msleep(20);

	अगर (dev->warm)
		जाओ warm;

	/* set initial रेजिस्टर values */
	क्रम (i = 0; i < ARRAY_SIZE(init_regs); i++) अणु
		ret = regmap_ग_लिखो(dev->regmap, init_regs[i][0],
				init_regs[i][1]);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* set xtal related regs */
	ret = regmap_bulk_ग_लिखो(dev->regmap, R4D_XTALFLX1,
			xtal_regs[dev->xtal_freq], 5);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R10_LT1, 0x80,
			dev->loopthrough ? 0x00 : 0x80);
	अगर (ret)
		जाओ err;

	/* clear IRQ */
	ret = regmap_ग_लिखो(dev->regmap, R0A_IRQ3, TDA18250_IRQ_HW_INIT);
	अगर (ret)
		जाओ err;

	/* start HW init */
	ret = regmap_ग_लिखो(dev->regmap, R2A_MSM1, 0x70);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, R2B_MSM2, 0x01);
	अगर (ret)
		जाओ err;

	ret = tda18250_रुको_क्रम_irq(fe, 500, 10, TDA18250_IRQ_HW_INIT);
	अगर (ret)
		जाओ err;

	/* tuner calibration */
	ret = regmap_ग_लिखो(dev->regmap, R2A_MSM1, 0x02);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, R2B_MSM2, 0x01);
	अगर (ret)
		जाओ err;

	ret = tda18250_रुको_क्रम_irq(fe, 500, 10, TDA18250_IRQ_CAL);
	अगर (ret)
		जाओ err;

	dev->warm = true;

warm:
	/* घातer up LNA */
	ret = regmap_ग_लिखो_bits(dev->regmap, R0C_AGC11, 0x80, 0x00);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda18250_set_agc(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	u8 uपंचांगp, uपंचांगp2;

	dev_dbg(&client->dev, "\n");

	ret = regmap_ग_लिखो_bits(dev->regmap, R1F_RF_BPF, 0x87, 0x06);
	अगर (ret)
		जाओ err;

	uपंचांगp = ((c->frequency < 100000000) &&
			((c->delivery_प्रणाली == SYS_DVBC_ANNEX_A) ||
			(c->delivery_प्रणाली == SYS_DVBC_ANNEX_C)) &&
			(c->bandwidth_hz == 6000000)) ? 0x80 : 0x00;
	ret = regmap_ग_लिखो(dev->regmap, R5A_H3H5, uपंचांगp);
	अगर (ret)
		जाओ err;

	/* AGC1 */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		uपंचांगp = 4;
		अवरोध;
	शेष: /* DVB-C/QAM */
		चयन (c->bandwidth_hz) अणु
		हाल 6000000:
			uपंचांगp = (c->frequency < 800000000) ? 6 : 4;
			अवरोध;
		शेष: /* 7.935 and 8 MHz */
			uपंचांगp = (c->frequency < 100000000) ? 2 : 3;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = regmap_ग_लिखो_bits(dev->regmap, R0C_AGC11, 0x07, uपंचांगp);
	अगर (ret)
		जाओ err;

	/* AGC2 */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		uपंचांगp = (c->frequency < 320000000) ? 20 : 16;
		uपंचांगp2 = (c->frequency < 320000000) ? 22 : 18;
		अवरोध;
	शेष: /* DVB-C/QAM */
		चयन (c->bandwidth_hz) अणु
		हाल 6000000:
			अगर (c->frequency < 600000000) अणु
				uपंचांगp = 18;
				uपंचांगp2 = 22;
			पूर्ण अन्यथा अगर (c->frequency < 800000000) अणु
				uपंचांगp = 16;
				uपंचांगp2 = 20;
			पूर्ण अन्यथा अणु
				uपंचांगp = 14;
				uपंचांगp2 = 16;
			पूर्ण
			अवरोध;
		शेष: /* 7.935 and 8 MHz */
			uपंचांगp = (c->frequency < 320000000) ? 16 : 18;
			uपंचांगp2 = (c->frequency < 320000000) ? 18 : 20;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	ret = regmap_ग_लिखो_bits(dev->regmap, R58_AGC2_UP1, 0x1f, uपंचांगp2+8);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो_bits(dev->regmap, R13_AGC22, 0x1f, uपंचांगp);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो_bits(dev->regmap, R14_AGC23, 0x1f, uपंचांगp2);
	अगर (ret)
		जाओ err;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		uपंचांगp = 98;
		अवरोध;
	शेष: /* DVB-C/QAM */
		uपंचांगp = 90;
		अवरोध;
	पूर्ण
	ret = regmap_ग_लिखो_bits(dev->regmap, R16_AGC25, 0xf8, uपंचांगp);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R12_AGC21, 0x60,
			(c->frequency > 800000000) ? 0x40 : 0x20);
	अगर (ret)
		जाओ err;

	/* AGC3 */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		uपंचांगp = (c->frequency < 320000000) ? 5 : 7;
		uपंचांगp2 = (c->frequency < 320000000) ? 10 : 12;
		अवरोध;
	शेष: /* DVB-C/QAM */
		uपंचांगp = 7;
		uपंचांगp2 = 12;
		अवरोध;
	पूर्ण
	ret = regmap_ग_लिखो(dev->regmap, R17_AGC31, (uपंचांगp << 4) | uपंचांगp2);
	अगर (ret)
		जाओ err;

	/* S2D */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		अगर (c->bandwidth_hz == 8000000)
			uपंचांगp = 0x04;
		अन्यथा
			uपंचांगp = (c->frequency < 320000000) ? 0x04 : 0x02;
		अवरोध;
	शेष: /* DVB-C/QAM */
		अगर (c->bandwidth_hz == 6000000)
			uपंचांगp = ((c->frequency > 172544000) &&
				(c->frequency < 320000000)) ? 0x04 : 0x02;
		अन्यथा /* 7.935 and 8 MHz */
			uपंचांगp = ((c->frequency > 320000000) &&
				(c->frequency < 600000000)) ? 0x02 : 0x04;
		अवरोध;
	पूर्ण
	ret = regmap_ग_लिखो_bits(dev->regmap, R20_IR_MIX, 0x06, uपंचांगp);
	अगर (ret)
		जाओ err;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		uपंचांगp = 0;
		अवरोध;
	शेष: /* DVB-C/QAM */
		uपंचांगp = (c->frequency < 600000000) ? 0 : 3;
		अवरोध;
	पूर्ण
	ret = regmap_ग_लिखो_bits(dev->regmap, R16_AGC25, 0x03, uपंचांगp);
	अगर (ret)
		जाओ err;

	uपंचांगp = 0x09;
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		अगर (c->bandwidth_hz == 8000000)
			uपंचांगp = 0x0c;
		अवरोध;
	शेष: /* DVB-C/QAM */
		uपंचांगp = 0x0c;
		अवरोध;
	पूर्ण
	ret = regmap_ग_लिखो_bits(dev->regmap, R0F_AGC14, 0x3f, uपंचांगp);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda18250_pll_calc(काष्ठा dvb_frontend *fe, u8 *rभाग,
		u8 *nभाग, u8 *icp)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uval, exp, lopd, scale;
	अचिन्हित दीर्घ fvco;

	ret = regmap_पढ़ो(dev->regmap, R34_MD1, &uval);
	अगर (ret)
		जाओ err;

	exp = (uval & 0x70) >> 4;
	अगर (exp > 5)
		exp = 0;
	lopd = 1 << (exp - 1);
	scale = uval & 0x0f;
	fvco = lopd * scale * ((c->frequency / 1000) + dev->अगर_frequency);

	चयन (dev->xtal_freq) अणु
	हाल TDA18250_XTAL_FREQ_16MHZ:
		*rभाग = 1;
		*nभाग = 0;
		*icp = (fvco < 6622000) ? 0x05 : 0x02;
	अवरोध;
	हाल TDA18250_XTAL_FREQ_24MHZ:
	हाल TDA18250_XTAL_FREQ_25MHZ:
		*rभाग = 3;
		*nभाग = 1;
		*icp = (fvco < 6622000) ? 0x05 : 0x02;
	अवरोध;
	हाल TDA18250_XTAL_FREQ_27MHZ:
		अगर (fvco < 6643000) अणु
			*rभाग = 2;
			*nभाग = 0;
			*icp = 0x05;
		पूर्ण अन्यथा अगर (fvco < 6811000) अणु
			*rभाग = 2;
			*nभाग = 0;
			*icp = 0x06;
		पूर्ण अन्यथा अणु
			*rभाग = 3;
			*nभाग = 1;
			*icp = 0x02;
		पूर्ण
	अवरोध;
	हाल TDA18250_XTAL_FREQ_30MHZ:
		*rभाग = 2;
		*nभाग = 0;
		*icp = (fvco < 6811000) ? 0x05 : 0x02;
	अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&client->dev,
			"lopd=%d scale=%u fvco=%lu, rdiv=%d ndiv=%d icp=%d",
			lopd, scale, fvco, *rभाग, *nभाग, *icp);
	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18250_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 अगर_khz;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, j;
	u8 uपंचांगp;
	u8 buf[3];

	#घोषणा REG      0
	#घोषणा MASK     1
	#घोषणा DVBT_6   2
	#घोषणा DVBT_7   3
	#घोषणा DVBT_8   4
	#घोषणा DVBC_6   5
	#घोषणा DVBC_8   6
	#घोषणा ATSC     7

	अटल स्थिर u8 delsys_params[][16] = अणु
		[REG]    = अणु 0x22, 0x23, 0x24, 0x21, 0x0d, 0x0c, 0x0f, 0x14,
			     0x0e, 0x12, 0x58, 0x59, 0x1a, 0x19, 0x1e, 0x30 पूर्ण,
		[MASK]   = अणु 0x77, 0xff, 0xff, 0x87, 0xf0, 0x78, 0x07, 0xe0,
			     0x60, 0x0f, 0x60, 0x0f, 0x33, 0x30, 0x80, 0x06 पूर्ण,
		[DVBT_6] = अणु 0x51, 0x03, 0x83, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x60, 0x0f, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 पूर्ण,
		[DVBT_7] = अणु 0x52, 0x03, 0x85, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x60, 0x0f, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 पूर्ण,
		[DVBT_8] = अणु 0x53, 0x03, 0x87, 0x82, 0x40, 0x48, 0x06, 0xe0,
			     0x60, 0x07, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 पूर्ण,
		[DVBC_6] = अणु 0x32, 0x05, 0x86, 0x82, 0x50, 0x00, 0x06, 0x60,
			     0x40, 0x0e, 0x60, 0x05, 0x33, 0x10, 0x00, 0x04 पूर्ण,
		[DVBC_8] = अणु 0x53, 0x03, 0x88, 0x82, 0x50, 0x00, 0x06, 0x60,
			     0x40, 0x0e, 0x60, 0x05, 0x33, 0x10, 0x00, 0x04 पूर्ण,
		[ATSC]   = अणु 0x51, 0x03, 0x83, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x40, 0x0e, 0x60, 0x05, 0x03, 0x00, 0x80, 0x04 पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev,
			"delivery_system=%d frequency=%u bandwidth_hz=%u",
			c->delivery_प्रणाली, c->frequency, c->bandwidth_hz);


	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
		j = ATSC;
		अगर_khz = dev->अगर_atsc;
		अवरोध;
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		अगर (c->bandwidth_hz == 0) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण अन्यथा अगर (c->bandwidth_hz <= 6000000) अणु
			j = DVBT_6;
			अगर_khz = dev->अगर_dvbt_6;
		पूर्ण अन्यथा अगर (c->bandwidth_hz <= 7000000) अणु
			j = DVBT_7;
			अगर_khz = dev->अगर_dvbt_7;
		पूर्ण अन्यथा अगर (c->bandwidth_hz <= 8000000) अणु
			j = DVBT_8;
			अगर_khz = dev->अगर_dvbt_8;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		अगर (c->bandwidth_hz == 0) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण अन्यथा अगर (c->bandwidth_hz <= 6000000) अणु
			j = DVBC_6;
			अगर_khz = dev->अगर_dvbc_6;
		पूर्ण अन्यथा अगर (c->bandwidth_hz <= 8000000) अणु
			j = DVBC_8;
			अगर_khz = dev->अगर_dvbc_8;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		dev_err(&client->dev, "unsupported delivery system=%d",
				c->delivery_प्रणाली);
		जाओ err;
	पूर्ण

	/* set delivery प्रणाली dependent रेजिस्टरs */
	क्रम (i = 0; i < 16; i++) अणु
		ret = regmap_ग_लिखो_bits(dev->regmap, delsys_params[REG][i],
			 delsys_params[MASK][i],  delsys_params[j][i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* set IF अगर needed */
	अगर (dev->अगर_frequency != अगर_khz) अणु
		uपंचांगp = DIV_ROUND_CLOSEST(अगर_khz, 50);
		ret = regmap_ग_लिखो(dev->regmap, R26_IF, uपंचांगp);
		अगर (ret)
			जाओ err;
		dev->अगर_frequency = अगर_khz;
		dev_dbg(&client->dev, "set IF=%u kHz", अगर_khz);

	पूर्ण

	ret = tda18250_set_agc(fe);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R1A_AGCK, 0x03, 0x01);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R14_AGC23, 0x40, 0x00);
	अगर (ret)
		जाओ err;

	/* set frequency */
	buf[0] = ((c->frequency / 1000) >> 16) & 0xff;
	buf[1] = ((c->frequency / 1000) >>  8) & 0xff;
	buf[2] = ((c->frequency / 1000) >>  0) & 0xff;
	ret = regmap_bulk_ग_लिखो(dev->regmap, R27_RF1, buf, 3);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, R0A_IRQ3, TDA18250_IRQ_TUNE);
	अगर (ret)
		जाओ err;

	/* initial tune */
	ret = regmap_ग_लिखो(dev->regmap, R2A_MSM1, 0x01);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, R2B_MSM2, 0x01);
	अगर (ret)
		जाओ err;

	ret = tda18250_रुको_क्रम_irq(fe, 500, 10, TDA18250_IRQ_TUNE);
	अगर (ret)
		जाओ err;

	/* calc nभाग and rभाग */
	ret = tda18250_pll_calc(fe, &buf[0], &buf[1], &buf[2]);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R4F_XTALFLX3, 0xe0,
			(buf[0] << 6) | (buf[1] << 5));
	अगर (ret)
		जाओ err;

	/* clear IRQ */
	ret = regmap_ग_लिखो(dev->regmap, R0A_IRQ3, TDA18250_IRQ_TUNE);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R46_CPUMP, 0x07, 0x00);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R39_SD5, 0x03, 0x00);
	अगर (ret)
		जाओ err;

	/* tune again */
	ret = regmap_ग_लिखो(dev->regmap, R2A_MSM1, 0x01); /* tune */
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, R2B_MSM2, 0x01); /* go */
	अगर (ret)
		जाओ err;

	ret = tda18250_रुको_क्रम_irq(fe, 500, 10, TDA18250_IRQ_TUNE);
	अगर (ret)
		जाओ err;

	/* pll locking */
	msleep(20);

	ret = regmap_ग_लिखो_bits(dev->regmap, R2B_MSM2, 0x04, 0x04);
	अगर (ret)
		जाओ err;

	msleep(20);

	/* restore AGCK */
	ret = regmap_ग_लिखो_bits(dev->regmap, R1A_AGCK, 0x03, 0x03);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो_bits(dev->regmap, R14_AGC23, 0x40, 0x40);
	अगर (ret)
		जाओ err;

	/* अक्षरge pump */
	ret = regmap_ग_लिखो_bits(dev->regmap, R46_CPUMP, 0x07, buf[2]);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18250_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);

	*frequency = dev->अगर_frequency * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक tda18250_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	/* घातer करोwn LNA */
	ret = regmap_ग_लिखो_bits(dev->regmap, R0C_AGC11, 0x80, 0x00);
	अगर (ret)
		वापस ret;

	/* set अगर freq to 0 in order to make sure it's set after wake up */
	dev->अगर_frequency = 0;

	ret = tda18250_घातer_control(fe, TDA18250_POWER_STANDBY);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda18250_ops = अणु
	.info = अणु
		.name              = "NXP TDA18250",
		.frequency_min_hz  =  42 * MHz,
		.frequency_max_hz  = 870 * MHz,
	पूर्ण,

	.init = tda18250_init,
	.set_params = tda18250_set_params,
	.get_अगर_frequency = tda18250_get_अगर_frequency,
	.sleep = tda18250_sleep,
पूर्ण;

अटल पूर्णांक tda18250_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tda18250_config *cfg = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = cfg->fe;
	काष्ठा tda18250_dev *dev;
	पूर्णांक ret;
	अचिन्हित अक्षर chip_id[3];

	/* some रेजिस्टरs are always पढ़ो from HW */
	अटल स्थिर काष्ठा regmap_range tda18250_yes_ranges[] = अणु
		regmap_reg_range(R05_POWER1, R0B_IRQ4),
		regmap_reg_range(R21_IF_AGC, R21_IF_AGC),
		regmap_reg_range(R2A_MSM1, R2B_MSM2),
		regmap_reg_range(R2F_RSSI1, R31_IRQ_CTRL),
	पूर्ण;

	अटल स्थिर काष्ठा regmap_access_table tda18250_अस्थिर_table = अणु
		.yes_ranges = tda18250_yes_ranges,
		.n_yes_ranges = ARRAY_SIZE(tda18250_yes_ranges),
	पूर्ण;

	अटल स्थिर काष्ठा regmap_config tda18250_regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = TDA18250_NUM_REGS - 1,
		.अस्थिर_table = &tda18250_अस्थिर_table,
	पूर्ण;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	i2c_set_clientdata(client, dev);

	dev->fe = cfg->fe;
	dev->loopthrough = cfg->loopthrough;
	अगर (cfg->xtal_freq < TDA18250_XTAL_FREQ_MAX) अणु
		dev->xtal_freq = cfg->xtal_freq;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		dev_err(&client->dev, "xtal_freq invalid=%d", cfg->xtal_freq);
		जाओ err_kमुक्त;
	पूर्ण
	dev->अगर_dvbt_6 = cfg->अगर_dvbt_6;
	dev->अगर_dvbt_7 = cfg->अगर_dvbt_7;
	dev->अगर_dvbt_8 = cfg->अगर_dvbt_8;
	dev->अगर_dvbc_6 = cfg->अगर_dvbc_6;
	dev->अगर_dvbc_8 = cfg->अगर_dvbc_8;
	dev->अगर_atsc = cfg->अगर_atsc;

	dev->अगर_frequency = 0;
	dev->warm = false;

	dev->regmap = devm_regmap_init_i2c(client, &tda18250_regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* पढ़ो the three chip ID रेजिस्टरs */
	regmap_bulk_पढ़ो(dev->regmap, R00_ID1, &chip_id, 3);
	dev_dbg(&client->dev, "chip_id=%02x:%02x:%02x",
			chip_id[0], chip_id[1], chip_id[2]);

	चयन (chip_id[0]) अणु
	हाल 0xc7:
		dev->slave = false;
		अवरोध;
	हाल 0x47:
		dev->slave = true;
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	अगर (chip_id[1] != 0x4a) अणु
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	चयन (chip_id[2]) अणु
	हाल 0x20:
		dev_info(&client->dev,
				"NXP TDA18250AHN/%s successfully identified",
				dev->slave ? "S" : "M");
		अवरोध;
	हाल 0x21:
		dev_info(&client->dev,
				"NXP TDA18250BHN/%s successfully identified",
				dev->slave ? "S" : "M");
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	fe->tuner_priv = client;
	स_नकल(&fe->ops.tuner_ops, &tda18250_ops,
			माप(काष्ठा dvb_tuner_ops));

	/* put the tuner in standby */
	tda18250_घातer_control(fe, TDA18250_POWER_STANDBY);

	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda18250_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tda18250_dev *dev = i2c_get_clientdata(client);
	काष्ठा dvb_frontend *fe = dev->fe;

	dev_dbg(&client->dev, "\n");

	स_रखो(&fe->ops.tuner_ops, 0, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = शून्य;
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tda18250_id_table[] = अणु
	अणु"tda18250", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda18250_id_table);

अटल काष्ठा i2c_driver tda18250_driver = अणु
	.driver = अणु
		.name	= "tda18250",
	पूर्ण,
	.probe		= tda18250_probe,
	.हटाओ		= tda18250_हटाओ,
	.id_table	= tda18250_id_table,
पूर्ण;

module_i2c_driver(tda18250_driver);

MODULE_DESCRIPTION("NXP TDA18250 silicon tuner driver");
MODULE_AUTHOR("Olli Salonen <olli.salonen@iki.fi>");
MODULE_LICENSE("GPL");
