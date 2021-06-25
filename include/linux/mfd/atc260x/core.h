<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Core MFD defines क्रम ATC260x PMICs
 *
 * Copyright (C) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 * Copyright (C) 2020 Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#अगर_अघोषित __LINUX_MFD_ATC260X_CORE_H
#घोषणा __LINUX_MFD_ATC260X_CORE_H

#समावेश <linux/mfd/atc260x/atc2603c.h>
#समावेश <linux/mfd/atc260x/atc2609a.h>

क्रमागत atc260x_type अणु
	ATC2603A = 0,
	ATC2603C,
	ATC2609A,
पूर्ण;

क्रमागत atc260x_ver अणु
	ATC260X_A = 0,
	ATC260X_B,
	ATC260X_C,
	ATC260X_D,
	ATC260X_E,
	ATC260X_F,
	ATC260X_G,
	ATC260X_H,
पूर्ण;

काष्ठा atc260x अणु
	काष्ठा device *dev;

	काष्ठा regmap *regmap;
	स्थिर काष्ठा regmap_irq_chip *regmap_irq_chip;
	काष्ठा regmap_irq_chip_data *irq_data;

	काष्ठा mutex *regmap_mutex;	/* mutex क्रम custom regmap locking */

	स्थिर काष्ठा mfd_cell *cells;
	पूर्णांक nr_cells;
	पूर्णांक irq;

	क्रमागत atc260x_type ic_type;
	क्रमागत atc260x_ver ic_ver;
	स्थिर अक्षर *type_name;
	अचिन्हित पूर्णांक rev_reg;

	स्थिर काष्ठा atc260x_init_regs *init_regs; /* regs क्रम device init */
पूर्ण;

काष्ठा regmap_config;

पूर्णांक atc260x_match_device(काष्ठा atc260x *atc260x, काष्ठा regmap_config *regmap_cfg);
पूर्णांक atc260x_device_probe(काष्ठा atc260x *atc260x);

#पूर्ण_अगर /* __LINUX_MFD_ATC260X_CORE_H */
