<शैली गुरु>
//SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf-cgroup.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/bug.h>
#समावेश <linux/filter.h>
#समावेश <linux/mm.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <uapi/linux/btf.h>

#अगर_घोषित CONFIG_CGROUP_BPF

DEFINE_PER_CPU(काष्ठा bpf_cgroup_storage_info,
	       bpf_cgroup_storage_info[BPF_CGROUP_STORAGE_NEST_MAX]);

#समावेश "../cgroup/cgroup-internal.h"

#घोषणा LOCAL_STORAGE_CREATE_FLAG_MASK					\
	(BPF_F_NUMA_NODE | BPF_F_ACCESS_MASK)

काष्ठा bpf_cgroup_storage_map अणु
	काष्ठा bpf_map map;

	spinlock_t lock;
	काष्ठा rb_root root;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा bpf_cgroup_storage_map *map_to_storage(काष्ठा bpf_map *map)
अणु
	वापस container_of(map, काष्ठा bpf_cgroup_storage_map, map);
पूर्ण

अटल bool attach_type_isolated(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->key_size == माप(काष्ठा bpf_cgroup_storage_key);
पूर्ण

अटल पूर्णांक bpf_cgroup_storage_key_cmp(स्थिर काष्ठा bpf_cgroup_storage_map *map,
				      स्थिर व्योम *_key1, स्थिर व्योम *_key2)
अणु
	अगर (attach_type_isolated(&map->map)) अणु
		स्थिर काष्ठा bpf_cgroup_storage_key *key1 = _key1;
		स्थिर काष्ठा bpf_cgroup_storage_key *key2 = _key2;

		अगर (key1->cgroup_inode_id < key2->cgroup_inode_id)
			वापस -1;
		अन्यथा अगर (key1->cgroup_inode_id > key2->cgroup_inode_id)
			वापस 1;
		अन्यथा अगर (key1->attach_type < key2->attach_type)
			वापस -1;
		अन्यथा अगर (key1->attach_type > key2->attach_type)
			वापस 1;
	पूर्ण अन्यथा अणु
		स्थिर __u64 *cgroup_inode_id1 = _key1;
		स्थिर __u64 *cgroup_inode_id2 = _key2;

		अगर (*cgroup_inode_id1 < *cgroup_inode_id2)
			वापस -1;
		अन्यथा अगर (*cgroup_inode_id1 > *cgroup_inode_id2)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा bpf_cgroup_storage *
cgroup_storage_lookup(काष्ठा bpf_cgroup_storage_map *map,
		      व्योम *key, bool locked)
अणु
	काष्ठा rb_root *root = &map->root;
	काष्ठा rb_node *node;

	अगर (!locked)
		spin_lock_bh(&map->lock);

	node = root->rb_node;
	जबतक (node) अणु
		काष्ठा bpf_cgroup_storage *storage;

		storage = container_of(node, काष्ठा bpf_cgroup_storage, node);

		चयन (bpf_cgroup_storage_key_cmp(map, key, &storage->key)) अणु
		हाल -1:
			node = node->rb_left;
			अवरोध;
		हाल 1:
			node = node->rb_right;
			अवरोध;
		शेष:
			अगर (!locked)
				spin_unlock_bh(&map->lock);
			वापस storage;
		पूर्ण
	पूर्ण

	अगर (!locked)
		spin_unlock_bh(&map->lock);

	वापस शून्य;
पूर्ण

अटल पूर्णांक cgroup_storage_insert(काष्ठा bpf_cgroup_storage_map *map,
				 काष्ठा bpf_cgroup_storage *storage)
अणु
	काष्ठा rb_root *root = &map->root;
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;

	जबतक (*new) अणु
		काष्ठा bpf_cgroup_storage *this;

		this = container_of(*new, काष्ठा bpf_cgroup_storage, node);

		parent = *new;
		चयन (bpf_cgroup_storage_key_cmp(map, &storage->key, &this->key)) अणु
		हाल -1:
			new = &((*new)->rb_left);
			अवरोध;
		हाल 1:
			new = &((*new)->rb_right);
			अवरोध;
		शेष:
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	rb_link_node(&storage->node, parent, new);
	rb_insert_color(&storage->node, root);

	वापस 0;
पूर्ण

अटल व्योम *cgroup_storage_lookup_elem(काष्ठा bpf_map *_map, व्योम *key)
अणु
	काष्ठा bpf_cgroup_storage_map *map = map_to_storage(_map);
	काष्ठा bpf_cgroup_storage *storage;

	storage = cgroup_storage_lookup(map, key, false);
	अगर (!storage)
		वापस शून्य;

	वापस &READ_ONCE(storage->buf)->data[0];
पूर्ण

अटल पूर्णांक cgroup_storage_update_elem(काष्ठा bpf_map *map, व्योम *key,
				      व्योम *value, u64 flags)
अणु
	काष्ठा bpf_cgroup_storage *storage;
	काष्ठा bpf_storage_buffer *new;

	अगर (unlikely(flags & ~(BPF_F_LOCK | BPF_EXIST)))
		वापस -EINVAL;

	अगर (unlikely((flags & BPF_F_LOCK) &&
		     !map_value_has_spin_lock(map)))
		वापस -EINVAL;

	storage = cgroup_storage_lookup((काष्ठा bpf_cgroup_storage_map *)map,
					key, false);
	अगर (!storage)
		वापस -ENOENT;

	अगर (flags & BPF_F_LOCK) अणु
		copy_map_value_locked(map, storage->buf->data, value, false);
		वापस 0;
	पूर्ण

	new = bpf_map_kदो_स्मृति_node(map, माप(काष्ठा bpf_storage_buffer) +
				   map->value_size,
				   __GFP_ZERO | GFP_ATOMIC | __GFP_NOWARN,
				   map->numa_node);
	अगर (!new)
		वापस -ENOMEM;

	स_नकल(&new->data[0], value, map->value_size);
	check_and_init_map_lock(map, new->data);

	new = xchg(&storage->buf, new);
	kमुक्त_rcu(new, rcu);

	वापस 0;
पूर्ण

पूर्णांक bpf_percpu_cgroup_storage_copy(काष्ठा bpf_map *_map, व्योम *key,
				   व्योम *value)
अणु
	काष्ठा bpf_cgroup_storage_map *map = map_to_storage(_map);
	काष्ठा bpf_cgroup_storage *storage;
	पूर्णांक cpu, off = 0;
	u32 size;

	rcu_पढ़ो_lock();
	storage = cgroup_storage_lookup(map, key, false);
	अगर (!storage) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	/* per_cpu areas are zero-filled and bpf programs can only
	 * access 'value_size' of them, so copying rounded areas
	 * will not leak any kernel data
	 */
	size = round_up(_map->value_size, 8);
	क्रम_each_possible_cpu(cpu) अणु
		bpf_दीर्घ_स_नकल(value + off,
				per_cpu_ptr(storage->percpu_buf, cpu), size);
		off += size;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

पूर्णांक bpf_percpu_cgroup_storage_update(काष्ठा bpf_map *_map, व्योम *key,
				     व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_cgroup_storage_map *map = map_to_storage(_map);
	काष्ठा bpf_cgroup_storage *storage;
	पूर्णांक cpu, off = 0;
	u32 size;

	अगर (map_flags != BPF_ANY && map_flags != BPF_EXIST)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	storage = cgroup_storage_lookup(map, key, false);
	अगर (!storage) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	/* the user space will provide round_up(value_size, 8) bytes that
	 * will be copied पूर्णांकo per-cpu area. bpf programs can only access
	 * value_size of it. During lookup the same extra bytes will be
	 * वापसed or zeros which were zero-filled by percpu_alloc,
	 * so no kernel data leaks possible
	 */
	size = round_up(_map->value_size, 8);
	क्रम_each_possible_cpu(cpu) अणु
		bpf_दीर्घ_स_नकल(per_cpu_ptr(storage->percpu_buf, cpu),
				value + off, size);
		off += size;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_storage_get_next_key(काष्ठा bpf_map *_map, व्योम *key,
				       व्योम *_next_key)
अणु
	काष्ठा bpf_cgroup_storage_map *map = map_to_storage(_map);
	काष्ठा bpf_cgroup_storage *storage;

	spin_lock_bh(&map->lock);

	अगर (list_empty(&map->list))
		जाओ enoent;

	अगर (key) अणु
		storage = cgroup_storage_lookup(map, key, true);
		अगर (!storage)
			जाओ enoent;

		storage = list_next_entry(storage, list_map);
		अगर (!storage)
			जाओ enoent;
	पूर्ण अन्यथा अणु
		storage = list_first_entry(&map->list,
					 काष्ठा bpf_cgroup_storage, list_map);
	पूर्ण

	spin_unlock_bh(&map->lock);

	अगर (attach_type_isolated(&map->map)) अणु
		काष्ठा bpf_cgroup_storage_key *next = _next_key;
		*next = storage->key;
	पूर्ण अन्यथा अणु
		__u64 *next = _next_key;
		*next = storage->key.cgroup_inode_id;
	पूर्ण
	वापस 0;

enoent:
	spin_unlock_bh(&map->lock);
	वापस -ENOENT;
पूर्ण

अटल काष्ठा bpf_map *cgroup_storage_map_alloc(जोड़ bpf_attr *attr)
अणु
	पूर्णांक numa_node = bpf_map_attr_numa_node(attr);
	काष्ठा bpf_cgroup_storage_map *map;

	अगर (attr->key_size != माप(काष्ठा bpf_cgroup_storage_key) &&
	    attr->key_size != माप(__u64))
		वापस ERR_PTR(-EINVAL);

	अगर (attr->value_size == 0)
		वापस ERR_PTR(-EINVAL);

	अगर (attr->value_size > PAGE_SIZE)
		वापस ERR_PTR(-E2BIG);

	अगर (attr->map_flags & ~LOCAL_STORAGE_CREATE_FLAG_MASK ||
	    !bpf_map_flags_access_ok(attr->map_flags))
		वापस ERR_PTR(-EINVAL);

	अगर (attr->max_entries)
		/* max_entries is not used and enक्रमced to be 0 */
		वापस ERR_PTR(-EINVAL);

	map = kदो_स्मृति_node(माप(काष्ठा bpf_cgroup_storage_map),
			   __GFP_ZERO | GFP_USER | __GFP_ACCOUNT, numa_node);
	अगर (!map)
		वापस ERR_PTR(-ENOMEM);

	/* copy mandatory map attributes */
	bpf_map_init_from_attr(&map->map, attr);

	spin_lock_init(&map->lock);
	map->root = RB_ROOT;
	INIT_LIST_HEAD(&map->list);

	वापस &map->map;
पूर्ण

अटल व्योम cgroup_storage_map_मुक्त(काष्ठा bpf_map *_map)
अणु
	काष्ठा bpf_cgroup_storage_map *map = map_to_storage(_map);
	काष्ठा list_head *storages = &map->list;
	काष्ठा bpf_cgroup_storage *storage, *sपंचांगp;

	mutex_lock(&cgroup_mutex);

	list_क्रम_each_entry_safe(storage, sपंचांगp, storages, list_map) अणु
		bpf_cgroup_storage_unlink(storage);
		bpf_cgroup_storage_मुक्त(storage);
	पूर्ण

	mutex_unlock(&cgroup_mutex);

	WARN_ON(!RB_EMPTY_ROOT(&map->root));
	WARN_ON(!list_empty(&map->list));

	kमुक्त(map);
पूर्ण

अटल पूर्णांक cgroup_storage_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cgroup_storage_check_btf(स्थिर काष्ठा bpf_map *map,
				    स्थिर काष्ठा btf *btf,
				    स्थिर काष्ठा btf_type *key_type,
				    स्थिर काष्ठा btf_type *value_type)
अणु
	अगर (attach_type_isolated(map)) अणु
		काष्ठा btf_member *m;
		u32 offset, size;

		/* Key is expected to be of काष्ठा bpf_cgroup_storage_key type,
		 * which is:
		 * काष्ठा bpf_cgroup_storage_key अणु
		 *	__u64	cgroup_inode_id;
		 *	__u32	attach_type;
		 * पूर्ण;
		 */

		/*
		 * Key_type must be a काष्ठाure with two fields.
		 */
		अगर (BTF_INFO_KIND(key_type->info) != BTF_KIND_STRUCT ||
		    BTF_INFO_VLEN(key_type->info) != 2)
			वापस -EINVAL;

		/*
		 * The first field must be a 64 bit पूर्णांकeger at 0 offset.
		 */
		m = (काष्ठा btf_member *)(key_type + 1);
		size = माप_field(काष्ठा bpf_cgroup_storage_key, cgroup_inode_id);
		अगर (!btf_member_is_reg_पूर्णांक(btf, key_type, m, 0, size))
			वापस -EINVAL;

		/*
		 * The second field must be a 32 bit पूर्णांकeger at 64 bit offset.
		 */
		m++;
		offset = दुरत्व(काष्ठा bpf_cgroup_storage_key, attach_type);
		size = माप_field(काष्ठा bpf_cgroup_storage_key, attach_type);
		अगर (!btf_member_is_reg_पूर्णांक(btf, key_type, m, offset, size))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		u32 पूर्णांक_data;

		/*
		 * Key is expected to be u64, which stores the cgroup_inode_id
		 */

		अगर (BTF_INFO_KIND(key_type->info) != BTF_KIND_INT)
			वापस -EINVAL;

		पूर्णांक_data = *(u32 *)(key_type + 1);
		अगर (BTF_INT_BITS(पूर्णांक_data) != 64 || BTF_INT_OFFSET(पूर्णांक_data))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cgroup_storage_seq_show_elem(काष्ठा bpf_map *map, व्योम *key,
					 काष्ठा seq_file *m)
अणु
	क्रमागत bpf_cgroup_storage_type stype = cgroup_storage_type(map);
	काष्ठा bpf_cgroup_storage *storage;
	पूर्णांक cpu;

	rcu_पढ़ो_lock();
	storage = cgroup_storage_lookup(map_to_storage(map), key, false);
	अगर (!storage) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	btf_type_seq_show(map->btf, map->btf_key_type_id, key, m);
	stype = cgroup_storage_type(map);
	अगर (stype == BPF_CGROUP_STORAGE_SHARED) अणु
		seq_माला_दो(m, ": ");
		btf_type_seq_show(map->btf, map->btf_value_type_id,
				  &READ_ONCE(storage->buf)->data[0], m);
		seq_माला_दो(m, "\n");
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, ": {\n");
		क्रम_each_possible_cpu(cpu) अणु
			seq_म_लिखो(m, "\tcpu%d: ", cpu);
			btf_type_seq_show(map->btf, map->btf_value_type_id,
					  per_cpu_ptr(storage->percpu_buf, cpu),
					  m);
			seq_माला_दो(m, "\n");
		पूर्ण
		seq_माला_दो(m, "}\n");
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक cgroup_storage_map_btf_id;
स्थिर काष्ठा bpf_map_ops cgroup_storage_map_ops = अणु
	.map_alloc = cgroup_storage_map_alloc,
	.map_मुक्त = cgroup_storage_map_मुक्त,
	.map_get_next_key = cgroup_storage_get_next_key,
	.map_lookup_elem = cgroup_storage_lookup_elem,
	.map_update_elem = cgroup_storage_update_elem,
	.map_delete_elem = cgroup_storage_delete_elem,
	.map_check_btf = cgroup_storage_check_btf,
	.map_seq_show_elem = cgroup_storage_seq_show_elem,
	.map_btf_name = "bpf_cgroup_storage_map",
	.map_btf_id = &cgroup_storage_map_btf_id,
पूर्ण;

पूर्णांक bpf_cgroup_storage_assign(काष्ठा bpf_prog_aux *aux, काष्ठा bpf_map *_map)
अणु
	क्रमागत bpf_cgroup_storage_type stype = cgroup_storage_type(_map);

	अगर (aux->cgroup_storage[stype] &&
	    aux->cgroup_storage[stype] != _map)
		वापस -EBUSY;

	aux->cgroup_storage[stype] = _map;
	वापस 0;
पूर्ण

अटल माप_प्रकार bpf_cgroup_storage_calculate_size(काष्ठा bpf_map *map, u32 *pages)
अणु
	माप_प्रकार size;

	अगर (cgroup_storage_type(map) == BPF_CGROUP_STORAGE_SHARED) अणु
		size = माप(काष्ठा bpf_storage_buffer) + map->value_size;
		*pages = round_up(माप(काष्ठा bpf_cgroup_storage) + size,
				  PAGE_SIZE) >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		size = map->value_size;
		*pages = round_up(round_up(size, 8) * num_possible_cpus(),
				  PAGE_SIZE) >> PAGE_SHIFT;
	पूर्ण

	वापस size;
पूर्ण

काष्ठा bpf_cgroup_storage *bpf_cgroup_storage_alloc(काष्ठा bpf_prog *prog,
					क्रमागत bpf_cgroup_storage_type stype)
अणु
	स्थिर gfp_t gfp = __GFP_ZERO | GFP_USER;
	काष्ठा bpf_cgroup_storage *storage;
	काष्ठा bpf_map *map;
	माप_प्रकार size;
	u32 pages;

	map = prog->aux->cgroup_storage[stype];
	अगर (!map)
		वापस शून्य;

	size = bpf_cgroup_storage_calculate_size(map, &pages);

	storage = bpf_map_kदो_स्मृति_node(map, माप(काष्ठा bpf_cgroup_storage),
				       gfp, map->numa_node);
	अगर (!storage)
		जाओ enomem;

	अगर (stype == BPF_CGROUP_STORAGE_SHARED) अणु
		storage->buf = bpf_map_kदो_स्मृति_node(map, size, gfp,
						    map->numa_node);
		अगर (!storage->buf)
			जाओ enomem;
		check_and_init_map_lock(map, storage->buf->data);
	पूर्ण अन्यथा अणु
		storage->percpu_buf = bpf_map_alloc_percpu(map, size, 8, gfp);
		अगर (!storage->percpu_buf)
			जाओ enomem;
	पूर्ण

	storage->map = (काष्ठा bpf_cgroup_storage_map *)map;

	वापस storage;

enomem:
	kमुक्त(storage);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम मुक्त_shared_cgroup_storage_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_cgroup_storage *storage =
		container_of(rcu, काष्ठा bpf_cgroup_storage, rcu);

	kमुक्त(storage->buf);
	kमुक्त(storage);
पूर्ण

अटल व्योम मुक्त_percpu_cgroup_storage_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_cgroup_storage *storage =
		container_of(rcu, काष्ठा bpf_cgroup_storage, rcu);

	मुक्त_percpu(storage->percpu_buf);
	kमुक्त(storage);
पूर्ण

व्योम bpf_cgroup_storage_मुक्त(काष्ठा bpf_cgroup_storage *storage)
अणु
	क्रमागत bpf_cgroup_storage_type stype;
	काष्ठा bpf_map *map;

	अगर (!storage)
		वापस;

	map = &storage->map->map;
	stype = cgroup_storage_type(map);
	अगर (stype == BPF_CGROUP_STORAGE_SHARED)
		call_rcu(&storage->rcu, मुक्त_shared_cgroup_storage_rcu);
	अन्यथा
		call_rcu(&storage->rcu, मुक्त_percpu_cgroup_storage_rcu);
पूर्ण

व्योम bpf_cgroup_storage_link(काष्ठा bpf_cgroup_storage *storage,
			     काष्ठा cgroup *cgroup,
			     क्रमागत bpf_attach_type type)
अणु
	काष्ठा bpf_cgroup_storage_map *map;

	अगर (!storage)
		वापस;

	storage->key.attach_type = type;
	storage->key.cgroup_inode_id = cgroup_id(cgroup);

	map = storage->map;

	spin_lock_bh(&map->lock);
	WARN_ON(cgroup_storage_insert(map, storage));
	list_add(&storage->list_map, &map->list);
	list_add(&storage->list_cg, &cgroup->bpf.storages);
	spin_unlock_bh(&map->lock);
पूर्ण

व्योम bpf_cgroup_storage_unlink(काष्ठा bpf_cgroup_storage *storage)
अणु
	काष्ठा bpf_cgroup_storage_map *map;
	काष्ठा rb_root *root;

	अगर (!storage)
		वापस;

	map = storage->map;

	spin_lock_bh(&map->lock);
	root = &map->root;
	rb_erase(&storage->node, root);

	list_del(&storage->list_map);
	list_del(&storage->list_cg);
	spin_unlock_bh(&map->lock);
पूर्ण

#पूर्ण_अगर
