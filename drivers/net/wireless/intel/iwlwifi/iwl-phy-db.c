<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2020 Intel Corporation
 * Copyright (C) 2016 Intel Deutschland GmbH
 */
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>

#समावेश "iwl-drv.h"
#समावेश "iwl-phy-db.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-op-mode.h"
#समावेश "iwl-trans.h"

#घोषणा CHANNEL_NUM_SIZE	4	/* num of channels in calib_ch size */

काष्ठा iwl_phy_db_entry अणु
	u16	size;
	u8	*data;
पूर्ण;

/**
 * काष्ठा iwl_phy_db - stores phy configuration and calibration data.
 *
 * @cfg: phy configuration.
 * @calib_nch: non channel specअगरic calibration data.
 * @n_group_papd: number of entries in papd channel group.
 * @calib_ch_group_papd: calibration data related to papd channel group.
 * @n_group_txp: number of entries in tx घातer channel group.
 * @calib_ch_group_txp: calibration data related to tx घातer chanel group.
 * @trans: transport layer
 */
काष्ठा iwl_phy_db अणु
	काष्ठा iwl_phy_db_entry	cfg;
	काष्ठा iwl_phy_db_entry	calib_nch;
	पूर्णांक n_group_papd;
	काष्ठा iwl_phy_db_entry	*calib_ch_group_papd;
	पूर्णांक n_group_txp;
	काष्ठा iwl_phy_db_entry	*calib_ch_group_txp;

	काष्ठा iwl_trans *trans;
पूर्ण;

क्रमागत iwl_phy_db_section_type अणु
	IWL_PHY_DB_CFG = 1,
	IWL_PHY_DB_CALIB_NCH,
	IWL_PHY_DB_UNUSED,
	IWL_PHY_DB_CALIB_CHG_PAPD,
	IWL_PHY_DB_CALIB_CHG_TXP,
	IWL_PHY_DB_MAX
पूर्ण;

#घोषणा PHY_DB_CMD 0x6c

/* क्रम parsing of tx घातer channel group data that comes from the firmware*/
काष्ठा iwl_phy_db_chg_txp अणु
	__le32 space;
	__le16 max_channel_idx;
पूर्ण __packed;

काष्ठा iwl_phy_db *iwl_phy_db_init(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_phy_db *phy_db = kzalloc(माप(काष्ठा iwl_phy_db),
					    GFP_KERNEL);

	अगर (!phy_db)
		वापस phy_db;

	phy_db->trans = trans;

	phy_db->n_group_txp = -1;
	phy_db->n_group_papd = -1;

	/* TODO: add शेष values of the phy db. */
	वापस phy_db;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_phy_db_init);

/*
 * get phy db section: वापसs a poपूर्णांकer to a phy db section specअगरied by
 * type and channel group id.
 */
अटल काष्ठा iwl_phy_db_entry *
iwl_phy_db_get_section(काष्ठा iwl_phy_db *phy_db,
		       क्रमागत iwl_phy_db_section_type type,
		       u16 chg_id)
अणु
	अगर (!phy_db || type >= IWL_PHY_DB_MAX)
		वापस शून्य;

	चयन (type) अणु
	हाल IWL_PHY_DB_CFG:
		वापस &phy_db->cfg;
	हाल IWL_PHY_DB_CALIB_NCH:
		वापस &phy_db->calib_nch;
	हाल IWL_PHY_DB_CALIB_CHG_PAPD:
		अगर (chg_id >= phy_db->n_group_papd)
			वापस शून्य;
		वापस &phy_db->calib_ch_group_papd[chg_id];
	हाल IWL_PHY_DB_CALIB_CHG_TXP:
		अगर (chg_id >= phy_db->n_group_txp)
			वापस शून्य;
		वापस &phy_db->calib_ch_group_txp[chg_id];
	शेष:
		वापस शून्य;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम iwl_phy_db_मुक्त_section(काष्ठा iwl_phy_db *phy_db,
				    क्रमागत iwl_phy_db_section_type type,
				    u16 chg_id)
