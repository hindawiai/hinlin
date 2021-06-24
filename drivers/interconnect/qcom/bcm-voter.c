<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020-2021, The Linux Foundation. All rights reserved.
 */

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <soc/qcom/rpmh.h>
#समावेश <soc/qcom/tcs.h>

#समावेश "bcm-voter.h"
#समावेश "icc-rpmh.h"

अटल LIST_HEAD(bcm_voters);
अटल DEFINE_MUTEX(bcm_voter_lock);

/**
 * काष्ठा bcm_voter - Bus Clock Manager voter
 * @dev: reference to the device that communicates with the BCM
 * @np: reference to the device node to match bcm voters
 * @lock: mutex to protect commit and wake/sleep lists in the voter
 * @commit_list: list containing bcms to be committed to hardware
 * @ws_list: list containing bcms that have dअगरferent wake/sleep votes
 * @voter_node: list of bcm voters
 * @tcs_रुको: mask क्रम which buckets require TCS completion
 */
काष्ठा bcm_voter अणु
	काष्ठा device *dev;
	काष्ठा device_node *np;
	काष्ठा mutex lock;
	काष्ठा list_head commit_list;
	काष्ठा list_head ws_list;
	काष्ठा list_head voter_node;
	u32 tcs_रुको;
पूर्ण;

अटल पूर्णांक cmp_vcd(व्योम *priv, स्थिर काष्ठा list_head *a, स्थिर काष्ठा list_head *b)
अणु
	स्थिर काष्ठा qcom_icc_bcm *bcm_a = list_entry(a, काष्ठा qcom_icc_bcm, list);
	स्थिर काष्ठा qcom_icc_bcm *bcm_b = list_entry(b, काष्ठा qcom_icc_bcm, list);

	वापस bcm_a->aux_data.vcd - bcm_b->aux_data.vcd;
पूर्ण

अटल u64 bcm_भाग(u64 num, u32 base)
अणु
	/* Ensure that small votes aren't lost. */
	अगर (num && num < base)
		वापस 1;

	करो_भाग(num, base);

	वापस num;
पूर्ण

अटल व्योम bcm_aggregate(काष्ठा qcom_icc_bcm *bcm)
अणु
	काष्ठा qcom_icc_node *node;
	माप_प्रकार i, bucket;
	u64 agg_avg[QCOM_ICC_NUM_BUCKETS] = अणु0पूर्ण;
	u64 agg_peak[QCOM_ICC_NUM_BUCKETS] = अणु0पूर्ण;
	u64 temp;

	क्रम (bucket = 0; bucket < QCOM_ICC_NUM_BUCKETS; bucket++) अणु
		क्रम (i = 0; i < bcm->num_nodes; i++) अणु
			node = bcm->nodes[i];
			temp = bcm_भाग(node->sum_avg[bucket] * bcm->aux_data.width,
				       node->buswidth * node->channels);
			agg_avg[bucket] = max(agg_avg[bucket], temp);

			temp = bcm_भाग(node->max_peak[bucket] * bcm->aux_data.width,
				       node->buswidth);
			agg_peak[bucket] = max(agg_peak[bucket], temp);
		पूर्ण

		temp = agg_avg[bucket] * bcm->vote_scale;
		bcm->vote_x[bucket] = bcm_भाग(temp, bcm->aux_data.unit);

		temp = agg_peak[bucket] * bcm->vote_scale;
		bcm->vote_y[bucket] = bcm_भाग(temp, bcm->aux_data.unit);
	पूर्ण

	अगर (bcm->keepalive && bcm->vote_x[QCOM_ICC_BUCKET_AMC] == 0 &&
	    bcm->vote_y[QCOM_ICC_BUCKET_AMC] == 0) अणु
		bcm->vote_x[QCOM_ICC_BUCKET_AMC] = 1;
		bcm->vote_x[QCOM_ICC_BUCKET_WAKE] = 1;
		bcm->vote_y[QCOM_ICC_BUCKET_AMC] = 1;
		bcm->vote_y[QCOM_ICC_BUCKET_WAKE] = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tcs_cmd_gen(काष्ठा tcs_cmd *cmd, u64 vote_x, u64 vote_y,
			       u32 addr, bool commit, bool रुको)
अणु
	bool valid = true;

	अगर (!cmd)
		वापस;

	स_रखो(cmd, 0, माप(*cmd));

	अगर (vote_x == 0 && vote_y == 0)
		valid = false;

	अगर (vote_x > BCM_TCS_CMD_VOTE_MASK)
		vote_x = BCM_TCS_CMD_VOTE_MASK;

	अगर (vote_y > BCM_TCS_CMD_VOTE_MASK)
		vote_y = BCM_TCS_CMD_VOTE_MASK;

	cmd->addr = addr;
	cmd->data = BCM_TCS_CMD(commit, valid, vote_x, vote_y);

	/*
	 * Set the रुको क्रम completion flag on command that need to be completed
	 * beक्रमe the next command.
	 */
	cmd->रुको = रुको;
