<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Security plug functions
 *
 * Copyright (C) 2001 WireX Communications, Inc <chris@wirex.com>
 * Copyright (C) 2001-2002 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2001 Networks Associates Technology, Inc <ssmalley@nai.com>
 * Copyright (C) 2016 Mellanox Technologies
 */

#घोषणा pr_fmt(fmt) "LSM: " fmt

#समावेश <linux/bpf.h>
#समावेश <linux/capability.h>
#समावेश <linux/dcache.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/पूर्णांकegrity.h>
#समावेश <linux/ima.h>
#समावेश <linux/evm.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/mman.h>
#समावेश <linux/mount.h>
#समावेश <linux/personality.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/माला.स>
#समावेश <linux/msg.h>
#समावेश <net/flow.h>

#घोषणा MAX_LSM_EVM_XATTR	2

/* How many LSMs were built पूर्णांकo the kernel? */
#घोषणा LSM_COUNT (__end_lsm_info - __start_lsm_info)

/*
 * These are descriptions of the reasons that can be passed to the
 * security_locked_करोwn() LSM hook. Placing this array here allows
 * all security modules to use the same descriptions क्रम auditing
 * purposes.
 */
स्थिर अक्षर *स्थिर lockकरोwn_reasons[LOCKDOWN_CONFIDENTIALITY_MAX+1] = अणु
	[LOCKDOWN_NONE] = "none",
	[LOCKDOWN_MODULE_SIGNATURE] = "unsigned module loading",
	[LOCKDOWN_DEV_MEM] = "/dev/mem,kmem,port",
	[LOCKDOWN_EFI_TEST] = "/dev/efi_test access",
	[LOCKDOWN_KEXEC] = "kexec of unsigned images",
	[LOCKDOWN_HIBERNATION] = "hibernation",
	[LOCKDOWN_PCI_ACCESS] = "direct PCI access",
	[LOCKDOWN_IOPORT] = "raw io port access",
	[LOCKDOWN_MSR] = "raw MSR access",
	[LOCKDOWN_ACPI_TABLES] = "modifying ACPI tables",
	[LOCKDOWN_PCMCIA_CIS] = "direct PCMCIA CIS storage",
	[LOCKDOWN_TIOCSSERIAL] = "reconfiguration of serial port IO",
	[LOCKDOWN_MODULE_PARAMETERS] = "unsafe module parameters",
	[LOCKDOWN_MMIOTRACE] = "unsafe mmio",
	[LOCKDOWN_DEBUGFS] = "debugfs access",
	[LOCKDOWN_XMON_WR] = "xmon write access",
	[LOCKDOWN_INTEGRITY_MAX] = "integrity",
	[LOCKDOWN_KCORE] = "/proc/kcore access",
	[LOCKDOWN_KPROBES] = "use of kprobes",
	[LOCKDOWN_BPF_READ] = "use of bpf to read kernel RAM",
	[LOCKDOWN_PERF] = "unsafe use of perf",
	[LOCKDOWN_TRACEFS] = "use of tracefs",
	[LOCKDOWN_XMON_RW] = "xmon read and write access",
	[LOCKDOWN_XFRM_SECRET] = "xfrm SA secret",
	[LOCKDOWN_CONFIDENTIALITY_MAX] = "confidentiality",
पूर्ण;

काष्ठा security_hook_heads security_hook_heads __lsm_ro_after_init;
अटल BLOCKING_NOTIFIER_HEAD(blocking_lsm_notअगरier_chain);

अटल काष्ठा kmem_cache *lsm_file_cache;
अटल काष्ठा kmem_cache *lsm_inode_cache;

अक्षर *lsm_names;
अटल काष्ठा lsm_blob_sizes blob_sizes __lsm_ro_after_init;

/* Boot-समय LSM user choice */
अटल __initdata स्थिर अक्षर *chosen_lsm_order;
अटल __initdata स्थिर अक्षर *chosen_major_lsm;

अटल __initस्थिर स्थिर अक्षर * स्थिर builtin_lsm_order = CONFIG_LSM;

/* Ordered list of LSMs to initialize. */
अटल __initdata काष्ठा lsm_info **ordered_lsms;
अटल __initdata काष्ठा lsm_info *exclusive;

अटल __initdata bool debug;
#घोषणा init_debug(...)						\
	करो अणु							\
		अगर (debug)					\
			pr_info(__VA_ARGS__);			\
	पूर्ण जबतक (0)

अटल bool __init is_enabled(काष्ठा lsm_info *lsm)
अणु
	अगर (!lsm->enabled)
		वापस false;

	वापस *lsm->enabled;
पूर्ण

/* Mark an LSM's enabled flag. */
अटल पूर्णांक lsm_enabled_true __initdata = 1;
अटल पूर्णांक lsm_enabled_false __initdata = 0;
अटल व्योम __init set_enabled(काष्ठा lsm_info *lsm, bool enabled)
अणु
	/*
	 * When an LSM hasn't configured an enable variable, we can use
	 * a hard-coded location क्रम storing the शेष enabled state.
	 */
	अगर (!lsm->enabled) अणु
		अगर (enabled)
			lsm->enabled = &lsm_enabled_true;
		अन्यथा
			lsm->enabled = &lsm_enabled_false;
	पूर्ण अन्यथा अगर (lsm->enabled == &lsm_enabled_true) अणु
		अगर (!enabled)
			lsm->enabled = &lsm_enabled_false;
	पूर्ण अन्यथा अगर (lsm->enabled == &lsm_enabled_false) अणु
		अगर (enabled)
			lsm->enabled = &lsm_enabled_true;
	पूर्ण अन्यथा अणु
		*lsm->enabled = enabled;
	पूर्ण
पूर्ण

/* Is an LSM alपढ़ोy listed in the ordered LSMs list? */
अटल bool __init exists_ordered_lsm(काष्ठा lsm_info *lsm)
अणु
	काष्ठा lsm_info **check;

	क्रम (check = ordered_lsms; *check; check++)
		अगर (*check == lsm)
			वापस true;

	वापस false;
पूर्ण

/* Append an LSM to the list of ordered LSMs to initialize. */
अटल पूर्णांक last_lsm __initdata;
अटल व्योम __init append_ordered_lsm(काष्ठा lsm_info *lsm, स्थिर अक्षर *from)
अणु
	/* Ignore duplicate selections. */
	अगर (exists_ordered_lsm(lsm))
		वापस;

	अगर (WARN(last_lsm == LSM_COUNT, "%s: out of LSM slots!?\n", from))
		वापस;

	/* Enable this LSM, अगर it is not alपढ़ोy set. */
	अगर (!lsm->enabled)
		lsm->enabled = &lsm_enabled_true;
	ordered_lsms[last_lsm++] = lsm;

	init_debug("%s ordering: %s (%sabled)\n", from, lsm->name,
		   is_enabled(lsm) ? "en" : "dis");
पूर्ण

/* Is an LSM allowed to be initialized? */
अटल bool __init lsm_allowed(काष्ठा lsm_info *lsm)
अणु
	/* Skip अगर the LSM is disabled. */
	अगर (!is_enabled(lsm))
		वापस false;

	/* Not allowed अगर another exclusive LSM alपढ़ोy initialized. */
	अगर ((lsm->flags & LSM_FLAG_EXCLUSIVE) && exclusive) अणु
		init_debug("exclusive disabled: %s\n", lsm->name);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम __init lsm_set_blob_size(पूर्णांक *need, पूर्णांक *lbs)
अणु
	पूर्णांक offset;

	अगर (*need > 0) अणु
		offset = *lbs;
		*lbs += *need;
		*need = offset;
	पूर्ण
पूर्ण

अटल व्योम __init lsm_set_blob_sizes(काष्ठा lsm_blob_sizes *needed)
अणु
	अगर (!needed)
		वापस;

	lsm_set_blob_size(&needed->lbs_cred, &blob_sizes.lbs_cred);
	lsm_set_blob_size(&needed->lbs_file, &blob_sizes.lbs_file);
	/*
	 * The inode blob माला_लो an rcu_head in addition to
	 * what the modules might need.
	 */
	अगर (needed->lbs_inode && blob_sizes.lbs_inode == 0)
		blob_sizes.lbs_inode = माप(काष्ठा rcu_head);
	lsm_set_blob_size(&needed->lbs_inode, &blob_sizes.lbs_inode);
	lsm_set_blob_size(&needed->lbs_ipc, &blob_sizes.lbs_ipc);
	lsm_set_blob_size(&needed->lbs_msg_msg, &blob_sizes.lbs_msg_msg);
	lsm_set_blob_size(&needed->lbs_superblock, &blob_sizes.lbs_superblock);
	lsm_set_blob_size(&needed->lbs_task, &blob_sizes.lbs_task);
पूर्ण

/* Prepare LSM क्रम initialization. */
अटल व्योम __init prepare_lsm(काष्ठा lsm_info *lsm)
अणु
	पूर्णांक enabled = lsm_allowed(lsm);

	/* Record enablement (to handle any following exclusive LSMs). */
	set_enabled(lsm, enabled);

	/* If enabled, करो pre-initialization work. */
	अगर (enabled) अणु
		अगर ((lsm->flags & LSM_FLAG_EXCLUSIVE) && !exclusive) अणु
			exclusive = lsm;
			init_debug("exclusive chosen: %s\n", lsm->name);
		पूर्ण

		lsm_set_blob_sizes(lsm->blobs);
	पूर्ण
पूर्ण

/* Initialize a given LSM, अगर it is enabled. */
अटल व्योम __init initialize_lsm(काष्ठा lsm_info *lsm)
अणु
	अगर (is_enabled(lsm)) अणु
		पूर्णांक ret;

		init_debug("initializing %s\n", lsm->name);
		ret = lsm->init();
		WARN(ret, "%s failed to initialize: %d\n", lsm->name, ret);
	पूर्ण
पूर्ण

/* Populate ordered LSMs list from comma-separated LSM name list. */
अटल व्योम __init ordered_lsm_parse(स्थिर अक्षर *order, स्थिर अक्षर *origin)
अणु
	काष्ठा lsm_info *lsm;
	अक्षर *sep, *name, *next;

	/* LSM_ORDER_FIRST is always first. */
	क्रम (lsm = __start_lsm_info; lsm < __end_lsm_info; lsm++) अणु
		अगर (lsm->order == LSM_ORDER_FIRST)
			append_ordered_lsm(lsm, "first");
	पूर्ण

	/* Process "security=", अगर given. */
	अगर (chosen_major_lsm) अणु
		काष्ठा lsm_info *major;

		/*
		 * To match the original "security=" behavior, this
		 * explicitly करोes NOT fallback to another Legacy Major
		 * अगर the selected one was separately disabled: disable
		 * all non-matching Legacy Major LSMs.
		 */
		क्रम (major = __start_lsm_info; major < __end_lsm_info;
		     major++) अणु
			अगर ((major->flags & LSM_FLAG_LEGACY_MAJOR) &&
			    म_भेद(major->name, chosen_major_lsm) != 0) अणु
				set_enabled(major, false);
				init_debug("security=%s disabled: %s\n",
					   chosen_major_lsm, major->name);
			पूर्ण
		पूर्ण
	पूर्ण

	sep = kstrdup(order, GFP_KERNEL);
	next = sep;
	/* Walk the list, looking क्रम matching LSMs. */
	जबतक ((name = strsep(&next, ",")) != शून्य) अणु
		bool found = false;

		क्रम (lsm = __start_lsm_info; lsm < __end_lsm_info; lsm++) अणु
			अगर (lsm->order == LSM_ORDER_MUTABLE &&
			    म_भेद(lsm->name, name) == 0) अणु
				append_ordered_lsm(lsm, origin);
				found = true;
			पूर्ण
		पूर्ण

		अगर (!found)
			init_debug("%s ignored: %s\n", origin, name);
	पूर्ण

	/* Process "security=", अगर given. */
	अगर (chosen_major_lsm) अणु
		क्रम (lsm = __start_lsm_info; lsm < __end_lsm_info; lsm++) अणु
			अगर (exists_ordered_lsm(lsm))
				जारी;
			अगर (म_भेद(lsm->name, chosen_major_lsm) == 0)
				append_ordered_lsm(lsm, "security=");
		पूर्ण
	पूर्ण

	/* Disable all LSMs not in the ordered list. */
	क्रम (lsm = __start_lsm_info; lsm < __end_lsm_info; lsm++) अणु
		अगर (exists_ordered_lsm(lsm))
			जारी;
		set_enabled(lsm, false);
		init_debug("%s disabled: %s\n", origin, lsm->name);
	पूर्ण

	kमुक्त(sep);
