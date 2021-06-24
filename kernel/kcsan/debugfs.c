<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KCSAN debugfs पूर्णांकerface.
 *
 * Copyright (C) 2019, Google LLC.
 */

#घोषणा pr_fmt(fmt) "kcsan: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/bug.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>

#समावेश "kcsan.h"

atomic_दीर्घ_t kcsan_counters[KCSAN_COUNTER_COUNT];
अटल स्थिर अक्षर *स्थिर counter_names[] = अणु
	[KCSAN_COUNTER_USED_WATCHPOINTS]		= "used_watchpoints",
	[KCSAN_COUNTER_SETUP_WATCHPOINTS]		= "setup_watchpoints",
	[KCSAN_COUNTER_DATA_RACES]			= "data_races",
	[KCSAN_COUNTER_ASSERT_FAILURES]			= "assert_failures",
	[KCSAN_COUNTER_NO_CAPACITY]			= "no_capacity",
	[KCSAN_COUNTER_REPORT_RACES]			= "report_races",
	[KCSAN_COUNTER_RACES_UNKNOWN_ORIGIN]		= "races_unknown_origin",
	[KCSAN_COUNTER_UNENCODABLE_ACCESSES]		= "unencodable_accesses",
	[KCSAN_COUNTER_ENCODING_FALSE_POSITIVES]	= "encoding_false_positives",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(counter_names) == KCSAN_COUNTER_COUNT);

/*
 * Addresses क्रम filtering functions from reporting. This list can be used as a
 * whitelist or blacklist.
 */
अटल काष्ठा अणु
	अचिन्हित दीर्घ	*addrs;		/* array of addresses */
	माप_प्रकार		size;		/* current size */
	पूर्णांक		used;		/* number of elements used */
	bool		sorted;		/* अगर elements are sorted */
	bool		whitelist;	/* अगर list is a blacklist or whitelist */
पूर्ण report_filterlist = अणु
	.addrs		= शून्य,
	.size		= 8,		/* small initial size */
	.used		= 0,
	.sorted		= false,
	.whitelist	= false,	/* शेष is blacklist */
पूर्ण;
अटल DEFINE_SPINLOCK(report_filterlist_lock);

/*
 * The microbenchmark allows benchmarking KCSAN core runसमय only. To run
 * multiple thपढ़ोs, pipe 'microbench=<iters>' from multiple tasks पूर्णांकo the
 * debugfs file. This will not generate any conflicts, and tests fast-path only.
 */
अटल noअंतरभूत व्योम microbenchmark(अचिन्हित दीर्घ iters)
अणु
	स्थिर काष्ठा kcsan_ctx ctx_save = current->kcsan_ctx;
	स्थिर bool was_enabled = READ_ONCE(kcsan_enabled);
	cycles_t cycles;

	/* We may have been called from an atomic region; reset context. */
	स_रखो(&current->kcsan_ctx, 0, माप(current->kcsan_ctx));
	/*
	 * Disable to benchmark fast-path क्रम all accesses, and (expected
	 * negligible) call पूर्णांकo slow-path, but never set up watchpoपूर्णांकs.
	 */
	WRITE_ONCE(kcsan_enabled, false);

	pr_info("%s begin | iters: %lu\n", __func__, iters);

	cycles = get_cycles();
	जबतक (iters--) अणु
		अचिन्हित दीर्घ addr = iters & ((PAGE_SIZE << 8) - 1);
		पूर्णांक type = !(iters & 0x7f) ? KCSAN_ACCESS_ATOMIC :
				(!(iters & 0xf) ? KCSAN_ACCESS_WRITE : 0);
		__kcsan_check_access((व्योम *)addr, माप(दीर्घ), type);
	पूर्ण
	cycles = get_cycles() - cycles;

	pr_info("%s end   | cycles: %llu\n", __func__, cycles);

	WRITE_ONCE(kcsan_enabled, was_enabled);
	/* restore context */
	current->kcsan_ctx = ctx_save;
पूर्ण

अटल पूर्णांक cmp_filterlist_addrs(स्थिर व्योम *rhs, स्थिर व्योम *lhs)
अणु
	स्थिर अचिन्हित दीर्घ a = *(स्थिर अचिन्हित दीर्घ *)rhs;
	स्थिर अचिन्हित दीर्घ b = *(स्थिर अचिन्हित दीर्घ *)lhs;

	वापस a < b ? -1 : a == b ? 0 : 1;
पूर्ण

bool kcsan_skip_report_debugfs(अचिन्हित दीर्घ func_addr)
अणु
	अचिन्हित दीर्घ symbolsize, offset;
	अचिन्हित दीर्घ flags;
	bool ret = false;

	अगर (!kallsyms_lookup_size_offset(func_addr, &symbolsize, &offset))
		वापस false;
	func_addr -= offset; /* Get function start */

	spin_lock_irqsave(&report_filterlist_lock, flags);
	अगर (report_filterlist.used == 0)
		जाओ out;

	/* Sort array अगर it is unsorted, and then करो a binary search. */
	अगर (!report_filterlist.sorted) अणु
		sort(report_filterlist.addrs, report_filterlist.used,
		     माप(अचिन्हित दीर्घ), cmp_filterlist_addrs, शून्य);
		report_filterlist.sorted = true;
	पूर्ण
	ret = !!द्वा_खोज(&func_addr, report_filterlist.addrs,
			report_filterlist.used, माप(अचिन्हित दीर्घ),
			cmp_filterlist_addrs);
	अगर (report_filterlist.whitelist)
		ret = !ret;

