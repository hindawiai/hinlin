<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AMD Encrypted Register State Support
 *
 * Author: Joerg Roedel <jroedel@suse.de>
 *
 * This file is not compiled stand-alone. It contains code shared
 * between the pre-decompression boot code and the running Linux kernel
 * and is included directly पूर्णांकo both code-bases.
 */

#अगर_अघोषित __BOOT_COMPRESSED
#घोषणा error(v)	pr_err(v)
#घोषणा has_cpuflag(f)	boot_cpu_has(f)
#पूर्ण_अगर

अटल bool __init sev_es_check_cpu_features(व्योम)
अणु
	अगर (!has_cpuflag(X86_FEATURE_RDRAND)) अणु
		error("RDRAND instruction not supported - no trusted source of randomness available\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम __noवापस sev_es_terminate(अचिन्हित पूर्णांक reason)
अणु
	u64 val = GHCB_MSR_TERM_REQ;

	/*
	 * Tell the hypervisor what went wrong - only reason-set 0 is
	 * currently supported.
	 */
	val |= GHCB_SEV_TERM_REASON(0, reason);

	/* Request Guest Termination from Hypvervisor */
	sev_es_wr_ghcb_msr(val);
	VMGEXIT();

	जबतक (true)
		यंत्र अस्थिर("hlt\n" : : : "memory");
पूर्ण

अटल bool sev_es_negotiate_protocol(व्योम)
अणु
	u64 val;

	/* Do the GHCB protocol version negotiation */
	sev_es_wr_ghcb_msr(GHCB_MSR_SEV_INFO_REQ);
	VMGEXIT();
	val = sev_es_rd_ghcb_msr();

	अगर (GHCB_MSR_INFO(val) != GHCB_MSR_SEV_INFO_RESP)
		वापस false;

	अगर (GHCB_MSR_PROTO_MAX(val) < GHCB_PROTO_OUR ||
	    GHCB_MSR_PROTO_MIN(val) > GHCB_PROTO_OUR)
		वापस false;

	वापस true;
पूर्ण

अटल __always_अंतरभूत व्योम vc_ghcb_invalidate(काष्ठा ghcb *ghcb)
अणु
	ghcb->save.sw_निकास_code = 0;
	स_रखो(ghcb->save.valid_biपंचांगap, 0, माप(ghcb->save.valid_biपंचांगap));
पूर्ण

अटल bool vc_decoding_needed(अचिन्हित दीर्घ निकास_code)
अणु
	/* Exceptions करोn't require to decode the inकाष्ठाion */
	वापस !(निकास_code >= SVM_EXIT_EXCP_BASE &&
		 निकास_code <= SVM_EXIT_LAST_EXCP);
पूर्ण

अटल क्रमागत es_result vc_init_em_ctxt(काष्ठा es_em_ctxt *ctxt,
				      काष्ठा pt_regs *regs,
				      अचिन्हित दीर्घ निकास_code)
अणु
	क्रमागत es_result ret = ES_OK;

	स_रखो(ctxt, 0, माप(*ctxt));
	ctxt->regs = regs;

	अगर (vc_decoding_needed(निकास_code))
		ret = vc_decode_insn(ctxt);

	वापस ret;
पूर्ण

अटल व्योम vc_finish_insn(काष्ठा es_em_ctxt *ctxt)
अणु
	ctxt->regs->ip += ctxt->insn.length;
पूर्ण

अटल क्रमागत es_result sev_es_ghcb_hv_call(काष्ठा ghcb *ghcb,
					  काष्ठा es_em_ctxt *ctxt,
					  u64 निकास_code, u64 निकास_info_1,
					  u64 निकास_info_2)
अणु
	क्रमागत es_result ret;

	/* Fill in protocol and क्रमmat specअगरiers */
	ghcb->protocol_version = GHCB_PROTOCOL_MAX;
	ghcb->ghcb_usage       = GHCB_DEFAULT_USAGE;

	ghcb_set_sw_निकास_code(ghcb, निकास_code);
	ghcb_set_sw_निकास_info_1(ghcb, निकास_info_1);
	ghcb_set_sw_निकास_info_2(ghcb, निकास_info_2);

	sev_es_wr_ghcb_msr(__pa(ghcb));
	VMGEXIT();

	अगर ((ghcb->save.sw_निकास_info_1 & 0xffffffff) == 1) अणु
		u64 info = ghcb->save.sw_निकास_info_2;
		अचिन्हित दीर्घ v;

		info = ghcb->save.sw_निकास_info_2;
		v = info & SVM_EVTINJ_VEC_MASK;

		/* Check अगर exception inक्रमmation from hypervisor is sane. */
		अगर ((info & SVM_EVTINJ_VALID) &&
		    ((v == X86_TRAP_GP) || (v == X86_TRAP_UD)) &&
		    ((info & SVM_EVTINJ_TYPE_MASK) == SVM_EVTINJ_TYPE_EXEPT)) अणु
			ctxt->fi.vector = v;
			अगर (info & SVM_EVTINJ_VALID_ERR)
				ctxt->fi.error_code = info >> 32;
			ret = ES_EXCEPTION;
		पूर्ण अन्यथा अणु
			ret = ES_VMM_ERROR;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ES_OK;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Boot VC Handler - This is the first VC handler during boot, there is no GHCB
 * page yet, so it only supports the MSR based communication with the
 * hypervisor and only the CPUID निकास-code.
 */
व्योम __init करो_vc_no_ghcb(काष्ठा pt_regs *regs, अचिन्हित दीर्घ निकास_code)
अणु
	अचिन्हित पूर्णांक fn = lower_bits(regs->ax, 32);
	अचिन्हित दीर्घ val;

	/* Only CPUID is supported via MSR protocol */
	अगर (निकास_code != SVM_EXIT_CPUID)
		जाओ fail;

	sev_es_wr_ghcb_msr(GHCB_CPUID_REQ(fn, GHCB_CPUID_REQ_EAX));
	VMGEXIT();
	val = sev_es_rd_ghcb_msr();
	अगर (GHCB_RESP_CODE(val) != GHCB_MSR_CPUID_RESP)
		जाओ fail;
	regs->ax = val >> 32;

	sev_es_wr_ghcb_msr(GHCB_CPUID_REQ(fn, GHCB_CPUID_REQ_EBX));
	VMGEXIT();
	val = sev_es_rd_ghcb_msr();
	अगर (GHCB_RESP_CODE(val) != GHCB_MSR_CPUID_RESP)
		जाओ fail;
	regs->bx = val >> 32;

	sev_es_wr_ghcb_msr(GHCB_CPUID_REQ(fn, GHCB_CPUID_REQ_ECX));
	VMGEXIT();
	val = sev_es_rd_ghcb_msr();
	अगर (GHCB_RESP_CODE(val) != GHCB_MSR_CPUID_RESP)
		जाओ fail;
	regs->cx = val >> 32;

	sev_es_wr_ghcb_msr(GHCB_CPUID_REQ(fn, GHCB_CPUID_REQ_EDX));
	VMGEXIT();
	val = sev_es_rd_ghcb_msr();
	अगर (GHCB_RESP_CODE(val) != GHCB_MSR_CPUID_RESP)
		जाओ fail;
	regs->dx = val >> 32;

	/*
	 * This is a VC handler and the #VC is only उठाओd when SEV-ES is
	 * active, which means SEV must be active too. Do sanity checks on the
	 * CPUID results to make sure the hypervisor करोes not trick the kernel
	 * पूर्णांकo the no-sev path. This could map sensitive data unencrypted and
	 * make it accessible to the hypervisor.
	 *
	 * In particular, check क्रम:
	 *	- Availability of CPUID leaf 0x8000001f
	 *	- SEV CPUID bit.
	 *
	 * The hypervisor might still report the wrong C-bit position, but this
	 * can't be checked here.
	 */

	अगर (fn == 0x80000000 && (regs->ax < 0x8000001f))
		/* SEV leaf check */
		जाओ fail;
	अन्यथा अगर ((fn == 0x8000001f && !(regs->ax & BIT(1))))
		/* SEV bit */
		जाओ fail;

	/* Skip over the CPUID two-byte opcode */
	regs->ip += 2;

	वापस;

fail:
	/* Terminate the guest */
	sev_es_terminate(GHCB_SEV_ES_REASON_GENERAL_REQUEST);
पूर्ण

अटल क्रमागत es_result vc_insn_string_पढ़ो(काष्ठा es_em_ctxt *ctxt,
					  व्योम *src, अक्षर *buf,
					  अचिन्हित पूर्णांक data_size,
					  अचिन्हित पूर्णांक count,
					  bool backwards)
अणु
	पूर्णांक i, b = backwards ? -1 : 1;
	क्रमागत es_result ret = ES_OK;

	क्रम (i = 0; i < count; i++) अणु
		व्योम *s = src + (i * data_size * b);
		अक्षर *d = buf + (i * data_size);

		ret = vc_पढ़ो_mem(ctxt, s, d, data_size);
		अगर (ret != ES_OK)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत es_result vc_insn_string_ग_लिखो(काष्ठा es_em_ctxt *ctxt,
					   व्योम *dst, अक्षर *buf,
					   अचिन्हित पूर्णांक data_size,
					   अचिन्हित पूर्णांक count,
					   bool backwards)
अणु
	पूर्णांक i, s = backwards ? -1 : 1;
	क्रमागत es_result ret = ES_OK;

	क्रम (i = 0; i < count; i++) अणु
		व्योम *d = dst + (i * data_size * s);
		अक्षर *b = buf + (i * data_size);

		ret = vc_ग_लिखो_mem(ctxt, d, b, data_size);
		अगर (ret != ES_OK)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा IOIO_TYPE_STR  BIT(2)
#घोषणा IOIO_TYPE_IN   1
#घोषणा IOIO_TYPE_INS  (IOIO_TYPE_IN | IOIO_TYPE_STR)
#घोषणा IOIO_TYPE_OUT  0
#घोषणा IOIO_TYPE_OUTS (IOIO_TYPE_OUT | IOIO_TYPE_STR)

#घोषणा IOIO_REP       BIT(3)

#घोषणा IOIO_ADDR_64   BIT(9)
#घोषणा IOIO_ADDR_32   BIT(8)
#घोषणा IOIO_ADDR_16   BIT(7)

#घोषणा IOIO_DATA_32   BIT(6)
#घोषणा IOIO_DATA_16   BIT(5)
#घोषणा IOIO_DATA_8    BIT(4)

#घोषणा IOIO_SEG_ES    (0 << 10)
#घोषणा IOIO_SEG_DS    (3 << 10)

अटल क्रमागत es_result vc_ioio_निकासinfo(काष्ठा es_em_ctxt *ctxt, u64 *निकासinfo)
अणु
	काष्ठा insn *insn = &ctxt->insn;
	*निकासinfo = 0;

	चयन (insn->opcode.bytes[0]) अणु
	/* INS opcodes */
	हाल 0x6c:
	हाल 0x6d:
		*निकासinfo |= IOIO_TYPE_INS;
		*निकासinfo |= IOIO_SEG_ES;
		*निकासinfo |= (ctxt->regs->dx & 0xffff) << 16;
		अवरोध;

	/* OUTS opcodes */
	हाल 0x6e:
	हाल 0x6f:
		*निकासinfo |= IOIO_TYPE_OUTS;
		*निकासinfo |= IOIO_SEG_DS;
		*निकासinfo |= (ctxt->regs->dx & 0xffff) << 16;
		अवरोध;

	/* IN immediate opcodes */
	हाल 0xe4:
	हाल 0xe5:
		*निकासinfo |= IOIO_TYPE_IN;
		*निकासinfo |= (u8)insn->immediate.value << 16;
		अवरोध;

	/* OUT immediate opcodes */
	हाल 0xe6:
	हाल 0xe7:
		*निकासinfo |= IOIO_TYPE_OUT;
		*निकासinfo |= (u8)insn->immediate.value << 16;
		अवरोध;

	/* IN रेजिस्टर opcodes */
	हाल 0xec:
	हाल 0xed:
		*निकासinfo |= IOIO_TYPE_IN;
		*निकासinfo |= (ctxt->regs->dx & 0xffff) << 16;
		अवरोध;

	/* OUT रेजिस्टर opcodes */
	हाल 0xee:
	हाल 0xef:
		*निकासinfo |= IOIO_TYPE_OUT;
		*निकासinfo |= (ctxt->regs->dx & 0xffff) << 16;
		अवरोध;

	शेष:
		वापस ES_DECODE_FAILED;
	पूर्ण

	चयन (insn->opcode.bytes[0]) अणु
	हाल 0x6c:
	हाल 0x6e:
	हाल 0xe4:
	हाल 0xe6:
	हाल 0xec:
	हाल 0xee:
		/* Single byte opcodes */
		*निकासinfo |= IOIO_DATA_8;
		अवरोध;
	शेष:
		/* Length determined by inकाष्ठाion parsing */
		*निकासinfo |= (insn->opnd_bytes == 2) ? IOIO_DATA_16
						     : IOIO_DATA_32;
	पूर्ण
	चयन (insn->addr_bytes) अणु
	हाल 2:
		*निकासinfo |= IOIO_ADDR_16;
		अवरोध;
	हाल 4:
		*निकासinfo |= IOIO_ADDR_32;
		अवरोध;
	हाल 8:
		*निकासinfo |= IOIO_ADDR_64;
		अवरोध;
	पूर्ण

	अगर (insn_has_rep_prefix(insn))
		*निकासinfo |= IOIO_REP;

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_ioio(काष्ठा ghcb *ghcb, काष्ठा es_em_ctxt *ctxt)
अणु
	काष्ठा pt_regs *regs = ctxt->regs;
	u64 निकास_info_1, निकास_info_2;
	क्रमागत es_result ret;

	ret = vc_ioio_निकासinfo(ctxt, &निकास_info_1);
	अगर (ret != ES_OK)
		वापस ret;

	अगर (निकास_info_1 & IOIO_TYPE_STR) अणु

		/* (REP) INS/OUTS */

		bool df = ((regs->flags & X86_EFLAGS_DF) == X86_EFLAGS_DF);
		अचिन्हित पूर्णांक io_bytes, निकास_bytes;
		अचिन्हित पूर्णांक ghcb_count, op_count;
		अचिन्हित दीर्घ es_base;
		u64 sw_scratch;

		/*
		 * For the string variants with rep prefix the amount of in/out
		 * operations per #VC exception is limited so that the kernel
		 * has a chance to take पूर्णांकerrupts and re-schedule जबतक the
		 * inकाष्ठाion is emulated.
		 */
		io_bytes   = (निकास_info_1 >> 4) & 0x7;
		ghcb_count = माप(ghcb->shared_buffer) / io_bytes;

		op_count    = (निकास_info_1 & IOIO_REP) ? regs->cx : 1;
		निकास_info_2 = min(op_count, ghcb_count);
		निकास_bytes  = निकास_info_2 * io_bytes;

		es_base = insn_get_seg_base(ctxt->regs, INAT_SEG_REG_ES);

		/* Read bytes of OUTS पूर्णांकo the shared buffer */
		अगर (!(निकास_info_1 & IOIO_TYPE_IN)) अणु
			ret = vc_insn_string_पढ़ो(ctxt,
					       (व्योम *)(es_base + regs->si),
					       ghcb->shared_buffer, io_bytes,
					       निकास_info_2, df);
			अगर (ret)
				वापस ret;
		पूर्ण

		/*
		 * Issue an VMGEXIT to the HV to consume the bytes from the
		 * shared buffer or to have it ग_लिखो them पूर्णांकo the shared buffer
		 * depending on the inकाष्ठाion: OUTS or INS.
		 */
		sw_scratch = __pa(ghcb) + दुरत्व(काष्ठा ghcb, shared_buffer);
		ghcb_set_sw_scratch(ghcb, sw_scratch);
		ret = sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_IOIO,
					  निकास_info_1, निकास_info_2);
		अगर (ret != ES_OK)
			वापस ret;

		/* Read bytes from shared buffer पूर्णांकo the guest's destination. */
		अगर (निकास_info_1 & IOIO_TYPE_IN) अणु
			ret = vc_insn_string_ग_लिखो(ctxt,
						   (व्योम *)(es_base + regs->di),
						   ghcb->shared_buffer, io_bytes,
						   निकास_info_2, df);
			अगर (ret)
				वापस ret;

			अगर (df)
				regs->di -= निकास_bytes;
			अन्यथा
				regs->di += निकास_bytes;
		पूर्ण अन्यथा अणु
			अगर (df)
				regs->si -= निकास_bytes;
			अन्यथा
				regs->si += निकास_bytes;
		पूर्ण

		अगर (निकास_info_1 & IOIO_REP)
			regs->cx -= निकास_info_2;

		ret = regs->cx ? ES_RETRY : ES_OK;

	पूर्ण अन्यथा अणु

		/* IN/OUT पूर्णांकo/from rAX */

		पूर्णांक bits = (निकास_info_1 & 0x70) >> 1;
		u64 rax = 0;

		अगर (!(निकास_info_1 & IOIO_TYPE_IN))
			rax = lower_bits(regs->ax, bits);

		ghcb_set_rax(ghcb, rax);

		ret = sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_IOIO, निकास_info_1, 0);
		अगर (ret != ES_OK)
			वापस ret;

		अगर (निकास_info_1 & IOIO_TYPE_IN) अणु
			अगर (!ghcb_rax_is_valid(ghcb))
				वापस ES_VMM_ERROR;
			regs->ax = lower_bits(ghcb->save.rax, bits);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत es_result vc_handle_cpuid(काष्ठा ghcb *ghcb,
				      काष्ठा es_em_ctxt *ctxt)
