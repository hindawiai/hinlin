<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_VM86_H
#घोषणा _UAPI_ASM_X86_VM86_H

/*
 * I'm guessing at the VIF/VIP flag usage, but hope that this is how
 * the Pentium uses them. Linux will वापस from vm86 mode when both
 * VIF and VIP is set.
 *
 * On a Pentium, we could probably optimize the भव flags directly
 * in the eflags रेजिस्टर instead of करोing it "by hand" in vflags...
 *
 * Linus
 */

#समावेश <यंत्र/processor-flags.h>

#घोषणा BIOSSEG		0x0f000

#घोषणा CPU_086		0
#घोषणा CPU_186		1
#घोषणा CPU_286		2
#घोषणा CPU_386		3
#घोषणा CPU_486		4
#घोषणा CPU_586		5

/*
 * Return values क्रम the 'vm86()' प्रणाली call
 */
#घोषणा VM86_TYPE(retval)	((retval) & 0xff)
#घोषणा VM86_ARG(retval)	((retval) >> 8)

#घोषणा VM86_SIGNAL	0	/* वापस due to संकेत */
#घोषणा VM86_UNKNOWN	1	/* unhandled GP fault
				   - IO-inकाष्ठाion or similar */
#घोषणा VM86_INTx	2	/* पूर्णांक3/पूर्णांक x inकाष्ठाion (ARG = x) */
#घोषणा VM86_STI	3	/* sti/popf/iret inकाष्ठाion enabled
				   भव पूर्णांकerrupts */

/*
 * Additional वापस values when invoking new vm86()
 */
#घोषणा VM86_PICRETURN	4	/* वापस due to pending PIC request */
#घोषणा VM86_TRAP	6	/* वापस due to DOS-debugger request */

/*
 * function codes when invoking new vm86()
 */
#घोषणा VM86_PLUS_INSTALL_CHECK	0
#घोषणा VM86_ENTER		1
#घोषणा VM86_ENTER_NO_BYPASS	2
#घोषणा	VM86_REQUEST_IRQ	3
#घोषणा VM86_FREE_IRQ		4
#घोषणा VM86_GET_IRQ_BITS	5
#घोषणा VM86_GET_AND_RESET_IRQ	6

/*
 * This is the stack-layout seen by the user space program when we have
 * करोne a translation of "SAVE_ALL" from vm86 mode. The real kernel layout
 * is 'kernel_vm86_regs' (see below).
 */

काष्ठा vm86_regs अणु
/*
 * normal regs, with special meaning क्रम the segment descriptors..
 */
	दीर्घ ebx;
	दीर्घ ecx;
	दीर्घ edx;
	दीर्घ esi;
	दीर्घ edi;
	दीर्घ ebp;
	दीर्घ eax;
	दीर्घ __null_ds;
	दीर्घ __null_es;
	दीर्घ __null_fs;
	दीर्घ __null_gs;
	दीर्घ orig_eax;
	दीर्घ eip;
	अचिन्हित लघु cs, __csh;
	दीर्घ eflags;
	दीर्घ esp;
	अचिन्हित लघु ss, __ssh;
/*
 * these are specअगरic to v86 mode:
 */
	अचिन्हित लघु es, __esh;
	अचिन्हित लघु ds, __dsh;
	अचिन्हित लघु fs, __fsh;
	अचिन्हित लघु gs, __gsh;
पूर्ण;

काष्ठा revectored_काष्ठा अणु
	अचिन्हित दीर्घ __map[8];			/* 256 bits */
पूर्ण;

काष्ठा vm86_काष्ठा अणु
	काष्ठा vm86_regs regs;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ screen_biपंचांगap;		/* unused, preserved by vm86() */
	अचिन्हित दीर्घ cpu_type;
	काष्ठा revectored_काष्ठा पूर्णांक_revectored;
	काष्ठा revectored_काष्ठा पूर्णांक21_revectored;
पूर्ण;

/*
 * flags masks
 */
#घोषणा VM86_SCREEN_BITMAP	0x0001        /* no दीर्घer supported */

काष्ठा vm86plus_info_काष्ठा अणु
	अचिन्हित दीर्घ क्रमce_वापस_क्रम_pic:1;
	अचिन्हित दीर्घ vm86dbg_active:1;       /* क्रम debugger */
	अचिन्हित दीर्घ vm86dbg_TFpendig:1;     /* क्रम debugger */
	अचिन्हित दीर्घ unused:28;
	अचिन्हित दीर्घ is_vm86pus:1;	      /* क्रम vm86 पूर्णांकernal use */
	अचिन्हित अक्षर vm86dbg_पूर्णांकxxtab[32];   /* क्रम debugger */
पूर्ण;
काष्ठा vm86plus_काष्ठा अणु
	काष्ठा vm86_regs regs;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ screen_biपंचांगap;
	अचिन्हित दीर्घ cpu_type;
	काष्ठा revectored_काष्ठा पूर्णांक_revectored;
	काष्ठा revectored_काष्ठा पूर्णांक21_revectored;
	काष्ठा vm86plus_info_काष्ठा vm86plus;
पूर्ण;


#पूर्ण_अगर /* _UAPI_ASM_X86_VM86_H */
