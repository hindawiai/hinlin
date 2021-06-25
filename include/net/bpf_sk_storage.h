<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 Facebook */
#अगर_अघोषित _BPF_SK_STORAGE_H
#घोषणा _BPF_SK_STORAGE_H

#समावेश <linux/rculist.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bpf.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/sock_diag.h>
#समावेश <uapi/linux/btf.h>
#समावेश <linux/bpf_local_storage.h>

काष्ठा sock;

व्योम bpf_sk_storage_मुक्त(काष्ठा sock *sk);

बाह्य स्थिर काष्ठा bpf_func_proto bpf_sk_storage_get_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sk_storage_delete_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sk_storage_get_tracing_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_sk_storage_delete_tracing_proto;

काष्ठा bpf_local_storage_elem;
काष्ठा bpf_sk_storage_diag;
काष्ठा sk_buff;
काष्ठा nlattr;

#अगर_घोषित CONFIG_BPF_SYSCALL
पूर्णांक bpf_sk_storage_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk);
काष्ठा bpf_sk_storage_diag *
bpf_sk_storage_diag_alloc(स्थिर काष्ठा nlattr *nla_stgs);
व्योम bpf_sk_storage_diag_मुक्त(काष्ठा bpf_sk_storage_diag *diag);
पूर्णांक bpf_sk_storage_diag_put(काष्ठा bpf_sk_storage_diag *diag,
			    काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    पूर्णांक stg_array_type,
			    अचिन्हित पूर्णांक *res_diag_size);
#अन्यथा
अटल अंतरभूत पूर्णांक bpf_sk_storage_clone(स्थिर काष्ठा sock *sk,
				       काष्ठा sock *newsk)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा bpf_sk_storage_diag *
bpf_sk_storage_diag_alloc(स्थिर काष्ठा nlattr *nla)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम bpf_sk_storage_diag_मुक्त(काष्ठा bpf_sk_storage_diag *diag)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक bpf_sk_storage_diag_put(काष्ठा bpf_sk_storage_diag *diag,
					  काष्ठा sock *sk, काष्ठा sk_buff *skb,
					  पूर्णांक stg_array_type,
					  अचिन्हित पूर्णांक *res_diag_size)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _BPF_SK_STORAGE_H */
