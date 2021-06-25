<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __INODE_DOT_H__
#घोषणा __INODE_DOT_H__

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mm.h>
#समावेश "util.h"

बाह्य पूर्णांक gfs2_releasepage(काष्ठा page *page, gfp_t gfp_mask);
बाह्य पूर्णांक gfs2_पूर्णांकernal_पढ़ो(काष्ठा gfs2_inode *ip,
			      अक्षर *buf, loff_t *pos, अचिन्हित size);
बाह्य व्योम gfs2_set_aops(काष्ठा inode *inode);

अटल अंतरभूत पूर्णांक gfs2_is_stuffed(स्थिर काष्ठा gfs2_inode *ip)
अणु
	वापस !ip->i_height;
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_is_jdata(स्थिर काष्ठा gfs2_inode *ip)
अणु
	वापस ip->i_diskflags & GFS2_DIF_JDATA;
पूर्ण

अटल अंतरभूत bool gfs2_is_ordered(स्थिर काष्ठा gfs2_sbd *sdp)
अणु
	वापस sdp->sd_args.ar_data == GFS2_DATA_ORDERED;
पूर्ण

अटल अंतरभूत bool gfs2_is_ग_लिखोback(स्थिर काष्ठा gfs2_sbd *sdp)
अणु
	वापस sdp->sd_args.ar_data == GFS2_DATA_WRITEBACK;
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_is_dir(स्थिर काष्ठा gfs2_inode *ip)
अणु
	वापस S_ISसूची(ip->i_inode.i_mode);
पूर्ण

अटल अंतरभूत व्योम gfs2_set_inode_blocks(काष्ठा inode *inode, u64 blocks)
अणु
	inode->i_blocks = blocks <<
		(GFS2_SB(inode)->sd_sb.sb_bsize_shअगरt - GFS2_BASIC_BLOCK_SHIFT);
पूर्ण

अटल अंतरभूत u64 gfs2_get_inode_blocks(स्थिर काष्ठा inode *inode)
अणु
	वापस inode->i_blocks >>
		(GFS2_SB(inode)->sd_sb.sb_bsize_shअगरt - GFS2_BASIC_BLOCK_SHIFT);
पूर्ण

अटल अंतरभूत व्योम gfs2_add_inode_blocks(काष्ठा inode *inode, s64 change)
अणु
	change <<= inode->i_blkbits - GFS2_BASIC_BLOCK_SHIFT;
	gfs2_निश्चित(GFS2_SB(inode), (change >= 0 || inode->i_blocks >= -change));
	inode->i_blocks += change;
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_check_inum(स्थिर काष्ठा gfs2_inode *ip, u64 no_addr,
				  u64 no_क्रमmal_ino)
अणु
	वापस ip->i_no_addr == no_addr && ip->i_no_क्रमmal_ino == no_क्रमmal_ino;
पूर्ण

अटल अंतरभूत व्योम gfs2_inum_out(स्थिर काष्ठा gfs2_inode *ip,
				 काष्ठा gfs2_dirent *dent)
अणु
	dent->de_inum.no_क्रमmal_ino = cpu_to_be64(ip->i_no_क्रमmal_ino);
	dent->de_inum.no_addr = cpu_to_be64(ip->i_no_addr);
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_check_पूर्णांकernal_file_size(काष्ठा inode *inode,
						u64 minsize, u64 maxsize)
अणु
	u64 size = i_size_पढ़ो(inode);
	अगर (size < minsize || size > maxsize)
		जाओ err;
	अगर (size & (BIT(inode->i_blkbits) - 1))
		जाओ err;
	वापस 0;
err:
	gfs2_consist_inode(GFS2_I(inode));
	वापस -EIO;
पूर्ण

बाह्य काष्ठा inode *gfs2_inode_lookup(काष्ठा super_block *sb, अचिन्हित type, 
				       u64 no_addr, u64 no_क्रमmal_ino,
				       अचिन्हित पूर्णांक blktype);
बाह्य काष्ठा inode *gfs2_lookup_by_inum(काष्ठा gfs2_sbd *sdp, u64 no_addr,
					 u64 no_क्रमmal_ino,
					 अचिन्हित पूर्णांक blktype);

बाह्य पूर्णांक gfs2_inode_refresh(काष्ठा gfs2_inode *ip);

बाह्य काष्ठा inode *gfs2_lookupi(काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
				  पूर्णांक is_root);
बाह्य पूर्णांक gfs2_permission(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *inode, पूर्णांक mask);
बाह्य काष्ठा inode *gfs2_lookup_simple(काष्ठा inode *dip, स्थिर अक्षर *name);
बाह्य व्योम gfs2_dinode_out(स्थिर काष्ठा gfs2_inode *ip, व्योम *buf);
बाह्य पूर्णांक gfs2_खोलो_common(काष्ठा inode *inode, काष्ठा file *file);
बाह्य loff_t gfs2_seek_data(काष्ठा file *file, loff_t offset);
बाह्य loff_t gfs2_seek_hole(काष्ठा file *file, loff_t offset);

बाह्य स्थिर काष्ठा file_operations gfs2_file_fops_nolock;
बाह्य स्थिर काष्ठा file_operations gfs2_dir_fops_nolock;

बाह्य पूर्णांक gfs2_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
बाह्य पूर्णांक gfs2_fileattr_set(काष्ठा user_namespace *mnt_userns,
			     काष्ठा dentry *dentry, काष्ठा fileattr *fa);
बाह्य व्योम gfs2_set_inode_flags(काष्ठा inode *inode);
 
#अगर_घोषित CONFIG_GFS2_FS_LOCKING_DLM
बाह्य स्थिर काष्ठा file_operations gfs2_file_fops;
बाह्य स्थिर काष्ठा file_operations gfs2_dir_fops;

अटल अंतरभूत पूर्णांक gfs2_localflocks(स्थिर काष्ठा gfs2_sbd *sdp)
अणु
	वापस sdp->sd_args.ar_localflocks;
पूर्ण
#अन्यथा /* Single node only */
#घोषणा gfs2_file_fops gfs2_file_fops_nolock
#घोषणा gfs2_dir_fops gfs2_dir_fops_nolock

अटल अंतरभूत पूर्णांक gfs2_localflocks(स्थिर काष्ठा gfs2_sbd *sdp)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_GFS2_FS_LOCKING_DLM */

#पूर्ण_अगर /* __INODE_DOT_H__ */

