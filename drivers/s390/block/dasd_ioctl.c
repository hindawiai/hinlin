<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Carsten Otte <Cotte@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2001
 *
 * i/o controls क्रम the dasd driver.
 */

#घोषणा KMSG_COMPONENT "dasd"

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compat.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/schid.h>
#समावेश <यंत्र/cmb.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/dasd_mod.h>

/* This is ugly... */
#घोषणा PRINTK_HEADER "dasd_ioctl:"

#समावेश "dasd_int.h"


अटल पूर्णांक
dasd_ioctl_api_version(व्योम __user *argp)
अणु
	पूर्णांक ver = DASD_API_VERSION;
	वापस put_user(ver, (पूर्णांक __user *)argp);
पूर्ण

/*
 * Enable device.
 * used by dasdfmt after BIODASDDISABLE to retrigger blocksize detection
 */
अटल पूर्णांक
dasd_ioctl_enable(काष्ठा block_device *bdev)
अणु
	काष्ठा dasd_device *base;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;

	dasd_enable_device(base);
	dasd_put_device(base);
	वापस 0;
पूर्ण

/*
 * Disable device.
 * Used by dasdfmt. Disable I/O operations but allow ioctls.
 */
अटल पूर्णांक
dasd_ioctl_disable(काष्ठा block_device *bdev)
अणु
	काष्ठा dasd_device *base;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;
	/*
	 * Man this is sick. We करोn't करो a real disable but only करोwngrade
	 * the device to DASD_STATE_BASIC. The reason is that dasdfmt uses
	 * BIODASDDISABLE to disable accesses to the device via the block
	 * device layer but it still wants to करो i/o on the device by
	 * using the BIODASDFMT ioctl. Thereक्रमe the correct state क्रम the
	 * device is DASD_STATE_BASIC that allows to करो basic i/o.
	 */
	dasd_set_target_state(base, DASD_STATE_BASIC);
	/*
	 * Set i_size to zero, since पढ़ो, ग_लिखो, etc. check against this
	 * value.
	 */
	set_capacity(bdev->bd_disk, 0);
	dasd_put_device(base);
	वापस 0;
पूर्ण

/*
 * Quiesce device.
 */
अटल पूर्णांक dasd_ioctl_quiesce(काष्ठा dasd_block *block)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_device *base;

	base = block->base;
	अगर (!capable (CAP_SYS_ADMIN))
		वापस -EACCES;

	pr_info("%s: The DASD has been put in the quiesce "
		"state\n", dev_name(&base->cdev->dev));
	spin_lock_irqsave(get_ccwdev_lock(base->cdev), flags);
	dasd_device_set_stop_bits(base, DASD_STOPPED_QUIESCE);
	spin_unlock_irqrestore(get_ccwdev_lock(base->cdev), flags);
	वापस 0;
पूर्ण


/*
 * Resume device.
 */
अटल पूर्णांक dasd_ioctl_resume(काष्ठा dasd_block *block)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_device *base;

	base = block->base;
	अगर (!capable (CAP_SYS_ADMIN))
		वापस -EACCES;

	pr_info("%s: I/O operations have been resumed "
		"on the DASD\n", dev_name(&base->cdev->dev));
	spin_lock_irqsave(get_ccwdev_lock(base->cdev), flags);
	dasd_device_हटाओ_stop_bits(base, DASD_STOPPED_QUIESCE);
	spin_unlock_irqrestore(get_ccwdev_lock(base->cdev), flags);

	dasd_schedule_block_bh(block);
	वापस 0;
पूर्ण

/*
 * Abort all failfast I/O on a device.
 */
अटल पूर्णांक dasd_ioctl_पातio(काष्ठा dasd_block *block)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_device *base;
	काष्ठा dasd_ccw_req *cqr, *n;

	base = block->base;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (test_and_set_bit(DASD_FLAG_ABORTALL, &base->flags))
		वापस 0;
	DBF_DEV_EVENT(DBF_NOTICE, base, "%s", "abortall flag set");

	spin_lock_irqsave(&block->request_queue_lock, flags);
	spin_lock(&block->queue_lock);
	list_क्रम_each_entry_safe(cqr, n, &block->ccw_queue, blocklist) अणु
		अगर (test_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags) &&
		    cqr->callback_data &&
		    cqr->callback_data != DASD_SLEEPON_START_TAG &&
		    cqr->callback_data != DASD_SLEEPON_END_TAG) अणु
			spin_unlock(&block->queue_lock);
			blk_पात_request(cqr->callback_data);
			spin_lock(&block->queue_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&block->queue_lock);
	spin_unlock_irqrestore(&block->request_queue_lock, flags);

	dasd_schedule_block_bh(block);
	वापस 0;
