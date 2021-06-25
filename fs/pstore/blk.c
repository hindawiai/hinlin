<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implements pstore backend driver that ग_लिखो to block (or non-block) storage
 * devices, using the pstore/zone API.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "../../block/blk.h"
#समावेश <linux/blkdev.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pstore_blk.h>
#समावेश <linux/mount.h>
#समावेश <linux/uपन.स>

अटल दीर्घ kmsg_size = CONFIG_PSTORE_BLK_KMSG_SIZE;
module_param(kmsg_size, दीर्घ, 0400);
MODULE_PARM_DESC(kmsg_size, "kmsg dump record size in kbytes");

अटल पूर्णांक max_reason = CONFIG_PSTORE_BLK_MAX_REASON;
module_param(max_reason, पूर्णांक, 0400);
MODULE_PARM_DESC(max_reason,
		 "maximum reason for kmsg dump (default 2: Oops and Panic)");

#अगर IS_ENABLED(CONFIG_PSTORE_PMSG)
अटल दीर्घ pmsg_size = CONFIG_PSTORE_BLK_PMSG_SIZE;
#अन्यथा
अटल दीर्घ pmsg_size = -1;
#पूर्ण_अगर
module_param(pmsg_size, दीर्घ, 0400);
MODULE_PARM_DESC(pmsg_size, "pmsg size in kbytes");

#अगर IS_ENABLED(CONFIG_PSTORE_CONSOLE)
अटल दीर्घ console_size = CONFIG_PSTORE_BLK_CONSOLE_SIZE;
#अन्यथा
अटल दीर्घ console_size = -1;
#पूर्ण_अगर
module_param(console_size, दीर्घ, 0400);
MODULE_PARM_DESC(console_size, "console size in kbytes");

#अगर IS_ENABLED(CONFIG_PSTORE_FTRACE)
अटल दीर्घ ftrace_size = CONFIG_PSTORE_BLK_FTRACE_SIZE;
#अन्यथा
अटल दीर्घ ftrace_size = -1;
#पूर्ण_अगर
module_param(ftrace_size, दीर्घ, 0400);
MODULE_PARM_DESC(ftrace_size, "ftrace size in kbytes");

अटल bool best_efक्रमt;
module_param(best_efक्रमt, bool, 0400);
MODULE_PARM_DESC(best_efक्रमt, "use best effort to write (i.e. do not require storage driver pstore support, default: off)");

/*
 * blkdev - the block device to use क्रम pstore storage
 *
 * Usually, this will be a partition of a block device.
 *
 * blkdev accepts the following variants:
 * 1) <hex_major><hex_minor> device number in hexadecimal representation,
 *    with no leading 0x, क्रम example b302.
 * 2) /dev/<disk_name> represents the device number of disk
 * 3) /dev/<disk_name><decimal> represents the device number
 *    of partition - device number of disk plus the partition number
 * 4) /dev/<disk_name>p<decimal> - same as the above, that क्रमm is
 *    used when disk name of partitioned disk ends on a digit.
 * 5) PARTUUID=00112233-4455-6677-8899-AABBCCDDEEFF representing the
 *    unique id of a partition अगर the partition table provides it.
 *    The UUID may be either an EFI/GPT UUID, or refer to an MSDOS
 *    partition using the क्रमmat SSSSSSSS-PP, where SSSSSSSS is a zero-
 *    filled hex representation of the 32-bit "NT disk signature", and PP
 *    is a zero-filled hex representation of the 1-based partition number.
 * 6) PARTUUID=<UUID>/PARTNROFF=<पूर्णांक> to select a partition in relation to
 *    a partition with a known unique id.
 * 7) <major>:<minor> major and minor number of the device separated by
 *    a colon.
 */
अटल अक्षर blkdev[80] = CONFIG_PSTORE_BLK_BLKDEV;
module_param_string(blkdev, blkdev, 80, 0400);
MODULE_PARM_DESC(blkdev, "block device for pstore storage");

/*
 * All globals must only be accessed under the pstore_blk_lock
 * during the रेजिस्टर/unरेजिस्टर functions.
 */
अटल DEFINE_MUTEX(pstore_blk_lock);
अटल काष्ठा block_device *psblk_bdev;
अटल काष्ठा pstore_zone_info *pstore_zone_info;

काष्ठा bdev_info अणु
	dev_t devt;
	sector_t nr_sects;
	sector_t start_sect;
पूर्ण;

