<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2018 Netronome Systems, Inc. */

#अगर_अघोषित __BPF_TOOL_XLATED_DUMPER_H
#घोषणा __BPF_TOOL_XLATED_DUMPER_H

#घोषणा SYM_MAX_NAME	256

काष्ठा bpf_prog_linfo;

काष्ठा kernel_sym अणु
	अचिन्हित दीर्घ address;
	अक्षर name[SYM_MAX_NAME];
पूर्ण;

काष्ठा dump_data अणु
	अचिन्हित दीर्घ address_call_base;
	काष्ठा kernel_sym *sym_mapping;
	__u32 sym_count;
	__u64 *jited_ksyms;
	__u32 nr_jited_ksyms;
	काष्ठा btf *btf;
	व्योम *func_info;
	__u32 finfo_rec_size;
	स्थिर काष्ठा bpf_prog_linfo *prog_linfo;
	अक्षर scratch_buff[SYM_MAX_NAME + 8];
पूर्ण;

व्योम kernel_syms_load(काष्ठा dump_data *dd);
व्योम kernel_syms_destroy(काष्ठा dump_data *dd);
काष्ठा kernel_sym *kernel_syms_search(काष्ठा dump_data *dd, अचिन्हित दीर्घ key);
व्योम dump_xlated_json(काष्ठा dump_data *dd, व्योम *buf, अचिन्हित पूर्णांक len,
		       bool opcodes, bool linum);
व्योम dump_xlated_plain(काष्ठा dump_data *dd, व्योम *buf, अचिन्हित पूर्णांक len,
		       bool opcodes, bool linum);
व्योम dump_xlated_क्रम_graph(काष्ठा dump_data *dd, व्योम *buf, व्योम *buf_end,
			   अचिन्हित पूर्णांक start_index);

#पूर्ण_अगर
