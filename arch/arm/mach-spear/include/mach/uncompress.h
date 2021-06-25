<शैली गुरु>
/*
 * arch/arm/plat-spear/include/plat/uncompress.h
 *
 * Serial port stubs क्रम kernel decompress status messages
 *
 * Copyright (C) 2009 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/amba/serial.h>
#समावेश <mach/spear.h>

#अगर_अघोषित __PLAT_UNCOMPRESS_H
#घोषणा __PLAT_UNCOMPRESS_H
/*
 * This करोes not append a newline
 */
अटल अंतरभूत व्योम अ_दो(पूर्णांक c)
अणु
	व्योम __iomem *base = (व्योम __iomem *)SPEAR_DBG_UART_BASE;

	जबतक (पढ़ोl_relaxed(base + UART01x_FR) & UART01x_FR_TXFF)
		barrier();

	ग_लिखोl_relaxed(c, base + UART01x_DR);
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण

/*
 * nothing to करो
 */
#घोषणा arch_decomp_setup()

#पूर्ण_अगर /* __PLAT_UNCOMPRESS_H */
