<शैली गुरु>
/*
 * kmod stress test driver
 *
 * Copyright (C) 2017 Luis R. Rodriguez <mcgrof@kernel.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or at your option any
 * later version; or, when distributed separately from the Linux kernel or
 * when incorporated पूर्णांकo other software packages, subject to the following
 * license:
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of copyleft-next (version 0.3.1 or later) as published
 * at http://copyleft-next.org/.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/*
 * This driver provides an पूर्णांकerface to trigger and test the kernel's
 * module loader through a series of configurations and a few triggers.
 * To test this driver use the following script as root:
 *
 * tools/testing/selftests/kmod/kmod.sh --help
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#घोषणा TEST_START_NUM_THREADS	50
#घोषणा TEST_START_DRIVER	"test_module"
#घोषणा TEST_START_TEST_FS	"xfs"
#घोषणा TEST_START_TEST_CASE	TEST_KMOD_DRIVER


अटल bool क्रमce_init_test = false;
module_param(क्रमce_init_test, bool_enable_only, 0644);
MODULE_PARM_DESC(क्रमce_init_test,
		 "Force kicking a test immediately after driver loads");

/*
 * For device allocation / registration
 */
अटल DEFINE_MUTEX(reg_dev_mutex);
अटल LIST_HEAD(reg_test_devs);

/*
 * num_test_devs actually represents the *next* ID of the next
 * device we will allow to create.
 */
अटल पूर्णांक num_test_devs;

/**
 * क्रमागत kmod_test_हाल - linker table test हाल
 *
 * If you add a  test हाल, please be sure to review अगर you need to se
 * @need_mod_put क्रम your tests हाल.
 *
 * @TEST_KMOD_DRIVER: stress tests request_module()
 * @TEST_KMOD_FS_TYPE: stress tests get_fs_type()
 */
क्रमागत kmod_test_हाल अणु
	__TEST_KMOD_INVALID = 0,

	TEST_KMOD_DRIVER,
	TEST_KMOD_FS_TYPE,

	__TEST_KMOD_MAX,
पूर्ण;

काष्ठा test_config अणु
	अक्षर *test_driver;
	अक्षर *test_fs;
	अचिन्हित पूर्णांक num_thपढ़ोs;
	क्रमागत kmod_test_हाल test_हाल;
	पूर्णांक test_result;
पूर्ण;

काष्ठा kmod_test_device;

/**
 * kmod_test_device_info - thपढ़ो info
 *
 * @ret_sync: वापस value अगर request_module() is used, sync request क्रम
 * 	@TEST_KMOD_DRIVER
 * @fs_sync: वापस value of get_fs_type() क्रम @TEST_KMOD_FS_TYPE
 * @thपढ़ो_idx: thपढ़ो ID
 * @test_dev: test device test is being perक्रमmed under
 * @need_mod_put: Some tests (get_fs_type() is one) requires putting the module
 *	(module_put(fs_sync->owner)) when करोne, otherwise you will not be able
 *	to unload the respective modules and re-test. We use this to keep
 *	accounting of when we need this and to help out in हाल we need to
 *	error out and deal with module_put() on error.
 */
काष्ठा kmod_test_device_info अणु
	पूर्णांक ret_sync;
	काष्ठा file_प्रणाली_type *fs_sync;
	काष्ठा task_काष्ठा *task_sync;
	अचिन्हित पूर्णांक thपढ़ो_idx;
	काष्ठा kmod_test_device *test_dev;
	bool need_mod_put;
पूर्ण;

/**
 * kmod_test_device - test device to help test kmod
 *
 * @dev_idx: unique ID क्रम test device
 * @config: configuration क्रम the test
 * @misc_dev: we use a misc device under the hood
 * @dev: poपूर्णांकer to misc_dev's own काष्ठा device
 * @config_mutex: protects configuration of test
 * @trigger_mutex: the test trigger can only be fired once at a समय
 * @thपढ़ो_lock: protects @करोne count, and the @info per each thपढ़ो
 * @करोne: number of thपढ़ोs which have completed or failed
 * @test_is_oom: when we run out of memory, use this to halt moving क्रमward
 * @kthपढ़ोs_करोne: completion used to संकेत when all work is करोne
 * @list: needed to be part of the reg_test_devs
 * @info: array of info क्रम each thपढ़ो
 */
काष्ठा kmod_test_device अणु
	पूर्णांक dev_idx;
	काष्ठा test_config config;
	काष्ठा miscdevice misc_dev;
	काष्ठा device *dev;
	काष्ठा mutex config_mutex;
	काष्ठा mutex trigger_mutex;
	काष्ठा mutex thपढ़ो_mutex;

	अचिन्हित पूर्णांक करोne;

	bool test_is_oom;
	काष्ठा completion kthपढ़ोs_करोne;
	काष्ठा list_head list;

	काष्ठा kmod_test_device_info *info;
