<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 2010, Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __LINUX_POWER_GPIO_CHARGER_H__
#घोषणा __LINUX_POWER_GPIO_CHARGER_H__

#समावेश <linux/घातer_supply.h>
#समावेश <linux/types.h>

/**
 * काष्ठा gpio_अक्षरger_platक्रमm_data - platक्रमm_data क्रम gpio_अक्षरger devices
 * @name:		Name क्रम the अक्षरgers घातer_supply device
 * @type:		Type of the अक्षरger
 * @supplied_to:	Array of battery names to which this अक्षरgers supplies घातer
 * @num_supplicants:	Number of entries in the supplied_to array
 */
काष्ठा gpio_अक्षरger_platक्रमm_data अणु
	स्थिर अक्षर *name;
	क्रमागत घातer_supply_type type;
	अक्षर **supplied_to;
	माप_प्रकार num_supplicants;
पूर्ण;

#पूर्ण_अगर
