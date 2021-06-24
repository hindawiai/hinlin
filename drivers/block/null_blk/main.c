<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Add configfs and memory store: Kyungchan Koh <kkc6196@fb.com> and
 * Shaohua Li <shli@fb.com>
 */
#समावेश <linux/module.h>

#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश "null_blk.h"

#घोषणा PAGE_SECTORS_SHIFT	(PAGE_SHIFT - SECTOR_SHIFT)
#घोषणा PAGE_SECTORS		(1 << PAGE_SECTORS_SHIFT)
#घोषणा SECTOR_MASK		(PAGE_SECTORS - 1)

#घोषणा FREE_BATCH		16

#घोषणा TICKS_PER_SEC		50ULL
#घोषणा TIMER_INTERVAL		(NSEC_PER_SEC / TICKS_PER_SEC)

#अगर_घोषित CONFIG_BLK_DEV_शून्य_BLK_FAULT_INJECTION
अटल DECLARE_FAULT_ATTR(null_समयout_attr);
अटल DECLARE_FAULT_ATTR(null_requeue_attr);
अटल DECLARE_FAULT_ATTR(null_init_hctx_attr);
#पूर्ण_अगर

अटल अंतरभूत u64 mb_per_tick(पूर्णांक mbps)
अणु
	वापस (1 << 20) / TICKS_PER_SEC * ((u64) mbps);
पूर्ण

/*
 * Status flags क्रम nullb_device.
 *
 * CONFIGURED:	Device has been configured and turned on. Cannot reconfigure.
 * UP:		Device is currently on and visible in userspace.
 * THROTTLED:	Device is being throttled.
 * CACHE:	Device is using a ग_लिखो-back cache.
 */
क्रमागत nullb_device_flags अणु
	शून्यB_DEV_FL_CONFIGURED	= 0,
	शून्यB_DEV_FL_UP		= 1,
	शून्यB_DEV_FL_THROTTLED	= 2,
	शून्यB_DEV_FL_CACHE	= 3,
पूर्ण;

#घोषणा MAP_SZ		((PAGE_SIZE >> SECTOR_SHIFT) + 2)
/*
 * nullb_page is a page in memory क्रम nullb devices.
 *
 * @page:	The page holding the data.
 * @biपंचांगap:	The biपंचांगap represents which sector in the page has data.
 *		Each bit represents one block size. For example, sector 8
 *		will use the 7th bit
 * The highest 2 bits of biपंचांगap are क्रम special purpose. LOCK means the cache
 * page is being flushing to storage. FREE means the cache page is मुक्तd and
 * should be skipped from flushing to storage. Please see
 * null_make_cache_space
 */
काष्ठा nullb_page अणु
	काष्ठा page *page;
	DECLARE_BITMAP(biपंचांगap, MAP_SZ);
पूर्ण;
#घोषणा शून्यB_PAGE_LOCK (MAP_SZ - 1)
#घोषणा शून्यB_PAGE_FREE (MAP_SZ - 2)

अटल LIST_HEAD(nullb_list);
अटल काष्ठा mutex lock;
अटल पूर्णांक null_major;
अटल DEFINE_IDA(nullb_indexes);
अटल काष्ठा blk_mq_tag_set tag_set;

क्रमागत अणु
	शून्य_IRQ_NONE		= 0,
	शून्य_IRQ_SOFTIRQ	= 1,
	शून्य_IRQ_TIMER		= 2,
पूर्ण;

क्रमागत अणु
	शून्य_Q_BIO		= 0,
	शून्य_Q_RQ		= 1,
	शून्य_Q_MQ		= 2,
पूर्ण;

अटल bool g_virt_boundary = false;
module_param_named(virt_boundary, g_virt_boundary, bool, 0444);
MODULE_PARM_DESC(virt_boundary, "Require a virtual boundary for the device. Default: False");

अटल पूर्णांक g_no_sched;
module_param_named(no_sched, g_no_sched, पूर्णांक, 0444);
MODULE_PARM_DESC(no_sched, "No io scheduler");

अटल पूर्णांक g_submit_queues = 1;
module_param_named(submit_queues, g_submit_queues, पूर्णांक, 0444);
MODULE_PARM_DESC(submit_queues, "Number of submission queues");

अटल पूर्णांक g_home_node = NUMA_NO_NODE;
module_param_named(home_node, g_home_node, पूर्णांक, 0444);
MODULE_PARM_DESC(home_node, "Home node for the device");

#अगर_घोषित CONFIG_BLK_DEV_शून्य_BLK_FAULT_INJECTION
/*
 * For more details about fault injection, please refer to
 * Documentation/fault-injection/fault-injection.rst.
 */
अटल अक्षर g_समयout_str[80];
module_param_string(समयout, g_समयout_str, माप(g_समयout_str), 0444);
MODULE_PARM_DESC(समयout, "Fault injection. timeout=<interval>,<probability>,<space>,<times>");

अटल अक्षर g_requeue_str[80];
module_param_string(requeue, g_requeue_str, माप(g_requeue_str), 0444);
MODULE_PARM_DESC(requeue, "Fault injection. requeue=<interval>,<probability>,<space>,<times>");

अटल अक्षर g_init_hctx_str[80];
module_param_string(init_hctx, g_init_hctx_str, माप(g_init_hctx_str), 0444);
MODULE_PARM_DESC(init_hctx, "Fault injection to fail hctx init. init_hctx=<interval>,<probability>,<space>,<times>");
#पूर्ण_अगर

अटल पूर्णांक g_queue_mode = शून्य_Q_MQ;

अटल पूर्णांक null_param_store_val(स्थिर अक्षर *str, पूर्णांक *val, पूर्णांक min, पूर्णांक max)
अणु
	पूर्णांक ret, new_val;

	ret = kstrtoपूर्णांक(str, 10, &new_val);
	अगर (ret)
		वापस -EINVAL;

	अगर (new_val < min || new_val > max)
		वापस -EINVAL;

	*val = new_val;
	वापस 0;
पूर्ण

