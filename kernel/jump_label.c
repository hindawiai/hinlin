<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * jump label support
 *
 * Copyright (C) 2009 Jason Baron <jbaron@redhat.com>
 * Copyright (C) 2011 Peter Zijlstra
 *
 */
#समावेश <linux/memory.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/err.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/jump_label_ratelimit.h>
#समावेश <linux/bug.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/sections.h>

/* mutex to protect coming/going of the jump_label table */
अटल DEFINE_MUTEX(jump_label_mutex);

व्योम jump_label_lock(व्योम)
अणु
	mutex_lock(&jump_label_mutex);
पूर्ण

व्योम jump_label_unlock(व्योम)
अणु
	mutex_unlock(&jump_label_mutex);
पूर्ण

अटल पूर्णांक jump_label_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा jump_entry *jea = a;
	स्थिर काष्ठा jump_entry *jeb = b;

	/*
	 * Entrires are sorted by key.
	 */
	अगर (jump_entry_key(jea) < jump_entry_key(jeb))
		वापस -1;

	अगर (jump_entry_key(jea) > jump_entry_key(jeb))
		वापस 1;

	/*
	 * In the batching mode, entries should also be sorted by the code
	 * inside the alपढ़ोy sorted list of entries, enabling a द्वा_खोज in
	 * the vector.
	 */
	अगर (jump_entry_code(jea) < jump_entry_code(jeb))
		वापस -1;

	अगर (jump_entry_code(jea) > jump_entry_code(jeb))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम jump_label_swap(व्योम *a, व्योम *b, पूर्णांक size)
अणु
	दीर्घ delta = (अचिन्हित दीर्घ)a - (अचिन्हित दीर्घ)b;
	काष्ठा jump_entry *jea = a;
	काष्ठा jump_entry *jeb = b;
	काष्ठा jump_entry पंचांगp = *jea;

	jea->code	= jeb->code - delta;
	jea->target	= jeb->target - delta;
	jea->key	= jeb->key - delta;

	jeb->code	= पंचांगp.code + delta;
	jeb->target	= पंचांगp.target + delta;
	jeb->key	= पंचांगp.key + delta;
पूर्ण

अटल व्योम
jump_label_sort_entries(काष्ठा jump_entry *start, काष्ठा jump_entry *stop)
अणु
	अचिन्हित दीर्घ size;
	व्योम *swapfn = शून्य;

	अगर (IS_ENABLED(CONFIG_HAVE_ARCH_JUMP_LABEL_RELATIVE))
		swapfn = jump_label_swap;

	size = (((अचिन्हित दीर्घ)stop - (अचिन्हित दीर्घ)start)
					/ माप(काष्ठा jump_entry));
	sort(start, size, माप(काष्ठा jump_entry), jump_label_cmp, swapfn);
पूर्ण

अटल व्योम jump_label_update(काष्ठा अटल_key *key);

/*
 * There are similar definitions क्रम the !CONFIG_JUMP_LABEL हाल in jump_label.h.
 * The use of 'atomic_read()' requires atomic.h and its problematic क्रम some
 * kernel headers such as kernel.h and others. Since अटल_key_count() is not
 * used in the branch statements as it is क्रम the !CONFIG_JUMP_LABEL हाल its ok
 * to have it be a function here. Similarly, क्रम 'static_key_enable()' and
 * 'static_key_disable()', which require bug.h. This should allow jump_label.h
 * to be included from most/all places क्रम CONFIG_JUMP_LABEL.
 */
पूर्णांक अटल_key_count(काष्ठा अटल_key *key)
अणु
	/*
	 * -1 means the first अटल_key_slow_inc() is in progress.
	 *  अटल_key_enabled() must वापस true, so वापस 1 here.
	 */
	पूर्णांक n = atomic_पढ़ो(&key->enabled);

	वापस n >= 0 ? n : 1;
पूर्ण
EXPORT_SYMBOL_GPL(अटल_key_count);

