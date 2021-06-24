<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/delay.h>

#समावेश "reset.h"

अटल पूर्णांक qcom_reset(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	rcdev->ops->निश्चित(rcdev, id);
	udelay(1);
	rcdev->ops->deनिश्चित(rcdev, id);
	वापस 0;
पूर्ण

अटल पूर्णांक
qcom_reset_निश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	काष्ठा qcom_reset_controller *rst;
	स्थिर काष्ठा qcom_reset_map *map;
	u32 mask;

	rst = to_qcom_reset_controller(rcdev);
	map = &rst->reset_map[id];
	mask = BIT(map->bit);

	वापस regmap_update_bits(rst->regmap, map->reg, mask, mask);
पूर्ण

अटल पूर्णांक
qcom_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	काष्ठा qcom_reset_controller *rst;
	स्थिर काष्ठा qcom_reset_map *map;
	u32 mask;

	rst = to_qcom_reset_controller(rcdev);
	map = &rst->reset_map[id];
	mask = BIT(map->bit);

	वापस regmap_update_bits(rst->regmap, map->reg, mask, 0);
पूर्ण

स्थिर काष्ठा reset_control_ops qcom_reset_ops = अणु
	.reset = qcom_reset,
	.निश्चित = qcom_reset_निश्चित,
	.deनिश्चित = qcom_reset_deनिश्चित,
पूर्ण;
EXPORT_SYMBOL_GPL(qcom_reset_ops);
