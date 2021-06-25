<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Facebook
 */
#समावेश <linux/bpf.h>
#समावेश <linux/err.h>
#समावेश <linux/sock_diag.h>
#समावेश <net/sock_reuseport.h>

काष्ठा reuseport_array अणु
	काष्ठा bpf_map map;
	काष्ठा sock __rcu *ptrs[];
पूर्ण;

अटल काष्ठा reuseport_array *reuseport_array(काष्ठा bpf_map *map)
अणु
	वापस (काष्ठा reuseport_array *)map;
पूर्ण

/* The caller must hold the reuseport_lock */
व्योम bpf_sk_reuseport_detach(काष्ठा sock *sk)
अणु
	uपूर्णांकptr_t sk_user_data;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk_user_data = (uपूर्णांकptr_t)sk->sk_user_data;
	अगर (sk_user_data & SK_USER_DATA_BPF) अणु
		काष्ठा sock __rcu **socks;

		socks = (व्योम *)(sk_user_data & SK_USER_DATA_PTRMASK);
		WRITE_ONCE(sk->sk_user_data, शून्य);
		/*
		 * Do not move this शून्य assignment outside of
		 * sk->sk_callback_lock because there is
		 * a race with reuseport_array_मुक्त()
		 * which करोes not hold the reuseport_lock.
		 */
		RCU_INIT_POINTER(*socks, शून्य);
	पूर्ण
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल पूर्णांक reuseport_array_alloc_check(जोड़ bpf_attr *attr)
अणु
	अगर (attr->value_size != माप(u32) &&
	    attr->value_size != माप(u64))
		वापस -EINVAL;

	वापस array_map_alloc_check(attr);
पूर्ण

अटल व्योम *reuseport_array_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा reuseport_array *array = reuseport_array(map);
	u32 index = *(u32 *)key;

	अगर (unlikely(index >= array->map.max_entries))
		वापस शून्य;

	वापस rcu_dereference(array->ptrs[index]);
पूर्ण

/* Called from syscall only */
अटल पूर्णांक reuseport_array_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा reuseport_array *array = reuseport_array(map);
	u32 index = *(u32 *)key;
	काष्ठा sock *sk;
	पूर्णांक err;

	अगर (index >= map->max_entries)
		वापस -E2BIG;

	अगर (!rcu_access_poपूर्णांकer(array->ptrs[index]))
		वापस -ENOENT;

	spin_lock_bh(&reuseport_lock);

	sk = rcu_dereference_रक्षित(array->ptrs[index],
				       lockdep_is_held(&reuseport_lock));
	अगर (sk) अणु
		ग_लिखो_lock_bh(&sk->sk_callback_lock);
		WRITE_ONCE(sk->sk_user_data, शून्य);
		RCU_INIT_POINTER(array->ptrs[index], शून्य);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		err = 0;
	पूर्ण अन्यथा अणु
		err = -ENOENT;
	पूर्ण

	spin_unlock_bh(&reuseport_lock);

	वापस err;
पूर्ण

अटल व्योम reuseport_array_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा reuseport_array *array = reuseport_array(map);
	काष्ठा sock *sk;
	u32 i;

	/*
	 * ops->map_*_elem() will not be able to access this
	 * array now. Hence, this function only races with
	 * bpf_sk_reuseport_detach() which was triggerred by
	 * बंद() or disconnect().
	 *
	 * This function and bpf_sk_reuseport_detach() are
	 * both removing sk from "array".  Who हटाओs it
	 * first करोes not matter.
	 *
	 * The only concern here is bpf_sk_reuseport_detach()
	 * may access "array" which is being मुक्तd here.
	 * bpf_sk_reuseport_detach() access this "array"
	 * through sk->sk_user_data _and_ with sk->sk_callback_lock
	 * held which is enough because this "array" is not मुक्तd
	 * until all sk->sk_user_data has stopped referencing this "array".
	 *
	 * Hence, due to the above, taking "reuseport_lock" is not
	 * needed here.
	 */

	/*
	 * Since reuseport_lock is not taken, sk is accessed under
	 * rcu_पढ़ो_lock()
	 */
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < map->max_entries; i++) अणु
		sk = rcu_dereference(array->ptrs[i]);
		अगर (sk) अणु
			ग_लिखो_lock_bh(&sk->sk_callback_lock);
			/*
			 * No need क्रम WRITE_ONCE(). At this poपूर्णांक,
			 * no one is पढ़ोing it without taking the
			 * sk->sk_callback_lock.
			 */
			sk->sk_user_data = शून्य;
			ग_लिखो_unlock_bh(&sk->sk_callback_lock);
			RCU_INIT_POINTER(array->ptrs[i], शून्य);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * Once reaching here, all sk->sk_user_data is not
	 * referenceing this "array".  "array" can be मुक्तd now.
	 */
	bpf_map_area_मुक्त(array);