व्योम अटल_key_slow_inc_cpuslocked(काष्ठा अटल_key *key)
अणु
	पूर्णांक v, v1;

	STATIC_KEY_CHECK_USE(key);
	lockdep_निश्चित_cpus_held();

	/*
	 * Careful अगर we get concurrent अटल_key_slow_inc() calls;
	 * later calls must रुको क्रम the first one to _finish_ the
	 * jump_label_update() process.  At the same समय, however,
	 * the jump_label_update() call below wants to see
	 * अटल_key_enabled(&key) क्रम jumps to be updated properly.
	 *
	 * So give a special meaning to negative key->enabled: it sends
	 * अटल_key_slow_inc() करोwn the slow path, and it is non-zero
	 * so it counts as "enabled" in jump_label_update().  Note that
	 * atomic_inc_unless_negative() checks >= 0, so roll our own.
	 */
	क्रम (v = atomic_पढ़ो(&key->enabled); v > 0; v = v1) अणु
		v1 = atomic_cmpxchg(&key->enabled, v, v + 1);
		अगर (likely(v1 == v))
			वापस;
	पूर्ण

	jump_label_lock();
	अगर (atomic_पढ़ो(&key->enabled) == 0) अणु
		atomic_set(&key->enabled, -1);
		jump_label_update(key);
		/*
		 * Ensure that अगर the above cmpxchg loop observes our positive
		 * value, it must also observe all the text changes.
		 */
		atomic_set_release(&key->enabled, 1);
	पूर्ण अन्यथा अणु
		atomic_inc(&key->enabled);
	पूर्ण
	jump_label_unlock();
पूर्ण

व्योम अटल_key_slow_inc(काष्ठा अटल_key *key)
अणु
	cpus_पढ़ो_lock();
	अटल_key_slow_inc_cpuslocked(key);
	cpus_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(अटल_key_slow_inc);

व्योम अटल_key_enable_cpuslocked(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);
	lockdep_निश्चित_cpus_held();

	अगर (atomic_पढ़ो(&key->enabled) > 0) अणु
		WARN_ON_ONCE(atomic_पढ़ो(&key->enabled) != 1);
		वापस;
	पूर्ण

	jump_label_lock();
	अगर (atomic_पढ़ो(&key->enabled) == 0) अणु
		atomic_set(&key->enabled, -1);
		jump_label_update(key);
		/*
		 * See अटल_key_slow_inc().
		 */
		atomic_set_release(&key->enabled, 1);
	पूर्ण
	jump_label_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(अटल_key_enable_cpuslocked);

व्योम अटल_key_enable(काष्ठा अटल_key *key)
अणु
	cpus_पढ़ो_lock();
	अटल_key_enable_cpuslocked(key);
	cpus_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(अटल_key_enable);

व्योम अटल_key_disable_cpuslocked(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);
	lockdep_निश्चित_cpus_held();

	अगर (atomic_पढ़ो(&key->enabled) != 1) अणु
		WARN_ON_ONCE(atomic_पढ़ो(&key->enabled) != 0);
		वापस;
	पूर्ण

	jump_label_lock();
	अगर (atomic_cmpxchg(&key->enabled, 1, 0))
		jump_label_update(key);
	jump_label_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(अटल_key_disable_cpuslocked);

व्योम अटल_key_disable(काष्ठा अटल_key *key)
अणु
	cpus_पढ़ो_lock();
	अटल_key_disable_cpuslocked(key);
	cpus_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(अटल_key_disable);

अटल bool अटल_key_slow_try_dec(काष्ठा अटल_key *key)
अणु
	पूर्णांक val;

	val = atomic_fetch_add_unless(&key->enabled, -1, 1);
	अगर (val == 1)
		वापस false;

	/*
	 * The negative count check is valid even when a negative
	 * key->enabled is in use by अटल_key_slow_inc(); a
	 * __अटल_key_slow_dec() beक्रमe the first अटल_key_slow_inc()
	 * वापसs is unbalanced, because all other अटल_key_slow_inc()
	 * instances block जबतक the update is in progress.
	 */
	WARN(val < 0, "jump label: negative count!\n");
	वापस true;
पूर्ण

अटल व्योम __अटल_key_slow_dec_cpuslocked(काष्ठा अटल_key *key)
अणु
	lockdep_निश्चित_cpus_held();

	अगर (अटल_key_slow_try_dec(key))
		वापस;

	jump_label_lock();
	अगर (atomic_dec_and_test(&key->enabled))
		jump_label_update(key);
	jump_label_unlock();
