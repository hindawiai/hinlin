<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 HiSilicon Limited.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeping.h>

#घोषणा DMA_MAP_BENCHMARK	_IOWR('d', 1, काष्ठा map_benchmark)
#घोषणा DMA_MAP_MAX_THREADS	1024
#घोषणा DMA_MAP_MAX_SECONDS	300
#घोषणा DMA_MAP_MAX_TRANS_DELAY	(10 * NSEC_PER_MSEC)

#घोषणा DMA_MAP_BIसूचीECTIONAL	0
#घोषणा DMA_MAP_TO_DEVICE	1
#घोषणा DMA_MAP_FROM_DEVICE	2

काष्ठा map_benchmark अणु
	__u64 avg_map_100ns; /* average map latency in 100ns */
	__u64 map_stddev; /* standard deviation of map latency */
	__u64 avg_unmap_100ns; /* as above */
	__u64 unmap_stddev;
	__u32 thपढ़ोs; /* how many thपढ़ोs will करो map/unmap in parallel */
	__u32 seconds; /* how दीर्घ the test will last */
	__s32 node; /* which numa node this benchmark will run on */
	__u32 dma_bits; /* DMA addressing capability */
	__u32 dma_dir; /* DMA data direction */
	__u32 dma_trans_ns; /* समय क्रम DMA transmission in ns */
	__u32 granule;	/* how many PAGE_SIZE will करो map/unmap once a समय */
	__u8 expansion[76];	/* For future use */
पूर्ण;

काष्ठा map_benchmark_data अणु
	काष्ठा map_benchmark bparam;
	काष्ठा device *dev;
	काष्ठा dentry  *debugfs;
	क्रमागत dma_data_direction dir;
	atomic64_t sum_map_100ns;
	atomic64_t sum_unmap_100ns;
	atomic64_t sum_sq_map;
	atomic64_t sum_sq_unmap;
	atomic64_t loops;
पूर्ण;

