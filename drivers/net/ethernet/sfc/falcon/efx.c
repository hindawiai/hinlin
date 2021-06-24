<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2005-2013 Solarflare Communications Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/in.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/topology.h>
#समावेश <linux/gfp.h>
#समावेश <linux/aer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "nic.h"
#समावेश "selftest.h"

#समावेश "workarounds.h"

/**************************************************************************
 *
 * Type name strings
 *
 **************************************************************************
 */

/* Loopback mode names (see LOOPBACK_MODE()) */
स्थिर अचिन्हित पूर्णांक ef4_loopback_mode_max = LOOPBACK_MAX;
स्थिर अक्षर *स्थिर ef4_loopback_mode_names[] = अणु
	[LOOPBACK_NONE]		= "NONE",
	[LOOPBACK_DATA]		= "DATAPATH",
	[LOOPBACK_GMAC]		= "GMAC",
	[LOOPBACK_XGMII]	= "XGMII",
	[LOOPBACK_XGXS]		= "XGXS",
	[LOOPBACK_XAUI]		= "XAUI",
	[LOOPBACK_GMII]		= "GMII",
	[LOOPBACK_SGMII]	= "SGMII",
	[LOOPBACK_XGBR]		= "XGBR",
	[LOOPBACK_XFI]		= "XFI",
	[LOOPBACK_XAUI_FAR]	= "XAUI_FAR",
	[LOOPBACK_GMII_FAR]	= "GMII_FAR",
	[LOOPBACK_SGMII_FAR]	= "SGMII_FAR",
	[LOOPBACK_XFI_FAR]	= "XFI_FAR",
	[LOOPBACK_GPHY]		= "GPHY",
	[LOOPBACK_PHYXS]	= "PHYXS",
	[LOOPBACK_PCS]		= "PCS",
	[LOOPBACK_PMAPMD]	= "PMA/PMD",
	[LOOPBACK_XPORT]	= "XPORT",
	[LOOPBACK_XGMII_WS]	= "XGMII_WS",
	[LOOPBACK_XAUI_WS]	= "XAUI_WS",
	[LOOPBACK_XAUI_WS_FAR]  = "XAUI_WS_FAR",
	[LOOPBACK_XAUI_WS_NEAR] = "XAUI_WS_NEAR",
	[LOOPBACK_GMII_WS]	= "GMII_WS",
	[LOOPBACK_XFI_WS]	= "XFI_WS",
	[LOOPBACK_XFI_WS_FAR]	= "XFI_WS_FAR",
	[LOOPBACK_PHYXS_WS]	= "PHYXS_WS",
पूर्ण;

स्थिर अचिन्हित पूर्णांक ef4_reset_type_max = RESET_TYPE_MAX;
स्थिर अक्षर *स्थिर ef4_reset_type_names[] = अणु
	[RESET_TYPE_INVISIBLE]          = "INVISIBLE",
	[RESET_TYPE_ALL]                = "ALL",
	[RESET_TYPE_RECOVER_OR_ALL]     = "RECOVER_OR_ALL",
	[RESET_TYPE_WORLD]              = "WORLD",
	[RESET_TYPE_RECOVER_OR_DISABLE] = "RECOVER_OR_DISABLE",
	[RESET_TYPE_DATAPATH]           = "DATAPATH",
	[RESET_TYPE_DISABLE]            = "DISABLE",
	[RESET_TYPE_TX_WATCHDOG]        = "TX_WATCHDOG",
	[RESET_TYPE_INT_ERROR]          = "INT_ERROR",
	[RESET_TYPE_RX_RECOVERY]        = "RX_RECOVERY",
	[RESET_TYPE_DMA_ERROR]          = "DMA_ERROR",
	[RESET_TYPE_TX_SKIP]            = "TX_SKIP",
पूर्ण;

/* Reset workqueue. If any NIC has a hardware failure then a reset will be
 * queued onto this work queue. This is not a per-nic work queue, because
 * ef4_reset_work() acquires the rtnl lock, so resets are naturally serialised.
 */
अटल काष्ठा workqueue_काष्ठा *reset_workqueue;

/* How often and how many बार to poll क्रम a reset जबतक रुकोing क्रम a
 * BIST that another function started to complete.
 */
#घोषणा BIST_WAIT_DELAY_MS	100
#घोषणा BIST_WAIT_DELAY_COUNT	100

/**************************************************************************
 *
 * Configurable values
 *
 *************************************************************************/

/*
 * Use separate channels क्रम TX and RX events
 *
 * Set this to 1 to use separate channels क्रम TX and RX. It allows us
 * to control पूर्णांकerrupt affinity separately क्रम TX and RX.
 *
 * This is only used in MSI-X पूर्णांकerrupt mode
 */
bool ef4_separate_tx_channels;
module_param(ef4_separate_tx_channels, bool, 0444);
MODULE_PARM_DESC(ef4_separate_tx_channels,
		 "Use separate channels for TX and RX");

/* This is the weight asचिन्हित to each of the (per-channel) भव
 * NAPI devices.
 */
अटल पूर्णांक napi_weight = 64;

/* This is the समय (in jअगरfies) between invocations of the hardware
 * monitor.
 * On Falcon-based NICs, this will:
 * - Check the on-board hardware monitor;
 * - Poll the link state and reconfigure the hardware as necessary.
 * On Siena-based NICs क्रम घातer प्रणालीs with EEH support, this will give EEH a
 * chance to start.
 */
अटल अचिन्हित पूर्णांक ef4_monitor_पूर्णांकerval = 1 * HZ;

/* Initial पूर्णांकerrupt moderation settings.  They can be modअगरied after
 * module load with ethtool.
 *
 * The शेष क्रम RX should strike a balance between increasing the
 * round-trip latency and reducing overhead.
 */
अटल अचिन्हित पूर्णांक rx_irq_mod_usec = 60;

/* Initial पूर्णांकerrupt moderation settings.  They can be modअगरied after
 * module load with ethtool.
 *
 * This शेष is chosen to ensure that a 10G link करोes not go idle
 * जबतक a TX queue is stopped after it has become full.  A queue is
 * restarted when it drops below half full.  The समय this takes (assuming
 * worst हाल 3 descriptors per packet and 1024 descriptors) is
 *   512 / 3 * 1.2 = 205 usec.
 */
अटल अचिन्हित पूर्णांक tx_irq_mod_usec = 150;

/* This is the first पूर्णांकerrupt mode to try out of:
 * 0 => MSI-X
 * 1 => MSI
 * 2 => legacy
 */
अटल अचिन्हित पूर्णांक पूर्णांकerrupt_mode;

/* This is the requested number of CPUs to use क्रम Receive-Side Scaling (RSS),
 * i.e. the number of CPUs among which we may distribute simultaneous
 * पूर्णांकerrupt handling.
 *
 * Cards without MSI-X will only target one CPU via legacy or MSI पूर्णांकerrupt.
 * The शेष (0) means to assign an पूर्णांकerrupt to each core.
 */
अटल अचिन्हित पूर्णांक rss_cpus;
module_param(rss_cpus, uपूर्णांक, 0444);
MODULE_PARM_DESC(rss_cpus, "Number of CPUs to use for Receive-Side Scaling");

अटल bool phy_flash_cfg;
module_param(phy_flash_cfg, bool, 0644);
MODULE_PARM_DESC(phy_flash_cfg, "Set PHYs into reflash mode initially");

अटल अचिन्हित irq_adapt_low_thresh = 8000;
module_param(irq_adapt_low_thresh, uपूर्णांक, 0644);
MODULE_PARM_DESC(irq_adapt_low_thresh,
		 "Threshold score for reducing IRQ moderation");

अटल अचिन्हित irq_adapt_high_thresh = 16000;
module_param(irq_adapt_high_thresh, uपूर्णांक, 0644);
MODULE_PARM_DESC(irq_adapt_high_thresh,
		 "Threshold score for increasing IRQ moderation");

अटल अचिन्हित debug = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
			 NETIF_MSG_LINK | NETIF_MSG_IFDOWN |
			 NETIF_MSG_IFUP | NETIF_MSG_RX_ERR |
			 NETIF_MSG_TX_ERR | NETIF_MSG_HW);
module_param(debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "Bitmapped debugging message enable value");

/**************************************************************************
 *
 * Utility functions and prototypes
 *
 *************************************************************************/

अटल पूर्णांक ef4_soft_enable_पूर्णांकerrupts(काष्ठा ef4_nic *efx);
अटल व्योम ef4_soft_disable_पूर्णांकerrupts(काष्ठा ef4_nic *efx);
अटल व्योम ef4_हटाओ_channel(काष्ठा ef4_channel *channel);
अटल व्योम ef4_हटाओ_channels(काष्ठा ef4_nic *efx);
अटल स्थिर काष्ठा ef4_channel_type ef4_शेष_channel_type;
अटल व्योम ef4_हटाओ_port(काष्ठा ef4_nic *efx);
अटल व्योम ef4_init_napi_channel(काष्ठा ef4_channel *channel);
अटल व्योम ef4_fini_napi(काष्ठा ef4_nic *efx);
अटल व्योम ef4_fini_napi_channel(काष्ठा ef4_channel *channel);
अटल व्योम ef4_fini_काष्ठा(काष्ठा ef4_nic *efx);
अटल व्योम ef4_start_all(काष्ठा ef4_nic *efx);
अटल व्योम ef4_stop_all(काष्ठा ef4_nic *efx);

#घोषणा EF4_ASSERT_RESET_SERIALISED(efx)		\
	करो अणु						\
		अगर ((efx->state == STATE_READY) ||	\
		    (efx->state == STATE_RECOVERY) ||	\
		    (efx->state == STATE_DISABLED))	\
			ASSERT_RTNL();			\
	पूर्ण जबतक (0)

अटल पूर्णांक ef4_check_disabled(काष्ठा ef4_nic *efx)
अणु
	अगर (efx->state == STATE_DISABLED || efx->state == STATE_RECOVERY) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "device is disabled due to earlier errors\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/**************************************************************************
 *
 * Event queue processing
 *
 *************************************************************************/

/* Process channel's event queue
 *
 * This function is responsible क्रम processing the event queue of a
 * single channel.  The caller must guarantee that this function will
 * never be concurrently called more than once on the same channel,
 * though dअगरferent channels may be being processed concurrently.
 */
अटल पूर्णांक ef4_process_channel(काष्ठा ef4_channel *channel, पूर्णांक budget)
अणु
	काष्ठा ef4_tx_queue *tx_queue;
	पूर्णांक spent;

	अगर (unlikely(!channel->enabled))
		वापस 0;

	ef4_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		tx_queue->pkts_compl = 0;
		tx_queue->bytes_compl = 0;
	पूर्ण

	spent = ef4_nic_process_eventq(channel, budget);
	अगर (spent && ef4_channel_has_rx_queue(channel)) अणु
		काष्ठा ef4_rx_queue *rx_queue =
			ef4_channel_get_rx_queue(channel);

		ef4_rx_flush_packet(channel);
		ef4_fast_push_rx_descriptors(rx_queue, true);
	पूर्ण

	/* Update BQL */
	ef4_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		अगर (tx_queue->bytes_compl) अणु
			netdev_tx_completed_queue(tx_queue->core_txq,
				tx_queue->pkts_compl, tx_queue->bytes_compl);
		पूर्ण
	पूर्ण

	वापस spent;
पूर्ण

/* NAPI poll handler
 *
 * NAPI guarantees serialisation of polls of the same device, which
 * provides the guarantee required by ef4_process_channel().
 */
अटल व्योम ef4_update_irq_mod(काष्ठा ef4_nic *efx, काष्ठा ef4_channel *channel)
अणु
	पूर्णांक step = efx->irq_mod_step_us;

	अगर (channel->irq_mod_score < irq_adapt_low_thresh) अणु
		अगर (channel->irq_moderation_us > step) अणु
			channel->irq_moderation_us -= step;
			efx->type->push_irq_moderation(channel);
		पूर्ण
	पूर्ण अन्यथा अगर (channel->irq_mod_score > irq_adapt_high_thresh) अणु
		अगर (channel->irq_moderation_us <
		    efx->irq_rx_moderation_us) अणु
			channel->irq_moderation_us += step;
			efx->type->push_irq_moderation(channel);
		पूर्ण
	पूर्ण

	channel->irq_count = 0;
	channel->irq_mod_score = 0;
पूर्ण

अटल पूर्णांक ef4_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ef4_channel *channel =
		container_of(napi, काष्ठा ef4_channel, napi_str);
	काष्ठा ef4_nic *efx = channel->efx;
	पूर्णांक spent;

	netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
		   "channel %d NAPI poll executing on CPU %d\n",
		   channel->channel, raw_smp_processor_id());

	spent = ef4_process_channel(channel, budget);

	अगर (spent < budget) अणु
		अगर (ef4_channel_has_rx_queue(channel) &&
		    efx->irq_rx_adaptive &&
		    unlikely(++channel->irq_count == 1000)) अणु
			ef4_update_irq_mod(efx, channel);
		पूर्ण

		ef4_filter_rfs_expire(channel);

		/* There is no race here; although napi_disable() will
		 * only रुको क्रम napi_complete(), this isn't a problem
		 * since ef4_nic_eventq_पढ़ो_ack() will have no effect अगर
		 * पूर्णांकerrupts have alपढ़ोy been disabled.
		 */
		napi_complete_करोne(napi, spent);
		ef4_nic_eventq_पढ़ो_ack(channel);
	पूर्ण

	वापस spent;
पूर्ण

/* Create event queue
 * Event queue memory allocations are करोne only once.  If the channel
 * is reset, the memory buffer will be reused; this guards against
 * errors during channel reset and also simplअगरies पूर्णांकerrupt handling.
 */