पूर्ण

अटल व्योम tcs_list_gen(काष्ठा bcm_voter *voter, पूर्णांक bucket,
			 काष्ठा tcs_cmd tcs_list[MAX_VCD],
			 पूर्णांक n[MAX_VCD + 1])
अणु
	काष्ठा list_head *bcm_list = &voter->commit_list;
	काष्ठा qcom_icc_bcm *bcm;
	bool commit, रुको;
	माप_प्रकार idx = 0, batch = 0, cur_vcd_size = 0;

	स_रखो(n, 0, माप(पूर्णांक) * (MAX_VCD + 1));

	list_क्रम_each_entry(bcm, bcm_list, list) अणु
		commit = false;
		cur_vcd_size++;
		अगर ((list_is_last(&bcm->list, bcm_list)) ||
		    bcm->aux_data.vcd != list_next_entry(bcm, list)->aux_data.vcd) अणु
			commit = true;
			cur_vcd_size = 0;
		पूर्ण

		रुको = commit && (voter->tcs_रुको & BIT(bucket));

		tcs_cmd_gen(&tcs_list[idx], bcm->vote_x[bucket],
			    bcm->vote_y[bucket], bcm->addr, commit, रुको);
		idx++;
		n[batch]++;
		/*
		 * Batch the BCMs in such a way that we करो not split them in
		 * multiple payloads when they are under the same VCD. This is
		 * to ensure that every BCM is committed since we only set the
		 * commit bit on the last BCM request of every VCD.
		 */
		अगर (n[batch] >= MAX_RPMH_PAYLOAD) अणु
			अगर (!commit) अणु
				n[batch] -= cur_vcd_size;
				n[batch + 1] = cur_vcd_size;
			पूर्ण
			batch++;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * of_bcm_voter_get - माला_लो a bcm voter handle from DT node
 * @dev: device poपूर्णांकer क्रम the consumer device
 * @name: name क्रम the bcm voter device
 *
 * This function will match a device_node poपूर्णांकer क्रम the phandle
 * specअगरied in the device DT and वापस a bcm_voter handle on success.
 *
 * Returns bcm_voter poपूर्णांकer or ERR_PTR() on error. EPROBE_DEFER is वापसed
 * when matching bcm voter is yet to be found.
 */
काष्ठा bcm_voter *of_bcm_voter_get(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा bcm_voter *voter = ERR_PTR(-EPROBE_DEFER);
	काष्ठा bcm_voter *temp;
	काष्ठा device_node *np, *node;
	पूर्णांक idx = 0;

	अगर (!dev || !dev->of_node)
		वापस ERR_PTR(-ENODEV);

	np = dev->of_node;

	अगर (name) अणु
		idx = of_property_match_string(np, "qcom,bcm-voter-names", name);
		अगर (idx < 0)
			वापस ERR_PTR(idx);
	पूर्ण

	node = of_parse_phandle(np, "qcom,bcm-voters", idx);

	mutex_lock(&bcm_voter_lock);
	list_क्रम_each_entry(temp, &bcm_voters, voter_node) अणु
		अगर (temp->np == node) अणु
			voter = temp;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&bcm_voter_lock);

	of_node_put(node);
	वापस voter;
पूर्ण
EXPORT_SYMBOL_GPL(of_bcm_voter_get);

/**
 * qcom_icc_bcm_voter_add - queues up the bcm nodes that require updates
 * @voter: voter that the bcms are being added to
 * @bcm: bcm to add to the commit and wake sleep list
 */
व्योम qcom_icc_bcm_voter_add(काष्ठा bcm_voter *voter, काष्ठा qcom_icc_bcm *bcm)
अणु
	अगर (!voter)
		वापस;

	mutex_lock(&voter->lock);
	अगर (list_empty(&bcm->list))
		list_add_tail(&bcm->list, &voter->commit_list);

	अगर (list_empty(&bcm->ws_list))
		list_add_tail(&bcm->ws_list, &voter->ws_list);

	mutex_unlock(&voter->lock);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_bcm_voter_add);

/**
 * qcom_icc_bcm_voter_commit - generates and commits tcs cmds based on bcms
 * @voter: voter that needs flushing
 *
 * This function generates a set of AMC commands and flushes to the BCM device
 * associated with the voter. It conditionally generate WAKE and SLEEP commands
 * based on deltas between WAKE/SLEEP requirements. The ws_list persists
 * through multiple commit requests and bcm nodes are हटाओd only when the
 * requirements क्रम WAKE matches SLEEP.
 *
 * Returns 0 on success, or an appropriate error code otherwise.
 */
