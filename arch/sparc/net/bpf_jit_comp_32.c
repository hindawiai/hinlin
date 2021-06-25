<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/moduleloader.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/cache.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/ptrace.h>

#समावेश "bpf_jit_32.h"

अटल अंतरभूत bool is_simm13(अचिन्हित पूर्णांक value)
अणु
	वापस value + 0x1000 < 0x2000;
पूर्ण

#घोषणा SEEN_DATAREF 1 /* might call बाह्यal helpers */
#घोषणा SEEN_XREG    2 /* ebx is used */
#घोषणा SEEN_MEM     4 /* use mem[] क्रम temporary storage */

#घोषणा S13(X)		((X) & 0x1fff)
#घोषणा IMMED		0x00002000
#घोषणा RD(X)		((X) << 25)
#घोषणा RS1(X)		((X) << 14)
#घोषणा RS2(X)		((X))
#घोषणा OP(X)		((X) << 30)
#घोषणा OP2(X)		((X) << 22)
#घोषणा OP3(X)		((X) << 19)
#घोषणा COND(X)		((X) << 25)
#घोषणा F1(X)		OP(X)
#घोषणा F2(X, Y)	(OP(X) | OP2(Y))
#घोषणा F3(X, Y)	(OP(X) | OP3(Y))

#घोषणा CONDN		COND(0x0)
#घोषणा CONDE		COND(0x1)
#घोषणा CONDLE		COND(0x2)
#घोषणा CONDL		COND(0x3)
#घोषणा CONDLEU		COND(0x4)
#घोषणा CONDCS		COND(0x5)
#घोषणा CONDNEG		COND(0x6)
#घोषणा CONDVC		COND(0x7)
#घोषणा CONDA		COND(0x8)
#घोषणा CONDNE		COND(0x9)
#घोषणा CONDG		COND(0xa)
#घोषणा CONDGE		COND(0xb)
#घोषणा CONDGU		COND(0xc)
#घोषणा CONDCC		COND(0xd)
#घोषणा CONDPOS		COND(0xe)
#घोषणा CONDVS		COND(0xf)

#घोषणा CONDGEU		CONDCC
#घोषणा CONDLU		CONDCS

#घोषणा WDISP22(X)	(((X) >> 2) & 0x3fffff)

#घोषणा BA		(F2(0, 2) | CONDA)
#घोषणा BGU		(F2(0, 2) | CONDGU)
#घोषणा BLEU		(F2(0, 2) | CONDLEU)
#घोषणा BGEU		(F2(0, 2) | CONDGEU)
#घोषणा BLU		(F2(0, 2) | CONDLU)
#घोषणा BE		(F2(0, 2) | CONDE)
#घोषणा BNE		(F2(0, 2) | CONDNE)

#घोषणा BE_PTR		BE

#घोषणा SETHI(K, REG)	\
	(F2(0, 0x4) | RD(REG) | (((K) >> 10) & 0x3fffff))
#घोषणा OR_LO(K, REG)	\
	(F3(2, 0x02) | IMMED | RS1(REG) | ((K) & 0x3ff) | RD(REG))

#घोषणा ADD		F3(2, 0x00)
#घोषणा AND		F3(2, 0x01)
#घोषणा ANDCC		F3(2, 0x11)
#घोषणा OR		F3(2, 0x02)
#घोषणा XOR		F3(2, 0x03)
#घोषणा SUB		F3(2, 0x04)
#घोषणा SUBCC		F3(2, 0x14)
#घोषणा MUL		F3(2, 0x0a)	/* umul */
#घोषणा DIV		F3(2, 0x0e)	/* uभाग */
#घोषणा SLL		F3(2, 0x25)
#घोषणा SRL		F3(2, 0x26)
#घोषणा JMPL		F3(2, 0x38)
#घोषणा CALL		F1(1)
#घोषणा BR		F2(0, 0x01)
#घोषणा RD_Y		F3(2, 0x28)
#घोषणा WR_Y		F3(2, 0x30)

#घोषणा LD32		F3(3, 0x00)
#घोषणा LD8		F3(3, 0x01)
#घोषणा LD16		F3(3, 0x02)
#घोषणा LD64		F3(3, 0x0b)
#घोषणा ST32		F3(3, 0x04)

