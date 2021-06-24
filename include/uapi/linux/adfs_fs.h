<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ADFS_FS_H
#घोषणा _UAPI_ADFS_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

/*
 * Disc Record at disc address 0xc00
 */
काष्ठा adfs_discrecord अणु
    __u8  log2secsize;
    __u8  secspertrack;
    __u8  heads;
    __u8  density;
    __u8  idlen;
    __u8  log2bpmb;
    __u8  skew;
    __u8  bootoption;
    __u8  lowsector;
    __u8  nzones;
    __le16 zone_spare;
    __le32 root;
    __le32 disc_size;
    __le16 disc_id;
    __u8  disc_name[10];
    __le32 disc_type;
    __le32 disc_size_high;
    __u8  log2sharesize:4;
    __u8  unused40:4;
    __u8  big_flag:1;
    __u8  unused41:7;
    __u8  nzones_high;
    __u8  reserved43;
    __le32 क्रमmat_version;
    __le32 root_size;
    __u8  unused52[60 - 52];
पूर्ण __attribute__((packed, aligned(4)));

#घोषणा ADFS_DISCRECORD		(0xc00)
#घोषणा ADFS_DR_OFFSET		(0x1c0)
#घोषणा ADFS_DR_SIZE		 60
#घोषणा ADFS_DR_SIZE_BITS	(ADFS_DR_SIZE << 3)

#पूर्ण_अगर /* _UAPI_ADFS_FS_H */
