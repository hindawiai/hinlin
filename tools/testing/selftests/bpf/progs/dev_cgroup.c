<शैली गुरु>
/* Copyright (c) 2017 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */

#समावेश <linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>

SEC("cgroup/dev")
पूर्णांक bpf_prog1(काष्ठा bpf_cgroup_dev_ctx *ctx)
अणु
	लघु type = ctx->access_type & 0xFFFF;
#अगर_घोषित DEBUG
	लघु access = ctx->access_type >> 16;
	अक्षर fmt[] = "  %d:%d    \n";

	चयन (type) अणु
	हाल BPF_DEVCG_DEV_BLOCK:
		fmt[0] = 'b';
		अवरोध;
	हाल BPF_DEVCG_DEV_CHAR:
		fmt[0] = 'c';
		अवरोध;
	शेष:
		fmt[0] = '?';
		अवरोध;
	पूर्ण

	अगर (access & BPF_DEVCG_ACC_READ)
		fmt[8] = 'r';

	अगर (access & BPF_DEVCG_ACC_WRITE)
		fmt[9] = 'w';

	अगर (access & BPF_DEVCG_ACC_MKNOD)
		fmt[10] = 'm';

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), ctx->major, ctx->minor);
#पूर्ण_अगर

	/* Allow access to /dev/zero and /dev/अक्रमom.
	 * Forbid everything अन्यथा.
	 */
	अगर (ctx->major != 1 || type != BPF_DEVCG_DEV_CHAR)
		वापस 0;

	चयन (ctx->minor) अणु
	हाल 5: /* 1:5 /dev/zero */
	हाल 9: /* 1:9 /dev/uअक्रमom */
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = LINUX_VERSION_CODE;
