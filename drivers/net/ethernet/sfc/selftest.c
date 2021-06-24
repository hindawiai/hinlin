<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2012 Solarflare Communications Inc.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/pci.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/udp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "efx_common.h"
#समावेश "efx_channels.h"
#समावेश "nic.h"
#समावेश "mcdi_port_common.h"
#समावेश "selftest.h"
#समावेश "workarounds.h"

/* IRQ latency can be enormous because:
 * - All IRQs may be disabled on a CPU क्रम a *दीर्घ* समय by e.g. a
 *   slow serial console or an old IDE driver करोing error recovery
 * - The PREEMPT_RT patches mostly deal with this, but also allow a
 *   tasklet or normal task to be given higher priority than our IRQ
 *   thपढ़ोs
 * Try to aव्योम blaming the hardware क्रम this.
 */
#घोषणा IRQ_TIMEOUT HZ

/*
 * Loopback test packet काष्ठाure
 *
 * The self-test should stress every RSS vector, and unक्रमtunately
 * Falcon only perक्रमms RSS on TCP/UDP packets.
 */
काष्ठा efx_loopback_payload अणु
	काष्ठा ethhdr header;
	काष्ठा iphdr ip;
	काष्ठा udphdr udp;
	__be16 iteration;
	अक्षर msg[64];
पूर्ण __packed;

/* Loopback test source MAC address */
अटल स्थिर u8 payload_source[ETH_ALEN] __aligned(2) = अणु
	0x00, 0x0f, 0x53, 0x1b, 0x1b, 0x1b,
पूर्ण;

अटल स्थिर अक्षर payload_msg[] =
	"Hello world! This is an Efx loopback test in progress!";

/* Interrupt mode names */
अटल स्थिर अचिन्हित पूर्णांक efx_पूर्णांकerrupt_mode_max = EFX_INT_MODE_MAX;
अटल स्थिर अक्षर *स्थिर efx_पूर्णांकerrupt_mode_names[] = अणु
	[EFX_INT_MODE_MSIX]   = "MSI-X",
	[EFX_INT_MODE_MSI]    = "MSI",
	[EFX_INT_MODE_LEGACY] = "legacy",
पूर्ण;
#घोषणा INT_MODE(efx) \
	STRING_TABLE_LOOKUP(efx->पूर्णांकerrupt_mode, efx_पूर्णांकerrupt_mode)

/**
 * काष्ठा efx_loopback_state - persistent state during a loopback selftest
 * @flush:		Drop all packets in efx_loopback_rx_packet
 * @packet_count:	Number of packets being used in this test
 * @skbs:		An array of skbs transmitted
 * @offload_csum:	Checksums are being offloaded
 * @rx_good:		RX good packet count
 * @rx_bad:		RX bad packet count
 * @payload:		Payload used in tests
 */
काष्ठा efx_loopback_state अणु
	bool flush;
	पूर्णांक packet_count;
	काष्ठा sk_buff **skbs;
	bool offload_csum;
	atomic_t rx_good;
	atomic_t rx_bad;
	काष्ठा efx_loopback_payload payload;
पूर्ण;

/* How दीर्घ to रुको क्रम all the packets to arrive (in ms) */
#घोषणा LOOPBACK_TIMEOUT_MS 1000

/**************************************************************************
 *
 * MII, NVRAM and रेजिस्टर tests
 *
 **************************************************************************/

अटल पूर्णांक efx_test_phy_alive(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests)
अणु
	पूर्णांक rc = 0;

	rc = efx_mcdi_phy_test_alive(efx);
	tests->phy_alive = rc ? -1 : 1;

	वापस rc;
पूर्ण

अटल पूर्णांक efx_test_nvram(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests)
अणु
	पूर्णांक rc = 0;

	अगर (efx->type->test_nvram) अणु
		rc = efx->type->test_nvram(efx);
		अगर (rc == -EPERM)
			rc = 0;
		अन्यथा
			tests->nvram = rc ? -1 : 1;
	पूर्ण

	वापस rc;
पूर्ण

/**************************************************************************
 *
 * Interrupt and event queue testing
 *
 **************************************************************************/

