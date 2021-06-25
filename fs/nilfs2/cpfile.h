<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * cpfile.h - NILFS checkpoपूर्णांक file.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#अगर_अघोषित _NILFS_CPखाता_H
#घोषणा _NILFS_CPखाता_H

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/nilfs2_api.h>		/* nilfs_cpstat */
#समावेश <linux/nilfs2_ondisk.h>	/* nilfs_inode, nilfs_checkpoपूर्णांक */


पूर्णांक nilfs_cpfile_get_checkpoपूर्णांक(काष्ठा inode *, __u64, पूर्णांक,
				काष्ठा nilfs_checkpoपूर्णांक **,
				काष्ठा buffer_head **);
व्योम nilfs_cpfile_put_checkpoपूर्णांक(काष्ठा inode *, __u64, काष्ठा buffer_head *);
पूर्णांक nilfs_cpfile_delete_checkpoपूर्णांकs(काष्ठा inode *, __u64, __u64);
पूर्णांक nilfs_cpfile_delete_checkpoपूर्णांक(काष्ठा inode *, __u64);
पूर्णांक nilfs_cpfile_change_cpmode(काष्ठा inode *, __u64, पूर्णांक);
पूर्णांक nilfs_cpfile_is_snapshot(काष्ठा inode *, __u64);
पूर्णांक nilfs_cpfile_get_stat(काष्ठा inode *, काष्ठा nilfs_cpstat *);
sमाप_प्रकार nilfs_cpfile_get_cpinfo(काष्ठा inode *, __u64 *, पूर्णांक, व्योम *,
				अचिन्हित पूर्णांक, माप_प्रकार);

पूर्णांक nilfs_cpfile_पढ़ो(काष्ठा super_block *sb, माप_प्रकार cpsize,
		      काष्ठा nilfs_inode *raw_inode, काष्ठा inode **inodep);

#पूर्ण_अगर	/* _NILFS_CPखाता_H */
