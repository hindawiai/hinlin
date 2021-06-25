<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Driver क्रम M88RS2000 demodulator


*/

#अगर_अघोषित M88RS2000_H
#घोषणा M88RS2000_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

काष्ठा m88rs2000_config अणु
	/* Demodulator i2c address */
	u8 demod_addr;

	u8 *inittab;

	/* minimum delay beक्रमe retuning */
	पूर्णांक min_delay_ms;

	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend *, पूर्णांक);
पूर्ण;

क्रमागत अणु
	CALL_IS_SET_FRONTEND = 0x0,
	CALL_IS_READ,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_M88RS2000)
बाह्य काष्ठा dvb_frontend *m88rs2000_attach(
	स्थिर काष्ठा m88rs2000_config *config, काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *m88rs2000_attach(
	स्थिर काष्ठा m88rs2000_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_M88RS2000 */

#घोषणा RS2000_FE_CRYSTAL_KHZ 27000

क्रमागत अणु
	DEMOD_WRITE = 0x1,
	WRITE_DELAY = 0x10,
पूर्ण;
#पूर्ण_अगर /* M88RS2000_H */
