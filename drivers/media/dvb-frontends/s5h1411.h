<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Samsung S5H1411 VSB/QAM demodulator driver

    Copyright (C) 2008 Steven Toth <stoth@linuxtv.org>


*/

#अगर_अघोषित __S5H1411_H__
#घोषणा __S5H1411_H__

#समावेश <linux/dvb/frontend.h>

#घोषणा S5H1411_I2C_TOP_ADDR (0x32 >> 1)
#घोषणा S5H1411_I2C_QAM_ADDR (0x34 >> 1)

काष्ठा s5h1411_config अणु

	/* serial/parallel output */
#घोषणा S5H1411_PARALLEL_OUTPUT 0
#घोषणा S5H1411_SERIAL_OUTPUT   1
	u8 output_mode;

	/* GPIO Setting */
#घोषणा S5H1411_GPIO_OFF 0
#घोषणा S5H1411_GPIO_ON  1
	u8 gpio;

	/* MPEG संकेत timing */
#घोषणा S5H1411_MPEGTIMING_CONTINUOUS_INVERTING_CLOCK       0
#घोषणा S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK    1
#घोषणा S5H1411_MPEGTIMING_NONCONTINUOUS_INVERTING_CLOCK    2
#घोषणा S5H1411_MPEGTIMING_NONCONTINUOUS_NONINVERTING_CLOCK 3
	u16 mpeg_timing;

	/* IF Freq क्रम QAM and VSB in KHz */
#घोषणा S5H1411_IF_3250  3250
#घोषणा S5H1411_IF_3500  3500
#घोषणा S5H1411_IF_4000  4000
#घोषणा S5H1411_IF_5380  5380
#घोषणा S5H1411_IF_44000 44000
#घोषणा S5H1411_VSB_IF_DEFAULT S5H1411_IF_44000
#घोषणा S5H1411_QAM_IF_DEFAULT S5H1411_IF_44000
	u16 qam_अगर;
	u16 vsb_अगर;

	/* Spectral Inversion */
#घोषणा S5H1411_INVERSION_OFF 0
#घोषणा S5H1411_INVERSION_ON  1
	u8 inversion;

	/* Return lock status based on tuner lock, or demod lock */
#घोषणा S5H1411_TUNERLOCKING 0
#घोषणा S5H1411_DEMODLOCKING 1
	u8 status_mode;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_S5H1411)
बाह्य काष्ठा dvb_frontend *s5h1411_attach(स्थिर काष्ठा s5h1411_config *config,
					   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *s5h1411_attach(
	स्थिर काष्ठा s5h1411_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_S5H1411 */

#पूर्ण_अगर /* __S5H1411_H__ */
