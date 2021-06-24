<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/slab.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/skbuff.h>

#समावेश "network.h"
#समावेश "hardware.h"
#समावेश "main.h"
#समावेश "tty.h"

#घोषणा MAX_ASSOCIATED_TTYS 2

#घोषणा SC_RCV_BITS     (SC_RCV_B7_1|SC_RCV_B7_0|SC_RCV_ODDP|SC_RCV_EVNP)

काष्ठा ipw_network अणु
	/* Hardware context, used क्रम calls to hardware layer. */
	काष्ठा ipw_hardware *hardware;
	/* Context क्रम kernel 'generic_ppp' functionality */
	काष्ठा ppp_channel *ppp_channel;
	/* tty context connected with IPW console */
	काष्ठा ipw_tty *associated_ttys[NO_OF_IPW_CHANNELS][MAX_ASSOCIATED_TTYS];
	/* True अगर ppp needs waking up once we're पढ़ोy to xmit */
	पूर्णांक ppp_blocked;
	/* Number of packets queued up in hardware module. */
	पूर्णांक outgoing_packets_queued;
	/* Spinlock to aव्योम पूर्णांकerrupts during shutकरोwn */
	spinlock_t lock;
	काष्ठा mutex बंद_lock;

	/* PPP ioctl data, not actually used anywere */
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक rbits;
	u32 xaccm[8];
	u32 raccm;
	पूर्णांक mru;

	पूर्णांक shutting_करोwn;
	अचिन्हित पूर्णांक ras_control_lines;

	काष्ठा work_काष्ठा work_go_online;
	काष्ठा work_काष्ठा work_go_offline;
पूर्ण;

अटल व्योम notअगरy_packet_sent(व्योम *callback_data, अचिन्हित पूर्णांक packet_length)
अणु
	काष्ठा ipw_network *network = callback_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&network->lock, flags);
	network->outgoing_packets_queued--;
	अगर (network->ppp_channel != शून्य) अणु
		अगर (network->ppp_blocked) अणु
			network->ppp_blocked = 0;
			spin_unlock_irqrestore(&network->lock, flags);
			ppp_output_wakeup(network->ppp_channel);
			अगर (ipwireless_debug)
				prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME
				       ": ppp unblocked\n");
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&network->lock, flags);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&network->lock, flags);
पूर्ण

/*
 * Called by the ppp प्रणाली when it has a packet to send to the hardware.
 */
अटल पूर्णांक ipwireless_ppp_start_xmit(काष्ठा ppp_channel *ppp_channel,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा ipw_network *network = ppp_channel->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&network->lock, flags);
	अगर (network->outgoing_packets_queued < ipwireless_out_queue) अणु
		अचिन्हित अक्षर *buf;
		अटल अचिन्हित अक्षर header[] = अणु
			PPP_ALLSTATIONS, /* 0xff */
			PPP_UI,		 /* 0x03 */
		पूर्ण;
		पूर्णांक ret;

		network->outgoing_packets_queued++;
		spin_unlock_irqrestore(&network->lock, flags);

		/*
		 * If we have the requested amount of headroom in the skb we
		 * were handed, then we can add the header efficiently.
		 */
		अगर (skb_headroom(skb) >= 2) अणु
			स_नकल(skb_push(skb, 2), header, 2);
			ret = ipwireless_send_packet(network->hardware,
					       IPW_CHANNEL_RAS, skb->data,
					       skb->len,
					       notअगरy_packet_sent,
					       network);
			अगर (ret < 0) अणु
				skb_pull(skb, 2);
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Otherwise (rarely) we करो it inefficiently. */
			buf = kदो_स्मृति(skb->len + 2, GFP_ATOMIC);
			अगर (!buf)
				वापस 0;
			स_नकल(buf + 2, skb->data, skb->len);
			स_नकल(buf, header, 2);
			ret = ipwireless_send_packet(network->hardware,
					       IPW_CHANNEL_RAS, buf,
					       skb->len + 2,
					       notअगरy_packet_sent,
					       network);
			kमुक्त(buf);
			अगर (ret < 0)
				वापस 0;
		पूर्ण
		kमुक्त_skb(skb);
		वापस 1;
	पूर्ण अन्यथा अणु
		/*
		 * Otherwise reject the packet, and flag that the ppp प्रणाली
		 * needs to be unblocked once we are पढ़ोy to send.
		 */
		network->ppp_blocked = 1;
		spin_unlock_irqrestore(&network->lock, flags);
		अगर (ipwireless_debug)
			prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME ": ppp blocked\n");
		वापस 0;
	पूर्ण