पूर्ण

अटल व्योम __अटल_key_slow_dec(काष्ठा अटल_key *key)
अणु
	cpus_पढ़ो_lock();
	__अटल_key_slow_dec_cpuslocked(key);
	cpus_पढ़ो_unlock();
पूर्ण

व्योम jump_label_update_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अटल_key_deferred *key =
		container_of(work, काष्ठा अटल_key_deferred, work.work);
	__अटल_key_slow_dec(&key->key);
पूर्ण
EXPORT_SYMBOL_GPL(jump_label_update_समयout);

व्योम अटल_key_slow_dec(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);
	__अटल_key_slow_dec(key);
पूर्ण
EXPORT_SYMBOL_GPL(अटल_key_slow_dec);

व्योम अटल_key_slow_dec_cpuslocked(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);
	__अटल_key_slow_dec_cpuslocked(key);
पूर्ण

व्योम __अटल_key_slow_dec_deferred(काष्ठा अटल_key *key,
				    काष्ठा delayed_work *work,
				    अचिन्हित दीर्घ समयout)
अणु
	STATIC_KEY_CHECK_USE(key);

	अगर (अटल_key_slow_try_dec(key))
		वापस;

	schedule_delayed_work(work, समयout);
पूर्ण
EXPORT_SYMBOL_GPL(__अटल_key_slow_dec_deferred);

व्योम __अटल_key_deferred_flush(व्योम *key, काष्ठा delayed_work *work)
अणु
	STATIC_KEY_CHECK_USE(key);
	flush_delayed_work(work);
पूर्ण
EXPORT_SYMBOL_GPL(__अटल_key_deferred_flush);

व्योम jump_label_rate_limit(काष्ठा अटल_key_deferred *key,
		अचिन्हित दीर्घ rl)
अणु
	STATIC_KEY_CHECK_USE(key);
	key->समयout = rl;
	INIT_DELAYED_WORK(&key->work, jump_label_update_समयout);
पूर्ण
EXPORT_SYMBOL_GPL(jump_label_rate_limit);

अटल पूर्णांक addr_conflict(काष्ठा jump_entry *entry, व्योम *start, व्योम *end)
अणु
	अगर (jump_entry_code(entry) <= (अचिन्हित दीर्घ)end &&
	    jump_entry_code(entry) + JUMP_LABEL_NOP_SIZE > (अचिन्हित दीर्घ)start)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक __jump_label_text_reserved(काष्ठा jump_entry *iter_start,
		काष्ठा jump_entry *iter_stop, व्योम *start, व्योम *end)
अणु
	काष्ठा jump_entry *iter;

	iter = iter_start;
	जबतक (iter < iter_stop) अणु
		अगर (addr_conflict(iter, start, end))
			वापस 1;
		iter++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Update code which is definitely not currently executing.
 * Architectures which need heavyweight synchronization to modअगरy
 * running code can override this to make the non-live update हाल
 * cheaper.
 */
व्योम __weak __init_or_module arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
					    क्रमागत jump_label_type type)
अणु
	arch_jump_label_transक्रमm(entry, type);
पूर्ण

अटल अंतरभूत काष्ठा jump_entry *अटल_key_entries(काष्ठा अटल_key *key)
अणु
	WARN_ON_ONCE(key->type & JUMP_TYPE_LINKED);
	वापस (काष्ठा jump_entry *)(key->type & ~JUMP_TYPE_MASK);
पूर्ण

अटल अंतरभूत bool अटल_key_type(काष्ठा अटल_key *key)
अणु
	वापस key->type & JUMP_TYPE_TRUE;
पूर्ण

अटल अंतरभूत bool अटल_key_linked(काष्ठा अटल_key *key)
अणु
	वापस key->type & JUMP_TYPE_LINKED;
पूर्ण

अटल अंतरभूत व्योम अटल_key_clear_linked(काष्ठा अटल_key *key)
अणु
	key->type &= ~JUMP_TYPE_LINKED;
पूर्ण

अटल अंतरभूत व्योम अटल_key_set_linked(काष्ठा अटल_key *key)
अणु
	key->type |= JUMP_TYPE_LINKED;
