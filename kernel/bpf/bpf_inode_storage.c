<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Facebook
 * Copyright 2020 Google LLC.
 */

#समावेश <linux/rculist.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_local_storage.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/sock_diag.h>
#समावेश <uapi/linux/btf.h>
#समावेश <linux/bpf_lsm.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/fdtable.h>

DEFINE_BPF_STORAGE_CACHE(inode_cache);

अटल काष्ठा bpf_local_storage __rcu **
inode_storage_ptr(व्योम *owner)
अणु
	काष्ठा inode *inode = owner;
	काष्ठा bpf_storage_blob *bsb;

	bsb = bpf_inode(inode);
	अगर (!bsb)
		वापस शून्य;
	वापस &bsb->storage;
पूर्ण

अटल काष्ठा bpf_local_storage_data *inode_storage_lookup(काष्ठा inode *inode,
							   काष्ठा bpf_map *map,
							   bool cacheit_lockit)
अणु
	काष्ठा bpf_local_storage *inode_storage;
	काष्ठा bpf_local_storage_map *smap;
	काष्ठा bpf_storage_blob *bsb;

	bsb = bpf_inode(inode);
	अगर (!bsb)
		वापस शून्य;

	inode_storage = rcu_dereference(bsb->storage);
	अगर (!inode_storage)
		वापस शून्य;

	smap = (काष्ठा bpf_local_storage_map *)map;
	वापस bpf_local_storage_lookup(inode_storage, smap, cacheit_lockit);
पूर्ण

व्योम bpf_inode_storage_मुक्त(काष्ठा inode *inode)
अणु
	काष्ठा bpf_local_storage_elem *selem;
	काष्ठा bpf_local_storage *local_storage;
	bool मुक्त_inode_storage = false;
	काष्ठा bpf_storage_blob *bsb;
	काष्ठा hlist_node *n;

	bsb = bpf_inode(inode);
	अगर (!bsb)
		वापस;

	rcu_पढ़ो_lock();

	local_storage = rcu_dereference(bsb->storage);
	अगर (!local_storage) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	/* Netiher the bpf_prog nor the bpf-map's syscall
	 * could be modअगरying the local_storage->list now.
	 * Thus, no elem can be added-to or deleted-from the
	 * local_storage->list by the bpf_prog or by the bpf-map's syscall.
	 *
	 * It is racing with bpf_local_storage_map_मुक्त() alone
	 * when unlinking elem from the local_storage->list and
	 * the map's bucket->list.
	 */
	raw_spin_lock_bh(&local_storage->lock);
	hlist_क्रम_each_entry_safe(selem, n, &local_storage->list, snode) अणु
		/* Always unlink from map beक्रमe unlinking from
		 * local_storage.
		 */
		bpf_selem_unlink_map(selem);
		मुक्त_inode_storage = bpf_selem_unlink_storage_nolock(
			local_storage, selem, false);
	पूर्ण
	raw_spin_unlock_bh(&local_storage->lock);
	rcu_पढ़ो_unlock();

	/* मुक्त_inoode_storage should always be true as दीर्घ as
	 * local_storage->list was non-empty.
	 */
	अगर (मुक्त_inode_storage)
		kमुक्त_rcu(local_storage, rcu);
पूर्ण

अटल व्योम *bpf_fd_inode_storage_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा file *f;
	पूर्णांक fd;

	fd = *(पूर्णांक *)key;
	f = fget_raw(fd);
	अगर (!f)
		वापस ERR_PTR(-EBADF);

	sdata = inode_storage_lookup(f->f_inode, map, true);
	fput(f);
	वापस sdata ? sdata->data : शून्य;
पूर्ण

