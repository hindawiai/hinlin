<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_util.h>

#समावेश "mdp5_kms.h"
#समावेश "mdp5_smp.h"


काष्ठा mdp5_smp अणु
	काष्ठा drm_device *dev;

	uपूर्णांक8_t reserved[MAX_CLIENTS]; /* fixed MMBs allocation per client */

	पूर्णांक blk_cnt;
	पूर्णांक blk_size;

	/* रेजिस्टर cache */
	u32 alloc_w[22];
	u32 alloc_r[22];
	u32 pipe_reqprio_fअगरo_wm0[SSPP_MAX];
	u32 pipe_reqprio_fअगरo_wm1[SSPP_MAX];
	u32 pipe_reqprio_fअगरo_wm2[SSPP_MAX];
पूर्ण;

अटल अंतरभूत
काष्ठा mdp5_kms *get_kms(काष्ठा mdp5_smp *smp)
अणु
	काष्ठा msm_drm_निजी *priv = smp->dev->dev_निजी;

	वापस to_mdp5_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल अंतरभूत u32 pipe2client(क्रमागत mdp5_pipe pipe, पूर्णांक plane)
अणु
#घोषणा CID_UNUSED	0

	अगर (WARN_ON(plane >= pipe2nclients(pipe)))
		वापस CID_UNUSED;

	/*
	 * Note on SMP clients:
	 * For ViG pipes, fetch Y/Cr/Cb-components clients are always
	 * consecutive, and in that order.
	 *
	 * e.g.:
	 * अगर mdp5_cfg->smp.clients[SSPP_VIG0] = N,
	 *	Y  plane's client ID is N
	 *	Cr plane's client ID is N + 1
	 *	Cb plane's client ID is N + 2
	 */

	वापस mdp5_cfg->smp.clients[pipe] + plane;
पूर्ण

/* allocate blocks क्रम the specअगरied request: */
अटल पूर्णांक smp_request_block(काष्ठा mdp5_smp *smp,
		काष्ठा mdp5_smp_state *state,
		u32 cid, पूर्णांक nblks)
अणु
	व्योम *cs = state->client_state[cid];
	पूर्णांक i, avail, cnt = smp->blk_cnt;
	uपूर्णांक8_t reserved;

	/* we shouldn't be requesting blocks क्रम an in-use client: */
	WARN_ON(biपंचांगap_weight(cs, cnt) > 0);

	reserved = smp->reserved[cid];

	अगर (reserved) अणु
		nblks = max(0, nblks - reserved);
		DBG("%d MMBs allocated (%d reserved)", nblks, reserved);
	पूर्ण

	avail = cnt - biपंचांगap_weight(state->state, cnt);
	अगर (nblks > avail) अणु
		DRM_DEV_ERROR(smp->dev->dev, "out of blks (req=%d > avail=%d)\n",
				nblks, avail);
		वापस -ENOSPC;
	पूर्ण

	क्रम (i = 0; i < nblks; i++) अणु
		पूर्णांक blk = find_first_zero_bit(state->state, cnt);
		set_bit(blk, cs);
		set_bit(blk, state->state);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_fअगरo_thresholds(काष्ठा mdp5_smp *smp,
		क्रमागत mdp5_pipe pipe, पूर्णांक nblks)
अणु
	u32 smp_entries_per_blk = smp->blk_size / (128 / BITS_PER_BYTE);
	u32 val;

	/* 1/4 of SMP pool that is being fetched */
	val = (nblks * smp_entries_per_blk) / 4;

	smp->pipe_reqprio_fअगरo_wm0[pipe] = val * 1;
	smp->pipe_reqprio_fअगरo_wm1[pipe] = val * 2;
	smp->pipe_reqprio_fअगरo_wm2[pipe] = val * 3;
पूर्ण

/*
 * NOTE: looks like अगर horizontal decimation is used (अगर we supported that)
 * then the width used to calculate SMP block requirements is the post-
 * decimated width.  Ie. SMP buffering sits करोwnstream of decimation (which
 * presumably happens during the dma from scanout buffer).
 */
uपूर्णांक32_t mdp5_smp_calculate(काष्ठा mdp5_smp *smp,
		स्थिर काष्ठा mdp_क्रमmat *क्रमmat,
		u32 width, bool hdecim)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat->base.pixel_क्रमmat);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(smp);
	पूर्णांक rev = mdp5_cfg_get_hw_rev(mdp5_kms->cfg);
	पूर्णांक i, hsub, nplanes, nlines;
	uपूर्णांक32_t blkcfg = 0;

	nplanes = info->num_planes;
	hsub = info->hsub;

	/* dअगरferent अगर BWC (compressed framebuffer?) enabled: */
	nlines = 2;

	/* Newer MDPs have split/packing logic, which fetches sub-sampled
	 * U and V components (splits them from Y अगर necessary) and packs
	 * them together, ग_लिखोs to SMP using a single client.
	 */
	अगर ((rev > 0) && (क्रमmat->chroma_sample > CHROMA_FULL)) अणु
		nplanes = 2;

		/* अगर decimation is enabled, HW decimates less on the
		 * sub sampled chroma components
		 */
		अगर (hdecim && (hsub > 1))
			hsub = 1;
	पूर्ण

	क्रम (i = 0; i < nplanes; i++) अणु
		पूर्णांक n, fetch_stride, cpp;

		cpp = info->cpp[i];
		fetch_stride = width * cpp / (i ? hsub : 1);

		n = DIV_ROUND_UP(fetch_stride * nlines, smp->blk_size);

		/* क्रम hw rev v1.00 */
		अगर (rev == 0)
			n = roundup_घात_of_two(n);

		blkcfg |= (n << (8 * i));
	पूर्ण

	वापस blkcfg;
