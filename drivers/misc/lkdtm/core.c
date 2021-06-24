<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux Kernel Dump Test Module क्रम testing kernel crashes conditions:
 * induces प्रणाली failures at predefined crashpoपूर्णांकs and under predefined
 * operational conditions in order to evaluate the reliability of kernel
 * sanity checking and crash dumps obtained using dअगरferent dumping
 * solutions.
 *
 * Copyright (C) IBM Corporation, 2006
 *
 * Author: Ankita Garg <ankita@in.ibm.com>
 *
 * It is adapted from the Linux Kernel Dump Test Tool by
 * Fernanकरो Luis Vazquez Cao <http://lkdtt.sourceक्रमge.net>
 *
 * Debugfs support added by Simon Kagstrom <simon.kagstrom@netinsight.net>
 *
 * See Documentation/fault-injection/provoke-crashes.rst क्रम inकाष्ठाions
 */
#समावेश "lkdtm.h"
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>

#घोषणा DEFAULT_COUNT 10

अटल पूर्णांक lkdपंचांग_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार lkdपंचांग_debugfs_पढ़ो(काष्ठा file *f, अक्षर __user *user_buf,
		माप_प्रकार count, loff_t *off);
अटल sमाप_प्रकार direct_entry(काष्ठा file *f, स्थिर अक्षर __user *user_buf,
			    माप_प्रकार count, loff_t *off);

#अगर_घोषित CONFIG_KPROBES
अटल पूर्णांक lkdपंचांग_kprobe_handler(काष्ठा kprobe *kp, काष्ठा pt_regs *regs);
अटल sमाप_प्रकार lkdपंचांग_debugfs_entry(काष्ठा file *f,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *off);
# define CRASHPOINT_KPROBE(_symbol)				\
		.kprobe = अणु					\
			.symbol_name = (_symbol),		\
			.pre_handler = lkdपंचांग_kprobe_handler,	\
		पूर्ण,
# define CRASHPOINT_WRITE(_symbol)				\
		(_symbol) ? lkdपंचांग_debugfs_entry : direct_entry
#अन्यथा
# define CRASHPOINT_KPROBE(_symbol)
# define CRASHPOINT_WRITE(_symbol)		direct_entry
#पूर्ण_अगर

/* Crash poपूर्णांकs */
काष्ठा crashpoपूर्णांक अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations fops;
	काष्ठा kprobe kprobe;
पूर्ण;

#घोषणा CRASHPOINT(_name, _symbol)				\
	अणु							\
		.name = _name,					\
		.fops = अणु					\
			.पढ़ो	= lkdपंचांग_debugfs_पढ़ो,		\
			.llseek	= generic_file_llseek,		\
			.खोलो	= lkdपंचांग_debugfs_खोलो,		\
			.ग_लिखो	= CRASHPOINT_WRITE(_symbol)	\
		पूर्ण,						\
		CRASHPOINT_KPROBE(_symbol)			\
	पूर्ण

/* Define the possible places where we can trigger a crash poपूर्णांक. */
अटल काष्ठा crashpoपूर्णांक crashpoपूर्णांकs[] = अणु
	CRASHPOINT("DIRECT",		 शून्य),
#अगर_घोषित CONFIG_KPROBES
	CRASHPOINT("INT_HARDWARE_ENTRY", "do_IRQ"),
	CRASHPOINT("INT_HW_IRQ_EN",	 "handle_irq_event"),
	CRASHPOINT("INT_TASKLET_ENTRY",	 "tasklet_action"),
	CRASHPOINT("FS_DEVRW",		 "ll_rw_block"),
	CRASHPOINT("MEM_SWAPOUT",	 "shrink_inactive_list"),
	CRASHPOINT("TIMERADD",		 "hrtimer_start"),
	CRASHPOINT("SCSI_DISPATCH_CMD",	 "scsi_dispatch_cmd"),
	CRASHPOINT("IDE_CORE_CP",	 "generic_ide_ioctl"),
#पूर्ण_अगर
पूर्ण;


/* Crash types. */
काष्ठा crashtype अणु
	स्थिर अक्षर *name;
	व्योम (*func)(व्योम);
पूर्ण;

