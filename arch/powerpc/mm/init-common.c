<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Dave Engebretsen <engebret@us.ibm.com>
 *      Rework क्रम PPC64 port.
 */

#अघोषित DEBUG

#समावेश <linux/माला.स>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/kup.h>

phys_addr_t memstart_addr __ro_after_init = (phys_addr_t)~0ull;
EXPORT_SYMBOL_GPL(memstart_addr);
phys_addr_t kernstart_addr __ro_after_init;
EXPORT_SYMBOL_GPL(kernstart_addr);
अचिन्हित दीर्घ kernstart_virt_addr __ro_after_init = KERNELBASE;
EXPORT_SYMBOL_GPL(kernstart_virt_addr);

bool disable_kuep = !IS_ENABLED(CONFIG_PPC_KUEP);
bool disable_kuap = !IS_ENABLED(CONFIG_PPC_KUAP);

अटल पूर्णांक __init parse_nosmep(अक्षर *p)
अणु
	disable_kuep = true;
	pr_warn("Disabling Kernel Userspace Execution Prevention\n");
	वापस 0;
पूर्ण
early_param("nosmep", parse_nosmep);

अटल पूर्णांक __init parse_nosmap(अक्षर *p)
अणु
	disable_kuap = true;
	pr_warn("Disabling Kernel Userspace Access Protection\n");
	वापस 0;
पूर्ण
early_param("nosmap", parse_nosmap);

#घोषणा CTOR(shअगरt) अटल व्योम ctor_##shअगरt(व्योम *addr) \
अणु							\
	स_रखो(addr, 0, माप(व्योम *) << (shअगरt));	\
पूर्ण

CTOR(0); CTOR(1); CTOR(2); CTOR(3); CTOR(4); CTOR(5); CTOR(6); CTOR(7);
CTOR(8); CTOR(9); CTOR(10); CTOR(11); CTOR(12); CTOR(13); CTOR(14); CTOR(15);

अटल अंतरभूत व्योम (*ctor(पूर्णांक shअगरt))(व्योम *)
अणु
	BUILD_BUG_ON(MAX_PGTABLE_INDEX_SIZE != 15);

	चयन (shअगरt) अणु
	हाल 0: वापस ctor_0;
	हाल 1: वापस ctor_1;
	हाल 2: वापस ctor_2;
	हाल 3: वापस ctor_3;
	हाल 4: वापस ctor_4;
	हाल 5: वापस ctor_5;
	हाल 6: वापस ctor_6;
	हाल 7: वापस ctor_7;
	हाल 8: वापस ctor_8;
	हाल 9: वापस ctor_9;
	हाल 10: वापस ctor_10;
	हाल 11: वापस ctor_11;
	हाल 12: वापस ctor_12;
	हाल 13: वापस ctor_13;
	हाल 14: वापस ctor_14;
	हाल 15: वापस ctor_15;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा kmem_cache *pgtable_cache[MAX_PGTABLE_INDEX_SIZE + 1];
EXPORT_SYMBOL_GPL(pgtable_cache);	/* used by kvm_hv module */

/*
 * Create a kmem_cache() क्रम pagetables.  This is not used क्रम PTE
 * pages - they're linked to काष्ठा page, come from the normal मुक्त
 * pages pool and have a dअगरferent entry size (see real_pte_t) to
 * everything अन्यथा.  Caches created by this function are used क्रम all
 * the higher level pagetables, and क्रम hugepage pagetables.
 */
व्योम pgtable_cache_add(अचिन्हित पूर्णांक shअगरt)
अणु
	अक्षर *name;
	अचिन्हित दीर्घ table_size = माप(व्योम *) << shअगरt;
	अचिन्हित दीर्घ align = table_size;

	/* When batching pgtable poपूर्णांकers क्रम RCU मुक्तing, we store
	 * the index size in the low bits.  Table alignment must be
	 * big enough to fit it.
	 *
	 * Likewise, hugeapge pagetable poपूर्णांकers contain a (dअगरferent)
	 * shअगरt value in the low bits.  All tables must be aligned so
	 * as to leave enough 0 bits in the address to contain it. */
	अचिन्हित दीर्घ minalign = max(MAX_PGTABLE_INDEX_SIZE + 1,
				     HUGEPD_SHIFT_MASK + 1);
	काष्ठा kmem_cache *new;

	/* It would be nice अगर this was a BUILD_BUG_ON(), but at the
	 * moment, gcc करोesn't seem to recognize is_घातer_of_2 as a
	 * स्थिरant expression, so so much क्रम that. */
	BUG_ON(!is_घातer_of_2(minalign));
	BUG_ON(shअगरt > MAX_PGTABLE_INDEX_SIZE);

	अगर (PGT_CACHE(shअगरt))
		वापस; /* Alपढ़ोy have a cache of this size */

	align = max_t(अचिन्हित दीर्घ, align, minalign);
	name = kaप्र_लिखो(GFP_KERNEL, "pgtable-2^%d", shअगरt);
	new = kmem_cache_create(name, table_size, align, 0, ctor(shअगरt));
	अगर (!new)
		panic("Could not allocate pgtable cache for order %d", shअगरt);

	kमुक्त(name);
	pgtable_cache[shअगरt] = new;

	pr_debug("Allocated pgtable cache for order %d\n", shअगरt);
पूर्ण
EXPORT_SYMBOL_GPL(pgtable_cache_add);	/* used by kvm_hv module */

व्योम pgtable_cache_init(व्योम)
अणु
	pgtable_cache_add(PGD_INDEX_SIZE);

	अगर (PMD_CACHE_INDEX)
		pgtable_cache_add(PMD_CACHE_INDEX);
	/*
	 * In all current configs, when the PUD index exists it's the
	 * same size as either the pgd or pmd index except with THP enabled
	 * on book3s 64
	 */
	अगर (PUD_CACHE_INDEX)
		pgtable_cache_add(PUD_CACHE_INDEX);
पूर्ण
