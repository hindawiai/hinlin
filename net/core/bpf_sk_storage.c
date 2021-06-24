<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook  */
#समावेश <linux/rculist.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/bpf_local_storage.h>
#समावेश <net/bpf_sk_storage.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/sock_diag.h>
#समावेश <uapi/linux/btf.h>

DEFINE_BPF_STORAGE_CACHE(sk_cache);

अटल काष्ठा bpf_local_storage_data *
bpf_sk_storage_lookup(काष्ठा sock *sk, काष्ठा bpf_map *map, bool cacheit_lockit)
अणु
	काष्ठा bpf_local_storage *sk_storage;
	काष्ठा bpf_local_storage_map *smap;

	sk_storage = rcu_dereference(sk->sk_bpf_storage);
	अगर (!sk_storage)
		वापस शून्य;

	smap = (काष्ठा bpf_local_storage_map *)map;
	वापस bpf_local_storage_lookup(sk_storage, smap, cacheit_lockit);
पूर्ण

अटल पूर्णांक bpf_sk_storage_del(काष्ठा sock *sk, काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_local_storage_data *sdata;

	sdata = bpf_sk_storage_lookup(sk, map, false);
	अगर (!sdata)
		वापस -ENOENT;

	bpf_selem_unlink(SELEM(sdata));

	वापस 0;
पूर्ण

/* Called by __sk_deकाष्ठा() & bpf_sk_storage_clone() */
व्योम bpf_sk_storage_मुक्त(काष्ठा sock *sk)
अणु
	काष्ठा bpf_local_storage_elem *selem;
	काष्ठा bpf_local_storage *sk_storage;
	bool मुक्त_sk_storage = false;
	काष्ठा hlist_node *n;

	rcu_पढ़ो_lock();
	sk_storage = rcu_dereference(sk->sk_bpf_storage);
	अगर (!sk_storage) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	/* Netiher the bpf_prog nor the bpf-map's syscall
	 * could be modअगरying the sk_storage->list now.
	 * Thus, no elem can be added-to or deleted-from the
	 * sk_storage->list by the bpf_prog or by the bpf-map's syscall.
	 *
	 * It is racing with bpf_local_storage_map_मुक्त() alone
	 * when unlinking elem from the sk_storage->list and
	 * the map's bucket->list.
	 */
	raw_spin_lock_bh(&sk_storage->lock);
	hlist_क्रम_each_entry_safe(selem, n, &sk_storage->list, snode) अणु
		/* Always unlink from map beक्रमe unlinking from
		 * sk_storage.
		 */
		bpf_selem_unlink_map(selem);
		मुक्त_sk_storage = bpf_selem_unlink_storage_nolock(sk_storage,
								  selem, true);
	पूर्ण
	raw_spin_unlock_bh(&sk_storage->lock);
	rcu_पढ़ो_unlock();

	अगर (मुक्त_sk_storage)
		kमुक्त_rcu(sk_storage, rcu);
पूर्ण

अटल व्योम bpf_sk_storage_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_local_storage_map *smap;

	smap = (काष्ठा bpf_local_storage_map *)map;
	bpf_local_storage_cache_idx_मुक्त(&sk_cache, smap->cache_idx);
	bpf_local_storage_map_मुक्त(smap, शून्य);
पूर्ण

अटल काष्ठा bpf_map *bpf_sk_storage_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_local_storage_map *smap;

	smap = bpf_local_storage_map_alloc(attr);
	अगर (IS_ERR(smap))
		वापस ERR_CAST(smap);

	smap->cache_idx = bpf_local_storage_cache_idx_get(&sk_cache);
	वापस &smap->map;
पूर्ण

अटल पूर्णांक notsupp_get_next_key(काष्ठा bpf_map *map, व्योम *key,
				व्योम *next_key)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल व्योम *bpf_fd_sk_storage_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा socket *sock;
	पूर्णांक fd, err;

	fd = *(पूर्णांक *)key;
	sock = sockfd_lookup(fd, &err);
	अगर (sock) अणु
		sdata = bpf_sk_storage_lookup(sock->sk, map, true);
		sockfd_put(sock);
		वापस sdata ? sdata->data : शून्य;
	पूर्ण

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक bpf_fd_sk_storage_update_elem(काष्ठा bpf_map *map, व्योम *key,
					 व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा socket *sock;
	पूर्णांक fd, err;

	fd = *(पूर्णांक *)key;
	sock = sockfd_lookup(fd, &err);
	अगर (sock) अणु
		sdata = bpf_local_storage_update(
			sock->sk, (काष्ठा bpf_local_storage_map *)map, value,
			map_flags);
		sockfd_put(sock);
		वापस PTR_ERR_OR_ZERO(sdata);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bpf_fd_sk_storage_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा socket *sock;
	पूर्णांक fd, err;

	fd = *(पूर्णांक *)key;
	sock = sockfd_lookup(fd, &err);
	अगर (sock) अणु
		err = bpf_sk_storage_del(sock->sk, map);
		sockfd_put(sock);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा bpf_local_storage_elem *
bpf_sk_storage_clone_elem(काष्ठा sock *newsk,
			  काष्ठा bpf_local_storage_map *smap,
			  काष्ठा bpf_local_storage_elem *selem)
अणु
	काष्ठा bpf_local_storage_elem *copy_selem;

	copy_selem = bpf_selem_alloc(smap, newsk, शून्य, true);
	अगर (!copy_selem)
		वापस शून्य;

	अगर (map_value_has_spin_lock(&smap->map))
		copy_map_value_locked(&smap->map, SDATA(copy_selem)->data,
				      SDATA(selem)->data, true);
	अन्यथा
		copy_map_value(&smap->map, SDATA(copy_selem)->data,
			       SDATA(selem)->data);

	वापस copy_selem;
पूर्ण

पूर्णांक bpf_sk_storage_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
	काष्ठा bpf_local_storage *new_sk_storage = शून्य;
	काष्ठा bpf_local_storage *sk_storage;
	काष्ठा bpf_local_storage_elem *selem;
	पूर्णांक ret = 0;

	RCU_INIT_POINTER(newsk->sk_bpf_storage, शून्य);

	rcu_पढ़ो_lock();
	sk_storage = rcu_dereference(sk->sk_bpf_storage);

	अगर (!sk_storage || hlist_empty(&sk_storage->list))
		जाओ out;

	hlist_क्रम_each_entry_rcu(selem, &sk_storage->list, snode) अणु
		काष्ठा bpf_local_storage_elem *copy_selem;
		काष्ठा bpf_local_storage_map *smap;
		काष्ठा bpf_map *map;

		smap = rcu_dereference(SDATA(selem)->smap);
		अगर (!(smap->map.map_flags & BPF_F_CLONE))
			जारी;

		/* Note that क्रम lockless listeners adding new element
		 * here can race with cleanup in bpf_local_storage_map_मुक्त.
		 * Try to grab map refcnt to make sure that it's still
		 * alive and prevent concurrent removal.
		 */
		map = bpf_map_inc_not_zero(&smap->map);
		अगर (IS_ERR(map))
			जारी;

		copy_selem = bpf_sk_storage_clone_elem(newsk, smap, selem);
		अगर (!copy_selem) अणु
			ret = -ENOMEM;
			bpf_map_put(map);
			जाओ out;
		पूर्ण

		अगर (new_sk_storage) अणु
			bpf_selem_link_map(smap, copy_selem);
			bpf_selem_link_storage_nolock(new_sk_storage, copy_selem);
		पूर्ण अन्यथा अणु
			ret = bpf_local_storage_alloc(newsk, smap, copy_selem);
			अगर (ret) अणु
				kमुक्त(copy_selem);
				atomic_sub(smap->elem_size,
					   &newsk->sk_omem_alloc);
				bpf_map_put(map);
				जाओ out;
			पूर्ण

			new_sk_storage =
				rcu_dereference(copy_selem->local_storage);
		पूर्ण
		bpf_map_put(map);
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	/* In हाल of an error, करोn't मुक्त anything explicitly here, the
	 * caller is responsible to call bpf_sk_storage_मुक्त.
	 */

	वापस ret;
पूर्ण

BPF_CALL_4(bpf_sk_storage_get, काष्ठा bpf_map *, map, काष्ठा sock *, sk,
	   व्योम *, value, u64, flags)
अणु
	काष्ठा bpf_local_storage_data *sdata;

	अगर (!sk || !sk_fullsock(sk) || flags > BPF_SK_STORAGE_GET_F_CREATE)
		वापस (अचिन्हित दीर्घ)शून्य;

	sdata = bpf_sk_storage_lookup(sk, map, true);
	अगर (sdata)
		वापस (अचिन्हित दीर्घ)sdata->data;

	अगर (flags == BPF_SK_STORAGE_GET_F_CREATE &&
	    /* Cannot add new elem to a going away sk.
	     * Otherwise, the new elem may become a leak
	     * (and also other memory issues during map
	     *  deकाष्ठाion).
	     */
	    refcount_inc_not_zero(&sk->sk_refcnt)) अणु
		sdata = bpf_local_storage_update(
			sk, (काष्ठा bpf_local_storage_map *)map, value,
			BPF_NOEXIST);
		/* sk must be a fullsock (guaranteed by verअगरier),
		 * so sock_gen_put() is unnecessary.
		 */
		sock_put(sk);
		वापस IS_ERR(sdata) ?
			(अचिन्हित दीर्घ)शून्य : (अचिन्हित दीर्घ)sdata->data;
	पूर्ण

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

BPF_CALL_2(bpf_sk_storage_delete, काष्ठा bpf_map *, map, काष्ठा sock *, sk)
अणु
	अगर (!sk || !sk_fullsock(sk))
		वापस -EINVAL;

	अगर (refcount_inc_not_zero(&sk->sk_refcnt)) अणु
		पूर्णांक err;

		err = bpf_sk_storage_del(sk, map);
		sock_put(sk);
		वापस err;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक bpf_sk_storage_अक्षरge(काष्ठा bpf_local_storage_map *smap,
				 व्योम *owner, u32 size)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)owner;

	/* same check as in sock_kदो_स्मृति() */
	अगर (size <= sysctl_opपंचांगem_max &&
	    atomic_पढ़ो(&sk->sk_omem_alloc) + size < sysctl_opपंचांगem_max) अणु
		atomic_add(size, &sk->sk_omem_alloc);
		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल व्योम bpf_sk_storage_unअक्षरge(काष्ठा bpf_local_storage_map *smap,
				    व्योम *owner, u32 size)
अणु
	काष्ठा sock *sk = owner;

	atomic_sub(size, &sk->sk_omem_alloc);
पूर्ण

अटल काष्ठा bpf_local_storage __rcu **
bpf_sk_storage_ptr(व्योम *owner)
अणु
	काष्ठा sock *sk = owner;

	वापस &sk->sk_bpf_storage;
पूर्ण

अटल पूर्णांक sk_storage_map_btf_id;
स्थिर काष्ठा bpf_map_ops sk_storage_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = bpf_local_storage_map_alloc_check,
	.map_alloc = bpf_sk_storage_map_alloc,
	.map_मुक्त = bpf_sk_storage_map_मुक्त,
	.map_get_next_key = notsupp_get_next_key,
	.map_lookup_elem = bpf_fd_sk_storage_lookup_elem,
	.map_update_elem = bpf_fd_sk_storage_update_elem,
	.map_delete_elem = bpf_fd_sk_storage_delete_elem,
	.map_check_btf = bpf_local_storage_map_check_btf,
	.map_btf_name = "bpf_local_storage_map",
	.map_btf_id = &sk_storage_map_btf_id,
	.map_local_storage_अक्षरge = bpf_sk_storage_अक्षरge,
	.map_local_storage_unअक्षरge = bpf_sk_storage_unअक्षरge,
	.map_owner_storage_ptr = bpf_sk_storage_ptr,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_sk_storage_get_proto = अणु
	.func		= bpf_sk_storage_get,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.arg3_type	= ARG_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_sk_storage_get_cg_sock_proto = अणु
	.func		= bpf_sk_storage_get,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_CTX, /* context is 'struct sock' */
	.arg3_type	= ARG_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_sk_storage_delete_proto = अणु
	.func		= bpf_sk_storage_delete,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
पूर्ण;

अटल bool bpf_sk_storage_tracing_allowed(स्थिर काष्ठा bpf_prog *prog)
अणु
	स्थिर काष्ठा btf *btf_vmlinux;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *tname;
	u32 btf_id;

	अगर (prog->aux->dst_prog)
		वापस false;

	/* Ensure the tracing program is not tracing
	 * any bpf_sk_storage*() function and also
	 * use the bpf_sk_storage_(get|delete) helper.
	 */
	चयन (prog->expected_attach_type) अणु
	हाल BPF_TRACE_ITER:
	हाल BPF_TRACE_RAW_TP:
		/* bpf_sk_storage has no trace poपूर्णांक */
		वापस true;
	हाल BPF_TRACE_FENTRY:
	हाल BPF_TRACE_FEXIT:
		btf_vmlinux = bpf_get_btf_vmlinux();
		btf_id = prog->aux->attach_btf_id;
		t = btf_type_by_id(btf_vmlinux, btf_id);
		tname = btf_name_by_offset(btf_vmlinux, t->name_off);
		वापस !!म_भेदन(tname, "bpf_sk_storage",
				 म_माप("bpf_sk_storage"));
	शेष:
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

BPF_CALL_4(bpf_sk_storage_get_tracing, काष्ठा bpf_map *, map, काष्ठा sock *, sk,
	   व्योम *, value, u64, flags)
अणु
	अगर (in_irq() || in_nmi())
		वापस (अचिन्हित दीर्घ)शून्य;

	वापस (अचिन्हित दीर्घ)____bpf_sk_storage_get(map, sk, value, flags);
पूर्ण

BPF_CALL_2(bpf_sk_storage_delete_tracing, काष्ठा bpf_map *, map,
	   काष्ठा sock *, sk)
अणु
	अगर (in_irq() || in_nmi())
		वापस -EPERM;

	वापस ____bpf_sk_storage_delete(map, sk);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sk_storage_get_tracing_proto = अणु
	.func		= bpf_sk_storage_get_tracing,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_BTF_ID,
	.arg2_btf_id	= &btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON],
	.arg3_type	= ARG_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg4_type	= ARG_ANYTHING,
	.allowed	= bpf_sk_storage_tracing_allowed,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_sk_storage_delete_tracing_proto = अणु
	.func		= bpf_sk_storage_delete_tracing,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_BTF_ID,
	.arg2_btf_id	= &btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON],
	.allowed	= bpf_sk_storage_tracing_allowed,
