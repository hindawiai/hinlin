<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Miscellaneous bits
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

/*
 * The maximum listening backlog queue size that may be set on a socket by
 * listen().
 */
अचिन्हित पूर्णांक rxrpc_max_backlog __पढ़ो_mostly = 10;

/*
 * How दीर्घ to रुको beक्रमe scheduling ACK generation after seeing a
 * packet with RXRPC_REQUEST_ACK set (in jअगरfies).
 */
अचिन्हित दीर्घ rxrpc_requested_ack_delay = 1;

/*
 * How दीर्घ to रुको beक्रमe scheduling an ACK with subtype DELAY (in jअगरfies).
 *
 * We use this when we've received new data packets.  If those packets aren't
 * all consumed within this समय we will send a DELAY ACK अगर an ACK was not
 * requested to let the sender know it करोesn't need to resend.
 */
अचिन्हित दीर्घ rxrpc_soft_ack_delay = HZ;

/*
 * How दीर्घ to रुको beक्रमe scheduling an ACK with subtype IDLE (in jअगरfies).
 *
 * We use this when we've consumed some previously soft-ACK'd packets when
 * further packets aren't immediately received to decide when to send an IDLE
 * ACK let the other end know that it can मुक्त up its Tx buffer space.
 */
अचिन्हित दीर्घ rxrpc_idle_ack_delay = HZ / 2;

/*
 * Receive winकरोw size in packets.  This indicates the maximum number of
 * unconsumed received packets we're willing to retain in memory.  Once this
 * limit is hit, we should generate an EXCEEDS_WINDOW ACK and discard further
 * packets.
 */
अचिन्हित पूर्णांक rxrpc_rx_winकरोw_size = RXRPC_INIT_RX_WINDOW_SIZE;
#अगर (RXRPC_RXTX_BUFF_SIZE - 1) < RXRPC_INIT_RX_WINDOW_SIZE
#त्रुटि Need to reduce RXRPC_INIT_RX_WINDOW_SIZE
#पूर्ण_अगर

/*
 * Maximum Rx MTU size.  This indicates to the sender the size of jumbo packet
 * made by gluing normal packets together that we're willing to handle.
 */
अचिन्हित पूर्णांक rxrpc_rx_mtu = 5692;

/*
 * The maximum number of fragments in a received jumbo packet that we tell the
 * sender that we're willing to handle.
 */
अचिन्हित पूर्णांक rxrpc_rx_jumbo_max = 4;

स्थिर s8 rxrpc_ack_priority[] = अणु
	[0]				= 0,
	[RXRPC_ACK_DELAY]		= 1,
	[RXRPC_ACK_REQUESTED]		= 2,
	[RXRPC_ACK_IDLE]		= 3,
	[RXRPC_ACK_DUPLICATE]		= 4,
	[RXRPC_ACK_OUT_OF_SEQUENCE]	= 5,
	[RXRPC_ACK_EXCEEDS_WINDOW]	= 6,
	[RXRPC_ACK_NOSPACE]		= 7,
	[RXRPC_ACK_PING_RESPONSE]	= 8,
पूर्ण;
