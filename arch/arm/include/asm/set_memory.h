<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 1999-2002 Russell King
 */

#अगर_अघोषित _ASMARM_SET_MEMORY_H
#घोषणा _ASMARM_SET_MEMORY_H

#अगर_घोषित CONFIG_MMU
पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages);
#अन्यथा
अटल अंतरभूत पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