पूर्ण

अटल व्योम __init lsm_early_cred(काष्ठा cred *cred);
अटल व्योम __init lsm_early_task(काष्ठा task_काष्ठा *task);

अटल पूर्णांक lsm_append(स्थिर अक्षर *new, अक्षर **result);

अटल व्योम __init ordered_lsm_init(व्योम)
अणु
	काष्ठा lsm_info **lsm;

	ordered_lsms = kसुस्मृति(LSM_COUNT + 1, माप(*ordered_lsms),
				GFP_KERNEL);

	अगर (chosen_lsm_order) अणु
		अगर (chosen_major_lsm) अणु
			pr_info("security= is ignored because it is superseded by lsm=\n");
			chosen_major_lsm = शून्य;
		पूर्ण
		ordered_lsm_parse(chosen_lsm_order, "cmdline");
	पूर्ण अन्यथा
		ordered_lsm_parse(builtin_lsm_order, "builtin");

	क्रम (lsm = ordered_lsms; *lsm; lsm++)
		prepare_lsm(*lsm);

	init_debug("cred blob size       = %d\n", blob_sizes.lbs_cred);
	init_debug("file blob size       = %d\n", blob_sizes.lbs_file);
	init_debug("inode blob size      = %d\n", blob_sizes.lbs_inode);
	init_debug("ipc blob size        = %d\n", blob_sizes.lbs_ipc);
	init_debug("msg_msg blob size    = %d\n", blob_sizes.lbs_msg_msg);
	init_debug("superblock blob size = %d\n", blob_sizes.lbs_superblock);
	init_debug("task blob size       = %d\n", blob_sizes.lbs_task);

	/*
	 * Create any kmem_caches needed क्रम blobs
	 */
	अगर (blob_sizes.lbs_file)
		lsm_file_cache = kmem_cache_create("lsm_file_cache",
						   blob_sizes.lbs_file, 0,
						   SLAB_PANIC, शून्य);
	अगर (blob_sizes.lbs_inode)
		lsm_inode_cache = kmem_cache_create("lsm_inode_cache",
						    blob_sizes.lbs_inode, 0,
						    SLAB_PANIC, शून्य);

	lsm_early_cred((काष्ठा cred *) current->cred);
	lsm_early_task(current);
	क्रम (lsm = ordered_lsms; *lsm; lsm++)
		initialize_lsm(*lsm);

	kमुक्त(ordered_lsms);
पूर्ण

पूर्णांक __init early_security_init(व्योम)
अणु
	पूर्णांक i;
	काष्ठा hlist_head *list = (काष्ठा hlist_head *) &security_hook_heads;
	काष्ठा lsm_info *lsm;

	क्रम (i = 0; i < माप(security_hook_heads) / माप(काष्ठा hlist_head);
	     i++)
		INIT_HLIST_HEAD(&list[i]);

	क्रम (lsm = __start_early_lsm_info; lsm < __end_early_lsm_info; lsm++) अणु
		अगर (!lsm->enabled)
			lsm->enabled = &lsm_enabled_true;
		prepare_lsm(lsm);
		initialize_lsm(lsm);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * security_init - initializes the security framework
 *
 * This should be called early in the kernel initialization sequence.
 */
पूर्णांक __init security_init(व्योम)
अणु
	काष्ठा lsm_info *lsm;

	pr_info("Security Framework initializing\n");

	/*
	 * Append the names of the early LSM modules now that kदो_स्मृति() is
	 * available
	 */
	क्रम (lsm = __start_early_lsm_info; lsm < __end_early_lsm_info; lsm++) अणु
		अगर (lsm->enabled)
			lsm_append(lsm->name, &lsm_names);
	पूर्ण

	/* Load LSMs in specअगरied order. */
	ordered_lsm_init();

	वापस 0;
पूर्ण

/* Save user chosen LSM */
अटल पूर्णांक __init choose_major_lsm(अक्षर *str)
अणु
	chosen_major_lsm = str;
	वापस 1;
पूर्ण
__setup("security=", choose_major_lsm);

/* Explicitly choose LSM initialization order. */
अटल पूर्णांक __init choose_lsm_order(अक्षर *str)
अणु
	chosen_lsm_order = str;
	वापस 1;
पूर्ण
__setup("lsm=", choose_lsm_order);

/* Enable LSM order debugging. */
अटल पूर्णांक __init enable_debug(अक्षर *str)
अणु
	debug = true;
	वापस 1;
पूर्ण
__setup("lsm.debug", enable_debug);

अटल bool match_last_lsm(स्थिर अक्षर *list, स्थिर अक्षर *lsm)
अणु
	स्थिर अक्षर *last;

	अगर (WARN_ON(!list || !lsm))
		वापस false;
	last = म_खोजप(list, ',');
	अगर (last)
		/* Pass the comma, म_भेद() will check क्रम '\0' */
		last++;
	अन्यथा
		last = list;
	वापस !म_भेद(last, lsm);
पूर्ण

अटल पूर्णांक lsm_append(स्थिर अक्षर *new, अक्षर **result)
अणु
	अक्षर *cp;

	अगर (*result == शून्य) अणु
		*result = kstrdup(new, GFP_KERNEL);
		अगर (*result == शून्य)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/* Check अगर it is the last रेजिस्टरed name */
		अगर (match_last_lsm(*result, new))
			वापस 0;
		cp = kaप्र_लिखो(GFP_KERNEL, "%s,%s", *result, new);
		अगर (cp == शून्य)
			वापस -ENOMEM;
		kमुक्त(*result);
		*result = cp;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * security_add_hooks - Add a modules hooks to the hook lists.
 * @hooks: the hooks to add
 * @count: the number of hooks to add
 * @lsm: the name of the security module
 *
 * Each LSM has to रेजिस्टर its hooks with the infraकाष्ठाure.
 */
व्योम __init security_add_hooks(काष्ठा security_hook_list *hooks, पूर्णांक count,
				अक्षर *lsm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		hooks[i].lsm = lsm;
		hlist_add_tail_rcu(&hooks[i].list, hooks[i].head);
	पूर्ण

	/*
	 * Don't try to append during early_security_init(), we'll come back
	 * and fix this up afterwards.
	 */
	अगर (slab_is_available()) अणु
		अगर (lsm_append(lsm, &lsm_names) < 0)
			panic("%s - Cannot get early memory.\n", __func__);
	पूर्ण
पूर्ण

पूर्णांक call_blocking_lsm_notअगरier(क्रमागत lsm_event event, व्योम *data)
अणु
	वापस blocking_notअगरier_call_chain(&blocking_lsm_notअगरier_chain,
					    event, data);
पूर्ण
EXPORT_SYMBOL(call_blocking_lsm_notअगरier);

पूर्णांक रेजिस्टर_blocking_lsm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&blocking_lsm_notअगरier_chain,
						nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_blocking_lsm_notअगरier);

पूर्णांक unरेजिस्टर_blocking_lsm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&blocking_lsm_notअगरier_chain,
						  nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_blocking_lsm_notअगरier);

/**
 * lsm_cred_alloc - allocate a composite cred blob
 * @cred: the cred that needs a blob
 * @gfp: allocation type
 *
 * Allocate the cred blob क्रम all the modules
 *
 * Returns 0, or -ENOMEM अगर memory can't be allocated.
 */
