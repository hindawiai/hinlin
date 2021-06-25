<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम
 *    Samsung S5H1420 and
 *    PnpNetwork PN1010 QPSK Demodulator
 *
 * Copyright (C) 2005 Andrew de Quincey <adq_dvb@lidskialf.net>
 * Copyright (C) 2005-8 Patrick Boettcher <pb@linuxtv.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <linux/i2c.h>


#समावेश <media/dvb_frontend.h>
#समावेश "s5h1420.h"
#समावेश "s5h1420_priv.h"

#घोषणा TONE_FREQ 22000

काष्ठा s5h1420_state अणु
	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा s5h1420_config* config;

	काष्ठा dvb_frontend frontend;
	काष्ठा i2c_adapter tuner_i2c_adapter;

	u8 CON_1_val;

	u8 postlocked:1;
	u32 fclk;
	u32 tunedfreq;
	क्रमागत fe_code_rate fec_inner;
	u32 symbol_rate;

	/* FIXME: ugly workaround क्रम flexcop's incapable i2c-controller
	 * it करोes not support repeated-start, workaround: ग_लिखो addr-1
	 * and then पढ़ो
	 */
	u8 shaकरोw[256];
पूर्ण;

अटल u32 s5h1420_माला_लोymbolrate(काष्ठा s5h1420_state* state);
अटल पूर्णांक s5h1420_get_tune_settings(काष्ठा dvb_frontend* fe,
				     काष्ठा dvb_frontend_tune_settings* fesettings);


अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debugging");

#घोषणा dprपूर्णांकk(x...) करो अणु \
	अगर (debug) \
		prपूर्णांकk(KERN_DEBUG "S5H1420: " x); \
पूर्ण जबतक (0)

