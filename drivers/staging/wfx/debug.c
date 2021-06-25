<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Debugfs पूर्णांकerface.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/crc32.h>

#समावेश "debug.h"
#समावेश "wfx.h"
#समावेश "sta.h"
#समावेश "main.h"
#समावेश "hif_tx.h"
#समावेश "hif_tx_mib.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "traces.h"

अटल स्थिर काष्ठा trace_prपूर्णांक_flags hअगर_msg_prपूर्णांक_map[] = अणु
	hअगर_msg_list,
पूर्ण;

अटल स्थिर काष्ठा trace_prपूर्णांक_flags hअगर_mib_prपूर्णांक_map[] = अणु
	hअगर_mib_list,
पूर्ण;

अटल स्थिर काष्ठा trace_prपूर्णांक_flags wfx_reg_prपूर्णांक_map[] = अणु
	wfx_reg_list,
पूर्ण;

अटल स्थिर अक्षर *get_symbol(अचिन्हित दीर्घ val,
			      स्थिर काष्ठा trace_prपूर्णांक_flags *symbol_array)
अणु
	पूर्णांक i;

	क्रम (i = 0; symbol_array[i].mask != -1; i++) अणु
		अगर (val == symbol_array[i].mask)
			वापस symbol_array[i].name;
	पूर्ण

	वापस "unknown";
पूर्ण

स्थिर अक्षर *get_hअगर_name(अचिन्हित दीर्घ id)
अणु
	वापस get_symbol(id, hअगर_msg_prपूर्णांक_map);
पूर्ण

स्थिर अक्षर *get_mib_name(अचिन्हित दीर्घ id)
अणु
	वापस get_symbol(id, hअगर_mib_prपूर्णांक_map);
पूर्ण

स्थिर अक्षर *get_reg_name(अचिन्हित दीर्घ id)
अणु
	वापस get_symbol(id, wfx_reg_prपूर्णांक_map);
पूर्ण

अटल पूर्णांक wfx_counters_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक ret, i;
	काष्ठा wfx_dev *wdev = seq->निजी;
	काष्ठा hअगर_mib_extended_count_table counters[3];

	क्रम (i = 0; i < ARRAY_SIZE(counters); i++) अणु
		ret = hअगर_get_counters_table(wdev, i, counters + i);
		अगर (ret < 0)
			वापस ret;
		अगर (ret > 0)
			वापस -EIO;
	पूर्ण

	seq_म_लिखो(seq, "%-24s %12s %12s %12s\n",
		   "", "global", "iface 0", "iface 1");

