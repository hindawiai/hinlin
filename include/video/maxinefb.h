<शैली गुरु>
/*
 *      linux/drivers/video/maxinefb.h
 *
 *      DECstation 5000/xx onboard framebuffer support, Copyright (C) 1999 by
 *      Michael Engel <engel@unix-ag.org> and Karsten Merker <merker@guug.de>
 *      This file is subject to the terms and conditions of the GNU General
 *      Public License.  See the file COPYING in the मुख्य directory of this
 *      archive क्रम more details.
 */

#समावेश <यंत्र/addrspace.h>

/*
 * IMS332 video controller रेजिस्टर base address
 */
#घोषणा MAXINEFB_IMS332_ADDRESS		KSEG1ADDR(0x1c140000)

/*
 * Begin of DECstation 5000/xx onboard framebuffer memory, शेष resolution
 * is 1024x768x8
 */
#घोषणा DS5000_xx_ONBOARD_FBMEM_START	KSEG1ADDR(0x0a000000)

/*
 *      The IMS 332 video controller used in the DECstation 5000/xx series
 *      uses 32 bits wide रेजिस्टरs; the following defines declare the
 *      रेजिस्टर numbers, to get the real offset, these have to be multiplied
 *      by four.
 */

#घोषणा IMS332_REG_CURSOR_RAM           0x200	/* hardware cursor biपंचांगap */

/*
 * The color palette entries have the क्रमm 0x00BBGGRR
 */
#घोषणा IMS332_REG_COLOR_PALETTE        0x100	/* color palette, 256 entries */
#घोषणा IMS332_REG_CURSOR_COLOR_PALETTE	0x0a1	/* cursor color palette, */
						/* 3 entries             */
