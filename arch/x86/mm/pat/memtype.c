<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Page Attribute Table (PAT) support: handle memory caching attributes in page tables.
 *
 * Authors: Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *          Suresh B Siddha <suresh.b.siddha@पूर्णांकel.com>
 *
 * Loosely based on earlier PAT patchset from Eric Biederman and Andi Kleen.
 *
 * Basic principles:
 *
 * PAT is a CPU feature supported by all modern x86 CPUs, to allow the firmware and
 * the kernel to set one of a handful of 'caching type' attributes क्रम physical
 * memory ranges: uncached, ग_लिखो-combining, ग_लिखो-through, ग_लिखो-रक्षित,
 * and the most commonly used and शेष attribute: ग_लिखो-back caching.
 *
 * PAT support supercedes and augments MTRR support in a compatible fashion: MTRR is
 * a hardware पूर्णांकerface to क्रमागतerate a limited number of physical memory ranges
 * and set their caching attributes explicitly, programmed पूर्णांकo the CPU via MSRs.
 * Even modern CPUs have MTRRs enabled - but these are typically not touched
 * by the kernel or by user-space (such as the X server), we rely on PAT क्रम any
 * additional cache attribute logic.
 *
 * PAT करोesn't work via explicit memory ranges, but uses page table entries to add
 * cache attribute inक्रमmation to the mapped memory range: there's 3 bits used,
 * (_PAGE_PWT, _PAGE_PCD, _PAGE_PAT), with the 8 possible values mapped by the
 * CPU to actual cache attributes via an MSR loaded पूर्णांकo the CPU (MSR_IA32_CR_PAT).
 *
 * ( There's a metric ton of finer details, such as compatibility with CPU quirks
 *   that only support 4 types of PAT entries, and पूर्णांकeraction with MTRRs, see
 *   below क्रम details. )
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/memblock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/rbtree.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/fcntl.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/पन.स>

#समावेश "memtype.h"
#समावेश "../mm_internal.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "" fmt

अटल bool __पढ़ो_mostly pat_bp_initialized;
अटल bool __पढ़ो_mostly pat_disabled = !IS_ENABLED(CONFIG_X86_PAT);
अटल bool __पढ़ो_mostly pat_bp_enabled;
अटल bool __पढ़ो_mostly pat_cm_initialized;

/*
 * PAT support is enabled by शेष, but can be disabled क्रम
 * various user-requested or hardware-क्रमced reasons:
 */
व्योम pat_disable(स्थिर अक्षर *msg_reason)
अणु
	अगर (pat_disabled)
		वापस;

	अगर (pat_bp_initialized) अणु
		WARN_ONCE(1, "x86/PAT: PAT cannot be disabled after initialization\n");
		वापस;
	पूर्ण

	pat_disabled = true;
	pr_info("x86/PAT: %s\n", msg_reason);
पूर्ण

अटल पूर्णांक __init nopat(अक्षर *str)
अणु
	pat_disable("PAT support disabled via boot option.");
	वापस 0;
पूर्ण
early_param("nopat", nopat);

bool pat_enabled(व्योम)
अणु
	वापस pat_bp_enabled;
पूर्ण
EXPORT_SYMBOL_GPL(pat_enabled);

पूर्णांक pat_debug_enable;

अटल पूर्णांक __init pat_debug_setup(अक्षर *str)
अणु
	pat_debug_enable = 1;
	वापस 0;
पूर्ण
__setup("debugpat", pat_debug_setup);

#अगर_घोषित CONFIG_X86_PAT
/*
 * X86 PAT uses page flags arch_1 and uncached together to keep track of
 * memory type of pages that have backing page काष्ठा.
 *
 * X86 PAT supports 4 dअगरferent memory types:
 *  - _PAGE_CACHE_MODE_WB
 *  - _PAGE_CACHE_MODE_WC
 *  - _PAGE_CACHE_MODE_UC_MINUS
 *  - _PAGE_CACHE_MODE_WT
 *
 * _PAGE_CACHE_MODE_WB is the शेष type.
 */

#घोषणा _PGMT_WB		0
#घोषणा _PGMT_WC		(1UL << PG_arch_1)
#घोषणा _PGMT_UC_MINUS		(1UL << PG_uncached)
#घोषणा _PGMT_WT		(1UL << PG_uncached | 1UL << PG_arch_1)
#घोषणा _PGMT_MASK		(1UL << PG_uncached | 1UL << PG_arch_1)
#घोषणा _PGMT_CLEAR_MASK	(~_PGMT_MASK)

अटल अंतरभूत क्रमागत page_cache_mode get_page_memtype(काष्ठा page *pg)
अणु
	अचिन्हित दीर्घ pg_flags = pg->flags & _PGMT_MASK;

	अगर (pg_flags == _PGMT_WB)
		वापस _PAGE_CACHE_MODE_WB;
	अन्यथा अगर (pg_flags == _PGMT_WC)
		वापस _PAGE_CACHE_MODE_WC;
	अन्यथा अगर (pg_flags == _PGMT_UC_MINUS)
		वापस _PAGE_CACHE_MODE_UC_MINUS;
	अन्यथा
		वापस _PAGE_CACHE_MODE_WT;
पूर्ण

अटल अंतरभूत व्योम set_page_memtype(काष्ठा page *pg,
				    क्रमागत page_cache_mode memtype)
