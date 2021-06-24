<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#समावेश "general.h"

पूर्णांक bit1cnt_दीर्घ(u32 data)
अणु
	पूर्णांक i, cnt = 0;

	क्रम (i = 0; i < 32; i++) अणु
		अगर (data & 0x01)
			cnt++;
		data >>= 1;
	पूर्ण
	वापस cnt;
पूर्ण

