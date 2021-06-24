<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2004 - 2006 Intel Corporation. All rights reserved.
 */

/*
 * This code implements the DMA subप्रणाली. It provides a HW-neutral पूर्णांकerface
 * क्रम other kernel code to use asynchronous memory copy capabilities,
 * अगर present, and allows dअगरferent HW DMA drivers to रेजिस्टर as providing
 * this capability.
 *
 * Due to the fact we are accelerating what is alपढ़ोy a relatively fast
 * operation, the code goes to great lengths to aव्योम additional overhead,
 * such as locking.
 *
 * LOCKING:
 *
 * The subप्रणाली keeps a global list of dma_device काष्ठाs it is रक्षित by a
 * mutex, dma_list_mutex.
 *
 * A subप्रणाली can get access to a channel by calling dmaengine_get() followed
 * by dma_find_channel(), or अगर it has need क्रम an exclusive channel it can call
 * dma_request_channel().  Once a channel is allocated a reference is taken
 * against its corresponding driver to disable removal.
 *
 * Each device has a channels list, which runs unlocked but is never modअगरied
 * once the device is रेजिस्टरed, it's just setup by the driver.
 *
 * See Documentation/driver-api/dmaengine क्रम more details
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/rculist.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/acpi_dma.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/mempool.h>
#समावेश <linux/numa.h>

#समावेश "dmaengine.h"

अटल DEFINE_MUTEX(dma_list_mutex);
अटल DEFINE_IDA(dma_ida);
अटल LIST_HEAD(dma_device_list);
अटल दीर्घ dmaengine_ref_count;

/* --- debugfs implementation --- */
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>

अटल काष्ठा dentry *rootdir;

अटल व्योम dmaengine_debug_रेजिस्टर(काष्ठा dma_device *dma_dev)
अणु
	dma_dev->dbg_dev_root = debugfs_create_dir(dev_name(dma_dev->dev),
						   rootdir);
	अगर (IS_ERR(dma_dev->dbg_dev_root))
		dma_dev->dbg_dev_root = शून्य;
पूर्ण

अटल व्योम dmaengine_debug_unरेजिस्टर(काष्ठा dma_device *dma_dev)
अणु
	debugfs_हटाओ_recursive(dma_dev->dbg_dev_root);
	dma_dev->dbg_dev_root = शून्य;
पूर्ण

अटल व्योम dmaengine_dbg_summary_show(काष्ठा seq_file *s,
				       काष्ठा dma_device *dma_dev)
