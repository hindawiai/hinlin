<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2016-2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/linkmode.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <linux/firmware.h>
#समावेश <linux/utsname.h>
#समावेश <linux/समय.स>
#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_xdp.h"
#समावेश "bnxt_ethtool.h"
#समावेश "bnxt_nvm_defs.h"	/* NVRAM content स्थिरant and काष्ठाure defs */
#समावेश "bnxt_fw_hdr.h"	/* Firmware hdr स्थिरant and काष्ठाure defs */
#समावेश "bnxt_coredump.h"
#घोषणा FLASH_NVRAM_TIMEOUT	((HWRM_CMD_TIMEOUT) * 100)
#घोषणा FLASH_PACKAGE_TIMEOUT	((HWRM_CMD_TIMEOUT) * 200)
#घोषणा INSTALL_PACKAGE_TIMEOUT	((HWRM_CMD_TIMEOUT) * 200)

अटल u32 bnxt_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	वापस bp->msg_enable;
पूर्ण

अटल व्योम bnxt_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	bp->msg_enable = value;
पूर्ण

अटल पूर्णांक bnxt_get_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_coal *hw_coal;
	u16 mult;

	स_रखो(coal, 0, माप(*coal));

	coal->use_adaptive_rx_coalesce = bp->flags & BNXT_FLAG_DIM;

	hw_coal = &bp->rx_coal;
	mult = hw_coal->bufs_per_record;
	coal->rx_coalesce_usecs = hw_coal->coal_ticks;
	coal->rx_max_coalesced_frames = hw_coal->coal_bufs / mult;
	coal->rx_coalesce_usecs_irq = hw_coal->coal_ticks_irq;
	coal->rx_max_coalesced_frames_irq = hw_coal->coal_bufs_irq / mult;

	hw_coal = &bp->tx_coal;
	mult = hw_coal->bufs_per_record;
	coal->tx_coalesce_usecs = hw_coal->coal_ticks;
	coal->tx_max_coalesced_frames = hw_coal->coal_bufs / mult;
	coal->tx_coalesce_usecs_irq = hw_coal->coal_ticks_irq;
	coal->tx_max_coalesced_frames_irq = hw_coal->coal_bufs_irq / mult;

	coal->stats_block_coalesce_usecs = bp->stats_coal_ticks;

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_set_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	bool update_stats = false;
	काष्ठा bnxt_coal *hw_coal;
	पूर्णांक rc = 0;
	u16 mult;

	अगर (coal->use_adaptive_rx_coalesce) अणु
		bp->flags |= BNXT_FLAG_DIM;
	पूर्ण अन्यथा अणु
		अगर (bp->flags & BNXT_FLAG_DIM) अणु
			bp->flags &= ~(BNXT_FLAG_DIM);
			जाओ reset_coalesce;
		पूर्ण
	पूर्ण

	hw_coal = &bp->rx_coal;
	mult = hw_coal->bufs_per_record;
	hw_coal->coal_ticks = coal->rx_coalesce_usecs;
	hw_coal->coal_bufs = coal->rx_max_coalesced_frames * mult;
	hw_coal->coal_ticks_irq = coal->rx_coalesce_usecs_irq;
	hw_coal->coal_bufs_irq = coal->rx_max_coalesced_frames_irq * mult;

	hw_coal = &bp->tx_coal;
	mult = hw_coal->bufs_per_record;
	hw_coal->coal_ticks = coal->tx_coalesce_usecs;
	hw_coal->coal_bufs = coal->tx_max_coalesced_frames * mult;
	hw_coal->coal_ticks_irq = coal->tx_coalesce_usecs_irq;
	hw_coal->coal_bufs_irq = coal->tx_max_coalesced_frames_irq * mult;

	अगर (bp->stats_coal_ticks != coal->stats_block_coalesce_usecs) अणु
		u32 stats_ticks = coal->stats_block_coalesce_usecs;

		/* Allow 0, which means disable. */
		अगर (stats_ticks)
			stats_ticks = clamp_t(u32, stats_ticks,
					      BNXT_MIN_STATS_COAL_TICKS,
					      BNXT_MAX_STATS_COAL_TICKS);
		stats_ticks = roundकरोwn(stats_ticks, BNXT_MIN_STATS_COAL_TICKS);
		bp->stats_coal_ticks = stats_ticks;
		अगर (bp->stats_coal_ticks)
			bp->current_पूर्णांकerval =
				bp->stats_coal_ticks * HZ / 1000000;
		अन्यथा
			bp->current_पूर्णांकerval = BNXT_TIMER_INTERVAL;
		update_stats = true;
	पूर्ण

reset_coalesce:
	अगर (netअगर_running(dev)) अणु
		अगर (update_stats) अणु
			rc = bnxt_बंद_nic(bp, true, false);
			अगर (!rc)
				rc = bnxt_खोलो_nic(bp, true, false);
		पूर्ण अन्यथा अणु
			rc = bnxt_hwrm_set_coal(bp);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर अक्षर * स्थिर bnxt_ring_rx_stats_str[] = अणु
	"rx_ucast_packets",
	"rx_mcast_packets",
	"rx_bcast_packets",
	"rx_discards",
	"rx_errors",
	"rx_ucast_bytes",
	"rx_mcast_bytes",
	"rx_bcast_bytes",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bnxt_ring_tx_stats_str[] = अणु
	"tx_ucast_packets",
	"tx_mcast_packets",
	"tx_bcast_packets",
	"tx_errors",
	"tx_discards",
	"tx_ucast_bytes",
	"tx_mcast_bytes",
	"tx_bcast_bytes",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bnxt_ring_tpa_stats_str[] = अणु
	"tpa_packets",
	"tpa_bytes",
	"tpa_events",
	"tpa_aborts",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bnxt_ring_tpa2_stats_str[] = अणु
	"rx_tpa_eligible_pkt",
	"rx_tpa_eligible_bytes",
	"rx_tpa_pkt",
	"rx_tpa_bytes",
	"rx_tpa_errors",
	"rx_tpa_events",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bnxt_rx_sw_stats_str[] = अणु
	"rx_l4_csum_errors",
	"rx_resets",
	"rx_buf_errors",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bnxt_cmn_sw_stats_str[] = अणु
	"missed_irqs",
पूर्ण;

#घोषणा BNXT_RX_STATS_ENTRY(counter)	\
	अणु BNXT_RX_STATS_OFFSET(counter), __stringअगरy(counter) पूर्ण

#घोषणा BNXT_TX_STATS_ENTRY(counter)	\
	अणु BNXT_TX_STATS_OFFSET(counter), __stringअगरy(counter) पूर्ण

#घोषणा BNXT_RX_STATS_EXT_ENTRY(counter)	\
	अणु BNXT_RX_STATS_EXT_OFFSET(counter), __stringअगरy(counter) पूर्ण

#घोषणा BNXT_TX_STATS_EXT_ENTRY(counter)	\
	अणु BNXT_TX_STATS_EXT_OFFSET(counter), __stringअगरy(counter) पूर्ण

#घोषणा BNXT_RX_STATS_EXT_PFC_ENTRY(n)				\
	BNXT_RX_STATS_EXT_ENTRY(pfc_pri##n##_rx_duration_us),	\
	BNXT_RX_STATS_EXT_ENTRY(pfc_pri##n##_rx_transitions)

#घोषणा BNXT_TX_STATS_EXT_PFC_ENTRY(n)				\
	BNXT_TX_STATS_EXT_ENTRY(pfc_pri##n##_tx_duration_us),	\
	BNXT_TX_STATS_EXT_ENTRY(pfc_pri##n##_tx_transitions)

#घोषणा BNXT_RX_STATS_EXT_PFC_ENTRIES				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(0),				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(1),				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(2),				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(3),				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(4),				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(5),				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(6),				\
	BNXT_RX_STATS_EXT_PFC_ENTRY(7)

#घोषणा BNXT_TX_STATS_EXT_PFC_ENTRIES				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(0),				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(1),				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(2),				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(3),				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(4),				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(5),				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(6),				\
	BNXT_TX_STATS_EXT_PFC_ENTRY(7)

#घोषणा BNXT_RX_STATS_EXT_COS_ENTRY(n)				\
	BNXT_RX_STATS_EXT_ENTRY(rx_bytes_cos##n),		\
	BNXT_RX_STATS_EXT_ENTRY(rx_packets_cos##n)

#घोषणा BNXT_TX_STATS_EXT_COS_ENTRY(n)				\
	BNXT_TX_STATS_EXT_ENTRY(tx_bytes_cos##n),		\
	BNXT_TX_STATS_EXT_ENTRY(tx_packets_cos##n)

#घोषणा BNXT_RX_STATS_EXT_COS_ENTRIES				\
	BNXT_RX_STATS_EXT_COS_ENTRY(0),				\
	BNXT_RX_STATS_EXT_COS_ENTRY(1),				\
	BNXT_RX_STATS_EXT_COS_ENTRY(2),				\
	BNXT_RX_STATS_EXT_COS_ENTRY(3),				\
	BNXT_RX_STATS_EXT_COS_ENTRY(4),				\
	BNXT_RX_STATS_EXT_COS_ENTRY(5),				\
	BNXT_RX_STATS_EXT_COS_ENTRY(6),				\
	BNXT_RX_STATS_EXT_COS_ENTRY(7)				\

#घोषणा BNXT_TX_STATS_EXT_COS_ENTRIES				\
	BNXT_TX_STATS_EXT_COS_ENTRY(0),				\
	BNXT_TX_STATS_EXT_COS_ENTRY(1),				\
	BNXT_TX_STATS_EXT_COS_ENTRY(2),				\
	BNXT_TX_STATS_EXT_COS_ENTRY(3),				\
	BNXT_TX_STATS_EXT_COS_ENTRY(4),				\
	BNXT_TX_STATS_EXT_COS_ENTRY(5),				\
	BNXT_TX_STATS_EXT_COS_ENTRY(6),				\
	BNXT_TX_STATS_EXT_COS_ENTRY(7)				\

#घोषणा BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(n)			\
	BNXT_RX_STATS_EXT_ENTRY(rx_discard_bytes_cos##n),	\
	BNXT_RX_STATS_EXT_ENTRY(rx_discard_packets_cos##n)

#घोषणा BNXT_RX_STATS_EXT_DISCARD_COS_ENTRIES				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(0),				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(1),				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(2),				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(3),				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(4),				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(5),				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(6),				\
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRY(7)

#घोषणा BNXT_RX_STATS_PRI_ENTRY(counter, n)		\
	अणु BNXT_RX_STATS_EXT_OFFSET(counter##_cos0),	\
	  __stringअगरy(counter##_pri##n) पूर्ण

#घोषणा BNXT_TX_STATS_PRI_ENTRY(counter, n)		\
	अणु BNXT_TX_STATS_EXT_OFFSET(counter##_cos0),	\
	  __stringअगरy(counter##_pri##n) पूर्ण

#घोषणा BNXT_RX_STATS_PRI_ENTRIES(counter)		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 0),		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 1),		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 2),		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 3),		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 4),		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 5),		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 6),		\
	BNXT_RX_STATS_PRI_ENTRY(counter, 7)

#घोषणा BNXT_TX_STATS_PRI_ENTRIES(counter)		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 0),		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 1),		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 2),		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 3),		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 4),		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 5),		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 6),		\
	BNXT_TX_STATS_PRI_ENTRY(counter, 7)

क्रमागत अणु
	RX_TOTAL_DISCARDS,
	TX_TOTAL_DISCARDS,
पूर्ण;

अटल काष्ठा अणु
	u64			counter;
	अक्षर			string[ETH_GSTRING_LEN];
पूर्ण bnxt_sw_func_stats[] = अणु
	अणु0, "rx_total_discard_pkts"पूर्ण,
	अणु0, "tx_total_discard_pkts"पूर्ण,
पूर्ण;

#घोषणा NUM_RING_RX_SW_STATS		ARRAY_SIZE(bnxt_rx_sw_stats_str)
#घोषणा NUM_RING_CMN_SW_STATS		ARRAY_SIZE(bnxt_cmn_sw_stats_str)
#घोषणा NUM_RING_RX_HW_STATS		ARRAY_SIZE(bnxt_ring_rx_stats_str)
#घोषणा NUM_RING_TX_HW_STATS		ARRAY_SIZE(bnxt_ring_tx_stats_str)

अटल स्थिर काष्ठा अणु
	दीर्घ offset;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnxt_port_stats_arr[] = अणु
	BNXT_RX_STATS_ENTRY(rx_64b_frames),
	BNXT_RX_STATS_ENTRY(rx_65b_127b_frames),
	BNXT_RX_STATS_ENTRY(rx_128b_255b_frames),
	BNXT_RX_STATS_ENTRY(rx_256b_511b_frames),
	BNXT_RX_STATS_ENTRY(rx_512b_1023b_frames),
	BNXT_RX_STATS_ENTRY(rx_1024b_1518b_frames),
	BNXT_RX_STATS_ENTRY(rx_good_vlan_frames),
	BNXT_RX_STATS_ENTRY(rx_1519b_2047b_frames),
	BNXT_RX_STATS_ENTRY(rx_2048b_4095b_frames),
	BNXT_RX_STATS_ENTRY(rx_4096b_9216b_frames),
	BNXT_RX_STATS_ENTRY(rx_9217b_16383b_frames),
	BNXT_RX_STATS_ENTRY(rx_total_frames),
	BNXT_RX_STATS_ENTRY(rx_ucast_frames),
	BNXT_RX_STATS_ENTRY(rx_mcast_frames),
	BNXT_RX_STATS_ENTRY(rx_bcast_frames),
	BNXT_RX_STATS_ENTRY(rx_fcs_err_frames),
	BNXT_RX_STATS_ENTRY(rx_ctrl_frames),
	BNXT_RX_STATS_ENTRY(rx_छोड़ो_frames),
	BNXT_RX_STATS_ENTRY(rx_pfc_frames),
	BNXT_RX_STATS_ENTRY(rx_align_err_frames),
	BNXT_RX_STATS_ENTRY(rx_ovrsz_frames),
	BNXT_RX_STATS_ENTRY(rx_jbr_frames),
	BNXT_RX_STATS_ENTRY(rx_mtu_err_frames),
	BNXT_RX_STATS_ENTRY(rx_tagged_frames),
	BNXT_RX_STATS_ENTRY(rx_द्विगुन_tagged_frames),
	BNXT_RX_STATS_ENTRY(rx_good_frames),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri0),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri1),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri2),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri3),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri4),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri5),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri6),
	BNXT_RX_STATS_ENTRY(rx_pfc_ena_frames_pri7),
	BNXT_RX_STATS_ENTRY(rx_undrsz_frames),
	BNXT_RX_STATS_ENTRY(rx_eee_lpi_events),
	BNXT_RX_STATS_ENTRY(rx_eee_lpi_duration),
	BNXT_RX_STATS_ENTRY(rx_bytes),
	BNXT_RX_STATS_ENTRY(rx_runt_bytes),
	BNXT_RX_STATS_ENTRY(rx_runt_frames),
	BNXT_RX_STATS_ENTRY(rx_stat_discard),
	BNXT_RX_STATS_ENTRY(rx_stat_err),

	BNXT_TX_STATS_ENTRY(tx_64b_frames),
	BNXT_TX_STATS_ENTRY(tx_65b_127b_frames),
	BNXT_TX_STATS_ENTRY(tx_128b_255b_frames),
	BNXT_TX_STATS_ENTRY(tx_256b_511b_frames),
	BNXT_TX_STATS_ENTRY(tx_512b_1023b_frames),
	BNXT_TX_STATS_ENTRY(tx_1024b_1518b_frames),
	BNXT_TX_STATS_ENTRY(tx_good_vlan_frames),
	BNXT_TX_STATS_ENTRY(tx_1519b_2047b_frames),
	BNXT_TX_STATS_ENTRY(tx_2048b_4095b_frames),
	BNXT_TX_STATS_ENTRY(tx_4096b_9216b_frames),
	BNXT_TX_STATS_ENTRY(tx_9217b_16383b_frames),
	BNXT_TX_STATS_ENTRY(tx_good_frames),
	BNXT_TX_STATS_ENTRY(tx_total_frames),
	BNXT_TX_STATS_ENTRY(tx_ucast_frames),
	BNXT_TX_STATS_ENTRY(tx_mcast_frames),
	BNXT_TX_STATS_ENTRY(tx_bcast_frames),
	BNXT_TX_STATS_ENTRY(tx_छोड़ो_frames),
	BNXT_TX_STATS_ENTRY(tx_pfc_frames),
	BNXT_TX_STATS_ENTRY(tx_jabber_frames),
	BNXT_TX_STATS_ENTRY(tx_fcs_err_frames),
	BNXT_TX_STATS_ENTRY(tx_err),
	BNXT_TX_STATS_ENTRY(tx_fअगरo_underruns),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri0),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri1),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri2),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri3),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri4),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri5),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri6),
	BNXT_TX_STATS_ENTRY(tx_pfc_ena_frames_pri7),
	BNXT_TX_STATS_ENTRY(tx_eee_lpi_events),
	BNXT_TX_STATS_ENTRY(tx_eee_lpi_duration),
	BNXT_TX_STATS_ENTRY(tx_total_collisions),
	BNXT_TX_STATS_ENTRY(tx_bytes),
	BNXT_TX_STATS_ENTRY(tx_xthol_frames),
	BNXT_TX_STATS_ENTRY(tx_stat_discard),
	BNXT_TX_STATS_ENTRY(tx_stat_error),
पूर्ण;

अटल स्थिर काष्ठा अणु
	दीर्घ offset;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnxt_port_stats_ext_arr[] = अणु
	BNXT_RX_STATS_EXT_ENTRY(link_करोwn_events),
	BNXT_RX_STATS_EXT_ENTRY(continuous_छोड़ो_events),
	BNXT_RX_STATS_EXT_ENTRY(resume_छोड़ो_events),
	BNXT_RX_STATS_EXT_ENTRY(continuous_roce_छोड़ो_events),
	BNXT_RX_STATS_EXT_ENTRY(resume_roce_छोड़ो_events),
	BNXT_RX_STATS_EXT_COS_ENTRIES,
	BNXT_RX_STATS_EXT_PFC_ENTRIES,
	BNXT_RX_STATS_EXT_ENTRY(rx_bits),
	BNXT_RX_STATS_EXT_ENTRY(rx_buffer_passed_threshold),
	BNXT_RX_STATS_EXT_ENTRY(rx_pcs_symbol_err),
	BNXT_RX_STATS_EXT_ENTRY(rx_corrected_bits),
	BNXT_RX_STATS_EXT_DISCARD_COS_ENTRIES,
पूर्ण;

अटल स्थिर काष्ठा अणु
	दीर्घ offset;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnxt_tx_port_stats_ext_arr[] = अणु
	BNXT_TX_STATS_EXT_COS_ENTRIES,
	BNXT_TX_STATS_EXT_PFC_ENTRIES,
पूर्ण;

अटल स्थिर काष्ठा अणु
	दीर्घ base_off;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnxt_rx_bytes_pri_arr[] = अणु
	BNXT_RX_STATS_PRI_ENTRIES(rx_bytes),
पूर्ण;

अटल स्थिर काष्ठा अणु
	दीर्घ base_off;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnxt_rx_pkts_pri_arr[] = अणु
	BNXT_RX_STATS_PRI_ENTRIES(rx_packets),
पूर्ण;

अटल स्थिर काष्ठा अणु
	दीर्घ base_off;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnxt_tx_bytes_pri_arr[] = अणु
	BNXT_TX_STATS_PRI_ENTRIES(tx_bytes),
पूर्ण;

अटल स्थिर काष्ठा अणु
	दीर्घ base_off;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnxt_tx_pkts_pri_arr[] = अणु
	BNXT_TX_STATS_PRI_ENTRIES(tx_packets),
पूर्ण;

