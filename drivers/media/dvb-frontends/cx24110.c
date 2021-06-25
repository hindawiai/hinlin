<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    cx24110 - Single Chip Satellite Channel Receiver driver module

    Copyright (C) 2002 Peter Hettkamp <peter.hettkamp@htp-tel.de> based on
    work
    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>


*/

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <media/dvb_frontend.h>
#समावेश "cx24110.h"


काष्ठा cx24110_state अणु

	काष्ठा i2c_adapter* i2c;

	स्थिर काष्ठा cx24110_config* config;

	काष्ठा dvb_frontend frontend;

	u32 lastber;
	u32 lastbler;
	u32 lastesn0;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "cx24110: " args); \
	पूर्ण जबतक (0)

अटल काष्ठा अणुu8 reg; u8 data;पूर्ण cx24110_regdata[]=
		      /* Comments beginning with @ denote this value should
			 be the शेष */
	अणुअणु0x09,0x01पूर्ण, /* SoftResetAll */
	 अणु0x09,0x00पूर्ण, /* release reset */
	 अणु0x01,0xe8पूर्ण, /* MSB of code rate 27.5MS/s */
	 अणु0x02,0x17पूर्ण, /* middle byte " */
	 अणु0x03,0x29पूर्ण, /* LSB         " */
	 अणु0x05,0x03पूर्ण, /* @ DVB mode, standard code rate 3/4 */
	 अणु0x06,0xa5पूर्ण, /* @ PLL 60MHz */
	 अणु0x07,0x01पूर्ण, /* @ Fclk, i.e. sampling घड़ी, 60MHz */
	 अणु0x0a,0x00पूर्ण, /* @ partial chip disables, करो not set */
	 अणु0x0b,0x01पूर्ण, /* set output घड़ी in gapped mode, start संकेत low
			 active क्रम first byte */
	 अणु0x0c,0x11पूर्ण, /* no parity bytes, large hold समय, serial data out */
	 अणु0x0d,0x6fपूर्ण, /* @ RS Sync/Unsync thresholds */
	 अणु0x10,0x40पूर्ण, /* chip करोc is misleading here: ग_लिखो bit 6 as 1
			 to aव्योम starting the BER counter. Reset the
			 CRC test bit. Finite counting selected */
	 अणु0x15,0xffपूर्ण, /* @ size of the limited समय winकरोw क्रम RS BER
			 estimation. It is <value>*256 RS blocks, this
			 gives approx. 2.6 sec at 27.5MS/s, rate 3/4 */
	 अणु0x16,0x00पूर्ण, /* @ enable all RS output ports */
	 अणु0x17,0x04पूर्ण, /* @ समय winकरोw allowed क्रम the RS to sync */
	 अणु0x18,0xaeपूर्ण, /* @ allow all standard DVB code rates to be scanned
			 क्रम स्वतःmatically */
		      /* leave the current code rate and normalization
			 रेजिस्टरs as they are after reset... */
	 अणु0x21,0x10पूर्ण, /* @ during AutoAcq, search each viterbi setting
			 only once */
	 अणु0x23,0x18पूर्ण, /* @ size of the limited समय winकरोw क्रम Viterbi BER
			 estimation. It is <value>*65536 channel bits, i.e.
			 approx. 38ms at 27.5MS/s, rate 3/4 */
	 अणु0x24,0x24पूर्ण, /* करो not trigger Viterbi CRC test. Finite count winकरोw */
		      /* leave front-end AGC parameters at शेष values */
		      /* leave decimation AGC parameters at शेष values */
	 अणु0x35,0x40पूर्ण, /* disable all पूर्णांकerrupts. They are not connected anyway */
	 अणु0x36,0xffपूर्ण, /* clear all पूर्णांकerrupt pending flags */
	 अणु0x37,0x00पूर्ण, /* @ fully enable AutoAcqq state machine */
	 अणु0x38,0x07पूर्ण, /* @ enable fade recovery, but not स्वतःstart AutoAcq */
		      /* leave the equalizer parameters on their शेष values */
		      /* leave the final AGC parameters on their शेष values */
	 अणु0x41,0x00पूर्ण, /* @ MSB of front-end derotator frequency */
	 अणु0x42,0x00पूर्ण, /* @ middle bytes " */
	 अणु0x43,0x00पूर्ण, /* @ LSB          " */
		      /* leave the carrier tracking loop parameters on शेष */
		      /* leave the bit timing loop parameters at शेष */
	 अणु0x56,0x4dपूर्ण, /* set the filtune voltage to 2.7V, as recommended by */
		      /* the cx24108 data sheet क्रम symbol rates above 15MS/s */
	 अणु0x57,0x00पूर्ण, /* @ Filter sigma delta enabled, positive */
	 अणु0x61,0x95पूर्ण, /* GPIO pins 1-4 have special function */
	 अणु0x62,0x05पूर्ण, /* GPIO pin 5 has special function, pin 6 is GPIO */
	 अणु0x63,0x00पूर्ण, /* All GPIO pins use CMOS output अक्षरacteristics */
	 अणु0x64,0x20पूर्ण, /* GPIO 6 is input, all others are outमाला_दो */
	 अणु0x6d,0x30पूर्ण, /* tuner स्वतः mode घड़ी freq 62kHz */
	 अणु0x70,0x15पूर्ण, /* use स्वतः mode, tuner word is 21 bits दीर्घ */
	 अणु0x73,0x00पूर्ण, /* @ disable several demod bypasses */
	 अणु0x74,0x00पूर्ण, /* @  " */
	 अणु0x75,0x00पूर्ण  /* @  " */
		      /* the reमुख्यing रेजिस्टरs are क्रम SEC */
	पूर्ण;


