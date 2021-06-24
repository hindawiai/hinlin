<शैली गुरु>
/*
 * Copyright (c) 2008 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *    Keith Packard <keithp@keithp.com>
 *    Mika Kuoppala <mika.kuoppala@पूर्णांकel.com>
 *
 */

#समावेश <linux/ascii85.h>
#समावेश <linux/nmi.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/utsname.h>
#समावेश <linux/zlib.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "display/intel_atomic.h"
#समावेश "display/intel_csr.h"
#समावेश "display/intel_overlay.h"

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_lmem.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"

#समावेश "i915_drv.h"
#समावेश "i915_gpu_error.h"
#समावेश "i915_memcpy.h"
#समावेश "i915_scatterlist.h"

#घोषणा ALLOW_FAIL (GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN)
#घोषणा ATOMIC_MAYFAIL (GFP_ATOMIC | __GFP_NOWARN)

अटल व्योम __sg_set_buf(काष्ठा scatterlist *sg,
			 व्योम *addr, अचिन्हित पूर्णांक len, loff_t it)
अणु
	sg->page_link = (अचिन्हित दीर्घ)virt_to_page(addr);
	sg->offset = offset_in_page(addr);
	sg->length = len;
	sg->dma_address = it;
पूर्ण

अटल bool __i915_error_grow(काष्ठा drm_i915_error_state_buf *e, माप_प्रकार len)
अणु
	अगर (!len)
		वापस false;

	अगर (e->bytes + len + 1 <= e->size)
		वापस true;

	अगर (e->bytes) अणु
		__sg_set_buf(e->cur++, e->buf, e->bytes, e->iter);
		e->iter += e->bytes;
		e->buf = शून्य;
		e->bytes = 0;
	पूर्ण

	अगर (e->cur == e->end) अणु
		काष्ठा scatterlist *sgl;

		sgl = (typeof(sgl))__get_मुक्त_page(ALLOW_FAIL);
		अगर (!sgl) अणु
			e->err = -ENOMEM;
			वापस false;
		पूर्ण

		अगर (e->cur) अणु
			e->cur->offset = 0;
			e->cur->length = 0;
			e->cur->page_link =
				(अचिन्हित दीर्घ)sgl | SG_CHAIN;
		पूर्ण अन्यथा अणु
			e->sgl = sgl;
		पूर्ण

		e->cur = sgl;
		e->end = sgl + SG_MAX_SINGLE_ALLOC - 1;
	पूर्ण

	e->size = ALIGN(len + 1, SZ_64K);
	e->buf = kदो_स्मृति(e->size, ALLOW_FAIL);
	अगर (!e->buf) अणु
		e->size = PAGE_ALIGN(len + 1);
		e->buf = kदो_स्मृति(e->size, GFP_KERNEL);
	पूर्ण
	अगर (!e->buf) अणु
		e->err = -ENOMEM;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

