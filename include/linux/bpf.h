<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 */
#अगर_अघोषित _LINUX_BPF_H
#घोषणा _LINUX_BPF_H 1

#समावेश <uapi/linux/bpf.h>

#समावेश <linux/workqueue.h>
#समावेश <linux/file.h>
#समावेश <linux/percpu.h>
#समावेश <linux/err.h>
#समावेश <linux/rbtree_latch.h>
#समावेश <linux/numa.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/refcount.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/capability.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu-refcount.h>

काष्ठा bpf_verअगरier_env;
काष्ठा bpf_verअगरier_log;
काष्ठा perf_event;
काष्ठा bpf_prog;
काष्ठा bpf_prog_aux;
काष्ठा bpf_map;
काष्ठा sock;
काष्ठा seq_file;
काष्ठा btf;
काष्ठा btf_type;
काष्ठा exception_table_entry;
काष्ठा seq_operations;
काष्ठा bpf_iter_aux_info;
काष्ठा bpf_local_storage;
काष्ठा bpf_local_storage_map;
काष्ठा kobject;
काष्ठा mem_cgroup;
काष्ठा module;
काष्ठा bpf_func_state;

बाह्य काष्ठा idr btf_idr;
बाह्य spinlock_t btf_idr_lock;
बाह्य काष्ठा kobject *btf_kobj;

प्रकार पूर्णांक (*bpf_iter_init_seq_priv_t)(व्योम *निजी_data,
					काष्ठा bpf_iter_aux_info *aux);
प्रकार व्योम (*bpf_iter_fini_seq_priv_t)(व्योम *निजी_data);
काष्ठा bpf_iter_seq_info अणु
	स्थिर काष्ठा seq_operations *seq_ops;
	bpf_iter_init_seq_priv_t init_seq_निजी;
	bpf_iter_fini_seq_priv_t fini_seq_निजी;
	u32 seq_priv_size;
पूर्ण;

/* map is generic key/value storage optionally accessible by eBPF programs */
काष्ठा bpf_map_ops अणु
	/* funcs callable from userspace (via syscall) */
	पूर्णांक (*map_alloc_check)(जोड़ bpf_attr *attr);
	काष्ठा bpf_map *(*map_alloc)(जोड़ bpf_attr *attr);
	व्योम (*map_release)(काष्ठा bpf_map *map, काष्ठा file *map_file);
	व्योम (*map_मुक्त)(काष्ठा bpf_map *map);
	पूर्णांक (*map_get_next_key)(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key);
	व्योम (*map_release_uref)(काष्ठा bpf_map *map);
	व्योम *(*map_lookup_elem_sys_only)(काष्ठा bpf_map *map, व्योम *key);
	पूर्णांक (*map_lookup_batch)(काष्ठा bpf_map *map, स्थिर जोड़ bpf_attr *attr,
				जोड़ bpf_attr __user *uattr);
	पूर्णांक (*map_lookup_and_delete_batch)(काष्ठा bpf_map *map,
					   स्थिर जोड़ bpf_attr *attr,
					   जोड़ bpf_attr __user *uattr);
	पूर्णांक (*map_update_batch)(काष्ठा bpf_map *map, स्थिर जोड़ bpf_attr *attr,
				जोड़ bpf_attr __user *uattr);
	पूर्णांक (*map_delete_batch)(काष्ठा bpf_map *map, स्थिर जोड़ bpf_attr *attr,
				जोड़ bpf_attr __user *uattr);

	/* funcs callable from userspace and from eBPF programs */
	व्योम *(*map_lookup_elem)(काष्ठा bpf_map *map, व्योम *key);
	पूर्णांक (*map_update_elem)(काष्ठा bpf_map *map, व्योम *key, व्योम *value, u64 flags);
	पूर्णांक (*map_delete_elem)(काष्ठा bpf_map *map, व्योम *key);
	पूर्णांक (*map_push_elem)(काष्ठा bpf_map *map, व्योम *value, u64 flags);
	पूर्णांक (*map_pop_elem)(काष्ठा bpf_map *map, व्योम *value);
	पूर्णांक (*map_peek_elem)(काष्ठा bpf_map *map, व्योम *value);

	/* funcs called by prog_array and perf_event_array map */
	व्योम *(*map_fd_get_ptr)(काष्ठा bpf_map *map, काष्ठा file *map_file,
				पूर्णांक fd);
	व्योम (*map_fd_put_ptr)(व्योम *ptr);
	पूर्णांक (*map_gen_lookup)(काष्ठा bpf_map *map, काष्ठा bpf_insn *insn_buf);
	u32 (*map_fd_sys_lookup_elem)(व्योम *ptr);
	व्योम (*map_seq_show_elem)(काष्ठा bpf_map *map, व्योम *key,
				  काष्ठा seq_file *m);
	पूर्णांक (*map_check_btf)(स्थिर काष्ठा bpf_map *map,
			     स्थिर काष्ठा btf *btf,
			     स्थिर काष्ठा btf_type *key_type,
			     स्थिर काष्ठा btf_type *value_type);

	/* Prog poke tracking helpers. */
	पूर्णांक (*map_poke_track)(काष्ठा bpf_map *map, काष्ठा bpf_prog_aux *aux);
	व्योम (*map_poke_untrack)(काष्ठा bpf_map *map, काष्ठा bpf_prog_aux *aux);
	व्योम (*map_poke_run)(काष्ठा bpf_map *map, u32 key, काष्ठा bpf_prog *old,
			     काष्ठा bpf_prog *new);

	/* Direct value access helpers. */
	पूर्णांक (*map_direct_value_addr)(स्थिर काष्ठा bpf_map *map,
				     u64 *imm, u32 off);
	पूर्णांक (*map_direct_value_meta)(स्थिर काष्ठा bpf_map *map,
				     u64 imm, u32 *off);
	पूर्णांक (*map_mmap)(काष्ठा bpf_map *map, काष्ठा vm_area_काष्ठा *vma);
	__poll_t (*map_poll)(काष्ठा bpf_map *map, काष्ठा file *filp,
			     काष्ठा poll_table_काष्ठा *pts);

	/* Functions called by bpf_local_storage maps */
	पूर्णांक (*map_local_storage_अक्षरge)(काष्ठा bpf_local_storage_map *smap,
					व्योम *owner, u32 size);
	व्योम (*map_local_storage_unअक्षरge)(काष्ठा bpf_local_storage_map *smap,
					   व्योम *owner, u32 size);
	काष्ठा bpf_local_storage __rcu ** (*map_owner_storage_ptr)(व्योम *owner);

	/* Misc helpers.*/
	पूर्णांक (*map_redirect)(काष्ठा bpf_map *map, u32 अगरindex, u64 flags);

	/* map_meta_equal must be implemented क्रम maps that can be
	 * used as an inner map.  It is a runसमय check to ensure
	 * an inner map can be inserted to an outer map.
	 *
	 * Some properties of the inner map has been used during the
	 * verअगरication समय.  When inserting an inner map at the runसमय,
	 * map_meta_equal has to ensure the inserting map has the same
	 * properties that the verअगरier has used earlier.
	 */
	bool (*map_meta_equal)(स्थिर काष्ठा bpf_map *meta0,
			       स्थिर काष्ठा bpf_map *meta1);


	पूर्णांक (*map_set_क्रम_each_callback_args)(काष्ठा bpf_verअगरier_env *env,
					      काष्ठा bpf_func_state *caller,
					      काष्ठा bpf_func_state *callee);
	पूर्णांक (*map_क्रम_each_callback)(काष्ठा bpf_map *map, व्योम *callback_fn,
				     व्योम *callback_ctx, u64 flags);

	/* BTF name and id of काष्ठा allocated by map_alloc */
	स्थिर अक्षर * स्थिर map_btf_name;
	पूर्णांक *map_btf_id;

	/* bpf_iter info used to खोलो a seq_file */
	स्थिर काष्ठा bpf_iter_seq_info *iter_seq_info;
पूर्ण;

काष्ठा bpf_map अणु
	/* The first two cachelines with पढ़ो-mostly members of which some
	 * are also accessed in fast-path (e.g. ops, max_entries).
	 */
	स्थिर काष्ठा bpf_map_ops *ops ____cacheline_aligned;
	काष्ठा bpf_map *inner_map_meta;
#अगर_घोषित CONFIG_SECURITY
	व्योम *security;
#पूर्ण_अगर
	क्रमागत bpf_map_type map_type;
	u32 key_size;
	u32 value_size;
	u32 max_entries;
	u32 map_flags;
	पूर्णांक spin_lock_off; /* >=0 valid offset, <0 error */
	u32 id;
	पूर्णांक numa_node;
	u32 btf_key_type_id;
	u32 btf_value_type_id;
	काष्ठा btf *btf;
#अगर_घोषित CONFIG_MEMCG_KMEM
	काष्ठा mem_cgroup *memcg;
#पूर्ण_अगर
	अक्षर name[BPF_OBJ_NAME_LEN];
	u32 btf_vmlinux_value_type_id;
	bool bypass_spec_v1;
	bool frozen; /* ग_लिखो-once; ग_लिखो-रक्षित by मुक्तze_mutex */
	/* 22 bytes hole */

	/* The 3rd and 4th cacheline with misc members to aव्योम false sharing
	 * particularly with refcounting.
	 */
	atomic64_t refcnt ____cacheline_aligned;
	atomic64_t usercnt;
	काष्ठा work_काष्ठा work;
	काष्ठा mutex मुक्तze_mutex;
	u64 ग_लिखोcnt; /* writable mmap cnt; रक्षित by मुक्तze_mutex */
पूर्ण;

