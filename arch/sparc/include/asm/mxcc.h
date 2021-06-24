<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mxcc.h:  Definitions of the Viking MXCC रेजिस्टरs
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_MXCC_H
#घोषणा _SPARC_MXCC_H

/* These रेजिस्टरs are accessed through ASI 0x2. */
#घोषणा MXCC_DATSTREAM       0x1C00000  /* Data stream रेजिस्टर */
#घोषणा MXCC_SRCSTREAM       0x1C00100  /* Source stream रेजिस्टर */
#घोषणा MXCC_DESSTREAM       0x1C00200  /* Destination stream रेजिस्टर */
#घोषणा MXCC_RMCOUNT         0x1C00300  /* Count of references and misses */
#घोषणा MXCC_STEST           0x1C00804  /* Internal self-test */
#घोषणा MXCC_CREG            0x1C00A04  /* Control रेजिस्टर */
#घोषणा MXCC_SREG            0x1C00B00  /* Status रेजिस्टर */
#घोषणा MXCC_RREG            0x1C00C04  /* Reset रेजिस्टर */
#घोषणा MXCC_EREG            0x1C00E00  /* Error code रेजिस्टर */
#घोषणा MXCC_PREG            0x1C00F04  /* Address port रेजिस्टर */

/* Some MXCC स्थिरants. */
#घोषणा MXCC_STREAM_SIZE     0x20       /* Size in bytes of one stream r/w */

/* The MXCC Control Register:
 *
 * ----------------------------------------------------------------------
 * |                                   | RRC | RSV |PRE|MCE|PARE|ECE|RSV|
 * ----------------------------------------------------------------------
 *  31                              10    9    8-6   5   4    3   2  1-0
 *
 * RRC: Controls what you पढ़ो from MXCC_RMCOUNT reg.
 *      0=Misses 1=References
 * PRE: Prefetch enable
 * MCE: Multiple Command Enable
 * PARE: Parity enable
 * ECE: External cache enable
 */

#घोषणा MXCC_CTL_RRC   0x00000200
#घोषणा MXCC_CTL_PRE   0x00000020
#घोषणा MXCC_CTL_MCE   0x00000010
#घोषणा MXCC_CTL_PARE  0x00000008
#घोषणा MXCC_CTL_ECE   0x00000004

/* The MXCC Error Register:
 *
 * --------------------------------------------------------
 * |ME| RSV|CE|PEW|PEE|ASE|EIV| MOPC|ECODE|PRIV|RSV|HPADDR|
 * --------------------------------------------------------
 *  31   30 29  28  27  26  25 24-15  14-7   6  5-3   2-0
 *
 * ME: Multiple Errors have occurred
 * CE: Cache consistency Error
 * PEW: Parity Error during a Write operation
 * PEE: Parity Error involving the External cache
 * ASE: ASynchronous Error
 * EIV: This रेजिस्टर is toast
 * MOPC: MXCC Operation Code क्रम instance causing error
 * ECODE: The Error CODE
 * PRIV: A privileged mode error? 0=no 1=yes
 * HPADDR: High PhysicalADDRess bits (35-32)
 */

#घोषणा MXCC_ERR_ME     0x80000000
#घोषणा MXCC_ERR_CE     0x20000000
#घोषणा MXCC_ERR_PEW    0x10000000
#घोषणा MXCC_ERR_PEE    0x08000000
#घोषणा MXCC_ERR_ASE    0x04000000
#घोषणा MXCC_ERR_EIV    0x02000000
#घोषणा MXCC_ERR_MOPC   0x01FF8000
#घोषणा MXCC_ERR_ECODE  0x00007F80
#घोषणा MXCC_ERR_PRIV   0x00000040
#घोषणा MXCC_ERR_HPADDR 0x0000000f

/* The MXCC Port रेजिस्टर:
 *
 * -----------------------------------------------------
 * |                | MID |                            |
 * -----------------------------------------------------
 *  31            21 20-18 17                         0
 *
 * MID: The moduleID of the cpu your पढ़ो this from.
 */

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम mxcc_set_stream_src(अचिन्हित दीर्घ *paddr)
अणु
	अचिन्हित दीर्घ data0 = paddr[0];
	अचिन्हित दीर्घ data1 = paddr[1];

	__यंत्र__ __अस्थिर__ ("or %%g0, %0, %%g2\n\t"
			      "or %%g0, %1, %%g3\n\t"
			      "stda %%g2, [%2] %3\n\t" : :
			      "r" (data0), "r" (data1),
			      "r" (MXCC_SRCSTREAM),
			      "i" (ASI_M_MXCC) : "g2", "g3");
पूर्ण

अटल अंतरभूत व्योम mxcc_set_stream_dst(अचिन्हित दीर्घ *paddr)
अणु
	अचिन्हित दीर्घ data0 = paddr[0];
	अचिन्हित दीर्घ data1 = paddr[1];

	__यंत्र__ __अस्थिर__ ("or %%g0, %0, %%g2\n\t"
			      "or %%g0, %1, %%g3\n\t"
			      "stda %%g2, [%2] %3\n\t" : :
			      "r" (data0), "r" (data1),
			      "r" (MXCC_DESSTREAM),
			      "i" (ASI_M_MXCC) : "g2", "g3");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mxcc_get_creg(व्योम)
अणु
	अचिन्हित दीर्घ mxcc_control;

	__यंत्र__ __अस्थिर__("set 0xffffffff, %%g2\n\t"
			     "set 0xffffffff, %%g3\n\t"
			     "stda %%g2, [%1] %2\n\t"
			     "lda [%3] %2, %0\n\t" :
			     "=r" (mxcc_control) :
			     "r" (MXCC_EREG), "i" (ASI_M_MXCC),
			     "r" (MXCC_CREG) : "g2", "g3");
	वापस mxcc_control;
पूर्ण

अटल अंतरभूत व्योम mxcc_set_creg(अचिन्हित दीर्घ mxcc_control)
अणु
	__यंत्र__ __अस्थिर__("sta %0, [%1] %2\n\t" : :
			     "r" (mxcc_control), "r" (MXCC_CREG),
			     "i" (ASI_M_MXCC));
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* !(_SPARC_MXCC_H) */
