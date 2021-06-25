<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2020 The Linux Foundation. All rights reserved.
 */

#समावेश "debugfs.h"

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "hal_rx.h"
#समावेश "dp_tx.h"
#समावेश "debugfs_htt_stats.h"
#समावेश "peer.h"

अटल स्थिर अक्षर *htt_bp_umac_ring[HTT_SW_UMAC_RING_IDX_MAX] = अणु
	"REO2SW1_RING",
	"REO2SW2_RING",
	"REO2SW3_RING",
	"REO2SW4_RING",
	"WBM2REO_LINK_RING",
	"REO2TCL_RING",
	"REO2FW_RING",
	"RELEASE_RING",
	"PPE_RELEASE_RING",
	"TCL2TQM_RING",
	"TQM_RELEASE_RING",
	"REO_RELEASE_RING",
	"WBM2SW0_RELEASE_RING",
	"WBM2SW1_RELEASE_RING",
	"WBM2SW2_RELEASE_RING",
	"WBM2SW3_RELEASE_RING",
	"REO_CMD_RING",
	"REO_STATUS_RING",
पूर्ण;

अटल स्थिर अक्षर *htt_bp_lmac_ring[HTT_SW_LMAC_RING_IDX_MAX] = अणु
	"FW2RXDMA_BUF_RING",
	"FW2RXDMA_STATUS_RING",
	"FW2RXDMA_LINK_RING",
	"SW2RXDMA_BUF_RING",
	"WBM2RXDMA_LINK_RING",
	"RXDMA2FW_RING",
	"RXDMA2SW_RING",
	"RXDMA2RELEASE_RING",
	"RXDMA2REO_RING",
	"MONITOR_STATUS_RING",
	"MONITOR_BUF_RING",
	"MONITOR_DESC_RING",
	"MONITOR_DEST_RING",
पूर्ण;

अटल व्योम ath11k_fw_stats_pdevs_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा ath11k_fw_stats_pdev *i, *पंचांगp;

	list_क्रम_each_entry_safe(i, पंचांगp, head, list) अणु
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल व्योम ath11k_fw_stats_vdevs_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा ath11k_fw_stats_vdev *i, *पंचांगp;

	list_क्रम_each_entry_safe(i, पंचांगp, head, list) अणु
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल व्योम ath11k_fw_stats_bcn_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा ath11k_fw_stats_bcn *i, *पंचांगp;

	list_क्रम_each_entry_safe(i, पंचांगp, head, list) अणु
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल व्योम ath11k_debugfs_fw_stats_reset(काष्ठा ath11k *ar)
अणु
	spin_lock_bh(&ar->data_lock);
	ar->debug.fw_stats_करोne = false;
	ath11k_fw_stats_pdevs_मुक्त(&ar->debug.fw_stats.pdevs);
	ath11k_fw_stats_vdevs_मुक्त(&ar->debug.fw_stats.vdevs);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

