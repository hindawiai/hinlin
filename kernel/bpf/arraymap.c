<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2016,2017 Facebook
 */
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/filter.h>
#समावेश <linux/perf_event.h>
#समावेश <uapi/linux/btf.h>
#समावेश <linux/rcupdate_trace.h>

#समावेश "map_in_map.h"

#घोषणा ARRAY_CREATE_FLAG_MASK \
	(BPF_F_NUMA_NODE | BPF_F_MMAPABLE | BPF_F_ACCESS_MASK | \
	 BPF_F_PRESERVE_ELEMS | BPF_F_INNER_MAP)

अटल व्योम bpf_array_मुक्त_percpu(काष्ठा bpf_array *array)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < array->map.max_entries; i++) अणु
		मुक्त_percpu(array->pptrs[i]);
		cond_resched();
	पूर्ण
पूर्ण

अटल पूर्णांक bpf_array_alloc_percpu(काष्ठा bpf_array *array)
अणु
	व्योम __percpu *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < array->map.max_entries; i++) अणु
		ptr = bpf_map_alloc_percpu(&array->map, array->elem_size, 8,
					   GFP_USER | __GFP_NOWARN);
		अगर (!ptr) अणु
			bpf_array_मुक्त_percpu(array);
			वापस -ENOMEM;
		पूर्ण
		array->pptrs[i] = ptr;
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

/* Called from syscall */
पूर्णांक array_map_alloc_check(जोड़ bpf_attr *attr)
अणु
	bool percpu = attr->map_type == BPF_MAP_TYPE_PERCPU_ARRAY;
	पूर्णांक numa_node = bpf_map_attr_numa_node(attr);

	/* check sanity of attributes */
	अगर (attr->max_entries == 0 || attr->key_size != 4 ||
	    attr->value_size == 0 ||
	    attr->map_flags & ~ARRAY_CREATE_FLAG_MASK ||
	    !bpf_map_flags_access_ok(attr->map_flags) ||
	    (percpu && numa_node != NUMA_NO_NODE))
		वापस -EINVAL;

	अगर (attr->map_type != BPF_MAP_TYPE_ARRAY &&
	    attr->map_flags & (BPF_F_MMAPABLE | BPF_F_INNER_MAP))
		वापस -EINVAL;

	अगर (attr->map_type != BPF_MAP_TYPE_PERF_EVENT_ARRAY &&
	    attr->map_flags & BPF_F_PRESERVE_ELEMS)
		वापस -EINVAL;

	अगर (attr->value_size > KMALLOC_MAX_SIZE)
		/* अगर value_size is bigger, the user space won't be able to
		 * access the elements.
		 */
		वापस -E2BIG;

	वापस 0;
पूर्ण

अटल काष्ठा bpf_map *array_map_alloc(जोड़ bpf_attr *attr)
अणु
	bool percpu = attr->map_type == BPF_MAP_TYPE_PERCPU_ARRAY;
	पूर्णांक numa_node = bpf_map_attr_numa_node(attr);
	u32 elem_size, index_mask, max_entries;
	bool bypass_spec_v1 = bpf_bypass_spec_v1();
	u64 array_size, mask64;
	काष्ठा bpf_array *array;

	elem_size = round_up(attr->value_size, 8);

	max_entries = attr->max_entries;

	/* On 32 bit archs roundup_घात_of_two() with max_entries that has
	 * upper most bit set in u32 space is undefined behavior due to
	 * resulting 1U << 32, so करो it manually here in u64 space.
	 */
	mask64 = fls_दीर्घ(max_entries - 1);
	mask64 = 1ULL << mask64;
	mask64 -= 1;

	index_mask = mask64;
	अगर (!bypass_spec_v1) अणु
		/* round up array size to nearest घातer of 2,
		 * since cpu will speculate within index_mask limits
		 */
		max_entries = index_mask + 1;
		/* Check क्रम overflows. */
		अगर (max_entries < attr->max_entries)
			वापस ERR_PTR(-E2BIG);
	पूर्ण

	array_size = माप(*array);
	अगर (percpu) अणु
		array_size += (u64) max_entries * माप(व्योम *);
	पूर्ण अन्यथा अणु
		/* rely on vदो_स्मृति() to वापस page-aligned memory and
		 * ensure array->value is exactly page-aligned
		 */
		अगर (attr->map_flags & BPF_F_MMAPABLE) अणु
			array_size = PAGE_ALIGN(array_size);
			array_size += PAGE_ALIGN((u64) max_entries * elem_size);
		पूर्ण अन्यथा अणु
			array_size += (u64) max_entries * elem_size;
		पूर्ण
	पूर्ण

	/* allocate all map elements and zero-initialize them */
	अगर (attr->map_flags & BPF_F_MMAPABLE) अणु
		व्योम *data;

		/* kदो_स्मृति'ed memory can't be mmap'ed, use explicit vदो_स्मृति */
		data = bpf_map_area_mmapable_alloc(array_size, numa_node);
		अगर (!data)
			वापस ERR_PTR(-ENOMEM);
		array = data + PAGE_ALIGN(माप(काष्ठा bpf_array))
			- दुरत्व(काष्ठा bpf_array, value);
	पूर्ण अन्यथा अणु
		array = bpf_map_area_alloc(array_size, numa_node);
	पूर्ण
	अगर (!array)
		वापस ERR_PTR(-ENOMEM);
	array->index_mask = index_mask;
	array->map.bypass_spec_v1 = bypass_spec_v1;

	/* copy mandatory map attributes */
	bpf_map_init_from_attr(&array->map, attr);
	array->elem_size = elem_size;

	अगर (percpu && bpf_array_alloc_percpu(array)) अणु
		bpf_map_area_मुक्त(array);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस &array->map;
पूर्ण

/* Called from syscall or from eBPF program */
अटल व्योम *array_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 index = *(u32 *)key;

	अगर (unlikely(index >= array->map.max_entries))
		वापस शून्य;

	वापस array->value + array->elem_size * (index & array->index_mask);