अणु
	काष्ठा dma_chan *chan;

	list_क्रम_each_entry(chan, &dma_dev->channels, device_node) अणु
		अगर (chan->client_count) अणु
			seq_म_लिखो(s, " %-13s| %s", dma_chan_name(chan),
				   chan->dbg_client_name ?: "in-use");

			अगर (chan->router)
				seq_म_लिखो(s, " (via router: %s)\n",
					dev_name(chan->router->dev));
			अन्यथा
				seq_माला_दो(s, "\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dmaengine_summary_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा dma_device *dma_dev = शून्य;

	mutex_lock(&dma_list_mutex);
	list_क्रम_each_entry(dma_dev, &dma_device_list, global_node) अणु
		seq_म_लिखो(s, "dma%d (%s): number of channels: %u\n",
			   dma_dev->dev_id, dev_name(dma_dev->dev),
			   dma_dev->chancnt);

		अगर (dma_dev->dbg_summary_show)
			dma_dev->dbg_summary_show(s, dma_dev);
		अन्यथा
			dmaengine_dbg_summary_show(s, dma_dev);

		अगर (!list_is_last(&dma_dev->global_node, &dma_device_list))
			seq_माला_दो(s, "\n");
	पूर्ण
	mutex_unlock(&dma_list_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dmaengine_summary);

अटल व्योम __init dmaengine_debugfs_init(व्योम)
अणु
	rootdir = debugfs_create_dir("dmaengine", शून्य);

	/* /sys/kernel/debug/dmaengine/summary */
	debugfs_create_file("summary", 0444, rootdir, शून्य,
			    &dmaengine_summary_fops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dmaengine_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक dmaengine_debug_रेजिस्टर(काष्ठा dma_device *dma_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dmaengine_debug_unरेजिस्टर(काष्ठा dma_device *dma_dev) अणु पूर्ण
#पूर्ण_अगर	/* DEBUG_FS */

/* --- sysfs implementation --- */

#घोषणा DMA_SLAVE_NAME	"slave"

/**
 * dev_to_dma_chan - convert a device poपूर्णांकer to its sysfs container object
 * @dev:	device node
 *
 * Must be called under dma_list_mutex.
 */
अटल काष्ठा dma_chan *dev_to_dma_chan(काष्ठा device *dev)
अणु
	काष्ठा dma_chan_dev *chan_dev;

	chan_dev = container_of(dev, typeof(*chan_dev), device);
	वापस chan_dev->chan;
पूर्ण

अटल sमाप_प्रकार स_नकल_count_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dma_chan *chan;
	अचिन्हित दीर्घ count = 0;
	पूर्णांक i;
	पूर्णांक err;

	mutex_lock(&dma_list_mutex);
	chan = dev_to_dma_chan(dev);
	अगर (chan) अणु
		क्रम_each_possible_cpu(i)
			count += per_cpu_ptr(chan->local, i)->स_नकल_count;
		err = प्र_लिखो(buf, "%lu\n", count);
	पूर्ण अन्यथा
		err = -ENODEV;
	mutex_unlock(&dma_list_mutex);

	वापस err;
पूर्ण
अटल DEVICE_ATTR_RO(स_नकल_count);

अटल sमाप_प्रकार bytes_transferred_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dma_chan *chan;
	अचिन्हित दीर्घ count = 0;
	पूर्णांक i;
	पूर्णांक err;

	mutex_lock(&dma_list_mutex);
	chan = dev_to_dma_chan(dev);
	अगर (chan) अणु
		क्रम_each_possible_cpu(i)
			count += per_cpu_ptr(chan->local, i)->bytes_transferred;
		err = प्र_लिखो(buf, "%lu\n", count);
	पूर्ण अन्यथा
		err = -ENODEV;
	mutex_unlock(&dma_list_mutex);

	वापस err;
पूर्ण
अटल DEVICE_ATTR_RO(bytes_transferred);

अटल sमाप_प्रकार in_use_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा dma_chan *chan;
	पूर्णांक err;

	mutex_lock(&dma_list_mutex);
	chan = dev_to_dma_chan(dev);
	अगर (chan)
		err = प्र_लिखो(buf, "%d\n", chan->client_count);
	अन्यथा
		err = -ENODEV;
	mutex_unlock(&dma_list_mutex);

	वापस err;
पूर्ण
अटल DEVICE_ATTR_RO(in_use);

अटल काष्ठा attribute *dma_dev_attrs[] = अणु
	&dev_attr_स_नकल_count.attr,
	&dev_attr_bytes_transferred.attr,
	&dev_attr_in_use.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(dma_dev);

अटल व्योम chan_dev_release(काष्ठा device *dev)
अणु
	काष्ठा dma_chan_dev *chan_dev;

	chan_dev = container_of(dev, typeof(*chan_dev), device);
	kमुक्त(chan_dev);
पूर्ण

अटल काष्ठा class dma_devclass = अणु
	.name		= "dma",
	.dev_groups	= dma_dev_groups,
	.dev_release	= chan_dev_release,
पूर्ण;

/* --- client and device registration --- */

/* enable iteration over all operation types */
अटल dma_cap_mask_t dma_cap_mask_all;

/**
 * काष्ठा dma_chan_tbl_ent - tracks channel allocations per core/operation
 * @chan:	associated channel क्रम this entry
 */
काष्ठा dma_chan_tbl_ent अणु
	काष्ठा dma_chan *chan;
पूर्ण;

/* percpu lookup table क्रम memory-to-memory offload providers */
अटल काष्ठा dma_chan_tbl_ent __percpu *channel_table[DMA_TX_TYPE_END];

अटल पूर्णांक __init dma_channel_table_init(व्योम)
अणु
	क्रमागत dma_transaction_type cap;
	पूर्णांक err = 0;

	biपंचांगap_fill(dma_cap_mask_all.bits, DMA_TX_TYPE_END);

	/* 'interrupt', 'private', and 'slave' are channel capabilities,
	 * but are not associated with an operation so they करो not need
	 * an entry in the channel_table
	 */
	clear_bit(DMA_INTERRUPT, dma_cap_mask_all.bits);
	clear_bit(DMA_PRIVATE, dma_cap_mask_all.bits);
	clear_bit(DMA_SLAVE, dma_cap_mask_all.bits);

	क्रम_each_dma_cap_mask(cap, dma_cap_mask_all) अणु
		channel_table[cap] = alloc_percpu(काष्ठा dma_chan_tbl_ent);
		अगर (!channel_table[cap]) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (err) अणु
		pr_err("dmaengine dma_channel_table_init failure: %d\n", err);
		क्रम_each_dma_cap_mask(cap, dma_cap_mask_all)
			मुक्त_percpu(channel_table[cap]);
	पूर्ण

	वापस err;
पूर्ण
arch_initcall(dma_channel_table_init);

/**
 * dma_chan_is_local - checks अगर the channel is in the same NUMA-node as the CPU
 * @chan:	DMA channel to test
 * @cpu:	CPU index which the channel should be बंद to
 *
 * Returns true अगर the channel is in the same NUMA-node as the CPU.
 */
अटल bool dma_chan_is_local(काष्ठा dma_chan *chan, पूर्णांक cpu)
अणु
	पूर्णांक node = dev_to_node(chan->device->dev);
	वापस node == NUMA_NO_NODE ||
		cpumask_test_cpu(cpu, cpumask_of_node(node));
पूर्ण

/**
 * min_chan - finds the channel with min count and in the same NUMA-node as the CPU
 * @cap:	capability to match
 * @cpu:	CPU index which the channel should be बंद to
 *
 * If some channels are बंद to the given CPU, the one with the lowest
 * reference count is वापसed. Otherwise, CPU is ignored and only the
 * reference count is taken पूर्णांकo account.
 *
 * Must be called under dma_list_mutex.
 */
अटल काष्ठा dma_chan *min_chan(क्रमागत dma_transaction_type cap, पूर्णांक cpu)
अणु
	काष्ठा dma_device *device;
	काष्ठा dma_chan *chan;
	काष्ठा dma_chan *min = शून्य;
	काष्ठा dma_chan *localmin = शून्य;

	list_क्रम_each_entry(device, &dma_device_list, global_node) अणु
		अगर (!dma_has_cap(cap, device->cap_mask) ||
		    dma_has_cap(DMA_PRIVATE, device->cap_mask))
			जारी;
		list_क्रम_each_entry(chan, &device->channels, device_node) अणु
			अगर (!chan->client_count)
				जारी;
			अगर (!min || chan->table_count < min->table_count)
				min = chan;

			अगर (dma_chan_is_local(chan, cpu))
				अगर (!localmin ||
				    chan->table_count < localmin->table_count)
					localmin = chan;
		पूर्ण
	पूर्ण

	chan = localmin ? localmin : min;

	अगर (chan)
		chan->table_count++;

	वापस chan;
पूर्ण

/**
 * dma_channel_rebalance - redistribute the available channels
 *
 * Optimize क्रम CPU isolation (each CPU माला_लो a dedicated channel क्रम an
 * operation type) in the SMP हाल, and operation isolation (aव्योम
 * multi-tasking channels) in the non-SMP हाल.
 *
 * Must be called under dma_list_mutex.
 */
अटल व्योम dma_channel_rebalance(व्योम)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_device *device;
	पूर्णांक cpu;
	पूर्णांक cap;

	/* unकरो the last distribution */
	क्रम_each_dma_cap_mask(cap, dma_cap_mask_all)
		क्रम_each_possible_cpu(cpu)
			per_cpu_ptr(channel_table[cap], cpu)->chan = शून्य;

	list_क्रम_each_entry(device, &dma_device_list, global_node) अणु
		अगर (dma_has_cap(DMA_PRIVATE, device->cap_mask))
			जारी;
		list_क्रम_each_entry(chan, &device->channels, device_node)
			chan->table_count = 0;
	पूर्ण

	/* करोn't populate the channel_table अगर no clients are available */
	अगर (!dmaengine_ref_count)
		वापस;

	/* redistribute available channels */
	क्रम_each_dma_cap_mask(cap, dma_cap_mask_all)
		क्रम_each_online_cpu(cpu) अणु
			chan = min_chan(cap, cpu);
			per_cpu_ptr(channel_table[cap], cpu)->chan = chan;
		पूर्ण
पूर्ण

अटल पूर्णांक dma_device_satisfies_mask(काष्ठा dma_device *device,
				     स्थिर dma_cap_mask_t *want)
अणु
	dma_cap_mask_t has;

	biपंचांगap_and(has.bits, want->bits, device->cap_mask.bits,
		DMA_TX_TYPE_END);
	वापस biपंचांगap_equal(want->bits, has.bits, DMA_TX_TYPE_END);
पूर्ण

अटल काष्ठा module *dma_chan_to_owner(काष्ठा dma_chan *chan)
अणु
	वापस chan->device->owner;
पूर्ण

/**
 * balance_ref_count - catch up the channel reference count
 * @chan:	channel to balance ->client_count versus dmaengine_ref_count
 *
 * Must be called under dma_list_mutex.
 */
अटल व्योम balance_ref_count(काष्ठा dma_chan *chan)
अणु
	काष्ठा module *owner = dma_chan_to_owner(chan);

	जबतक (chan->client_count < dmaengine_ref_count) अणु
		__module_get(owner);
		chan->client_count++;
	पूर्ण
पूर्ण

अटल व्योम dma_device_release(काष्ठा kref *ref)
अणु
	काष्ठा dma_device *device = container_of(ref, काष्ठा dma_device, ref);

	list_del_rcu(&device->global_node);
	dma_channel_rebalance();

	अगर (device->device_release)
		device->device_release(device);
पूर्ण

अटल व्योम dma_device_put(काष्ठा dma_device *device)
अणु
	lockdep_निश्चित_held(&dma_list_mutex);
	kref_put(&device->ref, dma_device_release);
पूर्ण

/**
 * dma_chan_get - try to grab a DMA channel's parent driver module
 * @chan:	channel to grab
 *
 * Must be called under dma_list_mutex.
 */
अटल पूर्णांक dma_chan_get(काष्ठा dma_chan *chan)
अणु
	काष्ठा module *owner = dma_chan_to_owner(chan);
	पूर्णांक ret;

	/* The channel is alपढ़ोy in use, update client count */
	अगर (chan->client_count) अणु
		__module_get(owner);
		जाओ out;
	पूर्ण

	अगर (!try_module_get(owner))
		वापस -ENODEV;

	ret = kref_get_unless_zero(&chan->device->ref);
	अगर (!ret) अणु
		ret = -ENODEV;
		जाओ module_put_out;
	पूर्ण

	/* allocate upon first client reference */
	अगर (chan->device->device_alloc_chan_resources) अणु
		ret = chan->device->device_alloc_chan_resources(chan);
		अगर (ret < 0)
			जाओ err_out;
	पूर्ण

	अगर (!dma_has_cap(DMA_PRIVATE, chan->device->cap_mask))
		balance_ref_count(chan);

out:
	chan->client_count++;
	वापस 0;

err_out:
	dma_device_put(chan->device);
module_put_out:
	module_put(owner);
	वापस ret;
पूर्ण

/**
 * dma_chan_put - drop a reference to a DMA channel's parent driver module
 * @chan:	channel to release
 *
 * Must be called under dma_list_mutex.
 */
अटल व्योम dma_chan_put(काष्ठा dma_chan *chan)
अणु
	/* This channel is not in use, bail out */
	अगर (!chan->client_count)
		वापस;

	chan->client_count--;

	/* This channel is not in use anymore, मुक्त it */
	अगर (!chan->client_count && chan->device->device_मुक्त_chan_resources) अणु
		/* Make sure all operations have completed */
		dmaengine_synchronize(chan);
		chan->device->device_मुक्त_chan_resources(chan);
	पूर्ण

	/* If the channel is used via a DMA request router, मुक्त the mapping */
	अगर (chan->router && chan->router->route_मुक्त) अणु
		chan->router->route_मुक्त(chan->router->dev, chan->route_data);
		chan->router = शून्य;
		chan->route_data = शून्य;
	पूर्ण

	dma_device_put(chan->device);
	module_put(dma_chan_to_owner(chan));
पूर्ण

क्रमागत dma_status dma_sync_रुको(काष्ठा dma_chan *chan, dma_cookie_t cookie)
अणु
	क्रमागत dma_status status;
	अचिन्हित दीर्घ dma_sync_रुको_समयout = jअगरfies + msecs_to_jअगरfies(5000);

	dma_async_issue_pending(chan);
	करो अणु
		status = dma_async_is_tx_complete(chan, cookie, शून्य, शून्य);
		अगर (समय_after_eq(jअगरfies, dma_sync_रुको_समयout)) अणु
			dev_err(chan->device->dev, "%s: timeout!\n", __func__);
			वापस DMA_ERROR;
		पूर्ण
		अगर (status != DMA_IN_PROGRESS)
			अवरोध;
		cpu_relax();
	पूर्ण जबतक (1);

	वापस status;
पूर्ण
EXPORT_SYMBOL(dma_sync_रुको);

/**
 * dma_find_channel - find a channel to carry out the operation
 * @tx_type:	transaction type
 */
काष्ठा dma_chan *dma_find_channel(क्रमागत dma_transaction_type tx_type)
अणु
	वापस this_cpu_पढ़ो(channel_table[tx_type]->chan);
पूर्ण
EXPORT_SYMBOL(dma_find_channel);

/**
 * dma_issue_pending_all - flush all pending operations across all channels
 */
व्योम dma_issue_pending_all(व्योम)
अणु
	काष्ठा dma_device *device;
	काष्ठा dma_chan *chan;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(device, &dma_device_list, global_node) अणु
		अगर (dma_has_cap(DMA_PRIVATE, device->cap_mask))
			जारी;
		list_क्रम_each_entry(chan, &device->channels, device_node)
			अगर (chan->client_count)
				device->device_issue_pending(chan);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(dma_issue_pending_all);

पूर्णांक dma_get_slave_caps(काष्ठा dma_chan *chan, काष्ठा dma_slave_caps *caps)
अणु
	काष्ठा dma_device *device;

	अगर (!chan || !caps)
		वापस -EINVAL;

	device = chan->device;

	/* check अगर the channel supports slave transactions */
	अगर (!(test_bit(DMA_SLAVE, device->cap_mask.bits) ||
	      test_bit(DMA_CYCLIC, device->cap_mask.bits)))
		वापस -ENXIO;

	/*
	 * Check whether it reports it uses the generic slave
	 * capabilities, अगर not, that means it करोesn't support any
	 * kind of slave capabilities reporting.
	 */
	अगर (!device->directions)
		वापस -ENXIO;

	caps->src_addr_widths = device->src_addr_widths;
	caps->dst_addr_widths = device->dst_addr_widths;
	caps->directions = device->directions;
	caps->min_burst = device->min_burst;
	caps->max_burst = device->max_burst;
	caps->max_sg_burst = device->max_sg_burst;
	caps->residue_granularity = device->residue_granularity;
	caps->descriptor_reuse = device->descriptor_reuse;
	caps->cmd_छोड़ो = !!device->device_छोड़ो;
	caps->cmd_resume = !!device->device_resume;
	caps->cmd_terminate = !!device->device_terminate_all;

	/*
	 * DMA engine device might be configured with non-unअगरormly
	 * distributed slave capabilities per device channels. In this
	 * हाल the corresponding driver may provide the device_caps
	 * callback to override the generic capabilities with
	 * channel-specअगरic ones.
	 */
	अगर (device->device_caps)
		device->device_caps(chan, caps);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dma_get_slave_caps);

अटल काष्ठा dma_chan *निजी_candidate(स्थिर dma_cap_mask_t *mask,
					  काष्ठा dma_device *dev,
					  dma_filter_fn fn, व्योम *fn_param)
अणु
	काष्ठा dma_chan *chan;

	अगर (mask && !dma_device_satisfies_mask(dev, mask)) अणु
		dev_dbg(dev->dev, "%s: wrong capabilities\n", __func__);
		वापस शून्य;
	पूर्ण
	/* devices with multiple channels need special handling as we need to
	 * ensure that all channels are either निजी or खुला.
	 */
	अगर (dev->chancnt > 1 && !dma_has_cap(DMA_PRIVATE, dev->cap_mask))
		list_क्रम_each_entry(chan, &dev->channels, device_node) अणु
			/* some channels are alपढ़ोy खुलाly allocated */
			अगर (chan->client_count)
				वापस शून्य;
		पूर्ण

	list_क्रम_each_entry(chan, &dev->channels, device_node) अणु
		अगर (chan->client_count) अणु
			dev_dbg(dev->dev, "%s: %s busy\n",
				 __func__, dma_chan_name(chan));
			जारी;
		पूर्ण
		अगर (fn && !fn(chan, fn_param)) अणु
			dev_dbg(dev->dev, "%s: %s filter said false\n",
				 __func__, dma_chan_name(chan));
			जारी;
		पूर्ण
		वापस chan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_chan *find_candidate(काष्ठा dma_device *device,
				       स्थिर dma_cap_mask_t *mask,
				       dma_filter_fn fn, व्योम *fn_param)
अणु
	काष्ठा dma_chan *chan = निजी_candidate(mask, device, fn, fn_param);
	पूर्णांक err;

	अगर (chan) अणु
		/* Found a suitable channel, try to grab, prep, and वापस it.
		 * We first set DMA_PRIVATE to disable balance_ref_count as this
		 * channel will not be published in the general-purpose
		 * allocator
		 */
		dma_cap_set(DMA_PRIVATE, device->cap_mask);
		device->निजीcnt++;
		err = dma_chan_get(chan);

		अगर (err) अणु
			अगर (err == -ENODEV) अणु
				dev_dbg(device->dev, "%s: %s module removed\n",
					__func__, dma_chan_name(chan));
				list_del_rcu(&device->global_node);
			पूर्ण अन्यथा
				dev_dbg(device->dev,
					"%s: failed to get %s: (%d)\n",
					 __func__, dma_chan_name(chan), err);

			अगर (--device->निजीcnt == 0)
				dma_cap_clear(DMA_PRIVATE, device->cap_mask);

			chan = ERR_PTR(err);
		पूर्ण
	पूर्ण

	वापस chan ? chan : ERR_PTR(-EPROBE_DEFER);
पूर्ण

/**
 * dma_get_slave_channel - try to get specअगरic channel exclusively
 * @chan:	target channel
 */
काष्ठा dma_chan *dma_get_slave_channel(काष्ठा dma_chan *chan)
अणु
	पूर्णांक err = -EBUSY;

	/* lock against __dma_request_channel */
	mutex_lock(&dma_list_mutex);

	अगर (chan->client_count == 0) अणु
		काष्ठा dma_device *device = chan->device;

		dma_cap_set(DMA_PRIVATE, device->cap_mask);
		device->निजीcnt++;
		err = dma_chan_get(chan);
		अगर (err) अणु
			dev_dbg(chan->device->dev,
				"%s: failed to get %s: (%d)\n",
				__func__, dma_chan_name(chan), err);
			chan = शून्य;
			अगर (--device->निजीcnt == 0)
				dma_cap_clear(DMA_PRIVATE, device->cap_mask);
		पूर्ण
	पूर्ण अन्यथा
		chan = शून्य;

	mutex_unlock(&dma_list_mutex);


	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(dma_get_slave_channel);

काष्ठा dma_chan *dma_get_any_slave_channel(काष्ठा dma_device *device)
अणु
	dma_cap_mask_t mask;
	काष्ठा dma_chan *chan;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* lock against __dma_request_channel */
	mutex_lock(&dma_list_mutex);

	chan = find_candidate(device, &mask, शून्य, शून्य);

	mutex_unlock(&dma_list_mutex);

	वापस IS_ERR(chan) ? शून्य : chan;
पूर्ण
EXPORT_SYMBOL_GPL(dma_get_any_slave_channel);

/**
 * __dma_request_channel - try to allocate an exclusive channel
 * @mask:	capabilities that the channel must satisfy
 * @fn:		optional callback to disposition available channels
 * @fn_param:	opaque parameter to pass to dma_filter_fn()
 * @np:		device node to look क्रम DMA channels
 *
 * Returns poपूर्णांकer to appropriate DMA channel on success or शून्य.
 */
काष्ठा dma_chan *__dma_request_channel(स्थिर dma_cap_mask_t *mask,
				       dma_filter_fn fn, व्योम *fn_param,
				       काष्ठा device_node *np)
अणु
	काष्ठा dma_device *device, *_d;
	काष्ठा dma_chan *chan = शून्य;

	/* Find a channel */
	mutex_lock(&dma_list_mutex);
	list_क्रम_each_entry_safe(device, _d, &dma_device_list, global_node) अणु
		/* Finds a DMA controller with matching device node */
		अगर (np && device->dev->of_node && np != device->dev->of_node)
			जारी;

		chan = find_candidate(device, mask, fn, fn_param);
		अगर (!IS_ERR(chan))
			अवरोध;

		chan = शून्य;
	पूर्ण
	mutex_unlock(&dma_list_mutex);

	pr_debug("%s: %s (%s)\n",
		 __func__,
		 chan ? "success" : "fail",
		 chan ? dma_chan_name(chan) : शून्य);

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(__dma_request_channel);

अटल स्थिर काष्ठा dma_slave_map *dma_filter_match(काष्ठा dma_device *device,
						    स्थिर अक्षर *name,
						    काष्ठा device *dev)
अणु
	पूर्णांक i;

	अगर (!device->filter.mapcnt)
		वापस शून्य;

	क्रम (i = 0; i < device->filter.mapcnt; i++) अणु
		स्थिर काष्ठा dma_slave_map *map = &device->filter.map[i];

		अगर (!म_भेद(map->devname, dev_name(dev)) &&
		    !म_भेद(map->slave, name))
			वापस map;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * dma_request_chan - try to allocate an exclusive slave channel
 * @dev:	poपूर्णांकer to client device काष्ठाure
 * @name:	slave channel name
 *
 * Returns poपूर्णांकer to appropriate DMA channel on success or an error poपूर्णांकer.
 */
काष्ठा dma_chan *dma_request_chan(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा dma_device *d, *_d;
	काष्ठा dma_chan *chan = शून्य;

	/* If device-tree is present get slave info from here */
	अगर (dev->of_node)
		chan = of_dma_request_slave_channel(dev->of_node, name);

	/* If device was क्रमागतerated by ACPI get slave info from here */
	अगर (has_acpi_companion(dev) && !chan)
		chan = acpi_dma_request_slave_chan_by_name(dev, name);

	अगर (PTR_ERR(chan) == -EPROBE_DEFER)
		वापस chan;

	अगर (!IS_ERR_OR_शून्य(chan))
		जाओ found;

	/* Try to find the channel via the DMA filter map(s) */
	mutex_lock(&dma_list_mutex);
	list_क्रम_each_entry_safe(d, _d, &dma_device_list, global_node) अणु
		dma_cap_mask_t mask;
		स्थिर काष्ठा dma_slave_map *map = dma_filter_match(d, name, dev);

		अगर (!map)
			जारी;

		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);

		chan = find_candidate(d, &mask, d->filter.fn, map->param);
		अगर (!IS_ERR(chan))
			अवरोध;
	पूर्ण
	mutex_unlock(&dma_list_mutex);

	अगर (IS_ERR(chan))
		वापस chan;
	अगर (!chan)
		वापस ERR_PTR(-EPROBE_DEFER);

found:
#अगर_घोषित CONFIG_DEBUG_FS
	chan->dbg_client_name = kaप्र_लिखो(GFP_KERNEL, "%s:%s", dev_name(dev),
					  name);
#पूर्ण_अगर

	chan->name = kaप्र_लिखो(GFP_KERNEL, "dma:%s", name);
	अगर (!chan->name)
		वापस chan;
	chan->slave = dev;

	अगर (sysfs_create_link(&chan->dev->device.kobj, &dev->kobj,
			      DMA_SLAVE_NAME))
		dev_warn(dev, "Cannot create DMA %s symlink\n", DMA_SLAVE_NAME);
	अगर (sysfs_create_link(&dev->kobj, &chan->dev->device.kobj, chan->name))
		dev_warn(dev, "Cannot create DMA %s symlink\n", chan->name);

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(dma_request_chan);

/**
 * dma_request_chan_by_mask - allocate a channel satisfying certain capabilities
 * @mask:	capabilities that the channel must satisfy
 *
 * Returns poपूर्णांकer to appropriate DMA channel on success or an error poपूर्णांकer.
 */
काष्ठा dma_chan *dma_request_chan_by_mask(स्थिर dma_cap_mask_t *mask)
अणु
	काष्ठा dma_chan *chan;

	अगर (!mask)
		वापस ERR_PTR(-ENODEV);

	chan = __dma_request_channel(mask, शून्य, शून्य, शून्य);
	अगर (!chan) अणु
		mutex_lock(&dma_list_mutex);
		अगर (list_empty(&dma_device_list))
			chan = ERR_PTR(-EPROBE_DEFER);
		अन्यथा
			chan = ERR_PTR(-ENODEV);
		mutex_unlock(&dma_list_mutex);
	पूर्ण

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(dma_request_chan_by_mask);

व्योम dma_release_channel(काष्ठा dma_chan *chan)
अणु
	mutex_lock(&dma_list_mutex);
	WARN_ONCE(chan->client_count != 1,
		  "chan reference count %d != 1\n", chan->client_count);
	dma_chan_put(chan);
	/* drop PRIVATE cap enabled by __dma_request_channel() */
	अगर (--chan->device->निजीcnt == 0)
		dma_cap_clear(DMA_PRIVATE, chan->device->cap_mask);

	अगर (chan->slave) अणु
		sysfs_हटाओ_link(&chan->dev->device.kobj, DMA_SLAVE_NAME);
		sysfs_हटाओ_link(&chan->slave->kobj, chan->name);
		kमुक्त(chan->name);
		chan->name = शून्य;
		chan->slave = शून्य;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	kमुक्त(chan->dbg_client_name);
	chan->dbg_client_name = शून्य;
#पूर्ण_अगर
	mutex_unlock(&dma_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dma_release_channel);

/**
 * dmaengine_get - रेजिस्टर पूर्णांकerest in dma_channels
 */
व्योम dmaengine_get(व्योम)
अणु
	काष्ठा dma_device *device, *_d;
	काष्ठा dma_chan *chan;
	पूर्णांक err;

	mutex_lock(&dma_list_mutex);
	dmaengine_ref_count++;

	/* try to grab channels */
	list_क्रम_each_entry_safe(device, _d, &dma_device_list, global_node) अणु
		अगर (dma_has_cap(DMA_PRIVATE, device->cap_mask))
			जारी;
		list_क्रम_each_entry(chan, &device->channels, device_node) अणु
			err = dma_chan_get(chan);
			अगर (err == -ENODEV) अणु
				/* module हटाओd beक्रमe we could use it */
				list_del_rcu(&device->global_node);
				अवरोध;
			पूर्ण अन्यथा अगर (err)
				dev_dbg(chan->device->dev,
					"%s: failed to get %s: (%d)\n",
					__func__, dma_chan_name(chan), err);
		पूर्ण
	पूर्ण

	/* अगर this is the first reference and there were channels
	 * रुकोing we need to rebalance to get those channels
	 * incorporated पूर्णांकo the channel table
	 */
	अगर (dmaengine_ref_count == 1)
		dma_channel_rebalance();
	mutex_unlock(&dma_list_mutex);
पूर्ण
EXPORT_SYMBOL(dmaengine_get);

/**
 * dmaengine_put - let DMA drivers be हटाओd when ref_count == 0
 */
व्योम dmaengine_put(व्योम)
अणु
	काष्ठा dma_device *device, *_d;
	काष्ठा dma_chan *chan;

	mutex_lock(&dma_list_mutex);
	dmaengine_ref_count--;
	BUG_ON(dmaengine_ref_count < 0);
	/* drop channel references */
	list_क्रम_each_entry_safe(device, _d, &dma_device_list, global_node) अणु
		अगर (dma_has_cap(DMA_PRIVATE, device->cap_mask))
			जारी;
		list_क्रम_each_entry(chan, &device->channels, device_node)
			dma_chan_put(chan);
	पूर्ण
	mutex_unlock(&dma_list_mutex);
पूर्ण
EXPORT_SYMBOL(dmaengine_put);

अटल bool device_has_all_tx_types(काष्ठा dma_device *device)
अणु
	/* A device that satisfies this test has channels that will never cause
	 * an async_tx channel चयन event as all possible operation types can
	 * be handled.
	 */
	#अगर_घोषित CONFIG_ASYNC_TX_DMA
	अगर (!dma_has_cap(DMA_INTERRUPT, device->cap_mask))
		वापस false;
	#पूर्ण_अगर

	#अगर IS_ENABLED(CONFIG_ASYNC_MEMCPY)
	अगर (!dma_has_cap(DMA_MEMCPY, device->cap_mask))
		वापस false;
	#पूर्ण_अगर

	#अगर IS_ENABLED(CONFIG_ASYNC_XOR)
	अगर (!dma_has_cap(DMA_XOR, device->cap_mask))
		वापस false;

	#अगर_अघोषित CONFIG_ASYNC_TX_DISABLE_XOR_VAL_DMA
	अगर (!dma_has_cap(DMA_XOR_VAL, device->cap_mask))
		वापस false;
	#पूर्ण_अगर
	#पूर्ण_अगर

	#अगर IS_ENABLED(CONFIG_ASYNC_PQ)
	अगर (!dma_has_cap(DMA_PQ, device->cap_mask))
		वापस false;

	#अगर_अघोषित CONFIG_ASYNC_TX_DISABLE_PQ_VAL_DMA
	अगर (!dma_has_cap(DMA_PQ_VAL, device->cap_mask))
		वापस false;
	#पूर्ण_अगर
	#पूर्ण_अगर

	वापस true;
पूर्ण

अटल पूर्णांक get_dma_id(काष्ठा dma_device *device)
अणु
	पूर्णांक rc = ida_alloc(&dma_ida, GFP_KERNEL);

	अगर (rc < 0)
		वापस rc;
	device->dev_id = rc;
	वापस 0;
पूर्ण

अटल पूर्णांक __dma_async_device_channel_रेजिस्टर(काष्ठा dma_device *device,
					       काष्ठा dma_chan *chan)
अणु
	पूर्णांक rc;

	chan->local = alloc_percpu(typeof(*chan->local));
	अगर (!chan->local)
		वापस -ENOMEM;
	chan->dev = kzalloc(माप(*chan->dev), GFP_KERNEL);
	अगर (!chan->dev) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_local;
	पूर्ण

	/*
	 * When the chan_id is a negative value, we are dynamically adding
	 * the channel. Otherwise we are अटल क्रमागतerating.
	 */
	mutex_lock(&device->chan_mutex);
	chan->chan_id = ida_alloc(&device->chan_ida, GFP_KERNEL);
	mutex_unlock(&device->chan_mutex);
	अगर (chan->chan_id < 0) अणु
		pr_err("%s: unable to alloc ida for chan: %d\n",
		       __func__, chan->chan_id);
		rc = chan->chan_id;
		जाओ err_मुक्त_dev;
	पूर्ण

	chan->dev->device.class = &dma_devclass;
	chan->dev->device.parent = device->dev;
	chan->dev->chan = chan;
	chan->dev->dev_id = device->dev_id;
	dev_set_name(&chan->dev->device, "dma%dchan%d",
		     device->dev_id, chan->chan_id);
	rc = device_रेजिस्टर(&chan->dev->device);
	अगर (rc)
		जाओ err_out_ida;
	chan->client_count = 0;
	device->chancnt++;

	वापस 0;

 err_out_ida:
	mutex_lock(&device->chan_mutex);
	ida_मुक्त(&device->chan_ida, chan->chan_id);
	mutex_unlock(&device->chan_mutex);
 err_मुक्त_dev:
	kमुक्त(chan->dev);
 err_मुक्त_local:
	मुक्त_percpu(chan->local);
	chan->local = शून्य;
	वापस rc;
पूर्ण

पूर्णांक dma_async_device_channel_रेजिस्टर(काष्ठा dma_device *device,
				      काष्ठा dma_chan *chan)
अणु
	पूर्णांक rc;

	rc = __dma_async_device_channel_रेजिस्टर(device, chan);
	अगर (rc < 0)
		वापस rc;

	dma_channel_rebalance();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dma_async_device_channel_रेजिस्टर);

अटल व्योम __dma_async_device_channel_unरेजिस्टर(काष्ठा dma_device *device,
						  काष्ठा dma_chan *chan)
अणु
	WARN_ONCE(!device->device_release && chan->client_count,
		  "%s called while %d clients hold a reference\n",
		  __func__, chan->client_count);
	mutex_lock(&dma_list_mutex);
	device->chancnt--;
	chan->dev->chan = शून्य;
	mutex_unlock(&dma_list_mutex);
	mutex_lock(&device->chan_mutex);
	ida_मुक्त(&device->chan_ida, chan->chan_id);
	mutex_unlock(&device->chan_mutex);
	device_unरेजिस्टर(&chan->dev->device);
	मुक्त_percpu(chan->local);
पूर्ण

व्योम dma_async_device_channel_unरेजिस्टर(काष्ठा dma_device *device,
					 काष्ठा dma_chan *chan)
अणु
	__dma_async_device_channel_unरेजिस्टर(device, chan);
	dma_channel_rebalance();
पूर्ण
EXPORT_SYMBOL_GPL(dma_async_device_channel_unरेजिस्टर);

/**
 * dma_async_device_रेजिस्टर - रेजिस्टरs DMA devices found
 * @device:	poपूर्णांकer to &काष्ठा dma_device
 *
 * After calling this routine the काष्ठाure should not be मुक्तd except in the
 * device_release() callback which will be called after
 * dma_async_device_unरेजिस्टर() is called and no further references are taken.
 */
पूर्णांक dma_async_device_रेजिस्टर(काष्ठा dma_device *device)
अणु
	पूर्णांक rc;
	काष्ठा dma_chan* chan;

	अगर (!device)
		वापस -ENODEV;

	/* validate device routines */
	अगर (!device->dev) अणु
		pr_err("DMAdevice must have dev\n");
		वापस -EIO;
	पूर्ण

	device->owner = device->dev->driver->owner;

	अगर (dma_has_cap(DMA_MEMCPY, device->cap_mask) && !device->device_prep_dma_स_नकल) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_MEMCPY");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_XOR, device->cap_mask) && !device->device_prep_dma_xor) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_XOR");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_XOR_VAL, device->cap_mask) && !device->device_prep_dma_xor_val) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_XOR_VAL");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_PQ, device->cap_mask) && !device->device_prep_dma_pq) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_PQ");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_PQ_VAL, device->cap_mask) && !device->device_prep_dma_pq_val) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_PQ_VAL");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_MEMSET, device->cap_mask) && !device->device_prep_dma_स_रखो) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_MEMSET");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_INTERRUPT, device->cap_mask) && !device->device_prep_dma_पूर्णांकerrupt) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_INTERRUPT");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_CYCLIC, device->cap_mask) && !device->device_prep_dma_cyclic) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_CYCLIC");
		वापस -EIO;
	पूर्ण

	अगर (dma_has_cap(DMA_INTERLEAVE, device->cap_mask) && !device->device_prep_पूर्णांकerleaved_dma) अणु
		dev_err(device->dev,
			"Device claims capability %s, but op is not defined\n",
			"DMA_INTERLEAVE");
		वापस -EIO;
	पूर्ण


	अगर (!device->device_tx_status) अणु
		dev_err(device->dev, "Device tx_status is not defined\n");
		वापस -EIO;
	पूर्ण


	अगर (!device->device_issue_pending) अणु
		dev_err(device->dev, "Device issue_pending is not defined\n");
		वापस -EIO;
	पूर्ण

	अगर (!device->device_release)
		dev_dbg(device->dev,
			 "WARN: Device release is not defined so it is not safe to unbind this driver while in use\n");

	kref_init(&device->ref);

	/* note: this only matters in the
	 * CONFIG_ASYNC_TX_ENABLE_CHANNEL_SWITCH=n हाल
	 */
	अगर (device_has_all_tx_types(device))
		dma_cap_set(DMA_ASYNC_TX, device->cap_mask);

	rc = get_dma_id(device);
	अगर (rc != 0)
		वापस rc;

	mutex_init(&device->chan_mutex);
	ida_init(&device->chan_ida);

	/* represent channels in sysfs. Probably want devs too */
	list_क्रम_each_entry(chan, &device->channels, device_node) अणु
		rc = __dma_async_device_channel_रेजिस्टर(device, chan);
		अगर (rc < 0)
			जाओ err_out;
	पूर्ण

	mutex_lock(&dma_list_mutex);
	/* take references on खुला channels */
	अगर (dmaengine_ref_count && !dma_has_cap(DMA_PRIVATE, device->cap_mask))
		list_क्रम_each_entry(chan, &device->channels, device_node) अणु
			/* अगर clients are alपढ़ोy रुकोing क्रम channels we need
			 * to take references on their behalf
			 */
			अगर (dma_chan_get(chan) == -ENODEV) अणु
				/* note we can only get here क्रम the first
				 * channel as the reमुख्यing channels are
				 * guaranteed to get a reference
				 */
				rc = -ENODEV;
				mutex_unlock(&dma_list_mutex);
				जाओ err_out;
			पूर्ण
		पूर्ण
	list_add_tail_rcu(&device->global_node, &dma_device_list);
	अगर (dma_has_cap(DMA_PRIVATE, device->cap_mask))
		device->निजीcnt++;	/* Always निजी */
	dma_channel_rebalance();
	mutex_unlock(&dma_list_mutex);

	dmaengine_debug_रेजिस्टर(device);

	वापस 0;

