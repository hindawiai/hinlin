<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 */
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/bpf_lirc.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/btf.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/license.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/idr.h>
#समावेश <linux/cred.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/nospec.h>
#समावेश <linux/audit.h>
#समावेश <uapi/linux/btf.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/bpf_lsm.h>
#समावेश <linux/poll.h>
#समावेश <linux/bpf-netns.h>
#समावेश <linux/rcupdate_trace.h>
#समावेश <linux/memcontrol.h>

#घोषणा IS_FD_ARRAY(map) ((map)->map_type == BPF_MAP_TYPE_PERF_EVENT_ARRAY || \
			  (map)->map_type == BPF_MAP_TYPE_CGROUP_ARRAY || \
			  (map)->map_type == BPF_MAP_TYPE_ARRAY_OF_MAPS)
#घोषणा IS_FD_PROG_ARRAY(map) ((map)->map_type == BPF_MAP_TYPE_PROG_ARRAY)
#घोषणा IS_FD_HASH(map) ((map)->map_type == BPF_MAP_TYPE_HASH_OF_MAPS)
#घोषणा IS_FD_MAP(map) (IS_FD_ARRAY(map) || IS_FD_PROG_ARRAY(map) || \
			IS_FD_HASH(map))

#घोषणा BPF_OBJ_FLAG_MASK   (BPF_F_RDONLY | BPF_F_WRONLY)

DEFINE_PER_CPU(पूर्णांक, bpf_prog_active);
अटल DEFINE_IDR(prog_idr);
अटल DEFINE_SPINLOCK(prog_idr_lock);
अटल DEFINE_IDR(map_idr);
अटल DEFINE_SPINLOCK(map_idr_lock);
अटल DEFINE_IDR(link_idr);
अटल DEFINE_SPINLOCK(link_idr_lock);

पूर्णांक sysctl_unprivileged_bpf_disabled __पढ़ो_mostly =
	IS_BUILTIN(CONFIG_BPF_UNPRIV_DEFAULT_OFF) ? 2 : 0;

अटल स्थिर काष्ठा bpf_map_ops * स्थिर bpf_map_types[] = अणु
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type)
#घोषणा BPF_MAP_TYPE(_id, _ops) \
	[_id] = &_ops,
#घोषणा BPF_LINK_TYPE(_id, _name)
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
#अघोषित BPF_MAP_TYPE
#अघोषित BPF_LINK_TYPE
पूर्ण;

/*
 * If we're handed a bigger काष्ठा than we know of, ensure all the unknown bits
 * are 0 - i.e. new user-space करोes not rely on any kernel feature extensions
 * we करोn't know about yet.
 *
 * There is a ToCToU between this function call and the following
 * copy_from_user() call. However, this is not a concern since this function is
 * meant to be a future-proofing of bits.
 */
पूर्णांक bpf_check_uarg_tail_zero(व्योम __user *uaddr,
			     माप_प्रकार expected_size,
			     माप_प्रकार actual_size)
अणु
	अचिन्हित अक्षर __user *addr = uaddr + expected_size;
	पूर्णांक res;

	अगर (unlikely(actual_size > PAGE_SIZE))	/* silly large */
		वापस -E2BIG;

	अगर (actual_size <= expected_size)
		वापस 0;

	res = check_zeroed_user(addr, actual_size - expected_size);
	अगर (res < 0)
		वापस res;
	वापस res ? 0 : -E2BIG;
पूर्ण

स्थिर काष्ठा bpf_map_ops bpf_map_offload_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc = bpf_map_offload_map_alloc,
	.map_मुक्त = bpf_map_offload_map_मुक्त,
	.map_check_btf = map_check_no_btf,
पूर्ण;

अटल काष्ठा bpf_map *find_and_alloc_map(जोड़ bpf_attr *attr)
अणु
	स्थिर काष्ठा bpf_map_ops *ops;
	u32 type = attr->map_type;
	काष्ठा bpf_map *map;
	पूर्णांक err;

	अगर (type >= ARRAY_SIZE(bpf_map_types))
		वापस ERR_PTR(-EINVAL);
	type = array_index_nospec(type, ARRAY_SIZE(bpf_map_types));
	ops = bpf_map_types[type];
	अगर (!ops)
		वापस ERR_PTR(-EINVAL);

	अगर (ops->map_alloc_check) अणु
		err = ops->map_alloc_check(attr);
		अगर (err)
			वापस ERR_PTR(err);
	पूर्ण
	अगर (attr->map_अगरindex)
		ops = &bpf_map_offload_ops;
	map = ops->map_alloc(attr);
	अगर (IS_ERR(map))
		वापस map;
	map->ops = ops;
	map->map_type = type;
	वापस map;
पूर्ण

अटल u32 bpf_map_value_size(स्थिर काष्ठा bpf_map *map)
अणु
	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_PERCPU_ARRAY ||
	    map->map_type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE)
		वापस round_up(map->value_size, 8) * num_possible_cpus();
	अन्यथा अगर (IS_FD_MAP(map))
		वापस माप(u32);
	अन्यथा
		वापस  map->value_size;
पूर्ण

अटल व्योम maybe_रुको_bpf_programs(काष्ठा bpf_map *map)
अणु
	/* Wait क्रम any running BPF programs to complete so that
	 * userspace, when we वापस to it, knows that all programs
	 * that could be running use the new map value.
	 */
	अगर (map->map_type == BPF_MAP_TYPE_HASH_OF_MAPS ||
	    map->map_type == BPF_MAP_TYPE_ARRAY_OF_MAPS)
		synchronize_rcu();
पूर्ण

अटल पूर्णांक bpf_map_update_value(काष्ठा bpf_map *map, काष्ठा fd f, व्योम *key,
				व्योम *value, __u64 flags)
अणु
	पूर्णांक err;

	/* Need to create a kthपढ़ो, thus must support schedule */
	अगर (bpf_map_is_dev_bound(map)) अणु
		वापस bpf_map_offload_update_elem(map, key, value, flags);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_CPUMAP ||
		   map->map_type == BPF_MAP_TYPE_STRUCT_OPS) अणु
		वापस map->ops->map_update_elem(map, key, value, flags);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_SOCKHASH ||
		   map->map_type == BPF_MAP_TYPE_SOCKMAP) अणु
		वापस sock_map_update_elem_sys(map, key, value, flags);
	पूर्ण अन्यथा अगर (IS_FD_PROG_ARRAY(map)) अणु
		वापस bpf_fd_array_map_update_elem(map, f.file, key, value,
						    flags);
	पूर्ण

	bpf_disable_instrumentation();
	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH) अणु
		err = bpf_percpu_hash_update(map, key, value, flags);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_PERCPU_ARRAY) अणु
		err = bpf_percpu_array_update(map, key, value, flags);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE) अणु
		err = bpf_percpu_cgroup_storage_update(map, key, value,
						       flags);
	पूर्ण अन्यथा अगर (IS_FD_ARRAY(map)) अणु
		rcu_पढ़ो_lock();
		err = bpf_fd_array_map_update_elem(map, f.file, key, value,
						   flags);
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_HASH_OF_MAPS) अणु
		rcu_पढ़ो_lock();
		err = bpf_fd_htab_map_update_elem(map, f.file, key, value,
						  flags);
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_REUSEPORT_SOCKARRAY) अणु
		/* rcu_पढ़ो_lock() is not needed */
		err = bpf_fd_reuseport_array_update_elem(map, key, value,
							 flags);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_QUEUE ||
		   map->map_type == BPF_MAP_TYPE_STACK) अणु
		err = map->ops->map_push_elem(map, value, flags);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		err = map->ops->map_update_elem(map, key, value, flags);
		rcu_पढ़ो_unlock();
	पूर्ण
	bpf_enable_instrumentation();
	maybe_रुको_bpf_programs(map);

	वापस err;
पूर्ण

अटल पूर्णांक bpf_map_copy_value(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			      __u64 flags)
अणु
	व्योम *ptr;
	पूर्णांक err;

	अगर (bpf_map_is_dev_bound(map))
		वापस bpf_map_offload_lookup_elem(map, key, value);

	bpf_disable_instrumentation();
	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH) अणु
		err = bpf_percpu_hash_copy(map, key, value);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_PERCPU_ARRAY) अणु
		err = bpf_percpu_array_copy(map, key, value);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE) अणु
		err = bpf_percpu_cgroup_storage_copy(map, key, value);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_STACK_TRACE) अणु
		err = bpf_stackmap_copy(map, key, value);
	पूर्ण अन्यथा अगर (IS_FD_ARRAY(map) || IS_FD_PROG_ARRAY(map)) अणु
		err = bpf_fd_array_map_lookup_elem(map, key, value);
	पूर्ण अन्यथा अगर (IS_FD_HASH(map)) अणु
		err = bpf_fd_htab_map_lookup_elem(map, key, value);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_REUSEPORT_SOCKARRAY) अणु
		err = bpf_fd_reuseport_array_lookup_elem(map, key, value);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_QUEUE ||
		   map->map_type == BPF_MAP_TYPE_STACK) अणु
		err = map->ops->map_peek_elem(map, value);
	पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_STRUCT_OPS) अणु
		/* काष्ठा_ops map requires directly updating "value" */
		err = bpf_काष्ठा_ops_map_sys_lookup_elem(map, key, value);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		अगर (map->ops->map_lookup_elem_sys_only)
			ptr = map->ops->map_lookup_elem_sys_only(map, key);
		अन्यथा
			ptr = map->ops->map_lookup_elem(map, key);
		अगर (IS_ERR(ptr)) अणु
			err = PTR_ERR(ptr);
		पूर्ण अन्यथा अगर (!ptr) अणु
			err = -ENOENT;
		पूर्ण अन्यथा अणु
			err = 0;
			अगर (flags & BPF_F_LOCK)
				/* lock 'ptr' and copy everything but lock */
				copy_map_value_locked(map, value, ptr, true);
			अन्यथा
				copy_map_value(map, value, ptr);
			/* mask lock, since value wasn't zero inited */
			check_and_init_map_lock(map, value);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	bpf_enable_instrumentation();
	maybe_रुको_bpf_programs(map);

	वापस err;
पूर्ण

/* Please, करो not use this function outside from the map creation path
 * (e.g. in map update path) without taking care of setting the active
 * memory cgroup (see at bpf_map_kदो_स्मृति_node() क्रम example).
 */
अटल व्योम *__bpf_map_area_alloc(u64 size, पूर्णांक numa_node, bool mmapable)
अणु
	/* We really just want to fail instead of triggering OOM समाप्तer
	 * under memory pressure, thereक्रमe we set __GFP_NORETRY to kदो_स्मृति,
	 * which is used क्रम lower order allocation requests.
	 *
	 * It has been observed that higher order allocation requests करोne by
	 * vदो_स्मृति with __GFP_NORETRY being set might fail due to not trying
	 * to reclaim memory from the page cache, thus we set
	 * __GFP_RETRY_MAYFAIL to aव्योम such situations.
	 */

	स्थिर gfp_t gfp = __GFP_NOWARN | __GFP_ZERO | __GFP_ACCOUNT;
	अचिन्हित पूर्णांक flags = 0;
	अचिन्हित दीर्घ align = 1;
	व्योम *area;

	अगर (size >= SIZE_MAX)
		वापस शून्य;

	/* kदो_स्मृति()'ed memory can't be mmap()'ed */
	अगर (mmapable) अणु
		BUG_ON(!PAGE_ALIGNED(size));
		align = SHMLBA;
		flags = VM_USERMAP;
	पूर्ण अन्यथा अगर (size <= (PAGE_SIZE << PAGE_ALLOC_COSTLY_ORDER)) अणु
		area = kदो_स्मृति_node(size, gfp | GFP_USER | __GFP_NORETRY,
				    numa_node);
		अगर (area != शून्य)
			वापस area;
	पूर्ण

	वापस __vदो_स्मृति_node_range(size, align, VMALLOC_START, VMALLOC_END,
			gfp | GFP_KERNEL | __GFP_RETRY_MAYFAIL, PAGE_KERNEL,
			flags, numa_node, __builtin_वापस_address(0));
पूर्ण

व्योम *bpf_map_area_alloc(u64 size, पूर्णांक numa_node)
अणु
	वापस __bpf_map_area_alloc(size, numa_node, false);
पूर्ण

व्योम *bpf_map_area_mmapable_alloc(u64 size, पूर्णांक numa_node)
अणु
	वापस __bpf_map_area_alloc(size, numa_node, true);
पूर्ण

व्योम bpf_map_area_मुक्त(व्योम *area)
अणु
	kvमुक्त(area);
पूर्ण

अटल u32 bpf_map_flags_retain_permanent(u32 flags)
अणु
	/* Some map creation flags are not tied to the map object but
	 * rather to the map fd instead, so they have no meaning upon
	 * map object inspection since multiple file descriptors with
	 * dअगरferent (access) properties can exist here. Thus, given
	 * this has zero meaning क्रम the map itself, lets clear these
	 * from here.
	 */
	वापस flags & ~(BPF_F_RDONLY | BPF_F_WRONLY);
पूर्ण

व्योम bpf_map_init_from_attr(काष्ठा bpf_map *map, जोड़ bpf_attr *attr)
अणु
	map->map_type = attr->map_type;
	map->key_size = attr->key_size;
	map->value_size = attr->value_size;
	map->max_entries = attr->max_entries;
	map->map_flags = bpf_map_flags_retain_permanent(attr->map_flags);
	map->numa_node = bpf_map_attr_numa_node(attr);
पूर्ण

अटल पूर्णांक bpf_map_alloc_id(काष्ठा bpf_map *map)
अणु
	पूर्णांक id;

	idr_preload(GFP_KERNEL);
	spin_lock_bh(&map_idr_lock);
	id = idr_alloc_cyclic(&map_idr, map, 1, पूर्णांक_उच्च, GFP_ATOMIC);
	अगर (id > 0)
		map->id = id;
	spin_unlock_bh(&map_idr_lock);
	idr_preload_end();

	अगर (WARN_ON_ONCE(!id))
		वापस -ENOSPC;

	वापस id > 0 ? 0 : id;
पूर्ण

व्योम bpf_map_मुक्त_id(काष्ठा bpf_map *map, bool करो_idr_lock)
अणु
	अचिन्हित दीर्घ flags;

	/* Offloaded maps are हटाओd from the IDR store when their device
	 * disappears - even अगर someone holds an fd to them they are unusable,
	 * the memory is gone, all ops will fail; they are simply रुकोing क्रम
	 * refcnt to drop to be मुक्तd.
	 */
	अगर (!map->id)
		वापस;

	अगर (करो_idr_lock)
		spin_lock_irqsave(&map_idr_lock, flags);
	अन्यथा
		__acquire(&map_idr_lock);

	idr_हटाओ(&map_idr, map->id);
	map->id = 0;

	अगर (करो_idr_lock)
		spin_unlock_irqrestore(&map_idr_lock, flags);
	अन्यथा
		__release(&map_idr_lock);
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
अटल व्योम bpf_map_save_memcg(काष्ठा bpf_map *map)
अणु
	map->memcg = get_mem_cgroup_from_mm(current->mm);
पूर्ण

अटल व्योम bpf_map_release_memcg(काष्ठा bpf_map *map)
अणु
	mem_cgroup_put(map->memcg);
पूर्ण

व्योम *bpf_map_kदो_स्मृति_node(स्थिर काष्ठा bpf_map *map, माप_प्रकार size, gfp_t flags,
			   पूर्णांक node)
अणु
	काष्ठा mem_cgroup *old_memcg;
	व्योम *ptr;

	old_memcg = set_active_memcg(map->memcg);
	ptr = kदो_स्मृति_node(size, flags | __GFP_ACCOUNT, node);
	set_active_memcg(old_memcg);

	वापस ptr;
पूर्ण

व्योम *bpf_map_kzalloc(स्थिर काष्ठा bpf_map *map, माप_प्रकार size, gfp_t flags)
अणु
	काष्ठा mem_cgroup *old_memcg;
	व्योम *ptr;

	old_memcg = set_active_memcg(map->memcg);
	ptr = kzalloc(size, flags | __GFP_ACCOUNT);
	set_active_memcg(old_memcg);

	वापस ptr;
पूर्ण

व्योम __percpu *bpf_map_alloc_percpu(स्थिर काष्ठा bpf_map *map, माप_प्रकार size,
				    माप_प्रकार align, gfp_t flags)
अणु
	काष्ठा mem_cgroup *old_memcg;
	व्योम __percpu *ptr;

	old_memcg = set_active_memcg(map->memcg);
	ptr = __alloc_percpu_gfp(size, align, flags | __GFP_ACCOUNT);
	set_active_memcg(old_memcg);

	वापस ptr;
पूर्ण

#अन्यथा
अटल व्योम bpf_map_save_memcg(काष्ठा bpf_map *map)
अणु
पूर्ण

अटल व्योम bpf_map_release_memcg(काष्ठा bpf_map *map)
अणु
पूर्ण
#पूर्ण_अगर

/* called from workqueue */
अटल व्योम bpf_map_मुक्त_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bpf_map *map = container_of(work, काष्ठा bpf_map, work);

	security_bpf_map_मुक्त(map);
	bpf_map_release_memcg(map);
	/* implementation dependent मुक्तing */
	map->ops->map_मुक्त(map);
पूर्ण

अटल व्योम bpf_map_put_uref(काष्ठा bpf_map *map)
अणु
	अगर (atomic64_dec_and_test(&map->usercnt)) अणु
		अगर (map->ops->map_release_uref)
			map->ops->map_release_uref(map);
	पूर्ण
पूर्ण

/* decrement map refcnt and schedule it क्रम मुक्तing via workqueue
 * (unrelying map implementation ops->map_मुक्त() might sleep)
 */
अटल व्योम __bpf_map_put(काष्ठा bpf_map *map, bool करो_idr_lock)
अणु
	अगर (atomic64_dec_and_test(&map->refcnt)) अणु
		/* bpf_map_मुक्त_id() must be called first */
		bpf_map_मुक्त_id(map, करो_idr_lock);
		btf_put(map->btf);
		INIT_WORK(&map->work, bpf_map_मुक्त_deferred);
		schedule_work(&map->work);
	पूर्ण
पूर्ण

व्योम bpf_map_put(काष्ठा bpf_map *map)
अणु
	__bpf_map_put(map, true);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_map_put);

व्योम bpf_map_put_with_uref(काष्ठा bpf_map *map)
अणु
	bpf_map_put_uref(map);
	bpf_map_put(map);
पूर्ण

अटल पूर्णांक bpf_map_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा bpf_map *map = filp->निजी_data;

	अगर (map->ops->map_release)
		map->ops->map_release(map, filp);

	bpf_map_put_with_uref(map);
	वापस 0;
पूर्ण

अटल भ_शेषe_t map_get_sys_perms(काष्ठा bpf_map *map, काष्ठा fd f)
अणु
	भ_शेषe_t mode = f.file->f_mode;

	/* Our file permissions may have been overridden by global
	 * map permissions facing syscall side.
	 */
	अगर (READ_ONCE(map->frozen))
		mode &= ~FMODE_CAN_WRITE;
	वापस mode;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* Provides an approximation of the map's memory footprपूर्णांक.
 * Used only to provide a backward compatibility and display
 * a reasonable "memlock" info.
 */