अटल पूर्णांक cx24110_ग_लिखोreg (काष्ठा cx24110_state* state, पूर्णांक reg, पूर्णांक data)
अणु
	u8 buf [] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक err;

	अगर ((err = i2c_transfer(state->i2c, &msg, 1)) != 1) अणु
		dprपूर्णांकk("%s: writereg error (err == %i, reg == 0x%02x, data == 0x%02x)\n",
			__func__, err, reg, data);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_पढ़ोreg (काष्ठा cx24110_state* state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0 [] = अणु reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 1 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) वापस ret;

	वापस b1[0];
पूर्ण

अटल पूर्णांक cx24110_set_inversion(काष्ठा cx24110_state *state,
				 क्रमागत fe_spectral_inversion inversion)
अणु
/* fixme (low): error handling */

	चयन (inversion) अणु
	हाल INVERSION_OFF:
		cx24110_ग_लिखोreg(state,0x37,cx24110_पढ़ोreg(state,0x37)|0x1);
		/* AcqSpectrInvDis on. No idea why someone should want this */
		cx24110_ग_लिखोreg(state,0x5,cx24110_पढ़ोreg(state,0x5)&0xf7);
		/* Initial value 0 at start of acq */
		cx24110_ग_लिखोreg(state,0x22,cx24110_पढ़ोreg(state,0x22)&0xef);
		/* current value 0 */
		/* The cx24110 manual tells us this reg is पढ़ो-only.
		   But what the heck... set it ayways */
		अवरोध;
	हाल INVERSION_ON:
		cx24110_ग_लिखोreg(state,0x37,cx24110_पढ़ोreg(state,0x37)|0x1);
		/* AcqSpectrInvDis on. No idea why someone should want this */
		cx24110_ग_लिखोreg(state,0x5,cx24110_पढ़ोreg(state,0x5)|0x08);
		/* Initial value 1 at start of acq */
		cx24110_ग_लिखोreg(state,0x22,cx24110_पढ़ोreg(state,0x22)|0x10);
		/* current value 1 */
		अवरोध;
	हाल INVERSION_AUTO:
		cx24110_ग_लिखोreg(state,0x37,cx24110_पढ़ोreg(state,0x37)&0xfe);
		/* AcqSpectrInvDis off. Leave initial & current states as is */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_set_fec(काष्ठा cx24110_state *state, क्रमागत fe_code_rate fec)
