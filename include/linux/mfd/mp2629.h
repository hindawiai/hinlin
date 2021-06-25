<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2020 Monolithic Power Systems, Inc
 */

#अगर_अघोषित __MP2629_H__
#घोषणा __MP2629_H__

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

काष्ठा mp2629_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

क्रमागत mp2629_adc_chan अणु
	MP2629_BATT_VOLT,
	MP2629_SYSTEM_VOLT,
	MP2629_INPUT_VOLT,
	MP2629_BATT_CURRENT,
	MP2629_INPUT_CURRENT,
	MP2629_ADC_CHAN_END
पूर्ण;

#पूर्ण_अगर
