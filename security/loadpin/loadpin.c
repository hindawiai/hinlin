<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Module and Firmware Pinning Security Module
 *
 * Copyright 2011-2016 Google Inc.
 *
 * Author: Kees Cook <keescook@chromium.org>
 */

#घोषणा pr_fmt(fmt) "LoadPin: " fmt

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/mount.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/path.h>
#समावेश <linux/sched.h>	/* current */
#समावेश <linux/string_helpers.h>

अटल व्योम report_load(स्थिर अक्षर *origin, काष्ठा file *file, अक्षर *operation)
अणु
	अक्षर *cmdline, *pathname;

	pathname = kstrdup_quotable_file(file, GFP_KERNEL);
	cmdline = kstrdup_quotable_cmdline(current, GFP_KERNEL);

	pr_notice("%s %s obj=%s%s%s pid=%d cmdline=%s%s%s\n",
		  origin, operation,
		  (pathname && pathname[0] != '<') ? "\"" : "",
		  pathname,
		  (pathname && pathname[0] != '<') ? "\"" : "",
		  task_pid_nr(current),
		  cmdline ? "\"" : "", cmdline, cmdline ? "\"" : "");

	kमुक्त(cmdline);
	kमुक्त(pathname);
पूर्ण

अटल पूर्णांक enक्रमce = IS_ENABLED(CONFIG_SECURITY_LOADPIN_ENFORCE);
अटल अक्षर *exclude_पढ़ो_files[READING_MAX_ID];
अटल पूर्णांक ignore_पढ़ो_file_id[READING_MAX_ID] __ro_after_init;
अटल काष्ठा super_block *pinned_root;
अटल DEFINE_SPINLOCK(pinned_root_spinlock);

#अगर_घोषित CONFIG_SYSCTL

अटल काष्ठा ctl_path loadpin_sysctl_path[] = अणु
	अणु .procname = "kernel", पूर्ण,
	अणु .procname = "loadpin", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table loadpin_sysctl_table[] = अणु
	अणु
		.procname       = "enforce",
		.data           = &enक्रमce,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * This must be called after early kernel init, since then the rootdev
 * is available.
 */
अटल व्योम check_pinning_enक्रमcement(काष्ठा super_block *mnt_sb)
अणु
	bool ro = false;

	/*
	 * If load pinning is not enक्रमced via a पढ़ो-only block
	 * device, allow sysctl to change modes क्रम testing.
	 */
	अगर (mnt_sb->s_bdev) अणु
		अक्षर bdev[BDEVNAME_SIZE];

		ro = bdev_पढ़ो_only(mnt_sb->s_bdev);
		bdevname(mnt_sb->s_bdev, bdev);
		pr_info("%s (%u:%u): %s\n", bdev,
			MAJOR(mnt_sb->s_bdev->bd_dev),
			MINOR(mnt_sb->s_bdev->bd_dev),
			ro ? "read-only" : "writable");
	पूर्ण अन्यथा
		pr_info("mnt_sb lacks block device, treating as: writable\n");

	अगर (!ro) अणु
		अगर (!रेजिस्टर_sysctl_paths(loadpin_sysctl_path,
					   loadpin_sysctl_table))
			pr_notice("sysctl registration failed!\n");
		अन्यथा
			pr_info("enforcement can be disabled.\n");
	पूर्ण अन्यथा
		pr_info("load pinning engaged.\n");
पूर्ण
#अन्यथा
अटल व्योम check_pinning_enक्रमcement(काष्ठा super_block *mnt_sb)
अणु
	pr_info("load pinning engaged.\n");
पूर्ण
#पूर्ण_अगर

अटल व्योम loadpin_sb_मुक्त_security(काष्ठा super_block *mnt_sb)
अणु
	/*
	 * When unmounting the fileप्रणाली we were using क्रम load
	 * pinning, we acknowledge the superblock release, but make sure
	 * no other modules or firmware can be loaded.
	 */
	अगर (!IS_ERR_OR_शून्य(pinned_root) && mnt_sb == pinned_root) अणु
		pinned_root = ERR_PTR(-EIO);
		pr_info("umount pinned fs: refusing further loads\n");
	पूर्ण
पूर्ण

अटल पूर्णांक loadpin_पढ़ो_file(काष्ठा file *file, क्रमागत kernel_पढ़ो_file_id id,
			     bool contents)