पूर्ण

अटल पूर्णांक array_map_direct_value_addr(स्थिर काष्ठा bpf_map *map, u64 *imm,
				       u32 off)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);

	अगर (map->max_entries != 1)
		वापस -ENOTSUPP;
	अगर (off >= map->value_size)
		वापस -EINVAL;

	*imm = (अचिन्हित दीर्घ)array->value;
	वापस 0;
पूर्ण

अटल पूर्णांक array_map_direct_value_meta(स्थिर काष्ठा bpf_map *map, u64 imm,
				       u32 *off)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u64 base = (अचिन्हित दीर्घ)array->value;
	u64 range = array->elem_size;

	अगर (map->max_entries != 1)
		वापस -ENOTSUPP;
	अगर (imm < base || imm >= base + range)
		वापस -ENOENT;

	*off = imm - base;
	वापस 0;
पूर्ण

/* emit BPF inकाष्ठाions equivalent to C code of array_map_lookup_elem() */
अटल पूर्णांक array_map_gen_lookup(काष्ठा bpf_map *map, काष्ठा bpf_insn *insn_buf)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	काष्ठा bpf_insn *insn = insn_buf;
	u32 elem_size = round_up(map->value_size, 8);
	स्थिर पूर्णांक ret = BPF_REG_0;
	स्थिर पूर्णांक map_ptr = BPF_REG_1;
	स्थिर पूर्णांक index = BPF_REG_2;

	अगर (map->map_flags & BPF_F_INNER_MAP)
		वापस -EOPNOTSUPP;

	*insn++ = BPF_ALU64_IMM(BPF_ADD, map_ptr, दुरत्व(काष्ठा bpf_array, value));
	*insn++ = BPF_LDX_MEM(BPF_W, ret, index, 0);
	अगर (!map->bypass_spec_v1) अणु
		*insn++ = BPF_JMP_IMM(BPF_JGE, ret, map->max_entries, 4);
		*insn++ = BPF_ALU32_IMM(BPF_AND, ret, array->index_mask);
	पूर्ण अन्यथा अणु
		*insn++ = BPF_JMP_IMM(BPF_JGE, ret, map->max_entries, 3);
	पूर्ण

	अगर (is_घातer_of_2(elem_size)) अणु
		*insn++ = BPF_ALU64_IMM(BPF_LSH, ret, ilog2(elem_size));
	पूर्ण अन्यथा अणु
		*insn++ = BPF_ALU64_IMM(BPF_MUL, ret, elem_size);
	पूर्ण
	*insn++ = BPF_ALU64_REG(BPF_ADD, ret, map_ptr);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
	*insn++ = BPF_MOV64_IMM(ret, 0);
	वापस insn - insn_buf;
पूर्ण

/* Called from eBPF program */
अटल व्योम *percpu_array_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 index = *(u32 *)key;

	अगर (unlikely(index >= array->map.max_entries))
		वापस शून्य;

	वापस this_cpu_ptr(array->pptrs[index & array->index_mask]);
पूर्ण

पूर्णांक bpf_percpu_array_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 index = *(u32 *)key;
	व्योम __percpu *pptr;
	पूर्णांक cpu, off = 0;
	u32 size;

	अगर (unlikely(index >= array->map.max_entries))
		वापस -ENOENT;

	/* per_cpu areas are zero-filled and bpf programs can only
	 * access 'value_size' of them, so copying rounded areas
	 * will not leak any kernel data
	 */
	size = round_up(map->value_size, 8);
	rcu_पढ़ो_lock();
	pptr = array->pptrs[index & array->index_mask];
	क्रम_each_possible_cpu(cpu) अणु
		bpf_दीर्घ_स_नकल(value + off, per_cpu_ptr(pptr, cpu), size);
		off += size;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/* Called from syscall */
अटल पूर्णांक array_map_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = (u32 *)next_key;

	अगर (index >= array->map.max_entries) अणु
		*next = 0;
		वापस 0;
	पूर्ण

	अगर (index == array->map.max_entries - 1)
		वापस -ENOENT;

	*next = index + 1;
	वापस 0;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक array_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
				 u64 map_flags)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 index = *(u32 *)key;
	अक्षर *val;

	अगर (unlikely((map_flags & ~BPF_F_LOCK) > BPF_EXIST))
		/* unknown flags */
		वापस -EINVAL;

	अगर (unlikely(index >= array->map.max_entries))
		/* all elements were pre-allocated, cannot insert a new one */
		वापस -E2BIG;

	अगर (unlikely(map_flags & BPF_NOEXIST))
		/* all elements alपढ़ोy exist */
		वापस -EEXIST;

	अगर (unlikely((map_flags & BPF_F_LOCK) &&
		     !map_value_has_spin_lock(map)))
		वापस -EINVAL;

	अगर (array->map.map_type == BPF_MAP_TYPE_PERCPU_ARRAY) अणु
		स_नकल(this_cpu_ptr(array->pptrs[index & array->index_mask]),
		       value, map->value_size);
	पूर्ण अन्यथा अणु
		val = array->value +
			array->elem_size * (index & array->index_mask);
		अगर (map_flags & BPF_F_LOCK)
			copy_map_value_locked(map, val, value, false);
		अन्यथा
			copy_map_value(map, val, value);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bpf_percpu_array_update(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			    u64 map_flags)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 index = *(u32 *)key;
	व्योम __percpu *pptr;
	पूर्णांक cpu, off = 0;
	u32 size;

	अगर (unlikely(map_flags > BPF_EXIST))
		/* unknown flags */
		वापस -EINVAL;

	अगर (unlikely(index >= array->map.max_entries))
		/* all elements were pre-allocated, cannot insert a new one */
		वापस -E2BIG;

	अगर (unlikely(map_flags == BPF_NOEXIST))
		/* all elements alपढ़ोy exist */
		वापस -EEXIST;

	/* the user space will provide round_up(value_size, 8) bytes that
	 * will be copied पूर्णांकo per-cpu area. bpf programs can only access
	 * value_size of it. During lookup the same extra bytes will be
	 * वापसed or zeros which were zero-filled by percpu_alloc,
	 * so no kernel data leaks possible
	 */
	size = round_up(map->value_size, 8);
	rcu_पढ़ो_lock();
	pptr = array->pptrs[index & array->index_mask];
	क्रम_each_possible_cpu(cpu) अणु
		bpf_दीर्घ_स_नकल(per_cpu_ptr(pptr, cpu), value + off, size);
		off += size;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक array_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम *array_map_vदो_स्मृति_addr(काष्ठा bpf_array *array)
