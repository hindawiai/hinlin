<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_BPF_H
#घोषणा _XT_BPF_H

#समावेश <linux/filter.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/types.h>

#घोषणा XT_BPF_MAX_NUM_INSTR	64
#घोषणा XT_BPF_PATH_MAX		(XT_BPF_MAX_NUM_INSTR * माप(काष्ठा sock_filter))

काष्ठा bpf_prog;

काष्ठा xt_bpf_info अणु
	__u16 bpf_program_num_elem;
	काष्ठा sock_filter bpf_program[XT_BPF_MAX_NUM_INSTR];

	/* only used in the kernel */
	काष्ठा bpf_prog *filter __attribute__((aligned(8)));
पूर्ण;

क्रमागत xt_bpf_modes अणु
	XT_BPF_MODE_BYTECODE,
	XT_BPF_MODE_FD_PINNED,
	XT_BPF_MODE_FD_ELF,
पूर्ण;
#घोषणा XT_BPF_MODE_PATH_PINNED XT_BPF_MODE_FD_PINNED

काष्ठा xt_bpf_info_v1 अणु
	__u16 mode;
	__u16 bpf_program_num_elem;
	__s32 fd;
	जोड़ अणु
		काष्ठा sock_filter bpf_program[XT_BPF_MAX_NUM_INSTR];
		अक्षर path[XT_BPF_PATH_MAX];
	पूर्ण;

	/* only used in the kernel */
	काष्ठा bpf_prog *filter __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /*_XT_BPF_H */
