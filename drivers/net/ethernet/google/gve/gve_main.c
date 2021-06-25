<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <net/sch_generic.h>
#समावेश "gve.h"
#समावेश "gve_adminq.h"
#समावेश "gve_register.h"

#घोषणा GVE_DEFAULT_RX_COPYBREAK	(256)

#घोषणा DEFAULT_MSG_LEVEL	(NETIF_MSG_DRV | NETIF_MSG_LINK)
#घोषणा GVE_VERSION		"1.0.0"
#घोषणा GVE_VERSION_PREFIX	"GVE-"

स्थिर अक्षर gve_version_str[] = GVE_VERSION;
अटल स्थिर अक्षर gve_version_prefix[] = GVE_VERSION_PREFIX;

अटल व्योम gve_get_stats(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा gve_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक start;
	पूर्णांक ring;

	अगर (priv->rx) अणु
		क्रम (ring = 0; ring < priv->rx_cfg.num_queues; ring++) अणु
			करो अणु
				start =
				  u64_stats_fetch_begin(&priv->rx[ring].statss);
				s->rx_packets += priv->rx[ring].rpackets;
				s->rx_bytes += priv->rx[ring].rbytes;
			पूर्ण जबतक (u64_stats_fetch_retry(&priv->rx[ring].statss,
						       start));
		पूर्ण
	पूर्ण
	अगर (priv->tx) अणु
		क्रम (ring = 0; ring < priv->tx_cfg.num_queues; ring++) अणु
			करो अणु
				start =
				  u64_stats_fetch_begin(&priv->tx[ring].statss);
				s->tx_packets += priv->tx[ring].pkt_करोne;
				s->tx_bytes += priv->tx[ring].bytes_करोne;
			पूर्ण जबतक (u64_stats_fetch_retry(&priv->tx[ring].statss,
						       start));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक gve_alloc_counter_array(काष्ठा gve_priv *priv)
अणु
	priv->counter_array =
		dma_alloc_coherent(&priv->pdev->dev,
				   priv->num_event_counters *
				   माप(*priv->counter_array),
				   &priv->counter_array_bus, GFP_KERNEL);
	अगर (!priv->counter_array)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम gve_मुक्त_counter_array(काष्ठा gve_priv *priv)
अणु
	dma_मुक्त_coherent(&priv->pdev->dev,
			  priv->num_event_counters *
			  माप(*priv->counter_array),
			  priv->counter_array, priv->counter_array_bus);
	priv->counter_array = शून्य;
पूर्ण

/* NIC requests to report stats */
अटल व्योम gve_stats_report_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gve_priv *priv = container_of(work, काष्ठा gve_priv,
					     stats_report_task);
	अगर (gve_get_करो_report_stats(priv)) अणु
		gve_handle_report_stats(priv);
		gve_clear_करो_report_stats(priv);
	पूर्ण
पूर्ण

अटल व्योम gve_stats_report_schedule(काष्ठा gve_priv *priv)
अणु
	अगर (!gve_get_probe_in_progress(priv) &&
	    !gve_get_reset_in_progress(priv)) अणु
		gve_set_करो_report_stats(priv);
		queue_work(priv->gve_wq, &priv->stats_report_task);
	पूर्ण
पूर्ण

अटल व्योम gve_stats_report_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा gve_priv *priv = from_समयr(priv, t, stats_report_समयr);

	mod_समयr(&priv->stats_report_समयr,
		  round_jअगरfies(jअगरfies +
		  msecs_to_jअगरfies(priv->stats_report_समयr_period)));
	gve_stats_report_schedule(priv);
पूर्ण

अटल पूर्णांक gve_alloc_stats_report(काष्ठा gve_priv *priv)
अणु
	पूर्णांक tx_stats_num, rx_stats_num;

	tx_stats_num = (GVE_TX_STATS_REPORT_NUM + NIC_TX_STATS_REPORT_NUM) *
		       priv->tx_cfg.num_queues;
	rx_stats_num = (GVE_RX_STATS_REPORT_NUM + NIC_RX_STATS_REPORT_NUM) *
		       priv->rx_cfg.num_queues;
	priv->stats_report_len = काष्ठा_size(priv->stats_report, stats,
					     tx_stats_num + rx_stats_num);
	priv->stats_report =
		dma_alloc_coherent(&priv->pdev->dev, priv->stats_report_len,
				   &priv->stats_report_bus, GFP_KERNEL);
	अगर (!priv->stats_report)
		वापस -ENOMEM;
	/* Set up समयr क्रम the report-stats task */
	समयr_setup(&priv->stats_report_समयr, gve_stats_report_समयr, 0);
	priv->stats_report_समयr_period = GVE_STATS_REPORT_TIMER_PERIOD;
	वापस 0;
पूर्ण

अटल व्योम gve_मुक्त_stats_report(काष्ठा gve_priv *priv)
अणु
	del_समयr_sync(&priv->stats_report_समयr);
	dma_मुक्त_coherent(&priv->pdev->dev, priv->stats_report_len,
			  priv->stats_report, priv->stats_report_bus);
	priv->stats_report = शून्य;
पूर्ण

अटल irqवापस_t gve_mgmnt_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा gve_priv *priv = arg;

	queue_work(priv->gve_wq, &priv->service_task);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t gve_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा gve_notअगरy_block *block = arg;
	काष्ठा gve_priv *priv = block->priv;

	ioग_लिखो32be(GVE_IRQ_MASK, gve_irq_करोorbell(priv, block));
	napi_schedule_irqoff(&block->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gve_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gve_notअगरy_block *block;
	__be32 __iomem *irq_करोorbell;
	bool reschedule = false;
	काष्ठा gve_priv *priv;

	block = container_of(napi, काष्ठा gve_notअगरy_block, napi);
	priv = block->priv;

	अगर (block->tx)
		reschedule |= gve_tx_poll(block, budget);
	अगर (block->rx)
		reschedule |= gve_rx_poll(block, budget);

	अगर (reschedule)
		वापस budget;

	napi_complete(napi);
	irq_करोorbell = gve_irq_करोorbell(priv, block);
	ioग_लिखो32be(GVE_IRQ_ACK | GVE_IRQ_EVENT, irq_करोorbell);

	/* Double check we have no extra work.
	 * Ensure unmask synchronizes with checking क्रम work.
	 */
	mb();
	अगर (block->tx)
		reschedule |= gve_tx_poll(block, -1);
	अगर (block->rx)
		reschedule |= gve_rx_poll(block, -1);
	अगर (reschedule && napi_reschedule(napi))
		ioग_लिखो32be(GVE_IRQ_MASK, irq_करोorbell);

	वापस 0;
पूर्ण

अटल पूर्णांक gve_alloc_notअगरy_blocks(काष्ठा gve_priv *priv)
अणु
	पूर्णांक num_vecs_requested = priv->num_ntfy_blks + 1;
	अक्षर *name = priv->dev->name;
	अचिन्हित पूर्णांक active_cpus;
	पूर्णांक vecs_enabled;
	पूर्णांक i, j;
	पूर्णांक err;

	priv->msix_vectors = kvzalloc(num_vecs_requested *
				      माप(*priv->msix_vectors), GFP_KERNEL);
	अगर (!priv->msix_vectors)
		वापस -ENOMEM;
	क्रम (i = 0; i < num_vecs_requested; i++)
		priv->msix_vectors[i].entry = i;
	vecs_enabled = pci_enable_msix_range(priv->pdev, priv->msix_vectors,
					     GVE_MIN_MSIX, num_vecs_requested);
	अगर (vecs_enabled < 0) अणु
		dev_err(&priv->pdev->dev, "Could not enable min msix %d/%d\n",
			GVE_MIN_MSIX, vecs_enabled);
		err = vecs_enabled;
		जाओ पात_with_msix_vectors;
	पूर्ण
	अगर (vecs_enabled != num_vecs_requested) अणु
		पूर्णांक new_num_ntfy_blks = (vecs_enabled - 1) & ~0x1;
		पूर्णांक vecs_per_type = new_num_ntfy_blks / 2;
		पूर्णांक vecs_left = new_num_ntfy_blks % 2;

		priv->num_ntfy_blks = new_num_ntfy_blks;
		priv->mgmt_msix_idx = priv->num_ntfy_blks;
		priv->tx_cfg.max_queues = min_t(पूर्णांक, priv->tx_cfg.max_queues,
						vecs_per_type);
		priv->rx_cfg.max_queues = min_t(पूर्णांक, priv->rx_cfg.max_queues,
						vecs_per_type + vecs_left);
		dev_err(&priv->pdev->dev,
			"Could not enable desired msix, only enabled %d, adjusting tx max queues to %d, and rx max queues to %d\n",
			vecs_enabled, priv->tx_cfg.max_queues,
			priv->rx_cfg.max_queues);
		अगर (priv->tx_cfg.num_queues > priv->tx_cfg.max_queues)
			priv->tx_cfg.num_queues = priv->tx_cfg.max_queues;
		अगर (priv->rx_cfg.num_queues > priv->rx_cfg.max_queues)
			priv->rx_cfg.num_queues = priv->rx_cfg.max_queues;
	पूर्ण
	/* Half the notअगरication blocks go to TX and half to RX */
	active_cpus = min_t(पूर्णांक, priv->num_ntfy_blks / 2, num_online_cpus());

	/* Setup Management Vector  - the last vector */
	snम_लिखो(priv->mgmt_msix_name, माप(priv->mgmt_msix_name), "%s-mgmnt",
		 name);
	err = request_irq(priv->msix_vectors[priv->mgmt_msix_idx].vector,
			  gve_mgmnt_पूर्णांकr, 0, priv->mgmt_msix_name, priv);
	अगर (err) अणु
		dev_err(&priv->pdev->dev, "Did not receive management vector.\n");
		जाओ पात_with_msix_enabled;
	पूर्ण
	priv->ntfy_blocks =
		dma_alloc_coherent(&priv->pdev->dev,
				   priv->num_ntfy_blks *
				   माप(*priv->ntfy_blocks),
				   &priv->ntfy_block_bus, GFP_KERNEL);
	अगर (!priv->ntfy_blocks) अणु
		err = -ENOMEM;
		जाओ पात_with_mgmt_vector;
	पूर्ण
	/* Setup the other blocks - the first n-1 vectors */
	क्रम (i = 0; i < priv->num_ntfy_blks; i++) अणु
		काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[i];
		पूर्णांक msix_idx = i;

		snम_लिखो(block->name, माप(block->name), "%s-ntfy-block.%d",
			 name, i);
		block->priv = priv;
		err = request_irq(priv->msix_vectors[msix_idx].vector,
				  gve_पूर्णांकr, 0, block->name, block);
		अगर (err) अणु
			dev_err(&priv->pdev->dev,
				"Failed to receive msix vector %d\n", i);
			जाओ पात_with_some_ntfy_blocks;
		पूर्ण
		irq_set_affinity_hपूर्णांक(priv->msix_vectors[msix_idx].vector,
				      get_cpu_mask(i % active_cpus));
	पूर्ण
	वापस 0;
पात_with_some_ntfy_blocks:
	क्रम (j = 0; j < i; j++) अणु
		काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[j];
		पूर्णांक msix_idx = j;

		irq_set_affinity_hपूर्णांक(priv->msix_vectors[msix_idx].vector,
				      शून्य);
		मुक्त_irq(priv->msix_vectors[msix_idx].vector, block);
	पूर्ण
	dma_मुक्त_coherent(&priv->pdev->dev, priv->num_ntfy_blks *
			  माप(*priv->ntfy_blocks),
			  priv->ntfy_blocks, priv->ntfy_block_bus);
	priv->ntfy_blocks = शून्य;
पात_with_mgmt_vector:
	मुक्त_irq(priv->msix_vectors[priv->mgmt_msix_idx].vector, priv);
पात_with_msix_enabled:
	pci_disable_msix(priv->pdev);
पात_with_msix_vectors:
	kvमुक्त(priv->msix_vectors);
	priv->msix_vectors = शून्य;
	वापस err;
पूर्ण

अटल व्योम gve_मुक्त_notअगरy_blocks(काष्ठा gve_priv *priv)
अणु
	पूर्णांक i;

	अगर (priv->msix_vectors) अणु
		/* Free the irqs */
		क्रम (i = 0; i < priv->num_ntfy_blks; i++) अणु
			काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[i];
			पूर्णांक msix_idx = i;

			irq_set_affinity_hपूर्णांक(priv->msix_vectors[msix_idx].vector,
					      शून्य);
			मुक्त_irq(priv->msix_vectors[msix_idx].vector, block);
		पूर्ण
		मुक्त_irq(priv->msix_vectors[priv->mgmt_msix_idx].vector, priv);
	पूर्ण
	dma_मुक्त_coherent(&priv->pdev->dev,
			  priv->num_ntfy_blks * माप(*priv->ntfy_blocks),
			  priv->ntfy_blocks, priv->ntfy_block_bus);
	priv->ntfy_blocks = शून्य;
	pci_disable_msix(priv->pdev);
	kvमुक्त(priv->msix_vectors);
	priv->msix_vectors = शून्य;
पूर्ण

अटल पूर्णांक gve_setup_device_resources(काष्ठा gve_priv *priv)
अणु
	पूर्णांक err;

	err = gve_alloc_counter_array(priv);
	अगर (err)
		वापस err;
	err = gve_alloc_notअगरy_blocks(priv);
	अगर (err)
		जाओ पात_with_counter;
	err = gve_alloc_stats_report(priv);
	अगर (err)
		जाओ पात_with_ntfy_blocks;
	err = gve_adminq_configure_device_resources(priv,
						    priv->counter_array_bus,
						    priv->num_event_counters,
						    priv->ntfy_block_bus,
						    priv->num_ntfy_blks);
	अगर (unlikely(err)) अणु
		dev_err(&priv->pdev->dev,
			"could not setup device_resources: err=%d\n", err);
		err = -ENXIO;
		जाओ पात_with_stats_report;
	पूर्ण
	err = gve_adminq_report_stats(priv, priv->stats_report_len,
				      priv->stats_report_bus,
				      GVE_STATS_REPORT_TIMER_PERIOD);
	अगर (err)
		dev_err(&priv->pdev->dev,
			"Failed to report stats: err=%d\n", err);
	gve_set_device_resources_ok(priv);
	वापस 0;
पात_with_stats_report:
	gve_मुक्त_stats_report(priv);
पात_with_ntfy_blocks:
	gve_मुक्त_notअगरy_blocks(priv);
पात_with_counter:
	gve_मुक्त_counter_array(priv);
	वापस err;
पूर्ण

अटल व्योम gve_trigger_reset(काष्ठा gve_priv *priv);

अटल व्योम gve_tearकरोwn_device_resources(काष्ठा gve_priv *priv)
अणु
	पूर्णांक err;

	/* Tell device its resources are being मुक्तd */
	अगर (gve_get_device_resources_ok(priv)) अणु
		/* detach the stats report */
		err = gve_adminq_report_stats(priv, 0, 0x0, GVE_STATS_REPORT_TIMER_PERIOD);
		अगर (err) अणु
			dev_err(&priv->pdev->dev,
				"Failed to detach stats report: err=%d\n", err);
			gve_trigger_reset(priv);
		पूर्ण
		err = gve_adminq_deconfigure_device_resources(priv);
		अगर (err) अणु
			dev_err(&priv->pdev->dev,
				"Could not deconfigure device resources: err=%d\n",
				err);
			gve_trigger_reset(priv);
		पूर्ण
	पूर्ण
	gve_मुक्त_counter_array(priv);
	gve_मुक्त_notअगरy_blocks(priv);
	gve_मुक्त_stats_report(priv);
	gve_clear_device_resources_ok(priv);
पूर्ण

अटल व्योम gve_add_napi(काष्ठा gve_priv *priv, पूर्णांक ntfy_idx)
अणु
	काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];

	netअगर_napi_add(priv->dev, &block->napi, gve_napi_poll,
		       NAPI_POLL_WEIGHT);
पूर्ण

अटल व्योम gve_हटाओ_napi(काष्ठा gve_priv *priv, पूर्णांक ntfy_idx)
अणु
	काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];

	netअगर_napi_del(&block->napi);
