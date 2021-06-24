<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ath9k.h"

#घोषणा REG_WRITE_D(_ah, _reg, _val) \
	ath9k_hw_common(_ah)->ops->ग_लिखो((_ah), (_val), (_reg))
#घोषणा REG_READ_D(_ah, _reg) \
	ath9k_hw_common(_ah)->ops->पढ़ो((_ah), (_reg))

व्योम ath9k_debug_sync_cause(काष्ठा ath_softc *sc, u32 sync_cause)
अणु
	अगर (sync_cause)
		sc->debug.stats.istats.sync_cause_all++;
	अगर (sync_cause & AR_INTR_SYNC_RTC_IRQ)
		sc->debug.stats.istats.sync_rtc_irq++;
	अगर (sync_cause & AR_INTR_SYNC_MAC_IRQ)
		sc->debug.stats.istats.sync_mac_irq++;
	अगर (sync_cause & AR_INTR_SYNC_EEPROM_ILLEGAL_ACCESS)
		sc->debug.stats.istats.eeprom_illegal_access++;
	अगर (sync_cause & AR_INTR_SYNC_APB_TIMEOUT)
		sc->debug.stats.istats.apb_समयout++;
	अगर (sync_cause & AR_INTR_SYNC_PCI_MODE_CONFLICT)
		sc->debug.stats.istats.pci_mode_conflict++;
	अगर (sync_cause & AR_INTR_SYNC_HOST1_FATAL)
		sc->debug.stats.istats.host1_fatal++;
	अगर (sync_cause & AR_INTR_SYNC_HOST1_PERR)
		sc->debug.stats.istats.host1_perr++;
	अगर (sync_cause & AR_INTR_SYNC_TRCV_FIFO_PERR)
		sc->debug.stats.istats.trcv_fअगरo_perr++;
	अगर (sync_cause & AR_INTR_SYNC_RADM_CPL_EP)
		sc->debug.stats.istats.radm_cpl_ep++;
	अगर (sync_cause & AR_INTR_SYNC_RADM_CPL_DLLP_ABORT)
		sc->debug.stats.istats.radm_cpl_dllp_पात++;
	अगर (sync_cause & AR_INTR_SYNC_RADM_CPL_TLP_ABORT)
		sc->debug.stats.istats.radm_cpl_tlp_पात++;
	अगर (sync_cause & AR_INTR_SYNC_RADM_CPL_ECRC_ERR)
		sc->debug.stats.istats.radm_cpl_ecrc_err++;
	अगर (sync_cause & AR_INTR_SYNC_RADM_CPL_TIMEOUT)
		sc->debug.stats.istats.radm_cpl_समयout++;
	अगर (sync_cause & AR_INTR_SYNC_LOCAL_TIMEOUT)
		sc->debug.stats.istats.local_समयout++;
	अगर (sync_cause & AR_INTR_SYNC_PM_ACCESS)
		sc->debug.stats.istats.pm_access++;
	अगर (sync_cause & AR_INTR_SYNC_MAC_AWAKE)
		sc->debug.stats.istats.mac_awake++;
	अगर (sync_cause & AR_INTR_SYNC_MAC_ASLEEP)
		sc->debug.stats.istats.mac_asleep++;
	अगर (sync_cause & AR_INTR_SYNC_MAC_SLEEP_ACCESS)
		sc->debug.stats.istats.mac_sleep_access++;
पूर्ण

अटल sमाप_प्रकार ath9k_debugfs_पढ़ो_buf(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	u8 *buf = file->निजी_data;
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, म_माप(buf));
पूर्ण

अटल पूर्णांक ath9k_debugfs_release_buf(काष्ठा inode *inode, काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ATH_DEBUG

अटल sमाप_प्रकार पढ़ो_file_debug(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "0x%08x\n", common->debug_mask);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_debug(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	अचिन्हित दीर्घ mask;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &mask))
		वापस -EINVAL;

	common->debug_mask = mask;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_debug = अणु
	.पढ़ो = पढ़ो_file_debug,
	.ग_लिखो = ग_लिखो_file_debug,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#पूर्ण_अगर

#घोषणा DMA_BUF_LEN 1024


अटल sमाप_प्रकार पढ़ो_file_ani(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_hw *ah = sc->sc_ah;
	अचिन्हित पूर्णांक len = 0;
	स्थिर अचिन्हित पूर्णांक size = 1024;
	sमाप_प्रकार retval = 0;
	अक्षर *buf;
	पूर्णांक i;
	काष्ठा अणु
		स्थिर अक्षर *name;
		अचिन्हित पूर्णांक val;
	पूर्ण ani_info[] = अणु
		अणु "ANI RESET", ah->stats.ast_ani_reset पूर्ण,
		अणु "OFDM LEVEL", ah->ani.ofdmNoiseImmunityLevel पूर्ण,
		अणु "CCK LEVEL", ah->ani.cckNoiseImmunityLevel पूर्ण,
		अणु "SPUR UP", ah->stats.ast_ani_spurup पूर्ण,
		अणु "SPUR DOWN", ah->stats.ast_ani_spurकरोwn पूर्ण,
		अणु "OFDM WS-DET ON", ah->stats.ast_ani_ofdmon पूर्ण,
		अणु "OFDM WS-DET OFF", ah->stats.ast_ani_ofdmoff पूर्ण,
		अणु "MRC-CCK ON", ah->stats.ast_ani_ccklow पूर्ण,
		अणु "MRC-CCK OFF", ah->stats.ast_ani_cckhigh पूर्ण,
		अणु "FIR-STEP UP", ah->stats.ast_ani_stepup पूर्ण,
		अणु "FIR-STEP DOWN", ah->stats.ast_ani_stepकरोwn पूर्ण,
		अणु "INV LISTENTIME", ah->stats.ast_ani_lneg_or_lzero पूर्ण,
		अणु "OFDM ERRORS", ah->stats.ast_ani_ofdmerrs पूर्ण,
		अणु "CCK ERRORS", ah->stats.ast_ani_cckerrs पूर्ण,
	पूर्ण;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, size - len, "%15s: %s\n", "ANI",
			 common->disable_ani ? "DISABLED" : "ENABLED");

	अगर (common->disable_ani)
		जाओ निकास;

	क्रम (i = 0; i < ARRAY_SIZE(ani_info); i++)
		len += scnम_लिखो(buf + len, size - len, "%15s: %u\n",
				 ani_info[i].name, ani_info[i].val);

