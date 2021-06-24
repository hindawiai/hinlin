<शैली गुरु>
/*
 * Block driver क्रम media (i.e., flash cards)
 *
 * Copyright 2002 Hewlett-Packard Company
 * Copyright 2005-2008 Pierre Ossman
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 *
 * HEWLETT-PACKARD COMPANY MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,
 * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS
 * FITNESS FOR ANY PARTICULAR PURPOSE.
 *
 * Many thanks to Alessandro Rubini and Jonathan Corbet!
 *
 * Author:  Andrew Christian
 *          28 May 2002
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hdreg.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/cdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/delay.h>
#समावेश <linux/capability.h>
#समावेश <linux/compat.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/idr.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/mmc/ioctl.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>

#समावेश <linux/uaccess.h>

#समावेश "queue.h"
#समावेश "block.h"
#समावेश "core.h"
#समावेश "card.h"
#समावेश "crypto.h"
#समावेश "host.h"
#समावेश "bus.h"
#समावेश "mmc_ops.h"
#समावेश "quirks.h"
#समावेश "sd_ops.h"

MODULE_ALIAS("mmc:block");
#अगर_घोषित MODULE_PARAM_PREFIX
#अघोषित MODULE_PARAM_PREFIX
#पूर्ण_अगर
#घोषणा MODULE_PARAM_PREFIX "mmcblk."

/*
 * Set a 10 second समयout क्रम polling ग_लिखो request busy state. Note, mmc core
 * is setting a 3 second समयout क्रम SD cards, and SDHCI has दीर्घ had a 10
 * second software समयr to समयout the whole request, so 10 seconds should be
 * ample.
 */
#घोषणा MMC_BLK_TIMEOUT_MS  (10 * 1000)
#घोषणा MMC_EXTRACT_INDEX_FROM_ARG(x) ((x & 0x00FF0000) >> 16)
#घोषणा MMC_EXTRACT_VALUE_FROM_ARG(x) ((x & 0x0000FF00) >> 8)

#घोषणा mmc_req_rel_wr(req)	((req->cmd_flags & REQ_FUA) && \
				  (rq_data_dir(req) == WRITE))
अटल DEFINE_MUTEX(block_mutex);

/*
 * The शेषs come from config options but can be overriden by module
 * or bootarg options.
 */
अटल पूर्णांक perdev_minors = CONFIG_MMC_BLOCK_MINORS;

/*
 * We've only got one major, so number of mmcblk devices is
 * limited to (1 << 20) / number of minors per device.  It is also
 * limited by the MAX_DEVICES below.
 */
अटल पूर्णांक max_devices;

#घोषणा MAX_DEVICES 256

अटल DEFINE_IDA(mmc_blk_ida);
अटल DEFINE_IDA(mmc_rpmb_ida);

/*
 * There is one mmc_blk_data per slot.
 */
काष्ठा mmc_blk_data अणु
	काष्ठा device	*parent;
	काष्ठा gendisk	*disk;
	काष्ठा mmc_queue queue;
	काष्ठा list_head part;
	काष्ठा list_head rpmbs;

	अचिन्हित पूर्णांक	flags;
#घोषणा MMC_BLK_CMD23	(1 << 0)	/* Can करो SET_BLOCK_COUNT क्रम multiblock */
#घोषणा MMC_BLK_REL_WR	(1 << 1)	/* MMC Reliable ग_लिखो support */

	अचिन्हित पूर्णांक	usage;
	अचिन्हित पूर्णांक	पढ़ो_only;
	अचिन्हित पूर्णांक	part_type;
	अचिन्हित पूर्णांक	reset_करोne;
#घोषणा MMC_BLK_READ		BIT(0)
#घोषणा MMC_BLK_WRITE		BIT(1)
#घोषणा MMC_BLK_DISCARD		BIT(2)
#घोषणा MMC_BLK_SECDISCARD	BIT(3)
#घोषणा MMC_BLK_CQE_RECOVERY	BIT(4)

	/*
	 * Only set in मुख्य mmc_blk_data associated
	 * with mmc_card with dev_set_drvdata, and keeps
	 * track of the current selected device partition.
	 */
	अचिन्हित पूर्णांक	part_curr;
	काष्ठा device_attribute क्रमce_ro;
	काष्ठा device_attribute घातer_ro_lock;
	पूर्णांक	area_type;

	/* debugfs files (only in मुख्य mmc_blk_data) */
	काष्ठा dentry *status_dentry;
	काष्ठा dentry *ext_csd_dentry;
पूर्ण;

/* Device type क्रम RPMB अक्षरacter devices */
अटल dev_t mmc_rpmb_devt;

/* Bus type क्रम RPMB अक्षरacter devices */
अटल काष्ठा bus_type mmc_rpmb_bus_type = अणु
	.name = "mmc_rpmb",
पूर्ण;

/**
 * काष्ठा mmc_rpmb_data - special RPMB device type क्रम these areas
 * @dev: the device क्रम the RPMB area
 * @chrdev: अक्षरacter device क्रम the RPMB area
 * @id: unique device ID number
 * @part_index: partition index (0 on first)
 * @md: parent MMC block device
 * @node: list item, so we can put this device on a list
 */
काष्ठा mmc_rpmb_data अणु
	काष्ठा device dev;
	काष्ठा cdev chrdev;
	पूर्णांक id;
	अचिन्हित पूर्णांक part_index;
	काष्ठा mmc_blk_data *md;
	काष्ठा list_head node;
पूर्ण;

अटल DEFINE_MUTEX(खोलो_lock);

module_param(perdev_minors, पूर्णांक, 0444);
MODULE_PARM_DESC(perdev_minors, "Minors numbers to allocate per device");

अटल अंतरभूत पूर्णांक mmc_blk_part_चयन(काष्ठा mmc_card *card,
				      अचिन्हित पूर्णांक part_type);
अटल व्योम mmc_blk_rw_rq_prep(काष्ठा mmc_queue_req *mqrq,
			       काष्ठा mmc_card *card,
			       पूर्णांक disable_multi,
			       काष्ठा mmc_queue *mq);
अटल व्योम mmc_blk_hsq_req_करोne(काष्ठा mmc_request *mrq);

अटल काष्ठा mmc_blk_data *mmc_blk_get(काष्ठा gendisk *disk)
अणु
	काष्ठा mmc_blk_data *md;

	mutex_lock(&खोलो_lock);
	md = disk->निजी_data;
	अगर (md && md->usage == 0)
		md = शून्य;
	अगर (md)
		md->usage++;
	mutex_unlock(&खोलो_lock);

	वापस md;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_get_devidx(काष्ठा gendisk *disk)
अणु
	पूर्णांक devidx = disk->first_minor / perdev_minors;
	वापस devidx;
पूर्ण

अटल व्योम mmc_blk_put(काष्ठा mmc_blk_data *md)
अणु
	mutex_lock(&खोलो_lock);
	md->usage--;
	अगर (md->usage == 0) अणु
		पूर्णांक devidx = mmc_get_devidx(md->disk);
		blk_put_queue(md->queue.queue);
		ida_simple_हटाओ(&mmc_blk_ida, devidx);
		put_disk(md->disk);
		kमुक्त(md);
	पूर्ण
	mutex_unlock(&खोलो_lock);
पूर्ण

अटल sमाप_प्रकार घातer_ro_lock_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));
	काष्ठा mmc_card *card = md->queue.card;
	पूर्णांक locked = 0;

	अगर (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PERM_WP_EN)
		locked = 2;
	अन्यथा अगर (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PWR_WP_EN)
		locked = 1;

	ret = snम_लिखो(buf, PAGE_SIZE, "%d\n", locked);

	mmc_blk_put(md);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार घातer_ro_lock_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा mmc_blk_data *md, *part_md;
	काष्ठा mmc_queue *mq;
	काष्ठा request *req;
	अचिन्हित दीर्घ set;

	अगर (kम_से_अदीर्घ(buf, 0, &set))
		वापस -EINVAL;

	अगर (set != 1)
		वापस count;

	md = mmc_blk_get(dev_to_disk(dev));
	mq = &md->queue;

	/* Dispatch locking to the block layer */
	req = blk_get_request(mq->queue, REQ_OP_DRV_OUT, 0);
	अगर (IS_ERR(req)) अणु
		count = PTR_ERR(req);
		जाओ out_put;
	पूर्ण
	req_to_mmc_queue_req(req)->drv_op = MMC_DRV_OP_BOOT_WP;
	blk_execute_rq(शून्य, req, 0);
	ret = req_to_mmc_queue_req(req)->drv_op_result;
	blk_put_request(req);

	अगर (!ret) अणु
		pr_info("%s: Locking boot partition ro until next power on\n",
			md->disk->disk_name);
		set_disk_ro(md->disk, 1);

		list_क्रम_each_entry(part_md, &md->part, part)
			अगर (part_md->area_type == MMC_BLK_DATA_AREA_BOOT) अणु
				pr_info("%s: Locking boot partition ro until next power on\n", part_md->disk->disk_name);
				set_disk_ro(part_md->disk, 1);
			पूर्ण
	पूर्ण
out_put:
	mmc_blk_put(md);
	वापस count;
पूर्ण

अटल sमाप_प्रकार क्रमce_ro_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));

	ret = snम_लिखो(buf, PAGE_SIZE, "%d\n",
		       get_disk_ro(dev_to_disk(dev)) ^
		       md->पढ़ो_only);
	mmc_blk_put(md);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार क्रमce_ro_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अक्षर *end;
	काष्ठा mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));
	अचिन्हित दीर्घ set = simple_म_से_अदीर्घ(buf, &end, 0);
	अगर (end == buf) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	set_disk_ro(dev_to_disk(dev), set || md->पढ़ो_only);
	ret = count;
out:
	mmc_blk_put(md);
	वापस ret;
पूर्ण

अटल पूर्णांक mmc_blk_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा mmc_blk_data *md = mmc_blk_get(bdev->bd_disk);
	पूर्णांक ret = -ENXIO;

	mutex_lock(&block_mutex);
	अगर (md) अणु
		ret = 0;
		अगर ((mode & FMODE_WRITE) && md->पढ़ो_only) अणु
			mmc_blk_put(md);
			ret = -EROFS;
		पूर्ण
	पूर्ण
	mutex_unlock(&block_mutex);

	वापस ret;
पूर्ण

अटल व्योम mmc_blk_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा mmc_blk_data *md = disk->निजी_data;

	mutex_lock(&block_mutex);
	mmc_blk_put(md);
	mutex_unlock(&block_mutex);
पूर्ण

अटल पूर्णांक
mmc_blk_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	geo->cylinders = get_capacity(bdev->bd_disk) / (4 * 16);
	geo->heads = 4;
	geo->sectors = 16;
	वापस 0;
पूर्ण

काष्ठा mmc_blk_ioc_data अणु
	काष्ठा mmc_ioc_cmd ic;
	अचिन्हित अक्षर *buf;
	u64 buf_bytes;
	काष्ठा mmc_rpmb_data *rpmb;
पूर्ण;

अटल काष्ठा mmc_blk_ioc_data *mmc_blk_ioctl_copy_from_user(
	काष्ठा mmc_ioc_cmd __user *user)
अणु
	काष्ठा mmc_blk_ioc_data *idata;
	पूर्णांक err;

	idata = kदो_स्मृति(माप(*idata), GFP_KERNEL);
	अगर (!idata) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(&idata->ic, user, माप(idata->ic))) अणु
		err = -EFAULT;
		जाओ idata_err;
	पूर्ण

	idata->buf_bytes = (u64) idata->ic.blksz * idata->ic.blocks;
	अगर (idata->buf_bytes > MMC_IOC_MAX_BYTES) अणु
		err = -EOVERFLOW;
		जाओ idata_err;
	पूर्ण

	अगर (!idata->buf_bytes) अणु
		idata->buf = शून्य;
		वापस idata;
	पूर्ण

	idata->buf = memdup_user((व्योम __user *)(अचिन्हित दीर्घ)
				 idata->ic.data_ptr, idata->buf_bytes);
	अगर (IS_ERR(idata->buf)) अणु
		err = PTR_ERR(idata->buf);
		जाओ idata_err;
	पूर्ण

	वापस idata;

idata_err:
	kमुक्त(idata);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक mmc_blk_ioctl_copy_to_user(काष्ठा mmc_ioc_cmd __user *ic_ptr,
				      काष्ठा mmc_blk_ioc_data *idata)
अणु
	काष्ठा mmc_ioc_cmd *ic = &idata->ic;

	अगर (copy_to_user(&(ic_ptr->response), ic->response,
			 माप(ic->response)))
		वापस -EFAULT;

	अगर (!idata->ic.ग_लिखो_flag) अणु
		अगर (copy_to_user((व्योम __user *)(अचिन्हित दीर्घ)ic->data_ptr,
				 idata->buf, idata->buf_bytes))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक card_busy_detect(काष्ठा mmc_card *card, अचिन्हित पूर्णांक समयout_ms,
			    u32 *resp_errs)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);
	पूर्णांक err = 0;
	u32 status;

	करो अणु
		bool करोne = समय_after(jअगरfies, समयout);

		err = __mmc_send_status(card, &status, 5);
		अगर (err) अणु
			dev_err(mmc_dev(card->host),
				"error %d requesting status\n", err);
			वापस err;
		पूर्ण

		/* Accumulate any response error bits seen */
		अगर (resp_errs)
			*resp_errs |= status;

		/*
		 * Timeout अगर the device never becomes पढ़ोy क्रम data and never
		 * leaves the program state.
		 */
		अगर (करोne) अणु
			dev_err(mmc_dev(card->host),
				"Card stuck in wrong state! %s status: %#x\n",
				 __func__, status);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण जबतक (!mmc_पढ़ोy_क्रम_data(status));

	वापस err;
