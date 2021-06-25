<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * contains some Q40 related पूर्णांकerrupt definitions
 */

#घोषणा Q40_IRQ_MAX      (34)

#घोषणा Q40_IRQ_SAMPLE    (34)
#घोषणा Q40_IRQ_KEYBOARD (32)
#घोषणा Q40_IRQ_FRAME    (33)


/* masks क्रम पूर्णांकerrupt regiosters*/
/* पूर्णांकernal, IIRQ_REG */
#घोषणा Q40_IRQ_KEYB_MASK    (2)
#घोषणा Q40_IRQ_SER_MASK     (1<<2)
#घोषणा Q40_IRQ_FRAME_MASK   (1<<3)
#घोषणा Q40_IRQ_EXT_MASK     (1<<4)    /* is a EIRQ */
/* eirq, EIRQ_REG */
#घोषणा Q40_IRQ3_MASK        (1)
#घोषणा Q40_IRQ4_MASK        (1<<1)
#घोषणा Q40_IRQ5_MASK        (1<<2)
#घोषणा Q40_IRQ6_MASK        (1<<3)
#घोषणा Q40_IRQ7_MASK        (1<<4)
#घोषणा Q40_IRQ10_MASK       (1<<5)
#घोषणा Q40_IRQ14_MASK       (1<<6)
#घोषणा Q40_IRQ15_MASK       (1<<7)
