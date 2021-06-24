<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Clang Control Flow Integrity (CFI) error and slowpath handling.
 *
 * Copyright (C) 2021 Google LLC
 */

#समावेश <linux/hardirq.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/set_memory.h>

/* Compiler-defined handler names */
#अगर_घोषित CONFIG_CFI_PERMISSIVE
#घोषणा cfi_failure_handler	__ubsan_handle_cfi_check_fail
#अन्यथा
#घोषणा cfi_failure_handler	__ubsan_handle_cfi_check_fail_पात
#पूर्ण_अगर

अटल अंतरभूत व्योम handle_cfi_failure(व्योम *ptr)
अणु
	अगर (IS_ENABLED(CONFIG_CFI_PERMISSIVE))
		WARN_RATELIMIT(1, "CFI failure (target: %pS):\n", ptr);
	अन्यथा
		panic("CFI failure (target: %pS)\n", ptr);
पूर्ण

#अगर_घोषित CONFIG_MODULES
#अगर_घोषित CONFIG_CFI_CLANG_SHADOW
/*
 * Index type. A 16-bit index can address at most (2^16)-2 pages (taking
 * पूर्णांकo account SHADOW_INVALID), i.e. ~256M with 4k pages.
 */
प्रकार u16 shaकरोw_t;
#घोषणा SHADOW_INVALID		((shaकरोw_t)~0UL)

काष्ठा cfi_shaकरोw अणु
	/* Page index क्रम the beginning of the shaकरोw */
	अचिन्हित दीर्घ base;
	/* An array of __cfi_check locations (as indices to the shaकरोw) */
	shaकरोw_t shaकरोw[1];
पूर्ण __packed;

/*
 * The shaकरोw covers ~128M from the beginning of the module region. If
 * the region is larger, we fall back to __module_address क्रम the rest.
 */
#घोषणा __SHADOW_RANGE		(_UL(SZ_128M) >> PAGE_SHIFT)

/* The in-memory size of काष्ठा cfi_shaकरोw, always at least one page */
#घोषणा __SHADOW_PAGES		((__SHADOW_RANGE * माप(shaकरोw_t)) >> PAGE_SHIFT)
#घोषणा SHADOW_PAGES		max(1UL, __SHADOW_PAGES)
#घोषणा SHADOW_SIZE		(SHADOW_PAGES << PAGE_SHIFT)

/* The actual size of the shaकरोw array, minus metadata */
#घोषणा SHADOW_ARR_SIZE		(SHADOW_SIZE - दुरत्व(काष्ठा cfi_shaकरोw, shaकरोw))
#घोषणा SHADOW_ARR_SLOTS	(SHADOW_ARR_SIZE / माप(shaकरोw_t))

अटल DEFINE_MUTEX(shaकरोw_update_lock);
अटल काष्ठा cfi_shaकरोw __rcu *cfi_shaकरोw __पढ़ो_mostly;

/* Returns the index in the shaकरोw क्रम the given address */
अटल अंतरभूत पूर्णांक ptr_to_shaकरोw(स्थिर काष्ठा cfi_shaकरोw *s, अचिन्हित दीर्घ ptr)
अणु
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ page = ptr >> PAGE_SHIFT;

	अगर (unlikely(page < s->base))
		वापस -1; /* Outside of module area */

	index = page - s->base;

	अगर (index >= SHADOW_ARR_SLOTS)
		वापस -1; /* Cannot be addressed with shaकरोw */

	वापस (पूर्णांक)index;
पूर्ण

/* Returns the page address क्रम an index in the shaकरोw */
अटल अंतरभूत अचिन्हित दीर्घ shaकरोw_to_ptr(स्थिर काष्ठा cfi_shaकरोw *s,
	पूर्णांक index)
अणु
	अगर (unlikely(index < 0 || index >= SHADOW_ARR_SLOTS))
		वापस 0;

	वापस (s->base + index) << PAGE_SHIFT;
पूर्ण

/* Returns the __cfi_check function address क्रम the given shaकरोw location */
अटल अंतरभूत अचिन्हित दीर्घ shaकरोw_to_check_fn(स्थिर काष्ठा cfi_shaकरोw *s,
	पूर्णांक index)
अणु
	अगर (unlikely(index < 0 || index >= SHADOW_ARR_SLOTS))
		वापस 0;

	अगर (unlikely(s->shaकरोw[index] == SHADOW_INVALID))
		वापस 0;

	/* __cfi_check is always page aligned */
	वापस (s->base + s->shaकरोw[index]) << PAGE_SHIFT;
