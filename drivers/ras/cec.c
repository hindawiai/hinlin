<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017-2019 Borislav Petkov, SUSE Lअसल.
 */
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ras.h>
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/mce.h>

#समावेश "debugfs.h"

/*
 * RAS Correctable Errors Collector
 *
 * This is a simple gadget which collects correctable errors and counts their
 * occurrence per physical page address.
 *
 * We've opted क्रम possibly the simplest data काष्ठाure to collect those - an
 * array of the size of a memory page. It stores 512 u64's with the following
 * काष्ठाure:
 *
 * [63 ... PFN ... 12 | 11 ... generation ... 10 | 9 ... count ... 0]
 *
 * The generation in the two highest order bits is two bits which are set to 11b
 * on every insertion. During the course of each entry's existence, the
 * generation field माला_लो decremented during spring cleaning to 10b, then 01b and
 * then 00b.
 *
 * This way we're employing the natural numeric ordering to make sure that newly
 * inserted/touched elements have higher 12-bit counts (which we've manufactured)
 * and thus iterating over the array initially won't kick out those elements
 * which were inserted last.
 *
 * Spring cleaning is what we करो when we reach a certain number CLEAN_ELEMS of
 * elements entered पूर्णांकo the array, during which, we're decaying all elements.
 * If, after decay, an element माला_लो inserted again, its generation is set to 11b
 * to make sure it has higher numerical count than other, older elements and
 * thus emulate an an LRU-like behavior when deleting elements to मुक्त up space
 * in the page.
 *
 * When an element reaches it's max count of action_threshold, we try to poison
 * it by assuming that errors triggered action_threshold बार in a single page
 * are excessive and that page shouldn't be used anymore. action_threshold is
 * initialized to COUNT_MASK which is the maximum.
 *
 * That error event entry causes cec_add_elem() to वापस !0 value and thus
 * संकेत to its callers to log the error.
 *
 * To the question why we've chosen a page and moving elements around with
 * स_हटाओ(), it is because it is a very simple काष्ठाure to handle and max data
 * movement is 4K which on highly optimized modern CPUs is almost unnoticeable.
 * We wanted to aव्योम the poपूर्णांकer traversal of more complex काष्ठाures like a
 * linked list or some sort of a balancing search tree.
 *
 * Deleting an element takes O(n) but since it is only a single page, it should
 * be fast enough and it shouldn't happen all too often depending on error
 * patterns.
 */

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "RAS: " fmt

/*
 * We use DECAY_BITS bits of PAGE_SHIFT bits क्रम counting decay, i.e., how दीर्घ
 * elements have stayed in the array without having been accessed again.
 */
#घोषणा DECAY_BITS		2
#घोषणा DECAY_MASK		((1ULL << DECAY_BITS) - 1)
#घोषणा MAX_ELEMS		(PAGE_SIZE / माप(u64))

/*
 * Threshold amount of inserted elements after which we start spring
 * cleaning.
 */
#घोषणा CLEAN_ELEMS		(MAX_ELEMS >> DECAY_BITS)

/* Bits which count the number of errors happened in this 4K page. */
#घोषणा COUNT_BITS		(PAGE_SHIFT - DECAY_BITS)
#घोषणा COUNT_MASK		((1ULL << COUNT_BITS) - 1)
#घोषणा FULL_COUNT_MASK		(PAGE_SIZE - 1)

/*
 * u64: [ 63 ... 12 | DECAY_BITS | COUNT_BITS ]
 */

#घोषणा PFN(e)			((e) >> PAGE_SHIFT)
#घोषणा DECAY(e)		(((e) >> COUNT_BITS) & DECAY_MASK)
#घोषणा COUNT(e)		((अचिन्हित पूर्णांक)(e) & COUNT_MASK)
#घोषणा FULL_COUNT(e)		((e) & (PAGE_SIZE - 1))

अटल काष्ठा ce_array अणु
	u64 *array;			/* container page */
	अचिन्हित पूर्णांक n;			/* number of elements in the array */

	अचिन्हित पूर्णांक decay_count;	/*
					 * number of element insertions/increments
					 * since the last spring cleaning.
					 */

	u64 pfns_poisoned;		/*
					 * number of PFNs which got poisoned.
					 */

	u64 ces_entered;		/*
					 * The number of correctable errors
					 * entered पूर्णांकo the collector.
					 */

	u64 decays_करोne;		/*
					 * Times we did spring cleaning.
					 */

	जोड़ अणु
		काष्ठा अणु
			__u32	disabled : 1,	/* cmdline disabled */
			__resv   : 31;
		पूर्ण;
		__u32 flags;
	पूर्ण;
पूर्ण ce_arr;

अटल DEFINE_MUTEX(ce_mutex);
अटल u64 dfs_pfn;

/* Amount of errors after which we offline */
अटल u64 action_threshold = COUNT_MASK;

