<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mmap based event notअगरications क्रम SELinux
 *
 * Author: KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * Copyright (C) 2010 NEC corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश "avc.h"
#समावेश "security.h"

/*
 * The selinux_status_page shall be exposed to userspace applications
 * using mmap पूर्णांकerface on /selinux/status.
 * It enables to notअगरy applications a few events that will cause reset
 * of userspace access vector without context चयनing.
 *
 * The selinux_kernel_status काष्ठाure on the head of status page is
 * रक्षित from concurrent accesses using seqlock logic, so userspace
 * application should reference the status page according to the seqlock
 * logic.
 *
 * Typically, application checks status->sequence at the head of access
 * control routine. If it is odd-number, kernel is updating the status,
 * so please रुको क्रम a moment. If it is changed from the last sequence
 * number, it means something happen, so application will reset userspace
 * avc, अगर needed.
 * In most हालs, application shall confirm the kernel status is not
 * changed without any प्रणाली call invocations.
 */

/*
 * selinux_kernel_status_page
 *
 * It वापसs a reference to selinux_status_page. If the status page is
 * not allocated yet, it also tries to allocate it at the first समय.
 */
काष्ठा page *selinux_kernel_status_page(काष्ठा selinux_state *state)
अणु
	काष्ठा selinux_kernel_status   *status;
	काष्ठा page		       *result = शून्य;

	mutex_lock(&state->status_lock);
	अगर (!state->status_page) अणु
		state->status_page = alloc_page(GFP_KERNEL|__GFP_ZERO);

		अगर (state->status_page) अणु
			status = page_address(state->status_page);

			status->version = SELINUX_KERNEL_STATUS_VERSION;
			status->sequence = 0;
			status->enक्रमcing = enक्रमcing_enabled(state);
			/*
			 * NOTE: the next policyload event shall set
			 * a positive value on the status->policyload,
			 * although it may not be 1, but never zero.
			 * So, application can know it was updated.
			 */
			status->policyload = 0;
			status->deny_unknown =
				!security_get_allow_unknown(state);
		पूर्ण
	पूर्ण
	result = state->status_page;
	mutex_unlock(&state->status_lock);

	वापस result;
पूर्ण

/*
 * selinux_status_update_setenक्रमce
 *
 * It updates status of the current enक्रमcing/permissive mode.
 */
व्योम selinux_status_update_setenक्रमce(काष्ठा selinux_state *state,
				      पूर्णांक enक्रमcing)
अणु
	काष्ठा selinux_kernel_status   *status;

	mutex_lock(&state->status_lock);
	अगर (state->status_page) अणु
		status = page_address(state->status_page);

		status->sequence++;
		smp_wmb();

		status->enक्रमcing = enक्रमcing;

		smp_wmb();
		status->sequence++;
	पूर्ण
	mutex_unlock(&state->status_lock);
पूर्ण

/*
 * selinux_status_update_policyload
 *
 * It updates status of the बार of policy reloaded, and current
 * setting of deny_unknown.
 */
व्योम selinux_status_update_policyload(काष्ठा selinux_state *state,
				      पूर्णांक seqno)
अणु
	काष्ठा selinux_kernel_status   *status;

	mutex_lock(&state->status_lock);
	अगर (state->status_page) अणु
		status = page_address(state->status_page);

		status->sequence++;
		smp_wmb();

		status->policyload = seqno;
		status->deny_unknown = !security_get_allow_unknown(state);

		smp_wmb();
		status->sequence++;
	पूर्ण
	mutex_unlock(&state->status_lock);
पूर्ण
