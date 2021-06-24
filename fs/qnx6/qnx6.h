<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * QNX6 file प्रणाली, Linux implementation.
 *
 * Version : 1.0.0
 *
 * History :
 *
 * 01-02-2012 by Kai Bankett (chaosman@ontika.net) : first release.
 * 16-02-2012 page map extension by Al Viro
 *
 */

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>

प्रकार __u16 __bitwise __fs16;
प्रकार __u32 __bitwise __fs32;
प्रकार __u64 __bitwise __fs64;

#समावेश <linux/qnx6_fs.h>

काष्ठा qnx6_sb_info अणु
	काष्ठा buffer_head	*sb_buf;	/* superblock buffer */
	काष्ठा qnx6_super_block	*sb;		/* our superblock */
	पूर्णांक			s_blks_off;	/* blkoffset fs-startpoपूर्णांक */
	पूर्णांक			s_ptrbits;	/* indirect poपूर्णांकer bitfield */
	अचिन्हित दीर्घ		s_mount_opt;	/* all mount options */
	पूर्णांक			s_bytesex;	/* holds endianess info */
	काष्ठा inode *		inodes;
	काष्ठा inode *		दीर्घfile;
पूर्ण;

काष्ठा qnx6_inode_info अणु
	__fs32			di_block_ptr[QNX6_NO_सूचीECT_POINTERS];
	__u8			di_filelevels;
	__u32			i_dir_start_lookup;
	काष्ठा inode		vfs_inode;
पूर्ण;

बाह्य काष्ठा inode *qnx6_iget(काष्ठा super_block *sb, अचिन्हित ino);
बाह्य काष्ठा dentry *qnx6_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
					अचिन्हित पूर्णांक flags);

#अगर_घोषित CONFIG_QNX6FS_DEBUG
बाह्य व्योम qnx6_superblock_debug(काष्ठा qnx6_super_block *,
						काष्ठा super_block *);
#पूर्ण_अगर

बाह्य स्थिर काष्ठा inode_operations qnx6_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations qnx6_dir_operations;

अटल अंतरभूत काष्ठा qnx6_sb_info *QNX6_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा qnx6_inode_info *QNX6_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा qnx6_inode_info, vfs_inode);
पूर्ण

#घोषणा clear_opt(o, opt)		(o &= ~(QNX6_MOUNT_##opt))
#घोषणा set_opt(o, opt)			(o |= (QNX6_MOUNT_##opt))
#घोषणा test_opt(sb, opt)		(QNX6_SB(sb)->s_mount_opt & \
					 QNX6_MOUNT_##opt)
क्रमागत अणु
	BYTESEX_LE,
	BYTESEX_BE,
पूर्ण;

अटल अंतरभूत __u64 fs64_to_cpu(काष्ठा qnx6_sb_info *sbi, __fs64 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस le64_to_cpu((__क्रमce __le64)n);
	अन्यथा
		वापस be64_to_cpu((__क्रमce __be64)n);
पूर्ण

अटल अंतरभूत __fs64 cpu_to_fs64(काष्ठा qnx6_sb_info *sbi, __u64 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस (__क्रमce __fs64)cpu_to_le64(n);
	अन्यथा
		वापस (__क्रमce __fs64)cpu_to_be64(n);
पूर्ण

अटल अंतरभूत __u32 fs32_to_cpu(काष्ठा qnx6_sb_info *sbi, __fs32 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस le32_to_cpu((__क्रमce __le32)n);
	अन्यथा
		वापस be32_to_cpu((__क्रमce __be32)n);
पूर्ण

अटल अंतरभूत __fs32 cpu_to_fs32(काष्ठा qnx6_sb_info *sbi, __u32 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस (__क्रमce __fs32)cpu_to_le32(n);
	अन्यथा
		वापस (__क्रमce __fs32)cpu_to_be32(n);
पूर्ण

अटल अंतरभूत __u16 fs16_to_cpu(काष्ठा qnx6_sb_info *sbi, __fs16 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस le16_to_cpu((__क्रमce __le16)n);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)n);
पूर्ण

अटल अंतरभूत __fs16 cpu_to_fs16(काष्ठा qnx6_sb_info *sbi, __u16 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस (__क्रमce __fs16)cpu_to_le16(n);
	अन्यथा
		वापस (__क्रमce __fs16)cpu_to_be16(n);
पूर्ण

बाह्य काष्ठा qnx6_super_block *qnx6_mmi_fill_super(काष्ठा super_block *s,
						    पूर्णांक silent);

अटल अंतरभूत व्योम qnx6_put_page(काष्ठा page *page)
अणु
	kunmap(page);
	put_page(page);
पूर्ण

बाह्य अचिन्हित qnx6_find_entry(पूर्णांक len, काष्ठा inode *dir, स्थिर अक्षर *name,
				काष्ठा page **res_page);
