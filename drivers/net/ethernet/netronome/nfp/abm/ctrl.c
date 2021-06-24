<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>

#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfpcore/nfp_nffw.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_abi.h"
#समावेश "../nfp_main.h"
#समावेश "../nfp_net.h"
#समावेश "main.h"

#घोषणा NFP_NUM_PRIOS_SYM_NAME	"_abi_pci_dscp_num_prio_%u"
#घोषणा NFP_NUM_BANDS_SYM_NAME	"_abi_pci_dscp_num_band_%u"
#घोषणा NFP_ACT_MASK_SYM_NAME	"_abi_nfd_out_q_actions_%u"

#घोषणा NFP_RED_SUPPORT_SYM_NAME	"_abi_nfd_out_red_offload_%u"

#घोषणा NFP_QLVL_SYM_NAME	"_abi_nfd_out_q_lvls_%u%s"
#घोषणा NFP_QLVL_STRIDE		16
#घोषणा NFP_QLVL_BLOG_BYTES	0
#घोषणा NFP_QLVL_BLOG_PKTS	4
#घोषणा NFP_QLVL_THRS		8
#घोषणा NFP_QLVL_ACT		12

#घोषणा NFP_QMSTAT_SYM_NAME	"_abi_nfdqm%u_stats%s"
#घोषणा NFP_QMSTAT_STRIDE	32
#घोषणा NFP_QMSTAT_NON_STO	0
#घोषणा NFP_QMSTAT_STO		8
#घोषणा NFP_QMSTAT_DROP		16
#घोषणा NFP_QMSTAT_ECN		24

#घोषणा NFP_Q_STAT_SYM_NAME	"_abi_nfd_rxq_stats%u%s"
#घोषणा NFP_Q_STAT_STRIDE	16
#घोषणा NFP_Q_STAT_PKTS		0
#घोषणा NFP_Q_STAT_BYTES	8

#घोषणा NFP_NET_ABM_MBOX_CMD		NFP_NET_CFG_MBOX_SIMPLE_CMD
#घोषणा NFP_NET_ABM_MBOX_RET		NFP_NET_CFG_MBOX_SIMPLE_RET
#घोषणा NFP_NET_ABM_MBOX_DATALEN	NFP_NET_CFG_MBOX_SIMPLE_VAL
#घोषणा NFP_NET_ABM_MBOX_RESERVED	(NFP_NET_CFG_MBOX_SIMPLE_VAL + 4)
#घोषणा NFP_NET_ABM_MBOX_DATA		(NFP_NET_CFG_MBOX_SIMPLE_VAL + 8)

अटल पूर्णांक
nfp_abm_ctrl_stat(काष्ठा nfp_abm_link *alink, स्थिर काष्ठा nfp_rtsym *sym,
		  अचिन्हित पूर्णांक stride, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक band,
		  अचिन्हित पूर्णांक queue, bool is_u64, u64 *res)
अणु
	काष्ठा nfp_cpp *cpp = alink->abm->app->cpp;
	u64 val, sym_offset;
	अचिन्हित पूर्णांक qid;
	u32 val32;
	पूर्णांक err;

	qid = band * NFP_NET_MAX_RX_RINGS + alink->queue_base + queue;

	sym_offset = qid * stride + offset;
	अगर (is_u64)
		err = __nfp_rtsym_पढ़ोq(cpp, sym, 3, 0, sym_offset, &val);
	अन्यथा
		err = __nfp_rtsym_पढ़ोl(cpp, sym, 3, 0, sym_offset, &val32);
	अगर (err) अणु
		nfp_err(cpp, "RED offload reading stat failed on vNIC %d band %d queue %d (+ %d)\n",
			alink->id, band, queue, alink->queue_base);
		वापस err;
	पूर्ण

	*res = is_u64 ? val : val32;
	वापस 0;
पूर्ण

पूर्णांक __nfp_abm_ctrl_set_q_lvl(काष्ठा nfp_abm *abm, अचिन्हित पूर्णांक id, u32 val)
अणु
	काष्ठा nfp_cpp *cpp = abm->app->cpp;
	u64 sym_offset;
	पूर्णांक err;

	__clear_bit(id, abm->threshold_undef);
	अगर (abm->thresholds[id] == val)
		वापस 0;

	sym_offset = id * NFP_QLVL_STRIDE + NFP_QLVL_THRS;
	err = __nfp_rtsym_ग_लिखोl(cpp, abm->q_lvls, 4, 0, sym_offset, val);
	अगर (err) अणु
		nfp_err(cpp,
			"RED offload setting level failed on subqueue %d\n",
			id);
		वापस err;
	पूर्ण

	abm->thresholds[id] = val;
	वापस 0;
