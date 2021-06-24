<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/capability.h>
#समावेश <linux/compat.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fs.h>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/pr.h>
#समावेश <linux/uaccess.h>
#समावेश "blk.h"

अटल पूर्णांक blkpg_करो_ioctl(काष्ठा block_device *bdev,
			  काष्ठा blkpg_partition __user *upart, पूर्णांक op)
अणु
	काष्ठा blkpg_partition p;
	दीर्घ दीर्घ start, length;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (copy_from_user(&p, upart, माप(काष्ठा blkpg_partition)))
		वापस -EFAULT;
	अगर (bdev_is_partition(bdev))
		वापस -EINVAL;

	अगर (p.pno <= 0)
		वापस -EINVAL;

	अगर (op == BLKPG_DEL_PARTITION)
		वापस bdev_del_partition(bdev, p.pno);

	start = p.start >> SECTOR_SHIFT;
	length = p.length >> SECTOR_SHIFT;

	चयन (op) अणु
	हाल BLKPG_ADD_PARTITION:
		/* check अगर partition is aligned to blocksize */
		अगर (p.start & (bdev_logical_block_size(bdev) - 1))
			वापस -EINVAL;
		वापस bdev_add_partition(bdev, p.pno, start, length);
	हाल BLKPG_RESIZE_PARTITION:
		वापस bdev_resize_partition(bdev, p.pno, start, length);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक blkpg_ioctl(काष्ठा block_device *bdev,
		       काष्ठा blkpg_ioctl_arg __user *arg)
अणु
	काष्ठा blkpg_partition __user *udata;
	पूर्णांक op;

	अगर (get_user(op, &arg->op) || get_user(udata, &arg->data))
		वापस -EFAULT;

	वापस blkpg_करो_ioctl(bdev, udata, op);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_blkpg_ioctl_arg अणु
	compat_पूर्णांक_t op;
	compat_पूर्णांक_t flags;
	compat_पूर्णांक_t datalen;
	compat_caddr_t data;
पूर्ण;

अटल पूर्णांक compat_blkpg_ioctl(काष्ठा block_device *bdev,
			      काष्ठा compat_blkpg_ioctl_arg __user *arg)
अणु
	compat_caddr_t udata;
	पूर्णांक op;

	अगर (get_user(op, &arg->op) || get_user(udata, &arg->data))
		वापस -EFAULT;

	वापस blkpg_करो_ioctl(bdev, compat_ptr(udata), op);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक blkdev_reपढ़ो_part(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा block_device *पंचांगp;

	अगर (!disk_part_scan_enabled(bdev->bd_disk) || bdev_is_partition(bdev))
		वापस -EINVAL;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (bdev->bd_part_count)
		वापस -EBUSY;

	/*
	 * Reखोलो the device to revalidate the driver state and क्रमce a
	 * partition rescan.
	 */
	mode &= ~FMODE_EXCL;
	set_bit(GD_NEED_PART_SCAN, &bdev->bd_disk->state);

	पंचांगp = blkdev_get_by_dev(bdev->bd_dev, mode, शून्य);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);
	blkdev_put(पंचांगp, mode);
	वापस 0;
पूर्ण

