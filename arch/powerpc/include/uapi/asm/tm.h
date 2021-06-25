<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_TM_H
#घोषणा _ASM_POWERPC_TM_H

/* Reason codes describing kernel causes क्रम transaction पातs.  By
 * convention, bit0 is copied to TEXASR[56] (IBM bit 7) which is set अगर
 * the failure is persistent.  PAPR saves 0xff-0xe0 क्रम the hypervisor.
 */
#घोषणा TM_CAUSE_PERSISTENT	0x01
#घोषणा TM_CAUSE_KVM_RESCHED	0xe0  /* From PAPR */
#घोषणा TM_CAUSE_KVM_FAC_UNAV	0xe2  /* From PAPR */
#घोषणा TM_CAUSE_RESCHED	0xde
#घोषणा TM_CAUSE_TLBI		0xdc
#घोषणा TM_CAUSE_FAC_UNAV	0xda
#घोषणा TM_CAUSE_SYSCALL	0xd8
#घोषणा TM_CAUSE_MISC		0xd6  /* future use */
#घोषणा TM_CAUSE_SIGNAL		0xd4
#घोषणा TM_CAUSE_ALIGNMENT	0xd2
#घोषणा TM_CAUSE_EMULATE	0xd0

#पूर्ण_अगर