#घोषणा BNXT_NUM_SW_FUNC_STATS	ARRAY_SIZE(bnxt_sw_func_stats)
#घोषणा BNXT_NUM_PORT_STATS ARRAY_SIZE(bnxt_port_stats_arr)
#घोषणा BNXT_NUM_STATS_PRI			\
	(ARRAY_SIZE(bnxt_rx_bytes_pri_arr) +	\
	 ARRAY_SIZE(bnxt_rx_pkts_pri_arr) +	\
	 ARRAY_SIZE(bnxt_tx_bytes_pri_arr) +	\
	 ARRAY_SIZE(bnxt_tx_pkts_pri_arr))

अटल पूर्णांक bnxt_get_num_tpa_ring_stats(काष्ठा bnxt *bp)
अणु
	अगर (BNXT_SUPPORTS_TPA(bp)) अणु
		अगर (bp->max_tpa_v2) अणु
			अगर (BNXT_CHIP_P5_THOR(bp))
				वापस BNXT_NUM_TPA_RING_STATS_P5;
			वापस BNXT_NUM_TPA_RING_STATS_P5_SR2;
		पूर्ण
		वापस BNXT_NUM_TPA_RING_STATS;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_get_num_ring_stats(काष्ठा bnxt *bp)
अणु
	पूर्णांक rx, tx, cmn;

	rx = NUM_RING_RX_HW_STATS + NUM_RING_RX_SW_STATS +
	     bnxt_get_num_tpa_ring_stats(bp);
	tx = NUM_RING_TX_HW_STATS;
	cmn = NUM_RING_CMN_SW_STATS;
	वापस rx * bp->rx_nr_rings + tx * bp->tx_nr_rings +
	       cmn * bp->cp_nr_rings;
पूर्ण

अटल पूर्णांक bnxt_get_num_stats(काष्ठा bnxt *bp)
अणु
	पूर्णांक num_stats = bnxt_get_num_ring_stats(bp);

	num_stats += BNXT_NUM_SW_FUNC_STATS;

	अगर (bp->flags & BNXT_FLAG_PORT_STATS)
		num_stats += BNXT_NUM_PORT_STATS;

	अगर (bp->flags & BNXT_FLAG_PORT_STATS_EXT) अणु
		num_stats += bp->fw_rx_stats_ext_size +
			     bp->fw_tx_stats_ext_size;
		अगर (bp->pri2cos_valid)
			num_stats += BNXT_NUM_STATS_PRI;
	पूर्ण

	वापस num_stats;
पूर्ण

अटल पूर्णांक bnxt_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस bnxt_get_num_stats(bp);
	हाल ETH_SS_TEST:
		अगर (!bp->num_tests)
			वापस -EOPNOTSUPP;
		वापस bp->num_tests;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल bool is_rx_ring(काष्ठा bnxt *bp, पूर्णांक ring_num)
अणु
	वापस ring_num < bp->rx_nr_rings;
पूर्ण

अटल bool is_tx_ring(काष्ठा bnxt *bp, पूर्णांक ring_num)
अणु
	पूर्णांक tx_base = 0;

	अगर (!(bp->flags & BNXT_FLAG_SHARED_RINGS))
		tx_base = bp->rx_nr_rings;

	अगर (ring_num >= tx_base && ring_num < (tx_base + bp->tx_nr_rings))
		वापस true;
	वापस false;
पूर्ण

अटल व्योम bnxt_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *stats, u64 *buf)
अणु
	u32 i, j = 0;
	काष्ठा bnxt *bp = netdev_priv(dev);
	u32 tpa_stats;

	अगर (!bp->bnapi) अणु
		j += bnxt_get_num_ring_stats(bp) + BNXT_NUM_SW_FUNC_STATS;
		जाओ skip_ring_stats;
	पूर्ण

	क्रम (i = 0; i < BNXT_NUM_SW_FUNC_STATS; i++)
		bnxt_sw_func_stats[i].counter = 0;

	tpa_stats = bnxt_get_num_tpa_ring_stats(bp);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		u64 *sw_stats = cpr->stats.sw_stats;
		u64 *sw;
		पूर्णांक k;

		अगर (is_rx_ring(bp, i)) अणु
			क्रम (k = 0; k < NUM_RING_RX_HW_STATS; j++, k++)
				buf[j] = sw_stats[k];
		पूर्ण
		अगर (is_tx_ring(bp, i)) अणु
			k = NUM_RING_RX_HW_STATS;
			क्रम (; k < NUM_RING_RX_HW_STATS + NUM_RING_TX_HW_STATS;
			       j++, k++)
				buf[j] = sw_stats[k];
		पूर्ण
		अगर (!tpa_stats || !is_rx_ring(bp, i))
			जाओ skip_tpa_ring_stats;

		k = NUM_RING_RX_HW_STATS + NUM_RING_TX_HW_STATS;
		क्रम (; k < NUM_RING_RX_HW_STATS + NUM_RING_TX_HW_STATS +
			   tpa_stats; j++, k++)
			buf[j] = sw_stats[k];

skip_tpa_ring_stats:
		sw = (u64 *)&cpr->sw_stats.rx;
		अगर (is_rx_ring(bp, i)) अणु
			क्रम (k = 0; k < NUM_RING_RX_SW_STATS; j++, k++)
				buf[j] = sw[k];
		पूर्ण

		sw = (u64 *)&cpr->sw_stats.cmn;
		क्रम (k = 0; k < NUM_RING_CMN_SW_STATS; j++, k++)
			buf[j] = sw[k];

		bnxt_sw_func_stats[RX_TOTAL_DISCARDS].counter +=
			BNXT_GET_RING_STATS64(sw_stats, rx_discard_pkts);
		bnxt_sw_func_stats[TX_TOTAL_DISCARDS].counter +=
			BNXT_GET_RING_STATS64(sw_stats, tx_discard_pkts);
	पूर्ण

	क्रम (i = 0; i < BNXT_NUM_SW_FUNC_STATS; i++, j++)
		buf[j] = bnxt_sw_func_stats[i].counter;

skip_ring_stats:
	अगर (bp->flags & BNXT_FLAG_PORT_STATS) अणु
		u64 *port_stats = bp->port_stats.sw_stats;

		क्रम (i = 0; i < BNXT_NUM_PORT_STATS; i++, j++)
			buf[j] = *(port_stats + bnxt_port_stats_arr[i].offset);
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_PORT_STATS_EXT) अणु
		u64 *rx_port_stats_ext = bp->rx_port_stats_ext.sw_stats;
		u64 *tx_port_stats_ext = bp->tx_port_stats_ext.sw_stats;

		क्रम (i = 0; i < bp->fw_rx_stats_ext_size; i++, j++) अणु
			buf[j] = *(rx_port_stats_ext +
				   bnxt_port_stats_ext_arr[i].offset);
		पूर्ण
		क्रम (i = 0; i < bp->fw_tx_stats_ext_size; i++, j++) अणु
			buf[j] = *(tx_port_stats_ext +
				   bnxt_tx_port_stats_ext_arr[i].offset);
		पूर्ण
		अगर (bp->pri2cos_valid) अणु
			क्रम (i = 0; i < 8; i++, j++) अणु
				दीर्घ n = bnxt_rx_bytes_pri_arr[i].base_off +
					 bp->pri2cos_idx[i];

				buf[j] = *(rx_port_stats_ext + n);
			पूर्ण
			क्रम (i = 0; i < 8; i++, j++) अणु
				दीर्घ n = bnxt_rx_pkts_pri_arr[i].base_off +
					 bp->pri2cos_idx[i];

				buf[j] = *(rx_port_stats_ext + n);
			पूर्ण
			क्रम (i = 0; i < 8; i++, j++) अणु
				दीर्घ n = bnxt_tx_bytes_pri_arr[i].base_off +
					 bp->pri2cos_idx[i];

				buf[j] = *(tx_port_stats_ext + n);
			पूर्ण
			क्रम (i = 0; i < 8; i++, j++) अणु
				दीर्घ n = bnxt_tx_pkts_pri_arr[i].base_off +
					 bp->pri2cos_idx[i];

				buf[j] = *(tx_port_stats_ext + n);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	अटल स्थिर अक्षर * स्थिर *str;
	u32 i, j, num_str;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
			अगर (is_rx_ring(bp, i)) अणु
				num_str = NUM_RING_RX_HW_STATS;
				क्रम (j = 0; j < num_str; j++) अणु
					प्र_लिखो(buf, "[%d]: %s", i,
						bnxt_ring_rx_stats_str[j]);
					buf += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
			अगर (is_tx_ring(bp, i)) अणु
				num_str = NUM_RING_TX_HW_STATS;
				क्रम (j = 0; j < num_str; j++) अणु
					प्र_लिखो(buf, "[%d]: %s", i,
						bnxt_ring_tx_stats_str[j]);
					buf += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
			num_str = bnxt_get_num_tpa_ring_stats(bp);
			अगर (!num_str || !is_rx_ring(bp, i))
				जाओ skip_tpa_stats;

			अगर (bp->max_tpa_v2)
				str = bnxt_ring_tpa2_stats_str;
			अन्यथा
				str = bnxt_ring_tpa_stats_str;

			क्रम (j = 0; j < num_str; j++) अणु
				प्र_लिखो(buf, "[%d]: %s", i, str[j]);
				buf += ETH_GSTRING_LEN;
			पूर्ण
skip_tpa_stats:
			अगर (is_rx_ring(bp, i)) अणु
				num_str = NUM_RING_RX_SW_STATS;
				क्रम (j = 0; j < num_str; j++) अणु
					प्र_लिखो(buf, "[%d]: %s", i,
						bnxt_rx_sw_stats_str[j]);
					buf += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
			num_str = NUM_RING_CMN_SW_STATS;
			क्रम (j = 0; j < num_str; j++) अणु
				प्र_लिखो(buf, "[%d]: %s", i,
					bnxt_cmn_sw_stats_str[j]);
				buf += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < BNXT_NUM_SW_FUNC_STATS; i++) अणु
			म_नकल(buf, bnxt_sw_func_stats[i].string);
			buf += ETH_GSTRING_LEN;
		पूर्ण

		अगर (bp->flags & BNXT_FLAG_PORT_STATS) अणु
			क्रम (i = 0; i < BNXT_NUM_PORT_STATS; i++) अणु
				म_नकल(buf, bnxt_port_stats_arr[i].string);
				buf += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		अगर (bp->flags & BNXT_FLAG_PORT_STATS_EXT) अणु
			क्रम (i = 0; i < bp->fw_rx_stats_ext_size; i++) अणु
				म_नकल(buf, bnxt_port_stats_ext_arr[i].string);
				buf += ETH_GSTRING_LEN;
			पूर्ण
			क्रम (i = 0; i < bp->fw_tx_stats_ext_size; i++) अणु
				म_नकल(buf,
				       bnxt_tx_port_stats_ext_arr[i].string);
				buf += ETH_GSTRING_LEN;
			पूर्ण
			अगर (bp->pri2cos_valid) अणु
				क्रम (i = 0; i < 8; i++) अणु
					म_नकल(buf,
					       bnxt_rx_bytes_pri_arr[i].string);
					buf += ETH_GSTRING_LEN;
				पूर्ण
				क्रम (i = 0; i < 8; i++) अणु
					म_नकल(buf,
					       bnxt_rx_pkts_pri_arr[i].string);
					buf += ETH_GSTRING_LEN;
				पूर्ण
				क्रम (i = 0; i < 8; i++) अणु
					म_नकल(buf,
					       bnxt_tx_bytes_pri_arr[i].string);
					buf += ETH_GSTRING_LEN;
				पूर्ण
				क्रम (i = 0; i < 8; i++) अणु
					म_नकल(buf,
					       bnxt_tx_pkts_pri_arr[i].string);
					buf += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ETH_SS_TEST:
		अगर (bp->num_tests)
			स_नकल(buf, bp->test_info->string,
			       bp->num_tests * ETH_GSTRING_LEN);
		अवरोध;
	शेष:
		netdev_err(bp->dev, "bnxt_get_strings invalid request %x\n",
			   stringset);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnxt_get_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	ering->rx_max_pending = BNXT_MAX_RX_DESC_CNT;
	ering->rx_jumbo_max_pending = BNXT_MAX_RX_JUM_DESC_CNT;
	ering->tx_max_pending = BNXT_MAX_TX_DESC_CNT;

	ering->rx_pending = bp->rx_ring_size;
	ering->rx_jumbo_pending = bp->rx_agg_ring_size;
	ering->tx_pending = bp->tx_ring_size;
पूर्ण

