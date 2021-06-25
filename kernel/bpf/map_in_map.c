<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */
#समावेश <linux/slab.h>
#समावेश <linux/bpf.h>

#समावेश "map_in_map.h"

काष्ठा bpf_map *bpf_map_meta_alloc(पूर्णांक inner_map_ufd)
अणु
	काष्ठा bpf_map *inner_map, *inner_map_meta;
	u32 inner_map_meta_size;
	काष्ठा fd f;

	f = fdget(inner_map_ufd);
	inner_map = __bpf_map_get(f);
	अगर (IS_ERR(inner_map))
		वापस inner_map;

	/* Does not support >1 level map-in-map */
	अगर (inner_map->inner_map_meta) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!inner_map->ops->map_meta_equal) अणु
		fdput(f);
		वापस ERR_PTR(-ENOTSUPP);
	पूर्ण

	अगर (map_value_has_spin_lock(inner_map)) अणु
		fdput(f);
		वापस ERR_PTR(-ENOTSUPP);
	पूर्ण

	inner_map_meta_size = माप(*inner_map_meta);
	/* In some हालs verअगरier needs to access beyond just base map. */
	अगर (inner_map->ops == &array_map_ops)
		inner_map_meta_size = माप(काष्ठा bpf_array);

	inner_map_meta = kzalloc(inner_map_meta_size, GFP_USER);
	अगर (!inner_map_meta) अणु
		fdput(f);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	inner_map_meta->map_type = inner_map->map_type;
	inner_map_meta->key_size = inner_map->key_size;
	inner_map_meta->value_size = inner_map->value_size;
	inner_map_meta->map_flags = inner_map->map_flags;
	inner_map_meta->max_entries = inner_map->max_entries;
	inner_map_meta->spin_lock_off = inner_map->spin_lock_off;

	/* Misc members not needed in bpf_map_meta_equal() check. */
	inner_map_meta->ops = inner_map->ops;
	अगर (inner_map->ops == &array_map_ops) अणु
		inner_map_meta->bypass_spec_v1 = inner_map->bypass_spec_v1;
		container_of(inner_map_meta, काष्ठा bpf_array, map)->index_mask =
		     container_of(inner_map, काष्ठा bpf_array, map)->index_mask;
	पूर्ण

	fdput(f);
	वापस inner_map_meta;
पूर्ण

व्योम bpf_map_meta_मुक्त(काष्ठा bpf_map *map_meta)
अणु
	kमुक्त(map_meta);
पूर्ण

bool bpf_map_meta_equal(स्थिर काष्ठा bpf_map *meta0,
			स्थिर काष्ठा bpf_map *meta1)
अणु
	/* No need to compare ops because it is covered by map_type */
	वापस meta0->map_type == meta1->map_type &&
		meta0->key_size == meta1->key_size &&
		meta0->value_size == meta1->value_size &&
		meta0->map_flags == meta1->map_flags;
पूर्ण

व्योम *bpf_map_fd_get_ptr(काष्ठा bpf_map *map,
			 काष्ठा file *map_file /* not used */,
			 पूर्णांक ufd)
अणु
	काष्ठा bpf_map *inner_map, *inner_map_meta;
	काष्ठा fd f;

	f = fdget(ufd);
	inner_map = __bpf_map_get(f);
	अगर (IS_ERR(inner_map))
		वापस inner_map;

	inner_map_meta = map->inner_map_meta;
	अगर (inner_map_meta->ops->map_meta_equal(inner_map_meta, inner_map))
		bpf_map_inc(inner_map);
	अन्यथा
		inner_map = ERR_PTR(-EINVAL);

	fdput(f);
	वापस inner_map;
पूर्ण

व्योम bpf_map_fd_put_ptr(व्योम *ptr)
अणु
	/* ptr->ops->map_मुक्त() has to go through one
	 * rcu grace period by itself.
	 */
	bpf_map_put(ptr);
पूर्ण

u32 bpf_map_fd_sys_lookup_elem(व्योम *ptr)
अणु
	वापस ((काष्ठा bpf_map *)ptr)->id;
पूर्ण
