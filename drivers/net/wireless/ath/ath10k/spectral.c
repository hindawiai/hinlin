<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013-2017 Qualcomm Atheros, Inc.
 */

#समावेश <linux/relay.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "wmi-ops.h"

अटल व्योम send_fft_sample(काष्ठा ath10k *ar,
			    स्थिर काष्ठा fft_sample_tlv *fft_sample_tlv)
अणु
	पूर्णांक length;

	अगर (!ar->spectral.rfs_chan_spec_scan)
		वापस;

	length = __be16_to_cpu(fft_sample_tlv->length) +
		 माप(*fft_sample_tlv);
	relay_ग_लिखो(ar->spectral.rfs_chan_spec_scan, fft_sample_tlv, length);
पूर्ण

अटल uपूर्णांक8_t get_max_exp(s8 max_index, u16 max_magnitude, माप_प्रकार bin_len,
			   u8 *data)
अणु
	पूर्णांक dc_pos;
	u8 max_exp;

	dc_pos = bin_len / 2;

	/* peak index outside of bins */
	अगर (dc_pos < max_index || -dc_pos >= max_index)
		वापस 0;

	क्रम (max_exp = 0; max_exp < 8; max_exp++) अणु
		अगर (data[dc_pos + max_index] == (max_magnitude >> max_exp))
			अवरोध;
	पूर्ण

	/* max_exp not found */
	अगर (data[dc_pos + max_index] != (max_magnitude >> max_exp))
		वापस 0;

	वापस max_exp;
पूर्ण

अटल अंतरभूत माप_प्रकार ath10k_spectral_fix_bin_size(काष्ठा ath10k *ar,
						  माप_प्रकार bin_len)
अणु
	/* some chipsets reports bin size as 2^n bytes + 'm' bytes in
	 * report mode 2. First 2^n bytes carries inband tones and last
	 * 'm' bytes carries band edge detection data मुख्यly used in
	 * radar detection purpose. Strip last 'm' bytes to make bin size
	 * as a valid one. 'm' can take possible values of 4, 12.
	 */
	अगर (!is_घातer_of_2(bin_len))
		bin_len -= ar->hw_params.spectral_bin_discard;

	वापस bin_len;
पूर्ण

पूर्णांक ath10k_spectral_process_fft(काष्ठा ath10k *ar,
				काष्ठा wmi_phyerr_ev_arg *phyerr,
				स्थिर काष्ठा phyerr_fft_report *fftr,
				माप_प्रकार bin_len, u64 tsf)