अटल पूर्णांक bnxt_set_ringparam(काष्ठा net_device *dev,
			      काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर ((ering->rx_pending > BNXT_MAX_RX_DESC_CNT) ||
	    (ering->tx_pending > BNXT_MAX_TX_DESC_CNT) ||
	    (ering->tx_pending <= MAX_SKB_FRAGS))
		वापस -EINVAL;

	अगर (netअगर_running(dev))
		bnxt_बंद_nic(bp, false, false);

	bp->rx_ring_size = ering->rx_pending;
	bp->tx_ring_size = ering->tx_pending;
	bnxt_set_ring_params(bp);

	अगर (netअगर_running(dev))
		वापस bnxt_खोलो_nic(bp, false, false);

	वापस 0;
पूर्ण

अटल व्योम bnxt_get_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channel)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	पूर्णांक max_rx_rings, max_tx_rings, tcs;
	पूर्णांक max_tx_sch_inमाला_दो, tx_grps;

	/* Get the most up-to-date max_tx_sch_inमाला_दो. */
	अगर (netअगर_running(dev) && BNXT_NEW_RM(bp))
		bnxt_hwrm_func_resc_qcaps(bp, false);
	max_tx_sch_inमाला_दो = hw_resc->max_tx_sch_inमाला_दो;

	bnxt_get_max_rings(bp, &max_rx_rings, &max_tx_rings, true);
	अगर (max_tx_sch_inमाला_दो)
		max_tx_rings = min_t(पूर्णांक, max_tx_rings, max_tx_sch_inमाला_दो);

	tcs = netdev_get_num_tc(dev);
	tx_grps = max(tcs, 1);
	अगर (bp->tx_nr_rings_xdp)
		tx_grps++;
	max_tx_rings /= tx_grps;
	channel->max_combined = min_t(पूर्णांक, max_rx_rings, max_tx_rings);

	अगर (bnxt_get_max_rings(bp, &max_rx_rings, &max_tx_rings, false)) अणु
		max_rx_rings = 0;
		max_tx_rings = 0;
	पूर्ण
	अगर (max_tx_sch_inमाला_दो)
		max_tx_rings = min_t(पूर्णांक, max_tx_rings, max_tx_sch_inमाला_दो);

	अगर (tcs > 1)
		max_tx_rings /= tcs;

	channel->max_rx = max_rx_rings;
	channel->max_tx = max_tx_rings;
	channel->max_other = 0;
	अगर (bp->flags & BNXT_FLAG_SHARED_RINGS) अणु
		channel->combined_count = bp->rx_nr_rings;
		अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
			channel->combined_count--;
	पूर्ण अन्यथा अणु
		अगर (!BNXT_CHIP_TYPE_NITRO_A0(bp)) अणु
			channel->rx_count = bp->rx_nr_rings;
			channel->tx_count = bp->tx_nr_rings_per_tc;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_set_channels(काष्ठा net_device *dev,
			     काष्ठा ethtool_channels *channel)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक req_tx_rings, req_rx_rings, tcs;
	bool sh = false;
	पूर्णांक tx_xdp = 0;
	पूर्णांक rc = 0;

	अगर (channel->other_count)
		वापस -EINVAL;

	अगर (!channel->combined_count &&
	    (!channel->rx_count || !channel->tx_count))
		वापस -EINVAL;

	अगर (channel->combined_count &&
	    (channel->rx_count || channel->tx_count))
		वापस -EINVAL;

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp) && (channel->rx_count ||
					    channel->tx_count))
		वापस -EINVAL;

	अगर (channel->combined_count)
		sh = true;

	tcs = netdev_get_num_tc(dev);

	req_tx_rings = sh ? channel->combined_count : channel->tx_count;
	req_rx_rings = sh ? channel->combined_count : channel->rx_count;
	अगर (bp->tx_nr_rings_xdp) अणु
		अगर (!sh) अणु
			netdev_err(dev, "Only combined mode supported when XDP is enabled.\n");
			वापस -EINVAL;
		पूर्ण
		tx_xdp = req_rx_rings;
	पूर्ण
	rc = bnxt_check_rings(bp, req_tx_rings, req_rx_rings, sh, tcs, tx_xdp);
	अगर (rc) अणु
		netdev_warn(dev, "Unable to allocate the requested rings\n");
		वापस rc;
	पूर्ण

	अगर (bnxt_get_nr_rss_ctxs(bp, req_rx_rings) !=
	    bnxt_get_nr_rss_ctxs(bp, bp->rx_nr_rings) &&
	    (dev->priv_flags & IFF_RXFH_CONFIGURED)) अणु
		netdev_warn(dev, "RSS table size change required, RSS table entries must be default to proceed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		अगर (BNXT_PF(bp)) अणु
			/* TODO CHIMP_FW: Send message to all VF's
			 * beक्रमe PF unload
			 */
		पूर्ण
		rc = bnxt_बंद_nic(bp, true, false);
		अगर (rc) अणु
			netdev_err(bp->dev, "Set channel failure rc :%x\n",
				   rc);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (sh) अणु
		bp->flags |= BNXT_FLAG_SHARED_RINGS;
		bp->rx_nr_rings = channel->combined_count;
		bp->tx_nr_rings_per_tc = channel->combined_count;
	पूर्ण अन्यथा अणु
		bp->flags &= ~BNXT_FLAG_SHARED_RINGS;
		bp->rx_nr_rings = channel->rx_count;
		bp->tx_nr_rings_per_tc = channel->tx_count;
	पूर्ण
	bp->tx_nr_rings_xdp = tx_xdp;
	bp->tx_nr_rings = bp->tx_nr_rings_per_tc + tx_xdp;
	अगर (tcs > 1)
		bp->tx_nr_rings = bp->tx_nr_rings_per_tc * tcs + tx_xdp;

	bp->cp_nr_rings = sh ? max_t(पूर्णांक, bp->tx_nr_rings, bp->rx_nr_rings) :
			       bp->tx_nr_rings + bp->rx_nr_rings;

	/* After changing number of rx channels, update NTUPLE feature. */
	netdev_update_features(dev);
	अगर (netअगर_running(dev)) अणु
		rc = bnxt_खोलो_nic(bp, true, false);
		अगर ((!rc) && BNXT_PF(bp)) अणु
			/* TODO CHIMP_FW: Send message to all VF's
			 * to renable
			 */
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = bnxt_reserve_rings(bp, true);
	पूर्ण

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
अटल पूर्णांक bnxt_grxclsrlall(काष्ठा bnxt *bp, काष्ठा ethtool_rxnfc *cmd,
			    u32 *rule_locs)
अणु
	पूर्णांक i, j = 0;

	cmd->data = bp->ntp_fltr_count;
	क्रम (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++) अणु
		काष्ठा hlist_head *head;
		काष्ठा bnxt_ntuple_filter *fltr;

		head = &bp->ntp_fltr_hash_tbl[i];
		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(fltr, head, hash) अणु
			अगर (j == cmd->rule_cnt)
				अवरोध;
			rule_locs[j++] = fltr->sw_id;
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (j == cmd->rule_cnt)
			अवरोध;
	पूर्ण
	cmd->rule_cnt = j;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_grxclsrule(काष्ठा bnxt *bp, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fs =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा bnxt_ntuple_filter *fltr;
	काष्ठा flow_keys *fkeys;
	पूर्णांक i, rc = -EINVAL;

	अगर (fs->location >= BNXT_NTP_FLTR_MAX_FLTR)
		वापस rc;

	क्रम (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++) अणु
		काष्ठा hlist_head *head;

		head = &bp->ntp_fltr_hash_tbl[i];
		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(fltr, head, hash) अणु
			अगर (fltr->sw_id == fs->location)
				जाओ fltr_found;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस rc;

fltr_found:
	fkeys = &fltr->fkeys;
	अगर (fkeys->basic.n_proto == htons(ETH_P_IP)) अणु
		अगर (fkeys->basic.ip_proto == IPPROTO_TCP)
			fs->flow_type = TCP_V4_FLOW;
		अन्यथा अगर (fkeys->basic.ip_proto == IPPROTO_UDP)
			fs->flow_type = UDP_V4_FLOW;
		अन्यथा
			जाओ fltr_err;

		fs->h_u.tcp_ip4_spec.ip4src = fkeys->addrs.v4addrs.src;
		fs->m_u.tcp_ip4_spec.ip4src = cpu_to_be32(~0);

		fs->h_u.tcp_ip4_spec.ip4dst = fkeys->addrs.v4addrs.dst;
		fs->m_u.tcp_ip4_spec.ip4dst = cpu_to_be32(~0);

		fs->h_u.tcp_ip4_spec.psrc = fkeys->ports.src;
		fs->m_u.tcp_ip4_spec.psrc = cpu_to_be16(~0);

		fs->h_u.tcp_ip4_spec.pdst = fkeys->ports.dst;
		fs->m_u.tcp_ip4_spec.pdst = cpu_to_be16(~0);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		अगर (fkeys->basic.ip_proto == IPPROTO_TCP)
			fs->flow_type = TCP_V6_FLOW;
		अन्यथा अगर (fkeys->basic.ip_proto == IPPROTO_UDP)
			fs->flow_type = UDP_V6_FLOW;
		अन्यथा
			जाओ fltr_err;

		*(काष्ठा in6_addr *)&fs->h_u.tcp_ip6_spec.ip6src[0] =
			fkeys->addrs.v6addrs.src;
		*(काष्ठा in6_addr *)&fs->h_u.tcp_ip6_spec.ip6dst[0] =
			fkeys->addrs.v6addrs.dst;
		क्रम (i = 0; i < 4; i++) अणु
			fs->m_u.tcp_ip6_spec.ip6src[i] = cpu_to_be32(~0);
			fs->m_u.tcp_ip6_spec.ip6dst[i] = cpu_to_be32(~0);
		पूर्ण
		fs->h_u.tcp_ip6_spec.psrc = fkeys->ports.src;
		fs->m_u.tcp_ip6_spec.psrc = cpu_to_be16(~0);

		fs->h_u.tcp_ip6_spec.pdst = fkeys->ports.dst;
		fs->m_u.tcp_ip6_spec.pdst = cpu_to_be16(~0);
	पूर्ण

	fs->ring_cookie = fltr->rxq;
	rc = 0;

fltr_err:
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल u64 get_ethtool_ipv4_rss(काष्ठा bnxt *bp)
अणु
	अगर (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4)
		वापस RXH_IP_SRC | RXH_IP_DST;
	वापस 0;
पूर्ण

अटल u64 get_ethtool_ipv6_rss(काष्ठा bnxt *bp)
अणु
	अगर (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6)
		वापस RXH_IP_SRC | RXH_IP_DST;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_grxfh(काष्ठा bnxt *bp, काष्ठा ethtool_rxnfc *cmd)
अणु
	cmd->data = 0;
	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		अगर (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		cmd->data |= get_ethtool_ipv4_rss(bp);
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल IPV4_FLOW:
		cmd->data |= get_ethtool_ipv4_rss(bp);
		अवरोध;

	हाल TCP_V6_FLOW:
		अगर (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		cmd->data |= get_ethtool_ipv6_rss(bp);
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV6_FLOW:
		cmd->data |= get_ethtool_ipv6_rss(bp);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा RXH_4TUPLE (RXH_IP_SRC | RXH_IP_DST | RXH_L4_B_0_1 | RXH_L4_B_2_3)
#घोषणा RXH_2TUPLE (RXH_IP_SRC | RXH_IP_DST)

अटल पूर्णांक bnxt_srxfh(काष्ठा bnxt *bp, काष्ठा ethtool_rxnfc *cmd)
अणु
	u32 rss_hash_cfg = bp->rss_hash_cfg;
	पूर्णांक tuple, rc = 0;

	अगर (cmd->data == RXH_4TUPLE)
		tuple = 4;
	अन्यथा अगर (cmd->data == RXH_2TUPLE)
		tuple = 2;
	अन्यथा अगर (!cmd->data)
		tuple = 0;
	अन्यथा
		वापस -EINVAL;

	अगर (cmd->flow_type == TCP_V4_FLOW) अणु
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4;
		अगर (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4;
	पूर्ण अन्यथा अगर (cmd->flow_type == UDP_V4_FLOW) अणु
		अगर (tuple == 4 && !(bp->flags & BNXT_FLAG_UDP_RSS_CAP))
			वापस -EINVAL;
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4;
		अगर (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4;
	पूर्ण अन्यथा अगर (cmd->flow_type == TCP_V6_FLOW) अणु
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6;
		अगर (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6;
	पूर्ण अन्यथा अगर (cmd->flow_type == UDP_V6_FLOW) अणु
		अगर (tuple == 4 && !(bp->flags & BNXT_FLAG_UDP_RSS_CAP))
			वापस -EINVAL;
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6;
		अगर (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6;
	पूर्ण अन्यथा अगर (tuple == 4) अणु
		वापस -EINVAL;
	पूर्ण

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल IPV4_FLOW:
		अगर (tuple == 2)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4;
		अन्यथा अगर (!tuple)
			rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4;
		अवरोध;

	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV6_FLOW:
		अगर (tuple == 2)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6;
		अन्यथा अगर (!tuple)
			rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6;
		अवरोध;
	पूर्ण

	अगर (bp->rss_hash_cfg == rss_hash_cfg)
		वापस 0;

	bp->rss_hash_cfg = rss_hash_cfg;
	अगर (netअगर_running(bp->dev)) अणु
		bnxt_बंद_nic(bp, false, false);
		rc = bnxt_खोलो_nic(bp, false, false);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			  u32 *rule_locs)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	चयन (cmd->cmd) अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	हाल ETHTOOL_GRXRINGS:
		cmd->data = bp->rx_nr_rings;
		अवरोध;

	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = bp->ntp_fltr_count;
		cmd->data = BNXT_NTP_FLTR_MAX_FLTR;
		अवरोध;

	हाल ETHTOOL_GRXCLSRLALL:
		rc = bnxt_grxclsrlall(bp, cmd, (u32 *)rule_locs);
		अवरोध;

	हाल ETHTOOL_GRXCLSRULE:
		rc = bnxt_grxclsrule(bp, cmd);
		अवरोध;
#पूर्ण_अगर

	हाल ETHTOOL_GRXFH:
		rc = bnxt_grxfh(bp, cmd);
		अवरोध;

	शेष:
		rc = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		rc = bnxt_srxfh(bp, cmd);
		अवरोध;

	शेष:
		rc = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

u32 bnxt_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस ALIGN(bp->rx_nr_rings, BNXT_RSS_TABLE_ENTRIES_P5);
	वापस HW_HASH_INDEX_SIZE;
पूर्ण

अटल u32 bnxt_get_rxfh_key_size(काष्ठा net_device *dev)
अणु
	वापस HW_HASH_KEY_SIZE;
पूर्ण

अटल पूर्णांक bnxt_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key,
			 u8 *hfunc)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vnic_info *vnic;
	u32 i, tbl_size;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (!bp->vnic_info)
		वापस 0;

	vnic = &bp->vnic_info[0];
	अगर (indir && bp->rss_indir_tbl) अणु
		tbl_size = bnxt_get_rxfh_indir_size(dev);
		क्रम (i = 0; i < tbl_size; i++)
			indir[i] = bp->rss_indir_tbl[i];
	पूर्ण

	अगर (key && vnic->rss_hash_key)
		स_नकल(key, vnic->rss_hash_key, HW_HASH_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
			 स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	अगर (hfunc && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (key)
		वापस -EOPNOTSUPP;

	अगर (indir) अणु
		u32 i, pad, tbl_size = bnxt_get_rxfh_indir_size(dev);

		क्रम (i = 0; i < tbl_size; i++)
			bp->rss_indir_tbl[i] = indir[i];
		pad = bp->rss_indir_tbl_entries - tbl_size;
		अगर (pad)
			स_रखो(&bp->rss_indir_tbl[i], 0, pad * माप(u16));
	पूर्ण

	अगर (netअगर_running(bp->dev)) अणु
		bnxt_बंद_nic(bp, false, false);
		rc = bnxt_खोलो_nic(bp, false, false);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnxt_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->fw_version, bp->fw_ver_str, माप(info->fw_version));
	strlcpy(info->bus_info, pci_name(bp->pdev), माप(info->bus_info));
	info->n_stats = bnxt_get_num_stats(bp);
	info->testinfo_len = bp->num_tests;
	/* TODO CHIMP_FW: eeprom dump details */
	info->eedump_len = 0;
	/* TODO CHIMP FW: reg dump details */
	info->regdump_len = 0;
पूर्ण

अटल पूर्णांक bnxt_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक reg_len;

	अगर (!BNXT_PF(bp))
		वापस -EOPNOTSUPP;

	reg_len = BNXT_PXP_REG_LEN;

	अगर (bp->fw_cap & BNXT_FW_CAP_PCIE_STATS_SUPPORTED)
		reg_len += माप(काष्ठा pcie_ctx_hw_stats);

	वापस reg_len;
पूर्ण

अटल व्योम bnxt_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			  व्योम *_p)
अणु
	काष्ठा pcie_ctx_hw_stats *hw_pcie_stats;
	काष्ठा hwrm_pcie_qstats_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	dma_addr_t hw_pcie_stats_addr;
	पूर्णांक rc;

	regs->version = 0;
	bnxt_dbg_hwrm_rd_reg(bp, 0, BNXT_PXP_REG_LEN / 4, _p);

	अगर (!(bp->fw_cap & BNXT_FW_CAP_PCIE_STATS_SUPPORTED))
		वापस;

	hw_pcie_stats = dma_alloc_coherent(&bp->pdev->dev,
					   माप(*hw_pcie_stats),
					   &hw_pcie_stats_addr, GFP_KERNEL);
	अगर (!hw_pcie_stats)
		वापस;

	regs->version = 1;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PCIE_QSTATS, -1, -1);
	req.pcie_stat_size = cpu_to_le16(माप(*hw_pcie_stats));
	req.pcie_stat_host_addr = cpu_to_le64(hw_pcie_stats_addr);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		__le64 *src = (__le64 *)hw_pcie_stats;
		u64 *dst = (u64 *)(_p + BNXT_PXP_REG_LEN);
		पूर्णांक i;

		क्रम (i = 0; i < माप(*hw_pcie_stats) / माप(__le64); i++)
			dst[i] = le64_to_cpu(src[i]);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	dma_मुक्त_coherent(&bp->pdev->dev, माप(*hw_pcie_stats), hw_pcie_stats,
			  hw_pcie_stats_addr);
पूर्ण

अटल व्योम bnxt_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	wol->supported = 0;
	wol->wolopts = 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
	अगर (bp->flags & BNXT_FLAG_WOL_CAP) अणु
		wol->supported = WAKE_MAGIC;
		अगर (bp->wol)
			wol->wolopts = WAKE_MAGIC;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		अगर (!(bp->flags & BNXT_FLAG_WOL_CAP))
			वापस -EINVAL;
		अगर (!bp->wol) अणु
			अगर (bnxt_hwrm_alloc_wol_fltr(bp))
				वापस -EBUSY;
			bp->wol = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bp->wol) अणु
			अगर (bnxt_hwrm_मुक्त_wol_fltr(bp))
				वापस -EBUSY;
			bp->wol = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

u32 _bnxt_fw_to_ethtool_adv_spds(u16 fw_speeds, u8 fw_छोड़ो)
अणु
	u32 speed_mask = 0;

	/* TODO: support 25GB, 40GB, 50GB with dअगरferent cable type */
	/* set the advertised speeds */
	अगर (fw_speeds & BNXT_LINK_SPEED_MSK_100MB)
		speed_mask |= ADVERTISED_100baseT_Full;
	अगर (fw_speeds & BNXT_LINK_SPEED_MSK_1GB)
		speed_mask |= ADVERTISED_1000baseT_Full;
	अगर (fw_speeds & BNXT_LINK_SPEED_MSK_2_5GB)
		speed_mask |= ADVERTISED_2500baseX_Full;
	अगर (fw_speeds & BNXT_LINK_SPEED_MSK_10GB)
		speed_mask |= ADVERTISED_10000baseT_Full;
	अगर (fw_speeds & BNXT_LINK_SPEED_MSK_40GB)
		speed_mask |= ADVERTISED_40000baseCR4_Full;

	अगर ((fw_छोड़ो & BNXT_LINK_PAUSE_BOTH) == BNXT_LINK_PAUSE_BOTH)
		speed_mask |= ADVERTISED_Pause;
	अन्यथा अगर (fw_छोड़ो & BNXT_LINK_PAUSE_TX)
		speed_mask |= ADVERTISED_Asym_Pause;
	अन्यथा अगर (fw_छोड़ो & BNXT_LINK_PAUSE_RX)
		speed_mask |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;

	वापस speed_mask;
पूर्ण

#घोषणा BNXT_FW_TO_ETHTOOL_SPDS(fw_speeds, fw_छोड़ो, lk_ksettings, name)\
अणु									\
	अगर ((fw_speeds) & BNXT_LINK_SPEED_MSK_100MB)			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     100baseT_Full);	\
	अगर ((fw_speeds) & BNXT_LINK_SPEED_MSK_1GB)			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     1000baseT_Full);	\
	अगर ((fw_speeds) & BNXT_LINK_SPEED_MSK_10GB)			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     10000baseT_Full);	\
	अगर ((fw_speeds) & BNXT_LINK_SPEED_MSK_25GB)			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     25000baseCR_Full);	\
	अगर ((fw_speeds) & BNXT_LINK_SPEED_MSK_40GB)			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     40000baseCR4_Full);\
	अगर ((fw_speeds) & BNXT_LINK_SPEED_MSK_50GB)			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     50000baseCR2_Full);\
	अगर ((fw_speeds) & BNXT_LINK_SPEED_MSK_100GB)			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     100000baseCR4_Full);\
	अगर ((fw_छोड़ो) & BNXT_LINK_PAUSE_RX) अणु				\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     Pause);		\
		अगर (!((fw_छोड़ो) & BNXT_LINK_PAUSE_TX))			\
			ethtool_link_ksettings_add_link_mode(		\
					lk_ksettings, name, Asym_Pause);\
	पूर्ण अन्यथा अगर ((fw_छोड़ो) & BNXT_LINK_PAUSE_TX) अणु			\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     Asym_Pause);	\
	पूर्ण								\
पूर्ण

#घोषणा BNXT_ETHTOOL_TO_FW_SPDS(fw_speeds, lk_ksettings, name)		\
अणु									\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  100baseT_Full) ||	\
	    ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  100baseT_Half))	\
		(fw_speeds) |= BNXT_LINK_SPEED_MSK_100MB;		\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  1000baseT_Full) ||	\
	    ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  1000baseT_Half))	\
		(fw_speeds) |= BNXT_LINK_SPEED_MSK_1GB;			\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  10000baseT_Full))	\
		(fw_speeds) |= BNXT_LINK_SPEED_MSK_10GB;		\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  25000baseCR_Full))	\
		(fw_speeds) |= BNXT_LINK_SPEED_MSK_25GB;		\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  40000baseCR4_Full))	\
		(fw_speeds) |= BNXT_LINK_SPEED_MSK_40GB;		\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  50000baseCR2_Full))	\
		(fw_speeds) |= BNXT_LINK_SPEED_MSK_50GB;		\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  100000baseCR4_Full))	\
		(fw_speeds) |= BNXT_LINK_SPEED_MSK_100GB;		\
पूर्ण

#घोषणा BNXT_FW_TO_ETHTOOL_PAM4_SPDS(fw_speeds, lk_ksettings, name)	\
अणु									\
	अगर ((fw_speeds) & BNXT_LINK_PAM4_SPEED_MSK_50GB)		\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     50000baseCR_Full);	\
	अगर ((fw_speeds) & BNXT_LINK_PAM4_SPEED_MSK_100GB)		\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     100000baseCR2_Full);\
	अगर ((fw_speeds) & BNXT_LINK_PAM4_SPEED_MSK_200GB)		\
		ethtool_link_ksettings_add_link_mode(lk_ksettings, name,\
						     200000baseCR4_Full);\
पूर्ण

#घोषणा BNXT_ETHTOOL_TO_FW_PAM4_SPDS(fw_speeds, lk_ksettings, name)	\
अणु									\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  50000baseCR_Full))	\
		(fw_speeds) |= BNXT_LINK_PAM4_SPEED_MSK_50GB;		\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  100000baseCR2_Full))	\
		(fw_speeds) |= BNXT_LINK_PAM4_SPEED_MSK_100GB;		\
	अगर (ethtool_link_ksettings_test_link_mode(lk_ksettings, name,	\
						  200000baseCR4_Full))	\
		(fw_speeds) |= BNXT_LINK_PAM4_SPEED_MSK_200GB;		\
पूर्ण

अटल व्योम bnxt_fw_to_ethtool_advertised_fec(काष्ठा bnxt_link_info *link_info,
				काष्ठा ethtool_link_ksettings *lk_ksettings)
अणु
	u16 fec_cfg = link_info->fec_cfg;

	अगर ((fec_cfg & BNXT_FEC_NONE) || !(fec_cfg & BNXT_FEC_AUTONEG)) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_NONE_BIT,
				 lk_ksettings->link_modes.advertising);
		वापस;
	पूर्ण
	अगर (fec_cfg & BNXT_FEC_ENC_BASE_R)
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT,
				 lk_ksettings->link_modes.advertising);
	अगर (fec_cfg & BNXT_FEC_ENC_RS)
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT,
				 lk_ksettings->link_modes.advertising);
	अगर (fec_cfg & BNXT_FEC_ENC_LLRS)
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_LLRS_BIT,
				 lk_ksettings->link_modes.advertising);
पूर्ण

अटल व्योम bnxt_fw_to_ethtool_advertised_spds(काष्ठा bnxt_link_info *link_info,
				काष्ठा ethtool_link_ksettings *lk_ksettings)
अणु
	u16 fw_speeds = link_info->advertising;
	u8 fw_छोड़ो = 0;

	अगर (link_info->स्वतःneg & BNXT_AUTONEG_FLOW_CTRL)
		fw_छोड़ो = link_info->स्वतः_छोड़ो_setting;

	BNXT_FW_TO_ETHTOOL_SPDS(fw_speeds, fw_छोड़ो, lk_ksettings, advertising);
	fw_speeds = link_info->advertising_pam4;
	BNXT_FW_TO_ETHTOOL_PAM4_SPDS(fw_speeds, lk_ksettings, advertising);
	bnxt_fw_to_ethtool_advertised_fec(link_info, lk_ksettings);
पूर्ण

अटल व्योम bnxt_fw_to_ethtool_lp_adv(काष्ठा bnxt_link_info *link_info,
				काष्ठा ethtool_link_ksettings *lk_ksettings)
अणु
	u16 fw_speeds = link_info->lp_स्वतः_link_speeds;
	u8 fw_छोड़ो = 0;

	अगर (link_info->स्वतःneg & BNXT_AUTONEG_FLOW_CTRL)
		fw_छोड़ो = link_info->lp_छोड़ो;

	BNXT_FW_TO_ETHTOOL_SPDS(fw_speeds, fw_छोड़ो, lk_ksettings,
				lp_advertising);
	fw_speeds = link_info->lp_स्वतः_pam4_link_speeds;
	BNXT_FW_TO_ETHTOOL_PAM4_SPDS(fw_speeds, lk_ksettings, lp_advertising);
पूर्ण

अटल व्योम bnxt_fw_to_ethtool_support_fec(काष्ठा bnxt_link_info *link_info,
				काष्ठा ethtool_link_ksettings *lk_ksettings)
