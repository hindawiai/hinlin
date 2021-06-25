<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_EARLY_IOREMAP_H_
#घोषणा _ASM_EARLY_IOREMAP_H_

#समावेश <linux/types.h>

/*
 * early_ioremap() and early_iounmap() are क्रम temporary early boot-समय
 * mappings, beक्रमe the real ioremap() is functional.
 */
बाह्य व्योम __iomem *early_ioremap(resource_माप_प्रकार phys_addr,
				   अचिन्हित दीर्घ size);
बाह्य व्योम *early_memremap(resource_माप_प्रकार phys_addr,
			    अचिन्हित दीर्घ size);
बाह्य व्योम *early_memremap_ro(resource_माप_प्रकार phys_addr,
			       अचिन्हित दीर्घ size);
बाह्य व्योम *early_memremap_prot(resource_माप_प्रकार phys_addr,
				 अचिन्हित दीर्घ size, अचिन्हित दीर्घ prot_val);
बाह्य व्योम early_iounmap(व्योम __iomem *addr, अचिन्हित दीर्घ size);
बाह्य व्योम early_memunmap(व्योम *addr, अचिन्हित दीर्घ size);

/*
 * Weak function called by early_ioremap_reset(). It करोes nothing, but
 * architectures may provide their own version to करो any needed cleanups.
 */
बाह्य व्योम early_ioremap_shutकरोwn(व्योम);

#अगर defined(CONFIG_GENERIC_EARLY_IOREMAP) && defined(CONFIG_MMU)
/* Arch-specअगरic initialization */
बाह्य व्योम early_ioremap_init(व्योम);

/* Generic initialization called by architecture code */
बाह्य व्योम early_ioremap_setup(व्योम);

/*
 * Called as last step in paging_init() so library can act
 * accordingly क्रम subsequent map/unmap requests.
 */
बाह्य व्योम early_ioremap_reset(व्योम);

/*
 * Early copy from unmapped memory to kernel mapped memory.
 */
बाह्य व्योम copy_from_early_mem(व्योम *dest, phys_addr_t src,
				अचिन्हित दीर्घ size);

#अन्यथा
अटल अंतरभूत व्योम early_ioremap_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम early_ioremap_setup(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम early_ioremap_reset(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_EARLY_IOREMAP_H_ */