अटल पूर्णांक lsm_cred_alloc(काष्ठा cred *cred, gfp_t gfp)
अणु
	अगर (blob_sizes.lbs_cred == 0) अणु
		cred->security = शून्य;
		वापस 0;
	पूर्ण

	cred->security = kzalloc(blob_sizes.lbs_cred, gfp);
	अगर (cred->security == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * lsm_early_cred - during initialization allocate a composite cred blob
 * @cred: the cred that needs a blob
 *
 * Allocate the cred blob क्रम all the modules
 */
अटल व्योम __init lsm_early_cred(काष्ठा cred *cred)
अणु
	पूर्णांक rc = lsm_cred_alloc(cred, GFP_KERNEL);

	अगर (rc)
		panic("%s: Early cred alloc failed.\n", __func__);
पूर्ण

/**
 * lsm_file_alloc - allocate a composite file blob
 * @file: the file that needs a blob
 *
 * Allocate the file blob क्रम all the modules
 *
 * Returns 0, or -ENOMEM अगर memory can't be allocated.
 */
अटल पूर्णांक lsm_file_alloc(काष्ठा file *file)
अणु
	अगर (!lsm_file_cache) अणु
		file->f_security = शून्य;
		वापस 0;
	पूर्ण

	file->f_security = kmem_cache_zalloc(lsm_file_cache, GFP_KERNEL);
	अगर (file->f_security == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * lsm_inode_alloc - allocate a composite inode blob
 * @inode: the inode that needs a blob
 *
 * Allocate the inode blob क्रम all the modules
 *
 * Returns 0, or -ENOMEM अगर memory can't be allocated.
 */
पूर्णांक lsm_inode_alloc(काष्ठा inode *inode)
अणु
	अगर (!lsm_inode_cache) अणु
		inode->i_security = शून्य;
		वापस 0;
	पूर्ण

	inode->i_security = kmem_cache_zalloc(lsm_inode_cache, GFP_NOFS);
	अगर (inode->i_security == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * lsm_task_alloc - allocate a composite task blob
 * @task: the task that needs a blob
 *
 * Allocate the task blob क्रम all the modules
 *
 * Returns 0, or -ENOMEM अगर memory can't be allocated.
 */
अटल पूर्णांक lsm_task_alloc(काष्ठा task_काष्ठा *task)
अणु
	अगर (blob_sizes.lbs_task == 0) अणु
		task->security = शून्य;
		वापस 0;
	पूर्ण

	task->security = kzalloc(blob_sizes.lbs_task, GFP_KERNEL);
	अगर (task->security == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * lsm_ipc_alloc - allocate a composite ipc blob
 * @kip: the ipc that needs a blob
 *
 * Allocate the ipc blob क्रम all the modules
 *
 * Returns 0, or -ENOMEM अगर memory can't be allocated.
 */
अटल पूर्णांक lsm_ipc_alloc(काष्ठा kern_ipc_perm *kip)
अणु
	अगर (blob_sizes.lbs_ipc == 0) अणु
		kip->security = शून्य;
		वापस 0;
	पूर्ण

	kip->security = kzalloc(blob_sizes.lbs_ipc, GFP_KERNEL);
	अगर (kip->security == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * lsm_msg_msg_alloc - allocate a composite msg_msg blob
 * @mp: the msg_msg that needs a blob
 *
 * Allocate the ipc blob क्रम all the modules
 *
 * Returns 0, or -ENOMEM अगर memory can't be allocated.
 */
अटल पूर्णांक lsm_msg_msg_alloc(काष्ठा msg_msg *mp)
अणु
	अगर (blob_sizes.lbs_msg_msg == 0) अणु
		mp->security = शून्य;
		वापस 0;
	पूर्ण

	mp->security = kzalloc(blob_sizes.lbs_msg_msg, GFP_KERNEL);
	अगर (mp->security == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * lsm_early_task - during initialization allocate a composite task blob
 * @task: the task that needs a blob
 *
 * Allocate the task blob क्रम all the modules
 */
अटल व्योम __init lsm_early_task(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक rc = lsm_task_alloc(task);

	अगर (rc)
		panic("%s: Early task alloc failed.\n", __func__);
पूर्ण

/**
 * lsm_superblock_alloc - allocate a composite superblock blob
 * @sb: the superblock that needs a blob
 *
 * Allocate the superblock blob क्रम all the modules
 *
 * Returns 0, or -ENOMEM अगर memory can't be allocated.
 */
अटल पूर्णांक lsm_superblock_alloc(काष्ठा super_block *sb)
अणु
	अगर (blob_sizes.lbs_superblock == 0) अणु
		sb->s_security = शून्य;
		वापस 0;
	पूर्ण

	sb->s_security = kzalloc(blob_sizes.lbs_superblock, GFP_KERNEL);
	अगर (sb->s_security == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/*
 * The शेष value of the LSM hook is defined in linux/lsm_hook_defs.h and
 * can be accessed with:
 *
 *	LSM_RET_DEFAULT(<hook_name>)
 *
 * The macros below define अटल स्थिरants क्रम the शेष value of each
 * LSM hook.
 */
#घोषणा LSM_RET_DEFAULT(NAME) (NAME##_शेष)
#घोषणा DECLARE_LSM_RET_DEFAULT_व्योम(DEFAULT, NAME)
#घोषणा DECLARE_LSM_RET_DEFAULT_पूर्णांक(DEFAULT, NAME) \
	अटल स्थिर पूर्णांक LSM_RET_DEFAULT(NAME) = (DEFAULT);
#घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...) \
	DECLARE_LSM_RET_DEFAULT_##RET(DEFAULT, NAME)

#समावेश <linux/lsm_hook_defs.h>
#अघोषित LSM_HOOK

/*
 * Hook list operation macros.
 *
 * call_व्योम_hook:
 *	This is a hook that करोes not वापस a value.
 *
 * call_पूर्णांक_hook:
 *	This is a hook that वापसs a value.
 */

#घोषणा call_व्योम_hook(FUNC, ...)				\
	करो अणु							\
		काष्ठा security_hook_list *P;			\
								\
		hlist_क्रम_each_entry(P, &security_hook_heads.FUNC, list) \
			P->hook.FUNC(__VA_ARGS__);		\
	पूर्ण जबतक (0)

#घोषणा call_पूर्णांक_hook(FUNC, IRC, ...) (अणु			\
	पूर्णांक RC = IRC;						\
	करो अणु							\
		काष्ठा security_hook_list *P;			\
								\
		hlist_क्रम_each_entry(P, &security_hook_heads.FUNC, list) अणु \
			RC = P->hook.FUNC(__VA_ARGS__);		\
			अगर (RC != 0)				\
				अवरोध;				\
		पूर्ण						\
	पूर्ण जबतक (0);						\
	RC;							\
पूर्ण)

/* Security operations */

पूर्णांक security_binder_set_context_mgr(काष्ठा task_काष्ठा *mgr)
अणु
	वापस call_पूर्णांक_hook(binder_set_context_mgr, 0, mgr);
पूर्ण

पूर्णांक security_binder_transaction(काष्ठा task_काष्ठा *from,
				काष्ठा task_काष्ठा *to)
अणु
	वापस call_पूर्णांक_hook(binder_transaction, 0, from, to);
पूर्ण

पूर्णांक security_binder_transfer_binder(काष्ठा task_काष्ठा *from,
				    काष्ठा task_काष्ठा *to)
अणु
	वापस call_पूर्णांक_hook(binder_transfer_binder, 0, from, to);
पूर्ण

पूर्णांक security_binder_transfer_file(काष्ठा task_काष्ठा *from,
				  काष्ठा task_काष्ठा *to, काष्ठा file *file)
अणु
	वापस call_पूर्णांक_hook(binder_transfer_file, 0, from, to, file);
पूर्ण

पूर्णांक security_ptrace_access_check(काष्ठा task_काष्ठा *child, अचिन्हित पूर्णांक mode)
अणु
	वापस call_पूर्णांक_hook(ptrace_access_check, 0, child, mode);
पूर्ण

पूर्णांक security_ptrace_traceme(काष्ठा task_काष्ठा *parent)
अणु
	वापस call_पूर्णांक_hook(ptrace_traceme, 0, parent);
पूर्ण

पूर्णांक security_capget(काष्ठा task_काष्ठा *target,
		     kernel_cap_t *effective,
		     kernel_cap_t *inheritable,
		     kernel_cap_t *permitted)
अणु
	वापस call_पूर्णांक_hook(capget, 0, target,
				effective, inheritable, permitted);
पूर्ण

पूर्णांक security_capset(काष्ठा cred *new, स्थिर काष्ठा cred *old,
		    स्थिर kernel_cap_t *effective,
		    स्थिर kernel_cap_t *inheritable,
		    स्थिर kernel_cap_t *permitted)
अणु
	वापस call_पूर्णांक_hook(capset, 0, new, old,
				effective, inheritable, permitted);
पूर्ण

पूर्णांक security_capable(स्थिर काष्ठा cred *cred,
		     काष्ठा user_namespace *ns,
		     पूर्णांक cap,
		     अचिन्हित पूर्णांक opts)
अणु
	वापस call_पूर्णांक_hook(capable, 0, cred, ns, cap, opts);
पूर्ण

पूर्णांक security_quotactl(पूर्णांक cmds, पूर्णांक type, पूर्णांक id, काष्ठा super_block *sb)
अणु
	वापस call_पूर्णांक_hook(quotactl, 0, cmds, type, id, sb);
पूर्ण

पूर्णांक security_quota_on(काष्ठा dentry *dentry)
अणु
	वापस call_पूर्णांक_hook(quota_on, 0, dentry);
पूर्ण

पूर्णांक security_syslog(पूर्णांक type)
अणु
	वापस call_पूर्णांक_hook(syslog, 0, type);
पूर्ण

पूर्णांक security_समय_रखो64(स्थिर काष्ठा बारpec64 *ts, स्थिर काष्ठा समयzone *tz)
अणु
	वापस call_पूर्णांक_hook(समय_रखो, 0, ts, tz);
पूर्ण

पूर्णांक security_vm_enough_memory_mm(काष्ठा mm_काष्ठा *mm, दीर्घ pages)
अणु
	काष्ठा security_hook_list *hp;
	पूर्णांक cap_sys_admin = 1;
	पूर्णांक rc;

	/*
	 * The module will respond with a positive value अगर
	 * it thinks the __vm_enough_memory() call should be
	 * made with the cap_sys_admin set. If all of the modules
	 * agree that it should be set it will. If any module
	 * thinks it should not be set it won't.
	 */
	hlist_क्रम_each_entry(hp, &security_hook_heads.vm_enough_memory, list) अणु
		rc = hp->hook.vm_enough_memory(mm, pages);
		अगर (rc <= 0) अणु
			cap_sys_admin = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस __vm_enough_memory(mm, pages, cap_sys_admin);
पूर्ण

पूर्णांक security_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm)
अणु
	वापस call_पूर्णांक_hook(bprm_creds_क्रम_exec, 0, bprm);
पूर्ण

पूर्णांक security_bprm_creds_from_file(काष्ठा linux_binprm *bprm, काष्ठा file *file)
अणु
	वापस call_पूर्णांक_hook(bprm_creds_from_file, 0, bprm, file);
पूर्ण

पूर्णांक security_bprm_check(काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(bprm_check_security, 0, bprm);
	अगर (ret)
		वापस ret;
	वापस ima_bprm_check(bprm);
पूर्ण

व्योम security_bprm_committing_creds(काष्ठा linux_binprm *bprm)
अणु
	call_व्योम_hook(bprm_committing_creds, bprm);
पूर्ण

व्योम security_bprm_committed_creds(काष्ठा linux_binprm *bprm)
अणु
	call_व्योम_hook(bprm_committed_creds, bprm);
पूर्ण

पूर्णांक security_fs_context_dup(काष्ठा fs_context *fc, काष्ठा fs_context *src_fc)
अणु
	वापस call_पूर्णांक_hook(fs_context_dup, 0, fc, src_fc);
पूर्ण

पूर्णांक security_fs_context_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	वापस call_पूर्णांक_hook(fs_context_parse_param, -ENOPARAM, fc, param);
पूर्ण

पूर्णांक security_sb_alloc(काष्ठा super_block *sb)
अणु
	पूर्णांक rc = lsm_superblock_alloc(sb);

	अगर (unlikely(rc))
		वापस rc;
	rc = call_पूर्णांक_hook(sb_alloc_security, 0, sb);
	अगर (unlikely(rc))
		security_sb_मुक्त(sb);
	वापस rc;
पूर्ण

व्योम security_sb_delete(काष्ठा super_block *sb)
अणु
	call_व्योम_hook(sb_delete, sb);
पूर्ण

व्योम security_sb_मुक्त(काष्ठा super_block *sb)
अणु
	call_व्योम_hook(sb_मुक्त_security, sb);
	kमुक्त(sb->s_security);
	sb->s_security = शून्य;
पूर्ण

व्योम security_मुक्त_mnt_opts(व्योम **mnt_opts)
अणु
	अगर (!*mnt_opts)
		वापस;
	call_व्योम_hook(sb_मुक्त_mnt_opts, *mnt_opts);
	*mnt_opts = शून्य;
पूर्ण
EXPORT_SYMBOL(security_मुक्त_mnt_opts);

पूर्णांक security_sb_eat_lsm_opts(अक्षर *options, व्योम **mnt_opts)
अणु
	वापस call_पूर्णांक_hook(sb_eat_lsm_opts, 0, options, mnt_opts);
पूर्ण
EXPORT_SYMBOL(security_sb_eat_lsm_opts);

पूर्णांक security_sb_mnt_opts_compat(काष्ठा super_block *sb,
				व्योम *mnt_opts)
अणु
	वापस call_पूर्णांक_hook(sb_mnt_opts_compat, 0, sb, mnt_opts);
पूर्ण
EXPORT_SYMBOL(security_sb_mnt_opts_compat);

पूर्णांक security_sb_remount(काष्ठा super_block *sb,
			व्योम *mnt_opts)
अणु
	वापस call_पूर्णांक_hook(sb_remount, 0, sb, mnt_opts);
पूर्ण
EXPORT_SYMBOL(security_sb_remount);

पूर्णांक security_sb_kern_mount(काष्ठा super_block *sb)
अणु
	वापस call_पूर्णांक_hook(sb_kern_mount, 0, sb);
पूर्ण

पूर्णांक security_sb_show_options(काष्ठा seq_file *m, काष्ठा super_block *sb)
अणु
	वापस call_पूर्णांक_hook(sb_show_options, 0, m, sb);
पूर्ण

पूर्णांक security_sb_statfs(काष्ठा dentry *dentry)
अणु
	वापस call_पूर्णांक_hook(sb_statfs, 0, dentry);
पूर्ण

पूर्णांक security_sb_mount(स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
                       स्थिर अक्षर *type, अचिन्हित दीर्घ flags, व्योम *data)
अणु
	वापस call_पूर्णांक_hook(sb_mount, 0, dev_name, path, type, flags, data);
पूर्ण

पूर्णांक security_sb_umount(काष्ठा vfsmount *mnt, पूर्णांक flags)
अणु
	वापस call_पूर्णांक_hook(sb_umount, 0, mnt, flags);
पूर्ण

पूर्णांक security_sb_pivotroot(स्थिर काष्ठा path *old_path, स्थिर काष्ठा path *new_path)
अणु
	वापस call_पूर्णांक_hook(sb_pivotroot, 0, old_path, new_path);
पूर्ण

पूर्णांक security_sb_set_mnt_opts(काष्ठा super_block *sb,
				व्योम *mnt_opts,
				अचिन्हित दीर्घ kern_flags,
				अचिन्हित दीर्घ *set_kern_flags)
अणु
	वापस call_पूर्णांक_hook(sb_set_mnt_opts,
				mnt_opts ? -EOPNOTSUPP : 0, sb,
				mnt_opts, kern_flags, set_kern_flags);
पूर्ण
EXPORT_SYMBOL(security_sb_set_mnt_opts);

पूर्णांक security_sb_clone_mnt_opts(स्थिर काष्ठा super_block *oldsb,
				काष्ठा super_block *newsb,
				अचिन्हित दीर्घ kern_flags,
				अचिन्हित दीर्घ *set_kern_flags)
अणु
	वापस call_पूर्णांक_hook(sb_clone_mnt_opts, 0, oldsb, newsb,
				kern_flags, set_kern_flags);
पूर्ण
EXPORT_SYMBOL(security_sb_clone_mnt_opts);

पूर्णांक security_add_mnt_opt(स्थिर अक्षर *option, स्थिर अक्षर *val, पूर्णांक len,
			 व्योम **mnt_opts)
अणु
	वापस call_पूर्णांक_hook(sb_add_mnt_opt, -EINVAL,
					option, val, len, mnt_opts);
पूर्ण
EXPORT_SYMBOL(security_add_mnt_opt);

पूर्णांक security_move_mount(स्थिर काष्ठा path *from_path, स्थिर काष्ठा path *to_path)
अणु
	वापस call_पूर्णांक_hook(move_mount, 0, from_path, to_path);
पूर्ण

पूर्णांक security_path_notअगरy(स्थिर काष्ठा path *path, u64 mask,
				अचिन्हित पूर्णांक obj_type)
अणु
	वापस call_पूर्णांक_hook(path_notअगरy, 0, path, mask, obj_type);
पूर्ण

पूर्णांक security_inode_alloc(काष्ठा inode *inode)
अणु
	पूर्णांक rc = lsm_inode_alloc(inode);

	अगर (unlikely(rc))
		वापस rc;
	rc = call_पूर्णांक_hook(inode_alloc_security, 0, inode);
	अगर (unlikely(rc))
		security_inode_मुक्त(inode);
	वापस rc;
पूर्ण

अटल व्योम inode_मुक्त_by_rcu(काष्ठा rcu_head *head)
अणु
	/*
	 * The rcu head is at the start of the inode blob
	 */
	kmem_cache_मुक्त(lsm_inode_cache, head);
पूर्ण

व्योम security_inode_मुक्त(काष्ठा inode *inode)
अणु
	पूर्णांकegrity_inode_मुक्त(inode);
	call_व्योम_hook(inode_मुक्त_security, inode);
	/*
	 * The inode may still be referenced in a path walk and
	 * a call to security_inode_permission() can be made
	 * after inode_मुक्त_security() is called. Ideally, the VFS
	 * wouldn't करो this, but fixing that is a much harder
	 * job. For now, simply मुक्त the i_security via RCU, and
	 * leave the current inode->i_security poपूर्णांकer पूर्णांकact.
	 * The inode will be मुक्तd after the RCU grace period too.
	 */
	अगर (inode->i_security)
		call_rcu((काष्ठा rcu_head *)inode->i_security,
				inode_मुक्त_by_rcu);
पूर्ण

पूर्णांक security_dentry_init_security(काष्ठा dentry *dentry, पूर्णांक mode,
					स्थिर काष्ठा qstr *name, व्योम **ctx,
					u32 *ctxlen)
अणु
	वापस call_पूर्णांक_hook(dentry_init_security, -EOPNOTSUPP, dentry, mode,
				name, ctx, ctxlen);
पूर्ण
EXPORT_SYMBOL(security_dentry_init_security);

पूर्णांक security_dentry_create_files_as(काष्ठा dentry *dentry, पूर्णांक mode,
				    काष्ठा qstr *name,
				    स्थिर काष्ठा cred *old, काष्ठा cred *new)
अणु
	वापस call_पूर्णांक_hook(dentry_create_files_as, 0, dentry, mode,
				name, old, new);
पूर्ण
EXPORT_SYMBOL(security_dentry_create_files_as);

पूर्णांक security_inode_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				 स्थिर काष्ठा qstr *qstr,
				 स्थिर initxattrs initxattrs, व्योम *fs_data)
अणु
	काष्ठा xattr new_xattrs[MAX_LSM_EVM_XATTR + 1];
	काष्ठा xattr *lsm_xattr, *evm_xattr, *xattr;
	पूर्णांक ret;

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	अगर (!initxattrs)
		वापस call_पूर्णांक_hook(inode_init_security, -EOPNOTSUPP, inode,
				     dir, qstr, शून्य, शून्य, शून्य);
	स_रखो(new_xattrs, 0, माप(new_xattrs));
	lsm_xattr = new_xattrs;
	ret = call_पूर्णांक_hook(inode_init_security, -EOPNOTSUPP, inode, dir, qstr,
						&lsm_xattr->name,
						&lsm_xattr->value,
						&lsm_xattr->value_len);
	अगर (ret)
		जाओ out;

	evm_xattr = lsm_xattr + 1;
	ret = evm_inode_init_security(inode, lsm_xattr, evm_xattr);
	अगर (ret)
		जाओ out;
	ret = initxattrs(inode, new_xattrs, fs_data);
out:
	क्रम (xattr = new_xattrs; xattr->value != शून्य; xattr++)
		kमुक्त(xattr->value);
	वापस (ret == -EOPNOTSUPP) ? 0 : ret;
पूर्ण
EXPORT_SYMBOL(security_inode_init_security);

पूर्णांक security_inode_init_security_anon(काष्ठा inode *inode,
				      स्थिर काष्ठा qstr *name,
				      स्थिर काष्ठा inode *context_inode)
अणु
	वापस call_पूर्णांक_hook(inode_init_security_anon, 0, inode, name,
			     context_inode);
पूर्ण

पूर्णांक security_old_inode_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				     स्थिर काष्ठा qstr *qstr, स्थिर अक्षर **name,
				     व्योम **value, माप_प्रकार *len)
अणु
	अगर (unlikely(IS_PRIVATE(inode)))
		वापस -EOPNOTSUPP;
	वापस call_पूर्णांक_hook(inode_init_security, -EOPNOTSUPP, inode, dir,
			     qstr, name, value, len);
पूर्ण
EXPORT_SYMBOL(security_old_inode_init_security);

#अगर_घोषित CONFIG_SECURITY_PATH
पूर्णांक security_path_mknod(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry, umode_t mode,
			अचिन्हित पूर्णांक dev)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dir->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_mknod, 0, dir, dentry, mode, dev);
पूर्ण
EXPORT_SYMBOL(security_path_mknod);

पूर्णांक security_path_सूची_गढ़ो(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dir->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_सूची_गढ़ो, 0, dir, dentry, mode);
पूर्ण
EXPORT_SYMBOL(security_path_सूची_गढ़ो);

पूर्णांक security_path_सूची_हटाओ(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dir->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_सूची_हटाओ, 0, dir, dentry);
पूर्ण

पूर्णांक security_path_unlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dir->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_unlink, 0, dir, dentry);
पूर्ण
EXPORT_SYMBOL(security_path_unlink);

पूर्णांक security_path_symlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
			  स्थिर अक्षर *old_name)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dir->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_symlink, 0, dir, dentry, old_name);
पूर्ण

पूर्णांक security_path_link(काष्ठा dentry *old_dentry, स्थिर काष्ठा path *new_dir,
		       काष्ठा dentry *new_dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(old_dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_link, 0, old_dentry, new_dir, new_dentry);
पूर्ण

पूर्णांक security_path_नाम(स्थिर काष्ठा path *old_dir, काष्ठा dentry *old_dentry,
			 स्थिर काष्ठा path *new_dir, काष्ठा dentry *new_dentry,
			 अचिन्हित पूर्णांक flags)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(old_dentry)) ||
		     (d_is_positive(new_dentry) && IS_PRIVATE(d_backing_inode(new_dentry)))))
		वापस 0;

	अगर (flags & RENAME_EXCHANGE) अणु
		पूर्णांक err = call_पूर्णांक_hook(path_नाम, 0, new_dir, new_dentry,
					old_dir, old_dentry);
		अगर (err)
			वापस err;
	पूर्ण

	वापस call_पूर्णांक_hook(path_नाम, 0, old_dir, old_dentry, new_dir,
				new_dentry);