पूर्ण;

अटल स्थिर अक्षर *test_हाल_str(क्रमागत kmod_test_हाल test_हाल)
अणु
	चयन (test_हाल) अणु
	हाल TEST_KMOD_DRIVER:
		वापस "TEST_KMOD_DRIVER";
	हाल TEST_KMOD_FS_TYPE:
		वापस "TEST_KMOD_FS_TYPE";
	शेष:
		वापस "invalid";
	पूर्ण
पूर्ण

अटल काष्ठा miscdevice *dev_to_misc_dev(काष्ठा device *dev)
अणु
	वापस dev_get_drvdata(dev);
पूर्ण

अटल काष्ठा kmod_test_device *misc_dev_to_test_dev(काष्ठा miscdevice *misc_dev)
अणु
	वापस container_of(misc_dev, काष्ठा kmod_test_device, misc_dev);
पूर्ण

अटल काष्ठा kmod_test_device *dev_to_test_dev(काष्ठा device *dev)
अणु
	काष्ठा miscdevice *misc_dev;

	misc_dev = dev_to_misc_dev(dev);

	वापस misc_dev_to_test_dev(misc_dev);
पूर्ण

/* Must run with thपढ़ो_mutex held */
अटल व्योम kmod_test_करोne_check(काष्ठा kmod_test_device *test_dev,
				 अचिन्हित पूर्णांक idx)
अणु
	काष्ठा test_config *config = &test_dev->config;

	test_dev->करोne++;
	dev_dbg(test_dev->dev, "Done thread count: %u\n", test_dev->करोne);

	अगर (test_dev->करोne == config->num_thपढ़ोs) अणु
		dev_info(test_dev->dev, "Done: %u threads have all run now\n",
			 test_dev->करोne);
		dev_info(test_dev->dev, "Last thread to run: %u\n", idx);
		complete(&test_dev->kthपढ़ोs_करोne);
	पूर्ण
पूर्ण

अटल व्योम test_kmod_put_module(काष्ठा kmod_test_device_info *info)
अणु
	काष्ठा kmod_test_device *test_dev = info->test_dev;
	काष्ठा test_config *config = &test_dev->config;

	अगर (!info->need_mod_put)
		वापस;

	चयन (config->test_हाल) अणु
	हाल TEST_KMOD_DRIVER:
		अवरोध;
	हाल TEST_KMOD_FS_TYPE:
		अगर (info->fs_sync && info->fs_sync->owner)
			module_put(info->fs_sync->owner);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	info->need_mod_put = true;
पूर्ण

