<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    TDA10023  - DVB-C decoder
    (as used in Philips CU1216-3 NIM and the Reelbox DVB-C tuner card)

    Copyright (C) 2005 Georg Acher, BayCom GmbH (acher at baycom करोt de)
    Copyright (c) 2006 Harपंचांगut Birr (e9hack at gmail करोt com)

    Remotely based on tda10021.c
    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>
    Copyright (C) 2004 Markus Schulz <msc@antzप्रणाली.de>
		   Support क्रम TDA10021

*/

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "tda1002x.h"

#घोषणा REG0_INIT_VAL 0x23

काष्ठा tda10023_state अणु
	काष्ठा i2c_adapter* i2c;
	/* configuration settings */
	स्थिर काष्ठा tda10023_config *config;
	काष्ठा dvb_frontend frontend;

	u8 pwm;
	u8 reg0;

	/* घड़ी settings */
	u32 xtal;
	u8 pll_m;
	u8 pll_p;
	u8 pll_n;
	u32 sysclk;
पूर्ण;

#घोषणा dprपूर्णांकk(x...)

अटल पूर्णांक verbose;

अटल u8 tda10023_पढ़ोreg (काष्ठा tda10023_state* state, u8 reg)
अणु
	u8 b0 [] = अणु reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 1 पूर्ण,
				  अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer (state->i2c, msg, 2);
	अगर (ret != 2) अणु
		पूर्णांक num = state->frontend.dvb ? state->frontend.dvb->num : -1;
		prपूर्णांकk(KERN_ERR "DVB: TDA10023(%d): %s: readreg error (reg == 0x%02x, ret == %i)\n",
			num, __func__, reg, ret);
	पूर्ण
	वापस b1[0];
पूर्ण

