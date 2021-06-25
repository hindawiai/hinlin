<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NetCP driver local header
 *
 * Copyright (C) 2014 Texas Instruments Incorporated
 * Authors:	Sandeep Nair <sandeep_n@ti.com>
 *		Sandeep Paulraj <s-paulraj@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *		Santosh Shilimkar <santosh.shilimkar@ti.com>
 *		Wingman Kwok <w-kwok2@ti.com>
 *		Murali Karicheri <m-karicheri2@ti.com>
 */
#अगर_अघोषित __NETCP_H__
#घोषणा __NETCP_H__

#समावेश <linux/netdevice.h>
#समावेश <linux/soc/ti/knav_dma.h>
#समावेश <linux/u64_stats_sync.h>

/* Maximum Ethernet frame size supported by Keystone चयन */
#घोषणा NETCP_MAX_FRAME_SIZE		9504

#घोषणा SGMII_LINK_MAC_MAC_AUTONEG	0
#घोषणा SGMII_LINK_MAC_PHY		1
#घोषणा SGMII_LINK_MAC_MAC_FORCED	2
#घोषणा SGMII_LINK_MAC_FIBER		3
#घोषणा SGMII_LINK_MAC_PHY_NO_MDIO	4
#घोषणा RGMII_LINK_MAC_PHY		5
#घोषणा RGMII_LINK_MAC_PHY_NO_MDIO	7
#घोषणा XGMII_LINK_MAC_PHY		10
#घोषणा XGMII_LINK_MAC_MAC_FORCED	11

काष्ठा netcp_device;

काष्ठा netcp_tx_pipe अणु
	काष्ठा netcp_device	*netcp_device;
	व्योम			*dma_queue;
	अचिन्हित पूर्णांक		dma_queue_id;
	/* To port क्रम packet क्रमwarded to चयन. Used only by ethss */
	u8			चयन_to_port;
#घोषणा	SWITCH_TO_PORT_IN_TAGINFO	BIT(0)
	u8			flags;
	व्योम			*dma_channel;
	स्थिर अक्षर		*dma_chan_name;
पूर्ण;

#घोषणा ADDR_NEW			BIT(0)
#घोषणा ADDR_VALID			BIT(1)

क्रमागत netcp_addr_type अणु
	ADDR_ANY,
	ADDR_DEV,
	ADDR_UCAST,
	ADDR_MCAST,
	ADDR_BCAST
पूर्ण;

काष्ठा netcp_addr अणु
	काष्ठा netcp_पूर्णांकf	*netcp;
	अचिन्हित अक्षर		addr[ETH_ALEN];
	क्रमागत netcp_addr_type	type;
	अचिन्हित पूर्णांक		flags;
	काष्ठा list_head	node;
पूर्ण;

काष्ठा netcp_stats अणु
	काष्ठा u64_stats_sync   syncp_rx ____cacheline_aligned_in_smp;
	u64                     rx_packets;
	u64                     rx_bytes;
	u32                     rx_errors;
	u32                     rx_dropped;

	काष्ठा u64_stats_sync   syncp_tx ____cacheline_aligned_in_smp;
	u64                     tx_packets;
	u64                     tx_bytes;
	u32                     tx_errors;
	u32                     tx_dropped;
पूर्ण;

काष्ठा netcp_पूर्णांकf अणु
	काष्ठा device		*dev;
	काष्ठा device		*ndev_dev;
	काष्ठा net_device	*ndev;
	bool			big_endian;
	अचिन्हित पूर्णांक		tx_compl_qid;
	व्योम			*tx_pool;
	काष्ठा list_head	txhook_list_head;
	अचिन्हित पूर्णांक		tx_छोड़ो_threshold;
	व्योम			*tx_compl_q;

	अचिन्हित पूर्णांक		tx_resume_threshold;
	व्योम			*rx_queue;
	व्योम			*rx_pool;
	काष्ठा list_head	rxhook_list_head;
	अचिन्हित पूर्णांक		rx_queue_id;
	व्योम			*rx_fdq[KNAV_DMA_FDQ_PER_CHAN];
	काष्ठा napi_काष्ठा	rx_napi;
	काष्ठा napi_काष्ठा	tx_napi;