पूर्ण

/*
 * Allow I/O on a device
 */
अटल पूर्णांक dasd_ioctl_allowio(काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_device *base;

	base = block->base;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (test_and_clear_bit(DASD_FLAG_ABORTALL, &base->flags))
		DBF_DEV_EVENT(DBF_NOTICE, base, "%s", "abortall flag unset");

	वापस 0;
पूर्ण

/*
 * perक्रमms क्रमmatting of _device_ according to _fdata_
 * Note: The discipline's क्रमmat_function is assumed to deliver क्रमmatting
 * commands to क्रमmat multiple units of the device. In terms of the ECKD
 * devices this means CCWs are generated to क्रमmat multiple tracks.
 */
अटल पूर्णांक
dasd_क्रमmat(काष्ठा dasd_block *block, काष्ठा क्रमmat_data_t *fdata)
अणु
	काष्ठा dasd_device *base;
	पूर्णांक rc;

	base = block->base;
	अगर (base->discipline->क्रमmat_device == शून्य)
		वापस -EPERM;

	अगर (base->state != DASD_STATE_BASIC) अणु
		pr_warn("%s: The DASD cannot be formatted while it is enabled\n",
			dev_name(&base->cdev->dev));
		वापस -EBUSY;
	पूर्ण

	DBF_DEV_EVENT(DBF_NOTICE, base,
		      "formatting units %u to %u (%u B blocks) flags %u",
		      fdata->start_unit,
		      fdata->stop_unit, fdata->blksize, fdata->पूर्णांकensity);

	/* Since dasdfmt keeps the device खोलो after it was disabled,
	 * there still exists an inode क्रम this device.
	 * We must update i_blkbits, otherwise we might get errors when
	 * enabling the device later.
	 */
	अगर (fdata->start_unit == 0) अणु
		block->gdp->part0->bd_inode->i_blkbits =
			blksize_bits(fdata->blksize);
	पूर्ण

	rc = base->discipline->क्रमmat_device(base, fdata, 1);
	अगर (rc == -EAGAIN)
		rc = base->discipline->क्रमmat_device(base, fdata, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक dasd_check_क्रमmat(काष्ठा dasd_block *block,
			     काष्ठा क्रमmat_check_t *cdata)
अणु
	काष्ठा dasd_device *base;
	पूर्णांक rc;

	base = block->base;
	अगर (!base->discipline->check_device_क्रमmat)
		वापस -ENOTTY;

	rc = base->discipline->check_device_क्रमmat(base, cdata, 1);
	अगर (rc == -EAGAIN)
		rc = base->discipline->check_device_क्रमmat(base, cdata, 0);

	वापस rc;
पूर्ण

/*
 * Format device.
 */
अटल पूर्णांक
dasd_ioctl_क्रमmat(काष्ठा block_device *bdev, व्योम __user *argp)
अणु
	काष्ठा dasd_device *base;
	काष्ठा क्रमmat_data_t fdata;
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (!argp)
		वापस -EINVAL;
	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;
	अगर (base->features & DASD_FEATURE_READONLY ||
	    test_bit(DASD_FLAG_DEVICE_RO, &base->flags)) अणु
		dasd_put_device(base);
		वापस -EROFS;
	पूर्ण
	अगर (copy_from_user(&fdata, argp, माप(काष्ठा क्रमmat_data_t))) अणु
		dasd_put_device(base);
		वापस -EFAULT;
	पूर्ण
	अगर (bdev_is_partition(bdev)) अणु
		pr_warn("%s: The specified DASD is a partition and cannot be formatted\n",
			dev_name(&base->cdev->dev));
		dasd_put_device(base);
		वापस -EINVAL;
	पूर्ण
	rc = dasd_क्रमmat(base->block, &fdata);
	dasd_put_device(base);

	वापस rc;
पूर्ण

/*
 * Check device क्रमmat
 */
अटल पूर्णांक dasd_ioctl_check_क्रमmat(काष्ठा block_device *bdev, व्योम __user *argp)
अणु
	काष्ठा क्रमmat_check_t cdata;
	काष्ठा dasd_device *base;
	पूर्णांक rc = 0;

	अगर (!argp)
		वापस -EINVAL;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;
	अगर (bdev_is_partition(bdev)) अणु
		pr_warn("%s: The specified DASD is a partition and cannot be checked\n",
			dev_name(&base->cdev->dev));
		rc = -EINVAL;
		जाओ out_err;
	पूर्ण

	अगर (copy_from_user(&cdata, argp, माप(cdata))) अणु
		rc = -EFAULT;
		जाओ out_err;
	पूर्ण

	rc = dasd_check_क्रमmat(base->block, &cdata);
	अगर (rc)
		जाओ out_err;

	अगर (copy_to_user(argp, &cdata, माप(cdata)))
		rc = -EFAULT;

out_err:
	dasd_put_device(base);

	वापस rc;
पूर्ण

अटल पूर्णांक dasd_release_space(काष्ठा dasd_device *device,
			      काष्ठा क्रमmat_data_t *rdata)
अणु
	अगर (!device->discipline->is_ese && !device->discipline->is_ese(device))
		वापस -ENOTSUPP;
	अगर (!device->discipline->release_space)
		वापस -ENOTSUPP;

	वापस device->discipline->release_space(device, rdata);
पूर्ण

/*
 * Release allocated space
 */
अटल पूर्णांक dasd_ioctl_release_space(काष्ठा block_device *bdev, व्योम __user *argp)
अणु
	काष्ठा क्रमmat_data_t rdata;
	काष्ठा dasd_device *base;
	पूर्णांक rc = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (!argp)
		वापस -EINVAL;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;
	अगर (base->features & DASD_FEATURE_READONLY ||
	    test_bit(DASD_FLAG_DEVICE_RO, &base->flags)) अणु
		rc = -EROFS;
		जाओ out_err;
	पूर्ण
	अगर (bdev_is_partition(bdev)) अणु
		pr_warn("%s: The specified DASD is a partition and tracks cannot be released\n",
			dev_name(&base->cdev->dev));
		rc = -EINVAL;
		जाओ out_err;
	पूर्ण

	अगर (copy_from_user(&rdata, argp, माप(rdata))) अणु
		rc = -EFAULT;
		जाओ out_err;
	पूर्ण

	rc = dasd_release_space(base, &rdata);

out_err:
	dasd_put_device(base);

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_DASD_PROखाता
/*
 * Reset device profile inक्रमmation
 */
अटल पूर्णांक dasd_ioctl_reset_profile(काष्ठा dasd_block *block)
अणु
	dasd_profile_reset(&block->profile);
	वापस 0;
पूर्ण

/*
 * Return device profile inक्रमmation
 */
अटल पूर्णांक dasd_ioctl_पढ़ो_profile(काष्ठा dasd_block *block, व्योम __user *argp)
अणु
	काष्ठा dasd_profile_info_t *data;
	पूर्णांक rc = 0;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock_bh(&block->profile.lock);
	अगर (block->profile.data) अणु
		data->dasd_io_reqs = block->profile.data->dasd_io_reqs;
		data->dasd_io_sects = block->profile.data->dasd_io_sects;
		स_नकल(data->dasd_io_secs, block->profile.data->dasd_io_secs,
		       माप(data->dasd_io_secs));
		स_नकल(data->dasd_io_बार, block->profile.data->dasd_io_बार,
		       माप(data->dasd_io_बार));
		स_नकल(data->dasd_io_timps, block->profile.data->dasd_io_timps,
		       माप(data->dasd_io_timps));
		स_नकल(data->dasd_io_समय1, block->profile.data->dasd_io_समय1,
		       माप(data->dasd_io_समय1));
		स_नकल(data->dasd_io_समय2, block->profile.data->dasd_io_समय2,
		       माप(data->dasd_io_समय2));
		स_नकल(data->dasd_io_समय2ps,
		       block->profile.data->dasd_io_समय2ps,
		       माप(data->dasd_io_समय2ps));
		स_नकल(data->dasd_io_समय3, block->profile.data->dasd_io_समय3,
		       माप(data->dasd_io_समय3));
		स_नकल(data->dasd_io_nr_req,
		       block->profile.data->dasd_io_nr_req,
		       माप(data->dasd_io_nr_req));
		spin_unlock_bh(&block->profile.lock);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&block->profile.lock);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (copy_to_user(argp, data, माप(*data)))
		rc = -EFAULT;
out:
	kमुक्त(data);
	वापस rc;
पूर्ण
#अन्यथा
अटल पूर्णांक dasd_ioctl_reset_profile(काष्ठा dasd_block *block)
अणु
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक dasd_ioctl_पढ़ो_profile(काष्ठा dasd_block *block, व्योम __user *argp)
अणु
	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर

/*
 * Return dasd inक्रमmation. Used क्रम BIODASDINFO and BIODASDINFO2.
 */
अटल पूर्णांक __dasd_ioctl_inक्रमmation(काष्ठा dasd_block *block,
		काष्ठा dasd_inक्रमmation2_t *dasd_info)
अणु
	काष्ठा subchannel_id sch_id;
	काष्ठा ccw_dev_id dev_id;
	काष्ठा dasd_device *base;
	काष्ठा ccw_device *cdev;
	काष्ठा list_head *l;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	base = block->base;
	अगर (!base->discipline || !base->discipline->fill_info)
		वापस -EINVAL;

	rc = base->discipline->fill_info(base, dasd_info);
	अगर (rc)
		वापस rc;

	cdev = base->cdev;
	ccw_device_get_id(cdev, &dev_id);
	ccw_device_get_schid(cdev, &sch_id);

	dasd_info->devno = dev_id.devno;
	dasd_info->schid = sch_id.sch_no;
	dasd_info->cu_type = cdev->id.cu_type;
	dasd_info->cu_model = cdev->id.cu_model;
	dasd_info->dev_type = cdev->id.dev_type;
	dasd_info->dev_model = cdev->id.dev_model;
	dasd_info->status = base->state;
	/*
	 * The खोलो_count is increased क्रम every खोलोer, that includes
	 * the blkdev_get in dasd_scan_partitions.
	 * This must be hidden from user-space.
	 */
	dasd_info->खोलो_count = atomic_पढ़ो(&block->खोलो_count);
	अगर (!block->bdev)
		dasd_info->खोलो_count++;

	/*
	 * check अगर device is really क्रमmatted
	 * LDL / CDL was वापसed by 'fill_info'
	 */
	अगर ((base->state < DASD_STATE_READY) ||
	    (dasd_check_blocksize(block->bp_block)))
		dasd_info->क्रमmat = DASD_FORMAT_NONE;

	dasd_info->features |=
		((base->features & DASD_FEATURE_READONLY) != 0);

	स_नकल(dasd_info->type, base->discipline->name, 4);

	spin_lock_irqsave(&block->queue_lock, flags);
	list_क्रम_each(l, &base->ccw_queue)
		dasd_info->chanq_len++;
	spin_unlock_irqrestore(&block->queue_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक dasd_ioctl_inक्रमmation(काष्ठा dasd_block *block, व्योम __user *argp,
		माप_प्रकार copy_size)
अणु
	काष्ठा dasd_inक्रमmation2_t *dasd_info;
	पूर्णांक error;

	dasd_info = kzalloc(माप(*dasd_info), GFP_KERNEL);
	अगर (!dasd_info)
		वापस -ENOMEM;

	error = __dasd_ioctl_inक्रमmation(block, dasd_info);
	अगर (!error && copy_to_user(argp, dasd_info, copy_size))
		error = -EFAULT;
	kमुक्त(dasd_info);
	वापस error;
पूर्ण

/*
 * Set पढ़ो only
 */
पूर्णांक dasd_set_पढ़ो_only(काष्ठा block_device *bdev, bool ro)
अणु
	काष्ठा dasd_device *base;
	पूर्णांक rc;

	/* करो not manipulate hardware state क्रम partitions */
	अगर (bdev_is_partition(bdev))
		वापस 0;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;
	अगर (!ro && test_bit(DASD_FLAG_DEVICE_RO, &base->flags))
		rc = -EROFS;
	अन्यथा
		rc = dasd_set_feature(base->cdev, DASD_FEATURE_READONLY, ro);
	dasd_put_device(base);
	वापस rc;
पूर्ण

अटल पूर्णांक dasd_ioctl_पढ़ोall_cmb(काष्ठा dasd_block *block, अचिन्हित पूर्णांक cmd,
				  काष्ठा cmbdata __user *argp)
अणु
	माप_प्रकार size = _IOC_SIZE(cmd);
	काष्ठा cmbdata data;
	पूर्णांक ret;

	ret = cmf_पढ़ोall(block->base->cdev, &data);
	अगर (!ret && copy_to_user(argp, &data, min(size, माप(*argp))))
		वापस -EFAULT;
	वापस ret;
पूर्ण

पूर्णांक dasd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
	       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dasd_block *block;
	काष्ठा dasd_device *base;
	व्योम __user *argp;
	पूर्णांक rc;

	अगर (is_compat_task())
		argp = compat_ptr(arg);
	अन्यथा
		argp = (व्योम __user *)arg;

	अगर ((_IOC_सूची(cmd) != _IOC_NONE) && !arg) अणु
		PRINT_DEBUG("empty data ptr");
		वापस -EINVAL;
	पूर्ण

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;
	block = base->block;
	rc = 0;
	चयन (cmd) अणु
	हाल BIODASDDISABLE:
		rc = dasd_ioctl_disable(bdev);
		अवरोध;
	हाल BIODASDENABLE:
		rc = dasd_ioctl_enable(bdev);
		अवरोध;
	हाल BIODASDQUIESCE:
		rc = dasd_ioctl_quiesce(block);
		अवरोध;
	हाल BIODASDRESUME:
		rc = dasd_ioctl_resume(block);
		अवरोध;
	हाल BIODASDABORTIO:
		rc = dasd_ioctl_पातio(block);
		अवरोध;
	हाल BIODASDALLOWIO:
		rc = dasd_ioctl_allowio(block);
		अवरोध;
	हाल BIODASDFMT:
		rc = dasd_ioctl_क्रमmat(bdev, argp);
		अवरोध;
	हाल BIODASDCHECKFMT:
		rc = dasd_ioctl_check_क्रमmat(bdev, argp);
		अवरोध;
	हाल BIODASDINFO:
		rc = dasd_ioctl_inक्रमmation(block, argp,
				माप(काष्ठा dasd_inक्रमmation_t));
		अवरोध;
	हाल BIODASDINFO2:
		rc = dasd_ioctl_inक्रमmation(block, argp,
				माप(काष्ठा dasd_inक्रमmation2_t));
		अवरोध;
	हाल BIODASDPRRD:
		rc = dasd_ioctl_पढ़ो_profile(block, argp);
		अवरोध;
	हाल BIODASDPRRST:
		rc = dasd_ioctl_reset_profile(block);
		अवरोध;
	हाल DASDAPIVER:
		rc = dasd_ioctl_api_version(argp);
		अवरोध;
	हाल BIODASDCMFENABLE:
		rc = enable_cmf(base->cdev);
		अवरोध;
	हाल BIODASDCMFDISABLE:
		rc = disable_cmf(base->cdev);
		अवरोध;
	हाल BIODASDREADALLCMB:
		rc = dasd_ioctl_पढ़ोall_cmb(block, cmd, argp);
		अवरोध;
	हाल BIODASDRAS:
		rc = dasd_ioctl_release_space(bdev, argp);
		अवरोध;
	शेष:
		/* अगर the discipline has an ioctl method try it. */
		rc = -ENOTTY;
		अगर (base->discipline->ioctl)
			rc = base->discipline->ioctl(block, cmd, argp);
	पूर्ण
	dasd_put_device(base);
	वापस rc;
पूर्ण


/**
 * dasd_biodasdinfo() - fill out the dasd inक्रमmation काष्ठाure
 * @disk [in]: poपूर्णांकer to gendisk काष्ठाure that references a DASD
 * @info [out]: poपूर्णांकer to the dasd_inक्रमmation2_t काष्ठाure
 *
 * Provide access to DASD specअगरic inक्रमmation.
 * The gendisk काष्ठाure is checked अगर it beदीर्घs to the DASD driver by
 * comparing the gendisk->fops poपूर्णांकer.
 * If it करोes not beदीर्घ to the DASD driver -EINVAL is वापसed.
 * Otherwise the provided dasd_inक्रमmation2_t काष्ठाure is filled out.
 *
 * Returns:
 *   %0 on success and a negative error value on failure.
 */
पूर्णांक dasd_biodasdinfo(काष्ठा gendisk *disk, काष्ठा dasd_inक्रमmation2_t *info)
अणु
	काष्ठा dasd_device *base;
	पूर्णांक error;

	अगर (disk->fops != &dasd_device_operations)
		वापस -EINVAL;

	base = dasd_device_from_gendisk(disk);
	अगर (!base)
		वापस -ENODEV;
	error = __dasd_ioctl_inक्रमmation(base->block, info);
	dasd_put_device(base);
	वापस error;
पूर्ण
/* export that symbol_get in partition detection is possible */
EXPORT_SYMBOL_GPL(dasd_biodasdinfo);
