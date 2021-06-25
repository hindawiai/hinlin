<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "net_driver.h"
#समावेश <linux/module.h>
#समावेश "efx_channels.h"
#समावेश "efx.h"
#समावेश "efx_common.h"
#समावेश "tx_common.h"
#समावेश "rx_common.h"
#समावेश "nic.h"
#समावेश "sriov.h"
#समावेश "workarounds.h"

/* This is the first पूर्णांकerrupt mode to try out of:
 * 0 => MSI-X
 * 1 => MSI
 * 2 => legacy
 */
अचिन्हित पूर्णांक efx_पूर्णांकerrupt_mode = EFX_INT_MODE_MSIX;

/* This is the requested number of CPUs to use क्रम Receive-Side Scaling (RSS),
 * i.e. the number of CPUs among which we may distribute simultaneous
 * पूर्णांकerrupt handling.
 *
 * Cards without MSI-X will only target one CPU via legacy or MSI पूर्णांकerrupt.
 * The शेष (0) means to assign an पूर्णांकerrupt to each core.
 */
अचिन्हित पूर्णांक rss_cpus;

अटल अचिन्हित पूर्णांक irq_adapt_low_thresh = 8000;
module_param(irq_adapt_low_thresh, uपूर्णांक, 0644);
MODULE_PARM_DESC(irq_adapt_low_thresh,
		 "Threshold score for reducing IRQ moderation");

अटल अचिन्हित पूर्णांक irq_adapt_high_thresh = 16000;
module_param(irq_adapt_high_thresh, uपूर्णांक, 0644);
MODULE_PARM_DESC(irq_adapt_high_thresh,
		 "Threshold score for increasing IRQ moderation");

/* This is the weight asचिन्हित to each of the (per-channel) भव
 * NAPI devices.
 */
अटल पूर्णांक napi_weight = 64;

/***************
 * Housekeeping
 ***************/

पूर्णांक efx_channel_dummy_op_पूर्णांक(काष्ठा efx_channel *channel)
अणु
	वापस 0;
पूर्ण

व्योम efx_channel_dummy_op_व्योम(काष्ठा efx_channel *channel)
अणु
पूर्ण

अटल स्थिर काष्ठा efx_channel_type efx_शेष_channel_type = अणु
	.pre_probe		= efx_channel_dummy_op_पूर्णांक,
	.post_हटाओ		= efx_channel_dummy_op_व्योम,
	.get_name		= efx_get_channel_name,
	.copy			= efx_copy_channel,
	.want_txqs		= efx_शेष_channel_want_txqs,
	.keep_eventq		= false,
	.want_pio		= true,
पूर्ण;

/*************
 * INTERRUPTS
 *************/

अटल अचिन्हित पूर्णांक efx_wanted_parallelism(काष्ठा efx_nic *efx)
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

	अगर (count > EFX_MAX_RX_QUEUES) अणु
		netअगर_cond_dbg(efx, probe, efx->net_dev, !rss_cpus, warn,
			       "Reducing number of rx queues from %u to %u.\n",
			       count, EFX_MAX_RX_QUEUES);
		count = EFX_MAX_RX_QUEUES;
	पूर्ण

	/* If RSS is requested क्रम the PF *and* VFs then we can't ग_लिखो RSS
	 * table entries that are inaccessible to VFs
	 */
#अगर_घोषित CONFIG_SFC_SRIOV
	अगर (efx->type->sriov_wanted) अणु
		अगर (efx->type->sriov_wanted(efx) && efx_vf_size(efx) > 1 &&
		    count > efx_vf_size(efx)) अणु
			netअगर_warn(efx, probe, efx->net_dev,
				   "Reducing number of RSS channels from %u to %u for "
				   "VF support. Increase vf-msix-limit to use more "
				   "channels on the PF.\n",
				   count, efx_vf_size(efx));
			count = efx_vf_size(efx);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस count;
पूर्ण

अटल पूर्णांक efx_allocate_msix_channels(काष्ठा efx_nic *efx,
				      अचिन्हित पूर्णांक max_channels,
				      अचिन्हित पूर्णांक extra_channels,
				      अचिन्हित पूर्णांक parallelism)