अटल पूर्णांक tda10023_ग_लिखोreg (काष्ठा tda10023_state* state, u8 reg, u8 data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer (state->i2c, &msg, 1);
	अगर (ret != 1) अणु
		पूर्णांक num = state->frontend.dvb ? state->frontend.dvb->num : -1;
		prपूर्णांकk(KERN_ERR "DVB: TDA10023(%d): %s, writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			num, __func__, reg, data, ret);
	पूर्ण
	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण


अटल पूर्णांक tda10023_ग_लिखोbit (काष्ठा tda10023_state* state, u8 reg, u8 mask,u8 data)
अणु
	अगर (mask==0xff)
		वापस tda10023_ग_लिखोreg(state, reg, data);
	अन्यथा अणु
		u8 val;
		val=tda10023_पढ़ोreg(state,reg);
		val&=~mask;
		val|=(data&mask);
		वापस tda10023_ग_लिखोreg(state, reg, val);
	पूर्ण
पूर्ण

अटल व्योम tda10023_ग_लिखोtab(काष्ठा tda10023_state* state, u8* tab)
अणु
	u8 r,m,v;
	जबतक (1) अणु
		r=*tab++;
		m=*tab++;
		v=*tab++;
		अगर (r==0xff) अणु
			अगर (m==0xff)
				अवरोध;
			अन्यथा
				msleep(m);
		पूर्ण
		अन्यथा
			tda10023_ग_लिखोbit(state,r,m,v);
	पूर्ण
पूर्ण

//get access to tuner
अटल पूर्णांक lock_tuner(काष्ठा tda10023_state* state)
अणु
	u8 buf[2] = अणु 0x0f, 0xc0 पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr=state->config->demod_address, .flags=0, .buf=buf, .len=2पूर्ण;

	अगर(i2c_transfer(state->i2c, &msg, 1) != 1)
	अणु
		prपूर्णांकk("tda10023: lock tuner fails\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

//release access from tuner
अटल पूर्णांक unlock_tuner(काष्ठा tda10023_state* state)
अणु
	u8 buf[2] = अणु 0x0f, 0x40 पूर्ण;
	काष्ठा i2c_msg msg_post=अणु.addr=state->config->demod_address, .flags=0, .buf=buf, .len=2पूर्ण;

	अगर(i2c_transfer(state->i2c, &msg_post, 1) != 1)
	अणु
		prपूर्णांकk("tda10023: unlock tuner fails\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_setup_reg0 (काष्ठा tda10023_state* state, u8 reg0)
अणु
	reg0 |= state->reg0 & 0x63;

	tda10023_ग_लिखोreg (state, 0x00, reg0 & 0xfe);
	tda10023_ग_लिखोreg (state, 0x00, reg0 | 0x01);

	state->reg0 = reg0;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_set_symbolrate (काष्ठा tda10023_state* state, u32 sr)
अणु
	s32 BDR;
	s32 BDRI;
	s16 SFIL=0;
	u16 NDEC = 0;

	/* aव्योम भग्नing poपूर्णांक operations multiplying syscloc and भागider
	   by 10 */
	u32 sysclk_x_10 = state->sysclk * 10;

	अगर (sr < (u32)(sysclk_x_10/984)) अणु
		NDEC=3;
		SFIL=1;
	पूर्ण अन्यथा अगर (sr < (u32)(sysclk_x_10/640)) अणु
		NDEC=3;
		SFIL=0;
	पूर्ण अन्यथा अगर (sr < (u32)(sysclk_x_10/492)) अणु
		NDEC=2;
		SFIL=1;
	पूर्ण अन्यथा अगर (sr < (u32)(sysclk_x_10/320)) अणु
		NDEC=2;
		SFIL=0;
	पूर्ण अन्यथा अगर (sr < (u32)(sysclk_x_10/246)) अणु
		NDEC=1;
		SFIL=1;
	पूर्ण अन्यथा अगर (sr < (u32)(sysclk_x_10/160)) अणु
		NDEC=1;
		SFIL=0;
	पूर्ण अन्यथा अगर (sr < (u32)(sysclk_x_10/123)) अणु
		NDEC=0;
		SFIL=1;
	पूर्ण

	BDRI = (state->sysclk)*16;
	BDRI>>=NDEC;
	BDRI +=sr/2;
	BDRI /=sr;

	अगर (BDRI>255)
		BDRI=255;

	अणु
		u64 BDRX;

		BDRX=1<<(24+NDEC);
		BDRX*=sr;
		करो_भाग(BDRX, state->sysclk);	/* BDRX/=SYSCLK; */

		BDR=(s32)BDRX;
	पूर्ण
	dprपूर्णांकk("Symbolrate %i, BDR %i BDRI %i, NDEC %i\n",
		sr, BDR, BDRI, NDEC);
	tda10023_ग_लिखोbit (state, 0x03, 0xc0, NDEC<<6);
	tda10023_ग_लिखोreg (state, 0x0a, BDR&255);
	tda10023_ग_लिखोreg (state, 0x0b, (BDR>>8)&255);
	tda10023_ग_लिखोreg (state, 0x0c, (BDR>>16)&31);
	tda10023_ग_लिखोreg (state, 0x0d, BDRI);
	tda10023_ग_लिखोreg (state, 0x3d, (SFIL<<7));
	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_init (काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	u8 tda10023_inittab[] = अणु
/*        reg  mask val */
/* 000 */ 0x2a, 0xff, 0x02,  /* PLL3, Bypass, Power Down */
/* 003 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 006 */ 0x2a, 0xff, 0x03,  /* PLL3, Bypass, Power Down */
/* 009 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
			   /* PLL1 */
/* 012 */ 0x28, 0xff, (state->pll_m-1),
			   /* PLL2 */
/* 015 */ 0x29, 0xff, ((state->pll_p-1)<<6)|(state->pll_n-1),
			   /* GPR FSAMPLING=1 */
/* 018 */ 0x00, 0xff, REG0_INIT_VAL,
/* 021 */ 0x2a, 0xff, 0x08,  /* PLL3 PSACLK=1 */
/* 024 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 027 */ 0x1f, 0xff, 0x00,  /* RESET */
/* 030 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 033 */ 0xe6, 0x0c, 0x04,  /* RSCFG_IND */
/* 036 */ 0x10, 0xc0, 0x80,  /* DECDVBCFG1 PBER=1 */

/* 039 */ 0x0e, 0xff, 0x82,  /* GAIN1 */
/* 042 */ 0x03, 0x08, 0x08,  /* CLKCONF DYN=1 */
/* 045 */ 0x2e, 0xbf, 0x30,  /* AGCCONF2 TRIAGC=0,POSAGC=ENAGCIF=1
				       PPWMTUN=0 PPWMIF=0 */
/* 048 */ 0x01, 0xff, 0x30,  /* AGCREF */
/* 051 */ 0x1e, 0x84, 0x84,  /* CONTROL SACLK_ON=1 */
/* 054 */ 0x1b, 0xff, 0xc8,  /* ADC TWOS=1 */
/* 057 */ 0x3b, 0xff, 0xff,  /* IFMAX */
/* 060 */ 0x3c, 0xff, 0x00,  /* IFMIN */
/* 063 */ 0x34, 0xff, 0x00,  /* PWMREF */
/* 066 */ 0x35, 0xff, 0xff,  /* TUNMAX */
/* 069 */ 0x36, 0xff, 0x00,  /* TUNMIN */
/* 072 */ 0x06, 0xff, 0x7f,  /* EQCONF1 POSI=7 ENADAPT=ENEQUAL=DFE=1 */
/* 075 */ 0x1c, 0x30, 0x30,  /* EQCONF2 STEPALGO=SGNALGO=1 */
/* 078 */ 0x37, 0xff, 0xf6,  /* DELTAF_LSB */
/* 081 */ 0x38, 0xff, 0xff,  /* DELTAF_MSB */
/* 084 */ 0x02, 0xff, 0x93,  /* AGCCONF1  IFS=1 KAGCIF=2 KAGCTUN=3 */
/* 087 */ 0x2d, 0xff, 0xf6,  /* SWEEP SWPOS=1 SWDYN=7 SWSTEP=1 SWLEN=2 */
/* 090 */ 0x04, 0x10, 0x00,  /* SWRAMP=1 */
/* 093 */ 0x12, 0xff, TDA10023_OUTPUT_MODE_PARALLEL_B, /*
				INTP1 POCLKP=1 FEL=1 MFS=0 */
/* 096 */ 0x2b, 0x01, 0xa1,  /* INTS1 */
/* 099 */ 0x20, 0xff, 0x04,  /* INTP2 SWAPP=? MSBFIRSTP=? INTPSEL=? */
/* 102 */ 0x2c, 0xff, 0x0d,  /* INTP/S TRIP=0 TRIS=0 */
/* 105 */ 0xc4, 0xff, 0x00,
/* 108 */ 0xc3, 0x30, 0x00,
/* 111 */ 0xb5, 0xff, 0x19,  /* ERAGC_THD */
/* 114 */ 0x00, 0x03, 0x01,  /* GPR, CLBS soft reset */
/* 117 */ 0x00, 0x03, 0x03,  /* GPR, CLBS soft reset */
/* 120 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 123 */ 0xff, 0xff, 0xff
पूर्ण;
	dprपूर्णांकk("DVB: TDA10023(%d): init chip\n", fe->dvb->num);

	/* override शेष values अगर set in config */
	अगर (state->config->deltaf) अणु
		tda10023_inittab[80] = (state->config->deltaf & 0xff);
		tda10023_inittab[83] = (state->config->deltaf >> 8);
	पूर्ण

	अगर (state->config->output_mode)
		tda10023_inittab[95] = state->config->output_mode;

	tda10023_ग_लिखोtab(state, tda10023_inittab);

	वापस 0;
पूर्ण

काष्ठा qam_params अणु
	u8 qam, lockthr, mseth, aref, agcrefnyq, eragnyq_thd;
पूर्ण;

अटल पूर्णांक tda10023_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys  = c->delivery_प्रणाली;
	अचिन्हित qam = c->modulation;
	bool is_annex_c;
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	अटल स्थिर काष्ठा qam_params qam_params[] = अणु
		/* Modulation  QAM    LOCKTHR   MSETH   AREF AGCREFNYQ ERAGCNYQ_THD */
		[QPSK]    = अणु (5<<2),  0x78,    0x8c,   0x96,   0x78,   0x4c  पूर्ण,
		[QAM_16]  = अणु (0<<2),  0x87,    0xa2,   0x91,   0x8c,   0x57  पूर्ण,
		[QAM_32]  = अणु (1<<2),  0x64,    0x74,   0x96,   0x8c,   0x57  पूर्ण,
		[QAM_64]  = अणु (2<<2),  0x46,    0x43,   0x6a,   0x6a,   0x44  पूर्ण,
		[QAM_128] = अणु (3<<2),  0x36,    0x34,   0x7e,   0x78,   0x4c  पूर्ण,
		[QAM_256] = अणु (4<<2),  0x26,    0x23,   0x6c,   0x5c,   0x3c  पूर्ण,
	पूर्ण;

	चयन (delsys) अणु
	हाल SYS_DVBC_ANNEX_A:
		is_annex_c = false;
		अवरोध;
	हाल SYS_DVBC_ANNEX_C:
		is_annex_c = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * gcc optimizes the code below the same way as it would code:
	 *		 "if (qam > 5) return -EINVAL;"
	 * Yet, the code is clearer, as it shows what QAM standards are
	 * supported by the driver, and aव्योमs the usage of magic numbers on
	 * it.
	 */
	चयन (qam) अणु
	हाल QPSK:
	हाल QAM_16:
	हाल QAM_32:
	हाल QAM_64:
	हाल QAM_128:
	हाल QAM_256:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	tda10023_set_symbolrate(state, c->symbol_rate);
	tda10023_ग_लिखोreg(state, 0x05, qam_params[qam].lockthr);
	tda10023_ग_लिखोreg(state, 0x08, qam_params[qam].mseth);
	tda10023_ग_लिखोreg(state, 0x09, qam_params[qam].aref);
	tda10023_ग_लिखोreg(state, 0xb4, qam_params[qam].agcrefnyq);
	tda10023_ग_लिखोreg(state, 0xb6, qam_params[qam].eragnyq_thd);
#अगर 0
	tda10023_ग_लिखोreg(state, 0x04, (c->inversion ? 0x12 : 0x32));
	tda10023_ग_लिखोbit(state, 0x04, 0x60, (c->inversion ? 0 : 0x20));
#पूर्ण_अगर
	tda10023_ग_लिखोbit(state, 0x04, 0x40, 0x40);

	अगर (is_annex_c)
		tda10023_ग_लिखोbit(state, 0x3d, 0xfc, 0x03);
	अन्यथा
		tda10023_ग_लिखोbit(state, 0x3d, 0xfc, 0x02);

	tda10023_setup_reg0(state, qam_params[qam].qam);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_पढ़ो_status(काष्ठा dvb_frontend *fe,
				क्रमागत fe_status *status)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	पूर्णांक sync;

	*status = 0;

	//0x11[1] == CARLOCK -> Carrier locked
	//0x11[2] == FSYNC -> Frame synchronisation
	//0x11[3] == FEL -> Front End locked
	//0x11[6] == NODVB -> DVB Mode Inक्रमmation
	sync = tda10023_पढ़ोreg (state, 0x11);

	अगर (sync & 2)
		*status |= FE_HAS_SIGNAL|FE_HAS_CARRIER;

	अगर (sync & 4)
		*status |= FE_HAS_SYNC|FE_HAS_VITERBI;

	अगर (sync & 8)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	u8 a,b,c;
	a=tda10023_पढ़ोreg(state, 0x14);
	b=tda10023_पढ़ोreg(state, 0x15);
	c=tda10023_पढ़ोreg(state, 0x16)&0xf;
	tda10023_ग_लिखोbit (state, 0x10, 0xc0, 0x00);

	*ber = a | (b<<8)| (c<<16);
	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	u8 अगरgain=tda10023_पढ़ोreg(state, 0x2f);

	u16 gain = ((255-tda10023_पढ़ोreg(state, 0x17))) + (255-अगरgain)/16;
	// Max raw value is about 0xb0 -> Normalize to >0xf0 after 0x90
	अगर (gain>0x90)
		gain=gain+2*(gain-0x90);
	अगर (gain>255)
		gain=255;

	*strength = (gain<<8)|gain;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;

	u8 quality = ~tda10023_पढ़ोreg(state, 0x18);
	*snr = (quality << 8) | quality;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	u8 a,b,c,d;
	a= tda10023_पढ़ोreg (state, 0x74);
	b= tda10023_पढ़ोreg (state, 0x75);
	c= tda10023_पढ़ोreg (state, 0x76);
	d= tda10023_पढ़ोreg (state, 0x77);
	*ucblocks = a | (b<<8)|(c<<16)|(d<<24);

	tda10023_ग_लिखोbit (state, 0x10, 0x20,0x00);
	tda10023_ग_लिखोbit (state, 0x10, 0x20,0x20);
	tda10023_ग_लिखोbit (state, 0x13, 0x01, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	पूर्णांक sync,inv;
	s8 afc = 0;

	sync = tda10023_पढ़ोreg(state, 0x11);
	afc = tda10023_पढ़ोreg(state, 0x19);
	inv = tda10023_पढ़ोreg(state, 0x04);

	अगर (verbose) अणु
		/* AFC only valid when carrier has been recovered */
		prपूर्णांकk(sync & 2 ? "DVB: TDA10023(%d): AFC (%d) %dHz\n" :
				  "DVB: TDA10023(%d): [AFC (%d) %dHz]\n",
			state->frontend.dvb->num, afc,
		       -((s32)p->symbol_rate * afc) >> 10);
	पूर्ण

	p->inversion = (inv&0x20?0:1);
	p->modulation = ((state->reg0 >> 2) & 7) + QAM_16;

	p->fec_inner = FEC_NONE;
	p->frequency = ((p->frequency + 31250) / 62500) * 62500;

	अगर (sync & 2)
		p->frequency -= ((s32)p->symbol_rate * afc) >> 10;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;

	tda10023_ग_लिखोreg (state, 0x1b, 0x02);  /* pकरोwn ADC */
	tda10023_ग_लिखोreg (state, 0x00, 0x80);  /* standby */

	वापस 0;
पूर्ण

अटल पूर्णांक tda10023_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		lock_tuner(state);
	पूर्ण अन्यथा अणु
		unlock_tuner(state);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tda10023_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda10023_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10023_ops;

काष्ठा dvb_frontend *tda10023_attach(स्थिर काष्ठा tda10023_config *config,
				     काष्ठा i2c_adapter *i2c,
				     u8 pwm)
अणु
	काष्ठा tda10023_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा tda10023_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* wakeup अगर in standby */
	tda10023_ग_लिखोreg (state, 0x00, 0x33);
	/* check अगर the demod is there */
	अगर ((tda10023_पढ़ोreg(state, 0x1a) & 0xf0) != 0x70) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &tda10023_ops, माप(काष्ठा dvb_frontend_ops));
	state->pwm = pwm;
	state->reg0 = REG0_INIT_VAL;
	अगर (state->config->xtal) अणु
		state->xtal  = state->config->xtal;
		state->pll_m = state->config->pll_m;
		state->pll_p = state->config->pll_p;
		state->pll_n = state->config->pll_n;
	पूर्ण अन्यथा अणु
		/* set शेष values अगर not defined in config */
		state->xtal  = 28920000;
		state->pll_m = 8;
		state->pll_p = 4;
		state->pll_n = 1;
	पूर्ण

	/* calc sysclk */
	state->sysclk = (state->xtal * state->pll_m / \
			(state->pll_n * state->pll_p));

	state->frontend.ops.info.symbol_rate_min = (state->sysclk/2)/64;
	state->frontend.ops.info.symbol_rate_max = (state->sysclk/2)/4;

	dprपूर्णांकk("DVB: TDA10023 %s: xtal:%d pll_m:%d pll_p:%d pll_n:%d\n",
		__func__, state->xtal, state->pll_m, state->pll_p,
		state->pll_n);

	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10023_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A, SYS_DVBC_ANNEX_C पूर्ण,
	.info = अणु
		.name = "Philips TDA10023 DVB-C",
		.frequency_min_hz =  47 * MHz,
		.frequency_max_hz = 862 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min = 0,  /* set in tda10023_attach */
		.symbol_rate_max = 0,  /* set in tda10023_attach */
		.caps = 0x400 | //FE_CAN_QAM_4
			FE_CAN_QAM_16 | FE_CAN_QAM_32 | FE_CAN_QAM_64 |
			FE_CAN_QAM_128 | FE_CAN_QAM_256 |
			FE_CAN_FEC_AUTO
	पूर्ण,

	.release = tda10023_release,

	.init = tda10023_init,
	.sleep = tda10023_sleep,
	.i2c_gate_ctrl = tda10023_i2c_gate_ctrl,

	.set_frontend = tda10023_set_parameters,
	.get_frontend = tda10023_get_frontend,
	.पढ़ो_status = tda10023_पढ़ो_status,
	.पढ़ो_ber = tda10023_पढ़ो_ber,
	.पढ़ो_संकेत_strength = tda10023_पढ़ो_संकेत_strength,
	.पढ़ो_snr = tda10023_पढ़ो_snr,
	.पढ़ो_ucblocks = tda10023_पढ़ो_ucblocks,
पूर्ण;


MODULE_DESCRIPTION("Philips TDA10023 DVB-C demodulator driver");
MODULE_AUTHOR("Georg Acher, Hartmut Birr");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(tda10023_attach);