#घोषणा ETH_SW_CAN_REMOVE_ETH_FCS	BIT(0)
	u32			hw_cap;

	/* 64-bit netcp stats */
	काष्ठा netcp_stats	stats;

	व्योम			*rx_channel;
	स्थिर अक्षर		*dma_chan_name;
	u32			rx_pool_size;
	u32			rx_pool_region_id;
	u32			tx_pool_size;
	u32			tx_pool_region_id;
	काष्ठा list_head	module_head;
	काष्ठा list_head	पूर्णांकerface_list;
	काष्ठा list_head	addr_list;
	bool			netdev_रेजिस्टरed;
	bool			primary_module_attached;

	/* Lock used क्रम protecting Rx/Tx hook list management */
	spinlock_t		lock;
	काष्ठा netcp_device	*netcp_device;
	काष्ठा device_node	*node_पूर्णांकerface;

	/* DMA configuration data */
	u32			msg_enable;
	u32			rx_queue_depths[KNAV_DMA_FDQ_PER_CHAN];
पूर्ण;

#घोषणा	NETCP_PSDATA_LEN		KNAV_DMA_NUM_PS_WORDS
काष्ठा netcp_packet अणु
	काष्ठा sk_buff		*skb;
	__le32			*epib;
	u32			*psdata;
	u32			eflags;
	अचिन्हित पूर्णांक		psdata_len;
	काष्ठा netcp_पूर्णांकf	*netcp;
	काष्ठा netcp_tx_pipe	*tx_pipe;
	bool			rxtstamp_complete;
	व्योम			*ts_context;

	व्योम (*txtstamp)(व्योम *ctx, काष्ठा sk_buff *skb);
पूर्ण;

अटल अंतरभूत u32 *netcp_push_psdata(काष्ठा netcp_packet *p_info,
				     अचिन्हित पूर्णांक bytes)
अणु
	u32 *buf;
	अचिन्हित पूर्णांक words;

	अगर ((bytes & 0x03) != 0)
		वापस शून्य;
	words = bytes >> 2;

	अगर ((p_info->psdata_len + words) > NETCP_PSDATA_LEN)
		वापस शून्य;

	p_info->psdata_len += words;
	buf = &p_info->psdata[NETCP_PSDATA_LEN - p_info->psdata_len];
	वापस buf;
पूर्ण

अटल अंतरभूत पूर्णांक netcp_align_psdata(काष्ठा netcp_packet *p_info,
				     अचिन्हित पूर्णांक byte_align)
अणु
	पूर्णांक padding;

	चयन (byte_align) अणु
	हाल 0:
		padding = -EINVAL;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 4:
		padding = 0;
		अवरोध;
	हाल 8:
		padding = (p_info->psdata_len << 2) % 8;
		अवरोध;
	हाल 16:
		padding = (p_info->psdata_len << 2) % 16;
		अवरोध;
	शेष:
		padding = (p_info->psdata_len << 2) % byte_align;
		अवरोध;
	पूर्ण
	वापस padding;
पूर्ण

