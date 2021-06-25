<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * eBPF JIT compiler
 *
 * Copyright 2016 Naveen N. Rao <naveen.n.rao@linux.vnet.ibm.com>
 *		  IBM Corporation
 *
 * Based on the घातerpc classic BPF JIT compiler by Matt Evans
 */
#समावेश <linux/moduleloader.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <linux/bpf.h>

#समावेश "bpf_jit.h"

अटल व्योम bpf_jit_fill_ill_insns(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	स_रखो32(area, BREAKPOINT_INSTRUCTION, size / 4);
पूर्ण

/* Fix the branch target addresses क्रम subprog calls */
अटल पूर्णांक bpf_jit_fixup_subprog_calls(काष्ठा bpf_prog *fp, u32 *image,
				       काष्ठा codegen_context *ctx, u32 *addrs)
अणु
	स्थिर काष्ठा bpf_insn *insn = fp->insnsi;
	bool func_addr_fixed;
	u64 func_addr;
	u32 पंचांगp_idx;
	पूर्णांक i, ret;

	क्रम (i = 0; i < fp->len; i++) अणु
		/*
		 * During the extra pass, only the branch target addresses क्रम
		 * the subprog calls need to be fixed. All other inकाष्ठाions
		 * can left untouched.
		 *
		 * The JITed image length करोes not change because we alपढ़ोy
		 * ensure that the JITed inकाष्ठाion sequence क्रम these calls
		 * are of fixed length by padding them with NOPs.
		 */
		अगर (insn[i].code == (BPF_JMP | BPF_CALL) &&
		    insn[i].src_reg == BPF_PSEUDO_CALL) अणु
			ret = bpf_jit_get_func_addr(fp, &insn[i], true,
						    &func_addr,
						    &func_addr_fixed);
			अगर (ret < 0)
				वापस ret;

			/*
			 * Save ctx->idx as this would currently poपूर्णांक to the
			 * end of the JITed image and set it to the offset of
			 * the inकाष्ठाion sequence corresponding to the
			 * subprog call temporarily.
			 */
			पंचांगp_idx = ctx->idx;
			ctx->idx = addrs[i] / 4;
			bpf_jit_emit_func_call_rel(image, ctx, func_addr);

			/*
			 * Restore ctx->idx here. This is safe as the length
			 * of the JITed sequence reमुख्यs unchanged.
			 */
			ctx->idx = पंचांगp_idx;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा घातerpc64_jit_data अणु
	काष्ठा bpf_binary_header *header;
	u32 *addrs;
	u8 *image;
	u32 proglen;
	काष्ठा codegen_context ctx;
पूर्ण;

bool bpf_jit_needs_zext(व्योम)
अणु
	वापस true;
पूर्ण

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *fp)
अणु
	u32 proglen;
	u32 alloclen;
	u8 *image = शून्य;
	u32 *code_base;
	u32 *addrs;
	काष्ठा घातerpc64_jit_data *jit_data;
	काष्ठा codegen_context cgctx;
	पूर्णांक pass;
	पूर्णांक flen;
	काष्ठा bpf_binary_header *bpf_hdr;
	काष्ठा bpf_prog *org_fp = fp;
	काष्ठा bpf_prog *पंचांगp_fp;
	bool bpf_blinded = false;
	bool extra_pass = false;

	अगर (!fp->jit_requested)
		वापस org_fp;

	पंचांगp_fp = bpf_jit_blind_स्थिरants(org_fp);
	अगर (IS_ERR(पंचांगp_fp))
		वापस org_fp;

	अगर (पंचांगp_fp != org_fp) अणु
		bpf_blinded = true;
		fp = पंचांगp_fp;
	पूर्ण

	jit_data = fp->aux->jit_data;
	अगर (!jit_data) अणु
		jit_data = kzalloc(माप(*jit_data), GFP_KERNEL);
		अगर (!jit_data) अणु
			fp = org_fp;
			जाओ out;
		पूर्ण
		fp->aux->jit_data = jit_data;
	पूर्ण

	flen = fp->len;
	addrs = jit_data->addrs;
	अगर (addrs) अणु
		cgctx = jit_data->ctx;
		image = jit_data->image;
		bpf_hdr = jit_data->header;
		proglen = jit_data->proglen;
		alloclen = proglen + FUNCTION_DESCR_SIZE;
		extra_pass = true;
		जाओ skip_init_ctx;
	पूर्ण

	addrs = kसुस्मृति(flen + 1, माप(*addrs), GFP_KERNEL);
	अगर (addrs == शून्य) अणु
		fp = org_fp;
		जाओ out_addrs;
	पूर्ण

	स_रखो(&cgctx, 0, माप(काष्ठा codegen_context));
	स_नकल(cgctx.b2p, b2p, माप(cgctx.b2p));

	/* Make sure that the stack is quadword aligned. */
	cgctx.stack_size = round_up(fp->aux->stack_depth, 16);

	/* Scouting faux-generate pass 0 */
	अगर (bpf_jit_build_body(fp, 0, &cgctx, addrs, false)) अणु
		/* We hit something illegal or unsupported. */
		fp = org_fp;
		जाओ out_addrs;
	पूर्ण

	/*
	 * If we have seen a tail call, we need a second pass.
	 * This is because bpf_jit_emit_common_epilogue() is called
	 * from bpf_jit_emit_tail_call() with a not yet stable ctx->seen.
	 */
	अगर (cgctx.seen & SEEN_TAILCALL) अणु
		cgctx.idx = 0;
		अगर (bpf_jit_build_body(fp, 0, &cgctx, addrs, false)) अणु
			fp = org_fp;
			जाओ out_addrs;
		पूर्ण
	पूर्ण

	bpf_jit_पुनः_स्मृति_regs(&cgctx);
	/*
	 * Pretend to build prologue, given the features we've seen.  This will
	 * update ctgtx.idx as it pretends to output inकाष्ठाions, then we can
	 * calculate total size from idx.
	 */
	bpf_jit_build_prologue(0, &cgctx);
	bpf_jit_build_epilogue(0, &cgctx);

	proglen = cgctx.idx * 4;
	alloclen = proglen + FUNCTION_DESCR_SIZE;

	bpf_hdr = bpf_jit_binary_alloc(alloclen, &image, 4, bpf_jit_fill_ill_insns);
	अगर (!bpf_hdr) अणु
		fp = org_fp;
		जाओ out_addrs;
	पूर्ण