अटल अचिन्हित दीर्घ bpf_map_memory_footprपूर्णांक(स्थिर काष्ठा bpf_map *map)
अणु
	अचिन्हित दीर्घ size;

	size = round_up(map->key_size + bpf_map_value_size(map), 8);

	वापस round_up(map->max_entries * size, PAGE_SIZE);
पूर्ण

अटल व्योम bpf_map_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *filp)
अणु
	स्थिर काष्ठा bpf_map *map = filp->निजी_data;
	स्थिर काष्ठा bpf_array *array;
	u32 type = 0, jited = 0;

	अगर (map->map_type == BPF_MAP_TYPE_PROG_ARRAY) अणु
		array = container_of(map, काष्ठा bpf_array, map);
		type  = array->aux->type;
		jited = array->aux->jited;
	पूर्ण

	seq_म_लिखो(m,
		   "map_type:\t%u\n"
		   "key_size:\t%u\n"
		   "value_size:\t%u\n"
		   "max_entries:\t%u\n"
		   "map_flags:\t%#x\n"
		   "memlock:\t%lu\n"
		   "map_id:\t%u\n"
		   "frozen:\t%u\n",
		   map->map_type,
		   map->key_size,
		   map->value_size,
		   map->max_entries,
		   map->map_flags,
		   bpf_map_memory_footprपूर्णांक(map),
		   map->id,
		   READ_ONCE(map->frozen));
	अगर (type) अणु
		seq_म_लिखो(m, "owner_prog_type:\t%u\n", type);
		seq_म_लिखो(m, "owner_jited:\t%u\n", jited);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार bpf_dummy_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार siz,
			      loff_t *ppos)
अणु
	/* We need this handler such that alloc_file() enables
	 * f_mode with FMODE_CAN_READ.
	 */
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार bpf_dummy_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			       माप_प्रकार siz, loff_t *ppos)
अणु
	/* We need this handler such that alloc_file() enables
	 * f_mode with FMODE_CAN_WRITE.
	 */
	वापस -EINVAL;
पूर्ण

/* called क्रम any extra memory-mapped regions (except initial) */
अटल व्योम bpf_map_mmap_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bpf_map *map = vma->vm_file->निजी_data;

	अगर (vma->vm_flags & VM_MAYWRITE) अणु
		mutex_lock(&map->मुक्तze_mutex);
		map->ग_लिखोcnt++;
		mutex_unlock(&map->मुक्तze_mutex);
	पूर्ण
पूर्ण

/* called क्रम all unmapped memory region (including initial) */
अटल व्योम bpf_map_mmap_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bpf_map *map = vma->vm_file->निजी_data;

	अगर (vma->vm_flags & VM_MAYWRITE) अणु
		mutex_lock(&map->मुक्तze_mutex);
		map->ग_लिखोcnt--;
		mutex_unlock(&map->मुक्तze_mutex);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा bpf_map_शेष_vmops = अणु
	.खोलो		= bpf_map_mmap_खोलो,
	.बंद		= bpf_map_mmap_बंद,
पूर्ण;

अटल पूर्णांक bpf_map_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bpf_map *map = filp->निजी_data;
	पूर्णांक err;

	अगर (!map->ops->map_mmap || map_value_has_spin_lock(map))
		वापस -ENOTSUPP;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	mutex_lock(&map->मुक्तze_mutex);

	अगर (vma->vm_flags & VM_WRITE) अणु
		अगर (map->frozen) अणु
			err = -EPERM;
			जाओ out;
		पूर्ण
		/* map is meant to be पढ़ो-only, so करो not allow mapping as
		 * writable, because it's possible to leak a writable page
		 * reference and allows user-space to still modअगरy it after
		 * मुक्तzing, जबतक verअगरier will assume contents करो not change
		 */
		अगर (map->map_flags & BPF_F_RDONLY_PROG) अणु
			err = -EACCES;
			जाओ out;
		पूर्ण
	पूर्ण

	/* set शेष खोलो/बंद callbacks */
	vma->vm_ops = &bpf_map_शेष_vmops;
	vma->vm_निजी_data = map;
	vma->vm_flags &= ~VM_MAYEXEC;
	अगर (!(vma->vm_flags & VM_WRITE))
		/* disallow re-mapping with PROT_WRITE */
		vma->vm_flags &= ~VM_MAYWRITE;

	err = map->ops->map_mmap(map, vma);
	अगर (err)
		जाओ out;

	अगर (vma->vm_flags & VM_MAYWRITE)
		map->ग_लिखोcnt++;
out:
	mutex_unlock(&map->मुक्तze_mutex);
	वापस err;
पूर्ण

अटल __poll_t bpf_map_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *pts)
अणु
	काष्ठा bpf_map *map = filp->निजी_data;

	अगर (map->ops->map_poll)
		वापस map->ops->map_poll(map, filp, pts);

	वापस EPOLLERR;
पूर्ण

स्थिर काष्ठा file_operations bpf_map_fops = अणु
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= bpf_map_show_fdinfo,
#पूर्ण_अगर
	.release	= bpf_map_release,
	.पढ़ो		= bpf_dummy_पढ़ो,
	.ग_लिखो		= bpf_dummy_ग_लिखो,
	.mmap		= bpf_map_mmap,
	.poll		= bpf_map_poll,
पूर्ण;

पूर्णांक bpf_map_new_fd(काष्ठा bpf_map *map, पूर्णांक flags)
अणु
	पूर्णांक ret;

	ret = security_bpf_map(map, OPEN_FMODE(flags));
	अगर (ret < 0)
		वापस ret;

	वापस anon_inode_getfd("bpf-map", &bpf_map_fops, map,
				flags | O_CLOEXEC);
पूर्ण

पूर्णांक bpf_get_file_flag(पूर्णांक flags)
अणु
	अगर ((flags & BPF_F_RDONLY) && (flags & BPF_F_WRONLY))
		वापस -EINVAL;
	अगर (flags & BPF_F_RDONLY)
		वापस O_RDONLY;
	अगर (flags & BPF_F_WRONLY)
		वापस O_WRONLY;
	वापस O_RDWR;
पूर्ण

/* helper macro to check that unused fields 'union bpf_attr' are zero */
#घोषणा CHECK_ATTR(CMD) \
	स_प्रथम_inv((व्योम *) &attr->CMD##_LAST_FIELD + \
		   माप(attr->CMD##_LAST_FIELD), 0, \
		   माप(*attr) - \
		   दुरत्व(जोड़ bpf_attr, CMD##_LAST_FIELD) - \
		   माप(attr->CMD##_LAST_FIELD)) != शून्य

/* dst and src must have at least "size" number of bytes.
 * Return म_माप on success and < 0 on error.
 */
पूर्णांक bpf_obj_name_cpy(अक्षर *dst, स्थिर अक्षर *src, अचिन्हित पूर्णांक size)
अणु
	स्थिर अक्षर *end = src + size;
	स्थिर अक्षर *orig_src = src;

	स_रखो(dst, 0, size);
	/* Copy all है_अक्षर_अंक(), '_' and '.' अक्षरs. */
	जबतक (src < end && *src) अणु
		अगर (!है_अक्षर_अंक(*src) &&
		    *src != '_' && *src != '.')
			वापस -EINVAL;
		*dst++ = *src++;
	पूर्ण

	/* No '\0' found in "size" number of bytes */
	अगर (src == end)
		वापस -EINVAL;

	वापस src - orig_src;
पूर्ण

पूर्णांक map_check_no_btf(स्थिर काष्ठा bpf_map *map,
		     स्थिर काष्ठा btf *btf,
		     स्थिर काष्ठा btf_type *key_type,
		     स्थिर काष्ठा btf_type *value_type)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक map_check_btf(काष्ठा bpf_map *map, स्थिर काष्ठा btf *btf,
			 u32 btf_key_id, u32 btf_value_id)
अणु
	स्थिर काष्ठा btf_type *key_type, *value_type;
	u32 key_size, value_size;
	पूर्णांक ret = 0;

	/* Some maps allow key to be unspecअगरied. */
	अगर (btf_key_id) अणु
		key_type = btf_type_id_size(btf, &btf_key_id, &key_size);
		अगर (!key_type || key_size != map->key_size)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		key_type = btf_type_by_id(btf, 0);
		अगर (!map->ops->map_check_btf)
			वापस -EINVAL;
	पूर्ण

	value_type = btf_type_id_size(btf, &btf_value_id, &value_size);
	अगर (!value_type || value_size != map->value_size)
		वापस -EINVAL;

	map->spin_lock_off = btf_find_spin_lock(btf, value_type);

	अगर (map_value_has_spin_lock(map)) अणु
		अगर (map->map_flags & BPF_F_RDONLY_PROG)
			वापस -EACCES;
		अगर (map->map_type != BPF_MAP_TYPE_HASH &&
		    map->map_type != BPF_MAP_TYPE_ARRAY &&
		    map->map_type != BPF_MAP_TYPE_CGROUP_STORAGE &&
		    map->map_type != BPF_MAP_TYPE_SK_STORAGE &&
		    map->map_type != BPF_MAP_TYPE_INODE_STORAGE &&
		    map->map_type != BPF_MAP_TYPE_TASK_STORAGE)
			वापस -ENOTSUPP;
		अगर (map->spin_lock_off + माप(काष्ठा bpf_spin_lock) >
		    map->value_size) अणु
			WARN_ONCE(1,
				  "verifier bug spin_lock_off %d value_size %d\n",
				  map->spin_lock_off, map->value_size);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (map->ops->map_check_btf)
		ret = map->ops->map_check_btf(map, btf, key_type, value_type);

	वापस ret;
पूर्ण

#घोषणा BPF_MAP_CREATE_LAST_FIELD btf_vmlinux_value_type_id
/* called via syscall */
अटल पूर्णांक map_create(जोड़ bpf_attr *attr)
अणु
	पूर्णांक numa_node = bpf_map_attr_numa_node(attr);
	काष्ठा bpf_map *map;
	पूर्णांक f_flags;
	पूर्णांक err;

	err = CHECK_ATTR(BPF_MAP_CREATE);
	अगर (err)
		वापस -EINVAL;

	अगर (attr->btf_vmlinux_value_type_id) अणु
		अगर (attr->map_type != BPF_MAP_TYPE_STRUCT_OPS ||
		    attr->btf_key_type_id || attr->btf_value_type_id)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (attr->btf_key_type_id && !attr->btf_value_type_id) अणु
		वापस -EINVAL;
	पूर्ण

	f_flags = bpf_get_file_flag(attr->map_flags);
	अगर (f_flags < 0)
		वापस f_flags;

	अगर (numa_node != NUMA_NO_NODE &&
	    ((अचिन्हित पूर्णांक)numa_node >= nr_node_ids ||
	     !node_online(numa_node)))
		वापस -EINVAL;

	/* find map type and init map: hashtable vs rbtree vs bloom vs ... */
	map = find_and_alloc_map(attr);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	err = bpf_obj_name_cpy(map->name, attr->map_name,
			       माप(attr->map_name));
	अगर (err < 0)
		जाओ मुक्त_map;

	atomic64_set(&map->refcnt, 1);
	atomic64_set(&map->usercnt, 1);
	mutex_init(&map->मुक्तze_mutex);

	map->spin_lock_off = -EINVAL;
	अगर (attr->btf_key_type_id || attr->btf_value_type_id ||
	    /* Even the map's value is a kernel's काष्ठा,
	     * the bpf_prog.o must have BTF to begin with
	     * to figure out the corresponding kernel's
	     * counter part.  Thus, attr->btf_fd has
	     * to be valid also.
	     */
	    attr->btf_vmlinux_value_type_id) अणु
		काष्ठा btf *btf;

		btf = btf_get_by_fd(attr->btf_fd);
		अगर (IS_ERR(btf)) अणु
			err = PTR_ERR(btf);
			जाओ मुक्त_map;
		पूर्ण
		अगर (btf_is_kernel(btf)) अणु
			btf_put(btf);
			err = -EACCES;
			जाओ मुक्त_map;
		पूर्ण
		map->btf = btf;

		अगर (attr->btf_value_type_id) अणु
			err = map_check_btf(map, btf, attr->btf_key_type_id,
					    attr->btf_value_type_id);
			अगर (err)
				जाओ मुक्त_map;
		पूर्ण

		map->btf_key_type_id = attr->btf_key_type_id;
		map->btf_value_type_id = attr->btf_value_type_id;
		map->btf_vmlinux_value_type_id =
			attr->btf_vmlinux_value_type_id;
	पूर्ण

	err = security_bpf_map_alloc(map);
	अगर (err)
		जाओ मुक्त_map;

	err = bpf_map_alloc_id(map);
	अगर (err)
		जाओ मुक्त_map_sec;

	bpf_map_save_memcg(map);

	err = bpf_map_new_fd(map, f_flags);
	अगर (err < 0) अणु
		/* failed to allocate fd.
		 * bpf_map_put_with_uref() is needed because the above
		 * bpf_map_alloc_id() has published the map
		 * to the userspace and the userspace may
		 * have refcnt-ed it through BPF_MAP_GET_FD_BY_ID.
		 */
		bpf_map_put_with_uref(map);
		वापस err;
	पूर्ण

	वापस err;

मुक्त_map_sec:
	security_bpf_map_मुक्त(map);
मुक्त_map:
	btf_put(map->btf);
	map->ops->map_मुक्त(map);
	वापस err;
पूर्ण

/* अगर error is वापसed, fd is released.
 * On success caller should complete fd access with matching fdput()
 */
काष्ठा bpf_map *__bpf_map_get(काष्ठा fd f)
अणु
	अगर (!f.file)
		वापस ERR_PTR(-EBADF);
	अगर (f.file->f_op != &bpf_map_fops) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस f.file->निजी_data;
पूर्ण

व्योम bpf_map_inc(काष्ठा bpf_map *map)
अणु
	atomic64_inc(&map->refcnt);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_map_inc);

व्योम bpf_map_inc_with_uref(काष्ठा bpf_map *map)
अणु
	atomic64_inc(&map->refcnt);
	atomic64_inc(&map->usercnt);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_map_inc_with_uref);

काष्ठा bpf_map *bpf_map_get(u32 ufd)
अणु
	काष्ठा fd f = fdget(ufd);
	काष्ठा bpf_map *map;

	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस map;

	bpf_map_inc(map);
	fdput(f);

	वापस map;
पूर्ण

काष्ठा bpf_map *bpf_map_get_with_uref(u32 ufd)
अणु
	काष्ठा fd f = fdget(ufd);
	काष्ठा bpf_map *map;

	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस map;

	bpf_map_inc_with_uref(map);
	fdput(f);

	वापस map;
पूर्ण

/* map_idr_lock should have been held */
अटल काष्ठा bpf_map *__bpf_map_inc_not_zero(काष्ठा bpf_map *map, bool uref)
अणु
	पूर्णांक refold;

	refold = atomic64_fetch_add_unless(&map->refcnt, 1, 0);
	अगर (!refold)
		वापस ERR_PTR(-ENOENT);
	अगर (uref)
		atomic64_inc(&map->usercnt);

	वापस map;
पूर्ण

काष्ठा bpf_map *bpf_map_inc_not_zero(काष्ठा bpf_map *map)
अणु
	spin_lock_bh(&map_idr_lock);
	map = __bpf_map_inc_not_zero(map, false);
	spin_unlock_bh(&map_idr_lock);

	वापस map;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_map_inc_not_zero);

पूर्णांक __weak bpf_stackmap_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल व्योम *__bpf_copy_key(व्योम __user *ukey, u64 key_size)
अणु
	अगर (key_size)
		वापस memdup_user(ukey, key_size);

	अगर (ukey)
		वापस ERR_PTR(-EINVAL);

	वापस शून्य;
पूर्ण

/* last field in 'union bpf_attr' used by this command */
#घोषणा BPF_MAP_LOOKUP_ELEM_LAST_FIELD flags

अटल पूर्णांक map_lookup_elem(जोड़ bpf_attr *attr)
अणु
	व्योम __user *ukey = u64_to_user_ptr(attr->key);
	व्योम __user *uvalue = u64_to_user_ptr(attr->value);
	पूर्णांक ufd = attr->map_fd;
	काष्ठा bpf_map *map;
	व्योम *key, *value;
	u32 value_size;
	काष्ठा fd f;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_MAP_LOOKUP_ELEM))
		वापस -EINVAL;

	अगर (attr->flags & ~BPF_F_LOCK)
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	अगर (!(map_get_sys_perms(map, f) & FMODE_CAN_READ)) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	अगर ((attr->flags & BPF_F_LOCK) &&
	    !map_value_has_spin_lock(map)) अणु
		err = -EINVAL;
		जाओ err_put;
	पूर्ण

	key = __bpf_copy_key(ukey, map->key_size);
	अगर (IS_ERR(key)) अणु
		err = PTR_ERR(key);
		जाओ err_put;
	पूर्ण

	value_size = bpf_map_value_size(map);

	err = -ENOMEM;
	value = kदो_स्मृति(value_size, GFP_USER | __GFP_NOWARN);
	अगर (!value)
		जाओ मुक्त_key;

	err = bpf_map_copy_value(map, key, value, attr->flags);
	अगर (err)
		जाओ मुक्त_value;

	err = -EFAULT;
	अगर (copy_to_user(uvalue, value, value_size) != 0)
		जाओ मुक्त_value;

	err = 0;

मुक्त_value:
	kमुक्त(value);
मुक्त_key:
	kमुक्त(key);
err_put:
	fdput(f);
	वापस err;
पूर्ण


#घोषणा BPF_MAP_UPDATE_ELEM_LAST_FIELD flags

अटल पूर्णांक map_update_elem(जोड़ bpf_attr *attr)
अणु
	व्योम __user *ukey = u64_to_user_ptr(attr->key);
	व्योम __user *uvalue = u64_to_user_ptr(attr->value);
	पूर्णांक ufd = attr->map_fd;
	काष्ठा bpf_map *map;
	व्योम *key, *value;
	u32 value_size;
	काष्ठा fd f;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_MAP_UPDATE_ELEM))
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	अगर (!(map_get_sys_perms(map, f) & FMODE_CAN_WRITE)) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	अगर ((attr->flags & BPF_F_LOCK) &&
	    !map_value_has_spin_lock(map)) अणु
		err = -EINVAL;
		जाओ err_put;
	पूर्ण

	key = __bpf_copy_key(ukey, map->key_size);
	अगर (IS_ERR(key)) अणु
		err = PTR_ERR(key);
		जाओ err_put;
	पूर्ण

	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_PERCPU_ARRAY ||
	    map->map_type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE)
		value_size = round_up(map->value_size, 8) * num_possible_cpus();
	अन्यथा
		value_size = map->value_size;

	err = -ENOMEM;
	value = kदो_स्मृति(value_size, GFP_USER | __GFP_NOWARN);
	अगर (!value)
		जाओ मुक्त_key;

	err = -EFAULT;
	अगर (copy_from_user(value, uvalue, value_size) != 0)
		जाओ मुक्त_value;

	err = bpf_map_update_value(map, f, key, value, attr->flags);

मुक्त_value:
	kमुक्त(value);
मुक्त_key:
	kमुक्त(key);
err_put:
	fdput(f);
	वापस err;
पूर्ण

#घोषणा BPF_MAP_DELETE_ELEM_LAST_FIELD key