अटल पूर्णांक run_request(व्योम *data)
अणु
	काष्ठा kmod_test_device_info *info = data;
	काष्ठा kmod_test_device *test_dev = info->test_dev;
	काष्ठा test_config *config = &test_dev->config;

	चयन (config->test_हाल) अणु
	हाल TEST_KMOD_DRIVER:
		info->ret_sync = request_module("%s", config->test_driver);
		अवरोध;
	हाल TEST_KMOD_FS_TYPE:
		info->fs_sync = get_fs_type(config->test_fs);
		info->need_mod_put = true;
		अवरोध;
	शेष:
		/* __trigger_config_run() alपढ़ोy checked क्रम test sanity */
		BUG();
		वापस -EINVAL;
	पूर्ण

	dev_dbg(test_dev->dev, "Ran thread %u\n", info->thपढ़ो_idx);

	test_kmod_put_module(info);

	mutex_lock(&test_dev->thपढ़ो_mutex);
	info->task_sync = शून्य;
	kmod_test_करोne_check(test_dev, info->thपढ़ो_idx);
	mutex_unlock(&test_dev->thपढ़ो_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक tally_work_test(काष्ठा kmod_test_device_info *info)
अणु
	काष्ठा kmod_test_device *test_dev = info->test_dev;
	काष्ठा test_config *config = &test_dev->config;
	पूर्णांक err_ret = 0;

	चयन (config->test_हाल) अणु
	हाल TEST_KMOD_DRIVER:
		/*
		 * Only capture errors, अगर one is found that's
		 * enough, क्रम now.
		 */
		अगर (info->ret_sync != 0)
			err_ret = info->ret_sync;
		dev_info(test_dev->dev,
			 "Sync thread %d return status: %d\n",
			 info->thपढ़ो_idx, info->ret_sync);
		अवरोध;
	हाल TEST_KMOD_FS_TYPE:
		/* For now we make this simple */
		अगर (!info->fs_sync)
			err_ret = -EINVAL;
		dev_info(test_dev->dev, "Sync thread %u fs: %s\n",
			 info->thपढ़ो_idx, info->fs_sync ? config->test_fs :
			 "NULL");
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस err_ret;
पूर्ण

/*
 * XXX: add result option to display अगर all errors did not match.
 * For now we just keep any error code अगर one was found.
 *
 * If this ran it means *all* tasks were created fine and we
 * are now just collecting results.
 *
 * Only propagate errors, करो not override with a subsequent sucess हाल.
 */
अटल व्योम tally_up_work(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;
	काष्ठा kmod_test_device_info *info;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err_ret = 0;
	पूर्णांक ret = 0;

	mutex_lock(&test_dev->thपढ़ो_mutex);

	dev_info(test_dev->dev, "Results:\n");

	क्रम (idx=0; idx < config->num_thपढ़ोs; idx++) अणु
		info = &test_dev->info[idx];
		ret = tally_work_test(info);
		अगर (ret)
			err_ret = ret;
	पूर्ण

	/*
	 * Note: request_module() वापसs 256 क्रम a module not found even
	 * though modprobe itself वापसs 1.
	 */
	config->test_result = err_ret;

	mutex_unlock(&test_dev->thपढ़ो_mutex);
पूर्ण

अटल पूर्णांक try_one_request(काष्ठा kmod_test_device *test_dev, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा kmod_test_device_info *info = &test_dev->info[idx];
	पूर्णांक fail_ret = -ENOMEM;

	mutex_lock(&test_dev->thपढ़ो_mutex);

	info->thपढ़ो_idx = idx;
	info->test_dev = test_dev;
	info->task_sync = kthपढ़ो_run(run_request, info, "%s-%u",
				      KBUILD_MODNAME, idx);

	अगर (!info->task_sync || IS_ERR(info->task_sync)) अणु
		test_dev->test_is_oom = true;
		dev_err(test_dev->dev, "Setting up thread %u failed\n", idx);
		info->task_sync = शून्य;
		जाओ err_out;
	पूर्ण अन्यथा
		dev_dbg(test_dev->dev, "Kicked off thread %u\n", idx);

	mutex_unlock(&test_dev->thपढ़ो_mutex);

	वापस 0;

err_out:
	info->ret_sync = fail_ret;
	mutex_unlock(&test_dev->thपढ़ो_mutex);

	वापस fail_ret;
पूर्ण

अटल व्योम test_dev_kmod_stop_tests(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;
	काष्ठा kmod_test_device_info *info;
	अचिन्हित पूर्णांक i;

	dev_info(test_dev->dev, "Ending request_module() tests\n");

	mutex_lock(&test_dev->thपढ़ो_mutex);

	क्रम (i=0; i < config->num_thपढ़ोs; i++) अणु
		info = &test_dev->info[i];
		अगर (info->task_sync && !IS_ERR(info->task_sync)) अणु
			dev_info(test_dev->dev,
				 "Stopping still-running thread %i\n", i);
			kthपढ़ो_stop(info->task_sync);
		पूर्ण

		/*
		 * info->task_sync is well रक्षित, it can only be
		 * शून्य or a poपूर्णांकer to a काष्ठा. If its शून्य we either
		 * never ran, or we did and we completed the work. Completed
		 * tasks *always* put the module क्रम us. This is a sanity
		 * check -- just in हाल.
		 */
		अगर (info->task_sync && info->need_mod_put)
			test_kmod_put_module(info);
	पूर्ण

	mutex_unlock(&test_dev->thपढ़ो_mutex);
पूर्ण

/*
 * Only रुको *अगरf* we did not run पूर्णांकo any errors during all of our thपढ़ो
 * set up. If run पूर्णांकo any issues we stop thपढ़ोs and just bail out with
 * an error to the trigger. This also means we करोn't need any tally work
 * क्रम any thपढ़ोs which fail.
 */
अटल पूर्णांक try_requests(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret;
	bool any_error = false;

	क्रम (idx=0; idx < config->num_thपढ़ोs; idx++) अणु
		अगर (test_dev->test_is_oom) अणु
			any_error = true;
			अवरोध;
		पूर्ण

		ret = try_one_request(test_dev, idx);
		अगर (ret) अणु
			any_error = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!any_error) अणु
		test_dev->test_is_oom = false;
		dev_info(test_dev->dev,
			 "No errors were found while initializing threads\n");
		रुको_क्रम_completion(&test_dev->kthपढ़ोs_करोne);
		tally_up_work(test_dev);
	पूर्ण अन्यथा अणु
		test_dev->test_is_oom = true;
		dev_info(test_dev->dev,
			 "At least one thread failed to start, stop all work\n");
		test_dev_kmod_stop_tests(test_dev);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक run_test_driver(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;

	dev_info(test_dev->dev, "Test case: %s (%u)\n",
		 test_हाल_str(config->test_हाल),
		 config->test_हाल);
	dev_info(test_dev->dev, "Test driver to load: %s\n",
		 config->test_driver);
	dev_info(test_dev->dev, "Number of threads to run: %u\n",
		 config->num_thपढ़ोs);
	dev_info(test_dev->dev, "Thread IDs will range from 0 - %u\n",
		 config->num_thपढ़ोs - 1);

	वापस try_requests(test_dev);
पूर्ण

अटल पूर्णांक run_test_fs_type(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;

	dev_info(test_dev->dev, "Test case: %s (%u)\n",
		 test_हाल_str(config->test_हाल),
		 config->test_हाल);
	dev_info(test_dev->dev, "Test filesystem to load: %s\n",
		 config->test_fs);
	dev_info(test_dev->dev, "Number of threads to run: %u\n",
		 config->num_thपढ़ोs);
	dev_info(test_dev->dev, "Thread IDs will range from 0 - %u\n",
		 config->num_thपढ़ोs - 1);

	वापस try_requests(test_dev);
पूर्ण

अटल sमाप_प्रकार config_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;
	पूर्णांक len = 0;

	mutex_lock(&test_dev->config_mutex);

	len += snम_लिखो(buf, PAGE_SIZE,
			"Custom trigger configuration for: %s\n",
			dev_name(dev));

	len += snम_लिखो(buf+len, PAGE_SIZE - len,
			"Number of threads:\t%u\n",
			config->num_thपढ़ोs);

	len += snम_लिखो(buf+len, PAGE_SIZE - len,
			"Test_case:\t%s (%u)\n",
			test_हाल_str(config->test_हाल),
			config->test_हाल);

	अगर (config->test_driver)
		len += snम_लिखो(buf+len, PAGE_SIZE - len,
				"driver:\t%s\n",
				config->test_driver);
	अन्यथा
		len += snम_लिखो(buf+len, PAGE_SIZE - len,
				"driver:\tEMPTY\n");

	अगर (config->test_fs)
		len += snम_लिखो(buf+len, PAGE_SIZE - len,
				"fs:\t%s\n",
				config->test_fs);
	अन्यथा
		len += snम_लिखो(buf+len, PAGE_SIZE - len,
				"fs:\tEMPTY\n");

	mutex_unlock(&test_dev->config_mutex);

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(config);

/*
 * This ensures we करोn't allow kicking thपढ़ोs through अगर our configuration
 * is faulty.
 */
अटल पूर्णांक __trigger_config_run(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;

	test_dev->करोne = 0;

	चयन (config->test_हाल) अणु
	हाल TEST_KMOD_DRIVER:
		वापस run_test_driver(test_dev);
	हाल TEST_KMOD_FS_TYPE:
		वापस run_test_fs_type(test_dev);
	शेष:
		dev_warn(test_dev->dev,
			 "Invalid test case requested: %u\n",
			 config->test_हाल);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक trigger_config_run(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;
	पूर्णांक ret;

	mutex_lock(&test_dev->trigger_mutex);
	mutex_lock(&test_dev->config_mutex);

	ret = __trigger_config_run(test_dev);
	अगर (ret < 0)
		जाओ out;
	dev_info(test_dev->dev, "General test result: %d\n",
		 config->test_result);

	/*
	 * We must वापस 0 after a trigger even unless something went
	 * wrong with the setup of the test. If the test setup went fine
	 * then userspace must just check the result of config->test_result.
	 * One issue with relying on the वापस from a call in the kernel
	 * is अगर the kernel वापसs a possitive value using this trigger
	 * will not वापस the value to userspace, it would be lost.
	 *
	 * By not relying on capturing the वापस value of tests we are using
	 * through the trigger it also us to run tests with set -e and only
	 * fail when something went wrong with the driver upon trigger
	 * requests.
	 */
	ret = 0;

out:
	mutex_unlock(&test_dev->config_mutex);
	mutex_unlock(&test_dev->trigger_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
trigger_config_store(काष्ठा device *dev,
		     काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	पूर्णांक ret;

	अगर (test_dev->test_is_oom)
		वापस -ENOMEM;

	/* For all पूर्णांकents and purposes we करोn't care what userspace
	 * sent this trigger, we care only that we were triggered.
	 * We treat the वापस value only क्रम caputuring issues with
	 * the test setup. At this poपूर्णांक all the test variables should
	 * have been allocated so typically this should never fail.
	 */
	ret = trigger_config_run(test_dev);
	अगर (unlikely(ret < 0))
		जाओ out;

	/*
	 * Note: any वापस > 0 will be treated as success
	 * and the error value will not be available to userspace.
	 * Do not rely on trying to send to userspace a test value
	 * वापस value as possitive वापस errors will be lost.
	 */
	अगर (WARN_ON(ret > 0))
		वापस -EINVAL;

	ret = count;
out:
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(trigger_config);

/*
 * XXX: move to kम_नकलन() once merged.
 *
 * Users should use kमुक्त_स्थिर() when मुक्तing these.
 */
अटल पूर्णांक __kम_नकलन(अक्षर **dst, स्थिर अक्षर *name, माप_प्रकार count, gfp_t gfp)
अणु
	*dst = kstrndup(name, count, gfp);
	अगर (!*dst)
		वापस -ENOSPC;
	वापस count;
पूर्ण

अटल पूर्णांक config_copy_test_driver_name(काष्ठा test_config *config,
				    स्थिर अक्षर *name,
				    माप_प्रकार count)
अणु
	वापस __kम_नकलन(&config->test_driver, name, count, GFP_KERNEL);
पूर्ण


अटल पूर्णांक config_copy_test_fs(काष्ठा test_config *config, स्थिर अक्षर *name,
			       माप_प्रकार count)
अणु
	वापस __kम_नकलन(&config->test_fs, name, count, GFP_KERNEL);
पूर्ण

अटल व्योम __kmod_config_मुक्त(काष्ठा test_config *config)
अणु
	अगर (!config)
		वापस;

	kमुक्त_स्थिर(config->test_driver);
	config->test_driver = शून्य;

	kमुक्त_स्थिर(config->test_fs);
	config->test_fs = शून्य;
पूर्ण

अटल व्योम kmod_config_मुक्त(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config;

	अगर (!test_dev)
		वापस;

	config = &test_dev->config;

	mutex_lock(&test_dev->config_mutex);
	__kmod_config_मुक्त(config);
	mutex_unlock(&test_dev->config_mutex);
पूर्ण

अटल sमाप_प्रकार config_test_driver_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;
	पूर्णांक copied;

	mutex_lock(&test_dev->config_mutex);

	kमुक्त_स्थिर(config->test_driver);
	config->test_driver = शून्य;

	copied = config_copy_test_driver_name(config, buf, count);
	mutex_unlock(&test_dev->config_mutex);

	वापस copied;
पूर्ण

/*
 * As per sysfs_kf_seq_show() the buf is max PAGE_SIZE.
 */
अटल sमाप_प्रकार config_test_show_str(काष्ठा mutex *config_mutex,
				    अक्षर *dst,
				    अक्षर *src)
अणु
	पूर्णांक len;

	mutex_lock(config_mutex);
	len = snम_लिखो(dst, PAGE_SIZE, "%s\n", src);
	mutex_unlock(config_mutex);

	वापस len;
पूर्ण

अटल sमाप_प्रकार config_test_driver_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस config_test_show_str(&test_dev->config_mutex, buf,
				    config->test_driver);
पूर्ण
अटल DEVICE_ATTR_RW(config_test_driver);

अटल sमाप_प्रकार config_test_fs_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;
	पूर्णांक copied;

	mutex_lock(&test_dev->config_mutex);

	kमुक्त_स्थिर(config->test_fs);
	config->test_fs = शून्य;

	copied = config_copy_test_fs(config, buf, count);
	mutex_unlock(&test_dev->config_mutex);

	वापस copied;
पूर्ण

अटल sमाप_प्रकार config_test_fs_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस config_test_show_str(&test_dev->config_mutex, buf,
				    config->test_fs);
पूर्ण
अटल DEVICE_ATTR_RW(config_test_fs);

अटल पूर्णांक trigger_config_run_type(काष्ठा kmod_test_device *test_dev,
				   क्रमागत kmod_test_हाल test_हाल,
				   स्थिर अक्षर *test_str)
अणु
	पूर्णांक copied = 0;
	काष्ठा test_config *config = &test_dev->config;

	mutex_lock(&test_dev->config_mutex);

	चयन (test_हाल) अणु
	हाल TEST_KMOD_DRIVER:
		kमुक्त_स्थिर(config->test_driver);
		config->test_driver = शून्य;
		copied = config_copy_test_driver_name(config, test_str,
						      म_माप(test_str));
		अवरोध;
	हाल TEST_KMOD_FS_TYPE:
		kमुक्त_स्थिर(config->test_fs);
		config->test_fs = शून्य;
		copied = config_copy_test_fs(config, test_str,
					     म_माप(test_str));
		अवरोध;
	शेष:
		mutex_unlock(&test_dev->config_mutex);
		वापस -EINVAL;
	पूर्ण

	config->test_हाल = test_हाल;

	mutex_unlock(&test_dev->config_mutex);

	अगर (copied <= 0 || copied != म_माप(test_str)) अणु
		test_dev->test_is_oom = true;
		वापस -ENOMEM;
	पूर्ण

	test_dev->test_is_oom = false;

	वापस trigger_config_run(test_dev);
पूर्ण

अटल व्योम मुक्त_test_dev_info(काष्ठा kmod_test_device *test_dev)
अणु
	vमुक्त(test_dev->info);
	test_dev->info = शून्य;
पूर्ण

अटल पूर्णांक kmod_config_sync_info(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;

	मुक्त_test_dev_info(test_dev);
	test_dev->info =
		vzalloc(array_size(माप(काष्ठा kmod_test_device_info),
				   config->num_thपढ़ोs));
	अगर (!test_dev->info)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * Old kernels may not have this, अगर you want to port this code to
 * test it on older kernels.
 */
#अगर_घोषित get_kmod_umh_limit
अटल अचिन्हित पूर्णांक kmod_init_test_thपढ़ो_limit(व्योम)
अणु
	वापस get_kmod_umh_limit();
पूर्ण
#अन्यथा
अटल अचिन्हित पूर्णांक kmod_init_test_thपढ़ो_limit(व्योम)
अणु
	वापस TEST_START_NUM_THREADS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __kmod_config_init(काष्ठा kmod_test_device *test_dev)
अणु
	काष्ठा test_config *config = &test_dev->config;
	पूर्णांक ret = -ENOMEM, copied;

	__kmod_config_मुक्त(config);

	copied = config_copy_test_driver_name(config, TEST_START_DRIVER,
					      म_माप(TEST_START_DRIVER));
	अगर (copied != म_माप(TEST_START_DRIVER))
		जाओ err_out;

	copied = config_copy_test_fs(config, TEST_START_TEST_FS,
				     म_माप(TEST_START_TEST_FS));
	अगर (copied != म_माप(TEST_START_TEST_FS))
		जाओ err_out;

	config->num_thपढ़ोs = kmod_init_test_thपढ़ो_limit();
	config->test_result = 0;
	config->test_हाल = TEST_START_TEST_CASE;

	ret = kmod_config_sync_info(test_dev);
	अगर (ret)
		जाओ err_out;

	test_dev->test_is_oom = false;

	वापस 0;

err_out:
	test_dev->test_is_oom = true;
	WARN_ON(test_dev->test_is_oom);

	__kmod_config_मुक्त(config);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार reset_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	पूर्णांक ret;

	mutex_lock(&test_dev->trigger_mutex);
	mutex_lock(&test_dev->config_mutex);

	ret = __kmod_config_init(test_dev);
	अगर (ret < 0) अणु
		ret = -ENOMEM;
		dev_err(dev, "could not alloc settings for config trigger: %d\n",
		       ret);
		जाओ out;
	पूर्ण

	dev_info(dev, "reset\n");
	ret = count;

out:
	mutex_unlock(&test_dev->config_mutex);
	mutex_unlock(&test_dev->trigger_mutex);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(reset);

अटल पूर्णांक test_dev_config_update_uपूर्णांक_sync(काष्ठा kmod_test_device *test_dev,
					    स्थिर अक्षर *buf, माप_प्रकार size,
					    अचिन्हित पूर्णांक *config,
					    पूर्णांक (*test_sync)(काष्ठा kmod_test_device *test_dev))
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक old_val;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&test_dev->config_mutex);

	old_val = *config;
	*(अचिन्हित पूर्णांक *)config = val;

	ret = test_sync(test_dev);
	अगर (ret) अणु
		*(अचिन्हित पूर्णांक *)config = old_val;

		ret = test_sync(test_dev);
		WARN_ON(ret);

		mutex_unlock(&test_dev->config_mutex);
		वापस -EINVAL;
	पूर्ण

	mutex_unlock(&test_dev->config_mutex);
	/* Always वापस full ग_लिखो size even अगर we didn't consume all */
	वापस size;
पूर्ण

अटल पूर्णांक test_dev_config_update_uपूर्णांक_range(काष्ठा kmod_test_device *test_dev,
					     स्थिर अक्षर *buf, माप_प्रकार size,
					     अचिन्हित पूर्णांक *config,
					     अचिन्हित पूर्णांक min,
					     अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val < min || val > max)
		वापस -EINVAL;

	mutex_lock(&test_dev->config_mutex);
	*config = val;
	mutex_unlock(&test_dev->config_mutex);

	/* Always वापस full ग_लिखो size even अगर we didn't consume all */
	वापस size;
पूर्ण

अटल पूर्णांक test_dev_config_update_पूर्णांक(काष्ठा kmod_test_device *test_dev,
				      स्थिर अक्षर *buf, माप_प्रकार size,
				      पूर्णांक *config)
अणु
	पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&test_dev->config_mutex);
	*config = val;
	mutex_unlock(&test_dev->config_mutex);
	/* Always वापस full ग_लिखो size even अगर we didn't consume all */
	वापस size;
पूर्ण

अटल sमाप_प्रकार test_dev_config_show_पूर्णांक(काष्ठा kmod_test_device *test_dev,
					अक्षर *buf,
					पूर्णांक config)
अणु
	पूर्णांक val;

	mutex_lock(&test_dev->config_mutex);
	val = config;
	mutex_unlock(&test_dev->config_mutex);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार test_dev_config_show_uपूर्णांक(काष्ठा kmod_test_device *test_dev,
					 अक्षर *buf,
					 अचिन्हित पूर्णांक config)
अणु
	अचिन्हित पूर्णांक val;

	mutex_lock(&test_dev->config_mutex);
	val = config;
	mutex_unlock(&test_dev->config_mutex);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार test_result_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस test_dev_config_update_पूर्णांक(test_dev, buf, count,
					  &config->test_result);
पूर्ण

अटल sमाप_प्रकार config_num_thपढ़ोs_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस test_dev_config_update_uपूर्णांक_sync(test_dev, buf, count,
						&config->num_thपढ़ोs,
						kmod_config_sync_info);
पूर्ण

अटल sमाप_प्रकार config_num_thपढ़ोs_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस test_dev_config_show_पूर्णांक(test_dev, buf, config->num_thपढ़ोs);
पूर्ण
अटल DEVICE_ATTR_RW(config_num_thपढ़ोs);

अटल sमाप_प्रकार config_test_हाल_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस test_dev_config_update_uपूर्णांक_range(test_dev, buf, count,
						 &config->test_हाल,
						 __TEST_KMOD_INVALID + 1,
						 __TEST_KMOD_MAX - 1);
पूर्ण

अटल sमाप_प्रकार config_test_हाल_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस test_dev_config_show_uपूर्णांक(test_dev, buf, config->test_हाल);
पूर्ण
अटल DEVICE_ATTR_RW(config_test_हाल);

अटल sमाप_प्रकार test_result_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा kmod_test_device *test_dev = dev_to_test_dev(dev);
	काष्ठा test_config *config = &test_dev->config;

	वापस test_dev_config_show_पूर्णांक(test_dev, buf, config->test_result);
पूर्ण
अटल DEVICE_ATTR_RW(test_result);

#घोषणा TEST_KMOD_DEV_ATTR(name)		&dev_attr_##name.attr

अटल काष्ठा attribute *test_dev_attrs[] = अणु
	TEST_KMOD_DEV_ATTR(trigger_config),
	TEST_KMOD_DEV_ATTR(config),
	TEST_KMOD_DEV_ATTR(reset),

	TEST_KMOD_DEV_ATTR(config_test_driver),
	TEST_KMOD_DEV_ATTR(config_test_fs),
	TEST_KMOD_DEV_ATTR(config_num_thपढ़ोs),
	TEST_KMOD_DEV_ATTR(config_test_हाल),
	TEST_KMOD_DEV_ATTR(test_result),

	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(test_dev);

अटल पूर्णांक kmod_config_init(काष्ठा kmod_test_device *test_dev)
अणु
	पूर्णांक ret;

	mutex_lock(&test_dev->config_mutex);
	ret = __kmod_config_init(test_dev);
	mutex_unlock(&test_dev->config_mutex);

	वापस ret;
पूर्ण

अटल काष्ठा kmod_test_device *alloc_test_dev_kmod(पूर्णांक idx)
अणु
	पूर्णांक ret;
	काष्ठा kmod_test_device *test_dev;
	काष्ठा miscdevice *misc_dev;

	test_dev = vzalloc(माप(काष्ठा kmod_test_device));
	अगर (!test_dev)
		जाओ err_out;

	mutex_init(&test_dev->config_mutex);
	mutex_init(&test_dev->trigger_mutex);
	mutex_init(&test_dev->thपढ़ो_mutex);

	init_completion(&test_dev->kthपढ़ोs_करोne);

	ret = kmod_config_init(test_dev);
	अगर (ret < 0) अणु
		pr_err("Cannot alloc kmod_config_init()\n");
		जाओ err_out_मुक्त;
	पूर्ण

	test_dev->dev_idx = idx;
	misc_dev = &test_dev->misc_dev;

	misc_dev->minor = MISC_DYNAMIC_MINOR;
	misc_dev->name = kaप्र_लिखो(GFP_KERNEL, "test_kmod%d", idx);
	अगर (!misc_dev->name) अणु
		pr_err("Cannot alloc misc_dev->name\n");
		जाओ err_out_मुक्त_config;
	पूर्ण
	misc_dev->groups = test_dev_groups;

	वापस test_dev;

err_out_मुक्त_config:
	मुक्त_test_dev_info(test_dev);
	kmod_config_मुक्त(test_dev);
err_out_मुक्त:
	vमुक्त(test_dev);
	test_dev = शून्य;
err_out:
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_test_dev_kmod(काष्ठा kmod_test_device *test_dev)
अणु
	अगर (test_dev) अणु
		kमुक्त_स्थिर(test_dev->misc_dev.name);
		test_dev->misc_dev.name = शून्य;
		मुक्त_test_dev_info(test_dev);
		kmod_config_मुक्त(test_dev);
		vमुक्त(test_dev);
		test_dev = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा kmod_test_device *रेजिस्टर_test_dev_kmod(व्योम)
अणु
	काष्ठा kmod_test_device *test_dev = शून्य;
	पूर्णांक ret;

	mutex_lock(&reg_dev_mutex);

	/* पूर्णांक should suffice क्रम number of devices, test क्रम wrap */
	अगर (num_test_devs + 1 == पूर्णांक_उच्च) अणु
		pr_err("reached limit of number of test devices\n");
		जाओ out;
	पूर्ण

	test_dev = alloc_test_dev_kmod(num_test_devs);
	अगर (!test_dev)
		जाओ out;

	ret = misc_रेजिस्टर(&test_dev->misc_dev);
	अगर (ret) अणु
		pr_err("could not register misc device: %d\n", ret);
		मुक्त_test_dev_kmod(test_dev);
		जाओ out;
	पूर्ण

	test_dev->dev = test_dev->misc_dev.this_device;
	list_add_tail(&test_dev->list, &reg_test_devs);
	dev_info(test_dev->dev, "interface ready\n");

	num_test_devs++;

out:
	mutex_unlock(&reg_dev_mutex);

	वापस test_dev;

पूर्ण

अटल पूर्णांक __init test_kmod_init(व्योम)
अणु
	काष्ठा kmod_test_device *test_dev;
	पूर्णांक ret;

	test_dev = रेजिस्टर_test_dev_kmod();
	अगर (!test_dev) अणु
		pr_err("Cannot add first test kmod device\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * With some work we might be able to gracefully enable
	 * testing with this driver built-in, क्रम now this seems
	 * rather risky. For those willing to try have at it,
	 * and enable the below. Good luck! If that works, try
	 * lowering the init level क्रम more fun.
	 */
	अगर (क्रमce_init_test) अणु
		ret = trigger_config_run_type(test_dev,
					      TEST_KMOD_DRIVER, "tun");
		अगर (WARN_ON(ret))
			वापस ret;
		ret = trigger_config_run_type(test_dev,
					      TEST_KMOD_FS_TYPE, "btrfs");
		अगर (WARN_ON(ret))
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
late_initcall(test_kmod_init);

अटल
व्योम unरेजिस्टर_test_dev_kmod(काष्ठा kmod_test_device *test_dev)
अणु
	mutex_lock(&test_dev->trigger_mutex);
	mutex_lock(&test_dev->config_mutex);

	test_dev_kmod_stop_tests(test_dev);

	dev_info(test_dev->dev, "removing interface\n");
	misc_deरेजिस्टर(&test_dev->misc_dev);

	mutex_unlock(&test_dev->config_mutex);
	mutex_unlock(&test_dev->trigger_mutex);

	मुक्त_test_dev_kmod(test_dev);
पूर्ण

अटल व्योम __निकास test_kmod_निकास(व्योम)
अणु
	काष्ठा kmod_test_device *test_dev, *पंचांगp;

	mutex_lock(&reg_dev_mutex);
	list_क्रम_each_entry_safe(test_dev, पंचांगp, &reg_test_devs, list) अणु
		list_del(&test_dev->list);
		unरेजिस्टर_test_dev_kmod(test_dev);
	पूर्ण
	mutex_unlock(&reg_dev_mutex);
पूर्ण
module_निकास(test_kmod_निकास);

MODULE_AUTHOR("Luis R. Rodriguez <mcgrof@kernel.org>");
MODULE_LICENSE("GPL");