अणु
	u16 fec_cfg = link_info->fec_cfg;

	अगर (fec_cfg & BNXT_FEC_NONE) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_NONE_BIT,
				 lk_ksettings->link_modes.supported);
		वापस;
	पूर्ण
	अगर (fec_cfg & BNXT_FEC_ENC_BASE_R_CAP)
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT,
				 lk_ksettings->link_modes.supported);
	अगर (fec_cfg & BNXT_FEC_ENC_RS_CAP)
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT,
				 lk_ksettings->link_modes.supported);
	अगर (fec_cfg & BNXT_FEC_ENC_LLRS_CAP)
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_LLRS_BIT,
				 lk_ksettings->link_modes.supported);
पूर्ण

अटल व्योम bnxt_fw_to_ethtool_support_spds(काष्ठा bnxt_link_info *link_info,
				काष्ठा ethtool_link_ksettings *lk_ksettings)
अणु
	u16 fw_speeds = link_info->support_speeds;

	BNXT_FW_TO_ETHTOOL_SPDS(fw_speeds, 0, lk_ksettings, supported);
	fw_speeds = link_info->support_pam4_speeds;
	BNXT_FW_TO_ETHTOOL_PAM4_SPDS(fw_speeds, lk_ksettings, supported);

	ethtool_link_ksettings_add_link_mode(lk_ksettings, supported, Pause);
	ethtool_link_ksettings_add_link_mode(lk_ksettings, supported,
					     Asym_Pause);

	अगर (link_info->support_स्वतः_speeds ||
	    link_info->support_pam4_स्वतः_speeds)
		ethtool_link_ksettings_add_link_mode(lk_ksettings, supported,
						     Autoneg);
	bnxt_fw_to_ethtool_support_fec(link_info, lk_ksettings);
पूर्ण

u32 bnxt_fw_to_ethtool_speed(u16 fw_link_speed)
अणु
	चयन (fw_link_speed) अणु
	हाल BNXT_LINK_SPEED_100MB:
		वापस SPEED_100;
	हाल BNXT_LINK_SPEED_1GB:
		वापस SPEED_1000;
	हाल BNXT_LINK_SPEED_2_5GB:
		वापस SPEED_2500;
	हाल BNXT_LINK_SPEED_10GB:
		वापस SPEED_10000;
	हाल BNXT_LINK_SPEED_20GB:
		वापस SPEED_20000;
	हाल BNXT_LINK_SPEED_25GB:
		वापस SPEED_25000;
	हाल BNXT_LINK_SPEED_40GB:
		वापस SPEED_40000;
	हाल BNXT_LINK_SPEED_50GB:
		वापस SPEED_50000;
	हाल BNXT_LINK_SPEED_100GB:
		वापस SPEED_100000;
	शेष:
		वापस SPEED_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *lk_ksettings)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info = &bp->link_info;
	काष्ठा ethtool_link_settings *base = &lk_ksettings->base;
	u32 ethtool_speed;

	ethtool_link_ksettings_zero_link_mode(lk_ksettings, supported);
	mutex_lock(&bp->link_lock);
	bnxt_fw_to_ethtool_support_spds(link_info, lk_ksettings);

	ethtool_link_ksettings_zero_link_mode(lk_ksettings, advertising);
	अगर (link_info->स्वतःneg) अणु
		bnxt_fw_to_ethtool_advertised_spds(link_info, lk_ksettings);
		ethtool_link_ksettings_add_link_mode(lk_ksettings,
						     advertising, Autoneg);
		base->स्वतःneg = AUTONEG_ENABLE;
		base->duplex = DUPLEX_UNKNOWN;
		अगर (link_info->phy_link_status == BNXT_LINK_LINK) अणु
			bnxt_fw_to_ethtool_lp_adv(link_info, lk_ksettings);
			अगर (link_info->duplex & BNXT_LINK_DUPLEX_FULL)
				base->duplex = DUPLEX_FULL;
			अन्यथा
				base->duplex = DUPLEX_HALF;
		पूर्ण
		ethtool_speed = bnxt_fw_to_ethtool_speed(link_info->link_speed);
	पूर्ण अन्यथा अणु
		base->स्वतःneg = AUTONEG_DISABLE;
		ethtool_speed =
			bnxt_fw_to_ethtool_speed(link_info->req_link_speed);
		base->duplex = DUPLEX_HALF;
		अगर (link_info->req_duplex == BNXT_LINK_DUPLEX_FULL)
			base->duplex = DUPLEX_FULL;
	पूर्ण
	base->speed = ethtool_speed;

	base->port = PORT_NONE;
	अगर (link_info->media_type == PORT_PHY_QCFG_RESP_MEDIA_TYPE_TP) अणु
		base->port = PORT_TP;
		ethtool_link_ksettings_add_link_mode(lk_ksettings, supported,
						     TP);
		ethtool_link_ksettings_add_link_mode(lk_ksettings, advertising,
						     TP);
	पूर्ण अन्यथा अणु
		ethtool_link_ksettings_add_link_mode(lk_ksettings, supported,
						     FIBRE);
		ethtool_link_ksettings_add_link_mode(lk_ksettings, advertising,
						     FIBRE);

		अगर (link_info->media_type == PORT_PHY_QCFG_RESP_MEDIA_TYPE_DAC)
			base->port = PORT_DA;
		अन्यथा अगर (link_info->media_type ==
			 PORT_PHY_QCFG_RESP_MEDIA_TYPE_FIBRE)
			base->port = PORT_FIBRE;
	पूर्ण
	base->phy_address = link_info->phy_addr;
	mutex_unlock(&bp->link_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_क्रमce_link_speed(काष्ठा net_device *dev, u32 ethtool_speed)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info = &bp->link_info;
	u16 support_pam4_spds = link_info->support_pam4_speeds;
	u16 support_spds = link_info->support_speeds;
	u8 sig_mode = BNXT_SIG_MODE_NRZ;
	u16 fw_speed = 0;

	चयन (ethtool_speed) अणु
	हाल SPEED_100:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_100MB)
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_100MB;
		अवरोध;
	हाल SPEED_1000:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_1GB)
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_1GB;
		अवरोध;
	हाल SPEED_2500:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_2_5GB)
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_2_5GB;
		अवरोध;
	हाल SPEED_10000:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_10GB)
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_10GB;
		अवरोध;
	हाल SPEED_20000:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_20GB)
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_20GB;
		अवरोध;
	हाल SPEED_25000:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_25GB)
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_25GB;
		अवरोध;
	हाल SPEED_40000:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_40GB)
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_40GB;
		अवरोध;
	हाल SPEED_50000:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_50GB) अणु
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_50GB;
		पूर्ण अन्यथा अगर (support_pam4_spds & BNXT_LINK_PAM4_SPEED_MSK_50GB) अणु
			fw_speed = PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_50GB;
			sig_mode = BNXT_SIG_MODE_PAM4;
		पूर्ण
		अवरोध;
	हाल SPEED_100000:
		अगर (support_spds & BNXT_LINK_SPEED_MSK_100GB) अणु
			fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_100GB;
		पूर्ण अन्यथा अगर (support_pam4_spds & BNXT_LINK_PAM4_SPEED_MSK_100GB) अणु
			fw_speed = PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_100GB;
			sig_mode = BNXT_SIG_MODE_PAM4;
		पूर्ण
		अवरोध;
	हाल SPEED_200000:
		अगर (support_pam4_spds & BNXT_LINK_PAM4_SPEED_MSK_200GB) अणु
			fw_speed = PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_200GB;
			sig_mode = BNXT_SIG_MODE_PAM4;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!fw_speed) अणु
		netdev_err(dev, "unsupported speed!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (link_info->req_link_speed == fw_speed &&
	    link_info->req_संकेत_mode == sig_mode &&
	    link_info->स्वतःneg == 0)
		वापस -EALREADY;

	link_info->req_link_speed = fw_speed;
	link_info->req_संकेत_mode = sig_mode;
	link_info->req_duplex = BNXT_LINK_DUPLEX_FULL;
	link_info->स्वतःneg = 0;
	link_info->advertising = 0;
	link_info->advertising_pam4 = 0;

	वापस 0;
पूर्ण

u16 bnxt_get_fw_स्वतः_link_speeds(u32 advertising)
अणु
	u16 fw_speed_mask = 0;

	/* only support स्वतःneg at speed 100, 1000, and 10000 */
	अगर (advertising & (ADVERTISED_100baseT_Full |
			   ADVERTISED_100baseT_Half)) अणु
		fw_speed_mask |= BNXT_LINK_SPEED_MSK_100MB;
	पूर्ण
	अगर (advertising & (ADVERTISED_1000baseT_Full |
			   ADVERTISED_1000baseT_Half)) अणु
		fw_speed_mask |= BNXT_LINK_SPEED_MSK_1GB;
	पूर्ण
	अगर (advertising & ADVERTISED_10000baseT_Full)
		fw_speed_mask |= BNXT_LINK_SPEED_MSK_10GB;

	अगर (advertising & ADVERTISED_40000baseCR4_Full)
		fw_speed_mask |= BNXT_LINK_SPEED_MSK_40GB;

	वापस fw_speed_mask;
पूर्ण

अटल पूर्णांक bnxt_set_link_ksettings(काष्ठा net_device *dev,
			   स्थिर काष्ठा ethtool_link_ksettings *lk_ksettings)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info = &bp->link_info;
	स्थिर काष्ठा ethtool_link_settings *base = &lk_ksettings->base;
	bool set_छोड़ो = false;
	u32 speed;
	पूर्णांक rc = 0;

	अगर (!BNXT_PHY_CFG_ABLE(bp))
		वापस -EOPNOTSUPP;

	mutex_lock(&bp->link_lock);
	अगर (base->स्वतःneg == AUTONEG_ENABLE) अणु
		link_info->advertising = 0;
		link_info->advertising_pam4 = 0;
		BNXT_ETHTOOL_TO_FW_SPDS(link_info->advertising, lk_ksettings,
					advertising);
		BNXT_ETHTOOL_TO_FW_PAM4_SPDS(link_info->advertising_pam4,
					     lk_ksettings, advertising);
		link_info->स्वतःneg |= BNXT_AUTONEG_SPEED;
		अगर (!link_info->advertising && !link_info->advertising_pam4) अणु
			link_info->advertising = link_info->support_स्वतः_speeds;
			link_info->advertising_pam4 =
				link_info->support_pam4_स्वतः_speeds;
		पूर्ण
		/* any change to स्वतःneg will cause link change, thereक्रमe the
		 * driver should put back the original छोड़ो setting in स्वतःneg
		 */
		set_छोड़ो = true;
	पूर्ण अन्यथा अणु
		u8 phy_type = link_info->phy_type;

		अगर (phy_type == PORT_PHY_QCFG_RESP_PHY_TYPE_BASET  ||
		    phy_type == PORT_PHY_QCFG_RESP_PHY_TYPE_BASETE ||
		    link_info->media_type == PORT_PHY_QCFG_RESP_MEDIA_TYPE_TP) अणु
			netdev_err(dev, "10GBase-T devices must autoneg\n");
			rc = -EINVAL;
			जाओ set_setting_निकास;
		पूर्ण
		अगर (base->duplex == DUPLEX_HALF) अणु
			netdev_err(dev, "HALF DUPLEX is not supported!\n");
			rc = -EINVAL;
			जाओ set_setting_निकास;
		पूर्ण
		speed = base->speed;
		rc = bnxt_क्रमce_link_speed(dev, speed);
		अगर (rc) अणु
			अगर (rc == -EALREADY)
				rc = 0;
			जाओ set_setting_निकास;
		पूर्ण
	पूर्ण

	अगर (netअगर_running(dev))
		rc = bnxt_hwrm_set_link_setting(bp, set_छोड़ो, false);

set_setting_निकास:
	mutex_unlock(&bp->link_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_get_fecparam(काष्ठा net_device *dev,
			     काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info;
	u8 active_fec;
	u16 fec_cfg;

	link_info = &bp->link_info;
	fec_cfg = link_info->fec_cfg;
	active_fec = link_info->active_fec_sig_mode &
		     PORT_PHY_QCFG_RESP_ACTIVE_FEC_MASK;
	अगर (fec_cfg & BNXT_FEC_NONE) अणु
		fec->fec = ETHTOOL_FEC_NONE;
		fec->active_fec = ETHTOOL_FEC_NONE;
		वापस 0;
	पूर्ण
	अगर (fec_cfg & BNXT_FEC_AUTONEG)
		fec->fec |= ETHTOOL_FEC_AUTO;
	अगर (fec_cfg & BNXT_FEC_ENC_BASE_R)
		fec->fec |= ETHTOOL_FEC_BASER;
	अगर (fec_cfg & BNXT_FEC_ENC_RS)
		fec->fec |= ETHTOOL_FEC_RS;
	अगर (fec_cfg & BNXT_FEC_ENC_LLRS)
		fec->fec |= ETHTOOL_FEC_LLRS;

	चयन (active_fec) अणु
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_CLAUSE74_ACTIVE:
		fec->active_fec |= ETHTOOL_FEC_BASER;
		अवरोध;
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_CLAUSE91_ACTIVE:
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS544_1XN_ACTIVE:
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS544_IEEE_ACTIVE:
		fec->active_fec |= ETHTOOL_FEC_RS;
		अवरोध;
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS272_1XN_ACTIVE:
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS272_IEEE_ACTIVE:
		fec->active_fec |= ETHTOOL_FEC_LLRS;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_get_fec_stats(काष्ठा net_device *dev,
			       काष्ठा ethtool_fec_stats *fec_stats)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u64 *rx;

	अगर (BNXT_VF(bp) || !(bp->flags & BNXT_FLAG_PORT_STATS_EXT))
		वापस;

	rx = bp->rx_port_stats_ext.sw_stats;
	fec_stats->corrected_bits.total =
		*(rx + BNXT_RX_STATS_EXT_OFFSET(rx_corrected_bits));
पूर्ण

अटल u32 bnxt_ethtool_क्रमced_fec_to_fw(काष्ठा bnxt_link_info *link_info,
					 u32 fec)
अणु
	u32 fw_fec = PORT_PHY_CFG_REQ_FLAGS_FEC_AUTONEG_DISABLE;

	अगर (fec & ETHTOOL_FEC_BASER)
		fw_fec |= BNXT_FEC_BASE_R_ON(link_info);
	अन्यथा अगर (fec & ETHTOOL_FEC_RS)
		fw_fec |= BNXT_FEC_RS_ON(link_info);
	अन्यथा अगर (fec & ETHTOOL_FEC_LLRS)
		fw_fec |= BNXT_FEC_LLRS_ON;
	वापस fw_fec;
पूर्ण

अटल पूर्णांक bnxt_set_fecparam(काष्ठा net_device *dev,
			     काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा hwrm_port_phy_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info;
	u32 new_cfg, fec = fecparam->fec;
	u16 fec_cfg;
	पूर्णांक rc;

	link_info = &bp->link_info;
	fec_cfg = link_info->fec_cfg;
	अगर (fec_cfg & BNXT_FEC_NONE)
		वापस -EOPNOTSUPP;

	अगर (fec & ETHTOOL_FEC_OFF) अणु
		new_cfg = PORT_PHY_CFG_REQ_FLAGS_FEC_AUTONEG_DISABLE |
			  BNXT_FEC_ALL_OFF(link_info);
		जाओ apply_fec;
	पूर्ण
	अगर (((fec & ETHTOOL_FEC_AUTO) && !(fec_cfg & BNXT_FEC_AUTONEG_CAP)) ||
	    ((fec & ETHTOOL_FEC_RS) && !(fec_cfg & BNXT_FEC_ENC_RS_CAP)) ||
	    ((fec & ETHTOOL_FEC_LLRS) && !(fec_cfg & BNXT_FEC_ENC_LLRS_CAP)) ||
	    ((fec & ETHTOOL_FEC_BASER) && !(fec_cfg & BNXT_FEC_ENC_BASE_R_CAP)))
		वापस -EINVAL;

	अगर (fec & ETHTOOL_FEC_AUTO) अणु
		अगर (!link_info->स्वतःneg)
			वापस -EINVAL;
		new_cfg = PORT_PHY_CFG_REQ_FLAGS_FEC_AUTONEG_ENABLE;
	पूर्ण अन्यथा अणु
		new_cfg = bnxt_ethtool_क्रमced_fec_to_fw(link_info, fec);
	पूर्ण

apply_fec:
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);
	req.flags = cpu_to_le32(new_cfg | PORT_PHY_CFG_REQ_FLAGS_RESET_PHY);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	/* update current settings */
	अगर (!rc) अणु
		mutex_lock(&bp->link_lock);
		bnxt_update_link(bp, false);
		mutex_unlock(&bp->link_lock);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnxt_get_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	अगर (BNXT_VF(bp))
		वापस;
	eछोड़ो->स्वतःneg = !!(link_info->स्वतःneg & BNXT_AUTONEG_FLOW_CTRL);
	eछोड़ो->rx_छोड़ो = !!(link_info->req_flow_ctrl & BNXT_LINK_PAUSE_RX);
	eछोड़ो->tx_छोड़ो = !!(link_info->req_flow_ctrl & BNXT_LINK_PAUSE_TX);
पूर्ण

अटल व्योम bnxt_get_छोड़ो_stats(काष्ठा net_device *dev,
				 काष्ठा ethtool_छोड़ो_stats *epstat)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u64 *rx, *tx;

	अगर (BNXT_VF(bp) || !(bp->flags & BNXT_FLAG_PORT_STATS))
		वापस;

	rx = bp->port_stats.sw_stats;
	tx = bp->port_stats.sw_stats + BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;

	epstat->rx_छोड़ो_frames = BNXT_GET_RX_PORT_STATS64(rx, rx_छोड़ो_frames);
	epstat->tx_छोड़ो_frames = BNXT_GET_TX_PORT_STATS64(tx, tx_छोड़ो_frames);
पूर्ण

अटल पूर्णांक bnxt_set_छोड़ोparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	पूर्णांक rc = 0;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	अगर (!BNXT_PHY_CFG_ABLE(bp))
		वापस -EOPNOTSUPP;

	mutex_lock(&bp->link_lock);
	अगर (eछोड़ो->स्वतःneg) अणु
		अगर (!(link_info->स्वतःneg & BNXT_AUTONEG_SPEED)) अणु
			rc = -EINVAL;
			जाओ छोड़ो_निकास;
		पूर्ण

		link_info->स्वतःneg |= BNXT_AUTONEG_FLOW_CTRL;
		अगर (bp->hwrm_spec_code >= 0x10201)
			link_info->req_flow_ctrl =
				PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE;
	पूर्ण अन्यथा अणु
		/* when transition from स्वतः छोड़ो to क्रमce छोड़ो,
		 * क्रमce a link change
		 */
		अगर (link_info->स्वतःneg & BNXT_AUTONEG_FLOW_CTRL)
			link_info->क्रमce_link_chng = true;
		link_info->स्वतःneg &= ~BNXT_AUTONEG_FLOW_CTRL;
		link_info->req_flow_ctrl = 0;
	पूर्ण
	अगर (eछोड़ो->rx_छोड़ो)
		link_info->req_flow_ctrl |= BNXT_LINK_PAUSE_RX;

	अगर (eछोड़ो->tx_छोड़ो)
		link_info->req_flow_ctrl |= BNXT_LINK_PAUSE_TX;

	अगर (netअगर_running(dev))
		rc = bnxt_hwrm_set_छोड़ो(bp);

छोड़ो_निकास:
	mutex_unlock(&bp->link_lock);
	वापस rc;
पूर्ण

अटल u32 bnxt_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	/* TODO: handle MF, VF, driver बंद हाल */
	वापस bp->link_info.link_up;
पूर्ण

पूर्णांक bnxt_hwrm_nvm_get_dev_info(काष्ठा bnxt *bp,
			       काष्ठा hwrm_nvm_get_dev_info_output *nvm_dev_info)
अणु
	काष्ठा hwrm_nvm_get_dev_info_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_nvm_get_dev_info_input req = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (BNXT_VF(bp))
		वापस -EOPNOTSUPP;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_GET_DEV_INFO, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		स_नकल(nvm_dev_info, resp, माप(*resp));
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_prपूर्णांक_admin_err(काष्ठा bnxt *bp)
अणु
	netdev_info(bp->dev, "PF does not have admin privileges to flash or reset the device\n");
पूर्ण

अटल पूर्णांक bnxt_find_nvram_item(काष्ठा net_device *dev, u16 type, u16 ordinal,
				u16 ext, u16 *index, u32 *item_length,
				u32 *data_length);

अटल पूर्णांक __bnxt_flash_nvram(काष्ठा net_device *dev, u16 dir_type,
			      u16 dir_ordinal, u16 dir_ext, u16 dir_attr,
			      u32 dir_item_len, स्थिर u8 *data,
			      माप_प्रकार data_len)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;
	काष्ठा hwrm_nvm_ग_लिखो_input req = अणु0पूर्ण;
	dma_addr_t dma_handle;
	u8 *kmem = शून्य;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_WRITE, -1, -1);

	req.dir_type = cpu_to_le16(dir_type);
	req.dir_ordinal = cpu_to_le16(dir_ordinal);
	req.dir_ext = cpu_to_le16(dir_ext);
	req.dir_attr = cpu_to_le16(dir_attr);
	req.dir_item_length = cpu_to_le32(dir_item_len);
	अगर (data_len && data) अणु
		req.dir_data_length = cpu_to_le32(data_len);

		kmem = dma_alloc_coherent(&bp->pdev->dev, data_len, &dma_handle,
					  GFP_KERNEL);
		अगर (!kmem)
			वापस -ENOMEM;

		स_नकल(kmem, data, data_len);
		req.host_src_addr = cpu_to_le64(dma_handle);
	पूर्ण

	rc = _hwrm_send_message(bp, &req, माप(req), FLASH_NVRAM_TIMEOUT);
	अगर (kmem)
		dma_मुक्त_coherent(&bp->pdev->dev, data_len, kmem, dma_handle);

	अगर (rc == -EACCES)
		bnxt_prपूर्णांक_admin_err(bp);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_flash_nvram(काष्ठा net_device *dev, u16 dir_type,
			    u16 dir_ordinal, u16 dir_ext, u16 dir_attr,
			    स्थिर u8 *data, माप_प्रकार data_len)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = __bnxt_flash_nvram(dev, dir_type, dir_ordinal, dir_ext, dir_attr,
				0, data, data_len);
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_firmware_reset(काष्ठा net_device *dev, u8 proc_type,
				    u8 self_reset, u8 flags)
अणु
	काष्ठा hwrm_fw_reset_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FW_RESET, -1, -1);

	req.embedded_proc_type = proc_type;
	req.selfrst_status = self_reset;
	req.flags = flags;

	अगर (proc_type == FW_RESET_REQ_EMBEDDED_PROC_TYPE_AP) अणु
		rc = hwrm_send_message_silent(bp, &req, माप(req),
					      HWRM_CMD_TIMEOUT);
	पूर्ण अन्यथा अणु
		rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
		अगर (rc == -EACCES)
			bnxt_prपूर्णांक_admin_err(bp);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_firmware_reset(काष्ठा net_device *dev,
			       क्रमागत bnxt_nvm_directory_type dir_type)
