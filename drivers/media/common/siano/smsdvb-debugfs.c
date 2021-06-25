<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright(c) 2013 Mauro Carvalho Chehab

#समावेश "smscoreapi.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>

#समावेश "smsdvb.h"

अटल काष्ठा dentry *smsdvb_debugfs_usb_root;

काष्ठा smsdvb_debugfs अणु
	काष्ठा kref		refcount;
	spinlock_t		lock;

	अक्षर			stats_data[PAGE_SIZE];
	अचिन्हित		stats_count;
	bool			stats_was_पढ़ो;

	रुको_queue_head_t	stats_queue;
पूर्ण;

अटल व्योम smsdvb_prपूर्णांक_dvb_stats(काष्ठा smsdvb_debugfs *debug_data,
			    काष्ठा sms_stats *p)
अणु
	पूर्णांक n = 0;
	अक्षर *buf;

	spin_lock(&debug_data->lock);
	अगर (debug_data->stats_count) अणु
		spin_unlock(&debug_data->lock);
		वापस;
	पूर्ण

	buf = debug_data->stats_data;

	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_rf_locked = %d\n", p->is_rf_locked);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_demod_locked = %d\n", p->is_demod_locked);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_external_lna_on = %d\n", p->is_बाह्यal_lna_on);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "SNR = %d\n", p->SNR);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "ber = %d\n", p->ber);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "FIB_CRC = %d\n", p->FIB_CRC);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "ts_per = %d\n", p->ts_per);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "MFER = %d\n", p->MFER);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "RSSI = %d\n", p->RSSI);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "in_band_pwr = %d\n", p->in_band_pwr);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "carrier_offset = %d\n", p->carrier_offset);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "modem_state = %d\n", p->modem_state);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "frequency = %d\n", p->frequency);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "bandwidth = %d\n", p->bandwidth);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "transmission_mode = %d\n", p->transmission_mode);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "modem_state = %d\n", p->modem_state);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "guard_interval = %d\n", p->guard_पूर्णांकerval);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "code_rate = %d\n", p->code_rate);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "lp_code_rate = %d\n", p->lp_code_rate);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "hierarchy = %d\n", p->hierarchy);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "constellation = %d\n", p->स्थिरellation);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "burst_size = %d\n", p->burst_size);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "burst_duration = %d\n", p->burst_duration);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "burst_cycle_time = %d\n", p->burst_cycle_समय);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "calc_burst_cycle_time = %d\n",
		      p->calc_burst_cycle_समय);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_rows = %d\n", p->num_of_rows);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_padd_cols = %d\n", p->num_of_padd_cols);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_punct_cols = %d\n", p->num_of_punct_cols);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "error_ts_packets = %d\n", p->error_ts_packets);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "total_ts_packets = %d\n", p->total_ts_packets);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_valid_mpe_tlbs = %d\n", p->num_of_valid_mpe_tlbs);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_invalid_mpe_tlbs = %d\n", p->num_of_invalid_mpe_tlbs);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_corrected_mpe_tlbs = %d\n", p->num_of_corrected_mpe_tlbs);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "ber_error_count = %d\n", p->ber_error_count);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "ber_bit_count = %d\n", p->ber_bit_count);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "sms_to_host_tx_errors = %d\n", p->sms_to_host_tx_errors);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "pre_ber = %d\n", p->pre_ber);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "cell_id = %d\n", p->cell_id);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "dvbh_srv_ind_hp = %d\n", p->dvbh_srv_ind_hp);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "dvbh_srv_ind_lp = %d\n", p->dvbh_srv_ind_lp);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_mpe_received = %d\n", p->num_mpe_received);

	debug_data->stats_count = n;
	spin_unlock(&debug_data->lock);
	wake_up(&debug_data->stats_queue);
पूर्ण

अटल व्योम smsdvb_prपूर्णांक_isdb_stats(काष्ठा smsdvb_debugfs *debug_data,
			     काष्ठा sms_isdbt_stats *p)
