<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * xtalk.h -- platक्रमm-independent crosstalk पूर्णांकerface, derived from
 * IRIX <sys/PCI/bridge.h>, revision 1.38.
 *
 * Copyright (C) 1995 - 1997, 1999 Silcon Graphics, Inc.
 * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)
 */
#अगर_अघोषित _ASM_XTALK_XTALK_H
#घोषणा _ASM_XTALK_XTALK_H

#अगर_अघोषित __ASSEMBLY__
/*
 * User-level device driver visible types
 */
प्रकार अक्षर		xwidgetnum_t;	/* xtalk widget number	(0..15) */

#घोषणा XWIDGET_NONE		-1

प्रकार पूर्णांक xwidget_part_num_t; /* xtalk widget part number */

#घोषणा XWIDGET_PART_NUM_NONE	-1

प्रकार पूर्णांक		xwidget_rev_num_t;	/* xtalk widget revision number */

#घोषणा XWIDGET_REV_NUM_NONE	-1

प्रकार पूर्णांक xwidget_mfg_num_t;	/* xtalk widget manufacturing ID */

#घोषणा XWIDGET_MFG_NUM_NONE	-1

प्रकार काष्ठा xtalk_piomap_s *xtalk_piomap_t;

/* It is often convenient to fold the XIO target port
 * number पूर्णांकo the XIO address.
 */
#घोषणा XIO_NOWHERE	(0xFFFFFFFFFFFFFFFFull)
#घोषणा XIO_ADDR_BITS	(0x0000FFFFFFFFFFFFull)
#घोषणा XIO_PORT_BITS	(0xF000000000000000ull)
#घोषणा XIO_PORT_SHIFT	(60)

#घोषणा XIO_PACKED(x)	(((x)&XIO_PORT_BITS) != 0)
#घोषणा XIO_ADDR(x)	((x)&XIO_ADDR_BITS)
#घोषणा XIO_PORT(x)	((xwidgetnum_t)(((x)&XIO_PORT_BITS) >> XIO_PORT_SHIFT))
#घोषणा XIO_PACK(p, o)	((((uपूर्णांक64_t)(p))<<XIO_PORT_SHIFT) | ((o)&XIO_ADDR_BITS))

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_XTALK_XTALK_H */