अटल पूर्णांक map_delete_elem(जोड़ bpf_attr *attr)
अणु
	व्योम __user *ukey = u64_to_user_ptr(attr->key);
	पूर्णांक ufd = attr->map_fd;
	काष्ठा bpf_map *map;
	काष्ठा fd f;
	व्योम *key;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_MAP_DELETE_ELEM))
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	अगर (!(map_get_sys_perms(map, f) & FMODE_CAN_WRITE)) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	key = __bpf_copy_key(ukey, map->key_size);
	अगर (IS_ERR(key)) अणु
		err = PTR_ERR(key);
		जाओ err_put;
	पूर्ण

	अगर (bpf_map_is_dev_bound(map)) अणु
		err = bpf_map_offload_delete_elem(map, key);
		जाओ out;
	पूर्ण अन्यथा अगर (IS_FD_PROG_ARRAY(map) ||
		   map->map_type == BPF_MAP_TYPE_STRUCT_OPS) अणु
		/* These maps require sleepable context */
		err = map->ops->map_delete_elem(map, key);
		जाओ out;
	पूर्ण

	bpf_disable_instrumentation();
	rcu_पढ़ो_lock();
	err = map->ops->map_delete_elem(map, key);
	rcu_पढ़ो_unlock();
	bpf_enable_instrumentation();
	maybe_रुको_bpf_programs(map);
out:
	kमुक्त(key);
err_put:
	fdput(f);
	वापस err;
पूर्ण

/* last field in 'union bpf_attr' used by this command */
#घोषणा BPF_MAP_GET_NEXT_KEY_LAST_FIELD next_key

अटल पूर्णांक map_get_next_key(जोड़ bpf_attr *attr)
अणु
	व्योम __user *ukey = u64_to_user_ptr(attr->key);
	व्योम __user *unext_key = u64_to_user_ptr(attr->next_key);
	पूर्णांक ufd = attr->map_fd;
	काष्ठा bpf_map *map;
	व्योम *key, *next_key;
	काष्ठा fd f;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_MAP_GET_NEXT_KEY))
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	अगर (!(map_get_sys_perms(map, f) & FMODE_CAN_READ)) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	अगर (ukey) अणु
		key = __bpf_copy_key(ukey, map->key_size);
		अगर (IS_ERR(key)) अणु
			err = PTR_ERR(key);
			जाओ err_put;
		पूर्ण
	पूर्ण अन्यथा अणु
		key = शून्य;
	पूर्ण

	err = -ENOMEM;
	next_key = kदो_स्मृति(map->key_size, GFP_USER);
	अगर (!next_key)
		जाओ मुक्त_key;

	अगर (bpf_map_is_dev_bound(map)) अणु
		err = bpf_map_offload_get_next_key(map, key, next_key);
		जाओ out;
	पूर्ण

	rcu_पढ़ो_lock();
	err = map->ops->map_get_next_key(map, key, next_key);
	rcu_पढ़ो_unlock();
out:
	अगर (err)
		जाओ मुक्त_next_key;

	err = -EFAULT;
	अगर (copy_to_user(unext_key, next_key, map->key_size) != 0)
		जाओ मुक्त_next_key;

	err = 0;

मुक्त_next_key:
	kमुक्त(next_key);
मुक्त_key:
	kमुक्त(key);
err_put:
	fdput(f);
	वापस err;
पूर्ण

पूर्णांक generic_map_delete_batch(काष्ठा bpf_map *map,
			     स्थिर जोड़ bpf_attr *attr,
			     जोड़ bpf_attr __user *uattr)
अणु
	व्योम __user *keys = u64_to_user_ptr(attr->batch.keys);
	u32 cp, max_count;
	पूर्णांक err = 0;
	व्योम *key;

	अगर (attr->batch.elem_flags & ~BPF_F_LOCK)
		वापस -EINVAL;

	अगर ((attr->batch.elem_flags & BPF_F_LOCK) &&
	    !map_value_has_spin_lock(map)) अणु
		वापस -EINVAL;
	पूर्ण

	max_count = attr->batch.count;
	अगर (!max_count)
		वापस 0;

	key = kदो_स्मृति(map->key_size, GFP_USER | __GFP_NOWARN);
	अगर (!key)
		वापस -ENOMEM;

	क्रम (cp = 0; cp < max_count; cp++) अणु
		err = -EFAULT;
		अगर (copy_from_user(key, keys + cp * map->key_size,
				   map->key_size))
			अवरोध;

		अगर (bpf_map_is_dev_bound(map)) अणु
			err = bpf_map_offload_delete_elem(map, key);
			अवरोध;
		पूर्ण

		bpf_disable_instrumentation();
		rcu_पढ़ो_lock();
		err = map->ops->map_delete_elem(map, key);
		rcu_पढ़ो_unlock();
		bpf_enable_instrumentation();
		maybe_रुको_bpf_programs(map);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (copy_to_user(&uattr->batch.count, &cp, माप(cp)))
		err = -EFAULT;

	kमुक्त(key);
	वापस err;
पूर्ण

पूर्णांक generic_map_update_batch(काष्ठा bpf_map *map,
			     स्थिर जोड़ bpf_attr *attr,
			     जोड़ bpf_attr __user *uattr)
अणु
	व्योम __user *values = u64_to_user_ptr(attr->batch.values);
	व्योम __user *keys = u64_to_user_ptr(attr->batch.keys);
	u32 value_size, cp, max_count;
	पूर्णांक ufd = attr->map_fd;
	व्योम *key, *value;
	काष्ठा fd f;
	पूर्णांक err = 0;

	f = fdget(ufd);
	अगर (attr->batch.elem_flags & ~BPF_F_LOCK)
		वापस -EINVAL;

	अगर ((attr->batch.elem_flags & BPF_F_LOCK) &&
	    !map_value_has_spin_lock(map)) अणु
		वापस -EINVAL;
	पूर्ण

	value_size = bpf_map_value_size(map);

	max_count = attr->batch.count;
	अगर (!max_count)
		वापस 0;

	key = kदो_स्मृति(map->key_size, GFP_USER | __GFP_NOWARN);
	अगर (!key)
		वापस -ENOMEM;

	value = kदो_स्मृति(value_size, GFP_USER | __GFP_NOWARN);
	अगर (!value) अणु
		kमुक्त(key);
		वापस -ENOMEM;
	पूर्ण

	क्रम (cp = 0; cp < max_count; cp++) अणु
		err = -EFAULT;
		अगर (copy_from_user(key, keys + cp * map->key_size,
		    map->key_size) ||
		    copy_from_user(value, values + cp * value_size, value_size))
			अवरोध;

		err = bpf_map_update_value(map, f, key, value,
					   attr->batch.elem_flags);

		अगर (err)
			अवरोध;
	पूर्ण

	अगर (copy_to_user(&uattr->batch.count, &cp, माप(cp)))
		err = -EFAULT;

	kमुक्त(value);
	kमुक्त(key);
	वापस err;
पूर्ण

#घोषणा MAP_LOOKUP_RETRIES 3

पूर्णांक generic_map_lookup_batch(काष्ठा bpf_map *map,
				    स्थिर जोड़ bpf_attr *attr,
				    जोड़ bpf_attr __user *uattr)
अणु
	व्योम __user *uobatch = u64_to_user_ptr(attr->batch.out_batch);
	व्योम __user *ubatch = u64_to_user_ptr(attr->batch.in_batch);
	व्योम __user *values = u64_to_user_ptr(attr->batch.values);
	व्योम __user *keys = u64_to_user_ptr(attr->batch.keys);
	व्योम *buf, *buf_prevkey, *prev_key, *key, *value;
	पूर्णांक err, retry = MAP_LOOKUP_RETRIES;
	u32 value_size, cp, max_count;

	अगर (attr->batch.elem_flags & ~BPF_F_LOCK)
		वापस -EINVAL;

	अगर ((attr->batch.elem_flags & BPF_F_LOCK) &&
	    !map_value_has_spin_lock(map))
		वापस -EINVAL;

	value_size = bpf_map_value_size(map);

	max_count = attr->batch.count;
	अगर (!max_count)
		वापस 0;

	अगर (put_user(0, &uattr->batch.count))
		वापस -EFAULT;

	buf_prevkey = kदो_स्मृति(map->key_size, GFP_USER | __GFP_NOWARN);
	अगर (!buf_prevkey)
		वापस -ENOMEM;

	buf = kदो_स्मृति(map->key_size + value_size, GFP_USER | __GFP_NOWARN);
	अगर (!buf) अणु
		kमुक्त(buf_prevkey);
		वापस -ENOMEM;
	पूर्ण

	err = -EFAULT;
	prev_key = शून्य;
	अगर (ubatch && copy_from_user(buf_prevkey, ubatch, map->key_size))
		जाओ मुक्त_buf;
	key = buf;
	value = key + map->key_size;
	अगर (ubatch)
		prev_key = buf_prevkey;

	क्रम (cp = 0; cp < max_count;) अणु
		rcu_पढ़ो_lock();
		err = map->ops->map_get_next_key(map, prev_key, key);
		rcu_पढ़ो_unlock();
		अगर (err)
			अवरोध;
		err = bpf_map_copy_value(map, key, value,
					 attr->batch.elem_flags);

		अगर (err == -ENOENT) अणु
			अगर (retry) अणु
				retry--;
				जारी;
			पूर्ण
			err = -EINTR;
			अवरोध;
		पूर्ण

		अगर (err)
			जाओ मुक्त_buf;

		अगर (copy_to_user(keys + cp * map->key_size, key,
				 map->key_size)) अणु
			err = -EFAULT;
			जाओ मुक्त_buf;
		पूर्ण
		अगर (copy_to_user(values + cp * value_size, value, value_size)) अणु
			err = -EFAULT;
			जाओ मुक्त_buf;
		पूर्ण

		अगर (!prev_key)
			prev_key = buf_prevkey;

		swap(prev_key, key);
		retry = MAP_LOOKUP_RETRIES;
		cp++;
	पूर्ण

	अगर (err == -EFAULT)
		जाओ मुक्त_buf;

	अगर ((copy_to_user(&uattr->batch.count, &cp, माप(cp)) ||
		    (cp && copy_to_user(uobatch, prev_key, map->key_size))))
		err = -EFAULT;

मुक्त_buf:
	kमुक्त(buf_prevkey);
	kमुक्त(buf);
	वापस err;
पूर्ण

#घोषणा BPF_MAP_LOOKUP_AND_DELETE_ELEM_LAST_FIELD value

अटल पूर्णांक map_lookup_and_delete_elem(जोड़ bpf_attr *attr)
अणु
	व्योम __user *ukey = u64_to_user_ptr(attr->key);
	व्योम __user *uvalue = u64_to_user_ptr(attr->value);
	पूर्णांक ufd = attr->map_fd;
	काष्ठा bpf_map *map;
	व्योम *key, *value;
	u32 value_size;
	काष्ठा fd f;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_MAP_LOOKUP_AND_DELETE_ELEM))
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	अगर (!(map_get_sys_perms(map, f) & FMODE_CAN_READ) ||
	    !(map_get_sys_perms(map, f) & FMODE_CAN_WRITE)) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	key = __bpf_copy_key(ukey, map->key_size);
	अगर (IS_ERR(key)) अणु
		err = PTR_ERR(key);
		जाओ err_put;
	पूर्ण

	value_size = map->value_size;

	err = -ENOMEM;
	value = kदो_स्मृति(value_size, GFP_USER | __GFP_NOWARN);
	अगर (!value)
		जाओ मुक्त_key;

	अगर (map->map_type == BPF_MAP_TYPE_QUEUE ||
	    map->map_type == BPF_MAP_TYPE_STACK) अणु
		err = map->ops->map_pop_elem(map, value);
	पूर्ण अन्यथा अणु
		err = -ENOTSUPP;
	पूर्ण

	अगर (err)
		जाओ मुक्त_value;

	अगर (copy_to_user(uvalue, value, value_size) != 0) अणु
		err = -EFAULT;
		जाओ मुक्त_value;
	पूर्ण

	err = 0;

मुक्त_value:
	kमुक्त(value);
मुक्त_key:
	kमुक्त(key);
err_put:
	fdput(f);
	वापस err;
पूर्ण

#घोषणा BPF_MAP_FREEZE_LAST_FIELD map_fd

अटल पूर्णांक map_मुक्तze(स्थिर जोड़ bpf_attr *attr)
अणु
	पूर्णांक err = 0, ufd = attr->map_fd;
	काष्ठा bpf_map *map;
	काष्ठा fd f;

	अगर (CHECK_ATTR(BPF_MAP_FREEZE))
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	अगर (map->map_type == BPF_MAP_TYPE_STRUCT_OPS) अणु
		fdput(f);
		वापस -ENOTSUPP;
	पूर्ण

	mutex_lock(&map->मुक्तze_mutex);

	अगर (map->ग_लिखोcnt) अणु
		err = -EBUSY;
		जाओ err_put;
	पूर्ण
	अगर (READ_ONCE(map->frozen)) अणु
		err = -EBUSY;
		जाओ err_put;
	पूर्ण
	अगर (!bpf_capable()) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	WRITE_ONCE(map->frozen, true);
err_put:
	mutex_unlock(&map->मुक्तze_mutex);
	fdput(f);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा bpf_prog_ops * स्थिर bpf_prog_types[] = अणु
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type) \
	[_id] = & _name ## _prog_ops,
#घोषणा BPF_MAP_TYPE(_id, _ops)
#घोषणा BPF_LINK_TYPE(_id, _name)
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
#अघोषित BPF_MAP_TYPE
#अघोषित BPF_LINK_TYPE
पूर्ण;

अटल पूर्णांक find_prog_type(क्रमागत bpf_prog_type type, काष्ठा bpf_prog *prog)
अणु
	स्थिर काष्ठा bpf_prog_ops *ops;

	अगर (type >= ARRAY_SIZE(bpf_prog_types))
		वापस -EINVAL;
	type = array_index_nospec(type, ARRAY_SIZE(bpf_prog_types));
	ops = bpf_prog_types[type];
	अगर (!ops)
		वापस -EINVAL;

	अगर (!bpf_prog_is_dev_bound(prog->aux))
		prog->aux->ops = ops;
	अन्यथा
		prog->aux->ops = &bpf_offload_prog_ops;
	prog->type = type;
	वापस 0;
पूर्ण

क्रमागत bpf_audit अणु
	BPF_AUDIT_LOAD,
	BPF_AUDIT_UNLOAD,
	BPF_AUDIT_MAX,
पूर्ण;

अटल स्थिर अक्षर * स्थिर bpf_audit_str[BPF_AUDIT_MAX] = अणु
	[BPF_AUDIT_LOAD]   = "LOAD",
	[BPF_AUDIT_UNLOAD] = "UNLOAD",
पूर्ण;

अटल व्योम bpf_audit_prog(स्थिर काष्ठा bpf_prog *prog, अचिन्हित पूर्णांक op)
अणु
	काष्ठा audit_context *ctx = शून्य;
	काष्ठा audit_buffer *ab;

	अगर (WARN_ON_ONCE(op >= BPF_AUDIT_MAX))
		वापस;
	अगर (audit_enabled == AUDIT_OFF)
		वापस;
	अगर (op == BPF_AUDIT_LOAD)
		ctx = audit_context();
	ab = audit_log_start(ctx, GFP_ATOMIC, AUDIT_BPF);
	अगर (unlikely(!ab))
		वापस;
	audit_log_क्रमmat(ab, "prog-id=%u op=%s",
			 prog->aux->id, bpf_audit_str[op]);
	audit_log_end(ab);
पूर्ण

अटल पूर्णांक bpf_prog_alloc_id(काष्ठा bpf_prog *prog)
अणु
	पूर्णांक id;

	idr_preload(GFP_KERNEL);
	spin_lock_bh(&prog_idr_lock);
	id = idr_alloc_cyclic(&prog_idr, prog, 1, पूर्णांक_उच्च, GFP_ATOMIC);
	अगर (id > 0)
		prog->aux->id = id;
	spin_unlock_bh(&prog_idr_lock);
	idr_preload_end();

	/* id is in [1, पूर्णांक_उच्च) */
	अगर (WARN_ON_ONCE(!id))
		वापस -ENOSPC;

	वापस id > 0 ? 0 : id;
पूर्ण

व्योम bpf_prog_मुक्त_id(काष्ठा bpf_prog *prog, bool करो_idr_lock)
अणु
	/* cBPF to eBPF migrations are currently not in the idr store.
	 * Offloaded programs are हटाओd from the store when their device
	 * disappears - even अगर someone grअसल an fd to them they are unusable,
	 * simply रुकोing क्रम refcnt to drop to be मुक्तd.
	 */
	अगर (!prog->aux->id)
		वापस;

	अगर (करो_idr_lock)
		spin_lock_bh(&prog_idr_lock);
	अन्यथा
		__acquire(&prog_idr_lock);

	idr_हटाओ(&prog_idr, prog->aux->id);
	prog->aux->id = 0;

	अगर (करो_idr_lock)
		spin_unlock_bh(&prog_idr_lock);
	अन्यथा
		__release(&prog_idr_lock);
पूर्ण

अटल व्योम __bpf_prog_put_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_prog_aux *aux = container_of(rcu, काष्ठा bpf_prog_aux, rcu);

	kvमुक्त(aux->func_info);
	kमुक्त(aux->func_info_aux);
	मुक्त_uid(aux->user);
	security_bpf_prog_मुक्त(aux);
	bpf_prog_मुक्त(aux->prog);
पूर्ण

अटल व्योम __bpf_prog_put_noref(काष्ठा bpf_prog *prog, bool deferred)
अणु
	bpf_prog_kallsyms_del_all(prog);
	btf_put(prog->aux->btf);
	kvमुक्त(prog->aux->jited_linfo);
	kvमुक्त(prog->aux->linfo);
	kमुक्त(prog->aux->kfunc_tab);
	अगर (prog->aux->attach_btf)
		btf_put(prog->aux->attach_btf);

	अगर (deferred) अणु
		अगर (prog->aux->sleepable)
			call_rcu_tasks_trace(&prog->aux->rcu, __bpf_prog_put_rcu);
		अन्यथा
			call_rcu(&prog->aux->rcu, __bpf_prog_put_rcu);
	पूर्ण अन्यथा अणु
		__bpf_prog_put_rcu(&prog->aux->rcu);
	पूर्ण
पूर्ण

अटल व्योम __bpf_prog_put(काष्ठा bpf_prog *prog, bool करो_idr_lock)
अणु
	अगर (atomic64_dec_and_test(&prog->aux->refcnt)) अणु
		perf_event_bpf_event(prog, PERF_BPF_EVENT_PROG_UNLOAD, 0);
		bpf_audit_prog(prog, BPF_AUDIT_UNLOAD);
		/* bpf_prog_मुक्त_id() must be called first */
		bpf_prog_मुक्त_id(prog, करो_idr_lock);
		__bpf_prog_put_noref(prog, true);
	पूर्ण
पूर्ण

व्योम bpf_prog_put(काष्ठा bpf_prog *prog)
अणु
	__bpf_prog_put(prog, true);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_put);

अटल पूर्णांक bpf_prog_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा bpf_prog *prog = filp->निजी_data;

	bpf_prog_put(prog);
	वापस 0;
पूर्ण

अटल व्योम bpf_prog_get_stats(स्थिर काष्ठा bpf_prog *prog,
			       काष्ठा bpf_prog_stats *stats)
