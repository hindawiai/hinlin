<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <net/dst.h>

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-defines.h"
#समावेश "ethernet-mem.h"
#समावेश "ethernet-rx.h"
#समावेश "ethernet-tx.h"
#समावेश "ethernet-mdio.h"
#समावेश "ethernet-util.h"

#घोषणा OCTEON_MAX_MTU 65392

अटल पूर्णांक num_packet_buffers = 1024;
module_param(num_packet_buffers, पूर्णांक, 0444);
MODULE_PARM_DESC(num_packet_buffers, "\n"
	"\tNumber of packet buffers to allocate and store in the\n"
	"\tFPA. By default, 1024 packet buffers are used.\n");

अटल पूर्णांक घात_receive_group = 15;
module_param(घात_receive_group, पूर्णांक, 0444);
MODULE_PARM_DESC(घात_receive_group, "\n"
	"\tPOW group to receive packets from. All ethernet hardware\n"
	"\twill be configured to send incoming packets to this POW\n"
	"\tgroup. Also any other software can submit packets to this\n"
	"\tgroup for the kernel to process.");

अटल पूर्णांक receive_group_order;
module_param(receive_group_order, पूर्णांक, 0444);
MODULE_PARM_DESC(receive_group_order, "\n"
	"\tOrder (0..4) of receive groups to take into use. Ethernet hardware\n"
	"\twill be configured to send incoming packets to multiple POW\n"
	"\tgroups. pow_receive_group parameter is ignored when multiple\n"
	"\tgroups are taken into use and groups are allocated starting\n"
	"\tfrom 0. By default, a single group is used.\n");

पूर्णांक घात_send_group = -1;
module_param(घात_send_group, पूर्णांक, 0644);
MODULE_PARM_DESC(घात_send_group, "\n"
	"\tPOW group to send packets to other software on. This\n"
	"\tcontrols the creation of the virtual device pow0.\n"
	"\talways_use_pow also depends on this value.");

पूर्णांक always_use_घात;
module_param(always_use_घात, पूर्णांक, 0444);
MODULE_PARM_DESC(always_use_घात, "\n"
	"\tWhen set, always send to the pow group. This will cause\n"
	"\tpackets sent to real ethernet devices to be sent to the\n"
	"\tPOW group instead of the hardware. Unless some other\n"
	"\tapplication changes the config, packets will still be\n"
	"\treceived from the low level hardware. Use this option\n"
	"\tto allow a CVMX app to intercept all packets from the\n"
	"\tlinux kernel. You must specify pow_send_group along with\n"
	"\tthis option.");

अक्षर घात_send_list[128] = "";
module_param_string(घात_send_list, घात_send_list, माप(घात_send_list), 0444);
MODULE_PARM_DESC(घात_send_list, "\n"
	"\tComma separated list of ethernet devices that should use the\n"
	"\tPOW for transmit instead of the actual ethernet hardware. This\n"
	"\tis a per port version of always_use_pow. always_use_pow takes\n"
	"\tprecedence over this list. For example, setting this to\n"
	"\t\"eth2,spi3,spi7\" would cause these three devices to transmit\n"
	"\tusing the pow_send_group.");

पूर्णांक rx_napi_weight = 32;
module_param(rx_napi_weight, पूर्णांक, 0444);
MODULE_PARM_DESC(rx_napi_weight, "The NAPI WEIGHT parameter.");

/* Mask indicating which receive groups are in use. */
पूर्णांक घात_receive_groups;

/*
 * cvm_oct_poll_queue_stopping - flag to indicate polling should stop.
 *
 * Set to one right beक्रमe cvm_oct_poll_queue is destroyed.
 */
atomic_t cvm_oct_poll_queue_stopping = ATOMIC_INIT(0);

/*
 * Array of every ethernet device owned by this driver indexed by
 * the ipd input port number.
 */
काष्ठा net_device *cvm_oct_device[TOTAL_NUMBER_OF_PORTS];

u64 cvm_oct_tx_poll_पूर्णांकerval;

