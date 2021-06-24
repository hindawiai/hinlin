<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_net_common.c
 * Netronome network device driver: Common functions between PF and VF
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 *          Brad Petrus <brad.petrus@netronome.com>
 *          Chris Telfer <chris.telfer@netronome.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/mm.h>
#समावेश <linux/overflow.h>
#समावेश <linux/page_ref.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/msi.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/log2.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kसमय.स>

#समावेश <net/tls.h>
#समावेश <net/vxlan.h>

#समावेश "nfpcore/nfp_nsp.h"
#समावेश "ccm.h"
#समावेश "nfp_app.h"
#समावेश "nfp_net_ctrl.h"
#समावेश "nfp_net.h"
#समावेश "nfp_net_sriov.h"
#समावेश "nfp_port.h"
#समावेश "crypto/crypto.h"
#समावेश "crypto/fw.h"

/**
 * nfp_net_get_fw_version() - Read and parse the FW version
 * @fw_ver:	Output fw_version काष्ठाure to पढ़ो to
 * @ctrl_bar:	Mapped address of the control BAR
 */
व्योम nfp_net_get_fw_version(काष्ठा nfp_net_fw_version *fw_ver,
			    व्योम __iomem *ctrl_bar)
अणु
	u32 reg;

	reg = पढ़ोl(ctrl_bar + NFP_NET_CFG_VERSION);
	put_unaligned_le32(reg, fw_ver);
पूर्ण

