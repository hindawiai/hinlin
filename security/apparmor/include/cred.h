<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor contexts used to associate "labels" to objects.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __AA_CONTEXT_H
#घोषणा __AA_CONTEXT_H

#समावेश <linux/cred.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#समावेश "label.h"
#समावेश "policy_ns.h"
#समावेश "task.h"

अटल अंतरभूत काष्ठा aa_label *cred_label(स्थिर काष्ठा cred *cred)
अणु
	काष्ठा aa_label **blob = cred->security + apparmor_blob_sizes.lbs_cred;

	AA_BUG(!blob);
	वापस *blob;
पूर्ण

अटल अंतरभूत व्योम set_cred_label(स्थिर काष्ठा cred *cred,
				  काष्ठा aa_label *label)
अणु
	काष्ठा aa_label **blob = cred->security + apparmor_blob_sizes.lbs_cred;

	AA_BUG(!blob);
	*blob = label;
पूर्ण

/**
 * aa_cred_raw_label - obtain cred's label
 * @cred: cred to obtain label from  (NOT शून्य)
 *
 * Returns: confining label
 *
 * करोes NOT increment reference count
 */
अटल अंतरभूत काष्ठा aa_label *aa_cred_raw_label(स्थिर काष्ठा cred *cred)
अणु
	काष्ठा aa_label *label = cred_label(cred);

	AA_BUG(!label);
	वापस label;
पूर्ण

/**
 * aa_get_newest_cred_label - obtain the newest label on a cred
 * @cred: cred to obtain label from (NOT शून्य)
 *
 * Returns: newest version of confining label
 */
अटल अंतरभूत काष्ठा aa_label *aa_get_newest_cred_label(स्थिर काष्ठा cred *cred)
अणु
	वापस aa_get_newest_label(aa_cred_raw_label(cred));
पूर्ण

/**
 * __aa_task_raw_label - retrieve another task's label
 * @task: task to query  (NOT शून्य)
 *
 * Returns: @task's label without incrementing its ref count
 *
 * If @task != current needs to be called in RCU safe critical section
 */
अटल अंतरभूत काष्ठा aa_label *__aa_task_raw_label(काष्ठा task_काष्ठा *task)
अणु
	वापस aa_cred_raw_label(__task_cred(task));
पूर्ण

/**
 * aa_current_raw_label - find the current tasks confining label
 *
 * Returns: up to date confining label or the ns unconfined label (NOT शून्य)
 *
 * This fn will not update the tasks cred to the most up to date version
 * of the label so it is safe to call when inside of locks.
 */
अटल अंतरभूत काष्ठा aa_label *aa_current_raw_label(व्योम)
अणु
	वापस aa_cred_raw_label(current_cred());
पूर्ण

/**
 * aa_get_current_label - get the newest version of the current tasks label
 *
 * Returns: newest version of confining label (NOT शून्य)
 *
 * This fn will not update the tasks cred, so it is safe inside of locks
 *
 * The वापसed reference must be put with aa_put_label()
 */
अटल अंतरभूत काष्ठा aa_label *aa_get_current_label(व्योम)
अणु
	काष्ठा aa_label *l = aa_current_raw_label();

	अगर (label_is_stale(l))
		वापस aa_get_newest_label(l);
	वापस aa_get_label(l);
पूर्ण

#घोषणा __end_current_label_crit_section(X) end_current_label_crit_section(X)

/**
 * end_label_crit_section - put a reference found with begin_current_label..
 * @label: label reference to put
 *
 * Should only be used with a reference obtained with
 * begin_current_label_crit_section and never used in situations where the
 * task cred may be updated
 */
अटल अंतरभूत व्योम end_current_label_crit_section(काष्ठा aa_label *label)
अणु
	अगर (label != aa_current_raw_label())
		aa_put_label(label);
पूर्ण

/**
 * __begin_current_label_crit_section - current's confining label
 *
 * Returns: up to date confining label or the ns unconfined label (NOT शून्य)
 *
 * safe to call inside locks
 *
 * The वापसed reference must be put with __end_current_label_crit_section()
 * This must NOT be used अगर the task cred could be updated within the
 * critical section between __begin_current_label_crit_section() ..
 * __end_current_label_crit_section()
 */
अटल अंतरभूत काष्ठा aa_label *__begin_current_label_crit_section(व्योम)
अणु
	काष्ठा aa_label *label = aa_current_raw_label();

	अगर (label_is_stale(label))
		label = aa_get_newest_label(label);

	वापस label;
पूर्ण

/**
 * begin_current_label_crit_section - current's confining label and update it
 *
 * Returns: up to date confining label or the ns unconfined label (NOT शून्य)
 *
 * Not safe to call inside locks
 *
 * The वापसed reference must be put with end_current_label_crit_section()
 * This must NOT be used अगर the task cred could be updated within the
 * critical section between begin_current_label_crit_section() ..
 * end_current_label_crit_section()
 */
अटल अंतरभूत काष्ठा aa_label *begin_current_label_crit_section(व्योम)
अणु
	काष्ठा aa_label *label = aa_current_raw_label();

	might_sleep();

	अगर (label_is_stale(label)) अणु
		label = aa_get_newest_label(label);
		अगर (aa_replace_current_label(label) == 0)
			/* task cred will keep the reference */
			aa_put_label(label);
	पूर्ण

	वापस label;
पूर्ण

अटल अंतरभूत काष्ठा aa_ns *aa_get_current_ns(व्योम)
अणु
	काष्ठा aa_label *label;
	काष्ठा aa_ns *ns;

	label  = __begin_current_label_crit_section();
	ns = aa_get_ns(labels_ns(label));
	__end_current_label_crit_section(label);

	वापस ns;
पूर्ण

#पूर्ण_अगर /* __AA_CONTEXT_H */
