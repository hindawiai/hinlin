<शैली गुरु>
/*
 * Platक्रमm data क्रम MAX9768
 * Copyright (C) 2011, 2012 by Wolfram Sang, Pengutronix e.K.
 * same licence as the driver
 */

#अगर_अघोषित __SOUND_MAX9768_PDATA_H__
#घोषणा __SOUND_MAX9768_PDATA_H__

/**
 * काष्ठा max9768_pdata - optional platक्रमm specअगरic MAX9768 configuration
 * @shdn_gpio:	GPIO to SHDN pin. If not valid, pin must be hardwired HIGH
 * @mute_gpio:	GPIO to MUTE pin. If not valid, control क्रम mute won't be added
 * @flags: configuration flags, e.g. set classic PWM mode (check datasheet
 *         regarding "filterless modulation" which is शेष).
 */
काष्ठा max9768_pdata अणु
	पूर्णांक shdn_gpio;
	पूर्णांक mute_gpio;
	अचिन्हित flags;
#घोषणा MAX9768_FLAG_CLASSIC_PWM	(1 << 0)
पूर्ण;

#पूर्ण_अगर /* __SOUND_MAX9768_PDATA_H__*/