#घोषणा CRASHTYPE(_name)			\
	अणु					\
		.name = __stringअगरy(_name),	\
		.func = lkdपंचांग_ ## _name,	\
	पूर्ण

/* Define the possible types of crashes that can be triggered. */
अटल स्थिर काष्ठा crashtype crashtypes[] = अणु
	CRASHTYPE(PANIC),
	CRASHTYPE(BUG),
	CRASHTYPE(WARNING),
	CRASHTYPE(WARNING_MESSAGE),
	CRASHTYPE(EXCEPTION),
	CRASHTYPE(LOOP),
	CRASHTYPE(EXHAUST_STACK),
	CRASHTYPE(CORRUPT_STACK),
	CRASHTYPE(CORRUPT_STACK_STRONG),
	CRASHTYPE(REPORT_STACK),
	CRASHTYPE(CORRUPT_LIST_ADD),
	CRASHTYPE(CORRUPT_LIST_DEL),
	CRASHTYPE(STACK_GUARD_PAGE_LEADING),
	CRASHTYPE(STACK_GUARD_PAGE_TRAILING),
	CRASHTYPE(UNSET_SMEP),
	CRASHTYPE(CORRUPT_PAC),
	CRASHTYPE(UNALIGNED_LOAD_STORE_WRITE),
	CRASHTYPE(FORTIFY_OBJECT),
	CRASHTYPE(FORTIFY_SUBOBJECT),
	CRASHTYPE(OVERWRITE_ALLOCATION),
	CRASHTYPE(WRITE_AFTER_FREE),
	CRASHTYPE(READ_AFTER_FREE),
	CRASHTYPE(WRITE_BUDDY_AFTER_FREE),
	CRASHTYPE(READ_BUDDY_AFTER_FREE),
	CRASHTYPE(SLAB_FREE_DOUBLE),
	CRASHTYPE(SLAB_FREE_CROSS),
	CRASHTYPE(SLAB_FREE_PAGE),
	CRASHTYPE(SOFTLOCKUP),
	CRASHTYPE(HARDLOCKUP),
	CRASHTYPE(SPINLOCKUP),
	CRASHTYPE(HUNG_TASK),
	CRASHTYPE(OVERFLOW_SIGNED),
	CRASHTYPE(OVERFLOW_UNSIGNED),
	CRASHTYPE(ARRAY_BOUNDS),
	CRASHTYPE(EXEC_DATA),
	CRASHTYPE(EXEC_STACK),
	CRASHTYPE(EXEC_KMALLOC),
	CRASHTYPE(EXEC_VMALLOC),
	CRASHTYPE(EXEC_RODATA),
	CRASHTYPE(EXEC_USERSPACE),
	CRASHTYPE(EXEC_शून्य),
	CRASHTYPE(ACCESS_USERSPACE),
	CRASHTYPE(ACCESS_शून्य),
	CRASHTYPE(WRITE_RO),
	CRASHTYPE(WRITE_RO_AFTER_INIT),
	CRASHTYPE(WRITE_KERN),
	CRASHTYPE(REFCOUNT_INC_OVERFLOW),
	CRASHTYPE(REFCOUNT_ADD_OVERFLOW),
	CRASHTYPE(REFCOUNT_INC_NOT_ZERO_OVERFLOW),
	CRASHTYPE(REFCOUNT_ADD_NOT_ZERO_OVERFLOW),
	CRASHTYPE(REFCOUNT_DEC_ZERO),
	CRASHTYPE(REFCOUNT_DEC_NEGATIVE),
	CRASHTYPE(REFCOUNT_DEC_AND_TEST_NEGATIVE),
	CRASHTYPE(REFCOUNT_SUB_AND_TEST_NEGATIVE),
	CRASHTYPE(REFCOUNT_INC_ZERO),
	CRASHTYPE(REFCOUNT_ADD_ZERO),
	CRASHTYPE(REFCOUNT_INC_SATURATED),
	CRASHTYPE(REFCOUNT_DEC_SATURATED),
	CRASHTYPE(REFCOUNT_ADD_SATURATED),
	CRASHTYPE(REFCOUNT_INC_NOT_ZERO_SATURATED),
	CRASHTYPE(REFCOUNT_ADD_NOT_ZERO_SATURATED),
	CRASHTYPE(REFCOUNT_DEC_AND_TEST_SATURATED),
	CRASHTYPE(REFCOUNT_SUB_AND_TEST_SATURATED),
	CRASHTYPE(REFCOUNT_TIMING),
	CRASHTYPE(ATOMIC_TIMING),
	CRASHTYPE(USERCOPY_HEAP_SIZE_TO),
	CRASHTYPE(USERCOPY_HEAP_SIZE_FROM),
	CRASHTYPE(USERCOPY_HEAP_WHITELIST_TO),
	CRASHTYPE(USERCOPY_HEAP_WHITELIST_FROM),
	CRASHTYPE(USERCOPY_STACK_FRAME_TO),
	CRASHTYPE(USERCOPY_STACK_FRAME_FROM),
	CRASHTYPE(USERCOPY_STACK_BEYOND),
	CRASHTYPE(USERCOPY_KERNEL),
	CRASHTYPE(STACKLEAK_ERASING),
	CRASHTYPE(CFI_FORWARD_PROTO),
	CRASHTYPE(FORTIFIED_STRSCPY),
