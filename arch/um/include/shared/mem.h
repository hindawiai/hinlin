<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __MEM_H__
#घोषणा __MEM_H__

बाह्य पूर्णांक phys_mapping(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ दीर्घ *offset_out);

बाह्य अचिन्हित दीर्घ uml_physmem;
अटल अंतरभूत अचिन्हित दीर्घ to_phys(व्योम *virt)
अणु
	वापस(((अचिन्हित दीर्घ) virt) - uml_physmem);
पूर्ण

अटल अंतरभूत व्योम *to_virt(अचिन्हित दीर्घ phys)
अणु
	वापस((व्योम *) uml_physmem + phys);
पूर्ण

#पूर्ण_अगर