अणु
	u8 self_reset = FW_RESET_REQ_SELFRST_STATUS_SELFRSTNONE;
	u8 proc_type, flags = 0;

	/* TODO: Address self-reset of APE/KONG/BONO/TANG or ungraceful reset */
	/*       (e.g. when firmware isn't alपढ़ोy running) */
	चयन (dir_type) अणु
	हाल BNX_सूची_TYPE_CHIMP_PATCH:
	हाल BNX_सूची_TYPE_BOOTCODE:
	हाल BNX_सूची_TYPE_BOOTCODE_2:
		proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_BOOT;
		/* Self-reset ChiMP upon next PCIe reset: */
		self_reset = FW_RESET_REQ_SELFRST_STATUS_SELFRSTPCIERST;
		अवरोध;
	हाल BNX_सूची_TYPE_APE_FW:
	हाल BNX_सूची_TYPE_APE_PATCH:
		proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_MGMT;
		/* Self-reset APE upon next PCIe reset: */
		self_reset = FW_RESET_REQ_SELFRST_STATUS_SELFRSTPCIERST;
		अवरोध;
	हाल BNX_सूची_TYPE_KONG_FW:
	हाल BNX_सूची_TYPE_KONG_PATCH:
		proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_NETCTRL;
		अवरोध;
	हाल BNX_सूची_TYPE_BONO_FW:
	हाल BNX_सूची_TYPE_BONO_PATCH:
		proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_ROCE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस bnxt_hwrm_firmware_reset(dev, proc_type, self_reset, flags);
पूर्ण

अटल पूर्णांक bnxt_firmware_reset_chip(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u8 flags = 0;

	अगर (bp->fw_cap & BNXT_FW_CAP_HOT_RESET)
		flags = FW_RESET_REQ_FLAGS_RESET_GRACEFUL;

	वापस bnxt_hwrm_firmware_reset(dev,
					FW_RESET_REQ_EMBEDDED_PROC_TYPE_CHIP,
					FW_RESET_REQ_SELFRST_STATUS_SELFRSTASAP,
					flags);
पूर्ण

अटल पूर्णांक bnxt_firmware_reset_ap(काष्ठा net_device *dev)
अणु
	वापस bnxt_hwrm_firmware_reset(dev, FW_RESET_REQ_EMBEDDED_PROC_TYPE_AP,
					FW_RESET_REQ_SELFRST_STATUS_SELFRSTNONE,
					0);
पूर्ण

अटल पूर्णांक bnxt_flash_firmware(काष्ठा net_device *dev,
			       u16 dir_type,
			       स्थिर u8 *fw_data,
			       माप_प्रकार fw_size)
अणु
	पूर्णांक	rc = 0;
	u16	code_type;
	u32	stored_crc;
	u32	calculated_crc;
	काष्ठा bnxt_fw_header *header = (काष्ठा bnxt_fw_header *)fw_data;

	चयन (dir_type) अणु
	हाल BNX_सूची_TYPE_BOOTCODE:
	हाल BNX_सूची_TYPE_BOOTCODE_2:
		code_type = CODE_BOOT;
		अवरोध;
	हाल BNX_सूची_TYPE_CHIMP_PATCH:
		code_type = CODE_CHIMP_PATCH;
		अवरोध;
	हाल BNX_सूची_TYPE_APE_FW:
		code_type = CODE_MCTP_PASSTHRU;
		अवरोध;
	हाल BNX_सूची_TYPE_APE_PATCH:
		code_type = CODE_APE_PATCH;
		अवरोध;
	हाल BNX_सूची_TYPE_KONG_FW:
		code_type = CODE_KONG_FW;
		अवरोध;
	हाल BNX_सूची_TYPE_KONG_PATCH:
		code_type = CODE_KONG_PATCH;
		अवरोध;
	हाल BNX_सूची_TYPE_BONO_FW:
		code_type = CODE_BONO_FW;
		अवरोध;
	हाल BNX_सूची_TYPE_BONO_PATCH:
		code_type = CODE_BONO_PATCH;
		अवरोध;
	शेष:
		netdev_err(dev, "Unsupported directory entry type: %u\n",
			   dir_type);
		वापस -EINVAL;
	पूर्ण
	अगर (fw_size < माप(काष्ठा bnxt_fw_header)) अणु
		netdev_err(dev, "Invalid firmware file size: %u\n",
			   (अचिन्हित पूर्णांक)fw_size);
		वापस -EINVAL;
	पूर्ण
	अगर (header->signature != cpu_to_le32(BNXT_FIRMWARE_BIN_SIGNATURE)) अणु
		netdev_err(dev, "Invalid firmware signature: %08X\n",
			   le32_to_cpu(header->signature));
		वापस -EINVAL;
	पूर्ण
	अगर (header->code_type != code_type) अणु
		netdev_err(dev, "Expected firmware type: %d, read: %d\n",
			   code_type, header->code_type);
		वापस -EINVAL;
	पूर्ण
	अगर (header->device != DEVICE_CUMULUS_FAMILY) अणु
		netdev_err(dev, "Expected firmware device family %d, read: %d\n",
			   DEVICE_CUMULUS_FAMILY, header->device);
		वापस -EINVAL;
	पूर्ण
	/* Confirm the CRC32 checksum of the file: */
	stored_crc = le32_to_cpu(*(__le32 *)(fw_data + fw_size -
					     माप(stored_crc)));
	calculated_crc = ~crc32(~0, fw_data, fw_size - माप(stored_crc));
	अगर (calculated_crc != stored_crc) अणु
		netdev_err(dev, "Firmware file CRC32 checksum (%08lX) does not match calculated checksum (%08lX)\n",
			   (अचिन्हित दीर्घ)stored_crc,
			   (अचिन्हित दीर्घ)calculated_crc);
		वापस -EINVAL;
	पूर्ण
	rc = bnxt_flash_nvram(dev, dir_type, BNX_सूची_ORDINAL_FIRST,
			      0, 0, fw_data, fw_size);
	अगर (rc == 0)	/* Firmware update successful */
		rc = bnxt_firmware_reset(dev, dir_type);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_flash_microcode(काष्ठा net_device *dev,
				u16 dir_type,
				स्थिर u8 *fw_data,
				माप_प्रकार fw_size)
अणु
	काष्ठा bnxt_ucode_trailer *trailer;
	u32 calculated_crc;
	u32 stored_crc;
	पूर्णांक rc = 0;

	अगर (fw_size < माप(काष्ठा bnxt_ucode_trailer)) अणु
		netdev_err(dev, "Invalid microcode file size: %u\n",
			   (अचिन्हित पूर्णांक)fw_size);
		वापस -EINVAL;
	पूर्ण
	trailer = (काष्ठा bnxt_ucode_trailer *)(fw_data + (fw_size -
						माप(*trailer)));
	अगर (trailer->sig != cpu_to_le32(BNXT_UCODE_TRAILER_SIGNATURE)) अणु
		netdev_err(dev, "Invalid microcode trailer signature: %08X\n",
			   le32_to_cpu(trailer->sig));
		वापस -EINVAL;
	पूर्ण
	अगर (le16_to_cpu(trailer->dir_type) != dir_type) अणु
		netdev_err(dev, "Expected microcode type: %d, read: %d\n",
			   dir_type, le16_to_cpu(trailer->dir_type));
		वापस -EINVAL;
	पूर्ण
	अगर (le16_to_cpu(trailer->trailer_length) <
		माप(काष्ठा bnxt_ucode_trailer)) अणु
		netdev_err(dev, "Invalid microcode trailer length: %d\n",
			   le16_to_cpu(trailer->trailer_length));
		वापस -EINVAL;
	पूर्ण

	/* Confirm the CRC32 checksum of the file: */
	stored_crc = le32_to_cpu(*(__le32 *)(fw_data + fw_size -
					     माप(stored_crc)));
	calculated_crc = ~crc32(~0, fw_data, fw_size - माप(stored_crc));
	अगर (calculated_crc != stored_crc) अणु
		netdev_err(dev,
			   "CRC32 (%08lX) does not match calculated: %08lX\n",
			   (अचिन्हित दीर्घ)stored_crc,
			   (अचिन्हित दीर्घ)calculated_crc);
		वापस -EINVAL;
	पूर्ण
	rc = bnxt_flash_nvram(dev, dir_type, BNX_सूची_ORDINAL_FIRST,
			      0, 0, fw_data, fw_size);

	वापस rc;
पूर्ण

अटल bool bnxt_dir_type_is_ape_bin_क्रमmat(u16 dir_type)
अणु
	चयन (dir_type) अणु
	हाल BNX_सूची_TYPE_CHIMP_PATCH:
	हाल BNX_सूची_TYPE_BOOTCODE:
	हाल BNX_सूची_TYPE_BOOTCODE_2:
	हाल BNX_सूची_TYPE_APE_FW:
	हाल BNX_सूची_TYPE_APE_PATCH:
	हाल BNX_सूची_TYPE_KONG_FW:
	हाल BNX_सूची_TYPE_KONG_PATCH:
	हाल BNX_सूची_TYPE_BONO_FW:
	हाल BNX_सूची_TYPE_BONO_PATCH:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool bnxt_dir_type_is_other_exec_क्रमmat(u16 dir_type)
अणु
	चयन (dir_type) अणु
	हाल BNX_सूची_TYPE_AVS:
	हाल BNX_सूची_TYPE_EXP_ROM_MBA:
	हाल BNX_सूची_TYPE_PCIE:
	हाल BNX_सूची_TYPE_TSCF_UCODE:
	हाल BNX_सूची_TYPE_EXT_PHY:
	हाल BNX_सूची_TYPE_CCM:
	हाल BNX_सूची_TYPE_ISCSI_BOOT:
	हाल BNX_सूची_TYPE_ISCSI_BOOT_IPV6:
	हाल BNX_सूची_TYPE_ISCSI_BOOT_IPV4N6:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool bnxt_dir_type_is_executable(u16 dir_type)
अणु
	वापस bnxt_dir_type_is_ape_bin_क्रमmat(dir_type) ||
		bnxt_dir_type_is_other_exec_क्रमmat(dir_type);
पूर्ण

अटल पूर्णांक bnxt_flash_firmware_from_file(काष्ठा net_device *dev,
					 u16 dir_type,
					 स्थिर अक्षर *filename)
अणु
	स्थिर काष्ठा firmware  *fw;
	पूर्णांक			rc;

	rc = request_firmware(&fw, filename, &dev->dev);
	अगर (rc != 0) अणु
		netdev_err(dev, "Error %d requesting firmware file: %s\n",
			   rc, filename);
		वापस rc;
	पूर्ण
	अगर (bnxt_dir_type_is_ape_bin_क्रमmat(dir_type))
		rc = bnxt_flash_firmware(dev, dir_type, fw->data, fw->size);
	अन्यथा अगर (bnxt_dir_type_is_other_exec_क्रमmat(dir_type))
		rc = bnxt_flash_microcode(dev, dir_type, fw->data, fw->size);
	अन्यथा
		rc = bnxt_flash_nvram(dev, dir_type, BNX_सूची_ORDINAL_FIRST,
				      0, 0, fw->data, fw->size);
	release_firmware(fw);
	वापस rc;
पूर्ण

#घोषणा BNXT_PKG_DMA_SIZE	0x40000
#घोषणा BNXT_NVM_MORE_FLAG	(cpu_to_le16(NVM_MODIFY_REQ_FLAGS_BATCH_MODE))
#घोषणा BNXT_NVM_LAST_FLAG	(cpu_to_le16(NVM_MODIFY_REQ_FLAGS_BATCH_LAST))

पूर्णांक bnxt_flash_package_from_fw_obj(काष्ठा net_device *dev, स्थिर काष्ठा firmware *fw,
				   u32 install_type)
अणु
	काष्ठा hwrm_nvm_install_update_input install = अणु0पूर्ण;
	काष्ठा hwrm_nvm_install_update_output resp = अणु0पूर्ण;
	काष्ठा hwrm_nvm_modअगरy_input modअगरy = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	bool defrag_attempted = false;
	dma_addr_t dma_handle;
	u8 *kmem = शून्य;
	u32 modअगरy_len;
	u32 item_len;
	पूर्णांक rc = 0;
	u16 index;

	bnxt_hwrm_fw_set_समय(bp);

	bnxt_hwrm_cmd_hdr_init(bp, &modअगरy, HWRM_NVM_MODIFY, -1, -1);

	/* Try allocating a large DMA buffer first.  Older fw will
	 * cause excessive NVRAM erases when using small blocks.
	 */
	modअगरy_len = roundup_घात_of_two(fw->size);
	modअगरy_len = min_t(u32, modअगरy_len, BNXT_PKG_DMA_SIZE);
	जबतक (1) अणु
		kmem = dma_alloc_coherent(&bp->pdev->dev, modअगरy_len,
					  &dma_handle, GFP_KERNEL);
		अगर (!kmem && modअगरy_len > PAGE_SIZE)
			modअगरy_len /= 2;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!kmem)
		वापस -ENOMEM;

	modअगरy.host_src_addr = cpu_to_le64(dma_handle);

	bnxt_hwrm_cmd_hdr_init(bp, &install, HWRM_NVM_INSTALL_UPDATE, -1, -1);
	अगर ((install_type & 0xffff) == 0)
		install_type >>= 16;
	install.install_type = cpu_to_le32(install_type);

	करो अणु
		u32 copied = 0, len = modअगरy_len;

		rc = bnxt_find_nvram_item(dev, BNX_सूची_TYPE_UPDATE,
					  BNX_सूची_ORDINAL_FIRST,
					  BNX_सूची_EXT_NONE,
					  &index, &item_len, शून्य);
		अगर (rc) अणु
			netdev_err(dev, "PKG update area not created in nvram\n");
			अवरोध;
		पूर्ण
		अगर (fw->size > item_len) अणु
			netdev_err(dev, "PKG insufficient update area in nvram: %lu\n",
				   (अचिन्हित दीर्घ)fw->size);
			rc = -EFBIG;
			अवरोध;
		पूर्ण

		modअगरy.dir_idx = cpu_to_le16(index);

		अगर (fw->size > modअगरy_len)
			modअगरy.flags = BNXT_NVM_MORE_FLAG;
		जबतक (copied < fw->size) अणु
			u32 balance = fw->size - copied;

			अगर (balance <= modअगरy_len) अणु
				len = balance;
				अगर (copied)
					modअगरy.flags |= BNXT_NVM_LAST_FLAG;
			पूर्ण
			स_नकल(kmem, fw->data + copied, len);
			modअगरy.len = cpu_to_le32(len);
			modअगरy.offset = cpu_to_le32(copied);
			rc = hwrm_send_message(bp, &modअगरy, माप(modअगरy),
					       FLASH_PACKAGE_TIMEOUT);
			अगर (rc)
				जाओ pkg_पात;
			copied += len;
		पूर्ण
		mutex_lock(&bp->hwrm_cmd_lock);
		rc = _hwrm_send_message_silent(bp, &install, माप(install),
					       INSTALL_PACKAGE_TIMEOUT);
		स_नकल(&resp, bp->hwrm_cmd_resp_addr, माप(resp));

		अगर (defrag_attempted) अणु
			/* We have tried to defragment alपढ़ोy in the previous
			 * iteration. Return with the result क्रम INSTALL_UPDATE
			 */
			mutex_unlock(&bp->hwrm_cmd_lock);
			अवरोध;
		पूर्ण

		अगर (rc && ((काष्ठा hwrm_err_output *)&resp)->cmd_err ==
		    NVM_INSTALL_UPDATE_CMD_ERR_CODE_FRAG_ERR) अणु
			install.flags =
				cpu_to_le16(NVM_INSTALL_UPDATE_REQ_FLAGS_ALLOWED_TO_DEFRAG);

			rc = _hwrm_send_message_silent(bp, &install,
						       माप(install),
						       INSTALL_PACKAGE_TIMEOUT);
			स_नकल(&resp, bp->hwrm_cmd_resp_addr, माप(resp));

			अगर (rc && ((काष्ठा hwrm_err_output *)&resp)->cmd_err ==
			    NVM_INSTALL_UPDATE_CMD_ERR_CODE_NO_SPACE) अणु
				/* FW has cleared NVM area, driver will create
				 * UPDATE directory and try the flash again
				 */
				defrag_attempted = true;
				install.flags = 0;
				rc = __bnxt_flash_nvram(bp->dev,
							BNX_सूची_TYPE_UPDATE,
							BNX_सूची_ORDINAL_FIRST,
							0, 0, item_len, शून्य,
							0);
			पूर्ण अन्यथा अगर (rc) अणु
				netdev_err(dev, "HWRM_NVM_INSTALL_UPDATE failure rc :%x\n", rc);
			पूर्ण
		पूर्ण अन्यथा अगर (rc) अणु
			netdev_err(dev, "HWRM_NVM_INSTALL_UPDATE failure rc :%x\n", rc);
		पूर्ण
		mutex_unlock(&bp->hwrm_cmd_lock);
	पूर्ण जबतक (defrag_attempted && !rc);