err_out:
	/* अगर we never रेजिस्टरed a channel just release the idr */
	अगर (!device->chancnt) अणु
		ida_मुक्त(&dma_ida, device->dev_id);
		वापस rc;
	पूर्ण

	list_क्रम_each_entry(chan, &device->channels, device_node) अणु
		अगर (chan->local == शून्य)
			जारी;
		mutex_lock(&dma_list_mutex);
		chan->dev->chan = शून्य;
		mutex_unlock(&dma_list_mutex);
		device_unरेजिस्टर(&chan->dev->device);
		मुक्त_percpu(chan->local);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL(dma_async_device_रेजिस्टर);

/**
 * dma_async_device_unरेजिस्टर - unरेजिस्टर a DMA device
 * @device:	poपूर्णांकer to &काष्ठा dma_device
 *
 * This routine is called by dma driver निकास routines, dmaengine holds module
 * references to prevent it being called जबतक channels are in use.
 */
व्योम dma_async_device_unरेजिस्टर(काष्ठा dma_device *device)
अणु
	काष्ठा dma_chan *chan, *n;

	dmaengine_debug_unरेजिस्टर(device);

	list_क्रम_each_entry_safe(chan, n, &device->channels, device_node)
		__dma_async_device_channel_unरेजिस्टर(device, chan);

	mutex_lock(&dma_list_mutex);
	/*
	 * setting DMA_PRIVATE ensures the device being torn करोwn will not
	 * be used in the channel_table
	 */
	dma_cap_set(DMA_PRIVATE, device->cap_mask);
	dma_channel_rebalance();
	ida_मुक्त(&dma_ida, device->dev_id);
	dma_device_put(device);
	mutex_unlock(&dma_list_mutex);