पूर्ण

अटल व्योम prepare_next_shaकरोw(स्थिर काष्ठा cfi_shaकरोw __rcu *prev,
		काष्ठा cfi_shaकरोw *next)
अणु
	पूर्णांक i, index, check;

	/* Mark everything invalid */
	स_रखो(next->shaकरोw, 0xFF, SHADOW_ARR_SIZE);

	अगर (!prev)
		वापस; /* No previous shaकरोw */

	/* If the base address didn't change, an update is not needed */
	अगर (prev->base == next->base) अणु
		स_नकल(next->shaकरोw, prev->shaकरोw, SHADOW_ARR_SIZE);
		वापस;
	पूर्ण

	/* Convert the previous shaकरोw to the new address range */
	क्रम (i = 0; i < SHADOW_ARR_SLOTS; ++i) अणु
		अगर (prev->shaकरोw[i] == SHADOW_INVALID)
			जारी;

		index = ptr_to_shaकरोw(next, shaकरोw_to_ptr(prev, i));
		अगर (index < 0)
			जारी;

		check = ptr_to_shaकरोw(next,
				shaकरोw_to_check_fn(prev, prev->shaकरोw[i]));
		अगर (check < 0)
			जारी;

		next->shaकरोw[index] = (shaकरोw_t)check;
	पूर्ण
पूर्ण

अटल व्योम add_module_to_shaकरोw(काष्ठा cfi_shaकरोw *s, काष्ठा module *mod,
			अचिन्हित दीर्घ min_addr, अचिन्हित दीर्घ max_addr)
अणु
	पूर्णांक check_index;
	अचिन्हित दीर्घ check = (अचिन्हित दीर्घ)mod->cfi_check;
	अचिन्हित दीर्घ ptr;

	अगर (unlikely(!PAGE_ALIGNED(check))) अणु
		pr_warn("cfi: not using shadow for module %s\n", mod->name);
		वापस;
	पूर्ण

	check_index = ptr_to_shaकरोw(s, check);
	अगर (check_index < 0)
		वापस; /* Module not addressable with shaकरोw */

	/* For each page, store the check function index in the shaकरोw */
	क्रम (ptr = min_addr; ptr <= max_addr; ptr += PAGE_SIZE) अणु
		पूर्णांक index = ptr_to_shaकरोw(s, ptr);

		अगर (index >= 0) अणु
			/* Each page must only contain one module */
			WARN_ON_ONCE(s->shaकरोw[index] != SHADOW_INVALID);
			s->shaकरोw[index] = (shaकरोw_t)check_index;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम हटाओ_module_from_shaकरोw(काष्ठा cfi_shaकरोw *s, काष्ठा module *mod,
		अचिन्हित दीर्घ min_addr, अचिन्हित दीर्घ max_addr)
अणु
	अचिन्हित दीर्घ ptr;

	क्रम (ptr = min_addr; ptr <= max_addr; ptr += PAGE_SIZE) अणु
		पूर्णांक index = ptr_to_shaकरोw(s, ptr);

		अगर (index >= 0)
			s->shaकरोw[index] = SHADOW_INVALID;
	पूर्ण
पूर्ण

प्रकार व्योम (*update_shaकरोw_fn)(काष्ठा cfi_shaकरोw *, काष्ठा module *,
			अचिन्हित दीर्घ min_addr, अचिन्हित दीर्घ max_addr);

अटल व्योम update_shaकरोw(काष्ठा module *mod, अचिन्हित दीर्घ base_addr,
		update_shaकरोw_fn fn)
अणु
	काष्ठा cfi_shaकरोw *prev;
	काष्ठा cfi_shaकरोw *next;
	अचिन्हित दीर्घ min_addr, max_addr;

	next = vदो_स्मृति(SHADOW_SIZE);

	mutex_lock(&shaकरोw_update_lock);
	prev = rcu_dereference_रक्षित(cfi_shaकरोw,
					 mutex_is_locked(&shaकरोw_update_lock));

	अगर (next) अणु
		next->base = base_addr >> PAGE_SHIFT;
		prepare_next_shaकरोw(prev, next);

		min_addr = (अचिन्हित दीर्घ)mod->core_layout.base;
		max_addr = min_addr + mod->core_layout.text_size;
		fn(next, mod, min_addr & PAGE_MASK, max_addr & PAGE_MASK);

		set_memory_ro((अचिन्हित दीर्घ)next, SHADOW_PAGES);
	पूर्ण

	rcu_assign_poपूर्णांकer(cfi_shaकरोw, next);
	mutex_unlock(&shaकरोw_update_lock);
	synchronize_rcu();

	अगर (prev) अणु
		set_memory_rw((अचिन्हित दीर्घ)prev, SHADOW_PAGES);
		vमुक्त(prev);
	पूर्ण
