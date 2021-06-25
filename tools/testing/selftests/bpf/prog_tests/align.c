<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

#घोषणा MAX_INSNS	512
#घोषणा MAX_MATCHES	16

काष्ठा bpf_reg_match अणु
	अचिन्हित पूर्णांक line;
	स्थिर अक्षर *match;
पूर्ण;

काष्ठा bpf_align_test अणु
	स्थिर अक्षर *descr;
	काष्ठा bpf_insn	insns[MAX_INSNS];
	क्रमागत अणु
		UNDEF,
		ACCEPT,
		REJECT
	पूर्ण result;
	क्रमागत bpf_prog_type prog_type;
	/* Matches must be in order of increasing line */
	काष्ठा bpf_reg_match matches[MAX_MATCHES];
पूर्ण;

अटल काष्ठा bpf_align_test tests[] = अणु
	/* Four tests of known स्थिरants.  These aren't staggeringly
	 * पूर्णांकeresting since we track exact values now.
	 */
	अणु
		.descr = "mov",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_3, 2),
			BPF_MOV64_IMM(BPF_REG_3, 4),
			BPF_MOV64_IMM(BPF_REG_3, 8),
			BPF_MOV64_IMM(BPF_REG_3, 16),
			BPF_MOV64_IMM(BPF_REG_3, 32),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			अणु1, "R1=ctx(id=0,off=0,imm=0)"पूर्ण,
			अणु1, "R10=fp0"पूर्ण,
			अणु1, "R3_w=inv2"पूर्ण,
			अणु2, "R3_w=inv4"पूर्ण,
			अणु3, "R3_w=inv8"पूर्ण,
			अणु4, "R3_w=inv16"पूर्ण,
			अणु5, "R3_w=inv32"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "shift",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_3, 4),
			BPF_MOV64_IMM(BPF_REG_4, 32),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			अणु1, "R1=ctx(id=0,off=0,imm=0)"पूर्ण,
			अणु1, "R10=fp0"पूर्ण,
			अणु1, "R3_w=inv1"पूर्ण,
			अणु2, "R3_w=inv2"पूर्ण,
			अणु3, "R3_w=inv4"पूर्ण,
			अणु4, "R3_w=inv8"पूर्ण,
			अणु5, "R3_w=inv16"पूर्ण,
			अणु6, "R3_w=inv1"पूर्ण,
			अणु7, "R4_w=inv32"पूर्ण,
			अणु8, "R4_w=inv16"पूर्ण,
			अणु9, "R4_w=inv8"पूर्ण,
			अणु10, "R4_w=inv4"पूर्ण,
			अणु11, "R4_w=inv2"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "addsub",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_3, 4),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, 4),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, 2),
			BPF_MOV64_IMM(BPF_REG_4, 8),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 2),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			अणु1, "R1=ctx(id=0,off=0,imm=0)"पूर्ण,
			अणु1, "R10=fp0"पूर्ण,
			अणु1, "R3_w=inv4"पूर्ण,
			अणु2, "R3_w=inv8"पूर्ण,
			अणु3, "R3_w=inv10"पूर्ण,
			अणु4, "R4_w=inv8"पूर्ण,
			अणु5, "R4_w=inv12"पूर्ण,
			अणु6, "R4_w=inv14"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "mul",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_3, 7),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_3, 2),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_3, 4),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			अणु1, "R1=ctx(id=0,off=0,imm=0)"पूर्ण,
			अणु1, "R10=fp0"पूर्ण,
			अणु1, "R3_w=inv7"पूर्ण,
			अणु2, "R3_w=inv7"पूर्ण,
			अणु3, "R3_w=inv14"पूर्ण,
			अणु4, "R3_w=inv56"पूर्ण,
		पूर्ण,
	पूर्ण,

	/* Tests using unknown values */
#घोषणा PREP_PKT_POINTERS \
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, \
		    दुरत्व(काष्ठा __sk_buff, data)), \
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1, \
		    दुरत्व(काष्ठा __sk_buff, data_end))

