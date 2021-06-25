<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/cfg80211.h>

#समावेश "wil6210.h"

अटल पूर्णांक wil_ethtoolops_get_coalesce(काष्ठा net_device *ndev,
				       काष्ठा ethtool_coalesce *cp)
अणु
	काष्ठा wil6210_priv *wil = ndev_to_wil(ndev);
	u32 tx_itr_en, tx_itr_val = 0;
	u32 rx_itr_en, rx_itr_val = 0;
	पूर्णांक ret;

	mutex_lock(&wil->mutex);
	wil_dbg_misc(wil, "ethtoolops_get_coalesce\n");

	ret = wil_pm_runसमय_get(wil);
	अगर (ret < 0)
		जाओ out;

	tx_itr_en = wil_r(wil, RGF_DMA_ITR_TX_CNT_CTL);
	अगर (tx_itr_en & BIT_DMA_ITR_TX_CNT_CTL_EN)
		tx_itr_val = wil_r(wil, RGF_DMA_ITR_TX_CNT_TRSH);

	rx_itr_en = wil_r(wil, RGF_DMA_ITR_RX_CNT_CTL);
	अगर (rx_itr_en & BIT_DMA_ITR_RX_CNT_CTL_EN)
		rx_itr_val = wil_r(wil, RGF_DMA_ITR_RX_CNT_TRSH);

	wil_pm_runसमय_put(wil);

	cp->tx_coalesce_usecs = tx_itr_val;
	cp->rx_coalesce_usecs = rx_itr_val;
	ret = 0;

out:
	mutex_unlock(&wil->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wil_ethtoolops_set_coalesce(काष्ठा net_device *ndev,
				       काष्ठा ethtool_coalesce *cp)
अणु
	काष्ठा wil6210_priv *wil = ndev_to_wil(ndev);
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	पूर्णांक ret;

	mutex_lock(&wil->mutex);
	wil_dbg_misc(wil, "ethtoolops_set_coalesce: rx %d usec, tx %d usec\n",
		     cp->rx_coalesce_usecs, cp->tx_coalesce_usecs);

	अगर (wdev->अगरtype == NL80211_IFTYPE_MONITOR) अणु
		wil_dbg_misc(wil, "No IRQ coalescing in monitor mode\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* only @rx_coalesce_usecs and @tx_coalesce_usecs supported,
	 * ignore other parameters
	 */

	अगर (cp->rx_coalesce_usecs > WIL6210_ITR_TRSH_MAX ||
	    cp->tx_coalesce_usecs > WIL6210_ITR_TRSH_MAX)
		जाओ out_bad;

	wil->tx_max_burst_duration = cp->tx_coalesce_usecs;
	wil->rx_max_burst_duration = cp->rx_coalesce_usecs;

	ret = wil_pm_runसमय_get(wil);
	अगर (ret < 0)
		जाओ out;

	wil->txrx_ops.configure_पूर्णांकerrupt_moderation(wil);

	wil_pm_runसमय_put(wil);
	ret = 0;

out:
	mutex_unlock(&wil->mutex);
	वापस ret;

out_bad:
	wil_dbg_misc(wil, "Unsupported coalescing params. Raw command:\n");
	prपूर्णांक_hex_dump_debug("DBG[MISC] coal ", DUMP_PREFIX_OFFSET, 16, 4,
			     cp, माप(*cp), false);
	mutex_unlock(&wil->mutex);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops wil_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo	= cfg80211_get_drvinfo,
	.get_coalesce	= wil_ethtoolops_get_coalesce,
	.set_coalesce	= wil_ethtoolops_set_coalesce,
पूर्ण;

व्योम wil_set_ethtoolops(काष्ठा net_device *ndev)
अणु
	ndev->ethtool_ops = &wil_ethtool_ops;
पूर्ण
