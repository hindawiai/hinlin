<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_LINUX__
#घोषणा __XFS_LINUX__

#समावेश <linux/types.h>
#समावेश <linux/uuid.h>

/*
 * Kernel specअगरic type declarations क्रम XFS
 */

प्रकार __s64			xfs_off_t;	/* <file offset> type */
प्रकार अचिन्हित दीर्घ दीर्घ	xfs_ino_t;	/* <inode> type */
प्रकार __s64			xfs_daddr_t;	/* <disk address> type */
प्रकार __u32			xfs_dev_t;
प्रकार __u32			xfs_nlink_t;

#समावेश "xfs_types.h"

#समावेश "kmem.h"
#समावेश "mrlock.h"

#समावेश <linux/semaphore.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/file.h>
#समावेश <linux/swap.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/bitops.h>
#समावेश <linux/major.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sort.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/capability.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/xattr.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/param.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "xfs_fs.h"
#समावेश "xfs_stats.h"
#समावेश "xfs_sysctl.h"
#समावेश "xfs_iops.h"
#समावेश "xfs_aops.h"
#समावेश "xfs_super.h"
#समावेश "xfs_cksum.h"
#समावेश "xfs_buf.h"
#समावेश "xfs_message.h"

#अगर_घोषित __BIG_ENDIAN
#घोषणा XFS_NATIVE_HOST 1
#अन्यथा
#अघोषित XFS_NATIVE_HOST
#पूर्ण_अगर

#घोषणा irix_sgid_inherit	xfs_params.sgid_inherit.val
#घोषणा irix_symlink_mode	xfs_params.symlink_mode.val
#घोषणा xfs_panic_mask		xfs_params.panic_mask.val
#घोषणा xfs_error_level		xfs_params.error_level.val
#घोषणा xfs_syncd_centisecs	xfs_params.syncd_समयr.val
#घोषणा xfs_stats_clear		xfs_params.stats_clear.val
#घोषणा xfs_inherit_sync	xfs_params.inherit_sync.val
#घोषणा xfs_inherit_nodump	xfs_params.inherit_nodump.val
#घोषणा xfs_inherit_noaसमय	xfs_params.inherit_noatim.val
#घोषणा xfs_inherit_nosymlinks	xfs_params.inherit_nosym.val
#घोषणा xfs_rotorstep		xfs_params.rotorstep.val
#घोषणा xfs_inherit_nodefrag	xfs_params.inherit_nodfrg.val
#घोषणा xfs_fstrm_centisecs	xfs_params.fstrm_समयr.val
#घोषणा xfs_blockgc_secs	xfs_params.blockgc_समयr.val

#घोषणा current_cpu()		(raw_smp_processor_id())
#घोषणा current_set_flags_nested(sp, f)		\
		(*(sp) = current->flags, current->flags |= (f))
#घोषणा current_restore_flags_nested(sp, f)	\
		(current->flags = ((current->flags & ~(f)) | (*(sp) & (f))))

#घोषणा NBBY		8		/* number of bits per byte */

/*
 * Size of block device i/o is parameterized here.
 * Currently the प्रणाली supports page-sized i/o.
 */
#घोषणा	BLKDEV_IOSHIFT		PAGE_SHIFT
#घोषणा	BLKDEV_IOSIZE		(1<<BLKDEV_IOSHIFT)
/* number of BB's per block device block */
#घोषणा	BLKDEV_BB		BTOBB(BLKDEV_IOSIZE)

#घोषणा ENOATTR		ENODATA		/* Attribute not found */
#घोषणा EWRONGFS	EINVAL		/* Mount with wrong fileप्रणाली type */
#घोषणा EFSCORRUPTED	EUCLEAN		/* Fileप्रणाली is corrupted */
#घोषणा EFSBADCRC	EBADMSG		/* Bad CRC detected */

#घोषणा __वापस_address __builtin_वापस_address(0)

/*
 * Return the address of a label.  Use barrier() so that the optimizer
 * won't reorder code to refactor the error jumpouts पूर्णांकo a single
 * वापस, which throws off the reported address.
 */
#घोषणा __this_address	(अणु __label__ __here; __here: barrier(); &&__here; पूर्ण)

#घोषणा XFS_PROJID_DEFAULT	0

#घोषणा howmany(x, y)	(((x)+((y)-1))/(y))

अटल अंतरभूत व्योम delay(दीर्घ ticks)
अणु
	schedule_समयout_unपूर्णांकerruptible(ticks);
पूर्ण