#घोषणा check_size(name, alignsize) (अणु				\
	दीर्घ _##name_ = (name);					\
	_##name_ = _##name_ <= 0 ? 0 : (_##name_ * 1024);	\
	अगर (_##name_ & ((alignsize) - 1)) अणु			\
		pr_info(#name " must align to %d\n",		\
				(alignsize));			\
		_##name_ = ALIGN(name, (alignsize));		\
	पूर्ण							\
	_##name_;						\
पूर्ण)

अटल पूर्णांक __रेजिस्टर_pstore_device(काष्ठा pstore_device_info *dev)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&pstore_blk_lock);

	अगर (!dev || !dev->total_size || !dev->पढ़ो || !dev->ग_लिखो)
		वापस -EINVAL;

	/* someone alपढ़ोy रेजिस्टरed beक्रमe */
	अगर (pstore_zone_info)
		वापस -EBUSY;

	pstore_zone_info = kzalloc(माप(काष्ठा pstore_zone_info), GFP_KERNEL);
	अगर (!pstore_zone_info)
		वापस -ENOMEM;

	/* zero means not limit on which backends to attempt to store. */
	अगर (!dev->flags)
		dev->flags = अच_पूर्णांक_उच्च;

#घोषणा verअगरy_size(name, alignsize, enabled) अणु				\
		दीर्घ _##name_;						\
		अगर (enabled)						\
			_##name_ = check_size(name, alignsize);		\
		अन्यथा							\
			_##name_ = 0;					\
		name = _##name_ / 1024;					\
		pstore_zone_info->name = _##name_;			\
	पूर्ण

	verअगरy_size(kmsg_size, 4096, dev->flags & PSTORE_FLAGS_DMESG);
	verअगरy_size(pmsg_size, 4096, dev->flags & PSTORE_FLAGS_PMSG);
	verअगरy_size(console_size, 4096, dev->flags & PSTORE_FLAGS_CONSOLE);
	verअगरy_size(ftrace_size, 4096, dev->flags & PSTORE_FLAGS_FTRACE);
#अघोषित verअगरy_size

	pstore_zone_info->total_size = dev->total_size;
	pstore_zone_info->max_reason = max_reason;
	pstore_zone_info->पढ़ो = dev->पढ़ो;
	pstore_zone_info->ग_लिखो = dev->ग_लिखो;
	pstore_zone_info->erase = dev->erase;
	pstore_zone_info->panic_ग_लिखो = dev->panic_ग_लिखो;
	pstore_zone_info->name = KBUILD_MODNAME;
	pstore_zone_info->owner = THIS_MODULE;

	ret = रेजिस्टर_pstore_zone(pstore_zone_info);
	अगर (ret) अणु
		kमुक्त(pstore_zone_info);
		pstore_zone_info = शून्य;
	पूर्ण
	वापस ret;
पूर्ण
/**
 * रेजिस्टर_pstore_device() - रेजिस्टर non-block device to pstore/blk
 *
 * @dev: non-block device inक्रमmation
 *
 * Return:
 * * 0		- OK
 * * Others	- something error.
 */
पूर्णांक रेजिस्टर_pstore_device(काष्ठा pstore_device_info *dev)
अणु
	पूर्णांक ret;

	mutex_lock(&pstore_blk_lock);
	ret = __रेजिस्टर_pstore_device(dev);
	mutex_unlock(&pstore_blk_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_pstore_device);

अटल व्योम __unरेजिस्टर_pstore_device(काष्ठा pstore_device_info *dev)
अणु
	lockdep_निश्चित_held(&pstore_blk_lock);
	अगर (pstore_zone_info && pstore_zone_info->पढ़ो == dev->पढ़ो) अणु
		unरेजिस्टर_pstore_zone(pstore_zone_info);
		kमुक्त(pstore_zone_info);
		pstore_zone_info = शून्य;
	पूर्ण
पूर्ण

/**
 * unरेजिस्टर_pstore_device() - unरेजिस्टर non-block device from pstore/blk
 *
 * @dev: non-block device inक्रमmation
 */
व्योम unरेजिस्टर_pstore_device(काष्ठा pstore_device_info *dev)
अणु
	mutex_lock(&pstore_blk_lock);
	__unरेजिस्टर_pstore_device(dev);
	mutex_unlock(&pstore_blk_lock);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_pstore_device);

/**
 * psblk_get_bdev() - खोलो block device
 *
 * @holder:	Exclusive holder identअगरier
 * @info:	Inक्रमmation about bdev to fill in
 *
 * Return: poपूर्णांकer to block device on success and others on error.
 *
 * On success, the वापसed block_device has reference count of one.
 */