पूर्णांक qcom_icc_bcm_voter_commit(काष्ठा bcm_voter *voter)
अणु
	काष्ठा qcom_icc_bcm *bcm;
	काष्ठा qcom_icc_bcm *bcm_पंचांगp;
	पूर्णांक commit_idx[MAX_VCD + 1];
	काष्ठा tcs_cmd cmds[MAX_BCMS];
	पूर्णांक ret = 0;

	अगर (!voter)
		वापस 0;

	mutex_lock(&voter->lock);
	list_क्रम_each_entry(bcm, &voter->commit_list, list)
		bcm_aggregate(bcm);

	/*
	 * Pre sort the BCMs based on VCD क्रम ease of generating a command list
	 * that groups the BCMs with the same VCD together. VCDs are numbered
	 * with lowest being the most expensive समय wise, ensuring that
	 * those commands are being sent the earliest in the queue. This needs
	 * to be sorted every commit since we can't guarantee the order in which
	 * the BCMs are added to the list.
	 */
	list_sort(शून्य, &voter->commit_list, cmp_vcd);

	/*
	 * Conकाष्ठा the command list based on a pre ordered list of BCMs
	 * based on VCD.
	 */
	tcs_list_gen(voter, QCOM_ICC_BUCKET_AMC, cmds, commit_idx);
	अगर (!commit_idx[0])
		जाओ out;

	rpmh_invalidate(voter->dev);

	ret = rpmh_ग_लिखो_batch(voter->dev, RPMH_ACTIVE_ONLY_STATE,
			       cmds, commit_idx);
	अगर (ret) अणु
		pr_err("Error sending AMC RPMH requests (%d)\n", ret);
		जाओ out;
	पूर्ण

	list_क्रम_each_entry_safe(bcm, bcm_पंचांगp, &voter->commit_list, list)
		list_del_init(&bcm->list);

	list_क्रम_each_entry_safe(bcm, bcm_पंचांगp, &voter->ws_list, ws_list) अणु
		/*
		 * Only generate WAKE and SLEEP commands अगर a resource's
		 * requirements change as the execution environment transitions
		 * between dअगरferent घातer states.
		 */
		अगर (bcm->vote_x[QCOM_ICC_BUCKET_WAKE] !=
		    bcm->vote_x[QCOM_ICC_BUCKET_SLEEP] ||
		    bcm->vote_y[QCOM_ICC_BUCKET_WAKE] !=
		    bcm->vote_y[QCOM_ICC_BUCKET_SLEEP])
			list_add_tail(&bcm->list, &voter->commit_list);
		अन्यथा
			list_del_init(&bcm->ws_list);
	पूर्ण

	अगर (list_empty(&voter->commit_list))
		जाओ out;

	list_sort(शून्य, &voter->commit_list, cmp_vcd);

	tcs_list_gen(voter, QCOM_ICC_BUCKET_WAKE, cmds, commit_idx);

	ret = rpmh_ग_लिखो_batch(voter->dev, RPMH_WAKE_ONLY_STATE, cmds, commit_idx);
	अगर (ret) अणु
		pr_err("Error sending WAKE RPMH requests (%d)\n", ret);
		जाओ out;
	पूर्ण

	tcs_list_gen(voter, QCOM_ICC_BUCKET_SLEEP, cmds, commit_idx);

	ret = rpmh_ग_लिखो_batch(voter->dev, RPMH_SLEEP_STATE, cmds, commit_idx);
	अगर (ret) अणु
		pr_err("Error sending SLEEP RPMH requests (%d)\n", ret);
		जाओ out;
	पूर्ण

out:
	list_क्रम_each_entry_safe(bcm, bcm_पंचांगp, &voter->commit_list, list)
		list_del_init(&bcm->list);

	mutex_unlock(&voter->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_bcm_voter_commit);

अटल पूर्णांक qcom_icc_bcm_voter_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा bcm_voter *voter;

	voter = devm_kzalloc(&pdev->dev, माप(*voter), GFP_KERNEL);
	अगर (!voter)
		वापस -ENOMEM;

	voter->dev = &pdev->dev;
	voter->np = np;

	अगर (of_property_पढ़ो_u32(np, "qcom,tcs-wait", &voter->tcs_रुको))
		voter->tcs_रुको = QCOM_ICC_TAG_ACTIVE_ONLY;

	mutex_init(&voter->lock);
	INIT_LIST_HEAD(&voter->commit_list);
	INIT_LIST_HEAD(&voter->ws_list);

	mutex_lock(&bcm_voter_lock);
	list_add_tail(&voter->voter_node, &bcm_voters);
	mutex_unlock(&bcm_voter_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_voter_of_match[] = अणु
	अणु .compatible = "qcom,bcm-voter" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_voter_of_match);

अटल काष्ठा platक्रमm_driver qcom_icc_bcm_voter_driver = अणु
	.probe = qcom_icc_bcm_voter_probe,
	.driver = अणु
		.name		= "bcm_voter",
		.of_match_table = bcm_voter_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_icc_bcm_voter_driver);

MODULE_AUTHOR("David Dai <daidavid1@codeaurora.org>");
MODULE_DESCRIPTION("Qualcomm BCM Voter interconnect driver");
MODULE_LICENSE("GPL v2");