अणु
	वापस (व्योम *)round_करोwn((अचिन्हित दीर्घ)array, PAGE_SIZE);
पूर्ण

/* Called when map->refcnt goes to zero, either from workqueue or from syscall */
अटल व्योम array_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);

	अगर (array->map.map_type == BPF_MAP_TYPE_PERCPU_ARRAY)
		bpf_array_मुक्त_percpu(array);

	अगर (array->map.map_flags & BPF_F_MMAPABLE)
		bpf_map_area_मुक्त(array_map_vदो_स्मृति_addr(array));
	अन्यथा
		bpf_map_area_मुक्त(array);
पूर्ण

अटल व्योम array_map_seq_show_elem(काष्ठा bpf_map *map, व्योम *key,
				    काष्ठा seq_file *m)
अणु
	व्योम *value;

	rcu_पढ़ो_lock();

	value = array_map_lookup_elem(map, key);
	अगर (!value) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (map->btf_key_type_id)
		seq_म_लिखो(m, "%u: ", *(u32 *)key);
	btf_type_seq_show(map->btf, map->btf_value_type_id, value, m);
	seq_माला_दो(m, "\n");

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम percpu_array_map_seq_show_elem(काष्ठा bpf_map *map, व्योम *key,
					   काष्ठा seq_file *m)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 index = *(u32 *)key;
	व्योम __percpu *pptr;
	पूर्णांक cpu;

	rcu_पढ़ो_lock();

	seq_म_लिखो(m, "%u: {\n", *(u32 *)key);
	pptr = array->pptrs[index & array->index_mask];
	क्रम_each_possible_cpu(cpu) अणु
		seq_म_लिखो(m, "\tcpu%d: ", cpu);
		btf_type_seq_show(map->btf, map->btf_value_type_id,
				  per_cpu_ptr(pptr, cpu), m);
		seq_माला_दो(m, "\n");
	पूर्ण
	seq_माला_दो(m, "}\n");

	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक array_map_check_btf(स्थिर काष्ठा bpf_map *map,
			       स्थिर काष्ठा btf *btf,
			       स्थिर काष्ठा btf_type *key_type,
			       स्थिर काष्ठा btf_type *value_type)
अणु
	u32 पूर्णांक_data;

	/* One exception क्रम keyless BTF: .bss/.data/.rodata map */
	अगर (btf_type_is_व्योम(key_type)) अणु
		अगर (map->map_type != BPF_MAP_TYPE_ARRAY ||
		    map->max_entries != 1)
			वापस -EINVAL;

		अगर (BTF_INFO_KIND(value_type->info) != BTF_KIND_DATASEC)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	अगर (BTF_INFO_KIND(key_type->info) != BTF_KIND_INT)
		वापस -EINVAL;

	पूर्णांक_data = *(u32 *)(key_type + 1);
	/* bpf array can only take a u32 key. This check makes sure
	 * that the btf matches the attr used during map_create.
	 */
	अगर (BTF_INT_BITS(पूर्णांक_data) != 32 || BTF_INT_OFFSET(पूर्णांक_data))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक array_map_mmap(काष्ठा bpf_map *map, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	pgoff_t pgoff = PAGE_ALIGN(माप(*array)) >> PAGE_SHIFT;

	अगर (!(map->map_flags & BPF_F_MMAPABLE))
		वापस -EINVAL;

	अगर (vma->vm_pgoff * PAGE_SIZE + (vma->vm_end - vma->vm_start) >
	    PAGE_ALIGN((u64)array->map.max_entries * array->elem_size))
		वापस -EINVAL;

	वापस remap_vदो_स्मृति_range(vma, array_map_vदो_स्मृति_addr(array),
				   vma->vm_pgoff + pgoff);
पूर्ण

अटल bool array_map_meta_equal(स्थिर काष्ठा bpf_map *meta0,
				 स्थिर काष्ठा bpf_map *meta1)
अणु
	अगर (!bpf_map_meta_equal(meta0, meta1))
		वापस false;
	वापस meta0->map_flags & BPF_F_INNER_MAP ? true :
	       meta0->max_entries == meta1->max_entries;
पूर्ण

काष्ठा bpf_iter_seq_array_map_info अणु
	काष्ठा bpf_map *map;
	व्योम *percpu_value_buf;
	u32 index;
पूर्ण;

अटल व्योम *bpf_array_map_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_array_map_info *info = seq->निजी;
	काष्ठा bpf_map *map = info->map;
	काष्ठा bpf_array *array;
	u32 index;

	अगर (info->index >= map->max_entries)
		वापस शून्य;

	अगर (*pos == 0)
		++*pos;
	array = container_of(map, काष्ठा bpf_array, map);
	index = info->index & array->index_mask;
	अगर (info->percpu_value_buf)
	       वापस array->pptrs[index];
	वापस array->value + array->elem_size * index;
पूर्ण

अटल व्योम *bpf_array_map_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_array_map_info *info = seq->निजी;
	काष्ठा bpf_map *map = info->map;
	काष्ठा bpf_array *array;
	u32 index;

	++*pos;
	++info->index;
	अगर (info->index >= map->max_entries)
		वापस शून्य;

	array = container_of(map, काष्ठा bpf_array, map);
	index = info->index & array->index_mask;
	अगर (info->percpu_value_buf)
	       वापस array->pptrs[index];
	वापस array->value + array->elem_size * index;
पूर्ण

अटल पूर्णांक __bpf_array_map_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_seq_array_map_info *info = seq->निजी;
	काष्ठा bpf_iter__bpf_map_elem ctx = अणुपूर्ण;
	काष्ठा bpf_map *map = info->map;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;
	पूर्णांक off = 0, cpu = 0;
	व्योम __percpu **pptr;
	u32 size;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, v == शून्य);
	अगर (!prog)
		वापस 0;

	ctx.meta = &meta;
	ctx.map = info->map;
	अगर (v) अणु
		ctx.key = &info->index;

		अगर (!info->percpu_value_buf) अणु
			ctx.value = v;
		पूर्ण अन्यथा अणु
			pptr = v;
			size = round_up(map->value_size, 8);
			क्रम_each_possible_cpu(cpu) अणु
				bpf_दीर्घ_स_नकल(info->percpu_value_buf + off,
						per_cpu_ptr(pptr, cpu),
						size);
				off += size;
			पूर्ण
			ctx.value = info->percpu_value_buf;
		पूर्ण
	पूर्ण

	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक bpf_array_map_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __bpf_array_map_seq_show(seq, v);