pkg_पात:
	dma_मुक्त_coherent(&bp->pdev->dev, modअगरy_len, kmem, dma_handle);
	अगर (resp.result) अणु
		netdev_err(dev, "PKG install error = %d, problem_item = %d\n",
			   (s8)resp.result, (पूर्णांक)resp.problem_item);
		rc = -ENOPKG;
	पूर्ण
	अगर (rc == -EACCES)
		bnxt_prपूर्णांक_admin_err(bp);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_flash_package_from_file(काष्ठा net_device *dev, स्थिर अक्षर *filename,
					u32 install_type)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक rc;

	rc = request_firmware(&fw, filename, &dev->dev);
	अगर (rc != 0) अणु
		netdev_err(dev, "PKG error %d requesting file: %s\n",
			   rc, filename);
		वापस rc;
	पूर्ण

	rc = bnxt_flash_package_from_fw_obj(dev, fw, install_type);

	release_firmware(fw);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_flash_device(काष्ठा net_device *dev,
			     काष्ठा ethtool_flash *flash)
अणु
	अगर (!BNXT_PF((काष्ठा bnxt *)netdev_priv(dev))) अणु
		netdev_err(dev, "flashdev not supported from a virtual function\n");
		वापस -EINVAL;
	पूर्ण

	अगर (flash->region == ETHTOOL_FLASH_ALL_REGIONS ||
	    flash->region > 0xffff)
		वापस bnxt_flash_package_from_file(dev, flash->data,
						    flash->region);

	वापस bnxt_flash_firmware_from_file(dev, flash->region, flash->data);
पूर्ण

अटल पूर्णांक nvm_get_dir_info(काष्ठा net_device *dev, u32 *entries, u32 *length)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;
	काष्ठा hwrm_nvm_get_dir_info_input req = अणु0पूर्ण;
	काष्ठा hwrm_nvm_get_dir_info_output *output = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_GET_सूची_INFO, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		*entries = le32_to_cpu(output->entries);
		*length = le32_to_cpu(output->entry_length);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (BNXT_VF(bp))
		वापस 0;

	/* The -1 वापस value allows the entire 32-bit range of offsets to be
	 * passed via the ethtool command-line utility.
	 */
	वापस -1;
पूर्ण

अटल पूर्णांक bnxt_get_nvram_directory(काष्ठा net_device *dev, u32 len, u8 *data)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;
	u32 dir_entries;
	u32 entry_length;
	u8 *buf;
	माप_प्रकार buflen;
	dma_addr_t dma_handle;
	काष्ठा hwrm_nvm_get_dir_entries_input req = अणु0पूर्ण;

	rc = nvm_get_dir_info(dev, &dir_entries, &entry_length);
	अगर (rc != 0)
		वापस rc;

	अगर (!dir_entries || !entry_length)
		वापस -EIO;

	/* Insert 2 bytes of directory info (count and size of entries) */
	अगर (len < 2)
		वापस -EINVAL;

	*data++ = dir_entries;
	*data++ = entry_length;
	len -= 2;
	स_रखो(data, 0xff, len);

	buflen = dir_entries * entry_length;
	buf = dma_alloc_coherent(&bp->pdev->dev, buflen, &dma_handle,
				 GFP_KERNEL);
	अगर (!buf) अणु
		netdev_err(dev, "dma_alloc_coherent failure, length = %u\n",
			   (अचिन्हित)buflen);
		वापस -ENOMEM;
	पूर्ण
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_GET_सूची_ENTRIES, -1, -1);
	req.host_dest_addr = cpu_to_le64(dma_handle);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc == 0)
		स_नकल(data, buf, len > buflen ? buflen : len);
	dma_मुक्त_coherent(&bp->pdev->dev, buflen, buf, dma_handle);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_get_nvram_item(काष्ठा net_device *dev, u32 index, u32 offset,
			       u32 length, u8 *data)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;
	u8 *buf;
	dma_addr_t dma_handle;
	काष्ठा hwrm_nvm_पढ़ो_input req = अणु0पूर्ण;

	अगर (!length)
		वापस -EINVAL;

	buf = dma_alloc_coherent(&bp->pdev->dev, length, &dma_handle,
				 GFP_KERNEL);
	अगर (!buf) अणु
		netdev_err(dev, "dma_alloc_coherent failure, length = %u\n",
			   (अचिन्हित)length);
		वापस -ENOMEM;
	पूर्ण
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_READ, -1, -1);
	req.host_dest_addr = cpu_to_le64(dma_handle);
	req.dir_idx = cpu_to_le16(index);
	req.offset = cpu_to_le32(offset);
	req.len = cpu_to_le32(length);

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc == 0)
		स_नकल(data, buf, length);
	dma_मुक्त_coherent(&bp->pdev->dev, length, buf, dma_handle);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_find_nvram_item(काष्ठा net_device *dev, u16 type, u16 ordinal,
				u16 ext, u16 *index, u32 *item_length,
				u32 *data_length)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;
	काष्ठा hwrm_nvm_find_dir_entry_input req = अणु0पूर्ण;
	काष्ठा hwrm_nvm_find_dir_entry_output *output = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_FIND_सूची_ENTRY, -1, -1);
	req.enables = 0;
	req.dir_idx = 0;
	req.dir_type = cpu_to_le16(type);
	req.dir_ordinal = cpu_to_le16(ordinal);
	req.dir_ext = cpu_to_le16(ext);
	req.opt_ordinal = NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_EQ;
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc == 0) अणु
		अगर (index)
			*index = le16_to_cpu(output->dir_idx);
		अगर (item_length)
			*item_length = le32_to_cpu(output->dir_item_length);
		अगर (data_length)
			*data_length = le32_to_cpu(output->dir_data_length);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल अक्षर *bnxt_parse_pkglog(पूर्णांक desired_field, u8 *data, माप_प्रकार datalen)
अणु
	अक्षर	*retval = शून्य;
	अक्षर	*p;
	अक्षर	*value;
	पूर्णांक	field = 0;

	अगर (datalen < 1)
		वापस शून्य;
	/* null-terminate the log data (removing last '\n'): */
	data[datalen - 1] = 0;
	क्रम (p = data; *p != 0; p++) अणु
		field = 0;
		retval = शून्य;
		जबतक (*p != 0 && *p != '\n') अणु
			value = p;
			जबतक (*p != 0 && *p != '\t' && *p != '\n')
				p++;
			अगर (field == desired_field)
				retval = value;
			अगर (*p != '\t')
				अवरोध;
			*p = 0;
			field++;
			p++;
		पूर्ण
		अगर (*p == 0)
			अवरोध;
		*p = 0;
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम bnxt_get_pkgver(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u16 index = 0;
	अक्षर *pkgver;
	u32 pkglen;
	u8 *pkgbuf;
	पूर्णांक len;

	अगर (bnxt_find_nvram_item(dev, BNX_सूची_TYPE_PKG_LOG,
				 BNX_सूची_ORDINAL_FIRST, BNX_सूची_EXT_NONE,
				 &index, शून्य, &pkglen) != 0)
		वापस;

	pkgbuf = kzalloc(pkglen, GFP_KERNEL);
	अगर (!pkgbuf) अणु
		dev_err(&bp->pdev->dev, "Unable to allocate memory for pkg version, length = %u\n",
			pkglen);
		वापस;
	पूर्ण

	अगर (bnxt_get_nvram_item(dev, index, 0, pkglen, pkgbuf))
		जाओ err;

	pkgver = bnxt_parse_pkglog(BNX_PKG_LOG_FIELD_IDX_PKG_VERSION, pkgbuf,
				   pkglen);
	अगर (pkgver && *pkgver != 0 && है_अंक(*pkgver)) अणु
		len = म_माप(bp->fw_ver_str);
		snम_लिखो(bp->fw_ver_str + len, FW_VER_STR_LEN - len - 1,
			 "/pkg %s", pkgver);
	पूर्ण
err:
	kमुक्त(pkgbuf);
पूर्ण

अटल पूर्णांक bnxt_get_eeprom(काष्ठा net_device *dev,
			   काष्ठा ethtool_eeprom *eeprom,
			   u8 *data)
अणु
	u32 index;
	u32 offset;

	अगर (eeprom->offset == 0) /* special offset value to get directory */
		वापस bnxt_get_nvram_directory(dev, eeprom->len, data);

	index = eeprom->offset >> 24;
	offset = eeprom->offset & 0xffffff;

	अगर (index == 0) अणु
		netdev_err(dev, "unsupported index value: %d\n", index);
		वापस -EINVAL;
	पूर्ण

	वापस bnxt_get_nvram_item(dev, index - 1, offset, eeprom->len, data);
पूर्ण

अटल पूर्णांक bnxt_erase_nvram_directory(काष्ठा net_device *dev, u8 index)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा hwrm_nvm_erase_dir_entry_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_ERASE_सूची_ENTRY, -1, -1);
	req.dir_idx = cpu_to_le16(index);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_set_eeprom(काष्ठा net_device *dev,
			   काष्ठा ethtool_eeprom *eeprom,
			   u8 *data)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u8 index, dir_op;
	u16 type, ext, ordinal, attr;

	अगर (!BNXT_PF(bp)) अणु
		netdev_err(dev, "NVM write not supported from a virtual function\n");
		वापस -EINVAL;
	पूर्ण

	type = eeprom->magic >> 16;

	अगर (type == 0xffff) अणु /* special value क्रम directory operations */
		index = eeprom->magic & 0xff;
		dir_op = eeprom->magic >> 8;
		अगर (index == 0)
			वापस -EINVAL;
		चयन (dir_op) अणु
		हाल 0x0e: /* erase */
			अगर (eeprom->offset != ~eeprom->magic)
				वापस -EINVAL;
			वापस bnxt_erase_nvram_directory(dev, index - 1);
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Create or re-ग_लिखो an NVM item: */
	अगर (bnxt_dir_type_is_executable(type))
		वापस -EOPNOTSUPP;
	ext = eeprom->magic & 0xffff;
	ordinal = eeprom->offset >> 16;
	attr = eeprom->offset & 0xffff;

	वापस bnxt_flash_nvram(dev, type, ordinal, ext, attr, data,
				eeprom->len);
पूर्ण

अटल पूर्णांक bnxt_set_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा ethtool_eee *eee = &bp->eee;
	काष्ठा bnxt_link_info *link_info = &bp->link_info;
	u32 advertising;
	पूर्णांक rc = 0;

	अगर (!BNXT_PHY_CFG_ABLE(bp))
		वापस -EOPNOTSUPP;

	अगर (!(bp->phy_flags & BNXT_PHY_FL_EEE_CAP))
		वापस -EOPNOTSUPP;

	mutex_lock(&bp->link_lock);
	advertising = _bnxt_fw_to_ethtool_adv_spds(link_info->advertising, 0);
	अगर (!edata->eee_enabled)
		जाओ eee_ok;

	अगर (!(link_info->स्वतःneg & BNXT_AUTONEG_SPEED)) अणु
		netdev_warn(dev, "EEE requires autoneg\n");
		rc = -EINVAL;
		जाओ eee_निकास;
	पूर्ण
	अगर (edata->tx_lpi_enabled) अणु
		अगर (bp->lpi_पंचांगr_hi && (edata->tx_lpi_समयr > bp->lpi_पंचांगr_hi ||
				       edata->tx_lpi_समयr < bp->lpi_पंचांगr_lo)) अणु
			netdev_warn(dev, "Valid LPI timer range is %d and %d microsecs\n",
				    bp->lpi_पंचांगr_lo, bp->lpi_पंचांगr_hi);
			rc = -EINVAL;
			जाओ eee_निकास;
		पूर्ण अन्यथा अगर (!bp->lpi_पंचांगr_hi) अणु
			edata->tx_lpi_समयr = eee->tx_lpi_समयr;
		पूर्ण
	पूर्ण
	अगर (!edata->advertised) अणु
		edata->advertised = advertising & eee->supported;
	पूर्ण अन्यथा अगर (edata->advertised & ~advertising) अणु
		netdev_warn(dev, "EEE advertised %x must be a subset of autoneg advertised speeds %x\n",
			    edata->advertised, advertising);
		rc = -EINVAL;
		जाओ eee_निकास;
	पूर्ण

	eee->advertised = edata->advertised;
	eee->tx_lpi_enabled = edata->tx_lpi_enabled;
	eee->tx_lpi_समयr = edata->tx_lpi_समयr;
eee_ok:
	eee->eee_enabled = edata->eee_enabled;

	अगर (netअगर_running(dev))
		rc = bnxt_hwrm_set_link_setting(bp, false, true);

eee_निकास:
	mutex_unlock(&bp->link_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_get_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (!(bp->phy_flags & BNXT_PHY_FL_EEE_CAP))
		वापस -EOPNOTSUPP;

	*edata = bp->eee;
	अगर (!bp->eee.eee_enabled) अणु
		/* Preserve tx_lpi_समयr so that the last value will be used
		 * by शेष when it is re-enabled.
		 */
		edata->advertised = 0;
		edata->tx_lpi_enabled = 0;
	पूर्ण

	अगर (!bp->eee.eee_active)
		edata->lp_advertised = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_पढ़ो_sfp_module_eeprom_info(काष्ठा bnxt *bp, u16 i2c_addr,
					    u16 page_number, u16 start_addr,
					    u16 data_length, u8 *buf)
अणु
	काष्ठा hwrm_port_phy_i2c_पढ़ो_input req = अणु0पूर्ण;
	काष्ठा hwrm_port_phy_i2c_पढ़ो_output *output = bp->hwrm_cmd_resp_addr;
	पूर्णांक rc, byte_offset = 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_I2C_READ, -1, -1);
	req.i2c_slave_addr = i2c_addr;
	req.page_number = cpu_to_le16(page_number);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	करो अणु
		u16 xfer_size;

		xfer_size = min_t(u16, data_length, BNXT_MAX_PHY_I2C_RESP_SIZE);
		data_length -= xfer_size;
		req.page_offset = cpu_to_le16(start_addr + byte_offset);
		req.data_length = xfer_size;
		req.enables = cpu_to_le32(start_addr + byte_offset ?
				 PORT_PHY_I2C_READ_REQ_ENABLES_PAGE_OFFSET : 0);
		mutex_lock(&bp->hwrm_cmd_lock);
		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
		अगर (!rc)
			स_नकल(buf + byte_offset, output->data, xfer_size);
		mutex_unlock(&bp->hwrm_cmd_lock);
		byte_offset += xfer_size;
	पूर्ण जबतक (!rc && data_length > 0);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_get_module_info(काष्ठा net_device *dev,
				काष्ठा ethtool_modinfo *modinfo)
अणु
	u8 data[SFF_DIAG_SUPPORT_OFFSET + 1];
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	/* No poपूर्णांक in going further अगर phy status indicates
	 * module is not inserted or अगर it is घातered करोwn or
	 * अगर it is of type 10GBase-T
	 */
	अगर (bp->link_info.module_status >
		PORT_PHY_QCFG_RESP_MODULE_STATUS_WARNINGMSG)
		वापस -EOPNOTSUPP;

	/* This feature is not supported in older firmware versions */
	अगर (bp->hwrm_spec_code < 0x10202)
		वापस -EOPNOTSUPP;

	rc = bnxt_पढ़ो_sfp_module_eeprom_info(bp, I2C_DEV_ADDR_A0, 0, 0,
					      SFF_DIAG_SUPPORT_OFFSET + 1,
					      data);
	अगर (!rc) अणु
		u8 module_id = data[0];
		u8 diag_supported = data[SFF_DIAG_SUPPORT_OFFSET];

		चयन (module_id) अणु
		हाल SFF_MODULE_ID_SFP:
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
			अगर (!diag_supported)
				modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
			अवरोध;
		हाल SFF_MODULE_ID_QSFP:
		हाल SFF_MODULE_ID_QSFP_PLUS:
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
			अवरोध;
		हाल SFF_MODULE_ID_QSFP28:
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
			अवरोध;
		शेष:
			rc = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_get_module_eeprom(काष्ठा net_device *dev,
				  काष्ठा ethtool_eeprom *eeprom,
				  u8 *data)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u16  start = eeprom->offset, length = eeprom->len;
	पूर्णांक rc = 0;

	स_रखो(data, 0, eeprom->len);

	/* Read A0 portion of the EEPROM */
	अगर (start < ETH_MODULE_SFF_8436_LEN) अणु
		अगर (start + eeprom->len > ETH_MODULE_SFF_8436_LEN)
			length = ETH_MODULE_SFF_8436_LEN - start;
		rc = bnxt_पढ़ो_sfp_module_eeprom_info(bp, I2C_DEV_ADDR_A0, 0,
						      start, length, data);
		अगर (rc)
			वापस rc;
		start += length;
		data += length;
		length = eeprom->len - length;
	पूर्ण

	/* Read A2 portion of the EEPROM */
	अगर (length) अणु
		start -= ETH_MODULE_SFF_8436_LEN;
		rc = bnxt_पढ़ो_sfp_module_eeprom_info(bp, I2C_DEV_ADDR_A2, 0,
						      start, length, data);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_nway_reset(काष्ठा net_device *dev)
अणु
	पूर्णांक rc = 0;

	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	अगर (!BNXT_PHY_CFG_ABLE(bp))
		वापस -EOPNOTSUPP;

	अगर (!(link_info->स्वतःneg & BNXT_AUTONEG_SPEED))
		वापस -EINVAL;

	अगर (netअगर_running(dev))
		rc = bnxt_hwrm_set_link_setting(bp, true, false);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_set_phys_id(काष्ठा net_device *dev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा hwrm_port_led_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_pf_info *pf = &bp->pf;
	काष्ठा bnxt_led_cfg *led_cfg;
	u8 led_state;
	__le16 duration;
	पूर्णांक i;

	अगर (!bp->num_leds || BNXT_VF(bp))
		वापस -EOPNOTSUPP;

	अगर (state == ETHTOOL_ID_ACTIVE) अणु
		led_state = PORT_LED_CFG_REQ_LED0_STATE_BLINKALT;
		duration = cpu_to_le16(500);
	पूर्ण अन्यथा अगर (state == ETHTOOL_ID_INACTIVE) अणु
		led_state = PORT_LED_CFG_REQ_LED1_STATE_DEFAULT;
		duration = cpu_to_le16(0);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_LED_CFG, -1, -1);
	req.port_id = cpu_to_le16(pf->port_id);
	req.num_leds = bp->num_leds;
	led_cfg = (काष्ठा bnxt_led_cfg *)&req.led0_id;
	क्रम (i = 0; i < bp->num_leds; i++, led_cfg++) अणु
		req.enables |= BNXT_LED_DFLT_ENABLES(i);
		led_cfg->led_id = bp->leds[i].led_id;
		led_cfg->led_state = led_state;
		led_cfg->led_blink_on = duration;
		led_cfg->led_blink_off = duration;
		led_cfg->led_group_id = bp->leds[i].led_group_id;
	पूर्ण
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_selftest_irq(काष्ठा bnxt *bp, u16 cmpl_ring)
अणु
	काष्ठा hwrm_selftest_irq_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_SELFTEST_IRQ, cmpl_ring, -1);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_test_irq(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		u16 cmpl_ring = bp->grp_info[i].cp_fw_ring_id;
		पूर्णांक rc;

		rc = bnxt_hwrm_selftest_irq(bp, cmpl_ring);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_mac_loopback(काष्ठा bnxt *bp, bool enable)
अणु
	काष्ठा hwrm_port_mac_cfg_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_MAC_CFG, -1, -1);

	req.enables = cpu_to_le32(PORT_MAC_CFG_REQ_ENABLES_LPBK);
	अगर (enable)
		req.lpbk = PORT_MAC_CFG_REQ_LPBK_LOCAL;
	अन्यथा
		req.lpbk = PORT_MAC_CFG_REQ_LPBK_NONE;
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_query_क्रमce_speeds(काष्ठा bnxt *bp, u16 *क्रमce_speeds)
अणु
	काष्ठा hwrm_port_phy_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_port_phy_qcaps_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		*क्रमce_speeds = le16_to_cpu(resp->supported_speeds_क्रमce_mode);

	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_disable_an_क्रम_lpbk(काष्ठा bnxt *bp,
				    काष्ठा hwrm_port_phy_cfg_input *req)
