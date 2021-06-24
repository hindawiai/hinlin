<शैली गुरु>
/* Copyright 2008-2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/माला.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/fsl/ptp_qoriq.h>

#समावेश "dpaa_eth.h"
#समावेश "mac.h"

अटल स्थिर अक्षर dpaa_stats_percpu[][ETH_GSTRING_LEN] = अणु
	"interrupts",
	"rx packets",
	"tx packets",
	"tx confirm",
	"tx S/G",
	"tx error",
	"rx error",
	"rx dropped",
	"tx dropped",
पूर्ण;

अटल अक्षर dpaa_stats_global[][ETH_GSTRING_LEN] = अणु
	/* dpa rx errors */
	"rx dma error",
	"rx frame physical error",
	"rx frame size error",
	"rx header error",

	/* demultiplexing errors */
	"qman cg_tdrop",
	"qman wred",
	"qman error cond",
	"qman early window",
	"qman late window",
	"qman fq tdrop",
	"qman fq retired",
	"qman orp disabled",

	/* congestion related stats */
	"congestion time (ms)",
	"entered congestion",
	"congested (0/1)"
पूर्ण;

#घोषणा DPAA_STATS_PERCPU_LEN ARRAY_SIZE(dpaa_stats_percpu)
#घोषणा DPAA_STATS_GLOBAL_LEN ARRAY_SIZE(dpaa_stats_global)

