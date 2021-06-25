<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश <linux/माला.स>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_vblank_work.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/समयr.h>

#समावेश <nvhw/class/cl907d.h>

#समावेश "nouveau_drv.h"
#समावेश "core.h"
#समावेश "head.h"
#समावेश "wndw.h"
#समावेश "handles.h"
#समावेश "crc.h"

अटल स्थिर अक्षर * स्थिर nv50_crc_sources[] = अणु
	[NV50_CRC_SOURCE_NONE] = "none",
	[NV50_CRC_SOURCE_AUTO] = "auto",
	[NV50_CRC_SOURCE_RG] = "rg",
	[NV50_CRC_SOURCE_OUTP_ACTIVE] = "outp-active",
	[NV50_CRC_SOURCE_OUTP_COMPLETE] = "outp-complete",
	[NV50_CRC_SOURCE_OUTP_INACTIVE] = "outp-inactive",
पूर्ण;

अटल पूर्णांक nv50_crc_parse_source(स्थिर अक्षर *buf, क्रमागत nv50_crc_source *s)
अणु
	पूर्णांक i;

	अगर (!buf) अणु
		*s = NV50_CRC_SOURCE_NONE;
		वापस 0;
	पूर्ण

	i = match_string(nv50_crc_sources, ARRAY_SIZE(nv50_crc_sources), buf);
	अगर (i < 0)
		वापस i;

	*s = i;
	वापस 0;
पूर्ण

पूर्णांक
nv50_crc_verअगरy_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_name,
		       माप_प्रकार *values_cnt)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(crtc->dev);
	क्रमागत nv50_crc_source source;

	अगर (nv50_crc_parse_source(source_name, &source) < 0) अणु
		NV_DEBUG(drm, "unknown source %s\n", source_name);
		वापस -EINVAL;
	पूर्ण

	*values_cnt = 1;
	वापस 0;
पूर्ण

स्थिर अक्षर *स्थिर *nv50_crc_get_sources(काष्ठा drm_crtc *crtc, माप_प्रकार *count)
अणु
	*count = ARRAY_SIZE(nv50_crc_sources);
	वापस nv50_crc_sources;
पूर्ण

