<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MDP5_PIPE_H__
#घोषणा __MDP5_PIPE_H__

/* TODO: Add SSPP_MAX in mdp5.xml.h */
#घोषणा SSPP_MAX	(SSPP_CURSOR1 + 1)

/* represents a hw pipe, which is dynamically asचिन्हित to a plane */
काष्ठा mdp5_hw_pipe अणु
	पूर्णांक idx;

	स्थिर अक्षर *name;
	क्रमागत mdp5_pipe pipe;

	uपूर्णांक32_t reg_offset;
	uपूर्णांक32_t caps;

	uपूर्णांक32_t flush_mask;      /* used to commit pipe रेजिस्टरs */

	/* number of smp blocks per plane, ie:
	 *   nblks_y | (nblks_u << 8) | (nblks_v << 16)
	 */
	uपूर्णांक32_t blkcfg;
पूर्ण;

/* global atomic state of assignment between pipes and planes: */
काष्ठा mdp5_hw_pipe_state अणु
	काष्ठा drm_plane *hwpipe_to_plane[SSPP_MAX];
पूर्ण;

पूर्णांक mdp5_pipe_assign(काष्ठा drm_atomic_state *s, काष्ठा drm_plane *plane,
		     uपूर्णांक32_t caps, uपूर्णांक32_t blkcfg,
		     काष्ठा mdp5_hw_pipe **hwpipe,
		     काष्ठा mdp5_hw_pipe **r_hwpipe);
व्योम mdp5_pipe_release(काष्ठा drm_atomic_state *s, काष्ठा mdp5_hw_pipe *hwpipe);

काष्ठा mdp5_hw_pipe *mdp5_pipe_init(क्रमागत mdp5_pipe pipe,
		uपूर्णांक32_t reg_offset, uपूर्णांक32_t caps);
व्योम mdp5_pipe_destroy(काष्ठा mdp5_hw_pipe *hwpipe);

#पूर्ण_अगर /* __MDP5_PIPE_H__ */