/* Each element "decays" each decay_पूर्णांकerval which is 24hrs by शेष. */
#घोषणा CEC_DECAY_DEFAULT_INTERVAL	24 * 60 * 60	/* 24 hrs */
#घोषणा CEC_DECAY_MIN_INTERVAL		 1 * 60 * 60	/* 1h */
#घोषणा CEC_DECAY_MAX_INTERVAL	   30 *	24 * 60 * 60	/* one month */
अटल काष्ठा delayed_work cec_work;
अटल u64 decay_पूर्णांकerval = CEC_DECAY_DEFAULT_INTERVAL;

/*
 * Decrement decay value. We're using DECAY_BITS bits to denote decay of an
 * element in the array. On insertion and any access, it माला_लो reset to max.
 */
अटल व्योम करो_spring_cleaning(काष्ठा ce_array *ca)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ca->n; i++) अणु
		u8 decay = DECAY(ca->array[i]);

		अगर (!decay)
			जारी;

		decay--;

		ca->array[i] &= ~(DECAY_MASK << COUNT_BITS);
		ca->array[i] |= (decay << COUNT_BITS);
	पूर्ण
	ca->decay_count = 0;
	ca->decays_करोne++;
पूर्ण

/*
 * @पूर्णांकerval in seconds
 */
अटल व्योम cec_mod_work(अचिन्हित दीर्घ पूर्णांकerval)
अणु
	अचिन्हित दीर्घ iv;

	iv = पूर्णांकerval * HZ;
	mod_delayed_work(प्रणाली_wq, &cec_work, round_jअगरfies(iv));
पूर्ण

अटल व्योम cec_work_fn(काष्ठा work_काष्ठा *work)
अणु
	mutex_lock(&ce_mutex);
	करो_spring_cleaning(&ce_arr);
	mutex_unlock(&ce_mutex);

	cec_mod_work(decay_पूर्णांकerval);
पूर्ण

/*
 * @to: index of the smallest element which is >= then @pfn.
 *
 * Return the index of the pfn अगर found, otherwise negative value.
 */
अटल पूर्णांक __find_elem(काष्ठा ce_array *ca, u64 pfn, अचिन्हित पूर्णांक *to)
अणु
	पूर्णांक min = 0, max = ca->n - 1;
	u64 this_pfn;

	जबतक (min <= max) अणु
		पूर्णांक i = (min + max) >> 1;

		this_pfn = PFN(ca->array[i]);

		अगर (this_pfn < pfn)
			min = i + 1;
		अन्यथा अगर (this_pfn > pfn)
			max = i - 1;
		अन्यथा अगर (this_pfn == pfn) अणु
			अगर (to)
				*to = i;

			वापस i;
		पूर्ण
	पूर्ण

	/*
	 * When the loop terminates without finding @pfn, min has the index of
	 * the element slot where the new @pfn should be inserted. The loop
	 * terminates when min > max, which means the min index poपूर्णांकs to the
	 * bigger element जबतक the max index to the smaller element, in-between
	 * which the new @pfn beदीर्घs to.
	 *
	 * For more details, see exercise 1, Section 6.2.1 in TAOCP, vol. 3.
	 */
	अगर (to)
		*to = min;

	वापस -ENOKEY;
पूर्ण

अटल पूर्णांक find_elem(काष्ठा ce_array *ca, u64 pfn, अचिन्हित पूर्णांक *to)
अणु
	WARN_ON(!to);

	अगर (!ca->n) अणु
		*to = 0;
		वापस -ENOKEY;
	पूर्ण
	वापस __find_elem(ca, pfn, to);
पूर्ण

अटल व्योम del_elem(काष्ठा ce_array *ca, पूर्णांक idx)
अणु
	/* Save us a function call when deleting the last element. */
	अगर (ca->n - (idx + 1))
		स_हटाओ((व्योम *)&ca->array[idx],
			(व्योम *)&ca->array[idx + 1],
			(ca->n - (idx + 1)) * माप(u64));

	ca->n--;
पूर्ण

अटल u64 del_lru_elem_unlocked(काष्ठा ce_array *ca)
अणु
	अचिन्हित पूर्णांक min = FULL_COUNT_MASK;
	पूर्णांक i, min_idx = 0;

	क्रम (i = 0; i < ca->n; i++) अणु
		अचिन्हित पूर्णांक this = FULL_COUNT(ca->array[i]);

		अगर (min > this) अणु
			min = this;
			min_idx = i;
		पूर्ण
	पूर्ण

	del_elem(ca, min_idx);

	वापस PFN(ca->array[min_idx]);
पूर्ण

/*
 * We वापस the 0th pfn in the error हाल under the assumption that it cannot
 * be poisoned and excessive CEs in there are a serious deal anyway.
 */