अणु
	u64 nsecs = 0, cnt = 0, misses = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा bpf_prog_stats *st;
		अचिन्हित पूर्णांक start;
		u64 tnsecs, tcnt, पंचांगisses;

		st = per_cpu_ptr(prog->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&st->syncp);
			tnsecs = st->nsecs;
			tcnt = st->cnt;
			पंचांगisses = st->misses;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&st->syncp, start));
		nsecs += tnsecs;
		cnt += tcnt;
		misses += पंचांगisses;
	पूर्ण
	stats->nsecs = nsecs;
	stats->cnt = cnt;
	stats->misses = misses;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम bpf_prog_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *filp)
अणु
	स्थिर काष्ठा bpf_prog *prog = filp->निजी_data;
	अक्षर prog_tag[माप(prog->tag) * 2 + 1] = अणु पूर्ण;
	काष्ठा bpf_prog_stats stats;

	bpf_prog_get_stats(prog, &stats);
	bin2hex(prog_tag, prog->tag, माप(prog->tag));
	seq_म_लिखो(m,
		   "prog_type:\t%u\n"
		   "prog_jited:\t%u\n"
		   "prog_tag:\t%s\n"
		   "memlock:\t%llu\n"
		   "prog_id:\t%u\n"
		   "run_time_ns:\t%llu\n"
		   "run_cnt:\t%llu\n"
		   "recursion_misses:\t%llu\n",
		   prog->type,
		   prog->jited,
		   prog_tag,
		   prog->pages * 1ULL << PAGE_SHIFT,
		   prog->aux->id,
		   stats.nsecs,
		   stats.cnt,
		   stats.misses);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा file_operations bpf_prog_fops = अणु
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= bpf_prog_show_fdinfo,
#पूर्ण_अगर
	.release	= bpf_prog_release,
	.पढ़ो		= bpf_dummy_पढ़ो,
	.ग_लिखो		= bpf_dummy_ग_लिखो,
पूर्ण;

पूर्णांक bpf_prog_new_fd(काष्ठा bpf_prog *prog)
अणु
	पूर्णांक ret;

	ret = security_bpf_prog(prog);
	अगर (ret < 0)
		वापस ret;

	वापस anon_inode_getfd("bpf-prog", &bpf_prog_fops, prog,
				O_RDWR | O_CLOEXEC);
पूर्ण

अटल काष्ठा bpf_prog *____bpf_prog_get(काष्ठा fd f)
अणु
	अगर (!f.file)
		वापस ERR_PTR(-EBADF);
	अगर (f.file->f_op != &bpf_prog_fops) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस f.file->निजी_data;
पूर्ण

व्योम bpf_prog_add(काष्ठा bpf_prog *prog, पूर्णांक i)
अणु
	atomic64_add(i, &prog->aux->refcnt);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_add);

व्योम bpf_prog_sub(काष्ठा bpf_prog *prog, पूर्णांक i)
अणु
	/* Only to be used क्रम unकरोing previous bpf_prog_add() in some
	 * error path. We still know that another entity in our call
	 * path holds a reference to the program, thus atomic_sub() can
	 * be safely used in such हालs!
	 */
	WARN_ON(atomic64_sub_वापस(i, &prog->aux->refcnt) == 0);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_sub);

व्योम bpf_prog_inc(काष्ठा bpf_prog *prog)
अणु
	atomic64_inc(&prog->aux->refcnt);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_inc);

/* prog_idr_lock should have been held */
काष्ठा bpf_prog *bpf_prog_inc_not_zero(काष्ठा bpf_prog *prog)
अणु
	पूर्णांक refold;

	refold = atomic64_fetch_add_unless(&prog->aux->refcnt, 1, 0);

	अगर (!refold)
		वापस ERR_PTR(-ENOENT);

	वापस prog;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_inc_not_zero);

bool bpf_prog_get_ok(काष्ठा bpf_prog *prog,
			    क्रमागत bpf_prog_type *attach_type, bool attach_drv)
अणु
	/* not an attachment, just a refcount inc, always allow */
	अगर (!attach_type)
		वापस true;

	अगर (prog->type != *attach_type)
		वापस false;
	अगर (bpf_prog_is_dev_bound(prog->aux) && !attach_drv)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा bpf_prog *__bpf_prog_get(u32 ufd, क्रमागत bpf_prog_type *attach_type,
				       bool attach_drv)
अणु
	काष्ठा fd f = fdget(ufd);
	काष्ठा bpf_prog *prog;

	prog = ____bpf_prog_get(f);
	अगर (IS_ERR(prog))
		वापस prog;
	अगर (!bpf_prog_get_ok(prog, attach_type, attach_drv)) अणु
		prog = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	bpf_prog_inc(prog);
out:
	fdput(f);
	वापस prog;
पूर्ण

काष्ठा bpf_prog *bpf_prog_get(u32 ufd)
अणु
	वापस __bpf_prog_get(ufd, शून्य, false);
पूर्ण

काष्ठा bpf_prog *bpf_prog_get_type_dev(u32 ufd, क्रमागत bpf_prog_type type,
				       bool attach_drv)
अणु
	वापस __bpf_prog_get(ufd, &type, attach_drv);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_get_type_dev);

/* Initially all BPF programs could be loaded w/o specअगरying
 * expected_attach_type. Later क्रम some of them specअगरying expected_attach_type
 * at load समय became required so that program could be validated properly.
 * Programs of types that are allowed to be loaded both w/ and w/o (क्रम
 * backward compatibility) expected_attach_type, should have the शेष attach
 * type asचिन्हित to expected_attach_type क्रम the latter हाल, so that it can be
 * validated later at attach समय.
 *
 * bpf_prog_load_fixup_attach_type() sets expected_attach_type in @attr अगर
 * prog type requires it but has some attach types that have to be backward
 * compatible.
 */
अटल व्योम bpf_prog_load_fixup_attach_type(जोड़ bpf_attr *attr)
अणु
	चयन (attr->prog_type) अणु
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
		/* Unक्रमtunately BPF_ATTACH_TYPE_UNSPEC क्रमागतeration करोesn't
		 * exist so checking क्रम non-zero is the way to go here.
		 */
		अगर (!attr->expected_attach_type)
			attr->expected_attach_type =
				BPF_CGROUP_INET_SOCK_CREATE;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
bpf_prog_load_check_attach(क्रमागत bpf_prog_type prog_type,
			   क्रमागत bpf_attach_type expected_attach_type,
			   काष्ठा btf *attach_btf, u32 btf_id,
			   काष्ठा bpf_prog *dst_prog)
अणु
	अगर (btf_id) अणु
		अगर (btf_id > BTF_MAX_TYPE)
			वापस -EINVAL;

		अगर (!attach_btf && !dst_prog)
			वापस -EINVAL;

		चयन (prog_type) अणु
		हाल BPF_PROG_TYPE_TRACING:
		हाल BPF_PROG_TYPE_LSM:
		हाल BPF_PROG_TYPE_STRUCT_OPS:
		हाल BPF_PROG_TYPE_EXT:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (attach_btf && (!btf_id || dst_prog))
		वापस -EINVAL;

	अगर (dst_prog && prog_type != BPF_PROG_TYPE_TRACING &&
	    prog_type != BPF_PROG_TYPE_EXT)
		वापस -EINVAL;

	चयन (prog_type) अणु
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
		चयन (expected_attach_type) अणु
		हाल BPF_CGROUP_INET_SOCK_CREATE:
		हाल BPF_CGROUP_INET_SOCK_RELEASE:
		हाल BPF_CGROUP_INET4_POST_BIND:
		हाल BPF_CGROUP_INET6_POST_BIND:
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		चयन (expected_attach_type) अणु
		हाल BPF_CGROUP_INET4_BIND:
		हाल BPF_CGROUP_INET6_BIND:
		हाल BPF_CGROUP_INET4_CONNECT:
		हाल BPF_CGROUP_INET6_CONNECT:
		हाल BPF_CGROUP_INET4_GETPEERNAME:
		हाल BPF_CGROUP_INET6_GETPEERNAME:
		हाल BPF_CGROUP_INET4_GETSOCKNAME:
		हाल BPF_CGROUP_INET6_GETSOCKNAME:
		हाल BPF_CGROUP_UDP4_SENDMSG:
		हाल BPF_CGROUP_UDP6_SENDMSG:
		हाल BPF_CGROUP_UDP4_RECVMSG:
		हाल BPF_CGROUP_UDP6_RECVMSG:
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल BPF_PROG_TYPE_CGROUP_SKB:
		चयन (expected_attach_type) अणु
		हाल BPF_CGROUP_INET_INGRESS:
		हाल BPF_CGROUP_INET_EGRESS:
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
		चयन (expected_attach_type) अणु
		हाल BPF_CGROUP_SETSOCKOPT:
		हाल BPF_CGROUP_GETSOCKOPT:
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल BPF_PROG_TYPE_SK_LOOKUP:
		अगर (expected_attach_type == BPF_SK_LOOKUP)
			वापस 0;
		वापस -EINVAL;
	हाल BPF_PROG_TYPE_EXT:
		अगर (expected_attach_type)
			वापस -EINVAL;
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool is_net_admin_prog_type(क्रमागत bpf_prog_type prog_type)
अणु
	चयन (prog_type) अणु
	हाल BPF_PROG_TYPE_SCHED_CLS:
	हाल BPF_PROG_TYPE_SCHED_ACT:
	हाल BPF_PROG_TYPE_XDP:
	हाल BPF_PROG_TYPE_LWT_IN:
	हाल BPF_PROG_TYPE_LWT_OUT:
	हाल BPF_PROG_TYPE_LWT_XMIT:
	हाल BPF_PROG_TYPE_LWT_SEG6LOCAL:
	हाल BPF_PROG_TYPE_SK_SKB:
	हाल BPF_PROG_TYPE_SK_MSG:
	हाल BPF_PROG_TYPE_LIRC_MODE2:
	हाल BPF_PROG_TYPE_FLOW_DISSECTOR:
	हाल BPF_PROG_TYPE_CGROUP_DEVICE:
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
	हाल BPF_PROG_TYPE_CGROUP_SYSCTL:
	हाल BPF_PROG_TYPE_SOCK_OPS:
	हाल BPF_PROG_TYPE_EXT: /* extends any prog */
		वापस true;
	हाल BPF_PROG_TYPE_CGROUP_SKB:
		/* always unpriv */
	हाल BPF_PROG_TYPE_SK_REUSEPORT:
		/* equivalent to SOCKET_FILTER. need CAP_BPF only */
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_perfmon_prog_type(क्रमागत bpf_prog_type prog_type)
अणु
	चयन (prog_type) अणु
	हाल BPF_PROG_TYPE_KPROBE:
	हाल BPF_PROG_TYPE_TRACEPOINT:
	हाल BPF_PROG_TYPE_PERF_EVENT:
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT:
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE:
	हाल BPF_PROG_TYPE_TRACING:
	हाल BPF_PROG_TYPE_LSM:
	हाल BPF_PROG_TYPE_STRUCT_OPS: /* has access to काष्ठा sock */
	हाल BPF_PROG_TYPE_EXT: /* extends any prog */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* last field in 'union bpf_attr' used by this command */
#घोषणा	BPF_PROG_LOAD_LAST_FIELD attach_prog_fd

अटल पूर्णांक bpf_prog_load(जोड़ bpf_attr *attr, जोड़ bpf_attr __user *uattr)
अणु
	क्रमागत bpf_prog_type type = attr->prog_type;
	काष्ठा bpf_prog *prog, *dst_prog = शून्य;
	काष्ठा btf *attach_btf = शून्य;
	पूर्णांक err;
	अक्षर license[128];
	bool is_gpl;

	अगर (CHECK_ATTR(BPF_PROG_LOAD))
		वापस -EINVAL;

	अगर (attr->prog_flags & ~(BPF_F_STRICT_ALIGNMENT |
				 BPF_F_ANY_ALIGNMENT |
				 BPF_F_TEST_STATE_FREQ |
				 BPF_F_SLEEPABLE |
				 BPF_F_TEST_RND_HI32))
		वापस -EINVAL;

	अगर (!IS_ENABLED(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) &&
	    (attr->prog_flags & BPF_F_ANY_ALIGNMENT) &&
	    !bpf_capable())
		वापस -EPERM;

	/* copy eBPF program license from user space */
	अगर (म_नकलन_from_user(license, u64_to_user_ptr(attr->license),
			      माप(license) - 1) < 0)
		वापस -EFAULT;
	license[माप(license) - 1] = 0;

	/* eBPF programs must be GPL compatible to use GPL-ed functions */
	is_gpl = license_is_gpl_compatible(license);

	अगर (attr->insn_cnt == 0 ||
	    attr->insn_cnt > (bpf_capable() ? BPF_COMPLEXITY_LIMIT_INSNS : BPF_MAXINSNS))
		वापस -E2BIG;
	अगर (type != BPF_PROG_TYPE_SOCKET_FILTER &&
	    type != BPF_PROG_TYPE_CGROUP_SKB &&
	    !bpf_capable())
		वापस -EPERM;

	अगर (is_net_admin_prog_type(type) && !capable(CAP_NET_ADMIN) && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (is_perfmon_prog_type(type) && !perfmon_capable())
		वापस -EPERM;

	/* attach_prog_fd/attach_btf_obj_fd can specअगरy fd of either bpf_prog
	 * or btf, we need to check which one it is
	 */
	अगर (attr->attach_prog_fd) अणु
		dst_prog = bpf_prog_get(attr->attach_prog_fd);
		अगर (IS_ERR(dst_prog)) अणु
			dst_prog = शून्य;
			attach_btf = btf_get_by_fd(attr->attach_btf_obj_fd);
			अगर (IS_ERR(attach_btf))
				वापस -EINVAL;
			अगर (!btf_is_kernel(attach_btf)) अणु
				/* attaching through specअगरying bpf_prog's BTF
				 * objects directly might be supported eventually
				 */
				btf_put(attach_btf);
				वापस -ENOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (attr->attach_btf_id) अणु
		/* fall back to vmlinux BTF, अगर BTF type ID is specअगरied */
		attach_btf = bpf_get_btf_vmlinux();
		अगर (IS_ERR(attach_btf))
			वापस PTR_ERR(attach_btf);
		अगर (!attach_btf)
			वापस -EINVAL;
		btf_get(attach_btf);
	पूर्ण

	bpf_prog_load_fixup_attach_type(attr);
	अगर (bpf_prog_load_check_attach(type, attr->expected_attach_type,
				       attach_btf, attr->attach_btf_id,
				       dst_prog)) अणु
		अगर (dst_prog)
			bpf_prog_put(dst_prog);
		अगर (attach_btf)
			btf_put(attach_btf);
		वापस -EINVAL;
	पूर्ण

	/* plain bpf_prog allocation */
	prog = bpf_prog_alloc(bpf_prog_size(attr->insn_cnt), GFP_USER);
	अगर (!prog) अणु
		अगर (dst_prog)
			bpf_prog_put(dst_prog);
		अगर (attach_btf)
			btf_put(attach_btf);
		वापस -ENOMEM;
	पूर्ण

	prog->expected_attach_type = attr->expected_attach_type;
	prog->aux->attach_btf = attach_btf;
	prog->aux->attach_btf_id = attr->attach_btf_id;
	prog->aux->dst_prog = dst_prog;
	prog->aux->offload_requested = !!attr->prog_अगरindex;
	prog->aux->sleepable = attr->prog_flags & BPF_F_SLEEPABLE;

	err = security_bpf_prog_alloc(prog->aux);
	अगर (err)
		जाओ मुक्त_prog;

	prog->aux->user = get_current_user();
	prog->len = attr->insn_cnt;

	err = -EFAULT;
	अगर (copy_from_user(prog->insns, u64_to_user_ptr(attr->insns),
			   bpf_prog_insn_size(prog)) != 0)
		जाओ मुक्त_prog_sec;

	prog->orig_prog = शून्य;
	prog->jited = 0;

	atomic64_set(&prog->aux->refcnt, 1);
	prog->gpl_compatible = is_gpl ? 1 : 0;

	अगर (bpf_prog_is_dev_bound(prog->aux)) अणु
		err = bpf_prog_offload_init(prog, attr);
		अगर (err)
			जाओ मुक्त_prog_sec;
	पूर्ण

	/* find program type: socket_filter vs tracing_filter */
	err = find_prog_type(type, prog);
	अगर (err < 0)
		जाओ मुक्त_prog_sec;

	prog->aux->load_समय = kसमय_get_bootसमय_ns();
	err = bpf_obj_name_cpy(prog->aux->name, attr->prog_name,
			       माप(attr->prog_name));
	अगर (err < 0)
		जाओ मुक्त_prog_sec;

	/* run eBPF verअगरier */
	err = bpf_check(&prog, attr, uattr);
	अगर (err < 0)
		जाओ मुक्त_used_maps;

	prog = bpf_prog_select_runसमय(prog, &err);
	अगर (err < 0)
		जाओ मुक्त_used_maps;

	err = bpf_prog_alloc_id(prog);
	अगर (err)
		जाओ मुक्त_used_maps;

	/* Upon success of bpf_prog_alloc_id(), the BPF prog is
	 * effectively खुलाly exposed. However, retrieving via
	 * bpf_prog_get_fd_by_id() will take another reference,
	 * thereक्रमe it cannot be gone underneath us.
	 *
	 * Only क्रम the समय /after/ successful bpf_prog_new_fd()
	 * and beक्रमe वापसing to userspace, we might just hold
	 * one reference and any parallel बंद on that fd could
	 * rip everything out. Hence, below notअगरications must
	 * happen beक्रमe bpf_prog_new_fd().
	 *
	 * Also, any failure handling from this poपूर्णांक onwards must
	 * be using bpf_prog_put() given the program is exposed.
	 */
	bpf_prog_kallsyms_add(prog);
	perf_event_bpf_event(prog, PERF_BPF_EVENT_PROG_LOAD, 0);
	bpf_audit_prog(prog, BPF_AUDIT_LOAD);

	err = bpf_prog_new_fd(prog);
	अगर (err < 0)
		bpf_prog_put(prog);
	वापस err;

मुक्त_used_maps:
	/* In हाल we have subprogs, we need to रुको क्रम a grace
	 * period beक्रमe we can tear करोwn JIT memory since symbols
	 * are alपढ़ोy exposed under kallsyms.
	 */
	__bpf_prog_put_noref(prog, prog->aux->func_cnt);
	वापस err;
मुक्त_prog_sec:
	मुक्त_uid(prog->aux->user);
	security_bpf_prog_मुक्त(prog->aux);
मुक्त_prog:
	अगर (prog->aux->attach_btf)
		btf_put(prog->aux->attach_btf);
	bpf_prog_मुक्त(prog);
	वापस err;
पूर्ण

#घोषणा BPF_OBJ_LAST_FIELD file_flags

अटल पूर्णांक bpf_obj_pin(स्थिर जोड़ bpf_attr *attr)
अणु
	अगर (CHECK_ATTR(BPF_OBJ) || attr->file_flags != 0)
		वापस -EINVAL;

	वापस bpf_obj_pin_user(attr->bpf_fd, u64_to_user_ptr(attr->pathname));
पूर्ण

अटल पूर्णांक bpf_obj_get(स्थिर जोड़ bpf_attr *attr)
अणु
	अगर (CHECK_ATTR(BPF_OBJ) || attr->bpf_fd != 0 ||
	    attr->file_flags & ~BPF_OBJ_FLAG_MASK)
		वापस -EINVAL;

	वापस bpf_obj_get_user(u64_to_user_ptr(attr->pathname),
				attr->file_flags);
पूर्ण

व्योम bpf_link_init(काष्ठा bpf_link *link, क्रमागत bpf_link_type type,
		   स्थिर काष्ठा bpf_link_ops *ops, काष्ठा bpf_prog *prog)
अणु
	atomic64_set(&link->refcnt, 1);
	link->type = type;
	link->id = 0;
	link->ops = ops;
	link->prog = prog;
पूर्ण

अटल व्योम bpf_link_मुक्त_id(पूर्णांक id)
अणु
	अगर (!id)
		वापस;

	spin_lock_bh(&link_idr_lock);
	idr_हटाओ(&link_idr, id);
	spin_unlock_bh(&link_idr_lock);
पूर्ण

/* Clean up bpf_link and corresponding anon_inode file and FD. After
 * anon_inode is created, bpf_link can't be just kfree()'d due to deferred
 * anon_inode's release() call. This helper marksbpf_link as
 * defunct, releases anon_inode file and माला_दो reserved FD. bpf_prog's refcnt
 * is not decremented, it's the responsibility of a calling code that failed
 * to complete bpf_link initialization.
 */
व्योम bpf_link_cleanup(काष्ठा bpf_link_primer *primer)
अणु
	primer->link->prog = शून्य;
	bpf_link_मुक्त_id(primer->id);
	fput(primer->file);
	put_unused_fd(primer->fd);
पूर्ण

व्योम bpf_link_inc(काष्ठा bpf_link *link)
अणु
	atomic64_inc(&link->refcnt);
पूर्ण

/* bpf_link_मुक्त is guaranteed to be called from process context */
अटल व्योम bpf_link_मुक्त(काष्ठा bpf_link *link)
अणु
	bpf_link_मुक्त_id(link->id);
	अगर (link->prog) अणु
		/* detach BPF program, clean up used resources */
		link->ops->release(link);
		bpf_prog_put(link->prog);
	पूर्ण
	/* मुक्त bpf_link and its containing memory */
	link->ops->dealloc(link);
पूर्ण

अटल व्योम bpf_link_put_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bpf_link *link = container_of(work, काष्ठा bpf_link, work);

	bpf_link_मुक्त(link);
पूर्ण

/* bpf_link_put can be called from atomic context, but ensures that resources
 * are मुक्तd from process context
 */
व्योम bpf_link_put(काष्ठा bpf_link *link)
अणु
	अगर (!atomic64_dec_and_test(&link->refcnt))
		वापस;

	अगर (in_atomic()) अणु
		INIT_WORK(&link->work, bpf_link_put_deferred);
		schedule_work(&link->work);
	पूर्ण अन्यथा अणु
		bpf_link_मुक्त(link);
	पूर्ण
पूर्ण

अटल पूर्णांक bpf_link_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा bpf_link *link = filp->निजी_data;

	bpf_link_put(link);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type)
