<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Red Hat, Inc.
 * Author: Jason Wang <jasowang@redhat.com>
 *
 * IOTLB implementation क्रम vhost.
 */
#समावेश <linux/slab.h>
#समावेश <linux/vhost_iotlb.h>
#समावेश <linux/module.h>

#घोषणा MOD_VERSION  "0.1"
#घोषणा MOD_DESC     "VHOST IOTLB"
#घोषणा MOD_AUTHOR   "Jason Wang <jasowang@redhat.com>"
#घोषणा MOD_LICENSE  "GPL v2"

#घोषणा START(map) ((map)->start)
#घोषणा LAST(map) ((map)->last)

INTERVAL_TREE_DEFINE(काष्ठा vhost_iotlb_map,
		     rb, __u64, __subtree_last,
		     START, LAST, अटल अंतरभूत, vhost_iotlb_itree);

/**
 * vhost_iotlb_map_मुक्त - हटाओ a map node and मुक्त it
 * @iotlb: the IOTLB
 * @map: the map that want to be हटाओ and मुक्तd
 */
व्योम vhost_iotlb_map_मुक्त(काष्ठा vhost_iotlb *iotlb,
			  काष्ठा vhost_iotlb_map *map)
अणु
	vhost_iotlb_itree_हटाओ(map, &iotlb->root);
	list_del(&map->link);
	kमुक्त(map);
	iotlb->nmaps--;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_map_मुक्त);

/**
 * vhost_iotlb_add_range - add a new range to vhost IOTLB
 * @iotlb: the IOTLB
 * @start: start of the IOVA range
 * @last: last of IOVA range
 * @addr: the address that is mapped to @start
 * @perm: access permission of this range
 *
 * Returns an error last is smaller than start or memory allocation
 * fails
 */
पूर्णांक vhost_iotlb_add_range(काष्ठा vhost_iotlb *iotlb,
			  u64 start, u64 last,
			  u64 addr, अचिन्हित पूर्णांक perm)
अणु
	काष्ठा vhost_iotlb_map *map;

	अगर (last < start)
		वापस -EFAULT;

	अगर (iotlb->limit &&
	    iotlb->nmaps == iotlb->limit &&
	    iotlb->flags & VHOST_IOTLB_FLAG_RETIRE) अणु
		map = list_first_entry(&iotlb->list, typeof(*map), link);
		vhost_iotlb_map_मुक्त(iotlb, map);
	पूर्ण

	map = kदो_स्मृति(माप(*map), GFP_ATOMIC);
	अगर (!map)
		वापस -ENOMEM;

	map->start = start;
	map->size = last - start + 1;
	map->last = last;
	map->addr = addr;
	map->perm = perm;

	iotlb->nmaps++;
	vhost_iotlb_itree_insert(map, &iotlb->root);

	INIT_LIST_HEAD(&map->link);
	list_add_tail(&map->link, &iotlb->list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_add_range);

/**
 * vring_iotlb_del_range - delete overlapped ranges from vhost IOTLB
 * @iotlb: the IOTLB
 * @start: start of the IOVA range
 * @last: last of IOVA range
 */
व्योम vhost_iotlb_del_range(काष्ठा vhost_iotlb *iotlb, u64 start, u64 last)
अणु
	काष्ठा vhost_iotlb_map *map;

	जबतक ((map = vhost_iotlb_itree_iter_first(&iotlb->root,
						   start, last)))
		vhost_iotlb_map_मुक्त(iotlb, map);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_del_range);

/**
 * vhost_iotlb_alloc - add a new vhost IOTLB
 * @limit: maximum number of IOTLB entries
 * @flags: VHOST_IOTLB_FLAG_XXX
 *
 * Returns an error is memory allocation fails
 */
काष्ठा vhost_iotlb *vhost_iotlb_alloc(अचिन्हित पूर्णांक limit, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा vhost_iotlb *iotlb = kzalloc(माप(*iotlb), GFP_KERNEL);

	अगर (!iotlb)
		वापस शून्य;

	iotlb->root = RB_ROOT_CACHED;
	iotlb->limit = limit;
	iotlb->nmaps = 0;
	iotlb->flags = flags;
	INIT_LIST_HEAD(&iotlb->list);

	वापस iotlb;
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_alloc);

/**
 * vhost_iotlb_reset - reset vhost IOTLB (मुक्त all IOTLB entries)
 * @iotlb: the IOTLB to be reset
 */
व्योम vhost_iotlb_reset(काष्ठा vhost_iotlb *iotlb)
अणु
	vhost_iotlb_del_range(iotlb, 0ULL, 0ULL - 1);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_reset);

/**
 * vhost_iotlb_मुक्त - reset and मुक्त vhost IOTLB
 * @iotlb: the IOTLB to be मुक्तd
 */
व्योम vhost_iotlb_मुक्त(काष्ठा vhost_iotlb *iotlb)
अणु
	अगर (iotlb) अणु
		vhost_iotlb_reset(iotlb);
		kमुक्त(iotlb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_मुक्त);

/**
 * vhost_iotlb_itree_first - वापस the first overlapped range
 * @iotlb: the IOTLB
 * @start: start of IOVA range
 * @last: last byte in IOVA range
 */
काष्ठा vhost_iotlb_map *
vhost_iotlb_itree_first(काष्ठा vhost_iotlb *iotlb, u64 start, u64 last)
अणु
	वापस vhost_iotlb_itree_iter_first(&iotlb->root, start, last);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_itree_first);

/**
 * vhost_iotlb_itree_next - वापस the next overlapped range
 * @map: the starting map node
 * @start: start of IOVA range
 * @last: last byte IOVA range
 */
काष्ठा vhost_iotlb_map *
vhost_iotlb_itree_next(काष्ठा vhost_iotlb_map *map, u64 start, u64 last)
अणु
	वापस vhost_iotlb_itree_iter_next(map, start, last);
पूर्ण
EXPORT_SYMBOL_GPL(vhost_iotlb_itree_next);

MODULE_VERSION(MOD_VERSION);
MODULE_DESCRIPTION(MOD_DESC);
MODULE_AUTHOR(MOD_AUTHOR);
MODULE_LICENSE(MOD_LICENSE);
