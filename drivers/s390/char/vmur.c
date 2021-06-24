<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम System z and s390 unit record devices
 * (z/VM भव punch, पढ़ोer, prपूर्णांकer)
 *
 * Copyright IBM Corp. 2001, 2009
 * Authors: Malcolm Beattie <beattiem@uk.ibm.com>
 *	    Michael Holzheu <holzheu@de.ibm.com>
 *	    Frank Munzert <munzert@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "vmur"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/diag.h>

#समावेश "vmur.h"

/*
 * Driver overview
 *
 * Unit record device support is implemented as a अक्षरacter device driver.
 * We can fit at least 16 bits पूर्णांकo a device minor number and use the
 * simple method of mapping a अक्षरacter device number with minor abcd
 * to the unit record device with devno abcd.
 * I/O to भव unit record devices is handled as follows:
 * Reads: Diagnose code 0x14 (input spool file manipulation)
 * is used to पढ़ो spool data page-wise.
 * Writes: The CCW used is WRITE_CCW_CMD (0x01). The device's record length
 * is available by पढ़ोing sysfs attr reclen. Each ग_लिखो() to the device
 * must specअगरy an पूर्णांकegral multiple (maximal 511) of reclen.
 */

अटल अक्षर ur_banner[] = "z/VM virtual unit record device driver";

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("s390 z/VM virtual unit record device driver");
MODULE_LICENSE("GPL");

अटल dev_t ur_first_dev_maj_min;
अटल काष्ठा class *vmur_class;
अटल काष्ठा debug_info *vmur_dbf;

/* We put the device's record length (क्रम ग_लिखोs) in the driver_info field */
अटल काष्ठा ccw_device_id ur_ids[] = अणु
	अणु CCWDEV_CU_DI(READER_PUNCH_DEVTYPE, 80) पूर्ण,
	अणु CCWDEV_CU_DI(PRINTER_DEVTYPE, 132) पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(ccw, ur_ids);

अटल पूर्णांक ur_probe(काष्ठा ccw_device *cdev);
अटल व्योम ur_हटाओ(काष्ठा ccw_device *cdev);
अटल पूर्णांक ur_set_online(काष्ठा ccw_device *cdev);
अटल पूर्णांक ur_set_offline(काष्ठा ccw_device *cdev);

अटल काष्ठा ccw_driver ur_driver = अणु
	.driver = अणु
		.name	= "vmur",
		.owner	= THIS_MODULE,
	पूर्ण,
	.ids		= ur_ids,
	.probe		= ur_probe,
	.हटाओ		= ur_हटाओ,
	.set_online	= ur_set_online,
	.set_offline	= ur_set_offline,
	.पूर्णांक_class	= IRQIO_VMR,
पूर्ण;

अटल DEFINE_MUTEX(vmur_mutex);

/*
 * Allocation, मुक्तing, getting and putting of urdev काष्ठाures
 *
 * Each ur device (urd) contains a reference to its corresponding ccw device
 * (cdev) using the urd->cdev poपूर्णांकer. Each ccw device has a reference to the
 * ur device using dev_get_drvdata(&cdev->dev) poपूर्णांकer.
 *
 * urd references:
 * - ur_probe माला_लो a urd reference, ur_हटाओ drops the reference
 *   dev_get_drvdata(&cdev->dev)
 * - ur_खोलो माला_लो a urd reference, ur_release drops the reference
 *   (urf->urd)
 *
 * cdev references:
 * - urdev_alloc get a cdev reference (urd->cdev)
 * - urdev_मुक्त drops the cdev reference (urd->cdev)
 *
 * Setting and clearing of dev_get_drvdata(&cdev->dev) is रक्षित by the ccwdev lock
 */
अटल काष्ठा urdev *urdev_alloc(काष्ठा ccw_device *cdev)
अणु
	काष्ठा urdev *urd;

	urd = kzalloc(माप(काष्ठा urdev), GFP_KERNEL);
	अगर (!urd)
		वापस शून्य;
	urd->reclen = cdev->id.driver_info;
	ccw_device_get_id(cdev, &urd->dev_id);
	mutex_init(&urd->io_mutex);
	init_रुकोqueue_head(&urd->रुको);
	spin_lock_init(&urd->खोलो_lock);
	refcount_set(&urd->ref_count,  1);
	urd->cdev = cdev;
	get_device(&cdev->dev);
	वापस urd;
पूर्ण

