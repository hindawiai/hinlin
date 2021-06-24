<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * This header provides स्थिरants क्रम most IRQ bindings.
 *
 * Most IRQ bindings include a flags cell as part of the IRQ specअगरier.
 * In most हालs, the क्रमmat of the flags cell uses the standard values
 * defined in this header.
 */

#अगर_अघोषित _DT_BINDINGS_INTERRUPT_CONTROLLER_IRQ_H
#घोषणा _DT_BINDINGS_INTERRUPT_CONTROLLER_IRQ_H

#घोषणा IRQ_TYPE_NONE		0
#घोषणा IRQ_TYPE_EDGE_RISING	1
#घोषणा IRQ_TYPE_EDGE_FALLING	2
#घोषणा IRQ_TYPE_EDGE_BOTH	(IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
#घोषणा IRQ_TYPE_LEVEL_HIGH	4
#घोषणा IRQ_TYPE_LEVEL_LOW	8

#पूर्ण_अगर
