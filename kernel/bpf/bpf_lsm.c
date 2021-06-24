<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright (C) 2020 Google LLC.
 */

#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/bpf_lsm.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <net/bpf_sk_storage.h>
#समावेश <linux/bpf_local_storage.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/ima.h>

/* For every LSM hook that allows attachment of BPF programs, declare a nop
 * function where a BPF program can be attached.
 */
#घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...)	\
noअंतरभूत RET bpf_lsm_##NAME(__VA_ARGS__)	\
अणु						\
	वापस DEFAULT;				\
पूर्ण

#समावेश <linux/lsm_hook_defs.h>
#अघोषित LSM_HOOK

#घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...) BTF_ID(func, bpf_lsm_##NAME)
BTF_SET_START(bpf_lsm_hooks)
#समावेश <linux/lsm_hook_defs.h>
#अघोषित LSM_HOOK
BTF_SET_END(bpf_lsm_hooks)

पूर्णांक bpf_lsm_verअगरy_prog(काष्ठा bpf_verअगरier_log *vlog,
			स्थिर काष्ठा bpf_prog *prog)
अणु
	अगर (!prog->gpl_compatible) अणु
		bpf_log(vlog,
			"LSM programs must have a GPL compatible license\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!btf_id_set_contains(&bpf_lsm_hooks, prog->aux->attach_btf_id)) अणु
		bpf_log(vlog, "attach_btf_id %u points to wrong type name %s\n",
			prog->aux->attach_btf_id, prog->aux->attach_func_name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Mask क्रम all the currently supported BPRM option flags */
#घोषणा BPF_F_BRPM_OPTS_MASK	BPF_F_BPRM_SECUREEXEC

BPF_CALL_2(bpf_bprm_opts_set, काष्ठा linux_binprm *, bprm, u64, flags)
अणु
	अगर (flags & ~BPF_F_BRPM_OPTS_MASK)
		वापस -EINVAL;

	bprm->secureexec = (flags & BPF_F_BPRM_SECUREEXEC);
	वापस 0;
पूर्ण

BTF_ID_LIST_SINGLE(bpf_bprm_opts_set_btf_ids, काष्ठा, linux_binprm)

अटल स्थिर काष्ठा bpf_func_proto bpf_bprm_opts_set_proto = अणु
	.func		= bpf_bprm_opts_set,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &bpf_bprm_opts_set_btf_ids[0],
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_ima_inode_hash, काष्ठा inode *, inode, व्योम *, dst, u32, size)
अणु
	वापस ima_inode_hash(inode, dst, size);
पूर्ण

अटल bool bpf_ima_inode_hash_allowed(स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस bpf_lsm_is_sleepable_hook(prog->aux->attach_btf_id);
पूर्ण

BTF_ID_LIST_SINGLE(bpf_ima_inode_hash_btf_ids, काष्ठा, inode)

अटल स्थिर काष्ठा bpf_func_proto bpf_ima_inode_hash_proto = अणु
	.func		= bpf_ima_inode_hash,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &bpf_ima_inode_hash_btf_ids[0],
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.allowed	= bpf_ima_inode_hash_allowed,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
bpf_lsm_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_inode_storage_get:
		वापस &bpf_inode_storage_get_proto;
	हाल BPF_FUNC_inode_storage_delete:
		वापस &bpf_inode_storage_delete_proto;
#अगर_घोषित CONFIG_NET
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
#पूर्ण_अगर /* CONFIG_NET */
	हाल BPF_FUNC_spin_lock:
		वापस &bpf_spin_lock_proto;
	हाल BPF_FUNC_spin_unlock:
		वापस &bpf_spin_unlock_proto;
	हाल BPF_FUNC_bprm_opts_set:
		वापस &bpf_bprm_opts_set_proto;
	हाल BPF_FUNC_ima_inode_hash:
		वापस prog->aux->sleepable ? &bpf_ima_inode_hash_proto : शून्य;
	शेष:
		वापस tracing_prog_func_proto(func_id, prog);
	पूर्ण
पूर्ण

/* The set of hooks which are called without pagefaults disabled and are allowed
 * to "sleep" and thus can be used क्रम sleeable BPF programs.
 */
BTF_SET_START(sleepable_lsm_hooks)
BTF_ID(func, bpf_lsm_bpf)
BTF_ID(func, bpf_lsm_bpf_map)
BTF_ID(func, bpf_lsm_bpf_map_alloc_security)
BTF_ID(func, bpf_lsm_bpf_map_मुक्त_security)
BTF_ID(func, bpf_lsm_bpf_prog)
BTF_ID(func, bpf_lsm_bprm_check_security)
BTF_ID(func, bpf_lsm_bprm_committed_creds)
BTF_ID(func, bpf_lsm_bprm_committing_creds)
BTF_ID(func, bpf_lsm_bprm_creds_क्रम_exec)
BTF_ID(func, bpf_lsm_bprm_creds_from_file)
BTF_ID(func, bpf_lsm_capget)
BTF_ID(func, bpf_lsm_capset)
BTF_ID(func, bpf_lsm_cred_prepare)
BTF_ID(func, bpf_lsm_file_ioctl)
BTF_ID(func, bpf_lsm_file_lock)
BTF_ID(func, bpf_lsm_file_खोलो)
BTF_ID(func, bpf_lsm_file_receive)

#अगर_घोषित CONFIG_SECURITY_NETWORK
BTF_ID(func, bpf_lsm_inet_conn_established)
#पूर्ण_अगर /* CONFIG_SECURITY_NETWORK */

BTF_ID(func, bpf_lsm_inode_create)
BTF_ID(func, bpf_lsm_inode_मुक्त_security)
BTF_ID(func, bpf_lsm_inode_getattr)
BTF_ID(func, bpf_lsm_inode_getxattr)
BTF_ID(func, bpf_lsm_inode_mknod)
BTF_ID(func, bpf_lsm_inode_need_समाप्तpriv)
BTF_ID(func, bpf_lsm_inode_post_setxattr)
BTF_ID(func, bpf_lsm_inode_पढ़ोlink)
BTF_ID(func, bpf_lsm_inode_नाम)
BTF_ID(func, bpf_lsm_inode_सूची_हटाओ)
BTF_ID(func, bpf_lsm_inode_setattr)
BTF_ID(func, bpf_lsm_inode_setxattr)
BTF_ID(func, bpf_lsm_inode_symlink)
BTF_ID(func, bpf_lsm_inode_unlink)
BTF_ID(func, bpf_lsm_kernel_module_request)
BTF_ID(func, bpf_lsm_kernfs_init_security)

#अगर_घोषित CONFIG_KEYS
BTF_ID(func, bpf_lsm_key_मुक्त)
#पूर्ण_अगर /* CONFIG_KEYS */

BTF_ID(func, bpf_lsm_mmap_file)
BTF_ID(func, bpf_lsm_netlink_send)
BTF_ID(func, bpf_lsm_path_notअगरy)
BTF_ID(func, bpf_lsm_release_secctx)
BTF_ID(func, bpf_lsm_sb_alloc_security)
BTF_ID(func, bpf_lsm_sb_eat_lsm_opts)
BTF_ID(func, bpf_lsm_sb_kern_mount)
BTF_ID(func, bpf_lsm_sb_mount)
BTF_ID(func, bpf_lsm_sb_remount)
BTF_ID(func, bpf_lsm_sb_set_mnt_opts)
BTF_ID(func, bpf_lsm_sb_show_options)
BTF_ID(func, bpf_lsm_sb_statfs)
BTF_ID(func, bpf_lsm_sb_umount)
BTF_ID(func, bpf_lsm_समय_रखो)

#अगर_घोषित CONFIG_SECURITY_NETWORK
BTF_ID(func, bpf_lsm_socket_accept)
BTF_ID(func, bpf_lsm_socket_bind)
BTF_ID(func, bpf_lsm_socket_connect)
BTF_ID(func, bpf_lsm_socket_create)
BTF_ID(func, bpf_lsm_socket_getpeername)
BTF_ID(func, bpf_lsm_socket_getpeersec_dgram)
BTF_ID(func, bpf_lsm_socket_माला_लोockname)
BTF_ID(func, bpf_lsm_socket_माला_लोockopt)
BTF_ID(func, bpf_lsm_socket_listen)
BTF_ID(func, bpf_lsm_socket_post_create)
BTF_ID(func, bpf_lsm_socket_recvmsg)
BTF_ID(func, bpf_lsm_socket_sendmsg)
BTF_ID(func, bpf_lsm_socket_shutकरोwn)
BTF_ID(func, bpf_lsm_socket_socketpair)
#पूर्ण_अगर /* CONFIG_SECURITY_NETWORK */

BTF_ID(func, bpf_lsm_syslog)
BTF_ID(func, bpf_lsm_task_alloc)
BTF_ID(func, bpf_lsm_task_माला_लोecid_subj)
BTF_ID(func, bpf_lsm_task_माला_लोecid_obj)
BTF_ID(func, bpf_lsm_task_prctl)
BTF_ID(func, bpf_lsm_task_setscheduler)
BTF_ID(func, bpf_lsm_task_to_inode)
BTF_SET_END(sleepable_lsm_hooks)

bool bpf_lsm_is_sleepable_hook(u32 btf_id)
अणु
	वापस btf_id_set_contains(&sleepable_lsm_hooks, btf_id);
पूर्ण

स्थिर काष्ठा bpf_prog_ops lsm_prog_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops lsm_verअगरier_ops = अणु
	.get_func_proto = bpf_lsm_func_proto,
	.is_valid_access = btf_ctx_access,
पूर्ण;
