<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 */
#अगर_अघोषित __CLOCKSOURCE_SAMSUNG_PWM_H
#घोषणा __CLOCKSOURCE_SAMSUNG_PWM_H

#समावेश <linux/spinlock.h>

#घोषणा SAMSUNG_PWM_NUM		5

/*
 * Following declaration must be in an अगरdef due to this symbol being अटल
 * in pwm-samsung driver अगर the घड़ीsource driver is not compiled in and the
 * spinlock is not shared between both drivers.
 */
#अगर_घोषित CONFIG_CLKSRC_SAMSUNG_PWM
बाह्य spinlock_t samsung_pwm_lock;
#पूर्ण_अगर

काष्ठा samsung_pwm_variant अणु
	u8 bits;
	u8 भाग_base;
	u8 tclk_mask;
	u8 output_mask;
	bool has_tपूर्णांक_cstat;
पूर्ण;

व्योम samsung_pwm_घड़ीsource_init(व्योम __iomem *base,
		अचिन्हित पूर्णांक *irqs, काष्ठा samsung_pwm_variant *variant);

#पूर्ण_अगर /* __CLOCKSOURCE_SAMSUNG_PWM_H */
