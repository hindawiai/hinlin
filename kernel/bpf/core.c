<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux Socket Filter - Kernel level socket filtering
 *
 * Based on the design of the Berkeley Packet Filter. The new
 * पूर्णांकernal क्रमmat has been deचिन्हित by PLUMgrid:
 *
 *	Copyright (c) 2011 - 2014 PLUMgrid, http://plumgrid.com
 *
 * Authors:
 *
 *	Jay Schulist <jschlst@samba.org>
 *	Alexei Starovoitov <ast@plumgrid.com>
 *	Daniel Borkmann <dborkman@redhat.com>
 *
 * Andi Kleen - Fix a few bad bugs and races.
 * Kris Katterjohn - Added many additional checks in bpf_check_classic()
 */

#समावेश <uapi/linux/btf.h>
#समावेश <linux/filter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/objtool.h>
#समावेश <linux/rbtree_latch.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/extable.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/unaligned.h>

/* Registers */
#घोषणा BPF_R0	regs[BPF_REG_0]
#घोषणा BPF_R1	regs[BPF_REG_1]
#घोषणा BPF_R2	regs[BPF_REG_2]
#घोषणा BPF_R3	regs[BPF_REG_3]
#घोषणा BPF_R4	regs[BPF_REG_4]
#घोषणा BPF_R5	regs[BPF_REG_5]
#घोषणा BPF_R6	regs[BPF_REG_6]
#घोषणा BPF_R7	regs[BPF_REG_7]
#घोषणा BPF_R8	regs[BPF_REG_8]
#घोषणा BPF_R9	regs[BPF_REG_9]
#घोषणा BPF_R10	regs[BPF_REG_10]

/* Named रेजिस्टरs */
#घोषणा DST	regs[insn->dst_reg]
#घोषणा SRC	regs[insn->src_reg]
#घोषणा FP	regs[BPF_REG_FP]
#घोषणा AX	regs[BPF_REG_AX]
#घोषणा ARG1	regs[BPF_REG_ARG1]
#घोषणा CTX	regs[BPF_REG_CTX]
#घोषणा IMM	insn->imm

/* No hurry in this branch
 *
 * Exported क्रम the bpf jit load helper.
 */
व्योम *bpf_पूर्णांकernal_load_poपूर्णांकer_neg_helper(स्थिर काष्ठा sk_buff *skb, पूर्णांक k, अचिन्हित पूर्णांक size)
अणु
	u8 *ptr = शून्य;

	अगर (k >= SKF_NET_OFF)
		ptr = skb_network_header(skb) + k - SKF_NET_OFF;
	अन्यथा अगर (k >= SKF_LL_OFF)
		ptr = skb_mac_header(skb) + k - SKF_LL_OFF;

	अगर (ptr >= skb->head && ptr + size <= skb_tail_poपूर्णांकer(skb))
		वापस ptr;

	वापस शून्य;
पूर्ण

काष्ठा bpf_prog *bpf_prog_alloc_no_stats(अचिन्हित पूर्णांक size, gfp_t gfp_extra_flags)
अणु
	gfp_t gfp_flags = GFP_KERNEL_ACCOUNT | __GFP_ZERO | gfp_extra_flags;
	काष्ठा bpf_prog_aux *aux;
	काष्ठा bpf_prog *fp;

	size = round_up(size, PAGE_SIZE);
	fp = __vदो_स्मृति(size, gfp_flags);
	अगर (fp == शून्य)
		वापस शून्य;

	aux = kzalloc(माप(*aux), GFP_KERNEL_ACCOUNT | gfp_extra_flags);
	अगर (aux == शून्य) अणु
		vमुक्त(fp);
		वापस शून्य;
	पूर्ण
	fp->active = alloc_percpu_gfp(पूर्णांक, GFP_KERNEL_ACCOUNT | gfp_extra_flags);
	अगर (!fp->active) अणु
		vमुक्त(fp);
		kमुक्त(aux);
		वापस शून्य;
	पूर्ण

	fp->pages = size / PAGE_SIZE;
	fp->aux = aux;
	fp->aux->prog = fp;
	fp->jit_requested = ebpf_jit_enabled();

	INIT_LIST_HEAD_RCU(&fp->aux->ksym.lnode);
	mutex_init(&fp->aux->used_maps_mutex);
	mutex_init(&fp->aux->dst_mutex);

	वापस fp;
पूर्ण

काष्ठा bpf_prog *bpf_prog_alloc(अचिन्हित पूर्णांक size, gfp_t gfp_extra_flags)
अणु
	gfp_t gfp_flags = GFP_KERNEL_ACCOUNT | __GFP_ZERO | gfp_extra_flags;
	काष्ठा bpf_prog *prog;
	पूर्णांक cpu;

	prog = bpf_prog_alloc_no_stats(size, gfp_extra_flags);
	अगर (!prog)
		वापस शून्य;

	prog->stats = alloc_percpu_gfp(काष्ठा bpf_prog_stats, gfp_flags);
	अगर (!prog->stats) अणु
		मुक्त_percpu(prog->active);
		kमुक्त(prog->aux);
		vमुक्त(prog);
		वापस शून्य;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा bpf_prog_stats *pstats;

		pstats = per_cpu_ptr(prog->stats, cpu);
		u64_stats_init(&pstats->syncp);
	पूर्ण
	वापस prog;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_alloc);

पूर्णांक bpf_prog_alloc_jited_linfo(काष्ठा bpf_prog *prog)
अणु
	अगर (!prog->aux->nr_linfo || !prog->jit_requested)
		वापस 0;

	prog->aux->jited_linfo = kvसुस्मृति(prog->aux->nr_linfo,
					  माप(*prog->aux->jited_linfo),
					  GFP_KERNEL_ACCOUNT | __GFP_NOWARN);
	अगर (!prog->aux->jited_linfo)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम bpf_prog_jit_attempt_करोne(काष्ठा bpf_prog *prog)
अणु
	अगर (prog->aux->jited_linfo &&
	    (!prog->jited || !prog->aux->jited_linfo[0])) अणु
		kvमुक्त(prog->aux->jited_linfo);
		prog->aux->jited_linfo = शून्य;
	पूर्ण

	kमुक्त(prog->aux->kfunc_tab);
	prog->aux->kfunc_tab = शून्य;
पूर्ण

/* The jit engine is responsible to provide an array
 * क्रम insn_off to the jited_off mapping (insn_to_jit_off).
 *
 * The idx to this array is the insn_off.  Hence, the insn_off
 * here is relative to the prog itself instead of the मुख्य prog.
 * This array has one entry क्रम each xlated bpf insn.
 *
 * jited_off is the byte off to the last byte of the jited insn.
 *
 * Hence, with
 * insn_start:
 *      The first bpf insn off of the prog.  The insn off
 *      here is relative to the मुख्य prog.
 *      e.g. अगर prog is a subprog, insn_start > 0
 * linfo_idx:
 *      The prog's idx to prog->aux->linfo and jited_linfo
 *
 * jited_linfo[linfo_idx] = prog->bpf_func
 *
 * For i > linfo_idx,
 *
 * jited_linfo[i] = prog->bpf_func +
 *	insn_to_jit_off[linfo[i].insn_off - insn_start - 1]
 */
व्योम bpf_prog_fill_jited_linfo(काष्ठा bpf_prog *prog,
			       स्थिर u32 *insn_to_jit_off)
अणु
	u32 linfo_idx, insn_start, insn_end, nr_linfo, i;
	स्थिर काष्ठा bpf_line_info *linfo;
	व्योम **jited_linfo;

	अगर (!prog->aux->jited_linfo)
		/* Userspace did not provide linfo */
		वापस;

	linfo_idx = prog->aux->linfo_idx;
	linfo = &prog->aux->linfo[linfo_idx];
	insn_start = linfo[0].insn_off;
	insn_end = insn_start + prog->len;

	jited_linfo = &prog->aux->jited_linfo[linfo_idx];
	jited_linfo[0] = prog->bpf_func;

	nr_linfo = prog->aux->nr_linfo - linfo_idx;

	क्रम (i = 1; i < nr_linfo && linfo[i].insn_off < insn_end; i++)
		/* The verअगरier ensures that linfo[i].insn_off is
		 * strictly increasing
		 */
		jited_linfo[i] = prog->bpf_func +
			insn_to_jit_off[linfo[i].insn_off - insn_start - 1];
पूर्ण

काष्ठा bpf_prog *bpf_prog_पुनः_स्मृति(काष्ठा bpf_prog *fp_old, अचिन्हित पूर्णांक size,
				  gfp_t gfp_extra_flags)
अणु
	gfp_t gfp_flags = GFP_KERNEL_ACCOUNT | __GFP_ZERO | gfp_extra_flags;
	काष्ठा bpf_prog *fp;
	u32 pages;

	size = round_up(size, PAGE_SIZE);
	pages = size / PAGE_SIZE;
	अगर (pages <= fp_old->pages)
		वापस fp_old;

	fp = __vदो_स्मृति(size, gfp_flags);
	अगर (fp) अणु
		स_नकल(fp, fp_old, fp_old->pages * PAGE_SIZE);
		fp->pages = pages;
		fp->aux->prog = fp;

		/* We keep fp->aux from fp_old around in the new
		 * पुनः_स्मृतिated काष्ठाure.
		 */
		fp_old->aux = शून्य;
		fp_old->stats = शून्य;
		fp_old->active = शून्य;
		__bpf_prog_मुक्त(fp_old);
	पूर्ण

	वापस fp;
पूर्ण

व्योम __bpf_prog_मुक्त(काष्ठा bpf_prog *fp)
अणु
	अगर (fp->aux) अणु
		mutex_destroy(&fp->aux->used_maps_mutex);
		mutex_destroy(&fp->aux->dst_mutex);
		kमुक्त(fp->aux->poke_tab);
		kमुक्त(fp->aux);
	पूर्ण
	मुक्त_percpu(fp->stats);
	मुक्त_percpu(fp->active);
	vमुक्त(fp);
पूर्ण

पूर्णांक bpf_prog_calc_tag(काष्ठा bpf_prog *fp)
अणु
	स्थिर u32 bits_offset = SHA1_BLOCK_SIZE - माप(__be64);
	u32 raw_size = bpf_prog_tag_scratch_size(fp);
	u32 digest[SHA1_DIGEST_WORDS];
	u32 ws[SHA1_WORKSPACE_WORDS];
	u32 i, bsize, psize, blocks;
	काष्ठा bpf_insn *dst;
	bool was_ld_map;
	u8 *raw, *toकरो;
	__be32 *result;
	__be64 *bits;

	raw = vदो_स्मृति(raw_size);
	अगर (!raw)
		वापस -ENOMEM;

	sha1_init(digest);
	स_रखो(ws, 0, माप(ws));

	/* We need to take out the map fd क्रम the digest calculation
	 * since they are unstable from user space side.
	 */
	dst = (व्योम *)raw;
	क्रम (i = 0, was_ld_map = false; i < fp->len; i++) अणु
		dst[i] = fp->insnsi[i];
		अगर (!was_ld_map &&
		    dst[i].code == (BPF_LD | BPF_IMM | BPF_DW) &&
		    (dst[i].src_reg == BPF_PSEUDO_MAP_FD ||
		     dst[i].src_reg == BPF_PSEUDO_MAP_VALUE)) अणु
			was_ld_map = true;
			dst[i].imm = 0;
		पूर्ण अन्यथा अगर (was_ld_map &&
			   dst[i].code == 0 &&
			   dst[i].dst_reg == 0 &&
			   dst[i].src_reg == 0 &&
			   dst[i].off == 0) अणु
			was_ld_map = false;
			dst[i].imm = 0;
		पूर्ण अन्यथा अणु
			was_ld_map = false;
		पूर्ण
	पूर्ण

	psize = bpf_prog_insn_size(fp);
	स_रखो(&raw[psize], 0, raw_size - psize);
	raw[psize++] = 0x80;

	bsize  = round_up(psize, SHA1_BLOCK_SIZE);
	blocks = bsize / SHA1_BLOCK_SIZE;
	toकरो   = raw;
	अगर (bsize - psize >= माप(__be64)) अणु
		bits = (__be64 *)(toकरो + bsize - माप(__be64));
	पूर्ण अन्यथा अणु
		bits = (__be64 *)(toकरो + bsize + bits_offset);
		blocks++;
	पूर्ण
	*bits = cpu_to_be64((psize - 1) << 3);

	जबतक (blocks--) अणु
		sha1_transक्रमm(digest, toकरो, ws);
		toकरो += SHA1_BLOCK_SIZE;
	पूर्ण

	result = (__क्रमce __be32 *)digest;
	क्रम (i = 0; i < SHA1_DIGEST_WORDS; i++)
		result[i] = cpu_to_be32(digest[i]);
	स_नकल(fp->tag, result, माप(fp->tag));

	vमुक्त(raw);
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_adj_delta_to_imm(काष्ठा bpf_insn *insn, u32 pos, s32 end_old,
				s32 end_new, s32 curr, स्थिर bool probe_pass)