अणु
	काष्ठा bnxt_link_info *link_info = &bp->link_info;
	u16 fw_advertising;
	u16 fw_speed;
	पूर्णांक rc;

	अगर (!link_info->स्वतःneg ||
	    (bp->phy_flags & BNXT_PHY_FL_AN_PHY_LPBK))
		वापस 0;

	rc = bnxt_query_क्रमce_speeds(bp, &fw_advertising);
	अगर (rc)
		वापस rc;

	fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_1GB;
	अगर (bp->link_info.link_up)
		fw_speed = bp->link_info.link_speed;
	अन्यथा अगर (fw_advertising & BNXT_LINK_SPEED_MSK_10GB)
		fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_10GB;
	अन्यथा अगर (fw_advertising & BNXT_LINK_SPEED_MSK_25GB)
		fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_25GB;
	अन्यथा अगर (fw_advertising & BNXT_LINK_SPEED_MSK_40GB)
		fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_40GB;
	अन्यथा अगर (fw_advertising & BNXT_LINK_SPEED_MSK_50GB)
		fw_speed = PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_50GB;

	req->क्रमce_link_speed = cpu_to_le16(fw_speed);
	req->flags |= cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_FORCE |
				  PORT_PHY_CFG_REQ_FLAGS_RESET_PHY);
	rc = hwrm_send_message(bp, req, माप(*req), HWRM_CMD_TIMEOUT);
	req->flags = 0;
	req->क्रमce_link_speed = cpu_to_le16(0);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_phy_loopback(काष्ठा bnxt *bp, bool enable, bool ext)
अणु
	काष्ठा hwrm_port_phy_cfg_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);

	अगर (enable) अणु
		bnxt_disable_an_क्रम_lpbk(bp, &req);
		अगर (ext)
			req.lpbk = PORT_PHY_CFG_REQ_LPBK_EXTERNAL;
		अन्यथा
			req.lpbk = PORT_PHY_CFG_REQ_LPBK_LOCAL;
	पूर्ण अन्यथा अणु
		req.lpbk = PORT_PHY_CFG_REQ_LPBK_NONE;
	पूर्ण
	req.enables = cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_LPBK);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_rx_loopback(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr,
			    u32 raw_cons, पूर्णांक pkt_size)
अणु
	काष्ठा bnxt_napi *bnapi = cpr->bnapi;
	काष्ठा bnxt_rx_ring_info *rxr;
	काष्ठा bnxt_sw_rx_bd *rx_buf;
	काष्ठा rx_cmp *rxcmp;
	u16 cp_cons, cons;
	u8 *data;
	u32 len;
	पूर्णांक i;

	rxr = bnapi->rx_ring;
	cp_cons = RING_CMP(raw_cons);
	rxcmp = (काष्ठा rx_cmp *)
		&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];
	cons = rxcmp->rx_cmp_opaque;
	rx_buf = &rxr->rx_buf_ring[cons];
	data = rx_buf->data_ptr;
	len = le32_to_cpu(rxcmp->rx_cmp_len_flags_type) >> RX_CMP_LEN_SHIFT;
	अगर (len != pkt_size)
		वापस -EIO;
	i = ETH_ALEN;
	अगर (!ether_addr_equal(data + i, bnapi->bp->dev->dev_addr))
		वापस -EIO;
	i += ETH_ALEN;
	क्रम (  ; i < pkt_size; i++) अणु
		अगर (data[i] != (u8)(i & 0xff))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_poll_loopback(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr,
			      पूर्णांक pkt_size)
अणु
	काष्ठा tx_cmp *txcmp;
	पूर्णांक rc = -EIO;
	u32 raw_cons;
	u32 cons;
	पूर्णांक i;

	raw_cons = cpr->cp_raw_cons;
	क्रम (i = 0; i < 200; i++) अणु
		cons = RING_CMP(raw_cons);
		txcmp = &cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)];

		अगर (!TX_CMP_VALID(txcmp, raw_cons)) अणु
			udelay(5);
			जारी;
		पूर्ण

		/* The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();
		अगर (TX_CMP_TYPE(txcmp) == CMP_TYPE_RX_L2_CMP) अणु
			rc = bnxt_rx_loopback(bp, cpr, raw_cons, pkt_size);
			raw_cons = NEXT_RAW_CMP(raw_cons);
			raw_cons = NEXT_RAW_CMP(raw_cons);
			अवरोध;
		पूर्ण
		raw_cons = NEXT_RAW_CMP(raw_cons);
	पूर्ण
	cpr->cp_raw_cons = raw_cons;
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_run_loopback(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[0];
	काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[0];
	काष्ठा bnxt_cp_ring_info *cpr;
	पूर्णांक pkt_size, i = 0;
	काष्ठा sk_buff *skb;
	dma_addr_t map;
	u8 *data;
	पूर्णांक rc;

	cpr = &rxr->bnapi->cp_ring;
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		cpr = cpr->cp_ring_arr[BNXT_RX_HDL];
	pkt_size = min(bp->dev->mtu + ETH_HLEN, bp->rx_copy_thresh);
	skb = netdev_alloc_skb(bp->dev, pkt_size);
	अगर (!skb)
		वापस -ENOMEM;
	data = skb_put(skb, pkt_size);
	eth_broadcast_addr(data);
	i += ETH_ALEN;
	ether_addr_copy(&data[i], bp->dev->dev_addr);
	i += ETH_ALEN;
	क्रम ( ; i < pkt_size; i++)
		data[i] = (u8)(i & 0xff);

	map = dma_map_single(&bp->pdev->dev, skb->data, pkt_size,
			     PCI_DMA_TODEVICE);
	अगर (dma_mapping_error(&bp->pdev->dev, map)) अणु
		dev_kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण
	bnxt_xmit_bd(bp, txr, map, pkt_size);

	/* Sync BD data beक्रमe updating करोorbell */
	wmb();

	bnxt_db_ग_लिखो(bp, &txr->tx_db, txr->tx_prod);
	rc = bnxt_poll_loopback(bp, cpr, pkt_size);

	dma_unmap_single(&bp->pdev->dev, map, pkt_size, PCI_DMA_TODEVICE);
	dev_kमुक्त_skb(skb);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_run_fw_tests(काष्ठा bnxt *bp, u8 test_mask, u8 *test_results)
अणु
	काष्ठा hwrm_selftest_exec_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_selftest_exec_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_SELFTEST_EXEC, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	resp->test_success = 0;
	req.flags = test_mask;
	rc = _hwrm_send_message(bp, &req, माप(req), bp->test_info->समयout);
	*test_results = resp->test_success;
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

#घोषणा BNXT_DRV_TESTS			4
#घोषणा BNXT_MACLPBK_TEST_IDX		(bp->num_tests - BNXT_DRV_TESTS)
#घोषणा BNXT_PHYLPBK_TEST_IDX		(BNXT_MACLPBK_TEST_IDX + 1)
#घोषणा BNXT_EXTLPBK_TEST_IDX		(BNXT_MACLPBK_TEST_IDX + 2)
#घोषणा BNXT_IRQ_TEST_IDX		(BNXT_MACLPBK_TEST_IDX + 3)

अटल व्योम bnxt_self_test(काष्ठा net_device *dev, काष्ठा ethtool_test *etest,
			   u64 *buf)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	bool करो_ext_lpbk = false;
	bool offline = false;
	u8 test_results = 0;
	u8 test_mask = 0;
	पूर्णांक rc = 0, i;

	अगर (!bp->num_tests || !BNXT_PF(bp))
		वापस;
	स_रखो(buf, 0, माप(u64) * bp->num_tests);
	अगर (!netअगर_running(dev)) अणु
		etest->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण

	अगर ((etest->flags & ETH_TEST_FL_EXTERNAL_LB) &&
	    (bp->phy_flags & BNXT_PHY_FL_EXT_LPBK))
		करो_ext_lpbk = true;

	अगर (etest->flags & ETH_TEST_FL_OFFLINE) अणु
		अगर (bp->pf.active_vfs || !BNXT_SINGLE_PF(bp)) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			netdev_warn(dev, "Offline tests cannot be run with active VFs or on shared PF\n");
			वापस;
		पूर्ण
		offline = true;
	पूर्ण

	क्रम (i = 0; i < bp->num_tests - BNXT_DRV_TESTS; i++) अणु
		u8 bit_val = 1 << i;

		अगर (!(bp->test_info->offline_mask & bit_val))
			test_mask |= bit_val;
		अन्यथा अगर (offline)
			test_mask |= bit_val;
	पूर्ण
	अगर (!offline) अणु
		bnxt_run_fw_tests(bp, test_mask, &test_results);
	पूर्ण अन्यथा अणु
		rc = bnxt_बंद_nic(bp, false, false);
		अगर (rc)
			वापस;
		bnxt_run_fw_tests(bp, test_mask, &test_results);

		buf[BNXT_MACLPBK_TEST_IDX] = 1;
		bnxt_hwrm_mac_loopback(bp, true);
		msleep(250);
		rc = bnxt_half_खोलो_nic(bp);
		अगर (rc) अणु
			bnxt_hwrm_mac_loopback(bp, false);
			etest->flags |= ETH_TEST_FL_FAILED;
			वापस;
		पूर्ण
		अगर (bnxt_run_loopback(bp))
			etest->flags |= ETH_TEST_FL_FAILED;
		अन्यथा
			buf[BNXT_MACLPBK_TEST_IDX] = 0;

		bnxt_hwrm_mac_loopback(bp, false);
		bnxt_hwrm_phy_loopback(bp, true, false);
		msleep(1000);
		अगर (bnxt_run_loopback(bp)) अणु
			buf[BNXT_PHYLPBK_TEST_IDX] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		पूर्ण
		अगर (करो_ext_lpbk) अणु
			etest->flags |= ETH_TEST_FL_EXTERNAL_LB_DONE;
			bnxt_hwrm_phy_loopback(bp, true, true);
			msleep(1000);
			अगर (bnxt_run_loopback(bp)) अणु
				buf[BNXT_EXTLPBK_TEST_IDX] = 1;
				etest->flags |= ETH_TEST_FL_FAILED;
			पूर्ण
		पूर्ण
		bnxt_hwrm_phy_loopback(bp, false, false);
		bnxt_half_बंद_nic(bp);
		rc = bnxt_खोलो_nic(bp, false, true);
	पूर्ण
	अगर (rc || bnxt_test_irq(bp)) अणु
		buf[BNXT_IRQ_TEST_IDX] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण
	क्रम (i = 0; i < bp->num_tests - BNXT_DRV_TESTS; i++) अणु
		u8 bit_val = 1 << i;

		अगर ((test_mask & bit_val) && !(test_results & bit_val)) अणु
			buf[i] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_reset(काष्ठा net_device *dev, u32 *flags)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	bool reload = false;
	u32 req = *flags;

	अगर (!req)
		वापस -EINVAL;

	अगर (!BNXT_PF(bp)) अणु
		netdev_err(dev, "Reset is not supported from a VF\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (pci_vfs_asचिन्हित(bp->pdev) &&
	    !(bp->fw_cap & BNXT_FW_CAP_HOT_RESET)) अणु
		netdev_err(dev,
			   "Reset not allowed when VFs are assigned to VMs\n");
		वापस -EBUSY;
	पूर्ण

	अगर ((req & BNXT_FW_RESET_CHIP) == BNXT_FW_RESET_CHIP) अणु
		/* This feature is not supported in older firmware versions */
		अगर (bp->hwrm_spec_code >= 0x10803) अणु
			अगर (!bnxt_firmware_reset_chip(dev)) अणु
				netdev_info(dev, "Firmware reset request successful.\n");
				अगर (!(bp->fw_cap & BNXT_FW_CAP_HOT_RESET))
					reload = true;
				*flags &= ~BNXT_FW_RESET_CHIP;
			पूर्ण
		पूर्ण अन्यथा अगर (req == BNXT_FW_RESET_CHIP) अणु
			वापस -EOPNOTSUPP; /* only request, fail hard */
		पूर्ण
	पूर्ण

	अगर (req & BNXT_FW_RESET_AP) अणु
		/* This feature is not supported in older firmware versions */
		अगर (bp->hwrm_spec_code >= 0x10803) अणु
			अगर (!bnxt_firmware_reset_ap(dev)) अणु
				netdev_info(dev, "Reset application processor successful.\n");
				reload = true;
				*flags &= ~BNXT_FW_RESET_AP;
			पूर्ण
		पूर्ण अन्यथा अगर (req == BNXT_FW_RESET_AP) अणु
			वापस -EOPNOTSUPP; /* only request, fail hard */
		पूर्ण
	पूर्ण

	अगर (reload)
		netdev_info(dev, "Reload driver to complete reset\n");

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_dbg_dma_data(काष्ठा bnxt *bp, व्योम *msg, पूर्णांक msg_len,
				  काष्ठा bnxt_hwrm_dbg_dma_info *info)
अणु
	काष्ठा hwrm_dbg_cmn_output *cmn_resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_dbg_cmn_input *cmn_req = msg;
	__le16 *seq_ptr = msg + info->seq_off;
	u16 seq = 0, len, segs_off;
	व्योम *resp = cmn_resp;
	dma_addr_t dma_handle;
	पूर्णांक rc, off = 0;
	व्योम *dma_buf;

	dma_buf = dma_alloc_coherent(&bp->pdev->dev, info->dma_len, &dma_handle,
				     GFP_KERNEL);
	अगर (!dma_buf)
		वापस -ENOMEM;

	segs_off = दुरत्व(काष्ठा hwrm_dbg_coredump_list_output,
			    total_segments);
	cmn_req->host_dest_addr = cpu_to_le64(dma_handle);
	cmn_req->host_buf_len = cpu_to_le32(info->dma_len);
	mutex_lock(&bp->hwrm_cmd_lock);
	जबतक (1) अणु
		*seq_ptr = cpu_to_le16(seq);
		rc = _hwrm_send_message(bp, msg, msg_len,
					HWRM_COREDUMP_TIMEOUT);
		अगर (rc)
			अवरोध;

		len = le16_to_cpu(*((__le16 *)(resp + info->data_len_off)));
		अगर (!seq &&
		    cmn_req->req_type == cpu_to_le16(HWRM_DBG_COREDUMP_LIST)) अणु
			info->segs = le16_to_cpu(*((__le16 *)(resp +
							      segs_off)));
			अगर (!info->segs) अणु
				rc = -EIO;
				अवरोध;
			पूर्ण

			info->dest_buf_size = info->segs *
					माप(काष्ठा coredump_segment_record);
			info->dest_buf = kदो_स्मृति(info->dest_buf_size,
						 GFP_KERNEL);
			अगर (!info->dest_buf) अणु
				rc = -ENOMEM;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (info->dest_buf) अणु
			अगर ((info->seg_start + off + len) <=
			    BNXT_COREDUMP_BUF_LEN(info->buf_len)) अणु
				स_नकल(info->dest_buf + off, dma_buf, len);
			पूर्ण अन्यथा अणु
				rc = -ENOBUFS;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (cmn_req->req_type ==
				cpu_to_le16(HWRM_DBG_COREDUMP_RETRIEVE))
			info->dest_buf_size += len;

		अगर (!(cmn_resp->flags & HWRM_DBG_CMN_FLAGS_MORE))
			अवरोध;

		seq++;
		off += len;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	dma_मुक्त_coherent(&bp->pdev->dev, info->dma_len, dma_buf, dma_handle);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_dbg_coredump_list(काष्ठा bnxt *bp,
				       काष्ठा bnxt_coredump *coredump)
अणु
	काष्ठा hwrm_dbg_coredump_list_input req = अणु0पूर्ण;
	काष्ठा bnxt_hwrm_dbg_dma_info info = अणुशून्यपूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_DBG_COREDUMP_LIST, -1, -1);

	info.dma_len = COREDUMP_LIST_BUF_LEN;
	info.seq_off = दुरत्व(काष्ठा hwrm_dbg_coredump_list_input, seq_no);
	info.data_len_off = दुरत्व(काष्ठा hwrm_dbg_coredump_list_output,
				     data_len);

	rc = bnxt_hwrm_dbg_dma_data(bp, &req, माप(req), &info);
	अगर (!rc) अणु
		coredump->data = info.dest_buf;
		coredump->data_size = info.dest_buf_size;
		coredump->total_segs = info.segs;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_dbg_coredump_initiate(काष्ठा bnxt *bp, u16 component_id,
					   u16 segment_id)
अणु
	काष्ठा hwrm_dbg_coredump_initiate_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_DBG_COREDUMP_INITIATE, -1, -1);
	req.component_id = cpu_to_le16(component_id);
	req.segment_id = cpu_to_le16(segment_id);

	वापस hwrm_send_message(bp, &req, माप(req), HWRM_COREDUMP_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_dbg_coredump_retrieve(काष्ठा bnxt *bp, u16 component_id,
					   u16 segment_id, u32 *seg_len,
					   व्योम *buf, u32 buf_len, u32 offset)
अणु
	काष्ठा hwrm_dbg_coredump_retrieve_input req = अणु0पूर्ण;
	काष्ठा bnxt_hwrm_dbg_dma_info info = अणुशून्यपूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_DBG_COREDUMP_RETRIEVE, -1, -1);
	req.component_id = cpu_to_le16(component_id);
	req.segment_id = cpu_to_le16(segment_id);

	info.dma_len = COREDUMP_RETRIEVE_BUF_LEN;
	info.seq_off = दुरत्व(काष्ठा hwrm_dbg_coredump_retrieve_input,
				seq_no);
	info.data_len_off = दुरत्व(काष्ठा hwrm_dbg_coredump_retrieve_output,
				     data_len);
	अगर (buf) अणु
		info.dest_buf = buf + offset;
		info.buf_len = buf_len;
		info.seg_start = offset;
	पूर्ण

	rc = bnxt_hwrm_dbg_dma_data(bp, &req, माप(req), &info);
	अगर (!rc)
		*seg_len = info.dest_buf_size;

	वापस rc;
पूर्ण

अटल व्योम
bnxt_fill_coredump_seg_hdr(काष्ठा bnxt *bp,
			   काष्ठा bnxt_coredump_segment_hdr *seg_hdr,
			   काष्ठा coredump_segment_record *seg_rec, u32 seg_len,
			   पूर्णांक status, u32 duration, u32 instance)
अणु
	स_रखो(seg_hdr, 0, माप(*seg_hdr));
	स_नकल(seg_hdr->signature, "sEgM", 4);
	अगर (seg_rec) अणु
		seg_hdr->component_id = (__क्रमce __le32)seg_rec->component_id;
		seg_hdr->segment_id = (__क्रमce __le32)seg_rec->segment_id;
		seg_hdr->low_version = seg_rec->version_low;
		seg_hdr->high_version = seg_rec->version_hi;
	पूर्ण अन्यथा अणु
		/* For hwrm_ver_get response Component id = 2
		 * and Segment id = 0
		 */
		seg_hdr->component_id = cpu_to_le32(2);
		seg_hdr->segment_id = 0;
	पूर्ण
	seg_hdr->function_id = cpu_to_le16(bp->pdev->devfn);
	seg_hdr->length = cpu_to_le32(seg_len);
	seg_hdr->status = cpu_to_le32(status);
	seg_hdr->duration = cpu_to_le32(duration);
	seg_hdr->data_offset = cpu_to_le32(माप(*seg_hdr));
	seg_hdr->instance = cpu_to_le32(instance);
