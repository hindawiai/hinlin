<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_IO_H
#घोषणा __ASM_OPENRISC_IO_H

#समावेश <linux/types.h>

/*
 * PCI: can we really करो 0 here अगर we have no port IO?
 */
#घोषणा IO_SPACE_LIMIT		0

/* OpenRISC has no port IO */
#घोषणा HAVE_ARCH_PIO_SIZE	1
#घोषणा PIO_RESERVED		0X0UL
#घोषणा PIO_OFFSET		0
#घोषणा PIO_MASK		0

#घोषणा ioremap ioremap
व्योम __iomem *ioremap(phys_addr_t offset, अचिन्हित दीर्घ size);

#घोषणा iounmap iounmap
बाह्य व्योम iounmap(व्योम __iomem *addr);

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर
