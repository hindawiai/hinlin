<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CMA_H__
#घोषणा __CMA_H__

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/numa.h>

/*
 * There is always at least global CMA area and a few optional
 * areas configured in kernel .config.
 */
#अगर_घोषित CONFIG_CMA_AREAS
#घोषणा MAX_CMA_AREAS	(1 + CONFIG_CMA_AREAS)

#अन्यथा
#घोषणा MAX_CMA_AREAS	(0)

#पूर्ण_अगर

#घोषणा CMA_MAX_NAME 64

काष्ठा cma;

बाह्य अचिन्हित दीर्घ totalcma_pages;
बाह्य phys_addr_t cma_get_base(स्थिर काष्ठा cma *cma);
बाह्य अचिन्हित दीर्घ cma_get_size(स्थिर काष्ठा cma *cma);
बाह्य स्थिर अक्षर *cma_get_name(स्थिर काष्ठा cma *cma);

बाह्य पूर्णांक __init cma_declare_contiguous_nid(phys_addr_t base,
			phys_addr_t size, phys_addr_t limit,
			phys_addr_t alignment, अचिन्हित पूर्णांक order_per_bit,
			bool fixed, स्थिर अक्षर *name, काष्ठा cma **res_cma,
			पूर्णांक nid);
अटल अंतरभूत पूर्णांक __init cma_declare_contiguous(phys_addr_t base,
			phys_addr_t size, phys_addr_t limit,
			phys_addr_t alignment, अचिन्हित पूर्णांक order_per_bit,
			bool fixed, स्थिर अक्षर *name, काष्ठा cma **res_cma)
अणु
	वापस cma_declare_contiguous_nid(base, size, limit, alignment,
			order_per_bit, fixed, name, res_cma, NUMA_NO_NODE);
पूर्ण
बाह्य पूर्णांक cma_init_reserved_mem(phys_addr_t base, phys_addr_t size,
					अचिन्हित पूर्णांक order_per_bit,
					स्थिर अक्षर *name,
					काष्ठा cma **res_cma);
बाह्य काष्ठा page *cma_alloc(काष्ठा cma *cma, अचिन्हित दीर्घ count, अचिन्हित पूर्णांक align,
			      bool no_warn);
बाह्य bool cma_release(काष्ठा cma *cma, स्थिर काष्ठा page *pages, अचिन्हित दीर्घ count);

बाह्य पूर्णांक cma_क्रम_each_area(पूर्णांक (*it)(काष्ठा cma *cma, व्योम *data), व्योम *data);
#पूर्ण_अगर