#घोषणा LOAD_UNKNOWN(DST_REG) \
	PREP_PKT_POINTERS, \
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2), \
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8), \
	BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_0, 1), \
	BPF_EXIT_INSN(), \
	BPF_LDX_MEM(BPF_B, DST_REG, BPF_REG_2, 0)

	अणु
		.descr = "unknown shift",
		.insns = अणु
			LOAD_UNKNOWN(BPF_REG_3),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_3, 1),
			LOAD_UNKNOWN(BPF_REG_4),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_4, 5),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 1),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			अणु7, "R0_w=pkt(id=0,off=8,r=8,imm=0)"पूर्ण,
			अणु7, "R3_w=inv(id=0,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु8, "R3_w=inv(id=0,umax_value=510,var_off=(0x0; 0x1fe))"पूर्ण,
			अणु9, "R3_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			अणु10, "R3_w=inv(id=0,umax_value=2040,var_off=(0x0; 0x7f8))"पूर्ण,
			अणु11, "R3_w=inv(id=0,umax_value=4080,var_off=(0x0; 0xff0))"पूर्ण,
			अणु18, "R3=pkt_end(id=0,off=0,imm=0)"पूर्ण,
			अणु18, "R4_w=inv(id=0,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु19, "R4_w=inv(id=0,umax_value=8160,var_off=(0x0; 0x1fe0))"पूर्ण,
			अणु20, "R4_w=inv(id=0,umax_value=4080,var_off=(0x0; 0xff0))"पूर्ण,
			अणु21, "R4_w=inv(id=0,umax_value=2040,var_off=(0x0; 0x7f8))"पूर्ण,
			अणु22, "R4_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			अणु23, "R4_w=inv(id=0,umax_value=510,var_off=(0x0; 0x1fe))"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "unknown mul",
		.insns = अणु
			LOAD_UNKNOWN(BPF_REG_3),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_3),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_4, 1),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_3),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_4, 2),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_3),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_4, 4),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_3),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_4, 8),
			BPF_ALU64_IMM(BPF_MUL, BPF_REG_4, 2),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			अणु7, "R3_w=inv(id=0,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु8, "R4_w=inv(id=1,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु9, "R4_w=inv(id=0,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु10, "R4_w=inv(id=1,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु11, "R4_w=inv(id=0,umax_value=510,var_off=(0x0; 0x1fe))"पूर्ण,
			अणु12, "R4_w=inv(id=1,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु13, "R4_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			अणु14, "R4_w=inv(id=1,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु15, "R4_w=inv(id=0,umax_value=2040,var_off=(0x0; 0x7f8))"पूर्ण,
			अणु16, "R4_w=inv(id=0,umax_value=4080,var_off=(0x0; 0xff0))"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "packet const offset",
		.insns = अणु
			PREP_PKT_POINTERS,
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_2),

			BPF_MOV64_IMM(BPF_REG_0, 0),

			/* Skip over ethernet header.  */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 14),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),

			BPF_LDX_MEM(BPF_B, BPF_REG_4, BPF_REG_5, 0),
			BPF_LDX_MEM(BPF_B, BPF_REG_4, BPF_REG_5, 1),
			BPF_LDX_MEM(BPF_B, BPF_REG_4, BPF_REG_5, 2),
			BPF_LDX_MEM(BPF_B, BPF_REG_4, BPF_REG_5, 3),
			BPF_LDX_MEM(BPF_H, BPF_REG_4, BPF_REG_5, 0),
			BPF_LDX_MEM(BPF_H, BPF_REG_4, BPF_REG_5, 2),
			BPF_LDX_MEM(BPF_W, BPF_REG_4, BPF_REG_5, 0),

			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			अणु4, "R5_w=pkt(id=0,off=0,r=0,imm=0)"पूर्ण,
			अणु5, "R5_w=pkt(id=0,off=14,r=0,imm=0)"पूर्ण,
			अणु6, "R4_w=pkt(id=0,off=14,r=0,imm=0)"पूर्ण,
			अणु10, "R2=pkt(id=0,off=0,r=18,imm=0)"पूर्ण,
			अणु10, "R5=pkt(id=0,off=14,r=18,imm=0)"पूर्ण,
			अणु10, "R4_w=inv(id=0,umax_value=255,var_off=(0x0; 0xff))"पूर्ण,
			अणु14, "R4_w=inv(id=0,umax_value=65535,var_off=(0x0; 0xffff))"पूर्ण,
			अणु15, "R4_w=inv(id=0,umax_value=65535,var_off=(0x0; 0xffff))"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "packet variable offset",
		.insns = अणु
			LOAD_UNKNOWN(BPF_REG_6),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_6, 2),

			/* First, add a स्थिरant to the R5 packet poपूर्णांकer,
			 * then a variable with a known alignment.
			 */
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_2),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 14),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_6),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_4, BPF_REG_5, 0),

			/* Now, test in the other direction.  Adding first
			 * the variable offset to R5, then the स्थिरant.
			 */
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_2),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_6),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 14),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_4, BPF_REG_5, 0),

			/* Test multiple accumulations of unknown values
			 * पूर्णांकo a packet poपूर्णांकer.
			 */
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_2),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 14),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_6),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 4),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_6),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_4, BPF_REG_5, 0),

			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			/* Calculated offset in R6 has unknown value, but known
			 * alignment of 4.
			 */
			अणु8, "R2_w=pkt(id=0,off=0,r=8,imm=0)"पूर्ण,
			अणु8, "R6_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Offset is added to packet poपूर्णांकer R5, resulting in
			 * known fixed offset, and variable offset from R6.
			 */
			अणु11, "R5_w=pkt(id=1,off=14,r=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* At the समय the word size load is perक्रमmed from R5,
			 * it's total offset is NET_IP_ALIGN + reg->off (0) +
			 * reg->aux_off (14) which is 16.  Then the variable
			 * offset is considered using reg->aux_off_align which
			 * is 4 and meets the load's requirements.
			 */
			अणु15, "R4=pkt(id=1,off=18,r=18,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			अणु15, "R5=pkt(id=1,off=14,r=18,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Variable offset is added to R5 packet poपूर्णांकer,
			 * resulting in auxiliary alignment of 4.
			 */
			अणु18, "R5_w=pkt(id=2,off=0,r=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Constant offset is added to R5, resulting in
			 * reg->off of 14.
			 */
			अणु19, "R5_w=pkt(id=2,off=14,r=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* At the समय the word size load is perक्रमmed from R5,
			 * its total fixed offset is NET_IP_ALIGN + reg->off
			 * (14) which is 16.  Then the variable offset is 4-byte
			 * aligned, so the total offset is 4-byte aligned and
			 * meets the load's requirements.
			 */
			अणु23, "R4=pkt(id=2,off=18,r=18,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			अणु23, "R5=pkt(id=2,off=14,r=18,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Constant offset is added to R5 packet poपूर्णांकer,
			 * resulting in reg->off value of 14.
			 */
			अणु26, "R5_w=pkt(id=0,off=14,r=8"पूर्ण,
			/* Variable offset is added to R5, resulting in a
			 * variable offset of (4n).
			 */
			अणु27, "R5_w=pkt(id=3,off=14,r=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Constant is added to R5 again, setting reg->off to 18. */
			अणु28, "R5_w=pkt(id=3,off=18,r=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* And once more we add a variable; resulting var_off
			 * is still (4n), fixed offset is not changed.
			 * Also, we create a new reg->id.
			 */
			अणु29, "R5_w=pkt(id=4,off=18,r=0,umax_value=2040,var_off=(0x0; 0x7fc)"पूर्ण,
			/* At the समय the word size load is perक्रमmed from R5,
			 * its total fixed offset is NET_IP_ALIGN + reg->off (18)
			 * which is 20.  Then the variable offset is (4n), so
			 * the total offset is 4-byte aligned and meets the
			 * load's requirements.
			 */
			अणु33, "R4=pkt(id=4,off=22,r=22,umax_value=2040,var_off=(0x0; 0x7fc)"पूर्ण,
			अणु33, "R5=pkt(id=4,off=18,r=22,umax_value=2040,var_off=(0x0; 0x7fc)"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "packet variable offset 2",
		.insns = अणु
			/* Create an unknown offset, (4n+2)-aligned */
			LOAD_UNKNOWN(BPF_REG_6),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_6, 2),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_6, 14),
			/* Add it to the packet poपूर्णांकer */
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_2),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_6),
			/* Check bounds and perक्रमm a पढ़ो */
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_5, 0),
			/* Make a (4n) offset from the value we just पढ़ो */
			BPF_ALU64_IMM(BPF_AND, BPF_REG_6, 0xff),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_6, 2),
			/* Add it to the packet poपूर्णांकer */
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_6),
			/* Check bounds and perक्रमm a पढ़ो */
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_5, 0),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			/* Calculated offset in R6 has unknown value, but known
			 * alignment of 4.
			 */
			अणु8, "R2_w=pkt(id=0,off=0,r=8,imm=0)"पूर्ण,
			अणु8, "R6_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Adding 14 makes R6 be (4n+2) */
			अणु9, "R6_w=inv(id=0,umin_value=14,umax_value=1034,var_off=(0x2; 0x7fc))"पूर्ण,
			/* Packet poपूर्णांकer has (4n+2) offset */
			अणु11, "R5_w=pkt(id=1,off=0,r=0,umin_value=14,umax_value=1034,var_off=(0x2; 0x7fc)"पूर्ण,
			अणु13, "R4=pkt(id=1,off=4,r=0,umin_value=14,umax_value=1034,var_off=(0x2; 0x7fc)"पूर्ण,
			/* At the समय the word size load is perक्रमmed from R5,
			 * its total fixed offset is NET_IP_ALIGN + reg->off (0)
			 * which is 2.  Then the variable offset is (4n+2), so
			 * the total offset is 4-byte aligned and meets the
			 * load's requirements.
			 */
			अणु15, "R5=pkt(id=1,off=0,r=4,umin_value=14,umax_value=1034,var_off=(0x2; 0x7fc)"पूर्ण,
			/* Newly पढ़ो value in R6 was shअगरted left by 2, so has
			 * known alignment of 4.
			 */
			अणु18, "R6_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Added (4n) to packet poपूर्णांकer's (4n+2) var_off, giving
			 * another (4n+2).
			 */
			अणु19, "R5_w=pkt(id=2,off=0,r=0,umin_value=14,umax_value=2054,var_off=(0x2; 0xffc)"पूर्ण,
			अणु21, "R4=pkt(id=2,off=4,r=0,umin_value=14,umax_value=2054,var_off=(0x2; 0xffc)"पूर्ण,
			/* At the समय the word size load is perक्रमmed from R5,
			 * its total fixed offset is NET_IP_ALIGN + reg->off (0)
			 * which is 2.  Then the variable offset is (4n+2), so
			 * the total offset is 4-byte aligned and meets the
			 * load's requirements.
			 */
			अणु23, "R5=pkt(id=2,off=0,r=4,umin_value=14,umax_value=2054,var_off=(0x2; 0xffc)"पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.descr = "dubious pointer arithmetic",
		.insns = अणु
			PREP_PKT_POINTERS,
			BPF_MOV64_IMM(BPF_REG_0, 0),
			/* (ptr - ptr) << 2 */
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_3),
			BPF_ALU64_REG(BPF_SUB, BPF_REG_5, BPF_REG_2),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_5, 2),
			/* We have a (4n) value.  Let's make a packet offset
			 * out of it.  First add 14, to make it a (4n+2)
			 */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 14),
			/* Then make sure it's nonnegative */
			BPF_JMP_IMM(BPF_JSGE, BPF_REG_5, 0, 1),
			BPF_EXIT_INSN(),
			/* Add it to packet poपूर्णांकer */
			BPF_MOV64_REG(BPF_REG_6, BPF_REG_2),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_5),
			/* Check bounds and perक्रमm a पढ़ो */
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_6),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_4, BPF_REG_6, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.result = REJECT,
		.matches = अणु
			अणु4, "R5_w=pkt_end(id=0,off=0,imm=0)"पूर्ण,
			/* (ptr - ptr) << 2 == unknown, (4n) */
			अणु6, "R5_w=inv(id=0,smax_value=9223372036854775804,umax_value=18446744073709551612,var_off=(0x0; 0xfffffffffffffffc)"पूर्ण,
			/* (4n) + 14 == (4n+2).  We blow our bounds, because
			 * the add could overflow.
			 */
			अणु7, "R5_w=inv(id=0,smin_value=-9223372036854775806,smax_value=9223372036854775806,umin_value=2,umax_value=18446744073709551614,var_off=(0x2; 0xfffffffffffffffc)"पूर्ण,
			/* Checked s>=0 */
			अणु9, "R5=inv(id=0,umin_value=2,umax_value=9223372036854775806,var_off=(0x2; 0x7ffffffffffffffc)"पूर्ण,
			/* packet poपूर्णांकer + nonnegative (4n+2) */
			अणु11, "R6_w=pkt(id=1,off=0,r=0,umin_value=2,umax_value=9223372036854775806,var_off=(0x2; 0x7ffffffffffffffc)"पूर्ण,
			अणु13, "R4_w=pkt(id=1,off=4,r=0,umin_value=2,umax_value=9223372036854775806,var_off=(0x2; 0x7ffffffffffffffc)"पूर्ण,
			/* NET_IP_ALIGN + (4n+2) == (4n), alignment is fine.
			 * We checked the bounds, but it might have been able
			 * to overflow अगर the packet poपूर्णांकer started in the
			 * upper half of the address space.
			 * So we did not get a 'range' on R6, and the access
			 * attempt will fail.
			 */
			अणु15, "R6_w=pkt(id=1,off=0,r=0,umin_value=2,umax_value=9223372036854775806,var_off=(0x2; 0x7ffffffffffffffc)"पूर्ण,
		पूर्ण
	पूर्ण,
	अणु
		.descr = "variable subtraction",
		.insns = अणु
			/* Create an unknown offset, (4n+2)-aligned */
			LOAD_UNKNOWN(BPF_REG_6),
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_6),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_6, 2),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_6, 14),
			/* Create another unknown, (4n)-aligned, and subtract
			 * it from the first one
			 */
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_7, 2),
			BPF_ALU64_REG(BPF_SUB, BPF_REG_6, BPF_REG_7),
			/* Bounds-check the result */
			BPF_JMP_IMM(BPF_JSGE, BPF_REG_6, 0, 1),
			BPF_EXIT_INSN(),
			/* Add it to the packet poपूर्णांकer */
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_2),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_6),
			/* Check bounds and perक्रमm a पढ़ो */
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_5, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			/* Calculated offset in R6 has unknown value, but known
			 * alignment of 4.
			 */
			अणु7, "R2_w=pkt(id=0,off=0,r=8,imm=0)"पूर्ण,
			अणु9, "R6_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Adding 14 makes R6 be (4n+2) */
			अणु10, "R6_w=inv(id=0,umin_value=14,umax_value=1034,var_off=(0x2; 0x7fc))"पूर्ण,
			/* New unknown value in R7 is (4n) */
			अणु11, "R7_w=inv(id=0,umax_value=1020,var_off=(0x0; 0x3fc))"पूर्ण,
			/* Subtracting it from R6 blows our अचिन्हित bounds */
			अणु12, "R6=inv(id=0,smin_value=-1006,smax_value=1034,umin_value=2,umax_value=18446744073709551614,var_off=(0x2; 0xfffffffffffffffc)"पूर्ण,
			/* Checked s>= 0 */
			अणु14, "R6=inv(id=0,umin_value=2,umax_value=1034,var_off=(0x2; 0x7fc))"पूर्ण,
			/* At the समय the word size load is perक्रमmed from R5,
			 * its total fixed offset is NET_IP_ALIGN + reg->off (0)
			 * which is 2.  Then the variable offset is (4n+2), so
			 * the total offset is 4-byte aligned and meets the
			 * load's requirements.
			 */
			अणु20, "R5=pkt(id=2,off=0,r=4,umin_value=2,umax_value=1034,var_off=(0x2; 0x7fc)"पूर्ण,

		पूर्ण,
	पूर्ण,
	अणु
		.descr = "pointer variable subtraction",
		.insns = अणु
			/* Create an unknown offset, (4n+2)-aligned and bounded
			 * to [14,74]
			 */
			LOAD_UNKNOWN(BPF_REG_6),
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_6),
			BPF_ALU64_IMM(BPF_AND, BPF_REG_6, 0xf),
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_6, 2),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_6, 14),
			/* Subtract it from the packet poपूर्णांकer */
			BPF_MOV64_REG(BPF_REG_5, BPF_REG_2),
			BPF_ALU64_REG(BPF_SUB, BPF_REG_5, BPF_REG_6),
			/* Create another unknown, (4n)-aligned and >= 74.
			 * That in fact means >= 76, since 74 % 4 == 2
			 */
			BPF_ALU64_IMM(BPF_LSH, BPF_REG_7, 2),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, 76),
			/* Add it to the packet poपूर्णांकer */
			BPF_ALU64_REG(BPF_ADD, BPF_REG_5, BPF_REG_7),
			/* Check bounds and perक्रमm a पढ़ो */
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_5),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 4),
			BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_4, 1),
			BPF_EXIT_INSN(),
			BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_5, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.prog_type = BPF_PROG_TYPE_SCHED_CLS,
		.matches = अणु
			/* Calculated offset in R6 has unknown value, but known
			 * alignment of 4.
			 */
			अणु7, "R2_w=pkt(id=0,off=0,r=8,imm=0)"पूर्ण,
			अणु10, "R6_w=inv(id=0,umax_value=60,var_off=(0x0; 0x3c))"पूर्ण,
			/* Adding 14 makes R6 be (4n+2) */
			अणु11, "R6_w=inv(id=0,umin_value=14,umax_value=74,var_off=(0x2; 0x7c))"पूर्ण,
			/* Subtracting from packet poपूर्णांकer overflows ubounds */
			अणु13, "R5_w=pkt(id=2,off=0,r=8,umin_value=18446744073709551542,umax_value=18446744073709551602,var_off=(0xffffffffffffff82; 0x7c)"पूर्ण,
			/* New unknown value in R7 is (4n), >= 76 */
			अणु15, "R7_w=inv(id=0,umin_value=76,umax_value=1096,var_off=(0x0; 0x7fc))"पूर्ण,
			/* Adding it to packet poपूर्णांकer gives nice bounds again */
			अणु16, "R5_w=pkt(id=3,off=0,r=0,umin_value=2,umax_value=1082,var_off=(0x2; 0xfffffffc)"पूर्ण,
			/* At the समय the word size load is perक्रमmed from R5,
			 * its total fixed offset is NET_IP_ALIGN + reg->off (0)
			 * which is 2.  Then the variable offset is (4n+2), so
			 * the total offset is 4-byte aligned and meets the
			 * load's requirements.
			 */
			अणु20, "R5=pkt(id=3,off=0,r=4,umin_value=2,umax_value=1082,var_off=(0x2; 0xfffffffc)"पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक probe_filter_length(स्थिर काष्ठा bpf_insn *fp)