#अगर_घोषित CONFIG_X86_32
	CRASHTYPE(DOUBLE_FAULT),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	CRASHTYPE(PPC_SLB_MULTIHIT),
#पूर्ण_अगर
पूर्ण;


/* Global kprobe entry and crashtype. */
अटल काष्ठा kprobe *lkdपंचांग_kprobe;
अटल काष्ठा crashpoपूर्णांक *lkdपंचांग_crashpoपूर्णांक;
अटल स्थिर काष्ठा crashtype *lkdपंचांग_crashtype;

/* Module parameters */
अटल पूर्णांक recur_count = -1;
module_param(recur_count, पूर्णांक, 0644);
MODULE_PARM_DESC(recur_count, " Recursion level for the stack overflow test");

अटल अक्षर* cpoपूर्णांक_name;
module_param(cpoपूर्णांक_name, अक्षरp, 0444);
MODULE_PARM_DESC(cpoपूर्णांक_name, " Crash Point, where kernel is to be crashed");

अटल अक्षर* cpoपूर्णांक_type;
module_param(cpoपूर्णांक_type, अक्षरp, 0444);
MODULE_PARM_DESC(cpoपूर्णांक_type, " Crash Point Type, action to be taken on "\
				"hitting the crash point");

अटल पूर्णांक cpoपूर्णांक_count = DEFAULT_COUNT;
module_param(cpoपूर्णांक_count, पूर्णांक, 0644);
MODULE_PARM_DESC(cpoपूर्णांक_count, " Crash Point Count, number of times the "\
				"crash point is to be hit to trigger action");