/* Test generation and receipt of पूर्णांकerrupts */
अटल पूर्णांक efx_test_पूर्णांकerrupts(काष्ठा efx_nic *efx,
			       काष्ठा efx_self_tests *tests)
अणु
	अचिन्हित दीर्घ समयout, रुको;
	पूर्णांक cpu;
	पूर्णांक rc;

	netअगर_dbg(efx, drv, efx->net_dev, "testing interrupts\n");
	tests->पूर्णांकerrupt = -1;

	rc = efx_nic_irq_test_start(efx);
	अगर (rc == -ENOTSUPP) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "direct interrupt testing not supported\n");
		tests->पूर्णांकerrupt = 0;
		वापस 0;
	पूर्ण

	समयout = jअगरfies + IRQ_TIMEOUT;
	रुको = 1;

	/* Wait क्रम arrival of test पूर्णांकerrupt. */
	netअगर_dbg(efx, drv, efx->net_dev, "waiting for test interrupt\n");
	करो अणु
		schedule_समयout_unपूर्णांकerruptible(रुको);
		cpu = efx_nic_irq_test_irq_cpu(efx);
		अगर (cpu >= 0)
			जाओ success;
		रुको *= 2;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	netअगर_err(efx, drv, efx->net_dev, "timed out waiting for interrupt\n");
	वापस -ETIMEDOUT;

 success:
	netअगर_dbg(efx, drv, efx->net_dev, "%s test interrupt seen on CPU%d\n",
		  INT_MODE(efx), cpu);
	tests->पूर्णांकerrupt = 1;
	वापस 0;
पूर्ण

/* Test generation and receipt of पूर्णांकerrupting events */
अटल पूर्णांक efx_test_eventq_irq(काष्ठा efx_nic *efx,
			       काष्ठा efx_self_tests *tests)
अणु
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक पढ़ो_ptr[EFX_MAX_CHANNELS];
	अचिन्हित दीर्घ napi_ran = 0, dma_pend = 0, पूर्णांक_pend = 0;
	अचिन्हित दीर्घ समयout, रुको;

	BUILD_BUG_ON(EFX_MAX_CHANNELS > BITS_PER_LONG);

	efx_क्रम_each_channel(channel, efx) अणु
		पढ़ो_ptr[channel->channel] = channel->eventq_पढ़ो_ptr;
		set_bit(channel->channel, &dma_pend);
		set_bit(channel->channel, &पूर्णांक_pend);
		efx_nic_event_test_start(channel);
	पूर्ण

	समयout = jअगरfies + IRQ_TIMEOUT;
	रुको = 1;

	/* Wait क्रम arrival of पूर्णांकerrupts.  NAPI processing may or may
	 * not complete in समय, but we can cope in any हाल.
	 */
	करो अणु
		schedule_समयout_unपूर्णांकerruptible(रुको);

		efx_क्रम_each_channel(channel, efx) अणु
			efx_stop_eventq(channel);
			अगर (channel->eventq_पढ़ो_ptr !=
			    पढ़ो_ptr[channel->channel]) अणु
				set_bit(channel->channel, &napi_ran);
				clear_bit(channel->channel, &dma_pend);
				clear_bit(channel->channel, &पूर्णांक_pend);
			पूर्ण अन्यथा अणु
				अगर (efx_nic_event_present(channel))
					clear_bit(channel->channel, &dma_pend);
				अगर (efx_nic_event_test_irq_cpu(channel) >= 0)
					clear_bit(channel->channel, &पूर्णांक_pend);
			पूर्ण
			efx_start_eventq(channel);
		पूर्ण

		रुको *= 2;
	पूर्ण जबतक ((dma_pend || पूर्णांक_pend) && समय_beक्रमe(jअगरfies, समयout));

	efx_क्रम_each_channel(channel, efx) अणु
		bool dma_seen = !test_bit(channel->channel, &dma_pend);
		bool पूर्णांक_seen = !test_bit(channel->channel, &पूर्णांक_pend);

		tests->eventq_dma[channel->channel] = dma_seen ? 1 : -1;
		tests->eventq_पूर्णांक[channel->channel] = पूर्णांक_seen ? 1 : -1;

		अगर (dma_seen && पूर्णांक_seen) अणु
			netअगर_dbg(efx, drv, efx->net_dev,
				  "channel %d event queue passed (with%s NAPI)\n",
				  channel->channel,
				  test_bit(channel->channel, &napi_ran) ?
				  "" : "out");
		पूर्ण अन्यथा अणु
			/* Report failure and whether either पूर्णांकerrupt or DMA
			 * worked
			 */
			netअगर_err(efx, drv, efx->net_dev,
				  "channel %d timed out waiting for event queue\n",
				  channel->channel);
			अगर (पूर्णांक_seen)
				netअगर_err(efx, drv, efx->net_dev,
					  "channel %d saw interrupt "
					  "during event queue test\n",
					  channel->channel);
			अगर (dma_seen)
				netअगर_err(efx, drv, efx->net_dev,
					  "channel %d event was generated, but "
					  "failed to trigger an interrupt\n",
					  channel->channel);
		पूर्ण
	पूर्ण

	वापस (dma_pend || पूर्णांक_pend) ? -ETIMEDOUT : 0;