अटल व्योम urdev_मुक्त(काष्ठा urdev *urd)
अणु
	TRACE("urdev_free: %p\n", urd);
	अगर (urd->cdev)
		put_device(&urd->cdev->dev);
	kमुक्त(urd);
पूर्ण

अटल व्योम urdev_get(काष्ठा urdev *urd)
अणु
	refcount_inc(&urd->ref_count);
पूर्ण

अटल काष्ठा urdev *urdev_get_from_cdev(काष्ठा ccw_device *cdev)
अणु
	काष्ठा urdev *urd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	urd = dev_get_drvdata(&cdev->dev);
	अगर (urd)
		urdev_get(urd);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	वापस urd;
पूर्ण

अटल काष्ठा urdev *urdev_get_from_devno(u16 devno)
अणु
	अक्षर bus_id[16];
	काष्ठा ccw_device *cdev;
	काष्ठा urdev *urd;

	प्र_लिखो(bus_id, "0.0.%04x", devno);
	cdev = get_ccwdev_by_busid(&ur_driver, bus_id);
	अगर (!cdev)
		वापस शून्य;
	urd = urdev_get_from_cdev(cdev);
	put_device(&cdev->dev);
	वापस urd;
पूर्ण

अटल व्योम urdev_put(काष्ठा urdev *urd)
अणु
	अगर (refcount_dec_and_test(&urd->ref_count))
		urdev_मुक्त(urd);
पूर्ण

/*
 * Low-level functions to करो I/O to a ur device.
 *     alloc_chan_prog
 *     मुक्त_chan_prog
 *     करो_ur_io
 *     ur_पूर्णांक_handler
 *
 * alloc_chan_prog allocates and builds the channel program
 * मुक्त_chan_prog मुक्तs memory of the channel program
 *
 * करो_ur_io issues the channel program to the device and blocks रुकोing
 * on a completion event it publishes at urd->io_करोne. The function
 * serialises itself on the device's mutex so that only one I/O
 * is issued at a समय (and that I/O is synchronous).
 *
 * ur_पूर्णांक_handler catches the "I/O done" पूर्णांकerrupt, ग_लिखोs the
 * subchannel status word पूर्णांकo the scsw member of the urdev काष्ठाure
 * and complete()s the io_करोne to wake the रुकोing करो_ur_io.
 *
 * The caller of करो_ur_io is responsible क्रम kमुक्त()ing the channel program
 * address poपूर्णांकer that alloc_chan_prog वापसed.
 */

अटल व्योम मुक्त_chan_prog(काष्ठा ccw1 *cpa)
अणु
	काष्ठा ccw1 *ptr = cpa;

	जबतक (ptr->cda) अणु
		kमुक्त((व्योम *)(addr_t) ptr->cda);
		ptr++;
	पूर्ण
	kमुक्त(cpa);
पूर्ण

/*
 * alloc_chan_prog
 * The channel program we use is ग_लिखो commands chained together
 * with a final NOP CCW command-chained on (which ensures that CE and DE
 * are presented together in a single पूर्णांकerrupt instead of as separate
 * पूर्णांकerrupts unless an incorrect length indication kicks in first). The
 * data length in each CCW is reclen.
 */
अटल काष्ठा ccw1 *alloc_chan_prog(स्थिर अक्षर __user *ubuf, पूर्णांक rec_count,
				    पूर्णांक reclen)
अणु
	काष्ठा ccw1 *cpa;
	व्योम *kbuf;
	पूर्णांक i;

	TRACE("alloc_chan_prog(%p, %i, %i)\n", ubuf, rec_count, reclen);

	/*
	 * We chain a NOP onto the ग_लिखोs to क्रमce CE+DE together.
	 * That means we allocate room क्रम CCWs to cover count/reclen
	 * records plus a NOP.
	 */
	cpa = kसुस्मृति(rec_count + 1, माप(काष्ठा ccw1),
		      GFP_KERNEL | GFP_DMA);
	अगर (!cpa)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < rec_count; i++) अणु
		cpa[i].cmd_code = WRITE_CCW_CMD;
		cpa[i].flags = CCW_FLAG_CC | CCW_FLAG_SLI;
		cpa[i].count = reclen;
		kbuf = kदो_स्मृति(reclen, GFP_KERNEL | GFP_DMA);
		अगर (!kbuf) अणु
			मुक्त_chan_prog(cpa);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		cpa[i].cda = (u32)(addr_t) kbuf;
		अगर (copy_from_user(kbuf, ubuf, reclen)) अणु
			मुक्त_chan_prog(cpa);
			वापस ERR_PTR(-EFAULT);
		पूर्ण
		ubuf += reclen;
	पूर्ण
	/* The following NOP CCW क्रमces CE+DE to be presented together */
	cpa[i].cmd_code = CCW_CMD_NOOP;
	वापस cpa;
