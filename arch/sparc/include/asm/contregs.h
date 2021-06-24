<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_CONTREGS_H
#घोषणा _SPARC_CONTREGS_H

/* contregs.h:  Addresses of रेजिस्टरs in the ASI_CONTROL alternate address
 *              space. These are क्रम the mmu's context रेजिस्टर, etc.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

/* s=Swअगरt, h=Ross_HyperSPARC, v=TI_Viking, t=Tsunami, r=Ross_Cypress        */
#घोषणा AC_M_PCR      0x0000        /* shv Processor Control Reg             */
#घोषणा AC_M_CTPR     0x0100        /* shv Context Table Poपूर्णांकer Reg         */
#घोषणा AC_M_CXR      0x0200        /* shv Context Register                  */
#घोषणा AC_M_SFSR     0x0300        /* shv Synchronous Fault Status Reg      */
#घोषणा AC_M_SFAR     0x0400        /* shv Synchronous Fault Address Reg     */
#घोषणा AC_M_AFSR     0x0500        /*  hv Asynchronous Fault Status Reg     */
#घोषणा AC_M_AFAR     0x0600        /*  hv Asynchronous Fault Address Reg    */
#घोषणा AC_M_RESET    0x0700        /*  hv Reset Reg                         */
#घोषणा AC_M_RPR      0x1000        /*  hv Root Poपूर्णांकer Reg                  */
#घोषणा AC_M_TSUTRCR  0x1000        /* s   TLB Replacement Ctrl Reg          */
#घोषणा AC_M_IAPTP    0x1100        /*  hv Inकाष्ठाion Access PTP            */
#घोषणा AC_M_DAPTP    0x1200        /*  hv Data Access PTP                   */
#घोषणा AC_M_ITR      0x1300        /*  hv Index Tag Register                */
#घोषणा AC_M_TRCR     0x1400        /*  hv TLB Replacement Control Reg       */
#घोषणा AC_M_SFSRX    0x1300        /* s   Synch Fault Status Reg prim       */
#घोषणा AC_M_SFARX    0x1400        /* s   Synch Fault Address Reg prim      */
#घोषणा AC_M_RPR1     0x1500        /*  h  Root Poपूर्णांकer Reg (entry 2)        */
#घोषणा AC_M_IAPTP1   0x1600        /*  h  Inकाष्ठाion Access PTP (entry 2)  */
#घोषणा AC_M_DAPTP1   0x1700        /*  h  Data Access PTP (entry 2)         */

#पूर्ण_अगर /* _SPARC_CONTREGS_H */
