<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Zarlink DVB-T ZL10353 demodulator
 *
 *  Copyright (C) 2006, 2007 Christopher Pascoe <c.pascoe@itee.uq.edu.au>
 */

#अगर_अघोषित ZL10353_H
#घोषणा ZL10353_H

#समावेश <linux/dvb/frontend.h>

काष्ठा zl10353_config
अणु
	/* demodulator's I2C address */
	u8 demod_address;

	/* frequencies in units of 0.1kHz */
	पूर्णांक adc_घड़ी;	/* शेष: 450560 (45.056  MHz) */
	पूर्णांक अगर2;	/* शेष: 361667 (36.1667 MHz) */

	/* set अगर no pll is connected to the secondary i2c bus */
	पूर्णांक no_tuner;

	/* set अगर parallel ts output is required */
	पूर्णांक parallel_ts;

	/* set अगर i2c_gate_ctrl disable is required */
	u8 disable_i2c_gate_ctrl:1;

	/* घड़ी control रेजिस्टरs (0x51-0x54) */
	u8 घड़ी_ctl_1;  /* शेष: 0x46 */
	u8 pll_0;        /* शेष: 0x15 */
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_ZL10353)
बाह्य काष्ठा dvb_frontend* zl10353_attach(स्थिर काष्ठा zl10353_config *config,
					   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* zl10353_attach(स्थिर काष्ठा zl10353_config *config,
					   काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_ZL10353 */

#पूर्ण_अगर /* ZL10353_H */
