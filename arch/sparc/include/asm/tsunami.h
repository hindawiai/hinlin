<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tsunami.h:  Module specअगरic definitions क्रम Tsunami V8 Sparcs
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_TSUNAMI_H
#घोषणा _SPARC_TSUNAMI_H

#समावेश <यंत्र/asi.h>

/* The MMU control रेजिस्टर on the Tsunami:
 *
 * -----------------------------------------------------------------------
 * | implvers |SW|AV|DV|MV| RSV |PC|ITD|ALC| RSV |PE| RC |IE|DE|RSV|NF|ME|
 * -----------------------------------------------------------------------
 *  31      24 23 22 21 20 19-18 17  16 14  13-12 11 10-9  8  7 6-2  1  0
 *
 * SW: Enable Software Table Walks  0=off 1=on
 * AV: Address View bit
 * DV: Data View bit
 * MV: Memory View bit
 * PC: Parity Control
 * ITD: ITBR disable
 * ALC: Alternate Cacheable
 * PE: Parity Enable   0=off 1=on
 * RC: Refresh Control
 * IE: Inकाष्ठाion cache Enable  0=off 1=on
 * DE: Data cache Enable  0=off 1=on
 * NF: No Fault, same as all other SRMMUs
 * ME: MMU Enable, same as all other SRMMUs
 */

#घोषणा TSUNAMI_SW        0x00800000
#घोषणा TSUNAMI_AV        0x00400000
#घोषणा TSUNAMI_DV        0x00200000
#घोषणा TSUNAMI_MV        0x00100000
#घोषणा TSUNAMI_PC        0x00020000
#घोषणा TSUNAMI_ITD       0x00010000
#घोषणा TSUNAMI_ALC       0x00008000
#घोषणा TSUNAMI_PE        0x00001000
#घोषणा TSUNAMI_RCMASK    0x00000C00
#घोषणा TSUNAMI_IENAB     0x00000200
#घोषणा TSUNAMI_DENAB     0x00000100
#घोषणा TSUNAMI_NF        0x00000002
#घोषणा TSUNAMI_ME        0x00000001

अटल अंतरभूत व्योम tsunami_flush_icache(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outमाला_दो */
			     : "i" (ASI_M_IC_FLCLEAR)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम tsunami_flush_dcache(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outमाला_दो */
			     : "i" (ASI_M_DC_FLCLEAR)
			     : "memory");
पूर्ण

#पूर्ण_अगर /* !(_SPARC_TSUNAMI_H) */
