<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "cgroup_helpers.h"

अटल अक्षर bpf_log_buf[4096];
अटल bool verbose;

क्रमागत sockopt_test_error अणु
	OK = 0,
	DENY_LOAD,
	DENY_ATTACH,
	EPERM_GETSOCKOPT,
	EFAULT_GETSOCKOPT,
	EPERM_SETSOCKOPT,
	EFAULT_SETSOCKOPT,
पूर्ण;

अटल काष्ठा sockopt_test अणु
	स्थिर अक्षर			*descr;
	स्थिर काष्ठा bpf_insn		insns[64];
	क्रमागत bpf_attach_type		attach_type;
	क्रमागत bpf_attach_type		expected_attach_type;

	पूर्णांक				set_optname;
	पूर्णांक				set_level;
	स्थिर अक्षर			set_optval[64];
	socklen_t			set_optlen;

	पूर्णांक				get_optname;
	पूर्णांक				get_level;
	स्थिर अक्षर			get_optval[64];
	socklen_t			get_optlen;
	socklen_t			get_optlen_ret;

	क्रमागत sockopt_test_error		error;
पूर्ण tests[] = अणु

	/* ==================== माला_लोockopt ====================  */

	अणु
		.descr = "getsockopt: no expected_attach_type",
		.insns = अणु
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),

		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = 0,
		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "getsockopt: wrong expected_attach_type",
		.insns = अणु
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),

		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,
		.error = DENY_ATTACH,
	पूर्ण,
	अणु
		.descr = "getsockopt: bypass bpf hook",
		.insns = अणु
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_level = SOL_IP,
		.set_level = SOL_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optval = अणु 1 << 3 पूर्ण,
		.set_optlen = 1,

		.get_optval = अणु 1 << 3 पूर्ण,
		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "getsockopt: return EPERM from bpf hook",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_level = SOL_IP,
		.get_optname = IP_TOS,

		.get_optlen = 1,
		.error = EPERM_GETSOCKOPT,
	पूर्ण,
	अणु
		.descr = "getsockopt: no optval bounds check, deny loading",
		.insns = अणु
			/* r6 = ctx->optval */
			BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),

			/* ctx->optval[0] = 0x80 */
			BPF_MOV64_IMM(BPF_REG_0, 0x80),
			BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_0, 0),

			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,
		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "getsockopt: read ctx->level",
		.insns = अणु
			/* r6 = ctx->level */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, level)),

			/* अगर (ctx->level == 123) अणु */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_6, 123, 4),
			/* ctx->retval = 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण अन्यथा अणु */
			/* वापस 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_level = 123,

		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "getsockopt: deny writing to ctx->level",
		.insns = अणु
			/* ctx->level = 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, level)),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "getsockopt: read ctx->optname",
		.insns = अणु
			/* r6 = ctx->optname */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optname)),

			/* अगर (ctx->optname == 123) अणु */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_6, 123, 4),
			/* ctx->retval = 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण अन्यथा अणु */
			/* वापस 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_optname = 123,

		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "getsockopt: read ctx->retval",
		.insns = अणु
			/* r6 = ctx->retval */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),

			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_level = SOL_IP,
		.get_optname = IP_TOS,
		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "getsockopt: deny writing to ctx->optname",
		.insns = अणु
			/* ctx->optname = 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optname)),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "getsockopt: read ctx->optlen",
		.insns = अणु
			/* r6 = ctx->optlen */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),

			/* अगर (ctx->optlen == 64) अणु */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_6, 64, 4),
			/* ctx->retval = 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण अन्यथा अणु */
			/* वापस 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_optlen = 64,
	पूर्ण,
	अणु
		.descr = "getsockopt: deny bigger ctx->optlen",
		.insns = अणु
			/* ctx->optlen = 65 */
			BPF_MOV64_IMM(BPF_REG_0, 65),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),

			/* ctx->retval = 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),

			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_optlen = 64,

		.error = EFAULT_GETSOCKOPT,
	पूर्ण,
	अणु
		.descr = "getsockopt: deny arbitrary ctx->retval",
		.insns = अणु
			/* ctx->retval = 123 */
			BPF_MOV64_IMM(BPF_REG_0, 123),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),

			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_optlen = 64,

		.error = EFAULT_GETSOCKOPT,
	पूर्ण,
	अणु
		.descr = "getsockopt: support smaller ctx->optlen",
		.insns = अणु
			/* ctx->optlen = 32 */
			BPF_MOV64_IMM(BPF_REG_0, 32),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),
			/* ctx->retval = 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_optlen = 64,
		.get_optlen_ret = 32,
	पूर्ण,
	अणु
		.descr = "getsockopt: deny writing to ctx->optval",
		.insns = अणु
			/* ctx->optval = 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "getsockopt: deny writing to ctx->optval_end",
		.insns = अणु
			/* ctx->optval_end = 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optval_end)),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "getsockopt: rewrite value",
		.insns = अणु
			/* r6 = ctx->optval */
			BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),
			/* r2 = ctx->optval */
			BPF_MOV64_REG(BPF_REG_2, BPF_REG_6),
			/* r6 = ctx->optval + 1 */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_6, 1),

			/* r7 = ctx->optval_end */
			BPF_LDX_MEM(BPF_DW, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval_end)),

			/* अगर (ctx->optval + 1 <= ctx->optval_end) अणु */
			BPF_JMP_REG(BPF_JGT, BPF_REG_6, BPF_REG_7, 1),
			/* ctx->optval[0] = 0xF0 */
			BPF_ST_MEM(BPF_B, BPF_REG_2, 0, 0xF0),
			/* पूर्ण */

			/* ctx->retval = 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),

			/* वापस 1*/
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,

		.get_level = SOL_IP,
		.get_optname = IP_TOS,

		.get_optval = अणु 0xF0 पूर्ण,
		.get_optlen = 1,
	पूर्ण,

	/* ==================== setsockopt ====================  */

	अणु
		.descr = "setsockopt: no expected_attach_type",
		.insns = अणु
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),

		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = 0,
		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "setsockopt: wrong expected_attach_type",
		.insns = अणु
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),

		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_GETSOCKOPT,
		.error = DENY_ATTACH,
	पूर्ण,
	अणु
		.descr = "setsockopt: bypass bpf hook",
		.insns = अणु
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.get_level = SOL_IP,
		.set_level = SOL_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optval = अणु 1 << 3 पूर्ण,
		.set_optlen = 1,

		.get_optval = अणु 1 << 3 पूर्ण,
		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "setsockopt: return EPERM from bpf hook",
		.insns = अणु
			/* वापस 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.set_level = SOL_IP,
		.set_optname = IP_TOS,

		.set_optlen = 1,
		.error = EPERM_SETSOCKOPT,
	पूर्ण,
	अणु
		.descr = "setsockopt: no optval bounds check, deny loading",
		.insns = अणु
			/* r6 = ctx->optval */
			BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),

			/* r0 = ctx->optval[0] */
			BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_6, 0),

			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,
		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "setsockopt: read ctx->level",
		.insns = अणु
			/* r6 = ctx->level */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, level)),

			/* अगर (ctx->level == 123) अणु */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_6, 123, 4),
			/* ctx->optlen = -1 */
			BPF_MOV64_IMM(BPF_REG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण अन्यथा अणु */
			/* वापस 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.set_level = 123,

		.set_optlen = 1,
	पूर्ण,
	अणु
		.descr = "setsockopt: allow changing ctx->level",
		.insns = अणु
			/* ctx->level = SOL_IP */
			BPF_MOV64_IMM(BPF_REG_0, SOL_IP),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, level)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.get_level = SOL_IP,
		.set_level = 234, /* should be rewritten to SOL_IP */

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optval = अणु 1 << 3 पूर्ण,
		.set_optlen = 1,
		.get_optval = अणु 1 << 3 पूर्ण,
		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "setsockopt: read ctx->optname",
		.insns = अणु
			/* r6 = ctx->optname */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optname)),

			/* अगर (ctx->optname == 123) अणु */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_6, 123, 4),
			/* ctx->optlen = -1 */
			BPF_MOV64_IMM(BPF_REG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण अन्यथा अणु */
			/* वापस 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.set_optname = 123,

		.set_optlen = 1,
	पूर्ण,
	अणु
		.descr = "setsockopt: allow changing ctx->optname",
		.insns = अणु
			/* ctx->optname = IP_TOS */
			BPF_MOV64_IMM(BPF_REG_0, IP_TOS),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optname)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.get_level = SOL_IP,
		.set_level = SOL_IP,

		.get_optname = IP_TOS,
		.set_optname = 456, /* should be rewritten to IP_TOS */

		.set_optval = अणु 1 << 3 पूर्ण,
		.set_optlen = 1,
		.get_optval = अणु 1 << 3 पूर्ण,
		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "setsockopt: read ctx->optlen",
		.insns = अणु
			/* r6 = ctx->optlen */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),

			/* अगर (ctx->optlen == 64) अणु */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_6, 64, 4),
			/* ctx->optlen = -1 */
			BPF_MOV64_IMM(BPF_REG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण अन्यथा अणु */
			/* वापस 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.set_optlen = 64,
	पूर्ण,
	अणु
		.descr = "setsockopt: ctx->optlen == -1 is ok",
		.insns = अणु
			/* ctx->optlen = -1 */
			BPF_MOV64_IMM(BPF_REG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.set_optlen = 64,
	पूर्ण,
	अणु
		.descr = "setsockopt: deny ctx->optlen < 0 (except -1)",
		.insns = अणु
			/* ctx->optlen = -2 */
			BPF_MOV64_IMM(BPF_REG_0, -2),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),
			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.set_optlen = 4,

		.error = EFAULT_SETSOCKOPT,
	पूर्ण,
	अणु
		.descr = "setsockopt: deny ctx->optlen > input optlen",
		.insns = अणु
			/* ctx->optlen = 65 */
			BPF_MOV64_IMM(BPF_REG_0, 65),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.set_optlen = 64,

		.error = EFAULT_SETSOCKOPT,
	पूर्ण,
	अणु
		.descr = "setsockopt: allow changing ctx->optlen within bounds",
		.insns = अणु
			/* r6 = ctx->optval */
			BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),
			/* r2 = ctx->optval */
			BPF_MOV64_REG(BPF_REG_2, BPF_REG_6),
			/* r6 = ctx->optval + 1 */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_6, 1),

			/* r7 = ctx->optval_end */
			BPF_LDX_MEM(BPF_DW, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval_end)),

			/* अगर (ctx->optval + 1 <= ctx->optval_end) अणु */
			BPF_JMP_REG(BPF_JGT, BPF_REG_6, BPF_REG_7, 1),
			/* ctx->optval[0] = 1 << 3 */
			BPF_ST_MEM(BPF_B, BPF_REG_2, 0, 1 << 3),
			/* पूर्ण */

			/* ctx->optlen = 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optlen)),

			/* वापस 1*/
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.get_level = SOL_IP,
		.set_level = SOL_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optval = अणु 1, 1, 1, 1 पूर्ण,
		.set_optlen = 4,
		.get_optval = अणु 1 << 3 पूर्ण,
		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "setsockopt: deny write ctx->retval",
		.insns = अणु
			/* ctx->retval = 0 */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),

			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "setsockopt: deny read ctx->retval",
		.insns = अणु
			/* r6 = ctx->retval */
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, retval)),

			/* वापस 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "setsockopt: deny writing to ctx->optval",
		.insns = अणु
			/* ctx->optval = 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "setsockopt: deny writing to ctx->optval_end",
		.insns = अणु
			/* ctx->optval_end = 1 */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sockopt, optval_end)),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.error = DENY_LOAD,
	पूर्ण,
	अणु
		.descr = "setsockopt: allow IP_TOS <= 128",
		.insns = अणु
			/* r6 = ctx->optval */
			BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),
			/* r7 = ctx->optval + 1 */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_6),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, 1),

			/* r8 = ctx->optval_end */
			BPF_LDX_MEM(BPF_DW, BPF_REG_8, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval_end)),

			/* अगर (ctx->optval + 1 <= ctx->optval_end) अणु */
			BPF_JMP_REG(BPF_JGT, BPF_REG_7, BPF_REG_8, 4),

			/* r9 = ctx->optval[0] */
			BPF_LDX_MEM(BPF_B, BPF_REG_9, BPF_REG_6, 0),

			/* अगर (ctx->optval[0] < 128) */
			BPF_JMP_IMM(BPF_JGT, BPF_REG_9, 128, 2),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण */

			/* पूर्ण अन्यथा अणु */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */

			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.get_level = SOL_IP,
		.set_level = SOL_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optval = अणु 0x80 पूर्ण,
		.set_optlen = 1,
		.get_optval = अणु 0x80 पूर्ण,
		.get_optlen = 1,
	पूर्ण,
	अणु
		.descr = "setsockopt: deny IP_TOS > 128",
		.insns = अणु
			/* r6 = ctx->optval */
			BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval)),
			/* r7 = ctx->optval + 1 */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_6),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, 1),

			/* r8 = ctx->optval_end */
			BPF_LDX_MEM(BPF_DW, BPF_REG_8, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sockopt, optval_end)),

			/* अगर (ctx->optval + 1 <= ctx->optval_end) अणु */
			BPF_JMP_REG(BPF_JGT, BPF_REG_7, BPF_REG_8, 4),

			/* r9 = ctx->optval[0] */
			BPF_LDX_MEM(BPF_B, BPF_REG_9, BPF_REG_6, 0),

			/* अगर (ctx->optval[0] < 128) */
			BPF_JMP_IMM(BPF_JGT, BPF_REG_9, 128, 2),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),
			/* पूर्ण */

			/* पूर्ण अन्यथा अणु */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* पूर्ण */

			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGROUP_SETSOCKOPT,

		.get_level = SOL_IP,
		.set_level = SOL_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optval = अणु 0x81 पूर्ण,
		.set_optlen = 1,
		.get_optval = अणु 0x00 पूर्ण,
		.get_optlen = 1,

		.error = EPERM_SETSOCKOPT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक load_prog(स्थिर काष्ठा bpf_insn *insns,
		     क्रमागत bpf_attach_type expected_attach_type)
