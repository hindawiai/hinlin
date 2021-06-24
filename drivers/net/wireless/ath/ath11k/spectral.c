<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2019-2020 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/relay.h>
#समावेश "core.h"
#समावेश "debug.h"

#घोषणा ATH11K_SPECTRAL_NUM_RESP_PER_EVENT	2
#घोषणा ATH11K_SPECTRAL_EVENT_TIMEOUT_MS	1

#घोषणा ATH11K_SPECTRAL_DWORD_SIZE		4
/* HW bug, expected BIN size is 2 bytes but HW report as 4 bytes */
#घोषणा ATH11K_SPECTRAL_BIN_SIZE		4
#घोषणा ATH11K_SPECTRAL_ATH11K_MIN_BINS		64
#घोषणा ATH11K_SPECTRAL_ATH11K_MIN_IB_BINS	32
#घोषणा ATH11K_SPECTRAL_ATH11K_MAX_IB_BINS	256

#घोषणा ATH11K_SPECTRAL_SCAN_COUNT_MAX		4095

/* Max channel computed by sum of 2g and 5g band channels */
#घोषणा ATH11K_SPECTRAL_TOTAL_CHANNEL		41
#घोषणा ATH11K_SPECTRAL_SAMPLES_PER_CHANNEL	70
#घोषणा ATH11K_SPECTRAL_PER_SAMPLE_SIZE		(माप(काष्ठा fft_sample_ath11k) + \
						 ATH11K_SPECTRAL_ATH11K_MAX_IB_BINS)
#घोषणा ATH11K_SPECTRAL_TOTAL_SAMPLE		(ATH11K_SPECTRAL_TOTAL_CHANNEL * \
						 ATH11K_SPECTRAL_SAMPLES_PER_CHANNEL)
#घोषणा ATH11K_SPECTRAL_SUB_BUFF_SIZE		ATH11K_SPECTRAL_PER_SAMPLE_SIZE
#घोषणा ATH11K_SPECTRAL_NUM_SUB_BUF		ATH11K_SPECTRAL_TOTAL_SAMPLE

#घोषणा ATH11K_SPECTRAL_20MHZ			20
#घोषणा ATH11K_SPECTRAL_40MHZ			40
#घोषणा ATH11K_SPECTRAL_80MHZ			80

#घोषणा ATH11K_SPECTRAL_SIGNATURE		0xFA

#घोषणा ATH11K_SPECTRAL_TAG_RADAR_SUMMARY	0x0
#घोषणा ATH11K_SPECTRAL_TAG_RADAR_FFT		0x1
#घोषणा ATH11K_SPECTRAL_TAG_SCAN_SUMMARY	0x2
#घोषणा ATH11K_SPECTRAL_TAG_SCAN_SEARCH		0x3

#घोषणा SPECTRAL_TLV_HDR_LEN				GENMASK(15, 0)
#घोषणा SPECTRAL_TLV_HDR_TAG				GENMASK(23, 16)
#घोषणा SPECTRAL_TLV_HDR_SIGN				GENMASK(31, 24)

#घोषणा SPECTRAL_SUMMARY_INFO0_AGC_TOTAL_GAIN		GENMASK(7, 0)
#घोषणा SPECTRAL_SUMMARY_INFO0_OB_FLAG			BIT(8)
#घोषणा SPECTRAL_SUMMARY_INFO0_GRP_IDX			GENMASK(16, 9)
#घोषणा SPECTRAL_SUMMARY_INFO0_RECENT_RFSAT		BIT(17)
#घोषणा SPECTRAL_SUMMARY_INFO0_INBAND_PWR_DB		GENMASK(27, 18)
#घोषणा SPECTRAL_SUMMARY_INFO0_FALSE_SCAN		BIT(28)
#घोषणा SPECTRAL_SUMMARY_INFO0_DETECTOR_ID		GENMASK(30, 29)
#घोषणा SPECTRAL_SUMMARY_INFO0_PRI80			BIT(31)

#घोषणा SPECTRAL_SUMMARY_INFO2_PEAK_SIGNED_IDX		GENMASK(11, 0)
#घोषणा SPECTRAL_SUMMARY_INFO2_PEAK_MAGNITUDE		GENMASK(21, 12)
#घोषणा SPECTRAL_SUMMARY_INFO2_NARROWBAND_MASK		GENMASK(29, 22)
#घोषणा SPECTRAL_SUMMARY_INFO2_GAIN_CHANGE		BIT(30)

काष्ठा spectral_tlv अणु
	__le32 बारtamp;
	__le32 header;
पूर्ण __packed;

काष्ठा spectral_summary_fft_report अणु
	__le32 बारtamp;
	__le32 tlv_header;
	__le32 info0;
	__le32 reserve0;
	__le32 info2;
	__le32 reserve1;
पूर्ण __packed;

