<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Copyright (C) 2020 Google LLC.
 */

#अगर_अघोषित _LINUX_BPF_LSM_H
#घोषणा _LINUX_BPF_LSM_H

#समावेश <linux/sched.h>
#समावेश <linux/bpf.h>
#समावेश <linux/lsm_hooks.h>

#अगर_घोषित CONFIG_BPF_LSM

#घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...) \
	RET bpf_lsm_##NAME(__VA_ARGS__);
#समावेश <linux/lsm_hook_defs.h>
#अघोषित LSM_HOOK

काष्ठा bpf_storage_blob अणु
	काष्ठा bpf_local_storage __rcu *storage;
पूर्ण;

बाह्य काष्ठा lsm_blob_sizes bpf_lsm_blob_sizes;

पूर्णांक bpf_lsm_verअगरy_prog(काष्ठा bpf_verअगरier_log *vlog,
			स्थिर काष्ठा bpf_prog *prog);

bool bpf_lsm_is_sleepable_hook(u32 btf_id);

अटल अंतरभूत काष्ठा bpf_storage_blob *bpf_inode(
	स्थिर काष्ठा inode *inode)
अणु
	अगर (unlikely(!inode->i_security))
		वापस शून्य;

	वापस inode->i_security + bpf_lsm_blob_sizes.lbs_inode;
पूर्ण

बाह्य स्थिर काष्ठा bpf_func_proto bpf_inode_storage_get_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_inode_storage_delete_proto;
व्योम bpf_inode_storage_मुक्त(काष्ठा inode *inode);

#अन्यथा /* !CONFIG_BPF_LSM */

अटल अंतरभूत bool bpf_lsm_is_sleepable_hook(u32 btf_id)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_lsm_verअगरy_prog(काष्ठा bpf_verअगरier_log *vlog,
				      स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा bpf_storage_blob *bpf_inode(
	स्थिर काष्ठा inode *inode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम bpf_inode_storage_मुक्त(काष्ठा inode *inode)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BPF_LSM */

#पूर्ण_अगर /* _LINUX_BPF_LSM_H */