पूर्ण

अटल पूर्णांक __mmc_blk_ioctl_cmd(काष्ठा mmc_card *card, काष्ठा mmc_blk_data *md,
			       काष्ठा mmc_blk_ioc_data *idata)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण, sbc = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा scatterlist sg;
	पूर्णांक err;
	अचिन्हित पूर्णांक target_part;

	अगर (!card || !md || !idata)
		वापस -EINVAL;

	/*
	 * The RPMB accesses comes in from the अक्षरacter device, so we
	 * need to target these explicitly. Else we just target the
	 * partition type क्रम the block device the ioctl() was issued
	 * on.
	 */
	अगर (idata->rpmb) अणु
		/* Support multiple RPMB partitions */
		target_part = idata->rpmb->part_index;
		target_part |= EXT_CSD_PART_CONFIG_ACC_RPMB;
	पूर्ण अन्यथा अणु
		target_part = md->part_type;
	पूर्ण

	cmd.opcode = idata->ic.opcode;
	cmd.arg = idata->ic.arg;
	cmd.flags = idata->ic.flags;

	अगर (idata->buf_bytes) अणु
		data.sg = &sg;
		data.sg_len = 1;
		data.blksz = idata->ic.blksz;
		data.blocks = idata->ic.blocks;

		sg_init_one(data.sg, idata->buf, idata->buf_bytes);

		अगर (idata->ic.ग_लिखो_flag)
			data.flags = MMC_DATA_WRITE;
		अन्यथा
			data.flags = MMC_DATA_READ;

		/* data.flags must alपढ़ोy be set beक्रमe करोing this. */
		mmc_set_data_समयout(&data, card);

		/* Allow overriding the समयout_ns क्रम empirical tuning. */
		अगर (idata->ic.data_समयout_ns)
			data.समयout_ns = idata->ic.data_समयout_ns;

		अगर ((cmd.flags & MMC_RSP_R1B) == MMC_RSP_R1B) अणु
			/*
			 * Pretend this is a data transfer and rely on the
			 * host driver to compute समयout.  When all host
			 * drivers support cmd.cmd_समयout क्रम R1B, this
			 * can be changed to:
			 *
			 *     mrq.data = शून्य;
			 *     cmd.cmd_समयout = idata->ic.cmd_समयout_ms;
			 */
			data.समयout_ns = idata->ic.cmd_समयout_ms * 1000000;
		पूर्ण

		mrq.data = &data;
	पूर्ण

	mrq.cmd = &cmd;

	err = mmc_blk_part_चयन(card, target_part);
	अगर (err)
		वापस err;

	अगर (idata->ic.is_acmd) अणु
		err = mmc_app_cmd(card->host, card);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (idata->rpmb) अणु
		sbc.opcode = MMC_SET_BLOCK_COUNT;
		/*
		 * We करोn't करो any blockcount validation because the max size
		 * may be increased by a future standard. We just copy the
		 * 'Reliable Write' bit here.
		 */
		sbc.arg = data.blocks | (idata->ic.ग_लिखो_flag & BIT(31));
		sbc.flags = MMC_RSP_R1 | MMC_CMD_AC;
		mrq.sbc = &sbc;
	पूर्ण

	अगर ((MMC_EXTRACT_INDEX_FROM_ARG(cmd.arg) == EXT_CSD_SANITIZE_START) &&
	    (cmd.opcode == MMC_SWITCH))
		वापस mmc_sanitize(card, idata->ic.cmd_समयout_ms);

	mmc_रुको_क्रम_req(card->host, &mrq);

	अगर (cmd.error) अणु
		dev_err(mmc_dev(card->host), "%s: cmd error %d\n",
						__func__, cmd.error);
		वापस cmd.error;
	पूर्ण
	अगर (data.error) अणु
		dev_err(mmc_dev(card->host), "%s: data error %d\n",
						__func__, data.error);
		वापस data.error;
	पूर्ण

	/*
	 * Make sure the cache of the PARTITION_CONFIG रेजिस्टर and
	 * PARTITION_ACCESS bits is updated in हाल the ioctl ext_csd ग_लिखो
	 * changed it successfully.
	 */
	अगर ((MMC_EXTRACT_INDEX_FROM_ARG(cmd.arg) == EXT_CSD_PART_CONFIG) &&
	    (cmd.opcode == MMC_SWITCH)) अणु
		काष्ठा mmc_blk_data *मुख्य_md = dev_get_drvdata(&card->dev);
		u8 value = MMC_EXTRACT_VALUE_FROM_ARG(cmd.arg);

		/*
		 * Update cache so the next mmc_blk_part_चयन call operates
		 * on up-to-date data.
		 */
		card->ext_csd.part_config = value;
		मुख्य_md->part_curr = value & EXT_CSD_PART_CONFIG_ACC_MASK;
	पूर्ण

	/*
	 * Make sure to update CACHE_CTRL in हाल it was changed. The cache
	 * will get turned back on अगर the card is re-initialized, e.g.
	 * suspend/resume or hw reset in recovery.
	 */
	अगर ((MMC_EXTRACT_INDEX_FROM_ARG(cmd.arg) == EXT_CSD_CACHE_CTRL) &&
	    (cmd.opcode == MMC_SWITCH)) अणु
		u8 value = MMC_EXTRACT_VALUE_FROM_ARG(cmd.arg) & 1;

		card->ext_csd.cache_ctrl = value;
	पूर्ण

	/*
	 * According to the SD specs, some commands require a delay after
	 * issuing the command.
	 */
	अगर (idata->ic.postsleep_min_us)
		usleep_range(idata->ic.postsleep_min_us, idata->ic.postsleep_max_us);

	स_नकल(&(idata->ic.response), cmd.resp, माप(cmd.resp));

	अगर (idata->rpmb || (cmd.flags & MMC_RSP_R1B) == MMC_RSP_R1B) अणु
		/*
		 * Ensure RPMB/R1B command has completed by polling CMD13
		 * "Send Status".
		 */
		err = card_busy_detect(card, MMC_BLK_TIMEOUT_MS, शून्य);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mmc_blk_ioctl_cmd(काष्ठा mmc_blk_data *md,
			     काष्ठा mmc_ioc_cmd __user *ic_ptr,
			     काष्ठा mmc_rpmb_data *rpmb)
अणु
	काष्ठा mmc_blk_ioc_data *idata;
	काष्ठा mmc_blk_ioc_data *idatas[1];
	काष्ठा mmc_queue *mq;
	काष्ठा mmc_card *card;
	पूर्णांक err = 0, ioc_err = 0;
	काष्ठा request *req;

	idata = mmc_blk_ioctl_copy_from_user(ic_ptr);
	अगर (IS_ERR(idata))
		वापस PTR_ERR(idata);
	/* This will be शून्य on non-RPMB ioctl():s */
	idata->rpmb = rpmb;

	card = md->queue.card;
	अगर (IS_ERR(card)) अणु
		err = PTR_ERR(card);
		जाओ cmd_करोne;
	पूर्ण

	/*
	 * Dispatch the ioctl() पूर्णांकo the block request queue.
	 */
	mq = &md->queue;
	req = blk_get_request(mq->queue,
		idata->ic.ग_लिखो_flag ? REQ_OP_DRV_OUT : REQ_OP_DRV_IN, 0);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ cmd_करोne;
	पूर्ण
	idatas[0] = idata;
	req_to_mmc_queue_req(req)->drv_op =
		rpmb ? MMC_DRV_OP_IOCTL_RPMB : MMC_DRV_OP_IOCTL;
	req_to_mmc_queue_req(req)->drv_op_data = idatas;
	req_to_mmc_queue_req(req)->ioc_count = 1;
	blk_execute_rq(शून्य, req, 0);
	ioc_err = req_to_mmc_queue_req(req)->drv_op_result;
	err = mmc_blk_ioctl_copy_to_user(ic_ptr, idata);
	blk_put_request(req);

cmd_करोne:
	kमुक्त(idata->buf);
	kमुक्त(idata);
	वापस ioc_err ? ioc_err : err;
पूर्ण

अटल पूर्णांक mmc_blk_ioctl_multi_cmd(काष्ठा mmc_blk_data *md,
				   काष्ठा mmc_ioc_multi_cmd __user *user,
				   काष्ठा mmc_rpmb_data *rpmb)
अणु
	काष्ठा mmc_blk_ioc_data **idata = शून्य;
	काष्ठा mmc_ioc_cmd __user *cmds = user->cmds;
	काष्ठा mmc_card *card;
	काष्ठा mmc_queue *mq;
	पूर्णांक i, err = 0, ioc_err = 0;
	__u64 num_of_cmds;
	काष्ठा request *req;

	अगर (copy_from_user(&num_of_cmds, &user->num_of_cmds,
			   माप(num_of_cmds)))
		वापस -EFAULT;

	अगर (!num_of_cmds)
		वापस 0;

	अगर (num_of_cmds > MMC_IOC_MAX_CMDS)
		वापस -EINVAL;

	idata = kसुस्मृति(num_of_cmds, माप(*idata), GFP_KERNEL);
	अगर (!idata)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_of_cmds; i++) अणु
		idata[i] = mmc_blk_ioctl_copy_from_user(&cmds[i]);
		अगर (IS_ERR(idata[i])) अणु
			err = PTR_ERR(idata[i]);
			num_of_cmds = i;
			जाओ cmd_err;
		पूर्ण
		/* This will be शून्य on non-RPMB ioctl():s */
		idata[i]->rpmb = rpmb;
	पूर्ण

	card = md->queue.card;
	अगर (IS_ERR(card)) अणु
		err = PTR_ERR(card);
		जाओ cmd_err;
	पूर्ण


	/*
	 * Dispatch the ioctl()s पूर्णांकo the block request queue.
	 */
	mq = &md->queue;
	req = blk_get_request(mq->queue,
		idata[0]->ic.ग_लिखो_flag ? REQ_OP_DRV_OUT : REQ_OP_DRV_IN, 0);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ cmd_err;
	पूर्ण
	req_to_mmc_queue_req(req)->drv_op =
		rpmb ? MMC_DRV_OP_IOCTL_RPMB : MMC_DRV_OP_IOCTL;
	req_to_mmc_queue_req(req)->drv_op_data = idata;
	req_to_mmc_queue_req(req)->ioc_count = num_of_cmds;
	blk_execute_rq(शून्य, req, 0);
	ioc_err = req_to_mmc_queue_req(req)->drv_op_result;

	/* copy to user अगर data and response */
	क्रम (i = 0; i < num_of_cmds && !err; i++)
		err = mmc_blk_ioctl_copy_to_user(&cmds[i], idata[i]);

	blk_put_request(req);

cmd_err:
	क्रम (i = 0; i < num_of_cmds; i++) अणु
		kमुक्त(idata[i]->buf);
		kमुक्त(idata[i]);
	पूर्ण
	kमुक्त(idata);
	वापस ioc_err ? ioc_err : err;
पूर्ण

अटल पूर्णांक mmc_blk_check_blkdev(काष्ठा block_device *bdev)
अणु
	/*
	 * The caller must have CAP_SYS_RAWIO, and must be calling this on the
	 * whole block device, not on a partition.  This prevents overspray
	 * between sibling partitions.
	 */
	अगर (!capable(CAP_SYS_RAWIO) || bdev_is_partition(bdev))
		वापस -EPERM;
	वापस 0;
पूर्ण