पूर्ण
EXPORT_SYMBOL(dma_async_device_unरेजिस्टर);

अटल व्योम dmam_device_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा dma_device *device;

	device = *(काष्ठा dma_device **)res;
	dma_async_device_unरेजिस्टर(device);
पूर्ण

/**
 * dmaenginem_async_device_रेजिस्टर - रेजिस्टरs DMA devices found
 * @device:	poपूर्णांकer to &काष्ठा dma_device
 *
 * The operation is managed and will be unकरोne on driver detach.
 */
पूर्णांक dmaenginem_async_device_रेजिस्टर(काष्ठा dma_device *device)
अणु
	व्योम *p;
	पूर्णांक ret;

	p = devres_alloc(dmam_device_release, माप(व्योम *), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	ret = dma_async_device_रेजिस्टर(device);
	अगर (!ret) अणु
		*(काष्ठा dma_device **)p = device;
		devres_add(device->dev, p);
	पूर्ण अन्यथा अणु
		devres_मुक्त(p);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dmaenginem_async_device_रेजिस्टर);

काष्ठा dmaengine_unmap_pool अणु
	काष्ठा kmem_cache *cache;
	स्थिर अक्षर *name;
	mempool_t *pool;
	माप_प्रकार size;
पूर्ण;

#घोषणा __UNMAP_POOL(x) अणु .size = x, .name = "dmaengine-unmap-" __stringअगरy(x) पूर्ण
अटल काष्ठा dmaengine_unmap_pool unmap_pool[] = अणु
	__UNMAP_POOL(2),
	#अगर IS_ENABLED(CONFIG_DMA_ENGINE_RAID)
	__UNMAP_POOL(16),
	__UNMAP_POOL(128),
	__UNMAP_POOL(256),
	#पूर्ण_अगर