पूर्ण

अटल पूर्णांक efx_test_phy(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests,
			अचिन्हित flags)
अणु
	पूर्णांक rc;

	mutex_lock(&efx->mac_lock);
	rc = efx_mcdi_phy_run_tests(efx, tests->phy_ext, flags);
	mutex_unlock(&efx->mac_lock);
	अगर (rc == -EPERM)
		rc = 0;
	अन्यथा
		netअगर_info(efx, drv, efx->net_dev,
			   "%s phy selftest\n", rc ? "Failed" : "Passed");

	वापस rc;
पूर्ण

/**************************************************************************
 *
 * Loopback testing
 * NB Only one loopback test can be executing concurrently.
 *
 **************************************************************************/

/* Loopback test RX callback
 * This is called क्रम each received packet during loopback testing.
 */
व्योम efx_loopback_rx_packet(काष्ठा efx_nic *efx,
			    स्थिर अक्षर *buf_ptr, पूर्णांक pkt_len)
अणु
	काष्ठा efx_loopback_state *state = efx->loopback_selftest;
	काष्ठा efx_loopback_payload *received;
	काष्ठा efx_loopback_payload *payload;

	BUG_ON(!buf_ptr);

	/* If we are just flushing, then drop the packet */
	अगर ((state == शून्य) || state->flush)
		वापस;

	payload = &state->payload;

	received = (काष्ठा efx_loopback_payload *) buf_ptr;
	received->ip.saddr = payload->ip.saddr;
	अगर (state->offload_csum)
		received->ip.check = payload->ip.check;

	/* Check that header exists */
	अगर (pkt_len < माप(received->header)) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "saw runt RX packet (length %d) in %s loopback "
			  "test\n", pkt_len, LOOPBACK_MODE(efx));
		जाओ err;
	पूर्ण

	/* Check that the ethernet header exists */
	अगर (स_भेद(&received->header, &payload->header, ETH_HLEN) != 0) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "saw non-loopback RX packet in %s loopback test\n",
			  LOOPBACK_MODE(efx));
		जाओ err;
	पूर्ण

	/* Check packet length */
	अगर (pkt_len != माप(*payload)) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "saw incorrect RX packet length %d (wanted %d) in "
			  "%s loopback test\n", pkt_len, (पूर्णांक)माप(*payload),
			  LOOPBACK_MODE(efx));
		जाओ err;
	पूर्ण

	/* Check that IP header matches */
	अगर (स_भेद(&received->ip, &payload->ip, माप(payload->ip)) != 0) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "saw corrupted IP header in %s loopback test\n",
			  LOOPBACK_MODE(efx));
		जाओ err;
	पूर्ण

	/* Check that msg and padding matches */
	अगर (स_भेद(&received->msg, &payload->msg, माप(received->msg)) != 0) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "saw corrupted RX packet in %s loopback test\n",
			  LOOPBACK_MODE(efx));
		जाओ err;
	पूर्ण

	/* Check that iteration matches */
	अगर (received->iteration != payload->iteration) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "saw RX packet from iteration %d (wanted %d) in "
			  "%s loopback test\n", ntohs(received->iteration),
			  ntohs(payload->iteration), LOOPBACK_MODE(efx));
		जाओ err;
	पूर्ण

	/* Increase correct RX count */
	netअगर_vdbg(efx, drv, efx->net_dev,
		   "got loopback RX in %s loopback test\n", LOOPBACK_MODE(efx));

	atomic_inc(&state->rx_good);
	वापस;

 err:
