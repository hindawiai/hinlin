<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */

#अगर_अघोषित _UAPI_LINUX_F2FS_H
#घोषणा _UAPI_LINUX_F2FS_H
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * f2fs-specअगरic ioctl commands
 */
#घोषणा F2FS_IOCTL_MAGIC		0xf5
#घोषणा F2FS_IOC_START_ATOMIC_WRITE	_IO(F2FS_IOCTL_MAGIC, 1)
#घोषणा F2FS_IOC_COMMIT_ATOMIC_WRITE	_IO(F2FS_IOCTL_MAGIC, 2)
#घोषणा F2FS_IOC_START_VOLATILE_WRITE	_IO(F2FS_IOCTL_MAGIC, 3)
#घोषणा F2FS_IOC_RELEASE_VOLATILE_WRITE	_IO(F2FS_IOCTL_MAGIC, 4)
#घोषणा F2FS_IOC_ABORT_VOLATILE_WRITE	_IO(F2FS_IOCTL_MAGIC, 5)
#घोषणा F2FS_IOC_GARBAGE_COLLECT	_IOW(F2FS_IOCTL_MAGIC, 6, __u32)
#घोषणा F2FS_IOC_WRITE_CHECKPOINT	_IO(F2FS_IOCTL_MAGIC, 7)
#घोषणा F2FS_IOC_DEFRAGMENT		_IOWR(F2FS_IOCTL_MAGIC, 8,	\
						काष्ठा f2fs_defragment)
#घोषणा F2FS_IOC_MOVE_RANGE		_IOWR(F2FS_IOCTL_MAGIC, 9,	\
						काष्ठा f2fs_move_range)
#घोषणा F2FS_IOC_FLUSH_DEVICE		_IOW(F2FS_IOCTL_MAGIC, 10,	\
						काष्ठा f2fs_flush_device)
#घोषणा F2FS_IOC_GARBAGE_COLLECT_RANGE	_IOW(F2FS_IOCTL_MAGIC, 11,	\
						काष्ठा f2fs_gc_range)
#घोषणा F2FS_IOC_GET_FEATURES		_IOR(F2FS_IOCTL_MAGIC, 12, __u32)
#घोषणा F2FS_IOC_SET_PIN_खाता		_IOW(F2FS_IOCTL_MAGIC, 13, __u32)
#घोषणा F2FS_IOC_GET_PIN_खाता		_IOR(F2FS_IOCTL_MAGIC, 14, __u32)
#घोषणा F2FS_IOC_PRECACHE_EXTENTS	_IO(F2FS_IOCTL_MAGIC, 15)
#घोषणा F2FS_IOC_RESIZE_FS		_IOW(F2FS_IOCTL_MAGIC, 16, __u64)
#घोषणा F2FS_IOC_GET_COMPRESS_BLOCKS	_IOR(F2FS_IOCTL_MAGIC, 17, __u64)
#घोषणा F2FS_IOC_RELEASE_COMPRESS_BLOCKS				\
					_IOR(F2FS_IOCTL_MAGIC, 18, __u64)
#घोषणा F2FS_IOC_RESERVE_COMPRESS_BLOCKS				\
					_IOR(F2FS_IOCTL_MAGIC, 19, __u64)
#घोषणा F2FS_IOC_SEC_TRIM_खाता		_IOW(F2FS_IOCTL_MAGIC, 20,	\
						काष्ठा f2fs_sectrim_range)
#घोषणा F2FS_IOC_GET_COMPRESS_OPTION	_IOR(F2FS_IOCTL_MAGIC, 21,	\
						काष्ठा f2fs_comp_option)
#घोषणा F2FS_IOC_SET_COMPRESS_OPTION	_IOW(F2FS_IOCTL_MAGIC, 22,	\
						काष्ठा f2fs_comp_option)
#घोषणा F2FS_IOC_DECOMPRESS_खाता	_IO(F2FS_IOCTL_MAGIC, 23)
#घोषणा F2FS_IOC_COMPRESS_खाता		_IO(F2FS_IOCTL_MAGIC, 24)

/*
 * should be same as XFS_IOC_GOINGDOWN.
 * Flags क्रम going करोwn operation used by FS_IOC_GOINGDOWN
 */
#घोषणा F2FS_IOC_SHUTDOWN	_IOR('X', 125, __u32)	/* Shutकरोwn */
#घोषणा F2FS_GOING_DOWN_FULLSYNC	0x0	/* going करोwn with full sync */
#घोषणा F2FS_GOING_DOWN_METASYNC	0x1	/* going करोwn with metadata */
#घोषणा F2FS_GOING_DOWN_NOSYNC		0x2	/* going करोwn */
#घोषणा F2FS_GOING_DOWN_METAFLUSH	0x3	/* going करोwn with meta flush */
#घोषणा F2FS_GOING_DOWN_NEED_FSCK	0x4	/* going करोwn to trigger fsck */

/*
 * Flags used by F2FS_IOC_SEC_TRIM_खाता
 */
#घोषणा F2FS_TRIM_खाता_DISCARD		0x1	/* send discard command */
#घोषणा F2FS_TRIM_खाता_ZEROOUT		0x2	/* zero out */
#घोषणा F2FS_TRIM_खाता_MASK		0x3

काष्ठा f2fs_gc_range अणु
	__u32 sync;
	__u64 start;
	__u64 len;
पूर्ण;

काष्ठा f2fs_defragment अणु
	__u64 start;
	__u64 len;
पूर्ण;

काष्ठा f2fs_move_range अणु
	__u32 dst_fd;		/* destination fd */
	__u64 pos_in;		/* start position in src_fd */
	__u64 pos_out;		/* start position in dst_fd */
	__u64 len;		/* size to move */
पूर्ण;

काष्ठा f2fs_flush_device अणु
	__u32 dev_num;		/* device number to flush */
	__u32 segments;		/* # of segments to flush */
पूर्ण;

काष्ठा f2fs_sectrim_range अणु
	__u64 start;
	__u64 len;
	__u64 flags;
पूर्ण;

काष्ठा f2fs_comp_option अणु
	__u8 algorithm;
	__u8 log_cluster_size;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_F2FS_H */
