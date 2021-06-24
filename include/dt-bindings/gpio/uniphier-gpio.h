<शैली गुरु>
/*
 * Copyright (C) 2017 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#अगर_अघोषित _DT_BINDINGS_GPIO_UNIPHIER_H
#घोषणा _DT_BINDINGS_GPIO_UNIPHIER_H

#घोषणा UNIPHIER_GPIO_LINES_PER_BANK	8

#घोषणा UNIPHIER_GPIO_IRQ_OFFSET	((UNIPHIER_GPIO_LINES_PER_BANK) * 15)

#घोषणा UNIPHIER_GPIO_PORT(bank, line)	\
			((UNIPHIER_GPIO_LINES_PER_BANK) * (bank) + (line))

#घोषणा UNIPHIER_GPIO_IRQ(n)		((UNIPHIER_GPIO_IRQ_OFFSET) + (n))

#पूर्ण_अगर /* _DT_BINDINGS_GPIO_UNIPHIER_H */
