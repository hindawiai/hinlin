<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common functionality क्रम RV32 and RV64 BPF JIT compilers
 *
 * Copyright (c) 2019 Bjथघrn Tथघpel <bjorn.topel@gmail.com>
 *
 */

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश "bpf_jit.h"

/* Number of iterations to try until offsets converge. */
#घोषणा NR_JIT_ITERATIONS	16

अटल पूर्णांक build_body(काष्ठा rv_jit_context *ctx, bool extra_pass, पूर्णांक *offset)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->prog;
	पूर्णांक i;

	क्रम (i = 0; i < prog->len; i++) अणु
		स्थिर काष्ठा bpf_insn *insn = &prog->insnsi[i];
		पूर्णांक ret;

		ret = bpf_jit_emit_insn(insn, ctx, extra_pass);
		/* BPF_LD | BPF_IMM | BPF_DW: skip the next inकाष्ठाion. */
		अगर (ret > 0)
			i++;
		अगर (offset)
			offset[i] = ctx->ninsns;
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

bool bpf_jit_needs_zext(व्योम)
अणु
	वापस true;
पूर्ण

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	bool पंचांगp_blinded = false, extra_pass = false;
	काष्ठा bpf_prog *पंचांगp, *orig_prog = prog;
	पूर्णांक pass = 0, prev_ninsns = 0, i;
	काष्ठा rv_jit_data *jit_data;
	काष्ठा rv_jit_context *ctx;
	अचिन्हित पूर्णांक image_size = 0;

	अगर (!prog->jit_requested)
		वापस orig_prog;

	पंचांगp = bpf_jit_blind_स्थिरants(prog);
	अगर (IS_ERR(पंचांगp))
		वापस orig_prog;
	अगर (पंचांगp != prog) अणु
		पंचांगp_blinded = true;
		prog = पंचांगp;
	पूर्ण

	jit_data = prog->aux->jit_data;
	अगर (!jit_data) अणु
		jit_data = kzalloc(माप(*jit_data), GFP_KERNEL);
		अगर (!jit_data) अणु
			prog = orig_prog;
			जाओ out;
		पूर्ण
		prog->aux->jit_data = jit_data;
	पूर्ण

	ctx = &jit_data->ctx;

	अगर (ctx->offset) अणु
		extra_pass = true;
		image_size = माप(*ctx->insns) * ctx->ninsns;
		जाओ skip_init_ctx;
	पूर्ण

	ctx->prog = prog;
	ctx->offset = kसुस्मृति(prog->len, माप(पूर्णांक), GFP_KERNEL);
	अगर (!ctx->offset) अणु
		prog = orig_prog;
		जाओ out_offset;
	पूर्ण
	क्रम (i = 0; i < prog->len; i++) अणु
		prev_ninsns += 32;
		ctx->offset[i] = prev_ninsns;
	पूर्ण

	क्रम (i = 0; i < NR_JIT_ITERATIONS; i++) अणु
		pass++;
		ctx->ninsns = 0;
		अगर (build_body(ctx, extra_pass, ctx->offset)) अणु
			prog = orig_prog;
			जाओ out_offset;
		पूर्ण
		bpf_jit_build_prologue(ctx);
		ctx->epilogue_offset = ctx->ninsns;
		bpf_jit_build_epilogue(ctx);

		अगर (ctx->ninsns == prev_ninsns) अणु
			अगर (jit_data->header)
				अवरोध;

			image_size = माप(*ctx->insns) * ctx->ninsns;
			jit_data->header =
				bpf_jit_binary_alloc(image_size,
						     &jit_data->image,
						     माप(u32),
						     bpf_fill_ill_insns);
			अगर (!jit_data->header) अणु
				prog = orig_prog;
				जाओ out_offset;
			पूर्ण

			ctx->insns = (u16 *)jit_data->image;
			/*
			 * Now, when the image is allocated, the image can
			 * potentially shrink more (auipc/jalr -> jal).
			 */
		पूर्ण
		prev_ninsns = ctx->ninsns;
	पूर्ण

	अगर (i == NR_JIT_ITERATIONS) अणु
		pr_err("bpf-jit: image did not converge in <%d passes!\n", i);
		bpf_jit_binary_मुक्त(jit_data->header);
		prog = orig_prog;
		जाओ out_offset;
	पूर्ण

skip_init_ctx:
	pass++;
	ctx->ninsns = 0;

	bpf_jit_build_prologue(ctx);
	अगर (build_body(ctx, extra_pass, शून्य)) अणु
		bpf_jit_binary_मुक्त(jit_data->header);
		prog = orig_prog;
		जाओ out_offset;
	पूर्ण
	bpf_jit_build_epilogue(ctx);

	अगर (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, image_size, pass, ctx->insns);

	prog->bpf_func = (व्योम *)ctx->insns;
	prog->jited = 1;
	prog->jited_len = image_size;

	bpf_flush_icache(jit_data->header, ctx->insns + ctx->ninsns);

	अगर (!prog->is_func || extra_pass) अणु
		bpf_jit_binary_lock_ro(jit_data->header);
out_offset:
		kमुक्त(ctx->offset);
		kमुक्त(jit_data);
		prog->aux->jit_data = शून्य;
	पूर्ण
out:

	अगर (पंचांगp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   पंचांगp : orig_prog);
	वापस prog;
पूर्ण

व्योम *bpf_jit_alloc_exec(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, PAGE_SIZE, BPF_JIT_REGION_START,
				    BPF_JIT_REGION_END, GFP_KERNEL,
				    PAGE_KERNEL, 0, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
पूर्ण

व्योम bpf_jit_मुक्त_exec(व्योम *addr)
अणु
	वापस vमुक्त(addr);
पूर्ण
