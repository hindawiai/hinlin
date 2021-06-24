<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IPWireless 3G PCMCIA Network Driver
 *
 * Original code
 *   by Stephen Blackheath <stephen@blacksapphire.com>,
 *      Ben Martel <benm@symmetric.co.nz>
 *
 * Copyrighted as follows:
 *   Copyright (C) 2004 by Symmetric Systems Ltd (NZ)
 *
 * Various driver changes and reग_लिखोs, port to new kernels
 *   Copyright (C) 2006-2007 Jiri Kosina
 *
 * Misc code cleanups and updates
 *   Copyright (C) 2007 David Sterba
 */

#अगर_अघोषित _IPWIRELESS_CS_TTY_H_
#घोषणा _IPWIRELESS_CS_TTY_H_

#समावेश <linux/types.h>
#समावेश <linux/sched.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

काष्ठा ipw_tty;
काष्ठा ipw_network;
काष्ठा ipw_hardware;

पूर्णांक ipwireless_tty_init(व्योम);
व्योम ipwireless_tty_release(व्योम);

काष्ठा ipw_tty *ipwireless_tty_create(काष्ठा ipw_hardware *hw,
				      काष्ठा ipw_network *net);
व्योम ipwireless_tty_मुक्त(काष्ठा ipw_tty *tty);
व्योम ipwireless_tty_received(काष्ठा ipw_tty *tty, अचिन्हित अक्षर *data,
			     अचिन्हित पूर्णांक length);
पूर्णांक ipwireless_tty_is_modem(काष्ठा ipw_tty *tty);
व्योम ipwireless_tty_notअगरy_control_line_change(काष्ठा ipw_tty *tty,
					       अचिन्हित पूर्णांक channel_idx,
					       अचिन्हित पूर्णांक control_lines,
					       अचिन्हित पूर्णांक changed_mask);

#पूर्ण_अगर
