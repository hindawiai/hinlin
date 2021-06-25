<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2019 SiFive
 */

#अगर_अघोषित _ASM_RISCV_SET_MEMORY_H
#घोषणा _ASM_RISCV_SET_MEMORY_H

#अगर_अघोषित __ASSEMBLY__
/*
 * Functions to change memory attributes.
 */
#अगर_घोषित CONFIG_MMU
पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_rw_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages);
व्योम protect_kernel_text_data(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम protect_kernel_text_data(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक set_memory_rw_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_64BIT) && defined(CONFIG_STRICT_KERNEL_RWX)
व्योम protect_kernel_linear_mapping_text_rodata(व्योम);
#अन्यथा
अटल अंतरभूत व्योम protect_kernel_linear_mapping_text_rodata(व्योम) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक set_direct_map_invalid_noflush(काष्ठा page *page);
पूर्णांक set_direct_map_शेष_noflush(काष्ठा page *page);
bool kernel_page_present(काष्ठा page *page);

#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
#अगर_घोषित CONFIG_64BIT
#घोषणा SECTION_ALIGN (1 << 21)
#अन्यथा
#घोषणा SECTION_ALIGN (1 << 22)
#पूर्ण_अगर
#अन्यथा /* !CONFIG_STRICT_KERNEL_RWX */
#घोषणा SECTION_ALIGN L1_CACHE_BYTES
#पूर्ण_अगर /* CONFIG_STRICT_KERNEL_RWX */

#पूर्ण_अगर /* _ASM_RISCV_SET_MEMORY_H */