पूर्ण

/***
 * A 'struct static_key' uses a जोड़ such that it either poपूर्णांकs directly
 * to a table of 'struct jump_entry' or to a linked list of modules which in
 * turn poपूर्णांक to 'struct jump_entry' tables.
 *
 * The two lower bits of the poपूर्णांकer are used to keep track of which poपूर्णांकer
 * type is in use and to store the initial branch direction, we use an access
 * function which preserves these bits.
 */
अटल व्योम अटल_key_set_entries(काष्ठा अटल_key *key,
				   काष्ठा jump_entry *entries)
अणु
	अचिन्हित दीर्घ type;

	WARN_ON_ONCE((अचिन्हित दीर्घ)entries & JUMP_TYPE_MASK);
	type = key->type & JUMP_TYPE_MASK;
	key->entries = entries;
	key->type |= type;
पूर्ण

अटल क्रमागत jump_label_type jump_label_type(काष्ठा jump_entry *entry)
अणु
	काष्ठा अटल_key *key = jump_entry_key(entry);
	bool enabled = अटल_key_enabled(key);
	bool branch = jump_entry_is_branch(entry);

	/* See the comment in linux/jump_label.h */
	वापस enabled ^ branch;
पूर्ण

अटल bool jump_label_can_update(काष्ठा jump_entry *entry, bool init)
अणु
	/*
	 * Cannot update code that was in an init text area.
	 */
	अगर (!init && jump_entry_is_init(entry))
		वापस false;

	अगर (!kernel_text_address(jump_entry_code(entry))) अणु
		/*
		 * This skips patching built-in __निकास, which
		 * is part of init_section_contains() but is
		 * not part of kernel_text_address().
		 *
		 * Skipping built-in __निकास is fine since it
		 * will never be executed.
		 */
		WARN_ONCE(!jump_entry_is_init(entry),
			  "can't patch jump_label at %pS",
			  (व्योम *)jump_entry_code(entry));
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

#अगर_अघोषित HAVE_JUMP_LABEL_BATCH
अटल व्योम __jump_label_update(काष्ठा अटल_key *key,
				काष्ठा jump_entry *entry,
				काष्ठा jump_entry *stop,
				bool init)
अणु
	क्रम (; (entry < stop) && (jump_entry_key(entry) == key); entry++) अणु
		अगर (jump_label_can_update(entry, init))
			arch_jump_label_transक्रमm(entry, jump_label_type(entry));
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __jump_label_update(काष्ठा अटल_key *key,
				काष्ठा jump_entry *entry,
				काष्ठा jump_entry *stop,
				bool init)
अणु
	क्रम (; (entry < stop) && (jump_entry_key(entry) == key); entry++) अणु

		अगर (!jump_label_can_update(entry, init))
			जारी;

		अगर (!arch_jump_label_transक्रमm_queue(entry, jump_label_type(entry))) अणु
			/*
			 * Queue is full: Apply the current queue and try again.
			 */
			arch_jump_label_transक्रमm_apply();
			BUG_ON(!arch_jump_label_transक्रमm_queue(entry, jump_label_type(entry)));
		पूर्ण
	पूर्ण
	arch_jump_label_transक्रमm_apply();
पूर्ण
#पूर्ण_अगर

व्योम __init jump_label_init(व्योम)
अणु
	काष्ठा jump_entry *iter_start = __start___jump_table;
	काष्ठा jump_entry *iter_stop = __stop___jump_table;
	काष्ठा अटल_key *key = शून्य;
	काष्ठा jump_entry *iter;

	/*
	 * Since we are initializing the अटल_key.enabled field with
	 * with the 'raw' पूर्णांक values (to aव्योम pulling in atomic.h) in
	 * jump_label.h, let's make sure that is safe. There are only two
	 * हालs to check since we initialize to 0 or 1.
	 */
	BUILD_BUG_ON((पूर्णांक)ATOMIC_INIT(0) != 0);
	BUILD_BUG_ON((पूर्णांक)ATOMIC_INIT(1) != 1);

	अगर (अटल_key_initialized)
		वापस;

	cpus_पढ़ो_lock();
	jump_label_lock();
	jump_label_sort_entries(iter_start, iter_stop);

	क्रम (iter = iter_start; iter < iter_stop; iter++) अणु
		काष्ठा अटल_key *iterk;

		/* reग_लिखो NOPs */
		अगर (jump_label_type(iter) == JUMP_LABEL_NOP)
			arch_jump_label_transक्रमm_अटल(iter, JUMP_LABEL_NOP);

		अगर (init_section_contains((व्योम *)jump_entry_code(iter), 1))
			jump_entry_set_init(iter);

		iterk = jump_entry_key(iter);
		अगर (iterk == key)
			जारी;

		key = iterk;
		अटल_key_set_entries(key, iter);
	पूर्ण
	अटल_key_initialized = true;
	jump_label_unlock();
	cpus_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_MODULES