अटल पूर्णांक mmc_blk_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
	अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mmc_blk_data *md;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल MMC_IOC_CMD:
		ret = mmc_blk_check_blkdev(bdev);
		अगर (ret)
			वापस ret;
		md = mmc_blk_get(bdev->bd_disk);
		अगर (!md)
			वापस -EINVAL;
		ret = mmc_blk_ioctl_cmd(md,
					(काष्ठा mmc_ioc_cmd __user *)arg,
					शून्य);
		mmc_blk_put(md);
		वापस ret;
	हाल MMC_IOC_MULTI_CMD:
		ret = mmc_blk_check_blkdev(bdev);
		अगर (ret)
			वापस ret;
		md = mmc_blk_get(bdev->bd_disk);
		अगर (!md)
			वापस -EINVAL;
		ret = mmc_blk_ioctl_multi_cmd(md,
					(काष्ठा mmc_ioc_multi_cmd __user *)arg,
					शून्य);
		mmc_blk_put(md);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक mmc_blk_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
	अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस mmc_blk_ioctl(bdev, mode, cmd, (अचिन्हित दीर्घ) compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा block_device_operations mmc_bकरोps = अणु
	.खोलो			= mmc_blk_खोलो,
	.release		= mmc_blk_release,
	.getgeo			= mmc_blk_getgeo,
	.owner			= THIS_MODULE,
	.ioctl			= mmc_blk_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= mmc_blk_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mmc_blk_part_चयन_pre(काष्ठा mmc_card *card,
				   अचिन्हित पूर्णांक part_type)
अणु
	पूर्णांक ret = 0;

	अगर (part_type == EXT_CSD_PART_CONFIG_ACC_RPMB) अणु
		अगर (card->ext_csd.cmdq_en) अणु
			ret = mmc_cmdq_disable(card);
			अगर (ret)
				वापस ret;
		पूर्ण
		mmc_retune_छोड़ो(card->host);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mmc_blk_part_चयन_post(काष्ठा mmc_card *card,
				    अचिन्हित पूर्णांक part_type)
अणु
	पूर्णांक ret = 0;

	अगर (part_type == EXT_CSD_PART_CONFIG_ACC_RPMB) अणु
		mmc_retune_unछोड़ो(card->host);
		अगर (card->reenable_cmdq && !card->ext_csd.cmdq_en)
			ret = mmc_cmdq_enable(card);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_blk_part_चयन(काष्ठा mmc_card *card,
				      अचिन्हित पूर्णांक part_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा mmc_blk_data *मुख्य_md = dev_get_drvdata(&card->dev);

	अगर (मुख्य_md->part_curr == part_type)
		वापस 0;

	अगर (mmc_card_mmc(card)) अणु
		u8 part_config = card->ext_csd.part_config;

		ret = mmc_blk_part_चयन_pre(card, part_type);
		अगर (ret)
			वापस ret;

		part_config &= ~EXT_CSD_PART_CONFIG_ACC_MASK;
		part_config |= part_type;

		ret = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_PART_CONFIG, part_config,
				 card->ext_csd.part_समय);
		अगर (ret) अणु
			mmc_blk_part_चयन_post(card, part_type);
			वापस ret;
		पूर्ण

		card->ext_csd.part_config = part_config;

		ret = mmc_blk_part_चयन_post(card, मुख्य_md->part_curr);
	पूर्ण

	मुख्य_md->part_curr = part_type;
	वापस ret;
पूर्ण

अटल पूर्णांक mmc_sd_num_wr_blocks(काष्ठा mmc_card *card, u32 *written_blocks)
अणु
	पूर्णांक err;
	u32 result;
	__be32 *blocks;

	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;

	काष्ठा scatterlist sg;

	cmd.opcode = MMC_APP_CMD;
	cmd.arg = card->rca << 16;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_रुको_क्रम_cmd(card->host, &cmd, 0);
	अगर (err)
		वापस err;
	अगर (!mmc_host_is_spi(card->host) && !(cmd.resp[0] & R1_APP_CMD))
		वापस -EIO;

	स_रखो(&cmd, 0, माप(काष्ठा mmc_command));

	cmd.opcode = SD_APP_SEND_NUM_WR_BLKS;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 4;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;
	mmc_set_data_समयout(&data, card);

	mrq.cmd = &cmd;
	mrq.data = &data;

	blocks = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!blocks)
		वापस -ENOMEM;

	sg_init_one(&sg, blocks, 4);

	mmc_रुको_क्रम_req(card->host, &mrq);

	result = ntohl(*blocks);
	kमुक्त(blocks);

	अगर (cmd.error || data.error)
		वापस -EIO;

	*written_blocks = result;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mmc_blk_घड़ी_khz(काष्ठा mmc_host *host)
अणु
	अगर (host->actual_घड़ी)
		वापस host->actual_घड़ी / 1000;

	/* Clock may be subject to a भागisor, fudge it by a factor of 2. */
	अगर (host->ios.घड़ी)
		वापस host->ios.घड़ी / 2000;

	/* How can there be no घड़ी */
	WARN_ON_ONCE(1);
	वापस 100; /* 100 kHz is minimum possible value */
पूर्ण

अटल अचिन्हित पूर्णांक mmc_blk_data_समयout_ms(काष्ठा mmc_host *host,
					    काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक ms = DIV_ROUND_UP(data->समयout_ns, 1000000);
	अचिन्हित पूर्णांक khz;

	अगर (data->समयout_clks) अणु
		khz = mmc_blk_घड़ी_khz(host);
		ms += DIV_ROUND_UP(data->समयout_clks, khz);
	पूर्ण

	वापस ms;
पूर्ण

अटल पूर्णांक mmc_blk_reset(काष्ठा mmc_blk_data *md, काष्ठा mmc_host *host,
			 पूर्णांक type)
अणु
	पूर्णांक err;

	अगर (md->reset_करोne & type)
		वापस -EEXIST;

	md->reset_करोne |= type;
	err = mmc_hw_reset(host);
	/* Ensure we चयन back to the correct partition */
	अगर (err) अणु
		काष्ठा mmc_blk_data *मुख्य_md =
			dev_get_drvdata(&host->card->dev);
		पूर्णांक part_err;

		मुख्य_md->part_curr = मुख्य_md->part_type;
		part_err = mmc_blk_part_चयन(host->card, md->part_type);
		अगर (part_err) अणु
			/*
			 * We have failed to get back पूर्णांकo the correct
			 * partition, so we need to पात the whole request.
			 */
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल अंतरभूत व्योम mmc_blk_reset_success(काष्ठा mmc_blk_data *md, पूर्णांक type)
अणु
	md->reset_करोne &= ~type;
पूर्ण

/*
 * The non-block commands come back from the block layer after it queued it and
 * processed it with all other requests and then they get issued in this
 * function.
 */
अटल व्योम mmc_blk_issue_drv_op(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mq_rq;
	काष्ठा mmc_card *card = mq->card;
	काष्ठा mmc_blk_data *md = mq->blkdata;
	काष्ठा mmc_blk_ioc_data **idata;
	bool rpmb_ioctl;
	u8 **ext_csd;
	u32 status;
	पूर्णांक ret;
	पूर्णांक i;

	mq_rq = req_to_mmc_queue_req(req);
	rpmb_ioctl = (mq_rq->drv_op == MMC_DRV_OP_IOCTL_RPMB);

	चयन (mq_rq->drv_op) अणु
	हाल MMC_DRV_OP_IOCTL:
	हाल MMC_DRV_OP_IOCTL_RPMB:
		idata = mq_rq->drv_op_data;
		क्रम (i = 0, ret = 0; i < mq_rq->ioc_count; i++) अणु
			ret = __mmc_blk_ioctl_cmd(card, md, idata[i]);
			अगर (ret)
				अवरोध;
		पूर्ण
		/* Always चयन back to मुख्य area after RPMB access */
		अगर (rpmb_ioctl)
			mmc_blk_part_चयन(card, 0);
		अवरोध;
	हाल MMC_DRV_OP_BOOT_WP:
		ret = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BOOT_WP,
				 card->ext_csd.boot_ro_lock |
				 EXT_CSD_BOOT_WP_B_PWR_WP_EN,
				 card->ext_csd.part_समय);
		अगर (ret)
			pr_err("%s: Locking boot partition ro until next power on failed: %d\n",
			       md->disk->disk_name, ret);
		अन्यथा
			card->ext_csd.boot_ro_lock |=
				EXT_CSD_BOOT_WP_B_PWR_WP_EN;
		अवरोध;
	हाल MMC_DRV_OP_GET_CARD_STATUS:
		ret = mmc_send_status(card, &status);
		अगर (!ret)
			ret = status;
		अवरोध;
	हाल MMC_DRV_OP_GET_EXT_CSD:
		ext_csd = mq_rq->drv_op_data;
		ret = mmc_get_ext_csd(card, ext_csd);
		अवरोध;
	शेष:
		pr_err("%s: unknown driver specific operation\n",
		       md->disk->disk_name);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	mq_rq->drv_op_result = ret;
	blk_mq_end_request(req, ret ? BLK_STS_IOERR : BLK_STS_OK);
पूर्ण

अटल व्योम mmc_blk_issue_discard_rq(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_blk_data *md = mq->blkdata;
	काष्ठा mmc_card *card = md->queue.card;
	अचिन्हित पूर्णांक from, nr;
	पूर्णांक err = 0, type = MMC_BLK_DISCARD;
	blk_status_t status = BLK_STS_OK;

	अगर (!mmc_can_erase(card)) अणु
		status = BLK_STS_NOTSUPP;
		जाओ fail;
	पूर्ण

	from = blk_rq_pos(req);
	nr = blk_rq_sectors(req);

	करो अणु
		err = 0;
		अगर (card->quirks & MMC_QUIRK_Iन_अंकD_CMD38) अणु
			err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
					 Iन_अंकD_CMD38_ARG_EXT_CSD,
					 card->erase_arg == MMC_TRIM_ARG ?
					 Iन_अंकD_CMD38_ARG_TRIM :
					 Iन_अंकD_CMD38_ARG_ERASE,
					 card->ext_csd.generic_cmd6_समय);
		पूर्ण
		अगर (!err)
			err = mmc_erase(card, from, nr, card->erase_arg);
	पूर्ण जबतक (err == -EIO && !mmc_blk_reset(md, card->host, type));
	अगर (err)
		status = BLK_STS_IOERR;
	अन्यथा
		mmc_blk_reset_success(md, type);
fail:
	blk_mq_end_request(req, status);
पूर्ण

अटल व्योम mmc_blk_issue_secdiscard_rq(काष्ठा mmc_queue *mq,
				       काष्ठा request *req)
अणु
	काष्ठा mmc_blk_data *md = mq->blkdata;
	काष्ठा mmc_card *card = md->queue.card;
	अचिन्हित पूर्णांक from, nr, arg;
	पूर्णांक err = 0, type = MMC_BLK_SECDISCARD;
	blk_status_t status = BLK_STS_OK;

	अगर (!(mmc_can_secure_erase_trim(card))) अणु
		status = BLK_STS_NOTSUPP;
		जाओ out;
	पूर्ण

	from = blk_rq_pos(req);
	nr = blk_rq_sectors(req);

	अगर (mmc_can_trim(card) && !mmc_erase_group_aligned(card, from, nr))
		arg = MMC_SECURE_TRIM1_ARG;
	अन्यथा
		arg = MMC_SECURE_ERASE_ARG;

retry:
	अगर (card->quirks & MMC_QUIRK_Iन_अंकD_CMD38) अणु
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				 Iन_अंकD_CMD38_ARG_EXT_CSD,
				 arg == MMC_SECURE_TRIM1_ARG ?
				 Iन_अंकD_CMD38_ARG_SECTRIM1 :
				 Iन_अंकD_CMD38_ARG_SECERASE,
				 card->ext_csd.generic_cmd6_समय);
		अगर (err)
			जाओ out_retry;
	पूर्ण

	err = mmc_erase(card, from, nr, arg);
	अगर (err == -EIO)
		जाओ out_retry;
	अगर (err) अणु
		status = BLK_STS_IOERR;
		जाओ out;
	पूर्ण

	अगर (arg == MMC_SECURE_TRIM1_ARG) अणु
		अगर (card->quirks & MMC_QUIRK_Iन_अंकD_CMD38) अणु
			err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
					 Iन_अंकD_CMD38_ARG_EXT_CSD,
					 Iन_अंकD_CMD38_ARG_SECTRIM2,
					 card->ext_csd.generic_cmd6_समय);
			अगर (err)
				जाओ out_retry;
		पूर्ण

		err = mmc_erase(card, from, nr, MMC_SECURE_TRIM2_ARG);
		अगर (err == -EIO)
			जाओ out_retry;
		अगर (err) अणु
			status = BLK_STS_IOERR;
			जाओ out;
		पूर्ण
	पूर्ण

out_retry:
	अगर (err && !mmc_blk_reset(md, card->host, type))
		जाओ retry;
	अगर (!err)
		mmc_blk_reset_success(md, type);
out:
	blk_mq_end_request(req, status);
पूर्ण

