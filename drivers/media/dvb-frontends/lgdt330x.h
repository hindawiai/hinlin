<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम LGDT3302 and LGDT3303 - VSB/QAM
 *
 *    Copyright (C) 2005 Wilson Michaels <wilsonmichaels@earthlink.net>
 */

#अगर_अघोषित LGDT330X_H
#घोषणा LGDT330X_H

#समावेश <linux/dvb/frontend.h>

प्रकार क्रमागत lg_chip_t अणु
		UNDEFINED,
		LGDT3302,
		LGDT3303
पूर्णlg_chip_type;

/**
 * काष्ठा lgdt330x_config - contains lgdt330x configuration
 *
 * @demod_chip:		LG demodulator chip LGDT3302 or LGDT3303
 * @serial_mpeg:	MPEG hardware पूर्णांकerface - 0:parallel 1:serial
 * @pll_rf_set:		Callback function to set PLL पूर्णांकerface
 * @set_ts_params:	Callback function to set device param क्रम start_dma
 * @घड़ी_polarity_flip:
 *	Flip the polarity of the mpeg data transfer घड़ी using alternate
 *	init data.
 *	This option applies ONLY to LGDT3303 - 0:disabled (शेष) 1:enabled
 * @get_dvb_frontend:
 *	वापसs the frontend associated with this I2C client.
 *	Filled by the driver.
 */
काष्ठा lgdt330x_config
अणु
	lg_chip_type demod_chip;
	पूर्णांक serial_mpeg;
	पूर्णांक (*pll_rf_set) (काष्ठा dvb_frontend* fe, पूर्णांक index);
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend* fe, पूर्णांक is_punctured);
	पूर्णांक घड़ी_polarity_flip;

	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LGDT330X)
काष्ठा dvb_frontend *lgdt330x_attach(स्थिर काष्ठा lgdt330x_config *config,
				     u8 demod_address,
				     काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *lgdt330x_attach(स्थिर काष्ठा lgdt330x_config *config,
				     u8 demod_address,
				     काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_LGDT330X

#पूर्ण_अगर /* LGDT330X_H */
