<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Atheros CARL9170 driver
 *
 * firmware parser
 *
 * Copyright 2009, 2010, Christian Lamparter <chunkeey@googlemail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/crc32.h>
#समावेश <linux/module.h>
#समावेश "carl9170.h"
#समावेश "fwcmd.h"
#समावेश "version.h"

अटल स्थिर u8 otus_magic[4] = अणु OTUS_MAGIC पूर्ण;

अटल स्थिर व्योम *carl9170_fw_find_desc(काष्ठा ar9170 *ar, स्थिर u8 descid[4],
	स्थिर अचिन्हित पूर्णांक len, स्थिर u8 compatible_revision)
अणु
	स्थिर काष्ठा carl9170fw_desc_head *iter;

	carl9170fw_क्रम_each_hdr(iter, ar->fw.desc) अणु
		अगर (carl9170fw_desc_cmp(iter, descid, len,
					compatible_revision))
			वापस (व्योम *)iter;
	पूर्ण

	/* needed to find the LAST desc */
	अगर (carl9170fw_desc_cmp(iter, descid, len,
				compatible_revision))
		वापस (व्योम *)iter;

	वापस शून्य;
पूर्ण

अटल पूर्णांक carl9170_fw_verअगरy_descs(काष्ठा ar9170 *ar,
	स्थिर काष्ठा carl9170fw_desc_head *head, अचिन्हित पूर्णांक max_len)
अणु
	स्थिर काष्ठा carl9170fw_desc_head *pos;
	अचिन्हित दीर्घ pos_addr, end_addr;
	अचिन्हित पूर्णांक pos_length;

	अगर (max_len < माप(*pos))
		वापस -ENODATA;

	max_len = min_t(अचिन्हित पूर्णांक, CARL9170FW_DESC_MAX_LENGTH, max_len);

	pos = head;
	pos_addr = (अचिन्हित दीर्घ) pos;
	end_addr = pos_addr + max_len;

	जबतक (pos_addr < end_addr) अणु
		अगर (pos_addr + माप(*head) > end_addr)
			वापस -E2BIG;

		pos_length = le16_to_cpu(pos->length);

		अगर (pos_length < माप(*head))
			वापस -EBADMSG;

		अगर (pos_length > max_len)
			वापस -EOVERFLOW;

		अगर (pos_addr + pos_length > end_addr)
			वापस -EMSGSIZE;

		अगर (carl9170fw_desc_cmp(pos, LAST_MAGIC,
					CARL9170FW_LAST_DESC_SIZE,
					CARL9170FW_LAST_DESC_CUR_VER))
			वापस 0;

		pos_addr += pos_length;
		pos = (व्योम *)pos_addr;
		max_len -= pos_length;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम carl9170_fw_info(काष्ठा ar9170 *ar)
अणु
	स्थिर काष्ठा carl9170fw_motd_desc *motd_desc;
	अचिन्हित पूर्णांक str_ver_len;
	u32 fw_date;

	dev_info(&ar->udev->dev, "driver   API: %s 2%03d-%02d-%02d [%d-%d]\n",
		CARL9170FW_VERSION_GIT, CARL9170FW_VERSION_YEAR,
		CARL9170FW_VERSION_MONTH, CARL9170FW_VERSION_DAY,
		CARL9170FW_API_MIN_VER, CARL9170FW_API_MAX_VER);

	motd_desc = carl9170_fw_find_desc(ar, MOTD_MAGIC,
		माप(*motd_desc), CARL9170FW_MOTD_DESC_CUR_VER);

	अगर (motd_desc) अणु
		str_ver_len = strnlen(motd_desc->release,
			CARL9170FW_MOTD_RELEASE_LEN);

		fw_date = le32_to_cpu(motd_desc->fw_year_month_day);

		dev_info(&ar->udev->dev, "firmware API: %.*s 2%03d-%02d-%02d\n",
			 str_ver_len, motd_desc->release,
			 CARL9170FW_GET_YEAR(fw_date),
			 CARL9170FW_GET_MONTH(fw_date),
			 CARL9170FW_GET_DAY(fw_date));

		strlcpy(ar->hw->wiphy->fw_version, motd_desc->release,
			माप(ar->hw->wiphy->fw_version));
	पूर्ण
पूर्ण

अटल bool valid_dma_addr(स्थिर u32 address)
अणु
	अगर (address >= AR9170_SRAM_OFFSET &&
	    address < (AR9170_SRAM_OFFSET + AR9170_SRAM_SIZE))
		वापस true;

	वापस false;
