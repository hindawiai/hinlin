<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Google LLC. */

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

__u32 pid = 0;

अक्षर num_out[64] = अणुपूर्ण;
दीर्घ num_ret = 0;

अक्षर ip_out[64] = अणुपूर्ण;
दीर्घ ip_ret = 0;

अक्षर sym_out[64] = अणुपूर्ण;
दीर्घ sym_ret = 0;

अक्षर addr_out[64] = अणुपूर्ण;
दीर्घ addr_ret = 0;

अक्षर str_out[64] = अणुपूर्ण;
दीर्घ str_ret = 0;

अक्षर over_out[6] = अणुपूर्ण;
दीर्घ over_ret = 0;

अक्षर pad_out[10] = अणुपूर्ण;
दीर्घ pad_ret = 0;

अक्षर noarg_out[64] = अणुपूर्ण;
दीर्घ noarg_ret = 0;

दीर्घ nobuf_ret = 0;

बाह्य स्थिर व्योम schedule __ksym;

SEC("raw_tp/sys_enter")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	/* Convenient values to pretty-prपूर्णांक */
	स्थिर __u8 ex_ipv4[] = अणु127, 0, 0, 1पूर्ण;
	स्थिर __u8 ex_ipv6[] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1पूर्ण;
	अटल स्थिर अक्षर str1[] = "str1";
	अटल स्थिर अक्षर दीर्घstr[] = "longstr";

	अगर ((पूर्णांक)bpf_get_current_pid_tgid() != pid)
		वापस 0;

	/* Integer types */
	num_ret  = BPF_SNPRINTF(num_out, माप(num_out),
				"%d %u %x %li %llu %lX",
				-8, 9, 150, -424242, 1337, 0xDABBAD00);
	/* IP addresses */
	ip_ret   = BPF_SNPRINTF(ip_out, माप(ip_out), "%pi4 %pI6",
				&ex_ipv4, &ex_ipv6);
	/* Symbol lookup क्रमmatting */
	sym_ret  = BPF_SNPRINTF(sym_out,  माप(sym_out), "%ps %pS %pB",
				&schedule, &schedule, &schedule);
	/* Kernel poपूर्णांकers */
	addr_ret = BPF_SNPRINTF(addr_out, माप(addr_out), "%pK %px %p",
				0, 0xFFFF00000ADD4E55, 0xFFFF00000ADD4E55);
	/* Strings embedding */
	str_ret  = BPF_SNPRINTF(str_out, माप(str_out), "%s %+05s",
				str1, दीर्घstr);
	/* Overflow */
	over_ret = BPF_SNPRINTF(over_out, माप(over_out), "%%overflow");
	/* Padding of fixed width numbers */
	pad_ret = BPF_SNPRINTF(pad_out, माप(pad_out), "%5d %0900000X", 4, 4);
	/* No args */
	noarg_ret = BPF_SNPRINTF(noarg_out, माप(noarg_out), "simple case");
	/* No buffer */
	nobuf_ret = BPF_SNPRINTF(शून्य, 0, "only interested in length %d", 60);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