अणु
	काष्ठा fft_sample_ath10k *fft_sample;
	u8 buf[माप(*fft_sample) + SPECTRAL_ATH10K_MAX_NUM_BINS];
	u16 freq1, freq2, total_gain_db, base_pwr_db, length, peak_mag;
	u32 reg0, reg1;
	u8 chain_idx, *bins;
	पूर्णांक dc_pos;

	fft_sample = (काष्ठा fft_sample_ath10k *)&buf;

	bin_len = ath10k_spectral_fix_bin_size(ar, bin_len);

	अगर (bin_len < 64 || bin_len > SPECTRAL_ATH10K_MAX_NUM_BINS)
		वापस -EINVAL;

	reg0 = __le32_to_cpu(fftr->reg0);
	reg1 = __le32_to_cpu(fftr->reg1);

	length = माप(*fft_sample) - माप(काष्ठा fft_sample_tlv) + bin_len;
	fft_sample->tlv.type = ATH_FFT_SAMPLE_ATH10K;
	fft_sample->tlv.length = __cpu_to_be16(length);

	/* TODO: there might be a reason why the hardware reports 20/40/80 MHz,
	 * but the results/plots suggest that its actually 22/44/88 MHz.
	 */
	चयन (phyerr->chan_width_mhz) अणु
	हाल 20:
		fft_sample->chan_width_mhz = 22;
		अवरोध;
	हाल 40:
		fft_sample->chan_width_mhz = 44;
		अवरोध;
	हाल 80:
		/* TODO: As experiments with an analogue sender and various
		 * configurations (fft-sizes of 64/128/256 and 20/40/80 Mhz)
		 * show, the particular configuration of 80 MHz/64 bins करोes
		 * not match with the other samples at all. Until the reason
		 * क्रम that is found, करोn't report these samples.
		 */
		अगर (bin_len == 64)
			वापस -EINVAL;
		fft_sample->chan_width_mhz = 88;
		अवरोध;
	शेष:
		fft_sample->chan_width_mhz = phyerr->chan_width_mhz;
	पूर्ण

	fft_sample->relpwr_db = MS(reg1, SEARCH_FFT_REPORT_REG1_RELPWR_DB);
	fft_sample->avgpwr_db = MS(reg1, SEARCH_FFT_REPORT_REG1_AVGPWR_DB);

	peak_mag = MS(reg1, SEARCH_FFT_REPORT_REG1_PEAK_MAG);
	fft_sample->max_magnitude = __cpu_to_be16(peak_mag);
	fft_sample->max_index = MS(reg0, SEARCH_FFT_REPORT_REG0_PEAK_SIDX);
	fft_sample->rssi = phyerr->rssi_combined;

	total_gain_db = MS(reg0, SEARCH_FFT_REPORT_REG0_TOTAL_GAIN_DB);
	base_pwr_db = MS(reg0, SEARCH_FFT_REPORT_REG0_BASE_PWR_DB);
	fft_sample->total_gain_db = __cpu_to_be16(total_gain_db);
	fft_sample->base_pwr_db = __cpu_to_be16(base_pwr_db);

	freq1 = phyerr->freq1;
	freq2 = phyerr->freq2;
	fft_sample->freq1 = __cpu_to_be16(freq1);
	fft_sample->freq2 = __cpu_to_be16(freq2);

	chain_idx = MS(reg0, SEARCH_FFT_REPORT_REG0_FFT_CHN_IDX);

	fft_sample->noise = __cpu_to_be16(phyerr->nf_chains[chain_idx]);

	bins = (u8 *)fftr;
	bins += माप(*fftr) + ar->hw_params.spectral_bin_offset;

	fft_sample->tsf = __cpu_to_be64(tsf);

	/* max_exp has been directly reported by previous hardware (ath9k),
	 * maybe its possible to get it by other means?
	 */
	fft_sample->max_exp = get_max_exp(fft_sample->max_index, peak_mag,
					  bin_len, bins);

	स_नकल(fft_sample->data, bins, bin_len);

	/* DC value (value in the middle) is the blind spot of the spectral
	 * sample and invalid, पूर्णांकerpolate it.
	 */
	dc_pos = bin_len / 2;
	fft_sample->data[dc_pos] = (fft_sample->data[dc_pos + 1] +
				    fft_sample->data[dc_pos - 1]) / 2;

	send_fft_sample(ar, &fft_sample->tlv);

	वापस 0;
पूर्ण

अटल काष्ठा ath10k_vअगर *ath10k_get_spectral_vdev(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (list_empty(&ar->arvअगरs))
		वापस शून्य;

	/* अगर there alपढ़ोy is a vअगर करोing spectral, वापस that. */
	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list)
		अगर (arvअगर->spectral_enabled)
			वापस arvअगर;

	/* otherwise, वापस the first vअगर. */
	वापस list_first_entry(&ar->arvअगरs, typeof(*arvअगर), list);
पूर्ण

