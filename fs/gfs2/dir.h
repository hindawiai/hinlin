<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __सूची_DOT_H__
#घोषणा __सूची_DOT_H__

#समावेश <linux/dcache.h>
#समावेश <linux/crc32.h>

काष्ठा inode;
काष्ठा gfs2_inode;
काष्ठा gfs2_inum;
काष्ठा buffer_head;
काष्ठा gfs2_dirent;

काष्ठा gfs2_diradd अणु
	अचिन्हित nr_blocks;
	काष्ठा gfs2_dirent *dent;
	काष्ठा buffer_head *bh;
	पूर्णांक save_loc;
पूर्ण;

बाह्य काष्ठा inode *gfs2_dir_search(काष्ठा inode *dir,
				     स्थिर काष्ठा qstr *filename,
				     bool fail_on_exist);
बाह्य पूर्णांक gfs2_dir_check(काष्ठा inode *dir, स्थिर काष्ठा qstr *filename,
			  स्थिर काष्ठा gfs2_inode *ip);
बाह्य पूर्णांक gfs2_dir_add(काष्ठा inode *inode, स्थिर काष्ठा qstr *filename,
			स्थिर काष्ठा gfs2_inode *ip, काष्ठा gfs2_diradd *da);
अटल अंतरभूत व्योम gfs2_dir_no_add(काष्ठा gfs2_diradd *da)
अणु
	brअन्यथा(da->bh);
	da->bh = शून्य;
पूर्ण
बाह्य पूर्णांक gfs2_dir_del(काष्ठा gfs2_inode *dip, स्थिर काष्ठा dentry *dentry);
बाह्य पूर्णांक gfs2_dir_पढ़ो(काष्ठा inode *inode, काष्ठा dir_context *ctx,
			 काष्ठा file_ra_state *f_ra);
बाह्य पूर्णांक gfs2_dir_mvino(काष्ठा gfs2_inode *dip, स्थिर काष्ठा qstr *filename,
			  स्थिर काष्ठा gfs2_inode *nip, अचिन्हित पूर्णांक new_type);

बाह्य पूर्णांक gfs2_dir_exhash_dealloc(काष्ठा gfs2_inode *dip);

बाह्य पूर्णांक gfs2_diradd_alloc_required(काष्ठा inode *dir,
				      स्थिर काष्ठा qstr *filename,
				      काष्ठा gfs2_diradd *da);
बाह्य पूर्णांक gfs2_dir_get_new_buffer(काष्ठा gfs2_inode *ip, u64 block,
				   काष्ठा buffer_head **bhp);
बाह्य व्योम gfs2_dir_hash_inval(काष्ठा gfs2_inode *ip);

अटल अंतरभूत u32 gfs2_disk_hash(स्थिर अक्षर *data, पूर्णांक len)
अणु
        वापस crc32_le((u32)~0, data, len) ^ (u32)~0;
पूर्ण


अटल अंतरभूत व्योम gfs2_str2qstr(काष्ठा qstr *name, स्थिर अक्षर *fname)
अणु
	name->name = fname;
	name->len = म_माप(fname);
	name->hash = gfs2_disk_hash(name->name, name->len);
पूर्ण

/* N.B. This probably ought to take inum & type as args as well */
अटल अंतरभूत व्योम gfs2_qstr2dirent(स्थिर काष्ठा qstr *name, u16 reclen, काष्ठा gfs2_dirent *dent)
अणु
	dent->de_inum.no_addr = cpu_to_be64(0);
	dent->de_inum.no_क्रमmal_ino = cpu_to_be64(0);
	dent->de_hash = cpu_to_be32(name->hash);
	dent->de_rec_len = cpu_to_be16(reclen);
	dent->de_name_len = cpu_to_be16(name->len);
	dent->de_type = cpu_to_be16(0);
	स_रखो(dent->__pad, 0, माप(dent->__pad));
	स_नकल(dent + 1, name->name, name->len);
पूर्ण

बाह्य काष्ठा qstr gfs2_qकरोt;
बाह्य काष्ठा qstr gfs2_qकरोtकरोt;

#पूर्ण_अगर /* __सूची_DOT_H__ */