अणु
	अचिन्हित पूर्णांक n_channels = parallelism;
	पूर्णांक vec_count;
	पूर्णांक tx_per_ev;
	पूर्णांक n_xdp_tx;
	पूर्णांक n_xdp_ev;

	अगर (efx_separate_tx_channels)
		n_channels *= 2;
	n_channels += extra_channels;

	/* To allow XDP transmit to happen from arbitrary NAPI contexts
	 * we allocate a TX queue per CPU. We share event queues across
	 * multiple tx queues, assuming tx and ev queues are both
	 * maximum size.
	 */
	tx_per_ev = EFX_MAX_EVQ_SIZE / EFX_TXQ_MAX_ENT(efx);
	n_xdp_tx = num_possible_cpus();
	n_xdp_ev = DIV_ROUND_UP(n_xdp_tx, tx_per_ev);

	vec_count = pci_msix_vec_count(efx->pci_dev);
	अगर (vec_count < 0)
		वापस vec_count;

	max_channels = min_t(अचिन्हित पूर्णांक, vec_count, max_channels);

	/* Check resources.
	 * We need a channel per event queue, plus a VI per tx queue.
	 * This may be more pessimistic than it needs to be.
	 */
	अगर (n_channels + n_xdp_ev > max_channels) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Insufficient resources for %d XDP event queues (%d other channels, max %d)\n",
			  n_xdp_ev, n_channels, max_channels);
		efx->n_xdp_channels = 0;
		efx->xdp_tx_per_channel = 0;
		efx->xdp_tx_queue_count = 0;
	पूर्ण अन्यथा अगर (n_channels + n_xdp_tx > efx->max_vis) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Insufficient resources for %d XDP TX queues (%d other channels, max VIs %d)\n",
			  n_xdp_tx, n_channels, efx->max_vis);
		efx->n_xdp_channels = 0;
		efx->xdp_tx_per_channel = 0;
		efx->xdp_tx_queue_count = 0;
	पूर्ण अन्यथा अणु
		efx->n_xdp_channels = n_xdp_ev;
		efx->xdp_tx_per_channel = EFX_MAX_TXQ_PER_CHANNEL;
		efx->xdp_tx_queue_count = n_xdp_tx;
		n_channels += n_xdp_ev;
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Allocating %d TX and %d event queues for XDP\n",
			  n_xdp_tx, n_xdp_ev);
	पूर्ण

	अगर (vec_count < n_channels) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "WARNING: Insufficient MSI-X vectors available (%d < %u).\n",
			  vec_count, n_channels);
		netअगर_err(efx, drv, efx->net_dev,
			  "WARNING: Performance may be reduced.\n");
		n_channels = vec_count;
	पूर्ण

	n_channels = min(n_channels, max_channels);

	efx->n_channels = n_channels;

	/* Ignore XDP tx channels when creating rx channels. */
	n_channels -= efx->n_xdp_channels;

	अगर (efx_separate_tx_channels) अणु
		efx->n_tx_channels =
			min(max(n_channels / 2, 1U),
			    efx->max_tx_channels);
		efx->tx_channel_offset =
			n_channels - efx->n_tx_channels;
		efx->n_rx_channels =
			max(n_channels -
			    efx->n_tx_channels, 1U);
	पूर्ण अन्यथा अणु
		efx->n_tx_channels = min(n_channels, efx->max_tx_channels);
		efx->tx_channel_offset = 0;
		efx->n_rx_channels = n_channels;
	पूर्ण

	efx->n_rx_channels = min(efx->n_rx_channels, parallelism);
	efx->n_tx_channels = min(efx->n_tx_channels, parallelism);

	efx->xdp_channel_offset = n_channels;

	netअगर_dbg(efx, drv, efx->net_dev,
		  "Allocating %u RX channels\n",
		  efx->n_rx_channels);

	वापस efx->n_channels;
पूर्ण

/* Probe the number and type of पूर्णांकerrupts we are able to obtain, and
 * the resulting numbers of channels and RX queues.
 */