पूर्ण

अटल काष्ठा bpf_map *reuseport_array_alloc(जोड़ bpf_attr *attr)
अणु
	पूर्णांक numa_node = bpf_map_attr_numa_node(attr);
	काष्ठा reuseport_array *array;
	u64 array_size;

	अगर (!bpf_capable())
		वापस ERR_PTR(-EPERM);

	array_size = माप(*array);
	array_size += (u64)attr->max_entries * माप(काष्ठा sock *);

	/* allocate all map elements and zero-initialize them */
	array = bpf_map_area_alloc(array_size, numa_node);
	अगर (!array)
		वापस ERR_PTR(-ENOMEM);

	/* copy mandatory map attributes */
	bpf_map_init_from_attr(&array->map, attr);

	वापस &array->map;
पूर्ण

पूर्णांक bpf_fd_reuseport_array_lookup_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value)
अणु
	काष्ठा sock *sk;
	पूर्णांक err;

	अगर (map->value_size != माप(u64))
		वापस -ENOSPC;

	rcu_पढ़ो_lock();
	sk = reuseport_array_lookup_elem(map, key);
	अगर (sk) अणु
		*(u64 *)value = __sock_gen_cookie(sk);
		err = 0;
	पूर्ण अन्यथा अणु
		err = -ENOENT;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक
reuseport_array_update_check(स्थिर काष्ठा reuseport_array *array,
			     स्थिर काष्ठा sock *nsk,
			     स्थिर काष्ठा sock *osk,
			     स्थिर काष्ठा sock_reuseport *nsk_reuse,
			     u32 map_flags)
अणु
	अगर (osk && map_flags == BPF_NOEXIST)
		वापस -EEXIST;

	अगर (!osk && map_flags == BPF_EXIST)
		वापस -ENOENT;

	अगर (nsk->sk_protocol != IPPROTO_UDP && nsk->sk_protocol != IPPROTO_TCP)
		वापस -ENOTSUPP;

	अगर (nsk->sk_family != AF_INET && nsk->sk_family != AF_INET6)
		वापस -ENOTSUPP;

	अगर (nsk->sk_type != SOCK_STREAM && nsk->sk_type != SOCK_DGRAM)
		वापस -ENOTSUPP;

	/*
	 * sk must be hashed (i.e. listening in the TCP हाल or binded
	 * in the UDP हाल) and
	 * it must also be a SO_REUSEPORT sk (i.e. reuse cannot be शून्य).
	 *
	 * Also, sk will be used in bpf helper that is रक्षित by
	 * rcu_पढ़ो_lock().
	 */
	अगर (!sock_flag(nsk, SOCK_RCU_FREE) || !sk_hashed(nsk) || !nsk_reuse)
		वापस -EINVAL;

	/* READ_ONCE because the sk->sk_callback_lock may not be held here */
	अगर (READ_ONCE(nsk->sk_user_data))
		वापस -EBUSY;

	वापस 0;
पूर्ण

/*
 * Called from syscall only.
 * The "nsk" in the fd refcnt.
 * The "osk" and "reuse" are रक्षित by reuseport_lock.
 */