पूर्ण;

अटल काष्ठा dmaengine_unmap_pool *__get_unmap_pool(पूर्णांक nr)
अणु
	पूर्णांक order = get_count_order(nr);

	चयन (order) अणु
	हाल 0 ... 1:
		वापस &unmap_pool[0];
#अगर IS_ENABLED(CONFIG_DMA_ENGINE_RAID)
	हाल 2 ... 4:
		वापस &unmap_pool[1];
	हाल 5 ... 7:
		वापस &unmap_pool[2];
	हाल 8:
		वापस &unmap_pool[3];
#पूर्ण_अगर
	शेष:
		BUG();
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम dmaengine_unmap(काष्ठा kref *kref)
अणु
	काष्ठा dmaengine_unmap_data *unmap = container_of(kref, typeof(*unmap), kref);
	काष्ठा device *dev = unmap->dev;
	पूर्णांक cnt, i;

	cnt = unmap->to_cnt;
	क्रम (i = 0; i < cnt; i++)
		dma_unmap_page(dev, unmap->addr[i], unmap->len,
			       DMA_TO_DEVICE);
	cnt += unmap->from_cnt;
	क्रम (; i < cnt; i++)
		dma_unmap_page(dev, unmap->addr[i], unmap->len,
			       DMA_FROM_DEVICE);
	cnt += unmap->bidi_cnt;
	क्रम (; i < cnt; i++) अणु
		अगर (unmap->addr[i] == 0)
			जारी;
		dma_unmap_page(dev, unmap->addr[i], unmap->len,
			       DMA_BIसूचीECTIONAL);
	पूर्ण
	cnt = unmap->map_cnt;
	mempool_मुक्त(unmap, __get_unmap_pool(cnt)->pool);
