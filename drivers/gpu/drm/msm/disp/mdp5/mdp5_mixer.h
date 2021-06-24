<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __MDP5_LM_H__
#घोषणा __MDP5_LM_H__

/* represents a hw Layer Mixer, one (or more) is dynamically asचिन्हित to a crtc */
काष्ठा mdp5_hw_mixer अणु
	पूर्णांक idx;

	स्थिर अक्षर *name;

	पूर्णांक lm;			/* the LM instance # */
	uपूर्णांक32_t caps;
	पूर्णांक pp;
	पूर्णांक dspp;

	uपूर्णांक32_t flush_mask;      /* used to commit LM रेजिस्टरs */
पूर्ण;

/* global atomic state of assignment between CRTCs and Layer Mixers: */
काष्ठा mdp5_hw_mixer_state अणु
	काष्ठा drm_crtc *hwmixer_to_crtc[8];
पूर्ण;

काष्ठा mdp5_hw_mixer *mdp5_mixer_init(स्थिर काष्ठा mdp5_lm_instance *lm);
व्योम mdp5_mixer_destroy(काष्ठा mdp5_hw_mixer *lm);
पूर्णांक mdp5_mixer_assign(काष्ठा drm_atomic_state *s, काष्ठा drm_crtc *crtc,
		      uपूर्णांक32_t caps, काष्ठा mdp5_hw_mixer **mixer,
		      काष्ठा mdp5_hw_mixer **r_mixer);
व्योम mdp5_mixer_release(काष्ठा drm_atomic_state *s,
			काष्ठा mdp5_hw_mixer *mixer);

#पूर्ण_अगर /* __MDP5_LM_H__ */