व्योम ath11k_debugfs_fw_stats_process(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_fw_stats stats = अणुपूर्ण;
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	bool is_end;
	अटल अचिन्हित पूर्णांक num_vdev, num_bcn;
	माप_प्रकार total_vdevs_started = 0;
	पूर्णांक i, ret;

	INIT_LIST_HEAD(&stats.pdevs);
	INIT_LIST_HEAD(&stats.vdevs);
	INIT_LIST_HEAD(&stats.bcn);

	ret = ath11k_wmi_pull_fw_stats(ab, skb, &stats);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to pull fw stats: %d\n", ret);
		जाओ मुक्त;
	पूर्ण

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_pdev_id(ab, stats.pdev_id);
	अगर (!ar) अणु
		rcu_पढ़ो_unlock();
		ath11k_warn(ab, "failed to get ar for pdev_id %d: %d\n",
			    stats.pdev_id, ret);
		जाओ मुक्त;
	पूर्ण

	spin_lock_bh(&ar->data_lock);

	अगर (stats.stats_id == WMI_REQUEST_PDEV_STAT) अणु
		list_splice_tail_init(&stats.pdevs, &ar->debug.fw_stats.pdevs);
		ar->debug.fw_stats_करोne = true;
		जाओ complete;
	पूर्ण

	अगर (stats.stats_id == WMI_REQUEST_VDEV_STAT) अणु
		अगर (list_empty(&stats.vdevs)) अणु
			ath11k_warn(ab, "empty vdev stats");
			जाओ complete;
		पूर्ण
		/* FW sends all the active VDEV stats irrespective of PDEV,
		 * hence limit until the count of all VDEVs started
		 */
		क्रम (i = 0; i < ab->num_radios; i++) अणु
			pdev = rcu_dereference(ab->pdevs_active[i]);
			अगर (pdev && pdev->ar)
				total_vdevs_started += ar->num_started_vdevs;
		पूर्ण

		is_end = ((++num_vdev) == total_vdevs_started);

		list_splice_tail_init(&stats.vdevs,
				      &ar->debug.fw_stats.vdevs);

		अगर (is_end) अणु
			ar->debug.fw_stats_करोne = true;
			num_vdev = 0;
		पूर्ण
		जाओ complete;
	पूर्ण

	अगर (stats.stats_id == WMI_REQUEST_BCN_STAT) अणु
		अगर (list_empty(&stats.bcn)) अणु
			ath11k_warn(ab, "empty bcn stats");
			जाओ complete;
		पूर्ण
		/* Mark end until we reached the count of all started VDEVs
		 * within the PDEV
		 */
		is_end = ((++num_bcn) == ar->num_started_vdevs);

		list_splice_tail_init(&stats.bcn,
				      &ar->debug.fw_stats.bcn);

		अगर (is_end) अणु
			ar->debug.fw_stats_करोne = true;
			num_bcn = 0;
		पूर्ण
	पूर्ण
complete:
	complete(&ar->debug.fw_stats_complete);
	rcu_पढ़ो_unlock();
	spin_unlock_bh(&ar->data_lock);

मुक्त:
	ath11k_fw_stats_pdevs_मुक्त(&stats.pdevs);
	ath11k_fw_stats_vdevs_मुक्त(&stats.vdevs);
	ath11k_fw_stats_bcn_मुक्त(&stats.bcn);
पूर्ण

अटल पूर्णांक ath11k_debugfs_fw_stats_request(काष्ठा ath11k *ar,
					   काष्ठा stats_request_params *req_param)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	अचिन्हित दीर्घ समयout, समय_left;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	/* FW stats can get split when exceeding the stats data buffer limit.
	 * In that हाल, since there is no end marking क्रम the back-to-back
	 * received 'update stats' event, we keep a 3 seconds समयout in हाल,
	 * fw_stats_करोne is not marked yet
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(3 * HZ);

	ath11k_debugfs_fw_stats_reset(ar);

	reinit_completion(&ar->debug.fw_stats_complete);

	ret = ath11k_wmi_send_stats_request_cmd(ar, req_param);

	अगर (ret) अणु
		ath11k_warn(ab, "could not request fw stats (%d)\n",
			    ret);
		वापस ret;
	पूर्ण

	समय_left =
	रुको_क्रम_completion_समयout(&ar->debug.fw_stats_complete,
				    1 * HZ);
	अगर (!समय_left)
		वापस -ETIMEDOUT;

	क्रम (;;) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;

		spin_lock_bh(&ar->data_lock);
		अगर (ar->debug.fw_stats_करोne) अणु
			spin_unlock_bh(&ar->data_lock);
			अवरोध;
		पूर्ण
		spin_unlock_bh(&ar->data_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_खोलो_pdev_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath11k *ar = inode->i_निजी;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा stats_request_params req_param;
	व्योम *buf = शून्य;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ err_unlock;
	पूर्ण

	buf = vदो_स्मृति(ATH11K_FW_STATS_BUF_SIZE);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	req_param.pdev_id = ar->pdev->pdev_id;
	req_param.vdev_id = 0;
	req_param.stats_id = WMI_REQUEST_PDEV_STAT;

	ret = ath11k_debugfs_fw_stats_request(ar, &req_param);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to request fw pdev stats: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	ath11k_wmi_fw_stats_fill(ar, &ar->debug.fw_stats, req_param.stats_id,
				 buf);

	file->निजी_data = buf;

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_मुक्त:
	vमुक्त(buf);

err_unlock:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_release_pdev_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath11k_पढ़ो_pdev_stats(काष्ठा file *file,
				      अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *buf = file->निजी_data;
	माप_प्रकार len = म_माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_pdev_stats = अणु
	.खोलो = ath11k_खोलो_pdev_stats,
	.release = ath11k_release_pdev_stats,
	.पढ़ो = ath11k_पढ़ो_pdev_stats,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ath11k_खोलो_vdev_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath11k *ar = inode->i_निजी;
	काष्ठा stats_request_params req_param;
	व्योम *buf = शून्य;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ err_unlock;
	पूर्ण

	buf = vदो_स्मृति(ATH11K_FW_STATS_BUF_SIZE);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	req_param.pdev_id = ar->pdev->pdev_id;
	/* VDEV stats is always sent क्रम all active VDEVs from FW */
	req_param.vdev_id = 0;
	req_param.stats_id = WMI_REQUEST_VDEV_STAT;

	ret = ath11k_debugfs_fw_stats_request(ar, &req_param);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to request fw vdev stats: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	ath11k_wmi_fw_stats_fill(ar, &ar->debug.fw_stats, req_param.stats_id,
				 buf);

	file->निजी_data = buf;

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_मुक्त:
	vमुक्त(buf);

err_unlock:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_release_vdev_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath11k_पढ़ो_vdev_stats(काष्ठा file *file,
				      अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *buf = file->निजी_data;
	माप_प्रकार len = म_माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_vdev_stats = अणु
	.खोलो = ath11k_खोलो_vdev_stats,
	.release = ath11k_release_vdev_stats,
	.पढ़ो = ath11k_पढ़ो_vdev_stats,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ath11k_खोलो_bcn_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath11k *ar = inode->i_निजी;
	काष्ठा ath11k_vअगर *arvअगर;
	काष्ठा stats_request_params req_param;
	व्योम *buf = शून्य;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ err_unlock;
	पूर्ण

	buf = vदो_स्मृति(ATH11K_FW_STATS_BUF_SIZE);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	req_param.stats_id = WMI_REQUEST_BCN_STAT;
	req_param.pdev_id = ar->pdev->pdev_id;

	/* loop all active VDEVs क्रम bcn stats */
	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		अगर (!arvअगर->is_up)
			जारी;

		req_param.vdev_id = arvअगर->vdev_id;
		ret = ath11k_debugfs_fw_stats_request(ar, &req_param);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to request fw bcn stats: %d\n", ret);
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	ath11k_wmi_fw_stats_fill(ar, &ar->debug.fw_stats, req_param.stats_id,
				 buf);

	/* since beacon stats request is looped क्रम all active VDEVs, saved fw
	 * stats is not मुक्तd क्रम each request until करोne क्रम all active VDEVs
	 */
	spin_lock_bh(&ar->data_lock);
	ath11k_fw_stats_bcn_मुक्त(&ar->debug.fw_stats.bcn);
	spin_unlock_bh(&ar->data_lock);

	file->निजी_data = buf;

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_मुक्त:
	vमुक्त(buf);

err_unlock:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_release_bcn_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath11k_पढ़ो_bcn_stats(काष्ठा file *file,
				     अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *buf = file->निजी_data;
	माप_प्रकार len = म_माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_bcn_stats = अणु
	.खोलो = ath11k_खोलो_bcn_stats,
	.release = ath11k_release_bcn_stats,
	.पढ़ो = ath11k_पढ़ो_bcn_stats,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_पढ़ो_simulate_fw_crash(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर buf[] =
		"To simulate firmware crash write one of the keywords to this file:\n"
		"`assert` - this will send WMI_FORCE_FW_HANG_CMDID to firmware to cause assert.\n"
		"`hw-restart` - this will simply queue hw restart without fw/hw actually crashing.\n";

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, म_माप(buf));
पूर्ण

/* Simulate firmware crash:
 * 'soft': Call wmi command causing firmware hang. This firmware hang is
 * recoverable by warm firmware reset.
 * 'hard': Force firmware crash by setting any vdev parameter क्रम not allowed
 * vdev id. This is hard firmware crash because it is recoverable only by cold
 * firmware reset.
 */
अटल sमाप_प्रकार ath11k_ग_लिखो_simulate_fw_crash(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k_base *ab = file->निजी_data;
	काष्ठा ath11k_pdev *pdev;
	काष्ठा ath11k *ar = ab->pdevs[0].ar;
	अक्षर buf[32] = अणु0पूर्ण;
	sमाप_प्रकार rc;
	पूर्णांक i, ret, radioup = 0;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		अगर (ar && ar->state == ATH11K_STATE_ON) अणु
			radioup = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	/* filter partial ग_लिखोs and invalid commands */
	अगर (*ppos != 0 || count >= माप(buf) || count == 0)
		वापस -EINVAL;

	rc = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos, user_buf, count);
	अगर (rc < 0)
		वापस rc;

	/* drop the possible '\n' from the end */
	अगर (buf[*ppos - 1] == '\n')
		buf[*ppos - 1] = '\0';

	अगर (radioup == 0) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	अगर (!म_भेद(buf, "assert")) अणु
		ath11k_info(ab, "simulating firmware assert crash\n");
		ret = ath11k_wmi_क्रमce_fw_hang_cmd(ar,
						   ATH11K_WMI_FW_HANG_ASSERT_TYPE,
						   ATH11K_WMI_FW_HANG_DELAY);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (ret) अणु
		ath11k_warn(ab, "failed to simulate firmware crash: %d\n", ret);
		जाओ निकास;
	पूर्ण

	ret = count;

निकास:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_simulate_fw_crash = अणु
	.पढ़ो = ath11k_पढ़ो_simulate_fw_crash,
	.ग_लिखो = ath11k_ग_लिखो_simulate_fw_crash,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_ग_लिखो_enable_extd_tx_stats(काष्ठा file *file,
						 स्थिर अक्षर __user *ubuf,
						 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	u32 filter;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक_from_user(ubuf, count, 0, &filter))
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	अगर (filter == ar->debug.extd_tx_stats) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ar->debug.extd_tx_stats = filter;
	ret = count;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath11k_पढ़ो_enable_extd_tx_stats(काष्ठा file *file,
						अक्षर __user *ubuf,
						माप_प्रकार count, loff_t *ppos)

अणु
	अक्षर buf[32] = अणु0पूर्ण;
	काष्ठा ath11k *ar = file->निजी_data;
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%08x\n",
			ar->debug.extd_tx_stats);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_extd_tx_stats = अणु
	.पढ़ो = ath11k_पढ़ो_enable_extd_tx_stats,
	.ग_लिखो = ath11k_ग_लिखो_enable_extd_tx_stats,
	.खोलो = simple_खोलो
पूर्ण;

अटल sमाप_प्रकार ath11k_ग_लिखो_extd_rx_stats(काष्ठा file *file,
					  स्थिर अक्षर __user *ubuf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा htt_rx_ring_tlv_filter tlv_filter = अणु0पूर्ण;
	u32 enable, rx_filter = 0, ring_id;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक_from_user(ubuf, count, 0, &enable))
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	अगर (enable > 1) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (enable == ar->debug.extd_rx_stats) अणु
		ret = count;
		जाओ निकास;
	पूर्ण

	अगर (enable) अणु
		rx_filter =  HTT_RX_FILTER_TLV_FLAGS_MPDU_START;
		rx_filter |= HTT_RX_FILTER_TLV_FLAGS_PPDU_START;
		rx_filter |= HTT_RX_FILTER_TLV_FLAGS_PPDU_END;
		rx_filter |= HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS;
		rx_filter |= HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS_EXT;
		rx_filter |= HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE;

		tlv_filter.rx_filter = rx_filter;
		tlv_filter.pkt_filter_flags0 = HTT_RX_FP_MGMT_FILTER_FLAGS0;
		tlv_filter.pkt_filter_flags1 = HTT_RX_FP_MGMT_FILTER_FLAGS1;
		tlv_filter.pkt_filter_flags2 = HTT_RX_FP_CTRL_FILTER_FLASG2;
		tlv_filter.pkt_filter_flags3 = HTT_RX_FP_CTRL_FILTER_FLASG3 |
			HTT_RX_FP_DATA_FILTER_FLASG3;
	पूर्ण अन्यथा अणु
		tlv_filter = ath11k_mac_mon_status_filter_शेष;
	पूर्ण

	ar->debug.rx_filter = tlv_filter.rx_filter;

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		ring_id = ar->dp.rx_mon_status_refill_ring[i].refill_buf_ring.ring_id;
		ret = ath11k_dp_tx_htt_rx_filter_setup(ar->ab, ring_id, ar->dp.mac_id,
						       HAL_RXDMA_MONITOR_STATUS,
						       DP_RX_BUFFER_SIZE, &tlv_filter);

		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to set rx filter for monitor status ring\n");
			जाओ निकास;
		पूर्ण
	पूर्ण

	ar->debug.extd_rx_stats = enable;
	ret = count;
निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath11k_पढ़ो_extd_rx_stats(काष्ठा file *file,
					 अक्षर __user *ubuf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	अक्षर buf[32];
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%d\n",
			ar->debug.extd_rx_stats);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_extd_rx_stats = अणु
	.पढ़ो = ath11k_पढ़ो_extd_rx_stats,
	.ग_लिखो = ath11k_ग_लिखो_extd_rx_stats,
	.खोलो = simple_खोलो,
पूर्ण;

अटल पूर्णांक ath11k_fill_bp_stats(काष्ठा ath11k_base *ab,
				काष्ठा ath11k_bp_stats *bp_stats,
				अक्षर *buf, पूर्णांक len, पूर्णांक size)
अणु
	lockdep_निश्चित_held(&ab->base_lock);

	len += scnम_लिखो(buf + len, size - len, "count: %u\n",
			 bp_stats->count);
	len += scnम_लिखो(buf + len, size - len, "hp: %u\n",
			 bp_stats->hp);
	len += scnम_लिखो(buf + len, size - len, "tp: %u\n",
			 bp_stats->tp);
	len += scnम_लिखो(buf + len, size - len, "seen before: %ums\n\n",
			 jअगरfies_to_msecs(jअगरfies - bp_stats->jअगरfies));
	वापस len;
पूर्ण

अटल sमाप_प्रकार ath11k_debugfs_dump_soc_ring_bp_stats(काष्ठा ath11k_base *ab,
						     अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा ath11k_bp_stats *bp_stats;
	bool stats_rxd = false;
	u8 i, pdev_idx;
	पूर्णांक len = 0;

	len += scnम_लिखो(buf + len, size - len, "\nBackpressure Stats\n");
	len += scnम_लिखो(buf + len, size - len, "==================\n");

	spin_lock_bh(&ab->base_lock);
	क्रम (i = 0; i < HTT_SW_UMAC_RING_IDX_MAX; i++) अणु
		bp_stats = &ab->soc_stats.bp_stats.umac_ring_bp_stats[i];

		अगर (!bp_stats->count)
			जारी;

		len += scnम_लिखो(buf + len, size - len, "Ring: %s\n",
				 htt_bp_umac_ring[i]);
		len = ath11k_fill_bp_stats(ab, bp_stats, buf, len, size);
		stats_rxd = true;
	पूर्ण

	क्रम (i = 0; i < HTT_SW_LMAC_RING_IDX_MAX; i++) अणु
		क्रम (pdev_idx = 0; pdev_idx < MAX_RADIOS; pdev_idx++) अणु
			bp_stats =
				&ab->soc_stats.bp_stats.lmac_ring_bp_stats[i][pdev_idx];

			अगर (!bp_stats->count)
				जारी;

			len += scnम_लिखो(buf + len, size - len, "Ring: %s\n",
					 htt_bp_lmac_ring[i]);
			len += scnम_लिखो(buf + len, size - len, "pdev: %d\n",
					 pdev_idx);
			len = ath11k_fill_bp_stats(ab, bp_stats, buf, len, size);
			stats_rxd = true;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ab->base_lock);

	अगर (!stats_rxd)
		len += scnम_लिखो(buf + len, size - len,
				 "No Ring Backpressure stats received\n\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार ath11k_debugfs_dump_soc_dp_stats(काष्ठा file *file,
						अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k_base *ab = file->निजी_data;
	काष्ठा ath11k_soc_dp_stats *soc_stats = &ab->soc_stats;
	पूर्णांक len = 0, i, retval;
	स्थिर पूर्णांक size = 4096;
	अटल स्थिर अक्षर *rxdma_err[HAL_REO_ENTR_RING_RXDMA_ECODE_MAX] = अणु
			"Overflow", "MPDU len", "FCS", "Decrypt", "TKIP MIC",
			"Unencrypt", "MSDU len", "MSDU limit", "WiFi parse",
			"AMSDU parse", "SA timeout", "DA timeout",
			"Flow timeout", "Flush req"पूर्ण;
	अटल स्थिर अक्षर *reo_err[HAL_REO_DEST_RING_ERROR_CODE_MAX] = अणु
			"Desc addr zero", "Desc inval", "AMPDU in non BA",
			"Non BA dup", "BA dup", "Frame 2k jump", "BAR 2k jump",
			"Frame OOR", "BAR OOR", "No BA session",
			"Frame SN equal SSN", "PN check fail", "2k err",
			"PN err", "Desc blocked"पूर्ण;

	अक्षर *buf;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, size - len, "SOC RX STATS:\n\n");
	len += scnम_लिखो(buf + len, size - len, "err ring pkts: %u\n",
			 soc_stats->err_ring_pkts);
	len += scnम_लिखो(buf + len, size - len, "Invalid RBM: %u\n\n",
			 soc_stats->invalid_rbm);
	len += scnम_लिखो(buf + len, size - len, "RXDMA errors:\n");
	क्रम (i = 0; i < HAL_REO_ENTR_RING_RXDMA_ECODE_MAX; i++)
		len += scnम_लिखो(buf + len, size - len, "%s: %u\n",
				 rxdma_err[i], soc_stats->rxdma_error[i]);

	len += scnम_लिखो(buf + len, size - len, "\nREO errors:\n");
	क्रम (i = 0; i < HAL_REO_DEST_RING_ERROR_CODE_MAX; i++)
		len += scnम_लिखो(buf + len, size - len, "%s: %u\n",
				 reo_err[i], soc_stats->reo_error[i]);

	len += scnम_लिखो(buf + len, size - len, "\nHAL REO errors:\n");
	len += scnम_लिखो(buf + len, size - len,
			 "ring0: %u\nring1: %u\nring2: %u\nring3: %u\n",
			 soc_stats->hal_reo_error[0],
			 soc_stats->hal_reo_error[1],
			 soc_stats->hal_reo_error[2],
			 soc_stats->hal_reo_error[3]);

	len += scnम_लिखो(buf + len, size - len, "\nSOC TX STATS:\n");
	len += scnम_लिखो(buf + len, size - len, "\nTCL Ring Full Failures:\n");

	क्रम (i = 0; i < DP_TCL_NUM_RING_MAX; i++)
		len += scnम_लिखो(buf + len, size - len, "ring%d: %u\n",
				 i, soc_stats->tx_err.desc_na[i]);

	len += scnम_लिखो(buf + len, size - len,
			 "\nMisc Transmit Failures: %d\n",
			 atomic_पढ़ो(&soc_stats->tx_err.misc_fail));

	len += ath11k_debugfs_dump_soc_ring_bp_stats(ab, buf + len, size - len);

	अगर (len > size)
		len = size;
	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_soc_dp_stats = अणु
	.पढ़ो = ath11k_debugfs_dump_soc_dp_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

पूर्णांक ath11k_debugfs_pdev_create(काष्ठा ath11k_base *ab)
अणु
	अगर (test_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags))
		वापस 0;

	ab->debugfs_soc = debugfs_create_dir(ab->hw_params.name, ab->debugfs_ath11k);
	अगर (IS_ERR(ab->debugfs_soc))
		वापस PTR_ERR(ab->debugfs_soc);

	debugfs_create_file("simulate_fw_crash", 0600, ab->debugfs_soc, ab,
			    &fops_simulate_fw_crash);

	debugfs_create_file("soc_dp_stats", 0600, ab->debugfs_soc, ab,
			    &fops_soc_dp_stats);

	वापस 0;
पूर्ण

व्योम ath11k_debugfs_pdev_destroy(काष्ठा ath11k_base *ab)
अणु
	debugfs_हटाओ_recursive(ab->debugfs_soc);
	ab->debugfs_soc = शून्य;
पूर्ण

पूर्णांक ath11k_debugfs_soc_create(काष्ठा ath11k_base *ab)
अणु
	ab->debugfs_ath11k = debugfs_create_dir("ath11k", शून्य);

	वापस PTR_ERR_OR_ZERO(ab->debugfs_ath11k);
पूर्ण

व्योम ath11k_debugfs_soc_destroy(काष्ठा ath11k_base *ab)
अणु
	debugfs_हटाओ_recursive(ab->debugfs_ath11k);
	ab->debugfs_ath11k = शून्य;
पूर्ण
EXPORT_SYMBOL(ath11k_debugfs_soc_destroy);

व्योम ath11k_debugfs_fw_stats_init(काष्ठा ath11k *ar)
अणु
	काष्ठा dentry *fwstats_dir = debugfs_create_dir("fw_stats",
							ar->debug.debugfs_pdev);

	ar->debug.fw_stats.debugfs_fwstats = fwstats_dir;

	/* all stats debugfs files created are under "fw_stats" directory
	 * created per PDEV
	 */
	debugfs_create_file("pdev_stats", 0600, fwstats_dir, ar,
			    &fops_pdev_stats);
	debugfs_create_file("vdev_stats", 0600, fwstats_dir, ar,
			    &fops_vdev_stats);
	debugfs_create_file("beacon_stats", 0600, fwstats_dir, ar,
			    &fops_bcn_stats);

	INIT_LIST_HEAD(&ar->debug.fw_stats.pdevs);
	INIT_LIST_HEAD(&ar->debug.fw_stats.vdevs);
	INIT_LIST_HEAD(&ar->debug.fw_stats.bcn);

	init_completion(&ar->debug.fw_stats_complete);
पूर्ण

अटल sमाप_प्रकार ath11k_ग_लिखो_pktlog_filter(काष्ठा file *file,
					  स्थिर अक्षर __user *ubuf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा htt_rx_ring_tlv_filter tlv_filter = अणु0पूर्ण;
	u32 rx_filter = 0, ring_id, filter, mode;
	u8 buf[128] = अणु0पूर्ण;
	पूर्णांक i, ret;
	sमाप_प्रकार rc;

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	rc = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos, ubuf, count);
	अगर (rc < 0) अणु
		ret = rc;
		जाओ out;
	पूर्ण
	buf[rc] = '\0';

	ret = माला_पूछो(buf, "0x%x %u", &filter, &mode);
	अगर (ret != 2) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (filter) अणु
		ret = ath11k_wmi_pdev_pktlog_enable(ar, filter);
		अगर (ret) अणु
			ath11k_warn(ar->ab,
				    "failed to enable pktlog filter %x: %d\n",
				    ar->debug.pktlog_filter, ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ath11k_wmi_pdev_pktlog_disable(ar);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to disable pktlog: %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

#घोषणा HTT_RX_FILTER_TLV_LITE_MODE \
			(HTT_RX_FILTER_TLV_FLAGS_PPDU_START | \
			HTT_RX_FILTER_TLV_FLAGS_PPDU_END | \
			HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS | \
			HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS_EXT | \
			HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE | \
			HTT_RX_FILTER_TLV_FLAGS_MPDU_START)

	अगर (mode == ATH11K_PKTLOG_MODE_FULL) अणु
		rx_filter = HTT_RX_FILTER_TLV_LITE_MODE |
			    HTT_RX_FILTER_TLV_FLAGS_MSDU_START |
			    HTT_RX_FILTER_TLV_FLAGS_MSDU_END |
			    HTT_RX_FILTER_TLV_FLAGS_MPDU_END |
			    HTT_RX_FILTER_TLV_FLAGS_PACKET_HEADER |
			    HTT_RX_FILTER_TLV_FLAGS_ATTENTION;
	पूर्ण अन्यथा अगर (mode == ATH11K_PKTLOG_MODE_LITE) अणु
		ret = ath11k_dp_tx_htt_h2t_ppdu_stats_req(ar,
							  HTT_PPDU_STATS_TAG_PKTLOG);
		अगर (ret) अणु
			ath11k_err(ar->ab, "failed to enable pktlog lite: %d\n", ret);
			जाओ out;
		पूर्ण

		rx_filter = HTT_RX_FILTER_TLV_LITE_MODE;
	पूर्ण अन्यथा अणु
		ret = ath11k_dp_tx_htt_h2t_ppdu_stats_req(ar,
							  HTT_PPDU_STATS_TAG_DEFAULT);
		अगर (ret) अणु
			ath11k_err(ar->ab, "failed to send htt ppdu stats req: %d\n",
				   ret);
			जाओ out;
		पूर्ण
	पूर्ण

	tlv_filter.rx_filter = rx_filter;
	अगर (rx_filter) अणु
		tlv_filter.pkt_filter_flags0 = HTT_RX_FP_MGMT_FILTER_FLAGS0;
		tlv_filter.pkt_filter_flags1 = HTT_RX_FP_MGMT_FILTER_FLAGS1;
		tlv_filter.pkt_filter_flags2 = HTT_RX_FP_CTRL_FILTER_FLASG2;
		tlv_filter.pkt_filter_flags3 = HTT_RX_FP_CTRL_FILTER_FLASG3 |
					       HTT_RX_FP_DATA_FILTER_FLASG3;
	पूर्ण

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		ring_id = ar->dp.rx_mon_status_refill_ring[i].refill_buf_ring.ring_id;
		ret = ath11k_dp_tx_htt_rx_filter_setup(ab, ring_id,
						       ar->dp.mac_id + i,
						       HAL_RXDMA_MONITOR_STATUS,
						       DP_RX_BUFFER_SIZE, &tlv_filter);

		अगर (ret) अणु
			ath11k_warn(ab, "failed to set rx filter for monitor status ring\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI, "pktlog filter %d mode %s\n",
		   filter, ((mode == ATH11K_PKTLOG_MODE_FULL) ? "full" : "lite"));

	ar->debug.pktlog_filter = filter;
	ar->debug.pktlog_mode = mode;
	ret = count;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath11k_पढ़ो_pktlog_filter(काष्ठा file *file,
					 अक्षर __user *ubuf,
					 माप_प्रकार count, loff_t *ppos)

अणु
	अक्षर buf[32] = अणु0पूर्ण;
	काष्ठा ath11k *ar = file->निजी_data;
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%08x %08x\n",
			ar->debug.pktlog_filter,
			ar->debug.pktlog_mode);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_pktlog_filter = अणु
	.पढ़ो = ath11k_पढ़ो_pktlog_filter,
	.ग_लिखो = ath11k_ग_लिखो_pktlog_filter,
	.खोलो = simple_खोलो
पूर्ण;

अटल sमाप_प्रकार ath11k_ग_लिखो_simulate_radar(काष्ठा file *file,
					   स्थिर अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	पूर्णांक ret;

	ret = ath11k_wmi_simulate_radar(ar);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_simulate_radar = अणु
	.ग_लिखो = ath11k_ग_लिखो_simulate_radar,
	.खोलो = simple_खोलो
पूर्ण;

पूर्णांक ath11k_debugfs_रेजिस्टर(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	अक्षर pdev_name[5];
	अक्षर buf[100] = अणु0पूर्ण;

	snम_लिखो(pdev_name, माप(pdev_name), "%s%d", "mac", ar->pdev_idx);

	ar->debug.debugfs_pdev = debugfs_create_dir(pdev_name, ab->debugfs_soc);
	अगर (IS_ERR(ar->debug.debugfs_pdev))
		वापस PTR_ERR(ar->debug.debugfs_pdev);

	/* Create a symlink under ieee80211/phy* */
	snम_लिखो(buf, 100, "../../ath11k/%pd2", ar->debug.debugfs_pdev);
	debugfs_create_symlink("ath11k", ar->hw->wiphy->debugfsdir, buf);

	ath11k_debugfs_htt_stats_init(ar);

	ath11k_debugfs_fw_stats_init(ar);

	debugfs_create_file("ext_tx_stats", 0644,
			    ar->debug.debugfs_pdev, ar,
			    &fops_extd_tx_stats);
	debugfs_create_file("ext_rx_stats", 0644,
			    ar->debug.debugfs_pdev, ar,
			    &fops_extd_rx_stats);
	debugfs_create_file("pktlog_filter", 0644,
			    ar->debug.debugfs_pdev, ar,
			    &fops_pktlog_filter);

	अगर (ar->hw->wiphy->bands[NL80211_BAND_5GHZ]) अणु
		debugfs_create_file("dfs_simulate_radar", 0200,
				    ar->debug.debugfs_pdev, ar,
				    &fops_simulate_radar);
		debugfs_create_bool("dfs_block_radar_events", 0200,
				    ar->debug.debugfs_pdev,
				    &ar->dfs_block_radar_events);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath11k_debugfs_unरेजिस्टर(काष्ठा ath11k *ar)
अणु
पूर्ण