पूर्ण

अटल पूर्णांक करो_ur_io(काष्ठा urdev *urd, काष्ठा ccw1 *cpa)
अणु
	पूर्णांक rc;
	काष्ठा ccw_device *cdev = urd->cdev;
	DECLARE_COMPLETION_ONSTACK(event);

	TRACE("do_ur_io: cpa=%p\n", cpa);

	rc = mutex_lock_पूर्णांकerruptible(&urd->io_mutex);
	अगर (rc)
		वापस rc;

	urd->io_करोne = &event;

	spin_lock_irq(get_ccwdev_lock(cdev));
	rc = ccw_device_start(cdev, cpa, 1, 0, 0);
	spin_unlock_irq(get_ccwdev_lock(cdev));

	TRACE("do_ur_io: ccw_device_start returned %d\n", rc);
	अगर (rc)
		जाओ out;

	रुको_क्रम_completion(&event);
	TRACE("do_ur_io: I/O complete\n");
	rc = 0;

out:
	mutex_unlock(&urd->io_mutex);
	वापस rc;
पूर्ण

/*
 * ur पूर्णांकerrupt handler, called from the ccw_device layer
 */
अटल व्योम ur_पूर्णांक_handler(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm,
			   काष्ठा irb *irb)
अणु
	काष्ठा urdev *urd;

	अगर (!IS_ERR(irb)) अणु
		TRACE("ur_int_handler: intparm=0x%lx cstat=%02x dstat=%02x res=%u\n",
		      पूर्णांकparm, irb->scsw.cmd.cstat, irb->scsw.cmd.dstat,
		      irb->scsw.cmd.count);
	पूर्ण
	अगर (!पूर्णांकparm) अणु
		TRACE("ur_int_handler: unsolicited interrupt\n");
		वापस;
	पूर्ण
	urd = dev_get_drvdata(&cdev->dev);
	BUG_ON(!urd);
	/* On special conditions irb is an error poपूर्णांकer */
	अगर (IS_ERR(irb))
		urd->io_request_rc = PTR_ERR(irb);
	अन्यथा अगर (irb->scsw.cmd.dstat == (DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		urd->io_request_rc = 0;
	अन्यथा
		urd->io_request_rc = -EIO;

	complete(urd->io_करोne);
पूर्ण

/*
 * reclen sysfs attribute - The record length to be used क्रम ग_लिखो CCWs
 */
अटल sमाप_प्रकार ur_attr_reclen_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा urdev *urd;
	पूर्णांक rc;

	urd = urdev_get_from_cdev(to_ccwdev(dev));
	अगर (!urd)
		वापस -ENODEV;
	rc = प्र_लिखो(buf, "%zu\n", urd->reclen);
	urdev_put(urd);
	वापस rc;
पूर्ण

अटल DEVICE_ATTR(reclen, 0444, ur_attr_reclen_show, शून्य);

अटल पूर्णांक ur_create_attributes(काष्ठा device *dev)
अणु
	वापस device_create_file(dev, &dev_attr_reclen);
पूर्ण

अटल व्योम ur_हटाओ_attributes(काष्ठा device *dev)
अणु
	device_हटाओ_file(dev, &dev_attr_reclen);
पूर्ण

/*
 * diagnose code 0x210 - retrieve device inक्रमmation
 * cc=0  normal completion, we have a real device
 * cc=1  CP paging error
 * cc=2  The भव device exists, but is not associated with a real device
 * cc=3  Invalid device address, or the भव device करोes not exist
 */
अटल पूर्णांक get_urd_class(काष्ठा urdev *urd)
अणु
	अटल काष्ठा diag210 ur_diag210;
	पूर्णांक cc;

	ur_diag210.vrdcdvno = urd->dev_id.devno;
	ur_diag210.vrdclen = माप(काष्ठा diag210);

	cc = diag210(&ur_diag210);
	चयन (cc) अणु
	हाल 0:
		वापस -EOPNOTSUPP;
	हाल 2:
		वापस ur_diag210.vrdcvcla; /* भव device class */
	हाल 3:
		वापस -ENODEV;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * Allocation and मुक्तing of urfile काष्ठाures
 */
अटल काष्ठा urfile *urfile_alloc(काष्ठा urdev *urd)
अणु
	काष्ठा urfile *urf;

	urf = kzalloc(माप(काष्ठा urfile), GFP_KERNEL);
	अगर (!urf)
		वापस शून्य;
	urf->urd = urd;

	TRACE("urfile_alloc: urd=%p urf=%p rl=%zu\n", urd, urf,
	      urf->dev_reclen);

	वापस urf;
पूर्ण

अटल व्योम urfile_मुक्त(काष्ठा urfile *urf)
अणु
	TRACE("urfile_free: urf=%p urd=%p\n", urf, urf->urd);
	kमुक्त(urf);
पूर्ण

/*
 * The fops implementation of the अक्षरacter device driver
 */
अटल sमाप_प्रकार करो_ग_लिखो(काष्ठा urdev *urd, स्थिर अक्षर __user *udata,
			माप_प्रकार count, माप_प्रकार reclen, loff_t *ppos)
अणु
	काष्ठा ccw1 *cpa;
	पूर्णांक rc;

	cpa = alloc_chan_prog(udata, count / reclen, reclen);
	अगर (IS_ERR(cpa))
		वापस PTR_ERR(cpa);

	rc = करो_ur_io(urd, cpa);
	अगर (rc)
		जाओ fail_kमुक्त_cpa;

	अगर (urd->io_request_rc) अणु
		rc = urd->io_request_rc;
		जाओ fail_kमुक्त_cpa;
	पूर्ण
	*ppos += count;
	rc = count;

fail_kमुक्त_cpa:
	मुक्त_chan_prog(cpa);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार ur_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *udata,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा urfile *urf = file->निजी_data;

	TRACE("ur_write: count=%zu\n", count);

	अगर (count == 0)
		वापस 0;

	अगर (count % urf->dev_reclen)
		वापस -EINVAL;	/* count must be a multiple of reclen */

	अगर (count > urf->dev_reclen * MAX_RECS_PER_IO)
		count = urf->dev_reclen * MAX_RECS_PER_IO;

	वापस करो_ग_लिखो(urf->urd, udata, count, urf->dev_reclen, ppos);
पूर्ण

/*
 * diagnose code 0x14 subcode 0x0028 - position spool file to designated
 *				       record
 * cc=0  normal completion
 * cc=2  no file active on the भव पढ़ोer or device not पढ़ोy
 * cc=3  record specअगरied is beyond खातापूर्ण
 */
अटल पूर्णांक diag_position_to_record(पूर्णांक devno, पूर्णांक record)
अणु
	पूर्णांक cc;

	cc = diag14(record, devno, 0x28);
	चयन (cc) अणु
	हाल 0:
		वापस 0;
	हाल 2:
		वापस -ENOMEDIUM;
	हाल 3:
		वापस -ENODATA; /* position beyond end of file */
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * diagnose code 0x14 subcode 0x0000 - पढ़ो next spool file buffer
 * cc=0  normal completion
 * cc=1  खातापूर्ण reached
 * cc=2  no file active on the भव पढ़ोer, and no file eligible
 * cc=3  file alपढ़ोy active on the भव पढ़ोer or specअगरied भव
 *	 पढ़ोer करोes not exist or is not a पढ़ोer
 */
अटल पूर्णांक diag_पढ़ो_file(पूर्णांक devno, अक्षर *buf)
अणु
	पूर्णांक cc;

	cc = diag14((अचिन्हित दीर्घ) buf, devno, 0x00);
	चयन (cc) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		वापस -ENODATA;
	हाल 2:
		वापस -ENOMEDIUM;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार diag14_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf, माप_प्रकार count,
			   loff_t *offs)
अणु
	माप_प्रकार len, copied, res;
	अक्षर *buf;
	पूर्णांक rc;
	u16 reclen;
	काष्ठा urdev *urd;

	urd = ((काष्ठा urfile *) file->निजी_data)->urd;
	reclen = ((काष्ठा urfile *) file->निजी_data)->file_reclen;

	rc = diag_position_to_record(urd->dev_id.devno, *offs / PAGE_SIZE + 1);
	अगर (rc == -ENODATA)
		वापस 0;
	अगर (rc)
		वापस rc;

	len = min((माप_प्रकार) PAGE_SIZE, count);
	buf = (अक्षर *) __get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!buf)
		वापस -ENOMEM;

	copied = 0;
	res = (माप_प्रकार) (*offs % PAGE_SIZE);
	करो अणु
		rc = diag_पढ़ो_file(urd->dev_id.devno, buf);
		अगर (rc == -ENODATA) अणु
			अवरोध;
		पूर्ण
		अगर (rc)
			जाओ fail;
		अगर (reclen && (copied == 0) && (*offs < PAGE_SIZE))
			*((u16 *) &buf[खाता_RECLEN_OFFSET]) = reclen;
		len = min(count - copied, PAGE_SIZE - res);
		अगर (copy_to_user(ubuf + copied, buf + res, len)) अणु
			rc = -EFAULT;
			जाओ fail;
		पूर्ण
		res = 0;
		copied += len;
	पूर्ण जबतक (copied != count);

	*offs += copied;
	rc = copied;