#अगर_घोषित DEBUG
	अगर (atomic_पढ़ो(&state->rx_bad) == 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "received packet:\n");
		prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 0x10, 1,
			       buf_ptr, pkt_len, 0);
		netअगर_err(efx, drv, efx->net_dev, "expected packet:\n");
		prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 0x10, 1,
			       &state->payload, माप(state->payload), 0);
	पूर्ण
#पूर्ण_अगर
	atomic_inc(&state->rx_bad);
पूर्ण

/* Initialise an efx_selftest_state क्रम a new iteration */
अटल व्योम efx_iterate_state(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_loopback_state *state = efx->loopback_selftest;
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा efx_loopback_payload *payload = &state->payload;

	/* Initialise the layerII header */
	ether_addr_copy((u8 *)&payload->header.h_dest, net_dev->dev_addr);
	ether_addr_copy((u8 *)&payload->header.h_source, payload_source);
	payload->header.h_proto = htons(ETH_P_IP);

	/* saddr set later and used as incrementing count */
	payload->ip.daddr = htonl(INADDR_LOOPBACK);
	payload->ip.ihl = 5;
	payload->ip.check = (__क्रमce __sum16) htons(0xdead);
	payload->ip.tot_len = htons(माप(*payload) - माप(काष्ठा ethhdr));
	payload->ip.version = IPVERSION;
	payload->ip.protocol = IPPROTO_UDP;

	/* Initialise udp header */
	payload->udp.source = 0;
	payload->udp.len = htons(माप(*payload) - माप(काष्ठा ethhdr) -
				 माप(काष्ठा iphdr));
	payload->udp.check = 0;	/* checksum ignored */

	/* Fill out payload */
	payload->iteration = htons(ntohs(payload->iteration) + 1);
	स_नकल(&payload->msg, payload_msg, माप(payload_msg));

	/* Fill out reमुख्यing state members */
	atomic_set(&state->rx_good, 0);
	atomic_set(&state->rx_bad, 0);
	smp_wmb();
पूर्ण

अटल पूर्णांक efx_begin_loopback(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	काष्ठा efx_loopback_state *state = efx->loopback_selftest;
	काष्ठा efx_loopback_payload *payload;
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	netdev_tx_t rc;

	/* Transmit N copies of buffer */
	क्रम (i = 0; i < state->packet_count; i++) अणु
		/* Allocate an skb, holding an extra reference क्रम
		 * transmit completion counting */
		skb = alloc_skb(माप(state->payload), GFP_KERNEL);
		अगर (!skb)
			वापस -ENOMEM;
		state->skbs[i] = skb;
		skb_get(skb);

		/* Copy the payload in, incrementing the source address to
		 * exercise the rss vectors */
		payload = skb_put(skb, माप(state->payload));
		स_नकल(payload, &state->payload, माप(state->payload));
		payload->ip.saddr = htonl(INADDR_LOOPBACK | (i << 2));

		/* Ensure everything we've written is visible to the
		 * पूर्णांकerrupt handler. */
		smp_wmb();

		netअगर_tx_lock_bh(efx->net_dev);
		rc = efx_enqueue_skb(tx_queue, skb);
		netअगर_tx_unlock_bh(efx->net_dev);

		अगर (rc != NETDEV_TX_OK) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "TX queue %d could not transmit packet %d of "
				  "%d in %s loopback test\n", tx_queue->label,
				  i + 1, state->packet_count,
				  LOOPBACK_MODE(efx));

			/* Defer cleaning up the other skbs क्रम the caller */
			kमुक्त_skb(skb);
			वापस -EPIPE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efx_poll_loopback(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_loopback_state *state = efx->loopback_selftest;

	वापस atomic_पढ़ो(&state->rx_good) == state->packet_count;
पूर्ण

अटल पूर्णांक efx_end_loopback(काष्ठा efx_tx_queue *tx_queue,
			    काष्ठा efx_loopback_self_tests *lb_tests)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	काष्ठा efx_loopback_state *state = efx->loopback_selftest;
	काष्ठा sk_buff *skb;
	पूर्णांक tx_करोne = 0, rx_good, rx_bad;
	पूर्णांक i, rc = 0;

	netअगर_tx_lock_bh(efx->net_dev);

	/* Count the number of tx completions, and decrement the refcnt. Any
	 * skbs not alपढ़ोy completed will be मुक्त'd when the queue is flushed */
	क्रम (i = 0; i < state->packet_count; i++) अणु
		skb = state->skbs[i];
		अगर (skb && !skb_shared(skb))
			++tx_करोne;
		dev_kमुक्त_skb(skb);
	पूर्ण

	netअगर_tx_unlock_bh(efx->net_dev);

	/* Check TX completion and received packet counts */
	rx_good = atomic_पढ़ो(&state->rx_good);
	rx_bad = atomic_पढ़ो(&state->rx_bad);
	अगर (tx_करोne != state->packet_count) अणु
		/* Don't मुक्त the skbs; they will be picked up on TX
		 * overflow or channel tearकरोwn.
		 */
		netअगर_err(efx, drv, efx->net_dev,
			  "TX queue %d saw only %d out of an expected %d "
			  "TX completion events in %s loopback test\n",
			  tx_queue->label, tx_करोne, state->packet_count,
			  LOOPBACK_MODE(efx));
		rc = -ETIMEDOUT;
		/* Allow to fall through so we see the RX errors as well */
	पूर्ण

	/* We may always be up to a flush away from our desired packet total */
	अगर (rx_good != state->packet_count) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "TX queue %d saw only %d out of an expected %d "
			  "received packets in %s loopback test\n",
			  tx_queue->label, rx_good, state->packet_count,
			  LOOPBACK_MODE(efx));
		rc = -ETIMEDOUT;
		/* Fall through */
	पूर्ण

	/* Update loopback test काष्ठाure */
	lb_tests->tx_sent[tx_queue->label] += state->packet_count;
	lb_tests->tx_करोne[tx_queue->label] += tx_करोne;
	lb_tests->rx_good += rx_good;
	lb_tests->rx_bad += rx_bad;

	वापस rc;
पूर्ण

अटल पूर्णांक
efx_test_loopback(काष्ठा efx_tx_queue *tx_queue,
		  काष्ठा efx_loopback_self_tests *lb_tests)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	काष्ठा efx_loopback_state *state = efx->loopback_selftest;
	पूर्णांक i, begin_rc, end_rc;

	क्रम (i = 0; i < 3; i++) अणु
		/* Determine how many packets to send */
		state->packet_count = efx->txq_entries / 3;
		state->packet_count = min(1 << (i << 2), state->packet_count);
		state->skbs = kसुस्मृति(state->packet_count,
				      माप(state->skbs[0]), GFP_KERNEL);
		अगर (!state->skbs)
			वापस -ENOMEM;
		state->flush = false;

		netअगर_dbg(efx, drv, efx->net_dev,
			  "TX queue %d (hw %d) testing %s loopback with %d packets\n",
			  tx_queue->label, tx_queue->queue, LOOPBACK_MODE(efx),
			  state->packet_count);

		efx_iterate_state(efx);
		begin_rc = efx_begin_loopback(tx_queue);

		/* This will normally complete very quickly, but be
		 * prepared to रुको much दीर्घer. */
		msleep(1);
		अगर (!efx_poll_loopback(efx)) अणु
			msleep(LOOPBACK_TIMEOUT_MS);
			efx_poll_loopback(efx);
		पूर्ण

		end_rc = efx_end_loopback(tx_queue, lb_tests);
		kमुक्त(state->skbs);

		अगर (begin_rc || end_rc) अणु
			/* Wait a जबतक to ensure there are no packets
			 * भग्नing around after a failure. */
			schedule_समयout_unपूर्णांकerruptible(HZ / 10);
			वापस begin_rc ? begin_rc : end_rc;
		पूर्ण
	पूर्ण

	netअगर_dbg(efx, drv, efx->net_dev,
		  "TX queue %d passed %s loopback test with a burst length "
		  "of %d packets\n", tx_queue->label, LOOPBACK_MODE(efx),
		  state->packet_count);

	वापस 0;
पूर्ण

/* Wait क्रम link up. On Falcon, we would prefer to rely on efx_monitor, but
 * any contention on the mac lock (via e.g. efx_mac_mcast_work) causes it
 * to delay and retry. Thereक्रमe, it's safer to just poll directly. Wait
 * क्रम link up and any faults to dissipate. */
अटल पूर्णांक efx_रुको_क्रम_link(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_link_state *link_state = &efx->link_state;
	पूर्णांक count, link_up_count = 0;
	bool link_up;

	क्रम (count = 0; count < 40; count++) अणु
		schedule_समयout_unपूर्णांकerruptible(HZ / 10);

		अगर (efx->type->monitor != शून्य) अणु
			mutex_lock(&efx->mac_lock);
			efx->type->monitor(efx);
			mutex_unlock(&efx->mac_lock);
		पूर्ण

		mutex_lock(&efx->mac_lock);
		link_up = link_state->up;
		अगर (link_up)
			link_up = !efx->type->check_mac_fault(efx);
		mutex_unlock(&efx->mac_lock);

		अगर (link_up) अणु
			अगर (++link_up_count == 2)
				वापस 0;
		पूर्ण अन्यथा अणु
			link_up_count = 0;
		पूर्ण
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक efx_test_loopbacks(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests,
			      अचिन्हित पूर्णांक loopback_modes)
अणु
	क्रमागत efx_loopback_mode mode;
	काष्ठा efx_loopback_state *state;
	काष्ठा efx_channel *channel =
		efx_get_channel(efx, efx->tx_channel_offset);
	काष्ठा efx_tx_queue *tx_queue;
	पूर्णांक rc = 0;

	/* Set the port loopback_selftest member. From this poपूर्णांक on
	 * all received packets will be dropped. Mark the state as
	 * "flushing" so all inflight packets are dropped */
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	BUG_ON(efx->loopback_selftest);
	state->flush = true;
	efx->loopback_selftest = state;

	/* Test all supported loopback modes */
	क्रम (mode = LOOPBACK_NONE; mode <= LOOPBACK_TEST_MAX; mode++) अणु
		अगर (!(loopback_modes & (1 << mode)))
			जारी;

		/* Move the port पूर्णांकo the specअगरied loopback mode. */
		state->flush = true;
		mutex_lock(&efx->mac_lock);
		efx->loopback_mode = mode;
		rc = __efx_reconfigure_port(efx);
		mutex_unlock(&efx->mac_lock);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "unable to move into %s loopback\n",
				  LOOPBACK_MODE(efx));
			जाओ out;
		पूर्ण

		rc = efx_रुको_क्रम_link(efx);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "loopback %s never came up\n",
				  LOOPBACK_MODE(efx));
			जाओ out;
		पूर्ण

		/* Test all enabled types of TX queue */
		efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
			state->offload_csum = (tx_queue->type &
					       EFX_TXQ_TYPE_OUTER_CSUM);
			rc = efx_test_loopback(tx_queue,
					       &tests->loopback[mode]);
			अगर (rc)
				जाओ out;
		पूर्ण
	पूर्ण

 out:
	/* Remove the flush. The caller will हटाओ the loopback setting */
	state->flush = true;
	efx->loopback_selftest = शून्य;
	wmb();
	kमुक्त(state);

	अगर (rc == -EPERM)
		rc = 0;

	वापस rc;