अटल पूर्णांक blk_ioctl_discard(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित दीर्घ arg, अचिन्हित दीर्घ flags)
अणु
	uपूर्णांक64_t range[2];
	uपूर्णांक64_t start, len;
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	पूर्णांक err;

	अगर (!(mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (!blk_queue_discard(q))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(range, (व्योम __user *)arg, माप(range)))
		वापस -EFAULT;

	start = range[0];
	len = range[1];

	अगर (start & 511)
		वापस -EINVAL;
	अगर (len & 511)
		वापस -EINVAL;

	अगर (start + len > i_size_पढ़ो(bdev->bd_inode))
		वापस -EINVAL;

	err = truncate_bdev_range(bdev, mode, start, start + len - 1);
	अगर (err)
		वापस err;

	वापस blkdev_issue_discard(bdev, start >> 9, len >> 9,
				    GFP_KERNEL, flags);
पूर्ण

अटल पूर्णांक blk_ioctl_zeroout(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित दीर्घ arg)
अणु
	uपूर्णांक64_t range[2];
	uपूर्णांक64_t start, end, len;
	पूर्णांक err;

	अगर (!(mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (copy_from_user(range, (व्योम __user *)arg, माप(range)))
		वापस -EFAULT;

	start = range[0];
	len = range[1];
	end = start + len - 1;

	अगर (start & 511)
		वापस -EINVAL;
	अगर (len & 511)
		वापस -EINVAL;
	अगर (end >= (uपूर्णांक64_t)i_size_पढ़ो(bdev->bd_inode))
		वापस -EINVAL;
	अगर (end < start)
		वापस -EINVAL;

	/* Invalidate the page cache, including dirty pages */
	err = truncate_bdev_range(bdev, mode, start, end);
	अगर (err)
		वापस err;

	वापस blkdev_issue_zeroout(bdev, start >> 9, len >> 9, GFP_KERNEL,
			BLKDEV_ZERO_NOUNMAP);
पूर्ण

अटल पूर्णांक put_uलघु(अचिन्हित लघु __user *argp, अचिन्हित लघु val)
अणु
	वापस put_user(val, argp);
पूर्ण

अटल पूर्णांक put_पूर्णांक(पूर्णांक __user *argp, पूर्णांक val)
अणु
	वापस put_user(val, argp);
पूर्ण

अटल पूर्णांक put_uपूर्णांक(अचिन्हित पूर्णांक __user *argp, अचिन्हित पूर्णांक val)
अणु
	वापस put_user(val, argp);
पूर्ण

अटल पूर्णांक put_दीर्घ(दीर्घ __user *argp, दीर्घ val)
अणु
	वापस put_user(val, argp);
पूर्ण

अटल पूर्णांक put_uदीर्घ(अचिन्हित दीर्घ __user *argp, अचिन्हित दीर्घ val)
अणु
	वापस put_user(val, argp);
पूर्ण

अटल पूर्णांक put_u64(u64 __user *argp, u64 val)
अणु
	वापस put_user(val, argp);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक compat_put_दीर्घ(compat_दीर्घ_t __user *argp, दीर्घ val)
अणु
	वापस put_user(val, argp);
पूर्ण

अटल पूर्णांक compat_put_uदीर्घ(compat_uदीर्घ_t __user *argp, compat_uदीर्घ_t val)
अणु
	वापस put_user(val, argp);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
/*
 * This is the equivalent of compat_ptr_ioctl(), to be used by block
 * drivers that implement only commands that are completely compatible
 * between 32-bit and 64-bit user space
 */
पूर्णांक blkdev_compat_ptr_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;

	अगर (disk->fops->ioctl)
		वापस disk->fops->ioctl(bdev, mode, cmd,
					 (अचिन्हित दीर्घ)compat_ptr(arg));

	वापस -ENOIOCTLCMD;
पूर्ण
EXPORT_SYMBOL(blkdev_compat_ptr_ioctl);
#पूर्ण_अगर

अटल पूर्णांक blkdev_pr_रेजिस्टर(काष्ठा block_device *bdev,
		काष्ठा pr_registration __user *arg)
अणु
	स्थिर काष्ठा pr_ops *ops = bdev->bd_disk->fops->pr_ops;
	काष्ठा pr_registration reg;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!ops || !ops->pr_रेजिस्टर)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&reg, arg, माप(reg)))
		वापस -EFAULT;

	अगर (reg.flags & ~PR_FL_IGNORE_KEY)
		वापस -EOPNOTSUPP;
	वापस ops->pr_रेजिस्टर(bdev, reg.old_key, reg.new_key, reg.flags);
पूर्ण

अटल पूर्णांक blkdev_pr_reserve(काष्ठा block_device *bdev,
		काष्ठा pr_reservation __user *arg)
अणु
	स्थिर काष्ठा pr_ops *ops = bdev->bd_disk->fops->pr_ops;
	काष्ठा pr_reservation rsv;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!ops || !ops->pr_reserve)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&rsv, arg, माप(rsv)))
		वापस -EFAULT;

	अगर (rsv.flags & ~PR_FL_IGNORE_KEY)
		वापस -EOPNOTSUPP;
	वापस ops->pr_reserve(bdev, rsv.key, rsv.type, rsv.flags);
पूर्ण

अटल पूर्णांक blkdev_pr_release(काष्ठा block_device *bdev,
		काष्ठा pr_reservation __user *arg)
अणु
	स्थिर काष्ठा pr_ops *ops = bdev->bd_disk->fops->pr_ops;
	काष्ठा pr_reservation rsv;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!ops || !ops->pr_release)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&rsv, arg, माप(rsv)))
		वापस -EFAULT;

	अगर (rsv.flags)
		वापस -EOPNOTSUPP;
	वापस ops->pr_release(bdev, rsv.key, rsv.type);
पूर्ण