काष्ठा ath11k_spectral_summary_report अणु
	काष्ठा wmi_dma_buf_release_meta_data meta;
	u32 बारtamp;
	u8 agc_total_gain;
	u8 grp_idx;
	u16 inb_pwr_db;
	s16 peak_idx;
	u16 peak_mag;
	u8 detector_id;
	bool out_of_band_flag;
	bool rf_saturation;
	bool primary80;
	bool gain_change;
	bool false_scan;
पूर्ण;

#घोषणा SPECTRAL_FFT_REPORT_INFO0_DETECTOR_ID		GENMASK(1, 0)
#घोषणा SPECTRAL_FFT_REPORT_INFO0_FFT_NUM		GENMASK(4, 2)
#घोषणा SPECTRAL_FFT_REPORT_INFO0_RADAR_CHECK		GENMASK(16, 5)
#घोषणा SPECTRAL_FFT_REPORT_INFO0_PEAK_SIGNED_IDX	GENMASK(27, 17)
#घोषणा SPECTRAL_FFT_REPORT_INFO0_CHAIN_IDX		GENMASK(30, 28)

#घोषणा SPECTRAL_FFT_REPORT_INFO1_BASE_PWR_DB		GENMASK(8, 0)
#घोषणा SPECTRAL_FFT_REPORT_INFO1_TOTAL_GAIN_DB		GENMASK(16, 9)

#घोषणा SPECTRAL_FFT_REPORT_INFO2_NUM_STRONG_BINS	GENMASK(7, 0)
#घोषणा SPECTRAL_FFT_REPORT_INFO2_PEAK_MAGNITUDE	GENMASK(17, 8)
#घोषणा SPECTRAL_FFT_REPORT_INFO2_AVG_PWR_DB		GENMASK(24, 18)
#घोषणा SPECTRAL_FFT_REPORT_INFO2_REL_PWR_DB		GENMASK(31, 25)

काष्ठा spectral_search_fft_report अणु
	__le32 बारtamp;
	__le32 tlv_header;
	__le32 info0;
	__le32 info1;
	__le32 info2;
	__le32 reserve0;
	u8 bins[0];
पूर्ण __packed;

काष्ठा ath11k_spectral_search_report अणु
	u32 बारtamp;
	u8 detector_id;
	u8 fft_count;
	u16 radar_check;
	s16 peak_idx;
	u8 chain_idx;
	u16 base_pwr_db;
	u8 total_gain_db;
	u8 strong_bin_count;
	u16 peak_mag;
	u8 avg_pwr_db;
	u8 rel_pwr_db;
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
	*is_global = 1;
	वापस buf_file;
पूर्ण

अटल पूर्णांक हटाओ_buf_file_handler(काष्ठा dentry *dentry)
अणु
	debugfs_हटाओ(dentry);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rchan_callbacks rfs_scan_cb = अणु
	.create_buf_file = create_buf_file_handler,
	.हटाओ_buf_file = हटाओ_buf_file_handler,
पूर्ण;