अणु
	स्थिर s64 imm_min = S32_MIN, imm_max = S32_MAX;
	s32 delta = end_new - end_old;
	s64 imm = insn->imm;

	अगर (curr < pos && curr + imm + 1 >= end_old)
		imm += delta;
	अन्यथा अगर (curr >= end_new && curr + imm + 1 < end_new)
		imm -= delta;
	अगर (imm < imm_min || imm > imm_max)
		वापस -दुस्फल;
	अगर (!probe_pass)
		insn->imm = imm;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_adj_delta_to_off(काष्ठा bpf_insn *insn, u32 pos, s32 end_old,
				s32 end_new, s32 curr, स्थिर bool probe_pass)
अणु
	स्थिर s32 off_min = S16_MIN, off_max = S16_MAX;
	s32 delta = end_new - end_old;
	s32 off = insn->off;

	अगर (curr < pos && curr + off + 1 >= end_old)
		off += delta;
	अन्यथा अगर (curr >= end_new && curr + off + 1 < end_new)
		off -= delta;
	अगर (off < off_min || off > off_max)
		वापस -दुस्फल;
	अगर (!probe_pass)
		insn->off = off;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_adj_branches(काष्ठा bpf_prog *prog, u32 pos, s32 end_old,
			    s32 end_new, स्थिर bool probe_pass)
अणु
	u32 i, insn_cnt = prog->len + (probe_pass ? end_new - end_old : 0);
	काष्ठा bpf_insn *insn = prog->insnsi;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		u8 code;

		/* In the probing pass we still operate on the original,
		 * unpatched image in order to check overflows beक्रमe we
		 * करो any other adjusपंचांगents. Thereक्रमe skip the patchlet.
		 */
		अगर (probe_pass && i == pos) अणु
			i = end_new;
			insn = prog->insnsi + end_old;
		पूर्ण
		code = insn->code;
		अगर ((BPF_CLASS(code) != BPF_JMP &&
		     BPF_CLASS(code) != BPF_JMP32) ||
		    BPF_OP(code) == BPF_EXIT)
			जारी;
		/* Adjust offset of jmps अगर we cross patch boundaries. */
		अगर (BPF_OP(code) == BPF_CALL) अणु
			अगर (insn->src_reg != BPF_PSEUDO_CALL)
				जारी;
			ret = bpf_adj_delta_to_imm(insn, pos, end_old,
						   end_new, i, probe_pass);
		पूर्ण अन्यथा अणु
			ret = bpf_adj_delta_to_off(insn, pos, end_old,
						   end_new, i, probe_pass);
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bpf_adj_linfo(काष्ठा bpf_prog *prog, u32 off, u32 delta)
अणु
	काष्ठा bpf_line_info *linfo;
	u32 i, nr_linfo;

	nr_linfo = prog->aux->nr_linfo;
	अगर (!nr_linfo || !delta)
		वापस;

	linfo = prog->aux->linfo;

	क्रम (i = 0; i < nr_linfo; i++)
		अगर (off < linfo[i].insn_off)
			अवरोध;

	/* Push all off < linfo[i].insn_off by delta */
	क्रम (; i < nr_linfo; i++)
		linfo[i].insn_off += delta;
पूर्ण

काष्ठा bpf_prog *bpf_patch_insn_single(काष्ठा bpf_prog *prog, u32 off,
				       स्थिर काष्ठा bpf_insn *patch, u32 len)
अणु
	u32 insn_adj_cnt, insn_rest, insn_delta = len - 1;
	स्थिर u32 cnt_max = S16_MAX;
	काष्ठा bpf_prog *prog_adj;
	पूर्णांक err;

	/* Since our patchlet करोesn't expand the image, we're करोne. */
	अगर (insn_delta == 0) अणु
		स_नकल(prog->insnsi + off, patch, माप(*patch));
		वापस prog;
	पूर्ण

	insn_adj_cnt = prog->len + insn_delta;

	/* Reject anything that would potentially let the insn->off
	 * target overflow when we have excessive program expansions.
	 * We need to probe here beक्रमe we करो any पुनः_स्मृतिation where
	 * we afterwards may not fail anymore.
	 */
	अगर (insn_adj_cnt > cnt_max &&
	    (err = bpf_adj_branches(prog, off, off + 1, off + len, true)))
		वापस ERR_PTR(err);

	/* Several new inकाष्ठाions need to be inserted. Make room
	 * क्रम them. Likely, there's no need क्रम a new allocation as
	 * last page could have large enough tailroom.
	 */
	prog_adj = bpf_prog_पुनः_स्मृति(prog, bpf_prog_size(insn_adj_cnt),
				    GFP_USER);
	अगर (!prog_adj)
		वापस ERR_PTR(-ENOMEM);

	prog_adj->len = insn_adj_cnt;

	/* Patching happens in 3 steps:
	 *
	 * 1) Move over tail of insnsi from next inकाष्ठाion onwards,
	 *    so we can patch the single target insn with one or more
	 *    new ones (patching is always from 1 to n insns, n > 0).
	 * 2) Inject new inकाष्ठाions at the target location.
	 * 3) Adjust branch offsets अगर necessary.
	 */
	insn_rest = insn_adj_cnt - off - len;

	स_हटाओ(prog_adj->insnsi + off + len, prog_adj->insnsi + off + 1,
		माप(*patch) * insn_rest);
	स_नकल(prog_adj->insnsi + off, patch, माप(*patch) * len);

	/* We are guaranteed to not fail at this poपूर्णांक, otherwise
	 * the ship has sailed to reverse to the original state. An
	 * overflow cannot happen at this poपूर्णांक.
	 */
	BUG_ON(bpf_adj_branches(prog_adj, off, off + 1, off + len, false));

	bpf_adj_linfo(prog_adj, off, insn_delta);

	वापस prog_adj;
पूर्ण

पूर्णांक bpf_हटाओ_insns(काष्ठा bpf_prog *prog, u32 off, u32 cnt)
अणु
	/* Branch offsets can't overflow when program is shrinking, no need
	 * to call bpf_adj_branches(..., true) here
	 */
	स_हटाओ(prog->insnsi + off, prog->insnsi + off + cnt,
		माप(काष्ठा bpf_insn) * (prog->len - off - cnt));
	prog->len -= cnt;

	वापस WARN_ON_ONCE(bpf_adj_branches(prog, off, off + cnt, off, false));
पूर्ण

अटल व्योम bpf_prog_kallsyms_del_subprogs(काष्ठा bpf_prog *fp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fp->aux->func_cnt; i++)
		bpf_prog_kallsyms_del(fp->aux->func[i]);
पूर्ण

व्योम bpf_prog_kallsyms_del_all(काष्ठा bpf_prog *fp)
अणु
	bpf_prog_kallsyms_del_subprogs(fp);
	bpf_prog_kallsyms_del(fp);
पूर्ण

#अगर_घोषित CONFIG_BPF_JIT
/* All BPF JIT sysctl knobs here. */
पूर्णांक bpf_jit_enable   __पढ़ो_mostly = IS_BUILTIN(CONFIG_BPF_JIT_DEFAULT_ON);
पूर्णांक bpf_jit_kallsyms __पढ़ो_mostly = IS_BUILTIN(CONFIG_BPF_JIT_DEFAULT_ON);
पूर्णांक bpf_jit_harden   __पढ़ो_mostly;
दीर्घ bpf_jit_limit   __पढ़ो_mostly;

अटल व्योम
bpf_prog_ksym_set_addr(काष्ठा bpf_prog *prog)
अणु
	स्थिर काष्ठा bpf_binary_header *hdr = bpf_jit_binary_hdr(prog);
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)hdr;

	WARN_ON_ONCE(!bpf_prog_ebpf_jited(prog));

	prog->aux->ksym.start = (अचिन्हित दीर्घ) prog->bpf_func;
	prog->aux->ksym.end   = addr + hdr->pages * PAGE_SIZE;
पूर्ण

अटल व्योम
bpf_prog_ksym_set_name(काष्ठा bpf_prog *prog)
अणु
	अक्षर *sym = prog->aux->ksym.name;
	स्थिर अक्षर *end = sym + KSYM_NAME_LEN;
	स्थिर काष्ठा btf_type *type;
	स्थिर अक्षर *func_name;

	BUILD_BUG_ON(माप("bpf_prog_") +
		     माप(prog->tag) * 2 +
		     /* name has been null terminated.
		      * We should need +1 क्रम the '_' preceding
		      * the name.  However, the null अक्षरacter
		      * is द्विगुन counted between the name and the
		      * माप("bpf_prog_") above, so we omit
		      * the +1 here.
		      */
		     माप(prog->aux->name) > KSYM_NAME_LEN);

	sym += snम_लिखो(sym, KSYM_NAME_LEN, "bpf_prog_");
	sym  = bin2hex(sym, prog->tag, माप(prog->tag));

	/* prog->aux->name will be ignored अगर full btf name is available */
	अगर (prog->aux->func_info_cnt) अणु
		type = btf_type_by_id(prog->aux->btf,
				      prog->aux->func_info[prog->aux->func_idx].type_id);
		func_name = btf_name_by_offset(prog->aux->btf, type->name_off);
		snम_लिखो(sym, (माप_प्रकार)(end - sym), "_%s", func_name);
		वापस;
	पूर्ण

	अगर (prog->aux->name[0])
		snम_लिखो(sym, (माप_प्रकार)(end - sym), "_%s", prog->aux->name);
	अन्यथा
		*sym = 0;
पूर्ण

अटल अचिन्हित दीर्घ bpf_get_ksym_start(काष्ठा latch_tree_node *n)
अणु
	वापस container_of(n, काष्ठा bpf_ksym, tnode)->start;
पूर्ण

अटल __always_अंतरभूत bool bpf_tree_less(काष्ठा latch_tree_node *a,
					  काष्ठा latch_tree_node *b)
अणु
	वापस bpf_get_ksym_start(a) < bpf_get_ksym_start(b);
पूर्ण

अटल __always_अंतरभूत पूर्णांक bpf_tree_comp(व्योम *key, काष्ठा latch_tree_node *n)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)key;
	स्थिर काष्ठा bpf_ksym *ksym;

	ksym = container_of(n, काष्ठा bpf_ksym, tnode);

	अगर (val < ksym->start)
		वापस -1;
	अगर (val >= ksym->end)
		वापस  1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा latch_tree_ops bpf_tree_ops = अणु
	.less	= bpf_tree_less,
	.comp	= bpf_tree_comp,
पूर्ण;

अटल DEFINE_SPINLOCK(bpf_lock);
अटल LIST_HEAD(bpf_kallsyms);
अटल काष्ठा latch_tree_root bpf_tree __cacheline_aligned;