अणु
	काष्ठा iwl_phy_db_entry *entry =
				iwl_phy_db_get_section(phy_db, type, chg_id);
	अगर (!entry)
		वापस;

	kमुक्त(entry->data);
	entry->data = शून्य;
	entry->size = 0;
पूर्ण

व्योम iwl_phy_db_मुक्त(काष्ठा iwl_phy_db *phy_db)
अणु
	पूर्णांक i;

	अगर (!phy_db)
		वापस;

	iwl_phy_db_मुक्त_section(phy_db, IWL_PHY_DB_CFG, 0);
	iwl_phy_db_मुक्त_section(phy_db, IWL_PHY_DB_CALIB_NCH, 0);

	क्रम (i = 0; i < phy_db->n_group_papd; i++)
		iwl_phy_db_मुक्त_section(phy_db, IWL_PHY_DB_CALIB_CHG_PAPD, i);
	kमुक्त(phy_db->calib_ch_group_papd);

	क्रम (i = 0; i < phy_db->n_group_txp; i++)
		iwl_phy_db_मुक्त_section(phy_db, IWL_PHY_DB_CALIB_CHG_TXP, i);
	kमुक्त(phy_db->calib_ch_group_txp);

	kमुक्त(phy_db);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_phy_db_मुक्त);

पूर्णांक iwl_phy_db_set_section(काष्ठा iwl_phy_db *phy_db,
			   काष्ठा iwl_rx_packet *pkt)
अणु
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);
	काष्ठा iwl_calib_res_notअगर_phy_db *phy_db_notअगर =
			(काष्ठा iwl_calib_res_notअगर_phy_db *)pkt->data;
	क्रमागत iwl_phy_db_section_type type;
	u16 size;
	काष्ठा iwl_phy_db_entry *entry;
	u16 chg_id = 0;

	अगर (pkt_len < माप(*phy_db_notअगर))
		वापस -EINVAL;

	type = le16_to_cpu(phy_db_notअगर->type);
	size = le16_to_cpu(phy_db_notअगर->length);

	अगर (pkt_len < माप(*phy_db_notअगर) + size)
		वापस -EINVAL;

	अगर (!phy_db)
		वापस -EINVAL;

	अगर (type == IWL_PHY_DB_CALIB_CHG_PAPD) अणु
		chg_id = le16_to_cpup((__le16 *)phy_db_notअगर->data);
		अगर (phy_db && !phy_db->calib_ch_group_papd) अणु
			/*
			 * Firmware sends the largest index first, so we can use
			 * it to know how much we should allocate.
			 */
			phy_db->calib_ch_group_papd = kसुस्मृति(chg_id + 1,
							      माप(काष्ठा iwl_phy_db_entry),
							      GFP_ATOMIC);
			अगर (!phy_db->calib_ch_group_papd)
				वापस -ENOMEM;
			phy_db->n_group_papd = chg_id + 1;
		पूर्ण
	पूर्ण अन्यथा अगर (type == IWL_PHY_DB_CALIB_CHG_TXP) अणु
		chg_id = le16_to_cpup((__le16 *)phy_db_notअगर->data);
		अगर (phy_db && !phy_db->calib_ch_group_txp) अणु
			/*
			 * Firmware sends the largest index first, so we can use
			 * it to know how much we should allocate.
			 */
			phy_db->calib_ch_group_txp = kसुस्मृति(chg_id + 1,
							     माप(काष्ठा iwl_phy_db_entry),
							     GFP_ATOMIC);
			अगर (!phy_db->calib_ch_group_txp)
				वापस -ENOMEM;
			phy_db->n_group_txp = chg_id + 1;
		पूर्ण
	पूर्ण

	entry = iwl_phy_db_get_section(phy_db, type, chg_id);
	अगर (!entry)
		वापस -EINVAL;

	kमुक्त(entry->data);
	entry->data = kmemdup(phy_db_notअगर->data, size, GFP_ATOMIC);
	अगर (!entry->data) अणु
		entry->size = 0;
		वापस -ENOMEM;
	पूर्ण

	entry->size = size;

	IWL_DEBUG_INFO(phy_db->trans,
		       "%s(%d): [PHYDB]SET: Type %d , Size: %d\n",
		       __func__, __LINE__, type, size);

	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_phy_db_set_section);