अटल काष्ठा block_device *psblk_get_bdev(व्योम *holder,
					   काष्ठा bdev_info *info)
अणु
	काष्ठा block_device *bdev = ERR_PTR(-ENODEV);
	भ_शेषe_t mode = FMODE_READ | FMODE_WRITE;
	sector_t nr_sects;

	lockdep_निश्चित_held(&pstore_blk_lock);

	अगर (pstore_zone_info)
		वापस ERR_PTR(-EBUSY);

	अगर (!blkdev[0])
		वापस ERR_PTR(-ENODEV);

	अगर (holder)
		mode |= FMODE_EXCL;
	bdev = blkdev_get_by_path(blkdev, mode, holder);
	अगर (IS_ERR(bdev)) अणु
		dev_t devt;

		devt = name_to_dev_t(blkdev);
		अगर (devt == 0)
			वापस ERR_PTR(-ENODEV);
		bdev = blkdev_get_by_dev(devt, mode, holder);
		अगर (IS_ERR(bdev))
			वापस bdev;
	पूर्ण

	nr_sects = bdev_nr_sectors(bdev);
	अगर (!nr_sects) अणु
		pr_err("not enough space for '%s'\n", blkdev);
		blkdev_put(bdev, mode);
		वापस ERR_PTR(-ENOSPC);
	पूर्ण

	अगर (info) अणु
		info->devt = bdev->bd_dev;
		info->nr_sects = nr_sects;
		info->start_sect = get_start_sect(bdev);
	पूर्ण

	वापस bdev;
पूर्ण

अटल व्योम psblk_put_bdev(काष्ठा block_device *bdev, व्योम *holder)
अणु
	भ_शेषe_t mode = FMODE_READ | FMODE_WRITE;

	lockdep_निश्चित_held(&pstore_blk_lock);

	अगर (!bdev)
		वापस;

	अगर (holder)
		mode |= FMODE_EXCL;
	blkdev_put(bdev, mode);
पूर्ण

अटल sमाप_प्रकार psblk_generic_blk_पढ़ो(अक्षर *buf, माप_प्रकार bytes, loff_t pos)
अणु
	काष्ठा block_device *bdev = psblk_bdev;
	काष्ठा file file;
	काष्ठा kiocb kiocb;
	काष्ठा iov_iter iter;
	काष्ठा kvec iov = अणु.iov_base = buf, .iov_len = bytesपूर्ण;

	अगर (!bdev)
		वापस -ENODEV;

	स_रखो(&file, 0, माप(काष्ठा file));
	file.f_mapping = bdev->bd_inode->i_mapping;
	file.f_flags = O_DSYNC | __O_SYNC | O_NOATIME;
	file.f_inode = bdev->bd_inode;
	file_ra_state_init(&file.f_ra, file.f_mapping);

	init_sync_kiocb(&kiocb, &file);
	kiocb.ki_pos = pos;
	iov_iter_kvec(&iter, READ, &iov, 1, bytes);

	वापस generic_file_पढ़ो_iter(&kiocb, &iter);
पूर्ण

अटल sमाप_प्रकार psblk_generic_blk_ग_लिखो(स्थिर अक्षर *buf, माप_प्रकार bytes,
		loff_t pos)
अणु
	काष्ठा block_device *bdev = psblk_bdev;
	काष्ठा iov_iter iter;
	काष्ठा kiocb kiocb;
	काष्ठा file file;
	sमाप_प्रकार ret;
	काष्ठा kvec iov = अणु.iov_base = (व्योम *)buf, .iov_len = bytesपूर्ण;

	अगर (!bdev)
		वापस -ENODEV;

	/* Console/Ftrace backend may handle buffer until flush dirty zones */
	अगर (in_पूर्णांकerrupt() || irqs_disabled())
		वापस -EBUSY;

	स_रखो(&file, 0, माप(काष्ठा file));
	file.f_mapping = bdev->bd_inode->i_mapping;
	file.f_flags = O_DSYNC | __O_SYNC | O_NOATIME;
	file.f_inode = bdev->bd_inode;

	init_sync_kiocb(&kiocb, &file);
	kiocb.ki_pos = pos;
	iov_iter_kvec(&iter, WRITE, &iov, 1, bytes);

	inode_lock(bdev->bd_inode);
	ret = generic_ग_लिखो_checks(&kiocb, &iter);
	अगर (ret > 0)
		ret = generic_perक्रमm_ग_लिखो(&file, &iter, pos);
	inode_unlock(bdev->bd_inode);

	अगर (likely(ret > 0)) अणु
		स्थिर काष्ठा file_operations f_op = अणु.fsync = blkdev_fsyncपूर्ण;

		file.f_op = &f_op;
		kiocb.ki_pos += ret;
		ret = generic_ग_लिखो_sync(&kiocb, ret);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This takes its configuration only from the module parameters now.
 * See psblk_get_bdev() and blkdev.
 */