अटल u64 __maybe_unused del_lru_elem(व्योम)
अणु
	काष्ठा ce_array *ca = &ce_arr;
	u64 pfn;

	अगर (!ca->n)
		वापस 0;

	mutex_lock(&ce_mutex);
	pfn = del_lru_elem_unlocked(ca);
	mutex_unlock(&ce_mutex);

	वापस pfn;
पूर्ण

अटल bool sanity_check(काष्ठा ce_array *ca)
अणु
	bool ret = false;
	u64 prev = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ca->n; i++) अणु
		u64 this = PFN(ca->array[i]);

		अगर (WARN(prev > this, "prev: 0x%016llx <-> this: 0x%016llx\n", prev, this))
			ret = true;

		prev = this;
	पूर्ण

	अगर (!ret)
		वापस ret;

	pr_info("Sanity check dump:\n{ n: %d\n", ca->n);
	क्रम (i = 0; i < ca->n; i++) अणु
		u64 this = PFN(ca->array[i]);

		pr_info(" %03d: [%016llx|%03llx]\n", i, this, FULL_COUNT(ca->array[i]));
	पूर्ण
	pr_info("}\n");

	वापस ret;
पूर्ण

/**
 * cec_add_elem - Add an element to the CEC array.
 * @pfn:	page frame number to insert
 *
 * Return values:
 * - <0:	on error
 * -  0:	on success
 * - >0:	when the inserted pfn was offlined
 */
अटल पूर्णांक cec_add_elem(u64 pfn)
अणु
	काष्ठा ce_array *ca = &ce_arr;
	पूर्णांक count, err, ret = 0;
	अचिन्हित पूर्णांक to = 0;

	/*
	 * We can be called very early on the identअगरy_cpu() path where we are
	 * not initialized yet. We ignore the error क्रम simplicity.
	 */
	अगर (!ce_arr.array || ce_arr.disabled)
		वापस -ENODEV;

	mutex_lock(&ce_mutex);

	ca->ces_entered++;

	/* Array full, मुक्त the LRU slot. */
	अगर (ca->n == MAX_ELEMS)
		WARN_ON(!del_lru_elem_unlocked(ca));

	err = find_elem(ca, pfn, &to);
	अगर (err < 0) अणु
		/*
		 * Shअगरt range [to-end] to make room क्रम one more element.
		 */
		स_हटाओ((व्योम *)&ca->array[to + 1],
			(व्योम *)&ca->array[to],
			(ca->n - to) * माप(u64));

		ca->array[to] = pfn << PAGE_SHIFT;
		ca->n++;
	पूर्ण

	/* Add/refresh element generation and increment count */
	ca->array[to] |= DECAY_MASK << COUNT_BITS;
	ca->array[to]++;

	/* Check action threshold and soft-offline, अगर reached. */
	count = COUNT(ca->array[to]);
	अगर (count >= action_threshold) अणु
		u64 pfn = ca->array[to] >> PAGE_SHIFT;

		अगर (!pfn_valid(pfn)) अणु
			pr_warn("CEC: Invalid pfn: 0x%llx\n", pfn);
		पूर्ण अन्यथा अणु
			/* We have reached max count क्रम this page, soft-offline it. */
			pr_err("Soft-offlining pfn: 0x%llx\n", pfn);
			memory_failure_queue(pfn, MF_SOFT_OFFLINE);
			ca->pfns_poisoned++;
		पूर्ण

		del_elem(ca, to);

		/*
		 * Return a >0 value to callers, to denote that we've reached
		 * the offlining threshold.
		 */
		ret = 1;

		जाओ unlock;
	पूर्ण

	ca->decay_count++;

	अगर (ca->decay_count >= CLEAN_ELEMS)
		करो_spring_cleaning(ca);

	WARN_ON_ONCE(sanity_check(ca));

