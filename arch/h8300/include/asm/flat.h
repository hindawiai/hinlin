<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/h8300/यंत्र/include/flat.h -- uClinux flat-क्रमmat executables
 */

#अगर_अघोषित __H8300_FLAT_H__
#घोषणा __H8300_FLAT_H__

#समावेश <यंत्र/unaligned.h>

/*
 * on the H8 a couple of the relocations have an inकाष्ठाion in the
 * top byte.  As there can only be 24bits of address space,  we just
 * always preserve that 8bits at the top,  when it isn't an inकाष्ठाion
 * is is 0 (davidm@snapgear.com)
 */

#घोषणा	flat_get_relocate_addr(rel)		(rel & ~0x00000001)
अटल अंतरभूत पूर्णांक flat_get_addr_from_rp(u32 __user *rp, u32 relval, u32 flags,
					u32 *addr)
अणु
	u32 val = get_unaligned((__क्रमce u32 *)rp);
	अगर (!(flags & FLAT_FLAG_GOTPIC))
		val &= 0x00ffffff;
	*addr = val;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक flat_put_addr_at_rp(u32 __user *rp, u32 addr, u32 rel)
अणु
	u32 *p = (__क्रमce u32 *)rp;
	put_unaligned((addr & 0x00ffffff) | (*(अक्षर *)p << 24), p);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __H8300_FLAT_H__ */
