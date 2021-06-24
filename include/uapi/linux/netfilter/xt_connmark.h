<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _XT_CONNMARK_H
#घोषणा _XT_CONNMARK_H

#समावेश <linux/types.h>

/* Copyright (C) 2002,2004 MARA Systems AB <https://www.maraप्रणालीs.com>
 * by Henrik Nordstrom <hno@maraप्रणालीs.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

क्रमागत अणु
	XT_CONNMARK_SET = 0,
	XT_CONNMARK_SAVE,
	XT_CONNMARK_RESTORE
पूर्ण;

क्रमागत अणु
	D_SHIFT_LEFT = 0,
	D_SHIFT_RIGHT,
पूर्ण;

काष्ठा xt_connmark_tginfo1 अणु
	__u32 cपंचांगark, cपंचांगask, nfmask;
	__u8 mode;
पूर्ण;

काष्ठा xt_connmark_tginfo2 अणु
	__u32 cपंचांगark, cपंचांगask, nfmask;
	__u8 shअगरt_dir, shअगरt_bits, mode;
पूर्ण;

काष्ठा xt_connmark_mtinfo1 अणु
	__u32 mark, mask;
	__u8 invert;
पूर्ण;

#पूर्ण_अगर /*_XT_CONNMARK_H*/
