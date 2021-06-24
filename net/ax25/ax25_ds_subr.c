<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/net.h>
#समावेश <linux/gfp.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

व्योम ax25_ds_nr_error_recovery(ax25_cb *ax25)
अणु
	ax25_ds_establish_data_link(ax25);
पूर्ण

/*
 *	dl1bke 960114: transmit I frames on DAMA poll
 */
व्योम ax25_ds_enquiry_response(ax25_cb *ax25)
अणु
	ax25_cb *ax25o;

	/* Please note that neither DK4EG's nor DG2FEF's
	 * DAMA spec mention the following behaviour as seen
	 * with TheFirmware:
	 *
	 * 	DB0ACH->DL1BKE <RR C P R0> [DAMA]
	 *	DL1BKE->DB0ACH <I NR=0 NS=0>
	 *	DL1BKE-7->DB0PRA-6 DB0ACH <I C S3 R5>
	 *	DL1BKE->DB0ACH <RR R F R0>
	 *
	 * The Flexnet DAMA Master implementation apparently
	 * insists on the "proper" AX.25 behaviour:
	 *
	 * 	DB0ACH->DL1BKE <RR C P R0> [DAMA]
	 *	DL1BKE->DB0ACH <RR R F R0>
	 *	DL1BKE->DB0ACH <I NR=0 NS=0>
	 *	DL1BKE-7->DB0PRA-6 DB0ACH <I C S3 R5>
	 *
	 * Flexnet refuses to send us *any* I frame अगर we send
	 * a REJ in हाल AX25_COND_REJECT is set. It is superfluous in
	 * this mode anyway (a RR or RNR invokes the retransmission).
	 * Is this a Flexnet bug?
	 */

	ax25_std_enquiry_response(ax25);

	अगर (!(ax25->condition & AX25_COND_PEER_RX_BUSY)) अणु
		ax25_requeue_frames(ax25);
		ax25_kick(ax25);
	पूर्ण

	अगर (ax25->state == AX25_STATE_1 || ax25->state == AX25_STATE_2 || skb_peek(&ax25->ack_queue) != शून्य)
		ax25_ds_t1_समयout(ax25);
	अन्यथा
		ax25->n2count = 0;

	ax25_start_t3समयr(ax25);
	ax25_ds_set_समयr(ax25->ax25_dev);

	spin_lock(&ax25_list_lock);
	ax25_क्रम_each(ax25o, &ax25_list) अणु
		अगर (ax25o == ax25)
			जारी;

		अगर (ax25o->ax25_dev != ax25->ax25_dev)
			जारी;

		अगर (ax25o->state == AX25_STATE_1 || ax25o->state == AX25_STATE_2) अणु
			ax25_ds_t1_समयout(ax25o);
			जारी;
		पूर्ण

		अगर (!(ax25o->condition & AX25_COND_PEER_RX_BUSY) && ax25o->state == AX25_STATE_3) अणु
			ax25_requeue_frames(ax25o);
			ax25_kick(ax25o);
		पूर्ण

		अगर (ax25o->state == AX25_STATE_1 || ax25o->state == AX25_STATE_2 || skb_peek(&ax25o->ack_queue) != शून्य)
			ax25_ds_t1_समयout(ax25o);

		/* करो not start T3 क्रम listening sockets (tnx DD8NE) */

		अगर (ax25o->state != AX25_STATE_0)
			ax25_start_t3समयr(ax25o);
	पूर्ण
	spin_unlock(&ax25_list_lock);
पूर्ण

व्योम ax25_ds_establish_data_link(ax25_cb *ax25)
अणु
	ax25->condition &= AX25_COND_DAMA_MODE;
	ax25->n2count    = 0;
	ax25_calculate_t1(ax25);
	ax25_start_t1समयr(ax25);
	ax25_stop_t2समयr(ax25);
	ax25_start_t3समयr(ax25);
पूर्ण

/*
 *	:::FIXME:::
 *	This is a kludge. Not all drivers recognize kiss commands.
 *	We need a driver level  request to चयन duplex mode, that करोes
 *	either SCC changing, PI config or KISS as required. Currently
 *	this request isn't reliable.
 */
अटल व्योम ax25_kiss_cmd(ax25_dev *ax25_dev, अचिन्हित अक्षर cmd, अचिन्हित अक्षर param)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *p;

	अगर (ax25_dev->dev == शून्य)
		वापस;

	अगर ((skb = alloc_skb(2, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reset_network_header(skb);
	p = skb_put(skb, 2);

	*p++ = cmd;
	*p++ = param;

	skb->protocol = ax25_type_trans(skb, ax25_dev->dev);

	dev_queue_xmit(skb);
पूर्ण

/*
 *	A nasty problem arises अगर we count the number of DAMA connections
 *	wrong, especially when connections on the device alपढ़ोy existed
 *	and our network node (or the sysop) decides to turn on DAMA Master
 *	mode. We thus flag the 'real' slave connections with
 *	ax25->dama_slave=1 and look on every disconnect अगर still slave
 *	connections exist.
 */
अटल पूर्णांक ax25_check_dama_slave(ax25_dev *ax25_dev)
अणु
	ax25_cb *ax25;
	पूर्णांक res = 0;

	spin_lock(&ax25_list_lock);
	ax25_क्रम_each(ax25, &ax25_list)
		अगर (ax25->ax25_dev == ax25_dev && (ax25->condition & AX25_COND_DAMA_MODE) && ax25->state > AX25_STATE_1) अणु
			res = 1;
			अवरोध;
		पूर्ण
	spin_unlock(&ax25_list_lock);

	वापस res;
पूर्ण

अटल व्योम ax25_dev_dama_on(ax25_dev *ax25_dev)
अणु
	अगर (ax25_dev == शून्य)
		वापस;

	अगर (ax25_dev->dama.slave == 0)
		ax25_kiss_cmd(ax25_dev, 5, 1);

	ax25_dev->dama.slave = 1;
	ax25_ds_set_समयr(ax25_dev);
पूर्ण

व्योम ax25_dev_dama_off(ax25_dev *ax25_dev)
अणु
	अगर (ax25_dev == शून्य)
		वापस;

	अगर (ax25_dev->dama.slave && !ax25_check_dama_slave(ax25_dev)) अणु
		ax25_kiss_cmd(ax25_dev, 5, 0);
		ax25_dev->dama.slave = 0;
		ax25_ds_del_समयr(ax25_dev);
	पूर्ण
पूर्ण

व्योम ax25_dama_on(ax25_cb *ax25)
अणु
	ax25_dev_dama_on(ax25->ax25_dev);
	ax25->condition |= AX25_COND_DAMA_MODE;
पूर्ण

व्योम ax25_dama_off(ax25_cb *ax25)
अणु
	ax25->condition &= ~AX25_COND_DAMA_MODE;
	ax25_dev_dama_off(ax25->ax25_dev);
पूर्ण
