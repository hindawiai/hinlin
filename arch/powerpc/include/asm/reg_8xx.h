<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Contains रेजिस्टर definitions common to PowerPC 8xx CPUs.  Notice
 */
#अगर_अघोषित _ASM_POWERPC_REG_8xx_H
#घोषणा _ASM_POWERPC_REG_8xx_H

/* Cache control on the MPC8xx is provided through some additional
 * special purpose रेजिस्टरs.
 */
#घोषणा SPRN_IC_CST	560	/* Inकाष्ठाion cache control/status */
#घोषणा SPRN_IC_ADR	561	/* Address needed क्रम some commands */
#घोषणा SPRN_IC_DAT	562	/* Read-only data रेजिस्टर */
#घोषणा SPRN_DC_CST	568	/* Data cache control/status */
#घोषणा SPRN_DC_ADR	569	/* Address needed क्रम some commands */
#घोषणा SPRN_DC_DAT	570	/* Read-only data रेजिस्टर */

/* Misc Debug */
#घोषणा SPRN_DPDR	630
#घोषणा SPRN_MI_CAM	816
#घोषणा SPRN_MI_RAM0	817
#घोषणा SPRN_MI_RAM1	818
#घोषणा SPRN_MD_CAM	824
#घोषणा SPRN_MD_RAM0	825
#घोषणा SPRN_MD_RAM1	826

/* Special MSR manipulation रेजिस्टरs */
#घोषणा SPRN_EIE	80	/* External पूर्णांकerrupt enable (EE=1, RI=1) */
#घोषणा SPRN_EID	81	/* External पूर्णांकerrupt disable (EE=0, RI=1) */
#घोषणा SPRN_NRI	82	/* Non recoverable पूर्णांकerrupt (EE=0, RI=0) */

/* Debug रेजिस्टरs */
#घोषणा SPRN_CMPA	144
#घोषणा SPRN_COUNTA	150
#घोषणा SPRN_CMPE	152
#घोषणा SPRN_CMPF	153
#घोषणा SPRN_LCTRL1	156
#घोषणा   LCTRL1_CTE_GT		0xc0000000
#घोषणा   LCTRL1_CTF_LT		0x14000000
#घोषणा   LCTRL1_CRWE_RW	0x00000000
#घोषणा   LCTRL1_CRWE_RO	0x00040000
#घोषणा   LCTRL1_CRWE_WO	0x000c0000
#घोषणा   LCTRL1_CRWF_RW	0x00000000
#घोषणा   LCTRL1_CRWF_RO	0x00010000
#घोषणा   LCTRL1_CRWF_WO	0x00030000
#घोषणा SPRN_LCTRL2	157
#घोषणा   LCTRL2_LW0EN		0x80000000
#घोषणा   LCTRL2_LW0LA_E	0x00000000
#घोषणा   LCTRL2_LW0LA_F	0x04000000
#घोषणा   LCTRL2_LW0LA_EandF	0x08000000
#घोषणा   LCTRL2_LW0LADC	0x02000000
#घोषणा   LCTRL2_SLW0EN		0x00000002
#अगर_घोषित CONFIG_PPC_8xx
#घोषणा SPRN_ICTRL	158
#पूर्ण_अगर
#घोषणा SPRN_BAR	159

/* Commands.  Only the first few are available to the inकाष्ठाion cache.
*/
#घोषणा	IDC_ENABLE	0x02000000	/* Cache enable */
#घोषणा IDC_DISABLE	0x04000000	/* Cache disable */
#घोषणा IDC_LDLCK	0x06000000	/* Load and lock */
#घोषणा IDC_UNLINE	0x08000000	/* Unlock line */
#घोषणा IDC_UNALL	0x0a000000	/* Unlock all */
#घोषणा IDC_INVALL	0x0c000000	/* Invalidate all */

#घोषणा DC_FLINE	0x0e000000	/* Flush data cache line */
#घोषणा DC_SFWT		0x01000000	/* Set क्रमced ग_लिखोthrough mode */
#घोषणा DC_CFWT		0x03000000	/* Clear क्रमced ग_लिखोthrough mode */
#घोषणा DC_SLES		0x05000000	/* Set little endian swap mode */
#घोषणा DC_CLES		0x07000000	/* Clear little endian swap mode */

/* Status.
*/
#घोषणा IDC_ENABLED	0x80000000	/* Cache is enabled */
#घोषणा IDC_CERR1	0x00200000	/* Cache error 1 */
#घोषणा IDC_CERR2	0x00100000	/* Cache error 2 */
#घोषणा IDC_CERR3	0x00080000	/* Cache error 3 */

#घोषणा DC_DFWT		0x40000000	/* Data cache is क्रमced ग_लिखो through */
#घोषणा DC_LES		0x20000000	/* Caches are little endian mode */

#पूर्ण_अगर /* _ASM_POWERPC_REG_8xx_H */
