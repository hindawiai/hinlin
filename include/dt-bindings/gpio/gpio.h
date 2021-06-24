<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम most GPIO bindings.
 *
 * Most GPIO bindings include a flags cell as part of the GPIO specअगरier.
 * In most हालs, the क्रमmat of the flags cell uses the standard values
 * defined in this header.
 */

#अगर_अघोषित _DT_BINDINGS_GPIO_GPIO_H
#घोषणा _DT_BINDINGS_GPIO_GPIO_H

/* Bit 0 express polarity */
#घोषणा GPIO_ACTIVE_HIGH 0
#घोषणा GPIO_ACTIVE_LOW 1

/* Bit 1 express single-endedness */
#घोषणा GPIO_PUSH_PULL 0
#घोषणा GPIO_SINGLE_ENDED 2

/* Bit 2 express Open drain or खोलो source */
#घोषणा GPIO_LINE_OPEN_SOURCE 0
#घोषणा GPIO_LINE_OPEN_DRAIN 4

/*
 * Open Drain/Collector is the combination of single-ended खोलो drain पूर्णांकerface.
 * Open Source/Emitter is the combination of single-ended खोलो source पूर्णांकerface.
 */
#घोषणा GPIO_OPEN_DRAIN (GPIO_SINGLE_ENDED | GPIO_LINE_OPEN_DRAIN)
#घोषणा GPIO_OPEN_SOURCE (GPIO_SINGLE_ENDED | GPIO_LINE_OPEN_SOURCE)

/* Bit 3 express GPIO suspend/resume and reset persistence */
#घोषणा GPIO_PERSISTENT 0
#घोषणा GPIO_TRANSITORY 8

/* Bit 4 express pull up */
#घोषणा GPIO_PULL_UP 16

/* Bit 5 express pull करोwn */
#घोषणा GPIO_PULL_DOWN 32

#पूर्ण_अगर