अटल पूर्णांक __रेजिस्टर_pstore_blk(व्योम)
अणु
	अक्षर bdev_name[BDEVNAME_SIZE];
	काष्ठा block_device *bdev;
	काष्ठा pstore_device_info dev;
	काष्ठा bdev_info binfo;
	व्योम *holder = blkdev;
	पूर्णांक ret = -ENODEV;

	lockdep_निश्चित_held(&pstore_blk_lock);

	/* hold bdev exclusively */
	स_रखो(&binfo, 0, माप(binfo));
	bdev = psblk_get_bdev(holder, &binfo);
	अगर (IS_ERR(bdev)) अणु
		pr_err("failed to open '%s'!\n", blkdev);
		वापस PTR_ERR(bdev);
	पूर्ण

	/* only allow driver matching the @blkdev */
	अगर (!binfo.devt) अणु
		pr_debug("no major\n");
		ret = -ENODEV;
		जाओ err_put_bdev;
	पूर्ण

	/* psblk_bdev must be asचिन्हित beक्रमe रेजिस्टर to pstore/blk */
	psblk_bdev = bdev;

	स_रखो(&dev, 0, माप(dev));
	dev.total_size = binfo.nr_sects << SECTOR_SHIFT;
	dev.पढ़ो = psblk_generic_blk_पढ़ो;
	dev.ग_लिखो = psblk_generic_blk_ग_लिखो;

	ret = __रेजिस्टर_pstore_device(&dev);
	अगर (ret)
		जाओ err_put_bdev;

	bdevname(bdev, bdev_name);
	pr_info("attached %s (no dedicated panic_write!)\n", bdev_name);
	वापस 0;

err_put_bdev:
	psblk_bdev = शून्य;
	psblk_put_bdev(bdev, holder);
	वापस ret;
पूर्ण

अटल व्योम __unरेजिस्टर_pstore_blk(अचिन्हित पूर्णांक major)
अणु
	काष्ठा pstore_device_info dev = अणु .पढ़ो = psblk_generic_blk_पढ़ो पूर्ण;
	व्योम *holder = blkdev;

	lockdep_निश्चित_held(&pstore_blk_lock);
	अगर (psblk_bdev && MAJOR(psblk_bdev->bd_dev) == major) अणु
		__unरेजिस्टर_pstore_device(&dev);
		psblk_put_bdev(psblk_bdev, holder);
		psblk_bdev = शून्य;
	पूर्ण
पूर्ण

/* get inक्रमmation of pstore/blk */
पूर्णांक pstore_blk_get_config(काष्ठा pstore_blk_config *info)
अणु
	म_नकलन(info->device, blkdev, 80);
	info->max_reason = max_reason;
	info->kmsg_size = check_size(kmsg_size, 4096);
	info->pmsg_size = check_size(pmsg_size, 4096);
	info->ftrace_size = check_size(ftrace_size, 4096);
	info->console_size = check_size(console_size, 4096);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pstore_blk_get_config);

अटल पूर्णांक __init pstore_blk_init(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&pstore_blk_lock);
	अगर (!pstore_zone_info && best_efक्रमt && blkdev[0])
		ret = __रेजिस्टर_pstore_blk();
	mutex_unlock(&pstore_blk_lock);

	वापस ret;
पूर्ण
late_initcall(pstore_blk_init);

अटल व्योम __निकास pstore_blk_निकास(व्योम)
अणु
	mutex_lock(&pstore_blk_lock);
	अगर (psblk_bdev)
		__unरेजिस्टर_pstore_blk(MAJOR(psblk_bdev->bd_dev));
	अन्यथा अणु
		काष्ठा pstore_device_info dev = अणु पूर्ण;

		अगर (pstore_zone_info)
			dev.पढ़ो = pstore_zone_info->पढ़ो;
		__unरेजिस्टर_pstore_device(&dev);
	पूर्ण
	mutex_unlock(&pstore_blk_lock);
पूर्ण
module_निकास(pstore_blk_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WeiXiong Liao <liaoweixiong@allwinnertech.com>");
MODULE_AUTHOR("Kees Cook <keescook@chromium.org>");
MODULE_DESCRIPTION("pstore backend for block devices");