निकास:
	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_ani(काष्ठा file *file,
			      स्थिर अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	अचिन्हित दीर्घ ani;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &ani))
		वापस -EINVAL;

	अगर (ani > 1)
		वापस -EINVAL;

	common->disable_ani = !ani;

	अगर (common->disable_ani) अणु
		clear_bit(ATH_OP_ANI_RUN, &common->op_flags);
		ath_stop_ani(sc);
	पूर्ण अन्यथा अणु
		ath_check_ani(sc);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_ani = अणु
	.पढ़ो = पढ़ो_file_ani,
	.ग_लिखो = ग_लिखो_file_ani,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT

अटल sमाप_प्रकार पढ़ो_file_bt_ant_भागersity(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%d\n", common->bt_ant_भागersity);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_bt_ant_भागersity(काष्ठा file *file,
					   स्थिर अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath9k_hw_capabilities *pCap = &sc->sc_ah->caps;
	अचिन्हित दीर्घ bt_ant_भागersity;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	अगर (!(pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV))
		जाओ निकास;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &bt_ant_भागersity))
		वापस -EINVAL;

	common->bt_ant_भागersity = !!bt_ant_भागersity;
	ath9k_ps_wakeup(sc);
	ath9k_hw_set_bt_ant_भागersity(sc->sc_ah, common->bt_ant_भागersity);
	ath_dbg(common, CONFIG, "Enable WLAN/BT RX Antenna diversity: %d\n",
		common->bt_ant_भागersity);
	ath9k_ps_restore(sc);
निकास:
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_bt_ant_भागersity = अणु
	.पढ़ो = पढ़ो_file_bt_ant_भागersity,
	.ग_लिखो = ग_लिखो_file_bt_ant_भागersity,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#पूर्ण_अगर

व्योम ath9k_debug_stat_ant(काष्ठा ath_softc *sc,
			  काष्ठा ath_hw_antcomb_conf *भाग_ant_conf,
			  पूर्णांक मुख्य_rssi_avg, पूर्णांक alt_rssi_avg)
अणु
	काष्ठा ath_antenna_stats *as_मुख्य = &sc->debug.stats.ant_stats[ANT_MAIN];
	काष्ठा ath_antenna_stats *as_alt = &sc->debug.stats.ant_stats[ANT_ALT];

	as_मुख्य->lna_attempt_cnt[भाग_ant_conf->मुख्य_lna_conf]++;
	as_alt->lna_attempt_cnt[भाग_ant_conf->alt_lna_conf]++;

	as_मुख्य->rssi_avg = मुख्य_rssi_avg;
	as_alt->rssi_avg = alt_rssi_avg;
पूर्ण

अटल sमाप_प्रकार पढ़ो_file_antenna_भागersity(काष्ठा file *file,
					   अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	काष्ठा ath_antenna_stats *as_मुख्य = &sc->debug.stats.ant_stats[ANT_MAIN];
	काष्ठा ath_antenna_stats *as_alt = &sc->debug.stats.ant_stats[ANT_ALT];
	काष्ठा ath_hw_antcomb_conf भाग_ant_conf;
	अचिन्हित पूर्णांक len = 0;
	स्थिर अचिन्हित पूर्णांक size = 1024;
	sमाप_प्रकार retval = 0;
	अक्षर *buf;
	अटल स्थिर अक्षर *lna_conf_str[4] = अणु
		"LNA1_MINUS_LNA2", "LNA2", "LNA1", "LNA1_PLUS_LNA2"
	पूर्ण;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	अगर (!(pCap->hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)) अणु
		len += scnम_लिखो(buf + len, size - len, "%s\n",
				 "Antenna Diversity Combining is disabled");
		जाओ निकास;
	पूर्ण

	ath9k_ps_wakeup(sc);
	ath9k_hw_antभाग_comb_conf_get(ah, &भाग_ant_conf);
	len += scnम_लिखो(buf + len, size - len, "Current MAIN config : %s\n",
			 lna_conf_str[भाग_ant_conf.मुख्य_lna_conf]);
	len += scnम_लिखो(buf + len, size - len, "Current ALT config  : %s\n",
			 lna_conf_str[भाग_ant_conf.alt_lna_conf]);
	len += scnम_लिखो(buf + len, size - len, "Average MAIN RSSI   : %d\n",
			 as_मुख्य->rssi_avg);
	len += scnम_लिखो(buf + len, size - len, "Average ALT RSSI    : %d\n\n",
			 as_alt->rssi_avg);
	ath9k_ps_restore(sc);

	len += scnम_लिखो(buf + len, size - len, "Packet Receive Cnt:\n");
	len += scnम_लिखो(buf + len, size - len, "-------------------\n");

	len += scnम_लिखो(buf + len, size - len, "%30s%15s\n",
			 "MAIN", "ALT");
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "TOTAL COUNT",
			 as_मुख्य->recv_cnt,
			 as_alt->recv_cnt);
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA1",
			 as_मुख्य->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA1],
			 as_alt->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA1]);
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA2",
			 as_मुख्य->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA2],
			 as_alt->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA2]);
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA1 + LNA2",
			 as_मुख्य->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2],
			 as_alt->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2]);
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA1 - LNA2",
			 as_मुख्य->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2],
			 as_alt->lna_recv_cnt[ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2]);

	len += scnम_लिखो(buf + len, size - len, "\nLNA Config Attempts:\n");
	len += scnम_लिखो(buf + len, size - len, "--------------------\n");

	len += scnम_लिखो(buf + len, size - len, "%30s%15s\n",
			 "MAIN", "ALT");
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA1",
			 as_मुख्य->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA1],
			 as_alt->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA1]);
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA2",
			 as_मुख्य->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA2],
			 as_alt->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA2]);
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA1 + LNA2",
			 as_मुख्य->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2],
			 as_alt->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2]);
	len += scnम_लिखो(buf + len, size - len, "%-14s:%15d%15d\n",
			 "LNA1 - LNA2",
			 as_मुख्य->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2],
			 as_alt->lna_attempt_cnt[ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2]);

