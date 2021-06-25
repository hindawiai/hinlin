<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * dat.h - NILFS disk address translation.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#अगर_अघोषित _NILFS_DAT_H
#घोषणा _NILFS_DAT_H

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश <linux/nilfs2_ondisk.h>	/* nilfs_inode, nilfs_checkpoपूर्णांक */


काष्ठा nilfs_palloc_req;

पूर्णांक nilfs_dat_translate(काष्ठा inode *, __u64, sector_t *);

पूर्णांक nilfs_dat_prepare_alloc(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
व्योम nilfs_dat_commit_alloc(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
व्योम nilfs_dat_पात_alloc(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
पूर्णांक nilfs_dat_prepare_start(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
व्योम nilfs_dat_commit_start(काष्ठा inode *, काष्ठा nilfs_palloc_req *,
			    sector_t);
पूर्णांक nilfs_dat_prepare_end(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
व्योम nilfs_dat_commit_end(काष्ठा inode *, काष्ठा nilfs_palloc_req *, पूर्णांक);
व्योम nilfs_dat_पात_end(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
पूर्णांक nilfs_dat_prepare_update(काष्ठा inode *, काष्ठा nilfs_palloc_req *,
			     काष्ठा nilfs_palloc_req *);
व्योम nilfs_dat_commit_update(काष्ठा inode *, काष्ठा nilfs_palloc_req *,
			     काष्ठा nilfs_palloc_req *, पूर्णांक);
व्योम nilfs_dat_पात_update(काष्ठा inode *, काष्ठा nilfs_palloc_req *,
			    काष्ठा nilfs_palloc_req *);

पूर्णांक nilfs_dat_mark_dirty(काष्ठा inode *, __u64);
पूर्णांक nilfs_dat_मुक्तv(काष्ठा inode *, __u64 *, माप_प्रकार);
पूर्णांक nilfs_dat_move(काष्ठा inode *, __u64, sector_t);
sमाप_प्रकार nilfs_dat_get_vinfo(काष्ठा inode *, व्योम *, अचिन्हित पूर्णांक, माप_प्रकार);

पूर्णांक nilfs_dat_पढ़ो(काष्ठा super_block *sb, माप_प्रकार entry_size,
		   काष्ठा nilfs_inode *raw_inode, काष्ठा inode **inodep);

#पूर्ण_अगर	/* _NILFS_DAT_H */
