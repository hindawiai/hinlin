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

#समावेश "common.h"

अटल sमाप_प्रकार पढ़ो_file_modal_eeprom(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_hw *ah = file->निजी_data;
	u32 len = 0, size = 6000;
	अक्षर *buf;
	माप_प्रकार retval;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	len = ah->eep_ops->dump_eeprom(ah, false, buf, len, size);

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_modal_eeprom = अणु
	.पढ़ो = पढ़ो_file_modal_eeprom,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;


व्योम ath9k_cmn_debug_modal_eeprom(काष्ठा dentry *debugfs_phy,
				  काष्ठा ath_hw *ah)
अणु
	debugfs_create_file("modal_eeprom", 0400, debugfs_phy, ah,
			    &fops_modal_eeprom);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_debug_modal_eeprom);

अटल sमाप_प्रकार पढ़ो_file_base_eeprom(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_hw *ah = file->निजी_data;
	u32 len = 0, size = 1500;
	sमाप_प्रकार retval = 0;
	अक्षर *buf;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len = ah->eep_ops->dump_eeprom(ah, true, buf, len, size);

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_base_eeprom = अणु
	.पढ़ो = पढ़ो_file_base_eeprom,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath9k_cmn_debug_base_eeprom(काष्ठा dentry *debugfs_phy,
				 काष्ठा ath_hw *ah)
अणु
	debugfs_create_file("base_eeprom", 0400, debugfs_phy, ah,
			    &fops_base_eeprom);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_debug_base_eeprom);

व्योम ath9k_cmn_debug_stat_rx(काष्ठा ath_rx_stats *rxstats,
			     काष्ठा ath_rx_status *rs)
अणु
#घोषणा RX_PHY_ERR_INC(c) rxstats->phy_err_stats[c]++
#घोषणा RX_CMN_STAT_INC(c) (rxstats->c++)

	RX_CMN_STAT_INC(rx_pkts_all);
	rxstats->rx_bytes_all += rs->rs_datalen;

	अगर (rs->rs_status & ATH9K_RXERR_CRC)
		RX_CMN_STAT_INC(crc_err);
	अगर (rs->rs_status & ATH9K_RXERR_DECRYPT)
		RX_CMN_STAT_INC(decrypt_crc_err);
	अगर (rs->rs_status & ATH9K_RXERR_MIC)
		RX_CMN_STAT_INC(mic_err);
	अगर (rs->rs_status & ATH9K_RX_DELIM_CRC_PRE)
		RX_CMN_STAT_INC(pre_delim_crc_err);
	अगर (rs->rs_status & ATH9K_RX_DELIM_CRC_POST)
		RX_CMN_STAT_INC(post_delim_crc_err);
	अगर (rs->rs_status & ATH9K_RX_DECRYPT_BUSY)
		RX_CMN_STAT_INC(decrypt_busy_err);

	अगर (rs->rs_status & ATH9K_RXERR_PHY) अणु
		RX_CMN_STAT_INC(phy_err);
		अगर (rs->rs_phyerr < ATH9K_PHYERR_MAX)
			RX_PHY_ERR_INC(rs->rs_phyerr);
	पूर्ण

#अघोषित RX_CMN_STAT_INC
#अघोषित RX_PHY_ERR_INC
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_debug_stat_rx);

अटल sमाप_प्रकार पढ़ो_file_recv(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
#घोषणा RXS_ERR(s, e)					\
	करो अणु						\
		len += scnम_लिखो(buf + len, size - len,	\
				 "%18s : %10u\n", s,	\
				 rxstats->e);		\
	पूर्ण जबतक (0)

	काष्ठा ath_rx_stats *rxstats = file->निजी_data;
	अक्षर *buf;
	अचिन्हित पूर्णांक len = 0, size = 1600;
	sमाप_प्रकार retval = 0;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	RXS_ERR("PKTS-ALL", rx_pkts_all);
	RXS_ERR("BYTES-ALL", rx_bytes_all);
	RXS_ERR("BEACONS", rx_beacons);
	RXS_ERR("FRAGS", rx_frags);
	RXS_ERR("SPECTRAL", rx_spectral);
	RXS_ERR("SPECTRAL SMPL GOOD", rx_spectral_sample_good);
	RXS_ERR("SPECTRAL SMPL ERR", rx_spectral_sample_err);

	RXS_ERR("CRC ERR", crc_err);
	RXS_ERR("DECRYPT CRC ERR", decrypt_crc_err);
	RXS_ERR("PHY ERR", phy_err);
	RXS_ERR("MIC ERR", mic_err);
	RXS_ERR("PRE-DELIM CRC ERR", pre_delim_crc_err);
	RXS_ERR("POST-DELIM CRC ERR", post_delim_crc_err);
	RXS_ERR("DECRYPT BUSY ERR", decrypt_busy_err);
	RXS_ERR("LENGTH-ERR", rx_len_err);
	RXS_ERR("OOM-ERR", rx_oom_err);
	RXS_ERR("RATE-ERR", rx_rate_err);
	RXS_ERR("TOO-MANY-FRAGS", rx_too_many_frags_err);

	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;

#अघोषित RXS_ERR
पूर्ण

अटल स्थिर काष्ठा file_operations fops_recv = अणु
	.पढ़ो = पढ़ो_file_recv,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath9k_cmn_debug_recv(काष्ठा dentry *debugfs_phy,
			  काष्ठा ath_rx_stats *rxstats)
अणु
	debugfs_create_file("recv", 0400, debugfs_phy, rxstats, &fops_recv);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_debug_recv);