पूर्ण;

काष्ठा bpf_sk_storage_diag अणु
	u32 nr_maps;
	काष्ठा bpf_map *maps[];
पूर्ण;

/* The reply will be like:
 * INET_DIAG_BPF_SK_STORAGES (nla_nest)
 *	SK_DIAG_BPF_STORAGE (nla_nest)
 *		SK_DIAG_BPF_STORAGE_MAP_ID (nla_put_u32)
 *		SK_DIAG_BPF_STORAGE_MAP_VALUE (nla_reserve_64bit)
 *	SK_DIAG_BPF_STORAGE (nla_nest)
 *		SK_DIAG_BPF_STORAGE_MAP_ID (nla_put_u32)
 *		SK_DIAG_BPF_STORAGE_MAP_VALUE (nla_reserve_64bit)
 *	....
 */
अटल पूर्णांक nla_value_size(u32 value_size)
अणु
	/* SK_DIAG_BPF_STORAGE (nla_nest)
	 *	SK_DIAG_BPF_STORAGE_MAP_ID (nla_put_u32)
	 *	SK_DIAG_BPF_STORAGE_MAP_VALUE (nla_reserve_64bit)
	 */
	वापस nla_total_size(0) + nla_total_size(माप(u32)) +
		nla_total_size_64bit(value_size);