पूर्ण

अटल व्योम bpf_array_map_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (!v)
		(व्योम)__bpf_array_map_seq_show(seq, शून्य);
पूर्ण

अटल पूर्णांक bpf_iter_init_array_map(व्योम *priv_data,
				   काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा bpf_iter_seq_array_map_info *seq_info = priv_data;
	काष्ठा bpf_map *map = aux->map;
	व्योम *value_buf;
	u32 buf_size;

	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_ARRAY) अणु
		buf_size = round_up(map->value_size, 8) * num_possible_cpus();
		value_buf = kदो_स्मृति(buf_size, GFP_USER | __GFP_NOWARN);
		अगर (!value_buf)
			वापस -ENOMEM;

		seq_info->percpu_value_buf = value_buf;
	पूर्ण

	seq_info->map = map;
	वापस 0;
पूर्ण

अटल व्योम bpf_iter_fini_array_map(व्योम *priv_data)
अणु
	काष्ठा bpf_iter_seq_array_map_info *seq_info = priv_data;

	kमुक्त(seq_info->percpu_value_buf);
पूर्ण

अटल स्थिर काष्ठा seq_operations bpf_array_map_seq_ops = अणु
	.start	= bpf_array_map_seq_start,
	.next	= bpf_array_map_seq_next,
	.stop	= bpf_array_map_seq_stop,
	.show	= bpf_array_map_seq_show,
पूर्ण;

अटल स्थिर काष्ठा bpf_iter_seq_info iter_seq_info = अणु
	.seq_ops		= &bpf_array_map_seq_ops,
	.init_seq_निजी	= bpf_iter_init_array_map,
	.fini_seq_निजी	= bpf_iter_fini_array_map,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_array_map_info),
पूर्ण;

अटल पूर्णांक bpf_क्रम_each_array_elem(काष्ठा bpf_map *map, व्योम *callback_fn,
				   व्योम *callback_ctx, u64 flags)
अणु
	u32 i, key, num_elems = 0;
	काष्ठा bpf_array *array;
	bool is_percpu;
	u64 ret = 0;
	व्योम *val;

	अगर (flags != 0)
		वापस -EINVAL;

	is_percpu = map->map_type == BPF_MAP_TYPE_PERCPU_ARRAY;
	array = container_of(map, काष्ठा bpf_array, map);
	अगर (is_percpu)
		migrate_disable();
	क्रम (i = 0; i < map->max_entries; i++) अणु
		अगर (is_percpu)
			val = this_cpu_ptr(array->pptrs[i]);
		अन्यथा
			val = array->value + array->elem_size * i;
		num_elems++;
		key = i;
		ret = BPF_CAST_CALL(callback_fn)((u64)(दीर्घ)map,
					(u64)(दीर्घ)&key, (u64)(दीर्घ)val,
					(u64)(दीर्घ)callback_ctx, 0);
		/* वापस value: 0 - जारी, 1 - stop and वापस */
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (is_percpu)
		migrate_enable();
	वापस num_elems;
पूर्ण

अटल पूर्णांक array_map_btf_id;
स्थिर काष्ठा bpf_map_ops array_map_ops = अणु
	.map_meta_equal = array_map_meta_equal,
	.map_alloc_check = array_map_alloc_check,
	.map_alloc = array_map_alloc,
	.map_मुक्त = array_map_मुक्त,
	.map_get_next_key = array_map_get_next_key,
	.map_lookup_elem = array_map_lookup_elem,
	.map_update_elem = array_map_update_elem,
	.map_delete_elem = array_map_delete_elem,
	.map_gen_lookup = array_map_gen_lookup,
	.map_direct_value_addr = array_map_direct_value_addr,
	.map_direct_value_meta = array_map_direct_value_meta,
	.map_mmap = array_map_mmap,
	.map_seq_show_elem = array_map_seq_show_elem,
	.map_check_btf = array_map_check_btf,
	.map_lookup_batch = generic_map_lookup_batch,
	.map_update_batch = generic_map_update_batch,
	.map_set_क्रम_each_callback_args = map_set_क्रम_each_callback_args,
	.map_क्रम_each_callback = bpf_क्रम_each_array_elem,
	.map_btf_name = "bpf_array",
	.map_btf_id = &array_map_btf_id,
	.iter_seq_info = &iter_seq_info,
पूर्ण;

