<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_QUOTAIO_V1_H
#घोषणा _LINUX_QUOTAIO_V1_H

#समावेश <linux/types.h>

/*
 * The following स्थिरants define the amount of समय given a user
 * beक्रमe the soft limits are treated as hard limits (usually resulting
 * in an allocation failure). The समयr is started when the user crosses
 * their soft limit, it is reset when they go below their soft limit.
 */
#घोषणा MAX_IQ_TIME  604800	/* (7*24*60*60) 1 week */
#घोषणा MAX_DQ_TIME  604800	/* (7*24*60*60) 1 week */

/*
 * The following काष्ठाure defines the क्रमmat of the disk quota file
 * (as it appears on disk) - the file is an array of these काष्ठाures
 * indexed by user or group number.
 */
काष्ठा v1_disk_dqblk अणु
	__u32 dqb_bhardlimit;	/* असलolute limit on disk blks alloc */
	__u32 dqb_bsoftlimit;	/* preferred limit on disk blks */
	__u32 dqb_curblocks;	/* current block count */
	__u32 dqb_ihardlimit;	/* असलolute limit on allocated inodes */
	__u32 dqb_isoftlimit;	/* preferred inode limit */
	__u32 dqb_curinodes;	/* current # allocated inodes */

	/* below fields dअगरfer in length on 32-bit vs 64-bit architectures */
	अचिन्हित दीर्घ dqb_bसमय; /* समय limit क्रम excessive disk use */
	अचिन्हित दीर्घ dqb_iसमय; /* समय limit क्रम excessive inode use */
पूर्ण;

#घोषणा v1_dqoff(UID)      ((loff_t)((UID) * माप (काष्ठा v1_disk_dqblk)))

#पूर्ण_अगर	/* _LINUX_QUOTAIO_V1_H */
