<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    TDA10021/TDA10023  - Single Chip Cable Channel Receiver driver module
			 used on the the Siemens DVB-C cards

    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>
    Copyright (C) 2004 Markus Schulz <msc@antzप्रणाली.de>
		   Support क्रम TDA10021

*/

#अगर_अघोषित TDA1002x_H
#घोषणा TDA1002x_H

#समावेश <linux/dvb/frontend.h>

काष्ठा tda1002x_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;
	u8 invert;
पूर्ण;

क्रमागत tda10023_output_mode अणु
	TDA10023_OUTPUT_MODE_PARALLEL_A = 0xe0,
	TDA10023_OUTPUT_MODE_PARALLEL_B = 0xa1,
	TDA10023_OUTPUT_MODE_PARALLEL_C = 0xa0,
	TDA10023_OUTPUT_MODE_SERIAL, /* TODO: not implemented */
पूर्ण;

काष्ठा tda10023_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;
	u8 invert;

	/* घड़ी settings */
	u32 xtal; /* शेषs: 28920000 */
	u8 pll_m; /* शेषs: 8 */
	u8 pll_p; /* शेषs: 4 */
	u8 pll_n; /* शेषs: 1 */

	/* MPEG2 TS output mode */
	u8 output_mode;

	/* input freq offset + baseband conversion type */
	u16 deltaf;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TDA10021)
बाह्य काष्ठा dvb_frontend* tda10021_attach(स्थिर काष्ठा tda1002x_config* config,
					    काष्ठा i2c_adapter* i2c, u8 pwm);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* tda10021_attach(स्थिर काष्ठा tda1002x_config* config,
					    काष्ठा i2c_adapter* i2c, u8 pwm)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_TDA10021

#अगर IS_REACHABLE(CONFIG_DVB_TDA10023)
बाह्य काष्ठा dvb_frontend *tda10023_attach(
	स्थिर काष्ठा tda10023_config *config,
	काष्ठा i2c_adapter *i2c, u8 pwm);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *tda10023_attach(
	स्थिर काष्ठा tda10023_config *config,
	काष्ठा i2c_adapter *i2c, u8 pwm)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_TDA10023

#पूर्ण_अगर // TDA1002x_H
