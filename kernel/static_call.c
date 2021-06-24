<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/अटल_call.h>
#समावेश <linux/bug.h>
#समावेश <linux/smp.h>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/cpu.h>
#समावेश <linux/processor.h>
#समावेश <यंत्र/sections.h>

बाह्य काष्ठा अटल_call_site __start_अटल_call_sites[],
			       __stop_अटल_call_sites[];
बाह्य काष्ठा अटल_call_tramp_key __start_अटल_call_tramp_key[],
				    __stop_अटल_call_tramp_key[];

अटल bool अटल_call_initialized;

/* mutex to protect key modules/sites */
अटल DEFINE_MUTEX(अटल_call_mutex);

अटल व्योम अटल_call_lock(व्योम)
अणु
	mutex_lock(&अटल_call_mutex);
पूर्ण

अटल व्योम अटल_call_unlock(व्योम)
अणु
	mutex_unlock(&अटल_call_mutex);
पूर्ण

अटल अंतरभूत व्योम *अटल_call_addr(काष्ठा अटल_call_site *site)
अणु
	वापस (व्योम *)((दीर्घ)site->addr + (दीर्घ)&site->addr);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __अटल_call_key(स्थिर काष्ठा अटल_call_site *site)
अणु
	वापस (दीर्घ)site->key + (दीर्घ)&site->key;
पूर्ण

अटल अंतरभूत काष्ठा अटल_call_key *अटल_call_key(स्थिर काष्ठा अटल_call_site *site)
अणु
	वापस (व्योम *)(__अटल_call_key(site) & ~STATIC_CALL_SITE_FLAGS);
पूर्ण

/* These assume the key is word-aligned. */
अटल अंतरभूत bool अटल_call_is_init(काष्ठा अटल_call_site *site)
अणु
	वापस __अटल_call_key(site) & STATIC_CALL_SITE_INIT;
पूर्ण

अटल अंतरभूत bool अटल_call_is_tail(काष्ठा अटल_call_site *site)
अणु
	वापस __अटल_call_key(site) & STATIC_CALL_SITE_TAIL;
पूर्ण

अटल अंतरभूत व्योम अटल_call_set_init(काष्ठा अटल_call_site *site)
अणु
	site->key = (__अटल_call_key(site) | STATIC_CALL_SITE_INIT) -
		    (दीर्घ)&site->key;
पूर्ण