अणु
	अचिन्हित दीर्घ memtype_flags;
	अचिन्हित दीर्घ old_flags;
	अचिन्हित दीर्घ new_flags;

	चयन (memtype) अणु
	हाल _PAGE_CACHE_MODE_WC:
		memtype_flags = _PGMT_WC;
		अवरोध;
	हाल _PAGE_CACHE_MODE_UC_MINUS:
		memtype_flags = _PGMT_UC_MINUS;
		अवरोध;
	हाल _PAGE_CACHE_MODE_WT:
		memtype_flags = _PGMT_WT;
		अवरोध;
	हाल _PAGE_CACHE_MODE_WB:
	शेष:
		memtype_flags = _PGMT_WB;
		अवरोध;
	पूर्ण

	करो अणु
		old_flags = pg->flags;
		new_flags = (old_flags & _PGMT_CLEAR_MASK) | memtype_flags;
	पूर्ण जबतक (cmpxchg(&pg->flags, old_flags, new_flags) != old_flags);
पूर्ण
#अन्यथा
अटल अंतरभूत क्रमागत page_cache_mode get_page_memtype(काष्ठा page *pg)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत व्योम set_page_memtype(काष्ठा page *pg,
				    क्रमागत page_cache_mode memtype)
अणु
पूर्ण
#पूर्ण_अगर

क्रमागत अणु
	PAT_UC = 0,		/* uncached */
	PAT_WC = 1,		/* Write combining */
	PAT_WT = 4,		/* Write Through */
	PAT_WP = 5,		/* Write Protected */
	PAT_WB = 6,		/* Write Back (शेष) */
	PAT_UC_MINUS = 7,	/* UC, but can be overridden by MTRR */
पूर्ण;

#घोषणा CM(c) (_PAGE_CACHE_MODE_ ## c)

अटल क्रमागत page_cache_mode pat_get_cache_mode(अचिन्हित pat_val, अक्षर *msg)
अणु
	क्रमागत page_cache_mode cache;
	अक्षर *cache_mode;

	चयन (pat_val) अणु
	हाल PAT_UC:       cache = CM(UC);       cache_mode = "UC  "; अवरोध;
	हाल PAT_WC:       cache = CM(WC);       cache_mode = "WC  "; अवरोध;
	हाल PAT_WT:       cache = CM(WT);       cache_mode = "WT  "; अवरोध;
	हाल PAT_WP:       cache = CM(WP);       cache_mode = "WP  "; अवरोध;
	हाल PAT_WB:       cache = CM(WB);       cache_mode = "WB  "; अवरोध;
	हाल PAT_UC_MINUS: cache = CM(UC_MINUS); cache_mode = "UC- "; अवरोध;
	शेष:           cache = CM(WB);       cache_mode = "WB  "; अवरोध;
	पूर्ण

	स_नकल(msg, cache_mode, 4);

	वापस cache;
पूर्ण

#अघोषित CM

/*
 * Update the cache mode to pgprot translation tables according to PAT
 * configuration.
 * Using lower indices is preferred, so we start with highest index.
 */
अटल व्योम __init_cache_modes(u64 pat)
अणु
	क्रमागत page_cache_mode cache;
	अक्षर pat_msg[33];
	पूर्णांक i;

	WARN_ON_ONCE(pat_cm_initialized);

	pat_msg[32] = 0;
	क्रम (i = 7; i >= 0; i--) अणु
		cache = pat_get_cache_mode((pat >> (i * 8)) & 7,
					   pat_msg + 4 * i);
		update_cache_mode_entry(i, cache);
	पूर्ण
	pr_info("x86/PAT: Configuration [0-7]: %s\n", pat_msg);

	pat_cm_initialized = true;
पूर्ण

#घोषणा PAT(x, y)	((u64)PAT_ ## y << ((x)*8))

अटल व्योम pat_bp_init(u64 pat)
अणु
	u64 पंचांगp_pat;

	अगर (!boot_cpu_has(X86_FEATURE_PAT)) अणु
		pat_disable("PAT not supported by the CPU.");
		वापस;
	पूर्ण

	rdmsrl(MSR_IA32_CR_PAT, पंचांगp_pat);
	अगर (!पंचांगp_pat) अणु
		pat_disable("PAT support disabled by the firmware.");
		वापस;
	पूर्ण

	wrmsrl(MSR_IA32_CR_PAT, pat);
	pat_bp_enabled = true;

	__init_cache_modes(pat);
पूर्ण

अटल व्योम pat_ap_init(u64 pat)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_PAT)) अणु
		/*
		 * If this happens we are on a secondary CPU, but चयनed to
		 * PAT on the boot CPU. We have no way to unकरो PAT.
		 */
		panic("x86/PAT: PAT enabled, but not supported by secondary CPU\n");
	पूर्ण

	wrmsrl(MSR_IA32_CR_PAT, pat);
पूर्ण

व्योम init_cache_modes(व्योम)
अणु
	u64 pat = 0;

	अगर (pat_cm_initialized)
		वापस;

	अगर (boot_cpu_has(X86_FEATURE_PAT)) अणु
		/*
		 * CPU supports PAT. Set PAT table to be consistent with
		 * PAT MSR. This हाल supports "nopat" boot option, and
		 * भव machine environments which support PAT without
		 * MTRRs. In specअगरic, Xen has unique setup to PAT MSR.
		 *
		 * If PAT MSR वापसs 0, it is considered invalid and emulates
		 * as No PAT.
		 */
		rdmsrl(MSR_IA32_CR_PAT, pat);
	पूर्ण

	अगर (!pat) अणु
		/*
		 * No PAT. Emulate the PAT table that corresponds to the two
		 * cache bits, PWT (Write Through) and PCD (Cache Disable).
		 * This setup is also the same as the BIOS शेष setup.
		 *
		 * PTE encoding:
		 *
		 *       PCD
		 *       |PWT  PAT
		 *       ||    slot
		 *       00    0    WB : _PAGE_CACHE_MODE_WB
		 *       01    1    WT : _PAGE_CACHE_MODE_WT
		 *       10    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *       11    3    UC : _PAGE_CACHE_MODE_UC
		 *
		 * NOTE: When WC or WP is used, it is redirected to UC- per
		 * the शेष setup in __cachemode2pte_tbl[].
		 */
		pat = PAT(0, WB) | PAT(1, WT) | PAT(2, UC_MINUS) | PAT(3, UC) |
		      PAT(4, WB) | PAT(5, WT) | PAT(6, UC_MINUS) | PAT(7, UC);
	पूर्ण

	__init_cache_modes(pat);
