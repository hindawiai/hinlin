<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * eisa_bus.h पूर्णांकerface between the eisa BA driver and the bus क्रमागतerator
 *
 * Copyright (c) 2002 Daniel Engstrom <5116@telia.com>
 */

#अगर_अघोषित ASM_EISA_H
#घोषणा ASM_EISA_H

बाह्य व्योम eisa_make_irq_level(पूर्णांक num);
बाह्य व्योम eisa_make_irq_edge(पूर्णांक num);
बाह्य पूर्णांक eisa_क्रमागतerator(अचिन्हित दीर्घ eeprom_addr,
			   काष्ठा resource *io_parent, 
			   काष्ठा resource *mem_parent);
बाह्य पूर्णांक eisa_eeprom_init(अचिन्हित दीर्घ addr);

#पूर्ण_अगर
