<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * queue_stack_maps.c: BPF queue and stack maps
 *
 * Copyright (c) 2018 Politecnico di Torino
 */
#समावेश <linux/bpf.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/capability.h>
#समावेश "percpu_freelist.h"

#घोषणा QUEUE_STACK_CREATE_FLAG_MASK \
	(BPF_F_NUMA_NODE | BPF_F_ACCESS_MASK)

काष्ठा bpf_queue_stack अणु
	काष्ठा bpf_map map;
	raw_spinlock_t lock;
	u32 head, tail;
	u32 size; /* max_entries + 1 */

	अक्षर elements[] __aligned(8);
पूर्ण;

अटल काष्ठा bpf_queue_stack *bpf_queue_stack(काष्ठा bpf_map *map)
अणु
	वापस container_of(map, काष्ठा bpf_queue_stack, map);
पूर्ण

अटल bool queue_stack_map_is_empty(काष्ठा bpf_queue_stack *qs)
अणु
	वापस qs->head == qs->tail;
पूर्ण

अटल bool queue_stack_map_is_full(काष्ठा bpf_queue_stack *qs)
अणु
	u32 head = qs->head + 1;

	अगर (unlikely(head >= qs->size))
		head = 0;

	वापस head == qs->tail;
पूर्ण

/* Called from syscall */
अटल पूर्णांक queue_stack_map_alloc_check(जोड़ bpf_attr *attr)
अणु
	अगर (!bpf_capable())
		वापस -EPERM;

	/* check sanity of attributes */
	अगर (attr->max_entries == 0 || attr->key_size != 0 ||
	    attr->value_size == 0 ||
	    attr->map_flags & ~QUEUE_STACK_CREATE_FLAG_MASK ||
	    !bpf_map_flags_access_ok(attr->map_flags))
		वापस -EINVAL;

	अगर (attr->value_size > KMALLOC_MAX_SIZE)
		/* अगर value_size is bigger, the user space won't be able to
		 * access the elements.
		 */
		वापस -E2BIG;

	वापस 0;
पूर्ण

अटल काष्ठा bpf_map *queue_stack_map_alloc(जोड़ bpf_attr *attr)
अणु
	पूर्णांक numa_node = bpf_map_attr_numa_node(attr);
	काष्ठा bpf_queue_stack *qs;
	u64 size, queue_size;

	size = (u64) attr->max_entries + 1;
	queue_size = माप(*qs) + size * attr->value_size;

	qs = bpf_map_area_alloc(queue_size, numa_node);
	अगर (!qs)
		वापस ERR_PTR(-ENOMEM);

	स_रखो(qs, 0, माप(*qs));

	bpf_map_init_from_attr(&qs->map, attr);

	qs->size = size;

	raw_spin_lock_init(&qs->lock);

	वापस &qs->map;
पूर्ण

/* Called when map->refcnt goes to zero, either from workqueue or from syscall */
अटल व्योम queue_stack_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_queue_stack *qs = bpf_queue_stack(map);

	bpf_map_area_मुक्त(qs);
पूर्ण

अटल पूर्णांक __queue_map_get(काष्ठा bpf_map *map, व्योम *value, bool delete)
अणु
	काष्ठा bpf_queue_stack *qs = bpf_queue_stack(map);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	व्योम *ptr;

	raw_spin_lock_irqsave(&qs->lock, flags);

	अगर (queue_stack_map_is_empty(qs)) अणु
		स_रखो(value, 0, qs->map.value_size);
		err = -ENOENT;
		जाओ out;
	पूर्ण

	ptr = &qs->elements[qs->tail * qs->map.value_size];
	स_नकल(value, ptr, qs->map.value_size);

	अगर (delete) अणु
		अगर (unlikely(++qs->tail >= qs->size))
			qs->tail = 0;
	पूर्ण

out:
	raw_spin_unlock_irqrestore(&qs->lock, flags);
	वापस err;
पूर्ण


अटल पूर्णांक __stack_map_get(काष्ठा bpf_map *map, व्योम *value, bool delete)
अणु
	काष्ठा bpf_queue_stack *qs = bpf_queue_stack(map);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	व्योम *ptr;
	u32 index;

	raw_spin_lock_irqsave(&qs->lock, flags);

	अगर (queue_stack_map_is_empty(qs)) अणु
		स_रखो(value, 0, qs->map.value_size);
		err = -ENOENT;
		जाओ out;
	पूर्ण

	index = qs->head - 1;
	अगर (unlikely(index >= qs->size))
		index = qs->size - 1;

	ptr = &qs->elements[index * qs->map.value_size];
	स_नकल(value, ptr, qs->map.value_size);

	अगर (delete)
		qs->head = index;