पूर्ण

पूर्णांक nfp_abm_ctrl_set_q_lvl(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक band,
			   अचिन्हित पूर्णांक queue, u32 val)
अणु
	अचिन्हित पूर्णांक threshold;

	threshold = band * NFP_NET_MAX_RX_RINGS + alink->queue_base + queue;

	वापस __nfp_abm_ctrl_set_q_lvl(alink->abm, threshold, val);
पूर्ण

पूर्णांक __nfp_abm_ctrl_set_q_act(काष्ठा nfp_abm *abm, अचिन्हित पूर्णांक id,
			     क्रमागत nfp_abm_q_action act)
अणु
	काष्ठा nfp_cpp *cpp = abm->app->cpp;
	u64 sym_offset;
	पूर्णांक err;

	अगर (abm->actions[id] == act)
		वापस 0;

	sym_offset = id * NFP_QLVL_STRIDE + NFP_QLVL_ACT;
	err = __nfp_rtsym_ग_लिखोl(cpp, abm->q_lvls, 4, 0, sym_offset, act);
	अगर (err) अणु
		nfp_err(cpp,
			"RED offload setting action failed on subqueue %d\n",
			id);
		वापस err;
	पूर्ण

	abm->actions[id] = act;
	वापस 0;
पूर्ण

पूर्णांक nfp_abm_ctrl_set_q_act(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक band,
			   अचिन्हित पूर्णांक queue, क्रमागत nfp_abm_q_action act)
अणु
	अचिन्हित पूर्णांक qid;

	qid = band * NFP_NET_MAX_RX_RINGS + alink->queue_base + queue;

	वापस __nfp_abm_ctrl_set_q_act(alink->abm, qid, act);
पूर्ण

u64 nfp_abm_ctrl_stat_non_sto(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक band;
	u64 val, sum = 0;

	क्रम (band = 0; band < alink->abm->num_bands; band++) अणु
		अगर (nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				      NFP_QMSTAT_STRIDE, NFP_QMSTAT_NON_STO,
				      band, queue, true, &val))
			वापस 0;
		sum += val;
	पूर्ण

	वापस sum;
पूर्ण

u64 nfp_abm_ctrl_stat_sto(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक band;
	u64 val, sum = 0;

	क्रम (band = 0; band < alink->abm->num_bands; band++) अणु
		अगर (nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				      NFP_QMSTAT_STRIDE, NFP_QMSTAT_STO,
				      band, queue, true, &val))
			वापस 0;
		sum += val;
	पूर्ण

	वापस sum;
पूर्ण

अटल पूर्णांक
nfp_abm_ctrl_stat_basic(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक band,
			अचिन्हित पूर्णांक queue, अचिन्हित पूर्णांक off, u64 *val)
अणु
	अगर (!nfp_abm_has_prio(alink->abm)) अणु
		अगर (!band) अणु
			अचिन्हित पूर्णांक id = alink->queue_base + queue;

			*val = nn_पढ़ोq(alink->vnic,
					NFP_NET_CFG_RXR_STATS(id) + off);
		पूर्ण अन्यथा अणु
			*val = 0;
		पूर्ण

		वापस 0;
	पूर्ण अन्यथा अणु
		वापस nfp_abm_ctrl_stat(alink, alink->abm->q_stats,
					 NFP_Q_STAT_STRIDE, off, band, queue,
					 true, val);
	पूर्ण
पूर्ण

पूर्णांक nfp_abm_ctrl_पढ़ो_q_stats(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक band,
			      अचिन्हित पूर्णांक queue, काष्ठा nfp_alink_stats *stats)
अणु
	पूर्णांक err;

	err = nfp_abm_ctrl_stat_basic(alink, band, queue, NFP_Q_STAT_PKTS,
				      &stats->tx_pkts);
	अगर (err)
		वापस err;

	err = nfp_abm_ctrl_stat_basic(alink, band, queue, NFP_Q_STAT_BYTES,
				      &stats->tx_bytes);
	अगर (err)
		वापस err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->q_lvls, NFP_QLVL_STRIDE,
				NFP_QLVL_BLOG_BYTES, band, queue, false,
				&stats->backlog_bytes);
	अगर (err)
		वापस err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->q_lvls,
				NFP_QLVL_STRIDE, NFP_QLVL_BLOG_PKTS,
				band, queue, false, &stats->backlog_pkts);
	अगर (err)
		वापस err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				NFP_QMSTAT_STRIDE, NFP_QMSTAT_DROP,
				band, queue, true, &stats->drops);
	अगर (err)
		वापस err;

	वापस nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				 NFP_QMSTAT_STRIDE, NFP_QMSTAT_ECN,
				 band, queue, true, &stats->overlimits);
