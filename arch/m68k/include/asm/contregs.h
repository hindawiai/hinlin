<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_CONTREGS_H
#घोषणा _M68K_CONTREGS_H

/* contregs.h:  Addresses of रेजिस्टरs in the ASI_CONTROL alternate address
 *              space. These are क्रम the mmu's context रेजिस्टर, etc.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

/* 3=sun3
   4=sun4 (as in sun4 sysमुख्यt student book)
   c=sun4c (according to davem) */

#घोषणा AC_IDPROM     0x00000000    /* 34  ID PROM, R/O, byte, 32 bytes      */
#घोषणा AC_PAGEMAP    0x10000000    /* 3   Pagemap R/W, दीर्घ                 */
#घोषणा AC_SEGMAP     0x20000000    /* 3   Segment map, byte                 */
#घोषणा AC_CONTEXT    0x30000000    /* 34c current mmu-context               */
#घोषणा AC_SENABLE    0x40000000    /* 34c प्रणाली dvma/cache/reset enable reg*/
#घोषणा AC_UDVMA_ENB  0x50000000    /* 34  Not used on Sun boards, byte      */
#घोषणा AC_BUS_ERROR  0x60000000    /* 34  Not cleared on पढ़ो, byte.        */
#घोषणा AC_SYNC_ERR   0x60000000    /*  c fault type                         */
#घोषणा AC_SYNC_VA    0x60000004    /*  c fault भव address              */
#घोषणा AC_ASYNC_ERR  0x60000008    /*  c asynchronous fault type            */
#घोषणा AC_ASYNC_VA   0x6000000c    /*  c async fault भव address        */
#घोषणा AC_LEDS       0x70000000    /* 34  Zero turns on LEDs, byte          */
#घोषणा AC_CACHETAGS  0x80000000    /* 34c direct access to the VAC tags     */
#घोषणा AC_CACHEDDATA 0x90000000    /* 3 c direct access to the VAC data     */
#घोषणा AC_UDVMA_MAP  0xD0000000    /* 4  Not used on Sun boards, byte       */
#घोषणा AC_VME_VECTOR 0xE0000000    /* 4  For non-Autovector VME, byte       */
#घोषणा AC_BOOT_SCC   0xF0000000    /* 34  bypass to access Zilog 8530. byte.*/

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

#पूर्ण_अगर /* _M68K_CONTREGS_H */
