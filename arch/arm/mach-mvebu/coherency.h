<शैली गुरु>
/*
 * arch/arm/mach-mvebu/include/mach/coherency.h
 *
 *
 * Coherency fabric (Aurora) support क्रम Armada 370 and XP platक्रमms.
 *
 * Copyright (C) 2012 Marvell
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __MACH_370_XP_COHERENCY_H
#घोषणा __MACH_370_XP_COHERENCY_H

बाह्य व्योम __iomem *coherency_base;	/* क्रम coherency_ll.S */
बाह्य अचिन्हित दीर्घ coherency_phys_base;
पूर्णांक set_cpu_coherent(व्योम);

पूर्णांक coherency_init(व्योम);
पूर्णांक coherency_available(व्योम);

#पूर्ण_अगर	/* __MACH_370_XP_COHERENCY_H */