#घोषणा PUT_COUNTER(name) \
	seq_म_लिखो(seq, "%-24s %12d %12d %12d\n", #name, \
		   le32_to_cpu(counters[2].count_##name), \
		   le32_to_cpu(counters[0].count_##name), \
		   le32_to_cpu(counters[1].count_##name))

	PUT_COUNTER(tx_packets);
	PUT_COUNTER(tx_multicast_frames);
	PUT_COUNTER(tx_frames_success);
	PUT_COUNTER(tx_frame_failures);
	PUT_COUNTER(tx_frames_retried);
	PUT_COUNTER(tx_frames_multi_retried);

	PUT_COUNTER(rts_success);
	PUT_COUNTER(rts_failures);
	PUT_COUNTER(ack_failures);

	PUT_COUNTER(rx_packets);
	PUT_COUNTER(rx_frames_success);
	PUT_COUNTER(rx_packet_errors);
	PUT_COUNTER(plcp_errors);
	PUT_COUNTER(fcs_errors);
	PUT_COUNTER(rx_decryption_failures);
	PUT_COUNTER(rx_mic_failures);
	PUT_COUNTER(rx_no_key_failures);
	PUT_COUNTER(rx_frame_duplicates);
	PUT_COUNTER(rx_multicast_frames);
	PUT_COUNTER(rx_cmacicv_errors);
	PUT_COUNTER(rx_cmac_replays);
	PUT_COUNTER(rx_mgmt_ccmp_replays);

	PUT_COUNTER(rx_beacon);
	PUT_COUNTER(miss_beacon);

#अघोषित PUT_COUNTER

	क्रम (i = 0; i < ARRAY_SIZE(counters[0].reserved); i++)
		seq_म_लिखो(seq, "reserved[%02d]%12s %12d %12d %12d\n", i, "",
			   le32_to_cpu(counters[2].reserved[i]),
			   le32_to_cpu(counters[0].reserved[i]),
			   le32_to_cpu(counters[1].reserved[i]));

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(wfx_counters);

अटल स्थिर अक्षर * स्थिर channel_names[] = अणु
	[0] = "1M",
	[1] = "2M",
	[2] = "5.5M",
	[3] = "11M",
	/* Entries 4 and 5 करोes not exist */
	[6] = "6M",
	[7] = "9M",
	[8] = "12M",
	[9] = "18M",
	[10] = "24M",
	[11] = "36M",
	[12] = "48M",
	[13] = "54M",
	[14] = "MCS0",
	[15] = "MCS1",
	[16] = "MCS2",
	[17] = "MCS3",
	[18] = "MCS4",
	[19] = "MCS5",
	[20] = "MCS6",
	[21] = "MCS7",
पूर्ण;

अटल पूर्णांक wfx_rx_stats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा wfx_dev *wdev = seq->निजी;
	काष्ठा hअगर_rx_stats *st = &wdev->rx_stats;
	पूर्णांक i;

	mutex_lock(&wdev->rx_stats_lock);
	seq_म_लिखो(seq, "Timestamp: %dus\n", st->date);
	seq_म_लिखो(seq, "Low power clock: frequency %uHz, external %s\n",
		   le32_to_cpu(st->pwr_clk_freq),
		   st->is_ext_pwr_clk ? "yes" : "no");
	seq_म_लिखो(seq,
		   "Num. of frames: %d, PER (x10e4): %d, Throughput: %dKbps/s\n",
		   st->nb_rx_frame, st->per_total, st->throughput);
	seq_माला_दो(seq, "       Num. of      PER     RSSI      SNR      CFO\n");
	seq_माला_दो(seq, "        frames  (x10e4)    (dBm)     (dB)    (kHz)\n");
	क्रम (i = 0; i < ARRAY_SIZE(channel_names); i++) अणु
		अगर (channel_names[i])
			seq_म_लिखो(seq, "%5s %8d %8d %8d %8d %8d\n",
				   channel_names[i],
				   le32_to_cpu(st->nb_rx_by_rate[i]),
				   le16_to_cpu(st->per[i]),
				   (s16)le16_to_cpu(st->rssi[i]) / 100,
				   (s16)le16_to_cpu(st->snr[i]) / 100,
				   (s16)le16_to_cpu(st->cfo[i]));
	पूर्ण
	mutex_unlock(&wdev->rx_stats_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(wfx_rx_stats);

अटल पूर्णांक wfx_tx_घातer_loop_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा wfx_dev *wdev = seq->निजी;
	काष्ठा hअगर_tx_घातer_loop_info *st = &wdev->tx_घातer_loop_info;
	पूर्णांक पंचांगp;

	mutex_lock(&wdev->tx_घातer_loop_info_lock);
	पंचांगp = le16_to_cpu(st->tx_gain_dig);
	seq_म_लिखो(seq, "Tx gain digital: %d\n", पंचांगp);
	पंचांगp = le16_to_cpu(st->tx_gain_pa);
	seq_म_लिखो(seq, "Tx gain PA: %d\n", पंचांगp);
	पंचांगp = (s16)le16_to_cpu(st->target_pout);
	seq_म_लिखो(seq, "Target Pout: %d.%02d dBm\n", पंचांगp / 4, (पंचांगp % 4) * 25);
	पंचांगp = (s16)le16_to_cpu(st->p_estimation);
	seq_म_लिखो(seq, "FEM Pout: %d.%02d dBm\n", पंचांगp / 4, (पंचांगp % 4) * 25);
	पंचांगp = le16_to_cpu(st->vpdet);
	seq_म_लिखो(seq, "Vpdet: %d mV\n", पंचांगp);
	seq_म_लिखो(seq, "Measure index: %d\n", st->measurement_index);
	mutex_unlock(&wdev->tx_घातer_loop_info_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(wfx_tx_घातer_loop);

अटल sमाप_प्रकार wfx_send_pds_ग_लिखो(काष्ठा file *file,
				  स्थिर अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wfx_dev *wdev = file->निजी_data;
	अक्षर *buf;
	पूर्णांक ret;

	अगर (*ppos != 0) अणु
		dev_dbg(wdev->dev, "PDS data must be written in one transaction");
		वापस -EBUSY;
	पूर्ण
	buf = memdup_user(user_buf, count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);
	*ppos = *ppos + count;
	ret = wfx_send_pds(wdev, buf, count);
	kमुक्त(buf);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations wfx_send_pds_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = wfx_send_pds_ग_लिखो,
पूर्ण;

काष्ठा dbgfs_hअगर_msg अणु
	काष्ठा wfx_dev *wdev;
	काष्ठा completion complete;
	u8 reply[1024];
	पूर्णांक ret;
पूर्ण;

अटल sमाप_प्रकार wfx_send_hअगर_msg_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dbgfs_hअगर_msg *context = file->निजी_data;
	काष्ठा wfx_dev *wdev = context->wdev;
	काष्ठा hअगर_msg *request;

	अगर (completion_करोne(&context->complete)) अणु
		dev_dbg(wdev->dev, "read previous result before start a new one\n");
		वापस -EBUSY;
	पूर्ण
	अगर (count < माप(काष्ठा hअगर_msg))
		वापस -EINVAL;

	// wfx_cmd_send() checks that reply buffer is wide enough, but करोes not
	// वापस precise length पढ़ो. User have to know how many bytes should
	// be पढ़ो. Filling reply buffer with a memory pattern may help user.
	स_रखो(context->reply, 0xFF, माप(context->reply));
	request = memdup_user(user_buf, count);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	अगर (le16_to_cpu(request->len) != count) अणु
		kमुक्त(request);
		वापस -EINVAL;
	पूर्ण
	context->ret = wfx_cmd_send(wdev, request, context->reply,
				    माप(context->reply), false);

	kमुक्त(request);
	complete(&context->complete);
	वापस count;
पूर्ण

अटल sमाप_प्रकार wfx_send_hअगर_msg_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dbgfs_hअगर_msg *context = file->निजी_data;
	पूर्णांक ret;

	अगर (count > माप(context->reply))
		वापस -EINVAL;
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&context->complete);
	अगर (ret)
		वापस ret;
	अगर (context->ret < 0)
		वापस context->ret;
	// Be careful, ग_लिखो() is रुकोing क्रम a full message जबतक पढ़ो()
	// only वापसs a payload
	अगर (copy_to_user(user_buf, context->reply, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल पूर्णांक wfx_send_hअगर_msg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dbgfs_hअगर_msg *context = kzalloc(माप(*context), GFP_KERNEL);

	अगर (!context)
		वापस -ENOMEM;
	context->wdev = inode->i_निजी;
	init_completion(&context->complete);
	file->निजी_data = context;
	वापस 0;
पूर्ण

अटल पूर्णांक wfx_send_hअगर_msg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dbgfs_hअगर_msg *context = file->निजी_data;

	kमुक्त(context);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations wfx_send_hअगर_msg_fops = अणु
	.खोलो = wfx_send_hअगर_msg_खोलो,
	.release = wfx_send_hअगर_msg_release,
	.ग_लिखो = wfx_send_hअगर_msg_ग_लिखो,
	.पढ़ो = wfx_send_hअगर_msg_पढ़ो,
पूर्ण;

अटल पूर्णांक wfx_ps_समयout_set(व्योम *data, u64 val)
अणु
	काष्ठा wfx_dev *wdev = (काष्ठा wfx_dev *)data;
	काष्ठा wfx_vअगर *wvअगर;

	wdev->क्रमce_ps_समयout = val;
	wvअगर = शून्य;
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य)
		wfx_update_pm(wvअगर);
	वापस 0;
पूर्ण

अटल पूर्णांक wfx_ps_समयout_get(व्योम *data, u64 *val)
अणु
	काष्ठा wfx_dev *wdev = (काष्ठा wfx_dev *)data;

	*val = wdev->क्रमce_ps_समयout;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(wfx_ps_समयout_fops, wfx_ps_समयout_get, wfx_ps_समयout_set, "%lld\n");

पूर्णांक wfx_debug_init(काष्ठा wfx_dev *wdev)
अणु
	काष्ठा dentry *d;

	d = debugfs_create_dir("wfx", wdev->hw->wiphy->debugfsdir);
	debugfs_create_file("counters", 0444, d, wdev, &wfx_counters_fops);
	debugfs_create_file("rx_stats", 0444, d, wdev, &wfx_rx_stats_fops);
	debugfs_create_file("tx_power_loop", 0444, d, wdev,
			    &wfx_tx_घातer_loop_fops);
	debugfs_create_file("send_pds", 0200, d, wdev, &wfx_send_pds_fops);
	debugfs_create_file("send_hif_msg", 0600, d, wdev,
			    &wfx_send_hअगर_msg_fops);
	debugfs_create_file("ps_timeout", 0600, d, wdev, &wfx_ps_समयout_fops);

	वापस 0;
पूर्ण
