<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_EMULATE_PREFIX_H
#घोषणा _ASM_X86_EMULATE_PREFIX_H

/*
 * Virt escape sequences to trigger inकाष्ठाion emulation;
 * ideally these would decode to 'whole' inकाष्ठाion and not destroy
 * the inकाष्ठाion stream; sadly this is not true क्रम the 'kvm' one :/
 */

#घोषणा __XEN_EMULATE_PREFIX  0x0f,0x0b,0x78,0x65,0x6e  /* ud2 ; .ascii "xen" */
#घोषणा __KVM_EMULATE_PREFIX  0x0f,0x0b,0x6b,0x76,0x6d	/* ud2 ; .ascii "kvm" */

#पूर्ण_अगर
