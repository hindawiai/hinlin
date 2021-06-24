<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* 8-byte aligned .bss */
अटल अस्थिर दीर्घ अटल_var1;
अटल अस्थिर पूर्णांक अटल_var11;
पूर्णांक var1 = 0;
/* 4-byte aligned .rodata */
स्थिर अस्थिर पूर्णांक rovar1;

/* same "subprog" name in both files */
अटल __noअंतरभूत पूर्णांक subprog(पूर्णांक x)
अणु
	/* but dअगरferent क्रमmula */
	वापस x * 2;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक handler1(स्थिर व्योम *ctx)
अणु
	var1 = subprog(rovar1) + अटल_var1 + अटल_var11;

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
पूर्णांक VERSION SEC("version") = 1;
