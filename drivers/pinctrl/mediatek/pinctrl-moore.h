<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017-2018 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */
#अगर_अघोषित __PINCTRL_MOORE_H
#घोषणा __PINCTRL_MOORE_H

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "../pinmux.h"
#समावेश "mtk-eint.h"
#समावेश "pinctrl-mtk-common-v2.h"

#घोषणा MTK_RANGE(_a)		अणु .range = (_a), .nranges = ARRAY_SIZE(_a), पूर्ण

#घोषणा MTK_PIN(_number, _name, _eपूर्णांक_m, _eपूर्णांक_n, _drv_n) अणु	\
		.number = _number,			\
		.name = _name,				\
		.eपूर्णांक = अणु				\
			.eपूर्णांक_m = _eपूर्णांक_m,		\
			.eपूर्णांक_n = _eपूर्णांक_n,		\
		पूर्ण,					\
		.drv_n = _drv_n,			\
		.funcs = शून्य,				\
	पूर्ण

#घोषणा PINCTRL_PIN_GROUP(name, id)			\
	अणु						\
		name,					\
		id##_pins,				\
		ARRAY_SIZE(id##_pins),			\
		id##_funcs,				\
	पूर्ण

पूर्णांक mtk_moore_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			    स्थिर काष्ठा mtk_pin_soc *soc);

#पूर्ण_अगर /* __PINCTRL_MOORE_H */