fail:
	मुक्त_page((अचिन्हित दीर्घ) buf);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार ur_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf, माप_प्रकार count,
		       loff_t *offs)
अणु
	काष्ठा urdev *urd;
	पूर्णांक rc;

	TRACE("ur_read: count=%zu ppos=%li\n", count, (अचिन्हित दीर्घ) *offs);

	अगर (count == 0)
		वापस 0;

	urd = ((काष्ठा urfile *) file->निजी_data)->urd;
	rc = mutex_lock_पूर्णांकerruptible(&urd->io_mutex);
	अगर (rc)
		वापस rc;
	rc = diag14_पढ़ो(file, ubuf, count, offs);
	mutex_unlock(&urd->io_mutex);
	वापस rc;
पूर्ण

/*
 * diagnose code 0x14 subcode 0x0fff - retrieve next file descriptor
 * cc=0  normal completion
 * cc=1  no files on पढ़ोer queue or no subsequent file
 * cc=2  spid specअगरied is invalid
 */
अटल पूर्णांक diag_पढ़ो_next_file_info(काष्ठा file_control_block *buf, पूर्णांक spid)
अणु
	पूर्णांक cc;

	cc = diag14((अचिन्हित दीर्घ) buf, spid, 0xfff);
	चयन (cc) अणु
	हाल 0:
		वापस 0;
	शेष:
		वापस -ENODATA;
	पूर्ण
