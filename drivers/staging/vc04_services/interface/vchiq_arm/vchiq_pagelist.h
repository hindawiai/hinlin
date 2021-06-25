<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#अगर_अघोषित VCHIQ_PAGELIST_H
#घोषणा VCHIQ_PAGELIST_H

#घोषणा PAGELIST_WRITE 0
#घोषणा PAGELIST_READ 1
#घोषणा PAGELIST_READ_WITH_FRAGMENTS 2

काष्ठा pagelist अणु
	u32 length;
	u16 type;
	u16 offset;
	u32 addrs[1];	/* N.B. 12 LSBs hold the number
			 * of following pages at consecutive
			 * addresses.
			 */
पूर्ण;

#पूर्ण_अगर /* VCHIQ_PAGELIST_H */
