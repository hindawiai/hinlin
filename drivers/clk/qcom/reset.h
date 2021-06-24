<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __QCOM_CLK_RESET_H__
#घोषणा __QCOM_CLK_RESET_H__

#समावेश <linux/reset-controller.h>

काष्ठा qcom_reset_map अणु
	अचिन्हित पूर्णांक reg;
	u8 bit;
पूर्ण;

काष्ठा regmap;

काष्ठा qcom_reset_controller अणु
	स्थिर काष्ठा qcom_reset_map *reset_map;
	काष्ठा regmap *regmap;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

#घोषणा to_qcom_reset_controller(r) \
	container_of(r, काष्ठा qcom_reset_controller, rcdev);

बाह्य स्थिर काष्ठा reset_control_ops qcom_reset_ops;

#पूर्ण_अगर