#घोषणा LDPTR		LD32
#घोषणा BASE_STACKFRAME	96

#घोषणा LD32I		(LD32 | IMMED)
#घोषणा LD8I		(LD8 | IMMED)
#घोषणा LD16I		(LD16 | IMMED)
#घोषणा LD64I		(LD64 | IMMED)
#घोषणा LDPTRI		(LDPTR | IMMED)
#घोषणा ST32I		(ST32 | IMMED)

#घोषणा emit_nop()		\
करो अणु				\
	*prog++ = SETHI(0, G0);	\
पूर्ण जबतक (0)

#घोषणा emit_neg()					\
करो अणु	/* sub %g0, r_A, r_A */				\
	*prog++ = SUB | RS1(G0) | RS2(r_A) | RD(r_A);	\
पूर्ण जबतक (0)

#घोषणा emit_reg_move(FROM, TO)				\
करो अणु	/* or %g0, FROM, TO */				\
	*prog++ = OR | RS1(G0) | RS2(FROM) | RD(TO);	\
पूर्ण जबतक (0)

#घोषणा emit_clear(REG)					\
करो अणु	/* or %g0, %g0, REG */				\
	*prog++ = OR | RS1(G0) | RS2(G0) | RD(REG);	\
पूर्ण जबतक (0)

#घोषणा emit_set_स्थिर(K, REG)					\
करो अणु	/* sethi %hi(K), REG */					\
	*prog++ = SETHI(K, REG);				\
	/* or REG, %lo(K), REG */				\
	*prog++ = OR_LO(K, REG);				\
पूर्ण जबतक (0)

	/* Emit
	 *
	 *	OP	r_A, r_X, r_A
	 */
#घोषणा emit_alu_X(OPCODE)					\
करो अणु								\
	seen |= SEEN_XREG;					\
	*prog++ = OPCODE | RS1(r_A) | RS2(r_X) | RD(r_A);	\
पूर्ण जबतक (0)

	/* Emit either:
	 *
	 *	OP	r_A, K, r_A
	 *
	 * or
	 *
	 *	sethi	%hi(K), r_TMP
	 *	or	r_TMP, %lo(K), r_TMP
	 *	OP	r_A, r_TMP, r_A
	 *
	 * depending upon whether K fits in a चिन्हित 13-bit
	 * immediate inकाष्ठाion field.  Emit nothing अगर K
	 * is zero.
	 */
#घोषणा emit_alu_K(OPCODE, K)					\
करो अणु								\
	अगर (K || OPCODE == AND || OPCODE == MUL) अणु		\
		अचिन्हित पूर्णांक _insn = OPCODE;			\
		_insn |= RS1(r_A) | RD(r_A);			\
		अगर (is_simm13(K)) अणु				\
			*prog++ = _insn | IMMED | S13(K);	\
		पूर्ण अन्यथा अणु					\
			emit_set_स्थिर(K, r_TMP);		\
			*prog++ = _insn | RS2(r_TMP);		\
		पूर्ण						\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा emit_loadimm(K, DEST)						\
करो अणु									\
	अगर (is_simm13(K)) अणु						\
		/* or %g0, K, DEST */					\
		*prog++ = OR | IMMED | RS1(G0) | S13(K) | RD(DEST);	\
	पूर्ण अन्यथा अणु							\
		emit_set_स्थिर(K, DEST);				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा emit_loadptr(BASE, STRUCT, FIELD, DEST)				\
करो अणु	अचिन्हित पूर्णांक _off = दुरत्व(STRUCT, FIELD);			\
	BUILD_BUG_ON(माप_field(STRUCT, FIELD) != माप(व्योम *));	\
	*prog++ = LDPTRI | RS1(BASE) | S13(_off) | RD(DEST);		\
पूर्ण जबतक (0)

#घोषणा emit_load32(BASE, STRUCT, FIELD, DEST)				\
करो अणु	अचिन्हित पूर्णांक _off = दुरत्व(STRUCT, FIELD);			\
	BUILD_BUG_ON(माप_field(STRUCT, FIELD) != माप(u32));	\
	*prog++ = LD32I | RS1(BASE) | S13(_off) | RD(DEST);		\
