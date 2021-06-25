<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CEPH_STRIPER_H
#घोषणा _LINUX_CEPH_STRIPER_H

#समावेश <linux/list.h>
#समावेश <linux/types.h>

काष्ठा ceph_file_layout;

व्योम ceph_calc_file_object_mapping(काष्ठा ceph_file_layout *l,
				   u64 off, u64 len,
				   u64 *objno, u64 *objoff, u32 *xlen);

काष्ठा ceph_object_extent अणु
	काष्ठा list_head oe_item;
	u64 oe_objno;
	u64 oe_off;
	u64 oe_len;
पूर्ण;

अटल अंतरभूत व्योम ceph_object_extent_init(काष्ठा ceph_object_extent *ex)
अणु
	INIT_LIST_HEAD(&ex->oe_item);
पूर्ण

/*
 * Called क्रम each mapped stripe unit.
 *
 * @bytes: number of bytes mapped, i.e. the minimum of the full length
 *         requested (file extent length) or the reमुख्यder of the stripe
 *         unit within an object
 */
प्रकार व्योम (*ceph_object_extent_fn_t)(काष्ठा ceph_object_extent *ex,
					u32 bytes, व्योम *arg);

पूर्णांक ceph_file_to_extents(काष्ठा ceph_file_layout *l, u64 off, u64 len,
			 काष्ठा list_head *object_extents,
			 काष्ठा ceph_object_extent *alloc_fn(व्योम *arg),
			 व्योम *alloc_arg,
			 ceph_object_extent_fn_t action_fn,
			 व्योम *action_arg);
पूर्णांक ceph_iterate_extents(काष्ठा ceph_file_layout *l, u64 off, u64 len,
			 काष्ठा list_head *object_extents,
			 ceph_object_extent_fn_t action_fn,
			 व्योम *action_arg);

काष्ठा ceph_file_extent अणु
	u64 fe_off;
	u64 fe_len;
पूर्ण;

अटल अंतरभूत u64 ceph_file_extents_bytes(काष्ठा ceph_file_extent *file_extents,
					  u32 num_file_extents)
अणु
	u64 bytes = 0;
	u32 i;

	क्रम (i = 0; i < num_file_extents; i++)
		bytes += file_extents[i].fe_len;

	वापस bytes;
पूर्ण

पूर्णांक ceph_extent_to_file(काष्ठा ceph_file_layout *l,
			u64 objno, u64 objoff, u64 objlen,
			काष्ठा ceph_file_extent **file_extents,
			u32 *num_file_extents);

u64 ceph_get_num_objects(काष्ठा ceph_file_layout *l, u64 size);

#पूर्ण_अगर
