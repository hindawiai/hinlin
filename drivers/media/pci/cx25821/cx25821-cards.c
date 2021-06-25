<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 *	Based on Steven Toth <stoth@linuxtv.org> cx23885 driver
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "cx25821.h"

/* board config info */

काष्ठा cx25821_board cx25821_boards[] = अणु
	[UNKNOWN_BOARD] = अणु
		.name = "UNKNOWN/GENERIC",
		/* Ensure safe शेष क्रम unknown boards */
		.clk_freq = 0,
	पूर्ण,

	[CX25821_BOARD] = अणु
		.name = "CX25821",
		.portb = CX25821_RAW,
		.portc = CX25821_264,
	पूर्ण,

पूर्ण;
