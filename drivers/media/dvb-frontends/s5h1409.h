<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Samsung S5H1409 VSB/QAM demodulator driver

    Copyright (C) 2006 Steven Toth <stoth@linuxtv.org>


*/

#अगर_अघोषित __S5H1409_H__
#घोषणा __S5H1409_H__

#समावेश <linux/dvb/frontend.h>

काष्ठा s5h1409_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* serial/parallel output */
#घोषणा S5H1409_PARALLEL_OUTPUT 0
#घोषणा S5H1409_SERIAL_OUTPUT   1
	u8 output_mode;

	/* GPIO Setting */
#घोषणा S5H1409_GPIO_OFF 0
#घोषणा S5H1409_GPIO_ON  1
	u8 gpio;

	/* IF Freq क्रम QAM in KHz, VSB is hardcoded to 5380 */
	u16 qam_अगर;

	/* Spectral Inversion */
#घोषणा S5H1409_INVERSION_OFF 0
#घोषणा S5H1409_INVERSION_ON  1
	u8 inversion;

	/* Return lock status based on tuner lock, or demod lock */
#घोषणा S5H1409_TUNERLOCKING 0
#घोषणा S5H1409_DEMODLOCKING 1
	u8 status_mode;

	/* MPEG संकेत timing */
#घोषणा S5H1409_MPEGTIMING_CONTINUOUS_INVERTING_CLOCK       0
#घोषणा S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK    1
#घोषणा S5H1409_MPEGTIMING_NONCONTINUOUS_INVERTING_CLOCK    2
#घोषणा S5H1409_MPEGTIMING_NONCONTINUOUS_NONINVERTING_CLOCK 3
	u16 mpeg_timing;

	/* HVR-1600 optimizations (to better work with MXL5005s)
	   Note: some of these are likely to be folded पूर्णांकo the generic driver
	   after being regression tested with other boards */
#घोषणा S5H1409_HVR1600_NOOPTIMIZE 0
#घोषणा S5H1409_HVR1600_OPTIMIZE   1
	u8 hvr1600_opt;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_S5H1409)
बाह्य काष्ठा dvb_frontend *s5h1409_attach(स्थिर काष्ठा s5h1409_config *config,
					   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *s5h1409_attach(
	स्थिर काष्ठा s5h1409_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_S5H1409 */

#पूर्ण_अगर /* __S5H1409_H__ */
