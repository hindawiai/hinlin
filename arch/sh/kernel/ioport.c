<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/ioport.c
 *
 * Copyright (C) 2000  Niibe Yutaka
 * Copyright (C) 2005 - 2007 Paul Mundt
 */
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/io_trapped.h>

अचिन्हित दीर्घ sh_io_port_base __पढ़ो_mostly = -1;
EXPORT_SYMBOL(sh_io_port_base);

व्योम __iomem *__ioport_map(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size)
अणु
	अगर (sh_mv.mv_ioport_map)
		वापस sh_mv.mv_ioport_map(addr, size);

	वापस (व्योम __iomem *)(addr + sh_io_port_base);
पूर्ण
EXPORT_SYMBOL(__ioport_map);

व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	व्योम __iomem *ret;

	ret = __ioport_map_trapped(port, nr);
	अगर (ret)
		वापस ret;

	वापस __ioport_map(port, nr);
पूर्ण
EXPORT_SYMBOL(ioport_map);

व्योम ioport_unmap(व्योम __iomem *addr)
अणु
	अगर (sh_mv.mv_ioport_unmap)
		sh_mv.mv_ioport_unmap(addr);
पूर्ण
EXPORT_SYMBOL(ioport_unmap);
