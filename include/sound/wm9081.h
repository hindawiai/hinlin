<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/wm9081.h -- Platक्रमm data क्रम WM9081
 *
 * Copyright 2009 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_WM_9081_H
#घोषणा __LINUX_SND_WM_9081_H

काष्ठा wm9081_retune_mobile_setting अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक rate;
	u16 config[20];
पूर्ण;

काष्ठा wm9081_pdata अणु
	bool irq_high;   /* IRQ is active high */
	bool irq_cmos;   /* IRQ is in CMOS mode */

	काष्ठा wm9081_retune_mobile_setting *retune_configs;
	पूर्णांक num_retune_configs;
पूर्ण;

#पूर्ण_अगर
