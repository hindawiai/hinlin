<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_MFP_H
#घोषणा __ASM_MACH_MFP_H

#समावेश <plat/mfp.h>

/*
 * NOTE: the MFPR रेजिस्टर bit definitions on PXA168 processor lines are a
 * bit dअगरferent from those on PXA3xx.  Bit [7:10] are now reserved, which
 * were SLEEP_OE_N, SLEEP_DATA, SLEEP_SEL and the LSB of DRIVE bits.
 *
 * To cope with this dअगरference and re-use the pxa3xx mfp code as much as
 * possible, we make the following compromise:
 *
 * 1. SLEEP_OE_N will always be programmed to '1' (by MFP_LPM_FLOAT)
 * 2. DRIVE strength definitions redefined to include the reserved bit
 *    - the reserved bit dअगरfers between pxa168 and pxa910, and the
 *      MFP_DRIVE_* macros are inभागidually defined in mfp-pxaअणु168,910पूर्ण.h
 * 3. Override MFP_CFG() and MFP_CFG_DRV()
 * 4. Drop the use of MFP_CFG_LPM() and MFP_CFG_X()
 */

#अघोषित MFP_CFG
#अघोषित MFP_CFG_DRV
#अघोषित MFP_CFG_LPM
#अघोषित MFP_CFG_X
#अघोषित MFP_CFG_DEFAULT

#घोषणा MFP_CFG(pin, af)		\
	(MFP_LPM_FLOAT | MFP_PIN(MFP_PIN_##pin) | MFP_##af | MFP_DRIVE_MEDIUM)

#घोषणा MFP_CFG_DRV(pin, af, drv)	\
	(MFP_LPM_FLOAT | MFP_PIN(MFP_PIN_##pin) | MFP_##af | MFP_DRIVE_##drv)

#पूर्ण_अगर /* __ASM_MACH_MFP_H */
