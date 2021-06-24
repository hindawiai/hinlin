<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/prctl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/poपूर्णांकer_auth.h>

पूर्णांक ptrauth_prctl_reset_keys(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ptrauth_keys_user *keys = &tsk->thपढ़ो.keys_user;
	अचिन्हित दीर्घ addr_key_mask = PR_PAC_APIAKEY | PR_PAC_APIBKEY |
				      PR_PAC_APDAKEY | PR_PAC_APDBKEY;
	अचिन्हित दीर्घ key_mask = addr_key_mask | PR_PAC_APGAKEY;

	अगर (!प्रणाली_supports_address_auth() && !प्रणाली_supports_generic_auth())
		वापस -EINVAL;

	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(tsk)))
		वापस -EINVAL;

	अगर (!arg) अणु
		ptrauth_keys_init_user(keys);
		वापस 0;
	पूर्ण

	अगर (arg & ~key_mask)
		वापस -EINVAL;

	अगर (((arg & addr_key_mask) && !प्रणाली_supports_address_auth()) ||
	    ((arg & PR_PAC_APGAKEY) && !प्रणाली_supports_generic_auth()))
		वापस -EINVAL;

	अगर (arg & PR_PAC_APIAKEY)
		get_अक्रमom_bytes(&keys->apia, माप(keys->apia));
	अगर (arg & PR_PAC_APIBKEY)
		get_अक्रमom_bytes(&keys->apib, माप(keys->apib));
	अगर (arg & PR_PAC_APDAKEY)
		get_अक्रमom_bytes(&keys->apda, माप(keys->apda));
	अगर (arg & PR_PAC_APDBKEY)
		get_अक्रमom_bytes(&keys->apdb, माप(keys->apdb));
	अगर (arg & PR_PAC_APGAKEY)
		get_अक्रमom_bytes(&keys->apga, माप(keys->apga));
	ptrauth_keys_install_user(keys);

	वापस 0;
पूर्ण

अटल u64 arg_to_enxx_mask(अचिन्हित दीर्घ arg)
अणु
	u64 sctlr_enxx_mask = 0;

	WARN_ON(arg & ~PR_PAC_ENABLED_KEYS_MASK);
	अगर (arg & PR_PAC_APIAKEY)
		sctlr_enxx_mask |= SCTLR_ELx_ENIA;
	अगर (arg & PR_PAC_APIBKEY)
		sctlr_enxx_mask |= SCTLR_ELx_ENIB;
	अगर (arg & PR_PAC_APDAKEY)
		sctlr_enxx_mask |= SCTLR_ELx_ENDA;
	अगर (arg & PR_PAC_APDBKEY)
		sctlr_enxx_mask |= SCTLR_ELx_ENDB;
	वापस sctlr_enxx_mask;
पूर्ण

पूर्णांक ptrauth_set_enabled_keys(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ keys,
			     अचिन्हित दीर्घ enabled)
अणु
	u64 sctlr = tsk->thपढ़ो.sctlr_user;

	अगर (!प्रणाली_supports_address_auth())
		वापस -EINVAL;

	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(tsk)))
		वापस -EINVAL;

	अगर ((keys & ~PR_PAC_ENABLED_KEYS_MASK) || (enabled & ~keys))
		वापस -EINVAL;

	sctlr &= ~arg_to_enxx_mask(keys);
	sctlr |= arg_to_enxx_mask(enabled);
	अगर (tsk == current)
		set_task_sctlr_el1(sctlr);
	अन्यथा
		tsk->thपढ़ो.sctlr_user = sctlr;

	वापस 0;
पूर्ण

पूर्णांक ptrauth_get_enabled_keys(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक retval = 0;

	अगर (!प्रणाली_supports_address_auth())
		वापस -EINVAL;

	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(tsk)))
		वापस -EINVAL;

	अगर (tsk->thपढ़ो.sctlr_user & SCTLR_ELx_ENIA)
		retval |= PR_PAC_APIAKEY;
	अगर (tsk->thपढ़ो.sctlr_user & SCTLR_ELx_ENIB)
		retval |= PR_PAC_APIBKEY;
	अगर (tsk->thपढ़ो.sctlr_user & SCTLR_ELx_ENDA)
		retval |= PR_PAC_APDAKEY;
	अगर (tsk->thपढ़ो.sctlr_user & SCTLR_ELx_ENDB)
		retval |= PR_PAC_APDBKEY;

	वापस retval;
पूर्ण