अटल क्रमागत jump_label_type jump_label_init_type(काष्ठा jump_entry *entry)
अणु
	काष्ठा अटल_key *key = jump_entry_key(entry);
	bool type = अटल_key_type(key);
	bool branch = jump_entry_is_branch(entry);

	/* See the comment in linux/jump_label.h */
	वापस type ^ branch;
पूर्ण

काष्ठा अटल_key_mod अणु
	काष्ठा अटल_key_mod *next;
	काष्ठा jump_entry *entries;
	काष्ठा module *mod;
पूर्ण;

अटल अंतरभूत काष्ठा अटल_key_mod *अटल_key_mod(काष्ठा अटल_key *key)
अणु
	WARN_ON_ONCE(!अटल_key_linked(key));
	वापस (काष्ठा अटल_key_mod *)(key->type & ~JUMP_TYPE_MASK);
पूर्ण

/***
 * key->type and key->next are the same via जोड़.
 * This sets key->next and preserves the type bits.
 *
 * See additional comments above अटल_key_set_entries().
 */
अटल व्योम अटल_key_set_mod(काष्ठा अटल_key *key,
			       काष्ठा अटल_key_mod *mod)
अणु
	अचिन्हित दीर्घ type;

	WARN_ON_ONCE((अचिन्हित दीर्घ)mod & JUMP_TYPE_MASK);
	type = key->type & JUMP_TYPE_MASK;
	key->next = mod;
	key->type |= type;
पूर्ण

अटल पूर्णांक __jump_label_mod_text_reserved(व्योम *start, व्योम *end)
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

	ret = __jump_label_text_reserved(mod->jump_entries,
				mod->jump_entries + mod->num_jump_entries,
				start, end);

	module_put(mod);

	वापस ret;
पूर्ण

अटल व्योम __jump_label_mod_update(काष्ठा अटल_key *key)
अणु
	काष्ठा अटल_key_mod *mod;

	क्रम (mod = अटल_key_mod(key); mod; mod = mod->next) अणु
		काष्ठा jump_entry *stop;
		काष्ठा module *m;

		/*
		 * शून्य अगर the अटल_key is defined in a module
		 * that करोes not use it
		 */
		अगर (!mod->entries)
			जारी;

		m = mod->mod;
		अगर (!m)
			stop = __stop___jump_table;
		अन्यथा
			stop = m->jump_entries + m->num_jump_entries;
		__jump_label_update(key, mod->entries, stop,
				    m && m->state == MODULE_STATE_COMING);
	पूर्ण
पूर्ण

/***
 * apply_jump_label_nops - patch module jump labels with arch_get_jump_label_nop()
 * @mod: module to patch
 *
 * Allow क्रम run-समय selection of the optimal nops. Beक्रमe the module
 * loads patch these with arch_get_jump_label_nop(), which is specअगरied by
 * the arch specअगरic jump label code.
 */
व्योम jump_label_apply_nops(काष्ठा module *mod)
अणु
	काष्ठा jump_entry *iter_start = mod->jump_entries;
	काष्ठा jump_entry *iter_stop = iter_start + mod->num_jump_entries;
	काष्ठा jump_entry *iter;

	/* अगर the module करोesn't have jump label entries, just वापस */
	अगर (iter_start == iter_stop)
		वापस;

	क्रम (iter = iter_start; iter < iter_stop; iter++) अणु
		/* Only ग_लिखो NOPs क्रम arch_branch_अटल(). */
		अगर (jump_label_init_type(iter) == JUMP_LABEL_NOP)
			arch_jump_label_transक्रमm_अटल(iter, JUMP_LABEL_NOP);
	पूर्ण
