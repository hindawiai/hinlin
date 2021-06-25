<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* XSKMAP used क्रम AF_XDP sockets
 * Copyright(c) 2018 Intel Corporation.
 */

#समावेश <linux/bpf.h>
#समावेश <linux/capability.h>
#समावेश <net/xdp_sock.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#समावेश "xsk.h"

अटल काष्ठा xsk_map_node *xsk_map_node_alloc(काष्ठा xsk_map *map,
					       काष्ठा xdp_sock **map_entry)
अणु
	काष्ठा xsk_map_node *node;

	node = bpf_map_kzalloc(&map->map, माप(*node),
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_inc(&map->map);

	node->map = map;
	node->map_entry = map_entry;
	वापस node;
पूर्ण

अटल व्योम xsk_map_node_मुक्त(काष्ठा xsk_map_node *node)
अणु
	bpf_map_put(&node->map->map);
	kमुक्त(node);
पूर्ण

अटल व्योम xsk_map_sock_add(काष्ठा xdp_sock *xs, काष्ठा xsk_map_node *node)
अणु
	spin_lock_bh(&xs->map_list_lock);
	list_add_tail(&node->node, &xs->map_list);
	spin_unlock_bh(&xs->map_list_lock);
पूर्ण

अटल व्योम xsk_map_sock_delete(काष्ठा xdp_sock *xs,
				काष्ठा xdp_sock **map_entry)
अणु
	काष्ठा xsk_map_node *n, *पंचांगp;

	spin_lock_bh(&xs->map_list_lock);
	list_क्रम_each_entry_safe(n, पंचांगp, &xs->map_list, node) अणु
		अगर (map_entry == n->map_entry) अणु
			list_del(&n->node);
			xsk_map_node_मुक्त(n);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&xs->map_list_lock);
पूर्ण

अटल काष्ठा bpf_map *xsk_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा xsk_map *m;
	पूर्णांक numa_node;
	u64 size;

	अगर (!capable(CAP_NET_ADMIN))
		वापस ERR_PTR(-EPERM);

	अगर (attr->max_entries == 0 || attr->key_size != 4 ||
	    attr->value_size != 4 ||
	    attr->map_flags & ~(BPF_F_NUMA_NODE | BPF_F_RDONLY | BPF_F_WRONLY))
		वापस ERR_PTR(-EINVAL);

	numa_node = bpf_map_attr_numa_node(attr);
	size = काष्ठा_size(m, xsk_map, attr->max_entries);

	m = bpf_map_area_alloc(size, numa_node);
	अगर (!m)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&m->map, attr);
	spin_lock_init(&m->lock);

	वापस &m->map;
पूर्ण

अटल व्योम xsk_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा xsk_map *m = container_of(map, काष्ठा xsk_map, map);

	synchronize_net();
	bpf_map_area_मुक्त(m);
पूर्ण

