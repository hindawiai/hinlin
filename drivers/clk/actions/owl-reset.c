<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Actions Semi Owl SoCs Reset Management Unit driver
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश "owl-reset.h"

अटल पूर्णांक owl_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id)
अणु
	काष्ठा owl_reset *reset = to_owl_reset(rcdev);
	स्थिर काष्ठा owl_reset_map *map = &reset->reset_map[id];

	वापस regmap_update_bits(reset->regmap, map->reg, map->bit, 0);
पूर्ण

अटल पूर्णांक owl_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा owl_reset *reset = to_owl_reset(rcdev);
	स्थिर काष्ठा owl_reset_map *map = &reset->reset_map[id];

	वापस regmap_update_bits(reset->regmap, map->reg, map->bit, map->bit);
पूर्ण

अटल पूर्णांक owl_reset_reset(काष्ठा reset_controller_dev *rcdev,
			   अचिन्हित दीर्घ id)
अणु
	owl_reset_निश्चित(rcdev, id);
	udelay(1);
	owl_reset_deनिश्चित(rcdev, id);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_reset_status(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id)
अणु
	काष्ठा owl_reset *reset = to_owl_reset(rcdev);
	स्थिर काष्ठा owl_reset_map *map = &reset->reset_map[id];
	u32 reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(reset->regmap, map->reg, &reg);
	अगर (ret)
		वापस ret;

	/*
	 * The reset control API expects 0 अगर reset is not निश्चितed,
	 * which is the opposite of what our hardware uses.
	 */
	वापस !(map->bit & reg);
पूर्ण

स्थिर काष्ठा reset_control_ops owl_reset_ops = अणु
	.निश्चित		= owl_reset_निश्चित,
	.deनिश्चित	= owl_reset_deनिश्चित,
	.reset		= owl_reset_reset,
	.status		= owl_reset_status,
पूर्ण;