पूर्ण जबतक (0)

#घोषणा emit_load16(BASE, STRUCT, FIELD, DEST)				\
करो अणु	अचिन्हित पूर्णांक _off = दुरत्व(STRUCT, FIELD);			\
	BUILD_BUG_ON(माप_field(STRUCT, FIELD) != माप(u16));	\
	*prog++ = LD16I | RS1(BASE) | S13(_off) | RD(DEST);		\
पूर्ण जबतक (0)

#घोषणा __emit_load8(BASE, STRUCT, FIELD, DEST)				\
करो अणु	अचिन्हित पूर्णांक _off = दुरत्व(STRUCT, FIELD);			\
	*prog++ = LD8I | RS1(BASE) | S13(_off) | RD(DEST);		\
पूर्ण जबतक (0)

#घोषणा emit_load8(BASE, STRUCT, FIELD, DEST)				\
करो अणु	BUILD_BUG_ON(माप_field(STRUCT, FIELD) != माप(u8));	\
	__emit_load8(BASE, STRUCT, FIELD, DEST);			\
पूर्ण जबतक (0)

#घोषणा BIAS (-4)

#घोषणा emit_ldmem(OFF, DEST)						\
करो अणु	*prog++ = LD32I | RS1(SP) | S13(BIAS - (OFF)) | RD(DEST);	\
पूर्ण जबतक (0)

#घोषणा emit_sपंचांगem(OFF, SRC)						\
करो अणु	*prog++ = ST32I | RS1(SP) | S13(BIAS - (OFF)) | RD(SRC);	\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_SMP
#घोषणा emit_load_cpu(REG)						\
	emit_load32(G6, काष्ठा thपढ़ो_info, cpu, REG)
#अन्यथा
#घोषणा emit_load_cpu(REG)	emit_clear(REG)
#पूर्ण_अगर

#घोषणा emit_skb_loadptr(FIELD, DEST) \
	emit_loadptr(r_SKB, काष्ठा sk_buff, FIELD, DEST)
#घोषणा emit_skb_load32(FIELD, DEST) \
	emit_load32(r_SKB, काष्ठा sk_buff, FIELD, DEST)
#घोषणा emit_skb_load16(FIELD, DEST) \
	emit_load16(r_SKB, काष्ठा sk_buff, FIELD, DEST)
#घोषणा __emit_skb_load8(FIELD, DEST) \
	__emit_load8(r_SKB, काष्ठा sk_buff, FIELD, DEST)
#घोषणा emit_skb_load8(FIELD, DEST) \
	emit_load8(r_SKB, काष्ठा sk_buff, FIELD, DEST)

#घोषणा emit_jmpl(BASE, IMM_OFF, LREG) \
	*prog++ = (JMPL | IMMED | RS1(BASE) | S13(IMM_OFF) | RD(LREG))

#घोषणा emit_call(FUNC)					\
करो अणु	व्योम *_here = image + addrs[i] - 8;		\
	अचिन्हित पूर्णांक _off = (व्योम *)(FUNC) - _here;	\
	*prog++ = CALL | (((_off) >> 2) & 0x3fffffff);	\
	emit_nop();					\
पूर्ण जबतक (0)

#घोषणा emit_branch(BR_OPC, DEST)			\
करो अणु	अचिन्हित पूर्णांक _here = addrs[i] - 8;		\
	*prog++ = BR_OPC | WDISP22((DEST) - _here);	\
पूर्ण जबतक (0)

#घोषणा emit_branch_off(BR_OPC, OFF)			\
करो अणु	*prog++ = BR_OPC | WDISP22(OFF);		\
पूर्ण जबतक (0)

#घोषणा emit_jump(DEST)		emit_branch(BA, DEST)

#घोषणा emit_पढ़ो_y(REG)	*prog++ = RD_Y | RD(REG)
#घोषणा emit_ग_लिखो_y(REG)	*prog++ = WR_Y | IMMED | RS1(REG) | S13(0)

#घोषणा emit_cmp(R1, R2) \
	*prog++ = (SUBCC | RS1(R1) | RS2(R2) | RD(G0))

#घोषणा emit_cmpi(R1, IMM) \
	*prog++ = (SUBCC | IMMED | RS1(R1) | S13(IMM) | RD(G0));

