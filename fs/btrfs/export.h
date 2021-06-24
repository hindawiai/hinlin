<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_EXPORT_H
#घोषणा BTRFS_EXPORT_H

#समावेश <linux/exportfs.h>

बाह्य स्थिर काष्ठा export_operations btrfs_export_ops;

काष्ठा btrfs_fid अणु
	u64 objectid;
	u64 root_objectid;
	u32 gen;

	u64 parent_objectid;
	u32 parent_gen;

	u64 parent_root_objectid;
पूर्ण __attribute__ ((packed));

काष्ठा dentry *btrfs_get_dentry(काष्ठा super_block *sb, u64 objectid,
				u64 root_objectid, u32 generation,
				पूर्णांक check_generation);
काष्ठा dentry *btrfs_get_parent(काष्ठा dentry *child);

#पूर्ण_अगर