अटल पूर्णांक blkdev_pr_preempt(काष्ठा block_device *bdev,
		काष्ठा pr_preempt __user *arg, bool पात)
अणु
	स्थिर काष्ठा pr_ops *ops = bdev->bd_disk->fops->pr_ops;
	काष्ठा pr_preempt p;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!ops || !ops->pr_preempt)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&p, arg, माप(p)))
		वापस -EFAULT;

	अगर (p.flags)
		वापस -EOPNOTSUPP;
	वापस ops->pr_preempt(bdev, p.old_key, p.new_key, p.type, पात);
पूर्ण

अटल पूर्णांक blkdev_pr_clear(काष्ठा block_device *bdev,
		काष्ठा pr_clear __user *arg)
अणु
	स्थिर काष्ठा pr_ops *ops = bdev->bd_disk->fops->pr_ops;
	काष्ठा pr_clear c;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!ops || !ops->pr_clear)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&c, arg, माप(c)))
		वापस -EFAULT;

	अगर (c.flags)
		वापस -EOPNOTSUPP;
	वापस ops->pr_clear(bdev, c.key);
पूर्ण

अटल पूर्णांक blkdev_flushbuf(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	fsync_bdev(bdev);
	invalidate_bdev(bdev);
	वापस 0;
पूर्ण

अटल पूर्णांक blkdev_roset(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret, n;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (get_user(n, (पूर्णांक __user *)arg))
		वापस -EFAULT;
	अगर (bdev->bd_disk->fops->set_पढ़ो_only) अणु
		ret = bdev->bd_disk->fops->set_पढ़ो_only(bdev, n);
		अगर (ret)
			वापस ret;
	पूर्ण
	bdev->bd_पढ़ो_only = n;
	वापस 0;
पूर्ण

अटल पूर्णांक blkdev_getgeo(काष्ठा block_device *bdev,
		काष्ठा hd_geometry __user *argp)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा hd_geometry geo;
	पूर्णांक ret;

	अगर (!argp)
		वापस -EINVAL;
	अगर (!disk->fops->getgeo)
		वापस -ENOTTY;

	/*
	 * We need to set the startsect first, the driver may
	 * want to override it.
	 */
	स_रखो(&geo, 0, माप(geo));
	geo.start = get_start_sect(bdev);
	ret = disk->fops->getgeo(bdev, &geo);
	अगर (ret)
		वापस ret;
	अगर (copy_to_user(argp, &geo, माप(geo)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_hd_geometry अणु
	अचिन्हित अक्षर heads;
	अचिन्हित अक्षर sectors;
	अचिन्हित लघु cylinders;
	u32 start;
पूर्ण;

अटल पूर्णांक compat_hdio_getgeo(काष्ठा block_device *bdev,
			      काष्ठा compat_hd_geometry __user *ugeo)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा hd_geometry geo;
	पूर्णांक ret;

	अगर (!ugeo)
		वापस -EINVAL;
	अगर (!disk->fops->getgeo)
		वापस -ENOTTY;

	स_रखो(&geo, 0, माप(geo));
	/*
	 * We need to set the startsect first, the driver may
	 * want to override it.
	 */
	geo.start = get_start_sect(bdev);
	ret = disk->fops->getgeo(bdev, &geo);
	अगर (ret)
		वापस ret;

	ret = copy_to_user(ugeo, &geo, 4);
	ret |= put_user(geo.start, &ugeo->start);
	अगर (ret)
		ret = -EFAULT;

	वापस ret;
पूर्ण
#पूर्ण_अगर

/* set the logical block size */
अटल पूर्णांक blkdev_bszset(काष्ठा block_device *bdev, भ_शेषe_t mode,
		पूर्णांक __user *argp)
अणु
	पूर्णांक ret, n;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (!argp)
		वापस -EINVAL;
	अगर (get_user(n, argp))
		वापस -EFAULT;

	अगर (mode & FMODE_EXCL)
		वापस set_blocksize(bdev, n);

	अगर (IS_ERR(blkdev_get_by_dev(bdev->bd_dev, mode | FMODE_EXCL, &bdev)))
		वापस -EBUSY;
	ret = set_blocksize(bdev, n);
	blkdev_put(bdev, mode | FMODE_EXCL);

	वापस ret;
पूर्ण

/*
 * Common commands that are handled the same way on native and compat
 * user space. Note the separate arg/argp parameters that are needed
 * to deal with the compat_ptr() conversion.
 */
अटल पूर्णांक blkdev_common_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
				अचिन्हित cmd, अचिन्हित दीर्घ arg, व्योम __user *argp)
अणु
	अचिन्हित पूर्णांक max_sectors;

	चयन (cmd) अणु
	हाल BLKFLSBUF:
		वापस blkdev_flushbuf(bdev, mode, cmd, arg);
	हाल BLKROSET:
		वापस blkdev_roset(bdev, mode, cmd, arg);
	हाल BLKDISCARD:
		वापस blk_ioctl_discard(bdev, mode, arg, 0);
	हाल BLKSECDISCARD:
		वापस blk_ioctl_discard(bdev, mode, arg,
				BLKDEV_DISCARD_SECURE);
	हाल BLKZEROOUT:
		वापस blk_ioctl_zeroout(bdev, mode, arg);
	हाल BLKREPORTZONE:
		वापस blkdev_report_zones_ioctl(bdev, mode, cmd, arg);
	हाल BLKRESETZONE:
	हाल BLKOPENZONE:
	हाल BLKCLOSEZONE:
	हाल BLKFINISHZONE:
		वापस blkdev_zone_mgmt_ioctl(bdev, mode, cmd, arg);
	हाल BLKGETZONESZ:
		वापस put_uपूर्णांक(argp, bdev_zone_sectors(bdev));
	हाल BLKGETNRZONES:
		वापस put_uपूर्णांक(argp, blkdev_nr_zones(bdev->bd_disk));
	हाल BLKROGET:
		वापस put_पूर्णांक(argp, bdev_पढ़ो_only(bdev) != 0);
	हाल BLKSSZGET: /* get block device logical block size */
		वापस put_पूर्णांक(argp, bdev_logical_block_size(bdev));
	हाल BLKPBSZGET: /* get block device physical block size */
		वापस put_uपूर्णांक(argp, bdev_physical_block_size(bdev));
	हाल BLKIOMIN:
		वापस put_uपूर्णांक(argp, bdev_io_min(bdev));
	हाल BLKIOOPT:
		वापस put_uपूर्णांक(argp, bdev_io_opt(bdev));
	हाल BLKALIGNOFF:
		वापस put_पूर्णांक(argp, bdev_alignment_offset(bdev));
	हाल BLKDISCARDZEROES:
		वापस put_uपूर्णांक(argp, 0);
	हाल BLKSECTGET:
		max_sectors = min_t(अचिन्हित पूर्णांक, अच_लघु_उच्च,
				    queue_max_sectors(bdev_get_queue(bdev)));
		वापस put_uलघु(argp, max_sectors);
	हाल BLKROTATIONAL:
		वापस put_uलघु(argp, !blk_queue_nonrot(bdev_get_queue(bdev)));
	हाल BLKRASET:
	हाल BLKFRASET:
		अगर(!capable(CAP_SYS_ADMIN))
			वापस -EACCES;
		bdev->bd_bdi->ra_pages = (arg * 512) / PAGE_SIZE;
		वापस 0;
	हाल BLKRRPART:
		वापस blkdev_reपढ़ो_part(bdev, mode);
	हाल BLKTRACESTART:
	हाल BLKTRACESTOP:
	हाल BLKTRACETEARDOWN:
		वापस blk_trace_ioctl(bdev, cmd, argp);
	हाल IOC_PR_REGISTER:
		वापस blkdev_pr_रेजिस्टर(bdev, argp);
	हाल IOC_PR_RESERVE:
		वापस blkdev_pr_reserve(bdev, argp);
	हाल IOC_PR_RELEASE:
		वापस blkdev_pr_release(bdev, argp);
	हाल IOC_PR_PREEMPT:
		वापस blkdev_pr_preempt(bdev, argp, false);
	हाल IOC_PR_PREEMPT_ABORT:
		वापस blkdev_pr_preempt(bdev, argp, true);
	हाल IOC_PR_CLEAR:
		वापस blkdev_pr_clear(bdev, argp);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

/*
 * Always keep this in sync with compat_blkdev_ioctl()
 * to handle all incompatible commands in both functions.
 *
 * New commands must be compatible and go पूर्णांकo blkdev_common_ioctl
 */
पूर्णांक blkdev_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित cmd,
			अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	loff_t size;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	/* These need separate implementations क्रम the data काष्ठाure */
	हाल HDIO_GETGEO:
		वापस blkdev_getgeo(bdev, argp);
	हाल BLKPG:
		वापस blkpg_ioctl(bdev, argp);

	/* Compat mode वापसs 32-bit data instead of 'long' */
	हाल BLKRAGET:
	हाल BLKFRAGET:
		अगर (!argp)
			वापस -EINVAL;
		वापस put_दीर्घ(argp, (bdev->bd_bdi->ra_pages*PAGE_SIZE) / 512);
	हाल BLKGETSIZE:
		size = i_size_पढ़ो(bdev->bd_inode);
		अगर ((size >> 9) > ~0UL)
			वापस -EFBIG;
		वापस put_uदीर्घ(argp, size >> 9);

	/* The data is compatible, but the command number is dअगरferent */
	हाल BLKBSZGET: /* get block device soft block size (cf. BLKSSZGET) */
		वापस put_पूर्णांक(argp, block_size(bdev));
	हाल BLKBSZSET:
		वापस blkdev_bszset(bdev, mode, argp);
	हाल BLKGETSIZE64:
		वापस put_u64(argp, i_size_पढ़ो(bdev->bd_inode));

	/* Incompatible alignment on i386 */
	हाल BLKTRACESETUP:
		वापस blk_trace_ioctl(bdev, cmd, argp);
	शेष:
		अवरोध;
	पूर्ण

	ret = blkdev_common_ioctl(bdev, mode, cmd, arg, argp);
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	अगर (!bdev->bd_disk->fops->ioctl)
		वापस -ENOTTY;
	वापस bdev->bd_disk->fops->ioctl(bdev, mode, cmd, arg);
पूर्ण
EXPORT_SYMBOL_GPL(blkdev_ioctl); /* क्रम /dev/raw */

#अगर_घोषित CONFIG_COMPAT

#घोषणा BLKBSZGET_32		_IOR(0x12, 112, पूर्णांक)
#घोषणा BLKBSZSET_32		_IOW(0x12, 113, पूर्णांक)
#घोषणा BLKGETSIZE64_32		_IOR(0x12, 114, पूर्णांक)

/* Most of the generic ioctls are handled in the normal fallback path.
   This assumes the blkdev's low level compat_ioctl always वापसs
   ENOIOCTLCMD क्रम unknown ioctls. */
दीर्घ compat_blkdev_ioctl(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	व्योम __user *argp = compat_ptr(arg);
	काष्ठा block_device *bdev = I_BDEV(file->f_mapping->host);
	काष्ठा gendisk *disk = bdev->bd_disk;
	भ_शेषe_t mode = file->f_mode;
	loff_t size;

	/*
	 * O_NDELAY can be altered using fcntl(.., F_SETFL, ..), so we have
	 * to updated it beक्रमe every ioctl.
	 */
	अगर (file->f_flags & O_NDELAY)
		mode |= FMODE_NDELAY;
	अन्यथा
		mode &= ~FMODE_NDELAY;

	चयन (cmd) अणु
	/* These need separate implementations क्रम the data काष्ठाure */
	हाल HDIO_GETGEO:
		वापस compat_hdio_getgeo(bdev, argp);
	हाल BLKPG:
		वापस compat_blkpg_ioctl(bdev, argp);

	/* Compat mode वापसs 32-bit data instead of 'long' */
	हाल BLKRAGET:
	हाल BLKFRAGET:
		अगर (!argp)
			वापस -EINVAL;
		वापस compat_put_दीर्घ(argp,
			       (bdev->bd_bdi->ra_pages * PAGE_SIZE) / 512);
	हाल BLKGETSIZE:
		size = i_size_पढ़ो(bdev->bd_inode);
		अगर ((size >> 9) > ~0UL)
			वापस -EFBIG;
		वापस compat_put_uदीर्घ(argp, size >> 9);

	/* The data is compatible, but the command number is dअगरferent */
	हाल BLKBSZGET_32: /* get the logical block size (cf. BLKSSZGET) */
		वापस put_पूर्णांक(argp, bdev_logical_block_size(bdev));
	हाल BLKBSZSET_32:
		वापस blkdev_bszset(bdev, mode, argp);
	हाल BLKGETSIZE64_32:
		वापस put_u64(argp, i_size_पढ़ो(bdev->bd_inode));

	/* Incompatible alignment on i386 */
	हाल BLKTRACESETUP32:
		वापस blk_trace_ioctl(bdev, cmd, argp);
	शेष:
		अवरोध;
	पूर्ण

	ret = blkdev_common_ioctl(bdev, mode, cmd, arg, argp);
	अगर (ret == -ENOIOCTLCMD && disk->fops->compat_ioctl)
		ret = disk->fops->compat_ioctl(bdev, mode, cmd, arg);

	वापस ret;
पूर्ण
#पूर्ण_अगर