पूर्ण

व्योम bpf_sk_storage_diag_मुक्त(काष्ठा bpf_sk_storage_diag *diag)
अणु
	u32 i;

	अगर (!diag)
		वापस;

	क्रम (i = 0; i < diag->nr_maps; i++)
		bpf_map_put(diag->maps[i]);

	kमुक्त(diag);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_sk_storage_diag_मुक्त);

अटल bool diag_check_dup(स्थिर काष्ठा bpf_sk_storage_diag *diag,
			   स्थिर काष्ठा bpf_map *map)
अणु
	u32 i;

	क्रम (i = 0; i < diag->nr_maps; i++) अणु
		अगर (diag->maps[i] == map)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा bpf_sk_storage_diag *
bpf_sk_storage_diag_alloc(स्थिर काष्ठा nlattr *nla_stgs)
अणु
	काष्ठा bpf_sk_storage_diag *diag;
	काष्ठा nlattr *nla;
	u32 nr_maps = 0;
	पूर्णांक rem, err;

	/* bpf_local_storage_map is currently limited to CAP_SYS_ADMIN as
	 * the map_alloc_check() side also करोes.
	 */
	अगर (!bpf_capable())
		वापस ERR_PTR(-EPERM);

	nla_क्रम_each_nested(nla, nla_stgs, rem) अणु
		अगर (nla_type(nla) == SK_DIAG_BPF_STORAGE_REQ_MAP_FD)
			nr_maps++;
	पूर्ण

	diag = kzalloc(माप(*diag) + माप(diag->maps[0]) * nr_maps,
		       GFP_KERNEL);
	अगर (!diag)
		वापस ERR_PTR(-ENOMEM);

	nla_क्रम_each_nested(nla, nla_stgs, rem) अणु
		काष्ठा bpf_map *map;
		पूर्णांक map_fd;

		अगर (nla_type(nla) != SK_DIAG_BPF_STORAGE_REQ_MAP_FD)
			जारी;

		map_fd = nla_get_u32(nla);
		map = bpf_map_get(map_fd);
		अगर (IS_ERR(map)) अणु
			err = PTR_ERR(map);
			जाओ err_मुक्त;
		पूर्ण
		अगर (map->map_type != BPF_MAP_TYPE_SK_STORAGE) अणु
			bpf_map_put(map);
			err = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण
		अगर (diag_check_dup(diag, map)) अणु
			bpf_map_put(map);
			err = -EEXIST;
			जाओ err_मुक्त;
		पूर्ण
		diag->maps[diag->nr_maps++] = map;
	पूर्ण

	वापस diag;

