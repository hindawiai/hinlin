<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This is the driver क्रम the ST MAC 10/100/1000 on-chip Ethernet controllers.
  ST Ethernet IPs are built around a Synopsys IP Core.

	Copyright(C) 2007-2011 STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>

  Documentation available at:
	http://www.stlinux.com
  Support available at:
	https://bugzilla.stlinux.com/
*******************************************************************************/

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/pinctrl/consumer.h>
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phylink.h>
#समावेश <linux/udp.h>
#समावेश <linux/bpf_trace.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश "stmmac_ptp.h"
#समावेश "stmmac.h"
#समावेश "stmmac_xdp.h"
#समावेश <linux/reset.h>
#समावेश <linux/of_mdपन.स>
#समावेश "dwmac1000.h"
#समावेश "dwxgmac2.h"
#समावेश "hwif.h"

#घोषणा	STMMAC_ALIGN(x)		ALIGN(ALIGN(x, SMP_CACHE_BYTES), 16)
#घोषणा	TSO_MAX_BUFF_SIZE	(SZ_16K - 1)

/* Module parameters */
#घोषणा TX_TIMEO	5000
अटल पूर्णांक watchकरोg = TX_TIMEO;
module_param(watchकरोg, पूर्णांक, 0644);
MODULE_PARM_DESC(watchकरोg, "Transmit timeout in milliseconds (default 5s)");

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Message Level (-1: default, 0: no output, 16: all)");

अटल पूर्णांक phyaddr = -1;
module_param(phyaddr, पूर्णांक, 0444);
MODULE_PARM_DESC(phyaddr, "Physical device address");

#घोषणा STMMAC_TX_THRESH(x)	((x)->dma_tx_size / 4)
#घोषणा STMMAC_RX_THRESH(x)	((x)->dma_rx_size / 4)

/* Limit to make sure XDP TX and slow path can coexist */
#घोषणा STMMAC_XSK_TX_BUDGET_MAX	256
#घोषणा STMMAC_TX_XSK_AVAIL		16
#घोषणा STMMAC_RX_FILL_BATCH		16

#घोषणा STMMAC_XDP_PASS		0
#घोषणा STMMAC_XDP_CONSUMED	BIT(0)
#घोषणा STMMAC_XDP_TX		BIT(1)
#घोषणा STMMAC_XDP_REसूचीECT	BIT(2)

अटल पूर्णांक flow_ctrl = FLOW_AUTO;
module_param(flow_ctrl, पूर्णांक, 0644);
MODULE_PARM_DESC(flow_ctrl, "Flow control ability [on/off]");

अटल पूर्णांक छोड़ो = PAUSE_TIME;
module_param(छोड़ो, पूर्णांक, 0644);
MODULE_PARM_DESC(छोड़ो, "Flow Control Pause Time");

#घोषणा TC_DEFAULT 64
अटल पूर्णांक tc = TC_DEFAULT;
module_param(tc, पूर्णांक, 0644);
MODULE_PARM_DESC(tc, "DMA threshold control value");

#घोषणा	DEFAULT_बफ_मानE	1536
अटल पूर्णांक buf_sz = DEFAULT_बफ_मानE;
module_param(buf_sz, पूर्णांक, 0644);
MODULE_PARM_DESC(buf_sz, "DMA buffer size");

#घोषणा	STMMAC_RX_COPYBREAK	256

अटल स्थिर u32 शेष_msg_level = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
				      NETIF_MSG_LINK | NETIF_MSG_IFUP |
				      NETIF_MSG_IFDOWN | NETIF_MSG_TIMER);

#घोषणा STMMAC_DEFAULT_LPI_TIMER	1000
अटल पूर्णांक eee_समयr = STMMAC_DEFAULT_LPI_TIMER;
module_param(eee_समयr, पूर्णांक, 0644);
MODULE_PARM_DESC(eee_समयr, "LPI tx expiration time in msec");
#घोषणा STMMAC_LPI_T(x) (jअगरfies + usecs_to_jअगरfies(x))

/* By शेष the driver will use the ring mode to manage tx and rx descriptors,
 * but allow user to क्रमce to use the chain instead of the ring
 */
अटल अचिन्हित पूर्णांक chain_mode;
module_param(chain_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(chain_mode, "To use chain instead of ring mode");

अटल irqवापस_t sपंचांगmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
/* For MSI पूर्णांकerrupts handling */
अटल irqवापस_t sपंचांगmac_mac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t sपंचांगmac_safety_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t sपंचांगmac_msi_पूर्णांकr_tx(पूर्णांक irq, व्योम *data);
अटल irqवापस_t sपंचांगmac_msi_पूर्णांकr_rx(पूर्णांक irq, व्योम *data);
अटल व्योम sपंचांगmac_tx_समयr_arm(काष्ठा sपंचांगmac_priv *priv, u32 queue);
अटल व्योम sपंचांगmac_flush_tx_descriptors(काष्ठा sपंचांगmac_priv *priv, पूर्णांक queue);

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा net_device_ops sपंचांगmac_netdev_ops;
अटल व्योम sपंचांगmac_init_fs(काष्ठा net_device *dev);
अटल व्योम sपंचांगmac_निकास_fs(काष्ठा net_device *dev);
#पूर्ण_अगर

#घोषणा STMMAC_COAL_TIMER(x) (ns_to_kसमय((x) * NSEC_PER_USEC))

पूर्णांक sपंचांगmac_bus_clks_config(काष्ठा sपंचांगmac_priv *priv, bool enabled)
अणु
	पूर्णांक ret = 0;

	अगर (enabled) अणु
		ret = clk_prepare_enable(priv->plat->sपंचांगmac_clk);
		अगर (ret)
			वापस ret;
		ret = clk_prepare_enable(priv->plat->pclk);
		अगर (ret) अणु
			clk_disable_unprepare(priv->plat->sपंचांगmac_clk);
			वापस ret;
		पूर्ण
		अगर (priv->plat->clks_config) अणु
			ret = priv->plat->clks_config(priv->plat->bsp_priv, enabled);
			अगर (ret) अणु
				clk_disable_unprepare(priv->plat->sपंचांगmac_clk);
				clk_disable_unprepare(priv->plat->pclk);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(priv->plat->sपंचांगmac_clk);
		clk_disable_unprepare(priv->plat->pclk);
		अगर (priv->plat->clks_config)
			priv->plat->clks_config(priv->plat->bsp_priv, enabled);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_bus_clks_config);

/**
 * sपंचांगmac_verअगरy_args - verअगरy the driver parameters.
 * Description: it checks the driver parameters and set a शेष in हाल of
 * errors.
 */
अटल व्योम sपंचांगmac_verअगरy_args(व्योम)
अणु
	अगर (unlikely(watchकरोg < 0))
		watchकरोg = TX_TIMEO;
	अगर (unlikely((buf_sz < DEFAULT_बफ_मानE) || (buf_sz > BUF_SIZE_16KiB)))
		buf_sz = DEFAULT_बफ_मानE;
	अगर (unlikely(flow_ctrl > 1))
		flow_ctrl = FLOW_AUTO;
	अन्यथा अगर (likely(flow_ctrl < 0))
		flow_ctrl = FLOW_OFF;
	अगर (unlikely((छोड़ो < 0) || (छोड़ो > 0xffff)))
		छोड़ो = PAUSE_TIME;
	अगर (eee_समयr < 0)
		eee_समयr = STMMAC_DEFAULT_LPI_TIMER;
पूर्ण

अटल व्योम __sपंचांगmac_disable_all_queues(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_cnt = priv->plat->rx_queues_to_use;
	u32 tx_queues_cnt = priv->plat->tx_queues_to_use;
	u32 maxq = max(rx_queues_cnt, tx_queues_cnt);
	u32 queue;

	क्रम (queue = 0; queue < maxq; queue++) अणु
		काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];

		अगर (sपंचांगmac_xdp_is_enabled(priv) &&
		    test_bit(queue, priv->af_xdp_zc_qps)) अणु
			napi_disable(&ch->rxtx_napi);
			जारी;
		पूर्ण

		अगर (queue < rx_queues_cnt)
			napi_disable(&ch->rx_napi);
		अगर (queue < tx_queues_cnt)
			napi_disable(&ch->tx_napi);
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_disable_all_queues - Disable all queues
 * @priv: driver निजी काष्ठाure
 */