अटल व्योम
nv50_crc_program_ctx(काष्ठा nv50_head *head,
		     काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(head->base.base.dev);
	काष्ठा nv50_core *core = disp->core;
	u32 पूर्णांकerlock[NV50_DISP_INTERLOCK__SIZE] = अणु 0 पूर्ण;

	core->func->crc->set_ctx(head, ctx);
	core->func->update(core, पूर्णांकerlock, false);
पूर्ण

अटल व्योम nv50_crc_ctx_flip_work(काष्ठा kthपढ़ो_work *base)
अणु
	काष्ठा drm_vblank_work *work = to_drm_vblank_work(base);
	काष्ठा nv50_crc *crc = container_of(work, काष्ठा nv50_crc, flip_work);
	काष्ठा nv50_head *head = container_of(crc, काष्ठा nv50_head, crc);
	काष्ठा drm_crtc *crtc = &head->base.base;
	काष्ठा nv50_disp *disp = nv50_disp(crtc->dev);
	u8 new_idx = crc->ctx_idx ^ 1;

	/*
	 * We करोn't want to accidentally रुको क्रम दीर्घer then the vblank, so
	 * try again क्रम the next vblank अगर we करोn't grab the lock
	 */
	अगर (!mutex_trylock(&disp->mutex)) अणु
		DRM_DEV_DEBUG_KMS(crtc->dev->dev,
				  "Lock contended, delaying CRC ctx flip for head-%d\n",
				  head->base.index);
		drm_vblank_work_schedule(work,
					 drm_crtc_vblank_count(crtc) + 1,
					 true);
		वापस;
	पूर्ण

	DRM_DEV_DEBUG_KMS(crtc->dev->dev,
			  "Flipping notifier ctx for head %d (%d -> %d)\n",
			  drm_crtc_index(crtc), crc->ctx_idx, new_idx);

	nv50_crc_program_ctx(head, शून्य);
	nv50_crc_program_ctx(head, &crc->ctx[new_idx]);
	mutex_unlock(&disp->mutex);

	spin_lock_irq(&crc->lock);
	crc->ctx_changed = true;
	spin_unlock_irq(&crc->lock);
पूर्ण

अटल अंतरभूत व्योम nv50_crc_reset_ctx(काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	स_रखो_io(ctx->mem.object.map.ptr, 0, ctx->mem.object.map.size);
पूर्ण

अटल व्योम
nv50_crc_get_entries(काष्ठा nv50_head *head,
		     स्थिर काष्ठा nv50_crc_func *func,
		     क्रमागत nv50_crc_source source)
अणु
	काष्ठा drm_crtc *crtc = &head->base.base;
	काष्ठा nv50_crc *crc = &head->crc;
	u32 output_crc;

	जबतक (crc->entry_idx < func->num_entries) अणु
		/*
		 * While Nvidia's करोcumentation says CRCs are written on each
		 * subsequent vblank after being enabled, in practice they
		 * aren't written immediately.
		 */
		output_crc = func->get_entry(head, &crc->ctx[crc->ctx_idx],
					     source, crc->entry_idx);
		अगर (!output_crc)
			वापस;

		drm_crtc_add_crc_entry(crtc, true, crc->frame, &output_crc);
		crc->frame++;
		crc->entry_idx++;
	पूर्ण
पूर्ण

व्योम nv50_crc_handle_vblank(काष्ठा nv50_head *head)
अणु
	काष्ठा drm_crtc *crtc = &head->base.base;
	काष्ठा nv50_crc *crc = &head->crc;
	स्थिर काष्ठा nv50_crc_func *func =
		nv50_disp(head->base.base.dev)->core->func->crc;
	काष्ठा nv50_crc_notअगरier_ctx *ctx;
	bool need_reschedule = false;

	अगर (!func)
		वापस;

	/*
	 * We करोn't lose events if we aren't able to report CRCs until the
	 * next vblank, so only report CRCs अगर the locks we need aren't
	 * contended to prevent missing an actual vblank event
	 */
	अगर (!spin_trylock(&crc->lock))
		वापस;

	अगर (!crc->src)
		जाओ out;

	ctx = &crc->ctx[crc->ctx_idx];
	अगर (crc->ctx_changed && func->ctx_finished(head, ctx)) अणु
		nv50_crc_get_entries(head, func, crc->src);

		crc->ctx_idx ^= 1;
		crc->entry_idx = 0;
		crc->ctx_changed = false;

		/*
		 * Unक्रमtunately when notअगरier contexts are changed during CRC
		 * capture, we will inevitably lose the CRC entry क्रम the
		 * frame where the hardware actually latched onto the first
		 * UPDATE. According to Nvidia's hardware engineers, there's
		 * no workaround क्रम this.
		 *
		 * Now, we could try to be smart here and calculate the number
		 * of missed CRCs based on audit बारtamps, but those were
		 * हटाओd starting with volta. Since we always flush our
		 * updates back-to-back without रुकोing, we'll just be
		 * optimistic and assume we always miss exactly one frame.
		 */
		DRM_DEV_DEBUG_KMS(head->base.base.dev->dev,
				  "Notifier ctx flip for head-%d finished, lost CRC for frame %llu\n",
				  head->base.index, crc->frame);
		crc->frame++;

		nv50_crc_reset_ctx(ctx);
		need_reschedule = true;
	पूर्ण

	nv50_crc_get_entries(head, func, crc->src);

	अगर (need_reschedule)
		drm_vblank_work_schedule(&crc->flip_work,
					 drm_crtc_vblank_count(crtc)
					 + crc->flip_threshold
					 - crc->entry_idx,
					 true);

out:
	spin_unlock(&crc->lock);
पूर्ण

अटल व्योम nv50_crc_रुको_ctx_finished(काष्ठा nv50_head *head,
				       स्थिर काष्ठा nv50_crc_func *func,
				       काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	काष्ठा drm_device *dev = head->base.base.dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	s64 ret;

	ret = nvअगर_msec(&drm->client.device, 50,
			अगर (func->ctx_finished(head, ctx)) अवरोध;);
	अगर (ret == -ETIMEDOUT)
		NV_ERROR(drm,
			 "CRC notifier ctx for head %d not finished after 50ms\n",
			 head->base.index);
	अन्यथा अगर (ret)
		NV_ATOMIC(drm,
			  "CRC notifier ctx for head-%d finished after %lldns\n",
			  head->base.index, ret);
पूर्ण

व्योम nv50_crc_atomic_stop_reporting(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा nv50_head *head = nv50_head(crtc);
		काष्ठा nv50_head_atom *asyh = nv50_head_atom(crtc_state);
		काष्ठा nv50_crc *crc = &head->crc;

		अगर (!asyh->clr.crc)
			जारी;

		spin_lock_irq(&crc->lock);
		crc->src = NV50_CRC_SOURCE_NONE;
		spin_unlock_irq(&crc->lock);

		drm_crtc_vblank_put(crtc);
		drm_vblank_work_cancel_sync(&crc->flip_work);

		NV_ATOMIC(nouveau_drm(crtc->dev),
			  "CRC reporting on vblank for head-%d disabled\n",
			  head->base.index);

		/* CRC generation is still enabled in hw, we'll just report
		 * any reमुख्यing CRC entries ourselves after it माला_लो disabled
		 * in hardware
		 */
	पूर्ण
पूर्ण

व्योम nv50_crc_atomic_init_notअगरier_contexts(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		काष्ठा nv50_head *head = nv50_head(crtc);
		काष्ठा nv50_head_atom *asyh = nv50_head_atom(new_crtc_state);
		काष्ठा nv50_crc *crc = &head->crc;
		पूर्णांक i;

		अगर (!asyh->set.crc)
			जारी;

		crc->entry_idx = 0;
		crc->ctx_changed = false;
		क्रम (i = 0; i < ARRAY_SIZE(crc->ctx); i++)
			nv50_crc_reset_ctx(&crc->ctx[i]);
	पूर्ण
पूर्ण

व्योम nv50_crc_atomic_release_notअगरier_contexts(काष्ठा drm_atomic_state *state)
अणु
	स्थिर काष्ठा nv50_crc_func *func =
		nv50_disp(state->dev)->core->func->crc;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		काष्ठा nv50_head *head = nv50_head(crtc);
		काष्ठा nv50_head_atom *asyh = nv50_head_atom(new_crtc_state);
		काष्ठा nv50_crc *crc = &head->crc;
		काष्ठा nv50_crc_notअगरier_ctx *ctx = &crc->ctx[crc->ctx_idx];

		अगर (!asyh->clr.crc)
			जारी;

		अगर (crc->ctx_changed) अणु
			nv50_crc_रुको_ctx_finished(head, func, ctx);
			ctx = &crc->ctx[crc->ctx_idx ^ 1];
		पूर्ण
		nv50_crc_रुको_ctx_finished(head, func, ctx);
	पूर्ण
पूर्ण

व्योम nv50_crc_atomic_start_reporting(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा nv50_head *head = nv50_head(crtc);
		काष्ठा nv50_head_atom *asyh = nv50_head_atom(crtc_state);
		काष्ठा nv50_crc *crc = &head->crc;
		u64 vbl_count;

		अगर (!asyh->set.crc)
			जारी;

		drm_crtc_vblank_get(crtc);

		spin_lock_irq(&crc->lock);
		vbl_count = drm_crtc_vblank_count(crtc);
		crc->frame = vbl_count;
		crc->src = asyh->crc.src;
		drm_vblank_work_schedule(&crc->flip_work,
					 vbl_count + crc->flip_threshold,
					 true);
		spin_unlock_irq(&crc->lock);

		NV_ATOMIC(nouveau_drm(crtc->dev),
			  "CRC reporting on vblank for head-%d enabled\n",
			  head->base.index);
	पूर्ण
पूर्ण

पूर्णांक nv50_crc_atomic_check_head(काष्ठा nv50_head *head,
			       काष्ठा nv50_head_atom *asyh,
			       काष्ठा nv50_head_atom *armh)
अणु
	काष्ठा nv50_atom *atom = nv50_atom(asyh->state.state);
	काष्ठा drm_device *dev = head->base.base.dev;
	काष्ठा nv50_disp *disp = nv50_disp(dev);
	bool changed = armh->crc.src != asyh->crc.src;

	अगर (!armh->crc.src && !asyh->crc.src) अणु
		asyh->set.crc = false;
		asyh->clr.crc = false;
		वापस 0;
	पूर्ण

	/* While we करोn't care about entry tags, Volta+ hw always needs the
	 * controlling wndw channel programmed to a wndw that's owned by our
	 * head
	 */
	अगर (asyh->crc.src && disp->disp->object.oclass >= GV100_DISP &&
	    !(BIT(asyh->crc.wndw) & asyh->wndw.owned)) अणु
		अगर (!asyh->wndw.owned) अणु
			/* TODO: once we support flexible channel ownership,
			 * we should ग_लिखो some code here to handle attempting
			 * to "steal" a plane: e.g. take a plane that is
			 * currently not-visible and owned by another head,
			 * and reassign it to this head. If we fail to करो so,
			 * we shuld reject the mode outright as CRC capture
			 * then becomes impossible.
			 */
			NV_ATOMIC(nouveau_drm(dev),
				  "No available wndws for CRC readback\n");
			वापस -EINVAL;
		पूर्ण
		asyh->crc.wndw = ffs(asyh->wndw.owned) - 1;
	पूर्ण

	अगर (drm_atomic_crtc_needs_modeset(&asyh->state) || changed ||
	    armh->crc.wndw != asyh->crc.wndw) अणु
		asyh->clr.crc = armh->crc.src && armh->state.active;
		asyh->set.crc = asyh->crc.src && asyh->state.active;
		अगर (changed)
			asyh->set.or |= armh->or.crc_raster !=
					asyh->or.crc_raster;

		अगर (asyh->clr.crc && asyh->set.crc)
			atom->flush_disable = true;
	पूर्ण अन्यथा अणु
		asyh->set.crc = false;
		asyh->clr.crc = false;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nv50_crc_atomic_check_outp(काष्ठा nv50_atom *atom)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	पूर्णांक i;

	अगर (atom->flush_disable)
		वापस;

	क्रम_each_oldnew_crtc_in_state(&atom->state, crtc, old_crtc_state,
				      new_crtc_state, i) अणु
		काष्ठा nv50_head_atom *armh = nv50_head_atom(old_crtc_state);
		काष्ठा nv50_head_atom *asyh = nv50_head_atom(new_crtc_state);
		काष्ठा nv50_outp_atom *outp_atom;
		काष्ठा nouveau_encoder *outp =
			nv50_real_outp(nv50_head_atom_get_encoder(armh));
		काष्ठा drm_encoder *encoder = &outp->base.base;

		अगर (!asyh->clr.crc)
			जारी;

		/*
		 * Re-programming ORs can't be करोne in the same flush as
		 * disabling CRCs
		 */
		list_क्रम_each_entry(outp_atom, &atom->outp, head) अणु
			अगर (outp_atom->encoder == encoder) अणु
				अगर (outp_atom->set.mask) अणु
					atom->flush_disable = true;
					वापस;
				पूर्ण अन्यथा अणु
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत nv50_crc_source_type
nv50_crc_source_type(काष्ठा nouveau_encoder *outp,
		     क्रमागत nv50_crc_source source)
अणु
	काष्ठा dcb_output *dcbe = outp->dcb;

	चयन (source) अणु
	हाल NV50_CRC_SOURCE_NONE: वापस NV50_CRC_SOURCE_TYPE_NONE;
	हाल NV50_CRC_SOURCE_RG:   वापस NV50_CRC_SOURCE_TYPE_RG;
	शेष:		   अवरोध;
	पूर्ण

	अगर (dcbe->location != DCB_LOC_ON_CHIP)
		वापस NV50_CRC_SOURCE_TYPE_PIOR;

	चयन (dcbe->type) अणु
	हाल DCB_OUTPUT_DP:	वापस NV50_CRC_SOURCE_TYPE_SF;
	हाल DCB_OUTPUT_ANALOG:	वापस NV50_CRC_SOURCE_TYPE_DAC;
	शेष:		वापस NV50_CRC_SOURCE_TYPE_SOR;
	पूर्ण
पूर्ण

व्योम nv50_crc_atomic_set(काष्ठा nv50_head *head,
			 काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा drm_crtc *crtc = &head->base.base;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nv50_crc *crc = &head->crc;
	स्थिर काष्ठा nv50_crc_func *func = nv50_disp(dev)->core->func->crc;
	काष्ठा nouveau_encoder *outp =
		nv50_real_outp(nv50_head_atom_get_encoder(asyh));

	func->set_src(head, outp->or,
		      nv50_crc_source_type(outp, asyh->crc.src),
		      &crc->ctx[crc->ctx_idx], asyh->crc.wndw);
पूर्ण

व्योम nv50_crc_atomic_clr(काष्ठा nv50_head *head)
अणु
	स्थिर काष्ठा nv50_crc_func *func =
		nv50_disp(head->base.base.dev)->core->func->crc;

	func->set_src(head, 0, NV50_CRC_SOURCE_TYPE_NONE, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
nv50_crc_raster_type(क्रमागत nv50_crc_source source)
अणु
	चयन (source) अणु
	हाल NV50_CRC_SOURCE_NONE:
	हाल NV50_CRC_SOURCE_AUTO:
	हाल NV50_CRC_SOURCE_RG:
	हाल NV50_CRC_SOURCE_OUTP_ACTIVE:
		वापस NV907D_HEAD_SET_CONTROL_OUTPUT_RESOURCE_CRC_MODE_ACTIVE_RASTER;
	हाल NV50_CRC_SOURCE_OUTP_COMPLETE:
		वापस NV907D_HEAD_SET_CONTROL_OUTPUT_RESOURCE_CRC_MODE_COMPLETE_RASTER;
	हाल NV50_CRC_SOURCE_OUTP_INACTIVE:
		वापस NV907D_HEAD_SET_CONTROL_OUTPUT_RESOURCE_CRC_MODE_NON_ACTIVE_RASTER;
	पूर्ण

	वापस 0;
पूर्ण

/* We handle mapping the memory क्रम CRC notअगरiers ourselves, since each
 * notअगरier needs it's own handle
 */
अटल अंतरभूत पूर्णांक
nv50_crc_ctx_init(काष्ठा nv50_head *head, काष्ठा nvअगर_mmu *mmu,
		  काष्ठा nv50_crc_notअगरier_ctx *ctx, माप_प्रकार len, पूर्णांक idx)
अणु
	काष्ठा nv50_core *core = nv50_disp(head->base.base.dev)->core;
	पूर्णांक ret;

	ret = nvअगर_mem_ctor_map(mmu, "kmsCrcNtfy", NVIF_MEM_VRAM, len, &ctx->mem);
	अगर (ret)
		वापस ret;

	ret = nvअगर_object_ctor(&core->chan.base.user, "kmsCrcNtfyCtxDma",
			       NV50_DISP_HANDLE_CRC_CTX(head, idx),
			       NV_DMA_IN_MEMORY,
			       &(काष्ठा nv_dma_v0) अणु
					.target = NV_DMA_V0_TARGET_VRAM,
					.access = NV_DMA_V0_ACCESS_RDWR,
					.start = ctx->mem.addr,
					.limit =  ctx->mem.addr
						+ ctx->mem.size - 1,
			       पूर्ण, माप(काष्ठा nv_dma_v0),
			       &ctx->ntfy);
	अगर (ret)
		जाओ fail_fini;

	वापस 0;

fail_fini:
	nvअगर_mem_dtor(&ctx->mem);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
nv50_crc_ctx_fini(काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	nvअगर_object_dtor(&ctx->ntfy);
	nvअगर_mem_dtor(&ctx->mem);
पूर्ण

पूर्णांक nv50_crc_set_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_str)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा nv50_head *head = nv50_head(crtc);
	काष्ठा nv50_crc *crc = &head->crc;
	स्थिर काष्ठा nv50_crc_func *func = nv50_disp(dev)->core->func->crc;
	काष्ठा nvअगर_mmu *mmu = &nouveau_drm(dev)->client.mmu;
	काष्ठा nv50_head_atom *asyh;
	काष्ठा drm_crtc_state *crtc_state;
	क्रमागत nv50_crc_source source;
	पूर्णांक ret = 0, ctx_flags = 0, i;

	ret = nv50_crc_parse_source(source_str, &source);
	अगर (ret)
		वापस ret;

	/*
	 * Since we करोn't want the user to accidentally interrupt us as we're
	 * disabling CRCs
	 */
	अगर (source)
		ctx_flags |= DRM_MODESET_ACQUIRE_INTERRUPTIBLE;
	drm_modeset_acquire_init(&ctx, ctx_flags);

	state = drm_atomic_state_alloc(dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ out_acquire_fini;
	पूर्ण
	state->acquire_ctx = &ctx;

	अगर (source) अणु
		क्रम (i = 0; i < ARRAY_SIZE(head->crc.ctx); i++) अणु
			ret = nv50_crc_ctx_init(head, mmu, &crc->ctx[i],
						func->notअगरier_len, i);
			अगर (ret)
				जाओ out_ctx_fini;
		पूर्ण
	पूर्ण

retry:
	crtc_state = drm_atomic_get_crtc_state(state, &head->base.base);
	अगर (IS_ERR(crtc_state)) अणु
		ret = PTR_ERR(crtc_state);
		अगर (ret == -EDEADLK)
			जाओ deadlock;
		अन्यथा अगर (ret)
			जाओ out_drop_locks;
	पूर्ण
	asyh = nv50_head_atom(crtc_state);
	asyh->crc.src = source;
	asyh->or.crc_raster = nv50_crc_raster_type(source);

	ret = drm_atomic_commit(state);
	अगर (ret == -EDEADLK)
		जाओ deadlock;
	अन्यथा अगर (ret)
		जाओ out_drop_locks;

	अगर (!source) अणु
		/*
		 * If the user specअगरied a custom flip threshold through
		 * debugfs, reset it
		 */
		crc->flip_threshold = func->flip_threshold;
	पूर्ण

out_drop_locks:
	drm_modeset_drop_locks(&ctx);
out_ctx_fini:
	अगर (!source || ret) अणु
		क्रम (i = 0; i < ARRAY_SIZE(crc->ctx); i++)
			nv50_crc_ctx_fini(&crc->ctx[i]);
	पूर्ण
	drm_atomic_state_put(state);
out_acquire_fini:
	drm_modeset_acquire_fini(&ctx);
	वापस ret;

deadlock:
	drm_atomic_state_clear(state);
	drm_modeset_backoff(&ctx);
	जाओ retry;
पूर्ण

अटल पूर्णांक
nv50_crc_debugfs_flip_threshold_get(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा nv50_head *head = m->निजी;
	काष्ठा drm_crtc *crtc = &head->base.base;
	काष्ठा nv50_crc *crc = &head->crc;
	पूर्णांक ret;

	ret = drm_modeset_lock_single_पूर्णांकerruptible(&crtc->mutex);
	अगर (ret)
		वापस ret;

	seq_म_लिखो(m, "%d\n", crc->flip_threshold);

	drm_modeset_unlock(&crtc->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
nv50_crc_debugfs_flip_threshold_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, nv50_crc_debugfs_flip_threshold_get,
			   inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार
nv50_crc_debugfs_flip_threshold_set(काष्ठा file *file,
				    स्थिर अक्षर __user *ubuf, माप_प्रकार len,
				    loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा nv50_head *head = m->निजी;
	काष्ठा nv50_head_atom *armh;
	काष्ठा drm_crtc *crtc = &head->base.base;
	काष्ठा nouveau_drm *drm = nouveau_drm(crtc->dev);
	काष्ठा nv50_crc *crc = &head->crc;
	स्थिर काष्ठा nv50_crc_func *func =
		nv50_disp(crtc->dev)->core->func->crc;
	पूर्णांक value, ret;

	ret = kstrtoपूर्णांक_from_user(ubuf, len, 10, &value);
	अगर (ret)
		वापस ret;

	अगर (value > func->flip_threshold)
		वापस -EINVAL;
	अन्यथा अगर (value == -1)
		value = func->flip_threshold;
	अन्यथा अगर (value < -1)
		वापस -EINVAL;

	ret = drm_modeset_lock_single_पूर्णांकerruptible(&crtc->mutex);
	अगर (ret)
		वापस ret;

	armh = nv50_head_atom(crtc->state);
	अगर (armh->crc.src) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	NV_DEBUG(drm,
		 "Changing CRC flip threshold for next capture on head-%d to %d\n",
		 head->base.index, value);
	crc->flip_threshold = value;
	ret = len;

out:
	drm_modeset_unlock(&crtc->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations nv50_crc_flip_threshold_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = nv50_crc_debugfs_flip_threshold_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = nv50_crc_debugfs_flip_threshold_set,
पूर्ण;

पूर्णांक nv50_head_crc_late_रेजिस्टर(काष्ठा nv50_head *head)
अणु
	काष्ठा drm_crtc *crtc = &head->base.base;
	स्थिर काष्ठा nv50_crc_func *func =
		nv50_disp(crtc->dev)->core->func->crc;
	काष्ठा dentry *root;

	अगर (!func || !crtc->debugfs_entry)
		वापस 0;

	root = debugfs_create_dir("nv_crc", crtc->debugfs_entry);
	debugfs_create_file("flip_threshold", 0644, root, head,
			    &nv50_crc_flip_threshold_fops);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
nv50_crc_init_head(काष्ठा nv50_disp *disp, स्थिर काष्ठा nv50_crc_func *func,
		   काष्ठा nv50_head *head)
अणु
	काष्ठा nv50_crc *crc = &head->crc;

	crc->flip_threshold = func->flip_threshold;
	spin_lock_init(&crc->lock);
	drm_vblank_work_init(&crc->flip_work, &head->base.base,
			     nv50_crc_ctx_flip_work);
पूर्ण

व्योम nv50_crc_init(काष्ठा drm_device *dev)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(dev);
	काष्ठा drm_crtc *crtc;
	स्थिर काष्ठा nv50_crc_func *func = disp->core->func->crc;

	अगर (!func)
		वापस;

	drm_क्रम_each_crtc(crtc, dev)
		nv50_crc_init_head(disp, func, nv50_head(crtc));
पूर्ण