अणु
	पूर्णांक len;

	क्रम (len = MAX_INSNS - 1; len > 0; --len)
		अगर (fp[len].code != 0 || fp[len].imm != 0)
			अवरोध;
	वापस len + 1;
पूर्ण

अटल अक्षर bpf_vlog[32768];

अटल पूर्णांक करो_test_single(काष्ठा bpf_align_test *test)
अणु
	काष्ठा bpf_insn *prog = test->insns;
	पूर्णांक prog_type = test->prog_type;
	अक्षर bpf_vlog_copy[32768];
	स्थिर अक्षर *line_ptr;
	पूर्णांक cur_line = -1;
	पूर्णांक prog_len, i;
	पूर्णांक fd_prog;
	पूर्णांक ret;

	prog_len = probe_filter_length(prog);
	fd_prog = bpf_verअगरy_program(prog_type ? : BPF_PROG_TYPE_SOCKET_FILTER,
				     prog, prog_len, BPF_F_STRICT_ALIGNMENT,
				     "GPL", 0, bpf_vlog, माप(bpf_vlog), 2);
	अगर (fd_prog < 0 && test->result != REJECT) अणु
		म_लिखो("Failed to load program.\n");
		म_लिखो("%s", bpf_vlog);
		ret = 1;
	पूर्ण अन्यथा अगर (fd_prog >= 0 && test->result == REJECT) अणु
		म_लिखो("Unexpected success to load!\n");
		म_लिखो("%s", bpf_vlog);
		ret = 1;
		बंद(fd_prog);
	पूर्ण अन्यथा अणु
		ret = 0;
		/* We make a local copy so that we can म_मोहर() it */
		म_नकलन(bpf_vlog_copy, bpf_vlog, माप(bpf_vlog_copy));
		line_ptr = म_मोहर(bpf_vlog_copy, "\n");
		क्रम (i = 0; i < MAX_MATCHES; i++) अणु
			काष्ठा bpf_reg_match m = test->matches[i];

			अगर (!m.match)
				अवरोध;
			जबतक (line_ptr) अणु
				cur_line = -1;
				माला_पूछो(line_ptr, "%u: ", &cur_line);
				अगर (cur_line == m.line)
					अवरोध;
				line_ptr = म_मोहर(शून्य, "\n");
			पूर्ण
			अगर (!line_ptr) अणु
				म_लिखो("Failed to find line %u for match: %s\n",
				       m.line, m.match);
				ret = 1;
				म_लिखो("%s", bpf_vlog);
				अवरोध;
			पूर्ण
			अगर (!म_माला(line_ptr, m.match)) अणु
				म_लिखो("Failed to find match %u: %s\n",
				       m.line, m.match);
				ret = 1;
				म_लिखो("%s", bpf_vlog);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (fd_prog >= 0)
			बंद(fd_prog);
	पूर्ण
	वापस ret;
पूर्ण

व्योम test_align(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		काष्ठा bpf_align_test *test = &tests[i];

		अगर (!test__start_subtest(test->descr))
			जारी;

		CHECK_FAIL(करो_test_single(test));
	पूर्ण
पूर्ण
