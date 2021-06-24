<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2021 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@linux.microsoft.com)
 *
 * Measure critical data काष्ठाures मुख्यtaपूर्णांकed by SELinux
 * using IMA subप्रणाली.
 */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ima.h>
#समावेश "security.h"
#समावेश "ima.h"

/*
 * selinux_ima_collect_state - Read selinux configuration settings
 *
 * @state: selinux_state
 *
 * On success वापसs the configuration settings string.
 * On error, वापसs शून्य.
 */
अटल अक्षर *selinux_ima_collect_state(काष्ठा selinux_state *state)
अणु
	स्थिर अक्षर *on = "=1;", *off = "=0;";
	अक्षर *buf;
	पूर्णांक buf_len, len, i, rc;

	buf_len = म_माप("initialized=0;enforcing=0;checkreqprot=0;") + 1;

	len = म_माप(on);
	क्रम (i = 0; i < __POLICYDB_CAPABILITY_MAX; i++)
		buf_len += म_माप(selinux_policycap_names[i]) + len;

	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	rc = strscpy(buf, "initialized", buf_len);
	WARN_ON(rc < 0);

	rc = strlcat(buf, selinux_initialized(state) ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, "enforcing", buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, enक्रमcing_enabled(state) ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, "checkreqprot", buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, checkreqprot_get(state) ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	क्रम (i = 0; i < __POLICYDB_CAPABILITY_MAX; i++) अणु
		rc = strlcat(buf, selinux_policycap_names[i], buf_len);
		WARN_ON(rc >= buf_len);

		rc = strlcat(buf, state->policycap[i] ? on : off, buf_len);
		WARN_ON(rc >= buf_len);
	पूर्ण

	वापस buf;
पूर्ण

/*
 * selinux_ima_measure_state_locked - Measure SELinux state and hash of policy
 *
 * @state: selinux state काष्ठा
 */
व्योम selinux_ima_measure_state_locked(काष्ठा selinux_state *state)
अणु
	अक्षर *state_str = शून्य;
	व्योम *policy = शून्य;
	माप_प्रकार policy_len;
	पूर्णांक rc = 0;

	WARN_ON(!mutex_is_locked(&state->policy_mutex));

	state_str = selinux_ima_collect_state(state);
	अगर (!state_str) अणु
		pr_err("SELinux: %s: failed to read state.\n", __func__);
		वापस;
	पूर्ण

	ima_measure_critical_data("selinux", "selinux-state",
				  state_str, म_माप(state_str), false);

	kमुक्त(state_str);

	/*
	 * Measure SELinux policy only after initialization is completed.
	 */
	अगर (!selinux_initialized(state))
		वापस;

	rc = security_पढ़ो_state_kernel(state, &policy, &policy_len);
	अगर (rc) अणु
		pr_err("SELinux: %s: failed to read policy %d.\n", __func__, rc);
		वापस;
	पूर्ण

	ima_measure_critical_data("selinux", "selinux-policy-hash",
				  policy, policy_len, true);

	vमुक्त(policy);
पूर्ण

/*
 * selinux_ima_measure_state - Measure SELinux state and hash of policy
 *
 * @state: selinux state काष्ठा
 */
व्योम selinux_ima_measure_state(काष्ठा selinux_state *state)
अणु
	WARN_ON(mutex_is_locked(&state->policy_mutex));

	mutex_lock(&state->policy_mutex);
	selinux_ima_measure_state_locked(state);
	mutex_unlock(&state->policy_mutex);
पूर्ण