#घोषणा emit_btst(R1, R2) \
	*prog++ = (ANDCC | RS1(R1) | RS2(R2) | RD(G0))

#घोषणा emit_btsti(R1, IMM) \
	*prog++ = (ANDCC | IMMED | RS1(R1) | S13(IMM) | RD(G0));

#घोषणा emit_sub(R1, R2, R3) \
	*prog++ = (SUB | RS1(R1) | RS2(R2) | RD(R3))

#घोषणा emit_subi(R1, IMM, R3) \
	*prog++ = (SUB | IMMED | RS1(R1) | S13(IMM) | RD(R3))

#घोषणा emit_add(R1, R2, R3) \
	*prog++ = (ADD | RS1(R1) | RS2(R2) | RD(R3))

#घोषणा emit_addi(R1, IMM, R3) \
	*prog++ = (ADD | IMMED | RS1(R1) | S13(IMM) | RD(R3))

#घोषणा emit_and(R1, R2, R3) \
	*prog++ = (AND | RS1(R1) | RS2(R2) | RD(R3))

#घोषणा emit_andi(R1, IMM, R3) \
	*prog++ = (AND | IMMED | RS1(R1) | S13(IMM) | RD(R3))

#घोषणा emit_alloc_stack(SZ) \
	*prog++ = (SUB | IMMED | RS1(SP) | S13(SZ) | RD(SP))

#घोषणा emit_release_stack(SZ) \
	*prog++ = (ADD | IMMED | RS1(SP) | S13(SZ) | RD(SP))

/* A note about branch offset calculations.  The addrs[] array,
 * indexed by BPF inकाष्ठाion, records the address after all the
 * sparc inकाष्ठाions emitted क्रम that BPF inकाष्ठाion.
 *
 * The most common हाल is to emit a branch at the end of such
 * a code sequence.  So this would be two inकाष्ठाions, the
 * branch and it's delay slot.
 *
 * Thereक्रमe by शेष the branch emitters calculate the branch
 * offset field as:
 *
 *	destination - (addrs[i] - 8)
 *
 * This "addrs[i] - 8" is the address of the branch itself or
 * what "." would be in assembler notation.  The "8" part is
 * how we take पूर्णांकo consideration the branch and it's delay
 * slot mentioned above.
 *
 * Someबार we need to emit a branch earlier in the code
 * sequence.  And in these situations we adjust "destination"
 * to accommodate this dअगरference.  For example, अगर we needed
 * to emit a branch (and it's delay slot) right beक्रमe the
 * final inकाष्ठाion emitted क्रम a BPF opcode, we'd use
 * "destination + 4" instead of just plain "destination" above.
 *
 * This is why you see all of these funny emit_branch() and
 * emit_jump() calls with adjusted offsets.
 */