पूर्ण

अटल व्योम
bnxt_fill_coredump_record(काष्ठा bnxt *bp, काष्ठा bnxt_coredump_record *record,
			  समय64_t start, s16 start_utc, u16 total_segs,
			  पूर्णांक status)
अणु
	समय64_t end = kसमय_get_real_seconds();
	u32 os_ver_major = 0, os_ver_minor = 0;
	काष्ठा पंचांग पंचांग;

	समय64_to_पंचांग(start, 0, &पंचांग);
	स_रखो(record, 0, माप(*record));
	स_नकल(record->signature, "cOrE", 4);
	record->flags = 0;
	record->low_version = 0;
	record->high_version = 1;
	record->asic_state = 0;
	strlcpy(record->प्रणाली_name, utsname()->nodename,
		माप(record->प्रणाली_name));
	record->year = cpu_to_le16(पंचांग.पंचांग_year + 1900);
	record->month = cpu_to_le16(पंचांग.पंचांग_mon + 1);
	record->day = cpu_to_le16(पंचांग.पंचांग_mday);
	record->hour = cpu_to_le16(पंचांग.पंचांग_hour);
	record->minute = cpu_to_le16(पंचांग.पंचांग_min);
	record->second = cpu_to_le16(पंचांग.पंचांग_sec);
	record->utc_bias = cpu_to_le16(start_utc);
	म_नकल(record->commandline, "ethtool -w");
	record->total_segments = cpu_to_le32(total_segs);

	माला_पूछो(utsname()->release, "%u.%u", &os_ver_major, &os_ver_minor);
	record->os_ver_major = cpu_to_le32(os_ver_major);
	record->os_ver_minor = cpu_to_le32(os_ver_minor);

	strlcpy(record->os_name, utsname()->sysname, 32);
	समय64_to_पंचांग(end, 0, &पंचांग);
	record->end_year = cpu_to_le16(पंचांग.पंचांग_year + 1900);
	record->end_month = cpu_to_le16(पंचांग.पंचांग_mon + 1);
	record->end_day = cpu_to_le16(पंचांग.पंचांग_mday);
	record->end_hour = cpu_to_le16(पंचांग.पंचांग_hour);
	record->end_minute = cpu_to_le16(पंचांग.पंचांग_min);
	record->end_second = cpu_to_le16(पंचांग.पंचांग_sec);
	record->end_utc_bias = cpu_to_le16(sys_tz.tz_minuteswest * 60);
	record->asic_id1 = cpu_to_le32(bp->chip_num << 16 |
				       bp->ver_resp.chip_rev << 8 |
				       bp->ver_resp.chip_metal);
	record->asic_id2 = 0;
	record->coredump_status = cpu_to_le32(status);
	record->ioctl_low_version = 0;
	record->ioctl_high_version = 0;
पूर्ण

अटल पूर्णांक bnxt_get_coredump(काष्ठा bnxt *bp, व्योम *buf, u32 *dump_len)
अणु
	u32 ver_get_resp_len = माप(काष्ठा hwrm_ver_get_output);
	u32 offset = 0, seg_hdr_len, seg_record_len, buf_len = 0;
	काष्ठा coredump_segment_record *seg_record = शून्य;
	काष्ठा bnxt_coredump_segment_hdr seg_hdr;
	काष्ठा bnxt_coredump coredump = अणुशून्यपूर्ण;
	समय64_t start_समय;
	u16 start_utc;
	पूर्णांक rc = 0, i;

	अगर (buf)
		buf_len = *dump_len;

	start_समय = kसमय_get_real_seconds();
	start_utc = sys_tz.tz_minuteswest * 60;
	seg_hdr_len = माप(seg_hdr);

	/* First segment should be hwrm_ver_get response */
	*dump_len = seg_hdr_len + ver_get_resp_len;
	अगर (buf) अणु
		bnxt_fill_coredump_seg_hdr(bp, &seg_hdr, शून्य, ver_get_resp_len,
					   0, 0, 0);
		स_नकल(buf + offset, &seg_hdr, seg_hdr_len);
		offset += seg_hdr_len;
		स_नकल(buf + offset, &bp->ver_resp, ver_get_resp_len);
		offset += ver_get_resp_len;
	पूर्ण

	rc = bnxt_hwrm_dbg_coredump_list(bp, &coredump);
	अगर (rc) अणु
		netdev_err(bp->dev, "Failed to get coredump segment list\n");
		जाओ err;
	पूर्ण

	*dump_len += seg_hdr_len * coredump.total_segs;

	seg_record = (काष्ठा coredump_segment_record *)coredump.data;
	seg_record_len = माप(*seg_record);

	क्रम (i = 0; i < coredump.total_segs; i++) अणु
		u16 comp_id = le16_to_cpu(seg_record->component_id);
		u16 seg_id = le16_to_cpu(seg_record->segment_id);
		u32 duration = 0, seg_len = 0;
		अचिन्हित दीर्घ start, end;

		अगर (buf && ((offset + seg_hdr_len) >
			    BNXT_COREDUMP_BUF_LEN(buf_len))) अणु
			rc = -ENOBUFS;
			जाओ err;
		पूर्ण

		start = jअगरfies;

		rc = bnxt_hwrm_dbg_coredump_initiate(bp, comp_id, seg_id);
		अगर (rc) अणु
			netdev_err(bp->dev,
				   "Failed to initiate coredump for seg = %d\n",
				   seg_record->segment_id);
			जाओ next_seg;
		पूर्ण

		/* Write segment data पूर्णांकo the buffer */
		rc = bnxt_hwrm_dbg_coredump_retrieve(bp, comp_id, seg_id,
						     &seg_len, buf, buf_len,
						     offset + seg_hdr_len);
		अगर (rc && rc == -ENOBUFS)
			जाओ err;
		अन्यथा अगर (rc)
			netdev_err(bp->dev,
				   "Failed to retrieve coredump for seg = %d\n",
				   seg_record->segment_id);

next_seg:
		end = jअगरfies;
		duration = jअगरfies_to_msecs(end - start);
		bnxt_fill_coredump_seg_hdr(bp, &seg_hdr, seg_record, seg_len,
					   rc, duration, 0);

		अगर (buf) अणु
			/* Write segment header पूर्णांकo the buffer */
			स_नकल(buf + offset, &seg_hdr, seg_hdr_len);
			offset += seg_hdr_len + seg_len;
		पूर्ण

		*dump_len += seg_len;
		seg_record =
			(काष्ठा coredump_segment_record *)((u8 *)seg_record +
							   seg_record_len);
	पूर्ण

err:
	अगर (buf)
		bnxt_fill_coredump_record(bp, buf + offset, start_समय,
					  start_utc, coredump.total_segs + 1,
					  rc);
	kमुक्त(coredump.data);
	*dump_len += माप(काष्ठा bnxt_coredump_record);
	अगर (rc == -ENOBUFS)
		netdev_err(bp->dev, "Firmware returned large coredump buffer\n");
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_set_dump(काष्ठा net_device *dev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (dump->flag > BNXT_DUMP_CRASH) अणु
		netdev_info(dev, "Supports only Live(0) and Crash(1) dumps.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_TEE_BNXT_FW) && dump->flag == BNXT_DUMP_CRASH) अणु
		netdev_info(dev, "Cannot collect crash dump as TEE_BNXT_FW config option is not enabled.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	bp->dump_flag = dump->flag;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_get_dump_flag(काष्ठा net_device *dev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (bp->hwrm_spec_code < 0x10801)
		वापस -EOPNOTSUPP;

	dump->version = bp->ver_resp.hwrm_fw_maj_8b << 24 |
			bp->ver_resp.hwrm_fw_min_8b << 16 |
			bp->ver_resp.hwrm_fw_bld_8b << 8 |
			bp->ver_resp.hwrm_fw_rsvd_8b;

	dump->flag = bp->dump_flag;
	अगर (bp->dump_flag == BNXT_DUMP_CRASH)
		dump->len = BNXT_CRASH_DUMP_LEN;
	अन्यथा
		bnxt_get_coredump(bp, शून्य, &dump->len);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_get_dump_data(काष्ठा net_device *dev, काष्ठा ethtool_dump *dump,
			      व्योम *buf)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (bp->hwrm_spec_code < 0x10801)
		वापस -EOPNOTSUPP;

	स_रखो(buf, 0, dump->len);

	dump->flag = bp->dump_flag;
	अगर (dump->flag == BNXT_DUMP_CRASH) अणु
#अगर_घोषित CONFIG_TEE_BNXT_FW
		वापस tee_bnxt_copy_coredump(buf, 0, dump->len);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस bnxt_get_coredump(bp, buf, &dump->len);
	पूर्ण

	वापस 0;
पूर्ण

व्योम bnxt_ethtool_init(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_selftest_qlist_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_selftest_qlist_input req = अणु0पूर्ण;
	काष्ठा bnxt_test_info *test_info;
	काष्ठा net_device *dev = bp->dev;
	पूर्णांक i, rc;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_PKG_VER))
		bnxt_get_pkgver(dev);

	bp->num_tests = 0;
	अगर (bp->hwrm_spec_code < 0x10704 || !BNXT_PF(bp))
		वापस;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_SELFTEST_QLIST, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ ethtool_init_निकास;

	test_info = bp->test_info;
	अगर (!test_info)
		test_info = kzalloc(माप(*bp->test_info), GFP_KERNEL);
	अगर (!test_info)
		जाओ ethtool_init_निकास;

	bp->test_info = test_info;
	bp->num_tests = resp->num_tests + BNXT_DRV_TESTS;
	अगर (bp->num_tests > BNXT_MAX_TEST)
		bp->num_tests = BNXT_MAX_TEST;

	test_info->offline_mask = resp->offline_tests;
	test_info->समयout = le16_to_cpu(resp->test_समयout);
	अगर (!test_info->समयout)
		test_info->समयout = HWRM_CMD_TIMEOUT;
	क्रम (i = 0; i < bp->num_tests; i++) अणु
		अक्षर *str = test_info->string[i];
		अक्षर *fw_str = resp->test0_name + i * 32;

		अगर (i == BNXT_MACLPBK_TEST_IDX) अणु
			म_नकल(str, "Mac loopback test (offline)");
		पूर्ण अन्यथा अगर (i == BNXT_PHYLPBK_TEST_IDX) अणु
			म_नकल(str, "Phy loopback test (offline)");
		पूर्ण अन्यथा अगर (i == BNXT_EXTLPBK_TEST_IDX) अणु
			म_नकल(str, "Ext loopback test (offline)");
		पूर्ण अन्यथा अगर (i == BNXT_IRQ_TEST_IDX) अणु
			म_नकल(str, "Interrupt_test (offline)");
		पूर्ण अन्यथा अणु
			strlcpy(str, fw_str, ETH_GSTRING_LEN);
			म_जोड़न(str, " test", ETH_GSTRING_LEN - म_माप(str));
			अगर (test_info->offline_mask & (1 << i))
				म_जोड़न(str, " (offline)",
					ETH_GSTRING_LEN - म_माप(str));
			अन्यथा
				म_जोड़न(str, " (online)",
					ETH_GSTRING_LEN - म_माप(str));
		पूर्ण
	पूर्ण

ethtool_init_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
पूर्ण

अटल व्योम bnxt_get_eth_phy_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_eth_phy_stats *phy_stats)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u64 *rx;

	अगर (BNXT_VF(bp) || !(bp->flags & BNXT_FLAG_PORT_STATS_EXT))
		वापस;

	rx = bp->rx_port_stats_ext.sw_stats;
	phy_stats->SymbolErrorDuringCarrier =
		*(rx + BNXT_RX_STATS_EXT_OFFSET(rx_pcs_symbol_err));
पूर्ण

अटल व्योम bnxt_get_eth_mac_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_eth_mac_stats *mac_stats)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u64 *rx, *tx;

	अगर (BNXT_VF(bp) || !(bp->flags & BNXT_FLAG_PORT_STATS))
		वापस;

	rx = bp->port_stats.sw_stats;
	tx = bp->port_stats.sw_stats + BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;

	mac_stats->FramesReceivedOK =
		BNXT_GET_RX_PORT_STATS64(rx, rx_good_frames);
	mac_stats->FramesTransmittedOK =
		BNXT_GET_TX_PORT_STATS64(tx, tx_good_frames);
	mac_stats->FrameCheckSequenceErrors =
		BNXT_GET_RX_PORT_STATS64(rx, rx_fcs_err_frames);
	mac_stats->AlignmentErrors =
		BNXT_GET_RX_PORT_STATS64(rx, rx_align_err_frames);
	mac_stats->OutOfRangeLengthField =
		BNXT_GET_RX_PORT_STATS64(rx, rx_oor_len_frames);
पूर्ण

अटल व्योम bnxt_get_eth_ctrl_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_eth_ctrl_stats *ctrl_stats)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u64 *rx;

	अगर (BNXT_VF(bp) || !(bp->flags & BNXT_FLAG_PORT_STATS))
		वापस;

	rx = bp->port_stats.sw_stats;
	ctrl_stats->MACControlFramesReceived =
		BNXT_GET_RX_PORT_STATS64(rx, rx_ctrl_frames);
पूर्ण

अटल स्थिर काष्ठा ethtool_rmon_hist_range bnxt_rmon_ranges[] = अणु
	अणु    0,    64 पूर्ण,
	अणु   65,   127 पूर्ण,
	अणु  128,   255 पूर्ण,
	अणु  256,   511 पूर्ण,
	अणु  512,  1023 पूर्ण,
	अणु 1024,  1518 पूर्ण,
	अणु 1519,  2047 पूर्ण,
	अणु 2048,  4095 पूर्ण,
	अणु 4096,  9216 पूर्ण,
	अणु 9217, 16383 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम bnxt_get_rmon_stats(काष्ठा net_device *dev,
				काष्ठा ethtool_rmon_stats *rmon_stats,
				स्थिर काष्ठा ethtool_rmon_hist_range **ranges)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u64 *rx, *tx;

	अगर (BNXT_VF(bp) || !(bp->flags & BNXT_FLAG_PORT_STATS))
		वापस;

	rx = bp->port_stats.sw_stats;
	tx = bp->port_stats.sw_stats + BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;

	rmon_stats->jabbers =
		BNXT_GET_RX_PORT_STATS64(rx, rx_jbr_frames);
	rmon_stats->oversize_pkts =
		BNXT_GET_RX_PORT_STATS64(rx, rx_ovrsz_frames);
	rmon_stats->undersize_pkts =
		BNXT_GET_RX_PORT_STATS64(rx, rx_undrsz_frames);

	rmon_stats->hist[0] = BNXT_GET_RX_PORT_STATS64(rx, rx_64b_frames);
	rmon_stats->hist[1] = BNXT_GET_RX_PORT_STATS64(rx, rx_65b_127b_frames);
	rmon_stats->hist[2] = BNXT_GET_RX_PORT_STATS64(rx, rx_128b_255b_frames);
	rmon_stats->hist[3] = BNXT_GET_RX_PORT_STATS64(rx, rx_256b_511b_frames);
	rmon_stats->hist[4] =
		BNXT_GET_RX_PORT_STATS64(rx, rx_512b_1023b_frames);
	rmon_stats->hist[5] =
		BNXT_GET_RX_PORT_STATS64(rx, rx_1024b_1518b_frames);
	rmon_stats->hist[6] =
		BNXT_GET_RX_PORT_STATS64(rx, rx_1519b_2047b_frames);
	rmon_stats->hist[7] =
		BNXT_GET_RX_PORT_STATS64(rx, rx_2048b_4095b_frames);
	rmon_stats->hist[8] =
		BNXT_GET_RX_PORT_STATS64(rx, rx_4096b_9216b_frames);
	rmon_stats->hist[9] =
		BNXT_GET_RX_PORT_STATS64(rx, rx_9217b_16383b_frames);

	rmon_stats->hist_tx[0] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_64b_frames);
	rmon_stats->hist_tx[1] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_65b_127b_frames);
	rmon_stats->hist_tx[2] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_128b_255b_frames);
	rmon_stats->hist_tx[3] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_256b_511b_frames);
	rmon_stats->hist_tx[4] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_512b_1023b_frames);
	rmon_stats->hist_tx[5] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_1024b_1518b_frames);
	rmon_stats->hist_tx[6] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_1519b_2047b_frames);
	rmon_stats->hist_tx[7] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_2048b_4095b_frames);
	rmon_stats->hist_tx[8] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_4096b_9216b_frames);
	rmon_stats->hist_tx[9] =
		BNXT_GET_TX_PORT_STATS64(tx, tx_9217b_16383b_frames);

	*ranges = bnxt_rmon_ranges;
पूर्ण

व्योम bnxt_ethtool_मुक्त(काष्ठा bnxt *bp)
अणु
	kमुक्त(bp->test_info);
	bp->test_info = शून्य;
पूर्ण

स्थिर काष्ठा ethtool_ops bnxt_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USECS_IRQ |
				     ETHTOOL_COALESCE_MAX_FRAMES_IRQ |
				     ETHTOOL_COALESCE_STATS_BLOCK_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_link_ksettings	= bnxt_get_link_ksettings,
	.set_link_ksettings	= bnxt_set_link_ksettings,
	.get_fec_stats		= bnxt_get_fec_stats,
	.get_fecparam		= bnxt_get_fecparam,
	.set_fecparam		= bnxt_set_fecparam,
	.get_छोड़ो_stats	= bnxt_get_छोड़ो_stats,
	.get_छोड़ोparam		= bnxt_get_छोड़ोparam,
	.set_छोड़ोparam		= bnxt_set_छोड़ोparam,
	.get_drvinfo		= bnxt_get_drvinfo,
	.get_regs_len		= bnxt_get_regs_len,
	.get_regs		= bnxt_get_regs,
	.get_wol		= bnxt_get_wol,
	.set_wol		= bnxt_set_wol,
	.get_coalesce		= bnxt_get_coalesce,
	.set_coalesce		= bnxt_set_coalesce,
	.get_msglevel		= bnxt_get_msglevel,
	.set_msglevel		= bnxt_set_msglevel,
	.get_sset_count		= bnxt_get_sset_count,
	.get_strings		= bnxt_get_strings,
	.get_ethtool_stats	= bnxt_get_ethtool_stats,
	.set_ringparam		= bnxt_set_ringparam,
	.get_ringparam		= bnxt_get_ringparam,
	.get_channels		= bnxt_get_channels,
	.set_channels		= bnxt_set_channels,
	.get_rxnfc		= bnxt_get_rxnfc,
	.set_rxnfc		= bnxt_set_rxnfc,
	.get_rxfh_indir_size    = bnxt_get_rxfh_indir_size,
	.get_rxfh_key_size      = bnxt_get_rxfh_key_size,
	.get_rxfh               = bnxt_get_rxfh,
	.set_rxfh		= bnxt_set_rxfh,
	.flash_device		= bnxt_flash_device,
	.get_eeprom_len         = bnxt_get_eeprom_len,
	.get_eeprom             = bnxt_get_eeprom,
	.set_eeprom		= bnxt_set_eeprom,
	.get_link		= bnxt_get_link,
	.get_eee		= bnxt_get_eee,
	.set_eee		= bnxt_set_eee,
	.get_module_info	= bnxt_get_module_info,
	.get_module_eeprom	= bnxt_get_module_eeprom,
	.nway_reset		= bnxt_nway_reset,
	.set_phys_id		= bnxt_set_phys_id,
	.self_test		= bnxt_self_test,
	.reset			= bnxt_reset,
	.set_dump		= bnxt_set_dump,
	.get_dump_flag		= bnxt_get_dump_flag,
	.get_dump_data		= bnxt_get_dump_data,
	.get_eth_phy_stats	= bnxt_get_eth_phy_stats,
	.get_eth_mac_stats	= bnxt_get_eth_mac_stats,
	.get_eth_ctrl_stats	= bnxt_get_eth_ctrl_stats,
	.get_rmon_stats		= bnxt_get_rmon_stats,
पूर्ण;