व्योम bpf_ksym_add(काष्ठा bpf_ksym *ksym)
अणु
	spin_lock_bh(&bpf_lock);
	WARN_ON_ONCE(!list_empty(&ksym->lnode));
	list_add_tail_rcu(&ksym->lnode, &bpf_kallsyms);
	latch_tree_insert(&ksym->tnode, &bpf_tree, &bpf_tree_ops);
	spin_unlock_bh(&bpf_lock);
पूर्ण

अटल व्योम __bpf_ksym_del(काष्ठा bpf_ksym *ksym)
अणु
	अगर (list_empty(&ksym->lnode))
		वापस;

	latch_tree_erase(&ksym->tnode, &bpf_tree, &bpf_tree_ops);
	list_del_rcu(&ksym->lnode);
पूर्ण

व्योम bpf_ksym_del(काष्ठा bpf_ksym *ksym)
अणु
	spin_lock_bh(&bpf_lock);
	__bpf_ksym_del(ksym);
	spin_unlock_bh(&bpf_lock);
पूर्ण

अटल bool bpf_prog_kallsyms_candidate(स्थिर काष्ठा bpf_prog *fp)
अणु
	वापस fp->jited && !bpf_prog_was_classic(fp);
पूर्ण

अटल bool bpf_prog_kallsyms_verअगरy_off(स्थिर काष्ठा bpf_prog *fp)
अणु
	वापस list_empty(&fp->aux->ksym.lnode) ||
	       fp->aux->ksym.lnode.prev == LIST_POISON2;
पूर्ण

व्योम bpf_prog_kallsyms_add(काष्ठा bpf_prog *fp)
अणु
	अगर (!bpf_prog_kallsyms_candidate(fp) ||
	    !bpf_capable())
		वापस;

	bpf_prog_ksym_set_addr(fp);
	bpf_prog_ksym_set_name(fp);
	fp->aux->ksym.prog = true;

	bpf_ksym_add(&fp->aux->ksym);
पूर्ण

व्योम bpf_prog_kallsyms_del(काष्ठा bpf_prog *fp)
अणु
	अगर (!bpf_prog_kallsyms_candidate(fp))
		वापस;

	bpf_ksym_del(&fp->aux->ksym);
पूर्ण

अटल काष्ठा bpf_ksym *bpf_ksym_find(अचिन्हित दीर्घ addr)
अणु
	काष्ठा latch_tree_node *n;

	n = latch_tree_find((व्योम *)addr, &bpf_tree, &bpf_tree_ops);
	वापस n ? container_of(n, काष्ठा bpf_ksym, tnode) : शून्य;
पूर्ण

स्थिर अक्षर *__bpf_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
				 अचिन्हित दीर्घ *off, अक्षर *sym)
अणु
	काष्ठा bpf_ksym *ksym;
	अक्षर *ret = शून्य;

	rcu_पढ़ो_lock();
	ksym = bpf_ksym_find(addr);
	अगर (ksym) अणु
		अचिन्हित दीर्घ symbol_start = ksym->start;
		अचिन्हित दीर्घ symbol_end = ksym->end;

		म_नकलन(sym, ksym->name, KSYM_NAME_LEN);

		ret = sym;
		अगर (size)
			*size = symbol_end - symbol_start;
		अगर (off)
			*off  = addr - symbol_start;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

bool is_bpf_text_address(अचिन्हित दीर्घ addr)
अणु
	bool ret;

	rcu_पढ़ो_lock();
	ret = bpf_ksym_find(addr) != शून्य;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल काष्ठा bpf_prog *bpf_prog_ksym_find(अचिन्हित दीर्घ addr)
अणु
	काष्ठा bpf_ksym *ksym = bpf_ksym_find(addr);

	वापस ksym && ksym->prog ?
	       container_of(ksym, काष्ठा bpf_prog_aux, ksym)->prog :
	       शून्य;
पूर्ण

स्थिर काष्ठा exception_table_entry *search_bpf_extables(अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा exception_table_entry *e = शून्य;
	काष्ठा bpf_prog *prog;

	rcu_पढ़ो_lock();
	prog = bpf_prog_ksym_find(addr);
	अगर (!prog)
		जाओ out;
	अगर (!prog->aux->num_exentries)
		जाओ out;

	e = search_extable(prog->aux->extable, prog->aux->num_exentries, addr);
out:
	rcu_पढ़ो_unlock();
	वापस e;
पूर्ण

पूर्णांक bpf_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value, अक्षर *type,
		    अक्षर *sym)
अणु
	काष्ठा bpf_ksym *ksym;
	अचिन्हित पूर्णांक it = 0;
	पूर्णांक ret = -दुस्फल;

	अगर (!bpf_jit_kallsyms_enabled())
		वापस ret;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ksym, &bpf_kallsyms, lnode) अणु
		अगर (it++ != symnum)
			जारी;

		म_नकलन(sym, ksym->name, KSYM_NAME_LEN);

		*value = ksym->start;
		*type  = BPF_SYM_ELF_TYPE;

		ret = 0;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

पूर्णांक bpf_jit_add_poke_descriptor(काष्ठा bpf_prog *prog,
				काष्ठा bpf_jit_poke_descriptor *poke)
अणु
	काष्ठा bpf_jit_poke_descriptor *tab = prog->aux->poke_tab;
	अटल स्थिर u32 poke_tab_max = 1024;
	u32 slot = prog->aux->size_poke_tab;
	u32 size = slot + 1;

	अगर (size > poke_tab_max)
		वापस -ENOSPC;
	अगर (poke->tailcall_target || poke->tailcall_target_stable ||
	    poke->tailcall_bypass || poke->adj_off || poke->bypass_addr)
		वापस -EINVAL;

	चयन (poke->reason) अणु
	हाल BPF_POKE_REASON_TAIL_CALL:
		अगर (!poke->tail_call.map)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	tab = kपुनः_स्मृति(tab, size * माप(*poke), GFP_KERNEL);
	अगर (!tab)
		वापस -ENOMEM;

	स_नकल(&tab[slot], poke, माप(*poke));
	prog->aux->size_poke_tab = size;
	prog->aux->poke_tab = tab;

	वापस slot;
पूर्ण

अटल atomic_दीर्घ_t bpf_jit_current;

/* Can be overridden by an arch's JIT compiler अगर it has a custom,
 * dedicated BPF backend memory area, or अगर neither of the two
 * below apply.
 */
u64 __weak bpf_jit_alloc_exec_limit(व्योम)
अणु
#अगर defined(MODULES_VADDR)
	वापस MODULES_END - MODULES_VADDR;
#अन्यथा
	वापस VMALLOC_END - VMALLOC_START;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init bpf_jit_अक्षरge_init(व्योम)
अणु
	/* Only used as heuristic here to derive limit. */
	bpf_jit_limit = min_t(u64, round_up(bpf_jit_alloc_exec_limit() >> 2,
					    PAGE_SIZE), दीर्घ_उच्च);
	वापस 0;
पूर्ण
pure_initcall(bpf_jit_अक्षरge_init);

पूर्णांक bpf_jit_अक्षरge_modmem(u32 pages)
अणु
	अगर (atomic_दीर्घ_add_वापस(pages, &bpf_jit_current) >
	    (bpf_jit_limit >> PAGE_SHIFT)) अणु
		अगर (!capable(CAP_SYS_ADMIN)) अणु
			atomic_दीर्घ_sub(pages, &bpf_jit_current);
			वापस -EPERM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम bpf_jit_unअक्षरge_modmem(u32 pages)
अणु
	atomic_दीर्घ_sub(pages, &bpf_jit_current);
पूर्ण

व्योम *__weak bpf_jit_alloc_exec(अचिन्हित दीर्घ size)
अणु
	वापस module_alloc(size);
पूर्ण

व्योम __weak bpf_jit_मुक्त_exec(व्योम *addr)
अणु
	module_memमुक्त(addr);
पूर्ण

काष्ठा bpf_binary_header *
bpf_jit_binary_alloc(अचिन्हित पूर्णांक proglen, u8 **image_ptr,
		     अचिन्हित पूर्णांक alignment,
		     bpf_jit_fill_hole_t bpf_fill_ill_insns)
अणु
	काष्ठा bpf_binary_header *hdr;
	u32 size, hole, start, pages;

	WARN_ON_ONCE(!is_घातer_of_2(alignment) ||
		     alignment > BPF_IMAGE_ALIGNMENT);

	/* Most of BPF filters are really small, but अगर some of them
	 * fill a page, allow at least 128 extra bytes to insert a
	 * अक्रमom section of illegal inकाष्ठाions.
	 */
	size = round_up(proglen + माप(*hdr) + 128, PAGE_SIZE);
	pages = size / PAGE_SIZE;

	अगर (bpf_jit_अक्षरge_modmem(pages))
		वापस शून्य;
	hdr = bpf_jit_alloc_exec(size);
	अगर (!hdr) अणु
		bpf_jit_unअक्षरge_modmem(pages);
		वापस शून्य;
	पूर्ण

	/* Fill space with illegal/arch-dep inकाष्ठाions. */
	bpf_fill_ill_insns(hdr, size);

	hdr->pages = pages;
	hole = min_t(अचिन्हित पूर्णांक, size - (proglen + माप(*hdr)),
		     PAGE_SIZE - माप(*hdr));
	start = (get_अक्रमom_पूर्णांक() % hole) & ~(alignment - 1);

	/* Leave a अक्रमom number of inकाष्ठाions beक्रमe BPF code. */
	*image_ptr = &hdr->image[start];

	वापस hdr;
पूर्ण

व्योम bpf_jit_binary_मुक्त(काष्ठा bpf_binary_header *hdr)
अणु
	u32 pages = hdr->pages;

	bpf_jit_मुक्त_exec(hdr);
	bpf_jit_unअक्षरge_modmem(pages);
पूर्ण

/* This symbol is only overridden by archs that have dअगरferent
 * requirements than the usual eBPF JITs, f.e. when they only
 * implement cBPF JIT, करो not set images पढ़ो-only, etc.
 */
व्योम __weak bpf_jit_मुक्त(काष्ठा bpf_prog *fp)
अणु
	अगर (fp->jited) अणु
		काष्ठा bpf_binary_header *hdr = bpf_jit_binary_hdr(fp);

		bpf_jit_binary_मुक्त(hdr);

		WARN_ON_ONCE(!bpf_prog_kallsyms_verअगरy_off(fp));
	पूर्ण

	bpf_prog_unlock_मुक्त(fp);
पूर्ण

पूर्णांक bpf_jit_get_func_addr(स्थिर काष्ठा bpf_prog *prog,
			  स्थिर काष्ठा bpf_insn *insn, bool extra_pass,
			  u64 *func_addr, bool *func_addr_fixed)
अणु
	s16 off = insn->off;
	s32 imm = insn->imm;
	u8 *addr;

	*func_addr_fixed = insn->src_reg != BPF_PSEUDO_CALL;
	अगर (!*func_addr_fixed) अणु
		/* Place-holder address till the last pass has collected
		 * all addresses क्रम JITed subprograms in which हाल we
		 * can pick them up from prog->aux.
		 */
		अगर (!extra_pass)
			addr = शून्य;
		अन्यथा अगर (prog->aux->func &&
			 off >= 0 && off < prog->aux->func_cnt)
			addr = (u8 *)prog->aux->func[off]->bpf_func;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Address of a BPF helper call. Since part of the core
		 * kernel, it's always at a fixed location. __bpf_call_base
		 * and the helper with imm relative to it are both in core
		 * kernel.
		 */
		addr = (u8 *)__bpf_call_base + imm;
	पूर्ण

	*func_addr = (अचिन्हित दीर्घ)addr;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_jit_blind_insn(स्थिर काष्ठा bpf_insn *from,
			      स्थिर काष्ठा bpf_insn *aux,
			      काष्ठा bpf_insn *to_buff,
			      bool emit_zext)