व्योम bpf_jit_compile(काष्ठा bpf_prog *fp)
अणु
	अचिन्हित पूर्णांक cleanup_addr, proglen, oldproglen = 0;
	u32 temp[8], *prog, *func, seen = 0, pass;
	स्थिर काष्ठा sock_filter *filter = fp->insns;
	पूर्णांक i, flen = fp->len, pc_ret0 = -1;
	अचिन्हित पूर्णांक *addrs;
	व्योम *image;

	अगर (!bpf_jit_enable)
		वापस;

	addrs = kदो_स्मृति_array(flen, माप(*addrs), GFP_KERNEL);
	अगर (addrs == शून्य)
		वापस;

	/* Beक्रमe first pass, make a rough estimation of addrs[]
	 * each bpf inकाष्ठाion is translated to less than 64 bytes
	 */
	क्रम (proglen = 0, i = 0; i < flen; i++) अणु
		proglen += 64;
		addrs[i] = proglen;
	पूर्ण
	cleanup_addr = proglen; /* epilogue address */
	image = शून्य;
	क्रम (pass = 0; pass < 10; pass++) अणु
		u8 seen_or_pass0 = (pass == 0) ? (SEEN_XREG | SEEN_DATAREF | SEEN_MEM) : seen;

		/* no prologue/epilogue क्रम trivial filters (RET something) */
		proglen = 0;
		prog = temp;

		/* Prologue */
		अगर (seen_or_pass0) अणु
			अगर (seen_or_pass0 & SEEN_MEM) अणु
				अचिन्हित पूर्णांक sz = BASE_STACKFRAME;
				sz += BPF_MEMWORDS * माप(u32);
				emit_alloc_stack(sz);
			पूर्ण

			/* Make sure we करोnt leek kernel memory. */
			अगर (seen_or_pass0 & SEEN_XREG)
				emit_clear(r_X);

			/* If this filter needs to access skb data,
			 * load %o4 and %o5 with:
			 *  %o4 = skb->len - skb->data_len
			 *  %o5 = skb->data
			 * And also back up %o7 पूर्णांकo r_saved_O7 so we can
			 * invoke the stubs using 'call'.
			 */
			अगर (seen_or_pass0 & SEEN_DATAREF) अणु
				emit_load32(r_SKB, काष्ठा sk_buff, len, r_HEADLEN);
				emit_load32(r_SKB, काष्ठा sk_buff, data_len, r_TMP);
				emit_sub(r_HEADLEN, r_TMP, r_HEADLEN);
				emit_loadptr(r_SKB, काष्ठा sk_buff, data, r_SKB_DATA);
			पूर्ण
		पूर्ण
		emit_reg_move(O7, r_saved_O7);

		/* Make sure we करोnt leak kernel inक्रमmation to the user. */
		अगर (bpf_needs_clear_a(&filter[0]))
			emit_clear(r_A); /* A = 0 */

		क्रम (i = 0; i < flen; i++) अणु
			अचिन्हित पूर्णांक K = filter[i].k;
			अचिन्हित पूर्णांक t_offset;
			अचिन्हित पूर्णांक f_offset;
			u32 t_op, f_op;
			u16 code = bpf_anc_helper(&filter[i]);
			पूर्णांक ilen;

			चयन (code) अणु
			हाल BPF_ALU | BPF_ADD | BPF_X:	/* A += X; */
				emit_alu_X(ADD);
				अवरोध;
			हाल BPF_ALU | BPF_ADD | BPF_K:	/* A += K; */
				emit_alu_K(ADD, K);
				अवरोध;
			हाल BPF_ALU | BPF_SUB | BPF_X:	/* A -= X; */
				emit_alu_X(SUB);
				अवरोध;
			हाल BPF_ALU | BPF_SUB | BPF_K:	/* A -= K */
				emit_alu_K(SUB, K);
				अवरोध;
			हाल BPF_ALU | BPF_AND | BPF_X:	/* A &= X */
				emit_alu_X(AND);
				अवरोध;
			हाल BPF_ALU | BPF_AND | BPF_K:	/* A &= K */
				emit_alu_K(AND, K);
				अवरोध;
			हाल BPF_ALU | BPF_OR | BPF_X:	/* A |= X */
				emit_alu_X(OR);
				अवरोध;
			हाल BPF_ALU | BPF_OR | BPF_K:	/* A |= K */
				emit_alu_K(OR, K);
				अवरोध;
			हाल BPF_ANC | SKF_AD_ALU_XOR_X: /* A ^= X; */
			हाल BPF_ALU | BPF_XOR | BPF_X:
				emit_alu_X(XOR);
				अवरोध;
			हाल BPF_ALU | BPF_XOR | BPF_K:	/* A ^= K */
				emit_alu_K(XOR, K);
				अवरोध;
			हाल BPF_ALU | BPF_LSH | BPF_X:	/* A <<= X */
				emit_alu_X(SLL);
				अवरोध;
			हाल BPF_ALU | BPF_LSH | BPF_K:	/* A <<= K */
				emit_alu_K(SLL, K);
				अवरोध;
			हाल BPF_ALU | BPF_RSH | BPF_X:	/* A >>= X */
				emit_alu_X(SRL);
				अवरोध;
			हाल BPF_ALU | BPF_RSH | BPF_K:	/* A >>= K */
				emit_alu_K(SRL, K);
				अवरोध;
			हाल BPF_ALU | BPF_MUL | BPF_X:	/* A *= X; */
				emit_alu_X(MUL);
				अवरोध;
			हाल BPF_ALU | BPF_MUL | BPF_K:	/* A *= K */
				emit_alu_K(MUL, K);
				अवरोध;
			हाल BPF_ALU | BPF_DIV | BPF_K:	/* A /= K with K != 0*/
				अगर (K == 1)
					अवरोध;
				emit_ग_लिखो_y(G0);
				/* The Sparc v8 architecture requires
				 * three inकाष्ठाions between a %y
				 * रेजिस्टर ग_लिखो and the first use.
				 */
				emit_nop();
				emit_nop();
				emit_nop();
				emit_alu_K(DIV, K);
				अवरोध;
			हाल BPF_ALU | BPF_DIV | BPF_X:	/* A /= X; */
				emit_cmpi(r_X, 0);
				अगर (pc_ret0 > 0) अणु
					t_offset = addrs[pc_ret0 - 1];
					emit_branch(BE, t_offset + 20);
					emit_nop(); /* delay slot */
				पूर्ण अन्यथा अणु
					emit_branch_off(BNE, 16);
					emit_nop();
					emit_jump(cleanup_addr + 20);
					emit_clear(r_A);
				पूर्ण
				emit_ग_लिखो_y(G0);
				/* The Sparc v8 architecture requires
				 * three inकाष्ठाions between a %y
				 * रेजिस्टर ग_लिखो and the first use.
				 */
				emit_nop();
				emit_nop();
				emit_nop();
				emit_alu_X(DIV);
				अवरोध;
			हाल BPF_ALU | BPF_NEG:
				emit_neg();
				अवरोध;
			हाल BPF_RET | BPF_K:
				अगर (!K) अणु
					अगर (pc_ret0 == -1)
						pc_ret0 = i;
					emit_clear(r_A);
				पूर्ण अन्यथा अणु
					emit_loadimm(K, r_A);
				पूर्ण
				fallthrough;
			हाल BPF_RET | BPF_A:
				अगर (seen_or_pass0) अणु
					अगर (i != flen - 1) अणु
						emit_jump(cleanup_addr);
						emit_nop();
						अवरोध;
					पूर्ण
					अगर (seen_or_pass0 & SEEN_MEM) अणु
						अचिन्हित पूर्णांक sz = BASE_STACKFRAME;
						sz += BPF_MEMWORDS * माप(u32);
						emit_release_stack(sz);
					पूर्ण
				पूर्ण
				/* jmpl %r_saved_O7 + 8, %g0 */
				emit_jmpl(r_saved_O7, 8, G0);
				emit_reg_move(r_A, O0); /* delay slot */
				अवरोध;
			हाल BPF_MISC | BPF_TAX:
				seen |= SEEN_XREG;
				emit_reg_move(r_A, r_X);
				अवरोध;
			हाल BPF_MISC | BPF_TXA:
				seen |= SEEN_XREG;
				emit_reg_move(r_X, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_CPU:
				emit_load_cpu(r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_PROTOCOL:
				emit_skb_load16(protocol, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_PKTTYPE:
				__emit_skb_load8(__pkt_type_offset, r_A);
				emit_andi(r_A, PKT_TYPE_MAX, r_A);
				emit_alu_K(SRL, 5);
				अवरोध;
			हाल BPF_ANC | SKF_AD_IFINDEX:
				emit_skb_loadptr(dev, r_A);
				emit_cmpi(r_A, 0);
				emit_branch(BE_PTR, cleanup_addr + 4);
				emit_nop();
				emit_load32(r_A, काष्ठा net_device, अगरindex, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_MARK:
				emit_skb_load32(mark, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_QUEUE:
				emit_skb_load16(queue_mapping, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_HATYPE:
				emit_skb_loadptr(dev, r_A);
				emit_cmpi(r_A, 0);
				emit_branch(BE_PTR, cleanup_addr + 4);
				emit_nop();
				emit_load16(r_A, काष्ठा net_device, type, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_RXHASH:
				emit_skb_load32(hash, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_VLAN_TAG:
				emit_skb_load16(vlan_tci, r_A);
				अवरोध;
			हाल BPF_ANC | SKF_AD_VLAN_TAG_PRESENT:
				__emit_skb_load8(__pkt_vlan_present_offset, r_A);
				अगर (PKT_VLAN_PRESENT_BIT)
					emit_alu_K(SRL, PKT_VLAN_PRESENT_BIT);
				अगर (PKT_VLAN_PRESENT_BIT < 7)
					emit_andi(r_A, 1, r_A);
				अवरोध;
			हाल BPF_LD | BPF_W | BPF_LEN:
				emit_skb_load32(len, r_A);
				अवरोध;
			हाल BPF_LDX | BPF_W | BPF_LEN:
				emit_skb_load32(len, r_X);
				अवरोध;
			हाल BPF_LD | BPF_IMM:
				emit_loadimm(K, r_A);
				अवरोध;
			हाल BPF_LDX | BPF_IMM:
				emit_loadimm(K, r_X);
				अवरोध;
			हाल BPF_LD | BPF_MEM:
				seen |= SEEN_MEM;
				emit_ldmem(K * 4, r_A);
				अवरोध;
			हाल BPF_LDX | BPF_MEM:
				seen |= SEEN_MEM | SEEN_XREG;
				emit_ldmem(K * 4, r_X);
				अवरोध;
			हाल BPF_ST:
				seen |= SEEN_MEM;
				emit_sपंचांगem(K * 4, r_A);
				अवरोध;
			हाल BPF_STX:
				seen |= SEEN_MEM | SEEN_XREG;
				emit_sपंचांगem(K * 4, r_X);
				अवरोध;

#घोषणा CHOOSE_LOAD_FUNC(K, func) \
	((पूर्णांक)K < 0 ? ((पूर्णांक)K >= SKF_LL_OFF ? func##_negative_offset : func) : func##_positive_offset)

			हाल BPF_LD | BPF_W | BPF_ABS:
				func = CHOOSE_LOAD_FUNC(K, bpf_jit_load_word);
common_load:			seen |= SEEN_DATAREF;
				emit_loadimm(K, r_OFF);
				emit_call(func);
				अवरोध;
			हाल BPF_LD | BPF_H | BPF_ABS:
				func = CHOOSE_LOAD_FUNC(K, bpf_jit_load_half);
				जाओ common_load;
			हाल BPF_LD | BPF_B | BPF_ABS:
				func = CHOOSE_LOAD_FUNC(K, bpf_jit_load_byte);
				जाओ common_load;
			हाल BPF_LDX | BPF_B | BPF_MSH:
				func = CHOOSE_LOAD_FUNC(K, bpf_jit_load_byte_msh);
				जाओ common_load;
			हाल BPF_LD | BPF_W | BPF_IND:
				func = bpf_jit_load_word;
common_load_ind:		seen |= SEEN_DATAREF | SEEN_XREG;
				अगर (K) अणु
					अगर (is_simm13(K)) अणु
						emit_addi(r_X, K, r_OFF);
					पूर्ण अन्यथा अणु
						emit_loadimm(K, r_TMP);
						emit_add(r_X, r_TMP, r_OFF);
					पूर्ण
				पूर्ण अन्यथा अणु
					emit_reg_move(r_X, r_OFF);
				पूर्ण
				emit_call(func);
				अवरोध;
			हाल BPF_LD | BPF_H | BPF_IND:
				func = bpf_jit_load_half;
				जाओ common_load_ind;
			हाल BPF_LD | BPF_B | BPF_IND:
				func = bpf_jit_load_byte;
				जाओ common_load_ind;
			हाल BPF_JMP | BPF_JA:
				emit_jump(addrs[i + K]);
				emit_nop();
				अवरोध;

#घोषणा COND_SEL(CODE, TOP, FOP)	\
	हाल CODE:			\
		t_op = TOP;		\
		f_op = FOP;		\
		जाओ cond_branch

			COND_SEL(BPF_JMP | BPF_JGT | BPF_K, BGU, BLEU);
			COND_SEL(BPF_JMP | BPF_JGE | BPF_K, BGEU, BLU);
			COND_SEL(BPF_JMP | BPF_JEQ | BPF_K, BE, BNE);
			COND_SEL(BPF_JMP | BPF_JSET | BPF_K, BNE, BE);
			COND_SEL(BPF_JMP | BPF_JGT | BPF_X, BGU, BLEU);
			COND_SEL(BPF_JMP | BPF_JGE | BPF_X, BGEU, BLU);
			COND_SEL(BPF_JMP | BPF_JEQ | BPF_X, BE, BNE);
			COND_SEL(BPF_JMP | BPF_JSET | BPF_X, BNE, BE);

cond_branch:			f_offset = addrs[i + filter[i].jf];
				t_offset = addrs[i + filter[i].jt];

				/* same tarमाला_लो, can aव्योम करोing the test :) */
				अगर (filter[i].jt == filter[i].jf) अणु
					emit_jump(t_offset);
					emit_nop();
					अवरोध;
				पूर्ण

				चयन (code) अणु
				हाल BPF_JMP | BPF_JGT | BPF_X:
				हाल BPF_JMP | BPF_JGE | BPF_X:
				हाल BPF_JMP | BPF_JEQ | BPF_X:
					seen |= SEEN_XREG;
					emit_cmp(r_A, r_X);
					अवरोध;
				हाल BPF_JMP | BPF_JSET | BPF_X:
					seen |= SEEN_XREG;
					emit_btst(r_A, r_X);
					अवरोध;
				हाल BPF_JMP | BPF_JEQ | BPF_K:
				हाल BPF_JMP | BPF_JGT | BPF_K:
				हाल BPF_JMP | BPF_JGE | BPF_K:
					अगर (is_simm13(K)) अणु
						emit_cmpi(r_A, K);
					पूर्ण अन्यथा अणु
						emit_loadimm(K, r_TMP);
						emit_cmp(r_A, r_TMP);
					पूर्ण
					अवरोध;
				हाल BPF_JMP | BPF_JSET | BPF_K:
					अगर (is_simm13(K)) अणु
						emit_btsti(r_A, K);
					पूर्ण अन्यथा अणु
						emit_loadimm(K, r_TMP);
						emit_btst(r_A, r_TMP);
					पूर्ण
					अवरोध;
				पूर्ण
				अगर (filter[i].jt != 0) अणु
					अगर (filter[i].jf)
						t_offset += 8;
					emit_branch(t_op, t_offset);
					emit_nop(); /* delay slot */
					अगर (filter[i].jf) अणु
						emit_jump(f_offset);
						emit_nop();
					पूर्ण
					अवरोध;
				पूर्ण
				emit_branch(f_op, f_offset);
				emit_nop(); /* delay slot */
				अवरोध;

			शेष:
				/* hmm, too complex filter, give up with jit compiler */
				जाओ out;
			पूर्ण
			ilen = (व्योम *) prog - (व्योम *) temp;
			अगर (image) अणु
				अगर (unlikely(proglen + ilen > oldproglen)) अणु
					pr_err("bpb_jit_compile fatal error\n");
					kमुक्त(addrs);
					module_memमुक्त(image);
					वापस;
				पूर्ण
				स_नकल(image + proglen, temp, ilen);
			पूर्ण
			proglen += ilen;
			addrs[i] = proglen;
			prog = temp;
		पूर्ण
		/* last bpf inकाष्ठाion is always a RET :
		 * use it to give the cleanup inकाष्ठाion(s) addr
		 */
		cleanup_addr = proglen - 8; /* jmpl; mov r_A,%o0; */
		अगर (seen_or_pass0 & SEEN_MEM)
			cleanup_addr -= 4; /* add %sp, X, %sp; */

		अगर (image) अणु
			अगर (proglen != oldproglen)
				pr_err("bpb_jit_compile proglen=%u != oldproglen=%u\n",
				       proglen, oldproglen);
			अवरोध;
		पूर्ण
		अगर (proglen == oldproglen) अणु
			image = module_alloc(proglen);
			अगर (!image)
				जाओ out;
		पूर्ण
		oldproglen = proglen;
	पूर्ण

	अगर (bpf_jit_enable > 1)
		bpf_jit_dump(flen, proglen, pass + 1, image);

	अगर (image) अणु
		fp->bpf_func = (व्योम *)image;
		fp->jited = 1;
	पूर्ण
out:
	kमुक्त(addrs);
	वापस;
पूर्ण

व्योम bpf_jit_मुक्त(काष्ठा bpf_prog *fp)
अणु
	अगर (fp->jited)
		module_memमुक्त(fp->bpf_func);

	bpf_prog_unlock_मुक्त(fp);
पूर्ण