अटल पूर्णांक dpaa_get_link_ksettings(काष्ठा net_device *net_dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!net_dev->phydev)
		वापस 0;

	phy_ethtool_ksettings_get(net_dev->phydev, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_set_link_ksettings(काष्ठा net_device *net_dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	पूर्णांक err;

	अगर (!net_dev->phydev)
		वापस -ENODEV;

	err = phy_ethtool_ksettings_set(net_dev->phydev, cmd);
	अगर (err < 0)
		netdev_err(net_dev, "phy_ethtool_ksettings_set() = %d\n", err);

	वापस err;
पूर्ण

अटल व्योम dpaa_get_drvinfo(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, KBUILD_MODNAME,
		माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, dev_name(net_dev->dev.parent->parent),
		माप(drvinfo->bus_info));
पूर्ण

अटल u32 dpaa_get_msglevel(काष्ठा net_device *net_dev)
अणु
	वापस ((काष्ठा dpaa_priv *)netdev_priv(net_dev))->msg_enable;
पूर्ण

अटल व्योम dpaa_set_msglevel(काष्ठा net_device *net_dev,
			      u32 msg_enable)
अणु
	((काष्ठा dpaa_priv *)netdev_priv(net_dev))->msg_enable = msg_enable;
पूर्ण

अटल पूर्णांक dpaa_nway_reset(काष्ठा net_device *net_dev)
अणु
	पूर्णांक err;

	अगर (!net_dev->phydev)
		वापस -ENODEV;

	err = 0;
	अगर (net_dev->phydev->स्वतःneg) अणु
		err = phy_start_aneg(net_dev->phydev);
		अगर (err < 0)
			netdev_err(net_dev, "phy_start_aneg() = %d\n",
				   err);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम dpaa_get_छोड़ोparam(काष्ठा net_device *net_dev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा mac_device *mac_dev;
	काष्ठा dpaa_priv *priv;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	अगर (!net_dev->phydev)
		वापस;

	eछोड़ो->स्वतःneg = mac_dev->स्वतःneg_छोड़ो;
	eछोड़ो->rx_छोड़ो = mac_dev->rx_छोड़ो_active;
	eछोड़ो->tx_छोड़ो = mac_dev->tx_छोड़ो_active;
पूर्ण

अटल पूर्णांक dpaa_set_छोड़ोparam(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा mac_device *mac_dev;
	काष्ठा phy_device *phydev;
	bool rx_छोड़ो, tx_छोड़ो;
	काष्ठा dpaa_priv *priv;
	पूर्णांक err;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	phydev = net_dev->phydev;
	अगर (!phydev) अणु
		netdev_err(net_dev, "phy device not initialized\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!phy_validate_छोड़ो(phydev, eछोड़ो))
		वापस -EINVAL;

	/* The MAC should know how to handle PAUSE frame स्वतःnegotiation beक्रमe
	 * adjust_link is triggered by a क्रमced renegotiation of sym/asym PAUSE
	 * settings.
	 */
	mac_dev->स्वतःneg_छोड़ो = !!eछोड़ो->स्वतःneg;
	mac_dev->rx_छोड़ो_req = !!eछोड़ो->rx_छोड़ो;
	mac_dev->tx_छोड़ो_req = !!eछोड़ो->tx_छोड़ो;

	/* Determine the sym/asym advertised PAUSE capabilities from the desired
	 * rx/tx छोड़ो settings.
	 */

	phy_set_asym_छोड़ो(phydev, eछोड़ो->rx_छोड़ो, eछोड़ो->tx_छोड़ो);

	fman_get_छोड़ो_cfg(mac_dev, &rx_छोड़ो, &tx_छोड़ो);
	err = fman_set_mac_active_छोड़ो(mac_dev, rx_छोड़ो, tx_छोड़ो);
	अगर (err < 0)
		netdev_err(net_dev, "set_mac_active_pause() = %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_get_sset_count(काष्ठा net_device *net_dev, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक total_stats, num_stats;

	num_stats   = num_online_cpus() + 1;
	total_stats = num_stats * (DPAA_STATS_PERCPU_LEN + 1) +
			DPAA_STATS_GLOBAL_LEN;

	चयन (type) अणु
	हाल ETH_SS_STATS:
		वापस total_stats;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम copy_stats(काष्ठा dpaa_percpu_priv *percpu_priv, पूर्णांक num_cpus,
		       पूर्णांक crr_cpu, u64 bp_count, u64 *data)
अणु
	पूर्णांक num_values = num_cpus + 1;
	पूर्णांक crr = 0;

	/* update current CPU's stats and also add them to the total values */
	data[crr * num_values + crr_cpu] = percpu_priv->in_पूर्णांकerrupt;
	data[crr++ * num_values + num_cpus] += percpu_priv->in_पूर्णांकerrupt;

	data[crr * num_values + crr_cpu] = percpu_priv->stats.rx_packets;
	data[crr++ * num_values + num_cpus] += percpu_priv->stats.rx_packets;

	data[crr * num_values + crr_cpu] = percpu_priv->stats.tx_packets;
	data[crr++ * num_values + num_cpus] += percpu_priv->stats.tx_packets;

	data[crr * num_values + crr_cpu] = percpu_priv->tx_confirm;
	data[crr++ * num_values + num_cpus] += percpu_priv->tx_confirm;

	data[crr * num_values + crr_cpu] = percpu_priv->tx_frag_skbuffs;
	data[crr++ * num_values + num_cpus] += percpu_priv->tx_frag_skbuffs;

	data[crr * num_values + crr_cpu] = percpu_priv->stats.tx_errors;
	data[crr++ * num_values + num_cpus] += percpu_priv->stats.tx_errors;

	data[crr * num_values + crr_cpu] = percpu_priv->stats.rx_errors;
	data[crr++ * num_values + num_cpus] += percpu_priv->stats.rx_errors;

	data[crr * num_values + crr_cpu] = percpu_priv->stats.rx_dropped;
	data[crr++ * num_values + num_cpus] += percpu_priv->stats.rx_dropped;

	data[crr * num_values + crr_cpu] = percpu_priv->stats.tx_dropped;
	data[crr++ * num_values + num_cpus] += percpu_priv->stats.tx_dropped;

	data[crr * num_values + crr_cpu] = bp_count;
	data[crr++ * num_values + num_cpus] += bp_count;
पूर्ण

अटल व्योम dpaa_get_ethtool_stats(काष्ठा net_device *net_dev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा dpaa_percpu_priv *percpu_priv;
	काष्ठा dpaa_rx_errors rx_errors;
	अचिन्हित पूर्णांक num_cpus, offset;
	u64 bp_count, cg_समय, cg_num;
	काष्ठा dpaa_ern_cnt ern_cnt;
	काष्ठा dpaa_bp *dpaa_bp;
	काष्ठा dpaa_priv *priv;
	पूर्णांक total_stats, i;
	bool cg_status;

	total_stats = dpaa_get_sset_count(net_dev, ETH_SS_STATS);
	priv     = netdev_priv(net_dev);
	num_cpus = num_online_cpus();

	स_रखो(&bp_count, 0, माप(bp_count));
	स_रखो(&rx_errors, 0, माप(काष्ठा dpaa_rx_errors));
	स_रखो(&ern_cnt, 0, माप(काष्ठा dpaa_ern_cnt));
	स_रखो(data, 0, total_stats * माप(u64));

	क्रम_each_online_cpu(i) अणु
		percpu_priv = per_cpu_ptr(priv->percpu_priv, i);
		dpaa_bp = priv->dpaa_bp;
		अगर (!dpaa_bp->percpu_count)
			जारी;
		bp_count = *(per_cpu_ptr(dpaa_bp->percpu_count, i));
		rx_errors.dme += percpu_priv->rx_errors.dme;
		rx_errors.fpe += percpu_priv->rx_errors.fpe;
		rx_errors.fse += percpu_priv->rx_errors.fse;
		rx_errors.phe += percpu_priv->rx_errors.phe;

		ern_cnt.cg_tdrop     += percpu_priv->ern_cnt.cg_tdrop;
		ern_cnt.wred         += percpu_priv->ern_cnt.wred;
		ern_cnt.err_cond     += percpu_priv->ern_cnt.err_cond;
		ern_cnt.early_winकरोw += percpu_priv->ern_cnt.early_winकरोw;
		ern_cnt.late_winकरोw  += percpu_priv->ern_cnt.late_winकरोw;
		ern_cnt.fq_tdrop     += percpu_priv->ern_cnt.fq_tdrop;
		ern_cnt.fq_retired   += percpu_priv->ern_cnt.fq_retired;
		ern_cnt.orp_zero     += percpu_priv->ern_cnt.orp_zero;

		copy_stats(percpu_priv, num_cpus, i, bp_count, data);
	पूर्ण

	offset = (num_cpus + 1) * (DPAA_STATS_PERCPU_LEN + 1);
	स_नकल(data + offset, &rx_errors, माप(काष्ठा dpaa_rx_errors));

	offset += माप(काष्ठा dpaa_rx_errors) / माप(u64);
	स_नकल(data + offset, &ern_cnt, माप(काष्ठा dpaa_ern_cnt));

	/* gather congestion related counters */
	cg_num    = 0;
	cg_status = false;
	cg_समय   = jअगरfies_to_msecs(priv->cgr_data.congested_jअगरfies);
	अगर (qman_query_cgr_congested(&priv->cgr_data.cgr, &cg_status) == 0) अणु
		cg_num    = priv->cgr_data.cgr_congested_count;

		/* reset congestion stats (like QMan API करोes */
		priv->cgr_data.congested_jअगरfies   = 0;
		priv->cgr_data.cgr_congested_count = 0;
	पूर्ण

	offset += माप(काष्ठा dpaa_ern_cnt) / माप(u64);
	data[offset++] = cg_समय;
	data[offset++] = cg_num;
	data[offset++] = cg_status;
पूर्ण

अटल व्योम dpaa_get_strings(काष्ठा net_device *net_dev, u32 stringset,
			     u8 *data)
अणु
	अचिन्हित पूर्णांक i, j, num_cpus, size;
	अक्षर string_cpu[ETH_GSTRING_LEN];
	u8 *strings;

	स_रखो(string_cpu, 0, माप(string_cpu));
	strings   = data;
	num_cpus  = num_online_cpus();
	size      = DPAA_STATS_GLOBAL_LEN * ETH_GSTRING_LEN;

	क्रम (i = 0; i < DPAA_STATS_PERCPU_LEN; i++) अणु
		क्रम (j = 0; j < num_cpus; j++) अणु
			snम_लिखो(string_cpu, ETH_GSTRING_LEN, "%s [CPU %d]",
				 dpaa_stats_percpu[i], j);
			स_नकल(strings, string_cpu, ETH_GSTRING_LEN);
			strings += ETH_GSTRING_LEN;
		पूर्ण
		snम_लिखो(string_cpu, ETH_GSTRING_LEN, "%s [TOTAL]",
			 dpaa_stats_percpu[i]);
		स_नकल(strings, string_cpu, ETH_GSTRING_LEN);
		strings += ETH_GSTRING_LEN;
	पूर्ण
	क्रम (j = 0; j < num_cpus; j++) अणु
		snम_लिखो(string_cpu, ETH_GSTRING_LEN,
			 "bpool [CPU %d]", j);
		स_नकल(strings, string_cpu, ETH_GSTRING_LEN);
		strings += ETH_GSTRING_LEN;
	पूर्ण
	snम_लिखो(string_cpu, ETH_GSTRING_LEN, "bpool [TOTAL]");
	स_नकल(strings, string_cpu, ETH_GSTRING_LEN);
	strings += ETH_GSTRING_LEN;

	स_नकल(strings, dpaa_stats_global, size);
पूर्ण

अटल पूर्णांक dpaa_get_hash_opts(काष्ठा net_device *dev,
			      काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(dev);

	cmd->data = 0;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		अगर (priv->keygen_in_use)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V4_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V4_FLOW:
	हाल ESP_V6_FLOW:
		अगर (priv->keygen_in_use)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		cmd->data = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			  u32 *unused)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXFH:
		ret = dpaa_get_hash_opts(dev, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dpaa_set_hash(काष्ठा net_device *net_dev, bool enable)
अणु
	काष्ठा mac_device *mac_dev;
	काष्ठा fman_port *rxport;
	काष्ठा dpaa_priv *priv;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;
	rxport = mac_dev->port[0];

	fman_port_use_kg_hash(rxport, enable);
	priv->keygen_in_use = enable;
पूर्ण

अटल पूर्णांक dpaa_set_hash_opts(काष्ठा net_device *dev,
			      काष्ठा ethtool_rxnfc *nfc)
अणु
	पूर्णांक ret = -EINVAL;

	/* we support hashing on IPv4/v6 src/dest IP and L4 src/dest port */
	अगर (nfc->data &
	    ~(RXH_IP_SRC | RXH_IP_DST | RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V4_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V4_FLOW:
	हाल ESP_V6_FLOW:
		dpaa_set_hash(dev, !!nfc->data);
		ret = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dpaa_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = dpaa_set_hash_opts(dev, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dpaa_get_ts_info(काष्ठा net_device *net_dev,
			    काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा device_node *mac_node = dev->of_node;
	काष्ठा device_node *fman_node = शून्य, *ptp_node = शून्य;
	काष्ठा platक्रमm_device *ptp_dev = शून्य;
	काष्ठा ptp_qoriq *ptp = शून्य;

	info->phc_index = -1;

	fman_node = of_get_parent(mac_node);
	अगर (fman_node)
		ptp_node = of_parse_phandle(fman_node, "ptimer-handle", 0);

	अगर (ptp_node)
		ptp_dev = of_find_device_by_node(ptp_node);

	अगर (ptp_dev)
		ptp = platक्रमm_get_drvdata(ptp_dev);

	अगर (ptp)
		info->phc_index = ptp->phc_index;

	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_get_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा qman_portal *portal;
	u32 period;
	u8 thresh;

	portal = qman_get_affine_portal(smp_processor_id());
	qman_portal_get_iperiod(portal, &period);
	qman_dqrr_get_ithresh(portal, &thresh);

	c->rx_coalesce_usecs = period;
	c->rx_max_coalesced_frames = thresh;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_set_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *c)
अणु
	स्थिर cpumask_t *cpus = qman_affine_cpus();
	bool needs_revert[NR_CPUS] = अणुfalseपूर्ण;
	काष्ठा qman_portal *portal;
	u32 period, prev_period;
	u8 thresh, prev_thresh;
	पूर्णांक cpu, res;

	period = c->rx_coalesce_usecs;
	thresh = c->rx_max_coalesced_frames;

	/* save previous values */
	portal = qman_get_affine_portal(smp_processor_id());
	qman_portal_get_iperiod(portal, &prev_period);
	qman_dqrr_get_ithresh(portal, &prev_thresh);

	/* set new values */
	क्रम_each_cpu_and(cpu, cpus, cpu_online_mask) अणु
		portal = qman_get_affine_portal(cpu);
		res = qman_portal_set_iperiod(portal, period);
		अगर (res)
			जाओ revert_values;
		res = qman_dqrr_set_ithresh(portal, thresh);
		अगर (res) अणु
			qman_portal_set_iperiod(portal, prev_period);
			जाओ revert_values;
		पूर्ण
		needs_revert[cpu] = true;
	पूर्ण

	वापस 0;

revert_values:
	/* restore previous values */
	क्रम_each_cpu_and(cpu, cpus, cpu_online_mask) अणु
		अगर (!needs_revert[cpu])
			जारी;
		portal = qman_get_affine_portal(cpu);
		/* previous values will not fail, ignore वापस value */
		qman_portal_set_iperiod(portal, prev_period);
		qman_dqrr_set_ithresh(portal, prev_thresh);
	पूर्ण

	वापस res;
पूर्ण

स्थिर काष्ठा ethtool_ops dpaa_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_RX_MAX_FRAMES,
	.get_drvinfo = dpaa_get_drvinfo,
	.get_msglevel = dpaa_get_msglevel,
	.set_msglevel = dpaa_set_msglevel,
	.nway_reset = dpaa_nway_reset,
	.get_छोड़ोparam = dpaa_get_छोड़ोparam,
	.set_छोड़ोparam = dpaa_set_छोड़ोparam,
	.get_link = ethtool_op_get_link,
	.get_sset_count = dpaa_get_sset_count,
	.get_ethtool_stats = dpaa_get_ethtool_stats,
	.get_strings = dpaa_get_strings,
	.get_link_ksettings = dpaa_get_link_ksettings,
	.set_link_ksettings = dpaa_set_link_ksettings,
	.get_rxnfc = dpaa_get_rxnfc,
	.set_rxnfc = dpaa_set_rxnfc,
	.get_ts_info = dpaa_get_ts_info,
	.get_coalesce = dpaa_get_coalesce,
	.set_coalesce = dpaa_set_coalesce,
पूर्ण;
