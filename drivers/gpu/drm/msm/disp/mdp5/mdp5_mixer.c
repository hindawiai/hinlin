<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 The Linux Foundation. All rights reserved.
 */

#समावेश "mdp5_kms.h"

/*
 * As of now, there are only 2 combinations possible क्रम source split:
 *
 * Left | Right
 * -----|------
 *  LM0 | LM1
 *  LM2 | LM5
 *
 */
अटल पूर्णांक lm_right_pair[] = अणु 1, -1, 5, -1, -1, -1 पूर्ण;

अटल पूर्णांक get_right_pair_idx(काष्ठा mdp5_kms *mdp5_kms, पूर्णांक lm)
अणु
	पूर्णांक i;
	पूर्णांक pair_lm;

	pair_lm = lm_right_pair[lm];
	अगर (pair_lm < 0)
		वापस -EINVAL;

	क्रम (i = 0; i < mdp5_kms->num_hwmixers; i++) अणु
		काष्ठा mdp5_hw_mixer *mixer = mdp5_kms->hwmixers[i];

		अगर (mixer->lm == pair_lm)
			वापस mixer->idx;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक mdp5_mixer_assign(काष्ठा drm_atomic_state *s, काष्ठा drm_crtc *crtc,
		      uपूर्णांक32_t caps, काष्ठा mdp5_hw_mixer **mixer,
		      काष्ठा mdp5_hw_mixer **r_mixer)
अणु
	काष्ठा msm_drm_निजी *priv = s->dev->dev_निजी;
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(priv->kms));
	काष्ठा mdp5_global_state *global_state = mdp5_get_global_state(s);
	काष्ठा mdp5_hw_mixer_state *new_state;
	पूर्णांक i;

	अगर (IS_ERR(global_state))
		वापस PTR_ERR(global_state);

	new_state = &global_state->hwmixer;

	क्रम (i = 0; i < mdp5_kms->num_hwmixers; i++) अणु
		काष्ठा mdp5_hw_mixer *cur = mdp5_kms->hwmixers[i];

		/*
		 * skip अगर alपढ़ोy in-use by a dअगरferent CRTC. If there is a
		 * mixer alपढ़ोy asचिन्हित to this CRTC, it means this call is
		 * a request to get an additional right mixer. Assume that the
		 * existing mixer is the 'left' one, and try to see अगर we can
		 * get its corresponding 'right' pair.
		 */
		अगर (new_state->hwmixer_to_crtc[cur->idx] &&
		    new_state->hwmixer_to_crtc[cur->idx] != crtc)
			जारी;

		/* skip अगर करोesn't support some required caps: */
		अगर (caps & ~cur->caps)
			जारी;

		अगर (r_mixer) अणु
			पूर्णांक pair_idx;

			pair_idx = get_right_pair_idx(mdp5_kms, cur->lm);
			अगर (pair_idx < 0)
				वापस -EINVAL;

			अगर (new_state->hwmixer_to_crtc[pair_idx])
				जारी;

			*r_mixer = mdp5_kms->hwmixers[pair_idx];
		पूर्ण

		/*
		 * prefer a pair-able LM over an unpairable one. We can
		 * चयन the CRTC from Normal mode to Source Split mode
		 * without requiring a full modeset अगर we had alपढ़ोy
		 * asचिन्हित this CRTC a pair-able LM.
		 *
		 * TODO: There will be assignment sequences which would
		 * result in the CRTC requiring a full modeset, even
		 * अगर we have the LM resources to prevent it. For a platक्रमm
		 * with a few displays, we करोn't run out of pair-able LMs
		 * so easily. For now, ignore the possibility of requiring
		 * a full modeset.
		 */
		अगर (!(*mixer) || cur->caps & MDP_LM_CAP_PAIR)
			*mixer = cur;
	पूर्ण

	अगर (!(*mixer))
		वापस -ENOMEM;

	अगर (r_mixer && !(*r_mixer))
		वापस -ENOMEM;

	DBG("assigning Layer Mixer %d to crtc %s", (*mixer)->lm, crtc->name);

	new_state->hwmixer_to_crtc[(*mixer)->idx] = crtc;
	अगर (r_mixer) अणु
		DBG("assigning Right Layer Mixer %d to crtc %s", (*r_mixer)->lm,
		    crtc->name);
		new_state->hwmixer_to_crtc[(*r_mixer)->idx] = crtc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mdp5_mixer_release(काष्ठा drm_atomic_state *s, काष्ठा mdp5_hw_mixer *mixer)
अणु
	काष्ठा mdp5_global_state *global_state = mdp5_get_global_state(s);
	काष्ठा mdp5_hw_mixer_state *new_state = &global_state->hwmixer;

	अगर (!mixer)
		वापस;

	अगर (WARN_ON(!new_state->hwmixer_to_crtc[mixer->idx]))
		वापस;

	DBG("%s: release from crtc %s", mixer->name,
	    new_state->hwmixer_to_crtc[mixer->idx]->name);

	new_state->hwmixer_to_crtc[mixer->idx] = शून्य;
पूर्ण

व्योम mdp5_mixer_destroy(काष्ठा mdp5_hw_mixer *mixer)
अणु
	kमुक्त(mixer);
पूर्ण

अटल स्थिर अक्षर * स्थिर mixer_names[] = अणु
	"LM0", "LM1", "LM2", "LM3", "LM4", "LM5",
पूर्ण;

काष्ठा mdp5_hw_mixer *mdp5_mixer_init(स्थिर काष्ठा mdp5_lm_instance *lm)
अणु
	काष्ठा mdp5_hw_mixer *mixer;

	mixer = kzalloc(माप(*mixer), GFP_KERNEL);
	अगर (!mixer)
		वापस ERR_PTR(-ENOMEM);

	mixer->name = mixer_names[lm->id];
	mixer->lm = lm->id;
	mixer->caps = lm->caps;
	mixer->pp = lm->pp;
	mixer->dspp = lm->dspp;
	mixer->flush_mask = mdp_ctl_flush_mask_lm(lm->id);

	वापस mixer;
पूर्ण
