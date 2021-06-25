<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PERCPU_H
#घोषणा __LINUX_PERCPU_H

#समावेश <linux/mmdebug.h>
#समावेश <linux/preempt.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pfn.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/percpu.h>

/* enough to cover all DEFINE_PER_CPUs in modules */
#अगर_घोषित CONFIG_MODULES
#घोषणा PERCPU_MODULE_RESERVE		(8 << 10)
#अन्यथा
#घोषणा PERCPU_MODULE_RESERVE		0
#पूर्ण_अगर

/* minimum unit size, also is the maximum supported allocation size */
#घोषणा PCPU_MIN_UNIT_SIZE		PFN_ALIGN(32 << 10)

/* minimum allocation size and shअगरt in bytes */
#घोषणा PCPU_MIN_ALLOC_SHIFT		2
#घोषणा PCPU_MIN_ALLOC_SIZE		(1 << PCPU_MIN_ALLOC_SHIFT)

/*
 * The PCPU_BITMAP_BLOCK_SIZE must be the same size as PAGE_SIZE as the
 * updating of hपूर्णांकs is used to manage the nr_empty_pop_pages in both
 * the chunk and globally.
 */
#घोषणा PCPU_BITMAP_BLOCK_SIZE		PAGE_SIZE
#घोषणा PCPU_BITMAP_BLOCK_BITS		(PCPU_BITMAP_BLOCK_SIZE >>	\
					 PCPU_MIN_ALLOC_SHIFT)

/*
 * Percpu allocator can serve percpu allocations beक्रमe slab is
 * initialized which allows slab to depend on the percpu allocator.
 * The following two parameters decide how much resource to
 * pपुनः_स्मृतिate क्रम this.  Keep PERCPU_DYNAMIC_RESERVE equal to or
 * larger than PERCPU_DYNAMIC_EARLY_SIZE.
 */
#घोषणा PERCPU_DYNAMIC_EARLY_SLOTS	128
#घोषणा PERCPU_DYNAMIC_EARLY_SIZE	(12 << 10)

/*
 * PERCPU_DYNAMIC_RESERVE indicates the amount of मुक्त area to piggy
 * back on the first chunk क्रम dynamic percpu allocation अगर arch is
 * manually allocating and mapping it क्रम faster access (as a part of
 * large page mapping क्रम example).
 *
 * The following values give between one and two pages of मुक्त space
 * after typical minimal boot (2-way SMP, single disk and NIC) with
 * both defconfig and a distro config on x86_64 and 32.  More
 * पूर्णांकelligent way to determine this would be nice.
 */
#अगर BITS_PER_LONG > 32
#घोषणा PERCPU_DYNAMIC_RESERVE		(28 << 10)
#अन्यथा
#घोषणा PERCPU_DYNAMIC_RESERVE		(20 << 10)
#पूर्ण_अगर

बाह्य व्योम *pcpu_base_addr;
बाह्य स्थिर अचिन्हित दीर्घ *pcpu_unit_offsets;

काष्ठा pcpu_group_info अणु
	पूर्णांक			nr_units;	/* aligned # of units */
	अचिन्हित दीर्घ		base_offset;	/* base address offset */
	अचिन्हित पूर्णांक		*cpu_map;	/* unit->cpu map, empty
						 * entries contain NR_CPUS */
पूर्ण;

काष्ठा pcpu_alloc_info अणु
	माप_प्रकार			अटल_size;
	माप_प्रकार			reserved_size;
	माप_प्रकार			dyn_size;
	माप_प्रकार			unit_size;
	माप_प्रकार			atom_size;
	माप_प्रकार			alloc_size;
	माप_प्रकार			__ai_size;	/* पूर्णांकernal, करोn't use */
	पूर्णांक			nr_groups;	/* 0 अगर grouping unnecessary */
	काष्ठा pcpu_group_info	groups[];
पूर्ण;

क्रमागत pcpu_fc अणु
	PCPU_FC_AUTO,
	PCPU_FC_EMBED,
	PCPU_FC_PAGE,

	PCPU_FC_NR,
पूर्ण;
बाह्य स्थिर अक्षर * स्थिर pcpu_fc_names[PCPU_FC_NR];

बाह्य क्रमागत pcpu_fc pcpu_chosen_fc;

प्रकार व्योम * (*pcpu_fc_alloc_fn_t)(अचिन्हित पूर्णांक cpu, माप_प्रकार size,
				     माप_प्रकार align);
प्रकार व्योम (*pcpu_fc_मुक्त_fn_t)(व्योम *ptr, माप_प्रकार size);
प्रकार व्योम (*pcpu_fc_populate_pte_fn_t)(अचिन्हित दीर्घ addr);
प्रकार पूर्णांक (pcpu_fc_cpu_distance_fn_t)(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to);

बाह्य काष्ठा pcpu_alloc_info * __init pcpu_alloc_alloc_info(पूर्णांक nr_groups,
							     पूर्णांक nr_units);
बाह्य व्योम __init pcpu_मुक्त_alloc_info(काष्ठा pcpu_alloc_info *ai);

बाह्य व्योम __init pcpu_setup_first_chunk(स्थिर काष्ठा pcpu_alloc_info *ai,
					 व्योम *base_addr);

#अगर_घोषित CONFIG_NEED_PER_CPU_EMBED_FIRST_CHUNK
बाह्य पूर्णांक __init pcpu_embed_first_chunk(माप_प्रकार reserved_size, माप_प्रकार dyn_size,
				माप_प्रकार atom_size,
				pcpu_fc_cpu_distance_fn_t cpu_distance_fn,
				pcpu_fc_alloc_fn_t alloc_fn,
				pcpu_fc_मुक्त_fn_t मुक्त_fn);
#पूर्ण_अगर

#अगर_घोषित CONFIG_NEED_PER_CPU_PAGE_FIRST_CHUNK
बाह्य पूर्णांक __init pcpu_page_first_chunk(माप_प्रकार reserved_size,
				pcpu_fc_alloc_fn_t alloc_fn,
				pcpu_fc_मुक्त_fn_t मुक्त_fn,
				pcpu_fc_populate_pte_fn_t populate_pte_fn);
#पूर्ण_अगर

बाह्य व्योम __percpu *__alloc_reserved_percpu(माप_प्रकार size, माप_प्रकार align);
बाह्य bool __is_kernel_percpu_address(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *can_addr);
बाह्य bool is_kernel_percpu_address(अचिन्हित दीर्घ addr);

#अगर !defined(CONFIG_SMP) || !defined(CONFIG_HAVE_SETUP_PER_CPU_AREA)
बाह्य व्योम __init setup_per_cpu_areas(व्योम);
#पूर्ण_अगर

बाह्य व्योम __percpu *__alloc_percpu_gfp(माप_प्रकार size, माप_प्रकार align, gfp_t gfp);
बाह्य व्योम __percpu *__alloc_percpu(माप_प्रकार size, माप_प्रकार align);
बाह्य व्योम मुक्त_percpu(व्योम __percpu *__pdata);
बाह्य phys_addr_t per_cpu_ptr_to_phys(व्योम *addr);

#घोषणा alloc_percpu_gfp(type, gfp)					\
	(typeof(type) __percpu *)__alloc_percpu_gfp(माप(type),	\
						__alignof__(type), gfp)
#घोषणा alloc_percpu(type)						\
	(typeof(type) __percpu *)__alloc_percpu(माप(type),		\
						__alignof__(type))

बाह्य अचिन्हित दीर्घ pcpu_nr_pages(व्योम);

#पूर्ण_अगर /* __LINUX_PERCPU_H */
