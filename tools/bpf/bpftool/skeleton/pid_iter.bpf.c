<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (c) 2020 Facebook */
#समावेश <vmlinux.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश "pid_iter.h"

/* keep in sync with the definition in मुख्य.h */
क्रमागत bpf_obj_type अणु
	BPF_OBJ_UNKNOWN,
	BPF_OBJ_PROG,
	BPF_OBJ_MAP,
	BPF_OBJ_LINK,
	BPF_OBJ_BTF,
पूर्ण;

बाह्य स्थिर व्योम bpf_link_fops __ksym;
बाह्य स्थिर व्योम bpf_map_fops __ksym;
बाह्य स्थिर व्योम bpf_prog_fops __ksym;
बाह्य स्थिर व्योम btf_fops __ksym;

स्थिर अस्थिर क्रमागत bpf_obj_type obj_type = BPF_OBJ_UNKNOWN;

अटल __always_अंतरभूत __u32 get_obj_id(व्योम *ent, क्रमागत bpf_obj_type type)
अणु
	चयन (type) अणु
	हाल BPF_OBJ_PROG:
		वापस BPF_CORE_READ((काष्ठा bpf_prog *)ent, aux, id);
	हाल BPF_OBJ_MAP:
		वापस BPF_CORE_READ((काष्ठा bpf_map *)ent, id);
	हाल BPF_OBJ_BTF:
		वापस BPF_CORE_READ((काष्ठा btf *)ent, id);
	हाल BPF_OBJ_LINK:
		वापस BPF_CORE_READ((काष्ठा bpf_link *)ent, id);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

SEC("iter/task_file")
पूर्णांक iter(काष्ठा bpf_iter__task_file *ctx)
अणु
	काष्ठा file *file = ctx->file;
	काष्ठा task_काष्ठा *task = ctx->task;
	काष्ठा pid_iter_entry e;
	स्थिर व्योम *fops;

	अगर (!file || !task)
		वापस 0;

	चयन (obj_type) अणु
	हाल BPF_OBJ_PROG:
		fops = &bpf_prog_fops;
		अवरोध;
	हाल BPF_OBJ_MAP:
		fops = &bpf_map_fops;
		अवरोध;
	हाल BPF_OBJ_BTF:
		fops = &btf_fops;
		अवरोध;
	हाल BPF_OBJ_LINK:
		fops = &bpf_link_fops;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (file->f_op != fops)
		वापस 0;

	e.pid = task->tgid;
	e.id = get_obj_id(file->निजी_data, obj_type);
	bpf_probe_पढ़ो_kernel(&e.comm, माप(e.comm),
			      task->group_leader->comm);
	bpf_seq_ग_लिखो(ctx->meta->seq, &e, माप(e));

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "Dual BSD/GPL";
