<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Landlock LSM - Credential hooks
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#समावेश <linux/cred.h>
#समावेश <linux/lsm_hooks.h>

#समावेश "common.h"
#समावेश "cred.h"
#समावेश "ruleset.h"
#समावेश "setup.h"

अटल पूर्णांक hook_cred_prepare(काष्ठा cred *स्थिर new,
		स्थिर काष्ठा cred *स्थिर old, स्थिर gfp_t gfp)
अणु
	काष्ठा landlock_ruleset *स्थिर old_करोm = landlock_cred(old)->करोमुख्य;

	अगर (old_करोm) अणु
		landlock_get_ruleset(old_करोm);
		landlock_cred(new)->करोमुख्य = old_करोm;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hook_cred_मुक्त(काष्ठा cred *स्थिर cred)
अणु
	काष्ठा landlock_ruleset *स्थिर करोm = landlock_cred(cred)->करोमुख्य;

	अगर (करोm)
		landlock_put_ruleset_deferred(करोm);
पूर्ण

अटल काष्ठा security_hook_list landlock_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(cred_prepare, hook_cred_prepare),
	LSM_HOOK_INIT(cred_मुक्त, hook_cred_मुक्त),
पूर्ण;

__init व्योम landlock_add_cred_hooks(व्योम)
अणु
	security_add_hooks(landlock_hooks, ARRAY_SIZE(landlock_hooks),
			LANDLOCK_NAME);
पूर्ण