#घोषणा BPF_MAP_TYPE(_id, _ops)
#घोषणा BPF_LINK_TYPE(_id, _name) [_id] = #_name,
अटल स्थिर अक्षर *bpf_link_type_strs[] = अणु
	[BPF_LINK_TYPE_UNSPEC] = "<invalid>",
#समावेश <linux/bpf_types.h>
पूर्ण;
#अघोषित BPF_PROG_TYPE
#अघोषित BPF_MAP_TYPE
#अघोषित BPF_LINK_TYPE

अटल व्योम bpf_link_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *filp)
अणु
	स्थिर काष्ठा bpf_link *link = filp->निजी_data;
	स्थिर काष्ठा bpf_prog *prog = link->prog;
	अक्षर prog_tag[माप(prog->tag) * 2 + 1] = अणु पूर्ण;

	bin2hex(prog_tag, prog->tag, माप(prog->tag));
	seq_म_लिखो(m,
		   "link_type:\t%s\n"
		   "link_id:\t%u\n"
		   "prog_tag:\t%s\n"
		   "prog_id:\t%u\n",
		   bpf_link_type_strs[link->type],
		   link->id,
		   prog_tag,
		   prog->aux->id);
	अगर (link->ops->show_fdinfo)
		link->ops->show_fdinfo(link, m);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations bpf_link_fops = अणु
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= bpf_link_show_fdinfo,
#पूर्ण_अगर
	.release	= bpf_link_release,
	.पढ़ो		= bpf_dummy_पढ़ो,
	.ग_लिखो		= bpf_dummy_ग_लिखो,
पूर्ण;

अटल पूर्णांक bpf_link_alloc_id(काष्ठा bpf_link *link)
अणु
	पूर्णांक id;

	idr_preload(GFP_KERNEL);
	spin_lock_bh(&link_idr_lock);
	id = idr_alloc_cyclic(&link_idr, link, 1, पूर्णांक_उच्च, GFP_ATOMIC);
	spin_unlock_bh(&link_idr_lock);
	idr_preload_end();

	वापस id;
पूर्ण

/* Prepare bpf_link to be exposed to user-space by allocating anon_inode file,
 * reserving unused FD and allocating ID from link_idr. This is to be paired
 * with bpf_link_settle() to install FD and ID and expose bpf_link to
 * user-space, अगर bpf_link is successfully attached. If not, bpf_link and
 * pre-allocated resources are to be मुक्तd with bpf_cleanup() call. All the
 * transient state is passed around in काष्ठा bpf_link_primer.
 * This is preferred way to create and initialize bpf_link, especially when
 * there are complicated and expensive operations inbetween creating bpf_link
 * itself and attaching it to BPF hook. By using bpf_link_prime() and
 * bpf_link_settle() kernel code using bpf_link करोesn't have to perक्रमm
 * expensive (and potentially failing) roll back operations in a rare हाल
 * that file, FD, or ID can't be allocated.
 */
पूर्णांक bpf_link_prime(काष्ठा bpf_link *link, काष्ठा bpf_link_primer *primer)
अणु
	काष्ठा file *file;
	पूर्णांक fd, id;

	fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (fd < 0)
		वापस fd;


	id = bpf_link_alloc_id(link);
	अगर (id < 0) अणु
		put_unused_fd(fd);
		वापस id;
	पूर्ण

	file = anon_inode_getfile("bpf_link", &bpf_link_fops, link, O_CLOEXEC);
	अगर (IS_ERR(file)) अणु
		bpf_link_मुक्त_id(id);
		put_unused_fd(fd);
		वापस PTR_ERR(file);
	पूर्ण

	primer->link = link;
	primer->file = file;
	primer->fd = fd;
	primer->id = id;
	वापस 0;
पूर्ण

पूर्णांक bpf_link_settle(काष्ठा bpf_link_primer *primer)
अणु
	/* make bpf_link fetchable by ID */
	spin_lock_bh(&link_idr_lock);
	primer->link->id = primer->id;
	spin_unlock_bh(&link_idr_lock);
	/* make bpf_link fetchable by FD */
	fd_install(primer->fd, primer->file);
	/* pass through installed FD */
	वापस primer->fd;
पूर्ण

पूर्णांक bpf_link_new_fd(काष्ठा bpf_link *link)
अणु
	वापस anon_inode_getfd("bpf-link", &bpf_link_fops, link, O_CLOEXEC);
पूर्ण

काष्ठा bpf_link *bpf_link_get_from_fd(u32 ufd)
अणु
	काष्ठा fd f = fdget(ufd);
	काष्ठा bpf_link *link;

	अगर (!f.file)
		वापस ERR_PTR(-EBADF);
	अगर (f.file->f_op != &bpf_link_fops) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	link = f.file->निजी_data;
	bpf_link_inc(link);
	fdput(f);

	वापस link;
पूर्ण

काष्ठा bpf_tracing_link अणु
	काष्ठा bpf_link link;
	क्रमागत bpf_attach_type attach_type;
	काष्ठा bpf_trampoline *trampoline;
	काष्ठा bpf_prog *tgt_prog;
पूर्ण;

