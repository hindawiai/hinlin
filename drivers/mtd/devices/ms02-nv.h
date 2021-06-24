<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Copyright (c) 2001, 2003  Maciej W. Rozycki
 *
 *	DEC MS02-NV (54-20948-01) battery backed-up NVRAM module क्रम
 *	DECstation/DECप्रणाली 5000/2x0 and DECप्रणाली 5900 and 5900/260
 *	प्रणालीs.
 */

#समावेश <linux/ioport.h>
#समावेश <linux/mtd/mtd.h>

/*
 * Addresses are decoded as follows:
 *
 * 0x000000 - 0x3fffff	SRAM
 * 0x400000 - 0x7fffff	CSR
 *
 * Within the SRAM area the following ranges are क्रमced by the प्रणाली
 * firmware:
 *
 * 0x000000 - 0x0003ff	diagnostic area, destroyed upon a reboot
 * 0x000400 - ENDofRAM	storage area, available to operating प्रणालीs
 *
 * but we can't really use the available area right from 0x000400 as
 * the first word is used by the firmware as a status flag passed
 * from an operating प्रणाली.  If anything but the valid data magic
 * ID value is found, the firmware considers the SRAM clean, i.e.
 * containing no valid data, and disables the battery resulting in
 * data being erased as soon as घातer is चयनed off.  So the choice
 * क्रम the start address of the user-available is 0x001000 which is
 * nicely page aligned.  The area between 0x000404 and 0x000fff may
 * be used by the driver क्रम own needs.
 *
 * The diagnostic area defines two status words to be पढ़ो by an
 * operating प्रणाली, a magic ID to distinguish a MS02-NV board from
 * anything अन्यथा and a status inक्रमmation providing results of tests
 * as well as the size of SRAM available, which can be 1MiB or 2MiB
 * (that's what the firmware handles; no idea अगर 2MiB modules ever
 * existed).
 *
 * The firmware only handles the MS02-NV board अगर installed in the
 * last (15th) slot, so क्रम any other location the status inक्रमmation
 * stored in the SRAM cannot be relied upon.  But from the hardware
 * poपूर्णांक of view there is no problem using up to 14 such boards in a
 * प्रणाली -- only the 1st slot needs to be filled with a DRAM module.
 * The MS02-NV board is ECC-रक्षित, like other MS02 memory boards.
 *
 * The state of the battery as provided by the CSR is reflected on
 * the two onboard LEDs.  When facing the battery side of the board,
 * with the LEDs at the top left and the battery at the bottom right
 * (i.e. looking from the back side of the प्रणाली box), their meaning
 * is as follows (the प्रणाली has to be घातered on):
 *
 * left LED		battery disable status: lit = enabled
 * right LED		battery condition status: lit = OK
 */

/* MS02-NV iomem रेजिस्टर offsets. */
#घोषणा MS02NV_CSR		0x400000	/* control & status रेजिस्टर */

/* MS02-NV CSR status bits. */
#घोषणा MS02NV_CSR_BATT_OK	0x01		/* battery OK */
#घोषणा MS02NV_CSR_BATT_OFF	0x02		/* battery disabled */


/* MS02-NV memory offsets. */
#घोषणा MS02NV_DIAG		0x0003f8	/* diagnostic status */
#घोषणा MS02NV_MAGIC		0x0003fc	/* MS02-NV magic ID */
#घोषणा MS02NV_VALID		0x000400	/* valid data magic ID */
#घोषणा MS02NV_RAM		0x001000	/* user-exposed RAM start */

/* MS02-NV diagnostic status bits. */
#घोषणा MS02NV_DIAG_TEST	0x01		/* SRAM test करोne (?) */
#घोषणा MS02NV_DIAG_RO		0x02		/* SRAM r/o test करोne */
#घोषणा MS02NV_DIAG_RW		0x04		/* SRAM r/w test करोne */
#घोषणा MS02NV_DIAG_FAIL	0x08		/* SRAM test failed */
#घोषणा MS02NV_DIAG_SIZE_MASK	0xf0		/* SRAM size mask */
#घोषणा MS02NV_DIAG_SIZE_SHIFT	0x10		/* SRAM size shअगरt (left) */

/* MS02-NV general स्थिरants. */
#घोषणा MS02NV_ID		0x03021966	/* MS02-NV magic ID value */
#घोषणा MS02NV_VALID_ID		0xbd100248	/* valid data magic ID value */
#घोषणा MS02NV_SLOT_SIZE	0x800000	/* size of the address space
						   decoded by the module */


प्रकार अस्थिर u32 ms02nv_uपूर्णांक;

काष्ठा ms02nv_निजी अणु
	काष्ठा mtd_info *next;
	काष्ठा अणु
		काष्ठा resource *module;
		काष्ठा resource *diag_ram;
		काष्ठा resource *user_ram;
		काष्ठा resource *csr;
	पूर्ण resource;
	u_अक्षर *addr;
	माप_प्रकार size;
	u_अक्षर *uaddr;
पूर्ण;
