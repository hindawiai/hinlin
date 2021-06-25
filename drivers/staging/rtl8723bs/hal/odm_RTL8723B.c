<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

s8 odm_CCKRSSI_8723B(u8 LNA_idx, u8 VGA_idx)
अणु
	s8 rx_pwr_all = 0x00;

	चयन (LNA_idx) अणु
	/* 46  53 73 95 201301231630 */
	/*  46 53 77 99 201301241630 */

	हाल 6:
		rx_pwr_all = -34 - (2 * VGA_idx);
		अवरोध;
	हाल 4:
		rx_pwr_all = -14 - (2 * VGA_idx);
		अवरोध;
	हाल 1:
		rx_pwr_all = 6 - (2 * VGA_idx);
		अवरोध;
	हाल 0:
		rx_pwr_all = 16 - (2 * VGA_idx);
		अवरोध;
	शेष:
		/* rx_pwr_all = -53+(2*(31-VGA_idx)); */
		/* DbgPrपूर्णांक("wrong LNA index\n"); */
		अवरोध;

	पूर्ण
	वापस rx_pwr_all;
पूर्ण
