<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015, He Kuang <hekuang@huawei.com>
 * Copyright (C) 2015, Huawei Inc.
 */
#अगर_अघोषित __BPF_PROLOGUE_H
#घोषणा __BPF_PROLOGUE_H

#समावेश <linux/compiler.h>
#समावेश <linux/filter.h>
#समावेश "probe-event.h"

#घोषणा BPF_PROLOGUE_MAX_ARGS 3
#घोषणा BPF_PROLOGUE_START_ARG_REG BPF_REG_3
#घोषणा BPF_PROLOGUE_FETCH_RESULT_REG BPF_REG_2

#अगर_घोषित HAVE_BPF_PROLOGUE
पूर्णांक bpf__gen_prologue(काष्ठा probe_trace_arg *args, पूर्णांक nargs,
		      काष्ठा bpf_insn *new_prog, माप_प्रकार *new_cnt,
		      माप_प्रकार cnt_space);
#अन्यथा
#समावेश <त्रुटिसं.स>

अटल अंतरभूत पूर्णांक
bpf__gen_prologue(काष्ठा probe_trace_arg *args __maybe_unused,
		  पूर्णांक nargs __maybe_unused,
		  काष्ठा bpf_insn *new_prog __maybe_unused,
		  माप_प्रकार *new_cnt,
		  माप_प्रकार cnt_space __maybe_unused)
अणु
	अगर (!new_cnt)
		वापस -EINVAL;
	*new_cnt = 0;
	वापस -ENOTSUP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __BPF_PROLOGUE_H */
