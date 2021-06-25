<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from work (c) 1995,1996 Christian Vogelgsang.
 * Portions derived from IRIX header files (c) 1988 Silicon Graphics
 */
#अगर_अघोषित _EFS_EFS_H_
#घोषणा _EFS_EFS_H_

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>

#घोषणा EFS_VERSION "1.0a"

अटल स्थिर अक्षर cprt[] = "EFS: "EFS_VERSION" - (c) 1999 Al Smith <Al.Smith@aeschi.ch.eu.org>";


/* 1 block is 512 bytes */
#घोषणा	EFS_BLOCKSIZE_BITS	9
#घोषणा	EFS_BLOCKSIZE		(1 << EFS_BLOCKSIZE_BITS)

प्रकार	पूर्णांक32_t		efs_block_t;
प्रकार uपूर्णांक32_t	efs_ino_t;

#घोषणा	EFS_सूचीECTEXTENTS	12

/*
 * layout of an extent, in memory and on disk. 8 bytes exactly.
 */
प्रकार जोड़ extent_u अणु
	अचिन्हित अक्षर raw[8];
	काष्ठा extent_s अणु
		अचिन्हित पूर्णांक	ex_magic:8;	/* magic # (zero) */
		अचिन्हित पूर्णांक	ex_bn:24;	/* basic block */
		अचिन्हित पूर्णांक	ex_length:8;	/* numblocks in this extent */
		अचिन्हित पूर्णांक	ex_offset:24;	/* logical offset पूर्णांकo file */
	पूर्ण cooked;
पूर्ण efs_extent;

प्रकार काष्ठा edevs अणु
	__be16		odev;
	__be32		ndev;
पूर्ण efs_devs;

/*
 * extent based fileप्रणाली inode as it appears on disk.  The efs inode
 * is exactly 128 bytes दीर्घ.
 */
काष्ठा	efs_dinode अणु
	__be16		di_mode;	/* mode and type of file */
	__be16		di_nlink;	/* number of links to file */
	__be16		di_uid;		/* owner's user id */
	__be16		di_gid;		/* owner's group id */
	__be32		di_size;	/* number of bytes in file */
	__be32		di_aसमय;	/* समय last accessed */
	__be32		di_mसमय;	/* समय last modअगरied */
	__be32		di_स_समय;	/* समय created */
	__be32		di_gen;		/* generation number */
	__be16		di_numextents;	/* # of extents */
	u_अक्षर		di_version;	/* version of inode */
	u_अक्षर		di_spare;	/* spare - used by AFS */
	जोड़ di_addr अणु
		efs_extent	di_extents[EFS_सूचीECTEXTENTS];
		efs_devs	di_dev;	/* device क्रम IFCHR/IFBLK */
	पूर्ण di_u;
पूर्ण;

/* efs inode storage in memory */
काष्ठा efs_inode_info अणु
	पूर्णांक		numextents;
	पूर्णांक		lastextent;

	efs_extent	extents[EFS_सूचीECTEXTENTS];
	काष्ठा inode	vfs_inode;
पूर्ण;

#समावेश <linux/efs_fs_sb.h>

#घोषणा EFS_सूचीBSIZE_BITS	EFS_BLOCKSIZE_BITS
#घोषणा EFS_सूचीBSIZE		(1 << EFS_सूचीBSIZE_BITS)

काष्ठा efs_dentry अणु
	__be32		inode;
	अचिन्हित अक्षर	namelen;
	अक्षर		name[3];
पूर्ण;

#घोषणा EFS_DENTSIZE	(माप(काष्ठा efs_dentry) - 3 + 1)
#घोषणा EFS_MAXNAMELEN  ((1 << (माप(अक्षर) * 8)) - 1)

#घोषणा EFS_सूचीBLK_HEADERSIZE	4
#घोषणा EFS_सूचीBLK_MAGIC	0xbeef	/* moo */

काष्ठा efs_dir अणु
	__be16	magic;
	अचिन्हित अक्षर	firstused;
	अचिन्हित अक्षर	slots;

	अचिन्हित अक्षर	space[EFS_सूचीBSIZE - EFS_सूचीBLK_HEADERSIZE];
पूर्ण;

#घोषणा EFS_MAXENTS \
	((EFS_सूचीBSIZE - EFS_सूचीBLK_HEADERSIZE) / \
	 (EFS_DENTSIZE + माप(अक्षर)))

#घोषणा EFS_SLOTAT(dir, slot) EFS_REALOFF((dir)->space[slot])

#घोषणा EFS_REALOFF(offset) ((offset << 1))


अटल अंतरभूत काष्ठा efs_inode_info *INODE_INFO(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा efs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा efs_sb_info *SUPER_INFO(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

काष्ठा statfs;
काष्ठा fid;

बाह्य स्थिर काष्ठा inode_operations efs_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations efs_dir_operations;
बाह्य स्थिर काष्ठा address_space_operations efs_symlink_aops;

बाह्य काष्ठा inode *efs_iget(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य efs_block_t efs_map_block(काष्ठा inode *, efs_block_t);
बाह्य पूर्णांक efs_get_block(काष्ठा inode *, sector_t, काष्ठा buffer_head *, पूर्णांक);

बाह्य काष्ठा dentry *efs_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);
बाह्य काष्ठा dentry *efs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type);
बाह्य काष्ठा dentry *efs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type);
बाह्य काष्ठा dentry *efs_get_parent(काष्ठा dentry *);
बाह्य पूर्णांक efs_bmap(काष्ठा inode *, पूर्णांक);

#पूर्ण_अगर /* _EFS_EFS_H_ */
