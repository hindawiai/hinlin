<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

अटल पूर्णांक sequence = 0;
__s32 input_retval = 0;

__u64 fentry_result = 0;
SEC("fentry/bpf_modify_return_test")
पूर्णांक BPF_PROG(fentry_test, पूर्णांक a, __u64 b)
अणु
	sequence++;
	fentry_result = (sequence == 1);
	वापस 0;
पूर्ण

__u64 भ_शेष_ret_result = 0;
SEC("fmod_ret/bpf_modify_return_test")
पूर्णांक BPF_PROG(भ_शेष_ret_test, पूर्णांक a, पूर्णांक *b, पूर्णांक ret)
अणु
	sequence++;
	/* This is the first भ_शेष_ret program, the ret passed should be 0 */
	भ_शेष_ret_result = (sequence == 2 && ret == 0);
	वापस input_retval;
पूर्ण

__u64 fनिकास_result = 0;
SEC("fexit/bpf_modify_return_test")
पूर्णांक BPF_PROG(fनिकास_test, पूर्णांक a, __u64 b, पूर्णांक ret)
अणु
	sequence++;
	/* If the input_reval is non-zero a successful modअगरication should have
	 * occurred.
	 */
	अगर (input_retval)
		fनिकास_result = (sequence == 3 && ret == input_retval);
	अन्यथा
		fनिकास_result = (sequence == 3 && ret == 4);

	वापस 0;
पूर्ण