पूर्ण

पूर्णांक mdp5_smp_assign(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state,
		क्रमागत mdp5_pipe pipe, uपूर्णांक32_t blkcfg)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(smp);
	काष्ठा drm_device *dev = mdp5_kms->dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < pipe2nclients(pipe); i++) अणु
		u32 cid = pipe2client(pipe, i);
		पूर्णांक n = blkcfg & 0xff;

		अगर (!n)
			जारी;

		DBG("%s[%d]: request %d SMP blocks", pipe2name(pipe), i, n);
		ret = smp_request_block(smp, state, cid, n);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "Cannot allocate %d SMP blocks: %d\n",
					n, ret);
			वापस ret;
		पूर्ण

		blkcfg >>= 8;
	पूर्ण

	state->asचिन्हित |= (1 << pipe);

	वापस 0;
पूर्ण

/* Release SMP blocks क्रम all clients of the pipe */
व्योम mdp5_smp_release(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state,
		क्रमागत mdp5_pipe pipe)
अणु
	पूर्णांक i;
	पूर्णांक cnt = smp->blk_cnt;

	क्रम (i = 0; i < pipe2nclients(pipe); i++) अणु
		u32 cid = pipe2client(pipe, i);
		व्योम *cs = state->client_state[cid];

		/* update global state: */
		biपंचांगap_andnot(state->state, state->state, cs, cnt);

		/* clear client's state */
		biपंचांगap_zero(cs, cnt);
	पूर्ण

	state->released |= (1 << pipe);
पूर्ण

/* NOTE: SMP_ALLOC_* regs are *not* द्विगुन buffered, so release has to
 * happen after scanout completes.
 */
अटल अचिन्हित update_smp_state(काष्ठा mdp5_smp *smp,
		u32 cid, mdp5_smp_state_t *asचिन्हित)
अणु
	पूर्णांक cnt = smp->blk_cnt;
	अचिन्हित nblks = 0;
	u32 blk, val;

	क्रम_each_set_bit(blk, *asचिन्हित, cnt) अणु
		पूर्णांक idx = blk / 3;
		पूर्णांक fld = blk % 3;

		val = smp->alloc_w[idx];

		चयन (fld) अणु
		हाल 0:
			val &= ~MDP5_SMP_ALLOC_W_REG_CLIENT0__MASK;
			val |= MDP5_SMP_ALLOC_W_REG_CLIENT0(cid);
			अवरोध;
		हाल 1:
			val &= ~MDP5_SMP_ALLOC_W_REG_CLIENT1__MASK;
			val |= MDP5_SMP_ALLOC_W_REG_CLIENT1(cid);
			अवरोध;
		हाल 2:
			val &= ~MDP5_SMP_ALLOC_W_REG_CLIENT2__MASK;
			val |= MDP5_SMP_ALLOC_W_REG_CLIENT2(cid);
			अवरोध;
		पूर्ण

		smp->alloc_w[idx] = val;
		smp->alloc_r[idx] = val;

		nblks++;
	पूर्ण

	वापस nblks;
पूर्ण

अटल व्योम ग_लिखो_smp_alloc_regs(काष्ठा mdp5_smp *smp)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(smp);
	पूर्णांक i, num_regs;

	num_regs = smp->blk_cnt / 3 + 1;

	क्रम (i = 0; i < num_regs; i++) अणु
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SMP_ALLOC_W_REG(i),
			   smp->alloc_w[i]);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SMP_ALLOC_R_REG(i),
			   smp->alloc_r[i]);
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_smp_fअगरo_regs(काष्ठा mdp5_smp *smp)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(smp);
	पूर्णांक i;

	क्रम (i = 0; i < mdp5_kms->num_hwpipes; i++) अणु
		काष्ठा mdp5_hw_pipe *hwpipe = mdp5_kms->hwpipes[i];
		क्रमागत mdp5_pipe pipe = hwpipe->pipe;

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_REQPRIO_FIFO_WM_0(pipe),
			   smp->pipe_reqprio_fअगरo_wm0[pipe]);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_REQPRIO_FIFO_WM_1(pipe),
			   smp->pipe_reqprio_fअगरo_wm1[pipe]);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_REQPRIO_FIFO_WM_2(pipe),
			   smp->pipe_reqprio_fअगरo_wm2[pipe]);
	पूर्ण
