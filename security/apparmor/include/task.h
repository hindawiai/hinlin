<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor task related definitions and mediation
 *
 * Copyright 2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_TASK_H
#घोषणा __AA_TASK_H

अटल अंतरभूत काष्ठा aa_task_ctx *task_ctx(काष्ठा task_काष्ठा *task)
अणु
	वापस task->security + apparmor_blob_sizes.lbs_task;
पूर्ण

/*
 * काष्ठा aa_task_ctx - inक्रमmation क्रम current task label change
 * @nnp: snapshot of label at समय of no_new_privs
 * @onexec: profile to transition to on next exec  (MAY BE शून्य)
 * @previous: profile the task may वापस to     (MAY BE शून्य)
 * @token: magic value the task must know क्रम वापसing to @previous_profile
 */
काष्ठा aa_task_ctx अणु
	काष्ठा aa_label *nnp;
	काष्ठा aa_label *onexec;
	काष्ठा aa_label *previous;
	u64 token;
पूर्ण;

पूर्णांक aa_replace_current_label(काष्ठा aa_label *label);
पूर्णांक aa_set_current_onexec(काष्ठा aa_label *label, bool stack);
पूर्णांक aa_set_current_hat(काष्ठा aa_label *label, u64 token);
पूर्णांक aa_restore_previous_label(u64 cookie);
काष्ठा aa_label *aa_get_task_label(काष्ठा task_काष्ठा *task);

/**
 * aa_मुक्त_task_ctx - मुक्त a task_ctx
 * @ctx: task_ctx to मुक्त (MAYBE शून्य)
 */
अटल अंतरभूत व्योम aa_मुक्त_task_ctx(काष्ठा aa_task_ctx *ctx)
अणु
	अगर (ctx) अणु
		aa_put_label(ctx->nnp);
		aa_put_label(ctx->previous);
		aa_put_label(ctx->onexec);
	पूर्ण
पूर्ण

/**
 * aa_dup_task_ctx - duplicate a task context, incrementing reference counts
 * @new: a blank task context      (NOT शून्य)
 * @old: the task context to copy  (NOT शून्य)
 */
अटल अंतरभूत व्योम aa_dup_task_ctx(काष्ठा aa_task_ctx *new,
				   स्थिर काष्ठा aa_task_ctx *old)
अणु
	*new = *old;
	aa_get_label(new->nnp);
	aa_get_label(new->previous);
	aa_get_label(new->onexec);
पूर्ण

/**
 * aa_clear_task_ctx_trans - clear transition tracking info from the ctx
 * @ctx: task context to clear (NOT शून्य)
 */
अटल अंतरभूत व्योम aa_clear_task_ctx_trans(काष्ठा aa_task_ctx *ctx)
अणु
	AA_BUG(!ctx);

	aa_put_label(ctx->previous);
	aa_put_label(ctx->onexec);
	ctx->previous = शून्य;
	ctx->onexec = शून्य;
	ctx->token = 0;
पूर्ण

#पूर्ण_अगर /* __AA_TASK_H */