अटल पूर्णांक is_valid_channel(u16 ch_id)
अणु
	अगर (ch_id <= 14 ||
	    (36 <= ch_id && ch_id <= 64 && ch_id % 4 == 0) ||
	    (100 <= ch_id && ch_id <= 140 && ch_id % 4 == 0) ||
	    (145 <= ch_id && ch_id <= 165 && ch_id % 4 == 1))
		वापस 1;
	वापस 0;
पूर्ण

अटल u8 ch_id_to_ch_index(u16 ch_id)
अणु
	अगर (WARN_ON(!is_valid_channel(ch_id)))
		वापस 0xff;

	अगर (ch_id <= 14)
		वापस ch_id - 1;
	अगर (ch_id <= 64)
		वापस (ch_id + 20) / 4;
	अगर (ch_id <= 140)
		वापस (ch_id - 12) / 4;
	वापस (ch_id - 13) / 4;
पूर्ण


अटल u16 channel_id_to_papd(u16 ch_id)
अणु
	अगर (WARN_ON(!is_valid_channel(ch_id)))
		वापस 0xff;

	अगर (1 <= ch_id && ch_id <= 14)
		वापस 0;
	अगर (36 <= ch_id && ch_id <= 64)
		वापस 1;
	अगर (100 <= ch_id && ch_id <= 140)
		वापस 2;
	वापस 3;
पूर्ण

अटल u16 channel_id_to_txp(काष्ठा iwl_phy_db *phy_db, u16 ch_id)
अणु
	काष्ठा iwl_phy_db_chg_txp *txp_chg;
	पूर्णांक i;
	u8 ch_index = ch_id_to_ch_index(ch_id);
	अगर (ch_index == 0xff)
		वापस 0xff;

	क्रम (i = 0; i < phy_db->n_group_txp; i++) अणु
		txp_chg = (व्योम *)phy_db->calib_ch_group_txp[i].data;
		अगर (!txp_chg)
			वापस 0xff;
		/*
		 * Looking क्रम the first channel group that its max channel is
		 * higher then wanted channel.
		 */
		अगर (le16_to_cpu(txp_chg->max_channel_idx) >= ch_index)
			वापस i;
	पूर्ण
	वापस 0xff;
पूर्ण
अटल
पूर्णांक iwl_phy_db_get_section_data(काष्ठा iwl_phy_db *phy_db,
				u32 type, u8 **data, u16 *size, u16 ch_id)
अणु
	काष्ठा iwl_phy_db_entry *entry;
	u16 ch_group_id = 0;

	अगर (!phy_db)
		वापस -EINVAL;

	/* find wanted channel group */
	अगर (type == IWL_PHY_DB_CALIB_CHG_PAPD)
		ch_group_id = channel_id_to_papd(ch_id);
	अन्यथा अगर (type == IWL_PHY_DB_CALIB_CHG_TXP)
		ch_group_id = channel_id_to_txp(phy_db, ch_id);

	entry = iwl_phy_db_get_section(phy_db, type, ch_group_id);
	अगर (!entry)
		वापस -EINVAL;

	*data = entry->data;
	*size = entry->size;

	IWL_DEBUG_INFO(phy_db->trans,
		       "%s(%d): [PHYDB] GET: Type %d , Size: %d\n",
		       __func__, __LINE__, type, *size);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_send_phy_db_cmd(काष्ठा iwl_phy_db *phy_db, u16 type,
			       u16 length, व्योम *data)
