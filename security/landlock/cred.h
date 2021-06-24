<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Landlock LSM - Credential hooks
 *
 * Copyright तऊ 2019-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2019-2020 ANSSI
 */

#अगर_अघोषित _SECURITY_LANDLOCK_CRED_H
#घोषणा _SECURITY_LANDLOCK_CRED_H

#समावेश <linux/cred.h>
#समावेश <linux/init.h>
#समावेश <linux/rcupdate.h>

#समावेश "ruleset.h"
#समावेश "setup.h"

काष्ठा landlock_cred_security अणु
	काष्ठा landlock_ruleset *करोमुख्य;
पूर्ण;

अटल अंतरभूत काष्ठा landlock_cred_security *landlock_cred(
		स्थिर काष्ठा cred *cred)
अणु
	वापस cred->security + landlock_blob_sizes.lbs_cred;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा landlock_ruleset *landlock_get_current_करोमुख्य(व्योम)
अणु
	वापस landlock_cred(current_cred())->करोमुख्य;
पूर्ण

/*
 * The call needs to come from an RCU पढ़ो-side critical section.
 */
अटल अंतरभूत स्थिर काष्ठा landlock_ruleset *landlock_get_task_करोमुख्य(
		स्थिर काष्ठा task_काष्ठा *स्थिर task)
अणु
	वापस landlock_cred(__task_cred(task))->करोमुख्य;
पूर्ण

अटल अंतरभूत bool landlocked(स्थिर काष्ठा task_काष्ठा *स्थिर task)
अणु
	bool has_करोm;

	अगर (task == current)
		वापस !!landlock_get_current_करोमुख्य();

	rcu_पढ़ो_lock();
	has_करोm = !!landlock_get_task_करोमुख्य(task);
	rcu_पढ़ो_unlock();
	वापस has_करोm;
पूर्ण

__init व्योम landlock_add_cred_hooks(व्योम);

#पूर्ण_अगर /* _SECURITY_LANDLOCK_CRED_H */