out:
	raw_spin_unlock_irqrestore(&qs->lock, flags);
	वापस err;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक queue_map_peek_elem(काष्ठा bpf_map *map, व्योम *value)
अणु
	वापस __queue_map_get(map, value, false);
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक stack_map_peek_elem(काष्ठा bpf_map *map, व्योम *value)
अणु
	वापस __stack_map_get(map, value, false);
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक queue_map_pop_elem(काष्ठा bpf_map *map, व्योम *value)
अणु
	वापस __queue_map_get(map, value, true);
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक stack_map_pop_elem(काष्ठा bpf_map *map, व्योम *value)
अणु
	वापस __stack_map_get(map, value, true);
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक queue_stack_map_push_elem(काष्ठा bpf_map *map, व्योम *value,
				     u64 flags)
अणु
	काष्ठा bpf_queue_stack *qs = bpf_queue_stack(map);
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक err = 0;
	व्योम *dst;

	/* BPF_EXIST is used to क्रमce making room क्रम a new element in हाल the
	 * map is full
	 */
	bool replace = (flags & BPF_EXIST);

	/* Check supported flags क्रम queue and stack maps */
	अगर (flags & BPF_NOEXIST || flags > BPF_EXIST)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&qs->lock, irq_flags);

	अगर (queue_stack_map_is_full(qs)) अणु
		अगर (!replace) अणु
			err = -E2BIG;
			जाओ out;
		पूर्ण
		/* advance tail poपूर्णांकer to overग_लिखो oldest element */
		अगर (unlikely(++qs->tail >= qs->size))
			qs->tail = 0;
	पूर्ण

	dst = &qs->elements[qs->head * qs->map.value_size];
	स_नकल(dst, value, qs->map.value_size);

	अगर (unlikely(++qs->head >= qs->size))
		qs->head = 0;

out:
	raw_spin_unlock_irqrestore(&qs->lock, irq_flags);
	वापस err;
पूर्ण

/* Called from syscall or from eBPF program */
अटल व्योम *queue_stack_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस शून्य;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक queue_stack_map_update_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value, u64 flags)
अणु
	वापस -EINVAL;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक queue_stack_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस -EINVAL;
पूर्ण

/* Called from syscall */
अटल पूर्णांक queue_stack_map_get_next_key(काष्ठा bpf_map *map, व्योम *key,
					व्योम *next_key)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक queue_map_btf_id;
स्थिर काष्ठा bpf_map_ops queue_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = queue_stack_map_alloc_check,
	.map_alloc = queue_stack_map_alloc,
	.map_मुक्त = queue_stack_map_मुक्त,
	.map_lookup_elem = queue_stack_map_lookup_elem,
	.map_update_elem = queue_stack_map_update_elem,
	.map_delete_elem = queue_stack_map_delete_elem,
	.map_push_elem = queue_stack_map_push_elem,
	.map_pop_elem = queue_map_pop_elem,
	.map_peek_elem = queue_map_peek_elem,
	.map_get_next_key = queue_stack_map_get_next_key,
	.map_btf_name = "bpf_queue_stack",
	.map_btf_id = &queue_map_btf_id,
पूर्ण;

अटल पूर्णांक stack_map_btf_id;
स्थिर काष्ठा bpf_map_ops stack_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = queue_stack_map_alloc_check,
	.map_alloc = queue_stack_map_alloc,
	.map_मुक्त = queue_stack_map_मुक्त,
	.map_lookup_elem = queue_stack_map_lookup_elem,
	.map_update_elem = queue_stack_map_update_elem,
	.map_delete_elem = queue_stack_map_delete_elem,
	.map_push_elem = queue_stack_map_push_elem,
	.map_pop_elem = stack_map_pop_elem,
	.map_peek_elem = stack_map_peek_elem,
	.map_get_next_key = queue_stack_map_get_next_key,
	.map_btf_name = "bpf_queue_stack",
	.map_btf_id = &stack_map_btf_id,
पूर्ण;