अटल पूर्णांक ef4_probe_eventq(काष्ठा ef4_channel *channel)
अणु
	काष्ठा ef4_nic *efx = channel->efx;
	अचिन्हित दीर्घ entries;

	netअगर_dbg(efx, probe, efx->net_dev,
		  "chan %d create event queue\n", channel->channel);

	/* Build an event queue with room क्रम one event per tx and rx buffer,
	 * plus some extra क्रम link state events and MCDI completions. */
	entries = roundup_घात_of_two(efx->rxq_entries + efx->txq_entries + 128);
	EF4_BUG_ON_PARANOID(entries > EF4_MAX_EVQ_SIZE);
	channel->eventq_mask = max(entries, EF4_MIN_EVQ_SIZE) - 1;

	वापस ef4_nic_probe_eventq(channel);
पूर्ण

/* Prepare channel's event queue */
अटल पूर्णांक ef4_init_eventq(काष्ठा ef4_channel *channel)
अणु
	काष्ठा ef4_nic *efx = channel->efx;
	पूर्णांक rc;

	EF4_WARN_ON_PARANOID(channel->eventq_init);

	netअगर_dbg(efx, drv, efx->net_dev,
		  "chan %d init event queue\n", channel->channel);

	rc = ef4_nic_init_eventq(channel);
	अगर (rc == 0) अणु
		efx->type->push_irq_moderation(channel);
		channel->eventq_पढ़ो_ptr = 0;
		channel->eventq_init = true;
	पूर्ण
	वापस rc;
पूर्ण

/* Enable event queue processing and NAPI */
व्योम ef4_start_eventq(काष्ठा ef4_channel *channel)
अणु
	netअगर_dbg(channel->efx, अगरup, channel->efx->net_dev,
		  "chan %d start event queue\n", channel->channel);

	/* Make sure the NAPI handler sees the enabled flag set */
	channel->enabled = true;
	smp_wmb();

	napi_enable(&channel->napi_str);
	ef4_nic_eventq_पढ़ो_ack(channel);
पूर्ण

/* Disable event queue processing and NAPI */
व्योम ef4_stop_eventq(काष्ठा ef4_channel *channel)
अणु
	अगर (!channel->enabled)
		वापस;

	napi_disable(&channel->napi_str);
	channel->enabled = false;
पूर्ण

अटल व्योम ef4_fini_eventq(काष्ठा ef4_channel *channel)
अणु
	अगर (!channel->eventq_init)
		वापस;

	netअगर_dbg(channel->efx, drv, channel->efx->net_dev,
		  "chan %d fini event queue\n", channel->channel);

	ef4_nic_fini_eventq(channel);
	channel->eventq_init = false;
पूर्ण

अटल व्योम ef4_हटाओ_eventq(काष्ठा ef4_channel *channel)
अणु
	netअगर_dbg(channel->efx, drv, channel->efx->net_dev,
		  "chan %d remove event queue\n", channel->channel);

	ef4_nic_हटाओ_eventq(channel);
पूर्ण

/**************************************************************************
 *
 * Channel handling
 *
 *************************************************************************/

/* Allocate and initialise a channel काष्ठाure. */
अटल काष्ठा ef4_channel *
ef4_alloc_channel(काष्ठा ef4_nic *efx, पूर्णांक i, काष्ठा ef4_channel *old_channel)
अणु
	काष्ठा ef4_channel *channel;
	काष्ठा ef4_rx_queue *rx_queue;
	काष्ठा ef4_tx_queue *tx_queue;
	पूर्णांक j;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस शून्य;

	channel->efx = efx;
	channel->channel = i;
	channel->type = &ef4_शेष_channel_type;

	क्रम (j = 0; j < EF4_TXQ_TYPES; j++) अणु
		tx_queue = &channel->tx_queue[j];
		tx_queue->efx = efx;
		tx_queue->queue = i * EF4_TXQ_TYPES + j;
		tx_queue->channel = channel;
	पूर्ण

	rx_queue = &channel->rx_queue;
	rx_queue->efx = efx;
	समयr_setup(&rx_queue->slow_fill, ef4_rx_slow_fill, 0);

	वापस channel;
पूर्ण

/* Allocate and initialise a channel काष्ठाure, copying parameters
 * (but not resources) from an old channel काष्ठाure.
 */