पूर्ण

पूर्णांक nfp_abm_ctrl_पढ़ो_q_xstats(काष्ठा nfp_abm_link *alink,
			       अचिन्हित पूर्णांक band, अचिन्हित पूर्णांक queue,
			       काष्ठा nfp_alink_xstats *xstats)
अणु
	पूर्णांक err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				NFP_QMSTAT_STRIDE, NFP_QMSTAT_DROP,
				band, queue, true, &xstats->pdrop);
	अगर (err)
		वापस err;

	वापस nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				 NFP_QMSTAT_STRIDE, NFP_QMSTAT_ECN,
				 band, queue, true, &xstats->ecn_marked);
पूर्ण

पूर्णांक nfp_abm_ctrl_qm_enable(काष्ठा nfp_abm *abm)
अणु
	वापस nfp_mbox_cmd(abm->app->pf, NFP_MBOX_PCIE_ABM_ENABLE,
			    शून्य, 0, शून्य, 0);
पूर्ण

पूर्णांक nfp_abm_ctrl_qm_disable(काष्ठा nfp_abm *abm)
अणु
	वापस nfp_mbox_cmd(abm->app->pf, NFP_MBOX_PCIE_ABM_DISABLE,
			    शून्य, 0, शून्य, 0);
पूर्ण

