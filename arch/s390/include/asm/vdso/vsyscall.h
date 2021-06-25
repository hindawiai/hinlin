<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_VDSO_VSYSCALL_H
#घोषणा __ASM_VDSO_VSYSCALL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/hrसमयr.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <vdso/datapage.h>
#समावेश <यंत्र/vdso.h>
/*
 * Update the vDSO data page to keep in sync with kernel समयkeeping.
 */

अटल __always_अंतरभूत काष्ठा vdso_data *__s390_get_k_vdso_data(व्योम)
अणु
	वापस vdso_data;
पूर्ण
#घोषणा __arch_get_k_vdso_data __s390_get_k_vdso_data

/* The यंत्र-generic header needs to be included after the definitions above */
#समावेश <यंत्र-generic/vdso/vsyscall.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_VSYSCALL_H */