अटल काष्ठा ef4_channel *
ef4_copy_channel(स्थिर काष्ठा ef4_channel *old_channel)
अणु
	काष्ठा ef4_channel *channel;
	काष्ठा ef4_rx_queue *rx_queue;
	काष्ठा ef4_tx_queue *tx_queue;
	पूर्णांक j;

	channel = kदो_स्मृति(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस शून्य;

	*channel = *old_channel;

	channel->napi_dev = शून्य;
	INIT_HLIST_NODE(&channel->napi_str.napi_hash_node);
	channel->napi_str.napi_id = 0;
	channel->napi_str.state = 0;
	स_रखो(&channel->eventq, 0, माप(channel->eventq));

	क्रम (j = 0; j < EF4_TXQ_TYPES; j++) अणु
		tx_queue = &channel->tx_queue[j];
		अगर (tx_queue->channel)
			tx_queue->channel = channel;
		tx_queue->buffer = शून्य;
		स_रखो(&tx_queue->txd, 0, माप(tx_queue->txd));
	पूर्ण

	rx_queue = &channel->rx_queue;
	rx_queue->buffer = शून्य;
	स_रखो(&rx_queue->rxd, 0, माप(rx_queue->rxd));
	समयr_setup(&rx_queue->slow_fill, ef4_rx_slow_fill, 0);

	वापस channel;
पूर्ण

अटल पूर्णांक ef4_probe_channel(काष्ठा ef4_channel *channel)
अणु
	काष्ठा ef4_tx_queue *tx_queue;
	काष्ठा ef4_rx_queue *rx_queue;
	पूर्णांक rc;

	netअगर_dbg(channel->efx, probe, channel->efx->net_dev,
		  "creating channel %d\n", channel->channel);

	rc = channel->type->pre_probe(channel);
	अगर (rc)
		जाओ fail;

	rc = ef4_probe_eventq(channel);
	अगर (rc)
		जाओ fail;

	ef4_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		rc = ef4_probe_tx_queue(tx_queue);
		अगर (rc)
			जाओ fail;
	पूर्ण

	ef4_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
		rc = ef4_probe_rx_queue(rx_queue);
		अगर (rc)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	ef4_हटाओ_channel(channel);
	वापस rc;
पूर्ण

अटल व्योम
ef4_get_channel_name(काष्ठा ef4_channel *channel, अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ef4_nic *efx = channel->efx;
	स्थिर अक्षर *type;
	पूर्णांक number;

	number = channel->channel;
	अगर (efx->tx_channel_offset == 0) अणु
		type = "";
	पूर्ण अन्यथा अगर (channel->channel < efx->tx_channel_offset) अणु
		type = "-rx";
	पूर्ण अन्यथा अणु
		type = "-tx";
		number -= efx->tx_channel_offset;
	पूर्ण
	snम_लिखो(buf, len, "%s%s-%d", efx->name, type, number);
पूर्ण

अटल व्योम ef4_set_channel_names(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;

	ef4_क्रम_each_channel(channel, efx)
		channel->type->get_name(channel,
					efx->msi_context[channel->channel].name,
					माप(efx->msi_context[0].name));
पूर्ण

अटल पूर्णांक ef4_probe_channels(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;
	पूर्णांक rc;

	/* Restart special buffer allocation */
	efx->next_buffer_table = 0;

	/* Probe channels in reverse, so that any 'extra' channels
	 * use the start of the buffer table. This allows the traffic
	 * channels to be resized without moving them or wasting the
	 * entries beक्रमe them.
	 */
	ef4_क्रम_each_channel_rev(channel, efx) अणु
		rc = ef4_probe_channel(channel);
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "failed to create channel %d\n",
				  channel->channel);
			जाओ fail;
		पूर्ण
	पूर्ण
	ef4_set_channel_names(efx);

	वापस 0;

fail:
	ef4_हटाओ_channels(efx);
	वापस rc;
पूर्ण

/* Channels are shutकरोwn and reinitialised whilst the NIC is running
 * to propagate configuration changes (mtu, checksum offload), or
 * to clear hardware error conditions
 */
अटल व्योम ef4_start_datapath(काष्ठा ef4_nic *efx)
अणु
	netdev_features_t old_features = efx->net_dev->features;
	bool old_rx_scatter = efx->rx_scatter;
	काष्ठा ef4_tx_queue *tx_queue;
	काष्ठा ef4_rx_queue *rx_queue;
	काष्ठा ef4_channel *channel;
	माप_प्रकार rx_buf_len;

	/* Calculate the rx buffer allocation parameters required to
	 * support the current MTU, including padding क्रम header
	 * alignment and overruns.
	 */
	efx->rx_dma_len = (efx->rx_prefix_size +
			   EF4_MAX_FRAME_LEN(efx->net_dev->mtu) +
			   efx->type->rx_buffer_padding);
	rx_buf_len = (माप(काष्ठा ef4_rx_page_state) +
		      efx->rx_ip_align + efx->rx_dma_len);
	अगर (rx_buf_len <= PAGE_SIZE) अणु
		efx->rx_scatter = efx->type->always_rx_scatter;
		efx->rx_buffer_order = 0;
	पूर्ण अन्यथा अगर (efx->type->can_rx_scatter) अणु
		BUILD_BUG_ON(EF4_RX_USR_BUF_SIZE % L1_CACHE_BYTES);
		BUILD_BUG_ON(माप(काष्ठा ef4_rx_page_state) +
			     2 * ALIGN(NET_IP_ALIGN + EF4_RX_USR_BUF_SIZE,
				       EF4_RX_BUF_ALIGNMENT) >
			     PAGE_SIZE);
		efx->rx_scatter = true;
		efx->rx_dma_len = EF4_RX_USR_BUF_SIZE;
		efx->rx_buffer_order = 0;
	पूर्ण अन्यथा अणु
		efx->rx_scatter = false;
		efx->rx_buffer_order = get_order(rx_buf_len);
	पूर्ण

	ef4_rx_config_page_split(efx);
	अगर (efx->rx_buffer_order)
		netअगर_dbg(efx, drv, efx->net_dev,
			  "RX buf len=%u; page order=%u batch=%u\n",
			  efx->rx_dma_len, efx->rx_buffer_order,
			  efx->rx_pages_per_batch);
	अन्यथा
		netअगर_dbg(efx, drv, efx->net_dev,
			  "RX buf len=%u step=%u bpp=%u; page batch=%u\n",
			  efx->rx_dma_len, efx->rx_page_buf_step,
			  efx->rx_bufs_per_page, efx->rx_pages_per_batch);

	/* Restore previously fixed features in hw_features and हटाओ
	 * features which are fixed now
	 */
	efx->net_dev->hw_features |= efx->net_dev->features;
	efx->net_dev->hw_features &= ~efx->fixed_features;
	efx->net_dev->features |= efx->fixed_features;
	अगर (efx->net_dev->features != old_features)
		netdev_features_change(efx->net_dev);

	/* RX filters may also have scatter-enabled flags */
	अगर (efx->rx_scatter != old_rx_scatter)
		efx->type->filter_update_rx_scatter(efx);

	/* We must keep at least one descriptor in a TX ring empty.
	 * We could aव्योम this when the queue size करोes not exactly
	 * match the hardware ring size, but it's not that important.
	 * Thereक्रमe we stop the queue when one more skb might fill
	 * the ring completely.  We wake it when half way back to
	 * empty.
	 */
	efx->txq_stop_thresh = efx->txq_entries - ef4_tx_max_skb_descs(efx);
	efx->txq_wake_thresh = efx->txq_stop_thresh / 2;

	/* Initialise the channels */
	ef4_क्रम_each_channel(channel, efx) अणु
		ef4_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
			ef4_init_tx_queue(tx_queue);
			atomic_inc(&efx->active_queues);
		पूर्ण

		ef4_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
			ef4_init_rx_queue(rx_queue);
			atomic_inc(&efx->active_queues);
			ef4_stop_eventq(channel);
			ef4_fast_push_rx_descriptors(rx_queue, false);
			ef4_start_eventq(channel);
		पूर्ण

		WARN_ON(channel->rx_pkt_n_frags);
	पूर्ण

	अगर (netअगर_device_present(efx->net_dev))
		netअगर_tx_wake_all_queues(efx->net_dev);
पूर्ण

अटल व्योम ef4_stop_datapath(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;
	काष्ठा ef4_tx_queue *tx_queue;
	काष्ठा ef4_rx_queue *rx_queue;
	पूर्णांक rc;

	EF4_ASSERT_RESET_SERIALISED(efx);
	BUG_ON(efx->port_enabled);

	/* Stop RX refill */
	ef4_क्रम_each_channel(channel, efx) अणु
		ef4_क्रम_each_channel_rx_queue(rx_queue, channel)
			rx_queue->refill_enabled = false;
	पूर्ण

	ef4_क्रम_each_channel(channel, efx) अणु
		/* RX packet processing is pipelined, so रुको क्रम the
		 * NAPI handler to complete.  At least event queue 0
		 * might be kept active by non-data events, so करोn't
		 * use napi_synchronize() but actually disable NAPI
		 * temporarily.
		 */
		अगर (ef4_channel_has_rx_queue(channel)) अणु
			ef4_stop_eventq(channel);
			ef4_start_eventq(channel);
		पूर्ण
	पूर्ण

	rc = efx->type->fini_dmaq(efx);
	अगर (rc && EF4_WORKAROUND_7803(efx)) अणु
		/* Schedule a reset to recover from the flush failure. The
		 * descriptor caches reference memory we're about to मुक्त,
		 * but falcon_reconfigure_mac_wrapper() won't reconnect
		 * the MACs because of the pending reset.
		 */
		netअगर_err(efx, drv, efx->net_dev,
			  "Resetting to recover from flush failure\n");
		ef4_schedule_reset(efx, RESET_TYPE_ALL);
	पूर्ण अन्यथा अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev, "failed to flush queues\n");
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "successfully flushed all queues\n");
	पूर्ण

	ef4_क्रम_each_channel(channel, efx) अणु
		ef4_क्रम_each_channel_rx_queue(rx_queue, channel)
			ef4_fini_rx_queue(rx_queue);
		ef4_क्रम_each_possible_channel_tx_queue(tx_queue, channel)
			ef4_fini_tx_queue(tx_queue);
	पूर्ण
पूर्ण

अटल व्योम ef4_हटाओ_channel(काष्ठा ef4_channel *channel)
अणु
	काष्ठा ef4_tx_queue *tx_queue;
	काष्ठा ef4_rx_queue *rx_queue;

	netअगर_dbg(channel->efx, drv, channel->efx->net_dev,
		  "destroy chan %d\n", channel->channel);

	ef4_क्रम_each_channel_rx_queue(rx_queue, channel)
		ef4_हटाओ_rx_queue(rx_queue);
	ef4_क्रम_each_possible_channel_tx_queue(tx_queue, channel)
		ef4_हटाओ_tx_queue(tx_queue);
	ef4_हटाओ_eventq(channel);
	channel->type->post_हटाओ(channel);
पूर्ण

अटल व्योम ef4_हटाओ_channels(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;

	ef4_क्रम_each_channel(channel, efx)
		ef4_हटाओ_channel(channel);
पूर्ण

पूर्णांक
ef4_पुनः_स्मृति_channels(काष्ठा ef4_nic *efx, u32 rxq_entries, u32 txq_entries)
अणु
	काष्ठा ef4_channel *other_channel[EF4_MAX_CHANNELS], *channel;
	u32 old_rxq_entries, old_txq_entries;
	अचिन्हित i, next_buffer_table = 0;
	पूर्णांक rc, rc2;

	rc = ef4_check_disabled(efx);
	अगर (rc)
		वापस rc;

	/* Not all channels should be पुनः_स्मृतिated. We must aव्योम
	 * पुनः_स्मृतिating their buffer table entries.
	 */
	ef4_क्रम_each_channel(channel, efx) अणु
		काष्ठा ef4_rx_queue *rx_queue;
		काष्ठा ef4_tx_queue *tx_queue;

		अगर (channel->type->copy)
			जारी;
		next_buffer_table = max(next_buffer_table,
					channel->eventq.index +
					channel->eventq.entries);
		ef4_क्रम_each_channel_rx_queue(rx_queue, channel)
			next_buffer_table = max(next_buffer_table,
						rx_queue->rxd.index +
						rx_queue->rxd.entries);
		ef4_क्रम_each_channel_tx_queue(tx_queue, channel)
			next_buffer_table = max(next_buffer_table,
						tx_queue->txd.index +
						tx_queue->txd.entries);
	पूर्ण

	ef4_device_detach_sync(efx);
	ef4_stop_all(efx);
	ef4_soft_disable_पूर्णांकerrupts(efx);

	/* Clone channels (where possible) */
	स_रखो(other_channel, 0, माप(other_channel));
	क्रम (i = 0; i < efx->n_channels; i++) अणु
		channel = efx->channel[i];
		अगर (channel->type->copy)
			channel = channel->type->copy(channel);
		अगर (!channel) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		other_channel[i] = channel;
	पूर्ण

	/* Swap entry counts and channel poपूर्णांकers */
	old_rxq_entries = efx->rxq_entries;
	old_txq_entries = efx->txq_entries;
	efx->rxq_entries = rxq_entries;
	efx->txq_entries = txq_entries;
	क्रम (i = 0; i < efx->n_channels; i++) अणु
		channel = efx->channel[i];
		efx->channel[i] = other_channel[i];
		other_channel[i] = channel;
	पूर्ण

	/* Restart buffer table allocation */
	efx->next_buffer_table = next_buffer_table;

	क्रम (i = 0; i < efx->n_channels; i++) अणु
		channel = efx->channel[i];
		अगर (!channel->type->copy)
			जारी;
		rc = ef4_probe_channel(channel);
		अगर (rc)
			जाओ rollback;
		ef4_init_napi_channel(efx->channel[i]);
	पूर्ण

out:
	/* Destroy unused channel काष्ठाures */
	क्रम (i = 0; i < efx->n_channels; i++) अणु
		channel = other_channel[i];
		अगर (channel && channel->type->copy) अणु
			ef4_fini_napi_channel(channel);
			ef4_हटाओ_channel(channel);
			kमुक्त(channel);
		पूर्ण
	पूर्ण

	rc2 = ef4_soft_enable_पूर्णांकerrupts(efx);
	अगर (rc2) अणु
		rc = rc ? rc : rc2;
		netअगर_err(efx, drv, efx->net_dev,
			  "unable to restart interrupts on channel reallocation\n");
		ef4_schedule_reset(efx, RESET_TYPE_DISABLE);
	पूर्ण अन्यथा अणु
		ef4_start_all(efx);
		netअगर_device_attach(efx->net_dev);
	पूर्ण
	वापस rc;

rollback:
	/* Swap back */
	efx->rxq_entries = old_rxq_entries;
	efx->txq_entries = old_txq_entries;
	क्रम (i = 0; i < efx->n_channels; i++) अणु
		channel = efx->channel[i];
		efx->channel[i] = other_channel[i];
		other_channel[i] = channel;
	पूर्ण
	जाओ out;
पूर्ण

व्योम ef4_schedule_slow_fill(काष्ठा ef4_rx_queue *rx_queue)
अणु
	mod_समयr(&rx_queue->slow_fill, jअगरfies + msecs_to_jअगरfies(100));
पूर्ण

अटल स्थिर काष्ठा ef4_channel_type ef4_शेष_channel_type = अणु
	.pre_probe		= ef4_channel_dummy_op_पूर्णांक,
	.post_हटाओ		= ef4_channel_dummy_op_व्योम,
	.get_name		= ef4_get_channel_name,
	.copy			= ef4_copy_channel,
	.keep_eventq		= false,
पूर्ण;

पूर्णांक ef4_channel_dummy_op_पूर्णांक(काष्ठा ef4_channel *channel)
अणु
	वापस 0;
पूर्ण

व्योम ef4_channel_dummy_op_व्योम(काष्ठा ef4_channel *channel)
अणु
पूर्ण

/**************************************************************************
 *
 * Port handling
 *
 **************************************************************************/

/* This ensures that the kernel is kept inक्रमmed (via
 * netअगर_carrier_on/off) of the link status, and also मुख्यtains the
 * link status's stop on the port's TX queue.
 */
व्योम ef4_link_status_changed(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_link_state *link_state = &efx->link_state;

	/* SFC Bug 5356: A net_dev notअगरier is रेजिस्टरed, so we must ensure
	 * that no events are triggered between unरेजिस्टर_netdev() and the
	 * driver unloading. A more general condition is that NETDEV_CHANGE
	 * can only be generated between NETDEV_UP and NETDEV_DOWN */
	अगर (!netअगर_running(efx->net_dev))
		वापस;

	अगर (link_state->up != netअगर_carrier_ok(efx->net_dev)) अणु
		efx->n_link_state_changes++;

		अगर (link_state->up)
			netअगर_carrier_on(efx->net_dev);
		अन्यथा
			netअगर_carrier_off(efx->net_dev);
	पूर्ण

	/* Status message क्रम kernel log */
	अगर (link_state->up)
		netअगर_info(efx, link, efx->net_dev,
			   "link up at %uMbps %s-duplex (MTU %d)\n",
			   link_state->speed, link_state->fd ? "full" : "half",
			   efx->net_dev->mtu);
	अन्यथा
		netअगर_info(efx, link, efx->net_dev, "link down\n");
पूर्ण

व्योम ef4_link_set_advertising(काष्ठा ef4_nic *efx, u32 advertising)
अणु
	efx->link_advertising = advertising;
	अगर (advertising) अणु
		अगर (advertising & ADVERTISED_Pause)
			efx->wanted_fc |= (EF4_FC_TX | EF4_FC_RX);
		अन्यथा
			efx->wanted_fc &= ~(EF4_FC_TX | EF4_FC_RX);
		अगर (advertising & ADVERTISED_Asym_Pause)
			efx->wanted_fc ^= EF4_FC_TX;
	पूर्ण
पूर्ण

व्योम ef4_link_set_wanted_fc(काष्ठा ef4_nic *efx, u8 wanted_fc)
अणु
	efx->wanted_fc = wanted_fc;
	अगर (efx->link_advertising) अणु
		अगर (wanted_fc & EF4_FC_RX)
			efx->link_advertising |= (ADVERTISED_Pause |
						  ADVERTISED_Asym_Pause);
		अन्यथा
			efx->link_advertising &= ~(ADVERTISED_Pause |
						   ADVERTISED_Asym_Pause);
		अगर (wanted_fc & EF4_FC_TX)
			efx->link_advertising ^= ADVERTISED_Asym_Pause;
	पूर्ण
पूर्ण

अटल व्योम ef4_fini_port(काष्ठा ef4_nic *efx);

/* We assume that efx->type->reconfigure_mac will always try to sync RX
 * filters and thereक्रमe needs to पढ़ो-lock the filter table against मुक्तing
 */
व्योम ef4_mac_reconfigure(काष्ठा ef4_nic *efx)
अणु
	करोwn_पढ़ो(&efx->filter_sem);
	efx->type->reconfigure_mac(efx);
	up_पढ़ो(&efx->filter_sem);
पूर्ण

/* Push loopback/घातer/transmit disable settings to the PHY, and reconfigure
 * the MAC appropriately. All other PHY configuration changes are pushed
 * through phy_op->set_link_ksettings(), and pushed asynchronously to the MAC
 * through ef4_monitor().
 *
 * Callers must hold the mac_lock
 */
पूर्णांक __ef4_reconfigure_port(काष्ठा ef4_nic *efx)
अणु
	क्रमागत ef4_phy_mode phy_mode;
	पूर्णांक rc;

	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	/* Disable PHY transmit in mac level loopbacks */
	phy_mode = efx->phy_mode;
	अगर (LOOPBACK_INTERNAL(efx))
		efx->phy_mode |= PHY_MODE_TX_DISABLED;
	अन्यथा
		efx->phy_mode &= ~PHY_MODE_TX_DISABLED;

	rc = efx->type->reconfigure_port(efx);

	अगर (rc)
		efx->phy_mode = phy_mode;

	वापस rc;
पूर्ण

/* Reinitialise the MAC to pick up new PHY settings, even अगर the port is
 * disabled. */
पूर्णांक ef4_reconfigure_port(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	EF4_ASSERT_RESET_SERIALISED(efx);

	mutex_lock(&efx->mac_lock);
	rc = __ef4_reconfigure_port(efx);
	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

/* Asynchronous work item क्रम changing MAC promiscuity and multicast
 * hash.  Aव्योम a drain/rx_ingress enable by reconfiguring the current
 * MAC directly. */
अटल व्योम ef4_mac_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा ef4_nic *efx = container_of(data, काष्ठा ef4_nic, mac_work);

	mutex_lock(&efx->mac_lock);
	अगर (efx->port_enabled)
		ef4_mac_reconfigure(efx);
	mutex_unlock(&efx->mac_lock);
पूर्ण

अटल पूर्णांक ef4_probe_port(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	netअगर_dbg(efx, probe, efx->net_dev, "create port\n");

	अगर (phy_flash_cfg)
		efx->phy_mode = PHY_MODE_SPECIAL;

	/* Connect up MAC/PHY operations table */
	rc = efx->type->probe_port(efx);
	अगर (rc)
		वापस rc;

	/* Initialise MAC address to permanent address */
	ether_addr_copy(efx->net_dev->dev_addr, efx->net_dev->perm_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक ef4_init_port(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	netअगर_dbg(efx, drv, efx->net_dev, "init port\n");

	mutex_lock(&efx->mac_lock);

	rc = efx->phy_op->init(efx);
	अगर (rc)
		जाओ fail1;

	efx->port_initialized = true;

	/* Reconfigure the MAC beक्रमe creating dma queues (required क्रम
	 * Falcon/A1 where RX_INGR_EN/TX_DRAIN_EN isn't supported) */
	ef4_mac_reconfigure(efx);

	/* Ensure the PHY advertises the correct flow control settings */
	rc = efx->phy_op->reconfigure(efx);
	अगर (rc && rc != -EPERM)
		जाओ fail2;

	mutex_unlock(&efx->mac_lock);
	वापस 0;

fail2:
	efx->phy_op->fini(efx);
fail1:
	mutex_unlock(&efx->mac_lock);
	वापस rc;
पूर्ण

अटल व्योम ef4_start_port(काष्ठा ef4_nic *efx)
अणु
	netअगर_dbg(efx, अगरup, efx->net_dev, "start port\n");
	BUG_ON(efx->port_enabled);

	mutex_lock(&efx->mac_lock);
	efx->port_enabled = true;

	/* Ensure MAC ingress/egress is enabled */
	ef4_mac_reconfigure(efx);

	mutex_unlock(&efx->mac_lock);
पूर्ण

/* Cancel work क्रम MAC reconfiguration, periodic hardware monitoring
 * and the async self-test, रुको क्रम them to finish and prevent them
 * being scheduled again.  This करोesn't cover online resets, which
 * should only be cancelled when removing the device.
 */
अटल व्योम ef4_stop_port(काष्ठा ef4_nic *efx)
अणु
	netअगर_dbg(efx, अगरकरोwn, efx->net_dev, "stop port\n");

	EF4_ASSERT_RESET_SERIALISED(efx);

	mutex_lock(&efx->mac_lock);
	efx->port_enabled = false;
	mutex_unlock(&efx->mac_lock);

	/* Serialise against ef4_set_multicast_list() */
	netअगर_addr_lock_bh(efx->net_dev);
	netअगर_addr_unlock_bh(efx->net_dev);

	cancel_delayed_work_sync(&efx->monitor_work);
	ef4_selftest_async_cancel(efx);
	cancel_work_sync(&efx->mac_work);
पूर्ण

अटल व्योम ef4_fini_port(काष्ठा ef4_nic *efx)
अणु
	netअगर_dbg(efx, drv, efx->net_dev, "shut down port\n");

	अगर (!efx->port_initialized)
		वापस;

	efx->phy_op->fini(efx);
	efx->port_initialized = false;

	efx->link_state.up = false;
	ef4_link_status_changed(efx);
पूर्ण

अटल व्योम ef4_हटाओ_port(काष्ठा ef4_nic *efx)
अणु
	netअगर_dbg(efx, drv, efx->net_dev, "destroying port\n");

	efx->type->हटाओ_port(efx);
पूर्ण

/**************************************************************************
 *
 * NIC handling
 *
 **************************************************************************/

अटल LIST_HEAD(ef4_primary_list);
अटल LIST_HEAD(ef4_unassociated_list);

अटल bool ef4_same_controller(काष्ठा ef4_nic *left, काष्ठा ef4_nic *right)
अणु
	वापस left->type == right->type &&
		left->vpd_sn && right->vpd_sn &&
		!म_भेद(left->vpd_sn, right->vpd_sn);
पूर्ण

अटल व्योम ef4_associate(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_nic *other, *next;

	अगर (efx->primary == efx) अणु
		/* Adding primary function; look क्रम secondaries */

		netअगर_dbg(efx, probe, efx->net_dev, "adding to primary list\n");
		list_add_tail(&efx->node, &ef4_primary_list);

		list_क्रम_each_entry_safe(other, next, &ef4_unassociated_list,
					 node) अणु
			अगर (ef4_same_controller(efx, other)) अणु
				list_del(&other->node);
				netअगर_dbg(other, probe, other->net_dev,
					  "moving to secondary list of %s %s\n",
					  pci_name(efx->pci_dev),
					  efx->net_dev->name);
				list_add_tail(&other->node,
					      &efx->secondary_list);
				other->primary = efx;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Adding secondary function; look क्रम primary */

		list_क्रम_each_entry(other, &ef4_primary_list, node) अणु
			अगर (ef4_same_controller(efx, other)) अणु
				netअगर_dbg(efx, probe, efx->net_dev,
					  "adding to secondary list of %s %s\n",
					  pci_name(other->pci_dev),
					  other->net_dev->name);
				list_add_tail(&efx->node,
					      &other->secondary_list);
				efx->primary = other;
				वापस;
			पूर्ण
		पूर्ण

		netअगर_dbg(efx, probe, efx->net_dev,
			  "adding to unassociated list\n");
		list_add_tail(&efx->node, &ef4_unassociated_list);
	पूर्ण
पूर्ण

अटल व्योम ef4_dissociate(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_nic *other, *next;

	list_del(&efx->node);
	efx->primary = शून्य;

	list_क्रम_each_entry_safe(other, next, &efx->secondary_list, node) अणु
		list_del(&other->node);
		netअगर_dbg(other, probe, other->net_dev,
			  "moving to unassociated list\n");
		list_add_tail(&other->node, &ef4_unassociated_list);
		other->primary = शून्य;
	पूर्ण
पूर्ण

/* This configures the PCI device to enable I/O and DMA. */
अटल पूर्णांक ef4_init_io(काष्ठा ef4_nic *efx)
अणु
	काष्ठा pci_dev *pci_dev = efx->pci_dev;
	dma_addr_t dma_mask = efx->type->max_dma_mask;
	अचिन्हित पूर्णांक mem_map_size = efx->type->mem_map_size(efx);
	पूर्णांक rc, bar;

	netअगर_dbg(efx, probe, efx->net_dev, "initialising I/O\n");

	bar = efx->type->mem_bar;

	rc = pci_enable_device(pci_dev);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to enable PCI device\n");
		जाओ fail1;
	पूर्ण

	pci_set_master(pci_dev);

	/* Set the PCI DMA mask.  Try all possibilities from our genuine mask
	 * करोwn to 32 bits, because some architectures will allow 40 bit
	 * masks event though they reject 46 bit masks.
	 */
	जबतक (dma_mask > 0x7fffffffUL) अणु
		rc = dma_set_mask_and_coherent(&pci_dev->dev, dma_mask);
		अगर (rc == 0)
			अवरोध;
		dma_mask >>= 1;
	पूर्ण
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "could not find a suitable DMA mask\n");
		जाओ fail2;
	पूर्ण
	netअगर_dbg(efx, probe, efx->net_dev,
		  "using DMA mask %llx\n", (अचिन्हित दीर्घ दीर्घ) dma_mask);

	efx->membase_phys = pci_resource_start(efx->pci_dev, bar);
	rc = pci_request_region(pci_dev, bar, "sfc");
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "request for memory BAR failed\n");
		rc = -EIO;
		जाओ fail3;
	पूर्ण
	efx->membase = ioremap(efx->membase_phys, mem_map_size);
	अगर (!efx->membase) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "could not map memory BAR at %llx+%x\n",
			  (अचिन्हित दीर्घ दीर्घ)efx->membase_phys, mem_map_size);
		rc = -ENOMEM;
		जाओ fail4;
	पूर्ण
	netअगर_dbg(efx, probe, efx->net_dev,
		  "memory BAR at %llx+%x (virtual %p)\n",
		  (अचिन्हित दीर्घ दीर्घ)efx->membase_phys, mem_map_size,
		  efx->membase);

	वापस 0;

 fail4:
	pci_release_region(efx->pci_dev, bar);
 fail3:
	efx->membase_phys = 0;
 fail2:
	pci_disable_device(efx->pci_dev);
 fail1:
	वापस rc;
पूर्ण

अटल व्योम ef4_fini_io(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक bar;

	netअगर_dbg(efx, drv, efx->net_dev, "shutting down I/O\n");

	अगर (efx->membase) अणु
		iounmap(efx->membase);
		efx->membase = शून्य;
	पूर्ण

	अगर (efx->membase_phys) अणु
		bar = efx->type->mem_bar;
		pci_release_region(efx->pci_dev, bar);
		efx->membase_phys = 0;
	पूर्ण

	/* Don't disable bus-mastering अगर VFs are asचिन्हित */
	अगर (!pci_vfs_asचिन्हित(efx->pci_dev))
		pci_disable_device(efx->pci_dev);
पूर्ण

व्योम ef4_set_शेष_rx_indir_table(काष्ठा ef4_nic *efx)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(efx->rx_indir_table); i++)
		efx->rx_indir_table[i] =
			ethtool_rxfh_indir_शेष(i, efx->rss_spपढ़ो);
पूर्ण

अटल अचिन्हित पूर्णांक ef4_wanted_parallelism(काष्ठा ef4_nic *efx)
अणु
	cpumask_var_t thपढ़ो_mask;
	अचिन्हित पूर्णांक count;
	पूर्णांक cpu;

	अगर (rss_cpus) अणु
		count = rss_cpus;
	पूर्ण अन्यथा अणु
		अगर (unlikely(!zalloc_cpumask_var(&thपढ़ो_mask, GFP_KERNEL))) अणु
			netअगर_warn(efx, probe, efx->net_dev,
				   "RSS disabled due to allocation failure\n");
			वापस 1;
		पूर्ण

		count = 0;
		क्रम_each_online_cpu(cpu) अणु
			अगर (!cpumask_test_cpu(cpu, thपढ़ो_mask)) अणु
				++count;
				cpumask_or(thपढ़ो_mask, thपढ़ो_mask,
					   topology_sibling_cpumask(cpu));
			पूर्ण
		पूर्ण

		मुक्त_cpumask_var(thपढ़ो_mask);
	पूर्ण

	अगर (count > EF4_MAX_RX_QUEUES) अणु
		netअगर_cond_dbg(efx, probe, efx->net_dev, !rss_cpus, warn,
			       "Reducing number of rx queues from %u to %u.\n",
			       count, EF4_MAX_RX_QUEUES);
		count = EF4_MAX_RX_QUEUES;
	पूर्ण

	वापस count;
पूर्ण

/* Probe the number and type of पूर्णांकerrupts we are able to obtain, and
 * the resulting numbers of channels and RX queues.
 */
अटल पूर्णांक ef4_probe_पूर्णांकerrupts(काष्ठा ef4_nic *efx)
अणु
	अचिन्हित पूर्णांक extra_channels = 0;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक rc;

	क्रम (i = 0; i < EF4_MAX_EXTRA_CHANNELS; i++)
		अगर (efx->extra_channel_type[i])
			++extra_channels;

	अगर (efx->पूर्णांकerrupt_mode == EF4_INT_MODE_MSIX) अणु
		काष्ठा msix_entry xentries[EF4_MAX_CHANNELS];
		अचिन्हित पूर्णांक n_channels;

		n_channels = ef4_wanted_parallelism(efx);
		अगर (ef4_separate_tx_channels)
			n_channels *= 2;
		n_channels += extra_channels;
		n_channels = min(n_channels, efx->max_channels);

		क्रम (i = 0; i < n_channels; i++)
			xentries[i].entry = i;
		rc = pci_enable_msix_range(efx->pci_dev,
					   xentries, 1, n_channels);
		अगर (rc < 0) अणु
			/* Fall back to single channel MSI */
			efx->पूर्णांकerrupt_mode = EF4_INT_MODE_MSI;
			netअगर_err(efx, drv, efx->net_dev,
				  "could not enable MSI-X\n");
		पूर्ण अन्यथा अगर (rc < n_channels) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "WARNING: Insufficient MSI-X vectors"
				  " available (%d < %u).\n", rc, n_channels);
			netअगर_err(efx, drv, efx->net_dev,
				  "WARNING: Performance may be reduced.\n");
			n_channels = rc;
		पूर्ण

		अगर (rc > 0) अणु
			efx->n_channels = n_channels;
			अगर (n_channels > extra_channels)
				n_channels -= extra_channels;
			अगर (ef4_separate_tx_channels) अणु
				efx->n_tx_channels = min(max(n_channels / 2,
							     1U),
							 efx->max_tx_channels);
				efx->n_rx_channels = max(n_channels -
							 efx->n_tx_channels,
							 1U);
			पूर्ण अन्यथा अणु
				efx->n_tx_channels = min(n_channels,
							 efx->max_tx_channels);
				efx->n_rx_channels = n_channels;
			पूर्ण
			क्रम (i = 0; i < efx->n_channels; i++)
				ef4_get_channel(efx, i)->irq =
					xentries[i].vector;
		पूर्ण
	पूर्ण

	/* Try single पूर्णांकerrupt MSI */
	अगर (efx->पूर्णांकerrupt_mode == EF4_INT_MODE_MSI) अणु
		efx->n_channels = 1;
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		rc = pci_enable_msi(efx->pci_dev);
		अगर (rc == 0) अणु
			ef4_get_channel(efx, 0)->irq = efx->pci_dev->irq;
		पूर्ण अन्यथा अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "could not enable MSI\n");
			efx->पूर्णांकerrupt_mode = EF4_INT_MODE_LEGACY;
		पूर्ण
	पूर्ण

	/* Assume legacy पूर्णांकerrupts */
	अगर (efx->पूर्णांकerrupt_mode == EF4_INT_MODE_LEGACY) अणु
		efx->n_channels = 1 + (ef4_separate_tx_channels ? 1 : 0);
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		efx->legacy_irq = efx->pci_dev->irq;
	पूर्ण

	/* Assign extra channels अगर possible */
	j = efx->n_channels;
	क्रम (i = 0; i < EF4_MAX_EXTRA_CHANNELS; i++) अणु
		अगर (!efx->extra_channel_type[i])
			जारी;
		अगर (efx->पूर्णांकerrupt_mode != EF4_INT_MODE_MSIX ||
		    efx->n_channels <= extra_channels) अणु
			efx->extra_channel_type[i]->handle_no_channel(efx);
		पूर्ण अन्यथा अणु
			--j;
			ef4_get_channel(efx, j)->type =
				efx->extra_channel_type[i];
		पूर्ण
	पूर्ण

	efx->rss_spपढ़ो = efx->n_rx_channels;

	वापस 0;
पूर्ण

अटल पूर्णांक ef4_soft_enable_पूर्णांकerrupts(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel, *end_channel;
	पूर्णांक rc;

	BUG_ON(efx->state == STATE_DISABLED);

	efx->irq_soft_enabled = true;
	smp_wmb();

	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (!channel->type->keep_eventq) अणु
			rc = ef4_init_eventq(channel);
			अगर (rc)
				जाओ fail;
		पूर्ण
		ef4_start_eventq(channel);
	पूर्ण

	वापस 0;
fail:
	end_channel = channel;
	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (channel == end_channel)
			अवरोध;
		ef4_stop_eventq(channel);
		अगर (!channel->type->keep_eventq)
			ef4_fini_eventq(channel);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ef4_soft_disable_पूर्णांकerrupts(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;

	अगर (efx->state == STATE_DISABLED)
		वापस;

	efx->irq_soft_enabled = false;
	smp_wmb();

	अगर (efx->legacy_irq)
		synchronize_irq(efx->legacy_irq);

	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (channel->irq)
			synchronize_irq(channel->irq);

		ef4_stop_eventq(channel);
		अगर (!channel->type->keep_eventq)
			ef4_fini_eventq(channel);
	पूर्ण
पूर्ण

अटल पूर्णांक ef4_enable_पूर्णांकerrupts(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel, *end_channel;
	पूर्णांक rc;

	BUG_ON(efx->state == STATE_DISABLED);

	अगर (efx->eeh_disabled_legacy_irq) अणु
		enable_irq(efx->legacy_irq);
		efx->eeh_disabled_legacy_irq = false;
	पूर्ण

	efx->type->irq_enable_master(efx);

	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (channel->type->keep_eventq) अणु
			rc = ef4_init_eventq(channel);
			अगर (rc)
				जाओ fail;
		पूर्ण
	पूर्ण

	rc = ef4_soft_enable_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail;

	वापस 0;

fail:
	end_channel = channel;
	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (channel == end_channel)
			अवरोध;
		अगर (channel->type->keep_eventq)
			ef4_fini_eventq(channel);
	पूर्ण

	efx->type->irq_disable_non_ev(efx);

	वापस rc;
पूर्ण

अटल व्योम ef4_disable_पूर्णांकerrupts(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;

	ef4_soft_disable_पूर्णांकerrupts(efx);

	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (channel->type->keep_eventq)
			ef4_fini_eventq(channel);
	पूर्ण

	efx->type->irq_disable_non_ev(efx);
पूर्ण

अटल व्योम ef4_हटाओ_पूर्णांकerrupts(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;

	/* Remove MSI/MSI-X पूर्णांकerrupts */
	ef4_क्रम_each_channel(channel, efx)
		channel->irq = 0;
	pci_disable_msi(efx->pci_dev);
	pci_disable_msix(efx->pci_dev);

	/* Remove legacy पूर्णांकerrupt */
	efx->legacy_irq = 0;
पूर्ण

अटल व्योम ef4_set_channels(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;
	काष्ठा ef4_tx_queue *tx_queue;

	efx->tx_channel_offset =
		ef4_separate_tx_channels ?
		efx->n_channels - efx->n_tx_channels : 0;

	/* We need to mark which channels really have RX and TX
	 * queues, and adjust the TX queue numbers अगर we have separate
	 * RX-only and TX-only channels.
	 */
	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (channel->channel < efx->n_rx_channels)
			channel->rx_queue.core_index = channel->channel;
		अन्यथा
			channel->rx_queue.core_index = -1;

		ef4_क्रम_each_channel_tx_queue(tx_queue, channel)
			tx_queue->queue -= (efx->tx_channel_offset *
					    EF4_TXQ_TYPES);
	पूर्ण
पूर्ण

अटल पूर्णांक ef4_probe_nic(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	netअगर_dbg(efx, probe, efx->net_dev, "creating NIC\n");

	/* Carry out hardware-type specअगरic initialisation */
	rc = efx->type->probe(efx);
	अगर (rc)
		वापस rc;

	करो अणु
		अगर (!efx->max_channels || !efx->max_tx_channels) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "Insufficient resources to allocate"
				  " any channels\n");
			rc = -ENOSPC;
			जाओ fail1;
		पूर्ण

		/* Determine the number of channels and queues by trying
		 * to hook in MSI-X पूर्णांकerrupts.
		 */
		rc = ef4_probe_पूर्णांकerrupts(efx);
		अगर (rc)
			जाओ fail1;

		ef4_set_channels(efx);

		/* dimension_resources can fail with EAGAIN */
		rc = efx->type->dimension_resources(efx);
		अगर (rc != 0 && rc != -EAGAIN)
			जाओ fail2;

		अगर (rc == -EAGAIN)
			/* try again with new max_channels */
			ef4_हटाओ_पूर्णांकerrupts(efx);

	पूर्ण जबतक (rc == -EAGAIN);

	अगर (efx->n_channels > 1)
		netdev_rss_key_fill(&efx->rx_hash_key,
				    माप(efx->rx_hash_key));
	ef4_set_शेष_rx_indir_table(efx);

	netअगर_set_real_num_tx_queues(efx->net_dev, efx->n_tx_channels);
	netअगर_set_real_num_rx_queues(efx->net_dev, efx->n_rx_channels);

	/* Initialise the पूर्णांकerrupt moderation settings */
	efx->irq_mod_step_us = DIV_ROUND_UP(efx->समयr_quantum_ns, 1000);
	ef4_init_irq_moderation(efx, tx_irq_mod_usec, rx_irq_mod_usec, true,
				true);

	वापस 0;

fail2:
	ef4_हटाओ_पूर्णांकerrupts(efx);
fail1:
	efx->type->हटाओ(efx);
	वापस rc;
पूर्ण

अटल व्योम ef4_हटाओ_nic(काष्ठा ef4_nic *efx)
अणु
	netअगर_dbg(efx, drv, efx->net_dev, "destroying NIC\n");

	ef4_हटाओ_पूर्णांकerrupts(efx);
	efx->type->हटाओ(efx);
पूर्ण

अटल पूर्णांक ef4_probe_filters(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	spin_lock_init(&efx->filter_lock);
	init_rwsem(&efx->filter_sem);
	mutex_lock(&efx->mac_lock);
	करोwn_ग_लिखो(&efx->filter_sem);
	rc = efx->type->filter_table_probe(efx);
	अगर (rc)
		जाओ out_unlock;

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर (efx->type->offload_features & NETIF_F_NTUPLE) अणु
		काष्ठा ef4_channel *channel;
		पूर्णांक i, success = 1;

		ef4_क्रम_each_channel(channel, efx) अणु
			channel->rps_flow_id =
				kसुस्मृति(efx->type->max_rx_ip_filters,
					माप(*channel->rps_flow_id),
					GFP_KERNEL);
			अगर (!channel->rps_flow_id)
				success = 0;
			अन्यथा
				क्रम (i = 0;
				     i < efx->type->max_rx_ip_filters;
				     ++i)
					channel->rps_flow_id[i] =
						RPS_FLOW_ID_INVALID;
		पूर्ण

		अगर (!success) अणु
			ef4_क्रम_each_channel(channel, efx)
				kमुक्त(channel->rps_flow_id);
			efx->type->filter_table_हटाओ(efx);
			rc = -ENOMEM;
			जाओ out_unlock;
		पूर्ण

		efx->rps_expire_index = efx->rps_expire_channel = 0;
	पूर्ण
#पूर्ण_अगर
out_unlock:
	up_ग_लिखो(&efx->filter_sem);
	mutex_unlock(&efx->mac_lock);
	वापस rc;
पूर्ण

अटल व्योम ef4_हटाओ_filters(काष्ठा ef4_nic *efx)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा ef4_channel *channel;

	ef4_क्रम_each_channel(channel, efx)
		kमुक्त(channel->rps_flow_id);
#पूर्ण_अगर
	करोwn_ग_लिखो(&efx->filter_sem);
	efx->type->filter_table_हटाओ(efx);
	up_ग_लिखो(&efx->filter_sem);
पूर्ण

अटल व्योम ef4_restore_filters(काष्ठा ef4_nic *efx)
अणु
	करोwn_पढ़ो(&efx->filter_sem);
	efx->type->filter_table_restore(efx);
	up_पढ़ो(&efx->filter_sem);
पूर्ण

/**************************************************************************
 *
 * NIC startup/shutकरोwn
 *
 *************************************************************************/

अटल पूर्णांक ef4_probe_all(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	rc = ef4_probe_nic(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev, "failed to create NIC\n");
		जाओ fail1;
	पूर्ण

	rc = ef4_probe_port(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev, "failed to create port\n");
		जाओ fail2;
	पूर्ण

	BUILD_BUG_ON(EF4_DEFAULT_DMAQ_SIZE < EF4_RXQ_MIN_ENT);
	अगर (WARN_ON(EF4_DEFAULT_DMAQ_SIZE < EF4_TXQ_MIN_ENT(efx))) अणु
		rc = -EINVAL;
		जाओ fail3;
	पूर्ण
	efx->rxq_entries = efx->txq_entries = EF4_DEFAULT_DMAQ_SIZE;

	rc = ef4_probe_filters(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to create filter tables\n");
		जाओ fail4;
	पूर्ण

	rc = ef4_probe_channels(efx);
	अगर (rc)
		जाओ fail5;

	वापस 0;

 fail5:
	ef4_हटाओ_filters(efx);
 fail4:
 fail3:
	ef4_हटाओ_port(efx);
 fail2:
	ef4_हटाओ_nic(efx);
 fail1:
	वापस rc;
पूर्ण

/* If the पूर्णांकerface is supposed to be running but is not, start
 * the hardware and software data path, regular activity क्रम the port
 * (MAC statistics, link polling, etc.) and schedule the port to be
 * reconfigured.  Interrupts must alपढ़ोy be enabled.  This function
 * is safe to call multiple बार, so दीर्घ as the NIC is not disabled.
 * Requires the RTNL lock.
 */
अटल व्योम ef4_start_all(काष्ठा ef4_nic *efx)
अणु
	EF4_ASSERT_RESET_SERIALISED(efx);
	BUG_ON(efx->state == STATE_DISABLED);

	/* Check that it is appropriate to restart the पूर्णांकerface. All
	 * of these flags are safe to पढ़ो under just the rtnl lock */
	अगर (efx->port_enabled || !netअगर_running(efx->net_dev) ||
	    efx->reset_pending)
		वापस;

	ef4_start_port(efx);
	ef4_start_datapath(efx);

	/* Start the hardware monitor अगर there is one */
	अगर (efx->type->monitor != शून्य)
		queue_delayed_work(efx->workqueue, &efx->monitor_work,
				   ef4_monitor_पूर्णांकerval);

	efx->type->start_stats(efx);
	efx->type->pull_stats(efx);
	spin_lock_bh(&efx->stats_lock);
	efx->type->update_stats(efx, शून्य, शून्य);
	spin_unlock_bh(&efx->stats_lock);
पूर्ण

/* Quiesce the hardware and software data path, and regular activity
 * क्रम the port without bringing the link करोwn.  Safe to call multiple
 * बार with the NIC in almost any state, but पूर्णांकerrupts should be
 * enabled.  Requires the RTNL lock.
 */
अटल व्योम ef4_stop_all(काष्ठा ef4_nic *efx)
अणु
	EF4_ASSERT_RESET_SERIALISED(efx);

	/* port_enabled can be पढ़ो safely under the rtnl lock */
	अगर (!efx->port_enabled)
		वापस;

	/* update stats beक्रमe we go करोwn so we can accurately count
	 * rx_nodesc_drops
	 */
	efx->type->pull_stats(efx);
	spin_lock_bh(&efx->stats_lock);
	efx->type->update_stats(efx, शून्य, शून्य);
	spin_unlock_bh(&efx->stats_lock);
	efx->type->stop_stats(efx);
	ef4_stop_port(efx);

	/* Stop the kernel transmit पूर्णांकerface.  This is only valid अगर
	 * the device is stopped or detached; otherwise the watchकरोg
	 * may fire immediately.
	 */
	WARN_ON(netअगर_running(efx->net_dev) &&
		netअगर_device_present(efx->net_dev));
	netअगर_tx_disable(efx->net_dev);

	ef4_stop_datapath(efx);
पूर्ण

अटल व्योम ef4_हटाओ_all(काष्ठा ef4_nic *efx)
अणु
	ef4_हटाओ_channels(efx);
	ef4_हटाओ_filters(efx);
	ef4_हटाओ_port(efx);
	ef4_हटाओ_nic(efx);
पूर्ण

/**************************************************************************
 *
 * Interrupt moderation
 *
 **************************************************************************/
अचिन्हित पूर्णांक ef4_usecs_to_ticks(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक usecs)
अणु
	अगर (usecs == 0)
		वापस 0;
	अगर (usecs * 1000 < efx->समयr_quantum_ns)
		वापस 1; /* never round करोwn to 0 */
	वापस usecs * 1000 / efx->समयr_quantum_ns;
पूर्ण

अचिन्हित पूर्णांक ef4_ticks_to_usecs(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक ticks)
अणु
	/* We must round up when converting ticks to microseconds
	 * because we round करोwn when converting the other way.
	 */
	वापस DIV_ROUND_UP(ticks * efx->समयr_quantum_ns, 1000);
पूर्ण

/* Set पूर्णांकerrupt moderation parameters */
पूर्णांक ef4_init_irq_moderation(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक tx_usecs,
			    अचिन्हित पूर्णांक rx_usecs, bool rx_adaptive,
			    bool rx_may_override_tx)
अणु
	काष्ठा ef4_channel *channel;
	अचिन्हित पूर्णांक समयr_max_us;

	EF4_ASSERT_RESET_SERIALISED(efx);

	समयr_max_us = efx->समयr_max_ns / 1000;

	अगर (tx_usecs > समयr_max_us || rx_usecs > समयr_max_us)
		वापस -EINVAL;

	अगर (tx_usecs != rx_usecs && efx->tx_channel_offset == 0 &&
	    !rx_may_override_tx) अणु
		netअगर_err(efx, drv, efx->net_dev, "Channels are shared. "
			  "RX and TX IRQ moderation must be equal\n");
		वापस -EINVAL;
	पूर्ण

	efx->irq_rx_adaptive = rx_adaptive;
	efx->irq_rx_moderation_us = rx_usecs;
	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (ef4_channel_has_rx_queue(channel))
			channel->irq_moderation_us = rx_usecs;
		अन्यथा अगर (ef4_channel_has_tx_queues(channel))
			channel->irq_moderation_us = tx_usecs;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ef4_get_irq_moderation(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक *tx_usecs,
			    अचिन्हित पूर्णांक *rx_usecs, bool *rx_adaptive)
अणु
	*rx_adaptive = efx->irq_rx_adaptive;
	*rx_usecs = efx->irq_rx_moderation_us;

	/* If channels are shared between RX and TX, so is IRQ
	 * moderation.  Otherwise, IRQ moderation is the same क्रम all
	 * TX channels and is not adaptive.
	 */
	अगर (efx->tx_channel_offset == 0) अणु
		*tx_usecs = *rx_usecs;
	पूर्ण अन्यथा अणु
		काष्ठा ef4_channel *tx_channel;

		tx_channel = efx->channel[efx->tx_channel_offset];
		*tx_usecs = tx_channel->irq_moderation_us;
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * Hardware monitor
 *
 **************************************************************************/

/* Run periodically off the general workqueue */
अटल व्योम ef4_monitor(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा ef4_nic *efx = container_of(data, काष्ठा ef4_nic,
					   monitor_work.work);

	netअगर_vdbg(efx, समयr, efx->net_dev,
		   "hardware monitor executing on CPU %d\n",
		   raw_smp_processor_id());
	BUG_ON(efx->type->monitor == शून्य);

	/* If the mac_lock is alपढ़ोy held then it is likely a port
	 * reconfiguration is alपढ़ोy in place, which will likely करो
	 * most of the work of monitor() anyway. */
	अगर (mutex_trylock(&efx->mac_lock)) अणु
		अगर (efx->port_enabled)
			efx->type->monitor(efx);
		mutex_unlock(&efx->mac_lock);
	पूर्ण

	queue_delayed_work(efx->workqueue, &efx->monitor_work,
			   ef4_monitor_पूर्णांकerval);
पूर्ण

/**************************************************************************
 *
 * ioctls
 *
 *************************************************************************/

/* Net device ioctl
 * Context: process, rtnl_lock() held.
 */
अटल पूर्णांक ef4_ioctl(काष्ठा net_device *net_dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	/* Convert phy_id from older PRTAD/DEVAD क्रमmat */
	अगर ((cmd == SIOCGMIIREG || cmd == SIOCSMIIREG) &&
	    (data->phy_id & 0xfc00) == 0x0400)
		data->phy_id ^= MDIO_PHY_ID_C45 | 0x0400;

	वापस mdio_mii_ioctl(&efx->mdio, data, cmd);
पूर्ण

/**************************************************************************
 *
 * NAPI पूर्णांकerface
 *
 **************************************************************************/

अटल व्योम ef4_init_napi_channel(काष्ठा ef4_channel *channel)
अणु
	काष्ठा ef4_nic *efx = channel->efx;

	channel->napi_dev = efx->net_dev;
	netअगर_napi_add(channel->napi_dev, &channel->napi_str,
		       ef4_poll, napi_weight);
पूर्ण

अटल व्योम ef4_init_napi(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;

	ef4_क्रम_each_channel(channel, efx)
		ef4_init_napi_channel(channel);
पूर्ण

अटल व्योम ef4_fini_napi_channel(काष्ठा ef4_channel *channel)
अणु
	अगर (channel->napi_dev)
		netअगर_napi_del(&channel->napi_str);

	channel->napi_dev = शून्य;
पूर्ण

अटल व्योम ef4_fini_napi(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_channel *channel;

	ef4_क्रम_each_channel(channel, efx)
		ef4_fini_napi_channel(channel);
पूर्ण

/**************************************************************************
 *
 * Kernel net device पूर्णांकerface
 *
 *************************************************************************/

/* Context: process, rtnl_lock() held. */
पूर्णांक ef4_net_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	netअगर_dbg(efx, अगरup, efx->net_dev, "opening device on CPU %d\n",
		  raw_smp_processor_id());

	rc = ef4_check_disabled(efx);
	अगर (rc)
		वापस rc;
	अगर (efx->phy_mode & PHY_MODE_SPECIAL)
		वापस -EBUSY;

	/* Notअगरy the kernel of the link state polled during driver load,
	 * beक्रमe the monitor starts running */
	ef4_link_status_changed(efx);

	ef4_start_all(efx);
	ef4_selftest_async_start(efx);
	वापस 0;
पूर्ण

/* Context: process, rtnl_lock() held.
 * Note that the kernel will ignore our वापस code; this method
 * should really be a व्योम.
 */
पूर्णांक ef4_net_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	netअगर_dbg(efx, अगरकरोwn, efx->net_dev, "closing on CPU %d\n",
		  raw_smp_processor_id());

	/* Stop the device and flush all the channels */
	ef4_stop_all(efx);

	वापस 0;
पूर्ण

/* Context: process, dev_base_lock or RTNL held, non-blocking. */
अटल व्योम ef4_net_stats(काष्ठा net_device *net_dev,
			  काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	spin_lock_bh(&efx->stats_lock);
	efx->type->update_stats(efx, शून्य, stats);
	spin_unlock_bh(&efx->stats_lock);
पूर्ण

/* Context: netअगर_tx_lock held, BHs disabled. */
अटल व्योम ef4_watchकरोg(काष्ठा net_device *net_dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	netअगर_err(efx, tx_err, efx->net_dev,
		  "TX stuck with port_enabled=%d: resetting channels\n",
		  efx->port_enabled);

	ef4_schedule_reset(efx, RESET_TYPE_TX_WATCHDOG);
पूर्ण


/* Context: process, rtnl_lock() held. */
अटल पूर्णांक ef4_change_mtu(काष्ठा net_device *net_dev, पूर्णांक new_mtu)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	rc = ef4_check_disabled(efx);
	अगर (rc)
		वापस rc;

	netअगर_dbg(efx, drv, efx->net_dev, "changing MTU to %d\n", new_mtu);

	ef4_device_detach_sync(efx);
	ef4_stop_all(efx);

	mutex_lock(&efx->mac_lock);
	net_dev->mtu = new_mtu;
	ef4_mac_reconfigure(efx);
	mutex_unlock(&efx->mac_lock);

	ef4_start_all(efx);
	netअगर_device_attach(efx->net_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक ef4_set_mac_address(काष्ठा net_device *net_dev, व्योम *data)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा sockaddr *addr = data;
	u8 *new_addr = addr->sa_data;
	u8 old_addr[6];
	पूर्णांक rc;

	अगर (!is_valid_ether_addr(new_addr)) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "invalid ethernet MAC address requested: %pM\n",
			  new_addr);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	/* save old address */
	ether_addr_copy(old_addr, net_dev->dev_addr);
	ether_addr_copy(net_dev->dev_addr, new_addr);
	अगर (efx->type->set_mac_address) अणु
		rc = efx->type->set_mac_address(efx);
		अगर (rc) अणु
			ether_addr_copy(net_dev->dev_addr, old_addr);
			वापस rc;
		पूर्ण
	पूर्ण

	/* Reconfigure the MAC */
	mutex_lock(&efx->mac_lock);
	ef4_mac_reconfigure(efx);
	mutex_unlock(&efx->mac_lock);

	वापस 0;
पूर्ण

/* Context: netअगर_addr_lock held, BHs disabled. */
अटल व्योम ef4_set_rx_mode(काष्ठा net_device *net_dev)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	अगर (efx->port_enabled)
		queue_work(efx->workqueue, &efx->mac_work);
	/* Otherwise ef4_start_port() will करो this */
पूर्ण

अटल पूर्णांक ef4_set_features(काष्ठा net_device *net_dev, netdev_features_t data)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	/* If disabling RX n-tuple filtering, clear existing filters */
	अगर (net_dev->features & ~data & NETIF_F_NTUPLE) अणु
		rc = efx->type->filter_clear_rx(efx, EF4_FILTER_PRI_MANUAL);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* If Rx VLAN filter is changed, update filters via mac_reconfigure */
	अगर ((net_dev->features ^ data) & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		/* ef4_set_rx_mode() will schedule MAC work to update filters
		 * when a new features are finally set in net_dev.
		 */
		ef4_set_rx_mode(net_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ef4_netdev_ops = अणु
	.nकरो_खोलो		= ef4_net_खोलो,
	.nकरो_stop		= ef4_net_stop,
	.nकरो_get_stats64	= ef4_net_stats,
	.nकरो_tx_समयout		= ef4_watchकरोg,
	.nकरो_start_xmit		= ef4_hard_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= ef4_ioctl,
	.nकरो_change_mtu		= ef4_change_mtu,
	.nकरो_set_mac_address	= ef4_set_mac_address,
	.nकरो_set_rx_mode	= ef4_set_rx_mode,
	.nकरो_set_features	= ef4_set_features,
	.nकरो_setup_tc		= ef4_setup_tc,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= ef4_filter_rfs,
#पूर्ण_अगर
पूर्ण;

अटल व्योम ef4_update_name(काष्ठा ef4_nic *efx)
अणु
	म_नकल(efx->name, efx->net_dev->name);
	ef4_mtd_नाम(efx);
	ef4_set_channel_names(efx);
पूर्ण

अटल पूर्णांक ef4_netdev_event(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *net_dev = netdev_notअगरier_info_to_dev(ptr);

	अगर ((net_dev->netdev_ops == &ef4_netdev_ops) &&
	    event == NETDEV_CHANGENAME)
		ef4_update_name(netdev_priv(net_dev));

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ef4_netdev_notअगरier = अणु
	.notअगरier_call = ef4_netdev_event,
पूर्ण;

अटल sमाप_प्रकार
show_phy_type(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ef4_nic *efx = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", efx->phy_type);
पूर्ण
अटल DEVICE_ATTR(phy_type, 0444, show_phy_type, शून्य);

अटल पूर्णांक ef4_रेजिस्टर_netdev(काष्ठा ef4_nic *efx)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा ef4_channel *channel;
	पूर्णांक rc;

	net_dev->watchकरोg_समयo = 5 * HZ;
	net_dev->irq = efx->pci_dev->irq;
	net_dev->netdev_ops = &ef4_netdev_ops;
	net_dev->ethtool_ops = &ef4_ethtool_ops;
	net_dev->gso_max_segs = EF4_TSO_MAX_SEGS;
	net_dev->min_mtu = EF4_MIN_MTU;
	net_dev->max_mtu = EF4_MAX_MTU;

	rtnl_lock();

	/* Enable resets to be scheduled and check whether any were
	 * alपढ़ोy requested.  If so, the NIC is probably hosed so we
	 * पात.
	 */
	efx->state = STATE_READY;
	smp_mb(); /* ensure we change state beक्रमe checking reset_pending */
	अगर (efx->reset_pending) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "aborting probe due to scheduled reset\n");
		rc = -EIO;
		जाओ fail_locked;
	पूर्ण

	rc = dev_alloc_name(net_dev, net_dev->name);
	अगर (rc < 0)
		जाओ fail_locked;
	ef4_update_name(efx);

	/* Always start with carrier off; PHY events will detect the link */
	netअगर_carrier_off(net_dev);

	rc = रेजिस्टर_netdevice(net_dev);
	अगर (rc)
		जाओ fail_locked;

	ef4_क्रम_each_channel(channel, efx) अणु
		काष्ठा ef4_tx_queue *tx_queue;
		ef4_क्रम_each_channel_tx_queue(tx_queue, channel)
			ef4_init_tx_queue_core_txq(tx_queue);
	पूर्ण

	ef4_associate(efx);

	rtnl_unlock();

	rc = device_create_file(&efx->pci_dev->dev, &dev_attr_phy_type);
	अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "failed to init net dev attributes\n");
		जाओ fail_रेजिस्टरed;
	पूर्ण
	वापस 0;

fail_रेजिस्टरed:
	rtnl_lock();
	ef4_dissociate(efx);
	unरेजिस्टर_netdevice(net_dev);
fail_locked:
	efx->state = STATE_UNINIT;
	rtnl_unlock();
	netअगर_err(efx, drv, efx->net_dev, "could not register net dev\n");
	वापस rc;
पूर्ण

अटल व्योम ef4_unरेजिस्टर_netdev(काष्ठा ef4_nic *efx)
अणु
	अगर (!efx->net_dev)
		वापस;

	BUG_ON(netdev_priv(efx->net_dev) != efx);

	अगर (ef4_dev_रेजिस्टरed(efx)) अणु
		strlcpy(efx->name, pci_name(efx->pci_dev), माप(efx->name));
		device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_phy_type);
		unरेजिस्टर_netdev(efx->net_dev);
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * Device reset and suspend
 *
 **************************************************************************/

/* Tears करोwn the entire software state and most of the hardware state
 * beक्रमe reset.  */
व्योम ef4_reset_करोwn(काष्ठा ef4_nic *efx, क्रमागत reset_type method)
अणु
	EF4_ASSERT_RESET_SERIALISED(efx);

	ef4_stop_all(efx);
	ef4_disable_पूर्णांकerrupts(efx);

	mutex_lock(&efx->mac_lock);
	अगर (efx->port_initialized && method != RESET_TYPE_INVISIBLE &&
	    method != RESET_TYPE_DATAPATH)
		efx->phy_op->fini(efx);
	efx->type->fini(efx);
पूर्ण

/* This function will always ensure that the locks acquired in
 * ef4_reset_करोwn() are released. A failure वापस code indicates
 * that we were unable to reinitialise the hardware, and the
 * driver should be disabled. If ok is false, then the rx and tx
 * engines are not restarted, pending a RESET_DISABLE. */
पूर्णांक ef4_reset_up(काष्ठा ef4_nic *efx, क्रमागत reset_type method, bool ok)
अणु
	पूर्णांक rc;

	EF4_ASSERT_RESET_SERIALISED(efx);

	/* Ensure that SRAM is initialised even अगर we're disabling the device */
	rc = efx->type->init(efx);
	अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev, "failed to initialise NIC\n");
		जाओ fail;
	पूर्ण

	अगर (!ok)
		जाओ fail;

	अगर (efx->port_initialized && method != RESET_TYPE_INVISIBLE &&
	    method != RESET_TYPE_DATAPATH) अणु
		rc = efx->phy_op->init(efx);
		अगर (rc)
			जाओ fail;
		rc = efx->phy_op->reconfigure(efx);
		अगर (rc && rc != -EPERM)
			netअगर_err(efx, drv, efx->net_dev,
				  "could not restore PHY settings\n");
	पूर्ण

	rc = ef4_enable_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail;

	करोwn_पढ़ो(&efx->filter_sem);
	ef4_restore_filters(efx);
	up_पढ़ो(&efx->filter_sem);

	mutex_unlock(&efx->mac_lock);

	ef4_start_all(efx);

	वापस 0;

fail:
	efx->port_initialized = false;

	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

/* Reset the NIC using the specअगरied method.  Note that the reset may
 * fail, in which हाल the card will be left in an unusable state.
 *
 * Caller must hold the rtnl_lock.
 */
पूर्णांक ef4_reset(काष्ठा ef4_nic *efx, क्रमागत reset_type method)
अणु
	पूर्णांक rc, rc2;
	bool disabled;

	netअगर_info(efx, drv, efx->net_dev, "resetting (%s)\n",
		   RESET_TYPE(method));

	ef4_device_detach_sync(efx);
	ef4_reset_करोwn(efx, method);

	rc = efx->type->reset(efx, method);
	अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev, "failed to reset hardware\n");
		जाओ out;
	पूर्ण

	/* Clear flags क्रम the scopes we covered.  We assume the NIC and
	 * driver are now quiescent so that there is no race here.
	 */
	अगर (method < RESET_TYPE_MAX_METHOD)
		efx->reset_pending &= -(1 << (method + 1));
	अन्यथा /* it करोesn't fit पूर्णांकo the well-ordered scope hierarchy */
		__clear_bit(method, &efx->reset_pending);

	/* Reinitialise bus-mastering, which may have been turned off beक्रमe
	 * the reset was scheduled. This is still appropriate, even in the
	 * RESET_TYPE_DISABLE since this driver generally assumes the hardware
	 * can respond to requests. */
	pci_set_master(efx->pci_dev);

out:
	/* Leave device stopped अगर necessary */
	disabled = rc ||
		method == RESET_TYPE_DISABLE ||
		method == RESET_TYPE_RECOVER_OR_DISABLE;
	rc2 = ef4_reset_up(efx, method, !disabled);
	अगर (rc2) अणु
		disabled = true;
		अगर (!rc)
			rc = rc2;
	पूर्ण

	अगर (disabled) अणु
		dev_बंद(efx->net_dev);
		netअगर_err(efx, drv, efx->net_dev, "has been disabled\n");
		efx->state = STATE_DISABLED;
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, drv, efx->net_dev, "reset complete\n");
		netअगर_device_attach(efx->net_dev);
	पूर्ण
	वापस rc;
पूर्ण

/* Try recovery mechanisms.
 * For now only EEH is supported.
 * Returns 0 अगर the recovery mechanisms are unsuccessful.
 * Returns a non-zero value otherwise.
 */
पूर्णांक ef4_try_recovery(काष्ठा ef4_nic *efx)
अणु
#अगर_घोषित CONFIG_EEH
	/* A PCI error can occur and not be seen by EEH because nothing
	 * happens on the PCI bus. In this हाल the driver may fail and
	 * schedule a 'recover or reset', leading to this recovery handler.
	 * Manually call the eeh failure check function.
	 */
	काष्ठा eeh_dev *eehdev = pci_dev_to_eeh_dev(efx->pci_dev);
	अगर (eeh_dev_check_failure(eehdev)) अणु
		/* The EEH mechanisms will handle the error and reset the
		 * device अगर necessary.
		 */
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* The worker thपढ़ो exists so that code that cannot sleep can
 * schedule a reset क्रम later.
 */
अटल व्योम ef4_reset_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा ef4_nic *efx = container_of(data, काष्ठा ef4_nic, reset_work);
	अचिन्हित दीर्घ pending;
	क्रमागत reset_type method;

	pending = READ_ONCE(efx->reset_pending);
	method = fls(pending) - 1;

	अगर ((method == RESET_TYPE_RECOVER_OR_DISABLE ||
	     method == RESET_TYPE_RECOVER_OR_ALL) &&
	    ef4_try_recovery(efx))
		वापस;

	अगर (!pending)
		वापस;

	rtnl_lock();

	/* We checked the state in ef4_schedule_reset() but it may
	 * have changed by now.  Now that we have the RTNL lock,
	 * it cannot change again.
	 */
	अगर (efx->state == STATE_READY)
		(व्योम)ef4_reset(efx, method);

	rtnl_unlock();
पूर्ण

व्योम ef4_schedule_reset(काष्ठा ef4_nic *efx, क्रमागत reset_type type)
अणु
	क्रमागत reset_type method;

	अगर (efx->state == STATE_RECOVERY) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "recovering: skip scheduling %s reset\n",
			  RESET_TYPE(type));
		वापस;
	पूर्ण

	चयन (type) अणु
	हाल RESET_TYPE_INVISIBLE:
	हाल RESET_TYPE_ALL:
	हाल RESET_TYPE_RECOVER_OR_ALL:
	हाल RESET_TYPE_WORLD:
	हाल RESET_TYPE_DISABLE:
	हाल RESET_TYPE_RECOVER_OR_DISABLE:
	हाल RESET_TYPE_DATAPATH:
		method = type;
		netअगर_dbg(efx, drv, efx->net_dev, "scheduling %s reset\n",
			  RESET_TYPE(method));
		अवरोध;
	शेष:
		method = efx->type->map_reset_reason(type);
		netअगर_dbg(efx, drv, efx->net_dev,
			  "scheduling %s reset for %s\n",
			  RESET_TYPE(method), RESET_TYPE(type));
		अवरोध;
	पूर्ण

	set_bit(method, &efx->reset_pending);
	smp_mb(); /* ensure we change reset_pending beक्रमe checking state */

	/* If we're not READY then just leave the flags set as the cue
	 * to पात probing or reschedule the reset later.
	 */
	अगर (READ_ONCE(efx->state) != STATE_READY)
		वापस;

	queue_work(reset_workqueue, &efx->reset_work);
पूर्ण

/**************************************************************************
 *
 * List of NICs we support
 *
 **************************************************************************/

/* PCI device ID table */
अटल स्थिर काष्ठा pci_device_id ef4_pci_table[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE,
		    PCI_DEVICE_ID_SOLARFLARE_SFC4000A_0),
	 .driver_data = (अचिन्हित दीर्घ) &falcon_a1_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE,
		    PCI_DEVICE_ID_SOLARFLARE_SFC4000B),
	 .driver_data = (अचिन्हित दीर्घ) &falcon_b0_nic_typeपूर्ण,
	अणु0पूर्ण			/* end of list */
पूर्ण;

/**************************************************************************
 *
 * Dummy PHY/MAC operations
 *
 * Can be used क्रम some unimplemented operations
 * Needed so all function poपूर्णांकers are valid and करो not have to be tested
 * beक्रमe use
 *
 **************************************************************************/
पूर्णांक ef4_port_dummy_op_पूर्णांक(काष्ठा ef4_nic *efx)
अणु
	वापस 0;
पूर्ण
व्योम ef4_port_dummy_op_व्योम(काष्ठा ef4_nic *efx) अणुपूर्ण

अटल bool ef4_port_dummy_op_poll(काष्ठा ef4_nic *efx)
अणु
	वापस false;
पूर्ण

अटल स्थिर काष्ठा ef4_phy_operations ef4_dummy_phy_operations = अणु
	.init		 = ef4_port_dummy_op_पूर्णांक,
	.reconfigure	 = ef4_port_dummy_op_पूर्णांक,
	.poll		 = ef4_port_dummy_op_poll,
	.fini		 = ef4_port_dummy_op_व्योम,
पूर्ण;

/**************************************************************************
 *
 * Data housekeeping
 *
 **************************************************************************/

/* This zeroes out and then fills in the invariants in a काष्ठा
 * ef4_nic (including all sub-काष्ठाures).
 */
अटल पूर्णांक ef4_init_काष्ठा(काष्ठा ef4_nic *efx,
			   काष्ठा pci_dev *pci_dev, काष्ठा net_device *net_dev)
अणु
	पूर्णांक i;

	/* Initialise common काष्ठाures */
	INIT_LIST_HEAD(&efx->node);
	INIT_LIST_HEAD(&efx->secondary_list);
	spin_lock_init(&efx->biu_lock);
#अगर_घोषित CONFIG_SFC_FALCON_MTD
	INIT_LIST_HEAD(&efx->mtd_list);
#पूर्ण_अगर
	INIT_WORK(&efx->reset_work, ef4_reset_work);
	INIT_DELAYED_WORK(&efx->monitor_work, ef4_monitor);
	INIT_DELAYED_WORK(&efx->selftest_work, ef4_selftest_async_work);
	efx->pci_dev = pci_dev;
	efx->msg_enable = debug;
	efx->state = STATE_UNINIT;
	strlcpy(efx->name, pci_name(pci_dev), माप(efx->name));

	efx->net_dev = net_dev;
	efx->rx_prefix_size = efx->type->rx_prefix_size;
	efx->rx_ip_align =
		NET_IP_ALIGN ? (efx->rx_prefix_size + NET_IP_ALIGN) % 4 : 0;
	efx->rx_packet_hash_offset =
		efx->type->rx_hash_offset - efx->type->rx_prefix_size;
	efx->rx_packet_ts_offset =
		efx->type->rx_ts_offset - efx->type->rx_prefix_size;
	spin_lock_init(&efx->stats_lock);
	mutex_init(&efx->mac_lock);
	efx->phy_op = &ef4_dummy_phy_operations;
	efx->mdio.dev = net_dev;
	INIT_WORK(&efx->mac_work, ef4_mac_work);
	init_रुकोqueue_head(&efx->flush_wq);

	क्रम (i = 0; i < EF4_MAX_CHANNELS; i++) अणु
		efx->channel[i] = ef4_alloc_channel(efx, i, शून्य);
		अगर (!efx->channel[i])
			जाओ fail;
		efx->msi_context[i].efx = efx;
		efx->msi_context[i].index = i;
	पूर्ण

	/* Higher numbered पूर्णांकerrupt modes are less capable! */
	efx->पूर्णांकerrupt_mode = max(efx->type->max_पूर्णांकerrupt_mode,
				  पूर्णांकerrupt_mode);

	/* Would be good to use the net_dev name, but we're too early */
	snम_लिखो(efx->workqueue_name, माप(efx->workqueue_name), "sfc%s",
		 pci_name(pci_dev));
	efx->workqueue = create_singlethपढ़ो_workqueue(efx->workqueue_name);
	अगर (!efx->workqueue)
		जाओ fail;

	वापस 0;

fail:
	ef4_fini_काष्ठा(efx);
	वापस -ENOMEM;
पूर्ण

अटल व्योम ef4_fini_काष्ठा(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < EF4_MAX_CHANNELS; i++)
		kमुक्त(efx->channel[i]);

	kमुक्त(efx->vpd_sn);

	अगर (efx->workqueue) अणु
		destroy_workqueue(efx->workqueue);
		efx->workqueue = शून्य;
	पूर्ण
पूर्ण

व्योम ef4_update_sw_stats(काष्ठा ef4_nic *efx, u64 *stats)
अणु
	u64 n_rx_nodesc_trunc = 0;
	काष्ठा ef4_channel *channel;

	ef4_क्रम_each_channel(channel, efx)
		n_rx_nodesc_trunc += channel->n_rx_nodesc_trunc;
	stats[GENERIC_STAT_rx_nodesc_trunc] = n_rx_nodesc_trunc;
	stats[GENERIC_STAT_rx_noskb_drops] = atomic_पढ़ो(&efx->n_rx_noskb_drops);
पूर्ण

/**************************************************************************
 *
 * PCI पूर्णांकerface
 *
 **************************************************************************/

/* Main body of final NIC shutकरोwn code
 * This is called only at module unload (or hotplug removal).
 */
अटल व्योम ef4_pci_हटाओ_मुख्य(काष्ठा ef4_nic *efx)
अणु
	/* Flush reset_work. It can no दीर्घer be scheduled since we
	 * are not READY.
	 */
	BUG_ON(efx->state == STATE_READY);
	cancel_work_sync(&efx->reset_work);

	ef4_disable_पूर्णांकerrupts(efx);
	ef4_nic_fini_पूर्णांकerrupt(efx);
	ef4_fini_port(efx);
	efx->type->fini(efx);
	ef4_fini_napi(efx);
	ef4_हटाओ_all(efx);
पूर्ण

/* Final NIC shutकरोwn
 * This is called only at module unload (or hotplug removal).  A PF can call
 * this on its VFs to ensure they are unbound first.
 */
अटल व्योम ef4_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा ef4_nic *efx;

	efx = pci_get_drvdata(pci_dev);
	अगर (!efx)
		वापस;

	/* Mark the NIC as fini, then stop the पूर्णांकerface */
	rtnl_lock();
	ef4_dissociate(efx);
	dev_बंद(efx->net_dev);
	ef4_disable_पूर्णांकerrupts(efx);
	efx->state = STATE_UNINIT;
	rtnl_unlock();

	ef4_unरेजिस्टर_netdev(efx);

	ef4_mtd_हटाओ(efx);

	ef4_pci_हटाओ_मुख्य(efx);

	ef4_fini_io(efx);
	netअगर_dbg(efx, drv, efx->net_dev, "shutdown successful\n");

	ef4_fini_काष्ठा(efx);
	मुक्त_netdev(efx->net_dev);

	pci_disable_pcie_error_reporting(pci_dev);
पूर्ण;

/* NIC VPD inक्रमmation
 * Called during probe to display the part number of the
 * installed NIC.  VPD is potentially very large but this should
 * always appear within the first 512 bytes.
 */
#घोषणा SFC_VPD_LEN 512
अटल व्योम ef4_probe_vpd_strings(काष्ठा ef4_nic *efx)
अणु
	काष्ठा pci_dev *dev = efx->pci_dev;
	अक्षर vpd_data[SFC_VPD_LEN];
	sमाप_प्रकार vpd_size;
	पूर्णांक ro_start, ro_size, i, j;

	/* Get the vpd data from the device */
	vpd_size = pci_पढ़ो_vpd(dev, 0, माप(vpd_data), vpd_data);
	अगर (vpd_size <= 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "Unable to read VPD\n");
		वापस;
	पूर्ण

	/* Get the Read only section */
	ro_start = pci_vpd_find_tag(vpd_data, vpd_size, PCI_VPD_LRDT_RO_DATA);
	अगर (ro_start < 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "VPD Read-only not found\n");
		वापस;
	पूर्ण

	ro_size = pci_vpd_lrdt_size(&vpd_data[ro_start]);
	j = ro_size;
	i = ro_start + PCI_VPD_LRDT_TAG_SIZE;
	अगर (i + j > vpd_size)
		j = vpd_size - i;

	/* Get the Part number */
	i = pci_vpd_find_info_keyword(vpd_data, i, j, "PN");
	अगर (i < 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "Part number not found\n");
		वापस;
	पूर्ण

	j = pci_vpd_info_field_size(&vpd_data[i]);
	i += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (i + j > vpd_size) अणु
		netअगर_err(efx, drv, efx->net_dev, "Incomplete part number\n");
		वापस;
	पूर्ण

	netअगर_info(efx, drv, efx->net_dev,
		   "Part Number : %.*s\n", j, &vpd_data[i]);

	i = ro_start + PCI_VPD_LRDT_TAG_SIZE;
	j = ro_size;
	i = pci_vpd_find_info_keyword(vpd_data, i, j, "SN");
	अगर (i < 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "Serial number not found\n");
		वापस;
	पूर्ण

	j = pci_vpd_info_field_size(&vpd_data[i]);
	i += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (i + j > vpd_size) अणु
		netअगर_err(efx, drv, efx->net_dev, "Incomplete serial number\n");
		वापस;
	पूर्ण

	efx->vpd_sn = kदो_स्मृति(j + 1, GFP_KERNEL);
	अगर (!efx->vpd_sn)
		वापस;

	snम_लिखो(efx->vpd_sn, j + 1, "%s", &vpd_data[i]);
पूर्ण


/* Main body of NIC initialisation
 * This is called at module load (or hotplug insertion, theoretically).
 */
अटल पूर्णांक ef4_pci_probe_मुख्य(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	/* Do start-of-day initialisation */
	rc = ef4_probe_all(efx);
	अगर (rc)
		जाओ fail1;

	ef4_init_napi(efx);

	rc = efx->type->init(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to initialise NIC\n");
		जाओ fail3;
	पूर्ण

	rc = ef4_init_port(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to initialise port\n");
		जाओ fail4;
	पूर्ण

	rc = ef4_nic_init_पूर्णांकerrupt(efx);
	अगर (rc)
		जाओ fail5;
	rc = ef4_enable_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail6;

	वापस 0;

 fail6:
	ef4_nic_fini_पूर्णांकerrupt(efx);
 fail5:
	ef4_fini_port(efx);
 fail4:
	efx->type->fini(efx);
 fail3:
	ef4_fini_napi(efx);
	ef4_हटाओ_all(efx);
 fail1:
	वापस rc;
पूर्ण

/* NIC initialisation
 *
 * This is called at module load (or hotplug insertion,
 * theoretically).  It sets up PCI mappings, resets the NIC,
 * sets up and रेजिस्टरs the network devices with the kernel and hooks
 * the पूर्णांकerrupt service routine.  It करोes not prepare the device क्रम
 * transmission; this is left to the first समय one of the network
 * पूर्णांकerfaces is brought up (i.e. ef4_net_खोलो).
 */
अटल पूर्णांक ef4_pci_probe(काष्ठा pci_dev *pci_dev,
			 स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा net_device *net_dev;
	काष्ठा ef4_nic *efx;
	पूर्णांक rc;

	/* Allocate and initialise a काष्ठा net_device and काष्ठा ef4_nic */
	net_dev = alloc_etherdev_mqs(माप(*efx), EF4_MAX_CORE_TX_QUEUES,
				     EF4_MAX_RX_QUEUES);
	अगर (!net_dev)
		वापस -ENOMEM;
	efx = netdev_priv(net_dev);
	efx->type = (स्थिर काष्ठा ef4_nic_type *) entry->driver_data;
	efx->fixed_features |= NETIF_F_HIGHDMA;

	pci_set_drvdata(pci_dev, efx);
	SET_NETDEV_DEV(net_dev, &pci_dev->dev);
	rc = ef4_init_काष्ठा(efx, pci_dev, net_dev);
	अगर (rc)
		जाओ fail1;

	netअगर_info(efx, probe, efx->net_dev,
		   "Solarflare NIC detected\n");

	ef4_probe_vpd_strings(efx);

	/* Set up basic I/O (BAR mappings etc) */
	rc = ef4_init_io(efx);
	अगर (rc)
		जाओ fail2;

	rc = ef4_pci_probe_मुख्य(efx);
	अगर (rc)
		जाओ fail3;

	net_dev->features |= (efx->type->offload_features | NETIF_F_SG |
			      NETIF_F_RXCSUM);
	/* Mask क्रम features that also apply to VLAN devices */
	net_dev->vlan_features |= (NETIF_F_HW_CSUM | NETIF_F_SG |
				   NETIF_F_HIGHDMA | NETIF_F_RXCSUM);

	net_dev->hw_features = net_dev->features & ~efx->fixed_features;

	/* Disable VLAN filtering by शेष.  It may be enक्रमced अगर
	 * the feature is fixed (i.e. VLAN filters are required to
	 * receive VLAN tagged packets due to vPort restrictions).
	 */
	net_dev->features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
	net_dev->features |= efx->fixed_features;

	rc = ef4_रेजिस्टर_netdev(efx);
	अगर (rc)
		जाओ fail4;

	netअगर_dbg(efx, probe, efx->net_dev, "initialisation successful\n");

	/* Try to create MTDs, but allow this to fail */
	rtnl_lock();
	rc = ef4_mtd_probe(efx);
	rtnl_unlock();
	अगर (rc && rc != -EPERM)
		netअगर_warn(efx, probe, efx->net_dev,
			   "failed to create MTDs (%d)\n", rc);

	rc = pci_enable_pcie_error_reporting(pci_dev);
	अगर (rc && rc != -EINVAL)
		netअगर_notice(efx, probe, efx->net_dev,
			     "PCIE error reporting unavailable (%d).\n",
			     rc);

	वापस 0;

 fail4:
	ef4_pci_हटाओ_मुख्य(efx);
 fail3:
	ef4_fini_io(efx);
 fail2:
	ef4_fini_काष्ठा(efx);
 fail1:
	WARN_ON(rc > 0);
	netअगर_dbg(efx, drv, efx->net_dev, "initialisation failed. rc=%d\n", rc);
	मुक्त_netdev(net_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक ef4_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा ef4_nic *efx = dev_get_drvdata(dev);

	rtnl_lock();

	अगर (efx->state != STATE_DISABLED) अणु
		efx->state = STATE_UNINIT;

		ef4_device_detach_sync(efx);

		ef4_stop_all(efx);
		ef4_disable_पूर्णांकerrupts(efx);
	पूर्ण

	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक ef4_pm_thaw(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा ef4_nic *efx = dev_get_drvdata(dev);

	rtnl_lock();

	अगर (efx->state != STATE_DISABLED) अणु
		rc = ef4_enable_पूर्णांकerrupts(efx);
		अगर (rc)
			जाओ fail;

		mutex_lock(&efx->mac_lock);
		efx->phy_op->reconfigure(efx);
		mutex_unlock(&efx->mac_lock);

		ef4_start_all(efx);

		netअगर_device_attach(efx->net_dev);

		efx->state = STATE_READY;

		efx->type->resume_wol(efx);
	पूर्ण

	rtnl_unlock();

	/* Reschedule any quenched resets scheduled during ef4_pm_मुक्तze() */
	queue_work(reset_workqueue, &efx->reset_work);

	वापस 0;

fail:
	rtnl_unlock();

	वापस rc;
पूर्ण

अटल पूर्णांक ef4_pm_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा ef4_nic *efx = pci_get_drvdata(pci_dev);

	efx->type->fini(efx);

	efx->reset_pending = 0;

	pci_save_state(pci_dev);
	वापस pci_set_घातer_state(pci_dev, PCI_D3hot);
पूर्ण

/* Used क्रम both resume and restore */
अटल पूर्णांक ef4_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा ef4_nic *efx = pci_get_drvdata(pci_dev);
	पूर्णांक rc;

	rc = pci_set_घातer_state(pci_dev, PCI_D0);
	अगर (rc)
		वापस rc;
	pci_restore_state(pci_dev);
	rc = pci_enable_device(pci_dev);
	अगर (rc)
		वापस rc;
	pci_set_master(efx->pci_dev);
	rc = efx->type->reset(efx, RESET_TYPE_ALL);
	अगर (rc)
		वापस rc;
	rc = efx->type->init(efx);
	अगर (rc)
		वापस rc;
	rc = ef4_pm_thaw(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक ef4_pm_suspend(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	ef4_pm_मुक्तze(dev);
	rc = ef4_pm_घातeroff(dev);
	अगर (rc)
		ef4_pm_resume(dev);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ef4_pm_ops = अणु
	.suspend	= ef4_pm_suspend,
	.resume		= ef4_pm_resume,
	.मुक्तze		= ef4_pm_मुक्तze,
	.thaw		= ef4_pm_thaw,
	.घातeroff	= ef4_pm_घातeroff,
	.restore	= ef4_pm_resume,
पूर्ण;

/* A PCI error affecting this device was detected.
 * At this poपूर्णांक MMIO and DMA may be disabled.
 * Stop the software path and request a slot reset.
 */
अटल pci_ers_result_t ef4_io_error_detected(काष्ठा pci_dev *pdev,
					      pci_channel_state_t state)
अणु
	pci_ers_result_t status = PCI_ERS_RESULT_RECOVERED;
	काष्ठा ef4_nic *efx = pci_get_drvdata(pdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	rtnl_lock();

	अगर (efx->state != STATE_DISABLED) अणु
		efx->state = STATE_RECOVERY;
		efx->reset_pending = 0;

		ef4_device_detach_sync(efx);

		ef4_stop_all(efx);
		ef4_disable_पूर्णांकerrupts(efx);

		status = PCI_ERS_RESULT_NEED_RESET;
	पूर्ण अन्यथा अणु
		/* If the पूर्णांकerface is disabled we करोn't want to करो anything
		 * with it.
		 */
		status = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	rtnl_unlock();

	pci_disable_device(pdev);

	वापस status;
पूर्ण

/* Fake a successful reset, which will be perक्रमmed later in ef4_io_resume. */
अटल pci_ers_result_t ef4_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ef4_nic *efx = pci_get_drvdata(pdev);
	pci_ers_result_t status = PCI_ERS_RESULT_RECOVERED;

	अगर (pci_enable_device(pdev)) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "Cannot re-enable PCI device after reset.\n");
		status =  PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस status;
पूर्ण

/* Perक्रमm the actual reset and resume I/O operations. */
अटल व्योम ef4_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ef4_nic *efx = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rtnl_lock();

	अगर (efx->state == STATE_DISABLED)
		जाओ out;

	rc = ef4_reset(efx, RESET_TYPE_ALL);
	अगर (rc) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "ef4_reset failed after PCI error (%d)\n", rc);
	पूर्ण अन्यथा अणु
		efx->state = STATE_READY;
		netअगर_dbg(efx, hw, efx->net_dev,
			  "Done resetting and resuming IO after PCI error.\n");
	पूर्ण

out:
	rtnl_unlock();
पूर्ण

/* For simplicity and reliability, we always require a slot reset and try to
 * reset the hardware when a pci error affecting the device is detected.
 * We leave both the link_reset and mmio_enabled callback unimplemented:
 * with our request क्रम slot reset the mmio_enabled callback will never be
 * called, and the link_reset callback is not used by AER or EEH mechanisms.
 */
अटल स्थिर काष्ठा pci_error_handlers ef4_err_handlers = अणु
	.error_detected = ef4_io_error_detected,
	.slot_reset	= ef4_io_slot_reset,
	.resume		= ef4_io_resume,
पूर्ण;

अटल काष्ठा pci_driver ef4_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= ef4_pci_table,
	.probe		= ef4_pci_probe,
	.हटाओ		= ef4_pci_हटाओ,
	.driver.pm	= &ef4_pm_ops,
	.err_handler	= &ef4_err_handlers,
पूर्ण;

/**************************************************************************
 *
 * Kernel module पूर्णांकerface
 *
 *************************************************************************/

module_param(पूर्णांकerrupt_mode, uपूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांकerrupt_mode,
		 "Interrupt mode (0=>MSIX 1=>MSI 2=>legacy)");

अटल पूर्णांक __init ef4_init_module(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO "Solarflare Falcon driver v" EF4_DRIVER_VERSION "\n");

	rc = रेजिस्टर_netdevice_notअगरier(&ef4_netdev_notअगरier);
	अगर (rc)
		जाओ err_notअगरier;

	reset_workqueue = create_singlethपढ़ो_workqueue("sfc_reset");
	अगर (!reset_workqueue) अणु
		rc = -ENOMEM;
		जाओ err_reset;
	पूर्ण

	rc = pci_रेजिस्टर_driver(&ef4_pci_driver);
	अगर (rc < 0)
		जाओ err_pci;

	वापस 0;

 err_pci:
	destroy_workqueue(reset_workqueue);
 err_reset:
	unरेजिस्टर_netdevice_notअगरier(&ef4_netdev_notअगरier);
 err_notअगरier:
	वापस rc;
पूर्ण

अटल व्योम __निकास ef4_निकास_module(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Solarflare Falcon driver unloading\n");

	pci_unरेजिस्टर_driver(&ef4_pci_driver);
	destroy_workqueue(reset_workqueue);
	unरेजिस्टर_netdevice_notअगरier(&ef4_netdev_notअगरier);

पूर्ण

module_init(ef4_init_module);
module_निकास(ef4_निकास_module);

MODULE_AUTHOR("Solarflare Communications and "
	      "Michael Brown <mbrown@fensystems.co.uk>");
MODULE_DESCRIPTION("Solarflare Falcon network driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ef4_pci_table);
MODULE_VERSION(EF4_DRIVER_VERSION);