अटल पूर्णांक ath10k_spectral_scan_trigger(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक res;
	पूर्णांक vdev_id;

	lockdep_निश्चित_held(&ar->conf_mutex);

	arvअगर = ath10k_get_spectral_vdev(ar);
	अगर (!arvअगर)
		वापस -ENODEV;
	vdev_id = arvअगर->vdev_id;

	अगर (ar->spectral.mode == SPECTRAL_DISABLED)
		वापस 0;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_CLEAR,
					      WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	अगर (res < 0)
		वापस res;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_TRIGGER,
					      WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	अगर (res < 0)
		वापस res;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_spectral_scan_config(काष्ठा ath10k *ar,
				       क्रमागत ath10k_spectral_mode mode)
अणु
	काष्ठा wmi_vdev_spectral_conf_arg arg;
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक vdev_id, count, res = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	arvअगर = ath10k_get_spectral_vdev(ar);
	अगर (!arvअगर)
		वापस -ENODEV;

	vdev_id = arvअगर->vdev_id;

	arvअगर->spectral_enabled = (mode != SPECTRAL_DISABLED);
	ar->spectral.mode = mode;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_CLEAR,
					      WMI_SPECTRAL_ENABLE_CMD_DISABLE);
	अगर (res < 0) अणु
		ath10k_warn(ar, "failed to enable spectral scan: %d\n", res);
		वापस res;
	पूर्ण

	अगर (mode == SPECTRAL_DISABLED)
		वापस 0;

	अगर (mode == SPECTRAL_BACKGROUND)
		count = WMI_SPECTRAL_COUNT_DEFAULT;
	अन्यथा
		count = max_t(u8, 1, ar->spectral.config.count);

	arg.vdev_id = vdev_id;
	arg.scan_count = count;
	arg.scan_period = WMI_SPECTRAL_PERIOD_DEFAULT;
	arg.scan_priority = WMI_SPECTRAL_PRIORITY_DEFAULT;
	arg.scan_fft_size = ar->spectral.config.fft_size;
	arg.scan_gc_ena = WMI_SPECTRAL_GC_ENA_DEFAULT;
	arg.scan_restart_ena = WMI_SPECTRAL_RESTART_ENA_DEFAULT;
	arg.scan_noise_न्यूनमान_ref = WMI_SPECTRAL_NOISE_FLOOR_REF_DEFAULT;
	arg.scan_init_delay = WMI_SPECTRAL_INIT_DELAY_DEFAULT;
	arg.scan_nb_tone_thr = WMI_SPECTRAL_NB_TONE_THR_DEFAULT;
	arg.scan_str_bin_thr = WMI_SPECTRAL_STR_BIN_THR_DEFAULT;
	arg.scan_wb_rpt_mode = WMI_SPECTRAL_WB_RPT_MODE_DEFAULT;
	arg.scan_rssi_rpt_mode = WMI_SPECTRAL_RSSI_RPT_MODE_DEFAULT;
	arg.scan_rssi_thr = WMI_SPECTRAL_RSSI_THR_DEFAULT;
	arg.scan_pwr_क्रमmat = WMI_SPECTRAL_PWR_FORMAT_DEFAULT;
	arg.scan_rpt_mode = WMI_SPECTRAL_RPT_MODE_DEFAULT;
	arg.scan_bin_scale = WMI_SPECTRAL_BIN_SCALE_DEFAULT;
	arg.scan_dbm_adj = WMI_SPECTRAL_DBM_ADJ_DEFAULT;
	arg.scan_chn_mask = WMI_SPECTRAL_CHN_MASK_DEFAULT;

	res = ath10k_wmi_vdev_spectral_conf(ar, &arg);
	अगर (res < 0) अणु
		ath10k_warn(ar, "failed to configure spectral scan: %d\n", res);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार पढ़ो_file_spec_scan_ctl(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर *mode = "";
	माप_प्रकार len;
	क्रमागत ath10k_spectral_mode spectral_mode;

	mutex_lock(&ar->conf_mutex);
	spectral_mode = ar->spectral.mode;
	mutex_unlock(&ar->conf_mutex);

	चयन (spectral_mode) अणु
	हाल SPECTRAL_DISABLED:
		mode = "disable";
		अवरोध;
	हाल SPECTRAL_BACKGROUND:
		mode = "background";
		अवरोध;
	हाल SPECTRAL_MANUAL:
		mode = "manual";
		अवरोध;
	पूर्ण

	len = म_माप(mode);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, mode, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_spec_scan_ctl(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	sमाप_प्रकार len;
	पूर्णांक res;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';

	mutex_lock(&ar->conf_mutex);

	अगर (म_भेदन("trigger", buf, 7) == 0) अणु
		अगर (ar->spectral.mode == SPECTRAL_MANUAL ||
		    ar->spectral.mode == SPECTRAL_BACKGROUND) अणु
			/* reset the configuration to aकरोpt possibly changed
			 * debugfs parameters
			 */
			res = ath10k_spectral_scan_config(ar,
							  ar->spectral.mode);
			अगर (res < 0) अणु
				ath10k_warn(ar, "failed to reconfigure spectral scan: %d\n",
					    res);
			पूर्ण
			res = ath10k_spectral_scan_trigger(ar);
			अगर (res < 0) अणु
				ath10k_warn(ar, "failed to trigger spectral scan: %d\n",
					    res);
			पूर्ण
		पूर्ण अन्यथा अणु
			res = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेदन("background", buf, 10) == 0) अणु
		res = ath10k_spectral_scan_config(ar, SPECTRAL_BACKGROUND);
	पूर्ण अन्यथा अगर (म_भेदन("manual", buf, 6) == 0) अणु
		res = ath10k_spectral_scan_config(ar, SPECTRAL_MANUAL);
	पूर्ण अन्यथा अगर (म_भेदन("disable", buf, 7) == 0) अणु
		res = ath10k_spectral_scan_config(ar, SPECTRAL_DISABLED);
	पूर्ण अन्यथा अणु
		res = -EINVAL;
	पूर्ण

	mutex_unlock(&ar->conf_mutex);

	अगर (res < 0)
		वापस res;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spec_scan_ctl = अणु
	.पढ़ो = पढ़ो_file_spec_scan_ctl,
	.ग_लिखो = ग_लिखो_file_spec_scan_ctl,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_spectral_count(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	माप_प्रकार len;
	u8 spectral_count;

	mutex_lock(&ar->conf_mutex);
	spectral_count = ar->spectral.config.count;
	mutex_unlock(&ar->conf_mutex);

	len = प्र_लिखो(buf, "%d\n", spectral_count);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_spectral_count(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 255)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	ar->spectral.config.count = val;
	mutex_unlock(&ar->conf_mutex);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spectral_count = अणु
	.पढ़ो = पढ़ो_file_spectral_count,
	.ग_लिखो = ग_लिखो_file_spectral_count,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_spectral_bins(काष्ठा file *file,
				       अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक bins, fft_size, bin_scale;
	माप_प्रकार len;

	mutex_lock(&ar->conf_mutex);

	fft_size = ar->spectral.config.fft_size;
	bin_scale = WMI_SPECTRAL_BIN_SCALE_DEFAULT;
	bins = 1 << (fft_size - bin_scale);

	mutex_unlock(&ar->conf_mutex);

	len = प्र_लिखो(buf, "%d\n", bins);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_spectral_bins(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val < 64 || val > SPECTRAL_ATH10K_MAX_NUM_BINS)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(val))
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	ar->spectral.config.fft_size = ilog2(val);
	ar->spectral.config.fft_size += WMI_SPECTRAL_BIN_SCALE_DEFAULT;
	mutex_unlock(&ar->conf_mutex);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spectral_bins = अणु
	.पढ़ो = पढ़ो_file_spectral_bins,
	.ग_लिखो = ग_लिखो_file_spectral_bins,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल काष्ठा dentry *create_buf_file_handler(स्थिर अक्षर *filename,
					      काष्ठा dentry *parent,
					      umode_t mode,
					      काष्ठा rchan_buf *buf,
					      पूर्णांक *is_global)
अणु
	काष्ठा dentry *buf_file;

	buf_file = debugfs_create_file(filename, mode, parent, buf,
				       &relay_file_operations);
	अगर (IS_ERR(buf_file))
		वापस शून्य;

	*is_global = 1;
	वापस buf_file;
पूर्ण

अटल पूर्णांक हटाओ_buf_file_handler(काष्ठा dentry *dentry)
अणु
	debugfs_हटाओ(dentry);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rchan_callbacks rfs_spec_scan_cb = अणु
	.create_buf_file = create_buf_file_handler,
	.हटाओ_buf_file = हटाओ_buf_file_handler,
पूर्ण;

पूर्णांक ath10k_spectral_start(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list)
		arvअगर->spectral_enabled = 0;

	ar->spectral.mode = SPECTRAL_DISABLED;
	ar->spectral.config.count = WMI_SPECTRAL_COUNT_DEFAULT;
	ar->spectral.config.fft_size = WMI_SPECTRAL_FFT_SIZE_DEFAULT;

	वापस 0;
पूर्ण

पूर्णांक ath10k_spectral_vअगर_stop(काष्ठा ath10k_vअगर *arvअगर)
अणु
	अगर (!arvअगर->spectral_enabled)
		वापस 0;

	वापस ath10k_spectral_scan_config(arvअगर->ar, SPECTRAL_DISABLED);
पूर्ण

पूर्णांक ath10k_spectral_create(काष्ठा ath10k *ar)
अणु
	/* The buffer size covers whole channels in dual bands up to 128 bins.
	 * Scan with bigger than 128 bins needs to be run on single band each.
	 */
	ar->spectral.rfs_chan_spec_scan = relay_खोलो("spectral_scan",
						     ar->debug.debugfs_phy,
						     1140, 2500,
						     &rfs_spec_scan_cb, शून्य);
	debugfs_create_file("spectral_scan_ctl",
			    0600,
			    ar->debug.debugfs_phy, ar,
			    &fops_spec_scan_ctl);
	debugfs_create_file("spectral_count",
			    0600,
			    ar->debug.debugfs_phy, ar,
			    &fops_spectral_count);
	debugfs_create_file("spectral_bins",
			    0600,
			    ar->debug.debugfs_phy, ar,
			    &fops_spectral_bins);

	वापस 0;
पूर्ण

व्योम ath10k_spectral_destroy(काष्ठा ath10k *ar)
अणु
	अगर (ar->spectral.rfs_chan_spec_scan) अणु
		relay_बंद(ar->spectral.rfs_chan_spec_scan);
		ar->spectral.rfs_chan_spec_scan = शून्य;
	पूर्ण
पूर्ण