काष्ठा netcp_module अणु
	स्थिर अक्षर		*name;
	काष्ठा module		*owner;
	bool			primary;

	/* probe/हटाओ: called once per NETCP instance */
	पूर्णांक	(*probe)(काष्ठा netcp_device *netcp_device,
			 काष्ठा device *device, काष्ठा device_node *node,
			 व्योम **inst_priv);
	पूर्णांक	(*हटाओ)(काष्ठा netcp_device *netcp_device, व्योम *inst_priv);

	/* attach/release: called once per network पूर्णांकerface */
	पूर्णांक	(*attach)(व्योम *inst_priv, काष्ठा net_device *ndev,
			  काष्ठा device_node *node, व्योम **पूर्णांकf_priv);
	पूर्णांक	(*release)(व्योम *पूर्णांकf_priv);
	पूर्णांक	(*खोलो)(व्योम *पूर्णांकf_priv, काष्ठा net_device *ndev);
	पूर्णांक	(*बंद)(व्योम *पूर्णांकf_priv, काष्ठा net_device *ndev);
	पूर्णांक	(*add_addr)(व्योम *पूर्णांकf_priv, काष्ठा netcp_addr *naddr);
	पूर्णांक	(*del_addr)(व्योम *पूर्णांकf_priv, काष्ठा netcp_addr *naddr);
	पूर्णांक	(*add_vid)(व्योम *पूर्णांकf_priv, पूर्णांक vid);
	पूर्णांक	(*del_vid)(व्योम *पूर्णांकf_priv, पूर्णांक vid);
	पूर्णांक	(*ioctl)(व्योम *पूर्णांकf_priv, काष्ठा अगरreq *req, पूर्णांक cmd);
	पूर्णांक	(*set_rx_mode)(व्योम *पूर्णांकf_priv, bool promisc);

	/* used पूर्णांकernally */
	काष्ठा list_head	module_list;
	काष्ठा list_head	पूर्णांकerface_list;
पूर्ण;

पूर्णांक netcp_रेजिस्टर_module(काष्ठा netcp_module *module);
व्योम netcp_unरेजिस्टर_module(काष्ठा netcp_module *module);
व्योम *netcp_module_get_पूर्णांकf_data(काष्ठा netcp_module *module,
				 काष्ठा netcp_पूर्णांकf *पूर्णांकf);

पूर्णांक netcp_txpipe_init(काष्ठा netcp_tx_pipe *tx_pipe,
		      काष्ठा netcp_device *netcp_device,
		      स्थिर अक्षर *dma_chan_name, अचिन्हित पूर्णांक dma_queue_id);
पूर्णांक netcp_txpipe_खोलो(काष्ठा netcp_tx_pipe *tx_pipe);
पूर्णांक netcp_txpipe_बंद(काष्ठा netcp_tx_pipe *tx_pipe);

प्रकार पूर्णांक netcp_hook_rtn(पूर्णांक order, व्योम *data, काष्ठा netcp_packet *packet);
पूर्णांक netcp_रेजिस्टर_txhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			  netcp_hook_rtn *hook_rtn, व्योम *hook_data);
पूर्णांक netcp_unरेजिस्टर_txhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			    netcp_hook_rtn *hook_rtn, व्योम *hook_data);
पूर्णांक netcp_रेजिस्टर_rxhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			  netcp_hook_rtn *hook_rtn, व्योम *hook_data);
पूर्णांक netcp_unरेजिस्टर_rxhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			    netcp_hook_rtn *hook_rtn, व्योम *hook_data);
व्योम *netcp_device_find_module(काष्ठा netcp_device *netcp_device,
			       स्थिर अक्षर *name);

/* SGMII functions */
पूर्णांक netcp_sgmii_reset(व्योम __iomem *sgmii_ofs, पूर्णांक port);
bool netcp_sgmii_rtreset(व्योम __iomem *sgmii_ofs, पूर्णांक port, bool set);
पूर्णांक netcp_sgmii_get_port_link(व्योम __iomem *sgmii_ofs, पूर्णांक port);
पूर्णांक netcp_sgmii_config(व्योम __iomem *sgmii_ofs, पूर्णांक port, u32 पूर्णांकerface);

/* XGBE SERDES init functions */
पूर्णांक netcp_xgbe_serdes_init(व्योम __iomem *serdes_regs, व्योम __iomem *xgbe_regs);

#पूर्ण_अगर	/* __NETCP_H__ */
