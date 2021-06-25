<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DRM_RANDOM_H__
#घोषणा __DRM_RANDOM_H__

/* This is a temporary home क्रम a couple of utility functions that should
 * be transposed to lib/ at the earliest convenience.
 */

#समावेश <linux/अक्रमom.h>

#घोषणा DRM_RND_STATE_INITIALIZER(seed__) (अणु				\
	काष्ठा rnd_state state__;					\
	pअक्रमom_seed_state(&state__, (seed__));				\
	state__;							\
पूर्ण)

#घोषणा DRM_RND_STATE(name__, seed__) \
	काष्ठा rnd_state name__ = DRM_RND_STATE_INITIALIZER(seed__)

अचिन्हित पूर्णांक *drm_अक्रमom_order(अचिन्हित पूर्णांक count,
			       काष्ठा rnd_state *state);
व्योम drm_अक्रमom_reorder(अचिन्हित पूर्णांक *order,
			अचिन्हित पूर्णांक count,
			काष्ठा rnd_state *state);

#पूर्ण_अगर /* !__DRM_RANDOM_H__ */