पूर्ण

अटल पूर्णांक gve_रेजिस्टर_qpls(काष्ठा gve_priv *priv)
अणु
	पूर्णांक num_qpls = gve_num_tx_qpls(priv) + gve_num_rx_qpls(priv);
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < num_qpls; i++) अणु
		err = gve_adminq_रेजिस्टर_page_list(priv, &priv->qpls[i]);
		अगर (err) अणु
			netअगर_err(priv, drv, priv->dev,
				  "failed to register queue page list %d\n",
				  priv->qpls[i].id);
			/* This failure will trigger a reset - no need to clean
			 * up
			 */
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gve_unरेजिस्टर_qpls(काष्ठा gve_priv *priv)
अणु
	पूर्णांक num_qpls = gve_num_tx_qpls(priv) + gve_num_rx_qpls(priv);
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < num_qpls; i++) अणु
		err = gve_adminq_unरेजिस्टर_page_list(priv, priv->qpls[i].id);
		/* This failure will trigger a reset - no need to clean up */
		अगर (err) अणु
			netअगर_err(priv, drv, priv->dev,
				  "Failed to unregister queue page list %d\n",
				  priv->qpls[i].id);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gve_create_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक err;
	पूर्णांक i;

	err = gve_adminq_create_tx_queues(priv, priv->tx_cfg.num_queues);
	अगर (err) अणु
		netअगर_err(priv, drv, priv->dev, "failed to create %d tx queues\n",
			  priv->tx_cfg.num_queues);
		/* This failure will trigger a reset - no need to clean
		 * up
		 */
		वापस err;
	पूर्ण
	netअगर_dbg(priv, drv, priv->dev, "created %d tx queues\n",
		  priv->tx_cfg.num_queues);

	err = gve_adminq_create_rx_queues(priv, priv->rx_cfg.num_queues);
	अगर (err) अणु
		netअगर_err(priv, drv, priv->dev, "failed to create %d rx queues\n",
			  priv->rx_cfg.num_queues);
		/* This failure will trigger a reset - no need to clean
		 * up
		 */
		वापस err;
	पूर्ण
	netअगर_dbg(priv, drv, priv->dev, "created %d rx queues\n",
		  priv->rx_cfg.num_queues);

	/* Rx data ring has been prefilled with packet buffers at queue
	 * allocation समय.
	 * Write the करोorbell to provide descriptor slots and packet buffers
	 * to the NIC.
	 */
	क्रम (i = 0; i < priv->rx_cfg.num_queues; i++)
		gve_rx_ग_लिखो_करोorbell(priv, &priv->rx[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक gve_alloc_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक ntfy_idx;
	पूर्णांक err;
	पूर्णांक i;

	/* Setup tx rings */
	priv->tx = kvzalloc(priv->tx_cfg.num_queues * माप(*priv->tx),
			    GFP_KERNEL);
	अगर (!priv->tx)
		वापस -ENOMEM;
	err = gve_tx_alloc_rings(priv);
	अगर (err)
		जाओ मुक्त_tx;
	/* Setup rx rings */
	priv->rx = kvzalloc(priv->rx_cfg.num_queues * माप(*priv->rx),
			    GFP_KERNEL);
	अगर (!priv->rx) अणु
		err = -ENOMEM;
		जाओ मुक्त_tx_queue;
	पूर्ण
	err = gve_rx_alloc_rings(priv);
	अगर (err)
		जाओ मुक्त_rx;
	/* Add tx napi & init sync stats*/
	क्रम (i = 0; i < priv->tx_cfg.num_queues; i++) अणु
		u64_stats_init(&priv->tx[i].statss);
		ntfy_idx = gve_tx_idx_to_ntfy(priv, i);
		gve_add_napi(priv, ntfy_idx);
	पूर्ण
	/* Add rx napi  & init sync stats*/
	क्रम (i = 0; i < priv->rx_cfg.num_queues; i++) अणु
		u64_stats_init(&priv->rx[i].statss);
		ntfy_idx = gve_rx_idx_to_ntfy(priv, i);
		gve_add_napi(priv, ntfy_idx);
	पूर्ण

	वापस 0;

मुक्त_rx:
	kvमुक्त(priv->rx);
	priv->rx = शून्य;
मुक्त_tx_queue:
	gve_tx_मुक्त_rings(priv);
मुक्त_tx:
	kvमुक्त(priv->tx);
	priv->tx = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक gve_destroy_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक err;

	err = gve_adminq_destroy_tx_queues(priv, priv->tx_cfg.num_queues);
	अगर (err) अणु
		netअगर_err(priv, drv, priv->dev,
			  "failed to destroy tx queues\n");
		/* This failure will trigger a reset - no need to clean up */
		वापस err;
	पूर्ण
	netअगर_dbg(priv, drv, priv->dev, "destroyed tx queues\n");
	err = gve_adminq_destroy_rx_queues(priv, priv->rx_cfg.num_queues);
	अगर (err) अणु
		netअगर_err(priv, drv, priv->dev,
			  "failed to destroy rx queues\n");
		/* This failure will trigger a reset - no need to clean up */
		वापस err;
	पूर्ण
	netअगर_dbg(priv, drv, priv->dev, "destroyed rx queues\n");
	वापस 0;
पूर्ण

अटल व्योम gve_मुक्त_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक ntfy_idx;
	पूर्णांक i;

	अगर (priv->tx) अणु
		क्रम (i = 0; i < priv->tx_cfg.num_queues; i++) अणु
			ntfy_idx = gve_tx_idx_to_ntfy(priv, i);
			gve_हटाओ_napi(priv, ntfy_idx);
		पूर्ण
		gve_tx_मुक्त_rings(priv);
		kvमुक्त(priv->tx);
		priv->tx = शून्य;
	पूर्ण
	अगर (priv->rx) अणु
		क्रम (i = 0; i < priv->rx_cfg.num_queues; i++) अणु
			ntfy_idx = gve_rx_idx_to_ntfy(priv, i);
			gve_हटाओ_napi(priv, ntfy_idx);
		पूर्ण
		gve_rx_मुक्त_rings(priv);
		kvमुक्त(priv->rx);
		priv->rx = शून्य;
	पूर्ण
पूर्ण

पूर्णांक gve_alloc_page(काष्ठा gve_priv *priv, काष्ठा device *dev,
		   काष्ठा page **page, dma_addr_t *dma,
		   क्रमागत dma_data_direction dir)
अणु
	*page = alloc_page(GFP_KERNEL);
	अगर (!*page) अणु
		priv->page_alloc_fail++;
		वापस -ENOMEM;
	पूर्ण
	*dma = dma_map_page(dev, *page, 0, PAGE_SIZE, dir);
	अगर (dma_mapping_error(dev, *dma)) अणु
		priv->dma_mapping_error++;
		put_page(*page);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gve_alloc_queue_page_list(काष्ठा gve_priv *priv, u32 id,
				     पूर्णांक pages)
अणु
	काष्ठा gve_queue_page_list *qpl = &priv->qpls[id];
	पूर्णांक err;
	पूर्णांक i;

	अगर (pages + priv->num_रेजिस्टरed_pages > priv->max_रेजिस्टरed_pages) अणु
		netअगर_err(priv, drv, priv->dev,
			  "Reached max number of registered pages %llu > %llu\n",
			  pages + priv->num_रेजिस्टरed_pages,
			  priv->max_रेजिस्टरed_pages);
		वापस -EINVAL;
	पूर्ण

	qpl->id = id;
	qpl->num_entries = 0;
	qpl->pages = kvzalloc(pages * माप(*qpl->pages), GFP_KERNEL);
	/* caller handles clean up */
	अगर (!qpl->pages)
		वापस -ENOMEM;
	qpl->page_buses = kvzalloc(pages * माप(*qpl->page_buses),
				   GFP_KERNEL);
	/* caller handles clean up */
	अगर (!qpl->page_buses)
		वापस -ENOMEM;

	क्रम (i = 0; i < pages; i++) अणु
		err = gve_alloc_page(priv, &priv->pdev->dev, &qpl->pages[i],
				     &qpl->page_buses[i],
				     gve_qpl_dma_dir(priv, id));
		/* caller handles clean up */
		अगर (err)
			वापस -ENOMEM;
		qpl->num_entries++;
	पूर्ण
	priv->num_रेजिस्टरed_pages += pages;

	वापस 0;
पूर्ण

व्योम gve_मुक्त_page(काष्ठा device *dev, काष्ठा page *page, dma_addr_t dma,
		   क्रमागत dma_data_direction dir)
अणु
	अगर (!dma_mapping_error(dev, dma))
		dma_unmap_page(dev, dma, PAGE_SIZE, dir);
	अगर (page)
		put_page(page);
पूर्ण

अटल व्योम gve_मुक्त_queue_page_list(काष्ठा gve_priv *priv,
				     पूर्णांक id)
अणु
	काष्ठा gve_queue_page_list *qpl = &priv->qpls[id];
	पूर्णांक i;

	अगर (!qpl->pages)
		वापस;
	अगर (!qpl->page_buses)
		जाओ मुक्त_pages;

	क्रम (i = 0; i < qpl->num_entries; i++)
		gve_मुक्त_page(&priv->pdev->dev, qpl->pages[i],
			      qpl->page_buses[i], gve_qpl_dma_dir(priv, id));

	kvमुक्त(qpl->page_buses);
मुक्त_pages:
	kvमुक्त(qpl->pages);
	priv->num_रेजिस्टरed_pages -= qpl->num_entries;
पूर्ण

अटल पूर्णांक gve_alloc_qpls(काष्ठा gve_priv *priv)
अणु
	पूर्णांक num_qpls = gve_num_tx_qpls(priv) + gve_num_rx_qpls(priv);
	पूर्णांक i, j;
	पूर्णांक err;

	/* Raw addressing means no QPLs */
	अगर (priv->raw_addressing)
		वापस 0;

	priv->qpls = kvzalloc(num_qpls * माप(*priv->qpls), GFP_KERNEL);
	अगर (!priv->qpls)
		वापस -ENOMEM;

	क्रम (i = 0; i < gve_num_tx_qpls(priv); i++) अणु
		err = gve_alloc_queue_page_list(priv, i,
						priv->tx_pages_per_qpl);
		अगर (err)
			जाओ मुक्त_qpls;
	पूर्ण
	क्रम (; i < num_qpls; i++) अणु
		err = gve_alloc_queue_page_list(priv, i,
						priv->rx_data_slot_cnt);
		अगर (err)
			जाओ मुक्त_qpls;
	पूर्ण

	priv->qpl_cfg.qpl_map_size = BITS_TO_LONGS(num_qpls) *
				     माप(अचिन्हित दीर्घ) * BITS_PER_BYTE;
	priv->qpl_cfg.qpl_id_map = kvzalloc(BITS_TO_LONGS(num_qpls) *
					    माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!priv->qpl_cfg.qpl_id_map) अणु
		err = -ENOMEM;
		जाओ मुक्त_qpls;
	पूर्ण

	वापस 0;

मुक्त_qpls:
	क्रम (j = 0; j <= i; j++)
		gve_मुक्त_queue_page_list(priv, j);
	kvमुक्त(priv->qpls);
	वापस err;
पूर्ण

अटल व्योम gve_मुक्त_qpls(काष्ठा gve_priv *priv)
अणु
	पूर्णांक num_qpls = gve_num_tx_qpls(priv) + gve_num_rx_qpls(priv);
	पूर्णांक i;

	/* Raw addressing means no QPLs */
	अगर (priv->raw_addressing)
		वापस;

	kvमुक्त(priv->qpl_cfg.qpl_id_map);

	क्रम (i = 0; i < num_qpls; i++)
		gve_मुक्त_queue_page_list(priv, i);

	kvमुक्त(priv->qpls);
पूर्ण

/* Use this to schedule a reset when the device is capable of continuing
 * to handle other requests in its current state. If it is not, करो a reset
 * in thपढ़ो instead.
 */
व्योम gve_schedule_reset(काष्ठा gve_priv *priv)
अणु
	gve_set_करो_reset(priv);
	queue_work(priv->gve_wq, &priv->service_task);
पूर्ण

अटल व्योम gve_reset_and_tearकरोwn(काष्ठा gve_priv *priv, bool was_up);
अटल पूर्णांक gve_reset_recovery(काष्ठा gve_priv *priv, bool was_up);
अटल व्योम gve_turnकरोwn(काष्ठा gve_priv *priv);
अटल व्योम gve_turnup(काष्ठा gve_priv *priv);

अटल पूर्णांक gve_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा gve_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	err = gve_alloc_qpls(priv);
	अगर (err)
		वापस err;
	err = gve_alloc_rings(priv);
	अगर (err)
		जाओ मुक्त_qpls;

	err = netअगर_set_real_num_tx_queues(dev, priv->tx_cfg.num_queues);
	अगर (err)
		जाओ मुक्त_rings;
	err = netअगर_set_real_num_rx_queues(dev, priv->rx_cfg.num_queues);
	अगर (err)
		जाओ मुक्त_rings;

	err = gve_रेजिस्टर_qpls(priv);
	अगर (err)
		जाओ reset;
	err = gve_create_rings(priv);
	अगर (err)
		जाओ reset;
	gve_set_device_rings_ok(priv);

	अगर (gve_get_report_stats(priv))
		mod_समयr(&priv->stats_report_समयr,
			  round_jअगरfies(jअगरfies +
				msecs_to_jअगरfies(priv->stats_report_समयr_period)));

	gve_turnup(priv);
	queue_work(priv->gve_wq, &priv->service_task);
	priv->पूर्णांकerface_up_cnt++;
	वापस 0;

मुक्त_rings:
	gve_मुक्त_rings(priv);
मुक्त_qpls:
	gve_मुक्त_qpls(priv);
	वापस err;

reset:
	/* This must have been called from a reset due to the rtnl lock
	 * so just वापस at this poपूर्णांक.
	 */
	अगर (gve_get_reset_in_progress(priv))
		वापस err;
	/* Otherwise reset beक्रमe वापसing */
	gve_reset_and_tearकरोwn(priv, true);
	/* अगर this fails there is nothing we can करो so just ignore the वापस */
	gve_reset_recovery(priv, false);
	/* वापस the original error */
	वापस err;
पूर्ण

अटल पूर्णांक gve_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा gve_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	netअगर_carrier_off(dev);
	अगर (gve_get_device_rings_ok(priv)) अणु
		gve_turnकरोwn(priv);
		err = gve_destroy_rings(priv);
		अगर (err)
			जाओ err;
		err = gve_unरेजिस्टर_qpls(priv);
		अगर (err)
			जाओ err;
		gve_clear_device_rings_ok(priv);
	पूर्ण
	del_समयr_sync(&priv->stats_report_समयr);

	gve_मुक्त_rings(priv);
	gve_मुक्त_qpls(priv);
	priv->पूर्णांकerface_करोwn_cnt++;
	वापस 0;

err:
	/* This must have been called from a reset due to the rtnl lock
	 * so just वापस at this poपूर्णांक.
	 */
	अगर (gve_get_reset_in_progress(priv))
		वापस err;
	/* Otherwise reset beक्रमe वापसing */
	gve_reset_and_tearकरोwn(priv, true);
	वापस gve_reset_recovery(priv, false);
पूर्ण

पूर्णांक gve_adjust_queues(काष्ठा gve_priv *priv,
		      काष्ठा gve_queue_config new_rx_config,
		      काष्ठा gve_queue_config new_tx_config)
अणु
	पूर्णांक err;

	अगर (netअगर_carrier_ok(priv->dev)) अणु
		/* To make this process as simple as possible we tearकरोwn the
		 * device, set the new configuration, and then bring the device
		 * up again.
		 */
		err = gve_बंद(priv->dev);
		/* we have alपढ़ोy tried to reset in बंद,
		 * just fail at this poपूर्णांक
		 */
		अगर (err)
			वापस err;
		priv->tx_cfg = new_tx_config;
		priv->rx_cfg = new_rx_config;

		err = gve_खोलो(priv->dev);
		अगर (err)
			जाओ err;

		वापस 0;
	पूर्ण
	/* Set the config क्रम the next up. */
	priv->tx_cfg = new_tx_config;
	priv->rx_cfg = new_rx_config;

	वापस 0;
err:
	netअगर_err(priv, drv, priv->dev,
		  "Adjust queues failed! !!! DISABLING ALL QUEUES !!!\n");
	gve_turnकरोwn(priv);
	वापस err;
पूर्ण

अटल व्योम gve_turnकरोwn(काष्ठा gve_priv *priv)
अणु
	पूर्णांक idx;

	अगर (netअगर_carrier_ok(priv->dev))
		netअगर_carrier_off(priv->dev);

	अगर (!gve_get_napi_enabled(priv))
		वापस;

	/* Disable napi to prevent more work from coming in */
	क्रम (idx = 0; idx < priv->tx_cfg.num_queues; idx++) अणु
		पूर्णांक ntfy_idx = gve_tx_idx_to_ntfy(priv, idx);
		काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_disable(&block->napi);
	पूर्ण
	क्रम (idx = 0; idx < priv->rx_cfg.num_queues; idx++) अणु
		पूर्णांक ntfy_idx = gve_rx_idx_to_ntfy(priv, idx);
		काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_disable(&block->napi);
	पूर्ण

	/* Stop tx queues */
	netअगर_tx_disable(priv->dev);

	gve_clear_napi_enabled(priv);
	gve_clear_report_stats(priv);
पूर्ण

अटल व्योम gve_turnup(काष्ठा gve_priv *priv)
अणु
	पूर्णांक idx;

	/* Start the tx queues */
	netअगर_tx_start_all_queues(priv->dev);

	/* Enable napi and unmask पूर्णांकerrupts क्रम all queues */
	क्रम (idx = 0; idx < priv->tx_cfg.num_queues; idx++) अणु
		पूर्णांक ntfy_idx = gve_tx_idx_to_ntfy(priv, idx);
		काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_enable(&block->napi);
		ioग_लिखो32be(0, gve_irq_करोorbell(priv, block));
	पूर्ण
	क्रम (idx = 0; idx < priv->rx_cfg.num_queues; idx++) अणु
		पूर्णांक ntfy_idx = gve_rx_idx_to_ntfy(priv, idx);
		काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_enable(&block->napi);
		ioग_लिखो32be(0, gve_irq_करोorbell(priv, block));
	पूर्ण

	gve_set_napi_enabled(priv);
पूर्ण

अटल व्योम gve_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा gve_priv *priv = netdev_priv(dev);

	gve_schedule_reset(priv);
	priv->tx_समयo_cnt++;
पूर्ण

अटल स्थिर काष्ठा net_device_ops gve_netdev_ops = अणु
	.nकरो_start_xmit		=	gve_tx,
	.nकरो_खोलो		=	gve_खोलो,
	.nकरो_stop		=	gve_बंद,
	.nकरो_get_stats64	=	gve_get_stats,
	.nकरो_tx_समयout         =       gve_tx_समयout,
पूर्ण;

अटल व्योम gve_handle_status(काष्ठा gve_priv *priv, u32 status)
अणु
	अगर (GVE_DEVICE_STATUS_RESET_MASK & status) अणु
		dev_info(&priv->pdev->dev, "Device requested reset.\n");
		gve_set_करो_reset(priv);
	पूर्ण
	अगर (GVE_DEVICE_STATUS_REPORT_STATS_MASK & status) अणु
		priv->stats_report_trigger_cnt++;
		gve_set_करो_report_stats(priv);
	पूर्ण
पूर्ण

अटल व्योम gve_handle_reset(काष्ठा gve_priv *priv)
अणु
	/* A service task will be scheduled at the end of probe to catch any
	 * resets that need to happen, and we करोn't want to reset until
	 * probe is करोne.
	 */
	अगर (gve_get_probe_in_progress(priv))
		वापस;

	अगर (gve_get_करो_reset(priv)) अणु
		rtnl_lock();
		gve_reset(priv, false);
		rtnl_unlock();
	पूर्ण
पूर्ण

व्योम gve_handle_report_stats(काष्ठा gve_priv *priv)
अणु
	पूर्णांक idx, stats_idx = 0, tx_bytes;
	अचिन्हित पूर्णांक start = 0;
	काष्ठा stats *stats = priv->stats_report->stats;

	अगर (!gve_get_report_stats(priv))
		वापस;

	be64_add_cpu(&priv->stats_report->written_count, 1);
	/* tx stats */
	अगर (priv->tx) अणु
		क्रम (idx = 0; idx < priv->tx_cfg.num_queues; idx++) अणु
			करो अणु
				start = u64_stats_fetch_begin(&priv->tx[idx].statss);
				tx_bytes = priv->tx[idx].bytes_करोne;
			पूर्ण जबतक (u64_stats_fetch_retry(&priv->tx[idx].statss, start));
			stats[stats_idx++] = (काष्ठा stats) अणु
				.stat_name = cpu_to_be32(TX_WAKE_CNT),
				.value = cpu_to_be64(priv->tx[idx].wake_queue),
				.queue_id = cpu_to_be32(idx),
			पूर्ण;
			stats[stats_idx++] = (काष्ठा stats) अणु
				.stat_name = cpu_to_be32(TX_STOP_CNT),
				.value = cpu_to_be64(priv->tx[idx].stop_queue),
				.queue_id = cpu_to_be32(idx),
			पूर्ण;
			stats[stats_idx++] = (काष्ठा stats) अणु
				.stat_name = cpu_to_be32(TX_FRAMES_SENT),
				.value = cpu_to_be64(priv->tx[idx].req),
				.queue_id = cpu_to_be32(idx),
			पूर्ण;
			stats[stats_idx++] = (काष्ठा stats) अणु
				.stat_name = cpu_to_be32(TX_BYTES_SENT),
				.value = cpu_to_be64(tx_bytes),
				.queue_id = cpu_to_be32(idx),
			पूर्ण;
			stats[stats_idx++] = (काष्ठा stats) अणु
				.stat_name = cpu_to_be32(TX_LAST_COMPLETION_PROCESSED),
				.value = cpu_to_be64(priv->tx[idx].करोne),
				.queue_id = cpu_to_be32(idx),
			पूर्ण;
		पूर्ण
	पूर्ण
	/* rx stats */
	अगर (priv->rx) अणु
		क्रम (idx = 0; idx < priv->rx_cfg.num_queues; idx++) अणु
			stats[stats_idx++] = (काष्ठा stats) अणु
				.stat_name = cpu_to_be32(RX_NEXT_EXPECTED_SEQUENCE),
				.value = cpu_to_be64(priv->rx[idx].desc.seqno),
				.queue_id = cpu_to_be32(idx),
			पूर्ण;
			stats[stats_idx++] = (काष्ठा stats) अणु
				.stat_name = cpu_to_be32(RX_BUFFERS_POSTED),
				.value = cpu_to_be64(priv->rx[0].fill_cnt),
				.queue_id = cpu_to_be32(idx),
			पूर्ण;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gve_handle_link_status(काष्ठा gve_priv *priv, bool link_status)
अणु
	अगर (!gve_get_napi_enabled(priv))
		वापस;

	अगर (link_status == netअगर_carrier_ok(priv->dev))
		वापस;

	अगर (link_status) अणु
		netdev_info(priv->dev, "Device link is up.\n");
		netअगर_carrier_on(priv->dev);
	पूर्ण अन्यथा अणु
		netdev_info(priv->dev, "Device link is down.\n");
		netअगर_carrier_off(priv->dev);
	पूर्ण
पूर्ण

/* Handle NIC status रेजिस्टर changes, reset requests and report stats */
अटल व्योम gve_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gve_priv *priv = container_of(work, काष्ठा gve_priv,
					     service_task);
	u32 status = ioपढ़ो32be(&priv->reg_bar0->device_status);

	gve_handle_status(priv, status);

	gve_handle_reset(priv);
	gve_handle_link_status(priv, GVE_DEVICE_STATUS_LINK_STATUS_MASK & status);
पूर्ण

अटल पूर्णांक gve_init_priv(काष्ठा gve_priv *priv, bool skip_describe_device)
अणु
	पूर्णांक num_ntfy;
	पूर्णांक err;

	/* Set up the adminq */
	err = gve_adminq_alloc(&priv->pdev->dev, priv);
	अगर (err) अणु
		dev_err(&priv->pdev->dev,
			"Failed to alloc admin queue: err=%d\n", err);
		वापस err;
	पूर्ण

	अगर (skip_describe_device)
		जाओ setup_device;

	priv->raw_addressing = false;
	/* Get the initial inक्रमmation we need from the device */
	err = gve_adminq_describe_device(priv);
	अगर (err) अणु
		dev_err(&priv->pdev->dev,
			"Could not get device information: err=%d\n", err);
		जाओ err;
	पूर्ण
	अगर (priv->dev->max_mtu > PAGE_SIZE) अणु
		priv->dev->max_mtu = PAGE_SIZE;
		err = gve_adminq_set_mtu(priv, priv->dev->mtu);
		अगर (err) अणु
			dev_err(&priv->pdev->dev, "Could not set mtu");
			जाओ err;
		पूर्ण
	पूर्ण
	priv->dev->mtu = priv->dev->max_mtu;
	num_ntfy = pci_msix_vec_count(priv->pdev);
	अगर (num_ntfy <= 0) अणु
		dev_err(&priv->pdev->dev,
			"could not count MSI-x vectors: err=%d\n", num_ntfy);
		err = num_ntfy;
		जाओ err;
	पूर्ण अन्यथा अगर (num_ntfy < GVE_MIN_MSIX) अणु
		dev_err(&priv->pdev->dev, "gve needs at least %d MSI-x vectors, but only has %d\n",
			GVE_MIN_MSIX, num_ntfy);
		err = -EINVAL;
		जाओ err;
	पूर्ण

	priv->num_रेजिस्टरed_pages = 0;
	priv->rx_copyअवरोध = GVE_DEFAULT_RX_COPYBREAK;
	/* gvnic has one Notअगरication Block per MSI-x vector, except क्रम the
	 * management vector
	 */
	priv->num_ntfy_blks = (num_ntfy - 1) & ~0x1;
	priv->mgmt_msix_idx = priv->num_ntfy_blks;

	priv->tx_cfg.max_queues =
		min_t(पूर्णांक, priv->tx_cfg.max_queues, priv->num_ntfy_blks / 2);
	priv->rx_cfg.max_queues =
		min_t(पूर्णांक, priv->rx_cfg.max_queues, priv->num_ntfy_blks / 2);

	priv->tx_cfg.num_queues = priv->tx_cfg.max_queues;
	priv->rx_cfg.num_queues = priv->rx_cfg.max_queues;
	अगर (priv->शेष_num_queues > 0) अणु
		priv->tx_cfg.num_queues = min_t(पूर्णांक, priv->शेष_num_queues,
						priv->tx_cfg.num_queues);
		priv->rx_cfg.num_queues = min_t(पूर्णांक, priv->शेष_num_queues,
						priv->rx_cfg.num_queues);
	पूर्ण

	dev_info(&priv->pdev->dev, "TX queues %d, RX queues %d\n",
		 priv->tx_cfg.num_queues, priv->rx_cfg.num_queues);
	dev_info(&priv->pdev->dev, "Max TX queues %d, Max RX queues %d\n",
		 priv->tx_cfg.max_queues, priv->rx_cfg.max_queues);

setup_device:
	err = gve_setup_device_resources(priv);
	अगर (!err)
		वापस 0;
err:
	gve_adminq_मुक्त(&priv->pdev->dev, priv);
	वापस err;
पूर्ण

अटल व्योम gve_tearकरोwn_priv_resources(काष्ठा gve_priv *priv)
अणु
	gve_tearकरोwn_device_resources(priv);
	gve_adminq_मुक्त(&priv->pdev->dev, priv);
पूर्ण

अटल व्योम gve_trigger_reset(काष्ठा gve_priv *priv)
अणु
	/* Reset the device by releasing the AQ */
	gve_adminq_release(priv);
पूर्ण

अटल व्योम gve_reset_and_tearकरोwn(काष्ठा gve_priv *priv, bool was_up)
अणु
	gve_trigger_reset(priv);
	/* With the reset having alपढ़ोy happened, बंद cannot fail */
	अगर (was_up)
		gve_बंद(priv->dev);
	gve_tearकरोwn_priv_resources(priv);
पूर्ण

अटल पूर्णांक gve_reset_recovery(काष्ठा gve_priv *priv, bool was_up)
अणु
	पूर्णांक err;

	err = gve_init_priv(priv, true);
	अगर (err)
		जाओ err;
	अगर (was_up) अणु
		err = gve_खोलो(priv->dev);
		अगर (err)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dev_err(&priv->pdev->dev, "Reset failed! !!! DISABLING ALL QUEUES !!!\n");
	gve_turnकरोwn(priv);
	वापस err;
पूर्ण

पूर्णांक gve_reset(काष्ठा gve_priv *priv, bool attempt_tearकरोwn)
अणु
	bool was_up = netअगर_carrier_ok(priv->dev);
	पूर्णांक err;

	dev_info(&priv->pdev->dev, "Performing reset\n");
	gve_clear_करो_reset(priv);
	gve_set_reset_in_progress(priv);
	/* If we aren't attempting to tearकरोwn normally, just go turnकरोwn and
	 * reset right away.
	 */
	अगर (!attempt_tearकरोwn) अणु
		gve_turnकरोwn(priv);
		gve_reset_and_tearकरोwn(priv, was_up);
	पूर्ण अन्यथा अणु
		/* Otherwise attempt to बंद normally */
		अगर (was_up) अणु
			err = gve_बंद(priv->dev);
			/* If that fails reset as we did above */
			अगर (err)
				gve_reset_and_tearकरोwn(priv, was_up);
		पूर्ण
		/* Clean up any reमुख्यing resources */
		gve_tearकरोwn_priv_resources(priv);
	पूर्ण

	/* Set it all back up */
	err = gve_reset_recovery(priv, was_up);
	gve_clear_reset_in_progress(priv);
	priv->reset_cnt++;
	priv->पूर्णांकerface_up_cnt = 0;
	priv->पूर्णांकerface_करोwn_cnt = 0;
	priv->stats_report_trigger_cnt = 0;
	वापस err;
पूर्ण

अटल व्योम gve_ग_लिखो_version(u8 __iomem *driver_version_रेजिस्टर)
अणु
	स्थिर अक्षर *c = gve_version_prefix;

	जबतक (*c) अणु
		ग_लिखोb(*c, driver_version_रेजिस्टर);
		c++;
	पूर्ण

	c = gve_version_str;
	जबतक (*c) अणु
		ग_लिखोb(*c, driver_version_रेजिस्टर);
		c++;
	पूर्ण
	ग_लिखोb('\n', driver_version_रेजिस्टर);
पूर्ण

अटल पूर्णांक gve_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक max_tx_queues, max_rx_queues;
	काष्ठा net_device *dev;
	__be32 __iomem *db_bar;
	काष्ठा gve_रेजिस्टरs __iomem *reg_bar;
	काष्ठा gve_priv *priv;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस -ENXIO;

	err = pci_request_regions(pdev, "gvnic-cfg");
	अगर (err)
		जाओ पात_with_enabled;

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set dma mask: err=%d\n", err);
		जाओ पात_with_pci_region;
	पूर्ण

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to set consistent dma mask: err=%d\n", err);
		जाओ पात_with_pci_region;
	पूर्ण

	reg_bar = pci_iomap(pdev, GVE_REGISTER_BAR, 0);
	अगर (!reg_bar) अणु
		dev_err(&pdev->dev, "Failed to map pci bar!\n");
		err = -ENOMEM;
		जाओ पात_with_pci_region;
	पूर्ण

	db_bar = pci_iomap(pdev, GVE_DOORBELL_BAR, 0);
	अगर (!db_bar) अणु
		dev_err(&pdev->dev, "Failed to map doorbell bar!\n");
		err = -ENOMEM;
		जाओ पात_with_reg_bar;
	पूर्ण

	gve_ग_लिखो_version(&reg_bar->driver_version);
	/* Get max queues to alloc etherdev */
	max_rx_queues = ioपढ़ो32be(&reg_bar->max_tx_queues);
	max_tx_queues = ioपढ़ो32be(&reg_bar->max_rx_queues);
	/* Alloc and setup the netdev and priv */
	dev = alloc_etherdev_mqs(माप(*priv), max_tx_queues, max_rx_queues);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "could not allocate netdev\n");
		जाओ पात_with_db_bar;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);
	pci_set_drvdata(pdev, dev);
	dev->ethtool_ops = &gve_ethtool_ops;
	dev->netdev_ops = &gve_netdev_ops;
	/* advertise features */
	dev->hw_features = NETIF_F_HIGHDMA;
	dev->hw_features |= NETIF_F_SG;
	dev->hw_features |= NETIF_F_HW_CSUM;
	dev->hw_features |= NETIF_F_TSO;
	dev->hw_features |= NETIF_F_TSO6;
	dev->hw_features |= NETIF_F_TSO_ECN;
	dev->hw_features |= NETIF_F_RXCSUM;
	dev->hw_features |= NETIF_F_RXHASH;
	dev->features = dev->hw_features;
	dev->watchकरोg_समयo = 5 * HZ;
	dev->min_mtu = ETH_MIN_MTU;
	netअगर_carrier_off(dev);

	priv = netdev_priv(dev);
	priv->dev = dev;
	priv->pdev = pdev;
	priv->msg_enable = DEFAULT_MSG_LEVEL;
	priv->reg_bar0 = reg_bar;
	priv->db_bar2 = db_bar;
	priv->service_task_flags = 0x0;
	priv->state_flags = 0x0;
	priv->ethtool_flags = 0x0;

	gve_set_probe_in_progress(priv);
	priv->gve_wq = alloc_ordered_workqueue("gve", 0);
	अगर (!priv->gve_wq) अणु
		dev_err(&pdev->dev, "Could not allocate workqueue");
		err = -ENOMEM;
		जाओ पात_with_netdev;
	पूर्ण
	INIT_WORK(&priv->service_task, gve_service_task);
	INIT_WORK(&priv->stats_report_task, gve_stats_report_task);
	priv->tx_cfg.max_queues = max_tx_queues;
	priv->rx_cfg.max_queues = max_rx_queues;

	err = gve_init_priv(priv, false);
	अगर (err)
		जाओ पात_with_wq;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ पात_with_wq;

	dev_info(&pdev->dev, "GVE version %s\n", gve_version_str);
	gve_clear_probe_in_progress(priv);
	queue_work(priv->gve_wq, &priv->service_task);
	वापस 0;