अटल अंतरभूत bool map_value_has_spin_lock(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->spin_lock_off >= 0;
पूर्ण

अटल अंतरभूत व्योम check_and_init_map_lock(काष्ठा bpf_map *map, व्योम *dst)
अणु
	अगर (likely(!map_value_has_spin_lock(map)))
		वापस;
	*(काष्ठा bpf_spin_lock *)(dst + map->spin_lock_off) =
		(काष्ठा bpf_spin_lock)अणुपूर्ण;
पूर्ण

/* copy everything but bpf_spin_lock */
अटल अंतरभूत व्योम copy_map_value(काष्ठा bpf_map *map, व्योम *dst, व्योम *src)
अणु
	अगर (unlikely(map_value_has_spin_lock(map))) अणु
		u32 off = map->spin_lock_off;

		स_नकल(dst, src, off);
		स_नकल(dst + off + माप(काष्ठा bpf_spin_lock),
		       src + off + माप(काष्ठा bpf_spin_lock),
		       map->value_size - off - माप(काष्ठा bpf_spin_lock));
	पूर्ण अन्यथा अणु
		स_नकल(dst, src, map->value_size);
	पूर्ण
पूर्ण
व्योम copy_map_value_locked(काष्ठा bpf_map *map, व्योम *dst, व्योम *src,
			   bool lock_src);
पूर्णांक bpf_obj_name_cpy(अक्षर *dst, स्थिर अक्षर *src, अचिन्हित पूर्णांक size);

काष्ठा bpf_offload_dev;
काष्ठा bpf_offloaded_map;

काष्ठा bpf_map_dev_ops अणु
	पूर्णांक (*map_get_next_key)(काष्ठा bpf_offloaded_map *map,
				व्योम *key, व्योम *next_key);
	पूर्णांक (*map_lookup_elem)(काष्ठा bpf_offloaded_map *map,
			       व्योम *key, व्योम *value);
	पूर्णांक (*map_update_elem)(काष्ठा bpf_offloaded_map *map,
			       व्योम *key, व्योम *value, u64 flags);
	पूर्णांक (*map_delete_elem)(काष्ठा bpf_offloaded_map *map, व्योम *key);
पूर्ण;

काष्ठा bpf_offloaded_map अणु
	काष्ठा bpf_map map;
	काष्ठा net_device *netdev;
	स्थिर काष्ठा bpf_map_dev_ops *dev_ops;
	व्योम *dev_priv;
	काष्ठा list_head offloads;
पूर्ण;

अटल अंतरभूत काष्ठा bpf_offloaded_map *map_to_offmap(काष्ठा bpf_map *map)
अणु
	वापस container_of(map, काष्ठा bpf_offloaded_map, map);
पूर्ण

अटल अंतरभूत bool bpf_map_offload_neutral(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->map_type == BPF_MAP_TYPE_PERF_EVENT_ARRAY;
पूर्ण

अटल अंतरभूत bool bpf_map_support_seq_show(स्थिर काष्ठा bpf_map *map)
अणु
	वापस (map->btf_value_type_id || map->btf_vmlinux_value_type_id) &&
		map->ops->map_seq_show_elem;
पूर्ण

पूर्णांक map_check_no_btf(स्थिर काष्ठा bpf_map *map,
		     स्थिर काष्ठा btf *btf,
		     स्थिर काष्ठा btf_type *key_type,
		     स्थिर काष्ठा btf_type *value_type);

bool bpf_map_meta_equal(स्थिर काष्ठा bpf_map *meta0,
			स्थिर काष्ठा bpf_map *meta1);

बाह्य स्थिर काष्ठा bpf_map_ops bpf_map_offload_ops;

/* function argument स्थिरraपूर्णांकs */
क्रमागत bpf_arg_type अणु
	ARG_DONTCARE = 0,	/* unused argument in helper function */

	/* the following स्थिरraपूर्णांकs used to prototype
	 * bpf_map_lookup/update/delete_elem() functions
	 */
	ARG_CONST_MAP_PTR,	/* स्थिर argument used as poपूर्णांकer to bpf_map */
	ARG_PTR_TO_MAP_KEY,	/* poपूर्णांकer to stack used as map key */
	ARG_PTR_TO_MAP_VALUE,	/* poपूर्णांकer to stack used as map value */
	ARG_PTR_TO_UNINIT_MAP_VALUE,	/* poपूर्णांकer to valid memory used to store a map value */
	ARG_PTR_TO_MAP_VALUE_OR_शून्य,	/* poपूर्णांकer to stack used as map value or शून्य */

	/* the following स्थिरraपूर्णांकs used to prototype bpf_स_भेद() and other
	 * functions that access data on eBPF program stack
	 */
	ARG_PTR_TO_MEM,		/* poपूर्णांकer to valid memory (stack, packet, map value) */
	ARG_PTR_TO_MEM_OR_शून्य, /* poपूर्णांकer to valid memory or शून्य */
	ARG_PTR_TO_UNINIT_MEM,	/* poपूर्णांकer to memory करोes not need to be initialized,
				 * helper function must fill all bytes or clear
				 * them in error हाल.
				 */

	ARG_CONST_SIZE,		/* number of bytes accessed from memory */
	ARG_CONST_SIZE_OR_ZERO,	/* number of bytes accessed from memory or 0 */

	ARG_PTR_TO_CTX,		/* poपूर्णांकer to context */
	ARG_PTR_TO_CTX_OR_शून्य,	/* poपूर्णांकer to context or शून्य */
	ARG_ANYTHING,		/* any (initialized) argument is ok */
	ARG_PTR_TO_SPIN_LOCK,	/* poपूर्णांकer to bpf_spin_lock */
	ARG_PTR_TO_SOCK_COMMON,	/* poपूर्णांकer to sock_common */
	ARG_PTR_TO_INT,		/* poपूर्णांकer to पूर्णांक */
	ARG_PTR_TO_LONG,	/* poपूर्णांकer to दीर्घ */
	ARG_PTR_TO_SOCKET,	/* poपूर्णांकer to bpf_sock (fullsock) */
	ARG_PTR_TO_SOCKET_OR_शून्य,	/* poपूर्णांकer to bpf_sock (fullsock) or शून्य */
	ARG_PTR_TO_BTF_ID,	/* poपूर्णांकer to in-kernel काष्ठा */
	ARG_PTR_TO_ALLOC_MEM,	/* poपूर्णांकer to dynamically allocated memory */
	ARG_PTR_TO_ALLOC_MEM_OR_शून्य,	/* poपूर्णांकer to dynamically allocated memory or शून्य */
	ARG_CONST_ALLOC_SIZE_OR_ZERO,	/* number of allocated bytes requested */
	ARG_PTR_TO_BTF_ID_SOCK_COMMON,	/* poपूर्णांकer to in-kernel sock_common or bpf-mirrored bpf_sock */
	ARG_PTR_TO_PERCPU_BTF_ID,	/* poपूर्णांकer to in-kernel percpu type */
	ARG_PTR_TO_FUNC,	/* poपूर्णांकer to a bpf program function */
	ARG_PTR_TO_STACK_OR_शून्य,	/* poपूर्णांकer to stack or शून्य */
	ARG_PTR_TO_CONST_STR,	/* poपूर्णांकer to a null terminated पढ़ो-only string */
	__BPF_ARG_TYPE_MAX,
पूर्ण;

/* type of values वापसed from helper functions */
क्रमागत bpf_वापस_type अणु
	RET_INTEGER,			/* function वापसs पूर्णांकeger */
	RET_VOID,			/* function करोesn't वापस anything */
	RET_PTR_TO_MAP_VALUE,		/* वापसs a poपूर्णांकer to map elem value */
	RET_PTR_TO_MAP_VALUE_OR_शून्य,	/* वापसs a poपूर्णांकer to map elem value or शून्य */
	RET_PTR_TO_SOCKET_OR_शून्य,	/* वापसs a poपूर्णांकer to a socket or शून्य */
	RET_PTR_TO_TCP_SOCK_OR_शून्य,	/* वापसs a poपूर्णांकer to a tcp_sock or शून्य */
	RET_PTR_TO_SOCK_COMMON_OR_शून्य,	/* वापसs a poपूर्णांकer to a sock_common or शून्य */
	RET_PTR_TO_ALLOC_MEM_OR_शून्य,	/* वापसs a poपूर्णांकer to dynamically allocated memory or शून्य */
	RET_PTR_TO_BTF_ID_OR_शून्य,	/* वापसs a poपूर्णांकer to a btf_id or शून्य */
	RET_PTR_TO_MEM_OR_BTF_ID_OR_शून्य, /* वापसs a poपूर्णांकer to a valid memory or a btf_id or शून्य */
	RET_PTR_TO_MEM_OR_BTF_ID,	/* वापसs a poपूर्णांकer to a valid memory or a btf_id */
	RET_PTR_TO_BTF_ID,		/* वापसs a poपूर्णांकer to a btf_id */
पूर्ण;

/* eBPF function prototype used by verअगरier to allow BPF_CALLs from eBPF programs
 * to in-kernel helper functions and क्रम adjusting imm32 field in BPF_CALL
 * inकाष्ठाions after verअगरying
 */
काष्ठा bpf_func_proto अणु
	u64 (*func)(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5);
	bool gpl_only;
	bool pkt_access;
	क्रमागत bpf_वापस_type ret_type;
	जोड़ अणु
		काष्ठा अणु
			क्रमागत bpf_arg_type arg1_type;
			क्रमागत bpf_arg_type arg2_type;
			क्रमागत bpf_arg_type arg3_type;
			क्रमागत bpf_arg_type arg4_type;
			क्रमागत bpf_arg_type arg5_type;
		पूर्ण;
		क्रमागत bpf_arg_type arg_type[5];
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 *arg1_btf_id;
			u32 *arg2_btf_id;
			u32 *arg3_btf_id;
			u32 *arg4_btf_id;
			u32 *arg5_btf_id;
		पूर्ण;
		u32 *arg_btf_id[5];
	पूर्ण;
	पूर्णांक *ret_btf_id; /* वापस value btf_id */
	bool (*allowed)(स्थिर काष्ठा bpf_prog *prog);
पूर्ण;

/* bpf_context is पूर्णांकentionally undefined काष्ठाure. Poपूर्णांकer to bpf_context is
 * the first argument to eBPF programs.
 * For socket filters: 'struct bpf_context *' == 'struct sk_buff *'
 */
काष्ठा bpf_context;

क्रमागत bpf_access_type अणु
	BPF_READ = 1,
	BPF_WRITE = 2
पूर्ण;

/* types of values stored in eBPF रेजिस्टरs */
/* Poपूर्णांकer types represent:
 * poपूर्णांकer
 * poपूर्णांकer + imm
 * poपूर्णांकer + (u16) var
 * poपूर्णांकer + (u16) var + imm
 * अगर (range > 0) then [ptr, ptr + range - off) is safe to access
 * अगर (id > 0) means that some 'var' was added
 * अगर (off > 0) means that 'imm' was added
 */
क्रमागत bpf_reg_type अणु
	NOT_INIT = 0,		 /* nothing was written पूर्णांकo रेजिस्टर */
	SCALAR_VALUE,		 /* reg करोesn't contain a valid poपूर्णांकer */
	PTR_TO_CTX,		 /* reg poपूर्णांकs to bpf_context */
	CONST_PTR_TO_MAP,	 /* reg poपूर्णांकs to काष्ठा bpf_map */
	PTR_TO_MAP_VALUE,	 /* reg poपूर्णांकs to map element value */
	PTR_TO_MAP_VALUE_OR_शून्य,/* poपूर्णांकs to map elem value or शून्य */
	PTR_TO_STACK,		 /* reg == frame_poपूर्णांकer + offset */
	PTR_TO_PACKET_META,	 /* skb->data - meta_len */
	PTR_TO_PACKET,		 /* reg poपूर्णांकs to skb->data */
	PTR_TO_PACKET_END,	 /* skb->data + headlen */
	PTR_TO_FLOW_KEYS,	 /* reg poपूर्णांकs to bpf_flow_keys */
	PTR_TO_SOCKET,		 /* reg poपूर्णांकs to काष्ठा bpf_sock */
	PTR_TO_SOCKET_OR_शून्य,	 /* reg poपूर्णांकs to काष्ठा bpf_sock or शून्य */
	PTR_TO_SOCK_COMMON,	 /* reg poपूर्णांकs to sock_common */
	PTR_TO_SOCK_COMMON_OR_शून्य, /* reg poपूर्णांकs to sock_common or शून्य */
	PTR_TO_TCP_SOCK,	 /* reg poपूर्णांकs to काष्ठा tcp_sock */
	PTR_TO_TCP_SOCK_OR_शून्य, /* reg poपूर्णांकs to काष्ठा tcp_sock or शून्य */
	PTR_TO_TP_BUFFER,	 /* reg poपूर्णांकs to a writable raw tp's buffer */
	PTR_TO_XDP_SOCK,	 /* reg poपूर्णांकs to काष्ठा xdp_sock */
	/* PTR_TO_BTF_ID poपूर्णांकs to a kernel काष्ठा that करोes not need
	 * to be null checked by the BPF program. This करोes not imply the
	 * poपूर्णांकer is _not_ null and in practice this can easily be a null
	 * poपूर्णांकer when पढ़ोing poपूर्णांकer chains. The assumption is program
	 * context will handle null poपूर्णांकer dereference typically via fault
	 * handling. The verअगरier must keep this in mind and can make no
	 * assumptions about null or non-null when करोing branch analysis.
	 * Further, when passed पूर्णांकo helpers the helpers can not, without
	 * additional context, assume the value is non-null.
	 */
	PTR_TO_BTF_ID,
	/* PTR_TO_BTF_ID_OR_शून्य poपूर्णांकs to a kernel काष्ठा that has not
	 * been checked क्रम null. Used primarily to inक्रमm the verअगरier
	 * an explicit null check is required क्रम this काष्ठा.
	 */
	PTR_TO_BTF_ID_OR_शून्य,
	PTR_TO_MEM,		 /* reg poपूर्णांकs to valid memory region */
	PTR_TO_MEM_OR_शून्य,	 /* reg poपूर्णांकs to valid memory region or शून्य */
	PTR_TO_RDONLY_BUF,	 /* reg poपूर्णांकs to a पढ़ोonly buffer */
	PTR_TO_RDONLY_BUF_OR_शून्य, /* reg poपूर्णांकs to a पढ़ोonly buffer or शून्य */
	PTR_TO_RDWR_BUF,	 /* reg poपूर्णांकs to a पढ़ो/ग_लिखो buffer */
	PTR_TO_RDWR_BUF_OR_शून्य, /* reg poपूर्णांकs to a पढ़ो/ग_लिखो buffer or शून्य */
	PTR_TO_PERCPU_BTF_ID,	 /* reg poपूर्णांकs to a percpu kernel variable */
	PTR_TO_FUNC,		 /* reg poपूर्णांकs to a bpf program function */
	PTR_TO_MAP_KEY,		 /* reg poपूर्णांकs to a map element key */
	__BPF_REG_TYPE_MAX,
पूर्ण;

/* The inक्रमmation passed from prog-specअगरic *_is_valid_access
 * back to the verअगरier.
 */
काष्ठा bpf_insn_access_aux अणु
	क्रमागत bpf_reg_type reg_type;
	जोड़ अणु
		पूर्णांक ctx_field_size;
		काष्ठा अणु
			काष्ठा btf *btf;
			u32 btf_id;
		पूर्ण;
	पूर्ण;
	काष्ठा bpf_verअगरier_log *log; /* क्रम verbose logs */
पूर्ण;

अटल अंतरभूत व्योम
bpf_ctx_record_field_size(काष्ठा bpf_insn_access_aux *aux, u32 size)
अणु
	aux->ctx_field_size = size;
पूर्ण

काष्ठा bpf_prog_ops अणु
	पूर्णांक (*test_run)(काष्ठा bpf_prog *prog, स्थिर जोड़ bpf_attr *kattr,
			जोड़ bpf_attr __user *uattr);
पूर्ण;

काष्ठा bpf_verअगरier_ops अणु
	/* वापस eBPF function prototype क्रम verअगरication */
	स्थिर काष्ठा bpf_func_proto *
	(*get_func_proto)(क्रमागत bpf_func_id func_id,
			  स्थिर काष्ठा bpf_prog *prog);

	/* वापस true अगर 'size' wide access at offset 'off' within bpf_context
	 * with 'type' (पढ़ो or ग_लिखो) is allowed
	 */
	bool (*is_valid_access)(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				स्थिर काष्ठा bpf_prog *prog,
				काष्ठा bpf_insn_access_aux *info);
	पूर्णांक (*gen_prologue)(काष्ठा bpf_insn *insn, bool direct_ग_लिखो,
			    स्थिर काष्ठा bpf_prog *prog);
	पूर्णांक (*gen_ld_असल)(स्थिर काष्ठा bpf_insn *orig,
			  काष्ठा bpf_insn *insn_buf);
	u32 (*convert_ctx_access)(क्रमागत bpf_access_type type,
				  स्थिर काष्ठा bpf_insn *src,
				  काष्ठा bpf_insn *dst,
				  काष्ठा bpf_prog *prog, u32 *target_size);
	पूर्णांक (*btf_काष्ठा_access)(काष्ठा bpf_verअगरier_log *log,
				 स्थिर काष्ठा btf *btf,
				 स्थिर काष्ठा btf_type *t, पूर्णांक off, पूर्णांक size,
				 क्रमागत bpf_access_type atype,
				 u32 *next_btf_id);
	bool (*check_kfunc_call)(u32 kfunc_btf_id);
पूर्ण;

काष्ठा bpf_prog_offload_ops अणु
	/* verअगरier basic callbacks */
	पूर्णांक (*insn_hook)(काष्ठा bpf_verअगरier_env *env,
			 पूर्णांक insn_idx, पूर्णांक prev_insn_idx);
	पूर्णांक (*finalize)(काष्ठा bpf_verअगरier_env *env);
	/* verअगरier optimization callbacks (called after .finalize) */
	पूर्णांक (*replace_insn)(काष्ठा bpf_verअगरier_env *env, u32 off,
			    काष्ठा bpf_insn *insn);
	पूर्णांक (*हटाओ_insns)(काष्ठा bpf_verअगरier_env *env, u32 off, u32 cnt);
	/* program management callbacks */
	पूर्णांक (*prepare)(काष्ठा bpf_prog *prog);
	पूर्णांक (*translate)(काष्ठा bpf_prog *prog);
	व्योम (*destroy)(काष्ठा bpf_prog *prog);
पूर्ण;

काष्ठा bpf_prog_offload अणु
	काष्ठा bpf_prog		*prog;
	काष्ठा net_device	*netdev;
	काष्ठा bpf_offload_dev	*offdev;
	व्योम			*dev_priv;
	काष्ठा list_head	offloads;
	bool			dev_state;
	bool			opt_failed;
	व्योम			*jited_image;
	u32			jited_len;
पूर्ण;

क्रमागत bpf_cgroup_storage_type अणु
	BPF_CGROUP_STORAGE_SHARED,
	BPF_CGROUP_STORAGE_PERCPU,
	__BPF_CGROUP_STORAGE_MAX
पूर्ण;

#घोषणा MAX_BPF_CGROUP_STORAGE_TYPE __BPF_CGROUP_STORAGE_MAX

/* The दीर्घest tracepoपूर्णांक has 12 args.
 * See include/trace/bpf_probe.h
 */
#घोषणा MAX_BPF_FUNC_ARGS 12

/* The maximum number of arguments passed through रेजिस्टरs
 * a single function may have.
 */
#घोषणा MAX_BPF_FUNC_REG_ARGS 5

काष्ठा btf_func_model अणु
	u8 ret_size;
	u8 nr_args;
	u8 arg_size[MAX_BPF_FUNC_ARGS];
पूर्ण;

/* Restore arguments beक्रमe वापसing from trampoline to let original function
 * जारी executing. This flag is used क्रम fentry progs when there are no
 * fनिकास progs.
 */
#घोषणा BPF_TRAMP_F_RESTORE_REGS	BIT(0)
/* Call original function after fentry progs, but beक्रमe fनिकास progs.
 * Makes sense क्रम fentry/fनिकास, normal calls and indirect calls.
 */
#घोषणा BPF_TRAMP_F_CALL_ORIG		BIT(1)
/* Skip current frame and वापस to parent.  Makes sense क्रम fentry/fनिकास
 * programs only. Should not be used with normal calls and indirect calls.
 */
#घोषणा BPF_TRAMP_F_SKIP_FRAME		BIT(2)

/* Each call __bpf_prog_enter + call bpf_func + call __bpf_prog_निकास is ~50
 * bytes on x86.  Pick a number to fit पूर्णांकo BPF_IMAGE_SIZE / 2
 */
#घोषणा BPF_MAX_TRAMP_PROGS 38

काष्ठा bpf_tramp_progs अणु
	काष्ठा bpf_prog *progs[BPF_MAX_TRAMP_PROGS];
	पूर्णांक nr_progs;
पूर्ण;

/* Dअगरferent use हालs क्रम BPF trampoline:
 * 1. replace nop at the function entry (kprobe equivalent)
 *    flags = BPF_TRAMP_F_RESTORE_REGS
 *    fentry = a set of programs to run beक्रमe वापसing from trampoline
 *
 * 2. replace nop at the function entry (kprobe + kretprobe equivalent)
 *    flags = BPF_TRAMP_F_CALL_ORIG | BPF_TRAMP_F_SKIP_FRAME
 *    orig_call = fentry_ip + MCOUNT_INSN_SIZE
 *    fentry = a set of program to run beक्रमe calling original function
 *    fनिकास = a set of program to run after original function
 *
 * 3. replace direct call inकाष्ठाion anywhere in the function body
 *    or assign a function poपूर्णांकer क्रम indirect call (like tcp_congestion_ops->cong_aव्योम)
 *    With flags = 0
 *      fentry = a set of programs to run beक्रमe वापसing from trampoline
 *    With flags = BPF_TRAMP_F_CALL_ORIG
 *      orig_call = original callback addr or direct function addr
 *      fentry = a set of program to run beक्रमe calling original function
 *      fनिकास = a set of program to run after original function
 */
काष्ठा bpf_tramp_image;
पूर्णांक arch_prepare_bpf_trampoline(काष्ठा bpf_tramp_image *tr, व्योम *image, व्योम *image_end,
				स्थिर काष्ठा btf_func_model *m, u32 flags,
				काष्ठा bpf_tramp_progs *tprogs,
				व्योम *orig_call);
/* these two functions are called from generated trampoline */
u64 notrace __bpf_prog_enter(काष्ठा bpf_prog *prog);
व्योम notrace __bpf_prog_निकास(काष्ठा bpf_prog *prog, u64 start);
u64 notrace __bpf_prog_enter_sleepable(काष्ठा bpf_prog *prog);
व्योम notrace __bpf_prog_निकास_sleepable(काष्ठा bpf_prog *prog, u64 start);
व्योम notrace __bpf_tramp_enter(काष्ठा bpf_tramp_image *tr);
व्योम notrace __bpf_tramp_निकास(काष्ठा bpf_tramp_image *tr);

काष्ठा bpf_ksym अणु
	अचिन्हित दीर्घ		 start;
	अचिन्हित दीर्घ		 end;
	अक्षर			 name[KSYM_NAME_LEN];
	काष्ठा list_head	 lnode;
	काष्ठा latch_tree_node	 tnode;
	bool			 prog;
पूर्ण;

क्रमागत bpf_tramp_prog_type अणु
	BPF_TRAMP_FENTRY,
	BPF_TRAMP_FEXIT,
	BPF_TRAMP_MODIFY_RETURN,
	BPF_TRAMP_MAX,
	BPF_TRAMP_REPLACE, /* more than MAX */
पूर्ण;

काष्ठा bpf_tramp_image अणु
	व्योम *image;
	काष्ठा bpf_ksym ksym;
	काष्ठा percpu_ref pcref;
	व्योम *ip_after_call;
	व्योम *ip_epilogue;
	जोड़ अणु
		काष्ठा rcu_head rcu;
		काष्ठा work_काष्ठा work;
	पूर्ण;
पूर्ण;

काष्ठा bpf_trampoline अणु
	/* hlist क्रम trampoline_table */
	काष्ठा hlist_node hlist;
	/* serializes access to fields of this trampoline */
	काष्ठा mutex mutex;
	refcount_t refcnt;
	u64 key;
	काष्ठा अणु
		काष्ठा btf_func_model model;
		व्योम *addr;
		bool ftrace_managed;
	पूर्ण func;
	/* अगर !शून्य this is BPF_PROG_TYPE_EXT program that extends another BPF
	 * program by replacing one of its functions. func.addr is the address
	 * of the function it replaced.
	 */
	काष्ठा bpf_prog *extension_prog;
	/* list of BPF programs using this trampoline */
	काष्ठा hlist_head progs_hlist[BPF_TRAMP_MAX];
	/* Number of attached programs. A counter per kind. */
	पूर्णांक progs_cnt[BPF_TRAMP_MAX];
	/* Executable image of trampoline */
	काष्ठा bpf_tramp_image *cur_image;
	u64 selector;
	काष्ठा module *mod;
पूर्ण;

काष्ठा bpf_attach_target_info अणु
	काष्ठा btf_func_model भ_शेषel;
	दीर्घ tgt_addr;
	स्थिर अक्षर *tgt_name;
	स्थिर काष्ठा btf_type *tgt_type;
पूर्ण;

#घोषणा BPF_DISPATCHER_MAX 48 /* Fits in 2048B */

काष्ठा bpf_dispatcher_prog अणु
	काष्ठा bpf_prog *prog;
	refcount_t users;
पूर्ण;

काष्ठा bpf_dispatcher अणु
	/* dispatcher mutex */
	काष्ठा mutex mutex;
	व्योम *func;
	काष्ठा bpf_dispatcher_prog progs[BPF_DISPATCHER_MAX];
	पूर्णांक num_progs;
	व्योम *image;
	u32 image_off;
	काष्ठा bpf_ksym ksym;
पूर्ण;

अटल __always_अंतरभूत __nocfi अचिन्हित पूर्णांक bpf_dispatcher_nop_func(
	स्थिर व्योम *ctx,
	स्थिर काष्ठा bpf_insn *insnsi,
	अचिन्हित पूर्णांक (*bpf_func)(स्थिर व्योम *,
				 स्थिर काष्ठा bpf_insn *))
अणु
	वापस bpf_func(ctx, insnsi);
पूर्ण
#अगर_घोषित CONFIG_BPF_JIT
पूर्णांक bpf_trampoline_link_prog(काष्ठा bpf_prog *prog, काष्ठा bpf_trampoline *tr);
पूर्णांक bpf_trampoline_unlink_prog(काष्ठा bpf_prog *prog, काष्ठा bpf_trampoline *tr);
काष्ठा bpf_trampoline *bpf_trampoline_get(u64 key,
					  काष्ठा bpf_attach_target_info *tgt_info);
व्योम bpf_trampoline_put(काष्ठा bpf_trampoline *tr);
#घोषणा BPF_DISPATCHER_INIT(_name) अणु				\
	.mutex = __MUTEX_INITIALIZER(_name.mutex),		\
	.func = &_name##_func,					\
	.progs = अणुपूर्ण,						\
	.num_progs = 0,						\
	.image = शून्य,						\
	.image_off = 0,						\
	.ksym = अणु						\
		.name  = #_name,				\
		.lnode = LIST_HEAD_INIT(_name.ksym.lnode),	\
	पूर्ण,							\
पूर्ण

#घोषणा DEFINE_BPF_DISPATCHER(name)					\
	noअंतरभूत __nocfi अचिन्हित पूर्णांक bpf_dispatcher_##name##_func(	\
		स्थिर व्योम *ctx,					\
		स्थिर काष्ठा bpf_insn *insnsi,				\
		अचिन्हित पूर्णांक (*bpf_func)(स्थिर व्योम *,			\
					 स्थिर काष्ठा bpf_insn *))	\
	अणु								\
		वापस bpf_func(ctx, insnsi);				\
	पूर्ण								\
	EXPORT_SYMBOL(bpf_dispatcher_##name##_func);			\
	काष्ठा bpf_dispatcher bpf_dispatcher_##name =			\
		BPF_DISPATCHER_INIT(bpf_dispatcher_##name);
#घोषणा DECLARE_BPF_DISPATCHER(name)					\
	अचिन्हित पूर्णांक bpf_dispatcher_##name##_func(			\
		स्थिर व्योम *ctx,					\
		स्थिर काष्ठा bpf_insn *insnsi,				\
		अचिन्हित पूर्णांक (*bpf_func)(स्थिर व्योम *,			\
					 स्थिर काष्ठा bpf_insn *));	\
	बाह्य काष्ठा bpf_dispatcher bpf_dispatcher_##name;
#घोषणा BPF_DISPATCHER_FUNC(name) bpf_dispatcher_##name##_func
#घोषणा BPF_DISPATCHER_PTR(name) (&bpf_dispatcher_##name)
व्योम bpf_dispatcher_change_prog(काष्ठा bpf_dispatcher *d, काष्ठा bpf_prog *from,
				काष्ठा bpf_prog *to);
/* Called only from JIT-enabled code, so there's no need क्रम stubs. */
व्योम *bpf_jit_alloc_exec_page(व्योम);
व्योम bpf_image_ksym_add(व्योम *data, काष्ठा bpf_ksym *ksym);
व्योम bpf_image_ksym_del(काष्ठा bpf_ksym *ksym);
व्योम bpf_ksym_add(काष्ठा bpf_ksym *ksym);
व्योम bpf_ksym_del(काष्ठा bpf_ksym *ksym);
पूर्णांक bpf_jit_अक्षरge_modmem(u32 pages);
व्योम bpf_jit_unअक्षरge_modmem(u32 pages);
#अन्यथा
अटल अंतरभूत पूर्णांक bpf_trampoline_link_prog(काष्ठा bpf_prog *prog,
					   काष्ठा bpf_trampoline *tr)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक bpf_trampoline_unlink_prog(काष्ठा bpf_prog *prog,
					     काष्ठा bpf_trampoline *tr)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत काष्ठा bpf_trampoline *bpf_trampoline_get(u64 key,
							काष्ठा bpf_attach_target_info *tgt_info)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण
अटल अंतरभूत व्योम bpf_trampoline_put(काष्ठा bpf_trampoline *tr) अणुपूर्ण
#घोषणा DEFINE_BPF_DISPATCHER(name)
#घोषणा DECLARE_BPF_DISPATCHER(name)
#घोषणा BPF_DISPATCHER_FUNC(name) bpf_dispatcher_nop_func
#घोषणा BPF_DISPATCHER_PTR(name) शून्य
अटल अंतरभूत व्योम bpf_dispatcher_change_prog(काष्ठा bpf_dispatcher *d,
					      काष्ठा bpf_prog *from,
					      काष्ठा bpf_prog *to) अणुपूर्ण
अटल अंतरभूत bool is_bpf_image_address(अचिन्हित दीर्घ address)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

काष्ठा bpf_func_info_aux अणु
	u16 linkage;
	bool unreliable;
पूर्ण;

क्रमागत bpf_jit_poke_reason अणु
	BPF_POKE_REASON_TAIL_CALL,
पूर्ण;

/* Descriptor of pokes poपूर्णांकing /पूर्णांकo/ the JITed image. */
काष्ठा bpf_jit_poke_descriptor अणु
	व्योम *tailcall_target;
	व्योम *tailcall_bypass;
	व्योम *bypass_addr;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा bpf_map *map;
			u32 key;
		पूर्ण tail_call;
	पूर्ण;
	bool tailcall_target_stable;
	u8 adj_off;
	u16 reason;
	u32 insn_idx;
पूर्ण;

/* reg_type info क्रम ctx arguments */
काष्ठा bpf_ctx_arg_aux अणु
	u32 offset;
	क्रमागत bpf_reg_type reg_type;
	u32 btf_id;
पूर्ण;

काष्ठा btf_mod_pair अणु
	काष्ठा btf *btf;
	काष्ठा module *module;
पूर्ण;

काष्ठा bpf_kfunc_desc_tab;

काष्ठा bpf_prog_aux अणु
	atomic64_t refcnt;
	u32 used_map_cnt;
	u32 used_btf_cnt;
	u32 max_ctx_offset;
	u32 max_pkt_offset;
	u32 max_tp_access;
	u32 stack_depth;
	u32 id;
	u32 func_cnt; /* used by non-func prog as the number of func progs */
	u32 func_idx; /* 0 क्रम non-func prog, the index in func array क्रम func prog */
	u32 attach_btf_id; /* in-kernel BTF type id to attach to */
	u32 ctx_arg_info_size;
	u32 max_rकरोnly_access;
	u32 max_rdwr_access;
	काष्ठा btf *attach_btf;
	स्थिर काष्ठा bpf_ctx_arg_aux *ctx_arg_info;
	काष्ठा mutex dst_mutex; /* protects dst_* poपूर्णांकers below, *after* prog becomes visible */
	काष्ठा bpf_prog *dst_prog;
	काष्ठा bpf_trampoline *dst_trampoline;
	क्रमागत bpf_prog_type saved_dst_prog_type;
	क्रमागत bpf_attach_type saved_dst_attach_type;
	bool verअगरier_zext; /* Zero extensions has been inserted by verअगरier. */
	bool offload_requested;
	bool attach_btf_trace; /* true अगर attaching to BTF-enabled raw tp */
	bool func_proto_unreliable;
	bool sleepable;
	bool tail_call_reachable;
	काष्ठा hlist_node tramp_hlist;
	/* BTF_KIND_FUNC_PROTO क्रम valid attach_btf_id */
	स्थिर काष्ठा btf_type *attach_func_proto;
	/* function name क्रम valid attach_btf_id */
	स्थिर अक्षर *attach_func_name;
	काष्ठा bpf_prog **func;
	व्योम *jit_data; /* JIT specअगरic data. arch dependent */
	काष्ठा bpf_jit_poke_descriptor *poke_tab;
	काष्ठा bpf_kfunc_desc_tab *kfunc_tab;
	u32 size_poke_tab;
	काष्ठा bpf_ksym ksym;
	स्थिर काष्ठा bpf_prog_ops *ops;
	काष्ठा bpf_map **used_maps;
	काष्ठा mutex used_maps_mutex; /* mutex क्रम used_maps and used_map_cnt */
	काष्ठा btf_mod_pair *used_btfs;
	काष्ठा bpf_prog *prog;
	काष्ठा user_काष्ठा *user;
	u64 load_समय; /* ns since bootसमय */
	काष्ठा bpf_map *cgroup_storage[MAX_BPF_CGROUP_STORAGE_TYPE];
	अक्षर name[BPF_OBJ_NAME_LEN];
#अगर_घोषित CONFIG_SECURITY
	व्योम *security;
#पूर्ण_अगर
	काष्ठा bpf_prog_offload *offload;
	काष्ठा btf *btf;
	काष्ठा bpf_func_info *func_info;
	काष्ठा bpf_func_info_aux *func_info_aux;
	/* bpf_line_info loaded from userspace.  linfo->insn_off
	 * has the xlated insn offset.
	 * Both the मुख्य and sub prog share the same linfo.
	 * The subprog can access its first linfo by
	 * using the linfo_idx.
	 */
	काष्ठा bpf_line_info *linfo;
	/* jited_linfo is the jited addr of the linfo.  It has a
	 * one to one mapping to linfo:
	 * jited_linfo[i] is the jited addr क्रम the linfo[i]->insn_off.
	 * Both the मुख्य and sub prog share the same jited_linfo.
	 * The subprog can access its first jited_linfo by
	 * using the linfo_idx.
	 */
	व्योम **jited_linfo;
	u32 func_info_cnt;
	u32 nr_linfo;
	/* subprog can use linfo_idx to access its first linfo and
	 * jited_linfo.
	 * मुख्य prog always has linfo_idx == 0
	 */
	u32 linfo_idx;
	u32 num_exentries;
	काष्ठा exception_table_entry *extable;
	जोड़ अणु
		काष्ठा work_काष्ठा work;
		काष्ठा rcu_head	rcu;
	पूर्ण;
पूर्ण;

काष्ठा bpf_array_aux अणु
	/* 'Ownership' of prog array is claimed by the first program that
	 * is going to use this map or by the first program which FD is
	 * stored in the map to make sure that all callers and callees have
	 * the same prog type and JITed flag.
	 */
	क्रमागत bpf_prog_type type;
	bool jited;
	/* Programs with direct jumps पूर्णांकo programs part of this array. */
	काष्ठा list_head poke_progs;
	काष्ठा bpf_map *map;
	काष्ठा mutex poke_mutex;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा bpf_link अणु
	atomic64_t refcnt;
	u32 id;
	क्रमागत bpf_link_type type;
	स्थिर काष्ठा bpf_link_ops *ops;
	काष्ठा bpf_prog *prog;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा bpf_link_ops अणु
	व्योम (*release)(काष्ठा bpf_link *link);
	व्योम (*dealloc)(काष्ठा bpf_link *link);
	पूर्णांक (*detach)(काष्ठा bpf_link *link);
	पूर्णांक (*update_prog)(काष्ठा bpf_link *link, काष्ठा bpf_prog *new_prog,
			   काष्ठा bpf_prog *old_prog);
	व्योम (*show_fdinfo)(स्थिर काष्ठा bpf_link *link, काष्ठा seq_file *seq);
	पूर्णांक (*fill_link_info)(स्थिर काष्ठा bpf_link *link,
			      काष्ठा bpf_link_info *info);
पूर्ण;

काष्ठा bpf_link_primer अणु
	काष्ठा bpf_link *link;
	काष्ठा file *file;
	पूर्णांक fd;
	u32 id;
पूर्ण;

काष्ठा bpf_काष्ठा_ops_value;
काष्ठा btf_member;

#घोषणा BPF_STRUCT_OPS_MAX_NR_MEMBERS 64
काष्ठा bpf_काष्ठा_ops अणु
	स्थिर काष्ठा bpf_verअगरier_ops *verअगरier_ops;
	पूर्णांक (*init)(काष्ठा btf *btf);
	पूर्णांक (*check_member)(स्थिर काष्ठा btf_type *t,
			    स्थिर काष्ठा btf_member *member);
	पूर्णांक (*init_member)(स्थिर काष्ठा btf_type *t,
			   स्थिर काष्ठा btf_member *member,
			   व्योम *kdata, स्थिर व्योम *udata);
	पूर्णांक (*reg)(व्योम *kdata);
	व्योम (*unreg)(व्योम *kdata);
	स्थिर काष्ठा btf_type *type;
	स्थिर काष्ठा btf_type *value_type;
	स्थिर अक्षर *name;
	काष्ठा btf_func_model func_models[BPF_STRUCT_OPS_MAX_NR_MEMBERS];
	u32 type_id;
	u32 value_id;
पूर्ण;

#अगर defined(CONFIG_BPF_JIT) && defined(CONFIG_BPF_SYSCALL)
#घोषणा BPF_MODULE_OWNER ((व्योम *)((0xeB9FUL << 2) + POISON_POINTER_DELTA))
स्थिर काष्ठा bpf_काष्ठा_ops *bpf_काष्ठा_ops_find(u32 type_id);
व्योम bpf_काष्ठा_ops_init(काष्ठा btf *btf, काष्ठा bpf_verअगरier_log *log);
bool bpf_काष्ठा_ops_get(स्थिर व्योम *kdata);
व्योम bpf_काष्ठा_ops_put(स्थिर व्योम *kdata);
पूर्णांक bpf_काष्ठा_ops_map_sys_lookup_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value);
अटल अंतरभूत bool bpf_try_module_get(स्थिर व्योम *data, काष्ठा module *owner)
अणु
	अगर (owner == BPF_MODULE_OWNER)
		वापस bpf_काष्ठा_ops_get(data);
	अन्यथा
		वापस try_module_get(owner);
पूर्ण
अटल अंतरभूत व्योम bpf_module_put(स्थिर व्योम *data, काष्ठा module *owner)
अणु
	अगर (owner == BPF_MODULE_OWNER)
		bpf_काष्ठा_ops_put(data);
	अन्यथा
		module_put(owner);
पूर्ण
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा bpf_काष्ठा_ops *bpf_काष्ठा_ops_find(u32 type_id)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम bpf_काष्ठा_ops_init(काष्ठा btf *btf,
				       काष्ठा bpf_verअगरier_log *log)
अणु
पूर्ण
अटल अंतरभूत bool bpf_try_module_get(स्थिर व्योम *data, काष्ठा module *owner)
अणु
	वापस try_module_get(owner);
पूर्ण
अटल अंतरभूत व्योम bpf_module_put(स्थिर व्योम *data, काष्ठा module *owner)
अणु
	module_put(owner);
पूर्ण
अटल अंतरभूत पूर्णांक bpf_काष्ठा_ops_map_sys_lookup_elem(काष्ठा bpf_map *map,
						     व्योम *key,
						     व्योम *value)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

काष्ठा bpf_array अणु
	काष्ठा bpf_map map;
	u32 elem_size;
	u32 index_mask;
	काष्ठा bpf_array_aux *aux;
	जोड़ अणु
		अक्षर value[0] __aligned(8);
		व्योम *ptrs[0] __aligned(8);
		व्योम __percpu *pptrs[0] __aligned(8);
	पूर्ण;
पूर्ण;

#घोषणा BPF_COMPLEXITY_LIMIT_INSNS      1000000 /* yes. 1M insns */
#घोषणा MAX_TAIL_CALL_CNT 32

#घोषणा BPF_F_ACCESS_MASK	(BPF_F_RDONLY |		\
				 BPF_F_RDONLY_PROG |	\
				 BPF_F_WRONLY |		\
				 BPF_F_WRONLY_PROG)