अटल व्योम mmc_blk_issue_flush(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_blk_data *md = mq->blkdata;
	काष्ठा mmc_card *card = md->queue.card;
	पूर्णांक ret = 0;

	ret = mmc_flush_cache(card);
	blk_mq_end_request(req, ret ? BLK_STS_IOERR : BLK_STS_OK);
पूर्ण

/*
 * Reक्रमmat current ग_लिखो as a reliable ग_लिखो, supporting
 * both legacy and the enhanced reliable ग_लिखो MMC cards.
 * In each transfer we'll handle only as much as a single
 * reliable ग_लिखो can handle, thus finish the request in
 * partial completions.
 */
अटल अंतरभूत व्योम mmc_apply_rel_rw(काष्ठा mmc_blk_request *brq,
				    काष्ठा mmc_card *card,
				    काष्ठा request *req)
अणु
	अगर (!(card->ext_csd.rel_param & EXT_CSD_WR_REL_PARAM_EN)) अणु
		/* Legacy mode imposes restrictions on transfers. */
		अगर (!IS_ALIGNED(blk_rq_pos(req), card->ext_csd.rel_sectors))
			brq->data.blocks = 1;

		अगर (brq->data.blocks > card->ext_csd.rel_sectors)
			brq->data.blocks = card->ext_csd.rel_sectors;
		अन्यथा अगर (brq->data.blocks < card->ext_csd.rel_sectors)
			brq->data.blocks = 1;
	पूर्ण
पूर्ण

#घोषणा CMD_ERRORS_EXCL_OOR						\
	(R1_ADDRESS_ERROR |	/* Misaligned address */		\
	 R1_BLOCK_LEN_ERROR |	/* Transferred block length incorrect */\
	 R1_WP_VIOLATION |	/* Tried to ग_लिखो to रक्षित block */	\
	 R1_CARD_ECC_FAILED |	/* Card ECC failed */			\
	 R1_CC_ERROR |		/* Card controller error */		\
	 R1_ERROR)		/* General/unknown error */

#घोषणा CMD_ERRORS							\
	(CMD_ERRORS_EXCL_OOR |						\
	 R1_OUT_OF_RANGE)	/* Command argument out of range */	\

अटल व्योम mmc_blk_eval_resp_error(काष्ठा mmc_blk_request *brq)
अणु
	u32 val;

	/*
	 * Per the SD specअगरication(physical layer version 4.10)[1],
	 * section 4.3.3, it explicitly states that "When the last
	 * block of user area is पढ़ो using CMD18, the host should
	 * ignore OUT_OF_RANGE error that may occur even the sequence
	 * is correct". And JESD84-B51 क्रम eMMC also has a similar
	 * statement on section 6.8.3.
	 *
	 * Multiple block पढ़ो/ग_लिखो could be करोne by either predefined
	 * method, namely CMD23, or खोलो-ending mode. For खोलो-ending mode,
	 * we should ignore the OUT_OF_RANGE error as it's normal behaviour.
	 *
	 * However the spec[1] करोesn't tell us whether we should also
	 * ignore that क्रम predefined method. But per the spec[1], section
	 * 4.15 Set Block Count Command, it says"If illegal block count
	 * is set, out of range error will be indicated during पढ़ो/ग_लिखो
	 * operation (For example, data transfer is stopped at user area
	 * boundary)." In another word, we could expect a out of range error
	 * in the response क्रम the following CMD18/25. And अगर argument of
	 * CMD23 + the argument of CMD18/25 exceed the max number of blocks,
	 * we could also expect to get a -ETIMEDOUT or any error number from
	 * the host drivers due to missing data response(क्रम ग_लिखो)/data(क्रम
	 * पढ़ो), as the cards will stop the data transfer by itself per the
	 * spec. So we only need to check R1_OUT_OF_RANGE क्रम खोलो-ending mode.
	 */

	अगर (!brq->stop.error) अणु
		bool oor_with_खोलो_end;
		/* If there is no error yet, check R1 response */

		val = brq->stop.resp[0] & CMD_ERRORS;
		oor_with_खोलो_end = val & R1_OUT_OF_RANGE && !brq->mrq.sbc;

		अगर (val && !oor_with_खोलो_end)
			brq->stop.error = -EIO;
	पूर्ण
पूर्ण

अटल व्योम mmc_blk_data_prep(काष्ठा mmc_queue *mq, काष्ठा mmc_queue_req *mqrq,
			      पूर्णांक disable_multi, bool *करो_rel_wr_p,
			      bool *करो_data_tag_p)
अणु
	काष्ठा mmc_blk_data *md = mq->blkdata;
	काष्ठा mmc_card *card = md->queue.card;
	काष्ठा mmc_blk_request *brq = &mqrq->brq;
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);
	bool करो_rel_wr, करो_data_tag;

	/*
	 * Reliable ग_लिखोs are used to implement Forced Unit Access and
	 * are supported only on MMCs.
	 */
	करो_rel_wr = (req->cmd_flags & REQ_FUA) &&
		    rq_data_dir(req) == WRITE &&
		    (md->flags & MMC_BLK_REL_WR);

	स_रखो(brq, 0, माप(काष्ठा mmc_blk_request));

	mmc_crypto_prepare_req(mqrq);

	brq->mrq.data = &brq->data;
	brq->mrq.tag = req->tag;

	brq->stop.opcode = MMC_STOP_TRANSMISSION;
	brq->stop.arg = 0;

	अगर (rq_data_dir(req) == READ) अणु
		brq->data.flags = MMC_DATA_READ;
		brq->stop.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	पूर्ण अन्यथा अणु
		brq->data.flags = MMC_DATA_WRITE;
		brq->stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	पूर्ण

	brq->data.blksz = 512;
	brq->data.blocks = blk_rq_sectors(req);
	brq->data.blk_addr = blk_rq_pos(req);

	/*
	 * The command queue supports 2 priorities: "high" (1) and "simple" (0).
	 * The eMMC will give "high" priority tasks priority over "simple"
	 * priority tasks. Here we always set "simple" priority by not setting
	 * MMC_DATA_PRIO.
	 */

	/*
	 * The block layer करोesn't support all sector count
	 * restrictions, so we need to be prepared क्रम too big
	 * requests.
	 */
	अगर (brq->data.blocks > card->host->max_blk_count)
		brq->data.blocks = card->host->max_blk_count;

	अगर (brq->data.blocks > 1) अणु
		/*
		 * Some SD cards in SPI mode वापस a CRC error or even lock up
		 * completely when trying to पढ़ो the last block using a
		 * multiblock पढ़ो command.
		 */
		अगर (mmc_host_is_spi(card->host) && (rq_data_dir(req) == READ) &&
		    (blk_rq_pos(req) + blk_rq_sectors(req) ==
		     get_capacity(md->disk)))
			brq->data.blocks--;

		/*
		 * After a पढ़ो error, we reकरो the request one sector
		 * at a समय in order to accurately determine which
		 * sectors can be पढ़ो successfully.
		 */
		अगर (disable_multi)
			brq->data.blocks = 1;

		/*
		 * Some controllers have HW issues जबतक operating
		 * in multiple I/O mode
		 */
		अगर (card->host->ops->multi_io_quirk)
			brq->data.blocks = card->host->ops->multi_io_quirk(card,
						(rq_data_dir(req) == READ) ?
						MMC_DATA_READ : MMC_DATA_WRITE,
						brq->data.blocks);
	पूर्ण

	अगर (करो_rel_wr) अणु
		mmc_apply_rel_rw(brq, card, req);
		brq->data.flags |= MMC_DATA_REL_WR;
	पूर्ण

	/*
	 * Data tag is used only during writing meta data to speed
	 * up ग_लिखो and any subsequent पढ़ो of this meta data
	 */
	करो_data_tag = card->ext_csd.data_tag_unit_size &&
		      (req->cmd_flags & REQ_META) &&
		      (rq_data_dir(req) == WRITE) &&
		      ((brq->data.blocks * brq->data.blksz) >=
		       card->ext_csd.data_tag_unit_size);

	अगर (करो_data_tag)
		brq->data.flags |= MMC_DATA_DAT_TAG;

	mmc_set_data_समयout(&brq->data, card);

	brq->data.sg = mqrq->sg;
	brq->data.sg_len = mmc_queue_map_sg(mq, mqrq);

	/*
	 * Adjust the sg list so it is the same size as the
	 * request.
	 */
	अगर (brq->data.blocks != blk_rq_sectors(req)) अणु
		पूर्णांक i, data_size = brq->data.blocks << 9;
		काष्ठा scatterlist *sg;

		क्रम_each_sg(brq->data.sg, sg, brq->data.sg_len, i) अणु
			data_size -= sg->length;
			अगर (data_size <= 0) अणु
				sg->length += data_size;
				i++;
				अवरोध;
			पूर्ण
		पूर्ण
		brq->data.sg_len = i;
	पूर्ण

	अगर (करो_rel_wr_p)
		*करो_rel_wr_p = करो_rel_wr;

	अगर (करो_data_tag_p)
		*करो_data_tag_p = करो_data_tag;
पूर्ण

#घोषणा MMC_CQE_RETRIES 2

