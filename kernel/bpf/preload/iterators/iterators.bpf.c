<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

#आशय clang attribute push (__attribute__((preserve_access_index)), apply_to = record)
काष्ठा seq_file;
काष्ठा bpf_iter_meta अणु
	काष्ठा seq_file *seq;
	__u64 session_id;
	__u64 seq_num;
पूर्ण;

काष्ठा bpf_map अणु
	__u32 id;
	अक्षर name[16];
	__u32 max_entries;
पूर्ण;

काष्ठा bpf_iter__bpf_map अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा bpf_map *map;
पूर्ण;

काष्ठा btf_type अणु
	__u32 name_off;
पूर्ण;

काष्ठा btf_header अणु
	__u32   str_len;
पूर्ण;

काष्ठा btf अणु
	स्थिर अक्षर *strings;
	काष्ठा btf_type **types;
	काष्ठा btf_header hdr;
पूर्ण;

काष्ठा bpf_prog_aux अणु
	__u32 id;
	अक्षर name[16];
	स्थिर अक्षर *attach_func_name;
	काष्ठा bpf_prog *dst_prog;
	काष्ठा bpf_func_info *func_info;
	काष्ठा btf *btf;
पूर्ण;

काष्ठा bpf_prog अणु
	काष्ठा bpf_prog_aux *aux;
पूर्ण;

काष्ठा bpf_iter__bpf_prog अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा bpf_prog *prog;
पूर्ण;
#आशय clang attribute pop

अटल स्थिर अक्षर *get_name(काष्ठा btf *btf, दीर्घ btf_id, स्थिर अक्षर *fallback)
अणु
	काष्ठा btf_type **types, *t;
	अचिन्हित पूर्णांक name_off;
	स्थिर अक्षर *str;

	अगर (!btf)
		वापस fallback;
	str = btf->strings;
	types = btf->types;
	bpf_probe_पढ़ो_kernel(&t, माप(t), types + btf_id);
	name_off = BPF_CORE_READ(t, name_off);
	अगर (name_off >= btf->hdr.str_len)
		वापस fallback;
	वापस str + name_off;
पूर्ण

SEC("iter/bpf_map")
पूर्णांक dump_bpf_map(काष्ठा bpf_iter__bpf_map *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	__u64 seq_num = ctx->meta->seq_num;
	काष्ठा bpf_map *map = ctx->map;

	अगर (!map)
		वापस 0;

	अगर (seq_num == 0)
		BPF_SEQ_PRINTF(seq, "  id name             max_entries\n");

	BPF_SEQ_PRINTF(seq, "%4u %-16s%6d\n", map->id, map->name, map->max_entries);
	वापस 0;
पूर्ण

SEC("iter/bpf_prog")
पूर्णांक dump_bpf_prog(काष्ठा bpf_iter__bpf_prog *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	__u64 seq_num = ctx->meta->seq_num;
	काष्ठा bpf_prog *prog = ctx->prog;
	काष्ठा bpf_prog_aux *aux;

	अगर (!prog)
		वापस 0;

	aux = prog->aux;
	अगर (seq_num == 0)
		BPF_SEQ_PRINTF(seq, "  id name             attached\n");

	BPF_SEQ_PRINTF(seq, "%4u %-16s %s %s\n", aux->id,
		       get_name(aux->btf, aux->func_info[0].type_id, aux->name),
		       aux->attach_func_name, aux->dst_prog->aux->name);
	वापस 0;
पूर्ण
अक्षर LICENSE[] SEC("license") = "GPL";
