<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STATFS_H
#घोषणा _LINUX_STATFS_H

#समावेश <linux/types.h>
#समावेश <यंत्र/statfs.h>
#समावेश <यंत्र/byteorder.h>

काष्ठा kstatfs अणु
	दीर्घ f_type;
	दीर्घ f_bsize;
	u64 f_blocks;
	u64 f_bमुक्त;
	u64 f_bavail;
	u64 f_files;
	u64 f_fमुक्त;
	__kernel_fsid_t f_fsid;
	दीर्घ f_namelen;
	दीर्घ f_frsize;
	दीर्घ f_flags;
	दीर्घ f_spare[4];
पूर्ण;

/*
 * Definitions क्रम the flag in f_flag.
 *
 * Generally these flags are equivalent to the MS_ flags used in the mount
 * ABI.  The exception is ST_VALID which has the same value as MS_REMOUNT
 * which करोesn't make any sense क्रम statfs.
 */
#घोषणा ST_RDONLY	0x0001	/* mount पढ़ो-only */
#घोषणा ST_NOSUID	0x0002	/* ignore suid and sgid bits */
#घोषणा ST_NODEV	0x0004	/* disallow access to device special files */
#घोषणा ST_NOEXEC	0x0008	/* disallow program execution */
#घोषणा ST_SYNCHRONOUS	0x0010	/* ग_लिखोs are synced at once */
#घोषणा ST_VALID	0x0020	/* f_flags support is implemented */
#घोषणा ST_MANDLOCK	0x0040	/* allow mandatory locks on an FS */
/* 0x0080 used क्रम ST_WRITE in glibc */
/* 0x0100 used क्रम ST_APPEND in glibc */
/* 0x0200 used क्रम ST_IMMUTABLE in glibc */
#घोषणा ST_NOATIME	0x0400	/* करो not update access बार */
#घोषणा ST_NOसूचीATIME	0x0800	/* करो not update directory access बार */
#घोषणा ST_RELATIME	0x1000	/* update aसमय relative to mसमय/स_समय */
#घोषणा ST_NOSYMFOLLOW	0x2000	/* करो not follow symlinks */

काष्ठा dentry;
बाह्य पूर्णांक vfs_get_fsid(काष्ठा dentry *dentry, __kernel_fsid_t *fsid);

अटल अंतरभूत __kernel_fsid_t u64_to_fsid(u64 v)
अणु
	वापस (__kernel_fsid_t)अणु.val = अणु(u32)v, (u32)(v>>32)पूर्णपूर्ण;
पूर्ण

/* Fold 16 bytes uuid to 64 bit fsid */
अटल अंतरभूत __kernel_fsid_t uuid_to_fsid(__u8 *uuid)
अणु
	वापस u64_to_fsid(le64_to_cpup((व्योम *)uuid) ^
		le64_to_cpup((व्योम *)(uuid + माप(u64))));
पूर्ण

#पूर्ण_अगर
