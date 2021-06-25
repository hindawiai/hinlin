<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASMS390_SET_MEMORY_H
#घोषणा _ASMS390_SET_MEMORY_H

#समावेश <linux/mutex.h>

बाह्य काष्ठा mutex cpa_mutex;

#घोषणा SET_MEMORY_RO	1UL
#घोषणा SET_MEMORY_RW	2UL
#घोषणा SET_MEMORY_NX	4UL
#घोषणा SET_MEMORY_X	8UL

पूर्णांक __set_memory(अचिन्हित दीर्घ addr, पूर्णांक numpages, अचिन्हित दीर्घ flags);

अटल अंतरभूत पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, SET_MEMORY_RO);
पूर्ण

अटल अंतरभूत पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, SET_MEMORY_RW);
पूर्ण

अटल अंतरभूत पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, SET_MEMORY_NX);
पूर्ण

अटल अंतरभूत पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, SET_MEMORY_X);
पूर्ण

#पूर्ण_अगर