पूर्णांक nfp_abm_ctrl_prio_map_update(काष्ठा nfp_abm_link *alink, u32 *packed)
अणु
	स्थिर u32 cmd = NFP_NET_CFG_MBOX_CMD_PCI_DSCP_PRIOMAP_SET;
	काष्ठा nfp_net *nn = alink->vnic;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = nfp_net_mbox_lock(nn, alink->abm->prio_map_len);
	अगर (err)
		वापस err;

	/* Write data_len and wipe reserved */
	nn_ग_लिखोq(nn, nn->tlv_caps.mbox_off + NFP_NET_ABM_MBOX_DATALEN,
		  alink->abm->prio_map_len);

	क्रम (i = 0; i < alink->abm->prio_map_len; i += माप(u32))
		nn_ग_लिखोl(nn, nn->tlv_caps.mbox_off + NFP_NET_ABM_MBOX_DATA + i,
			  packed[i / माप(u32)]);

	err = nfp_net_mbox_reconfig_and_unlock(nn, cmd);
	अगर (err)
		nfp_err(alink->abm->app->cpp,
			"setting DSCP -> VQ map failed with error %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_abm_ctrl_prio_check_params(काष्ठा nfp_abm_link *alink)
अणु
	काष्ठा nfp_abm *abm = alink->abm;
	काष्ठा nfp_net *nn = alink->vnic;
	अचिन्हित पूर्णांक min_mbox_sz;

	अगर (!nfp_abm_has_prio(alink->abm))
		वापस 0;

	min_mbox_sz = NFP_NET_ABM_MBOX_DATA + alink->abm->prio_map_len;
	अगर (nn->tlv_caps.mbox_len < min_mbox_sz) अणु
		nfp_err(abm->app->pf->cpp, "vNIC mailbox too small for prio offload: %u, need: %u\n",
			nn->tlv_caps.mbox_len,  min_mbox_sz);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nfp_abm_ctrl_पढ़ो_params(काष्ठा nfp_abm_link *alink)
अणु
	alink->queue_base = nn_पढ़ोl(alink->vnic, NFP_NET_CFG_START_RXQ);
	alink->queue_base /= alink->vnic->stride_rx;

	वापस nfp_abm_ctrl_prio_check_params(alink);
पूर्ण

अटल अचिन्हित पूर्णांक nfp_abm_ctrl_prio_map_size(काष्ठा nfp_abm *abm)
अणु
	अचिन्हित पूर्णांक size;

	size = roundup_घात_of_two(order_base_2(abm->num_bands));
	size = DIV_ROUND_UP(size * abm->num_prios, BITS_PER_BYTE);
	size = round_up(size, माप(u32));

	वापस size;
पूर्ण

अटल स्थिर काष्ठा nfp_rtsym *
nfp_abm_ctrl_find_rtsym(काष्ठा nfp_pf *pf, स्थिर अक्षर *name, अचिन्हित पूर्णांक size)
अणु
	स्थिर काष्ठा nfp_rtsym *sym;

	sym = nfp_rtsym_lookup(pf->rtbl, name);
	अगर (!sym) अणु
		nfp_err(pf->cpp, "Symbol '%s' not found\n", name);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	अगर (nfp_rtsym_size(sym) != size) अणु
		nfp_err(pf->cpp,
			"Symbol '%s' wrong size: expected %u got %llu\n",
			name, size, nfp_rtsym_size(sym));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस sym;
पूर्ण

अटल स्थिर काष्ठा nfp_rtsym *
nfp_abm_ctrl_find_q_rtsym(काष्ठा nfp_abm *abm, स्थिर अक्षर *name_fmt,
			  माप_प्रकार size)
अणु
	अक्षर pf_symbol[64];

	size = array3_size(size, abm->num_bands, NFP_NET_MAX_RX_RINGS);
	snम_लिखो(pf_symbol, माप(pf_symbol), name_fmt,
		 abm->pf_id, nfp_abm_has_prio(abm) ? "_per_band" : "");

	वापस nfp_abm_ctrl_find_rtsym(abm->app->pf, pf_symbol, size);
पूर्ण

पूर्णांक nfp_abm_ctrl_find_addrs(काष्ठा nfp_abm *abm)
अणु
	काष्ठा nfp_pf *pf = abm->app->pf;
	स्थिर काष्ठा nfp_rtsym *sym;
	पूर्णांक res;

	abm->pf_id = nfp_cppcore_pcie_unit(pf->cpp);

	/* Check अगर Qdisc offloads are supported */
	res = nfp_pf_rtsym_पढ़ो_optional(pf, NFP_RED_SUPPORT_SYM_NAME, 1);
	अगर (res < 0)
		वापस res;
	abm->red_support = res;

	/* Read count of prios and prio bands */
	res = nfp_pf_rtsym_पढ़ो_optional(pf, NFP_NUM_BANDS_SYM_NAME, 1);
	अगर (res < 0)
		वापस res;
	abm->num_bands = res;

	res = nfp_pf_rtsym_पढ़ो_optional(pf, NFP_NUM_PRIOS_SYM_NAME, 1);
	अगर (res < 0)
		वापस res;
	abm->num_prios = res;

	/* Read available actions */
	res = nfp_pf_rtsym_पढ़ो_optional(pf, NFP_ACT_MASK_SYM_NAME,
					 BIT(NFP_ABM_ACT_MARK_DROP));
	अगर (res < 0)
		वापस res;
	abm->action_mask = res;

	abm->prio_map_len = nfp_abm_ctrl_prio_map_size(abm);
	abm->dscp_mask = GENMASK(7, 8 - order_base_2(abm->num_prios));

	/* Check values are sane, U16_MAX is arbitrarily chosen as max */
	अगर (!is_घातer_of_2(abm->num_bands) || !is_घातer_of_2(abm->num_prios) ||
	    abm->num_bands > U16_MAX || abm->num_prios > U16_MAX ||
	    (abm->num_bands == 1) != (abm->num_prios == 1)) अणु
		nfp_err(pf->cpp,
			"invalid priomap description num bands: %u and num prios: %u\n",
			abm->num_bands, abm->num_prios);
		वापस -EINVAL;
	पूर्ण

	/* Find level and stat symbols */
	अगर (!abm->red_support)
		वापस 0;

	sym = nfp_abm_ctrl_find_q_rtsym(abm, NFP_QLVL_SYM_NAME,
					NFP_QLVL_STRIDE);
	अगर (IS_ERR(sym))
		वापस PTR_ERR(sym);
	abm->q_lvls = sym;

	sym = nfp_abm_ctrl_find_q_rtsym(abm, NFP_QMSTAT_SYM_NAME,
					NFP_QMSTAT_STRIDE);
	अगर (IS_ERR(sym))
		वापस PTR_ERR(sym);
	abm->qm_stats = sym;

	अगर (nfp_abm_has_prio(abm)) अणु
		sym = nfp_abm_ctrl_find_q_rtsym(abm, NFP_Q_STAT_SYM_NAME,
						NFP_Q_STAT_STRIDE);
		अगर (IS_ERR(sym))
			वापस PTR_ERR(sym);
		abm->q_stats = sym;
	पूर्ण

	वापस 0;
पूर्ण
