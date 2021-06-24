<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ntc_thermistor.h - NTC Thermistors
 *
 *  Copyright (C) 2010 Samsung Electronics
 *  MyungJoo Ham <myungjoo.ham@samsung.com>
 */
#अगर_अघोषित _LINUX_NTC_H
#घोषणा _LINUX_NTC_H

काष्ठा iio_channel;

क्रमागत ntc_thermistor_type अणु
	TYPE_B57330V2103,
	TYPE_B57891S0103,
	TYPE_NCPXXWB473,
	TYPE_NCPXXWF104,
	TYPE_NCPXXWL333,
	TYPE_NCPXXXH103,
पूर्ण;

काष्ठा ntc_thermistor_platक्रमm_data अणु
	/*
	 * One (not both) of पढ़ो_uV and पढ़ो_ohm should be provided and only
	 * one of the two should be provided.
	 * Both functions should वापस negative value क्रम an error हाल.
	 *
	 * pullup_uV, pullup_ohm, pullकरोwn_ohm, and connect are required to use
	 * पढ़ो_uV()
	 *
	 * How to setup pullup_ohm, pullकरोwn_ohm, and connect is
	 * described at Documentation/hwmon/ntc_thermistor.rst
	 *
	 * pullup/करोwn_ohm: 0 क्रम infinite / not-connected
	 *
	 * chan: iio_channel poपूर्णांकer to communicate with the ADC which the
	 * thermistor is using क्रम conversion of the analog values.
	 */
	पूर्णांक (*पढ़ो_uv)(काष्ठा ntc_thermistor_platक्रमm_data *);
	अचिन्हित पूर्णांक pullup_uv;

	अचिन्हित पूर्णांक pullup_ohm;
	अचिन्हित पूर्णांक pullकरोwn_ohm;
	क्रमागत अणु NTC_CONNECTED_POSITIVE, NTC_CONNECTED_GROUND पूर्ण connect;
	काष्ठा iio_channel *chan;

	पूर्णांक (*पढ़ो_ohm)(व्योम);
पूर्ण;

#पूर्ण_अगर /* _LINUX_NTC_H */
