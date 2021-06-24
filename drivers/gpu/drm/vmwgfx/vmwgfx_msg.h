<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ OR MIT */
/**************************************************************************
 *
 * Copyright 2016 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************
 *
 * Based on code from vmware.c and vmmouse.c.
 * Author:
 *   Sinclair Yeh <syeh@vmware.com>
 */
#अगर_अघोषित _VMWGFX_MSG_H
#घोषणा _VMWGFX_MSG_H

#समावेश <यंत्र/vmware.h>

/**
 * Hypervisor-specअगरic bi-directional communication channel.  Should never
 * execute on bare metal hardware.  The caller must make sure to check क्रम
 * supported hypervisor beक्रमe using these macros.
 *
 * The last two parameters are both input and output and must be initialized.
 *
 * @cmd: [IN] Message Cmd
 * @in_ebx: [IN] Message Len, through EBX
 * @in_si: [IN] Input argument through SI, set to 0 अगर not used
 * @in_di: [IN] Input argument through DI, set ot 0 अगर not used
 * @flags: [IN] hypercall flags + [channel id]
 * @magic: [IN] hypervisor magic value
 * @eax: [OUT] value of EAX रेजिस्टर
 * @ebx: [OUT] e.g. status from an HB message status command
 * @ecx: [OUT] e.g. status from a non-HB message status command
 * @edx: [OUT] e.g. channel id
 * @si:  [OUT]
 * @di:  [OUT]
 */
#घोषणा VMW_PORT(cmd, in_ebx, in_si, in_di,	\
		 flags, magic,		\
		 eax, ebx, ecx, edx, si, di)	\
(अणु						\
	यंत्र अस्थिर (VMWARE_HYPERCALL :	\
		"=a"(eax),			\
		"=b"(ebx),			\
		"=c"(ecx),			\
		"=d"(edx),			\
		"=S"(si),			\
		"=D"(di) :			\
		"a"(magic),			\
		"b"(in_ebx),			\
		"c"(cmd),			\
		"d"(flags),			\
		"S"(in_si),			\
		"D"(in_di) :			\
		"memory");			\
पूर्ण)


/**
 * Hypervisor-specअगरic bi-directional communication channel.  Should never
 * execute on bare metal hardware.  The caller must make sure to check क्रम
 * supported hypervisor beक्रमe using these macros.
 *
 * The last 3 parameters are both input and output and must be initialized.
 *
 * @cmd: [IN] Message Cmd
 * @in_ecx: [IN] Message Len, through ECX
 * @in_si: [IN] Input argument through SI, set to 0 अगर not used
 * @in_di: [IN] Input argument through DI, set to 0 अगर not used
 * @flags: [IN] hypercall flags + [channel id]
 * @magic: [IN] hypervisor magic value
 * @bp:  [IN]
 * @eax: [OUT] value of EAX रेजिस्टर
 * @ebx: [OUT] e.g. status from an HB message status command
 * @ecx: [OUT] e.g. status from a non-HB message status command
 * @edx: [OUT] e.g. channel id
 * @si:  [OUT]
 * @di:  [OUT]
 */
#अगर_घोषित __x86_64__

#घोषणा VMW_PORT_HB_OUT(cmd, in_ecx, in_si, in_di,	\
			flags, magic, bp,		\
			eax, ebx, ecx, edx, si, di)	\
(अणु							\
	यंत्र अस्थिर ("push %%rbp;"			\
		"mov %12, %%rbp;"			\
		VMWARE_HYPERCALL_HB_OUT			\
		"pop %%rbp;" :				\
		"=a"(eax),				\
		"=b"(ebx),				\
		"=c"(ecx),				\
		"=d"(edx),				\
		"=S"(si),				\
		"=D"(di) :				\
		"a"(magic),				\
		"b"(cmd),				\
		"c"(in_ecx),				\
		"d"(flags),				\
		"S"(in_si),				\
		"D"(in_di),				\
		"r"(bp) :				\
		"memory", "cc");			\
पूर्ण)


#घोषणा VMW_PORT_HB_IN(cmd, in_ecx, in_si, in_di,	\
		       flags, magic, bp,		\
		       eax, ebx, ecx, edx, si, di)	\
(अणु							\
	यंत्र अस्थिर ("push %%rbp;"			\
		"mov %12, %%rbp;"			\
		VMWARE_HYPERCALL_HB_IN			\
		"pop %%rbp" :				\
		"=a"(eax),				\
		"=b"(ebx),				\
		"=c"(ecx),				\
		"=d"(edx),				\
		"=S"(si),				\
		"=D"(di) :				\
		"a"(magic),				\
		"b"(cmd),				\
		"c"(in_ecx),				\
		"d"(flags),				\
		"S"(in_si),				\
		"D"(in_di),				\
		"r"(bp) :				\
		"memory", "cc");			\
पूर्ण)

#अन्यथा

/*
 * In the 32-bit version of this macro, we store bp in a memory location
 * because we've ran out of रेजिस्टरs.
 * Now we can't reference that memory location while we've modअगरied
 * %esp or %ebp, so we first push it on the stack, just beक्रमe we push
 * %ebp, and then when we need it we पढ़ो it from the stack where we
 * just pushed it.
 */
#घोषणा VMW_PORT_HB_OUT(cmd, in_ecx, in_si, in_di,	\
			flags, magic, bp,		\
			eax, ebx, ecx, edx, si, di)	\
(अणु							\
	यंत्र अस्थिर ("push %12;"			\
		"push %%ebp;"				\
		"mov 0x04(%%esp), %%ebp;"		\
		VMWARE_HYPERCALL_HB_OUT			\
		"pop %%ebp;"				\
		"add $0x04, %%esp;" :			\
		"=a"(eax),				\
		"=b"(ebx),				\
		"=c"(ecx),				\
		"=d"(edx),				\
		"=S"(si),				\
		"=D"(di) :				\
		"a"(magic),				\
		"b"(cmd),				\
		"c"(in_ecx),				\
		"d"(flags),				\
		"S"(in_si),				\
		"D"(in_di),				\
		"m"(bp) :				\
		"memory", "cc");			\
पूर्ण)


#घोषणा VMW_PORT_HB_IN(cmd, in_ecx, in_si, in_di,	\
		       flags, magic, bp,		\
		       eax, ebx, ecx, edx, si, di)	\
(अणु							\
	यंत्र अस्थिर ("push %12;"			\
		"push %%ebp;"				\
		"mov 0x04(%%esp), %%ebp;"		\
		VMWARE_HYPERCALL_HB_IN			\
		"pop %%ebp;"				\
		"add $0x04, %%esp;" :			\
		"=a"(eax),				\
		"=b"(ebx),				\
		"=c"(ecx),				\
		"=d"(edx),				\
		"=S"(si),				\
		"=D"(di) :				\
		"a"(magic),				\
		"b"(cmd),				\
		"c"(in_ecx),				\
		"d"(flags),				\
		"S"(in_si),				\
		"D"(in_di),				\
		"m"(bp) :				\
		"memory", "cc");			\
पूर्ण)
#पूर्ण_अगर /* #अगर __x86_64__ */

#पूर्ण_अगर
