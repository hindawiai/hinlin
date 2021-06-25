<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * प्रणाली_state.c - State of the प्रणाली modअगरied by livepatches
 *
 * Copyright (C) 2019 SUSE
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/livepatch.h>
#समावेश "core.h"
#समावेश "state.h"
#समावेश "transition.h"

#घोषणा klp_क्रम_each_state(patch, state)		\
	क्रम (state = patch->states; state && state->id; state++)

/**
 * klp_get_state() - get inक्रमmation about प्रणाली state modअगरied by
 *	the given patch
 * @patch:	livepatch that modअगरies the given प्रणाली state
 * @id:		custom identअगरier of the modअगरied प्रणाली state
 *
 * Checks whether the given patch modअगरies the given प्रणाली state.
 *
 * The function can be called either from pre/post (un)patch
 * callbacks or from the kernel code added by the livepatch.
 *
 * Return: poपूर्णांकer to काष्ठा klp_state when found, otherwise शून्य.
 */
काष्ठा klp_state *klp_get_state(काष्ठा klp_patch *patch, अचिन्हित दीर्घ id)
अणु
	काष्ठा klp_state *state;

	klp_क्रम_each_state(patch, state) अणु
		अगर (state->id == id)
			वापस state;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(klp_get_state);

/**
 * klp_get_prev_state() - get inक्रमmation about प्रणाली state modअगरied by
 *	the alपढ़ोy installed livepatches
 * @id:		custom identअगरier of the modअगरied प्रणाली state
 *
 * Checks whether alपढ़ोy installed livepatches modअगरy the given
 * प्रणाली state.
 *
 * The same प्रणाली state can be modअगरied by more non-cumulative
 * livepatches. It is expected that the latest livepatch has
 * the most up-to-date inक्रमmation.
 *
 * The function can be called only during transition when a new
 * livepatch is being enabled or when such a transition is reverted.
 * It is typically called only from pre/post (un)patch
 * callbacks.
 *
 * Return: poपूर्णांकer to the latest काष्ठा klp_state from alपढ़ोy
 *	installed livepatches, शून्य when not found.
 */
काष्ठा klp_state *klp_get_prev_state(अचिन्हित दीर्घ id)
अणु
	काष्ठा klp_patch *patch;
	काष्ठा klp_state *state, *last_state = शून्य;

	अगर (WARN_ON_ONCE(!klp_transition_patch))
		वापस शून्य;

	klp_क्रम_each_patch(patch) अणु
		अगर (patch == klp_transition_patch)
			जाओ out;

		state = klp_get_state(patch, id);
		अगर (state)
			last_state = state;
	पूर्ण

out:
	वापस last_state;
पूर्ण
EXPORT_SYMBOL_GPL(klp_get_prev_state);

/* Check अगर the patch is able to deal with the existing प्रणाली state. */
अटल bool klp_is_state_compatible(काष्ठा klp_patch *patch,
				    काष्ठा klp_state *old_state)
अणु
	काष्ठा klp_state *state;

	state = klp_get_state(patch, old_state->id);

	/* A cumulative livepatch must handle all alपढ़ोy modअगरied states. */
	अगर (!state)
		वापस !patch->replace;

	वापस state->version >= old_state->version;
पूर्ण

/*
 * Check that the new livepatch will not अवरोध the existing प्रणाली states.
 * Cumulative patches must handle all alपढ़ोy modअगरied states.
 * Non-cumulative patches can touch alपढ़ोy modअगरied states.
 */
bool klp_is_patch_compatible(काष्ठा klp_patch *patch)
अणु
	काष्ठा klp_patch *old_patch;
	काष्ठा klp_state *old_state;

	klp_क्रम_each_patch(old_patch) अणु
		klp_क्रम_each_state(old_patch, old_state) अणु
			अगर (!klp_is_state_compatible(patch, old_state))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