अणु
	काष्ठा bpf_load_program_attr attr = अणु
		.prog_type = BPF_PROG_TYPE_CGROUP_SOCKOPT,
		.expected_attach_type = expected_attach_type,
		.insns = insns,
		.license = "GPL",
		.log_level = 2,
	पूर्ण;
	पूर्णांक fd;

	क्रम (;
	     insns[attr.insns_cnt].code != (BPF_JMP | BPF_EXIT);
	     attr.insns_cnt++) अणु
	पूर्ण
	attr.insns_cnt++;

	fd = bpf_load_program_xattr(&attr, bpf_log_buf, माप(bpf_log_buf));
	अगर (verbose && fd < 0)
		ख_लिखो(मानक_त्रुटि, "%s\n", bpf_log_buf);

	वापस fd;
पूर्ण

अटल पूर्णांक run_test(पूर्णांक cgroup_fd, काष्ठा sockopt_test *test)
अणु
	पूर्णांक sock_fd, err, prog_fd;
	व्योम *optval = शून्य;
	पूर्णांक ret = 0;

	prog_fd = load_prog(test->insns, test->expected_attach_type);
	अगर (prog_fd < 0) अणु
		अगर (test->error == DENY_LOAD)
			वापस 0;

		log_err("Failed to load BPF program");
		वापस -1;
	पूर्ण

	err = bpf_prog_attach(prog_fd, cgroup_fd, test->attach_type, 0);
	अगर (err < 0) अणु
		अगर (test->error == DENY_ATTACH)
			जाओ बंद_prog_fd;

		log_err("Failed to attach BPF program");
		ret = -1;
		जाओ बंद_prog_fd;
	पूर्ण

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	अगर (sock_fd < 0) अणु
		log_err("Failed to create AF_INET socket");
		ret = -1;
		जाओ detach_prog;
	पूर्ण

	अगर (test->set_optlen) अणु
		err = setsockopt(sock_fd, test->set_level, test->set_optname,
				 test->set_optval, test->set_optlen);
		अगर (err) अणु
			अगर (त्रुटि_सं == EPERM && test->error == EPERM_SETSOCKOPT)
				जाओ बंद_sock_fd;
			अगर (त्रुटि_सं == EFAULT && test->error == EFAULT_SETSOCKOPT)
				जाओ मुक्त_optval;

			log_err("Failed to call setsockopt");
			ret = -1;
			जाओ बंद_sock_fd;
		पूर्ण
	पूर्ण

	अगर (test->get_optlen) अणु
		optval = दो_स्मृति(test->get_optlen);
		socklen_t optlen = test->get_optlen;
		socklen_t expected_get_optlen = test->get_optlen_ret ?:
			test->get_optlen;

		err = माला_लोockopt(sock_fd, test->get_level, test->get_optname,
				 optval, &optlen);
		अगर (err) अणु
			अगर (त्रुटि_सं == EPERM && test->error == EPERM_GETSOCKOPT)
				जाओ मुक्त_optval;
			अगर (त्रुटि_सं == EFAULT && test->error == EFAULT_GETSOCKOPT)
				जाओ मुक्त_optval;

			log_err("Failed to call getsockopt");
			ret = -1;
			जाओ मुक्त_optval;
		पूर्ण

		अगर (optlen != expected_get_optlen) अणु
			त्रुटि_सं = 0;
			log_err("getsockopt returned unexpected optlen");
			ret = -1;
			जाओ मुक्त_optval;
		पूर्ण

		अगर (स_भेद(optval, test->get_optval, optlen) != 0) अणु
			त्रुटि_सं = 0;
			log_err("getsockopt returned unexpected optval");
			ret = -1;
			जाओ मुक्त_optval;
		पूर्ण
	पूर्ण

	ret = test->error != OK;

मुक्त_optval:
	मुक्त(optval);
बंद_sock_fd:
	बंद(sock_fd);
detach_prog:
	bpf_prog_detach2(prog_fd, cgroup_fd, test->attach_type);
बंद_prog_fd:
	बंद(prog_fd);
	वापस ret;
पूर्ण

व्योम test_sockopt(व्योम)
अणु
	पूर्णांक cgroup_fd, i;

	cgroup_fd = test__join_cgroup("/sockopt");
	अगर (CHECK_FAIL(cgroup_fd < 0))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		test__start_subtest(tests[i].descr);
		CHECK_FAIL(run_test(cgroup_fd, &tests[i]));
	पूर्ण

	बंद(cgroup_fd);
पूर्ण
