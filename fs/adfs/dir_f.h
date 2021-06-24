<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/fs/adfs/dir_f.h
 *
 *  Copyright (C) 1999 Russell King
 *
 *  Structures of directories on the F क्रमmat disk
 */
#अगर_अघोषित ADFS_सूची_F_H
#घोषणा ADFS_सूची_F_H

/*
 * Directory header
 */
काष्ठा adfs_dirheader अणु
	__u8 starपंचांगasseq;
	__u8 startname[4];
पूर्ण __attribute__((packed));

#घोषणा ADFS_NEWसूची_SIZE	2048
#घोषणा ADFS_NUM_सूची_ENTRIES	77

/*
 * Directory entries
 */
काष्ठा adfs_direntry अणु
#घोषणा ADFS_F_NAME_LEN 10
	अक्षर dirobname[ADFS_F_NAME_LEN];
	__u8 dirload[4];
	__u8 direxec[4];
	__u8 dirlen[4];
	__u8 dirinddiscadd[3];
	__u8 newdiratts;
पूर्ण __attribute__((packed));

/*
 * Directory tail
 */
काष्ठा adfs_olddirtail अणु
	__u8 dirlasपंचांगask;
	अक्षर स_नाम[10];
	__u8 dirparent[3];
	अक्षर dirtitle[19];
	__u8 reserved[14];
	__u8 endmasseq;
	__u8 endname[4];
	__u8 dircheckbyte;
पूर्ण __attribute__((packed));

काष्ठा adfs_newdirtail अणु
	__u8 dirlasपंचांगask;
	__u8 reserved[2];
	__u8 dirparent[3];
	अक्षर dirtitle[19];
	अक्षर स_नाम[10];
	__u8 endmasseq;
	__u8 endname[4];
	__u8 dircheckbyte;
पूर्ण __attribute__((packed));

जोड़ adfs_dirtail अणु
	काष्ठा adfs_olddirtail old;
	काष्ठा adfs_newdirtail new;
पूर्ण;

#पूर्ण_अगर