पूर्ण

अटल पूर्णांक jump_label_add_module(काष्ठा module *mod)
अणु
	काष्ठा jump_entry *iter_start = mod->jump_entries;
	काष्ठा jump_entry *iter_stop = iter_start + mod->num_jump_entries;
	काष्ठा jump_entry *iter;
	काष्ठा अटल_key *key = शून्य;
	काष्ठा अटल_key_mod *jlm, *jlm2;

	/* अगर the module करोesn't have jump label entries, just वापस */
	अगर (iter_start == iter_stop)
		वापस 0;

	jump_label_sort_entries(iter_start, iter_stop);

	क्रम (iter = iter_start; iter < iter_stop; iter++) अणु
		काष्ठा अटल_key *iterk;

		अगर (within_module_init(jump_entry_code(iter), mod))
			jump_entry_set_init(iter);

		iterk = jump_entry_key(iter);
		अगर (iterk == key)
			जारी;

		key = iterk;
		अगर (within_module((अचिन्हित दीर्घ)key, mod)) अणु
			अटल_key_set_entries(key, iter);
			जारी;
		पूर्ण
		jlm = kzalloc(माप(काष्ठा अटल_key_mod), GFP_KERNEL);
		अगर (!jlm)
			वापस -ENOMEM;
		अगर (!अटल_key_linked(key)) अणु
			jlm2 = kzalloc(माप(काष्ठा अटल_key_mod),
				       GFP_KERNEL);
			अगर (!jlm2) अणु
				kमुक्त(jlm);
				वापस -ENOMEM;
			पूर्ण
			preempt_disable();
			jlm2->mod = __module_address((अचिन्हित दीर्घ)key);
			preempt_enable();
			jlm2->entries = अटल_key_entries(key);
			jlm2->next = शून्य;
			अटल_key_set_mod(key, jlm2);
			अटल_key_set_linked(key);
		पूर्ण
		jlm->mod = mod;
		jlm->entries = iter;
		jlm->next = अटल_key_mod(key);
		अटल_key_set_mod(key, jlm);
		अटल_key_set_linked(key);

		/* Only update अगर we've changed from our initial state */
		अगर (jump_label_type(iter) != jump_label_init_type(iter))
			__jump_label_update(key, iter, iter_stop, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम jump_label_del_module(काष्ठा module *mod)
अणु
	काष्ठा jump_entry *iter_start = mod->jump_entries;
	काष्ठा jump_entry *iter_stop = iter_start + mod->num_jump_entries;
	काष्ठा jump_entry *iter;
	काष्ठा अटल_key *key = शून्य;
	काष्ठा अटल_key_mod *jlm, **prev;

	क्रम (iter = iter_start; iter < iter_stop; iter++) अणु
		अगर (jump_entry_key(iter) == key)
			जारी;

		key = jump_entry_key(iter);

		अगर (within_module((अचिन्हित दीर्घ)key, mod))
			जारी;

		/* No memory during module load */
		अगर (WARN_ON(!अटल_key_linked(key)))
			जारी;

		prev = &key->next;
		jlm = अटल_key_mod(key);

		जबतक (jlm && jlm->mod != mod) अणु
			prev = &jlm->next;
			jlm = jlm->next;
		पूर्ण

		/* No memory during module load */
		अगर (WARN_ON(!jlm))
			जारी;

		अगर (prev == &key->next)
			अटल_key_set_mod(key, jlm->next);
		अन्यथा
			*prev = jlm->next;

		kमुक्त(jlm);

		jlm = अटल_key_mod(key);
		/* अगर only one etry is left, fold it back पूर्णांकo the अटल_key */
		अगर (jlm->next == शून्य) अणु
			अटल_key_set_entries(key, jlm->entries);
			अटल_key_clear_linked(key);
			kमुक्त(jlm);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
jump_label_module_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val,
			 व्योम *data)