अटल व्योम mmc_blk_cqe_complete_rq(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_request *mrq = &mqrq->brq.mrq;
	काष्ठा request_queue *q = req->q;
	काष्ठा mmc_host *host = mq->card->host;
	क्रमागत mmc_issue_type issue_type = mmc_issue_type(mq, req);
	अचिन्हित दीर्घ flags;
	bool put_card;
	पूर्णांक err;

	mmc_cqe_post_req(host, mrq);

	अगर (mrq->cmd && mrq->cmd->error)
		err = mrq->cmd->error;
	अन्यथा अगर (mrq->data && mrq->data->error)
		err = mrq->data->error;
	अन्यथा
		err = 0;

	अगर (err) अणु
		अगर (mqrq->retries++ < MMC_CQE_RETRIES)
			blk_mq_requeue_request(req, true);
		अन्यथा
			blk_mq_end_request(req, BLK_STS_IOERR);
	पूर्ण अन्यथा अगर (mrq->data) अणु
		अगर (blk_update_request(req, BLK_STS_OK, mrq->data->bytes_xfered))
			blk_mq_requeue_request(req, true);
		अन्यथा
			__blk_mq_end_request(req, BLK_STS_OK);
	पूर्ण अन्यथा अणु
		blk_mq_end_request(req, BLK_STS_OK);
	पूर्ण

	spin_lock_irqsave(&mq->lock, flags);

	mq->in_flight[issue_type] -= 1;

	put_card = (mmc_tot_in_flight(mq) == 0);

	mmc_cqe_check_busy(mq);

	spin_unlock_irqrestore(&mq->lock, flags);

	अगर (!mq->cqe_busy)
		blk_mq_run_hw_queues(q, true);

	अगर (put_card)
		mmc_put_card(mq->card, &mq->ctx);
पूर्ण

व्योम mmc_blk_cqe_recovery(काष्ठा mmc_queue *mq)
अणु
	काष्ठा mmc_card *card = mq->card;
	काष्ठा mmc_host *host = card->host;
	पूर्णांक err;

	pr_debug("%s: CQE recovery start\n", mmc_hostname(host));

	err = mmc_cqe_recovery(host);
	अगर (err)
		mmc_blk_reset(mq->blkdata, host, MMC_BLK_CQE_RECOVERY);
	अन्यथा
		mmc_blk_reset_success(mq->blkdata, MMC_BLK_CQE_RECOVERY);

	pr_debug("%s: CQE recovery done\n", mmc_hostname(host));
पूर्ण

अटल व्योम mmc_blk_cqe_req_करोne(काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_queue_req *mqrq = container_of(mrq, काष्ठा mmc_queue_req,
						  brq.mrq);
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);
	काष्ठा request_queue *q = req->q;
	काष्ठा mmc_queue *mq = q->queuedata;

	/*
	 * Block layer समयouts race with completions which means the normal
	 * completion path cannot be used during recovery.
	 */
	अगर (mq->in_recovery)
		mmc_blk_cqe_complete_rq(mq, req);
	अन्यथा अगर (likely(!blk_should_fake_समयout(req->q)))
		blk_mq_complete_request(req);
पूर्ण

अटल पूर्णांक mmc_blk_cqe_start_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	mrq->करोne		= mmc_blk_cqe_req_करोne;
	mrq->recovery_notअगरier	= mmc_cqe_recovery_notअगरier;

	वापस mmc_cqe_start_req(host, mrq);
पूर्ण

अटल काष्ठा mmc_request *mmc_blk_cqe_prep_dcmd(काष्ठा mmc_queue_req *mqrq,
						 काष्ठा request *req)
अणु
	काष्ठा mmc_blk_request *brq = &mqrq->brq;

	स_रखो(brq, 0, माप(*brq));

	brq->mrq.cmd = &brq->cmd;
	brq->mrq.tag = req->tag;

	वापस &brq->mrq;
पूर्ण

अटल पूर्णांक mmc_blk_cqe_issue_flush(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_request *mrq = mmc_blk_cqe_prep_dcmd(mqrq, req);

	mrq->cmd->opcode = MMC_SWITCH;
	mrq->cmd->arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
			(EXT_CSD_FLUSH_CACHE << 16) |
			(1 << 8) |
			EXT_CSD_CMD_SET_NORMAL;
	mrq->cmd->flags = MMC_CMD_AC | MMC_RSP_R1B;

	वापस mmc_blk_cqe_start_req(mq->card->host, mrq);
पूर्ण

अटल पूर्णांक mmc_blk_hsq_issue_rw_rq(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_host *host = mq->card->host;
	पूर्णांक err;

	mmc_blk_rw_rq_prep(mqrq, mq->card, 0, mq);
	mqrq->brq.mrq.करोne = mmc_blk_hsq_req_करोne;
	mmc_pre_req(host, &mqrq->brq.mrq);

	err = mmc_cqe_start_req(host, &mqrq->brq.mrq);
	अगर (err)
		mmc_post_req(host, &mqrq->brq.mrq, err);

	वापस err;
पूर्ण

अटल पूर्णांक mmc_blk_cqe_issue_rw_rq(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_host *host = mq->card->host;

	अगर (host->hsq_enabled)
		वापस mmc_blk_hsq_issue_rw_rq(mq, req);

	mmc_blk_data_prep(mq, mqrq, 0, शून्य, शून्य);

	वापस mmc_blk_cqe_start_req(mq->card->host, &mqrq->brq.mrq);
पूर्ण

अटल व्योम mmc_blk_rw_rq_prep(काष्ठा mmc_queue_req *mqrq,
			       काष्ठा mmc_card *card,
			       पूर्णांक disable_multi,
			       काष्ठा mmc_queue *mq)
अणु
	u32 पढ़ोcmd, ग_लिखोcmd;
	काष्ठा mmc_blk_request *brq = &mqrq->brq;
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);
	काष्ठा mmc_blk_data *md = mq->blkdata;
	bool करो_rel_wr, करो_data_tag;

	mmc_blk_data_prep(mq, mqrq, disable_multi, &करो_rel_wr, &करो_data_tag);

	brq->mrq.cmd = &brq->cmd;

	brq->cmd.arg = blk_rq_pos(req);
	अगर (!mmc_card_blockaddr(card))
		brq->cmd.arg <<= 9;
	brq->cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	अगर (brq->data.blocks > 1 || करो_rel_wr) अणु
		/* SPI multiblock ग_लिखोs terminate using a special
		 * token, not a STOP_TRANSMISSION request.
		 */
		अगर (!mmc_host_is_spi(card->host) ||
		    rq_data_dir(req) == READ)
			brq->mrq.stop = &brq->stop;
		पढ़ोcmd = MMC_READ_MULTIPLE_BLOCK;
		ग_लिखोcmd = MMC_WRITE_MULTIPLE_BLOCK;
	पूर्ण अन्यथा अणु
		brq->mrq.stop = शून्य;
		पढ़ोcmd = MMC_READ_SINGLE_BLOCK;
		ग_लिखोcmd = MMC_WRITE_BLOCK;
	पूर्ण
	brq->cmd.opcode = rq_data_dir(req) == READ ? पढ़ोcmd : ग_लिखोcmd;

	/*
	 * Pre-defined multi-block transfers are preferable to
	 * खोलो ended-ones (and necessary क्रम reliable ग_लिखोs).
	 * However, it is not sufficient to just send CMD23,
	 * and aव्योम the final CMD12, as on an error condition
	 * CMD12 (stop) needs to be sent anyway. This, coupled
	 * with Auto-CMD23 enhancements provided by some
	 * hosts, means that the complनिकासy of dealing
	 * with this is best left to the host. If CMD23 is
	 * supported by card and host, we'll fill sbc in and let
	 * the host deal with handling it correctly. This means
	 * that क्रम hosts that करोn't expose MMC_CAP_CMD23, no
	 * change of behavior will be observed.
	 *
	 * N.B: Some MMC cards experience perf degradation.
	 * We'll aव्योम using CMD23-bounded multiblock ग_लिखोs क्रम
	 * these, जबतक retaining features like reliable ग_लिखोs.
	 */
	अगर ((md->flags & MMC_BLK_CMD23) && mmc_op_multi(brq->cmd.opcode) &&
	    (करो_rel_wr || !(card->quirks & MMC_QUIRK_BLK_NO_CMD23) ||
	     करो_data_tag)) अणु
		brq->sbc.opcode = MMC_SET_BLOCK_COUNT;
		brq->sbc.arg = brq->data.blocks |
			(करो_rel_wr ? (1 << 31) : 0) |
			(करो_data_tag ? (1 << 29) : 0);
		brq->sbc.flags = MMC_RSP_R1 | MMC_CMD_AC;
		brq->mrq.sbc = &brq->sbc;
	पूर्ण
पूर्ण

#घोषणा MMC_MAX_RETRIES		5
#घोषणा MMC_DATA_RETRIES	2
#घोषणा MMC_NO_RETRIES		(MMC_MAX_RETRIES + 1)

अटल पूर्णांक mmc_blk_send_stop(काष्ठा mmc_card *card, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा mmc_command cmd = अणु
		.opcode = MMC_STOP_TRANSMISSION,
		.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC,
		/* Some hosts रुको क्रम busy anyway, so provide a busy समयout */
		.busy_समयout = समयout,
	पूर्ण;

	वापस mmc_रुको_क्रम_cmd(card->host, &cmd, 5);
पूर्ण

अटल पूर्णांक mmc_blk_fix_state(काष्ठा mmc_card *card, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_blk_request *brq = &mqrq->brq;
	अचिन्हित पूर्णांक समयout = mmc_blk_data_समयout_ms(card->host, &brq->data);
	पूर्णांक err;

	mmc_retune_hold_now(card->host);

	mmc_blk_send_stop(card, समयout);

	err = card_busy_detect(card, समयout, शून्य);

	mmc_retune_release(card->host);

	वापस err;
पूर्ण

#घोषणा MMC_READ_SINGLE_RETRIES	2

/* Single sector पढ़ो during recovery */
अटल व्योम mmc_blk_पढ़ो_single(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_request *mrq = &mqrq->brq.mrq;
	काष्ठा mmc_card *card = mq->card;
	काष्ठा mmc_host *host = card->host;
	blk_status_t error = BLK_STS_OK;
	पूर्णांक retries = 0;

	करो अणु
		u32 status;
		पूर्णांक err;

		mmc_blk_rw_rq_prep(mqrq, card, 1, mq);

		mmc_रुको_क्रम_req(host, mrq);

		err = mmc_send_status(card, &status);
		अगर (err)
			जाओ error_निकास;

		अगर (!mmc_host_is_spi(host) &&
		    !mmc_पढ़ोy_क्रम_data(status)) अणु
			err = mmc_blk_fix_state(card, req);
			अगर (err)
				जाओ error_निकास;
		पूर्ण

		अगर (mrq->cmd->error && retries++ < MMC_READ_SINGLE_RETRIES)
			जारी;

		retries = 0;

		अगर (mrq->cmd->error ||
		    mrq->data->error ||
		    (!mmc_host_is_spi(host) &&
		     (mrq->cmd->resp[0] & CMD_ERRORS || status & CMD_ERRORS)))
			error = BLK_STS_IOERR;
		अन्यथा
			error = BLK_STS_OK;

	पूर्ण जबतक (blk_update_request(req, error, 512));

	वापस;

error_निकास:
	mrq->data->bytes_xfered = 0;
	blk_update_request(req, BLK_STS_IOERR, 512);
	/* Let it try the reमुख्यing request again */
	अगर (mqrq->retries > MMC_MAX_RETRIES - 1)
		mqrq->retries = MMC_MAX_RETRIES - 1;
पूर्ण

अटल अंतरभूत bool mmc_blk_oor_valid(काष्ठा mmc_blk_request *brq)
अणु
	वापस !!brq->mrq.sbc;
पूर्ण

अटल अंतरभूत u32 mmc_blk_stop_err_bits(काष्ठा mmc_blk_request *brq)
अणु
	वापस mmc_blk_oor_valid(brq) ? CMD_ERRORS : CMD_ERRORS_EXCL_OOR;
पूर्ण

/*
 * Check क्रम errors the host controller driver might not have seen such as
 * response mode errors or invalid card state.
 */
अटल bool mmc_blk_status_error(काष्ठा request *req, u32 status)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_blk_request *brq = &mqrq->brq;
	काष्ठा mmc_queue *mq = req->q->queuedata;
	u32 stop_err_bits;

	अगर (mmc_host_is_spi(mq->card->host))
		वापस false;

	stop_err_bits = mmc_blk_stop_err_bits(brq);

	वापस brq->cmd.resp[0]  & CMD_ERRORS    ||
	       brq->stop.resp[0] & stop_err_bits ||
	       status            & stop_err_bits ||
	       (rq_data_dir(req) == WRITE && !mmc_पढ़ोy_क्रम_data(status));
पूर्ण

अटल अंतरभूत bool mmc_blk_cmd_started(काष्ठा mmc_blk_request *brq)
अणु
	वापस !brq->sbc.error && !brq->cmd.error &&
	       !(brq->cmd.resp[0] & CMD_ERRORS);
पूर्ण

/*
 * Requests are completed by mmc_blk_mq_complete_rq() which sets simple
 * policy:
 * 1. A request that has transferred at least some data is considered
 * successful and will be requeued अगर there is reमुख्यing data to
 * transfer.
 * 2. Otherwise the number of retries is incremented and the request
 * will be requeued अगर there are reमुख्यing retries.
 * 3. Otherwise the request will be errored out.
 * That means mmc_blk_mq_complete_rq() is controlled by bytes_xfered and
 * mqrq->retries. So there are only 4 possible actions here:
 *	1. करो not accept the bytes_xfered value i.e. set it to zero
 *	2. change mqrq->retries to determine the number of retries
 *	3. try to reset the card
 *	4. पढ़ो one sector at a समय
 */
अटल व्योम mmc_blk_mq_rw_recovery(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	पूर्णांक type = rq_data_dir(req) == READ ? MMC_BLK_READ : MMC_BLK_WRITE;
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_blk_request *brq = &mqrq->brq;
	काष्ठा mmc_blk_data *md = mq->blkdata;
	काष्ठा mmc_card *card = mq->card;
	u32 status;
	u32 blocks;
	पूर्णांक err;

	/*
	 * Some errors the host driver might not have seen. Set the number of
	 * bytes transferred to zero in that हाल.
	 */
	err = __mmc_send_status(card, &status, 0);
	अगर (err || mmc_blk_status_error(req, status))
		brq->data.bytes_xfered = 0;

	mmc_retune_release(card->host);

	/*
	 * Try again to get the status. This also provides an opportunity क्रम
	 * re-tuning.
	 */
	अगर (err)
		err = __mmc_send_status(card, &status, 0);

	/*
	 * Nothing more to करो after the number of bytes transferred has been
	 * updated and there is no card.
	 */
	अगर (err && mmc_detect_card_हटाओd(card->host))
		वापस;

	/* Try to get back to "tran" state */
	अगर (!mmc_host_is_spi(mq->card->host) &&
	    (err || !mmc_पढ़ोy_क्रम_data(status)))
		err = mmc_blk_fix_state(mq->card, req);

	/*
	 * Special हाल क्रम SD cards where the card might record the number of
	 * blocks written.
	 */
	अगर (!err && mmc_blk_cmd_started(brq) && mmc_card_sd(card) &&
	    rq_data_dir(req) == WRITE) अणु
		अगर (mmc_sd_num_wr_blocks(card, &blocks))
			brq->data.bytes_xfered = 0;
		अन्यथा
			brq->data.bytes_xfered = blocks << 9;
	पूर्ण

	/* Reset अगर the card is in a bad state */
	अगर (!mmc_host_is_spi(mq->card->host) &&
	    err && mmc_blk_reset(md, card->host, type)) अणु
		pr_err("%s: recovery failed!\n", req->rq_disk->disk_name);
		mqrq->retries = MMC_NO_RETRIES;
		वापस;
	पूर्ण

	/*
	 * If anything was करोne, just वापस and अगर there is anything reमुख्यing
	 * on the request it will get requeued.
	 */
	अगर (brq->data.bytes_xfered)
		वापस;

	/* Reset beक्रमe last retry */
	अगर (mqrq->retries + 1 == MMC_MAX_RETRIES)
		mmc_blk_reset(md, card->host, type);

	/* Command errors fail fast, so use all MMC_MAX_RETRIES */
	अगर (brq->sbc.error || brq->cmd.error)
		वापस;

	/* Reduce the reमुख्यing retries क्रम data errors */
	अगर (mqrq->retries < MMC_MAX_RETRIES - MMC_DATA_RETRIES) अणु
		mqrq->retries = MMC_MAX_RETRIES - MMC_DATA_RETRIES;
		वापस;
	पूर्ण

	/* FIXME: Missing single sector पढ़ो क्रम large sector size */
	अगर (!mmc_large_sector(card) && rq_data_dir(req) == READ &&
	    brq->data.blocks > 1) अणु
		/* Read one sector at a समय */
		mmc_blk_पढ़ो_single(mq, req);
		वापस;
	पूर्ण
पूर्ण

अटल अंतरभूत bool mmc_blk_rq_error(काष्ठा mmc_blk_request *brq)
अणु
	mmc_blk_eval_resp_error(brq);

	वापस brq->sbc.error || brq->cmd.error || brq->stop.error ||
	       brq->data.error || brq->cmd.resp[0] & CMD_ERRORS;
पूर्ण

अटल पूर्णांक mmc_blk_card_busy(काष्ठा mmc_card *card, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	u32 status = 0;
	पूर्णांक err;

	अगर (mmc_host_is_spi(card->host) || rq_data_dir(req) == READ)
		वापस 0;

	err = card_busy_detect(card, MMC_BLK_TIMEOUT_MS, &status);

	/*
	 * Do not assume data transferred correctly अगर there are any error bits
	 * set.
	 */
	अगर (status & mmc_blk_stop_err_bits(&mqrq->brq)) अणु
		mqrq->brq.data.bytes_xfered = 0;
		err = err ? err : -EIO;
	पूर्ण

	/* Copy the exception bit so it will be seen later on */
	अगर (mmc_card_mmc(card) && status & R1_EXCEPTION_EVENT)
		mqrq->brq.cmd.resp[0] |= R1_EXCEPTION_EVENT;

	वापस err;
पूर्ण

अटल अंतरभूत व्योम mmc_blk_rw_reset_success(काष्ठा mmc_queue *mq,
					    काष्ठा request *req)
अणु
	पूर्णांक type = rq_data_dir(req) == READ ? MMC_BLK_READ : MMC_BLK_WRITE;

	mmc_blk_reset_success(mq->blkdata, type);
पूर्ण

अटल व्योम mmc_blk_mq_complete_rq(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	अचिन्हित पूर्णांक nr_bytes = mqrq->brq.data.bytes_xfered;

	अगर (nr_bytes) अणु
		अगर (blk_update_request(req, BLK_STS_OK, nr_bytes))
			blk_mq_requeue_request(req, true);
		अन्यथा
			__blk_mq_end_request(req, BLK_STS_OK);
	पूर्ण अन्यथा अगर (!blk_rq_bytes(req)) अणु
		__blk_mq_end_request(req, BLK_STS_IOERR);
	पूर्ण अन्यथा अगर (mqrq->retries++ < MMC_MAX_RETRIES) अणु
		blk_mq_requeue_request(req, true);
	पूर्ण अन्यथा अणु
		अगर (mmc_card_हटाओd(mq->card))
			req->rq_flags |= RQF_QUIET;
		blk_mq_end_request(req, BLK_STS_IOERR);
	पूर्ण
पूर्ण

अटल bool mmc_blk_urgent_bkops_needed(काष्ठा mmc_queue *mq,
					काष्ठा mmc_queue_req *mqrq)
अणु
	वापस mmc_card_mmc(mq->card) && !mmc_host_is_spi(mq->card->host) &&
	       (mqrq->brq.cmd.resp[0] & R1_EXCEPTION_EVENT ||
		mqrq->brq.stop.resp[0] & R1_EXCEPTION_EVENT);
पूर्ण

अटल व्योम mmc_blk_urgent_bkops(काष्ठा mmc_queue *mq,
				 काष्ठा mmc_queue_req *mqrq)
अणु
	अगर (mmc_blk_urgent_bkops_needed(mq, mqrq))
		mmc_run_bkops(mq->card);
पूर्ण

अटल व्योम mmc_blk_hsq_req_करोne(काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_queue_req *mqrq =
		container_of(mrq, काष्ठा mmc_queue_req, brq.mrq);
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);
	काष्ठा request_queue *q = req->q;
	काष्ठा mmc_queue *mq = q->queuedata;
	काष्ठा mmc_host *host = mq->card->host;
	अचिन्हित दीर्घ flags;

	अगर (mmc_blk_rq_error(&mqrq->brq) ||
	    mmc_blk_urgent_bkops_needed(mq, mqrq)) अणु
		spin_lock_irqsave(&mq->lock, flags);
		mq->recovery_needed = true;
		mq->recovery_req = req;
		spin_unlock_irqrestore(&mq->lock, flags);

		host->cqe_ops->cqe_recovery_start(host);

		schedule_work(&mq->recovery_work);
		वापस;
	पूर्ण

	mmc_blk_rw_reset_success(mq, req);

	/*
	 * Block layer समयouts race with completions which means the normal
	 * completion path cannot be used during recovery.
	 */
	अगर (mq->in_recovery)
		mmc_blk_cqe_complete_rq(mq, req);
	अन्यथा अगर (likely(!blk_should_fake_समयout(req->q)))
		blk_mq_complete_request(req);
पूर्ण

व्योम mmc_blk_mq_complete(काष्ठा request *req)
अणु
	काष्ठा mmc_queue *mq = req->q->queuedata;
	काष्ठा mmc_host *host = mq->card->host;

	अगर (host->cqe_enabled)
		mmc_blk_cqe_complete_rq(mq, req);
	अन्यथा अगर (likely(!blk_should_fake_समयout(req->q)))
		mmc_blk_mq_complete_rq(mq, req);
पूर्ण

अटल व्योम mmc_blk_mq_poll_completion(काष्ठा mmc_queue *mq,
				       काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_host *host = mq->card->host;

	अगर (mmc_blk_rq_error(&mqrq->brq) ||
	    mmc_blk_card_busy(mq->card, req)) अणु
		mmc_blk_mq_rw_recovery(mq, req);
	पूर्ण अन्यथा अणु
		mmc_blk_rw_reset_success(mq, req);
		mmc_retune_release(host);
	पूर्ण

	mmc_blk_urgent_bkops(mq, mqrq);
पूर्ण

अटल व्योम mmc_blk_mq_dec_in_flight(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	अचिन्हित दीर्घ flags;
	bool put_card;

	spin_lock_irqsave(&mq->lock, flags);

	mq->in_flight[mmc_issue_type(mq, req)] -= 1;

	put_card = (mmc_tot_in_flight(mq) == 0);

	spin_unlock_irqrestore(&mq->lock, flags);

	अगर (put_card)
		mmc_put_card(mq->card, &mq->ctx);
पूर्ण

अटल व्योम mmc_blk_mq_post_req(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_request *mrq = &mqrq->brq.mrq;
	काष्ठा mmc_host *host = mq->card->host;

	mmc_post_req(host, mrq, 0);

	/*
	 * Block layer समयouts race with completions which means the normal
	 * completion path cannot be used during recovery.
	 */
	अगर (mq->in_recovery)
		mmc_blk_mq_complete_rq(mq, req);
	अन्यथा अगर (likely(!blk_should_fake_समयout(req->q)))
		blk_mq_complete_request(req);

	mmc_blk_mq_dec_in_flight(mq, req);
पूर्ण

व्योम mmc_blk_mq_recovery(काष्ठा mmc_queue *mq)
अणु
	काष्ठा request *req = mq->recovery_req;
	काष्ठा mmc_host *host = mq->card->host;
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);

	mq->recovery_req = शून्य;
	mq->rw_रुको = false;

	अगर (mmc_blk_rq_error(&mqrq->brq)) अणु
		mmc_retune_hold_now(host);
		mmc_blk_mq_rw_recovery(mq, req);
	पूर्ण

	mmc_blk_urgent_bkops(mq, mqrq);

	mmc_blk_mq_post_req(mq, req);
पूर्ण

अटल व्योम mmc_blk_mq_complete_prev_req(काष्ठा mmc_queue *mq,
					 काष्ठा request **prev_req)
अणु
	अगर (mmc_host_करोne_complete(mq->card->host))
		वापस;

	mutex_lock(&mq->complete_lock);

	अगर (!mq->complete_req)
		जाओ out_unlock;

	mmc_blk_mq_poll_completion(mq, mq->complete_req);

	अगर (prev_req)
		*prev_req = mq->complete_req;
	अन्यथा
		mmc_blk_mq_post_req(mq, mq->complete_req);

	mq->complete_req = शून्य;

out_unlock:
	mutex_unlock(&mq->complete_lock);
पूर्ण

व्योम mmc_blk_mq_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_queue *mq = container_of(work, काष्ठा mmc_queue,
					    complete_work);

	mmc_blk_mq_complete_prev_req(mq, शून्य);
पूर्ण

अटल व्योम mmc_blk_mq_req_करोne(काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_queue_req *mqrq = container_of(mrq, काष्ठा mmc_queue_req,
						  brq.mrq);
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);
	काष्ठा request_queue *q = req->q;
	काष्ठा mmc_queue *mq = q->queuedata;
	काष्ठा mmc_host *host = mq->card->host;
	अचिन्हित दीर्घ flags;

	अगर (!mmc_host_करोne_complete(host)) अणु
		bool रुकोing;

		/*
		 * We cannot complete the request in this context, so record
		 * that there is a request to complete, and that a following
		 * request करोes not need to रुको (although it करोes need to
		 * complete complete_req first).
		 */
		spin_lock_irqsave(&mq->lock, flags);
		mq->complete_req = req;
		mq->rw_रुको = false;
		रुकोing = mq->रुकोing;
		spin_unlock_irqrestore(&mq->lock, flags);

		/*
		 * If 'waiting' then the रुकोing task will complete this
		 * request, otherwise queue a work to करो it. Note that
		 * complete_work may still race with the dispatch of a following
		 * request.
		 */
		अगर (रुकोing)
			wake_up(&mq->रुको);
		अन्यथा
			queue_work(mq->card->complete_wq, &mq->complete_work);

		वापस;
	पूर्ण

	/* Take the recovery path क्रम errors or urgent background operations */
	अगर (mmc_blk_rq_error(&mqrq->brq) ||
	    mmc_blk_urgent_bkops_needed(mq, mqrq)) अणु
		spin_lock_irqsave(&mq->lock, flags);
		mq->recovery_needed = true;
		mq->recovery_req = req;
		spin_unlock_irqrestore(&mq->lock, flags);
		wake_up(&mq->रुको);
		schedule_work(&mq->recovery_work);
		वापस;
	पूर्ण

	mmc_blk_rw_reset_success(mq, req);

	mq->rw_रुको = false;
	wake_up(&mq->रुको);

	mmc_blk_mq_post_req(mq, req);
पूर्ण

अटल bool mmc_blk_rw_रुको_cond(काष्ठा mmc_queue *mq, पूर्णांक *err)
अणु
	अचिन्हित दीर्घ flags;
	bool करोne;

	/*
	 * Wait जबतक there is another request in progress, but not अगर recovery
	 * is needed. Also indicate whether there is a request रुकोing to start.
	 */
	spin_lock_irqsave(&mq->lock, flags);
	अगर (mq->recovery_needed) अणु
		*err = -EBUSY;
		करोne = true;
	पूर्ण अन्यथा अणु
		करोne = !mq->rw_रुको;
	पूर्ण
	mq->रुकोing = !करोne;
	spin_unlock_irqrestore(&mq->lock, flags);

	वापस करोne;
पूर्ण

अटल पूर्णांक mmc_blk_rw_रुको(काष्ठा mmc_queue *mq, काष्ठा request **prev_req)
अणु
	पूर्णांक err = 0;

	रुको_event(mq->रुको, mmc_blk_rw_रुको_cond(mq, &err));

	/* Always complete the previous request अगर there is one */
	mmc_blk_mq_complete_prev_req(mq, prev_req);

	वापस err;
पूर्ण

अटल पूर्णांक mmc_blk_mq_issue_rw_rq(काष्ठा mmc_queue *mq,
				  काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_host *host = mq->card->host;
	काष्ठा request *prev_req = शून्य;
	पूर्णांक err = 0;

	mmc_blk_rw_rq_prep(mqrq, mq->card, 0, mq);

	mqrq->brq.mrq.करोne = mmc_blk_mq_req_करोne;

	mmc_pre_req(host, &mqrq->brq.mrq);

	err = mmc_blk_rw_रुको(mq, &prev_req);
	अगर (err)
		जाओ out_post_req;

	mq->rw_रुको = true;

	err = mmc_start_request(host, &mqrq->brq.mrq);

	अगर (prev_req)
		mmc_blk_mq_post_req(mq, prev_req);

	अगर (err)
		mq->rw_रुको = false;

	/* Release re-tuning here where there is no synchronization required */
	अगर (err || mmc_host_करोne_complete(host))
		mmc_retune_release(host);

out_post_req:
	अगर (err)
		mmc_post_req(host, &mqrq->brq.mrq, err);

	वापस err;
पूर्ण

अटल पूर्णांक mmc_blk_रुको_क्रम_idle(काष्ठा mmc_queue *mq, काष्ठा mmc_host *host)
अणु
	अगर (host->cqe_enabled)
		वापस host->cqe_ops->cqe_रुको_क्रम_idle(host);

	वापस mmc_blk_rw_रुको(mq, शून्य);
पूर्ण

क्रमागत mmc_issued mmc_blk_mq_issue_rq(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_blk_data *md = mq->blkdata;
	काष्ठा mmc_card *card = md->queue.card;
	काष्ठा mmc_host *host = card->host;
	पूर्णांक ret;

	ret = mmc_blk_part_चयन(card, md->part_type);
	अगर (ret)
		वापस MMC_REQ_FAILED_TO_START;

	चयन (mmc_issue_type(mq, req)) अणु
	हाल MMC_ISSUE_SYNC:
		ret = mmc_blk_रुको_क्रम_idle(mq, host);
		अगर (ret)
			वापस MMC_REQ_BUSY;
		चयन (req_op(req)) अणु
		हाल REQ_OP_DRV_IN:
		हाल REQ_OP_DRV_OUT:
			mmc_blk_issue_drv_op(mq, req);
			अवरोध;
		हाल REQ_OP_DISCARD:
			mmc_blk_issue_discard_rq(mq, req);
			अवरोध;
		हाल REQ_OP_SECURE_ERASE:
			mmc_blk_issue_secdiscard_rq(mq, req);
			अवरोध;
		हाल REQ_OP_FLUSH:
			mmc_blk_issue_flush(mq, req);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			वापस MMC_REQ_FAILED_TO_START;
		पूर्ण
		वापस MMC_REQ_FINISHED;
	हाल MMC_ISSUE_DCMD:
	हाल MMC_ISSUE_ASYNC:
		चयन (req_op(req)) अणु
		हाल REQ_OP_FLUSH:
			अगर (!mmc_cache_enabled(host)) अणु
				blk_mq_end_request(req, BLK_STS_OK);
				वापस MMC_REQ_FINISHED;
			पूर्ण
			ret = mmc_blk_cqe_issue_flush(mq, req);
			अवरोध;
		हाल REQ_OP_READ:
		हाल REQ_OP_WRITE:
			अगर (host->cqe_enabled)
				ret = mmc_blk_cqe_issue_rw_rq(mq, req);
			अन्यथा
				ret = mmc_blk_mq_issue_rw_rq(mq, req);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			ret = -EINVAL;
		पूर्ण
		अगर (!ret)
			वापस MMC_REQ_STARTED;
		वापस ret == -EBUSY ? MMC_REQ_BUSY : MMC_REQ_FAILED_TO_START;
	शेष:
		WARN_ON_ONCE(1);
		वापस MMC_REQ_FAILED_TO_START;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक mmc_blk_पढ़ोonly(काष्ठा mmc_card *card)
अणु
	वापस mmc_card_पढ़ोonly(card) ||
	       !(card->csd.cmdclass & CCC_BLOCK_WRITE);
पूर्ण

अटल काष्ठा mmc_blk_data *mmc_blk_alloc_req(काष्ठा mmc_card *card,
					      काष्ठा device *parent,
					      sector_t size,
					      bool शेष_ro,
					      स्थिर अक्षर *subname,
					      पूर्णांक area_type)
अणु
	काष्ठा mmc_blk_data *md;
	पूर्णांक devidx, ret;
	अक्षर cap_str[10];

	devidx = ida_simple_get(&mmc_blk_ida, 0, max_devices, GFP_KERNEL);
	अगर (devidx < 0) अणु
		/*
		 * We get -ENOSPC because there are no more any available
		 * devidx. The reason may be that, either userspace haven't yet
		 * unmounted the partitions, which postpones mmc_blk_release()
		 * from being called, or the device has more partitions than
		 * what we support.
		 */
		अगर (devidx == -ENOSPC)
			dev_err(mmc_dev(card->host),
				"no more device IDs available\n");

		वापस ERR_PTR(devidx);
	पूर्ण

	md = kzalloc(माप(काष्ठा mmc_blk_data), GFP_KERNEL);
	अगर (!md) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	md->area_type = area_type;

	/*
	 * Set the पढ़ो-only status based on the supported commands
	 * and the ग_लिखो protect चयन.
	 */
	md->पढ़ो_only = mmc_blk_पढ़ोonly(card);

	md->disk = alloc_disk(perdev_minors);
	अगर (md->disk == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त;
	पूर्ण

	INIT_LIST_HEAD(&md->part);
	INIT_LIST_HEAD(&md->rpmbs);
	md->usage = 1;

	ret = mmc_init_queue(&md->queue, card);
	अगर (ret)
		जाओ err_putdisk;

	md->queue.blkdata = md;

	/*
	 * Keep an extra reference to the queue so that we can shutकरोwn the
	 * queue (i.e. call blk_cleanup_queue()) जबतक there are still
	 * references to the 'md'. The corresponding blk_put_queue() is in
	 * mmc_blk_put().
	 */
	अगर (!blk_get_queue(md->queue.queue)) अणु
		mmc_cleanup_queue(&md->queue);
		ret = -ENODEV;
		जाओ err_putdisk;
	पूर्ण

	md->disk->major	= MMC_BLOCK_MAJOR;
	md->disk->first_minor = devidx * perdev_minors;
	md->disk->fops = &mmc_bकरोps;
	md->disk->निजी_data = md;
	md->disk->queue = md->queue.queue;
	md->parent = parent;
	set_disk_ro(md->disk, md->पढ़ो_only || शेष_ro);
	md->disk->flags = GENHD_FL_EXT_DEVT;
	अगर (area_type & (MMC_BLK_DATA_AREA_RPMB | MMC_BLK_DATA_AREA_BOOT))
		md->disk->flags |= GENHD_FL_NO_PART_SCAN
				   | GENHD_FL_SUPPRESS_PARTITION_INFO;

	/*
	 * As discussed on lkml, GENHD_FL_REMOVABLE should:
	 *
	 * - be set क्रम removable media with permanent block devices
	 * - be unset क्रम removable block devices with permanent media
	 *
	 * Since MMC block devices clearly fall under the second
	 * हाल, we करो not set GENHD_FL_REMOVABLE.  Userspace
	 * should use the block device creation/deकाष्ठाion hotplug
	 * messages to tell when the card is present.
	 */

	snम_लिखो(md->disk->disk_name, माप(md->disk->disk_name),
		 "mmcblk%u%s", card->host->index, subname ? subname : "");

	set_capacity(md->disk, size);

	अगर (mmc_host_cmd23(card->host)) अणु
		अगर ((mmc_card_mmc(card) &&
		     card->csd.mmca_vsn >= CSD_SPEC_VER_3) ||
		    (mmc_card_sd(card) &&
		     card->scr.cmds & SD_SCR_CMD23_SUPPORT))
			md->flags |= MMC_BLK_CMD23;
	पूर्ण

	अगर (mmc_card_mmc(card) &&
	    md->flags & MMC_BLK_CMD23 &&
	    ((card->ext_csd.rel_param & EXT_CSD_WR_REL_PARAM_EN) ||
	     card->ext_csd.rel_sectors)) अणु
		md->flags |= MMC_BLK_REL_WR;
		blk_queue_ग_लिखो_cache(md->queue.queue, true, true);
	पूर्ण

	string_get_size((u64)size, 512, STRING_UNITS_2,
			cap_str, माप(cap_str));
	pr_info("%s: %s %s %s %s\n",
		md->disk->disk_name, mmc_card_id(card), mmc_card_name(card),
		cap_str, md->पढ़ो_only ? "(ro)" : "");

	वापस md;

 err_putdisk:
	put_disk(md->disk);
 err_kमुक्त:
	kमुक्त(md);
 out:
	ida_simple_हटाओ(&mmc_blk_ida, devidx);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा mmc_blk_data *mmc_blk_alloc(काष्ठा mmc_card *card)
अणु
	sector_t size;

	अगर (!mmc_card_sd(card) && mmc_card_blockaddr(card)) अणु
		/*
		 * The EXT_CSD sector count is in number or 512 byte
		 * sectors.
		 */
		size = card->ext_csd.sectors;
	पूर्ण अन्यथा अणु
		/*
		 * The CSD capacity field is in units of पढ़ो_blkbits.
		 * set_capacity takes units of 512 bytes.
		 */
		size = (typeof(sector_t))card->csd.capacity
			<< (card->csd.पढ़ो_blkbits - 9);
	पूर्ण

	वापस mmc_blk_alloc_req(card, &card->dev, size, false, शून्य,
					MMC_BLK_DATA_AREA_MAIN);
पूर्ण

अटल पूर्णांक mmc_blk_alloc_part(काष्ठा mmc_card *card,
			      काष्ठा mmc_blk_data *md,
			      अचिन्हित पूर्णांक part_type,
			      sector_t size,
			      bool शेष_ro,
			      स्थिर अक्षर *subname,
			      पूर्णांक area_type)
अणु
	काष्ठा mmc_blk_data *part_md;

	part_md = mmc_blk_alloc_req(card, disk_to_dev(md->disk), size, शेष_ro,
				    subname, area_type);
	अगर (IS_ERR(part_md))
		वापस PTR_ERR(part_md);
	part_md->part_type = part_type;
	list_add(&part_md->part, &md->part);

	वापस 0;
पूर्ण

/**
 * mmc_rpmb_ioctl() - ioctl handler क्रम the RPMB अक्षरdev
 * @filp: the अक्षरacter device file
 * @cmd: the ioctl() command
 * @arg: the argument from userspace
 *
 * This will essentially just redirect the ioctl()s coming in over to
 * the मुख्य block device spawning the RPMB अक्षरacter device.
 */
अटल दीर्घ mmc_rpmb_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	काष्ठा mmc_rpmb_data *rpmb = filp->निजी_data;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल MMC_IOC_CMD:
		ret = mmc_blk_ioctl_cmd(rpmb->md,
					(काष्ठा mmc_ioc_cmd __user *)arg,
					rpmb);
		अवरोध;
	हाल MMC_IOC_MULTI_CMD:
		ret = mmc_blk_ioctl_multi_cmd(rpmb->md,
					(काष्ठा mmc_ioc_multi_cmd __user *)arg,
					rpmb);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ mmc_rpmb_ioctl_compat(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	वापस mmc_rpmb_ioctl(filp, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mmc_rpmb_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा mmc_rpmb_data *rpmb = container_of(inode->i_cdev,
						  काष्ठा mmc_rpmb_data, chrdev);

	get_device(&rpmb->dev);
	filp->निजी_data = rpmb;
	mmc_blk_get(rpmb->md->disk);

	वापस nonseekable_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक mmc_rpmb_chrdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा mmc_rpmb_data *rpmb = container_of(inode->i_cdev,
						  काष्ठा mmc_rpmb_data, chrdev);

	mmc_blk_put(rpmb->md);
	put_device(&rpmb->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mmc_rpmb_fileops = अणु
	.release = mmc_rpmb_chrdev_release,
	.खोलो = mmc_rpmb_chrdev_खोलो,
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.unlocked_ioctl = mmc_rpmb_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = mmc_rpmb_ioctl_compat,
#पूर्ण_अगर
पूर्ण;

अटल व्योम mmc_blk_rpmb_device_release(काष्ठा device *dev)
अणु
	काष्ठा mmc_rpmb_data *rpmb = dev_get_drvdata(dev);

	ida_simple_हटाओ(&mmc_rpmb_ida, rpmb->id);
	kमुक्त(rpmb);
पूर्ण

अटल पूर्णांक mmc_blk_alloc_rpmb_part(काष्ठा mmc_card *card,
				   काष्ठा mmc_blk_data *md,
				   अचिन्हित पूर्णांक part_index,
				   sector_t size,
				   स्थिर अक्षर *subname)
अणु
	पूर्णांक devidx, ret;
	अक्षर rpmb_name[DISK_NAME_LEN];
	अक्षर cap_str[10];
	काष्ठा mmc_rpmb_data *rpmb;

	/* This creates the minor number क्रम the RPMB अक्षर device */
	devidx = ida_simple_get(&mmc_rpmb_ida, 0, max_devices, GFP_KERNEL);
	अगर (devidx < 0)
		वापस devidx;

	rpmb = kzalloc(माप(*rpmb), GFP_KERNEL);
	अगर (!rpmb) अणु
		ida_simple_हटाओ(&mmc_rpmb_ida, devidx);
		वापस -ENOMEM;
	पूर्ण

	snम_लिखो(rpmb_name, माप(rpmb_name),
		 "mmcblk%u%s", card->host->index, subname ? subname : "");

	rpmb->id = devidx;
	rpmb->part_index = part_index;
	rpmb->dev.init_name = rpmb_name;
	rpmb->dev.bus = &mmc_rpmb_bus_type;
	rpmb->dev.devt = MKDEV(MAJOR(mmc_rpmb_devt), rpmb->id);
	rpmb->dev.parent = &card->dev;
	rpmb->dev.release = mmc_blk_rpmb_device_release;
	device_initialize(&rpmb->dev);
	dev_set_drvdata(&rpmb->dev, rpmb);
	rpmb->md = md;

	cdev_init(&rpmb->chrdev, &mmc_rpmb_fileops);
	rpmb->chrdev.owner = THIS_MODULE;
	ret = cdev_device_add(&rpmb->chrdev, &rpmb->dev);
	अगर (ret) अणु
		pr_err("%s: could not add character device\n", rpmb_name);
		जाओ out_put_device;
	पूर्ण

	list_add(&rpmb->node, &md->rpmbs);

	string_get_size((u64)size, 512, STRING_UNITS_2,
			cap_str, माप(cap_str));

	pr_info("%s: %s %s %s, chardev (%d:%d)\n",
		rpmb_name, mmc_card_id(card), mmc_card_name(card), cap_str,
		MAJOR(mmc_rpmb_devt), rpmb->id);

	वापस 0;

out_put_device:
	put_device(&rpmb->dev);
	वापस ret;
पूर्ण

अटल व्योम mmc_blk_हटाओ_rpmb_part(काष्ठा mmc_rpmb_data *rpmb)

अणु
	cdev_device_del(&rpmb->chrdev, &rpmb->dev);
	put_device(&rpmb->dev);
पूर्ण

/* MMC Physical partitions consist of two boot partitions and
 * up to four general purpose partitions.
 * For each partition enabled in EXT_CSD a block device will be allocatedi
 * to provide access to the partition.
 */

अटल पूर्णांक mmc_blk_alloc_parts(काष्ठा mmc_card *card, काष्ठा mmc_blk_data *md)
अणु
	पूर्णांक idx, ret;

	अगर (!mmc_card_mmc(card))
		वापस 0;

	क्रम (idx = 0; idx < card->nr_parts; idx++) अणु
		अगर (card->part[idx].area_type & MMC_BLK_DATA_AREA_RPMB) अणु
			/*
			 * RPMB partitions करोes not provide block access, they
			 * are only accessed using ioctl():s. Thus create
			 * special RPMB block devices that करो not have a
			 * backing block queue क्रम these.
			 */
			ret = mmc_blk_alloc_rpmb_part(card, md,
				card->part[idx].part_cfg,
				card->part[idx].size >> 9,
				card->part[idx].name);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (card->part[idx].size) अणु
			ret = mmc_blk_alloc_part(card, md,
				card->part[idx].part_cfg,
				card->part[idx].size >> 9,
				card->part[idx].क्रमce_ro,
				card->part[idx].name,
				card->part[idx].area_type);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mmc_blk_हटाओ_req(काष्ठा mmc_blk_data *md)
अणु
	काष्ठा mmc_card *card;

	अगर (md) अणु
		/*
		 * Flush reमुख्यing requests and मुक्त queues. It
		 * is मुक्तing the queue that stops new requests
		 * from being accepted.
		 */
		card = md->queue.card;
		अगर (md->disk->flags & GENHD_FL_UP) अणु
			device_हटाओ_file(disk_to_dev(md->disk), &md->क्रमce_ro);
			अगर ((md->area_type & MMC_BLK_DATA_AREA_BOOT) &&
					card->ext_csd.boot_ro_lockable)
				device_हटाओ_file(disk_to_dev(md->disk),
					&md->घातer_ro_lock);

			del_gendisk(md->disk);
		पूर्ण
		mmc_cleanup_queue(&md->queue);
		mmc_blk_put(md);
	पूर्ण
पूर्ण

अटल व्योम mmc_blk_हटाओ_parts(काष्ठा mmc_card *card,
				 काष्ठा mmc_blk_data *md)
अणु
	काष्ठा list_head *pos, *q;
	काष्ठा mmc_blk_data *part_md;
	काष्ठा mmc_rpmb_data *rpmb;

	/* Remove RPMB partitions */
	list_क्रम_each_safe(pos, q, &md->rpmbs) अणु
		rpmb = list_entry(pos, काष्ठा mmc_rpmb_data, node);
		list_del(pos);
		mmc_blk_हटाओ_rpmb_part(rpmb);
	पूर्ण
	/* Remove block partitions */
	list_क्रम_each_safe(pos, q, &md->part) अणु
		part_md = list_entry(pos, काष्ठा mmc_blk_data, part);
		list_del(pos);
		mmc_blk_हटाओ_req(part_md);
	पूर्ण
पूर्ण

अटल पूर्णांक mmc_add_disk(काष्ठा mmc_blk_data *md)
अणु
	पूर्णांक ret;
	काष्ठा mmc_card *card = md->queue.card;

	device_add_disk(md->parent, md->disk, शून्य);
	md->क्रमce_ro.show = क्रमce_ro_show;
	md->क्रमce_ro.store = क्रमce_ro_store;
	sysfs_attr_init(&md->क्रमce_ro.attr);
	md->क्रमce_ro.attr.name = "force_ro";
	md->क्रमce_ro.attr.mode = S_IRUGO | S_IWUSR;
	ret = device_create_file(disk_to_dev(md->disk), &md->क्रमce_ro);
	अगर (ret)
		जाओ क्रमce_ro_fail;

	अगर ((md->area_type & MMC_BLK_DATA_AREA_BOOT) &&
	     card->ext_csd.boot_ro_lockable) अणु
		umode_t mode;

		अगर (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PWR_WP_DIS)
			mode = S_IRUGO;
		अन्यथा
			mode = S_IRUGO | S_IWUSR;

		md->घातer_ro_lock.show = घातer_ro_lock_show;
		md->घातer_ro_lock.store = घातer_ro_lock_store;
		sysfs_attr_init(&md->घातer_ro_lock.attr);
		md->घातer_ro_lock.attr.mode = mode;
		md->घातer_ro_lock.attr.name =
					"ro_lock_until_next_power_on";
		ret = device_create_file(disk_to_dev(md->disk),
				&md->घातer_ro_lock);
		अगर (ret)
			जाओ घातer_ro_lock_fail;
	पूर्ण
	वापस ret;

घातer_ro_lock_fail:
	device_हटाओ_file(disk_to_dev(md->disk), &md->क्रमce_ro);
क्रमce_ro_fail:
	del_gendisk(md->disk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक mmc_dbg_card_status_get(व्योम *data, u64 *val)
अणु
	काष्ठा mmc_card *card = data;
	काष्ठा mmc_blk_data *md = dev_get_drvdata(&card->dev);
	काष्ठा mmc_queue *mq = &md->queue;
	काष्ठा request *req;
	पूर्णांक ret;

	/* Ask the block layer about the card status */
	req = blk_get_request(mq->queue, REQ_OP_DRV_IN, 0);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	req_to_mmc_queue_req(req)->drv_op = MMC_DRV_OP_GET_CARD_STATUS;
	blk_execute_rq(शून्य, req, 0);
	ret = req_to_mmc_queue_req(req)->drv_op_result;
	अगर (ret >= 0) अणु
		*val = ret;
		ret = 0;
	पूर्ण
	blk_put_request(req);

	वापस ret;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(mmc_dbg_card_status_fops, mmc_dbg_card_status_get,
			 शून्य, "%08llx\n");

/* That is two digits * 512 + 1 क्रम newline */
#घोषणा EXT_CSD_STR_LEN 1025

अटल पूर्णांक mmc_ext_csd_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा mmc_card *card = inode->i_निजी;
	काष्ठा mmc_blk_data *md = dev_get_drvdata(&card->dev);
	काष्ठा mmc_queue *mq = &md->queue;
	काष्ठा request *req;
	अक्षर *buf;
	sमाप_प्रकार n = 0;
	u8 *ext_csd;
	पूर्णांक err, i;

	buf = kदो_स्मृति(EXT_CSD_STR_LEN + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Ask the block layer क्रम the EXT CSD */
	req = blk_get_request(mq->queue, REQ_OP_DRV_IN, 0);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out_मुक्त;
	पूर्ण
	req_to_mmc_queue_req(req)->drv_op = MMC_DRV_OP_GET_EXT_CSD;
	req_to_mmc_queue_req(req)->drv_op_data = &ext_csd;
	blk_execute_rq(शून्य, req, 0);
	err = req_to_mmc_queue_req(req)->drv_op_result;
	blk_put_request(req);
	अगर (err) अणु
		pr_err("FAILED %d\n", err);
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < 512; i++)
		n += प्र_लिखो(buf + n, "%02x", ext_csd[i]);
	n += प्र_लिखो(buf + n, "\n");

	अगर (n != EXT_CSD_STR_LEN) अणु
		err = -EINVAL;
		kमुक्त(ext_csd);
		जाओ out_मुक्त;
	पूर्ण

	filp->निजी_data = buf;
	kमुक्त(ext_csd);
	वापस 0;

out_मुक्त:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल sमाप_प्रकार mmc_ext_csd_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर *buf = filp->निजी_data;

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos,
				       buf, EXT_CSD_STR_LEN);
पूर्ण

अटल पूर्णांक mmc_ext_csd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mmc_dbg_ext_csd_fops = अणु
	.खोलो		= mmc_ext_csd_खोलो,
	.पढ़ो		= mmc_ext_csd_पढ़ो,
	.release	= mmc_ext_csd_release,
	.llseek		= शेष_llseek,
पूर्ण;

अटल पूर्णांक mmc_blk_add_debugfs(काष्ठा mmc_card *card, काष्ठा mmc_blk_data *md)
अणु
	काष्ठा dentry *root;

	अगर (!card->debugfs_root)
		वापस 0;

	root = card->debugfs_root;

	अगर (mmc_card_mmc(card) || mmc_card_sd(card)) अणु
		md->status_dentry =
			debugfs_create_file_unsafe("status", 0400, root,
						   card,
						   &mmc_dbg_card_status_fops);
		अगर (!md->status_dentry)
			वापस -EIO;
	पूर्ण

	अगर (mmc_card_mmc(card)) अणु
		md->ext_csd_dentry =
			debugfs_create_file("ext_csd", S_IRUSR, root, card,
					    &mmc_dbg_ext_csd_fops);
		अगर (!md->ext_csd_dentry)
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mmc_blk_हटाओ_debugfs(काष्ठा mmc_card *card,
				   काष्ठा mmc_blk_data *md)
अणु
	अगर (!card->debugfs_root)
		वापस;

	अगर (!IS_ERR_OR_शून्य(md->status_dentry)) अणु
		debugfs_हटाओ(md->status_dentry);
		md->status_dentry = शून्य;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(md->ext_csd_dentry)) अणु
		debugfs_हटाओ(md->ext_csd_dentry);
		md->ext_csd_dentry = शून्य;
	पूर्ण
पूर्ण

#अन्यथा

अटल पूर्णांक mmc_blk_add_debugfs(काष्ठा mmc_card *card, काष्ठा mmc_blk_data *md)
अणु
	वापस 0;
पूर्ण

अटल व्योम mmc_blk_हटाओ_debugfs(काष्ठा mmc_card *card,
				   काष्ठा mmc_blk_data *md)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक mmc_blk_probe(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_blk_data *md, *part_md;
	पूर्णांक ret = 0;

	/*
	 * Check that the card supports the command class(es) we need.
	 */
	अगर (!(card->csd.cmdclass & CCC_BLOCK_READ))
		वापस -ENODEV;

	mmc_fixup_device(card, mmc_blk_fixups);

	card->complete_wq = alloc_workqueue("mmc_complete",
					WQ_MEM_RECLAIM | WQ_HIGHPRI, 0);
	अगर (!card->complete_wq) अणु
		pr_err("Failed to create mmc completion workqueue");
		वापस -ENOMEM;
	पूर्ण

	md = mmc_blk_alloc(card);
	अगर (IS_ERR(md)) अणु
		ret = PTR_ERR(md);
		जाओ out_मुक्त;
	पूर्ण

	ret = mmc_blk_alloc_parts(card, md);
	अगर (ret)
		जाओ out;

	dev_set_drvdata(&card->dev, md);

	ret = mmc_add_disk(md);
	अगर (ret)
		जाओ out;

	list_क्रम_each_entry(part_md, &md->part, part) अणु
		ret = mmc_add_disk(part_md);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Add two debugfs entries */
	mmc_blk_add_debugfs(card, md);

	pm_runसमय_set_स्वतःsuspend_delay(&card->dev, 3000);
	pm_runसमय_use_स्वतःsuspend(&card->dev);

	/*
	 * Don't enable runसमय PM क्रम SD-combo cards here. Leave that
	 * decision to be taken during the SDIO init sequence instead.
	 */
	अगर (card->type != MMC_TYPE_SD_COMBO) अणु
		pm_runसमय_set_active(&card->dev);
		pm_runसमय_enable(&card->dev);
	पूर्ण

	वापस 0;

out:
	mmc_blk_हटाओ_parts(card, md);
	mmc_blk_हटाओ_req(md);
out_मुक्त:
	destroy_workqueue(card->complete_wq);
	वापस ret;
पूर्ण

अटल व्योम mmc_blk_हटाओ(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_blk_data *md = dev_get_drvdata(&card->dev);

	mmc_blk_हटाओ_debugfs(card, md);
	mmc_blk_हटाओ_parts(card, md);
	pm_runसमय_get_sync(&card->dev);
	अगर (md->part_curr != md->part_type) अणु
		mmc_claim_host(card->host);
		mmc_blk_part_चयन(card, md->part_type);
		mmc_release_host(card->host);
	पूर्ण
	अगर (card->type != MMC_TYPE_SD_COMBO)
		pm_runसमय_disable(&card->dev);
	pm_runसमय_put_noidle(&card->dev);
	mmc_blk_हटाओ_req(md);
	dev_set_drvdata(&card->dev, शून्य);
	destroy_workqueue(card->complete_wq);
पूर्ण

अटल पूर्णांक _mmc_blk_suspend(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_blk_data *part_md;
	काष्ठा mmc_blk_data *md = dev_get_drvdata(&card->dev);

	अगर (md) अणु
		mmc_queue_suspend(&md->queue);
		list_क्रम_each_entry(part_md, &md->part, part) अणु
			mmc_queue_suspend(&part_md->queue);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mmc_blk_shutकरोwn(काष्ठा mmc_card *card)
अणु
	_mmc_blk_suspend(card);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mmc_blk_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);

	वापस _mmc_blk_suspend(card);
पूर्ण

अटल पूर्णांक mmc_blk_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_blk_data *part_md;
	काष्ठा mmc_blk_data *md = dev_get_drvdata(dev);

	अगर (md) अणु
		/*
		 * Resume involves the card going पूर्णांकo idle state,
		 * so current partition is always the मुख्य one.
		 */
		md->part_curr = md->part_type;
		mmc_queue_resume(&md->queue);
		list_क्रम_each_entry(part_md, &md->part, part) अणु
			mmc_queue_resume(&part_md->queue);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mmc_blk_pm_ops, mmc_blk_suspend, mmc_blk_resume);

अटल काष्ठा mmc_driver mmc_driver = अणु
	.drv		= अणु
		.name	= "mmcblk",
		.pm	= &mmc_blk_pm_ops,
	पूर्ण,
	.probe		= mmc_blk_probe,
	.हटाओ		= mmc_blk_हटाओ,
	.shutकरोwn	= mmc_blk_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init mmc_blk_init(व्योम)
अणु
	पूर्णांक res;

	res  = bus_रेजिस्टर(&mmc_rpmb_bus_type);
	अगर (res < 0) अणु
		pr_err("mmcblk: could not register RPMB bus type\n");
		वापस res;
	पूर्ण
	res = alloc_chrdev_region(&mmc_rpmb_devt, 0, MAX_DEVICES, "rpmb");
	अगर (res < 0) अणु
		pr_err("mmcblk: failed to allocate rpmb chrdev region\n");
		जाओ out_bus_unreg;
	पूर्ण

	अगर (perdev_minors != CONFIG_MMC_BLOCK_MINORS)
		pr_info("mmcblk: using %d minors per device\n", perdev_minors);

	max_devices = min(MAX_DEVICES, (1 << MINORBITS) / perdev_minors);

	res = रेजिस्टर_blkdev(MMC_BLOCK_MAJOR, "mmc");
	अगर (res)
		जाओ out_chrdev_unreg;

	res = mmc_रेजिस्टर_driver(&mmc_driver);
	अगर (res)
		जाओ out_blkdev_unreg;

	वापस 0;

out_blkdev_unreg:
	unरेजिस्टर_blkdev(MMC_BLOCK_MAJOR, "mmc");
out_chrdev_unreg:
	unरेजिस्टर_chrdev_region(mmc_rpmb_devt, MAX_DEVICES);
out_bus_unreg:
	bus_unरेजिस्टर(&mmc_rpmb_bus_type);
	वापस res;
पूर्ण

अटल व्योम __निकास mmc_blk_निकास(व्योम)
अणु
	mmc_unरेजिस्टर_driver(&mmc_driver);
	unरेजिस्टर_blkdev(MMC_BLOCK_MAJOR, "mmc");
	unरेजिस्टर_chrdev_region(mmc_rpmb_devt, MAX_DEVICES);
	bus_unरेजिस्टर(&mmc_rpmb_bus_type);
पूर्ण

module_init(mmc_blk_init);
module_निकास(mmc_blk_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Multimedia Card (MMC) block device driver");

