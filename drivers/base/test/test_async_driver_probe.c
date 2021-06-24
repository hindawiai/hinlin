<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Google, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समय.स>
#समावेश <linux/numa.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/topology.h>

#घोषणा TEST_PROBE_DELAY	(5 * 1000)	/* 5 sec */
#घोषणा TEST_PROBE_THRESHOLD	(TEST_PROBE_DELAY / 2)

अटल atomic_t warnings, errors, समयout, async_completed;

अटल पूर्णांक test_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	/*
	 * Determine अगर we have hit the "timeout" limit क्रम the test अगर we
	 * have then report it as an error, otherwise we wil sleep क्रम the
	 * required amount of समय and then report completion.
	 */
	अगर (atomic_पढ़ो(&समयout)) अणु
		dev_err(dev, "async probe took too long\n");
		atomic_inc(&errors);
	पूर्ण अन्यथा अणु
		dev_dbg(&pdev->dev, "sleeping for %d msecs in probe\n",
			 TEST_PROBE_DELAY);
		msleep(TEST_PROBE_DELAY);
		dev_dbg(&pdev->dev, "done sleeping\n");
	पूर्ण

	/*
	 * Report NUMA mismatch अगर device node is set and we are not
	 * perक्रमming an async init on that node.
	 */
	अगर (dev->driver->probe_type == PROBE_PREFER_ASYNCHRONOUS) अणु
		अगर (IS_ENABLED(CONFIG_NUMA) &&
		    dev_to_node(dev) != numa_node_id()) अणु
			dev_warn(dev, "NUMA node mismatch %d != %d\n",
				 dev_to_node(dev), numa_node_id());
			atomic_inc(&warnings);
		पूर्ण

		atomic_inc(&async_completed);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver async_driver = अणु
	.driver = अणु
		.name = "test_async_driver",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe = test_probe,
पूर्ण;

अटल काष्ठा platक्रमm_driver sync_driver = अणु
	.driver = अणु
		.name = "test_sync_driver",
		.probe_type = PROBE_FORCE_SYNCHRONOUS,
	पूर्ण,
	.probe = test_probe,
पूर्ण;

अटल काष्ठा platक्रमm_device *async_dev[NR_CPUS * 2];
अटल काष्ठा platक्रमm_device *sync_dev[2];

