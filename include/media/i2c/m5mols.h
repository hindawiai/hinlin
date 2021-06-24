<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver header क्रम M-5MOLS 8M Pixel camera sensor with ISP
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 *
 * Copyright (C) 2009 Samsung Electronics Co., Ltd.
 * Author: Dongsoo Nathaniel Kim <करोngsoo45.kim@samsung.com>
 */

#अगर_अघोषित MEDIA_M5MOLS_H
#घोषणा MEDIA_M5MOLS_H

/**
 * काष्ठा m5mols_platक्रमm_data - platक्रमm data क्रम M-5MOLS driver
 * @gpio_reset:	GPIO driving the reset pin of M-5MOLS
 * @reset_polarity: active state क्रम gpio_reset pin, 0 or 1
 * @set_घातer:	an additional callback to the board setup code
 *		to be called after enabling and beक्रमe disabling
 *		the sensor's supply regulators
 */
काष्ठा m5mols_platक्रमm_data अणु
	पूर्णांक gpio_reset;
	u8 reset_polarity;
	पूर्णांक (*set_घातer)(काष्ठा device *dev, पूर्णांक on);
पूर्ण;

#पूर्ण_अगर	/* MEDIA_M5MOLS_H */