पूर्ण
EXPORT_SYMBOL(security_path_नाम);

पूर्णांक security_path_truncate(स्थिर काष्ठा path *path)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(path->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_truncate, 0, path);
पूर्ण

पूर्णांक security_path_chmod(स्थिर काष्ठा path *path, umode_t mode)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(path->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_chmod, 0, path, mode);
पूर्ण

पूर्णांक security_path_chown(स्थिर काष्ठा path *path, kuid_t uid, kgid_t gid)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(path->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(path_chown, 0, path, uid, gid);
पूर्ण

पूर्णांक security_path_chroot(स्थिर काष्ठा path *path)
अणु
	वापस call_पूर्णांक_hook(path_chroot, 0, path);
पूर्ण
#पूर्ण_अगर

पूर्णांक security_inode_create(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	अगर (unlikely(IS_PRIVATE(dir)))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_create, 0, dir, dentry, mode);
पूर्ण
EXPORT_SYMBOL_GPL(security_inode_create);

पूर्णांक security_inode_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			 काष्ठा dentry *new_dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(old_dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_link, 0, old_dentry, dir, new_dentry);
पूर्ण

पूर्णांक security_inode_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_unlink, 0, dir, dentry);
पूर्ण

पूर्णांक security_inode_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry,
			    स्थिर अक्षर *old_name)
अणु
	अगर (unlikely(IS_PRIVATE(dir)))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_symlink, 0, dir, dentry, old_name);
पूर्ण

पूर्णांक security_inode_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	अगर (unlikely(IS_PRIVATE(dir)))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_सूची_गढ़ो, 0, dir, dentry, mode);
पूर्ण
EXPORT_SYMBOL_GPL(security_inode_सूची_गढ़ो);

पूर्णांक security_inode_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_सूची_हटाओ, 0, dir, dentry);
पूर्ण

पूर्णांक security_inode_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	अगर (unlikely(IS_PRIVATE(dir)))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_mknod, 0, dir, dentry, mode, dev);
पूर्ण

पूर्णांक security_inode_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			   काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			   अचिन्हित पूर्णांक flags)
अणु
        अगर (unlikely(IS_PRIVATE(d_backing_inode(old_dentry)) ||
            (d_is_positive(new_dentry) && IS_PRIVATE(d_backing_inode(new_dentry)))))
		वापस 0;

	अगर (flags & RENAME_EXCHANGE) अणु
		पूर्णांक err = call_पूर्णांक_hook(inode_नाम, 0, new_dir, new_dentry,
						     old_dir, old_dentry);
		अगर (err)
			वापस err;
	पूर्ण

	वापस call_पूर्णांक_hook(inode_नाम, 0, old_dir, old_dentry,
					   new_dir, new_dentry);
पूर्ण

पूर्णांक security_inode_पढ़ोlink(काष्ठा dentry *dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_पढ़ोlink, 0, dentry);
पूर्ण

पूर्णांक security_inode_follow_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
			       bool rcu)
अणु
	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_follow_link, 0, dentry, inode, rcu);
पूर्ण

पूर्णांक security_inode_permission(काष्ठा inode *inode, पूर्णांक mask)
अणु
	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_permission, 0, inode, mask);
पूर्ण

पूर्णांक security_inode_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	पूर्णांक ret;

	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	ret = call_पूर्णांक_hook(inode_setattr, 0, dentry, attr);
	अगर (ret)
		वापस ret;
	वापस evm_inode_setattr(dentry, attr);
पूर्ण
EXPORT_SYMBOL_GPL(security_inode_setattr);

पूर्णांक security_inode_getattr(स्थिर काष्ठा path *path)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(path->dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_getattr, 0, path);
पूर्ण

पूर्णांक security_inode_setxattr(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, स्थिर अक्षर *name,
			    स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक ret;

	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	/*
	 * SELinux and Smack पूर्णांकegrate the cap call,
	 * so assume that all LSMs supplying this call करो so.
	 */
	ret = call_पूर्णांक_hook(inode_setxattr, 1, mnt_userns, dentry, name, value,
			    size, flags);

	अगर (ret == 1)
		ret = cap_inode_setxattr(dentry, name, value, size, flags);
	अगर (ret)
		वापस ret;
	ret = ima_inode_setxattr(dentry, name, value, size);
	अगर (ret)
		वापस ret;
	वापस evm_inode_setxattr(dentry, name, value, size);
पूर्ण

व्योम security_inode_post_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
				  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस;
	call_व्योम_hook(inode_post_setxattr, dentry, name, value, size, flags);
	evm_inode_post_setxattr(dentry, name, value, size);
पूर्ण

पूर्णांक security_inode_getxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_getxattr, 0, dentry, name);
पूर्ण