अटल व्योम cvm_oct_rx_refill_worker(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(cvm_oct_rx_refill_work, cvm_oct_rx_refill_worker);

अटल व्योम cvm_oct_rx_refill_worker(काष्ठा work_काष्ठा *work)
अणु
	/*
	 * FPA 0 may have been drained, try to refill it अगर we need
	 * more than num_packet_buffers / 2, otherwise normal receive
	 * processing will refill it.  If it were drained, no packets
	 * could be received so cvm_oct_napi_poll would never be
	 * invoked to करो the refill.
	 */
	cvm_oct_rx_refill_pool(num_packet_buffers / 2);

	अगर (!atomic_पढ़ो(&cvm_oct_poll_queue_stopping))
		schedule_delayed_work(&cvm_oct_rx_refill_work, HZ);
पूर्ण

अटल व्योम cvm_oct_periodic_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा octeon_ethernet *priv = container_of(work,
						    काष्ठा octeon_ethernet,
						    port_periodic_work.work);

	अगर (priv->poll)
		priv->poll(cvm_oct_device[priv->port]);

	cvm_oct_device[priv->port]->netdev_ops->nकरो_get_stats
						(cvm_oct_device[priv->port]);

	अगर (!atomic_पढ़ो(&cvm_oct_poll_queue_stopping))
		schedule_delayed_work(&priv->port_periodic_work, HZ);
पूर्ण

अटल व्योम cvm_oct_configure_common_hw(व्योम)
अणु
	/* Setup the FPA */
	cvmx_fpa_enable();
	cvm_oct_mem_fill_fpa(CVMX_FPA_PACKET_POOL, CVMX_FPA_PACKET_POOL_SIZE,
			     num_packet_buffers);
	cvm_oct_mem_fill_fpa(CVMX_FPA_WQE_POOL, CVMX_FPA_WQE_POOL_SIZE,
			     num_packet_buffers);
	अगर (CVMX_FPA_OUTPUT_BUFFER_POOL != CVMX_FPA_PACKET_POOL)
		cvm_oct_mem_fill_fpa(CVMX_FPA_OUTPUT_BUFFER_POOL,
				     CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE, 1024);

#अगर_घोषित __LITTLE_ENDIAN
	अणु
		जोड़ cvmx_ipd_ctl_status ipd_ctl_status;

		ipd_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_IPD_CTL_STATUS);
		ipd_ctl_status.s.pkt_lend = 1;
		ipd_ctl_status.s.wqe_lend = 1;
		cvmx_ग_लिखो_csr(CVMX_IPD_CTL_STATUS, ipd_ctl_status.u64);
	पूर्ण
#पूर्ण_अगर

	cvmx_helper_setup_red(num_packet_buffers / 4, num_packet_buffers / 8);
पूर्ण

/**
 * cvm_oct_मुक्त_work- Free a work queue entry
 *
 * @work_queue_entry: Work queue entry to मुक्त
 *
 * Returns Zero on success, Negative on failure.
 */
पूर्णांक cvm_oct_मुक्त_work(व्योम *work_queue_entry)
अणु
	काष्ठा cvmx_wqe *work = work_queue_entry;

	पूर्णांक segments = work->word2.s.bufs;
	जोड़ cvmx_buf_ptr segment_ptr = work->packet_ptr;

	जबतक (segments--) अणु
		जोड़ cvmx_buf_ptr next_ptr = *(जोड़ cvmx_buf_ptr *)
			cvmx_phys_to_ptr(segment_ptr.s.addr - 8);
		अगर (unlikely(!segment_ptr.s.i))
			cvmx_fpa_मुक्त(cvm_oct_get_buffer_ptr(segment_ptr),
				      segment_ptr.s.pool,
				      CVMX_FPA_PACKET_POOL_SIZE / 128);
		segment_ptr = next_ptr;
	पूर्ण
	cvmx_fpa_मुक्त(work, CVMX_FPA_WQE_POOL, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cvm_oct_मुक्त_work);

/**
 * cvm_oct_common_get_stats - get the low level ethernet statistics
 * @dev:    Device to get the statistics from
 *
 * Returns Poपूर्णांकer to the statistics
 */
अटल काष्ठा net_device_stats *cvm_oct_common_get_stats(काष्ठा net_device *dev)
अणु
	cvmx_pip_port_status_t rx_status;
	cvmx_pko_port_status_t tx_status;
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);

	अगर (priv->port < CVMX_PIP_NUM_INPUT_PORTS) अणु
		अगर (octeon_is_simulation()) अणु
			/* The simulator करोesn't support statistics */
			स_रखो(&rx_status, 0, माप(rx_status));
			स_रखो(&tx_status, 0, माप(tx_status));
		पूर्ण अन्यथा अणु
			cvmx_pip_get_port_status(priv->port, 1, &rx_status);
			cvmx_pko_get_port_status(priv->port, 1, &tx_status);
		पूर्ण

		dev->stats.rx_packets += rx_status.inb_packets;
		dev->stats.tx_packets += tx_status.packets;
		dev->stats.rx_bytes += rx_status.inb_octets;
		dev->stats.tx_bytes += tx_status.octets;
		dev->stats.multicast += rx_status.multicast_packets;
		dev->stats.rx_crc_errors += rx_status.inb_errors;
		dev->stats.rx_frame_errors += rx_status.fcs_align_err_packets;
		dev->stats.rx_dropped += rx_status.dropped_packets;
	पूर्ण

	वापस &dev->stats;
पूर्ण

/**
 * cvm_oct_common_change_mtu - change the link MTU
 * @dev:     Device to change
 * @new_mtu: The new MTU
 *
 * Returns Zero on success
 */
अटल पूर्णांक cvm_oct_common_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	पूर्णांक पूर्णांकerface = INTERFACE(priv->port);
#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
	पूर्णांक vlan_bytes = VLAN_HLEN;
