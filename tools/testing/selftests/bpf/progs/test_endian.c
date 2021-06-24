<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा IN16 0x1234
#घोषणा IN32 0x12345678U
#घोषणा IN64 0x123456789abcdef0ULL

__u16 in16 = 0;
__u32 in32 = 0;
__u64 in64 = 0;

__u16 out16 = 0;
__u32 out32 = 0;
__u64 out64 = 0;

__u16 स्थिर16 = 0;
__u32 स्थिर32 = 0;
__u64 स्थिर64 = 0;

SEC("raw_tp/sys_enter")
पूर्णांक sys_enter(स्थिर व्योम *ctx)
अणु
	out16 = __builtin_bswap16(in16);
	out32 = __builtin_bswap32(in32);
	out64 = __builtin_bswap64(in64);
	स्थिर16 = ___bpf_swab16(IN16);
	स्थिर32 = ___bpf_swab32(IN32);
	स्थिर64 = ___bpf_swab64(IN64);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