unlock:
	mutex_unlock(&ce_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक u64_get(व्योम *data, u64 *val)
अणु
	*val = *(u64 *)data;

	वापस 0;
पूर्ण

अटल पूर्णांक pfn_set(व्योम *data, u64 val)
अणु
	*(u64 *)data = val;

	cec_add_elem(val);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(pfn_ops, u64_get, pfn_set, "0x%llx\n");

अटल पूर्णांक decay_पूर्णांकerval_set(व्योम *data, u64 val)
अणु
	अगर (val < CEC_DECAY_MIN_INTERVAL)
		वापस -EINVAL;

	अगर (val > CEC_DECAY_MAX_INTERVAL)
		वापस -EINVAL;

	*(u64 *)data   = val;
	decay_पूर्णांकerval = val;

	cec_mod_work(decay_पूर्णांकerval);

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(decay_पूर्णांकerval_ops, u64_get, decay_पूर्णांकerval_set, "%lld\n");

अटल पूर्णांक action_threshold_set(व्योम *data, u64 val)
अणु
	*(u64 *)data = val;

	अगर (val > COUNT_MASK)
		val = COUNT_MASK;

	action_threshold = val;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(action_threshold_ops, u64_get, action_threshold_set, "%lld\n");

अटल स्थिर अक्षर * स्थिर bins[] = अणु "00", "01", "10", "11" पूर्ण;

अटल पूर्णांक array_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ce_array *ca = &ce_arr;
	पूर्णांक i;

	mutex_lock(&ce_mutex);

	seq_म_लिखो(m, "{ n: %d\n", ca->n);
	क्रम (i = 0; i < ca->n; i++) अणु
		u64 this = PFN(ca->array[i]);

		seq_म_लिखो(m, " %3d: [%016llx|%s|%03llx]\n",
			   i, this, bins[DECAY(ca->array[i])], COUNT(ca->array[i]));
	पूर्ण

	seq_म_लिखो(m, "}\n");

	seq_म_लिखो(m, "Stats:\nCEs: %llu\nofflined pages: %llu\n",
		   ca->ces_entered, ca->pfns_poisoned);

	seq_म_लिखो(m, "Flags: 0x%x\n", ca->flags);

	seq_म_लिखो(m, "Decay interval: %lld seconds\n", decay_पूर्णांकerval);
	seq_म_लिखो(m, "Decays: %lld\n", ca->decays_करोne);

	seq_म_लिखो(m, "Action threshold: %lld\n", action_threshold);

	mutex_unlock(&ce_mutex);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(array);

अटल पूर्णांक __init create_debugfs_nodes(व्योम)
अणु
	काष्ठा dentry *d, *pfn, *decay, *count, *array;

	d = debugfs_create_dir("cec", ras_debugfs_dir);
	अगर (!d) अणु
		pr_warn("Error creating cec debugfs node!\n");
		वापस -1;
	पूर्ण

	decay = debugfs_create_file("decay_interval", S_IRUSR | S_IWUSR, d,
				    &decay_पूर्णांकerval, &decay_पूर्णांकerval_ops);
	अगर (!decay) अणु
		pr_warn("Error creating decay_interval debugfs node!\n");
		जाओ err;
	पूर्ण

	count = debugfs_create_file("action_threshold", S_IRUSR | S_IWUSR, d,
				    &action_threshold, &action_threshold_ops);
	अगर (!count) अणु
		pr_warn("Error creating action_threshold debugfs node!\n");
		जाओ err;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_RAS_CEC_DEBUG))
		वापस 0;

	pfn = debugfs_create_file("pfn", S_IRUSR | S_IWUSR, d, &dfs_pfn, &pfn_ops);
	अगर (!pfn) अणु
		pr_warn("Error creating pfn debugfs node!\n");
		जाओ err;
	पूर्ण

	array = debugfs_create_file("array", S_IRUSR, d, शून्य, &array_fops);
	अगर (!array) अणु
		pr_warn("Error creating array debugfs node!\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	debugfs_हटाओ_recursive(d);

	वापस 1;
पूर्ण

अटल पूर्णांक cec_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			व्योम *data)
अणु
	काष्ठा mce *m = (काष्ठा mce *)data;

	अगर (!m)
		वापस NOTIFY_DONE;

	/* We eat only correctable DRAM errors with usable addresses. */
	अगर (mce_is_memory_error(m) &&
	    mce_is_correctable(m)  &&
	    mce_usable_address(m)) अणु
		अगर (!cec_add_elem(m->addr >> PAGE_SHIFT)) अणु
			m->kflags |= MCE_HANDLED_CEC;
			वापस NOTIFY_OK;
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block cec_nb = अणु
	.notअगरier_call	= cec_notअगरier,
	.priority	= MCE_PRIO_CEC,
पूर्ण;

अटल पूर्णांक __init cec_init(व्योम)
अणु
	अगर (ce_arr.disabled)
		वापस -ENODEV;

	ce_arr.array = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!ce_arr.array) अणु
		pr_err("Error allocating CE array page!\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (create_debugfs_nodes()) अणु
		मुक्त_page((अचिन्हित दीर्घ)ce_arr.array);
		वापस -ENOMEM;
	पूर्ण

	INIT_DELAYED_WORK(&cec_work, cec_work_fn);
	schedule_delayed_work(&cec_work, CEC_DECAY_DEFAULT_INTERVAL);

	mce_रेजिस्टर_decode_chain(&cec_nb);

	pr_info("Correctable Errors collector initialized.\n");
	वापस 0;
पूर्ण
late_initcall(cec_init);

पूर्णांक __init parse_cec_param(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;

	अगर (*str == '=')
		str++;

	अगर (!म_भेद(str, "cec_disable"))
		ce_arr.disabled = 1;
	अन्यथा
		वापस 0;

	वापस 1;
पूर्ण
