<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <stdbool.h>

#अगर_घोषित ENABLE_ATOMICS_TESTS
bool skip_tests __attribute((__section__(".data"))) = false;
#अन्यथा
bool skip_tests = true;
#पूर्ण_अगर

__u64 add64_value = 1;
__u64 add64_result = 0;
__u32 add32_value = 1;
__u32 add32_result = 0;
__u64 add_stack_value_copy = 0;
__u64 add_stack_result = 0;
__u64 add_noवापस_value = 1;

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(add, पूर्णांक a)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS
	__u64 add_stack_value = 1;

	add64_result = __sync_fetch_and_add(&add64_value, 2);
	add32_result = __sync_fetch_and_add(&add32_value, 2);
	add_stack_result = __sync_fetch_and_add(&add_stack_value, 2);
	add_stack_value_copy = add_stack_value;
	__sync_fetch_and_add(&add_noवापस_value, 2);
#पूर्ण_अगर

	वापस 0;
पूर्ण

__s64 sub64_value = 1;
__s64 sub64_result = 0;
__s32 sub32_value = 1;
__s32 sub32_result = 0;
__s64 sub_stack_value_copy = 0;
__s64 sub_stack_result = 0;
__s64 sub_noवापस_value = 1;

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(sub, पूर्णांक a)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS
	__u64 sub_stack_value = 1;

	sub64_result = __sync_fetch_and_sub(&sub64_value, 2);
	sub32_result = __sync_fetch_and_sub(&sub32_value, 2);
	sub_stack_result = __sync_fetch_and_sub(&sub_stack_value, 2);
	sub_stack_value_copy = sub_stack_value;
	__sync_fetch_and_sub(&sub_noवापस_value, 2);
#पूर्ण_अगर

	वापस 0;
पूर्ण

__u64 and64_value = (0x110ull << 32);
__u64 and64_result = 0;
__u32 and32_value = 0x110;
__u32 and32_result = 0;
__u64 and_noवापस_value = (0x110ull << 32);

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(and, पूर्णांक a)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS

	and64_result = __sync_fetch_and_and(&and64_value, 0x011ull << 32);
	and32_result = __sync_fetch_and_and(&and32_value, 0x011);
	__sync_fetch_and_and(&and_noवापस_value, 0x011ull << 32);
#पूर्ण_अगर

	वापस 0;
पूर्ण

__u64 or64_value = (0x110ull << 32);
__u64 or64_result = 0;
__u32 or32_value = 0x110;
__u32 or32_result = 0;
__u64 or_noवापस_value = (0x110ull << 32);

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(or, पूर्णांक a)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS
	or64_result = __sync_fetch_and_or(&or64_value, 0x011ull << 32);
	or32_result = __sync_fetch_and_or(&or32_value, 0x011);
	__sync_fetch_and_or(&or_noवापस_value, 0x011ull << 32);
#पूर्ण_अगर

	वापस 0;
पूर्ण

__u64 xor64_value = (0x110ull << 32);
__u64 xor64_result = 0;
__u32 xor32_value = 0x110;
__u32 xor32_result = 0;
__u64 xor_noवापस_value = (0x110ull << 32);

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(xor, पूर्णांक a)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS
	xor64_result = __sync_fetch_and_xor(&xor64_value, 0x011ull << 32);
	xor32_result = __sync_fetch_and_xor(&xor32_value, 0x011);
	__sync_fetch_and_xor(&xor_noवापस_value, 0x011ull << 32);
#पूर्ण_अगर

	वापस 0;
पूर्ण

__u64 cmpxchg64_value = 1;
__u64 cmpxchg64_result_fail = 0;
__u64 cmpxchg64_result_succeed = 0;
__u32 cmpxchg32_value = 1;
__u32 cmpxchg32_result_fail = 0;
__u32 cmpxchg32_result_succeed = 0;

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(cmpxchg, पूर्णांक a)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS
	cmpxchg64_result_fail = __sync_val_compare_and_swap(&cmpxchg64_value, 0, 3);
	cmpxchg64_result_succeed = __sync_val_compare_and_swap(&cmpxchg64_value, 1, 2);

	cmpxchg32_result_fail = __sync_val_compare_and_swap(&cmpxchg32_value, 0, 3);
	cmpxchg32_result_succeed = __sync_val_compare_and_swap(&cmpxchg32_value, 1, 2);
#पूर्ण_अगर

	वापस 0;
पूर्ण

__u64 xchg64_value = 1;
__u64 xchg64_result = 0;
__u32 xchg32_value = 1;
__u32 xchg32_result = 0;

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(xchg, पूर्णांक a)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS
	__u64 val64 = 2;
	__u32 val32 = 2;

	xchg64_result = __sync_lock_test_and_set(&xchg64_value, val64);
	xchg32_result = __sync_lock_test_and_set(&xchg32_value, val32);
#पूर्ण_अगर

	वापस 0;
पूर्ण
