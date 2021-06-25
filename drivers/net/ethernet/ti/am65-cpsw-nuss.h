<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 *
 */

#अगर_अघोषित AM65_CPSW_NUSS_H_
#घोषणा AM65_CPSW_NUSS_H_

#समावेश <linux/अगर_ether.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/ti/k3-ringacc.h>
#समावेश <net/devlink.h>
#समावेश "am65-cpsw-qos.h"

काष्ठा am65_cpts;

#घोषणा HOST_PORT_NUM		0

#घोषणा AM65_CPSW_MAX_TX_QUEUES	8
#घोषणा AM65_CPSW_MAX_RX_QUEUES	1
#घोषणा AM65_CPSW_MAX_RX_FLOWS	1

#घोषणा AM65_CPSW_PORT_VLAN_REG_OFFSET	0x014

काष्ठा am65_cpsw_slave_data अणु
	bool				mac_only;
	काष्ठा cpsw_sl			*mac_sl;
	काष्ठा device_node		*phy_node;
	काष्ठा phy_device		*phy;
	phy_पूर्णांकerface_t			phy_अगर;
	काष्ठा phy			*अगरphy;
	bool				rx_छोड़ो;
	bool				tx_छोड़ो;
	u8				mac_addr[ETH_ALEN];
	पूर्णांक				port_vlan;
पूर्ण;

काष्ठा am65_cpsw_port अणु
	काष्ठा am65_cpsw_common		*common;
	काष्ठा net_device		*ndev;
	स्थिर अक्षर			*name;
	u32				port_id;
	व्योम __iomem			*port_base;
	व्योम __iomem			*stat_base;
	व्योम __iomem			*fetch_ram_base;
	bool				disabled;
	काष्ठा am65_cpsw_slave_data	slave;
	bool				tx_ts_enabled;
	bool				rx_ts_enabled;
	काष्ठा am65_cpsw_qos		qos;
	काष्ठा devlink_port		devlink_port;
पूर्ण;

काष्ठा am65_cpsw_host अणु
	काष्ठा am65_cpsw_common		*common;
	व्योम __iomem			*port_base;
	व्योम __iomem			*stat_base;
पूर्ण;

काष्ठा am65_cpsw_tx_chn अणु
	काष्ठा device *dma_dev;
	काष्ठा napi_काष्ठा napi_tx;
	काष्ठा am65_cpsw_common	*common;
	काष्ठा k3_cppi_desc_pool *desc_pool;
	काष्ठा k3_udma_glue_tx_channel *tx_chn;
	spinlock_t lock; /* protect TX rings in multi-port mode */
	पूर्णांक irq;
	u32 id;
	u32 descs_num;
	अक्षर tx_chn_name[128];
पूर्ण;

काष्ठा am65_cpsw_rx_chn अणु
	काष्ठा device *dev;
	काष्ठा device *dma_dev;
	काष्ठा k3_cppi_desc_pool *desc_pool;
	काष्ठा k3_udma_glue_rx_channel *rx_chn;
	u32 descs_num;
	पूर्णांक irq;
पूर्ण;

#घोषणा AM65_CPSW_QUIRK_I2027_NO_TX_CSUM BIT(0)

काष्ठा am65_cpsw_pdata अणु
	u32	quirks;
	क्रमागत k3_ring_mode fdqring_mode;
	स्थिर अक्षर	*ale_dev_id;
पूर्ण;

क्रमागत cpsw_devlink_param_id अणु
	AM65_CPSW_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	AM65_CPSW_DL_PARAM_SWITCH_MODE,
पूर्ण;

काष्ठा am65_cpsw_devlink अणु
	काष्ठा am65_cpsw_common *common;
पूर्ण;