अटल पूर्णांक percpu_array_map_btf_id;
स्थिर काष्ठा bpf_map_ops percpu_array_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = array_map_alloc_check,
	.map_alloc = array_map_alloc,
	.map_मुक्त = array_map_मुक्त,
	.map_get_next_key = array_map_get_next_key,
	.map_lookup_elem = percpu_array_map_lookup_elem,
	.map_update_elem = array_map_update_elem,
	.map_delete_elem = array_map_delete_elem,
	.map_seq_show_elem = percpu_array_map_seq_show_elem,
	.map_check_btf = array_map_check_btf,
	.map_lookup_batch = generic_map_lookup_batch,
	.map_update_batch = generic_map_update_batch,
	.map_set_क्रम_each_callback_args = map_set_क्रम_each_callback_args,
	.map_क्रम_each_callback = bpf_क्रम_each_array_elem,
	.map_btf_name = "bpf_array",
	.map_btf_id = &percpu_array_map_btf_id,
	.iter_seq_info = &iter_seq_info,
पूर्ण;

अटल पूर्णांक fd_array_map_alloc_check(जोड़ bpf_attr *attr)
अणु
	/* only file descriptors can be stored in this type of map */
	अगर (attr->value_size != माप(u32))
		वापस -EINVAL;
	/* Program पढ़ो-only/ग_लिखो-only not supported क्रम special maps yet. */
	अगर (attr->map_flags & (BPF_F_RDONLY_PROG | BPF_F_WRONLY_PROG))
		वापस -EINVAL;
	वापस array_map_alloc_check(attr);
पूर्ण

अटल व्योम fd_array_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	पूर्णांक i;

	/* make sure it's empty */
	क्रम (i = 0; i < array->map.max_entries; i++)
		BUG_ON(array->ptrs[i] != शून्य);

	bpf_map_area_मुक्त(array);
पूर्ण

अटल व्योम *fd_array_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

/* only called from syscall */
पूर्णांक bpf_fd_array_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key, u32 *value)
अणु
	व्योम **elem, *ptr;
	पूर्णांक ret =  0;

	अगर (!map->ops->map_fd_sys_lookup_elem)
		वापस -ENOTSUPP;

	rcu_पढ़ो_lock();
	elem = array_map_lookup_elem(map, key);
	अगर (elem && (ptr = READ_ONCE(*elem)))
		*value = map->ops->map_fd_sys_lookup_elem(ptr);
	अन्यथा
		ret = -ENOENT;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* only called from syscall */
पूर्णांक bpf_fd_array_map_update_elem(काष्ठा bpf_map *map, काष्ठा file *map_file,
				 व्योम *key, व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	व्योम *new_ptr, *old_ptr;
	u32 index = *(u32 *)key, ufd;

	अगर (map_flags != BPF_ANY)
		वापस -EINVAL;

	अगर (index >= array->map.max_entries)
		वापस -E2BIG;

	ufd = *(u32 *)value;
	new_ptr = map->ops->map_fd_get_ptr(map, map_file, ufd);
	अगर (IS_ERR(new_ptr))
		वापस PTR_ERR(new_ptr);

	अगर (map->ops->map_poke_run) अणु
		mutex_lock(&array->aux->poke_mutex);
		old_ptr = xchg(array->ptrs + index, new_ptr);
		map->ops->map_poke_run(map, index, old_ptr, new_ptr);
		mutex_unlock(&array->aux->poke_mutex);
	पूर्ण अन्यथा अणु
		old_ptr = xchg(array->ptrs + index, new_ptr);
	पूर्ण

	अगर (old_ptr)
		map->ops->map_fd_put_ptr(old_ptr);
	वापस 0;
पूर्ण

अटल पूर्णांक fd_array_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	व्योम *old_ptr;
	u32 index = *(u32 *)key;

	अगर (index >= array->map.max_entries)
		वापस -E2BIG;

	अगर (map->ops->map_poke_run) अणु
		mutex_lock(&array->aux->poke_mutex);
		old_ptr = xchg(array->ptrs + index, शून्य);
		map->ops->map_poke_run(map, index, old_ptr, शून्य);
		mutex_unlock(&array->aux->poke_mutex);
	पूर्ण अन्यथा अणु
		old_ptr = xchg(array->ptrs + index, शून्य);
	पूर्ण

	अगर (old_ptr) अणु
		map->ops->map_fd_put_ptr(old_ptr);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल व्योम *prog_fd_array_get_ptr(काष्ठा bpf_map *map,
				   काष्ठा file *map_file, पूर्णांक fd)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	काष्ठा bpf_prog *prog = bpf_prog_get(fd);

	अगर (IS_ERR(prog))
		वापस prog;

	अगर (!bpf_prog_array_compatible(array, prog)) अणु
		bpf_prog_put(prog);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस prog;
पूर्ण

अटल व्योम prog_fd_array_put_ptr(व्योम *ptr)
अणु
	bpf_prog_put(ptr);
पूर्ण

अटल u32 prog_fd_array_sys_lookup_elem(व्योम *ptr)
अणु
	वापस ((काष्ठा bpf_prog *)ptr)->aux->id;
पूर्ण

/* decrement refcnt of all bpf_progs that are stored in this map */
अटल व्योम bpf_fd_array_map_clear(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	पूर्णांक i;

	क्रम (i = 0; i < array->map.max_entries; i++)
		fd_array_map_delete_elem(map, &i);
पूर्ण

अटल व्योम prog_array_map_seq_show_elem(काष्ठा bpf_map *map, व्योम *key,
					 काष्ठा seq_file *m)
अणु
	व्योम **elem, *ptr;
	u32 prog_id;

	rcu_पढ़ो_lock();

	elem = array_map_lookup_elem(map, key);
	अगर (elem) अणु
		ptr = READ_ONCE(*elem);
		अगर (ptr) अणु
			seq_म_लिखो(m, "%u: ", *(u32 *)key);
			prog_id = prog_fd_array_sys_lookup_elem(ptr);
			btf_type_seq_show(map->btf, map->btf_value_type_id,
					  &prog_id, m);
			seq_माला_दो(m, "\n");
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

काष्ठा prog_poke_elem अणु
	काष्ठा list_head list;
	काष्ठा bpf_prog_aux *aux;
पूर्ण;

अटल पूर्णांक prog_array_map_poke_track(काष्ठा bpf_map *map,
				     काष्ठा bpf_prog_aux *prog_aux)
अणु
	काष्ठा prog_poke_elem *elem;
	काष्ठा bpf_array_aux *aux;
	पूर्णांक ret = 0;

	aux = container_of(map, काष्ठा bpf_array, map)->aux;
	mutex_lock(&aux->poke_mutex);
	list_क्रम_each_entry(elem, &aux->poke_progs, list) अणु
		अगर (elem->aux == prog_aux)
			जाओ out;
	पूर्ण

	elem = kदो_स्मृति(माप(*elem), GFP_KERNEL);
	अगर (!elem) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&elem->list);
	/* We must track the program's aux info at this poपूर्णांक in समय
	 * since the program poपूर्णांकer itself may not be stable yet, see
	 * also comment in prog_array_map_poke_run().
	 */
	elem->aux = prog_aux;

	list_add_tail(&elem->list, &aux->poke_progs);
out:
	mutex_unlock(&aux->poke_mutex);
	वापस ret;
पूर्ण

अटल व्योम prog_array_map_poke_untrack(काष्ठा bpf_map *map,
					काष्ठा bpf_prog_aux *prog_aux)
अणु
	काष्ठा prog_poke_elem *elem, *पंचांगp;
	काष्ठा bpf_array_aux *aux;

	aux = container_of(map, काष्ठा bpf_array, map)->aux;
	mutex_lock(&aux->poke_mutex);
	list_क्रम_each_entry_safe(elem, पंचांगp, &aux->poke_progs, list) अणु
		अगर (elem->aux == prog_aux) अणु
			list_del_init(&elem->list);
			kमुक्त(elem);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&aux->poke_mutex);
