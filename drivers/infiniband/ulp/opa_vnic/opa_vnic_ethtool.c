<शैली गुरु>
/*
 * Copyright(c) 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains OPA VNIC ethtool functions
 */

#समावेश <linux/ethtool.h>

#समावेश "opa_vnic_internal.h"

क्रमागत अणुNETDEV_STATS, VNIC_STATSपूर्ण;

काष्ठा vnic_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	काष्ठा अणु
		पूर्णांक माप_stat;
		पूर्णांक stat_offset;
	पूर्ण;
पूर्ण;

#घोषणा VNIC_STAT(m)            अणु माप_field(काष्ठा opa_vnic_stats, m),   \
				  दुरत्व(काष्ठा opa_vnic_stats, m) पूर्ण

अटल काष्ठा vnic_stats vnic_gstrings_stats[] = अणु
	/* NETDEV stats */
	अणु"rx_packets", VNIC_STAT(netstats.rx_packets)पूर्ण,
	अणु"tx_packets", VNIC_STAT(netstats.tx_packets)पूर्ण,
	अणु"rx_bytes", VNIC_STAT(netstats.rx_bytes)पूर्ण,
	अणु"tx_bytes", VNIC_STAT(netstats.tx_bytes)पूर्ण,
	अणु"rx_errors", VNIC_STAT(netstats.rx_errors)पूर्ण,
	अणु"tx_errors", VNIC_STAT(netstats.tx_errors)पूर्ण,
	अणु"rx_dropped", VNIC_STAT(netstats.rx_dropped)पूर्ण,
	अणु"tx_dropped", VNIC_STAT(netstats.tx_dropped)पूर्ण,

	/* SUMMARY counters */
	अणु"tx_unicast", VNIC_STAT(tx_grp.unicast)पूर्ण,
	अणु"tx_mcastbcast", VNIC_STAT(tx_grp.mcastbcast)पूर्ण,
	अणु"tx_untagged", VNIC_STAT(tx_grp.untagged)पूर्ण,
	अणु"tx_vlan", VNIC_STAT(tx_grp.vlan)पूर्ण,

	अणु"tx_64_size", VNIC_STAT(tx_grp.s_64)पूर्ण,
	अणु"tx_65_127", VNIC_STAT(tx_grp.s_65_127)पूर्ण,
	अणु"tx_128_255", VNIC_STAT(tx_grp.s_128_255)पूर्ण,
	अणु"tx_256_511", VNIC_STAT(tx_grp.s_256_511)पूर्ण,
	अणु"tx_512_1023", VNIC_STAT(tx_grp.s_512_1023)पूर्ण,
	अणु"tx_1024_1518", VNIC_STAT(tx_grp.s_1024_1518)पूर्ण,
	अणु"tx_1519_max", VNIC_STAT(tx_grp.s_1519_max)पूर्ण,

	अणु"rx_unicast", VNIC_STAT(rx_grp.unicast)पूर्ण,
	अणु"rx_mcastbcast", VNIC_STAT(rx_grp.mcastbcast)पूर्ण,
	अणु"rx_untagged", VNIC_STAT(rx_grp.untagged)पूर्ण,
	अणु"rx_vlan", VNIC_STAT(rx_grp.vlan)पूर्ण,

	अणु"rx_64_size", VNIC_STAT(rx_grp.s_64)पूर्ण,
	अणु"rx_65_127", VNIC_STAT(rx_grp.s_65_127)पूर्ण,
	अणु"rx_128_255", VNIC_STAT(rx_grp.s_128_255)पूर्ण,
	अणु"rx_256_511", VNIC_STAT(rx_grp.s_256_511)पूर्ण,
	अणु"rx_512_1023", VNIC_STAT(rx_grp.s_512_1023)पूर्ण,
	अणु"rx_1024_1518", VNIC_STAT(rx_grp.s_1024_1518)पूर्ण,
	अणु"rx_1519_max", VNIC_STAT(rx_grp.s_1519_max)पूर्ण,

	/* ERROR counters */
	अणु"rx_fifo_errors", VNIC_STAT(netstats.rx_fअगरo_errors)पूर्ण,
	अणु"rx_length_errors", VNIC_STAT(netstats.rx_length_errors)पूर्ण,

	अणु"tx_fifo_errors", VNIC_STAT(netstats.tx_fअगरo_errors)पूर्ण,
	अणु"tx_carrier_errors", VNIC_STAT(netstats.tx_carrier_errors)पूर्ण,

	अणु"tx_dlid_zero", VNIC_STAT(tx_dlid_zero)पूर्ण,
	अणु"tx_drop_state", VNIC_STAT(tx_drop_state)पूर्ण,
	अणु"rx_drop_state", VNIC_STAT(rx_drop_state)पूर्ण,
	अणु"rx_oversize", VNIC_STAT(rx_oversize)पूर्ण,
	अणु"rx_runt", VNIC_STAT(rx_runt)पूर्ण,
पूर्ण;

#घोषणा VNIC_STATS_LEN  ARRAY_SIZE(vnic_gstrings_stats)

/* vnic_get_drvinfo - get driver info */
अटल व्योम vnic_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, opa_vnic_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, dev_name(netdev->dev.parent),
		माप(drvinfo->bus_info));
पूर्ण

/* vnic_get_sset_count - get string set count */
अटल पूर्णांक vnic_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	वापस (sset == ETH_SS_STATS) ? VNIC_STATS_LEN : -EOPNOTSUPP;
पूर्ण

/* vnic_get_ethtool_stats - get statistics */
अटल व्योम vnic_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	काष्ठा opa_vnic_stats vstats;
	पूर्णांक i;

	स_रखो(&vstats, 0, माप(vstats));
	spin_lock(&adapter->stats_lock);
	adapter->rn_ops->nकरो_get_stats64(netdev, &vstats.netstats);
	spin_unlock(&adapter->stats_lock);
	क्रम (i = 0; i < VNIC_STATS_LEN; i++) अणु
		अक्षर *p = (अक्षर *)&vstats + vnic_gstrings_stats[i].stat_offset;

		data[i] = (vnic_gstrings_stats[i].माप_stat ==
			   माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
पूर्ण

/* vnic_get_strings - get strings */
अटल व्योम vnic_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < VNIC_STATS_LEN; i++)
		स_नकल(data + i * ETH_GSTRING_LEN,
		       vnic_gstrings_stats[i].stat_string,
		       ETH_GSTRING_LEN);
पूर्ण

/* ethtool ops */
अटल स्थिर काष्ठा ethtool_ops opa_vnic_ethtool_ops = अणु
	.get_drvinfo = vnic_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_strings = vnic_get_strings,
	.get_sset_count = vnic_get_sset_count,
	.get_ethtool_stats = vnic_get_ethtool_stats,
पूर्ण;

/* opa_vnic_set_ethtool_ops - set ethtool ops */
व्योम opa_vnic_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &opa_vnic_ethtool_ops;
पूर्ण