अणु
	पूर्णांक i, n = 0;
	अक्षर *buf;

	spin_lock(&debug_data->lock);
	अगर (debug_data->stats_count) अणु
		spin_unlock(&debug_data->lock);
		वापस;
	पूर्ण

	buf = debug_data->stats_data;

	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "statistics_type = %d\t", p->statistics_type);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "full_size = %d\n", p->full_size);

	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_rf_locked = %d\t\t", p->is_rf_locked);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_demod_locked = %d\t", p->is_demod_locked);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_external_lna_on = %d\n", p->is_बाह्यal_lna_on);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "SNR = %d dB\t\t", p->SNR);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "RSSI = %d dBm\t\t", p->RSSI);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "in_band_pwr = %d dBm\n", p->in_band_pwr);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "carrier_offset = %d\t", p->carrier_offset);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "bandwidth = %d\t\t", p->bandwidth);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "frequency = %d Hz\n", p->frequency);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "transmission_mode = %d\t", p->transmission_mode);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "modem_state = %d\t\t", p->modem_state);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "guard_interval = %d\n", p->guard_पूर्णांकerval);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "system_type = %d\t\t", p->प्रणाली_type);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "partial_reception = %d\t", p->partial_reception);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_layers = %d\n", p->num_of_layers);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "sms_to_host_tx_errors = %d\n", p->sms_to_host_tx_errors);

	क्रम (i = 0; i < 3; i++) अणु
		अगर (p->layer_info[i].number_of_segments < 1 ||
		    p->layer_info[i].number_of_segments > 13)
			जारी;

		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\nLayer %d\n", i);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tcode_rate = %d\t",
			      p->layer_info[i].code_rate);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "constellation = %d\n",
			      p->layer_info[i].स्थिरellation);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tber = %-5d\t",
			      p->layer_info[i].ber);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "\tber_error_count = %-5d\t",
			      p->layer_info[i].ber_error_count);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "ber_bit_count = %-5d\n",
			      p->layer_info[i].ber_bit_count);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tpre_ber = %-5d\t",
			      p->layer_info[i].pre_ber);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tts_per = %-5d\n",
			      p->layer_info[i].ts_per);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "\terror_ts_packets = %-5d\t",
			      p->layer_info[i].error_ts_packets);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "total_ts_packets = %-5d\t",
			      p->layer_info[i].total_ts_packets);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "ti_ldepth_i = %d\n",
			      p->layer_info[i].ti_ldepth_i);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "\tnumber_of_segments = %d\t",
			      p->layer_info[i].number_of_segments);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "tmcc_errors = %d\n",
			      p->layer_info[i].पंचांगcc_errors);
	पूर्ण

	debug_data->stats_count = n;
	spin_unlock(&debug_data->lock);
	wake_up(&debug_data->stats_queue);
पूर्ण

अटल व्योम smsdvb_prपूर्णांक_isdb_stats_ex(काष्ठा smsdvb_debugfs *debug_data,
				काष्ठा sms_isdbt_stats_ex *p)
अणु
	पूर्णांक i, n = 0;
	अक्षर *buf;

	spin_lock(&debug_data->lock);
	अगर (debug_data->stats_count) अणु
		spin_unlock(&debug_data->lock);
		वापस;
	पूर्ण

	buf = debug_data->stats_data;

	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "statistics_type = %d\t", p->statistics_type);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "full_size = %d\n", p->full_size);

	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_rf_locked = %d\t\t", p->is_rf_locked);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_demod_locked = %d\t", p->is_demod_locked);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "is_external_lna_on = %d\n", p->is_बाह्यal_lna_on);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "SNR = %d dB\t\t", p->SNR);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "RSSI = %d dBm\t\t", p->RSSI);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "in_band_pwr = %d dBm\n", p->in_band_pwr);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "carrier_offset = %d\t", p->carrier_offset);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "bandwidth = %d\t\t", p->bandwidth);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "frequency = %d Hz\n", p->frequency);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "transmission_mode = %d\t", p->transmission_mode);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "modem_state = %d\t\t", p->modem_state);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "guard_interval = %d\n", p->guard_पूर्णांकerval);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "system_type = %d\t\t", p->प्रणाली_type);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "partial_reception = %d\t", p->partial_reception);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
		      "num_of_layers = %d\n", p->num_of_layers);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "segment_number = %d\t",
		      p->segment_number);
	n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "tune_bw = %d\n",
		      p->tune_bw);

	क्रम (i = 0; i < 3; i++) अणु
		अगर (p->layer_info[i].number_of_segments < 1 ||
		    p->layer_info[i].number_of_segments > 13)
			जारी;

		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\nLayer %d\n", i);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tcode_rate = %d\t",
			      p->layer_info[i].code_rate);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "constellation = %d\n",
			      p->layer_info[i].स्थिरellation);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tber = %-5d\t",
			      p->layer_info[i].ber);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "\tber_error_count = %-5d\t",
			      p->layer_info[i].ber_error_count);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "ber_bit_count = %-5d\n",
			      p->layer_info[i].ber_bit_count);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tpre_ber = %-5d\t",
			      p->layer_info[i].pre_ber);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "\tts_per = %-5d\n",
			      p->layer_info[i].ts_per);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "\terror_ts_packets = %-5d\t",
			      p->layer_info[i].error_ts_packets);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "total_ts_packets = %-5d\t",
			      p->layer_info[i].total_ts_packets);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "ti_ldepth_i = %d\n",
			      p->layer_info[i].ti_ldepth_i);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n,
			      "\tnumber_of_segments = %d\t",
			      p->layer_info[i].number_of_segments);
		n += scnम_लिखो(&buf[n], PAGE_SIZE - n, "tmcc_errors = %d\n",
			      p->layer_info[i].पंचांगcc_errors);
	पूर्ण


	debug_data->stats_count = n;
	spin_unlock(&debug_data->lock);

	wake_up(&debug_data->stats_queue);
