<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * fixed.h
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * Copyright (c) 2009 Nokia Corporation
 * Roger Quadros <ext-roger.quadros@nokia.com>
 */

#अगर_अघोषित __REGULATOR_FIXED_H
#घोषणा __REGULATOR_FIXED_H

काष्ठा regulator_init_data;

/**
 * काष्ठा fixed_voltage_config - fixed_voltage_config काष्ठाure
 * @supply_name:	Name of the regulator supply
 * @input_supply:	Name of the input regulator supply
 * @microvolts:		Output voltage of regulator
 * @startup_delay:	Start-up समय in microseconds
 * @enabled_at_boot:	Whether regulator has been enabled at
 * 			boot or not. 1 = Yes, 0 = No
 * 			This is used to keep the regulator at
 * 			the शेष state
 * @init_data:		regulator_init_data
 *
 * This काष्ठाure contains fixed voltage regulator configuration
 * inक्रमmation that must be passed by platक्रमm code to the fixed
 * voltage regulator driver.
 */
काष्ठा fixed_voltage_config अणु
	स्थिर अक्षर *supply_name;
	स्थिर अक्षर *input_supply;
	पूर्णांक microvolts;
	अचिन्हित startup_delay;
	अचिन्हित पूर्णांक off_on_delay;
	अचिन्हित enabled_at_boot:1;
	काष्ठा regulator_init_data *init_data;
पूर्ण;

काष्ठा regulator_consumer_supply;

#अगर IS_ENABLED(CONFIG_REGULATOR)
काष्ठा platक्रमm_device *regulator_रेजिस्टर_always_on(पूर्णांक id, स्थिर अक्षर *name,
		काष्ठा regulator_consumer_supply *supplies, पूर्णांक num_supplies, पूर्णांक uv);
#अन्यथा
अटल अंतरभूत काष्ठा platक्रमm_device *regulator_रेजिस्टर_always_on(पूर्णांक id, स्थिर अक्षर *name,
		काष्ठा regulator_consumer_supply *supplies, पूर्णांक num_supplies, पूर्णांक uv)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#घोषणा regulator_रेजिस्टर_fixed(id, s, ns) regulator_रेजिस्टर_always_on(id, \
						"fixed-dummy", s, ns, 0)

#पूर्ण_अगर
