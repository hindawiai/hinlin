<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Driver क्रम M88RS2000 demodulator and tuner

	Copyright (C) 2012 Malcolm Priestley (tvboxspy@gmail.com)
	Beta Driver

	Include various calculation code from DS3000 driver.
	Copyright (C) 2009 Konstantin Dimitrov.


*/
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>


#समावेश <media/dvb_frontend.h>
#समावेश "m88rs2000.h"

काष्ठा m88rs2000_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा m88rs2000_config *config;
	काष्ठा dvb_frontend frontend;
	u8 no_lock_count;
	u32 tuner_frequency;
	u32 symbol_rate;
	क्रमागत fe_code_rate fec_inner;
	u8 tuner_level;
	पूर्णांक errmode;
पूर्ण;

अटल पूर्णांक m88rs2000_debug;

module_param_named(debug, m88rs2000_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info (or-able)).");

#घोषणा dprपूर्णांकk(level, args...) करो अणु \
	अगर (level & m88rs2000_debug) \
		prपूर्णांकk(KERN_DEBUG "m88rs2000-fe: " args); \
पूर्ण जबतक (0)

#घोषणा deb_info(args...)  dprपूर्णांकk(0x01, args)
#घोषणा info(क्रमmat, arg...) \
	prपूर्णांकk(KERN_INFO "m88rs2000-fe: " क्रमmat "\n" , ## arg)

अटल पूर्णांक m88rs2000_ग_लिखोreg(काष्ठा m88rs2000_state *state,
	u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->demod_addr,
		.flags = 0,
		.buf = buf,
		.len = 2
	पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		deb_info("%s: writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			 __func__, reg, data, ret);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल u8 m88rs2000_पढ़ोreg(काष्ठा m88rs2000_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->config->demod_addr,
			.flags = 0,
			.buf = b0,
			.len = 1
		पूर्ण, अणु
			.addr = state->config->demod_addr,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 1
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		deb_info("%s: readreg error (reg == 0x%02x, ret == %i)\n",
				__func__, reg, ret);

	वापस b1[0];
पूर्ण

अटल u32 m88rs2000_get_mclk(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u32 mclk;
	u8 reg;
	/* Must not be 0x00 or 0xff */
	reg = m88rs2000_पढ़ोreg(state, 0x86);
	अगर (!reg || reg == 0xff)
		वापस 0;

	reg /= 2;
	reg += 1;

	mclk = (u32)(reg * RS2000_FE_CRYSTAL_KHZ + 28 / 2) / 28;

	वापस mclk;
पूर्ण

अटल पूर्णांक m88rs2000_set_carrieroffset(काष्ठा dvb_frontend *fe, s16 offset)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u32 mclk;
	s32 पंचांगp;
	u8 reg;
	पूर्णांक ret;

	mclk = m88rs2000_get_mclk(fe);
	अगर (!mclk)
		वापस -EINVAL;

	पंचांगp = (offset * 4096 + (s32)mclk / 2) / (s32)mclk;
	अगर (पंचांगp < 0)
		पंचांगp += 4096;

	/* Carrier Offset */
	ret = m88rs2000_ग_लिखोreg(state, 0x9c, (u8)(पंचांगp >> 4));

	reg = m88rs2000_पढ़ोreg(state, 0x9d);
	reg &= 0xf;
	reg |= (u8)(पंचांगp & 0xf) << 4;

	ret |= m88rs2000_ग_लिखोreg(state, 0x9d, reg);

	वापस ret;
पूर्ण

अटल पूर्णांक m88rs2000_set_symbolrate(काष्ठा dvb_frontend *fe, u32 srate)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u64 temp;
	u32 mclk;
	u8 b[3];

	अगर ((srate < 1000000) || (srate > 45000000))
		वापस -EINVAL;

	mclk = m88rs2000_get_mclk(fe);
	अगर (!mclk)
		वापस -EINVAL;

	temp = srate / 1000;
	temp *= 1 << 24;

	करो_भाग(temp, mclk);

	b[0] = (u8) (temp >> 16) & 0xff;
	b[1] = (u8) (temp >> 8) & 0xff;
	b[2] = (u8) temp & 0xff;

	ret = m88rs2000_ग_लिखोreg(state, 0x93, b[2]);
	ret |= m88rs2000_ग_लिखोreg(state, 0x94, b[1]);
	ret |= m88rs2000_ग_लिखोreg(state, 0x95, b[0]);

	अगर (srate > 10000000)
		ret |= m88rs2000_ग_लिखोreg(state, 0xa0, 0x20);
	अन्यथा
		ret |= m88rs2000_ग_लिखोreg(state, 0xa0, 0x60);

	ret |= m88rs2000_ग_लिखोreg(state, 0xa1, 0xe0);

	अगर (srate > 12000000)
		ret |= m88rs2000_ग_लिखोreg(state, 0xa3, 0x20);
	अन्यथा अगर (srate > 2800000)
		ret |= m88rs2000_ग_लिखोreg(state, 0xa3, 0x98);
	अन्यथा
		ret |= m88rs2000_ग_लिखोreg(state, 0xa3, 0x90);

	deb_info("m88rs2000: m88rs2000_set_symbolrate\n");
	वापस ret;
पूर्ण

अटल पूर्णांक m88rs2000_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				    काष्ठा dvb_diseqc_master_cmd *m)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;

	पूर्णांक i;
	u8 reg;
	deb_info("%s\n", __func__);
	m88rs2000_ग_लिखोreg(state, 0x9a, 0x30);
	reg = m88rs2000_पढ़ोreg(state, 0xb2);
	reg &= 0x3f;
	m88rs2000_ग_लिखोreg(state, 0xb2, reg);
	क्रम (i = 0; i <  m->msg_len; i++)
		m88rs2000_ग_लिखोreg(state, 0xb3 + i, m->msg[i]);

	reg = m88rs2000_पढ़ोreg(state, 0xb1);
	reg &= 0x87;
	reg |= ((m->msg_len - 1) << 3) | 0x07;
	reg &= 0x7f;
	m88rs2000_ग_लिखोreg(state, 0xb1, reg);

	क्रम (i = 0; i < 15; i++) अणु
		अगर ((m88rs2000_पढ़ोreg(state, 0xb1) & 0x40) == 0x0)
			अवरोध;
		msleep(20);
	पूर्ण

	reg = m88rs2000_पढ़ोreg(state, 0xb1);
	अगर ((reg & 0x40) > 0x0) अणु
		reg &= 0x7f;
		reg |= 0x40;
		m88rs2000_ग_लिखोreg(state, 0xb1, reg);
	पूर्ण

	reg = m88rs2000_पढ़ोreg(state, 0xb2);
	reg &= 0x3f;
	reg |= 0x80;
	m88rs2000_ग_लिखोreg(state, 0xb2, reg);
	m88rs2000_ग_लिखोreg(state, 0x9a, 0xb0);


	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u8 reg0, reg1;
	deb_info("%s\n", __func__);
	m88rs2000_ग_लिखोreg(state, 0x9a, 0x30);
	msleep(50);
	reg0 = m88rs2000_पढ़ोreg(state, 0xb1);
	reg1 = m88rs2000_पढ़ोreg(state, 0xb2);
	/* TODO complete this section */
	m88rs2000_ग_लिखोreg(state, 0xb2, reg1);
	m88rs2000_ग_लिखोreg(state, 0xb1, reg0);
	m88rs2000_ग_लिखोreg(state, 0x9a, 0xb0);

	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_set_tone(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u8 reg0, reg1;
	m88rs2000_ग_लिखोreg(state, 0x9a, 0x30);
	reg0 = m88rs2000_पढ़ोreg(state, 0xb1);
	reg1 = m88rs2000_पढ़ोreg(state, 0xb2);

	reg1 &= 0x3f;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		reg0 |= 0x4;
		reg0 &= 0xbc;
		अवरोध;
	हाल SEC_TONE_OFF:
		reg1 |= 0x80;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	m88rs2000_ग_लिखोreg(state, 0xb2, reg1);
	m88rs2000_ग_लिखोreg(state, 0xb1, reg0);
	m88rs2000_ग_लिखोreg(state, 0x9a, 0xb0);
	वापस 0;
पूर्ण

काष्ठा inittab अणु
	u8 cmd;
	u8 reg;
	u8 val;
पूर्ण;

अटल काष्ठा inittab m88rs2000_setup[] = अणु
	अणुDEMOD_WRITE, 0x9a, 0x30पूर्ण,
	अणुDEMOD_WRITE, 0x00, 0x01पूर्ण,
	अणुWRITE_DELAY, 0x19, 0x00पूर्ण,
	अणुDEMOD_WRITE, 0x00, 0x00पूर्ण,
	अणुDEMOD_WRITE, 0x9a, 0xb0पूर्ण,
	अणुDEMOD_WRITE, 0x81, 0xc1पूर्ण,
	अणुDEMOD_WRITE, 0x81, 0x81पूर्ण,
	अणुDEMOD_WRITE, 0x86, 0xc6पूर्ण,
	अणुDEMOD_WRITE, 0x9a, 0x30पूर्ण,
	अणुDEMOD_WRITE, 0xf0, 0x22पूर्ण,
	अणुDEMOD_WRITE, 0xf1, 0xbfपूर्ण,
	अणुDEMOD_WRITE, 0xb0, 0x45पूर्ण,
	अणुDEMOD_WRITE, 0xb2, 0x01पूर्ण, /* set voltage pin always set 1*/
	अणुDEMOD_WRITE, 0x9a, 0xb0पूर्ण,
	अणु0xff, 0xaa, 0xffपूर्ण
पूर्ण;

अटल काष्ठा inittab m88rs2000_shutकरोwn[] = अणु
	अणुDEMOD_WRITE, 0x9a, 0x30पूर्ण,
	अणुDEMOD_WRITE, 0xb0, 0x00पूर्ण,
	अणुDEMOD_WRITE, 0xf1, 0x89पूर्ण,
	अणुDEMOD_WRITE, 0x00, 0x01पूर्ण,
	अणुDEMOD_WRITE, 0x9a, 0xb0पूर्ण,
	अणुDEMOD_WRITE, 0x81, 0x81पूर्ण,
	अणु0xff, 0xaa, 0xffपूर्ण
पूर्ण;

अटल काष्ठा inittab fe_reset[] = अणु
	अणुDEMOD_WRITE, 0x00, 0x01पूर्ण,
	अणुDEMOD_WRITE, 0x20, 0x81पूर्ण,
	अणुDEMOD_WRITE, 0x21, 0x80पूर्ण,
	अणुDEMOD_WRITE, 0x10, 0x33पूर्ण,
	अणुDEMOD_WRITE, 0x11, 0x44पूर्ण,
	अणुDEMOD_WRITE, 0x12, 0x07पूर्ण,
	अणुDEMOD_WRITE, 0x18, 0x20पूर्ण,
	अणुDEMOD_WRITE, 0x28, 0x04पूर्ण,
	अणुDEMOD_WRITE, 0x29, 0x8eपूर्ण,
	अणुDEMOD_WRITE, 0x3b, 0xffपूर्ण,
	अणुDEMOD_WRITE, 0x32, 0x10पूर्ण,
	अणुDEMOD_WRITE, 0x33, 0x02पूर्ण,
	अणुDEMOD_WRITE, 0x34, 0x30पूर्ण,
	अणुDEMOD_WRITE, 0x35, 0xffपूर्ण,
	अणुDEMOD_WRITE, 0x38, 0x50पूर्ण,
	अणुDEMOD_WRITE, 0x39, 0x68पूर्ण,
	अणुDEMOD_WRITE, 0x3c, 0x7fपूर्ण,
	अणुDEMOD_WRITE, 0x3d, 0x0fपूर्ण,
	अणुDEMOD_WRITE, 0x45, 0x20पूर्ण,
	अणुDEMOD_WRITE, 0x46, 0x24पूर्ण,
	अणुDEMOD_WRITE, 0x47, 0x7cपूर्ण,
	अणुDEMOD_WRITE, 0x48, 0x16पूर्ण,
	अणुDEMOD_WRITE, 0x49, 0x04पूर्ण,
	अणुDEMOD_WRITE, 0x4a, 0x01पूर्ण,
	अणुDEMOD_WRITE, 0x4b, 0x78पूर्ण,
	अणुDEMOD_WRITE, 0X4d, 0xd2पूर्ण,
	अणुDEMOD_WRITE, 0x4e, 0x6dपूर्ण,
	अणुDEMOD_WRITE, 0x50, 0x30पूर्ण,
	अणुDEMOD_WRITE, 0x51, 0x30पूर्ण,
	अणुDEMOD_WRITE, 0x54, 0x7bपूर्ण,
	अणुDEMOD_WRITE, 0x56, 0x09पूर्ण,
	अणुDEMOD_WRITE, 0x58, 0x59पूर्ण,
	अणुDEMOD_WRITE, 0x59, 0x37पूर्ण,
	अणुDEMOD_WRITE, 0x63, 0xfaपूर्ण,
	अणु0xff, 0xaa, 0xffपूर्ण
पूर्ण;

अटल काष्ठा inittab fe_trigger[] = अणु
	अणुDEMOD_WRITE, 0x97, 0x04पूर्ण,
	अणुDEMOD_WRITE, 0x99, 0x77पूर्ण,
	अणुDEMOD_WRITE, 0x9b, 0x64पूर्ण,
	अणुDEMOD_WRITE, 0x9e, 0x00पूर्ण,
	अणुDEMOD_WRITE, 0x9f, 0xf8पूर्ण,
	अणुDEMOD_WRITE, 0x98, 0xffपूर्ण,
	अणुDEMOD_WRITE, 0xc0, 0x0fपूर्ण,
	अणुDEMOD_WRITE, 0x89, 0x01पूर्ण,
	अणुDEMOD_WRITE, 0x00, 0x00पूर्ण,
	अणुWRITE_DELAY, 0x0a, 0x00पूर्ण,
	अणुDEMOD_WRITE, 0x00, 0x01पूर्ण,
	अणुDEMOD_WRITE, 0x00, 0x00पूर्ण,
	अणुDEMOD_WRITE, 0x9a, 0xb0पूर्ण,
	अणु0xff, 0xaa, 0xffपूर्ण
पूर्ण;

अटल पूर्णांक m88rs2000_tab_set(काष्ठा m88rs2000_state *state,
		काष्ठा inittab *tab)
अणु
	पूर्णांक ret = 0;
	u8 i;
	अगर (tab == शून्य)
		वापस -EINVAL;

	क्रम (i = 0; i < 255; i++) अणु
		चयन (tab[i].cmd) अणु
		हाल 0x01:
			ret = m88rs2000_ग_लिखोreg(state, tab[i].reg,
				tab[i].val);
			अवरोध;
		हाल 0x10:
			अगर (tab[i].reg > 0)
				mdelay(tab[i].reg);
			अवरोध;
		हाल 0xff:
			अगर (tab[i].reg == 0xaa && tab[i].val == 0xff)
				वापस 0;
			अवरोध;
		हाल 0x00:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (ret < 0)
			वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_set_voltage(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_sec_voltage volt)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u8 data;

	data = m88rs2000_पढ़ोreg(state, 0xb2);
	data |= 0x03; /* bit0 V/H, bit1 off/on */

	चयन (volt) अणु
	हाल SEC_VOLTAGE_18:
		data &= ~0x03;
		अवरोध;
	हाल SEC_VOLTAGE_13:
		data &= ~0x03;
		data |= 0x01;
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		अवरोध;
	पूर्ण

	m88rs2000_ग_लिखोreg(state, 0xb2, data);

	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	deb_info("m88rs2000: init chip\n");
	/* Setup frontend from shutकरोwn/cold */
	अगर (state->config->inittab)
		ret = m88rs2000_tab_set(state,
				(काष्ठा inittab *)state->config->inittab);
	अन्यथा
		ret = m88rs2000_tab_set(state, m88rs2000_setup);

	वापस ret;
पूर्ण

अटल पूर्णांक m88rs2000_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	/* Shutकरोwn the frondend */
	ret = m88rs2000_tab_set(state, m88rs2000_shutकरोwn);
	वापस ret;
पूर्ण

अटल पूर्णांक m88rs2000_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u8 reg = m88rs2000_पढ़ोreg(state, 0x8c);

	*status = 0;

	अगर ((reg & 0xee) == 0xee) अणु
		*status = FE_HAS_CARRIER | FE_HAS_SIGNAL | FE_HAS_VITERBI
			| FE_HAS_SYNC | FE_HAS_LOCK;
		अगर (state->config->set_ts_params)
			state->config->set_ts_params(fe, CALL_IS_READ);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u8 पंचांगp0, पंचांगp1;

	m88rs2000_ग_लिखोreg(state, 0x9a, 0x30);
	पंचांगp0 = m88rs2000_पढ़ोreg(state, 0xd8);
	अगर ((पंचांगp0 & 0x10) != 0) अणु
		m88rs2000_ग_लिखोreg(state, 0x9a, 0xb0);
		*ber = 0xffffffff;
		वापस 0;
	पूर्ण

	*ber = (m88rs2000_पढ़ोreg(state, 0xd7) << 8) |
		m88rs2000_पढ़ोreg(state, 0xd6);

	पंचांगp1 = m88rs2000_पढ़ोreg(state, 0xd9);
	m88rs2000_ग_लिखोreg(state, 0xd9, (पंचांगp1 & ~7) | 4);
	/* needs twice */
	m88rs2000_ग_लिखोreg(state, 0xd8, (पंचांगp0 & ~8) | 0x30);
	m88rs2000_ग_लिखोreg(state, 0xd8, (पंचांगp0 & ~8) | 0x30);
	m88rs2000_ग_लिखोreg(state, 0x9a, 0xb0);

	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
	u16 *strength)
अणु
	अगर (fe->ops.tuner_ops.get_rf_strength)
		fe->ops.tuner_ops.get_rf_strength(fe, strength);

	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;

	*snr = 512 * m88rs2000_पढ़ोreg(state, 0x65);

	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	u8 पंचांगp;

	*ucblocks = (m88rs2000_पढ़ोreg(state, 0xd5) << 8) |
			m88rs2000_पढ़ोreg(state, 0xd4);
	पंचांगp = m88rs2000_पढ़ोreg(state, 0xd8);
	m88rs2000_ग_लिखोreg(state, 0xd8, पंचांगp & ~0x20);
	/* needs two बार */
	m88rs2000_ग_लिखोreg(state, 0xd8, पंचांगp | 0x20);
	m88rs2000_ग_लिखोreg(state, 0xd8, पंचांगp | 0x20);

	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_set_fec(काष्ठा m88rs2000_state *state,
			     क्रमागत fe_code_rate fec)
अणु
	u8 fec_set, reg;
	पूर्णांक ret;

	चयन (fec) अणु
	हाल FEC_1_2:
		fec_set = 0x8;
		अवरोध;
	हाल FEC_2_3:
		fec_set = 0x10;
		अवरोध;
	हाल FEC_3_4:
		fec_set = 0x20;
		अवरोध;
	हाल FEC_5_6:
		fec_set = 0x40;
		अवरोध;
	हाल FEC_7_8:
		fec_set = 0x80;
		अवरोध;
	हाल FEC_AUTO:
	शेष:
		fec_set = 0x0;
	पूर्ण

	reg = m88rs2000_पढ़ोreg(state, 0x70);
	reg &= 0x7;
	ret = m88rs2000_ग_लिखोreg(state, 0x70, reg | fec_set);

	ret |= m88rs2000_ग_लिखोreg(state, 0x76, 0x8);

	वापस ret;
पूर्ण

अटल क्रमागत fe_code_rate m88rs2000_get_fec(काष्ठा m88rs2000_state *state)
अणु
	u8 reg;
	m88rs2000_ग_लिखोreg(state, 0x9a, 0x30);
	reg = m88rs2000_पढ़ोreg(state, 0x76);
	m88rs2000_ग_लिखोreg(state, 0x9a, 0xb0);

	reg &= 0xf0;
	reg >>= 5;

	चयन (reg) अणु
	हाल 0x4:
		वापस FEC_1_2;
	हाल 0x3:
		वापस FEC_2_3;
	हाल 0x2:
		वापस FEC_3_4;
	हाल 0x1:
		वापस FEC_5_6;
	हाल 0x0:
		वापस FEC_7_8;
	शेष:
		अवरोध;
	पूर्ण

	वापस FEC_AUTO;
पूर्ण

अटल पूर्णांक m88rs2000_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	क्रमागत fe_status status = 0;
	पूर्णांक i, ret = 0;
	u32 tuner_freq;
	s16 offset = 0;
	u8 reg;

	state->no_lock_count = 0;

	अगर (c->delivery_प्रणाली != SYS_DVBS) अणु
		deb_info("%s: unsupported delivery system selected (%d)\n",
			 __func__, c->delivery_प्रणाली);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Set Tuner */
	अगर (fe->ops.tuner_ops.set_params)
		ret = fe->ops.tuner_ops.set_params(fe);

	अगर (ret < 0)
		वापस -ENODEV;

	अगर (fe->ops.tuner_ops.get_frequency) अणु
		ret = fe->ops.tuner_ops.get_frequency(fe, &tuner_freq);

		अगर (ret < 0)
			वापस -ENODEV;

		offset = (s16)((s32)tuner_freq - c->frequency);
	पूर्ण अन्यथा अणु
		offset = 0;
	पूर्ण

	/* शेष mclk value 96.4285 * 2 * 1000 = 192857 */
	अगर (((c->frequency % 192857) >= (192857 - 3000)) ||
				(c->frequency % 192857) <= 3000)
		ret = m88rs2000_ग_लिखोreg(state, 0x86, 0xc2);
	अन्यथा
		ret = m88rs2000_ग_लिखोreg(state, 0x86, 0xc6);

	ret |= m88rs2000_set_carrieroffset(fe, offset);
	अगर (ret < 0)
		वापस -ENODEV;

	/* Reset demod by symbol rate */
	अगर (c->symbol_rate > 27500000)
		ret = m88rs2000_ग_लिखोreg(state, 0xf1, 0xa4);
	अन्यथा
		ret = m88rs2000_ग_लिखोreg(state, 0xf1, 0xbf);

	ret |= m88rs2000_tab_set(state, fe_reset);
	अगर (ret < 0)
		वापस -ENODEV;

	/* Set FEC */
	ret = m88rs2000_set_fec(state, c->fec_inner);
	ret |= m88rs2000_ग_लिखोreg(state, 0x85, 0x1);
	ret |= m88rs2000_ग_लिखोreg(state, 0x8a, 0xbf);
	ret |= m88rs2000_ग_लिखोreg(state, 0x8d, 0x1e);
	ret |= m88rs2000_ग_लिखोreg(state, 0x90, 0xf1);
	ret |= m88rs2000_ग_लिखोreg(state, 0x91, 0x08);

	अगर (ret < 0)
		वापस -ENODEV;

	/* Set Symbol Rate */
	ret = m88rs2000_set_symbolrate(fe, c->symbol_rate);
	अगर (ret < 0)
		वापस -ENODEV;

	/* Set up Demod */
	ret = m88rs2000_tab_set(state, fe_trigger);
	अगर (ret < 0)
		वापस -ENODEV;

	क्रम (i = 0; i < 25; i++) अणु
		reg = m88rs2000_पढ़ोreg(state, 0x8c);
		अगर ((reg & 0xee) == 0xee) अणु
			status = FE_HAS_LOCK;
			अवरोध;
		पूर्ण
		state->no_lock_count++;
		अगर (state->no_lock_count == 15) अणु
			reg = m88rs2000_पढ़ोreg(state, 0x70);
			reg ^= 0x4;
			m88rs2000_ग_लिखोreg(state, 0x70, reg);
			state->no_lock_count = 0;
		पूर्ण
		msleep(20);
	पूर्ण

	अगर (status & FE_HAS_LOCK) अणु
		state->fec_inner = m88rs2000_get_fec(state);
		/* Unknown suspect SNR level */
		reg = m88rs2000_पढ़ोreg(state, 0x65);
	पूर्ण

	state->tuner_frequency = c->frequency;
	state->symbol_rate = c->symbol_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_get_frontend(काष्ठा dvb_frontend *fe,
				  काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;

	c->fec_inner = state->fec_inner;
	c->frequency = state->tuner_frequency;
	c->symbol_rate = state->symbol_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *tune)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->symbol_rate > 3000000)
		tune->min_delay_ms = 2000;
	अन्यथा
		tune->min_delay_ms = 3000;

	tune->step_size = c->symbol_rate / 16000;
	tune->max_drअगरt = c->symbol_rate / 2000;

	वापस 0;
पूर्ण

अटल पूर्णांक m88rs2000_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;

	अगर (enable)
		m88rs2000_ग_लिखोreg(state, 0x81, 0x84);
	अन्यथा
		m88rs2000_ग_लिखोreg(state, 0x81, 0x81);
	udelay(10);
	वापस 0;
पूर्ण

अटल व्योम m88rs2000_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs2000_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops m88rs2000_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "M88RS2000 DVB-S",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.frequency_stepsize_hz	= 1 * MHz,
		.frequency_tolerance_hz	= 5 * MHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.symbol_rate_tolerance	= 500,	/* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		      FE_CAN_QPSK | FE_CAN_INVERSION_AUTO |
		      FE_CAN_FEC_AUTO
	पूर्ण,

	.release = m88rs2000_release,
	.init = m88rs2000_init,
	.sleep = m88rs2000_sleep,
	.i2c_gate_ctrl = m88rs2000_i2c_gate_ctrl,
	.पढ़ो_status = m88rs2000_पढ़ो_status,
	.पढ़ो_ber = m88rs2000_पढ़ो_ber,
	.पढ़ो_संकेत_strength = m88rs2000_पढ़ो_संकेत_strength,
	.पढ़ो_snr = m88rs2000_पढ़ो_snr,
	.पढ़ो_ucblocks = m88rs2000_पढ़ो_ucblocks,
	.diseqc_send_master_cmd = m88rs2000_send_diseqc_msg,
	.diseqc_send_burst = m88rs2000_send_diseqc_burst,
	.set_tone = m88rs2000_set_tone,
	.set_voltage = m88rs2000_set_voltage,

	.set_frontend = m88rs2000_set_frontend,
	.get_frontend = m88rs2000_get_frontend,
	.get_tune_settings = m88rs2000_get_tune_settings,
पूर्ण;

काष्ठा dvb_frontend *m88rs2000_attach(स्थिर काष्ठा m88rs2000_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा m88rs2000_state *state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा m88rs2000_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->tuner_frequency = 0;
	state->symbol_rate = 0;
	state->fec_inner = 0;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &m88rs2000_ops,
			माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(m88rs2000_attach);

MODULE_DESCRIPTION("M88RS2000 DVB-S Demodulator driver");
MODULE_AUTHOR("Malcolm Priestley tvboxspy@gmail.com");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.13");

