<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2016 Facebook
 */

#समावेश <linux/bpf.h>

#समावेश "disasm.h"

#घोषणा __BPF_FUNC_STR_FN(x) [BPF_FUNC_ ## x] = __stringअगरy(bpf_ ## x)
अटल स्थिर अक्षर * स्थिर func_id_str[] = अणु
	__BPF_FUNC_MAPPER(__BPF_FUNC_STR_FN)
पूर्ण;
#अघोषित __BPF_FUNC_STR_FN

अटल स्थिर अक्षर *__func_get_name(स्थिर काष्ठा bpf_insn_cbs *cbs,
				   स्थिर काष्ठा bpf_insn *insn,
				   अक्षर *buff, माप_प्रकार len)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(func_id_str) != __BPF_FUNC_MAX_ID);

	अगर (!insn->src_reg &&
	    insn->imm >= 0 && insn->imm < __BPF_FUNC_MAX_ID &&
	    func_id_str[insn->imm])
		वापस func_id_str[insn->imm];

	अगर (cbs && cbs->cb_call) अणु
		स्थिर अक्षर *res;

		res = cbs->cb_call(cbs->निजी_data, insn);
		अगर (res)
			वापस res;
	पूर्ण

	अगर (insn->src_reg == BPF_PSEUDO_CALL)
		snम_लिखो(buff, len, "%+d", insn->imm);
	अन्यथा अगर (insn->src_reg == BPF_PSEUDO_KFUNC_CALL)
		snम_लिखो(buff, len, "kernel-function");

	वापस buff;
पूर्ण

अटल स्थिर अक्षर *__func_imm_name(स्थिर काष्ठा bpf_insn_cbs *cbs,
				   स्थिर काष्ठा bpf_insn *insn,
				   u64 full_imm, अक्षर *buff, माप_प्रकार len)
अणु
	अगर (cbs && cbs->cb_imm)
		वापस cbs->cb_imm(cbs->निजी_data, insn, full_imm);

	snम_लिखो(buff, len, "0x%llx", (अचिन्हित दीर्घ दीर्घ)full_imm);
	वापस buff;
पूर्ण

स्थिर अक्षर *func_id_name(पूर्णांक id)
अणु
	अगर (id >= 0 && id < __BPF_FUNC_MAX_ID && func_id_str[id])
		वापस func_id_str[id];
	अन्यथा
		वापस "unknown";
पूर्ण

स्थिर अक्षर *स्थिर bpf_class_string[8] = अणु
	[BPF_LD]    = "ld",
	[BPF_LDX]   = "ldx",
	[BPF_ST]    = "st",
	[BPF_STX]   = "stx",
	[BPF_ALU]   = "alu",
	[BPF_JMP]   = "jmp",
	[BPF_JMP32] = "jmp32",
	[BPF_ALU64] = "alu64",
पूर्ण;

स्थिर अक्षर *स्थिर bpf_alu_string[16] = अणु
	[BPF_ADD >> 4]  = "+=",
	[BPF_SUB >> 4]  = "-=",
	[BPF_MUL >> 4]  = "*=",
	[BPF_DIV >> 4]  = "/=",
	[BPF_OR  >> 4]  = "|=",
	[BPF_AND >> 4]  = "&=",
	[BPF_LSH >> 4]  = "<<=",
	[BPF_RSH >> 4]  = ">>=",
	[BPF_NEG >> 4]  = "neg",
	[BPF_MOD >> 4]  = "%=",
	[BPF_XOR >> 4]  = "^=",
	[BPF_MOV >> 4]  = "=",
	[BPF_ARSH >> 4] = "s>>=",
	[BPF_END >> 4]  = "endian",
पूर्ण;

अटल स्थिर अक्षर *स्थिर bpf_atomic_alu_string[16] = अणु
	[BPF_ADD >> 4]  = "add",
	[BPF_AND >> 4]  = "and",
	[BPF_OR >> 4]  = "or",
	[BPF_XOR >> 4]  = "xor",
पूर्ण;

अटल स्थिर अक्षर *स्थिर bpf_ldst_string[] = अणु
	[BPF_W >> 3]  = "u32",
	[BPF_H >> 3]  = "u16",
	[BPF_B >> 3]  = "u8",
	[BPF_DW >> 3] = "u64",
पूर्ण;

अटल स्थिर अक्षर *स्थिर bpf_jmp_string[16] = अणु
	[BPF_JA >> 4]   = "jmp",
	[BPF_JEQ >> 4]  = "==",
	[BPF_JGT >> 4]  = ">",
	[BPF_JLT >> 4]  = "<",
	[BPF_JGE >> 4]  = ">=",
	[BPF_JLE >> 4]  = "<=",
	[BPF_JSET >> 4] = "&",
	[BPF_JNE >> 4]  = "!=",
	[BPF_JSGT >> 4] = "s>",
	[BPF_JSLT >> 4] = "s<",
	[BPF_JSGE >> 4] = "s>=",
	[BPF_JSLE >> 4] = "s<=",
	[BPF_CALL >> 4] = "call",
	[BPF_EXIT >> 4] = "exit",
पूर्ण;

अटल व्योम prपूर्णांक_bpf_end_insn(bpf_insn_prपूर्णांक_t verbose,
			       व्योम *निजी_data,
			       स्थिर काष्ठा bpf_insn *insn)
अणु
	verbose(निजी_data, "(%02x) r%d = %s%d r%d\n",
		insn->code, insn->dst_reg,
		BPF_SRC(insn->code) == BPF_TO_BE ? "be" : "le",
		insn->imm, insn->dst_reg);
पूर्ण

व्योम prपूर्णांक_bpf_insn(स्थिर काष्ठा bpf_insn_cbs *cbs,
		    स्थिर काष्ठा bpf_insn *insn,
		    bool allow_ptr_leaks)
अणु
	स्थिर bpf_insn_prपूर्णांक_t verbose = cbs->cb_prपूर्णांक;
	u8 class = BPF_CLASS(insn->code);

	अगर (class == BPF_ALU || class == BPF_ALU64) अणु
		अगर (BPF_OP(insn->code) == BPF_END) अणु
			अगर (class == BPF_ALU64)
				verbose(cbs->निजी_data, "BUG_alu64_%02x\n", insn->code);
			अन्यथा
				prपूर्णांक_bpf_end_insn(verbose, cbs->निजी_data, insn);
		पूर्ण अन्यथा अगर (BPF_OP(insn->code) == BPF_NEG) अणु
			verbose(cbs->निजी_data, "(%02x) %c%d = -%c%d\n",
				insn->code, class == BPF_ALU ? 'w' : 'r',
				insn->dst_reg, class == BPF_ALU ? 'w' : 'r',
				insn->dst_reg);
		पूर्ण अन्यथा अगर (BPF_SRC(insn->code) == BPF_X) अणु
			verbose(cbs->निजी_data, "(%02x) %c%d %s %c%d\n",
				insn->code, class == BPF_ALU ? 'w' : 'r',
				insn->dst_reg,
				bpf_alu_string[BPF_OP(insn->code) >> 4],
				class == BPF_ALU ? 'w' : 'r',
				insn->src_reg);
		पूर्ण अन्यथा अणु
			verbose(cbs->निजी_data, "(%02x) %c%d %s %d\n",
				insn->code, class == BPF_ALU ? 'w' : 'r',
				insn->dst_reg,
				bpf_alu_string[BPF_OP(insn->code) >> 4],
				insn->imm);
		पूर्ण
	पूर्ण अन्यथा अगर (class == BPF_STX) अणु
		अगर (BPF_MODE(insn->code) == BPF_MEM)
			verbose(cbs->निजी_data, "(%02x) *(%s *)(r%d %+d) = r%d\n",
				insn->code,
				bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
				insn->dst_reg,
				insn->off, insn->src_reg);
		अन्यथा अगर (BPF_MODE(insn->code) == BPF_ATOMIC &&
			 (insn->imm == BPF_ADD || insn->imm == BPF_AND ||
			  insn->imm == BPF_OR || insn->imm == BPF_XOR)) अणु
			verbose(cbs->निजी_data, "(%02x) lock *(%s *)(r%d %+d) %s r%d\n",
				insn->code,
				bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
				insn->dst_reg, insn->off,
				bpf_alu_string[BPF_OP(insn->imm) >> 4],
				insn->src_reg);
		पूर्ण अन्यथा अगर (BPF_MODE(insn->code) == BPF_ATOMIC &&
			   (insn->imm == (BPF_ADD | BPF_FETCH) ||
			    insn->imm == (BPF_AND | BPF_FETCH) ||
			    insn->imm == (BPF_OR | BPF_FETCH) ||
			    insn->imm == (BPF_XOR | BPF_FETCH))) अणु
			verbose(cbs->निजी_data, "(%02x) r%d = atomic%s_fetch_%s((%s *)(r%d %+d), r%d)\n",
				insn->code, insn->src_reg,
				BPF_SIZE(insn->code) == BPF_DW ? "64" : "",
				bpf_atomic_alu_string[BPF_OP(insn->imm) >> 4],
				bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
				insn->dst_reg, insn->off, insn->src_reg);
		पूर्ण अन्यथा अगर (BPF_MODE(insn->code) == BPF_ATOMIC &&
			   insn->imm == BPF_CMPXCHG) अणु
			verbose(cbs->निजी_data, "(%02x) r0 = atomic%s_cmpxchg((%s *)(r%d %+d), r0, r%d)\n",
				insn->code,
				BPF_SIZE(insn->code) == BPF_DW ? "64" : "",
				bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
				insn->dst_reg, insn->off,
				insn->src_reg);
		पूर्ण अन्यथा अगर (BPF_MODE(insn->code) == BPF_ATOMIC &&
			   insn->imm == BPF_XCHG) अणु
			verbose(cbs->निजी_data, "(%02x) r%d = atomic%s_xchg((%s *)(r%d %+d), r%d)\n",
				insn->code, insn->src_reg,
				BPF_SIZE(insn->code) == BPF_DW ? "64" : "",
				bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
				insn->dst_reg, insn->off, insn->src_reg);
		पूर्ण अन्यथा अणु
			verbose(cbs->निजी_data, "BUG_%02x\n", insn->code);
		पूर्ण
	पूर्ण अन्यथा अगर (class == BPF_ST) अणु
		अगर (BPF_MODE(insn->code) != BPF_MEM) अणु
			verbose(cbs->निजी_data, "BUG_st_%02x\n", insn->code);
			वापस;
		पूर्ण
		verbose(cbs->निजी_data, "(%02x) *(%s *)(r%d %+d) = %d\n",
			insn->code,
			bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
			insn->dst_reg,
			insn->off, insn->imm);
	पूर्ण अन्यथा अगर (class == BPF_LDX) अणु
		अगर (BPF_MODE(insn->code) != BPF_MEM) अणु
			verbose(cbs->निजी_data, "BUG_ldx_%02x\n", insn->code);
			वापस;
		पूर्ण
		verbose(cbs->निजी_data, "(%02x) r%d = *(%s *)(r%d %+d)\n",
			insn->code, insn->dst_reg,
			bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
			insn->src_reg, insn->off);
	पूर्ण अन्यथा अगर (class == BPF_LD) अणु
		अगर (BPF_MODE(insn->code) == BPF_ABS) अणु
			verbose(cbs->निजी_data, "(%02x) r0 = *(%s *)skb[%d]\n",
				insn->code,
				bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
				insn->imm);
		पूर्ण अन्यथा अगर (BPF_MODE(insn->code) == BPF_IND) अणु
			verbose(cbs->निजी_data, "(%02x) r0 = *(%s *)skb[r%d + %d]\n",
				insn->code,
				bpf_ldst_string[BPF_SIZE(insn->code) >> 3],
				insn->src_reg, insn->imm);
		पूर्ण अन्यथा अगर (BPF_MODE(insn->code) == BPF_IMM &&
			   BPF_SIZE(insn->code) == BPF_DW) अणु
			/* At this poपूर्णांक, we alपढ़ोy made sure that the second
			 * part of the ldimm64 insn is accessible.
			 */
			u64 imm = ((u64)(insn + 1)->imm << 32) | (u32)insn->imm;
			bool is_ptr = insn->src_reg == BPF_PSEUDO_MAP_FD ||
				      insn->src_reg == BPF_PSEUDO_MAP_VALUE;
			अक्षर पंचांगp[64];

			अगर (is_ptr && !allow_ptr_leaks)
				imm = 0;

			verbose(cbs->निजी_data, "(%02x) r%d = %s\n",
				insn->code, insn->dst_reg,
				__func_imm_name(cbs, insn, imm,
						पंचांगp, माप(पंचांगp)));
		पूर्ण अन्यथा अणु
			verbose(cbs->निजी_data, "BUG_ld_%02x\n", insn->code);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (class == BPF_JMP32 || class == BPF_JMP) अणु
		u8 opcode = BPF_OP(insn->code);

		अगर (opcode == BPF_CALL) अणु
			अक्षर पंचांगp[64];

			अगर (insn->src_reg == BPF_PSEUDO_CALL) अणु
				verbose(cbs->निजी_data, "(%02x) call pc%s\n",
					insn->code,
					__func_get_name(cbs, insn,
							पंचांगp, माप(पंचांगp)));
			पूर्ण अन्यथा अणु
				म_नकल(पंचांगp, "unknown");
				verbose(cbs->निजी_data, "(%02x) call %s#%d\n", insn->code,
					__func_get_name(cbs, insn,
							पंचांगp, माप(पंचांगp)),
					insn->imm);
			पूर्ण
		पूर्ण अन्यथा अगर (insn->code == (BPF_JMP | BPF_JA)) अणु
			verbose(cbs->निजी_data, "(%02x) goto pc%+d\n",
				insn->code, insn->off);
		पूर्ण अन्यथा अगर (insn->code == (BPF_JMP | BPF_EXIT)) अणु
			verbose(cbs->निजी_data, "(%02x) exit\n", insn->code);
		पूर्ण अन्यथा अगर (BPF_SRC(insn->code) == BPF_X) अणु
			verbose(cbs->निजी_data,
				"(%02x) if %c%d %s %c%d goto pc%+d\n",
				insn->code, class == BPF_JMP32 ? 'w' : 'r',
				insn->dst_reg,
				bpf_jmp_string[BPF_OP(insn->code) >> 4],
				class == BPF_JMP32 ? 'w' : 'r',
				insn->src_reg, insn->off);
		पूर्ण अन्यथा अणु
			verbose(cbs->निजी_data,
				"(%02x) if %c%d %s 0x%x goto pc%+d\n",
				insn->code, class == BPF_JMP32 ? 'w' : 'r',
				insn->dst_reg,
				bpf_jmp_string[BPF_OP(insn->code) >> 4],
				insn->imm, insn->off);
		पूर्ण
	पूर्ण अन्यथा अणु
		verbose(cbs->निजी_data, "(%02x) %s\n",
			insn->code, bpf_class_string[class]);
	पूर्ण
पूर्ण
