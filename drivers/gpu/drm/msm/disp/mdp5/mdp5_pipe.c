<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "mdp5_kms.h"

पूर्णांक mdp5_pipe_assign(काष्ठा drm_atomic_state *s, काष्ठा drm_plane *plane,
		     uपूर्णांक32_t caps, uपूर्णांक32_t blkcfg,
		     काष्ठा mdp5_hw_pipe **hwpipe,
		     काष्ठा mdp5_hw_pipe **r_hwpipe)
अणु
	काष्ठा msm_drm_निजी *priv = s->dev->dev_निजी;
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(priv->kms));
	काष्ठा mdp5_global_state *new_global_state, *old_global_state;
	काष्ठा mdp5_hw_pipe_state *old_state, *new_state;
	पूर्णांक i, j;

	new_global_state = mdp5_get_global_state(s);
	अगर (IS_ERR(new_global_state))
		वापस PTR_ERR(new_global_state);

	/* grab old_state after mdp5_get_global_state(), since now we hold lock: */
	old_global_state = mdp5_get_existing_global_state(mdp5_kms);

	old_state = &old_global_state->hwpipe;
	new_state = &new_global_state->hwpipe;

	क्रम (i = 0; i < mdp5_kms->num_hwpipes; i++) अणु
		काष्ठा mdp5_hw_pipe *cur = mdp5_kms->hwpipes[i];

		/* skip अगर alपढ़ोy in-use.. check both new and old state,
		 * since we cannot immediately re-use a pipe that is
		 * released in the current update in some हालs:
		 *  (1) mdp5 can have SMP (non-द्विगुन-buffered)
		 *  (2) hw pipe previously asचिन्हित to dअगरferent CRTC
		 *      (vblanks might not be aligned)
		 */
		अगर (new_state->hwpipe_to_plane[cur->idx] ||
				old_state->hwpipe_to_plane[cur->idx])
			जारी;

		/* skip अगर करोesn't support some required caps: */
		अगर (caps & ~cur->caps)
			जारी;

		/*
		 * करोn't assign a cursor pipe to a plane that isn't going to
		 * be used as a cursor
		 */
		अगर (cur->caps & MDP_PIPE_CAP_CURSOR &&
				plane->type != DRM_PLANE_TYPE_CURSOR)
			जारी;

		/* possible candidate, take the one with the
		 * fewest unneeded caps bits set:
		 */
		अगर (!(*hwpipe) || (hweight_दीर्घ(cur->caps & ~caps) <
				   hweight_दीर्घ((*hwpipe)->caps & ~caps))) अणु
			bool r_found = false;

			अगर (r_hwpipe) अणु
				क्रम (j = i + 1; j < mdp5_kms->num_hwpipes;
				     j++) अणु
					काष्ठा mdp5_hw_pipe *r_cur =
							mdp5_kms->hwpipes[j];

					/* reject dअगरferent types of hwpipes */
					अगर (r_cur->caps != cur->caps)
						जारी;

					/* respect priority, eg. VIG0 > VIG1 */
					अगर (cur->pipe > r_cur->pipe)
						जारी;

					*r_hwpipe = r_cur;
					r_found = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!r_hwpipe || r_found)
				*hwpipe = cur;
		पूर्ण
	पूर्ण

	अगर (!(*hwpipe))
		वापस -ENOMEM;

	अगर (r_hwpipe && !(*r_hwpipe))
		वापस -ENOMEM;

	अगर (mdp5_kms->smp) अणु
		पूर्णांक ret;

		/* We करोn't support SMP and 2 hwpipes/plane together */
		WARN_ON(r_hwpipe);

		DBG("%s: alloc SMP blocks", (*hwpipe)->name);
		ret = mdp5_smp_assign(mdp5_kms->smp, &new_global_state->smp,
				(*hwpipe)->pipe, blkcfg);
		अगर (ret)
			वापस -ENOMEM;

		(*hwpipe)->blkcfg = blkcfg;
	पूर्ण

	DBG("%s: assign to plane %s for caps %x",
			(*hwpipe)->name, plane->name, caps);
	new_state->hwpipe_to_plane[(*hwpipe)->idx] = plane;

	अगर (r_hwpipe) अणु
		DBG("%s: assign to right of plane %s for caps %x",
		    (*r_hwpipe)->name, plane->name, caps);
		new_state->hwpipe_to_plane[(*r_hwpipe)->idx] = plane;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mdp5_pipe_release(काष्ठा drm_atomic_state *s, काष्ठा mdp5_hw_pipe *hwpipe)
अणु
	काष्ठा msm_drm_निजी *priv = s->dev->dev_निजी;
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(priv->kms));
	काष्ठा mdp5_global_state *state = mdp5_get_global_state(s);
	काष्ठा mdp5_hw_pipe_state *new_state = &state->hwpipe;

	अगर (!hwpipe)
		वापस;

	अगर (WARN_ON(!new_state->hwpipe_to_plane[hwpipe->idx]))
		वापस;

	DBG("%s: release from plane %s", hwpipe->name,
		new_state->hwpipe_to_plane[hwpipe->idx]->name);

	अगर (mdp5_kms->smp) अणु
		DBG("%s: free SMP blocks", hwpipe->name);
		mdp5_smp_release(mdp5_kms->smp, &state->smp, hwpipe->pipe);
	पूर्ण

	new_state->hwpipe_to_plane[hwpipe->idx] = शून्य;
पूर्ण

व्योम mdp5_pipe_destroy(काष्ठा mdp5_hw_pipe *hwpipe)
अणु
	kमुक्त(hwpipe);
पूर्ण

काष्ठा mdp5_hw_pipe *mdp5_pipe_init(क्रमागत mdp5_pipe pipe,
		uपूर्णांक32_t reg_offset, uपूर्णांक32_t caps)
अणु
	काष्ठा mdp5_hw_pipe *hwpipe;

	hwpipe = kzalloc(माप(*hwpipe), GFP_KERNEL);
	अगर (!hwpipe)
		वापस ERR_PTR(-ENOMEM);

	hwpipe->name = pipe2name(pipe);
	hwpipe->pipe = pipe;
	hwpipe->reg_offset = reg_offset;
	hwpipe->caps = caps;
	hwpipe->flush_mask = mdp_ctl_flush_mask_pipe(pipe);

	वापस hwpipe;
पूर्ण
