<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *	   Zhiyong Tao <zhiyong.tao@mediatek.com>
 *	   Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */
#अगर_अघोषित __PINCTRL_PARIS_H
#घोषणा __PINCTRL_PARIS_H

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
#समावेश "../pinctrl-utils.h"
#समावेश "../pinmux.h"
#समावेश "mtk-eint.h"
#समावेश "pinctrl-mtk-common-v2.h"

#घोषणा MTK_RANGE(_a)		अणु .range = (_a), .nranges = ARRAY_SIZE(_a), पूर्ण

#घोषणा MTK_EINT_FUNCTION(_eपूर्णांकmux, _eपूर्णांकnum)				\
	अणु							\
		.eपूर्णांक_m = _eपूर्णांकmux,					\
		.eपूर्णांक_n = _eपूर्णांकnum,					\
	पूर्ण

#घोषणा MTK_FUNCTION(_val, _name)				\
	अणु							\
		.muxval = _val,					\
		.name = _name,					\
	पूर्ण

#घोषणा MTK_PIN(_number, _name, _eपूर्णांक, _drv_n, ...) अणु	\
		.number = _number,			\
		.name = _name,				\
		.eपूर्णांक = _eपूर्णांक,				\
		.drv_n = _drv_n,			\
		.funcs = (काष्ठा mtk_func_desc[])अणु	\
			__VA_ARGS__, अणु पूर्ण पूर्ण,				\
	पूर्ण

#घोषणा PINCTRL_PIN_GROUP(name, id)			\
	अणु						\
		name,					\
		id##_pins,				\
		ARRAY_SIZE(id##_pins),			\
		id##_funcs,				\
	पूर्ण

पूर्णांक mtk_paris_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			    स्थिर काष्ठा mtk_pin_soc *soc);

sमाप_प्रकार mtk_pctrl_show_one_pin(काष्ठा mtk_pinctrl *hw,
	अचिन्हित पूर्णांक gpio, अक्षर *buf, अचिन्हित पूर्णांक bufLen);

बाह्य स्थिर काष्ठा dev_pm_ops mtk_paris_pinctrl_pm_ops;

#पूर्ण_अगर /* __PINCTRL_PARIS_H */