अटल काष्ठा platक्रमm_device *
test_platक्रमm_device_रेजिस्टर_node(अक्षर *name, पूर्णांक id, पूर्णांक nid)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc(name, id);
	अगर (!pdev)
		वापस शून्य;

	अगर (nid != NUMA_NO_NODE)
		set_dev_node(&pdev->dev, nid);

	ret = platक्रमm_device_add(pdev);
	अगर (ret) अणु
		platक्रमm_device_put(pdev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस pdev;

पूर्ण

अटल पूर्णांक __init test_async_probe_init(व्योम)
अणु
	काष्ठा platक्रमm_device **pdev = शून्य;
	पूर्णांक async_id = 0, sync_id = 0;
	अचिन्हित दीर्घ दीर्घ duration;
	kसमय_प्रकार callसमय, delta;
	पूर्णांक err, nid, cpu;

	pr_info("registering first set of asynchronous devices...\n");

	क्रम_each_online_cpu(cpu) अणु
		nid = cpu_to_node(cpu);
		pdev = &async_dev[async_id];
		*pdev =	test_platक्रमm_device_रेजिस्टर_node("test_async_driver",
							   async_id,
							   nid);
		अगर (IS_ERR(*pdev)) अणु
			err = PTR_ERR(*pdev);
			*pdev = शून्य;
			pr_err("failed to create async_dev: %d\n", err);
			जाओ err_unरेजिस्टर_async_devs;
		पूर्ण

		async_id++;
	पूर्ण

	pr_info("registering asynchronous driver...\n");
	callसमय = kसमय_get();
	err = platक्रमm_driver_रेजिस्टर(&async_driver);
	अगर (err) अणु
		pr_err("Failed to register async_driver: %d\n", err);
		जाओ err_unरेजिस्टर_async_devs;
	पूर्ण

	delta = kसमय_sub(kसमय_get(), callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ms(delta);
	pr_info("registration took %lld msecs\n", duration);
	अगर (duration > TEST_PROBE_THRESHOLD) अणु
		pr_err("test failed: probe took too long\n");
		err = -ETIMEDOUT;
		जाओ err_unरेजिस्टर_async_driver;
	पूर्ण

	pr_info("registering second set of asynchronous devices...\n");
	callसमय = kसमय_get();
	क्रम_each_online_cpu(cpu) अणु
		nid = cpu_to_node(cpu);
		pdev = &sync_dev[sync_id];

		*pdev = test_platक्रमm_device_रेजिस्टर_node("test_async_driver",
							   async_id,
							   nid);
		अगर (IS_ERR(*pdev)) अणु
			err = PTR_ERR(*pdev);
			*pdev = शून्य;
			pr_err("failed to create async_dev: %d\n", err);
			जाओ err_unरेजिस्टर_async_driver;
		पूर्ण

		async_id++;
	पूर्ण

	delta = kसमय_sub(kसमय_get(), callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ms(delta);
	dev_info(&(*pdev)->dev,
		 "registration took %lld msecs\n", duration);
	अगर (duration > TEST_PROBE_THRESHOLD) अणु
		dev_err(&(*pdev)->dev,
			"test failed: probe took too long\n");
		err = -ETIMEDOUT;
		जाओ err_unरेजिस्टर_async_driver;
	पूर्ण


	pr_info("registering first synchronous device...\n");
	nid = cpu_to_node(cpu);
	pdev = &sync_dev[sync_id];

	*pdev = test_platक्रमm_device_रेजिस्टर_node("test_sync_driver",
						   sync_id,
						   NUMA_NO_NODE);
	अगर (IS_ERR(*pdev)) अणु
		err = PTR_ERR(*pdev);
		*pdev = शून्य;
		pr_err("failed to create sync_dev: %d\n", err);
		जाओ err_unरेजिस्टर_async_driver;
	पूर्ण

	sync_id++;

	pr_info("registering synchronous driver...\n");
	callसमय = kसमय_get();
	err = platक्रमm_driver_रेजिस्टर(&sync_driver);
	अगर (err) अणु
		pr_err("Failed to register async_driver: %d\n", err);
		जाओ err_unरेजिस्टर_sync_devs;
	पूर्ण

	delta = kसमय_sub(kसमय_get(), callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ms(delta);
	pr_info("registration took %lld msecs\n", duration);
	अगर (duration < TEST_PROBE_THRESHOLD) अणु
		dev_err(&(*pdev)->dev,
			"test failed: probe was too quick\n");
		err = -ETIMEDOUT;
		जाओ err_unरेजिस्टर_sync_driver;
	पूर्ण

	pr_info("registering second synchronous device...\n");
	pdev = &sync_dev[sync_id];
	callसमय = kसमय_get();

	*pdev = test_platक्रमm_device_रेजिस्टर_node("test_sync_driver",
						   sync_id,
						   NUMA_NO_NODE);
	अगर (IS_ERR(*pdev)) अणु
		err = PTR_ERR(*pdev);
		*pdev = शून्य;
		pr_err("failed to create sync_dev: %d\n", err);
		जाओ err_unरेजिस्टर_sync_driver;
	पूर्ण

	sync_id++;

	delta = kसमय_sub(kसमय_get(), callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ms(delta);
	dev_info(&(*pdev)->dev,
		 "registration took %lld msecs\n", duration);
	अगर (duration < TEST_PROBE_THRESHOLD) अणु
		dev_err(&(*pdev)->dev,
			"test failed: probe was too quick\n");
		err = -ETIMEDOUT;
		जाओ err_unरेजिस्टर_sync_driver;
	पूर्ण

	/*
	 * The async events should have completed जबतक we were taking care
	 * of the synchronous events. We will now terminate any outstanding
	 * asynchronous probe calls reमुख्यing by क्रमcing समयout and हटाओ
	 * the driver beक्रमe we वापस which should क्रमce the flush of the
	 * pending asynchronous probe calls.
	 *
	 * Otherwise अगर they completed without errors or warnings then
	 * report successful completion.
	 */
	अगर (atomic_पढ़ो(&async_completed) != async_id) अणु
		pr_err("async events still pending, forcing timeout\n");
		atomic_inc(&समयout);
		err = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (!atomic_पढ़ो(&errors) && !atomic_पढ़ो(&warnings)) अणु
		pr_info("completed successfully\n");
		वापस 0;
	पूर्ण

err_unरेजिस्टर_sync_driver:
	platक्रमm_driver_unरेजिस्टर(&sync_driver);
err_unरेजिस्टर_sync_devs:
	जबतक (sync_id--)
		platक्रमm_device_unरेजिस्टर(sync_dev[sync_id]);
err_unरेजिस्टर_async_driver:
	platक्रमm_driver_unरेजिस्टर(&async_driver);
err_unरेजिस्टर_async_devs:
	जबतक (async_id--)
		platक्रमm_device_unरेजिस्टर(async_dev[async_id]);

	/*
	 * If err is alपढ़ोy set then count that as an additional error क्रम
	 * the test. Otherwise we will report an invalid argument error and
	 * not count that as we should have reached here as a result of
	 * errors or warnings being reported by the probe routine.
	 */
	अगर (err)
		atomic_inc(&errors);
	अन्यथा
		err = -EINVAL;

	pr_err("Test failed with %d errors and %d warnings\n",
	       atomic_पढ़ो(&errors), atomic_पढ़ो(&warnings));

	वापस err;
पूर्ण
module_init(test_async_probe_init);

अटल व्योम __निकास test_async_probe_निकास(व्योम)
अणु
	पूर्णांक id = 2;

	platक्रमm_driver_unरेजिस्टर(&async_driver);
	platक्रमm_driver_unरेजिस्टर(&sync_driver);

	जबतक (id--)
		platक्रमm_device_unरेजिस्टर(sync_dev[id]);

	id = NR_CPUS * 2;
	जबतक (id--)
		platक्रमm_device_unरेजिस्टर(async_dev[id]);
पूर्ण
module_निकास(test_async_probe_निकास);

MODULE_DESCRIPTION("Test module for asynchronous driver probing");
MODULE_AUTHOR("Dmitry Torokhov <dtor@chromium.org>");
MODULE_LICENSE("GPL");