#अन्यथा
	पूर्णांक vlan_bytes = 0;
#पूर्ण_अगर
	पूर्णांक mtu_overhead = ETH_HLEN + ETH_FCS_LEN + vlan_bytes;

	dev->mtu = new_mtu;

	अगर ((पूर्णांकerface < 2) &&
	    (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface) !=
		CVMX_HELPER_INTERFACE_MODE_SPI)) अणु
		पूर्णांक index = INDEX(priv->port);
		/* Add ethernet header and FCS, and VLAN अगर configured. */
		पूर्णांक max_packet = new_mtu + mtu_overhead;

		अगर (OCTEON_IS_MODEL(OCTEON_CN3XXX) ||
		    OCTEON_IS_MODEL(OCTEON_CN58XX)) अणु
			/* Signal errors on packets larger than the MTU */
			cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_FRM_MAX(index, पूर्णांकerface),
				       max_packet);
		पूर्ण अन्यथा अणु
			/*
			 * Set the hardware to truncate packets larger
			 * than the MTU and smaller the 64 bytes.
			 */
			जोड़ cvmx_pip_frm_len_chkx frm_len_chk;

			frm_len_chk.u64 = 0;
			frm_len_chk.s.minlen = VLAN_ETH_ZLEN;
			frm_len_chk.s.maxlen = max_packet;
			cvmx_ग_लिखो_csr(CVMX_PIP_FRM_LEN_CHKX(पूर्णांकerface),
				       frm_len_chk.u64);
		पूर्ण
		/*
		 * Set the hardware to truncate packets larger than
		 * the MTU. The jabber रेजिस्टर must be set to a
		 * multiple of 8 bytes, so round up.
		 */
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_JABBER(index, पूर्णांकerface),
			       (max_packet + 7) & ~7u);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cvm_oct_common_set_multicast_list - set the multicast list
 * @dev:    Device to work on
 */
अटल व्योम cvm_oct_common_set_multicast_list(काष्ठा net_device *dev)
अणु
	जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	पूर्णांक पूर्णांकerface = INTERFACE(priv->port);

	अगर ((पूर्णांकerface < 2) &&
	    (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface) !=
		CVMX_HELPER_INTERFACE_MODE_SPI)) अणु
		जोड़ cvmx_gmxx_rxx_adr_ctl control;
		पूर्णांक index = INDEX(priv->port);

		control.u64 = 0;
		control.s.bcst = 1;	/* Allow broadcast MAC addresses */

		अगर (!netdev_mc_empty(dev) || (dev->flags & IFF_ALLMULTI) ||
		    (dev->flags & IFF_PROMISC))
			/* Force accept multicast packets */
			control.s.mcst = 2;
		अन्यथा
			/* Force reject multicast packets */
			control.s.mcst = 1;

		अगर (dev->flags & IFF_PROMISC)
			/*
			 * Reject matches अगर promisc. Since CAM is
			 * shut off, should accept everything.
			 */
			control.s.cam_mode = 0;
		अन्यथा
			/* Filter packets based on the CAM */
			control.s.cam_mode = 1;

		gmx_cfg.u64 =
		    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface),
			       gmx_cfg.u64 & ~1ull);

		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CTL(index, पूर्णांकerface),
			       control.u64);
		अगर (dev->flags & IFF_PROMISC)
			cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM_EN
				       (index, पूर्णांकerface), 0);
		अन्यथा
			cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM_EN
				       (index, पूर्णांकerface), 1);

		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface),
			       gmx_cfg.u64);
	पूर्ण
पूर्ण

अटल पूर्णांक cvm_oct_set_mac_filter(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;
	पूर्णांक पूर्णांकerface = INTERFACE(priv->port);

	अगर ((पूर्णांकerface < 2) &&
	    (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface) !=
		CVMX_HELPER_INTERFACE_MODE_SPI)) अणु
		पूर्णांक i;
		u8 *ptr = dev->dev_addr;
		u64 mac = 0;
		पूर्णांक index = INDEX(priv->port);

		क्रम (i = 0; i < 6; i++)
			mac = (mac << 8) | (u64)ptr[i];

		gmx_cfg.u64 =
		    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface),
			       gmx_cfg.u64 & ~1ull);

		cvmx_ग_लिखो_csr(CVMX_GMXX_SMACX(index, पूर्णांकerface), mac);
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM0(index, पूर्णांकerface),
			       ptr[0]);
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM1(index, पूर्णांकerface),
			       ptr[1]);
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM2(index, पूर्णांकerface),
			       ptr[2]);
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM3(index, पूर्णांकerface),
			       ptr[3]);
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM4(index, पूर्णांकerface),
			       ptr[4]);
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_ADR_CAM5(index, पूर्णांकerface),
			       ptr[5]);
		cvm_oct_common_set_multicast_list(dev);
		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface),
			       gmx_cfg.u64);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cvm_oct_common_set_mac_address - set the hardware MAC address क्रम a device
 * @dev:    The device in question.
 * @addr:   Socket address.
 *
 * Returns Zero on success
 */