skip_init_ctx:
	code_base = (u32 *)(image + FUNCTION_DESCR_SIZE);

	अगर (extra_pass) अणु
		/*
		 * Do not touch the prologue and epilogue as they will reमुख्य
		 * unchanged. Only fix the branch target address क्रम subprog
		 * calls in the body.
		 *
		 * This करोes not change the offsets and lengths of the subprog
		 * call inकाष्ठाion sequences and hence, the size of the JITed
		 * image as well.
		 */
		bpf_jit_fixup_subprog_calls(fp, code_base, &cgctx, addrs);

		/* There is no need to perक्रमm the usual passes. */
		जाओ skip_codegen_passes;
	पूर्ण

	/* Code generation passes 1-2 */
	क्रम (pass = 1; pass < 3; pass++) अणु
		/* Now build the prologue, body code & epilogue क्रम real. */
		cgctx.idx = 0;
		bpf_jit_build_prologue(code_base, &cgctx);
		bpf_jit_build_body(fp, code_base, &cgctx, addrs, extra_pass);
		bpf_jit_build_epilogue(code_base, &cgctx);

		अगर (bpf_jit_enable > 1)
			pr_info("Pass %d: shrink = %d, seen = 0x%x\n", pass,
				proglen - (cgctx.idx * 4), cgctx.seen);
	पूर्ण

skip_codegen_passes:
	अगर (bpf_jit_enable > 1)
		/*
		 * Note that we output the base address of the code_base
		 * rather than image, since opcodes are in code_base.
		 */
		bpf_jit_dump(flen, proglen, pass, code_base);

#अगर_घोषित PPC64_ELF_ABI_v1
	/* Function descriptor nastiness: Address + TOC */
	((u64 *)image)[0] = (u64)code_base;
	((u64 *)image)[1] = local_paca->kernel_toc;
#पूर्ण_अगर

	fp->bpf_func = (व्योम *)image;
	fp->jited = 1;
	fp->jited_len = alloclen;

	bpf_flush_icache(bpf_hdr, (u8 *)bpf_hdr + (bpf_hdr->pages * PAGE_SIZE));
	अगर (!fp->is_func || extra_pass) अणु
		bpf_prog_fill_jited_linfo(fp, addrs);
out_addrs:
		kमुक्त(addrs);
		kमुक्त(jit_data);
		fp->aux->jit_data = शून्य;
	पूर्ण अन्यथा अणु
		jit_data->addrs = addrs;
		jit_data->ctx = cgctx;
		jit_data->proglen = proglen;
		jit_data->image = image;
		jit_data->header = bpf_hdr;
	पूर्ण

out:
	अगर (bpf_blinded)
		bpf_jit_prog_release_other(fp, fp == org_fp ? पंचांगp_fp : org_fp);

	वापस fp;
पूर्ण

/* Overriding bpf_jit_मुक्त() as we करोn't set images पढ़ो-only. */
व्योम bpf_jit_मुक्त(काष्ठा bpf_prog *fp)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)fp->bpf_func & PAGE_MASK;
	काष्ठा bpf_binary_header *bpf_hdr = (व्योम *)addr;

	अगर (fp->jited)
		bpf_jit_binary_मुक्त(bpf_hdr);

	bpf_prog_unlock_मुक्त(fp);
पूर्ण