अणु
	काष्ठा super_block *load_root;
	स्थिर अक्षर *origin = kernel_पढ़ो_file_id_str(id);

	/*
	 * If we will not know that we'll be seeing the full contents
	 * then we cannot trust a load will be complete and unchanged
	 * off disk. Treat all contents=false hooks as अगर there were
	 * no associated file काष्ठा.
	 */
	अगर (!contents)
		file = शून्य;

	/* If the file id is excluded, ignore the pinning. */
	अगर ((अचिन्हित पूर्णांक)id < ARRAY_SIZE(ignore_पढ़ो_file_id) &&
	    ignore_पढ़ो_file_id[id]) अणु
		report_load(origin, file, "pinning-excluded");
		वापस 0;
	पूर्ण

	/* This handles the older init_module API that has a शून्य file. */
	अगर (!file) अणु
		अगर (!enक्रमce) अणु
			report_load(origin, शून्य, "old-api-pinning-ignored");
			वापस 0;
		पूर्ण

		report_load(origin, शून्य, "old-api-denied");
		वापस -EPERM;
	पूर्ण

	load_root = file->f_path.mnt->mnt_sb;

	/* First loaded module/firmware defines the root क्रम all others. */
	spin_lock(&pinned_root_spinlock);
	/*
	 * pinned_root is only शून्य at startup. Otherwise, it is either
	 * a valid reference, or an ERR_PTR.
	 */
	अगर (!pinned_root) अणु
		pinned_root = load_root;
		/*
		 * Unlock now since it's only pinned_root we care about.
		 * In the worst हाल, we will (correctly) report pinning
		 * failures beक्रमe we have announced that pinning is
		 * enक्रमcing. This would be purely cosmetic.
		 */
		spin_unlock(&pinned_root_spinlock);
		check_pinning_enक्रमcement(pinned_root);
		report_load(origin, file, "pinned");
	पूर्ण अन्यथा अणु
		spin_unlock(&pinned_root_spinlock);
	पूर्ण

	अगर (IS_ERR_OR_शून्य(pinned_root) || load_root != pinned_root) अणु
		अगर (unlikely(!enक्रमce)) अणु
			report_load(origin, file, "pinning-ignored");
			वापस 0;
		पूर्ण

		report_load(origin, file, "denied");
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक loadpin_load_data(क्रमागत kernel_load_data_id id, bool contents)
अणु
	वापस loadpin_पढ़ो_file(शून्य, (क्रमागत kernel_पढ़ो_file_id) id, contents);
पूर्ण

अटल काष्ठा security_hook_list loadpin_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(sb_मुक्त_security, loadpin_sb_मुक्त_security),
	LSM_HOOK_INIT(kernel_पढ़ो_file, loadpin_पढ़ो_file),
	LSM_HOOK_INIT(kernel_load_data, loadpin_load_data),
पूर्ण;

अटल व्योम __init parse_exclude(व्योम)
अणु
	पूर्णांक i, j;
	अक्षर *cur;

	/*
	 * Make sure all the arrays stay within expected sizes. This
	 * is slightly weird because kernel_पढ़ो_file_str[] includes
	 * READING_MAX_ID, which isn't actually meaningful here.
	 */
	BUILD_BUG_ON(ARRAY_SIZE(exclude_पढ़ो_files) !=
		     ARRAY_SIZE(ignore_पढ़ो_file_id));
	BUILD_BUG_ON(ARRAY_SIZE(kernel_पढ़ो_file_str) <
		     ARRAY_SIZE(ignore_पढ़ो_file_id));

	क्रम (i = 0; i < ARRAY_SIZE(exclude_पढ़ो_files); i++) अणु
		cur = exclude_पढ़ो_files[i];
		अगर (!cur)
			अवरोध;
		अगर (*cur == '\0')
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(ignore_पढ़ो_file_id); j++) अणु
			अगर (म_भेद(cur, kernel_पढ़ो_file_str[j]) == 0) अणु
				pr_info("excluding: %s\n",
					kernel_पढ़ो_file_str[j]);
				ignore_पढ़ो_file_id[j] = 1;
				/*
				 * Can not अवरोध, because one पढ़ो_file_str
				 * may map to more than on पढ़ो_file_id.
				 */
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init loadpin_init(व्योम)
अणु
	pr_info("ready to pin (currently %senforcing)\n",
		enक्रमce ? "" : "not ");
	parse_exclude();
	security_add_hooks(loadpin_hooks, ARRAY_SIZE(loadpin_hooks), "loadpin");
	वापस 0;
पूर्ण

DEFINE_LSM(loadpin) = अणु
	.name = "loadpin",
	.init = loadpin_init,
पूर्ण;

/* Should not be mutable after boot, so not listed in sysfs (perm == 0). */
module_param(enक्रमce, पूर्णांक, 0);
MODULE_PARM_DESC(enक्रमce, "Enforce module/firmware pinning");
module_param_array_named(exclude, exclude_पढ़ो_files, अक्षरp, शून्य, 0);
MODULE_PARM_DESC(exclude, "Exclude pinning specific read file types");