पूर्ण

व्योम dmaengine_unmap_put(काष्ठा dmaengine_unmap_data *unmap)
अणु
	अगर (unmap)
		kref_put(&unmap->kref, dmaengine_unmap);
पूर्ण
EXPORT_SYMBOL_GPL(dmaengine_unmap_put);

अटल व्योम dmaengine_destroy_unmap_pool(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(unmap_pool); i++) अणु
		काष्ठा dmaengine_unmap_pool *p = &unmap_pool[i];

		mempool_destroy(p->pool);
		p->pool = शून्य;
		kmem_cache_destroy(p->cache);
		p->cache = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __init dmaengine_init_unmap_pool(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(unmap_pool); i++) अणु
		काष्ठा dmaengine_unmap_pool *p = &unmap_pool[i];
		माप_प्रकार size;

		size = माप(काष्ठा dmaengine_unmap_data) +
		       माप(dma_addr_t) * p->size;

		p->cache = kmem_cache_create(p->name, size, 0,
					     SLAB_HWCACHE_ALIGN, शून्य);
		अगर (!p->cache)
			अवरोध;
		p->pool = mempool_create_slab_pool(1, p->cache);
		अगर (!p->pool)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(unmap_pool))
		वापस 0;

	dmaengine_destroy_unmap_pool();
	वापस -ENOMEM;
