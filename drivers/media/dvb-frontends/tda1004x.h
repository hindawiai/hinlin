<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
  /*
     Driver क्रम Philips tda1004xh OFDM Frontend

     (c) 2004 Andrew de Quincey


   */

#अगर_अघोषित TDA1004X_H
#घोषणा TDA1004X_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

क्रमागत tda10046_xtal अणु
	TDA10046_XTAL_4M,
	TDA10046_XTAL_16M,
पूर्ण;

क्रमागत tda10046_agc अणु
	TDA10046_AGC_DEFAULT,		/* original configuration */
	TDA10046_AGC_IFO_AUTO_NEG,	/* IF AGC only, स्वतःmatic, negative */
	TDA10046_AGC_IFO_AUTO_POS,	/* IF AGC only, स्वतःmatic, positive */
	TDA10046_AGC_TDA827X,		/* IF AGC only, special setup क्रम tda827x */
पूर्ण;

/* Many (hybrid) boards use GPIO 1 and 3
	GPIO1	analog - dvb चयन
	GPIO3	firmware eeprom address चयन
*/
क्रमागत tda10046_gpio अणु
	TDA10046_GPTRI  = 0x00,		/* All GPIOs tristate */
	TDA10046_GP00   = 0x40,		/* GPIO3=0, GPIO1=0 */
	TDA10046_GP01   = 0x42,		/* GPIO3=0, GPIO1=1 */
	TDA10046_GP10   = 0x48,		/* GPIO3=1, GPIO1=0 */
	TDA10046_GP11   = 0x4a,		/* GPIO3=1, GPIO1=1 */
	TDA10046_GP00_I = 0x80,		/* GPIO3=0, GPIO1=0, invert in sleep mode*/
	TDA10046_GP01_I = 0x82,		/* GPIO3=0, GPIO1=1, invert in sleep mode */
	TDA10046_GP10_I = 0x88,		/* GPIO3=1, GPIO1=0, invert in sleep mode */
	TDA10046_GP11_I = 0x8a,		/* GPIO3=1, GPIO1=1, invert in sleep mode */
पूर्ण;

क्रमागत tda10046_अगर अणु
	TDA10046_FREQ_3617,		/* original config, 36,166 MHZ */
	TDA10046_FREQ_3613,		/* 36,13 MHZ */
	TDA10046_FREQ_045,		/* low IF, 4.0, 4.5, or 5.0 MHZ */
	TDA10046_FREQ_052,		/* low IF, 5.1667 MHZ क्रम tda9889 */
पूर्ण;

क्रमागत tda10046_tsout अणु
	TDA10046_TS_PARALLEL  = 0x00,	/* parallel transport stream, शेष */
	TDA10046_TS_SERIAL    = 0x01,	/* serial transport stream */
पूर्ण;

काष्ठा tda1004x_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* करोes the "inversion" need inverted? */
	u8 invert;

	/* Does the OCLK संकेत need inverted? */
	u8 invert_oclk;

	/* parallel or serial transport stream */
	क्रमागत tda10046_tsout ts_mode;

	/* Xtal frequency, 4 or 16MHz*/
	क्रमागत tda10046_xtal xtal_freq;

	/* IF frequency */
	क्रमागत tda10046_अगर अगर_freq;

	/* AGC configuration */
	क्रमागत tda10046_agc agc_config;

	/* setting of GPIO1 and 3 */
	क्रमागत tda10046_gpio gpio_config;

	/* slave address and configuration of the tuner */
	u8 tuner_address;
	u8 antenna_चयन;

	/* अगर the board uses another I2c Bridge (tda8290), its address */
	u8 i2c_gate;

	/* request firmware क्रम device */
	पूर्णांक (*request_firmware)(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name);
पूर्ण;

क्रमागत tda1004x_demod अणु
	TDA1004X_DEMOD_TDA10045,
	TDA1004X_DEMOD_TDA10046,
पूर्ण;

काष्ठा tda1004x_state अणु
	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा tda1004x_config* config;
	काष्ठा dvb_frontend frontend;

	/* निजी demod data */
	क्रमागत tda1004x_demod demod_type;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TDA1004X)
बाह्य काष्ठा dvb_frontend* tda10045_attach(स्थिर काष्ठा tda1004x_config* config,
					    काष्ठा i2c_adapter* i2c);

बाह्य काष्ठा dvb_frontend* tda10046_attach(स्थिर काष्ठा tda1004x_config* config,
					    काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* tda10045_attach(स्थिर काष्ठा tda1004x_config* config,
					    काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dvb_frontend* tda10046_attach(स्थिर काष्ठा tda1004x_config* config,
					    काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_TDA1004X

अटल अंतरभूत पूर्णांक tda1004x_ग_लिखोreg(काष्ठा dvb_frontend *fe, u8 reg, u8 val) अणु
	पूर्णांक r = 0;
	u8 buf[] = अणुreg, valपूर्ण;
	अगर (fe->ops.ग_लिखो)
		r = fe->ops.ग_लिखो(fe, buf, 2);
	वापस r;
पूर्ण

#पूर्ण_अगर // TDA1004X_H
