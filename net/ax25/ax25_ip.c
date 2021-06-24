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
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>	/* For TIOCINQ/OUTQ */
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sysctl.h>
#समावेश <net/ip.h>
#समावेश <net/arp.h>

/*
 *	IP over AX.25 encapsulation.
 */

/*
 *	Shove an AX.25 UI header on an IP packet and handle ARP
 */

#अगर_घोषित CONFIG_INET

अटल पूर्णांक ax25_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			    अचिन्हित लघु type, स्थिर व्योम *daddr,
			    स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *buff;

	/* they someबार come back to us... */
	अगर (type == ETH_P_AX25)
		वापस 0;

	/* header is an AX.25 UI frame from us to them */
	buff = skb_push(skb, AX25_HEADER_LEN);
	*buff++ = 0x00;	/* KISS DATA */

	अगर (daddr != शून्य)
		स_नकल(buff, daddr, dev->addr_len);	/* Address specअगरied */

	buff[6] &= ~AX25_CBIT;
	buff[6] &= ~AX25_EBIT;
	buff[6] |= AX25_SSSID_SPARE;
	buff    += AX25_ADDR_LEN;

	अगर (saddr != शून्य)
		स_नकल(buff, saddr, dev->addr_len);
	अन्यथा
		स_नकल(buff, dev->dev_addr, dev->addr_len);

	buff[6] &= ~AX25_CBIT;
	buff[6] |= AX25_EBIT;
	buff[6] |= AX25_SSSID_SPARE;
	buff    += AX25_ADDR_LEN;

	*buff++  = AX25_UI;	/* UI */

	/* Append a suitable AX.25 PID */
	चयन (type) अणु
	हाल ETH_P_IP:
		*buff++ = AX25_P_IP;
		अवरोध;
	हाल ETH_P_ARP:
		*buff++ = AX25_P_ARP;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "AX.25: ax25_hard_header - wrong protocol type 0x%2.2x\n", type);
		*buff++ = 0;
		अवरोध;
	पूर्ण

	अगर (daddr != शून्य)
		वापस AX25_HEADER_LEN;

	वापस -AX25_HEADER_LEN;	/* Unfinished header */
पूर्ण

netdev_tx_t ax25_ip_xmit(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *ourskb;
	अचिन्हित अक्षर *bp  = skb->data;
	ax25_route *route;
	काष्ठा net_device *dev = शून्य;
	ax25_address *src, *dst;
	ax25_digi *digipeat = शून्य;
	ax25_dev *ax25_dev;
	ax25_cb *ax25;
	अक्षर ip_mode = ' ';

	dst = (ax25_address *)(bp + 1);
	src = (ax25_address *)(bp + 8);

	ax25_route_lock_use();
	route = ax25_get_route(dst, शून्य);
	अगर (route) अणु
		digipeat = route->digipeat;
		dev = route->dev;
		ip_mode = route->ip_mode;
	पूर्ण

	अगर (dev == शून्य)
		dev = skb->dev;

	अगर ((ax25_dev = ax25_dev_ax25dev(dev)) == शून्य) अणु
		kमुक्त_skb(skb);
		जाओ put;
	पूर्ण

	अगर (bp[16] == AX25_P_IP) अणु
		अगर (ip_mode == 'V' || (ip_mode == ' ' && ax25_dev->values[AX25_VALUES_IPDEFMODE])) अणु
			/*
			 *	We copy the buffer and release the original thereby
			 *	keeping it straight
			 *
			 *	Note: we report 1 back so the caller will
			 *	not feed the frame direct to the physical device
			 *	We करोn't want that to happen. (It won't be upset
			 *	as we have pulled the frame from the queue by
			 *	मुक्तing it).
			 *
			 *	NB: TCP modअगरies buffers that are still
			 *	on a device queue, thus we use skb_copy()
			 *      instead of using skb_clone() unless this
			 *	माला_लो fixed.
			 */

			ax25_address src_c;
			ax25_address dst_c;

			अगर ((ourskb = skb_copy(skb, GFP_ATOMIC)) == शून्य) अणु
				kमुक्त_skb(skb);
				जाओ put;
			पूर्ण

			अगर (skb->sk != शून्य)
				skb_set_owner_w(ourskb, skb->sk);

			kमुक्त_skb(skb);
			/* dl9sau: bugfix
			 * after kमुक्त_skb(), dst and src which were poपूर्णांकer
			 * to bp which is part of skb->data would not be valid
			 * anymore hope that after skb_pull(ourskb, ..) our
			 * dsc_c and src_c will not become invalid
			 */
			bp  = ourskb->data;
			dst_c = *(ax25_address *)(bp + 1);
			src_c = *(ax25_address *)(bp + 8);

			skb_pull(ourskb, AX25_HEADER_LEN - 1);	/* Keep PID */
			skb_reset_network_header(ourskb);

			ax25=ax25_send_frame(
			    ourskb,
			    ax25_dev->values[AX25_VALUES_PACLEN],
			    &src_c,
			    &dst_c, digipeat, dev);
			अगर (ax25) अणु
				ax25_cb_put(ax25);
			पूर्ण
			जाओ put;
		पूर्ण
	पूर्ण

	bp[7]  &= ~AX25_CBIT;
	bp[7]  &= ~AX25_EBIT;
	bp[7]  |= AX25_SSSID_SPARE;

	bp[14] &= ~AX25_CBIT;
	bp[14] |= AX25_EBIT;
	bp[14] |= AX25_SSSID_SPARE;

	skb_pull(skb, AX25_KISS_HEADER_LEN);

	अगर (digipeat != शून्य) अणु
		अगर ((ourskb = ax25_rt_build_path(skb, src, dst, route->digipeat)) == शून्य) अणु
			kमुक्त_skb(skb);
			जाओ put;
		पूर्ण

		skb = ourskb;
	पूर्ण

	ax25_queue_xmit(skb, dev);

put:

	ax25_route_lock_unuse();
	वापस NETDEV_TX_OK;
पूर्ण

#अन्यथा	/* INET */

अटल पूर्णांक ax25_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			    अचिन्हित लघु type, स्थिर व्योम *daddr,
			    स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	वापस -AX25_HEADER_LEN;
पूर्ण

netdev_tx_t ax25_ip_xmit(काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण
#पूर्ण_अगर

अटल bool ax25_validate_header(स्थिर अक्षर *header, अचिन्हित पूर्णांक len)
अणु
	ax25_digi digi;

	अगर (!len)
		वापस false;

	अगर (header[0])
		वापस true;

	वापस ax25_addr_parse(header + 1, len - 1, शून्य, शून्य, &digi, शून्य,
			       शून्य);
पूर्ण

स्थिर काष्ठा header_ops ax25_header_ops = अणु
	.create = ax25_hard_header,
	.validate = ax25_validate_header,
पूर्ण;

EXPORT_SYMBOL(ax25_header_ops);
EXPORT_SYMBOL(ax25_ip_xmit);