पूर्ण

अटल पूर्णांक verअगरy_uri_device(काष्ठा urdev *urd)
अणु
	काष्ठा file_control_block *fcb;
	अक्षर *buf;
	पूर्णांक rc;

	fcb = kदो_स्मृति(माप(*fcb), GFP_KERNEL | GFP_DMA);
	अगर (!fcb)
		वापस -ENOMEM;

	/* check क्रम empty पढ़ोer device (beginning of chain) */
	rc = diag_पढ़ो_next_file_info(fcb, 0);
	अगर (rc)
		जाओ fail_मुक्त_fcb;

	/* अगर file is in hold status, we करो not पढ़ो it */
	अगर (fcb->file_stat & (FLG_SYSTEM_HOLD | FLG_USER_HOLD)) अणु
		rc = -EPERM;
		जाओ fail_मुक्त_fcb;
	पूर्ण

	/* खोलो file on भव पढ़ोer	*/
	buf = (अक्षर *) __get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!buf) अणु
		rc = -ENOMEM;
		जाओ fail_मुक्त_fcb;
	पूर्ण
	rc = diag_पढ़ो_file(urd->dev_id.devno, buf);
	अगर ((rc != 0) && (rc != -ENODATA)) /* खातापूर्ण करोes not hurt */
		जाओ fail_मुक्त_buf;

	/* check अगर the file on top of the queue is खोलो now */
	rc = diag_पढ़ो_next_file_info(fcb, 0);
	अगर (rc)
		जाओ fail_मुक्त_buf;
	अगर (!(fcb->file_stat & FLG_IN_USE)) अणु
		rc = -EMखाता;
		जाओ fail_मुक्त_buf;
	पूर्ण
	rc = 0;

fail_मुक्त_buf:
	मुक्त_page((अचिन्हित दीर्घ) buf);
fail_मुक्त_fcb:
	kमुक्त(fcb);
	वापस rc;
पूर्ण

