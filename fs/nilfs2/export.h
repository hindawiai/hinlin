<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित NILFS_EXPORT_H
#घोषणा NILFS_EXPORT_H

#समावेश <linux/exportfs.h>

बाह्य स्थिर काष्ठा export_operations nilfs_export_ops;

/**
 * काष्ठा nilfs_fid - NILFS file id type
 * @cno: checkpoपूर्णांक number
 * @ino: inode number
 * @gen: file generation (version) क्रम NFS
 * @parent_gen: parent generation (version) क्रम NFS
 * @parent_ino: parent inode number
 */
काष्ठा nilfs_fid अणु
	u64 cno;
	u64 ino;
	u32 gen;

	u32 parent_gen;
	u64 parent_ino;
पूर्ण __packed;

#पूर्ण_अगर
