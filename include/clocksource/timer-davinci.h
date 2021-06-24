<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI DaVinci घड़ीsource driver
 *
 * Copyright (C) 2019 Texas Instruments
 * Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#अगर_अघोषित __TIMER_DAVINCI_H__
#घोषणा __TIMER_DAVINCI_H__

#समावेश <linux/clk.h>
#समावेश <linux/ioport.h>

क्रमागत अणु
	DAVINCI_TIMER_CLOCKEVENT_IRQ,
	DAVINCI_TIMER_CLOCKSOURCE_IRQ,
	DAVINCI_TIMER_NUM_IRQS,
पूर्ण;

/**
 * काष्ठा davinci_समयr_cfg - davinci घड़ीsource driver configuration काष्ठा
 * @reg:        रेजिस्टर range resource
 * @irq:        घड़ीevent and घड़ीsource पूर्णांकerrupt resources
 * @cmp_off:    अगर set - it specअगरies the compare रेजिस्टर used क्रम घड़ीevent
 *
 * Note: अगर the compare रेजिस्टर is specअगरied, the driver will use the bottom
 * घड़ी half क्रम both घड़ीsource and घड़ीevent and the compare रेजिस्टर
 * to generate event irqs. The user must supply the correct compare रेजिस्टर
 * पूर्णांकerrupt number.
 *
 * This is only used by da830 the DSP of which uses the top half. The समयr
 * driver still configures the top half to run in मुक्त-run mode.
 */
काष्ठा davinci_समयr_cfg अणु
	काष्ठा resource reg;
	काष्ठा resource irq[DAVINCI_TIMER_NUM_IRQS];
	अचिन्हित पूर्णांक cmp_off;
पूर्ण;

पूर्णांक __init davinci_समयr_रेजिस्टर(काष्ठा clk *clk,
				  स्थिर काष्ठा davinci_समयr_cfg *data);

#पूर्ण_अगर /* __TIMER_DAVINCI_H__ */