पूर्णांक bpf_fd_reuseport_array_update_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value, u64 map_flags)
अणु
	काष्ठा reuseport_array *array = reuseport_array(map);
	काष्ठा sock *मुक्त_osk = शून्य, *osk, *nsk;
	काष्ठा sock_reuseport *reuse;
	u32 index = *(u32 *)key;
	uपूर्णांकptr_t sk_user_data;
	काष्ठा socket *socket;
	पूर्णांक err, fd;

	अगर (map_flags > BPF_EXIST)
		वापस -EINVAL;

	अगर (index >= map->max_entries)
		वापस -E2BIG;

	अगर (map->value_size == माप(u64)) अणु
		u64 fd64 = *(u64 *)value;

		अगर (fd64 > S32_MAX)
			वापस -EINVAL;
		fd = fd64;
	पूर्ण अन्यथा अणु
		fd = *(पूर्णांक *)value;
	पूर्ण

	socket = sockfd_lookup(fd, &err);
	अगर (!socket)
		वापस err;

	nsk = socket->sk;
	अगर (!nsk) अणु
		err = -EINVAL;
		जाओ put_file;
	पूर्ण

	/* Quick checks beक्रमe taking reuseport_lock */
	err = reuseport_array_update_check(array, nsk,
					   rcu_access_poपूर्णांकer(array->ptrs[index]),
					   rcu_access_poपूर्णांकer(nsk->sk_reuseport_cb),
					   map_flags);
	अगर (err)
		जाओ put_file;

	spin_lock_bh(&reuseport_lock);
	/*
	 * Some of the checks only need reuseport_lock
	 * but it is करोne under sk_callback_lock also
	 * क्रम simplicity reason.
	 */
	ग_लिखो_lock_bh(&nsk->sk_callback_lock);

	osk = rcu_dereference_रक्षित(array->ptrs[index],
					lockdep_is_held(&reuseport_lock));
	reuse = rcu_dereference_रक्षित(nsk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	err = reuseport_array_update_check(array, nsk, osk, reuse, map_flags);
	अगर (err)
		जाओ put_file_unlock;

	sk_user_data = (uपूर्णांकptr_t)&array->ptrs[index] | SK_USER_DATA_NOCOPY |
		SK_USER_DATA_BPF;
	WRITE_ONCE(nsk->sk_user_data, (व्योम *)sk_user_data);
	rcu_assign_poपूर्णांकer(array->ptrs[index], nsk);
	मुक्त_osk = osk;
	err = 0;

put_file_unlock:
	ग_लिखो_unlock_bh(&nsk->sk_callback_lock);

	अगर (मुक्त_osk) अणु
		ग_लिखो_lock_bh(&मुक्त_osk->sk_callback_lock);
		WRITE_ONCE(मुक्त_osk->sk_user_data, शून्य);
		ग_लिखो_unlock_bh(&मुक्त_osk->sk_callback_lock);
	पूर्ण

	spin_unlock_bh(&reuseport_lock);
put_file:
	fput(socket->file);
	वापस err;
पूर्ण

/* Called from syscall */
अटल पूर्णांक reuseport_array_get_next_key(काष्ठा bpf_map *map, व्योम *key,
					व्योम *next_key)
अणु
	काष्ठा reuseport_array *array = reuseport_array(map);
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

अटल पूर्णांक reuseport_array_map_btf_id;
स्थिर काष्ठा bpf_map_ops reuseport_array_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = reuseport_array_alloc_check,
	.map_alloc = reuseport_array_alloc,
	.map_मुक्त = reuseport_array_मुक्त,
	.map_lookup_elem = reuseport_array_lookup_elem,
	.map_get_next_key = reuseport_array_get_next_key,
	.map_delete_elem = reuseport_array_delete_elem,
	.map_btf_name = "reuseport_array",
	.map_btf_id = &reuseport_array_map_btf_id,
पूर्ण;
