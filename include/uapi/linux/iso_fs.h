<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ISOFS_FS_H
#घोषणा _ISOFS_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

/*
 * The isofs fileप्रणाली स्थिरants/काष्ठाures
 */

/* This part borrowed from the bsd386 isofs */
#घोषणा ISODCL(from, to) (to - from + 1)

काष्ठा iso_volume_descriptor अणु
	__u8 type[ISODCL(1,1)]; /* 711 */
	अक्षर id[ISODCL(2,6)];
	__u8 version[ISODCL(7,7)];
	__u8 data[ISODCL(8,2048)];
पूर्ण;

/* volume descriptor types */
#घोषणा ISO_VD_PRIMARY 1
#घोषणा ISO_VD_SUPPLEMENTARY 2
#घोषणा ISO_VD_END 255

#घोषणा ISO_STANDARD_ID "CD001"

काष्ठा iso_primary_descriptor अणु
	__u8 type			[ISODCL (  1,   1)]; /* 711 */
	अक्षर id				[ISODCL (  2,   6)];
	__u8 version			[ISODCL (  7,   7)]; /* 711 */
	__u8 unused1			[ISODCL (  8,   8)];
	अक्षर प्रणाली_id			[ISODCL (  9,  40)]; /* aअक्षरs */
	अक्षर volume_id			[ISODCL ( 41,  72)]; /* dअक्षरs */
	__u8 unused2			[ISODCL ( 73,  80)];
	__u8 volume_space_size		[ISODCL ( 81,  88)]; /* 733 */
	__u8 unused3			[ISODCL ( 89, 120)];
	__u8 volume_set_size		[ISODCL (121, 124)]; /* 723 */
	__u8 volume_sequence_number	[ISODCL (125, 128)]; /* 723 */
	__u8 logical_block_size		[ISODCL (129, 132)]; /* 723 */
	__u8 path_table_size		[ISODCL (133, 140)]; /* 733 */
	__u8 type_l_path_table		[ISODCL (141, 144)]; /* 731 */
	__u8 opt_type_l_path_table	[ISODCL (145, 148)]; /* 731 */
	__u8 type_m_path_table		[ISODCL (149, 152)]; /* 732 */
	__u8 opt_type_m_path_table	[ISODCL (153, 156)]; /* 732 */
	__u8 root_directory_record	[ISODCL (157, 190)]; /* 9.1 */
	अक्षर volume_set_id		[ISODCL (191, 318)]; /* dअक्षरs */
	अक्षर publisher_id		[ISODCL (319, 446)]; /* aअक्षरs */
	अक्षर preparer_id		[ISODCL (447, 574)]; /* aअक्षरs */
	अक्षर application_id		[ISODCL (575, 702)]; /* aअक्षरs */
	अक्षर copyright_file_id		[ISODCL (703, 739)]; /* 7.5 dअक्षरs */
	अक्षर असलtract_file_id		[ISODCL (740, 776)]; /* 7.5 dअक्षरs */
	अक्षर bibliographic_file_id	[ISODCL (777, 813)]; /* 7.5 dअक्षरs */
	__u8 creation_date		[ISODCL (814, 830)]; /* 8.4.26.1 */
	__u8 modअगरication_date		[ISODCL (831, 847)]; /* 8.4.26.1 */
	__u8 expiration_date		[ISODCL (848, 864)]; /* 8.4.26.1 */
	__u8 effective_date		[ISODCL (865, 881)]; /* 8.4.26.1 */
	__u8 file_काष्ठाure_version	[ISODCL (882, 882)]; /* 711 */
	__u8 unused4			[ISODCL (883, 883)];
	__u8 application_data		[ISODCL (884, 1395)];
	__u8 unused5			[ISODCL (1396, 2048)];
पूर्ण;