पूर्ण

अटल व्योम prog_array_map_poke_run(काष्ठा bpf_map *map, u32 key,
				    काष्ठा bpf_prog *old,
				    काष्ठा bpf_prog *new)
अणु
	u8 *old_addr, *new_addr, *old_bypass_addr;
	काष्ठा prog_poke_elem *elem;
	काष्ठा bpf_array_aux *aux;

	aux = container_of(map, काष्ठा bpf_array, map)->aux;
	WARN_ON_ONCE(!mutex_is_locked(&aux->poke_mutex));

	list_क्रम_each_entry(elem, &aux->poke_progs, list) अणु
		काष्ठा bpf_jit_poke_descriptor *poke;
		पूर्णांक i, ret;

		क्रम (i = 0; i < elem->aux->size_poke_tab; i++) अणु
			poke = &elem->aux->poke_tab[i];

			/* Few things to be aware of:
			 *
			 * 1) We can only ever access aux in this context, but
			 *    not aux->prog since it might not be stable yet and
			 *    there could be danger of use after मुक्त otherwise.
			 * 2) Initially when we start tracking aux, the program
			 *    is not JITed yet and also करोes not have a kallsyms
			 *    entry. We skip these as poke->tailcall_target_stable
			 *    is not active yet. The JIT will करो the final fixup
			 *    beक्रमe setting it stable. The various
			 *    poke->tailcall_target_stable are successively
			 *    activated, so tail call updates can arrive from here
			 *    जबतक JIT is still finishing its final fixup क्रम
			 *    non-activated poke entries.
			 * 3) On program tearकरोwn, the program's kallsym entry माला_लो
			 *    हटाओd out of RCU callback, but we can only untrack
			 *    from sleepable context, thereक्रमe bpf_arch_text_poke()
			 *    might not see that this is in BPF text section and
			 *    bails out with -EINVAL. As these are unreachable since
			 *    RCU grace period alपढ़ोy passed, we simply skip them.
			 * 4) Also programs reaching refcount of zero जबतक patching
			 *    is in progress is okay since we're रक्षित under
			 *    poke_mutex and untrack the programs beक्रमe the JIT
			 *    buffer is मुक्तd. When we're still in the middle of
			 *    patching and suddenly kallsyms entry of the program
			 *    माला_लो evicted, we just skip the rest which is fine due
			 *    to poपूर्णांक 3).
			 * 5) Any other error happening below from bpf_arch_text_poke()
			 *    is a unexpected bug.
			 */
			अगर (!READ_ONCE(poke->tailcall_target_stable))
				जारी;
			अगर (poke->reason != BPF_POKE_REASON_TAIL_CALL)
				जारी;
			अगर (poke->tail_call.map != map ||
			    poke->tail_call.key != key)
				जारी;

			old_bypass_addr = old ? शून्य : poke->bypass_addr;
			old_addr = old ? (u8 *)old->bpf_func + poke->adj_off : शून्य;
			new_addr = new ? (u8 *)new->bpf_func + poke->adj_off : शून्य;

			अगर (new) अणु
				ret = bpf_arch_text_poke(poke->tailcall_target,
							 BPF_MOD_JUMP,
							 old_addr, new_addr);
				BUG_ON(ret < 0 && ret != -EINVAL);
				अगर (!old) अणु
					ret = bpf_arch_text_poke(poke->tailcall_bypass,
								 BPF_MOD_JUMP,
								 poke->bypass_addr,
								 शून्य);
					BUG_ON(ret < 0 && ret != -EINVAL);
				पूर्ण
			पूर्ण अन्यथा अणु
				ret = bpf_arch_text_poke(poke->tailcall_bypass,
							 BPF_MOD_JUMP,
							 old_bypass_addr,
							 poke->bypass_addr);
				BUG_ON(ret < 0 && ret != -EINVAL);
				/* let other CPUs finish the execution of program
				 * so that it will not possible to expose them
				 * to invalid nop, stack unwind, nop state
				 */
				अगर (!ret)
					synchronize_rcu();
				ret = bpf_arch_text_poke(poke->tailcall_target,
							 BPF_MOD_JUMP,
							 old_addr, शून्य);
				BUG_ON(ret < 0 && ret != -EINVAL);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prog_array_map_clear_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bpf_map *map = container_of(work, काष्ठा bpf_array_aux,
					   work)->map;
	bpf_fd_array_map_clear(map);
	bpf_map_put(map);