#घोषणा BPF_MAP_CAN_READ	BIT(0)
#घोषणा BPF_MAP_CAN_WRITE	BIT(1)

अटल अंतरभूत u32 bpf_map_flags_to_cap(काष्ठा bpf_map *map)
अणु
	u32 access_flags = map->map_flags & (BPF_F_RDONLY_PROG | BPF_F_WRONLY_PROG);

	/* Combination of BPF_F_RDONLY_PROG | BPF_F_WRONLY_PROG is
	 * not possible.
	 */
	अगर (access_flags & BPF_F_RDONLY_PROG)
		वापस BPF_MAP_CAN_READ;
	अन्यथा अगर (access_flags & BPF_F_WRONLY_PROG)
		वापस BPF_MAP_CAN_WRITE;
	अन्यथा
		वापस BPF_MAP_CAN_READ | BPF_MAP_CAN_WRITE;
पूर्ण

अटल अंतरभूत bool bpf_map_flags_access_ok(u32 access_flags)
अणु
	वापस (access_flags & (BPF_F_RDONLY_PROG | BPF_F_WRONLY_PROG)) !=
	       (BPF_F_RDONLY_PROG | BPF_F_WRONLY_PROG);
पूर्ण

काष्ठा bpf_event_entry अणु
	काष्ठा perf_event *event;
	काष्ठा file *perf_file;
	काष्ठा file *map_file;
	काष्ठा rcu_head rcu;