पूर्ण

व्योम mdp5_smp_prepare_commit(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state)
अणु
	क्रमागत mdp5_pipe pipe;

	क्रम_each_set_bit(pipe, &state->asचिन्हित, माप(state->asचिन्हित) * 8) अणु
		अचिन्हित i, nblks = 0;

		क्रम (i = 0; i < pipe2nclients(pipe); i++) अणु
			u32 cid = pipe2client(pipe, i);
			व्योम *cs = state->client_state[cid];

			nblks += update_smp_state(smp, cid, cs);

			DBG("assign %s:%u, %u blks",
				pipe2name(pipe), i, nblks);
		पूर्ण

		set_fअगरo_thresholds(smp, pipe, nblks);
	पूर्ण

	ग_लिखो_smp_alloc_regs(smp);
	ग_लिखो_smp_fअगरo_regs(smp);

	state->asचिन्हित = 0;
पूर्ण

व्योम mdp5_smp_complete_commit(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state)
अणु
	क्रमागत mdp5_pipe pipe;

	क्रम_each_set_bit(pipe, &state->released, माप(state->released) * 8) अणु
		DBG("release %s", pipe2name(pipe));
		set_fअगरo_thresholds(smp, pipe, 0);
	पूर्ण

	ग_लिखो_smp_fअगरo_regs(smp);

	state->released = 0;
पूर्ण

व्योम mdp5_smp_dump(काष्ठा mdp5_smp *smp, काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(smp);
	काष्ठा mdp5_hw_pipe_state *hwpstate;
	काष्ठा mdp5_smp_state *state;
	काष्ठा mdp5_global_state *global_state;
	पूर्णांक total = 0, i, j;

	drm_म_लिखो(p, "name\tinuse\tplane\n");
	drm_म_लिखो(p, "----\t-----\t-----\n");

	अगर (drm_can_sleep())
		drm_modeset_lock(&mdp5_kms->glob_state_lock, शून्य);

	global_state = mdp5_get_existing_global_state(mdp5_kms);

	/* grab these *after* we hold the state_lock */
	hwpstate = &global_state->hwpipe;
	state = &global_state->smp;

	क्रम (i = 0; i < mdp5_kms->num_hwpipes; i++) अणु
		काष्ठा mdp5_hw_pipe *hwpipe = mdp5_kms->hwpipes[i];
		काष्ठा drm_plane *plane = hwpstate->hwpipe_to_plane[hwpipe->idx];
		क्रमागत mdp5_pipe pipe = hwpipe->pipe;
		क्रम (j = 0; j < pipe2nclients(pipe); j++) अणु
			u32 cid = pipe2client(pipe, j);
			व्योम *cs = state->client_state[cid];
			पूर्णांक inuse = biपंचांगap_weight(cs, smp->blk_cnt);

			drm_म_लिखो(p, "%s:%d\t%d\t%s\n",
				pipe2name(pipe), j, inuse,
				plane ? plane->name : शून्य);

			total += inuse;
		पूर्ण
	पूर्ण

	drm_म_लिखो(p, "TOTAL:\t%d\t(of %d)\n", total, smp->blk_cnt);
	drm_म_लिखो(p, "AVAIL:\t%d\n", smp->blk_cnt -
			biपंचांगap_weight(state->state, smp->blk_cnt));

	अगर (drm_can_sleep())
		drm_modeset_unlock(&mdp5_kms->glob_state_lock);
पूर्ण

व्योम mdp5_smp_destroy(काष्ठा mdp5_smp *smp)
अणु
	kमुक्त(smp);
पूर्ण

काष्ठा mdp5_smp *mdp5_smp_init(काष्ठा mdp5_kms *mdp5_kms, स्थिर काष्ठा mdp5_smp_block *cfg)
अणु
	काष्ठा mdp5_smp_state *state;
	काष्ठा mdp5_global_state *global_state;
	काष्ठा mdp5_smp *smp = शून्य;
	पूर्णांक ret;

	smp = kzalloc(माप(*smp), GFP_KERNEL);
	अगर (unlikely(!smp)) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	smp->dev = mdp5_kms->dev;
	smp->blk_cnt = cfg->mmb_count;
	smp->blk_size = cfg->mmb_size;

	global_state = mdp5_get_existing_global_state(mdp5_kms);
	state = &global_state->smp;

	/* अटलally tied MMBs cannot be re-allocated: */
	biपंचांगap_copy(state->state, cfg->reserved_state, smp->blk_cnt);
	स_नकल(smp->reserved, cfg->reserved, माप(smp->reserved));

	वापस smp;
fail:
	अगर (smp)
		mdp5_smp_destroy(smp);

	वापस ERR_PTR(ret);
पूर्ण