अणु
	काष्ठा pt_regs *regs = ctxt->regs;
	u32 cr4 = native_पढ़ो_cr4();
	क्रमागत es_result ret;

	ghcb_set_rax(ghcb, regs->ax);
	ghcb_set_rcx(ghcb, regs->cx);

	अगर (cr4 & X86_CR4_OSXSAVE)
		/* Safe to पढ़ो xcr0 */
		ghcb_set_xcr0(ghcb, xgetbv(XCR_XFEATURE_ENABLED_MASK));
	अन्यथा
		/* xgetbv will cause #GP - use reset value क्रम xcr0 */
		ghcb_set_xcr0(ghcb, 1);

	ret = sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_CPUID, 0, 0);
	अगर (ret != ES_OK)
		वापस ret;

	अगर (!(ghcb_rax_is_valid(ghcb) &&
	      ghcb_rbx_is_valid(ghcb) &&
	      ghcb_rcx_is_valid(ghcb) &&
	      ghcb_rdx_is_valid(ghcb)))
		वापस ES_VMM_ERROR;

	regs->ax = ghcb->save.rax;
	regs->bx = ghcb->save.rbx;
	regs->cx = ghcb->save.rcx;
	regs->dx = ghcb->save.rdx;

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_rdtsc(काष्ठा ghcb *ghcb,
				      काष्ठा es_em_ctxt *ctxt,
				      अचिन्हित दीर्घ निकास_code)
अणु
	bool rdtscp = (निकास_code == SVM_EXIT_RDTSCP);
	क्रमागत es_result ret;

	ret = sev_es_ghcb_hv_call(ghcb, ctxt, निकास_code, 0, 0);
	अगर (ret != ES_OK)
		वापस ret;

	अगर (!(ghcb_rax_is_valid(ghcb) && ghcb_rdx_is_valid(ghcb) &&
	     (!rdtscp || ghcb_rcx_is_valid(ghcb))))
		वापस ES_VMM_ERROR;

	ctxt->regs->ax = ghcb->save.rax;
	ctxt->regs->dx = ghcb->save.rdx;
	अगर (rdtscp)
		ctxt->regs->cx = ghcb->save.rcx;

	वापस ES_OK;
पूर्ण
