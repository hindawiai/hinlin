<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_OHARE_H
#घोषणा _ASM_POWERPC_OHARE_H
#अगर_घोषित __KERNEL__
/*
 * ohare.h: definitions क्रम using the "O'Hare" I/O controller chip.
 *
 * Copyright (C) 1997 Paul Mackerras.
 *
 * BenH: Changed to match those of heathrow (but not all of them). Please
 *       check अगर I didn't अवरोध anything (especially the media bay).
 */

/* offset from ohare base क्रम feature control रेजिस्टर */
#घोषणा OHARE_MBCR	0x34
#घोषणा OHARE_FCR	0x38

/*
 * Bits in feature control रेजिस्टर.
 * These were mostly derived by experiment on a घातerbook 3400
 * and may dअगरfer क्रम other machines.
 */
#घोषणा OH_SCC_RESET		1
#घोषणा OH_BAY_POWER_N		2	/* a guess */
#घोषणा OH_BAY_PCI_ENABLE	4	/* a guess */
#घोषणा OH_BAY_IDE_ENABLE	8
#घोषणा OH_BAY_FLOPPY_ENABLE	0x10
#घोषणा OH_IDE0_ENABLE		0x20
#घोषणा OH_IDE0_RESET_N		0x40	/* a guess */
#घोषणा OH_BAY_DEV_MASK		0x1c
#घोषणा OH_BAY_RESET_N		0x80
#घोषणा OH_IOBUS_ENABLE		0x100	/* IOBUS seems to be IDE */
#घोषणा OH_SCC_ENABLE		0x200
#घोषणा OH_MESH_ENABLE		0x400
#घोषणा OH_FLOPPY_ENABLE	0x800
#घोषणा OH_SCCA_IO		0x4000
#घोषणा OH_SCCB_IO		0x8000
#घोषणा OH_VIA_ENABLE		0x10000	/* Is apparently wrong, to be verअगरied */
#घोषणा OH_IDE1_RESET_N		0x800000

/*
 * Bits to set in the feature control रेजिस्टर on PowerBooks.
 */
#घोषणा PBOOK_FEATURES		(OH_IDE_ENABLE | OH_SCC_ENABLE | \
				 OH_MESH_ENABLE | OH_SCCA_IO | OH_SCCB_IO)

/*
 * A magic value to put पूर्णांकo the feature control रेजिस्टर of the
 * "ohare" I/O controller on Starmaxes to enable the IDE CD पूर्णांकerface.
 * Contributed by Harry Eaton.
 */
#घोषणा STARMAX_FEATURES	0xbeff7a

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_OHARE_H */