__म_लिखो(2, 0)
अटल व्योम i915_error_भ_लिखो(काष्ठा drm_i915_error_state_buf *e,
			       स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	बहु_सूची ap;
	पूर्णांक len;

	अगर (e->err)
		वापस;

	va_copy(ap, args);
	len = vsnम_लिखो(शून्य, 0, fmt, ap);
	बहु_पूर्ण(ap);
	अगर (len <= 0) अणु
		e->err = len;
		वापस;
	पूर्ण

	अगर (!__i915_error_grow(e, len))
		वापस;

	GEM_BUG_ON(e->bytes >= e->size);
	len = vscnम_लिखो(e->buf + e->bytes, e->size - e->bytes, fmt, args);
	अगर (len < 0) अणु
		e->err = len;
		वापस;
	पूर्ण
	e->bytes += len;
पूर्ण

अटल व्योम i915_error_माला_दो(काष्ठा drm_i915_error_state_buf *e, स्थिर अक्षर *str)
अणु
	अचिन्हित len;

	अगर (e->err || !str)
		वापस;

	len = म_माप(str);
	अगर (!__i915_error_grow(e, len))
		वापस;

	GEM_BUG_ON(e->bytes + len > e->size);
	स_नकल(e->buf + e->bytes, str, len);
	e->bytes += len;
पूर्ण

#घोषणा err_म_लिखो(e, ...) i915_error_म_लिखो(e, __VA_ARGS__)
#घोषणा err_माला_दो(e, s) i915_error_माला_दो(e, s)

अटल व्योम __i915_म_लिखोn_error(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf)
अणु
	i915_error_भ_लिखो(p->arg, vaf->fmt, *vaf->va);
पूर्ण

अटल अंतरभूत काष्ठा drm_prपूर्णांकer
i915_error_prपूर्णांकer(काष्ठा drm_i915_error_state_buf *e)
अणु
	काष्ठा drm_prपूर्णांकer p = अणु
		.म_लिखोn = __i915_म_लिखोn_error,
		.arg = e,
	पूर्ण;
	वापस p;
पूर्ण

/* single thपढ़ोed page allocator with a reserved stash क्रम emergencies */
अटल व्योम pool_fini(काष्ठा pagevec *pv)
अणु
	pagevec_release(pv);
पूर्ण

अटल पूर्णांक pool_refill(काष्ठा pagevec *pv, gfp_t gfp)
अणु
	जबतक (pagevec_space(pv)) अणु
		काष्ठा page *p;

		p = alloc_page(gfp);
		अगर (!p)
			वापस -ENOMEM;

		pagevec_add(pv, p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pool_init(काष्ठा pagevec *pv, gfp_t gfp)
अणु
	पूर्णांक err;

	pagevec_init(pv);

	err = pool_refill(pv, gfp);
	अगर (err)
		pool_fini(pv);

	वापस err;
पूर्ण

अटल व्योम *pool_alloc(काष्ठा pagevec *pv, gfp_t gfp)
अणु
	काष्ठा page *p;

	p = alloc_page(gfp);
	अगर (!p && pagevec_count(pv))
		p = pv->pages[--pv->nr];

	वापस p ? page_address(p) : शून्य;
पूर्ण

अटल व्योम pool_मुक्त(काष्ठा pagevec *pv, व्योम *addr)
अणु
	काष्ठा page *p = virt_to_page(addr);

	अगर (pagevec_space(pv))
		pagevec_add(pv, p);
	अन्यथा
		__मुक्त_page(p);
पूर्ण

#अगर_घोषित CONFIG_DRM_I915_COMPRESS_ERROR

काष्ठा i915_vma_compress अणु
	काष्ठा pagevec pool;
	काष्ठा z_stream_s zstream;
	व्योम *पंचांगp;
पूर्ण;

अटल bool compress_init(काष्ठा i915_vma_compress *c)
अणु
	काष्ठा z_stream_s *zstream = &c->zstream;

	अगर (pool_init(&c->pool, ALLOW_FAIL))
		वापस false;

	zstream->workspace =
		kदो_स्मृति(zlib_deflate_workspacesize(MAX_WBITS, MAX_MEM_LEVEL),
			ALLOW_FAIL);
	अगर (!zstream->workspace) अणु
		pool_fini(&c->pool);
		वापस false;
	पूर्ण

	c->पंचांगp = शून्य;
	अगर (i915_has_स_नकल_from_wc())
		c->पंचांगp = pool_alloc(&c->pool, ALLOW_FAIL);

	वापस true;
पूर्ण

अटल bool compress_start(काष्ठा i915_vma_compress *c)
अणु
	काष्ठा z_stream_s *zstream = &c->zstream;
	व्योम *workspace = zstream->workspace;

	स_रखो(zstream, 0, माप(*zstream));
	zstream->workspace = workspace;

	वापस zlib_deflateInit(zstream, Z_DEFAULT_COMPRESSION) == Z_OK;
पूर्ण

अटल व्योम *compress_next_page(काष्ठा i915_vma_compress *c,
				काष्ठा i915_vma_coredump *dst)
अणु
	व्योम *page;

	अगर (dst->page_count >= dst->num_pages)
		वापस ERR_PTR(-ENOSPC);

	page = pool_alloc(&c->pool, ALLOW_FAIL);
	अगर (!page)
		वापस ERR_PTR(-ENOMEM);

	वापस dst->pages[dst->page_count++] = page;
पूर्ण

अटल पूर्णांक compress_page(काष्ठा i915_vma_compress *c,
			 व्योम *src,
			 काष्ठा i915_vma_coredump *dst,
			 bool wc)
अणु
	काष्ठा z_stream_s *zstream = &c->zstream;

	zstream->next_in = src;
	अगर (wc && c->पंचांगp && i915_स_नकल_from_wc(c->पंचांगp, src, PAGE_SIZE))
		zstream->next_in = c->पंचांगp;
	zstream->avail_in = PAGE_SIZE;

	करो अणु
		अगर (zstream->avail_out == 0) अणु
			zstream->next_out = compress_next_page(c, dst);
			अगर (IS_ERR(zstream->next_out))
				वापस PTR_ERR(zstream->next_out);

			zstream->avail_out = PAGE_SIZE;
		पूर्ण

		अगर (zlib_deflate(zstream, Z_NO_FLUSH) != Z_OK)
			वापस -EIO;

		cond_resched();
	पूर्ण जबतक (zstream->avail_in);

	/* Fallback to uncompressed अगर we increase size? */
	अगर (0 && zstream->total_out > zstream->total_in)
		वापस -E2BIG;

	वापस 0;
पूर्ण

अटल पूर्णांक compress_flush(काष्ठा i915_vma_compress *c,
			  काष्ठा i915_vma_coredump *dst)
अणु
	काष्ठा z_stream_s *zstream = &c->zstream;

	करो अणु
		चयन (zlib_deflate(zstream, Z_FINISH)) अणु
		हाल Z_OK: /* more space requested */
			zstream->next_out = compress_next_page(c, dst);
			अगर (IS_ERR(zstream->next_out))
				वापस PTR_ERR(zstream->next_out);

			zstream->avail_out = PAGE_SIZE;
			अवरोध;

		हाल Z_STREAM_END:
			जाओ end;

		शेष: /* any error */
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक (1);

end:
	स_रखो(zstream->next_out, 0, zstream->avail_out);
	dst->unused = zstream->avail_out;
	वापस 0;
पूर्ण

अटल व्योम compress_finish(काष्ठा i915_vma_compress *c)
अणु
	zlib_deflateEnd(&c->zstream);
पूर्ण

अटल व्योम compress_fini(काष्ठा i915_vma_compress *c)
अणु
	kमुक्त(c->zstream.workspace);
	अगर (c->पंचांगp)
		pool_मुक्त(&c->pool, c->पंचांगp);
	pool_fini(&c->pool);
पूर्ण

अटल व्योम err_compression_marker(काष्ठा drm_i915_error_state_buf *m)
अणु
	err_माला_दो(m, ":");
पूर्ण

#अन्यथा

काष्ठा i915_vma_compress अणु
	काष्ठा pagevec pool;
पूर्ण;

अटल bool compress_init(काष्ठा i915_vma_compress *c)
अणु
	वापस pool_init(&c->pool, ALLOW_FAIL) == 0;
पूर्ण

अटल bool compress_start(काष्ठा i915_vma_compress *c)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक compress_page(काष्ठा i915_vma_compress *c,
			 व्योम *src,
			 काष्ठा i915_vma_coredump *dst,
			 bool wc)
अणु
	व्योम *ptr;

	ptr = pool_alloc(&c->pool, ALLOW_FAIL);
	अगर (!ptr)
		वापस -ENOMEM;

	अगर (!(wc && i915_स_नकल_from_wc(ptr, src, PAGE_SIZE)))
		स_नकल(ptr, src, PAGE_SIZE);
	dst->pages[dst->page_count++] = ptr;
	cond_resched();

	वापस 0;
पूर्ण

अटल पूर्णांक compress_flush(काष्ठा i915_vma_compress *c,
			  काष्ठा i915_vma_coredump *dst)
अणु
	वापस 0;
पूर्ण

अटल व्योम compress_finish(काष्ठा i915_vma_compress *c)
अणु
पूर्ण

अटल व्योम compress_fini(काष्ठा i915_vma_compress *c)
अणु
	pool_fini(&c->pool);
पूर्ण

अटल व्योम err_compression_marker(काष्ठा drm_i915_error_state_buf *m)
अणु
	err_माला_दो(m, "~");
पूर्ण

#पूर्ण_अगर

अटल व्योम error_prपूर्णांक_instकरोne(काष्ठा drm_i915_error_state_buf *m,
				 स्थिर काष्ठा पूर्णांकel_engine_coredump *ee)
अणु
	स्थिर काष्ठा sseu_dev_info *sseu = &ee->engine->gt->info.sseu;
	पूर्णांक slice;
	पूर्णांक subslice;

	err_म_लिखो(m, "  INSTDONE: 0x%08x\n",
		   ee->instकरोne.instकरोne);

	अगर (ee->engine->class != RENDER_CLASS || INTEL_GEN(m->i915) <= 3)
		वापस;

	err_म_लिखो(m, "  SC_INSTDONE: 0x%08x\n",
		   ee->instकरोne.slice_common);

	अगर (INTEL_GEN(m->i915) <= 6)
		वापस;

	क्रम_each_instकरोne_slice_subslice(m->i915, sseu, slice, subslice)
		err_म_लिखो(m, "  SAMPLER_INSTDONE[%d][%d]: 0x%08x\n",
			   slice, subslice,
			   ee->instकरोne.sampler[slice][subslice]);

	क्रम_each_instकरोne_slice_subslice(m->i915, sseu, slice, subslice)
		err_म_लिखो(m, "  ROW_INSTDONE[%d][%d]: 0x%08x\n",
			   slice, subslice,
			   ee->instकरोne.row[slice][subslice]);

	अगर (INTEL_GEN(m->i915) < 12)
		वापस;

	err_म_लिखो(m, "  SC_INSTDONE_EXTRA: 0x%08x\n",
		   ee->instकरोne.slice_common_extra[0]);
	err_म_लिखो(m, "  SC_INSTDONE_EXTRA2: 0x%08x\n",
		   ee->instकरोne.slice_common_extra[1]);
पूर्ण

अटल व्योम error_prपूर्णांक_request(काष्ठा drm_i915_error_state_buf *m,
				स्थिर अक्षर *prefix,
				स्थिर काष्ठा i915_request_coredump *erq)
अणु
	अगर (!erq->seqno)
		वापस;

	err_म_लिखो(m, "%s pid %d, seqno %8x:%08x%s%s, prio %d, head %08x, tail %08x\n",
		   prefix, erq->pid, erq->context, erq->seqno,
		   test_bit(DMA_FENCE_FLAG_SIGNALED_BIT,
			    &erq->flags) ? "!" : "",
		   test_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT,
			    &erq->flags) ? "+" : "",
		   erq->sched_attr.priority,
		   erq->head, erq->tail);
पूर्ण

अटल व्योम error_prपूर्णांक_context(काष्ठा drm_i915_error_state_buf *m,
				स्थिर अक्षर *header,
				स्थिर काष्ठा i915_gem_context_coredump *ctx)
अणु
	स्थिर u32 period = m->i915->gt.घड़ी_period_ns;

	err_म_लिखो(m, "%s%s[%d] prio %d, guilty %d active %d, runtime total %lluns, avg %lluns\n",
		   header, ctx->comm, ctx->pid, ctx->sched_attr.priority,
		   ctx->guilty, ctx->active,
		   ctx->total_runसमय * period,
		   mul_u32_u32(ctx->avg_runसमय, period));
पूर्ण

अटल काष्ठा i915_vma_coredump *
__find_vma(काष्ठा i915_vma_coredump *vma, स्थिर अक्षर *name)
अणु
	जबतक (vma) अणु
		अगर (म_भेद(vma->name, name) == 0)
			वापस vma;
		vma = vma->next;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा i915_vma_coredump *
find_batch(स्थिर काष्ठा पूर्णांकel_engine_coredump *ee)
अणु
	वापस __find_vma(ee->vma, "batch");
पूर्ण

अटल व्योम error_prपूर्णांक_engine(काष्ठा drm_i915_error_state_buf *m,
			       स्थिर काष्ठा पूर्णांकel_engine_coredump *ee)
अणु
	काष्ठा i915_vma_coredump *batch;
	पूर्णांक n;

	err_म_लिखो(m, "%s command stream:\n", ee->engine->name);
	err_म_लिखो(m, "  CCID:  0x%08x\n", ee->ccid);
	err_म_लिखो(m, "  START: 0x%08x\n", ee->start);
	err_म_लिखो(m, "  HEAD:  0x%08x [0x%08x]\n", ee->head, ee->rq_head);
	err_म_लिखो(m, "  TAIL:  0x%08x [0x%08x, 0x%08x]\n",
		   ee->tail, ee->rq_post, ee->rq_tail);
	err_म_लिखो(m, "  CTL:   0x%08x\n", ee->ctl);
	err_म_लिखो(m, "  MODE:  0x%08x\n", ee->mode);
	err_म_लिखो(m, "  HWS:   0x%08x\n", ee->hws);
	err_म_लिखो(m, "  ACTHD: 0x%08x %08x\n",
		   (u32)(ee->acthd>>32), (u32)ee->acthd);
	err_म_लिखो(m, "  IPEIR: 0x%08x\n", ee->ipeir);
	err_म_लिखो(m, "  IPEHR: 0x%08x\n", ee->ipehr);
	err_म_लिखो(m, "  ESR:   0x%08x\n", ee->esr);

	error_prपूर्णांक_instकरोne(m, ee);

	batch = find_batch(ee);
	अगर (batch) अणु
		u64 start = batch->gtt_offset;
		u64 end = start + batch->gtt_size;

		err_म_लिखो(m, "  batch: [0x%08x_%08x, 0x%08x_%08x]\n",
			   upper_32_bits(start), lower_32_bits(start),
			   upper_32_bits(end), lower_32_bits(end));
	पूर्ण
	अगर (INTEL_GEN(m->i915) >= 4) अणु
		err_म_लिखो(m, "  BBADDR: 0x%08x_%08x\n",
			   (u32)(ee->bbaddr>>32), (u32)ee->bbaddr);
		err_म_लिखो(m, "  BB_STATE: 0x%08x\n", ee->bbstate);
		err_म_लिखो(m, "  INSTPS: 0x%08x\n", ee->instps);
	पूर्ण
	err_म_लिखो(m, "  INSTPM: 0x%08x\n", ee->instpm);
	err_म_लिखो(m, "  FADDR: 0x%08x %08x\n", upper_32_bits(ee->faddr),
		   lower_32_bits(ee->faddr));
	अगर (INTEL_GEN(m->i915) >= 6) अणु
		err_म_लिखो(m, "  RC PSMI: 0x%08x\n", ee->rc_psmi);
		err_म_लिखो(m, "  FAULT_REG: 0x%08x\n", ee->fault_reg);
	पूर्ण
	अगर (HAS_PPGTT(m->i915)) अणु
		err_म_लिखो(m, "  GFX_MODE: 0x%08x\n", ee->vm_info.gfx_mode);

		अगर (INTEL_GEN(m->i915) >= 8) अणु
			पूर्णांक i;
			क्रम (i = 0; i < 4; i++)
				err_म_लिखो(m, "  PDP%d: 0x%016llx\n",
					   i, ee->vm_info.pdp[i]);
		पूर्ण अन्यथा अणु
			err_म_लिखो(m, "  PP_DIR_BASE: 0x%08x\n",
				   ee->vm_info.pp_dir_base);
		पूर्ण
	पूर्ण
	err_म_लिखो(m, "  hung: %u\n", ee->hung);
	err_म_लिखो(m, "  engine reset count: %u\n", ee->reset_count);

	क्रम (n = 0; n < ee->num_ports; n++) अणु
		err_म_लिखो(m, "  ELSP[%d]:", n);
		error_prपूर्णांक_request(m, " ", &ee->execlist[n]);
	पूर्ण

	error_prपूर्णांक_context(m, "  Active context: ", &ee->context);
पूर्ण

व्योम i915_error_म_लिखो(काष्ठा drm_i915_error_state_buf *e, स्थिर अक्षर *f, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, f);
	i915_error_भ_लिखो(e, f, args);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम prपूर्णांक_error_vma(काष्ठा drm_i915_error_state_buf *m,
			    स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर काष्ठा i915_vma_coredump *vma)
अणु
	अक्षर out[ASCII85_BUFSZ];
	पूर्णांक page;

	अगर (!vma)
		वापस;

	err_म_लिखो(m, "%s --- %s = 0x%08x %08x\n",
		   engine ? engine->name : "global", vma->name,
		   upper_32_bits(vma->gtt_offset),
		   lower_32_bits(vma->gtt_offset));

	अगर (vma->gtt_page_sizes > I915_GTT_PAGE_SIZE_4K)
		err_म_लिखो(m, "gtt_page_sizes = 0x%08x\n", vma->gtt_page_sizes);

	err_compression_marker(m);
	क्रम (page = 0; page < vma->page_count; page++) अणु
		पूर्णांक i, len;

		len = PAGE_SIZE;
		अगर (page == vma->page_count - 1)
			len -= vma->unused;
		len = ascii85_encode_len(len);

		क्रम (i = 0; i < len; i++)
			err_माला_दो(m, ascii85_encode(vma->pages[page][i], out));
	पूर्ण
	err_माला_दो(m, "\n");
पूर्ण

अटल व्योम err_prपूर्णांक_capabilities(काष्ठा drm_i915_error_state_buf *m,
				   काष्ठा i915_gpu_coredump *error)
अणु
	काष्ठा drm_prपूर्णांकer p = i915_error_prपूर्णांकer(m);

	पूर्णांकel_device_info_prपूर्णांक_अटल(&error->device_info, &p);
	पूर्णांकel_device_info_prपूर्णांक_runसमय(&error->runसमय_info, &p);
	पूर्णांकel_driver_caps_prपूर्णांक(&error->driver_caps, &p);
पूर्ण

अटल व्योम err_prपूर्णांक_params(काष्ठा drm_i915_error_state_buf *m,
			     स्थिर काष्ठा i915_params *params)
अणु
	काष्ठा drm_prपूर्णांकer p = i915_error_prपूर्णांकer(m);

	i915_params_dump(params, &p);
पूर्ण

अटल व्योम err_prपूर्णांक_pciid(काष्ठा drm_i915_error_state_buf *m,
			    काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);

	err_म_लिखो(m, "PCI ID: 0x%04x\n", pdev->device);
	err_म_लिखो(m, "PCI Revision: 0x%02x\n", pdev->revision);
	err_म_लिखो(m, "PCI Subsystem: %04x:%04x\n",
		   pdev->subप्रणाली_venकरोr,
		   pdev->subप्रणाली_device);
पूर्ण

अटल व्योम err_prपूर्णांक_uc(काष्ठा drm_i915_error_state_buf *m,
			 स्थिर काष्ठा पूर्णांकel_uc_coredump *error_uc)
अणु
	काष्ठा drm_prपूर्णांकer p = i915_error_prपूर्णांकer(m);

	पूर्णांकel_uc_fw_dump(&error_uc->guc_fw, &p);
	पूर्णांकel_uc_fw_dump(&error_uc->huc_fw, &p);
	prपूर्णांक_error_vma(m, शून्य, error_uc->guc_log);
पूर्ण

अटल व्योम err_मुक्त_sgl(काष्ठा scatterlist *sgl)
अणु
	जबतक (sgl) अणु
		काष्ठा scatterlist *sg;

		क्रम (sg = sgl; !sg_is_chain(sg); sg++) अणु
			kमुक्त(sg_virt(sg));
			अगर (sg_is_last(sg))
				अवरोध;
		पूर्ण

		sg = sg_is_last(sg) ? शून्य : sg_chain_ptr(sg);
		मुक्त_page((अचिन्हित दीर्घ)sgl);
		sgl = sg;
	पूर्ण
पूर्ण

अटल व्योम err_prपूर्णांक_gt_info(काष्ठा drm_i915_error_state_buf *m,
			      काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	काष्ठा drm_prपूर्णांकer p = i915_error_prपूर्णांकer(m);

	पूर्णांकel_gt_info_prपूर्णांक(&gt->info, &p);
	पूर्णांकel_sseu_prपूर्णांक_topology(&gt->info.sseu, &p);
पूर्ण

अटल व्योम err_prपूर्णांक_gt(काष्ठा drm_i915_error_state_buf *m,
			 काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_coredump *ee;
	पूर्णांक i;

	err_म_लिखो(m, "GT awake: %s\n", yesno(gt->awake));
	err_म_लिखो(m, "EIR: 0x%08x\n", gt->eir);
	err_म_लिखो(m, "IER: 0x%08x\n", gt->ier);
	क्रम (i = 0; i < gt->ngtier; i++)
		err_म_लिखो(m, "GTIER[%d]: 0x%08x\n", i, gt->gtier[i]);
	err_म_लिखो(m, "PGTBL_ER: 0x%08x\n", gt->pgtbl_er);
	err_म_लिखो(m, "FORCEWAKE: 0x%08x\n", gt->क्रमcewake);
	err_म_लिखो(m, "DERRMR: 0x%08x\n", gt->derrmr);

	क्रम (i = 0; i < gt->nfence; i++)
		err_म_लिखो(m, "  fence[%d] = %08llx\n", i, gt->fence[i]);

	अगर (IS_GEN_RANGE(m->i915, 6, 11)) अणु
		err_म_लिखो(m, "ERROR: 0x%08x\n", gt->error);
		err_म_लिखो(m, "DONE_REG: 0x%08x\n", gt->करोne_reg);
	पूर्ण

	अगर (INTEL_GEN(m->i915) >= 8)
		err_म_लिखो(m, "FAULT_TLB_DATA: 0x%08x 0x%08x\n",
			   gt->fault_data1, gt->fault_data0);

	अगर (IS_GEN(m->i915, 7))
		err_म_लिखो(m, "ERR_INT: 0x%08x\n", gt->err_पूर्णांक);

	अगर (IS_GEN_RANGE(m->i915, 8, 11))
		err_म_लिखो(m, "GTT_CACHE_EN: 0x%08x\n", gt->gtt_cache);

	अगर (IS_GEN(m->i915, 12))
		err_म_लिखो(m, "AUX_ERR_DBG: 0x%08x\n", gt->aux_err);

	अगर (INTEL_GEN(m->i915) >= 12) अणु
		पूर्णांक i;

		क्रम (i = 0; i < GEN12_SFC_DONE_MAX; i++)
			err_म_लिखो(m, "  SFC_DONE[%d]: 0x%08x\n", i,
				   gt->sfc_करोne[i]);

		err_म_लिखो(m, "  GAM_DONE: 0x%08x\n", gt->gam_करोne);
	पूर्ण

	क्रम (ee = gt->engine; ee; ee = ee->next) अणु
		स्थिर काष्ठा i915_vma_coredump *vma;

		error_prपूर्णांक_engine(m, ee);
		क्रम (vma = ee->vma; vma; vma = vma->next)
			prपूर्णांक_error_vma(m, ee->engine, vma);
	पूर्ण

	अगर (gt->uc)
		err_prपूर्णांक_uc(m, gt->uc);

	err_prपूर्णांक_gt_info(m, gt);
पूर्ण

अटल व्योम __err_prपूर्णांक_to_sgl(काष्ठा drm_i915_error_state_buf *m,
			       काष्ठा i915_gpu_coredump *error)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_coredump *ee;
	काष्ठा बारpec64 ts;

	अगर (*error->error_msg)
		err_म_लिखो(m, "%s\n", error->error_msg);
	err_म_लिखो(m, "Kernel: %s %s\n",
		   init_utsname()->release,
		   init_utsname()->machine);
	err_म_लिखो(m, "Driver: %s\n", DRIVER_DATE);
	ts = kसमय_प्रकारo_बारpec64(error->समय);
	err_म_लिखो(m, "Time: %lld s %ld us\n",
		   (s64)ts.tv_sec, ts.tv_nsec / NSEC_PER_USEC);
	ts = kसमय_प्रकारo_बारpec64(error->bootसमय);
	err_म_लिखो(m, "Boottime: %lld s %ld us\n",
		   (s64)ts.tv_sec, ts.tv_nsec / NSEC_PER_USEC);
	ts = kसमय_प्रकारo_बारpec64(error->upसमय);
	err_म_लिखो(m, "Uptime: %lld s %ld us\n",
		   (s64)ts.tv_sec, ts.tv_nsec / NSEC_PER_USEC);
	err_म_लिखो(m, "Capture: %lu jiffies; %d ms ago\n",
		   error->capture, jअगरfies_to_msecs(jअगरfies - error->capture));

	क्रम (ee = error->gt ? error->gt->engine : शून्य; ee; ee = ee->next)
		err_म_लिखो(m, "Active process (on ring %s): %s [%d]\n",
			   ee->engine->name,
			   ee->context.comm,
			   ee->context.pid);

	err_म_लिखो(m, "Reset count: %u\n", error->reset_count);
	err_म_लिखो(m, "Suspend count: %u\n", error->suspend_count);
	err_म_लिखो(m, "Platform: %s\n", पूर्णांकel_platक्रमm_name(error->device_info.platक्रमm));
	err_म_लिखो(m, "Subplatform: 0x%x\n",
		   पूर्णांकel_subplatक्रमm(&error->runसमय_info,
				     error->device_info.platक्रमm));
	err_prपूर्णांक_pciid(m, m->i915);

	err_म_लिखो(m, "IOMMU enabled?: %d\n", error->iommu);

	अगर (HAS_CSR(m->i915)) अणु
		काष्ठा पूर्णांकel_csr *csr = &m->i915->csr;

		err_म_लिखो(m, "DMC loaded: %s\n",
			   yesno(csr->dmc_payload != शून्य));
		err_म_लिखो(m, "DMC fw version: %d.%d\n",
			   CSR_VERSION_MAJOR(csr->version),
			   CSR_VERSION_MINOR(csr->version));
	पूर्ण

	err_म_लिखो(m, "RPM wakelock: %s\n", yesno(error->wakelock));
	err_म_लिखो(m, "PM suspended: %s\n", yesno(error->suspended));

	अगर (error->gt)
		err_prपूर्णांक_gt(m, error->gt);

	अगर (error->overlay)
		पूर्णांकel_overlay_prपूर्णांक_error_state(m, error->overlay);

	अगर (error->display)
		पूर्णांकel_display_prपूर्णांक_error_state(m, error->display);

	err_prपूर्णांक_capabilities(m, error);
	err_prपूर्णांक_params(m, &error->params);
पूर्ण

अटल पूर्णांक err_prपूर्णांक_to_sgl(काष्ठा i915_gpu_coredump *error)
अणु
	काष्ठा drm_i915_error_state_buf m;

	अगर (IS_ERR(error))
		वापस PTR_ERR(error);

	अगर (READ_ONCE(error->sgl))
		वापस 0;

	स_रखो(&m, 0, माप(m));
	m.i915 = error->i915;

	__err_prपूर्णांक_to_sgl(&m, error);

	अगर (m.buf) अणु
		__sg_set_buf(m.cur++, m.buf, m.bytes, m.iter);
		m.bytes = 0;
		m.buf = शून्य;
	पूर्ण
	अगर (m.cur) अणु
		GEM_BUG_ON(m.end < m.cur);
		sg_mark_end(m.cur - 1);
	पूर्ण
	GEM_BUG_ON(m.sgl && !m.cur);

	अगर (m.err) अणु
		err_मुक्त_sgl(m.sgl);
		वापस m.err;
	पूर्ण

	अगर (cmpxchg(&error->sgl, शून्य, m.sgl))
		err_मुक्त_sgl(m.sgl);

	वापस 0;
पूर्ण

sमाप_प्रकार i915_gpu_coredump_copy_to_buffer(काष्ठा i915_gpu_coredump *error,
					 अक्षर *buf, loff_t off, माप_प्रकार rem)
अणु
	काष्ठा scatterlist *sg;
	माप_प्रकार count;
	loff_t pos;
	पूर्णांक err;

	अगर (!error || !rem)
		वापस 0;

	err = err_prपूर्णांक_to_sgl(error);
	अगर (err)
		वापस err;

	sg = READ_ONCE(error->fit);
	अगर (!sg || off < sg->dma_address)
		sg = error->sgl;
	अगर (!sg)
		वापस 0;

	pos = sg->dma_address;
	count = 0;
	करो अणु
		माप_प्रकार len, start;

		अगर (sg_is_chain(sg)) अणु
			sg = sg_chain_ptr(sg);
			GEM_BUG_ON(sg_is_chain(sg));
		पूर्ण

		len = sg->length;
		अगर (pos + len <= off) अणु
			pos += len;
			जारी;
		पूर्ण

		start = sg->offset;
		अगर (pos < off) अणु
			GEM_BUG_ON(off - pos > len);
			len -= off - pos;
			start += off - pos;
			pos = off;
		पूर्ण

		len = min(len, rem);
		GEM_BUG_ON(!len || len > sg->length);

		स_नकल(buf, page_address(sg_page(sg)) + start, len);

		count += len;
		pos += len;

		buf += len;
		rem -= len;
		अगर (!rem) अणु
			WRITE_ONCE(error->fit, sg);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!sg_is_last(sg++));

	वापस count;
पूर्ण

अटल व्योम i915_vma_coredump_मुक्त(काष्ठा i915_vma_coredump *vma)
अणु
	जबतक (vma) अणु
		काष्ठा i915_vma_coredump *next = vma->next;
		पूर्णांक page;

		क्रम (page = 0; page < vma->page_count; page++)
			मुक्त_page((अचिन्हित दीर्घ)vma->pages[page]);

		kमुक्त(vma);
		vma = next;
	पूर्ण
पूर्ण

अटल व्योम cleanup_params(काष्ठा i915_gpu_coredump *error)
अणु
	i915_params_मुक्त(&error->params);
पूर्ण

अटल व्योम cleanup_uc(काष्ठा पूर्णांकel_uc_coredump *uc)
अणु
	kमुक्त(uc->guc_fw.path);
	kमुक्त(uc->huc_fw.path);
	i915_vma_coredump_मुक्त(uc->guc_log);

	kमुक्त(uc);
पूर्ण

अटल व्योम cleanup_gt(काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	जबतक (gt->engine) अणु
		काष्ठा पूर्णांकel_engine_coredump *ee = gt->engine;

		gt->engine = ee->next;

		i915_vma_coredump_मुक्त(ee->vma);
		kमुक्त(ee);
	पूर्ण

	अगर (gt->uc)
		cleanup_uc(gt->uc);

	kमुक्त(gt);
पूर्ण

व्योम __i915_gpu_coredump_मुक्त(काष्ठा kref *error_ref)
अणु
	काष्ठा i915_gpu_coredump *error =
		container_of(error_ref, typeof(*error), ref);

	जबतक (error->gt) अणु
		काष्ठा पूर्णांकel_gt_coredump *gt = error->gt;

		error->gt = gt->next;
		cleanup_gt(gt);
	पूर्ण

	kमुक्त(error->overlay);
	kमुक्त(error->display);

	cleanup_params(error);

	err_मुक्त_sgl(error->sgl);
	kमुक्त(error);
पूर्ण

अटल काष्ठा i915_vma_coredump *
i915_vma_coredump_create(स्थिर काष्ठा पूर्णांकel_gt *gt,
			 स्थिर काष्ठा i915_vma *vma,
			 स्थिर अक्षर *name,
			 काष्ठा i915_vma_compress *compress)
अणु
	काष्ठा i915_ggtt *ggtt = gt->ggtt;
	स्थिर u64 slot = ggtt->error_capture.start;
	काष्ठा i915_vma_coredump *dst;
	अचिन्हित दीर्घ num_pages;
	काष्ठा sgt_iter iter;
	पूर्णांक ret;

	might_sleep();

	अगर (!vma || !vma->pages || !compress)
		वापस शून्य;

	num_pages = min_t(u64, vma->size, vma->obj->base.size) >> PAGE_SHIFT;
	num_pages = DIV_ROUND_UP(10 * num_pages, 8); /* worstहाल zlib growth */
	dst = kदो_स्मृति(माप(*dst) + num_pages * माप(u32 *), ALLOW_FAIL);
	अगर (!dst)
		वापस शून्य;

	अगर (!compress_start(compress)) अणु
		kमुक्त(dst);
		वापस शून्य;
	पूर्ण

	म_नकल(dst->name, name);
	dst->next = शून्य;

	dst->gtt_offset = vma->node.start;
	dst->gtt_size = vma->node.size;
	dst->gtt_page_sizes = vma->page_sizes.gtt;
	dst->num_pages = num_pages;
	dst->page_count = 0;
	dst->unused = 0;

	ret = -EINVAL;
	अगर (drm_mm_node_allocated(&ggtt->error_capture)) अणु
		व्योम __iomem *s;
		dma_addr_t dma;

		क्रम_each_sgt_daddr(dma, iter, vma->pages) अणु
			mutex_lock(&ggtt->error_mutex);
			ggtt->vm.insert_page(&ggtt->vm, dma, slot,
					     I915_CACHE_NONE, 0);
			mb();

			s = io_mapping_map_wc(&ggtt->iomap, slot, PAGE_SIZE);
			ret = compress_page(compress,
					    (व्योम  __क्रमce *)s, dst,
					    true);
			io_mapping_unmap(s);

			mb();
			ggtt->vm.clear_range(&ggtt->vm, slot, PAGE_SIZE);
			mutex_unlock(&ggtt->error_mutex);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (i915_gem_object_is_lmem(vma->obj)) अणु
		काष्ठा पूर्णांकel_memory_region *mem = vma->obj->mm.region;
		dma_addr_t dma;

		क्रम_each_sgt_daddr(dma, iter, vma->pages) अणु
			व्योम __iomem *s;

			s = io_mapping_map_wc(&mem->iomap,
					      dma - mem->region.start,
					      PAGE_SIZE);
			ret = compress_page(compress,
					    (व्योम __क्रमce *)s, dst,
					    true);
			io_mapping_unmap(s);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा page *page;

		क्रम_each_sgt_page(page, iter, vma->pages) अणु
			व्योम *s;

			drm_clflush_pages(&page, 1);

			s = kmap(page);
			ret = compress_page(compress, s, dst, false);
			kunmap(page);

			drm_clflush_pages(&page, 1);

			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret || compress_flush(compress, dst)) अणु
		जबतक (dst->page_count--)
			pool_मुक्त(&compress->pool, dst->pages[dst->page_count]);
		kमुक्त(dst);
		dst = शून्य;
	पूर्ण
	compress_finish(compress);

	वापस dst;
पूर्ण

अटल व्योम gt_record_fences(काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	काष्ठा i915_ggtt *ggtt = gt->_gt->ggtt;
	काष्ठा पूर्णांकel_uncore *uncore = gt->_gt->uncore;
	पूर्णांक i;

	अगर (INTEL_GEN(uncore->i915) >= 6) अणु
		क्रम (i = 0; i < ggtt->num_fences; i++)
			gt->fence[i] =
				पूर्णांकel_uncore_पढ़ो64(uncore,
						    FENCE_REG_GEN6_LO(i));
	पूर्ण अन्यथा अगर (INTEL_GEN(uncore->i915) >= 4) अणु
		क्रम (i = 0; i < ggtt->num_fences; i++)
			gt->fence[i] =
				पूर्णांकel_uncore_पढ़ो64(uncore,
						    FENCE_REG_965_LO(i));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ggtt->num_fences; i++)
			gt->fence[i] =
				पूर्णांकel_uncore_पढ़ो(uncore, FENCE_REG(i));
	पूर्ण
	gt->nfence = i;
पूर्ण

अटल व्योम engine_record_रेजिस्टरs(काष्ठा पूर्णांकel_engine_coredump *ee)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine = ee->engine;
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (INTEL_GEN(i915) >= 6) अणु
		ee->rc_psmi = ENGINE_READ(engine, RING_PSMI_CTL);

		अगर (INTEL_GEN(i915) >= 12)
			ee->fault_reg = पूर्णांकel_uncore_पढ़ो(engine->uncore,
							  GEN12_RING_FAULT_REG);
		अन्यथा अगर (INTEL_GEN(i915) >= 8)
			ee->fault_reg = पूर्णांकel_uncore_पढ़ो(engine->uncore,
							  GEN8_RING_FAULT_REG);
		अन्यथा
			ee->fault_reg = GEN6_RING_FAULT_REG_READ(engine);
	पूर्ण

	अगर (INTEL_GEN(i915) >= 4) अणु
		ee->esr = ENGINE_READ(engine, RING_ESR);
		ee->faddr = ENGINE_READ(engine, RING_DMA_FADD);
		ee->ipeir = ENGINE_READ(engine, RING_IPEIR);
		ee->ipehr = ENGINE_READ(engine, RING_IPEHR);
		ee->instps = ENGINE_READ(engine, RING_INSTPS);
		ee->bbaddr = ENGINE_READ(engine, RING_BBADDR);
		ee->ccid = ENGINE_READ(engine, CCID);
		अगर (INTEL_GEN(i915) >= 8) अणु
			ee->faddr |= (u64)ENGINE_READ(engine, RING_DMA_FADD_UDW) << 32;
			ee->bbaddr |= (u64)ENGINE_READ(engine, RING_BBADDR_UDW) << 32;
		पूर्ण
		ee->bbstate = ENGINE_READ(engine, RING_BBSTATE);
	पूर्ण अन्यथा अणु
		ee->faddr = ENGINE_READ(engine, DMA_FADD_I8XX);
		ee->ipeir = ENGINE_READ(engine, IPEIR);
		ee->ipehr = ENGINE_READ(engine, IPEHR);
	पूर्ण

	पूर्णांकel_engine_get_instकरोne(engine, &ee->instकरोne);

	ee->instpm = ENGINE_READ(engine, RING_INSTPM);
	ee->acthd = पूर्णांकel_engine_get_active_head(engine);
	ee->start = ENGINE_READ(engine, RING_START);
	ee->head = ENGINE_READ(engine, RING_HEAD);
	ee->tail = ENGINE_READ(engine, RING_TAIL);
	ee->ctl = ENGINE_READ(engine, RING_CTL);
	अगर (INTEL_GEN(i915) > 2)
		ee->mode = ENGINE_READ(engine, RING_MI_MODE);

	अगर (!HWS_NEEDS_PHYSICAL(i915)) अणु
		i915_reg_t mmio;

		अगर (IS_GEN(i915, 7)) अणु
			चयन (engine->id) अणु
			शेष:
				MISSING_CASE(engine->id);
				fallthrough;
			हाल RCS0:
				mmio = RENDER_HWS_PGA_GEN7;
				अवरोध;
			हाल BCS0:
				mmio = BLT_HWS_PGA_GEN7;
				अवरोध;
			हाल VCS0:
				mmio = BSD_HWS_PGA_GEN7;
				अवरोध;
			हाल VECS0:
				mmio = VEBOX_HWS_PGA_GEN7;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (IS_GEN(engine->i915, 6)) अणु
			mmio = RING_HWS_PGA_GEN6(engine->mmio_base);
		पूर्ण अन्यथा अणु
			/* XXX: gen8 वापसs to sanity */
			mmio = RING_HWS_PGA(engine->mmio_base);
		पूर्ण

		ee->hws = पूर्णांकel_uncore_पढ़ो(engine->uncore, mmio);
	पूर्ण

	ee->reset_count = i915_reset_engine_count(&i915->gpu_error, engine);

	अगर (HAS_PPGTT(i915)) अणु
		पूर्णांक i;

		ee->vm_info.gfx_mode = ENGINE_READ(engine, RING_MODE_GEN7);

		अगर (IS_GEN(i915, 6)) अणु
			ee->vm_info.pp_dir_base =
				ENGINE_READ(engine, RING_PP_सूची_BASE_READ);
		पूर्ण अन्यथा अगर (IS_GEN(i915, 7)) अणु
			ee->vm_info.pp_dir_base =
				ENGINE_READ(engine, RING_PP_सूची_BASE);
		पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
			u32 base = engine->mmio_base;

			क्रम (i = 0; i < 4; i++) अणु
				ee->vm_info.pdp[i] =
					पूर्णांकel_uncore_पढ़ो(engine->uncore,
							  GEN8_RING_PDP_UDW(base, i));
				ee->vm_info.pdp[i] <<= 32;
				ee->vm_info.pdp[i] |=
					पूर्णांकel_uncore_पढ़ो(engine->uncore,
							  GEN8_RING_PDP_LDW(base, i));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम record_request(स्थिर काष्ठा i915_request *request,
			   काष्ठा i915_request_coredump *erq)
अणु
	erq->flags = request->fence.flags;
	erq->context = request->fence.context;
	erq->seqno = request->fence.seqno;
	erq->sched_attr = request->sched.attr;
	erq->head = request->head;
	erq->tail = request->tail;

	erq->pid = 0;
	rcu_पढ़ो_lock();
	अगर (!पूर्णांकel_context_is_बंदd(request->context)) अणु
		स्थिर काष्ठा i915_gem_context *ctx;

		ctx = rcu_dereference(request->context->gem_context);
		अगर (ctx)
			erq->pid = pid_nr(ctx->pid);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम engine_record_execlists(काष्ठा पूर्णांकel_engine_coredump *ee)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_execlists * स्थिर el = &ee->engine->execlists;
	काष्ठा i915_request * स्थिर *port = el->active;
	अचिन्हित पूर्णांक n = 0;

	जबतक (*port)
		record_request(*port++, &ee->execlist[n++]);

	ee->num_ports = n;
पूर्ण

अटल bool record_context(काष्ठा i915_gem_context_coredump *e,
			   स्थिर काष्ठा i915_request *rq)
अणु
	काष्ठा i915_gem_context *ctx;
	काष्ठा task_काष्ठा *task;
	bool simulated;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(rq->context->gem_context);
	अगर (ctx && !kref_get_unless_zero(&ctx->ref))
		ctx = शून्य;
	rcu_पढ़ो_unlock();
	अगर (!ctx)
		वापस true;

	rcu_पढ़ो_lock();
	task = pid_task(ctx->pid, PIDTYPE_PID);
	अगर (task) अणु
		म_नकल(e->comm, task->comm);
		e->pid = task->pid;
	पूर्ण
	rcu_पढ़ो_unlock();

	e->sched_attr = ctx->sched;
	e->guilty = atomic_पढ़ो(&ctx->guilty_count);
	e->active = atomic_पढ़ो(&ctx->active_count);

	e->total_runसमय = rq->context->runसमय.total;
	e->avg_runसमय = ewma_runसमय_पढ़ो(&rq->context->runसमय.avg);

	simulated = i915_gem_context_no_error_capture(ctx);

	i915_gem_context_put(ctx);
	वापस simulated;
पूर्ण

काष्ठा पूर्णांकel_engine_capture_vma अणु
	काष्ठा पूर्णांकel_engine_capture_vma *next;
	काष्ठा i915_vma *vma;
	अक्षर name[16];
पूर्ण;

अटल काष्ठा पूर्णांकel_engine_capture_vma *
capture_vma(काष्ठा पूर्णांकel_engine_capture_vma *next,
	    काष्ठा i915_vma *vma,
	    स्थिर अक्षर *name,
	    gfp_t gfp)
अणु
	काष्ठा पूर्णांकel_engine_capture_vma *c;

	अगर (!vma)
		वापस next;

	c = kदो_स्मृति(माप(*c), gfp);
	अगर (!c)
		वापस next;

	अगर (!i915_active_acquire_अगर_busy(&vma->active)) अणु
		kमुक्त(c);
		वापस next;
	पूर्ण

	म_नकल(c->name, name);
	c->vma = vma; /* reference held जबतक active */

	c->next = next;
	वापस c;
पूर्ण

अटल काष्ठा पूर्णांकel_engine_capture_vma *
capture_user(काष्ठा पूर्णांकel_engine_capture_vma *capture,
	     स्थिर काष्ठा i915_request *rq,
	     gfp_t gfp)
अणु
	काष्ठा i915_capture_list *c;

	क्रम (c = rq->capture_list; c; c = c->next)
		capture = capture_vma(capture, c->vma, "user", gfp);

	वापस capture;
पूर्ण

अटल व्योम add_vma(काष्ठा पूर्णांकel_engine_coredump *ee,
		    काष्ठा i915_vma_coredump *vma)
अणु
	अगर (vma) अणु
		vma->next = ee->vma;
		ee->vma = vma;
	पूर्ण
पूर्ण

काष्ठा पूर्णांकel_engine_coredump *
पूर्णांकel_engine_coredump_alloc(काष्ठा पूर्णांकel_engine_cs *engine, gfp_t gfp)
अणु
	काष्ठा पूर्णांकel_engine_coredump *ee;

	ee = kzalloc(माप(*ee), gfp);
	अगर (!ee)
		वापस शून्य;

	ee->engine = engine;

	engine_record_रेजिस्टरs(ee);
	engine_record_execlists(ee);

	वापस ee;
पूर्ण

काष्ठा पूर्णांकel_engine_capture_vma *
पूर्णांकel_engine_coredump_add_request(काष्ठा पूर्णांकel_engine_coredump *ee,
				  काष्ठा i915_request *rq,
				  gfp_t gfp)
अणु
	काष्ठा पूर्णांकel_engine_capture_vma *vma = शून्य;

	ee->simulated |= record_context(&ee->context, rq);
	अगर (ee->simulated)
		वापस शून्य;

	/*
	 * We need to copy these to an anonymous buffer
	 * as the simplest method to aव्योम being overwritten
	 * by userspace.
	 */
	vma = capture_vma(vma, rq->batch, "batch", gfp);
	vma = capture_user(vma, rq, gfp);
	vma = capture_vma(vma, rq->ring->vma, "ring", gfp);
	vma = capture_vma(vma, rq->context->state, "HW context", gfp);

	ee->rq_head = rq->head;
	ee->rq_post = rq->postfix;
	ee->rq_tail = rq->tail;

	वापस vma;
पूर्ण

व्योम
पूर्णांकel_engine_coredump_add_vma(काष्ठा पूर्णांकel_engine_coredump *ee,
			      काष्ठा पूर्णांकel_engine_capture_vma *capture,
			      काष्ठा i915_vma_compress *compress)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine = ee->engine;

	जबतक (capture) अणु
		काष्ठा पूर्णांकel_engine_capture_vma *this = capture;
		काष्ठा i915_vma *vma = this->vma;

		add_vma(ee,
			i915_vma_coredump_create(engine->gt,
						 vma, this->name,
						 compress));

		i915_active_release(&vma->active);

		capture = this->next;
		kमुक्त(this);
	पूर्ण

	add_vma(ee,
		i915_vma_coredump_create(engine->gt,
					 engine->status_page.vma,
					 "HW Status",
					 compress));

	add_vma(ee,
		i915_vma_coredump_create(engine->gt,
					 engine->wa_ctx.vma,
					 "WA context",
					 compress));
पूर्ण

अटल काष्ठा पूर्णांकel_engine_coredump *
capture_engine(काष्ठा पूर्णांकel_engine_cs *engine,
	       काष्ठा i915_vma_compress *compress)
अणु
	काष्ठा पूर्णांकel_engine_capture_vma *capture = शून्य;
	काष्ठा पूर्णांकel_engine_coredump *ee;
	काष्ठा i915_request *rq;
	अचिन्हित दीर्घ flags;

	ee = पूर्णांकel_engine_coredump_alloc(engine, GFP_KERNEL);
	अगर (!ee)
		वापस शून्य;

	spin_lock_irqsave(&engine->active.lock, flags);
	rq = पूर्णांकel_engine_find_active_request(engine);
	अगर (rq)
		capture = पूर्णांकel_engine_coredump_add_request(ee, rq,
							    ATOMIC_MAYFAIL);
	spin_unlock_irqrestore(&engine->active.lock, flags);
	अगर (!capture) अणु
		kमुक्त(ee);
		वापस शून्य;
	पूर्ण

	पूर्णांकel_engine_coredump_add_vma(ee, capture, compress);

	वापस ee;
पूर्ण

अटल व्योम
gt_record_engines(काष्ठा पूर्णांकel_gt_coredump *gt,
		  पूर्णांकel_engine_mask_t engine_mask,
		  काष्ठा i915_vma_compress *compress)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt->_gt, id) अणु
		काष्ठा पूर्णांकel_engine_coredump *ee;

		/* Refill our page pool beक्रमe entering atomic section */
		pool_refill(&compress->pool, ALLOW_FAIL);

		ee = capture_engine(engine, compress);
		अगर (!ee)
			जारी;

		ee->hung = engine->mask & engine_mask;

		gt->simulated |= ee->simulated;
		अगर (ee->simulated) अणु
			kमुक्त(ee);
			जारी;
		पूर्ण

		ee->next = gt->engine;
		gt->engine = ee;
	पूर्ण
पूर्ण

अटल काष्ठा पूर्णांकel_uc_coredump *
gt_record_uc(काष्ठा पूर्णांकel_gt_coredump *gt,
	     काष्ठा i915_vma_compress *compress)
अणु
	स्थिर काष्ठा पूर्णांकel_uc *uc = &gt->_gt->uc;
	काष्ठा पूर्णांकel_uc_coredump *error_uc;

	error_uc = kzalloc(माप(*error_uc), ALLOW_FAIL);
	अगर (!error_uc)
		वापस शून्य;

	स_नकल(&error_uc->guc_fw, &uc->guc.fw, माप(uc->guc.fw));
	स_नकल(&error_uc->huc_fw, &uc->huc.fw, माप(uc->huc.fw));

	/* Non-शेष firmware paths will be specअगरied by the modparam.
	 * As modparams are generally accesible from the userspace make
	 * explicit copies of the firmware paths.
	 */
	error_uc->guc_fw.path = kstrdup(uc->guc.fw.path, ALLOW_FAIL);
	error_uc->huc_fw.path = kstrdup(uc->huc.fw.path, ALLOW_FAIL);
	error_uc->guc_log =
		i915_vma_coredump_create(gt->_gt,
					 uc->guc.log.vma, "GuC log buffer",
					 compress);

	वापस error_uc;
पूर्ण

/* Capture all रेजिस्टरs which करोn't fit पूर्णांकo another category. */
अटल व्योम gt_record_regs(काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->_gt->uncore;
	काष्ठा drm_i915_निजी *i915 = uncore->i915;
	पूर्णांक i;

	/*
	 * General organization
	 * 1. Registers specअगरic to a single generation
	 * 2. Registers which beदीर्घ to multiple generations
	 * 3. Feature specअगरic रेजिस्टरs.
	 * 4. Everything अन्यथा
	 * Please try to follow the order.
	 */

	/* 1: Registers specअगरic to a single generation */
	अगर (IS_VALLEYVIEW(i915)) अणु
		gt->gtier[0] = पूर्णांकel_uncore_पढ़ो(uncore, GTIER);
		gt->ier = पूर्णांकel_uncore_पढ़ो(uncore, VLV_IER);
		gt->क्रमcewake = पूर्णांकel_uncore_पढ़ो_fw(uncore, FORCEWAKE_VLV);
	पूर्ण

	अगर (IS_GEN(i915, 7))
		gt->err_पूर्णांक = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_ERR_INT);

	अगर (INTEL_GEN(i915) >= 12) अणु
		gt->fault_data0 = पूर्णांकel_uncore_पढ़ो(uncore,
						    GEN12_FAULT_TLB_DATA0);
		gt->fault_data1 = पूर्णांकel_uncore_पढ़ो(uncore,
						    GEN12_FAULT_TLB_DATA1);
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
		gt->fault_data0 = पूर्णांकel_uncore_पढ़ो(uncore,
						    GEN8_FAULT_TLB_DATA0);
		gt->fault_data1 = पूर्णांकel_uncore_पढ़ो(uncore,
						    GEN8_FAULT_TLB_DATA1);
	पूर्ण

	अगर (IS_GEN(i915, 6)) अणु
		gt->क्रमcewake = पूर्णांकel_uncore_पढ़ो_fw(uncore, FORCEWAKE);
		gt->gab_ctl = पूर्णांकel_uncore_पढ़ो(uncore, GAB_CTL);
		gt->gfx_mode = पूर्णांकel_uncore_पढ़ो(uncore, GFX_MODE);
	पूर्ण

	/* 2: Registers which beदीर्घ to multiple generations */
	अगर (INTEL_GEN(i915) >= 7)
		gt->क्रमcewake = पूर्णांकel_uncore_पढ़ो_fw(uncore, FORCEWAKE_MT);

	अगर (INTEL_GEN(i915) >= 6) अणु
		gt->derrmr = पूर्णांकel_uncore_पढ़ो(uncore, DERRMR);
		अगर (INTEL_GEN(i915) < 12) अणु
			gt->error = पूर्णांकel_uncore_पढ़ो(uncore, ERROR_GEN6);
			gt->करोne_reg = पूर्णांकel_uncore_पढ़ो(uncore, DONE_REG);
		पूर्ण
	पूर्ण

	/* 3: Feature specअगरic रेजिस्टरs */
	अगर (IS_GEN_RANGE(i915, 6, 7)) अणु
		gt->gam_ecochk = पूर्णांकel_uncore_पढ़ो(uncore, GAM_ECOCHK);
		gt->gac_eco = पूर्णांकel_uncore_पढ़ो(uncore, GAC_ECO_BITS);
	पूर्ण

	अगर (IS_GEN_RANGE(i915, 8, 11))
		gt->gtt_cache = पूर्णांकel_uncore_पढ़ो(uncore, HSW_GTT_CACHE_EN);

	अगर (IS_GEN(i915, 12))
		gt->aux_err = पूर्णांकel_uncore_पढ़ो(uncore, GEN12_AUX_ERR_DBG);

	अगर (INTEL_GEN(i915) >= 12) अणु
		क्रम (i = 0; i < GEN12_SFC_DONE_MAX; i++) अणु
			gt->sfc_करोne[i] =
				पूर्णांकel_uncore_पढ़ो(uncore, GEN12_SFC_DONE(i));
		पूर्ण

		gt->gam_करोne = पूर्णांकel_uncore_पढ़ो(uncore, GEN12_GAM_DONE);
	पूर्ण

	/* 4: Everything अन्यथा */
	अगर (INTEL_GEN(i915) >= 11) अणु
		gt->ier = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_DE_MISC_IER);
		gt->gtier[0] =
			पूर्णांकel_uncore_पढ़ो(uncore,
					  GEN11_RENDER_COPY_INTR_ENABLE);
		gt->gtier[1] =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN11_VCS_VECS_INTR_ENABLE);
		gt->gtier[2] =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN11_GUC_SG_INTR_ENABLE);
		gt->gtier[3] =
			पूर्णांकel_uncore_पढ़ो(uncore,
					  GEN11_GPM_WGBOXPERF_INTR_ENABLE);
		gt->gtier[4] =
			पूर्णांकel_uncore_पढ़ो(uncore,
					  GEN11_CRYPTO_RSVD_INTR_ENABLE);
		gt->gtier[5] =
			पूर्णांकel_uncore_पढ़ो(uncore,
					  GEN11_GUNIT_CSME_INTR_ENABLE);
		gt->ngtier = 6;
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
		gt->ier = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_DE_MISC_IER);
		क्रम (i = 0; i < 4; i++)
			gt->gtier[i] =
				पूर्णांकel_uncore_पढ़ो(uncore, GEN8_GT_IER(i));
		gt->ngtier = 4;
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(i915)) अणु
		gt->ier = पूर्णांकel_uncore_पढ़ो(uncore, DEIER);
		gt->gtier[0] = पूर्णांकel_uncore_पढ़ो(uncore, GTIER);
		gt->ngtier = 1;
	पूर्ण अन्यथा अगर (IS_GEN(i915, 2)) अणु
		gt->ier = पूर्णांकel_uncore_पढ़ो16(uncore, GEN2_IER);
	पूर्ण अन्यथा अगर (!IS_VALLEYVIEW(i915)) अणु
		gt->ier = पूर्णांकel_uncore_पढ़ो(uncore, GEN2_IER);
	पूर्ण
	gt->eir = पूर्णांकel_uncore_पढ़ो(uncore, EIR);
	gt->pgtbl_er = पूर्णांकel_uncore_पढ़ो(uncore, PGTBL_ER);
