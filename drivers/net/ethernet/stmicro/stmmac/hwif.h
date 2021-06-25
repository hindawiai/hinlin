<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
// Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
// sपंचांगmac HW Interface Callbacks

#अगर_अघोषित __STMMAC_HWIF_H__
#घोषणा __STMMAC_HWIF_H__

#समावेश <linux/netdevice.h>
#समावेश <linux/sपंचांगmac.h>

#घोषणा sपंचांगmac_करो_व्योम_callback(__priv, __module, __cname,  __arg0, __args...) \
(अणु \
	पूर्णांक __result = -EINVAL; \
	अगर ((__priv)->hw->__module && (__priv)->hw->__module->__cname) अणु \
		(__priv)->hw->__module->__cname((__arg0), ##__args); \
		__result = 0; \
	पूर्ण \
	__result; \
पूर्ण)
#घोषणा sपंचांगmac_करो_callback(__priv, __module, __cname,  __arg0, __args...) \
(अणु \
	पूर्णांक __result = -EINVAL; \
	अगर ((__priv)->hw->__module && (__priv)->hw->__module->__cname) \
		__result = (__priv)->hw->__module->__cname((__arg0), ##__args); \
	__result; \
पूर्ण)

काष्ठा sपंचांगmac_extra_stats;
काष्ठा sपंचांगmac_safety_stats;
काष्ठा dma_desc;
काष्ठा dma_extended_desc;
काष्ठा dma_edesc;

/* Descriptors helpers */
काष्ठा sपंचांगmac_desc_ops अणु
	/* DMA RX descriptor ring initialization */
	व्योम (*init_rx_desc)(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic, पूर्णांक mode,
			पूर्णांक end, पूर्णांक bfsize);
	/* DMA TX descriptor ring initialization */
	व्योम (*init_tx_desc)(काष्ठा dma_desc *p, पूर्णांक mode, पूर्णांक end);
	/* Invoked by the xmit function to prepare the tx descriptor */
	व्योम (*prepare_tx_desc)(काष्ठा dma_desc *p, पूर्णांक is_fs, पूर्णांक len,
			bool csum_flag, पूर्णांक mode, bool tx_own, bool ls,
			अचिन्हित पूर्णांक tot_pkt_len);
	व्योम (*prepare_tso_tx_desc)(काष्ठा dma_desc *p, पूर्णांक is_fs, पूर्णांक len1,
			पूर्णांक len2, bool tx_own, bool ls, अचिन्हित पूर्णांक tcphdrlen,
			अचिन्हित पूर्णांक tcppayloadlen);
	/* Set/get the owner of the descriptor */
	व्योम (*set_tx_owner)(काष्ठा dma_desc *p);
	पूर्णांक (*get_tx_owner)(काष्ठा dma_desc *p);
	/* Clean the tx descriptor as soon as the tx irq is received */
	व्योम (*release_tx_desc)(काष्ठा dma_desc *p, पूर्णांक mode);
	/* Clear पूर्णांकerrupt on tx frame completion. When this bit is
	 * set an पूर्णांकerrupt happens as soon as the frame is transmitted */
	व्योम (*set_tx_ic)(काष्ठा dma_desc *p);
	/* Last tx segment reports the transmit status */
	पूर्णांक (*get_tx_ls)(काष्ठा dma_desc *p);
	/* Return the transmit status looking at the TDES1 */
	पूर्णांक (*tx_status)(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
			काष्ठा dma_desc *p, व्योम __iomem *ioaddr);
	/* Get the buffer size from the descriptor */
	पूर्णांक (*get_tx_len)(काष्ठा dma_desc *p);
	/* Handle extra events on specअगरic पूर्णांकerrupts hw dependent */
	व्योम (*set_rx_owner)(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic);
	/* Get the receive frame size */
	पूर्णांक (*get_rx_frame_len)(काष्ठा dma_desc *p, पूर्णांक rx_coe_type);
	/* Return the reception status looking at the RDES1 */
	पूर्णांक (*rx_status)(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
			काष्ठा dma_desc *p);
	व्योम (*rx_extended_status)(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
			काष्ठा dma_extended_desc *p);
	/* Set tx बारtamp enable bit */
	व्योम (*enable_tx_बारtamp) (काष्ठा dma_desc *p);
	/* get tx बारtamp status */
	पूर्णांक (*get_tx_बारtamp_status) (काष्ठा dma_desc *p);
	/* get बारtamp value */
	व्योम (*get_बारtamp)(व्योम *desc, u32 ats, u64 *ts);
	/* get rx बारtamp status */
	पूर्णांक (*get_rx_बारtamp_status)(व्योम *desc, व्योम *next_desc, u32 ats);
	/* Display ring */
	व्योम (*display_ring)(व्योम *head, अचिन्हित पूर्णांक size, bool rx,
			     dma_addr_t dma_rx_phy, अचिन्हित पूर्णांक desc_size);
	/* set MSS via context descriptor */
	व्योम (*set_mss)(काष्ठा dma_desc *p, अचिन्हित पूर्णांक mss);
	/* get descriptor skbuff address */
	व्योम (*get_addr)(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *addr);
	/* set descriptor skbuff address */
	व्योम (*set_addr)(काष्ठा dma_desc *p, dma_addr_t addr);
	/* clear descriptor */
	व्योम (*clear)(काष्ठा dma_desc *p);
	/* RSS */
	पूर्णांक (*get_rx_hash)(काष्ठा dma_desc *p, u32 *hash,
			   क्रमागत pkt_hash_types *type);
	व्योम (*get_rx_header_len)(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *len);
	व्योम (*set_sec_addr)(काष्ठा dma_desc *p, dma_addr_t addr, bool buf2_valid);
	व्योम (*set_sarc)(काष्ठा dma_desc *p, u32 sarc_type);
	व्योम (*set_vlan_tag)(काष्ठा dma_desc *p, u16 tag, u16 inner_tag,
			     u32 inner_type);
	व्योम (*set_vlan)(काष्ठा dma_desc *p, u32 type);
	व्योम (*set_tbs)(काष्ठा dma_edesc *p, u32 sec, u32 nsec);
पूर्ण;

#घोषणा sपंचांगmac_init_rx_desc(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, init_rx_desc, __args)
#घोषणा sपंचांगmac_init_tx_desc(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, init_tx_desc, __args)
#घोषणा sपंचांगmac_prepare_tx_desc(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, prepare_tx_desc, __args)
#घोषणा sपंचांगmac_prepare_tso_tx_desc(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, prepare_tso_tx_desc, __args)
#घोषणा sपंचांगmac_set_tx_owner(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_tx_owner, __args)
#घोषणा sपंचांगmac_get_tx_owner(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, get_tx_owner, __args)
#घोषणा sपंचांगmac_release_tx_desc(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, release_tx_desc, __args)
#घोषणा sपंचांगmac_set_tx_ic(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_tx_ic, __args)
#घोषणा sपंचांगmac_get_tx_ls(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, get_tx_ls, __args)
#घोषणा sपंचांगmac_tx_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, tx_status, __args)
#घोषणा sपंचांगmac_get_tx_len(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, get_tx_len, __args)
#घोषणा sपंचांगmac_set_rx_owner(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_rx_owner, __args)
#घोषणा sपंचांगmac_get_rx_frame_len(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, get_rx_frame_len, __args)
#घोषणा sपंचांगmac_rx_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, rx_status, __args)
#घोषणा sपंचांगmac_rx_extended_status(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, rx_extended_status, __args)
#घोषणा sपंचांगmac_enable_tx_बारtamp(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, enable_tx_बारtamp, __args)
#घोषणा sपंचांगmac_get_tx_बारtamp_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, get_tx_बारtamp_status, __args)
#घोषणा sपंचांगmac_get_बारtamp(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, get_बारtamp, __args)
#घोषणा sपंचांगmac_get_rx_बारtamp_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, get_rx_बारtamp_status, __args)
#घोषणा sपंचांगmac_display_ring(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, display_ring, __args)
#घोषणा sपंचांगmac_set_mss(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_mss, __args)
#घोषणा sपंचांगmac_get_desc_addr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, get_addr, __args)
#घोषणा sपंचांगmac_set_desc_addr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_addr, __args)
#घोषणा sपंचांगmac_clear_desc(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, clear, __args)
#घोषणा sपंचांगmac_get_rx_hash(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, desc, get_rx_hash, __args)
#घोषणा sपंचांगmac_get_rx_header_len(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, get_rx_header_len, __args)
#घोषणा sपंचांगmac_set_desc_sec_addr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_sec_addr, __args)
#घोषणा sपंचांगmac_set_desc_sarc(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_sarc, __args)
#घोषणा sपंचांगmac_set_desc_vlan_tag(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_vlan_tag, __args)
#घोषणा sपंचांगmac_set_desc_vlan(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_vlan, __args)
#घोषणा sपंचांगmac_set_desc_tbs(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, desc, set_tbs, __args)

काष्ठा sपंचांगmac_dma_cfg;
काष्ठा dma_features;

/* Specअगरic DMA helpers */
काष्ठा sपंचांगmac_dma_ops अणु
	/* DMA core initialization */
	पूर्णांक (*reset)(व्योम __iomem *ioaddr);
	व्योम (*init)(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
		     पूर्णांक atds);
	व्योम (*init_chan)(व्योम __iomem *ioaddr,
			  काष्ठा sपंचांगmac_dma_cfg *dma_cfg, u32 chan);
	व्योम (*init_rx_chan)(व्योम __iomem *ioaddr,
			     काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
			     dma_addr_t phy, u32 chan);
	व्योम (*init_tx_chan)(व्योम __iomem *ioaddr,
			     काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
			     dma_addr_t phy, u32 chan);
	/* Configure the AXI Bus Mode Register */
	व्योम (*axi)(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_axi *axi);
	/* Dump DMA रेजिस्टरs */
	व्योम (*dump_regs)(व्योम __iomem *ioaddr, u32 *reg_space);
	व्योम (*dma_rx_mode)(व्योम __iomem *ioaddr, पूर्णांक mode, u32 channel,
			    पूर्णांक fअगरosz, u8 qmode);
	व्योम (*dma_tx_mode)(व्योम __iomem *ioaddr, पूर्णांक mode, u32 channel,
			    पूर्णांक fअगरosz, u8 qmode);
	/* To track extra statistic (अगर supported) */
	व्योम (*dma_diagnostic_fr) (व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				   व्योम __iomem *ioaddr);
	व्योम (*enable_dma_transmission) (व्योम __iomem *ioaddr);
	व्योम (*enable_dma_irq)(व्योम __iomem *ioaddr, u32 chan,
			       bool rx, bool tx);
	व्योम (*disable_dma_irq)(व्योम __iomem *ioaddr, u32 chan,
				bool rx, bool tx);
	व्योम (*start_tx)(व्योम __iomem *ioaddr, u32 chan);
	व्योम (*stop_tx)(व्योम __iomem *ioaddr, u32 chan);
	व्योम (*start_rx)(व्योम __iomem *ioaddr, u32 chan);
	व्योम (*stop_rx)(व्योम __iomem *ioaddr, u32 chan);
	पूर्णांक (*dma_पूर्णांकerrupt) (व्योम __iomem *ioaddr,
			      काष्ठा sपंचांगmac_extra_stats *x, u32 chan, u32 dir);
	/* If supported then get the optional core features */
	व्योम (*get_hw_feature)(व्योम __iomem *ioaddr,
			       काष्ठा dma_features *dma_cap);
	/* Program the HW RX Watchकरोg */
	व्योम (*rx_watchकरोg)(व्योम __iomem *ioaddr, u32 riwt, u32 queue);
	व्योम (*set_tx_ring_len)(व्योम __iomem *ioaddr, u32 len, u32 chan);
	व्योम (*set_rx_ring_len)(व्योम __iomem *ioaddr, u32 len, u32 chan);
	व्योम (*set_rx_tail_ptr)(व्योम __iomem *ioaddr, u32 tail_ptr, u32 chan);
	व्योम (*set_tx_tail_ptr)(व्योम __iomem *ioaddr, u32 tail_ptr, u32 chan);
	व्योम (*enable_tso)(व्योम __iomem *ioaddr, bool en, u32 chan);
	व्योम (*qmode)(व्योम __iomem *ioaddr, u32 channel, u8 qmode);
	व्योम (*set_bfsize)(व्योम __iomem *ioaddr, पूर्णांक bfsize, u32 chan);
	व्योम (*enable_sph)(व्योम __iomem *ioaddr, bool en, u32 chan);
	पूर्णांक (*enable_tbs)(व्योम __iomem *ioaddr, bool en, u32 chan);
पूर्ण;

#घोषणा sपंचांगmac_reset(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, dma, reset, __args)
#घोषणा sपंचांगmac_dma_init(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, init, __args)
#घोषणा sपंचांगmac_init_chan(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, init_chan, __args)
#घोषणा sपंचांगmac_init_rx_chan(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, init_rx_chan, __args)
#घोषणा sपंचांगmac_init_tx_chan(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, init_tx_chan, __args)
#घोषणा sपंचांगmac_axi(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, axi, __args)
#घोषणा sपंचांगmac_dump_dma_regs(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, dump_regs, __args)
#घोषणा sपंचांगmac_dma_rx_mode(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, dma_rx_mode, __args)
#घोषणा sपंचांगmac_dma_tx_mode(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, dma_tx_mode, __args)
#घोषणा sपंचांगmac_dma_diagnostic_fr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, dma_diagnostic_fr, __args)
#घोषणा sपंचांगmac_enable_dma_transmission(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, enable_dma_transmission, __args)
#घोषणा sपंचांगmac_enable_dma_irq(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, enable_dma_irq, __args)
#घोषणा sपंचांगmac_disable_dma_irq(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, disable_dma_irq, __args)
#घोषणा sपंचांगmac_start_tx(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, start_tx, __args)
#घोषणा sपंचांगmac_stop_tx(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, stop_tx, __args)
#घोषणा sपंचांगmac_start_rx(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, start_rx, __args)
#घोषणा sपंचांगmac_stop_rx(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, stop_rx, __args)
#घोषणा sपंचांगmac_dma_पूर्णांकerrupt_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, dma, dma_पूर्णांकerrupt, __args)
#घोषणा sपंचांगmac_get_hw_feature(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, get_hw_feature, __args)
#घोषणा sपंचांगmac_rx_watchकरोg(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, rx_watchकरोg, __args)
#घोषणा sपंचांगmac_set_tx_ring_len(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, set_tx_ring_len, __args)
#घोषणा sपंचांगmac_set_rx_ring_len(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, set_rx_ring_len, __args)
#घोषणा sपंचांगmac_set_rx_tail_ptr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, set_rx_tail_ptr, __args)
#घोषणा sपंचांगmac_set_tx_tail_ptr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, set_tx_tail_ptr, __args)
#घोषणा sपंचांगmac_enable_tso(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, enable_tso, __args)
#घोषणा sपंचांगmac_dma_qmode(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, qmode, __args)
#घोषणा sपंचांगmac_set_dma_bfsize(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, set_bfsize, __args)
#घोषणा sपंचांगmac_enable_sph(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, dma, enable_sph, __args)
#घोषणा sपंचांगmac_enable_tbs(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, dma, enable_tbs, __args)

काष्ठा mac_device_info;
काष्ठा net_device;
काष्ठा rgmii_adv;
काष्ठा sपंचांगmac_tc_entry;
काष्ठा sपंचांगmac_pps_cfg;
काष्ठा sपंचांगmac_rss;
काष्ठा sपंचांगmac_est;

/* Helpers to program the MAC core */
काष्ठा sपंचांगmac_ops अणु
	/* MAC core initialization */
	व्योम (*core_init)(काष्ठा mac_device_info *hw, काष्ठा net_device *dev);
	/* Enable the MAC RX/TX */
	व्योम (*set_mac)(व्योम __iomem *ioaddr, bool enable);
	/* Enable and verअगरy that the IPC module is supported */
	पूर्णांक (*rx_ipc)(काष्ठा mac_device_info *hw);
	/* Enable RX Queues */
	व्योम (*rx_queue_enable)(काष्ठा mac_device_info *hw, u8 mode, u32 queue);
	/* RX Queues Priority */
	व्योम (*rx_queue_prio)(काष्ठा mac_device_info *hw, u32 prio, u32 queue);
	/* TX Queues Priority */
	व्योम (*tx_queue_prio)(काष्ठा mac_device_info *hw, u32 prio, u32 queue);
	/* RX Queues Routing */
	व्योम (*rx_queue_routing)(काष्ठा mac_device_info *hw, u8 packet,
				 u32 queue);
	/* Program RX Algorithms */
	व्योम (*prog_mtl_rx_algorithms)(काष्ठा mac_device_info *hw, u32 rx_alg);
	/* Program TX Algorithms */
	व्योम (*prog_mtl_tx_algorithms)(काष्ठा mac_device_info *hw, u32 tx_alg);
	/* Set MTL TX queues weight */
	व्योम (*set_mtl_tx_queue_weight)(काष्ठा mac_device_info *hw,
					u32 weight, u32 queue);
	/* RX MTL queue to RX dma mapping */
	व्योम (*map_mtl_to_dma)(काष्ठा mac_device_info *hw, u32 queue, u32 chan);
	/* Configure AV Algorithm */
	व्योम (*config_cbs)(काष्ठा mac_device_info *hw, u32 send_slope,
			   u32 idle_slope, u32 high_credit, u32 low_credit,
			   u32 queue);
	/* Dump MAC रेजिस्टरs */
	व्योम (*dump_regs)(काष्ठा mac_device_info *hw, u32 *reg_space);
	/* Handle extra events on specअगरic पूर्णांकerrupts hw dependent */
	पूर्णांक (*host_irq_status)(काष्ठा mac_device_info *hw,
			       काष्ठा sपंचांगmac_extra_stats *x);
	/* Handle MTL पूर्णांकerrupts */
	पूर्णांक (*host_mtl_irq_status)(काष्ठा mac_device_info *hw, u32 chan);
	/* Multicast filter setting */
	व्योम (*set_filter)(काष्ठा mac_device_info *hw, काष्ठा net_device *dev);
	/* Flow control setting */
	व्योम (*flow_ctrl)(काष्ठा mac_device_info *hw, अचिन्हित पूर्णांक duplex,
			  अचिन्हित पूर्णांक fc, अचिन्हित पूर्णांक छोड़ो_समय, u32 tx_cnt);
	/* Set घातer management mode (e.g. magic frame) */
	व्योम (*pmt)(काष्ठा mac_device_info *hw, अचिन्हित दीर्घ mode);
	/* Set/Get Unicast MAC addresses */
	व्योम (*set_umac_addr)(काष्ठा mac_device_info *hw, अचिन्हित अक्षर *addr,
			      अचिन्हित पूर्णांक reg_n);
	व्योम (*get_umac_addr)(काष्ठा mac_device_info *hw, अचिन्हित अक्षर *addr,
			      अचिन्हित पूर्णांक reg_n);
	व्योम (*set_eee_mode)(काष्ठा mac_device_info *hw,
			     bool en_tx_lpi_घड़ीgating);
	व्योम (*reset_eee_mode)(काष्ठा mac_device_info *hw);
	व्योम (*set_eee_lpi_entry_समयr)(काष्ठा mac_device_info *hw, पूर्णांक et);
	व्योम (*set_eee_समयr)(काष्ठा mac_device_info *hw, पूर्णांक ls, पूर्णांक tw);
	व्योम (*set_eee_pls)(काष्ठा mac_device_info *hw, पूर्णांक link);
	व्योम (*debug)(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_extra_stats *x,
		      u32 rx_queues, u32 tx_queues);
	/* PCS calls */
	व्योम (*pcs_ctrl_ane)(व्योम __iomem *ioaddr, bool ane, bool srgmi_ral,
			     bool loopback);
	व्योम (*pcs_rane)(व्योम __iomem *ioaddr, bool restart);
	व्योम (*pcs_get_adv_lp)(व्योम __iomem *ioaddr, काष्ठा rgmii_adv *adv);
	/* Safety Features */
	पूर्णांक (*safety_feat_config)(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक asp);
	पूर्णांक (*safety_feat_irq_status)(काष्ठा net_device *ndev,
			व्योम __iomem *ioaddr, अचिन्हित पूर्णांक asp,
			काष्ठा sपंचांगmac_safety_stats *stats);
	पूर्णांक (*safety_feat_dump)(काष्ठा sपंचांगmac_safety_stats *stats,
			पूर्णांक index, अचिन्हित दीर्घ *count, स्थिर अक्षर **desc);
	/* Flexible RX Parser */
	पूर्णांक (*rxp_config)(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_tc_entry *entries,
			  अचिन्हित पूर्णांक count);
	/* Flexible PPS */
	पूर्णांक (*flex_pps_config)(व्योम __iomem *ioaddr, पूर्णांक index,
			       काष्ठा sपंचांगmac_pps_cfg *cfg, bool enable,
			       u32 sub_second_inc, u32 sysसमय_flags);
	/* Loopback क्रम selftests */
	व्योम (*set_mac_loopback)(व्योम __iomem *ioaddr, bool enable);
	/* RSS */
	पूर्णांक (*rss_configure)(काष्ठा mac_device_info *hw,
			     काष्ठा sपंचांगmac_rss *cfg, u32 num_rxq);
	/* VLAN */
	व्योम (*update_vlan_hash)(काष्ठा mac_device_info *hw, u32 hash,
				 __le16 perfect_match, bool is_द्विगुन);
	व्योम (*enable_vlan)(काष्ठा mac_device_info *hw, u32 type);
	पूर्णांक (*add_hw_vlan_rx_fltr)(काष्ठा net_device *dev,
				   काष्ठा mac_device_info *hw,
				   __be16 proto, u16 vid);
	पूर्णांक (*del_hw_vlan_rx_fltr)(काष्ठा net_device *dev,
				   काष्ठा mac_device_info *hw,
				   __be16 proto, u16 vid);
	व्योम (*restore_hw_vlan_rx_fltr)(काष्ठा net_device *dev,
					काष्ठा mac_device_info *hw);
	/* TX Timestamp */
	पूर्णांक (*get_mac_tx_बारtamp)(काष्ठा mac_device_info *hw, u64 *ts);
	/* Source Address Insertion / Replacement */
	व्योम (*sarc_configure)(व्योम __iomem *ioaddr, पूर्णांक val);
	/* Filtering */
	पूर्णांक (*config_l3_filter)(काष्ठा mac_device_info *hw, u32 filter_no,
				bool en, bool ipv6, bool sa, bool inv,
				u32 match);
	पूर्णांक (*config_l4_filter)(काष्ठा mac_device_info *hw, u32 filter_no,
				bool en, bool udp, bool sa, bool inv,
				u32 match);
	व्योम (*set_arp_offload)(काष्ठा mac_device_info *hw, bool en, u32 addr);
	पूर्णांक (*est_configure)(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_est *cfg,
			     अचिन्हित पूर्णांक ptp_rate);
	व्योम (*est_irq_status)(व्योम __iomem *ioaddr, काष्ठा net_device *dev,
			       काष्ठा sपंचांगmac_extra_stats *x, u32 txqcnt);
	व्योम (*fpe_configure)(व्योम __iomem *ioaddr, u32 num_txq, u32 num_rxq,
			      bool enable);
	व्योम (*fpe_send_mpacket)(व्योम __iomem *ioaddr,
				 क्रमागत sपंचांगmac_mpacket_type type);
	पूर्णांक (*fpe_irq_status)(व्योम __iomem *ioaddr, काष्ठा net_device *dev);
पूर्ण;

#घोषणा sपंचांगmac_core_init(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, core_init, __args)
#घोषणा sपंचांगmac_mac_set(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_mac, __args)
#घोषणा sपंचांगmac_rx_ipc(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, rx_ipc, __args)
#घोषणा sपंचांगmac_rx_queue_enable(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, rx_queue_enable, __args)
#घोषणा sपंचांगmac_rx_queue_prio(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, rx_queue_prio, __args)
#घोषणा sपंचांगmac_tx_queue_prio(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, tx_queue_prio, __args)
#घोषणा sपंचांगmac_rx_queue_routing(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, rx_queue_routing, __args)
#घोषणा sपंचांगmac_prog_mtl_rx_algorithms(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, prog_mtl_rx_algorithms, __args)
#घोषणा sपंचांगmac_prog_mtl_tx_algorithms(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, prog_mtl_tx_algorithms, __args)
#घोषणा sपंचांगmac_set_mtl_tx_queue_weight(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_mtl_tx_queue_weight, __args)
#घोषणा sपंचांगmac_map_mtl_to_dma(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, map_mtl_to_dma, __args)
#घोषणा sपंचांगmac_config_cbs(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, config_cbs, __args)
#घोषणा sपंचांगmac_dump_mac_regs(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, dump_regs, __args)
#घोषणा sपंचांगmac_host_irq_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, host_irq_status, __args)
#घोषणा sपंचांगmac_host_mtl_irq_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, host_mtl_irq_status, __args)
#घोषणा sपंचांगmac_set_filter(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_filter, __args)
#घोषणा sपंचांगmac_flow_ctrl(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, flow_ctrl, __args)
#घोषणा sपंचांगmac_pmt(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, pmt, __args)
#घोषणा sपंचांगmac_set_umac_addr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_umac_addr, __args)
#घोषणा sपंचांगmac_get_umac_addr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, get_umac_addr, __args)
#घोषणा sपंचांगmac_set_eee_mode(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_eee_mode, __args)
#घोषणा sपंचांगmac_reset_eee_mode(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, reset_eee_mode, __args)
#घोषणा sपंचांगmac_set_eee_lpi_समयr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_eee_lpi_entry_समयr, __args)
#घोषणा sपंचांगmac_set_eee_समयr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_eee_समयr, __args)
#घोषणा sपंचांगmac_set_eee_pls(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_eee_pls, __args)
#घोषणा sपंचांगmac_mac_debug(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, debug, __args)
#घोषणा sपंचांगmac_pcs_ctrl_ane(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, pcs_ctrl_ane, __args)
#घोषणा sपंचांगmac_pcs_rane(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, pcs_rane, __args)
#घोषणा sपंचांगmac_pcs_get_adv_lp(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, pcs_get_adv_lp, __args)
#घोषणा sपंचांगmac_safety_feat_config(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, safety_feat_config, __args)
#घोषणा sपंचांगmac_safety_feat_irq_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, safety_feat_irq_status, __args)
#घोषणा sपंचांगmac_safety_feat_dump(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, safety_feat_dump, __args)
#घोषणा sपंचांगmac_rxp_config(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, rxp_config, __args)
#घोषणा sपंचांगmac_flex_pps_config(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, flex_pps_config, __args)
#घोषणा sपंचांगmac_set_mac_loopback(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_mac_loopback, __args)
#घोषणा sपंचांगmac_rss_configure(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, rss_configure, __args)
#घोषणा sपंचांगmac_update_vlan_hash(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, update_vlan_hash, __args)
#घोषणा sपंचांगmac_enable_vlan(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, enable_vlan, __args)
#घोषणा sपंचांगmac_add_hw_vlan_rx_fltr(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, add_hw_vlan_rx_fltr, __args)
#घोषणा sपंचांगmac_del_hw_vlan_rx_fltr(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, del_hw_vlan_rx_fltr, __args)
#घोषणा sपंचांगmac_restore_hw_vlan_rx_fltr(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, restore_hw_vlan_rx_fltr, __args)
#घोषणा sपंचांगmac_get_mac_tx_बारtamp(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, get_mac_tx_बारtamp, __args)
#घोषणा sपंचांगmac_sarc_configure(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, sarc_configure, __args)
#घोषणा sपंचांगmac_config_l3_filter(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, config_l3_filter, __args)
#घोषणा sपंचांगmac_config_l4_filter(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, config_l4_filter, __args)
#घोषणा sपंचांगmac_set_arp_offload(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, set_arp_offload, __args)
#घोषणा sपंचांगmac_est_configure(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, est_configure, __args)
#घोषणा sपंचांगmac_est_irq_status(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, est_irq_status, __args)
#घोषणा sपंचांगmac_fpe_configure(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, fpe_configure, __args)
#घोषणा sपंचांगmac_fpe_send_mpacket(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mac, fpe_send_mpacket, __args)
#घोषणा sपंचांगmac_fpe_irq_status(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mac, fpe_irq_status, __args)

काष्ठा sपंचांगmac_priv;

/* PTP and HW Timer helpers */
काष्ठा sपंचांगmac_hwबारtamp अणु
	व्योम (*config_hw_tstamping) (व्योम __iomem *ioaddr, u32 data);
	व्योम (*config_sub_second_increment)(व्योम __iomem *ioaddr, u32 ptp_घड़ी,
					   पूर्णांक gmac4, u32 *ssinc);
	पूर्णांक (*init_sysसमय) (व्योम __iomem *ioaddr, u32 sec, u32 nsec);
	पूर्णांक (*config_addend) (व्योम __iomem *ioaddr, u32 addend);
	पूर्णांक (*adjust_sysसमय) (व्योम __iomem *ioaddr, u32 sec, u32 nsec,
			       पूर्णांक add_sub, पूर्णांक gmac4);
	व्योम (*get_sysसमय) (व्योम __iomem *ioaddr, u64 *sysसमय);
	व्योम (*get_ptpसमय)(व्योम __iomem *ioaddr, u64 *ptp_समय);
	व्योम (*बारtamp_पूर्णांकerrupt)(काष्ठा sपंचांगmac_priv *priv);
पूर्ण;

#घोषणा sपंचांगmac_config_hw_tstamping(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, ptp, config_hw_tstamping, __args)
#घोषणा sपंचांगmac_config_sub_second_increment(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, ptp, config_sub_second_increment, __args)
#घोषणा sपंचांगmac_init_sysसमय(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, ptp, init_sysसमय, __args)
#घोषणा sपंचांगmac_config_addend(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, ptp, config_addend, __args)
#घोषणा sपंचांगmac_adjust_sysसमय(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, ptp, adjust_sysसमय, __args)
#घोषणा sपंचांगmac_get_sysसमय(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, ptp, get_sysसमय, __args)
#घोषणा sपंचांगmac_get_ptpसमय(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, ptp, get_ptpसमय, __args)
#घोषणा sपंचांगmac_बारtamp_पूर्णांकerrupt(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, ptp, बारtamp_पूर्णांकerrupt, __args)

/* Helpers to manage the descriptors क्रम chain and ring modes */
काष्ठा sपंचांगmac_mode_ops अणु
	व्योम (*init) (व्योम *des, dma_addr_t phy_addr, अचिन्हित पूर्णांक size,
		      अचिन्हित पूर्णांक extend_desc);
	अचिन्हित पूर्णांक (*is_jumbo_frm) (पूर्णांक len, पूर्णांक ehn_desc);
	पूर्णांक (*jumbo_frm)(व्योम *priv, काष्ठा sk_buff *skb, पूर्णांक csum);
	पूर्णांक (*set_16kib_bfsize)(पूर्णांक mtu);
	व्योम (*init_desc3)(काष्ठा dma_desc *p);
	व्योम (*refill_desc3) (व्योम *priv, काष्ठा dma_desc *p);
	व्योम (*clean_desc3) (व्योम *priv, काष्ठा dma_desc *p);
पूर्ण;

#घोषणा sपंचांगmac_mode_init(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mode, init, __args)
#घोषणा sपंचांगmac_is_jumbo_frm(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mode, is_jumbo_frm, __args)
#घोषणा sपंचांगmac_jumbo_frm(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mode, jumbo_frm, __args)
#घोषणा sपंचांगmac_set_16kib_bfsize(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, mode, set_16kib_bfsize, __args)
#घोषणा sपंचांगmac_init_desc3(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mode, init_desc3, __args)
#घोषणा sपंचांगmac_refill_desc3(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mode, refill_desc3, __args)
#घोषणा sपंचांगmac_clean_desc3(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mode, clean_desc3, __args)

काष्ठा tc_cls_u32_offload;
काष्ठा tc_cbs_qopt_offload;
काष्ठा flow_cls_offload;
काष्ठा tc_taprio_qopt_offload;
काष्ठा tc_etf_qopt_offload;

काष्ठा sपंचांगmac_tc_ops अणु
	पूर्णांक (*init)(काष्ठा sपंचांगmac_priv *priv);
	पूर्णांक (*setup_cls_u32)(काष्ठा sपंचांगmac_priv *priv,
			     काष्ठा tc_cls_u32_offload *cls);
	पूर्णांक (*setup_cbs)(काष्ठा sपंचांगmac_priv *priv,
			 काष्ठा tc_cbs_qopt_offload *qopt);
	पूर्णांक (*setup_cls)(काष्ठा sपंचांगmac_priv *priv,
			 काष्ठा flow_cls_offload *cls);
	पूर्णांक (*setup_taprio)(काष्ठा sपंचांगmac_priv *priv,
			    काष्ठा tc_taprio_qopt_offload *qopt);
	पूर्णांक (*setup_etf)(काष्ठा sपंचांगmac_priv *priv,
			 काष्ठा tc_etf_qopt_offload *qopt);
पूर्ण;

#घोषणा sपंचांगmac_tc_init(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, tc, init, __args)
#घोषणा sपंचांगmac_tc_setup_cls_u32(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, tc, setup_cls_u32, __args)
#घोषणा sपंचांगmac_tc_setup_cbs(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, tc, setup_cbs, __args)
#घोषणा sपंचांगmac_tc_setup_cls(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, tc, setup_cls, __args)
#घोषणा sपंचांगmac_tc_setup_taprio(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, tc, setup_taprio, __args)
#घोषणा sपंचांगmac_tc_setup_etf(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, tc, setup_etf, __args)

काष्ठा sपंचांगmac_counters;

काष्ठा sपंचांगmac_mmc_ops अणु
	व्योम (*ctrl)(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक mode);
	व्योम (*पूर्णांकr_all_mask)(व्योम __iomem *ioaddr);
	व्योम (*पढ़ो)(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_counters *mmc);
पूर्ण;

#घोषणा sपंचांगmac_mmc_ctrl(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mmc, ctrl, __args)
#घोषणा sपंचांगmac_mmc_पूर्णांकr_all_mask(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mmc, पूर्णांकr_all_mask, __args)
#घोषणा sपंचांगmac_mmc_पढ़ो(__priv, __args...) \
	sपंचांगmac_करो_व्योम_callback(__priv, mmc, पढ़ो, __args)

/* XPCS callbacks */
#घोषणा sपंचांगmac_xpcs_validate(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, xpcs, validate, __args)
#घोषणा sपंचांगmac_xpcs_config(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, xpcs, config, __args)
#घोषणा sपंचांगmac_xpcs_get_state(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, xpcs, get_state, __args)
#घोषणा sपंचांगmac_xpcs_link_up(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, xpcs, link_up, __args)
#घोषणा sपंचांगmac_xpcs_probe(__priv, __args...) \
	sपंचांगmac_करो_callback(__priv, xpcs, probe, __args)

काष्ठा sपंचांगmac_regs_off अणु
	u32 ptp_off;
	u32 mmc_off;
पूर्ण;

बाह्य स्थिर काष्ठा sपंचांगmac_ops dwmac100_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_dma_ops dwmac100_dma_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_ops dwmac1000_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_dma_ops dwmac1000_dma_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_ops dwmac4_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_dma_ops dwmac4_dma_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_ops dwmac410_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_dma_ops dwmac410_dma_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_ops dwmac510_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_tc_ops dwmac510_tc_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_ops dwxgmac210_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_ops dwxlgmac2_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_dma_ops dwxgmac210_dma_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_desc_ops dwxgmac210_desc_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_mmc_ops dwmac_mmc_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_mmc_ops dwxgmac_mmc_ops;

#घोषणा GMAC_VERSION		0x00000020	/* GMAC CORE Version */
#घोषणा GMAC4_VERSION		0x00000110	/* GMAC4+ CORE Version */

पूर्णांक sपंचांगmac_hwअगर_init(काष्ठा sपंचांगmac_priv *priv);

#पूर्ण_अगर /* __STMMAC_HWIF_H__ */
