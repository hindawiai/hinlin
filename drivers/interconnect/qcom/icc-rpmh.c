<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश "bcm-voter.h"
#समावेश "icc-rpmh.h"

/**
 * qcom_icc_pre_aggregate - cleans up stale values from prior icc_set
 * @node: icc node to operate on
 */
व्योम qcom_icc_pre_aggregate(काष्ठा icc_node *node)
अणु
	माप_प्रकार i;
	काष्ठा qcom_icc_node *qn;

	qn = node->data;

	क्रम (i = 0; i < QCOM_ICC_NUM_BUCKETS; i++) अणु
		qn->sum_avg[i] = 0;
		qn->max_peak[i] = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_pre_aggregate);

/**
 * qcom_icc_aggregate - aggregate bw क्रम buckets indicated by tag
 * @node: node to aggregate
 * @tag: tag to indicate which buckets to aggregate
 * @avg_bw: new bw to sum aggregate
 * @peak_bw: new bw to max aggregate
 * @agg_avg: existing aggregate avg bw val
 * @agg_peak: existing aggregate peak bw val
 */
पूर्णांक qcom_icc_aggregate(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
		       u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
अणु
	माप_प्रकार i;
	काष्ठा qcom_icc_node *qn;
	काष्ठा qcom_icc_provider *qp;

	qn = node->data;
	qp = to_qcom_provider(node->provider);

	अगर (!tag)
		tag = QCOM_ICC_TAG_ALWAYS;

	क्रम (i = 0; i < QCOM_ICC_NUM_BUCKETS; i++) अणु
		अगर (tag & BIT(i)) अणु
			qn->sum_avg[i] += avg_bw;
			qn->max_peak[i] = max_t(u32, qn->max_peak[i], peak_bw);
		पूर्ण
	पूर्ण

	*agg_avg += avg_bw;
	*agg_peak = max_t(u32, *agg_peak, peak_bw);

	क्रम (i = 0; i < qn->num_bcms; i++)
		qcom_icc_bcm_voter_add(qp->voter, qn->bcms[i]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_aggregate);

/**
 * qcom_icc_set - set the स्थिरraपूर्णांकs based on path
 * @src: source node क्रम the path to set स्थिरraपूर्णांकs on
 * @dst: destination node क्रम the path to set स्थिरraपूर्णांकs on
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक qcom_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा qcom_icc_provider *qp;
	काष्ठा qcom_icc_node *qn;
	काष्ठा icc_node *node;

	अगर (!src)
		node = dst;
	अन्यथा
		node = src;

	qp = to_qcom_provider(node->provider);
	qn = node->data;

	qn->sum_avg[QCOM_ICC_BUCKET_AMC] = max_t(u64, qn->sum_avg[QCOM_ICC_BUCKET_AMC],
						 node->avg_bw);
	qn->max_peak[QCOM_ICC_BUCKET_AMC] = max_t(u64, qn->max_peak[QCOM_ICC_BUCKET_AMC],
						  node->peak_bw);

	qcom_icc_bcm_voter_commit(qp->voter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_set);

काष्ठा icc_node_data *qcom_icc_xlate_extended(काष्ठा of_phandle_args *spec, व्योम *data)
अणु
	काष्ठा icc_node_data *ndata;
	काष्ठा icc_node *node;

	node = of_icc_xlate_onecell(spec, data);
	अगर (IS_ERR(node))
		वापस ERR_CAST(node);

	ndata = kzalloc(माप(*ndata), GFP_KERNEL);
	अगर (!ndata)
		वापस ERR_PTR(-ENOMEM);

	ndata->node = node;

	अगर (spec->args_count == 2)
		ndata->tag = spec->args[1];

	अगर (spec->args_count > 2)
		pr_warn("%pOF: Too many arguments, path tag is not parsed\n", spec->np);

	वापस ndata;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_xlate_extended);

/**
 * qcom_icc_bcm_init - populates bcm aux data and connect qnodes
 * @bcm: bcm to be initialized
 * @dev: associated provider device
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक qcom_icc_bcm_init(काष्ठा qcom_icc_bcm *bcm, काष्ठा device *dev)
अणु
	काष्ठा qcom_icc_node *qn;
	स्थिर काष्ठा bcm_db *data;
	माप_प्रकार data_count;
	पूर्णांक i;

	/* BCM is alपढ़ोy initialised*/
	अगर (bcm->addr)
		वापस 0;

	bcm->addr = cmd_db_पढ़ो_addr(bcm->name);
	अगर (!bcm->addr) अणु
		dev_err(dev, "%s could not find RPMh address\n",
			bcm->name);
		वापस -EINVAL;
	पूर्ण

	data = cmd_db_पढ़ो_aux_data(bcm->name, &data_count);
	अगर (IS_ERR(data)) अणु
		dev_err(dev, "%s command db read error (%ld)\n",
			bcm->name, PTR_ERR(data));
		वापस PTR_ERR(data);
	पूर्ण
	अगर (!data_count) अणु
		dev_err(dev, "%s command db missing or partial aux data\n",
			bcm->name);
		वापस -EINVAL;
	पूर्ण

	bcm->aux_data.unit = le32_to_cpu(data->unit);
	bcm->aux_data.width = le16_to_cpu(data->width);
	bcm->aux_data.vcd = data->vcd;
	bcm->aux_data.reserved = data->reserved;
	INIT_LIST_HEAD(&bcm->list);
	INIT_LIST_HEAD(&bcm->ws_list);

	अगर (!bcm->vote_scale)
		bcm->vote_scale = 1000;

	/* Link Qnodes to their respective BCMs */
	क्रम (i = 0; i < bcm->num_nodes; i++) अणु
		qn = bcm->nodes[i];
		qn->bcms[qn->num_bcms] = bcm;
		qn->num_bcms++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_bcm_init);

MODULE_LICENSE("GPL v2");