पूर्ण

/**************************************************************************
 *
 * Entry poपूर्णांक
 *
 *************************************************************************/

पूर्णांक efx_selftest(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests,
		 अचिन्हित flags)
अणु
	क्रमागत efx_loopback_mode loopback_mode = efx->loopback_mode;
	पूर्णांक phy_mode = efx->phy_mode;
	पूर्णांक rc_test = 0, rc_reset, rc;

	efx_selftest_async_cancel(efx);

	/* Online (i.e. non-disruptive) testing
	 * This checks पूर्णांकerrupt generation, event delivery and PHY presence. */

	rc = efx_test_phy_alive(efx, tests);
	अगर (rc && !rc_test)
		rc_test = rc;

	rc = efx_test_nvram(efx, tests);
	अगर (rc && !rc_test)
		rc_test = rc;

	rc = efx_test_पूर्णांकerrupts(efx, tests);
	अगर (rc && !rc_test)
		rc_test = rc;

	rc = efx_test_eventq_irq(efx, tests);
	अगर (rc && !rc_test)
		rc_test = rc;

	अगर (rc_test)
		वापस rc_test;

	अगर (!(flags & ETH_TEST_FL_OFFLINE))
		वापस efx_test_phy(efx, tests, flags);

	/* Offline (i.e. disruptive) testing
	 * This checks MAC and PHY loopback on the specअगरied port. */

	/* Detach the device so the kernel करोesn't transmit during the
	 * loopback test and the watchकरोg समयout करोesn't fire.
	 */
	efx_device_detach_sync(efx);

	अगर (efx->type->test_chip) अणु
		rc_reset = efx->type->test_chip(efx, tests);
		अगर (rc_reset) अणु
			netअगर_err(efx, hw, efx->net_dev,
				  "Unable to recover from chip test\n");
			efx_schedule_reset(efx, RESET_TYPE_DISABLE);
			वापस rc_reset;
		पूर्ण

		अगर ((tests->memory < 0 || tests->रेजिस्टरs < 0) && !rc_test)
			rc_test = -EIO;
	पूर्ण

	/* Ensure that the phy is घातered and out of loopback
	 * क्रम the bist and loopback tests */
	mutex_lock(&efx->mac_lock);
	efx->phy_mode &= ~PHY_MODE_LOW_POWER;
	efx->loopback_mode = LOOPBACK_NONE;
	__efx_reconfigure_port(efx);
	mutex_unlock(&efx->mac_lock);

	rc = efx_test_phy(efx, tests, flags);
	अगर (rc && !rc_test)
		rc_test = rc;

	rc = efx_test_loopbacks(efx, tests, efx->loopback_modes);
	अगर (rc && !rc_test)
		rc_test = rc;

	/* restore the PHY to the previous state */
	mutex_lock(&efx->mac_lock);
	efx->phy_mode = phy_mode;
	efx->loopback_mode = loopback_mode;
	__efx_reconfigure_port(efx);
	mutex_unlock(&efx->mac_lock);

	efx_device_attach_अगर_not_resetting(efx);

	वापस rc_test;
