<शैली गुरु>
/*
 *	linux/include/video/pmag-ba-fb.h
 *
 *	TURBOchannel PMAG-BA Color Frame Buffer (CFB) card support,
 *	Copyright (C) 1999, 2000, 2001 by
 *	Michael Engel <engel@unix-ag.org>,
 *	Karsten Merker <merker@linuxtag.org>
 *	Copyright (c) 2005  Maciej W. Rozycki
 *
 *	This file is subject to the terms and conditions of the GNU General
 *	Public License.  See the file COPYING in the मुख्य directory of this
 *	archive क्रम more details.
 */

/* IOmem resource offsets.  */
#घोषणा PMAG_BA_FBMEM		0x000000	/* frame buffer */
#घोषणा PMAG_BA_BT459		0x200000	/* Bt459 RAMDAC */
#घोषणा PMAG_BA_IRQ		0x300000	/* IRQ acknowledge */
#घोषणा PMAG_BA_ROM		0x380000	/* REX option ROM */
#घोषणा PMAG_BA_BT438		0x380000	/* Bt438 घड़ी chip reset */
#घोषणा PMAG_BA_SIZE		0x400000	/* address space size */

/* Bt459 रेजिस्टर offsets, byte-wide रेजिस्टरs.  */
#घोषणा BT459_ADDR_LO		0x0		/* address low */
#घोषणा BT459_ADDR_HI		0x4		/* address high */
#घोषणा BT459_DATA		0x8		/* data winकरोw रेजिस्टर */
#घोषणा BT459_CMAP		0xc		/* color map winकरोw रेजिस्टर */