पूर्णांक efx_probe_पूर्णांकerrupts(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक extra_channels = 0;
	अचिन्हित पूर्णांक rss_spपढ़ो;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक rc;

	क्रम (i = 0; i < EFX_MAX_EXTRA_CHANNELS; i++)
		अगर (efx->extra_channel_type[i])
			++extra_channels;

	अगर (efx->पूर्णांकerrupt_mode == EFX_INT_MODE_MSIX) अणु
		अचिन्हित पूर्णांक parallelism = efx_wanted_parallelism(efx);
		काष्ठा msix_entry xentries[EFX_MAX_CHANNELS];
		अचिन्हित पूर्णांक n_channels;

		rc = efx_allocate_msix_channels(efx, efx->max_channels,
						extra_channels, parallelism);
		अगर (rc >= 0) अणु
			n_channels = rc;
			क्रम (i = 0; i < n_channels; i++)
				xentries[i].entry = i;
			rc = pci_enable_msix_range(efx->pci_dev, xentries, 1,
						   n_channels);
		पूर्ण
		अगर (rc < 0) अणु
			/* Fall back to single channel MSI */
			netअगर_err(efx, drv, efx->net_dev,
				  "could not enable MSI-X\n");
			अगर (efx->type->min_पूर्णांकerrupt_mode >= EFX_INT_MODE_MSI)
				efx->पूर्णांकerrupt_mode = EFX_INT_MODE_MSI;
			अन्यथा
				वापस rc;
		पूर्ण अन्यथा अगर (rc < n_channels) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "WARNING: Insufficient MSI-X vectors"
				  " available (%d < %u).\n", rc, n_channels);
			netअगर_err(efx, drv, efx->net_dev,
				  "WARNING: Performance may be reduced.\n");
			n_channels = rc;
		पूर्ण

		अगर (rc > 0) अणु
			क्रम (i = 0; i < efx->n_channels; i++)
				efx_get_channel(efx, i)->irq =
					xentries[i].vector;
		पूर्ण
	पूर्ण

	/* Try single पूर्णांकerrupt MSI */
	अगर (efx->पूर्णांकerrupt_mode == EFX_INT_MODE_MSI) अणु
		efx->n_channels = 1;
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		efx->n_xdp_channels = 0;
		efx->xdp_channel_offset = efx->n_channels;
		rc = pci_enable_msi(efx->pci_dev);
		अगर (rc == 0) अणु
			efx_get_channel(efx, 0)->irq = efx->pci_dev->irq;
		पूर्ण अन्यथा अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "could not enable MSI\n");
			अगर (efx->type->min_पूर्णांकerrupt_mode >= EFX_INT_MODE_LEGACY)
				efx->पूर्णांकerrupt_mode = EFX_INT_MODE_LEGACY;
			अन्यथा
				वापस rc;
		पूर्ण
	पूर्ण

	/* Assume legacy पूर्णांकerrupts */
	अगर (efx->पूर्णांकerrupt_mode == EFX_INT_MODE_LEGACY) अणु
		efx->n_channels = 1 + (efx_separate_tx_channels ? 1 : 0);
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		efx->n_xdp_channels = 0;
		efx->xdp_channel_offset = efx->n_channels;
		efx->legacy_irq = efx->pci_dev->irq;
	पूर्ण

	/* Assign extra channels अगर possible, beक्रमe XDP channels */
	efx->n_extra_tx_channels = 0;
	j = efx->xdp_channel_offset;
	क्रम (i = 0; i < EFX_MAX_EXTRA_CHANNELS; i++) अणु
		अगर (!efx->extra_channel_type[i])
			जारी;
		अगर (j <= efx->tx_channel_offset + efx->n_tx_channels) अणु
			efx->extra_channel_type[i]->handle_no_channel(efx);
		पूर्ण अन्यथा अणु
			--j;
			efx_get_channel(efx, j)->type =
				efx->extra_channel_type[i];
			अगर (efx_channel_has_tx_queues(efx_get_channel(efx, j)))
				efx->n_extra_tx_channels++;
		पूर्ण
	पूर्ण

	rss_spपढ़ो = efx->n_rx_channels;
	/* RSS might be usable on VFs even अगर it is disabled on the PF */