अणु
	काष्ठा module *mod = data;
	पूर्णांक ret = 0;

	cpus_पढ़ो_lock();
	jump_label_lock();

	चयन (val) अणु
	हाल MODULE_STATE_COMING:
		ret = jump_label_add_module(mod);
		अगर (ret) अणु
			WARN(1, "Failed to allocate memory: jump_label may not work properly.\n");
			jump_label_del_module(mod);
		पूर्ण
		अवरोध;
	हाल MODULE_STATE_GOING:
		jump_label_del_module(mod);
		अवरोध;
	पूर्ण

	jump_label_unlock();
	cpus_पढ़ो_unlock();

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल काष्ठा notअगरier_block jump_label_module_nb = अणु
	.notअगरier_call = jump_label_module_notअगरy,
	.priority = 1, /* higher than tracepoपूर्णांकs */
पूर्ण;

अटल __init पूर्णांक jump_label_init_module(व्योम)
अणु
	वापस रेजिस्टर_module_notअगरier(&jump_label_module_nb);
पूर्ण
early_initcall(jump_label_init_module);

#पूर्ण_अगर /* CONFIG_MODULES */

/***
 * jump_label_text_reserved - check अगर addr range is reserved
 * @start: start text addr
 * @end: end text addr
 *
 * checks अगर the text addr located between @start and @end
 * overlaps with any of the jump label patch addresses. Code
 * that wants to modअगरy kernel text should first verअगरy that
 * it करोes not overlap with any of the jump label addresses.
 * Caller must hold jump_label_mutex.
 *
 * वापसs 1 अगर there is an overlap, 0 otherwise
 */
पूर्णांक jump_label_text_reserved(व्योम *start, व्योम *end)
अणु
	पूर्णांक ret = __jump_label_text_reserved(__start___jump_table,
			__stop___jump_table, start, end);

	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_MODULES
	ret = __jump_label_mod_text_reserved(start, end);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम jump_label_update(काष्ठा अटल_key *key)
अणु
	काष्ठा jump_entry *stop = __stop___jump_table;
	bool init = प्रणाली_state < SYSTEM_RUNNING;
	काष्ठा jump_entry *entry;
#अगर_घोषित CONFIG_MODULES
	काष्ठा module *mod;

	अगर (अटल_key_linked(key)) अणु
		__jump_label_mod_update(key);
		वापस;
	पूर्ण

	preempt_disable();
	mod = __module_address((अचिन्हित दीर्घ)key);
	अगर (mod) अणु
		stop = mod->jump_entries + mod->num_jump_entries;
		init = mod->state == MODULE_STATE_COMING;
	पूर्ण
	preempt_enable();
#पूर्ण_अगर
	entry = अटल_key_entries(key);
	/* अगर there are no users, entry can be शून्य */
	अगर (entry)
		__jump_label_update(key, entry, stop, init);
पूर्ण

#अगर_घोषित CONFIG_STATIC_KEYS_SELFTEST
अटल DEFINE_STATIC_KEY_TRUE(sk_true);
अटल DEFINE_STATIC_KEY_FALSE(sk_false);

अटल __init पूर्णांक jump_label_test(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		WARN_ON(अटल_key_enabled(&sk_true.key) != true);
		WARN_ON(अटल_key_enabled(&sk_false.key) != false);

		WARN_ON(!अटल_branch_likely(&sk_true));
		WARN_ON(!अटल_branch_unlikely(&sk_true));
		WARN_ON(अटल_branch_likely(&sk_false));
		WARN_ON(अटल_branch_unlikely(&sk_false));

		अटल_branch_disable(&sk_true);
		अटल_branch_enable(&sk_false);

		WARN_ON(अटल_key_enabled(&sk_true.key) == true);
		WARN_ON(अटल_key_enabled(&sk_false.key) == false);

		WARN_ON(अटल_branch_likely(&sk_true));
		WARN_ON(अटल_branch_unlikely(&sk_true));
		WARN_ON(!अटल_branch_likely(&sk_false));
		WARN_ON(!अटल_branch_unlikely(&sk_false));

		अटल_branch_enable(&sk_true);
		अटल_branch_disable(&sk_false);
	पूर्ण

	वापस 0;
पूर्ण
early_initcall(jump_label_test);
#पूर्ण_अगर /* STATIC_KEYS_SELFTEST */
