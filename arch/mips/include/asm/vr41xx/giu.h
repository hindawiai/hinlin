<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Include file क्रम NEC VR4100 series General-purpose I/O Unit.
 *
 *  Copyright (C) 2005-2009  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __NEC_VR41XX_GIU_H
#घोषणा __NEC_VR41XX_GIU_H

/*
 * NEC VR4100 series GIU platक्रमm device IDs.
 */
क्रमागत अणु
	GPIO_50PINS_PULLUPDOWN,
	GPIO_36PINS,
	GPIO_48PINS_EDGE_SELECT,
पूर्ण;

प्रकार क्रमागत अणु
	IRQ_TRIGGER_LEVEL,
	IRQ_TRIGGER_EDGE,
	IRQ_TRIGGER_EDGE_FALLING,
	IRQ_TRIGGER_EDGE_RISING,
पूर्ण irq_trigger_t;

प्रकार क्रमागत अणु
	IRQ_SIGNAL_THROUGH,
	IRQ_SIGNAL_HOLD,
पूर्ण irq_संकेत_t;

बाह्य व्योम vr41xx_set_irq_trigger(अचिन्हित पूर्णांक pin, irq_trigger_t trigger,
				   irq_संकेत_t संकेत);

प्रकार क्रमागत अणु
	IRQ_LEVEL_LOW,
	IRQ_LEVEL_HIGH,
पूर्ण irq_level_t;

बाह्य व्योम vr41xx_set_irq_level(अचिन्हित पूर्णांक pin, irq_level_t level);

#पूर्ण_अगर /* __NEC_VR41XX_GIU_H */
