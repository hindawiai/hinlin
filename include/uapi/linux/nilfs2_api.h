<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * nilfs2_api.h - NILFS2 user space API
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित _LINUX_NILFS2_API_H
#घोषणा _LINUX_NILFS2_API_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/**
 * काष्ठा nilfs_cpinfo - checkpoपूर्णांक inक्रमmation
 * @ci_flags: flags
 * @ci_pad: padding
 * @ci_cno: checkpoपूर्णांक number
 * @ci_create: creation बारtamp
 * @ci_nblk_inc: number of blocks incremented by this checkpoपूर्णांक
 * @ci_inodes_count: inodes count
 * @ci_blocks_count: blocks count
 * @ci_next: next checkpoपूर्णांक number in snapshot list
 */
काष्ठा nilfs_cpinfo अणु
	__u32 ci_flags;
	__u32 ci_pad;
	__u64 ci_cno;
	__u64 ci_create;
	__u64 ci_nblk_inc;
	__u64 ci_inodes_count;
	__u64 ci_blocks_count;
	__u64 ci_next;
पूर्ण;

/* checkpoपूर्णांक flags */
क्रमागत अणु
	NILFS_CPINFO_SNAPSHOT,
	NILFS_CPINFO_INVALID,
	NILFS_CPINFO_SKETCH,
	NILFS_CPINFO_MINOR,
पूर्ण;

