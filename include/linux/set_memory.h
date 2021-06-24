<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2017, Michael Ellerman, IBM Corporation.
 */
#अगर_अघोषित _LINUX_SET_MEMORY_H_
#घोषणा _LINUX_SET_MEMORY_H_

#अगर_घोषित CONFIG_ARCH_HAS_SET_MEMORY
#समावेश <यंत्र/set_memory.h>
#अन्यथा
अटल अंतरभूत पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_x(अचिन्हित दीर्घ addr,  पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ARCH_HAS_SET_सूचीECT_MAP
अटल अंतरभूत पूर्णांक set_direct_map_invalid_noflush(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक set_direct_map_शेष_noflush(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool kernel_page_present(काष्ठा page *page)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित set_mce_nospec
अटल अंतरभूत पूर्णांक set_mce_nospec(अचिन्हित दीर्घ pfn, bool unmap)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित clear_mce_nospec
अटल अंतरभूत पूर्णांक clear_mce_nospec(अचिन्हित दीर्घ pfn)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ARCH_HAS_MEM_ENCRYPT
अटल अंतरभूत पूर्णांक set_memory_encrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक set_memory_decrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_MEM_ENCRYPT */

#पूर्ण_अगर /* _LINUX_SET_MEMORY_H_ */
