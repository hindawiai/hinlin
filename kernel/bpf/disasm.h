<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2016 Facebook
 */

#अगर_अघोषित __BPF_DISASM_H__
#घोषणा __BPF_DISASM_H__

#समावेश <linux/bpf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/stringअगरy.h>
#अगर_अघोषित __KERNEL__
#समावेश <मानकपन.स>
#समावेश <माला.स>
#पूर्ण_अगर

बाह्य स्थिर अक्षर *स्थिर bpf_alu_string[16];
बाह्य स्थिर अक्षर *स्थिर bpf_class_string[8];

स्थिर अक्षर *func_id_name(पूर्णांक id);

प्रकार __म_लिखो(2, 3) व्योम (*bpf_insn_prपूर्णांक_t)(व्योम *निजी_data,
						स्थिर अक्षर *, ...);
प्रकार स्थिर अक्षर *(*bpf_insn_revmap_call_t)(व्योम *निजी_data,
					      स्थिर काष्ठा bpf_insn *insn);
प्रकार स्थिर अक्षर *(*bpf_insn_prपूर्णांक_imm_t)(व्योम *निजी_data,
					    स्थिर काष्ठा bpf_insn *insn,
					    __u64 full_imm);

काष्ठा bpf_insn_cbs अणु
	bpf_insn_prपूर्णांक_t	cb_prपूर्णांक;
	bpf_insn_revmap_call_t	cb_call;
	bpf_insn_prपूर्णांक_imm_t	cb_imm;
	व्योम			*निजी_data;
पूर्ण;

व्योम prपूर्णांक_bpf_insn(स्थिर काष्ठा bpf_insn_cbs *cbs,
		    स्थिर काष्ठा bpf_insn *insn,
		    bool allow_ptr_leaks);
#पूर्ण_अगर