#घोषणा NILFS_CPINFO_FNS(flag, name)					\
अटल अंतरभूत पूर्णांक							\
nilfs_cpinfo_##name(स्थिर काष्ठा nilfs_cpinfo *cpinfo)			\
अणु									\
	वापस !!(cpinfo->ci_flags & (1UL << NILFS_CPINFO_##flag));	\
पूर्ण

NILFS_CPINFO_FNS(SNAPSHOT, snapshot)
NILFS_CPINFO_FNS(INVALID, invalid)
NILFS_CPINFO_FNS(MINOR, minor)

/**
 * nilfs_suinfo - segment usage inक्रमmation
 * @sui_lasपंचांगod: बारtamp of last modअगरication
 * @sui_nblocks: number of written blocks in segment
 * @sui_flags: segment usage flags
 */
काष्ठा nilfs_suinfo अणु
	__u64 sui_lasपंचांगod;
	__u32 sui_nblocks;
	__u32 sui_flags;
पूर्ण;

/* segment usage flags */
क्रमागत अणु
	NILFS_SUINFO_ACTIVE,
	NILFS_SUINFO_सूचीTY,
	NILFS_SUINFO_ERROR,
पूर्ण;

#घोषणा NILFS_SUINFO_FNS(flag, name)					\
अटल अंतरभूत पूर्णांक							\
nilfs_suinfo_##name(स्थिर काष्ठा nilfs_suinfo *si)			\
अणु									\
	वापस si->sui_flags & (1UL << NILFS_SUINFO_##flag);		\
पूर्ण

NILFS_SUINFO_FNS(ACTIVE, active)
NILFS_SUINFO_FNS(सूचीTY, dirty)
NILFS_SUINFO_FNS(ERROR, error)

अटल अंतरभूत पूर्णांक nilfs_suinfo_clean(स्थिर काष्ठा nilfs_suinfo *si)
अणु
	वापस !si->sui_flags;
पूर्ण

/**
 * nilfs_suinfo_update - segment usage inक्रमmation update
 * @sup_segnum: segment number
 * @sup_flags: flags क्रम which fields are active in sup_sui
 * @sup_reserved: reserved necessary क्रम alignment
 * @sup_sui: segment usage inक्रमmation
 */
काष्ठा nilfs_suinfo_update अणु
	__u64 sup_segnum;
	__u32 sup_flags;
	__u32 sup_reserved;
	काष्ठा nilfs_suinfo sup_sui;
पूर्ण;

क्रमागत अणु
	NILFS_SUINFO_UPDATE_LASTMOD,
	NILFS_SUINFO_UPDATE_NBLOCKS,
	NILFS_SUINFO_UPDATE_FLAGS,
	__NR_NILFS_SUINFO_UPDATE_FIELDS,
पूर्ण;

#घोषणा NILFS_SUINFO_UPDATE_FNS(flag, name)				\
अटल अंतरभूत व्योम							\
nilfs_suinfo_update_set_##name(काष्ठा nilfs_suinfo_update *sup)		\
अणु									\
	sup->sup_flags |= 1UL << NILFS_SUINFO_UPDATE_##flag;		\
पूर्ण									\
अटल अंतरभूत व्योम							\
nilfs_suinfo_update_clear_##name(काष्ठा nilfs_suinfo_update *sup)	\
अणु									\
	sup->sup_flags &= ~(1UL << NILFS_SUINFO_UPDATE_##flag);		\
पूर्ण									\
अटल अंतरभूत पूर्णांक							\
nilfs_suinfo_update_##name(स्थिर काष्ठा nilfs_suinfo_update *sup)	\
अणु									\
	वापस !!(sup->sup_flags & (1UL << NILFS_SUINFO_UPDATE_##flag));\
पूर्ण

NILFS_SUINFO_UPDATE_FNS(LASTMOD, lasपंचांगod)
NILFS_SUINFO_UPDATE_FNS(NBLOCKS, nblocks)
NILFS_SUINFO_UPDATE_FNS(FLAGS, flags)

क्रमागत अणु
	NILFS_CHECKPOINT,
	NILFS_SNAPSHOT,
पूर्ण;

/**
 * काष्ठा nilfs_cpmode - change checkpoपूर्णांक mode काष्ठाure
 * @cm_cno: checkpoपूर्णांक number
 * @cm_mode: mode of checkpoपूर्णांक
 * @cm_pad: padding
 */
काष्ठा nilfs_cpmode अणु
	__u64 cm_cno;
	__u32 cm_mode;
	__u32 cm_pad;
पूर्ण;

/**
 * काष्ठा nilfs_argv - argument vector
 * @v_base: poपूर्णांकer on data array from userspace
 * @v_nmembs: number of members in data array
 * @v_size: size of data array in bytes
 * @v_flags: flags
 * @v_index: start number of target data items
 */
काष्ठा nilfs_argv अणु
	__u64 v_base;
	__u32 v_nmembs;	/* number of members */
	__u16 v_size;	/* size of members */
	__u16 v_flags;
	__u64 v_index;
पूर्ण;

/**
 * काष्ठा nilfs_period - period of checkpoपूर्णांक numbers
 * @p_start: start checkpoपूर्णांक number (inclusive)
 * @p_end: end checkpoपूर्णांक number (exclusive)
 */
काष्ठा nilfs_period अणु
	__u64 p_start;
	__u64 p_end;
पूर्ण;

/**
 * काष्ठा nilfs_cpstat - checkpoपूर्णांक statistics
 * @cs_cno: checkpoपूर्णांक number
 * @cs_ncps: number of checkpoपूर्णांकs
 * @cs_nsss: number of snapshots
 */
काष्ठा nilfs_cpstat अणु
	__u64 cs_cno;
	__u64 cs_ncps;
	__u64 cs_nsss;
पूर्ण;

/**
 * काष्ठा nilfs_sustat - segment usage statistics
 * @ss_nsegs: number of segments
 * @ss_ncleansegs: number of clean segments
 * @ss_ndirtysegs: number of dirty segments
 * @ss_स_समय: creation समय of the last segment
 * @ss_nongc_स_समय: creation समय of the last segment not क्रम GC
 * @ss_prot_seq: least sequence number of segments which must not be reclaimed
 */
काष्ठा nilfs_sustat अणु
	__u64 ss_nsegs;
	__u64 ss_ncleansegs;
	__u64 ss_ndirtysegs;
	__u64 ss_स_समय;
	__u64 ss_nongc_स_समय;
	__u64 ss_prot_seq;
पूर्ण;

/**
 * काष्ठा nilfs_vinfo - भव block number inक्रमmation
 * @vi_vblocknr: भव block number
 * @vi_start: start checkpoपूर्णांक number (inclusive)
 * @vi_end: end checkpoपूर्णांक number (exclusive)
 * @vi_blocknr: disk block number
 */
काष्ठा nilfs_vinfo अणु
	__u64 vi_vblocknr;
	__u64 vi_start;
	__u64 vi_end;
	__u64 vi_blocknr;
पूर्ण;

/**
 * काष्ठा nilfs_vdesc - descriptor of भव block number
 * @vd_ino: inode number
 * @vd_cno: checkpoपूर्णांक number
 * @vd_vblocknr: भव block number
 * @vd_period: period of checkpoपूर्णांक numbers
 * @vd_blocknr: disk block number
 * @vd_offset: logical block offset inside a file
 * @vd_flags: flags (data or node block)
 * @vd_pad: padding
 */
काष्ठा nilfs_vdesc अणु
	__u64 vd_ino;
	__u64 vd_cno;
	__u64 vd_vblocknr;
	काष्ठा nilfs_period vd_period;
	__u64 vd_blocknr;
	__u64 vd_offset;
	__u32 vd_flags;
	__u32 vd_pad;
पूर्ण;

/**
 * काष्ठा nilfs_bdesc - descriptor of disk block number
 * @bd_ino: inode number
 * @bd_oblocknr: disk block address (क्रम skipping dead blocks)
 * @bd_blocknr: disk block address
 * @bd_offset: logical block offset inside a file
 * @bd_level: level in the b-tree organization
 * @bd_pad: padding
 */
काष्ठा nilfs_bdesc अणु
	__u64 bd_ino;
	__u64 bd_oblocknr;
	__u64 bd_blocknr;
	__u64 bd_offset;
	__u32 bd_level;
	__u32 bd_pad;
पूर्ण;

#घोषणा NILFS_IOCTL_IDENT	'n'

#घोषणा NILFS_IOCTL_CHANGE_CPMODE					\
	_IOW(NILFS_IOCTL_IDENT, 0x80, काष्ठा nilfs_cpmode)
#घोषणा NILFS_IOCTL_DELETE_CHECKPOINT					\
	_IOW(NILFS_IOCTL_IDENT, 0x81, __u64)
#घोषणा NILFS_IOCTL_GET_CPINFO						\
	_IOR(NILFS_IOCTL_IDENT, 0x82, काष्ठा nilfs_argv)
#घोषणा NILFS_IOCTL_GET_CPSTAT						\
	_IOR(NILFS_IOCTL_IDENT, 0x83, काष्ठा nilfs_cpstat)
#घोषणा NILFS_IOCTL_GET_SUINFO						\
	_IOR(NILFS_IOCTL_IDENT, 0x84, काष्ठा nilfs_argv)
#घोषणा NILFS_IOCTL_GET_SUSTAT						\
	_IOR(NILFS_IOCTL_IDENT, 0x85, काष्ठा nilfs_sustat)
#घोषणा NILFS_IOCTL_GET_VINFO						\
	_IOWR(NILFS_IOCTL_IDENT, 0x86, काष्ठा nilfs_argv)
#घोषणा NILFS_IOCTL_GET_BDESCS						\
	_IOWR(NILFS_IOCTL_IDENT, 0x87, काष्ठा nilfs_argv)
#घोषणा NILFS_IOCTL_CLEAN_SEGMENTS					\
	_IOW(NILFS_IOCTL_IDENT, 0x88, काष्ठा nilfs_argv[5])
#घोषणा NILFS_IOCTL_SYNC						\
	_IOR(NILFS_IOCTL_IDENT, 0x8A, __u64)
#घोषणा NILFS_IOCTL_RESIZE						\
	_IOW(NILFS_IOCTL_IDENT, 0x8B, __u64)
#घोषणा NILFS_IOCTL_SET_ALLOC_RANGE					\
	_IOW(NILFS_IOCTL_IDENT, 0x8C, __u64[2])
#घोषणा NILFS_IOCTL_SET_SUINFO						\
	_IOW(NILFS_IOCTL_IDENT, 0x8D, काष्ठा nilfs_argv)

#पूर्ण_अगर /* _LINUX_NILFS2_API_H */