अटल पूर्णांक cvm_oct_common_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	पूर्णांक r = eth_mac_addr(dev, addr);

	अगर (r)
		वापस r;
	वापस cvm_oct_set_mac_filter(dev);
पूर्ण

/**
 * cvm_oct_common_init - per network device initialization
 * @dev:    Device to initialize
 *
 * Returns Zero on success
 */
पूर्णांक cvm_oct_common_init(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	पूर्णांक ret;

	ret = of_get_mac_address(priv->of_node, dev->dev_addr);
	अगर (ret)
		eth_hw_addr_अक्रमom(dev);

	/*
	 * Force the पूर्णांकerface to use the POW send अगर always_use_घात
	 * was specअगरied or it is in the घात send list.
	 */
	अगर ((घात_send_group != -1) &&
	    (always_use_घात || म_माला(घात_send_list, dev->name)))
		priv->queue = -1;

	अगर (priv->queue != -1)
		dev->features |= NETIF_F_SG | NETIF_F_IP_CSUM;

	/* We करो our own locking, Linux करोesn't need to */
	dev->features |= NETIF_F_LLTX;
	dev->ethtool_ops = &cvm_oct_ethtool_ops;

	cvm_oct_set_mac_filter(dev);
	dev_set_mtu(dev, dev->mtu);

	/*
	 * Zero out stats क्रम port so we won't mistakenly show
	 * counters from the bootloader.
	 */
	स_रखो(dev->netdev_ops->nकरो_get_stats(dev), 0,
	       माप(काष्ठा net_device_stats));

	अगर (dev->netdev_ops->nकरो_stop)
		dev->netdev_ops->nकरो_stop(dev);

	वापस 0;
पूर्ण

व्योम cvm_oct_common_uninit(काष्ठा net_device *dev)
अणु
	अगर (dev->phydev)
		phy_disconnect(dev->phydev);
पूर्ण

पूर्णांक cvm_oct_common_खोलो(काष्ठा net_device *dev,
			व्योम (*link_poll)(काष्ठा net_device *))
अणु
	जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	पूर्णांक पूर्णांकerface = INTERFACE(priv->port);
	पूर्णांक index = INDEX(priv->port);
	जोड़ cvmx_helper_link_info link_info;
	पूर्णांक rv;

	rv = cvm_oct_phy_setup_device(dev);
	अगर (rv)
		वापस rv;

	gmx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
	gmx_cfg.s.en = 1;
	अगर (octeon_has_feature(OCTEON_FEATURE_PKND))
		gmx_cfg.s.pknd = priv->port;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmx_cfg.u64);

	अगर (octeon_is_simulation())
		वापस 0;

	अगर (dev->phydev) अणु
		पूर्णांक r = phy_पढ़ो_status(dev->phydev);

		अगर (r == 0 && dev->phydev->link == 0)
			netअगर_carrier_off(dev);
		cvm_oct_adjust_link(dev);
	पूर्ण अन्यथा अणु
		link_info = cvmx_helper_link_get(priv->port);
		अगर (!link_info.s.link_up)
			netअगर_carrier_off(dev);
		priv->poll = link_poll;
		link_poll(dev);
	पूर्ण

	वापस 0;
पूर्ण