अटल काष्ठा ath11k_vअगर *ath11k_spectral_get_vdev(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_vअगर *arvअगर;

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

अटल पूर्णांक ath11k_spectral_scan_trigger(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_vअगर *arvअगर;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	arvअगर = ath11k_spectral_get_vdev(ar);
	अगर (!arvअगर)
		वापस -ENODEV;

	अगर (ar->spectral.mode == ATH11K_SPECTRAL_DISABLED)
		वापस 0;

	ret = ath11k_wmi_vdev_spectral_enable(ar, arvअगर->vdev_id,
					      ATH11K_WMI_SPECTRAL_TRIGGER_CMD_CLEAR,
					      ATH11K_WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	अगर (ret)
		वापस ret;

	ret = ath11k_wmi_vdev_spectral_enable(ar, arvअगर->vdev_id,
					      ATH11K_WMI_SPECTRAL_TRIGGER_CMD_TRIGGER,
					      ATH11K_WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_spectral_scan_config(काष्ठा ath11k *ar,
				       क्रमागत ath11k_spectral_mode mode)
अणु
	काष्ठा ath11k_wmi_vdev_spectral_conf_param param = अणु 0 पूर्ण;
	काष्ठा ath11k_vअगर *arvअगर;
	पूर्णांक ret, count;

	lockdep_निश्चित_held(&ar->conf_mutex);

	arvअगर = ath11k_spectral_get_vdev(ar);
	अगर (!arvअगर)
		वापस -ENODEV;

	arvअगर->spectral_enabled = (mode != ATH11K_SPECTRAL_DISABLED);
	ar->spectral.mode = mode;

	ret = ath11k_wmi_vdev_spectral_enable(ar, arvअगर->vdev_id,
					      ATH11K_WMI_SPECTRAL_TRIGGER_CMD_CLEAR,
					      ATH11K_WMI_SPECTRAL_ENABLE_CMD_DISABLE);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to enable spectral scan: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (mode == ATH11K_SPECTRAL_DISABLED)
		वापस 0;

	अगर (mode == ATH11K_SPECTRAL_BACKGROUND)
		count = ATH11K_WMI_SPECTRAL_COUNT_DEFAULT;
	अन्यथा
		count = max_t(u16, 1, ar->spectral.count);

	param.vdev_id = arvअगर->vdev_id;
	param.scan_count = count;
	param.scan_fft_size = ar->spectral.fft_size;
	param.scan_period = ATH11K_WMI_SPECTRAL_PERIOD_DEFAULT;
	param.scan_priority = ATH11K_WMI_SPECTRAL_PRIORITY_DEFAULT;
	param.scan_gc_ena = ATH11K_WMI_SPECTRAL_GC_ENA_DEFAULT;
	param.scan_restart_ena = ATH11K_WMI_SPECTRAL_RESTART_ENA_DEFAULT;
	param.scan_noise_न्यूनमान_ref = ATH11K_WMI_SPECTRAL_NOISE_FLOOR_REF_DEFAULT;
	param.scan_init_delay = ATH11K_WMI_SPECTRAL_INIT_DELAY_DEFAULT;
	param.scan_nb_tone_thr = ATH11K_WMI_SPECTRAL_NB_TONE_THR_DEFAULT;
	param.scan_str_bin_thr = ATH11K_WMI_SPECTRAL_STR_BIN_THR_DEFAULT;
	param.scan_wb_rpt_mode = ATH11K_WMI_SPECTRAL_WB_RPT_MODE_DEFAULT;
	param.scan_rssi_rpt_mode = ATH11K_WMI_SPECTRAL_RSSI_RPT_MODE_DEFAULT;
	param.scan_rssi_thr = ATH11K_WMI_SPECTRAL_RSSI_THR_DEFAULT;
	param.scan_pwr_क्रमmat = ATH11K_WMI_SPECTRAL_PWR_FORMAT_DEFAULT;
	param.scan_rpt_mode = ATH11K_WMI_SPECTRAL_RPT_MODE_DEFAULT;
	param.scan_bin_scale = ATH11K_WMI_SPECTRAL_BIN_SCALE_DEFAULT;
	param.scan_dbm_adj = ATH11K_WMI_SPECTRAL_DBM_ADJ_DEFAULT;
	param.scan_chn_mask = ATH11K_WMI_SPECTRAL_CHN_MASK_DEFAULT;

	ret = ath11k_wmi_vdev_spectral_conf(ar, &param);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to configure spectral scan: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath11k_पढ़ो_file_spec_scan_ctl(काष्ठा file *file,
					      अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	अक्षर *mode = "";
	माप_प्रकार len;
	क्रमागत ath11k_spectral_mode spectral_mode;

	mutex_lock(&ar->conf_mutex);
	spectral_mode = ar->spectral.mode;
	mutex_unlock(&ar->conf_mutex);

	चयन (spectral_mode) अणु
	हाल ATH11K_SPECTRAL_DISABLED:
		mode = "disable";
		अवरोध;
	हाल ATH11K_SPECTRAL_BACKGROUND:
		mode = "background";
		अवरोध;
	हाल ATH11K_SPECTRAL_MANUAL:
		mode = "manual";
		अवरोध;
	पूर्ण

	len = म_माप(mode);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, mode, len);
पूर्ण

अटल sमाप_प्रकार ath11k_ग_लिखो_file_spec_scan_ctl(काष्ठा file *file,
					       स्थिर अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	अक्षर buf[32];
	sमाप_प्रकार len;
	पूर्णांक ret;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';

	mutex_lock(&ar->conf_mutex);

	अगर (म_भेदन("trigger", buf, 7) == 0) अणु
		अगर (ar->spectral.mode == ATH11K_SPECTRAL_MANUAL ||
		    ar->spectral.mode == ATH11K_SPECTRAL_BACKGROUND) अणु
			/* reset the configuration to aकरोpt possibly changed
			 * debugfs parameters
			 */
			ret = ath11k_spectral_scan_config(ar, ar->spectral.mode);
			अगर (ret) अणु
				ath11k_warn(ar->ab, "failed to reconfigure spectral scan: %d\n",
					    ret);
				जाओ unlock;
			पूर्ण

			ret = ath11k_spectral_scan_trigger(ar);
			अगर (ret) अणु
				ath11k_warn(ar->ab, "failed to trigger spectral scan: %d\n",
					    ret);
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेदन("background", buf, 10) == 0) अणु
		ret = ath11k_spectral_scan_config(ar, ATH11K_SPECTRAL_BACKGROUND);
	पूर्ण अन्यथा अगर (म_भेदन("manual", buf, 6) == 0) अणु
		ret = ath11k_spectral_scan_config(ar, ATH11K_SPECTRAL_MANUAL);
	पूर्ण अन्यथा अगर (म_भेदन("disable", buf, 7) == 0) अणु
		ret = ath11k_spectral_scan_config(ar, ATH11K_SPECTRAL_DISABLED);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

unlock:
	mutex_unlock(&ar->conf_mutex);

	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_scan_ctl = अणु
	.पढ़ो = ath11k_पढ़ो_file_spec_scan_ctl,
	.ग_लिखो = ath11k_ग_लिखो_file_spec_scan_ctl,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_पढ़ो_file_spectral_count(काष्ठा file *file,
					       अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	अक्षर buf[32];
	माप_प्रकार len;
	u16 spectral_count;

	mutex_lock(&ar->conf_mutex);
	spectral_count = ar->spectral.count;
	mutex_unlock(&ar->conf_mutex);

	len = प्र_लिखो(buf, "%d\n", spectral_count);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath11k_ग_लिखो_file_spectral_count(काष्ठा file *file,
						स्थिर अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > ATH11K_SPECTRAL_SCAN_COUNT_MAX)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	ar->spectral.count = val;
	mutex_unlock(&ar->conf_mutex);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_scan_count = अणु
	.पढ़ो = ath11k_पढ़ो_file_spectral_count,
	.ग_लिखो = ath11k_ग_लिखो_file_spectral_count,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_पढ़ो_file_spectral_bins(काष्ठा file *file,
					      अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक bins, fft_size;
	माप_प्रकार len;

	mutex_lock(&ar->conf_mutex);

	fft_size = ar->spectral.fft_size;
	bins = 1 << fft_size;

	mutex_unlock(&ar->conf_mutex);

	len = प्र_लिखो(buf, "%d\n", bins);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath11k_ग_लिखो_file_spectral_bins(काष्ठा file *file,
					       स्थिर अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath11k *ar = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val < ATH11K_SPECTRAL_ATH11K_MIN_BINS ||
	    val > SPECTRAL_ATH11K_MAX_NUM_BINS)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(val))
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	ar->spectral.fft_size = ilog2(val);
	mutex_unlock(&ar->conf_mutex);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_scan_bins = अणु
	.पढ़ो = ath11k_पढ़ो_file_spectral_bins,
	.ग_लिखो = ath11k_ग_लिखो_file_spectral_bins,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ath11k_spectral_pull_summary(काष्ठा ath11k *ar,
					काष्ठा wmi_dma_buf_release_meta_data *meta,
					काष्ठा spectral_summary_fft_report *summary,
					काष्ठा ath11k_spectral_summary_report *report)
अणु
	report->बारtamp = __le32_to_cpu(summary->बारtamp);
	report->agc_total_gain = FIELD_GET(SPECTRAL_SUMMARY_INFO0_AGC_TOTAL_GAIN,
					   __le32_to_cpu(summary->info0));
	report->out_of_band_flag = FIELD_GET(SPECTRAL_SUMMARY_INFO0_OB_FLAG,
					     __le32_to_cpu(summary->info0));
	report->grp_idx = FIELD_GET(SPECTRAL_SUMMARY_INFO0_GRP_IDX,
				    __le32_to_cpu(summary->info0));
	report->rf_saturation = FIELD_GET(SPECTRAL_SUMMARY_INFO0_RECENT_RFSAT,
					  __le32_to_cpu(summary->info0));
	report->inb_pwr_db = FIELD_GET(SPECTRAL_SUMMARY_INFO0_INBAND_PWR_DB,
				       __le32_to_cpu(summary->info0));
	report->false_scan = FIELD_GET(SPECTRAL_SUMMARY_INFO0_FALSE_SCAN,
				       __le32_to_cpu(summary->info0));
	report->detector_id = FIELD_GET(SPECTRAL_SUMMARY_INFO0_DETECTOR_ID,
					__le32_to_cpu(summary->info0));
	report->primary80 = FIELD_GET(SPECTRAL_SUMMARY_INFO0_PRI80,
				      __le32_to_cpu(summary->info0));
	report->peak_idx = FIELD_GET(SPECTRAL_SUMMARY_INFO2_PEAK_SIGNED_IDX,
				     __le32_to_cpu(summary->info2));
	report->peak_mag = FIELD_GET(SPECTRAL_SUMMARY_INFO2_PEAK_MAGNITUDE,
				     __le32_to_cpu(summary->info2));
	report->gain_change = FIELD_GET(SPECTRAL_SUMMARY_INFO2_GAIN_CHANGE,
					__le32_to_cpu(summary->info2));

	स_नकल(&report->meta, meta, माप(*meta));

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_spectral_pull_search(काष्ठा ath11k *ar,
				       काष्ठा spectral_search_fft_report *search,
				       काष्ठा ath11k_spectral_search_report *report)
अणु
	report->बारtamp = __le32_to_cpu(search->बारtamp);
	report->detector_id = FIELD_GET(SPECTRAL_FFT_REPORT_INFO0_DETECTOR_ID,
					__le32_to_cpu(search->info0));
	report->fft_count = FIELD_GET(SPECTRAL_FFT_REPORT_INFO0_FFT_NUM,
				      __le32_to_cpu(search->info0));
	report->radar_check = FIELD_GET(SPECTRAL_FFT_REPORT_INFO0_RADAR_CHECK,
					__le32_to_cpu(search->info0));
	report->peak_idx = FIELD_GET(SPECTRAL_FFT_REPORT_INFO0_PEAK_SIGNED_IDX,
				     __le32_to_cpu(search->info0));
	report->chain_idx = FIELD_GET(SPECTRAL_FFT_REPORT_INFO0_CHAIN_IDX,
				      __le32_to_cpu(search->info0));
	report->base_pwr_db = FIELD_GET(SPECTRAL_FFT_REPORT_INFO1_BASE_PWR_DB,
					__le32_to_cpu(search->info1));
	report->total_gain_db = FIELD_GET(SPECTRAL_FFT_REPORT_INFO1_TOTAL_GAIN_DB,
					  __le32_to_cpu(search->info1));
	report->strong_bin_count = FIELD_GET(SPECTRAL_FFT_REPORT_INFO2_NUM_STRONG_BINS,
					     __le32_to_cpu(search->info2));
	report->peak_mag = FIELD_GET(SPECTRAL_FFT_REPORT_INFO2_PEAK_MAGNITUDE,
				     __le32_to_cpu(search->info2));
	report->avg_pwr_db = FIELD_GET(SPECTRAL_FFT_REPORT_INFO2_AVG_PWR_DB,
				       __le32_to_cpu(search->info2));
	report->rel_pwr_db = FIELD_GET(SPECTRAL_FFT_REPORT_INFO2_REL_PWR_DB,
				       __le32_to_cpu(search->info2));

	वापस 0;
पूर्ण

अटल u8 ath11k_spectral_get_max_exp(s8 max_index, u8 max_magnitude,
				      पूर्णांक bin_len, u8 *bins)
अणु
	पूर्णांक dc_pos;
	u8 max_exp;

	dc_pos = bin_len / 2;

	/* peak index outside of bins */
	अगर (dc_pos <= max_index || -dc_pos >= max_index)
		वापस 0;

	क्रम (max_exp = 0; max_exp < 8; max_exp++) अणु
		अगर (bins[dc_pos + max_index] == (max_magnitude >> max_exp))
			अवरोध;
	पूर्ण

	/* max_exp not found */
	अगर (bins[dc_pos + max_index] != (max_magnitude >> max_exp))
		वापस 0;

	वापस max_exp;
पूर्ण

अटल व्योम ath11k_spectral_parse_fft(u8 *outbins, u8 *inbins, पूर्णांक num_bins, u8 fft_sz)
अणु
	पूर्णांक i, j;

	i = 0;
	j = 0;
	जबतक (i < num_bins) अणु
		outbins[i] = inbins[j];
		i++;
		j += fft_sz;
	पूर्ण
पूर्ण

अटल
पूर्णांक ath11k_spectral_process_fft(काष्ठा ath11k *ar,
				काष्ठा ath11k_spectral_summary_report *summary,
				व्योम *data,
				काष्ठा fft_sample_ath11k *fft_sample,
				u32 data_len)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा spectral_search_fft_report *fft_report = data;
	काष्ठा ath11k_spectral_search_report search;
	काष्ठा spectral_tlv *tlv;
	पूर्णांक tlv_len, bin_len, num_bins;
	u16 length, freq;
	u8 chan_width_mhz;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->spectral.lock);

	अगर (!ab->hw_params.spectral_fft_sz) अणु
		ath11k_warn(ab, "invalid bin size type for hw rev %d\n",
			    ab->hw_rev);
		वापस -EINVAL;
	पूर्ण

	tlv = (काष्ठा spectral_tlv *)data;
	tlv_len = FIELD_GET(SPECTRAL_TLV_HDR_LEN, __le32_to_cpu(tlv->header));
	/* convert Dword पूर्णांकo bytes */
	tlv_len *= ATH11K_SPECTRAL_DWORD_SIZE;
	bin_len = tlv_len - (माप(*fft_report) - माप(*tlv));

	अगर (data_len < (bin_len + माप(*fft_report))) अणु
		ath11k_warn(ab, "mismatch in expected bin len %d and data len %d\n",
			    bin_len, data_len);
		वापस -EINVAL;
	पूर्ण

	num_bins = bin_len / ATH11K_SPECTRAL_BIN_SIZE;
	/* Only In-band bins are useful to user क्रम visualize */
	num_bins >>= 1;

	अगर (num_bins < ATH11K_SPECTRAL_ATH11K_MIN_IB_BINS ||
	    num_bins > ATH11K_SPECTRAL_ATH11K_MAX_IB_BINS ||
	    !is_घातer_of_2(num_bins)) अणु
		ath11k_warn(ab, "Invalid num of bins %d\n", num_bins);
		वापस -EINVAL;
	पूर्ण

	ret = ath11k_spectral_pull_search(ar, data, &search);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to pull search report %d\n", ret);
		वापस ret;
	पूर्ण

	chan_width_mhz = summary->meta.ch_width;

	चयन (chan_width_mhz) अणु
	हाल ATH11K_SPECTRAL_20MHZ:
	हाल ATH11K_SPECTRAL_40MHZ:
	हाल ATH11K_SPECTRAL_80MHZ:
		fft_sample->chan_width_mhz = chan_width_mhz;
		अवरोध;
	शेष:
		ath11k_warn(ab, "invalid channel width %d\n", chan_width_mhz);
		वापस -EINVAL;
	पूर्ण

	length = माप(*fft_sample) - माप(काष्ठा fft_sample_tlv) + num_bins;
	fft_sample->tlv.type = ATH_FFT_SAMPLE_ATH11K;
	fft_sample->tlv.length = __cpu_to_be16(length);

	fft_sample->tsf = __cpu_to_be32(search.बारtamp);
	fft_sample->max_magnitude = __cpu_to_be16(search.peak_mag);
	fft_sample->max_index = FIELD_GET(SPECTRAL_FFT_REPORT_INFO0_PEAK_SIGNED_IDX,
					  __le32_to_cpu(fft_report->info0));

	summary->inb_pwr_db >>= 1;
	fft_sample->rssi = __cpu_to_be16(summary->inb_pwr_db);
	fft_sample->noise = __cpu_to_be32(summary->meta.noise_न्यूनमान[search.chain_idx]);

	freq = summary->meta.freq1;
	fft_sample->freq1 = __cpu_to_be16(freq);

	freq = summary->meta.freq2;
	fft_sample->freq2 = __cpu_to_be16(freq);

	ath11k_spectral_parse_fft(fft_sample->data, fft_report->bins, num_bins,
				  ab->hw_params.spectral_fft_sz);

	fft_sample->max_exp = ath11k_spectral_get_max_exp(fft_sample->max_index,
							  search.peak_mag,
							  num_bins,
							  fft_sample->data);

	अगर (ar->spectral.rfs_scan)
		relay_ग_लिखो(ar->spectral.rfs_scan, fft_sample,
			    length + माप(काष्ठा fft_sample_tlv));

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_spectral_process_data(काष्ठा ath11k *ar,
					काष्ठा ath11k_dbring_data *param)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा spectral_tlv *tlv;
	काष्ठा spectral_summary_fft_report *summary = शून्य;
	काष्ठा ath11k_spectral_summary_report summ_rpt;
	काष्ठा fft_sample_ath11k *fft_sample = शून्य;
	u8 *data;
	u32 data_len, i;
	u8 sign, tag;
	पूर्णांक tlv_len, sample_sz;
	पूर्णांक ret;
	bool quit = false;

	spin_lock_bh(&ar->spectral.lock);

	अगर (!ar->spectral.enabled) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	sample_sz = माप(*fft_sample) + ATH11K_SPECTRAL_ATH11K_MAX_IB_BINS;
	fft_sample = kदो_स्मृति(sample_sz, GFP_ATOMIC);
	अगर (!fft_sample) अणु
		ret = -ENOBUFS;
		जाओ unlock;
	पूर्ण

	data = param->data;
	data_len = param->data_sz;
	i = 0;
	जबतक (!quit && (i < data_len)) अणु
		अगर ((i + माप(*tlv)) > data_len) अणु
			ath11k_warn(ab, "failed to parse spectral tlv hdr at bytes %d\n",
				    i);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		tlv = (काष्ठा spectral_tlv *)&data[i];
		sign = FIELD_GET(SPECTRAL_TLV_HDR_SIGN,
				 __le32_to_cpu(tlv->header));
		अगर (sign != ATH11K_SPECTRAL_SIGNATURE) अणु
			ath11k_warn(ab, "Invalid sign 0x%x at bytes %d\n",
				    sign, i);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		tlv_len = FIELD_GET(SPECTRAL_TLV_HDR_LEN,
				    __le32_to_cpu(tlv->header));
		/* convert Dword पूर्णांकo bytes */
		tlv_len *= ATH11K_SPECTRAL_DWORD_SIZE;
		अगर ((i + माप(*tlv) + tlv_len) > data_len) अणु
			ath11k_warn(ab, "failed to parse spectral tlv payload at bytes %d tlv_len:%d data_len:%d\n",
				    i, tlv_len, data_len);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		tag = FIELD_GET(SPECTRAL_TLV_HDR_TAG,
				__le32_to_cpu(tlv->header));
		चयन (tag) अणु
		हाल ATH11K_SPECTRAL_TAG_SCAN_SUMMARY:
			/* HW bug in tlv length of summary report,
			 * HW report 3 DWORD size but the data payload
			 * is 4 DWORD size (16 bytes).
			 * Need to हटाओ this workaround once HW bug fixed
			 */
			tlv_len = माप(*summary) - माप(*tlv);

			अगर (tlv_len < (माप(*summary) - माप(*tlv))) अणु
				ath11k_warn(ab, "failed to parse spectral summary at bytes %d tlv_len:%d\n",
					    i, tlv_len);
				ret = -EINVAL;
				जाओ err;
			पूर्ण

			summary = (काष्ठा spectral_summary_fft_report *)tlv;
			ath11k_spectral_pull_summary(ar, &param->meta,
						     summary, &summ_rpt);
			अवरोध;
		हाल ATH11K_SPECTRAL_TAG_SCAN_SEARCH:
			अगर (tlv_len < (माप(काष्ठा spectral_search_fft_report) -
				       माप(*tlv))) अणु
				ath11k_warn(ab, "failed to parse spectral search fft at bytes %d\n",
					    i);
				ret = -EINVAL;
				जाओ err;
			पूर्ण

			स_रखो(fft_sample, 0, sample_sz);
			ret = ath11k_spectral_process_fft(ar, &summ_rpt, tlv,
							  fft_sample,
							  data_len - i);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to process spectral fft at bytes %d\n",
					    i);
				जाओ err;
			पूर्ण
			quit = true;
			अवरोध;
		पूर्ण

		i += माप(*tlv) + tlv_len;
	पूर्ण

	ret = 0;

err:
	kमुक्त(fft_sample);
unlock:
	spin_unlock_bh(&ar->spectral.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_spectral_ring_alloc(काष्ठा ath11k *ar,
				      काष्ठा ath11k_dbring_cap *db_cap)
अणु
	काष्ठा ath11k_spectral *sp = &ar->spectral;
	पूर्णांक ret;

	ret = ath11k_dbring_srng_setup(ar, &sp->rx_ring,
				       0, db_cap->min_elem);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup db ring\n");
		वापस ret;
	पूर्ण

	ath11k_dbring_set_cfg(ar, &sp->rx_ring,
			      ATH11K_SPECTRAL_NUM_RESP_PER_EVENT,
			      ATH11K_SPECTRAL_EVENT_TIMEOUT_MS,
			      ath11k_spectral_process_data);

	ret = ath11k_dbring_buf_setup(ar, &sp->rx_ring, db_cap);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup db ring buffer\n");
		जाओ srng_cleanup;
	पूर्ण

	ret = ath11k_dbring_wmi_cfg_setup(ar, &sp->rx_ring,
					  WMI_सूचीECT_BUF_SPECTRAL);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup db ring cfg\n");
		जाओ buffer_cleanup;
	पूर्ण

	वापस 0;

buffer_cleanup:
	ath11k_dbring_buf_cleanup(ar, &sp->rx_ring);
srng_cleanup:
	ath11k_dbring_srng_cleanup(ar, &sp->rx_ring);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ath11k_spectral_ring_मुक्त(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_spectral *sp = &ar->spectral;

	अगर (!sp->enabled)
		वापस;

	ath11k_dbring_srng_cleanup(ar, &sp->rx_ring);
	ath11k_dbring_buf_cleanup(ar, &sp->rx_ring);
पूर्ण

अटल अंतरभूत व्योम ath11k_spectral_debug_unरेजिस्टर(काष्ठा ath11k *ar)
अणु
	debugfs_हटाओ(ar->spectral.scan_bins);
	ar->spectral.scan_bins = शून्य;

	debugfs_हटाओ(ar->spectral.scan_count);
	ar->spectral.scan_count = शून्य;

	debugfs_हटाओ(ar->spectral.scan_ctl);
	ar->spectral.scan_ctl = शून्य;

	अगर (ar->spectral.rfs_scan) अणु
		relay_बंद(ar->spectral.rfs_scan);
		ar->spectral.rfs_scan = शून्य;
	पूर्ण
पूर्ण

पूर्णांक ath11k_spectral_vअगर_stop(काष्ठा ath11k_vअगर *arvअगर)
अणु
	अगर (!arvअगर->spectral_enabled)
		वापस 0;

	वापस ath11k_spectral_scan_config(arvअगर->ar, ATH11K_SPECTRAL_DISABLED);
पूर्ण

व्योम ath11k_spectral_reset_buffer(काष्ठा ath11k *ar)
अणु
	अगर (!ar->spectral.enabled)
		वापस;

	अगर (ar->spectral.rfs_scan)
		relay_reset(ar->spectral.rfs_scan);
पूर्ण

व्योम ath11k_spectral_deinit(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_spectral *sp;
	पूर्णांक i;

	क्रम (i = 0; i <  ab->num_radios; i++) अणु
		ar = ab->pdevs[i].ar;
		sp = &ar->spectral;

		अगर (!sp->enabled)
			जारी;

		ath11k_spectral_debug_unरेजिस्टर(ar);
		ath11k_spectral_ring_मुक्त(ar);

		spin_lock_bh(&sp->lock);

		sp->mode = ATH11K_SPECTRAL_DISABLED;
		sp->enabled = false;

		spin_unlock_bh(&sp->lock);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_spectral_debug_रेजिस्टर(काष्ठा ath11k *ar)
अणु
	पूर्णांक ret;

	ar->spectral.rfs_scan = relay_खोलो("spectral_scan",
					   ar->debug.debugfs_pdev,
					   ATH11K_SPECTRAL_SUB_BUFF_SIZE,
					   ATH11K_SPECTRAL_NUM_SUB_BUF,
					   &rfs_scan_cb, शून्य);
	अगर (!ar->spectral.rfs_scan) अणु
		ath11k_warn(ar->ab, "failed to open relay in pdev %d\n",
			    ar->pdev_idx);
		वापस -EINVAL;
	पूर्ण

	ar->spectral.scan_ctl = debugfs_create_file("spectral_scan_ctl",
						    0600,
						    ar->debug.debugfs_pdev, ar,
						    &fops_scan_ctl);
	अगर (!ar->spectral.scan_ctl) अणु
		ath11k_warn(ar->ab, "failed to open debugfs in pdev %d\n",
			    ar->pdev_idx);
		ret = -EINVAL;
		जाओ debug_unरेजिस्टर;
	पूर्ण

	ar->spectral.scan_count = debugfs_create_file("spectral_count",
						      0600,
						      ar->debug.debugfs_pdev, ar,
						      &fops_scan_count);
	अगर (!ar->spectral.scan_count) अणु
		ath11k_warn(ar->ab, "failed to open debugfs in pdev %d\n",
			    ar->pdev_idx);
		ret = -EINVAL;
		जाओ debug_unरेजिस्टर;
	पूर्ण

	ar->spectral.scan_bins = debugfs_create_file("spectral_bins",
						     0600,
						     ar->debug.debugfs_pdev, ar,
						     &fops_scan_bins);
	अगर (!ar->spectral.scan_bins) अणु
		ath11k_warn(ar->ab, "failed to open debugfs in pdev %d\n",
			    ar->pdev_idx);
		ret = -EINVAL;
		जाओ debug_unरेजिस्टर;
	पूर्ण

	वापस 0;

debug_unरेजिस्टर:
	ath11k_spectral_debug_unरेजिस्टर(ar);
	वापस ret;
पूर्ण

पूर्णांक ath11k_spectral_init(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_spectral *sp;
	काष्ठा ath11k_dbring_cap db_cap;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!test_bit(WMI_TLV_SERVICE_FREQINFO_IN_METADATA,
		      ab->wmi_ab.svc_map))
		वापस 0;

	अगर (!ab->hw_params.spectral_fft_sz)
		वापस 0;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		ar = ab->pdevs[i].ar;
		sp = &ar->spectral;

		ret = ath11k_dbring_get_cap(ar->ab, ar->pdev_idx,
					    WMI_सूचीECT_BUF_SPECTRAL,
					    &db_cap);
		अगर (ret)
			जारी;

		idr_init(&sp->rx_ring.bufs_idr);
		spin_lock_init(&sp->rx_ring.idr_lock);
		spin_lock_init(&sp->lock);

		ret = ath11k_spectral_ring_alloc(ar, &db_cap);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to init spectral ring for pdev %d\n",
				    i);
			जाओ deinit;
		पूर्ण

		spin_lock_bh(&sp->lock);

		sp->mode = ATH11K_SPECTRAL_DISABLED;
		sp->count = ATH11K_WMI_SPECTRAL_COUNT_DEFAULT;
		sp->fft_size = ATH11K_WMI_SPECTRAL_FFT_SIZE_DEFAULT;
		sp->enabled = true;

		spin_unlock_bh(&sp->lock);

		ret = ath11k_spectral_debug_रेजिस्टर(ar);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to register spectral for pdev %d\n",
				    i);
			जाओ deinit;
		पूर्ण
	पूर्ण

	वापस 0;

deinit:
	ath11k_spectral_deinit(ab);
	वापस ret;
पूर्ण

क्रमागत ath11k_spectral_mode ath11k_spectral_get_mode(काष्ठा ath11k *ar)
अणु
	अगर (ar->spectral.enabled)
		वापस ar->spectral.mode;
	अन्यथा
		वापस ATH11K_SPECTRAL_DISABLED;
पूर्ण

काष्ठा ath11k_dbring *ath11k_spectral_get_dbring(काष्ठा ath11k *ar)
अणु
	अगर (ar->spectral.enabled)
		वापस &ar->spectral.rx_ring;
	अन्यथा
		वापस शून्य;
पूर्ण
