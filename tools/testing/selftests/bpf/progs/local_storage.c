<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2020 Google LLC.
 */

#समावेश "vmlinux.h"
#समावेश <त्रुटिसं.स>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

#घोषणा DUMMY_STORAGE_VALUE 0xdeadbeef

पूर्णांक monitored_pid = 0;
पूर्णांक inode_storage_result = -1;
पूर्णांक sk_storage_result = -1;

काष्ठा local_storage अणु
	काष्ठा inode *exec_inode;
	__u32 value;
	काष्ठा bpf_spin_lock lock;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_INODE_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा local_storage);
पूर्ण inode_storage_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC | BPF_F_CLONE);
	__type(key, पूर्णांक);
	__type(value, काष्ठा local_storage);
पूर्ण sk_storage_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_TASK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा local_storage);
पूर्ण task_storage_map SEC(".maps");

SEC("lsm/inode_unlink")
पूर्णांक BPF_PROG(unlink_hook, काष्ठा inode *dir, काष्ठा dentry *victim)
अणु
	__u32 pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा local_storage *storage;
	bool is_self_unlink;

	अगर (pid != monitored_pid)
		वापस 0;

	storage = bpf_task_storage_get(&task_storage_map,
				       bpf_get_current_task_btf(), 0, 0);
	अगर (storage) अणु
		/* Don't let an executable delete itself */
		bpf_spin_lock(&storage->lock);
		is_self_unlink = storage->exec_inode == victim->d_inode;
		bpf_spin_unlock(&storage->lock);
		अगर (is_self_unlink)
			वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

SEC("lsm/inode_rename")
पूर्णांक BPF_PROG(inode_नाम, काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
	     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
	     अचिन्हित पूर्णांक flags)
अणु
	__u32 pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा local_storage *storage;
	पूर्णांक err;

	/* new_dentry->d_inode can be शून्य when the inode is नामd to a file
	 * that did not exist beक्रमe. The helper should be able to handle this
	 * शून्य poपूर्णांकer.
	 */
	bpf_inode_storage_get(&inode_storage_map, new_dentry->d_inode, 0,
			      BPF_LOCAL_STORAGE_GET_F_CREATE);

	storage = bpf_inode_storage_get(&inode_storage_map, old_dentry->d_inode,
					0, 0);
	अगर (!storage)
		वापस 0;

	bpf_spin_lock(&storage->lock);
	अगर (storage->value != DUMMY_STORAGE_VALUE)
		inode_storage_result = -1;
	bpf_spin_unlock(&storage->lock);

	err = bpf_inode_storage_delete(&inode_storage_map, old_dentry->d_inode);
	अगर (!err)
		inode_storage_result = err;

	वापस 0;
पूर्ण

SEC("lsm/socket_bind")
पूर्णांक BPF_PROG(socket_bind, काष्ठा socket *sock, काष्ठा sockaddr *address,
	     पूर्णांक addrlen)
अणु
	__u32 pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा local_storage *storage;
	पूर्णांक err;

	अगर (pid != monitored_pid)
		वापस 0;

	storage = bpf_sk_storage_get(&sk_storage_map, sock->sk, 0,
				     BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (!storage)
		वापस 0;

	bpf_spin_lock(&storage->lock);
	अगर (storage->value != DUMMY_STORAGE_VALUE)
		sk_storage_result = -1;
	bpf_spin_unlock(&storage->lock);

	err = bpf_sk_storage_delete(&sk_storage_map, sock->sk);
	अगर (!err)
		sk_storage_result = err;

	वापस 0;
पूर्ण

SEC("lsm/socket_post_create")
पूर्णांक BPF_PROG(socket_post_create, काष्ठा socket *sock, पूर्णांक family, पूर्णांक type,
	     पूर्णांक protocol, पूर्णांक kern)
अणु
	__u32 pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा local_storage *storage;

	अगर (pid != monitored_pid)
		वापस 0;

	storage = bpf_sk_storage_get(&sk_storage_map, sock->sk, 0,
				     BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (!storage)
		वापस 0;

	bpf_spin_lock(&storage->lock);
	storage->value = DUMMY_STORAGE_VALUE;
	bpf_spin_unlock(&storage->lock);

	वापस 0;
पूर्ण

/* This uses the local storage to remember the inode of the binary that a
 * process was originally executing.
 */
SEC("lsm/bprm_committed_creds")
व्योम BPF_PROG(exec, काष्ठा linux_binprm *bprm)
अणु
	__u32 pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा local_storage *storage;

	अगर (pid != monitored_pid)
		वापस;

	storage = bpf_task_storage_get(&task_storage_map,
				       bpf_get_current_task_btf(), 0,
				       BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (storage) अणु
		bpf_spin_lock(&storage->lock);
		storage->exec_inode = bprm->file->f_inode;
		bpf_spin_unlock(&storage->lock);
	पूर्ण

	storage = bpf_inode_storage_get(&inode_storage_map, bprm->file->f_inode,
					0, BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (!storage)
		वापस;

	bpf_spin_lock(&storage->lock);
	storage->value = DUMMY_STORAGE_VALUE;
	bpf_spin_unlock(&storage->lock);
पूर्ण
