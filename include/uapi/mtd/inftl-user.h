<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Parts of INFTL headers shared with userspace
 *
 */

#अगर_अघोषित __MTD_INFTL_USER_H__
#घोषणा __MTD_INFTL_USER_H__

#समावेश <linux/types.h>

#घोषणा	OSAK_VERSION	0x5120
#घोषणा	PERCENTUSED	98

#घोषणा	SECTORSIZE	512

/* Block Control Inक्रमmation */

काष्ठा inftl_bci अणु
	__u8 ECCsig[6];
	__u8 Status;
	__u8 Status1;
पूर्ण __attribute__((packed));

काष्ठा inftl_unithead1 अणु
	__u16 भवUnitNo;
	__u16 prevUnitNo;
	__u8 ANAC;
	__u8 NACs;
	__u8 parityPerField;
	__u8 discarded;
पूर्ण __attribute__((packed));

काष्ठा inftl_unithead2 अणु
	__u8 parityPerField;
	__u8 ANAC;
	__u16 prevUnitNo;
	__u16 भवUnitNo;
	__u8 NACs;
	__u8 discarded;
पूर्ण __attribute__((packed));

काष्ठा inftl_unittail अणु
	__u8 Reserved[4];
	__u16 EraseMark;
	__u16 EraseMark1;
पूर्ण __attribute__((packed));

जोड़ inftl_uci अणु
	काष्ठा inftl_unithead1 a;
	काष्ठा inftl_unithead2 b;
	काष्ठा inftl_unittail c;
पूर्ण;

काष्ठा inftl_oob अणु
	काष्ठा inftl_bci b;
	जोड़ inftl_uci u;
पूर्ण;


/* INFTL Media Header */

काष्ठा INFTLPartition अणु
	__u32 भवUnits;
	__u32 firstUnit;
	__u32 lastUnit;
	__u32 flags;
	__u32 spareUnits;
	__u32 Reserved0;
	__u32 Reserved1;
पूर्ण __attribute__((packed));

काष्ठा INFTLMediaHeader अणु
	अक्षर bootRecordID[8];
	__u32 NoOfBootImageBlocks;
	__u32 NoOfBinaryPartitions;
	__u32 NoOfBDTLPartitions;
	__u32 BlockMultiplierBits;
	__u32 FormatFlags;
	__u32 OsakVersion;
	__u32 PercentUsed;
	काष्ठा INFTLPartition Partitions[4];
पूर्ण __attribute__((packed));

/* Partition flag types */
#घोषणा	INFTL_BINARY	0x20000000
#घोषणा	INFTL_BDTL	0x40000000
#घोषणा	INFTL_LAST	0x80000000

#पूर्ण_अगर /* __MTD_INFTL_USER_H__ */


