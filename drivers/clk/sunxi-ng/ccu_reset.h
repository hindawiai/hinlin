<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_RESET_H_
#घोषणा _CCU_RESET_H_

#समावेश <linux/reset-controller.h>
#समावेश <linux/spinlock.h>

काष्ठा ccu_reset_map अणु
	u16	reg;
	u32	bit;
पूर्ण;


काष्ठा ccu_reset अणु
	व्योम __iomem			*base;
	काष्ठा ccu_reset_map		*reset_map;
	spinlock_t			*lock;

	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

अटल अंतरभूत काष्ठा ccu_reset *rcdev_to_ccu_reset(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा ccu_reset, rcdev);
पूर्ण

बाह्य स्थिर काष्ठा reset_control_ops ccu_reset_ops;

#पूर्ण_अगर /* _CCU_RESET_H_ */