#अगर_घोषित CONFIG_SFC_SRIOV
	अगर (efx->type->sriov_wanted) अणु
		efx->rss_spपढ़ो = ((rss_spपढ़ो > 1 ||
				    !efx->type->sriov_wanted(efx)) ?
				   rss_spपढ़ो : efx_vf_size(efx));
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	efx->rss_spपढ़ो = rss_spपढ़ो;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_SMP)
व्योम efx_set_पूर्णांकerrupt_affinity(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक cpu;

	efx_क्रम_each_channel(channel, efx) अणु
		cpu = cpumask_local_spपढ़ो(channel->channel,
					   pcibus_to_node(efx->pci_dev->bus));
		irq_set_affinity_hपूर्णांक(channel->irq, cpumask_of(cpu));
	पूर्ण
पूर्ण

व्योम efx_clear_पूर्णांकerrupt_affinity(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx)
		irq_set_affinity_hपूर्णांक(channel->irq, शून्य);
पूर्ण
#अन्यथा
व्योम
efx_set_पूर्णांकerrupt_affinity(काष्ठा efx_nic *efx __attribute__ ((unused)))
अणु
पूर्ण

व्योम
efx_clear_पूर्णांकerrupt_affinity(काष्ठा efx_nic *efx __attribute__ ((unused)))
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

व्योम efx_हटाओ_पूर्णांकerrupts(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	/* Remove MSI/MSI-X पूर्णांकerrupts */
	efx_क्रम_each_channel(channel, efx)
		channel->irq = 0;
	pci_disable_msi(efx->pci_dev);
	pci_disable_msix(efx->pci_dev);

	/* Remove legacy पूर्णांकerrupt */
	efx->legacy_irq = 0;
पूर्ण

/***************
 * EVENT QUEUES
 ***************/

/* Create event queue
 * Event queue memory allocations are करोne only once.  If the channel
 * is reset, the memory buffer will be reused; this guards against
 * errors during channel reset and also simplअगरies पूर्णांकerrupt handling.
 */
पूर्णांक efx_probe_eventq(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	अचिन्हित दीर्घ entries;

	netअगर_dbg(efx, probe, efx->net_dev,
		  "chan %d create event queue\n", channel->channel);

	/* Build an event queue with room क्रम one event per tx and rx buffer,
	 * plus some extra क्रम link state events and MCDI completions.
	 */
	entries = roundup_घात_of_two(efx->rxq_entries + efx->txq_entries + 128);
	EFX_WARN_ON_PARANOID(entries > EFX_MAX_EVQ_SIZE);
	channel->eventq_mask = max(entries, EFX_MIN_EVQ_SIZE) - 1;

	वापस efx_nic_probe_eventq(channel);
पूर्ण

/* Prepare channel's event queue */
पूर्णांक efx_init_eventq(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	पूर्णांक rc;

	EFX_WARN_ON_PARANOID(channel->eventq_init);

	netअगर_dbg(efx, drv, efx->net_dev,
		  "chan %d init event queue\n", channel->channel);

	rc = efx_nic_init_eventq(channel);
	अगर (rc == 0) अणु
		efx->type->push_irq_moderation(channel);
		channel->eventq_पढ़ो_ptr = 0;
		channel->eventq_init = true;
	पूर्ण
	वापस rc;
पूर्ण

/* Enable event queue processing and NAPI */
व्योम efx_start_eventq(काष्ठा efx_channel *channel)
अणु
	netअगर_dbg(channel->efx, अगरup, channel->efx->net_dev,
		  "chan %d start event queue\n", channel->channel);

	/* Make sure the NAPI handler sees the enabled flag set */
	channel->enabled = true;
	smp_wmb();

	napi_enable(&channel->napi_str);
	efx_nic_eventq_पढ़ो_ack(channel);
पूर्ण

/* Disable event queue processing and NAPI */
व्योम efx_stop_eventq(काष्ठा efx_channel *channel)
अणु
	अगर (!channel->enabled)
		वापस;

	napi_disable(&channel->napi_str);
	channel->enabled = false;
पूर्ण

व्योम efx_fini_eventq(काष्ठा efx_channel *channel)
अणु
	अगर (!channel->eventq_init)
		वापस;

	netअगर_dbg(channel->efx, drv, channel->efx->net_dev,
		  "chan %d fini event queue\n", channel->channel);

	efx_nic_fini_eventq(channel);
	channel->eventq_init = false;
पूर्ण

व्योम efx_हटाओ_eventq(काष्ठा efx_channel *channel)
अणु
	netअगर_dbg(channel->efx, drv, channel->efx->net_dev,
		  "chan %d remove event queue\n", channel->channel);

	efx_nic_हटाओ_eventq(channel);
पूर्ण

/**************************************************************************
 *
 * Channel handling
 *
 *************************************************************************/

#अगर_घोषित CONFIG_RFS_ACCEL
अटल व्योम efx_filter_rfs_expire(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(data);
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक समय, quota;

	channel = container_of(dwork, काष्ठा efx_channel, filter_work);
	समय = jअगरfies - channel->rfs_last_expiry;
	quota = channel->rfs_filter_count * समय / (30 * HZ);
	अगर (quota >= 20 && __efx_filter_rfs_expire(channel, min(channel->rfs_filter_count, quota)))
		channel->rfs_last_expiry += समय;
	/* Ensure we करो more work eventually even अगर NAPI poll is not happening */
	schedule_delayed_work(dwork, 30 * HZ);
पूर्ण
#पूर्ण_अगर

/* Allocate and initialise a channel काष्ठाure. */
अटल काष्ठा efx_channel *efx_alloc_channel(काष्ठा efx_nic *efx, पूर्णांक i)
अणु
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_channel *channel;
	पूर्णांक j;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस शून्य;

	channel->efx = efx;
	channel->channel = i;
	channel->type = &efx_शेष_channel_type;

	क्रम (j = 0; j < EFX_MAX_TXQ_PER_CHANNEL; j++) अणु
		tx_queue = &channel->tx_queue[j];
		tx_queue->efx = efx;
		tx_queue->queue = -1;
		tx_queue->label = j;
		tx_queue->channel = channel;
	पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
	INIT_DELAYED_WORK(&channel->filter_work, efx_filter_rfs_expire);
#पूर्ण_अगर

	rx_queue = &channel->rx_queue;
	rx_queue->efx = efx;
	समयr_setup(&rx_queue->slow_fill, efx_rx_slow_fill, 0);

	वापस channel;
पूर्ण

पूर्णांक efx_init_channels(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EFX_MAX_CHANNELS; i++) अणु
		efx->channel[i] = efx_alloc_channel(efx, i);
		अगर (!efx->channel[i])
			वापस -ENOMEM;
		efx->msi_context[i].efx = efx;
		efx->msi_context[i].index = i;
	पूर्ण

	/* Higher numbered पूर्णांकerrupt modes are less capable! */
	efx->पूर्णांकerrupt_mode = min(efx->type->min_पूर्णांकerrupt_mode,
				  efx_पूर्णांकerrupt_mode);

	efx->max_channels = EFX_MAX_CHANNELS;
	efx->max_tx_channels = EFX_MAX_CHANNELS;

	वापस 0;
पूर्ण

व्योम efx_fini_channels(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EFX_MAX_CHANNELS; i++)
		अगर (efx->channel[i]) अणु
			kमुक्त(efx->channel[i]);
			efx->channel[i] = शून्य;
		पूर्ण
पूर्ण

/* Allocate and initialise a channel काष्ठाure, copying parameters
 * (but not resources) from an old channel काष्ठाure.
 */
काष्ठा efx_channel *efx_copy_channel(स्थिर काष्ठा efx_channel *old_channel)
अणु
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_channel *channel;
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

	क्रम (j = 0; j < EFX_MAX_TXQ_PER_CHANNEL; j++) अणु
		tx_queue = &channel->tx_queue[j];
		अगर (tx_queue->channel)
			tx_queue->channel = channel;
		tx_queue->buffer = शून्य;
		tx_queue->cb_page = शून्य;
		स_रखो(&tx_queue->txd, 0, माप(tx_queue->txd));
	पूर्ण

	rx_queue = &channel->rx_queue;
	rx_queue->buffer = शून्य;
	स_रखो(&rx_queue->rxd, 0, माप(rx_queue->rxd));
	समयr_setup(&rx_queue->slow_fill, efx_rx_slow_fill, 0);
#अगर_घोषित CONFIG_RFS_ACCEL
	INIT_DELAYED_WORK(&channel->filter_work, efx_filter_rfs_expire);
#पूर्ण_अगर

	वापस channel;
पूर्ण

अटल पूर्णांक efx_probe_channel(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_rx_queue *rx_queue;
	पूर्णांक rc;

	netअगर_dbg(channel->efx, probe, channel->efx->net_dev,
		  "creating channel %d\n", channel->channel);

	rc = channel->type->pre_probe(channel);
	अगर (rc)
		जाओ fail;

	rc = efx_probe_eventq(channel);
	अगर (rc)
		जाओ fail;

	efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		rc = efx_probe_tx_queue(tx_queue);
		अगर (rc)
			जाओ fail;
	पूर्ण

	efx_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
		rc = efx_probe_rx_queue(rx_queue);
		अगर (rc)
			जाओ fail;
	पूर्ण

	channel->rx_list = शून्य;

	वापस 0;

fail:
	efx_हटाओ_channel(channel);
	वापस rc;
पूर्ण

व्योम efx_get_channel_name(काष्ठा efx_channel *channel, अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	स्थिर अक्षर *type;
	पूर्णांक number;

	number = channel->channel;

	अगर (number >= efx->xdp_channel_offset &&
	    !WARN_ON_ONCE(!efx->n_xdp_channels)) अणु
		type = "-xdp";
		number -= efx->xdp_channel_offset;
	पूर्ण अन्यथा अगर (efx->tx_channel_offset == 0) अणु
		type = "";
	पूर्ण अन्यथा अगर (number < efx->tx_channel_offset) अणु
		type = "-rx";
	पूर्ण अन्यथा अणु
		type = "-tx";
		number -= efx->tx_channel_offset;
	पूर्ण
	snम_लिखो(buf, len, "%s%s-%d", efx->name, type, number);
पूर्ण

व्योम efx_set_channel_names(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx)
		channel->type->get_name(channel,
					efx->msi_context[channel->channel].name,
					माप(efx->msi_context[0].name));
पूर्ण

पूर्णांक efx_probe_channels(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;
	पूर्णांक rc;

	/* Restart special buffer allocation */
	efx->next_buffer_table = 0;

	/* Probe channels in reverse, so that any 'extra' channels
	 * use the start of the buffer table. This allows the traffic
	 * channels to be resized without moving them or wasting the
	 * entries beक्रमe them.
	 */
	efx_क्रम_each_channel_rev(channel, efx) अणु
		rc = efx_probe_channel(channel);
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "failed to create channel %d\n",
				  channel->channel);
			जाओ fail;
		पूर्ण
	पूर्ण
	efx_set_channel_names(efx);

	वापस 0;

fail:
	efx_हटाओ_channels(efx);
	वापस rc;
पूर्ण

व्योम efx_हटाओ_channel(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_rx_queue *rx_queue;

	netअगर_dbg(channel->efx, drv, channel->efx->net_dev,
		  "destroy chan %d\n", channel->channel);

	efx_क्रम_each_channel_rx_queue(rx_queue, channel)
		efx_हटाओ_rx_queue(rx_queue);
	efx_क्रम_each_channel_tx_queue(tx_queue, channel)
		efx_हटाओ_tx_queue(tx_queue);
	efx_हटाओ_eventq(channel);
	channel->type->post_हटाओ(channel);
पूर्ण

व्योम efx_हटाओ_channels(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx)
		efx_हटाओ_channel(channel);

	kमुक्त(efx->xdp_tx_queues);
पूर्ण

पूर्णांक efx_पुनः_स्मृति_channels(काष्ठा efx_nic *efx, u32 rxq_entries, u32 txq_entries)
अणु
	काष्ठा efx_channel *other_channel[EFX_MAX_CHANNELS], *channel;
	अचिन्हित पूर्णांक i, next_buffer_table = 0;
	u32 old_rxq_entries, old_txq_entries;
	पूर्णांक rc, rc2;

	rc = efx_check_disabled(efx);
	अगर (rc)
		वापस rc;

	/* Not all channels should be पुनः_स्मृतिated. We must aव्योम
	 * पुनः_स्मृतिating their buffer table entries.
	 */
	efx_क्रम_each_channel(channel, efx) अणु
		काष्ठा efx_rx_queue *rx_queue;
		काष्ठा efx_tx_queue *tx_queue;

		अगर (channel->type->copy)
			जारी;
		next_buffer_table = max(next_buffer_table,
					channel->eventq.index +
					channel->eventq.entries);
		efx_क्रम_each_channel_rx_queue(rx_queue, channel)
			next_buffer_table = max(next_buffer_table,
						rx_queue->rxd.index +
						rx_queue->rxd.entries);
		efx_क्रम_each_channel_tx_queue(tx_queue, channel)
			next_buffer_table = max(next_buffer_table,
						tx_queue->txd.index +
						tx_queue->txd.entries);
	पूर्ण

	efx_device_detach_sync(efx);
	efx_stop_all(efx);
	efx_soft_disable_पूर्णांकerrupts(efx);

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
		rc = efx_probe_channel(channel);
		अगर (rc)
			जाओ rollback;
		efx_init_napi_channel(efx->channel[i]);
	पूर्ण

out:
	/* Destroy unused channel काष्ठाures */
	क्रम (i = 0; i < efx->n_channels; i++) अणु
		channel = other_channel[i];
		अगर (channel && channel->type->copy) अणु
			efx_fini_napi_channel(channel);
			efx_हटाओ_channel(channel);
			kमुक्त(channel);
		पूर्ण
	पूर्ण

	rc2 = efx_soft_enable_पूर्णांकerrupts(efx);
	अगर (rc2) अणु
		rc = rc ? rc : rc2;
		netअगर_err(efx, drv, efx->net_dev,
			  "unable to restart interrupts on channel reallocation\n");
		efx_schedule_reset(efx, RESET_TYPE_DISABLE);
	पूर्ण अन्यथा अणु
		efx_start_all(efx);
		efx_device_attach_अगर_not_resetting(efx);
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

पूर्णांक efx_set_channels(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक next_queue = 0;
	पूर्णांक xdp_queue_number;
	पूर्णांक rc;

	efx->tx_channel_offset =
		efx_separate_tx_channels ?
		efx->n_channels - efx->n_tx_channels : 0;

	अगर (efx->xdp_tx_queue_count) अणु
		EFX_WARN_ON_PARANOID(efx->xdp_tx_queues);

		/* Allocate array क्रम XDP TX queue lookup. */
		efx->xdp_tx_queues = kसुस्मृति(efx->xdp_tx_queue_count,
					     माप(*efx->xdp_tx_queues),
					     GFP_KERNEL);
		अगर (!efx->xdp_tx_queues)
			वापस -ENOMEM;
	पूर्ण

	/* We need to mark which channels really have RX and TX
	 * queues, and adjust the TX queue numbers अगर we have separate
	 * RX-only and TX-only channels.
	 */
	xdp_queue_number = 0;
	efx_क्रम_each_channel(channel, efx) अणु
		अगर (channel->channel < efx->n_rx_channels)
			channel->rx_queue.core_index = channel->channel;
		अन्यथा
			channel->rx_queue.core_index = -1;

		अगर (channel->channel >= efx->tx_channel_offset) अणु
			अगर (efx_channel_is_xdp_tx(channel)) अणु
				efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
					tx_queue->queue = next_queue++;
					netअगर_dbg(efx, drv, efx->net_dev, "Channel %u TXQ %u is XDP %u, HW %u\n",
						  channel->channel, tx_queue->label,
						  xdp_queue_number, tx_queue->queue);
					/* We may have a few left-over XDP TX
					 * queues owing to xdp_tx_queue_count
					 * not भागiding evenly by EFX_MAX_TXQ_PER_CHANNEL.
					 * We still allocate and probe those
					 * TXQs, but never use them.
					 */
					अगर (xdp_queue_number < efx->xdp_tx_queue_count)
						efx->xdp_tx_queues[xdp_queue_number] = tx_queue;
					xdp_queue_number++;
				पूर्ण
			पूर्ण अन्यथा अणु
				efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
					tx_queue->queue = next_queue++;
					netअगर_dbg(efx, drv, efx->net_dev, "Channel %u TXQ %u is HW %u\n",
						  channel->channel, tx_queue->label,
						  tx_queue->queue);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (xdp_queue_number)
		efx->xdp_tx_queue_count = xdp_queue_number;

	rc = netअगर_set_real_num_tx_queues(efx->net_dev, efx->n_tx_channels);
	अगर (rc)
		वापस rc;
	वापस netअगर_set_real_num_rx_queues(efx->net_dev, efx->n_rx_channels);
पूर्ण

bool efx_शेष_channel_want_txqs(काष्ठा efx_channel *channel)
अणु
	वापस channel->channel - channel->efx->tx_channel_offset <
		channel->efx->n_tx_channels;
पूर्ण

/*************
 * START/STOP
 *************/

पूर्णांक efx_soft_enable_पूर्णांकerrupts(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel, *end_channel;
	पूर्णांक rc;

	BUG_ON(efx->state == STATE_DISABLED);

	efx->irq_soft_enabled = true;
	smp_wmb();

	efx_क्रम_each_channel(channel, efx) अणु
		अगर (!channel->type->keep_eventq) अणु
			rc = efx_init_eventq(channel);
			अगर (rc)
				जाओ fail;
		पूर्ण
		efx_start_eventq(channel);
	पूर्ण

	efx_mcdi_mode_event(efx);

	वापस 0;
fail:
	end_channel = channel;
	efx_क्रम_each_channel(channel, efx) अणु
		अगर (channel == end_channel)
			अवरोध;
		efx_stop_eventq(channel);
		अगर (!channel->type->keep_eventq)
			efx_fini_eventq(channel);
	पूर्ण

	वापस rc;
पूर्ण

व्योम efx_soft_disable_पूर्णांकerrupts(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	अगर (efx->state == STATE_DISABLED)
		वापस;

	efx_mcdi_mode_poll(efx);

	efx->irq_soft_enabled = false;
	smp_wmb();

	अगर (efx->legacy_irq)
		synchronize_irq(efx->legacy_irq);

	efx_क्रम_each_channel(channel, efx) अणु
		अगर (channel->irq)
			synchronize_irq(channel->irq);

		efx_stop_eventq(channel);
		अगर (!channel->type->keep_eventq)
			efx_fini_eventq(channel);
	पूर्ण

	/* Flush the asynchronous MCDI request queue */
	efx_mcdi_flush_async(efx);
पूर्ण

पूर्णांक efx_enable_पूर्णांकerrupts(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel, *end_channel;
	पूर्णांक rc;

	/* TODO: Is this really a bug? */
	BUG_ON(efx->state == STATE_DISABLED);

	अगर (efx->eeh_disabled_legacy_irq) अणु
		enable_irq(efx->legacy_irq);
		efx->eeh_disabled_legacy_irq = false;
	पूर्ण

	efx->type->irq_enable_master(efx);

	efx_क्रम_each_channel(channel, efx) अणु
		अगर (channel->type->keep_eventq) अणु
			rc = efx_init_eventq(channel);
			अगर (rc)
				जाओ fail;
		पूर्ण
	पूर्ण

	rc = efx_soft_enable_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail;

	वापस 0;

fail:
	end_channel = channel;
	efx_क्रम_each_channel(channel, efx) अणु
		अगर (channel == end_channel)
			अवरोध;
		अगर (channel->type->keep_eventq)
			efx_fini_eventq(channel);
	पूर्ण

	efx->type->irq_disable_non_ev(efx);

	वापस rc;
पूर्ण

व्योम efx_disable_पूर्णांकerrupts(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	efx_soft_disable_पूर्णांकerrupts(efx);

	efx_क्रम_each_channel(channel, efx) अणु
		अगर (channel->type->keep_eventq)
			efx_fini_eventq(channel);
	पूर्ण

	efx->type->irq_disable_non_ev(efx);
पूर्ण

व्योम efx_start_channels(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx) अणु
		efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
			efx_init_tx_queue(tx_queue);
			atomic_inc(&efx->active_queues);
		पूर्ण

		efx_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
			efx_init_rx_queue(rx_queue);
			atomic_inc(&efx->active_queues);
			efx_stop_eventq(channel);
			efx_fast_push_rx_descriptors(rx_queue, false);
			efx_start_eventq(channel);
		पूर्ण

		WARN_ON(channel->rx_pkt_n_frags);
	पूर्ण
पूर्ण

व्योम efx_stop_channels(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा efx_channel *channel;
	पूर्णांक rc = 0;

	/* Stop RX refill */
	efx_क्रम_each_channel(channel, efx) अणु
		efx_क्रम_each_channel_rx_queue(rx_queue, channel)
			rx_queue->refill_enabled = false;
	पूर्ण

	efx_क्रम_each_channel(channel, efx) अणु
		/* RX packet processing is pipelined, so रुको क्रम the
		 * NAPI handler to complete.  At least event queue 0
		 * might be kept active by non-data events, so करोn't
		 * use napi_synchronize() but actually disable NAPI
		 * temporarily.
		 */
		अगर (efx_channel_has_rx_queue(channel)) अणु
			efx_stop_eventq(channel);
			efx_start_eventq(channel);
		पूर्ण
	पूर्ण

	अगर (efx->type->fini_dmaq)
		rc = efx->type->fini_dmaq(efx);

	अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev, "failed to flush queues\n");
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "successfully flushed all queues\n");
	पूर्ण

	efx_क्रम_each_channel(channel, efx) अणु
		efx_क्रम_each_channel_rx_queue(rx_queue, channel)
			efx_fini_rx_queue(rx_queue);
		efx_क्रम_each_channel_tx_queue(tx_queue, channel)
			efx_fini_tx_queue(tx_queue);
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * NAPI पूर्णांकerface
 *
 *************************************************************************/

/* Process channel's event queue
 *
 * This function is responsible क्रम processing the event queue of a
 * single channel.  The caller must guarantee that this function will
 * never be concurrently called more than once on the same channel,
 * though dअगरferent channels may be being processed concurrently.
 */
अटल पूर्णांक efx_process_channel(काष्ठा efx_channel *channel, पूर्णांक budget)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा list_head rx_list;
	पूर्णांक spent;

	अगर (unlikely(!channel->enabled))
		वापस 0;

	/* Prepare the batch receive list */
	EFX_WARN_ON_PARANOID(channel->rx_list != शून्य);
	INIT_LIST_HEAD(&rx_list);
	channel->rx_list = &rx_list;

	efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		tx_queue->pkts_compl = 0;
		tx_queue->bytes_compl = 0;
	पूर्ण

	spent = efx_nic_process_eventq(channel, budget);
	अगर (spent && efx_channel_has_rx_queue(channel)) अणु
		काष्ठा efx_rx_queue *rx_queue =
			efx_channel_get_rx_queue(channel);

		efx_rx_flush_packet(channel);
		efx_fast_push_rx_descriptors(rx_queue, true);
	पूर्ण

	/* Update BQL */
	efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		अगर (tx_queue->bytes_compl) अणु
			netdev_tx_completed_queue(tx_queue->core_txq,
						  tx_queue->pkts_compl,
						  tx_queue->bytes_compl);
		पूर्ण
	पूर्ण

	/* Receive any packets we queued up */
	netअगर_receive_skb_list(channel->rx_list);
	channel->rx_list = शून्य;

	वापस spent;
पूर्ण

अटल व्योम efx_update_irq_mod(काष्ठा efx_nic *efx, काष्ठा efx_channel *channel)
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

/* NAPI poll handler
 *
 * NAPI guarantees serialisation of polls of the same device, which
 * provides the guarantee required by efx_process_channel().
 */
अटल पूर्णांक efx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा efx_channel *channel =
		container_of(napi, काष्ठा efx_channel, napi_str);
	काष्ठा efx_nic *efx = channel->efx;
#अगर_घोषित CONFIG_RFS_ACCEL
	अचिन्हित पूर्णांक समय;
#पूर्ण_अगर
	पूर्णांक spent;

	netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
		   "channel %d NAPI poll executing on CPU %d\n",
		   channel->channel, raw_smp_processor_id());

	spent = efx_process_channel(channel, budget);

	xdp_करो_flush_map();

	अगर (spent < budget) अणु
		अगर (efx_channel_has_rx_queue(channel) &&
		    efx->irq_rx_adaptive &&
		    unlikely(++channel->irq_count == 1000)) अणु
			efx_update_irq_mod(efx, channel);
		पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
		/* Perhaps expire some ARFS filters */
		समय = jअगरfies - channel->rfs_last_expiry;
		/* Would our quota be >= 20? */
		अगर (channel->rfs_filter_count * समय >= 600 * HZ)
			mod_delayed_work(प्रणाली_wq, &channel->filter_work, 0);
#पूर्ण_अगर

		/* There is no race here; although napi_disable() will
		 * only रुको क्रम napi_complete(), this isn't a problem
		 * since efx_nic_eventq_पढ़ो_ack() will have no effect अगर
		 * पूर्णांकerrupts have alपढ़ोy been disabled.
		 */
		अगर (napi_complete_करोne(napi, spent))
			efx_nic_eventq_पढ़ो_ack(channel);
	पूर्ण

	वापस spent;
पूर्ण

व्योम efx_init_napi_channel(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;

	channel->napi_dev = efx->net_dev;
	netअगर_napi_add(channel->napi_dev, &channel->napi_str,
		       efx_poll, napi_weight);
पूर्ण

व्योम efx_init_napi(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx)
		efx_init_napi_channel(channel);
पूर्ण

व्योम efx_fini_napi_channel(काष्ठा efx_channel *channel)
अणु
	अगर (channel->napi_dev)
		netअगर_napi_del(&channel->napi_str);

	channel->napi_dev = शून्य;
पूर्ण

व्योम efx_fini_napi(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx)
		efx_fini_napi_channel(channel);
पूर्ण
