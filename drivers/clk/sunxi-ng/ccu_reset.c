<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/reset-controller.h>

#समावेश "ccu_reset.h"

अटल पूर्णांक ccu_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id)
अणु
	काष्ठा ccu_reset *ccu = rcdev_to_ccu_reset(rcdev);
	स्थिर काष्ठा ccu_reset_map *map = &ccu->reset_map[id];
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(ccu->lock, flags);

	reg = पढ़ोl(ccu->base + map->reg);
	ग_लिखोl(reg & ~map->bit, ccu->base + map->reg);

	spin_unlock_irqrestore(ccu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ccu_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा ccu_reset *ccu = rcdev_to_ccu_reset(rcdev);
	स्थिर काष्ठा ccu_reset_map *map = &ccu->reset_map[id];
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(ccu->lock, flags);

	reg = पढ़ोl(ccu->base + map->reg);
	ग_लिखोl(reg | map->bit, ccu->base + map->reg);

	spin_unlock_irqrestore(ccu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ccu_reset_reset(काष्ठा reset_controller_dev *rcdev,
			   अचिन्हित दीर्घ id)
अणु
	ccu_reset_निश्चित(rcdev, id);
	udelay(10);
	ccu_reset_deनिश्चित(rcdev, id);

	वापस 0;
पूर्ण

अटल पूर्णांक ccu_reset_status(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id)
अणु
	काष्ठा ccu_reset *ccu = rcdev_to_ccu_reset(rcdev);
	स्थिर काष्ठा ccu_reset_map *map = &ccu->reset_map[id];

	/*
	 * The reset control API expects 0 अगर reset is not निश्चितed,
	 * which is the opposite of what our hardware uses.
	 */
	वापस !(map->bit & पढ़ोl(ccu->base + map->reg));
पूर्ण

स्थिर काष्ठा reset_control_ops ccu_reset_ops = अणु
	.निश्चित		= ccu_reset_निश्चित,
	.deनिश्चित	= ccu_reset_deनिश्चित,
	.reset		= ccu_reset_reset,
	.status		= ccu_reset_status,
पूर्ण;
