<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012, Anish Kumar <anish198519851985@gmail.com>
 */

#अगर_अघोषित GENERIC_ADC_BATTERY_H
#घोषणा GENERIC_ADC_BATTERY_H

/**
 * काष्ठा gab_platक्रमm_data - platक्रमm_data क्रम generic adc iio battery driver.
 * @battery_info:         recommended काष्ठाure to specअगरy अटल घातer supply
 *			   parameters
 * @cal_अक्षरge:           calculate अक्षरge level.
 * @jitter_delay:         delay required after the पूर्णांकerrupt to check battery
 *			  status.Default set is 10ms.
 */
काष्ठा gab_platक्रमm_data अणु
	काष्ठा घातer_supply_info battery_info;
	पूर्णांक	(*cal_अक्षरge)(दीर्घ value);
	पूर्णांक     jitter_delay;
पूर्ण;

#पूर्ण_अगर /* GENERIC_ADC_BATTERY_H */
