<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_VDSO_VSYSCALL_H
#घोषणा __ASM_VDSO_VSYSCALL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <vdso/datapage.h>

#घोषणा VDSO_PRECISION_MASK	~(0xFF00ULL<<48)

बाह्य काष्ठा vdso_data *vdso_data;

/*
 * Update the vDSO data page to keep in sync with kernel समयkeeping.
 */
अटल __always_अंतरभूत
काष्ठा vdso_data *__arm64_get_k_vdso_data(व्योम)
अणु
	वापस vdso_data;
पूर्ण
#घोषणा __arch_get_k_vdso_data __arm64_get_k_vdso_data

अटल __always_अंतरभूत
व्योम __arm64_update_vsyscall(काष्ठा vdso_data *vdata, काष्ठा समयkeeper *tk)
अणु
	vdata[CS_HRES_COARSE].mask	= VDSO_PRECISION_MASK;
	vdata[CS_RAW].mask		= VDSO_PRECISION_MASK;
पूर्ण
#घोषणा __arch_update_vsyscall __arm64_update_vsyscall

/* The यंत्र-generic header needs to be included after the definitions above */
#समावेश <यंत्र-generic/vdso/vsyscall.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_VSYSCALL_H */
