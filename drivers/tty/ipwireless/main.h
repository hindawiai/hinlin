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

#अगर_अघोषित _IPWIRELESS_CS_H_
#घोषणा _IPWIRELESS_CS_H_

#समावेश <linux/sched.h>
#समावेश <linux/types.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश "hardware.h"

#घोषणा IPWIRELESS_PCCARD_NAME		"ipwireless"
#घोषणा IPWIRELESS_PCMCIA_VERSION	"1.1"
#घोषणा IPWIRELESS_PCMCIA_AUTHOR        \
	"Stephen Blackheath, Ben Martel, Jiri Kosina and David Sterba"

#घोषणा IPWIRELESS_TX_QUEUE_SIZE  262144
#घोषणा IPWIRELESS_RX_QUEUE_SIZE  262144

#घोषणा IPWIRELESS_STATE_DEBUG

काष्ठा ipw_hardware;
काष्ठा ipw_network;
काष्ठा ipw_tty;

काष्ठा ipw_dev अणु
	काष्ठा pcmcia_device *link;
	पूर्णांक is_v2_card;

	व्योम __iomem *attr_memory;

	व्योम __iomem *common_memory;

	/* Reference to attribute memory, containing CIS data */
	व्योम *attribute_memory;

	/* Hardware context */
	काष्ठा ipw_hardware *hardware;
	/* Network layer context */
	काष्ठा ipw_network *network;
	/* TTY device context */
	काष्ठा ipw_tty *tty;
	काष्ठा work_काष्ठा work_reboot;
पूर्ण;

/* Module parametres */
बाह्य पूर्णांक ipwireless_debug;
बाह्य पूर्णांक ipwireless_loopback;
बाह्य पूर्णांक ipwireless_out_queue;

#पूर्ण_अगर
