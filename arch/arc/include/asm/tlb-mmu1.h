<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_TLB_MMU_V1_H__
#घोषणा __ASM_TLB_MMU_V1_H__

#समावेश <यंत्र/mmu.h>

#अगर defined(__ASSEMBLY__) && (CONFIG_ARC_MMU_VER == 1)

.macro TLB_WRITE_HEURISTICS

#घोषणा JH_HACK1
#अघोषित JH_HACK2
#अघोषित JH_HACK3

#अगर_घोषित JH_HACK3
; Calculate set index क्रम 2-way MMU
; -aव्योमing use of GetIndex from MMU
;   and its unpleasant LFSR pseuकरो-अक्रमom sequence
;
; r1 = TLBPD0 from TLB_RELOAD above
;
; -- jh_ex_way_set not cleared on startup
;    didn't want to change setup.c
;    hence extra inकाष्ठाion to clean
;
; -- should be in cache since in same line
;    as r0/r1 saves above
;
ld  r0,[jh_ex_way_sel]  ; victim poपूर्णांकer
and r0,r0,1         ; clean
xor.f   r0,r0,1         ; flip
st  r0,[jh_ex_way_sel]  ; store back
asr r0,r1,12        ; get set # <<1, note bit 12=R=0
or.nz   r0,r0,1         ; set way bit
and r0,r0,0xff      ; clean
sr  r0,[ARC_REG_TLBINDEX]
#पूर्ण_अगर

#अगर_घोषित JH_HACK2
; JH hack #2
;  Faster than hack #1 in non-thrash हाल, but hard-coded क्रम 2-way MMU
;  Slower in thrash हाल (where it matters) because more code is executed
;  Inefficient due to two-रेजिस्टर paradigm of this miss handler
;
/* r1 = data TLBPD0 at this poपूर्णांक */
lr      r0,[eret]               /* inकाष्ठाion address */
xor     r0,r0,r1                /* compare set #       */
and.f   r0,r0,0x000fe000        /* 2-way MMU mask      */
bne     88f                     /* not in same set - no need to probe */

lr      r0,[eret]               /* inकाष्ठाion address */
and     r0,r0,PAGE_MASK         /* VPN of inकाष्ठाion address */
; lr  r1,[ARC_REG_TLBPD0]     /* Data VPN+ASID - alपढ़ोy in r1 from TLB_RELOAD*/
and     r1,r1,0xff              /* Data ASID */
or      r0,r0,r1                /* Inकाष्ठाion address + Data ASID */

lr      r1,[ARC_REG_TLBPD0]     /* save TLBPD0 containing data TLB*/
sr      r0,[ARC_REG_TLBPD0]     /* ग_लिखो inकाष्ठाion address to TLBPD0 */
sr      TLBProbe, [ARC_REG_TLBCOMMAND] /* Look क्रम inकाष्ठाion */
lr      r0,[ARC_REG_TLBINDEX]   /* r0 = index where inकाष्ठाion is, अगर at all */
sr      r1,[ARC_REG_TLBPD0]     /* restore TLBPD0 */

xor     r0,r0,1                 /* flip bottom bit of data index */
b.d     89f
sr      r0,[ARC_REG_TLBINDEX]   /* and put it back */
88:
sr  TLBGetIndex, [ARC_REG_TLBCOMMAND]
89:
#पूर्ण_अगर

#अगर_घोषित JH_HACK1
;
; Always checks whether inकाष्ठाion will be kicked out by dtlb miss
;
mov_s   r3, r1                  ; save PD0 prepared by TLB_RELOAD in r3
lr      r0,[eret]               /* inकाष्ठाion address */
and     r0,r0,PAGE_MASK         /* VPN of inकाष्ठाion address */
bmsk    r1,r3,7                 /* Data ASID, bits 7-0 */
or_s    r0,r0,r1                /* Inकाष्ठाion address + Data ASID */

sr      r0,[ARC_REG_TLBPD0]     /* ग_लिखो inकाष्ठाion address to TLBPD0 */
sr      TLBProbe, [ARC_REG_TLBCOMMAND] /* Look क्रम inकाष्ठाion */
lr      r0,[ARC_REG_TLBINDEX]   /* r0 = index where inकाष्ठाion is, अगर at all */
sr      r3,[ARC_REG_TLBPD0]     /* restore TLBPD0 */

sr      TLBGetIndex, [ARC_REG_TLBCOMMAND]
lr      r1,[ARC_REG_TLBINDEX]   /* r1 = index where MMU wants to put data */
cmp     r0,r1                   /* अगर no match on indices, go around */
xor.eq  r1,r1,1                 /* flip bottom bit of data index */
sr      r1,[ARC_REG_TLBINDEX]   /* and put it back */
#पूर्ण_अगर

.endm

#पूर्ण_अगर

#पूर्ण_अगर
