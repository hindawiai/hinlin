<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित AMIGAFFS_H
#घोषणा AMIGAFFS_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा FS_OFS		0x444F5300
#घोषणा FS_FFS		0x444F5301
#घोषणा FS_INTLOFS	0x444F5302
#घोषणा FS_INTLFFS	0x444F5303
#घोषणा FS_DCOFS	0x444F5304
#घोषणा FS_DCFFS	0x444F5305
#घोषणा MUFS_FS		0x6d754653   /* 'muFS' */
#घोषणा MUFS_OFS	0x6d754600   /* 'muF\0' */
#घोषणा MUFS_FFS	0x6d754601   /* 'muF\1' */
#घोषणा MUFS_INTLOFS	0x6d754602   /* 'muF\2' */
#घोषणा MUFS_INTLFFS	0x6d754603   /* 'muF\3' */
#घोषणा MUFS_DCOFS	0x6d754604   /* 'muF\4' */
#घोषणा MUFS_DCFFS	0x6d754605   /* 'muF\5' */

#घोषणा T_SHORT		2
#घोषणा T_LIST		16
#घोषणा T_DATA		8

#घोषणा ST_LINKखाता	-4
#घोषणा ST_खाता		-3
#घोषणा ST_ROOT		1
#घोषणा ST_USERसूची	2
#घोषणा ST_SOFTLINK	3
#घोषणा ST_LINKसूची	4

#घोषणा AFFS_ROOT_BMAPS		25

/* Seconds since Amiga epoch of 1978/01/01 to UNIX */
#घोषणा AFFS_EPOCH_DELTA ((8 * 365 + 2) * 86400LL)

काष्ठा affs_date अणु
	__be32 days;
	__be32 mins;
	__be32 ticks;
पूर्ण;

काष्ठा affs_लघु_date अणु
	__be16 days;
	__be16 mins;
	__be16 ticks;
पूर्ण;

काष्ठा affs_root_head अणु
	__be32 ptype;
	__be32 spare1;
	__be32 spare2;
	__be32 hash_size;
	__be32 spare3;
	__be32 checksum;
	__be32 hashtable[1];
पूर्ण;

काष्ठा affs_root_tail अणु
	__be32 bm_flag;
	__be32 bm_blk[AFFS_ROOT_BMAPS];
	__be32 bm_ext;
	काष्ठा affs_date root_change;
	u8 disk_name[32];
	__be32 spare1;
	__be32 spare2;
	काष्ठा affs_date disk_change;
	काष्ठा affs_date disk_create;
	__be32 spare3;
	__be32 spare4;
	__be32 dcache;
	__be32 stype;
पूर्ण;

काष्ठा affs_head अणु
	__be32 ptype;
	__be32 key;
	__be32 block_count;
	__be32 spare1;
	__be32 first_data;
	__be32 checksum;
	__be32 table[1];
पूर्ण;

काष्ठा affs_tail अणु
	__be32 spare1;
	__be16 uid;
	__be16 gid;
	__be32 protect;
	__be32 size;
	u8 comment[92];
	काष्ठा affs_date change;
	u8 name[32];
	__be32 spare2;
	__be32 original;
	__be32 link_chain;
	__be32 spare[5];
	__be32 hash_chain;
	__be32 parent;
	__be32 extension;
	__be32 stype;
पूर्ण;

काष्ठा slink_front
अणु
	__be32 ptype;
	__be32 key;
	__be32 spare1[3];
	__be32 checksum;
	u8 symname[1];	/* depends on block size */
पूर्ण;

काष्ठा affs_data_head
अणु
	__be32 ptype;
	__be32 key;
	__be32 sequence;
	__be32 size;
	__be32 next;
	__be32 checksum;
	u8 data[1];	/* depends on block size */
पूर्ण;

/* Permission bits */

#घोषणा FIBF_OTR_READ		0x8000
#घोषणा FIBF_OTR_WRITE		0x4000
#घोषणा FIBF_OTR_EXECUTE	0x2000
#घोषणा FIBF_OTR_DELETE		0x1000
#घोषणा FIBF_GRP_READ		0x0800
#घोषणा FIBF_GRP_WRITE		0x0400
#घोषणा FIBF_GRP_EXECUTE	0x0200
#घोषणा FIBF_GRP_DELETE		0x0100

#घोषणा FIBF_HIDDEN		0x0080
#घोषणा FIBF_SCRIPT		0x0040
#घोषणा FIBF_PURE		0x0020		/* no use under linux */
#घोषणा FIBF_ARCHIVED		0x0010		/* never set, always cleared on ग_लिखो */
#घोषणा FIBF_NOREAD		0x0008		/* 0 means allowed */
#घोषणा FIBF_NOWRITE		0x0004		/* 0 means allowed */
#घोषणा FIBF_NOEXECUTE		0x0002		/* 0 means allowed, ignored under linux */
#घोषणा FIBF_NODELETE		0x0001		/* 0 means allowed */

#घोषणा FIBF_OWNER		0x000F		/* Bits pertaining to owner */
#घोषणा FIBF_MASK		0xEE0E		/* Bits modअगरied by Linux */

#पूर्ण_अगर
