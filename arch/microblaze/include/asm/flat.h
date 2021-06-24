<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * uClinux flat-क्रमmat executables
 *
 * Copyright (C) 2005 John Williams <jwilliams@itee.uq.edu.au>
 */

#अगर_अघोषित _ASM_MICROBLAZE_FLAT_H
#घोषणा _ASM_MICROBLAZE_FLAT_H

#समावेश <यंत्र/unaligned.h>

/*
 * Microblaze works a little dअगरferently from other arches, because
 * of the MICROBLAZE_64 reloc type. Here, a 32 bit address is split
 * over two inकाष्ठाions, an 'imm' inकाष्ठाion which provides the top
 * 16 bits, then the inकाष्ठाion "proper" which provides the low 16
 * bits.
 */

/*
 * Crack खोलो a symbol reference and extract the address to be
 * relocated. rp is a potentially unaligned poपूर्णांकer to the
 * reference
 */

अटल अंतरभूत पूर्णांक flat_get_addr_from_rp(u32 __user *rp, u32 relval, u32 flags,
					u32 *addr)
अणु
	u32 *p = (__क्रमce u32 *)rp;

	/* Is it a split 64/32 reference? */
	अगर (relval & 0x80000000) अणु
		/* Grab the two halves of the reference */
		u32 val_hi, val_lo;

		val_hi = get_unaligned(p);
		val_lo = get_unaligned(p+1);

		/* Crack the address out */
		*addr = ((val_hi & 0xffff) << 16) + (val_lo & 0xffff);
	पूर्ण अन्यथा अणु
		/* Get the address straight out */
		*addr = get_unaligned(p);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Insert an address पूर्णांकo the symbol reference at rp. rp is potentially
 * unaligned.
 */

अटल अंतरभूत पूर्णांक
flat_put_addr_at_rp(u32 __user *rp, u32 addr, u32 relval)
अणु
	u32 *p = (__क्रमce u32 *)rp;
	/* Is this a split 64/32 reloc? */
	अगर (relval & 0x80000000) अणु
		/* Get the two "halves" */
		अचिन्हित दीर्घ val_hi = get_unaligned(p);
		अचिन्हित दीर्घ val_lo = get_unaligned(p + 1);

		/* insert the address */
		val_hi = (val_hi & 0xffff0000) | addr >> 16;
		val_lo = (val_lo & 0xffff0000) | (addr & 0xffff);

		/* store the two halves back पूर्णांकo memory */
		put_unaligned(val_hi, p);
		put_unaligned(val_lo, p+1);
	पूर्ण अन्यथा अणु
		/* Put it straight in, no messing around */
		put_unaligned(addr, p);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा	flat_get_relocate_addr(rel)	(rel & 0x7fffffff)

#पूर्ण_अगर /* _ASM_MICROBLAZE_FLAT_H */