पूर्ण

व्योम cfi_module_add(काष्ठा module *mod, अचिन्हित दीर्घ base_addr)
अणु
	update_shaकरोw(mod, base_addr, add_module_to_shaकरोw);
पूर्ण

व्योम cfi_module_हटाओ(काष्ठा module *mod, अचिन्हित दीर्घ base_addr)
अणु
	update_shaकरोw(mod, base_addr, हटाओ_module_from_shaकरोw);
पूर्ण

अटल अंतरभूत cfi_check_fn ptr_to_check_fn(स्थिर काष्ठा cfi_shaकरोw __rcu *s,
	अचिन्हित दीर्घ ptr)
अणु
	पूर्णांक index;

	अगर (unlikely(!s))
		वापस शून्य; /* No shaकरोw available */

	index = ptr_to_shaकरोw(s, ptr);
	अगर (index < 0)
		वापस शून्य; /* Cannot be addressed with shaकरोw */

	वापस (cfi_check_fn)shaकरोw_to_check_fn(s, index);
पूर्ण

अटल अंतरभूत cfi_check_fn find_shaकरोw_check_fn(अचिन्हित दीर्घ ptr)
अणु
	cfi_check_fn fn;

	rcu_पढ़ो_lock_sched();
	fn = ptr_to_check_fn(rcu_dereference_sched(cfi_shaकरोw), ptr);
	rcu_पढ़ो_unlock_sched();

	वापस fn;
पूर्ण

#अन्यथा /* !CONFIG_CFI_CLANG_SHADOW */

अटल अंतरभूत cfi_check_fn find_shaकरोw_check_fn(अचिन्हित दीर्घ ptr)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_CFI_CLANG_SHADOW */

अटल अंतरभूत cfi_check_fn find_module_check_fn(अचिन्हित दीर्घ ptr)
अणु
	cfi_check_fn fn = शून्य;
	काष्ठा module *mod;

	rcu_पढ़ो_lock_sched();
	mod = __module_address(ptr);
	अगर (mod)
		fn = mod->cfi_check;
	rcu_पढ़ो_unlock_sched();

	वापस fn;
पूर्ण

अटल अंतरभूत cfi_check_fn find_check_fn(अचिन्हित दीर्घ ptr)
अणु
	cfi_check_fn fn = शून्य;

	अगर (is_kernel_text(ptr))
		वापस __cfi_check;

	/*
	 * Indirect call checks can happen when RCU is not watching. Both
	 * the shaकरोw and __module_address use RCU, so we need to wake it
	 * up अगर necessary.
	 */
	RCU_NONIDLE(अणु
		अगर (IS_ENABLED(CONFIG_CFI_CLANG_SHADOW))
			fn = find_shaकरोw_check_fn(ptr);

		अगर (!fn)
			fn = find_module_check_fn(ptr);
	पूर्ण);

	वापस fn;
पूर्ण

व्योम __cfi_slowpath_diag(uपूर्णांक64_t id, व्योम *ptr, व्योम *diag)
अणु
	cfi_check_fn fn = find_check_fn((अचिन्हित दीर्घ)ptr);

	अगर (likely(fn))
		fn(id, ptr, diag);
	अन्यथा /* Don't allow unchecked modules */
		handle_cfi_failure(ptr);
पूर्ण
EXPORT_SYMBOL(__cfi_slowpath_diag);

#अन्यथा /* !CONFIG_MODULES */

व्योम __cfi_slowpath_diag(uपूर्णांक64_t id, व्योम *ptr, व्योम *diag)
अणु
	handle_cfi_failure(ptr); /* No modules */
पूर्ण
EXPORT_SYMBOL(__cfi_slowpath_diag);

#पूर्ण_अगर /* CONFIG_MODULES */

व्योम cfi_failure_handler(व्योम *data, व्योम *ptr, व्योम *vtable)
अणु
	handle_cfi_failure(ptr);
पूर्ण
EXPORT_SYMBOL(cfi_failure_handler);