अटल पूर्णांक verअगरy_device(काष्ठा urdev *urd)
अणु
	चयन (urd->class) अणु
	हाल DEV_CLASS_UR_O:
		वापस 0; /* no check needed here */
	हाल DEV_CLASS_UR_I:
		वापस verअगरy_uri_device(urd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक get_uri_file_reclen(काष्ठा urdev *urd)
अणु
	काष्ठा file_control_block *fcb;
	पूर्णांक rc;

	fcb = kदो_स्मृति(माप(*fcb), GFP_KERNEL | GFP_DMA);
	अगर (!fcb)
		वापस -ENOMEM;
	rc = diag_पढ़ो_next_file_info(fcb, 0);
	अगर (rc)
		जाओ fail_मुक्त;
	अगर (fcb->file_stat & FLG_CP_DUMP)
		rc = 0;
	अन्यथा
		rc = fcb->rec_len;

fail_मुक्त:
	kमुक्त(fcb);
	वापस rc;
पूर्ण

अटल पूर्णांक get_file_reclen(काष्ठा urdev *urd)
अणु
	चयन (urd->class) अणु
	हाल DEV_CLASS_UR_O:
		वापस 0;
	हाल DEV_CLASS_UR_I:
		वापस get_uri_file_reclen(urd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ur_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	u16 devno;
	काष्ठा urdev *urd;
	काष्ठा urfile *urf;
	अचिन्हित लघु accmode;
	पूर्णांक rc;

	accmode = file->f_flags & O_ACCMODE;

	अगर (accmode == O_RDWR)
		वापस -EACCES;
	/*
	 * We treat the minor number as the devno of the ur device
	 * to find in the driver tree.
	 */
	devno = iminor(file_inode(file));

	urd = urdev_get_from_devno(devno);
	अगर (!urd) अणु
		rc = -ENXIO;
		जाओ out;
	पूर्ण

	spin_lock(&urd->खोलो_lock);
	जबतक (urd->खोलो_flag) अणु
		spin_unlock(&urd->खोलो_lock);
		अगर (file->f_flags & O_NONBLOCK) अणु
			rc = -EBUSY;
			जाओ fail_put;
		पूर्ण
		अगर (रुको_event_पूर्णांकerruptible(urd->रुको, urd->खोलो_flag == 0)) अणु
			rc = -ERESTARTSYS;
			जाओ fail_put;
		पूर्ण
		spin_lock(&urd->खोलो_lock);
	पूर्ण
	urd->खोलो_flag++;
	spin_unlock(&urd->खोलो_lock);

	TRACE("ur_open\n");

	अगर (((accmode == O_RDONLY) && (urd->class != DEV_CLASS_UR_I)) ||
	    ((accmode == O_WRONLY) && (urd->class != DEV_CLASS_UR_O))) अणु
		TRACE("ur_open: unsupported dev class (%d)\n", urd->class);
		rc = -EACCES;
		जाओ fail_unlock;
	पूर्ण

	rc = verअगरy_device(urd);
	अगर (rc)
		जाओ fail_unlock;

	urf = urfile_alloc(urd);
	अगर (!urf) अणु
		rc = -ENOMEM;
		जाओ fail_unlock;
	पूर्ण

	urf->dev_reclen = urd->reclen;
	rc = get_file_reclen(urd);
	अगर (rc < 0)
		जाओ fail_urfile_मुक्त;
	urf->file_reclen = rc;
	file->निजी_data = urf;
	वापस 0;

fail_urfile_मुक्त:
	urfile_मुक्त(urf);
fail_unlock:
	spin_lock(&urd->खोलो_lock);
	urd->खोलो_flag--;
	spin_unlock(&urd->खोलो_lock);
fail_put:
	urdev_put(urd);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ur_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा urfile *urf = file->निजी_data;

	TRACE("ur_release\n");
	spin_lock(&urf->urd->खोलो_lock);
	urf->urd->खोलो_flag--;
	spin_unlock(&urf->urd->खोलो_lock);
	wake_up_पूर्णांकerruptible(&urf->urd->रुको);
	urdev_put(urf->urd);
	urfile_मुक्त(urf);
	वापस 0;
पूर्ण

अटल loff_t ur_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY)
		वापस -ESPIPE; /* seek allowed only क्रम पढ़ोer */
	अगर (offset % PAGE_SIZE)
		वापस -ESPIPE; /* only multiples of 4K allowed */
	वापस no_seek_end_llseek(file, offset, whence);
पूर्ण

अटल स्थिर काष्ठा file_operations ur_fops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = ur_खोलो,
	.release = ur_release,
	.पढ़ो	 = ur_पढ़ो,
	.ग_लिखो	 = ur_ग_लिखो,
	.llseek  = ur_llseek,
पूर्ण;

/*
 * ccw_device infraकाष्ठाure:
 *     ur_probe creates the काष्ठा urdev (with refcount = 1), the device
 *     attributes, sets up the पूर्णांकerrupt handler and validates the भव
 *     unit record device.
 *     ur_हटाओ हटाओs the device attributes and drops the reference to
 *     काष्ठा urdev.
 *
 *     ur_probe, ur_हटाओ, ur_set_online and ur_set_offline are serialized
 *     by the vmur_mutex lock.
 *
 *     urd->अक्षर_device is used as indication that the online function has
 *     been completed successfully.
 */
अटल पूर्णांक ur_probe(काष्ठा ccw_device *cdev)
अणु
	काष्ठा urdev *urd;
	पूर्णांक rc;

	TRACE("ur_probe: cdev=%p\n", cdev);

	mutex_lock(&vmur_mutex);
	urd = urdev_alloc(cdev);
	अगर (!urd) अणु
		rc = -ENOMEM;
		जाओ fail_unlock;
	पूर्ण

	rc = ur_create_attributes(&cdev->dev);
	अगर (rc) अणु
		rc = -ENOMEM;
		जाओ fail_urdev_put;
	पूर्ण
	cdev->handler = ur_पूर्णांक_handler;

	/* validate भव unit record device */
	urd->class = get_urd_class(urd);
	अगर (urd->class < 0) अणु
		rc = urd->class;
		जाओ fail_हटाओ_attr;
	पूर्ण
	अगर ((urd->class != DEV_CLASS_UR_I) && (urd->class != DEV_CLASS_UR_O)) अणु
		rc = -EOPNOTSUPP;
		जाओ fail_हटाओ_attr;
	पूर्ण
	spin_lock_irq(get_ccwdev_lock(cdev));
	dev_set_drvdata(&cdev->dev, urd);
	spin_unlock_irq(get_ccwdev_lock(cdev));

	mutex_unlock(&vmur_mutex);
	वापस 0;

fail_हटाओ_attr:
	ur_हटाओ_attributes(&cdev->dev);
fail_urdev_put:
	urdev_put(urd);
fail_unlock:
	mutex_unlock(&vmur_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक ur_set_online(काष्ठा ccw_device *cdev)
अणु
	काष्ठा urdev *urd;
	पूर्णांक minor, major, rc;
	अक्षर node_id[16];

	TRACE("ur_set_online: cdev=%p\n", cdev);

	mutex_lock(&vmur_mutex);
	urd = urdev_get_from_cdev(cdev);
	अगर (!urd) अणु
		/* ur_हटाओ alपढ़ोy deleted our urd */
		rc = -ENODEV;
		जाओ fail_unlock;
	पूर्ण

	अगर (urd->अक्षर_device) अणु
		/* Another ur_set_online was faster */
		rc = -EBUSY;
		जाओ fail_urdev_put;
	पूर्ण

	minor = urd->dev_id.devno;
	major = MAJOR(ur_first_dev_maj_min);

	urd->अक्षर_device = cdev_alloc();
	अगर (!urd->अक्षर_device) अणु
		rc = -ENOMEM;
		जाओ fail_urdev_put;
	पूर्ण

	urd->अक्षर_device->ops = &ur_fops;
	urd->अक्षर_device->owner = ur_fops.owner;

	rc = cdev_add(urd->अक्षर_device, MKDEV(major, minor), 1);
	अगर (rc)
		जाओ fail_मुक्त_cdev;
	अगर (urd->cdev->id.cu_type == READER_PUNCH_DEVTYPE) अणु
		अगर (urd->class == DEV_CLASS_UR_I)
			प्र_लिखो(node_id, "vmrdr-%s", dev_name(&cdev->dev));
		अगर (urd->class == DEV_CLASS_UR_O)
			प्र_लिखो(node_id, "vmpun-%s", dev_name(&cdev->dev));
	पूर्ण अन्यथा अगर (urd->cdev->id.cu_type == PRINTER_DEVTYPE) अणु
		प्र_लिखो(node_id, "vmprt-%s", dev_name(&cdev->dev));
	पूर्ण अन्यथा अणु
		rc = -EOPNOTSUPP;
		जाओ fail_मुक्त_cdev;
	पूर्ण

	urd->device = device_create(vmur_class, &cdev->dev,
				    urd->अक्षर_device->dev, शून्य, "%s", node_id);
	अगर (IS_ERR(urd->device)) अणु
		rc = PTR_ERR(urd->device);
		TRACE("ur_set_online: device_create rc=%d\n", rc);
		जाओ fail_मुक्त_cdev;
	पूर्ण
	urdev_put(urd);
	mutex_unlock(&vmur_mutex);
	वापस 0;

fail_मुक्त_cdev:
	cdev_del(urd->अक्षर_device);
	urd->अक्षर_device = शून्य;
fail_urdev_put:
	urdev_put(urd);
fail_unlock:
	mutex_unlock(&vmur_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक ur_set_offline_क्रमce(काष्ठा ccw_device *cdev, पूर्णांक क्रमce)
अणु
	काष्ठा urdev *urd;
	पूर्णांक rc;

	TRACE("ur_set_offline: cdev=%p\n", cdev);
	urd = urdev_get_from_cdev(cdev);
	अगर (!urd)
		/* ur_हटाओ alपढ़ोy deleted our urd */
		वापस -ENODEV;
	अगर (!urd->अक्षर_device) अणु
		/* Another ur_set_offline was faster */
		rc = -EBUSY;
		जाओ fail_urdev_put;
	पूर्ण
	अगर (!क्रमce && (refcount_पढ़ो(&urd->ref_count) > 2)) अणु
		/* There is still a user of urd (e.g. ur_खोलो) */
		TRACE("ur_set_offline: BUSY\n");
		rc = -EBUSY;
		जाओ fail_urdev_put;
	पूर्ण
	device_destroy(vmur_class, urd->अक्षर_device->dev);
	cdev_del(urd->अक्षर_device);
	urd->अक्षर_device = शून्य;
	rc = 0;

fail_urdev_put:
	urdev_put(urd);
	वापस rc;
पूर्ण

अटल पूर्णांक ur_set_offline(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक rc;

	mutex_lock(&vmur_mutex);
	rc = ur_set_offline_क्रमce(cdev, 0);
	mutex_unlock(&vmur_mutex);
	वापस rc;
पूर्ण

अटल व्योम ur_हटाओ(काष्ठा ccw_device *cdev)
अणु
	अचिन्हित दीर्घ flags;

	TRACE("ur_remove\n");

	mutex_lock(&vmur_mutex);

	अगर (cdev->online)
		ur_set_offline_क्रमce(cdev, 1);
	ur_हटाओ_attributes(&cdev->dev);

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	urdev_put(dev_get_drvdata(&cdev->dev));
	dev_set_drvdata(&cdev->dev, शून्य);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	mutex_unlock(&vmur_mutex);
पूर्ण

/*
 * Module initialisation and cleanup
 */
अटल पूर्णांक __init ur_init(व्योम)
अणु
	पूर्णांक rc;
	dev_t dev;

	अगर (!MACHINE_IS_VM) अणु
		pr_err("The %s cannot be loaded without z/VM\n",
		       ur_banner);
		वापस -ENODEV;
	पूर्ण

	vmur_dbf = debug_रेजिस्टर("vmur", 4, 1, 4 * माप(दीर्घ));
	अगर (!vmur_dbf)
		वापस -ENOMEM;
	rc = debug_रेजिस्टर_view(vmur_dbf, &debug_प्र_लिखो_view);
	अगर (rc)
		जाओ fail_मुक्त_dbf;

	debug_set_level(vmur_dbf, 6);

	vmur_class = class_create(THIS_MODULE, "vmur");
	अगर (IS_ERR(vmur_class)) अणु
		rc = PTR_ERR(vmur_class);
		जाओ fail_मुक्त_dbf;
	पूर्ण

	rc = ccw_driver_रेजिस्टर(&ur_driver);
	अगर (rc)
		जाओ fail_class_destroy;

	rc = alloc_chrdev_region(&dev, 0, NUM_MINORS, "vmur");
	अगर (rc) अणु
		pr_err("Kernel function alloc_chrdev_region failed with "
		       "error code %d\n", rc);
		जाओ fail_unरेजिस्टर_driver;
	पूर्ण
	ur_first_dev_maj_min = MKDEV(MAJOR(dev), 0);

	pr_info("%s loaded.\n", ur_banner);
	वापस 0;

fail_unरेजिस्टर_driver:
	ccw_driver_unरेजिस्टर(&ur_driver);
fail_class_destroy:
	class_destroy(vmur_class);
fail_मुक्त_dbf:
	debug_unरेजिस्टर(vmur_dbf);
	वापस rc;
पूर्ण

अटल व्योम __निकास ur_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(ur_first_dev_maj_min, NUM_MINORS);
	ccw_driver_unरेजिस्टर(&ur_driver);
	class_destroy(vmur_class);
	debug_unरेजिस्टर(vmur_dbf);
	pr_info("%s unloaded.\n", ur_banner);
पूर्ण

module_init(ur_init);
module_निकास(ur_निकास);