अटल पूर्णांक map_benchmark_thपढ़ो(व्योम *data)
अणु
	व्योम *buf;
	dma_addr_t dma_addr;
	काष्ठा map_benchmark_data *map = data;
	पूर्णांक npages = map->bparam.granule;
	u64 size = npages * PAGE_SIZE;
	पूर्णांक ret = 0;

	buf = alloc_pages_exact(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (!kthपढ़ो_should_stop())  अणु
		u64 map_100ns, unmap_100ns, map_sq, unmap_sq;
		kसमय_प्रकार map_sसमय, map_eसमय, unmap_sसमय, unmap_eसमय;
		kसमय_प्रकार map_delta, unmap_delta;

		/*
		 * क्रम a non-coherent device, अगर we करोn't stain them in the
		 * cache, this will give an underestimate of the real-world
		 * overhead of BIसूचीECTIONAL or TO_DEVICE mappings;
		 * 66 means evertything goes well! 66 is lucky.
		 */
		अगर (map->dir != DMA_FROM_DEVICE)
			स_रखो(buf, 0x66, size);

		map_sसमय = kसमय_get();
		dma_addr = dma_map_single(map->dev, buf, size, map->dir);
		अगर (unlikely(dma_mapping_error(map->dev, dma_addr))) अणु
			pr_err("dma_map_single failed on %s\n",
				dev_name(map->dev));
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		map_eसमय = kसमय_get();
		map_delta = kसमय_sub(map_eसमय, map_sसमय);

		/* Pretend DMA is transmitting */
		ndelay(map->bparam.dma_trans_ns);

		unmap_sसमय = kसमय_get();
		dma_unmap_single(map->dev, dma_addr, size, map->dir);
		unmap_eसमय = kसमय_get();
		unmap_delta = kसमय_sub(unmap_eसमय, unmap_sसमय);

		/* calculate sum and sum of squares */

		map_100ns = भाग64_ul(map_delta,  100);
		unmap_100ns = भाग64_ul(unmap_delta, 100);
		map_sq = map_100ns * map_100ns;
		unmap_sq = unmap_100ns * unmap_100ns;

		atomic64_add(map_100ns, &map->sum_map_100ns);
		atomic64_add(unmap_100ns, &map->sum_unmap_100ns);
		atomic64_add(map_sq, &map->sum_sq_map);
		atomic64_add(unmap_sq, &map->sum_sq_unmap);
		atomic64_inc(&map->loops);
	पूर्ण

out:
	मुक्त_pages_exact(buf, size);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_map_benchmark(काष्ठा map_benchmark_data *map)
अणु
	काष्ठा task_काष्ठा **tsk;
	पूर्णांक thपढ़ोs = map->bparam.thपढ़ोs;
	पूर्णांक node = map->bparam.node;
	स्थिर cpumask_t *cpu_mask = cpumask_of_node(node);
	u64 loops;
	पूर्णांक ret = 0;
	पूर्णांक i;

	tsk = kदो_स्मृति_array(thपढ़ोs, माप(*tsk), GFP_KERNEL);
	अगर (!tsk)
		वापस -ENOMEM;

	get_device(map->dev);

	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		tsk[i] = kthपढ़ो_create_on_node(map_benchmark_thपढ़ो, map,
				map->bparam.node, "dma-map-benchmark/%d", i);
		अगर (IS_ERR(tsk[i])) अणु
			pr_err("create dma_map thread failed\n");
			ret = PTR_ERR(tsk[i]);
			जाओ out;
		पूर्ण

		अगर (node != NUMA_NO_NODE)
			kthपढ़ो_bind_mask(tsk[i], cpu_mask);
	पूर्ण

	/* clear the old value in the previous benchmark */
	atomic64_set(&map->sum_map_100ns, 0);
	atomic64_set(&map->sum_unmap_100ns, 0);
	atomic64_set(&map->sum_sq_map, 0);
	atomic64_set(&map->sum_sq_unmap, 0);
	atomic64_set(&map->loops, 0);

	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		get_task_काष्ठा(tsk[i]);
		wake_up_process(tsk[i]);
	पूर्ण

	msleep_पूर्णांकerruptible(map->bparam.seconds * 1000);

	/* रुको क्रम the completion of benchmark thपढ़ोs */
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		ret = kthपढ़ो_stop(tsk[i]);
		अगर (ret)
			जाओ out;
	पूर्ण

	loops = atomic64_पढ़ो(&map->loops);
	अगर (likely(loops > 0)) अणु
		u64 map_variance, unmap_variance;
		u64 sum_map = atomic64_पढ़ो(&map->sum_map_100ns);
		u64 sum_unmap = atomic64_पढ़ो(&map->sum_unmap_100ns);
		u64 sum_sq_map = atomic64_पढ़ो(&map->sum_sq_map);
		u64 sum_sq_unmap = atomic64_पढ़ो(&map->sum_sq_unmap);

		/* average latency */
		map->bparam.avg_map_100ns = भाग64_u64(sum_map, loops);
		map->bparam.avg_unmap_100ns = भाग64_u64(sum_unmap, loops);

		/* standard deviation of latency */
		map_variance = भाग64_u64(sum_sq_map, loops) -
				map->bparam.avg_map_100ns *
				map->bparam.avg_map_100ns;
		unmap_variance = भाग64_u64(sum_sq_unmap, loops) -
				map->bparam.avg_unmap_100ns *
				map->bparam.avg_unmap_100ns;
		map->bparam.map_stddev = पूर्णांक_वर्ग_मूल64(map_variance);
		map->bparam.unmap_stddev = पूर्णांक_वर्ग_मूल64(unmap_variance);
	पूर्ण

out:
	क्रम (i = 0; i < thपढ़ोs; i++)
		put_task_काष्ठा(tsk[i]);
	put_device(map->dev);
	kमुक्त(tsk);
	वापस ret;
पूर्ण

अटल दीर्घ map_benchmark_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा map_benchmark_data *map = file->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	u64 old_dma_mask;
	पूर्णांक ret;

	अगर (copy_from_user(&map->bparam, argp, माप(map->bparam)))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल DMA_MAP_BENCHMARK:
		अगर (map->bparam.thपढ़ोs == 0 ||
		    map->bparam.thपढ़ोs > DMA_MAP_MAX_THREADS) अणु
			pr_err("invalid thread number\n");
			वापस -EINVAL;
		पूर्ण

		अगर (map->bparam.seconds == 0 ||
		    map->bparam.seconds > DMA_MAP_MAX_SECONDS) अणु
			pr_err("invalid duration seconds\n");
			वापस -EINVAL;
		पूर्ण

		अगर (map->bparam.dma_trans_ns > DMA_MAP_MAX_TRANS_DELAY) अणु
			pr_err("invalid transmission delay\n");
			वापस -EINVAL;
		पूर्ण

		अगर (map->bparam.node != NUMA_NO_NODE &&
		    !node_possible(map->bparam.node)) अणु
			pr_err("invalid numa node\n");
			वापस -EINVAL;
		पूर्ण

		अगर (map->bparam.granule < 1 || map->bparam.granule > 1024) अणु
			pr_err("invalid granule size\n");
			वापस -EINVAL;
		पूर्ण

		चयन (map->bparam.dma_dir) अणु
		हाल DMA_MAP_BIसूचीECTIONAL:
			map->dir = DMA_BIसूचीECTIONAL;
			अवरोध;
		हाल DMA_MAP_FROM_DEVICE:
			map->dir = DMA_FROM_DEVICE;
			अवरोध;
		हाल DMA_MAP_TO_DEVICE:
			map->dir = DMA_TO_DEVICE;
			अवरोध;
		शेष:
			pr_err("invalid DMA direction\n");
			वापस -EINVAL;
		पूर्ण

		old_dma_mask = dma_get_mask(map->dev);

		ret = dma_set_mask(map->dev,
				   DMA_BIT_MASK(map->bparam.dma_bits));
		अगर (ret) अणु
			pr_err("failed to set dma_mask on device %s\n",
				dev_name(map->dev));
			वापस -EINVAL;
		पूर्ण

		ret = करो_map_benchmark(map);

		/*
		 * restore the original dma_mask as many devices' dma_mask are
		 * set by architectures, acpi, busses. When we bind them back
		 * to their original drivers, those drivers shouldn't see
		 * dma_mask changed by benchmark
		 */
		dma_set_mask(map->dev, old_dma_mask);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (copy_to_user(argp, &map->bparam, माप(map->bparam)))
		वापस -EFAULT;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations map_benchmark_fops = अणु
	.खोलो			= simple_खोलो,
	.unlocked_ioctl		= map_benchmark_ioctl,
पूर्ण;

अटल व्योम map_benchmark_हटाओ_debugfs(व्योम *data)
अणु
	काष्ठा map_benchmark_data *map = (काष्ठा map_benchmark_data *)data;

	debugfs_हटाओ(map->debugfs);
पूर्ण

अटल पूर्णांक __map_benchmark_probe(काष्ठा device *dev)
अणु
	काष्ठा dentry *entry;
	काष्ठा map_benchmark_data *map;
	पूर्णांक ret;

	map = devm_kzalloc(dev, माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;
	map->dev = dev;

	ret = devm_add_action(dev, map_benchmark_हटाओ_debugfs, map);
	अगर (ret) अणु
		pr_err("Can't add debugfs remove action\n");
		वापस ret;
	पूर्ण

	/*
	 * we only permit a device bound with this driver, 2nd probe
	 * will fail
	 */
	entry = debugfs_create_file("dma_map_benchmark", 0600, शून्य, map,
			&map_benchmark_fops);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);
	map->debugfs = entry;

	वापस 0;
पूर्ण

अटल पूर्णांक map_benchmark_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस __map_benchmark_probe(&pdev->dev);
पूर्ण

अटल काष्ठा platक्रमm_driver map_benchmark_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "dma_map_benchmark",
	पूर्ण,
	.probe = map_benchmark_platक्रमm_probe,
पूर्ण;

अटल पूर्णांक
map_benchmark_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस __map_benchmark_probe(&pdev->dev);
पूर्ण

अटल काष्ठा pci_driver map_benchmark_pci_driver = अणु
	.name	= "dma_map_benchmark",
	.probe	= map_benchmark_pci_probe,
पूर्ण;

अटल पूर्णांक __init map_benchmark_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&map_benchmark_pci_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&map_benchmark_platक्रमm_driver);
	अगर (ret) अणु
		pci_unरेजिस्टर_driver(&map_benchmark_pci_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास map_benchmark_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&map_benchmark_platक्रमm_driver);
	pci_unरेजिस्टर_driver(&map_benchmark_pci_driver);
पूर्ण

module_init(map_benchmark_init);
module_निकास(map_benchmark_cleanup);

MODULE_AUTHOR("Barry Song <song.bao.hua@hisilicon.com>");
MODULE_DESCRIPTION("dma_map benchmark driver");
MODULE_LICENSE("GPL");