निकास:
	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_antenna_भागersity = अणु
	.पढ़ो = पढ़ो_file_antenna_भागersity,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक पढ़ो_file_dma(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(file->निजी);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	u32 val[ATH9K_NUM_DMA_DEBUG_REGS];
	पूर्णांक i, qcuOffset = 0, dcuOffset = 0;
	u32 *qcuBase = &val[0], *dcuBase = &val[4];

	ath9k_ps_wakeup(sc);

	REG_WRITE_D(ah, AR_MACMISC,
		  ((AR_MACMISC_DMA_OBS_LINE_8 << AR_MACMISC_DMA_OBS_S) |
		   (AR_MACMISC_MISC_OBS_BUS_1 <<
		    AR_MACMISC_MISC_OBS_BUS_MSB_S)));

	seq_माला_दो(file, "Raw DMA Debug values:\n");

	क्रम (i = 0; i < ATH9K_NUM_DMA_DEBUG_REGS; i++) अणु
		अगर (i % 4 == 0)
			seq_माला_दो(file, "\n");

		val[i] = REG_READ_D(ah, AR_DMADBG_0 + (i * माप(u32)));
		seq_म_लिखो(file, "%d: %08x ", i, val[i]);
	पूर्ण

	seq_माला_दो(file, "\n\n");
	seq_माला_दो(file, "Num QCU: chain_st fsp_ok fsp_st DCU: chain_st\n");

	क्रम (i = 0; i < ATH9K_NUM_QUEUES; i++, qcuOffset += 4, dcuOffset += 5) अणु
		अगर (i == 8) अणु
			qcuOffset = 0;
			qcuBase++;
		पूर्ण

		अगर (i == 6) अणु
			dcuOffset = 0;
			dcuBase++;
		पूर्ण

		seq_म_लिखो(file, "%2d          %2x      %1x     %2x           %2x\n",
			   i, (*qcuBase & (0x7 << qcuOffset)) >> qcuOffset,
			   (*qcuBase & (0x8 << qcuOffset)) >> (qcuOffset + 3),
			   (val[2] & (0x7 << (i * 3))) >> (i * 3),
			   (*dcuBase & (0x1f << dcuOffset)) >> dcuOffset);
	पूर्ण

	seq_माला_दो(file, "\n");

	seq_म_लिखो(file, "qcu_stitch state:   %2x    qcu_fetch state:        %2x\n",
		   (val[3] & 0x003c0000) >> 18, (val[3] & 0x03c00000) >> 22);
	seq_म_लिखो(file, "qcu_complete state: %2x    dcu_complete state:     %2x\n",
		   (val[3] & 0x1c000000) >> 26, (val[6] & 0x3));
	seq_म_लिखो(file, "dcu_arb state:      %2x    dcu_fp state:           %2x\n",
		   (val[5] & 0x06000000) >> 25, (val[5] & 0x38000000) >> 27);
	seq_म_लिखो(file, "chan_idle_dur:     %3d    chan_idle_dur_valid:     %1d\n",
		   (val[6] & 0x000003fc) >> 2, (val[6] & 0x00000400) >> 10);
	seq_म_लिखो(file, "txfifo_valid_0:      %1d    txfifo_valid_1:          %1d\n",
		   (val[6] & 0x00000800) >> 11, (val[6] & 0x00001000) >> 12);
	seq_म_लिखो(file, "txfifo_dcu_num_0:   %2d    txfifo_dcu_num_1:       %2d\n",
		   (val[6] & 0x0001e000) >> 13, (val[6] & 0x001e0000) >> 17);

	seq_म_लिखो(file, "pcu observe: 0x%x\n", REG_READ_D(ah, AR_OBS_BUS_1));
	seq_म_लिखो(file, "AR_CR: 0x%x\n", REG_READ_D(ah, AR_CR));

	ath9k_ps_restore(sc);

	वापस 0;
पूर्ण

व्योम ath_debug_stat_पूर्णांकerrupt(काष्ठा ath_softc *sc, क्रमागत ath9k_पूर्णांक status)
अणु
	अगर (status)
		sc->debug.stats.istats.total++;
	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
		अगर (status & ATH9K_INT_RXLP)
			sc->debug.stats.istats.rxlp++;
		अगर (status & ATH9K_INT_RXHP)
			sc->debug.stats.istats.rxhp++;
		अगर (status & ATH9K_INT_BB_WATCHDOG)
			sc->debug.stats.istats.bb_watchकरोg++;
	पूर्ण अन्यथा अणु
		अगर (status & ATH9K_INT_RX)
			sc->debug.stats.istats.rxok++;
	पूर्ण
	अगर (status & ATH9K_INT_RXEOL)
		sc->debug.stats.istats.rxeol++;
	अगर (status & ATH9K_INT_RXORN)
		sc->debug.stats.istats.rxorn++;
	अगर (status & ATH9K_INT_TX)
		sc->debug.stats.istats.txok++;
	अगर (status & ATH9K_INT_TXURN)
		sc->debug.stats.istats.txurn++;
	अगर (status & ATH9K_INT_RXPHY)
		sc->debug.stats.istats.rxphyerr++;
	अगर (status & ATH9K_INT_RXKCM)
		sc->debug.stats.istats.rx_keycache_miss++;
	अगर (status & ATH9K_INT_SWBA)
		sc->debug.stats.istats.swba++;
	अगर (status & ATH9K_INT_BMISS)
		sc->debug.stats.istats.bmiss++;
	अगर (status & ATH9K_INT_BNR)
		sc->debug.stats.istats.bnr++;
	अगर (status & ATH9K_INT_CST)
		sc->debug.stats.istats.cst++;
	अगर (status & ATH9K_INT_GTT)
		sc->debug.stats.istats.gtt++;
	अगर (status & ATH9K_INT_TIM)
		sc->debug.stats.istats.tim++;
	अगर (status & ATH9K_INT_CABEND)
		sc->debug.stats.istats.cabend++;
	अगर (status & ATH9K_INT_DTIMSYNC)
		sc->debug.stats.istats.dtimsync++;
	अगर (status & ATH9K_INT_DTIM)
		sc->debug.stats.istats.dtim++;
	अगर (status & ATH9K_INT_TSFOOR)
		sc->debug.stats.istats.tsfoor++;
	अगर (status & ATH9K_INT_MCI)
		sc->debug.stats.istats.mci++;
	अगर (status & ATH9K_INT_GENTIMER)
		sc->debug.stats.istats.gen_समयr++;
पूर्ण

अटल पूर्णांक पढ़ो_file_पूर्णांकerrupt(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(file->निजी);
	काष्ठा ath_softc *sc = hw->priv;

#घोषणा PR_IS(a, s)						\
	करो अणु							\
		seq_म_लिखो(file, "%21s: %10u\n", a,		\
			   sc->debug.stats.istats.s);		\
	पूर्ण जबतक (0)

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
		PR_IS("RXLP", rxlp);
		PR_IS("RXHP", rxhp);
		PR_IS("WATCHDOG", bb_watchकरोg);
	पूर्ण अन्यथा अणु
		PR_IS("RX", rxok);
	पूर्ण
	PR_IS("RXEOL", rxeol);
	PR_IS("RXORN", rxorn);
	PR_IS("TX", txok);
	PR_IS("TXURN", txurn);
	PR_IS("MIB", mib);
	PR_IS("RXPHY", rxphyerr);
	PR_IS("RXKCM", rx_keycache_miss);
	PR_IS("SWBA", swba);
	PR_IS("BMISS", bmiss);
	PR_IS("BNR", bnr);
	PR_IS("CST", cst);
	PR_IS("GTT", gtt);
	PR_IS("TIM", tim);
	PR_IS("CABEND", cabend);
	PR_IS("DTIMSYNC", dtimsync);
	PR_IS("DTIM", dtim);
	PR_IS("TSFOOR", tsfoor);
	PR_IS("MCI", mci);
	PR_IS("GENTIMER", gen_समयr);
	PR_IS("TOTAL", total);

	seq_माला_दो(file, "SYNC_CAUSE stats:\n");

	PR_IS("Sync-All", sync_cause_all);
	PR_IS("RTC-IRQ", sync_rtc_irq);
	PR_IS("MAC-IRQ", sync_mac_irq);
	PR_IS("EEPROM-Illegal-Access", eeprom_illegal_access);
	PR_IS("APB-Timeout", apb_समयout);
	PR_IS("PCI-Mode-Conflict", pci_mode_conflict);
	PR_IS("HOST1-Fatal", host1_fatal);
	PR_IS("HOST1-Perr", host1_perr);
	PR_IS("TRCV-FIFO-Perr", trcv_fअगरo_perr);
	PR_IS("RADM-CPL-EP", radm_cpl_ep);
	PR_IS("RADM-CPL-DLLP-Abort", radm_cpl_dllp_पात);
	PR_IS("RADM-CPL-TLP-Abort", radm_cpl_tlp_पात);
	PR_IS("RADM-CPL-ECRC-Err", radm_cpl_ecrc_err);
	PR_IS("RADM-CPL-Timeout", radm_cpl_समयout);
	PR_IS("Local-Bus-Timeout", local_समयout);
	PR_IS("PM-Access", pm_access);
	PR_IS("MAC-Awake", mac_awake);
	PR_IS("MAC-Asleep", mac_asleep);
	PR_IS("MAC-Sleep-Access", mac_sleep_access);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_file_xmit(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(file->निजी);
	काष्ठा ath_softc *sc = hw->priv;

	seq_म_लिखो(file, "%30s %10s%10s%10s\n\n", "BE", "BK", "VI", "VO");

	PR("MPDUs Queued:    ", queued);
	PR("MPDUs Completed: ", completed);
	PR("MPDUs XRetried:  ", xretries);
	PR("Aggregates:      ", a_aggr);
	PR("AMPDUs Queued HW:", a_queued_hw);
	PR("AMPDUs Completed:", a_completed);
	PR("AMPDUs Retried:  ", a_retries);
	PR("AMPDUs XRetried: ", a_xretries);
	PR("TXERR Filtered:  ", txerr_filtered);
	PR("FIFO Underrun:   ", fअगरo_underrun);
	PR("TXOP Exceeded:   ", xtxop);
	PR("TXTIMER Expiry:  ", समयr_exp);
	PR("DESC CFG Error:  ", desc_cfg_err);
	PR("DATA Underrun:   ", data_underrun);
	PR("DELIM Underrun:  ", delim_underrun);
	PR("TX-Pkts-All:     ", tx_pkts_all);
	PR("TX-Bytes-All:    ", tx_bytes_all);
	PR("HW-put-tx-buf:   ", puttxbuf);
	PR("HW-tx-start:     ", txstart);
	PR("HW-tx-proc-desc: ", txprocdesc);
	PR("TX-Failed:       ", txfailed);

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_queue(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
			काष्ठा seq_file *file)
अणु
	ath_txq_lock(sc, txq);

	seq_म_लिखो(file, "%s: %d ", "qnum", txq->axq_qnum);
	seq_म_लिखो(file, "%s: %2d ", "qdepth", txq->axq_depth);
	seq_म_लिखो(file, "%s: %2d ", "ampdu-depth", txq->axq_ampdu_depth);
	seq_म_लिखो(file, "%s: %3d\n", "pending", txq->pending_frames);

	ath_txq_unlock(sc, txq);
पूर्ण

अटल पूर्णांक पढ़ो_file_queues(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(file->निजी);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_txq *txq;
	पूर्णांक i;
	अटल स्थिर अक्षर *qname[4] = अणु
		"VO", "VI", "BE", "BK"
	पूर्ण;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		txq = sc->tx.txq_map[i];
		seq_म_लिखो(file, "(%s):  ", qname[i]);
		prपूर्णांक_queue(sc, txq, file);
	पूर्ण

	seq_माला_दो(file, "(CAB): ");
	prपूर्णांक_queue(sc, sc->beacon.cabq, file);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_file_misc(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(file->निजी);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath9k_vअगर_iter_data iter_data;
	काष्ठा ath_chanctx *ctx;
	अचिन्हित पूर्णांक reg;
	u32 rxfilter, i;

	seq_म_लिखो(file, "BSSID: %pM\n", common->curbssid);
	seq_म_लिखो(file, "BSSID-MASK: %pM\n", common->bssidmask);
	seq_म_लिखो(file, "OPMODE: %s\n",
		   ath_opmode_to_string(sc->sc_ah->opmode));

	ath9k_ps_wakeup(sc);
	rxfilter = ath9k_hw_getrxfilter(sc->sc_ah);
	ath9k_ps_restore(sc);

	seq_म_लिखो(file, "RXFILTER: 0x%x", rxfilter);

	अगर (rxfilter & ATH9K_RX_FILTER_UCAST)
		seq_माला_दो(file, " UCAST");
	अगर (rxfilter & ATH9K_RX_FILTER_MCAST)
		seq_माला_दो(file, " MCAST");
	अगर (rxfilter & ATH9K_RX_FILTER_BCAST)
		seq_माला_दो(file, " BCAST");
	अगर (rxfilter & ATH9K_RX_FILTER_CONTROL)
		seq_माला_दो(file, " CONTROL");
	अगर (rxfilter & ATH9K_RX_FILTER_BEACON)
		seq_माला_दो(file, " BEACON");
	अगर (rxfilter & ATH9K_RX_FILTER_PROM)
		seq_माला_दो(file, " PROM");
	अगर (rxfilter & ATH9K_RX_FILTER_PROBEREQ)
		seq_माला_दो(file, " PROBEREQ");
	अगर (rxfilter & ATH9K_RX_FILTER_PHYERR)
		seq_माला_दो(file, " PHYERR");
	अगर (rxfilter & ATH9K_RX_FILTER_MYBEACON)
		seq_माला_दो(file, " MYBEACON");
	अगर (rxfilter & ATH9K_RX_FILTER_COMP_BAR)
		seq_माला_दो(file, " COMP_BAR");
	अगर (rxfilter & ATH9K_RX_FILTER_PSPOLL)
		seq_माला_दो(file, " PSPOLL");
	अगर (rxfilter & ATH9K_RX_FILTER_PHYRADAR)
		seq_माला_दो(file, " PHYRADAR");
	अगर (rxfilter & ATH9K_RX_FILTER_MCAST_BCAST_ALL)
		seq_माला_दो(file, " MCAST_BCAST_ALL");
	अगर (rxfilter & ATH9K_RX_FILTER_CONTROL_WRAPPER)
		seq_माला_दो(file, " CONTROL_WRAPPER");

	seq_माला_दो(file, "\n");

	reg = sc->sc_ah->imask;

	seq_म_लिखो(file, "INTERRUPT-MASK: 0x%x", reg);

	अगर (reg & ATH9K_INT_SWBA)
		seq_माला_दो(file, " SWBA");
	अगर (reg & ATH9K_INT_BMISS)
		seq_माला_दो(file, " BMISS");
	अगर (reg & ATH9K_INT_CST)
		seq_माला_दो(file, " CST");
	अगर (reg & ATH9K_INT_RX)
		seq_माला_दो(file, " RX");
	अगर (reg & ATH9K_INT_RXHP)
		seq_माला_दो(file, " RXHP");
	अगर (reg & ATH9K_INT_RXLP)
		seq_माला_दो(file, " RXLP");
	अगर (reg & ATH9K_INT_BB_WATCHDOG)
		seq_माला_दो(file, " BB_WATCHDOG");

	seq_माला_दो(file, "\n");

	i = 0;
	ath_क्रम_each_chanctx(sc, ctx) अणु
		अगर (list_empty(&ctx->vअगरs))
			जारी;
		ath9k_calculate_iter_data(sc, ctx, &iter_data);

		seq_म_लिखो(file,
			   "VIFS: CTX %i(%i) AP: %i STA: %i MESH: %i",
			   i++, (पूर्णांक)(ctx->asचिन्हित), iter_data.naps,
			   iter_data.nstations,
			   iter_data.nmeshes);
		seq_म_लिखो(file, " ADHOC: %i OCB: %i TOTAL: %hi BEACON-VIF: %hi\n",
			   iter_data.nadhocs, iter_data.nocbs, sc->cur_chan->nvअगरs,
			   sc->nbcnvअगरs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_file_reset(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(file->निजी);
	काष्ठा ath_softc *sc = hw->priv;
	अटल स्थिर अक्षर * स्थिर reset_cause[__RESET_TYPE_MAX] = अणु
		[RESET_TYPE_BB_HANG] = "Baseband Hang",
		[RESET_TYPE_BB_WATCHDOG] = "Baseband Watchdog",
		[RESET_TYPE_FATAL_INT] = "Fatal HW Error",
		[RESET_TYPE_TX_ERROR] = "TX HW error",
		[RESET_TYPE_TX_GTT] = "Transmit timeout",
		[RESET_TYPE_TX_HANG] = "TX Path Hang",
		[RESET_TYPE_PLL_HANG] = "PLL RX Hang",
		[RESET_TYPE_MAC_HANG] = "MAC Hang",
		[RESET_TYPE_BEACON_STUCK] = "Stuck Beacon",
		[RESET_TYPE_MCI] = "MCI Reset",
		[RESET_TYPE_CALIBRATION] = "Calibration error",
		[RESET_TX_DMA_ERROR] = "Tx DMA stop error",
		[RESET_RX_DMA_ERROR] = "Rx DMA stop error",
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reset_cause); i++) अणु
		अगर (!reset_cause[i])
		    जारी;

		seq_म_लिखो(file, "%17s: %2d\n", reset_cause[i],
			   sc->debug.stats.reset[i]);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath_debug_stat_tx(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
		       काष्ठा ath_tx_status *ts, काष्ठा ath_txq *txq,
		       अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक qnum = txq->axq_qnum;

	TX_STAT_INC(sc, qnum, tx_pkts_all);
	sc->debug.stats.txstats[qnum].tx_bytes_all += bf->bf_mpdu->len;

	अगर (bf_isampdu(bf)) अणु
		अगर (flags & ATH_TX_ERROR)
			TX_STAT_INC(sc, qnum, a_xretries);
		अन्यथा
			TX_STAT_INC(sc, qnum, a_completed);
	पूर्ण अन्यथा अणु
		अगर (ts->ts_status & ATH9K_TXERR_XRETRY)
			TX_STAT_INC(sc, qnum, xretries);
		अन्यथा
			TX_STAT_INC(sc, qnum, completed);
	पूर्ण

	अगर (ts->ts_status & ATH9K_TXERR_FILT)
		TX_STAT_INC(sc, qnum, txerr_filtered);
	अगर (ts->ts_status & ATH9K_TXERR_FIFO)
		TX_STAT_INC(sc, qnum, fअगरo_underrun);
	अगर (ts->ts_status & ATH9K_TXERR_XTXOP)
		TX_STAT_INC(sc, qnum, xtxop);
	अगर (ts->ts_status & ATH9K_TXERR_TIMER_EXPIRED)
		TX_STAT_INC(sc, qnum, समयr_exp);
	अगर (ts->ts_flags & ATH9K_TX_DESC_CFG_ERR)
		TX_STAT_INC(sc, qnum, desc_cfg_err);
	अगर (ts->ts_flags & ATH9K_TX_DATA_UNDERRUN)
		TX_STAT_INC(sc, qnum, data_underrun);
	अगर (ts->ts_flags & ATH9K_TX_DELIM_UNDERRUN)
		TX_STAT_INC(sc, qnum, delim_underrun);
पूर्ण

व्योम ath_debug_stat_rx(काष्ठा ath_softc *sc, काष्ठा ath_rx_status *rs)
अणु
	ath9k_cmn_debug_stat_rx(&sc->debug.stats.rxstats, rs);
पूर्ण

अटल sमाप_प्रकार पढ़ो_file_regidx(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "0x%08x\n", sc->debug.regidx);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_regidx(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	अचिन्हित दीर्घ regidx;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &regidx))
		वापस -EINVAL;

	sc->debug.regidx = regidx;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_regidx = अणु
	.पढ़ो = पढ़ो_file_regidx,
	.ग_लिखो = ग_लिखो_file_regidx,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_regval(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;
	u32 regval;

	ath9k_ps_wakeup(sc);
	regval = REG_READ_D(ah, sc->debug.regidx);
	ath9k_ps_restore(sc);
	len = प्र_लिखो(buf, "0x%08x\n", regval);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_regval(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	अचिन्हित दीर्घ regval;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &regval))
		वापस -EINVAL;

	ath9k_ps_wakeup(sc);
	REG_WRITE_D(ah, sc->debug.regidx, regval);
	ath9k_ps_restore(sc);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_regval = अणु
	.पढ़ो = पढ़ो_file_regval,
	.ग_लिखो = ग_लिखो_file_regval,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#घोषणा REGDUMP_LINE_SIZE	20

अटल पूर्णांक खोलो_file_regdump(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath_softc *sc = inode->i_निजी;
	अचिन्हित पूर्णांक len = 0;
	u8 *buf;
	पूर्णांक i, j = 0;
	अचिन्हित दीर्घ num_regs, regdump_len, max_reg_offset;
	अटल स्थिर काष्ठा reg_hole अणु
		u32 start;
		u32 end;
	पूर्ण reg_hole_list[] = अणु
		अणु0x0200, 0x07fcपूर्ण,
		अणु0x0c00, 0x0ffcपूर्ण,
		अणु0x2000, 0x3ffcपूर्ण,
		अणु0x4100, 0x6ffcपूर्ण,
		अणु0x705c, 0x7ffcपूर्ण,
		अणु0x0000, 0x0000पूर्ण
	पूर्ण;

	max_reg_offset = AR_SREV_9300_20_OR_LATER(sc->sc_ah) ? 0x8800 : 0xb500;
	num_regs = max_reg_offset / 4 + 1;
	regdump_len = num_regs * REGDUMP_LINE_SIZE + 1;
	buf = vदो_स्मृति(regdump_len);
	अगर (!buf)
		वापस -ENOMEM;

	ath9k_ps_wakeup(sc);
	क्रम (i = 0; i < num_regs; i++) अणु
		अगर (reg_hole_list[j].start == i << 2) अणु
			i = reg_hole_list[j].end >> 2;
			j++;
			जारी;
		पूर्ण

		len += scnम_लिखो(buf + len, regdump_len - len,
			"0x%06x 0x%08x\n", i << 2, REG_READ(sc->sc_ah, i << 2));
	पूर्ण
	ath9k_ps_restore(sc);

	file->निजी_data = buf;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_regdump = अणु
	.खोलो = खोलो_file_regdump,
	.पढ़ो = ath9k_debugfs_पढ़ो_buf,
	.release = ath9k_debugfs_release_buf,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,/* पढ़ो accesses f_pos */
पूर्ण;

अटल पूर्णांक पढ़ो_file_dump_nfcal(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(file->निजी);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_nfcal_hist *h = sc->cur_chan->caldata.nfCalHist;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_conf *conf = &common->hw->conf;
	u32 i, j;
	u8 chainmask = (ah->rxchainmask << 3) | ah->rxchainmask;
	u8 nपढ़ो;

	seq_म_लिखो(file, "Channel Noise Floor : %d\n", ah->noise);
	seq_माला_दो(file, "Chain | privNF | # Readings | NF Readings\n");
	क्रम (i = 0; i < NUM_NF_READINGS; i++) अणु
		अगर (!(chainmask & (1 << i)) ||
		    ((i >= AR5416_MAX_CHAINS) && !conf_is_ht40(conf)))
			जारी;

		nपढ़ो = AR_PHY_CCA_FILTERWINDOW_LENGTH - h[i].invalidNFcount;
		seq_म_लिखो(file, " %d\t %d\t %d\t\t", i, h[i].privNF, nपढ़ो);
		क्रम (j = 0; j < nपढ़ो; j++)
			seq_म_लिखो(file, " %d", h[i].nfCalBuffer[j]);
		seq_माला_दो(file, "\n");
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
अटल sमाप_प्रकार पढ़ो_file_btcoex(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	u32 len = 0, size = 1500;
	अक्षर *buf;
	माप_प्रकार retval;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	अगर (!sc->sc_ah->common.btcoex_enabled) अणु
		len = scnम_लिखो(buf, size, "%s\n",
				"BTCOEX is disabled");
		जाओ निकास;
	पूर्ण

	len = ath9k_dump_btcoex(sc, buf, size);
निकास:
	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_btcoex = अणु
	.पढ़ो = पढ़ो_file_btcoex,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_DYNACK
अटल sमाप_प्रकार पढ़ो_file_ackto(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%u %c\n", ah->dynack.ackto,
		      (ah->dynack.enabled) ? 'A' : 'S');

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_ackto = अणु
	.पढ़ो = पढ़ो_file_ackto,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_WOW

अटल sमाप_प्रकार पढ़ो_file_wow(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	अचिन्हित पूर्णांक len = 0, size = 32;
	sमाप_प्रकार retval;
	अक्षर *buf;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, size - len, "WOW: %s\n",
			 sc->क्रमce_wow ? "ENABLED" : "DISABLED");

	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_wow(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val != 1)
		वापस -EINVAL;

	अगर (!sc->क्रमce_wow) अणु
		sc->क्रमce_wow = true;
		ath9k_init_wow(sc->hw);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_wow = अणु
	.पढ़ो = पढ़ो_file_wow,
	.ग_लिखो = ग_लिखो_file_wow,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#पूर्ण_अगर

अटल sमाप_प्रकार पढ़ो_file_tpc(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	अचिन्हित पूर्णांक len = 0, size = 32;
	sमाप_प्रकार retval;
	अक्षर *buf;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, size - len, "%s\n",
			 ah->tpc_enabled ? "ENABLED" : "DISABLED");

	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_tpc(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;
	bool tpc_enabled;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 1)
		वापस -EINVAL;

	tpc_enabled = !!val;

	अगर (tpc_enabled != ah->tpc_enabled) अणु
		ah->tpc_enabled = tpc_enabled;

		mutex_lock(&sc->mutex);
		ath9k_set_txघातer(sc, शून्य);
		mutex_unlock(&sc->mutex);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tpc = अणु
	.पढ़ो = पढ़ो_file_tpc,
	.ग_लिखो = ग_लिखो_file_tpc,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_nf_override(काष्ठा file *file,
				     अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	अगर (ah->nf_override == 0)
		len = प्र_लिखो(buf, "off\n");
	अन्यथा
		len = प्र_लिखो(buf, "%d\n", ah->nf_override);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_nf_override(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (म_भेदन("off", buf, 3) == 0)
		val = 0;
	अन्यथा अगर (kम_से_दीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 0)
		वापस -EINVAL;

	अगर (val < -120)
		वापस -EINVAL;

	ah->nf_override = val;

	अगर (ah->curchan) अणु
		ath9k_ps_wakeup(sc);
		ath9k_hw_loadnf(ah, ah->curchan);
		ath9k_ps_restore(sc);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_nf_override = अणु
	.पढ़ो = पढ़ो_file_nf_override,
	.ग_लिखो = ग_लिखो_file_nf_override,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/* Ethtool support क्रम get-stats */

#घोषणा AMKSTR(nm) #nm "_BE", #nm "_BK", #nm "_VI", #nm "_VO"
अटल स्थिर अक्षर ath9k_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"tx_pkts_nic",
	"tx_bytes_nic",
	"rx_pkts_nic",
	"rx_bytes_nic",
	AMKSTR(d_tx_pkts),
	AMKSTR(d_tx_bytes),
	AMKSTR(d_tx_mpdus_queued),
	AMKSTR(d_tx_mpdus_completed),
	AMKSTR(d_tx_mpdu_xretries),
	AMKSTR(d_tx_aggregates),
	AMKSTR(d_tx_ampdus_queued_hw),
	AMKSTR(d_tx_ampdus_completed),
	AMKSTR(d_tx_ampdu_retries),
	AMKSTR(d_tx_ampdu_xretries),
	AMKSTR(d_tx_fअगरo_underrun),
	AMKSTR(d_tx_op_exceeded),
	AMKSTR(d_tx_समयr_expiry),
	AMKSTR(d_tx_desc_cfg_err),
	AMKSTR(d_tx_data_underrun),
	AMKSTR(d_tx_delim_underrun),
	"d_rx_crc_err",
	"d_rx_decrypt_crc_err",
	"d_rx_phy_err",
	"d_rx_mic_err",
	"d_rx_pre_delim_crc_err",
	"d_rx_post_delim_crc_err",
	"d_rx_decrypt_busy_err",

	"d_rx_phyerr_radar",
	"d_rx_phyerr_ofdm_timing",
	"d_rx_phyerr_cck_timing",

पूर्ण;
#घोषणा ATH9K_SSTATS_LEN ARRAY_SIZE(ath9k_gstrings_stats)

व्योम ath9k_get_et_strings(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर,
			  u32 sset, u8 *data)
अणु
	अगर (sset == ETH_SS_STATS)
		स_नकल(data, *ath9k_gstrings_stats,
		       माप(ath9k_gstrings_stats));
पूर्ण

पूर्णांक ath9k_get_et_sset_count(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस ATH9K_SSTATS_LEN;
	वापस 0;
पूर्ण

#घोषणा AWDATA(elem)							\
	करो अणु								\
		data[i++] = sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BE)].elem; \
		data[i++] = sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BK)].elem; \
		data[i++] = sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VI)].elem; \
		data[i++] = sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VO)].elem; \
	पूर्ण जबतक (0)

#घोषणा AWDATA_RX(elem)						\
	करो अणु							\
		data[i++] = sc->debug.stats.rxstats.elem;	\
	पूर्ण जबतक (0)

व्योम ath9k_get_et_stats(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	पूर्णांक i = 0;

	data[i++] = (sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BE)].tx_pkts_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BK)].tx_pkts_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VI)].tx_pkts_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VO)].tx_pkts_all);
	data[i++] = (sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BE)].tx_bytes_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BK)].tx_bytes_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VI)].tx_bytes_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VO)].tx_bytes_all);
	AWDATA_RX(rx_pkts_all);
	AWDATA_RX(rx_bytes_all);

	AWDATA(tx_pkts_all);
	AWDATA(tx_bytes_all);
	AWDATA(queued);
	AWDATA(completed);
	AWDATA(xretries);
	AWDATA(a_aggr);
	AWDATA(a_queued_hw);
	AWDATA(a_completed);
	AWDATA(a_retries);
	AWDATA(a_xretries);
	AWDATA(fअगरo_underrun);
	AWDATA(xtxop);
	AWDATA(समयr_exp);
	AWDATA(desc_cfg_err);
	AWDATA(data_underrun);
	AWDATA(delim_underrun);

	AWDATA_RX(crc_err);
	AWDATA_RX(decrypt_crc_err);
	AWDATA_RX(phy_err);
	AWDATA_RX(mic_err);
	AWDATA_RX(pre_delim_crc_err);
	AWDATA_RX(post_delim_crc_err);
	AWDATA_RX(decrypt_busy_err);

	AWDATA_RX(phy_err_stats[ATH9K_PHYERR_RADAR]);
	AWDATA_RX(phy_err_stats[ATH9K_PHYERR_OFDM_TIMING]);
	AWDATA_RX(phy_err_stats[ATH9K_PHYERR_CCK_TIMING]);

	WARN_ON(i != ATH9K_SSTATS_LEN);
