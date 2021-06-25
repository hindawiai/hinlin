<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _X86_SGX_H
#घोषणा _X86_SGX_H

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/rwsem.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/sgx.h>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "sgx: " fmt

#घोषणा EREMOVE_ERROR_MESSAGE \
	"EREMOVE returned %d (0x%x) and an EPC page was leaked. SGX may become unusable. " \
	"Refer to Documentation/x86/sgx.rst for more information."

#घोषणा SGX_MAX_EPC_SECTIONS		8
#घोषणा SGX_EEXTEND_BLOCK_SIZE		256
#घोषणा SGX_NR_TO_SCAN			16
#घोषणा SGX_NR_LOW_PAGES		32
#घोषणा SGX_NR_HIGH_PAGES		64

/* Pages, which are being tracked by the page reclaimer. */
#घोषणा SGX_EPC_PAGE_RECLAIMER_TRACKED	BIT(0)

काष्ठा sgx_epc_page अणु
	अचिन्हित पूर्णांक section;
	अचिन्हित पूर्णांक flags;
	काष्ठा sgx_encl_page *owner;
	काष्ठा list_head list;
पूर्ण;

/*
 * Contains the tracking data क्रम NUMA nodes having EPC pages. Most importantly,
 * the मुक्त page list local to the node is stored here.
 */
काष्ठा sgx_numa_node अणु
	काष्ठा list_head मुक्त_page_list;
	spinlock_t lock;
पूर्ण;

/*
 * The firmware can define multiple chunks of EPC to the dअगरferent areas of the
 * physical memory e.g. क्रम memory areas of the each node. This काष्ठाure is
 * used to store EPC pages क्रम one EPC section and भव memory area where
 * the pages have been mapped.
 */
काष्ठा sgx_epc_section अणु
	अचिन्हित दीर्घ phys_addr;
	व्योम *virt_addr;
	काष्ठा sgx_epc_page *pages;
	काष्ठा sgx_numa_node *node;
पूर्ण;

बाह्य काष्ठा sgx_epc_section sgx_epc_sections[SGX_MAX_EPC_SECTIONS];

अटल अंतरभूत अचिन्हित दीर्घ sgx_get_epc_phys_addr(काष्ठा sgx_epc_page *page)
अणु
	काष्ठा sgx_epc_section *section = &sgx_epc_sections[page->section];
	अचिन्हित दीर्घ index;

	index = ((अचिन्हित दीर्घ)page - (अचिन्हित दीर्घ)section->pages) / माप(*page);

	वापस section->phys_addr + index * PAGE_SIZE;
पूर्ण

अटल अंतरभूत व्योम *sgx_get_epc_virt_addr(काष्ठा sgx_epc_page *page)
अणु
	काष्ठा sgx_epc_section *section = &sgx_epc_sections[page->section];
	अचिन्हित दीर्घ index;

	index = ((अचिन्हित दीर्घ)page - (अचिन्हित दीर्घ)section->pages) / माप(*page);

	वापस section->virt_addr + index * PAGE_SIZE;
पूर्ण

काष्ठा sgx_epc_page *__sgx_alloc_epc_page(व्योम);
व्योम sgx_मुक्त_epc_page(काष्ठा sgx_epc_page *page);

व्योम sgx_mark_page_reclaimable(काष्ठा sgx_epc_page *page);
पूर्णांक sgx_unmark_page_reclaimable(काष्ठा sgx_epc_page *page);
काष्ठा sgx_epc_page *sgx_alloc_epc_page(व्योम *owner, bool reclaim);

#अगर_घोषित CONFIG_X86_SGX_KVM
पूर्णांक __init sgx_vepc_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक __init sgx_vepc_init(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

व्योम sgx_update_lepubkeyhash(u64 *lepubkeyhash);

#पूर्ण_अगर /* _X86_SGX_H */