पूर्ण

अटल व्योम prog_array_map_clear(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_array_aux *aux = container_of(map, काष्ठा bpf_array,
						 map)->aux;
	bpf_map_inc(map);
	schedule_work(&aux->work);
पूर्ण

अटल काष्ठा bpf_map *prog_array_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_array_aux *aux;
	काष्ठा bpf_map *map;

	aux = kzalloc(माप(*aux), GFP_KERNEL_ACCOUNT);
	अगर (!aux)
		वापस ERR_PTR(-ENOMEM);

	INIT_WORK(&aux->work, prog_array_map_clear_deferred);
	INIT_LIST_HEAD(&aux->poke_progs);
	mutex_init(&aux->poke_mutex);

	map = array_map_alloc(attr);
	अगर (IS_ERR(map)) अणु
		kमुक्त(aux);
		वापस map;
	पूर्ण

	container_of(map, काष्ठा bpf_array, map)->aux = aux;
	aux->map = map;

	वापस map;
पूर्ण

अटल व्योम prog_array_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा prog_poke_elem *elem, *पंचांगp;
	काष्ठा bpf_array_aux *aux;

	aux = container_of(map, काष्ठा bpf_array, map)->aux;
	list_क्रम_each_entry_safe(elem, पंचांगp, &aux->poke_progs, list) अणु
		list_del_init(&elem->list);
		kमुक्त(elem);
	पूर्ण
	kमुक्त(aux);
	fd_array_map_मुक्त(map);
पूर्ण

/* prog_array->aux->अणुtype,jitedपूर्ण is a runसमय binding.
 * Doing अटल check alone in the verअगरier is not enough.
 * Thus, prog_array_map cannot be used as an inner_map
 * and map_meta_equal is not implemented.
 */
अटल पूर्णांक prog_array_map_btf_id;
स्थिर काष्ठा bpf_map_ops prog_array_map_ops = अणु
	.map_alloc_check = fd_array_map_alloc_check,
	.map_alloc = prog_array_map_alloc,
	.map_मुक्त = prog_array_map_मुक्त,
	.map_poke_track = prog_array_map_poke_track,
	.map_poke_untrack = prog_array_map_poke_untrack,
	.map_poke_run = prog_array_map_poke_run,
	.map_get_next_key = array_map_get_next_key,
	.map_lookup_elem = fd_array_map_lookup_elem,
	.map_delete_elem = fd_array_map_delete_elem,
	.map_fd_get_ptr = prog_fd_array_get_ptr,
	.map_fd_put_ptr = prog_fd_array_put_ptr,
	.map_fd_sys_lookup_elem = prog_fd_array_sys_lookup_elem,
	.map_release_uref = prog_array_map_clear,
	.map_seq_show_elem = prog_array_map_seq_show_elem,
	.map_btf_name = "bpf_array",
	.map_btf_id = &prog_array_map_btf_id,
पूर्ण;

अटल काष्ठा bpf_event_entry *bpf_event_entry_gen(काष्ठा file *perf_file,
						   काष्ठा file *map_file)
अणु
	काष्ठा bpf_event_entry *ee;

	ee = kzalloc(माप(*ee), GFP_ATOMIC);
	अगर (ee) अणु
		ee->event = perf_file->निजी_data;
		ee->perf_file = perf_file;
		ee->map_file = map_file;
	पूर्ण

	वापस ee;
पूर्ण

अटल व्योम __bpf_event_entry_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_event_entry *ee;

	ee = container_of(rcu, काष्ठा bpf_event_entry, rcu);
	fput(ee->perf_file);
	kमुक्त(ee);
पूर्ण

अटल व्योम bpf_event_entry_मुक्त_rcu(काष्ठा bpf_event_entry *ee)
अणु
	call_rcu(&ee->rcu, __bpf_event_entry_मुक्त);
पूर्ण

अटल व्योम *perf_event_fd_array_get_ptr(काष्ठा bpf_map *map,
					 काष्ठा file *map_file, पूर्णांक fd)
अणु
	काष्ठा bpf_event_entry *ee;
	काष्ठा perf_event *event;
	काष्ठा file *perf_file;
	u64 value;

	perf_file = perf_event_get(fd);
	अगर (IS_ERR(perf_file))
		वापस perf_file;

	ee = ERR_PTR(-EOPNOTSUPP);
	event = perf_file->निजी_data;
	अगर (perf_event_पढ़ो_local(event, &value, शून्य, शून्य) == -EOPNOTSUPP)
		जाओ err_out;

	ee = bpf_event_entry_gen(perf_file, map_file);
	अगर (ee)
		वापस ee;
	ee = ERR_PTR(-ENOMEM);
err_out:
	fput(perf_file);
	वापस ee;
पूर्ण

अटल व्योम perf_event_fd_array_put_ptr(व्योम *ptr)
अणु
	bpf_event_entry_मुक्त_rcu(ptr);
पूर्ण

अटल व्योम perf_event_fd_array_release(काष्ठा bpf_map *map,
					काष्ठा file *map_file)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	काष्ठा bpf_event_entry *ee;
	पूर्णांक i;

	अगर (map->map_flags & BPF_F_PRESERVE_ELEMS)
		वापस;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < array->map.max_entries; i++) अणु
		ee = READ_ONCE(array->ptrs[i]);
		अगर (ee && ee->map_file == map_file)
			fd_array_map_delete_elem(map, &i);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम perf_event_fd_array_map_मुक्त(काष्ठा bpf_map *map)
अणु
	अगर (map->map_flags & BPF_F_PRESERVE_ELEMS)
		bpf_fd_array_map_clear(map);
	fd_array_map_मुक्त(map);
पूर्ण