अणु
	अटल स्थिर पूर्णांक rate[FEC_AUTO] = अणु-1,    1,    2,    3,    5,    7, -1पूर्ण;
	अटल स्थिर पूर्णांक g1[FEC_AUTO]   = अणु-1, 0x01, 0x02, 0x05, 0x15, 0x45, -1पूर्ण;
	अटल स्थिर पूर्णांक g2[FEC_AUTO]   = अणु-1, 0x01, 0x03, 0x06, 0x1a, 0x7a, -1पूर्ण;

	/* Well, the AutoAcq engine of the cx24106 and 24110 स्वतःmatically
	   searches all enabled viterbi rates, and can handle non-standard
	   rates as well. */

	अगर (fec > FEC_AUTO)
		fec = FEC_AUTO;

	अगर (fec == FEC_AUTO) अणु /* (re-)establish AutoAcq behaviour */
		cx24110_ग_लिखोreg(state, 0x37, cx24110_पढ़ोreg(state, 0x37) & 0xdf);
		/* clear AcqVitDis bit */
		cx24110_ग_लिखोreg(state, 0x18, 0xae);
		/* allow all DVB standard code rates */
		cx24110_ग_लिखोreg(state, 0x05, (cx24110_पढ़ोreg(state, 0x05) & 0xf0) | 0x3);
		/* set nominal Viterbi rate 3/4 */
		cx24110_ग_लिखोreg(state, 0x22, (cx24110_पढ़ोreg(state, 0x22) & 0xf0) | 0x3);
		/* set current Viterbi rate 3/4 */
		cx24110_ग_लिखोreg(state, 0x1a, 0x05);
		cx24110_ग_लिखोreg(state, 0x1b, 0x06);
		/* set the puncture रेजिस्टरs क्रम code rate 3/4 */
		वापस 0;
	पूर्ण अन्यथा अणु
		cx24110_ग_लिखोreg(state, 0x37, cx24110_पढ़ोreg(state, 0x37) | 0x20);
		/* set AcqVitDis bit */
		अगर (rate[fec] < 0)
			वापस -EINVAL;

		cx24110_ग_लिखोreg(state, 0x05, (cx24110_पढ़ोreg(state, 0x05) & 0xf0) | rate[fec]);
		/* set nominal Viterbi rate */
		cx24110_ग_लिखोreg(state, 0x22, (cx24110_पढ़ोreg(state, 0x22) & 0xf0) | rate[fec]);
		/* set current Viterbi rate */
		cx24110_ग_लिखोreg(state, 0x1a, g1[fec]);
		cx24110_ग_लिखोreg(state, 0x1b, g2[fec]);
		/* not sure अगर this is the right way: I always used AutoAcq mode */
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत fe_code_rate cx24110_get_fec(काष्ठा cx24110_state *state)
अणु
	पूर्णांक i;

	i=cx24110_पढ़ोreg(state,0x22)&0x0f;
	अगर(!(i&0x08)) अणु
		वापस FEC_1_2 + i - 1;
	पूर्ण अन्यथा अणु
/* fixme (low): a special code rate has been selected. In theory, we need to
   वापस a denominator value, a numerator value, and a pair of puncture
   maps to correctly describe this mode. But this should never happen in
   practice, because it cannot be set by cx24110_get_fec. */
	   वापस FEC_NONE;
	पूर्ण
पूर्ण