अटल पूर्णांक xsk_map_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key)
अणु
	काष्ठा xsk_map *m = container_of(map, काष्ठा xsk_map, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = next_key;

	अगर (index >= m->map.max_entries) अणु
		*next = 0;
		वापस 0;
	पूर्ण

	अगर (index == m->map.max_entries - 1)
		वापस -ENOENT;
	*next = index + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक xsk_map_gen_lookup(काष्ठा bpf_map *map, काष्ठा bpf_insn *insn_buf)
अणु
	स्थिर पूर्णांक ret = BPF_REG_0, mp = BPF_REG_1, index = BPF_REG_2;
	काष्ठा bpf_insn *insn = insn_buf;

	*insn++ = BPF_LDX_MEM(BPF_W, ret, index, 0);
	*insn++ = BPF_JMP_IMM(BPF_JGE, ret, map->max_entries, 5);
	*insn++ = BPF_ALU64_IMM(BPF_LSH, ret, ilog2(माप(काष्ठा xsk_sock *)));
	*insn++ = BPF_ALU64_IMM(BPF_ADD, mp, दुरत्व(काष्ठा xsk_map, xsk_map));
	*insn++ = BPF_ALU64_REG(BPF_ADD, ret, mp);
	*insn++ = BPF_LDX_MEM(BPF_SIZखातापूर्ण(काष्ठा xsk_sock *), ret, ret, 0);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
	*insn++ = BPF_MOV64_IMM(ret, 0);
	वापस insn - insn_buf;
पूर्ण

अटल व्योम *__xsk_map_lookup_elem(काष्ठा bpf_map *map, u32 key)
अणु
	काष्ठा xsk_map *m = container_of(map, काष्ठा xsk_map, map);

	अगर (key >= map->max_entries)
		वापस शून्य;

	वापस READ_ONCE(m->xsk_map[key]);
पूर्ण

अटल व्योम *xsk_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस __xsk_map_lookup_elem(map, *(u32 *)key);
पूर्ण

अटल व्योम *xsk_map_lookup_elem_sys_only(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल पूर्णांक xsk_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			       u64 map_flags)
अणु
	काष्ठा xsk_map *m = container_of(map, काष्ठा xsk_map, map);
	काष्ठा xdp_sock *xs, *old_xs, **map_entry;
	u32 i = *(u32 *)key, fd = *(u32 *)value;
	काष्ठा xsk_map_node *node;
	काष्ठा socket *sock;
	पूर्णांक err;

	अगर (unlikely(map_flags > BPF_EXIST))
		वापस -EINVAL;
	अगर (unlikely(i >= m->map.max_entries))
		वापस -E2BIG;

	sock = sockfd_lookup(fd, &err);
	अगर (!sock)
		वापस err;

	अगर (sock->sk->sk_family != PF_XDP) अणु
		sockfd_put(sock);
		वापस -EOPNOTSUPP;
	पूर्ण

	xs = (काष्ठा xdp_sock *)sock->sk;

	map_entry = &m->xsk_map[i];
	node = xsk_map_node_alloc(m, map_entry);
	अगर (IS_ERR(node)) अणु
		sockfd_put(sock);
		वापस PTR_ERR(node);
	पूर्ण

	spin_lock_bh(&m->lock);
	old_xs = READ_ONCE(*map_entry);
	अगर (old_xs == xs) अणु
		err = 0;
		जाओ out;
	पूर्ण अन्यथा अगर (old_xs && map_flags == BPF_NOEXIST) अणु
		err = -EEXIST;
		जाओ out;
	पूर्ण अन्यथा अगर (!old_xs && map_flags == BPF_EXIST) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण
	xsk_map_sock_add(xs, node);
	WRITE_ONCE(*map_entry, xs);
	अगर (old_xs)
		xsk_map_sock_delete(old_xs, map_entry);
	spin_unlock_bh(&m->lock);
	sockfd_put(sock);
	वापस 0;

out:
	spin_unlock_bh(&m->lock);
	sockfd_put(sock);
	xsk_map_node_मुक्त(node);
	वापस err;
पूर्ण

अटल पूर्णांक xsk_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा xsk_map *m = container_of(map, काष्ठा xsk_map, map);
	काष्ठा xdp_sock *old_xs, **map_entry;
	पूर्णांक k = *(u32 *)key;

	अगर (k >= map->max_entries)
		वापस -EINVAL;

	spin_lock_bh(&m->lock);
	map_entry = &m->xsk_map[k];
	old_xs = xchg(map_entry, शून्य);
	अगर (old_xs)
		xsk_map_sock_delete(old_xs, map_entry);
	spin_unlock_bh(&m->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक xsk_map_redirect(काष्ठा bpf_map *map, u32 अगरindex, u64 flags)
अणु
	वापस __bpf_xdp_redirect_map(map, अगरindex, flags, __xsk_map_lookup_elem);
पूर्ण

व्योम xsk_map_try_sock_delete(काष्ठा xsk_map *map, काष्ठा xdp_sock *xs,
			     काष्ठा xdp_sock **map_entry)
अणु
	spin_lock_bh(&map->lock);
	अगर (READ_ONCE(*map_entry) == xs) अणु
		WRITE_ONCE(*map_entry, शून्य);
		xsk_map_sock_delete(xs, map_entry);
	पूर्ण
	spin_unlock_bh(&map->lock);
पूर्ण

अटल bool xsk_map_meta_equal(स्थिर काष्ठा bpf_map *meta0,
			       स्थिर काष्ठा bpf_map *meta1)
अणु
	वापस meta0->max_entries == meta1->max_entries &&
		bpf_map_meta_equal(meta0, meta1);
पूर्ण

अटल पूर्णांक xsk_map_btf_id;
स्थिर काष्ठा bpf_map_ops xsk_map_ops = अणु
	.map_meta_equal = xsk_map_meta_equal,
	.map_alloc = xsk_map_alloc,
	.map_मुक्त = xsk_map_मुक्त,
	.map_get_next_key = xsk_map_get_next_key,
	.map_lookup_elem = xsk_map_lookup_elem,
	.map_gen_lookup = xsk_map_gen_lookup,
	.map_lookup_elem_sys_only = xsk_map_lookup_elem_sys_only,
	.map_update_elem = xsk_map_update_elem,
	.map_delete_elem = xsk_map_delete_elem,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "xsk_map",
	.map_btf_id = &xsk_map_btf_id,
	.map_redirect = xsk_map_redirect,
पूर्ण;