पूर्ण

/**
 * pat_init - Initialize the PAT MSR and PAT table on the current CPU
 *
 * This function initializes PAT MSR and PAT table with an OS-defined value
 * to enable additional cache attributes, WC, WT and WP.
 *
 * This function must be called on all CPUs using the specअगरic sequence of
 * operations defined in Intel SDM. mtrr_rendezvous_handler() provides this
 * procedure क्रम PAT.
 */
व्योम pat_init(व्योम)
अणु
	u64 pat;
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

#अगर_अघोषित CONFIG_X86_PAT
	pr_info_once("x86/PAT: PAT support disabled because CONFIG_X86_PAT is disabled in the kernel.\n");
#पूर्ण_अगर

	अगर (pat_disabled)
		वापस;

	अगर ((c->x86_venकरोr == X86_VENDOR_INTEL) &&
	    (((c->x86 == 0x6) && (c->x86_model <= 0xd)) ||
	     ((c->x86 == 0xf) && (c->x86_model <= 0x6)))) अणु
		/*
		 * PAT support with the lower four entries. Intel Pentium 2,
		 * 3, M, and 4 are affected by PAT errata, which makes the
		 * upper four entries unusable. To be on the safe side, we करोn't
		 * use those.
		 *
		 *  PTE encoding:
		 *      PAT
		 *      |PCD
		 *      ||PWT  PAT
		 *      |||    slot
		 *      000    0    WB : _PAGE_CACHE_MODE_WB
		 *      001    1    WC : _PAGE_CACHE_MODE_WC
		 *      010    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *      011    3    UC : _PAGE_CACHE_MODE_UC
		 * PAT bit unused
		 *
		 * NOTE: When WT or WP is used, it is redirected to UC- per
		 * the शेष setup in __cachemode2pte_tbl[].
		 */
		pat = PAT(0, WB) | PAT(1, WC) | PAT(2, UC_MINUS) | PAT(3, UC) |
		      PAT(4, WB) | PAT(5, WC) | PAT(6, UC_MINUS) | PAT(7, UC);
	पूर्ण अन्यथा अणु
		/*
		 * Full PAT support.  We put WT in slot 7 to improve
		 * robustness in the presence of errata that might cause
		 * the high PAT bit to be ignored.  This way, a buggy slot 7
		 * access will hit slot 3, and slot 3 is UC, so at worst
		 * we lose perक्रमmance without causing a correctness issue.
		 * Pentium 4 erratum N46 is an example क्रम such an erratum,
		 * although we try not to use PAT at all on affected CPUs.
		 *
		 *  PTE encoding:
		 *      PAT
		 *      |PCD
		 *      ||PWT  PAT
		 *      |||    slot
		 *      000    0    WB : _PAGE_CACHE_MODE_WB
		 *      001    1    WC : _PAGE_CACHE_MODE_WC
		 *      010    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *      011    3    UC : _PAGE_CACHE_MODE_UC
		 *      100    4    WB : Reserved
		 *      101    5    WP : _PAGE_CACHE_MODE_WP
		 *      110    6    UC-: Reserved
		 *      111    7    WT : _PAGE_CACHE_MODE_WT
		 *
		 * The reserved slots are unused, but mapped to their
		 * corresponding types in the presence of PAT errata.
		 */
		pat = PAT(0, WB) | PAT(1, WC) | PAT(2, UC_MINUS) | PAT(3, UC) |
		      PAT(4, WB) | PAT(5, WP) | PAT(6, UC_MINUS) | PAT(7, WT);
	पूर्ण

	अगर (!pat_bp_initialized) अणु
		pat_bp_init(pat);
		pat_bp_initialized = true;
	पूर्ण अन्यथा अणु
		pat_ap_init(pat);
	पूर्ण
पूर्ण

#अघोषित PAT

अटल DEFINE_SPINLOCK(memtype_lock);	/* protects memtype accesses */

/*
 * Does पूर्णांकersection of PAT memory type and MTRR memory type and वापसs
 * the resulting memory type as PAT understands it.
 * (Type in pat and mtrr will not have same value)
 * The पूर्णांकersection is based on "Effective Memory Type" tables in IA-32
 * SDM vol 3a
 */
अटल अचिन्हित दीर्घ pat_x_mtrr_type(u64 start, u64 end,
				     क्रमागत page_cache_mode req_type)
अणु
	/*
	 * Look क्रम MTRR hपूर्णांक to get the effective type in हाल where PAT
	 * request is क्रम WB.
	 */
	अगर (req_type == _PAGE_CACHE_MODE_WB) अणु
		u8 mtrr_type, unअगरorm;

		mtrr_type = mtrr_type_lookup(start, end, &unअगरorm);
		अगर (mtrr_type != MTRR_TYPE_WRBACK)
			वापस _PAGE_CACHE_MODE_UC_MINUS;

		वापस _PAGE_CACHE_MODE_WB;
	पूर्ण

	वापस req_type;
