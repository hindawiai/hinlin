<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */
#अगर_अघोषित _H_JFS_TYPES
#घोषणा	_H_JFS_TYPES

/*
 *	jfs_types.h:
 *
 * basic type/utility definitions
 *
 * note: this header file must be the 1st include file
 * of JFS include list in all JFS .c file.
 */

#समावेश <linux/types.h>
#समावेश <linux/nls.h>

/*
 * transaction and lock id's
 *
 * Don't change these without carefully considering the impact on the
 * size and alignment of all of the linelock variants
 */
प्रकार u16 tid_t;
प्रकार u16 lid_t;

/*
 * Almost identical to Linux's बारpec, but not quite
 */
काष्ठा बारtruc_t अणु
	__le32 tv_sec;
	__le32 tv_nsec;
पूर्ण;

/*
 *	handy
 */

#घोषणा LEFTMOSTONE	0x80000000
#घोषणा	HIGHORDER	0x80000000u	/* high order bit on	*/
#घोषणा	ONES		0xffffffffu	/* all bit on		*/

/*
 *	physical xd (pxd)
 *
 *	The lefपंचांगost 24 bits of len_addr are the extent length.
 *	The righपंचांगost 8 bits of len_addr are the most signficant bits of
 *	the extent address
 */
प्रकार काष्ठा अणु
	__le32 len_addr;
	__le32 addr2;
पूर्ण pxd_t;

/* xd_t field स्थिरruction */

अटल अंतरभूत व्योम PXDlength(pxd_t *pxd, __u32 len)
अणु
	pxd->len_addr = (pxd->len_addr & cpu_to_le32(~0xffffff)) |
			cpu_to_le32(len & 0xffffff);
पूर्ण

अटल अंतरभूत व्योम PXDaddress(pxd_t *pxd, __u64 addr)
अणु
	pxd->len_addr = (pxd->len_addr & cpu_to_le32(0xffffff)) |
			cpu_to_le32((addr >> 32)<<24);
	pxd->addr2 = cpu_to_le32(addr & 0xffffffff);
पूर्ण

/* xd_t field extraction */
अटल अंतरभूत __u32 lengthPXD(pxd_t *pxd)
अणु
	वापस le32_to_cpu((pxd)->len_addr) & 0xffffff;
पूर्ण

अटल अंतरभूत __u64 addressPXD(pxd_t *pxd)
अणु
	__u64 n = le32_to_cpu(pxd->len_addr) & ~0xffffff;
	वापस (n << 8) + le32_to_cpu(pxd->addr2);
पूर्ण

#घोषणा MAXTREEHEIGHT 8
/* pxd list */
काष्ठा pxdlist अणु
	s16 maxnpxd;
	s16 npxd;
	pxd_t pxd[MAXTREEHEIGHT];
पूर्ण;


/*
 *	data extent descriptor (dxd)
 */
प्रकार काष्ठा अणु
	__u8 flag;	/* 1: flags */
	__u8 rsrvd[3];
	__le32 size;		/* 4: size in byte */
	pxd_t loc;		/* 8: address and length in unit of fsblksize */
पूर्ण dxd_t;			/* - 16 - */

/* dxd_t flags */
#घोषणा	DXD_INDEX	0x80	/* B+-tree index */
#घोषणा	DXD_INLINE	0x40	/* in-line data extent */
#घोषणा	DXD_EXTENT	0x20	/* out-of-line single extent */
#घोषणा	DXD_खाता	0x10	/* out-of-line file (inode) */
#घोषणा DXD_CORRUPT	0x08	/* Inconsistency detected */

/* dxd_t field स्थिरruction
 */
#घोषणा	DXDlength(dxd, len)	PXDlength(&(dxd)->loc, len)
#घोषणा	DXDaddress(dxd, addr)	PXDaddress(&(dxd)->loc, addr)
#घोषणा	lengthDXD(dxd)	lengthPXD(&(dxd)->loc)
#घोषणा	addressDXD(dxd)	addressPXD(&(dxd)->loc)
#घोषणा DXDsize(dxd, size32) ((dxd)->size = cpu_to_le32(size32))
#घोषणा sizeDXD(dxd)	le32_to_cpu((dxd)->size)

/*
 *	directory entry argument
 */
काष्ठा component_name अणु
	पूर्णांक namlen;
	ब_अक्षर_प्रकार *name;
पूर्ण;


/*
 *	DASD limit inक्रमmation - stored in directory inode
 */
काष्ठा dasd अणु
	u8 thresh;		/* Alert Threshold (in percent)		*/
	u8 delta;		/* Alert Threshold delta (in percent)	*/
	u8 rsrvd1;
	u8 limit_hi;		/* DASD limit (in logical blocks)	*/
	__le32 limit_lo;	/* DASD limit (in logical blocks)	*/
	u8 rsrvd2[3];
	u8 used_hi;		/* DASD usage (in logical blocks)	*/
	__le32 used_lo;		/* DASD usage (in logical blocks)	*/
पूर्ण;

#घोषणा DASDLIMIT(dasdp) \
	(((u64)((dasdp)->limit_hi) << 32) + __le32_to_cpu((dasdp)->limit_lo))
#घोषणा setDASDLIMIT(dasdp, limit)\
अणु\
	(dasdp)->limit_hi = ((u64)limit) >> 32;\
	(dasdp)->limit_lo = __cpu_to_le32(limit);\
पूर्ण
#घोषणा DASDUSED(dasdp) \
	(((u64)((dasdp)->used_hi) << 32) + __le32_to_cpu((dasdp)->used_lo))
#घोषणा setDASDUSED(dasdp, used)\
अणु\
	(dasdp)->used_hi = ((u64)used) >> 32;\
	(dasdp)->used_lo = __cpu_to_le32(used);\
पूर्ण

#पूर्ण_अगर				/* !_H_JFS_TYPES */