पूर्ण

व्योम ath9k_deinit_debug(काष्ठा ath_softc *sc)
अणु
	ath9k_cmn_spectral_deinit_debug(&sc->spec_priv);
पूर्ण

पूर्णांक ath9k_init_debug(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *) common->priv;

	sc->debug.debugfs_phy = debugfs_create_dir("ath9k",
						   sc->hw->wiphy->debugfsdir);
	अगर (!sc->debug.debugfs_phy)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_ATH_DEBUG
	debugfs_create_file("debug", 0600, sc->debug.debugfs_phy,
			    sc, &fops_debug);
#पूर्ण_अगर

	ath9k_dfs_init_debug(sc);
	ath9k_tx99_init_debug(sc);
	ath9k_cmn_spectral_init_debug(&sc->spec_priv, sc->debug.debugfs_phy);

	debugfs_create_devm_seqfile(sc->dev, "dma", sc->debug.debugfs_phy,
				    पढ़ो_file_dma);
	debugfs_create_devm_seqfile(sc->dev, "interrupt", sc->debug.debugfs_phy,
				    पढ़ो_file_पूर्णांकerrupt);
	debugfs_create_devm_seqfile(sc->dev, "xmit", sc->debug.debugfs_phy,
				    पढ़ो_file_xmit);
	debugfs_create_devm_seqfile(sc->dev, "queues", sc->debug.debugfs_phy,
				    पढ़ो_file_queues);
	debugfs_create_devm_seqfile(sc->dev, "misc", sc->debug.debugfs_phy,
				    पढ़ो_file_misc);
	debugfs_create_devm_seqfile(sc->dev, "reset", sc->debug.debugfs_phy,
				    पढ़ो_file_reset);

	ath9k_cmn_debug_recv(sc->debug.debugfs_phy, &sc->debug.stats.rxstats);
	ath9k_cmn_debug_phy_err(sc->debug.debugfs_phy, &sc->debug.stats.rxstats);

	debugfs_create_u8("rx_chainmask", 0400, sc->debug.debugfs_phy,
			  &ah->rxchainmask);
	debugfs_create_u8("tx_chainmask", 0400, sc->debug.debugfs_phy,
			  &ah->txchainmask);
	debugfs_create_file("ani", 0600,
			    sc->debug.debugfs_phy, sc, &fops_ani);
	debugfs_create_bool("paprd", 0600, sc->debug.debugfs_phy,
			    &sc->sc_ah->config.enable_paprd);
	debugfs_create_file("regidx", 0600, sc->debug.debugfs_phy,
			    sc, &fops_regidx);
	debugfs_create_file("regval", 0600, sc->debug.debugfs_phy,
			    sc, &fops_regval);
	debugfs_create_bool("ignore_extcca", 0600,
			    sc->debug.debugfs_phy,
			    &ah->config.cwm_ignore_extcca);
	debugfs_create_file("regdump", 0400, sc->debug.debugfs_phy, sc,
			    &fops_regdump);
	debugfs_create_devm_seqfile(sc->dev, "dump_nfcal",
				    sc->debug.debugfs_phy,
				    पढ़ो_file_dump_nfcal);

	ath9k_cmn_debug_base_eeprom(sc->debug.debugfs_phy, sc->sc_ah);
	ath9k_cmn_debug_modal_eeprom(sc->debug.debugfs_phy, sc->sc_ah);

	debugfs_create_u32("gpio_mask", 0600,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_mask);
	debugfs_create_u32("gpio_val", 0600,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_val);
	debugfs_create_file("antenna_diversity", 0400,
			    sc->debug.debugfs_phy, sc, &fops_antenna_भागersity);
#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	debugfs_create_file("bt_ant_diversity", 0600,
			    sc->debug.debugfs_phy, sc, &fops_bt_ant_भागersity);
	debugfs_create_file("btcoex", 0400, sc->debug.debugfs_phy, sc,
			    &fops_btcoex);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_WOW
	debugfs_create_file("wow", 0600, sc->debug.debugfs_phy, sc, &fops_wow);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_DYNACK
	debugfs_create_file("ack_to", 0400, sc->debug.debugfs_phy,
			    sc, &fops_ackto);
#पूर्ण_अगर
	debugfs_create_file("tpc", 0600, sc->debug.debugfs_phy, sc, &fops_tpc);

	debugfs_create_file("nf_override", 0600,
			    sc->debug.debugfs_phy, sc, &fops_nf_override);

	वापस 0;
पूर्ण
