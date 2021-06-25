<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";
पूर्णांक count = 0;

SEC("iter/task")
पूर्णांक dump_task(काष्ठा bpf_iter__task *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	अक्षर c;

	अगर (count < 4) अणु
		c = START_CHAR + count;
		bpf_seq_ग_लिखो(seq, &c, माप(c));
		count++;
	पूर्ण

	वापस 0;
पूर्ण