अटल पूर्णांक bpf_fd_inode_storage_update_elem(काष्ठा bpf_map *map, व्योम *key,
					 व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा file *f;
	पूर्णांक fd;

	fd = *(पूर्णांक *)key;
	f = fget_raw(fd);
	अगर (!f)
		वापस -EBADF;
	अगर (!inode_storage_ptr(f->f_inode)) अणु
		fput(f);
		वापस -EBADF;
	पूर्ण

	sdata = bpf_local_storage_update(f->f_inode,
					 (काष्ठा bpf_local_storage_map *)map,
					 value, map_flags);
	fput(f);
	वापस PTR_ERR_OR_ZERO(sdata);
पूर्ण

अटल पूर्णांक inode_storage_delete(काष्ठा inode *inode, काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_local_storage_data *sdata;

	sdata = inode_storage_lookup(inode, map, false);
	अगर (!sdata)
		वापस -ENOENT;

	bpf_selem_unlink(SELEM(sdata));

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fd_inode_storage_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा file *f;
	पूर्णांक fd, err;

	fd = *(पूर्णांक *)key;
	f = fget_raw(fd);
	अगर (!f)
		वापस -EBADF;

	err = inode_storage_delete(f->f_inode, map);
	fput(f);
	वापस err;
पूर्ण

BPF_CALL_4(bpf_inode_storage_get, काष्ठा bpf_map *, map, काष्ठा inode *, inode,
	   व्योम *, value, u64, flags)
अणु
	काष्ठा bpf_local_storage_data *sdata;

	अगर (flags & ~(BPF_LOCAL_STORAGE_GET_F_CREATE))
		वापस (अचिन्हित दीर्घ)शून्य;

	/* explicitly check that the inode_storage_ptr is not
	 * शून्य as inode_storage_lookup वापसs शून्य in this हाल and
	 * bpf_local_storage_update expects the owner to have a
	 * valid storage poपूर्णांकer.
	 */
	अगर (!inode || !inode_storage_ptr(inode))
		वापस (अचिन्हित दीर्घ)शून्य;

	sdata = inode_storage_lookup(inode, map, true);
	अगर (sdata)
		वापस (अचिन्हित दीर्घ)sdata->data;

	/* This helper must only called from where the inode is guaranteed
	 * to have a refcount and cannot be मुक्तd.
	 */
	अगर (flags & BPF_LOCAL_STORAGE_GET_F_CREATE) अणु
		sdata = bpf_local_storage_update(
			inode, (काष्ठा bpf_local_storage_map *)map, value,
			BPF_NOEXIST);
		वापस IS_ERR(sdata) ? (अचिन्हित दीर्घ)शून्य :
					     (अचिन्हित दीर्घ)sdata->data;
	पूर्ण

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

BPF_CALL_2(bpf_inode_storage_delete,
	   काष्ठा bpf_map *, map, काष्ठा inode *, inode)
अणु
	अगर (!inode)
		वापस -EINVAL;

	/* This helper must only called from where the inode is guaranteed
	 * to have a refcount and cannot be मुक्तd.
	 */
	वापस inode_storage_delete(inode, map);
पूर्ण

अटल पूर्णांक notsupp_get_next_key(काष्ठा bpf_map *map, व्योम *key,
				व्योम *next_key)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल काष्ठा bpf_map *inode_storage_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_local_storage_map *smap;

	smap = bpf_local_storage_map_alloc(attr);
	अगर (IS_ERR(smap))
		वापस ERR_CAST(smap);

	smap->cache_idx = bpf_local_storage_cache_idx_get(&inode_cache);
	वापस &smap->map;
पूर्ण

अटल व्योम inode_storage_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_local_storage_map *smap;

	smap = (काष्ठा bpf_local_storage_map *)map;
	bpf_local_storage_cache_idx_मुक्त(&inode_cache, smap->cache_idx);
	bpf_local_storage_map_मुक्त(smap, शून्य);
पूर्ण

अटल पूर्णांक inode_storage_map_btf_id;
स्थिर काष्ठा bpf_map_ops inode_storage_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = bpf_local_storage_map_alloc_check,
	.map_alloc = inode_storage_map_alloc,
	.map_मुक्त = inode_storage_map_मुक्त,
	.map_get_next_key = notsupp_get_next_key,
	.map_lookup_elem = bpf_fd_inode_storage_lookup_elem,
	.map_update_elem = bpf_fd_inode_storage_update_elem,
	.map_delete_elem = bpf_fd_inode_storage_delete_elem,
	.map_check_btf = bpf_local_storage_map_check_btf,
	.map_btf_name = "bpf_local_storage_map",
	.map_btf_id = &inode_storage_map_btf_id,
	.map_owner_storage_ptr = inode_storage_ptr,
पूर्ण;

BTF_ID_LIST_SINGLE(bpf_inode_storage_btf_ids, काष्ठा, inode)

स्थिर काष्ठा bpf_func_proto bpf_inode_storage_get_proto = अणु
	.func		= bpf_inode_storage_get,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_BTF_ID,
	.arg2_btf_id	= &bpf_inode_storage_btf_ids[0],
	.arg3_type	= ARG_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_inode_storage_delete_proto = अणु
	.func		= bpf_inode_storage_delete,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_BTF_ID,
	.arg2_btf_id	= &bpf_inode_storage_btf_ids[0],
पूर्ण;
