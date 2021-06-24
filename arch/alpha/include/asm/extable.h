<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_EXTABLE_H
#घोषणा _ASM_EXTABLE_H

/*
 * About the exception table:
 *
 * - insn is a 32-bit pc-relative offset from the faulting insn.
 * - nextinsn is a 16-bit offset off of the faulting inकाष्ठाion
 *   (not off of the *next* inकाष्ठाion as branches are).
 * - errreg is the रेजिस्टर in which to place -EFAULT.
 * - valreg is the final target रेजिस्टर क्रम the load sequence
 *   and will be zeroed.
 *
 * Either errreg or valreg may be $31, in which हाल nothing happens.
 *
 * The exception fixup inक्रमmation "just so happens" to be arranged
 * as in a MEM क्रमmat inकाष्ठाion.  This lets us emit our three
 * values like so:
 *
 *      lda valreg, nextinsn(errreg)
 *
 */

काष्ठा exception_table_entry
अणु
	चिन्हित पूर्णांक insn;
	जोड़ exception_fixup अणु
		अचिन्हित unit;
		काष्ठा अणु
			चिन्हित पूर्णांक nextinsn : 16;
			अचिन्हित पूर्णांक errreg : 5;
			अचिन्हित पूर्णांक valreg : 5;
		पूर्ण bits;
	पूर्ण fixup;
पूर्ण;

/* Returns the new pc */
#घोषणा fixup_exception(map_reg, _fixup, pc)			\
(अणु								\
	अगर ((_fixup)->fixup.bits.valreg != 31)			\
		map_reg((_fixup)->fixup.bits.valreg) = 0;	\
	अगर ((_fixup)->fixup.bits.errreg != 31)			\
		map_reg((_fixup)->fixup.bits.errreg) = -EFAULT;	\
	(pc) + (_fixup)->fixup.bits.nextinsn;			\
पूर्ण)

#घोषणा ARCH_HAS_RELATIVE_EXTABLE

#घोषणा swap_ex_entry_fixup(a, b, पंचांगp, delta)			\
	करो अणु							\
		(a)->fixup.unit = (b)->fixup.unit;		\
		(b)->fixup.unit = (पंचांगp).fixup.unit;		\
	पूर्ण जबतक (0)

#पूर्ण_अगर
