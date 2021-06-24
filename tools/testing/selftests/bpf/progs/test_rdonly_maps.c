<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <linux/ptrace.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अटल अस्थिर स्थिर काष्ठा अणु
	अचिन्हित a[4];
	/*
	 * अगर the काष्ठा's size is multiple of 16, compiler will put it पूर्णांकo
	 * .rodata.cst16 section, which is not recognized by libbpf; work
	 * around this by ensuring we करोn't have 16-aligned काष्ठा
	 */
	अक्षर _y;
पूर्ण rकरोnly_values = अणु .a = अणु2, 3, 4, 5पूर्ण पूर्ण;

अटल अस्थिर काष्ठा अणु
	अचिन्हित did_run;
	अचिन्हित iters;
	अचिन्हित sum;
पूर्ण res;

SEC("raw_tracepoint/sys_enter:skip_loop")
पूर्णांक skip_loop(काष्ठा pt_regs *ctx)
अणु
	/* prevent compiler to optimize everything out */
	अचिन्हित * अस्थिर p = (व्योम *)&rकरोnly_values.a;
	अचिन्हित iters = 0, sum = 0;

	/* we should never enter this loop */
	जबतक (*p & 1) अणु
		iters++;
		sum += *p;
		p++;
	पूर्ण
	res.did_run = 1;
	res.iters = iters;
	res.sum = sum;
	वापस 0;
पूर्ण

SEC("raw_tracepoint/sys_enter:part_loop")
पूर्णांक part_loop(काष्ठा pt_regs *ctx)
अणु
	/* prevent compiler to optimize everything out */
	अचिन्हित * अस्थिर p = (व्योम *)&rकरोnly_values.a;
	अचिन्हित iters = 0, sum = 0;

	/* validate verअगरier can derive loop termination */
	जबतक (*p < 5) अणु
		iters++;
		sum += *p;
		p++;
	पूर्ण
	res.did_run = 1;
	res.iters = iters;
	res.sum = sum;
	वापस 0;
पूर्ण

SEC("raw_tracepoint/sys_enter:full_loop")
पूर्णांक full_loop(काष्ठा pt_regs *ctx)
अणु
	/* prevent compiler to optimize everything out */
	अचिन्हित * अस्थिर p = (व्योम *)&rकरोnly_values.a;
	पूर्णांक i = माप(rकरोnly_values.a) / माप(rकरोnly_values.a[0]);
	अचिन्हित iters = 0, sum = 0;

	/* validate verअगरier can allow full loop as well */
	जबतक (i > 0 ) अणु
		iters++;
		sum += *p;
		p++;
		i--;
	पूर्ण
	res.did_run = 1;
	res.iters = iters;
	res.sum = sum;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
