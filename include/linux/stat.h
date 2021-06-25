<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STAT_H
#घोषणा _LINUX_STAT_H


#समावेश <यंत्र/स्थिति.स>
#समावेश <uapi/linux/स्थिति.स>

#घोषणा S_IRWXUGO	(S_IRWXU|S_IRWXG|S_IRWXO)
#घोषणा S_IALLUGO	(S_ISUID|S_ISGID|S_ISVTX|S_IRWXUGO)
#घोषणा S_IRUGO		(S_IRUSR|S_IRGRP|S_IROTH)
#घोषणा S_IWUGO		(S_IWUSR|S_IWGRP|S_IWOTH)
#घोषणा S_IXUGO		(S_IXUSR|S_IXGRP|S_IXOTH)

#घोषणा UTIME_NOW	((1l << 30) - 1l)
#घोषणा UTIME_OMIT	((1l << 30) - 2l)

#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <linux/uidgid.h>

काष्ठा kstat अणु
	u32		result_mask;	/* What fields the user got */
	umode_t		mode;
	अचिन्हित पूर्णांक	nlink;
	uपूर्णांक32_t	blksize;	/* Preferred I/O size */
	u64		attributes;
	u64		attributes_mask;
#घोषणा KSTAT_ATTR_FS_IOC_FLAGS				\
	(STATX_ATTR_COMPRESSED |			\
	 STATX_ATTR_IMMUTABLE |				\
	 STATX_ATTR_APPEND |				\
	 STATX_ATTR_NODUMP |				\
	 STATX_ATTR_ENCRYPTED |				\
	 STATX_ATTR_VERITY				\
	 )/* Attrs corresponding to FS_*_FL flags */
	u64		ino;
	dev_t		dev;
	dev_t		rdev;
	kuid_t		uid;
	kgid_t		gid;
	loff_t		size;
	काष्ठा बारpec64 aसमय;
	काष्ठा बारpec64 mसमय;
	काष्ठा बारpec64 स_समय;
	काष्ठा बारpec64 bसमय;			/* File creation समय */
	u64		blocks;
	u64		mnt_id;
पूर्ण;

#पूर्ण_अगर
