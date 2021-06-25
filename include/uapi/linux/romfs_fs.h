<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_ROMFS_FS_H
#घोषणा __LINUX_ROMFS_FS_H

#समावेश <linux/types.h>
#समावेश <linux/fs.h>

/* The basic काष्ठाures of the romfs fileप्रणाली */

#घोषणा ROMBSIZE BLOCK_SIZE
#घोषणा ROMBSBITS BLOCK_SIZE_BITS
#घोषणा ROMBMASK (ROMBSIZE-1)
#घोषणा ROMFS_MAGIC 0x7275

#घोषणा ROMFS_MAXFN 128

#घोषणा __mkw(h,l) (((h)&0x00ff)<< 8|((l)&0x00ff))
#घोषणा __mkl(h,l) (((h)&0xffff)<<16|((l)&0xffff))
#घोषणा __mk4(a,b,c,d) cpu_to_be32(__mkl(__mkw(a,b),__mkw(c,d)))
#घोषणा ROMSB_WORD0 __mk4('-','r','o','m')
#घोषणा ROMSB_WORD1 __mk4('1','f','s','-')

/* On-disk "super block" */

काष्ठा romfs_super_block अणु
	__be32 word0;
	__be32 word1;
	__be32 size;
	__be32 checksum;
	अक्षर name[0];		/* volume name */
पूर्ण;

/* On disk inode */

काष्ठा romfs_inode अणु
	__be32 next;		/* low 4 bits see ROMFH_ */
	__be32 spec;
	__be32 size;
	__be32 checksum;
	अक्षर name[0];
पूर्ण;

#घोषणा ROMFH_TYPE 7
#घोषणा ROMFH_HRD 0
#घोषणा ROMFH_सूची 1
#घोषणा ROMFH_REG 2
#घोषणा ROMFH_SYM 3
#घोषणा ROMFH_BLK 4
#घोषणा ROMFH_CHR 5
#घोषणा ROMFH_SCK 6
#घोषणा ROMFH_FIF 7
#घोषणा ROMFH_EXEC 8

/* Alignment */

#घोषणा ROMFH_SIZE 16
#घोषणा ROMFH_PAD (ROMFH_SIZE-1)
#घोषणा ROMFH_MASK (~ROMFH_PAD)

#पूर्ण_अगर