अटल व्योम sपंचांगmac_disable_all_queues(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_cnt = priv->plat->rx_queues_to_use;
	काष्ठा sपंचांगmac_rx_queue *rx_q;
	u32 queue;

	/* synchronize_rcu() needed क्रम pending XDP buffers to drain */
	क्रम (queue = 0; queue < rx_queues_cnt; queue++) अणु
		rx_q = &priv->rx_queue[queue];
		अगर (rx_q->xsk_pool) अणु
			synchronize_rcu();
			अवरोध;
		पूर्ण
	पूर्ण

	__sपंचांगmac_disable_all_queues(priv);
पूर्ण

/**
 * sपंचांगmac_enable_all_queues - Enable all queues
 * @priv: driver निजी काष्ठाure
 */
अटल व्योम sपंचांगmac_enable_all_queues(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_cnt = priv->plat->rx_queues_to_use;
	u32 tx_queues_cnt = priv->plat->tx_queues_to_use;
	u32 maxq = max(rx_queues_cnt, tx_queues_cnt);
	u32 queue;

	क्रम (queue = 0; queue < maxq; queue++) अणु
		काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];

		अगर (sपंचांगmac_xdp_is_enabled(priv) &&
		    test_bit(queue, priv->af_xdp_zc_qps)) अणु
			napi_enable(&ch->rxtx_napi);
			जारी;
		पूर्ण

		अगर (queue < rx_queues_cnt)
			napi_enable(&ch->rx_napi);
		अगर (queue < tx_queues_cnt)
			napi_enable(&ch->tx_napi);
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_service_event_schedule(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!test_bit(STMMAC_DOWN, &priv->state) &&
	    !test_and_set_bit(STMMAC_SERVICE_SCHED, &priv->state))
		queue_work(priv->wq, &priv->service_task);
पूर्ण

अटल व्योम sपंचांगmac_global_err(काष्ठा sपंचांगmac_priv *priv)
अणु
	netअगर_carrier_off(priv->dev);
	set_bit(STMMAC_RESET_REQUESTED, &priv->state);
	sपंचांगmac_service_event_schedule(priv);
पूर्ण

/**
 * sपंचांगmac_clk_csr_set - dynamically set the MDC घड़ी
 * @priv: driver निजी काष्ठाure
 * Description: this is to dynamically set the MDC घड़ी according to the csr
 * घड़ी input.
 * Note:
 *	If a specअगरic clk_csr value is passed from the platक्रमm
 *	this means that the CSR Clock Range selection cannot be
 *	changed at run-समय and it is fixed (as reported in the driver
 *	करोcumentation). Viceversa the driver will try to set the MDC
 *	घड़ी dynamically according to the actual घड़ी input.
 */
अटल व्योम sपंचांगmac_clk_csr_set(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 clk_rate;

	clk_rate = clk_get_rate(priv->plat->sपंचांगmac_clk);

	/* Platक्रमm provided शेष clk_csr would be assumed valid
	 * क्रम all other हालs except क्रम the below mentioned ones.
	 * For values higher than the IEEE 802.3 specअगरied frequency
	 * we can not estimate the proper भागider as it is not known
	 * the frequency of clk_csr_i. So we करो not change the शेष
	 * भागider.
	 */
	अगर (!(priv->clk_csr & MAC_CSR_H_FRQ_MASK)) अणु
		अगर (clk_rate < CSR_F_35M)
			priv->clk_csr = STMMAC_CSR_20_35M;
		अन्यथा अगर ((clk_rate >= CSR_F_35M) && (clk_rate < CSR_F_60M))
			priv->clk_csr = STMMAC_CSR_35_60M;
		अन्यथा अगर ((clk_rate >= CSR_F_60M) && (clk_rate < CSR_F_100M))
			priv->clk_csr = STMMAC_CSR_60_100M;
		अन्यथा अगर ((clk_rate >= CSR_F_100M) && (clk_rate < CSR_F_150M))
			priv->clk_csr = STMMAC_CSR_100_150M;
		अन्यथा अगर ((clk_rate >= CSR_F_150M) && (clk_rate < CSR_F_250M))
			priv->clk_csr = STMMAC_CSR_150_250M;
		अन्यथा अगर ((clk_rate >= CSR_F_250M) && (clk_rate < CSR_F_300M))
			priv->clk_csr = STMMAC_CSR_250_300M;
	पूर्ण

	अगर (priv->plat->has_sun8i) अणु
		अगर (clk_rate > 160000000)
			priv->clk_csr = 0x03;
		अन्यथा अगर (clk_rate > 80000000)
			priv->clk_csr = 0x02;
		अन्यथा अगर (clk_rate > 40000000)
			priv->clk_csr = 0x01;
		अन्यथा
			priv->clk_csr = 0;
	पूर्ण

	अगर (priv->plat->has_xgmac) अणु
		अगर (clk_rate > 400000000)
			priv->clk_csr = 0x5;
		अन्यथा अगर (clk_rate > 350000000)
			priv->clk_csr = 0x4;
		अन्यथा अगर (clk_rate > 300000000)
			priv->clk_csr = 0x3;
		अन्यथा अगर (clk_rate > 250000000)
			priv->clk_csr = 0x2;
		अन्यथा अगर (clk_rate > 150000000)
			priv->clk_csr = 0x1;
		अन्यथा
			priv->clk_csr = 0x0;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_pkt(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	pr_debug("len = %d byte, buf addr: 0x%p\n", len, buf);
	prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_OFFSET, buf, len);
पूर्ण

अटल अंतरभूत u32 sपंचांगmac_tx_avail(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	u32 avail;

	अगर (tx_q->dirty_tx > tx_q->cur_tx)
		avail = tx_q->dirty_tx - tx_q->cur_tx - 1;
	अन्यथा
		avail = priv->dma_tx_size - tx_q->cur_tx + tx_q->dirty_tx - 1;

	वापस avail;
पूर्ण

/**
 * sपंचांगmac_rx_dirty - Get RX queue dirty
 * @priv: driver निजी काष्ठाure
 * @queue: RX queue index
 */
अटल अंतरभूत u32 sपंचांगmac_rx_dirty(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	u32 dirty;

	अगर (rx_q->dirty_rx <= rx_q->cur_rx)
		dirty = rx_q->cur_rx - rx_q->dirty_rx;
	अन्यथा
		dirty = priv->dma_rx_size - rx_q->dirty_rx + rx_q->cur_rx;

	वापस dirty;
पूर्ण

अटल व्योम sपंचांगmac_lpi_entry_समयr_config(काष्ठा sपंचांगmac_priv *priv, bool en)
अणु
	पूर्णांक tx_lpi_समयr;

	/* Clear/set the SW EEE समयr flag based on LPI ET enablement */
	priv->eee_sw_समयr_en = en ? 0 : 1;
	tx_lpi_समयr  = en ? priv->tx_lpi_समयr : 0;
	sपंचांगmac_set_eee_lpi_समयr(priv, priv->hw, tx_lpi_समयr);
पूर्ण

/**
 * sपंचांगmac_enable_eee_mode - check and enter in LPI mode
 * @priv: driver निजी काष्ठाure
 * Description: this function is to verअगरy and enter in LPI mode in हाल of
 * EEE.
 */
अटल व्योम sपंचांगmac_enable_eee_mode(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	/* check अगर all TX queues have the work finished */
	क्रम (queue = 0; queue < tx_cnt; queue++) अणु
		काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];

		अगर (tx_q->dirty_tx != tx_q->cur_tx)
			वापस; /* still unfinished work */
	पूर्ण

	/* Check and enter in LPI mode */
	अगर (!priv->tx_path_in_lpi_mode)
		sपंचांगmac_set_eee_mode(priv, priv->hw,
				priv->plat->en_tx_lpi_घड़ीgating);
पूर्ण

/**
 * sपंचांगmac_disable_eee_mode - disable and निकास from LPI mode
 * @priv: driver निजी काष्ठाure
 * Description: this function is to निकास and disable EEE in हाल of
 * LPI state is true. This is called by the xmit.
 */
व्योम sपंचांगmac_disable_eee_mode(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!priv->eee_sw_समयr_en) अणु
		sपंचांगmac_lpi_entry_समयr_config(priv, 0);
		वापस;
	पूर्ण

	sपंचांगmac_reset_eee_mode(priv, priv->hw);
	del_समयr_sync(&priv->eee_ctrl_समयr);
	priv->tx_path_in_lpi_mode = false;
पूर्ण

/**
 * sपंचांगmac_eee_ctrl_समयr - EEE TX SW समयr.
 * @t:  समयr_list काष्ठा containing निजी info
 * Description:
 *  अगर there is no data transfer and अगर we are not in LPI state,
 *  then MAC Transmitter can be moved to LPI state.
 */
अटल व्योम sपंचांगmac_eee_ctrl_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sपंचांगmac_priv *priv = from_समयr(priv, t, eee_ctrl_समयr);

	sपंचांगmac_enable_eee_mode(priv);
	mod_समयr(&priv->eee_ctrl_समयr, STMMAC_LPI_T(priv->tx_lpi_समयr));
पूर्ण

/**
 * sपंचांगmac_eee_init - init EEE
 * @priv: driver निजी काष्ठाure
 * Description:
 *  अगर the GMAC supports the EEE (from the HW cap reg) and the phy device
 *  can also manage EEE, this function enable the LPI state and start related
 *  समयr.
 */
bool sपंचांगmac_eee_init(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक eee_tw_समयr = priv->eee_tw_समयr;

	/* Using PCS we cannot dial with the phy रेजिस्टरs at this stage
	 * so we करो not support extra feature like EEE.
	 */
	अगर (priv->hw->pcs == STMMAC_PCS_TBI ||
	    priv->hw->pcs == STMMAC_PCS_RTBI)
		वापस false;

	/* Check अगर MAC core supports the EEE feature. */
	अगर (!priv->dma_cap.eee)
		वापस false;

	mutex_lock(&priv->lock);

	/* Check अगर it needs to be deactivated */
	अगर (!priv->eee_active) अणु
		अगर (priv->eee_enabled) अणु
			netdev_dbg(priv->dev, "disable EEE\n");
			sपंचांगmac_lpi_entry_समयr_config(priv, 0);
			del_समयr_sync(&priv->eee_ctrl_समयr);
			sपंचांगmac_set_eee_समयr(priv, priv->hw, 0, eee_tw_समयr);
		पूर्ण
		mutex_unlock(&priv->lock);
		वापस false;
	पूर्ण

	अगर (priv->eee_active && !priv->eee_enabled) अणु
		समयr_setup(&priv->eee_ctrl_समयr, sपंचांगmac_eee_ctrl_समयr, 0);
		sपंचांगmac_set_eee_समयr(priv, priv->hw, STMMAC_DEFAULT_LIT_LS,
				     eee_tw_समयr);
	पूर्ण

	अगर (priv->plat->has_gmac4 && priv->tx_lpi_समयr <= STMMAC_ET_MAX) अणु
		del_समयr_sync(&priv->eee_ctrl_समयr);
		priv->tx_path_in_lpi_mode = false;
		sपंचांगmac_lpi_entry_समयr_config(priv, 1);
	पूर्ण अन्यथा अणु
		sपंचांगmac_lpi_entry_समयr_config(priv, 0);
		mod_समयr(&priv->eee_ctrl_समयr,
			  STMMAC_LPI_T(priv->tx_lpi_समयr));
	पूर्ण

	mutex_unlock(&priv->lock);
	netdev_dbg(priv->dev, "Energy-Efficient Ethernet initialized\n");
	वापस true;
पूर्ण

/* sपंचांगmac_get_tx_hwtstamp - get HW TX बारtamps
 * @priv: driver निजी काष्ठाure
 * @p : descriptor poपूर्णांकer
 * @skb : the socket buffer
 * Description :
 * This function will पढ़ो बारtamp from the descriptor & pass it to stack.
 * and also perक्रमm some sanity checks.
 */
अटल व्योम sपंचांगmac_get_tx_hwtstamp(काष्ठा sपंचांगmac_priv *priv,
				   काष्ठा dma_desc *p, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamp;
	bool found = false;
	s64 adjust = 0;
	u64 ns = 0;

	अगर (!priv->hwts_tx_en)
		वापस;

	/* निकास अगर skb करोesn't support hw tstamp */
	अगर (likely(!skb || !(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)))
		वापस;

	/* check tx tstamp status */
	अगर (sपंचांगmac_get_tx_बारtamp_status(priv, p)) अणु
		sपंचांगmac_get_बारtamp(priv, p, priv->adv_ts, &ns);
		found = true;
	पूर्ण अन्यथा अगर (!sपंचांगmac_get_mac_tx_बारtamp(priv, priv->hw, &ns)) अणु
		found = true;
	पूर्ण

	अगर (found) अणु
		/* Correct the clk करोमुख्य crossing(CDC) error */
		अगर (priv->plat->has_gmac4 && priv->plat->clk_ptp_rate) अणु
			adjust += -(2 * (NSEC_PER_SEC /
					 priv->plat->clk_ptp_rate));
			ns += adjust;
		पूर्ण

		स_रखो(&shhwtstamp, 0, माप(काष्ठा skb_shared_hwtstamps));
		shhwtstamp.hwtstamp = ns_to_kसमय(ns);

		netdev_dbg(priv->dev, "get valid TX hw timestamp %llu\n", ns);
		/* pass tstamp to stack */
		skb_tstamp_tx(skb, &shhwtstamp);
	पूर्ण
पूर्ण

/* sपंचांगmac_get_rx_hwtstamp - get HW RX बारtamps
 * @priv: driver निजी काष्ठाure
 * @p : descriptor poपूर्णांकer
 * @np : next descriptor poपूर्णांकer
 * @skb : the socket buffer
 * Description :
 * This function will पढ़ो received packet's बारtamp from the descriptor
 * and pass it to stack. It also perक्रमm some sanity checks.
 */
अटल व्योम sपंचांगmac_get_rx_hwtstamp(काष्ठा sपंचांगmac_priv *priv, काष्ठा dma_desc *p,
				   काष्ठा dma_desc *np, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps *shhwtstamp = शून्य;
	काष्ठा dma_desc *desc = p;
	u64 adjust = 0;
	u64 ns = 0;

	अगर (!priv->hwts_rx_en)
		वापस;
	/* For GMAC4, the valid बारtamp is from CTX next desc. */
	अगर (priv->plat->has_gmac4 || priv->plat->has_xgmac)
		desc = np;

	/* Check अगर बारtamp is available */
	अगर (sपंचांगmac_get_rx_बारtamp_status(priv, p, np, priv->adv_ts)) अणु
		sपंचांगmac_get_बारtamp(priv, desc, priv->adv_ts, &ns);

		/* Correct the clk करोमुख्य crossing(CDC) error */
		अगर (priv->plat->has_gmac4 && priv->plat->clk_ptp_rate) अणु
			adjust += 2 * (NSEC_PER_SEC / priv->plat->clk_ptp_rate);
			ns -= adjust;
		पूर्ण

		netdev_dbg(priv->dev, "get valid RX hw timestamp %llu\n", ns);
		shhwtstamp = skb_hwtstamps(skb);
		स_रखो(shhwtstamp, 0, माप(काष्ठा skb_shared_hwtstamps));
		shhwtstamp->hwtstamp = ns_to_kसमय(ns);
	पूर्ण अन्यथा  अणु
		netdev_dbg(priv->dev, "cannot get RX hw timestamp\n");
	पूर्ण
पूर्ण

/**
 *  sपंचांगmac_hwtstamp_set - control hardware बारtamping.
 *  @dev: device poपूर्णांकer.
 *  @अगरr: An IOCTL specअगरic काष्ठाure, that can contain a poपूर्णांकer to
 *  a proprietary काष्ठाure used to pass inक्रमmation to the driver.
 *  Description:
 *  This function configures the MAC to enable/disable both outgoing(TX)
 *  and incoming(RX) packets समय stamping based on user input.
 *  Return Value:
 *  0 on success and an appropriate -ve पूर्णांकeger on failure.
 */
अटल पूर्णांक sपंचांगmac_hwtstamp_set(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	काष्ठा hwtstamp_config config;
	काष्ठा बारpec64 now;
	u64 temp = 0;
	u32 ptp_v2 = 0;
	u32 tstamp_all = 0;
	u32 ptp_over_ipv4_udp = 0;
	u32 ptp_over_ipv6_udp = 0;
	u32 ptp_over_ethernet = 0;
	u32 snap_type_sel = 0;
	u32 ts_master_en = 0;
	u32 ts_event_en = 0;
	u32 sec_inc = 0;
	u32 value = 0;
	bool xmac;

	xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;

	अगर (!(priv->dma_cap.समय_stamp || priv->adv_ts)) अणु
		netdev_alert(priv->dev, "No support for HW time stamping\n");
		priv->hwts_tx_en = 0;
		priv->hwts_rx_en = 0;

		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (copy_from_user(&config, अगरr->अगरr_data,
			   माप(config)))
		वापस -EFAULT;

	netdev_dbg(priv->dev, "%s config flags:0x%x, tx_type:0x%x, rx_filter:0x%x\n",
		   __func__, config.flags, config.tx_type, config.rx_filter);

	/* reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	अगर (config.tx_type != HWTSTAMP_TX_OFF &&
	    config.tx_type != HWTSTAMP_TX_ON)
		वापस -दुस्फल;

	अगर (priv->adv_ts) अणु
		चयन (config.rx_filter) अणु
		हाल HWTSTAMP_FILTER_NONE:
			/* समय stamp no incoming packet at all */
			config.rx_filter = HWTSTAMP_FILTER_NONE;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
			/* PTP v1, UDP, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
			/* 'xmac' hardware can support Sync, Pdelay_Req and
			 * Pdelay_resp by setting bit14 and bits17/16 to 01
			 * This leaves Delay_Req बारtamps out.
			 * Enable all events *and* general purpose message
			 * बारtamping
			 */
			snap_type_sel = PTP_TCR_SNAPTYPSEL_1;
			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
			/* PTP v1, UDP, Sync packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_SYNC;
			/* take समय stamp क्रम SYNC messages only */
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
			/* PTP v1, UDP, Delay_req packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ;
			/* take समय stamp क्रम Delay_Req messages only */
			ts_master_en = PTP_TCR_TSMSTRENA;
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
			/* PTP v2, UDP, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take समय stamp क्रम all event messages */
			snap_type_sel = PTP_TCR_SNAPTYPSEL_1;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
			/* PTP v2, UDP, Sync packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_SYNC;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take समय stamp क्रम SYNC messages only */
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
			/* PTP v2, UDP, Delay_req packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take समय stamp क्रम Delay_Req messages only */
			ts_master_en = PTP_TCR_TSMSTRENA;
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
			/* PTP v2/802.AS1 any layer, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			snap_type_sel = PTP_TCR_SNAPTYPSEL_1;
			अगर (priv->synopsys_id != DWMAC_CORE_5_10)
				ts_event_en = PTP_TCR_TSEVNTENA;
			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			ptp_over_ethernet = PTP_TCR_TSIPENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
			/* PTP v2/802.AS1, any layer, Sync packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_SYNC;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take समय stamp क्रम SYNC messages only */
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			ptp_over_ethernet = PTP_TCR_TSIPENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
			/* PTP v2/802.AS1, any layer, Delay_req packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_DELAY_REQ;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take समय stamp क्रम Delay_Req messages only */
			ts_master_en = PTP_TCR_TSMSTRENA;
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			ptp_over_ethernet = PTP_TCR_TSIPENA;
			अवरोध;

		हाल HWTSTAMP_FILTER_NTP_ALL:
		हाल HWTSTAMP_FILTER_ALL:
			/* समय stamp any incoming packet */
			config.rx_filter = HWTSTAMP_FILTER_ALL;
			tstamp_all = PTP_TCR_TSENALL;
			अवरोध;

		शेष:
			वापस -दुस्फल;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (config.rx_filter) अणु
		हाल HWTSTAMP_FILTER_NONE:
			config.rx_filter = HWTSTAMP_FILTER_NONE;
			अवरोध;
		शेष:
			/* PTP v1, UDP, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
			अवरोध;
		पूर्ण
	पूर्ण
	priv->hwts_rx_en = ((config.rx_filter == HWTSTAMP_FILTER_NONE) ? 0 : 1);
	priv->hwts_tx_en = config.tx_type == HWTSTAMP_TX_ON;

	अगर (!priv->hwts_tx_en && !priv->hwts_rx_en)
		sपंचांगmac_config_hw_tstamping(priv, priv->ptpaddr, 0);
	अन्यथा अणु
		value = (PTP_TCR_TSENA | PTP_TCR_TSCFUPDT | PTP_TCR_TSCTRLSSR |
			 tstamp_all | ptp_v2 | ptp_over_ethernet |
			 ptp_over_ipv6_udp | ptp_over_ipv4_udp | ts_event_en |
			 ts_master_en | snap_type_sel);
		sपंचांगmac_config_hw_tstamping(priv, priv->ptpaddr, value);

		/* program Sub Second Increment reg */
		sपंचांगmac_config_sub_second_increment(priv,
				priv->ptpaddr, priv->plat->clk_ptp_rate,
				xmac, &sec_inc);
		temp = भाग_u64(1000000000ULL, sec_inc);

		/* Store sub second increment and flags क्रम later use */
		priv->sub_second_inc = sec_inc;
		priv->sysसमय_flags = value;

		/* calculate शेष added value:
		 * क्रमmula is :
		 * addend = (2^32)/freq_भाग_ratio;
		 * where, freq_भाग_ratio = 1e9ns/sec_inc
		 */
		temp = (u64)(temp << 32);
		priv->शेष_addend = भाग_u64(temp, priv->plat->clk_ptp_rate);
		sपंचांगmac_config_addend(priv, priv->ptpaddr, priv->शेष_addend);

		/* initialize प्रणाली समय */
		kसमय_get_real_ts64(&now);

		/* lower 32 bits of tv_sec are safe until y2106 */
		sपंचांगmac_init_sysसमय(priv, priv->ptpaddr,
				(u32)now.tv_sec, now.tv_nsec);
	पूर्ण

	स_नकल(&priv->tstamp_config, &config, माप(config));

	वापस copy_to_user(अगरr->अगरr_data, &config,
			    माप(config)) ? -EFAULT : 0;
पूर्ण

/**
 *  sपंचांगmac_hwtstamp_get - पढ़ो hardware बारtamping.
 *  @dev: device poपूर्णांकer.
 *  @अगरr: An IOCTL specअगरic काष्ठाure, that can contain a poपूर्णांकer to
 *  a proprietary काष्ठाure used to pass inक्रमmation to the driver.
 *  Description:
 *  This function obtain the current hardware बारtamping settings
 *  as requested.
 */
अटल पूर्णांक sपंचांगmac_hwtstamp_get(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	काष्ठा hwtstamp_config *config = &priv->tstamp_config;

	अगर (!(priv->dma_cap.समय_stamp || priv->dma_cap.aसमय_stamp))
		वापस -EOPNOTSUPP;

	वापस copy_to_user(अगरr->अगरr_data, config,
			    माप(*config)) ? -EFAULT : 0;
पूर्ण

/**
 * sपंचांगmac_init_ptp - init PTP
 * @priv: driver निजी काष्ठाure
 * Description: this is to verअगरy अगर the HW supports the PTPv1 or PTPv2.
 * This is करोne by looking at the HW cap. रेजिस्टर.
 * This function also रेजिस्टरs the ptp driver.
 */
अटल पूर्णांक sपंचांगmac_init_ptp(काष्ठा sपंचांगmac_priv *priv)
अणु
	bool xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;

	अगर (!(priv->dma_cap.समय_stamp || priv->dma_cap.aसमय_stamp))
		वापस -EOPNOTSUPP;

	priv->adv_ts = 0;
	/* Check अगर adv_ts can be enabled क्रम dwmac 4.x / xgmac core */
	अगर (xmac && priv->dma_cap.aसमय_stamp)
		priv->adv_ts = 1;
	/* Dwmac 3.x core with extend_desc can support adv_ts */
	अन्यथा अगर (priv->extend_desc && priv->dma_cap.aसमय_stamp)
		priv->adv_ts = 1;

	अगर (priv->dma_cap.समय_stamp)
		netdev_info(priv->dev, "IEEE 1588-2002 Timestamp supported\n");

	अगर (priv->adv_ts)
		netdev_info(priv->dev,
			    "IEEE 1588-2008 Advanced Timestamp supported\n");

	priv->hwts_tx_en = 0;
	priv->hwts_rx_en = 0;

	sपंचांगmac_ptp_रेजिस्टर(priv);

	वापस 0;
पूर्ण

अटल व्योम sपंचांगmac_release_ptp(काष्ठा sपंचांगmac_priv *priv)
अणु
	clk_disable_unprepare(priv->plat->clk_ptp_ref);
	sपंचांगmac_ptp_unरेजिस्टर(priv);
पूर्ण

/**
 *  sपंचांगmac_mac_flow_ctrl - Configure flow control in all queues
 *  @priv: driver निजी काष्ठाure
 *  @duplex: duplex passed to the next function
 *  Description: It is used क्रम configuring the flow control in all queues
 */
अटल व्योम sपंचांगmac_mac_flow_ctrl(काष्ठा sपंचांगmac_priv *priv, u32 duplex)
अणु
	u32 tx_cnt = priv->plat->tx_queues_to_use;

	sपंचांगmac_flow_ctrl(priv, priv->hw, duplex, priv->flow_ctrl,
			priv->छोड़ो, tx_cnt);
पूर्ण

अटल व्योम sपंचांगmac_validate(काष्ठा phylink_config *config,
			    अचिन्हित दीर्घ *supported,
			    काष्ठा phylink_link_state *state)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(to_net_dev(config->dev));
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mac_supported) = अणु 0, पूर्ण;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	पूर्णांक tx_cnt = priv->plat->tx_queues_to_use;
	पूर्णांक max_speed = priv->plat->max_speed;

	phylink_set(mac_supported, 10baseT_Half);
	phylink_set(mac_supported, 10baseT_Full);
	phylink_set(mac_supported, 100baseT_Half);
	phylink_set(mac_supported, 100baseT_Full);
	phylink_set(mac_supported, 1000baseT_Half);
	phylink_set(mac_supported, 1000baseT_Full);
	phylink_set(mac_supported, 1000baseKX_Full);

	phylink_set(mac_supported, Autoneg);
	phylink_set(mac_supported, Pause);
	phylink_set(mac_supported, Asym_Pause);
	phylink_set_port_modes(mac_supported);

	/* Cut करोwn 1G अगर asked to */
	अगर ((max_speed > 0) && (max_speed < 1000)) अणु
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseX_Full);
	पूर्ण अन्यथा अगर (priv->plat->has_xgmac) अणु
		अगर (!max_speed || (max_speed >= 2500)) अणु
			phylink_set(mac_supported, 2500baseT_Full);
			phylink_set(mac_supported, 2500baseX_Full);
		पूर्ण
		अगर (!max_speed || (max_speed >= 5000)) अणु
			phylink_set(mac_supported, 5000baseT_Full);
		पूर्ण
		अगर (!max_speed || (max_speed >= 10000)) अणु
			phylink_set(mac_supported, 10000baseSR_Full);
			phylink_set(mac_supported, 10000baseLR_Full);
			phylink_set(mac_supported, 10000baseER_Full);
			phylink_set(mac_supported, 10000baseLRM_Full);
			phylink_set(mac_supported, 10000baseT_Full);
			phylink_set(mac_supported, 10000baseKX4_Full);
			phylink_set(mac_supported, 10000baseKR_Full);
		पूर्ण
		अगर (!max_speed || (max_speed >= 25000)) अणु
			phylink_set(mac_supported, 25000baseCR_Full);
			phylink_set(mac_supported, 25000baseKR_Full);
			phylink_set(mac_supported, 25000baseSR_Full);
		पूर्ण
		अगर (!max_speed || (max_speed >= 40000)) अणु
			phylink_set(mac_supported, 40000baseKR4_Full);
			phylink_set(mac_supported, 40000baseCR4_Full);
			phylink_set(mac_supported, 40000baseSR4_Full);
			phylink_set(mac_supported, 40000baseLR4_Full);
		पूर्ण
		अगर (!max_speed || (max_speed >= 50000)) अणु
			phylink_set(mac_supported, 50000baseCR2_Full);
			phylink_set(mac_supported, 50000baseKR2_Full);
			phylink_set(mac_supported, 50000baseSR2_Full);
			phylink_set(mac_supported, 50000baseKR_Full);
			phylink_set(mac_supported, 50000baseSR_Full);
			phylink_set(mac_supported, 50000baseCR_Full);
			phylink_set(mac_supported, 50000baseLR_ER_FR_Full);
			phylink_set(mac_supported, 50000baseDR_Full);
		पूर्ण
		अगर (!max_speed || (max_speed >= 100000)) अणु
			phylink_set(mac_supported, 100000baseKR4_Full);
			phylink_set(mac_supported, 100000baseSR4_Full);
			phylink_set(mac_supported, 100000baseCR4_Full);
			phylink_set(mac_supported, 100000baseLR4_ER4_Full);
			phylink_set(mac_supported, 100000baseKR2_Full);
			phylink_set(mac_supported, 100000baseSR2_Full);
			phylink_set(mac_supported, 100000baseCR2_Full);
			phylink_set(mac_supported, 100000baseLR2_ER2_FR2_Full);
			phylink_set(mac_supported, 100000baseDR2_Full);
		पूर्ण
	पूर्ण

	/* Half-Duplex can only work with single queue */
	अगर (tx_cnt > 1) अणु
		phylink_set(mask, 10baseT_Half);
		phylink_set(mask, 100baseT_Half);
		phylink_set(mask, 1000baseT_Half);
	पूर्ण

	linkmode_and(supported, supported, mac_supported);
	linkmode_andnot(supported, supported, mask);

	linkmode_and(state->advertising, state->advertising, mac_supported);
	linkmode_andnot(state->advertising, state->advertising, mask);

	/* If PCS is supported, check which modes it supports. */
	sपंचांगmac_xpcs_validate(priv, &priv->hw->xpcs_args, supported, state);
पूर्ण

अटल व्योम sपंचांगmac_mac_pcs_get_state(काष्ठा phylink_config *config,
				     काष्ठा phylink_link_state *state)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(to_net_dev(config->dev));

	state->link = 0;
	sपंचांगmac_xpcs_get_state(priv, &priv->hw->xpcs_args, state);
पूर्ण

अटल व्योम sपंचांगmac_mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			      स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(to_net_dev(config->dev));

	sपंचांगmac_xpcs_config(priv, &priv->hw->xpcs_args, state);
पूर्ण

अटल व्योम sपंचांगmac_mac_an_restart(काष्ठा phylink_config *config)
अणु
	/* Not Supported */
पूर्ण

अटल व्योम sपंचांगmac_fpe_link_state_handle(काष्ठा sपंचांगmac_priv *priv, bool is_up)
अणु
	काष्ठा sपंचांगmac_fpe_cfg *fpe_cfg = priv->plat->fpe_cfg;
	क्रमागत sपंचांगmac_fpe_state *lo_state = &fpe_cfg->lo_fpe_state;
	क्रमागत sपंचांगmac_fpe_state *lp_state = &fpe_cfg->lp_fpe_state;
	bool *hs_enable = &fpe_cfg->hs_enable;

	अगर (is_up && *hs_enable) अणु
		sपंचांगmac_fpe_send_mpacket(priv, priv->ioaddr, MPACKET_VERIFY);
	पूर्ण अन्यथा अणु
		*lo_state = FPE_EVENT_UNKNOWN;
		*lp_state = FPE_EVENT_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_mac_link_करोwn(काष्ठा phylink_config *config,
				 अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(to_net_dev(config->dev));

	sपंचांगmac_mac_set(priv, priv->ioaddr, false);
	priv->eee_active = false;
	priv->tx_lpi_enabled = false;
	sपंचांगmac_eee_init(priv);
	sपंचांगmac_set_eee_pls(priv, priv->hw, false);

	अगर (priv->dma_cap.fpesel)
		sपंचांगmac_fpe_link_state_handle(priv, false);
पूर्ण

अटल व्योम sपंचांगmac_mac_link_up(काष्ठा phylink_config *config,
			       काष्ठा phy_device *phy,
			       अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
			       पूर्णांक speed, पूर्णांक duplex,
			       bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(to_net_dev(config->dev));
	u32 ctrl;

	sपंचांगmac_xpcs_link_up(priv, &priv->hw->xpcs_args, speed, पूर्णांकerface);

	ctrl = पढ़ोl(priv->ioaddr + MAC_CTRL_REG);
	ctrl &= ~priv->hw->link.speed_mask;

	अगर (पूर्णांकerface == PHY_INTERFACE_MODE_USXGMII) अणु
		चयन (speed) अणु
		हाल SPEED_10000:
			ctrl |= priv->hw->link.xgmii.speed10000;
			अवरोध;
		हाल SPEED_5000:
			ctrl |= priv->hw->link.xgmii.speed5000;
			अवरोध;
		हाल SPEED_2500:
			ctrl |= priv->hw->link.xgmii.speed2500;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांकerface == PHY_INTERFACE_MODE_XLGMII) अणु
		चयन (speed) अणु
		हाल SPEED_100000:
			ctrl |= priv->hw->link.xlgmii.speed100000;
			अवरोध;
		हाल SPEED_50000:
			ctrl |= priv->hw->link.xlgmii.speed50000;
			अवरोध;
		हाल SPEED_40000:
			ctrl |= priv->hw->link.xlgmii.speed40000;
			अवरोध;
		हाल SPEED_25000:
			ctrl |= priv->hw->link.xlgmii.speed25000;
			अवरोध;
		हाल SPEED_10000:
			ctrl |= priv->hw->link.xgmii.speed10000;
			अवरोध;
		हाल SPEED_2500:
			ctrl |= priv->hw->link.speed2500;
			अवरोध;
		हाल SPEED_1000:
			ctrl |= priv->hw->link.speed1000;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (speed) अणु
		हाल SPEED_2500:
			ctrl |= priv->hw->link.speed2500;
			अवरोध;
		हाल SPEED_1000:
			ctrl |= priv->hw->link.speed1000;
			अवरोध;
		हाल SPEED_100:
			ctrl |= priv->hw->link.speed100;
			अवरोध;
		हाल SPEED_10:
			ctrl |= priv->hw->link.speed10;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण

	priv->speed = speed;

	अगर (priv->plat->fix_mac_speed)
		priv->plat->fix_mac_speed(priv->plat->bsp_priv, speed);

	अगर (!duplex)
		ctrl &= ~priv->hw->link.duplex;
	अन्यथा
		ctrl |= priv->hw->link.duplex;

	/* Flow Control operation */
	अगर (tx_छोड़ो && rx_छोड़ो)
		sपंचांगmac_mac_flow_ctrl(priv, duplex);

	ग_लिखोl(ctrl, priv->ioaddr + MAC_CTRL_REG);

	sपंचांगmac_mac_set(priv, priv->ioaddr, true);
	अगर (phy && priv->dma_cap.eee) अणु
		priv->eee_active = phy_init_eee(phy, 1) >= 0;
		priv->eee_enabled = sपंचांगmac_eee_init(priv);
		priv->tx_lpi_enabled = priv->eee_enabled;
		sपंचांगmac_set_eee_pls(priv, priv->hw, true);
	पूर्ण

	अगर (priv->dma_cap.fpesel)
		sपंचांगmac_fpe_link_state_handle(priv, true);
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops sपंचांगmac_phylink_mac_ops = अणु
	.validate = sपंचांगmac_validate,
	.mac_pcs_get_state = sपंचांगmac_mac_pcs_get_state,
	.mac_config = sपंचांगmac_mac_config,
	.mac_an_restart = sपंचांगmac_mac_an_restart,
	.mac_link_करोwn = sपंचांगmac_mac_link_करोwn,
	.mac_link_up = sपंचांगmac_mac_link_up,
पूर्ण;

/**
 * sपंचांगmac_check_pcs_mode - verअगरy अगर RGMII/SGMII is supported
 * @priv: driver निजी काष्ठाure
 * Description: this is to verअगरy अगर the HW supports the PCS.
 * Physical Coding Sublayer (PCS) पूर्णांकerface that can be used when the MAC is
 * configured क्रम the TBI, RTBI, or SGMII PHY पूर्णांकerface.
 */
अटल व्योम sपंचांगmac_check_pcs_mode(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक पूर्णांकerface = priv->plat->पूर्णांकerface;

	अगर (priv->dma_cap.pcs) अणु
		अगर ((पूर्णांकerface == PHY_INTERFACE_MODE_RGMII) ||
		    (पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID) ||
		    (पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) ||
		    (पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)) अणु
			netdev_dbg(priv->dev, "PCS RGMII support enabled\n");
			priv->hw->pcs = STMMAC_PCS_RGMII;
		पूर्ण अन्यथा अगर (पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
			netdev_dbg(priv->dev, "PCS SGMII support enabled\n");
			priv->hw->pcs = STMMAC_PCS_SGMII;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_init_phy - PHY initialization
 * @dev: net device काष्ठाure
 * Description: it initializes the driver's PHY state, and attaches the PHY
 * to the mac driver.
 *  Return value:
 *  0 on success
 */
अटल पूर्णांक sपंचांगmac_init_phy(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	काष्ठा device_node *node;
	पूर्णांक ret;

	node = priv->plat->phylink_node;

	अगर (node)
		ret = phylink_of_phy_connect(priv->phylink, node, 0);

	/* Some DT bindings करो not set-up the PHY handle. Let's try to
	 * manually parse it
	 */
	अगर (!node || ret) अणु
		पूर्णांक addr = priv->plat->phy_addr;
		काष्ठा phy_device *phydev;

		phydev = mdiobus_get_phy(priv->mii, addr);
		अगर (!phydev) अणु
			netdev_err(priv->dev, "no phy at addr %d\n", addr);
			वापस -ENODEV;
		पूर्ण

		ret = phylink_connect_phy(priv->phylink, phydev);
	पूर्ण

	अगर (!priv->plat->pmt) अणु
		काष्ठा ethtool_wolinfo wol = अणु .cmd = ETHTOOL_GWOL पूर्ण;

		phylink_ethtool_get_wol(priv->phylink, &wol);
		device_set_wakeup_capable(priv->device, !!wol.supported);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_phy_setup(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा fwnode_handle *fwnode = of_fwnode_handle(priv->plat->phylink_node);
	पूर्णांक mode = priv->plat->phy_पूर्णांकerface;
	काष्ठा phylink *phylink;

	priv->phylink_config.dev = &priv->dev->dev;
	priv->phylink_config.type = PHYLINK_NETDEV;
	priv->phylink_config.pcs_poll = true;
	अगर (priv->plat->mdio_bus_data)
		priv->phylink_config.ovr_an_inband =
			priv->plat->mdio_bus_data->xpcs_an_inband;

	अगर (!fwnode)
		fwnode = dev_fwnode(priv->device);

	phylink = phylink_create(&priv->phylink_config, fwnode,
				 mode, &sपंचांगmac_phylink_mac_ops);
	अगर (IS_ERR(phylink))
		वापस PTR_ERR(phylink);

	priv->phylink = phylink;
	वापस 0;
पूर्ण

अटल व्योम sपंचांगmac_display_rx_rings(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	अचिन्हित पूर्णांक desc_size;
	व्योम *head_rx;
	u32 queue;

	/* Display RX rings */
	क्रम (queue = 0; queue < rx_cnt; queue++) अणु
		काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];

		pr_info("\tRX Queue %u rings\n", queue);

		अगर (priv->extend_desc) अणु
			head_rx = (व्योम *)rx_q->dma_erx;
			desc_size = माप(काष्ठा dma_extended_desc);
		पूर्ण अन्यथा अणु
			head_rx = (व्योम *)rx_q->dma_rx;
			desc_size = माप(काष्ठा dma_desc);
		पूर्ण

		/* Display RX ring */
		sपंचांगmac_display_ring(priv, head_rx, priv->dma_rx_size, true,
				    rx_q->dma_rx_phy, desc_size);
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_display_tx_rings(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	अचिन्हित पूर्णांक desc_size;
	व्योम *head_tx;
	u32 queue;

	/* Display TX rings */
	क्रम (queue = 0; queue < tx_cnt; queue++) अणु
		काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];

		pr_info("\tTX Queue %d rings\n", queue);

		अगर (priv->extend_desc) अणु
			head_tx = (व्योम *)tx_q->dma_etx;
			desc_size = माप(काष्ठा dma_extended_desc);
		पूर्ण अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL) अणु
			head_tx = (व्योम *)tx_q->dma_entx;
			desc_size = माप(काष्ठा dma_edesc);
		पूर्ण अन्यथा अणु
			head_tx = (व्योम *)tx_q->dma_tx;
			desc_size = माप(काष्ठा dma_desc);
		पूर्ण

		sपंचांगmac_display_ring(priv, head_tx, priv->dma_tx_size, false,
				    tx_q->dma_tx_phy, desc_size);
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_display_rings(काष्ठा sपंचांगmac_priv *priv)
अणु
	/* Display RX ring */
	sपंचांगmac_display_rx_rings(priv);

	/* Display TX ring */
	sपंचांगmac_display_tx_rings(priv);
पूर्ण

अटल पूर्णांक sपंचांगmac_set_bfsize(पूर्णांक mtu, पूर्णांक bufsize)
अणु
	पूर्णांक ret = bufsize;

	अगर (mtu >= BUF_SIZE_8KiB)
		ret = BUF_SIZE_16KiB;
	अन्यथा अगर (mtu >= BUF_SIZE_4KiB)
		ret = BUF_SIZE_8KiB;
	अन्यथा अगर (mtu >= BUF_SIZE_2KiB)
		ret = BUF_SIZE_4KiB;
	अन्यथा अगर (mtu > DEFAULT_बफ_मानE)
		ret = BUF_SIZE_2KiB;
	अन्यथा
		ret = DEFAULT_बफ_मानE;

	वापस ret;
पूर्ण

/**
 * sपंचांगmac_clear_rx_descriptors - clear RX descriptors
 * @priv: driver निजी काष्ठाure
 * @queue: RX queue index
 * Description: this function is called to clear the RX descriptors
 * in हाल of both basic and extended descriptors are used.
 */
अटल व्योम sपंचांगmac_clear_rx_descriptors(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	पूर्णांक i;

	/* Clear the RX descriptors */
	क्रम (i = 0; i < priv->dma_rx_size; i++)
		अगर (priv->extend_desc)
			sपंचांगmac_init_rx_desc(priv, &rx_q->dma_erx[i].basic,
					priv->use_riwt, priv->mode,
					(i == priv->dma_rx_size - 1),
					priv->dma_buf_sz);
		अन्यथा
			sपंचांगmac_init_rx_desc(priv, &rx_q->dma_rx[i],
					priv->use_riwt, priv->mode,
					(i == priv->dma_rx_size - 1),
					priv->dma_buf_sz);
पूर्ण

/**
 * sपंचांगmac_clear_tx_descriptors - clear tx descriptors
 * @priv: driver निजी काष्ठाure
 * @queue: TX queue index.
 * Description: this function is called to clear the TX descriptors
 * in हाल of both basic and extended descriptors are used.
 */
अटल व्योम sपंचांगmac_clear_tx_descriptors(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	पूर्णांक i;

	/* Clear the TX descriptors */
	क्रम (i = 0; i < priv->dma_tx_size; i++) अणु
		पूर्णांक last = (i == (priv->dma_tx_size - 1));
		काष्ठा dma_desc *p;

		अगर (priv->extend_desc)
			p = &tx_q->dma_etx[i].basic;
		अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			p = &tx_q->dma_entx[i].basic;
		अन्यथा
			p = &tx_q->dma_tx[i];

		sपंचांगmac_init_tx_desc(priv, p, priv->mode, last);
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_clear_descriptors - clear descriptors
 * @priv: driver निजी काष्ठाure
 * Description: this function is called to clear the TX and RX descriptors
 * in हाल of both basic and extended descriptors are used.
 */
अटल व्योम sपंचांगmac_clear_descriptors(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queue_cnt = priv->plat->rx_queues_to_use;
	u32 tx_queue_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	/* Clear the RX descriptors */
	क्रम (queue = 0; queue < rx_queue_cnt; queue++)
		sपंचांगmac_clear_rx_descriptors(priv, queue);

	/* Clear the TX descriptors */
	क्रम (queue = 0; queue < tx_queue_cnt; queue++)
		sपंचांगmac_clear_tx_descriptors(priv, queue);
पूर्ण

/**
 * sपंचांगmac_init_rx_buffers - init the RX descriptor buffer.
 * @priv: driver निजी काष्ठाure
 * @p: descriptor poपूर्णांकer
 * @i: descriptor index
 * @flags: gfp flag
 * @queue: RX queue index
 * Description: this function is called to allocate a receive buffer, perक्रमm
 * the DMA mapping and init the descriptor.
 */
अटल पूर्णांक sपंचांगmac_init_rx_buffers(काष्ठा sपंचांगmac_priv *priv, काष्ठा dma_desc *p,
				  पूर्णांक i, gfp_t flags, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	काष्ठा sपंचांगmac_rx_buffer *buf = &rx_q->buf_pool[i];

	अगर (!buf->page) अणु
		buf->page = page_pool_dev_alloc_pages(rx_q->page_pool);
		अगर (!buf->page)
			वापस -ENOMEM;
		buf->page_offset = sपंचांगmac_rx_offset(priv);
	पूर्ण

	अगर (priv->sph && !buf->sec_page) अणु
		buf->sec_page = page_pool_dev_alloc_pages(rx_q->page_pool);
		अगर (!buf->sec_page)
			वापस -ENOMEM;

		buf->sec_addr = page_pool_get_dma_addr(buf->sec_page);
		sपंचांगmac_set_desc_sec_addr(priv, p, buf->sec_addr, true);
	पूर्ण अन्यथा अणु
		buf->sec_page = शून्य;
		sपंचांगmac_set_desc_sec_addr(priv, p, buf->sec_addr, false);
	पूर्ण

	buf->addr = page_pool_get_dma_addr(buf->page) + buf->page_offset;

	sपंचांगmac_set_desc_addr(priv, p, buf->addr);
	अगर (priv->dma_buf_sz == BUF_SIZE_16KiB)
		sपंचांगmac_init_desc3(priv, p);

	वापस 0;
पूर्ण

/**
 * sपंचांगmac_मुक्त_rx_buffer - मुक्त RX dma buffers
 * @priv: निजी काष्ठाure
 * @queue: RX queue index
 * @i: buffer index.
 */
अटल व्योम sपंचांगmac_मुक्त_rx_buffer(काष्ठा sपंचांगmac_priv *priv, u32 queue, पूर्णांक i)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	काष्ठा sपंचांगmac_rx_buffer *buf = &rx_q->buf_pool[i];

	अगर (buf->page)
		page_pool_put_full_page(rx_q->page_pool, buf->page, false);
	buf->page = शून्य;

	अगर (buf->sec_page)
		page_pool_put_full_page(rx_q->page_pool, buf->sec_page, false);
	buf->sec_page = शून्य;
पूर्ण

/**
 * sपंचांगmac_मुक्त_tx_buffer - मुक्त RX dma buffers
 * @priv: निजी काष्ठाure
 * @queue: RX queue index
 * @i: buffer index.
 */
अटल व्योम sपंचांगmac_मुक्त_tx_buffer(काष्ठा sपंचांगmac_priv *priv, u32 queue, पूर्णांक i)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];

	अगर (tx_q->tx_skbuff_dma[i].buf &&
	    tx_q->tx_skbuff_dma[i].buf_type != STMMAC_TXBUF_T_XDP_TX) अणु
		अगर (tx_q->tx_skbuff_dma[i].map_as_page)
			dma_unmap_page(priv->device,
				       tx_q->tx_skbuff_dma[i].buf,
				       tx_q->tx_skbuff_dma[i].len,
				       DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(priv->device,
					 tx_q->tx_skbuff_dma[i].buf,
					 tx_q->tx_skbuff_dma[i].len,
					 DMA_TO_DEVICE);
	पूर्ण

	अगर (tx_q->xdpf[i] &&
	    (tx_q->tx_skbuff_dma[i].buf_type == STMMAC_TXBUF_T_XDP_TX ||
	     tx_q->tx_skbuff_dma[i].buf_type == STMMAC_TXBUF_T_XDP_NDO)) अणु
		xdp_वापस_frame(tx_q->xdpf[i]);
		tx_q->xdpf[i] = शून्य;
	पूर्ण

	अगर (tx_q->tx_skbuff_dma[i].buf_type == STMMAC_TXBUF_T_XSK_TX)
		tx_q->xsk_frames_करोne++;

	अगर (tx_q->tx_skbuff[i] &&
	    tx_q->tx_skbuff_dma[i].buf_type == STMMAC_TXBUF_T_SKB) अणु
		dev_kमुक्त_skb_any(tx_q->tx_skbuff[i]);
		tx_q->tx_skbuff[i] = शून्य;
	पूर्ण

	tx_q->tx_skbuff_dma[i].buf = 0;
	tx_q->tx_skbuff_dma[i].map_as_page = false;
पूर्ण

/**
 * dma_मुक्त_rx_skbufs - मुक्त RX dma buffers
 * @priv: निजी काष्ठाure
 * @queue: RX queue index
 */
अटल व्योम dma_मुक्त_rx_skbufs(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->dma_rx_size; i++)
		sपंचांगmac_मुक्त_rx_buffer(priv, queue, i);
पूर्ण

अटल पूर्णांक sपंचांगmac_alloc_rx_buffers(काष्ठा sपंचांगmac_priv *priv, u32 queue,
				   gfp_t flags)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	पूर्णांक i;

	क्रम (i = 0; i < priv->dma_rx_size; i++) अणु
		काष्ठा dma_desc *p;
		पूर्णांक ret;

		अगर (priv->extend_desc)
			p = &((rx_q->dma_erx + i)->basic);
		अन्यथा
			p = rx_q->dma_rx + i;

		ret = sपंचांगmac_init_rx_buffers(priv, p, i, flags,
					     queue);
		अगर (ret)
			वापस ret;

		rx_q->buf_alloc_num++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dma_मुक्त_rx_xskbufs - मुक्त RX dma buffers from XSK pool
 * @priv: निजी काष्ठाure
 * @queue: RX queue index
 */
अटल व्योम dma_मुक्त_rx_xskbufs(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	पूर्णांक i;

	क्रम (i = 0; i < priv->dma_rx_size; i++) अणु
		काष्ठा sपंचांगmac_rx_buffer *buf = &rx_q->buf_pool[i];

		अगर (!buf->xdp)
			जारी;

		xsk_buff_मुक्त(buf->xdp);
		buf->xdp = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_alloc_rx_buffers_zc(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	पूर्णांक i;

	क्रम (i = 0; i < priv->dma_rx_size; i++) अणु
		काष्ठा sपंचांगmac_rx_buffer *buf;
		dma_addr_t dma_addr;
		काष्ठा dma_desc *p;

		अगर (priv->extend_desc)
			p = (काष्ठा dma_desc *)(rx_q->dma_erx + i);
		अन्यथा
			p = rx_q->dma_rx + i;

		buf = &rx_q->buf_pool[i];

		buf->xdp = xsk_buff_alloc(rx_q->xsk_pool);
		अगर (!buf->xdp)
			वापस -ENOMEM;

		dma_addr = xsk_buff_xdp_get_dma(buf->xdp);
		sपंचांगmac_set_desc_addr(priv, p, dma_addr);
		rx_q->buf_alloc_num++;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xsk_buff_pool *sपंचांगmac_get_xsk_pool(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	अगर (!sपंचांगmac_xdp_is_enabled(priv) || !test_bit(queue, priv->af_xdp_zc_qps))
		वापस शून्य;

	वापस xsk_get_pool_from_qid(priv->dev, queue);
पूर्ण

/**
 * __init_dma_rx_desc_rings - init the RX descriptor ring (per queue)
 * @priv: driver निजी काष्ठाure
 * @queue: RX queue index
 * @flags: gfp flag.
 * Description: this function initializes the DMA RX descriptors
 * and allocates the socket buffers. It supports the chained and ring
 * modes.
 */
अटल पूर्णांक __init_dma_rx_desc_rings(काष्ठा sपंचांगmac_priv *priv, u32 queue, gfp_t flags)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	पूर्णांक ret;

	netअगर_dbg(priv, probe, priv->dev,
		  "(%s) dma_rx_phy=0x%08x\n", __func__,
		  (u32)rx_q->dma_rx_phy);

	sपंचांगmac_clear_rx_descriptors(priv, queue);

	xdp_rxq_info_unreg_mem_model(&rx_q->xdp_rxq);

	rx_q->xsk_pool = sपंचांगmac_get_xsk_pool(priv, queue);

	अगर (rx_q->xsk_pool) अणु
		WARN_ON(xdp_rxq_info_reg_mem_model(&rx_q->xdp_rxq,
						   MEM_TYPE_XSK_BUFF_POOL,
						   शून्य));
		netdev_info(priv->dev,
			    "Register MEM_TYPE_XSK_BUFF_POOL RxQ-%d\n",
			    rx_q->queue_index);
		xsk_pool_set_rxq_info(rx_q->xsk_pool, &rx_q->xdp_rxq);
	पूर्ण अन्यथा अणु
		WARN_ON(xdp_rxq_info_reg_mem_model(&rx_q->xdp_rxq,
						   MEM_TYPE_PAGE_POOL,
						   rx_q->page_pool));
		netdev_info(priv->dev,
			    "Register MEM_TYPE_PAGE_POOL RxQ-%d\n",
			    rx_q->queue_index);
	पूर्ण

	अगर (rx_q->xsk_pool) अणु
		/* RX XDP ZC buffer pool may not be populated, e.g.
		 * xdpsock TX-only.
		 */
		sपंचांगmac_alloc_rx_buffers_zc(priv, queue);
	पूर्ण अन्यथा अणु
		ret = sपंचांगmac_alloc_rx_buffers(priv, queue, flags);
		अगर (ret < 0)
			वापस -ENOMEM;
	पूर्ण

	rx_q->cur_rx = 0;
	rx_q->dirty_rx = 0;

	/* Setup the chained descriptor addresses */
	अगर (priv->mode == STMMAC_CHAIN_MODE) अणु
		अगर (priv->extend_desc)
			sपंचांगmac_mode_init(priv, rx_q->dma_erx,
					 rx_q->dma_rx_phy,
					 priv->dma_rx_size, 1);
		अन्यथा
			sपंचांगmac_mode_init(priv, rx_q->dma_rx,
					 rx_q->dma_rx_phy,
					 priv->dma_rx_size, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_dma_rx_desc_rings(काष्ठा net_device *dev, gfp_t flags)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 rx_count = priv->plat->rx_queues_to_use;
	u32 queue;
	पूर्णांक ret;

	/* RX INITIALIZATION */
	netअगर_dbg(priv, probe, priv->dev,
		  "SKB addresses:\nskb\t\tskb data\tdma data\n");

	क्रम (queue = 0; queue < rx_count; queue++) अणु
		ret = __init_dma_rx_desc_rings(priv, queue, flags);
		अगर (ret)
			जाओ err_init_rx_buffers;
	पूर्ण

	वापस 0;

err_init_rx_buffers:
	जबतक (queue >= 0) अणु
		काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];

		अगर (rx_q->xsk_pool)
			dma_मुक्त_rx_xskbufs(priv, queue);
		अन्यथा
			dma_मुक्त_rx_skbufs(priv, queue);

		rx_q->buf_alloc_num = 0;
		rx_q->xsk_pool = शून्य;

		अगर (queue == 0)
			अवरोध;

		queue--;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * __init_dma_tx_desc_rings - init the TX descriptor ring (per queue)
 * @priv: driver निजी काष्ठाure
 * @queue : TX queue index
 * Description: this function initializes the DMA TX descriptors
 * and allocates the socket buffers. It supports the chained and ring
 * modes.
 */
अटल पूर्णांक __init_dma_tx_desc_rings(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	पूर्णांक i;

	netअगर_dbg(priv, probe, priv->dev,
		  "(%s) dma_tx_phy=0x%08x\n", __func__,
		  (u32)tx_q->dma_tx_phy);

	/* Setup the chained descriptor addresses */
	अगर (priv->mode == STMMAC_CHAIN_MODE) अणु
		अगर (priv->extend_desc)
			sपंचांगmac_mode_init(priv, tx_q->dma_etx,
					 tx_q->dma_tx_phy,
					 priv->dma_tx_size, 1);
		अन्यथा अगर (!(tx_q->tbs & STMMAC_TBS_AVAIL))
			sपंचांगmac_mode_init(priv, tx_q->dma_tx,
					 tx_q->dma_tx_phy,
					 priv->dma_tx_size, 0);
	पूर्ण

	tx_q->xsk_pool = sपंचांगmac_get_xsk_pool(priv, queue);

	क्रम (i = 0; i < priv->dma_tx_size; i++) अणु
		काष्ठा dma_desc *p;

		अगर (priv->extend_desc)
			p = &((tx_q->dma_etx + i)->basic);
		अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			p = &((tx_q->dma_entx + i)->basic);
		अन्यथा
			p = tx_q->dma_tx + i;

		sपंचांगmac_clear_desc(priv, p);

		tx_q->tx_skbuff_dma[i].buf = 0;
		tx_q->tx_skbuff_dma[i].map_as_page = false;
		tx_q->tx_skbuff_dma[i].len = 0;
		tx_q->tx_skbuff_dma[i].last_segment = false;
		tx_q->tx_skbuff[i] = शून्य;
	पूर्ण

	tx_q->dirty_tx = 0;
	tx_q->cur_tx = 0;
	tx_q->mss = 0;

	netdev_tx_reset_queue(netdev_get_tx_queue(priv->dev, queue));

	वापस 0;
पूर्ण

अटल पूर्णांक init_dma_tx_desc_rings(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 tx_queue_cnt;
	u32 queue;

	tx_queue_cnt = priv->plat->tx_queues_to_use;

	क्रम (queue = 0; queue < tx_queue_cnt; queue++)
		__init_dma_tx_desc_rings(priv, queue);

	वापस 0;
पूर्ण

/**
 * init_dma_desc_rings - init the RX/TX descriptor rings
 * @dev: net device काष्ठाure
 * @flags: gfp flag.
 * Description: this function initializes the DMA RX/TX descriptors
 * and allocates the socket buffers. It supports the chained and ring
 * modes.
 */
अटल पूर्णांक init_dma_desc_rings(काष्ठा net_device *dev, gfp_t flags)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	ret = init_dma_rx_desc_rings(dev, flags);
	अगर (ret)
		वापस ret;

	ret = init_dma_tx_desc_rings(dev);

	sपंचांगmac_clear_descriptors(priv);

	अगर (netअगर_msg_hw(priv))
		sपंचांगmac_display_rings(priv);

	वापस ret;
पूर्ण

/**
 * dma_मुक्त_tx_skbufs - मुक्त TX dma buffers
 * @priv: निजी काष्ठाure
 * @queue: TX queue index
 */
अटल व्योम dma_मुक्त_tx_skbufs(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	पूर्णांक i;

	tx_q->xsk_frames_करोne = 0;

	क्रम (i = 0; i < priv->dma_tx_size; i++)
		sपंचांगmac_मुक्त_tx_buffer(priv, queue, i);

	अगर (tx_q->xsk_pool && tx_q->xsk_frames_करोne) अणु
		xsk_tx_completed(tx_q->xsk_pool, tx_q->xsk_frames_करोne);
		tx_q->xsk_frames_करोne = 0;
		tx_q->xsk_pool = शून्य;
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_मुक्त_tx_skbufs - मुक्त TX skb buffers
 * @priv: निजी काष्ठाure
 */
अटल व्योम sपंचांगmac_मुक्त_tx_skbufs(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_queue_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	क्रम (queue = 0; queue < tx_queue_cnt; queue++)
		dma_मुक्त_tx_skbufs(priv, queue);
पूर्ण

/**
 * __मुक्त_dma_rx_desc_resources - मुक्त RX dma desc resources (per queue)
 * @priv: निजी काष्ठाure
 * @queue: RX queue index
 */
अटल व्योम __मुक्त_dma_rx_desc_resources(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];

	/* Release the DMA RX socket buffers */
	अगर (rx_q->xsk_pool)
		dma_मुक्त_rx_xskbufs(priv, queue);
	अन्यथा
		dma_मुक्त_rx_skbufs(priv, queue);

	rx_q->buf_alloc_num = 0;
	rx_q->xsk_pool = शून्य;

	/* Free DMA regions of consistent memory previously allocated */
	अगर (!priv->extend_desc)
		dma_मुक्त_coherent(priv->device, priv->dma_rx_size *
				  माप(काष्ठा dma_desc),
				  rx_q->dma_rx, rx_q->dma_rx_phy);
	अन्यथा
		dma_मुक्त_coherent(priv->device, priv->dma_rx_size *
				  माप(काष्ठा dma_extended_desc),
				  rx_q->dma_erx, rx_q->dma_rx_phy);

	अगर (xdp_rxq_info_is_reg(&rx_q->xdp_rxq))
		xdp_rxq_info_unreg(&rx_q->xdp_rxq);

	kमुक्त(rx_q->buf_pool);
	अगर (rx_q->page_pool)
		page_pool_destroy(rx_q->page_pool);
पूर्ण

अटल व्योम मुक्त_dma_rx_desc_resources(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_count = priv->plat->rx_queues_to_use;
	u32 queue;

	/* Free RX queue resources */
	क्रम (queue = 0; queue < rx_count; queue++)
		__मुक्त_dma_rx_desc_resources(priv, queue);
पूर्ण

/**
 * __मुक्त_dma_tx_desc_resources - मुक्त TX dma desc resources (per queue)
 * @priv: निजी काष्ठाure
 * @queue: TX queue index
 */
अटल व्योम __मुक्त_dma_tx_desc_resources(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	माप_प्रकार size;
	व्योम *addr;

	/* Release the DMA TX socket buffers */
	dma_मुक्त_tx_skbufs(priv, queue);

	अगर (priv->extend_desc) अणु
		size = माप(काष्ठा dma_extended_desc);
		addr = tx_q->dma_etx;
	पूर्ण अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL) अणु
		size = माप(काष्ठा dma_edesc);
		addr = tx_q->dma_entx;
	पूर्ण अन्यथा अणु
		size = माप(काष्ठा dma_desc);
		addr = tx_q->dma_tx;
	पूर्ण

	size *= priv->dma_tx_size;

	dma_मुक्त_coherent(priv->device, size, addr, tx_q->dma_tx_phy);

	kमुक्त(tx_q->tx_skbuff_dma);
	kमुक्त(tx_q->tx_skbuff);
पूर्ण

अटल व्योम मुक्त_dma_tx_desc_resources(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 queue;

	/* Free TX queue resources */
	क्रम (queue = 0; queue < tx_count; queue++)
		__मुक्त_dma_tx_desc_resources(priv, queue);
पूर्ण

/**
 * __alloc_dma_rx_desc_resources - alloc RX resources (per queue).
 * @priv: निजी काष्ठाure
 * @queue: RX queue index
 * Description: according to which descriptor can be used (extend or basic)
 * this function allocates the resources क्रम TX and RX paths. In हाल of
 * reception, क्रम example, it pre-allocated the RX socket buffer in order to
 * allow zero-copy mechanism.
 */
अटल पूर्णांक __alloc_dma_rx_desc_resources(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	bool xdp_prog = sपंचांगmac_xdp_is_enabled(priv);
	काष्ठा page_pool_params pp_params = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक num_pages;
	अचिन्हित पूर्णांक napi_id;
	पूर्णांक ret;

	rx_q->queue_index = queue;
	rx_q->priv_data = priv;

	pp_params.flags = PP_FLAG_DMA_MAP | PP_FLAG_DMA_SYNC_DEV;
	pp_params.pool_size = priv->dma_rx_size;
	num_pages = DIV_ROUND_UP(priv->dma_buf_sz, PAGE_SIZE);
	pp_params.order = ilog2(num_pages);
	pp_params.nid = dev_to_node(priv->device);
	pp_params.dev = priv->device;
	pp_params.dma_dir = xdp_prog ? DMA_BIसूचीECTIONAL : DMA_FROM_DEVICE;
	pp_params.offset = sपंचांगmac_rx_offset(priv);
	pp_params.max_len = STMMAC_MAX_RX_BUF_SIZE(num_pages);

	rx_q->page_pool = page_pool_create(&pp_params);
	अगर (IS_ERR(rx_q->page_pool)) अणु
		ret = PTR_ERR(rx_q->page_pool);
		rx_q->page_pool = शून्य;
		वापस ret;
	पूर्ण

	rx_q->buf_pool = kसुस्मृति(priv->dma_rx_size,
				 माप(*rx_q->buf_pool),
				 GFP_KERNEL);
	अगर (!rx_q->buf_pool)
		वापस -ENOMEM;

	अगर (priv->extend_desc) अणु
		rx_q->dma_erx = dma_alloc_coherent(priv->device,
						   priv->dma_rx_size *
						   माप(काष्ठा dma_extended_desc),
						   &rx_q->dma_rx_phy,
						   GFP_KERNEL);
		अगर (!rx_q->dma_erx)
			वापस -ENOMEM;

	पूर्ण अन्यथा अणु
		rx_q->dma_rx = dma_alloc_coherent(priv->device,
						  priv->dma_rx_size *
						  माप(काष्ठा dma_desc),
						  &rx_q->dma_rx_phy,
						  GFP_KERNEL);
		अगर (!rx_q->dma_rx)
			वापस -ENOMEM;
	पूर्ण

	अगर (sपंचांगmac_xdp_is_enabled(priv) &&
	    test_bit(queue, priv->af_xdp_zc_qps))
		napi_id = ch->rxtx_napi.napi_id;
	अन्यथा
		napi_id = ch->rx_napi.napi_id;

	ret = xdp_rxq_info_reg(&rx_q->xdp_rxq, priv->dev,
			       rx_q->queue_index,
			       napi_id);
	अगर (ret) अणु
		netdev_err(priv->dev, "Failed to register xdp rxq info\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_dma_rx_desc_resources(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_count = priv->plat->rx_queues_to_use;
	u32 queue;
	पूर्णांक ret;

	/* RX queues buffers and DMA */
	क्रम (queue = 0; queue < rx_count; queue++) अणु
		ret = __alloc_dma_rx_desc_resources(priv, queue);
		अगर (ret)
			जाओ err_dma;
	पूर्ण

	वापस 0;

err_dma:
	मुक्त_dma_rx_desc_resources(priv);

	वापस ret;
पूर्ण

/**
 * __alloc_dma_tx_desc_resources - alloc TX resources (per queue).
 * @priv: निजी काष्ठाure
 * @queue: TX queue index
 * Description: according to which descriptor can be used (extend or basic)
 * this function allocates the resources क्रम TX and RX paths. In हाल of
 * reception, क्रम example, it pre-allocated the RX socket buffer in order to
 * allow zero-copy mechanism.
 */
अटल पूर्णांक __alloc_dma_tx_desc_resources(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	माप_प्रकार size;
	व्योम *addr;

	tx_q->queue_index = queue;
	tx_q->priv_data = priv;

	tx_q->tx_skbuff_dma = kसुस्मृति(priv->dma_tx_size,
				      माप(*tx_q->tx_skbuff_dma),
				      GFP_KERNEL);
	अगर (!tx_q->tx_skbuff_dma)
		वापस -ENOMEM;

	tx_q->tx_skbuff = kसुस्मृति(priv->dma_tx_size,
				  माप(काष्ठा sk_buff *),
				  GFP_KERNEL);
	अगर (!tx_q->tx_skbuff)
		वापस -ENOMEM;

	अगर (priv->extend_desc)
		size = माप(काष्ठा dma_extended_desc);
	अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		size = माप(काष्ठा dma_edesc);
	अन्यथा
		size = माप(काष्ठा dma_desc);

	size *= priv->dma_tx_size;

	addr = dma_alloc_coherent(priv->device, size,
				  &tx_q->dma_tx_phy, GFP_KERNEL);
	अगर (!addr)
		वापस -ENOMEM;

	अगर (priv->extend_desc)
		tx_q->dma_etx = addr;
	अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		tx_q->dma_entx = addr;
	अन्यथा
		tx_q->dma_tx = addr;

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_dma_tx_desc_resources(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 queue;
	पूर्णांक ret;

	/* TX queues buffers and DMA */
	क्रम (queue = 0; queue < tx_count; queue++) अणु
		ret = __alloc_dma_tx_desc_resources(priv, queue);
		अगर (ret)
			जाओ err_dma;
	पूर्ण

	वापस 0;

err_dma:
	मुक्त_dma_tx_desc_resources(priv);
	वापस ret;
पूर्ण

/**
 * alloc_dma_desc_resources - alloc TX/RX resources.
 * @priv: निजी काष्ठाure
 * Description: according to which descriptor can be used (extend or basic)
 * this function allocates the resources क्रम TX and RX paths. In हाल of
 * reception, क्रम example, it pre-allocated the RX socket buffer in order to
 * allow zero-copy mechanism.
 */
अटल पूर्णांक alloc_dma_desc_resources(काष्ठा sपंचांगmac_priv *priv)
अणु
	/* RX Allocation */
	पूर्णांक ret = alloc_dma_rx_desc_resources(priv);

	अगर (ret)
		वापस ret;

	ret = alloc_dma_tx_desc_resources(priv);

	वापस ret;
पूर्ण

/**
 * मुक्त_dma_desc_resources - मुक्त dma desc resources
 * @priv: निजी काष्ठाure
 */
अटल व्योम मुक्त_dma_desc_resources(काष्ठा sपंचांगmac_priv *priv)
अणु
	/* Release the DMA TX socket buffers */
	मुक्त_dma_tx_desc_resources(priv);

	/* Release the DMA RX socket buffers later
	 * to ensure all pending XDP_TX buffers are वापसed.
	 */
	मुक्त_dma_rx_desc_resources(priv);
पूर्ण

/**
 *  sपंचांगmac_mac_enable_rx_queues - Enable MAC rx queues
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम enabling the rx queues in the MAC
 */
अटल व्योम sपंचांगmac_mac_enable_rx_queues(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	पूर्णांक queue;
	u8 mode;

	क्रम (queue = 0; queue < rx_queues_count; queue++) अणु
		mode = priv->plat->rx_queues_cfg[queue].mode_to_use;
		sपंचांगmac_rx_queue_enable(priv, priv->hw, mode, queue);
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_start_rx_dma - start RX DMA channel
 * @priv: driver निजी काष्ठाure
 * @chan: RX channel index
 * Description:
 * This starts a RX DMA channel
 */
अटल व्योम sपंचांगmac_start_rx_dma(काष्ठा sपंचांगmac_priv *priv, u32 chan)
अणु
	netdev_dbg(priv->dev, "DMA RX processes started in channel %d\n", chan);
	sपंचांगmac_start_rx(priv, priv->ioaddr, chan);
पूर्ण

/**
 * sपंचांगmac_start_tx_dma - start TX DMA channel
 * @priv: driver निजी काष्ठाure
 * @chan: TX channel index
 * Description:
 * This starts a TX DMA channel
 */
अटल व्योम sपंचांगmac_start_tx_dma(काष्ठा sपंचांगmac_priv *priv, u32 chan)
अणु
	netdev_dbg(priv->dev, "DMA TX processes started in channel %d\n", chan);
	sपंचांगmac_start_tx(priv, priv->ioaddr, chan);
पूर्ण

/**
 * sपंचांगmac_stop_rx_dma - stop RX DMA channel
 * @priv: driver निजी काष्ठाure
 * @chan: RX channel index
 * Description:
 * This stops a RX DMA channel
 */
अटल व्योम sपंचांगmac_stop_rx_dma(काष्ठा sपंचांगmac_priv *priv, u32 chan)
अणु
	netdev_dbg(priv->dev, "DMA RX processes stopped in channel %d\n", chan);
	sपंचांगmac_stop_rx(priv, priv->ioaddr, chan);
पूर्ण

/**
 * sपंचांगmac_stop_tx_dma - stop TX DMA channel
 * @priv: driver निजी काष्ठाure
 * @chan: TX channel index
 * Description:
 * This stops a TX DMA channel
 */
अटल व्योम sपंचांगmac_stop_tx_dma(काष्ठा sपंचांगmac_priv *priv, u32 chan)
अणु
	netdev_dbg(priv->dev, "DMA TX processes stopped in channel %d\n", chan);
	sपंचांगmac_stop_tx(priv, priv->ioaddr, chan);
पूर्ण

/**
 * sपंचांगmac_start_all_dma - start all RX and TX DMA channels
 * @priv: driver निजी काष्ठाure
 * Description:
 * This starts all the RX and TX DMA channels
 */
अटल व्योम sपंचांगmac_start_all_dma(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan = 0;

	क्रम (chan = 0; chan < rx_channels_count; chan++)
		sपंचांगmac_start_rx_dma(priv, chan);

	क्रम (chan = 0; chan < tx_channels_count; chan++)
		sपंचांगmac_start_tx_dma(priv, chan);
पूर्ण

/**
 * sपंचांगmac_stop_all_dma - stop all RX and TX DMA channels
 * @priv: driver निजी काष्ठाure
 * Description:
 * This stops the RX and TX DMA channels
 */
अटल व्योम sपंचांगmac_stop_all_dma(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan = 0;

	क्रम (chan = 0; chan < rx_channels_count; chan++)
		sपंचांगmac_stop_rx_dma(priv, chan);

	क्रम (chan = 0; chan < tx_channels_count; chan++)
		sपंचांगmac_stop_tx_dma(priv, chan);
पूर्ण

/**
 *  sपंचांगmac_dma_operation_mode - HW DMA operation mode
 *  @priv: driver निजी काष्ठाure
 *  Description: it is used क्रम configuring the DMA operation mode रेजिस्टर in
 *  order to program the tx/rx DMA thresholds or Store-And-Forward mode.
 */
अटल व्योम sपंचांगmac_dma_operation_mode(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	पूर्णांक rxfअगरosz = priv->plat->rx_fअगरo_size;
	पूर्णांक txfअगरosz = priv->plat->tx_fअगरo_size;
	u32 txmode = 0;
	u32 rxmode = 0;
	u32 chan = 0;
	u8 qmode = 0;

	अगर (rxfअगरosz == 0)
		rxfअगरosz = priv->dma_cap.rx_fअगरo_size;
	अगर (txfअगरosz == 0)
		txfअगरosz = priv->dma_cap.tx_fअगरo_size;

	/* Adjust क्रम real per queue fअगरo size */
	rxfअगरosz /= rx_channels_count;
	txfअगरosz /= tx_channels_count;

	अगर (priv->plat->क्रमce_thresh_dma_mode) अणु
		txmode = tc;
		rxmode = tc;
	पूर्ण अन्यथा अगर (priv->plat->क्रमce_sf_dma_mode || priv->plat->tx_coe) अणु
		/*
		 * In हाल of GMAC, SF mode can be enabled
		 * to perक्रमm the TX COE in HW. This depends on:
		 * 1) TX COE अगर actually supported
		 * 2) There is no bugged Jumbo frame support
		 *    that needs to not insert csum in the TDES.
		 */
		txmode = SF_DMA_MODE;
		rxmode = SF_DMA_MODE;
		priv->xstats.threshold = SF_DMA_MODE;
	पूर्ण अन्यथा अणु
		txmode = tc;
		rxmode = SF_DMA_MODE;
	पूर्ण

	/* configure all channels */
	क्रम (chan = 0; chan < rx_channels_count; chan++) अणु
		काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[chan];
		u32 buf_size;

		qmode = priv->plat->rx_queues_cfg[chan].mode_to_use;

		sपंचांगmac_dma_rx_mode(priv, priv->ioaddr, rxmode, chan,
				rxfअगरosz, qmode);

		अगर (rx_q->xsk_pool) अणु
			buf_size = xsk_pool_get_rx_frame_size(rx_q->xsk_pool);
			sपंचांगmac_set_dma_bfsize(priv, priv->ioaddr,
					      buf_size,
					      chan);
		पूर्ण अन्यथा अणु
			sपंचांगmac_set_dma_bfsize(priv, priv->ioaddr,
					      priv->dma_buf_sz,
					      chan);
		पूर्ण
	पूर्ण

	क्रम (chan = 0; chan < tx_channels_count; chan++) अणु
		qmode = priv->plat->tx_queues_cfg[chan].mode_to_use;

		sपंचांगmac_dma_tx_mode(priv, priv->ioaddr, txmode, chan,
				txfअगरosz, qmode);
	पूर्ण
पूर्ण

अटल bool sपंचांगmac_xdp_xmit_zc(काष्ठा sपंचांगmac_priv *priv, u32 queue, u32 budget)
अणु
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(priv->dev, queue);
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	काष्ठा xsk_buff_pool *pool = tx_q->xsk_pool;
	अचिन्हित पूर्णांक entry = tx_q->cur_tx;
	काष्ठा dma_desc *tx_desc = शून्य;
	काष्ठा xdp_desc xdp_desc;
	bool work_करोne = true;

	/* Aव्योमs TX समय-out as we are sharing with slow path */
	nq->trans_start = jअगरfies;

	budget = min(budget, sपंचांगmac_tx_avail(priv, queue));

	जबतक (budget-- > 0) अणु
		dma_addr_t dma_addr;
		bool set_ic;

		/* We are sharing with slow path and stop XSK TX desc submission when
		 * available TX ring is less than threshold.
		 */
		अगर (unlikely(sपंचांगmac_tx_avail(priv, queue) < STMMAC_TX_XSK_AVAIL) ||
		    !netअगर_carrier_ok(priv->dev)) अणु
			work_करोne = false;
			अवरोध;
		पूर्ण

		अगर (!xsk_tx_peek_desc(pool, &xdp_desc))
			अवरोध;

		अगर (likely(priv->extend_desc))
			tx_desc = (काष्ठा dma_desc *)(tx_q->dma_etx + entry);
		अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			tx_desc = &tx_q->dma_entx[entry].basic;
		अन्यथा
			tx_desc = tx_q->dma_tx + entry;

		dma_addr = xsk_buff_raw_get_dma(pool, xdp_desc.addr);
		xsk_buff_raw_dma_sync_क्रम_device(pool, dma_addr, xdp_desc.len);

		tx_q->tx_skbuff_dma[entry].buf_type = STMMAC_TXBUF_T_XSK_TX;

		/* To वापस XDP buffer to XSK pool, we simple call
		 * xsk_tx_completed(), so we करोn't need to fill up
		 * 'buf' and 'xdpf'.
		 */
		tx_q->tx_skbuff_dma[entry].buf = 0;
		tx_q->xdpf[entry] = शून्य;

		tx_q->tx_skbuff_dma[entry].map_as_page = false;
		tx_q->tx_skbuff_dma[entry].len = xdp_desc.len;
		tx_q->tx_skbuff_dma[entry].last_segment = true;
		tx_q->tx_skbuff_dma[entry].is_jumbo = false;

		sपंचांगmac_set_desc_addr(priv, tx_desc, dma_addr);

		tx_q->tx_count_frames++;

		अगर (!priv->tx_coal_frames[queue])
			set_ic = false;
		अन्यथा अगर (tx_q->tx_count_frames % priv->tx_coal_frames[queue] == 0)
			set_ic = true;
		अन्यथा
			set_ic = false;

		अगर (set_ic) अणु
			tx_q->tx_count_frames = 0;
			sपंचांगmac_set_tx_ic(priv, tx_desc);
			priv->xstats.tx_set_ic_bit++;
		पूर्ण

		sपंचांगmac_prepare_tx_desc(priv, tx_desc, 1, xdp_desc.len,
				       true, priv->mode, true, true,
				       xdp_desc.len);

		sपंचांगmac_enable_dma_transmission(priv, priv->ioaddr);

		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, priv->dma_tx_size);
		entry = tx_q->cur_tx;
	पूर्ण

	अगर (tx_desc) अणु
		sपंचांगmac_flush_tx_descriptors(priv, queue);
		xsk_tx_release(pool);
	पूर्ण

	/* Return true अगर all of the 3 conditions are met
	 *  a) TX Budget is still available
	 *  b) work_करोne = true when XSK TX desc peek is empty (no more
	 *     pending XSK TX क्रम transmission)
	 */
	वापस !!budget && work_करोne;
पूर्ण

/**
 * sपंचांगmac_tx_clean - to manage the transmission completion
 * @priv: driver निजी काष्ठाure
 * @budget: napi budget limiting this functions packet handling
 * @queue: TX queue index
 * Description: it reclaims the transmit resources after transmission completes.
 */
अटल पूर्णांक sपंचांगmac_tx_clean(काष्ठा sपंचांगmac_priv *priv, पूर्णांक budget, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;
	अचिन्हित पूर्णांक entry, xmits = 0, count = 0;

	__netअगर_tx_lock_bh(netdev_get_tx_queue(priv->dev, queue));

	priv->xstats.tx_clean++;

	tx_q->xsk_frames_करोne = 0;

	entry = tx_q->dirty_tx;

	/* Try to clean all TX complete frame in 1 shot */
	जबतक ((entry != tx_q->cur_tx) && count < priv->dma_tx_size) अणु
		काष्ठा xdp_frame *xdpf;
		काष्ठा sk_buff *skb;
		काष्ठा dma_desc *p;
		पूर्णांक status;

		अगर (tx_q->tx_skbuff_dma[entry].buf_type == STMMAC_TXBUF_T_XDP_TX ||
		    tx_q->tx_skbuff_dma[entry].buf_type == STMMAC_TXBUF_T_XDP_NDO) अणु
			xdpf = tx_q->xdpf[entry];
			skb = शून्य;
		पूर्ण अन्यथा अगर (tx_q->tx_skbuff_dma[entry].buf_type == STMMAC_TXBUF_T_SKB) अणु
			xdpf = शून्य;
			skb = tx_q->tx_skbuff[entry];
		पूर्ण अन्यथा अणु
			xdpf = शून्य;
			skb = शून्य;
		पूर्ण

		अगर (priv->extend_desc)
			p = (काष्ठा dma_desc *)(tx_q->dma_etx + entry);
		अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			p = &tx_q->dma_entx[entry].basic;
		अन्यथा
			p = tx_q->dma_tx + entry;

		status = sपंचांगmac_tx_status(priv, &priv->dev->stats,
				&priv->xstats, p, priv->ioaddr);
		/* Check अगर the descriptor is owned by the DMA */
		अगर (unlikely(status & tx_dma_own))
			अवरोध;

		count++;

		/* Make sure descriptor fields are पढ़ो after पढ़ोing
		 * the own bit.
		 */
		dma_rmb();

		/* Just consider the last segment and ...*/
		अगर (likely(!(status & tx_not_ls))) अणु
			/* ... verअगरy the status error condition */
			अगर (unlikely(status & tx_err)) अणु
				priv->dev->stats.tx_errors++;
			पूर्ण अन्यथा अणु
				priv->dev->stats.tx_packets++;
				priv->xstats.tx_pkt_n++;
			पूर्ण
			अगर (skb)
				sपंचांगmac_get_tx_hwtstamp(priv, p, skb);
		पूर्ण

		अगर (likely(tx_q->tx_skbuff_dma[entry].buf &&
			   tx_q->tx_skbuff_dma[entry].buf_type != STMMAC_TXBUF_T_XDP_TX)) अणु
			अगर (tx_q->tx_skbuff_dma[entry].map_as_page)
				dma_unmap_page(priv->device,
					       tx_q->tx_skbuff_dma[entry].buf,
					       tx_q->tx_skbuff_dma[entry].len,
					       DMA_TO_DEVICE);
			अन्यथा
				dma_unmap_single(priv->device,
						 tx_q->tx_skbuff_dma[entry].buf,
						 tx_q->tx_skbuff_dma[entry].len,
						 DMA_TO_DEVICE);
			tx_q->tx_skbuff_dma[entry].buf = 0;
			tx_q->tx_skbuff_dma[entry].len = 0;
			tx_q->tx_skbuff_dma[entry].map_as_page = false;
		पूर्ण

		sपंचांगmac_clean_desc3(priv, tx_q, p);

		tx_q->tx_skbuff_dma[entry].last_segment = false;
		tx_q->tx_skbuff_dma[entry].is_jumbo = false;

		अगर (xdpf &&
		    tx_q->tx_skbuff_dma[entry].buf_type == STMMAC_TXBUF_T_XDP_TX) अणु
			xdp_वापस_frame_rx_napi(xdpf);
			tx_q->xdpf[entry] = शून्य;
		पूर्ण

		अगर (xdpf &&
		    tx_q->tx_skbuff_dma[entry].buf_type == STMMAC_TXBUF_T_XDP_NDO) अणु
			xdp_वापस_frame(xdpf);
			tx_q->xdpf[entry] = शून्य;
		पूर्ण

		अगर (tx_q->tx_skbuff_dma[entry].buf_type == STMMAC_TXBUF_T_XSK_TX)
			tx_q->xsk_frames_करोne++;

		अगर (tx_q->tx_skbuff_dma[entry].buf_type == STMMAC_TXBUF_T_SKB) अणु
			अगर (likely(skb)) अणु
				pkts_compl++;
				bytes_compl += skb->len;
				dev_consume_skb_any(skb);
				tx_q->tx_skbuff[entry] = शून्य;
			पूर्ण
		पूर्ण

		sपंचांगmac_release_tx_desc(priv, p, priv->mode);

		entry = STMMAC_GET_ENTRY(entry, priv->dma_tx_size);
	पूर्ण
	tx_q->dirty_tx = entry;

	netdev_tx_completed_queue(netdev_get_tx_queue(priv->dev, queue),
				  pkts_compl, bytes_compl);

	अगर (unlikely(netअगर_tx_queue_stopped(netdev_get_tx_queue(priv->dev,
								queue))) &&
	    sपंचांगmac_tx_avail(priv, queue) > STMMAC_TX_THRESH(priv)) अणु

		netअगर_dbg(priv, tx_करोne, priv->dev,
			  "%s: restart transmit\n", __func__);
		netअगर_tx_wake_queue(netdev_get_tx_queue(priv->dev, queue));
	पूर्ण

	अगर (tx_q->xsk_pool) अणु
		bool work_करोne;

		अगर (tx_q->xsk_frames_करोne)
			xsk_tx_completed(tx_q->xsk_pool, tx_q->xsk_frames_करोne);

		अगर (xsk_uses_need_wakeup(tx_q->xsk_pool))
			xsk_set_tx_need_wakeup(tx_q->xsk_pool);

		/* For XSK TX, we try to send as many as possible.
		 * If XSK work करोne (XSK TX desc empty and budget still
		 * available), वापस "budget - 1" to reenable TX IRQ.
		 * Else, वापस "budget" to make NAPI जारी polling.
		 */
		work_करोne = sपंचांगmac_xdp_xmit_zc(priv, queue,
					       STMMAC_XSK_TX_BUDGET_MAX);
		अगर (work_करोne)
			xmits = budget - 1;
		अन्यथा
			xmits = budget;
	पूर्ण

	अगर (priv->eee_enabled && !priv->tx_path_in_lpi_mode &&
	    priv->eee_sw_समयr_en) अणु
		sपंचांगmac_enable_eee_mode(priv);
		mod_समयr(&priv->eee_ctrl_समयr, STMMAC_LPI_T(priv->tx_lpi_समयr));
	पूर्ण

	/* We still have pending packets, let's call क्रम a new scheduling */
	अगर (tx_q->dirty_tx != tx_q->cur_tx)
		hrसमयr_start(&tx_q->txसमयr,
			      STMMAC_COAL_TIMER(priv->tx_coal_समयr[queue]),
			      HRTIMER_MODE_REL);

	__netअगर_tx_unlock_bh(netdev_get_tx_queue(priv->dev, queue));

	/* Combine decisions from TX clean and XSK TX */
	वापस max(count, xmits);
पूर्ण

/**
 * sपंचांगmac_tx_err - to manage the tx error
 * @priv: driver निजी काष्ठाure
 * @chan: channel index
 * Description: it cleans the descriptors and restarts the transmission
 * in हाल of transmission errors.
 */
अटल व्योम sपंचांगmac_tx_err(काष्ठा sपंचांगmac_priv *priv, u32 chan)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[chan];

	netअगर_tx_stop_queue(netdev_get_tx_queue(priv->dev, chan));

	sपंचांगmac_stop_tx_dma(priv, chan);
	dma_मुक्त_tx_skbufs(priv, chan);
	sपंचांगmac_clear_tx_descriptors(priv, chan);
	tx_q->dirty_tx = 0;
	tx_q->cur_tx = 0;
	tx_q->mss = 0;
	netdev_tx_reset_queue(netdev_get_tx_queue(priv->dev, chan));
	sपंचांगmac_init_tx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
			    tx_q->dma_tx_phy, chan);
	sपंचांगmac_start_tx_dma(priv, chan);

	priv->dev->stats.tx_errors++;
	netअगर_tx_wake_queue(netdev_get_tx_queue(priv->dev, chan));
पूर्ण

/**
 *  sपंचांगmac_set_dma_operation_mode - Set DMA operation mode by channel
 *  @priv: driver निजी काष्ठाure
 *  @txmode: TX operating mode
 *  @rxmode: RX operating mode
 *  @chan: channel index
 *  Description: it is used क्रम configuring of the DMA operation mode in
 *  runसमय in order to program the tx/rx DMA thresholds or Store-And-Forward
 *  mode.
 */
अटल व्योम sपंचांगmac_set_dma_operation_mode(काष्ठा sपंचांगmac_priv *priv, u32 txmode,
					  u32 rxmode, u32 chan)
अणु
	u8 rxqmode = priv->plat->rx_queues_cfg[chan].mode_to_use;
	u8 txqmode = priv->plat->tx_queues_cfg[chan].mode_to_use;
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	पूर्णांक rxfअगरosz = priv->plat->rx_fअगरo_size;
	पूर्णांक txfअगरosz = priv->plat->tx_fअगरo_size;

	अगर (rxfअगरosz == 0)
		rxfअगरosz = priv->dma_cap.rx_fअगरo_size;
	अगर (txfअगरosz == 0)
		txfअगरosz = priv->dma_cap.tx_fअगरo_size;

	/* Adjust क्रम real per queue fअगरo size */
	rxfअगरosz /= rx_channels_count;
	txfअगरosz /= tx_channels_count;

	sपंचांगmac_dma_rx_mode(priv, priv->ioaddr, rxmode, chan, rxfअगरosz, rxqmode);
	sपंचांगmac_dma_tx_mode(priv, priv->ioaddr, txmode, chan, txfअगरosz, txqmode);
पूर्ण

अटल bool sपंचांगmac_safety_feat_पूर्णांकerrupt(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक ret;

	ret = sपंचांगmac_safety_feat_irq_status(priv, priv->dev,
			priv->ioaddr, priv->dma_cap.asp, &priv->sstats);
	अगर (ret && (ret != -EINVAL)) अणु
		sपंचांगmac_global_err(priv);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक sपंचांगmac_napi_check(काष्ठा sपंचांगmac_priv *priv, u32 chan, u32 dir)
अणु
	पूर्णांक status = sपंचांगmac_dma_पूर्णांकerrupt_status(priv, priv->ioaddr,
						 &priv->xstats, chan, dir);
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[chan];
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[chan];
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[chan];
	काष्ठा napi_काष्ठा *rx_napi;
	काष्ठा napi_काष्ठा *tx_napi;
	अचिन्हित दीर्घ flags;

	rx_napi = rx_q->xsk_pool ? &ch->rxtx_napi : &ch->rx_napi;
	tx_napi = tx_q->xsk_pool ? &ch->rxtx_napi : &ch->tx_napi;

	अगर ((status & handle_rx) && (chan < priv->plat->rx_queues_to_use)) अणु
		अगर (napi_schedule_prep(rx_napi)) अणु
			spin_lock_irqsave(&ch->lock, flags);
			sपंचांगmac_disable_dma_irq(priv, priv->ioaddr, chan, 1, 0);
			spin_unlock_irqrestore(&ch->lock, flags);
			__napi_schedule(rx_napi);
		पूर्ण
	पूर्ण

	अगर ((status & handle_tx) && (chan < priv->plat->tx_queues_to_use)) अणु
		अगर (napi_schedule_prep(tx_napi)) अणु
			spin_lock_irqsave(&ch->lock, flags);
			sपंचांगmac_disable_dma_irq(priv, priv->ioaddr, chan, 0, 1);
			spin_unlock_irqrestore(&ch->lock, flags);
			__napi_schedule(tx_napi);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * sपंचांगmac_dma_पूर्णांकerrupt - DMA ISR
 * @priv: driver निजी काष्ठाure
 * Description: this is the DMA ISR. It is called by the मुख्य ISR.
 * It calls the dwmac dma routine and schedule poll method in हाल of some
 * work can be करोne.
 */
अटल व्योम sपंचांगmac_dma_पूर्णांकerrupt(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_channel_count = priv->plat->tx_queues_to_use;
	u32 rx_channel_count = priv->plat->rx_queues_to_use;
	u32 channels_to_check = tx_channel_count > rx_channel_count ?
				tx_channel_count : rx_channel_count;
	u32 chan;
	पूर्णांक status[max_t(u32, MTL_MAX_TX_QUEUES, MTL_MAX_RX_QUEUES)];

	/* Make sure we never check beyond our status buffer. */
	अगर (WARN_ON_ONCE(channels_to_check > ARRAY_SIZE(status)))
		channels_to_check = ARRAY_SIZE(status);

	क्रम (chan = 0; chan < channels_to_check; chan++)
		status[chan] = sपंचांगmac_napi_check(priv, chan,
						 DMA_सूची_RXTX);

	क्रम (chan = 0; chan < tx_channel_count; chan++) अणु
		अगर (unlikely(status[chan] & tx_hard_error_bump_tc)) अणु
			/* Try to bump up the dma threshold on this failure */
			अगर (unlikely(priv->xstats.threshold != SF_DMA_MODE) &&
			    (tc <= 256)) अणु
				tc += 64;
				अगर (priv->plat->क्रमce_thresh_dma_mode)
					sपंचांगmac_set_dma_operation_mode(priv,
								      tc,
								      tc,
								      chan);
				अन्यथा
					sपंचांगmac_set_dma_operation_mode(priv,
								    tc,
								    SF_DMA_MODE,
								    chan);
				priv->xstats.threshold = tc;
			पूर्ण
		पूर्ण अन्यथा अगर (unlikely(status[chan] == tx_hard_error)) अणु
			sपंचांगmac_tx_err(priv, chan);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_mmc_setup: setup the Mac Management Counters (MMC)
 * @priv: driver निजी काष्ठाure
 * Description: this masks the MMC irq, in fact, the counters are managed in SW.
 */
अटल व्योम sपंचांगmac_mmc_setup(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित पूर्णांक mode = MMC_CNTRL_RESET_ON_READ | MMC_CNTRL_COUNTER_RESET |
			    MMC_CNTRL_PRESET | MMC_CNTRL_FULL_HALF_PRESET;

	sपंचांगmac_mmc_पूर्णांकr_all_mask(priv, priv->mmcaddr);

	अगर (priv->dma_cap.rmon) अणु
		sपंचांगmac_mmc_ctrl(priv, priv->mmcaddr, mode);
		स_रखो(&priv->mmc, 0, माप(काष्ठा sपंचांगmac_counters));
	पूर्ण अन्यथा
		netdev_info(priv->dev, "No MAC Management Counters available\n");
पूर्ण

/**
 * sपंचांगmac_get_hw_features - get MAC capabilities from the HW cap. रेजिस्टर.
 * @priv: driver निजी काष्ठाure
 * Description:
 *  new GMAC chip generations have a new रेजिस्टर to indicate the
 *  presence of the optional feature/functions.
 *  This can be also used to override the value passed through the
 *  platक्रमm and necessary क्रम old MAC10/100 and GMAC chips.
 */
अटल पूर्णांक sपंचांगmac_get_hw_features(काष्ठा sपंचांगmac_priv *priv)
अणु
	वापस sपंचांगmac_get_hw_feature(priv, priv->ioaddr, &priv->dma_cap) == 0;
पूर्ण

/**
 * sपंचांगmac_check_ether_addr - check अगर the MAC addr is valid
 * @priv: driver निजी काष्ठाure
 * Description:
 * it is to verअगरy अगर the MAC address is valid, in हाल of failures it
 * generates a अक्रमom MAC address
 */
अटल व्योम sपंचांगmac_check_ether_addr(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!is_valid_ether_addr(priv->dev->dev_addr)) अणु
		sपंचांगmac_get_umac_addr(priv, priv->hw, priv->dev->dev_addr, 0);
		अगर (!is_valid_ether_addr(priv->dev->dev_addr))
			eth_hw_addr_अक्रमom(priv->dev);
		dev_info(priv->device, "device MAC address %pM\n",
			 priv->dev->dev_addr);
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_init_dma_engine - DMA init.
 * @priv: driver निजी काष्ठाure
 * Description:
 * It inits the DMA invoking the specअगरic MAC/GMAC callback.
 * Some DMA parameters can be passed from the platक्रमm;
 * in हाल of these are not passed a शेष is kept क्रम the MAC or GMAC.
 */
अटल पूर्णांक sपंचांगmac_init_dma_engine(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 dma_csr_ch = max(rx_channels_count, tx_channels_count);
	काष्ठा sपंचांगmac_rx_queue *rx_q;
	काष्ठा sपंचांगmac_tx_queue *tx_q;
	u32 chan = 0;
	पूर्णांक atds = 0;
	पूर्णांक ret = 0;

	अगर (!priv->plat->dma_cfg || !priv->plat->dma_cfg->pbl) अणु
		dev_err(priv->device, "Invalid DMA configuration\n");
		वापस -EINVAL;
	पूर्ण

	अगर (priv->extend_desc && (priv->mode == STMMAC_RING_MODE))
		atds = 1;

	ret = sपंचांगmac_reset(priv, priv->ioaddr);
	अगर (ret) अणु
		dev_err(priv->device, "Failed to reset the dma\n");
		वापस ret;
	पूर्ण

	/* DMA Configuration */
	sपंचांगmac_dma_init(priv, priv->ioaddr, priv->plat->dma_cfg, atds);

	अगर (priv->plat->axi)
		sपंचांगmac_axi(priv, priv->ioaddr, priv->plat->axi);

	/* DMA CSR Channel configuration */
	क्रम (chan = 0; chan < dma_csr_ch; chan++)
		sपंचांगmac_init_chan(priv, priv->ioaddr, priv->plat->dma_cfg, chan);

	/* DMA RX Channel Configuration */
	क्रम (chan = 0; chan < rx_channels_count; chan++) अणु
		rx_q = &priv->rx_queue[chan];

		sपंचांगmac_init_rx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
				    rx_q->dma_rx_phy, chan);

		rx_q->rx_tail_addr = rx_q->dma_rx_phy +
				     (rx_q->buf_alloc_num *
				      माप(काष्ठा dma_desc));
		sपंचांगmac_set_rx_tail_ptr(priv, priv->ioaddr,
				       rx_q->rx_tail_addr, chan);
	पूर्ण

	/* DMA TX Channel Configuration */
	क्रम (chan = 0; chan < tx_channels_count; chan++) अणु
		tx_q = &priv->tx_queue[chan];

		sपंचांगmac_init_tx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
				    tx_q->dma_tx_phy, chan);

		tx_q->tx_tail_addr = tx_q->dma_tx_phy;
		sपंचांगmac_set_tx_tail_ptr(priv, priv->ioaddr,
				       tx_q->tx_tail_addr, chan);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांगmac_tx_समयr_arm(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];

	hrसमयr_start(&tx_q->txसमयr,
		      STMMAC_COAL_TIMER(priv->tx_coal_समयr[queue]),
		      HRTIMER_MODE_REL);
पूर्ण

/**
 * sपंचांगmac_tx_समयr - mitigation sw समयr क्रम tx.
 * @t: data poपूर्णांकer
 * Description:
 * This is the समयr handler to directly invoke the sपंचांगmac_tx_clean.
 */
अटल क्रमागत hrसमयr_restart sपंचांगmac_tx_समयr(काष्ठा hrसमयr *t)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = container_of(t, काष्ठा sपंचांगmac_tx_queue, txसमयr);
	काष्ठा sपंचांगmac_priv *priv = tx_q->priv_data;
	काष्ठा sपंचांगmac_channel *ch;
	काष्ठा napi_काष्ठा *napi;

	ch = &priv->channel[tx_q->queue_index];
	napi = tx_q->xsk_pool ? &ch->rxtx_napi : &ch->tx_napi;

	अगर (likely(napi_schedule_prep(napi))) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ch->lock, flags);
		sपंचांगmac_disable_dma_irq(priv, priv->ioaddr, ch->index, 0, 1);
		spin_unlock_irqrestore(&ch->lock, flags);
		__napi_schedule(napi);
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * sपंचांगmac_init_coalesce - init mitigation options.
 * @priv: driver निजी काष्ठाure
 * Description:
 * This inits the coalesce parameters: i.e. समयr rate,
 * समयr handler and शेष threshold used क्रम enabling the
 * पूर्णांकerrupt on completion bit.
 */
अटल व्योम sपंचांगmac_init_coalesce(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_channel_count = priv->plat->tx_queues_to_use;
	u32 rx_channel_count = priv->plat->rx_queues_to_use;
	u32 chan;

	क्रम (chan = 0; chan < tx_channel_count; chan++) अणु
		काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[chan];

		priv->tx_coal_frames[chan] = STMMAC_TX_FRAMES;
		priv->tx_coal_समयr[chan] = STMMAC_COAL_TX_TIMER;

		hrसमयr_init(&tx_q->txसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		tx_q->txसमयr.function = sपंचांगmac_tx_समयr;
	पूर्ण

	क्रम (chan = 0; chan < rx_channel_count; chan++)
		priv->rx_coal_frames[chan] = STMMAC_RX_FRAMES;
पूर्ण

अटल व्योम sपंचांगmac_set_rings_length(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan;

	/* set TX ring length */
	क्रम (chan = 0; chan < tx_channels_count; chan++)
		sपंचांगmac_set_tx_ring_len(priv, priv->ioaddr,
				       (priv->dma_tx_size - 1), chan);

	/* set RX ring length */
	क्रम (chan = 0; chan < rx_channels_count; chan++)
		sपंचांगmac_set_rx_ring_len(priv, priv->ioaddr,
				       (priv->dma_rx_size - 1), chan);
पूर्ण

/**
 *  sपंचांगmac_set_tx_queue_weight - Set TX queue weight
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम setting TX queues weight
 */
अटल व्योम sपंचांगmac_set_tx_queue_weight(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 weight;
	u32 queue;

	क्रम (queue = 0; queue < tx_queues_count; queue++) अणु
		weight = priv->plat->tx_queues_cfg[queue].weight;
		sपंचांगmac_set_mtl_tx_queue_weight(priv, priv->hw, weight, queue);
	पूर्ण
पूर्ण

/**
 *  sपंचांगmac_configure_cbs - Configure CBS in TX queue
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम configuring CBS in AVB TX queues
 */
अटल व्योम sपंचांगmac_configure_cbs(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 mode_to_use;
	u32 queue;

	/* queue 0 is reserved क्रम legacy traffic */
	क्रम (queue = 1; queue < tx_queues_count; queue++) अणु
		mode_to_use = priv->plat->tx_queues_cfg[queue].mode_to_use;
		अगर (mode_to_use == MTL_QUEUE_DCB)
			जारी;

		sपंचांगmac_config_cbs(priv, priv->hw,
				priv->plat->tx_queues_cfg[queue].send_slope,
				priv->plat->tx_queues_cfg[queue].idle_slope,
				priv->plat->tx_queues_cfg[queue].high_credit,
				priv->plat->tx_queues_cfg[queue].low_credit,
				queue);
	पूर्ण
पूर्ण

/**
 *  sपंचांगmac_rx_queue_dma_chan_map - Map RX queue to RX dma channel
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम mapping RX queues to RX dma channels
 */
अटल व्योम sपंचांगmac_rx_queue_dma_chan_map(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u32 chan;

	क्रम (queue = 0; queue < rx_queues_count; queue++) अणु
		chan = priv->plat->rx_queues_cfg[queue].chan;
		sपंचांगmac_map_mtl_to_dma(priv, priv->hw, queue, chan);
	पूर्ण
पूर्ण

/**
 *  sपंचांगmac_mac_config_rx_queues_prio - Configure RX Queue priority
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम configuring the RX Queue Priority
 */
अटल व्योम sपंचांगmac_mac_config_rx_queues_prio(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u32 prio;

	क्रम (queue = 0; queue < rx_queues_count; queue++) अणु
		अगर (!priv->plat->rx_queues_cfg[queue].use_prio)
			जारी;

		prio = priv->plat->rx_queues_cfg[queue].prio;
		sपंचांगmac_rx_queue_prio(priv, priv->hw, prio, queue);
	पूर्ण
पूर्ण

/**
 *  sपंचांगmac_mac_config_tx_queues_prio - Configure TX Queue priority
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम configuring the TX Queue Priority
 */
अटल व्योम sपंचांगmac_mac_config_tx_queues_prio(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 queue;
	u32 prio;

	क्रम (queue = 0; queue < tx_queues_count; queue++) अणु
		अगर (!priv->plat->tx_queues_cfg[queue].use_prio)
			जारी;

		prio = priv->plat->tx_queues_cfg[queue].prio;
		sपंचांगmac_tx_queue_prio(priv, priv->hw, prio, queue);
	पूर्ण
पूर्ण

/**
 *  sपंचांगmac_mac_config_rx_queues_routing - Configure RX Queue Routing
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम configuring the RX queue routing
 */
अटल व्योम sपंचांगmac_mac_config_rx_queues_routing(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u8 packet;

	क्रम (queue = 0; queue < rx_queues_count; queue++) अणु
		/* no specअगरic packet type routing specअगरied क्रम the queue */
		अगर (priv->plat->rx_queues_cfg[queue].pkt_route == 0x0)
			जारी;

		packet = priv->plat->rx_queues_cfg[queue].pkt_route;
		sपंचांगmac_rx_queue_routing(priv, priv->hw, packet, queue);
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_mac_config_rss(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!priv->dma_cap.rssen || !priv->plat->rss_en) अणु
		priv->rss.enable = false;
		वापस;
	पूर्ण

	अगर (priv->dev->features & NETIF_F_RXHASH)
		priv->rss.enable = true;
	अन्यथा
		priv->rss.enable = false;

	sपंचांगmac_rss_configure(priv, priv->hw, &priv->rss,
			     priv->plat->rx_queues_to_use);
पूर्ण

/**
 *  sपंचांगmac_mtl_configuration - Configure MTL
 *  @priv: driver निजी काष्ठाure
 *  Description: It is used क्रम configurring MTL
 */
अटल व्योम sपंचांगmac_mtl_configuration(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 tx_queues_count = priv->plat->tx_queues_to_use;

	अगर (tx_queues_count > 1)
		sपंचांगmac_set_tx_queue_weight(priv);

	/* Configure MTL RX algorithms */
	अगर (rx_queues_count > 1)
		sपंचांगmac_prog_mtl_rx_algorithms(priv, priv->hw,
				priv->plat->rx_sched_algorithm);

	/* Configure MTL TX algorithms */
	अगर (tx_queues_count > 1)
		sपंचांगmac_prog_mtl_tx_algorithms(priv, priv->hw,
				priv->plat->tx_sched_algorithm);

	/* Configure CBS in AVB TX queues */
	अगर (tx_queues_count > 1)
		sपंचांगmac_configure_cbs(priv);

	/* Map RX MTL to DMA channels */
	sपंचांगmac_rx_queue_dma_chan_map(priv);

	/* Enable MAC RX Queues */
	sपंचांगmac_mac_enable_rx_queues(priv);

	/* Set RX priorities */
	अगर (rx_queues_count > 1)
		sपंचांगmac_mac_config_rx_queues_prio(priv);

	/* Set TX priorities */
	अगर (tx_queues_count > 1)
		sपंचांगmac_mac_config_tx_queues_prio(priv);

	/* Set RX routing */
	अगर (rx_queues_count > 1)
		sपंचांगmac_mac_config_rx_queues_routing(priv);

	/* Receive Side Scaling */
	अगर (rx_queues_count > 1)
		sपंचांगmac_mac_config_rss(priv);
पूर्ण

अटल व्योम sपंचांगmac_safety_feat_configuration(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (priv->dma_cap.asp) अणु
		netdev_info(priv->dev, "Enabling Safety Features\n");
		sपंचांगmac_safety_feat_config(priv, priv->ioaddr, priv->dma_cap.asp);
	पूर्ण अन्यथा अणु
		netdev_info(priv->dev, "No Safety Features support found\n");
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_fpe_start_wq(काष्ठा sपंचांगmac_priv *priv)
अणु
	अक्षर *name;

	clear_bit(__FPE_TASK_SCHED, &priv->fpe_task_state);
	clear_bit(__FPE_REMOVING,  &priv->fpe_task_state);

	name = priv->wq_name;
	प्र_लिखो(name, "%s-fpe", priv->dev->name);

	priv->fpe_wq = create_singlethपढ़ो_workqueue(name);
	अगर (!priv->fpe_wq) अणु
		netdev_err(priv->dev, "%s: Failed to create workqueue\n", name);

		वापस -ENOMEM;
	पूर्ण
	netdev_info(priv->dev, "FPE workqueue start");

	वापस 0;
पूर्ण

/**
 * sपंचांगmac_hw_setup - setup mac in a usable state.
 *  @dev : poपूर्णांकer to the device काष्ठाure.
 *  @init_ptp: initialize PTP अगर set
 *  Description:
 *  this is the मुख्य function to setup the HW in a usable state because the
 *  dma engine is reset, the core रेजिस्टरs are configured (e.g. AXI,
 *  Checksum features, समयrs). The DMA is पढ़ोy to start receiving and
 *  transmitting.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */
अटल पूर्णांक sपंचांगmac_hw_setup(काष्ठा net_device *dev, bool init_ptp)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	bool sph_en;
	u32 chan;
	पूर्णांक ret;

	/* DMA initialization and SW reset */
	ret = sपंचांगmac_init_dma_engine(priv);
	अगर (ret < 0) अणु
		netdev_err(priv->dev, "%s: DMA engine initialization failed\n",
			   __func__);
		वापस ret;
	पूर्ण

	/* Copy the MAC addr पूर्णांकo the HW  */
	sपंचांगmac_set_umac_addr(priv, priv->hw, dev->dev_addr, 0);

	/* PS and related bits will be programmed according to the speed */
	अगर (priv->hw->pcs) अणु
		पूर्णांक speed = priv->plat->mac_port_sel_speed;

		अगर ((speed == SPEED_10) || (speed == SPEED_100) ||
		    (speed == SPEED_1000)) अणु
			priv->hw->ps = speed;
		पूर्ण अन्यथा अणु
			dev_warn(priv->device, "invalid port speed\n");
			priv->hw->ps = 0;
		पूर्ण
	पूर्ण

	/* Initialize the MAC Core */
	sपंचांगmac_core_init(priv, priv->hw, dev);

	/* Initialize MTL*/
	sपंचांगmac_mtl_configuration(priv);

	/* Initialize Safety Features */
	sपंचांगmac_safety_feat_configuration(priv);

	ret = sपंचांगmac_rx_ipc(priv, priv->hw);
	अगर (!ret) अणु
		netdev_warn(priv->dev, "RX IPC Checksum Offload disabled\n");
		priv->plat->rx_coe = STMMAC_RX_COE_NONE;
		priv->hw->rx_csum = 0;
	पूर्ण

	/* Enable the MAC Rx/Tx */
	sपंचांगmac_mac_set(priv, priv->ioaddr, true);

	/* Set the HW DMA mode and the COE */
	sपंचांगmac_dma_operation_mode(priv);

	sपंचांगmac_mmc_setup(priv);

	अगर (init_ptp) अणु
		ret = clk_prepare_enable(priv->plat->clk_ptp_ref);
		अगर (ret < 0)
			netdev_warn(priv->dev, "failed to enable PTP reference clock: %d\n", ret);

		ret = sपंचांगmac_init_ptp(priv);
		अगर (ret == -EOPNOTSUPP)
			netdev_warn(priv->dev, "PTP not supported by HW\n");
		अन्यथा अगर (ret)
			netdev_warn(priv->dev, "PTP init failed\n");
	पूर्ण

	priv->eee_tw_समयr = STMMAC_DEFAULT_TWT_LS;

	/* Convert the समयr from msec to usec */
	अगर (!priv->tx_lpi_समयr)
		priv->tx_lpi_समयr = eee_समयr * 1000;

	अगर (priv->use_riwt) अणु
		u32 queue;

		क्रम (queue = 0; queue < rx_cnt; queue++) अणु
			अगर (!priv->rx_riwt[queue])
				priv->rx_riwt[queue] = DEF_DMA_RIWT;

			sपंचांगmac_rx_watchकरोg(priv, priv->ioaddr,
					   priv->rx_riwt[queue], queue);
		पूर्ण
	पूर्ण

	अगर (priv->hw->pcs)
		sपंचांगmac_pcs_ctrl_ane(priv, priv->ioaddr, 1, priv->hw->ps, 0);

	/* set TX and RX rings length */
	sपंचांगmac_set_rings_length(priv);

	/* Enable TSO */
	अगर (priv->tso) अणु
		क्रम (chan = 0; chan < tx_cnt; chan++) अणु
			काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[chan];

			/* TSO and TBS cannot co-exist */
			अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
				जारी;

			sपंचांगmac_enable_tso(priv, priv->ioaddr, 1, chan);
		पूर्ण
	पूर्ण

	/* Enable Split Header */
	sph_en = (priv->hw->rx_csum > 0) && priv->sph;
	क्रम (chan = 0; chan < rx_cnt; chan++)
		sपंचांगmac_enable_sph(priv, priv->ioaddr, sph_en, chan);


	/* VLAN Tag Insertion */
	अगर (priv->dma_cap.vlins)
		sपंचांगmac_enable_vlan(priv, priv->hw, STMMAC_VLAN_INSERT);

	/* TBS */
	क्रम (chan = 0; chan < tx_cnt; chan++) अणु
		काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[chan];
		पूर्णांक enable = tx_q->tbs & STMMAC_TBS_AVAIL;

		sपंचांगmac_enable_tbs(priv, priv->ioaddr, enable, chan);
	पूर्ण

	/* Configure real RX and TX queues */
	netअगर_set_real_num_rx_queues(dev, priv->plat->rx_queues_to_use);
	netअगर_set_real_num_tx_queues(dev, priv->plat->tx_queues_to_use);

	/* Start the ball rolling... */
	sपंचांगmac_start_all_dma(priv);

	अगर (priv->dma_cap.fpesel) अणु
		sपंचांगmac_fpe_start_wq(priv);

		अगर (priv->plat->fpe_cfg->enable)
			sपंचांगmac_fpe_handshake(priv, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांगmac_hw_tearकरोwn(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	clk_disable_unprepare(priv->plat->clk_ptp_ref);
पूर्ण

अटल व्योम sपंचांगmac_मुक्त_irq(काष्ठा net_device *dev,
			    क्रमागत request_irq_err irq_err, पूर्णांक irq_idx)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक j;

	चयन (irq_err) अणु
	हाल REQ_IRQ_ERR_ALL:
		irq_idx = priv->plat->tx_queues_to_use;
		fallthrough;
	हाल REQ_IRQ_ERR_TX:
		क्रम (j = irq_idx - 1; j >= 0; j--) अणु
			अगर (priv->tx_irq[j] > 0) अणु
				irq_set_affinity_hपूर्णांक(priv->tx_irq[j], शून्य);
				मुक्त_irq(priv->tx_irq[j], &priv->tx_queue[j]);
			पूर्ण
		पूर्ण
		irq_idx = priv->plat->rx_queues_to_use;
		fallthrough;
	हाल REQ_IRQ_ERR_RX:
		क्रम (j = irq_idx - 1; j >= 0; j--) अणु
			अगर (priv->rx_irq[j] > 0) अणु
				irq_set_affinity_hपूर्णांक(priv->rx_irq[j], शून्य);
				मुक्त_irq(priv->rx_irq[j], &priv->rx_queue[j]);
			पूर्ण
		पूर्ण

		अगर (priv->sfty_ue_irq > 0 && priv->sfty_ue_irq != dev->irq)
			मुक्त_irq(priv->sfty_ue_irq, dev);
		fallthrough;
	हाल REQ_IRQ_ERR_SFTY_UE:
		अगर (priv->sfty_ce_irq > 0 && priv->sfty_ce_irq != dev->irq)
			मुक्त_irq(priv->sfty_ce_irq, dev);
		fallthrough;
	हाल REQ_IRQ_ERR_SFTY_CE:
		अगर (priv->lpi_irq > 0 && priv->lpi_irq != dev->irq)
			मुक्त_irq(priv->lpi_irq, dev);
		fallthrough;
	हाल REQ_IRQ_ERR_LPI:
		अगर (priv->wol_irq > 0 && priv->wol_irq != dev->irq)
			मुक्त_irq(priv->wol_irq, dev);
		fallthrough;
	हाल REQ_IRQ_ERR_WOL:
		मुक्त_irq(dev->irq, dev);
		fallthrough;
	हाल REQ_IRQ_ERR_MAC:
	हाल REQ_IRQ_ERR_NO:
		/* If MAC IRQ request error, no more IRQ to मुक्त */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_request_irq_multi_msi(काष्ठा net_device *dev)
अणु
	क्रमागत request_irq_err irq_err = REQ_IRQ_ERR_NO;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	cpumask_t cpu_mask;
	पूर्णांक irq_idx = 0;
	अक्षर *पूर्णांक_name;
	पूर्णांक ret;
	पूर्णांक i;

	/* For common पूर्णांकerrupt */
	पूर्णांक_name = priv->पूर्णांक_name_mac;
	प्र_लिखो(पूर्णांक_name, "%s:%s", dev->name, "mac");
	ret = request_irq(dev->irq, sपंचांगmac_mac_पूर्णांकerrupt,
			  0, पूर्णांक_name, dev);
	अगर (unlikely(ret < 0)) अणु
		netdev_err(priv->dev,
			   "%s: alloc mac MSI %d (error: %d)\n",
			   __func__, dev->irq, ret);
		irq_err = REQ_IRQ_ERR_MAC;
		जाओ irq_error;
	पूर्ण

	/* Request the Wake IRQ in हाल of another line
	 * is used क्रम WoL
	 */
	अगर (priv->wol_irq > 0 && priv->wol_irq != dev->irq) अणु
		पूर्णांक_name = priv->पूर्णांक_name_wol;
		प्र_लिखो(पूर्णांक_name, "%s:%s", dev->name, "wol");
		ret = request_irq(priv->wol_irq,
				  sपंचांगmac_mac_पूर्णांकerrupt,
				  0, पूर्णांक_name, dev);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: alloc wol MSI %d (error: %d)\n",
				   __func__, priv->wol_irq, ret);
			irq_err = REQ_IRQ_ERR_WOL;
			जाओ irq_error;
		पूर्ण
	पूर्ण

	/* Request the LPI IRQ in हाल of another line
	 * is used क्रम LPI
	 */
	अगर (priv->lpi_irq > 0 && priv->lpi_irq != dev->irq) अणु
		पूर्णांक_name = priv->पूर्णांक_name_lpi;
		प्र_लिखो(पूर्णांक_name, "%s:%s", dev->name, "lpi");
		ret = request_irq(priv->lpi_irq,
				  sपंचांगmac_mac_पूर्णांकerrupt,
				  0, पूर्णांक_name, dev);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: alloc lpi MSI %d (error: %d)\n",
				   __func__, priv->lpi_irq, ret);
			irq_err = REQ_IRQ_ERR_LPI;
			जाओ irq_error;
		पूर्ण
	पूर्ण

	/* Request the Safety Feature Correctible Error line in
	 * हाल of another line is used
	 */
	अगर (priv->sfty_ce_irq > 0 && priv->sfty_ce_irq != dev->irq) अणु
		पूर्णांक_name = priv->पूर्णांक_name_sfty_ce;
		प्र_लिखो(पूर्णांक_name, "%s:%s", dev->name, "safety-ce");
		ret = request_irq(priv->sfty_ce_irq,
				  sपंचांगmac_safety_पूर्णांकerrupt,
				  0, पूर्णांक_name, dev);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: alloc sfty ce MSI %d (error: %d)\n",
				   __func__, priv->sfty_ce_irq, ret);
			irq_err = REQ_IRQ_ERR_SFTY_CE;
			जाओ irq_error;
		पूर्ण
	पूर्ण

	/* Request the Safety Feature Uncorrectible Error line in
	 * हाल of another line is used
	 */
	अगर (priv->sfty_ue_irq > 0 && priv->sfty_ue_irq != dev->irq) अणु
		पूर्णांक_name = priv->पूर्णांक_name_sfty_ue;
		प्र_लिखो(पूर्णांक_name, "%s:%s", dev->name, "safety-ue");
		ret = request_irq(priv->sfty_ue_irq,
				  sपंचांगmac_safety_पूर्णांकerrupt,
				  0, पूर्णांक_name, dev);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: alloc sfty ue MSI %d (error: %d)\n",
				   __func__, priv->sfty_ue_irq, ret);
			irq_err = REQ_IRQ_ERR_SFTY_UE;
			जाओ irq_error;
		पूर्ण
	पूर्ण

	/* Request Rx MSI irq */
	क्रम (i = 0; i < priv->plat->rx_queues_to_use; i++) अणु
		अगर (priv->rx_irq[i] == 0)
			जारी;

		पूर्णांक_name = priv->पूर्णांक_name_rx_irq[i];
		प्र_लिखो(पूर्णांक_name, "%s:%s-%d", dev->name, "rx", i);
		ret = request_irq(priv->rx_irq[i],
				  sपंचांगmac_msi_पूर्णांकr_rx,
				  0, पूर्णांक_name, &priv->rx_queue[i]);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: alloc rx-%d  MSI %d (error: %d)\n",
				   __func__, i, priv->rx_irq[i], ret);
			irq_err = REQ_IRQ_ERR_RX;
			irq_idx = i;
			जाओ irq_error;
		पूर्ण
		cpumask_clear(&cpu_mask);
		cpumask_set_cpu(i % num_online_cpus(), &cpu_mask);
		irq_set_affinity_hपूर्णांक(priv->rx_irq[i], &cpu_mask);
	पूर्ण

	/* Request Tx MSI irq */
	क्रम (i = 0; i < priv->plat->tx_queues_to_use; i++) अणु
		अगर (priv->tx_irq[i] == 0)
			जारी;

		पूर्णांक_name = priv->पूर्णांक_name_tx_irq[i];
		प्र_लिखो(पूर्णांक_name, "%s:%s-%d", dev->name, "tx", i);
		ret = request_irq(priv->tx_irq[i],
				  sपंचांगmac_msi_पूर्णांकr_tx,
				  0, पूर्णांक_name, &priv->tx_queue[i]);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: alloc tx-%d  MSI %d (error: %d)\n",
				   __func__, i, priv->tx_irq[i], ret);
			irq_err = REQ_IRQ_ERR_TX;
			irq_idx = i;
			जाओ irq_error;
		पूर्ण
		cpumask_clear(&cpu_mask);
		cpumask_set_cpu(i % num_online_cpus(), &cpu_mask);
		irq_set_affinity_hपूर्णांक(priv->tx_irq[i], &cpu_mask);
	पूर्ण

	वापस 0;

irq_error:
	sपंचांगmac_मुक्त_irq(dev, irq_err, irq_idx);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_request_irq_single(काष्ठा net_device *dev)
अणु
	क्रमागत request_irq_err irq_err = REQ_IRQ_ERR_NO;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	ret = request_irq(dev->irq, sपंचांगmac_पूर्णांकerrupt,
			  IRQF_SHARED, dev->name, dev);
	अगर (unlikely(ret < 0)) अणु
		netdev_err(priv->dev,
			   "%s: ERROR: allocating the IRQ %d (error: %d)\n",
			   __func__, dev->irq, ret);
		irq_err = REQ_IRQ_ERR_MAC;
		वापस ret;
	पूर्ण

	/* Request the Wake IRQ in हाल of another line
	 * is used क्रम WoL
	 */
	अगर (priv->wol_irq > 0 && priv->wol_irq != dev->irq) अणु
		ret = request_irq(priv->wol_irq, sपंचांगmac_पूर्णांकerrupt,
				  IRQF_SHARED, dev->name, dev);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: ERROR: allocating the WoL IRQ %d (%d)\n",
				   __func__, priv->wol_irq, ret);
			irq_err = REQ_IRQ_ERR_WOL;
			वापस ret;
		पूर्ण
	पूर्ण

	/* Request the IRQ lines */
	अगर (priv->lpi_irq > 0 && priv->lpi_irq != dev->irq) अणु
		ret = request_irq(priv->lpi_irq, sपंचांगmac_पूर्णांकerrupt,
				  IRQF_SHARED, dev->name, dev);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(priv->dev,
				   "%s: ERROR: allocating the LPI IRQ %d (%d)\n",
				   __func__, priv->lpi_irq, ret);
			irq_err = REQ_IRQ_ERR_LPI;
			जाओ irq_error;
		पूर्ण
	पूर्ण

	वापस 0;

irq_error:
	sपंचांगmac_मुक्त_irq(dev, irq_err, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_request_irq(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	/* Request the IRQ lines */
	अगर (priv->plat->multi_msi_en)
		ret = sपंचांगmac_request_irq_multi_msi(dev);
	अन्यथा
		ret = sपंचांगmac_request_irq_single(dev);

	वापस ret;
पूर्ण

/**
 *  sपंचांगmac_खोलो - खोलो entry poपूर्णांक of the driver
 *  @dev : poपूर्णांकer to the device काष्ठाure.
 *  Description:
 *  This function is the खोलो entry poपूर्णांक of the driver.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */
पूर्णांक sपंचांगmac_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक bfsize = 0;
	u32 chan;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->device);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->device);
		वापस ret;
	पूर्ण

	अगर (priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI &&
	    priv->hw->xpcs_args.an_mode != DW_AN_C73) अणु
		ret = sपंचांगmac_init_phy(dev);
		अगर (ret) अणु
			netdev_err(priv->dev,
				   "%s: Cannot attach to PHY (error: %d)\n",
				   __func__, ret);
			जाओ init_phy_error;
		पूर्ण
	पूर्ण

	/* Extra statistics */
	स_रखो(&priv->xstats, 0, माप(काष्ठा sपंचांगmac_extra_stats));
	priv->xstats.threshold = tc;

	bfsize = sपंचांगmac_set_16kib_bfsize(priv, dev->mtu);
	अगर (bfsize < 0)
		bfsize = 0;

	अगर (bfsize < BUF_SIZE_16KiB)
		bfsize = sपंचांगmac_set_bfsize(dev->mtu, priv->dma_buf_sz);

	priv->dma_buf_sz = bfsize;
	buf_sz = bfsize;

	priv->rx_copyअवरोध = STMMAC_RX_COPYBREAK;

	अगर (!priv->dma_tx_size)
		priv->dma_tx_size = DMA_DEFAULT_TX_SIZE;
	अगर (!priv->dma_rx_size)
		priv->dma_rx_size = DMA_DEFAULT_RX_SIZE;

	/* Earlier check क्रम TBS */
	क्रम (chan = 0; chan < priv->plat->tx_queues_to_use; chan++) अणु
		काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[chan];
		पूर्णांक tbs_en = priv->plat->tx_queues_cfg[chan].tbs_en;

		/* Setup per-TXQ tbs flag beक्रमe TX descriptor alloc */
		tx_q->tbs |= tbs_en ? STMMAC_TBS_AVAIL : 0;
	पूर्ण

	ret = alloc_dma_desc_resources(priv);
	अगर (ret < 0) अणु
		netdev_err(priv->dev, "%s: DMA descriptors allocation failed\n",
			   __func__);
		जाओ dma_desc_error;
	पूर्ण

	ret = init_dma_desc_rings(dev, GFP_KERNEL);
	अगर (ret < 0) अणु
		netdev_err(priv->dev, "%s: DMA descriptors initialization failed\n",
			   __func__);
		जाओ init_error;
	पूर्ण

	ret = sपंचांगmac_hw_setup(dev, true);
	अगर (ret < 0) अणु
		netdev_err(priv->dev, "%s: Hw setup failed\n", __func__);
		जाओ init_error;
	पूर्ण

	sपंचांगmac_init_coalesce(priv);

	phylink_start(priv->phylink);
	/* We may have called phylink_speed_करोwn beक्रमe */
	phylink_speed_up(priv->phylink);

	ret = sपंचांगmac_request_irq(dev);
	अगर (ret)
		जाओ irq_error;

	sपंचांगmac_enable_all_queues(priv);
	netअगर_tx_start_all_queues(priv->dev);

	वापस 0;

irq_error:
	phylink_stop(priv->phylink);

	क्रम (chan = 0; chan < priv->plat->tx_queues_to_use; chan++)
		hrसमयr_cancel(&priv->tx_queue[chan].txसमयr);

	sपंचांगmac_hw_tearकरोwn(dev);
init_error:
	मुक्त_dma_desc_resources(priv);
dma_desc_error:
	phylink_disconnect_phy(priv->phylink);
init_phy_error:
	pm_runसमय_put(priv->device);
	वापस ret;
पूर्ण

अटल व्योम sपंचांगmac_fpe_stop_wq(काष्ठा sपंचांगmac_priv *priv)
अणु
	set_bit(__FPE_REMOVING, &priv->fpe_task_state);

	अगर (priv->fpe_wq)
		destroy_workqueue(priv->fpe_wq);

	netdev_info(priv->dev, "FPE workqueue stop");
पूर्ण

/**
 *  sपंचांगmac_release - बंद entry poपूर्णांक of the driver
 *  @dev : device poपूर्णांकer.
 *  Description:
 *  This is the stop entry poपूर्णांक of the driver.
 */
पूर्णांक sपंचांगmac_release(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 chan;

	अगर (device_may_wakeup(priv->device))
		phylink_speed_करोwn(priv->phylink, false);
	/* Stop and disconnect the PHY */
	phylink_stop(priv->phylink);
	phylink_disconnect_phy(priv->phylink);

	sपंचांगmac_disable_all_queues(priv);

	क्रम (chan = 0; chan < priv->plat->tx_queues_to_use; chan++)
		hrसमयr_cancel(&priv->tx_queue[chan].txसमयr);

	/* Free the IRQ lines */
	sपंचांगmac_मुक्त_irq(dev, REQ_IRQ_ERR_ALL, 0);

	अगर (priv->eee_enabled) अणु
		priv->tx_path_in_lpi_mode = false;
		del_समयr_sync(&priv->eee_ctrl_समयr);
	पूर्ण

	/* Stop TX/RX DMA and clear the descriptors */
	sपंचांगmac_stop_all_dma(priv);

	/* Release and मुक्त the Rx/Tx resources */
	मुक्त_dma_desc_resources(priv);

	/* Disable the MAC Rx/Tx */
	sपंचांगmac_mac_set(priv, priv->ioaddr, false);

	netअगर_carrier_off(dev);

	sपंचांगmac_release_ptp(priv);

	pm_runसमय_put(priv->device);

	अगर (priv->dma_cap.fpesel)
		sपंचांगmac_fpe_stop_wq(priv);

	वापस 0;
पूर्ण

अटल bool sपंचांगmac_vlan_insert(काष्ठा sपंचांगmac_priv *priv, काष्ठा sk_buff *skb,
			       काष्ठा sपंचांगmac_tx_queue *tx_q)
अणु
	u16 tag = 0x0, inner_tag = 0x0;
	u32 inner_type = 0x0;
	काष्ठा dma_desc *p;

	अगर (!priv->dma_cap.vlins)
		वापस false;
	अगर (!skb_vlan_tag_present(skb))
		वापस false;
	अगर (skb->vlan_proto == htons(ETH_P_8021AD)) अणु
		inner_tag = skb_vlan_tag_get(skb);
		inner_type = STMMAC_VLAN_INSERT;
	पूर्ण

	tag = skb_vlan_tag_get(skb);

	अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		p = &tx_q->dma_entx[tx_q->cur_tx].basic;
	अन्यथा
		p = &tx_q->dma_tx[tx_q->cur_tx];

	अगर (sपंचांगmac_set_desc_vlan_tag(priv, p, tag, inner_tag, inner_type))
		वापस false;

	sपंचांगmac_set_tx_owner(priv, p);
	tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, priv->dma_tx_size);
	वापस true;
पूर्ण

/**
 *  sपंचांगmac_tso_allocator - बंद entry poपूर्णांक of the driver
 *  @priv: driver निजी काष्ठाure
 *  @des: buffer start address
 *  @total_len: total length to fill in descriptors
 *  @last_segment: condition क्रम the last descriptor
 *  @queue: TX queue index
 *  Description:
 *  This function fills descriptor and request new descriptors according to
 *  buffer length to fill
 */
अटल व्योम sपंचांगmac_tso_allocator(काष्ठा sपंचांगmac_priv *priv, dma_addr_t des,
				 पूर्णांक total_len, bool last_segment, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	काष्ठा dma_desc *desc;
	u32 buff_size;
	पूर्णांक पंचांगp_len;

	पंचांगp_len = total_len;

	जबतक (पंचांगp_len > 0) अणु
		dma_addr_t curr_addr;

		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx,
						priv->dma_tx_size);
		WARN_ON(tx_q->tx_skbuff[tx_q->cur_tx]);

		अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			desc = &tx_q->dma_entx[tx_q->cur_tx].basic;
		अन्यथा
			desc = &tx_q->dma_tx[tx_q->cur_tx];

		curr_addr = des + (total_len - पंचांगp_len);
		अगर (priv->dma_cap.addr64 <= 32)
			desc->des0 = cpu_to_le32(curr_addr);
		अन्यथा
			sपंचांगmac_set_desc_addr(priv, desc, curr_addr);

		buff_size = पंचांगp_len >= TSO_MAX_BUFF_SIZE ?
			    TSO_MAX_BUFF_SIZE : पंचांगp_len;

		sपंचांगmac_prepare_tso_tx_desc(priv, desc, 0, buff_size,
				0, 1,
				(last_segment) && (पंचांगp_len <= TSO_MAX_BUFF_SIZE),
				0, 0);

		पंचांगp_len -= TSO_MAX_BUFF_SIZE;
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_flush_tx_descriptors(काष्ठा sपंचांगmac_priv *priv, पूर्णांक queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	पूर्णांक desc_size;

	अगर (likely(priv->extend_desc))
		desc_size = माप(काष्ठा dma_extended_desc);
	अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		desc_size = माप(काष्ठा dma_edesc);
	अन्यथा
		desc_size = माप(काष्ठा dma_desc);

	/* The own bit must be the latest setting करोne when prepare the
	 * descriptor and then barrier is needed to make sure that
	 * all is coherent beक्रमe granting the DMA engine.
	 */
	wmb();

	tx_q->tx_tail_addr = tx_q->dma_tx_phy + (tx_q->cur_tx * desc_size);
	sपंचांगmac_set_tx_tail_ptr(priv, priv->ioaddr, tx_q->tx_tail_addr, queue);
पूर्ण

/**
 *  sपंचांगmac_tso_xmit - Tx entry poपूर्णांक of the driver क्रम oversized frames (TSO)
 *  @skb : the socket buffer
 *  @dev : device poपूर्णांकer
 *  Description: this is the transmit function that is called on TSO frames
 *  (support available on GMAC4 and newer chips).
 *  Diagram below show the ring programming in हाल of TSO frames:
 *
 *  First Descriptor
 *   --------
 *   | DES0 |---> buffer1 = L2/L3/L4 header
 *   | DES1 |---> TCP Payload (can जारी on next descr...)
 *   | DES2 |---> buffer 1 and 2 len
 *   | DES3 |---> must set TSE, TCP hdr len-> [22:19]. TCP payload len [17:0]
 *   --------
 *	|
 *     ...
 *	|
 *   --------
 *   | DES0 | --| Split TCP Payload on Buffers 1 and 2
 *   | DES1 | --|
 *   | DES2 | --> buffer 1 and 2 len
 *   | DES3 |
 *   --------
 *
 * mss is fixed when enable tso, so w/o programming the TDES3 ctx field.
 */
अटल netdev_tx_t sपंचांगmac_tso_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dma_desc *desc, *first, *mss_desc = शून्य;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
	u32 queue = skb_get_queue_mapping(skb);
	अचिन्हित पूर्णांक first_entry, tx_packets;
	पूर्णांक पंचांगp_pay_len = 0, first_tx;
	काष्ठा sपंचांगmac_tx_queue *tx_q;
	bool has_vlan, set_ic;
	u8 proto_hdr_len, hdr;
	u32 pay_len, mss;
	dma_addr_t des;
	पूर्णांक i;

	tx_q = &priv->tx_queue[queue];
	first_tx = tx_q->cur_tx;

	/* Compute header lengths */
	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
		proto_hdr_len = skb_transport_offset(skb) + माप(काष्ठा udphdr);
		hdr = माप(काष्ठा udphdr);
	पूर्ण अन्यथा अणु
		proto_hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		hdr = tcp_hdrlen(skb);
	पूर्ण

	/* Desc availability based on threshold should be enough safe */
	अगर (unlikely(sपंचांगmac_tx_avail(priv, queue) <
		(((skb->len - proto_hdr_len) / TSO_MAX_BUFF_SIZE + 1)))) अणु
		अगर (!netअगर_tx_queue_stopped(netdev_get_tx_queue(dev, queue))) अणु
			netअगर_tx_stop_queue(netdev_get_tx_queue(priv->dev,
								queue));
			/* This is a hard error, log it. */
			netdev_err(priv->dev,
				   "%s: Tx Ring full when queue awake\n",
				   __func__);
		पूर्ण
		वापस NETDEV_TX_BUSY;
	पूर्ण

	pay_len = skb_headlen(skb) - proto_hdr_len; /* no frags */

	mss = skb_shinfo(skb)->gso_size;

	/* set new MSS value अगर needed */
	अगर (mss != tx_q->mss) अणु
		अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			mss_desc = &tx_q->dma_entx[tx_q->cur_tx].basic;
		अन्यथा
			mss_desc = &tx_q->dma_tx[tx_q->cur_tx];

		sपंचांगmac_set_mss(priv, mss_desc, mss);
		tx_q->mss = mss;
		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx,
						priv->dma_tx_size);
		WARN_ON(tx_q->tx_skbuff[tx_q->cur_tx]);
	पूर्ण

	अगर (netअगर_msg_tx_queued(priv)) अणु
		pr_info("%s: hdrlen %d, hdr_len %d, pay_len %d, mss %d\n",
			__func__, hdr, proto_hdr_len, pay_len, mss);
		pr_info("\tskb->len %d, skb->data_len %d\n", skb->len,
			skb->data_len);
	पूर्ण

	/* Check अगर VLAN can be inserted by HW */
	has_vlan = sपंचांगmac_vlan_insert(priv, skb, tx_q);

	first_entry = tx_q->cur_tx;
	WARN_ON(tx_q->tx_skbuff[first_entry]);

	अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		desc = &tx_q->dma_entx[first_entry].basic;
	अन्यथा
		desc = &tx_q->dma_tx[first_entry];
	first = desc;

	अगर (has_vlan)
		sपंचांगmac_set_desc_vlan(priv, first, STMMAC_VLAN_INSERT);

	/* first descriptor: fill Headers on Buf1 */
	des = dma_map_single(priv->device, skb->data, skb_headlen(skb),
			     DMA_TO_DEVICE);
	अगर (dma_mapping_error(priv->device, des))
		जाओ dma_map_err;

	tx_q->tx_skbuff_dma[first_entry].buf = des;
	tx_q->tx_skbuff_dma[first_entry].len = skb_headlen(skb);
	tx_q->tx_skbuff_dma[first_entry].map_as_page = false;
	tx_q->tx_skbuff_dma[first_entry].buf_type = STMMAC_TXBUF_T_SKB;

	अगर (priv->dma_cap.addr64 <= 32) अणु
		first->des0 = cpu_to_le32(des);

		/* Fill start of payload in buff2 of first descriptor */
		अगर (pay_len)
			first->des1 = cpu_to_le32(des + proto_hdr_len);

		/* If needed take extra descriptors to fill the reमुख्यing payload */
		पंचांगp_pay_len = pay_len - TSO_MAX_BUFF_SIZE;
	पूर्ण अन्यथा अणु
		sपंचांगmac_set_desc_addr(priv, first, des);
		पंचांगp_pay_len = pay_len;
		des += proto_hdr_len;
		pay_len = 0;
	पूर्ण

	sपंचांगmac_tso_allocator(priv, des, पंचांगp_pay_len, (nfrags == 0), queue);

	/* Prepare fragments */
	क्रम (i = 0; i < nfrags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		des = skb_frag_dma_map(priv->device, frag, 0,
				       skb_frag_size(frag),
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->device, des))
			जाओ dma_map_err;

		sपंचांगmac_tso_allocator(priv, des, skb_frag_size(frag),
				     (i == nfrags - 1), queue);

		tx_q->tx_skbuff_dma[tx_q->cur_tx].buf = des;
		tx_q->tx_skbuff_dma[tx_q->cur_tx].len = skb_frag_size(frag);
		tx_q->tx_skbuff_dma[tx_q->cur_tx].map_as_page = true;
		tx_q->tx_skbuff_dma[tx_q->cur_tx].buf_type = STMMAC_TXBUF_T_SKB;
	पूर्ण

	tx_q->tx_skbuff_dma[tx_q->cur_tx].last_segment = true;

	/* Only the last descriptor माला_लो to poपूर्णांक to the skb. */
	tx_q->tx_skbuff[tx_q->cur_tx] = skb;
	tx_q->tx_skbuff_dma[tx_q->cur_tx].buf_type = STMMAC_TXBUF_T_SKB;

	/* Manage tx mitigation */
	tx_packets = (tx_q->cur_tx + 1) - first_tx;
	tx_q->tx_count_frames += tx_packets;

	अगर ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) && priv->hwts_tx_en)
		set_ic = true;
	अन्यथा अगर (!priv->tx_coal_frames[queue])
		set_ic = false;
	अन्यथा अगर (tx_packets > priv->tx_coal_frames[queue])
		set_ic = true;
	अन्यथा अगर ((tx_q->tx_count_frames %
		  priv->tx_coal_frames[queue]) < tx_packets)
		set_ic = true;
	अन्यथा
		set_ic = false;

	अगर (set_ic) अणु
		अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			desc = &tx_q->dma_entx[tx_q->cur_tx].basic;
		अन्यथा
			desc = &tx_q->dma_tx[tx_q->cur_tx];

		tx_q->tx_count_frames = 0;
		sपंचांगmac_set_tx_ic(priv, desc);
		priv->xstats.tx_set_ic_bit++;
	पूर्ण

	/* We've used all descriptors we need क्रम this skb, however,
	 * advance cur_tx so that it references a fresh descriptor.
	 * nकरो_start_xmit will fill this descriptor the next समय it's
	 * called and sपंचांगmac_tx_clean may clean up to this descriptor.
	 */
	tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, priv->dma_tx_size);

	अगर (unlikely(sपंचांगmac_tx_avail(priv, queue) <= (MAX_SKB_FRAGS + 1))) अणु
		netअगर_dbg(priv, hw, priv->dev, "%s: stop transmitted packets\n",
			  __func__);
		netअगर_tx_stop_queue(netdev_get_tx_queue(priv->dev, queue));
	पूर्ण

	dev->stats.tx_bytes += skb->len;
	priv->xstats.tx_tso_frames++;
	priv->xstats.tx_tso_nfrags += nfrags;

	अगर (priv->sarc_type)
		sपंचांगmac_set_desc_sarc(priv, first, priv->sarc_type);

	skb_tx_बारtamp(skb);

	अगर (unlikely((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
		     priv->hwts_tx_en)) अणु
		/* declare that device is करोing बारtamping */
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		sपंचांगmac_enable_tx_बारtamp(priv, first);
	पूर्ण

	/* Complete the first descriptor beक्रमe granting the DMA */
	sपंचांगmac_prepare_tso_tx_desc(priv, first, 1,
			proto_hdr_len,
			pay_len,
			1, tx_q->tx_skbuff_dma[first_entry].last_segment,
			hdr / 4, (skb->len - proto_hdr_len));

	/* If context desc is used to change MSS */
	अगर (mss_desc) अणु
		/* Make sure that first descriptor has been completely
		 * written, including its own bit. This is because MSS is
		 * actually beक्रमe first descriptor, so we need to make
		 * sure that MSS's own bit is the last thing written.
		 */
		dma_wmb();
		sपंचांगmac_set_tx_owner(priv, mss_desc);
	पूर्ण

	अगर (netअगर_msg_pktdata(priv)) अणु
		pr_info("%s: curr=%d dirty=%d f=%d, e=%d, f_p=%p, nfrags %d\n",
			__func__, tx_q->cur_tx, tx_q->dirty_tx, first_entry,
			tx_q->cur_tx, first, nfrags);
		pr_info(">>> frame to be transmitted: ");
		prपूर्णांक_pkt(skb->data, skb_headlen(skb));
	पूर्ण

	netdev_tx_sent_queue(netdev_get_tx_queue(dev, queue), skb->len);

	sपंचांगmac_flush_tx_descriptors(priv, queue);
	sपंचांगmac_tx_समयr_arm(priv, queue);

	वापस NETDEV_TX_OK;

dma_map_err:
	dev_err(priv->device, "Tx dma map failed\n");
	dev_kमुक्त_skb(skb);
	priv->dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

/**
 *  sपंचांगmac_xmit - Tx entry poपूर्णांक of the driver
 *  @skb : the socket buffer
 *  @dev : device poपूर्णांकer
 *  Description : this is the tx entry poपूर्णांक of the driver.
 *  It programs the chain or the ring and supports oversized frames
 *  and SG feature.
 */
अटल netdev_tx_t sपंचांगmac_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक first_entry, tx_packets, enh_desc;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक nopaged_len = skb_headlen(skb);
	पूर्णांक i, csum_insertion = 0, is_jumbo = 0;
	u32 queue = skb_get_queue_mapping(skb);
	पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
	पूर्णांक gso = skb_shinfo(skb)->gso_type;
	काष्ठा dma_edesc *tbs_desc = शून्य;
	काष्ठा dma_desc *desc, *first;
	काष्ठा sपंचांगmac_tx_queue *tx_q;
	bool has_vlan, set_ic;
	पूर्णांक entry, first_tx;
	dma_addr_t des;

	tx_q = &priv->tx_queue[queue];
	first_tx = tx_q->cur_tx;

	अगर (priv->tx_path_in_lpi_mode && priv->eee_sw_समयr_en)
		sपंचांगmac_disable_eee_mode(priv);

	/* Manage oversized TCP frames क्रम GMAC4 device */
	अगर (skb_is_gso(skb) && priv->tso) अणु
		अगर (gso & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))
			वापस sपंचांगmac_tso_xmit(skb, dev);
		अगर (priv->plat->has_gmac4 && (gso & SKB_GSO_UDP_L4))
			वापस sपंचांगmac_tso_xmit(skb, dev);
	पूर्ण

	अगर (unlikely(sपंचांगmac_tx_avail(priv, queue) < nfrags + 1)) अणु
		अगर (!netअगर_tx_queue_stopped(netdev_get_tx_queue(dev, queue))) अणु
			netअगर_tx_stop_queue(netdev_get_tx_queue(priv->dev,
								queue));
			/* This is a hard error, log it. */
			netdev_err(priv->dev,
				   "%s: Tx Ring full when queue awake\n",
				   __func__);
		पूर्ण
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Check अगर VLAN can be inserted by HW */
	has_vlan = sपंचांगmac_vlan_insert(priv, skb, tx_q);

	entry = tx_q->cur_tx;
	first_entry = entry;
	WARN_ON(tx_q->tx_skbuff[first_entry]);

	csum_insertion = (skb->ip_summed == CHECKSUM_PARTIAL);

	अगर (likely(priv->extend_desc))
		desc = (काष्ठा dma_desc *)(tx_q->dma_etx + entry);
	अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		desc = &tx_q->dma_entx[entry].basic;
	अन्यथा
		desc = tx_q->dma_tx + entry;

	first = desc;

	अगर (has_vlan)
		sपंचांगmac_set_desc_vlan(priv, first, STMMAC_VLAN_INSERT);

	enh_desc = priv->plat->enh_desc;
	/* To program the descriptors according to the size of the frame */
	अगर (enh_desc)
		is_jumbo = sपंचांगmac_is_jumbo_frm(priv, skb->len, enh_desc);

	अगर (unlikely(is_jumbo)) अणु
		entry = sपंचांगmac_jumbo_frm(priv, tx_q, skb, csum_insertion);
		अगर (unlikely(entry < 0) && (entry != -EINVAL))
			जाओ dma_map_err;
	पूर्ण

	क्रम (i = 0; i < nfrags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		पूर्णांक len = skb_frag_size(frag);
		bool last_segment = (i == (nfrags - 1));

		entry = STMMAC_GET_ENTRY(entry, priv->dma_tx_size);
		WARN_ON(tx_q->tx_skbuff[entry]);

		अगर (likely(priv->extend_desc))
			desc = (काष्ठा dma_desc *)(tx_q->dma_etx + entry);
		अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			desc = &tx_q->dma_entx[entry].basic;
		अन्यथा
			desc = tx_q->dma_tx + entry;

		des = skb_frag_dma_map(priv->device, frag, 0, len,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->device, des))
			जाओ dma_map_err; /* should reuse desc w/o issues */

		tx_q->tx_skbuff_dma[entry].buf = des;

		sपंचांगmac_set_desc_addr(priv, desc, des);

		tx_q->tx_skbuff_dma[entry].map_as_page = true;
		tx_q->tx_skbuff_dma[entry].len = len;
		tx_q->tx_skbuff_dma[entry].last_segment = last_segment;
		tx_q->tx_skbuff_dma[entry].buf_type = STMMAC_TXBUF_T_SKB;

		/* Prepare the descriptor and set the own bit too */
		sपंचांगmac_prepare_tx_desc(priv, desc, 0, len, csum_insertion,
				priv->mode, 1, last_segment, skb->len);
	पूर्ण

	/* Only the last descriptor माला_लो to poपूर्णांक to the skb. */
	tx_q->tx_skbuff[entry] = skb;
	tx_q->tx_skbuff_dma[entry].buf_type = STMMAC_TXBUF_T_SKB;

	/* According to the coalesce parameter the IC bit क्रम the latest
	 * segment is reset and the समयr re-started to clean the tx status.
	 * This approach takes care about the fragments: desc is the first
	 * element in हाल of no SG.
	 */
	tx_packets = (entry + 1) - first_tx;
	tx_q->tx_count_frames += tx_packets;

	अगर ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) && priv->hwts_tx_en)
		set_ic = true;
	अन्यथा अगर (!priv->tx_coal_frames[queue])
		set_ic = false;
	अन्यथा अगर (tx_packets > priv->tx_coal_frames[queue])
		set_ic = true;
	अन्यथा अगर ((tx_q->tx_count_frames %
		  priv->tx_coal_frames[queue]) < tx_packets)
		set_ic = true;
	अन्यथा
		set_ic = false;

	अगर (set_ic) अणु
		अगर (likely(priv->extend_desc))
			desc = &tx_q->dma_etx[entry].basic;
		अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
			desc = &tx_q->dma_entx[entry].basic;
		अन्यथा
			desc = &tx_q->dma_tx[entry];

		tx_q->tx_count_frames = 0;
		sपंचांगmac_set_tx_ic(priv, desc);
		priv->xstats.tx_set_ic_bit++;
	पूर्ण

	/* We've used all descriptors we need क्रम this skb, however,
	 * advance cur_tx so that it references a fresh descriptor.
	 * nकरो_start_xmit will fill this descriptor the next समय it's
	 * called and sपंचांगmac_tx_clean may clean up to this descriptor.
	 */
	entry = STMMAC_GET_ENTRY(entry, priv->dma_tx_size);
	tx_q->cur_tx = entry;

	अगर (netअगर_msg_pktdata(priv)) अणु
		netdev_dbg(priv->dev,
			   "%s: curr=%d dirty=%d f=%d, e=%d, first=%p, nfrags=%d",
			   __func__, tx_q->cur_tx, tx_q->dirty_tx, first_entry,
			   entry, first, nfrags);

		netdev_dbg(priv->dev, ">>> frame to be transmitted: ");
		prपूर्णांक_pkt(skb->data, skb->len);
	पूर्ण

	अगर (unlikely(sपंचांगmac_tx_avail(priv, queue) <= (MAX_SKB_FRAGS + 1))) अणु
		netअगर_dbg(priv, hw, priv->dev, "%s: stop transmitted packets\n",
			  __func__);
		netअगर_tx_stop_queue(netdev_get_tx_queue(priv->dev, queue));
	पूर्ण

	dev->stats.tx_bytes += skb->len;

	अगर (priv->sarc_type)
		sपंचांगmac_set_desc_sarc(priv, first, priv->sarc_type);

	skb_tx_बारtamp(skb);

	/* Ready to fill the first descriptor and set the OWN bit w/o any
	 * problems because all the descriptors are actually पढ़ोy to be
	 * passed to the DMA engine.
	 */
	अगर (likely(!is_jumbo)) अणु
		bool last_segment = (nfrags == 0);

		des = dma_map_single(priv->device, skb->data,
				     nopaged_len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->device, des))
			जाओ dma_map_err;

		tx_q->tx_skbuff_dma[first_entry].buf = des;
		tx_q->tx_skbuff_dma[first_entry].buf_type = STMMAC_TXBUF_T_SKB;
		tx_q->tx_skbuff_dma[first_entry].map_as_page = false;

		sपंचांगmac_set_desc_addr(priv, first, des);

		tx_q->tx_skbuff_dma[first_entry].len = nopaged_len;
		tx_q->tx_skbuff_dma[first_entry].last_segment = last_segment;

		अगर (unlikely((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
			     priv->hwts_tx_en)) अणु
			/* declare that device is करोing बारtamping */
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			sपंचांगmac_enable_tx_बारtamp(priv, first);
		पूर्ण

		/* Prepare the first descriptor setting the OWN bit too */
		sपंचांगmac_prepare_tx_desc(priv, first, 1, nopaged_len,
				csum_insertion, priv->mode, 0, last_segment,
				skb->len);
	पूर्ण

	अगर (tx_q->tbs & STMMAC_TBS_EN) अणु
		काष्ठा बारpec64 ts = ns_to_बारpec64(skb->tstamp);

		tbs_desc = &tx_q->dma_entx[first_entry];
		sपंचांगmac_set_desc_tbs(priv, tbs_desc, ts.tv_sec, ts.tv_nsec);
	पूर्ण

	sपंचांगmac_set_tx_owner(priv, first);

	netdev_tx_sent_queue(netdev_get_tx_queue(dev, queue), skb->len);

	sपंचांगmac_enable_dma_transmission(priv, priv->ioaddr);

	sपंचांगmac_flush_tx_descriptors(priv, queue);
	sपंचांगmac_tx_समयr_arm(priv, queue);

	वापस NETDEV_TX_OK;

dma_map_err:
	netdev_err(priv->dev, "Tx DMA map failed\n");
	dev_kमुक्त_skb(skb);
	priv->dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम sपंचांगmac_rx_vlan(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा vlan_ethhdr *veth;
	__be16 vlan_proto;
	u16 vlanid;

	veth = (काष्ठा vlan_ethhdr *)skb->data;
	vlan_proto = veth->h_vlan_proto;

	अगर ((vlan_proto == htons(ETH_P_8021Q) &&
	     dev->features & NETIF_F_HW_VLAN_CTAG_RX) ||
	    (vlan_proto == htons(ETH_P_8021AD) &&
	     dev->features & NETIF_F_HW_VLAN_STAG_RX)) अणु
		/* pop the vlan tag */
		vlanid = ntohs(veth->h_vlan_TCI);
		स_हटाओ(skb->data + VLAN_HLEN, veth, ETH_ALEN * 2);
		skb_pull(skb, VLAN_HLEN);
		__vlan_hwaccel_put_tag(skb, vlan_proto, vlanid);
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_rx_refill - refill used skb pपुनः_स्मृतिated buffers
 * @priv: driver निजी काष्ठाure
 * @queue: RX queue index
 * Description : this is to पुनः_स्मृतिate the skb क्रम the reception process
 * that is based on zero-copy.
 */
अटल अंतरभूत व्योम sपंचांगmac_rx_refill(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	पूर्णांक dirty = sपंचांगmac_rx_dirty(priv, queue);
	अचिन्हित पूर्णांक entry = rx_q->dirty_rx;

	जबतक (dirty-- > 0) अणु
		काष्ठा sपंचांगmac_rx_buffer *buf = &rx_q->buf_pool[entry];
		काष्ठा dma_desc *p;
		bool use_rx_wd;

		अगर (priv->extend_desc)
			p = (काष्ठा dma_desc *)(rx_q->dma_erx + entry);
		अन्यथा
			p = rx_q->dma_rx + entry;

		अगर (!buf->page) अणु
			buf->page = page_pool_dev_alloc_pages(rx_q->page_pool);
			अगर (!buf->page)
				अवरोध;
		पूर्ण

		अगर (priv->sph && !buf->sec_page) अणु
			buf->sec_page = page_pool_dev_alloc_pages(rx_q->page_pool);
			अगर (!buf->sec_page)
				अवरोध;

			buf->sec_addr = page_pool_get_dma_addr(buf->sec_page);
		पूर्ण

		buf->addr = page_pool_get_dma_addr(buf->page) + buf->page_offset;

		sपंचांगmac_set_desc_addr(priv, p, buf->addr);
		अगर (priv->sph)
			sपंचांगmac_set_desc_sec_addr(priv, p, buf->sec_addr, true);
		अन्यथा
			sपंचांगmac_set_desc_sec_addr(priv, p, buf->sec_addr, false);
		sपंचांगmac_refill_desc3(priv, rx_q, p);

		rx_q->rx_count_frames++;
		rx_q->rx_count_frames += priv->rx_coal_frames[queue];
		अगर (rx_q->rx_count_frames > priv->rx_coal_frames[queue])
			rx_q->rx_count_frames = 0;

		use_rx_wd = !priv->rx_coal_frames[queue];
		use_rx_wd |= rx_q->rx_count_frames > 0;
		अगर (!priv->use_riwt)
			use_rx_wd = false;

		dma_wmb();
		sपंचांगmac_set_rx_owner(priv, p, use_rx_wd);

		entry = STMMAC_GET_ENTRY(entry, priv->dma_rx_size);
	पूर्ण
	rx_q->dirty_rx = entry;
	rx_q->rx_tail_addr = rx_q->dma_rx_phy +
			    (rx_q->dirty_rx * माप(काष्ठा dma_desc));
	sपंचांगmac_set_rx_tail_ptr(priv, priv->ioaddr, rx_q->rx_tail_addr, queue);
पूर्ण

अटल अचिन्हित पूर्णांक sपंचांगmac_rx_buf1_len(काष्ठा sपंचांगmac_priv *priv,
				       काष्ठा dma_desc *p,
				       पूर्णांक status, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक plen = 0, hlen = 0;
	पूर्णांक coe = priv->hw->rx_csum;

	/* Not first descriptor, buffer is always zero */
	अगर (priv->sph && len)
		वापस 0;

	/* First descriptor, get split header length */
	sपंचांगmac_get_rx_header_len(priv, p, &hlen);
	अगर (priv->sph && hlen) अणु
		priv->xstats.rx_split_hdr_pkt_n++;
		वापस hlen;
	पूर्ण

	/* First descriptor, not last descriptor and not split header */
	अगर (status & rx_not_ls)
		वापस priv->dma_buf_sz;

	plen = sपंचांगmac_get_rx_frame_len(priv, p, coe);

	/* First descriptor and last descriptor and not split header */
	वापस min_t(अचिन्हित पूर्णांक, priv->dma_buf_sz, plen);
पूर्ण

अटल अचिन्हित पूर्णांक sपंचांगmac_rx_buf2_len(काष्ठा sपंचांगmac_priv *priv,
				       काष्ठा dma_desc *p,
				       पूर्णांक status, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक coe = priv->hw->rx_csum;
	अचिन्हित पूर्णांक plen = 0;

	/* Not split header, buffer is not available */
	अगर (!priv->sph)
		वापस 0;

	/* Not last descriptor */
	अगर (status & rx_not_ls)
		वापस priv->dma_buf_sz;

	plen = sपंचांगmac_get_rx_frame_len(priv, p, coe);

	/* Last descriptor */
	वापस plen - len;
पूर्ण

अटल पूर्णांक sपंचांगmac_xdp_xmit_xdpf(काष्ठा sपंचांगmac_priv *priv, पूर्णांक queue,
				काष्ठा xdp_frame *xdpf, bool dma_map)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	अचिन्हित पूर्णांक entry = tx_q->cur_tx;
	काष्ठा dma_desc *tx_desc;
	dma_addr_t dma_addr;
	bool set_ic;

	अगर (sपंचांगmac_tx_avail(priv, queue) < STMMAC_TX_THRESH(priv))
		वापस STMMAC_XDP_CONSUMED;

	अगर (likely(priv->extend_desc))
		tx_desc = (काष्ठा dma_desc *)(tx_q->dma_etx + entry);
	अन्यथा अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		tx_desc = &tx_q->dma_entx[entry].basic;
	अन्यथा
		tx_desc = tx_q->dma_tx + entry;

	अगर (dma_map) अणु
		dma_addr = dma_map_single(priv->device, xdpf->data,
					  xdpf->len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->device, dma_addr))
			वापस STMMAC_XDP_CONSUMED;

		tx_q->tx_skbuff_dma[entry].buf_type = STMMAC_TXBUF_T_XDP_NDO;
	पूर्ण अन्यथा अणु
		काष्ठा page *page = virt_to_page(xdpf->data);

		dma_addr = page_pool_get_dma_addr(page) + माप(*xdpf) +
			   xdpf->headroom;
		dma_sync_single_क्रम_device(priv->device, dma_addr,
					   xdpf->len, DMA_BIसूचीECTIONAL);

		tx_q->tx_skbuff_dma[entry].buf_type = STMMAC_TXBUF_T_XDP_TX;
	पूर्ण

	tx_q->tx_skbuff_dma[entry].buf = dma_addr;
	tx_q->tx_skbuff_dma[entry].map_as_page = false;
	tx_q->tx_skbuff_dma[entry].len = xdpf->len;
	tx_q->tx_skbuff_dma[entry].last_segment = true;
	tx_q->tx_skbuff_dma[entry].is_jumbo = false;

	tx_q->xdpf[entry] = xdpf;

	sपंचांगmac_set_desc_addr(priv, tx_desc, dma_addr);

	sपंचांगmac_prepare_tx_desc(priv, tx_desc, 1, xdpf->len,
			       true, priv->mode, true, true,
			       xdpf->len);

	tx_q->tx_count_frames++;

	अगर (tx_q->tx_count_frames % priv->tx_coal_frames[queue] == 0)
		set_ic = true;
	अन्यथा
		set_ic = false;

	अगर (set_ic) अणु
		tx_q->tx_count_frames = 0;
		sपंचांगmac_set_tx_ic(priv, tx_desc);
		priv->xstats.tx_set_ic_bit++;
	पूर्ण

	sपंचांगmac_enable_dma_transmission(priv, priv->ioaddr);

	entry = STMMAC_GET_ENTRY(entry, priv->dma_tx_size);
	tx_q->cur_tx = entry;

	वापस STMMAC_XDP_TX;
पूर्ण

अटल पूर्णांक sपंचांगmac_xdp_get_tx_queue(काष्ठा sपंचांगmac_priv *priv,
				   पूर्णांक cpu)
अणु
	पूर्णांक index = cpu;

	अगर (unlikely(index < 0))
		index = 0;

	जबतक (index >= priv->plat->tx_queues_to_use)
		index -= priv->plat->tx_queues_to_use;

	वापस index;
पूर्ण

अटल पूर्णांक sपंचांगmac_xdp_xmit_back(काष्ठा sपंचांगmac_priv *priv,
				काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_frame *xdpf = xdp_convert_buff_to_frame(xdp);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा netdev_queue *nq;
	पूर्णांक queue;
	पूर्णांक res;

	अगर (unlikely(!xdpf))
		वापस STMMAC_XDP_CONSUMED;

	queue = sपंचांगmac_xdp_get_tx_queue(priv, cpu);
	nq = netdev_get_tx_queue(priv->dev, queue);

	__netअगर_tx_lock(nq, cpu);
	/* Aव्योमs TX समय-out as we are sharing with slow path */
	nq->trans_start = jअगरfies;

	res = sपंचांगmac_xdp_xmit_xdpf(priv, queue, xdpf, false);
	अगर (res == STMMAC_XDP_TX)
		sपंचांगmac_flush_tx_descriptors(priv, queue);

	__netअगर_tx_unlock(nq);

	वापस res;
पूर्ण

/* This function assumes rcu_पढ़ो_lock() is held by the caller. */
अटल पूर्णांक __sपंचांगmac_xdp_run_prog(काष्ठा sपंचांगmac_priv *priv,
				 काष्ठा bpf_prog *prog,
				 काष्ठा xdp_buff *xdp)
अणु
	u32 act;
	पूर्णांक res;

	act = bpf_prog_run_xdp(prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		res = STMMAC_XDP_PASS;
		अवरोध;
	हाल XDP_TX:
		res = sपंचांगmac_xdp_xmit_back(priv, xdp);
		अवरोध;
	हाल XDP_REसूचीECT:
		अगर (xdp_करो_redirect(priv->dev, xdp, prog) < 0)
			res = STMMAC_XDP_CONSUMED;
		अन्यथा
			res = STMMAC_XDP_REसूचीECT;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(priv->dev, prog, act);
		fallthrough;
	हाल XDP_DROP:
		res = STMMAC_XDP_CONSUMED;
		अवरोध;
	पूर्ण

	वापस res;
पूर्ण

अटल काष्ठा sk_buff *sपंचांगmac_xdp_run_prog(काष्ठा sपंचांगmac_priv *priv,
					   काष्ठा xdp_buff *xdp)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक res;

	rcu_पढ़ो_lock();

	prog = READ_ONCE(priv->xdp_prog);
	अगर (!prog) अणु
		res = STMMAC_XDP_PASS;
		जाओ unlock;
	पूर्ण

	res = __sपंचांगmac_xdp_run_prog(priv, prog, xdp);
unlock:
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-res);
पूर्ण

अटल व्योम sपंचांगmac_finalize_xdp_rx(काष्ठा sपंचांगmac_priv *priv,
				   पूर्णांक xdp_status)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक queue;

	queue = sपंचांगmac_xdp_get_tx_queue(priv, cpu);

	अगर (xdp_status & STMMAC_XDP_TX)
		sपंचांगmac_tx_समयr_arm(priv, queue);

	अगर (xdp_status & STMMAC_XDP_REसूचीECT)
		xdp_करो_flush();
पूर्ण

अटल काष्ठा sk_buff *sपंचांगmac_स्थिरruct_skb_zc(काष्ठा sपंचांगmac_channel *ch,
					       काष्ठा xdp_buff *xdp)
अणु
	अचिन्हित पूर्णांक metasize = xdp->data - xdp->data_meta;
	अचिन्हित पूर्णांक datasize = xdp->data_end - xdp->data;
	काष्ठा sk_buff *skb;

	skb = __napi_alloc_skb(&ch->rxtx_napi,
			       xdp->data_end - xdp->data_hard_start,
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		वापस शून्य;

	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	स_नकल(__skb_put(skb, datasize), xdp->data, datasize);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

	वापस skb;
पूर्ण

अटल व्योम sपंचांगmac_dispatch_skb_zc(काष्ठा sपंचांगmac_priv *priv, u32 queue,
				   काष्ठा dma_desc *p, काष्ठा dma_desc *np,
				   काष्ठा xdp_buff *xdp)
अणु
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	अचिन्हित पूर्णांक len = xdp->data_end - xdp->data;
	क्रमागत pkt_hash_types hash_type;
	पूर्णांक coe = priv->hw->rx_csum;
	काष्ठा sk_buff *skb;
	u32 hash;

	skb = sपंचांगmac_स्थिरruct_skb_zc(ch, xdp);
	अगर (!skb) अणु
		priv->dev->stats.rx_dropped++;
		वापस;
	पूर्ण

	sपंचांगmac_get_rx_hwtstamp(priv, p, np, skb);
	sपंचांगmac_rx_vlan(priv->dev, skb);
	skb->protocol = eth_type_trans(skb, priv->dev);

	अगर (unlikely(!coe))
		skb_checksum_none_निश्चित(skb);
	अन्यथा
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (!sपंचांगmac_get_rx_hash(priv, p, &hash, &hash_type))
		skb_set_hash(skb, hash, hash_type);

	skb_record_rx_queue(skb, queue);
	napi_gro_receive(&ch->rxtx_napi, skb);

	priv->dev->stats.rx_packets++;
	priv->dev->stats.rx_bytes += len;
पूर्ण

अटल bool sपंचांगmac_rx_refill_zc(काष्ठा sपंचांगmac_priv *priv, u32 queue, u32 budget)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	अचिन्हित पूर्णांक entry = rx_q->dirty_rx;
	काष्ठा dma_desc *rx_desc = शून्य;
	bool ret = true;

	budget = min(budget, sपंचांगmac_rx_dirty(priv, queue));

	जबतक (budget-- > 0 && entry != rx_q->cur_rx) अणु
		काष्ठा sपंचांगmac_rx_buffer *buf = &rx_q->buf_pool[entry];
		dma_addr_t dma_addr;
		bool use_rx_wd;

		अगर (!buf->xdp) अणु
			buf->xdp = xsk_buff_alloc(rx_q->xsk_pool);
			अगर (!buf->xdp) अणु
				ret = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (priv->extend_desc)
			rx_desc = (काष्ठा dma_desc *)(rx_q->dma_erx + entry);
		अन्यथा
			rx_desc = rx_q->dma_rx + entry;

		dma_addr = xsk_buff_xdp_get_dma(buf->xdp);
		sपंचांगmac_set_desc_addr(priv, rx_desc, dma_addr);
		sपंचांगmac_set_desc_sec_addr(priv, rx_desc, 0, false);
		sपंचांगmac_refill_desc3(priv, rx_q, rx_desc);

		rx_q->rx_count_frames++;
		rx_q->rx_count_frames += priv->rx_coal_frames[queue];
		अगर (rx_q->rx_count_frames > priv->rx_coal_frames[queue])
			rx_q->rx_count_frames = 0;

		use_rx_wd = !priv->rx_coal_frames[queue];
		use_rx_wd |= rx_q->rx_count_frames > 0;
		अगर (!priv->use_riwt)
			use_rx_wd = false;

		dma_wmb();
		sपंचांगmac_set_rx_owner(priv, rx_desc, use_rx_wd);

		entry = STMMAC_GET_ENTRY(entry, priv->dma_rx_size);
	पूर्ण

	अगर (rx_desc) अणु
		rx_q->dirty_rx = entry;
		rx_q->rx_tail_addr = rx_q->dma_rx_phy +
				     (rx_q->dirty_rx * माप(काष्ठा dma_desc));
		sपंचांगmac_set_rx_tail_ptr(priv, priv->ioaddr, rx_q->rx_tail_addr, queue);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_rx_zc(काष्ठा sपंचांगmac_priv *priv, पूर्णांक limit, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	अचिन्हित पूर्णांक count = 0, error = 0, len = 0;
	पूर्णांक dirty = sपंचांगmac_rx_dirty(priv, queue);
	अचिन्हित पूर्णांक next_entry = rx_q->cur_rx;
	अचिन्हित पूर्णांक desc_size;
	काष्ठा bpf_prog *prog;
	bool failure = false;
	पूर्णांक xdp_status = 0;
	पूर्णांक status = 0;

	अगर (netअगर_msg_rx_status(priv)) अणु
		व्योम *rx_head;

		netdev_dbg(priv->dev, "%s: descriptor ring:\n", __func__);
		अगर (priv->extend_desc) अणु
			rx_head = (व्योम *)rx_q->dma_erx;
			desc_size = माप(काष्ठा dma_extended_desc);
		पूर्ण अन्यथा अणु
			rx_head = (व्योम *)rx_q->dma_rx;
			desc_size = माप(काष्ठा dma_desc);
		पूर्ण

		sपंचांगmac_display_ring(priv, rx_head, priv->dma_rx_size, true,
				    rx_q->dma_rx_phy, desc_size);
	पूर्ण
	जबतक (count < limit) अणु
		काष्ठा sपंचांगmac_rx_buffer *buf;
		अचिन्हित पूर्णांक buf1_len = 0;
		काष्ठा dma_desc *np, *p;
		पूर्णांक entry;
		पूर्णांक res;

		अगर (!count && rx_q->state_saved) अणु
			error = rx_q->state.error;
			len = rx_q->state.len;
		पूर्ण अन्यथा अणु
			rx_q->state_saved = false;
			error = 0;
			len = 0;
		पूर्ण

		अगर (count >= limit)
			अवरोध;

पढ़ो_again:
		buf1_len = 0;
		entry = next_entry;
		buf = &rx_q->buf_pool[entry];

		अगर (dirty >= STMMAC_RX_FILL_BATCH) अणु
			failure = failure ||
				  !sपंचांगmac_rx_refill_zc(priv, queue, dirty);
			dirty = 0;
		पूर्ण

		अगर (priv->extend_desc)
			p = (काष्ठा dma_desc *)(rx_q->dma_erx + entry);
		अन्यथा
			p = rx_q->dma_rx + entry;

		/* पढ़ो the status of the incoming frame */
		status = sपंचांगmac_rx_status(priv, &priv->dev->stats,
					  &priv->xstats, p);
		/* check अगर managed by the DMA otherwise go ahead */
		अगर (unlikely(status & dma_own))
			अवरोध;

		/* Prefetch the next RX descriptor */
		rx_q->cur_rx = STMMAC_GET_ENTRY(rx_q->cur_rx,
						priv->dma_rx_size);
		next_entry = rx_q->cur_rx;

		अगर (priv->extend_desc)
			np = (काष्ठा dma_desc *)(rx_q->dma_erx + next_entry);
		अन्यथा
			np = rx_q->dma_rx + next_entry;

		prefetch(np);

		अगर (priv->extend_desc)
			sपंचांगmac_rx_extended_status(priv, &priv->dev->stats,
						  &priv->xstats,
						  rx_q->dma_erx + entry);
		अगर (unlikely(status == discard_frame)) अणु
			xsk_buff_मुक्त(buf->xdp);
			buf->xdp = शून्य;
			dirty++;
			error = 1;
			अगर (!priv->hwts_rx_en)
				priv->dev->stats.rx_errors++;
		पूर्ण

		अगर (unlikely(error && (status & rx_not_ls)))
			जाओ पढ़ो_again;
		अगर (unlikely(error)) अणु
			count++;
			जारी;
		पूर्ण

		/* Ensure a valid XSK buffer beक्रमe proceed */
		अगर (!buf->xdp)
			अवरोध;

		/* XSK pool expects RX frame 1:1 mapped to XSK buffer */
		अगर (likely(status & rx_not_ls)) अणु
			xsk_buff_मुक्त(buf->xdp);
			buf->xdp = शून्य;
			dirty++;
			count++;
			जाओ पढ़ो_again;
		पूर्ण

		/* XDP ZC Frame only support primary buffers क्रम now */
		buf1_len = sपंचांगmac_rx_buf1_len(priv, p, status, len);
		len += buf1_len;

		/* ACS is set; GMAC core strips PAD/FCS क्रम IEEE 802.3
		 * Type frames (LLC/LLC-SNAP)
		 *
		 * llc_snap is never checked in GMAC >= 4, so this ACS
		 * feature is always disabled and packets need to be
		 * stripped manually.
		 */
		अगर (likely(!(status & rx_not_ls)) &&
		    (likely(priv->synopsys_id >= DWMAC_CORE_4_00) ||
		     unlikely(status != llc_snap))) अणु
			buf1_len -= ETH_FCS_LEN;
			len -= ETH_FCS_LEN;
		पूर्ण

		/* RX buffer is good and fit पूर्णांकo a XSK pool buffer */
		buf->xdp->data_end = buf->xdp->data + buf1_len;
		xsk_buff_dma_sync_क्रम_cpu(buf->xdp, rx_q->xsk_pool);

		rcu_पढ़ो_lock();
		prog = READ_ONCE(priv->xdp_prog);
		res = __sपंचांगmac_xdp_run_prog(priv, prog, buf->xdp);
		rcu_पढ़ो_unlock();

		चयन (res) अणु
		हाल STMMAC_XDP_PASS:
			sपंचांगmac_dispatch_skb_zc(priv, queue, p, np, buf->xdp);
			xsk_buff_मुक्त(buf->xdp);
			अवरोध;
		हाल STMMAC_XDP_CONSUMED:
			xsk_buff_मुक्त(buf->xdp);
			priv->dev->stats.rx_dropped++;
			अवरोध;
		हाल STMMAC_XDP_TX:
		हाल STMMAC_XDP_REसूचीECT:
			xdp_status |= res;
			अवरोध;
		पूर्ण

		buf->xdp = शून्य;
		dirty++;
		count++;
	पूर्ण

	अगर (status & rx_not_ls) अणु
		rx_q->state_saved = true;
		rx_q->state.error = error;
		rx_q->state.len = len;
	पूर्ण

	sपंचांगmac_finalize_xdp_rx(priv, xdp_status);

	अगर (xsk_uses_need_wakeup(rx_q->xsk_pool)) अणु
		अगर (failure || sपंचांगmac_rx_dirty(priv, queue) > 0)
			xsk_set_rx_need_wakeup(rx_q->xsk_pool);
		अन्यथा
			xsk_clear_rx_need_wakeup(rx_q->xsk_pool);

		वापस (पूर्णांक)count;
	पूर्ण

	वापस failure ? limit : (पूर्णांक)count;
पूर्ण

/**
 * sपंचांगmac_rx - manage the receive process
 * @priv: driver निजी काष्ठाure
 * @limit: napi bugget
 * @queue: RX queue index.
 * Description :  this the function called by the napi poll method.
 * It माला_लो all the frames inside the ring.
 */
अटल पूर्णांक sपंचांगmac_rx(काष्ठा sपंचांगmac_priv *priv, पूर्णांक limit, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	अचिन्हित पूर्णांक count = 0, error = 0, len = 0;
	पूर्णांक status = 0, coe = priv->hw->rx_csum;
	अचिन्हित पूर्णांक next_entry = rx_q->cur_rx;
	क्रमागत dma_data_direction dma_dir;
	अचिन्हित पूर्णांक desc_size;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा xdp_buff xdp;
	पूर्णांक xdp_status = 0;
	पूर्णांक buf_sz;

	dma_dir = page_pool_get_dma_dir(rx_q->page_pool);
	buf_sz = DIV_ROUND_UP(priv->dma_buf_sz, PAGE_SIZE) * PAGE_SIZE;

	अगर (netअगर_msg_rx_status(priv)) अणु
		व्योम *rx_head;

		netdev_dbg(priv->dev, "%s: descriptor ring:\n", __func__);
		अगर (priv->extend_desc) अणु
			rx_head = (व्योम *)rx_q->dma_erx;
			desc_size = माप(काष्ठा dma_extended_desc);
		पूर्ण अन्यथा अणु
			rx_head = (व्योम *)rx_q->dma_rx;
			desc_size = माप(काष्ठा dma_desc);
		पूर्ण

		sपंचांगmac_display_ring(priv, rx_head, priv->dma_rx_size, true,
				    rx_q->dma_rx_phy, desc_size);
	पूर्ण
	जबतक (count < limit) अणु
		अचिन्हित पूर्णांक buf1_len = 0, buf2_len = 0;
		क्रमागत pkt_hash_types hash_type;
		काष्ठा sपंचांगmac_rx_buffer *buf;
		काष्ठा dma_desc *np, *p;
		पूर्णांक entry;
		u32 hash;

		अगर (!count && rx_q->state_saved) अणु
			skb = rx_q->state.skb;
			error = rx_q->state.error;
			len = rx_q->state.len;
		पूर्ण अन्यथा अणु
			rx_q->state_saved = false;
			skb = शून्य;
			error = 0;
			len = 0;
		पूर्ण

		अगर (count >= limit)
			अवरोध;

पढ़ो_again:
		buf1_len = 0;
		buf2_len = 0;
		entry = next_entry;
		buf = &rx_q->buf_pool[entry];

		अगर (priv->extend_desc)
			p = (काष्ठा dma_desc *)(rx_q->dma_erx + entry);
		अन्यथा
			p = rx_q->dma_rx + entry;

		/* पढ़ो the status of the incoming frame */
		status = sपंचांगmac_rx_status(priv, &priv->dev->stats,
				&priv->xstats, p);
		/* check अगर managed by the DMA otherwise go ahead */
		अगर (unlikely(status & dma_own))
			अवरोध;

		rx_q->cur_rx = STMMAC_GET_ENTRY(rx_q->cur_rx,
						priv->dma_rx_size);
		next_entry = rx_q->cur_rx;

		अगर (priv->extend_desc)
			np = (काष्ठा dma_desc *)(rx_q->dma_erx + next_entry);
		अन्यथा
			np = rx_q->dma_rx + next_entry;

		prefetch(np);

		अगर (priv->extend_desc)
			sपंचांगmac_rx_extended_status(priv, &priv->dev->stats,
					&priv->xstats, rx_q->dma_erx + entry);
		अगर (unlikely(status == discard_frame)) अणु
			page_pool_recycle_direct(rx_q->page_pool, buf->page);
			buf->page = शून्य;
			error = 1;
			अगर (!priv->hwts_rx_en)
				priv->dev->stats.rx_errors++;
		पूर्ण

		अगर (unlikely(error && (status & rx_not_ls)))
			जाओ पढ़ो_again;
		अगर (unlikely(error)) अणु
			dev_kमुक्त_skb(skb);
			skb = शून्य;
			count++;
			जारी;
		पूर्ण

		/* Buffer is good. Go on. */

		prefetch(page_address(buf->page));
		अगर (buf->sec_page)
			prefetch(page_address(buf->sec_page));

		buf1_len = sपंचांगmac_rx_buf1_len(priv, p, status, len);
		len += buf1_len;
		buf2_len = sपंचांगmac_rx_buf2_len(priv, p, status, len);
		len += buf2_len;

		/* ACS is set; GMAC core strips PAD/FCS क्रम IEEE 802.3
		 * Type frames (LLC/LLC-SNAP)
		 *
		 * llc_snap is never checked in GMAC >= 4, so this ACS
		 * feature is always disabled and packets need to be
		 * stripped manually.
		 */
		अगर (likely(!(status & rx_not_ls)) &&
		    (likely(priv->synopsys_id >= DWMAC_CORE_4_00) ||
		     unlikely(status != llc_snap))) अणु
			अगर (buf2_len)
				buf2_len -= ETH_FCS_LEN;
			अन्यथा
				buf1_len -= ETH_FCS_LEN;

			len -= ETH_FCS_LEN;
		पूर्ण

		अगर (!skb) अणु
			अचिन्हित पूर्णांक pre_len, sync_len;

			dma_sync_single_क्रम_cpu(priv->device, buf->addr,
						buf1_len, dma_dir);

			xdp.data = page_address(buf->page) + buf->page_offset;
			xdp.data_end = xdp.data + buf1_len;
			xdp.data_hard_start = page_address(buf->page);
			xdp_set_data_meta_invalid(&xdp);
			xdp.frame_sz = buf_sz;
			xdp.rxq = &rx_q->xdp_rxq;

			pre_len = xdp.data_end - xdp.data_hard_start -
				  buf->page_offset;
			skb = sपंचांगmac_xdp_run_prog(priv, &xdp);
			/* Due xdp_adjust_tail: DMA sync क्रम_device
			 * cover max len CPU touch
			 */
			sync_len = xdp.data_end - xdp.data_hard_start -
				   buf->page_offset;
			sync_len = max(sync_len, pre_len);

			/* For Not XDP_PASS verdict */
			अगर (IS_ERR(skb)) अणु
				अचिन्हित पूर्णांक xdp_res = -PTR_ERR(skb);

				अगर (xdp_res & STMMAC_XDP_CONSUMED) अणु
					page_pool_put_page(rx_q->page_pool,
							   virt_to_head_page(xdp.data),
							   sync_len, true);
					buf->page = शून्य;
					priv->dev->stats.rx_dropped++;

					/* Clear skb as it was set as
					 * status by XDP program.
					 */
					skb = शून्य;

					अगर (unlikely((status & rx_not_ls)))
						जाओ पढ़ो_again;

					count++;
					जारी;
				पूर्ण अन्यथा अगर (xdp_res & (STMMAC_XDP_TX |
						      STMMAC_XDP_REसूचीECT)) अणु
					xdp_status |= xdp_res;
					buf->page = शून्य;
					skb = शून्य;
					count++;
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!skb) अणु
			/* XDP program may expand or reduce tail */
			buf1_len = xdp.data_end - xdp.data;

			skb = napi_alloc_skb(&ch->rx_napi, buf1_len);
			अगर (!skb) अणु
				priv->dev->stats.rx_dropped++;
				count++;
				जाओ drain_data;
			पूर्ण

			/* XDP program may adjust header */
			skb_copy_to_linear_data(skb, xdp.data, buf1_len);
			skb_put(skb, buf1_len);

			/* Data payload copied पूर्णांकo SKB, page पढ़ोy क्रम recycle */
			page_pool_recycle_direct(rx_q->page_pool, buf->page);
			buf->page = शून्य;
		पूर्ण अन्यथा अगर (buf1_len) अणु
			dma_sync_single_क्रम_cpu(priv->device, buf->addr,
						buf1_len, dma_dir);
			skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
					buf->page, buf->page_offset, buf1_len,
					priv->dma_buf_sz);

			/* Data payload appended पूर्णांकo SKB */
			page_pool_release_page(rx_q->page_pool, buf->page);
			buf->page = शून्य;
		पूर्ण

		अगर (buf2_len) अणु
			dma_sync_single_क्रम_cpu(priv->device, buf->sec_addr,
						buf2_len, dma_dir);
			skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
					buf->sec_page, 0, buf2_len,
					priv->dma_buf_sz);

			/* Data payload appended पूर्णांकo SKB */
			page_pool_release_page(rx_q->page_pool, buf->sec_page);
			buf->sec_page = शून्य;
		पूर्ण

drain_data:
		अगर (likely(status & rx_not_ls))
			जाओ पढ़ो_again;
		अगर (!skb)
			जारी;

		/* Got entire packet पूर्णांकo SKB. Finish it. */

		sपंचांगmac_get_rx_hwtstamp(priv, p, np, skb);
		sपंचांगmac_rx_vlan(priv->dev, skb);
		skb->protocol = eth_type_trans(skb, priv->dev);

		अगर (unlikely(!coe))
			skb_checksum_none_निश्चित(skb);
		अन्यथा
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		अगर (!sपंचांगmac_get_rx_hash(priv, p, &hash, &hash_type))
			skb_set_hash(skb, hash, hash_type);

		skb_record_rx_queue(skb, queue);
		napi_gro_receive(&ch->rx_napi, skb);
		skb = शून्य;

		priv->dev->stats.rx_packets++;
		priv->dev->stats.rx_bytes += len;
		count++;
	पूर्ण

	अगर (status & rx_not_ls || skb) अणु
		rx_q->state_saved = true;
		rx_q->state.skb = skb;
		rx_q->state.error = error;
		rx_q->state.len = len;
	पूर्ण

	sपंचांगmac_finalize_xdp_rx(priv, xdp_status);

	sपंचांगmac_rx_refill(priv, queue);

	priv->xstats.rx_pkt_n += count;

	वापस count;
पूर्ण

अटल पूर्णांक sपंचांगmac_napi_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sपंचांगmac_channel *ch =
		container_of(napi, काष्ठा sपंचांगmac_channel, rx_napi);
	काष्ठा sपंचांगmac_priv *priv = ch->priv_data;
	u32 chan = ch->index;
	पूर्णांक work_करोne;

	priv->xstats.napi_poll++;

	work_करोne = sपंचांगmac_rx(priv, budget, chan);
	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ch->lock, flags);
		sपंचांगmac_enable_dma_irq(priv, priv->ioaddr, chan, 1, 0);
		spin_unlock_irqrestore(&ch->lock, flags);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक sपंचांगmac_napi_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sपंचांगmac_channel *ch =
		container_of(napi, काष्ठा sपंचांगmac_channel, tx_napi);
	काष्ठा sपंचांगmac_priv *priv = ch->priv_data;
	u32 chan = ch->index;
	पूर्णांक work_करोne;

	priv->xstats.napi_poll++;

	work_करोne = sपंचांगmac_tx_clean(priv, budget, chan);
	work_करोne = min(work_करोne, budget);

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ch->lock, flags);
		sपंचांगmac_enable_dma_irq(priv, priv->ioaddr, chan, 0, 1);
		spin_unlock_irqrestore(&ch->lock, flags);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक sपंचांगmac_napi_poll_rxtx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sपंचांगmac_channel *ch =
		container_of(napi, काष्ठा sपंचांगmac_channel, rxtx_napi);
	काष्ठा sपंचांगmac_priv *priv = ch->priv_data;
	पूर्णांक rx_करोne, tx_करोne;
	u32 chan = ch->index;

	priv->xstats.napi_poll++;

	tx_करोne = sपंचांगmac_tx_clean(priv, budget, chan);
	tx_करोne = min(tx_करोne, budget);

	rx_करोne = sपंचांगmac_rx_zc(priv, budget, chan);

	/* If either TX or RX work is not complete, वापस budget
	 * and keep pooling
	 */
	अगर (tx_करोne >= budget || rx_करोne >= budget)
		वापस budget;

	/* all work करोne, निकास the polling mode */
	अगर (napi_complete_करोne(napi, rx_करोne)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ch->lock, flags);
		/* Both RX and TX work करोne are compelte,
		 * so enable both RX & TX IRQs.
		 */
		sपंचांगmac_enable_dma_irq(priv, priv->ioaddr, chan, 1, 1);
		spin_unlock_irqrestore(&ch->lock, flags);
	पूर्ण

	वापस min(rx_करोne, budget - 1);
पूर्ण

/**
 *  sपंचांगmac_tx_समयout
 *  @dev : Poपूर्णांकer to net device काष्ठाure
 *  @txqueue: the index of the hanging transmit queue
 *  Description: this function is called when a packet transmission fails to
 *   complete within a reasonable समय. The driver will mark the error in the
 *   netdev काष्ठाure and arrange क्रम the device to be reset to a sane state
 *   in order to transmit a new packet.
 */
अटल व्योम sपंचांगmac_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	sपंचांगmac_global_err(priv);
पूर्ण

/**
 *  sपंचांगmac_set_rx_mode - entry poपूर्णांक क्रम multicast addressing
 *  @dev : poपूर्णांकer to the device काष्ठाure
 *  Description:
 *  This function is a driver entry poपूर्णांक which माला_लो called by the kernel
 *  whenever multicast addresses must be enabled/disabled.
 *  Return value:
 *  व्योम.
 */
अटल व्योम sपंचांगmac_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	sपंचांगmac_set_filter(priv, priv->hw, dev);
पूर्ण

/**
 *  sपंचांगmac_change_mtu - entry poपूर्णांक to change MTU size क्रम the device.
 *  @dev : device poपूर्णांकer.
 *  @new_mtu : the new MTU size क्रम the device.
 *  Description: the Maximum Transfer Unit (MTU) is used by the network layer
 *  to drive packet transmission. Ethernet has an MTU of 1500 octets
 *  (ETH_DATA_LEN). This value can be changed with अगरconfig.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */
अटल पूर्णांक sपंचांगmac_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक txfअगरosz = priv->plat->tx_fअगरo_size;
	स्थिर पूर्णांक mtu = new_mtu;

	अगर (txfअगरosz == 0)
		txfअगरosz = priv->dma_cap.tx_fअगरo_size;

	txfअगरosz /= priv->plat->tx_queues_to_use;

	अगर (netअगर_running(dev)) अणु
		netdev_err(priv->dev, "must be stopped to change its MTU\n");
		वापस -EBUSY;
	पूर्ण

	अगर (sपंचांगmac_xdp_is_enabled(priv) && new_mtu > ETH_DATA_LEN) अणु
		netdev_dbg(priv->dev, "Jumbo frames not supported for XDP\n");
		वापस -EINVAL;
	पूर्ण

	new_mtu = STMMAC_ALIGN(new_mtu);

	/* If condition true, FIFO is too small or MTU too large */
	अगर ((txfअगरosz < new_mtu) || (new_mtu > BUF_SIZE_16KiB))
		वापस -EINVAL;

	dev->mtu = mtu;

	netdev_update_features(dev);

	वापस 0;
पूर्ण

अटल netdev_features_t sपंचांगmac_fix_features(काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (priv->plat->rx_coe == STMMAC_RX_COE_NONE)
		features &= ~NETIF_F_RXCSUM;

	अगर (!priv->plat->tx_coe)
		features &= ~NETIF_F_CSUM_MASK;

	/* Some GMAC devices have a bugged Jumbo frame support that
	 * needs to have the Tx COE disabled क्रम oversized frames
	 * (due to limited buffer sizes). In this हाल we disable
	 * the TX csum insertion in the TDES and not use SF.
	 */
	अगर (priv->plat->bugged_jumbo && (dev->mtu > ETH_DATA_LEN))
		features &= ~NETIF_F_CSUM_MASK;

	/* Disable tso अगर asked by ethtool */
	अगर ((priv->plat->tso_en) && (priv->dma_cap.tsoen)) अणु
		अगर (features & NETIF_F_TSO)
			priv->tso = true;
		अन्यथा
			priv->tso = false;
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक sपंचांगmac_set_features(काष्ठा net_device *netdev,
			       netdev_features_t features)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(netdev);
	bool sph_en;
	u32 chan;

	/* Keep the COE Type in हाल of csum is supporting */
	अगर (features & NETIF_F_RXCSUM)
		priv->hw->rx_csum = priv->plat->rx_coe;
	अन्यथा
		priv->hw->rx_csum = 0;
	/* No check needed because rx_coe has been set beक्रमe and it will be
	 * fixed in हाल of issue.
	 */
	sपंचांगmac_rx_ipc(priv, priv->hw);

	sph_en = (priv->hw->rx_csum > 0) && priv->sph;

	क्रम (chan = 0; chan < priv->plat->rx_queues_to_use; chan++)
		sपंचांगmac_enable_sph(priv, priv->ioaddr, sph_en, chan);

	वापस 0;
पूर्ण

अटल व्योम sपंचांगmac_fpe_event_status(काष्ठा sपंचांगmac_priv *priv, पूर्णांक status)
अणु
	काष्ठा sपंचांगmac_fpe_cfg *fpe_cfg = priv->plat->fpe_cfg;
	क्रमागत sपंचांगmac_fpe_state *lo_state = &fpe_cfg->lo_fpe_state;
	क्रमागत sपंचांगmac_fpe_state *lp_state = &fpe_cfg->lp_fpe_state;
	bool *hs_enable = &fpe_cfg->hs_enable;

	अगर (status == FPE_EVENT_UNKNOWN || !*hs_enable)
		वापस;

	/* If LP has sent verअगरy mPacket, LP is FPE capable */
	अगर ((status & FPE_EVENT_RVER) == FPE_EVENT_RVER) अणु
		अगर (*lp_state < FPE_STATE_CAPABLE)
			*lp_state = FPE_STATE_CAPABLE;

		/* If user has requested FPE enable, quickly response */
		अगर (*hs_enable)
			sपंचांगmac_fpe_send_mpacket(priv, priv->ioaddr,
						MPACKET_RESPONSE);
	पूर्ण

	/* If Local has sent verअगरy mPacket, Local is FPE capable */
	अगर ((status & FPE_EVENT_TVER) == FPE_EVENT_TVER) अणु
		अगर (*lo_state < FPE_STATE_CAPABLE)
			*lo_state = FPE_STATE_CAPABLE;
	पूर्ण

	/* If LP has sent response mPacket, LP is entering FPE ON */
	अगर ((status & FPE_EVENT_RRSP) == FPE_EVENT_RRSP)
		*lp_state = FPE_STATE_ENTERING_ON;

	/* If Local has sent response mPacket, Local is entering FPE ON */
	अगर ((status & FPE_EVENT_TRSP) == FPE_EVENT_TRSP)
		*lo_state = FPE_STATE_ENTERING_ON;

	अगर (!test_bit(__FPE_REMOVING, &priv->fpe_task_state) &&
	    !test_and_set_bit(__FPE_TASK_SCHED, &priv->fpe_task_state) &&
	    priv->fpe_wq) अणु
		queue_work(priv->fpe_wq, &priv->fpe_task);
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_common_पूर्णांकerrupt(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 queues_count;
	u32 queue;
	bool xmac;

	xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;
	queues_count = (rx_cnt > tx_cnt) ? rx_cnt : tx_cnt;

	अगर (priv->irq_wake)
		pm_wakeup_event(priv->device, 0);

	अगर (priv->dma_cap.estsel)
		sपंचांगmac_est_irq_status(priv, priv->ioaddr, priv->dev,
				      &priv->xstats, tx_cnt);

	अगर (priv->dma_cap.fpesel) अणु
		पूर्णांक status = sपंचांगmac_fpe_irq_status(priv, priv->ioaddr,
						   priv->dev);

		sपंचांगmac_fpe_event_status(priv, status);
	पूर्ण

	/* To handle GMAC own पूर्णांकerrupts */
	अगर ((priv->plat->has_gmac) || xmac) अणु
		पूर्णांक status = sपंचांगmac_host_irq_status(priv, priv->hw, &priv->xstats);

		अगर (unlikely(status)) अणु
			/* For LPI we need to save the tx status */
			अगर (status & CORE_IRQ_TX_PATH_IN_LPI_MODE)
				priv->tx_path_in_lpi_mode = true;
			अगर (status & CORE_IRQ_TX_PATH_EXIT_LPI_MODE)
				priv->tx_path_in_lpi_mode = false;
		पूर्ण

		क्रम (queue = 0; queue < queues_count; queue++) अणु
			status = sपंचांगmac_host_mtl_irq_status(priv, priv->hw,
							    queue);
		पूर्ण

		/* PCS link status */
		अगर (priv->hw->pcs) अणु
			अगर (priv->xstats.pcs_link)
				netअगर_carrier_on(priv->dev);
			अन्यथा
				netअगर_carrier_off(priv->dev);
		पूर्ण

		sपंचांगmac_बारtamp_पूर्णांकerrupt(priv, priv);
	पूर्ण
पूर्ण

/**
 *  sपंचांगmac_पूर्णांकerrupt - मुख्य ISR
 *  @irq: पूर्णांकerrupt number.
 *  @dev_id: to pass the net device poपूर्णांकer.
 *  Description: this is the मुख्य driver पूर्णांकerrupt service routine.
 *  It can call:
 *  o DMA service routine (to manage incoming frame reception and transmission
 *    status)
 *  o Core पूर्णांकerrupts to manage: remote wake-up, management counter, LPI
 *    पूर्णांकerrupts.
 */
अटल irqवापस_t sपंचांगmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	/* Check अगर adapter is up */
	अगर (test_bit(STMMAC_DOWN, &priv->state))
		वापस IRQ_HANDLED;

	/* Check अगर a fatal error happened */
	अगर (sपंचांगmac_safety_feat_पूर्णांकerrupt(priv))
		वापस IRQ_HANDLED;

	/* To handle Common पूर्णांकerrupts */
	sपंचांगmac_common_पूर्णांकerrupt(priv);

	/* To handle DMA पूर्णांकerrupts */
	sपंचांगmac_dma_पूर्णांकerrupt(priv);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांगmac_mac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (unlikely(!dev)) अणु
		netdev_err(priv->dev, "%s: invalid dev pointer\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	/* Check अगर adapter is up */
	अगर (test_bit(STMMAC_DOWN, &priv->state))
		वापस IRQ_HANDLED;

	/* To handle Common पूर्णांकerrupts */
	sपंचांगmac_common_पूर्णांकerrupt(priv);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांगmac_safety_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (unlikely(!dev)) अणु
		netdev_err(priv->dev, "%s: invalid dev pointer\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	/* Check अगर adapter is up */
	अगर (test_bit(STMMAC_DOWN, &priv->state))
		वापस IRQ_HANDLED;

	/* Check अगर a fatal error happened */
	sपंचांगmac_safety_feat_पूर्णांकerrupt(priv);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांगmac_msi_पूर्णांकr_tx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = (काष्ठा sपंचांगmac_tx_queue *)data;
	पूर्णांक chan = tx_q->queue_index;
	काष्ठा sपंचांगmac_priv *priv;
	पूर्णांक status;

	priv = container_of(tx_q, काष्ठा sपंचांगmac_priv, tx_queue[chan]);

	अगर (unlikely(!data)) अणु
		netdev_err(priv->dev, "%s: invalid dev pointer\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	/* Check अगर adapter is up */
	अगर (test_bit(STMMAC_DOWN, &priv->state))
		वापस IRQ_HANDLED;

	status = sपंचांगmac_napi_check(priv, chan, DMA_सूची_TX);

	अगर (unlikely(status & tx_hard_error_bump_tc)) अणु
		/* Try to bump up the dma threshold on this failure */
		अगर (unlikely(priv->xstats.threshold != SF_DMA_MODE) &&
		    tc <= 256) अणु
			tc += 64;
			अगर (priv->plat->क्रमce_thresh_dma_mode)
				sपंचांगmac_set_dma_operation_mode(priv,
							      tc,
							      tc,
							      chan);
			अन्यथा
				sपंचांगmac_set_dma_operation_mode(priv,
							      tc,
							      SF_DMA_MODE,
							      chan);
			priv->xstats.threshold = tc;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(status == tx_hard_error)) अणु
		sपंचांगmac_tx_err(priv, chan);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांगmac_msi_पूर्णांकr_rx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = (काष्ठा sपंचांगmac_rx_queue *)data;
	पूर्णांक chan = rx_q->queue_index;
	काष्ठा sपंचांगmac_priv *priv;

	priv = container_of(rx_q, काष्ठा sपंचांगmac_priv, rx_queue[chan]);

	अगर (unlikely(!data)) अणु
		netdev_err(priv->dev, "%s: invalid dev pointer\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	/* Check अगर adapter is up */
	अगर (test_bit(STMMAC_DOWN, &priv->state))
		वापस IRQ_HANDLED;

	sपंचांगmac_napi_check(priv, chan, DMA_सूची_RX);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/* Polling receive - used by NETCONSOLE and other diagnostic tools
 * to allow network I/O with पूर्णांकerrupts disabled.
 */
अटल व्योम sपंचांगmac_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	/* If adapter is करोwn, करो nothing */
	अगर (test_bit(STMMAC_DOWN, &priv->state))
		वापस;

	अगर (priv->plat->multi_msi_en) अणु
		क्रम (i = 0; i < priv->plat->rx_queues_to_use; i++)
			sपंचांगmac_msi_पूर्णांकr_rx(0, &priv->rx_queue[i]);

		क्रम (i = 0; i < priv->plat->tx_queues_to_use; i++)
			sपंचांगmac_msi_पूर्णांकr_tx(0, &priv->tx_queue[i]);
	पूर्ण अन्यथा अणु
		disable_irq(dev->irq);
		sपंचांगmac_पूर्णांकerrupt(dev->irq, dev);
		enable_irq(dev->irq);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 *  sपंचांगmac_ioctl - Entry poपूर्णांक क्रम the Ioctl
 *  @dev: Device poपूर्णांकer.
 *  @rq: An IOCTL specefic काष्ठाure, that can contain a poपूर्णांकer to
 *  a proprietary काष्ठाure used to pass inक्रमmation to the driver.
 *  @cmd: IOCTL command
 *  Description:
 *  Currently it supports the phy_mii_ioctl(...) and HW समय stamping.
 */
अटल पूर्णांक sपंचांगmac_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv (dev);
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		ret = phylink_mii_ioctl(priv->phylink, rq, cmd);
		अवरोध;
	हाल SIOCSHWTSTAMP:
		ret = sपंचांगmac_hwtstamp_set(dev, rq);
		अवरोध;
	हाल SIOCGHWTSTAMP:
		ret = sपंचांगmac_hwtstamp_get(dev, rq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				    व्योम *cb_priv)
अणु
	काष्ठा sपंचांगmac_priv *priv = cb_priv;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!tc_cls_can_offload_and_chain0(priv->dev, type_data))
		वापस ret;

	__sपंचांगmac_disable_all_queues(priv);

	चयन (type) अणु
	हाल TC_SETUP_CLSU32:
		ret = sपंचांगmac_tc_setup_cls_u32(priv, priv, type_data);
		अवरोध;
	हाल TC_SETUP_CLSFLOWER:
		ret = sपंचांगmac_tc_setup_cls(priv, priv, type_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sपंचांगmac_enable_all_queues(priv);
	वापस ret;
पूर्ण

अटल LIST_HEAD(sपंचांगmac_block_cb_list);

अटल पूर्णांक sपंचांगmac_setup_tc(काष्ठा net_device *ndev, क्रमागत tc_setup_type type,
			   व्योम *type_data)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &sपंचांगmac_block_cb_list,
						  sपंचांगmac_setup_tc_block_cb,
						  priv, priv, true);
	हाल TC_SETUP_QDISC_CBS:
		वापस sपंचांगmac_tc_setup_cbs(priv, priv, type_data);
	हाल TC_SETUP_QDISC_TAPRIO:
		वापस sपंचांगmac_tc_setup_taprio(priv, priv, type_data);
	हाल TC_SETUP_QDISC_ETF:
		वापस sपंचांगmac_tc_setup_etf(priv, priv, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u16 sपंचांगmac_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			       काष्ठा net_device *sb_dev)
अणु
	पूर्णांक gso = skb_shinfo(skb)->gso_type;

	अगर (gso & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6 | SKB_GSO_UDP_L4)) अणु
		/*
		 * There is no way to determine the number of TSO/USO
		 * capable Queues. Let's use always the Queue 0
		 * because अगर TSO/USO is supported then at least this
		 * one will be capable.
		 */
		वापस 0;
	पूर्ण

	वापस netdev_pick_tx(dev, skb, शून्य) % dev->real_num_tx_queues;
पूर्ण

अटल पूर्णांक sपंचांगmac_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	पूर्णांक ret = 0;

	ret = pm_runसमय_get_sync(priv->device);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->device);
		वापस ret;
	पूर्ण

	ret = eth_mac_addr(ndev, addr);
	अगर (ret)
		जाओ set_mac_error;

	sपंचांगmac_set_umac_addr(priv, priv->hw, ndev->dev_addr, 0);

set_mac_error:
	pm_runसमय_put(priv->device);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल काष्ठा dentry *sपंचांगmac_fs_dir;

अटल व्योम sysfs_display_ring(व्योम *head, पूर्णांक size, पूर्णांक extend_desc,
			       काष्ठा seq_file *seq, dma_addr_t dma_phy_addr)
अणु
	पूर्णांक i;
	काष्ठा dma_extended_desc *ep = (काष्ठा dma_extended_desc *)head;
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)head;
	dma_addr_t dma_addr;

	क्रम (i = 0; i < size; i++) अणु
		अगर (extend_desc) अणु
			dma_addr = dma_phy_addr + i * माप(*ep);
			seq_म_लिखो(seq, "%d [%pad]: 0x%x 0x%x 0x%x 0x%x\n",
				   i, &dma_addr,
				   le32_to_cpu(ep->basic.des0),
				   le32_to_cpu(ep->basic.des1),
				   le32_to_cpu(ep->basic.des2),
				   le32_to_cpu(ep->basic.des3));
			ep++;
		पूर्ण अन्यथा अणु
			dma_addr = dma_phy_addr + i * माप(*p);
			seq_म_लिखो(seq, "%d [%pad]: 0x%x 0x%x 0x%x 0x%x\n",
				   i, &dma_addr,
				   le32_to_cpu(p->des0), le32_to_cpu(p->des1),
				   le32_to_cpu(p->des2), le32_to_cpu(p->des3));
			p++;
		पूर्ण
		seq_म_लिखो(seq, "\n");
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_rings_status_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net_device *dev = seq->निजी;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 rx_count = priv->plat->rx_queues_to_use;
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 queue;

	अगर ((dev->flags & IFF_UP) == 0)
		वापस 0;

	क्रम (queue = 0; queue < rx_count; queue++) अणु
		काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];

		seq_म_लिखो(seq, "RX Queue %d:\n", queue);

		अगर (priv->extend_desc) अणु
			seq_म_लिखो(seq, "Extended descriptor ring:\n");
			sysfs_display_ring((व्योम *)rx_q->dma_erx,
					   priv->dma_rx_size, 1, seq, rx_q->dma_rx_phy);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(seq, "Descriptor ring:\n");
			sysfs_display_ring((व्योम *)rx_q->dma_rx,
					   priv->dma_rx_size, 0, seq, rx_q->dma_rx_phy);
		पूर्ण
	पूर्ण

	क्रम (queue = 0; queue < tx_count; queue++) अणु
		काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];

		seq_म_लिखो(seq, "TX Queue %d:\n", queue);

		अगर (priv->extend_desc) अणु
			seq_म_लिखो(seq, "Extended descriptor ring:\n");
			sysfs_display_ring((व्योम *)tx_q->dma_etx,
					   priv->dma_tx_size, 1, seq, tx_q->dma_tx_phy);
		पूर्ण अन्यथा अगर (!(tx_q->tbs & STMMAC_TBS_AVAIL)) अणु
			seq_म_लिखो(seq, "Descriptor ring:\n");
			sysfs_display_ring((व्योम *)tx_q->dma_tx,
					   priv->dma_tx_size, 0, seq, tx_q->dma_tx_phy);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sपंचांगmac_rings_status);

अटल पूर्णांक sपंचांगmac_dma_cap_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net_device *dev = seq->निजी;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (!priv->hw_cap_support) अणु
		seq_म_लिखो(seq, "DMA HW features not supported\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(seq, "==============================\n");
	seq_म_लिखो(seq, "\tDMA HW features\n");
	seq_म_लिखो(seq, "==============================\n");

	seq_म_लिखो(seq, "\t10/100 Mbps: %s\n",
		   (priv->dma_cap.mbps_10_100) ? "Y" : "N");
	seq_म_लिखो(seq, "\t1000 Mbps: %s\n",
		   (priv->dma_cap.mbps_1000) ? "Y" : "N");
	seq_म_लिखो(seq, "\tHalf duplex: %s\n",
		   (priv->dma_cap.half_duplex) ? "Y" : "N");
	seq_म_लिखो(seq, "\tHash Filter: %s\n",
		   (priv->dma_cap.hash_filter) ? "Y" : "N");
	seq_म_लिखो(seq, "\tMultiple MAC address registers: %s\n",
		   (priv->dma_cap.multi_addr) ? "Y" : "N");
	seq_म_लिखो(seq, "\tPCS (TBI/SGMII/RTBI PHY interfaces): %s\n",
		   (priv->dma_cap.pcs) ? "Y" : "N");
	seq_म_लिखो(seq, "\tSMA (MDIO) Interface: %s\n",
		   (priv->dma_cap.sma_mdio) ? "Y" : "N");
	seq_म_लिखो(seq, "\tPMT Remote wake up: %s\n",
		   (priv->dma_cap.pmt_remote_wake_up) ? "Y" : "N");
	seq_म_लिखो(seq, "\tPMT Magic Frame: %s\n",
		   (priv->dma_cap.pmt_magic_frame) ? "Y" : "N");
	seq_म_लिखो(seq, "\tRMON module: %s\n",
		   (priv->dma_cap.rmon) ? "Y" : "N");
	seq_म_लिखो(seq, "\tIEEE 1588-2002 Time Stamp: %s\n",
		   (priv->dma_cap.समय_stamp) ? "Y" : "N");
	seq_म_लिखो(seq, "\tIEEE 1588-2008 Advanced Time Stamp: %s\n",
		   (priv->dma_cap.aसमय_stamp) ? "Y" : "N");
	seq_म_लिखो(seq, "\t802.3az - Energy-Efficient Ethernet (EEE): %s\n",
		   (priv->dma_cap.eee) ? "Y" : "N");
	seq_म_लिखो(seq, "\tAV features: %s\n", (priv->dma_cap.av) ? "Y" : "N");
	seq_म_लिखो(seq, "\tChecksum Offload in TX: %s\n",
		   (priv->dma_cap.tx_coe) ? "Y" : "N");
	अगर (priv->synopsys_id >= DWMAC_CORE_4_00) अणु
		seq_म_लिखो(seq, "\tIP Checksum Offload in RX: %s\n",
			   (priv->dma_cap.rx_coe) ? "Y" : "N");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(seq, "\tIP Checksum Offload (type1) in RX: %s\n",
			   (priv->dma_cap.rx_coe_type1) ? "Y" : "N");
		seq_म_लिखो(seq, "\tIP Checksum Offload (type2) in RX: %s\n",
			   (priv->dma_cap.rx_coe_type2) ? "Y" : "N");
	पूर्ण
	seq_म_लिखो(seq, "\tRXFIFO > 2048bytes: %s\n",
		   (priv->dma_cap.rxfअगरo_over_2048) ? "Y" : "N");
	seq_म_लिखो(seq, "\tNumber of Additional RX channel: %d\n",
		   priv->dma_cap.number_rx_channel);
	seq_म_लिखो(seq, "\tNumber of Additional TX channel: %d\n",
		   priv->dma_cap.number_tx_channel);
	seq_म_लिखो(seq, "\tNumber of Additional RX queues: %d\n",
		   priv->dma_cap.number_rx_queues);
	seq_म_लिखो(seq, "\tNumber of Additional TX queues: %d\n",
		   priv->dma_cap.number_tx_queues);
	seq_म_लिखो(seq, "\tEnhanced descriptors: %s\n",
		   (priv->dma_cap.enh_desc) ? "Y" : "N");
	seq_म_लिखो(seq, "\tTX Fifo Size: %d\n", priv->dma_cap.tx_fअगरo_size);
	seq_म_लिखो(seq, "\tRX Fifo Size: %d\n", priv->dma_cap.rx_fअगरo_size);
	seq_म_लिखो(seq, "\tHash Table Size: %d\n", priv->dma_cap.hash_tb_sz);
	seq_म_लिखो(seq, "\tTSO: %s\n", priv->dma_cap.tsoen ? "Y" : "N");
	seq_म_लिखो(seq, "\tNumber of PPS Outputs: %d\n",
		   priv->dma_cap.pps_out_num);
	seq_म_लिखो(seq, "\tSafety Features: %s\n",
		   priv->dma_cap.asp ? "Y" : "N");
	seq_म_लिखो(seq, "\tFlexible RX Parser: %s\n",
		   priv->dma_cap.frpsel ? "Y" : "N");
	seq_म_लिखो(seq, "\tEnhanced Addressing: %d\n",
		   priv->dma_cap.addr64);
	seq_म_लिखो(seq, "\tReceive Side Scaling: %s\n",
		   priv->dma_cap.rssen ? "Y" : "N");
	seq_म_लिखो(seq, "\tVLAN Hash Filtering: %s\n",
		   priv->dma_cap.vlhash ? "Y" : "N");
	seq_म_लिखो(seq, "\tSplit Header: %s\n",
		   priv->dma_cap.sphen ? "Y" : "N");
	seq_म_लिखो(seq, "\tVLAN TX Insertion: %s\n",
		   priv->dma_cap.vlins ? "Y" : "N");
	seq_म_लिखो(seq, "\tDouble VLAN: %s\n",
		   priv->dma_cap.dvlan ? "Y" : "N");
	seq_म_लिखो(seq, "\tNumber of L3/L4 Filters: %d\n",
		   priv->dma_cap.l3l4fnum);
	seq_म_लिखो(seq, "\tARP Offloading: %s\n",
		   priv->dma_cap.arpoffsel ? "Y" : "N");
	seq_म_लिखो(seq, "\tEnhancements to Scheduled Traffic (EST): %s\n",
		   priv->dma_cap.estsel ? "Y" : "N");
	seq_म_लिखो(seq, "\tFrame Preemption (FPE): %s\n",
		   priv->dma_cap.fpesel ? "Y" : "N");
	seq_म_लिखो(seq, "\tTime-Based Scheduling (TBS): %s\n",
		   priv->dma_cap.tbssel ? "Y" : "N");
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sपंचांगmac_dma_cap);

/* Use network device events to नाम debugfs file entries.
 */
अटल पूर्णांक sपंचांगmac_device_event(काष्ठा notअगरier_block *unused,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (dev->netdev_ops != &sपंचांगmac_netdev_ops)
		जाओ करोne;

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		अगर (priv->dbgfs_dir)
			priv->dbgfs_dir = debugfs_नाम(sपंचांगmac_fs_dir,
							 priv->dbgfs_dir,
							 sपंचांगmac_fs_dir,
							 dev->name);
		अवरोध;
	पूर्ण
करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sपंचांगmac_notअगरier = अणु
	.notअगरier_call = sपंचांगmac_device_event,
पूर्ण;

अटल व्योम sपंचांगmac_init_fs(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	rtnl_lock();

	/* Create per netdev entries */
	priv->dbgfs_dir = debugfs_create_dir(dev->name, sपंचांगmac_fs_dir);

	/* Entry to report DMA RX/TX rings */
	debugfs_create_file("descriptors_status", 0444, priv->dbgfs_dir, dev,
			    &sपंचांगmac_rings_status_fops);

	/* Entry to report the DMA HW features */
	debugfs_create_file("dma_cap", 0444, priv->dbgfs_dir, dev,
			    &sपंचांगmac_dma_cap_fops);

	rtnl_unlock();
पूर्ण

अटल व्योम sपंचांगmac_निकास_fs(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	debugfs_हटाओ_recursive(priv->dbgfs_dir);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल u32 sपंचांगmac_vid_crc32_le(__le16 vid_le)
अणु
	अचिन्हित अक्षर *data = (अचिन्हित अक्षर *)&vid_le;
	अचिन्हित अक्षर data_byte = 0;
	u32 crc = ~0x0;
	u32 temp = 0;
	पूर्णांक i, bits;

	bits = get_biपंचांगask_order(VLAN_VID_MASK);
	क्रम (i = 0; i < bits; i++) अणु
		अगर ((i % 8) == 0)
			data_byte = data[i / 8];

		temp = ((crc & 1) ^ data_byte) & 1;
		crc >>= 1;
		data_byte >>= 1;

		अगर (temp)
			crc ^= 0xedb88320;
	पूर्ण

	वापस crc;
पूर्ण

अटल पूर्णांक sपंचांगmac_vlan_update(काष्ठा sपंचांगmac_priv *priv, bool is_द्विगुन)
अणु
	u32 crc, hash = 0;
	__le16 pmatch = 0;
	पूर्णांक count = 0;
	u16 vid = 0;

	क्रम_each_set_bit(vid, priv->active_vlans, VLAN_N_VID) अणु
		__le16 vid_le = cpu_to_le16(vid);
		crc = bitrev32(~sपंचांगmac_vid_crc32_le(vid_le)) >> 28;
		hash |= (1 << crc);
		count++;
	पूर्ण

	अगर (!priv->dma_cap.vlhash) अणु
		अगर (count > 2) /* VID = 0 always passes filter */
			वापस -EOPNOTSUPP;

		pmatch = cpu_to_le16(vid);
		hash = 0;
	पूर्ण

	वापस sपंचांगmac_update_vlan_hash(priv, priv->hw, hash, pmatch, is_द्विगुन);
पूर्ण

अटल पूर्णांक sपंचांगmac_vlan_rx_add_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	bool is_द्विगुन = false;
	पूर्णांक ret;

	अगर (be16_to_cpu(proto) == ETH_P_8021AD)
		is_द्विगुन = true;

	set_bit(vid, priv->active_vlans);
	ret = sपंचांगmac_vlan_update(priv, is_द्विगुन);
	अगर (ret) अणु
		clear_bit(vid, priv->active_vlans);
		वापस ret;
	पूर्ण

	अगर (priv->hw->num_vlan) अणु
		ret = sपंचांगmac_add_hw_vlan_rx_fltr(priv, ndev, priv->hw, proto, vid);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_vlan_rx_समाप्त_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	bool is_द्विगुन = false;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->device);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->device);
		वापस ret;
	पूर्ण

	अगर (be16_to_cpu(proto) == ETH_P_8021AD)
		is_द्विगुन = true;

	clear_bit(vid, priv->active_vlans);

	अगर (priv->hw->num_vlan) अणु
		ret = sपंचांगmac_del_hw_vlan_rx_fltr(priv, ndev, priv->hw, proto, vid);
		अगर (ret)
			जाओ del_vlan_error;
	पूर्ण

	ret = sपंचांगmac_vlan_update(priv, is_द्विगुन);

del_vlan_error:
	pm_runसमय_put(priv->device);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	चयन (bpf->command) अणु
	हाल XDP_SETUP_PROG:
		वापस sपंचांगmac_xdp_set_prog(priv, bpf->prog, bpf->extack);
	हाल XDP_SETUP_XSK_POOL:
		वापस sपंचांगmac_xdp_setup_pool(priv, bpf->xsk.pool,
					     bpf->xsk.queue_id);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_xdp_xmit(काष्ठा net_device *dev, पूर्णांक num_frames,
			   काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा netdev_queue *nq;
	पूर्णांक i, nxmit = 0;
	पूर्णांक queue;

	अगर (unlikely(test_bit(STMMAC_DOWN, &priv->state)))
		वापस -ENETDOWN;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	queue = sपंचांगmac_xdp_get_tx_queue(priv, cpu);
	nq = netdev_get_tx_queue(priv->dev, queue);

	__netअगर_tx_lock(nq, cpu);
	/* Aव्योमs TX समय-out as we are sharing with slow path */
	nq->trans_start = jअगरfies;

	क्रम (i = 0; i < num_frames; i++) अणु
		पूर्णांक res;

		res = sपंचांगmac_xdp_xmit_xdpf(priv, queue, frames[i], true);
		अगर (res == STMMAC_XDP_CONSUMED)
			अवरोध;

		nxmit++;
	पूर्ण

	अगर (flags & XDP_XMIT_FLUSH) अणु
		sपंचांगmac_flush_tx_descriptors(priv, queue);
		sपंचांगmac_tx_समयr_arm(priv, queue);
	पूर्ण

	__netअगर_tx_unlock(nq);

	वापस nxmit;
पूर्ण

व्योम sपंचांगmac_disable_rx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ch->lock, flags);
	sपंचांगmac_disable_dma_irq(priv, priv->ioaddr, queue, 1, 0);
	spin_unlock_irqrestore(&ch->lock, flags);

	sपंचांगmac_stop_rx_dma(priv, queue);
	__मुक्त_dma_rx_desc_resources(priv, queue);
पूर्ण

व्योम sपंचांगmac_enable_rx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	अचिन्हित दीर्घ flags;
	u32 buf_size;
	पूर्णांक ret;

	ret = __alloc_dma_rx_desc_resources(priv, queue);
	अगर (ret) अणु
		netdev_err(priv->dev, "Failed to alloc RX desc.\n");
		वापस;
	पूर्ण

	ret = __init_dma_rx_desc_rings(priv, queue, GFP_KERNEL);
	अगर (ret) अणु
		__मुक्त_dma_rx_desc_resources(priv, queue);
		netdev_err(priv->dev, "Failed to init RX desc.\n");
		वापस;
	पूर्ण

	sपंचांगmac_clear_rx_descriptors(priv, queue);

	sपंचांगmac_init_rx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
			    rx_q->dma_rx_phy, rx_q->queue_index);

	rx_q->rx_tail_addr = rx_q->dma_rx_phy + (rx_q->buf_alloc_num *
			     माप(काष्ठा dma_desc));
	sपंचांगmac_set_rx_tail_ptr(priv, priv->ioaddr,
			       rx_q->rx_tail_addr, rx_q->queue_index);

	अगर (rx_q->xsk_pool && rx_q->buf_alloc_num) अणु
		buf_size = xsk_pool_get_rx_frame_size(rx_q->xsk_pool);
		sपंचांगmac_set_dma_bfsize(priv, priv->ioaddr,
				      buf_size,
				      rx_q->queue_index);
	पूर्ण अन्यथा अणु
		sपंचांगmac_set_dma_bfsize(priv, priv->ioaddr,
				      priv->dma_buf_sz,
				      rx_q->queue_index);
	पूर्ण

	sपंचांगmac_start_rx_dma(priv, queue);

	spin_lock_irqsave(&ch->lock, flags);
	sपंचांगmac_enable_dma_irq(priv, priv->ioaddr, queue, 1, 0);
	spin_unlock_irqrestore(&ch->lock, flags);
पूर्ण

व्योम sपंचांगmac_disable_tx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ch->lock, flags);
	sपंचांगmac_disable_dma_irq(priv, priv->ioaddr, queue, 0, 1);
	spin_unlock_irqrestore(&ch->lock, flags);

	sपंचांगmac_stop_tx_dma(priv, queue);
	__मुक्त_dma_tx_desc_resources(priv, queue);
पूर्ण

व्योम sपंचांगmac_enable_tx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = __alloc_dma_tx_desc_resources(priv, queue);
	अगर (ret) अणु
		netdev_err(priv->dev, "Failed to alloc TX desc.\n");
		वापस;
	पूर्ण

	ret = __init_dma_tx_desc_rings(priv, queue);
	अगर (ret) अणु
		__मुक्त_dma_tx_desc_resources(priv, queue);
		netdev_err(priv->dev, "Failed to init TX desc.\n");
		वापस;
	पूर्ण

	sपंचांगmac_clear_tx_descriptors(priv, queue);

	sपंचांगmac_init_tx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
			    tx_q->dma_tx_phy, tx_q->queue_index);

	अगर (tx_q->tbs & STMMAC_TBS_AVAIL)
		sपंचांगmac_enable_tbs(priv, priv->ioaddr, 1, tx_q->queue_index);

	tx_q->tx_tail_addr = tx_q->dma_tx_phy;
	sपंचांगmac_set_tx_tail_ptr(priv, priv->ioaddr,
			       tx_q->tx_tail_addr, tx_q->queue_index);

	sपंचांगmac_start_tx_dma(priv, queue);

	spin_lock_irqsave(&ch->lock, flags);
	sपंचांगmac_enable_dma_irq(priv, priv->ioaddr, queue, 0, 1);
	spin_unlock_irqrestore(&ch->lock, flags);
पूर्ण

पूर्णांक sपंचांगmac_xsk_wakeup(काष्ठा net_device *dev, u32 queue, u32 flags)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	काष्ठा sपंचांगmac_rx_queue *rx_q;
	काष्ठा sपंचांगmac_tx_queue *tx_q;
	काष्ठा sपंचांगmac_channel *ch;

	अगर (test_bit(STMMAC_DOWN, &priv->state) ||
	    !netअगर_carrier_ok(priv->dev))
		वापस -ENETDOWN;

	अगर (!sपंचांगmac_xdp_is_enabled(priv))
		वापस -ENXIO;

	अगर (queue >= priv->plat->rx_queues_to_use ||
	    queue >= priv->plat->tx_queues_to_use)
		वापस -EINVAL;

	rx_q = &priv->rx_queue[queue];
	tx_q = &priv->tx_queue[queue];
	ch = &priv->channel[queue];

	अगर (!rx_q->xsk_pool && !tx_q->xsk_pool)
		वापस -ENXIO;

	अगर (!napi_अगर_scheduled_mark_missed(&ch->rxtx_napi)) अणु
		/* EQoS करोes not have per-DMA channel SW पूर्णांकerrupt,
		 * so we schedule RX Napi straight-away.
		 */
		अगर (likely(napi_schedule_prep(&ch->rxtx_napi)))
			__napi_schedule(&ch->rxtx_napi);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sपंचांगmac_netdev_ops = अणु
	.nकरो_खोलो = sपंचांगmac_खोलो,
	.nकरो_start_xmit = sपंचांगmac_xmit,
	.nकरो_stop = sपंचांगmac_release,
	.nकरो_change_mtu = sपंचांगmac_change_mtu,
	.nकरो_fix_features = sपंचांगmac_fix_features,
	.nकरो_set_features = sपंचांगmac_set_features,
	.nकरो_set_rx_mode = sपंचांगmac_set_rx_mode,
	.nकरो_tx_समयout = sपंचांगmac_tx_समयout,
	.nकरो_करो_ioctl = sपंचांगmac_ioctl,
	.nकरो_setup_tc = sपंचांगmac_setup_tc,
	.nकरो_select_queue = sपंचांगmac_select_queue,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = sपंचांगmac_poll_controller,
#पूर्ण_अगर
	.nकरो_set_mac_address = sपंचांगmac_set_mac_address,
	.nकरो_vlan_rx_add_vid = sपंचांगmac_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = sपंचांगmac_vlan_rx_समाप्त_vid,
	.nकरो_bpf = sपंचांगmac_bpf,
	.nकरो_xdp_xmit = sपंचांगmac_xdp_xmit,
	.nकरो_xsk_wakeup = sपंचांगmac_xsk_wakeup,
पूर्ण;

अटल व्योम sपंचांगmac_reset_subtask(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!test_and_clear_bit(STMMAC_RESET_REQUESTED, &priv->state))
		वापस;
	अगर (test_bit(STMMAC_DOWN, &priv->state))
		वापस;

	netdev_err(priv->dev, "Reset adapter.\n");

	rtnl_lock();
	netअगर_trans_update(priv->dev);
	जबतक (test_and_set_bit(STMMAC_RESETING, &priv->state))
		usleep_range(1000, 2000);

	set_bit(STMMAC_DOWN, &priv->state);
	dev_बंद(priv->dev);
	dev_खोलो(priv->dev, शून्य);
	clear_bit(STMMAC_DOWN, &priv->state);
	clear_bit(STMMAC_RESETING, &priv->state);
	rtnl_unlock();
पूर्ण

अटल व्योम sपंचांगmac_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sपंचांगmac_priv *priv = container_of(work, काष्ठा sपंचांगmac_priv,
			service_task);

	sपंचांगmac_reset_subtask(priv);
	clear_bit(STMMAC_SERVICE_SCHED, &priv->state);
पूर्ण

/**
 *  sपंचांगmac_hw_init - Init the MAC device
 *  @priv: driver निजी काष्ठाure
 *  Description: this function is to configure the MAC device according to
 *  some platक्रमm parameters or the HW capability रेजिस्टर. It prepares the
 *  driver to use either ring or chain modes and to setup either enhanced or
 *  normal descriptors.
 */
अटल पूर्णांक sपंचांगmac_hw_init(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक ret;

	/* dwmac-sun8i only work in chain mode */
	अगर (priv->plat->has_sun8i)
		chain_mode = 1;
	priv->chain_mode = chain_mode;

	/* Initialize HW Interface */
	ret = sपंचांगmac_hwअगर_init(priv);
	अगर (ret)
		वापस ret;

	/* Get the HW capability (new GMAC newer than 3.50a) */
	priv->hw_cap_support = sपंचांगmac_get_hw_features(priv);
	अगर (priv->hw_cap_support) अणु
		dev_info(priv->device, "DMA HW capability register supported\n");

		/* We can override some gmac/dma configuration fields: e.g.
		 * enh_desc, tx_coe (e.g. that are passed through the
		 * platक्रमm) with the values from the HW capability
		 * रेजिस्टर (अगर supported).
		 */
		priv->plat->enh_desc = priv->dma_cap.enh_desc;
		priv->plat->pmt = priv->dma_cap.pmt_remote_wake_up;
		priv->hw->pmt = priv->plat->pmt;
		अगर (priv->dma_cap.hash_tb_sz) अणु
			priv->hw->multicast_filter_bins =
					(BIT(priv->dma_cap.hash_tb_sz) << 5);
			priv->hw->mcast_bits_log2 =
					ilog2(priv->hw->multicast_filter_bins);
		पूर्ण

		/* TXCOE करोesn't work in thresh DMA mode */
		अगर (priv->plat->क्रमce_thresh_dma_mode)
			priv->plat->tx_coe = 0;
		अन्यथा
			priv->plat->tx_coe = priv->dma_cap.tx_coe;

		/* In हाल of GMAC4 rx_coe is from HW cap रेजिस्टर. */
		priv->plat->rx_coe = priv->dma_cap.rx_coe;

		अगर (priv->dma_cap.rx_coe_type2)
			priv->plat->rx_coe = STMMAC_RX_COE_TYPE2;
		अन्यथा अगर (priv->dma_cap.rx_coe_type1)
			priv->plat->rx_coe = STMMAC_RX_COE_TYPE1;

	पूर्ण अन्यथा अणु
		dev_info(priv->device, "No HW DMA feature register supported\n");
	पूर्ण

	अगर (priv->plat->rx_coe) अणु
		priv->hw->rx_csum = priv->plat->rx_coe;
		dev_info(priv->device, "RX Checksum Offload Engine supported\n");
		अगर (priv->synopsys_id < DWMAC_CORE_4_00)
			dev_info(priv->device, "COE Type %d\n", priv->hw->rx_csum);
	पूर्ण
	अगर (priv->plat->tx_coe)
		dev_info(priv->device, "TX Checksum insertion supported\n");

	अगर (priv->plat->pmt) अणु
		dev_info(priv->device, "Wake-Up On Lan supported\n");
		device_set_wakeup_capable(priv->device, 1);
	पूर्ण

	अगर (priv->dma_cap.tsoen)
		dev_info(priv->device, "TSO supported\n");

	priv->hw->vlan_fail_q_en = priv->plat->vlan_fail_q_en;
	priv->hw->vlan_fail_q = priv->plat->vlan_fail_q;

	/* Run HW quirks, अगर any */
	अगर (priv->hwअगर_quirks) अणु
		ret = priv->hwअगर_quirks(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Rx Watchकरोg is available in the COREs newer than the 3.40.
	 * In some हाल, क्रम example on bugged HW this feature
	 * has to be disable and this can be करोne by passing the
	 * riwt_off field from the platक्रमm.
	 */
	अगर (((priv->synopsys_id >= DWMAC_CORE_3_50) ||
	    (priv->plat->has_xgmac)) && (!priv->plat->riwt_off)) अणु
		priv->use_riwt = 1;
		dev_info(priv->device,
			 "Enable RX Mitigation via HW Watchdog Timer\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांगmac_napi_add(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 queue, maxq;

	maxq = max(priv->plat->rx_queues_to_use, priv->plat->tx_queues_to_use);

	क्रम (queue = 0; queue < maxq; queue++) अणु
		काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];

		ch->priv_data = priv;
		ch->index = queue;
		spin_lock_init(&ch->lock);

		अगर (queue < priv->plat->rx_queues_to_use) अणु
			netअगर_napi_add(dev, &ch->rx_napi, sपंचांगmac_napi_poll_rx,
				       NAPI_POLL_WEIGHT);
		पूर्ण
		अगर (queue < priv->plat->tx_queues_to_use) अणु
			netअगर_tx_napi_add(dev, &ch->tx_napi,
					  sपंचांगmac_napi_poll_tx,
					  NAPI_POLL_WEIGHT);
		पूर्ण
		अगर (queue < priv->plat->rx_queues_to_use &&
		    queue < priv->plat->tx_queues_to_use) अणु
			netअगर_napi_add(dev, &ch->rxtx_napi,
				       sपंचांगmac_napi_poll_rxtx,
				       NAPI_POLL_WEIGHT);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_napi_del(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 queue, maxq;

	maxq = max(priv->plat->rx_queues_to_use, priv->plat->tx_queues_to_use);

	क्रम (queue = 0; queue < maxq; queue++) अणु
		काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];

		अगर (queue < priv->plat->rx_queues_to_use)
			netअगर_napi_del(&ch->rx_napi);
		अगर (queue < priv->plat->tx_queues_to_use)
			netअगर_napi_del(&ch->tx_napi);
		अगर (queue < priv->plat->rx_queues_to_use &&
		    queue < priv->plat->tx_queues_to_use) अणु
			netअगर_napi_del(&ch->rxtx_napi);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक sपंचांगmac_reinit_queues(काष्ठा net_device *dev, u32 rx_cnt, u32 tx_cnt)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (netअगर_running(dev))
		sपंचांगmac_release(dev);

	sपंचांगmac_napi_del(dev);

	priv->plat->rx_queues_to_use = rx_cnt;
	priv->plat->tx_queues_to_use = tx_cnt;

	sपंचांगmac_napi_add(dev);

	अगर (netअगर_running(dev))
		ret = sपंचांगmac_खोलो(dev);

	वापस ret;
पूर्ण

पूर्णांक sपंचांगmac_reinit_ringparam(काष्ठा net_device *dev, u32 rx_size, u32 tx_size)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (netअगर_running(dev))
		sपंचांगmac_release(dev);

	priv->dma_rx_size = rx_size;
	priv->dma_tx_size = tx_size;

	अगर (netअगर_running(dev))
		ret = sपंचांगmac_खोलो(dev);

	वापस ret;
पूर्ण

#घोषणा SEND_VERIFY_MPAKCET_FMT "Send Verify mPacket lo_state=%d lp_state=%d\n"
अटल व्योम sपंचांगmac_fpe_lp_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sपंचांगmac_priv *priv = container_of(work, काष्ठा sपंचांगmac_priv,
						fpe_task);
	काष्ठा sपंचांगmac_fpe_cfg *fpe_cfg = priv->plat->fpe_cfg;
	क्रमागत sपंचांगmac_fpe_state *lo_state = &fpe_cfg->lo_fpe_state;
	क्रमागत sपंचांगmac_fpe_state *lp_state = &fpe_cfg->lp_fpe_state;
	bool *hs_enable = &fpe_cfg->hs_enable;
	bool *enable = &fpe_cfg->enable;
	पूर्णांक retries = 20;

	जबतक (retries-- > 0) अणु
		/* Bail out immediately अगर FPE handshake is OFF */
		अगर (*lo_state == FPE_STATE_OFF || !*hs_enable)
			अवरोध;

		अगर (*lo_state == FPE_STATE_ENTERING_ON &&
		    *lp_state == FPE_STATE_ENTERING_ON) अणु
			sपंचांगmac_fpe_configure(priv, priv->ioaddr,
					     priv->plat->tx_queues_to_use,
					     priv->plat->rx_queues_to_use,
					     *enable);

			netdev_info(priv->dev, "configured FPE\n");

			*lo_state = FPE_STATE_ON;
			*lp_state = FPE_STATE_ON;
			netdev_info(priv->dev, "!!! BOTH FPE stations ON\n");
			अवरोध;
		पूर्ण

		अगर ((*lo_state == FPE_STATE_CAPABLE ||
		     *lo_state == FPE_STATE_ENTERING_ON) &&
		     *lp_state != FPE_STATE_ON) अणु
			netdev_info(priv->dev, SEND_VERIFY_MPAKCET_FMT,
				    *lo_state, *lp_state);
			sपंचांगmac_fpe_send_mpacket(priv, priv->ioaddr,
						MPACKET_VERIFY);
		पूर्ण
		/* Sleep then retry */
		msleep(500);
	पूर्ण

	clear_bit(__FPE_TASK_SCHED, &priv->fpe_task_state);
पूर्ण

व्योम sपंचांगmac_fpe_handshake(काष्ठा sपंचांगmac_priv *priv, bool enable)
अणु
	अगर (priv->plat->fpe_cfg->hs_enable != enable) अणु
		अगर (enable) अणु
			sपंचांगmac_fpe_send_mpacket(priv, priv->ioaddr,
						MPACKET_VERIFY);
		पूर्ण अन्यथा अणु
			priv->plat->fpe_cfg->lo_fpe_state = FPE_STATE_OFF;
			priv->plat->fpe_cfg->lp_fpe_state = FPE_STATE_OFF;
		पूर्ण

		priv->plat->fpe_cfg->hs_enable = enable;
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_dvr_probe
 * @device: device poपूर्णांकer
 * @plat_dat: platक्रमm data poपूर्णांकer
 * @res: sपंचांगmac resource poपूर्णांकer
 * Description: this is the मुख्य probe function used to
 * call the alloc_etherdev, allocate the priv काष्ठाure.
 * Return:
 * वापसs 0 on success, otherwise त्रुटि_सं.
 */
पूर्णांक sपंचांगmac_dvr_probe(काष्ठा device *device,
		     काष्ठा plat_sपंचांगmacenet_data *plat_dat,
		     काष्ठा sपंचांगmac_resources *res)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा sपंचांगmac_priv *priv;
	u32 rxq;
	पूर्णांक i, ret = 0;

	ndev = devm_alloc_etherdev_mqs(device, माप(काष्ठा sपंचांगmac_priv),
				       MTL_MAX_TX_QUEUES, MTL_MAX_RX_QUEUES);
	अगर (!ndev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(ndev, device);

	priv = netdev_priv(ndev);
	priv->device = device;
	priv->dev = ndev;

	sपंचांगmac_set_ethtool_ops(ndev);
	priv->छोड़ो = छोड़ो;
	priv->plat = plat_dat;
	priv->ioaddr = res->addr;
	priv->dev->base_addr = (अचिन्हित दीर्घ)res->addr;
	priv->plat->dma_cfg->multi_msi_en = priv->plat->multi_msi_en;

	priv->dev->irq = res->irq;
	priv->wol_irq = res->wol_irq;
	priv->lpi_irq = res->lpi_irq;
	priv->sfty_ce_irq = res->sfty_ce_irq;
	priv->sfty_ue_irq = res->sfty_ue_irq;
	क्रम (i = 0; i < MTL_MAX_RX_QUEUES; i++)
		priv->rx_irq[i] = res->rx_irq[i];
	क्रम (i = 0; i < MTL_MAX_TX_QUEUES; i++)
		priv->tx_irq[i] = res->tx_irq[i];

	अगर (!is_zero_ether_addr(res->mac))
		स_नकल(priv->dev->dev_addr, res->mac, ETH_ALEN);

	dev_set_drvdata(device, priv->dev);

	/* Verअगरy driver arguments */
	sपंचांगmac_verअगरy_args();

	priv->af_xdp_zc_qps = biपंचांगap_zalloc(MTL_MAX_TX_QUEUES, GFP_KERNEL);
	अगर (!priv->af_xdp_zc_qps)
		वापस -ENOMEM;

	/* Allocate workqueue */
	priv->wq = create_singlethपढ़ो_workqueue("stmmac_wq");
	अगर (!priv->wq) अणु
		dev_err(priv->device, "failed to create workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_WORK(&priv->service_task, sपंचांगmac_service_task);

	/* Initialize Link Partner FPE workqueue */
	INIT_WORK(&priv->fpe_task, sपंचांगmac_fpe_lp_task);

	/* Override with kernel parameters अगर supplied XXX CRS XXX
	 * this needs to have multiple instances
	 */
	अगर ((phyaddr >= 0) && (phyaddr <= 31))
		priv->plat->phy_addr = phyaddr;

	अगर (priv->plat->sपंचांगmac_rst) अणु
		ret = reset_control_निश्चित(priv->plat->sपंचांगmac_rst);
		reset_control_deनिश्चित(priv->plat->sपंचांगmac_rst);
		/* Some reset controllers have only reset callback instead of
		 * निश्चित + deनिश्चित callbacks pair.
		 */
		अगर (ret == -ENOTSUPP)
			reset_control_reset(priv->plat->sपंचांगmac_rst);
	पूर्ण

	/* Init MAC and get the capabilities */
	ret = sपंचांगmac_hw_init(priv);
	अगर (ret)
		जाओ error_hw_init;

	/* Only DWMAC core version 5.20 onwards supports HW descriptor prefetch.
	 */
	अगर (priv->synopsys_id < DWMAC_CORE_5_20)
		priv->plat->dma_cfg->dche = false;

	sपंचांगmac_check_ether_addr(priv);

	ndev->netdev_ops = &sपंचांगmac_netdev_ops;

	ndev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			    NETIF_F_RXCSUM;

	ret = sपंचांगmac_tc_init(priv, priv);
	अगर (!ret) अणु
		ndev->hw_features |= NETIF_F_HW_TC;
	पूर्ण

	अगर ((priv->plat->tso_en) && (priv->dma_cap.tsoen)) अणु
		ndev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;
		अगर (priv->plat->has_gmac4)
			ndev->hw_features |= NETIF_F_GSO_UDP_L4;
		priv->tso = true;
		dev_info(priv->device, "TSO feature enabled\n");
	पूर्ण

	अगर (priv->dma_cap.sphen) अणु
		ndev->hw_features |= NETIF_F_GRO;
		priv->sph_cap = true;
		priv->sph = priv->sph_cap;
		dev_info(priv->device, "SPH feature enabled\n");
	पूर्ण

	/* The current IP रेजिस्टर MAC_HW_Feature1[ADDR64] only define
	 * 32/40/64 bit width, but some SOC support others like i.MX8MP
	 * support 34 bits but it map to 40 bits width in MAC_HW_Feature1[ADDR64].
	 * So overग_लिखो dma_cap.addr64 according to HW real design.
	 */
	अगर (priv->plat->addr64)
		priv->dma_cap.addr64 = priv->plat->addr64;

	अगर (priv->dma_cap.addr64) अणु
		ret = dma_set_mask_and_coherent(device,
				DMA_BIT_MASK(priv->dma_cap.addr64));
		अगर (!ret) अणु
			dev_info(priv->device, "Using %d bits DMA width\n",
				 priv->dma_cap.addr64);

			/*
			 * If more than 32 bits can be addressed, make sure to
			 * enable enhanced addressing mode.
			 */
			अगर (IS_ENABLED(CONFIG_ARCH_DMA_ADDR_T_64BIT))
				priv->plat->dma_cfg->eame = true;
		पूर्ण अन्यथा अणु
			ret = dma_set_mask_and_coherent(device, DMA_BIT_MASK(32));
			अगर (ret) अणु
				dev_err(priv->device, "Failed to set DMA Mask\n");
				जाओ error_hw_init;
			पूर्ण

			priv->dma_cap.addr64 = 32;
		पूर्ण
	पूर्ण

	ndev->features |= ndev->hw_features | NETIF_F_HIGHDMA;
	ndev->watchकरोg_समयo = msecs_to_jअगरfies(watchकरोg);
#अगर_घोषित STMMAC_VLAN_TAG_USED
	/* Both mac100 and gmac support receive VLAN tag detection */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_STAG_RX;
	अगर (priv->dma_cap.vlhash) अणु
		ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
		ndev->features |= NETIF_F_HW_VLAN_STAG_FILTER;
	पूर्ण
	अगर (priv->dma_cap.vlins) अणु
		ndev->features |= NETIF_F_HW_VLAN_CTAG_TX;
		अगर (priv->dma_cap.dvlan)
			ndev->features |= NETIF_F_HW_VLAN_STAG_TX;
	पूर्ण
#पूर्ण_अगर
	priv->msg_enable = netअगर_msg_init(debug, शेष_msg_level);

	/* Initialize RSS */
	rxq = priv->plat->rx_queues_to_use;
	netdev_rss_key_fill(priv->rss.key, माप(priv->rss.key));
	क्रम (i = 0; i < ARRAY_SIZE(priv->rss.table); i++)
		priv->rss.table[i] = ethtool_rxfh_indir_शेष(i, rxq);

	अगर (priv->dma_cap.rssen && priv->plat->rss_en)
		ndev->features |= NETIF_F_RXHASH;

	/* MTU range: 46 - hw-specअगरic max */
	ndev->min_mtu = ETH_ZLEN - ETH_HLEN;
	अगर (priv->plat->has_xgmac)
		ndev->max_mtu = XGMAC_JUMBO_LEN;
	अन्यथा अगर ((priv->plat->enh_desc) || (priv->synopsys_id >= DWMAC_CORE_4_00))
		ndev->max_mtu = JUMBO_LEN;
	अन्यथा
		ndev->max_mtu = SKB_MAX_HEAD(NET_SKB_PAD + NET_IP_ALIGN);
	/* Will not overग_लिखो ndev->max_mtu अगर plat->maxmtu > ndev->max_mtu
	 * as well as plat->maxmtu < ndev->min_mtu which is a invalid range.
	 */
	अगर ((priv->plat->maxmtu < ndev->max_mtu) &&
	    (priv->plat->maxmtu >= ndev->min_mtu))
		ndev->max_mtu = priv->plat->maxmtu;
	अन्यथा अगर (priv->plat->maxmtu < ndev->min_mtu)
		dev_warn(priv->device,
			 "%s: warning: maxmtu having invalid value (%d)\n",
			 __func__, priv->plat->maxmtu);

	अगर (flow_ctrl)
		priv->flow_ctrl = FLOW_AUTO;	/* RX/TX छोड़ो on */

	/* Setup channels NAPI */
	sपंचांगmac_napi_add(ndev);

	mutex_init(&priv->lock);

	/* If a specअगरic clk_csr value is passed from the platक्रमm
	 * this means that the CSR Clock Range selection cannot be
	 * changed at run-समय and it is fixed. Viceversa the driver'll try to
	 * set the MDC घड़ी dynamically according to the csr actual
	 * घड़ी input.
	 */
	अगर (priv->plat->clk_csr >= 0)
		priv->clk_csr = priv->plat->clk_csr;
	अन्यथा
		sपंचांगmac_clk_csr_set(priv);

	sपंचांगmac_check_pcs_mode(priv);

	pm_runसमय_get_noresume(device);
	pm_runसमय_set_active(device);
	pm_runसमय_enable(device);

	अगर (priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI) अणु
		/* MDIO bus Registration */
		ret = sपंचांगmac_mdio_रेजिस्टर(ndev);
		अगर (ret < 0) अणु
			dev_err(priv->device,
				"%s: MDIO bus (id: %d) registration failed",
				__func__, priv->plat->bus_id);
			जाओ error_mdio_रेजिस्टर;
		पूर्ण
	पूर्ण

	ret = sपंचांगmac_phy_setup(priv);
	अगर (ret) अणु
		netdev_err(ndev, "failed to setup phy (%d)\n", ret);
		जाओ error_phy_setup;
	पूर्ण

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(priv->device, "%s: ERROR %i registering the device\n",
			__func__, ret);
		जाओ error_netdev_रेजिस्टर;
	पूर्ण

	अगर (priv->plat->serdes_घातerup) अणु
		ret = priv->plat->serdes_घातerup(ndev,
						 priv->plat->bsp_priv);

		अगर (ret < 0)
			जाओ error_serdes_घातerup;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	sपंचांगmac_init_fs(ndev);
#पूर्ण_अगर

	/* Let pm_runसमय_put() disable the घड़ीs.
	 * If CONFIG_PM is not enabled, the घड़ीs will stay घातered.
	 */
	pm_runसमय_put(device);

	वापस ret;

error_serdes_घातerup:
	unरेजिस्टर_netdev(ndev);
error_netdev_रेजिस्टर:
	phylink_destroy(priv->phylink);
error_phy_setup:
	अगर (priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI)
		sपंचांगmac_mdio_unरेजिस्टर(ndev);
error_mdio_रेजिस्टर:
	sपंचांगmac_napi_del(ndev);
error_hw_init:
	destroy_workqueue(priv->wq);
	biपंचांगap_मुक्त(priv->af_xdp_zc_qps);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_dvr_probe);

/**
 * sपंचांगmac_dvr_हटाओ
 * @dev: device poपूर्णांकer
 * Description: this function resets the TX/RX processes, disables the MAC RX/TX
 * changes the link status, releases the DMA descriptor rings.
 */
पूर्णांक sपंचांगmac_dvr_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	netdev_info(priv->dev, "%s: removing driver", __func__);

	sपंचांगmac_stop_all_dma(priv);
	sपंचांगmac_mac_set(priv, priv->ioaddr, false);
	netअगर_carrier_off(ndev);
	unरेजिस्टर_netdev(ndev);

	/* Serdes घातer करोwn needs to happen after VLAN filter
	 * is deleted that is triggered by unरेजिस्टर_netdev().
	 */
	अगर (priv->plat->serdes_घातerकरोwn)
		priv->plat->serdes_घातerकरोwn(ndev, priv->plat->bsp_priv);

#अगर_घोषित CONFIG_DEBUG_FS
	sपंचांगmac_निकास_fs(ndev);
#पूर्ण_अगर
	phylink_destroy(priv->phylink);
	अगर (priv->plat->sपंचांगmac_rst)
		reset_control_निश्चित(priv->plat->sपंचांगmac_rst);
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	अगर (priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI)
		sपंचांगmac_mdio_unरेजिस्टर(ndev);
	destroy_workqueue(priv->wq);
	mutex_destroy(&priv->lock);
	biपंचांगap_मुक्त(priv->af_xdp_zc_qps);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_dvr_हटाओ);

/**
 * sपंचांगmac_suspend - suspend callback
 * @dev: device poपूर्णांकer
 * Description: this is the function to suspend the device and it is called
 * by the platक्रमm driver to stop the network queue, release the resources,
 * program the PMT रेजिस्टर (क्रम WoL), clean and release driver resources.
 */
पूर्णांक sपंचांगmac_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	u32 chan;
	पूर्णांक ret;

	अगर (!ndev || !netअगर_running(ndev))
		वापस 0;

	phylink_mac_change(priv->phylink, false);

	mutex_lock(&priv->lock);

	netअगर_device_detach(ndev);

	sपंचांगmac_disable_all_queues(priv);

	क्रम (chan = 0; chan < priv->plat->tx_queues_to_use; chan++)
		hrसमयr_cancel(&priv->tx_queue[chan].txसमयr);

	अगर (priv->eee_enabled) अणु
		priv->tx_path_in_lpi_mode = false;
		del_समयr_sync(&priv->eee_ctrl_समयr);
	पूर्ण

	/* Stop TX/RX DMA */
	sपंचांगmac_stop_all_dma(priv);

	अगर (priv->plat->serdes_घातerकरोwn)
		priv->plat->serdes_घातerकरोwn(ndev, priv->plat->bsp_priv);

	/* Enable Power करोwn mode by programming the PMT regs */
	अगर (device_may_wakeup(priv->device) && priv->plat->pmt) अणु
		sपंचांगmac_pmt(priv, priv->hw, priv->wolopts);
		priv->irq_wake = 1;
	पूर्ण अन्यथा अणु
		mutex_unlock(&priv->lock);
		rtnl_lock();
		अगर (device_may_wakeup(priv->device))
			phylink_speed_करोwn(priv->phylink, false);
		phylink_stop(priv->phylink);
		rtnl_unlock();
		mutex_lock(&priv->lock);

		sपंचांगmac_mac_set(priv, priv->ioaddr, false);
		pinctrl_pm_select_sleep_state(priv->device);
		/* Disable घड़ी in हाल of PWM is off */
		clk_disable_unprepare(priv->plat->clk_ptp_ref);
		ret = pm_runसमय_क्रमce_suspend(dev);
		अगर (ret) अणु
			mutex_unlock(&priv->lock);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&priv->lock);

	अगर (priv->dma_cap.fpesel) अणु
		/* Disable FPE */
		sपंचांगmac_fpe_configure(priv, priv->ioaddr,
				     priv->plat->tx_queues_to_use,
				     priv->plat->rx_queues_to_use, false);

		sपंचांगmac_fpe_handshake(priv, false);
	पूर्ण

	priv->speed = SPEED_UNKNOWN;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_suspend);

/**
 * sपंचांगmac_reset_queues_param - reset queue parameters
 * @priv: device poपूर्णांकer
 */
अटल व्योम sपंचांगmac_reset_queues_param(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	क्रम (queue = 0; queue < rx_cnt; queue++) अणु
		काष्ठा sपंचांगmac_rx_queue *rx_q = &priv->rx_queue[queue];

		rx_q->cur_rx = 0;
		rx_q->dirty_rx = 0;
	पूर्ण

	क्रम (queue = 0; queue < tx_cnt; queue++) अणु
		काष्ठा sपंचांगmac_tx_queue *tx_q = &priv->tx_queue[queue];

		tx_q->cur_tx = 0;
		tx_q->dirty_tx = 0;
		tx_q->mss = 0;

		netdev_tx_reset_queue(netdev_get_tx_queue(priv->dev, queue));
	पूर्ण
पूर्ण

/**
 * sपंचांगmac_resume - resume callback
 * @dev: device poपूर्णांकer
 * Description: when resume this function is invoked to setup the DMA and CORE
 * in a usable state.
 */
पूर्णांक sपंचांगmac_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (!netअगर_running(ndev))
		वापस 0;

	/* Power Down bit, पूर्णांकo the PM रेजिस्टर, is cleared
	 * स्वतःmatically as soon as a magic packet or a Wake-up frame
	 * is received. Anyway, it's better to manually clear
	 * this bit because it can generate problems जबतक resuming
	 * from another devices (e.g. serial console).
	 */
	अगर (device_may_wakeup(priv->device) && priv->plat->pmt) अणु
		mutex_lock(&priv->lock);
		sपंचांगmac_pmt(priv, priv->hw, 0);
		mutex_unlock(&priv->lock);
		priv->irq_wake = 0;
	पूर्ण अन्यथा अणु
		pinctrl_pm_select_शेष_state(priv->device);
		/* enable the clk previously disabled */
		ret = pm_runसमय_क्रमce_resume(dev);
		अगर (ret)
			वापस ret;
		अगर (priv->plat->clk_ptp_ref)
			clk_prepare_enable(priv->plat->clk_ptp_ref);
		/* reset the phy so that it's पढ़ोy */
		अगर (priv->mii)
			sपंचांगmac_mdio_reset(priv->mii);
	पूर्ण

	अगर (priv->plat->serdes_घातerup) अणु
		ret = priv->plat->serdes_घातerup(ndev,
						 priv->plat->bsp_priv);

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!device_may_wakeup(priv->device) || !priv->plat->pmt) अणु
		rtnl_lock();
		phylink_start(priv->phylink);
		/* We may have called phylink_speed_करोwn beक्रमe */
		phylink_speed_up(priv->phylink);
		rtnl_unlock();
	पूर्ण

	rtnl_lock();
	mutex_lock(&priv->lock);

	sपंचांगmac_reset_queues_param(priv);

	sपंचांगmac_मुक्त_tx_skbufs(priv);
	sपंचांगmac_clear_descriptors(priv);

	sपंचांगmac_hw_setup(ndev, false);
	sपंचांगmac_init_coalesce(priv);
	sपंचांगmac_set_rx_mode(ndev);

	sपंचांगmac_restore_hw_vlan_rx_fltr(priv, ndev, priv->hw);

	sपंचांगmac_enable_all_queues(priv);

	mutex_unlock(&priv->lock);
	rtnl_unlock();

	phylink_mac_change(priv->phylink, true);

	netअगर_device_attach(ndev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_resume);

#अगर_अघोषित MODULE
अटल पूर्णांक __init sपंचांगmac_cmdline_opt(अक्षर *str)
अणु
	अक्षर *opt;

	अगर (!str || !*str)
		वापस -EINVAL;
	जबतक ((opt = strsep(&str, ",")) != शून्य) अणु
		अगर (!म_भेदन(opt, "debug:", 6)) अणु
			अगर (kstrtoपूर्णांक(opt + 6, 0, &debug))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "phyaddr:", 8)) अणु
			अगर (kstrtoपूर्णांक(opt + 8, 0, &phyaddr))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "buf_sz:", 7)) अणु
			अगर (kstrtoपूर्णांक(opt + 7, 0, &buf_sz))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "tc:", 3)) अणु
			अगर (kstrtoपूर्णांक(opt + 3, 0, &tc))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "watchdog:", 9)) अणु
			अगर (kstrtoपूर्णांक(opt + 9, 0, &watchकरोg))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "flow_ctrl:", 10)) अणु
			अगर (kstrtoपूर्णांक(opt + 10, 0, &flow_ctrl))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "pause:", 6)) अणु
			अगर (kstrtoपूर्णांक(opt + 6, 0, &छोड़ो))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "eee_timer:", 10)) अणु
			अगर (kstrtoपूर्णांक(opt + 10, 0, &eee_समयr))
				जाओ err;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "chain_mode:", 11)) अणु
			अगर (kstrtoपूर्णांक(opt + 11, 0, &chain_mode))
				जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;

err:
	pr_err("%s: ERROR broken module parameter conversion", __func__);
	वापस -EINVAL;
पूर्ण

__setup("stmmaceth=", sपंचांगmac_cmdline_opt);
#पूर्ण_अगर /* MODULE */

अटल पूर्णांक __init sपंचांगmac_init(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	/* Create debugfs मुख्य directory अगर it करोesn't exist yet */
	अगर (!sपंचांगmac_fs_dir)
		sपंचांगmac_fs_dir = debugfs_create_dir(STMMAC_RESOURCE_NAME, शून्य);
	रेजिस्टर_netdevice_notअगरier(&sपंचांगmac_notअगरier);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __निकास sपंचांगmac_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	unरेजिस्टर_netdevice_notअगरier(&sपंचांगmac_notअगरier);
	debugfs_हटाओ_recursive(sपंचांगmac_fs_dir);
#पूर्ण_अगर
पूर्ण

module_init(sपंचांगmac_init)
module_निकास(sपंचांगmac_निकास)

MODULE_DESCRIPTION("STMMAC 10/100/1000 Ethernet device driver");
MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_LICENSE("GPL");