अटल sमाप_प्रकार पढ़ो_file_phy_err(काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
#घोषणा PHY_ERR(s, p) \
	len += scnम_लिखो(buf + len, size - len, "%22s : %10u\n", s, \
			 rxstats->phy_err_stats[p])

	काष्ठा ath_rx_stats *rxstats = file->निजी_data;
	अक्षर *buf;
	अचिन्हित पूर्णांक len = 0, size = 1600;
	sमाप_प्रकार retval = 0;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	PHY_ERR("UNDERRUN ERR", ATH9K_PHYERR_UNDERRUN);
	PHY_ERR("TIMING ERR", ATH9K_PHYERR_TIMING);
	PHY_ERR("PARITY ERR", ATH9K_PHYERR_PARITY);
	PHY_ERR("RATE ERR", ATH9K_PHYERR_RATE);
	PHY_ERR("LENGTH ERR", ATH9K_PHYERR_LENGTH);
	PHY_ERR("RADAR ERR", ATH9K_PHYERR_RADAR);
	PHY_ERR("SERVICE ERR", ATH9K_PHYERR_SERVICE);
	PHY_ERR("TOR ERR", ATH9K_PHYERR_TOR);

	PHY_ERR("OFDM-TIMING ERR", ATH9K_PHYERR_OFDM_TIMING);
	PHY_ERR("OFDM-SIGNAL-PARITY ERR", ATH9K_PHYERR_OFDM_SIGNAL_PARITY);
	PHY_ERR("OFDM-RATE ERR", ATH9K_PHYERR_OFDM_RATE_ILLEGAL);
	PHY_ERR("OFDM-LENGTH ERR", ATH9K_PHYERR_OFDM_LENGTH_ILLEGAL);
	PHY_ERR("OFDM-POWER-DROP ERR", ATH9K_PHYERR_OFDM_POWER_DROP);
	PHY_ERR("OFDM-SERVICE ERR", ATH9K_PHYERR_OFDM_SERVICE);
	PHY_ERR("OFDM-RESTART ERR", ATH9K_PHYERR_OFDM_RESTART);

	PHY_ERR("CCK-BLOCKER ERR", ATH9K_PHYERR_CCK_BLOCKER);
	PHY_ERR("CCK-TIMING ERR", ATH9K_PHYERR_CCK_TIMING);
	PHY_ERR("CCK-HEADER-CRC ERR", ATH9K_PHYERR_CCK_HEADER_CRC);
	PHY_ERR("CCK-RATE ERR", ATH9K_PHYERR_CCK_RATE_ILLEGAL);
	PHY_ERR("CCK-LENGTH ERR", ATH9K_PHYERR_CCK_LENGTH_ILLEGAL);
	PHY_ERR("CCK-POWER-DROP ERR", ATH9K_PHYERR_CCK_POWER_DROP);
	PHY_ERR("CCK-SERVICE ERR", ATH9K_PHYERR_CCK_SERVICE);
	PHY_ERR("CCK-RESTART ERR", ATH9K_PHYERR_CCK_RESTART);

	PHY_ERR("HT-CRC ERR", ATH9K_PHYERR_HT_CRC_ERROR);
	PHY_ERR("HT-LENGTH ERR", ATH9K_PHYERR_HT_LENGTH_ILLEGAL);
	PHY_ERR("HT-RATE ERR", ATH9K_PHYERR_HT_RATE_ILLEGAL);
	PHY_ERR("HT-ZLF ERR", ATH9K_PHYERR_HT_ZLF);

	PHY_ERR("FALSE-RADAR-EXT ERR", ATH9K_PHYERR_FALSE_RADAR_EXT);
	PHY_ERR("GREEN-FIELD ERR", ATH9K_PHYERR_GREEN_FIELD);
	PHY_ERR("SPECTRAL ERR", ATH9K_PHYERR_SPECTRAL);

	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;

#अघोषित PHY_ERR
पूर्ण

अटल स्थिर काष्ठा file_operations fops_phy_err = अणु
	.पढ़ो = पढ़ो_file_phy_err,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath9k_cmn_debug_phy_err(काष्ठा dentry *debugfs_phy,
			     काष्ठा ath_rx_stats *rxstats)
अणु
	debugfs_create_file("phy_err", 0400, debugfs_phy, rxstats,
			    &fops_phy_err);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_debug_phy_err);