/* Almost the same as the primary descriptor but two fields are specअगरied */
काष्ठा iso_supplementary_descriptor अणु
	__u8 type			[ISODCL (  1,   1)]; /* 711 */
	अक्षर id				[ISODCL (  2,   6)];
	__u8 version			[ISODCL (  7,   7)]; /* 711 */
	__u8 flags			[ISODCL (  8,   8)]; /* 853 */
	अक्षर प्रणाली_id			[ISODCL (  9,  40)]; /* aअक्षरs */
	अक्षर volume_id			[ISODCL ( 41,  72)]; /* dअक्षरs */
	__u8 unused2			[ISODCL ( 73,  80)];
	__u8 volume_space_size		[ISODCL ( 81,  88)]; /* 733 */
	__u8 escape			[ISODCL ( 89, 120)]; /* 856 */
	__u8 volume_set_size		[ISODCL (121, 124)]; /* 723 */
	__u8 volume_sequence_number	[ISODCL (125, 128)]; /* 723 */
	__u8 logical_block_size		[ISODCL (129, 132)]; /* 723 */
	__u8 path_table_size		[ISODCL (133, 140)]; /* 733 */
	__u8 type_l_path_table		[ISODCL (141, 144)]; /* 731 */
	__u8 opt_type_l_path_table	[ISODCL (145, 148)]; /* 731 */
	__u8 type_m_path_table		[ISODCL (149, 152)]; /* 732 */
	__u8 opt_type_m_path_table	[ISODCL (153, 156)]; /* 732 */
	__u8 root_directory_record	[ISODCL (157, 190)]; /* 9.1 */
	अक्षर volume_set_id		[ISODCL (191, 318)]; /* dअक्षरs */
	अक्षर publisher_id		[ISODCL (319, 446)]; /* aअक्षरs */
	अक्षर preparer_id		[ISODCL (447, 574)]; /* aअक्षरs */
	अक्षर application_id		[ISODCL (575, 702)]; /* aअक्षरs */
	अक्षर copyright_file_id		[ISODCL (703, 739)]; /* 7.5 dअक्षरs */
	अक्षर असलtract_file_id		[ISODCL (740, 776)]; /* 7.5 dअक्षरs */
	अक्षर bibliographic_file_id	[ISODCL (777, 813)]; /* 7.5 dअक्षरs */
	__u8 creation_date		[ISODCL (814, 830)]; /* 8.4.26.1 */
	__u8 modअगरication_date		[ISODCL (831, 847)]; /* 8.4.26.1 */
	__u8 expiration_date		[ISODCL (848, 864)]; /* 8.4.26.1 */
	__u8 effective_date		[ISODCL (865, 881)]; /* 8.4.26.1 */
	__u8 file_काष्ठाure_version	[ISODCL (882, 882)]; /* 711 */
	__u8 unused4			[ISODCL (883, 883)];
	__u8 application_data		[ISODCL (884, 1395)];
	__u8 unused5			[ISODCL (1396, 2048)];
पूर्ण;


#घोषणा HS_STANDARD_ID "CDROM"

काष्ठा  hs_volume_descriptor अणु
	__u8 foo			[ISODCL (  1,   8)]; /* 733 */
	__u8 type			[ISODCL (  9,   9)]; /* 711 */
	अक्षर id				[ISODCL ( 10,  14)];
	__u8 version			[ISODCL ( 15,  15)]; /* 711 */
	__u8 data[ISODCL(16,2048)];
पूर्ण;


काष्ठा hs_primary_descriptor अणु
	__u8 foo			[ISODCL (  1,   8)]; /* 733 */
	__u8 type			[ISODCL (  9,   9)]; /* 711 */
	__u8 id				[ISODCL ( 10,  14)];
	__u8 version			[ISODCL ( 15,  15)]; /* 711 */
	__u8 unused1			[ISODCL ( 16,  16)]; /* 711 */
	अक्षर प्रणाली_id			[ISODCL ( 17,  48)]; /* aअक्षरs */
	अक्षर volume_id			[ISODCL ( 49,  80)]; /* dअक्षरs */
	__u8 unused2			[ISODCL ( 81,  88)]; /* 733 */
	__u8 volume_space_size		[ISODCL ( 89,  96)]; /* 733 */
	__u8 unused3			[ISODCL ( 97, 128)]; /* 733 */
	__u8 volume_set_size		[ISODCL (129, 132)]; /* 723 */
	__u8 volume_sequence_number	[ISODCL (133, 136)]; /* 723 */
	__u8 logical_block_size		[ISODCL (137, 140)]; /* 723 */
	__u8 path_table_size		[ISODCL (141, 148)]; /* 733 */
	__u8 type_l_path_table		[ISODCL (149, 152)]; /* 731 */
	__u8 unused4			[ISODCL (153, 180)]; /* 733 */
	__u8 root_directory_record	[ISODCL (181, 214)]; /* 9.1 */
पूर्ण;

/* We use this to help us look up the parent inode numbers. */

काष्ठा iso_path_tableअणु
	__u8  name_len[2];	/* 721 */
	__u8  extent[4];	/* 731 */
	__u8  parent[2];	/* 721 */
	अक्षर name[0];
पूर्ण __attribute__((packed));

/* high sierra is identical to iso, except that the date is only 6 bytes, and
   there is an extra reserved byte after the flags */

काष्ठा iso_directory_record अणु
	__u8 length			[ISODCL (1, 1)]; /* 711 */
	__u8 ext_attr_length		[ISODCL (2, 2)]; /* 711 */
	__u8 extent			[ISODCL (3, 10)]; /* 733 */
	__u8 size			[ISODCL (11, 18)]; /* 733 */
	__u8 date			[ISODCL (19, 25)]; /* 7 by 711 */
	__u8 flags			[ISODCL (26, 26)];
	__u8 file_unit_size		[ISODCL (27, 27)]; /* 711 */
	__u8 पूर्णांकerleave			[ISODCL (28, 28)]; /* 711 */
	__u8 volume_sequence_number	[ISODCL (29, 32)]; /* 723 */
	__u8 name_len			[ISODCL (33, 33)]; /* 711 */
	अक्षर name			[0];
पूर्ण __attribute__((packed));

#घोषणा ISOFS_BLOCK_BITS 11
#घोषणा ISOFS_BLOCK_SIZE 2048

#घोषणा ISOFS_BUFFER_SIZE(INODE) ((INODE)->i_sb->s_blocksize)
#घोषणा ISOFS_BUFFER_BITS(INODE) ((INODE)->i_sb->s_blocksize_bits)

#पूर्ण_अगर /* _ISOFS_FS_H */
