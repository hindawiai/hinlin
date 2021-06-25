<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/glue-cache.h
 *
 *  Copyright (C) 1999-2002 Russell King
 */
#अगर_अघोषित ASM_GLUE_CACHE_H
#घोषणा ASM_GLUE_CACHE_H

#समावेश <यंत्र/glue.h>

/*
 *	Cache Model
 *	===========
 */
#अघोषित _CACHE
#अघोषित MULTI_CACHE

#अगर defined(CONFIG_CPU_CACHE_V4)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE v4
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_ARM920T) || defined(CONFIG_CPU_ARM922T) || \
    defined(CONFIG_CPU_ARM925T) || defined(CONFIG_CPU_ARM1020) || \
    defined(CONFIG_CPU_ARM1026)
# define MULTI_CACHE 1
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_FA526)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE fa
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_ARM926T)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE arm926
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_ARM940T)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE arm940
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_ARM946E)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE arm946
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_CACHE_V4WB)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE v4wb
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_XSCALE)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE xscale
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_XSC3)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE xsc3
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_MOHAWK)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE mohawk
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_FEROCEON)
# define MULTI_CACHE 1
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE v6
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_V7)
# अगरdef _CACHE
#  define MULTI_CACHE 1
# अन्यथा
#  define _CACHE v7
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CACHE_B15_RAC)
# define MULTI_CACHE 1
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_V7M)
#  define MULTI_CACHE 1
#पूर्ण_अगर

#अगर !defined(_CACHE) && !defined(MULTI_CACHE)
#त्रुटि Unknown cache मुख्यtenance model
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLER__
अटल अंतरभूत व्योम nop_flush_icache_all(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम nop_flush_kern_cache_all(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम nop_flush_kern_cache_louis(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम nop_flush_user_cache_all(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम nop_flush_user_cache_range(अचिन्हित दीर्घ a,
		अचिन्हित दीर्घ b, अचिन्हित पूर्णांक c) अणु पूर्ण

अटल अंतरभूत व्योम nop_coherent_kern_range(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b) अणु पूर्ण
अटल अंतरभूत पूर्णांक nop_coherent_user_range(अचिन्हित दीर्घ a,
		अचिन्हित दीर्घ b) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nop_flush_kern_dcache_area(व्योम *a, माप_प्रकार s) अणु पूर्ण

अटल अंतरभूत व्योम nop_dma_flush_range(स्थिर व्योम *a, स्थिर व्योम *b) अणु पूर्ण

अटल अंतरभूत व्योम nop_dma_map_area(स्थिर व्योम *s, माप_प्रकार l, पूर्णांक f) अणु पूर्ण
अटल अंतरभूत व्योम nop_dma_unmap_area(स्थिर व्योम *s, माप_प्रकार l, पूर्णांक f) अणु पूर्ण
#पूर्ण_अगर

#अगर_अघोषित MULTI_CACHE
#घोषणा __cpuc_flush_icache_all		__glue(_CACHE,_flush_icache_all)
#घोषणा __cpuc_flush_kern_all		__glue(_CACHE,_flush_kern_cache_all)
#घोषणा __cpuc_flush_kern_louis		__glue(_CACHE,_flush_kern_cache_louis)
#घोषणा __cpuc_flush_user_all		__glue(_CACHE,_flush_user_cache_all)
#घोषणा __cpuc_flush_user_range		__glue(_CACHE,_flush_user_cache_range)
#घोषणा __cpuc_coherent_kern_range	__glue(_CACHE,_coherent_kern_range)
#घोषणा __cpuc_coherent_user_range	__glue(_CACHE,_coherent_user_range)
#घोषणा __cpuc_flush_dcache_area	__glue(_CACHE,_flush_kern_dcache_area)

#घोषणा dmac_flush_range		__glue(_CACHE,_dma_flush_range)
#पूर्ण_अगर

#पूर्ण_अगर