पूर्ण

अटल bool valid_cpu_addr(स्थिर u32 address)
अणु
	अगर (valid_dma_addr(address) || (address >= AR9170_PRAM_OFFSET &&
	    address < (AR9170_PRAM_OFFSET + AR9170_PRAM_SIZE)))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक carl9170_fw_checksum(काष्ठा ar9170 *ar, स्थिर __u8 *data,
				माप_प्रकार len)
अणु
	स्थिर काष्ठा carl9170fw_otus_desc *otus_desc;
	स्थिर काष्ठा carl9170fw_last_desc *last_desc;
	स्थिर काष्ठा carl9170fw_chk_desc *chk_desc;
	अचिन्हित दीर्घ fin, dअगरf;
	अचिन्हित पूर्णांक dsc_len;
	u32 crc32;

	last_desc = carl9170_fw_find_desc(ar, LAST_MAGIC,
		माप(*last_desc), CARL9170FW_LAST_DESC_CUR_VER);
	अगर (!last_desc)
		वापस -EINVAL;

	otus_desc = carl9170_fw_find_desc(ar, OTUS_MAGIC,
		माप(*otus_desc), CARL9170FW_OTUS_DESC_CUR_VER);
	अगर (!otus_desc) अणु
		dev_err(&ar->udev->dev, "failed to find compatible firmware "
			"descriptor.\n");
		वापस -ENODATA;
	पूर्ण

	chk_desc = carl9170_fw_find_desc(ar, CHK_MAGIC,
		माप(*chk_desc), CARL9170FW_CHK_DESC_CUR_VER);

	अगर (!chk_desc) अणु
		dev_warn(&ar->udev->dev, "Unprotected firmware image.\n");
		वापस 0;
	पूर्ण

	dsc_len = min_t(अचिन्हित पूर्णांक, len,
			(अचिन्हित दीर्घ)chk_desc - (अचिन्हित दीर्घ)otus_desc);

	fin = (अचिन्हित दीर्घ) last_desc + माप(*last_desc);
	dअगरf = fin - (अचिन्हित दीर्घ) otus_desc;

	अगर (dअगरf < len)
		len -= dअगरf;

	अगर (len < 256)
		वापस -EIO;

	crc32 = crc32_le(~0, data, len);
	अगर (cpu_to_le32(crc32) != chk_desc->fw_crc32) अणु
		dev_err(&ar->udev->dev, "fw checksum test failed.\n");
		वापस -ENOEXEC;
	पूर्ण

	crc32 = crc32_le(crc32, (व्योम *)otus_desc, dsc_len);
	अगर (cpu_to_le32(crc32) != chk_desc->hdr_crc32) अणु
		dev_err(&ar->udev->dev, "descriptor check failed.\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक carl9170_fw_tx_sequence(काष्ठा ar9170 *ar)
अणु
	स्थिर काष्ठा carl9170fw_txsq_desc *txsq_desc;

	txsq_desc = carl9170_fw_find_desc(ar, TXSQ_MAGIC, माप(*txsq_desc),
					  CARL9170FW_TXSQ_DESC_CUR_VER);
	अगर (txsq_desc) अणु
		ar->fw.tx_seq_table = le32_to_cpu(txsq_desc->seq_table_addr);
		अगर (!valid_cpu_addr(ar->fw.tx_seq_table))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ar->fw.tx_seq_table = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम carl9170_fw_set_अगर_combinations(काष्ठा ar9170 *ar,
					    u16 अगर_comb_types)
अणु
	अगर (ar->fw.vअगर_num < 2)
		वापस;

	ar->अगर_comb_limits[0].max = ar->fw.vअगर_num;
	ar->अगर_comb_limits[0].types = अगर_comb_types;

	ar->अगर_combs[0].num_dअगरferent_channels = 1;
	ar->अगर_combs[0].max_पूर्णांकerfaces = ar->fw.vअगर_num;
	ar->अगर_combs[0].limits = ar->अगर_comb_limits;
	ar->अगर_combs[0].n_limits = ARRAY_SIZE(ar->अगर_comb_limits);

	ar->hw->wiphy->अगरace_combinations = ar->अगर_combs;
	ar->hw->wiphy->n_अगरace_combinations = ARRAY_SIZE(ar->अगर_combs);
पूर्ण

अटल पूर्णांक carl9170_fw(काष्ठा ar9170 *ar, स्थिर __u8 *data, माप_प्रकार len)
अणु
	स्थिर काष्ठा carl9170fw_otus_desc *otus_desc;
	पूर्णांक err;
	u16 अगर_comb_types;

	err = carl9170_fw_checksum(ar, data, len);
	अगर (err)
		वापस err;

	otus_desc = carl9170_fw_find_desc(ar, OTUS_MAGIC,
		माप(*otus_desc), CARL9170FW_OTUS_DESC_CUR_VER);
	अगर (!otus_desc) अणु
		वापस -ENODATA;
	पूर्ण

#घोषणा SUPP(feat)						\
	(carl9170fw_supports(otus_desc->feature_set, feat))

	अगर (!SUPP(CARL9170FW_DUMMY_FEATURE)) अणु
		dev_err(&ar->udev->dev, "invalid firmware descriptor "
			"format detected.\n");
		वापस -EINVAL;
	पूर्ण

	ar->fw.api_version = otus_desc->api_ver;

	अगर (ar->fw.api_version < CARL9170FW_API_MIN_VER ||
	    ar->fw.api_version > CARL9170FW_API_MAX_VER) अणु
		dev_err(&ar->udev->dev, "unsupported firmware api version.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!SUPP(CARL9170FW_COMMAND_PHY) || SUPP(CARL9170FW_UNUSABLE) ||
	    !SUPP(CARL9170FW_HANDLE_BACK_REQ)) अणु
		dev_err(&ar->udev->dev, "firmware does support "
			"mandatory features.\n");
		वापस -ECANCELED;
	पूर्ण

	अगर (ilog2(le32_to_cpu(otus_desc->feature_set)) >=
		__CARL9170FW_FEATURE_NUM) अणु
		dev_warn(&ar->udev->dev, "driver does not support all "
			 "firmware features.\n");
	पूर्ण

	अगर (!SUPP(CARL9170FW_COMMAND_CAM)) अणु
		dev_info(&ar->udev->dev, "crypto offloading is disabled "
			 "by firmware.\n");
		ar->fw.disable_offload_fw = true;
	पूर्ण

	अगर (SUPP(CARL9170FW_PSM) && SUPP(CARL9170FW_FIXED_5GHZ_PSM))
		ieee80211_hw_set(ar->hw, SUPPORTS_PS);

	अगर (!SUPP(CARL9170FW_USB_INIT_FIRMWARE)) अणु
		dev_err(&ar->udev->dev, "firmware does not provide "
			"mandatory interfaces.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (SUPP(CARL9170FW_MINIBOOT))
		ar->fw.offset = le16_to_cpu(otus_desc->miniboot_size);
	अन्यथा
		ar->fw.offset = 0;

	अगर (SUPP(CARL9170FW_USB_DOWN_STREAM)) अणु
		ar->hw->extra_tx_headroom += माप(काष्ठा ar9170_stream);
		ar->fw.tx_stream = true;
	पूर्ण

	अगर (SUPP(CARL9170FW_USB_UP_STREAM))
		ar->fw.rx_stream = true;

	अगर (SUPP(CARL9170FW_RX_FILTER)) अणु
		ar->fw.rx_filter = true;
		ar->rx_filter_caps = FIF_FCSFAIL | FIF_PLCPFAIL |
			FIF_CONTROL | FIF_PSPOLL | FIF_OTHER_BSS;
	पूर्ण

	अगर (SUPP(CARL9170FW_HW_COUNTERS))
		ar->fw.hw_counters = true;

	अगर (SUPP(CARL9170FW_WOL))
		device_set_wakeup_enable(&ar->udev->dev, true);

	अगर (SUPP(CARL9170FW_RX_BA_FILTER))
		ar->fw.ba_filter = true;

	अगर_comb_types = BIT(NL80211_IFTYPE_STATION) |
			BIT(NL80211_IFTYPE_P2P_CLIENT);

	ar->fw.vअगर_num = otus_desc->vअगर_num;
	ar->fw.cmd_bufs = otus_desc->cmd_bufs;
	ar->fw.address = le32_to_cpu(otus_desc->fw_address);
	ar->fw.rx_size = le16_to_cpu(otus_desc->rx_max_frame_len);
	ar->fw.mem_blocks = min_t(अचिन्हित पूर्णांक, otus_desc->tx_descs, 0xfe);
	atomic_set(&ar->mem_मुक्त_blocks, ar->fw.mem_blocks);
	ar->fw.mem_block_size = le16_to_cpu(otus_desc->tx_frag_len);

	अगर (ar->fw.vअगर_num >= AR9170_MAX_VIRTUAL_MAC || !ar->fw.vअगर_num ||
	    ar->fw.mem_blocks < 16 || !ar->fw.cmd_bufs ||
	    ar->fw.mem_block_size < 64 || ar->fw.mem_block_size > 512 ||
	    ar->fw.rx_size > 32768 || ar->fw.rx_size < 4096 ||
	    !valid_cpu_addr(ar->fw.address)) अणु
		dev_err(&ar->udev->dev, "firmware shows obvious signs of "
			"malicious tampering.\n");
		वापस -EINVAL;
	पूर्ण

	ar->fw.beacon_addr = le32_to_cpu(otus_desc->bcn_addr);
	ar->fw.beacon_max_len = le16_to_cpu(otus_desc->bcn_len);

	अगर (valid_dma_addr(ar->fw.beacon_addr) && ar->fw.beacon_max_len >=
	    AR9170_MAC_BCN_LENGTH_MAX) अणु
		ar->hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_ADHOC);

		अगर (SUPP(CARL9170FW_WLANTX_CAB)) अणु
			अगर_comb_types |= BIT(NL80211_IFTYPE_AP);

#अगर_घोषित CONFIG_MAC80211_MESH
			अगर_comb_types |=
				BIT(NL80211_IFTYPE_MESH_POINT);
#पूर्ण_अगर /* CONFIG_MAC80211_MESH */
		पूर्ण
	पूर्ण

	carl9170_fw_set_अगर_combinations(ar, अगर_comb_types);

	ar->hw->wiphy->पूर्णांकerface_modes |= अगर_comb_types;

	ar->hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	/* As IBSS Encryption is software-based, IBSS RSN is supported. */
	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
		 WIPHY_FLAG_IBSS_RSN | WIPHY_FLAG_SUPPORTS_TDLS;

#अघोषित SUPPORTED
	वापस carl9170_fw_tx_sequence(ar);
पूर्ण

अटल काष्ठा carl9170fw_desc_head *
carl9170_find_fw_desc(काष्ठा ar9170 *ar, स्थिर __u8 *fw_data, स्थिर माप_प्रकार len)

अणु
	पूर्णांक scan = 0, found = 0;

	अगर (!carl9170fw_size_check(len)) अणु
		dev_err(&ar->udev->dev, "firmware size is out of bound.\n");
		वापस शून्य;
	पूर्ण

	जबतक (scan < len - माप(काष्ठा carl9170fw_desc_head)) अणु
		अगर (fw_data[scan++] == otus_magic[found])
			found++;
		अन्यथा
			found = 0;

		अगर (scan >= len)
			अवरोध;

		अगर (found == माप(otus_magic))
			अवरोध;
	पूर्ण

	अगर (found != माप(otus_magic))
		वापस शून्य;

	वापस (व्योम *)&fw_data[scan - found];
पूर्ण

पूर्णांक carl9170_parse_firmware(काष्ठा ar9170 *ar)
अणु
	स्थिर काष्ठा carl9170fw_desc_head *fw_desc = शून्य;
	स्थिर काष्ठा firmware *fw = ar->fw.fw;
	अचिन्हित दीर्घ header_offset = 0;
	पूर्णांक err;

	अगर (WARN_ON(!fw))
		वापस -EINVAL;

	fw_desc = carl9170_find_fw_desc(ar, fw->data, fw->size);

	अगर (!fw_desc) अणु
		dev_err(&ar->udev->dev, "unsupported firmware.\n");
		वापस -ENODATA;
	पूर्ण

	header_offset = (अचिन्हित दीर्घ)fw_desc - (अचिन्हित दीर्घ)fw->data;

	err = carl9170_fw_verअगरy_descs(ar, fw_desc, fw->size - header_offset);
	अगर (err) अणु
		dev_err(&ar->udev->dev, "damaged firmware (%d).\n", err);
		वापस err;
	पूर्ण

	ar->fw.desc = fw_desc;

	carl9170_fw_info(ar);

	err = carl9170_fw(ar, fw->data, fw->size);
	अगर (err) अणु
		dev_err(&ar->udev->dev, "failed to parse firmware (%d).\n",
			err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
