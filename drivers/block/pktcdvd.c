<शैली गुरु>
/*
 * Copyright (C) 2000 Jens Axboe <axboe@suse.de>
 * Copyright (C) 2001-2004 Peter Osterlund <petero2@telia.com>
 * Copyright (C) 2006 Thomas Maier <balagi@jusपंचांगail.de>
 *
 * May be copied or modअगरied under the terms of the GNU General Public
 * License.  See linux/COPYING क्रम more inक्रमmation.
 *
 * Packet writing layer क्रम ATAPI and SCSI CD-RW, DVD+RW, DVD-RW and
 * DVD-RAM devices.
 *
 * Theory of operation:
 *
 * At the lowest level, there is the standard driver क्रम the CD/DVD device,
 * typically ide-cd.c or sr.c. This driver can handle पढ़ो and ग_लिखो requests,
 * but it करोesn't know anything about the special restrictions that apply to
 * packet writing. One restriction is that ग_लिखो requests must be aligned to
 * packet boundaries on the physical media, and the size of a ग_लिखो request
 * must be equal to the packet size. Another restriction is that a
 * GPCMD_FLUSH_CACHE command has to be issued to the drive beक्रमe a पढ़ो
 * command, अगर the previous command was a ग_लिखो.
 *
 * The purpose of the packet writing driver is to hide these restrictions from
 * higher layers, such as file प्रणालीs, and present a block device that can be
 * अक्रमomly पढ़ो and written using 2kB-sized blocks.
 *
 * The lowest layer in the packet writing driver is the packet I/O scheduler.
 * Its data is defined by the काष्ठा packet_iosched and includes two bio
 * queues with pending पढ़ो and ग_लिखो requests. These queues are processed
 * by the pkt_iosched_process_queue() function. The ग_लिखो requests in this
 * queue are alपढ़ोy properly aligned and sized. This layer is responsible क्रम
 * issuing the flush cache commands and scheduling the I/O in a good order.
 *
 * The next layer transक्रमms unaligned ग_लिखो requests to aligned ग_लिखोs. This
 * transक्रमmation requires पढ़ोing missing pieces of data from the underlying
 * block device, assembling the pieces to full packets and queuing them to the
 * packet I/O scheduler.
 *
 * At the top layer there is a custom ->submit_bio function that क्रमwards
 * पढ़ो requests directly to the iosched queue and माला_दो ग_लिखो requests in the
 * unaligned ग_लिखो queue. A kernel thपढ़ो perक्रमms the necessary पढ़ो
 * gathering to convert the unaligned ग_लिखोs to aligned ग_लिखोs and then feeds
 * them to the packet I/O scheduler.
 *
 *************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pktcdvd.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compat.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/backing-dev.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsi.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/nospec.h>
#समावेश <linux/uaccess.h>

#घोषणा DRIVER_NAME	"pktcdvd"

#घोषणा pkt_err(pd, fmt, ...)						\
	pr_err("%s: " fmt, pd->name, ##__VA_ARGS__)
#घोषणा pkt_notice(pd, fmt, ...)					\
	pr_notice("%s: " fmt, pd->name, ##__VA_ARGS__)
#घोषणा pkt_info(pd, fmt, ...)						\
	pr_info("%s: " fmt, pd->name, ##__VA_ARGS__)

#घोषणा pkt_dbg(level, pd, fmt, ...)					\
करो अणु									\
	अगर (level == 2 && PACKET_DEBUG >= 2)				\
		pr_notice("%s: %s():" fmt,				\
			  pd->name, __func__, ##__VA_ARGS__);		\
	अन्यथा अगर (level == 1 && PACKET_DEBUG >= 1)			\
		pr_notice("%s: " fmt, pd->name, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा MAX_SPEED 0xffff

अटल DEFINE_MUTEX(pktcdvd_mutex);
अटल काष्ठा pktcdvd_device *pkt_devs[MAX_WRITERS];
अटल काष्ठा proc_dir_entry *pkt_proc;
अटल पूर्णांक pktdev_major;
अटल पूर्णांक ग_लिखो_congestion_on  = PKT_WRITE_CONGESTION_ON;
अटल पूर्णांक ग_लिखो_congestion_off = PKT_WRITE_CONGESTION_OFF;
अटल काष्ठा mutex ctl_mutex;	/* Serialize खोलो/बंद/setup/tearकरोwn */
अटल mempool_t psd_pool;
अटल काष्ठा bio_set pkt_bio_set;

अटल काष्ठा class	*class_pktcdvd = शून्य;    /* /sys/class/pktcdvd */
अटल काष्ठा dentry	*pkt_debugfs_root = शून्य; /* /sys/kernel/debug/pktcdvd */

/* क्रमward declaration */
अटल पूर्णांक pkt_setup_dev(dev_t dev, dev_t* pkt_dev);
अटल पूर्णांक pkt_हटाओ_dev(dev_t pkt_dev);
अटल पूर्णांक pkt_seq_show(काष्ठा seq_file *m, व्योम *p);

अटल sector_t get_zone(sector_t sector, काष्ठा pktcdvd_device *pd)
अणु
	वापस (sector + pd->offset) & ~(sector_t)(pd->settings.size - 1);
पूर्ण

/*
 * create and रेजिस्टर a pktcdvd kernel object.
 */
अटल काष्ठा pktcdvd_kobj* pkt_kobj_create(काष्ठा pktcdvd_device *pd,
					स्थिर अक्षर* name,
					काष्ठा kobject* parent,
					काष्ठा kobj_type* ktype)
अणु
	काष्ठा pktcdvd_kobj *p;
	पूर्णांक error;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;
	p->pd = pd;
	error = kobject_init_and_add(&p->kobj, ktype, parent, "%s", name);
	अगर (error) अणु
		kobject_put(&p->kobj);
		वापस शून्य;
	पूर्ण
	kobject_uevent(&p->kobj, KOBJ_ADD);
	वापस p;
पूर्ण
/*
 * हटाओ a pktcdvd kernel object.
 */
अटल व्योम pkt_kobj_हटाओ(काष्ठा pktcdvd_kobj *p)
अणु
	अगर (p)
		kobject_put(&p->kobj);
पूर्ण
/*
 * शेष release function क्रम pktcdvd kernel objects.
 */
अटल व्योम pkt_kobj_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(to_pktcdvdkobj(kobj));
पूर्ण


/**********************************************************
 *
 * sysfs पूर्णांकerface क्रम pktcdvd
 * by (C) 2006  Thomas Maier <balagi@jusपंचांगail.de>
 *
 **********************************************************/

#घोषणा DEF_ATTR(_obj,_name,_mode) \
	अटल काष्ठा attribute _obj = अणु .name = _name, .mode = _mode पूर्ण

/**********************************************************
  /sys/class/pktcdvd/pktcdvd[0-7]/
                     stat/reset
                     stat/packets_started
                     stat/packets_finished
                     stat/kb_written
                     stat/kb_पढ़ो
                     stat/kb_पढ़ो_gather
                     ग_लिखो_queue/size
                     ग_लिखो_queue/congestion_off
                     ग_लिखो_queue/congestion_on
 **********************************************************/

DEF_ATTR(kobj_pkt_attr_st1, "reset", 0200);
DEF_ATTR(kobj_pkt_attr_st2, "packets_started", 0444);
DEF_ATTR(kobj_pkt_attr_st3, "packets_finished", 0444);
DEF_ATTR(kobj_pkt_attr_st4, "kb_written", 0444);
DEF_ATTR(kobj_pkt_attr_st5, "kb_read", 0444);
DEF_ATTR(kobj_pkt_attr_st6, "kb_read_gather", 0444);

अटल काष्ठा attribute *kobj_pkt_attrs_stat[] = अणु
	&kobj_pkt_attr_st1,
	&kobj_pkt_attr_st2,
	&kobj_pkt_attr_st3,
	&kobj_pkt_attr_st4,
	&kobj_pkt_attr_st5,
	&kobj_pkt_attr_st6,
	शून्य
पूर्ण;

DEF_ATTR(kobj_pkt_attr_wq1, "size", 0444);
DEF_ATTR(kobj_pkt_attr_wq2, "congestion_off", 0644);
DEF_ATTR(kobj_pkt_attr_wq3, "congestion_on",  0644);

अटल काष्ठा attribute *kobj_pkt_attrs_wqueue[] = अणु
	&kobj_pkt_attr_wq1,
	&kobj_pkt_attr_wq2,
	&kobj_pkt_attr_wq3,
	शून्य
पूर्ण;

अटल sमाप_प्रकार kobj_pkt_show(काष्ठा kobject *kobj,
			काष्ठा attribute *attr, अक्षर *data)
अणु
	काष्ठा pktcdvd_device *pd = to_pktcdvdkobj(kobj)->pd;
	पूर्णांक n = 0;
	पूर्णांक v;
	अगर (म_भेद(attr->name, "packets_started") == 0) अणु
		n = प्र_लिखो(data, "%lu\n", pd->stats.pkt_started);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "packets_finished") == 0) अणु
		n = प्र_लिखो(data, "%lu\n", pd->stats.pkt_ended);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "kb_written") == 0) अणु
		n = प्र_लिखो(data, "%lu\n", pd->stats.secs_w >> 1);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "kb_read") == 0) अणु
		n = प्र_लिखो(data, "%lu\n", pd->stats.secs_r >> 1);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "kb_read_gather") == 0) अणु
		n = प्र_लिखो(data, "%lu\n", pd->stats.secs_rg >> 1);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "size") == 0) अणु
		spin_lock(&pd->lock);
		v = pd->bio_queue_size;
		spin_unlock(&pd->lock);
		n = प्र_लिखो(data, "%d\n", v);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "congestion_off") == 0) अणु
		spin_lock(&pd->lock);
		v = pd->ग_लिखो_congestion_off;
		spin_unlock(&pd->lock);
		n = प्र_लिखो(data, "%d\n", v);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "congestion_on") == 0) अणु
		spin_lock(&pd->lock);
		v = pd->ग_लिखो_congestion_on;
		spin_unlock(&pd->lock);
		n = प्र_लिखो(data, "%d\n", v);
	पूर्ण
	वापस n;
पूर्ण

अटल व्योम init_ग_लिखो_congestion_marks(पूर्णांक* lo, पूर्णांक* hi)
अणु
	अगर (*hi > 0) अणु
		*hi = max(*hi, 500);
		*hi = min(*hi, 1000000);
		अगर (*lo <= 0)
			*lo = *hi - 100;
		अन्यथा अणु
			*lo = min(*lo, *hi - 100);
			*lo = max(*lo, 100);
		पूर्ण
	पूर्ण अन्यथा अणु
		*hi = -1;
		*lo = -1;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार kobj_pkt_store(काष्ठा kobject *kobj,
			काष्ठा attribute *attr,
			स्थिर अक्षर *data, माप_प्रकार len)
अणु
	काष्ठा pktcdvd_device *pd = to_pktcdvdkobj(kobj)->pd;
	पूर्णांक val;

	अगर (म_भेद(attr->name, "reset") == 0 && len > 0) अणु
		pd->stats.pkt_started = 0;
		pd->stats.pkt_ended = 0;
		pd->stats.secs_w = 0;
		pd->stats.secs_rg = 0;
		pd->stats.secs_r = 0;

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "congestion_off") == 0
		   && माला_पूछो(data, "%d", &val) == 1) अणु
		spin_lock(&pd->lock);
		pd->ग_लिखो_congestion_off = val;
		init_ग_लिखो_congestion_marks(&pd->ग_लिखो_congestion_off,
					&pd->ग_लिखो_congestion_on);
		spin_unlock(&pd->lock);

	पूर्ण अन्यथा अगर (म_भेद(attr->name, "congestion_on") == 0
		   && माला_पूछो(data, "%d", &val) == 1) अणु
		spin_lock(&pd->lock);
		pd->ग_लिखो_congestion_on = val;
		init_ग_लिखो_congestion_marks(&pd->ग_लिखो_congestion_off,
					&pd->ग_लिखो_congestion_on);
		spin_unlock(&pd->lock);
	पूर्ण
	वापस len;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops kobj_pkt_ops = अणु
	.show = kobj_pkt_show,
	.store = kobj_pkt_store
पूर्ण;
अटल काष्ठा kobj_type kobj_pkt_type_stat = अणु
	.release = pkt_kobj_release,
	.sysfs_ops = &kobj_pkt_ops,
	.शेष_attrs = kobj_pkt_attrs_stat
पूर्ण;
अटल काष्ठा kobj_type kobj_pkt_type_wqueue = अणु
	.release = pkt_kobj_release,
	.sysfs_ops = &kobj_pkt_ops,
	.शेष_attrs = kobj_pkt_attrs_wqueue
पूर्ण;

अटल व्योम pkt_sysfs_dev_new(काष्ठा pktcdvd_device *pd)
अणु
	अगर (class_pktcdvd) अणु
		pd->dev = device_create(class_pktcdvd, शून्य, MKDEV(0, 0), शून्य,
					"%s", pd->name);
		अगर (IS_ERR(pd->dev))
			pd->dev = शून्य;
	पूर्ण
	अगर (pd->dev) अणु
		pd->kobj_stat = pkt_kobj_create(pd, "stat",
					&pd->dev->kobj,
					&kobj_pkt_type_stat);
		pd->kobj_wqueue = pkt_kobj_create(pd, "write_queue",
					&pd->dev->kobj,
					&kobj_pkt_type_wqueue);
	पूर्ण
पूर्ण

अटल व्योम pkt_sysfs_dev_हटाओ(काष्ठा pktcdvd_device *pd)
अणु
	pkt_kobj_हटाओ(pd->kobj_stat);
	pkt_kobj_हटाओ(pd->kobj_wqueue);
	अगर (class_pktcdvd)
		device_unरेजिस्टर(pd->dev);