अटल पूर्णांक अटल_call_site_cmp(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा अटल_call_site *a = _a;
	स्थिर काष्ठा अटल_call_site *b = _b;
	स्थिर काष्ठा अटल_call_key *key_a = अटल_call_key(a);
	स्थिर काष्ठा अटल_call_key *key_b = अटल_call_key(b);

	अगर (key_a < key_b)
		वापस -1;

	अगर (key_a > key_b)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम अटल_call_site_swap(व्योम *_a, व्योम *_b, पूर्णांक size)
अणु
	दीर्घ delta = (अचिन्हित दीर्घ)_a - (अचिन्हित दीर्घ)_b;
	काष्ठा अटल_call_site *a = _a;
	काष्ठा अटल_call_site *b = _b;
	काष्ठा अटल_call_site पंचांगp = *a;

	a->addr = b->addr  - delta;
	a->key  = b->key   - delta;

	b->addr = पंचांगp.addr + delta;
	b->key  = पंचांगp.key  + delta;
पूर्ण

अटल अंतरभूत व्योम अटल_call_sort_entries(काष्ठा अटल_call_site *start,
					    काष्ठा अटल_call_site *stop)
अणु
	sort(start, stop - start, माप(काष्ठा अटल_call_site),
	     अटल_call_site_cmp, अटल_call_site_swap);
पूर्ण

अटल अंतरभूत bool अटल_call_key_has_mods(काष्ठा अटल_call_key *key)
अणु
	वापस !(key->type & 1);
पूर्ण

अटल अंतरभूत काष्ठा अटल_call_mod *अटल_call_key_next(काष्ठा अटल_call_key *key)
अणु
	अगर (!अटल_call_key_has_mods(key))
		वापस शून्य;

	वापस key->mods;
पूर्ण

अटल अंतरभूत काष्ठा अटल_call_site *अटल_call_key_sites(काष्ठा अटल_call_key *key)
अणु
	अगर (अटल_call_key_has_mods(key))
		वापस शून्य;

	वापस (काष्ठा अटल_call_site *)(key->type & ~1);
पूर्ण

व्योम __अटल_call_update(काष्ठा अटल_call_key *key, व्योम *tramp, व्योम *func)
अणु
	काष्ठा अटल_call_site *site, *stop;
	काष्ठा अटल_call_mod *site_mod, first;

	cpus_पढ़ो_lock();
	अटल_call_lock();

	अगर (key->func == func)
		जाओ करोne;

	key->func = func;

	arch_अटल_call_transक्रमm(शून्य, tramp, func, false);

	/*
	 * If uninitialized, we'll not update the callsites, but they still
	 * poपूर्णांक to the trampoline and we just patched that.
	 */
	अगर (WARN_ON_ONCE(!अटल_call_initialized))
		जाओ करोne;

	first = (काष्ठा अटल_call_mod)अणु
		.next = अटल_call_key_next(key),
		.mod = शून्य,
		.sites = अटल_call_key_sites(key),
	पूर्ण;

	क्रम (site_mod = &first; site_mod; site_mod = site_mod->next) अणु
		bool init = प्रणाली_state < SYSTEM_RUNNING;
		काष्ठा module *mod = site_mod->mod;

		अगर (!site_mod->sites) अणु
			/*
			 * This can happen अगर the अटल call key is defined in
			 * a module which करोesn't use it.
			 *
			 * It also happens in the has_mods हाल, where the
			 * 'first' entry has no sites associated with it.
			 */
			जारी;
		पूर्ण

		stop = __stop_अटल_call_sites;

		अगर (mod) अणु
#अगर_घोषित CONFIG_MODULES
			stop = mod->अटल_call_sites +
			       mod->num_अटल_call_sites;
			init = mod->state == MODULE_STATE_COMING;
#पूर्ण_अगर
		पूर्ण

		क्रम (site = site_mod->sites;
		     site < stop && अटल_call_key(site) == key; site++) अणु
			व्योम *site_addr = अटल_call_addr(site);

			अगर (!init && अटल_call_is_init(site))
				जारी;

			अगर (!kernel_text_address((अचिन्हित दीर्घ)site_addr)) अणु
				/*
				 * This skips patching built-in __निकास, which
				 * is part of init_section_contains() but is
				 * not part of kernel_text_address().
				 *
				 * Skipping built-in __निकास is fine since it
				 * will never be executed.
				 */
				WARN_ONCE(!अटल_call_is_init(site),
					  "can't patch static call site at %pS",
					  site_addr);
				जारी;
			पूर्ण

			arch_अटल_call_transक्रमm(site_addr, शून्य, func,
						   अटल_call_is_tail(site));
		पूर्ण
	पूर्ण

करोne:
	अटल_call_unlock();
	cpus_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(__अटल_call_update);

अटल पूर्णांक __अटल_call_init(काष्ठा module *mod,
			      काष्ठा अटल_call_site *start,
			      काष्ठा अटल_call_site *stop)
अणु
	काष्ठा अटल_call_site *site;
	काष्ठा अटल_call_key *key, *prev_key = शून्य;
	काष्ठा अटल_call_mod *site_mod;

	अगर (start == stop)
		वापस 0;

	अटल_call_sort_entries(start, stop);

	क्रम (site = start; site < stop; site++) अणु
		व्योम *site_addr = अटल_call_addr(site);

		अगर ((mod && within_module_init((अचिन्हित दीर्घ)site_addr, mod)) ||
		    (!mod && init_section_contains(site_addr, 1)))
			अटल_call_set_init(site);

		key = अटल_call_key(site);
		अगर (key != prev_key) अणु
			prev_key = key;

			/*
			 * For vmlinux (!mod) aव्योम the allocation by storing
			 * the sites poपूर्णांकer in the key itself. Also see
			 * __अटल_call_update()'s @first.
			 *
			 * This allows architectures (eg. x86) to call
			 * अटल_call_init() beक्रमe memory allocation works.
			 */
			अगर (!mod) अणु
				key->sites = site;
				key->type |= 1;
				जाओ करो_transक्रमm;
			पूर्ण

			site_mod = kzalloc(माप(*site_mod), GFP_KERNEL);
			अगर (!site_mod)
				वापस -ENOMEM;

			/*
			 * When the key has a direct sites poपूर्णांकer, extract
			 * that पूर्णांकo an explicit काष्ठा अटल_call_mod, so we
			 * can have a list of modules.
			 */
			अगर (अटल_call_key_sites(key)) अणु
				site_mod->mod = शून्य;
				site_mod->next = शून्य;
				site_mod->sites = अटल_call_key_sites(key);

				key->mods = site_mod;

				site_mod = kzalloc(माप(*site_mod), GFP_KERNEL);
				अगर (!site_mod)
					वापस -ENOMEM;
			पूर्ण

			site_mod->mod = mod;
			site_mod->sites = site;
			site_mod->next = अटल_call_key_next(key);
			key->mods = site_mod;
		पूर्ण

करो_transक्रमm:
		arch_अटल_call_transक्रमm(site_addr, शून्य, key->func,
				अटल_call_is_tail(site));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक addr_conflict(काष्ठा अटल_call_site *site, व्योम *start, व्योम *end)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)अटल_call_addr(site);

	अगर (addr <= (अचिन्हित दीर्घ)end &&
	    addr + CALL_INSN_SIZE > (अचिन्हित दीर्घ)start)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक __अटल_call_text_reserved(काष्ठा अटल_call_site *iter_start,
				       काष्ठा अटल_call_site *iter_stop,
				       व्योम *start, व्योम *end)