err_मुक्त:
	bpf_sk_storage_diag_मुक्त(diag);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_sk_storage_diag_alloc);

अटल पूर्णांक diag_get(काष्ठा bpf_local_storage_data *sdata, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nla_stg, *nla_value;
	काष्ठा bpf_local_storage_map *smap;

	/* It cannot exceed max nlattr's payload */
	BUILD_BUG_ON(U16_MAX - NLA_HDRLEN < BPF_LOCAL_STORAGE_MAX_VALUE_SIZE);

	nla_stg = nla_nest_start(skb, SK_DIAG_BPF_STORAGE);
	अगर (!nla_stg)
		वापस -EMSGSIZE;

	smap = rcu_dereference(sdata->smap);
	अगर (nla_put_u32(skb, SK_DIAG_BPF_STORAGE_MAP_ID, smap->map.id))
		जाओ errout;

	nla_value = nla_reserve_64bit(skb, SK_DIAG_BPF_STORAGE_MAP_VALUE,
				      smap->map.value_size,
				      SK_DIAG_BPF_STORAGE_PAD);
	अगर (!nla_value)
		जाओ errout;

	अगर (map_value_has_spin_lock(&smap->map))
		copy_map_value_locked(&smap->map, nla_data(nla_value),
				      sdata->data, true);
	अन्यथा
		copy_map_value(&smap->map, nla_data(nla_value), sdata->data);

	nla_nest_end(skb, nla_stg);
	वापस 0;

errout:
	nla_nest_cancel(skb, nla_stg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक bpf_sk_storage_diag_put_all(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				       पूर्णांक stg_array_type,
				       अचिन्हित पूर्णांक *res_diag_size)
अणु
	/* stg_array_type (e.g. INET_DIAG_BPF_SK_STORAGES) */
	अचिन्हित पूर्णांक diag_size = nla_total_size(0);
	काष्ठा bpf_local_storage *sk_storage;
	काष्ठा bpf_local_storage_elem *selem;
	काष्ठा bpf_local_storage_map *smap;
	काष्ठा nlattr *nla_stgs;
	अचिन्हित पूर्णांक saved_len;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();

	sk_storage = rcu_dereference(sk->sk_bpf_storage);
	अगर (!sk_storage || hlist_empty(&sk_storage->list)) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	nla_stgs = nla_nest_start(skb, stg_array_type);
	अगर (!nla_stgs)
		/* Continue to learn diag_size */
		err = -EMSGSIZE;

	saved_len = skb->len;
	hlist_क्रम_each_entry_rcu(selem, &sk_storage->list, snode) अणु
		smap = rcu_dereference(SDATA(selem)->smap);
		diag_size += nla_value_size(smap->map.value_size);

		अगर (nla_stgs && diag_get(SDATA(selem), skb))
			/* Continue to learn diag_size */
			err = -EMSGSIZE;
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (nla_stgs) अणु
		अगर (saved_len == skb->len)
			nla_nest_cancel(skb, nla_stgs);
		अन्यथा
			nla_nest_end(skb, nla_stgs);
	पूर्ण

	अगर (diag_size == nla_total_size(0)) अणु
		*res_diag_size = 0;
		वापस 0;
	पूर्ण

	*res_diag_size = diag_size;
	वापस err;
पूर्ण

पूर्णांक bpf_sk_storage_diag_put(काष्ठा bpf_sk_storage_diag *diag,
			    काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    पूर्णांक stg_array_type,
			    अचिन्हित पूर्णांक *res_diag_size)
अणु
	/* stg_array_type (e.g. INET_DIAG_BPF_SK_STORAGES) */
	अचिन्हित पूर्णांक diag_size = nla_total_size(0);
	काष्ठा bpf_local_storage *sk_storage;
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा nlattr *nla_stgs;
	अचिन्हित पूर्णांक saved_len;
	पूर्णांक err = 0;
	u32 i;

	*res_diag_size = 0;

	/* No map has been specअगरied.  Dump all. */
	अगर (!diag->nr_maps)
		वापस bpf_sk_storage_diag_put_all(sk, skb, stg_array_type,
						   res_diag_size);

	rcu_पढ़ो_lock();
	sk_storage = rcu_dereference(sk->sk_bpf_storage);
	अगर (!sk_storage || hlist_empty(&sk_storage->list)) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	nla_stgs = nla_nest_start(skb, stg_array_type);
	अगर (!nla_stgs)
		/* Continue to learn diag_size */
		err = -EMSGSIZE;

	saved_len = skb->len;
	क्रम (i = 0; i < diag->nr_maps; i++) अणु
		sdata = bpf_local_storage_lookup(sk_storage,
				(काष्ठा bpf_local_storage_map *)diag->maps[i],
				false);

		अगर (!sdata)
			जारी;

		diag_size += nla_value_size(diag->maps[i]->value_size);

		अगर (nla_stgs && diag_get(sdata, skb))
			/* Continue to learn diag_size */
			err = -EMSGSIZE;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (nla_stgs) अणु
		अगर (saved_len == skb->len)
			nla_nest_cancel(skb, nla_stgs);
		अन्यथा
			nla_nest_end(skb, nla_stgs);
	पूर्ण

	अगर (diag_size == nla_total_size(0)) अणु
		*res_diag_size = 0;
		वापस 0;
	पूर्ण

	*res_diag_size = diag_size;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_sk_storage_diag_put);

काष्ठा bpf_iter_seq_sk_storage_map_info अणु
	काष्ठा bpf_map *map;
	अचिन्हित पूर्णांक bucket_id;
	अचिन्हित skip_elems;
पूर्ण;

अटल काष्ठा bpf_local_storage_elem *
bpf_sk_storage_map_seq_find_next(काष्ठा bpf_iter_seq_sk_storage_map_info *info,
				 काष्ठा bpf_local_storage_elem *prev_selem)
	__acquires(RCU) __releases(RCU)
अणु
	काष्ठा bpf_local_storage *sk_storage;
	काष्ठा bpf_local_storage_elem *selem;
	u32 skip_elems = info->skip_elems;
	काष्ठा bpf_local_storage_map *smap;
	u32 bucket_id = info->bucket_id;
	u32 i, count, n_buckets;
	काष्ठा bpf_local_storage_map_bucket *b;

	smap = (काष्ठा bpf_local_storage_map *)info->map;
	n_buckets = 1U << smap->bucket_log;
	अगर (bucket_id >= n_buckets)
		वापस शून्य;

	/* try to find next selem in the same bucket */
	selem = prev_selem;
	count = 0;
	जबतक (selem) अणु
		selem = hlist_entry_safe(rcu_dereference(hlist_next_rcu(&selem->map_node)),
					 काष्ठा bpf_local_storage_elem, map_node);
		अगर (!selem) अणु
			/* not found, unlock and go to the next bucket */
			b = &smap->buckets[bucket_id++];
			rcu_पढ़ो_unlock();
			skip_elems = 0;
			अवरोध;
		पूर्ण
		sk_storage = rcu_dereference(selem->local_storage);
		अगर (sk_storage) अणु
			info->skip_elems = skip_elems + count;
			वापस selem;
		पूर्ण
		count++;
	पूर्ण

	क्रम (i = bucket_id; i < (1U << smap->bucket_log); i++) अणु
		b = &smap->buckets[i];
		rcu_पढ़ो_lock();
		count = 0;
		hlist_क्रम_each_entry_rcu(selem, &b->list, map_node) अणु
			sk_storage = rcu_dereference(selem->local_storage);
			अगर (sk_storage && count >= skip_elems) अणु
				info->bucket_id = i;
				info->skip_elems = count;
				वापस selem;
			पूर्ण
			count++;
		पूर्ण
		rcu_पढ़ो_unlock();
		skip_elems = 0;
	पूर्ण

	info->bucket_id = i;
	info->skip_elems = 0;
	वापस शून्य;
पूर्ण

अटल व्योम *bpf_sk_storage_map_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_local_storage_elem *selem;

	selem = bpf_sk_storage_map_seq_find_next(seq->निजी, शून्य);
	अगर (!selem)
		वापस शून्य;

	अगर (*pos == 0)
		++*pos;
	वापस selem;
पूर्ण

अटल व्योम *bpf_sk_storage_map_seq_next(काष्ठा seq_file *seq, व्योम *v,
					 loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_sk_storage_map_info *info = seq->निजी;

	++*pos;
	++info->skip_elems;
	वापस bpf_sk_storage_map_seq_find_next(seq->निजी, v);
पूर्ण

काष्ठा bpf_iter__bpf_sk_storage_map अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा bpf_map *, map);
	__bpf_md_ptr(काष्ठा sock *, sk);
	__bpf_md_ptr(व्योम *, value);
पूर्ण;

DEFINE_BPF_ITER_FUNC(bpf_sk_storage_map, काष्ठा bpf_iter_meta *meta,
		     काष्ठा bpf_map *map, काष्ठा sock *sk,
		     व्योम *value)

अटल पूर्णांक __bpf_sk_storage_map_seq_show(काष्ठा seq_file *seq,
					 काष्ठा bpf_local_storage_elem *selem)
अणु
	काष्ठा bpf_iter_seq_sk_storage_map_info *info = seq->निजी;
	काष्ठा bpf_iter__bpf_sk_storage_map ctx = अणुपूर्ण;
	काष्ठा bpf_local_storage *sk_storage;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = 0;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, selem == शून्य);
	अगर (prog) अणु
		ctx.meta = &meta;
		ctx.map = info->map;
		अगर (selem) अणु
			sk_storage = rcu_dereference(selem->local_storage);
			ctx.sk = sk_storage->owner;
			ctx.value = SDATA(selem)->data;
		पूर्ण
		ret = bpf_iter_run_prog(prog, &ctx);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_sk_storage_map_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __bpf_sk_storage_map_seq_show(seq, v);