व्योम cvm_oct_link_poll(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	जोड़ cvmx_helper_link_info link_info;

	link_info = cvmx_helper_link_get(priv->port);
	अगर (link_info.u64 == priv->link_info)
		वापस;

	अगर (cvmx_helper_link_set(priv->port, link_info))
		link_info.u64 = priv->link_info;
	अन्यथा
		priv->link_info = link_info.u64;

	अगर (link_info.s.link_up) अणु
		अगर (!netअगर_carrier_ok(dev))
			netअगर_carrier_on(dev);
	पूर्ण अन्यथा अगर (netअगर_carrier_ok(dev)) अणु
		netअगर_carrier_off(dev);
	पूर्ण
	cvm_oct_note_carrier(priv, link_info);
पूर्ण

अटल पूर्णांक cvm_oct_xaui_खोलो(काष्ठा net_device *dev)
अणु
	वापस cvm_oct_common_खोलो(dev, cvm_oct_link_poll);
पूर्ण

अटल स्थिर काष्ठा net_device_ops cvm_oct_npi_netdev_ops = अणु
	.nकरो_init		= cvm_oct_common_init,
	.nकरो_uninit		= cvm_oct_common_uninit,
	.nकरो_start_xmit		= cvm_oct_xmit,
	.nकरो_set_rx_mode	= cvm_oct_common_set_multicast_list,
	.nकरो_set_mac_address	= cvm_oct_common_set_mac_address,
	.nकरो_करो_ioctl		= cvm_oct_ioctl,
	.nकरो_change_mtu		= cvm_oct_common_change_mtu,
	.nकरो_get_stats		= cvm_oct_common_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cvm_oct_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops cvm_oct_xaui_netdev_ops = अणु
	.nकरो_init		= cvm_oct_common_init,
	.nकरो_uninit		= cvm_oct_common_uninit,
	.nकरो_खोलो		= cvm_oct_xaui_खोलो,
	.nकरो_stop		= cvm_oct_common_stop,
	.nकरो_start_xmit		= cvm_oct_xmit,
	.nकरो_set_rx_mode	= cvm_oct_common_set_multicast_list,
	.nकरो_set_mac_address	= cvm_oct_common_set_mac_address,
	.nकरो_करो_ioctl		= cvm_oct_ioctl,
	.nकरो_change_mtu		= cvm_oct_common_change_mtu,
	.nकरो_get_stats		= cvm_oct_common_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cvm_oct_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops cvm_oct_sgmii_netdev_ops = अणु
	.nकरो_init		= cvm_oct_sgmii_init,
	.nकरो_uninit		= cvm_oct_common_uninit,
	.nकरो_खोलो		= cvm_oct_sgmii_खोलो,
	.nकरो_stop		= cvm_oct_common_stop,
	.nकरो_start_xmit		= cvm_oct_xmit,
	.nकरो_set_rx_mode	= cvm_oct_common_set_multicast_list,
	.nकरो_set_mac_address	= cvm_oct_common_set_mac_address,
	.nकरो_करो_ioctl		= cvm_oct_ioctl,
	.nकरो_change_mtu		= cvm_oct_common_change_mtu,
	.nकरो_get_stats		= cvm_oct_common_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cvm_oct_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops cvm_oct_spi_netdev_ops = अणु
	.nकरो_init		= cvm_oct_spi_init,
	.nकरो_uninit		= cvm_oct_spi_uninit,
	.nकरो_start_xmit		= cvm_oct_xmit,
	.nकरो_set_rx_mode	= cvm_oct_common_set_multicast_list,
	.nकरो_set_mac_address	= cvm_oct_common_set_mac_address,
	.nकरो_करो_ioctl		= cvm_oct_ioctl,
	.nकरो_change_mtu		= cvm_oct_common_change_mtu,
	.nकरो_get_stats		= cvm_oct_common_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cvm_oct_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops cvm_oct_rgmii_netdev_ops = अणु
	.nकरो_init		= cvm_oct_common_init,
	.nकरो_uninit		= cvm_oct_common_uninit,
	.nकरो_खोलो		= cvm_oct_rgmii_खोलो,
	.nकरो_stop		= cvm_oct_common_stop,
	.nकरो_start_xmit		= cvm_oct_xmit,
	.nकरो_set_rx_mode	= cvm_oct_common_set_multicast_list,
	.nकरो_set_mac_address	= cvm_oct_common_set_mac_address,
	.nकरो_करो_ioctl		= cvm_oct_ioctl,
	.nकरो_change_mtu		= cvm_oct_common_change_mtu,
	.nकरो_get_stats		= cvm_oct_common_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cvm_oct_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops cvm_oct_घात_netdev_ops = अणु
	.nकरो_init		= cvm_oct_common_init,
	.nकरो_start_xmit		= cvm_oct_xmit_घात,
	.nकरो_set_rx_mode	= cvm_oct_common_set_multicast_list,
	.nकरो_set_mac_address	= cvm_oct_common_set_mac_address,
	.nकरो_करो_ioctl		= cvm_oct_ioctl,
	.nकरो_change_mtu		= cvm_oct_common_change_mtu,
	.nकरो_get_stats		= cvm_oct_common_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cvm_oct_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा device_node *cvm_oct_of_get_child
				(स्थिर काष्ठा device_node *parent, पूर्णांक reg_val)
अणु
	काष्ठा device_node *node;
	स्थिर __be32 *addr;
	पूर्णांक size;

	क्रम_each_child_of_node(parent, node) अणु
		addr = of_get_property(node, "reg", &size);
		अगर (addr && (be32_to_cpu(*addr) == reg_val))
			अवरोध;
	पूर्ण
	वापस node;
पूर्ण

अटल काष्ठा device_node *cvm_oct_node_क्रम_port(काष्ठा device_node *pip,
						 पूर्णांक पूर्णांकerface, पूर्णांक port)
अणु
	काष्ठा device_node *ni, *np;

	ni = cvm_oct_of_get_child(pip, पूर्णांकerface);
	अगर (!ni)
		वापस शून्य;

	np = cvm_oct_of_get_child(ni, port);
	of_node_put(ni);

	वापस np;
पूर्ण

अटल व्योम cvm_set_rgmii_delay(काष्ठा octeon_ethernet *priv, पूर्णांक अगरace,
				पूर्णांक port)
अणु
	काष्ठा device_node *np = priv->of_node;
	u32 delay_value;
	bool rx_delay;
	bool tx_delay;

	/* By शेष, both RX/TX delay is enabled in
	 * __cvmx_helper_rgmii_enable().
	 */
	rx_delay = true;
	tx_delay = true;

	अगर (!of_property_पढ़ो_u32(np, "rx-delay", &delay_value)) अणु
		cvmx_ग_लिखो_csr(CVMX_ASXX_RX_CLK_SETX(port, अगरace), delay_value);
		rx_delay = delay_value > 0;
	पूर्ण
	अगर (!of_property_पढ़ो_u32(np, "tx-delay", &delay_value)) अणु
		cvmx_ग_लिखो_csr(CVMX_ASXX_TX_CLK_SETX(port, अगरace), delay_value);
		tx_delay = delay_value > 0;
	पूर्ण

	अगर (!rx_delay && !tx_delay)
		priv->phy_mode = PHY_INTERFACE_MODE_RGMII_ID;
	अन्यथा अगर (!rx_delay)
		priv->phy_mode = PHY_INTERFACE_MODE_RGMII_RXID;
	अन्यथा अगर (!tx_delay)
		priv->phy_mode = PHY_INTERFACE_MODE_RGMII_TXID;
	अन्यथा
		priv->phy_mode = PHY_INTERFACE_MODE_RGMII;
पूर्ण

अटल पूर्णांक cvm_oct_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक num_पूर्णांकerfaces;
	पूर्णांक पूर्णांकerface;
	पूर्णांक fau = FAU_NUM_PACKET_BUFFERS_TO_FREE;
	पूर्णांक qos;
	काष्ठा device_node *pip;
	पूर्णांक mtu_overhead = ETH_HLEN + ETH_FCS_LEN;

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
	mtu_overhead += VLAN_HLEN;
#पूर्ण_अगर

	pip = pdev->dev.of_node;
	अगर (!pip) अणु
		pr_err("Error: No 'pip' in /aliases\n");
		वापस -EINVAL;
	पूर्ण

	cvm_oct_configure_common_hw();

	cvmx_helper_initialize_packet_io_global();

	अगर (receive_group_order) अणु
		अगर (receive_group_order > 4)
			receive_group_order = 4;
		घात_receive_groups = (1 << (1 << receive_group_order)) - 1;
	पूर्ण अन्यथा अणु
		घात_receive_groups = BIT(घात_receive_group);
	पूर्ण

	/* Change the input group क्रम all ports beक्रमe input is enabled */
	num_पूर्णांकerfaces = cvmx_helper_get_number_of_पूर्णांकerfaces();
	क्रम (पूर्णांकerface = 0; पूर्णांकerface < num_पूर्णांकerfaces; पूर्णांकerface++) अणु
		पूर्णांक num_ports = cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface);
		पूर्णांक port;

		क्रम (port = cvmx_helper_get_ipd_port(पूर्णांकerface, 0);
		     port < cvmx_helper_get_ipd_port(पूर्णांकerface, num_ports);
		     port++) अणु
			जोड़ cvmx_pip_prt_tagx pip_prt_tagx;

			pip_prt_tagx.u64 =
			    cvmx_पढ़ो_csr(CVMX_PIP_PRT_TAGX(port));

			अगर (receive_group_order) अणु
				पूर्णांक tag_mask;

				/* We support only 16 groups at the moment, so
				 * always disable the two additional "hidden"
				 * tag_mask bits on CN68XX.
				 */
				अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
					pip_prt_tagx.u64 |= 0x3ull << 44;

				tag_mask = ~((1 << receive_group_order) - 1);
				pip_prt_tagx.s.grptagbase	= 0;
				pip_prt_tagx.s.grptagmask	= tag_mask;
				pip_prt_tagx.s.grptag		= 1;
				pip_prt_tagx.s.tag_mode		= 0;
				pip_prt_tagx.s.inc_prt_flag	= 1;
				pip_prt_tagx.s.ip6_dprt_flag	= 1;
				pip_prt_tagx.s.ip4_dprt_flag	= 1;
				pip_prt_tagx.s.ip6_sprt_flag	= 1;
				pip_prt_tagx.s.ip4_sprt_flag	= 1;
				pip_prt_tagx.s.ip6_dst_flag	= 1;
				pip_prt_tagx.s.ip4_dst_flag	= 1;
				pip_prt_tagx.s.ip6_src_flag	= 1;
				pip_prt_tagx.s.ip4_src_flag	= 1;
				pip_prt_tagx.s.grp		= 0;
			पूर्ण अन्यथा अणु
				pip_prt_tagx.s.grptag	= 0;
				pip_prt_tagx.s.grp	= घात_receive_group;
			पूर्ण

			cvmx_ग_लिखो_csr(CVMX_PIP_PRT_TAGX(port),
				       pip_prt_tagx.u64);
		पूर्ण
	पूर्ण

	cvmx_helper_ipd_and_packet_input_enable();

	स_रखो(cvm_oct_device, 0, माप(cvm_oct_device));

	/*
	 * Initialize the FAU used क्रम counting packet buffers that
	 * need to be मुक्तd.
	 */
	cvmx_fau_atomic_ग_लिखो32(FAU_NUM_PACKET_BUFFERS_TO_FREE, 0);

	/* Initialize the FAU used क्रम counting tx SKBs that need to be मुक्तd */
	cvmx_fau_atomic_ग_लिखो32(FAU_TOTAL_TX_TO_CLEAN, 0);

	अगर ((घात_send_group != -1)) अणु
		काष्ठा net_device *dev;

		dev = alloc_etherdev(माप(काष्ठा octeon_ethernet));
		अगर (dev) अणु
			/* Initialize the device निजी काष्ठाure. */
			काष्ठा octeon_ethernet *priv = netdev_priv(dev);

			SET_NETDEV_DEV(dev, &pdev->dev);
			dev->netdev_ops = &cvm_oct_घात_netdev_ops;
			priv->imode = CVMX_HELPER_INTERFACE_MODE_DISABLED;
			priv->port = CVMX_PIP_NUM_INPUT_PORTS;
			priv->queue = -1;
			strscpy(dev->name, "pow%d", माप(dev->name));
			क्रम (qos = 0; qos < 16; qos++)
				skb_queue_head_init(&priv->tx_मुक्त_list[qos]);
			dev->min_mtu = VLAN_ETH_ZLEN - mtu_overhead;
			dev->max_mtu = OCTEON_MAX_MTU - mtu_overhead;

			अगर (रेजिस्टर_netdev(dev) < 0) अणु
				pr_err("Failed to register ethernet device for POW\n");
				मुक्त_netdev(dev);
			पूर्ण अन्यथा अणु
				cvm_oct_device[CVMX_PIP_NUM_INPUT_PORTS] = dev;
				pr_info("%s: POW send group %d, receive group %d\n",
					dev->name, घात_send_group,
					घात_receive_group);
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_err("Failed to allocate ethernet device for POW\n");
		पूर्ण
	पूर्ण

	num_पूर्णांकerfaces = cvmx_helper_get_number_of_पूर्णांकerfaces();
	क्रम (पूर्णांकerface = 0; पूर्णांकerface < num_पूर्णांकerfaces; पूर्णांकerface++) अणु
		cvmx_helper_पूर्णांकerface_mode_t imode =
		    cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface);
		पूर्णांक num_ports = cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface);
		पूर्णांक port;
		पूर्णांक port_index;

		क्रम (port_index = 0,
		     port = cvmx_helper_get_ipd_port(पूर्णांकerface, 0);
		     port < cvmx_helper_get_ipd_port(पूर्णांकerface, num_ports);
		     port_index++, port++) अणु
			काष्ठा octeon_ethernet *priv;
			काष्ठा net_device *dev =
			    alloc_etherdev(माप(काष्ठा octeon_ethernet));
			अगर (!dev) अणु
				pr_err("Failed to allocate ethernet device for port %d\n",
				       port);
				जारी;
			पूर्ण

			/* Initialize the device निजी काष्ठाure. */
			SET_NETDEV_DEV(dev, &pdev->dev);
			priv = netdev_priv(dev);
			priv->netdev = dev;
			priv->of_node = cvm_oct_node_क्रम_port(pip, पूर्णांकerface,
							      port_index);

			INIT_DELAYED_WORK(&priv->port_periodic_work,
					  cvm_oct_periodic_worker);
			priv->imode = imode;
			priv->port = port;
			priv->queue = cvmx_pko_get_base_queue(priv->port);
			priv->fau = fau - cvmx_pko_get_num_queues(port) * 4;
			priv->phy_mode = PHY_INTERFACE_MODE_NA;
			क्रम (qos = 0; qos < 16; qos++)
				skb_queue_head_init(&priv->tx_मुक्त_list[qos]);
			क्रम (qos = 0; qos < cvmx_pko_get_num_queues(port);
			     qos++)
				cvmx_fau_atomic_ग_लिखो32(priv->fau + qos * 4, 0);
			dev->min_mtu = VLAN_ETH_ZLEN - mtu_overhead;
			dev->max_mtu = OCTEON_MAX_MTU - mtu_overhead;

			चयन (priv->imode) अणु
			/* These types करोn't support ports to IPD/PKO */
			हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
			हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
			हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
				अवरोध;

			हाल CVMX_HELPER_INTERFACE_MODE_NPI:
				dev->netdev_ops = &cvm_oct_npi_netdev_ops;
				strscpy(dev->name, "npi%d", माप(dev->name));
				अवरोध;

			हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
				dev->netdev_ops = &cvm_oct_xaui_netdev_ops;
				strscpy(dev->name, "xaui%d", माप(dev->name));
				अवरोध;

			हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
				dev->netdev_ops = &cvm_oct_npi_netdev_ops;
				strscpy(dev->name, "loop%d", माप(dev->name));
				अवरोध;

			हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
				priv->phy_mode = PHY_INTERFACE_MODE_SGMII;
				dev->netdev_ops = &cvm_oct_sgmii_netdev_ops;
				strscpy(dev->name, "eth%d", माप(dev->name));
				अवरोध;

			हाल CVMX_HELPER_INTERFACE_MODE_SPI:
				dev->netdev_ops = &cvm_oct_spi_netdev_ops;
				strscpy(dev->name, "spi%d", माप(dev->name));
				अवरोध;

			हाल CVMX_HELPER_INTERFACE_MODE_GMII:
				priv->phy_mode = PHY_INTERFACE_MODE_GMII;
				dev->netdev_ops = &cvm_oct_rgmii_netdev_ops;
				strscpy(dev->name, "eth%d", माप(dev->name));
				अवरोध;

			हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
				dev->netdev_ops = &cvm_oct_rgmii_netdev_ops;
				strscpy(dev->name, "eth%d", माप(dev->name));
				cvm_set_rgmii_delay(priv, पूर्णांकerface,
						    port_index);
				अवरोध;
			पूर्ण

			अगर (priv->of_node && of_phy_is_fixed_link(priv->of_node)) अणु
				अगर (of_phy_रेजिस्टर_fixed_link(priv->of_node)) अणु
					netdev_err(dev, "Failed to register fixed link for interface %d, port %d\n",
						   पूर्णांकerface, priv->port);
					dev->netdev_ops = शून्य;
				पूर्ण
			पूर्ण

			अगर (!dev->netdev_ops) अणु
				मुक्त_netdev(dev);
			पूर्ण अन्यथा अगर (रेजिस्टर_netdev(dev) < 0) अणु
				pr_err("Failed to register ethernet device for interface %d, port %d\n",
				       पूर्णांकerface, priv->port);
				मुक्त_netdev(dev);
			पूर्ण अन्यथा अणु
				cvm_oct_device[priv->port] = dev;
				fau -=
				    cvmx_pko_get_num_queues(priv->port) *
				    माप(u32);
				schedule_delayed_work(&priv->port_periodic_work,
						      HZ);
			पूर्ण
		पूर्ण
	पूर्ण

	cvm_oct_tx_initialize();
	cvm_oct_rx_initialize();

	/*
	 * 150 uS: about 10 1500-byte packets at 1GE.
	 */
	cvm_oct_tx_poll_पूर्णांकerval = 150 * (octeon_get_घड़ी_rate() / 1000000);

	schedule_delayed_work(&cvm_oct_rx_refill_work, HZ);

	वापस 0;
