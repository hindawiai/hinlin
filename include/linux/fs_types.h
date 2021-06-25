<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FS_TYPES_H
#घोषणा _LINUX_FS_TYPES_H

/*
 * This is a header क्रम the common implementation of dirent
 * to fs on-disk file type conversion.  Although the fs on-disk
 * bits are specअगरic to every file प्रणाली, in practice, many
 * file प्रणालीs use the exact same on-disk क्रमmat to describe
 * the lower 3 file type bits that represent the 7 POSIX file
 * types.
 *
 * It is important to note that the definitions in this
 * header MUST NOT change. This would अवरोध both the
 * userspace ABI and the on-disk क्रमmat of fileप्रणालीs
 * using this code.
 *
 * All those file प्रणालीs can use this generic code क्रम the
 * conversions.
 */

/*
 * काष्ठा dirent file types
 * exposed to user via getdents(2), सूची_पढ़ो(3)
 *
 * These match bits 12..15 of stat.st_mode
 * (ie "(i_mode >> 12) & 15").
 */
#घोषणा S_DT_SHIFT	12
#घोषणा S_DT(mode)	(((mode) & S_IFMT) >> S_DT_SHIFT)
#घोषणा S_DT_MASK	(S_IFMT >> S_DT_SHIFT)

/* these are defined by POSIX and also present in glibc's dirent.h */
#घोषणा DT_UNKNOWN	0
#घोषणा DT_FIFO		1
#घोषणा DT_CHR		2
#घोषणा DT_सूची		4
#घोषणा DT_BLK		6
#घोषणा DT_REG		8
#घोषणा DT_LNK		10
#घोषणा DT_SOCK		12
#घोषणा DT_WHT		14

#घोषणा DT_MAX		(S_DT_MASK + 1) /* 16 */

/*
 * fs on-disk file types.
 * Only the low 3 bits are used क्रम the POSIX file types.
 * Other bits are reserved क्रम fs निजी use.
 * These definitions are shared and used by multiple fileप्रणालीs,
 * and MUST NOT change under any circumstances.
 *
 * Note that no fs currently stores the whiteout type on-disk,
 * so whiteout dirents are exposed to user as DT_CHR.
 */
#घोषणा FT_UNKNOWN	0
#घोषणा FT_REG_खाता	1
#घोषणा FT_सूची		2
#घोषणा FT_CHRDEV	3
#घोषणा FT_BLKDEV	4
#घोषणा FT_FIFO		5
#घोषणा FT_SOCK		6
#घोषणा FT_SYMLINK	7

#घोषणा FT_MAX		8

/*
 * declarations क्रम helper functions, accompanying implementation
 * is in fs/fs_types.c
 */
बाह्य अचिन्हित अक्षर fs_ftype_to_dtype(अचिन्हित पूर्णांक filetype);
बाह्य अचिन्हित अक्षर fs_umode_to_ftype(umode_t mode);
बाह्य अचिन्हित अक्षर fs_umode_to_dtype(umode_t mode);

#पूर्ण_अगर