पूर्ण;

bool bpf_prog_array_compatible(काष्ठा bpf_array *array, स्थिर काष्ठा bpf_prog *fp);
पूर्णांक bpf_prog_calc_tag(काष्ठा bpf_prog *fp);

स्थिर काष्ठा bpf_func_proto *bpf_get_trace_prपूर्णांकk_proto(व्योम);

प्रकार अचिन्हित दीर्घ (*bpf_ctx_copy_t)(व्योम *dst, स्थिर व्योम *src,
					अचिन्हित दीर्घ off, अचिन्हित दीर्घ len);
प्रकार u32 (*bpf_convert_ctx_access_t)(क्रमागत bpf_access_type type,
					स्थिर काष्ठा bpf_insn *src,
					काष्ठा bpf_insn *dst,
					काष्ठा bpf_prog *prog,
					u32 *target_size);

u64 bpf_event_output(काष्ठा bpf_map *map, u64 flags, व्योम *meta, u64 meta_size,
		     व्योम *ctx, u64 ctx_size, bpf_ctx_copy_t ctx_copy);

/* an array of programs to be executed under rcu_lock.
 *
 * Typical usage:
 * ret = BPF_PROG_RUN_ARRAY(&bpf_prog_array, ctx, BPF_PROG_RUN);
 *
 * the काष्ठाure वापसed by bpf_prog_array_alloc() should be populated
 * with program poपूर्णांकers and the last poपूर्णांकer must be शून्य.
 * The user has to keep refcnt on the program and make sure the program
 * is हटाओd from the array beक्रमe bpf_prog_put().
 * The 'struct bpf_prog_array *' should only be replaced with xchg()
 * since other cpus are walking the array of poपूर्णांकers in parallel.
 */