पूर्ण

अटल पूर्णांक cvm_oct_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक port;

	cvmx_ipd_disable();

	atomic_inc_वापस(&cvm_oct_poll_queue_stopping);
	cancel_delayed_work_sync(&cvm_oct_rx_refill_work);

	cvm_oct_rx_shutकरोwn();
	cvm_oct_tx_shutकरोwn();

	cvmx_pko_disable();

	/* Free the ethernet devices */
	क्रम (port = 0; port < TOTAL_NUMBER_OF_PORTS; port++) अणु
		अगर (cvm_oct_device[port]) अणु
			काष्ठा net_device *dev = cvm_oct_device[port];
			काष्ठा octeon_ethernet *priv = netdev_priv(dev);

			cancel_delayed_work_sync(&priv->port_periodic_work);

			cvm_oct_tx_shutकरोwn_dev(dev);
			unरेजिस्टर_netdev(dev);
			मुक्त_netdev(dev);
			cvm_oct_device[port] = शून्य;
		पूर्ण
	पूर्ण

	cvmx_pko_shutकरोwn();

	cvmx_ipd_मुक्त_ptr();

	/* Free the HW pools */
	cvm_oct_mem_empty_fpa(CVMX_FPA_PACKET_POOL, CVMX_FPA_PACKET_POOL_SIZE,
			      num_packet_buffers);
	cvm_oct_mem_empty_fpa(CVMX_FPA_WQE_POOL, CVMX_FPA_WQE_POOL_SIZE,
			      num_packet_buffers);
	अगर (CVMX_FPA_OUTPUT_BUFFER_POOL != CVMX_FPA_PACKET_POOL)
		cvm_oct_mem_empty_fpa(CVMX_FPA_OUTPUT_BUFFER_POOL,
				      CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE, 128);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cvm_oct_match[] = अणु
	अणु
		.compatible = "cavium,octeon-3860-pip",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cvm_oct_match);

अटल काष्ठा platक्रमm_driver cvm_oct_driver = अणु
	.probe		= cvm_oct_probe,
	.हटाओ		= cvm_oct_हटाओ,
	.driver		= अणु
		.name	= KBUILD_MODNAME,
		.of_match_table = cvm_oct_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cvm_oct_driver);

MODULE_SOFTDEP("pre: mdio-cavium");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cavium Networks <support@caviumnetworks.com>");
MODULE_DESCRIPTION("Cavium Networks Octeon ethernet driver.");
