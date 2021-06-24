<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor task related definitions and mediation
 *
 * Copyright 2017 Canonical Ltd.
 *
 * TODO
 * If a task uses change_hat it currently करोes not वापस to the old
 * cred or task context but instead creates a new one.  Ideally the task
 * should वापस to the previous cred अगर it has not been modअगरied.
 */

#समावेश "include/cred.h"
#समावेश "include/task.h"

/**
 * aa_get_task_label - Get another task's label
 * @task: task to query  (NOT शून्य)
 *
 * Returns: counted reference to @task's label
 */
काष्ठा aa_label *aa_get_task_label(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा aa_label *p;

	rcu_पढ़ो_lock();
	p = aa_get_newest_label(__aa_task_raw_label(task));
	rcu_पढ़ो_unlock();

	वापस p;
पूर्ण

/**
 * aa_replace_current_label - replace the current tasks label
 * @label: new label  (NOT शून्य)
 *
 * Returns: 0 or error on failure
 */
पूर्णांक aa_replace_current_label(काष्ठा aa_label *label)
अणु
	काष्ठा aa_label *old = aa_current_raw_label();
	काष्ठा aa_task_ctx *ctx = task_ctx(current);
	काष्ठा cred *new;

	AA_BUG(!label);

	अगर (old == label)
		वापस 0;

	अगर (current_cred() != current_real_cred())
		वापस -EBUSY;

	new  = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	अगर (ctx->nnp && label_is_stale(ctx->nnp)) अणु
		काष्ठा aa_label *पंचांगp = ctx->nnp;

		ctx->nnp = aa_get_newest_label(पंचांगp);
		aa_put_label(पंचांगp);
	पूर्ण
	अगर (unconfined(label) || (labels_ns(old) != labels_ns(label)))
		/*
		 * अगर चयनing to unconfined or a dअगरferent label namespace
		 * clear out context state
		 */
		aa_clear_task_ctx_trans(task_ctx(current));

	/*
	 * be careful चयनing cred label, when racing replacement it
	 * is possible that the cred labels's->proxy->label is the reference
	 * keeping @label valid, so make sure to get its reference beक्रमe
	 * dropping the reference on the cred's label
	 */
	aa_get_label(label);
	aa_put_label(cred_label(new));
	set_cred_label(new, label);

	commit_creds(new);
	वापस 0;
पूर्ण


/**
 * aa_set_current_onexec - set the tasks change_profile to happen onexec
 * @label: प्रणाली label to set at exec  (MAYBE शून्य to clear value)
 * @stack: whether stacking should be करोne
 * Returns: 0 or error on failure
 */
पूर्णांक aa_set_current_onexec(काष्ठा aa_label *label, bool stack)
अणु
	काष्ठा aa_task_ctx *ctx = task_ctx(current);

	aa_get_label(label);
	aa_put_label(ctx->onexec);
	ctx->onexec = label;
	ctx->token = stack;

	वापस 0;
पूर्ण

/**
 * aa_set_current_hat - set the current tasks hat
 * @label: label to set as the current hat  (NOT शून्य)
 * @token: token value that must be specअगरied to change from the hat
 *
 * Do चयन of tasks hat.  If the task is currently in a hat
 * validate the token to match.
 *
 * Returns: 0 or error on failure
 */
पूर्णांक aa_set_current_hat(काष्ठा aa_label *label, u64 token)
अणु
	काष्ठा aa_task_ctx *ctx = task_ctx(current);
	काष्ठा cred *new;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	AA_BUG(!label);

	अगर (!ctx->previous) अणु
		/* transfer refcount */
		ctx->previous = cred_label(new);
		ctx->token = token;
	पूर्ण अन्यथा अगर (ctx->token == token) अणु
		aa_put_label(cred_label(new));
	पूर्ण अन्यथा अणु
		/* previous_profile && ctx->token != token */
		पात_creds(new);
		वापस -EACCES;
	पूर्ण

	set_cred_label(new, aa_get_newest_label(label));
	/* clear exec on चयनing context */
	aa_put_label(ctx->onexec);
	ctx->onexec = शून्य;

	commit_creds(new);
	वापस 0;
पूर्ण

/**
 * aa_restore_previous_label - निकास from hat context restoring previous label
 * @token: the token that must be matched to निकास hat context
 *
 * Attempt to वापस out of a hat to the previous label.  The token
 * must match the stored token value.
 *
 * Returns: 0 or error of failure
 */
पूर्णांक aa_restore_previous_label(u64 token)
अणु
	काष्ठा aa_task_ctx *ctx = task_ctx(current);
	काष्ठा cred *new;

	अगर (ctx->token != token)
		वापस -EACCES;
	/* ignore restores when there is no saved label */
	अगर (!ctx->previous)
		वापस 0;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	aa_put_label(cred_label(new));
	set_cred_label(new, aa_get_newest_label(ctx->previous));
	AA_BUG(!cred_label(new));
	/* clear exec && prev inक्रमmation when restoring to previous context */
	aa_clear_task_ctx_trans(ctx);

	commit_creds(new);

	वापस 0;
पूर्ण