अटल पूर्णांक perf_event_array_map_btf_id;
स्थिर काष्ठा bpf_map_ops perf_event_array_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = fd_array_map_alloc_check,
	.map_alloc = array_map_alloc,
	.map_मुक्त = perf_event_fd_array_map_मुक्त,
	.map_get_next_key = array_map_get_next_key,
	.map_lookup_elem = fd_array_map_lookup_elem,
	.map_delete_elem = fd_array_map_delete_elem,
	.map_fd_get_ptr = perf_event_fd_array_get_ptr,
	.map_fd_put_ptr = perf_event_fd_array_put_ptr,
	.map_release = perf_event_fd_array_release,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "bpf_array",
	.map_btf_id = &perf_event_array_map_btf_id,
पूर्ण;

#अगर_घोषित CONFIG_CGROUPS
अटल व्योम *cgroup_fd_array_get_ptr(काष्ठा bpf_map *map,
				     काष्ठा file *map_file /* not used */,
				     पूर्णांक fd)
अणु
	वापस cgroup_get_from_fd(fd);
पूर्ण

अटल व्योम cgroup_fd_array_put_ptr(व्योम *ptr)
अणु
	/* cgroup_put मुक्त cgrp after a rcu grace period */
	cgroup_put(ptr);
पूर्ण

अटल व्योम cgroup_fd_array_मुक्त(काष्ठा bpf_map *map)
अणु
	bpf_fd_array_map_clear(map);
	fd_array_map_मुक्त(map);
पूर्ण

अटल पूर्णांक cgroup_array_map_btf_id;
स्थिर काष्ठा bpf_map_ops cgroup_array_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = fd_array_map_alloc_check,
	.map_alloc = array_map_alloc,
	.map_मुक्त = cgroup_fd_array_मुक्त,
	.map_get_next_key = array_map_get_next_key,
	.map_lookup_elem = fd_array_map_lookup_elem,
	.map_delete_elem = fd_array_map_delete_elem,
	.map_fd_get_ptr = cgroup_fd_array_get_ptr,
	.map_fd_put_ptr = cgroup_fd_array_put_ptr,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "bpf_array",
	.map_btf_id = &cgroup_array_map_btf_id,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा bpf_map *array_of_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_map *map, *inner_map_meta;

	inner_map_meta = bpf_map_meta_alloc(attr->inner_map_fd);
	अगर (IS_ERR(inner_map_meta))
		वापस inner_map_meta;

	map = array_map_alloc(attr);
	अगर (IS_ERR(map)) अणु
		bpf_map_meta_मुक्त(inner_map_meta);
		वापस map;
	पूर्ण

	map->inner_map_meta = inner_map_meta;

	वापस map;
पूर्ण

अटल व्योम array_of_map_मुक्त(काष्ठा bpf_map *map)
अणु
	/* map->inner_map_meta is only accessed by syscall which
	 * is रक्षित by fdget/fdput.
	 */
	bpf_map_meta_मुक्त(map->inner_map_meta);
	bpf_fd_array_map_clear(map);
	fd_array_map_मुक्त(map);
पूर्ण

अटल व्योम *array_of_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_map **inner_map = array_map_lookup_elem(map, key);

	अगर (!inner_map)
		वापस शून्य;

	वापस READ_ONCE(*inner_map);
पूर्ण

अटल पूर्णांक array_of_map_gen_lookup(काष्ठा bpf_map *map,
				   काष्ठा bpf_insn *insn_buf)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	u32 elem_size = round_up(map->value_size, 8);
	काष्ठा bpf_insn *insn = insn_buf;
	स्थिर पूर्णांक ret = BPF_REG_0;
	स्थिर पूर्णांक map_ptr = BPF_REG_1;
	स्थिर पूर्णांक index = BPF_REG_2;

	*insn++ = BPF_ALU64_IMM(BPF_ADD, map_ptr, दुरत्व(काष्ठा bpf_array, value));
	*insn++ = BPF_LDX_MEM(BPF_W, ret, index, 0);
	अगर (!map->bypass_spec_v1) अणु
		*insn++ = BPF_JMP_IMM(BPF_JGE, ret, map->max_entries, 6);
		*insn++ = BPF_ALU32_IMM(BPF_AND, ret, array->index_mask);
	पूर्ण अन्यथा अणु
		*insn++ = BPF_JMP_IMM(BPF_JGE, ret, map->max_entries, 5);
	पूर्ण
	अगर (is_घातer_of_2(elem_size))
		*insn++ = BPF_ALU64_IMM(BPF_LSH, ret, ilog2(elem_size));
	अन्यथा
		*insn++ = BPF_ALU64_IMM(BPF_MUL, ret, elem_size);
	*insn++ = BPF_ALU64_REG(BPF_ADD, ret, map_ptr);
	*insn++ = BPF_LDX_MEM(BPF_DW, ret, ret, 0);
	*insn++ = BPF_JMP_IMM(BPF_JEQ, ret, 0, 1);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
	*insn++ = BPF_MOV64_IMM(ret, 0);

	वापस insn - insn_buf;
पूर्ण

अटल पूर्णांक array_of_maps_map_btf_id;
स्थिर काष्ठा bpf_map_ops array_of_maps_map_ops = अणु
	.map_alloc_check = fd_array_map_alloc_check,
	.map_alloc = array_of_map_alloc,
	.map_मुक्त = array_of_map_मुक्त,
	.map_get_next_key = array_map_get_next_key,
	.map_lookup_elem = array_of_map_lookup_elem,
	.map_delete_elem = fd_array_map_delete_elem,
	.map_fd_get_ptr = bpf_map_fd_get_ptr,
	.map_fd_put_ptr = bpf_map_fd_put_ptr,
	.map_fd_sys_lookup_elem = bpf_map_fd_sys_lookup_elem,
	.map_gen_lookup = array_of_map_gen_lookup,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "bpf_array",
	.map_btf_id = &array_of_maps_map_btf_id,
पूर्ण;