अणु
	काष्ठा iwl_phy_db_cmd phy_db_cmd;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = PHY_DB_CMD,
	पूर्ण;

	IWL_DEBUG_INFO(phy_db->trans,
		       "Sending PHY-DB hcmd of type %d, of length %d\n",
		       type, length);

	/* Set phy db cmd variables */
	phy_db_cmd.type = cpu_to_le16(type);
	phy_db_cmd.length = cpu_to_le16(length);

	/* Set hcmd variables */
	cmd.data[0] = &phy_db_cmd;
	cmd.len[0] = माप(काष्ठा iwl_phy_db_cmd);
	cmd.data[1] = data;
	cmd.len[1] = length;
	cmd.dataflags[1] = IWL_HCMD_DFL_NOCOPY;

	वापस iwl_trans_send_cmd(phy_db->trans, &cmd);
पूर्ण

अटल पूर्णांक iwl_phy_db_send_all_channel_groups(
					काष्ठा iwl_phy_db *phy_db,
					क्रमागत iwl_phy_db_section_type type,
					u8 max_ch_groups)
अणु
	u16 i;
	पूर्णांक err;
	काष्ठा iwl_phy_db_entry *entry;

	/* Send all the  channel specअगरic groups to operational fw */
	क्रम (i = 0; i < max_ch_groups; i++) अणु
		entry = iwl_phy_db_get_section(phy_db,
					       type,
					       i);
		अगर (!entry)
			वापस -EINVAL;

		अगर (!entry->size)
			जारी;

		/* Send the requested PHY DB section */
		err = iwl_send_phy_db_cmd(phy_db,
					  type,
					  entry->size,
					  entry->data);
		अगर (err) अणु
			IWL_ERR(phy_db->trans,
				"Can't SEND phy_db section %d (%d), err %d\n",
				type, i, err);
			वापस err;
		पूर्ण

		IWL_DEBUG_INFO(phy_db->trans,
			       "Sent PHY_DB HCMD, type = %d num = %d\n",
			       type, i);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_send_phy_db_data(काष्ठा iwl_phy_db *phy_db)
अणु
	u8 *data = शून्य;
	u16 size = 0;
	पूर्णांक err;

	IWL_DEBUG_INFO(phy_db->trans,
		       "Sending phy db data and configuration to runtime image\n");

	/* Send PHY DB CFG section */
	err = iwl_phy_db_get_section_data(phy_db, IWL_PHY_DB_CFG,
					  &data, &size, 0);
	अगर (err) अणु
		IWL_ERR(phy_db->trans, "Cannot get Phy DB cfg section\n");
		वापस err;
	पूर्ण

	err = iwl_send_phy_db_cmd(phy_db, IWL_PHY_DB_CFG, size, data);
	अगर (err) अणु
		IWL_ERR(phy_db->trans,
			"Cannot send HCMD of  Phy DB cfg section\n");
		वापस err;
	पूर्ण

	err = iwl_phy_db_get_section_data(phy_db, IWL_PHY_DB_CALIB_NCH,
					  &data, &size, 0);
	अगर (err) अणु
		IWL_ERR(phy_db->trans,
			"Cannot get Phy DB non specific channel section\n");
		वापस err;
	पूर्ण

	err = iwl_send_phy_db_cmd(phy_db, IWL_PHY_DB_CALIB_NCH, size, data);
	अगर (err) अणु
		IWL_ERR(phy_db->trans,
			"Cannot send HCMD of Phy DB non specific channel section\n");
		वापस err;
	पूर्ण

	/* Send all the TXP channel specअगरic data */
	err = iwl_phy_db_send_all_channel_groups(phy_db,
						 IWL_PHY_DB_CALIB_CHG_PAPD,
						 phy_db->n_group_papd);
	अगर (err) अणु
		IWL_ERR(phy_db->trans,
			"Cannot send channel specific PAPD groups\n");
		वापस err;
	पूर्ण

	/* Send all the TXP channel specअगरic data */
	err = iwl_phy_db_send_all_channel_groups(phy_db,
						 IWL_PHY_DB_CALIB_CHG_TXP,
						 phy_db->n_group_txp);
	अगर (err) अणु
		IWL_ERR(phy_db->trans,
			"Cannot send channel specific TX power groups\n");
		वापस err;
	पूर्ण

	IWL_DEBUG_INFO(phy_db->trans,
		       "Finished sending phy db non channel data\n");
	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_send_phy_db_data);