/*
 * XFS wrapper काष्ठाure क्रम sysfs support. It depends on बाह्यal data
 * काष्ठाures and is embedded in various पूर्णांकernal data काष्ठाures to implement
 * the XFS sysfs object heirarchy. Define it here क्रम broad access throughout
 * the codebase.
 */
काष्ठा xfs_kobj अणु
	काष्ठा kobject		kobject;
	काष्ठा completion	complete;
पूर्ण;

काष्ठा xstats अणु
	काष्ठा xfsstats __percpu	*xs_stats;
	काष्ठा xfs_kobj			xs_kobj;
पूर्ण;

बाह्य काष्ठा xstats xfsstats;

अटल अंतरभूत dev_t xfs_to_linux_dev_t(xfs_dev_t dev)
अणु
	वापस MKDEV(sysv_major(dev) & 0x1ff, sysv_minor(dev));
पूर्ण

अटल अंतरभूत xfs_dev_t linux_to_xfs_dev_t(dev_t dev)
अणु
	वापस sysv_encode_dev(dev);
पूर्ण

/*
 * Various platक्रमm dependent calls that करोn't fit anywhere अन्यथा
 */
#घोषणा xfs_sort(a,n,s,fn)	sort(a,n,s,fn,शून्य)
#घोषणा xfs_stack_trace()	dump_stack()

अटल अंतरभूत uपूर्णांक64_t roundकरोwn_64(uपूर्णांक64_t x, uपूर्णांक32_t y)
अणु
	करो_भाग(x, y);
	वापस x * y;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t roundup_64(uपूर्णांक64_t x, uपूर्णांक32_t y)
अणु
	x += y - 1;
	करो_भाग(x, y);
	वापस x * y;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t howmany_64(uपूर्णांक64_t x, uपूर्णांक32_t y)
अणु
	x += y - 1;
	करो_भाग(x, y);
	वापस x;
पूर्ण

पूर्णांक xfs_rw_bdev(काष्ठा block_device *bdev, sector_t sector, अचिन्हित पूर्णांक count,
		अक्षर *data, अचिन्हित पूर्णांक op);

#घोषणा ASSERT_ALWAYS(expr)	\
	(likely(expr) ? (व्योम)0 : assfail(शून्य, #expr, __खाता__, __LINE__))

#अगर_घोषित DEBUG
#घोषणा ASSERT(expr)	\
	(likely(expr) ? (व्योम)0 : assfail(शून्य, #expr, __खाता__, __LINE__))

#अन्यथा	/* !DEBUG */

#अगर_घोषित XFS_WARN

#घोषणा ASSERT(expr)	\
	(likely(expr) ? (व्योम)0 : asswarn(शून्य, #expr, __खाता__, __LINE__))

#अन्यथा	/* !DEBUG && !XFS_WARN */

#घोषणा ASSERT(expr)		((व्योम)0)

#पूर्ण_अगर /* XFS_WARN */
#पूर्ण_अगर /* DEBUG */

#घोषणा XFS_IS_CORRUPT(mp, expr)	\
	(unlikely(expr) ? xfs_corruption_error(#expr, XFS_ERRLEVEL_LOW, (mp), \
					       शून्य, 0, __खाता__, __LINE__, \
					       __this_address), \
			  true : false)

#घोषणा STATIC अटल noअंतरभूत

#अगर_घोषित CONFIG_XFS_RT

/*
 * make sure we ignore the inode flag अगर the fileप्रणाली करोesn't have a
 * configured realसमय device.
 */
#घोषणा XFS_IS_REALTIME_INODE(ip)			\
	(((ip)->i_dअगरlags & XFS_DIFLAG_REALTIME) &&	\
	 (ip)->i_mount->m_rtdev_targp)
#घोषणा XFS_IS_REALTIME_MOUNT(mp) ((mp)->m_rtdev_targp ? 1 : 0)
#अन्यथा
#घोषणा XFS_IS_REALTIME_INODE(ip) (0)
#घोषणा XFS_IS_REALTIME_MOUNT(mp) (0)
#पूर्ण_अगर

/*
 * Starting in Linux 4.15, the %p (raw poपूर्णांकer value) prपूर्णांकk modअगरier
 * prपूर्णांकs a hashed version of the poपूर्णांकer to aव्योम leaking kernel
 * poपूर्णांकers पूर्णांकo dmesg.  If we're trying to debug the kernel we want the
 * raw values, so override this behavior as best we can.
 */
#अगर_घोषित DEBUG
# define PTR_FMT "%px"
#अन्यथा
# define PTR_FMT "%p"
#पूर्ण_अगर

#पूर्ण_अगर /* __XFS_LINUX__ */