काष्ठा bpf_prog_array_item अणु
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_cgroup_storage *cgroup_storage[MAX_BPF_CGROUP_STORAGE_TYPE];
पूर्ण;

काष्ठा bpf_prog_array अणु
	काष्ठा rcu_head rcu;
	काष्ठा bpf_prog_array_item items[];
पूर्ण;

काष्ठा bpf_prog_array *bpf_prog_array_alloc(u32 prog_cnt, gfp_t flags);
व्योम bpf_prog_array_मुक्त(काष्ठा bpf_prog_array *progs);
पूर्णांक bpf_prog_array_length(काष्ठा bpf_prog_array *progs);
bool bpf_prog_array_is_empty(काष्ठा bpf_prog_array *array);
पूर्णांक bpf_prog_array_copy_to_user(काष्ठा bpf_prog_array *progs,
				__u32 __user *prog_ids, u32 cnt);

व्योम bpf_prog_array_delete_safe(काष्ठा bpf_prog_array *progs,
				काष्ठा bpf_prog *old_prog);
पूर्णांक bpf_prog_array_delete_safe_at(काष्ठा bpf_prog_array *array, पूर्णांक index);
पूर्णांक bpf_prog_array_update_at(काष्ठा bpf_prog_array *array, पूर्णांक index,
			     काष्ठा bpf_prog *prog);
पूर्णांक bpf_prog_array_copy_info(काष्ठा bpf_prog_array *array,
			     u32 *prog_ids, u32 request_cnt,
			     u32 *prog_cnt);
पूर्णांक bpf_prog_array_copy(काष्ठा bpf_prog_array *old_array,
			काष्ठा bpf_prog *exclude_prog,
			काष्ठा bpf_prog *include_prog,
			काष्ठा bpf_prog_array **new_array);

/* BPF program asks to bypass CAP_NET_BIND_SERVICE in bind. */
#घोषणा BPF_RET_BIND_NO_CAP_NET_BIND_SERVICE			(1 << 0)
/* BPF program asks to set CN on the packet. */
#घोषणा BPF_RET_SET_CN						(1 << 0)

/* For BPF_PROG_RUN_ARRAY_FLAGS and __BPF_PROG_RUN_ARRAY,
 * अगर bpf_cgroup_storage_set() failed, the rest of programs
 * will not execute. This should be a really rare scenario
 * as it requires BPF_CGROUP_STORAGE_NEST_MAX number of
 * preemptions all between bpf_cgroup_storage_set() and
 * bpf_cgroup_storage_unset() on the same cpu.
 */
#घोषणा BPF_PROG_RUN_ARRAY_FLAGS(array, ctx, func, ret_flags)		\
	(अणु								\
		काष्ठा bpf_prog_array_item *_item;			\
		काष्ठा bpf_prog *_prog;					\
		काष्ठा bpf_prog_array *_array;				\
		u32 _ret = 1;						\
		u32 func_ret;						\
		migrate_disable();					\
		rcu_पढ़ो_lock();					\
		_array = rcu_dereference(array);			\
		_item = &_array->items[0];				\
		जबतक ((_prog = READ_ONCE(_item->prog))) अणु		\
			अगर (unlikely(bpf_cgroup_storage_set(_item->cgroup_storage)))	\
				अवरोध;					\
			func_ret = func(_prog, ctx);			\
			_ret &= (func_ret & 1);				\
			*(ret_flags) |= (func_ret >> 1);			\
			bpf_cgroup_storage_unset();			\
			_item++;					\
		पूर्ण							\
		rcu_पढ़ो_unlock();					\
		migrate_enable();					\
		_ret;							\
	 पूर्ण)

#घोषणा __BPF_PROG_RUN_ARRAY(array, ctx, func, check_non_null, set_cg_storage)	\
	(अणु						\
		काष्ठा bpf_prog_array_item *_item;	\
		काष्ठा bpf_prog *_prog;			\
		काष्ठा bpf_prog_array *_array;		\
		u32 _ret = 1;				\
		migrate_disable();			\
		rcu_पढ़ो_lock();			\
		_array = rcu_dereference(array);	\
		अगर (unlikely(check_non_null && !_array))\
			जाओ _out;			\
		_item = &_array->items[0];		\
		जबतक ((_prog = READ_ONCE(_item->prog))) अणु		\
			अगर (!set_cg_storage) अणु			\
				_ret &= func(_prog, ctx);	\
			पूर्ण अन्यथा अणु				\
				अगर (unlikely(bpf_cgroup_storage_set(_item->cgroup_storage)))	\
					अवरोध;			\
				_ret &= func(_prog, ctx);	\
				bpf_cgroup_storage_unset();	\
			पूर्ण				\
			_item++;			\
		पूर्ण					\
_out:							\
		rcu_पढ़ो_unlock();			\
		migrate_enable();			\
		_ret;					\
	 पूर्ण)

/* To be used by __cgroup_bpf_run_filter_skb क्रम EGRESS BPF progs
 * so BPF programs can request cwr क्रम TCP packets.
 *
 * Current cgroup skb programs can only वापस 0 or 1 (0 to drop the
 * packet. This macro changes the behavior so the low order bit
 * indicates whether the packet should be dropped (0) or not (1)
 * and the next bit is a congestion notअगरication bit. This could be
 * used by TCP to call tcp_enter_cwr()
 *
 * Hence, new allowed वापस values of CGROUP EGRESS BPF programs are:
 *   0: drop packet
 *   1: keep packet
 *   2: drop packet and cn
 *   3: keep packet and cn
 *
 * This macro then converts it to one of the NET_XMIT or an error
 * code that is then पूर्णांकerpreted as drop packet (and no cn):
 *   0: NET_XMIT_SUCCESS  skb should be transmitted
 *   1: NET_XMIT_DROP     skb should be dropped and cn
 *   2: NET_XMIT_CN       skb should be transmitted and cn
 *   3: -EPERM            skb should be dropped
 */