पूर्ण

व्योम efx_selftest_async_start(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx)
		efx_nic_event_test_start(channel);
	schedule_delayed_work(&efx->selftest_work, IRQ_TIMEOUT);
पूर्ण

व्योम efx_selftest_async_cancel(काष्ठा efx_nic *efx)
अणु
	cancel_delayed_work_sync(&efx->selftest_work);
पूर्ण

अटल व्योम efx_selftest_async_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा efx_nic *efx = container_of(data, काष्ठा efx_nic,
					   selftest_work.work);
	काष्ठा efx_channel *channel;
	पूर्णांक cpu;

	efx_क्रम_each_channel(channel, efx) अणु
		cpu = efx_nic_event_test_irq_cpu(channel);
		अगर (cpu < 0)
			netअगर_err(efx, अगरup, efx->net_dev,
				  "channel %d failed to trigger an interrupt\n",
				  channel->channel);
		अन्यथा
			netअगर_dbg(efx, अगरup, efx->net_dev,
				  "channel %d triggered interrupt on CPU %d\n",
				  channel->channel, cpu);
	पूर्ण
पूर्ण

व्योम efx_selftest_async_init(काष्ठा efx_nic *efx)
अणु
	INIT_DELAYED_WORK(&efx->selftest_work, efx_selftest_async_work);
पूर्ण