अटल व्योम bpf_tracing_link_release(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_tracing_link *tr_link =
		container_of(link, काष्ठा bpf_tracing_link, link);

	WARN_ON_ONCE(bpf_trampoline_unlink_prog(link->prog,
						tr_link->trampoline));

	bpf_trampoline_put(tr_link->trampoline);

	/* tgt_prog is शून्य अगर target is a kernel function */
	अगर (tr_link->tgt_prog)
		bpf_prog_put(tr_link->tgt_prog);
पूर्ण

अटल व्योम bpf_tracing_link_dealloc(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_tracing_link *tr_link =
		container_of(link, काष्ठा bpf_tracing_link, link);

	kमुक्त(tr_link);
पूर्ण

अटल व्योम bpf_tracing_link_show_fdinfo(स्थिर काष्ठा bpf_link *link,
					 काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_tracing_link *tr_link =
		container_of(link, काष्ठा bpf_tracing_link, link);

	seq_म_लिखो(seq,
		   "attach_type:\t%d\n",
		   tr_link->attach_type);
पूर्ण

अटल पूर्णांक bpf_tracing_link_fill_link_info(स्थिर काष्ठा bpf_link *link,
					   काष्ठा bpf_link_info *info)
अणु
	काष्ठा bpf_tracing_link *tr_link =
		container_of(link, काष्ठा bpf_tracing_link, link);

	info->tracing.attach_type = tr_link->attach_type;
	bpf_trampoline_unpack_key(tr_link->trampoline->key,
				  &info->tracing.target_obj_id,
				  &info->tracing.target_btf_id);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_link_ops bpf_tracing_link_lops = अणु
	.release = bpf_tracing_link_release,
	.dealloc = bpf_tracing_link_dealloc,
	.show_fdinfo = bpf_tracing_link_show_fdinfo,
	.fill_link_info = bpf_tracing_link_fill_link_info,
पूर्ण;

अटल पूर्णांक bpf_tracing_prog_attach(काष्ठा bpf_prog *prog,
				   पूर्णांक tgt_prog_fd,
				   u32 btf_id)
अणु
	काष्ठा bpf_link_primer link_primer;
	काष्ठा bpf_prog *tgt_prog = शून्य;
	काष्ठा bpf_trampoline *tr = शून्य;
	काष्ठा bpf_tracing_link *link;
	u64 key = 0;
	पूर्णांक err;

	चयन (prog->type) अणु
	हाल BPF_PROG_TYPE_TRACING:
		अगर (prog->expected_attach_type != BPF_TRACE_FENTRY &&
		    prog->expected_attach_type != BPF_TRACE_FEXIT &&
		    prog->expected_attach_type != BPF_MODIFY_RETURN) अणु
			err = -EINVAL;
			जाओ out_put_prog;
		पूर्ण
		अवरोध;
	हाल BPF_PROG_TYPE_EXT:
		अगर (prog->expected_attach_type != 0) अणु
			err = -EINVAL;
			जाओ out_put_prog;
		पूर्ण
		अवरोध;
	हाल BPF_PROG_TYPE_LSM:
		अगर (prog->expected_attach_type != BPF_LSM_MAC) अणु
			err = -EINVAL;
			जाओ out_put_prog;
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out_put_prog;
	पूर्ण

	अगर (!!tgt_prog_fd != !!btf_id) अणु
		err = -EINVAL;
		जाओ out_put_prog;
	पूर्ण

	अगर (tgt_prog_fd) अणु
		/* For now we only allow new tarमाला_लो क्रम BPF_PROG_TYPE_EXT */
		अगर (prog->type != BPF_PROG_TYPE_EXT) अणु
			err = -EINVAL;
			जाओ out_put_prog;
		पूर्ण

		tgt_prog = bpf_prog_get(tgt_prog_fd);
		अगर (IS_ERR(tgt_prog)) अणु
			err = PTR_ERR(tgt_prog);
			tgt_prog = शून्य;
			जाओ out_put_prog;
		पूर्ण

		key = bpf_trampoline_compute_key(tgt_prog, शून्य, btf_id);
	पूर्ण

	link = kzalloc(माप(*link), GFP_USER);
	अगर (!link) अणु
		err = -ENOMEM;
		जाओ out_put_prog;
	पूर्ण
	bpf_link_init(&link->link, BPF_LINK_TYPE_TRACING,
		      &bpf_tracing_link_lops, prog);
	link->attach_type = prog->expected_attach_type;

	mutex_lock(&prog->aux->dst_mutex);

	/* There are a few possible हालs here:
	 *
	 * - अगर prog->aux->dst_trampoline is set, the program was just loaded
	 *   and not yet attached to anything, so we can use the values stored
	 *   in prog->aux
	 *
	 * - अगर prog->aux->dst_trampoline is शून्य, the program has alपढ़ोy been
         *   attached to a target and its initial target was cleared (below)
	 *
	 * - अगर tgt_prog != शून्य, the caller specअगरied tgt_prog_fd +
	 *   target_btf_id using the link_create API.
	 *
	 * - अगर tgt_prog == शून्य when this function was called using the old
	 *   raw_tracepoपूर्णांक_खोलो API, and we need a target from prog->aux
	 *
	 * - अगर prog->aux->dst_trampoline and tgt_prog is शून्य, the program
	 *   was detached and is going क्रम re-attachment.
	 */
	अगर (!prog->aux->dst_trampoline && !tgt_prog) अणु
		/*
		 * Allow re-attach क्रम TRACING and LSM programs. If it's
		 * currently linked, bpf_trampoline_link_prog will fail.
		 * EXT programs need to specअगरy tgt_prog_fd, so they
		 * re-attach in separate code path.
		 */
		अगर (prog->type != BPF_PROG_TYPE_TRACING &&
		    prog->type != BPF_PROG_TYPE_LSM) अणु
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		btf_id = prog->aux->attach_btf_id;
		key = bpf_trampoline_compute_key(शून्य, prog->aux->attach_btf, btf_id);
	पूर्ण

	अगर (!prog->aux->dst_trampoline ||
	    (key && key != prog->aux->dst_trampoline->key)) अणु
		/* If there is no saved target, or the specअगरied target is
		 * dअगरferent from the destination specअगरied at load समय, we
		 * need a new trampoline and a check क्रम compatibility
		 */
		काष्ठा bpf_attach_target_info tgt_info = अणुपूर्ण;

		err = bpf_check_attach_target(शून्य, prog, tgt_prog, btf_id,
					      &tgt_info);
		अगर (err)
			जाओ out_unlock;

		tr = bpf_trampoline_get(key, &tgt_info);
		अगर (!tr) अणु
			err = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The caller didn't specअगरy a target, or the target was the
		 * same as the destination supplied during program load. This
		 * means we can reuse the trampoline and reference from program
		 * load समय, and there is no need to allocate a new one. This
		 * can only happen once क्रम any program, as the saved values in
		 * prog->aux are cleared below.
		 */
		tr = prog->aux->dst_trampoline;
		tgt_prog = prog->aux->dst_prog;
	पूर्ण

	err = bpf_link_prime(&link->link, &link_primer);
	अगर (err)
		जाओ out_unlock;

	err = bpf_trampoline_link_prog(prog, tr);
	अगर (err) अणु
		bpf_link_cleanup(&link_primer);
		link = शून्य;
		जाओ out_unlock;
	पूर्ण

	link->tgt_prog = tgt_prog;
	link->trampoline = tr;

	/* Always clear the trampoline and target prog from prog->aux to make
	 * sure the original attach destination is not kept alive after a
	 * program is (re-)attached to another target.
	 */
	अगर (prog->aux->dst_prog &&
	    (tgt_prog_fd || tr != prog->aux->dst_trampoline))
		/* got extra prog ref from syscall, or attaching to dअगरferent prog */
		bpf_prog_put(prog->aux->dst_prog);
	अगर (prog->aux->dst_trampoline && tr != prog->aux->dst_trampoline)
		/* we allocated a new trampoline, so मुक्त the old one */
		bpf_trampoline_put(prog->aux->dst_trampoline);

	prog->aux->dst_prog = शून्य;
	prog->aux->dst_trampoline = शून्य;
	mutex_unlock(&prog->aux->dst_mutex);

	वापस bpf_link_settle(&link_primer);
out_unlock:
	अगर (tr && tr != prog->aux->dst_trampoline)
		bpf_trampoline_put(tr);
	mutex_unlock(&prog->aux->dst_mutex);
	kमुक्त(link);
out_put_prog:
	अगर (tgt_prog_fd && tgt_prog)
		bpf_prog_put(tgt_prog);
	वापस err;
पूर्ण

काष्ठा bpf_raw_tp_link अणु
	काष्ठा bpf_link link;
	काष्ठा bpf_raw_event_map *btp;
पूर्ण;

अटल व्योम bpf_raw_tp_link_release(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_raw_tp_link *raw_tp =
		container_of(link, काष्ठा bpf_raw_tp_link, link);

	bpf_probe_unरेजिस्टर(raw_tp->btp, raw_tp->link.prog);
	bpf_put_raw_tracepoपूर्णांक(raw_tp->btp);
पूर्ण

अटल व्योम bpf_raw_tp_link_dealloc(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_raw_tp_link *raw_tp =
		container_of(link, काष्ठा bpf_raw_tp_link, link);

	kमुक्त(raw_tp);
पूर्ण

अटल व्योम bpf_raw_tp_link_show_fdinfo(स्थिर काष्ठा bpf_link *link,
					काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_raw_tp_link *raw_tp_link =
		container_of(link, काष्ठा bpf_raw_tp_link, link);

	seq_म_लिखो(seq,
		   "tp_name:\t%s\n",
		   raw_tp_link->btp->tp->name);
पूर्ण

अटल पूर्णांक bpf_raw_tp_link_fill_link_info(स्थिर काष्ठा bpf_link *link,
					  काष्ठा bpf_link_info *info)
अणु
	काष्ठा bpf_raw_tp_link *raw_tp_link =
		container_of(link, काष्ठा bpf_raw_tp_link, link);
	अक्षर __user *ubuf = u64_to_user_ptr(info->raw_tracepoपूर्णांक.tp_name);
	स्थिर अक्षर *tp_name = raw_tp_link->btp->tp->name;
	u32 ulen = info->raw_tracepoपूर्णांक.tp_name_len;
	माप_प्रकार tp_len = म_माप(tp_name);

	अगर (!ulen ^ !ubuf)
		वापस -EINVAL;

	info->raw_tracepoपूर्णांक.tp_name_len = tp_len + 1;

	अगर (!ubuf)
		वापस 0;

	अगर (ulen >= tp_len + 1) अणु
		अगर (copy_to_user(ubuf, tp_name, tp_len + 1))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अक्षर zero = '\0';

		अगर (copy_to_user(ubuf, tp_name, ulen - 1))
			वापस -EFAULT;
		अगर (put_user(zero, ubuf + ulen - 1))
			वापस -EFAULT;
		वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_link_ops bpf_raw_tp_link_lops = अणु
	.release = bpf_raw_tp_link_release,
	.dealloc = bpf_raw_tp_link_dealloc,
	.show_fdinfo = bpf_raw_tp_link_show_fdinfo,
	.fill_link_info = bpf_raw_tp_link_fill_link_info,
पूर्ण;

#घोषणा BPF_RAW_TRACEPOINT_OPEN_LAST_FIELD raw_tracepoपूर्णांक.prog_fd

अटल पूर्णांक bpf_raw_tracepoपूर्णांक_खोलो(स्थिर जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_link_primer link_primer;
	काष्ठा bpf_raw_tp_link *link;
	काष्ठा bpf_raw_event_map *btp;
	काष्ठा bpf_prog *prog;
	स्थिर अक्षर *tp_name;
	अक्षर buf[128];
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_RAW_TRACEPOINT_OPEN))
		वापस -EINVAL;

	prog = bpf_prog_get(attr->raw_tracepoपूर्णांक.prog_fd);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	चयन (prog->type) अणु
	हाल BPF_PROG_TYPE_TRACING:
	हाल BPF_PROG_TYPE_EXT:
	हाल BPF_PROG_TYPE_LSM:
		अगर (attr->raw_tracepoपूर्णांक.name) अणु
			/* The attach poपूर्णांक क्रम this category of programs
			 * should be specअगरied via btf_id during program load.
			 */
			err = -EINVAL;
			जाओ out_put_prog;
		पूर्ण
		अगर (prog->type == BPF_PROG_TYPE_TRACING &&
		    prog->expected_attach_type == BPF_TRACE_RAW_TP) अणु
			tp_name = prog->aux->attach_func_name;
			अवरोध;
		पूर्ण
		err = bpf_tracing_prog_attach(prog, 0, 0);
		अगर (err >= 0)
			वापस err;
		जाओ out_put_prog;
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT:
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE:
		अगर (म_नकलन_from_user(buf,
				      u64_to_user_ptr(attr->raw_tracepoपूर्णांक.name),
				      माप(buf) - 1) < 0) अणु
			err = -EFAULT;
			जाओ out_put_prog;
		पूर्ण
		buf[माप(buf) - 1] = 0;
		tp_name = buf;
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out_put_prog;
	पूर्ण

	btp = bpf_get_raw_tracepoपूर्णांक(tp_name);
	अगर (!btp) अणु
		err = -ENOENT;
		जाओ out_put_prog;
	पूर्ण

	link = kzalloc(माप(*link), GFP_USER);
	अगर (!link) अणु
		err = -ENOMEM;
		जाओ out_put_btp;
	पूर्ण
	bpf_link_init(&link->link, BPF_LINK_TYPE_RAW_TRACEPOINT,
		      &bpf_raw_tp_link_lops, prog);
	link->btp = btp;

	err = bpf_link_prime(&link->link, &link_primer);
	अगर (err) अणु
		kमुक्त(link);
		जाओ out_put_btp;
	पूर्ण

	err = bpf_probe_रेजिस्टर(link->btp, prog);
	अगर (err) अणु
		bpf_link_cleanup(&link_primer);
		जाओ out_put_btp;
	पूर्ण

	वापस bpf_link_settle(&link_primer);

out_put_btp:
	bpf_put_raw_tracepoपूर्णांक(btp);
out_put_prog:
	bpf_prog_put(prog);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_prog_attach_check_attach_type(स्थिर काष्ठा bpf_prog *prog,
					     क्रमागत bpf_attach_type attach_type)
अणु
	चयन (prog->type) अणु
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
	हाल BPF_PROG_TYPE_SK_LOOKUP:
		वापस attach_type == prog->expected_attach_type ? 0 : -EINVAL;
	हाल BPF_PROG_TYPE_CGROUP_SKB:
		अगर (!capable(CAP_NET_ADMIN))
			/* cg-skb progs can be loaded by unpriv user.
			 * check permissions at attach समय.
			 */
			वापस -EPERM;
		वापस prog->enक्रमce_expected_attach_type &&
			prog->expected_attach_type != attach_type ?
			-EINVAL : 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल क्रमागत bpf_prog_type
attach_type_to_prog_type(क्रमागत bpf_attach_type attach_type)
अणु
	चयन (attach_type) अणु
	हाल BPF_CGROUP_INET_INGRESS:
	हाल BPF_CGROUP_INET_EGRESS:
		वापस BPF_PROG_TYPE_CGROUP_SKB;
	हाल BPF_CGROUP_INET_SOCK_CREATE:
	हाल BPF_CGROUP_INET_SOCK_RELEASE:
	हाल BPF_CGROUP_INET4_POST_BIND:
	हाल BPF_CGROUP_INET6_POST_BIND:
		वापस BPF_PROG_TYPE_CGROUP_SOCK;
	हाल BPF_CGROUP_INET4_BIND:
	हाल BPF_CGROUP_INET6_BIND:
	हाल BPF_CGROUP_INET4_CONNECT:
	हाल BPF_CGROUP_INET6_CONNECT:
	हाल BPF_CGROUP_INET4_GETPEERNAME:
	हाल BPF_CGROUP_INET6_GETPEERNAME:
	हाल BPF_CGROUP_INET4_GETSOCKNAME:
	हाल BPF_CGROUP_INET6_GETSOCKNAME:
	हाल BPF_CGROUP_UDP4_SENDMSG:
	हाल BPF_CGROUP_UDP6_SENDMSG:
	हाल BPF_CGROUP_UDP4_RECVMSG:
	हाल BPF_CGROUP_UDP6_RECVMSG:
		वापस BPF_PROG_TYPE_CGROUP_SOCK_ADDR;
	हाल BPF_CGROUP_SOCK_OPS:
		वापस BPF_PROG_TYPE_SOCK_OPS;
	हाल BPF_CGROUP_DEVICE:
		वापस BPF_PROG_TYPE_CGROUP_DEVICE;
	हाल BPF_SK_MSG_VERDICT:
		वापस BPF_PROG_TYPE_SK_MSG;
	हाल BPF_SK_SKB_STREAM_PARSER:
	हाल BPF_SK_SKB_STREAM_VERDICT:
	हाल BPF_SK_SKB_VERDICT:
		वापस BPF_PROG_TYPE_SK_SKB;
	हाल BPF_LIRC_MODE2:
		वापस BPF_PROG_TYPE_LIRC_MODE2;
	हाल BPF_FLOW_DISSECTOR:
		वापस BPF_PROG_TYPE_FLOW_DISSECTOR;
	हाल BPF_CGROUP_SYSCTL:
		वापस BPF_PROG_TYPE_CGROUP_SYSCTL;
	हाल BPF_CGROUP_GETSOCKOPT:
	हाल BPF_CGROUP_SETSOCKOPT:
		वापस BPF_PROG_TYPE_CGROUP_SOCKOPT;
	हाल BPF_TRACE_ITER:
		वापस BPF_PROG_TYPE_TRACING;
	हाल BPF_SK_LOOKUP:
		वापस BPF_PROG_TYPE_SK_LOOKUP;
	हाल BPF_XDP:
		वापस BPF_PROG_TYPE_XDP;
	शेष:
		वापस BPF_PROG_TYPE_UNSPEC;
	पूर्ण
पूर्ण

#घोषणा BPF_PROG_ATTACH_LAST_FIELD replace_bpf_fd

#घोषणा BPF_F_ATTACH_MASK \
	(BPF_F_ALLOW_OVERRIDE | BPF_F_ALLOW_MULTI | BPF_F_REPLACE)

अटल पूर्णांक bpf_prog_attach(स्थिर जोड़ bpf_attr *attr)
अणु
	क्रमागत bpf_prog_type ptype;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret;

	अगर (CHECK_ATTR(BPF_PROG_ATTACH))
		वापस -EINVAL;

	अगर (attr->attach_flags & ~BPF_F_ATTACH_MASK)
		वापस -EINVAL;

	ptype = attach_type_to_prog_type(attr->attach_type);
	अगर (ptype == BPF_PROG_TYPE_UNSPEC)
		वापस -EINVAL;

	prog = bpf_prog_get_type(attr->attach_bpf_fd, ptype);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	अगर (bpf_prog_attach_check_attach_type(prog, attr->attach_type)) अणु
		bpf_prog_put(prog);
		वापस -EINVAL;
	पूर्ण

	चयन (ptype) अणु
	हाल BPF_PROG_TYPE_SK_SKB:
	हाल BPF_PROG_TYPE_SK_MSG:
		ret = sock_map_get_from_fd(attr, prog);
		अवरोध;
	हाल BPF_PROG_TYPE_LIRC_MODE2:
		ret = lirc_prog_attach(attr, prog);
		अवरोध;
	हाल BPF_PROG_TYPE_FLOW_DISSECTOR:
		ret = netns_bpf_prog_attach(attr, prog);
		अवरोध;
	हाल BPF_PROG_TYPE_CGROUP_DEVICE:
	हाल BPF_PROG_TYPE_CGROUP_SKB:
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
	हाल BPF_PROG_TYPE_CGROUP_SYSCTL:
	हाल BPF_PROG_TYPE_SOCK_OPS:
		ret = cgroup_bpf_prog_attach(attr, ptype, prog);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		bpf_prog_put(prog);
	वापस ret;
पूर्ण

#घोषणा BPF_PROG_DETACH_LAST_FIELD attach_type

अटल पूर्णांक bpf_prog_detach(स्थिर जोड़ bpf_attr *attr)
अणु
	क्रमागत bpf_prog_type ptype;

	अगर (CHECK_ATTR(BPF_PROG_DETACH))
		वापस -EINVAL;

	ptype = attach_type_to_prog_type(attr->attach_type);

	चयन (ptype) अणु
	हाल BPF_PROG_TYPE_SK_MSG:
	हाल BPF_PROG_TYPE_SK_SKB:
		वापस sock_map_prog_detach(attr, ptype);
	हाल BPF_PROG_TYPE_LIRC_MODE2:
		वापस lirc_prog_detach(attr);
	हाल BPF_PROG_TYPE_FLOW_DISSECTOR:
		वापस netns_bpf_prog_detach(attr, ptype);
	हाल BPF_PROG_TYPE_CGROUP_DEVICE:
	हाल BPF_PROG_TYPE_CGROUP_SKB:
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
	हाल BPF_PROG_TYPE_CGROUP_SYSCTL:
	हाल BPF_PROG_TYPE_SOCK_OPS:
		वापस cgroup_bpf_prog_detach(attr, ptype);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा BPF_PROG_QUERY_LAST_FIELD query.prog_cnt

अटल पूर्णांक bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
			  जोड़ bpf_attr __user *uattr)
अणु
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (CHECK_ATTR(BPF_PROG_QUERY))
		वापस -EINVAL;
	अगर (attr->query.query_flags & ~BPF_F_QUERY_EFFECTIVE)
		वापस -EINVAL;

	चयन (attr->query.attach_type) अणु
	हाल BPF_CGROUP_INET_INGRESS:
	हाल BPF_CGROUP_INET_EGRESS:
	हाल BPF_CGROUP_INET_SOCK_CREATE:
	हाल BPF_CGROUP_INET_SOCK_RELEASE:
	हाल BPF_CGROUP_INET4_BIND:
	हाल BPF_CGROUP_INET6_BIND:
	हाल BPF_CGROUP_INET4_POST_BIND:
	हाल BPF_CGROUP_INET6_POST_BIND:
	हाल BPF_CGROUP_INET4_CONNECT:
	हाल BPF_CGROUP_INET6_CONNECT:
	हाल BPF_CGROUP_INET4_GETPEERNAME:
	हाल BPF_CGROUP_INET6_GETPEERNAME:
	हाल BPF_CGROUP_INET4_GETSOCKNAME:
	हाल BPF_CGROUP_INET6_GETSOCKNAME:
	हाल BPF_CGROUP_UDP4_SENDMSG:
	हाल BPF_CGROUP_UDP6_SENDMSG:
	हाल BPF_CGROUP_UDP4_RECVMSG:
	हाल BPF_CGROUP_UDP6_RECVMSG:
	हाल BPF_CGROUP_SOCK_OPS:
	हाल BPF_CGROUP_DEVICE:
	हाल BPF_CGROUP_SYSCTL:
	हाल BPF_CGROUP_GETSOCKOPT:
	हाल BPF_CGROUP_SETSOCKOPT:
		वापस cgroup_bpf_prog_query(attr, uattr);
	हाल BPF_LIRC_MODE2:
		वापस lirc_prog_query(attr, uattr);
	हाल BPF_FLOW_DISSECTOR:
	हाल BPF_SK_LOOKUP:
		वापस netns_bpf_prog_query(attr, uattr);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा BPF_PROG_TEST_RUN_LAST_FIELD test.cpu

अटल पूर्णांक bpf_prog_test_run(स्थिर जोड़ bpf_attr *attr,
			     जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = -ENOTSUPP;

	अगर (CHECK_ATTR(BPF_PROG_TEST_RUN))
		वापस -EINVAL;

	अगर ((attr->test.ctx_size_in && !attr->test.ctx_in) ||
	    (!attr->test.ctx_size_in && attr->test.ctx_in))
		वापस -EINVAL;

	अगर ((attr->test.ctx_size_out && !attr->test.ctx_out) ||
	    (!attr->test.ctx_size_out && attr->test.ctx_out))
		वापस -EINVAL;

	prog = bpf_prog_get(attr->test.prog_fd);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	अगर (prog->aux->ops->test_run)
		ret = prog->aux->ops->test_run(prog, attr, uattr);

	bpf_prog_put(prog);
	वापस ret;
पूर्ण

#घोषणा BPF_OBJ_GET_NEXT_ID_LAST_FIELD next_id

अटल पूर्णांक bpf_obj_get_next_id(स्थिर जोड़ bpf_attr *attr,
			       जोड़ bpf_attr __user *uattr,
			       काष्ठा idr *idr,
			       spinlock_t *lock)
अणु
	u32 next_id = attr->start_id;
	पूर्णांक err = 0;

	अगर (CHECK_ATTR(BPF_OBJ_GET_NEXT_ID) || next_id >= पूर्णांक_उच्च)
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	next_id++;
	spin_lock_bh(lock);
	अगर (!idr_get_next(idr, &next_id))
		err = -ENOENT;
	spin_unlock_bh(lock);

	अगर (!err)
		err = put_user(next_id, &uattr->next_id);

	वापस err;
पूर्ण

काष्ठा bpf_map *bpf_map_get_curr_or_next(u32 *id)
अणु
	काष्ठा bpf_map *map;

	spin_lock_bh(&map_idr_lock);
again:
	map = idr_get_next(&map_idr, id);
	अगर (map) अणु
		map = __bpf_map_inc_not_zero(map, false);
		अगर (IS_ERR(map)) अणु
			(*id)++;
			जाओ again;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&map_idr_lock);

	वापस map;
पूर्ण

काष्ठा bpf_prog *bpf_prog_get_curr_or_next(u32 *id)
अणु
	काष्ठा bpf_prog *prog;

	spin_lock_bh(&prog_idr_lock);
again:
	prog = idr_get_next(&prog_idr, id);
	अगर (prog) अणु
		prog = bpf_prog_inc_not_zero(prog);
		अगर (IS_ERR(prog)) अणु
			(*id)++;
			जाओ again;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&prog_idr_lock);

	वापस prog;
पूर्ण

#घोषणा BPF_PROG_GET_FD_BY_ID_LAST_FIELD prog_id

काष्ठा bpf_prog *bpf_prog_by_id(u32 id)
अणु
	काष्ठा bpf_prog *prog;

	अगर (!id)
		वापस ERR_PTR(-ENOENT);

	spin_lock_bh(&prog_idr_lock);
	prog = idr_find(&prog_idr, id);
	अगर (prog)
		prog = bpf_prog_inc_not_zero(prog);
	अन्यथा
		prog = ERR_PTR(-ENOENT);
	spin_unlock_bh(&prog_idr_lock);
	वापस prog;
पूर्ण

अटल पूर्णांक bpf_prog_get_fd_by_id(स्थिर जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_prog *prog;
	u32 id = attr->prog_id;
	पूर्णांक fd;

	अगर (CHECK_ATTR(BPF_PROG_GET_FD_BY_ID))
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	prog = bpf_prog_by_id(id);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	fd = bpf_prog_new_fd(prog);
	अगर (fd < 0)
		bpf_prog_put(prog);

	वापस fd;
पूर्ण

#घोषणा BPF_MAP_GET_FD_BY_ID_LAST_FIELD खोलो_flags

अटल पूर्णांक bpf_map_get_fd_by_id(स्थिर जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_map *map;
	u32 id = attr->map_id;
	पूर्णांक f_flags;
	पूर्णांक fd;

	अगर (CHECK_ATTR(BPF_MAP_GET_FD_BY_ID) ||
	    attr->खोलो_flags & ~BPF_OBJ_FLAG_MASK)
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	f_flags = bpf_get_file_flag(attr->खोलो_flags);
	अगर (f_flags < 0)
		वापस f_flags;

	spin_lock_bh(&map_idr_lock);
	map = idr_find(&map_idr, id);
	अगर (map)
		map = __bpf_map_inc_not_zero(map, true);
	अन्यथा
		map = ERR_PTR(-ENOENT);
	spin_unlock_bh(&map_idr_lock);

	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	fd = bpf_map_new_fd(map, f_flags);
	अगर (fd < 0)
		bpf_map_put_with_uref(map);

	वापस fd;
पूर्ण

अटल स्थिर काष्ठा bpf_map *bpf_map_from_imm(स्थिर काष्ठा bpf_prog *prog,
					      अचिन्हित दीर्घ addr, u32 *off,
					      u32 *type)
अणु
	स्थिर काष्ठा bpf_map *map;
	पूर्णांक i;

	mutex_lock(&prog->aux->used_maps_mutex);
	क्रम (i = 0, *off = 0; i < prog->aux->used_map_cnt; i++) अणु
		map = prog->aux->used_maps[i];
		अगर (map == (व्योम *)addr) अणु
			*type = BPF_PSEUDO_MAP_FD;
			जाओ out;
		पूर्ण
		अगर (!map->ops->map_direct_value_meta)
			जारी;
		अगर (!map->ops->map_direct_value_meta(map, addr, off)) अणु
			*type = BPF_PSEUDO_MAP_VALUE;
			जाओ out;
		पूर्ण
	पूर्ण
	map = शून्य;

out:
	mutex_unlock(&prog->aux->used_maps_mutex);
	वापस map;
पूर्ण

अटल काष्ठा bpf_insn *bpf_insn_prepare_dump(स्थिर काष्ठा bpf_prog *prog,
					      स्थिर काष्ठा cred *f_cred)
अणु
	स्थिर काष्ठा bpf_map *map;
	काष्ठा bpf_insn *insns;
	u32 off, type;
	u64 imm;
	u8 code;
	पूर्णांक i;

	insns = kmemdup(prog->insnsi, bpf_prog_insn_size(prog),
			GFP_USER);
	अगर (!insns)
		वापस insns;

	क्रम (i = 0; i < prog->len; i++) अणु
		code = insns[i].code;

		अगर (code == (BPF_JMP | BPF_TAIL_CALL)) अणु
			insns[i].code = BPF_JMP | BPF_CALL;
			insns[i].imm = BPF_FUNC_tail_call;
			/* fall-through */
		पूर्ण
		अगर (code == (BPF_JMP | BPF_CALL) ||
		    code == (BPF_JMP | BPF_CALL_ARGS)) अणु
			अगर (code == (BPF_JMP | BPF_CALL_ARGS))
				insns[i].code = BPF_JMP | BPF_CALL;
			अगर (!bpf_dump_raw_ok(f_cred))
				insns[i].imm = 0;
			जारी;
		पूर्ण
		अगर (BPF_CLASS(code) == BPF_LDX && BPF_MODE(code) == BPF_PROBE_MEM) अणु
			insns[i].code = BPF_LDX | BPF_SIZE(code) | BPF_MEM;
			जारी;
		पूर्ण

		अगर (code != (BPF_LD | BPF_IMM | BPF_DW))
			जारी;

		imm = ((u64)insns[i + 1].imm << 32) | (u32)insns[i].imm;
		map = bpf_map_from_imm(prog, imm, &off, &type);
		अगर (map) अणु
			insns[i].src_reg = type;
			insns[i].imm = map->id;
			insns[i + 1].imm = off;
			जारी;
		पूर्ण
	पूर्ण

	वापस insns;
पूर्ण

अटल पूर्णांक set_info_rec_size(काष्ठा bpf_prog_info *info)
अणु
	/*
	 * Ensure info.*_rec_size is the same as kernel expected size
	 *
	 * or
	 *
	 * Only allow zero *_rec_size अगर both _rec_size and _cnt are
	 * zero.  In this हाल, the kernel will set the expected
	 * _rec_size back to the info.
	 */

	अगर ((info->nr_func_info || info->func_info_rec_size) &&
	    info->func_info_rec_size != माप(काष्ठा bpf_func_info))
		वापस -EINVAL;

	अगर ((info->nr_line_info || info->line_info_rec_size) &&
	    info->line_info_rec_size != माप(काष्ठा bpf_line_info))
		वापस -EINVAL;

	अगर ((info->nr_jited_line_info || info->jited_line_info_rec_size) &&
	    info->jited_line_info_rec_size != माप(__u64))
		वापस -EINVAL;

	info->func_info_rec_size = माप(काष्ठा bpf_func_info);
	info->line_info_rec_size = माप(काष्ठा bpf_line_info);
	info->jited_line_info_rec_size = माप(__u64);

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_prog_get_info_by_fd(काष्ठा file *file,
				   काष्ठा bpf_prog *prog,
				   स्थिर जोड़ bpf_attr *attr,
				   जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_prog_info __user *uinfo = u64_to_user_ptr(attr->info.info);
	काष्ठा bpf_prog_info info;
	u32 info_len = attr->info.info_len;
	काष्ठा bpf_prog_stats stats;
	अक्षर __user *uinsns;
	u32 ulen;
	पूर्णांक err;

	err = bpf_check_uarg_tail_zero(uinfo, माप(info), info_len);
	अगर (err)
		वापस err;
	info_len = min_t(u32, माप(info), info_len);

	स_रखो(&info, 0, माप(info));
	अगर (copy_from_user(&info, uinfo, info_len))
		वापस -EFAULT;

	info.type = prog->type;
	info.id = prog->aux->id;
	info.load_समय = prog->aux->load_समय;
	info.created_by_uid = from_kuid_munged(current_user_ns(),
					       prog->aux->user->uid);
	info.gpl_compatible = prog->gpl_compatible;

	स_नकल(info.tag, prog->tag, माप(prog->tag));
	स_नकल(info.name, prog->aux->name, माप(prog->aux->name));

	mutex_lock(&prog->aux->used_maps_mutex);
	ulen = info.nr_map_ids;
	info.nr_map_ids = prog->aux->used_map_cnt;
	ulen = min_t(u32, info.nr_map_ids, ulen);
	अगर (ulen) अणु
		u32 __user *user_map_ids = u64_to_user_ptr(info.map_ids);
		u32 i;

		क्रम (i = 0; i < ulen; i++)
			अगर (put_user(prog->aux->used_maps[i]->id,
				     &user_map_ids[i])) अणु
				mutex_unlock(&prog->aux->used_maps_mutex);
				वापस -EFAULT;
			पूर्ण
	पूर्ण
	mutex_unlock(&prog->aux->used_maps_mutex);

	err = set_info_rec_size(&info);
	अगर (err)
		वापस err;

	bpf_prog_get_stats(prog, &stats);
	info.run_समय_ns = stats.nsecs;
	info.run_cnt = stats.cnt;
	info.recursion_misses = stats.misses;

	अगर (!bpf_capable()) अणु
		info.jited_prog_len = 0;
		info.xlated_prog_len = 0;
		info.nr_jited_ksyms = 0;
		info.nr_jited_func_lens = 0;
		info.nr_func_info = 0;
		info.nr_line_info = 0;
		info.nr_jited_line_info = 0;
		जाओ करोne;
	पूर्ण

	ulen = info.xlated_prog_len;
	info.xlated_prog_len = bpf_prog_insn_size(prog);
	अगर (info.xlated_prog_len && ulen) अणु
		काष्ठा bpf_insn *insns_sanitized;
		bool fault;

		अगर (prog->blinded && !bpf_dump_raw_ok(file->f_cred)) अणु
			info.xlated_prog_insns = 0;
			जाओ करोne;
		पूर्ण
		insns_sanitized = bpf_insn_prepare_dump(prog, file->f_cred);
		अगर (!insns_sanitized)
			वापस -ENOMEM;
		uinsns = u64_to_user_ptr(info.xlated_prog_insns);
		ulen = min_t(u32, info.xlated_prog_len, ulen);
		fault = copy_to_user(uinsns, insns_sanitized, ulen);
		kमुक्त(insns_sanitized);
		अगर (fault)
			वापस -EFAULT;
	पूर्ण

	अगर (bpf_prog_is_dev_bound(prog->aux)) अणु
		err = bpf_prog_offload_info_fill(&info, prog);
		अगर (err)
			वापस err;
		जाओ करोne;
	पूर्ण

	/* NOTE: the following code is supposed to be skipped क्रम offload.
	 * bpf_prog_offload_info_fill() is the place to fill similar fields
	 * क्रम offload.
	 */
	ulen = info.jited_prog_len;
	अगर (prog->aux->func_cnt) अणु
		u32 i;

		info.jited_prog_len = 0;
		क्रम (i = 0; i < prog->aux->func_cnt; i++)
			info.jited_prog_len += prog->aux->func[i]->jited_len;
	पूर्ण अन्यथा अणु
		info.jited_prog_len = prog->jited_len;
	पूर्ण

	अगर (info.jited_prog_len && ulen) अणु
		अगर (bpf_dump_raw_ok(file->f_cred)) अणु
			uinsns = u64_to_user_ptr(info.jited_prog_insns);
			ulen = min_t(u32, info.jited_prog_len, ulen);

			/* क्रम multi-function programs, copy the JITed
			 * inकाष्ठाions क्रम all the functions
			 */
			अगर (prog->aux->func_cnt) अणु
				u32 len, मुक्त, i;
				u8 *img;

				मुक्त = ulen;
				क्रम (i = 0; i < prog->aux->func_cnt; i++) अणु
					len = prog->aux->func[i]->jited_len;
					len = min_t(u32, len, मुक्त);
					img = (u8 *) prog->aux->func[i]->bpf_func;
					अगर (copy_to_user(uinsns, img, len))
						वापस -EFAULT;
					uinsns += len;
					मुक्त -= len;
					अगर (!मुक्त)
						अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (copy_to_user(uinsns, prog->bpf_func, ulen))
					वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			info.jited_prog_insns = 0;
		पूर्ण
	पूर्ण

	ulen = info.nr_jited_ksyms;
	info.nr_jited_ksyms = prog->aux->func_cnt ? : 1;
	अगर (ulen) अणु
		अगर (bpf_dump_raw_ok(file->f_cred)) अणु
			अचिन्हित दीर्घ ksym_addr;
			u64 __user *user_ksyms;
			u32 i;

			/* copy the address of the kernel symbol
			 * corresponding to each function
			 */
			ulen = min_t(u32, info.nr_jited_ksyms, ulen);
			user_ksyms = u64_to_user_ptr(info.jited_ksyms);
			अगर (prog->aux->func_cnt) अणु
				क्रम (i = 0; i < ulen; i++) अणु
					ksym_addr = (अचिन्हित दीर्घ)
						prog->aux->func[i]->bpf_func;
					अगर (put_user((u64) ksym_addr,
						     &user_ksyms[i]))
						वापस -EFAULT;
				पूर्ण
			पूर्ण अन्यथा अणु
				ksym_addr = (अचिन्हित दीर्घ) prog->bpf_func;
				अगर (put_user((u64) ksym_addr, &user_ksyms[0]))
					वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			info.jited_ksyms = 0;
		पूर्ण
	पूर्ण

	ulen = info.nr_jited_func_lens;
	info.nr_jited_func_lens = prog->aux->func_cnt ? : 1;
	अगर (ulen) अणु
		अगर (bpf_dump_raw_ok(file->f_cred)) अणु
			u32 __user *user_lens;
			u32 func_len, i;

			/* copy the JITed image lengths क्रम each function */
			ulen = min_t(u32, info.nr_jited_func_lens, ulen);
			user_lens = u64_to_user_ptr(info.jited_func_lens);
			अगर (prog->aux->func_cnt) अणु
				क्रम (i = 0; i < ulen; i++) अणु
					func_len =
						prog->aux->func[i]->jited_len;
					अगर (put_user(func_len, &user_lens[i]))
						वापस -EFAULT;
				पूर्ण
			पूर्ण अन्यथा अणु
				func_len = prog->jited_len;
				अगर (put_user(func_len, &user_lens[0]))
					वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			info.jited_func_lens = 0;
		पूर्ण
	पूर्ण

	अगर (prog->aux->btf)
		info.btf_id = btf_obj_id(prog->aux->btf);

	ulen = info.nr_func_info;
	info.nr_func_info = prog->aux->func_info_cnt;
	अगर (info.nr_func_info && ulen) अणु
		अक्षर __user *user_finfo;

		user_finfo = u64_to_user_ptr(info.func_info);
		ulen = min_t(u32, info.nr_func_info, ulen);
		अगर (copy_to_user(user_finfo, prog->aux->func_info,
				 info.func_info_rec_size * ulen))
			वापस -EFAULT;
	पूर्ण

	ulen = info.nr_line_info;
	info.nr_line_info = prog->aux->nr_linfo;
	अगर (info.nr_line_info && ulen) अणु
		__u8 __user *user_linfo;

		user_linfo = u64_to_user_ptr(info.line_info);
		ulen = min_t(u32, info.nr_line_info, ulen);
		अगर (copy_to_user(user_linfo, prog->aux->linfo,
				 info.line_info_rec_size * ulen))
			वापस -EFAULT;
	पूर्ण

	ulen = info.nr_jited_line_info;
	अगर (prog->aux->jited_linfo)
		info.nr_jited_line_info = prog->aux->nr_linfo;
	अन्यथा
		info.nr_jited_line_info = 0;
	अगर (info.nr_jited_line_info && ulen) अणु
		अगर (bpf_dump_raw_ok(file->f_cred)) अणु
			__u64 __user *user_linfo;
			u32 i;

			user_linfo = u64_to_user_ptr(info.jited_line_info);
			ulen = min_t(u32, info.nr_jited_line_info, ulen);
			क्रम (i = 0; i < ulen; i++) अणु
				अगर (put_user((__u64)(दीर्घ)prog->aux->jited_linfo[i],
					     &user_linfo[i]))
					वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			info.jited_line_info = 0;
		पूर्ण
	पूर्ण

	ulen = info.nr_prog_tags;
	info.nr_prog_tags = prog->aux->func_cnt ? : 1;
	अगर (ulen) अणु
		__u8 __user (*user_prog_tags)[BPF_TAG_SIZE];
		u32 i;

		user_prog_tags = u64_to_user_ptr(info.prog_tags);
		ulen = min_t(u32, info.nr_prog_tags, ulen);
		अगर (prog->aux->func_cnt) अणु
			क्रम (i = 0; i < ulen; i++) अणु
				अगर (copy_to_user(user_prog_tags[i],
						 prog->aux->func[i]->tag,
						 BPF_TAG_SIZE))
					वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (copy_to_user(user_prog_tags[0],
					 prog->tag, BPF_TAG_SIZE))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

करोne:
	अगर (copy_to_user(uinfo, &info, info_len) ||
	    put_user(info_len, &uattr->info.info_len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_map_get_info_by_fd(काष्ठा file *file,
				  काष्ठा bpf_map *map,
				  स्थिर जोड़ bpf_attr *attr,
				  जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_map_info __user *uinfo = u64_to_user_ptr(attr->info.info);
	काष्ठा bpf_map_info info;
	u32 info_len = attr->info.info_len;
	पूर्णांक err;

	err = bpf_check_uarg_tail_zero(uinfo, माप(info), info_len);
	अगर (err)
		वापस err;
	info_len = min_t(u32, माप(info), info_len);

	स_रखो(&info, 0, माप(info));
	info.type = map->map_type;
	info.id = map->id;
	info.key_size = map->key_size;
	info.value_size = map->value_size;
	info.max_entries = map->max_entries;
	info.map_flags = map->map_flags;
	स_नकल(info.name, map->name, माप(map->name));

	अगर (map->btf) अणु
		info.btf_id = btf_obj_id(map->btf);
		info.btf_key_type_id = map->btf_key_type_id;
		info.btf_value_type_id = map->btf_value_type_id;
	पूर्ण
	info.btf_vmlinux_value_type_id = map->btf_vmlinux_value_type_id;

	अगर (bpf_map_is_dev_bound(map)) अणु
		err = bpf_map_offload_info_fill(&info, map);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (copy_to_user(uinfo, &info, info_len) ||
	    put_user(info_len, &uattr->info.info_len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_btf_get_info_by_fd(काष्ठा file *file,
				  काष्ठा btf *btf,
				  स्थिर जोड़ bpf_attr *attr,
				  जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_btf_info __user *uinfo = u64_to_user_ptr(attr->info.info);
	u32 info_len = attr->info.info_len;
	पूर्णांक err;

	err = bpf_check_uarg_tail_zero(uinfo, माप(*uinfo), info_len);
	अगर (err)
		वापस err;

	वापस btf_get_info_by_fd(btf, attr, uattr);
पूर्ण

अटल पूर्णांक bpf_link_get_info_by_fd(काष्ठा file *file,
				  काष्ठा bpf_link *link,
				  स्थिर जोड़ bpf_attr *attr,
				  जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_link_info __user *uinfo = u64_to_user_ptr(attr->info.info);
	काष्ठा bpf_link_info info;
	u32 info_len = attr->info.info_len;
	पूर्णांक err;

	err = bpf_check_uarg_tail_zero(uinfo, माप(info), info_len);
	अगर (err)
		वापस err;
	info_len = min_t(u32, माप(info), info_len);

	स_रखो(&info, 0, माप(info));
	अगर (copy_from_user(&info, uinfo, info_len))
		वापस -EFAULT;

	info.type = link->type;
	info.id = link->id;
	info.prog_id = link->prog->aux->id;

	अगर (link->ops->fill_link_info) अणु
		err = link->ops->fill_link_info(link, &info);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (copy_to_user(uinfo, &info, info_len) ||
	    put_user(info_len, &uattr->info.info_len))
		वापस -EFAULT;

	वापस 0;
पूर्ण


#घोषणा BPF_OBJ_GET_INFO_BY_FD_LAST_FIELD info.info

अटल पूर्णांक bpf_obj_get_info_by_fd(स्थिर जोड़ bpf_attr *attr,
				  जोड़ bpf_attr __user *uattr)
अणु
	पूर्णांक ufd = attr->info.bpf_fd;
	काष्ठा fd f;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_OBJ_GET_INFO_BY_FD))
		वापस -EINVAL;

	f = fdget(ufd);
	अगर (!f.file)
		वापस -EBADFD;

	अगर (f.file->f_op == &bpf_prog_fops)
		err = bpf_prog_get_info_by_fd(f.file, f.file->निजी_data, attr,
					      uattr);
	अन्यथा अगर (f.file->f_op == &bpf_map_fops)
		err = bpf_map_get_info_by_fd(f.file, f.file->निजी_data, attr,
					     uattr);
	अन्यथा अगर (f.file->f_op == &btf_fops)
		err = bpf_btf_get_info_by_fd(f.file, f.file->निजी_data, attr, uattr);
	अन्यथा अगर (f.file->f_op == &bpf_link_fops)
		err = bpf_link_get_info_by_fd(f.file, f.file->निजी_data,
					      attr, uattr);
	अन्यथा
		err = -EINVAL;

	fdput(f);
	वापस err;
पूर्ण

#घोषणा BPF_BTF_LOAD_LAST_FIELD btf_log_level

अटल पूर्णांक bpf_btf_load(स्थिर जोड़ bpf_attr *attr)
अणु
	अगर (CHECK_ATTR(BPF_BTF_LOAD))
		वापस -EINVAL;

	अगर (!bpf_capable())
		वापस -EPERM;

	वापस btf_new_fd(attr);
पूर्ण

#घोषणा BPF_BTF_GET_FD_BY_ID_LAST_FIELD btf_id

अटल पूर्णांक bpf_btf_get_fd_by_id(स्थिर जोड़ bpf_attr *attr)
अणु
	अगर (CHECK_ATTR(BPF_BTF_GET_FD_BY_ID))
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस btf_get_fd_by_id(attr->btf_id);
पूर्ण

अटल पूर्णांक bpf_task_fd_query_copy(स्थिर जोड़ bpf_attr *attr,
				    जोड़ bpf_attr __user *uattr,
				    u32 prog_id, u32 fd_type,
				    स्थिर अक्षर *buf, u64 probe_offset,
				    u64 probe_addr)
अणु
	अक्षर __user *ubuf = u64_to_user_ptr(attr->task_fd_query.buf);
	u32 len = buf ? म_माप(buf) : 0, input_len;
	पूर्णांक err = 0;

	अगर (put_user(len, &uattr->task_fd_query.buf_len))
		वापस -EFAULT;
	input_len = attr->task_fd_query.buf_len;
	अगर (input_len && ubuf) अणु
		अगर (!len) अणु
			/* nothing to copy, just make ubuf शून्य terminated */
			अक्षर zero = '\0';

			अगर (put_user(zero, ubuf))
				वापस -EFAULT;
		पूर्ण अन्यथा अगर (input_len >= len + 1) अणु
			/* ubuf can hold the string with शून्य terminator */
			अगर (copy_to_user(ubuf, buf, len + 1))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			/* ubuf cannot hold the string with शून्य terminator,
			 * करो a partial copy with शून्य terminator.
			 */
			अक्षर zero = '\0';

			err = -ENOSPC;
			अगर (copy_to_user(ubuf, buf, input_len - 1))
				वापस -EFAULT;
			अगर (put_user(zero, ubuf + input_len - 1))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (put_user(prog_id, &uattr->task_fd_query.prog_id) ||
	    put_user(fd_type, &uattr->task_fd_query.fd_type) ||
	    put_user(probe_offset, &uattr->task_fd_query.probe_offset) ||
	    put_user(probe_addr, &uattr->task_fd_query.probe_addr))
		वापस -EFAULT;

	वापस err;
पूर्ण

#घोषणा BPF_TASK_FD_QUERY_LAST_FIELD task_fd_query.probe_addr

अटल पूर्णांक bpf_task_fd_query(स्थिर जोड़ bpf_attr *attr,
			     जोड़ bpf_attr __user *uattr)
अणु
	pid_t pid = attr->task_fd_query.pid;
	u32 fd = attr->task_fd_query.fd;
	स्थिर काष्ठा perf_event *event;
	काष्ठा task_काष्ठा *task;
	काष्ठा file *file;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_TASK_FD_QUERY))
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (attr->task_fd_query.flags != 0)
		वापस -EINVAL;

	task = get_pid_task(find_vpid(pid), PIDTYPE_PID);
	अगर (!task)
		वापस -ENOENT;

	err = 0;
	file = fget_task(task, fd);
	put_task_काष्ठा(task);
	अगर (!file)
		वापस -EBADF;

	अगर (file->f_op == &bpf_link_fops) अणु
		काष्ठा bpf_link *link = file->निजी_data;

		अगर (link->ops == &bpf_raw_tp_link_lops) अणु
			काष्ठा bpf_raw_tp_link *raw_tp =
				container_of(link, काष्ठा bpf_raw_tp_link, link);
			काष्ठा bpf_raw_event_map *btp = raw_tp->btp;

			err = bpf_task_fd_query_copy(attr, uattr,
						     raw_tp->link.prog->aux->id,
						     BPF_FD_TYPE_RAW_TRACEPOINT,
						     btp->tp->name, 0, 0);
			जाओ put_file;
		पूर्ण
		जाओ out_not_supp;
	पूर्ण

	event = perf_get_event(file);
	अगर (!IS_ERR(event)) अणु
		u64 probe_offset, probe_addr;
		u32 prog_id, fd_type;
		स्थिर अक्षर *buf;

		err = bpf_get_perf_event_info(event, &prog_id, &fd_type,
					      &buf, &probe_offset,
					      &probe_addr);
		अगर (!err)
			err = bpf_task_fd_query_copy(attr, uattr, prog_id,
						     fd_type, buf,
						     probe_offset,
						     probe_addr);
		जाओ put_file;
	पूर्ण

out_not_supp:
	err = -ENOTSUPP;
put_file:
	fput(file);
	वापस err;
पूर्ण

#घोषणा BPF_MAP_BATCH_LAST_FIELD batch.flags

#घोषणा BPF_DO_BATCH(fn)			\
	करो अणु					\
		अगर (!fn) अणु			\
			err = -ENOTSUPP;	\
			जाओ err_put;		\
		पूर्ण				\
		err = fn(map, attr, uattr);	\
	पूर्ण जबतक (0)

अटल पूर्णांक bpf_map_करो_batch(स्थिर जोड़ bpf_attr *attr,
			    जोड़ bpf_attr __user *uattr,
			    पूर्णांक cmd)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक err, ufd;
	काष्ठा fd f;

	अगर (CHECK_ATTR(BPF_MAP_BATCH))
		वापस -EINVAL;

	ufd = attr->batch.map_fd;
	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	अगर ((cmd == BPF_MAP_LOOKUP_BATCH ||
	     cmd == BPF_MAP_LOOKUP_AND_DELETE_BATCH) &&
	    !(map_get_sys_perms(map, f) & FMODE_CAN_READ)) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	अगर (cmd != BPF_MAP_LOOKUP_BATCH &&
	    !(map_get_sys_perms(map, f) & FMODE_CAN_WRITE)) अणु
		err = -EPERM;
		जाओ err_put;
	पूर्ण

	अगर (cmd == BPF_MAP_LOOKUP_BATCH)
		BPF_DO_BATCH(map->ops->map_lookup_batch);
	अन्यथा अगर (cmd == BPF_MAP_LOOKUP_AND_DELETE_BATCH)
		BPF_DO_BATCH(map->ops->map_lookup_and_delete_batch);
	अन्यथा अगर (cmd == BPF_MAP_UPDATE_BATCH)
		BPF_DO_BATCH(map->ops->map_update_batch);
	अन्यथा
		BPF_DO_BATCH(map->ops->map_delete_batch);

err_put:
	fdput(f);
	वापस err;
पूर्ण

अटल पूर्णांक tracing_bpf_link_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	अगर (attr->link_create.attach_type != prog->expected_attach_type)
		वापस -EINVAL;

	अगर (prog->expected_attach_type == BPF_TRACE_ITER)
		वापस bpf_iter_link_attach(attr, prog);
	अन्यथा अगर (prog->type == BPF_PROG_TYPE_EXT)
		वापस bpf_tracing_prog_attach(prog,
					       attr->link_create.target_fd,
					       attr->link_create.target_btf_id);
	वापस -EINVAL;
पूर्ण

#घोषणा BPF_LINK_CREATE_LAST_FIELD link_create.iter_info_len
अटल पूर्णांक link_create(जोड़ bpf_attr *attr)
अणु
	क्रमागत bpf_prog_type ptype;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret;

	अगर (CHECK_ATTR(BPF_LINK_CREATE))
		वापस -EINVAL;

	prog = bpf_prog_get(attr->link_create.prog_fd);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	ret = bpf_prog_attach_check_attach_type(prog,
						attr->link_create.attach_type);
	अगर (ret)
		जाओ out;

	अगर (prog->type == BPF_PROG_TYPE_EXT) अणु
		ret = tracing_bpf_link_attach(attr, prog);
		जाओ out;
	पूर्ण

	ptype = attach_type_to_prog_type(attr->link_create.attach_type);
	अगर (ptype == BPF_PROG_TYPE_UNSPEC || ptype != prog->type) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (ptype) अणु
	हाल BPF_PROG_TYPE_CGROUP_SKB:
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	हाल BPF_PROG_TYPE_SOCK_OPS:
	हाल BPF_PROG_TYPE_CGROUP_DEVICE:
	हाल BPF_PROG_TYPE_CGROUP_SYSCTL:
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
		ret = cgroup_bpf_link_attach(attr, prog);
		अवरोध;
	हाल BPF_PROG_TYPE_TRACING:
		ret = tracing_bpf_link_attach(attr, prog);
		अवरोध;
	हाल BPF_PROG_TYPE_FLOW_DISSECTOR:
	हाल BPF_PROG_TYPE_SK_LOOKUP:
		ret = netns_bpf_link_create(attr, prog);
		अवरोध;
#अगर_घोषित CONFIG_NET
	हाल BPF_PROG_TYPE_XDP:
		ret = bpf_xdp_link_attach(attr, prog);
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	अगर (ret < 0)
		bpf_prog_put(prog);
	वापस ret;
पूर्ण

#घोषणा BPF_LINK_UPDATE_LAST_FIELD link_update.old_prog_fd

अटल पूर्णांक link_update(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_prog *old_prog = शून्य, *new_prog;
	काष्ठा bpf_link *link;
	u32 flags;
	पूर्णांक ret;

	अगर (CHECK_ATTR(BPF_LINK_UPDATE))
		वापस -EINVAL;

	flags = attr->link_update.flags;
	अगर (flags & ~BPF_F_REPLACE)
		वापस -EINVAL;

	link = bpf_link_get_from_fd(attr->link_update.link_fd);
	अगर (IS_ERR(link))
		वापस PTR_ERR(link);

	new_prog = bpf_prog_get(attr->link_update.new_prog_fd);
	अगर (IS_ERR(new_prog)) अणु
		ret = PTR_ERR(new_prog);
		जाओ out_put_link;
	पूर्ण

	अगर (flags & BPF_F_REPLACE) अणु
		old_prog = bpf_prog_get(attr->link_update.old_prog_fd);
		अगर (IS_ERR(old_prog)) अणु
			ret = PTR_ERR(old_prog);
			old_prog = शून्य;
			जाओ out_put_progs;
		पूर्ण
	पूर्ण अन्यथा अगर (attr->link_update.old_prog_fd) अणु
		ret = -EINVAL;
		जाओ out_put_progs;
	पूर्ण

	अगर (link->ops->update_prog)
		ret = link->ops->update_prog(link, new_prog, old_prog);
	अन्यथा
		ret = -EINVAL;

out_put_progs:
	अगर (old_prog)
		bpf_prog_put(old_prog);
	अगर (ret)
		bpf_prog_put(new_prog);
out_put_link:
	bpf_link_put(link);
	वापस ret;
पूर्ण

#घोषणा BPF_LINK_DETACH_LAST_FIELD link_detach.link_fd

अटल पूर्णांक link_detach(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_link *link;
	पूर्णांक ret;

	अगर (CHECK_ATTR(BPF_LINK_DETACH))
		वापस -EINVAL;

	link = bpf_link_get_from_fd(attr->link_detach.link_fd);
	अगर (IS_ERR(link))
		वापस PTR_ERR(link);

	अगर (link->ops->detach)
		ret = link->ops->detach(link);
	अन्यथा
		ret = -EOPNOTSUPP;

	bpf_link_put(link);
	वापस ret;
पूर्ण

अटल काष्ठा bpf_link *bpf_link_inc_not_zero(काष्ठा bpf_link *link)
अणु
	वापस atomic64_fetch_add_unless(&link->refcnt, 1, 0) ? link : ERR_PTR(-ENOENT);
पूर्ण

काष्ठा bpf_link *bpf_link_by_id(u32 id)
अणु
	काष्ठा bpf_link *link;

	अगर (!id)
		वापस ERR_PTR(-ENOENT);

	spin_lock_bh(&link_idr_lock);
	/* beक्रमe link is "settled", ID is 0, pretend it करोesn't exist yet */
	link = idr_find(&link_idr, id);
	अगर (link) अणु
		अगर (link->id)
			link = bpf_link_inc_not_zero(link);
		अन्यथा
			link = ERR_PTR(-EAGAIN);
	पूर्ण अन्यथा अणु
		link = ERR_PTR(-ENOENT);
	पूर्ण
	spin_unlock_bh(&link_idr_lock);
	वापस link;
पूर्ण

#घोषणा BPF_LINK_GET_FD_BY_ID_LAST_FIELD link_id

अटल पूर्णांक bpf_link_get_fd_by_id(स्थिर जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_link *link;
	u32 id = attr->link_id;
	पूर्णांक fd;

	अगर (CHECK_ATTR(BPF_LINK_GET_FD_BY_ID))
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	link = bpf_link_by_id(id);
	अगर (IS_ERR(link))
		वापस PTR_ERR(link);

	fd = bpf_link_new_fd(link);
	अगर (fd < 0)
		bpf_link_put(link);

	वापस fd;
पूर्ण

DEFINE_MUTEX(bpf_stats_enabled_mutex);

अटल पूर्णांक bpf_stats_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&bpf_stats_enabled_mutex);
	अटल_key_slow_dec(&bpf_stats_enabled_key.key);
	mutex_unlock(&bpf_stats_enabled_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations bpf_stats_fops = अणु
	.release = bpf_stats_release,
पूर्ण;

अटल पूर्णांक bpf_enable_runसमय_stats(व्योम)
अणु
	पूर्णांक fd;

	mutex_lock(&bpf_stats_enabled_mutex);

	/* Set a very high limit to aव्योम overflow */
	अगर (अटल_key_count(&bpf_stats_enabled_key.key) > पूर्णांक_उच्च / 2) अणु
		mutex_unlock(&bpf_stats_enabled_mutex);
		वापस -EBUSY;
	पूर्ण

	fd = anon_inode_getfd("bpf-stats", &bpf_stats_fops, शून्य, O_CLOEXEC);
	अगर (fd >= 0)
		अटल_key_slow_inc(&bpf_stats_enabled_key.key);

	mutex_unlock(&bpf_stats_enabled_mutex);
	वापस fd;
पूर्ण

#घोषणा BPF_ENABLE_STATS_LAST_FIELD enable_stats.type

अटल पूर्णांक bpf_enable_stats(जोड़ bpf_attr *attr)
अणु

	अगर (CHECK_ATTR(BPF_ENABLE_STATS))
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (attr->enable_stats.type) अणु
	हाल BPF_STATS_RUN_TIME:
		वापस bpf_enable_runसमय_stats();
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा BPF_ITER_CREATE_LAST_FIELD iter_create.flags

अटल पूर्णांक bpf_iter_create(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_link *link;
	पूर्णांक err;

	अगर (CHECK_ATTR(BPF_ITER_CREATE))
		वापस -EINVAL;

	अगर (attr->iter_create.flags)
		वापस -EINVAL;

	link = bpf_link_get_from_fd(attr->iter_create.link_fd);
	अगर (IS_ERR(link))
		वापस PTR_ERR(link);

	err = bpf_iter_new_fd(link);
	bpf_link_put(link);

	वापस err;
पूर्ण

#घोषणा BPF_PROG_BIND_MAP_LAST_FIELD prog_bind_map.flags

अटल पूर्णांक bpf_prog_bind_map(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_map *map;
	काष्ठा bpf_map **used_maps_old, **used_maps_new;
	पूर्णांक i, ret = 0;

	अगर (CHECK_ATTR(BPF_PROG_BIND_MAP))
		वापस -EINVAL;

	अगर (attr->prog_bind_map.flags)
		वापस -EINVAL;

	prog = bpf_prog_get(attr->prog_bind_map.prog_fd);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	map = bpf_map_get(attr->prog_bind_map.map_fd);
	अगर (IS_ERR(map)) अणु
		ret = PTR_ERR(map);
		जाओ out_prog_put;
	पूर्ण

	mutex_lock(&prog->aux->used_maps_mutex);

	used_maps_old = prog->aux->used_maps;

	क्रम (i = 0; i < prog->aux->used_map_cnt; i++)
		अगर (used_maps_old[i] == map) अणु
			bpf_map_put(map);
			जाओ out_unlock;
		पूर्ण

	used_maps_new = kदो_स्मृति_array(prog->aux->used_map_cnt + 1,
				      माप(used_maps_new[0]),
				      GFP_KERNEL);
	अगर (!used_maps_new) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	स_नकल(used_maps_new, used_maps_old,
	       माप(used_maps_old[0]) * prog->aux->used_map_cnt);
	used_maps_new[prog->aux->used_map_cnt] = map;

	prog->aux->used_map_cnt++;
	prog->aux->used_maps = used_maps_new;

	kमुक्त(used_maps_old);

out_unlock:
	mutex_unlock(&prog->aux->used_maps_mutex);

	अगर (ret)
		bpf_map_put(map);
out_prog_put:
	bpf_prog_put(prog);
	वापस ret;
पूर्ण

SYSCALL_DEFINE3(bpf, पूर्णांक, cmd, जोड़ bpf_attr __user *, uattr, अचिन्हित पूर्णांक, size)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक err;

	अगर (sysctl_unprivileged_bpf_disabled && !bpf_capable())
		वापस -EPERM;

	err = bpf_check_uarg_tail_zero(uattr, माप(attr), size);
	अगर (err)
		वापस err;
	size = min_t(u32, size, माप(attr));

	/* copy attributes from user space, may be less than माप(bpf_attr) */
	स_रखो(&attr, 0, माप(attr));
	अगर (copy_from_user(&attr, uattr, size) != 0)
		वापस -EFAULT;

	err = security_bpf(cmd, &attr, size);
	अगर (err < 0)
		वापस err;

	चयन (cmd) अणु
	हाल BPF_MAP_CREATE:
		err = map_create(&attr);
		अवरोध;
	हाल BPF_MAP_LOOKUP_ELEM:
		err = map_lookup_elem(&attr);
		अवरोध;
	हाल BPF_MAP_UPDATE_ELEM:
		err = map_update_elem(&attr);
		अवरोध;
	हाल BPF_MAP_DELETE_ELEM:
		err = map_delete_elem(&attr);
		अवरोध;
	हाल BPF_MAP_GET_NEXT_KEY:
		err = map_get_next_key(&attr);
		अवरोध;
	हाल BPF_MAP_FREEZE:
		err = map_मुक्तze(&attr);
		अवरोध;
	हाल BPF_PROG_LOAD:
		err = bpf_prog_load(&attr, uattr);
		अवरोध;
	हाल BPF_OBJ_PIN:
		err = bpf_obj_pin(&attr);
		अवरोध;
	हाल BPF_OBJ_GET:
		err = bpf_obj_get(&attr);
		अवरोध;
	हाल BPF_PROG_ATTACH:
		err = bpf_prog_attach(&attr);
		अवरोध;
	हाल BPF_PROG_DETACH:
		err = bpf_prog_detach(&attr);
		अवरोध;
	हाल BPF_PROG_QUERY:
		err = bpf_prog_query(&attr, uattr);
		अवरोध;
	हाल BPF_PROG_TEST_RUN:
		err = bpf_prog_test_run(&attr, uattr);
		अवरोध;
	हाल BPF_PROG_GET_NEXT_ID:
		err = bpf_obj_get_next_id(&attr, uattr,
					  &prog_idr, &prog_idr_lock);
		अवरोध;
	हाल BPF_MAP_GET_NEXT_ID:
		err = bpf_obj_get_next_id(&attr, uattr,
					  &map_idr, &map_idr_lock);
		अवरोध;
	हाल BPF_BTF_GET_NEXT_ID:
		err = bpf_obj_get_next_id(&attr, uattr,
					  &btf_idr, &btf_idr_lock);
		अवरोध;
	हाल BPF_PROG_GET_FD_BY_ID:
		err = bpf_prog_get_fd_by_id(&attr);
		अवरोध;
	हाल BPF_MAP_GET_FD_BY_ID:
		err = bpf_map_get_fd_by_id(&attr);
		अवरोध;
	हाल BPF_OBJ_GET_INFO_BY_FD:
		err = bpf_obj_get_info_by_fd(&attr, uattr);
		अवरोध;
	हाल BPF_RAW_TRACEPOINT_OPEN:
		err = bpf_raw_tracepoपूर्णांक_खोलो(&attr);
		अवरोध;
	हाल BPF_BTF_LOAD:
		err = bpf_btf_load(&attr);
		अवरोध;
	हाल BPF_BTF_GET_FD_BY_ID:
		err = bpf_btf_get_fd_by_id(&attr);
		अवरोध;
	हाल BPF_TASK_FD_QUERY:
		err = bpf_task_fd_query(&attr, uattr);
		अवरोध;
	हाल BPF_MAP_LOOKUP_AND_DELETE_ELEM:
		err = map_lookup_and_delete_elem(&attr);
		अवरोध;
	हाल BPF_MAP_LOOKUP_BATCH:
		err = bpf_map_करो_batch(&attr, uattr, BPF_MAP_LOOKUP_BATCH);
		अवरोध;
	हाल BPF_MAP_LOOKUP_AND_DELETE_BATCH:
		err = bpf_map_करो_batch(&attr, uattr,
				       BPF_MAP_LOOKUP_AND_DELETE_BATCH);
		अवरोध;
	हाल BPF_MAP_UPDATE_BATCH:
		err = bpf_map_करो_batch(&attr, uattr, BPF_MAP_UPDATE_BATCH);
		अवरोध;
	हाल BPF_MAP_DELETE_BATCH:
		err = bpf_map_करो_batch(&attr, uattr, BPF_MAP_DELETE_BATCH);
		अवरोध;
	हाल BPF_LINK_CREATE:
		err = link_create(&attr);
		अवरोध;
	हाल BPF_LINK_UPDATE:
		err = link_update(&attr);
		अवरोध;
	हाल BPF_LINK_GET_FD_BY_ID:
		err = bpf_link_get_fd_by_id(&attr);
		अवरोध;
	हाल BPF_LINK_GET_NEXT_ID:
		err = bpf_obj_get_next_id(&attr, uattr,
					  &link_idr, &link_idr_lock);
		अवरोध;
	हाल BPF_ENABLE_STATS:
		err = bpf_enable_stats(&attr);
		अवरोध;
	हाल BPF_ITER_CREATE:
		err = bpf_iter_create(&attr);
		अवरोध;
	हाल BPF_LINK_DETACH:
		err = link_detach(&attr);
		अवरोध;
	हाल BPF_PROG_BIND_MAP:
		err = bpf_prog_bind_map(&attr);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
