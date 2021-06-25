<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_ASM_SYSCALL_H
#घोषणा __UM_ASM_SYSCALL_H

#समावेश <यंत्र/syscall-generic.h>
#समावेश <uapi/linux/audit.h>

प्रकार यंत्रlinkage दीर्घ (*sys_call_ptr_t)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
					  अचिन्हित दीर्घ, अचिन्हित दीर्घ,
					  अचिन्हित दीर्घ, अचिन्हित दीर्घ);

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_X86_32
	वापस AUDIT_ARCH_I386;
#अन्यथा
	वापस AUDIT_ARCH_X86_64;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __UM_ASM_SYSCALL_H */
