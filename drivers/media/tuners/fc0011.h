<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_FC0011_H_
#घोषणा LINUX_FC0011_H_

#समावेश <media/dvb_frontend.h>


/** काष्ठा fc0011_config - fc0011 hardware config
 *
 * @i2c_address: I2C bus address.
 */
काष्ठा fc0011_config अणु
	u8 i2c_address;
पूर्ण;

/** क्रमागत fc0011_fe_callback_commands - Frontend callbacks
 *
 * @FC0011_FE_CALLBACK_POWER: Power on tuner hardware.
 * @FC0011_FE_CALLBACK_RESET: Request a tuner reset.
 */
क्रमागत fc0011_fe_callback_commands अणु
	FC0011_FE_CALLBACK_POWER,
	FC0011_FE_CALLBACK_RESET,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_FC0011)
काष्ठा dvb_frontend *fc0011_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा i2c_adapter *i2c,
				   स्थिर काष्ठा fc0011_config *config);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *fc0011_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा i2c_adapter *i2c,
				   स्थिर काष्ठा fc0011_config *config)
अणु
	dev_err(&i2c->dev, "fc0011 driver disabled in Kconfig\n");
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* LINUX_FC0011_H_ */