अणु
	काष्ठा bpf_insn *to = to_buff;
	u32 imm_rnd = get_अक्रमom_पूर्णांक();
	s16 off;

	BUILD_BUG_ON(BPF_REG_AX  + 1 != MAX_BPF_JIT_REG);
	BUILD_BUG_ON(MAX_BPF_REG + 1 != MAX_BPF_JIT_REG);

	/* Constraपूर्णांकs on AX रेजिस्टर:
	 *
	 * AX रेजिस्टर is inaccessible from user space. It is mapped in
	 * all JITs, and used here क्रम स्थिरant blinding reग_लिखोs. It is
	 * typically "stateless" meaning its contents are only valid within
	 * the executed inकाष्ठाion, but not across several inकाष्ठाions.
	 * There are a few exceptions however which are further detailed
	 * below.
	 *
	 * Constant blinding is only used by JITs, not in the पूर्णांकerpreter.
	 * The पूर्णांकerpreter uses AX in some occasions as a local temporary
	 * रेजिस्टर e.g. in DIV or MOD inकाष्ठाions.
	 *
	 * In restricted circumstances, the verअगरier can also use the AX
	 * रेजिस्टर क्रम reग_लिखोs as दीर्घ as they करो not पूर्णांकerfere with
	 * the above हालs!
	 */
	अगर (from->dst_reg == BPF_REG_AX || from->src_reg == BPF_REG_AX)
		जाओ out;

	अगर (from->imm == 0 &&
	    (from->code == (BPF_ALU   | BPF_MOV | BPF_K) ||
	     from->code == (BPF_ALU64 | BPF_MOV | BPF_K))) अणु
		*to++ = BPF_ALU64_REG(BPF_XOR, from->dst_reg, from->dst_reg);
		जाओ out;
	पूर्ण

	चयन (from->code) अणु
	हाल BPF_ALU | BPF_ADD | BPF_K:
	हाल BPF_ALU | BPF_SUB | BPF_K:
	हाल BPF_ALU | BPF_AND | BPF_K:
	हाल BPF_ALU | BPF_OR  | BPF_K:
	हाल BPF_ALU | BPF_XOR | BPF_K:
	हाल BPF_ALU | BPF_MUL | BPF_K:
	हाल BPF_ALU | BPF_MOV | BPF_K:
	हाल BPF_ALU | BPF_DIV | BPF_K:
	हाल BPF_ALU | BPF_MOD | BPF_K:
		*to++ = BPF_ALU32_IMM(BPF_MOV, BPF_REG_AX, imm_rnd ^ from->imm);
		*to++ = BPF_ALU32_IMM(BPF_XOR, BPF_REG_AX, imm_rnd);
		*to++ = BPF_ALU32_REG(from->code, from->dst_reg, BPF_REG_AX);
		अवरोध;

	हाल BPF_ALU64 | BPF_ADD | BPF_K:
	हाल BPF_ALU64 | BPF_SUB | BPF_K:
	हाल BPF_ALU64 | BPF_AND | BPF_K:
	हाल BPF_ALU64 | BPF_OR  | BPF_K:
	हाल BPF_ALU64 | BPF_XOR | BPF_K:
	हाल BPF_ALU64 | BPF_MUL | BPF_K:
	हाल BPF_ALU64 | BPF_MOV | BPF_K:
	हाल BPF_ALU64 | BPF_DIV | BPF_K:
	हाल BPF_ALU64 | BPF_MOD | BPF_K:
		*to++ = BPF_ALU64_IMM(BPF_MOV, BPF_REG_AX, imm_rnd ^ from->imm);
		*to++ = BPF_ALU64_IMM(BPF_XOR, BPF_REG_AX, imm_rnd);
		*to++ = BPF_ALU64_REG(from->code, from->dst_reg, BPF_REG_AX);
		अवरोध;

	हाल BPF_JMP | BPF_JEQ  | BPF_K:
	हाल BPF_JMP | BPF_JNE  | BPF_K:
	हाल BPF_JMP | BPF_JGT  | BPF_K:
	हाल BPF_JMP | BPF_JLT  | BPF_K:
	हाल BPF_JMP | BPF_JGE  | BPF_K:
	हाल BPF_JMP | BPF_JLE  | BPF_K:
	हाल BPF_JMP | BPF_JSGT | BPF_K:
	हाल BPF_JMP | BPF_JSLT | BPF_K:
	हाल BPF_JMP | BPF_JSGE | BPF_K:
	हाल BPF_JMP | BPF_JSLE | BPF_K:
	हाल BPF_JMP | BPF_JSET | BPF_K:
		/* Accommodate क्रम extra offset in हाल of a backjump. */
		off = from->off;
		अगर (off < 0)
			off -= 2;
		*to++ = BPF_ALU64_IMM(BPF_MOV, BPF_REG_AX, imm_rnd ^ from->imm);
		*to++ = BPF_ALU64_IMM(BPF_XOR, BPF_REG_AX, imm_rnd);
		*to++ = BPF_JMP_REG(from->code, from->dst_reg, BPF_REG_AX, off);
		अवरोध;

	हाल BPF_JMP32 | BPF_JEQ  | BPF_K:
	हाल BPF_JMP32 | BPF_JNE  | BPF_K:
	हाल BPF_JMP32 | BPF_JGT  | BPF_K:
	हाल BPF_JMP32 | BPF_JLT  | BPF_K:
	हाल BPF_JMP32 | BPF_JGE  | BPF_K:
	हाल BPF_JMP32 | BPF_JLE  | BPF_K:
	हाल BPF_JMP32 | BPF_JSGT | BPF_K:
	हाल BPF_JMP32 | BPF_JSLT | BPF_K:
	हाल BPF_JMP32 | BPF_JSGE | BPF_K:
	हाल BPF_JMP32 | BPF_JSLE | BPF_K:
	हाल BPF_JMP32 | BPF_JSET | BPF_K:
		/* Accommodate क्रम extra offset in हाल of a backjump. */
		off = from->off;
		अगर (off < 0)
			off -= 2;
		*to++ = BPF_ALU32_IMM(BPF_MOV, BPF_REG_AX, imm_rnd ^ from->imm);
		*to++ = BPF_ALU32_IMM(BPF_XOR, BPF_REG_AX, imm_rnd);
		*to++ = BPF_JMP32_REG(from->code, from->dst_reg, BPF_REG_AX,
				      off);
		अवरोध;

	हाल BPF_LD | BPF_IMM | BPF_DW:
		*to++ = BPF_ALU64_IMM(BPF_MOV, BPF_REG_AX, imm_rnd ^ aux[1].imm);
		*to++ = BPF_ALU64_IMM(BPF_XOR, BPF_REG_AX, imm_rnd);
		*to++ = BPF_ALU64_IMM(BPF_LSH, BPF_REG_AX, 32);
		*to++ = BPF_ALU64_REG(BPF_MOV, aux[0].dst_reg, BPF_REG_AX);
		अवरोध;
	हाल 0: /* Part 2 of BPF_LD | BPF_IMM | BPF_DW. */
		*to++ = BPF_ALU32_IMM(BPF_MOV, BPF_REG_AX, imm_rnd ^ aux[0].imm);
		*to++ = BPF_ALU32_IMM(BPF_XOR, BPF_REG_AX, imm_rnd);
		अगर (emit_zext)
			*to++ = BPF_ZEXT_REG(BPF_REG_AX);
		*to++ = BPF_ALU64_REG(BPF_OR,  aux[0].dst_reg, BPF_REG_AX);
		अवरोध;

	हाल BPF_ST | BPF_MEM | BPF_DW:
	हाल BPF_ST | BPF_MEM | BPF_W:
	हाल BPF_ST | BPF_MEM | BPF_H:
	हाल BPF_ST | BPF_MEM | BPF_B:
		*to++ = BPF_ALU64_IMM(BPF_MOV, BPF_REG_AX, imm_rnd ^ from->imm);
		*to++ = BPF_ALU64_IMM(BPF_XOR, BPF_REG_AX, imm_rnd);
		*to++ = BPF_STX_MEM(from->code, from->dst_reg, BPF_REG_AX, from->off);
		अवरोध;
	पूर्ण
out:
	वापस to - to_buff;
पूर्ण

अटल काष्ठा bpf_prog *bpf_prog_clone_create(काष्ठा bpf_prog *fp_other,
					      gfp_t gfp_extra_flags)
अणु
	gfp_t gfp_flags = GFP_KERNEL | __GFP_ZERO | gfp_extra_flags;
	काष्ठा bpf_prog *fp;

	fp = __vदो_स्मृति(fp_other->pages * PAGE_SIZE, gfp_flags);
	अगर (fp != शून्य) अणु
		/* aux->prog still poपूर्णांकs to the fp_other one, so
		 * when promoting the clone to the real program,
		 * this still needs to be adapted.
		 */
		स_नकल(fp, fp_other, fp_other->pages * PAGE_SIZE);
	पूर्ण

	वापस fp;
पूर्ण

अटल व्योम bpf_prog_clone_मुक्त(काष्ठा bpf_prog *fp)
अणु
	/* aux was stolen by the other clone, so we cannot मुक्त
	 * it from this path! It will be मुक्तd eventually by the
	 * other program on release.
	 *
	 * At this poपूर्णांक, we करोn't need a deferred release since
	 * clone is guaranteed to not be locked.
	 */
	fp->aux = शून्य;
	fp->stats = शून्य;
	fp->active = शून्य;
	__bpf_prog_मुक्त(fp);
पूर्ण

व्योम bpf_jit_prog_release_other(काष्ठा bpf_prog *fp, काष्ठा bpf_prog *fp_other)
अणु
	/* We have to repoपूर्णांक aux->prog to self, as we करोn't
	 * know whether fp here is the clone or the original.
	 */
	fp->aux->prog = fp;
	bpf_prog_clone_मुक्त(fp_other);
पूर्ण

