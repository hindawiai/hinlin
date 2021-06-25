<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_XTENSA_FLAT_H
#घोषणा __ASM_XTENSA_FLAT_H

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

#पूर्ण_अगर /* __ASM_XTENSA_FLAT_H */
