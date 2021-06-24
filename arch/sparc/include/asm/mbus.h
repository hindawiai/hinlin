<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mbus.h:  Various defines क्रम MBUS modules.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_MBUS_H
#घोषणा _SPARC_MBUS_H

#समावेश <यंत्र/ross.h>    /* HyperSparc stuff */
#समावेश <यंत्र/viking.h>  /* Ugh, bug city... */

क्रमागत mbus_module अणु
	HyperSparc        = 0,
	Swअगरt_ok          = 4,
	Swअगरt_bad_c       = 5,
	Swअगरt_lots_o_bugs = 6,
	Tsunami           = 7,
	Viking_12         = 8,
	Viking_2x         = 9,
	Viking_30         = 10,
	Viking_35         = 11,
	Viking_new        = 12,
	TurboSparc	  = 13,
	SRMMU_INVAL_MOD   = 14,
पूर्ण;

बाह्य क्रमागत mbus_module srmmu_modtype;
बाह्य अचिन्हित पूर्णांक viking_rev, swअगरt_rev, cypress_rev;

/* HW Mbus module bugs we have to deal with */
#घोषणा HWBUG_COPYBACK_BROKEN        0x00000001
#घोषणा HWBUG_ASIFLUSH_BROKEN        0x00000002
#घोषणा HWBUG_VACFLUSH_BITROT        0x00000004
#घोषणा HWBUG_KERN_ACCBROKEN         0x00000008
#घोषणा HWBUG_KERN_CBITBROKEN        0x00000010
#घोषणा HWBUG_MODIFIED_BITROT        0x00000020
#घोषणा HWBUG_PC_BADFAULT_ADDR       0x00000040
#घोषणा HWBUG_SUPERSCALAR_BAD        0x00000080
#घोषणा HWBUG_PACINIT_BITROT         0x00000100

/* First the module type values. To find out which you have, just load
 * the mmu control रेजिस्टर from ASI_M_MMUREG alternate address space and
 * shअगरt the value right 28 bits.
 */
/* IMPL field means the company which produced the chip. */
#घोषणा MBUS_VIKING        0x4   /* bleech, Texas Instruments Module */
#घोषणा MBUS_LSI           0x3   /* LSI Logics */
#घोषणा MBUS_ROSS          0x1   /* Ross is nice */
#घोषणा MBUS_FMI           0x0   /* Fujitsu Microelectronics/Swअगरt */

/* Ross Module versions */
#घोषणा ROSS_604_REV_CDE        0x0   /* revisions c, d, and e */
#घोषणा ROSS_604_REV_F          0x1   /* revision f */
#घोषणा ROSS_605                0xf   /* revision a, a.1, and a.2 */
#घोषणा ROSS_605_REV_B          0xe   /* revision b */

/* TI Viking Module versions */
#घोषणा VIKING_REV_12           0x1   /* Version 1.2 or SPARCclassic's CPU */
#घोषणा VIKING_REV_2            0x2   /* Version 2.1, 2.2, 2.3, and 2.4 */
#घोषणा VIKING_REV_30           0x3   /* Version 3.0 */
#घोषणा VIKING_REV_35           0x4   /* Version 3.5 */

/* LSI Logics. */
#घोषणा LSI_L64815		0x0

/* Fujitsu */
#घोषणा FMI_AURORA		0x4   /* MB8690x, a Swअगरt module... */
#घोषणा FMI_TURBO		0x5   /* MB86907, a TurboSparc module... */

/* For multiprocessor support we need to be able to obtain the CPU id and
 * the MBUS Module id.
 */

/* The CPU ID is encoded in the trap base रेजिस्टर, 20 bits to the left of
 * bit zero, with 2 bits being signअगरicant.
 */
#घोषणा TBR_ID_SHIFT            20

अटल अंतरभूत पूर्णांक get_cpuid(व्योम)
अणु
	रेजिस्टर पूर्णांक retval;
	__यंत्र__ __अस्थिर__("rd %%tbr, %0\n\t"
			     "srl %0, %1, %0\n\t" :
			     "=r" (retval) :
			     "i" (TBR_ID_SHIFT));
	वापस (retval & 3);
पूर्ण

अटल अंतरभूत पूर्णांक get_modid(व्योम)
अणु
	वापस (get_cpuid() | 0x8);
पूर्ण

	
#पूर्ण_अगर /* !(_SPARC_MBUS_H) */
