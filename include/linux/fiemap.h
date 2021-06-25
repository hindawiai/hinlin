<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FIEMAP_H
#घोषणा _LINUX_FIEMAP_H 1

#समावेश <uapi/linux/fiemap.h>
#समावेश <linux/fs.h>

काष्ठा fiemap_extent_info अणु
	अचिन्हित पूर्णांक fi_flags;		/* Flags as passed from user */
	अचिन्हित पूर्णांक fi_extents_mapped;	/* Number of mapped extents */
	अचिन्हित पूर्णांक fi_extents_max;	/* Size of fiemap_extent array */
	काष्ठा fiemap_extent __user *fi_extents_start; /* Start of
							fiemap_extent array */
पूर्ण;

पूर्णांक fiemap_prep(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		u64 start, u64 *len, u32 supported_flags);
पूर्णांक fiemap_fill_next_extent(काष्ठा fiemap_extent_info *info, u64 logical,
			    u64 phys, u64 len, u32 flags);

पूर्णांक generic_block_fiemap(काष्ठा inode *inode,
		काष्ठा fiemap_extent_info *fieinfo, u64 start, u64 len,
		get_block_t *get_block);

#पूर्ण_अगर /* _LINUX_FIEMAP_H 1 */
