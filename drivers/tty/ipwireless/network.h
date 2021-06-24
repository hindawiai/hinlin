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

#अगर_अघोषित _IPWIRELESS_CS_NETWORK_H_
#घोषणा _IPWIRELESS_CS_NETWORK_H_

#समावेश <linux/types.h>

काष्ठा ipw_network;
काष्ठा ipw_tty;
काष्ठा ipw_hardware;

/* Definitions of the dअगरferent channels on the PCMCIA UE */
#घोषणा IPW_CHANNEL_RAS      0
#घोषणा IPW_CHANNEL_DIALLER  1
#घोषणा IPW_CHANNEL_CONSOLE  2
#घोषणा NO_OF_IPW_CHANNELS   5

व्योम ipwireless_network_notअगरy_control_line_change(काष्ठा ipw_network *net,
		अचिन्हित पूर्णांक channel_idx, अचिन्हित पूर्णांक control_lines,
		अचिन्हित पूर्णांक control_mask);
व्योम ipwireless_network_packet_received(काष्ठा ipw_network *net,
		अचिन्हित पूर्णांक channel_idx, अचिन्हित अक्षर *data,
		अचिन्हित पूर्णांक length);
काष्ठा ipw_network *ipwireless_network_create(काष्ठा ipw_hardware *hw);
व्योम ipwireless_network_मुक्त(काष्ठा ipw_network *net);
व्योम ipwireless_associate_network_tty(काष्ठा ipw_network *net,
		अचिन्हित पूर्णांक channel_idx, काष्ठा ipw_tty *tty);
व्योम ipwireless_disassociate_network_ttys(काष्ठा ipw_network *net,
		अचिन्हित पूर्णांक channel_idx);

व्योम ipwireless_ppp_खोलो(काष्ठा ipw_network *net);

व्योम ipwireless_ppp_बंद(काष्ठा ipw_network *net);
पूर्णांक ipwireless_ppp_channel_index(काष्ठा ipw_network *net);
पूर्णांक ipwireless_ppp_unit_number(काष्ठा ipw_network *net);
पूर्णांक ipwireless_ppp_mru(स्थिर काष्ठा ipw_network *net);

#पूर्ण_अगर
