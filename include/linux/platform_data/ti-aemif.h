<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI DaVinci AEMIF platक्रमm glue.
 *
 * Copyright (C) 2017 BayLibre SAS
 *
 * Author:
 *   Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#अगर_अघोषित __TI_DAVINCI_AEMIF_DATA_H__
#घोषणा __TI_DAVINCI_AEMIF_DATA_H__

#समावेश <linux/of_platक्रमm.h>

/**
 * काष्ठा aemअगर_abus_data - Async bus configuration parameters.
 *
 * @cs - Chip-select number.
 */
काष्ठा aemअगर_abus_data अणु
	u32 cs;
पूर्ण;

/**
 * काष्ठा aemअगर_platक्रमm_data - Data to set up the TI aemअगर driver.
 *
 * @dev_lookup: of_dev_auxdata passed to of_platक्रमm_populate() क्रम aemअगर
 *              subdevices.
 * @cs_offset: Lowest allowed chip-select number.
 * @abus_data: Array of async bus configuration entries.
 * @num_abus_data: Number of abus entries.
 * @sub_devices: Array of platक्रमm subdevices.
 * @num_sub_devices: Number of subdevices.
 */
काष्ठा aemअगर_platक्रमm_data अणु
	काष्ठा of_dev_auxdata *dev_lookup;
	u32 cs_offset;
	काष्ठा aemअगर_abus_data *abus_data;
	माप_प्रकार num_abus_data;
	काष्ठा platक्रमm_device *sub_devices;
	माप_प्रकार num_sub_devices;
पूर्ण;

#पूर्ण_अगर /* __TI_DAVINCI_AEMIF_DATA_H__ */