अटल पूर्णांक null_set_queue_mode(स्थिर अक्षर *str, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस null_param_store_val(str, &g_queue_mode, शून्य_Q_BIO, शून्य_Q_MQ);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops null_queue_mode_param_ops = अणु
	.set	= null_set_queue_mode,
	.get	= param_get_पूर्णांक,
पूर्ण;

device_param_cb(queue_mode, &null_queue_mode_param_ops, &g_queue_mode, 0444);
MODULE_PARM_DESC(queue_mode, "Block interface to use (0=bio,1=rq,2=multiqueue)");

अटल पूर्णांक g_gb = 250;
module_param_named(gb, g_gb, पूर्णांक, 0444);
MODULE_PARM_DESC(gb, "Size in GB");

अटल पूर्णांक g_bs = 512;
module_param_named(bs, g_bs, पूर्णांक, 0444);
MODULE_PARM_DESC(bs, "Block size (in bytes)");

अटल पूर्णांक g_max_sectors;
module_param_named(max_sectors, g_max_sectors, पूर्णांक, 0444);
MODULE_PARM_DESC(max_sectors, "Maximum size of a command (in 512B sectors)");

अटल अचिन्हित पूर्णांक nr_devices = 1;
module_param(nr_devices, uपूर्णांक, 0444);
MODULE_PARM_DESC(nr_devices, "Number of devices to register");

अटल bool g_blocking;
module_param_named(blocking, g_blocking, bool, 0444);
MODULE_PARM_DESC(blocking, "Register as a blocking blk-mq driver device");

अटल bool shared_tags;
module_param(shared_tags, bool, 0444);
MODULE_PARM_DESC(shared_tags, "Share tag set between devices for blk-mq");

अटल bool g_shared_tag_biपंचांगap;
module_param_named(shared_tag_biपंचांगap, g_shared_tag_biपंचांगap, bool, 0444);
MODULE_PARM_DESC(shared_tag_biपंचांगap, "Use shared tag bitmap for all submission queues for blk-mq");

अटल पूर्णांक g_irqmode = शून्य_IRQ_SOFTIRQ;

अटल पूर्णांक null_set_irqmode(स्थिर अक्षर *str, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस null_param_store_val(str, &g_irqmode, शून्य_IRQ_NONE,
					शून्य_IRQ_TIMER);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops null_irqmode_param_ops = अणु
	.set	= null_set_irqmode,
	.get	= param_get_पूर्णांक,
पूर्ण;

device_param_cb(irqmode, &null_irqmode_param_ops, &g_irqmode, 0444);
MODULE_PARM_DESC(irqmode, "IRQ completion handler. 0-none, 1-softirq, 2-timer");

अटल अचिन्हित दीर्घ g_completion_nsec = 10000;
module_param_named(completion_nsec, g_completion_nsec, uदीर्घ, 0444);
MODULE_PARM_DESC(completion_nsec, "Time in ns to complete a request in hardware. Default: 10,000ns");

अटल पूर्णांक g_hw_queue_depth = 64;
module_param_named(hw_queue_depth, g_hw_queue_depth, पूर्णांक, 0444);
MODULE_PARM_DESC(hw_queue_depth, "Queue depth for each hardware queue. Default: 64");

अटल bool g_use_per_node_hctx;
module_param_named(use_per_node_hctx, g_use_per_node_hctx, bool, 0444);
MODULE_PARM_DESC(use_per_node_hctx, "Use per-node allocation for hardware context queues. Default: false");

अटल bool g_zoned;
module_param_named(zoned, g_zoned, bool, S_IRUGO);
MODULE_PARM_DESC(zoned, "Make device as a host-managed zoned block device. Default: false");

अटल अचिन्हित दीर्घ g_zone_size = 256;
module_param_named(zone_size, g_zone_size, uदीर्घ, S_IRUGO);
MODULE_PARM_DESC(zone_size, "Zone size in MB when block device is zoned. Must be power-of-two: Default: 256");

अटल अचिन्हित दीर्घ g_zone_capacity;
module_param_named(zone_capacity, g_zone_capacity, uदीर्घ, 0444);
MODULE_PARM_DESC(zone_capacity, "Zone capacity in MB when block device is zoned. Can be less than or equal to zone size. Default: Zone size");

अटल अचिन्हित पूर्णांक g_zone_nr_conv;
module_param_named(zone_nr_conv, g_zone_nr_conv, uपूर्णांक, 0444);
MODULE_PARM_DESC(zone_nr_conv, "Number of conventional zones when block device is zoned. Default: 0");

अटल अचिन्हित पूर्णांक g_zone_max_खोलो;
module_param_named(zone_max_खोलो, g_zone_max_खोलो, uपूर्णांक, 0444);
MODULE_PARM_DESC(zone_max_खोलो, "Maximum number of open zones when block device is zoned. Default: 0 (no limit)");

अटल अचिन्हित पूर्णांक g_zone_max_active;
module_param_named(zone_max_active, g_zone_max_active, uपूर्णांक, 0444);
MODULE_PARM_DESC(zone_max_active, "Maximum number of active zones when block device is zoned. Default: 0 (no limit)");

अटल काष्ठा nullb_device *null_alloc_dev(व्योम);
अटल व्योम null_मुक्त_dev(काष्ठा nullb_device *dev);
अटल व्योम null_del_dev(काष्ठा nullb *nullb);
अटल पूर्णांक null_add_dev(काष्ठा nullb_device *dev);
अटल व्योम null_मुक्त_device_storage(काष्ठा nullb_device *dev, bool is_cache);

अटल अंतरभूत काष्ठा nullb_device *to_nullb_device(काष्ठा config_item *item)
अणु
	वापस item ? container_of(item, काष्ठा nullb_device, item) : शून्य;
पूर्ण

अटल अंतरभूत sमाप_प्रकार nullb_device_uपूर्णांक_attr_show(अचिन्हित पूर्णांक val, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल अंतरभूत sमाप_प्रकार nullb_device_uदीर्घ_attr_show(अचिन्हित दीर्घ val,
	अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n", val);
पूर्ण

अटल अंतरभूत sमाप_प्रकार nullb_device_bool_attr_show(bool val, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार nullb_device_uपूर्णांक_attr_store(अचिन्हित पूर्णांक *val,
	स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक result;

	result = kstrtouपूर्णांक(page, 0, &पंचांगp);
	अगर (result < 0)
		वापस result;

	*val = पंचांगp;
	वापस count;
पूर्ण

अटल sमाप_प्रकार nullb_device_uदीर्घ_attr_store(अचिन्हित दीर्घ *val,
	स्थिर अक्षर *page, माप_प्रकार count)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ पंचांगp;

	result = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (result < 0)
		वापस result;

	*val = पंचांगp;
	वापस count;
पूर्ण

अटल sमाप_प्रकार nullb_device_bool_attr_store(bool *val, स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	bool पंचांगp;
	पूर्णांक result;

	result = kstrtobool(page,  &पंचांगp);
	अगर (result < 0)
		वापस result;

	*val = पंचांगp;
	वापस count;
पूर्ण

/* The following macro should only be used with TYPE = अणुuपूर्णांक, uदीर्घ, boolपूर्ण. */
#घोषणा शून्यB_DEVICE_ATTR(NAME, TYPE, APPLY)				\
अटल sमाप_प्रकार								\
nullb_device_##NAME##_show(काष्ठा config_item *item, अक्षर *page)	\
अणु									\
	वापस nullb_device_##TYPE##_attr_show(				\
				to_nullb_device(item)->NAME, page);	\
पूर्ण									\
अटल sमाप_प्रकार								\
nullb_device_##NAME##_store(काष्ठा config_item *item, स्थिर अक्षर *page,	\
			    माप_प्रकार count)				\
अणु									\
	पूर्णांक (*apply_fn)(काष्ठा nullb_device *dev, TYPE new_value) = APPLY;\
	काष्ठा nullb_device *dev = to_nullb_device(item);		\
	TYPE new_value = 0;						\
	पूर्णांक ret;							\
									\
	ret = nullb_device_##TYPE##_attr_store(&new_value, page, count);\
	अगर (ret < 0)							\
		वापस ret;						\
	अगर (apply_fn)							\
		ret = apply_fn(dev, new_value);				\
	अन्यथा अगर (test_bit(शून्यB_DEV_FL_CONFIGURED, &dev->flags)) 	\
		ret = -EBUSY;						\
	अगर (ret < 0)							\
		वापस ret;						\
	dev->NAME = new_value;						\
	वापस count;							\
पूर्ण									\
CONFIGFS_ATTR(nullb_device_, NAME);

अटल पूर्णांक nullb_apply_submit_queues(काष्ठा nullb_device *dev,
				     अचिन्हित पूर्णांक submit_queues)
अणु
	काष्ठा nullb *nullb = dev->nullb;
	काष्ठा blk_mq_tag_set *set;

	अगर (!nullb)
		वापस 0;

	/*
	 * Make sure that null_init_hctx() करोes not access nullb->queues[] past
	 * the end of that array.
	 */
	अगर (submit_queues > nr_cpu_ids)
		वापस -EINVAL;
	set = nullb->tag_set;
	blk_mq_update_nr_hw_queues(set, submit_queues);
	वापस set->nr_hw_queues == submit_queues ? 0 : -ENOMEM;
पूर्ण

शून्यB_DEVICE_ATTR(size, uदीर्घ, शून्य);
शून्यB_DEVICE_ATTR(completion_nsec, uदीर्घ, शून्य);
शून्यB_DEVICE_ATTR(submit_queues, uपूर्णांक, nullb_apply_submit_queues);
शून्यB_DEVICE_ATTR(home_node, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(queue_mode, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(blocksize, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(max_sectors, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(irqmode, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(hw_queue_depth, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(index, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(blocking, bool, शून्य);
शून्यB_DEVICE_ATTR(use_per_node_hctx, bool, शून्य);
शून्यB_DEVICE_ATTR(memory_backed, bool, शून्य);
शून्यB_DEVICE_ATTR(discard, bool, शून्य);
शून्यB_DEVICE_ATTR(mbps, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(cache_size, uदीर्घ, शून्य);
शून्यB_DEVICE_ATTR(zoned, bool, शून्य);
शून्यB_DEVICE_ATTR(zone_size, uदीर्घ, शून्य);
शून्यB_DEVICE_ATTR(zone_capacity, uदीर्घ, शून्य);
शून्यB_DEVICE_ATTR(zone_nr_conv, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(zone_max_खोलो, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(zone_max_active, uपूर्णांक, शून्य);
शून्यB_DEVICE_ATTR(virt_boundary, bool, शून्य);

अटल sमाप_प्रकार nullb_device_घातer_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस nullb_device_bool_attr_show(to_nullb_device(item)->घातer, page);
पूर्ण

अटल sमाप_प्रकार nullb_device_घातer_store(काष्ठा config_item *item,
				     स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nullb_device *dev = to_nullb_device(item);
	bool newp = false;
	sमाप_प्रकार ret;

	ret = nullb_device_bool_attr_store(&newp, page, count);
	अगर (ret < 0)
		वापस ret;

	अगर (!dev->घातer && newp) अणु
		अगर (test_and_set_bit(शून्यB_DEV_FL_UP, &dev->flags))
			वापस count;
		अगर (null_add_dev(dev)) अणु
			clear_bit(शून्यB_DEV_FL_UP, &dev->flags);
			वापस -ENOMEM;
		पूर्ण

		set_bit(शून्यB_DEV_FL_CONFIGURED, &dev->flags);
		dev->घातer = newp;
	पूर्ण अन्यथा अगर (dev->घातer && !newp) अणु
		अगर (test_and_clear_bit(शून्यB_DEV_FL_UP, &dev->flags)) अणु
			mutex_lock(&lock);
			dev->घातer = newp;
			null_del_dev(dev->nullb);
			mutex_unlock(&lock);
		पूर्ण
		clear_bit(शून्यB_DEV_FL_CONFIGURED, &dev->flags);
	पूर्ण

	वापस count;
पूर्ण

CONFIGFS_ATTR(nullb_device_, घातer);

अटल sमाप_प्रकार nullb_device_badblocks_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा nullb_device *t_dev = to_nullb_device(item);

	वापस badblocks_show(&t_dev->badblocks, page, 0);
पूर्ण

अटल sमाप_प्रकार nullb_device_badblocks_store(काष्ठा config_item *item,
				     स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nullb_device *t_dev = to_nullb_device(item);
	अक्षर *orig, *buf, *पंचांगp;
	u64 start, end;
	पूर्णांक ret;

	orig = kstrndup(page, count, GFP_KERNEL);
	अगर (!orig)
		वापस -ENOMEM;

	buf = म_मालाip(orig);

	ret = -EINVAL;
	अगर (buf[0] != '+' && buf[0] != '-')
		जाओ out;
	पंचांगp = म_अक्षर(&buf[1], '-');
	अगर (!पंचांगp)
		जाओ out;
	*पंचांगp = '\0';
	ret = kम_से_अदीर्घl(buf + 1, 0, &start);
	अगर (ret)
		जाओ out;
	ret = kम_से_अदीर्घl(पंचांगp + 1, 0, &end);
	अगर (ret)
		जाओ out;
	ret = -EINVAL;
	अगर (start > end)
		जाओ out;
	/* enable badblocks */
	cmpxchg(&t_dev->badblocks.shअगरt, -1, 0);
	अगर (buf[0] == '+')
		ret = badblocks_set(&t_dev->badblocks, start,
			end - start + 1, 1);
	अन्यथा
		ret = badblocks_clear(&t_dev->badblocks, start,
			end - start + 1);
	अगर (ret == 0)
		ret = count;
out:
	kमुक्त(orig);
	वापस ret;
पूर्ण
CONFIGFS_ATTR(nullb_device_, badblocks);

अटल काष्ठा configfs_attribute *nullb_device_attrs[] = अणु
	&nullb_device_attr_size,
	&nullb_device_attr_completion_nsec,
	&nullb_device_attr_submit_queues,
	&nullb_device_attr_home_node,
	&nullb_device_attr_queue_mode,
	&nullb_device_attr_blocksize,
	&nullb_device_attr_max_sectors,
	&nullb_device_attr_irqmode,
	&nullb_device_attr_hw_queue_depth,
	&nullb_device_attr_index,
	&nullb_device_attr_blocking,
	&nullb_device_attr_use_per_node_hctx,
	&nullb_device_attr_घातer,
	&nullb_device_attr_memory_backed,
	&nullb_device_attr_discard,
	&nullb_device_attr_mbps,
	&nullb_device_attr_cache_size,
	&nullb_device_attr_badblocks,
	&nullb_device_attr_zoned,
	&nullb_device_attr_zone_size,
	&nullb_device_attr_zone_capacity,
	&nullb_device_attr_zone_nr_conv,
	&nullb_device_attr_zone_max_खोलो,
	&nullb_device_attr_zone_max_active,
	&nullb_device_attr_virt_boundary,
	शून्य,
पूर्ण;

अटल व्योम nullb_device_release(काष्ठा config_item *item)
अणु
	काष्ठा nullb_device *dev = to_nullb_device(item);

	null_मुक्त_device_storage(dev, false);
	null_मुक्त_dev(dev);
पूर्ण

अटल काष्ठा configfs_item_operations nullb_device_ops = अणु
	.release	= nullb_device_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nullb_device_type = अणु
	.ct_item_ops	= &nullb_device_ops,
	.ct_attrs	= nullb_device_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा
config_item *nullb_group_make_item(काष्ठा config_group *group, स्थिर अक्षर *name)
अणु
	काष्ठा nullb_device *dev;

	dev = null_alloc_dev();
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	config_item_init_type_name(&dev->item, name, &nullb_device_type);

	वापस &dev->item;
पूर्ण

अटल व्योम
nullb_group_drop_item(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	काष्ठा nullb_device *dev = to_nullb_device(item);

	अगर (test_and_clear_bit(शून्यB_DEV_FL_UP, &dev->flags)) अणु
		mutex_lock(&lock);
		dev->घातer = false;
		null_del_dev(dev->nullb);
		mutex_unlock(&lock);
	पूर्ण

	config_item_put(item);
पूर्ण

अटल sमाप_प्रकार memb_group_features_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE,
			"memory_backed,discard,bandwidth,cache,badblocks,zoned,zone_size,zone_capacity,zone_nr_conv,zone_max_open,zone_max_active,blocksize,max_sectors,virt_boundary\n");
पूर्ण

CONFIGFS_ATTR_RO(memb_group_, features);

अटल काष्ठा configfs_attribute *nullb_group_attrs[] = अणु
	&memb_group_attr_features,
	शून्य,
पूर्ण;

अटल काष्ठा configfs_group_operations nullb_group_ops = अणु
	.make_item	= nullb_group_make_item,
	.drop_item	= nullb_group_drop_item,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nullb_group_type = अणु
	.ct_group_ops	= &nullb_group_ops,
	.ct_attrs	= nullb_group_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली nullb_subsys = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "nullb",
			.ci_type = &nullb_group_type,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक null_cache_active(काष्ठा nullb *nullb)
अणु
	वापस test_bit(शून्यB_DEV_FL_CACHE, &nullb->dev->flags);
पूर्ण

अटल काष्ठा nullb_device *null_alloc_dev(व्योम)
अणु
	काष्ठा nullb_device *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;
	INIT_RADIX_TREE(&dev->data, GFP_ATOMIC);
	INIT_RADIX_TREE(&dev->cache, GFP_ATOMIC);
	अगर (badblocks_init(&dev->badblocks, 0)) अणु
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	dev->size = g_gb * 1024;
	dev->completion_nsec = g_completion_nsec;
	dev->submit_queues = g_submit_queues;
	dev->home_node = g_home_node;
	dev->queue_mode = g_queue_mode;
	dev->blocksize = g_bs;
	dev->max_sectors = g_max_sectors;
	dev->irqmode = g_irqmode;
	dev->hw_queue_depth = g_hw_queue_depth;
	dev->blocking = g_blocking;
	dev->use_per_node_hctx = g_use_per_node_hctx;
	dev->zoned = g_zoned;
	dev->zone_size = g_zone_size;
	dev->zone_capacity = g_zone_capacity;
	dev->zone_nr_conv = g_zone_nr_conv;
	dev->zone_max_खोलो = g_zone_max_खोलो;
	dev->zone_max_active = g_zone_max_active;
	dev->virt_boundary = g_virt_boundary;
	वापस dev;
पूर्ण

अटल व्योम null_मुक्त_dev(काष्ठा nullb_device *dev)
अणु
	अगर (!dev)
		वापस;

	null_मुक्त_zoned_dev(dev);
	badblocks_निकास(&dev->badblocks);
	kमुक्त(dev);
पूर्ण

अटल व्योम put_tag(काष्ठा nullb_queue *nq, अचिन्हित पूर्णांक tag)
अणु
	clear_bit_unlock(tag, nq->tag_map);

	अगर (रुकोqueue_active(&nq->रुको))
		wake_up(&nq->रुको);
पूर्ण

अटल अचिन्हित पूर्णांक get_tag(काष्ठा nullb_queue *nq)
अणु
	अचिन्हित पूर्णांक tag;

	करो अणु
		tag = find_first_zero_bit(nq->tag_map, nq->queue_depth);
		अगर (tag >= nq->queue_depth)
			वापस -1U;
	पूर्ण जबतक (test_and_set_bit_lock(tag, nq->tag_map));

	वापस tag;
पूर्ण

अटल व्योम मुक्त_cmd(काष्ठा nullb_cmd *cmd)
अणु
	put_tag(cmd->nq, cmd->tag);
पूर्ण

अटल क्रमागत hrसमयr_restart null_cmd_समयr_expired(काष्ठा hrसमयr *समयr);

अटल काष्ठा nullb_cmd *__alloc_cmd(काष्ठा nullb_queue *nq)
अणु
	काष्ठा nullb_cmd *cmd;
	अचिन्हित पूर्णांक tag;

	tag = get_tag(nq);
	अगर (tag != -1U) अणु
		cmd = &nq->cmds[tag];
		cmd->tag = tag;
		cmd->error = BLK_STS_OK;
		cmd->nq = nq;
		अगर (nq->dev->irqmode == शून्य_IRQ_TIMER) अणु
			hrसमयr_init(&cmd->समयr, CLOCK_MONOTONIC,
				     HRTIMER_MODE_REL);
			cmd->समयr.function = null_cmd_समयr_expired;
		पूर्ण
		वापस cmd;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा nullb_cmd *alloc_cmd(काष्ठा nullb_queue *nq, पूर्णांक can_रुको)
अणु
	काष्ठा nullb_cmd *cmd;
	DEFINE_WAIT(रुको);

	cmd = __alloc_cmd(nq);
	अगर (cmd || !can_रुको)
		वापस cmd;

	करो अणु
		prepare_to_रुको(&nq->रुको, &रुको, TASK_UNINTERRUPTIBLE);
		cmd = __alloc_cmd(nq);
		अगर (cmd)
			अवरोध;

		io_schedule();
	पूर्ण जबतक (1);

	finish_रुको(&nq->रुको, &रुको);
	वापस cmd;
पूर्ण

अटल व्योम end_cmd(काष्ठा nullb_cmd *cmd)
अणु
	पूर्णांक queue_mode = cmd->nq->dev->queue_mode;

	चयन (queue_mode)  अणु
	हाल शून्य_Q_MQ:
		blk_mq_end_request(cmd->rq, cmd->error);
		वापस;
	हाल शून्य_Q_BIO:
		cmd->bio->bi_status = cmd->error;
		bio_endio(cmd->bio);
		अवरोध;
	पूर्ण

	मुक्त_cmd(cmd);
पूर्ण

अटल क्रमागत hrसमयr_restart null_cmd_समयr_expired(काष्ठा hrसमयr *समयr)
अणु
	end_cmd(container_of(समयr, काष्ठा nullb_cmd, समयr));

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम null_cmd_end_समयr(काष्ठा nullb_cmd *cmd)
अणु
	kसमय_प्रकार kt = cmd->nq->dev->completion_nsec;

	hrसमयr_start(&cmd->समयr, kt, HRTIMER_MODE_REL);
पूर्ण

अटल व्योम null_complete_rq(काष्ठा request *rq)
अणु
	end_cmd(blk_mq_rq_to_pdu(rq));
पूर्ण

अटल काष्ठा nullb_page *null_alloc_page(gfp_t gfp_flags)
अणु
	काष्ठा nullb_page *t_page;

	t_page = kदो_स्मृति(माप(काष्ठा nullb_page), gfp_flags);
	अगर (!t_page)
		जाओ out;

	t_page->page = alloc_pages(gfp_flags, 0);
	अगर (!t_page->page)
		जाओ out_मुक्तpage;

	स_रखो(t_page->biपंचांगap, 0, माप(t_page->biपंचांगap));
	वापस t_page;
out_मुक्तpage:
	kमुक्त(t_page);
out:
	वापस शून्य;
पूर्ण

अटल व्योम null_मुक्त_page(काष्ठा nullb_page *t_page)
अणु
	__set_bit(शून्यB_PAGE_FREE, t_page->biपंचांगap);
	अगर (test_bit(शून्यB_PAGE_LOCK, t_page->biपंचांगap))
		वापस;
	__मुक्त_page(t_page->page);
	kमुक्त(t_page);
पूर्ण

अटल bool null_page_empty(काष्ठा nullb_page *page)
अणु
	पूर्णांक size = MAP_SZ - 2;

	वापस find_first_bit(page->biपंचांगap, size) == size;
पूर्ण

अटल व्योम null_मुक्त_sector(काष्ठा nullb *nullb, sector_t sector,
	bool is_cache)
अणु
	अचिन्हित पूर्णांक sector_bit;
	u64 idx;
	काष्ठा nullb_page *t_page, *ret;
	काष्ठा radix_tree_root *root;

	root = is_cache ? &nullb->dev->cache : &nullb->dev->data;
	idx = sector >> PAGE_SECTORS_SHIFT;
	sector_bit = (sector & SECTOR_MASK);

	t_page = radix_tree_lookup(root, idx);
	अगर (t_page) अणु
		__clear_bit(sector_bit, t_page->biपंचांगap);

		अगर (null_page_empty(t_page)) अणु
			ret = radix_tree_delete_item(root, idx, t_page);
			WARN_ON(ret != t_page);
			null_मुक्त_page(ret);
			अगर (is_cache)
				nullb->dev->curr_cache -= PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा nullb_page *null_radix_tree_insert(काष्ठा nullb *nullb, u64 idx,
	काष्ठा nullb_page *t_page, bool is_cache)
अणु
	काष्ठा radix_tree_root *root;

	root = is_cache ? &nullb->dev->cache : &nullb->dev->data;

	अगर (radix_tree_insert(root, idx, t_page)) अणु
		null_मुक्त_page(t_page);
		t_page = radix_tree_lookup(root, idx);
		WARN_ON(!t_page || t_page->page->index != idx);
	पूर्ण अन्यथा अगर (is_cache)
		nullb->dev->curr_cache += PAGE_SIZE;

	वापस t_page;
पूर्ण

अटल व्योम null_मुक्त_device_storage(काष्ठा nullb_device *dev, bool is_cache)
अणु
	अचिन्हित दीर्घ pos = 0;
	पूर्णांक nr_pages;
	काष्ठा nullb_page *ret, *t_pages[FREE_BATCH];
	काष्ठा radix_tree_root *root;

	root = is_cache ? &dev->cache : &dev->data;

	करो अणु
		पूर्णांक i;

		nr_pages = radix_tree_gang_lookup(root,
				(व्योम **)t_pages, pos, FREE_BATCH);

		क्रम (i = 0; i < nr_pages; i++) अणु
			pos = t_pages[i]->page->index;
			ret = radix_tree_delete_item(root, pos, t_pages[i]);
			WARN_ON(ret != t_pages[i]);
			null_मुक्त_page(ret);
		पूर्ण

		pos++;
	पूर्ण जबतक (nr_pages == FREE_BATCH);

	अगर (is_cache)
		dev->curr_cache = 0;
पूर्ण

अटल काष्ठा nullb_page *__null_lookup_page(काष्ठा nullb *nullb,
	sector_t sector, bool क्रम_ग_लिखो, bool is_cache)
अणु
	अचिन्हित पूर्णांक sector_bit;
	u64 idx;
	काष्ठा nullb_page *t_page;
	काष्ठा radix_tree_root *root;

	idx = sector >> PAGE_SECTORS_SHIFT;
	sector_bit = (sector & SECTOR_MASK);

	root = is_cache ? &nullb->dev->cache : &nullb->dev->data;
	t_page = radix_tree_lookup(root, idx);
	WARN_ON(t_page && t_page->page->index != idx);

	अगर (t_page && (क्रम_ग_लिखो || test_bit(sector_bit, t_page->biपंचांगap)))
		वापस t_page;

	वापस शून्य;
पूर्ण

अटल काष्ठा nullb_page *null_lookup_page(काष्ठा nullb *nullb,
	sector_t sector, bool क्रम_ग_लिखो, bool ignore_cache)
अणु
	काष्ठा nullb_page *page = शून्य;

	अगर (!ignore_cache)
		page = __null_lookup_page(nullb, sector, क्रम_ग_लिखो, true);
	अगर (page)
		वापस page;
	वापस __null_lookup_page(nullb, sector, क्रम_ग_लिखो, false);
पूर्ण

अटल काष्ठा nullb_page *null_insert_page(काष्ठा nullb *nullb,
					   sector_t sector, bool ignore_cache)
	__releases(&nullb->lock)
	__acquires(&nullb->lock)
अणु
	u64 idx;
	काष्ठा nullb_page *t_page;

	t_page = null_lookup_page(nullb, sector, true, ignore_cache);
	अगर (t_page)
		वापस t_page;

	spin_unlock_irq(&nullb->lock);

	t_page = null_alloc_page(GFP_NOIO);
	अगर (!t_page)
		जाओ out_lock;

	अगर (radix_tree_preload(GFP_NOIO))
		जाओ out_मुक्तpage;

	spin_lock_irq(&nullb->lock);
	idx = sector >> PAGE_SECTORS_SHIFT;
	t_page->page->index = idx;
	t_page = null_radix_tree_insert(nullb, idx, t_page, !ignore_cache);
	radix_tree_preload_end();

	वापस t_page;
out_मुक्तpage:
	null_मुक्त_page(t_page);
out_lock:
	spin_lock_irq(&nullb->lock);
	वापस null_lookup_page(nullb, sector, true, ignore_cache);
पूर्ण

अटल पूर्णांक null_flush_cache_page(काष्ठा nullb *nullb, काष्ठा nullb_page *c_page)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक offset;
	u64 idx;
	काष्ठा nullb_page *t_page, *ret;
	व्योम *dst, *src;

	idx = c_page->page->index;

	t_page = null_insert_page(nullb, idx << PAGE_SECTORS_SHIFT, true);

	__clear_bit(शून्यB_PAGE_LOCK, c_page->biपंचांगap);
	अगर (test_bit(शून्यB_PAGE_FREE, c_page->biपंचांगap)) अणु
		null_मुक्त_page(c_page);
		अगर (t_page && null_page_empty(t_page)) अणु
			ret = radix_tree_delete_item(&nullb->dev->data,
				idx, t_page);
			null_मुक्त_page(t_page);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (!t_page)
		वापस -ENOMEM;

	src = kmap_atomic(c_page->page);
	dst = kmap_atomic(t_page->page);

	क्रम (i = 0; i < PAGE_SECTORS;
			i += (nullb->dev->blocksize >> SECTOR_SHIFT)) अणु
		अगर (test_bit(i, c_page->biपंचांगap)) अणु
			offset = (i << SECTOR_SHIFT);
			स_नकल(dst + offset, src + offset,
				nullb->dev->blocksize);
			__set_bit(i, t_page->biपंचांगap);
		पूर्ण
	पूर्ण

	kunmap_atomic(dst);
	kunmap_atomic(src);

	ret = radix_tree_delete_item(&nullb->dev->cache, idx, c_page);
	null_मुक्त_page(ret);
	nullb->dev->curr_cache -= PAGE_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक null_make_cache_space(काष्ठा nullb *nullb, अचिन्हित दीर्घ n)
अणु
	पूर्णांक i, err, nr_pages;
	काष्ठा nullb_page *c_pages[FREE_BATCH];
	अचिन्हित दीर्घ flushed = 0, one_round;

again:
	अगर ((nullb->dev->cache_size * 1024 * 1024) >
	     nullb->dev->curr_cache + n || nullb->dev->curr_cache == 0)
		वापस 0;

	nr_pages = radix_tree_gang_lookup(&nullb->dev->cache,
			(व्योम **)c_pages, nullb->cache_flush_pos, FREE_BATCH);
	/*
	 * nullb_flush_cache_page could unlock beक्रमe using the c_pages. To
	 * aव्योम race, we करोn't allow page मुक्त
	 */
	क्रम (i = 0; i < nr_pages; i++) अणु
		nullb->cache_flush_pos = c_pages[i]->page->index;
		/*
		 * We found the page which is being flushed to disk by other
		 * thपढ़ोs
		 */
		अगर (test_bit(शून्यB_PAGE_LOCK, c_pages[i]->biपंचांगap))
			c_pages[i] = शून्य;
		अन्यथा
			__set_bit(शून्यB_PAGE_LOCK, c_pages[i]->biपंचांगap);
	पूर्ण

	one_round = 0;
	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (c_pages[i] == शून्य)
			जारी;
		err = null_flush_cache_page(nullb, c_pages[i]);
		अगर (err)
			वापस err;
		one_round++;
	पूर्ण
	flushed += one_round << PAGE_SHIFT;

	अगर (n > flushed) अणु
		अगर (nr_pages == 0)
			nullb->cache_flush_pos = 0;
		अगर (one_round == 0) अणु
			/* give other thपढ़ोs a chance */
			spin_unlock_irq(&nullb->lock);
			spin_lock_irq(&nullb->lock);
		पूर्ण
		जाओ again;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक copy_to_nullb(काष्ठा nullb *nullb, काष्ठा page *source,
	अचिन्हित पूर्णांक off, sector_t sector, माप_प्रकार n, bool is_fua)
अणु
	माप_प्रकार temp, count = 0;
	अचिन्हित पूर्णांक offset;
	काष्ठा nullb_page *t_page;
	व्योम *dst, *src;

	जबतक (count < n) अणु
		temp = min_t(माप_प्रकार, nullb->dev->blocksize, n - count);

		अगर (null_cache_active(nullb) && !is_fua)
			null_make_cache_space(nullb, PAGE_SIZE);

		offset = (sector & SECTOR_MASK) << SECTOR_SHIFT;
		t_page = null_insert_page(nullb, sector,
			!null_cache_active(nullb) || is_fua);
		अगर (!t_page)
			वापस -ENOSPC;

		src = kmap_atomic(source);
		dst = kmap_atomic(t_page->page);
		स_नकल(dst + offset, src + off + count, temp);
		kunmap_atomic(dst);
		kunmap_atomic(src);

		__set_bit(sector & SECTOR_MASK, t_page->biपंचांगap);

		अगर (is_fua)
			null_मुक्त_sector(nullb, sector, true);

		count += temp;
		sector += temp >> SECTOR_SHIFT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक copy_from_nullb(काष्ठा nullb *nullb, काष्ठा page *dest,
	अचिन्हित पूर्णांक off, sector_t sector, माप_प्रकार n)
अणु
	माप_प्रकार temp, count = 0;
	अचिन्हित पूर्णांक offset;
	काष्ठा nullb_page *t_page;
	व्योम *dst, *src;

	जबतक (count < n) अणु
		temp = min_t(माप_प्रकार, nullb->dev->blocksize, n - count);

		offset = (sector & SECTOR_MASK) << SECTOR_SHIFT;
		t_page = null_lookup_page(nullb, sector, false,
			!null_cache_active(nullb));

		dst = kmap_atomic(dest);
		अगर (!t_page) अणु
			स_रखो(dst + off + count, 0, temp);
			जाओ next;
		पूर्ण
		src = kmap_atomic(t_page->page);
		स_नकल(dst + off + count, src + offset, temp);
		kunmap_atomic(src);
next:
		kunmap_atomic(dst);

		count += temp;
		sector += temp >> SECTOR_SHIFT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nullb_fill_pattern(काष्ठा nullb *nullb, काष्ठा page *page,
			       अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off)
अणु
	व्योम *dst;

	dst = kmap_atomic(page);
	स_रखो(dst + off, 0xFF, len);
	kunmap_atomic(dst);
पूर्ण

blk_status_t null_handle_discard(काष्ठा nullb_device *dev,
				 sector_t sector, sector_t nr_sectors)
अणु
	काष्ठा nullb *nullb = dev->nullb;
	माप_प्रकार n = nr_sectors << SECTOR_SHIFT;
	माप_प्रकार temp;

	spin_lock_irq(&nullb->lock);
	जबतक (n > 0) अणु
		temp = min_t(माप_प्रकार, n, dev->blocksize);
		null_मुक्त_sector(nullb, sector, false);
		अगर (null_cache_active(nullb))
			null_मुक्त_sector(nullb, sector, true);
		sector += temp >> SECTOR_SHIFT;
		n -= temp;
	पूर्ण
	spin_unlock_irq(&nullb->lock);

	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक null_handle_flush(काष्ठा nullb *nullb)
अणु
	पूर्णांक err;

	अगर (!null_cache_active(nullb))
		वापस 0;

	spin_lock_irq(&nullb->lock);
	जबतक (true) अणु
		err = null_make_cache_space(nullb,
			nullb->dev->cache_size * 1024 * 1024);
		अगर (err || nullb->dev->curr_cache == 0)
			अवरोध;
	पूर्ण

	WARN_ON(!radix_tree_empty(&nullb->dev->cache));
	spin_unlock_irq(&nullb->lock);
	वापस err;
पूर्ण

अटल पूर्णांक null_transfer(काष्ठा nullb *nullb, काष्ठा page *page,
	अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off, bool is_ग_लिखो, sector_t sector,
	bool is_fua)
अणु
	काष्ठा nullb_device *dev = nullb->dev;
	अचिन्हित पूर्णांक valid_len = len;
	पूर्णांक err = 0;

	अगर (!is_ग_लिखो) अणु
		अगर (dev->zoned)
			valid_len = null_zone_valid_पढ़ो_len(nullb,
				sector, len);

		अगर (valid_len) अणु
			err = copy_from_nullb(nullb, page, off,
				sector, valid_len);
			off += valid_len;
			len -= valid_len;
		पूर्ण

		अगर (len)
			nullb_fill_pattern(nullb, page, len, off);
		flush_dcache_page(page);
	पूर्ण अन्यथा अणु
		flush_dcache_page(page);
		err = copy_to_nullb(nullb, page, off, sector, len, is_fua);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक null_handle_rq(काष्ठा nullb_cmd *cmd)
अणु
	काष्ठा request *rq = cmd->rq;
	काष्ठा nullb *nullb = cmd->nq->dev->nullb;
	पूर्णांक err;
	अचिन्हित पूर्णांक len;
	sector_t sector = blk_rq_pos(rq);
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bvec;

	spin_lock_irq(&nullb->lock);
	rq_क्रम_each_segment(bvec, rq, iter) अणु
		len = bvec.bv_len;
		err = null_transfer(nullb, bvec.bv_page, len, bvec.bv_offset,
				     op_is_ग_लिखो(req_op(rq)), sector,
				     rq->cmd_flags & REQ_FUA);
		अगर (err) अणु
			spin_unlock_irq(&nullb->lock);
			वापस err;
		पूर्ण
		sector += len >> SECTOR_SHIFT;
	पूर्ण
	spin_unlock_irq(&nullb->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक null_handle_bio(काष्ठा nullb_cmd *cmd)
अणु
	काष्ठा bio *bio = cmd->bio;
	काष्ठा nullb *nullb = cmd->nq->dev->nullb;
	पूर्णांक err;
	अचिन्हित पूर्णांक len;
	sector_t sector = bio->bi_iter.bi_sector;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;

	spin_lock_irq(&nullb->lock);
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		len = bvec.bv_len;
		err = null_transfer(nullb, bvec.bv_page, len, bvec.bv_offset,
				     op_is_ग_लिखो(bio_op(bio)), sector,
				     bio->bi_opf & REQ_FUA);
		अगर (err) अणु
			spin_unlock_irq(&nullb->lock);
			वापस err;
		पूर्ण
		sector += len >> SECTOR_SHIFT;
	पूर्ण
	spin_unlock_irq(&nullb->lock);
	वापस 0;
पूर्ण

अटल व्योम null_stop_queue(काष्ठा nullb *nullb)
अणु
	काष्ठा request_queue *q = nullb->q;

	अगर (nullb->dev->queue_mode == शून्य_Q_MQ)
		blk_mq_stop_hw_queues(q);
पूर्ण

अटल व्योम null_restart_queue_async(काष्ठा nullb *nullb)
अणु
	काष्ठा request_queue *q = nullb->q;

	अगर (nullb->dev->queue_mode == शून्य_Q_MQ)
		blk_mq_start_stopped_hw_queues(q, true);
पूर्ण

अटल अंतरभूत blk_status_t null_handle_throttled(काष्ठा nullb_cmd *cmd)
अणु
	काष्ठा nullb_device *dev = cmd->nq->dev;
	काष्ठा nullb *nullb = dev->nullb;
	blk_status_t sts = BLK_STS_OK;
	काष्ठा request *rq = cmd->rq;

	अगर (!hrसमयr_active(&nullb->bw_समयr))
		hrसमयr_restart(&nullb->bw_समयr);

	अगर (atomic_दीर्घ_sub_वापस(blk_rq_bytes(rq), &nullb->cur_bytes) < 0) अणु
		null_stop_queue(nullb);
		/* race with समयr */
		अगर (atomic_दीर्घ_पढ़ो(&nullb->cur_bytes) > 0)
			null_restart_queue_async(nullb);
		/* requeue request */
		sts = BLK_STS_DEV_RESOURCE;
	पूर्ण
	वापस sts;
पूर्ण

अटल अंतरभूत blk_status_t null_handle_badblocks(काष्ठा nullb_cmd *cmd,
						 sector_t sector,
						 sector_t nr_sectors)
अणु
	काष्ठा badblocks *bb = &cmd->nq->dev->badblocks;
	sector_t first_bad;
	पूर्णांक bad_sectors;

	अगर (badblocks_check(bb, sector, nr_sectors, &first_bad, &bad_sectors))
		वापस BLK_STS_IOERR;

	वापस BLK_STS_OK;
पूर्ण

अटल अंतरभूत blk_status_t null_handle_memory_backed(काष्ठा nullb_cmd *cmd,
						     क्रमागत req_opf op,
						     sector_t sector,
						     sector_t nr_sectors)
अणु
	काष्ठा nullb_device *dev = cmd->nq->dev;
	पूर्णांक err;

	अगर (op == REQ_OP_DISCARD)
		वापस null_handle_discard(dev, sector, nr_sectors);

	अगर (dev->queue_mode == शून्य_Q_BIO)
		err = null_handle_bio(cmd);
	अन्यथा
		err = null_handle_rq(cmd);

	वापस त्रुटि_सं_to_blk_status(err);
पूर्ण

अटल व्योम nullb_zero_पढ़ो_cmd_buffer(काष्ठा nullb_cmd *cmd)
अणु
	काष्ठा nullb_device *dev = cmd->nq->dev;
	काष्ठा bio *bio;

	अगर (dev->memory_backed)
		वापस;

	अगर (dev->queue_mode == शून्य_Q_BIO && bio_op(cmd->bio) == REQ_OP_READ) अणु
		zero_fill_bio(cmd->bio);
	पूर्ण अन्यथा अगर (req_op(cmd->rq) == REQ_OP_READ) अणु
		__rq_क्रम_each_bio(bio, cmd->rq)
			zero_fill_bio(bio);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nullb_complete_cmd(काष्ठा nullb_cmd *cmd)
अणु
	/*
	 * Since root privileges are required to configure the null_blk
	 * driver, it is fine that this driver करोes not initialize the
	 * data buffers of पढ़ो commands. Zero-initialize these buffers
	 * anyway अगर KMSAN is enabled to prevent that KMSAN complains
	 * about null_blk not initializing पढ़ो data buffers.
	 */
	अगर (IS_ENABLED(CONFIG_KMSAN))
		nullb_zero_पढ़ो_cmd_buffer(cmd);

	/* Complete IO by अंतरभूत, softirq or समयr */
	चयन (cmd->nq->dev->irqmode) अणु
	हाल शून्य_IRQ_SOFTIRQ:
		चयन (cmd->nq->dev->queue_mode) अणु
		हाल शून्य_Q_MQ:
			अगर (likely(!blk_should_fake_समयout(cmd->rq->q)))
				blk_mq_complete_request(cmd->rq);
			अवरोध;
		हाल शून्य_Q_BIO:
			/*
			 * XXX: no proper submitting cpu inक्रमmation available.
			 */
			end_cmd(cmd);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल शून्य_IRQ_NONE:
		end_cmd(cmd);
		अवरोध;
	हाल शून्य_IRQ_TIMER:
		null_cmd_end_समयr(cmd);
		अवरोध;
	पूर्ण
पूर्ण

blk_status_t null_process_cmd(काष्ठा nullb_cmd *cmd,
			      क्रमागत req_opf op, sector_t sector,
			      अचिन्हित पूर्णांक nr_sectors)
अणु
	काष्ठा nullb_device *dev = cmd->nq->dev;
	blk_status_t ret;

	अगर (dev->badblocks.shअगरt != -1) अणु
		ret = null_handle_badblocks(cmd, sector, nr_sectors);
		अगर (ret != BLK_STS_OK)
			वापस ret;
	पूर्ण

	अगर (dev->memory_backed)
		वापस null_handle_memory_backed(cmd, op, sector, nr_sectors);

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t null_handle_cmd(काष्ठा nullb_cmd *cmd, sector_t sector,
				    sector_t nr_sectors, क्रमागत req_opf op)
अणु
	काष्ठा nullb_device *dev = cmd->nq->dev;
	काष्ठा nullb *nullb = dev->nullb;
	blk_status_t sts;

	अगर (test_bit(शून्यB_DEV_FL_THROTTLED, &dev->flags)) अणु
		sts = null_handle_throttled(cmd);
		अगर (sts != BLK_STS_OK)
			वापस sts;
	पूर्ण

	अगर (op == REQ_OP_FLUSH) अणु
		cmd->error = त्रुटि_सं_to_blk_status(null_handle_flush(nullb));
		जाओ out;
	पूर्ण

	अगर (dev->zoned)
		sts = null_process_zoned_cmd(cmd, op, sector, nr_sectors);
	अन्यथा
		sts = null_process_cmd(cmd, op, sector, nr_sectors);

	/* Do not overग_लिखो errors (e.g. समयout errors) */
	अगर (cmd->error == BLK_STS_OK)
		cmd->error = sts;

out:
	nullb_complete_cmd(cmd);
	वापस BLK_STS_OK;
पूर्ण

अटल क्रमागत hrसमयr_restart nullb_bwसमयr_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा nullb *nullb = container_of(समयr, काष्ठा nullb, bw_समयr);
	kसमय_प्रकार समयr_पूर्णांकerval = kसमय_set(0, TIMER_INTERVAL);
	अचिन्हित पूर्णांक mbps = nullb->dev->mbps;

	अगर (atomic_दीर्घ_पढ़ो(&nullb->cur_bytes) == mb_per_tick(mbps))
		वापस HRTIMER_NORESTART;

	atomic_दीर्घ_set(&nullb->cur_bytes, mb_per_tick(mbps));
	null_restart_queue_async(nullb);

	hrसमयr_क्रमward_now(&nullb->bw_समयr, समयr_पूर्णांकerval);

	वापस HRTIMER_RESTART;
पूर्ण

अटल व्योम nullb_setup_bwसमयr(काष्ठा nullb *nullb)
अणु
	kसमय_प्रकार समयr_पूर्णांकerval = kसमय_set(0, TIMER_INTERVAL);

	hrसमयr_init(&nullb->bw_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	nullb->bw_समयr.function = nullb_bwसमयr_fn;
	atomic_दीर्घ_set(&nullb->cur_bytes, mb_per_tick(nullb->dev->mbps));
	hrसमयr_start(&nullb->bw_समयr, समयr_पूर्णांकerval, HRTIMER_MODE_REL);
पूर्ण

अटल काष्ठा nullb_queue *nullb_to_queue(काष्ठा nullb *nullb)
अणु
	पूर्णांक index = 0;

	अगर (nullb->nr_queues != 1)
		index = raw_smp_processor_id() / ((nr_cpu_ids + nullb->nr_queues - 1) / nullb->nr_queues);

	वापस &nullb->queues[index];
पूर्ण

अटल blk_qc_t null_submit_bio(काष्ठा bio *bio)
अणु
	sector_t sector = bio->bi_iter.bi_sector;
	sector_t nr_sectors = bio_sectors(bio);
	काष्ठा nullb *nullb = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा nullb_queue *nq = nullb_to_queue(nullb);
	काष्ठा nullb_cmd *cmd;

	cmd = alloc_cmd(nq, 1);
	cmd->bio = bio;

	null_handle_cmd(cmd, sector, nr_sectors, bio_op(bio));
	वापस BLK_QC_T_NONE;
पूर्ण

अटल bool should_समयout_request(काष्ठा request *rq)
अणु
#अगर_घोषित CONFIG_BLK_DEV_शून्य_BLK_FAULT_INJECTION
	अगर (g_समयout_str[0])
		वापस should_fail(&null_समयout_attr, 1);
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल bool should_requeue_request(काष्ठा request *rq)
अणु
#अगर_घोषित CONFIG_BLK_DEV_शून्य_BLK_FAULT_INJECTION
	अगर (g_requeue_str[0])
		वापस should_fail(&null_requeue_attr, 1);
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस null_समयout_rq(काष्ठा request *rq, bool res)
अणु
	काष्ठा nullb_cmd *cmd = blk_mq_rq_to_pdu(rq);

	pr_info("rq %p timed out\n", rq);

	/*
	 * If the device is marked as blocking (i.e. memory backed or zoned
	 * device), the submission path may be blocked रुकोing क्रम resources
	 * and cause real समयouts. For these real समयouts, the submission
	 * path will complete the request using blk_mq_complete_request().
	 * Only fake समयouts need to execute blk_mq_complete_request() here.
	 */
	cmd->error = BLK_STS_TIMEOUT;
	अगर (cmd->fake_समयout)
		blk_mq_complete_request(rq);
	वापस BLK_EH_DONE;
पूर्ण

अटल blk_status_t null_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा nullb_cmd *cmd = blk_mq_rq_to_pdu(bd->rq);
	काष्ठा nullb_queue *nq = hctx->driver_data;
	sector_t nr_sectors = blk_rq_sectors(bd->rq);
	sector_t sector = blk_rq_pos(bd->rq);

	might_sleep_अगर(hctx->flags & BLK_MQ_F_BLOCKING);

	अगर (nq->dev->irqmode == शून्य_IRQ_TIMER) अणु
		hrसमयr_init(&cmd->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		cmd->समयr.function = null_cmd_समयr_expired;
	पूर्ण
	cmd->rq = bd->rq;
	cmd->error = BLK_STS_OK;
	cmd->nq = nq;
	cmd->fake_समयout = should_समयout_request(bd->rq);

	blk_mq_start_request(bd->rq);

	अगर (should_requeue_request(bd->rq)) अणु
		/*
		 * Alternate between hitting the core BUSY path, and the
		 * driver driven requeue path
		 */
		nq->requeue_selection++;
		अगर (nq->requeue_selection & 1)
			वापस BLK_STS_RESOURCE;
		अन्यथा अणु
			blk_mq_requeue_request(bd->rq, true);
			वापस BLK_STS_OK;
		पूर्ण
	पूर्ण
	अगर (cmd->fake_समयout)
		वापस BLK_STS_OK;

	वापस null_handle_cmd(cmd, sector, nr_sectors, req_op(bd->rq));
पूर्ण

अटल व्योम cleanup_queue(काष्ठा nullb_queue *nq)
अणु
	kमुक्त(nq->tag_map);
	kमुक्त(nq->cmds);
पूर्ण

अटल व्योम cleanup_queues(काष्ठा nullb *nullb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nullb->nr_queues; i++)
		cleanup_queue(&nullb->queues[i]);

	kमुक्त(nullb->queues);
पूर्ण

अटल व्योम null_निकास_hctx(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nullb_queue *nq = hctx->driver_data;
	काष्ठा nullb *nullb = nq->dev->nullb;

	nullb->nr_queues--;
पूर्ण

अटल व्योम null_init_queue(काष्ठा nullb *nullb, काष्ठा nullb_queue *nq)
अणु
	init_रुकोqueue_head(&nq->रुको);
	nq->queue_depth = nullb->queue_depth;
	nq->dev = nullb->dev;
पूर्ण

अटल पूर्णांक null_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *driver_data,
			  अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nullb *nullb = hctx->queue->queuedata;
	काष्ठा nullb_queue *nq;

#अगर_घोषित CONFIG_BLK_DEV_शून्य_BLK_FAULT_INJECTION
	अगर (g_init_hctx_str[0] && should_fail(&null_init_hctx_attr, 1))
		वापस -EFAULT;
#पूर्ण_अगर

	nq = &nullb->queues[hctx_idx];
	hctx->driver_data = nq;
	null_init_queue(nullb, nq);
	nullb->nr_queues++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops null_mq_ops = अणु
	.queue_rq       = null_queue_rq,
	.complete	= null_complete_rq,
	.समयout	= null_समयout_rq,
	.init_hctx	= null_init_hctx,
	.निकास_hctx	= null_निकास_hctx,
पूर्ण;

अटल व्योम null_del_dev(काष्ठा nullb *nullb)
अणु
	काष्ठा nullb_device *dev;

	अगर (!nullb)
		वापस;

	dev = nullb->dev;

	ida_simple_हटाओ(&nullb_indexes, nullb->index);

	list_del_init(&nullb->list);

	del_gendisk(nullb->disk);

	अगर (test_bit(शून्यB_DEV_FL_THROTTLED, &nullb->dev->flags)) अणु
		hrसमयr_cancel(&nullb->bw_समयr);
		atomic_दीर्घ_set(&nullb->cur_bytes, दीर्घ_उच्च);
		null_restart_queue_async(nullb);
	पूर्ण

	blk_cleanup_queue(nullb->q);
	अगर (dev->queue_mode == शून्य_Q_MQ &&
	    nullb->tag_set == &nullb->__tag_set)
		blk_mq_मुक्त_tag_set(nullb->tag_set);
	put_disk(nullb->disk);
	cleanup_queues(nullb);
	अगर (null_cache_active(nullb))
		null_मुक्त_device_storage(nullb->dev, true);
	kमुक्त(nullb);
	dev->nullb = शून्य;
पूर्ण

अटल व्योम null_config_discard(काष्ठा nullb *nullb)
अणु
	अगर (nullb->dev->discard == false)
		वापस;

	अगर (!nullb->dev->memory_backed) अणु
		nullb->dev->discard = false;
		pr_info("discard option is ignored without memory backing\n");
		वापस;
	पूर्ण

	अगर (nullb->dev->zoned) अणु
		nullb->dev->discard = false;
		pr_info("discard option is ignored in zoned mode\n");
		वापस;
	पूर्ण

	nullb->q->limits.discard_granularity = nullb->dev->blocksize;
	nullb->q->limits.discard_alignment = nullb->dev->blocksize;
	blk_queue_max_discard_sectors(nullb->q, अच_पूर्णांक_उच्च >> 9);
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, nullb->q);
पूर्ण

अटल स्थिर काष्ठा block_device_operations null_bio_ops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= null_submit_bio,
	.report_zones	= null_report_zones,
पूर्ण;

अटल स्थिर काष्ठा block_device_operations null_rq_ops = अणु
	.owner		= THIS_MODULE,
	.report_zones	= null_report_zones,
पूर्ण;

अटल पूर्णांक setup_commands(काष्ठा nullb_queue *nq)
अणु
	काष्ठा nullb_cmd *cmd;
	पूर्णांक i, tag_size;

	nq->cmds = kसुस्मृति(nq->queue_depth, माप(*cmd), GFP_KERNEL);
	अगर (!nq->cmds)
		वापस -ENOMEM;

	tag_size = ALIGN(nq->queue_depth, BITS_PER_LONG) / BITS_PER_LONG;
	nq->tag_map = kसुस्मृति(tag_size, माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!nq->tag_map) अणु
		kमुक्त(nq->cmds);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < nq->queue_depth; i++) अणु
		cmd = &nq->cmds[i];
		cmd->tag = -1U;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_queues(काष्ठा nullb *nullb)
अणु
	nullb->queues = kसुस्मृति(nr_cpu_ids, माप(काष्ठा nullb_queue),
				GFP_KERNEL);
	अगर (!nullb->queues)
		वापस -ENOMEM;

	nullb->queue_depth = nullb->dev->hw_queue_depth;

	वापस 0;
पूर्ण

अटल पूर्णांक init_driver_queues(काष्ठा nullb *nullb)
अणु
	काष्ठा nullb_queue *nq;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < nullb->dev->submit_queues; i++) अणु
		nq = &nullb->queues[i];

		null_init_queue(nullb, nq);

		ret = setup_commands(nq);
		अगर (ret)
			वापस ret;
		nullb->nr_queues++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक null_gendisk_रेजिस्टर(काष्ठा nullb *nullb)
अणु
	sector_t size = ((sector_t)nullb->dev->size * SZ_1M) >> SECTOR_SHIFT;
	काष्ठा gendisk *disk;

	disk = nullb->disk = alloc_disk_node(1, nullb->dev->home_node);
	अगर (!disk)
		वापस -ENOMEM;
	set_capacity(disk, size);

	disk->flags |= GENHD_FL_EXT_DEVT | GENHD_FL_SUPPRESS_PARTITION_INFO;
	disk->major		= null_major;
	disk->first_minor	= nullb->index;
	अगर (queue_is_mq(nullb->q))
		disk->fops		= &null_rq_ops;
	अन्यथा
		disk->fops		= &null_bio_ops;
	disk->निजी_data	= nullb;
	disk->queue		= nullb->q;
	म_नकलन(disk->disk_name, nullb->disk_name, DISK_NAME_LEN);

	अगर (nullb->dev->zoned) अणु
		पूर्णांक ret = null_रेजिस्टर_zoned_dev(nullb);

		अगर (ret)
			वापस ret;
	पूर्ण

	add_disk(disk);
	वापस 0;
पूर्ण

अटल पूर्णांक null_init_tag_set(काष्ठा nullb *nullb, काष्ठा blk_mq_tag_set *set)
अणु
	set->ops = &null_mq_ops;
	set->nr_hw_queues = nullb ? nullb->dev->submit_queues :
						g_submit_queues;
	set->queue_depth = nullb ? nullb->dev->hw_queue_depth :
						g_hw_queue_depth;
	set->numa_node = nullb ? nullb->dev->home_node : g_home_node;
	set->cmd_size	= माप(काष्ठा nullb_cmd);
	set->flags = BLK_MQ_F_SHOULD_MERGE;
	अगर (g_no_sched)
		set->flags |= BLK_MQ_F_NO_SCHED;
	अगर (g_shared_tag_biपंचांगap)
		set->flags |= BLK_MQ_F_TAG_HCTX_SHARED;
	set->driver_data = शून्य;

	अगर ((nullb && nullb->dev->blocking) || g_blocking)
		set->flags |= BLK_MQ_F_BLOCKING;

	वापस blk_mq_alloc_tag_set(set);
पूर्ण

अटल पूर्णांक null_validate_conf(काष्ठा nullb_device *dev)
अणु
	dev->blocksize = round_करोwn(dev->blocksize, 512);
	dev->blocksize = clamp_t(अचिन्हित पूर्णांक, dev->blocksize, 512, 4096);

	अगर (dev->queue_mode == शून्य_Q_MQ && dev->use_per_node_hctx) अणु
		अगर (dev->submit_queues != nr_online_nodes)
			dev->submit_queues = nr_online_nodes;
	पूर्ण अन्यथा अगर (dev->submit_queues > nr_cpu_ids)
		dev->submit_queues = nr_cpu_ids;
	अन्यथा अगर (dev->submit_queues == 0)
		dev->submit_queues = 1;

	dev->queue_mode = min_t(अचिन्हित पूर्णांक, dev->queue_mode, शून्य_Q_MQ);
	dev->irqmode = min_t(अचिन्हित पूर्णांक, dev->irqmode, शून्य_IRQ_TIMER);

	/* Do memory allocation, so set blocking */
	अगर (dev->memory_backed)
		dev->blocking = true;
	अन्यथा /* cache is meaningless */
		dev->cache_size = 0;
	dev->cache_size = min_t(अचिन्हित दीर्घ, अच_दीर्घ_उच्च / 1024 / 1024,
						dev->cache_size);
	dev->mbps = min_t(अचिन्हित पूर्णांक, 1024 * 40, dev->mbps);
	/* can not stop a queue */
	अगर (dev->queue_mode == शून्य_Q_BIO)
		dev->mbps = 0;

	अगर (dev->zoned &&
	    (!dev->zone_size || !is_घातer_of_2(dev->zone_size))) अणु
		pr_err("zone_size must be power-of-two\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_शून्य_BLK_FAULT_INJECTION
अटल bool __null_setup_fault(काष्ठा fault_attr *attr, अक्षर *str)
अणु
	अगर (!str[0])
		वापस true;

	अगर (!setup_fault_attr(attr, str))
		वापस false;

	attr->verbose = 0;
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल bool null_setup_fault(व्योम)
अणु
#अगर_घोषित CONFIG_BLK_DEV_शून्य_BLK_FAULT_INJECTION
	अगर (!__null_setup_fault(&null_समयout_attr, g_समयout_str))
		वापस false;
	अगर (!__null_setup_fault(&null_requeue_attr, g_requeue_str))
		वापस false;
	अगर (!__null_setup_fault(&null_init_hctx_attr, g_init_hctx_str))
		वापस false;
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल पूर्णांक null_add_dev(काष्ठा nullb_device *dev)
अणु
	काष्ठा nullb *nullb;
	पूर्णांक rv;

	rv = null_validate_conf(dev);
	अगर (rv)
		वापस rv;

	nullb = kzalloc_node(माप(*nullb), GFP_KERNEL, dev->home_node);
	अगर (!nullb) अणु
		rv = -ENOMEM;
		जाओ out;
	पूर्ण
	nullb->dev = dev;
	dev->nullb = nullb;

	spin_lock_init(&nullb->lock);

	rv = setup_queues(nullb);
	अगर (rv)
		जाओ out_मुक्त_nullb;

	अगर (dev->queue_mode == शून्य_Q_MQ) अणु
		अगर (shared_tags) अणु
			nullb->tag_set = &tag_set;
			rv = 0;
		पूर्ण अन्यथा अणु
			nullb->tag_set = &nullb->__tag_set;
			rv = null_init_tag_set(nullb, nullb->tag_set);
		पूर्ण

		अगर (rv)
			जाओ out_cleanup_queues;

		अगर (!null_setup_fault())
			जाओ out_cleanup_queues;

		nullb->tag_set->समयout = 5 * HZ;
		nullb->q = blk_mq_init_queue_data(nullb->tag_set, nullb);
		अगर (IS_ERR(nullb->q)) अणु
			rv = -ENOMEM;
			जाओ out_cleanup_tags;
		पूर्ण
	पूर्ण अन्यथा अगर (dev->queue_mode == शून्य_Q_BIO) अणु
		nullb->q = blk_alloc_queue(dev->home_node);
		अगर (!nullb->q) अणु
			rv = -ENOMEM;
			जाओ out_cleanup_queues;
		पूर्ण
		rv = init_driver_queues(nullb);
		अगर (rv)
			जाओ out_cleanup_blk_queue;
	पूर्ण

	अगर (dev->mbps) अणु
		set_bit(शून्यB_DEV_FL_THROTTLED, &dev->flags);
		nullb_setup_bwसमयr(nullb);
	पूर्ण

	अगर (dev->cache_size > 0) अणु
		set_bit(शून्यB_DEV_FL_CACHE, &nullb->dev->flags);
		blk_queue_ग_लिखो_cache(nullb->q, true, true);
	पूर्ण

	अगर (dev->zoned) अणु
		rv = null_init_zoned_dev(dev, nullb->q);
		अगर (rv)
			जाओ out_cleanup_blk_queue;
	पूर्ण

	nullb->q->queuedata = nullb;
	blk_queue_flag_set(QUEUE_FLAG_NONROT, nullb->q);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, nullb->q);

	mutex_lock(&lock);
	nullb->index = ida_simple_get(&nullb_indexes, 0, 0, GFP_KERNEL);
	dev->index = nullb->index;
	mutex_unlock(&lock);

	blk_queue_logical_block_size(nullb->q, dev->blocksize);
	blk_queue_physical_block_size(nullb->q, dev->blocksize);
	अगर (!dev->max_sectors)
		dev->max_sectors = queue_max_hw_sectors(nullb->q);
	dev->max_sectors = min_t(अचिन्हित पूर्णांक, dev->max_sectors,
				 BLK_DEF_MAX_SECTORS);
	blk_queue_max_hw_sectors(nullb->q, dev->max_sectors);

	अगर (dev->virt_boundary)
		blk_queue_virt_boundary(nullb->q, PAGE_SIZE - 1);

	null_config_discard(nullb);

	प्र_लिखो(nullb->disk_name, "nullb%d", nullb->index);

	rv = null_gendisk_रेजिस्टर(nullb);
	अगर (rv)
		जाओ out_cleanup_zone;

	mutex_lock(&lock);
	list_add_tail(&nullb->list, &nullb_list);
	mutex_unlock(&lock);

	वापस 0;
out_cleanup_zone:
	null_मुक्त_zoned_dev(dev);
out_cleanup_blk_queue:
	blk_cleanup_queue(nullb->q);
out_cleanup_tags:
	अगर (dev->queue_mode == शून्य_Q_MQ && nullb->tag_set == &nullb->__tag_set)
		blk_mq_मुक्त_tag_set(nullb->tag_set);
out_cleanup_queues:
	cleanup_queues(nullb);
out_मुक्त_nullb:
	kमुक्त(nullb);
	dev->nullb = शून्य;
out:
	वापस rv;
पूर्ण

अटल पूर्णांक __init null_init(व्योम)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा nullb *nullb;
	काष्ठा nullb_device *dev;

	अगर (g_bs > PAGE_SIZE) अणु
		pr_warn("invalid block size\n");
		pr_warn("defaults block size to %lu\n", PAGE_SIZE);
		g_bs = PAGE_SIZE;
	पूर्ण

	अगर (g_max_sectors > BLK_DEF_MAX_SECTORS) अणु
		pr_warn("invalid max sectors\n");
		pr_warn("defaults max sectors to %u\n", BLK_DEF_MAX_SECTORS);
		g_max_sectors = BLK_DEF_MAX_SECTORS;
	पूर्ण

	अगर (g_home_node != NUMA_NO_NODE && g_home_node >= nr_online_nodes) अणु
		pr_err("invalid home_node value\n");
		g_home_node = NUMA_NO_NODE;
	पूर्ण

	अगर (g_queue_mode == शून्य_Q_RQ) अणु
		pr_err("legacy IO path no longer available\n");
		वापस -EINVAL;
	पूर्ण
	अगर (g_queue_mode == शून्य_Q_MQ && g_use_per_node_hctx) अणु
		अगर (g_submit_queues != nr_online_nodes) अणु
			pr_warn("submit_queues param is set to %u.\n",
							nr_online_nodes);
			g_submit_queues = nr_online_nodes;
		पूर्ण
	पूर्ण अन्यथा अगर (g_submit_queues > nr_cpu_ids)
		g_submit_queues = nr_cpu_ids;
	अन्यथा अगर (g_submit_queues <= 0)
		g_submit_queues = 1;

	अगर (g_queue_mode == शून्य_Q_MQ && shared_tags) अणु
		ret = null_init_tag_set(शून्य, &tag_set);
		अगर (ret)
			वापस ret;
	पूर्ण

	config_group_init(&nullb_subsys.su_group);
	mutex_init(&nullb_subsys.su_mutex);

	ret = configfs_रेजिस्टर_subप्रणाली(&nullb_subsys);
	अगर (ret)
		जाओ err_tagset;

	mutex_init(&lock);

	null_major = रेजिस्टर_blkdev(0, "nullb");
	अगर (null_major < 0) अणु
		ret = null_major;
		जाओ err_conf;
	पूर्ण

	क्रम (i = 0; i < nr_devices; i++) अणु
		dev = null_alloc_dev();
		अगर (!dev) अणु
			ret = -ENOMEM;
			जाओ err_dev;
		पूर्ण
		ret = null_add_dev(dev);
		अगर (ret) अणु
			null_मुक्त_dev(dev);
			जाओ err_dev;
		पूर्ण
	पूर्ण

	pr_info("module loaded\n");
	वापस 0;

err_dev:
	जबतक (!list_empty(&nullb_list)) अणु
		nullb = list_entry(nullb_list.next, काष्ठा nullb, list);
		dev = nullb->dev;
		null_del_dev(nullb);
		null_मुक्त_dev(dev);
	पूर्ण
	unरेजिस्टर_blkdev(null_major, "nullb");
err_conf:
	configfs_unरेजिस्टर_subप्रणाली(&nullb_subsys);
err_tagset:
	अगर (g_queue_mode == शून्य_Q_MQ && shared_tags)
		blk_mq_मुक्त_tag_set(&tag_set);
	वापस ret;
पूर्ण

अटल व्योम __निकास null_निकास(व्योम)
अणु
	काष्ठा nullb *nullb;

	configfs_unरेजिस्टर_subप्रणाली(&nullb_subsys);

	unरेजिस्टर_blkdev(null_major, "nullb");

	mutex_lock(&lock);
	जबतक (!list_empty(&nullb_list)) अणु
		काष्ठा nullb_device *dev;

		nullb = list_entry(nullb_list.next, काष्ठा nullb, list);
		dev = nullb->dev;
		null_del_dev(nullb);
		null_मुक्त_dev(dev);
	पूर्ण
	mutex_unlock(&lock);

	अगर (g_queue_mode == शून्य_Q_MQ && shared_tags)
		blk_mq_मुक्त_tag_set(&tag_set);
पूर्ण

module_init(null_init);
module_निकास(null_निकास);

MODULE_AUTHOR("Jens Axboe <axboe@kernel.dk>");
MODULE_LICENSE("GPL");