/* Return the crashtype number or शून्य अगर the name is invalid */
अटल स्थिर काष्ठा crashtype *find_crashtype(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(crashtypes); i++) अणु
		अगर (!म_भेद(name, crashtypes[i].name))
			वापस &crashtypes[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * This is क्रमced noअंतरभूत just so it distinctly shows up in the stackdump
 * which makes validation of expected lkdपंचांग crashes easier.
 */
अटल noअंतरभूत व्योम lkdपंचांग_करो_action(स्थिर काष्ठा crashtype *crashtype)
अणु
	अगर (WARN_ON(!crashtype || !crashtype->func))
		वापस;
	crashtype->func();
पूर्ण

अटल पूर्णांक lkdपंचांग_रेजिस्टर_cpoपूर्णांक(काष्ठा crashpoपूर्णांक *crashpoपूर्णांक,
				 स्थिर काष्ठा crashtype *crashtype)
अणु
	पूर्णांक ret;

	/* If this करोesn't have a symbol, just call immediately. */
	अगर (!crashpoपूर्णांक->kprobe.symbol_name) अणु
		lkdपंचांग_करो_action(crashtype);
		वापस 0;
	पूर्ण

	अगर (lkdपंचांग_kprobe != शून्य)
		unरेजिस्टर_kprobe(lkdपंचांग_kprobe);

	lkdपंचांग_crashpoपूर्णांक = crashpoपूर्णांक;
	lkdपंचांग_crashtype = crashtype;
	lkdपंचांग_kprobe = &crashpoपूर्णांक->kprobe;
	ret = रेजिस्टर_kprobe(lkdपंचांग_kprobe);
	अगर (ret < 0) अणु
		pr_info("Couldn't register kprobe %s\n",
			crashpoपूर्णांक->kprobe.symbol_name);
		lkdपंचांग_kprobe = शून्य;
		lkdपंचांग_crashpoपूर्णांक = शून्य;
		lkdपंचांग_crashtype = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_KPROBES
/* Global crash counter and spinlock. */
अटल पूर्णांक crash_count = DEFAULT_COUNT;
अटल DEFINE_SPINLOCK(crash_count_lock);

/* Called by kprobe entry poपूर्णांकs. */
अटल पूर्णांक lkdपंचांग_kprobe_handler(काष्ठा kprobe *kp, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;
	bool करो_it = false;

	अगर (WARN_ON(!lkdपंचांग_crashpoपूर्णांक || !lkdपंचांग_crashtype))
		वापस 0;

	spin_lock_irqsave(&crash_count_lock, flags);
	crash_count--;
	pr_info("Crash point %s of type %s hit, trigger in %d rounds\n",
		lkdपंचांग_crashpoपूर्णांक->name, lkdपंचांग_crashtype->name, crash_count);

	अगर (crash_count == 0) अणु
		करो_it = true;
		crash_count = cpoपूर्णांक_count;
	पूर्ण
	spin_unlock_irqrestore(&crash_count_lock, flags);

	अगर (करो_it)
		lkdपंचांग_करो_action(lkdपंचांग_crashtype);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार lkdपंचांग_debugfs_entry(काष्ठा file *f,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *off)
अणु
	काष्ठा crashpoपूर्णांक *crashpoपूर्णांक = file_inode(f)->i_निजी;
	स्थिर काष्ठा crashtype *crashtype = शून्य;
	अक्षर *buf;
	पूर्णांक err;

	अगर (count >= PAGE_SIZE)
		वापस -EINVAL;

	buf = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	अगर (copy_from_user(buf, user_buf, count)) अणु
		मुक्त_page((अचिन्हित दीर्घ) buf);
		वापस -EFAULT;
	पूर्ण
	/* शून्य-terminate and हटाओ enter */
	buf[count] = '\0';
	strim(buf);

	crashtype = find_crashtype(buf);
	मुक्त_page((अचिन्हित दीर्घ)buf);

	अगर (!crashtype)
		वापस -EINVAL;

	err = lkdपंचांग_रेजिस्टर_cpoपूर्णांक(crashpoपूर्णांक, crashtype);
	अगर (err < 0)
		वापस err;

	*off += count;

	वापस count;
पूर्ण
#पूर्ण_अगर

/* Generic पढ़ो callback that just prपूर्णांकs out the available crash types */
अटल sमाप_प्रकार lkdपंचांग_debugfs_पढ़ो(काष्ठा file *f, अक्षर __user *user_buf,
		माप_प्रकार count, loff_t *off)
अणु
	अक्षर *buf;
	पूर्णांक i, n, out;

	buf = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	n = scnम_लिखो(buf, PAGE_SIZE, "Available crash types:\n");
	क्रम (i = 0; i < ARRAY_SIZE(crashtypes); i++) अणु
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "%s\n",
			      crashtypes[i].name);
	पूर्ण
	buf[n] = '\0';

	out = simple_पढ़ो_from_buffer(user_buf, count, off,
				      buf, n);
	मुक्त_page((अचिन्हित दीर्घ) buf);

	वापस out;
पूर्ण

अटल पूर्णांक lkdपंचांग_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/* Special entry to just crash directly. Available without KPROBEs */
अटल sमाप_प्रकार direct_entry(काष्ठा file *f, स्थिर अक्षर __user *user_buf,
		माप_प्रकार count, loff_t *off)
अणु
	स्थिर काष्ठा crashtype *crashtype;
	अक्षर *buf;

	अगर (count >= PAGE_SIZE)
		वापस -EINVAL;
	अगर (count < 1)
		वापस -EINVAL;

	buf = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	अगर (copy_from_user(buf, user_buf, count)) अणु
		मुक्त_page((अचिन्हित दीर्घ) buf);
		वापस -EFAULT;
	पूर्ण
	/* शून्य-terminate and हटाओ enter */
	buf[count] = '\0';
	strim(buf);

	crashtype = find_crashtype(buf);
	मुक्त_page((अचिन्हित दीर्घ) buf);
	अगर (!crashtype)
		वापस -EINVAL;

	pr_info("Performing direct entry %s\n", crashtype->name);
	lkdपंचांग_करो_action(crashtype);
	*off += count;

	वापस count;
पूर्ण

अटल काष्ठा dentry *lkdपंचांग_debugfs_root;

अटल पूर्णांक __init lkdपंचांग_module_init(व्योम)
अणु
	काष्ठा crashpoपूर्णांक *crashpoपूर्णांक = शून्य;
	स्थिर काष्ठा crashtype *crashtype = शून्य;
	पूर्णांक ret;
	पूर्णांक i;

	/* Neither or both of these need to be set */
	अगर ((cpoपूर्णांक_type || cpoपूर्णांक_name) && !(cpoपूर्णांक_type && cpoपूर्णांक_name)) अणु
		pr_err("Need both cpoint_type and cpoint_name or neither\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cpoपूर्णांक_type) अणु
		crashtype = find_crashtype(cpoपूर्णांक_type);
		अगर (!crashtype) अणु
			pr_err("Unknown crashtype '%s'\n", cpoपूर्णांक_type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (cpoपूर्णांक_name) अणु
		क्रम (i = 0; i < ARRAY_SIZE(crashpoपूर्णांकs); i++) अणु
			अगर (!म_भेद(cpoपूर्णांक_name, crashpoपूर्णांकs[i].name))
				crashpoपूर्णांक = &crashpoपूर्णांकs[i];
		पूर्ण

		/* Refuse unknown crashpoपूर्णांकs. */
		अगर (!crashpoपूर्णांक) अणु
			pr_err("Invalid crashpoint %s\n", cpoपूर्णांक_name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_KPROBES
	/* Set crash count. */
	crash_count = cpoपूर्णांक_count;
#पूर्ण_अगर

	/* Handle test-specअगरic initialization. */
	lkdपंचांग_bugs_init(&recur_count);
	lkdपंचांग_perms_init();
	lkdपंचांग_usercopy_init();
	lkdपंचांग_heap_init();

	/* Register debugfs पूर्णांकerface */
	lkdपंचांग_debugfs_root = debugfs_create_dir("provoke-crash", शून्य);

	/* Install debugfs trigger files. */
	क्रम (i = 0; i < ARRAY_SIZE(crashpoपूर्णांकs); i++) अणु
		काष्ठा crashpoपूर्णांक *cur = &crashpoपूर्णांकs[i];

		debugfs_create_file(cur->name, 0644, lkdपंचांग_debugfs_root, cur,
				    &cur->fops);
	पूर्ण

	/* Install crashpoपूर्णांक अगर one was selected. */
	अगर (crashpoपूर्णांक) अणु
		ret = lkdपंचांग_रेजिस्टर_cpoपूर्णांक(crashpoपूर्णांक, crashtype);
		अगर (ret < 0) अणु
			pr_info("Invalid crashpoint %s\n", crashpoपूर्णांक->name);
			जाओ out_err;
		पूर्ण
		pr_info("Crash point %s of type %s registered\n",
			crashpoपूर्णांक->name, cpoपूर्णांक_type);
	पूर्ण अन्यथा अणु
		pr_info("No crash points registered, enable through debugfs\n");
	पूर्ण

	वापस 0;

out_err:
	debugfs_हटाओ_recursive(lkdपंचांग_debugfs_root);
	वापस ret;
पूर्ण

अटल व्योम __निकास lkdपंचांग_module_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(lkdपंचांग_debugfs_root);

	/* Handle test-specअगरic clean-up. */
	lkdपंचांग_heap_निकास();
	lkdपंचांग_usercopy_निकास();

	अगर (lkdपंचांग_kprobe != शून्य)
		unरेजिस्टर_kprobe(lkdपंचांग_kprobe);

	pr_info("Crash point unregistered\n");
पूर्ण

module_init(lkdपंचांग_module_init);
module_निकास(lkdपंचांग_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel crash testing module");