पूर्ण

अटल व्योम bpf_sk_storage_map_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	अगर (!v)
		(व्योम)__bpf_sk_storage_map_seq_show(seq, v);
	अन्यथा
		rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक bpf_iter_init_sk_storage_map(व्योम *priv_data,
					काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा bpf_iter_seq_sk_storage_map_info *seq_info = priv_data;

	seq_info->map = aux->map;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_iter_attach_map(काष्ठा bpf_prog *prog,
			       जोड़ bpf_iter_link_info *linfo,
			       काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक err = -EINVAL;

	अगर (!linfo->map.map_fd)
		वापस -EBADF;

	map = bpf_map_get_with_uref(linfo->map.map_fd);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	अगर (map->map_type != BPF_MAP_TYPE_SK_STORAGE)
		जाओ put_map;

	अगर (prog->aux->max_rकरोnly_access > map->value_size) अणु
		err = -EACCES;
		जाओ put_map;
	पूर्ण

	aux->map = map;
	वापस 0;

put_map:
	bpf_map_put_with_uref(map);
	वापस err;
पूर्ण

अटल व्योम bpf_iter_detach_map(काष्ठा bpf_iter_aux_info *aux)
अणु
	bpf_map_put_with_uref(aux->map);
पूर्ण

अटल स्थिर काष्ठा seq_operations bpf_sk_storage_map_seq_ops = अणु
	.start  = bpf_sk_storage_map_seq_start,
	.next   = bpf_sk_storage_map_seq_next,
	.stop   = bpf_sk_storage_map_seq_stop,
	.show   = bpf_sk_storage_map_seq_show,
पूर्ण;

अटल स्थिर काष्ठा bpf_iter_seq_info iter_seq_info = अणु
	.seq_ops		= &bpf_sk_storage_map_seq_ops,
	.init_seq_निजी	= bpf_iter_init_sk_storage_map,
	.fini_seq_निजी	= शून्य,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_sk_storage_map_info),
पूर्ण;

अटल काष्ठा bpf_iter_reg bpf_sk_storage_map_reg_info = अणु
	.target			= "bpf_sk_storage_map",
	.attach_target		= bpf_iter_attach_map,
	.detach_target		= bpf_iter_detach_map,
	.show_fdinfo		= bpf_iter_map_show_fdinfo,
	.fill_link_info		= bpf_iter_map_fill_link_info,
	.ctx_arg_info_size	= 2,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__bpf_sk_storage_map, sk),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
		अणु दुरत्व(काष्ठा bpf_iter__bpf_sk_storage_map, value),
		  PTR_TO_RDWR_BUF_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &iter_seq_info,
पूर्ण;

अटल पूर्णांक __init bpf_sk_storage_map_iter_init(व्योम)
अणु
	bpf_sk_storage_map_reg_info.ctx_arg_info[0].btf_id =
		btf_sock_ids[BTF_SOCK_TYPE_SOCK];
	वापस bpf_iter_reg_target(&bpf_sk_storage_map_reg_info);
पूर्ण
late_initcall(bpf_sk_storage_map_iter_init);