अटल dma_addr_t nfp_net_dma_map_rx(काष्ठा nfp_net_dp *dp, व्योम *frag)
अणु
	वापस dma_map_single_attrs(dp->dev, frag + NFP_NET_RX_BUF_HEADROOM,
				    dp->fl_bufsz - NFP_NET_RX_BUF_NON_DATA,
				    dp->rx_dma_dir, DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

अटल व्योम
nfp_net_dma_sync_dev_rx(स्थिर काष्ठा nfp_net_dp *dp, dma_addr_t dma_addr)
अणु
	dma_sync_single_क्रम_device(dp->dev, dma_addr,
				   dp->fl_bufsz - NFP_NET_RX_BUF_NON_DATA,
				   dp->rx_dma_dir);
पूर्ण

अटल व्योम nfp_net_dma_unmap_rx(काष्ठा nfp_net_dp *dp, dma_addr_t dma_addr)
अणु
	dma_unmap_single_attrs(dp->dev, dma_addr,
			       dp->fl_bufsz - NFP_NET_RX_BUF_NON_DATA,
			       dp->rx_dma_dir, DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

अटल व्योम nfp_net_dma_sync_cpu_rx(काष्ठा nfp_net_dp *dp, dma_addr_t dma_addr,
				    अचिन्हित पूर्णांक len)
अणु
	dma_sync_single_क्रम_cpu(dp->dev, dma_addr - NFP_NET_RX_BUF_HEADROOM,
				len, dp->rx_dma_dir);
पूर्ण

/* Firmware reconfig
 *
 * Firmware reconfig may take a जबतक so we have two versions of it -
 * synchronous and asynchronous (posted).  All synchronous callers are holding
 * RTNL so we करोn't have to worry about serializing them.
 */
अटल व्योम nfp_net_reconfig_start(काष्ठा nfp_net *nn, u32 update)
अणु
	nn_ग_लिखोl(nn, NFP_NET_CFG_UPDATE, update);
	/* ensure update is written beक्रमe pinging HW */
	nn_pci_flush(nn);
	nfp_qcp_wr_ptr_add(nn->qcp_cfg, 1);
	nn->reconfig_in_progress_update = update;
पूर्ण

/* Pass 0 as update to run posted reconfigs. */
अटल व्योम nfp_net_reconfig_start_async(काष्ठा nfp_net *nn, u32 update)
अणु
	update |= nn->reconfig_posted;
	nn->reconfig_posted = 0;

	nfp_net_reconfig_start(nn, update);

	nn->reconfig_समयr_active = true;
	mod_समयr(&nn->reconfig_समयr, jअगरfies + NFP_NET_POLL_TIMEOUT * HZ);
पूर्ण

अटल bool nfp_net_reconfig_check_करोne(काष्ठा nfp_net *nn, bool last_check)
अणु
	u32 reg;

	reg = nn_पढ़ोl(nn, NFP_NET_CFG_UPDATE);
	अगर (reg == 0)
		वापस true;
	अगर (reg & NFP_NET_CFG_UPDATE_ERR) अणु
		nn_err(nn, "Reconfig error (status: 0x%08x update: 0x%08x ctrl: 0x%08x)\n",
		       reg, nn->reconfig_in_progress_update,
		       nn_पढ़ोl(nn, NFP_NET_CFG_CTRL));
		वापस true;
	पूर्ण अन्यथा अगर (last_check) अणु
		nn_err(nn, "Reconfig timeout (status: 0x%08x update: 0x%08x ctrl: 0x%08x)\n",
		       reg, nn->reconfig_in_progress_update,
		       nn_पढ़ोl(nn, NFP_NET_CFG_CTRL));
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __nfp_net_reconfig_रुको(काष्ठा nfp_net *nn, अचिन्हित दीर्घ deadline)
अणु
	bool समयd_out = false;
	पूर्णांक i;

	/* Poll update field, रुकोing क्रम NFP to ack the config.
	 * Do an opportunistic रुको-busy loop, afterward sleep.
	 */
	क्रम (i = 0; i < 50; i++) अणु
		अगर (nfp_net_reconfig_check_करोne(nn, false))
			वापस false;
		udelay(4);
	पूर्ण

	जबतक (!nfp_net_reconfig_check_करोne(nn, समयd_out)) अणु
		usleep_range(250, 500);
		समयd_out = समय_is_beक्रमe_eq_jअगरfies(deadline);
	पूर्ण

	वापस समयd_out;
पूर्ण

अटल पूर्णांक nfp_net_reconfig_रुको(काष्ठा nfp_net *nn, अचिन्हित दीर्घ deadline)
अणु
	अगर (__nfp_net_reconfig_रुको(nn, deadline))
		वापस -EIO;

	अगर (nn_पढ़ोl(nn, NFP_NET_CFG_UPDATE) & NFP_NET_CFG_UPDATE_ERR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम nfp_net_reconfig_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा nfp_net *nn = from_समयr(nn, t, reconfig_समयr);

	spin_lock_bh(&nn->reconfig_lock);

	nn->reconfig_समयr_active = false;

	/* If sync caller is present it will take over from us */
	अगर (nn->reconfig_sync_present)
		जाओ करोne;

	/* Read reconfig status and report errors */
	nfp_net_reconfig_check_करोne(nn, true);

	अगर (nn->reconfig_posted)
		nfp_net_reconfig_start_async(nn, 0);
करोne:
	spin_unlock_bh(&nn->reconfig_lock);
पूर्ण

/**
 * nfp_net_reconfig_post() - Post async reconfig request
 * @nn:      NFP Net device to reconfigure
 * @update:  The value क्रम the update field in the BAR config
 *
 * Record FW reconfiguration request.  Reconfiguration will be kicked off
 * whenever reconfiguration machinery is idle.  Multiple requests can be
 * merged together!
 */
अटल व्योम nfp_net_reconfig_post(काष्ठा nfp_net *nn, u32 update)
अणु
	spin_lock_bh(&nn->reconfig_lock);

	/* Sync caller will kick off async reconf when it's करोne, just post */
	अगर (nn->reconfig_sync_present) अणु
		nn->reconfig_posted |= update;
		जाओ करोne;
	पूर्ण

	/* Opportunistically check अगर the previous command is करोne */
	अगर (!nn->reconfig_समयr_active ||
	    nfp_net_reconfig_check_करोne(nn, false))
		nfp_net_reconfig_start_async(nn, update);
	अन्यथा
		nn->reconfig_posted |= update;
करोne:
	spin_unlock_bh(&nn->reconfig_lock);
पूर्ण

अटल व्योम nfp_net_reconfig_sync_enter(काष्ठा nfp_net *nn)
अणु
	bool cancelled_समयr = false;
	u32 pre_posted_requests;

	spin_lock_bh(&nn->reconfig_lock);

	WARN_ON(nn->reconfig_sync_present);
	nn->reconfig_sync_present = true;

	अगर (nn->reconfig_समयr_active) अणु
		nn->reconfig_समयr_active = false;
		cancelled_समयr = true;
	पूर्ण
	pre_posted_requests = nn->reconfig_posted;
	nn->reconfig_posted = 0;

	spin_unlock_bh(&nn->reconfig_lock);

	अगर (cancelled_समयr) अणु
		del_समयr_sync(&nn->reconfig_समयr);
		nfp_net_reconfig_रुको(nn, nn->reconfig_समयr.expires);
	पूर्ण

	/* Run the posted reconfigs which were issued beक्रमe we started */
	अगर (pre_posted_requests) अणु
		nfp_net_reconfig_start(nn, pre_posted_requests);
		nfp_net_reconfig_रुको(nn, jअगरfies + HZ * NFP_NET_POLL_TIMEOUT);
	पूर्ण
पूर्ण

अटल व्योम nfp_net_reconfig_रुको_posted(काष्ठा nfp_net *nn)
अणु
	nfp_net_reconfig_sync_enter(nn);

	spin_lock_bh(&nn->reconfig_lock);
	nn->reconfig_sync_present = false;
	spin_unlock_bh(&nn->reconfig_lock);
पूर्ण

/**
 * __nfp_net_reconfig() - Reconfigure the firmware
 * @nn:      NFP Net device to reconfigure
 * @update:  The value क्रम the update field in the BAR config
 *
 * Write the update word to the BAR and ping the reconfig queue.  The
 * poll until the firmware has acknowledged the update by zeroing the
 * update word.
 *
 * Return: Negative त्रुटि_सं on error, 0 on success
 */
पूर्णांक __nfp_net_reconfig(काष्ठा nfp_net *nn, u32 update)
अणु
	पूर्णांक ret;

	nfp_net_reconfig_sync_enter(nn);

	nfp_net_reconfig_start(nn, update);
	ret = nfp_net_reconfig_रुको(nn, jअगरfies + HZ * NFP_NET_POLL_TIMEOUT);

	spin_lock_bh(&nn->reconfig_lock);

	अगर (nn->reconfig_posted)
		nfp_net_reconfig_start_async(nn, 0);

	nn->reconfig_sync_present = false;

	spin_unlock_bh(&nn->reconfig_lock);

	वापस ret;
पूर्ण

पूर्णांक nfp_net_reconfig(काष्ठा nfp_net *nn, u32 update)
अणु
	पूर्णांक ret;

	nn_ctrl_bar_lock(nn);
	ret = __nfp_net_reconfig(nn, update);
	nn_ctrl_bar_unlock(nn);

	वापस ret;
पूर्ण

पूर्णांक nfp_net_mbox_lock(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक data_size)
अणु
	अगर (nn->tlv_caps.mbox_len < NFP_NET_CFG_MBOX_SIMPLE_VAL + data_size) अणु
		nn_err(nn, "mailbox too small for %u of data (%u)\n",
		       data_size, nn->tlv_caps.mbox_len);
		वापस -EIO;
	पूर्ण

	nn_ctrl_bar_lock(nn);
	वापस 0;
पूर्ण

/**
 * nfp_net_mbox_reconfig() - Reconfigure the firmware via the mailbox
 * @nn:        NFP Net device to reconfigure
 * @mbox_cmd:  The value क्रम the mailbox command
 *
 * Helper function क्रम mailbox updates
 *
 * Return: Negative त्रुटि_सं on error, 0 on success
 */
पूर्णांक nfp_net_mbox_reconfig(काष्ठा nfp_net *nn, u32 mbox_cmd)
अणु
	u32 mbox = nn->tlv_caps.mbox_off;
	पूर्णांक ret;

	nn_ग_लिखोq(nn, mbox + NFP_NET_CFG_MBOX_SIMPLE_CMD, mbox_cmd);

	ret = __nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_MBOX);
	अगर (ret) अणु
		nn_err(nn, "Mailbox update error\n");
		वापस ret;
	पूर्ण

	वापस -nn_पढ़ोl(nn, mbox + NFP_NET_CFG_MBOX_SIMPLE_RET);
पूर्ण

व्योम nfp_net_mbox_reconfig_post(काष्ठा nfp_net *nn, u32 mbox_cmd)
अणु
	u32 mbox = nn->tlv_caps.mbox_off;

	nn_ग_लिखोq(nn, mbox + NFP_NET_CFG_MBOX_SIMPLE_CMD, mbox_cmd);

	nfp_net_reconfig_post(nn, NFP_NET_CFG_UPDATE_MBOX);
पूर्ण

पूर्णांक nfp_net_mbox_reconfig_रुको_posted(काष्ठा nfp_net *nn)
अणु
	u32 mbox = nn->tlv_caps.mbox_off;

	nfp_net_reconfig_रुको_posted(nn);

	वापस -nn_पढ़ोl(nn, mbox + NFP_NET_CFG_MBOX_SIMPLE_RET);
पूर्ण

पूर्णांक nfp_net_mbox_reconfig_and_unlock(काष्ठा nfp_net *nn, u32 mbox_cmd)
अणु
	पूर्णांक ret;

	ret = nfp_net_mbox_reconfig(nn, mbox_cmd);
	nn_ctrl_bar_unlock(nn);
	वापस ret;
पूर्ण

/* Interrupt configuration and handling
 */

/**
 * nfp_net_irq_unmask() - Unmask स्वतःmasked पूर्णांकerrupt
 * @nn:       NFP Network काष्ठाure
 * @entry_nr: MSI-X table entry
 *
 * Clear the ICR क्रम the IRQ entry.
 */
अटल व्योम nfp_net_irq_unmask(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक entry_nr)
अणु
	nn_ग_लिखोb(nn, NFP_NET_CFG_ICR(entry_nr), NFP_NET_CFG_ICR_UNMASKED);
	nn_pci_flush(nn);
पूर्ण

/**
 * nfp_net_irqs_alloc() - allocates MSI-X irqs
 * @pdev:        PCI device काष्ठाure
 * @irq_entries: Array to be initialized and used to hold the irq entries
 * @min_irqs:    Minimal acceptable number of पूर्णांकerrupts
 * @wanted_irqs: Target number of पूर्णांकerrupts to allocate
 *
 * Return: Number of irqs obtained or 0 on error.
 */
अचिन्हित पूर्णांक
nfp_net_irqs_alloc(काष्ठा pci_dev *pdev, काष्ठा msix_entry *irq_entries,
		   अचिन्हित पूर्णांक min_irqs, अचिन्हित पूर्णांक wanted_irqs)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक got_irqs;

	क्रम (i = 0; i < wanted_irqs; i++)
		irq_entries[i].entry = i;

	got_irqs = pci_enable_msix_range(pdev, irq_entries,
					 min_irqs, wanted_irqs);
	अगर (got_irqs < 0) अणु
		dev_err(&pdev->dev, "Failed to enable %d-%d MSI-X (err=%d)\n",
			min_irqs, wanted_irqs, got_irqs);
		वापस 0;
	पूर्ण

	अगर (got_irqs < wanted_irqs)
		dev_warn(&pdev->dev, "Unable to allocate %d IRQs got only %d\n",
			 wanted_irqs, got_irqs);

	वापस got_irqs;
पूर्ण

/**
 * nfp_net_irqs_assign() - Assign पूर्णांकerrupts allocated बाह्यally to netdev
 * @nn:		 NFP Network काष्ठाure
 * @irq_entries: Table of allocated पूर्णांकerrupts
 * @n:		 Size of @irq_entries (number of entries to grab)
 *
 * After पूर्णांकerrupts are allocated with nfp_net_irqs_alloc() this function
 * should be called to assign them to a specअगरic netdev (port).
 */
व्योम
nfp_net_irqs_assign(काष्ठा nfp_net *nn, काष्ठा msix_entry *irq_entries,
		    अचिन्हित पूर्णांक n)
अणु
	काष्ठा nfp_net_dp *dp = &nn->dp;

	nn->max_r_vecs = n - NFP_NET_NON_Q_VECTORS;
	dp->num_r_vecs = nn->max_r_vecs;

	स_नकल(nn->irq_entries, irq_entries, माप(*irq_entries) * n);

	अगर (dp->num_rx_rings > dp->num_r_vecs ||
	    dp->num_tx_rings > dp->num_r_vecs)
		dev_warn(nn->dp.dev, "More rings (%d,%d) than vectors (%d).\n",
			 dp->num_rx_rings, dp->num_tx_rings,
			 dp->num_r_vecs);

	dp->num_rx_rings = min(dp->num_r_vecs, dp->num_rx_rings);
	dp->num_tx_rings = min(dp->num_r_vecs, dp->num_tx_rings);
	dp->num_stack_tx_rings = dp->num_tx_rings;
पूर्ण

/**
 * nfp_net_irqs_disable() - Disable पूर्णांकerrupts
 * @pdev:        PCI device काष्ठाure
 *
 * Unकरोes what @nfp_net_irqs_alloc() करोes.
 */
व्योम nfp_net_irqs_disable(काष्ठा pci_dev *pdev)
अणु
	pci_disable_msix(pdev);
पूर्ण

/**
 * nfp_net_irq_rxtx() - Interrupt service routine क्रम RX/TX rings.
 * @irq:      Interrupt
 * @data:     Opaque data काष्ठाure
 *
 * Return: Indicate अगर the पूर्णांकerrupt has been handled.
 */
अटल irqवापस_t nfp_net_irq_rxtx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nfp_net_r_vector *r_vec = data;

	napi_schedule_irqoff(&r_vec->napi);

	/* The FW स्वतः-masks any पूर्णांकerrupt, either via the MASK bit in
	 * the MSI-X table or via the per entry ICR field.  So there
	 * is no need to disable पूर्णांकerrupts here.
	 */
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nfp_ctrl_irq_rxtx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nfp_net_r_vector *r_vec = data;

	tasklet_schedule(&r_vec->tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * nfp_net_पढ़ो_link_status() - Reपढ़ो link status from control BAR
 * @nn:       NFP Network काष्ठाure
 */
अटल व्योम nfp_net_पढ़ो_link_status(काष्ठा nfp_net *nn)
अणु
	अचिन्हित दीर्घ flags;
	bool link_up;
	u32 sts;

	spin_lock_irqsave(&nn->link_status_lock, flags);

	sts = nn_पढ़ोl(nn, NFP_NET_CFG_STS);
	link_up = !!(sts & NFP_NET_CFG_STS_LINK);

	अगर (nn->link_up == link_up)
		जाओ out;

	nn->link_up = link_up;
	अगर (nn->port)
		set_bit(NFP_PORT_CHANGED, &nn->port->flags);

	अगर (nn->link_up) अणु
		netअगर_carrier_on(nn->dp.netdev);
		netdev_info(nn->dp.netdev, "NIC Link is Up\n");
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(nn->dp.netdev);
		netdev_info(nn->dp.netdev, "NIC Link is Down\n");
	पूर्ण
out:
	spin_unlock_irqrestore(&nn->link_status_lock, flags);
पूर्ण

/**
 * nfp_net_irq_lsc() - Interrupt service routine क्रम link state changes
 * @irq:      Interrupt
 * @data:     Opaque data काष्ठाure
 *
 * Return: Indicate अगर the पूर्णांकerrupt has been handled.
 */
अटल irqवापस_t nfp_net_irq_lsc(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nfp_net *nn = data;
	काष्ठा msix_entry *entry;

	entry = &nn->irq_entries[NFP_NET_IRQ_LSC_IDX];

	nfp_net_पढ़ो_link_status(nn);

	nfp_net_irq_unmask(nn, entry->entry);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * nfp_net_irq_exn() - Interrupt service routine क्रम exceptions
 * @irq:      Interrupt
 * @data:     Opaque data काष्ठाure
 *
 * Return: Indicate अगर the पूर्णांकerrupt has been handled.
 */
अटल irqवापस_t nfp_net_irq_exn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nfp_net *nn = data;

	nn_err(nn, "%s: UNIMPLEMENTED.\n", __func__);
	/* XXX TO BE IMPLEMENTED */
	वापस IRQ_HANDLED;
पूर्ण

/**
 * nfp_net_tx_ring_init() - Fill in the boilerplate क्रम a TX ring
 * @tx_ring:  TX ring काष्ठाure
 * @r_vec:    IRQ vector servicing this ring
 * @idx:      Ring index
 * @is_xdp:   Is this an XDP TX ring?
 */
अटल व्योम
nfp_net_tx_ring_init(काष्ठा nfp_net_tx_ring *tx_ring,
		     काष्ठा nfp_net_r_vector *r_vec, अचिन्हित पूर्णांक idx,
		     bool is_xdp)
अणु
	काष्ठा nfp_net *nn = r_vec->nfp_net;

	tx_ring->idx = idx;
	tx_ring->r_vec = r_vec;
	tx_ring->is_xdp = is_xdp;
	u64_stats_init(&tx_ring->r_vec->tx_sync);

	tx_ring->qcidx = tx_ring->idx * nn->stride_tx;
	tx_ring->qcp_q = nn->tx_bar + NFP_QCP_QUEUE_OFF(tx_ring->qcidx);
पूर्ण

/**
 * nfp_net_rx_ring_init() - Fill in the boilerplate क्रम a RX ring
 * @rx_ring:  RX ring काष्ठाure
 * @r_vec:    IRQ vector servicing this ring
 * @idx:      Ring index
 */
अटल व्योम
nfp_net_rx_ring_init(काष्ठा nfp_net_rx_ring *rx_ring,
		     काष्ठा nfp_net_r_vector *r_vec, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा nfp_net *nn = r_vec->nfp_net;

	rx_ring->idx = idx;
	rx_ring->r_vec = r_vec;
	u64_stats_init(&rx_ring->r_vec->rx_sync);

	rx_ring->fl_qcidx = rx_ring->idx * nn->stride_rx;
	rx_ring->qcp_fl = nn->rx_bar + NFP_QCP_QUEUE_OFF(rx_ring->fl_qcidx);
पूर्ण

/**
 * nfp_net_aux_irq_request() - Request an auxiliary पूर्णांकerrupt (LSC or EXN)
 * @nn:		NFP Network काष्ठाure
 * @ctrl_offset: Control BAR offset where IRQ configuration should be written
 * @क्रमmat:	म_लिखो-style क्रमmat to स्थिरruct the पूर्णांकerrupt name
 * @name:	Poपूर्णांकer to allocated space क्रम पूर्णांकerrupt name
 * @name_sz:	Size of space क्रम पूर्णांकerrupt name
 * @vector_idx:	Index of MSI-X vector used क्रम this पूर्णांकerrupt
 * @handler:	IRQ handler to रेजिस्टर क्रम this पूर्णांकerrupt
 */
अटल पूर्णांक
nfp_net_aux_irq_request(काष्ठा nfp_net *nn, u32 ctrl_offset,
			स्थिर अक्षर *क्रमmat, अक्षर *name, माप_प्रकार name_sz,
			अचिन्हित पूर्णांक vector_idx, irq_handler_t handler)
अणु
	काष्ठा msix_entry *entry;
	पूर्णांक err;

	entry = &nn->irq_entries[vector_idx];

	snम_लिखो(name, name_sz, क्रमmat, nfp_net_name(nn));
	err = request_irq(entry->vector, handler, 0, name, nn);
	अगर (err) अणु
		nn_err(nn, "Failed to request IRQ %d (err=%d).\n",
		       entry->vector, err);
		वापस err;
	पूर्ण
	nn_ग_लिखोb(nn, ctrl_offset, entry->entry);
	nfp_net_irq_unmask(nn, entry->entry);

	वापस 0;
पूर्ण

/**
 * nfp_net_aux_irq_मुक्त() - Free an auxiliary पूर्णांकerrupt (LSC or EXN)
 * @nn:		NFP Network काष्ठाure
 * @ctrl_offset: Control BAR offset where IRQ configuration should be written
 * @vector_idx:	Index of MSI-X vector used क्रम this पूर्णांकerrupt
 */
अटल व्योम nfp_net_aux_irq_मुक्त(काष्ठा nfp_net *nn, u32 ctrl_offset,
				 अचिन्हित पूर्णांक vector_idx)
अणु
	nn_ग_लिखोb(nn, ctrl_offset, 0xff);
	nn_pci_flush(nn);
	मुक्त_irq(nn->irq_entries[vector_idx].vector, nn);
पूर्ण

/* Transmit
 *
 * One queue controller peripheral queue is used क्रम transmit.  The
 * driver en-queues packets क्रम transmit by advancing the ग_लिखो
 * poपूर्णांकer.  The device indicates that packets have transmitted by
 * advancing the पढ़ो poपूर्णांकer.  The driver मुख्यtains a local copy of
 * the पढ़ो and ग_लिखो poपूर्णांकer in @काष्ठा nfp_net_tx_ring.  The driver
 * keeps @wr_p in sync with the queue controller ग_लिखो poपूर्णांकer and can
 * determine how many packets have been transmitted by comparing its
 * copy of the पढ़ो poपूर्णांकer @rd_p with the पढ़ो poपूर्णांकer मुख्यtained by
 * the queue controller peripheral.
 */

/**
 * nfp_net_tx_full() - Check अगर the TX ring is full
 * @tx_ring: TX ring to check
 * @dcnt:    Number of descriptors that need to be enqueued (must be >= 1)
 *
 * This function checks, based on the *host copy* of पढ़ो/ग_लिखो
 * poपूर्णांकer अगर a given TX ring is full.  The real TX queue may have
 * some newly made available slots.
 *
 * Return: True अगर the ring is full.
 */
अटल पूर्णांक nfp_net_tx_full(काष्ठा nfp_net_tx_ring *tx_ring, पूर्णांक dcnt)
अणु
	वापस (tx_ring->wr_p - tx_ring->rd_p) >= (tx_ring->cnt - dcnt);
पूर्ण

/* Wrappers क्रम deciding when to stop and restart TX queues */
अटल पूर्णांक nfp_net_tx_ring_should_wake(काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	वापस !nfp_net_tx_full(tx_ring, MAX_SKB_FRAGS * 4);
पूर्ण

अटल पूर्णांक nfp_net_tx_ring_should_stop(काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	वापस nfp_net_tx_full(tx_ring, MAX_SKB_FRAGS + 1);
पूर्ण

/**
 * nfp_net_tx_ring_stop() - stop tx ring
 * @nd_q:    netdev queue
 * @tx_ring: driver tx queue काष्ठाure
 *
 * Safely stop TX ring.  Remember that जबतक we are running .start_xmit()
 * someone अन्यथा may be cleaning the TX ring completions so we need to be
 * extra careful here.
 */
अटल व्योम nfp_net_tx_ring_stop(काष्ठा netdev_queue *nd_q,
				 काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	netअगर_tx_stop_queue(nd_q);

	/* We can race with the TX completion out of NAPI so recheck */
	smp_mb();
	अगर (unlikely(nfp_net_tx_ring_should_wake(tx_ring)))
		netअगर_tx_start_queue(nd_q);
पूर्ण

/**
 * nfp_net_tx_tso() - Set up Tx descriptor क्रम LSO
 * @r_vec: per-ring काष्ठाure
 * @txbuf: Poपूर्णांकer to driver soft TX descriptor
 * @txd: Poपूर्णांकer to HW TX descriptor
 * @skb: Poपूर्णांकer to SKB
 * @md_bytes: Prepend length
 *
 * Set up Tx descriptor क्रम LSO, करो nothing क्रम non-LSO skbs.
 * Return error on packet header greater than maximum supported LSO header size.
 */
अटल व्योम nfp_net_tx_tso(काष्ठा nfp_net_r_vector *r_vec,
			   काष्ठा nfp_net_tx_buf *txbuf,
			   काष्ठा nfp_net_tx_desc *txd, काष्ठा sk_buff *skb,
			   u32 md_bytes)
अणु
	u32 l3_offset, l4_offset, hdrlen;
	u16 mss;

	अगर (!skb_is_gso(skb))
		वापस;

	अगर (!skb->encapsulation) अणु
		l3_offset = skb_network_offset(skb);
		l4_offset = skb_transport_offset(skb);
		hdrlen = skb_transport_offset(skb) + tcp_hdrlen(skb);
	पूर्ण अन्यथा अणु
		l3_offset = skb_inner_network_offset(skb);
		l4_offset = skb_inner_transport_offset(skb);
		hdrlen = skb_inner_transport_header(skb) - skb->data +
			inner_tcp_hdrlen(skb);
	पूर्ण

	txbuf->pkt_cnt = skb_shinfo(skb)->gso_segs;
	txbuf->real_len += hdrlen * (txbuf->pkt_cnt - 1);

	mss = skb_shinfo(skb)->gso_size & PCIE_DESC_TX_MSS_MASK;
	txd->l3_offset = l3_offset - md_bytes;
	txd->l4_offset = l4_offset - md_bytes;
	txd->lso_hdrlen = hdrlen - md_bytes;
	txd->mss = cpu_to_le16(mss);
	txd->flags |= PCIE_DESC_TX_LSO;

	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_lso++;
	u64_stats_update_end(&r_vec->tx_sync);
पूर्ण

/**
 * nfp_net_tx_csum() - Set TX CSUM offload flags in TX descriptor
 * @dp:  NFP Net data path काष्ठा
 * @r_vec: per-ring काष्ठाure
 * @txbuf: Poपूर्णांकer to driver soft TX descriptor
 * @txd: Poपूर्णांकer to TX descriptor
 * @skb: Poपूर्णांकer to SKB
 *
 * This function sets the TX checksum flags in the TX descriptor based
 * on the configuration and the protocol of the packet to be transmitted.
 */
अटल व्योम nfp_net_tx_csum(काष्ठा nfp_net_dp *dp,
			    काष्ठा nfp_net_r_vector *r_vec,
			    काष्ठा nfp_net_tx_buf *txbuf,
			    काष्ठा nfp_net_tx_desc *txd, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा iphdr *iph;
	u8 l4_hdr;

	अगर (!(dp->ctrl & NFP_NET_CFG_CTRL_TXCSUM))
		वापस;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस;

	txd->flags |= PCIE_DESC_TX_CSUM;
	अगर (skb->encapsulation)
		txd->flags |= PCIE_DESC_TX_ENCAP;

	iph = skb->encapsulation ? inner_ip_hdr(skb) : ip_hdr(skb);
	ipv6h = skb->encapsulation ? inner_ipv6_hdr(skb) : ipv6_hdr(skb);

	अगर (iph->version == 4) अणु
		txd->flags |= PCIE_DESC_TX_IP4_CSUM;
		l4_hdr = iph->protocol;
	पूर्ण अन्यथा अगर (ipv6h->version == 6) अणु
		l4_hdr = ipv6h->nexthdr;
	पूर्ण अन्यथा अणु
		nn_dp_warn(dp, "partial checksum but ipv=%x!\n", iph->version);
		वापस;
	पूर्ण

	चयन (l4_hdr) अणु
	हाल IPPROTO_TCP:
		txd->flags |= PCIE_DESC_TX_TCP_CSUM;
		अवरोध;
	हाल IPPROTO_UDP:
		txd->flags |= PCIE_DESC_TX_UDP_CSUM;
		अवरोध;
	शेष:
		nn_dp_warn(dp, "partial checksum but l4 proto=%x!\n", l4_hdr);
		वापस;
	पूर्ण

	u64_stats_update_begin(&r_vec->tx_sync);
	अगर (skb->encapsulation)
		r_vec->hw_csum_tx_inner += txbuf->pkt_cnt;
	अन्यथा
		r_vec->hw_csum_tx += txbuf->pkt_cnt;
	u64_stats_update_end(&r_vec->tx_sync);
पूर्ण

अटल काष्ठा sk_buff *
nfp_net_tls_tx(काष्ठा nfp_net_dp *dp, काष्ठा nfp_net_r_vector *r_vec,
	       काष्ठा sk_buff *skb, u64 *tls_handle, पूर्णांक *nr_frags)
अणु
#अगर_घोषित CONFIG_TLS_DEVICE
	काष्ठा nfp_net_tls_offload_ctx *ntls;
	काष्ठा sk_buff *nskb;
	bool resync_pending;
	u32 datalen, seq;

	अगर (likely(!dp->ktls_tx))
		वापस skb;
	अगर (!skb->sk || !tls_is_sk_tx_device_offloaded(skb->sk))
		वापस skb;

	datalen = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	seq = ntohl(tcp_hdr(skb)->seq);
	ntls = tls_driver_ctx(skb->sk, TLS_OFFLOAD_CTX_सूची_TX);
	resync_pending = tls_offload_tx_resync_pending(skb->sk);
	अगर (unlikely(resync_pending || ntls->next_seq != seq)) अणु
		/* Pure ACK out of order alपढ़ोy */
		अगर (!datalen)
			वापस skb;

		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tls_tx_fallback++;
		u64_stats_update_end(&r_vec->tx_sync);

		nskb = tls_encrypt_skb(skb);
		अगर (!nskb) अणु
			u64_stats_update_begin(&r_vec->tx_sync);
			r_vec->tls_tx_no_fallback++;
			u64_stats_update_end(&r_vec->tx_sync);
			वापस शून्य;
		पूर्ण
		/* encryption wasn't necessary */
		अगर (nskb == skb)
			वापस skb;
		/* we करोn't re-check ring space */
		अगर (unlikely(skb_is_nonlinear(nskb))) अणु
			nn_dp_warn(dp, "tls_encrypt_skb() produced fragmented frame\n");
			u64_stats_update_begin(&r_vec->tx_sync);
			r_vec->tx_errors++;
			u64_stats_update_end(&r_vec->tx_sync);
			dev_kमुक्त_skb_any(nskb);
			वापस शून्य;
		पूर्ण

		/* jump क्रमward, a TX may have gotten lost, need to sync TX */
		अगर (!resync_pending && seq - ntls->next_seq < U32_MAX / 4)
			tls_offload_tx_resync_request(nskb->sk, seq,
						      ntls->next_seq);

		*nr_frags = 0;
		वापस nskb;
	पूर्ण

	अगर (datalen) अणु
		u64_stats_update_begin(&r_vec->tx_sync);
		अगर (!skb_is_gso(skb))
			r_vec->hw_tls_tx++;
		अन्यथा
			r_vec->hw_tls_tx += skb_shinfo(skb)->gso_segs;
		u64_stats_update_end(&r_vec->tx_sync);
	पूर्ण

	स_नकल(tls_handle, ntls->fw_handle, माप(ntls->fw_handle));
	ntls->next_seq += datalen;
#पूर्ण_अगर
	वापस skb;
पूर्ण

अटल व्योम nfp_net_tls_tx_unकरो(काष्ठा sk_buff *skb, u64 tls_handle)
अणु
#अगर_घोषित CONFIG_TLS_DEVICE
	काष्ठा nfp_net_tls_offload_ctx *ntls;
	u32 datalen, seq;

	अगर (!tls_handle)
		वापस;
	अगर (WARN_ON_ONCE(!skb->sk || !tls_is_sk_tx_device_offloaded(skb->sk)))
		वापस;

	datalen = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	seq = ntohl(tcp_hdr(skb)->seq);

	ntls = tls_driver_ctx(skb->sk, TLS_OFFLOAD_CTX_सूची_TX);
	अगर (ntls->next_seq == seq + datalen)
		ntls->next_seq = seq;
	अन्यथा
		WARN_ON_ONCE(1);
#पूर्ण_अगर
पूर्ण

अटल व्योम nfp_net_tx_xmit_more_flush(काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	wmb();
	nfp_qcp_wr_ptr_add(tx_ring->qcp_q, tx_ring->wr_ptr_add);
	tx_ring->wr_ptr_add = 0;
पूर्ण

अटल पूर्णांक nfp_net_prep_tx_meta(काष्ठा sk_buff *skb, u64 tls_handle)
अणु
	काष्ठा metadata_dst *md_dst = skb_metadata_dst(skb);
	अचिन्हित अक्षर *data;
	u32 meta_id = 0;
	पूर्णांक md_bytes;

	अगर (likely(!md_dst && !tls_handle))
		वापस 0;
	अगर (unlikely(md_dst && md_dst->type != METADATA_HW_PORT_MUX)) अणु
		अगर (!tls_handle)
			वापस 0;
		md_dst = शून्य;
	पूर्ण

	md_bytes = 4 + !!md_dst * 4 + !!tls_handle * 8;

	अगर (unlikely(skb_cow_head(skb, md_bytes)))
		वापस -ENOMEM;

	meta_id = 0;
	data = skb_push(skb, md_bytes) + md_bytes;
	अगर (md_dst) अणु
		data -= 4;
		put_unaligned_be32(md_dst->u.port_info.port_id, data);
		meta_id = NFP_NET_META_PORTID;
	पूर्ण
	अगर (tls_handle) अणु
		/* conn handle is opaque, we just use u64 to be able to quickly
		 * compare it to zero
		 */
		data -= 8;
		स_नकल(data, &tls_handle, माप(tls_handle));
		meta_id <<= NFP_NET_META_FIELD_SIZE;
		meta_id |= NFP_NET_META_CONN_HANDLE;
	पूर्ण

	data -= 4;
	put_unaligned_be32(meta_id, data);

	वापस md_bytes;
पूर्ण

/**
 * nfp_net_tx() - Main transmit entry poपूर्णांक
 * @skb:    SKB to transmit
 * @netdev: netdev काष्ठाure
 *
 * Return: NETDEV_TX_OK on success.
 */
अटल netdev_tx_t nfp_net_tx(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	स्थिर skb_frag_t *frag;
	पूर्णांक f, nr_frags, wr_idx, md_bytes;
	काष्ठा nfp_net_tx_ring *tx_ring;
	काष्ठा nfp_net_r_vector *r_vec;
	काष्ठा nfp_net_tx_buf *txbuf;
	काष्ठा nfp_net_tx_desc *txd;
	काष्ठा netdev_queue *nd_q;
	काष्ठा nfp_net_dp *dp;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक fsize;
	u64 tls_handle = 0;
	u16 qidx;

	dp = &nn->dp;
	qidx = skb_get_queue_mapping(skb);
	tx_ring = &dp->tx_rings[qidx];
	r_vec = tx_ring->r_vec;

	nr_frags = skb_shinfo(skb)->nr_frags;

	अगर (unlikely(nfp_net_tx_full(tx_ring, nr_frags + 1))) अणु
		nn_dp_warn(dp, "TX ring %d busy. wrp=%u rdp=%u\n",
			   qidx, tx_ring->wr_p, tx_ring->rd_p);
		nd_q = netdev_get_tx_queue(dp->netdev, qidx);
		netअगर_tx_stop_queue(nd_q);
		nfp_net_tx_xmit_more_flush(tx_ring);
		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tx_busy++;
		u64_stats_update_end(&r_vec->tx_sync);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	skb = nfp_net_tls_tx(dp, r_vec, skb, &tls_handle, &nr_frags);
	अगर (unlikely(!skb)) अणु
		nfp_net_tx_xmit_more_flush(tx_ring);
		वापस NETDEV_TX_OK;
	पूर्ण

	md_bytes = nfp_net_prep_tx_meta(skb, tls_handle);
	अगर (unlikely(md_bytes < 0))
		जाओ err_flush;

	/* Start with the head skbuf */
	dma_addr = dma_map_single(dp->dev, skb->data, skb_headlen(skb),
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dp->dev, dma_addr))
		जाओ err_dma_err;

	wr_idx = D_IDX(tx_ring, tx_ring->wr_p);

	/* Stash the soft descriptor of the head then initialize it */
	txbuf = &tx_ring->txbufs[wr_idx];
	txbuf->skb = skb;
	txbuf->dma_addr = dma_addr;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->real_len = skb->len;

	/* Build TX descriptor */
	txd = &tx_ring->txds[wr_idx];
	txd->offset_eop = (nr_frags ? 0 : PCIE_DESC_TX_EOP) | md_bytes;
	txd->dma_len = cpu_to_le16(skb_headlen(skb));
	nfp_desc_set_dma_addr(txd, dma_addr);
	txd->data_len = cpu_to_le16(skb->len);

	txd->flags = 0;
	txd->mss = 0;
	txd->lso_hdrlen = 0;

	/* Do not reorder - tso may adjust pkt cnt, vlan may override fields */
	nfp_net_tx_tso(r_vec, txbuf, txd, skb, md_bytes);
	nfp_net_tx_csum(dp, r_vec, txbuf, txd, skb);
	अगर (skb_vlan_tag_present(skb) && dp->ctrl & NFP_NET_CFG_CTRL_TXVLAN) अणु
		txd->flags |= PCIE_DESC_TX_VLAN;
		txd->vlan = cpu_to_le16(skb_vlan_tag_get(skb));
	पूर्ण

	/* Gather DMA */
	अगर (nr_frags > 0) अणु
		__le64 second_half;

		/* all descs must match except क्रम in addr, length and eop */
		second_half = txd->vals8[1];

		क्रम (f = 0; f < nr_frags; f++) अणु
			frag = &skb_shinfo(skb)->frags[f];
			fsize = skb_frag_size(frag);

			dma_addr = skb_frag_dma_map(dp->dev, frag, 0,
						    fsize, DMA_TO_DEVICE);
			अगर (dma_mapping_error(dp->dev, dma_addr))
				जाओ err_unmap;

			wr_idx = D_IDX(tx_ring, wr_idx + 1);
			tx_ring->txbufs[wr_idx].skb = skb;
			tx_ring->txbufs[wr_idx].dma_addr = dma_addr;
			tx_ring->txbufs[wr_idx].fidx = f;

			txd = &tx_ring->txds[wr_idx];
			txd->dma_len = cpu_to_le16(fsize);
			nfp_desc_set_dma_addr(txd, dma_addr);
			txd->offset_eop = md_bytes |
				((f == nr_frags - 1) ? PCIE_DESC_TX_EOP : 0);
			txd->vals8[1] = second_half;
		पूर्ण

		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tx_gather++;
		u64_stats_update_end(&r_vec->tx_sync);
	पूर्ण

	skb_tx_बारtamp(skb);

	nd_q = netdev_get_tx_queue(dp->netdev, tx_ring->idx);

	tx_ring->wr_p += nr_frags + 1;
	अगर (nfp_net_tx_ring_should_stop(tx_ring))
		nfp_net_tx_ring_stop(nd_q, tx_ring);

	tx_ring->wr_ptr_add += nr_frags + 1;
	अगर (__netdev_tx_sent_queue(nd_q, txbuf->real_len, netdev_xmit_more()))
		nfp_net_tx_xmit_more_flush(tx_ring);

	वापस NETDEV_TX_OK;

err_unmap:
	जबतक (--f >= 0) अणु
		frag = &skb_shinfo(skb)->frags[f];
		dma_unmap_page(dp->dev, tx_ring->txbufs[wr_idx].dma_addr,
			       skb_frag_size(frag), DMA_TO_DEVICE);
		tx_ring->txbufs[wr_idx].skb = शून्य;
		tx_ring->txbufs[wr_idx].dma_addr = 0;
		tx_ring->txbufs[wr_idx].fidx = -2;
		wr_idx = wr_idx - 1;
		अगर (wr_idx < 0)
			wr_idx += tx_ring->cnt;
	पूर्ण
	dma_unmap_single(dp->dev, tx_ring->txbufs[wr_idx].dma_addr,
			 skb_headlen(skb), DMA_TO_DEVICE);
	tx_ring->txbufs[wr_idx].skb = शून्य;
	tx_ring->txbufs[wr_idx].dma_addr = 0;
	tx_ring->txbufs[wr_idx].fidx = -2;
err_dma_err:
	nn_dp_warn(dp, "Failed to map DMA TX buffer\n");
err_flush:
	nfp_net_tx_xmit_more_flush(tx_ring);
	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_errors++;
	u64_stats_update_end(&r_vec->tx_sync);
	nfp_net_tls_tx_unकरो(skb, tls_handle);
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * nfp_net_tx_complete() - Handled completed TX packets
 * @tx_ring:	TX ring काष्ठाure
 * @budget:	NAPI budget (only used as bool to determine अगर in NAPI context)
 */
अटल व्योम nfp_net_tx_complete(काष्ठा nfp_net_tx_ring *tx_ring, पूर्णांक budget)
अणु
	काष्ठा nfp_net_r_vector *r_vec = tx_ring->r_vec;
	काष्ठा nfp_net_dp *dp = &r_vec->nfp_net->dp;
	काष्ठा netdev_queue *nd_q;
	u32 करोne_pkts = 0, करोne_bytes = 0;
	u32 qcp_rd_p;
	पूर्णांक toकरो;

	अगर (tx_ring->wr_p == tx_ring->rd_p)
		वापस;

	/* Work out how many descriptors have been transmitted */
	qcp_rd_p = nfp_qcp_rd_ptr_पढ़ो(tx_ring->qcp_q);

	अगर (qcp_rd_p == tx_ring->qcp_rd_p)
		वापस;

	toकरो = D_IDX(tx_ring, qcp_rd_p - tx_ring->qcp_rd_p);

	जबतक (toकरो--) अणु
		स्थिर skb_frag_t *frag;
		काष्ठा nfp_net_tx_buf *tx_buf;
		काष्ठा sk_buff *skb;
		पूर्णांक fidx, nr_frags;
		पूर्णांक idx;

		idx = D_IDX(tx_ring, tx_ring->rd_p++);
		tx_buf = &tx_ring->txbufs[idx];

		skb = tx_buf->skb;
		अगर (!skb)
			जारी;

		nr_frags = skb_shinfo(skb)->nr_frags;
		fidx = tx_buf->fidx;

		अगर (fidx == -1) अणु
			/* unmap head */
			dma_unmap_single(dp->dev, tx_buf->dma_addr,
					 skb_headlen(skb), DMA_TO_DEVICE);

			करोne_pkts += tx_buf->pkt_cnt;
			करोne_bytes += tx_buf->real_len;
		पूर्ण अन्यथा अणु
			/* unmap fragment */
			frag = &skb_shinfo(skb)->frags[fidx];
			dma_unmap_page(dp->dev, tx_buf->dma_addr,
				       skb_frag_size(frag), DMA_TO_DEVICE);
		पूर्ण

		/* check क्रम last gather fragment */
		अगर (fidx == nr_frags - 1)
			napi_consume_skb(skb, budget);

		tx_buf->dma_addr = 0;
		tx_buf->skb = शून्य;
		tx_buf->fidx = -2;
	पूर्ण

	tx_ring->qcp_rd_p = qcp_rd_p;

	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_bytes += करोne_bytes;
	r_vec->tx_pkts += करोne_pkts;
	u64_stats_update_end(&r_vec->tx_sync);

	अगर (!dp->netdev)
		वापस;

	nd_q = netdev_get_tx_queue(dp->netdev, tx_ring->idx);
	netdev_tx_completed_queue(nd_q, करोne_pkts, करोne_bytes);
	अगर (nfp_net_tx_ring_should_wake(tx_ring)) अणु
		/* Make sure TX thपढ़ो will see updated tx_ring->rd_p */
		smp_mb();

		अगर (unlikely(netअगर_tx_queue_stopped(nd_q)))
			netअगर_tx_wake_queue(nd_q);
	पूर्ण

	WARN_ONCE(tx_ring->wr_p - tx_ring->rd_p > tx_ring->cnt,
		  "TX ring corruption rd_p=%u wr_p=%u cnt=%u\n",
		  tx_ring->rd_p, tx_ring->wr_p, tx_ring->cnt);
पूर्ण

अटल bool nfp_net_xdp_complete(काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	काष्ठा nfp_net_r_vector *r_vec = tx_ring->r_vec;
	u32 करोne_pkts = 0, करोne_bytes = 0;
	bool करोne_all;
	पूर्णांक idx, toकरो;
	u32 qcp_rd_p;

	/* Work out how many descriptors have been transmitted */
	qcp_rd_p = nfp_qcp_rd_ptr_पढ़ो(tx_ring->qcp_q);

	अगर (qcp_rd_p == tx_ring->qcp_rd_p)
		वापस true;

	toकरो = D_IDX(tx_ring, qcp_rd_p - tx_ring->qcp_rd_p);

	करोne_all = toकरो <= NFP_NET_XDP_MAX_COMPLETE;
	toकरो = min(toकरो, NFP_NET_XDP_MAX_COMPLETE);

	tx_ring->qcp_rd_p = D_IDX(tx_ring, tx_ring->qcp_rd_p + toकरो);

	करोne_pkts = toकरो;
	जबतक (toकरो--) अणु
		idx = D_IDX(tx_ring, tx_ring->rd_p);
		tx_ring->rd_p++;

		करोne_bytes += tx_ring->txbufs[idx].real_len;
	पूर्ण

	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_bytes += करोne_bytes;
	r_vec->tx_pkts += करोne_pkts;
	u64_stats_update_end(&r_vec->tx_sync);

	WARN_ONCE(tx_ring->wr_p - tx_ring->rd_p > tx_ring->cnt,
		  "XDP TX ring corruption rd_p=%u wr_p=%u cnt=%u\n",
		  tx_ring->rd_p, tx_ring->wr_p, tx_ring->cnt);

	वापस करोne_all;
पूर्ण

/**
 * nfp_net_tx_ring_reset() - Free any untransmitted buffers and reset poपूर्णांकers
 * @dp:		NFP Net data path काष्ठा
 * @tx_ring:	TX ring काष्ठाure
 *
 * Assumes that the device is stopped, must be idempotent.
 */
अटल व्योम
nfp_net_tx_ring_reset(काष्ठा nfp_net_dp *dp, काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	स्थिर skb_frag_t *frag;
	काष्ठा netdev_queue *nd_q;

	जबतक (!tx_ring->is_xdp && tx_ring->rd_p != tx_ring->wr_p) अणु
		काष्ठा nfp_net_tx_buf *tx_buf;
		काष्ठा sk_buff *skb;
		पूर्णांक idx, nr_frags;

		idx = D_IDX(tx_ring, tx_ring->rd_p);
		tx_buf = &tx_ring->txbufs[idx];

		skb = tx_ring->txbufs[idx].skb;
		nr_frags = skb_shinfo(skb)->nr_frags;

		अगर (tx_buf->fidx == -1) अणु
			/* unmap head */
			dma_unmap_single(dp->dev, tx_buf->dma_addr,
					 skb_headlen(skb), DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			/* unmap fragment */
			frag = &skb_shinfo(skb)->frags[tx_buf->fidx];
			dma_unmap_page(dp->dev, tx_buf->dma_addr,
				       skb_frag_size(frag), DMA_TO_DEVICE);
		पूर्ण

		/* check क्रम last gather fragment */
		अगर (tx_buf->fidx == nr_frags - 1)
			dev_kमुक्त_skb_any(skb);

		tx_buf->dma_addr = 0;
		tx_buf->skb = शून्य;
		tx_buf->fidx = -2;

		tx_ring->qcp_rd_p++;
		tx_ring->rd_p++;
	पूर्ण

	स_रखो(tx_ring->txds, 0, tx_ring->size);
	tx_ring->wr_p = 0;
	tx_ring->rd_p = 0;
	tx_ring->qcp_rd_p = 0;
	tx_ring->wr_ptr_add = 0;

	अगर (tx_ring->is_xdp || !dp->netdev)
		वापस;

	nd_q = netdev_get_tx_queue(dp->netdev, tx_ring->idx);
	netdev_tx_reset_queue(nd_q);
पूर्ण

अटल व्योम nfp_net_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	nn_warn(nn, "TX watchdog timeout on ring: %u\n", txqueue);
पूर्ण

/* Receive processing
 */
अटल अचिन्हित पूर्णांक
nfp_net_calc_fl_bufsz(काष्ठा nfp_net_dp *dp)
अणु
	अचिन्हित पूर्णांक fl_bufsz;

	fl_bufsz = NFP_NET_RX_BUF_HEADROOM;
	fl_bufsz += dp->rx_dma_off;
	अगर (dp->rx_offset == NFP_NET_CFG_RX_OFFSET_DYNAMIC)
		fl_bufsz += NFP_NET_MAX_PREPEND;
	अन्यथा
		fl_bufsz += dp->rx_offset;
	fl_bufsz += ETH_HLEN + VLAN_HLEN * 2 + dp->mtu;

	fl_bufsz = SKB_DATA_ALIGN(fl_bufsz);
	fl_bufsz += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	वापस fl_bufsz;
पूर्ण

अटल व्योम
nfp_net_मुक्त_frag(व्योम *frag, bool xdp)
अणु
	अगर (!xdp)
		skb_मुक्त_frag(frag);
	अन्यथा
		__मुक्त_page(virt_to_page(frag));
पूर्ण

/**
 * nfp_net_rx_alloc_one() - Allocate and map page frag क्रम RX
 * @dp:		NFP Net data path काष्ठा
 * @dma_addr:	Poपूर्णांकer to storage क्रम DMA address (output param)
 *
 * This function will allcate a new page frag, map it क्रम DMA.
 *
 * Return: allocated page frag or शून्य on failure.
 */
अटल व्योम *nfp_net_rx_alloc_one(काष्ठा nfp_net_dp *dp, dma_addr_t *dma_addr)
अणु
	व्योम *frag;

	अगर (!dp->xdp_prog) अणु
		frag = netdev_alloc_frag(dp->fl_bufsz);
	पूर्ण अन्यथा अणु
		काष्ठा page *page;

		page = alloc_page(GFP_KERNEL);
		frag = page ? page_address(page) : शून्य;
	पूर्ण
	अगर (!frag) अणु
		nn_dp_warn(dp, "Failed to alloc receive page frag\n");
		वापस शून्य;
	पूर्ण

	*dma_addr = nfp_net_dma_map_rx(dp, frag);
	अगर (dma_mapping_error(dp->dev, *dma_addr)) अणु
		nfp_net_मुक्त_frag(frag, dp->xdp_prog);
		nn_dp_warn(dp, "Failed to map DMA RX buffer\n");
		वापस शून्य;
	पूर्ण

	वापस frag;
पूर्ण

अटल व्योम *nfp_net_napi_alloc_one(काष्ठा nfp_net_dp *dp, dma_addr_t *dma_addr)
अणु
	व्योम *frag;

	अगर (!dp->xdp_prog) अणु
		frag = napi_alloc_frag(dp->fl_bufsz);
		अगर (unlikely(!frag))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा page *page;

		page = dev_alloc_page();
		अगर (unlikely(!page))
			वापस शून्य;
		frag = page_address(page);
	पूर्ण

	*dma_addr = nfp_net_dma_map_rx(dp, frag);
	अगर (dma_mapping_error(dp->dev, *dma_addr)) अणु
		nfp_net_मुक्त_frag(frag, dp->xdp_prog);
		nn_dp_warn(dp, "Failed to map DMA RX buffer\n");
		वापस शून्य;
	पूर्ण

	वापस frag;
पूर्ण

/**
 * nfp_net_rx_give_one() - Put mapped skb on the software and hardware rings
 * @dp:		NFP Net data path काष्ठा
 * @rx_ring:	RX ring काष्ठाure
 * @frag:	page fragment buffer
 * @dma_addr:	DMA address of skb mapping
 */
अटल व्योम nfp_net_rx_give_one(स्थिर काष्ठा nfp_net_dp *dp,
				काष्ठा nfp_net_rx_ring *rx_ring,
				व्योम *frag, dma_addr_t dma_addr)
अणु
	अचिन्हित पूर्णांक wr_idx;

	wr_idx = D_IDX(rx_ring, rx_ring->wr_p);

	nfp_net_dma_sync_dev_rx(dp, dma_addr);

	/* Stash SKB and DMA address away */
	rx_ring->rxbufs[wr_idx].frag = frag;
	rx_ring->rxbufs[wr_idx].dma_addr = dma_addr;

	/* Fill मुक्तlist descriptor */
	rx_ring->rxds[wr_idx].fld.reserved = 0;
	rx_ring->rxds[wr_idx].fld.meta_len_dd = 0;
	nfp_desc_set_dma_addr(&rx_ring->rxds[wr_idx].fld,
			      dma_addr + dp->rx_dma_off);

	rx_ring->wr_p++;
	अगर (!(rx_ring->wr_p % NFP_NET_FL_BATCH)) अणु
		/* Update ग_लिखो poपूर्णांकer of the मुक्तlist queue. Make
		 * sure all ग_लिखोs are flushed beक्रमe telling the hardware.
		 */
		wmb();
		nfp_qcp_wr_ptr_add(rx_ring->qcp_fl, NFP_NET_FL_BATCH);
	पूर्ण
पूर्ण

/**
 * nfp_net_rx_ring_reset() - Reflect in SW state of मुक्तlist after disable
 * @rx_ring:	RX ring काष्ठाure
 *
 * Assumes that the device is stopped, must be idempotent.
 */
अटल व्योम nfp_net_rx_ring_reset(काष्ठा nfp_net_rx_ring *rx_ring)
अणु
	अचिन्हित पूर्णांक wr_idx, last_idx;

	/* wr_p == rd_p means ring was never fed FL bufs.  RX rings are always
	 * kept at cnt - 1 FL bufs.
	 */
	अगर (rx_ring->wr_p == 0 && rx_ring->rd_p == 0)
		वापस;

	/* Move the empty entry to the end of the list */
	wr_idx = D_IDX(rx_ring, rx_ring->wr_p);
	last_idx = rx_ring->cnt - 1;
	rx_ring->rxbufs[wr_idx].dma_addr = rx_ring->rxbufs[last_idx].dma_addr;
	rx_ring->rxbufs[wr_idx].frag = rx_ring->rxbufs[last_idx].frag;
	rx_ring->rxbufs[last_idx].dma_addr = 0;
	rx_ring->rxbufs[last_idx].frag = शून्य;

	स_रखो(rx_ring->rxds, 0, rx_ring->size);
	rx_ring->wr_p = 0;
	rx_ring->rd_p = 0;
पूर्ण

/**
 * nfp_net_rx_ring_bufs_मुक्त() - Free any buffers currently on the RX ring
 * @dp:		NFP Net data path काष्ठा
 * @rx_ring:	RX ring to हटाओ buffers from
 *
 * Assumes that the device is stopped and buffers are in [0, ring->cnt - 1)
 * entries.  After device is disabled nfp_net_rx_ring_reset() must be called
 * to restore required ring geometry.
 */
अटल व्योम
nfp_net_rx_ring_bufs_मुक्त(काष्ठा nfp_net_dp *dp,
			  काष्ठा nfp_net_rx_ring *rx_ring)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < rx_ring->cnt - 1; i++) अणु
		/* शून्य skb can only happen when initial filling of the ring
		 * fails to allocate enough buffers and calls here to मुक्त
		 * alपढ़ोy allocated ones.
		 */
		अगर (!rx_ring->rxbufs[i].frag)
			जारी;

		nfp_net_dma_unmap_rx(dp, rx_ring->rxbufs[i].dma_addr);
		nfp_net_मुक्त_frag(rx_ring->rxbufs[i].frag, dp->xdp_prog);
		rx_ring->rxbufs[i].dma_addr = 0;
		rx_ring->rxbufs[i].frag = शून्य;
	पूर्ण
पूर्ण

/**
 * nfp_net_rx_ring_bufs_alloc() - Fill RX ring with buffers (करोn't give to FW)
 * @dp:		NFP Net data path काष्ठा
 * @rx_ring:	RX ring to हटाओ buffers from
 */
अटल पूर्णांक
nfp_net_rx_ring_bufs_alloc(काष्ठा nfp_net_dp *dp,
			   काष्ठा nfp_net_rx_ring *rx_ring)
अणु
	काष्ठा nfp_net_rx_buf *rxbufs;
	अचिन्हित पूर्णांक i;

	rxbufs = rx_ring->rxbufs;

	क्रम (i = 0; i < rx_ring->cnt - 1; i++) अणु
		rxbufs[i].frag = nfp_net_rx_alloc_one(dp, &rxbufs[i].dma_addr);
		अगर (!rxbufs[i].frag) अणु
			nfp_net_rx_ring_bufs_मुक्त(dp, rx_ring);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nfp_net_rx_ring_fill_मुक्तlist() - Give buffers from the ring to FW
 * @dp:	     NFP Net data path काष्ठा
 * @rx_ring: RX ring to fill
 */
अटल व्योम
nfp_net_rx_ring_fill_मुक्तlist(काष्ठा nfp_net_dp *dp,
			      काष्ठा nfp_net_rx_ring *rx_ring)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < rx_ring->cnt - 1; i++)
		nfp_net_rx_give_one(dp, rx_ring, rx_ring->rxbufs[i].frag,
				    rx_ring->rxbufs[i].dma_addr);
पूर्ण

/**
 * nfp_net_rx_csum_has_errors() - group check अगर rxd has any csum errors
 * @flags: RX descriptor flags field in CPU byte order
 */
अटल पूर्णांक nfp_net_rx_csum_has_errors(u16 flags)
अणु
	u16 csum_all_checked, csum_all_ok;

	csum_all_checked = flags & __PCIE_DESC_RX_CSUM_ALL;
	csum_all_ok = flags & __PCIE_DESC_RX_CSUM_ALL_OK;

	वापस csum_all_checked != (csum_all_ok << PCIE_DESC_RX_CSUM_OK_SHIFT);
पूर्ण

/**
 * nfp_net_rx_csum() - set SKB checksum field based on RX descriptor flags
 * @dp:  NFP Net data path काष्ठा
 * @r_vec: per-ring काष्ठाure
 * @rxd: Poपूर्णांकer to RX descriptor
 * @meta: Parsed metadata prepend
 * @skb: Poपूर्णांकer to SKB
 */
अटल व्योम nfp_net_rx_csum(काष्ठा nfp_net_dp *dp,
			    काष्ठा nfp_net_r_vector *r_vec,
			    काष्ठा nfp_net_rx_desc *rxd,
			    काष्ठा nfp_meta_parsed *meta, काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	अगर (!(dp->netdev->features & NETIF_F_RXCSUM))
		वापस;

	अगर (meta->csum_type) अणु
		skb->ip_summed = meta->csum_type;
		skb->csum = meta->csum;
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_complete++;
		u64_stats_update_end(&r_vec->rx_sync);
		वापस;
	पूर्ण

	अगर (nfp_net_rx_csum_has_errors(le16_to_cpu(rxd->rxd.flags))) अणु
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_error++;
		u64_stats_update_end(&r_vec->rx_sync);
		वापस;
	पूर्ण

	/* Assume that the firmware will never report inner CSUM_OK unless outer
	 * L4 headers were successfully parsed. FW will always report zero UDP
	 * checksum as CSUM_OK.
	 */
	अगर (rxd->rxd.flags & PCIE_DESC_RX_TCP_CSUM_OK ||
	    rxd->rxd.flags & PCIE_DESC_RX_UDP_CSUM_OK) अणु
		__skb_incr_checksum_unnecessary(skb);
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_ok++;
		u64_stats_update_end(&r_vec->rx_sync);
	पूर्ण

	अगर (rxd->rxd.flags & PCIE_DESC_RX_I_TCP_CSUM_OK ||
	    rxd->rxd.flags & PCIE_DESC_RX_I_UDP_CSUM_OK) अणु
		__skb_incr_checksum_unnecessary(skb);
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_inner_ok++;
		u64_stats_update_end(&r_vec->rx_sync);
	पूर्ण
पूर्ण

अटल व्योम
nfp_net_set_hash(काष्ठा net_device *netdev, काष्ठा nfp_meta_parsed *meta,
		 अचिन्हित पूर्णांक type, __be32 *hash)
अणु
	अगर (!(netdev->features & NETIF_F_RXHASH))
		वापस;

	चयन (type) अणु
	हाल NFP_NET_RSS_IPV4:
	हाल NFP_NET_RSS_IPV6:
	हाल NFP_NET_RSS_IPV6_EX:
		meta->hash_type = PKT_HASH_TYPE_L3;
		अवरोध;
	शेष:
		meta->hash_type = PKT_HASH_TYPE_L4;
		अवरोध;
	पूर्ण

	meta->hash = get_unaligned_be32(hash);
पूर्ण

अटल व्योम
nfp_net_set_hash_desc(काष्ठा net_device *netdev, काष्ठा nfp_meta_parsed *meta,
		      व्योम *data, काष्ठा nfp_net_rx_desc *rxd)
अणु
	काष्ठा nfp_net_rx_hash *rx_hash = data;

	अगर (!(rxd->rxd.flags & PCIE_DESC_RX_RSS))
		वापस;

	nfp_net_set_hash(netdev, meta, get_unaligned_be32(&rx_hash->hash_type),
			 &rx_hash->hash);
पूर्ण

अटल bool
nfp_net_parse_meta(काष्ठा net_device *netdev, काष्ठा nfp_meta_parsed *meta,
		   व्योम *data, व्योम *pkt, अचिन्हित पूर्णांक pkt_len, पूर्णांक meta_len)
अणु
	u32 meta_info;

	meta_info = get_unaligned_be32(data);
	data += 4;

	जबतक (meta_info) अणु
		चयन (meta_info & NFP_NET_META_FIELD_MASK) अणु
		हाल NFP_NET_META_HASH:
			meta_info >>= NFP_NET_META_FIELD_SIZE;
			nfp_net_set_hash(netdev, meta,
					 meta_info & NFP_NET_META_FIELD_MASK,
					 (__be32 *)data);
			data += 4;
			अवरोध;
		हाल NFP_NET_META_MARK:
			meta->mark = get_unaligned_be32(data);
			data += 4;
			अवरोध;
		हाल NFP_NET_META_PORTID:
			meta->portid = get_unaligned_be32(data);
			data += 4;
			अवरोध;
		हाल NFP_NET_META_CSUM:
			meta->csum_type = CHECKSUM_COMPLETE;
			meta->csum =
				(__क्रमce __wsum)__get_unaligned_cpu32(data);
			data += 4;
			अवरोध;
		हाल NFP_NET_META_RESYNC_INFO:
			अगर (nfp_net_tls_rx_resync_req(netdev, data, pkt,
						      pkt_len))
				वापस शून्य;
			data += माप(काष्ठा nfp_net_tls_resync_req);
			अवरोध;
		शेष:
			वापस true;
		पूर्ण

		meta_info >>= NFP_NET_META_FIELD_SIZE;
	पूर्ण

	वापस data != pkt;
पूर्ण

अटल व्योम
nfp_net_rx_drop(स्थिर काष्ठा nfp_net_dp *dp, काष्ठा nfp_net_r_vector *r_vec,
		काष्ठा nfp_net_rx_ring *rx_ring, काष्ठा nfp_net_rx_buf *rxbuf,
		काष्ठा sk_buff *skb)
अणु
	u64_stats_update_begin(&r_vec->rx_sync);
	r_vec->rx_drops++;
	/* If we have both skb and rxbuf the replacement buffer allocation
	 * must have failed, count this as an alloc failure.
	 */
	अगर (skb && rxbuf)
		r_vec->rx_replace_buf_alloc_fail++;
	u64_stats_update_end(&r_vec->rx_sync);

	/* skb is build based on the frag, मुक्त_skb() would मुक्त the frag
	 * so to be able to reuse it we need an extra ref.
	 */
	अगर (skb && rxbuf && skb->head == rxbuf->frag)
		page_ref_inc(virt_to_head_page(rxbuf->frag));
	अगर (rxbuf)
		nfp_net_rx_give_one(dp, rx_ring, rxbuf->frag, rxbuf->dma_addr);
	अगर (skb)
		dev_kमुक्त_skb_any(skb);
पूर्ण

अटल bool
nfp_net_tx_xdp_buf(काष्ठा nfp_net_dp *dp, काष्ठा nfp_net_rx_ring *rx_ring,
		   काष्ठा nfp_net_tx_ring *tx_ring,
		   काष्ठा nfp_net_rx_buf *rxbuf, अचिन्हित पूर्णांक dma_off,
		   अचिन्हित पूर्णांक pkt_len, bool *completed)
अणु
	अचिन्हित पूर्णांक dma_map_sz = dp->fl_bufsz - NFP_NET_RX_BUF_NON_DATA;
	काष्ठा nfp_net_tx_buf *txbuf;
	काष्ठा nfp_net_tx_desc *txd;
	पूर्णांक wr_idx;

	/* Reject अगर xdp_adjust_tail grow packet beyond DMA area */
	अगर (pkt_len + dma_off > dma_map_sz)
		वापस false;

	अगर (unlikely(nfp_net_tx_full(tx_ring, 1))) अणु
		अगर (!*completed) अणु
			nfp_net_xdp_complete(tx_ring);
			*completed = true;
		पूर्ण

		अगर (unlikely(nfp_net_tx_full(tx_ring, 1))) अणु
			nfp_net_rx_drop(dp, rx_ring->r_vec, rx_ring, rxbuf,
					शून्य);
			वापस false;
		पूर्ण
	पूर्ण

	wr_idx = D_IDX(tx_ring, tx_ring->wr_p);

	/* Stash the soft descriptor of the head then initialize it */
	txbuf = &tx_ring->txbufs[wr_idx];

	nfp_net_rx_give_one(dp, rx_ring, txbuf->frag, txbuf->dma_addr);

	txbuf->frag = rxbuf->frag;
	txbuf->dma_addr = rxbuf->dma_addr;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->real_len = pkt_len;

	dma_sync_single_क्रम_device(dp->dev, rxbuf->dma_addr + dma_off,
				   pkt_len, DMA_BIसूचीECTIONAL);

	/* Build TX descriptor */
	txd = &tx_ring->txds[wr_idx];
	txd->offset_eop = PCIE_DESC_TX_EOP;
	txd->dma_len = cpu_to_le16(pkt_len);
	nfp_desc_set_dma_addr(txd, rxbuf->dma_addr + dma_off);
	txd->data_len = cpu_to_le16(pkt_len);

	txd->flags = 0;
	txd->mss = 0;
	txd->lso_hdrlen = 0;

	tx_ring->wr_p++;
	tx_ring->wr_ptr_add++;
	वापस true;
पूर्ण

/**
 * nfp_net_rx() - receive up to @budget packets on @rx_ring
 * @rx_ring:   RX ring to receive from
 * @budget:    NAPI budget
 *
 * Note, this function is separated out from the napi poll function to
 * more cleanly separate packet receive code from other bookkeeping
 * functions perक्रमmed in the napi poll function.
 *
 * Return: Number of packets received.
 */
अटल पूर्णांक nfp_net_rx(काष्ठा nfp_net_rx_ring *rx_ring, पूर्णांक budget)
अणु
	काष्ठा nfp_net_r_vector *r_vec = rx_ring->r_vec;
	काष्ठा nfp_net_dp *dp = &r_vec->nfp_net->dp;
	काष्ठा nfp_net_tx_ring *tx_ring;
	काष्ठा bpf_prog *xdp_prog;
	bool xdp_tx_cmpl = false;
	अचिन्हित पूर्णांक true_bufsz;
	काष्ठा sk_buff *skb;
	पूर्णांक pkts_polled = 0;
	काष्ठा xdp_buff xdp;
	पूर्णांक idx;

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(dp->xdp_prog);
	true_bufsz = xdp_prog ? PAGE_SIZE : dp->fl_bufsz;
	xdp_init_buff(&xdp, PAGE_SIZE - NFP_NET_RX_BUF_HEADROOM,
		      &rx_ring->xdp_rxq);
	tx_ring = r_vec->xdp_ring;

	जबतक (pkts_polled < budget) अणु
		अचिन्हित पूर्णांक meta_len, data_len, meta_off, pkt_len, pkt_off;
		काष्ठा nfp_net_rx_buf *rxbuf;
		काष्ठा nfp_net_rx_desc *rxd;
		काष्ठा nfp_meta_parsed meta;
		bool redir_egress = false;
		काष्ठा net_device *netdev;
		dma_addr_t new_dma_addr;
		u32 meta_len_xdp = 0;
		व्योम *new_frag;

		idx = D_IDX(rx_ring, rx_ring->rd_p);

		rxd = &rx_ring->rxds[idx];
		अगर (!(rxd->rxd.meta_len_dd & PCIE_DESC_RX_DD))
			अवरोध;

		/* Memory barrier to ensure that we won't करो other पढ़ोs
		 * beक्रमe the DD bit.
		 */
		dma_rmb();

		स_रखो(&meta, 0, माप(meta));

		rx_ring->rd_p++;
		pkts_polled++;

		rxbuf =	&rx_ring->rxbufs[idx];
		/*         < meta_len >
		 *  <-- [rx_offset] -->
		 *  ---------------------------------------------------------
		 * | [XX] |  metadata  |             packet           | XXXX |
		 *  ---------------------------------------------------------
		 *         <---------------- data_len --------------->
		 *
		 * The rx_offset is fixed क्रम all packets, the meta_len can vary
		 * on a packet by packet basis. If rx_offset is set to zero
		 * (_RX_OFFSET_DYNAMIC) metadata starts at the beginning of the
		 * buffer and is immediately followed by the packet (no [XX]).
		 */
		meta_len = rxd->rxd.meta_len_dd & PCIE_DESC_RX_META_LEN_MASK;
		data_len = le16_to_cpu(rxd->rxd.data_len);
		pkt_len = data_len - meta_len;

		pkt_off = NFP_NET_RX_BUF_HEADROOM + dp->rx_dma_off;
		अगर (dp->rx_offset == NFP_NET_CFG_RX_OFFSET_DYNAMIC)
			pkt_off += meta_len;
		अन्यथा
			pkt_off += dp->rx_offset;
		meta_off = pkt_off - meta_len;

		/* Stats update */
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->rx_pkts++;
		r_vec->rx_bytes += pkt_len;
		u64_stats_update_end(&r_vec->rx_sync);

		अगर (unlikely(meta_len > NFP_NET_MAX_PREPEND ||
			     (dp->rx_offset && meta_len > dp->rx_offset))) अणु
			nn_dp_warn(dp, "oversized RX packet metadata %u\n",
				   meta_len);
			nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, शून्य);
			जारी;
		पूर्ण

		nfp_net_dma_sync_cpu_rx(dp, rxbuf->dma_addr + meta_off,
					data_len);

		अगर (!dp->chained_metadata_क्रमmat) अणु
			nfp_net_set_hash_desc(dp->netdev, &meta,
					      rxbuf->frag + meta_off, rxd);
		पूर्ण अन्यथा अगर (meta_len) अणु
			अगर (unlikely(nfp_net_parse_meta(dp->netdev, &meta,
							rxbuf->frag + meta_off,
							rxbuf->frag + pkt_off,
							pkt_len, meta_len))) अणु
				nn_dp_warn(dp, "invalid RX packet metadata\n");
				nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf,
						शून्य);
				जारी;
			पूर्ण
		पूर्ण

		अगर (xdp_prog && !meta.portid) अणु
			व्योम *orig_data = rxbuf->frag + pkt_off;
			अचिन्हित पूर्णांक dma_off;
			पूर्णांक act;

			xdp_prepare_buff(&xdp,
					 rxbuf->frag + NFP_NET_RX_BUF_HEADROOM,
					 pkt_off - NFP_NET_RX_BUF_HEADROOM,
					 pkt_len, true);

			act = bpf_prog_run_xdp(xdp_prog, &xdp);

			pkt_len = xdp.data_end - xdp.data;
			pkt_off += xdp.data - orig_data;

			चयन (act) अणु
			हाल XDP_PASS:
				meta_len_xdp = xdp.data - xdp.data_meta;
				अवरोध;
			हाल XDP_TX:
				dma_off = pkt_off - NFP_NET_RX_BUF_HEADROOM;
				अगर (unlikely(!nfp_net_tx_xdp_buf(dp, rx_ring,
								 tx_ring, rxbuf,
								 dma_off,
								 pkt_len,
								 &xdp_tx_cmpl)))
					trace_xdp_exception(dp->netdev,
							    xdp_prog, act);
				जारी;
			शेष:
				bpf_warn_invalid_xdp_action(act);
				fallthrough;
			हाल XDP_ABORTED:
				trace_xdp_exception(dp->netdev, xdp_prog, act);
				fallthrough;
			हाल XDP_DROP:
				nfp_net_rx_give_one(dp, rx_ring, rxbuf->frag,
						    rxbuf->dma_addr);
				जारी;
			पूर्ण
		पूर्ण

		अगर (likely(!meta.portid)) अणु
			netdev = dp->netdev;
		पूर्ण अन्यथा अगर (meta.portid == NFP_META_PORT_ID_CTRL) अणु
			काष्ठा nfp_net *nn = netdev_priv(dp->netdev);

			nfp_app_ctrl_rx_raw(nn->app, rxbuf->frag + pkt_off,
					    pkt_len);
			nfp_net_rx_give_one(dp, rx_ring, rxbuf->frag,
					    rxbuf->dma_addr);
			जारी;
		पूर्ण अन्यथा अणु
			काष्ठा nfp_net *nn;

			nn = netdev_priv(dp->netdev);
			netdev = nfp_app_dev_get(nn->app, meta.portid,
						 &redir_egress);
			अगर (unlikely(!netdev)) अणु
				nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf,
						शून्य);
				जारी;
			पूर्ण

			अगर (nfp_netdev_is_nfp_repr(netdev))
				nfp_repr_inc_rx_stats(netdev, pkt_len);
		पूर्ण

		skb = build_skb(rxbuf->frag, true_bufsz);
		अगर (unlikely(!skb)) अणु
			nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, शून्य);
			जारी;
		पूर्ण
		new_frag = nfp_net_napi_alloc_one(dp, &new_dma_addr);
		अगर (unlikely(!new_frag)) अणु
			nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, skb);
			जारी;
		पूर्ण

		nfp_net_dma_unmap_rx(dp, rxbuf->dma_addr);

		nfp_net_rx_give_one(dp, rx_ring, new_frag, new_dma_addr);

		skb_reserve(skb, pkt_off);
		skb_put(skb, pkt_len);

		skb->mark = meta.mark;
		skb_set_hash(skb, meta.hash, meta.hash_type);

		skb_record_rx_queue(skb, rx_ring->idx);
		skb->protocol = eth_type_trans(skb, netdev);

		nfp_net_rx_csum(dp, r_vec, rxd, &meta, skb);

#अगर_घोषित CONFIG_TLS_DEVICE
		अगर (rxd->rxd.flags & PCIE_DESC_RX_DECRYPTED) अणु
			skb->decrypted = true;
			u64_stats_update_begin(&r_vec->rx_sync);
			r_vec->hw_tls_rx++;
			u64_stats_update_end(&r_vec->rx_sync);
		पूर्ण
#पूर्ण_अगर

		अगर (rxd->rxd.flags & PCIE_DESC_RX_VLAN)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       le16_to_cpu(rxd->rxd.vlan));
		अगर (meta_len_xdp)
			skb_metadata_set(skb, meta_len_xdp);

		अगर (likely(!redir_egress)) अणु
			napi_gro_receive(&rx_ring->r_vec->napi, skb);
		पूर्ण अन्यथा अणु
			skb->dev = netdev;
			skb_reset_network_header(skb);
			__skb_push(skb, ETH_HLEN);
			dev_queue_xmit(skb);
		पूर्ण
	पूर्ण

	अगर (xdp_prog) अणु
		अगर (tx_ring->wr_ptr_add)
			nfp_net_tx_xmit_more_flush(tx_ring);
		अन्यथा अगर (unlikely(tx_ring->wr_p != tx_ring->rd_p) &&
			 !xdp_tx_cmpl)
			अगर (!nfp_net_xdp_complete(tx_ring))
				pkts_polled = budget;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस pkts_polled;
पूर्ण

/**
 * nfp_net_poll() - napi poll function
 * @napi:    NAPI काष्ठाure
 * @budget:  NAPI budget
 *
 * Return: number of packets polled.
 */
अटल पूर्णांक nfp_net_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा nfp_net_r_vector *r_vec =
		container_of(napi, काष्ठा nfp_net_r_vector, napi);
	अचिन्हित पूर्णांक pkts_polled = 0;

	अगर (r_vec->tx_ring)
		nfp_net_tx_complete(r_vec->tx_ring, budget);
	अगर (r_vec->rx_ring)
		pkts_polled = nfp_net_rx(r_vec->rx_ring, budget);

	अगर (pkts_polled < budget)
		अगर (napi_complete_करोne(napi, pkts_polled))
			nfp_net_irq_unmask(r_vec->nfp_net, r_vec->irq_entry);

	वापस pkts_polled;
पूर्ण

/* Control device data path
 */

अटल bool
nfp_ctrl_tx_one(काष्ठा nfp_net *nn, काष्ठा nfp_net_r_vector *r_vec,
		काष्ठा sk_buff *skb, bool old)
अणु
	अचिन्हित पूर्णांक real_len = skb->len, meta_len = 0;
	काष्ठा nfp_net_tx_ring *tx_ring;
	काष्ठा nfp_net_tx_buf *txbuf;
	काष्ठा nfp_net_tx_desc *txd;
	काष्ठा nfp_net_dp *dp;
	dma_addr_t dma_addr;
	पूर्णांक wr_idx;

	dp = &r_vec->nfp_net->dp;
	tx_ring = r_vec->tx_ring;

	अगर (WARN_ON_ONCE(skb_shinfo(skb)->nr_frags)) अणु
		nn_dp_warn(dp, "Driver's CTRL TX does not implement gather\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (unlikely(nfp_net_tx_full(tx_ring, 1))) अणु
		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tx_busy++;
		u64_stats_update_end(&r_vec->tx_sync);
		अगर (!old)
			__skb_queue_tail(&r_vec->queue, skb);
		अन्यथा
			__skb_queue_head(&r_vec->queue, skb);
		वापस true;
	पूर्ण

	अगर (nfp_app_ctrl_has_meta(nn->app)) अणु
		अगर (unlikely(skb_headroom(skb) < 8)) अणु
			nn_dp_warn(dp, "CTRL TX on skb without headroom\n");
			जाओ err_मुक्त;
		पूर्ण
		meta_len = 8;
		put_unaligned_be32(NFP_META_PORT_ID_CTRL, skb_push(skb, 4));
		put_unaligned_be32(NFP_NET_META_PORTID, skb_push(skb, 4));
	पूर्ण

	/* Start with the head skbuf */
	dma_addr = dma_map_single(dp->dev, skb->data, skb_headlen(skb),
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dp->dev, dma_addr))
		जाओ err_dma_warn;

	wr_idx = D_IDX(tx_ring, tx_ring->wr_p);

	/* Stash the soft descriptor of the head then initialize it */
	txbuf = &tx_ring->txbufs[wr_idx];
	txbuf->skb = skb;
	txbuf->dma_addr = dma_addr;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->real_len = real_len;

	/* Build TX descriptor */
	txd = &tx_ring->txds[wr_idx];
	txd->offset_eop = meta_len | PCIE_DESC_TX_EOP;
	txd->dma_len = cpu_to_le16(skb_headlen(skb));
	nfp_desc_set_dma_addr(txd, dma_addr);
	txd->data_len = cpu_to_le16(skb->len);

	txd->flags = 0;
	txd->mss = 0;
	txd->lso_hdrlen = 0;

	tx_ring->wr_p++;
	tx_ring->wr_ptr_add++;
	nfp_net_tx_xmit_more_flush(tx_ring);

	वापस false;

err_dma_warn:
	nn_dp_warn(dp, "Failed to DMA map TX CTRL buffer\n");
err_मुक्त:
	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_errors++;
	u64_stats_update_end(&r_vec->tx_sync);
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण

bool __nfp_ctrl_tx(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_net_r_vector *r_vec = &nn->r_vecs[0];

	वापस nfp_ctrl_tx_one(nn, r_vec, skb, false);
पूर्ण

bool nfp_ctrl_tx(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_net_r_vector *r_vec = &nn->r_vecs[0];
	bool ret;

	spin_lock_bh(&r_vec->lock);
	ret = nfp_ctrl_tx_one(nn, r_vec, skb, false);
	spin_unlock_bh(&r_vec->lock);

	वापस ret;
पूर्ण

अटल व्योम __nfp_ctrl_tx_queued(काष्ठा nfp_net_r_vector *r_vec)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&r_vec->queue)))
		अगर (nfp_ctrl_tx_one(r_vec->nfp_net, r_vec, skb, true))
			वापस;
पूर्ण

अटल bool
nfp_ctrl_meta_ok(काष्ठा nfp_net *nn, व्योम *data, अचिन्हित पूर्णांक meta_len)
अणु
	u32 meta_type, meta_tag;

	अगर (!nfp_app_ctrl_has_meta(nn->app))
		वापस !meta_len;

	अगर (meta_len != 8)
		वापस false;

	meta_type = get_unaligned_be32(data);
	meta_tag = get_unaligned_be32(data + 4);

	वापस (meta_type == NFP_NET_META_PORTID &&
		meta_tag == NFP_META_PORT_ID_CTRL);
पूर्ण

अटल bool
nfp_ctrl_rx_one(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *dp,
		काष्ठा nfp_net_r_vector *r_vec, काष्ठा nfp_net_rx_ring *rx_ring)
अणु
	अचिन्हित पूर्णांक meta_len, data_len, meta_off, pkt_len, pkt_off;
	काष्ठा nfp_net_rx_buf *rxbuf;
	काष्ठा nfp_net_rx_desc *rxd;
	dma_addr_t new_dma_addr;
	काष्ठा sk_buff *skb;
	व्योम *new_frag;
	पूर्णांक idx;

	idx = D_IDX(rx_ring, rx_ring->rd_p);

	rxd = &rx_ring->rxds[idx];
	अगर (!(rxd->rxd.meta_len_dd & PCIE_DESC_RX_DD))
		वापस false;

	/* Memory barrier to ensure that we won't करो other पढ़ोs
	 * beक्रमe the DD bit.
	 */
	dma_rmb();

	rx_ring->rd_p++;

	rxbuf =	&rx_ring->rxbufs[idx];
	meta_len = rxd->rxd.meta_len_dd & PCIE_DESC_RX_META_LEN_MASK;
	data_len = le16_to_cpu(rxd->rxd.data_len);
	pkt_len = data_len - meta_len;

	pkt_off = NFP_NET_RX_BUF_HEADROOM + dp->rx_dma_off;
	अगर (dp->rx_offset == NFP_NET_CFG_RX_OFFSET_DYNAMIC)
		pkt_off += meta_len;
	अन्यथा
		pkt_off += dp->rx_offset;
	meta_off = pkt_off - meta_len;

	/* Stats update */
	u64_stats_update_begin(&r_vec->rx_sync);
	r_vec->rx_pkts++;
	r_vec->rx_bytes += pkt_len;
	u64_stats_update_end(&r_vec->rx_sync);

	nfp_net_dma_sync_cpu_rx(dp, rxbuf->dma_addr + meta_off,	data_len);

	अगर (unlikely(!nfp_ctrl_meta_ok(nn, rxbuf->frag + meta_off, meta_len))) अणु
		nn_dp_warn(dp, "incorrect metadata for ctrl packet (%d)\n",
			   meta_len);
		nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, शून्य);
		वापस true;
	पूर्ण

	skb = build_skb(rxbuf->frag, dp->fl_bufsz);
	अगर (unlikely(!skb)) अणु
		nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, शून्य);
		वापस true;
	पूर्ण
	new_frag = nfp_net_napi_alloc_one(dp, &new_dma_addr);
	अगर (unlikely(!new_frag)) अणु
		nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, skb);
		वापस true;
	पूर्ण

	nfp_net_dma_unmap_rx(dp, rxbuf->dma_addr);

	nfp_net_rx_give_one(dp, rx_ring, new_frag, new_dma_addr);

	skb_reserve(skb, pkt_off);
	skb_put(skb, pkt_len);

	nfp_app_ctrl_rx(nn->app, skb);

	वापस true;
पूर्ण

अटल bool nfp_ctrl_rx(काष्ठा nfp_net_r_vector *r_vec)
अणु
	काष्ठा nfp_net_rx_ring *rx_ring = r_vec->rx_ring;
	काष्ठा nfp_net *nn = r_vec->nfp_net;
	काष्ठा nfp_net_dp *dp = &nn->dp;
	अचिन्हित पूर्णांक budget = 512;

	जबतक (nfp_ctrl_rx_one(nn, dp, r_vec, rx_ring) && budget--)
		जारी;

	वापस budget;
पूर्ण

अटल व्योम nfp_ctrl_poll(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा nfp_net_r_vector *r_vec = from_tasklet(r_vec, t, tasklet);

	spin_lock(&r_vec->lock);
	nfp_net_tx_complete(r_vec->tx_ring, 0);
	__nfp_ctrl_tx_queued(r_vec);
	spin_unlock(&r_vec->lock);

	अगर (nfp_ctrl_rx(r_vec)) अणु
		nfp_net_irq_unmask(r_vec->nfp_net, r_vec->irq_entry);
	पूर्ण अन्यथा अणु
		tasklet_schedule(&r_vec->tasklet);
		nn_dp_warn(&r_vec->nfp_net->dp,
			   "control message budget exceeded!\n");
	पूर्ण
पूर्ण

/* Setup and Configuration
 */

/**
 * nfp_net_vecs_init() - Assign IRQs and setup rvecs.
 * @nn:		NFP Network काष्ठाure
 */
अटल व्योम nfp_net_vecs_init(काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_net_r_vector *r_vec;
	पूर्णांक r;

	nn->lsc_handler = nfp_net_irq_lsc;
	nn->exn_handler = nfp_net_irq_exn;

	क्रम (r = 0; r < nn->max_r_vecs; r++) अणु
		काष्ठा msix_entry *entry;

		entry = &nn->irq_entries[NFP_NET_NON_Q_VECTORS + r];

		r_vec = &nn->r_vecs[r];
		r_vec->nfp_net = nn;
		r_vec->irq_entry = entry->entry;
		r_vec->irq_vector = entry->vector;

		अगर (nn->dp.netdev) अणु
			r_vec->handler = nfp_net_irq_rxtx;
		पूर्ण अन्यथा अणु
			r_vec->handler = nfp_ctrl_irq_rxtx;

			__skb_queue_head_init(&r_vec->queue);
			spin_lock_init(&r_vec->lock);
			tasklet_setup(&r_vec->tasklet, nfp_ctrl_poll);
			tasklet_disable(&r_vec->tasklet);
		पूर्ण

		cpumask_set_cpu(r, &r_vec->affinity_mask);
	पूर्ण
पूर्ण

/**
 * nfp_net_tx_ring_मुक्त() - Free resources allocated to a TX ring
 * @tx_ring:   TX ring to मुक्त
 */
अटल व्योम nfp_net_tx_ring_मुक्त(काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	काष्ठा nfp_net_r_vector *r_vec = tx_ring->r_vec;
	काष्ठा nfp_net_dp *dp = &r_vec->nfp_net->dp;

	kvमुक्त(tx_ring->txbufs);

	अगर (tx_ring->txds)
		dma_मुक्त_coherent(dp->dev, tx_ring->size,
				  tx_ring->txds, tx_ring->dma);

	tx_ring->cnt = 0;
	tx_ring->txbufs = शून्य;
	tx_ring->txds = शून्य;
	tx_ring->dma = 0;
	tx_ring->size = 0;
पूर्ण

/**
 * nfp_net_tx_ring_alloc() - Allocate resource क्रम a TX ring
 * @dp:        NFP Net data path काष्ठा
 * @tx_ring:   TX Ring काष्ठाure to allocate
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक
nfp_net_tx_ring_alloc(काष्ठा nfp_net_dp *dp, काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	काष्ठा nfp_net_r_vector *r_vec = tx_ring->r_vec;

	tx_ring->cnt = dp->txd_cnt;

	tx_ring->size = array_size(tx_ring->cnt, माप(*tx_ring->txds));
	tx_ring->txds = dma_alloc_coherent(dp->dev, tx_ring->size,
					   &tx_ring->dma,
					   GFP_KERNEL | __GFP_NOWARN);
	अगर (!tx_ring->txds) अणु
		netdev_warn(dp->netdev, "failed to allocate TX descriptor ring memory, requested descriptor count: %d, consider lowering descriptor count\n",
			    tx_ring->cnt);
		जाओ err_alloc;
	पूर्ण

	tx_ring->txbufs = kvसुस्मृति(tx_ring->cnt, माप(*tx_ring->txbufs),
				   GFP_KERNEL);
	अगर (!tx_ring->txbufs)
		जाओ err_alloc;

	अगर (!tx_ring->is_xdp && dp->netdev)
		netअगर_set_xps_queue(dp->netdev, &r_vec->affinity_mask,
				    tx_ring->idx);

	वापस 0;

err_alloc:
	nfp_net_tx_ring_मुक्त(tx_ring);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
nfp_net_tx_ring_bufs_मुक्त(काष्ठा nfp_net_dp *dp,
			  काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!tx_ring->is_xdp)
		वापस;

	क्रम (i = 0; i < tx_ring->cnt; i++) अणु
		अगर (!tx_ring->txbufs[i].frag)
			वापस;

		nfp_net_dma_unmap_rx(dp, tx_ring->txbufs[i].dma_addr);
		__मुक्त_page(virt_to_page(tx_ring->txbufs[i].frag));
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_net_tx_ring_bufs_alloc(काष्ठा nfp_net_dp *dp,
			   काष्ठा nfp_net_tx_ring *tx_ring)
अणु
	काष्ठा nfp_net_tx_buf *txbufs = tx_ring->txbufs;
	अचिन्हित पूर्णांक i;

	अगर (!tx_ring->is_xdp)
		वापस 0;

	क्रम (i = 0; i < tx_ring->cnt; i++) अणु
		txbufs[i].frag = nfp_net_rx_alloc_one(dp, &txbufs[i].dma_addr);
		अगर (!txbufs[i].frag) अणु
			nfp_net_tx_ring_bufs_मुक्त(dp, tx_ring);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_net_tx_rings_prepare(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *dp)
अणु
	अचिन्हित पूर्णांक r;

	dp->tx_rings = kसुस्मृति(dp->num_tx_rings, माप(*dp->tx_rings),
			       GFP_KERNEL);
	अगर (!dp->tx_rings)
		वापस -ENOMEM;

	क्रम (r = 0; r < dp->num_tx_rings; r++) अणु
		पूर्णांक bias = 0;

		अगर (r >= dp->num_stack_tx_rings)
			bias = dp->num_stack_tx_rings;

		nfp_net_tx_ring_init(&dp->tx_rings[r], &nn->r_vecs[r - bias],
				     r, bias);

		अगर (nfp_net_tx_ring_alloc(dp, &dp->tx_rings[r]))
			जाओ err_मुक्त_prev;

		अगर (nfp_net_tx_ring_bufs_alloc(dp, &dp->tx_rings[r]))
			जाओ err_मुक्त_ring;
	पूर्ण

	वापस 0;

err_मुक्त_prev:
	जबतक (r--) अणु
		nfp_net_tx_ring_bufs_मुक्त(dp, &dp->tx_rings[r]);
err_मुक्त_ring:
		nfp_net_tx_ring_मुक्त(&dp->tx_rings[r]);
	पूर्ण
	kमुक्त(dp->tx_rings);
	वापस -ENOMEM;
पूर्ण

अटल व्योम nfp_net_tx_rings_मुक्त(काष्ठा nfp_net_dp *dp)
अणु
	अचिन्हित पूर्णांक r;

	क्रम (r = 0; r < dp->num_tx_rings; r++) अणु
		nfp_net_tx_ring_bufs_मुक्त(dp, &dp->tx_rings[r]);
		nfp_net_tx_ring_मुक्त(&dp->tx_rings[r]);
	पूर्ण

	kमुक्त(dp->tx_rings);
पूर्ण

/**
 * nfp_net_rx_ring_मुक्त() - Free resources allocated to a RX ring
 * @rx_ring:  RX ring to मुक्त
 */
अटल व्योम nfp_net_rx_ring_मुक्त(काष्ठा nfp_net_rx_ring *rx_ring)
अणु
	काष्ठा nfp_net_r_vector *r_vec = rx_ring->r_vec;
	काष्ठा nfp_net_dp *dp = &r_vec->nfp_net->dp;

	अगर (dp->netdev)
		xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	kvमुक्त(rx_ring->rxbufs);

	अगर (rx_ring->rxds)
		dma_मुक्त_coherent(dp->dev, rx_ring->size,
				  rx_ring->rxds, rx_ring->dma);

	rx_ring->cnt = 0;
	rx_ring->rxbufs = शून्य;
	rx_ring->rxds = शून्य;
	rx_ring->dma = 0;
	rx_ring->size = 0;
पूर्ण

/**
 * nfp_net_rx_ring_alloc() - Allocate resource क्रम a RX ring
 * @dp:	      NFP Net data path काष्ठा
 * @rx_ring:  RX ring to allocate
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक
nfp_net_rx_ring_alloc(काष्ठा nfp_net_dp *dp, काष्ठा nfp_net_rx_ring *rx_ring)
अणु
	पूर्णांक err;

	अगर (dp->netdev) अणु
		err = xdp_rxq_info_reg(&rx_ring->xdp_rxq, dp->netdev,
				       rx_ring->idx, rx_ring->r_vec->napi.napi_id);
		अगर (err < 0)
			वापस err;
	पूर्ण

	rx_ring->cnt = dp->rxd_cnt;
	rx_ring->size = array_size(rx_ring->cnt, माप(*rx_ring->rxds));
	rx_ring->rxds = dma_alloc_coherent(dp->dev, rx_ring->size,
					   &rx_ring->dma,
					   GFP_KERNEL | __GFP_NOWARN);
	अगर (!rx_ring->rxds) अणु
		netdev_warn(dp->netdev, "failed to allocate RX descriptor ring memory, requested descriptor count: %d, consider lowering descriptor count\n",
			    rx_ring->cnt);
		जाओ err_alloc;
	पूर्ण

	rx_ring->rxbufs = kvसुस्मृति(rx_ring->cnt, माप(*rx_ring->rxbufs),
				   GFP_KERNEL);
	अगर (!rx_ring->rxbufs)
		जाओ err_alloc;

	वापस 0;

err_alloc:
	nfp_net_rx_ring_मुक्त(rx_ring);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक nfp_net_rx_rings_prepare(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *dp)
अणु
	अचिन्हित पूर्णांक r;

	dp->rx_rings = kसुस्मृति(dp->num_rx_rings, माप(*dp->rx_rings),
			       GFP_KERNEL);
	अगर (!dp->rx_rings)
		वापस -ENOMEM;

	क्रम (r = 0; r < dp->num_rx_rings; r++) अणु
		nfp_net_rx_ring_init(&dp->rx_rings[r], &nn->r_vecs[r], r);

		अगर (nfp_net_rx_ring_alloc(dp, &dp->rx_rings[r]))
			जाओ err_मुक्त_prev;

		अगर (nfp_net_rx_ring_bufs_alloc(dp, &dp->rx_rings[r]))
			जाओ err_मुक्त_ring;
	पूर्ण

	वापस 0;

err_मुक्त_prev:
	जबतक (r--) अणु
		nfp_net_rx_ring_bufs_मुक्त(dp, &dp->rx_rings[r]);
err_मुक्त_ring:
		nfp_net_rx_ring_मुक्त(&dp->rx_rings[r]);
	पूर्ण
	kमुक्त(dp->rx_rings);
	वापस -ENOMEM;
पूर्ण

अटल व्योम nfp_net_rx_rings_मुक्त(काष्ठा nfp_net_dp *dp)
अणु
	अचिन्हित पूर्णांक r;

	क्रम (r = 0; r < dp->num_rx_rings; r++) अणु
		nfp_net_rx_ring_bufs_मुक्त(dp, &dp->rx_rings[r]);
		nfp_net_rx_ring_मुक्त(&dp->rx_rings[r]);
	पूर्ण

	kमुक्त(dp->rx_rings);
पूर्ण

अटल व्योम
nfp_net_vector_assign_rings(काष्ठा nfp_net_dp *dp,
			    काष्ठा nfp_net_r_vector *r_vec, पूर्णांक idx)
अणु
	r_vec->rx_ring = idx < dp->num_rx_rings ? &dp->rx_rings[idx] : शून्य;
	r_vec->tx_ring =
		idx < dp->num_stack_tx_rings ? &dp->tx_rings[idx] : शून्य;

	r_vec->xdp_ring = idx < dp->num_tx_rings - dp->num_stack_tx_rings ?
		&dp->tx_rings[dp->num_stack_tx_rings + idx] : शून्य;
पूर्ण

अटल पूर्णांक
nfp_net_prepare_vector(काष्ठा nfp_net *nn, काष्ठा nfp_net_r_vector *r_vec,
		       पूर्णांक idx)
अणु
	पूर्णांक err;

	/* Setup NAPI */
	अगर (nn->dp.netdev)
		netअगर_napi_add(nn->dp.netdev, &r_vec->napi,
			       nfp_net_poll, NAPI_POLL_WEIGHT);
	अन्यथा
		tasklet_enable(&r_vec->tasklet);

	snम_लिखो(r_vec->name, माप(r_vec->name),
		 "%s-rxtx-%d", nfp_net_name(nn), idx);
	err = request_irq(r_vec->irq_vector, r_vec->handler, 0, r_vec->name,
			  r_vec);
	अगर (err) अणु
		अगर (nn->dp.netdev)
			netअगर_napi_del(&r_vec->napi);
		अन्यथा
			tasklet_disable(&r_vec->tasklet);

		nn_err(nn, "Error requesting IRQ %d\n", r_vec->irq_vector);
		वापस err;
	पूर्ण
	disable_irq(r_vec->irq_vector);

	irq_set_affinity_hपूर्णांक(r_vec->irq_vector, &r_vec->affinity_mask);

	nn_dbg(nn, "RV%02d: irq=%03d/%03d\n", idx, r_vec->irq_vector,
	       r_vec->irq_entry);

	वापस 0;
पूर्ण

अटल व्योम
nfp_net_cleanup_vector(काष्ठा nfp_net *nn, काष्ठा nfp_net_r_vector *r_vec)
अणु
	irq_set_affinity_hपूर्णांक(r_vec->irq_vector, शून्य);
	अगर (nn->dp.netdev)
		netअगर_napi_del(&r_vec->napi);
	अन्यथा
		tasklet_disable(&r_vec->tasklet);

	मुक्त_irq(r_vec->irq_vector, r_vec);
पूर्ण

/**
 * nfp_net_rss_ग_लिखो_itbl() - Write RSS indirection table to device
 * @nn:      NFP Net device to reconfigure
 */
व्योम nfp_net_rss_ग_लिखो_itbl(काष्ठा nfp_net *nn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NFP_NET_CFG_RSS_ITBL_SZ; i += 4)
		nn_ग_लिखोl(nn, NFP_NET_CFG_RSS_ITBL + i,
			  get_unaligned_le32(nn->rss_itbl + i));
पूर्ण

/**
 * nfp_net_rss_ग_लिखो_key() - Write RSS hash key to device
 * @nn:      NFP Net device to reconfigure
 */
व्योम nfp_net_rss_ग_लिखो_key(काष्ठा nfp_net *nn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nfp_net_rss_key_sz(nn); i += 4)
		nn_ग_लिखोl(nn, NFP_NET_CFG_RSS_KEY + i,
			  get_unaligned_le32(nn->rss_key + i));
पूर्ण

/**
 * nfp_net_coalesce_ग_लिखो_cfg() - Write irq coalescence configuration to HW
 * @nn:      NFP Net device to reconfigure
 */
व्योम nfp_net_coalesce_ग_लिखो_cfg(काष्ठा nfp_net *nn)
अणु
	u8 i;
	u32 factor;
	u32 value;

	/* Compute factor used to convert coalesce '_usecs' parameters to
	 * ME बारtamp ticks.  There are 16 ME घड़ी cycles क्रम each बारtamp
	 * count.
	 */
	factor = nn->tlv_caps.me_freq_mhz / 16;

	/* copy RX पूर्णांकerrupt coalesce parameters */
	value = (nn->rx_coalesce_max_frames << 16) |
		(factor * nn->rx_coalesce_usecs);
	क्रम (i = 0; i < nn->dp.num_rx_rings; i++)
		nn_ग_लिखोl(nn, NFP_NET_CFG_RXR_IRQ_MOD(i), value);

	/* copy TX पूर्णांकerrupt coalesce parameters */
	value = (nn->tx_coalesce_max_frames << 16) |
		(factor * nn->tx_coalesce_usecs);
	क्रम (i = 0; i < nn->dp.num_tx_rings; i++)
		nn_ग_लिखोl(nn, NFP_NET_CFG_TXR_IRQ_MOD(i), value);
पूर्ण

/**
 * nfp_net_ग_लिखो_mac_addr() - Write mac address to the device control BAR
 * @nn:      NFP Net device to reconfigure
 * @addr:    MAC address to ग_लिखो
 *
 * Writes the MAC address from the netdev to the device control BAR.  Does not
 * perक्रमm the required reconfig.  We करो a bit of byte swapping dance because
 * firmware is LE.
 */
अटल व्योम nfp_net_ग_लिखो_mac_addr(काष्ठा nfp_net *nn, स्थिर u8 *addr)
अणु
	nn_ग_लिखोl(nn, NFP_NET_CFG_MACADDR + 0, get_unaligned_be32(addr));
	nn_ग_लिखोw(nn, NFP_NET_CFG_MACADDR + 6, get_unaligned_be16(addr + 4));
पूर्ण

अटल व्योम nfp_net_vec_clear_ring_data(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक idx)
अणु
	nn_ग_लिखोq(nn, NFP_NET_CFG_RXR_ADDR(idx), 0);
	nn_ग_लिखोb(nn, NFP_NET_CFG_RXR_SZ(idx), 0);
	nn_ग_लिखोb(nn, NFP_NET_CFG_RXR_VEC(idx), 0);

	nn_ग_लिखोq(nn, NFP_NET_CFG_TXR_ADDR(idx), 0);
	nn_ग_लिखोb(nn, NFP_NET_CFG_TXR_SZ(idx), 0);
	nn_ग_लिखोb(nn, NFP_NET_CFG_TXR_VEC(idx), 0);
पूर्ण

/**
 * nfp_net_clear_config_and_disable() - Clear control BAR and disable NFP
 * @nn:      NFP Net device to reconfigure
 *
 * Warning: must be fully idempotent.
 */
अटल व्योम nfp_net_clear_config_and_disable(काष्ठा nfp_net *nn)
अणु
	u32 new_ctrl, update;
	अचिन्हित पूर्णांक r;
	पूर्णांक err;

	new_ctrl = nn->dp.ctrl;
	new_ctrl &= ~NFP_NET_CFG_CTRL_ENABLE;
	update = NFP_NET_CFG_UPDATE_GEN;
	update |= NFP_NET_CFG_UPDATE_MSIX;
	update |= NFP_NET_CFG_UPDATE_RING;

	अगर (nn->cap & NFP_NET_CFG_CTRL_RINGCFG)
		new_ctrl &= ~NFP_NET_CFG_CTRL_RINGCFG;

	nn_ग_लिखोq(nn, NFP_NET_CFG_TXRS_ENABLE, 0);
	nn_ग_लिखोq(nn, NFP_NET_CFG_RXRS_ENABLE, 0);

	nn_ग_लिखोl(nn, NFP_NET_CFG_CTRL, new_ctrl);
	err = nfp_net_reconfig(nn, update);
	अगर (err)
		nn_err(nn, "Could not disable device: %d\n", err);

	क्रम (r = 0; r < nn->dp.num_rx_rings; r++)
		nfp_net_rx_ring_reset(&nn->dp.rx_rings[r]);
	क्रम (r = 0; r < nn->dp.num_tx_rings; r++)
		nfp_net_tx_ring_reset(&nn->dp, &nn->dp.tx_rings[r]);
	क्रम (r = 0; r < nn->dp.num_r_vecs; r++)
		nfp_net_vec_clear_ring_data(nn, r);

	nn->dp.ctrl = new_ctrl;
पूर्ण

अटल व्योम
nfp_net_rx_ring_hw_cfg_ग_लिखो(काष्ठा nfp_net *nn,
			     काष्ठा nfp_net_rx_ring *rx_ring, अचिन्हित पूर्णांक idx)
अणु
	/* Write the DMA address, size and MSI-X info to the device */
	nn_ग_लिखोq(nn, NFP_NET_CFG_RXR_ADDR(idx), rx_ring->dma);
	nn_ग_लिखोb(nn, NFP_NET_CFG_RXR_SZ(idx), ilog2(rx_ring->cnt));
	nn_ग_लिखोb(nn, NFP_NET_CFG_RXR_VEC(idx), rx_ring->r_vec->irq_entry);
पूर्ण

अटल व्योम
nfp_net_tx_ring_hw_cfg_ग_लिखो(काष्ठा nfp_net *nn,
			     काष्ठा nfp_net_tx_ring *tx_ring, अचिन्हित पूर्णांक idx)
अणु
	nn_ग_लिखोq(nn, NFP_NET_CFG_TXR_ADDR(idx), tx_ring->dma);
	nn_ग_लिखोb(nn, NFP_NET_CFG_TXR_SZ(idx), ilog2(tx_ring->cnt));
	nn_ग_लिखोb(nn, NFP_NET_CFG_TXR_VEC(idx), tx_ring->r_vec->irq_entry);
पूर्ण

/**
 * nfp_net_set_config_and_enable() - Write control BAR and enable NFP
 * @nn:      NFP Net device to reconfigure
 */
अटल पूर्णांक nfp_net_set_config_and_enable(काष्ठा nfp_net *nn)
अणु
	u32 bufsz, new_ctrl, update = 0;
	अचिन्हित पूर्णांक r;
	पूर्णांक err;

	new_ctrl = nn->dp.ctrl;

	अगर (nn->dp.ctrl & NFP_NET_CFG_CTRL_RSS_ANY) अणु
		nfp_net_rss_ग_लिखो_key(nn);
		nfp_net_rss_ग_लिखो_itbl(nn);
		nn_ग_लिखोl(nn, NFP_NET_CFG_RSS_CTRL, nn->rss_cfg);
		update |= NFP_NET_CFG_UPDATE_RSS;
	पूर्ण

	अगर (nn->dp.ctrl & NFP_NET_CFG_CTRL_IRQMOD) अणु
		nfp_net_coalesce_ग_लिखो_cfg(nn);
		update |= NFP_NET_CFG_UPDATE_IRQMOD;
	पूर्ण

	क्रम (r = 0; r < nn->dp.num_tx_rings; r++)
		nfp_net_tx_ring_hw_cfg_ग_लिखो(nn, &nn->dp.tx_rings[r], r);
	क्रम (r = 0; r < nn->dp.num_rx_rings; r++)
		nfp_net_rx_ring_hw_cfg_ग_लिखो(nn, &nn->dp.rx_rings[r], r);

	nn_ग_लिखोq(nn, NFP_NET_CFG_TXRS_ENABLE, nn->dp.num_tx_rings == 64 ?
		  0xffffffffffffffffULL : ((u64)1 << nn->dp.num_tx_rings) - 1);

	nn_ग_लिखोq(nn, NFP_NET_CFG_RXRS_ENABLE, nn->dp.num_rx_rings == 64 ?
		  0xffffffffffffffffULL : ((u64)1 << nn->dp.num_rx_rings) - 1);

	अगर (nn->dp.netdev)
		nfp_net_ग_लिखो_mac_addr(nn, nn->dp.netdev->dev_addr);

	nn_ग_लिखोl(nn, NFP_NET_CFG_MTU, nn->dp.mtu);

	bufsz = nn->dp.fl_bufsz - nn->dp.rx_dma_off - NFP_NET_RX_BUF_NON_DATA;
	nn_ग_लिखोl(nn, NFP_NET_CFG_FLBUFSZ, bufsz);

	/* Enable device */
	new_ctrl |= NFP_NET_CFG_CTRL_ENABLE;
	update |= NFP_NET_CFG_UPDATE_GEN;
	update |= NFP_NET_CFG_UPDATE_MSIX;
	update |= NFP_NET_CFG_UPDATE_RING;
	अगर (nn->cap & NFP_NET_CFG_CTRL_RINGCFG)
		new_ctrl |= NFP_NET_CFG_CTRL_RINGCFG;

	nn_ग_लिखोl(nn, NFP_NET_CFG_CTRL, new_ctrl);
	err = nfp_net_reconfig(nn, update);
	अगर (err) अणु
		nfp_net_clear_config_and_disable(nn);
		वापस err;
	पूर्ण

	nn->dp.ctrl = new_ctrl;

	क्रम (r = 0; r < nn->dp.num_rx_rings; r++)
		nfp_net_rx_ring_fill_मुक्तlist(&nn->dp, &nn->dp.rx_rings[r]);

	वापस 0;
पूर्ण

/**
 * nfp_net_बंद_stack() - Quiesce the stack (part of बंद)
 * @nn:	     NFP Net device to reconfigure
 */
अटल व्योम nfp_net_बंद_stack(काष्ठा nfp_net *nn)
अणु
	अचिन्हित पूर्णांक r;

	disable_irq(nn->irq_entries[NFP_NET_IRQ_LSC_IDX].vector);
	netअगर_carrier_off(nn->dp.netdev);
	nn->link_up = false;

	क्रम (r = 0; r < nn->dp.num_r_vecs; r++) अणु
		disable_irq(nn->r_vecs[r].irq_vector);
		napi_disable(&nn->r_vecs[r].napi);
	पूर्ण

	netअगर_tx_disable(nn->dp.netdev);
पूर्ण

/**
 * nfp_net_बंद_मुक्त_all() - Free all runसमय resources
 * @nn:      NFP Net device to reconfigure
 */
अटल व्योम nfp_net_बंद_मुक्त_all(काष्ठा nfp_net *nn)
अणु
	अचिन्हित पूर्णांक r;

	nfp_net_tx_rings_मुक्त(&nn->dp);
	nfp_net_rx_rings_मुक्त(&nn->dp);

	क्रम (r = 0; r < nn->dp.num_r_vecs; r++)
		nfp_net_cleanup_vector(nn, &nn->r_vecs[r]);

	nfp_net_aux_irq_मुक्त(nn, NFP_NET_CFG_LSC, NFP_NET_IRQ_LSC_IDX);
	nfp_net_aux_irq_मुक्त(nn, NFP_NET_CFG_EXN, NFP_NET_IRQ_EXN_IDX);
पूर्ण

/**
 * nfp_net_netdev_बंद() - Called when the device is करोwned
 * @netdev:      netdev काष्ठाure
 */
अटल पूर्णांक nfp_net_netdev_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	/* Step 1: Disable RX and TX rings from the Linux kernel perspective
	 */
	nfp_net_बंद_stack(nn);

	/* Step 2: Tell NFP
	 */
	nfp_net_clear_config_and_disable(nn);
	nfp_port_configure(netdev, false);

	/* Step 3: Free resources
	 */
	nfp_net_बंद_मुक्त_all(nn);

	nn_dbg(nn, "%s down", netdev->name);
	वापस 0;
पूर्ण

व्योम nfp_ctrl_बंद(काष्ठा nfp_net *nn)
अणु
	पूर्णांक r;

	rtnl_lock();

	क्रम (r = 0; r < nn->dp.num_r_vecs; r++) अणु
		disable_irq(nn->r_vecs[r].irq_vector);
		tasklet_disable(&nn->r_vecs[r].tasklet);
	पूर्ण

	nfp_net_clear_config_and_disable(nn);

	nfp_net_बंद_मुक्त_all(nn);

	rtnl_unlock();
पूर्ण

/**
 * nfp_net_खोलो_stack() - Start the device from stack's perspective
 * @nn:      NFP Net device to reconfigure
 */
अटल व्योम nfp_net_खोलो_stack(काष्ठा nfp_net *nn)
अणु
	अचिन्हित पूर्णांक r;

	क्रम (r = 0; r < nn->dp.num_r_vecs; r++) अणु
		napi_enable(&nn->r_vecs[r].napi);
		enable_irq(nn->r_vecs[r].irq_vector);
	पूर्ण

	netअगर_tx_wake_all_queues(nn->dp.netdev);

	enable_irq(nn->irq_entries[NFP_NET_IRQ_LSC_IDX].vector);
	nfp_net_पढ़ो_link_status(nn);
पूर्ण

अटल पूर्णांक nfp_net_खोलो_alloc_all(काष्ठा nfp_net *nn)
अणु
	पूर्णांक err, r;

	err = nfp_net_aux_irq_request(nn, NFP_NET_CFG_EXN, "%s-exn",
				      nn->exn_name, माप(nn->exn_name),
				      NFP_NET_IRQ_EXN_IDX, nn->exn_handler);
	अगर (err)
		वापस err;
	err = nfp_net_aux_irq_request(nn, NFP_NET_CFG_LSC, "%s-lsc",
				      nn->lsc_name, माप(nn->lsc_name),
				      NFP_NET_IRQ_LSC_IDX, nn->lsc_handler);
	अगर (err)
		जाओ err_मुक्त_exn;
	disable_irq(nn->irq_entries[NFP_NET_IRQ_LSC_IDX].vector);

	क्रम (r = 0; r < nn->dp.num_r_vecs; r++) अणु
		err = nfp_net_prepare_vector(nn, &nn->r_vecs[r], r);
		अगर (err)
			जाओ err_cleanup_vec_p;
	पूर्ण

	err = nfp_net_rx_rings_prepare(nn, &nn->dp);
	अगर (err)
		जाओ err_cleanup_vec;

	err = nfp_net_tx_rings_prepare(nn, &nn->dp);
	अगर (err)
		जाओ err_मुक्त_rx_rings;

	क्रम (r = 0; r < nn->max_r_vecs; r++)
		nfp_net_vector_assign_rings(&nn->dp, &nn->r_vecs[r], r);

	वापस 0;

err_मुक्त_rx_rings:
	nfp_net_rx_rings_मुक्त(&nn->dp);
err_cleanup_vec:
	r = nn->dp.num_r_vecs;
err_cleanup_vec_p:
	जबतक (r--)
		nfp_net_cleanup_vector(nn, &nn->r_vecs[r]);
	nfp_net_aux_irq_मुक्त(nn, NFP_NET_CFG_LSC, NFP_NET_IRQ_LSC_IDX);
err_मुक्त_exn:
	nfp_net_aux_irq_मुक्त(nn, NFP_NET_CFG_EXN, NFP_NET_IRQ_EXN_IDX);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_net_netdev_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक err;

	/* Step 1: Allocate resources क्रम rings and the like
	 * - Request पूर्णांकerrupts
	 * - Allocate RX and TX ring resources
	 * - Setup initial RSS table
	 */
	err = nfp_net_खोलो_alloc_all(nn);
	अगर (err)
		वापस err;

	err = netअगर_set_real_num_tx_queues(netdev, nn->dp.num_stack_tx_rings);
	अगर (err)
		जाओ err_मुक्त_all;

	err = netअगर_set_real_num_rx_queues(netdev, nn->dp.num_rx_rings);
	अगर (err)
		जाओ err_मुक्त_all;

	/* Step 2: Configure the NFP
	 * - Ifup the physical पूर्णांकerface अगर it exists
	 * - Enable rings from 0 to tx_rings/rx_rings - 1.
	 * - Write MAC address (in हाल it changed)
	 * - Set the MTU
	 * - Set the Freelist buffer size
	 * - Enable the FW
	 */
	err = nfp_port_configure(netdev, true);
	अगर (err)
		जाओ err_मुक्त_all;

	err = nfp_net_set_config_and_enable(nn);
	अगर (err)
		जाओ err_port_disable;

	/* Step 3: Enable क्रम kernel
	 * - put some मुक्तlist descriptors on each RX ring
	 * - enable NAPI on each ring
	 * - enable all TX queues
	 * - set link state
	 */
	nfp_net_खोलो_stack(nn);

	वापस 0;

err_port_disable:
	nfp_port_configure(netdev, false);
err_मुक्त_all:
	nfp_net_बंद_मुक्त_all(nn);
	वापस err;
पूर्ण

पूर्णांक nfp_ctrl_खोलो(काष्ठा nfp_net *nn)
अणु
	पूर्णांक err, r;

	/* ring dumping depends on vNICs being खोलोed/बंदd under rtnl */
	rtnl_lock();

	err = nfp_net_खोलो_alloc_all(nn);
	अगर (err)
		जाओ err_unlock;

	err = nfp_net_set_config_and_enable(nn);
	अगर (err)
		जाओ err_मुक्त_all;

	क्रम (r = 0; r < nn->dp.num_r_vecs; r++)
		enable_irq(nn->r_vecs[r].irq_vector);

	rtnl_unlock();

	वापस 0;

err_मुक्त_all:
	nfp_net_बंद_मुक्त_all(nn);
err_unlock:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल व्योम nfp_net_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	u32 new_ctrl;

	new_ctrl = nn->dp.ctrl;

	अगर (!netdev_mc_empty(netdev) || netdev->flags & IFF_ALLMULTI)
		new_ctrl |= nn->cap & NFP_NET_CFG_CTRL_L2MC;
	अन्यथा
		new_ctrl &= ~NFP_NET_CFG_CTRL_L2MC;

	अगर (netdev->flags & IFF_PROMISC) अणु
		अगर (nn->cap & NFP_NET_CFG_CTRL_PROMISC)
			new_ctrl |= NFP_NET_CFG_CTRL_PROMISC;
		अन्यथा
			nn_warn(nn, "FW does not support promiscuous mode\n");
	पूर्ण अन्यथा अणु
		new_ctrl &= ~NFP_NET_CFG_CTRL_PROMISC;
	पूर्ण

	अगर (new_ctrl == nn->dp.ctrl)
		वापस;

	nn_ग_लिखोl(nn, NFP_NET_CFG_CTRL, new_ctrl);
	nfp_net_reconfig_post(nn, NFP_NET_CFG_UPDATE_GEN);

	nn->dp.ctrl = new_ctrl;
पूर्ण

अटल व्योम nfp_net_rss_init_itbl(काष्ठा nfp_net *nn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(nn->rss_itbl); i++)
		nn->rss_itbl[i] =
			ethtool_rxfh_indir_शेष(i, nn->dp.num_rx_rings);
पूर्ण

अटल व्योम nfp_net_dp_swap(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *dp)
अणु
	काष्ठा nfp_net_dp new_dp = *dp;

	*dp = nn->dp;
	nn->dp = new_dp;

	nn->dp.netdev->mtu = new_dp.mtu;

	अगर (!netअगर_is_rxfh_configured(nn->dp.netdev))
		nfp_net_rss_init_itbl(nn);
पूर्ण

अटल पूर्णांक nfp_net_dp_swap_enable(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *dp)
अणु
	अचिन्हित पूर्णांक r;
	पूर्णांक err;

	nfp_net_dp_swap(nn, dp);

	क्रम (r = 0; r <	nn->max_r_vecs; r++)
		nfp_net_vector_assign_rings(&nn->dp, &nn->r_vecs[r], r);

	err = netअगर_set_real_num_rx_queues(nn->dp.netdev, nn->dp.num_rx_rings);
	अगर (err)
		वापस err;

	अगर (nn->dp.netdev->real_num_tx_queues != nn->dp.num_stack_tx_rings) अणु
		err = netअगर_set_real_num_tx_queues(nn->dp.netdev,
						   nn->dp.num_stack_tx_rings);
		अगर (err)
			वापस err;
	पूर्ण

	वापस nfp_net_set_config_and_enable(nn);
पूर्ण

काष्ठा nfp_net_dp *nfp_net_clone_dp(काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_net_dp *new;

	new = kदो_स्मृति(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	*new = nn->dp;

	/* Clear things which need to be recomputed */
	new->fl_bufsz = 0;
	new->tx_rings = शून्य;
	new->rx_rings = शून्य;
	new->num_r_vecs = 0;
	new->num_stack_tx_rings = 0;

	वापस new;
पूर्ण

अटल पूर्णांक
nfp_net_check_config(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *dp,
		     काष्ठा netlink_ext_ack *extack)
अणु
	/* XDP-enabled tests */
	अगर (!dp->xdp_prog)
		वापस 0;
	अगर (dp->fl_bufsz > PAGE_SIZE) अणु
		NL_SET_ERR_MSG_MOD(extack, "MTU too large w/ XDP enabled");
		वापस -EINVAL;
	पूर्ण
	अगर (dp->num_tx_rings > nn->max_tx_rings) अणु
		NL_SET_ERR_MSG_MOD(extack, "Insufficient number of TX rings w/ XDP enabled");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nfp_net_ring_reconfig(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *dp,
			  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक r, err;

	dp->fl_bufsz = nfp_net_calc_fl_bufsz(dp);

	dp->num_stack_tx_rings = dp->num_tx_rings;
	अगर (dp->xdp_prog)
		dp->num_stack_tx_rings -= dp->num_rx_rings;

	dp->num_r_vecs = max(dp->num_rx_rings, dp->num_stack_tx_rings);

	err = nfp_net_check_config(nn, dp, extack);
	अगर (err)
		जाओ निकास_मुक्त_dp;

	अगर (!netअगर_running(dp->netdev)) अणु
		nfp_net_dp_swap(nn, dp);
		err = 0;
		जाओ निकास_मुक्त_dp;
	पूर्ण

	/* Prepare new rings */
	क्रम (r = nn->dp.num_r_vecs; r < dp->num_r_vecs; r++) अणु
		err = nfp_net_prepare_vector(nn, &nn->r_vecs[r], r);
		अगर (err) अणु
			dp->num_r_vecs = r;
			जाओ err_cleanup_vecs;
		पूर्ण
	पूर्ण

	err = nfp_net_rx_rings_prepare(nn, dp);
	अगर (err)
		जाओ err_cleanup_vecs;

	err = nfp_net_tx_rings_prepare(nn, dp);
	अगर (err)
		जाओ err_मुक्त_rx;

	/* Stop device, swap in new rings, try to start the firmware */
	nfp_net_बंद_stack(nn);
	nfp_net_clear_config_and_disable(nn);

	err = nfp_net_dp_swap_enable(nn, dp);
	अगर (err) अणु
		पूर्णांक err2;

		nfp_net_clear_config_and_disable(nn);

		/* Try with old configuration and old rings */
		err2 = nfp_net_dp_swap_enable(nn, dp);
		अगर (err2)
			nn_err(nn, "Can't restore ring config - FW communication failed (%d,%d)\n",
			       err, err2);
	पूर्ण
	क्रम (r = dp->num_r_vecs - 1; r >= nn->dp.num_r_vecs; r--)
		nfp_net_cleanup_vector(nn, &nn->r_vecs[r]);

	nfp_net_rx_rings_मुक्त(dp);
	nfp_net_tx_rings_मुक्त(dp);

	nfp_net_खोलो_stack(nn);
निकास_मुक्त_dp:
	kमुक्त(dp);

	वापस err;

err_मुक्त_rx:
	nfp_net_rx_rings_मुक्त(dp);
err_cleanup_vecs:
	क्रम (r = dp->num_r_vecs - 1; r >= nn->dp.num_r_vecs; r--)
		nfp_net_cleanup_vector(nn, &nn->r_vecs[r]);
	kमुक्त(dp);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_net_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	काष्ठा nfp_net_dp *dp;
	पूर्णांक err;

	err = nfp_app_check_mtu(nn->app, netdev, new_mtu);
	अगर (err)
		वापस err;

	dp = nfp_net_clone_dp(nn);
	अगर (!dp)
		वापस -ENOMEM;

	dp->mtu = new_mtu;

	वापस nfp_net_ring_reconfig(nn, dp, शून्य);
पूर्ण

अटल पूर्णांक
nfp_net_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	स्थिर u32 cmd = NFP_NET_CFG_MBOX_CMD_CTAG_FILTER_ADD;
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक err;

	/* Priority tagged packets with vlan id 0 are processed by the
	 * NFP as untagged packets
	 */
	अगर (!vid)
		वापस 0;

	err = nfp_net_mbox_lock(nn, NFP_NET_CFG_VLAN_FILTER_SZ);
	अगर (err)
		वापस err;

	nn_ग_लिखोw(nn, nn->tlv_caps.mbox_off + NFP_NET_CFG_VLAN_FILTER_VID, vid);
	nn_ग_लिखोw(nn, nn->tlv_caps.mbox_off + NFP_NET_CFG_VLAN_FILTER_PROTO,
		  ETH_P_8021Q);

	वापस nfp_net_mbox_reconfig_and_unlock(nn, cmd);
पूर्ण

अटल पूर्णांक
nfp_net_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	स्थिर u32 cmd = NFP_NET_CFG_MBOX_CMD_CTAG_FILTER_KILL;
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक err;

	/* Priority tagged packets with vlan id 0 are processed by the
	 * NFP as untagged packets
	 */
	अगर (!vid)
		वापस 0;

	err = nfp_net_mbox_lock(nn, NFP_NET_CFG_VLAN_FILTER_SZ);
	अगर (err)
		वापस err;

	nn_ग_लिखोw(nn, nn->tlv_caps.mbox_off + NFP_NET_CFG_VLAN_FILTER_VID, vid);
	nn_ग_लिखोw(nn, nn->tlv_caps.mbox_off + NFP_NET_CFG_VLAN_FILTER_PROTO,
		  ETH_P_8021Q);

	वापस nfp_net_mbox_reconfig_and_unlock(nn, cmd);
पूर्ण

अटल व्योम nfp_net_stat64(काष्ठा net_device *netdev,
			   काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक r;

	/* Collect software stats */
	क्रम (r = 0; r < nn->max_r_vecs; r++) अणु
		काष्ठा nfp_net_r_vector *r_vec = &nn->r_vecs[r];
		u64 data[3];
		अचिन्हित पूर्णांक start;

		करो अणु
			start = u64_stats_fetch_begin(&r_vec->rx_sync);
			data[0] = r_vec->rx_pkts;
			data[1] = r_vec->rx_bytes;
			data[2] = r_vec->rx_drops;
		पूर्ण जबतक (u64_stats_fetch_retry(&r_vec->rx_sync, start));
		stats->rx_packets += data[0];
		stats->rx_bytes += data[1];
		stats->rx_dropped += data[2];

		करो अणु
			start = u64_stats_fetch_begin(&r_vec->tx_sync);
			data[0] = r_vec->tx_pkts;
			data[1] = r_vec->tx_bytes;
			data[2] = r_vec->tx_errors;
		पूर्ण जबतक (u64_stats_fetch_retry(&r_vec->tx_sync, start));
		stats->tx_packets += data[0];
		stats->tx_bytes += data[1];
		stats->tx_errors += data[2];
	पूर्ण

	/* Add in device stats */
	stats->multicast += nn_पढ़ोq(nn, NFP_NET_CFG_STATS_RX_MC_FRAMES);
	stats->rx_dropped += nn_पढ़ोq(nn, NFP_NET_CFG_STATS_RX_DISCARDS);
	stats->rx_errors += nn_पढ़ोq(nn, NFP_NET_CFG_STATS_RX_ERRORS);

	stats->tx_dropped += nn_पढ़ोq(nn, NFP_NET_CFG_STATS_TX_DISCARDS);
	stats->tx_errors += nn_पढ़ोq(nn, NFP_NET_CFG_STATS_TX_ERRORS);
पूर्ण

अटल पूर्णांक nfp_net_set_features(काष्ठा net_device *netdev,
				netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	u32 new_ctrl;
	पूर्णांक err;

	/* Assume this is not called with features we have not advertised */

	new_ctrl = nn->dp.ctrl;

	अगर (changed & NETIF_F_RXCSUM) अणु
		अगर (features & NETIF_F_RXCSUM)
			new_ctrl |= nn->cap & NFP_NET_CFG_CTRL_RXCSUM_ANY;
		अन्यथा
			new_ctrl &= ~NFP_NET_CFG_CTRL_RXCSUM_ANY;
	पूर्ण

	अगर (changed & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) अणु
		अगर (features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))
			new_ctrl |= NFP_NET_CFG_CTRL_TXCSUM;
		अन्यथा
			new_ctrl &= ~NFP_NET_CFG_CTRL_TXCSUM;
	पूर्ण

	अगर (changed & (NETIF_F_TSO | NETIF_F_TSO6)) अणु
		अगर (features & (NETIF_F_TSO | NETIF_F_TSO6))
			new_ctrl |= nn->cap & NFP_NET_CFG_CTRL_LSO2 ?:
					      NFP_NET_CFG_CTRL_LSO;
		अन्यथा
			new_ctrl &= ~NFP_NET_CFG_CTRL_LSO_ANY;
	पूर्ण

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			new_ctrl |= NFP_NET_CFG_CTRL_RXVLAN;
		अन्यथा
			new_ctrl &= ~NFP_NET_CFG_CTRL_RXVLAN;
	पूर्ण

	अगर (changed & NETIF_F_HW_VLAN_CTAG_TX) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_TX)
			new_ctrl |= NFP_NET_CFG_CTRL_TXVLAN;
		अन्यथा
			new_ctrl &= ~NFP_NET_CFG_CTRL_TXVLAN;
	पूर्ण

	अगर (changed & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER)
			new_ctrl |= NFP_NET_CFG_CTRL_CTAG_FILTER;
		अन्यथा
			new_ctrl &= ~NFP_NET_CFG_CTRL_CTAG_FILTER;
	पूर्ण

	अगर (changed & NETIF_F_SG) अणु
		अगर (features & NETIF_F_SG)
			new_ctrl |= NFP_NET_CFG_CTRL_GATHER;
		अन्यथा
			new_ctrl &= ~NFP_NET_CFG_CTRL_GATHER;
	पूर्ण

	err = nfp_port_set_features(netdev, features);
	अगर (err)
		वापस err;

	nn_dbg(nn, "Feature change 0x%llx -> 0x%llx (changed=0x%llx)\n",
	       netdev->features, features, changed);

	अगर (new_ctrl == nn->dp.ctrl)
		वापस 0;

	nn_dbg(nn, "NIC ctrl: 0x%x -> 0x%x\n", nn->dp.ctrl, new_ctrl);
	nn_ग_लिखोl(nn, NFP_NET_CFG_CTRL, new_ctrl);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
	अगर (err)
		वापस err;

	nn->dp.ctrl = new_ctrl;

	वापस 0;
पूर्ण

अटल netdev_features_t
nfp_net_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       netdev_features_t features)
अणु
	u8 l4_hdr;

	/* We can't करो TSO over द्विगुन tagged packets (802.1AD) */
	features &= vlan_features_check(skb, features);

	अगर (!skb->encapsulation)
		वापस features;

	/* Ensure that inner L4 header offset fits पूर्णांकo TX descriptor field */
	अगर (skb_is_gso(skb)) अणु
		u32 hdrlen;

		hdrlen = skb_inner_transport_header(skb) - skb->data +
			inner_tcp_hdrlen(skb);

		/* Assume worst हाल scenario of having दीर्घest possible
		 * metadata prepend - 8B
		 */
		अगर (unlikely(hdrlen > NFP_NET_LSO_MAX_HDR_SZ - 8))
			features &= ~NETIF_F_GSO_MASK;
	पूर्ण

	/* VXLAN/GRE check */
	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		l4_hdr = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l4_hdr = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	पूर्ण

	अगर (skb->inner_protocol_type != ENCAP_TYPE_ETHER ||
	    skb->inner_protocol != htons(ETH_P_TEB) ||
	    (l4_hdr != IPPROTO_UDP && l4_hdr != IPPROTO_GRE) ||
	    (l4_hdr == IPPROTO_UDP &&
	     (skb_inner_mac_header(skb) - skb_transport_header(skb) !=
	      माप(काष्ठा udphdr) + माप(काष्ठा vxlanhdr))))
		वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);

	वापस features;
पूर्ण

अटल पूर्णांक
nfp_net_get_phys_port_name(काष्ठा net_device *netdev, अक्षर *name, माप_प्रकार len)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक n;

	/* If port is defined, devlink_port is रेजिस्टरed and devlink core
	 * is taking care of name क्रमmatting.
	 */
	अगर (nn->port)
		वापस -EOPNOTSUPP;

	अगर (nn->dp.is_vf || nn->vnic_no_name)
		वापस -EOPNOTSUPP;

	n = snम_लिखो(name, len, "n%d", nn->id);
	अगर (n >= len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_net_xdp_setup_drv(काष्ठा nfp_net *nn, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा bpf_prog *prog = bpf->prog;
	काष्ठा nfp_net_dp *dp;
	पूर्णांक err;

	अगर (!prog == !nn->dp.xdp_prog) अणु
		WRITE_ONCE(nn->dp.xdp_prog, prog);
		xdp_attachment_setup(&nn->xdp, bpf);
		वापस 0;
	पूर्ण

	dp = nfp_net_clone_dp(nn);
	अगर (!dp)
		वापस -ENOMEM;

	dp->xdp_prog = prog;
	dp->num_tx_rings += prog ? nn->dp.num_rx_rings : -nn->dp.num_rx_rings;
	dp->rx_dma_dir = prog ? DMA_BIसूचीECTIONAL : DMA_FROM_DEVICE;
	dp->rx_dma_off = prog ? XDP_PACKET_HEADROOM - nn->dp.rx_offset : 0;

	/* We need RX reconfig to remap the buffers (BIसूची vs FROM_DEV) */
	err = nfp_net_ring_reconfig(nn, dp, bpf->extack);
	अगर (err)
		वापस err;

	xdp_attachment_setup(&nn->xdp, bpf);
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_net_xdp_setup_hw(काष्ठा nfp_net *nn, काष्ठा netdev_bpf *bpf)
अणु
	पूर्णांक err;

	err = nfp_app_xdp_offload(nn->app, nn, bpf->prog, bpf->extack);
	अगर (err)
		वापस err;

	xdp_attachment_setup(&nn->xdp_hw, bpf);
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_net_xdp(काष्ठा net_device *netdev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस nfp_net_xdp_setup_drv(nn, xdp);
	हाल XDP_SETUP_PROG_HW:
		वापस nfp_net_xdp_setup_hw(nn, xdp);
	शेष:
		वापस nfp_app_bpf(nn->app, nn, xdp);
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_net_set_mac_address(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	काष्ठा sockaddr *saddr = addr;
	पूर्णांक err;

	err = eth_prepare_mac_addr_change(netdev, addr);
	अगर (err)
		वापस err;

	nfp_net_ग_लिखो_mac_addr(nn, saddr->sa_data);

	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_MACADDR);
	अगर (err)
		वापस err;

	eth_commit_mac_addr_change(netdev, addr);

	वापस 0;
पूर्ण

स्थिर काष्ठा net_device_ops nfp_net_netdev_ops = अणु
	.nकरो_init		= nfp_app_nकरो_init,
	.nकरो_uninit		= nfp_app_nकरो_uninit,
	.nकरो_खोलो		= nfp_net_netdev_खोलो,
	.nकरो_stop		= nfp_net_netdev_बंद,
	.nकरो_start_xmit		= nfp_net_tx,
	.nकरो_get_stats64	= nfp_net_stat64,
	.nकरो_vlan_rx_add_vid	= nfp_net_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= nfp_net_vlan_rx_समाप्त_vid,
	.nकरो_set_vf_mac         = nfp_app_set_vf_mac,
	.nकरो_set_vf_vlan        = nfp_app_set_vf_vlan,
	.nकरो_set_vf_spoofchk    = nfp_app_set_vf_spoofchk,
	.nकरो_set_vf_trust	= nfp_app_set_vf_trust,
	.nकरो_get_vf_config	= nfp_app_get_vf_config,
	.nकरो_set_vf_link_state  = nfp_app_set_vf_link_state,
	.nकरो_setup_tc		= nfp_port_setup_tc,
	.nकरो_tx_समयout		= nfp_net_tx_समयout,
	.nकरो_set_rx_mode	= nfp_net_set_rx_mode,
	.nकरो_change_mtu		= nfp_net_change_mtu,
	.nकरो_set_mac_address	= nfp_net_set_mac_address,
	.nकरो_set_features	= nfp_net_set_features,
	.nकरो_features_check	= nfp_net_features_check,
	.nकरो_get_phys_port_name	= nfp_net_get_phys_port_name,
	.nकरो_bpf		= nfp_net_xdp,
	.nकरो_get_devlink_port	= nfp_devlink_get_devlink_port,
पूर्ण;

अटल पूर्णांक nfp_udp_tunnel_sync(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक i;

	BUILD_BUG_ON(NFP_NET_N_VXLAN_PORTS & 1);
	क्रम (i = 0; i < NFP_NET_N_VXLAN_PORTS; i += 2) अणु
		काष्ठा udp_tunnel_info ti0, ti1;

		udp_tunnel_nic_get_port(netdev, table, i, &ti0);
		udp_tunnel_nic_get_port(netdev, table, i + 1, &ti1);

		nn_ग_लिखोl(nn, NFP_NET_CFG_VXLAN_PORT + i * माप(ti0.port),
			  be16_to_cpu(ti1.port) << 16 | be16_to_cpu(ti0.port));
	पूर्ण

	वापस nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_VXLAN);
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info nfp_udp_tunnels = अणु
	.sync_table     = nfp_udp_tunnel_sync,
	.flags          = UDP_TUNNEL_NIC_INFO_MAY_SLEEP |
			  UDP_TUNNEL_NIC_INFO_OPEN_ONLY,
	.tables         = अणु
		अणु
			.n_entries      = NFP_NET_N_VXLAN_PORTS,
			.tunnel_types   = UDP_TUNNEL_TYPE_VXLAN,
		पूर्ण,
	पूर्ण,
पूर्ण;

/**
 * nfp_net_info() - Prपूर्णांक general info about the NIC
 * @nn:      NFP Net device to reconfigure
 */
व्योम nfp_net_info(काष्ठा nfp_net *nn)
अणु
	nn_info(nn, "Netronome NFP-6xxx %sNetdev: TxQs=%d/%d RxQs=%d/%d\n",
		nn->dp.is_vf ? "VF " : "",
		nn->dp.num_tx_rings, nn->max_tx_rings,
		nn->dp.num_rx_rings, nn->max_rx_rings);
	nn_info(nn, "VER: %d.%d.%d.%d, Maximum supported MTU: %d\n",
		nn->fw_ver.resv, nn->fw_ver.class,
		nn->fw_ver.major, nn->fw_ver.minor,
		nn->max_mtu);
	nn_info(nn, "CAP: %#x %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		nn->cap,
		nn->cap & NFP_NET_CFG_CTRL_PROMISC  ? "PROMISC "  : "",
		nn->cap & NFP_NET_CFG_CTRL_L2BC     ? "L2BCFILT " : "",
		nn->cap & NFP_NET_CFG_CTRL_L2MC     ? "L2MCFILT " : "",
		nn->cap & NFP_NET_CFG_CTRL_RXCSUM   ? "RXCSUM "   : "",
		nn->cap & NFP_NET_CFG_CTRL_TXCSUM   ? "TXCSUM "   : "",
		nn->cap & NFP_NET_CFG_CTRL_RXVLAN   ? "RXVLAN "   : "",
		nn->cap & NFP_NET_CFG_CTRL_TXVLAN   ? "TXVLAN "   : "",
		nn->cap & NFP_NET_CFG_CTRL_SCATTER  ? "SCATTER "  : "",
		nn->cap & NFP_NET_CFG_CTRL_GATHER   ? "GATHER "   : "",
		nn->cap & NFP_NET_CFG_CTRL_LSO      ? "TSO1 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_LSO2     ? "TSO2 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_RSS      ? "RSS1 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_RSS2     ? "RSS2 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_CTAG_FILTER ? "CTAG_FILTER " : "",
		nn->cap & NFP_NET_CFG_CTRL_MSIXAUTO ? "AUTOMASK " : "",
		nn->cap & NFP_NET_CFG_CTRL_IRQMOD   ? "IRQMOD "   : "",
		nn->cap & NFP_NET_CFG_CTRL_VXLAN    ? "VXLAN "    : "",
		nn->cap & NFP_NET_CFG_CTRL_NVGRE    ? "NVGRE "	  : "",
		nn->cap & NFP_NET_CFG_CTRL_CSUM_COMPLETE ?
						      "RXCSUM_COMPLETE " : "",
		nn->cap & NFP_NET_CFG_CTRL_LIVE_ADDR ? "LIVE_ADDR " : "",
		nfp_app_extra_cap(nn->app, nn));
पूर्ण

/**
 * nfp_net_alloc() - Allocate netdev and related काष्ठाure
 * @pdev:         PCI device
 * @ctrl_bar:     PCI IOMEM with vNIC config memory
 * @needs_netdev: Whether to allocate a netdev क्रम this vNIC
 * @max_tx_rings: Maximum number of TX rings supported by device
 * @max_rx_rings: Maximum number of RX rings supported by device
 *
 * This function allocates a netdev device and fills in the initial
 * part of the @काष्ठा nfp_net काष्ठाure.  In हाल of control device
 * nfp_net काष्ठाure is allocated without the netdev.
 *
 * Return: NFP Net device काष्ठाure, or ERR_PTR on error.
 */
काष्ठा nfp_net *
nfp_net_alloc(काष्ठा pci_dev *pdev, व्योम __iomem *ctrl_bar, bool needs_netdev,
	      अचिन्हित पूर्णांक max_tx_rings, अचिन्हित पूर्णांक max_rx_rings)
अणु
	काष्ठा nfp_net *nn;
	पूर्णांक err;

	अगर (needs_netdev) अणु
		काष्ठा net_device *netdev;

		netdev = alloc_etherdev_mqs(माप(काष्ठा nfp_net),
					    max_tx_rings, max_rx_rings);
		अगर (!netdev)
			वापस ERR_PTR(-ENOMEM);

		SET_NETDEV_DEV(netdev, &pdev->dev);
		nn = netdev_priv(netdev);
		nn->dp.netdev = netdev;
	पूर्ण अन्यथा अणु
		nn = vzalloc(माप(*nn));
		अगर (!nn)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	nn->dp.dev = &pdev->dev;
	nn->dp.ctrl_bar = ctrl_bar;
	nn->pdev = pdev;

	nn->max_tx_rings = max_tx_rings;
	nn->max_rx_rings = max_rx_rings;

	nn->dp.num_tx_rings = min_t(अचिन्हित पूर्णांक,
				    max_tx_rings, num_online_cpus());
	nn->dp.num_rx_rings = min_t(अचिन्हित पूर्णांक, max_rx_rings,
				 netअगर_get_num_शेष_rss_queues());

	nn->dp.num_r_vecs = max(nn->dp.num_tx_rings, nn->dp.num_rx_rings);
	nn->dp.num_r_vecs = min_t(अचिन्हित पूर्णांक,
				  nn->dp.num_r_vecs, num_online_cpus());

	nn->dp.txd_cnt = NFP_NET_TX_DESCS_DEFAULT;
	nn->dp.rxd_cnt = NFP_NET_RX_DESCS_DEFAULT;

	sema_init(&nn->bar_lock, 1);

	spin_lock_init(&nn->reconfig_lock);
	spin_lock_init(&nn->link_status_lock);

	समयr_setup(&nn->reconfig_समयr, nfp_net_reconfig_समयr, 0);

	err = nfp_net_tlv_caps_parse(&nn->pdev->dev, nn->dp.ctrl_bar,
				     &nn->tlv_caps);
	अगर (err)
		जाओ err_मुक्त_nn;

	err = nfp_ccm_mbox_alloc(nn);
	अगर (err)
		जाओ err_मुक्त_nn;

	वापस nn;

err_मुक्त_nn:
	अगर (nn->dp.netdev)
		मुक्त_netdev(nn->dp.netdev);
	अन्यथा
		vमुक्त(nn);
	वापस ERR_PTR(err);
पूर्ण

/**
 * nfp_net_मुक्त() - Unकरो what @nfp_net_alloc() did
 * @nn:      NFP Net device to reconfigure
 */
व्योम nfp_net_मुक्त(काष्ठा nfp_net *nn)
अणु
	WARN_ON(समयr_pending(&nn->reconfig_समयr) || nn->reconfig_posted);
	nfp_ccm_mbox_मुक्त(nn);

	अगर (nn->dp.netdev)
		मुक्त_netdev(nn->dp.netdev);
	अन्यथा
		vमुक्त(nn);
पूर्ण

/**
 * nfp_net_rss_key_sz() - Get current size of the RSS key
 * @nn:		NFP Net device instance
 *
 * Return: size of the RSS key क्रम currently selected hash function.
 */
अचिन्हित पूर्णांक nfp_net_rss_key_sz(काष्ठा nfp_net *nn)
अणु
	चयन (nn->rss_hfunc) अणु
	हाल ETH_RSS_HASH_TOP:
		वापस NFP_NET_CFG_RSS_KEY_SZ;
	हाल ETH_RSS_HASH_XOR:
		वापस 0;
	हाल ETH_RSS_HASH_CRC32:
		वापस 4;
	पूर्ण

	nn_warn(nn, "Unknown hash function: %u\n", nn->rss_hfunc);
	वापस 0;
पूर्ण

/**
 * nfp_net_rss_init() - Set the initial RSS parameters
 * @nn:	     NFP Net device to reconfigure
 */
अटल व्योम nfp_net_rss_init(काष्ठा nfp_net *nn)
अणु
	अचिन्हित दीर्घ func_bit, rss_cap_hfunc;
	u32 reg;

	/* Read the RSS function capability and select first supported func */
	reg = nn_पढ़ोl(nn, NFP_NET_CFG_RSS_CAP);
	rss_cap_hfunc =	FIELD_GET(NFP_NET_CFG_RSS_CAP_HFUNC, reg);
	अगर (!rss_cap_hfunc)
		rss_cap_hfunc =	FIELD_GET(NFP_NET_CFG_RSS_CAP_HFUNC,
					  NFP_NET_CFG_RSS_TOEPLITZ);

	func_bit = find_first_bit(&rss_cap_hfunc, NFP_NET_CFG_RSS_HFUNCS);
	अगर (func_bit == NFP_NET_CFG_RSS_HFUNCS) अणु
		dev_warn(nn->dp.dev,
			 "Bad RSS config, defaulting to Toeplitz hash\n");
		func_bit = ETH_RSS_HASH_TOP_BIT;
	पूर्ण
	nn->rss_hfunc = 1 << func_bit;

	netdev_rss_key_fill(nn->rss_key, nfp_net_rss_key_sz(nn));

	nfp_net_rss_init_itbl(nn);

	/* Enable IPv4/IPv6 TCP by शेष */
	nn->rss_cfg = NFP_NET_CFG_RSS_IPV4_TCP |
		      NFP_NET_CFG_RSS_IPV6_TCP |
		      FIELD_PREP(NFP_NET_CFG_RSS_HFUNC, nn->rss_hfunc) |
		      NFP_NET_CFG_RSS_MASK;
पूर्ण

/**
 * nfp_net_irqmod_init() - Set the initial IRQ moderation parameters
 * @nn:	     NFP Net device to reconfigure
 */
अटल व्योम nfp_net_irqmod_init(काष्ठा nfp_net *nn)
अणु
	nn->rx_coalesce_usecs      = 50;
	nn->rx_coalesce_max_frames = 64;
	nn->tx_coalesce_usecs      = 50;
	nn->tx_coalesce_max_frames = 64;
पूर्ण

अटल व्योम nfp_net_netdev_init(काष्ठा nfp_net *nn)
अणु
	काष्ठा net_device *netdev = nn->dp.netdev;

	nfp_net_ग_लिखो_mac_addr(nn, nn->dp.netdev->dev_addr);

	netdev->mtu = nn->dp.mtu;

	/* Advertise/enable offloads based on capabilities
	 *
	 * Note: netdev->features show the currently enabled features
	 * and netdev->hw_features advertises which features are
	 * supported.  By शेष we enable most features.
	 */
	अगर (nn->cap & NFP_NET_CFG_CTRL_LIVE_ADDR)
		netdev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	netdev->hw_features = NETIF_F_HIGHDMA;
	अगर (nn->cap & NFP_NET_CFG_CTRL_RXCSUM_ANY) अणु
		netdev->hw_features |= NETIF_F_RXCSUM;
		nn->dp.ctrl |= nn->cap & NFP_NET_CFG_CTRL_RXCSUM_ANY;
	पूर्ण
	अगर (nn->cap & NFP_NET_CFG_CTRL_TXCSUM) अणु
		netdev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_TXCSUM;
	पूर्ण
	अगर (nn->cap & NFP_NET_CFG_CTRL_GATHER) अणु
		netdev->hw_features |= NETIF_F_SG;
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_GATHER;
	पूर्ण
	अगर ((nn->cap & NFP_NET_CFG_CTRL_LSO && nn->fw_ver.major > 2) ||
	    nn->cap & NFP_NET_CFG_CTRL_LSO2) अणु
		netdev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;
		nn->dp.ctrl |= nn->cap & NFP_NET_CFG_CTRL_LSO2 ?:
					 NFP_NET_CFG_CTRL_LSO;
	पूर्ण
	अगर (nn->cap & NFP_NET_CFG_CTRL_RSS_ANY)
		netdev->hw_features |= NETIF_F_RXHASH;
	अगर (nn->cap & NFP_NET_CFG_CTRL_VXLAN) अणु
		अगर (nn->cap & NFP_NET_CFG_CTRL_LSO)
			netdev->hw_features |= NETIF_F_GSO_UDP_TUNNEL;
		netdev->udp_tunnel_nic_info = &nfp_udp_tunnels;
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_VXLAN;
	पूर्ण
	अगर (nn->cap & NFP_NET_CFG_CTRL_NVGRE) अणु
		अगर (nn->cap & NFP_NET_CFG_CTRL_LSO)
			netdev->hw_features |= NETIF_F_GSO_GRE;
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_NVGRE;
	पूर्ण
	अगर (nn->cap & (NFP_NET_CFG_CTRL_VXLAN | NFP_NET_CFG_CTRL_NVGRE))
		netdev->hw_enc_features = netdev->hw_features;

	netdev->vlan_features = netdev->hw_features;

	अगर (nn->cap & NFP_NET_CFG_CTRL_RXVLAN) अणु
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX;
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_RXVLAN;
	पूर्ण
	अगर (nn->cap & NFP_NET_CFG_CTRL_TXVLAN) अणु
		अगर (nn->cap & NFP_NET_CFG_CTRL_LSO2) अणु
			nn_warn(nn, "Device advertises both TSO2 and TXVLAN. Refusing to enable TXVLAN.\n");
		पूर्ण अन्यथा अणु
			netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX;
			nn->dp.ctrl |= NFP_NET_CFG_CTRL_TXVLAN;
		पूर्ण
	पूर्ण
	अगर (nn->cap & NFP_NET_CFG_CTRL_CTAG_FILTER) अणु
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_CTAG_FILTER;
	पूर्ण

	netdev->features = netdev->hw_features;

	अगर (nfp_app_has_tc(nn->app) && nn->port)
		netdev->hw_features |= NETIF_F_HW_TC;

	/* Advertise but disable TSO by शेष. */
	netdev->features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
	nn->dp.ctrl &= ~NFP_NET_CFG_CTRL_LSO_ANY;

	/* Finalise the netdev setup */
	netdev->netdev_ops = &nfp_net_netdev_ops;
	netdev->watchकरोg_समयo = msecs_to_jअगरfies(5 * 1000);

	/* MTU range: 68 - hw-specअगरic max */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = nn->max_mtu;

	netdev->gso_max_segs = NFP_NET_LSO_MAX_SEGS;

	netअगर_carrier_off(netdev);

	nfp_net_set_ethtool_ops(netdev);
पूर्ण

अटल पूर्णांक nfp_net_पढ़ो_caps(काष्ठा nfp_net *nn)
अणु
	/* Get some of the पढ़ो-only fields from the BAR */
	nn->cap = nn_पढ़ोl(nn, NFP_NET_CFG_CAP);
	nn->max_mtu = nn_पढ़ोl(nn, NFP_NET_CFG_MAX_MTU);

	/* ABI 4.x and ctrl vNIC always use chained metadata, in other हालs
	 * we allow use of non-chained metadata अगर RSS(v1) is the only
	 * advertised capability requiring metadata.
	 */
	nn->dp.chained_metadata_क्रमmat = nn->fw_ver.major == 4 ||
					 !nn->dp.netdev ||
					 !(nn->cap & NFP_NET_CFG_CTRL_RSS) ||
					 nn->cap & NFP_NET_CFG_CTRL_CHAIN_META;
	/* RSS(v1) uses non-chained metadata क्रमmat, except in ABI 4.x where
	 * it has the same meaning as RSSv2.
	 */
	अगर (nn->dp.chained_metadata_क्रमmat && nn->fw_ver.major != 4)
		nn->cap &= ~NFP_NET_CFG_CTRL_RSS;

	/* Determine RX packet/metadata boundary offset */
	अगर (nn->fw_ver.major >= 2) अणु
		u32 reg;

		reg = nn_पढ़ोl(nn, NFP_NET_CFG_RX_OFFSET);
		अगर (reg > NFP_NET_MAX_PREPEND) अणु
			nn_err(nn, "Invalid rx offset: %d\n", reg);
			वापस -EINVAL;
		पूर्ण
		nn->dp.rx_offset = reg;
	पूर्ण अन्यथा अणु
		nn->dp.rx_offset = NFP_NET_RX_OFFSET;
	पूर्ण

	/* For control vNICs mask out the capabilities app करोesn't want. */
	अगर (!nn->dp.netdev)
		nn->cap &= nn->app->type->ctrl_cap_mask;

	वापस 0;
पूर्ण

/**
 * nfp_net_init() - Initialise/finalise the nfp_net काष्ठाure
 * @nn:		NFP Net device काष्ठाure
 *
 * Return: 0 on success or negative त्रुटि_सं on error.
 */
पूर्णांक nfp_net_init(काष्ठा nfp_net *nn)
अणु
	पूर्णांक err;

	nn->dp.rx_dma_dir = DMA_FROM_DEVICE;

	err = nfp_net_पढ़ो_caps(nn);
	अगर (err)
		वापस err;

	/* Set शेष MTU and Freelist buffer size */
	अगर (!nfp_net_is_data_vnic(nn) && nn->app->ctrl_mtu) अणु
		nn->dp.mtu = min(nn->app->ctrl_mtu, nn->max_mtu);
	पूर्ण अन्यथा अगर (nn->max_mtu < NFP_NET_DEFAULT_MTU) अणु
		nn->dp.mtu = nn->max_mtu;
	पूर्ण अन्यथा अणु
		nn->dp.mtu = NFP_NET_DEFAULT_MTU;
	पूर्ण
	nn->dp.fl_bufsz = nfp_net_calc_fl_bufsz(&nn->dp);

	अगर (nfp_app_ctrl_uses_data_vnics(nn->app))
		nn->dp.ctrl |= nn->cap & NFP_NET_CFG_CTRL_CMSG_DATA;

	अगर (nn->cap & NFP_NET_CFG_CTRL_RSS_ANY) अणु
		nfp_net_rss_init(nn);
		nn->dp.ctrl |= nn->cap & NFP_NET_CFG_CTRL_RSS2 ?:
					 NFP_NET_CFG_CTRL_RSS;
	पूर्ण

	/* Allow L2 Broadcast and Multicast through by शेष, अगर supported */
	अगर (nn->cap & NFP_NET_CFG_CTRL_L2BC)
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_L2BC;

	/* Allow IRQ moderation, अगर supported */
	अगर (nn->cap & NFP_NET_CFG_CTRL_IRQMOD) अणु
		nfp_net_irqmod_init(nn);
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_IRQMOD;
	पूर्ण

	/* Stash the re-configuration queue away.  First odd queue in TX Bar */
	nn->qcp_cfg = nn->tx_bar + NFP_QCP_QUEUE_ADDR_SZ;

	/* Make sure the FW knows the netdev is supposed to be disabled here */
	nn_ग_लिखोl(nn, NFP_NET_CFG_CTRL, 0);
	nn_ग_लिखोq(nn, NFP_NET_CFG_TXRS_ENABLE, 0);
	nn_ग_लिखोq(nn, NFP_NET_CFG_RXRS_ENABLE, 0);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_RING |
				   NFP_NET_CFG_UPDATE_GEN);
	अगर (err)
		वापस err;

	अगर (nn->dp.netdev) अणु
		nfp_net_netdev_init(nn);

		err = nfp_ccm_mbox_init(nn);
		अगर (err)
			वापस err;

		err = nfp_net_tls_init(nn);
		अगर (err)
			जाओ err_clean_mbox;
	पूर्ण

	nfp_net_vecs_init(nn);

	अगर (!nn->dp.netdev)
		वापस 0;
	वापस रेजिस्टर_netdev(nn->dp.netdev);

err_clean_mbox:
	nfp_ccm_mbox_clean(nn);
	वापस err;
पूर्ण

/**
 * nfp_net_clean() - Unकरो what nfp_net_init() did.
 * @nn:		NFP Net device काष्ठाure
 */
व्योम nfp_net_clean(काष्ठा nfp_net *nn)
अणु
	अगर (!nn->dp.netdev)
		वापस;

	unरेजिस्टर_netdev(nn->dp.netdev);
	nfp_ccm_mbox_clean(nn);
	nfp_net_reconfig_रुको_posted(nn);
पूर्ण