अटल पूर्णांक cx24110_set_symbolrate (काष्ठा cx24110_state* state, u32 srate)
अणु
/* fixme (low): add error handling */
	u32 ratio;
	u32 पंचांगp, fclk, BDRI;

	अटल स्थिर u32 bands[]=अणु5000000UL,15000000UL,90999000UL/2पूर्ण;
	पूर्णांक i;

	dprपूर्णांकk("cx24110 debug: entering %s(%d)\n",__func__,srate);
	अगर (srate>90999000UL/2)
		srate=90999000UL/2;
	अगर (srate<500000)
		srate=500000;

	क्रम(i = 0; (i < ARRAY_SIZE(bands)) && (srate>bands[i]); i++)
		;
	/* first, check which sample rate is appropriate: 45, 60 80 or 90 MHz,
	   and set the PLL accordingly (R07[1:0] Fclk, R06[7:4] PLLmult,
	   R06[3:0] PLLphaseDetGain */
	पंचांगp=cx24110_पढ़ोreg(state,0x07)&0xfc;
	अगर(srate<90999000UL/4) अणु /* sample rate 45MHz*/
		cx24110_ग_लिखोreg(state,0x07,पंचांगp);
		cx24110_ग_लिखोreg(state,0x06,0x78);
		fclk=90999000UL/2;
	पूर्ण अन्यथा अगर(srate<60666000UL/2) अणु /* sample rate 60MHz */
		cx24110_ग_लिखोreg(state,0x07,पंचांगp|0x1);
		cx24110_ग_लिखोreg(state,0x06,0xa5);
		fclk=60666000UL;
	पूर्ण अन्यथा अगर(srate<80888000UL/2) अणु /* sample rate 80MHz */
		cx24110_ग_लिखोreg(state,0x07,पंचांगp|0x2);
		cx24110_ग_लिखोreg(state,0x06,0x87);
		fclk=80888000UL;
	पूर्ण अन्यथा अणु /* sample rate 90MHz */
		cx24110_ग_लिखोreg(state,0x07,पंचांगp|0x3);
		cx24110_ग_लिखोreg(state,0x06,0x78);
		fclk=90999000UL;
	पूर्ण
	dprपूर्णांकk("cx24110 debug: fclk %d Hz\n",fclk);
	/* we need to भागide two पूर्णांकegers with approx. 27 bits in 32 bit
	   arithmetic giving a 25 bit result */
	/* the maximum भागidend is 90999000/2, 0x02b6446c, this number is
	   also the most complex भागisor. Hence, the भागidend has,
	   assuming 32bit अचिन्हित arithmetic, 6 clear bits on top, the
	   भागisor 2 unused bits at the bottom. Also, the quotient is
	   always less than 1/2. Borrowed from VES1893.c, of course */

	पंचांगp=srate<<6;
	BDRI=fclk>>2;
	ratio=(पंचांगp/BDRI);

	पंचांगp=(पंचांगp%BDRI)<<8;
	ratio=(ratio<<8)+(पंचांगp/BDRI);

	पंचांगp=(पंचांगp%BDRI)<<8;
	ratio=(ratio<<8)+(पंचांगp/BDRI);

	पंचांगp=(पंचांगp%BDRI)<<1;
	ratio=(ratio<<1)+(पंचांगp/BDRI);

	dprपूर्णांकk("srate= %d (range %d, up to %d)\n", srate,i,bands[i]);
	dprपूर्णांकk("fclk = %d\n", fclk);
	dprपूर्णांकk("ratio= %08x\n", ratio);

	cx24110_ग_लिखोreg(state, 0x1, (ratio>>16)&0xff);
	cx24110_ग_लिखोreg(state, 0x2, (ratio>>8)&0xff);
	cx24110_ग_लिखोreg(state, 0x3, (ratio)&0xff);

	वापस 0;

पूर्ण

अटल पूर्णांक _cx24110_pll_ग_लिखो (काष्ठा dvb_frontend* fe, स्थिर u8 buf[], पूर्णांक len)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

	अगर (len != 3)
		वापस -EINVAL;

