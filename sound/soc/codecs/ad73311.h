<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * File:         sound/soc/codec/ad73311.h
 * Based on:
 * Author:       Clअगरf Cai <clअगरf.cai@analog.com>
 *
 * Created:      Thur Sep 25, 2008
 * Description:  definitions क्रम AD73311 रेजिस्टरs
 *
 * Modअगरied:
 *               Copyright 2006 Analog Devices Inc.
 *
 * Bugs:         Enter bugs at http://blackfin.uclinux.org/
 */

#अगर_अघोषित __AD73311_H__
#घोषणा __AD73311_H__

#घोषणा AD_CONTROL	0x8000
#घोषणा AD_DATA		0x0000
#घोषणा AD_READ		0x4000
#घोषणा AD_WRITE	0x0000

/* Control रेजिस्टर A */
#घोषणा CTRL_REG_A	(0 << 8)

#घोषणा REGA_MODE_PRO	0x00
#घोषणा REGA_MODE_DATA	0x01
#घोषणा REGA_MODE_MIXED	0x03
#घोषणा REGA_DLB		0x04
#घोषणा REGA_SLB		0x08
#घोषणा REGA_DEVC(x)		((x & 0x7) << 4)
#घोषणा REGA_RESET		0x80

/* Control रेजिस्टर B */
#घोषणा CTRL_REG_B	(1 << 8)

#घोषणा REGB_सूचीATE(x)	(x & 0x3)
#घोषणा REGB_SCDIV(x)	((x & 0x3) << 2)
#घोषणा REGB_MCDIV(x)	((x & 0x7) << 4)
#घोषणा REGB_CEE		(1 << 7)

/* Control रेजिस्टर C */
#घोषणा CTRL_REG_C	(2 << 8)

#घोषणा REGC_PUDEV		(1 << 0)
#घोषणा REGC_PUADC		(1 << 3)
#घोषणा REGC_PUDAC		(1 << 4)
#घोषणा REGC_PUREF		(1 << 5)
#घोषणा REGC_REFUSE		(1 << 6)

/* Control रेजिस्टर D */
#घोषणा CTRL_REG_D	(3 << 8)

#घोषणा REGD_IGS(x)		(x & 0x7)
#घोषणा REGD_RMOD		(1 << 3)
#घोषणा REGD_OGS(x)		((x & 0x7) << 4)
#घोषणा REGD_MUTE		(1 << 7)

/* Control रेजिस्टर E */
#घोषणा CTRL_REG_E	(4 << 8)

#घोषणा REGE_DA(x)		(x & 0x1f)
#घोषणा REGE_IBYP		(1 << 5)

/* Control रेजिस्टर F */
#घोषणा CTRL_REG_F	(5 << 8)

#घोषणा REGF_SEEN		(1 << 5)
#घोषणा REGF_INV		(1 << 6)
#घोषणा REGF_ALB		(1 << 7)

#पूर्ण_अगर