पूर्ण

काष्ठा pagerange_state अणु
	अचिन्हित दीर्घ		cur_pfn;
	पूर्णांक			ram;
	पूर्णांक			not_ram;
पूर्ण;

अटल पूर्णांक
pagerange_is_ram_callback(अचिन्हित दीर्घ initial_pfn, अचिन्हित दीर्घ total_nr_pages, व्योम *arg)
अणु
	काष्ठा pagerange_state *state = arg;

	state->not_ram	|= initial_pfn > state->cur_pfn;
	state->ram	|= total_nr_pages > 0;
	state->cur_pfn	 = initial_pfn + total_nr_pages;

	वापस state->ram && state->not_ram;
पूर्ण

अटल पूर्णांक pat_pagerange_is_ram(resource_माप_प्रकार start, resource_माप_प्रकार end)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_pfn = (end + PAGE_SIZE - 1) >> PAGE_SHIFT;
	काष्ठा pagerange_state state = अणुstart_pfn, 0, 0पूर्ण;

	/*
	 * For legacy reasons, physical address range in the legacy ISA
	 * region is tracked as non-RAM. This will allow users of
	 * /dev/mem to map portions of legacy ISA region, even when
	 * some of those portions are listed(or not even listed) with
	 * dअगरferent e820 types(RAM/reserved/..)
	 */
	अगर (start_pfn < ISA_END_ADDRESS >> PAGE_SHIFT)
		start_pfn = ISA_END_ADDRESS >> PAGE_SHIFT;

	अगर (start_pfn < end_pfn) अणु
		ret = walk_प्रणाली_ram_range(start_pfn, end_pfn - start_pfn,
				&state, pagerange_is_ram_callback);
	पूर्ण

	वापस (ret > 0) ? -1 : (state.ram ? 1 : 0);
पूर्ण

/*
 * For RAM pages, we use page flags to mark the pages with appropriate type.
 * The page flags are limited to four types, WB (शेष), WC, WT and UC-.
 * WP request fails with -EINVAL, and UC माला_लो redirected to UC-.  Setting
 * a new memory type is only allowed क्रम a page mapped with the शेष WB
 * type.
 *
 * Here we करो two passes:
 * - Find the memtype of all the pages in the range, look क्रम any conflicts.
 * - In हाल of no conflicts, set the new memtype क्रम pages in the range.
 */
अटल पूर्णांक reserve_ram_pages_type(u64 start, u64 end,
				  क्रमागत page_cache_mode req_type,
				  क्रमागत page_cache_mode *new_type)
