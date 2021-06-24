<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SET_MEMORY_H
#घोषणा _ASM_X86_SET_MEMORY_H

#समावेश <यंत्र/page.h>
#समावेश <यंत्र-generic/set_memory.h>

/*
 * The set_memory_* API can be used to change various attributes of a भव
 * address range. The attributes include:
 * Cacheability  : UnCached, WriteCombining, WriteThrough, WriteBack
 * Executability : eXecutable, NoteXecutable
 * Read/Write    : ReadOnly, ReadWrite
 * Presence      : NotPresent
 * Encryption    : Encrypted, Decrypted
 *
 * Within a category, the attributes are mutually exclusive.
 *
 * The implementation of this API will take care of various aspects that
 * are associated with changing such attributes, such as:
 * - Flushing TLBs
 * - Flushing CPU caches
 * - Making sure aliases of the memory behind the mapping करोn't violate
 *   coherency rules as defined by the CPU in the प्रणाली.
 *
 * What this API करोes not करो:
 * - Provide exclusion between various callers - including callers that
 *   operation on other mappings of the same physical page
 * - Restore शेष attributes when a page is मुक्तd
 * - Guarantee that mappings other than the requested one are
 *   in any state, other than that these करो not violate rules क्रम
 *   the CPU you have. Do not depend on any effects on other mappings,
 *   CPUs other than the one you have may have more relaxed rules.
 * The caller is required to take care of these.
 */

पूर्णांक __set_memory_prot(अचिन्हित दीर्घ addr, पूर्णांक numpages, pgprot_t prot);
पूर्णांक _set_memory_uc(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक _set_memory_wc(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक _set_memory_wt(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक _set_memory_wb(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_uc(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_wc(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_wb(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_np(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_4k(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_encrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_decrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_np_noalias(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_nonglobal(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_global(अचिन्हित दीर्घ addr, पूर्णांक numpages);

पूर्णांक set_pages_array_uc(काष्ठा page **pages, पूर्णांक addrinarray);
पूर्णांक set_pages_array_wc(काष्ठा page **pages, पूर्णांक addrinarray);
पूर्णांक set_pages_array_wt(काष्ठा page **pages, पूर्णांक addrinarray);
पूर्णांक set_pages_array_wb(काष्ठा page **pages, पूर्णांक addrinarray);

/*
 * For legacy compatibility with the old APIs, a few functions
 * are provided that work on a "struct page".
 * These functions operate ONLY on the 1:1 kernel mapping of the
 * memory that the काष्ठा page represents, and पूर्णांकernally just
 * call the set_memory_* function. See the description of the
 * set_memory_* function क्रम more details on conventions.
 *
 * These APIs should be considered *deprecated* and are likely going to
 * be हटाओd in the future.
 * The reason क्रम this is the implicit operation on the 1:1 mapping only,
 * making this not a generally useful API.
 *
 * Specअगरically, many users of the old APIs had a भव address,
 * called virt_to_page() or vदो_स्मृति_to_page() on that address to
 * get a काष्ठा page* that the old API required.
 * To convert these हालs, use set_memory_*() on the original
 * भव address, करो not use these functions.
 */

पूर्णांक set_pages_uc(काष्ठा page *page, पूर्णांक numpages);
पूर्णांक set_pages_wb(काष्ठा page *page, पूर्णांक numpages);
पूर्णांक set_pages_ro(काष्ठा page *page, पूर्णांक numpages);
पूर्णांक set_pages_rw(काष्ठा page *page, पूर्णांक numpages);

पूर्णांक set_direct_map_invalid_noflush(काष्ठा page *page);
पूर्णांक set_direct_map_शेष_noflush(काष्ठा page *page);
bool kernel_page_present(काष्ठा page *page);

बाह्य पूर्णांक kernel_set_to_पढ़ोonly;

#अगर_घोषित CONFIG_X86_64
/*
 * Prevent speculative access to the page by either unmapping
 * it (अगर we करो not require access to any part of the page) or
 * marking it uncacheable (अगर we want to try to retrieve data
 * from non-poisoned lines in the page).
 */
अटल अंतरभूत पूर्णांक set_mce_nospec(अचिन्हित दीर्घ pfn, bool unmap)
अणु
	अचिन्हित दीर्घ decoy_addr;
	पूर्णांक rc;

	/*
	 * We would like to just call:
	 *      set_memory_XX((अचिन्हित दीर्घ)pfn_to_kaddr(pfn), 1);
	 * but करोing that would radically increase the odds of a
	 * speculative access to the poison page because we'd have
	 * the भव address of the kernel 1:1 mapping sitting
	 * around in रेजिस्टरs.
	 * Instead we get tricky.  We create a non-canonical address
	 * that looks just like the one we want, but has bit 63 flipped.
	 * This relies on set_memory_XX() properly sanitizing any __pa()
	 * results with __PHYSICAL_MASK or PTE_PFN_MASK.
	 */
	decoy_addr = (pfn << PAGE_SHIFT) + (PAGE_OFFSET ^ BIT(63));

	अगर (unmap)
		rc = set_memory_np(decoy_addr, 1);
	अन्यथा
		rc = set_memory_uc(decoy_addr, 1);
	अगर (rc)
		pr_warn("Could not invalidate pfn=0x%lx from 1:1 map\n", pfn);
	वापस rc;
पूर्ण
#घोषणा set_mce_nospec set_mce_nospec

/* Restore full speculative operation to the pfn. */
अटल अंतरभूत पूर्णांक clear_mce_nospec(अचिन्हित दीर्घ pfn)
अणु
	वापस set_memory_wb((अचिन्हित दीर्घ) pfn_to_kaddr(pfn), 1);
पूर्ण
#घोषणा clear_mce_nospec clear_mce_nospec
#अन्यथा
/*
 * Few people would run a 32-bit kernel on a machine that supports
 * recoverable errors because they have too much memory to boot 32-bit.
 */
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_SET_MEMORY_H */