पूर्णांक security_inode_listxattr(काष्ठा dentry *dentry)
अणु
	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_listxattr, 0, dentry);
पूर्ण

पूर्णांक security_inode_हटाओxattr(काष्ठा user_namespace *mnt_userns,
			       काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;
	/*
	 * SELinux and Smack पूर्णांकegrate the cap call,
	 * so assume that all LSMs supplying this call करो so.
	 */
	ret = call_पूर्णांक_hook(inode_हटाओxattr, 1, mnt_userns, dentry, name);
	अगर (ret == 1)
		ret = cap_inode_हटाओxattr(mnt_userns, dentry, name);
	अगर (ret)
		वापस ret;
	ret = ima_inode_हटाओxattr(dentry, name);
	अगर (ret)
		वापस ret;
	वापस evm_inode_हटाओxattr(dentry, name);
पूर्ण

पूर्णांक security_inode_need_समाप्तpriv(काष्ठा dentry *dentry)
अणु
	वापस call_पूर्णांक_hook(inode_need_समाप्तpriv, 0, dentry);
पूर्ण

पूर्णांक security_inode_समाप्तpriv(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry)
अणु
	वापस call_पूर्णांक_hook(inode_समाप्तpriv, 0, mnt_userns, dentry);
पूर्ण

पूर्णांक security_inode_माला_लोecurity(काष्ठा user_namespace *mnt_userns,
			       काष्ठा inode *inode, स्थिर अक्षर *name,
			       व्योम **buffer, bool alloc)
अणु
	काष्ठा security_hook_list *hp;
	पूर्णांक rc;

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस LSM_RET_DEFAULT(inode_माला_लोecurity);
	/*
	 * Only one module will provide an attribute with a given name.
	 */
	hlist_क्रम_each_entry(hp, &security_hook_heads.inode_माला_लोecurity, list) अणु
		rc = hp->hook.inode_माला_लोecurity(mnt_userns, inode, name, buffer, alloc);
		अगर (rc != LSM_RET_DEFAULT(inode_माला_लोecurity))
			वापस rc;
	पूर्ण
	वापस LSM_RET_DEFAULT(inode_माला_लोecurity);
पूर्ण

पूर्णांक security_inode_setsecurity(काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा security_hook_list *hp;
	पूर्णांक rc;

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस LSM_RET_DEFAULT(inode_setsecurity);
	/*
	 * Only one module will provide an attribute with a given name.
	 */
	hlist_क्रम_each_entry(hp, &security_hook_heads.inode_setsecurity, list) अणु
		rc = hp->hook.inode_setsecurity(inode, name, value, size,
								flags);
		अगर (rc != LSM_RET_DEFAULT(inode_setsecurity))
			वापस rc;
	पूर्ण
	वापस LSM_RET_DEFAULT(inode_setsecurity);
पूर्ण

पूर्णांक security_inode_listsecurity(काष्ठा inode *inode, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;
	वापस call_पूर्णांक_hook(inode_listsecurity, 0, inode, buffer, buffer_size);
पूर्ण
EXPORT_SYMBOL(security_inode_listsecurity);

व्योम security_inode_माला_लोecid(काष्ठा inode *inode, u32 *secid)
अणु
	call_व्योम_hook(inode_माला_लोecid, inode, secid);
पूर्ण

पूर्णांक security_inode_copy_up(काष्ठा dentry *src, काष्ठा cred **new)
अणु
	वापस call_पूर्णांक_hook(inode_copy_up, 0, src, new);
पूर्ण
EXPORT_SYMBOL(security_inode_copy_up);

पूर्णांक security_inode_copy_up_xattr(स्थिर अक्षर *name)
अणु
	काष्ठा security_hook_list *hp;
	पूर्णांक rc;

	/*
	 * The implementation can वापस 0 (accept the xattr), 1 (discard the
	 * xattr), -EOPNOTSUPP अगर it करोes not know anything about the xattr or
	 * any other error code inहाल of an error.
	 */
	hlist_क्रम_each_entry(hp,
		&security_hook_heads.inode_copy_up_xattr, list) अणु
		rc = hp->hook.inode_copy_up_xattr(name);
		अगर (rc != LSM_RET_DEFAULT(inode_copy_up_xattr))
			वापस rc;
	पूर्ण

	वापस LSM_RET_DEFAULT(inode_copy_up_xattr);
पूर्ण
EXPORT_SYMBOL(security_inode_copy_up_xattr);

पूर्णांक security_kernfs_init_security(काष्ठा kernfs_node *kn_dir,
				  काष्ठा kernfs_node *kn)
अणु
	वापस call_पूर्णांक_hook(kernfs_init_security, 0, kn_dir, kn);
पूर्ण

पूर्णांक security_file_permission(काष्ठा file *file, पूर्णांक mask)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(file_permission, 0, file, mask);
	अगर (ret)
		वापस ret;

	वापस fsnotअगरy_perm(file, mask);
पूर्ण

पूर्णांक security_file_alloc(काष्ठा file *file)
अणु
	पूर्णांक rc = lsm_file_alloc(file);

	अगर (rc)
		वापस rc;
	rc = call_पूर्णांक_hook(file_alloc_security, 0, file);
	अगर (unlikely(rc))
		security_file_मुक्त(file);
	वापस rc;
पूर्ण

व्योम security_file_मुक्त(काष्ठा file *file)
अणु
	व्योम *blob;

	call_व्योम_hook(file_मुक्त_security, file);

	blob = file->f_security;
	अगर (blob) अणु
		file->f_security = शून्य;
		kmem_cache_मुक्त(lsm_file_cache, blob);
	पूर्ण
पूर्ण

पूर्णांक security_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस call_पूर्णांक_hook(file_ioctl, 0, file, cmd, arg);
पूर्ण
EXPORT_SYMBOL_GPL(security_file_ioctl);

अटल अंतरभूत अचिन्हित दीर्घ mmap_prot(काष्ठा file *file, अचिन्हित दीर्घ prot)
अणु
	/*
	 * Does we have PROT_READ and करोes the application expect
	 * it to imply PROT_EXEC?  If not, nothing to talk about...
	 */
	अगर ((prot & (PROT_READ | PROT_EXEC)) != PROT_READ)
		वापस prot;
	अगर (!(current->personality & READ_IMPLIES_EXEC))
		वापस prot;
	/*
	 * अगर that's an anonymous mapping, let it.
	 */
	अगर (!file)
		वापस prot | PROT_EXEC;
	/*
	 * ditto अगर it's not on noexec mount, except that on !MMU we need
	 * NOMMU_MAP_EXEC (== VM_MAYEXEC) in this हाल
	 */
	अगर (!path_noexec(&file->f_path)) अणु
#अगर_अघोषित CONFIG_MMU
		अगर (file->f_op->mmap_capabilities) अणु
			अचिन्हित caps = file->f_op->mmap_capabilities(file);
			अगर (!(caps & NOMMU_MAP_EXEC))
				वापस prot;
		पूर्ण
#पूर्ण_अगर
		वापस prot | PROT_EXEC;
	पूर्ण
	/* anything on noexec mount won't get PROT_EXEC */
	वापस prot;
पूर्ण

पूर्णांक security_mmap_file(काष्ठा file *file, अचिन्हित दीर्घ prot,
			अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;
	ret = call_पूर्णांक_hook(mmap_file, 0, file, prot,
					mmap_prot(file, prot), flags);
	अगर (ret)
		वापस ret;
	वापस ima_file_mmap(file, prot);
पूर्ण

पूर्णांक security_mmap_addr(अचिन्हित दीर्घ addr)
अणु
	वापस call_पूर्णांक_hook(mmap_addr, 0, addr);
पूर्ण

पूर्णांक security_file_mprotect(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ reqprot,
			    अचिन्हित दीर्घ prot)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(file_mprotect, 0, vma, reqprot, prot);
	अगर (ret)
		वापस ret;
	वापस ima_file_mprotect(vma, prot);
पूर्ण

पूर्णांक security_file_lock(काष्ठा file *file, अचिन्हित पूर्णांक cmd)
अणु
	वापस call_पूर्णांक_hook(file_lock, 0, file, cmd);
पूर्ण

पूर्णांक security_file_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस call_पूर्णांक_hook(file_fcntl, 0, file, cmd, arg);
पूर्ण

व्योम security_file_set_fowner(काष्ठा file *file)
अणु
	call_व्योम_hook(file_set_fowner, file);
पूर्ण

पूर्णांक security_file_send_sigiotask(काष्ठा task_काष्ठा *tsk,
				  काष्ठा fown_काष्ठा *fown, पूर्णांक sig)
अणु
	वापस call_पूर्णांक_hook(file_send_sigiotask, 0, tsk, fown, sig);
पूर्ण

पूर्णांक security_file_receive(काष्ठा file *file)
अणु
	वापस call_पूर्णांक_hook(file_receive, 0, file);
पूर्ण

पूर्णांक security_file_खोलो(काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(file_खोलो, 0, file);
	अगर (ret)
		वापस ret;

	वापस fsnotअगरy_perm(file, MAY_OPEN);
पूर्ण

पूर्णांक security_task_alloc(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ clone_flags)
अणु
	पूर्णांक rc = lsm_task_alloc(task);

	अगर (rc)
		वापस rc;
	rc = call_पूर्णांक_hook(task_alloc, 0, task, clone_flags);
	अगर (unlikely(rc))
		security_task_मुक्त(task);
	वापस rc;
पूर्ण

व्योम security_task_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	call_व्योम_hook(task_मुक्त, task);

	kमुक्त(task->security);
	task->security = शून्य;
पूर्ण

पूर्णांक security_cred_alloc_blank(काष्ठा cred *cred, gfp_t gfp)
अणु
	पूर्णांक rc = lsm_cred_alloc(cred, gfp);

	अगर (rc)
		वापस rc;

	rc = call_पूर्णांक_hook(cred_alloc_blank, 0, cred, gfp);
	अगर (unlikely(rc))
		security_cred_मुक्त(cred);
	वापस rc;
पूर्ण

व्योम security_cred_मुक्त(काष्ठा cred *cred)
अणु
	/*
	 * There is a failure हाल in prepare_creds() that
	 * may result in a call here with ->security being शून्य.
	 */
	अगर (unlikely(cred->security == शून्य))
		वापस;

	call_व्योम_hook(cred_मुक्त, cred);

	kमुक्त(cred->security);
	cred->security = शून्य;
पूर्ण

पूर्णांक security_prepare_creds(काष्ठा cred *new, स्थिर काष्ठा cred *old, gfp_t gfp)
अणु
	पूर्णांक rc = lsm_cred_alloc(new, gfp);

	अगर (rc)
		वापस rc;

	rc = call_पूर्णांक_hook(cred_prepare, 0, new, old, gfp);
	अगर (unlikely(rc))
		security_cred_मुक्त(new);
	वापस rc;
पूर्ण

व्योम security_transfer_creds(काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु
	call_व्योम_hook(cred_transfer, new, old);
पूर्ण

व्योम security_cred_माला_लोecid(स्थिर काष्ठा cred *c, u32 *secid)
अणु
	*secid = 0;
	call_व्योम_hook(cred_माला_लोecid, c, secid);
पूर्ण
EXPORT_SYMBOL(security_cred_माला_लोecid);

पूर्णांक security_kernel_act_as(काष्ठा cred *new, u32 secid)
अणु
	वापस call_पूर्णांक_hook(kernel_act_as, 0, new, secid);
पूर्ण

पूर्णांक security_kernel_create_files_as(काष्ठा cred *new, काष्ठा inode *inode)
अणु
	वापस call_पूर्णांक_hook(kernel_create_files_as, 0, new, inode);
पूर्ण

पूर्णांक security_kernel_module_request(अक्षर *kmod_name)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(kernel_module_request, 0, kmod_name);
	अगर (ret)
		वापस ret;
	वापस पूर्णांकegrity_kernel_module_request(kmod_name);
पूर्ण

पूर्णांक security_kernel_पढ़ो_file(काष्ठा file *file, क्रमागत kernel_पढ़ो_file_id id,
			      bool contents)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(kernel_पढ़ो_file, 0, file, id, contents);
	अगर (ret)
		वापस ret;
	वापस ima_पढ़ो_file(file, id, contents);
पूर्ण
EXPORT_SYMBOL_GPL(security_kernel_पढ़ो_file);

पूर्णांक security_kernel_post_पढ़ो_file(काष्ठा file *file, अक्षर *buf, loff_t size,
				   क्रमागत kernel_पढ़ो_file_id id)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(kernel_post_पढ़ो_file, 0, file, buf, size, id);
	अगर (ret)
		वापस ret;
	वापस ima_post_पढ़ो_file(file, buf, size, id);
पूर्ण
EXPORT_SYMBOL_GPL(security_kernel_post_पढ़ो_file);

पूर्णांक security_kernel_load_data(क्रमागत kernel_load_data_id id, bool contents)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(kernel_load_data, 0, id, contents);
	अगर (ret)
		वापस ret;
	वापस ima_load_data(id, contents);
पूर्ण
EXPORT_SYMBOL_GPL(security_kernel_load_data);

पूर्णांक security_kernel_post_load_data(अक्षर *buf, loff_t size,
				   क्रमागत kernel_load_data_id id,
				   अक्षर *description)
अणु
	पूर्णांक ret;

	ret = call_पूर्णांक_hook(kernel_post_load_data, 0, buf, size, id,
			    description);
	अगर (ret)
		वापस ret;
	वापस ima_post_load_data(buf, size, id, description);
पूर्ण
EXPORT_SYMBOL_GPL(security_kernel_post_load_data);

पूर्णांक security_task_fix_setuid(काष्ठा cred *new, स्थिर काष्ठा cred *old,
			     पूर्णांक flags)
अणु
	वापस call_पूर्णांक_hook(task_fix_setuid, 0, new, old, flags);
पूर्ण

पूर्णांक security_task_fix_setgid(काष्ठा cred *new, स्थिर काष्ठा cred *old,
				 पूर्णांक flags)
अणु
	वापस call_पूर्णांक_hook(task_fix_setgid, 0, new, old, flags);
पूर्ण

पूर्णांक security_task_setpgid(काष्ठा task_काष्ठा *p, pid_t pgid)
अणु
	वापस call_पूर्णांक_hook(task_setpgid, 0, p, pgid);
पूर्ण

पूर्णांक security_task_getpgid(काष्ठा task_काष्ठा *p)
अणु
	वापस call_पूर्णांक_hook(task_getpgid, 0, p);
पूर्ण

पूर्णांक security_task_माला_लोid(काष्ठा task_काष्ठा *p)
अणु
	वापस call_पूर्णांक_hook(task_माला_लोid, 0, p);
पूर्ण

व्योम security_task_माला_लोecid_subj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	*secid = 0;
	call_व्योम_hook(task_माला_लोecid_subj, p, secid);
पूर्ण
EXPORT_SYMBOL(security_task_माला_लोecid_subj);

व्योम security_task_माला_लोecid_obj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	*secid = 0;
	call_व्योम_hook(task_माला_लोecid_obj, p, secid);
पूर्ण
EXPORT_SYMBOL(security_task_माला_लोecid_obj);

पूर्णांक security_task_setnice(काष्ठा task_काष्ठा *p, पूर्णांक nice)
अणु
	वापस call_पूर्णांक_hook(task_setnice, 0, p, nice);
पूर्ण

पूर्णांक security_task_setioprio(काष्ठा task_काष्ठा *p, पूर्णांक ioprio)
अणु
	वापस call_पूर्णांक_hook(task_setioprio, 0, p, ioprio);
पूर्ण

पूर्णांक security_task_getioprio(काष्ठा task_काष्ठा *p)
अणु
	वापस call_पूर्णांक_hook(task_getioprio, 0, p);
पूर्ण

पूर्णांक security_task_prlimit(स्थिर काष्ठा cred *cred, स्थिर काष्ठा cred *tcred,
			  अचिन्हित पूर्णांक flags)
अणु
	वापस call_पूर्णांक_hook(task_prlimit, 0, cred, tcred, flags);
पूर्ण

पूर्णांक security_task_setrlimit(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक resource,
		काष्ठा rlimit *new_rlim)
अणु
	वापस call_पूर्णांक_hook(task_setrlimit, 0, p, resource, new_rlim);
पूर्ण

पूर्णांक security_task_setscheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस call_पूर्णांक_hook(task_setscheduler, 0, p);
पूर्ण

पूर्णांक security_task_माला_लोcheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस call_पूर्णांक_hook(task_माला_लोcheduler, 0, p);
पूर्ण

पूर्णांक security_task_movememory(काष्ठा task_काष्ठा *p)
अणु
	वापस call_पूर्णांक_hook(task_movememory, 0, p);
पूर्ण

पूर्णांक security_task_समाप्त(काष्ठा task_काष्ठा *p, काष्ठा kernel_siginfo *info,
			पूर्णांक sig, स्थिर काष्ठा cred *cred)
अणु
	वापस call_पूर्णांक_hook(task_समाप्त, 0, p, info, sig, cred);
पूर्ण

पूर्णांक security_task_prctl(पूर्णांक option, अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			 अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
अणु
	पूर्णांक thisrc;
	पूर्णांक rc = LSM_RET_DEFAULT(task_prctl);
	काष्ठा security_hook_list *hp;

	hlist_क्रम_each_entry(hp, &security_hook_heads.task_prctl, list) अणु
		thisrc = hp->hook.task_prctl(option, arg2, arg3, arg4, arg5);
		अगर (thisrc != LSM_RET_DEFAULT(task_prctl)) अणु
			rc = thisrc;
			अगर (thisrc != 0)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

व्योम security_task_to_inode(काष्ठा task_काष्ठा *p, काष्ठा inode *inode)
अणु
	call_व्योम_hook(task_to_inode, p, inode);
पूर्ण

पूर्णांक security_ipc_permission(काष्ठा kern_ipc_perm *ipcp, लघु flag)
अणु
	वापस call_पूर्णांक_hook(ipc_permission, 0, ipcp, flag);
पूर्ण

व्योम security_ipc_माला_लोecid(काष्ठा kern_ipc_perm *ipcp, u32 *secid)
अणु
	*secid = 0;
	call_व्योम_hook(ipc_माला_लोecid, ipcp, secid);
पूर्ण

पूर्णांक security_msg_msg_alloc(काष्ठा msg_msg *msg)
अणु
	पूर्णांक rc = lsm_msg_msg_alloc(msg);

	अगर (unlikely(rc))
		वापस rc;
	rc = call_पूर्णांक_hook(msg_msg_alloc_security, 0, msg);
	अगर (unlikely(rc))
		security_msg_msg_मुक्त(msg);
	वापस rc;
पूर्ण

व्योम security_msg_msg_मुक्त(काष्ठा msg_msg *msg)
अणु
	call_व्योम_hook(msg_msg_मुक्त_security, msg);
	kमुक्त(msg->security);
	msg->security = शून्य;
पूर्ण

पूर्णांक security_msg_queue_alloc(काष्ठा kern_ipc_perm *msq)
अणु
	पूर्णांक rc = lsm_ipc_alloc(msq);

	अगर (unlikely(rc))
		वापस rc;
	rc = call_पूर्णांक_hook(msg_queue_alloc_security, 0, msq);
	अगर (unlikely(rc))
		security_msg_queue_मुक्त(msq);
	वापस rc;
पूर्ण

व्योम security_msg_queue_मुक्त(काष्ठा kern_ipc_perm *msq)
अणु
	call_व्योम_hook(msg_queue_मुक्त_security, msq);
	kमुक्त(msq->security);
	msq->security = शून्य;
पूर्ण

पूर्णांक security_msg_queue_associate(काष्ठा kern_ipc_perm *msq, पूर्णांक msqflg)
अणु
	वापस call_पूर्णांक_hook(msg_queue_associate, 0, msq, msqflg);
पूर्ण

पूर्णांक security_msg_queue_msgctl(काष्ठा kern_ipc_perm *msq, पूर्णांक cmd)
अणु
	वापस call_पूर्णांक_hook(msg_queue_msgctl, 0, msq, cmd);
पूर्ण

पूर्णांक security_msg_queue_msgsnd(काष्ठा kern_ipc_perm *msq,
			       काष्ठा msg_msg *msg, पूर्णांक msqflg)
अणु
	वापस call_पूर्णांक_hook(msg_queue_msgsnd, 0, msq, msg, msqflg);
पूर्ण

पूर्णांक security_msg_queue_msgrcv(काष्ठा kern_ipc_perm *msq, काष्ठा msg_msg *msg,
			       काष्ठा task_काष्ठा *target, दीर्घ type, पूर्णांक mode)
अणु
	वापस call_पूर्णांक_hook(msg_queue_msgrcv, 0, msq, msg, target, type, mode);
पूर्ण

पूर्णांक security_shm_alloc(काष्ठा kern_ipc_perm *shp)
अणु
	पूर्णांक rc = lsm_ipc_alloc(shp);

	अगर (unlikely(rc))
		वापस rc;
	rc = call_पूर्णांक_hook(shm_alloc_security, 0, shp);
	अगर (unlikely(rc))
		security_shm_मुक्त(shp);
	वापस rc;
पूर्ण

व्योम security_shm_मुक्त(काष्ठा kern_ipc_perm *shp)
अणु
	call_व्योम_hook(shm_मुक्त_security, shp);
	kमुक्त(shp->security);
	shp->security = शून्य;
पूर्ण

पूर्णांक security_shm_associate(काष्ठा kern_ipc_perm *shp, पूर्णांक shmflg)
अणु
	वापस call_पूर्णांक_hook(shm_associate, 0, shp, shmflg);
पूर्ण

पूर्णांक security_shm_shmctl(काष्ठा kern_ipc_perm *shp, पूर्णांक cmd)
अणु
	वापस call_पूर्णांक_hook(shm_shmctl, 0, shp, cmd);
पूर्ण

पूर्णांक security_shm_shmat(काष्ठा kern_ipc_perm *shp, अक्षर __user *shmaddr, पूर्णांक shmflg)
अणु
	वापस call_पूर्णांक_hook(shm_shmat, 0, shp, shmaddr, shmflg);
पूर्ण

पूर्णांक security_sem_alloc(काष्ठा kern_ipc_perm *sma)
अणु
	पूर्णांक rc = lsm_ipc_alloc(sma);

	अगर (unlikely(rc))
		वापस rc;
	rc = call_पूर्णांक_hook(sem_alloc_security, 0, sma);
	अगर (unlikely(rc))
		security_sem_मुक्त(sma);
	वापस rc;
पूर्ण

व्योम security_sem_मुक्त(काष्ठा kern_ipc_perm *sma)
अणु
	call_व्योम_hook(sem_मुक्त_security, sma);
	kमुक्त(sma->security);
	sma->security = शून्य;
पूर्ण

पूर्णांक security_sem_associate(काष्ठा kern_ipc_perm *sma, पूर्णांक semflg)
अणु
	वापस call_पूर्णांक_hook(sem_associate, 0, sma, semflg);
पूर्ण

पूर्णांक security_sem_semctl(काष्ठा kern_ipc_perm *sma, पूर्णांक cmd)
अणु
	वापस call_पूर्णांक_hook(sem_semctl, 0, sma, cmd);
पूर्ण

पूर्णांक security_sem_semop(काष्ठा kern_ipc_perm *sma, काष्ठा sembuf *sops,
			अचिन्हित nsops, पूर्णांक alter)
अणु
	वापस call_पूर्णांक_hook(sem_semop, 0, sma, sops, nsops, alter);
पूर्ण

व्योम security_d_instantiate(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	अगर (unlikely(inode && IS_PRIVATE(inode)))
		वापस;
	call_व्योम_hook(d_instantiate, dentry, inode);
पूर्ण
EXPORT_SYMBOL(security_d_instantiate);

पूर्णांक security_getprocattr(काष्ठा task_काष्ठा *p, स्थिर अक्षर *lsm, अक्षर *name,
				अक्षर **value)
अणु
	काष्ठा security_hook_list *hp;

	hlist_क्रम_each_entry(hp, &security_hook_heads.getprocattr, list) अणु
		अगर (lsm != शून्य && म_भेद(lsm, hp->lsm))
			जारी;
		वापस hp->hook.getprocattr(p, name, value);
	पूर्ण
	वापस LSM_RET_DEFAULT(getprocattr);
पूर्ण

पूर्णांक security_setprocattr(स्थिर अक्षर *lsm, स्थिर अक्षर *name, व्योम *value,
			 माप_प्रकार size)
अणु
	काष्ठा security_hook_list *hp;

	hlist_क्रम_each_entry(hp, &security_hook_heads.setprocattr, list) अणु
		अगर (lsm != शून्य && म_भेद(lsm, hp->lsm))
			जारी;
		वापस hp->hook.setprocattr(name, value, size);
	पूर्ण
	वापस LSM_RET_DEFAULT(setprocattr);
पूर्ण

पूर्णांक security_netlink_send(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस call_पूर्णांक_hook(netlink_send, 0, sk, skb);
पूर्ण

पूर्णांक security_ismaclabel(स्थिर अक्षर *name)
अणु
	वापस call_पूर्णांक_hook(ismaclabel, 0, name);
पूर्ण
EXPORT_SYMBOL(security_ismaclabel);

पूर्णांक security_secid_to_secctx(u32 secid, अक्षर **secdata, u32 *seclen)
अणु
	काष्ठा security_hook_list *hp;
	पूर्णांक rc;

	/*
	 * Currently, only one LSM can implement secid_to_secctx (i.e this
	 * LSM hook is not "stackable").
	 */
	hlist_क्रम_each_entry(hp, &security_hook_heads.secid_to_secctx, list) अणु
		rc = hp->hook.secid_to_secctx(secid, secdata, seclen);
		अगर (rc != LSM_RET_DEFAULT(secid_to_secctx))
			वापस rc;
	पूर्ण

	वापस LSM_RET_DEFAULT(secid_to_secctx);
पूर्ण
EXPORT_SYMBOL(security_secid_to_secctx);

पूर्णांक security_secctx_to_secid(स्थिर अक्षर *secdata, u32 seclen, u32 *secid)
अणु
	*secid = 0;
	वापस call_पूर्णांक_hook(secctx_to_secid, 0, secdata, seclen, secid);
पूर्ण
EXPORT_SYMBOL(security_secctx_to_secid);

व्योम security_release_secctx(अक्षर *secdata, u32 seclen)
अणु
	call_व्योम_hook(release_secctx, secdata, seclen);
पूर्ण
EXPORT_SYMBOL(security_release_secctx);

व्योम security_inode_invalidate_secctx(काष्ठा inode *inode)
अणु
	call_व्योम_hook(inode_invalidate_secctx, inode);
पूर्ण
EXPORT_SYMBOL(security_inode_invalidate_secctx);

पूर्णांक security_inode_notअगरysecctx(काष्ठा inode *inode, व्योम *ctx, u32 ctxlen)
अणु
	वापस call_पूर्णांक_hook(inode_notअगरysecctx, 0, inode, ctx, ctxlen);
पूर्ण
EXPORT_SYMBOL(security_inode_notअगरysecctx);

पूर्णांक security_inode_setsecctx(काष्ठा dentry *dentry, व्योम *ctx, u32 ctxlen)
अणु
	वापस call_पूर्णांक_hook(inode_setsecctx, 0, dentry, ctx, ctxlen);
पूर्ण
EXPORT_SYMBOL(security_inode_setsecctx);

पूर्णांक security_inode_माला_लोecctx(काष्ठा inode *inode, व्योम **ctx, u32 *ctxlen)
अणु
	वापस call_पूर्णांक_hook(inode_माला_लोecctx, -EOPNOTSUPP, inode, ctx, ctxlen);
पूर्ण
EXPORT_SYMBOL(security_inode_माला_लोecctx);

#अगर_घोषित CONFIG_WATCH_QUEUE
पूर्णांक security_post_notअगरication(स्थिर काष्ठा cred *w_cred,
			       स्थिर काष्ठा cred *cred,
			       काष्ठा watch_notअगरication *n)
अणु
	वापस call_पूर्णांक_hook(post_notअगरication, 0, w_cred, cred, n);
पूर्ण
#पूर्ण_अगर /* CONFIG_WATCH_QUEUE */

#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
पूर्णांक security_watch_key(काष्ठा key *key)
अणु
	वापस call_पूर्णांक_hook(watch_key, 0, key);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_NETWORK

पूर्णांक security_unix_stream_connect(काष्ठा sock *sock, काष्ठा sock *other, काष्ठा sock *newsk)
अणु
	वापस call_पूर्णांक_hook(unix_stream_connect, 0, sock, other, newsk);
पूर्ण
EXPORT_SYMBOL(security_unix_stream_connect);

पूर्णांक security_unix_may_send(काष्ठा socket *sock,  काष्ठा socket *other)
अणु
	वापस call_पूर्णांक_hook(unix_may_send, 0, sock, other);
पूर्ण
EXPORT_SYMBOL(security_unix_may_send);

पूर्णांक security_socket_create(पूर्णांक family, पूर्णांक type, पूर्णांक protocol, पूर्णांक kern)
अणु
	वापस call_पूर्णांक_hook(socket_create, 0, family, type, protocol, kern);
पूर्ण

पूर्णांक security_socket_post_create(काष्ठा socket *sock, पूर्णांक family,
				पूर्णांक type, पूर्णांक protocol, पूर्णांक kern)
अणु
	वापस call_पूर्णांक_hook(socket_post_create, 0, sock, family, type,
						protocol, kern);
पूर्ण

पूर्णांक security_socket_socketpair(काष्ठा socket *socka, काष्ठा socket *sockb)
अणु
	वापस call_पूर्णांक_hook(socket_socketpair, 0, socka, sockb);
पूर्ण
EXPORT_SYMBOL(security_socket_socketpair);

पूर्णांक security_socket_bind(काष्ठा socket *sock, काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	वापस call_पूर्णांक_hook(socket_bind, 0, sock, address, addrlen);
पूर्ण

पूर्णांक security_socket_connect(काष्ठा socket *sock, काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	वापस call_पूर्णांक_hook(socket_connect, 0, sock, address, addrlen);
पूर्ण

पूर्णांक security_socket_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	वापस call_पूर्णांक_hook(socket_listen, 0, sock, backlog);
पूर्ण

पूर्णांक security_socket_accept(काष्ठा socket *sock, काष्ठा socket *newsock)
अणु
	वापस call_पूर्णांक_hook(socket_accept, 0, sock, newsock);
पूर्ण

पूर्णांक security_socket_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक size)
अणु
	वापस call_पूर्णांक_hook(socket_sendmsg, 0, sock, msg, size);
पूर्ण

पूर्णांक security_socket_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    पूर्णांक size, पूर्णांक flags)
अणु
	वापस call_पूर्णांक_hook(socket_recvmsg, 0, sock, msg, size, flags);
पूर्ण

पूर्णांक security_socket_माला_लोockname(काष्ठा socket *sock)
अणु
	वापस call_पूर्णांक_hook(socket_माला_लोockname, 0, sock);
पूर्ण

पूर्णांक security_socket_getpeername(काष्ठा socket *sock)
अणु
	वापस call_पूर्णांक_hook(socket_getpeername, 0, sock);
पूर्ण

पूर्णांक security_socket_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname)
अणु
	वापस call_पूर्णांक_hook(socket_माला_लोockopt, 0, sock, level, optname);
पूर्ण

पूर्णांक security_socket_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname)
अणु
	वापस call_पूर्णांक_hook(socket_setsockopt, 0, sock, level, optname);
पूर्ण

पूर्णांक security_socket_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	वापस call_पूर्णांक_hook(socket_shutकरोwn, 0, sock, how);
पूर्ण

पूर्णांक security_sock_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस call_पूर्णांक_hook(socket_sock_rcv_skb, 0, sk, skb);
पूर्ण
EXPORT_SYMBOL(security_sock_rcv_skb);

पूर्णांक security_socket_getpeersec_stream(काष्ठा socket *sock, अक्षर __user *optval,
				      पूर्णांक __user *optlen, अचिन्हित len)
अणु
	वापस call_पूर्णांक_hook(socket_getpeersec_stream, -ENOPROTOOPT, sock,
				optval, optlen, len);
पूर्ण

पूर्णांक security_socket_getpeersec_dgram(काष्ठा socket *sock, काष्ठा sk_buff *skb, u32 *secid)
अणु
	वापस call_पूर्णांक_hook(socket_getpeersec_dgram, -ENOPROTOOPT, sock,
			     skb, secid);
पूर्ण
EXPORT_SYMBOL(security_socket_getpeersec_dgram);

पूर्णांक security_sk_alloc(काष्ठा sock *sk, पूर्णांक family, gfp_t priority)
अणु
	वापस call_पूर्णांक_hook(sk_alloc_security, 0, sk, family, priority);
पूर्ण

व्योम security_sk_मुक्त(काष्ठा sock *sk)
अणु
	call_व्योम_hook(sk_मुक्त_security, sk);
पूर्ण

व्योम security_sk_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
	call_व्योम_hook(sk_clone_security, sk, newsk);
पूर्ण
EXPORT_SYMBOL(security_sk_clone);

व्योम security_sk_classअगरy_flow(काष्ठा sock *sk, काष्ठा flowi_common *flic)
अणु
	call_व्योम_hook(sk_माला_लोecid, sk, &flic->flowic_secid);
पूर्ण
EXPORT_SYMBOL(security_sk_classअगरy_flow);

व्योम security_req_classअगरy_flow(स्थिर काष्ठा request_sock *req,
				काष्ठा flowi_common *flic)
अणु
	call_व्योम_hook(req_classअगरy_flow, req, flic);
पूर्ण
EXPORT_SYMBOL(security_req_classअगरy_flow);

व्योम security_sock_graft(काष्ठा sock *sk, काष्ठा socket *parent)
अणु
	call_व्योम_hook(sock_graft, sk, parent);
पूर्ण
EXPORT_SYMBOL(security_sock_graft);

पूर्णांक security_inet_conn_request(स्थिर काष्ठा sock *sk,
			काष्ठा sk_buff *skb, काष्ठा request_sock *req)
अणु
	वापस call_पूर्णांक_hook(inet_conn_request, 0, sk, skb, req);
पूर्ण
EXPORT_SYMBOL(security_inet_conn_request);

व्योम security_inet_csk_clone(काष्ठा sock *newsk,
			स्थिर काष्ठा request_sock *req)
अणु
	call_व्योम_hook(inet_csk_clone, newsk, req);
पूर्ण

व्योम security_inet_conn_established(काष्ठा sock *sk,
			काष्ठा sk_buff *skb)
अणु
	call_व्योम_hook(inet_conn_established, sk, skb);
पूर्ण
EXPORT_SYMBOL(security_inet_conn_established);

पूर्णांक security_secmark_relabel_packet(u32 secid)
अणु
	वापस call_पूर्णांक_hook(secmark_relabel_packet, 0, secid);
पूर्ण
EXPORT_SYMBOL(security_secmark_relabel_packet);

व्योम security_secmark_refcount_inc(व्योम)
अणु
	call_व्योम_hook(secmark_refcount_inc);
पूर्ण
EXPORT_SYMBOL(security_secmark_refcount_inc);

व्योम security_secmark_refcount_dec(व्योम)
अणु
	call_व्योम_hook(secmark_refcount_dec);
पूर्ण
EXPORT_SYMBOL(security_secmark_refcount_dec);

पूर्णांक security_tun_dev_alloc_security(व्योम **security)
अणु
	वापस call_पूर्णांक_hook(tun_dev_alloc_security, 0, security);
पूर्ण
EXPORT_SYMBOL(security_tun_dev_alloc_security);

व्योम security_tun_dev_मुक्त_security(व्योम *security)
अणु
	call_व्योम_hook(tun_dev_मुक्त_security, security);
पूर्ण
EXPORT_SYMBOL(security_tun_dev_मुक्त_security);

पूर्णांक security_tun_dev_create(व्योम)
अणु
	वापस call_पूर्णांक_hook(tun_dev_create, 0);
पूर्ण
EXPORT_SYMBOL(security_tun_dev_create);

पूर्णांक security_tun_dev_attach_queue(व्योम *security)
अणु
	वापस call_पूर्णांक_hook(tun_dev_attach_queue, 0, security);
पूर्ण
EXPORT_SYMBOL(security_tun_dev_attach_queue);

पूर्णांक security_tun_dev_attach(काष्ठा sock *sk, व्योम *security)
अणु
	वापस call_पूर्णांक_hook(tun_dev_attach, 0, sk, security);
पूर्ण
EXPORT_SYMBOL(security_tun_dev_attach);

पूर्णांक security_tun_dev_खोलो(व्योम *security)
अणु
	वापस call_पूर्णांक_hook(tun_dev_खोलो, 0, security);
पूर्ण
EXPORT_SYMBOL(security_tun_dev_खोलो);

पूर्णांक security_sctp_assoc_request(काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sk_buff *skb)
अणु
	वापस call_पूर्णांक_hook(sctp_assoc_request, 0, ep, skb);
पूर्ण
EXPORT_SYMBOL(security_sctp_assoc_request);

पूर्णांक security_sctp_bind_connect(काष्ठा sock *sk, पूर्णांक optname,
			       काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	वापस call_पूर्णांक_hook(sctp_bind_connect, 0, sk, optname,
			     address, addrlen);
पूर्ण
EXPORT_SYMBOL(security_sctp_bind_connect);

व्योम security_sctp_sk_clone(काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sock *sk,
			    काष्ठा sock *newsk)
अणु
	call_व्योम_hook(sctp_sk_clone, ep, sk, newsk);
पूर्ण
EXPORT_SYMBOL(security_sctp_sk_clone);

#पूर्ण_अगर	/* CONFIG_SECURITY_NETWORK */

#अगर_घोषित CONFIG_SECURITY_INFINIBAND

पूर्णांक security_ib_pkey_access(व्योम *sec, u64 subnet_prefix, u16 pkey)
अणु
	वापस call_पूर्णांक_hook(ib_pkey_access, 0, sec, subnet_prefix, pkey);
पूर्ण
EXPORT_SYMBOL(security_ib_pkey_access);

पूर्णांक security_ib_endport_manage_subnet(व्योम *sec, स्थिर अक्षर *dev_name, u8 port_num)
अणु
	वापस call_पूर्णांक_hook(ib_endport_manage_subnet, 0, sec, dev_name, port_num);
पूर्ण
EXPORT_SYMBOL(security_ib_endport_manage_subnet);

पूर्णांक security_ib_alloc_security(व्योम **sec)
अणु
	वापस call_पूर्णांक_hook(ib_alloc_security, 0, sec);
पूर्ण
EXPORT_SYMBOL(security_ib_alloc_security);

व्योम security_ib_मुक्त_security(व्योम *sec)
अणु
	call_व्योम_hook(ib_मुक्त_security, sec);
पूर्ण
EXPORT_SYMBOL(security_ib_मुक्त_security);
#पूर्ण_अगर	/* CONFIG_SECURITY_INFINIBAND */

#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM

पूर्णांक security_xfrm_policy_alloc(काष्ठा xfrm_sec_ctx **ctxp,
			       काष्ठा xfrm_user_sec_ctx *sec_ctx,
			       gfp_t gfp)
अणु
	वापस call_पूर्णांक_hook(xfrm_policy_alloc_security, 0, ctxp, sec_ctx, gfp);
पूर्ण
EXPORT_SYMBOL(security_xfrm_policy_alloc);

पूर्णांक security_xfrm_policy_clone(काष्ठा xfrm_sec_ctx *old_ctx,
			      काष्ठा xfrm_sec_ctx **new_ctxp)
अणु
	वापस call_पूर्णांक_hook(xfrm_policy_clone_security, 0, old_ctx, new_ctxp);
पूर्ण

व्योम security_xfrm_policy_मुक्त(काष्ठा xfrm_sec_ctx *ctx)
अणु
	call_व्योम_hook(xfrm_policy_मुक्त_security, ctx);
पूर्ण
EXPORT_SYMBOL(security_xfrm_policy_मुक्त);

पूर्णांक security_xfrm_policy_delete(काष्ठा xfrm_sec_ctx *ctx)
अणु
	वापस call_पूर्णांक_hook(xfrm_policy_delete_security, 0, ctx);
पूर्ण

पूर्णांक security_xfrm_state_alloc(काष्ठा xfrm_state *x,
			      काष्ठा xfrm_user_sec_ctx *sec_ctx)
अणु
	वापस call_पूर्णांक_hook(xfrm_state_alloc, 0, x, sec_ctx);
पूर्ण
EXPORT_SYMBOL(security_xfrm_state_alloc);

पूर्णांक security_xfrm_state_alloc_acquire(काष्ठा xfrm_state *x,
				      काष्ठा xfrm_sec_ctx *polsec, u32 secid)
अणु
	वापस call_पूर्णांक_hook(xfrm_state_alloc_acquire, 0, x, polsec, secid);
पूर्ण

पूर्णांक security_xfrm_state_delete(काष्ठा xfrm_state *x)
अणु
	वापस call_पूर्णांक_hook(xfrm_state_delete_security, 0, x);
पूर्ण
EXPORT_SYMBOL(security_xfrm_state_delete);

व्योम security_xfrm_state_मुक्त(काष्ठा xfrm_state *x)
अणु
	call_व्योम_hook(xfrm_state_मुक्त_security, x);
पूर्ण

पूर्णांक security_xfrm_policy_lookup(काष्ठा xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir)
अणु
	वापस call_पूर्णांक_hook(xfrm_policy_lookup, 0, ctx, fl_secid, dir);
पूर्ण

पूर्णांक security_xfrm_state_pol_flow_match(काष्ठा xfrm_state *x,
				       काष्ठा xfrm_policy *xp,
				       स्थिर काष्ठा flowi_common *flic)
अणु
	काष्ठा security_hook_list *hp;
	पूर्णांक rc = LSM_RET_DEFAULT(xfrm_state_pol_flow_match);

	/*
	 * Since this function is expected to वापस 0 or 1, the judgment
	 * becomes dअगरficult अगर multiple LSMs supply this call. Fortunately,
	 * we can use the first LSM's judgment because currently only SELinux
	 * supplies this call.
	 *
	 * For speed optimization, we explicitly अवरोध the loop rather than
	 * using the macro
	 */
	hlist_क्रम_each_entry(hp, &security_hook_heads.xfrm_state_pol_flow_match,
				list) अणु
		rc = hp->hook.xfrm_state_pol_flow_match(x, xp, flic);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक security_xfrm_decode_session(काष्ठा sk_buff *skb, u32 *secid)
अणु
	वापस call_पूर्णांक_hook(xfrm_decode_session, 0, skb, secid, 1);
पूर्ण

व्योम security_skb_classअगरy_flow(काष्ठा sk_buff *skb, काष्ठा flowi_common *flic)
अणु
	पूर्णांक rc = call_पूर्णांक_hook(xfrm_decode_session, 0, skb, &flic->flowic_secid,
				0);

	BUG_ON(rc);
पूर्ण
EXPORT_SYMBOL(security_skb_classअगरy_flow);

#पूर्ण_अगर	/* CONFIG_SECURITY_NETWORK_XFRM */

#अगर_घोषित CONFIG_KEYS

पूर्णांक security_key_alloc(काष्ठा key *key, स्थिर काष्ठा cred *cred,
		       अचिन्हित दीर्घ flags)
अणु
	वापस call_पूर्णांक_hook(key_alloc, 0, key, cred, flags);
पूर्ण

व्योम security_key_मुक्त(काष्ठा key *key)
अणु
	call_व्योम_hook(key_मुक्त, key);
पूर्ण

पूर्णांक security_key_permission(key_ref_t key_ref, स्थिर काष्ठा cred *cred,
			    क्रमागत key_need_perm need_perm)
अणु
	वापस call_पूर्णांक_hook(key_permission, 0, key_ref, cred, need_perm);
पूर्ण

पूर्णांक security_key_माला_लोecurity(काष्ठा key *key, अक्षर **_buffer)
अणु
	*_buffer = शून्य;
	वापस call_पूर्णांक_hook(key_माला_लोecurity, 0, key, _buffer);
पूर्ण

#पूर्ण_अगर	/* CONFIG_KEYS */

#अगर_घोषित CONFIG_AUDIT

पूर्णांक security_audit_rule_init(u32 field, u32 op, अक्षर *rulestr, व्योम **lsmrule)
अणु
	वापस call_पूर्णांक_hook(audit_rule_init, 0, field, op, rulestr, lsmrule);
पूर्ण

पूर्णांक security_audit_rule_known(काष्ठा audit_krule *krule)
अणु
	वापस call_पूर्णांक_hook(audit_rule_known, 0, krule);
पूर्ण

व्योम security_audit_rule_मुक्त(व्योम *lsmrule)
अणु
	call_व्योम_hook(audit_rule_मुक्त, lsmrule);
पूर्ण

पूर्णांक security_audit_rule_match(u32 secid, u32 field, u32 op, व्योम *lsmrule)
अणु
	वापस call_पूर्णांक_hook(audit_rule_match, 0, secid, field, op, lsmrule);
पूर्ण
#पूर्ण_अगर /* CONFIG_AUDIT */

#अगर_घोषित CONFIG_BPF_SYSCALL
पूर्णांक security_bpf(पूर्णांक cmd, जोड़ bpf_attr *attr, अचिन्हित पूर्णांक size)
अणु
	वापस call_पूर्णांक_hook(bpf, 0, cmd, attr, size);
पूर्ण
पूर्णांक security_bpf_map(काष्ठा bpf_map *map, भ_शेषe_t भ_शेषe)
अणु
	वापस call_पूर्णांक_hook(bpf_map, 0, map, भ_शेषe);
पूर्ण
पूर्णांक security_bpf_prog(काष्ठा bpf_prog *prog)
अणु
	वापस call_पूर्णांक_hook(bpf_prog, 0, prog);
पूर्ण
पूर्णांक security_bpf_map_alloc(काष्ठा bpf_map *map)
अणु
	वापस call_पूर्णांक_hook(bpf_map_alloc_security, 0, map);
पूर्ण
पूर्णांक security_bpf_prog_alloc(काष्ठा bpf_prog_aux *aux)
अणु
	वापस call_पूर्णांक_hook(bpf_prog_alloc_security, 0, aux);
पूर्ण
व्योम security_bpf_map_मुक्त(काष्ठा bpf_map *map)
अणु
	call_व्योम_hook(bpf_map_मुक्त_security, map);
पूर्ण
व्योम security_bpf_prog_मुक्त(काष्ठा bpf_prog_aux *aux)
अणु
	call_व्योम_hook(bpf_prog_मुक्त_security, aux);
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */

पूर्णांक security_locked_करोwn(क्रमागत lockकरोwn_reason what)
अणु
	वापस call_पूर्णांक_hook(locked_करोwn, 0, what);
पूर्ण
EXPORT_SYMBOL(security_locked_करोwn);

#अगर_घोषित CONFIG_PERF_EVENTS
पूर्णांक security_perf_event_खोलो(काष्ठा perf_event_attr *attr, पूर्णांक type)
अणु
	वापस call_पूर्णांक_hook(perf_event_खोलो, 0, attr, type);
पूर्ण

पूर्णांक security_perf_event_alloc(काष्ठा perf_event *event)
अणु
	वापस call_पूर्णांक_hook(perf_event_alloc, 0, event);
पूर्ण

व्योम security_perf_event_मुक्त(काष्ठा perf_event *event)
अणु
	call_व्योम_hook(perf_event_मुक्त, event);
पूर्ण

पूर्णांक security_perf_event_पढ़ो(काष्ठा perf_event *event)
अणु
	वापस call_पूर्णांक_hook(perf_event_पढ़ो, 0, event);
पूर्ण

पूर्णांक security_perf_event_ग_लिखो(काष्ठा perf_event *event)
अणु
	वापस call_पूर्णांक_hook(perf_event_ग_लिखो, 0, event);
पूर्ण
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */
