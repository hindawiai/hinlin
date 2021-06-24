<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pt_insn_decoder.c: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <endian.h>
#समावेश <byteswap.h>
#समावेश "../../../arch/x86/include/asm/insn.h"

#समावेश "../../../arch/x86/lib/inat.c"
#समावेश "../../../arch/x86/lib/insn.c"

#समावेश "event.h"

#समावेश "intel-pt-insn-decoder.h"
#समावेश "dump-insn.h"

#अगर INTEL_PT_INSN_BUF_SZ < MAX_INSN_SIZE || INTEL_PT_INSN_BUF_SZ > MAX_INSN
#त्रुटि Inकाष्ठाion buffer size too small
#पूर्ण_अगर

/* Based on branch_type() from arch/x86/events/पूर्णांकel/lbr.c */
अटल व्योम पूर्णांकel_pt_insn_decoder(काष्ठा insn *insn,
				  काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn)
अणु
	क्रमागत पूर्णांकel_pt_insn_op op = INTEL_PT_OP_OTHER;
	क्रमागत पूर्णांकel_pt_insn_branch branch = INTEL_PT_BR_NO_BRANCH;
	पूर्णांक ext;

	पूर्णांकel_pt_insn->rel = 0;

	अगर (insn_is_avx(insn)) अणु
		पूर्णांकel_pt_insn->op = INTEL_PT_OP_OTHER;
		पूर्णांकel_pt_insn->branch = INTEL_PT_BR_NO_BRANCH;
		पूर्णांकel_pt_insn->length = insn->length;
		वापस;
	पूर्ण

	चयन (insn->opcode.bytes[0]) अणु
	हाल 0xf:
		चयन (insn->opcode.bytes[1]) अणु
		हाल 0x01:
			चयन (insn->modrm.bytes[0]) अणु
			हाल 0xc2: /* vmlaunch */
			हाल 0xc3: /* vmresume */
				op = INTEL_PT_OP_VMENTRY;
				branch = INTEL_PT_BR_INसूचीECT;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x05: /* syscall */
		हाल 0x34: /* sysenter */
			op = INTEL_PT_OP_SYSCALL;
			branch = INTEL_PT_BR_INसूचीECT;
			अवरोध;
		हाल 0x07: /* sysret */
		हाल 0x35: /* sysनिकास */
			op = INTEL_PT_OP_SYSRET;
			branch = INTEL_PT_BR_INसूचीECT;
			अवरोध;
		हाल 0x80 ... 0x8f: /* jcc */
			op = INTEL_PT_OP_JCC;
			branch = INTEL_PT_BR_CONDITIONAL;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x70 ... 0x7f: /* jcc */
		op = INTEL_PT_OP_JCC;
		branch = INTEL_PT_BR_CONDITIONAL;
		अवरोध;
	हाल 0xc2: /* near ret */
	हाल 0xc3: /* near ret */
	हाल 0xca: /* far ret */
	हाल 0xcb: /* far ret */
		op = INTEL_PT_OP_RET;
		branch = INTEL_PT_BR_INसूचीECT;
		अवरोध;
	हाल 0xcf: /* iret */
		op = INTEL_PT_OP_IRET;
		branch = INTEL_PT_BR_INसूचीECT;
		अवरोध;
	हाल 0xcc ... 0xce: /* पूर्णांक */
		op = INTEL_PT_OP_INT;
		branch = INTEL_PT_BR_INसूचीECT;
		अवरोध;
	हाल 0xe8: /* call near rel */
		op = INTEL_PT_OP_CALL;
		branch = INTEL_PT_BR_UNCONDITIONAL;
		अवरोध;
	हाल 0x9a: /* call far असलolute */
		op = INTEL_PT_OP_CALL;
		branch = INTEL_PT_BR_INसूचीECT;
		अवरोध;
	हाल 0xe0 ... 0xe2: /* loop */
		op = INTEL_PT_OP_LOOP;
		branch = INTEL_PT_BR_CONDITIONAL;
		अवरोध;
	हाल 0xe3: /* jcc */
		op = INTEL_PT_OP_JCC;
		branch = INTEL_PT_BR_CONDITIONAL;
		अवरोध;
	हाल 0xe9: /* jmp */
	हाल 0xeb: /* jmp */
		op = INTEL_PT_OP_JMP;
		branch = INTEL_PT_BR_UNCONDITIONAL;
		अवरोध;
	हाल 0xea: /* far jmp */
		op = INTEL_PT_OP_JMP;
		branch = INTEL_PT_BR_INसूचीECT;
		अवरोध;
	हाल 0xff: /* call near असलolute, call far असलolute ind */
		ext = (insn->modrm.bytes[0] >> 3) & 0x7;
		चयन (ext) अणु
		हाल 2: /* near ind call */
		हाल 3: /* far ind call */
			op = INTEL_PT_OP_CALL;
			branch = INTEL_PT_BR_INसूचीECT;
			अवरोध;
		हाल 4:
		हाल 5:
			op = INTEL_PT_OP_JMP;
			branch = INTEL_PT_BR_INसूचीECT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	पूर्णांकel_pt_insn->op = op;
	पूर्णांकel_pt_insn->branch = branch;
	पूर्णांकel_pt_insn->length = insn->length;

	अगर (branch == INTEL_PT_BR_CONDITIONAL ||
	    branch == INTEL_PT_BR_UNCONDITIONAL) अणु
#अगर __BYTE_ORDER == __BIG_ENDIAN
		चयन (insn->immediate.nbytes) अणु
		हाल 1:
			पूर्णांकel_pt_insn->rel = insn->immediate.value;
			अवरोध;
		हाल 2:
			पूर्णांकel_pt_insn->rel =
					bswap_16((लघु)insn->immediate.value);
			अवरोध;
		हाल 4:
			पूर्णांकel_pt_insn->rel = bswap_32(insn->immediate.value);
			अवरोध;
		शेष:
			पूर्णांकel_pt_insn->rel = 0;
			अवरोध;
		पूर्ण
#अन्यथा
		पूर्णांकel_pt_insn->rel = insn->immediate.value;
#पूर्ण_अगर
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_pt_get_insn(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len, पूर्णांक x86_64,
		      काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn)
अणु
	काष्ठा insn insn;
	पूर्णांक ret;

	ret = insn_decode(&insn, buf, len,
			  x86_64 ? INSN_MODE_64 : INSN_MODE_32);
	अगर (ret < 0 || insn.length > len)
		वापस -1;

	पूर्णांकel_pt_insn_decoder(&insn, पूर्णांकel_pt_insn);
	अगर (insn.length < INTEL_PT_INSN_BUF_SZ)
		स_नकल(पूर्णांकel_pt_insn->buf, buf, insn.length);
	अन्यथा
		स_नकल(पूर्णांकel_pt_insn->buf, buf, INTEL_PT_INSN_BUF_SZ);
	वापस 0;
पूर्ण

पूर्णांक arch_is_branch(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len, पूर्णांक x86_64)
अणु
	काष्ठा पूर्णांकel_pt_insn in;
	अगर (पूर्णांकel_pt_get_insn(buf, len, x86_64, &in) < 0)
		वापस -1;
	वापस in.branch != INTEL_PT_BR_NO_BRANCH;
पूर्ण

स्थिर अक्षर *dump_insn(काष्ठा perf_insn *x, uपूर्णांक64_t ip __maybe_unused,
		      u8 *inbuf, पूर्णांक inlen, पूर्णांक *lenp)
अणु
	काष्ठा insn insn;
	पूर्णांक n, i, ret;
	पूर्णांक left;

	ret = insn_decode(&insn, inbuf, inlen,
			  x->is64bit ? INSN_MODE_64 : INSN_MODE_32);

	अगर (ret < 0 || insn.length > inlen)
		वापस "<bad>";
	अगर (lenp)
		*lenp = insn.length;
	left = माप(x->out);
	n = snम_लिखो(x->out, left, "insn: ");
	left -= n;
	क्रम (i = 0; i < insn.length; i++) अणु
		n += snम_लिखो(x->out + n, left, "%02x ", inbuf[i]);
		left -= n;
	पूर्ण
	वापस x->out;
पूर्ण

स्थिर अक्षर *branch_name[] = अणु
	[INTEL_PT_OP_OTHER]	= "Other",
	[INTEL_PT_OP_CALL]	= "Call",
	[INTEL_PT_OP_RET]	= "Ret",
	[INTEL_PT_OP_JCC]	= "Jcc",
	[INTEL_PT_OP_JMP]	= "Jmp",
	[INTEL_PT_OP_LOOP]	= "Loop",
	[INTEL_PT_OP_IRET]	= "IRet",
	[INTEL_PT_OP_INT]	= "Int",
	[INTEL_PT_OP_SYSCALL]	= "Syscall",
	[INTEL_PT_OP_SYSRET]	= "Sysret",
	[INTEL_PT_OP_VMENTRY]	= "VMentry",
पूर्ण;

स्थिर अक्षर *पूर्णांकel_pt_insn_name(क्रमागत पूर्णांकel_pt_insn_op op)
अणु
	वापस branch_name[op];
पूर्ण

पूर्णांक पूर्णांकel_pt_insn_desc(स्थिर काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn, अक्षर *buf,
		       माप_प्रकार buf_len)
अणु
	चयन (पूर्णांकel_pt_insn->branch) अणु
	हाल INTEL_PT_BR_CONDITIONAL:
	हाल INTEL_PT_BR_UNCONDITIONAL:
		वापस snम_लिखो(buf, buf_len, "%s %s%d",
				पूर्णांकel_pt_insn_name(पूर्णांकel_pt_insn->op),
				पूर्णांकel_pt_insn->rel > 0 ? "+" : "",
				पूर्णांकel_pt_insn->rel);
	हाल INTEL_PT_BR_NO_BRANCH:
	हाल INTEL_PT_BR_INसूचीECT:
		वापस snम_लिखो(buf, buf_len, "%s",
				पूर्णांकel_pt_insn_name(पूर्णांकel_pt_insn->op));
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_pt_insn_type(क्रमागत पूर्णांकel_pt_insn_op op)
अणु
	चयन (op) अणु
	हाल INTEL_PT_OP_OTHER:
		वापस 0;
	हाल INTEL_PT_OP_CALL:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL;
	हाल INTEL_PT_OP_RET:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN;
	हाल INTEL_PT_OP_JCC:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CONDITIONAL;
	हाल INTEL_PT_OP_JMP:
		वापस PERF_IP_FLAG_BRANCH;
	हाल INTEL_PT_OP_LOOP:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CONDITIONAL;
	हाल INTEL_PT_OP_IRET:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN |
		       PERF_IP_FLAG_INTERRUPT;
	हाल INTEL_PT_OP_INT:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL |
		       PERF_IP_FLAG_INTERRUPT;
	हाल INTEL_PT_OP_SYSCALL:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL |
		       PERF_IP_FLAG_SYSCALLRET;
	हाल INTEL_PT_OP_SYSRET:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN |
		       PERF_IP_FLAG_SYSCALLRET;
	हाल INTEL_PT_OP_VMENTRY:
		वापस PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL |
		       PERF_IP_FLAG_VMENTRY;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
