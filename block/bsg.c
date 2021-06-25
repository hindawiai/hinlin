<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bsg.c - block layer implementation of the sg v4 पूर्णांकerface
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/file.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/cdev.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/percpu.h>
#समावेश <linux/idr.h>
#समावेश <linux/bsg.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/sg.h>

#घोषणा BSG_DESCRIPTION	"Block layer SCSI generic (bsg) driver"
#घोषणा BSG_VERSION	"0.4"

#घोषणा bsg_dbg(bd, fmt, ...) \
	pr_debug("%s: " fmt, (bd)->name, ##__VA_ARGS__)

काष्ठा bsg_device अणु
	काष्ठा request_queue *queue;
	spinlock_t lock;
	काष्ठा hlist_node dev_list;
	refcount_t ref_count;
	अक्षर name[20];
	पूर्णांक max_queue;
पूर्ण;

#घोषणा BSG_DEFAULT_CMDS	64
#घोषणा BSG_MAX_DEVS		32768

अटल DEFINE_MUTEX(bsg_mutex);
अटल DEFINE_IDR(bsg_minor_idr);

#घोषणा BSG_LIST_ARRAY_SIZE	8
अटल काष्ठा hlist_head bsg_device_list[BSG_LIST_ARRAY_SIZE];

अटल काष्ठा class *bsg_class;
अटल पूर्णांक bsg_major;

अटल अंतरभूत काष्ठा hlist_head *bsg_dev_idx_hash(पूर्णांक index)
अणु
	वापस &bsg_device_list[index & (BSG_LIST_ARRAY_SIZE - 1)];
पूर्ण

#घोषणा uptr64(val) ((व्योम __user *)(uपूर्णांकptr_t)(val))

अटल पूर्णांक bsg_scsi_check_proto(काष्ठा sg_io_v4 *hdr)
अणु
	अगर (hdr->protocol != BSG_PROTOCOL_SCSI  ||
	    hdr->subprotocol != BSG_SUB_PROTOCOL_SCSI_CMD)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक bsg_scsi_fill_hdr(काष्ठा request *rq, काष्ठा sg_io_v4 *hdr,
		भ_शेषe_t mode)
अणु
	काष्ठा scsi_request *sreq = scsi_req(rq);

	अगर (hdr->करोut_xfer_len && hdr->din_xfer_len) अणु
		pr_warn_once("BIDI support in bsg has been removed.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	sreq->cmd_len = hdr->request_len;
	अगर (sreq->cmd_len > BLK_MAX_CDB) अणु
		sreq->cmd = kzalloc(sreq->cmd_len, GFP_KERNEL);
		अगर (!sreq->cmd)
			वापस -ENOMEM;
	पूर्ण

	अगर (copy_from_user(sreq->cmd, uptr64(hdr->request), sreq->cmd_len))
		वापस -EFAULT;
	अगर (blk_verअगरy_command(sreq->cmd, mode))
		वापस -EPERM;
	वापस 0;
पूर्ण

अटल पूर्णांक bsg_scsi_complete_rq(काष्ठा request *rq, काष्ठा sg_io_v4 *hdr)
अणु
	काष्ठा scsi_request *sreq = scsi_req(rq);
	पूर्णांक ret = 0;

	/*
	 * fill in all the output members
	 */
	hdr->device_status = sreq->result & 0xff;
	hdr->transport_status = host_byte(sreq->result);
	hdr->driver_status = driver_byte(sreq->result);
	hdr->info = 0;
	अगर (hdr->device_status || hdr->transport_status || hdr->driver_status)
		hdr->info |= SG_INFO_CHECK;
	hdr->response_len = 0;

	अगर (sreq->sense_len && hdr->response) अणु
		पूर्णांक len = min_t(अचिन्हित पूर्णांक, hdr->max_response_len,
					sreq->sense_len);

		अगर (copy_to_user(uptr64(hdr->response), sreq->sense, len))
			ret = -EFAULT;
		अन्यथा
			hdr->response_len = len;
	पूर्ण

	अगर (rq_data_dir(rq) == READ)
		hdr->din_resid = sreq->resid_len;
	अन्यथा
		hdr->करोut_resid = sreq->resid_len;

	वापस ret;
पूर्ण

अटल व्योम bsg_scsi_मुक्त_rq(काष्ठा request *rq)
अणु
	scsi_req_मुक्त_cmd(scsi_req(rq));
पूर्ण

अटल स्थिर काष्ठा bsg_ops bsg_scsi_ops = अणु
	.check_proto		= bsg_scsi_check_proto,
	.fill_hdr		= bsg_scsi_fill_hdr,
	.complete_rq		= bsg_scsi_complete_rq,
	.मुक्त_rq		= bsg_scsi_मुक्त_rq,
पूर्ण;

अटल पूर्णांक bsg_sg_io(काष्ठा request_queue *q, भ_शेषe_t mode, व्योम __user *uarg)
अणु
	काष्ठा request *rq;
	काष्ठा bio *bio;
	काष्ठा sg_io_v4 hdr;
	पूर्णांक ret;

	अगर (copy_from_user(&hdr, uarg, माप(hdr)))
		वापस -EFAULT;

	अगर (!q->bsg_dev.class_dev)
		वापस -ENXIO;

	अगर (hdr.guard != 'Q')
		वापस -EINVAL;
	ret = q->bsg_dev.ops->check_proto(&hdr);
	अगर (ret)
		वापस ret;

	rq = blk_get_request(q, hdr.करोut_xfer_len ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	ret = q->bsg_dev.ops->fill_hdr(rq, &hdr, mode);
	अगर (ret) अणु
		blk_put_request(rq);
		वापस ret;
	पूर्ण

	rq->समयout = msecs_to_jअगरfies(hdr.समयout);
	अगर (!rq->समयout)
		rq->समयout = q->sg_समयout;
	अगर (!rq->समयout)
		rq->समयout = BLK_DEFAULT_SG_TIMEOUT;
	अगर (rq->समयout < BLK_MIN_SG_TIMEOUT)
		rq->समयout = BLK_MIN_SG_TIMEOUT;

	अगर (hdr.करोut_xfer_len) अणु
		ret = blk_rq_map_user(q, rq, शून्य, uptr64(hdr.करोut_xferp),
				hdr.करोut_xfer_len, GFP_KERNEL);
	पूर्ण अन्यथा अगर (hdr.din_xfer_len) अणु
		ret = blk_rq_map_user(q, rq, शून्य, uptr64(hdr.din_xferp),
				hdr.din_xfer_len, GFP_KERNEL);
	पूर्ण

	अगर (ret)
		जाओ out_मुक्त_rq;

	bio = rq->bio;

	blk_execute_rq(शून्य, rq, !(hdr.flags & BSG_FLAG_Q_AT_TAIL));
	ret = rq->q->bsg_dev.ops->complete_rq(rq, &hdr);
	blk_rq_unmap_user(bio);

out_मुक्त_rq:
	rq->q->bsg_dev.ops->मुक्त_rq(rq);
	blk_put_request(rq);
	अगर (!ret && copy_to_user(uarg, &hdr, माप(hdr)))
		वापस -EFAULT;
	वापस ret;
पूर्ण

अटल काष्ठा bsg_device *bsg_alloc_device(व्योम)
अणु
	काष्ठा bsg_device *bd;

	bd = kzalloc(माप(काष्ठा bsg_device), GFP_KERNEL);
	अगर (unlikely(!bd))
		वापस शून्य;

	spin_lock_init(&bd->lock);
	bd->max_queue = BSG_DEFAULT_CMDS;
	INIT_HLIST_NODE(&bd->dev_list);
	वापस bd;
पूर्ण

अटल पूर्णांक bsg_put_device(काष्ठा bsg_device *bd)
अणु
	काष्ठा request_queue *q = bd->queue;

	mutex_lock(&bsg_mutex);

	अगर (!refcount_dec_and_test(&bd->ref_count)) अणु
		mutex_unlock(&bsg_mutex);
		वापस 0;
	पूर्ण

	hlist_del(&bd->dev_list);
	mutex_unlock(&bsg_mutex);

	bsg_dbg(bd, "tearing down\n");

	/*
	 * बंद can always block
	 */
	kमुक्त(bd);
	blk_put_queue(q);
	वापस 0;
पूर्ण

अटल काष्ठा bsg_device *bsg_add_device(काष्ठा inode *inode,
					 काष्ठा request_queue *rq,
					 काष्ठा file *file)
अणु
	काष्ठा bsg_device *bd;
	अचिन्हित अक्षर buf[32];

	lockdep_निश्चित_held(&bsg_mutex);

	अगर (!blk_get_queue(rq))
		वापस ERR_PTR(-ENXIO);

	bd = bsg_alloc_device();
	अगर (!bd) अणु
		blk_put_queue(rq);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	bd->queue = rq;

	refcount_set(&bd->ref_count, 1);
	hlist_add_head(&bd->dev_list, bsg_dev_idx_hash(iminor(inode)));

	म_नकलन(bd->name, dev_name(rq->bsg_dev.class_dev), माप(bd->name) - 1);
	bsg_dbg(bd, "bound to <%s>, max queue %d\n",
		क्रमmat_dev_t(buf, inode->i_rdev), bd->max_queue);

	वापस bd;
पूर्ण

अटल काष्ठा bsg_device *__bsg_get_device(पूर्णांक minor, काष्ठा request_queue *q)
अणु
	काष्ठा bsg_device *bd;

	lockdep_निश्चित_held(&bsg_mutex);

	hlist_क्रम_each_entry(bd, bsg_dev_idx_hash(minor), dev_list) अणु
		अगर (bd->queue == q) अणु
			refcount_inc(&bd->ref_count);
			जाओ found;
		पूर्ण
	पूर्ण
	bd = शून्य;
found:
	वापस bd;
पूर्ण

अटल काष्ठा bsg_device *bsg_get_device(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bsg_device *bd;
	काष्ठा bsg_class_device *bcd;

	/*
	 * find the class device
	 */
	mutex_lock(&bsg_mutex);
	bcd = idr_find(&bsg_minor_idr, iminor(inode));

	अगर (!bcd) अणु
		bd = ERR_PTR(-ENODEV);
		जाओ out_unlock;
	पूर्ण

	bd = __bsg_get_device(iminor(inode), bcd->queue);
	अगर (!bd)
		bd = bsg_add_device(inode, bcd->queue, file);

out_unlock:
	mutex_unlock(&bsg_mutex);
	वापस bd;
पूर्ण

अटल पूर्णांक bsg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bsg_device *bd;

	bd = bsg_get_device(inode, file);

	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	file->निजी_data = bd;
	वापस 0;
पूर्ण

अटल पूर्णांक bsg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bsg_device *bd = file->निजी_data;

	file->निजी_data = शून्य;
	वापस bsg_put_device(bd);
पूर्ण

अटल पूर्णांक bsg_get_command_q(काष्ठा bsg_device *bd, पूर्णांक __user *uarg)
अणु
	वापस put_user(bd->max_queue, uarg);
पूर्ण

अटल पूर्णांक bsg_set_command_q(काष्ठा bsg_device *bd, पूर्णांक __user *uarg)
अणु
	पूर्णांक queue;

	अगर (get_user(queue, uarg))
		वापस -EFAULT;
	अगर (queue < 1)
		वापस -EINVAL;

	spin_lock_irq(&bd->lock);
	bd->max_queue = queue;
	spin_unlock_irq(&bd->lock);
	वापस 0;
पूर्ण

अटल दीर्घ bsg_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा bsg_device *bd = file->निजी_data;
	व्योम __user *uarg = (व्योम __user *) arg;

	चयन (cmd) अणु
	/*
	 * Our own ioctls
	 */
	हाल SG_GET_COMMAND_Q:
		वापस bsg_get_command_q(bd, uarg);
	हाल SG_SET_COMMAND_Q:
		वापस bsg_set_command_q(bd, uarg);

	/*
	 * SCSI/sg ioctls
	 */
	हाल SG_GET_VERSION_NUM:
	हाल SCSI_IOCTL_GET_IDLUN:
	हाल SCSI_IOCTL_GET_BUS_NUMBER:
	हाल SG_SET_TIMEOUT:
	हाल SG_GET_TIMEOUT:
	हाल SG_GET_RESERVED_SIZE:
	हाल SG_SET_RESERVED_SIZE:
	हाल SG_EMULATED_HOST:
	हाल SCSI_IOCTL_SEND_COMMAND:
		वापस scsi_cmd_ioctl(bd->queue, शून्य, file->f_mode, cmd, uarg);
	हाल SG_IO:
		वापस bsg_sg_io(bd->queue, file->f_mode, uarg);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations bsg_fops = अणु
	.खोलो		=	bsg_खोलो,
	.release	=	bsg_release,
	.unlocked_ioctl	=	bsg_ioctl,
	.compat_ioctl	=	compat_ptr_ioctl,
	.owner		=	THIS_MODULE,
	.llseek		=	शेष_llseek,
पूर्ण;

व्योम bsg_unरेजिस्टर_queue(काष्ठा request_queue *q)
अणु
	काष्ठा bsg_class_device *bcd = &q->bsg_dev;

	अगर (!bcd->class_dev)
		वापस;

	mutex_lock(&bsg_mutex);
	idr_हटाओ(&bsg_minor_idr, bcd->minor);
	अगर (q->kobj.sd)
		sysfs_हटाओ_link(&q->kobj, "bsg");
	device_unरेजिस्टर(bcd->class_dev);
	bcd->class_dev = शून्य;
	mutex_unlock(&bsg_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(bsg_unरेजिस्टर_queue);

पूर्णांक bsg_रेजिस्टर_queue(काष्ठा request_queue *q, काष्ठा device *parent,
		स्थिर अक्षर *name, स्थिर काष्ठा bsg_ops *ops)
अणु
	काष्ठा bsg_class_device *bcd;
	dev_t dev;
	पूर्णांक ret;
	काष्ठा device *class_dev = शून्य;

	/*
	 * we need a proper transport to send commands, not a stacked device
	 */
	अगर (!queue_is_mq(q))
		वापस 0;

	bcd = &q->bsg_dev;
	स_रखो(bcd, 0, माप(*bcd));

	mutex_lock(&bsg_mutex);

	ret = idr_alloc(&bsg_minor_idr, bcd, 0, BSG_MAX_DEVS, GFP_KERNEL);
	अगर (ret < 0) अणु
		अगर (ret == -ENOSPC) अणु
			prपूर्णांकk(KERN_ERR "bsg: too many bsg devices\n");
			ret = -EINVAL;
		पूर्ण
		जाओ unlock;
	पूर्ण

	bcd->minor = ret;
	bcd->queue = q;
	bcd->ops = ops;
	dev = MKDEV(bsg_major, bcd->minor);
	class_dev = device_create(bsg_class, parent, dev, शून्य, "%s", name);
	अगर (IS_ERR(class_dev)) अणु
		ret = PTR_ERR(class_dev);
		जाओ idr_हटाओ;
	पूर्ण
	bcd->class_dev = class_dev;

	अगर (q->kobj.sd) अणु
		ret = sysfs_create_link(&q->kobj, &bcd->class_dev->kobj, "bsg");
		अगर (ret)
			जाओ unरेजिस्टर_class_dev;
	पूर्ण

	mutex_unlock(&bsg_mutex);
	वापस 0;

unरेजिस्टर_class_dev:
	device_unरेजिस्टर(class_dev);
idr_हटाओ:
	idr_हटाओ(&bsg_minor_idr, bcd->minor);
unlock:
	mutex_unlock(&bsg_mutex);
	वापस ret;
पूर्ण

पूर्णांक bsg_scsi_रेजिस्टर_queue(काष्ठा request_queue *q, काष्ठा device *parent)
अणु
	अगर (!blk_queue_scsi_passthrough(q)) अणु
		WARN_ONCE(true, "Attempt to register a non-SCSI queue\n");
		वापस -EINVAL;
	पूर्ण

	वापस bsg_रेजिस्टर_queue(q, parent, dev_name(parent), &bsg_scsi_ops);
पूर्ण
EXPORT_SYMBOL_GPL(bsg_scsi_रेजिस्टर_queue);

अटल काष्ठा cdev bsg_cdev;

अटल अक्षर *bsg_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "bsg/%s", dev_name(dev));
पूर्ण

अटल पूर्णांक __init bsg_init(व्योम)
अणु
	पूर्णांक ret, i;
	dev_t devid;

	क्रम (i = 0; i < BSG_LIST_ARRAY_SIZE; i++)
		INIT_HLIST_HEAD(&bsg_device_list[i]);

	bsg_class = class_create(THIS_MODULE, "bsg");
	अगर (IS_ERR(bsg_class))
		वापस PTR_ERR(bsg_class);
	bsg_class->devnode = bsg_devnode;

	ret = alloc_chrdev_region(&devid, 0, BSG_MAX_DEVS, "bsg");
	अगर (ret)
		जाओ destroy_bsg_class;

	bsg_major = MAJOR(devid);

	cdev_init(&bsg_cdev, &bsg_fops);
	ret = cdev_add(&bsg_cdev, MKDEV(bsg_major, 0), BSG_MAX_DEVS);
	अगर (ret)
		जाओ unरेजिस्टर_chrdev;

	prपूर्णांकk(KERN_INFO BSG_DESCRIPTION " version " BSG_VERSION
	       " loaded (major %d)\n", bsg_major);
	वापस 0;
unरेजिस्टर_chrdev:
	unरेजिस्टर_chrdev_region(MKDEV(bsg_major, 0), BSG_MAX_DEVS);
destroy_bsg_class:
	class_destroy(bsg_class);
	वापस ret;
पूर्ण

MODULE_AUTHOR("Jens Axboe");
MODULE_DESCRIPTION(BSG_DESCRIPTION);
MODULE_LICENSE("GPL");

device_initcall(bsg_init);
