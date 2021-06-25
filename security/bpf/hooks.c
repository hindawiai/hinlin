<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright (C) 2020 Google LLC.
 */
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/bpf_lsm.h>

अटल काष्ठा security_hook_list bpf_lsm_hooks[] __lsm_ro_after_init = अणु
	#घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...) \
	LSM_HOOK_INIT(NAME, bpf_lsm_##NAME),
	#समावेश <linux/lsm_hook_defs.h>
	#अघोषित LSM_HOOK
	LSM_HOOK_INIT(inode_मुक्त_security, bpf_inode_storage_मुक्त),
	LSM_HOOK_INIT(task_मुक्त, bpf_task_storage_मुक्त),
पूर्ण;

अटल पूर्णांक __init bpf_lsm_init(व्योम)
अणु
	security_add_hooks(bpf_lsm_hooks, ARRAY_SIZE(bpf_lsm_hooks), "bpf");
	pr_info("LSM support for eBPF active\n");
	वापस 0;
पूर्ण

काष्ठा lsm_blob_sizes bpf_lsm_blob_sizes __lsm_ro_after_init = अणु
	.lbs_inode = माप(काष्ठा bpf_storage_blob),
	.lbs_task = माप(काष्ठा bpf_storage_blob),
पूर्ण;

DEFINE_LSM(bpf) = अणु
	.name = "bpf",
	.init = bpf_lsm_init,
	.blobs = &bpf_lsm_blob_sizes
पूर्ण;