पूर्ण

/* Handle an ioctl call that has come in via ppp. (copy of ppp_async_ioctl() */
अटल पूर्णांक ipwireless_ppp_ioctl(काष्ठा ppp_channel *ppp_channel,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ipw_network *network = ppp_channel->निजी;
	पूर्णांक err, val;
	u32 accm[8];
	पूर्णांक __user *user_arg = (पूर्णांक __user *) arg;

	err = -EFAULT;
	चयन (cmd) अणु
	हाल PPPIOCGFLAGS:
		val = network->flags | network->rbits;
		अगर (put_user(val, user_arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSFLAGS:
		अगर (get_user(val, user_arg))
			अवरोध;
		network->flags = val & ~SC_RCV_BITS;
		network->rbits = val & SC_RCV_BITS;
		err = 0;
		अवरोध;

	हाल PPPIOCGASYNCMAP:
		अगर (put_user(network->xaccm[0], user_arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSASYNCMAP:
		अगर (get_user(network->xaccm[0], user_arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGRASYNCMAP:
		अगर (put_user(network->raccm, user_arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSRASYNCMAP:
		अगर (get_user(network->raccm, user_arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGXASYNCMAP:
		अगर (copy_to_user((व्योम __user *) arg, network->xaccm,
					माप(network->xaccm)))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSXASYNCMAP:
		अगर (copy_from_user(accm, (व्योम __user *) arg, माप(accm)))
			अवरोध;
		accm[2] &= ~0x40000000U;	/* can't escape 0x5e */
		accm[3] |= 0x60000000U;	/* must escape 0x7d, 0x7e */
		स_नकल(network->xaccm, accm, माप(network->xaccm));
		err = 0;
		अवरोध;

	हाल PPPIOCGMRU:
		अगर (put_user(network->mru, user_arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSMRU:
		अगर (get_user(val, user_arg))
			अवरोध;
		अगर (val < PPP_MRU)
			val = PPP_MRU;
		network->mru = val;
		err = 0;
		अवरोध;

	शेष:
		err = -ENOTTY;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ppp_channel_ops ipwireless_ppp_channel_ops = अणु
	.start_xmit = ipwireless_ppp_start_xmit,
	.ioctl      = ipwireless_ppp_ioctl
पूर्ण;

अटल व्योम करो_go_online(काष्ठा work_काष्ठा *work_go_online)
अणु
	काष्ठा ipw_network *network =
		container_of(work_go_online, काष्ठा ipw_network,
				work_go_online);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&network->lock, flags);
	अगर (!network->ppp_channel) अणु
		काष्ठा ppp_channel *channel;

		spin_unlock_irqrestore(&network->lock, flags);
		channel = kzalloc(माप(काष्ठा ppp_channel), GFP_KERNEL);
		अगर (!channel) अणु
			prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
					": unable to allocate PPP channel\n");
			वापस;
		पूर्ण
		channel->निजी = network;
		channel->mtu = 16384;	/* Wild guess */
		channel->hdrlen = 2;
		channel->ops = &ipwireless_ppp_channel_ops;

		network->flags = 0;
		network->rbits = 0;
		network->mru = PPP_MRU;
		स_रखो(network->xaccm, 0, माप(network->xaccm));
		network->xaccm[0] = ~0U;
		network->xaccm[3] = 0x60000000U;
		network->raccm = ~0U;
		अगर (ppp_रेजिस्टर_channel(channel) < 0) अणु
			prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
					": unable to register PPP channel\n");
			kमुक्त(channel);
			वापस;
		पूर्ण
		spin_lock_irqsave(&network->lock, flags);
		network->ppp_channel = channel;
	पूर्ण
	spin_unlock_irqrestore(&network->lock, flags);
पूर्ण

अटल व्योम करो_go_offline(काष्ठा work_काष्ठा *work_go_offline)
अणु
	काष्ठा ipw_network *network =
		container_of(work_go_offline, काष्ठा ipw_network,
				work_go_offline);
	अचिन्हित दीर्घ flags;

	mutex_lock(&network->बंद_lock);
	spin_lock_irqsave(&network->lock, flags);
	अगर (network->ppp_channel != शून्य) अणु
		काष्ठा ppp_channel *channel = network->ppp_channel;

		network->ppp_channel = शून्य;
		spin_unlock_irqrestore(&network->lock, flags);
		mutex_unlock(&network->बंद_lock);
		ppp_unरेजिस्टर_channel(channel);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&network->lock, flags);
		mutex_unlock(&network->बंद_lock);
	पूर्ण
पूर्ण

व्योम ipwireless_network_notअगरy_control_line_change(काष्ठा ipw_network *network,
						   अचिन्हित पूर्णांक channel_idx,
						   अचिन्हित पूर्णांक control_lines,
						   अचिन्हित पूर्णांक changed_mask)
अणु
	पूर्णांक i;

	अगर (channel_idx == IPW_CHANNEL_RAS)
		network->ras_control_lines = control_lines;

	क्रम (i = 0; i < MAX_ASSOCIATED_TTYS; i++) अणु
		काष्ठा ipw_tty *tty =
			network->associated_ttys[channel_idx][i];

		/*
		 * If it's associated with a tty (other than the RAS channel
		 * when we're online), then send the data to that tty.  The RAS
		 * channel's data is handled above - it always goes through
		 * ppp_generic.
		 */
		अगर (tty)
			ipwireless_tty_notअगरy_control_line_change(tty,
								  channel_idx,
								  control_lines,
								  changed_mask);
	पूर्ण
पूर्ण

/*
 * Some versions of firmware stuff packets with 0xff 0x03 (PPP: ALLSTATIONS, UI)
 * bytes, which are required on sent packet, but not always present on received
 * packets
 */
अटल काष्ठा sk_buff *ipw_packet_received_skb(अचिन्हित अक्षर *data,
					       अचिन्हित पूर्णांक length)
अणु
	काष्ठा sk_buff *skb;

	अगर (length > 2 && data[0] == PPP_ALLSTATIONS && data[1] == PPP_UI) अणु
		length -= 2;
		data += 2;
	पूर्ण

	skb = dev_alloc_skb(length + 4);
	अगर (skb == शून्य)
		वापस शून्य;
	skb_reserve(skb, 2);
	skb_put_data(skb, data, length);

	वापस skb;
पूर्ण

व्योम ipwireless_network_packet_received(काष्ठा ipw_network *network,
					अचिन्हित पूर्णांक channel_idx,
					अचिन्हित अक्षर *data,
					अचिन्हित पूर्णांक length)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < MAX_ASSOCIATED_TTYS; i++) अणु
		काष्ठा ipw_tty *tty = network->associated_ttys[channel_idx][i];

		अगर (!tty)
			जारी;

		/*
		 * If it's associated with a tty (other than the RAS channel
		 * when we're online), then send the data to that tty.  The RAS
		 * channel's data is handled above - it always goes through
		 * ppp_generic.
		 */
		अगर (channel_idx == IPW_CHANNEL_RAS
				&& (network->ras_control_lines &
					IPW_CONTROL_LINE_DCD) != 0
				&& ipwireless_tty_is_modem(tty)) अणु
			/*
			 * If data came in on the RAS channel and this tty is
			 * the modem tty, and we are online, then we send it to
			 * the PPP layer.
			 */
			mutex_lock(&network->बंद_lock);
			spin_lock_irqsave(&network->lock, flags);
			अगर (network->ppp_channel != शून्य) अणु
				काष्ठा sk_buff *skb;

				spin_unlock_irqrestore(&network->lock,
						flags);

				/* Send the data to the ppp_generic module. */
				skb = ipw_packet_received_skb(data, length);
				अगर (skb)
					ppp_input(network->ppp_channel, skb);
			पूर्ण अन्यथा
				spin_unlock_irqrestore(&network->lock,
						flags);
			mutex_unlock(&network->बंद_lock);
		पूर्ण
		/* Otherwise we send it out the tty. */
		अन्यथा
			ipwireless_tty_received(tty, data, length);
	पूर्ण
पूर्ण

काष्ठा ipw_network *ipwireless_network_create(काष्ठा ipw_hardware *hw)
अणु
	काष्ठा ipw_network *network =
		kzalloc(माप(काष्ठा ipw_network), GFP_KERNEL);

	अगर (!network)
		वापस शून्य;

	spin_lock_init(&network->lock);
	mutex_init(&network->बंद_lock);

	network->hardware = hw;

	INIT_WORK(&network->work_go_online, करो_go_online);
	INIT_WORK(&network->work_go_offline, करो_go_offline);

	ipwireless_associate_network(hw, network);

	वापस network;
पूर्ण

व्योम ipwireless_network_मुक्त(काष्ठा ipw_network *network)
अणु
	network->shutting_करोwn = 1;

	ipwireless_ppp_बंद(network);
	flush_work(&network->work_go_online);
	flush_work(&network->work_go_offline);

	ipwireless_stop_पूर्णांकerrupts(network->hardware);
	ipwireless_associate_network(network->hardware, शून्य);

	kमुक्त(network);
पूर्ण

व्योम ipwireless_associate_network_tty(काष्ठा ipw_network *network,
				      अचिन्हित पूर्णांक channel_idx,
				      काष्ठा ipw_tty *tty)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_ASSOCIATED_TTYS; i++)
		अगर (network->associated_ttys[channel_idx][i] == शून्य) अणु
			network->associated_ttys[channel_idx][i] = tty;
			अवरोध;
		पूर्ण
पूर्ण

व्योम ipwireless_disassociate_network_ttys(काष्ठा ipw_network *network,
					  अचिन्हित पूर्णांक channel_idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_ASSOCIATED_TTYS; i++)
		network->associated_ttys[channel_idx][i] = शून्य;
पूर्ण

व्योम ipwireless_ppp_खोलो(काष्ठा ipw_network *network)
अणु
	अगर (ipwireless_debug)
		prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME ": online\n");
	schedule_work(&network->work_go_online);
पूर्ण

व्योम ipwireless_ppp_बंद(काष्ठा ipw_network *network)
अणु
	/* Disconnect from the wireless network. */
	अगर (ipwireless_debug)
		prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME ": offline\n");
	schedule_work(&network->work_go_offline);
पूर्ण

पूर्णांक ipwireless_ppp_channel_index(काष्ठा ipw_network *network)
अणु
	पूर्णांक ret = -1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&network->lock, flags);
	अगर (network->ppp_channel != शून्य)
		ret = ppp_channel_index(network->ppp_channel);
	spin_unlock_irqrestore(&network->lock, flags);

	वापस ret;
पूर्ण

पूर्णांक ipwireless_ppp_unit_number(काष्ठा ipw_network *network)
अणु
	पूर्णांक ret = -1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&network->lock, flags);
	अगर (network->ppp_channel != शून्य)
		ret = ppp_unit_number(network->ppp_channel);
	spin_unlock_irqrestore(&network->lock, flags);

	वापस ret;
पूर्ण

पूर्णांक ipwireless_ppp_mru(स्थिर काष्ठा ipw_network *network)
अणु
	वापस network->mru;
पूर्ण