/* tuner data is 21 bits दीर्घ, must be left-aligned in data */
/* tuner cx24108 is written through a dedicated 3wire पूर्णांकerface on the demod chip */
/* FIXME (low): add error handling, aव्योम infinite loops अगर HW fails... */

	cx24110_ग_लिखोreg(state,0x6d,0x30); /* स्वतः mode at 62kHz */
	cx24110_ग_लिखोreg(state,0x70,0x15); /* स्वतः mode 21 bits */

	/* अगर the स्वतः tuner ग_लिखोr is still busy, clear it out */
	जबतक (cx24110_पढ़ोreg(state,0x6d)&0x80)
		cx24110_ग_लिखोreg(state,0x72,0);

	/* ग_लिखो the topmost 8 bits */
	cx24110_ग_लिखोreg(state,0x72,buf[0]);

	/* रुको क्रम the send to be completed */
	जबतक ((cx24110_पढ़ोreg(state,0x6d)&0xc0)==0x80)
		;

	/* send another 8 bytes */
	cx24110_ग_लिखोreg(state,0x72,buf[1]);
	जबतक ((cx24110_पढ़ोreg(state,0x6d)&0xc0)==0x80)
		;

	/* and the topmost 5 bits of this byte */
	cx24110_ग_लिखोreg(state,0x72,buf[2]);
	जबतक ((cx24110_पढ़ोreg(state,0x6d)&0xc0)==0x80)
		;

	/* now strobe the enable line once */
	cx24110_ग_लिखोreg(state,0x6d,0x32);
	cx24110_ग_लिखोreg(state,0x6d,0x30);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_initfe(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;
/* fixme (low): error handling */
	पूर्णांक i;

	dprपूर्णांकk("%s: init chip\n", __func__);

	क्रम(i = 0; i < ARRAY_SIZE(cx24110_regdata); i++) अणु
		cx24110_ग_लिखोreg(state, cx24110_regdata[i].reg, cx24110_regdata[i].data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		वापस cx24110_ग_लिखोreg(state,0x76,(cx24110_पढ़ोreg(state,0x76)&0x3b)|0xc0);
	हाल SEC_VOLTAGE_18:
		वापस cx24110_ग_लिखोreg(state,0x76,(cx24110_पढ़ोreg(state,0x76)&0x3b)|0x40);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक cx24110_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	पूर्णांक rv, bit;
	काष्ठा cx24110_state *state = fe->demodulator_priv;
	अचिन्हित दीर्घ समयout;

	अगर (burst == SEC_MINI_A)
		bit = 0x00;
	अन्यथा अगर (burst == SEC_MINI_B)
		bit = 0x08;
	अन्यथा
		वापस -EINVAL;

	rv = cx24110_पढ़ोreg(state, 0x77);
	अगर (!(rv & 0x04))
		cx24110_ग_लिखोreg(state, 0x77, rv | 0x04);

	rv = cx24110_पढ़ोreg(state, 0x76);
	cx24110_ग_लिखोreg(state, 0x76, ((rv & 0x90) | 0x40 | bit));
	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (!समय_after(jअगरfies, समयout) && !(cx24110_पढ़ोreg(state, 0x76) & 0x40))
		; /* रुको क्रम LNB पढ़ोy */

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_send_diseqc_msg(काष्ठा dvb_frontend* fe,
				   काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	पूर्णांक i, rv;
	काष्ठा cx24110_state *state = fe->demodulator_priv;
	अचिन्हित दीर्घ समयout;

	अगर (cmd->msg_len < 3 || cmd->msg_len > 6)
		वापस -EINVAL;  /* not implemented */

	क्रम (i = 0; i < cmd->msg_len; i++)
		cx24110_ग_लिखोreg(state, 0x79 + i, cmd->msg[i]);

	rv = cx24110_पढ़ोreg(state, 0x77);
	अगर (rv & 0x04) अणु
		cx24110_ग_लिखोreg(state, 0x77, rv & ~0x04);
		msleep(30); /* reportedly fixes चयनing problems */
	पूर्ण

	rv = cx24110_पढ़ोreg(state, 0x76);

	cx24110_ग_लिखोreg(state, 0x76, ((rv & 0x90) | 0x40) | ((cmd->msg_len-3) & 3));
	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (!समय_after(jअगरfies, समयout) && !(cx24110_पढ़ोreg(state, 0x76) & 0x40))
		; /* रुको क्रम LNB पढ़ोy */

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

	पूर्णांक sync = cx24110_पढ़ोreg (state, 0x55);

	*status = 0;

	अगर (sync & 0x10)
		*status |= FE_HAS_SIGNAL;

	अगर (sync & 0x08)
		*status |= FE_HAS_CARRIER;

	sync = cx24110_पढ़ोreg (state, 0x08);

	अगर (sync & 0x40)
		*status |= FE_HAS_VITERBI;

	अगर (sync & 0x20)
		*status |= FE_HAS_SYNC;

	अगर ((sync & 0x60) == 0x60)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

	/* fixme (maybe): value range is 16 bit. Scale? */
	अगर(cx24110_पढ़ोreg(state,0x24)&0x10) अणु
		/* the Viterbi error counter has finished one counting winकरोw */
		cx24110_ग_लिखोreg(state,0x24,0x04); /* select the ber reg */
		state->lastber=cx24110_पढ़ोreg(state,0x25)|
			(cx24110_पढ़ोreg(state,0x26)<<8);
		cx24110_ग_लिखोreg(state,0x24,0x04); /* start new count winकरोw */
		cx24110_ग_लिखोreg(state,0x24,0x14);
	पूर्ण
	*ber = state->lastber;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* संकेत_strength)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

/* no provision in hardware. Read the frontend AGC accumulator. No idea how to scale this, but I know it is 2s complement */
	u8 संकेत = cx24110_पढ़ोreg (state, 0x27)+128;
	*संकेत_strength = (संकेत << 8) | संकेत;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

	/* no provision in hardware. Can be computed from the Es/N0 estimator, but I करोn't know how. */
	अगर(cx24110_पढ़ोreg(state,0x6a)&0x80) अणु
		/* the Es/N0 error counter has finished one counting winकरोw */
		state->lastesn0=cx24110_पढ़ोreg(state,0x69)|
			(cx24110_पढ़ोreg(state,0x68)<<8);
		cx24110_ग_लिखोreg(state,0x6a,0x84); /* start new count winकरोw */
	पूर्ण
	*snr = state->lastesn0;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

	अगर(cx24110_पढ़ोreg(state,0x10)&0x40) अणु
		/* the RS error counter has finished one counting winकरोw */
		cx24110_ग_लिखोreg(state,0x10,0x60); /* select the byer reg */
		(व्योम)(cx24110_पढ़ोreg(state, 0x12) |
			(cx24110_पढ़ोreg(state, 0x13) << 8) |
			(cx24110_पढ़ोreg(state, 0x14) << 16));
		cx24110_ग_लिखोreg(state,0x10,0x70); /* select the bler reg */
		state->lastbler=cx24110_पढ़ोreg(state,0x12)|
			(cx24110_पढ़ोreg(state,0x13)<<8)|
			(cx24110_पढ़ोreg(state,0x14)<<16);
		cx24110_ग_लिखोreg(state,0x10,0x20); /* start new count winकरोw */
	पूर्ण
	*ucblocks = state->lastbler;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	cx24110_set_inversion(state, p->inversion);
	cx24110_set_fec(state, p->fec_inner);
	cx24110_set_symbolrate(state, p->symbol_rate);
	cx24110_ग_लिखोreg(state,0x04,0x05); /* start acquisition */

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;
	s32 afc; अचिन्हित sclk;

/* cannot पढ़ो back tuner settings (freq). Need to have some निजी storage */

	sclk = cx24110_पढ़ोreg (state, 0x07) & 0x03;
/* ok, real AFC (FEDR) freq. is afc/2^24*fsamp, fsamp=45/60/80/90MHz.
 * Need 64 bit arithmetic. Is thiss possible in the kernel? */
	अगर (sclk==0) sclk=90999000L/2L;
	अन्यथा अगर (sclk==1) sclk=60666000L;
	अन्यथा अगर (sclk==2) sclk=80888000L;
	अन्यथा sclk=90999000L;
	sclk>>=8;
	afc = sclk*(cx24110_पढ़ोreg (state, 0x44)&0x1f)+
	      ((sclk*cx24110_पढ़ोreg (state, 0x45))>>8)+
	      ((sclk*cx24110_पढ़ोreg (state, 0x46))>>16);

	p->frequency += afc;
	p->inversion = (cx24110_पढ़ोreg (state, 0x22) & 0x10) ?
				INVERSION_ON : INVERSION_OFF;
	p->fec_inner = cx24110_get_fec(state);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24110_set_tone(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा cx24110_state *state = fe->demodulator_priv;

	वापस cx24110_ग_लिखोreg(state,0x76,(cx24110_पढ़ोreg(state,0x76)&~0x10)|(((tone==SEC_TONE_ON))?0x10:0));
पूर्ण

अटल व्योम cx24110_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा cx24110_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24110_ops;

काष्ठा dvb_frontend* cx24110_attach(स्थिर काष्ठा cx24110_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा cx24110_state* state = शून्य;
	पूर्णांक ret;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा cx24110_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->lastber = 0;
	state->lastbler = 0;
	state->lastesn0 = 0;

	/* check अगर the demod is there */
	ret = cx24110_पढ़ोreg(state, 0x00);
	अगर ((ret != 0x5a) && (ret != 0x69)) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &cx24110_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24110_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name = "Conexant CX24110 DVB-S",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		.frequency_stepsize_hz = 1011 * kHz,
		.frequency_tolerance_hz = 29500 * kHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_RECOVER
	पूर्ण,

	.release = cx24110_release,

	.init = cx24110_initfe,
	.ग_लिखो = _cx24110_pll_ग_लिखो,
	.set_frontend = cx24110_set_frontend,
	.get_frontend = cx24110_get_frontend,
	.पढ़ो_status = cx24110_पढ़ो_status,
	.पढ़ो_ber = cx24110_पढ़ो_ber,
	.पढ़ो_संकेत_strength = cx24110_पढ़ो_संकेत_strength,
	.पढ़ो_snr = cx24110_पढ़ो_snr,
	.पढ़ो_ucblocks = cx24110_पढ़ो_ucblocks,

	.diseqc_send_master_cmd = cx24110_send_diseqc_msg,
	.set_tone = cx24110_set_tone,
	.set_voltage = cx24110_set_voltage,
	.diseqc_send_burst = cx24110_diseqc_send_burst,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Conexant CX24110 DVB-S Demodulator driver");
MODULE_AUTHOR("Peter Hettkamp");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(cx24110_attach);