पूर्ण

काष्ठा dmaengine_unmap_data *
dmaengine_get_unmap_data(काष्ठा device *dev, पूर्णांक nr, gfp_t flags)
अणु
	काष्ठा dmaengine_unmap_data *unmap;

	unmap = mempool_alloc(__get_unmap_pool(nr)->pool, flags);
	अगर (!unmap)
		वापस शून्य;

	स_रखो(unmap, 0, माप(*unmap));
	kref_init(&unmap->kref);
	unmap->dev = dev;
	unmap->map_cnt = nr;

	वापस unmap;
पूर्ण
EXPORT_SYMBOL(dmaengine_get_unmap_data);

व्योम dma_async_tx_descriptor_init(काष्ठा dma_async_tx_descriptor *tx,
	काष्ठा dma_chan *chan)
अणु
	tx->chan = chan;
	#अगर_घोषित CONFIG_ASYNC_TX_ENABLE_CHANNEL_SWITCH
	spin_lock_init(&tx->lock);
	#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(dma_async_tx_descriptor_init);

अटल अंतरभूत पूर्णांक desc_check_and_set_metadata_mode(
	काष्ठा dma_async_tx_descriptor *desc, क्रमागत dma_desc_metadata_mode mode)
अणु
	/* Make sure that the metadata mode is not mixed */
	अगर (!desc->desc_metadata_mode) अणु
		अगर (dmaengine_is_metadata_mode_supported(desc->chan, mode))
			desc->desc_metadata_mode = mode;
		अन्यथा
			वापस -ENOTSUPP;
	पूर्ण अन्यथा अगर (desc->desc_metadata_mode != mode) अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dmaengine_desc_attach_metadata(काष्ठा dma_async_tx_descriptor *desc,
				   व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक ret;

	अगर (!desc)
		वापस -EINVAL;

	ret = desc_check_and_set_metadata_mode(desc, DESC_METADATA_CLIENT);
	अगर (ret)
		वापस ret;

	अगर (!desc->metadata_ops || !desc->metadata_ops->attach)
		वापस -ENOTSUPP;

	वापस desc->metadata_ops->attach(desc, data, len);
पूर्ण
EXPORT_SYMBOL_GPL(dmaengine_desc_attach_metadata);

व्योम *dmaengine_desc_get_metadata_ptr(काष्ठा dma_async_tx_descriptor *desc,
				      माप_प्रकार *payload_len, माप_प्रकार *max_len)
अणु
	पूर्णांक ret;

	अगर (!desc)
		वापस ERR_PTR(-EINVAL);

	ret = desc_check_and_set_metadata_mode(desc, DESC_METADATA_ENGINE);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (!desc->metadata_ops || !desc->metadata_ops->get_ptr)
		वापस ERR_PTR(-ENOTSUPP);

	वापस desc->metadata_ops->get_ptr(desc, payload_len, max_len);
पूर्ण
EXPORT_SYMBOL_GPL(dmaengine_desc_get_metadata_ptr);

पूर्णांक dmaengine_desc_set_metadata_len(काष्ठा dma_async_tx_descriptor *desc,
				    माप_प्रकार payload_len)
अणु
	पूर्णांक ret;

	अगर (!desc)
		वापस -EINVAL;

	ret = desc_check_and_set_metadata_mode(desc, DESC_METADATA_ENGINE);
	अगर (ret)
		वापस ret;

	अगर (!desc->metadata_ops || !desc->metadata_ops->set_len)
		वापस -ENOTSUPP;

	वापस desc->metadata_ops->set_len(desc, payload_len);
पूर्ण
EXPORT_SYMBOL_GPL(dmaengine_desc_set_metadata_len);

/**
 * dma_रुको_क्रम_async_tx - spin रुको क्रम a transaction to complete
 * @tx:		in-flight transaction to रुको on
 */
क्रमागत dma_status
dma_रुको_क्रम_async_tx(काष्ठा dma_async_tx_descriptor *tx)
अणु
	अचिन्हित दीर्घ dma_sync_रुको_समयout = jअगरfies + msecs_to_jअगरfies(5000);

	अगर (!tx)
		वापस DMA_COMPLETE;

	जबतक (tx->cookie == -EBUSY) अणु
		अगर (समय_after_eq(jअगरfies, dma_sync_रुको_समयout)) अणु
			dev_err(tx->chan->device->dev,
				"%s timeout waiting for descriptor submission\n",
				__func__);
			वापस DMA_ERROR;
		पूर्ण
		cpu_relax();
	पूर्ण
	वापस dma_sync_रुको(tx->chan, tx->cookie);
पूर्ण
EXPORT_SYMBOL_GPL(dma_रुको_क्रम_async_tx);

/**
 * dma_run_dependencies - process dependent operations on the target channel
 * @tx:		transaction with dependencies
 *
 * Helper routine क्रम DMA drivers to process (start) dependent operations
 * on their target channel.
 */
व्योम dma_run_dependencies(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा dma_async_tx_descriptor *dep = txd_next(tx);
	काष्ठा dma_async_tx_descriptor *dep_next;
	काष्ठा dma_chan *chan;

	अगर (!dep)
		वापस;

	/* we'll submit tx->next now, so clear the link */
	txd_clear_next(tx);
	chan = dep->chan;

	/* keep submitting up until a channel चयन is detected
	 * in that हाल we will be called again as a result of
	 * processing the पूर्णांकerrupt from async_tx_channel_चयन
	 */
	क्रम (; dep; dep = dep_next) अणु
		txd_lock(dep);
		txd_clear_parent(dep);
		dep_next = txd_next(dep);
		अगर (dep_next && dep_next->chan == chan)
			txd_clear_next(dep); /* ->next will be submitted */
		अन्यथा
			dep_next = शून्य; /* submit current dep and terminate */
		txd_unlock(dep);

		dep->tx_submit(dep);
	पूर्ण

	chan->device->device_issue_pending(chan);
पूर्ण
EXPORT_SYMBOL_GPL(dma_run_dependencies);

अटल पूर्णांक __init dma_bus_init(व्योम)
अणु
	पूर्णांक err = dmaengine_init_unmap_pool();

	अगर (err)
		वापस err;

	err = class_रेजिस्टर(&dma_devclass);
	अगर (!err)
		dmaengine_debugfs_init();

	वापस err;
पूर्ण
arch_initcall(dma_bus_init);
