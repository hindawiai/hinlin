<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Platक्रमm data declarations क्रम DA9052 PMICs.
 *
 * Copyright(c) 2011 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#अगर_अघोषित __MFD_DA9052_PDATA_H__
#घोषणा __MFD_DA9052_PDATA_H__

#घोषणा DA9052_MAX_REGULATORS	14

काष्ठा da9052;

काष्ठा da9052_pdata अणु
	काष्ठा led_platक्रमm_data *pled;
	पूर्णांक (*init) (काष्ठा da9052 *da9052);
	पूर्णांक irq_base;
	पूर्णांक gpio_base;
	पूर्णांक use_क्रम_apm;
	काष्ठा regulator_init_data *regulators[DA9052_MAX_REGULATORS];
पूर्ण;

#पूर्ण_अगर
