<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_POINTER_AUTH_H
#घोषणा __ASM_POINTER_AUTH_H

#समावेश <linux/bitops.h>
#समावेश <linux/prctl.h>
#समावेश <linux/अक्रमom.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/sysreg.h>

#अगर_घोषित CONFIG_ARM64_PTR_AUTH
/*
 * Each key is a 128-bit quantity which is split across a pair of 64-bit
 * रेजिस्टरs (Lo and Hi).
 */
काष्ठा ptrauth_key अणु
	अचिन्हित दीर्घ lo, hi;
पूर्ण;

/*
 * We give each process its own keys, which are shared by all thपढ़ोs. The keys
 * are inherited upon विभाजन(), and reinitialised upon exec*().
 */
काष्ठा ptrauth_keys_user अणु
	काष्ठा ptrauth_key apia;
	काष्ठा ptrauth_key apib;
	काष्ठा ptrauth_key apda;
	काष्ठा ptrauth_key apdb;
	काष्ठा ptrauth_key apga;
पूर्ण;

काष्ठा ptrauth_keys_kernel अणु
	काष्ठा ptrauth_key apia;
पूर्ण;

#घोषणा __ptrauth_key_install_nosync(k, v)			\
करो अणु								\
	काष्ठा ptrauth_key __pki_v = (v);			\
	ग_लिखो_sysreg_s(__pki_v.lo, SYS_ ## k ## KEYLO_EL1);	\
	ग_लिखो_sysreg_s(__pki_v.hi, SYS_ ## k ## KEYHI_EL1);	\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम ptrauth_keys_install_user(काष्ठा ptrauth_keys_user *keys)
अणु
	अगर (प्रणाली_supports_address_auth()) अणु
		__ptrauth_key_install_nosync(APIB, keys->apib);
		__ptrauth_key_install_nosync(APDA, keys->apda);
		__ptrauth_key_install_nosync(APDB, keys->apdb);
	पूर्ण

	अगर (प्रणाली_supports_generic_auth())
		__ptrauth_key_install_nosync(APGA, keys->apga);
पूर्ण

अटल अंतरभूत व्योम ptrauth_keys_init_user(काष्ठा ptrauth_keys_user *keys)
अणु
	अगर (प्रणाली_supports_address_auth()) अणु
		get_अक्रमom_bytes(&keys->apia, माप(keys->apia));
		get_अक्रमom_bytes(&keys->apib, माप(keys->apib));
		get_अक्रमom_bytes(&keys->apda, माप(keys->apda));
		get_अक्रमom_bytes(&keys->apdb, माप(keys->apdb));
	पूर्ण

	अगर (प्रणाली_supports_generic_auth())
		get_अक्रमom_bytes(&keys->apga, माप(keys->apga));

	ptrauth_keys_install_user(keys);
पूर्ण

अटल __always_अंतरभूत व्योम ptrauth_keys_init_kernel(काष्ठा ptrauth_keys_kernel *keys)
अणु
	अगर (प्रणाली_supports_address_auth())
		get_अक्रमom_bytes(&keys->apia, माप(keys->apia));
पूर्ण

अटल __always_अंतरभूत व्योम ptrauth_keys_चयन_kernel(काष्ठा ptrauth_keys_kernel *keys)
अणु
	अगर (!प्रणाली_supports_address_auth())
		वापस;

	__ptrauth_key_install_nosync(APIA, keys->apia);
	isb();
पूर्ण

बाह्य पूर्णांक ptrauth_prctl_reset_keys(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ arg);

बाह्य पूर्णांक ptrauth_set_enabled_keys(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ keys,
				    अचिन्हित दीर्घ enabled);
बाह्य पूर्णांक ptrauth_get_enabled_keys(काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत अचिन्हित दीर्घ ptrauth_strip_insn_pac(अचिन्हित दीर्घ ptr)
अणु
	वापस ptrauth_clear_pac(ptr);
पूर्ण

अटल __always_अंतरभूत व्योम ptrauth_enable(व्योम)
अणु
	अगर (!प्रणाली_supports_address_auth())
		वापस;
	sysreg_clear_set(sctlr_el1, 0, (SCTLR_ELx_ENIA | SCTLR_ELx_ENIB |
					SCTLR_ELx_ENDA | SCTLR_ELx_ENDB));
	isb();
पूर्ण

#घोषणा ptrauth_suspend_निकास()                                                 \
	ptrauth_keys_install_user(&current->thपढ़ो.keys_user)

#घोषणा ptrauth_thपढ़ो_init_user()                                             \
	करो अणु                                                                   \
		ptrauth_keys_init_user(&current->thपढ़ो.keys_user);            \
									       \
		/* enable all keys */                                          \
		अगर (प्रणाली_supports_address_auth())                            \
			set_task_sctlr_el1(current->thपढ़ो.sctlr_user |        \
					   SCTLR_ELx_ENIA | SCTLR_ELx_ENIB |   \
					   SCTLR_ELx_ENDA | SCTLR_ELx_ENDB);   \
	पूर्ण जबतक (0)

#घोषणा ptrauth_thपढ़ो_चयन_user(tsk)                                        \
	ptrauth_keys_install_user(&(tsk)->thपढ़ो.keys_user)

#घोषणा ptrauth_thपढ़ो_init_kernel(tsk)					\
	ptrauth_keys_init_kernel(&(tsk)->thपढ़ो.keys_kernel)
#घोषणा ptrauth_thपढ़ो_चयन_kernel(tsk)				\
	ptrauth_keys_चयन_kernel(&(tsk)->thपढ़ो.keys_kernel)

#अन्यथा /* CONFIG_ARM64_PTR_AUTH */
#घोषणा ptrauth_enable()
#घोषणा ptrauth_prctl_reset_keys(tsk, arg)	(-EINVAL)
#घोषणा ptrauth_set_enabled_keys(tsk, keys, enabled)	(-EINVAL)
#घोषणा ptrauth_get_enabled_keys(tsk)	(-EINVAL)
#घोषणा ptrauth_strip_insn_pac(lr)	(lr)
#घोषणा ptrauth_suspend_निकास()
#घोषणा ptrauth_thपढ़ो_init_user()
#घोषणा ptrauth_thपढ़ो_init_kernel(tsk)
#घोषणा ptrauth_thपढ़ो_चयन_user(tsk)
#घोषणा ptrauth_thपढ़ो_चयन_kernel(tsk)
#पूर्ण_अगर /* CONFIG_ARM64_PTR_AUTH */

#घोषणा PR_PAC_ENABLED_KEYS_MASK                                               \
	(PR_PAC_APIAKEY | PR_PAC_APIBKEY | PR_PAC_APDAKEY | PR_PAC_APDBKEY)

#पूर्ण_अगर /* __ASM_POINTER_AUTH_H */
