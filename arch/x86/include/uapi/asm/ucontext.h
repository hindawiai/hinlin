<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_UCONTEXT_H
#घोषणा _ASM_X86_UCONTEXT_H

/*
 * Indicates the presence of extended state inक्रमmation in the memory
 * layout poपूर्णांकed by the fpstate poपूर्णांकer in the ucontext's sigcontext
 * काष्ठा (uc_mcontext).
 */
#घोषणा UC_FP_XSTATE	0x1

#अगर_घोषित __x86_64__
/*
 * UC_SIGCONTEXT_SS will be set when delivering 64-bit or x32 संकेतs on
 * kernels that save SS in the sigcontext.  All kernels that set
 * UC_SIGCONTEXT_SS will correctly restore at least the low 32 bits of esp
 * regardless of SS (i.e. they implement espfix).
 *
 * Kernels that set UC_SIGCONTEXT_SS will also set UC_STRICT_RESTORE_SS
 * when delivering a संकेत that came from 64-bit code.
 *
 * Sigवापस restores SS as follows:
 *
 * अगर (saved SS is valid || UC_STRICT_RESTORE_SS is set ||
 *     saved CS is not 64-bit)
 *         new SS = saved SS  (will fail IRET and संकेत अगर invalid)
 * अन्यथा
 *         new SS = a flat 32-bit data segment
 *
 * This behavior serves three purposes:
 *
 * - Legacy programs that स्थिरruct a 64-bit sigcontext from scratch
 *   with zero or garbage in the SS slot (e.g. old CRIU) and call
 *   sigवापस will still work.
 *
 * - Old DOSEMU versions someबार catch a संकेत from a segmented
 *   context, delete the old SS segment (with modअगरy_ldt), and change
 *   the saved CS to a 64-bit segment.  These DOSEMU versions expect
 *   sigवापस to send them back to 64-bit mode without समाप्तing them,
 *   despite the fact that the SS selector when the संकेत was उठाओd is
 *   no दीर्घer valid.  UC_STRICT_RESTORE_SS will be clear, so the kernel
 *   will fix up SS क्रम these DOSEMU versions.
 *
 * - Old and new programs that catch a संकेत and वापस without
 *   modअगरying the saved context will end up in exactly the state they
 *   started in, even अगर they were running in a segmented context when
 *   the संकेत was उठाओd..  Old kernels would lose track of the
 *   previous SS value.
 */
#घोषणा UC_SIGCONTEXT_SS	0x2
#घोषणा UC_STRICT_RESTORE_SS	0x4
#पूर्ण_अगर

#समावेश <यंत्र-generic/ucontext.h>

#पूर्ण_अगर /* _ASM_X86_UCONTEXT_H */
