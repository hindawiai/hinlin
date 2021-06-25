<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * PM2301 अक्षरger driver.
 *
 * Copyright (C) 2012 ST Ericsson Corporation
 *
 * Contact: Olivier LAUNAY (olivier.launay@stericsson.com
 */

#अगर_अघोषित __LINUX_PM2301_H
#घोषणा __LINUX_PM2301_H

/**
 * काष्ठा pm2xxx_bm_अक्षरger_parameters - Charger specअगरic parameters
 * @ac_volt_max:	maximum allowed AC अक्षरger voltage in mV
 * @ac_curr_max:	maximum allowed AC अक्षरger current in mA
 */
काष्ठा pm2xxx_bm_अक्षरger_parameters अणु
	पूर्णांक ac_volt_max;
	पूर्णांक ac_curr_max;
पूर्ण;

/**
 * काष्ठा pm2xxx_bm_data - pm2xxx battery management data
 * @enable_overshoot    flag to enable VBAT overshoot control
 * @chg_params	  अक्षरger parameters
 */
काष्ठा pm2xxx_bm_data अणु
	bool enable_overshoot;
	स्थिर काष्ठा pm2xxx_bm_अक्षरger_parameters *chg_params;
पूर्ण;

काष्ठा pm2xxx_अक्षरger_platक्रमm_data अणु
	अक्षर **supplied_to;
	माप_प्रकार num_supplicants;
	पूर्णांक i2c_bus;
	स्थिर अक्षर *label;
	पूर्णांक gpio_irq_number;
	अचिन्हित पूर्णांक lpn_gpio;
	पूर्णांक irq_type;
पूर्ण;

काष्ठा pm2xxx_platक्रमm_data अणु
	काष्ठा pm2xxx_अक्षरger_platक्रमm_data *wall_अक्षरger;
	काष्ठा pm2xxx_bm_data *battery;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PM2301_H */