अटल u8 s5h1420_पढ़ोreg(काष्ठा s5h1420_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b[2];
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config->demod_address, .flags = 0, .buf = b, .len = 2 पूर्ण,
		अणु .addr = state->config->demod_address, .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b, .len = 1 पूर्ण,
	पूर्ण;

	b[0] = (reg - 1) & 0xff;
	b[1] = state->shaकरोw[(reg - 1) & 0xff];

	अगर (state->config->repeated_start_workaround) अणु
		ret = i2c_transfer(state->i2c, msg, 3);
		अगर (ret != 3)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = i2c_transfer(state->i2c, &msg[1], 1);
		अगर (ret != 1)
			वापस ret;
		ret = i2c_transfer(state->i2c, &msg[2], 1);
		अगर (ret != 1)
			वापस ret;
	पूर्ण

	/* dprपूर्णांकk("rd(%02x): %02x %02x\n", state->config->demod_address, reg, b[0]); */

	वापस b[0];
पूर्ण

अटल पूर्णांक s5h1420_ग_लिखोreg (काष्ठा s5h1420_state* state, u8 reg, u8 data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक err;

	/* dprपूर्णांकk("wr(%02x): %02x %02x\n", state->config->demod_address, reg, data); */
	err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1) अणु
		dprपूर्णांकk("%s: writereg error (err == %i, reg == 0x%02x, data == 0x%02x)\n", __func__, err, reg, data);
		वापस -EREMOTEIO;
	पूर्ण
	state->shaकरोw[reg] = data;

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	dprपूर्णांकk("enter %s\n", __func__);

	चयन(voltage) अणु
	हाल SEC_VOLTAGE_13:
		s5h1420_ग_लिखोreg(state, 0x3c,
				 (s5h1420_पढ़ोreg(state, 0x3c) & 0xfe) | 0x02);
		अवरोध;

	हाल SEC_VOLTAGE_18:
		s5h1420_ग_लिखोreg(state, 0x3c, s5h1420_पढ़ोreg(state, 0x3c) | 0x03);
		अवरोध;

	हाल SEC_VOLTAGE_OFF:
		s5h1420_ग_लिखोreg(state, 0x3c, s5h1420_पढ़ोreg(state, 0x3c) & 0xfd);
		अवरोध;
	पूर्ण

	dprपूर्णांकk("leave %s\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_set_tone(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	dprपूर्णांकk("enter %s\n", __func__);
	चयन(tone) अणु
	हाल SEC_TONE_ON:
		s5h1420_ग_लिखोreg(state, 0x3b,
				 (s5h1420_पढ़ोreg(state, 0x3b) & 0x74) | 0x08);
		अवरोध;

	हाल SEC_TONE_OFF:
		s5h1420_ग_लिखोreg(state, 0x3b,
				 (s5h1420_पढ़ोreg(state, 0x3b) & 0x74) | 0x01);
		अवरोध;
	पूर्ण
	dprपूर्णांकk("leave %s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_send_master_cmd (काष्ठा dvb_frontend* fe,
				    काष्ठा dvb_diseqc_master_cmd* cmd)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;
	u8 val;
	पूर्णांक i;
	अचिन्हित दीर्घ समयout;
	पूर्णांक result = 0;

	dprपूर्णांकk("enter %s\n", __func__);
	अगर (cmd->msg_len > माप(cmd->msg))
		वापस -EINVAL;

	/* setup क्रम DISEQC */
	val = s5h1420_पढ़ोreg(state, 0x3b);
	s5h1420_ग_लिखोreg(state, 0x3b, 0x02);
	msleep(15);

	/* ग_लिखो the DISEQC command bytes */
	क्रम(i=0; i< cmd->msg_len; i++) अणु
		s5h1420_ग_लिखोreg(state, 0x3d + i, cmd->msg[i]);
	पूर्ण

	/* kick off transmission */
	s5h1420_ग_लिखोreg(state, 0x3b, s5h1420_पढ़ोreg(state, 0x3b) |
				      ((cmd->msg_len-1) << 4) | 0x08);

	/* रुको क्रम transmission to complete */
	समयout = jअगरfies + ((100*HZ) / 1000);
	जबतक(समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (!(s5h1420_पढ़ोreg(state, 0x3b) & 0x08))
			अवरोध;

		msleep(5);
	पूर्ण
	अगर (समय_after(jअगरfies, समयout))
		result = -ETIMEDOUT;

	/* restore original settings */
	s5h1420_ग_लिखोreg(state, 0x3b, val);
	msleep(15);
	dprपूर्णांकk("leave %s\n", __func__);
	वापस result;
पूर्ण

अटल पूर्णांक s5h1420_recv_slave_reply (काष्ठा dvb_frontend* fe,
				     काष्ठा dvb_diseqc_slave_reply* reply)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;
	u8 val;
	पूर्णांक i;
	पूर्णांक length;
	अचिन्हित दीर्घ समयout;
	पूर्णांक result = 0;

	/* setup क्रम DISEQC receive */
	val = s5h1420_पढ़ोreg(state, 0x3b);
	s5h1420_ग_लिखोreg(state, 0x3b, 0x82); /* FIXME: guess - करो we need to set DIS_RDY(0x08) in receive mode? */
	msleep(15);

	/* रुको क्रम reception to complete */
	समयout = jअगरfies + ((reply->समयout*HZ) / 1000);
	जबतक(समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (!(s5h1420_पढ़ोreg(state, 0x3b) & 0x80)) /* FIXME: करो we test DIS_RDY(0x08) or RCV_EN(0x80)? */
			अवरोध;

		msleep(5);
	पूर्ण
	अगर (समय_after(jअगरfies, समयout)) अणु
		result = -ETIMEDOUT;
		जाओ निकास;
	पूर्ण

	/* check error flag - FIXME: not sure what this करोes - करोcs करो not describe
	 * beyond "error flag क्रम diseqc receive data :( */
	अगर (s5h1420_पढ़ोreg(state, 0x49)) अणु
		result = -EIO;
		जाओ निकास;
	पूर्ण

	/* check length */
	length = (s5h1420_पढ़ोreg(state, 0x3b) & 0x70) >> 4;
	अगर (length > माप(reply->msg)) अणु
		result = -EOVERFLOW;
		जाओ निकास;
	पूर्ण
	reply->msg_len = length;

	/* extract data */
	क्रम(i=0; i< length; i++) अणु
		reply->msg[i] = s5h1420_पढ़ोreg(state, 0x3d + i);
	पूर्ण

निकास:
	/* restore original settings */
	s5h1420_ग_लिखोreg(state, 0x3b, val);
	msleep(15);
	वापस result;
पूर्ण

अटल पूर्णांक s5h1420_send_burst(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_mini_cmd minicmd)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;
	u8 val;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ समयout;

	/* setup क्रम tone burst */
	val = s5h1420_पढ़ोreg(state, 0x3b);
	s5h1420_ग_लिखोreg(state, 0x3b, (s5h1420_पढ़ोreg(state, 0x3b) & 0x70) | 0x01);

	/* set value क्रम B position अगर requested */
	अगर (minicmd == SEC_MINI_B) अणु
		s5h1420_ग_लिखोreg(state, 0x3b, s5h1420_पढ़ोreg(state, 0x3b) | 0x04);
	पूर्ण
	msleep(15);

	/* start transmission */
	s5h1420_ग_लिखोreg(state, 0x3b, s5h1420_पढ़ोreg(state, 0x3b) | 0x08);

	/* रुको क्रम transmission to complete */
	समयout = jअगरfies + ((100*HZ) / 1000);
	जबतक(समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (!(s5h1420_पढ़ोreg(state, 0x3b) & 0x08))
			अवरोध;

		msleep(5);
	पूर्ण
	अगर (समय_after(jअगरfies, समयout))
		result = -ETIMEDOUT;

	/* restore original settings */
	s5h1420_ग_लिखोreg(state, 0x3b, val);
	msleep(15);
	वापस result;
पूर्ण

अटल क्रमागत fe_status s5h1420_get_status_bits(काष्ठा s5h1420_state *state)
अणु
	u8 val;
	क्रमागत fe_status status = 0;

	val = s5h1420_पढ़ोreg(state, 0x14);
	अगर (val & 0x02)
		status |=  FE_HAS_SIGNAL;
	अगर (val & 0x01)
		status |=  FE_HAS_CARRIER;
	val = s5h1420_पढ़ोreg(state, 0x36);
	अगर (val & 0x01)
		status |=  FE_HAS_VITERBI;
	अगर (val & 0x20)
		status |=  FE_HAS_SYNC;
	अगर (status == (FE_HAS_SIGNAL|FE_HAS_CARRIER|FE_HAS_VITERBI|FE_HAS_SYNC))
		status |=  FE_HAS_LOCK;

	वापस status;
पूर्ण

अटल पूर्णांक s5h1420_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;
	u8 val;

	dprपूर्णांकk("enter %s\n", __func__);

	अगर (status == शून्य)
		वापस -EINVAL;

	/* determine lock state */
	*status = s5h1420_get_status_bits(state);

	/* fix क्रम FEC 5/6 inversion issue - अगर it करोesn't quite lock, invert
	the inversion, रुको a bit and check again */
	अगर (*status == (FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI)) अणु
		val = s5h1420_पढ़ोreg(state, Vit10);
		अगर ((val & 0x07) == 0x03) अणु
			अगर (val & 0x08)
				s5h1420_ग_लिखोreg(state, Vit09, 0x13);
			अन्यथा
				s5h1420_ग_लिखोreg(state, Vit09, 0x1b);

			/* रुको a bit then update lock status */
			mdelay(200);
			*status = s5h1420_get_status_bits(state);
		पूर्ण
	पूर्ण

	/* perक्रमm post lock setup */
	अगर ((*status & FE_HAS_LOCK) && !state->postlocked) अणु

		/* calculate the data rate */
		u32 पंचांगp = s5h1420_माला_लोymbolrate(state);
		चयन (s5h1420_पढ़ोreg(state, Vit10) & 0x07) अणु
		हाल 0: पंचांगp = (पंचांगp * 2 * 1) / 2; अवरोध;
		हाल 1: पंचांगp = (पंचांगp * 2 * 2) / 3; अवरोध;
		हाल 2: पंचांगp = (पंचांगp * 2 * 3) / 4; अवरोध;
		हाल 3: पंचांगp = (पंचांगp * 2 * 5) / 6; अवरोध;
		हाल 4: पंचांगp = (पंचांगp * 2 * 6) / 7; अवरोध;
		हाल 5: पंचांगp = (पंचांगp * 2 * 7) / 8; अवरोध;
		पूर्ण

		अगर (पंचांगp == 0) अणु
			prपूर्णांकk(KERN_ERR "s5h1420: avoided division by 0\n");
			पंचांगp = 1;
		पूर्ण
		पंचांगp = state->fclk / पंचांगp;


		/* set the MPEG_CLK_INTL क्रम the calculated data rate */
		अगर (पंचांगp < 2)
			val = 0x00;
		अन्यथा अगर (पंचांगp < 5)
			val = 0x01;
		अन्यथा अगर (पंचांगp < 9)
			val = 0x02;
		अन्यथा अगर (पंचांगp < 13)
			val = 0x03;
		अन्यथा अगर (पंचांगp < 17)
			val = 0x04;
		अन्यथा अगर (पंचांगp < 25)
			val = 0x05;
		अन्यथा अगर (पंचांगp < 33)
			val = 0x06;
		अन्यथा
			val = 0x07;
		dprपूर्णांकk("for MPEG_CLK_INTL %d %x\n", पंचांगp, val);

		s5h1420_ग_लिखोreg(state, FEC01, 0x18);
		s5h1420_ग_लिखोreg(state, FEC01, 0x10);
		s5h1420_ग_लिखोreg(state, FEC01, val);

		/* Enable "MPEG_Out" */
		val = s5h1420_पढ़ोreg(state, Mpeg02);
		s5h1420_ग_लिखोreg(state, Mpeg02, val | (1 << 6));

		/* kicker disable */
		val = s5h1420_पढ़ोreg(state, QPSK01) & 0x7f;
		s5h1420_ग_लिखोreg(state, QPSK01, val);

		/* DC मुक्तze TODO it was never activated by शेष or it can stay activated */

		अगर (s5h1420_माला_लोymbolrate(state) >= 20000000) अणु
			s5h1420_ग_लिखोreg(state, Loop04, 0x8a);
			s5h1420_ग_लिखोreg(state, Loop05, 0x6a);
		पूर्ण अन्यथा अणु
			s5h1420_ग_लिखोreg(state, Loop04, 0x58);
			s5h1420_ग_लिखोreg(state, Loop05, 0x27);
		पूर्ण

		/* post-lock processing has been करोne! */
		state->postlocked = 1;
	पूर्ण

	dprपूर्णांकk("leave %s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	s5h1420_ग_लिखोreg(state, 0x46, 0x1d);
	mdelay(25);

	*ber = (s5h1420_पढ़ोreg(state, 0x48) << 8) | s5h1420_पढ़ोreg(state, 0x47);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	u8 val = s5h1420_पढ़ोreg(state, 0x15);

	*strength =  (u16) ((val << 8) | val);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	s5h1420_ग_लिखोreg(state, 0x46, 0x1f);
	mdelay(25);

	*ucblocks = (s5h1420_पढ़ोreg(state, 0x48) << 8) | s5h1420_पढ़ोreg(state, 0x47);

	वापस 0;
पूर्ण

अटल व्योम s5h1420_reset(काष्ठा s5h1420_state* state)
अणु
	dprपूर्णांकk("%s\n", __func__);
	s5h1420_ग_लिखोreg (state, 0x01, 0x08);
	s5h1420_ग_लिखोreg (state, 0x01, 0x00);
	udelay(10);
पूर्ण

अटल व्योम s5h1420_setsymbolrate(काष्ठा s5h1420_state* state,
				  काष्ठा dtv_frontend_properties *p)
अणु
	u8 v;
	u64 val;

	dprपूर्णांकk("enter %s\n", __func__);

	val = ((u64) p->symbol_rate / 1000ULL) * (1ULL<<24);
	अगर (p->symbol_rate < 29000000)
		val *= 2;
	करो_भाग(val, (state->fclk / 1000));

	dprपूर्णांकk("symbol rate register: %06llx\n", (अचिन्हित दीर्घ दीर्घ)val);

	v = s5h1420_पढ़ोreg(state, Loop01);
	s5h1420_ग_लिखोreg(state, Loop01, v & 0x7f);
	s5h1420_ग_लिखोreg(state, Tnco01, val >> 16);
	s5h1420_ग_लिखोreg(state, Tnco02, val >> 8);
	s5h1420_ग_लिखोreg(state, Tnco03, val & 0xff);
	s5h1420_ग_लिखोreg(state, Loop01,  v | 0x80);
	dprपूर्णांकk("leave %s\n", __func__);
पूर्ण

अटल u32 s5h1420_माला_लोymbolrate(काष्ठा s5h1420_state* state)
अणु
	वापस state->symbol_rate;
पूर्ण

अटल व्योम s5h1420_setfreqoffset(काष्ठा s5h1420_state* state, पूर्णांक freqoffset)
अणु
	पूर्णांक val;
	u8 v;

	dprपूर्णांकk("enter %s\n", __func__);

	/* remember freqoffset is in kHz, but the chip wants the offset in Hz, so
	 * भागide fclk by 1000000 to get the correct value. */
	val = -(पूर्णांक) ((freqoffset * (1<<24)) / (state->fclk / 1000000));

	dprपूर्णांकk("phase rotator/freqoffset: %d %06x\n", freqoffset, val);

	v = s5h1420_पढ़ोreg(state, Loop01);
	s5h1420_ग_लिखोreg(state, Loop01, v & 0xbf);
	s5h1420_ग_लिखोreg(state, Pnco01, val >> 16);
	s5h1420_ग_लिखोreg(state, Pnco02, val >> 8);
	s5h1420_ग_लिखोreg(state, Pnco03, val & 0xff);
	s5h1420_ग_लिखोreg(state, Loop01, v | 0x40);
	dprपूर्णांकk("leave %s\n", __func__);
पूर्ण

अटल पूर्णांक s5h1420_getfreqoffset(काष्ठा s5h1420_state* state)
अणु
	पूर्णांक val;

	s5h1420_ग_लिखोreg(state, 0x06, s5h1420_पढ़ोreg(state, 0x06) | 0x08);
	val  = s5h1420_पढ़ोreg(state, 0x0e) << 16;
	val |= s5h1420_पढ़ोreg(state, 0x0f) << 8;
	val |= s5h1420_पढ़ोreg(state, 0x10);
	s5h1420_ग_लिखोreg(state, 0x06, s5h1420_पढ़ोreg(state, 0x06) & 0xf7);

	अगर (val & 0x800000)
		val |= 0xff000000;

	/* remember freqoffset is in kHz, but the chip wants the offset in Hz, so
	 * भागide fclk by 1000000 to get the correct value. */
	val = (((-val) * (state->fclk/1000000)) / (1<<24));

	वापस val;
पूर्ण

अटल व्योम s5h1420_setfec_inversion(काष्ठा s5h1420_state* state,
				     काष्ठा dtv_frontend_properties *p)
अणु
	u8 inversion = 0;
	u8 vit08, vit09;

	dprपूर्णांकk("enter %s\n", __func__);

	अगर (p->inversion == INVERSION_OFF)
		inversion = state->config->invert ? 0x08 : 0;
	अन्यथा अगर (p->inversion == INVERSION_ON)
		inversion = state->config->invert ? 0 : 0x08;

	अगर ((p->fec_inner == FEC_AUTO) || (p->inversion == INVERSION_AUTO)) अणु
		vit08 = 0x3f;
		vit09 = 0;
	पूर्ण अन्यथा अणु
		चयन (p->fec_inner) अणु
		हाल FEC_1_2:
			vit08 = 0x01;
			vit09 = 0x10;
			अवरोध;

		हाल FEC_2_3:
			vit08 = 0x02;
			vit09 = 0x11;
			अवरोध;

		हाल FEC_3_4:
			vit08 = 0x04;
			vit09 = 0x12;
			अवरोध;

		हाल FEC_5_6:
			vit08 = 0x08;
			vit09 = 0x13;
			अवरोध;

		हाल FEC_6_7:
			vit08 = 0x10;
			vit09 = 0x14;
			अवरोध;

		हाल FEC_7_8:
			vit08 = 0x20;
			vit09 = 0x15;
			अवरोध;

		शेष:
			वापस;
		पूर्ण
	पूर्ण
	vit09 |= inversion;
	dprपूर्णांकk("fec: %02x %02x\n", vit08, vit09);
	s5h1420_ग_लिखोreg(state, Vit08, vit08);
	s5h1420_ग_लिखोreg(state, Vit09, vit09);
	dprपूर्णांकk("leave %s\n", __func__);
पूर्ण

अटल क्रमागत fe_code_rate s5h1420_getfec(काष्ठा s5h1420_state *state)
अणु
	चयन(s5h1420_पढ़ोreg(state, 0x32) & 0x07) अणु
	हाल 0:
		वापस FEC_1_2;

	हाल 1:
		वापस FEC_2_3;

	हाल 2:
		वापस FEC_3_4;

	हाल 3:
		वापस FEC_5_6;

	हाल 4:
		वापस FEC_6_7;

	हाल 5:
		वापस FEC_7_8;
	पूर्ण

	वापस FEC_NONE;
पूर्ण

अटल क्रमागत fe_spectral_inversion
s5h1420_getinversion(काष्ठा s5h1420_state *state)
अणु
	अगर (s5h1420_पढ़ोreg(state, 0x32) & 0x08)
		वापस INVERSION_ON;

	वापस INVERSION_OFF;
पूर्ण

अटल पूर्णांक s5h1420_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा s5h1420_state* state = fe->demodulator_priv;
	पूर्णांक frequency_delta;
	काष्ठा dvb_frontend_tune_settings fesettings;

	dprपूर्णांकk("enter %s\n", __func__);

	/* check अगर we should करो a fast-tune */
	s5h1420_get_tune_settings(fe, &fesettings);
	frequency_delta = p->frequency - state->tunedfreq;
	अगर ((frequency_delta > -fesettings.max_drअगरt) &&
			(frequency_delta < fesettings.max_drअगरt) &&
			(frequency_delta != 0) &&
			(state->fec_inner == p->fec_inner) &&
			(state->symbol_rate == p->symbol_rate)) अणु

		अगर (fe->ops.tuner_ops.set_params) अणु
			fe->ops.tuner_ops.set_params(fe);
			अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
		पूर्ण
		अगर (fe->ops.tuner_ops.get_frequency) अणु
			u32 पंचांगp;
			fe->ops.tuner_ops.get_frequency(fe, &पंचांगp);
			अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
			s5h1420_setfreqoffset(state, p->frequency - पंचांगp);
		पूर्ण अन्यथा अणु
			s5h1420_setfreqoffset(state, 0);
		पूर्ण
		dprपूर्णांकk("simple tune\n");
		वापस 0;
	पूर्ण
	dprपूर्णांकk("tuning demod\n");

	/* first of all, software reset */
	s5h1420_reset(state);

	/* set s5h1420 fclk PLL according to desired symbol rate */
	अगर (p->symbol_rate > 33000000)
		state->fclk = 80000000;
	अन्यथा अगर (p->symbol_rate > 28500000)
		state->fclk = 59000000;
	अन्यथा अगर (p->symbol_rate > 25000000)
		state->fclk = 86000000;
	अन्यथा अगर (p->symbol_rate > 1900000)
		state->fclk = 88000000;
	अन्यथा
		state->fclk = 44000000;

	dprपूर्णांकk("pll01: %d, ToneFreq: %d\n", state->fclk/1000000 - 8, (state->fclk + (TONE_FREQ * 32) - 1) / (TONE_FREQ * 32));
	s5h1420_ग_लिखोreg(state, PLL01, state->fclk/1000000 - 8);
	s5h1420_ग_लिखोreg(state, PLL02, 0x40);
	s5h1420_ग_लिखोreg(state, DiS01, (state->fclk + (TONE_FREQ * 32) - 1) / (TONE_FREQ * 32));

	/* TODO DC offset removal, config parameter ? */
	अगर (p->symbol_rate > 29000000)
		s5h1420_ग_लिखोreg(state, QPSK01, 0xae | 0x10);
	अन्यथा
		s5h1420_ग_लिखोreg(state, QPSK01, 0xac | 0x10);

	/* set misc रेजिस्टरs */
	s5h1420_ग_लिखोreg(state, CON_1, 0x00);
	s5h1420_ग_लिखोreg(state, QPSK02, 0x00);
	s5h1420_ग_लिखोreg(state, Pre01, 0xb0);

	s5h1420_ग_लिखोreg(state, Loop01, 0xF0);
	s5h1420_ग_लिखोreg(state, Loop02, 0x2a); /* e7 क्रम s5h1420 */
	s5h1420_ग_लिखोreg(state, Loop03, 0x79); /* 78 क्रम s5h1420 */
	अगर (p->symbol_rate > 20000000)
		s5h1420_ग_लिखोreg(state, Loop04, 0x79);
	अन्यथा
		s5h1420_ग_लिखोreg(state, Loop04, 0x58);
	s5h1420_ग_लिखोreg(state, Loop05, 0x6b);

	अगर (p->symbol_rate >= 8000000)
		s5h1420_ग_लिखोreg(state, Post01, (0 << 6) | 0x10);
	अन्यथा अगर (p->symbol_rate >= 4000000)
		s5h1420_ग_लिखोreg(state, Post01, (1 << 6) | 0x10);
	अन्यथा
		s5h1420_ग_लिखोreg(state, Post01, (3 << 6) | 0x10);

	s5h1420_ग_लिखोreg(state, Monitor12, 0x00); /* unमुक्तze DC compensation */

	s5h1420_ग_लिखोreg(state, Sync01, 0x33);
	s5h1420_ग_लिखोreg(state, Mpeg01, state->config->cdclk_polarity);
	s5h1420_ग_लिखोreg(state, Mpeg02, 0x3d); /* Parallel output more, disabled -> enabled later */
	s5h1420_ग_लिखोreg(state, Err01, 0x03); /* 0x1d क्रम s5h1420 */

	s5h1420_ग_लिखोreg(state, Vit06, 0x6e); /* 0x8e क्रम s5h1420 */
	s5h1420_ग_लिखोreg(state, DiS03, 0x00);
	s5h1420_ग_लिखोreg(state, Rf01, 0x61); /* Tuner i2c address - क्रम the gate controller */

	/* set tuner PLL */
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
		s5h1420_setfreqoffset(state, 0);
	पूर्ण

	/* set the reset of the parameters */
	s5h1420_setsymbolrate(state, p);
	s5h1420_setfec_inversion(state, p);

	/* start QPSK */
	s5h1420_ग_लिखोreg(state, QPSK01, s5h1420_पढ़ोreg(state, QPSK01) | 1);

	state->fec_inner = p->fec_inner;
	state->symbol_rate = p->symbol_rate;
	state->postlocked = 0;
	state->tunedfreq = p->frequency;

	dprपूर्णांकk("leave %s\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_get_frontend(काष्ठा dvb_frontend* fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	p->frequency = state->tunedfreq + s5h1420_getfreqoffset(state);
	p->inversion = s5h1420_getinversion(state);
	p->symbol_rate = s5h1420_माला_लोymbolrate(state);
	p->fec_inner = s5h1420_getfec(state);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_get_tune_settings(काष्ठा dvb_frontend* fe,
				     काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	अगर (p->symbol_rate > 20000000) अणु
		fesettings->min_delay_ms = 50;
		fesettings->step_size = 2000;
		fesettings->max_drअगरt = 8000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 12000000) अणु
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 1500;
		fesettings->max_drअगरt = 9000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 8000000) अणु
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 1000;
		fesettings->max_drअगरt = 8000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 4000000) अणु
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 500;
		fesettings->max_drअगरt = 7000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 2000000) अणु
		fesettings->min_delay_ms = 200;
		fesettings->step_size = (p->symbol_rate / 8000);
		fesettings->max_drअगरt = 14 * fesettings->step_size;
	पूर्ण अन्यथा अणु
		fesettings->min_delay_ms = 200;
		fesettings->step_size = (p->symbol_rate / 8000);
		fesettings->max_drअगरt = 18 * fesettings->step_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	अगर (enable)
		वापस s5h1420_ग_लिखोreg(state, 0x02, state->CON_1_val | 1);
	अन्यथा
		वापस s5h1420_ग_लिखोreg(state, 0x02, state->CON_1_val & 0xfe);
पूर्ण

अटल पूर्णांक s5h1420_init (काष्ठा dvb_frontend* fe)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;

	/* disable घातer करोwn and करो reset */
	state->CON_1_val = state->config->serial_mpeg << 4;
	s5h1420_ग_लिखोreg(state, 0x02, state->CON_1_val);
	msleep(10);
	s5h1420_reset(state);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1420_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;
	state->CON_1_val = 0x12;
	वापस s5h1420_ग_लिखोreg(state, 0x02, state->CON_1_val);
पूर्ण

अटल व्योम s5h1420_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा s5h1420_state* state = fe->demodulator_priv;
	i2c_del_adapter(&state->tuner_i2c_adapter);
	kमुक्त(state);
पूर्ण

अटल u32 s5h1420_tuner_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल पूर्णांक s5h1420_tuner_i2c_tuner_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा s5h1420_state *state = i2c_get_adapdata(i2c_adap);
	काष्ठा i2c_msg m[3];
	u8 tx_खोलो[2] = अणु CON_1, state->CON_1_val | 1 पूर्ण; /* repeater stops once there was a stop condition */

	अगर (1 + num > ARRAY_SIZE(m)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c xfer: num=%d is too big!\n",
		       KBUILD_MODNAME, num);
		वापस  -EOPNOTSUPP;
	पूर्ण

	स_रखो(m, 0, माप(काष्ठा i2c_msg) * (1 + num));

	m[0].addr = state->config->demod_address;
	m[0].buf  = tx_खोलो;
	m[0].len  = 2;

	स_नकल(&m[1], msg, माप(काष्ठा i2c_msg) * num);

	वापस i2c_transfer(state->i2c, m, 1 + num) == 1 + num ? num : -EIO;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm s5h1420_tuner_i2c_algo = अणु
	.master_xfer   = s5h1420_tuner_i2c_tuner_xfer,
	.functionality = s5h1420_tuner_i2c_func,
पूर्ण;

काष्ठा i2c_adapter *s5h1420_get_tuner_i2c_adapter(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1420_state *state = fe->demodulator_priv;
	वापस &state->tuner_i2c_adapter;
पूर्ण
EXPORT_SYMBOL(s5h1420_get_tuner_i2c_adapter);

अटल स्थिर काष्ठा dvb_frontend_ops s5h1420_ops;

काष्ठा dvb_frontend *s5h1420_attach(स्थिर काष्ठा s5h1420_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	/* allocate memory क्रम the पूर्णांकernal state */
	काष्ठा s5h1420_state *state = kzalloc(माप(काष्ठा s5h1420_state), GFP_KERNEL);
	u8 i;

	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->postlocked = 0;
	state->fclk = 88000000;
	state->tunedfreq = 0;
	state->fec_inner = FEC_NONE;
	state->symbol_rate = 0;

	/* check अगर the demod is there + identअगरy it */
	i = s5h1420_पढ़ोreg(state, ID01);
	अगर (i != 0x03)
		जाओ error;

	स_रखो(state->shaकरोw, 0xff, माप(state->shaकरोw));

	क्रम (i = 0; i < 0x50; i++)
		state->shaकरोw[i] = s5h1420_पढ़ोreg(state, i);

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &s5h1420_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* create tuner i2c adapter */
	strscpy(state->tuner_i2c_adapter.name, "S5H1420-PN1010 tuner I2C bus",
		माप(state->tuner_i2c_adapter.name));
	state->tuner_i2c_adapter.algo      = &s5h1420_tuner_i2c_algo;
	state->tuner_i2c_adapter.algo_data = शून्य;
	i2c_set_adapdata(&state->tuner_i2c_adapter, state);
	अगर (i2c_add_adapter(&state->tuner_i2c_adapter) < 0) अणु
		prपूर्णांकk(KERN_ERR "S5H1420/PN1010: tuner i2c bus could not be initialized\n");
		जाओ error;
	पूर्ण

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(s5h1420_attach);

अटल स्थिर काष्ठा dvb_frontend_ops s5h1420_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name     = "Samsung S5H1420/PnpNetwork PN1010 DVB-S",
		.frequency_min_hz    =  950 * MHz,
		.frequency_max_hz    = 2150 * MHz,
		.frequency_stepsize_hz = 125 * kHz,
		.frequency_tolerance_hz  = 29500 * kHz,
		.symbol_rate_min  = 1000000,
		.symbol_rate_max  = 45000000,
		/*  .symbol_rate_tolerance  = ???,*/
		.caps = FE_CAN_INVERSION_AUTO |
		FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		FE_CAN_QPSK
	पूर्ण,

	.release = s5h1420_release,

	.init = s5h1420_init,
	.sleep = s5h1420_sleep,
	.i2c_gate_ctrl = s5h1420_i2c_gate_ctrl,

	.set_frontend = s5h1420_set_frontend,
	.get_frontend = s5h1420_get_frontend,
	.get_tune_settings = s5h1420_get_tune_settings,

	.पढ़ो_status = s5h1420_पढ़ो_status,
	.पढ़ो_ber = s5h1420_पढ़ो_ber,
	.पढ़ो_संकेत_strength = s5h1420_पढ़ो_संकेत_strength,
	.पढ़ो_ucblocks = s5h1420_पढ़ो_ucblocks,

	.diseqc_send_master_cmd = s5h1420_send_master_cmd,
	.diseqc_recv_slave_reply = s5h1420_recv_slave_reply,
	.diseqc_send_burst = s5h1420_send_burst,
	.set_tone = s5h1420_set_tone,
	.set_voltage = s5h1420_set_voltage,
पूर्ण;

MODULE_DESCRIPTION("Samsung S5H1420/PnpNetwork PN1010 DVB-S Demodulator driver");
MODULE_AUTHOR("Andrew de Quincey, Patrick Boettcher");
MODULE_LICENSE("GPL");