पूर्ण

अटल व्योम gt_record_info(काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	स_नकल(&gt->info, &gt->_gt->info, माप(काष्ठा पूर्णांकel_gt_info));
पूर्ण

/*
 * Generate a semi-unique error code. The code is not meant to have meaning, The
 * code's only purpose is to try to prevent false duplicated bug reports by
 * grossly estimating a GPU error state.
 *
 * TODO Ideally, hashing the batchbuffer would be a very nice way to determine
 * the hang अगर we could strip the GTT offset inक्रमmation from it.
 *
 * It's only a small step better than a अक्रमom number in its current क्रमm.
 */
अटल u32 generate_ecode(स्थिर काष्ठा पूर्णांकel_engine_coredump *ee)
अणु
	/*
	 * IPEHR would be an ideal way to detect errors, as it's the gross
	 * measure of "the command that hung." However, has some very common
	 * synchronization commands which almost always appear in the हाल
	 * strictly a client bug. Use instकरोne to dअगरferentiate those some.
	 */
	वापस ee ? ee->ipehr ^ ee->instकरोne.instकरोne : 0;
पूर्ण

अटल स्थिर अक्षर *error_msg(काष्ठा i915_gpu_coredump *error)
अणु
	काष्ठा पूर्णांकel_engine_coredump *first = शून्य;
	अचिन्हित पूर्णांक hung_classes = 0;
	काष्ठा पूर्णांकel_gt_coredump *gt;
	पूर्णांक len;

	क्रम (gt = error->gt; gt; gt = gt->next) अणु
		काष्ठा पूर्णांकel_engine_coredump *cs;

		क्रम (cs = gt->engine; cs; cs = cs->next) अणु
			अगर (cs->hung) अणु
				hung_classes |= BIT(cs->engine->uabi_class);
				अगर (!first)
					first = cs;
			पूर्ण
		पूर्ण
	पूर्ण

	len = scnम_लिखो(error->error_msg, माप(error->error_msg),
			"GPU HANG: ecode %d:%x:%08x",
			INTEL_GEN(error->i915), hung_classes,
			generate_ecode(first));
	अगर (first && first->context.pid) अणु
		/* Just show the first executing process, more is confusing */
		len += scnम_लिखो(error->error_msg + len,
				 माप(error->error_msg) - len,
				 ", in %s [%d]",
				 first->context.comm, first->context.pid);
	पूर्ण

	वापस error->error_msg;
पूर्ण

अटल व्योम capture_gen(काष्ठा i915_gpu_coredump *error)
अणु
	काष्ठा drm_i915_निजी *i915 = error->i915;

	error->wakelock = atomic_पढ़ो(&i915->runसमय_pm.wakeref_count);
	error->suspended = i915->runसमय_pm.suspended;

	error->iommu = -1;
#अगर_घोषित CONFIG_INTEL_IOMMU
	error->iommu = पूर्णांकel_iommu_gfx_mapped;
#पूर्ण_अगर
	error->reset_count = i915_reset_count(&i915->gpu_error);
	error->suspend_count = i915->suspend_count;

	i915_params_copy(&error->params, &i915->params);
	स_नकल(&error->device_info,
	       INTEL_INFO(i915),
	       माप(error->device_info));
	स_नकल(&error->runसमय_info,
	       RUNTIME_INFO(i915),
	       माप(error->runसमय_info));
	error->driver_caps = i915->caps;
पूर्ण

काष्ठा i915_gpu_coredump *
i915_gpu_coredump_alloc(काष्ठा drm_i915_निजी *i915, gfp_t gfp)
अणु
	काष्ठा i915_gpu_coredump *error;

	अगर (!i915->params.error_capture)
		वापस शून्य;

	error = kzalloc(माप(*error), gfp);
	अगर (!error)
		वापस शून्य;

	kref_init(&error->ref);
	error->i915 = i915;

	error->समय = kसमय_get_real();
	error->bootसमय = kसमय_get_bootसमय();
	error->upसमय = kसमय_sub(kसमय_get(), i915->gt.last_init_समय);
	error->capture = jअगरfies;

	capture_gen(error);

	वापस error;
पूर्ण

#घोषणा DAY_AS_SECONDS(x) (24 * 60 * 60 * (x))

काष्ठा पूर्णांकel_gt_coredump *
पूर्णांकel_gt_coredump_alloc(काष्ठा पूर्णांकel_gt *gt, gfp_t gfp)
अणु
	काष्ठा पूर्णांकel_gt_coredump *gc;

	gc = kzalloc(माप(*gc), gfp);
	अगर (!gc)
		वापस शून्य;

	gc->_gt = gt;
	gc->awake = पूर्णांकel_gt_pm_is_awake(gt);

	gt_record_regs(gc);
	gt_record_fences(gc);

	वापस gc;
पूर्ण

काष्ठा i915_vma_compress *
i915_vma_capture_prepare(काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	काष्ठा i915_vma_compress *compress;

	compress = kदो_स्मृति(माप(*compress), ALLOW_FAIL);
	अगर (!compress)
		वापस शून्य;

	अगर (!compress_init(compress)) अणु
		kमुक्त(compress);
		वापस शून्य;
	पूर्ण

	वापस compress;
पूर्ण

व्योम i915_vma_capture_finish(काष्ठा पूर्णांकel_gt_coredump *gt,
			     काष्ठा i915_vma_compress *compress)
अणु
	अगर (!compress)
		वापस;

	compress_fini(compress);
	kमुक्त(compress);
पूर्ण

काष्ठा i915_gpu_coredump *
i915_gpu_coredump(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा i915_gpu_coredump *error;

	/* Check अगर GPU capture has been disabled */
	error = READ_ONCE(i915->gpu_error.first_error);
	अगर (IS_ERR(error))
		वापस error;

	error = i915_gpu_coredump_alloc(i915, ALLOW_FAIL);
	अगर (!error)
		वापस ERR_PTR(-ENOMEM);

	error->gt = पूर्णांकel_gt_coredump_alloc(gt, ALLOW_FAIL);
	अगर (error->gt) अणु
		काष्ठा i915_vma_compress *compress;

		compress = i915_vma_capture_prepare(error->gt);
		अगर (!compress) अणु
			kमुक्त(error->gt);
			kमुक्त(error);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		gt_record_info(error->gt);
		gt_record_engines(error->gt, engine_mask, compress);

		अगर (INTEL_INFO(i915)->has_gt_uc)
			error->gt->uc = gt_record_uc(error->gt, compress);

		i915_vma_capture_finish(error->gt, compress);

		error->simulated |= error->gt->simulated;
	पूर्ण

	error->overlay = पूर्णांकel_overlay_capture_error_state(i915);
	error->display = पूर्णांकel_display_capture_error_state(i915);

	वापस error;
पूर्ण

व्योम i915_error_state_store(काष्ठा i915_gpu_coredump *error)
अणु
	काष्ठा drm_i915_निजी *i915;
	अटल bool warned;

	अगर (IS_ERR_OR_शून्य(error))
		वापस;

	i915 = error->i915;
	drm_info(&i915->drm, "%s\n", error_msg(error));

	अगर (error->simulated ||
	    cmpxchg(&i915->gpu_error.first_error, शून्य, error))
		वापस;

	i915_gpu_coredump_get(error);

	अगर (!xchg(&warned, true) &&
	    kसमय_get_real_seconds() - DRIVER_TIMESTAMP < DAY_AS_SECONDS(180)) अणु
		pr_info("GPU hangs can indicate a bug anywhere in the entire gfx stack, including userspace.\n");
		pr_info("Please file a _new_ bug report at https://gitlab.freedesktop.org/drm/intel/issues/new.\n");
		pr_info("Please see https://gitlab.freedesktop.org/drm/intel/-/wikis/How-to-file-i915-bugs for details.\n");
		pr_info("drm/i915 developers can then reassign to the right component if it's not a kernel issue.\n");
		pr_info("The GPU crash dump is required to analyze GPU hangs, so please always attach it.\n");
		pr_info("GPU crash dump saved to /sys/class/drm/card%d/error\n",
			i915->drm.primary->index);
	पूर्ण
पूर्ण

/**
 * i915_capture_error_state - capture an error record क्रम later analysis
 * @gt: पूर्णांकel_gt which originated the hang
 * @engine_mask: hung engines
 *
 *
 * Should be called when an error is detected (either a hang or an error
 * पूर्णांकerrupt) to capture error state from the समय of the error.  Fills
 * out a काष्ठाure which becomes available in debugfs क्रम user level tools
 * to pick up.
 */
व्योम i915_capture_error_state(काष्ठा पूर्णांकel_gt *gt,
			      पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा i915_gpu_coredump *error;

	error = i915_gpu_coredump(gt, engine_mask);
	अगर (IS_ERR(error)) अणु
		cmpxchg(&gt->i915->gpu_error.first_error, शून्य, error);
		वापस;
	पूर्ण

	i915_error_state_store(error);
	i915_gpu_coredump_put(error);
पूर्ण

काष्ठा i915_gpu_coredump *
i915_first_error_state(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_gpu_coredump *error;

	spin_lock_irq(&i915->gpu_error.lock);
	error = i915->gpu_error.first_error;
	अगर (!IS_ERR_OR_शून्य(error))
		i915_gpu_coredump_get(error);
	spin_unlock_irq(&i915->gpu_error.lock);

	वापस error;
पूर्ण

व्योम i915_reset_error_state(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_gpu_coredump *error;

	spin_lock_irq(&i915->gpu_error.lock);
	error = i915->gpu_error.first_error;
	अगर (error != ERR_PTR(-ENODEV)) /* अगर disabled, always disabled */
		i915->gpu_error.first_error = शून्य;
	spin_unlock_irq(&i915->gpu_error.lock);

	अगर (!IS_ERR_OR_शून्य(error))
		i915_gpu_coredump_put(error);
पूर्ण

व्योम i915_disable_error_state(काष्ठा drm_i915_निजी *i915, पूर्णांक err)
अणु
	spin_lock_irq(&i915->gpu_error.lock);
	अगर (!i915->gpu_error.first_error)
		i915->gpu_error.first_error = ERR_PTR(err);
	spin_unlock_irq(&i915->gpu_error.lock);
पूर्ण