पूर्ण

अटल पूर्णांक smsdvb_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा smsdvb_client_t *client = inode->i_निजी;
	काष्ठा smsdvb_debugfs *debug_data = client->debug_data;

	kref_get(&debug_data->refcount);

	spin_lock(&debug_data->lock);
	debug_data->stats_count = 0;
	debug_data->stats_was_पढ़ो = false;
	spin_unlock(&debug_data->lock);

	file->निजी_data = debug_data;

	वापस 0;
पूर्ण

अटल व्योम smsdvb_debugfs_data_release(काष्ठा kref *ref)
अणु
	काष्ठा smsdvb_debugfs *debug_data;

	debug_data = container_of(ref, काष्ठा smsdvb_debugfs, refcount);
	kमुक्त(debug_data);
पूर्ण

अटल पूर्णांक smsdvb_stats_रुको_पढ़ो(काष्ठा smsdvb_debugfs *debug_data)
अणु
	पूर्णांक rc = 1;

	spin_lock(&debug_data->lock);

	अगर (debug_data->stats_was_पढ़ो)
		जाओ निकास;

	rc = debug_data->stats_count;

निकास:
	spin_unlock(&debug_data->lock);
	वापस rc;
पूर्ण

अटल __poll_t smsdvb_stats_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा smsdvb_debugfs *debug_data = file->निजी_data;
	पूर्णांक rc;

	kref_get(&debug_data->refcount);

	poll_रुको(file, &debug_data->stats_queue, रुको);

	rc = smsdvb_stats_रुको_पढ़ो(debug_data);
	kref_put(&debug_data->refcount, smsdvb_debugfs_data_release);

	वापस rc > 0 ? EPOLLIN | EPOLLRDNORM : 0;
पूर्ण

अटल sमाप_प्रकार smsdvb_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार nbytes, loff_t *ppos)
अणु
	पूर्णांक rc = 0, len;
	काष्ठा smsdvb_debugfs *debug_data = file->निजी_data;

	kref_get(&debug_data->refcount);

	अगर (file->f_flags & O_NONBLOCK) अणु
		rc = smsdvb_stats_रुको_पढ़ो(debug_data);
		अगर (!rc) अणु
			rc = -EWOULDBLOCK;
			जाओ ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = रुको_event_पूर्णांकerruptible(debug_data->stats_queue,
				      smsdvb_stats_रुको_पढ़ो(debug_data));
		अगर (rc < 0)
			जाओ ret;
	पूर्ण

	अगर (debug_data->stats_was_पढ़ो) अणु
		rc = 0;	/* खातापूर्ण */
		जाओ ret;
	पूर्ण

	len = debug_data->stats_count - *ppos;
	अगर (len >= 0)
		rc = simple_पढ़ो_from_buffer(user_buf, nbytes, ppos,
					     debug_data->stats_data, len);
	अन्यथा
		rc = 0;

	अगर (*ppos >= debug_data->stats_count) अणु
		spin_lock(&debug_data->lock);
		debug_data->stats_was_पढ़ो = true;
		spin_unlock(&debug_data->lock);
	पूर्ण
ret:
	kref_put(&debug_data->refcount, smsdvb_debugfs_data_release);
	वापस rc;
