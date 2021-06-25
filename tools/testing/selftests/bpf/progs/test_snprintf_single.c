<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Google LLC. */

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* The क्रमmat string is filled from the userspace such that loading fails */
अटल स्थिर अक्षर fmt[10];

SEC("raw_tp/sys_enter")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	अचिन्हित दीर्घ दीर्घ arg = 42;

	bpf_snम_लिखो(शून्य, 0, fmt, &arg, माप(arg));

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
