<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MEMTYPE_H
#घोषणा _ASM_X86_MEMTYPE_H

#समावेश <linux/types.h>
#समावेश <यंत्र/pgtable_types.h>

बाह्य bool pat_enabled(व्योम);
बाह्य व्योम pat_disable(स्थिर अक्षर *reason);
बाह्य व्योम pat_init(व्योम);
बाह्य व्योम init_cache_modes(व्योम);

बाह्य पूर्णांक memtype_reserve(u64 start, u64 end,
		क्रमागत page_cache_mode req_pcm, क्रमागत page_cache_mode *ret_pcm);
बाह्य पूर्णांक memtype_मुक्त(u64 start, u64 end);

बाह्य पूर्णांक memtype_kernel_map_sync(u64 base, अचिन्हित दीर्घ size,
		क्रमागत page_cache_mode pcm);

बाह्य पूर्णांक memtype_reserve_io(resource_माप_प्रकार start, resource_माप_प्रकार end,
			क्रमागत page_cache_mode *pcm);

बाह्य व्योम memtype_मुक्त_io(resource_माप_प्रकार start, resource_माप_प्रकार end);

बाह्य bool pat_pfn_immune_to_uc_mtrr(अचिन्हित दीर्घ pfn);

bool x86_has_pat_wp(व्योम);
क्रमागत page_cache_mode pgprot2cachemode(pgprot_t pgprot);

#पूर्ण_अगर /* _ASM_X86_MEMTYPE_H */