#घोषणा BPF_PROG_CGROUP_INET_EGRESS_RUN_ARRAY(array, ctx, func)		\
	(अणु						\
		u32 _flags = 0;				\
		bool _cn;				\
		u32 _ret;				\
		_ret = BPF_PROG_RUN_ARRAY_FLAGS(array, ctx, func, &_flags); \
		_cn = _flags & BPF_RET_SET_CN;		\
		अगर (_ret)				\
			_ret = (_cn ? NET_XMIT_CN : NET_XMIT_SUCCESS);	\
		अन्यथा					\
			_ret = (_cn ? NET_XMIT_DROP : -EPERM);		\
		_ret;					\
	पूर्ण)

#घोषणा BPF_PROG_RUN_ARRAY(array, ctx, func)		\
	__BPF_PROG_RUN_ARRAY(array, ctx, func, false, true)

#घोषणा BPF_PROG_RUN_ARRAY_CHECK(array, ctx, func)	\
	__BPF_PROG_RUN_ARRAY(array, ctx, func, true, false)

#अगर_घोषित CONFIG_BPF_SYSCALL
DECLARE_PER_CPU(पूर्णांक, bpf_prog_active);
बाह्य काष्ठा mutex bpf_stats_enabled_mutex;

/*
 * Block execution of BPF programs attached to instrumentation (perf,
 * kprobes, tracepoपूर्णांकs) to prevent deadlocks on map operations as any of
 * these events can happen inside a region which holds a map bucket lock
 * and can deadlock on it.
 *
 * Use the preemption safe inc/dec variants on RT because migrate disable
 * is preemptible on RT and preemption in the middle of the RMW operation
 * might lead to inconsistent state. Use the raw variants क्रम non RT
 * kernels as migrate_disable() maps to preempt_disable() so the slightly
 * more expensive save operation can be aव्योमed.
 */
अटल अंतरभूत व्योम bpf_disable_instrumentation(व्योम)
अणु
	migrate_disable();
	अगर (IS_ENABLED(CONFIG_PREEMPT_RT))
		this_cpu_inc(bpf_prog_active);
	अन्यथा
		__this_cpu_inc(bpf_prog_active);
पूर्ण

अटल अंतरभूत व्योम bpf_enable_instrumentation(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_PREEMPT_RT))
		this_cpu_dec(bpf_prog_active);
	अन्यथा
		__this_cpu_dec(bpf_prog_active);
	migrate_enable();
पूर्ण

बाह्य स्थिर काष्ठा file_operations bpf_map_fops;
बाह्य स्थिर काष्ठा file_operations bpf_prog_fops;
बाह्य स्थिर काष्ठा file_operations bpf_iter_fops;

#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type) \
	बाह्य स्थिर काष्ठा bpf_prog_ops _name ## _prog_ops; \
	बाह्य स्थिर काष्ठा bpf_verअगरier_ops _name ## _verअगरier_ops;
#घोषणा BPF_MAP_TYPE(_id, _ops) \
	बाह्य स्थिर काष्ठा bpf_map_ops _ops;
#घोषणा BPF_LINK_TYPE(_id, _name)
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
#अघोषित BPF_MAP_TYPE
#अघोषित BPF_LINK_TYPE

बाह्य स्थिर काष्ठा bpf_prog_ops bpf_offload_prog_ops;
बाह्य स्थिर काष्ठा bpf_verअगरier_ops tc_cls_act_analyzer_ops;
बाह्य स्थिर काष्ठा bpf_verअगरier_ops xdp_analyzer_ops;

काष्ठा bpf_prog *bpf_prog_get(u32 ufd);
काष्ठा bpf_prog *bpf_prog_get_type_dev(u32 ufd, क्रमागत bpf_prog_type type,
				       bool attach_drv);
व्योम bpf_prog_add(काष्ठा bpf_prog *prog, पूर्णांक i);
व्योम bpf_prog_sub(काष्ठा bpf_prog *prog, पूर्णांक i);
व्योम bpf_prog_inc(काष्ठा bpf_prog *prog);
काष्ठा bpf_prog * __must_check bpf_prog_inc_not_zero(काष्ठा bpf_prog *prog);
व्योम bpf_prog_put(काष्ठा bpf_prog *prog);

व्योम bpf_prog_मुक्त_id(काष्ठा bpf_prog *prog, bool करो_idr_lock);
व्योम bpf_map_मुक्त_id(काष्ठा bpf_map *map, bool करो_idr_lock);

काष्ठा bpf_map *bpf_map_get(u32 ufd);
काष्ठा bpf_map *bpf_map_get_with_uref(u32 ufd);
काष्ठा bpf_map *__bpf_map_get(काष्ठा fd f);
व्योम bpf_map_inc(काष्ठा bpf_map *map);
व्योम bpf_map_inc_with_uref(काष्ठा bpf_map *map);
काष्ठा bpf_map * __must_check bpf_map_inc_not_zero(काष्ठा bpf_map *map);
व्योम bpf_map_put_with_uref(काष्ठा bpf_map *map);
व्योम bpf_map_put(काष्ठा bpf_map *map);
व्योम *bpf_map_area_alloc(u64 size, पूर्णांक numa_node);
व्योम *bpf_map_area_mmapable_alloc(u64 size, पूर्णांक numa_node);
व्योम bpf_map_area_मुक्त(व्योम *base);
व्योम bpf_map_init_from_attr(काष्ठा bpf_map *map, जोड़ bpf_attr *attr);
पूर्णांक  generic_map_lookup_batch(काष्ठा bpf_map *map,
			      स्थिर जोड़ bpf_attr *attr,
			      जोड़ bpf_attr __user *uattr);
पूर्णांक  generic_map_update_batch(काष्ठा bpf_map *map,
			      स्थिर जोड़ bpf_attr *attr,
			      जोड़ bpf_attr __user *uattr);
पूर्णांक  generic_map_delete_batch(काष्ठा bpf_map *map,
			      स्थिर जोड़ bpf_attr *attr,
			      जोड़ bpf_attr __user *uattr);
काष्ठा bpf_map *bpf_map_get_curr_or_next(u32 *id);
काष्ठा bpf_prog *bpf_prog_get_curr_or_next(u32 *id);

#अगर_घोषित CONFIG_MEMCG_KMEM
व्योम *bpf_map_kदो_स्मृति_node(स्थिर काष्ठा bpf_map *map, माप_प्रकार size, gfp_t flags,
			   पूर्णांक node);
व्योम *bpf_map_kzalloc(स्थिर काष्ठा bpf_map *map, माप_प्रकार size, gfp_t flags);
व्योम __percpu *bpf_map_alloc_percpu(स्थिर काष्ठा bpf_map *map, माप_प्रकार size,
				    माप_प्रकार align, gfp_t flags);
#अन्यथा
अटल अंतरभूत व्योम *
bpf_map_kदो_स्मृति_node(स्थिर काष्ठा bpf_map *map, माप_प्रकार size, gfp_t flags,
		     पूर्णांक node)
अणु
	वापस kदो_स्मृति_node(size, flags, node);
पूर्ण

अटल अंतरभूत व्योम *
bpf_map_kzalloc(स्थिर काष्ठा bpf_map *map, माप_प्रकार size, gfp_t flags)
अणु
	वापस kzalloc(size, flags);
पूर्ण

अटल अंतरभूत व्योम __percpu *
bpf_map_alloc_percpu(स्थिर काष्ठा bpf_map *map, माप_प्रकार size, माप_प्रकार align,
		     gfp_t flags)
अणु
	वापस __alloc_percpu_gfp(size, align, flags);
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक sysctl_unprivileged_bpf_disabled;

अटल अंतरभूत bool bpf_allow_ptr_leaks(व्योम)
अणु
	वापस perfmon_capable();
पूर्ण

अटल अंतरभूत bool bpf_allow_uninit_stack(व्योम)
अणु
	वापस perfmon_capable();
पूर्ण

अटल अंतरभूत bool bpf_allow_ptr_to_map_access(व्योम)
अणु
	वापस perfmon_capable();
पूर्ण

अटल अंतरभूत bool bpf_bypass_spec_v1(व्योम)
अणु
	वापस perfmon_capable();
पूर्ण

अटल अंतरभूत bool bpf_bypass_spec_v4(व्योम)
अणु
	वापस perfmon_capable();
पूर्ण

पूर्णांक bpf_map_new_fd(काष्ठा bpf_map *map, पूर्णांक flags);
पूर्णांक bpf_prog_new_fd(काष्ठा bpf_prog *prog);

व्योम bpf_link_init(काष्ठा bpf_link *link, क्रमागत bpf_link_type type,
		   स्थिर काष्ठा bpf_link_ops *ops, काष्ठा bpf_prog *prog);
पूर्णांक bpf_link_prime(काष्ठा bpf_link *link, काष्ठा bpf_link_primer *primer);
पूर्णांक bpf_link_settle(काष्ठा bpf_link_primer *primer);
व्योम bpf_link_cleanup(काष्ठा bpf_link_primer *primer);
व्योम bpf_link_inc(काष्ठा bpf_link *link);
व्योम bpf_link_put(काष्ठा bpf_link *link);
पूर्णांक bpf_link_new_fd(काष्ठा bpf_link *link);
काष्ठा file *bpf_link_new_file(काष्ठा bpf_link *link, पूर्णांक *reserved_fd);
काष्ठा bpf_link *bpf_link_get_from_fd(u32 ufd);

पूर्णांक bpf_obj_pin_user(u32 ufd, स्थिर अक्षर __user *pathname);
पूर्णांक bpf_obj_get_user(स्थिर अक्षर __user *pathname, पूर्णांक flags);

#घोषणा BPF_ITER_FUNC_PREFIX "bpf_iter_"
#घोषणा DEFINE_BPF_ITER_FUNC(target, args...)			\
	बाह्य पूर्णांक bpf_iter_ ## target(args);			\
	पूर्णांक __init bpf_iter_ ## target(args) अणु वापस 0; पूर्ण

काष्ठा bpf_iter_aux_info अणु
	काष्ठा bpf_map *map;
पूर्ण;

प्रकार पूर्णांक (*bpf_iter_attach_target_t)(काष्ठा bpf_prog *prog,
					जोड़ bpf_iter_link_info *linfo,
					काष्ठा bpf_iter_aux_info *aux);
प्रकार व्योम (*bpf_iter_detach_target_t)(काष्ठा bpf_iter_aux_info *aux);
प्रकार व्योम (*bpf_iter_show_fdinfo_t) (स्थिर काष्ठा bpf_iter_aux_info *aux,
					काष्ठा seq_file *seq);
प्रकार पूर्णांक (*bpf_iter_fill_link_info_t)(स्थिर काष्ठा bpf_iter_aux_info *aux,
					 काष्ठा bpf_link_info *info);

क्रमागत bpf_iter_feature अणु
	BPF_ITER_RESCHED	= BIT(0),
पूर्ण;

#घोषणा BPF_ITER_CTX_ARG_MAX 2
काष्ठा bpf_iter_reg अणु
	स्थिर अक्षर *target;
	bpf_iter_attach_target_t attach_target;
	bpf_iter_detach_target_t detach_target;
	bpf_iter_show_fdinfo_t show_fdinfo;
	bpf_iter_fill_link_info_t fill_link_info;
	u32 ctx_arg_info_size;
	u32 feature;
	काष्ठा bpf_ctx_arg_aux ctx_arg_info[BPF_ITER_CTX_ARG_MAX];
	स्थिर काष्ठा bpf_iter_seq_info *seq_info;
पूर्ण;

काष्ठा bpf_iter_meta अणु
	__bpf_md_ptr(काष्ठा seq_file *, seq);
	u64 session_id;
	u64 seq_num;
पूर्ण;

काष्ठा bpf_iter__bpf_map_elem अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा bpf_map *, map);
	__bpf_md_ptr(व्योम *, key);
	__bpf_md_ptr(व्योम *, value);
पूर्ण;

