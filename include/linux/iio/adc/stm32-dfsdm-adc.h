<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file discribe the STM32 DFSDM IIO driver API क्रम audio part
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Arnaud Pouliquen <arnaud.pouliquen@st.com>.
 */

#अगर_अघोषित STM32_DFSDM_ADC_H
#घोषणा STM32_DFSDM_ADC_H

#समावेश <linux/iio/iपन.स>

पूर्णांक sपंचांग32_dfsdm_get_buff_cb(काष्ठा iio_dev *iio_dev,
			    पूर्णांक (*cb)(स्थिर व्योम *data, माप_प्रकार size,
				      व्योम *निजी),
			    व्योम *निजी);
पूर्णांक sपंचांग32_dfsdm_release_buff_cb(काष्ठा iio_dev *iio_dev);

#पूर्ण_अगर