out:
	spin_unlock_irqrestore(&report_filterlist_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम set_report_filterlist_whitelist(bool whitelist)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&report_filterlist_lock, flags);
	report_filterlist.whitelist = whitelist;
	spin_unlock_irqrestore(&report_filterlist_lock, flags);
पूर्ण

/* Returns 0 on success, error-code otherwise. */
अटल sमाप_प्रकार insert_report_filterlist(स्थिर अक्षर *func)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ addr = kallsyms_lookup_name(func);
	sमाप_प्रकार ret = 0;

	अगर (!addr) अणु
		pr_err("could not find function: '%s'\n", func);
		वापस -ENOENT;
	पूर्ण

	spin_lock_irqsave(&report_filterlist_lock, flags);

	अगर (report_filterlist.addrs == शून्य) अणु
		/* initial allocation */
		report_filterlist.addrs =
			kदो_स्मृति_array(report_filterlist.size,
				      माप(अचिन्हित दीर्घ), GFP_ATOMIC);
		अगर (report_filterlist.addrs == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (report_filterlist.used == report_filterlist.size) अणु
		/* resize filterlist */
		माप_प्रकार new_size = report_filterlist.size * 2;
		अचिन्हित दीर्घ *new_addrs =
			kपुनः_स्मृति(report_filterlist.addrs,
				 new_size * माप(अचिन्हित दीर्घ), GFP_ATOMIC);

		अगर (new_addrs == शून्य) अणु
			/* leave filterlist itself untouched */
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		report_filterlist.size = new_size;
		report_filterlist.addrs = new_addrs;
	पूर्ण

	/* Note: deduplicating should be करोne in userspace. */
	report_filterlist.addrs[report_filterlist.used++] =
		kallsyms_lookup_name(func);
	report_filterlist.sorted = false;

out:
	spin_unlock_irqrestore(&report_filterlist_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक show_info(काष्ठा seq_file *file, व्योम *v)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/* show stats */
	seq_म_लिखो(file, "enabled: %i\n", READ_ONCE(kcsan_enabled));
	क्रम (i = 0; i < KCSAN_COUNTER_COUNT; ++i) अणु
		seq_म_लिखो(file, "%s: %ld\n", counter_names[i],
			   atomic_दीर्घ_पढ़ो(&kcsan_counters[i]));
	पूर्ण

	/* show filter functions, and filter type */
	spin_lock_irqsave(&report_filterlist_lock, flags);
	seq_म_लिखो(file, "\n%s functions: %s\n",
		   report_filterlist.whitelist ? "whitelisted" : "blacklisted",
		   report_filterlist.used == 0 ? "none" : "");
	क्रम (i = 0; i < report_filterlist.used; ++i)
		seq_म_लिखो(file, " %ps\n", (व्योम *)report_filterlist.addrs[i]);
	spin_unlock_irqrestore(&report_filterlist_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, show_info, शून्य);
पूर्ण

अटल sमाप_प्रकार
debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *off)
अणु
	अक्षर kbuf[KSYM_NAME_LEN];
	अक्षर *arg;
	पूर्णांक पढ़ो_len = count < (माप(kbuf) - 1) ? count : (माप(kbuf) - 1);

	अगर (copy_from_user(kbuf, buf, पढ़ो_len))
		वापस -EFAULT;
	kbuf[पढ़ो_len] = '\0';
	arg = म_मालाip(kbuf);

	अगर (!म_भेद(arg, "on")) अणु
		WRITE_ONCE(kcsan_enabled, true);
	पूर्ण अन्यथा अगर (!म_भेद(arg, "off")) अणु
		WRITE_ONCE(kcsan_enabled, false);
	पूर्ण अन्यथा अगर (str_has_prefix(arg, "microbench=")) अणु
		अचिन्हित दीर्घ iters;

		अगर (kम_से_अदीर्घ(&arg[म_माप("microbench=")], 0, &iters))
			वापस -EINVAL;
		microbenchmark(iters);
	पूर्ण अन्यथा अगर (!म_भेद(arg, "whitelist")) अणु
		set_report_filterlist_whitelist(true);
	पूर्ण अन्यथा अगर (!म_भेद(arg, "blacklist")) अणु
		set_report_filterlist_whitelist(false);
	पूर्ण अन्यथा अगर (arg[0] == '!') अणु
		sमाप_प्रकार ret = insert_report_filterlist(&arg[1]);

		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_ops =
अणु
	.पढ़ो	 = seq_पढ़ो,
	.खोलो	 = debugfs_खोलो,
	.ग_लिखो	 = debugfs_ग_लिखो,
	.release = single_release
पूर्ण;

अटल पूर्णांक __init kcsan_debugfs_init(व्योम)
अणु
	debugfs_create_file("kcsan", 0644, शून्य, शून्य, &debugfs_ops);
	वापस 0;
पूर्ण

late_initcall(kcsan_debugfs_init);