पूर्णांक bpf_iter_reg_target(स्थिर काष्ठा bpf_iter_reg *reg_info);
व्योम bpf_iter_unreg_target(स्थिर काष्ठा bpf_iter_reg *reg_info);
bool bpf_iter_prog_supported(काष्ठा bpf_prog *prog);
पूर्णांक bpf_iter_link_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog);
पूर्णांक bpf_iter_new_fd(काष्ठा bpf_link *link);
bool bpf_link_is_iter(काष्ठा bpf_link *link);
काष्ठा bpf_prog *bpf_iter_get_info(काष्ठा bpf_iter_meta *meta, bool in_stop);
पूर्णांक bpf_iter_run_prog(काष्ठा bpf_prog *prog, व्योम *ctx);
व्योम bpf_iter_map_show_fdinfo(स्थिर काष्ठा bpf_iter_aux_info *aux,
			      काष्ठा seq_file *seq);
पूर्णांक bpf_iter_map_fill_link_info(स्थिर काष्ठा bpf_iter_aux_info *aux,
				काष्ठा bpf_link_info *info);

पूर्णांक map_set_क्रम_each_callback_args(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_func_state *caller,
				   काष्ठा bpf_func_state *callee);

पूर्णांक bpf_percpu_hash_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value);
पूर्णांक bpf_percpu_array_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value);
पूर्णांक bpf_percpu_hash_update(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			   u64 flags);
पूर्णांक bpf_percpu_array_update(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			    u64 flags);

पूर्णांक bpf_stackmap_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value);

पूर्णांक bpf_fd_array_map_update_elem(काष्ठा bpf_map *map, काष्ठा file *map_file,
				 व्योम *key, व्योम *value, u64 map_flags);
पूर्णांक bpf_fd_array_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key, u32 *value);
पूर्णांक bpf_fd_htab_map_update_elem(काष्ठा bpf_map *map, काष्ठा file *map_file,
				व्योम *key, व्योम *value, u64 map_flags);
पूर्णांक bpf_fd_htab_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key, u32 *value);

पूर्णांक bpf_get_file_flag(पूर्णांक flags);
पूर्णांक bpf_check_uarg_tail_zero(व्योम __user *uaddr, माप_प्रकार expected_size,
			     माप_प्रकार actual_size);

/* स_नकल that is used with 8-byte aligned poपूर्णांकers, घातer-of-8 size and
 * क्रमced to use 'long' पढ़ो/ग_लिखोs to try to atomically copy दीर्घ counters.
 * Best-efक्रमt only.  No barriers here, since it _will_ race with concurrent
 * updates from BPF programs. Called from bpf syscall and mostly used with
 * size 8 or 16 bytes, so ask compiler to अंतरभूत it.
 */
अटल अंतरभूत व्योम bpf_दीर्घ_स_नकल(व्योम *dst, स्थिर व्योम *src, u32 size)
अणु
	स्थिर दीर्घ *lsrc = src;
	दीर्घ *ldst = dst;

	size /= माप(दीर्घ);
	जबतक (size--)
		*ldst++ = *lsrc++;
पूर्ण

/* verअगरy correctness of eBPF program */
पूर्णांक bpf_check(काष्ठा bpf_prog **fp, जोड़ bpf_attr *attr,
	      जोड़ bpf_attr __user *uattr);

#अगर_अघोषित CONFIG_BPF_JIT_ALWAYS_ON
व्योम bpf_patch_call_args(काष्ठा bpf_insn *insn, u32 stack_depth);
#पूर्ण_अगर

काष्ठा btf *bpf_get_btf_vmlinux(व्योम);

/* Map specअगरics */
काष्ठा xdp_buff;
काष्ठा sk_buff;
काष्ठा bpf_dtab_netdev;
काष्ठा bpf_cpu_map_entry;

व्योम __dev_flush(व्योम);
पूर्णांक dev_xdp_enqueue(काष्ठा net_device *dev, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx);
पूर्णांक dev_map_enqueue(काष्ठा bpf_dtab_netdev *dst, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx);
पूर्णांक dev_map_generic_redirect(काष्ठा bpf_dtab_netdev *dst, काष्ठा sk_buff *skb,
			     काष्ठा bpf_prog *xdp_prog);
bool dev_map_can_have_prog(काष्ठा bpf_map *map);

व्योम __cpu_map_flush(व्योम);
पूर्णांक cpu_map_enqueue(काष्ठा bpf_cpu_map_entry *rcpu, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx);
bool cpu_map_prog_allowed(काष्ठा bpf_map *map);

/* Return map's numa specअगरied by userspace */
अटल अंतरभूत पूर्णांक bpf_map_attr_numa_node(स्थिर जोड़ bpf_attr *attr)
अणु
	वापस (attr->map_flags & BPF_F_NUMA_NODE) ?
		attr->numa_node : NUMA_NO_NODE;
पूर्ण

काष्ठा bpf_prog *bpf_prog_get_type_path(स्थिर अक्षर *name, क्रमागत bpf_prog_type type);
पूर्णांक array_map_alloc_check(जोड़ bpf_attr *attr);

पूर्णांक bpf_prog_test_run_xdp(काष्ठा bpf_prog *prog, स्थिर जोड़ bpf_attr *kattr,
			  जोड़ bpf_attr __user *uattr);
पूर्णांक bpf_prog_test_run_skb(काष्ठा bpf_prog *prog, स्थिर जोड़ bpf_attr *kattr,
			  जोड़ bpf_attr __user *uattr);
पूर्णांक bpf_prog_test_run_tracing(काष्ठा bpf_prog *prog,
			      स्थिर जोड़ bpf_attr *kattr,
			      जोड़ bpf_attr __user *uattr);
पूर्णांक bpf_prog_test_run_flow_dissector(काष्ठा bpf_prog *prog,
				     स्थिर जोड़ bpf_attr *kattr,
				     जोड़ bpf_attr __user *uattr);
पूर्णांक bpf_prog_test_run_raw_tp(काष्ठा bpf_prog *prog,
			     स्थिर जोड़ bpf_attr *kattr,
			     जोड़ bpf_attr __user *uattr);
पूर्णांक bpf_prog_test_run_sk_lookup(काष्ठा bpf_prog *prog,
				स्थिर जोड़ bpf_attr *kattr,
				जोड़ bpf_attr __user *uattr);
bool bpf_prog_test_check_kfunc_call(u32 kfunc_id);
bool btf_ctx_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
		    स्थिर काष्ठा bpf_prog *prog,
		    काष्ठा bpf_insn_access_aux *info);
पूर्णांक btf_काष्ठा_access(काष्ठा bpf_verअगरier_log *log, स्थिर काष्ठा btf *btf,
		      स्थिर काष्ठा btf_type *t, पूर्णांक off, पूर्णांक size,
		      क्रमागत bpf_access_type atype,
		      u32 *next_btf_id);
bool btf_काष्ठा_ids_match(काष्ठा bpf_verअगरier_log *log,
			  स्थिर काष्ठा btf *btf, u32 id, पूर्णांक off,
			  स्थिर काष्ठा btf *need_btf, u32 need_type_id);

पूर्णांक btf_distill_func_proto(काष्ठा bpf_verअगरier_log *log,
			   काष्ठा btf *btf,
			   स्थिर काष्ठा btf_type *func_proto,
			   स्थिर अक्षर *func_name,
			   काष्ठा btf_func_model *m);

काष्ठा bpf_reg_state;
पूर्णांक btf_check_subprog_arg_match(काष्ठा bpf_verअगरier_env *env, पूर्णांक subprog,
				काष्ठा bpf_reg_state *regs);
पूर्णांक btf_check_kfunc_arg_match(काष्ठा bpf_verअगरier_env *env,
			      स्थिर काष्ठा btf *btf, u32 func_id,
			      काष्ठा bpf_reg_state *regs);
पूर्णांक btf_prepare_func_args(काष्ठा bpf_verअगरier_env *env, पूर्णांक subprog,
			  काष्ठा bpf_reg_state *reg);
पूर्णांक btf_check_type_match(काष्ठा bpf_verअगरier_log *log, स्थिर काष्ठा bpf_prog *prog,
			 काष्ठा btf *btf, स्थिर काष्ठा btf_type *t);

काष्ठा bpf_prog *bpf_prog_by_id(u32 id);
काष्ठा bpf_link *bpf_link_by_id(u32 id);

स्थिर काष्ठा bpf_func_proto *bpf_base_func_proto(क्रमागत bpf_func_id func_id);
व्योम bpf_task_storage_मुक्त(काष्ठा task_काष्ठा *task);
bool bpf_prog_has_kfunc_call(स्थिर काष्ठा bpf_prog *prog);
स्थिर काष्ठा btf_func_model *
bpf_jit_find_kfunc_model(स्थिर काष्ठा bpf_prog *prog,
			 स्थिर काष्ठा bpf_insn *insn);
#अन्यथा /* !CONFIG_BPF_SYSCALL */
अटल अंतरभूत काष्ठा bpf_prog *bpf_prog_get(u32 ufd)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा bpf_prog *bpf_prog_get_type_dev(u32 ufd,
						     क्रमागत bpf_prog_type type,
						     bool attach_drv)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम bpf_prog_add(काष्ठा bpf_prog *prog, पूर्णांक i)
अणु
पूर्ण

अटल अंतरभूत व्योम bpf_prog_sub(काष्ठा bpf_prog *prog, पूर्णांक i)
अणु
पूर्ण

अटल अंतरभूत व्योम bpf_prog_put(काष्ठा bpf_prog *prog)
अणु
पूर्ण

अटल अंतरभूत व्योम bpf_prog_inc(काष्ठा bpf_prog *prog)
अणु
पूर्ण

अटल अंतरभूत काष्ठा bpf_prog *__must_check
bpf_prog_inc_not_zero(काष्ठा bpf_prog *prog)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम bpf_link_init(काष्ठा bpf_link *link, क्रमागत bpf_link_type type,
				 स्थिर काष्ठा bpf_link_ops *ops,
				 काष्ठा bpf_prog *prog)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक bpf_link_prime(काष्ठा bpf_link *link,
				 काष्ठा bpf_link_primer *primer)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_link_settle(काष्ठा bpf_link_primer *primer)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम bpf_link_cleanup(काष्ठा bpf_link_primer *primer)
अणु
पूर्ण

अटल अंतरभूत व्योम bpf_link_inc(काष्ठा bpf_link *link)
अणु
पूर्ण