पात_with_wq:
	destroy_workqueue(priv->gve_wq);

पात_with_netdev:
	मुक्त_netdev(dev);

पात_with_db_bar:
	pci_iounmap(pdev, db_bar);

पात_with_reg_bar:
	pci_iounmap(pdev, reg_bar);

पात_with_pci_region:
	pci_release_regions(pdev);

पात_with_enabled:
	pci_disable_device(pdev);
	वापस -ENXIO;
पूर्ण

अटल व्योम gve_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा gve_priv *priv = netdev_priv(netdev);
	__be32 __iomem *db_bar = priv->db_bar2;
	व्योम __iomem *reg_bar = priv->reg_bar0;

	unरेजिस्टर_netdev(netdev);
	gve_tearकरोwn_priv_resources(priv);
	destroy_workqueue(priv->gve_wq);
	मुक्त_netdev(netdev);
	pci_iounmap(pdev, db_bar);
	pci_iounmap(pdev, reg_bar);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id gve_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_GOOGLE, PCI_DEV_ID_GVNIC) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver gvnic_driver = अणु
	.name		= "gvnic",
	.id_table	= gve_id_table,
	.probe		= gve_probe,
	.हटाओ		= gve_हटाओ,
पूर्ण;

module_pci_driver(gvnic_driver);

MODULE_DEVICE_TABLE(pci, gve_id_table);
MODULE_AUTHOR("Google, Inc.");
MODULE_DESCRIPTION("gVNIC Driver");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION(GVE_VERSION);