अणु
	काष्ठा अटल_call_site *iter = iter_start;

	जबतक (iter < iter_stop) अणु
		अगर (addr_conflict(iter, start, end))
			वापस 1;
		iter++;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MODULES

अटल पूर्णांक __अटल_call_mod_text_reserved(व्योम *start, व्योम *end)
अणु
	काष्ठा module *mod;
	पूर्णांक ret;

	preempt_disable();
	mod = __module_text_address((अचिन्हित दीर्घ)start);
	WARN_ON_ONCE(__module_text_address((अचिन्हित दीर्घ)end) != mod);
	अगर (!try_module_get(mod))
		mod = शून्य;
	preempt_enable();

	अगर (!mod)
		वापस 0;

	ret = __अटल_call_text_reserved(mod->अटल_call_sites,
			mod->अटल_call_sites + mod->num_अटल_call_sites,
			start, end);

	module_put(mod);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ tramp_key_lookup(अचिन्हित दीर्घ addr)
अणु
	काष्ठा अटल_call_tramp_key *start = __start_अटल_call_tramp_key;
	काष्ठा अटल_call_tramp_key *stop = __stop_अटल_call_tramp_key;
	काष्ठा अटल_call_tramp_key *tramp_key;

	क्रम (tramp_key = start; tramp_key != stop; tramp_key++) अणु
		अचिन्हित दीर्घ tramp;

		tramp = (दीर्घ)tramp_key->tramp + (दीर्घ)&tramp_key->tramp;
		अगर (tramp == addr)
			वापस (दीर्घ)tramp_key->key + (दीर्घ)&tramp_key->key;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक अटल_call_add_module(काष्ठा module *mod)
अणु
	काष्ठा अटल_call_site *start = mod->अटल_call_sites;
	काष्ठा अटल_call_site *stop = start + mod->num_अटल_call_sites;
	काष्ठा अटल_call_site *site;

	क्रम (site = start; site != stop; site++) अणु
		अचिन्हित दीर्घ s_key = __अटल_call_key(site);
		अचिन्हित दीर्घ addr = s_key & ~STATIC_CALL_SITE_FLAGS;
		अचिन्हित दीर्घ key;

		/*
		 * Is the key is exported, 'addr' poपूर्णांकs to the key, which
		 * means modules are allowed to call अटल_call_update() on
		 * it.
		 *
		 * Otherwise, the key isn't exported, and 'addr' poपूर्णांकs to the
		 * trampoline so we need to lookup the key.
		 *
		 * We go through this dance to prevent crazy modules from
		 * abusing sensitive अटल calls.
		 */
		अगर (!kernel_text_address(addr))
			जारी;

		key = tramp_key_lookup(addr);
		अगर (!key) अणु
			pr_warn("Failed to fixup __raw_static_call() usage at: %ps\n",
				अटल_call_addr(site));
			वापस -EINVAL;
		पूर्ण

		key |= s_key & STATIC_CALL_SITE_FLAGS;
		site->key = key - (दीर्घ)&site->key;
	पूर्ण

	वापस __अटल_call_init(mod, start, stop);
पूर्ण