पूर्ण

अटल पूर्णांक smsdvb_stats_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा smsdvb_debugfs *debug_data = file->निजी_data;

	spin_lock(&debug_data->lock);
	debug_data->stats_was_पढ़ो = true;	/* वापस खातापूर्ण to पढ़ो() */
	spin_unlock(&debug_data->lock);
	wake_up_पूर्णांकerruptible_sync(&debug_data->stats_queue);

	kref_put(&debug_data->refcount, smsdvb_debugfs_data_release);
	file->निजी_data = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_stats_ops = अणु
	.खोलो = smsdvb_stats_खोलो,
	.poll = smsdvb_stats_poll,
	.पढ़ो = smsdvb_stats_पढ़ो,
	.release = smsdvb_stats_release,
	.llseek = generic_file_llseek,
पूर्ण;

/*
 * Functions used by smsdvb, in order to create the पूर्णांकerfaces
 */

पूर्णांक smsdvb_debugfs_create(काष्ठा smsdvb_client_t *client)
अणु
	काष्ठा smscore_device_t *coredev = client->coredev;
	काष्ठा dentry *d;
	काष्ठा smsdvb_debugfs *debug_data;

	अगर (!smsdvb_debugfs_usb_root || !coredev->is_usb_device)
		वापस -ENODEV;

	client->debugfs = debugfs_create_dir(coredev->devpath,
					     smsdvb_debugfs_usb_root);
	अगर (IS_ERR_OR_शून्य(client->debugfs)) अणु
		pr_info("Unable to create debugfs %s directory.\n",
			coredev->devpath);
		वापस -ENODEV;
	पूर्ण

	d = debugfs_create_file("stats", S_IRUGO | S_IWUSR, client->debugfs,
				client, &debugfs_stats_ops);
	अगर (!d) अणु
		debugfs_हटाओ(client->debugfs);
		वापस -ENOMEM;
	पूर्ण

	debug_data = kzalloc(माप(*client->debug_data), GFP_KERNEL);
	अगर (!debug_data)
		वापस -ENOMEM;

	client->debug_data        = debug_data;
	client->prt_dvb_stats     = smsdvb_prपूर्णांक_dvb_stats;
	client->prt_isdb_stats    = smsdvb_prपूर्णांक_isdb_stats;
	client->prt_isdb_stats_ex = smsdvb_prपूर्णांक_isdb_stats_ex;

	init_रुकोqueue_head(&debug_data->stats_queue);
	spin_lock_init(&debug_data->lock);
	kref_init(&debug_data->refcount);

	वापस 0;
पूर्ण

व्योम smsdvb_debugfs_release(काष्ठा smsdvb_client_t *client)
अणु
	अगर (!client->debugfs)
		वापस;

	client->prt_dvb_stats     = शून्य;
	client->prt_isdb_stats    = शून्य;
	client->prt_isdb_stats_ex = शून्य;

	debugfs_हटाओ_recursive(client->debugfs);
	kref_put(&client->debug_data->refcount, smsdvb_debugfs_data_release);

	client->debug_data = शून्य;
	client->debugfs = शून्य;
पूर्ण

व्योम smsdvb_debugfs_रेजिस्टर(व्योम)
अणु
	काष्ठा dentry *d;

	/*
	 * FIXME: This was written to debug Siano USB devices. So, it creates
	 * the debugfs node under <debugfs>/usb.
	 * A similar logic would be needed क्रम Siano sdio devices, but, in that
	 * हाल, usb_debug_root is not a good choice.
	 *
	 * Perhaps the right fix here would be to create another sysfs root
	 * node क्रम sdio-based boards, but this may need some logic at sdio
	 * subप्रणाली.
	 */
	d = debugfs_create_dir("smsdvb", usb_debug_root);
	अगर (IS_ERR_OR_शून्य(d)) अणु
		pr_err("Couldn't create sysfs node for smsdvb\n");
		वापस;
	पूर्ण
	smsdvb_debugfs_usb_root = d;
पूर्ण

व्योम smsdvb_debugfs_unरेजिस्टर(व्योम)
अणु
	अगर (!smsdvb_debugfs_usb_root)
		वापस;
	debugfs_हटाओ_recursive(smsdvb_debugfs_usb_root);
	smsdvb_debugfs_usb_root = शून्य;
पूर्ण
