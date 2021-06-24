<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * tps62360.h -- TI tps62360
 *
 * Interface क्रम regulator driver क्रम TI TPS62360 Processor core supply
 *
 * Copyright (C) 2012 NVIDIA Corporation

 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#अगर_अघोषित __LINUX_REGULATOR_TPS62360_H
#घोषणा __LINUX_REGULATOR_TPS62360_H

/*
 * काष्ठा tps62360_regulator_platक्रमm_data - tps62360 regulator platक्रमm data.
 *
 * @reg_init_data: The regulator init data.
 * @en_disअक्षरge: Enable disअक्षरge the output capacitor via पूर्णांकernal
 *                रेजिस्टर.
 * @en_पूर्णांकernal_pulldn: पूर्णांकernal pull करोwn enable or not.
 * @vsel0_gpio: Gpio number क्रम vsel0. It should be -1 अगर this is tied with
 *              fixed logic.
 * @vsel1_gpio: Gpio number क्रम vsel1. It should be -1 अगर this is tied with
 *              fixed logic.
 * @vsel0_def_state: Default state of vsel0. 1 अगर it is high अन्यथा 0.
 * @vsel1_def_state: Default state of vsel1. 1 अगर it is high अन्यथा 0.
 */
काष्ठा tps62360_regulator_platक्रमm_data अणु
	काष्ठा regulator_init_data *reg_init_data;
	bool en_disअक्षरge;
	bool en_पूर्णांकernal_pulldn;
	पूर्णांक vsel0_gpio;
	पूर्णांक vsel1_gpio;
	पूर्णांक vsel0_def_state;
	पूर्णांक vsel1_def_state;
पूर्ण;

#पूर्ण_अगर /* __LINUX_REGULATOR_TPS62360_H */
