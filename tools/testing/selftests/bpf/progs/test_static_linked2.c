<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* 4-byte aligned .bss */
अटल अस्थिर पूर्णांक अटल_var2;
अटल अस्थिर पूर्णांक अटल_var22;
पूर्णांक var2 = 0;
/* 8-byte aligned .rodata */
स्थिर अस्थिर दीर्घ rovar2;

/* same "subprog" name in both files */
अटल __noअंतरभूत पूर्णांक subprog(पूर्णांक x)
अणु
	/* but dअगरferent क्रमmula */
	वापस x * 3;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक handler2(स्थिर व्योम *ctx)
अणु
	var2 = subprog(rovar2) + अटल_var2 + अटल_var22;

	वापस 0;
पूर्ण

/* dअगरferent name and/or type of the variable करोesn't matter */
अक्षर _license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = 1;
