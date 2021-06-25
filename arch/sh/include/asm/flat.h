<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/flat.h
 *
 * uClinux flat-क्रमmat executables
 *
 * Copyright (C) 2003  Paul Mundt
 */
#अगर_अघोषित __ASM_SH_FLAT_H
#घोषणा __ASM_SH_FLAT_H

#समावेश <यंत्र/unaligned.h>

अटल अंतरभूत पूर्णांक flat_get_addr_from_rp(u32 __user *rp, u32 relval, u32 flags,
					u32 *addr)
अणु
	*addr = get_unaligned((__क्रमce u32 *)rp);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक flat_put_addr_at_rp(u32 __user *rp, u32 addr, u32 rel)
अणु
	put_unaligned(addr, (__क्रमce u32 *)rp);
	वापस 0;
पूर्ण

#घोषणा FLAT_PLAT_INIT(_r) \
  करो अणु _r->regs[0]=0; _r->regs[1]=0; _r->regs[2]=0; _r->regs[3]=0; \
       _r->regs[4]=0; _r->regs[5]=0; _r->regs[6]=0; _r->regs[7]=0; \
       _r->regs[8]=0; _r->regs[9]=0; _r->regs[10]=0; _r->regs[11]=0; \
       _r->regs[12]=0; _r->regs[13]=0; _r->regs[14]=0; \
       _r->sr = SR_FD; पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_SH_FLAT_H */
