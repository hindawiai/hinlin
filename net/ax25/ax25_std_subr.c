<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

/*
 * The following routines are taken from page 170 of the 7th ARRL Computer
 * Networking Conference paper, as is the whole state machine.
 */

व्योम ax25_std_nr_error_recovery(ax25_cb *ax25)
अणु
	ax25_std_establish_data_link(ax25);
पूर्ण

व्योम ax25_std_establish_data_link(ax25_cb *ax25)
अणु
	ax25->condition = 0x00;
	ax25->n2count   = 0;

	अगर (ax25->modulus == AX25_MODULUS)
		ax25_send_control(ax25, AX25_SABM, AX25_POLLON, AX25_COMMAND);
	अन्यथा
		ax25_send_control(ax25, AX25_SABME, AX25_POLLON, AX25_COMMAND);

	ax25_calculate_t1(ax25);
	ax25_stop_idleसमयr(ax25);
	ax25_stop_t3समयr(ax25);
	ax25_stop_t2समयr(ax25);
	ax25_start_t1समयr(ax25);
पूर्ण

व्योम ax25_std_transmit_enquiry(ax25_cb *ax25)
अणु
	अगर (ax25->condition & AX25_COND_OWN_RX_BUSY)
		ax25_send_control(ax25, AX25_RNR, AX25_POLLON, AX25_COMMAND);
	अन्यथा
		ax25_send_control(ax25, AX25_RR, AX25_POLLON, AX25_COMMAND);

	ax25->condition &= ~AX25_COND_ACK_PENDING;

	ax25_calculate_t1(ax25);
	ax25_start_t1समयr(ax25);
पूर्ण

व्योम ax25_std_enquiry_response(ax25_cb *ax25)
अणु
	अगर (ax25->condition & AX25_COND_OWN_RX_BUSY)
		ax25_send_control(ax25, AX25_RNR, AX25_POLLON, AX25_RESPONSE);
	अन्यथा
		ax25_send_control(ax25, AX25_RR, AX25_POLLON, AX25_RESPONSE);

	ax25->condition &= ~AX25_COND_ACK_PENDING;
पूर्ण

व्योम ax25_std_समयout_response(ax25_cb *ax25)
अणु
	अगर (ax25->condition & AX25_COND_OWN_RX_BUSY)
		ax25_send_control(ax25, AX25_RNR, AX25_POLLOFF, AX25_RESPONSE);
	अन्यथा
		ax25_send_control(ax25, AX25_RR, AX25_POLLOFF, AX25_RESPONSE);

	ax25->condition &= ~AX25_COND_ACK_PENDING;
पूर्ण