अटल अंतरभूत व्योम bpf_link_put(काष्ठा bpf_link *link)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक bpf_obj_get_user(स्थिर अक्षर __user *pathname, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool dev_map_can_have_prog(काष्ठा bpf_map *map)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम __dev_flush(व्योम)
अणु
पूर्ण

काष्ठा xdp_buff;
काष्ठा bpf_dtab_netdev;
काष्ठा bpf_cpu_map_entry;

अटल अंतरभूत
पूर्णांक dev_xdp_enqueue(काष्ठा net_device *dev, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक dev_map_enqueue(काष्ठा bpf_dtab_netdev *dst, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx)
अणु
	वापस 0;
पूर्ण

काष्ठा sk_buff;

अटल अंतरभूत पूर्णांक dev_map_generic_redirect(काष्ठा bpf_dtab_netdev *dst,
					   काष्ठा sk_buff *skb,
					   काष्ठा bpf_prog *xdp_prog)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __cpu_map_flush(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक cpu_map_enqueue(काष्ठा bpf_cpu_map_entry *rcpu,
				  काष्ठा xdp_buff *xdp,
				  काष्ठा net_device *dev_rx)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool cpu_map_prog_allowed(काष्ठा bpf_map *map)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा bpf_prog *bpf_prog_get_type_path(स्थिर अक्षर *name,
				क्रमागत bpf_prog_type type)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक bpf_prog_test_run_xdp(काष्ठा bpf_prog *prog,
					स्थिर जोड़ bpf_attr *kattr,
					जोड़ bpf_attr __user *uattr)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_prog_test_run_skb(काष्ठा bpf_prog *prog,
					स्थिर जोड़ bpf_attr *kattr,
					जोड़ bpf_attr __user *uattr)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_prog_test_run_tracing(काष्ठा bpf_prog *prog,
					    स्थिर जोड़ bpf_attr *kattr,
					    जोड़ bpf_attr __user *uattr)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_prog_test_run_flow_dissector(काष्ठा bpf_prog *prog,
						   स्थिर जोड़ bpf_attr *kattr,
						   जोड़ bpf_attr __user *uattr)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_prog_test_run_sk_lookup(काष्ठा bpf_prog *prog,
					      स्थिर जोड़ bpf_attr *kattr,
					      जोड़ bpf_attr __user *uattr)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत bool bpf_prog_test_check_kfunc_call(u32 kfunc_id)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम bpf_map_put(काष्ठा bpf_map *map)
अणु
पूर्ण

अटल अंतरभूत काष्ठा bpf_prog *bpf_prog_by_id(u32 id)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा bpf_func_proto *
bpf_base_func_proto(क्रमागत bpf_func_id func_id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम bpf_task_storage_मुक्त(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत bool bpf_prog_has_kfunc_call(स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा btf_func_model *
bpf_jit_find_kfunc_model(स्थिर काष्ठा bpf_prog *prog,
			 स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */

व्योम __bpf_मुक्त_used_btfs(काष्ठा bpf_prog_aux *aux,
			  काष्ठा btf_mod_pair *used_btfs, u32 len);

अटल अंतरभूत काष्ठा bpf_prog *bpf_prog_get_type(u32 ufd,
						 क्रमागत bpf_prog_type type)
अणु
	वापस bpf_prog_get_type_dev(ufd, type, false);
पूर्ण

व्योम __bpf_मुक्त_used_maps(काष्ठा bpf_prog_aux *aux,
			  काष्ठा bpf_map **used_maps, u32 len);

bool bpf_prog_get_ok(काष्ठा bpf_prog *, क्रमागत bpf_prog_type *, bool);

पूर्णांक bpf_prog_offload_compile(काष्ठा bpf_prog *prog);
व्योम bpf_prog_offload_destroy(काष्ठा bpf_prog *prog);
पूर्णांक bpf_prog_offload_info_fill(काष्ठा bpf_prog_info *info,
			       काष्ठा bpf_prog *prog);

पूर्णांक bpf_map_offload_info_fill(काष्ठा bpf_map_info *info, काष्ठा bpf_map *map);

पूर्णांक bpf_map_offload_lookup_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value);
पूर्णांक bpf_map_offload_update_elem(काष्ठा bpf_map *map,
				व्योम *key, व्योम *value, u64 flags);
पूर्णांक bpf_map_offload_delete_elem(काष्ठा bpf_map *map, व्योम *key);
पूर्णांक bpf_map_offload_get_next_key(काष्ठा bpf_map *map,
				 व्योम *key, व्योम *next_key);

bool bpf_offload_prog_map_match(काष्ठा bpf_prog *prog, काष्ठा bpf_map *map);

काष्ठा bpf_offload_dev *
bpf_offload_dev_create(स्थिर काष्ठा bpf_prog_offload_ops *ops, व्योम *priv);
व्योम bpf_offload_dev_destroy(काष्ठा bpf_offload_dev *offdev);
व्योम *bpf_offload_dev_priv(काष्ठा bpf_offload_dev *offdev);
पूर्णांक bpf_offload_dev_netdev_रेजिस्टर(काष्ठा bpf_offload_dev *offdev,
				    काष्ठा net_device *netdev);
व्योम bpf_offload_dev_netdev_unरेजिस्टर(काष्ठा bpf_offload_dev *offdev,
				       काष्ठा net_device *netdev);
bool bpf_offload_dev_match(काष्ठा bpf_prog *prog, काष्ठा net_device *netdev);

#अगर defined(CONFIG_NET) && defined(CONFIG_BPF_SYSCALL)
पूर्णांक bpf_prog_offload_init(काष्ठा bpf_prog *prog, जोड़ bpf_attr *attr);

अटल अंतरभूत bool bpf_prog_is_dev_bound(स्थिर काष्ठा bpf_prog_aux *aux)
अणु
	वापस aux->offload_requested;
पूर्ण

अटल अंतरभूत bool bpf_map_is_dev_bound(काष्ठा bpf_map *map)
अणु
	वापस unlikely(map->ops == &bpf_map_offload_ops);
पूर्ण

काष्ठा bpf_map *bpf_map_offload_map_alloc(जोड़ bpf_attr *attr);
व्योम bpf_map_offload_map_मुक्त(काष्ठा bpf_map *map);
#अन्यथा
अटल अंतरभूत पूर्णांक bpf_prog_offload_init(काष्ठा bpf_prog *prog,
					जोड़ bpf_attr *attr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool bpf_prog_is_dev_bound(काष्ठा bpf_prog_aux *aux)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool bpf_map_is_dev_bound(काष्ठा bpf_map *map)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा bpf_map *bpf_map_offload_map_alloc(जोड़ bpf_attr *attr)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम bpf_map_offload_map_मुक्त(काष्ठा bpf_map *map)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NET && CONFIG_BPF_SYSCALL */

#अगर defined(CONFIG_INET) && defined(CONFIG_BPF_SYSCALL)
पूर्णांक sock_map_get_from_fd(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog);
पूर्णांक sock_map_prog_detach(स्थिर जोड़ bpf_attr *attr, क्रमागत bpf_prog_type ptype);
पूर्णांक sock_map_update_elem_sys(काष्ठा bpf_map *map, व्योम *key, व्योम *value, u64 flags);
व्योम sock_map_unhash(काष्ठा sock *sk);
व्योम sock_map_बंद(काष्ठा sock *sk, दीर्घ समयout);

व्योम bpf_sk_reuseport_detach(काष्ठा sock *sk);
पूर्णांक bpf_fd_reuseport_array_lookup_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value);
पूर्णांक bpf_fd_reuseport_array_update_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value, u64 map_flags);
#अन्यथा
अटल अंतरभूत व्योम bpf_sk_reuseport_detach(काष्ठा sock *sk)
अणु
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
अटल अंतरभूत पूर्णांक sock_map_get_from_fd(स्थिर जोड़ bpf_attr *attr,
				       काष्ठा bpf_prog *prog)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक sock_map_prog_detach(स्थिर जोड़ bpf_attr *attr,
				       क्रमागत bpf_prog_type ptype)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक sock_map_update_elem_sys(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
					   u64 flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_fd_reuseport_array_lookup_elem(काष्ठा bpf_map *map,
						     व्योम *key, व्योम *value)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_fd_reuseport_array_update_elem(काष्ठा bpf_map *map,
						     व्योम *key, व्योम *value,
						     u64 map_flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */
#पूर्ण_अगर /* defined(CONFIG_INET) && defined(CONFIG_BPF_SYSCALL) */

/* verअगरier prototypes क्रम helper functions called from eBPF programs */
बाह्य स्थिर काष्ठा bpf_func_proto bpf_map_lookup_elem_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_map_update_elem_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_map_delete_elem_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_map_push_elem_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_map_pop_elem_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_map_peek_elem_proto;

बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_pअक्रमom_u32_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_smp_processor_id_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_numa_node_id_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_tail_call_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_ns_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_boot_ns_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_current_pid_tgid_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_current_uid_gid_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_current_comm_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_stackid_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_stack_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_task_stack_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_stackid_proto_pe;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_stack_proto_pe;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sock_map_update_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sock_hash_update_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_current_cgroup_id_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_current_ancestor_cgroup_id_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_msg_redirect_hash_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_msg_redirect_map_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sk_redirect_hash_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sk_redirect_map_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_spin_lock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_spin_unlock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_local_storage_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_म_से_दीर्घ_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_म_से_अदीर्घ_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_tcp_sock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_jअगरfies64_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_ns_current_pid_tgid_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_event_output_data_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_ringbuf_output_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_ringbuf_reserve_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_ringbuf_submit_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_ringbuf_discard_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_ringbuf_query_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp6_sock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp_sock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp_समयरुको_sock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp_request_sock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_skc_to_udp6_sock_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_copy_from_user_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_snम_लिखो_btf_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_snम_लिखो_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_per_cpu_ptr_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_this_cpu_ptr_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_coarse_ns_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sock_from_file_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_get_socket_ptr_cookie_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_task_storage_get_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_task_storage_delete_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_क्रम_each_map_elem_proto;

स्थिर काष्ठा bpf_func_proto *bpf_tracing_func_proto(
	क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog);

स्थिर काष्ठा bpf_func_proto *tracing_prog_func_proto(
  क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog);

/* Shared helpers among cBPF and eBPF. */
व्योम bpf_user_rnd_init_once(व्योम);
u64 bpf_user_rnd_u32(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5);
u64 bpf_get_raw_cpu_id(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5);

#अगर defined(CONFIG_NET)
bool bpf_sock_common_is_valid_access(पूर्णांक off, पूर्णांक size,
				     क्रमागत bpf_access_type type,
				     काष्ठा bpf_insn_access_aux *info);
bool bpf_sock_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
			      काष्ठा bpf_insn_access_aux *info);
u32 bpf_sock_convert_ctx_access(क्रमागत bpf_access_type type,
				स्थिर काष्ठा bpf_insn *si,
				काष्ठा bpf_insn *insn_buf,
				काष्ठा bpf_prog *prog,
				u32 *target_size);
#अन्यथा
अटल अंतरभूत bool bpf_sock_common_is_valid_access(पूर्णांक off, पूर्णांक size,
						   क्रमागत bpf_access_type type,
						   काष्ठा bpf_insn_access_aux *info)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool bpf_sock_is_valid_access(पूर्णांक off, पूर्णांक size,
					    क्रमागत bpf_access_type type,
					    काष्ठा bpf_insn_access_aux *info)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत u32 bpf_sock_convert_ctx_access(क्रमागत bpf_access_type type,
					      स्थिर काष्ठा bpf_insn *si,
					      काष्ठा bpf_insn *insn_buf,
					      काष्ठा bpf_prog *prog,
					      u32 *target_size)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_INET
काष्ठा sk_reuseport_kern अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;
	काष्ठा sock *selected_sk;
	व्योम *data_end;
	u32 hash;
	u32 reuseport_id;
	bool bind_inany;
पूर्ण;
bool bpf_tcp_sock_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				  काष्ठा bpf_insn_access_aux *info);

u32 bpf_tcp_sock_convert_ctx_access(क्रमागत bpf_access_type type,
				    स्थिर काष्ठा bpf_insn *si,
				    काष्ठा bpf_insn *insn_buf,
				    काष्ठा bpf_prog *prog,
				    u32 *target_size);

bool bpf_xdp_sock_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				  काष्ठा bpf_insn_access_aux *info);

u32 bpf_xdp_sock_convert_ctx_access(क्रमागत bpf_access_type type,
				    स्थिर काष्ठा bpf_insn *si,
				    काष्ठा bpf_insn *insn_buf,
				    काष्ठा bpf_prog *prog,
				    u32 *target_size);
#अन्यथा
अटल अंतरभूत bool bpf_tcp_sock_is_valid_access(पूर्णांक off, पूर्णांक size,
						क्रमागत bpf_access_type type,
						काष्ठा bpf_insn_access_aux *info)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 bpf_tcp_sock_convert_ctx_access(क्रमागत bpf_access_type type,
						  स्थिर काष्ठा bpf_insn *si,
						  काष्ठा bpf_insn *insn_buf,
						  काष्ठा bpf_prog *prog,
						  u32 *target_size)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool bpf_xdp_sock_is_valid_access(पूर्णांक off, पूर्णांक size,
						क्रमागत bpf_access_type type,
						काष्ठा bpf_insn_access_aux *info)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 bpf_xdp_sock_convert_ctx_access(क्रमागत bpf_access_type type,
						  स्थिर काष्ठा bpf_insn *si,
						  काष्ठा bpf_insn *insn_buf,
						  काष्ठा bpf_prog *prog,
						  u32 *target_size)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_INET */

क्रमागत bpf_text_poke_type अणु
	BPF_MOD_CALL,
	BPF_MOD_JUMP,
पूर्ण;

पूर्णांक bpf_arch_text_poke(व्योम *ip, क्रमागत bpf_text_poke_type t,
		       व्योम *addr1, व्योम *addr2);

काष्ठा btf_id_set;
bool btf_id_set_contains(स्थिर काष्ठा btf_id_set *set, u32 id);

पूर्णांक bpf_bम_लिखो_prepare(अक्षर *fmt, u32 fmt_size, स्थिर u64 *raw_args,
			u32 **bin_buf, u32 num_args);
व्योम bpf_bम_लिखो_cleanup(व्योम);

#पूर्ण_अगर /* _LINUX_BPF_H */