पूर्ण


/********************************************************************
  /sys/class/pktcdvd/
                     add            map block device
                     हटाओ         unmap packet dev
                     device_map     show mappings
 *******************************************************************/

अटल व्योम class_pktcdvd_release(काष्ठा class *cls)
अणु
	kमुक्त(cls);
पूर्ण

अटल sमाप_प्रकार device_map_show(काष्ठा class *c, काष्ठा class_attribute *attr,
			       अक्षर *data)
अणु
	पूर्णांक n = 0;
	पूर्णांक idx;
	mutex_lock_nested(&ctl_mutex, SINGLE_DEPTH_NESTING);
	क्रम (idx = 0; idx < MAX_WRITERS; idx++) अणु
		काष्ठा pktcdvd_device *pd = pkt_devs[idx];
		अगर (!pd)
			जारी;
		n += प्र_लिखो(data+n, "%s %u:%u %u:%u\n",
			pd->name,
			MAJOR(pd->pkt_dev), MINOR(pd->pkt_dev),
			MAJOR(pd->bdev->bd_dev),
			MINOR(pd->bdev->bd_dev));
	पूर्ण
	mutex_unlock(&ctl_mutex);
	वापस n;
पूर्ण
अटल CLASS_ATTR_RO(device_map);

अटल sमाप_प्रकार add_store(काष्ठा class *c, काष्ठा class_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक major, minor;

	अगर (माला_पूछो(buf, "%u:%u", &major, &minor) == 2) अणु
		/* pkt_setup_dev() expects caller to hold reference to self */
		अगर (!try_module_get(THIS_MODULE))
			वापस -ENODEV;

		pkt_setup_dev(MKDEV(major, minor), शून्य);

		module_put(THIS_MODULE);

		वापस count;
	पूर्ण

	वापस -EINVAL;
पूर्ण
अटल CLASS_ATTR_WO(add);

अटल sमाप_प्रकार हटाओ_store(काष्ठा class *c, काष्ठा class_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक major, minor;
	अगर (माला_पूछो(buf, "%u:%u", &major, &minor) == 2) अणु
		pkt_हटाओ_dev(MKDEV(major, minor));
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल CLASS_ATTR_WO(हटाओ);

अटल काष्ठा attribute *class_pktcdvd_attrs[] = अणु
	&class_attr_add.attr,
	&class_attr_हटाओ.attr,
	&class_attr_device_map.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(class_pktcdvd);

अटल पूर्णांक pkt_sysfs_init(व्योम)
अणु
	पूर्णांक ret = 0;

	/*
	 * create control files in sysfs
	 * /sys/class/pktcdvd/...
	 */
	class_pktcdvd = kzalloc(माप(*class_pktcdvd), GFP_KERNEL);
	अगर (!class_pktcdvd)
		वापस -ENOMEM;
	class_pktcdvd->name = DRIVER_NAME;
	class_pktcdvd->owner = THIS_MODULE;
	class_pktcdvd->class_release = class_pktcdvd_release;
	class_pktcdvd->class_groups = class_pktcdvd_groups;
	ret = class_रेजिस्टर(class_pktcdvd);
	अगर (ret) अणु
		kमुक्त(class_pktcdvd);
		class_pktcdvd = शून्य;
		pr_err("failed to create class pktcdvd\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pkt_sysfs_cleanup(व्योम)
अणु
	अगर (class_pktcdvd)
		class_destroy(class_pktcdvd);
	class_pktcdvd = शून्य;
पूर्ण

/********************************************************************
  entries in debugfs

  /sys/kernel/debug/pktcdvd[0-7]/
			info

 *******************************************************************/

अटल पूर्णांक pkt_debugfs_seq_show(काष्ठा seq_file *m, व्योम *p)
अणु
	वापस pkt_seq_show(m, p);
पूर्ण

अटल पूर्णांक pkt_debugfs_fops_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pkt_debugfs_seq_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debug_fops = अणु
	.खोलो		= pkt_debugfs_fops_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम pkt_debugfs_dev_new(काष्ठा pktcdvd_device *pd)
अणु
	अगर (!pkt_debugfs_root)
		वापस;
	pd->dfs_d_root = debugfs_create_dir(pd->name, pkt_debugfs_root);
	अगर (!pd->dfs_d_root)
		वापस;

	pd->dfs_f_info = debugfs_create_file("info", 0444,
					     pd->dfs_d_root, pd, &debug_fops);
पूर्ण

अटल व्योम pkt_debugfs_dev_हटाओ(काष्ठा pktcdvd_device *pd)
अणु
	अगर (!pkt_debugfs_root)
		वापस;
	debugfs_हटाओ(pd->dfs_f_info);
	debugfs_हटाओ(pd->dfs_d_root);
	pd->dfs_f_info = शून्य;
	pd->dfs_d_root = शून्य;
पूर्ण

अटल व्योम pkt_debugfs_init(व्योम)
अणु
	pkt_debugfs_root = debugfs_create_dir(DRIVER_NAME, शून्य);
पूर्ण

अटल व्योम pkt_debugfs_cleanup(व्योम)
अणु
	debugfs_हटाओ(pkt_debugfs_root);
	pkt_debugfs_root = शून्य;
पूर्ण

/* ----------------------------------------------------------*/


अटल व्योम pkt_bio_finished(काष्ठा pktcdvd_device *pd)
अणु
	BUG_ON(atomic_पढ़ो(&pd->cdrw.pending_bios) <= 0);
	अगर (atomic_dec_and_test(&pd->cdrw.pending_bios)) अणु
		pkt_dbg(2, pd, "queue empty\n");
		atomic_set(&pd->iosched.attention, 1);
		wake_up(&pd->wqueue);
	पूर्ण
पूर्ण

/*
 * Allocate a packet_data काष्ठा
 */
अटल काष्ठा packet_data *pkt_alloc_packet_data(पूर्णांक frames)
अणु
	पूर्णांक i;
	काष्ठा packet_data *pkt;

	pkt = kzalloc(माप(काष्ठा packet_data), GFP_KERNEL);
	अगर (!pkt)
		जाओ no_pkt;

	pkt->frames = frames;
	pkt->w_bio = bio_kदो_स्मृति(GFP_KERNEL, frames);
	अगर (!pkt->w_bio)
		जाओ no_bio;

	क्रम (i = 0; i < frames / FRAMES_PER_PAGE; i++) अणु
		pkt->pages[i] = alloc_page(GFP_KERNEL|__GFP_ZERO);
		अगर (!pkt->pages[i])
			जाओ no_page;
	पूर्ण

	spin_lock_init(&pkt->lock);
	bio_list_init(&pkt->orig_bios);

	क्रम (i = 0; i < frames; i++) अणु
		काष्ठा bio *bio = bio_kदो_स्मृति(GFP_KERNEL, 1);
		अगर (!bio)
			जाओ no_rd_bio;

		pkt->r_bios[i] = bio;
	पूर्ण

	वापस pkt;

no_rd_bio:
	क्रम (i = 0; i < frames; i++) अणु
		काष्ठा bio *bio = pkt->r_bios[i];
		अगर (bio)
			bio_put(bio);
	पूर्ण

no_page:
	क्रम (i = 0; i < frames / FRAMES_PER_PAGE; i++)
		अगर (pkt->pages[i])
			__मुक्त_page(pkt->pages[i]);
	bio_put(pkt->w_bio);
no_bio:
	kमुक्त(pkt);
no_pkt:
	वापस शून्य;
पूर्ण

/*
 * Free a packet_data काष्ठा
 */
अटल व्योम pkt_मुक्त_packet_data(काष्ठा packet_data *pkt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pkt->frames; i++) अणु
		काष्ठा bio *bio = pkt->r_bios[i];
		अगर (bio)
			bio_put(bio);
	पूर्ण
	क्रम (i = 0; i < pkt->frames / FRAMES_PER_PAGE; i++)
		__मुक्त_page(pkt->pages[i]);
	bio_put(pkt->w_bio);
	kमुक्त(pkt);
पूर्ण

अटल व्योम pkt_shrink_pktlist(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा packet_data *pkt, *next;

	BUG_ON(!list_empty(&pd->cdrw.pkt_active_list));

	list_क्रम_each_entry_safe(pkt, next, &pd->cdrw.pkt_मुक्त_list, list) अणु
		pkt_मुक्त_packet_data(pkt);
	पूर्ण
	INIT_LIST_HEAD(&pd->cdrw.pkt_मुक्त_list);
पूर्ण

अटल पूर्णांक pkt_grow_pktlist(काष्ठा pktcdvd_device *pd, पूर्णांक nr_packets)
अणु
	काष्ठा packet_data *pkt;

	BUG_ON(!list_empty(&pd->cdrw.pkt_मुक्त_list));

	जबतक (nr_packets > 0) अणु
		pkt = pkt_alloc_packet_data(pd->settings.size >> 2);
		अगर (!pkt) अणु
			pkt_shrink_pktlist(pd);
			वापस 0;
		पूर्ण
		pkt->id = nr_packets;
		pkt->pd = pd;
		list_add(&pkt->list, &pd->cdrw.pkt_मुक्त_list);
		nr_packets--;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत काष्ठा pkt_rb_node *pkt_rbtree_next(काष्ठा pkt_rb_node *node)
अणु
	काष्ठा rb_node *n = rb_next(&node->rb_node);
	अगर (!n)
		वापस शून्य;
	वापस rb_entry(n, काष्ठा pkt_rb_node, rb_node);
पूर्ण

अटल व्योम pkt_rbtree_erase(काष्ठा pktcdvd_device *pd, काष्ठा pkt_rb_node *node)
अणु
	rb_erase(&node->rb_node, &pd->bio_queue);
	mempool_मुक्त(node, &pd->rb_pool);
	pd->bio_queue_size--;
	BUG_ON(pd->bio_queue_size < 0);
पूर्ण

/*
 * Find the first node in the pd->bio_queue rb tree with a starting sector >= s.
 */
अटल काष्ठा pkt_rb_node *pkt_rbtree_find(काष्ठा pktcdvd_device *pd, sector_t s)
अणु
	काष्ठा rb_node *n = pd->bio_queue.rb_node;
	काष्ठा rb_node *next;
	काष्ठा pkt_rb_node *पंचांगp;

	अगर (!n) अणु
		BUG_ON(pd->bio_queue_size > 0);
		वापस शून्य;
	पूर्ण

	क्रम (;;) अणु
		पंचांगp = rb_entry(n, काष्ठा pkt_rb_node, rb_node);
		अगर (s <= पंचांगp->bio->bi_iter.bi_sector)
			next = n->rb_left;
		अन्यथा
			next = n->rb_right;
		अगर (!next)
			अवरोध;
		n = next;
	पूर्ण

	अगर (s > पंचांगp->bio->bi_iter.bi_sector) अणु
		पंचांगp = pkt_rbtree_next(पंचांगp);
		अगर (!पंचांगp)
			वापस शून्य;
	पूर्ण
	BUG_ON(s > पंचांगp->bio->bi_iter.bi_sector);
	वापस पंचांगp;
पूर्ण

/*
 * Insert a node पूर्णांकo the pd->bio_queue rb tree.
 */
अटल व्योम pkt_rbtree_insert(काष्ठा pktcdvd_device *pd, काष्ठा pkt_rb_node *node)
अणु
	काष्ठा rb_node **p = &pd->bio_queue.rb_node;
	काष्ठा rb_node *parent = शून्य;
	sector_t s = node->bio->bi_iter.bi_sector;
	काष्ठा pkt_rb_node *पंचांगp;

	जबतक (*p) अणु
		parent = *p;
		पंचांगp = rb_entry(parent, काष्ठा pkt_rb_node, rb_node);
		अगर (s < पंचांगp->bio->bi_iter.bi_sector)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण
	rb_link_node(&node->rb_node, parent, p);
	rb_insert_color(&node->rb_node, &pd->bio_queue);
	pd->bio_queue_size++;
पूर्ण

/*
 * Send a packet_command to the underlying block device and
 * रुको क्रम completion.
 */
अटल पूर्णांक pkt_generic_packet(काष्ठा pktcdvd_device *pd, काष्ठा packet_command *cgc)
अणु
	काष्ठा request_queue *q = bdev_get_queue(pd->bdev);
	काष्ठा request *rq;
	पूर्णांक ret = 0;

	rq = blk_get_request(q, (cgc->data_direction == CGC_DATA_WRITE) ?
			     REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	अगर (cgc->buflen) अणु
		ret = blk_rq_map_kern(q, rq, cgc->buffer, cgc->buflen,
				      GFP_NOIO);
		अगर (ret)
			जाओ out;
	पूर्ण

	scsi_req(rq)->cmd_len = COMMAND_SIZE(cgc->cmd[0]);
	स_नकल(scsi_req(rq)->cmd, cgc->cmd, CDROM_PACKET_SIZE);

	rq->समयout = 60*HZ;
	अगर (cgc->quiet)
		rq->rq_flags |= RQF_QUIET;

	blk_execute_rq(pd->bdev->bd_disk, rq, 0);
	अगर (scsi_req(rq)->result)
		ret = -EIO;
out:
	blk_put_request(rq);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *sense_key_string(__u8 index)
अणु
	अटल स्थिर अक्षर * स्थिर info[] = अणु
		"No sense", "Recovered error", "Not ready",
		"Medium error", "Hardware error", "Illegal request",
		"Unit attention", "Data protect", "Blank check",
	पूर्ण;

	वापस index < ARRAY_SIZE(info) ? info[index] : "INVALID";
पूर्ण

/*
 * A generic sense dump / resolve mechanism should be implemented across
 * all ATAPI + SCSI devices.
 */
अटल व्योम pkt_dump_sense(काष्ठा pktcdvd_device *pd,
			   काष्ठा packet_command *cgc)
अणु
	काष्ठा scsi_sense_hdr *sshdr = cgc->sshdr;

	अगर (sshdr)
		pkt_err(pd, "%*ph - sense %02x.%02x.%02x (%s)\n",
			CDROM_PACKET_SIZE, cgc->cmd,
			sshdr->sense_key, sshdr->asc, sshdr->ascq,
			sense_key_string(sshdr->sense_key));
	अन्यथा
		pkt_err(pd, "%*ph - no sense\n", CDROM_PACKET_SIZE, cgc->cmd);
पूर्ण

/*
 * flush the drive cache to media
 */
अटल पूर्णांक pkt_flush_cache(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा packet_command cgc;

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_FLUSH_CACHE;
	cgc.quiet = 1;

	/*
	 * the IMMED bit -- we शेष to not setting it, although that
	 * would allow a much faster बंद, this is safer
	 */
#अगर 0
	cgc.cmd[1] = 1 << 1;
#पूर्ण_अगर
	वापस pkt_generic_packet(pd, &cgc);
पूर्ण

/*
 * speed is given as the normal factor, e.g. 4 क्रम 4x
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_set_speed(काष्ठा pktcdvd_device *pd,
				अचिन्हित ग_लिखो_speed, अचिन्हित पढ़ो_speed)
अणु
	काष्ठा packet_command cgc;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक ret;

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.sshdr = &sshdr;
	cgc.cmd[0] = GPCMD_SET_SPEED;
	cgc.cmd[2] = (पढ़ो_speed >> 8) & 0xff;
	cgc.cmd[3] = पढ़ो_speed & 0xff;
	cgc.cmd[4] = (ग_लिखो_speed >> 8) & 0xff;
	cgc.cmd[5] = ग_लिखो_speed & 0xff;

	ret = pkt_generic_packet(pd, &cgc);
	अगर (ret)
		pkt_dump_sense(pd, &cgc);

	वापस ret;
पूर्ण

/*
 * Queue a bio क्रम processing by the low-level CD device. Must be called
 * from process context.
 */
अटल व्योम pkt_queue_bio(काष्ठा pktcdvd_device *pd, काष्ठा bio *bio)
अणु
	spin_lock(&pd->iosched.lock);
	अगर (bio_data_dir(bio) == READ)
		bio_list_add(&pd->iosched.पढ़ो_queue, bio);
	अन्यथा
		bio_list_add(&pd->iosched.ग_लिखो_queue, bio);
	spin_unlock(&pd->iosched.lock);

	atomic_set(&pd->iosched.attention, 1);
	wake_up(&pd->wqueue);
पूर्ण

/*
 * Process the queued पढ़ो/ग_लिखो requests. This function handles special
 * requirements क्रम CDRW drives:
 * - A cache flush command must be inserted beक्रमe a पढ़ो request अगर the
 *   previous request was a ग_लिखो.
 * - Switching between पढ़ोing and writing is slow, so करोn't करो it more often
 *   than necessary.
 * - Optimize क्रम throughput at the expense of latency. This means that streaming
 *   ग_लिखोs will never be पूर्णांकerrupted by a पढ़ो, but अगर the drive has to seek
 *   beक्रमe the next ग_लिखो, चयन to पढ़ोing instead अगर there are any pending
 *   पढ़ो requests.
 * - Set the पढ़ो speed according to current usage pattern. When only पढ़ोing
 *   from the device, it's best to use the highest possible पढ़ो speed, but
 *   when चयनing often between पढ़ोing and writing, it's better to have the
 *   same पढ़ो and ग_लिखो speeds.
 */
अटल व्योम pkt_iosched_process_queue(काष्ठा pktcdvd_device *pd)
अणु

	अगर (atomic_पढ़ो(&pd->iosched.attention) == 0)
		वापस;
	atomic_set(&pd->iosched.attention, 0);

	क्रम (;;) अणु
		काष्ठा bio *bio;
		पूर्णांक पढ़ोs_queued, ग_लिखोs_queued;

		spin_lock(&pd->iosched.lock);
		पढ़ोs_queued = !bio_list_empty(&pd->iosched.पढ़ो_queue);
		ग_लिखोs_queued = !bio_list_empty(&pd->iosched.ग_लिखो_queue);
		spin_unlock(&pd->iosched.lock);

		अगर (!पढ़ोs_queued && !ग_लिखोs_queued)
			अवरोध;

		अगर (pd->iosched.writing) अणु
			पूर्णांक need_ग_लिखो_seek = 1;
			spin_lock(&pd->iosched.lock);
			bio = bio_list_peek(&pd->iosched.ग_लिखो_queue);
			spin_unlock(&pd->iosched.lock);
			अगर (bio && (bio->bi_iter.bi_sector ==
				    pd->iosched.last_ग_लिखो))
				need_ग_लिखो_seek = 0;
			अगर (need_ग_लिखो_seek && पढ़ोs_queued) अणु
				अगर (atomic_पढ़ो(&pd->cdrw.pending_bios) > 0) अणु
					pkt_dbg(2, pd, "write, waiting\n");
					अवरोध;
				पूर्ण
				pkt_flush_cache(pd);
				pd->iosched.writing = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!पढ़ोs_queued && ग_लिखोs_queued) अणु
				अगर (atomic_पढ़ो(&pd->cdrw.pending_bios) > 0) अणु
					pkt_dbg(2, pd, "read, waiting\n");
					अवरोध;
				पूर्ण
				pd->iosched.writing = 1;
			पूर्ण
		पूर्ण

		spin_lock(&pd->iosched.lock);
		अगर (pd->iosched.writing)
			bio = bio_list_pop(&pd->iosched.ग_लिखो_queue);
		अन्यथा
			bio = bio_list_pop(&pd->iosched.पढ़ो_queue);
		spin_unlock(&pd->iosched.lock);

		अगर (!bio)
			जारी;

		अगर (bio_data_dir(bio) == READ)
			pd->iosched.successive_पढ़ोs +=
				bio->bi_iter.bi_size >> 10;
		अन्यथा अणु
			pd->iosched.successive_पढ़ोs = 0;
			pd->iosched.last_ग_लिखो = bio_end_sector(bio);
		पूर्ण
		अगर (pd->iosched.successive_पढ़ोs >= HI_SPEED_SWITCH) अणु
			अगर (pd->पढ़ो_speed == pd->ग_लिखो_speed) अणु
				pd->पढ़ो_speed = MAX_SPEED;
				pkt_set_speed(pd, pd->ग_लिखो_speed, pd->पढ़ो_speed);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pd->पढ़ो_speed != pd->ग_लिखो_speed) अणु
				pd->पढ़ो_speed = pd->ग_लिखो_speed;
				pkt_set_speed(pd, pd->ग_लिखो_speed, pd->पढ़ो_speed);
			पूर्ण
		पूर्ण

		atomic_inc(&pd->cdrw.pending_bios);
		submit_bio_noacct(bio);
	पूर्ण
पूर्ण

/*
 * Special care is needed अगर the underlying block device has a small
 * max_phys_segments value.
 */
अटल पूर्णांक pkt_set_segment_merging(काष्ठा pktcdvd_device *pd, काष्ठा request_queue *q)
अणु
	अगर ((pd->settings.size << 9) / CD_FRAMESIZE
	    <= queue_max_segments(q)) अणु
		/*
		 * The cdrom device can handle one segment/frame
		 */
		clear_bit(PACKET_MERGE_SEGS, &pd->flags);
		वापस 0;
	पूर्ण अन्यथा अगर ((pd->settings.size << 9) / PAGE_SIZE
		   <= queue_max_segments(q)) अणु
		/*
		 * We can handle this हाल at the expense of some extra memory
		 * copies during ग_लिखो operations
		 */
		set_bit(PACKET_MERGE_SEGS, &pd->flags);
		वापस 0;
	पूर्ण अन्यथा अणु
		pkt_err(pd, "cdrom max_phys_segments too small\n");
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम pkt_end_io_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा packet_data *pkt = bio->bi_निजी;
	काष्ठा pktcdvd_device *pd = pkt->pd;
	BUG_ON(!pd);

	pkt_dbg(2, pd, "bio=%p sec0=%llx sec=%llx err=%d\n",
		bio, (अचिन्हित दीर्घ दीर्घ)pkt->sector,
		(अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector, bio->bi_status);

	अगर (bio->bi_status)
		atomic_inc(&pkt->io_errors);
	अगर (atomic_dec_and_test(&pkt->io_रुको)) अणु
		atomic_inc(&pkt->run_sm);
		wake_up(&pd->wqueue);
	पूर्ण
	pkt_bio_finished(pd);
पूर्ण

अटल व्योम pkt_end_io_packet_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा packet_data *pkt = bio->bi_निजी;
	काष्ठा pktcdvd_device *pd = pkt->pd;
	BUG_ON(!pd);

	pkt_dbg(2, pd, "id=%d, err=%d\n", pkt->id, bio->bi_status);

	pd->stats.pkt_ended++;

	pkt_bio_finished(pd);
	atomic_dec(&pkt->io_रुको);
	atomic_inc(&pkt->run_sm);
	wake_up(&pd->wqueue);
पूर्ण

/*
 * Schedule पढ़ोs क्रम the holes in a packet
 */
अटल व्योम pkt_gather_data(काष्ठा pktcdvd_device *pd, काष्ठा packet_data *pkt)
अणु
	पूर्णांक frames_पढ़ो = 0;
	काष्ठा bio *bio;
	पूर्णांक f;
	अक्षर written[PACKET_MAX_SIZE];

	BUG_ON(bio_list_empty(&pkt->orig_bios));

	atomic_set(&pkt->io_रुको, 0);
	atomic_set(&pkt->io_errors, 0);

	/*
	 * Figure out which frames we need to पढ़ो beक्रमe we can ग_लिखो.
	 */
	स_रखो(written, 0, माप(written));
	spin_lock(&pkt->lock);
	bio_list_क्रम_each(bio, &pkt->orig_bios) अणु
		पूर्णांक first_frame = (bio->bi_iter.bi_sector - pkt->sector) /
			(CD_FRAMESIZE >> 9);
		पूर्णांक num_frames = bio->bi_iter.bi_size / CD_FRAMESIZE;
		pd->stats.secs_w += num_frames * (CD_FRAMESIZE >> 9);
		BUG_ON(first_frame < 0);
		BUG_ON(first_frame + num_frames > pkt->frames);
		क्रम (f = first_frame; f < first_frame + num_frames; f++)
			written[f] = 1;
	पूर्ण
	spin_unlock(&pkt->lock);

	अगर (pkt->cache_valid) अणु
		pkt_dbg(2, pd, "zone %llx cached\n",
			(अचिन्हित दीर्घ दीर्घ)pkt->sector);
		जाओ out_account;
	पूर्ण

	/*
	 * Schedule पढ़ोs क्रम missing parts of the packet.
	 */
	क्रम (f = 0; f < pkt->frames; f++) अणु
		पूर्णांक p, offset;

		अगर (written[f])
			जारी;

		bio = pkt->r_bios[f];
		bio_reset(bio);
		bio->bi_iter.bi_sector = pkt->sector + f * (CD_FRAMESIZE >> 9);
		bio_set_dev(bio, pd->bdev);
		bio->bi_end_io = pkt_end_io_पढ़ो;
		bio->bi_निजी = pkt;

		p = (f * CD_FRAMESIZE) / PAGE_SIZE;
		offset = (f * CD_FRAMESIZE) % PAGE_SIZE;
		pkt_dbg(2, pd, "Adding frame %d, page:%p offs:%d\n",
			f, pkt->pages[p], offset);
		अगर (!bio_add_page(bio, pkt->pages[p], CD_FRAMESIZE, offset))
			BUG();

		atomic_inc(&pkt->io_रुको);
		bio_set_op_attrs(bio, REQ_OP_READ, 0);
		pkt_queue_bio(pd, bio);
		frames_पढ़ो++;
	पूर्ण

out_account:
	pkt_dbg(2, pd, "need %d frames for zone %llx\n",
		frames_पढ़ो, (अचिन्हित दीर्घ दीर्घ)pkt->sector);
	pd->stats.pkt_started++;
	pd->stats.secs_rg += frames_पढ़ो * (CD_FRAMESIZE >> 9);
पूर्ण

/*
 * Find a packet matching zone, or the least recently used packet अगर
 * there is no match.
 */
अटल काष्ठा packet_data *pkt_get_packet_data(काष्ठा pktcdvd_device *pd, पूर्णांक zone)
अणु
	काष्ठा packet_data *pkt;

	list_क्रम_each_entry(pkt, &pd->cdrw.pkt_मुक्त_list, list) अणु
		अगर (pkt->sector == zone || pkt->list.next == &pd->cdrw.pkt_मुक्त_list) अणु
			list_del_init(&pkt->list);
			अगर (pkt->sector != zone)
				pkt->cache_valid = 0;
			वापस pkt;
		पूर्ण
	पूर्ण
	BUG();
	वापस शून्य;
पूर्ण

अटल व्योम pkt_put_packet_data(काष्ठा pktcdvd_device *pd, काष्ठा packet_data *pkt)
अणु
	अगर (pkt->cache_valid) अणु
		list_add(&pkt->list, &pd->cdrw.pkt_मुक्त_list);
	पूर्ण अन्यथा अणु
		list_add_tail(&pkt->list, &pd->cdrw.pkt_मुक्त_list);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pkt_set_state(काष्ठा packet_data *pkt, क्रमागत packet_data_state state)
अणु
#अगर PACKET_DEBUG > 1
	अटल स्थिर अक्षर *state_name[] = अणु
		"IDLE", "WAITING", "READ_WAIT", "WRITE_WAIT", "RECOVERY", "FINISHED"
	पूर्ण;
	क्रमागत packet_data_state old_state = pkt->state;
	pkt_dbg(2, pd, "pkt %2d : s=%6llx %s -> %s\n",
		pkt->id, (अचिन्हित दीर्घ दीर्घ)pkt->sector,
		state_name[old_state], state_name[state]);
#पूर्ण_अगर
	pkt->state = state;
पूर्ण

/*
 * Scan the work queue to see अगर we can start a new packet.
 * वापसs non-zero अगर any work was करोne.
 */
अटल पूर्णांक pkt_handle_queue(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा packet_data *pkt, *p;
	काष्ठा bio *bio = शून्य;
	sector_t zone = 0; /* Suppress gcc warning */
	काष्ठा pkt_rb_node *node, *first_node;
	काष्ठा rb_node *n;
	पूर्णांक wakeup;

	atomic_set(&pd->scan_queue, 0);

	अगर (list_empty(&pd->cdrw.pkt_मुक्त_list)) अणु
		pkt_dbg(2, pd, "no pkt\n");
		वापस 0;
	पूर्ण

	/*
	 * Try to find a zone we are not alपढ़ोy working on.
	 */
	spin_lock(&pd->lock);
	first_node = pkt_rbtree_find(pd, pd->current_sector);
	अगर (!first_node) अणु
		n = rb_first(&pd->bio_queue);
		अगर (n)
			first_node = rb_entry(n, काष्ठा pkt_rb_node, rb_node);
	पूर्ण
	node = first_node;
	जबतक (node) अणु
		bio = node->bio;
		zone = get_zone(bio->bi_iter.bi_sector, pd);
		list_क्रम_each_entry(p, &pd->cdrw.pkt_active_list, list) अणु
			अगर (p->sector == zone) अणु
				bio = शून्य;
				जाओ try_next_bio;
			पूर्ण
		पूर्ण
		अवरोध;
try_next_bio:
		node = pkt_rbtree_next(node);
		अगर (!node) अणु
			n = rb_first(&pd->bio_queue);
			अगर (n)
				node = rb_entry(n, काष्ठा pkt_rb_node, rb_node);
		पूर्ण
		अगर (node == first_node)
			node = शून्य;
	पूर्ण
	spin_unlock(&pd->lock);
	अगर (!bio) अणु
		pkt_dbg(2, pd, "no bio\n");
		वापस 0;
	पूर्ण

	pkt = pkt_get_packet_data(pd, zone);

	pd->current_sector = zone + pd->settings.size;
	pkt->sector = zone;
	BUG_ON(pkt->frames != pd->settings.size >> 2);
	pkt->ग_लिखो_size = 0;

	/*
	 * Scan work queue क्रम bios in the same zone and link them
	 * to this packet.
	 */
	spin_lock(&pd->lock);
	pkt_dbg(2, pd, "looking for zone %llx\n", (अचिन्हित दीर्घ दीर्घ)zone);
	जबतक ((node = pkt_rbtree_find(pd, zone)) != शून्य) अणु
		bio = node->bio;
		pkt_dbg(2, pd, "found zone=%llx\n", (अचिन्हित दीर्घ दीर्घ)
			get_zone(bio->bi_iter.bi_sector, pd));
		अगर (get_zone(bio->bi_iter.bi_sector, pd) != zone)
			अवरोध;
		pkt_rbtree_erase(pd, node);
		spin_lock(&pkt->lock);
		bio_list_add(&pkt->orig_bios, bio);
		pkt->ग_लिखो_size += bio->bi_iter.bi_size / CD_FRAMESIZE;
		spin_unlock(&pkt->lock);
	पूर्ण
	/* check ग_लिखो congestion marks, and अगर bio_queue_size is
	   below, wake up any रुकोers */
	wakeup = (pd->ग_लिखो_congestion_on > 0
	 		&& pd->bio_queue_size <= pd->ग_लिखो_congestion_off);
	spin_unlock(&pd->lock);
	अगर (wakeup) अणु
		clear_bdi_congested(pd->disk->queue->backing_dev_info,
					BLK_RW_ASYNC);
	पूर्ण

	pkt->sleep_समय = max(PACKET_WAIT_TIME, 1);
	pkt_set_state(pkt, PACKET_WAITING_STATE);
	atomic_set(&pkt->run_sm, 1);

	spin_lock(&pd->cdrw.active_list_lock);
	list_add(&pkt->list, &pd->cdrw.pkt_active_list);
	spin_unlock(&pd->cdrw.active_list_lock);

	वापस 1;
पूर्ण

/**
 * bio_list_copy_data - copy contents of data buffers from one chain of bios to
 * another
 * @src: source bio list
 * @dst: destination bio list
 *
 * Stops when it reaches the end of either the @src list or @dst list - that is,
 * copies min(src->bi_size, dst->bi_size) bytes (or the equivalent क्रम lists of
 * bios).
 */
अटल व्योम bio_list_copy_data(काष्ठा bio *dst, काष्ठा bio *src)
अणु
	काष्ठा bvec_iter src_iter = src->bi_iter;
	काष्ठा bvec_iter dst_iter = dst->bi_iter;

	जबतक (1) अणु
		अगर (!src_iter.bi_size) अणु
			src = src->bi_next;
			अगर (!src)
				अवरोध;

			src_iter = src->bi_iter;
		पूर्ण

		अगर (!dst_iter.bi_size) अणु
			dst = dst->bi_next;
			अगर (!dst)
				अवरोध;

			dst_iter = dst->bi_iter;
		पूर्ण

		bio_copy_data_iter(dst, &dst_iter, src, &src_iter);
	पूर्ण
पूर्ण

/*
 * Assemble a bio to ग_लिखो one packet and queue the bio क्रम processing
 * by the underlying block device.
 */
अटल व्योम pkt_start_ग_लिखो(काष्ठा pktcdvd_device *pd, काष्ठा packet_data *pkt)
अणु
	पूर्णांक f;

	bio_reset(pkt->w_bio);
	pkt->w_bio->bi_iter.bi_sector = pkt->sector;
	bio_set_dev(pkt->w_bio, pd->bdev);
	pkt->w_bio->bi_end_io = pkt_end_io_packet_ग_लिखो;
	pkt->w_bio->bi_निजी = pkt;

	/* XXX: locking? */
	क्रम (f = 0; f < pkt->frames; f++) अणु
		काष्ठा page *page = pkt->pages[(f * CD_FRAMESIZE) / PAGE_SIZE];
		अचिन्हित offset = (f * CD_FRAMESIZE) % PAGE_SIZE;

		अगर (!bio_add_page(pkt->w_bio, page, CD_FRAMESIZE, offset))
			BUG();
	पूर्ण
	pkt_dbg(2, pd, "vcnt=%d\n", pkt->w_bio->bi_vcnt);

	/*
	 * Fill-in bvec with data from orig_bios.
	 */
	spin_lock(&pkt->lock);
	bio_list_copy_data(pkt->w_bio, pkt->orig_मूलप्रण.सead);

	pkt_set_state(pkt, PACKET_WRITE_WAIT_STATE);
	spin_unlock(&pkt->lock);

	pkt_dbg(2, pd, "Writing %d frames for zone %llx\n",
		pkt->ग_लिखो_size, (अचिन्हित दीर्घ दीर्घ)pkt->sector);

	अगर (test_bit(PACKET_MERGE_SEGS, &pd->flags) || (pkt->ग_लिखो_size < pkt->frames))
		pkt->cache_valid = 1;
	अन्यथा
		pkt->cache_valid = 0;

	/* Start the ग_लिखो request */
	atomic_set(&pkt->io_रुको, 1);
	bio_set_op_attrs(pkt->w_bio, REQ_OP_WRITE, 0);
	pkt_queue_bio(pd, pkt->w_bio);
पूर्ण

अटल व्योम pkt_finish_packet(काष्ठा packet_data *pkt, blk_status_t status)
अणु
	काष्ठा bio *bio;

	अगर (status)
		pkt->cache_valid = 0;

	/* Finish all bios corresponding to this packet */
	जबतक ((bio = bio_list_pop(&pkt->orig_bios))) अणु
		bio->bi_status = status;
		bio_endio(bio);
	पूर्ण
पूर्ण

अटल व्योम pkt_run_state_machine(काष्ठा pktcdvd_device *pd, काष्ठा packet_data *pkt)
अणु
	pkt_dbg(2, pd, "pkt %d\n", pkt->id);

	क्रम (;;) अणु
		चयन (pkt->state) अणु
		हाल PACKET_WAITING_STATE:
			अगर ((pkt->ग_लिखो_size < pkt->frames) && (pkt->sleep_समय > 0))
				वापस;

			pkt->sleep_समय = 0;
			pkt_gather_data(pd, pkt);
			pkt_set_state(pkt, PACKET_READ_WAIT_STATE);
			अवरोध;

		हाल PACKET_READ_WAIT_STATE:
			अगर (atomic_पढ़ो(&pkt->io_रुको) > 0)
				वापस;

			अगर (atomic_पढ़ो(&pkt->io_errors) > 0) अणु
				pkt_set_state(pkt, PACKET_RECOVERY_STATE);
			पूर्ण अन्यथा अणु
				pkt_start_ग_लिखो(pd, pkt);
			पूर्ण
			अवरोध;

		हाल PACKET_WRITE_WAIT_STATE:
			अगर (atomic_पढ़ो(&pkt->io_रुको) > 0)
				वापस;

			अगर (!pkt->w_bio->bi_status) अणु
				pkt_set_state(pkt, PACKET_FINISHED_STATE);
			पूर्ण अन्यथा अणु
				pkt_set_state(pkt, PACKET_RECOVERY_STATE);
			पूर्ण
			अवरोध;

		हाल PACKET_RECOVERY_STATE:
			pkt_dbg(2, pd, "No recovery possible\n");
			pkt_set_state(pkt, PACKET_FINISHED_STATE);
			अवरोध;

		हाल PACKET_FINISHED_STATE:
			pkt_finish_packet(pkt, pkt->w_bio->bi_status);
			वापस;

		शेष:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pkt_handle_packets(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा packet_data *pkt, *next;

	/*
	 * Run state machine क्रम active packets
	 */
	list_क्रम_each_entry(pkt, &pd->cdrw.pkt_active_list, list) अणु
		अगर (atomic_पढ़ो(&pkt->run_sm) > 0) अणु
			atomic_set(&pkt->run_sm, 0);
			pkt_run_state_machine(pd, pkt);
		पूर्ण
	पूर्ण

	/*
	 * Move no दीर्घer active packets to the मुक्त list
	 */
	spin_lock(&pd->cdrw.active_list_lock);
	list_क्रम_each_entry_safe(pkt, next, &pd->cdrw.pkt_active_list, list) अणु
		अगर (pkt->state == PACKET_FINISHED_STATE) अणु
			list_del(&pkt->list);
			pkt_put_packet_data(pd, pkt);
			pkt_set_state(pkt, PACKET_IDLE_STATE);
			atomic_set(&pd->scan_queue, 1);
		पूर्ण
	पूर्ण
	spin_unlock(&pd->cdrw.active_list_lock);
पूर्ण

अटल व्योम pkt_count_states(काष्ठा pktcdvd_device *pd, पूर्णांक *states)
अणु
	काष्ठा packet_data *pkt;
	पूर्णांक i;

	क्रम (i = 0; i < PACKET_NUM_STATES; i++)
		states[i] = 0;

	spin_lock(&pd->cdrw.active_list_lock);
	list_क्रम_each_entry(pkt, &pd->cdrw.pkt_active_list, list) अणु
		states[pkt->state]++;
	पूर्ण
	spin_unlock(&pd->cdrw.active_list_lock);
पूर्ण

/*
 * kcdrwd is woken up when ग_लिखोs have been queued क्रम one of our
 * रेजिस्टरed devices
 */
अटल पूर्णांक kcdrwd(व्योम *foobar)
अणु
	काष्ठा pktcdvd_device *pd = foobar;
	काष्ठा packet_data *pkt;
	दीर्घ min_sleep_समय, residue;

	set_user_nice(current, MIN_NICE);
	set_मुक्तzable();

	क्रम (;;) अणु
		DECLARE_WAITQUEUE(रुको, current);

		/*
		 * Wait until there is something to करो
		 */
		add_रुको_queue(&pd->wqueue, &रुको);
		क्रम (;;) अणु
			set_current_state(TASK_INTERRUPTIBLE);

			/* Check अगर we need to run pkt_handle_queue */
			अगर (atomic_पढ़ो(&pd->scan_queue) > 0)
				जाओ work_to_करो;

			/* Check अगर we need to run the state machine क्रम some packet */
			list_क्रम_each_entry(pkt, &pd->cdrw.pkt_active_list, list) अणु
				अगर (atomic_पढ़ो(&pkt->run_sm) > 0)
					जाओ work_to_करो;
			पूर्ण

			/* Check अगर we need to process the iosched queues */
			अगर (atomic_पढ़ो(&pd->iosched.attention) != 0)
				जाओ work_to_करो;

			/* Otherwise, go to sleep */
			अगर (PACKET_DEBUG > 1) अणु
				पूर्णांक states[PACKET_NUM_STATES];
				pkt_count_states(pd, states);
				pkt_dbg(2, pd, "i:%d ow:%d rw:%d ww:%d rec:%d fin:%d\n",
					states[0], states[1], states[2],
					states[3], states[4], states[5]);
			पूर्ण

			min_sleep_समय = MAX_SCHEDULE_TIMEOUT;
			list_क्रम_each_entry(pkt, &pd->cdrw.pkt_active_list, list) अणु
				अगर (pkt->sleep_समय && pkt->sleep_समय < min_sleep_समय)
					min_sleep_समय = pkt->sleep_समय;
			पूर्ण

			pkt_dbg(2, pd, "sleeping\n");
			residue = schedule_समयout(min_sleep_समय);
			pkt_dbg(2, pd, "wake up\n");

			/* make swsusp happy with our thपढ़ो */
			try_to_मुक्तze();

			list_क्रम_each_entry(pkt, &pd->cdrw.pkt_active_list, list) अणु
				अगर (!pkt->sleep_समय)
					जारी;
				pkt->sleep_समय -= min_sleep_समय - residue;
				अगर (pkt->sleep_समय <= 0) अणु
					pkt->sleep_समय = 0;
					atomic_inc(&pkt->run_sm);
				पूर्ण
			पूर्ण

			अगर (kthपढ़ो_should_stop())
				अवरोध;
		पूर्ण
work_to_करो:
		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&pd->wqueue, &रुको);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/*
		 * अगर pkt_handle_queue वापसs true, we can queue
		 * another request.
		 */
		जबतक (pkt_handle_queue(pd))
			;

		/*
		 * Handle packet state machine
		 */
		pkt_handle_packets(pd);

		/*
		 * Handle iosched queues
		 */
		pkt_iosched_process_queue(pd);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pkt_prपूर्णांक_settings(काष्ठा pktcdvd_device *pd)
अणु
	pkt_info(pd, "%s packets, %u blocks, Mode-%c disc\n",
		 pd->settings.fp ? "Fixed" : "Variable",
		 pd->settings.size >> 2,
		 pd->settings.block_mode == 8 ? '1' : '2');
पूर्ण

अटल पूर्णांक pkt_mode_sense(काष्ठा pktcdvd_device *pd, काष्ठा packet_command *cgc, पूर्णांक page_code, पूर्णांक page_control)
अणु
	स_रखो(cgc->cmd, 0, माप(cgc->cmd));

	cgc->cmd[0] = GPCMD_MODE_SENSE_10;
	cgc->cmd[2] = page_code | (page_control << 6);
	cgc->cmd[7] = cgc->buflen >> 8;
	cgc->cmd[8] = cgc->buflen & 0xff;
	cgc->data_direction = CGC_DATA_READ;
	वापस pkt_generic_packet(pd, cgc);
पूर्ण

अटल पूर्णांक pkt_mode_select(काष्ठा pktcdvd_device *pd, काष्ठा packet_command *cgc)
अणु
	स_रखो(cgc->cmd, 0, माप(cgc->cmd));
	स_रखो(cgc->buffer, 0, 2);
	cgc->cmd[0] = GPCMD_MODE_SELECT_10;
	cgc->cmd[1] = 0x10;		/* PF */
	cgc->cmd[7] = cgc->buflen >> 8;
	cgc->cmd[8] = cgc->buflen & 0xff;
	cgc->data_direction = CGC_DATA_WRITE;
	वापस pkt_generic_packet(pd, cgc);
पूर्ण

अटल पूर्णांक pkt_get_disc_info(काष्ठा pktcdvd_device *pd, disc_inक्रमmation *di)
अणु
	काष्ठा packet_command cgc;
	पूर्णांक ret;

	/* set up command and get the disc info */
	init_cdrom_command(&cgc, di, माप(*di), CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_DISC_INFO;
	cgc.cmd[8] = cgc.buflen = 2;
	cgc.quiet = 1;

	ret = pkt_generic_packet(pd, &cgc);
	अगर (ret)
		वापस ret;

	/* not all drives have the same disc_info length, so requeue
	 * packet with the length the drive tells us it can supply
	 */
	cgc.buflen = be16_to_cpu(di->disc_inक्रमmation_length) +
		     माप(di->disc_inक्रमmation_length);

	अगर (cgc.buflen > माप(disc_inक्रमmation))
		cgc.buflen = माप(disc_inक्रमmation);

	cgc.cmd[8] = cgc.buflen;
	वापस pkt_generic_packet(pd, &cgc);
पूर्ण

अटल पूर्णांक pkt_get_track_info(काष्ठा pktcdvd_device *pd, __u16 track, __u8 type, track_inक्रमmation *ti)
अणु
	काष्ठा packet_command cgc;
	पूर्णांक ret;

	init_cdrom_command(&cgc, ti, 8, CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_TRACK_RZONE_INFO;
	cgc.cmd[1] = type & 3;
	cgc.cmd[4] = (track & 0xff00) >> 8;
	cgc.cmd[5] = track & 0xff;
	cgc.cmd[8] = 8;
	cgc.quiet = 1;

	ret = pkt_generic_packet(pd, &cgc);
	अगर (ret)
		वापस ret;

	cgc.buflen = be16_to_cpu(ti->track_inक्रमmation_length) +
		     माप(ti->track_inक्रमmation_length);

	अगर (cgc.buflen > माप(track_inक्रमmation))
		cgc.buflen = माप(track_inक्रमmation);

	cgc.cmd[8] = cgc.buflen;
	वापस pkt_generic_packet(pd, &cgc);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_get_last_written(काष्ठा pktcdvd_device *pd,
						दीर्घ *last_written)
अणु
	disc_inक्रमmation di;
	track_inक्रमmation ti;
	__u32 last_track;
	पूर्णांक ret;

	ret = pkt_get_disc_info(pd, &di);
	अगर (ret)
		वापस ret;

	last_track = (di.last_track_msb << 8) | di.last_track_lsb;
	ret = pkt_get_track_info(pd, last_track, 1, &ti);
	अगर (ret)
		वापस ret;

	/* अगर this track is blank, try the previous. */
	अगर (ti.blank) अणु
		last_track--;
		ret = pkt_get_track_info(pd, last_track, 1, &ti);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* अगर last recorded field is valid, वापस it. */
	अगर (ti.lra_v) अणु
		*last_written = be32_to_cpu(ti.last_rec_address);
	पूर्ण अन्यथा अणु
		/* make it up instead */
		*last_written = be32_to_cpu(ti.track_start) +
				be32_to_cpu(ti.track_size);
		अगर (ti.मुक्त_blocks)
			*last_written -= (be32_to_cpu(ti.मुक्त_blocks) + 7);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ग_लिखो mode select package based on pd->settings
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_set_ग_लिखो_settings(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा packet_command cgc;
	काष्ठा scsi_sense_hdr sshdr;
	ग_लिखो_param_page *wp;
	अक्षर buffer[128];
	पूर्णांक ret, size;

	/* करोesn't apply to DVD+RW or DVD-RAM */
	अगर ((pd->mmc3_profile == 0x1a) || (pd->mmc3_profile == 0x12))
		वापस 0;

	स_रखो(buffer, 0, माप(buffer));
	init_cdrom_command(&cgc, buffer, माप(*wp), CGC_DATA_READ);
	cgc.sshdr = &sshdr;
	ret = pkt_mode_sense(pd, &cgc, GPMODE_WRITE_PARMS_PAGE, 0);
	अगर (ret) अणु
		pkt_dump_sense(pd, &cgc);
		वापस ret;
	पूर्ण

	size = 2 + ((buffer[0] << 8) | (buffer[1] & 0xff));
	pd->mode_offset = (buffer[6] << 8) | (buffer[7] & 0xff);
	अगर (size > माप(buffer))
		size = माप(buffer);

	/*
	 * now get it all
	 */
	init_cdrom_command(&cgc, buffer, size, CGC_DATA_READ);
	cgc.sshdr = &sshdr;
	ret = pkt_mode_sense(pd, &cgc, GPMODE_WRITE_PARMS_PAGE, 0);
	अगर (ret) अणु
		pkt_dump_sense(pd, &cgc);
		वापस ret;
	पूर्ण

	/*
	 * ग_लिखो page is offset header + block descriptor length
	 */
	wp = (ग_लिखो_param_page *) &buffer[माप(काष्ठा mode_page_header) + pd->mode_offset];

	wp->fp = pd->settings.fp;
	wp->track_mode = pd->settings.track_mode;
	wp->ग_लिखो_type = pd->settings.ग_लिखो_type;
	wp->data_block_type = pd->settings.block_mode;

	wp->multi_session = 0;

#अगर_घोषित PACKET_USE_LS
	wp->link_size = 7;
	wp->ls_v = 1;
#पूर्ण_अगर

	अगर (wp->data_block_type == PACKET_BLOCK_MODE1) अणु
		wp->session_क्रमmat = 0;
		wp->subhdr2 = 0x20;
	पूर्ण अन्यथा अगर (wp->data_block_type == PACKET_BLOCK_MODE2) अणु
		wp->session_क्रमmat = 0x20;
		wp->subhdr2 = 8;
#अगर 0
		wp->mcn[0] = 0x80;
		स_नकल(&wp->mcn[1], PACKET_MCN, माप(wp->mcn) - 1);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/*
		 * paranoia
		 */
		pkt_err(pd, "write mode wrong %d\n", wp->data_block_type);
		वापस 1;
	पूर्ण
	wp->packet_size = cpu_to_be32(pd->settings.size >> 2);

	cgc.buflen = cgc.cmd[8] = size;
	ret = pkt_mode_select(pd, &cgc);
	अगर (ret) अणु
		pkt_dump_sense(pd, &cgc);
		वापस ret;
	पूर्ण

	pkt_prपूर्णांक_settings(pd);
	वापस 0;
पूर्ण

/*
 * 1 -- we can ग_लिखो to this track, 0 -- we can't
 */
अटल पूर्णांक pkt_writable_track(काष्ठा pktcdvd_device *pd, track_inक्रमmation *ti)
अणु
	चयन (pd->mmc3_profile) अणु
		हाल 0x1a: /* DVD+RW */
		हाल 0x12: /* DVD-RAM */
			/* The track is always writable on DVD+RW/DVD-RAM */
			वापस 1;
		शेष:
			अवरोध;
	पूर्ण

	अगर (!ti->packet || !ti->fp)
		वापस 0;

	/*
	 * "good" settings as per Mt Fuji.
	 */
	अगर (ti->rt == 0 && ti->blank == 0)
		वापस 1;

	अगर (ti->rt == 0 && ti->blank == 1)
		वापस 1;

	अगर (ti->rt == 1 && ti->blank == 0)
		वापस 1;

	pkt_err(pd, "bad state %d-%d-%d\n", ti->rt, ti->blank, ti->packet);
	वापस 0;
पूर्ण

/*
 * 1 -- we can ग_लिखो to this disc, 0 -- we can't
 */
अटल पूर्णांक pkt_writable_disc(काष्ठा pktcdvd_device *pd, disc_inक्रमmation *di)
अणु
	चयन (pd->mmc3_profile) अणु
		हाल 0x0a: /* CD-RW */
		हाल 0xffff: /* MMC3 not supported */
			अवरोध;
		हाल 0x1a: /* DVD+RW */
		हाल 0x13: /* DVD-RW */
		हाल 0x12: /* DVD-RAM */
			वापस 1;
		शेष:
			pkt_dbg(2, pd, "Wrong disc profile (%x)\n",
				pd->mmc3_profile);
			वापस 0;
	पूर्ण

	/*
	 * क्रम disc type 0xff we should probably reserve a new track.
	 * but i'm not sure, should we leave this to user apps? probably.
	 */
	अगर (di->disc_type == 0xff) अणु
		pkt_notice(pd, "unknown disc - no track?\n");
		वापस 0;
	पूर्ण

	अगर (di->disc_type != 0x20 && di->disc_type != 0) अणु
		pkt_err(pd, "wrong disc type (%x)\n", di->disc_type);
		वापस 0;
	पूर्ण

	अगर (di->erasable == 0) अणु
		pkt_notice(pd, "disc not erasable\n");
		वापस 0;
	पूर्ण

	अगर (di->border_status == PACKET_SESSION_RESERVED) अणु
		pkt_err(pd, "can't write to last track (reserved)\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_probe_settings(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा packet_command cgc;
	अचिन्हित अक्षर buf[12];
	disc_inक्रमmation di;
	track_inक्रमmation ti;
	पूर्णांक ret, track;

	init_cdrom_command(&cgc, buf, माप(buf), CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;
	cgc.cmd[8] = 8;
	ret = pkt_generic_packet(pd, &cgc);
	pd->mmc3_profile = ret ? 0xffff : buf[6] << 8 | buf[7];

	स_रखो(&di, 0, माप(disc_inक्रमmation));
	स_रखो(&ti, 0, माप(track_inक्रमmation));

	ret = pkt_get_disc_info(pd, &di);
	अगर (ret) अणु
		pkt_err(pd, "failed get_disc\n");
		वापस ret;
	पूर्ण

	अगर (!pkt_writable_disc(pd, &di))
		वापस -EROFS;

	pd->type = di.erasable ? PACKET_CDRW : PACKET_CDR;

	track = 1; /* (di.last_track_msb << 8) | di.last_track_lsb; */
	ret = pkt_get_track_info(pd, track, 1, &ti);
	अगर (ret) अणु
		pkt_err(pd, "failed get_track\n");
		वापस ret;
	पूर्ण

	अगर (!pkt_writable_track(pd, &ti)) अणु
		pkt_err(pd, "can't write to this track\n");
		वापस -EROFS;
	पूर्ण

	/*
	 * we keep packet size in 512 byte units, makes it easier to
	 * deal with request calculations.
	 */
	pd->settings.size = be32_to_cpu(ti.fixed_packet_size) << 2;
	अगर (pd->settings.size == 0) अणु
		pkt_notice(pd, "detected zero packet size!\n");
		वापस -ENXIO;
	पूर्ण
	अगर (pd->settings.size > PACKET_MAX_SECTORS) अणु
		pkt_err(pd, "packet size is too big\n");
		वापस -EROFS;
	पूर्ण
	pd->settings.fp = ti.fp;
	pd->offset = (be32_to_cpu(ti.track_start) << 2) & (pd->settings.size - 1);

	अगर (ti.nwa_v) अणु
		pd->nwa = be32_to_cpu(ti.next_writable);
		set_bit(PACKET_NWA_VALID, &pd->flags);
	पूर्ण

	/*
	 * in theory we could use lra on -RW media as well and just zero
	 * blocks that haven't been written yet, but in practice that
	 * is just a no-go. we'll use that क्रम -R, naturally.
	 */
	अगर (ti.lra_v) अणु
		pd->lra = be32_to_cpu(ti.last_rec_address);
		set_bit(PACKET_LRA_VALID, &pd->flags);
	पूर्ण अन्यथा अणु
		pd->lra = 0xffffffff;
		set_bit(PACKET_LRA_VALID, &pd->flags);
	पूर्ण

	/*
	 * fine क्रम now
	 */
	pd->settings.link_loss = 7;
	pd->settings.ग_लिखो_type = 0;	/* packet */
	pd->settings.track_mode = ti.track_mode;

	/*
	 * mode1 or mode2 disc
	 */
	चयन (ti.data_mode) अणु
		हाल PACKET_MODE1:
			pd->settings.block_mode = PACKET_BLOCK_MODE1;
			अवरोध;
		हाल PACKET_MODE2:
			pd->settings.block_mode = PACKET_BLOCK_MODE2;
			अवरोध;
		शेष:
			pkt_err(pd, "unknown data mode\n");
			वापस -EROFS;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * enable/disable ग_लिखो caching on drive
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_ग_लिखो_caching(काष्ठा pktcdvd_device *pd,
						पूर्णांक set)
अणु
	काष्ठा packet_command cgc;
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित अक्षर buf[64];
	पूर्णांक ret;

	init_cdrom_command(&cgc, buf, माप(buf), CGC_DATA_READ);
	cgc.sshdr = &sshdr;
	cgc.buflen = pd->mode_offset + 12;

	/*
	 * caching mode page might not be there, so quiet this command
	 */
	cgc.quiet = 1;

	ret = pkt_mode_sense(pd, &cgc, GPMODE_WCACHING_PAGE, 0);
	अगर (ret)
		वापस ret;

	buf[pd->mode_offset + 10] |= (!!set << 2);

	cgc.buflen = cgc.cmd[8] = 2 + ((buf[0] << 8) | (buf[1] & 0xff));
	ret = pkt_mode_select(pd, &cgc);
	अगर (ret) अणु
		pkt_err(pd, "write caching control failed\n");
		pkt_dump_sense(pd, &cgc);
	पूर्ण अन्यथा अगर (!ret && set)
		pkt_notice(pd, "enabled write caching\n");
	वापस ret;
पूर्ण

अटल पूर्णांक pkt_lock_करोor(काष्ठा pktcdvd_device *pd, पूर्णांक lockflag)
अणु
	काष्ठा packet_command cgc;

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL;
	cgc.cmd[4] = lockflag ? 1 : 0;
	वापस pkt_generic_packet(pd, &cgc);
पूर्ण

/*
 * Returns drive maximum ग_लिखो speed
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_get_max_speed(काष्ठा pktcdvd_device *pd,
						अचिन्हित *ग_लिखो_speed)
अणु
	काष्ठा packet_command cgc;
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित अक्षर buf[256+18];
	अचिन्हित अक्षर *cap_buf;
	पूर्णांक ret, offset;

	cap_buf = &buf[माप(काष्ठा mode_page_header) + pd->mode_offset];
	init_cdrom_command(&cgc, buf, माप(buf), CGC_DATA_UNKNOWN);
	cgc.sshdr = &sshdr;

	ret = pkt_mode_sense(pd, &cgc, GPMODE_CAPABILITIES_PAGE, 0);
	अगर (ret) अणु
		cgc.buflen = pd->mode_offset + cap_buf[1] + 2 +
			     माप(काष्ठा mode_page_header);
		ret = pkt_mode_sense(pd, &cgc, GPMODE_CAPABILITIES_PAGE, 0);
		अगर (ret) अणु
			pkt_dump_sense(pd, &cgc);
			वापस ret;
		पूर्ण
	पूर्ण

	offset = 20;			    /* Obsoleted field, used by older drives */
	अगर (cap_buf[1] >= 28)
		offset = 28;		    /* Current ग_लिखो speed selected */
	अगर (cap_buf[1] >= 30) अणु
		/* If the drive reports at least one "Logical Unit Write
		 * Speed Perक्रमmance Descriptor Block", use the inक्रमmation
		 * in the first block. (contains the highest speed)
		 */
		पूर्णांक num_spdb = (cap_buf[30] << 8) + cap_buf[31];
		अगर (num_spdb > 0)
			offset = 34;
	पूर्ण

	*ग_लिखो_speed = (cap_buf[offset] << 8) | cap_buf[offset + 1];
	वापस 0;
पूर्ण

/* These tables from cdrecord - I करोn't have orange book */
/* standard speed CD-RW (1-4x) */
अटल अक्षर clv_to_speed[16] = अणु
	/* 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
	   0, 2, 4, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;
/* high speed CD-RW (-10x) */
अटल अक्षर hs_clv_to_speed[16] = अणु
	/* 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
	   0, 2, 4, 6, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;
/* ultra high speed CD-RW */
अटल अक्षर us_clv_to_speed[16] = अणु
	/* 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
	   0, 2, 4, 8, 0, 0,16, 0,24,32,40,48, 0, 0, 0, 0
पूर्ण;

/*
 * पढ़ोs the maximum media speed from ATIP
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_media_speed(काष्ठा pktcdvd_device *pd,
						अचिन्हित *speed)
अणु
	काष्ठा packet_command cgc;
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित अक्षर buf[64];
	अचिन्हित पूर्णांक size, st, sp;
	पूर्णांक ret;

	init_cdrom_command(&cgc, buf, 2, CGC_DATA_READ);
	cgc.sshdr = &sshdr;
	cgc.cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cgc.cmd[1] = 2;
	cgc.cmd[2] = 4; /* READ ATIP */
	cgc.cmd[8] = 2;
	ret = pkt_generic_packet(pd, &cgc);
	अगर (ret) अणु
		pkt_dump_sense(pd, &cgc);
		वापस ret;
	पूर्ण
	size = ((अचिन्हित पूर्णांक) buf[0]<<8) + buf[1] + 2;
	अगर (size > माप(buf))
		size = माप(buf);

	init_cdrom_command(&cgc, buf, size, CGC_DATA_READ);
	cgc.sshdr = &sshdr;
	cgc.cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cgc.cmd[1] = 2;
	cgc.cmd[2] = 4;
	cgc.cmd[8] = size;
	ret = pkt_generic_packet(pd, &cgc);
	अगर (ret) अणु
		pkt_dump_sense(pd, &cgc);
		वापस ret;
	पूर्ण

	अगर (!(buf[6] & 0x40)) अणु
		pkt_notice(pd, "disc type is not CD-RW\n");
		वापस 1;
	पूर्ण
	अगर (!(buf[6] & 0x4)) अणु
		pkt_notice(pd, "A1 values on media are not valid, maybe not CDRW?\n");
		वापस 1;
	पूर्ण

	st = (buf[6] >> 3) & 0x7; /* disc sub-type */

	sp = buf[16] & 0xf; /* max speed from ATIP A1 field */

	/* Info from cdrecord */
	चयन (st) अणु
		हाल 0: /* standard speed */
			*speed = clv_to_speed[sp];
			अवरोध;
		हाल 1: /* high speed */
			*speed = hs_clv_to_speed[sp];
			अवरोध;
		हाल 2: /* ultra high speed */
			*speed = us_clv_to_speed[sp];
			अवरोध;
		शेष:
			pkt_notice(pd, "unknown disc sub-type %d\n", st);
			वापस 1;
	पूर्ण
	अगर (*speed) अणु
		pkt_info(pd, "maximum media speed: %d\n", *speed);
		वापस 0;
	पूर्ण अन्यथा अणु
		pkt_notice(pd, "unknown speed %d for sub-type %d\n", sp, st);
		वापस 1;
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक pkt_perक्रमm_opc(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा packet_command cgc;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक ret;

	pkt_dbg(2, pd, "Performing OPC\n");

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.sshdr = &sshdr;
	cgc.समयout = 60*HZ;
	cgc.cmd[0] = GPCMD_SEND_OPC;
	cgc.cmd[1] = 1;
	ret = pkt_generic_packet(pd, &cgc);
	अगर (ret)
		pkt_dump_sense(pd, &cgc);
	वापस ret;
पूर्ण

अटल पूर्णांक pkt_खोलो_ग_लिखो(काष्ठा pktcdvd_device *pd)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ग_लिखो_speed, media_ग_लिखो_speed, पढ़ो_speed;

	ret = pkt_probe_settings(pd);
	अगर (ret) अणु
		pkt_dbg(2, pd, "failed probe\n");
		वापस ret;
	पूर्ण

	ret = pkt_set_ग_लिखो_settings(pd);
	अगर (ret) अणु
		pkt_dbg(1, pd, "failed saving write settings\n");
		वापस -EIO;
	पूर्ण

	pkt_ग_लिखो_caching(pd, USE_WCACHING);

	ret = pkt_get_max_speed(pd, &ग_लिखो_speed);
	अगर (ret)
		ग_लिखो_speed = 16 * 177;
	चयन (pd->mmc3_profile) अणु
		हाल 0x13: /* DVD-RW */
		हाल 0x1a: /* DVD+RW */
		हाल 0x12: /* DVD-RAM */
			pkt_dbg(1, pd, "write speed %ukB/s\n", ग_लिखो_speed);
			अवरोध;
		शेष:
			ret = pkt_media_speed(pd, &media_ग_लिखो_speed);
			अगर (ret)
				media_ग_लिखो_speed = 16;
			ग_लिखो_speed = min(ग_लिखो_speed, media_ग_लिखो_speed * 177);
			pkt_dbg(1, pd, "write speed %ux\n", ग_लिखो_speed / 176);
			अवरोध;
	पूर्ण
	पढ़ो_speed = ग_लिखो_speed;

	ret = pkt_set_speed(pd, ग_लिखो_speed, पढ़ो_speed);
	अगर (ret) अणु
		pkt_dbg(1, pd, "couldn't set write speed\n");
		वापस -EIO;
	पूर्ण
	pd->ग_लिखो_speed = ग_लिखो_speed;
	pd->पढ़ो_speed = पढ़ो_speed;

	ret = pkt_perक्रमm_opc(pd);
	अगर (ret) अणु
		pkt_dbg(1, pd, "Optimum Power Calibration failed\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * called at खोलो समय.
 */
अटल पूर्णांक pkt_खोलो_dev(काष्ठा pktcdvd_device *pd, भ_शेषe_t ग_लिखो)
अणु
	पूर्णांक ret;
	दीर्घ lba;
	काष्ठा request_queue *q;
	काष्ठा block_device *bdev;

	/*
	 * We need to re-खोलो the cdrom device without O_NONBLOCK to be able
	 * to पढ़ो/ग_लिखो from/to it. It is alपढ़ोy खोलोed in O_NONBLOCK mode
	 * so खोलो should not fail.
	 */
	bdev = blkdev_get_by_dev(pd->bdev->bd_dev, FMODE_READ | FMODE_EXCL, pd);
	अगर (IS_ERR(bdev)) अणु
		ret = PTR_ERR(bdev);
		जाओ out;
	पूर्ण

	ret = pkt_get_last_written(pd, &lba);
	अगर (ret) अणु
		pkt_err(pd, "pkt_get_last_written failed\n");
		जाओ out_putdev;
	पूर्ण

	set_capacity(pd->disk, lba << 2);
	set_capacity_and_notअगरy(pd->bdev->bd_disk, lba << 2);

	q = bdev_get_queue(pd->bdev);
	अगर (ग_लिखो) अणु
		ret = pkt_खोलो_ग_लिखो(pd);
		अगर (ret)
			जाओ out_putdev;
		/*
		 * Some CDRW drives can not handle ग_लिखोs larger than one packet,
		 * even अगर the size is a multiple of the packet size.
		 */
		blk_queue_max_hw_sectors(q, pd->settings.size);
		set_bit(PACKET_WRITABLE, &pd->flags);
	पूर्ण अन्यथा अणु
		pkt_set_speed(pd, MAX_SPEED, MAX_SPEED);
		clear_bit(PACKET_WRITABLE, &pd->flags);
	पूर्ण

	ret = pkt_set_segment_merging(pd, q);
	अगर (ret)
		जाओ out_putdev;

	अगर (ग_लिखो) अणु
		अगर (!pkt_grow_pktlist(pd, CONFIG_CDROM_PKTCDVD_BUFFERS)) अणु
			pkt_err(pd, "not enough memory for buffers\n");
			ret = -ENOMEM;
			जाओ out_putdev;
		पूर्ण
		pkt_info(pd, "%lukB available on disc\n", lba << 1);
	पूर्ण

	वापस 0;

out_putdev:
	blkdev_put(bdev, FMODE_READ | FMODE_EXCL);
out:
	वापस ret;
पूर्ण

/*
 * called when the device is बंदd. makes sure that the device flushes
 * the पूर्णांकernal cache beक्रमe we बंद.
 */
अटल व्योम pkt_release_dev(काष्ठा pktcdvd_device *pd, पूर्णांक flush)
अणु
	अगर (flush && pkt_flush_cache(pd))
		pkt_dbg(1, pd, "not flushing cache\n");

	pkt_lock_करोor(pd, 0);

	pkt_set_speed(pd, MAX_SPEED, MAX_SPEED);
	blkdev_put(pd->bdev, FMODE_READ | FMODE_EXCL);

	pkt_shrink_pktlist(pd);
पूर्ण

अटल काष्ठा pktcdvd_device *pkt_find_dev_from_minor(अचिन्हित पूर्णांक dev_minor)
अणु
	अगर (dev_minor >= MAX_WRITERS)
		वापस शून्य;

	dev_minor = array_index_nospec(dev_minor, MAX_WRITERS);
	वापस pkt_devs[dev_minor];
पूर्ण

अटल पूर्णांक pkt_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा pktcdvd_device *pd = शून्य;
	पूर्णांक ret;

	mutex_lock(&pktcdvd_mutex);
	mutex_lock(&ctl_mutex);
	pd = pkt_find_dev_from_minor(MINOR(bdev->bd_dev));
	अगर (!pd) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	BUG_ON(pd->refcnt < 0);

	pd->refcnt++;
	अगर (pd->refcnt > 1) अणु
		अगर ((mode & FMODE_WRITE) &&
		    !test_bit(PACKET_WRITABLE, &pd->flags)) अणु
			ret = -EBUSY;
			जाओ out_dec;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = pkt_खोलो_dev(pd, mode & FMODE_WRITE);
		अगर (ret)
			जाओ out_dec;
		/*
		 * needed here as well, since ext2 (among others) may change
		 * the blocksize at mount समय
		 */
		set_blocksize(bdev, CD_FRAMESIZE);
	पूर्ण

	mutex_unlock(&ctl_mutex);
	mutex_unlock(&pktcdvd_mutex);
	वापस 0;

out_dec:
	pd->refcnt--;
out:
	mutex_unlock(&ctl_mutex);
	mutex_unlock(&pktcdvd_mutex);
	वापस ret;
पूर्ण

अटल व्योम pkt_बंद(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा pktcdvd_device *pd = disk->निजी_data;

	mutex_lock(&pktcdvd_mutex);
	mutex_lock(&ctl_mutex);
	pd->refcnt--;
	BUG_ON(pd->refcnt < 0);
	अगर (pd->refcnt == 0) अणु
		पूर्णांक flush = test_bit(PACKET_WRITABLE, &pd->flags);
		pkt_release_dev(pd, flush);
	पूर्ण
	mutex_unlock(&ctl_mutex);
	mutex_unlock(&pktcdvd_mutex);
पूर्ण


अटल व्योम pkt_end_io_पढ़ो_cloned(काष्ठा bio *bio)
अणु
	काष्ठा packet_stacked_data *psd = bio->bi_निजी;
	काष्ठा pktcdvd_device *pd = psd->pd;

	psd->bio->bi_status = bio->bi_status;
	bio_put(bio);
	bio_endio(psd->bio);
	mempool_मुक्त(psd, &psd_pool);
	pkt_bio_finished(pd);
पूर्ण

अटल व्योम pkt_make_request_पढ़ो(काष्ठा pktcdvd_device *pd, काष्ठा bio *bio)
अणु
	काष्ठा bio *cloned_bio = bio_clone_fast(bio, GFP_NOIO, &pkt_bio_set);
	काष्ठा packet_stacked_data *psd = mempool_alloc(&psd_pool, GFP_NOIO);

	psd->pd = pd;
	psd->bio = bio;
	bio_set_dev(cloned_bio, pd->bdev);
	cloned_bio->bi_निजी = psd;
	cloned_bio->bi_end_io = pkt_end_io_पढ़ो_cloned;
	pd->stats.secs_r += bio_sectors(bio);
	pkt_queue_bio(pd, cloned_bio);
पूर्ण

अटल व्योम pkt_make_request_ग_लिखो(काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	काष्ठा pktcdvd_device *pd = q->queuedata;
	sector_t zone;
	काष्ठा packet_data *pkt;
	पूर्णांक was_empty, blocked_bio;
	काष्ठा pkt_rb_node *node;

	zone = get_zone(bio->bi_iter.bi_sector, pd);

	/*
	 * If we find a matching packet in state WAITING or READ_WAIT, we can
	 * just append this bio to that packet.
	 */
	spin_lock(&pd->cdrw.active_list_lock);
	blocked_bio = 0;
	list_क्रम_each_entry(pkt, &pd->cdrw.pkt_active_list, list) अणु
		अगर (pkt->sector == zone) अणु
			spin_lock(&pkt->lock);
			अगर ((pkt->state == PACKET_WAITING_STATE) ||
			    (pkt->state == PACKET_READ_WAIT_STATE)) अणु
				bio_list_add(&pkt->orig_bios, bio);
				pkt->ग_लिखो_size +=
					bio->bi_iter.bi_size / CD_FRAMESIZE;
				अगर ((pkt->ग_लिखो_size >= pkt->frames) &&
				    (pkt->state == PACKET_WAITING_STATE)) अणु
					atomic_inc(&pkt->run_sm);
					wake_up(&pd->wqueue);
				पूर्ण
				spin_unlock(&pkt->lock);
				spin_unlock(&pd->cdrw.active_list_lock);
				वापस;
			पूर्ण अन्यथा अणु
				blocked_bio = 1;
			पूर्ण
			spin_unlock(&pkt->lock);
		पूर्ण
	पूर्ण
	spin_unlock(&pd->cdrw.active_list_lock);

 	/*
	 * Test अगर there is enough room left in the bio work queue
	 * (queue size >= congestion on mark).
	 * If not, रुको till the work queue size is below the congestion off mark.
	 */
	spin_lock(&pd->lock);
	अगर (pd->ग_लिखो_congestion_on > 0
	    && pd->bio_queue_size >= pd->ग_लिखो_congestion_on) अणु
		set_bdi_congested(q->backing_dev_info, BLK_RW_ASYNC);
		करो अणु
			spin_unlock(&pd->lock);
			congestion_रुको(BLK_RW_ASYNC, HZ);
			spin_lock(&pd->lock);
		पूर्ण जबतक(pd->bio_queue_size > pd->ग_लिखो_congestion_off);
	पूर्ण
	spin_unlock(&pd->lock);

	/*
	 * No matching packet found. Store the bio in the work queue.
	 */
	node = mempool_alloc(&pd->rb_pool, GFP_NOIO);
	node->bio = bio;
	spin_lock(&pd->lock);
	BUG_ON(pd->bio_queue_size < 0);
	was_empty = (pd->bio_queue_size == 0);
	pkt_rbtree_insert(pd, node);
	spin_unlock(&pd->lock);

	/*
	 * Wake up the worker thपढ़ो.
	 */
	atomic_set(&pd->scan_queue, 1);
	अगर (was_empty) अणु
		/* This wake_up is required क्रम correct operation */
		wake_up(&pd->wqueue);
	पूर्ण अन्यथा अगर (!list_empty(&pd->cdrw.pkt_मुक्त_list) && !blocked_bio) अणु
		/*
		 * This wake up is not required क्रम correct operation,
		 * but improves perक्रमmance in some हालs.
		 */
		wake_up(&pd->wqueue);
	पूर्ण
पूर्ण

अटल blk_qc_t pkt_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा pktcdvd_device *pd;
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा bio *split;

	blk_queue_split(&bio);

	pd = bio->bi_bdev->bd_disk->queue->queuedata;
	अगर (!pd) अणु
		pr_err("%s incorrect request queue\n", bio_devname(bio, b));
		जाओ end_io;
	पूर्ण

	pkt_dbg(2, pd, "start = %6llx stop = %6llx\n",
		(अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector,
		(अचिन्हित दीर्घ दीर्घ)bio_end_sector(bio));

	/*
	 * Clone READ bios so we can have our own bi_end_io callback.
	 */
	अगर (bio_data_dir(bio) == READ) अणु
		pkt_make_request_पढ़ो(pd, bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	अगर (!test_bit(PACKET_WRITABLE, &pd->flags)) अणु
		pkt_notice(pd, "WRITE for ro device (%llu)\n",
			   (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
		जाओ end_io;
	पूर्ण

	अगर (!bio->bi_iter.bi_size || (bio->bi_iter.bi_size % CD_FRAMESIZE)) अणु
		pkt_err(pd, "wrong bio size\n");
		जाओ end_io;
	पूर्ण

	करो अणु
		sector_t zone = get_zone(bio->bi_iter.bi_sector, pd);
		sector_t last_zone = get_zone(bio_end_sector(bio) - 1, pd);

		अगर (last_zone != zone) अणु
			BUG_ON(last_zone != zone + pd->settings.size);

			split = bio_split(bio, last_zone -
					  bio->bi_iter.bi_sector,
					  GFP_NOIO, &pkt_bio_set);
			bio_chain(split, bio);
		पूर्ण अन्यथा अणु
			split = bio;
		पूर्ण

		pkt_make_request_ग_लिखो(bio->bi_bdev->bd_disk->queue, split);
	पूर्ण जबतक (split != bio);

	वापस BLK_QC_T_NONE;
end_io:
	bio_io_error(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल व्योम pkt_init_queue(काष्ठा pktcdvd_device *pd)
अणु
	काष्ठा request_queue *q = pd->disk->queue;

	blk_queue_logical_block_size(q, CD_FRAMESIZE);
	blk_queue_max_hw_sectors(q, PACKET_MAX_SECTORS);
	q->queuedata = pd;
पूर्ण

अटल पूर्णांक pkt_seq_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा pktcdvd_device *pd = m->निजी;
	अक्षर *msg;
	अक्षर bdev_buf[BDEVNAME_SIZE];
	पूर्णांक states[PACKET_NUM_STATES];

	seq_म_लिखो(m, "Writer %s mapped to %s:\n", pd->name,
		   bdevname(pd->bdev, bdev_buf));

	seq_म_लिखो(m, "\nSettings:\n");
	seq_म_लिखो(m, "\tpacket size:\t\t%dkB\n", pd->settings.size / 2);

	अगर (pd->settings.ग_लिखो_type == 0)
		msg = "Packet";
	अन्यथा
		msg = "Unknown";
	seq_म_लिखो(m, "\twrite type:\t\t%s\n", msg);

	seq_म_लिखो(m, "\tpacket type:\t\t%s\n", pd->settings.fp ? "Fixed" : "Variable");
	seq_म_लिखो(m, "\tlink loss:\t\t%d\n", pd->settings.link_loss);

	seq_म_लिखो(m, "\ttrack mode:\t\t%d\n", pd->settings.track_mode);

	अगर (pd->settings.block_mode == PACKET_BLOCK_MODE1)
		msg = "Mode 1";
	अन्यथा अगर (pd->settings.block_mode == PACKET_BLOCK_MODE2)
		msg = "Mode 2";
	अन्यथा
		msg = "Unknown";
	seq_म_लिखो(m, "\tblock mode:\t\t%s\n", msg);

	seq_म_लिखो(m, "\nStatistics:\n");
	seq_म_लिखो(m, "\tpackets started:\t%lu\n", pd->stats.pkt_started);
	seq_म_लिखो(m, "\tpackets ended:\t\t%lu\n", pd->stats.pkt_ended);
	seq_म_लिखो(m, "\twritten:\t\t%lukB\n", pd->stats.secs_w >> 1);
	seq_म_लिखो(m, "\tread gather:\t\t%lukB\n", pd->stats.secs_rg >> 1);
	seq_म_लिखो(m, "\tread:\t\t\t%lukB\n", pd->stats.secs_r >> 1);

	seq_म_लिखो(m, "\nMisc:\n");
	seq_म_लिखो(m, "\treference count:\t%d\n", pd->refcnt);
	seq_म_लिखो(m, "\tflags:\t\t\t0x%lx\n", pd->flags);
	seq_म_लिखो(m, "\tread speed:\t\t%ukB/s\n", pd->पढ़ो_speed);
	seq_म_लिखो(m, "\twrite speed:\t\t%ukB/s\n", pd->ग_लिखो_speed);
	seq_म_लिखो(m, "\tstart offset:\t\t%lu\n", pd->offset);
	seq_म_लिखो(m, "\tmode page offset:\t%u\n", pd->mode_offset);

	seq_म_लिखो(m, "\nQueue state:\n");
	seq_म_लिखो(m, "\tbios queued:\t\t%d\n", pd->bio_queue_size);
	seq_म_लिखो(m, "\tbios pending:\t\t%d\n", atomic_पढ़ो(&pd->cdrw.pending_bios));
	seq_म_लिखो(m, "\tcurrent sector:\t\t0x%llx\n", (अचिन्हित दीर्घ दीर्घ)pd->current_sector);

	pkt_count_states(pd, states);
	seq_म_लिखो(m, "\tstate:\t\t\ti:%d ow:%d rw:%d ww:%d rec:%d fin:%d\n",
		   states[0], states[1], states[2], states[3], states[4], states[5]);

	seq_म_लिखो(m, "\twrite congestion marks:\toff=%d on=%d\n",
			pd->ग_लिखो_congestion_off,
			pd->ग_लिखो_congestion_on);
	वापस 0;
पूर्ण

अटल पूर्णांक pkt_new_dev(काष्ठा pktcdvd_device *pd, dev_t dev)
अणु
	पूर्णांक i;
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा block_device *bdev;

	अगर (pd->pkt_dev == dev) अणु
		pkt_err(pd, "recursive setup not allowed\n");
		वापस -EBUSY;
	पूर्ण
	क्रम (i = 0; i < MAX_WRITERS; i++) अणु
		काष्ठा pktcdvd_device *pd2 = pkt_devs[i];
		अगर (!pd2)
			जारी;
		अगर (pd2->bdev->bd_dev == dev) अणु
			pkt_err(pd, "%s already setup\n",
				bdevname(pd2->bdev, b));
			वापस -EBUSY;
		पूर्ण
		अगर (pd2->pkt_dev == dev) अणु
			pkt_err(pd, "can't chain pktcdvd devices\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	bdev = blkdev_get_by_dev(dev, FMODE_READ | FMODE_NDELAY, शून्य);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);
	अगर (!blk_queue_scsi_passthrough(bdev_get_queue(bdev))) अणु
		blkdev_put(bdev, FMODE_READ | FMODE_NDELAY);
		वापस -EINVAL;
	पूर्ण

	/* This is safe, since we have a reference from खोलो(). */
	__module_get(THIS_MODULE);

	pd->bdev = bdev;
	set_blocksize(bdev, CD_FRAMESIZE);

	pkt_init_queue(pd);

	atomic_set(&pd->cdrw.pending_bios, 0);
	pd->cdrw.thपढ़ो = kthपढ़ो_run(kcdrwd, pd, "%s", pd->name);
	अगर (IS_ERR(pd->cdrw.thपढ़ो)) अणु
		pkt_err(pd, "can't start kernel thread\n");
		जाओ out_mem;
	पूर्ण

	proc_create_single_data(pd->name, 0, pkt_proc, pkt_seq_show, pd);
	pkt_dbg(1, pd, "writer mapped to %s\n", bdevname(bdev, b));
	वापस 0;

out_mem:
	blkdev_put(bdev, FMODE_READ | FMODE_NDELAY);
	/* This is safe: खोलो() is still holding a reference. */
	module_put(THIS_MODULE);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक pkt_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pktcdvd_device *pd = bdev->bd_disk->निजी_data;
	पूर्णांक ret;

	pkt_dbg(2, pd, "cmd %x, dev %d:%d\n",
		cmd, MAJOR(bdev->bd_dev), MINOR(bdev->bd_dev));

	mutex_lock(&pktcdvd_mutex);
	चयन (cmd) अणु
	हाल CDROMEJECT:
		/*
		 * The करोor माला_लो locked when the device is खोलोed, so we
		 * have to unlock it or अन्यथा the eject command fails.
		 */
		अगर (pd->refcnt == 1)
			pkt_lock_करोor(pd, 0);
		fallthrough;
	/*
	 * क्रमward selected CDROM ioctls to CD-ROM, क्रम UDF
	 */
	हाल CDROMMULTISESSION:
	हाल CDROMREADTOCENTRY:
	हाल CDROM_LAST_WRITTEN:
	हाल CDROM_SEND_PACKET:
	हाल SCSI_IOCTL_SEND_COMMAND:
		अगर (!bdev->bd_disk->fops->ioctl)
			ret = -ENOTTY;
		अन्यथा
			ret = bdev->bd_disk->fops->ioctl(bdev, mode, cmd, arg);
		अवरोध;
	शेष:
		pkt_dbg(2, pd, "Unknown ioctl (%x)\n", cmd);
		ret = -ENOTTY;
	पूर्ण
	mutex_unlock(&pktcdvd_mutex);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक pkt_check_events(काष्ठा gendisk *disk,
				     अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा pktcdvd_device *pd = disk->निजी_data;
	काष्ठा gendisk *attached_disk;

	अगर (!pd)
		वापस 0;
	अगर (!pd->bdev)
		वापस 0;
	attached_disk = pd->bdev->bd_disk;
	अगर (!attached_disk || !attached_disk->fops->check_events)
		वापस 0;
	वापस attached_disk->fops->check_events(attached_disk, clearing);
पूर्ण

अटल अक्षर *pkt_devnode(काष्ठा gendisk *disk, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "pktcdvd/%s", disk->disk_name);
पूर्ण

अटल स्थिर काष्ठा block_device_operations pktcdvd_ops = अणु
	.owner =		THIS_MODULE,
	.submit_bio =		pkt_submit_bio,
	.खोलो =			pkt_खोलो,
	.release =		pkt_बंद,
	.ioctl =		pkt_ioctl,
	.compat_ioctl =		blkdev_compat_ptr_ioctl,
	.check_events =		pkt_check_events,
	.devnode =		pkt_devnode,
पूर्ण;

/*
 * Set up mapping from pktcdvd device to CD-ROM device.
 */
अटल पूर्णांक pkt_setup_dev(dev_t dev, dev_t* pkt_dev)
अणु
	पूर्णांक idx;
	पूर्णांक ret = -ENOMEM;
	काष्ठा pktcdvd_device *pd;
	काष्ठा gendisk *disk;

	mutex_lock_nested(&ctl_mutex, SINGLE_DEPTH_NESTING);

	क्रम (idx = 0; idx < MAX_WRITERS; idx++)
		अगर (!pkt_devs[idx])
			अवरोध;
	अगर (idx == MAX_WRITERS) अणु
		pr_err("max %d writers supported\n", MAX_WRITERS);
		ret = -EBUSY;
		जाओ out_mutex;
	पूर्ण

	pd = kzalloc(माप(काष्ठा pktcdvd_device), GFP_KERNEL);
	अगर (!pd)
		जाओ out_mutex;

	ret = mempool_init_kदो_स्मृति_pool(&pd->rb_pool, PKT_RB_POOL_SIZE,
					माप(काष्ठा pkt_rb_node));
	अगर (ret)
		जाओ out_mem;

	INIT_LIST_HEAD(&pd->cdrw.pkt_मुक्त_list);
	INIT_LIST_HEAD(&pd->cdrw.pkt_active_list);
	spin_lock_init(&pd->cdrw.active_list_lock);

	spin_lock_init(&pd->lock);
	spin_lock_init(&pd->iosched.lock);
	bio_list_init(&pd->iosched.पढ़ो_queue);
	bio_list_init(&pd->iosched.ग_लिखो_queue);
	प्र_लिखो(pd->name, DRIVER_NAME"%d", idx);
	init_रुकोqueue_head(&pd->wqueue);
	pd->bio_queue = RB_ROOT;

	pd->ग_लिखो_congestion_on  = ग_लिखो_congestion_on;
	pd->ग_लिखो_congestion_off = ग_लिखो_congestion_off;

	ret = -ENOMEM;
	disk = alloc_disk(1);
	अगर (!disk)
		जाओ out_mem;
	pd->disk = disk;
	disk->major = pktdev_major;
	disk->first_minor = idx;
	disk->fops = &pktcdvd_ops;
	disk->flags = GENHD_FL_REMOVABLE;
	म_नकल(disk->disk_name, pd->name);
	disk->निजी_data = pd;
	disk->queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!disk->queue)
		जाओ out_mem2;

	pd->pkt_dev = MKDEV(pktdev_major, idx);
	ret = pkt_new_dev(pd, dev);
	अगर (ret)
		जाओ out_mem2;

	/* inherit events of the host device */
	disk->events = pd->bdev->bd_disk->events;

	add_disk(disk);

	pkt_sysfs_dev_new(pd);
	pkt_debugfs_dev_new(pd);

	pkt_devs[idx] = pd;
	अगर (pkt_dev)
		*pkt_dev = pd->pkt_dev;

	mutex_unlock(&ctl_mutex);
	वापस 0;

out_mem2:
	put_disk(disk);
out_mem:
	mempool_निकास(&pd->rb_pool);
	kमुक्त(pd);
out_mutex:
	mutex_unlock(&ctl_mutex);
	pr_err("setup of pktcdvd device failed\n");
	वापस ret;
पूर्ण

/*
 * Tear करोwn mapping from pktcdvd device to CD-ROM device.
 */
अटल पूर्णांक pkt_हटाओ_dev(dev_t pkt_dev)
अणु
	काष्ठा pktcdvd_device *pd;
	पूर्णांक idx;
	पूर्णांक ret = 0;

	mutex_lock_nested(&ctl_mutex, SINGLE_DEPTH_NESTING);

	क्रम (idx = 0; idx < MAX_WRITERS; idx++) अणु
		pd = pkt_devs[idx];
		अगर (pd && (pd->pkt_dev == pkt_dev))
			अवरोध;
	पूर्ण
	अगर (idx == MAX_WRITERS) अणु
		pr_debug("dev not setup\n");
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (pd->refcnt > 0) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (!IS_ERR(pd->cdrw.thपढ़ो))
		kthपढ़ो_stop(pd->cdrw.thपढ़ो);

	pkt_devs[idx] = शून्य;

	pkt_debugfs_dev_हटाओ(pd);
	pkt_sysfs_dev_हटाओ(pd);

	blkdev_put(pd->bdev, FMODE_READ | FMODE_NDELAY);

	हटाओ_proc_entry(pd->name, pkt_proc);
	pkt_dbg(1, pd, "writer unmapped\n");

	del_gendisk(pd->disk);
	blk_cleanup_queue(pd->disk->queue);
	put_disk(pd->disk);

	mempool_निकास(&pd->rb_pool);
	kमुक्त(pd);

	/* This is safe: खोलो() is still holding a reference. */
	module_put(THIS_MODULE);

out:
	mutex_unlock(&ctl_mutex);
	वापस ret;
पूर्ण

अटल व्योम pkt_get_status(काष्ठा pkt_ctrl_command *ctrl_cmd)
अणु
	काष्ठा pktcdvd_device *pd;

	mutex_lock_nested(&ctl_mutex, SINGLE_DEPTH_NESTING);

	pd = pkt_find_dev_from_minor(ctrl_cmd->dev_index);
	अगर (pd) अणु
		ctrl_cmd->dev = new_encode_dev(pd->bdev->bd_dev);
		ctrl_cmd->pkt_dev = new_encode_dev(pd->pkt_dev);
	पूर्ण अन्यथा अणु
		ctrl_cmd->dev = 0;
		ctrl_cmd->pkt_dev = 0;
	पूर्ण
	ctrl_cmd->num_devices = MAX_WRITERS;

	mutex_unlock(&ctl_mutex);
पूर्ण

अटल दीर्घ pkt_ctl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा pkt_ctrl_command ctrl_cmd;
	पूर्णांक ret = 0;
	dev_t pkt_dev = 0;

	अगर (cmd != PACKET_CTRL_CMD)
		वापस -ENOTTY;

	अगर (copy_from_user(&ctrl_cmd, argp, माप(काष्ठा pkt_ctrl_command)))
		वापस -EFAULT;

	चयन (ctrl_cmd.command) अणु
	हाल PKT_CTRL_CMD_SETUP:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		ret = pkt_setup_dev(new_decode_dev(ctrl_cmd.dev), &pkt_dev);
		ctrl_cmd.pkt_dev = new_encode_dev(pkt_dev);
		अवरोध;
	हाल PKT_CTRL_CMD_TEARDOWN:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		ret = pkt_हटाओ_dev(new_decode_dev(ctrl_cmd.pkt_dev));
		अवरोध;
	हाल PKT_CTRL_CMD_STATUS:
		pkt_get_status(&ctrl_cmd);
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण

	अगर (copy_to_user(argp, &ctrl_cmd, माप(काष्ठा pkt_ctrl_command)))
		वापस -EFAULT;
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ pkt_ctl_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस pkt_ctl_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations pkt_ctl_fops = अणु
	.खोलो		= nonseekable_खोलो,
	.unlocked_ioctl	= pkt_ctl_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= pkt_ctl_compat_ioctl,
#पूर्ण_अगर
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice pkt_misc = अणु
	.minor 		= MISC_DYNAMIC_MINOR,
	.name  		= DRIVER_NAME,
	.nodename	= "pktcdvd/control",
	.fops  		= &pkt_ctl_fops
पूर्ण;

अटल पूर्णांक __init pkt_init(व्योम)
अणु
	पूर्णांक ret;

	mutex_init(&ctl_mutex);

	ret = mempool_init_kदो_स्मृति_pool(&psd_pool, PSD_POOL_SIZE,
				    माप(काष्ठा packet_stacked_data));
	अगर (ret)
		वापस ret;
	ret = bioset_init(&pkt_bio_set, BIO_POOL_SIZE, 0, 0);
	अगर (ret) अणु
		mempool_निकास(&psd_pool);
		वापस ret;
	पूर्ण

	ret = रेजिस्टर_blkdev(pktdev_major, DRIVER_NAME);
	अगर (ret < 0) अणु
		pr_err("unable to register block device\n");
		जाओ out2;
	पूर्ण
	अगर (!pktdev_major)
		pktdev_major = ret;

	ret = pkt_sysfs_init();
	अगर (ret)
		जाओ out;

	pkt_debugfs_init();

	ret = misc_रेजिस्टर(&pkt_misc);
	अगर (ret) अणु
		pr_err("unable to register misc device\n");
		जाओ out_misc;
	पूर्ण

	pkt_proc = proc_सूची_गढ़ो("driver/"DRIVER_NAME, शून्य);

	वापस 0;

out_misc:
	pkt_debugfs_cleanup();
	pkt_sysfs_cleanup();
out:
	unरेजिस्टर_blkdev(pktdev_major, DRIVER_NAME);
out2:
	mempool_निकास(&psd_pool);
	bioset_निकास(&pkt_bio_set);
	वापस ret;
पूर्ण

अटल व्योम __निकास pkt_निकास(व्योम)
अणु
	हटाओ_proc_entry("driver/"DRIVER_NAME, शून्य);
	misc_deरेजिस्टर(&pkt_misc);

	pkt_debugfs_cleanup();
	pkt_sysfs_cleanup();

	unरेजिस्टर_blkdev(pktdev_major, DRIVER_NAME);
	mempool_निकास(&psd_pool);
	bioset_निकास(&pkt_bio_set);
पूर्ण

MODULE_DESCRIPTION("Packet writing layer for CD/DVD drives");
MODULE_AUTHOR("Jens Axboe <axboe@suse.de>");
MODULE_LICENSE("GPL");

module_init(pkt_init);
module_निकास(pkt_निकास);