काष्ठा bpf_prog *bpf_jit_blind_स्थिरants(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_insn insn_buff[16], aux[2];
	काष्ठा bpf_prog *clone, *पंचांगp;
	पूर्णांक insn_delta, insn_cnt;
	काष्ठा bpf_insn *insn;
	पूर्णांक i, rewritten;

	अगर (!bpf_jit_blinding_enabled(prog) || prog->blinded)
		वापस prog;

	clone = bpf_prog_clone_create(prog, GFP_USER);
	अगर (!clone)
		वापस ERR_PTR(-ENOMEM);

	insn_cnt = clone->len;
	insn = clone->insnsi;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		/* We temporarily need to hold the original ld64 insn
		 * so that we can still access the first part in the
		 * second blinding run.
		 */
		अगर (insn[0].code == (BPF_LD | BPF_IMM | BPF_DW) &&
		    insn[1].code == 0)
			स_नकल(aux, insn, माप(aux));

		rewritten = bpf_jit_blind_insn(insn, aux, insn_buff,
						clone->aux->verअगरier_zext);
		अगर (!rewritten)
			जारी;

		पंचांगp = bpf_patch_insn_single(clone, i, insn_buff, rewritten);
		अगर (IS_ERR(पंचांगp)) अणु
			/* Patching may have repoपूर्णांकed aux->prog during
			 * पुनः_स्मृति from the original one, so we need to
			 * fix it up here on error.
			 */
			bpf_jit_prog_release_other(prog, clone);
			वापस पंचांगp;
		पूर्ण

		clone = पंचांगp;
		insn_delta = rewritten - 1;

		/* Walk new program and skip insns we just inserted. */
		insn = clone->insnsi + i + insn_delta;
		insn_cnt += insn_delta;
		i        += insn_delta;
	पूर्ण

	clone->blinded = 1;
	वापस clone;
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_JIT */

/* Base function क्रम offset calculation. Needs to go पूर्णांकo .text section,
 * thereक्रमe keeping it non-अटल as well; will also be used by JITs
 * anyway later on, so करो not let the compiler omit it. This also needs
 * to go पूर्णांकo kallsyms क्रम correlation from e.g. bpftool, so naming
 * must not change.
 */
noअंतरभूत u64 __bpf_call_base(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__bpf_call_base);

/* All UAPI available opcodes. */
#घोषणा BPF_INSN_MAP(INSN_2, INSN_3)		\
	/* 32 bit ALU operations. */		\
	/*   Register based. */			\
	INSN_3(ALU, ADD,  X),			\
	INSN_3(ALU, SUB,  X),			\
	INSN_3(ALU, AND,  X),			\
	INSN_3(ALU, OR,   X),			\
	INSN_3(ALU, LSH,  X),			\
	INSN_3(ALU, RSH,  X),			\
	INSN_3(ALU, XOR,  X),			\
	INSN_3(ALU, MUL,  X),			\
	INSN_3(ALU, MOV,  X),			\
	INSN_3(ALU, ARSH, X),			\
	INSN_3(ALU, DIV,  X),			\
	INSN_3(ALU, MOD,  X),			\
	INSN_2(ALU, NEG),			\
	INSN_3(ALU, END, TO_BE),		\
	INSN_3(ALU, END, TO_LE),		\
	/*   Immediate based. */		\
	INSN_3(ALU, ADD,  K),			\
	INSN_3(ALU, SUB,  K),			\
	INSN_3(ALU, AND,  K),			\
	INSN_3(ALU, OR,   K),			\
	INSN_3(ALU, LSH,  K),			\
	INSN_3(ALU, RSH,  K),			\
	INSN_3(ALU, XOR,  K),			\
	INSN_3(ALU, MUL,  K),			\
	INSN_3(ALU, MOV,  K),			\
	INSN_3(ALU, ARSH, K),			\
	INSN_3(ALU, DIV,  K),			\
	INSN_3(ALU, MOD,  K),			\
	/* 64 bit ALU operations. */		\
	/*   Register based. */			\
	INSN_3(ALU64, ADD,  X),			\
	INSN_3(ALU64, SUB,  X),			\
	INSN_3(ALU64, AND,  X),			\
	INSN_3(ALU64, OR,   X),			\
	INSN_3(ALU64, LSH,  X),			\
	INSN_3(ALU64, RSH,  X),			\
	INSN_3(ALU64, XOR,  X),			\
	INSN_3(ALU64, MUL,  X),			\
	INSN_3(ALU64, MOV,  X),			\
	INSN_3(ALU64, ARSH, X),			\
	INSN_3(ALU64, DIV,  X),			\
	INSN_3(ALU64, MOD,  X),			\
	INSN_2(ALU64, NEG),			\
	/*   Immediate based. */		\
	INSN_3(ALU64, ADD,  K),			\
	INSN_3(ALU64, SUB,  K),			\
	INSN_3(ALU64, AND,  K),			\
	INSN_3(ALU64, OR,   K),			\
	INSN_3(ALU64, LSH,  K),			\
	INSN_3(ALU64, RSH,  K),			\
	INSN_3(ALU64, XOR,  K),			\
	INSN_3(ALU64, MUL,  K),			\
	INSN_3(ALU64, MOV,  K),			\
	INSN_3(ALU64, ARSH, K),			\
	INSN_3(ALU64, DIV,  K),			\
	INSN_3(ALU64, MOD,  K),			\
	/* Call inकाष्ठाion. */			\
	INSN_2(JMP, CALL),			\
	/* Exit inकाष्ठाion. */			\
	INSN_2(JMP, EXIT),			\
	/* 32-bit Jump inकाष्ठाions. */		\
	/*   Register based. */			\
	INSN_3(JMP32, JEQ,  X),			\
	INSN_3(JMP32, JNE,  X),			\
	INSN_3(JMP32, JGT,  X),			\
	INSN_3(JMP32, JLT,  X),			\
	INSN_3(JMP32, JGE,  X),			\
	INSN_3(JMP32, JLE,  X),			\
	INSN_3(JMP32, JSGT, X),			\
	INSN_3(JMP32, JSLT, X),			\
	INSN_3(JMP32, JSGE, X),			\
	INSN_3(JMP32, JSLE, X),			\
	INSN_3(JMP32, JSET, X),			\
	/*   Immediate based. */		\
	INSN_3(JMP32, JEQ,  K),			\
	INSN_3(JMP32, JNE,  K),			\
	INSN_3(JMP32, JGT,  K),			\
	INSN_3(JMP32, JLT,  K),			\
	INSN_3(JMP32, JGE,  K),			\
	INSN_3(JMP32, JLE,  K),			\
	INSN_3(JMP32, JSGT, K),			\
	INSN_3(JMP32, JSLT, K),			\
	INSN_3(JMP32, JSGE, K),			\
	INSN_3(JMP32, JSLE, K),			\
	INSN_3(JMP32, JSET, K),			\
	/* Jump inकाष्ठाions. */		\
	/*   Register based. */			\
	INSN_3(JMP, JEQ,  X),			\
	INSN_3(JMP, JNE,  X),			\
	INSN_3(JMP, JGT,  X),			\
	INSN_3(JMP, JLT,  X),			\
	INSN_3(JMP, JGE,  X),			\
	INSN_3(JMP, JLE,  X),			\
	INSN_3(JMP, JSGT, X),			\
	INSN_3(JMP, JSLT, X),			\
	INSN_3(JMP, JSGE, X),			\
	INSN_3(JMP, JSLE, X),			\
	INSN_3(JMP, JSET, X),			\
	/*   Immediate based. */		\
	INSN_3(JMP, JEQ,  K),			\
	INSN_3(JMP, JNE,  K),			\
	INSN_3(JMP, JGT,  K),			\
	INSN_3(JMP, JLT,  K),			\
	INSN_3(JMP, JGE,  K),			\
	INSN_3(JMP, JLE,  K),			\
	INSN_3(JMP, JSGT, K),			\
	INSN_3(JMP, JSLT, K),			\
	INSN_3(JMP, JSGE, K),			\
	INSN_3(JMP, JSLE, K),			\
	INSN_3(JMP, JSET, K),			\
	INSN_2(JMP, JA),			\
	/* Store inकाष्ठाions. */		\
	/*   Register based. */			\
	INSN_3(STX, MEM,  B),			\
	INSN_3(STX, MEM,  H),			\
	INSN_3(STX, MEM,  W),			\
	INSN_3(STX, MEM,  DW),			\
	INSN_3(STX, ATOMIC, W),			\
	INSN_3(STX, ATOMIC, DW),		\
	/*   Immediate based. */		\
	INSN_3(ST, MEM, B),			\
	INSN_3(ST, MEM, H),			\
	INSN_3(ST, MEM, W),			\
	INSN_3(ST, MEM, DW),			\
	/* Load inकाष्ठाions. */		\
	/*   Register based. */			\
	INSN_3(LDX, MEM, B),			\
	INSN_3(LDX, MEM, H),			\
	INSN_3(LDX, MEM, W),			\
	INSN_3(LDX, MEM, DW),			\
	/*   Immediate based. */		\
	INSN_3(LD, IMM, DW)

bool bpf_opcode_in_insntable(u8 code)
अणु
#घोषणा BPF_INSN_2_TBL(x, y)    [BPF_##x | BPF_##y] = true
#घोषणा BPF_INSN_3_TBL(x, y, z) [BPF_##x | BPF_##y | BPF_##z] = true
	अटल स्थिर bool खुला_insntable[256] = अणु
		[0 ... 255] = false,
		/* Now overग_लिखो non-शेषs ... */
		BPF_INSN_MAP(BPF_INSN_2_TBL, BPF_INSN_3_TBL),
		/* UAPI exposed, but rewritten opcodes. cBPF carry-over. */
		[BPF_LD | BPF_ABS | BPF_B] = true,
		[BPF_LD | BPF_ABS | BPF_H] = true,
		[BPF_LD | BPF_ABS | BPF_W] = true,
		[BPF_LD | BPF_IND | BPF_B] = true,
		[BPF_LD | BPF_IND | BPF_H] = true,
		[BPF_LD | BPF_IND | BPF_W] = true,
	पूर्ण;
#अघोषित BPF_INSN_3_TBL
#अघोषित BPF_INSN_2_TBL
	वापस खुला_insntable[code];
पूर्ण

#अगर_अघोषित CONFIG_BPF_JIT_ALWAYS_ON
u64 __weak bpf_probe_पढ़ो_kernel(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
अणु
	स_रखो(dst, 0, size);
	वापस -EFAULT;
पूर्ण

/**
 *	__bpf_prog_run - run eBPF program on a given context
 *	@regs: is the array of MAX_BPF_EXT_REG eBPF pseuकरो-रेजिस्टरs
 *	@insn: is the array of eBPF inकाष्ठाions
 *
 * Decode and execute eBPF inकाष्ठाions.
 */
अटल u64 ___bpf_prog_run(u64 *regs, स्थिर काष्ठा bpf_insn *insn)
अणु
#घोषणा BPF_INSN_2_LBL(x, y)    [BPF_##x | BPF_##y] = &&x##_##y
#घोषणा BPF_INSN_3_LBL(x, y, z) [BPF_##x | BPF_##y | BPF_##z] = &&x##_##y##_##z
	अटल स्थिर व्योम * स्थिर jumptable[256] __annotate_jump_table = अणु
		[0 ... 255] = &&शेष_label,
		/* Now overग_लिखो non-शेषs ... */
		BPF_INSN_MAP(BPF_INSN_2_LBL, BPF_INSN_3_LBL),
		/* Non-UAPI available opcodes. */
		[BPF_JMP | BPF_CALL_ARGS] = &&JMP_CALL_ARGS,
		[BPF_JMP | BPF_TAIL_CALL] = &&JMP_TAIL_CALL,
		[BPF_LDX | BPF_PROBE_MEM | BPF_B] = &&LDX_PROBE_MEM_B,
		[BPF_LDX | BPF_PROBE_MEM | BPF_H] = &&LDX_PROBE_MEM_H,
		[BPF_LDX | BPF_PROBE_MEM | BPF_W] = &&LDX_PROBE_MEM_W,
		[BPF_LDX | BPF_PROBE_MEM | BPF_DW] = &&LDX_PROBE_MEM_DW,
	पूर्ण;
#अघोषित BPF_INSN_3_LBL
#अघोषित BPF_INSN_2_LBL
	u32 tail_call_cnt = 0;

#घोषणा CONT	 (अणु insn++; जाओ select_insn; पूर्ण)
#घोषणा CONT_JMP (अणु insn++; जाओ select_insn; पूर्ण)

select_insn:
	जाओ *jumptable[insn->code];

	/* ALU */
#घोषणा ALU(OPCODE, OP)			\
	ALU64_##OPCODE##_X:		\
		DST = DST OP SRC;	\
		CONT;			\
	ALU_##OPCODE##_X:		\
		DST = (u32) DST OP (u32) SRC;	\
		CONT;			\
	ALU64_##OPCODE##_K:		\
		DST = DST OP IMM;		\
		CONT;			\
	ALU_##OPCODE##_K:		\
		DST = (u32) DST OP (u32) IMM;	\
		CONT;

	ALU(ADD,  +)
	ALU(SUB,  -)
	ALU(AND,  &)
	ALU(OR,   |)
	ALU(LSH, <<)
	ALU(RSH, >>)
	ALU(XOR,  ^)
	ALU(MUL,  *)
#अघोषित ALU
	ALU_NEG:
		DST = (u32) -DST;
		CONT;
	ALU64_NEG:
		DST = -DST;
		CONT;
	ALU_MOV_X:
		DST = (u32) SRC;
		CONT;
	ALU_MOV_K:
		DST = (u32) IMM;
		CONT;
	ALU64_MOV_X:
		DST = SRC;
		CONT;
	ALU64_MOV_K:
		DST = IMM;
		CONT;
	LD_IMM_DW:
		DST = (u64) (u32) insn[0].imm | ((u64) (u32) insn[1].imm) << 32;
		insn++;
		CONT;
	ALU_ARSH_X:
		DST = (u64) (u32) (((s32) DST) >> SRC);
		CONT;
	ALU_ARSH_K:
		DST = (u64) (u32) (((s32) DST) >> IMM);
		CONT;
	ALU64_ARSH_X:
		(*(s64 *) &DST) >>= SRC;
		CONT;
	ALU64_ARSH_K:
		(*(s64 *) &DST) >>= IMM;
		CONT;
	ALU64_MOD_X:
		भाग64_u64_rem(DST, SRC, &AX);
		DST = AX;
		CONT;
	ALU_MOD_X:
		AX = (u32) DST;
		DST = करो_भाग(AX, (u32) SRC);
		CONT;
	ALU64_MOD_K:
		भाग64_u64_rem(DST, IMM, &AX);
		DST = AX;
		CONT;
	ALU_MOD_K:
		AX = (u32) DST;
		DST = करो_भाग(AX, (u32) IMM);
		CONT;
	ALU64_DIV_X:
		DST = भाग64_u64(DST, SRC);
		CONT;
	ALU_DIV_X:
		AX = (u32) DST;
		करो_भाग(AX, (u32) SRC);
		DST = (u32) AX;
		CONT;
	ALU64_DIV_K:
		DST = भाग64_u64(DST, IMM);
		CONT;
	ALU_DIV_K:
		AX = (u32) DST;
		करो_भाग(AX, (u32) IMM);
		DST = (u32) AX;
		CONT;
	ALU_END_TO_BE:
		चयन (IMM) अणु
		हाल 16:
			DST = (__क्रमce u16) cpu_to_be16(DST);
			अवरोध;
		हाल 32:
			DST = (__क्रमce u32) cpu_to_be32(DST);
			अवरोध;
		हाल 64:
			DST = (__क्रमce u64) cpu_to_be64(DST);
			अवरोध;
		पूर्ण
		CONT;
	ALU_END_TO_LE:
		चयन (IMM) अणु
		हाल 16:
			DST = (__क्रमce u16) cpu_to_le16(DST);
			अवरोध;
		हाल 32:
			DST = (__क्रमce u32) cpu_to_le32(DST);
			अवरोध;
		हाल 64:
			DST = (__क्रमce u64) cpu_to_le64(DST);
			अवरोध;
		पूर्ण
		CONT;

	/* CALL */
	JMP_CALL:
		/* Function call scratches BPF_R1-BPF_R5 रेजिस्टरs,
		 * preserves BPF_R6-BPF_R9, and stores वापस value
		 * पूर्णांकo BPF_R0.
		 */
		BPF_R0 = (__bpf_call_base + insn->imm)(BPF_R1, BPF_R2, BPF_R3,
						       BPF_R4, BPF_R5);
		CONT;

	JMP_CALL_ARGS:
		BPF_R0 = (__bpf_call_base_args + insn->imm)(BPF_R1, BPF_R2,
							    BPF_R3, BPF_R4,
							    BPF_R5,
							    insn + insn->off + 1);
		CONT;

	JMP_TAIL_CALL: अणु
		काष्ठा bpf_map *map = (काष्ठा bpf_map *) (अचिन्हित दीर्घ) BPF_R2;
		काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
		काष्ठा bpf_prog *prog;
		u32 index = BPF_R3;

		अगर (unlikely(index >= array->map.max_entries))
			जाओ out;
		अगर (unlikely(tail_call_cnt > MAX_TAIL_CALL_CNT))
			जाओ out;

		tail_call_cnt++;

		prog = READ_ONCE(array->ptrs[index]);
		अगर (!prog)
			जाओ out;

		/* ARG1 at this poपूर्णांक is guaranteed to poपूर्णांक to CTX from
		 * the verअगरier side due to the fact that the tail call is
		 * handled like a helper, that is, bpf_tail_call_proto,
		 * where arg1_type is ARG_PTR_TO_CTX.
		 */
		insn = prog->insnsi;
		जाओ select_insn;
out:
		CONT;
	पूर्ण
	JMP_JA:
		insn += insn->off;
		CONT;
	JMP_EXIT:
		वापस BPF_R0;
	/* JMP */
#घोषणा COND_JMP(SIGN, OPCODE, CMP_OP)				\
	JMP_##OPCODE##_X:					\
		अगर ((SIGN##64) DST CMP_OP (SIGN##64) SRC) अणु	\
			insn += insn->off;			\
			CONT_JMP;				\
		पूर्ण						\
		CONT;						\
	JMP32_##OPCODE##_X:					\
		अगर ((SIGN##32) DST CMP_OP (SIGN##32) SRC) अणु	\
			insn += insn->off;			\
			CONT_JMP;				\
		पूर्ण						\
		CONT;						\
	JMP_##OPCODE##_K:					\
		अगर ((SIGN##64) DST CMP_OP (SIGN##64) IMM) अणु	\
			insn += insn->off;			\
			CONT_JMP;				\
		पूर्ण						\
		CONT;						\
	JMP32_##OPCODE##_K:					\
		अगर ((SIGN##32) DST CMP_OP (SIGN##32) IMM) अणु	\
			insn += insn->off;			\
			CONT_JMP;				\
		पूर्ण						\
		CONT;
	COND_JMP(u, JEQ, ==)
	COND_JMP(u, JNE, !=)
	COND_JMP(u, JGT, >)
	COND_JMP(u, JLT, <)
	COND_JMP(u, JGE, >=)
	COND_JMP(u, JLE, <=)
	COND_JMP(u, JSET, &)
	COND_JMP(s, JSGT, >)
	COND_JMP(s, JSLT, <)
	COND_JMP(s, JSGE, >=)
	COND_JMP(s, JSLE, <=)
#अघोषित COND_JMP
	/* STX and ST and LDX*/
#घोषणा LDST(SIZEOP, SIZE)						\
	STX_MEM_##SIZEOP:						\
		*(SIZE *)(अचिन्हित दीर्घ) (DST + insn->off) = SRC;	\
		CONT;							\
	ST_MEM_##SIZEOP:						\
		*(SIZE *)(अचिन्हित दीर्घ) (DST + insn->off) = IMM;	\
		CONT;							\
	LDX_MEM_##SIZEOP:						\
		DST = *(SIZE *)(अचिन्हित दीर्घ) (SRC + insn->off);	\
		CONT;

	LDST(B,   u8)
	LDST(H,  u16)
	LDST(W,  u32)
	LDST(DW, u64)
#अघोषित LDST
#घोषणा LDX_PROBE(SIZEOP, SIZE)							\
	LDX_PROBE_MEM_##SIZEOP:							\
		bpf_probe_पढ़ो_kernel(&DST, SIZE, (स्थिर व्योम *)(दीर्घ) (SRC + insn->off));	\
		CONT;
	LDX_PROBE(B,  1)
	LDX_PROBE(H,  2)
	LDX_PROBE(W,  4)
	LDX_PROBE(DW, 8)
#अघोषित LDX_PROBE

#घोषणा ATOMIC_ALU_OP(BOP, KOP)						\
		हाल BOP:						\
			अगर (BPF_SIZE(insn->code) == BPF_W)		\
				atomic_##KOP((u32) SRC, (atomic_t *)(अचिन्हित दीर्घ) \
					     (DST + insn->off));	\
			अन्यथा						\
				atomic64_##KOP((u64) SRC, (atomic64_t *)(अचिन्हित दीर्घ) \
					       (DST + insn->off));	\
			अवरोध;						\
		हाल BOP | BPF_FETCH:					\
			अगर (BPF_SIZE(insn->code) == BPF_W)		\
				SRC = (u32) atomic_fetch_##KOP(		\
					(u32) SRC,			\
					(atomic_t *)(अचिन्हित दीर्घ) (DST + insn->off)); \
			अन्यथा						\
				SRC = (u64) atomic64_fetch_##KOP(	\
					(u64) SRC,			\
					(atomic64_t *)(अचिन्हित दीर्घ) (DST + insn->off)); \
			अवरोध;

	STX_ATOMIC_DW:
	STX_ATOMIC_W:
		चयन (IMM) अणु
		ATOMIC_ALU_OP(BPF_ADD, add)
		ATOMIC_ALU_OP(BPF_AND, and)
		ATOMIC_ALU_OP(BPF_OR, or)
		ATOMIC_ALU_OP(BPF_XOR, xor)
#अघोषित ATOMIC_ALU_OP

		हाल BPF_XCHG:
			अगर (BPF_SIZE(insn->code) == BPF_W)
				SRC = (u32) atomic_xchg(
					(atomic_t *)(अचिन्हित दीर्घ) (DST + insn->off),
					(u32) SRC);
			अन्यथा
				SRC = (u64) atomic64_xchg(
					(atomic64_t *)(अचिन्हित दीर्घ) (DST + insn->off),
					(u64) SRC);
			अवरोध;
		हाल BPF_CMPXCHG:
			अगर (BPF_SIZE(insn->code) == BPF_W)
				BPF_R0 = (u32) atomic_cmpxchg(
					(atomic_t *)(अचिन्हित दीर्घ) (DST + insn->off),
					(u32) BPF_R0, (u32) SRC);
			अन्यथा
				BPF_R0 = (u64) atomic64_cmpxchg(
					(atomic64_t *)(अचिन्हित दीर्घ) (DST + insn->off),
					(u64) BPF_R0, (u64) SRC);
			अवरोध;

		शेष:
			जाओ शेष_label;
		पूर्ण
		CONT;

	शेष_label:
		/* If we ever reach this, we have a bug somewhere. Die hard here
		 * instead of just वापसing 0; we could be somewhere in a subprog,
		 * so execution could जारी otherwise which we करो /not/ want.
		 *
		 * Note, verअगरier whitelists all opcodes in bpf_opcode_in_insntable().
		 */
		pr_warn("BPF interpreter: unknown opcode %02x (imm: 0x%x)\n",
			insn->code, insn->imm);
		BUG_ON(1);
		वापस 0;
पूर्ण

#घोषणा PROG_NAME(stack_size) __bpf_prog_run##stack_size
#घोषणा DEFINE_BPF_PROG_RUN(stack_size) \
अटल अचिन्हित पूर्णांक PROG_NAME(stack_size)(स्थिर व्योम *ctx, स्थिर काष्ठा bpf_insn *insn) \
अणु \
	u64 stack[stack_size / माप(u64)]; \
	u64 regs[MAX_BPF_EXT_REG]; \
\
	FP = (u64) (अचिन्हित दीर्घ) &stack[ARRAY_SIZE(stack)]; \
	ARG1 = (u64) (अचिन्हित दीर्घ) ctx; \
	वापस ___bpf_prog_run(regs, insn); \
पूर्ण

#घोषणा PROG_NAME_ARGS(stack_size) __bpf_prog_run_args##stack_size
#घोषणा DEFINE_BPF_PROG_RUN_ARGS(stack_size) \
अटल u64 PROG_NAME_ARGS(stack_size)(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5, \
				      स्थिर काष्ठा bpf_insn *insn) \
अणु \
	u64 stack[stack_size / माप(u64)]; \
	u64 regs[MAX_BPF_EXT_REG]; \
\
	FP = (u64) (अचिन्हित दीर्घ) &stack[ARRAY_SIZE(stack)]; \
	BPF_R1 = r1; \
	BPF_R2 = r2; \
	BPF_R3 = r3; \
	BPF_R4 = r4; \
	BPF_R5 = r5; \
	वापस ___bpf_prog_run(regs, insn); \
पूर्ण

#घोषणा EVAL1(FN, X) FN(X)
#घोषणा EVAL2(FN, X, Y...) FN(X) EVAL1(FN, Y)
#घोषणा EVAL3(FN, X, Y...) FN(X) EVAL2(FN, Y)
#घोषणा EVAL4(FN, X, Y...) FN(X) EVAL3(FN, Y)
#घोषणा EVAL5(FN, X, Y...) FN(X) EVAL4(FN, Y)
#घोषणा EVAL6(FN, X, Y...) FN(X) EVAL5(FN, Y)

EVAL6(DEFINE_BPF_PROG_RUN, 32, 64, 96, 128, 160, 192);
EVAL6(DEFINE_BPF_PROG_RUN, 224, 256, 288, 320, 352, 384);
EVAL4(DEFINE_BPF_PROG_RUN, 416, 448, 480, 512);

EVAL6(DEFINE_BPF_PROG_RUN_ARGS, 32, 64, 96, 128, 160, 192);
EVAL6(DEFINE_BPF_PROG_RUN_ARGS, 224, 256, 288, 320, 352, 384);
EVAL4(DEFINE_BPF_PROG_RUN_ARGS, 416, 448, 480, 512);

#घोषणा PROG_NAME_LIST(stack_size) PROG_NAME(stack_size),

अटल अचिन्हित पूर्णांक (*पूर्णांकerpreters[])(स्थिर व्योम *ctx,
				      स्थिर काष्ठा bpf_insn *insn) = अणु
EVAL6(PROG_NAME_LIST, 32, 64, 96, 128, 160, 192)
EVAL6(PROG_NAME_LIST, 224, 256, 288, 320, 352, 384)
EVAL4(PROG_NAME_LIST, 416, 448, 480, 512)
पूर्ण;
#अघोषित PROG_NAME_LIST
#घोषणा PROG_NAME_LIST(stack_size) PROG_NAME_ARGS(stack_size),
अटल u64 (*पूर्णांकerpreters_args[])(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5,
				  स्थिर काष्ठा bpf_insn *insn) = अणु
EVAL6(PROG_NAME_LIST, 32, 64, 96, 128, 160, 192)
EVAL6(PROG_NAME_LIST, 224, 256, 288, 320, 352, 384)
EVAL4(PROG_NAME_LIST, 416, 448, 480, 512)
पूर्ण;
#अघोषित PROG_NAME_LIST

व्योम bpf_patch_call_args(काष्ठा bpf_insn *insn, u32 stack_depth)
अणु
	stack_depth = max_t(u32, stack_depth, 1);
	insn->off = (s16) insn->imm;
	insn->imm = पूर्णांकerpreters_args[(round_up(stack_depth, 32) / 32) - 1] -
		__bpf_call_base_args;
	insn->code = BPF_JMP | BPF_CALL_ARGS;
पूर्ण

#अन्यथा
अटल अचिन्हित पूर्णांक __bpf_prog_ret0_warn(स्थिर व्योम *ctx,
					 स्थिर काष्ठा bpf_insn *insn)
अणु
	/* If this handler ever माला_लो executed, then BPF_JIT_ALWAYS_ON
	 * is not working properly, so warn about it!
	 */
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण
#पूर्ण_अगर

bool bpf_prog_array_compatible(काष्ठा bpf_array *array,
			       स्थिर काष्ठा bpf_prog *fp)
अणु
	अगर (fp->kprobe_override)
		वापस false;

	अगर (!array->aux->type) अणु
		/* There's no owner yet where we could check क्रम
		 * compatibility.
		 */
		array->aux->type  = fp->type;
		array->aux->jited = fp->jited;
		वापस true;
	पूर्ण

	वापस array->aux->type  == fp->type &&
	       array->aux->jited == fp->jited;
पूर्ण

अटल पूर्णांक bpf_check_tail_call(स्थिर काष्ठा bpf_prog *fp)
अणु
	काष्ठा bpf_prog_aux *aux = fp->aux;
	पूर्णांक i, ret = 0;

	mutex_lock(&aux->used_maps_mutex);
	क्रम (i = 0; i < aux->used_map_cnt; i++) अणु
		काष्ठा bpf_map *map = aux->used_maps[i];
		काष्ठा bpf_array *array;

		अगर (map->map_type != BPF_MAP_TYPE_PROG_ARRAY)
			जारी;

		array = container_of(map, काष्ठा bpf_array, map);
		अगर (!bpf_prog_array_compatible(array, fp)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&aux->used_maps_mutex);
	वापस ret;
पूर्ण

अटल व्योम bpf_prog_select_func(काष्ठा bpf_prog *fp)
अणु
#अगर_अघोषित CONFIG_BPF_JIT_ALWAYS_ON
	u32 stack_depth = max_t(u32, fp->aux->stack_depth, 1);

	fp->bpf_func = पूर्णांकerpreters[(round_up(stack_depth, 32) / 32) - 1];
#अन्यथा
	fp->bpf_func = __bpf_prog_ret0_warn;
#पूर्ण_अगर
पूर्ण

/**
 *	bpf_prog_select_runसमय - select exec runसमय क्रम BPF program
 *	@fp: bpf_prog populated with पूर्णांकernal BPF program
 *	@err: poपूर्णांकer to error variable
 *
 * Try to JIT eBPF program, अगर JIT is not available, use पूर्णांकerpreter.
 * The BPF program will be executed via BPF_PROG_RUN() macro.
 */
काष्ठा bpf_prog *bpf_prog_select_runसमय(काष्ठा bpf_prog *fp, पूर्णांक *err)
अणु
	/* In हाल of BPF to BPF calls, verअगरier did all the prep
	 * work with regards to JITing, etc.
	 */
	bool jit_needed = false;

	अगर (fp->bpf_func)
		जाओ finalize;

	अगर (IS_ENABLED(CONFIG_BPF_JIT_ALWAYS_ON) ||
	    bpf_prog_has_kfunc_call(fp))
		jit_needed = true;

	bpf_prog_select_func(fp);

	/* eBPF JITs can reग_लिखो the program in हाल स्थिरant
	 * blinding is active. However, in हाल of error during
	 * blinding, bpf_पूर्णांक_jit_compile() must always वापस a
	 * valid program, which in this हाल would simply not
	 * be JITed, but falls back to the पूर्णांकerpreter.
	 */
	अगर (!bpf_prog_is_dev_bound(fp->aux)) अणु
		*err = bpf_prog_alloc_jited_linfo(fp);
		अगर (*err)
			वापस fp;

		fp = bpf_पूर्णांक_jit_compile(fp);
		bpf_prog_jit_attempt_करोne(fp);
		अगर (!fp->jited && jit_needed) अणु
			*err = -ENOTSUPP;
			वापस fp;
		पूर्ण
	पूर्ण अन्यथा अणु
		*err = bpf_prog_offload_compile(fp);
		अगर (*err)
			वापस fp;
	पूर्ण

finalize:
	bpf_prog_lock_ro(fp);

	/* The tail call compatibility check can only be करोne at
	 * this late stage as we need to determine, अगर we deal
	 * with JITed or non JITed program concatenations and not
	 * all eBPF JITs might immediately support all features.
	 */
	*err = bpf_check_tail_call(fp);

	वापस fp;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_select_runसमय);

अटल अचिन्हित पूर्णांक __bpf_prog_ret1(स्थिर व्योम *ctx,
				    स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा bpf_prog_dummy अणु
	काष्ठा bpf_prog prog;
पूर्ण dummy_bpf_prog = अणु
	.prog = अणु
		.bpf_func = __bpf_prog_ret1,
	पूर्ण,
पूर्ण;

/* to aव्योम allocating empty bpf_prog_array क्रम cgroups that
 * करोn't have bpf program attached use one global 'empty_prog_array'
 * It will not be modअगरied the caller of bpf_prog_array_alloc()
 * (since caller requested prog_cnt == 0)
 * that poपूर्णांकer should be 'freed' by bpf_prog_array_मुक्त()
 */
अटल काष्ठा अणु
	काष्ठा bpf_prog_array hdr;
	काष्ठा bpf_prog *null_prog;
पूर्ण empty_prog_array = अणु
	.null_prog = शून्य,
पूर्ण;

काष्ठा bpf_prog_array *bpf_prog_array_alloc(u32 prog_cnt, gfp_t flags)
अणु
	अगर (prog_cnt)
		वापस kzalloc(माप(काष्ठा bpf_prog_array) +
			       माप(काष्ठा bpf_prog_array_item) *
			       (prog_cnt + 1),
			       flags);

	वापस &empty_prog_array.hdr;
पूर्ण

व्योम bpf_prog_array_मुक्त(काष्ठा bpf_prog_array *progs)
अणु
	अगर (!progs || progs == &empty_prog_array.hdr)
		वापस;
	kमुक्त_rcu(progs, rcu);
पूर्ण

पूर्णांक bpf_prog_array_length(काष्ठा bpf_prog_array *array)
अणु
	काष्ठा bpf_prog_array_item *item;
	u32 cnt = 0;

	क्रम (item = array->items; item->prog; item++)
		अगर (item->prog != &dummy_bpf_prog.prog)
			cnt++;
	वापस cnt;
पूर्ण

bool bpf_prog_array_is_empty(काष्ठा bpf_prog_array *array)
अणु
	काष्ठा bpf_prog_array_item *item;

	क्रम (item = array->items; item->prog; item++)
		अगर (item->prog != &dummy_bpf_prog.prog)
			वापस false;
	वापस true;
पूर्ण

अटल bool bpf_prog_array_copy_core(काष्ठा bpf_prog_array *array,
				     u32 *prog_ids,
				     u32 request_cnt)
अणु
	काष्ठा bpf_prog_array_item *item;
	पूर्णांक i = 0;

	क्रम (item = array->items; item->prog; item++) अणु
		अगर (item->prog == &dummy_bpf_prog.prog)
			जारी;
		prog_ids[i] = item->prog->aux->id;
		अगर (++i == request_cnt) अणु
			item++;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस !!(item->prog);
पूर्ण

पूर्णांक bpf_prog_array_copy_to_user(काष्ठा bpf_prog_array *array,
				__u32 __user *prog_ids, u32 cnt)
अणु
	अचिन्हित दीर्घ err = 0;
	bool nospc;
	u32 *ids;

	/* users of this function are करोing:
	 * cnt = bpf_prog_array_length();
	 * अगर (cnt > 0)
	 *     bpf_prog_array_copy_to_user(..., cnt);
	 * so below kसुस्मृति करोesn't need extra cnt > 0 check.
	 */
	ids = kसुस्मृति(cnt, माप(u32), GFP_USER | __GFP_NOWARN);
	अगर (!ids)
		वापस -ENOMEM;
	nospc = bpf_prog_array_copy_core(array, ids, cnt);
	err = copy_to_user(prog_ids, ids, cnt * माप(u32));
	kमुक्त(ids);
	अगर (err)
		वापस -EFAULT;
	अगर (nospc)
		वापस -ENOSPC;
	वापस 0;
पूर्ण

व्योम bpf_prog_array_delete_safe(काष्ठा bpf_prog_array *array,
				काष्ठा bpf_prog *old_prog)
अणु
	काष्ठा bpf_prog_array_item *item;

	क्रम (item = array->items; item->prog; item++)
		अगर (item->prog == old_prog) अणु
			WRITE_ONCE(item->prog, &dummy_bpf_prog.prog);
			अवरोध;
		पूर्ण
पूर्ण

/**
 * bpf_prog_array_delete_safe_at() - Replaces the program at the given
 *                                   index पूर्णांकo the program array with
 *                                   a dummy no-op program.
 * @array: a bpf_prog_array
 * @index: the index of the program to replace
 *
 * Skips over dummy programs, by not counting them, when calculating
 * the position of the program to replace.
 *
 * Return:
 * * 0		- Success
 * * -EINVAL	- Invalid index value. Must be a non-negative पूर्णांकeger.
 * * -ENOENT	- Index out of range
 */
पूर्णांक bpf_prog_array_delete_safe_at(काष्ठा bpf_prog_array *array, पूर्णांक index)
अणु
	वापस bpf_prog_array_update_at(array, index, &dummy_bpf_prog.prog);
पूर्ण

/**
 * bpf_prog_array_update_at() - Updates the program at the given index
 *                              पूर्णांकo the program array.
 * @array: a bpf_prog_array
 * @index: the index of the program to update
 * @prog: the program to insert पूर्णांकo the array
 *
 * Skips over dummy programs, by not counting them, when calculating
 * the position of the program to update.
 *
 * Return:
 * * 0		- Success
 * * -EINVAL	- Invalid index value. Must be a non-negative पूर्णांकeger.
 * * -ENOENT	- Index out of range
 */
पूर्णांक bpf_prog_array_update_at(काष्ठा bpf_prog_array *array, पूर्णांक index,
			     काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_array_item *item;

	अगर (unlikely(index < 0))
		वापस -EINVAL;

	क्रम (item = array->items; item->prog; item++) अणु
		अगर (item->prog == &dummy_bpf_prog.prog)
			जारी;
		अगर (!index) अणु
			WRITE_ONCE(item->prog, prog);
			वापस 0;
		पूर्ण
		index--;
	पूर्ण
	वापस -ENOENT;
पूर्ण

पूर्णांक bpf_prog_array_copy(काष्ठा bpf_prog_array *old_array,
			काष्ठा bpf_prog *exclude_prog,
			काष्ठा bpf_prog *include_prog,
			काष्ठा bpf_prog_array **new_array)
अणु
	पूर्णांक new_prog_cnt, carry_prog_cnt = 0;
	काष्ठा bpf_prog_array_item *existing;
	काष्ठा bpf_prog_array *array;
	bool found_exclude = false;
	पूर्णांक new_prog_idx = 0;

	/* Figure out how many existing progs we need to carry over to
	 * the new array.
	 */
	अगर (old_array) अणु
		existing = old_array->items;
		क्रम (; existing->prog; existing++) अणु
			अगर (existing->prog == exclude_prog) अणु
				found_exclude = true;
				जारी;
			पूर्ण
			अगर (existing->prog != &dummy_bpf_prog.prog)
				carry_prog_cnt++;
			अगर (existing->prog == include_prog)
				वापस -EEXIST;
		पूर्ण
	पूर्ण

	अगर (exclude_prog && !found_exclude)
		वापस -ENOENT;

	/* How many progs (not शून्य) will be in the new array? */
	new_prog_cnt = carry_prog_cnt;
	अगर (include_prog)
		new_prog_cnt += 1;

	/* Do we have any prog (not शून्य) in the new array? */
	अगर (!new_prog_cnt) अणु
		*new_array = शून्य;
		वापस 0;
	पूर्ण

	/* +1 as the end of prog_array is marked with शून्य */
	array = bpf_prog_array_alloc(new_prog_cnt + 1, GFP_KERNEL);
	अगर (!array)
		वापस -ENOMEM;

	/* Fill in the new prog array */
	अगर (carry_prog_cnt) अणु
		existing = old_array->items;
		क्रम (; existing->prog; existing++)
			अगर (existing->prog != exclude_prog &&
			    existing->prog != &dummy_bpf_prog.prog) अणु
				array->items[new_prog_idx++].prog =
					existing->prog;
			पूर्ण
	पूर्ण
	अगर (include_prog)
		array->items[new_prog_idx++].prog = include_prog;
	array->items[new_prog_idx].prog = शून्य;
	*new_array = array;
	वापस 0;
पूर्ण

पूर्णांक bpf_prog_array_copy_info(काष्ठा bpf_prog_array *array,
			     u32 *prog_ids, u32 request_cnt,
			     u32 *prog_cnt)
अणु
	u32 cnt = 0;

	अगर (array)
		cnt = bpf_prog_array_length(array);

	*prog_cnt = cnt;

	/* वापस early अगर user requested only program count or nothing to copy */
	अगर (!request_cnt || !cnt)
		वापस 0;

	/* this function is called under trace/bpf_trace.c: bpf_event_mutex */
	वापस bpf_prog_array_copy_core(array, prog_ids, request_cnt) ? -ENOSPC
								     : 0;
पूर्ण

व्योम __bpf_मुक्त_used_maps(काष्ठा bpf_prog_aux *aux,
			  काष्ठा bpf_map **used_maps, u32 len)
अणु
	काष्ठा bpf_map *map;
	u32 i;

	क्रम (i = 0; i < len; i++) अणु
		map = used_maps[i];
		अगर (map->ops->map_poke_untrack)
			map->ops->map_poke_untrack(map, aux);
		bpf_map_put(map);
	पूर्ण
पूर्ण

अटल व्योम bpf_मुक्त_used_maps(काष्ठा bpf_prog_aux *aux)
अणु
	__bpf_मुक्त_used_maps(aux, aux->used_maps, aux->used_map_cnt);
	kमुक्त(aux->used_maps);
पूर्ण

व्योम __bpf_मुक्त_used_btfs(काष्ठा bpf_prog_aux *aux,
			  काष्ठा btf_mod_pair *used_btfs, u32 len)
अणु
#अगर_घोषित CONFIG_BPF_SYSCALL
	काष्ठा btf_mod_pair *btf_mod;
	u32 i;

	क्रम (i = 0; i < len; i++) अणु
		btf_mod = &used_btfs[i];
		अगर (btf_mod->module)
			module_put(btf_mod->module);
		btf_put(btf_mod->btf);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम bpf_मुक्त_used_btfs(काष्ठा bpf_prog_aux *aux)
अणु
	__bpf_मुक्त_used_btfs(aux, aux->used_btfs, aux->used_btf_cnt);
	kमुक्त(aux->used_btfs);
पूर्ण

अटल व्योम bpf_prog_मुक्त_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bpf_prog_aux *aux;
	पूर्णांक i;

	aux = container_of(work, काष्ठा bpf_prog_aux, work);
	bpf_मुक्त_used_maps(aux);
	bpf_मुक्त_used_btfs(aux);
	अगर (bpf_prog_is_dev_bound(aux))
		bpf_prog_offload_destroy(aux->prog);
#अगर_घोषित CONFIG_PERF_EVENTS
	अगर (aux->prog->has_callchain_buf)
		put_callchain_buffers();
#पूर्ण_अगर
	अगर (aux->dst_trampoline)
		bpf_trampoline_put(aux->dst_trampoline);
	क्रम (i = 0; i < aux->func_cnt; i++)
		bpf_jit_मुक्त(aux->func[i]);
	अगर (aux->func_cnt) अणु
		kमुक्त(aux->func);
		bpf_prog_unlock_मुक्त(aux->prog);
	पूर्ण अन्यथा अणु
		bpf_jit_मुक्त(aux->prog);
	पूर्ण
पूर्ण

/* Free पूर्णांकernal BPF program */
व्योम bpf_prog_मुक्त(काष्ठा bpf_prog *fp)
अणु
	काष्ठा bpf_prog_aux *aux = fp->aux;

	अगर (aux->dst_prog)
		bpf_prog_put(aux->dst_prog);
	INIT_WORK(&aux->work, bpf_prog_मुक्त_deferred);
	schedule_work(&aux->work);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_मुक्त);

/* RNG क्रम unpriviledged user space with separated state from pअक्रमom_u32(). */
अटल DEFINE_PER_CPU(काष्ठा rnd_state, bpf_user_rnd_state);

व्योम bpf_user_rnd_init_once(व्योम)
अणु
	pअक्रमom_init_once(&bpf_user_rnd_state);
पूर्ण

BPF_CALL_0(bpf_user_rnd_u32)
अणु
	/* Should someone ever have the rather unwise idea to use some
	 * of the रेजिस्टरs passed पूर्णांकo this function, then note that
	 * this function is called from native eBPF and classic-to-eBPF
	 * transक्रमmations. Register assignments from both sides are
	 * dअगरferent, f.e. classic always sets fn(ctx, A, X) here.
	 */
	काष्ठा rnd_state *state;
	u32 res;

	state = &get_cpu_var(bpf_user_rnd_state);
	res = pअक्रमom_u32_state(state);
	put_cpu_var(bpf_user_rnd_state);

	वापस res;
पूर्ण

BPF_CALL_0(bpf_get_raw_cpu_id)
अणु
	वापस raw_smp_processor_id();
पूर्ण

/* Weak definitions of helper functions in हाल we करोn't have bpf syscall. */
स्थिर काष्ठा bpf_func_proto bpf_map_lookup_elem_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_map_update_elem_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_map_delete_elem_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_map_push_elem_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_map_pop_elem_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_map_peek_elem_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_spin_lock_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_spin_unlock_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_jअगरfies64_proto __weak;

स्थिर काष्ठा bpf_func_proto bpf_get_pअक्रमom_u32_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_smp_processor_id_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_numa_node_id_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_ns_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_boot_ns_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_coarse_ns_proto __weak;

स्थिर काष्ठा bpf_func_proto bpf_get_current_pid_tgid_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_current_uid_gid_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_current_comm_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_current_cgroup_id_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_current_ancestor_cgroup_id_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_local_storage_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_get_ns_current_pid_tgid_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_snम_लिखो_btf_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_seq_म_लिखो_btf_proto __weak;

स्थिर काष्ठा bpf_func_proto * __weak bpf_get_trace_prपूर्णांकk_proto(व्योम)
अणु
	वापस शून्य;
पूर्ण

u64 __weak
bpf_event_output(काष्ठा bpf_map *map, u64 flags, व्योम *meta, u64 meta_size,
		 व्योम *ctx, u64 ctx_size, bpf_ctx_copy_t ctx_copy)
अणु
	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_event_output);

/* Always built-in helper functions. */
स्थिर काष्ठा bpf_func_proto bpf_tail_call_proto = अणु
	.func		= शून्य,
	.gpl_only	= false,
	.ret_type	= RET_VOID,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

/* Stub क्रम JITs that only support cBPF. eBPF programs are पूर्णांकerpreted.
 * It is encouraged to implement bpf_पूर्णांक_jit_compile() instead, so that
 * eBPF and implicitly also cBPF can get JITed!
 */
काष्ठा bpf_prog * __weak bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	वापस prog;
पूर्ण

/* Stub क्रम JITs that support eBPF. All cBPF code माला_लो transक्रमmed पूर्णांकo
 * eBPF by the kernel and is later compiled by bpf_पूर्णांक_jit_compile().
 */
व्योम __weak bpf_jit_compile(काष्ठा bpf_prog *prog)
अणु
पूर्ण

bool __weak bpf_helper_changes_pkt_data(व्योम *func)
अणु
	वापस false;
पूर्ण

/* Return TRUE अगर the JIT backend wants verअगरier to enable sub-रेजिस्टर usage
 * analysis code and wants explicit zero extension inserted by verअगरier.
 * Otherwise, वापस FALSE.
 *
 * The verअगरier inserts an explicit zero extension after BPF_CMPXCHGs even अगर
 * you करोn't override this. JITs that don't want these extra insns can detect
 * them using insn_is_zext.
 */
bool __weak bpf_jit_needs_zext(व्योम)
अणु
	वापस false;
पूर्ण

bool __weak bpf_jit_supports_kfunc_call(व्योम)
अणु
	वापस false;
पूर्ण

/* To execute LD_ABS/LD_IND inकाष्ठाions __bpf_prog_run() may call
 * skb_copy_bits(), so provide a weak definition of it क्रम NET-less config.
 */
पूर्णांक __weak skb_copy_bits(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, व्योम *to,
			 पूर्णांक len)
अणु
	वापस -EFAULT;
पूर्ण

पूर्णांक __weak bpf_arch_text_poke(व्योम *ip, क्रमागत bpf_text_poke_type t,
			      व्योम *addr1, व्योम *addr2)
अणु
	वापस -ENOTSUPP;
पूर्ण

DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);
EXPORT_SYMBOL(bpf_stats_enabled_key);

/* All definitions of tracepoपूर्णांकs related to BPF. */
#घोषणा CREATE_TRACE_POINTS
#समावेश <linux/bpf_trace.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(xdp_exception);
EXPORT_TRACEPOINT_SYMBOL_GPL(xdp_bulk_tx);
