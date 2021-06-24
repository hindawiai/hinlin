<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VHOST_IOTLB_H
#घोषणा _LINUX_VHOST_IOTLB_H

#समावेश <linux/पूर्णांकerval_tree_generic.h>

काष्ठा vhost_iotlb_map अणु
	काष्ठा rb_node rb;
	काष्ठा list_head link;
	u64 start;
	u64 last;
	u64 size;
	u64 addr;
#घोषणा VHOST_MAP_RO 0x1
#घोषणा VHOST_MAP_WO 0x2
#घोषणा VHOST_MAP_RW 0x3
	u32 perm;
	u32 flags_padding;
	u64 __subtree_last;
पूर्ण;

#घोषणा VHOST_IOTLB_FLAG_RETIRE 0x1

काष्ठा vhost_iotlb अणु
	काष्ठा rb_root_cached root;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक nmaps;
	अचिन्हित पूर्णांक flags;
पूर्ण;

पूर्णांक vhost_iotlb_add_range(काष्ठा vhost_iotlb *iotlb, u64 start, u64 last,
			  u64 addr, अचिन्हित पूर्णांक perm);
व्योम vhost_iotlb_del_range(काष्ठा vhost_iotlb *iotlb, u64 start, u64 last);

काष्ठा vhost_iotlb *vhost_iotlb_alloc(अचिन्हित पूर्णांक limit, अचिन्हित पूर्णांक flags);
व्योम vhost_iotlb_मुक्त(काष्ठा vhost_iotlb *iotlb);
व्योम vhost_iotlb_reset(काष्ठा vhost_iotlb *iotlb);

काष्ठा vhost_iotlb_map *
vhost_iotlb_itree_first(काष्ठा vhost_iotlb *iotlb, u64 start, u64 last);
काष्ठा vhost_iotlb_map *
vhost_iotlb_itree_next(काष्ठा vhost_iotlb_map *map, u64 start, u64 last);

व्योम vhost_iotlb_map_मुक्त(काष्ठा vhost_iotlb *iotlb,
			  काष्ठा vhost_iotlb_map *map);
#पूर्ण_अगर
