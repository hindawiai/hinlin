<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * kexec.h क्रम kexec
 * Created by <nschichan@corp.मुक्त.fr> on Thu Oct 12 14:59:34 2006
 */

#अगर_अघोषित _MIPS_KEXEC
# define _MIPS_KEXEC

#समावेश <यंत्र/stacktrace.h>

/* Maximum physical address we can use pages from */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)
/* Maximum address we can reach in physical address mode */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)
 /* Maximum address we can use क्रम the control code buffer */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT (-1UL)
/* Reserve 3*4096 bytes क्रम board-specअगरic info */
#घोषणा KEXEC_CONTROL_PAGE_SIZE (4096 + 3*4096)

/* The native architecture */
#घोषणा KEXEC_ARCH KEXEC_ARCH_MIPS
#घोषणा MAX_NOTE_BYTES 1024

अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
				    काष्ठा pt_regs *oldregs)
अणु
	अगर (oldregs)
		स_नकल(newregs, oldregs, माप(*newregs));
	अन्यथा
		prepare_frametrace(newregs);
पूर्ण

#अगर_घोषित CONFIG_KEXEC
काष्ठा kimage;
बाह्य अचिन्हित दीर्घ kexec_args[4];
बाह्य पूर्णांक (*_machine_kexec_prepare)(काष्ठा kimage *);
बाह्य व्योम (*_machine_kexec_shutकरोwn)(व्योम);
बाह्य व्योम (*_machine_crash_shutकरोwn)(काष्ठा pt_regs *regs);
व्योम शेष_machine_crash_shutकरोwn(काष्ठा pt_regs *regs);
व्योम kexec_nonboot_cpu_jump(व्योम);
व्योम kexec_reboot(व्योम);
#अगर_घोषित CONFIG_SMP
बाह्य स्थिर अचिन्हित अक्षर kexec_smp_रुको[];
बाह्य अचिन्हित दीर्घ secondary_kexec_args[4];
बाह्य atomic_t kexec_पढ़ोy_to_reboot;
बाह्य व्योम (*_crash_smp_send_stop)(व्योम);
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* !_MIPS_KEXEC */
