<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/fs/adfs/dir_fplus.h
 *
 *  Copyright (C) 1999 Russell King
 *
 *  Structures of directories on the F+ क्रमmat disk
 */

#घोषणा ADFS_FPLUS_NAME_LEN	255

#घोषणा BIGसूचीSTARTNAME ('S' | 'B' << 8 | 'P' << 16 | 'r' << 24)
#घोषणा BIGसूचीENDNAME	('o' | 'v' << 8 | 'e' << 16 | 'n' << 24)

काष्ठा adfs_bigdirheader अणु
	__u8	starपंचांगasseq;
	__u8	bigdirversion[3];
	__le32	bigdirstartname;
	__le32	bigस_नामlen;
	__le32	bigdirsize;
	__le32	bigdirentries;
	__le32	bigस_नामsize;
	__le32	bigdirparent;
	अक्षर	bigस_नाम[1];
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा adfs_bigdirentry अणु
	__le32	bigdirload;
	__le32	bigdirexec;
	__le32	bigdirlen;
	__le32	bigdirindaddr;
	__le32	bigdirattr;
	__le32	bigdirobnamelen;
	__le32	bigdirobnameptr;
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा adfs_bigdirtail अणु
	__le32	bigdirendname;
	__u8	bigdirendmasseq;
	__u8	reserved[2];
	__u8	bigdircheckbyte;
पूर्ण __attribute__((packed, aligned(4)));