काष्ठा am65_cpsw_common अणु
	काष्ठा device		*dev;
	काष्ठा device		*mdio_dev;
	काष्ठा am65_cpsw_pdata	pdata;

	व्योम __iomem		*ss_base;
	व्योम __iomem		*cpsw_base;

	u32			port_num;
	काष्ठा am65_cpsw_host   host;
	काष्ठा am65_cpsw_port	*ports;
	u32			disabled_ports_mask;
	काष्ठा net_device	*dma_ndev;

	पूर्णांक			usage_count; /* number of खोलोed ports */
	काष्ठा cpsw_ale		*ale;
	पूर्णांक			tx_ch_num;
	u32			rx_flow_id_base;

	काष्ठा am65_cpsw_tx_chn	tx_chns[AM65_CPSW_MAX_TX_QUEUES];
	काष्ठा completion	tकरोwn_complete;
	atomic_t		tकरोwn_cnt;

	काष्ठा am65_cpsw_rx_chn	rx_chns;
	काष्ठा napi_काष्ठा	napi_rx;

	u32			nuss_ver;
	u32			cpsw_ver;
	अचिन्हित दीर्घ		bus_freq;
	bool			pf_p0_rx_ptype_rrobin;
	काष्ठा am65_cpts	*cpts;
	पूर्णांक			est_enabled;

	bool		is_emac_mode;
	u16			br_members;
	पूर्णांक			शेष_vlan;
	काष्ठा devlink *devlink;
	काष्ठा net_device *hw_bridge_dev;
	काष्ठा notअगरier_block am65_cpsw_netdevice_nb;
	अचिन्हित अक्षर चयन_id[MAX_PHYS_ITEM_ID_LEN];
पूर्ण;

काष्ठा am65_cpsw_ndev_stats अणु
	u64 tx_packets;
	u64 tx_bytes;
	u64 rx_packets;
	u64 rx_bytes;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा am65_cpsw_ndev_priv अणु
	u32			msg_enable;
	काष्ठा am65_cpsw_port	*port;
	काष्ठा am65_cpsw_ndev_stats __percpu *stats;
	bool offload_fwd_mark;
पूर्ण;

#घोषणा am65_ndev_to_priv(ndev) \
	((काष्ठा am65_cpsw_ndev_priv *)netdev_priv(ndev))
#घोषणा am65_ndev_to_port(ndev) (am65_ndev_to_priv(ndev)->port)
#घोषणा am65_ndev_to_common(ndev) (am65_ndev_to_port(ndev)->common)
#घोषणा am65_ndev_to_slave(ndev) (&am65_ndev_to_port(ndev)->slave)

#घोषणा am65_common_get_host(common) (&(common)->host)
#घोषणा am65_common_get_port(common, id) (&(common)->ports[(id) - 1])

#घोषणा am65_cpsw_napi_to_common(pnapi) \
	container_of(pnapi, काष्ठा am65_cpsw_common, napi_rx)
#घोषणा am65_cpsw_napi_to_tx_chn(pnapi) \
	container_of(pnapi, काष्ठा am65_cpsw_tx_chn, napi_tx)

#घोषणा AM65_CPSW_DRV_NAME "am65-cpsw-nuss"

#घोषणा AM65_CPSW_IS_CPSW2G(common) ((common)->port_num == 1)

बाह्य स्थिर काष्ठा ethtool_ops am65_cpsw_ethtool_ops_slave;

व्योम am65_cpsw_nuss_adjust_link(काष्ठा net_device *ndev);
व्योम am65_cpsw_nuss_set_p0_ptype(काष्ठा am65_cpsw_common *common);
व्योम am65_cpsw_nuss_हटाओ_tx_chns(काष्ठा am65_cpsw_common *common);
पूर्णांक am65_cpsw_nuss_update_tx_chns(काष्ठा am65_cpsw_common *common, पूर्णांक num_tx);

bool am65_cpsw_port_dev_check(स्थिर काष्ठा net_device *dev);

#पूर्ण_अगर /* AM65_CPSW_NUSS_H_ */