अटल व्योम अटल_call_del_module(काष्ठा module *mod)
अणु
	काष्ठा अटल_call_site *start = mod->अटल_call_sites;
	काष्ठा अटल_call_site *stop = mod->अटल_call_sites +
					mod->num_अटल_call_sites;
	काष्ठा अटल_call_key *key, *prev_key = शून्य;
	काष्ठा अटल_call_mod *site_mod, **prev;
	काष्ठा अटल_call_site *site;

	क्रम (site = start; site < stop; site++) अणु
		key = अटल_call_key(site);
		अगर (key == prev_key)
			जारी;

		prev_key = key;

		क्रम (prev = &key->mods, site_mod = key->mods;
		     site_mod && site_mod->mod != mod;
		     prev = &site_mod->next, site_mod = site_mod->next)
			;

		अगर (!site_mod)
			जारी;

		*prev = site_mod->next;
		kमुक्त(site_mod);
	पूर्ण
पूर्ण

अटल पूर्णांक अटल_call_module_notअगरy(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;
	पूर्णांक ret = 0;

	cpus_पढ़ो_lock();
	अटल_call_lock();

	चयन (val) अणु
	हाल MODULE_STATE_COMING:
		ret = अटल_call_add_module(mod);
		अगर (ret) अणु
			WARN(1, "Failed to allocate memory for static calls");
			अटल_call_del_module(mod);
		पूर्ण
		अवरोध;
	हाल MODULE_STATE_GOING:
		अटल_call_del_module(mod);
		अवरोध;
	पूर्ण

	अटल_call_unlock();
	cpus_पढ़ो_unlock();

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल काष्ठा notअगरier_block अटल_call_module_nb = अणु
	.notअगरier_call = अटल_call_module_notअगरy,
पूर्ण;

#अन्यथा

अटल अंतरभूत पूर्णांक __अटल_call_mod_text_reserved(व्योम *start, व्योम *end)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MODULES */

पूर्णांक अटल_call_text_reserved(व्योम *start, व्योम *end)
अणु
	पूर्णांक ret = __अटल_call_text_reserved(__start_अटल_call_sites,
			__stop_अटल_call_sites, start, end);

	अगर (ret)
		वापस ret;

	वापस __अटल_call_mod_text_reserved(start, end);
पूर्ण

पूर्णांक __init अटल_call_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (अटल_call_initialized)
		वापस 0;

	cpus_पढ़ो_lock();
	अटल_call_lock();
	ret = __अटल_call_init(शून्य, __start_अटल_call_sites,
				 __stop_अटल_call_sites);
	अटल_call_unlock();
	cpus_पढ़ो_unlock();

	अगर (ret) अणु
		pr_err("Failed to allocate memory for static_call!\n");
		BUG();
	पूर्ण

	अटल_call_initialized = true;

#अगर_घोषित CONFIG_MODULES
	रेजिस्टर_module_notअगरier(&अटल_call_module_nb);
#पूर्ण_अगर
	वापस 0;
पूर्ण
early_initcall(अटल_call_init);

दीर्घ __अटल_call_वापस0(व्योम)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_STATIC_CALL_SELFTEST

अटल पूर्णांक func_a(पूर्णांक x)
अणु
	वापस x+1;
पूर्ण

अटल पूर्णांक func_b(पूर्णांक x)
अणु
	वापस x+2;
पूर्ण

DEFINE_STATIC_CALL(sc_selftest, func_a);

अटल काष्ठा अटल_call_data अणु
      पूर्णांक (*func)(पूर्णांक);
      पूर्णांक val;
      पूर्णांक expect;
पूर्ण अटल_call_data [] __initdata = अणु
      अणु शून्य,   2, 3 पूर्ण,
      अणु func_b, 2, 4 पूर्ण,
      अणु func_a, 2, 3 पूर्ण
पूर्ण;

अटल पूर्णांक __init test_अटल_call_init(व्योम)
अणु
      पूर्णांक i;

      क्रम (i = 0; i < ARRAY_SIZE(अटल_call_data); i++ ) अणु
	      काष्ठा अटल_call_data *scd = &अटल_call_data[i];

              अगर (scd->func)
                      अटल_call_update(sc_selftest, scd->func);

              WARN_ON(अटल_call(sc_selftest)(scd->val) != scd->expect);
      पूर्ण

      वापस 0;
पूर्ण
early_initcall(test_अटल_call_init);

#पूर्ण_अगर /* CONFIG_STATIC_CALL_SELFTEST */