अणु
	काष्ठा page *page;
	u64 pfn;

	अगर (req_type == _PAGE_CACHE_MODE_WP) अणु
		अगर (new_type)
			*new_type = _PAGE_CACHE_MODE_UC_MINUS;
		वापस -EINVAL;
	पूर्ण

	अगर (req_type == _PAGE_CACHE_MODE_UC) अणु
		/* We करो not support strong UC */
		WARN_ON_ONCE(1);
		req_type = _PAGE_CACHE_MODE_UC_MINUS;
	पूर्ण

	क्रम (pfn = (start >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) अणु
		क्रमागत page_cache_mode type;

		page = pfn_to_page(pfn);
		type = get_page_memtype(page);
		अगर (type != _PAGE_CACHE_MODE_WB) अणु
			pr_info("x86/PAT: reserve_ram_pages_type failed [mem %#010Lx-%#010Lx], track 0x%x, req 0x%x\n",
				start, end - 1, type, req_type);
			अगर (new_type)
				*new_type = type;

			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (new_type)
		*new_type = req_type;

	क्रम (pfn = (start >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) अणु
		page = pfn_to_page(pfn);
		set_page_memtype(page, req_type);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_ram_pages_type(u64 start, u64 end)
अणु
	काष्ठा page *page;
	u64 pfn;

	क्रम (pfn = (start >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) अणु
		page = pfn_to_page(pfn);
		set_page_memtype(page, _PAGE_CACHE_MODE_WB);
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 sanitize_phys(u64 address)
अणु
	/*
	 * When changing the memtype क्रम pages containing poison allow
	 * क्रम a "decoy" भव address (bit 63 clear) passed to
	 * set_memory_X(). __pa() on a "decoy" address results in a
	 * physical address with bit 63 set.
	 *
	 * Decoy addresses are not present क्रम 32-bit builds, see
	 * set_mce_nospec().
	 */
	अगर (IS_ENABLED(CONFIG_X86_64))
		वापस address & __PHYSICAL_MASK;
	वापस address;
पूर्ण

/*
 * req_type typically has one of the:
 * - _PAGE_CACHE_MODE_WB
 * - _PAGE_CACHE_MODE_WC
 * - _PAGE_CACHE_MODE_UC_MINUS
 * - _PAGE_CACHE_MODE_UC
 * - _PAGE_CACHE_MODE_WT
 *
 * If new_type is शून्य, function will वापस an error अगर it cannot reserve the
 * region with req_type. If new_type is non-शून्य, function will वापस
 * available type in new_type in हाल of no error. In हाल of any error
 * it will वापस a negative वापस value.
 */
पूर्णांक memtype_reserve(u64 start, u64 end, क्रमागत page_cache_mode req_type,
		    क्रमागत page_cache_mode *new_type)
अणु
	काष्ठा memtype *entry_new;
	क्रमागत page_cache_mode actual_type;
	पूर्णांक is_range_ram;
	पूर्णांक err = 0;

	start = sanitize_phys(start);
	end = sanitize_phys(end);
	अगर (start >= end) अणु
		WARN(1, "%s failed: [mem %#010Lx-%#010Lx], req %s\n", __func__,
				start, end - 1, cattr_name(req_type));
		वापस -EINVAL;
	पूर्ण

	अगर (!pat_enabled()) अणु
		/* This is identical to page table setting without PAT */
		अगर (new_type)
			*new_type = req_type;
		वापस 0;
	पूर्ण

	/* Low ISA region is always mapped WB in page table. No need to track */
	अगर (x86_platक्रमm.is_untracked_pat_range(start, end)) अणु
		अगर (new_type)
			*new_type = _PAGE_CACHE_MODE_WB;
		वापस 0;
	पूर्ण

	/*
	 * Call mtrr_lookup to get the type hपूर्णांक. This is an
	 * optimization क्रम /dev/mem mmap'ers पूर्णांकo WB memory (BIOS
	 * tools and ACPI tools). Use WB request क्रम WB memory and use
	 * UC_MINUS otherwise.
	 */
	actual_type = pat_x_mtrr_type(start, end, req_type);

	अगर (new_type)
		*new_type = actual_type;

	is_range_ram = pat_pagerange_is_ram(start, end);
	अगर (is_range_ram == 1) अणु

		err = reserve_ram_pages_type(start, end, req_type, new_type);

		वापस err;
	पूर्ण अन्यथा अगर (is_range_ram < 0) अणु
		वापस -EINVAL;
	पूर्ण

	entry_new = kzalloc(माप(काष्ठा memtype), GFP_KERNEL);
	अगर (!entry_new)
		वापस -ENOMEM;

	entry_new->start = start;
	entry_new->end	 = end;
	entry_new->type	 = actual_type;

	spin_lock(&memtype_lock);

	err = memtype_check_insert(entry_new, new_type);
	अगर (err) अणु
		pr_info("x86/PAT: memtype_reserve failed [mem %#010Lx-%#010Lx], track %s, req %s\n",
			start, end - 1,
			cattr_name(entry_new->type), cattr_name(req_type));
		kमुक्त(entry_new);
		spin_unlock(&memtype_lock);

		वापस err;
	पूर्ण

	spin_unlock(&memtype_lock);

	dprपूर्णांकk("memtype_reserve added [mem %#010Lx-%#010Lx], track %s, req %s, ret %s\n",
		start, end - 1, cattr_name(entry_new->type), cattr_name(req_type),
		new_type ? cattr_name(*new_type) : "-");

	वापस err;
पूर्ण

पूर्णांक memtype_मुक्त(u64 start, u64 end)
अणु
	पूर्णांक is_range_ram;
	काष्ठा memtype *entry_old;

	अगर (!pat_enabled())
		वापस 0;

	start = sanitize_phys(start);
	end = sanitize_phys(end);

	/* Low ISA region is always mapped WB. No need to track */
	अगर (x86_platक्रमm.is_untracked_pat_range(start, end))
		वापस 0;

	is_range_ram = pat_pagerange_is_ram(start, end);
	अगर (is_range_ram == 1)
		वापस मुक्त_ram_pages_type(start, end);
	अगर (is_range_ram < 0)
		वापस -EINVAL;

	spin_lock(&memtype_lock);
	entry_old = memtype_erase(start, end);
	spin_unlock(&memtype_lock);

	अगर (IS_ERR(entry_old)) अणु
		pr_info("x86/PAT: %s:%d freeing invalid memtype [mem %#010Lx-%#010Lx]\n",
			current->comm, current->pid, start, end - 1);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(entry_old);

	dprपूर्णांकk("memtype_free request [mem %#010Lx-%#010Lx]\n", start, end - 1);

	वापस 0;
पूर्ण


/**
 * lookup_memtype - Looks up the memory type क्रम a physical address
 * @paddr: physical address of which memory type needs to be looked up
 *
 * Only to be called when PAT is enabled
 *
 * Returns _PAGE_CACHE_MODE_WB, _PAGE_CACHE_MODE_WC, _PAGE_CACHE_MODE_UC_MINUS
 * or _PAGE_CACHE_MODE_WT.
 */
अटल क्रमागत page_cache_mode lookup_memtype(u64 paddr)
अणु
	क्रमागत page_cache_mode rettype = _PAGE_CACHE_MODE_WB;
	काष्ठा memtype *entry;

	अगर (x86_platक्रमm.is_untracked_pat_range(paddr, paddr + PAGE_SIZE))
		वापस rettype;

	अगर (pat_pagerange_is_ram(paddr, paddr + PAGE_SIZE)) अणु
		काष्ठा page *page;

		page = pfn_to_page(paddr >> PAGE_SHIFT);
		वापस get_page_memtype(page);
	पूर्ण

	spin_lock(&memtype_lock);

	entry = memtype_lookup(paddr);
	अगर (entry != शून्य)
		rettype = entry->type;
	अन्यथा
		rettype = _PAGE_CACHE_MODE_UC_MINUS;

	spin_unlock(&memtype_lock);

	वापस rettype;
पूर्ण

/**
 * pat_pfn_immune_to_uc_mtrr - Check whether the PAT memory type
 * of @pfn cannot be overridden by UC MTRR memory type.
 *
 * Only to be called when PAT is enabled.
 *
 * Returns true, अगर the PAT memory type of @pfn is UC, UC-, or WC.
 * Returns false in other हालs.
 */
bool pat_pfn_immune_to_uc_mtrr(अचिन्हित दीर्घ pfn)
अणु
	क्रमागत page_cache_mode cm = lookup_memtype(PFN_PHYS(pfn));

	वापस cm == _PAGE_CACHE_MODE_UC ||
	       cm == _PAGE_CACHE_MODE_UC_MINUS ||
	       cm == _PAGE_CACHE_MODE_WC;
पूर्ण
EXPORT_SYMBOL_GPL(pat_pfn_immune_to_uc_mtrr);

/**
 * memtype_reserve_io - Request a memory type mapping क्रम a region of memory
 * @start: start (physical address) of the region
 * @end: end (physical address) of the region
 * @type: A poपूर्णांकer to memtype, with requested type. On success, requested
 * or any other compatible type that was available क्रम the region is वापसed
 *
 * On success, वापसs 0
 * On failure, वापसs non-zero
 */
पूर्णांक memtype_reserve_io(resource_माप_प्रकार start, resource_माप_प्रकार end,
			क्रमागत page_cache_mode *type)
अणु
	resource_माप_प्रकार size = end - start;
	क्रमागत page_cache_mode req_type = *type;
	क्रमागत page_cache_mode new_type;
	पूर्णांक ret;

	WARN_ON_ONCE(iomem_map_sanity_check(start, size));

	ret = memtype_reserve(start, end, req_type, &new_type);
	अगर (ret)
		जाओ out_err;

	अगर (!is_new_memtype_allowed(start, size, req_type, new_type))
		जाओ out_मुक्त;

	अगर (memtype_kernel_map_sync(start, size, new_type) < 0)
		जाओ out_मुक्त;

	*type = new_type;
	वापस 0;

out_मुक्त:
	memtype_मुक्त(start, end);
	ret = -EBUSY;
out_err:
	वापस ret;
पूर्ण

/**
 * memtype_मुक्त_io - Release a memory type mapping क्रम a region of memory
 * @start: start (physical address) of the region
 * @end: end (physical address) of the region
 */
व्योम memtype_मुक्त_io(resource_माप_प्रकार start, resource_माप_प्रकार end)
अणु
	memtype_मुक्त(start, end);
पूर्ण

#अगर_घोषित CONFIG_X86_PAT
पूर्णांक arch_io_reserve_memtype_wc(resource_माप_प्रकार start, resource_माप_प्रकार size)
अणु
	क्रमागत page_cache_mode type = _PAGE_CACHE_MODE_WC;

	वापस memtype_reserve_io(start, start + size, &type);
पूर्ण
EXPORT_SYMBOL(arch_io_reserve_memtype_wc);

व्योम arch_io_मुक्त_memtype_wc(resource_माप_प्रकार start, resource_माप_प्रकार size)
अणु
	memtype_मुक्त_io(start, start + size);
पूर्ण
EXPORT_SYMBOL(arch_io_मुक्त_memtype_wc);
#पूर्ण_अगर

pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				अचिन्हित दीर्घ size, pgprot_t vma_prot)
अणु
	अगर (!phys_mem_access_encrypted(pfn << PAGE_SHIFT, size))
		vma_prot = pgprot_decrypted(vma_prot);

	वापस vma_prot;
पूर्ण

#अगर_घोषित CONFIG_STRICT_DEVMEM
/* This check is करोne in drivers/अक्षर/mem.c in हाल of STRICT_DEVMEM */
अटल अंतरभूत पूर्णांक range_is_allowed(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
	वापस 1;
पूर्ण
#अन्यथा
/* This check is needed to aव्योम cache aliasing when PAT is enabled */
अटल अंतरभूत पूर्णांक range_is_allowed(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
	u64 from = ((u64)pfn) << PAGE_SHIFT;
	u64 to = from + size;
	u64 cursor = from;

	अगर (!pat_enabled())
		वापस 1;

	जबतक (cursor < to) अणु
		अगर (!devmem_is_allowed(pfn))
			वापस 0;
		cursor += PAGE_SIZE;
		pfn++;
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_STRICT_DEVMEM */

पूर्णांक phys_mem_access_prot_allowed(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				अचिन्हित दीर्घ size, pgprot_t *vma_prot)
अणु
	क्रमागत page_cache_mode pcm = _PAGE_CACHE_MODE_WB;

	अगर (!range_is_allowed(pfn, size))
		वापस 0;

	अगर (file->f_flags & O_DSYNC)
		pcm = _PAGE_CACHE_MODE_UC_MINUS;

	*vma_prot = __pgprot((pgprot_val(*vma_prot) & ~_PAGE_CACHE_MASK) |
			     cachemode2protval(pcm));
	वापस 1;
पूर्ण

/*
 * Change the memory type क्रम the physical address range in kernel identity
 * mapping space अगर that range is a part of identity map.
 */
पूर्णांक memtype_kernel_map_sync(u64 base, अचिन्हित दीर्घ size,
			    क्रमागत page_cache_mode pcm)
अणु
	अचिन्हित दीर्घ id_sz;

	अगर (base > __pa(high_memory-1))
		वापस 0;

	/*
	 * Some areas in the middle of the kernel identity range
	 * are not mapped, क्रम example the PCI space.
	 */
	अगर (!page_is_ram(base >> PAGE_SHIFT))
		वापस 0;

	id_sz = (__pa(high_memory-1) <= base + size) ?
				__pa(high_memory) - base : size;

	अगर (ioremap_change_attr((अचिन्हित दीर्घ)__va(base), id_sz, pcm) < 0) अणु
		pr_info("x86/PAT: %s:%d ioremap_change_attr failed %s for [mem %#010Lx-%#010Lx]\n",
			current->comm, current->pid,
			cattr_name(pcm),
			base, (अचिन्हित दीर्घ दीर्घ)(base + size-1));
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Internal पूर्णांकerface to reserve a range of physical memory with prot.
 * Reserved non RAM regions only and after successful memtype_reserve,
 * this func also keeps identity mapping (अगर any) in sync with this new prot.
 */
अटल पूर्णांक reserve_pfn_range(u64 paddr, अचिन्हित दीर्घ size, pgprot_t *vma_prot,
				पूर्णांक strict_prot)
अणु
	पूर्णांक is_ram = 0;
	पूर्णांक ret;
	क्रमागत page_cache_mode want_pcm = pgprot2cachemode(*vma_prot);
	क्रमागत page_cache_mode pcm = want_pcm;

	is_ram = pat_pagerange_is_ram(paddr, paddr + size);

	/*
	 * reserve_pfn_range() क्रम RAM pages. We करो not refcount to keep
	 * track of number of mappings of RAM pages. We can निश्चित that
	 * the type requested matches the type of first page in the range.
	 */
	अगर (is_ram) अणु
		अगर (!pat_enabled())
			वापस 0;

		pcm = lookup_memtype(paddr);
		अगर (want_pcm != pcm) अणु
			pr_warn("x86/PAT: %s:%d map pfn RAM range req %s for [mem %#010Lx-%#010Lx], got %s\n",
				current->comm, current->pid,
				cattr_name(want_pcm),
				(अचिन्हित दीर्घ दीर्घ)paddr,
				(अचिन्हित दीर्घ दीर्घ)(paddr + size - 1),
				cattr_name(pcm));
			*vma_prot = __pgprot((pgprot_val(*vma_prot) &
					     (~_PAGE_CACHE_MASK)) |
					     cachemode2protval(pcm));
		पूर्ण
		वापस 0;
	पूर्ण

	ret = memtype_reserve(paddr, paddr + size, want_pcm, &pcm);
	अगर (ret)
		वापस ret;

	अगर (pcm != want_pcm) अणु
		अगर (strict_prot ||
		    !is_new_memtype_allowed(paddr, size, want_pcm, pcm)) अणु
			memtype_मुक्त(paddr, paddr + size);
			pr_err("x86/PAT: %s:%d map pfn expected mapping type %s for [mem %#010Lx-%#010Lx], got %s\n",
			       current->comm, current->pid,
			       cattr_name(want_pcm),
			       (अचिन्हित दीर्घ दीर्घ)paddr,
			       (अचिन्हित दीर्घ दीर्घ)(paddr + size - 1),
			       cattr_name(pcm));
			वापस -EINVAL;
		पूर्ण
		/*
		 * We allow वापसing dअगरferent type than the one requested in
		 * non strict हाल.
		 */
		*vma_prot = __pgprot((pgprot_val(*vma_prot) &
				      (~_PAGE_CACHE_MASK)) |
				     cachemode2protval(pcm));
	पूर्ण

	अगर (memtype_kernel_map_sync(paddr, size, pcm) < 0) अणु
		memtype_मुक्त(paddr, paddr + size);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Internal पूर्णांकerface to मुक्त a range of physical memory.
 * Frees non RAM regions only.
 */
अटल व्योम मुक्त_pfn_range(u64 paddr, अचिन्हित दीर्घ size)
अणु
	पूर्णांक is_ram;

	is_ram = pat_pagerange_is_ram(paddr, paddr + size);
	अगर (is_ram == 0)
		memtype_मुक्त(paddr, paddr + size);
पूर्ण

/*
 * track_pfn_copy is called when vma that is covering the pfnmap माला_लो
 * copied through copy_page_range().
 *
 * If the vma has a linear pfn mapping क्रम the entire range, we get the prot
 * from pte and reserve the entire vma range with single reserve_pfn_range call.
 */
पूर्णांक track_pfn_copy(काष्ठा vm_area_काष्ठा *vma)
अणु
	resource_माप_प्रकार paddr;
	अचिन्हित दीर्घ prot;
	अचिन्हित दीर्घ vma_size = vma->vm_end - vma->vm_start;
	pgprot_t pgprot;

	अगर (vma->vm_flags & VM_PAT) अणु
		/*
		 * reserve the whole chunk covered by vma. We need the
		 * starting address and protection from pte.
		 */
		अगर (follow_phys(vma, vma->vm_start, 0, &prot, &paddr)) अणु
			WARN_ON_ONCE(1);
			वापस -EINVAL;
		पूर्ण
		pgprot = __pgprot(prot);
		वापस reserve_pfn_range(paddr, vma_size, &pgprot, 1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * prot is passed in as a parameter क्रम the new mapping. If the vma has
 * a linear pfn mapping क्रम the entire range, or no vma is provided,
 * reserve the entire pfn + size range with single reserve_pfn_range
 * call.
 */
पूर्णांक track_pfn_remap(काष्ठा vm_area_काष्ठा *vma, pgprot_t *prot,
		    अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	resource_माप_प्रकार paddr = (resource_माप_प्रकार)pfn << PAGE_SHIFT;
	क्रमागत page_cache_mode pcm;

	/* reserve the whole chunk starting from paddr */
	अगर (!vma || (addr == vma->vm_start
				&& size == (vma->vm_end - vma->vm_start))) अणु
		पूर्णांक ret;

		ret = reserve_pfn_range(paddr, size, prot, 0);
		अगर (ret == 0 && vma)
			vma->vm_flags |= VM_PAT;
		वापस ret;
	पूर्ण

	अगर (!pat_enabled())
		वापस 0;

	/*
	 * For anything smaller than the vma size we set prot based on the
	 * lookup.
	 */
	pcm = lookup_memtype(paddr);

	/* Check memtype क्रम the reमुख्यing pages */
	जबतक (size > PAGE_SIZE) अणु
		size -= PAGE_SIZE;
		paddr += PAGE_SIZE;
		अगर (pcm != lookup_memtype(paddr))
			वापस -EINVAL;
	पूर्ण

	*prot = __pgprot((pgprot_val(*prot) & (~_PAGE_CACHE_MASK)) |
			 cachemode2protval(pcm));

	वापस 0;
पूर्ण

व्योम track_pfn_insert(काष्ठा vm_area_काष्ठा *vma, pgprot_t *prot, pfn_t pfn)
अणु
	क्रमागत page_cache_mode pcm;

	अगर (!pat_enabled())
		वापस;

	/* Set prot based on lookup */
	pcm = lookup_memtype(pfn_t_to_phys(pfn));
	*prot = __pgprot((pgprot_val(*prot) & (~_PAGE_CACHE_MASK)) |
			 cachemode2protval(pcm));
पूर्ण

/*
 * untrack_pfn is called जबतक unmapping a pfnmap क्रम a region.
 * untrack can be called क्रम a specअगरic region indicated by pfn and size or
 * can be क्रम the entire vma (in which हाल pfn, size are zero).
 */
व्योम untrack_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ pfn,
		 अचिन्हित दीर्घ size)
अणु
	resource_माप_प्रकार paddr;
	अचिन्हित दीर्घ prot;

	अगर (vma && !(vma->vm_flags & VM_PAT))
		वापस;

	/* मुक्त the chunk starting from pfn or the whole chunk */
	paddr = (resource_माप_प्रकार)pfn << PAGE_SHIFT;
	अगर (!paddr && !size) अणु
		अगर (follow_phys(vma, vma->vm_start, 0, &prot, &paddr)) अणु
			WARN_ON_ONCE(1);
			वापस;
		पूर्ण

		size = vma->vm_end - vma->vm_start;
	पूर्ण
	मुक्त_pfn_range(paddr, size);
	अगर (vma)
		vma->vm_flags &= ~VM_PAT;
पूर्ण

/*
 * untrack_pfn_moved is called, जबतक mremapping a pfnmap क्रम a new region,
 * with the old vma after its pfnmap page table has been हटाओd.  The new
 * vma has a new pfnmap to the same pfn & cache type with VM_PAT set.
 */
व्योम untrack_pfn_moved(काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_flags &= ~VM_PAT;
पूर्ण

pgprot_t pgprot_ग_लिखोcombine(pgprot_t prot)
अणु
	वापस __pgprot(pgprot_val(prot) |
				cachemode2protval(_PAGE_CACHE_MODE_WC));
पूर्ण
EXPORT_SYMBOL_GPL(pgprot_ग_लिखोcombine);

pgprot_t pgprot_ग_लिखोthrough(pgprot_t prot)
अणु
	वापस __pgprot(pgprot_val(prot) |
				cachemode2protval(_PAGE_CACHE_MODE_WT));
पूर्ण
EXPORT_SYMBOL_GPL(pgprot_ग_लिखोthrough);

#अगर defined(CONFIG_DEBUG_FS) && defined(CONFIG_X86_PAT)

/*
 * We are allocating a temporary prपूर्णांकout-entry to be passed
 * between seq_start()/next() and seq_show():
 */
अटल काष्ठा memtype *memtype_get_idx(loff_t pos)
अणु
	काष्ठा memtype *entry_prपूर्णांक;
	पूर्णांक ret;

	entry_prपूर्णांक  = kzalloc(माप(काष्ठा memtype), GFP_KERNEL);
	अगर (!entry_prपूर्णांक)
		वापस शून्य;

	spin_lock(&memtype_lock);
	ret = memtype_copy_nth_element(entry_prपूर्णांक, pos);
	spin_unlock(&memtype_lock);

	/* Free it on error: */
	अगर (ret) अणु
		kमुक्त(entry_prपूर्णांक);
		वापस शून्य;
	पूर्ण

	वापस entry_prपूर्णांक;
पूर्ण

अटल व्योम *memtype_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	अगर (*pos == 0) अणु
		++*pos;
		seq_माला_दो(seq, "PAT memtype list:\n");
	पूर्ण

	वापस memtype_get_idx(*pos);
पूर्ण

अटल व्योम *memtype_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	kमुक्त(v);
	++*pos;
	वापस memtype_get_idx(*pos);
पूर्ण

अटल व्योम memtype_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	kमुक्त(v);
पूर्ण

अटल पूर्णांक memtype_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा memtype *entry_prपूर्णांक = (काष्ठा memtype *)v;

	seq_म_लिखो(seq, "PAT: [mem 0x%016Lx-0x%016Lx] %s\n",
			entry_prपूर्णांक->start,
			entry_prपूर्णांक->end,
			cattr_name(entry_prपूर्णांक->type));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations memtype_seq_ops = अणु
	.start = memtype_seq_start,
	.next  = memtype_seq_next,
	.stop  = memtype_seq_stop,
	.show  = memtype_seq_show,
पूर्ण;

अटल पूर्णांक memtype_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &memtype_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations memtype_fops = अणु
	.खोलो    = memtype_seq_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release,
पूर्ण;

अटल पूर्णांक __init pat_memtype_list_init(व्योम)
अणु
	अगर (pat_enabled()) अणु
		debugfs_create_file("pat_memtype_list", S_IRUSR,
				    arch_debugfs_dir, शून्य, &memtype_fops);
	पूर्ण
	वापस 0;
पूर्ण
late_initcall(pat_memtype_list_init);

#पूर्ण_अगर /* CONFIG_DEBUG_FS && CONFIG_X86_PAT */
