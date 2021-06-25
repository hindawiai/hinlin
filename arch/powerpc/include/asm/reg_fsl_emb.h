<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Contains रेजिस्टर definitions क्रम the Freescale Embedded Perक्रमmance
 * Monitor.
 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASM_POWERPC_REG_FSL_EMB_H__
#घोषणा __ASM_POWERPC_REG_FSL_EMB_H__

#समावेश <linux/stringअगरy.h>

#अगर_अघोषित __ASSEMBLY__
/* Perक्रमmance Monitor Registers */
#घोषणा mfpmr(rn)	(अणुअचिन्हित पूर्णांक rval; \
			यंत्र अस्थिर("mfpmr %0," __stringअगरy(rn) \
				     : "=r" (rval)); rval;पूर्ण)
#घोषणा mtpmr(rn, v)	यंत्र अस्थिर("mtpmr " __stringअगरy(rn) ",%0" : : "r" (v))
#पूर्ण_अगर /* __ASSEMBLY__ */

/* Freescale Book E Perक्रमmance Monitor APU Registers */
#घोषणा PMRN_PMC0	0x010	/* Perक्रमmance Monitor Counter 0 */
#घोषणा PMRN_PMC1	0x011	/* Perक्रमmance Monitor Counter 1 */
#घोषणा PMRN_PMC2	0x012	/* Perक्रमmance Monitor Counter 2 */
#घोषणा PMRN_PMC3	0x013	/* Perक्रमmance Monitor Counter 3 */
#घोषणा PMRN_PMC4	0x014	/* Perक्रमmance Monitor Counter 4 */
#घोषणा PMRN_PMC5	0x015	/* Perक्रमmance Monitor Counter 5 */
#घोषणा PMRN_PMLCA0	0x090	/* PM Local Control A0 */
#घोषणा PMRN_PMLCA1	0x091	/* PM Local Control A1 */
#घोषणा PMRN_PMLCA2	0x092	/* PM Local Control A2 */
#घोषणा PMRN_PMLCA3	0x093	/* PM Local Control A3 */
#घोषणा PMRN_PMLCA4	0x094	/* PM Local Control A4 */
#घोषणा PMRN_PMLCA5	0x095	/* PM Local Control A5 */

#घोषणा PMLCA_FC	0x80000000	/* Freeze Counter */
#घोषणा PMLCA_FCS	0x40000000	/* Freeze in Supervisor */
#घोषणा PMLCA_FCU	0x20000000	/* Freeze in User */
#घोषणा PMLCA_FCM1	0x10000000	/* Freeze when PMM==1 */
#घोषणा PMLCA_FCM0	0x08000000	/* Freeze when PMM==0 */
#घोषणा PMLCA_CE	0x04000000	/* Condition Enable */
#घोषणा PMLCA_FGCS1	0x00000002	/* Freeze in guest state */
#घोषणा PMLCA_FGCS0	0x00000001	/* Freeze in hypervisor state */

#घोषणा PMLCA_EVENT_MASK 0x01ff0000	/* Event field */
#घोषणा PMLCA_EVENT_SHIFT	16

#घोषणा PMRN_PMLCB0	0x110	/* PM Local Control B0 */
#घोषणा PMRN_PMLCB1	0x111	/* PM Local Control B1 */
#घोषणा PMRN_PMLCB2	0x112	/* PM Local Control B2 */
#घोषणा PMRN_PMLCB3	0x113	/* PM Local Control B3 */
#घोषणा PMRN_PMLCB4	0x114	/* PM Local Control B4 */
#घोषणा PMRN_PMLCB5	0x115	/* PM Local Control B5 */

#घोषणा PMLCB_THRESHMUL_MASK	0x0700	/* Threshold Multiple Field */
#घोषणा PMLCB_THRESHMUL_SHIFT	8

#घोषणा PMLCB_THRESHOLD_MASK	0x003f	/* Threshold Field */
#घोषणा PMLCB_THRESHOLD_SHIFT	0

#घोषणा PMRN_PMGC0	0x190	/* PM Global Control 0 */

#घोषणा PMGC0_FAC	0x80000000	/* Freeze all Counters */
#घोषणा PMGC0_PMIE	0x40000000	/* Interrupt Enable */
#घोषणा PMGC0_FCECE	0x20000000	/* Freeze countes on
					   Enabled Condition or
					   Event */

#घोषणा PMRN_UPMC0	0x000	/* User Perक्रमmance Monitor Counter 0 */
#घोषणा PMRN_UPMC1	0x001	/* User Perक्रमmance Monitor Counter 1 */
#घोषणा PMRN_UPMC2	0x002	/* User Perक्रमmance Monitor Counter 2 */
#घोषणा PMRN_UPMC3	0x003	/* User Perक्रमmance Monitor Counter 3 */
#घोषणा PMRN_UPMC4	0x004	/* User Perक्रमmance Monitor Counter 4 */
#घोषणा PMRN_UPMC5	0x005	/* User Perक्रमmance Monitor Counter 5 */
#घोषणा PMRN_UPMLCA0	0x080	/* User PM Local Control A0 */
#घोषणा PMRN_UPMLCA1	0x081	/* User PM Local Control A1 */
#घोषणा PMRN_UPMLCA2	0x082	/* User PM Local Control A2 */
#घोषणा PMRN_UPMLCA3	0x083	/* User PM Local Control A3 */
#घोषणा PMRN_UPMLCA4	0x084	/* User PM Local Control A4 */
#घोषणा PMRN_UPMLCA5	0x085	/* User PM Local Control A5 */
#घोषणा PMRN_UPMLCB0	0x100	/* User PM Local Control B0 */
#घोषणा PMRN_UPMLCB1	0x101	/* User PM Local Control B1 */
#घोषणा PMRN_UPMLCB2	0x102	/* User PM Local Control B2 */
#घोषणा PMRN_UPMLCB3	0x103	/* User PM Local Control B3 */
#घोषणा PMRN_UPMLCB4	0x104	/* User PM Local Control B4 */
#घोषणा PMRN_UPMLCB5	0x105	/* User PM Local Control B5 */
#घोषणा PMRN_UPMGC0	0x180	/* User PM Global Control 0 */


#पूर्ण_अगर /* __ASM_POWERPC_REG_FSL_EMB_H__ */
#पूर्ण_अगर /* __KERNEL__ */
