<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक probe_res;

अक्षर input[4] = अणुपूर्ण;
पूर्णांक test_pid;

SEC("tracepoint/syscalls/sys_enter_nanosleep")
पूर्णांक probe(व्योम *ctx)
अणु
	/* This BPF program perक्रमms variable-offset पढ़ोs and ग_लिखोs on a
	 * stack-allocated buffer.
	 */
	अक्षर stack_buf[16];
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ last;

	अगर ((bpf_get_current_pid_tgid() >> 32) != test_pid)
		वापस 0;

	/* Copy the input to the stack. */
	__builtin_स_नकल(stack_buf, input, 4);

	/* The first byte in the buffer indicates the length. */
	len = stack_buf[0] & 0xf;
	last = (len - 1) & 0xf;

	/* Append something to the buffer. The offset where we ग_लिखो is not
	 * अटलally known; this is a variable-offset stack ग_लिखो.
	 */
	stack_buf[len] = 42;

	/* Index पूर्णांकo the buffer at an unknown offset. This is a
	 * variable-offset stack पढ़ो.
	 *
	 * Note that अगर it wasn't क्रम the preceding variable-offset ग_लिखो, this
	 * पढ़ो would be rejected because the stack slot cannot be verअगरied as
	 * being initialized. With the preceding variable-offset ग_लिखो, the
	 * stack slot still cannot be verअगरied, but the ग_लिखो inhibits the
	 * respective check on the reasoning that, अगर there was a
	 * variable-offset to a higher-or-equal spot, we're probably पढ़ोing
	 * what we just wrote.
	 */
	probe_res = stack_buf[last];
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
