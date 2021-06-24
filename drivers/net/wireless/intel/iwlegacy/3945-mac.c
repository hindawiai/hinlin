<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portions of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>

#समावेश <net/ieee80211_radiotap.h>
#समावेश <net/mac80211.h>

#समावेश <यंत्र/भाग64.h>

#घोषणा DRV_NAME	"iwl3945"

#समावेश "commands.h"
#समावेश "common.h"
#समावेश "3945.h"
#समावेश "iwl-spectrum.h"

/*
 * module name, copyright, version, etc.
 */

#घोषणा DRV_DESCRIPTION	\
"Intel(R) PRO/Wireless 3945ABG/BG Network Connection driver for Linux"

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
#घोषणा VD "d"
#अन्यथा
#घोषणा VD
#पूर्ण_अगर

/*
 * add "s" to indicate spectrum measurement included.
 * we add it here to be consistent with previous releases in which
 * this was configurable.
 */
#घोषणा DRV_VERSION  IWLWIFI_VERSION VD "s"
#घोषणा DRV_COPYRIGHT	"Copyright(c) 2003-2011 Intel Corporation"
#घोषणा DRV_AUTHOR     "<ilw@linux.intel.com>"

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR(DRV_COPYRIGHT " " DRV_AUTHOR);
MODULE_LICENSE("GPL");

 /* module parameters */
काष्ठा il_mod_params il3945_mod_params = अणु
	.sw_crypto = 1,
	.restart_fw = 1,
	.disable_hw_scan = 1,
	/* the rest are 0 by शेष */
पूर्ण;

/**
 * il3945_get_antenna_flags - Get antenna flags क्रम RXON command
 * @il: eeprom and antenna fields are used to determine antenna flags
 *
 * il->eeprom39  is used to determine अगर antenna AUX/MAIN are reversed
 * il3945_mod_params.antenna specअगरies the antenna भागersity mode:
 *
 * IL_ANTENNA_DIVERSITY - NIC selects best antenna by itself
 * IL_ANTENNA_MAIN      - Force MAIN antenna
 * IL_ANTENNA_AUX       - Force AUX antenna
 */
__le32
il3945_get_antenna_flags(स्थिर काष्ठा il_priv *il)
अणु
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;

	चयन (il3945_mod_params.antenna) अणु
	हाल IL_ANTENNA_DIVERSITY:
		वापस 0;

	हाल IL_ANTENNA_MAIN:
		अगर (eeprom->antenna_चयन_type)
			वापस RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_B_MSK;
		वापस RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_A_MSK;

	हाल IL_ANTENNA_AUX:
		अगर (eeprom->antenna_चयन_type)
			वापस RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_A_MSK;
		वापस RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_B_MSK;
	पूर्ण

	/* bad antenna selector value */
	IL_ERR("Bad antenna selector value (0x%x)\n",
	       il3945_mod_params.antenna);

	वापस 0;		/* "diversity" is शेष अगर error */
पूर्ण

अटल पूर्णांक
il3945_set_ccmp_dynamic_key_info(काष्ठा il_priv *il,
				 काष्ठा ieee80211_key_conf *keyconf, u8 sta_id)
अणु
	अचिन्हित दीर्घ flags;
	__le16 key_flags = 0;
	पूर्णांक ret;

	key_flags |= (STA_KEY_FLG_CCMP | STA_KEY_FLG_MAP_KEY_MSK);
	key_flags |= cpu_to_le16(keyconf->keyidx << STA_KEY_FLG_KEYID_POS);

	अगर (sta_id == il->hw_params.bcast_id)
		key_flags |= STA_KEY_MULTICAST_MSK;

	keyconf->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
	keyconf->hw_key_idx = keyconf->keyidx;
	key_flags &= ~STA_KEY_FLG_INVALID;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].keyinfo.cipher = keyconf->cipher;
	il->stations[sta_id].keyinfo.keylen = keyconf->keylen;
	स_नकल(il->stations[sta_id].keyinfo.key, keyconf->key, keyconf->keylen);

	स_नकल(il->stations[sta_id].sta.key.key, keyconf->key, keyconf->keylen);

	अगर ((il->stations[sta_id].sta.key.
	     key_flags & STA_KEY_FLG_ENCRYPT_MSK) == STA_KEY_FLG_NO_ENC)
		il->stations[sta_id].sta.key.key_offset =
		    il_get_मुक्त_ucode_key_idx(il);
	/* अन्यथा, we are overriding an existing key => no need to allocated room
	 * in uCode. */

	WARN(il->stations[sta_id].sta.key.key_offset == WEP_INVALID_OFFSET,
	     "no space for a new key");

	il->stations[sta_id].sta.key.key_flags = key_flags;
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;

	D_INFO("hwcrypto: modify ucode station key info\n");

	ret = il_send_add_sta(il, &il->stations[sta_id].sta, CMD_ASYNC);

	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक
il3945_set_tkip_dynamic_key_info(काष्ठा il_priv *il,
				 काष्ठा ieee80211_key_conf *keyconf, u8 sta_id)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
il3945_set_wep_dynamic_key_info(काष्ठा il_priv *il,
				काष्ठा ieee80211_key_conf *keyconf, u8 sta_id)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
il3945_clear_sta_key_info(काष्ठा il_priv *il, u8 sta_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा il_addsta_cmd sta_cmd;

	spin_lock_irqsave(&il->sta_lock, flags);
	स_रखो(&il->stations[sta_id].keyinfo, 0, माप(काष्ठा il_hw_key));
	स_रखो(&il->stations[sta_id].sta.key, 0, माप(काष्ठा il4965_keyinfo));
	il->stations[sta_id].sta.key.key_flags = STA_KEY_FLG_NO_ENC;
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	D_INFO("hwcrypto: clear ucode station key info\n");
	वापस il_send_add_sta(il, &sta_cmd, CMD_SYNC);
पूर्ण

अटल पूर्णांक
il3945_set_dynamic_key(काष्ठा il_priv *il, काष्ठा ieee80211_key_conf *keyconf,
		       u8 sta_id)
अणु
	पूर्णांक ret = 0;

	keyconf->hw_key_idx = HW_KEY_DYNAMIC;

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		ret = il3945_set_ccmp_dynamic_key_info(il, keyconf, sta_id);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		ret = il3945_set_tkip_dynamic_key_info(il, keyconf, sta_id);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		ret = il3945_set_wep_dynamic_key_info(il, keyconf, sta_id);
		अवरोध;
	शेष:
		IL_ERR("Unknown alg: %s alg=%x\n", __func__, keyconf->cipher);
		ret = -EINVAL;
	पूर्ण

	D_WEP("Set dynamic key: alg=%x len=%d idx=%d sta=%d ret=%d\n",
	      keyconf->cipher, keyconf->keylen, keyconf->keyidx, sta_id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
il3945_हटाओ_अटल_key(काष्ठा il_priv *il)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
il3945_set_अटल_key(काष्ठा il_priv *il, काष्ठा ieee80211_key_conf *key)
अणु
	अगर (key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	    key->cipher == WLAN_CIPHER_SUITE_WEP104)
		वापस -EOPNOTSUPP;

	IL_ERR("Static key invalid: cipher %x\n", key->cipher);
	वापस -EINVAL;
पूर्ण

अटल व्योम
il3945_clear_मुक्त_frames(काष्ठा il_priv *il)
अणु
	काष्ठा list_head *element;

	D_INFO("%d frames on pre-allocated heap on clear.\n", il->frames_count);

	जबतक (!list_empty(&il->मुक्त_frames)) अणु
		element = il->मुक्त_frames.next;
		list_del(element);
		kमुक्त(list_entry(element, काष्ठा il3945_frame, list));
		il->frames_count--;
	पूर्ण

	अगर (il->frames_count) अणु
		IL_WARN("%d frames still in use.  Did we lose one?\n",
			il->frames_count);
		il->frames_count = 0;
	पूर्ण
पूर्ण

अटल काष्ठा il3945_frame *
il3945_get_मुक्त_frame(काष्ठा il_priv *il)
अणु
	काष्ठा il3945_frame *frame;
	काष्ठा list_head *element;
	अगर (list_empty(&il->मुक्त_frames)) अणु
		frame = kzalloc(माप(*frame), GFP_KERNEL);
		अगर (!frame) अणु
			IL_ERR("Could not allocate frame!\n");
			वापस शून्य;
		पूर्ण

		il->frames_count++;
		वापस frame;
	पूर्ण

	element = il->मुक्त_frames.next;
	list_del(element);
	वापस list_entry(element, काष्ठा il3945_frame, list);
पूर्ण

अटल व्योम
il3945_मुक्त_frame(काष्ठा il_priv *il, काष्ठा il3945_frame *frame)
अणु
	स_रखो(frame, 0, माप(*frame));
	list_add(&frame->list, &il->मुक्त_frames);
पूर्ण

अचिन्हित पूर्णांक
il3945_fill_beacon_frame(काष्ठा il_priv *il, काष्ठा ieee80211_hdr *hdr,
			 पूर्णांक left)
अणु

	अगर (!il_is_associated(il) || !il->beacon_skb)
		वापस 0;

	अगर (il->beacon_skb->len > left)
		वापस 0;

	स_नकल(hdr, il->beacon_skb->data, il->beacon_skb->len);

	वापस il->beacon_skb->len;
पूर्ण

अटल पूर्णांक
il3945_send_beacon_cmd(काष्ठा il_priv *il)
अणु
	काष्ठा il3945_frame *frame;
	अचिन्हित पूर्णांक frame_size;
	पूर्णांक rc;
	u8 rate;

	frame = il3945_get_मुक्त_frame(il);

	अगर (!frame) अणु
		IL_ERR("Could not obtain free frame buffer for beacon "
		       "command.\n");
		वापस -ENOMEM;
	पूर्ण

	rate = il_get_lowest_plcp(il);

	frame_size = il3945_hw_get_beacon_cmd(il, frame, rate);

	rc = il_send_cmd_pdu(il, C_TX_BEACON, frame_size, &frame->u.cmd[0]);

	il3945_मुक्त_frame(il, frame);

	वापस rc;
पूर्ण

अटल व्योम
il3945_unset_hw_params(काष्ठा il_priv *il)
अणु
	अगर (il->_3945.shared_virt)
		dma_मुक्त_coherent(&il->pci_dev->dev,
				  माप(काष्ठा il3945_shared),
				  il->_3945.shared_virt, il->_3945.shared_phys);
पूर्ण

अटल व्योम
il3945_build_tx_cmd_hwcrypto(काष्ठा il_priv *il, काष्ठा ieee80211_tx_info *info,
			     काष्ठा il_device_cmd *cmd,
			     काष्ठा sk_buff *skb_frag, पूर्णांक sta_id)
अणु
	काष्ठा il3945_tx_cmd *tx_cmd = (काष्ठा il3945_tx_cmd *)cmd->cmd.payload;
	काष्ठा il_hw_key *keyinfo = &il->stations[sta_id].keyinfo;

	tx_cmd->sec_ctl = 0;

	चयन (keyinfo->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		tx_cmd->sec_ctl = TX_CMD_SEC_CCM;
		स_नकल(tx_cmd->key, keyinfo->key, keyinfo->keylen);
		D_TX("tx_cmd with AES hwcrypto\n");
		अवरोध;

	हाल WLAN_CIPHER_SUITE_TKIP:
		अवरोध;

	हाल WLAN_CIPHER_SUITE_WEP104:
		tx_cmd->sec_ctl |= TX_CMD_SEC_KEY128;
		fallthrough;
	हाल WLAN_CIPHER_SUITE_WEP40:
		tx_cmd->sec_ctl |=
		    TX_CMD_SEC_WEP | (info->control.hw_key->
				      hw_key_idx & TX_CMD_SEC_MSK) <<
		    TX_CMD_SEC_SHIFT;

		स_नकल(&tx_cmd->key[3], keyinfo->key, keyinfo->keylen);

		D_TX("Configuring packet for WEP encryption " "with key %d\n",
		     info->control.hw_key->hw_key_idx);
		अवरोध;

	शेष:
		IL_ERR("Unknown encode cipher %x\n", keyinfo->cipher);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * handle build C_TX command notअगरication.
 */
अटल व्योम
il3945_build_tx_cmd_basic(काष्ठा il_priv *il, काष्ठा il_device_cmd *cmd,
			  काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_hdr *hdr, u8 std_id)
अणु
	काष्ठा il3945_tx_cmd *tx_cmd = (काष्ठा il3945_tx_cmd *)cmd->cmd.payload;
	__le32 tx_flags = tx_cmd->tx_flags;
	__le16 fc = hdr->frame_control;

	tx_cmd->stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;
	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
		tx_flags |= TX_CMD_FLG_ACK_MSK;
		अगर (ieee80211_is_mgmt(fc))
			tx_flags |= TX_CMD_FLG_SEQ_CTL_MSK;
		अगर (ieee80211_is_probe_resp(fc) &&
		    !(le16_to_cpu(hdr->seq_ctrl) & 0xf))
			tx_flags |= TX_CMD_FLG_TSF_MSK;
	पूर्ण अन्यथा अणु
		tx_flags &= (~TX_CMD_FLG_ACK_MSK);
		tx_flags |= TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण

	tx_cmd->sta_id = std_id;
	अगर (ieee80211_has_morefrags(fc))
		tx_flags |= TX_CMD_FLG_MORE_FRAG_MSK;

	अगर (ieee80211_is_data_qos(fc)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tx_cmd->tid_tspec = qc[0] & 0xf;
		tx_flags &= ~TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण अन्यथा अणु
		tx_flags |= TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण

	il_tx_cmd_protection(il, info, fc, &tx_flags);

	tx_flags &= ~(TX_CMD_FLG_ANT_SEL_MSK);
	अगर (ieee80211_is_mgmt(fc)) अणु
		अगर (ieee80211_is_assoc_req(fc) || ieee80211_is_reassoc_req(fc))
			tx_cmd->समयout.pm_frame_समयout = cpu_to_le16(3);
		अन्यथा
			tx_cmd->समयout.pm_frame_समयout = cpu_to_le16(2);
	पूर्ण अन्यथा अणु
		tx_cmd->समयout.pm_frame_समयout = 0;
	पूर्ण

	tx_cmd->driver_txop = 0;
	tx_cmd->tx_flags = tx_flags;
	tx_cmd->next_frame_len = 0;
पूर्ण

/*
 * start C_TX command process
 */
अटल पूर्णांक
il3945_tx_skb(काष्ठा il_priv *il,
	      काष्ठा ieee80211_sta *sta,
	      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा il3945_tx_cmd *tx_cmd;
	काष्ठा il_tx_queue *txq = शून्य;
	काष्ठा il_queue *q = शून्य;
	काष्ठा il_device_cmd *out_cmd;
	काष्ठा il_cmd_meta *out_meta;
	dma_addr_t phys_addr;
	dma_addr_t txcmd_phys;
	पूर्णांक txq_id = skb_get_queue_mapping(skb);
	u16 len, idx, hdr_len;
	u16 firstlen, secondlen;
	u8 sta_id;
	u8 tid = 0;
	__le16 fc;
	u8 रुको_ग_लिखो_ptr = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&il->lock, flags);
	अगर (il_is_rfसमाप्त(il)) अणु
		D_DROP("Dropping - RF KILL\n");
		जाओ drop_unlock;
	पूर्ण

	अगर ((ieee80211_get_tx_rate(il->hw, info)->hw_value & 0xFF) ==
	    IL_INVALID_RATE) अणु
		IL_ERR("ERROR: No TX rate available.\n");
		जाओ drop_unlock;
	पूर्ण

	fc = hdr->frame_control;

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (ieee80211_is_auth(fc))
		D_TX("Sending AUTH frame\n");
	अन्यथा अगर (ieee80211_is_assoc_req(fc))
		D_TX("Sending ASSOC frame\n");
	अन्यथा अगर (ieee80211_is_reassoc_req(fc))
		D_TX("Sending REASSOC frame\n");
#पूर्ण_अगर

	spin_unlock_irqrestore(&il->lock, flags);

	hdr_len = ieee80211_hdrlen(fc);

	/* Find idx पूर्णांकo station table क्रम destination station */
	sta_id = il_sta_id_or_broadcast(il, sta);
	अगर (sta_id == IL_INVALID_STATION) अणु
		D_DROP("Dropping - INVALID STATION: %pM\n", hdr->addr1);
		जाओ drop;
	पूर्ण

	D_RATE("station Id %d\n", sta_id);

	अगर (ieee80211_is_data_qos(fc)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
		अगर (unlikely(tid >= MAX_TID_COUNT))
			जाओ drop;
	पूर्ण

	/* Descriptor क्रम chosen Tx queue */
	txq = &il->txq[txq_id];
	q = &txq->q;

	अगर ((il_queue_space(q) < q->high_mark))
		जाओ drop;

	spin_lock_irqsave(&il->lock, flags);

	idx = il_get_cmd_idx(q, q->ग_लिखो_ptr, 0);

	txq->skbs[q->ग_लिखो_ptr] = skb;

	/* Init first empty entry in queue's array of Tx/cmd buffers */
	out_cmd = txq->cmd[idx];
	out_meta = &txq->meta[idx];
	tx_cmd = (काष्ठा il3945_tx_cmd *)out_cmd->cmd.payload;
	स_रखो(&out_cmd->hdr, 0, माप(out_cmd->hdr));
	स_रखो(tx_cmd, 0, माप(*tx_cmd));

	/*
	 * Set up the Tx-command (not MAC!) header.
	 * Store the chosen Tx queue and TFD idx within the sequence field;
	 * after Tx, uCode's Tx response will वापस this value so driver can
	 * locate the frame within the tx queue and करो post-tx processing.
	 */
	out_cmd->hdr.cmd = C_TX;
	out_cmd->hdr.sequence =
	    cpu_to_le16((u16)
			(QUEUE_TO_SEQ(txq_id) | IDX_TO_SEQ(q->ग_लिखो_ptr)));

	/* Copy MAC header from skb पूर्णांकo command buffer */
	स_नकल(tx_cmd->hdr, hdr, hdr_len);

	अगर (info->control.hw_key)
		il3945_build_tx_cmd_hwcrypto(il, info, out_cmd, skb, sta_id);

	/* TODO need this क्रम burst mode later on */
	il3945_build_tx_cmd_basic(il, out_cmd, info, hdr, sta_id);

	il3945_hw_build_tx_cmd_rate(il, out_cmd, info, hdr, sta_id);

	/* Total # bytes to be transmitted */
	tx_cmd->len = cpu_to_le16((u16) skb->len);

	tx_cmd->tx_flags &= ~TX_CMD_FLG_ANT_A_MSK;
	tx_cmd->tx_flags &= ~TX_CMD_FLG_ANT_B_MSK;

	/*
	 * Use the first empty entry in this queue's command buffer array
	 * to contain the Tx command and MAC header concatenated together
	 * (payload data will be in another buffer).
	 * Size of this varies, due to varying MAC header length.
	 * If end is not dword aligned, we'll have 2 extra bytes at the end
	 * of the MAC header (device पढ़ोs on dword boundaries).
	 * We'll tell device about this padding later.
	 */
	len =
	    माप(काष्ठा il3945_tx_cmd) + माप(काष्ठा il_cmd_header) +
	    hdr_len;
	firstlen = (len + 3) & ~3;

	/* Physical address of this Tx command's header (not MAC header!),
	 * within command buffer array. */
	txcmd_phys =
	    pci_map_single(il->pci_dev, &out_cmd->hdr, firstlen,
			   PCI_DMA_TODEVICE);
	अगर (unlikely(pci_dma_mapping_error(il->pci_dev, txcmd_phys)))
		जाओ drop_unlock;

	/* Set up TFD's 2nd entry to poपूर्णांक directly to reमुख्यder of skb,
	 * अगर any (802.11 null frames have no payload). */
	secondlen = skb->len - hdr_len;
	अगर (secondlen > 0) अणु
		phys_addr =
		    pci_map_single(il->pci_dev, skb->data + hdr_len, secondlen,
				   PCI_DMA_TODEVICE);
		अगर (unlikely(pci_dma_mapping_error(il->pci_dev, phys_addr)))
			जाओ drop_unlock;
	पूर्ण

	/* Add buffer containing Tx command and MAC(!) header to TFD's
	 * first entry */
	il->ops->txq_attach_buf_to_tfd(il, txq, txcmd_phys, firstlen, 1, 0);
	dma_unmap_addr_set(out_meta, mapping, txcmd_phys);
	dma_unmap_len_set(out_meta, len, firstlen);
	अगर (secondlen > 0)
		il->ops->txq_attach_buf_to_tfd(il, txq, phys_addr, secondlen, 0,
					       U32_PAD(secondlen));

	अगर (!ieee80211_has_morefrags(hdr->frame_control)) अणु
		txq->need_update = 1;
	पूर्ण अन्यथा अणु
		रुको_ग_लिखो_ptr = 1;
		txq->need_update = 0;
	पूर्ण

	il_update_stats(il, true, fc, skb->len);

	D_TX("sequence nr = 0X%x\n", le16_to_cpu(out_cmd->hdr.sequence));
	D_TX("tx_flags = 0X%x\n", le32_to_cpu(tx_cmd->tx_flags));
	il_prपूर्णांक_hex_dump(il, IL_DL_TX, tx_cmd, माप(*tx_cmd));
	il_prपूर्णांक_hex_dump(il, IL_DL_TX, (u8 *) tx_cmd->hdr,
			  ieee80211_hdrlen(fc));

	/* Tell device the ग_लिखो idx *just past* this latest filled TFD */
	q->ग_लिखो_ptr = il_queue_inc_wrap(q->ग_लिखो_ptr, q->n_bd);
	il_txq_update_ग_लिखो_ptr(il, txq);
	spin_unlock_irqrestore(&il->lock, flags);

	अगर (il_queue_space(q) < q->high_mark && il->mac80211_रेजिस्टरed) अणु
		अगर (रुको_ग_लिखो_ptr) अणु
			spin_lock_irqsave(&il->lock, flags);
			txq->need_update = 1;
			il_txq_update_ग_लिखो_ptr(il, txq);
			spin_unlock_irqrestore(&il->lock, flags);
		पूर्ण

		il_stop_queue(il, txq);
	पूर्ण

	वापस 0;

drop_unlock:
	spin_unlock_irqrestore(&il->lock, flags);
drop:
	वापस -1;
पूर्ण

अटल पूर्णांक
il3945_get_measurement(काष्ठा il_priv *il,
		       काष्ठा ieee80211_measurement_params *params, u8 type)
अणु
	काष्ठा il_spectrum_cmd spectrum;
	काष्ठा il_rx_pkt *pkt;
	काष्ठा il_host_cmd cmd = अणु
		.id = C_SPECTRUM_MEASUREMENT,
		.data = (व्योम *)&spectrum,
		.flags = CMD_WANT_SKB,
	पूर्ण;
	u32 add_समय = le64_to_cpu(params->start_समय);
	पूर्णांक rc;
	पूर्णांक spectrum_resp_status;
	पूर्णांक duration = le16_to_cpu(params->duration);

	अगर (il_is_associated(il))
		add_समय =
		    il_usecs_to_beacons(il,
					le64_to_cpu(params->start_समय) -
					il->_3945.last_tsf,
					le16_to_cpu(il->timing.beacon_पूर्णांकerval));

	स_रखो(&spectrum, 0, माप(spectrum));

	spectrum.channel_count = cpu_to_le16(1);
	spectrum.flags =
	    RXON_FLG_TSF2HOST_MSK | RXON_FLG_ANT_A_MSK | RXON_FLG_DIS_DIV_MSK;
	spectrum.filter_flags = MEASUREMENT_FILTER_FLAG;
	cmd.len = माप(spectrum);
	spectrum.len = cpu_to_le16(cmd.len - माप(spectrum.len));

	अगर (il_is_associated(il))
		spectrum.start_समय =
		    il_add_beacon_समय(il, il->_3945.last_beacon_समय, add_समय,
				       le16_to_cpu(il->timing.beacon_पूर्णांकerval));
	अन्यथा
		spectrum.start_समय = 0;

	spectrum.channels[0].duration = cpu_to_le32(duration * TIME_UNIT);
	spectrum.channels[0].channel = params->channel;
	spectrum.channels[0].type = type;
	अगर (il->active.flags & RXON_FLG_BAND_24G_MSK)
		spectrum.flags |=
		    RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK |
		    RXON_FLG_TGG_PROTECT_MSK;

	rc = il_send_cmd_sync(il, &cmd);
	अगर (rc)
		वापस rc;

	pkt = (काष्ठा il_rx_pkt *)cmd.reply_page;
	अगर (pkt->hdr.flags & IL_CMD_FAILED_MSK) अणु
		IL_ERR("Bad return from N_RX_ON_ASSOC command\n");
		rc = -EIO;
	पूर्ण

	spectrum_resp_status = le16_to_cpu(pkt->u.spectrum.status);
	चयन (spectrum_resp_status) अणु
	हाल 0:		/* Command will be handled */
		अगर (pkt->u.spectrum.id != 0xff) अणु
			D_INFO("Replaced existing measurement: %d\n",
			       pkt->u.spectrum.id);
			il->measurement_status &= ~MEASUREMENT_READY;
		पूर्ण
		il->measurement_status |= MEASUREMENT_ACTIVE;
		rc = 0;
		अवरोध;

	हाल 1:		/* Command will not be handled */
		rc = -EAGAIN;
		अवरोध;
	पूर्ण

	il_मुक्त_pages(il, cmd.reply_page);

	वापस rc;
पूर्ण

अटल व्योम
il3945_hdl_alive(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_alive_resp *palive;
	काष्ठा delayed_work *pwork;

	palive = &pkt->u.alive_frame;

	D_INFO("Alive ucode status 0x%08X revision " "0x%01X 0x%01X\n",
	       palive->is_valid, palive->ver_type, palive->ver_subtype);

	अगर (palive->ver_subtype == INITIALIZE_SUBTYPE) अणु
		D_INFO("Initialization Alive received.\n");
		स_नकल(&il->card_alive_init, &pkt->u.alive_frame,
		       माप(काष्ठा il_alive_resp));
		pwork = &il->init_alive_start;
	पूर्ण अन्यथा अणु
		D_INFO("Runtime Alive received.\n");
		स_नकल(&il->card_alive, &pkt->u.alive_frame,
		       माप(काष्ठा il_alive_resp));
		pwork = &il->alive_start;
		il3945_disable_events(il);
	पूर्ण

	/* We delay the ALIVE response by 5ms to
	 * give the HW RF Kill समय to activate... */
	अगर (palive->is_valid == UCODE_VALID_OK)
		queue_delayed_work(il->workqueue, pwork, msecs_to_jअगरfies(5));
	अन्यथा
		IL_WARN("uCode did not respond OK.\n");
पूर्ण

अटल व्योम
il3945_hdl_add_sta(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);

	D_RX("Received C_ADD_STA: 0x%02X\n", pkt->u.status);
पूर्ण

अटल व्योम
il3945_hdl_beacon(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il3945_beacon_notअगर *beacon = &(pkt->u.beacon_status);
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	u8 rate = beacon->beacon_notअगरy_hdr.rate;

	D_RX("beacon status %x retries %d iss %d " "tsf %d %d rate %d\n",
	     le32_to_cpu(beacon->beacon_notअगरy_hdr.status) & TX_STATUS_MSK,
	     beacon->beacon_notअगरy_hdr.failure_frame,
	     le32_to_cpu(beacon->ibss_mgr_status),
	     le32_to_cpu(beacon->high_tsf), le32_to_cpu(beacon->low_tsf), rate);
#पूर्ण_अगर

	il->ibss_manager = le32_to_cpu(beacon->ibss_mgr_status);

पूर्ण

/* Handle notअगरication from uCode that card's घातer state is changing
 * due to software, hardware, or critical temperature RFKILL */
अटल व्योम
il3945_hdl_card_state(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	u32 flags = le32_to_cpu(pkt->u.card_state_notअगर.flags);
	अचिन्हित दीर्घ status = il->status;

	IL_WARN("Card state received: HW:%s SW:%s\n",
		(flags & HW_CARD_DISABLED) ? "Kill" : "On",
		(flags & SW_CARD_DISABLED) ? "Kill" : "On");

	_il_wr(il, CSR_UCODE_DRV_GP1_SET, CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

	अगर (flags & HW_CARD_DISABLED)
		set_bit(S_RFKILL, &il->status);
	अन्यथा
		clear_bit(S_RFKILL, &il->status);

	il_scan_cancel(il);

	अगर ((test_bit(S_RFKILL, &status) !=
	     test_bit(S_RFKILL, &il->status)))
		wiphy_rfसमाप्त_set_hw_state(il->hw->wiphy,
					  test_bit(S_RFKILL, &il->status));
	अन्यथा
		wake_up(&il->रुको_command_queue);
पूर्ण

/*
 * il3945_setup_handlers - Initialize Rx handler callbacks
 *
 * Setup the RX handlers क्रम each of the reply types sent from the uCode
 * to the host.
 *
 * This function chains पूर्णांकo the hardware specअगरic files क्रम them to setup
 * any hardware specअगरic handlers as well.
 */
अटल व्योम
il3945_setup_handlers(काष्ठा il_priv *il)
अणु
	il->handlers[N_ALIVE] = il3945_hdl_alive;
	il->handlers[C_ADD_STA] = il3945_hdl_add_sta;
	il->handlers[N_ERROR] = il_hdl_error;
	il->handlers[N_CHANNEL_SWITCH] = il_hdl_csa;
	il->handlers[N_SPECTRUM_MEASUREMENT] = il_hdl_spectrum_measurement;
	il->handlers[N_PM_SLEEP] = il_hdl_pm_sleep;
	il->handlers[N_PM_DEBUG_STATS] = il_hdl_pm_debug_stats;
	il->handlers[N_BEACON] = il3945_hdl_beacon;

	/*
	 * The same handler is used क्रम both the REPLY to a discrete
	 * stats request from the host as well as क्रम the periodic
	 * stats notअगरications (after received beacons) from the uCode.
	 */
	il->handlers[C_STATS] = il3945_hdl_c_stats;
	il->handlers[N_STATS] = il3945_hdl_stats;

	il_setup_rx_scan_handlers(il);
	il->handlers[N_CARD_STATE] = il3945_hdl_card_state;

	/* Set up hardware specअगरic Rx handlers */
	il3945_hw_handler_setup(il);
पूर्ण

/************************** RX-FUNCTIONS ****************************/
/*
 * Rx theory of operation
 *
 * The host allocates 32 DMA target addresses and passes the host address
 * to the firmware at रेजिस्टर IL_RFDS_TBL_LOWER + N * RFD_SIZE where N is
 * 0 to 31
 *
 * Rx Queue Indexes
 * The host/firmware share two idx रेजिस्टरs क्रम managing the Rx buffers.
 *
 * The READ idx maps to the first position that the firmware may be writing
 * to -- the driver can पढ़ो up to (but not including) this position and get
 * good data.
 * The READ idx is managed by the firmware once the card is enabled.
 *
 * The WRITE idx maps to the last position the driver has पढ़ो from -- the
 * position preceding WRITE is the last slot the firmware can place a packet.
 *
 * The queue is empty (no good data) अगर WRITE = READ - 1, and is full अगर
 * WRITE = READ.
 *
 * During initialization, the host sets up the READ queue position to the first
 * IDX position, and WRITE to the last (READ - 1 wrapped)
 *
 * When the firmware places a packet in a buffer, it will advance the READ idx
 * and fire the RX पूर्णांकerrupt.  The driver can then query the READ idx and
 * process as many packets as possible, moving the WRITE idx क्रमward as it
 * resets the Rx queue buffers with new memory.
 *
 * The management in the driver is as follows:
 * + A list of pre-allocated SKBs is stored in iwl->rxq->rx_मुक्त.  When
 *   iwl->rxq->मुक्त_count drops to or below RX_LOW_WATERMARK, work is scheduled
 *   to replenish the iwl->rxq->rx_मुक्त.
 * + In il3945_rx_replenish (scheduled) अगर 'processed' != 'read' then the
 *   iwl->rxq is replenished and the READ IDX is updated (updating the
 *   'processed' and 'read' driver idxes as well)
 * + A received packet is processed and handed to the kernel network stack,
 *   detached from the iwl->rxq.  The driver 'processed' idx is updated.
 * + The Host/Firmware iwl->rxq is replenished at tasklet समय from the rx_मुक्त
 *   list. If there are no allocated buffers in iwl->rxq->rx_मुक्त, the READ
 *   IDX is not incremented and iwl->status(RX_STALLED) is set.  If there
 *   were enough मुक्त buffers and RX_STALLED is set it is cleared.
 *
 *
 * Driver sequence:
 *
 * il3945_rx_replenish()     Replenishes rx_मुक्त list from rx_used, and calls
 *                            il3945_rx_queue_restock
 * il3945_rx_queue_restock() Moves available buffers from rx_मुक्त पूर्णांकo Rx
 *                            queue, updates firmware poपूर्णांकers, and updates
 *                            the WRITE idx.  If insufficient rx_मुक्त buffers
 *                            are available, schedules il3945_rx_replenish
 *
 * -- enable पूर्णांकerrupts --
 * ISR - il3945_rx()         Detach il_rx_bufs from pool up to the
 *                            READ IDX, detaching the SKB from the pool.
 *                            Moves the packet buffer from queue to rx_used.
 *                            Calls il3945_rx_queue_restock to refill any empty
 *                            slots.
 * ...
 *
 */

/*
 * il3945_dma_addr2rbd_ptr - convert a DMA address to a uCode पढ़ो buffer ptr
 */
अटल अंतरभूत __le32
il3945_dma_addr2rbd_ptr(काष्ठा il_priv *il, dma_addr_t dma_addr)
अणु
	वापस cpu_to_le32((u32) dma_addr);
पूर्ण

/*
 * il3945_rx_queue_restock - refill RX queue from pre-allocated pool
 *
 * If there are slots in the RX queue that need to be restocked,
 * and we have मुक्त pre-allocated buffers, fill the ranks as much
 * as we can, pulling from rx_मुक्त.
 *
 * This moves the 'write' idx forward to catch up with 'processed', and
 * also updates the memory address in the firmware to reference the new
 * target buffer.
 */
अटल व्योम
il3945_rx_queue_restock(काष्ठा il_priv *il)
अणु
	काष्ठा il_rx_queue *rxq = &il->rxq;
	काष्ठा list_head *element;
	काष्ठा il_rx_buf *rxb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rxq->lock, flags);
	जबतक (il_rx_queue_space(rxq) > 0 && rxq->मुक्त_count) अणु
		/* Get next मुक्त Rx buffer, हटाओ from मुक्त list */
		element = rxq->rx_मुक्त.next;
		rxb = list_entry(element, काष्ठा il_rx_buf, list);
		list_del(element);

		/* Poपूर्णांक to Rx buffer via next RBD in circular buffer */
		rxq->bd[rxq->ग_लिखो] =
		    il3945_dma_addr2rbd_ptr(il, rxb->page_dma);
		rxq->queue[rxq->ग_लिखो] = rxb;
		rxq->ग_लिखो = (rxq->ग_लिखो + 1) & RX_QUEUE_MASK;
		rxq->मुक्त_count--;
	पूर्ण
	spin_unlock_irqrestore(&rxq->lock, flags);
	/* If the pre-allocated buffer pool is dropping low, schedule to
	 * refill it */
	अगर (rxq->मुक्त_count <= RX_LOW_WATERMARK)
		queue_work(il->workqueue, &il->rx_replenish);

	/* If we've added more space क्रम the firmware to place data, tell it.
	 * Increment device's ग_लिखो poपूर्णांकer in multiples of 8. */
	अगर (rxq->ग_लिखो_actual != (rxq->ग_लिखो & ~0x7) ||
	    असल(rxq->ग_लिखो - rxq->पढ़ो) > 7) अणु
		spin_lock_irqsave(&rxq->lock, flags);
		rxq->need_update = 1;
		spin_unlock_irqrestore(&rxq->lock, flags);
		il_rx_queue_update_ग_लिखो_ptr(il, rxq);
	पूर्ण
पूर्ण

/*
 * il3945_rx_replenish - Move all used packet from rx_used to rx_मुक्त
 *
 * When moving to rx_मुक्त an SKB is allocated क्रम the slot.
 *
 * Also restock the Rx queue via il3945_rx_queue_restock.
 * This is called as a scheduled work item (except क्रम during initialization)
 */
अटल व्योम
il3945_rx_allocate(काष्ठा il_priv *il, gfp_t priority)
अणु
	काष्ठा il_rx_queue *rxq = &il->rxq;
	काष्ठा list_head *element;
	काष्ठा il_rx_buf *rxb;
	काष्ठा page *page;
	dma_addr_t page_dma;
	अचिन्हित दीर्घ flags;
	gfp_t gfp_mask = priority;

	जबतक (1) अणु
		spin_lock_irqsave(&rxq->lock, flags);
		अगर (list_empty(&rxq->rx_used)) अणु
			spin_unlock_irqrestore(&rxq->lock, flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&rxq->lock, flags);

		अगर (rxq->मुक्त_count > RX_LOW_WATERMARK)
			gfp_mask |= __GFP_NOWARN;

		अगर (il->hw_params.rx_page_order > 0)
			gfp_mask |= __GFP_COMP;

		/* Alloc a new receive buffer */
		page = alloc_pages(gfp_mask, il->hw_params.rx_page_order);
		अगर (!page) अणु
			अगर (net_ratelimit())
				D_INFO("Failed to allocate SKB buffer.\n");
			अगर (rxq->मुक्त_count <= RX_LOW_WATERMARK &&
			    net_ratelimit())
				IL_ERR("Failed to allocate SKB buffer with %0x."
				       "Only %u free buffers remaining.\n",
				       priority, rxq->मुक्त_count);
			/* We करोn't reschedule replenish work here -- we will
			 * call the restock method and अगर it still needs
			 * more buffers it will schedule replenish */
			अवरोध;
		पूर्ण

		/* Get physical address of RB/SKB */
		page_dma =
		    pci_map_page(il->pci_dev, page, 0,
				 PAGE_SIZE << il->hw_params.rx_page_order,
				 PCI_DMA_FROMDEVICE);

		अगर (unlikely(pci_dma_mapping_error(il->pci_dev, page_dma))) अणु
			__मुक्त_pages(page, il->hw_params.rx_page_order);
			अवरोध;
		पूर्ण

		spin_lock_irqsave(&rxq->lock, flags);

		अगर (list_empty(&rxq->rx_used)) अणु
			spin_unlock_irqrestore(&rxq->lock, flags);
			pci_unmap_page(il->pci_dev, page_dma,
				       PAGE_SIZE << il->hw_params.rx_page_order,
				       PCI_DMA_FROMDEVICE);
			__मुक्त_pages(page, il->hw_params.rx_page_order);
			वापस;
		पूर्ण

		element = rxq->rx_used.next;
		rxb = list_entry(element, काष्ठा il_rx_buf, list);
		list_del(element);

		rxb->page = page;
		rxb->page_dma = page_dma;
		list_add_tail(&rxb->list, &rxq->rx_मुक्त);
		rxq->मुक्त_count++;
		il->alloc_rxb_page++;

		spin_unlock_irqrestore(&rxq->lock, flags);
	पूर्ण
पूर्ण

व्योम
il3945_rx_queue_reset(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	spin_lock_irqsave(&rxq->lock, flags);
	INIT_LIST_HEAD(&rxq->rx_मुक्त);
	INIT_LIST_HEAD(&rxq->rx_used);
	/* Fill the rx_used queue with _all_ of the Rx buffers */
	क्रम (i = 0; i < RX_FREE_BUFFERS + RX_QUEUE_SIZE; i++) अणु
		/* In the reset function, these buffers may have been allocated
		 * to an SKB, so we need to unmap and मुक्त potential storage */
		अगर (rxq->pool[i].page != शून्य) अणु
			pci_unmap_page(il->pci_dev, rxq->pool[i].page_dma,
				       PAGE_SIZE << il->hw_params.rx_page_order,
				       PCI_DMA_FROMDEVICE);
			__il_मुक्त_pages(il, rxq->pool[i].page);
			rxq->pool[i].page = शून्य;
		पूर्ण
		list_add_tail(&rxq->pool[i].list, &rxq->rx_used);
	पूर्ण

	/* Set us so that we have processed and used all buffers, but have
	 * not restocked the Rx queue with fresh buffers */
	rxq->पढ़ो = rxq->ग_लिखो = 0;
	rxq->ग_लिखो_actual = 0;
	rxq->मुक्त_count = 0;
	spin_unlock_irqrestore(&rxq->lock, flags);
पूर्ण

व्योम
il3945_rx_replenish(व्योम *data)
अणु
	काष्ठा il_priv *il = data;
	अचिन्हित दीर्घ flags;

	il3945_rx_allocate(il, GFP_KERNEL);

	spin_lock_irqsave(&il->lock, flags);
	il3945_rx_queue_restock(il);
	spin_unlock_irqrestore(&il->lock, flags);
पूर्ण

अटल व्योम
il3945_rx_replenish_now(काष्ठा il_priv *il)
अणु
	il3945_rx_allocate(il, GFP_ATOMIC);

	il3945_rx_queue_restock(il);
पूर्ण

/* Assumes that the skb field of the buffers in 'pool' is kept accurate.
 * If an SKB has been detached, the POOL needs to have its SKB set to शून्य
 * This मुक्त routine walks the list of POOL entries and अगर SKB is set to
 * non शून्य it is unmapped and मुक्तd
 */
अटल व्योम
il3945_rx_queue_मुक्त(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < RX_QUEUE_SIZE + RX_FREE_BUFFERS; i++) अणु
		अगर (rxq->pool[i].page != शून्य) अणु
			pci_unmap_page(il->pci_dev, rxq->pool[i].page_dma,
				       PAGE_SIZE << il->hw_params.rx_page_order,
				       PCI_DMA_FROMDEVICE);
			__il_मुक्त_pages(il, rxq->pool[i].page);
			rxq->pool[i].page = शून्य;
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(&il->pci_dev->dev, 4 * RX_QUEUE_SIZE, rxq->bd,
			  rxq->bd_dma);
	dma_मुक्त_coherent(&il->pci_dev->dev, माप(काष्ठा il_rb_status),
			  rxq->rb_stts, rxq->rb_stts_dma);
	rxq->bd = शून्य;
	rxq->rb_stts = शून्य;
पूर्ण

/* Convert linear संकेत-to-noise ratio पूर्णांकo dB */
अटल u8 ratio2dB[100] = अणु
/*	 0   1   2   3   4   5   6   7   8   9 */
	0, 0, 6, 10, 12, 14, 16, 17, 18, 19,	/* 00 - 09 */
	20, 21, 22, 22, 23, 23, 24, 25, 26, 26,	/* 10 - 19 */
	26, 26, 26, 27, 27, 28, 28, 28, 29, 29,	/* 20 - 29 */
	29, 30, 30, 30, 31, 31, 31, 31, 32, 32,	/* 30 - 39 */
	32, 32, 32, 33, 33, 33, 33, 33, 34, 34,	/* 40 - 49 */
	34, 34, 34, 34, 35, 35, 35, 35, 35, 35,	/* 50 - 59 */
	36, 36, 36, 36, 36, 36, 36, 37, 37, 37,	/* 60 - 69 */
	37, 37, 37, 37, 37, 38, 38, 38, 38, 38,	/* 70 - 79 */
	38, 38, 38, 38, 38, 39, 39, 39, 39, 39,	/* 80 - 89 */
	39, 39, 39, 39, 39, 40, 40, 40, 40, 40	/* 90 - 99 */
पूर्ण;

/* Calculates a relative dB value from a ratio of linear
 *   (i.e. not dB) संकेत levels.
 * Conversion assumes that levels are voltages (20*log), not घातers (10*log). */
पूर्णांक
il3945_calc_db_from_ratio(पूर्णांक sig_ratio)
अणु
	/* 1000:1 or higher just report as 60 dB */
	अगर (sig_ratio >= 1000)
		वापस 60;

	/* 100:1 or higher, भागide by 10 and use table,
	 *   add 20 dB to make up क्रम भागide by 10 */
	अगर (sig_ratio >= 100)
		वापस 20 + (पूर्णांक)ratio2dB[sig_ratio / 10];

	/* We shouldn't see this */
	अगर (sig_ratio < 1)
		वापस 0;

	/* Use table क्रम ratios 1:1 - 99:1 */
	वापस (पूर्णांक)ratio2dB[sig_ratio];
पूर्ण

/*
 * il3945_rx_handle - Main entry function क्रम receiving responses from uCode
 *
 * Uses the il->handlers callback function array to invoke
 * the appropriate handlers, including command responses,
 * frame-received notअगरications, and other notअगरications.
 */
अटल व्योम
il3945_rx_handle(काष्ठा il_priv *il)
अणु
	काष्ठा il_rx_buf *rxb;
	काष्ठा il_rx_pkt *pkt;
	काष्ठा il_rx_queue *rxq = &il->rxq;
	u32 r, i;
	पूर्णांक reclaim;
	अचिन्हित दीर्घ flags;
	u8 fill_rx = 0;
	u32 count = 8;
	पूर्णांक total_empty = 0;

	/* uCode's पढ़ो idx (stored in shared DRAM) indicates the last Rx
	 * buffer that the driver may process (last buffer filled by ucode). */
	r = le16_to_cpu(rxq->rb_stts->बंदd_rb_num) & 0x0FFF;
	i = rxq->पढ़ो;

	/* calculate total frames need to be restock after handling RX */
	total_empty = r - rxq->ग_लिखो_actual;
	अगर (total_empty < 0)
		total_empty += RX_QUEUE_SIZE;

	अगर (total_empty > (RX_QUEUE_SIZE / 2))
		fill_rx = 1;
	/* Rx पूर्णांकerrupt, but nothing sent from uCode */
	अगर (i == r)
		D_RX("r = %d, i = %d\n", r, i);

	जबतक (i != r) अणु
		पूर्णांक len;

		rxb = rxq->queue[i];

		/* If an RXB करोesn't have a Rx queue slot associated with it,
		 * then a bug has been पूर्णांकroduced in the queue refilling
		 * routines -- catch it here */
		BUG_ON(rxb == शून्य);

		rxq->queue[i] = शून्य;

		pci_unmap_page(il->pci_dev, rxb->page_dma,
			       PAGE_SIZE << il->hw_params.rx_page_order,
			       PCI_DMA_FROMDEVICE);
		pkt = rxb_addr(rxb);

		len = le32_to_cpu(pkt->len_n_flags) & IL_RX_FRAME_SIZE_MSK;
		len += माप(u32);	/* account क्रम status word */

		reclaim = il_need_reclaim(il, pkt);

		/* Based on type of command response or notअगरication,
		 *   handle those that need handling via function in
		 *   handlers table.  See il3945_setup_handlers() */
		अगर (il->handlers[pkt->hdr.cmd]) अणु
			D_RX("r = %d, i = %d, %s, 0x%02x\n", r, i,
			     il_get_cmd_string(pkt->hdr.cmd), pkt->hdr.cmd);
			il->isr_stats.handlers[pkt->hdr.cmd]++;
			il->handlers[pkt->hdr.cmd] (il, rxb);
		पूर्ण अन्यथा अणु
			/* No handling needed */
			D_RX("r %d i %d No handler needed for %s, 0x%02x\n", r,
			     i, il_get_cmd_string(pkt->hdr.cmd), pkt->hdr.cmd);
		पूर्ण

		/*
		 * XXX: After here, we should always check rxb->page
		 * against शून्य beक्रमe touching it or its भव
		 * memory (pkt). Because some handler might have
		 * alपढ़ोy taken or मुक्तd the pages.
		 */

		अगर (reclaim) अणु
			/* Invoke any callbacks, transfer the buffer to caller,
			 * and fire off the (possibly) blocking il_send_cmd()
			 * as we reclaim the driver command queue */
			अगर (rxb->page)
				il_tx_cmd_complete(il, rxb);
			अन्यथा
				IL_WARN("Claim null rxb?\n");
		पूर्ण

		/* Reuse the page अगर possible. For notअगरication packets and
		 * SKBs that fail to Rx correctly, add them back पूर्णांकo the
		 * rx_मुक्त list क्रम reuse later. */
		spin_lock_irqsave(&rxq->lock, flags);
		अगर (rxb->page != शून्य) अणु
			rxb->page_dma =
			    pci_map_page(il->pci_dev, rxb->page, 0,
					 PAGE_SIZE << il->hw_params.
					 rx_page_order, PCI_DMA_FROMDEVICE);
			अगर (unlikely(pci_dma_mapping_error(il->pci_dev,
							   rxb->page_dma))) अणु
				__il_मुक्त_pages(il, rxb->page);
				rxb->page = शून्य;
				list_add_tail(&rxb->list, &rxq->rx_used);
			पूर्ण अन्यथा अणु
				list_add_tail(&rxb->list, &rxq->rx_मुक्त);
				rxq->मुक्त_count++;
			पूर्ण
		पूर्ण अन्यथा
			list_add_tail(&rxb->list, &rxq->rx_used);

		spin_unlock_irqrestore(&rxq->lock, flags);

		i = (i + 1) & RX_QUEUE_MASK;
		/* If there are a lot of unused frames,
		 * restock the Rx queue so ucode won't निश्चित. */
		अगर (fill_rx) अणु
			count++;
			अगर (count >= 8) अणु
				rxq->पढ़ो = i;
				il3945_rx_replenish_now(il);
				count = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Backtrack one entry */
	rxq->पढ़ो = i;
	अगर (fill_rx)
		il3945_rx_replenish_now(il);
	अन्यथा
		il3945_rx_queue_restock(il);
पूर्ण

/* call this function to flush any scheduled tasklet */
अटल अंतरभूत व्योम
il3945_synchronize_irq(काष्ठा il_priv *il)
अणु
	/* रुको to make sure we flush pending tasklet */
	synchronize_irq(il->pci_dev->irq);
	tasklet_समाप्त(&il->irq_tasklet);
पूर्ण

अटल स्थिर अक्षर *
il3945_desc_lookup(पूर्णांक i)
अणु
	चयन (i) अणु
	हाल 1:
		वापस "FAIL";
	हाल 2:
		वापस "BAD_PARAM";
	हाल 3:
		वापस "BAD_CHECKSUM";
	हाल 4:
		वापस "NMI_INTERRUPT";
	हाल 5:
		वापस "SYSASSERT";
	हाल 6:
		वापस "FATAL_ERROR";
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

#घोषणा ERROR_START_OFFSET  (1 * माप(u32))
#घोषणा ERROR_ELEM_SIZE     (7 * माप(u32))

व्योम
il3945_dump_nic_error_log(काष्ठा il_priv *il)
अणु
	u32 i;
	u32 desc, समय, count, base, data1;
	u32 blink1, blink2, ilink1, ilink2;

	base = le32_to_cpu(il->card_alive.error_event_table_ptr);

	अगर (!il3945_hw_valid_rtc_data_addr(base)) अणु
		IL_ERR("Not valid error log pointer 0x%08X\n", base);
		वापस;
	पूर्ण

	count = il_पढ़ो_targ_mem(il, base);

	अगर (ERROR_START_OFFSET <= count * ERROR_ELEM_SIZE) अणु
		IL_ERR("Start IWL Error Log Dump:\n");
		IL_ERR("Status: 0x%08lX, count: %d\n", il->status, count);
	पूर्ण

	IL_ERR("Desc       Time       asrtPC  blink2 "
	       "ilink1  nmiPC   Line\n");
	क्रम (i = ERROR_START_OFFSET;
	     i < (count * ERROR_ELEM_SIZE) + ERROR_START_OFFSET;
	     i += ERROR_ELEM_SIZE) अणु
		desc = il_पढ़ो_targ_mem(il, base + i);
		समय = il_पढ़ो_targ_mem(il, base + i + 1 * माप(u32));
		blink1 = il_पढ़ो_targ_mem(il, base + i + 2 * माप(u32));
		blink2 = il_पढ़ो_targ_mem(il, base + i + 3 * माप(u32));
		ilink1 = il_पढ़ो_targ_mem(il, base + i + 4 * माप(u32));
		ilink2 = il_पढ़ो_targ_mem(il, base + i + 5 * माप(u32));
		data1 = il_पढ़ो_targ_mem(il, base + i + 6 * माप(u32));

		IL_ERR("%-13s (0x%X) %010u 0x%05X 0x%05X 0x%05X 0x%05X %u\n\n",
		       il3945_desc_lookup(desc), desc, समय, blink1, blink2,
		       ilink1, ilink2, data1);
	पूर्ण
पूर्ण

अटल व्योम
il3945_irq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा il_priv *il = from_tasklet(il, t, irq_tasklet);
	u32 पूर्णांकa, handled = 0;
	u32 पूर्णांकa_fh;
	अचिन्हित दीर्घ flags;
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	u32 पूर्णांकa_mask;
#पूर्ण_अगर

	spin_lock_irqsave(&il->lock, flags);

	/* Ack/clear/reset pending uCode पूर्णांकerrupts.
	 * Note:  Some bits in CSR_INT are "OR" of bits in CSR_FH_INT_STATUS,
	 *  and will clear only when CSR_FH_INT_STATUS माला_लो cleared. */
	पूर्णांकa = _il_rd(il, CSR_INT);
	_il_wr(il, CSR_INT, पूर्णांकa);

	/* Ack/clear/reset pending flow-handler (DMA) पूर्णांकerrupts.
	 * Any new पूर्णांकerrupts that happen after this, either जबतक we're
	 * in this tasklet, or later, will show up in next ISR/tasklet. */
	पूर्णांकa_fh = _il_rd(il, CSR_FH_INT_STATUS);
	_il_wr(il, CSR_FH_INT_STATUS, पूर्णांकa_fh);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (il_get_debug_level(il) & IL_DL_ISR) अणु
		/* just क्रम debug */
		पूर्णांकa_mask = _il_rd(il, CSR_INT_MASK);
		D_ISR("inta 0x%08x, enabled 0x%08x, fh 0x%08x\n", पूर्णांकa,
		      पूर्णांकa_mask, पूर्णांकa_fh);
	पूर्ण
#पूर्ण_अगर

	spin_unlock_irqrestore(&il->lock, flags);

	/* Since CSR_INT and CSR_FH_INT_STATUS पढ़ोs and clears are not
	 * atomic, make sure that पूर्णांकa covers all the पूर्णांकerrupts that
	 * we've discovered, even अगर FH पूर्णांकerrupt came in just after
	 * पढ़ोing CSR_INT. */
	अगर (पूर्णांकa_fh & CSR39_FH_INT_RX_MASK)
		पूर्णांकa |= CSR_INT_BIT_FH_RX;
	अगर (पूर्णांकa_fh & CSR39_FH_INT_TX_MASK)
		पूर्णांकa |= CSR_INT_BIT_FH_TX;

	/* Now service all पूर्णांकerrupt bits discovered above. */
	अगर (पूर्णांकa & CSR_INT_BIT_HW_ERR) अणु
		IL_ERR("Hardware error detected.  Restarting.\n");

		/* Tell the device to stop sending पूर्णांकerrupts */
		il_disable_पूर्णांकerrupts(il);

		il->isr_stats.hw++;
		il_irq_handle_error(il);

		handled |= CSR_INT_BIT_HW_ERR;

		वापस;
	पूर्ण
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (il_get_debug_level(il) & (IL_DL_ISR)) अणु
		/* NIC fires this, but we करोn't use it, redundant with WAKEUP */
		अगर (पूर्णांकa & CSR_INT_BIT_SCD) अणु
			D_ISR("Scheduler finished to transmit "
			      "the frame/frames.\n");
			il->isr_stats.sch++;
		पूर्ण

		/* Alive notअगरication via Rx पूर्णांकerrupt will करो the real work */
		अगर (पूर्णांकa & CSR_INT_BIT_ALIVE) अणु
			D_ISR("Alive interrupt\n");
			il->isr_stats.alive++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* Safely ignore these bits क्रम debug checks below */
	पूर्णांकa &= ~(CSR_INT_BIT_SCD | CSR_INT_BIT_ALIVE);

	/* Error detected by uCode */
	अगर (पूर्णांकa & CSR_INT_BIT_SW_ERR) अणु
		IL_ERR("Microcode SW error detected. " "Restarting 0x%X.\n",
		       पूर्णांकa);
		il->isr_stats.sw++;
		il_irq_handle_error(il);
		handled |= CSR_INT_BIT_SW_ERR;
	पूर्ण

	/* uCode wakes up after घातer-करोwn sleep */
	अगर (पूर्णांकa & CSR_INT_BIT_WAKEUP) अणु
		D_ISR("Wakeup interrupt\n");
		il_rx_queue_update_ग_लिखो_ptr(il, &il->rxq);

		spin_lock_irqsave(&il->lock, flags);
		il_txq_update_ग_लिखो_ptr(il, &il->txq[0]);
		il_txq_update_ग_लिखो_ptr(il, &il->txq[1]);
		il_txq_update_ग_लिखो_ptr(il, &il->txq[2]);
		il_txq_update_ग_लिखो_ptr(il, &il->txq[3]);
		il_txq_update_ग_लिखो_ptr(il, &il->txq[4]);
		spin_unlock_irqrestore(&il->lock, flags);

		il->isr_stats.wakeup++;
		handled |= CSR_INT_BIT_WAKEUP;
	पूर्ण

	/* All uCode command responses, including Tx command responses,
	 * Rx "responses" (frame-received notअगरication), and other
	 * notअगरications from uCode come through here*/
	अगर (पूर्णांकa & (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX)) अणु
		il3945_rx_handle(il);
		il->isr_stats.rx++;
		handled |= (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX);
	पूर्ण

	अगर (पूर्णांकa & CSR_INT_BIT_FH_TX) अणु
		D_ISR("Tx interrupt\n");
		il->isr_stats.tx++;

		_il_wr(il, CSR_FH_INT_STATUS, (1 << 6));
		il_wr(il, FH39_TCSR_CREDIT(FH39_SRVC_CHNL), 0x0);
		handled |= CSR_INT_BIT_FH_TX;
	पूर्ण

	अगर (पूर्णांकa & ~handled) अणु
		IL_ERR("Unhandled INTA bits 0x%08x\n", पूर्णांकa & ~handled);
		il->isr_stats.unhandled++;
	पूर्ण

	अगर (पूर्णांकa & ~il->पूर्णांकa_mask) अणु
		IL_WARN("Disabled INTA bits 0x%08x were pending\n",
			पूर्णांकa & ~il->पूर्णांकa_mask);
		IL_WARN("   with inta_fh = 0x%08x\n", पूर्णांकa_fh);
	पूर्ण

	/* Re-enable all पूर्णांकerrupts */
	/* only Re-enable अगर disabled by irq */
	अगर (test_bit(S_INT_ENABLED, &il->status))
		il_enable_पूर्णांकerrupts(il);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (il_get_debug_level(il) & (IL_DL_ISR)) अणु
		पूर्णांकa = _il_rd(il, CSR_INT);
		पूर्णांकa_mask = _il_rd(il, CSR_INT_MASK);
		पूर्णांकa_fh = _il_rd(il, CSR_FH_INT_STATUS);
		D_ISR("End inta 0x%08x, enabled 0x%08x, fh 0x%08x, "
		      "flags 0x%08lx\n", पूर्णांकa, पूर्णांकa_mask, पूर्णांकa_fh, flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
il3945_get_channels_क्रम_scan(काष्ठा il_priv *il, क्रमागत nl80211_band band,
			     u8 is_active, u8 n_probes,
			     काष्ठा il3945_scan_channel *scan_ch,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_channel *chan;
	स्थिर काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा il_channel_info *ch_info;
	u16 passive_dwell = 0;
	u16 active_dwell = 0;
	पूर्णांक added, i;

	sband = il_get_hw_mode(il, band);
	अगर (!sband)
		वापस 0;

	active_dwell = il_get_active_dwell_समय(il, band, n_probes);
	passive_dwell = il_get_passive_dwell_समय(il, band, vअगर);

	अगर (passive_dwell <= active_dwell)
		passive_dwell = active_dwell + 1;

	क्रम (i = 0, added = 0; i < il->scan_request->n_channels; i++) अणु
		chan = il->scan_request->channels[i];

		अगर (chan->band != band)
			जारी;

		scan_ch->channel = chan->hw_value;

		ch_info = il_get_channel_info(il, band, scan_ch->channel);
		अगर (!il_is_channel_valid(ch_info)) अणु
			D_SCAN("Channel %d is INVALID for this band.\n",
			       scan_ch->channel);
			जारी;
		पूर्ण

		scan_ch->active_dwell = cpu_to_le16(active_dwell);
		scan_ch->passive_dwell = cpu_to_le16(passive_dwell);
		/* If passive , set up क्रम स्वतः-चयन
		 *  and use दीर्घ active_dwell समय.
		 */
		अगर (!is_active || il_is_channel_passive(ch_info) ||
		    (chan->flags & IEEE80211_CHAN_NO_IR)) अणु
			scan_ch->type = 0;	/* passive */
			अगर (IL_UCODE_API(il->ucode_ver) == 1)
				scan_ch->active_dwell =
				    cpu_to_le16(passive_dwell - 1);
		पूर्ण अन्यथा अणु
			scan_ch->type = 1;	/* active */
		पूर्ण

		/* Set direct probe bits. These may be used both क्रम active
		 * scan channels (probes माला_लो sent right away),
		 * or क्रम passive channels (probes get se sent only after
		 * hearing clear Rx packet).*/
		अगर (IL_UCODE_API(il->ucode_ver) >= 2) अणु
			अगर (n_probes)
				scan_ch->type |= IL39_SCAN_PROBE_MASK(n_probes);
		पूर्ण अन्यथा अणु
			/* uCode v1 करोes not allow setting direct probe bits on
			 * passive channel. */
			अगर ((scan_ch->type & 1) && n_probes)
				scan_ch->type |= IL39_SCAN_PROBE_MASK(n_probes);
		पूर्ण

		/* Set txघातer levels to शेषs */
		scan_ch->tpc.dsp_atten = 110;
		/* scan_pwr_info->tpc.dsp_atten; */

		/*scan_pwr_info->tpc.tx_gain; */
		अगर (band == NL80211_BAND_5GHZ)
			scan_ch->tpc.tx_gain = ((1 << 5) | (3 << 3)) | 3;
		अन्यथा अणु
			scan_ch->tpc.tx_gain = ((1 << 5) | (5 << 3));
			/* NOTE: अगर we were करोing 6Mb OFDM क्रम scans we'd use
			 * घातer level:
			 * scan_ch->tpc.tx_gain = ((1 << 5) | (2 << 3)) | 3;
			 */
		पूर्ण

		D_SCAN("Scanning %d [%s %d]\n", scan_ch->channel,
		       (scan_ch->type & 1) ? "ACTIVE" : "PASSIVE",
		       (scan_ch->type & 1) ? active_dwell : passive_dwell);

		scan_ch++;
		added++;
	पूर्ण

	D_SCAN("total channels to scan %d\n", added);
	वापस added;
पूर्ण

अटल व्योम
il3945_init_hw_rates(काष्ठा il_priv *il, काष्ठा ieee80211_rate *rates)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RATE_COUNT_LEGACY; i++) अणु
		rates[i].bitrate = il3945_rates[i].ieee * 5;
		rates[i].hw_value = i;	/* Rate scaling will work on idxes */
		rates[i].hw_value_लघु = i;
		rates[i].flags = 0;
		अगर (i > IL39_LAST_OFDM_RATE || i < IL_FIRST_OFDM_RATE) अणु
			/*
			 * If CCK != 1M then set लघु preamble rate flag.
			 */
			rates[i].flags |=
			    (il3945_rates[i].plcp ==
			     10) ? 0 : IEEE80211_RATE_SHORT_PREAMBLE;
		पूर्ण
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * uCode करोwnload functions
 *
 ******************************************************************************/

अटल व्योम
il3945_dealloc_ucode_pci(काष्ठा il_priv *il)
अणु
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_code);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_data);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_data_backup);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_init);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_init_data);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_boot);
पूर्ण

/*
 * il3945_verअगरy_inst_full - verअगरy runसमय uCode image in card vs. host,
 *     looking at all data.
 */
अटल पूर्णांक
il3945_verअगरy_inst_full(काष्ठा il_priv *il, __le32 * image, u32 len)
अणु
	u32 val;
	u32 save_len = len;
	पूर्णांक rc = 0;
	u32 errcnt;

	D_INFO("ucode inst image size is %u\n", len);

	il_wr(il, HBUS_TARG_MEM_RADDR, IL39_RTC_INST_LOWER_BOUND);

	errcnt = 0;
	क्रम (; len > 0; len -= माप(u32), image++) अणु
		/* पढ़ो data comes through single port, स्वतः-incr addr */
		/* NOTE: Use the debugless पढ़ो so we करोn't flood kernel log
		 * अगर IL_DL_IO is set */
		val = _il_rd(il, HBUS_TARG_MEM_RDAT);
		अगर (val != le32_to_cpu(*image)) अणु
			IL_ERR("uCode INST section is invalid at "
			       "offset 0x%x, is 0x%x, s/b 0x%x\n",
			       save_len - len, val, le32_to_cpu(*image));
			rc = -EIO;
			errcnt++;
			अगर (errcnt >= 20)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!errcnt)
		D_INFO("ucode image in INSTRUCTION memory is good\n");

	वापस rc;
पूर्ण

/*
 * il3945_verअगरy_inst_sparse - verअगरy runसमय uCode image in card vs. host,
 *   using sample data 100 bytes apart.  If these sample poपूर्णांकs are good,
 *   it's a pretty good bet that everything between them is good, too.
 */
अटल पूर्णांक
il3945_verअगरy_inst_sparse(काष्ठा il_priv *il, __le32 * image, u32 len)
अणु
	u32 val;
	पूर्णांक rc = 0;
	u32 errcnt = 0;
	u32 i;

	D_INFO("ucode inst image size is %u\n", len);

	क्रम (i = 0; i < len; i += 100, image += 100 / माप(u32)) अणु
		/* पढ़ो data comes through single port, स्वतः-incr addr */
		/* NOTE: Use the debugless पढ़ो so we करोn't flood kernel log
		 * अगर IL_DL_IO is set */
		il_wr(il, HBUS_TARG_MEM_RADDR, i + IL39_RTC_INST_LOWER_BOUND);
		val = _il_rd(il, HBUS_TARG_MEM_RDAT);
		अगर (val != le32_to_cpu(*image)) अणु
#अगर 0				/* Enable this अगर you want to see details */
			IL_ERR("uCode INST section is invalid at "
			       "offset 0x%x, is 0x%x, s/b 0x%x\n", i, val,
			       *image);
#पूर्ण_अगर
			rc = -EIO;
			errcnt++;
			अगर (errcnt >= 3)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/*
 * il3945_verअगरy_ucode - determine which inकाष्ठाion image is in SRAM,
 *    and verअगरy its contents
 */
अटल पूर्णांक
il3945_verअगरy_ucode(काष्ठा il_priv *il)
अणु
	__le32 *image;
	u32 len;
	पूर्णांक rc = 0;

	/* Try bootstrap */
	image = (__le32 *) il->ucode_boot.v_addr;
	len = il->ucode_boot.len;
	rc = il3945_verअगरy_inst_sparse(il, image, len);
	अगर (rc == 0) अणु
		D_INFO("Bootstrap uCode is good in inst SRAM\n");
		वापस 0;
	पूर्ण

	/* Try initialize */
	image = (__le32 *) il->ucode_init.v_addr;
	len = il->ucode_init.len;
	rc = il3945_verअगरy_inst_sparse(il, image, len);
	अगर (rc == 0) अणु
		D_INFO("Initialize uCode is good in inst SRAM\n");
		वापस 0;
	पूर्ण

	/* Try runसमय/protocol */
	image = (__le32 *) il->ucode_code.v_addr;
	len = il->ucode_code.len;
	rc = il3945_verअगरy_inst_sparse(il, image, len);
	अगर (rc == 0) अणु
		D_INFO("Runtime uCode is good in inst SRAM\n");
		वापस 0;
	पूर्ण

	IL_ERR("NO VALID UCODE IMAGE IN INSTRUCTION SRAM!!\n");

	/* Since nothing seems to match, show first several data entries in
	 * inकाष्ठाion SRAM, so maybe visual inspection will give a clue.
	 * Selection of bootstrap image (vs. other images) is arbitrary. */
	image = (__le32 *) il->ucode_boot.v_addr;
	len = il->ucode_boot.len;
	rc = il3945_verअगरy_inst_full(il, image, len);

	वापस rc;
पूर्ण

अटल व्योम
il3945_nic_start(काष्ठा il_priv *il)
अणु
	/* Remove all resets to allow NIC to operate */
	_il_wr(il, CSR_RESET, 0);
पूर्ण

#घोषणा IL3945_UCODE_GET(item)						\
अटल u32 il3945_ucode_get_##item(स्थिर काष्ठा il_ucode_header *ucode)\
अणु									\
	वापस le32_to_cpu(ucode->v1.item);				\
पूर्ण

अटल u32
il3945_ucode_get_header_size(u32 api_ver)
अणु
	वापस 24;
पूर्ण

अटल u8 *
il3945_ucode_get_data(स्थिर काष्ठा il_ucode_header *ucode)
अणु
	वापस (u8 *) ucode->v1.data;
पूर्ण

IL3945_UCODE_GET(inst_size);
IL3945_UCODE_GET(data_size);
IL3945_UCODE_GET(init_size);
IL3945_UCODE_GET(init_data_size);
IL3945_UCODE_GET(boot_size);

/*
 * il3945_पढ़ो_ucode - Read uCode images from disk file.
 *
 * Copy पूर्णांकo buffers क्रम card to fetch via bus-mastering
 */
अटल पूर्णांक
il3945_पढ़ो_ucode(काष्ठा il_priv *il)
अणु
	स्थिर काष्ठा il_ucode_header *ucode;
	पूर्णांक ret = -EINVAL, idx;
	स्थिर काष्ठा firmware *ucode_raw;
	/* firmware file name contains uCode/driver compatibility version */
	स्थिर अक्षर *name_pre = il->cfg->fw_name_pre;
	स्थिर अचिन्हित पूर्णांक api_max = il->cfg->ucode_api_max;
	स्थिर अचिन्हित पूर्णांक api_min = il->cfg->ucode_api_min;
	अक्षर buf[25];
	u8 *src;
	माप_प्रकार len;
	u32 api_ver, inst_size, data_size, init_size, init_data_size, boot_size;

	/* Ask kernel firmware_class module to get the boot firmware off disk.
	 * request_firmware() is synchronous, file is in memory on वापस. */
	क्रम (idx = api_max; idx >= api_min; idx--) अणु
		प्र_लिखो(buf, "%s%u%s", name_pre, idx, ".ucode");
		ret = request_firmware(&ucode_raw, buf, &il->pci_dev->dev);
		अगर (ret < 0) अणु
			IL_ERR("%s firmware file req failed: %d\n", buf, ret);
			अगर (ret == -ENOENT)
				जारी;
			अन्यथा
				जाओ error;
		पूर्ण अन्यथा अणु
			अगर (idx < api_max)
				IL_ERR("Loaded firmware %s, "
				       "which is deprecated. "
				       " Please use API v%u instead.\n", buf,
				       api_max);
			D_INFO("Got firmware '%s' file "
			       "(%zd bytes) from disk\n", buf, ucode_raw->size);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		जाओ error;

	/* Make sure that we got at least our header! */
	अगर (ucode_raw->size < il3945_ucode_get_header_size(1)) अणु
		IL_ERR("File size way too small!\n");
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण

	/* Data from ucode file:  header followed by uCode images */
	ucode = (काष्ठा il_ucode_header *)ucode_raw->data;

	il->ucode_ver = le32_to_cpu(ucode->ver);
	api_ver = IL_UCODE_API(il->ucode_ver);
	inst_size = il3945_ucode_get_inst_size(ucode);
	data_size = il3945_ucode_get_data_size(ucode);
	init_size = il3945_ucode_get_init_size(ucode);
	init_data_size = il3945_ucode_get_init_data_size(ucode);
	boot_size = il3945_ucode_get_boot_size(ucode);
	src = il3945_ucode_get_data(ucode);

	/* api_ver should match the api version क्रमming part of the
	 * firmware filename ... but we करोn't check क्रम that and only rely
	 * on the API version पढ़ो from firmware header from here on क्रमward */

	अगर (api_ver < api_min || api_ver > api_max) अणु
		IL_ERR("Driver unable to support your firmware API. "
		       "Driver supports v%u, firmware is v%u.\n", api_max,
		       api_ver);
		il->ucode_ver = 0;
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण
	अगर (api_ver != api_max)
		IL_ERR("Firmware has old API version. Expected %u, "
		       "got %u. New firmware can be obtained "
		       "from http://www.intellinuxwireless.org.\n", api_max,
		       api_ver);

	IL_INFO("loaded firmware version %u.%u.%u.%u\n",
		IL_UCODE_MAJOR(il->ucode_ver), IL_UCODE_MINOR(il->ucode_ver),
		IL_UCODE_API(il->ucode_ver), IL_UCODE_SERIAL(il->ucode_ver));

	snम_लिखो(il->hw->wiphy->fw_version, माप(il->hw->wiphy->fw_version),
		 "%u.%u.%u.%u", IL_UCODE_MAJOR(il->ucode_ver),
		 IL_UCODE_MINOR(il->ucode_ver), IL_UCODE_API(il->ucode_ver),
		 IL_UCODE_SERIAL(il->ucode_ver));

	D_INFO("f/w package hdr ucode version raw = 0x%x\n", il->ucode_ver);
	D_INFO("f/w package hdr runtime inst size = %u\n", inst_size);
	D_INFO("f/w package hdr runtime data size = %u\n", data_size);
	D_INFO("f/w package hdr init inst size = %u\n", init_size);
	D_INFO("f/w package hdr init data size = %u\n", init_data_size);
	D_INFO("f/w package hdr boot inst size = %u\n", boot_size);

	/* Verअगरy size of file vs. image size info in file's header */
	अगर (ucode_raw->size !=
	    il3945_ucode_get_header_size(api_ver) + inst_size + data_size +
	    init_size + init_data_size + boot_size) अणु

		D_INFO("uCode file size %zd does not match expected size\n",
		       ucode_raw->size);
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण

	/* Verअगरy that uCode images will fit in card's SRAM */
	अगर (inst_size > IL39_MAX_INST_SIZE) अणु
		D_INFO("uCode instr len %d too large to fit in\n", inst_size);
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण

	अगर (data_size > IL39_MAX_DATA_SIZE) अणु
		D_INFO("uCode data len %d too large to fit in\n", data_size);
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण
	अगर (init_size > IL39_MAX_INST_SIZE) अणु
		D_INFO("uCode init instr len %d too large to fit in\n",
		       init_size);
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण
	अगर (init_data_size > IL39_MAX_DATA_SIZE) अणु
		D_INFO("uCode init data len %d too large to fit in\n",
		       init_data_size);
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण
	अगर (boot_size > IL39_MAX_BSM_SIZE) अणु
		D_INFO("uCode boot instr len %d too large to fit in\n",
		       boot_size);
		ret = -EINVAL;
		जाओ err_release;
	पूर्ण

	/* Allocate ucode buffers क्रम card's bus-master loading ... */

	/* Runसमय inकाष्ठाions and 2 copies of data:
	 * 1) unmodअगरied from disk
	 * 2) backup cache क्रम save/restore during घातer-करोwns */
	il->ucode_code.len = inst_size;
	il_alloc_fw_desc(il->pci_dev, &il->ucode_code);

	il->ucode_data.len = data_size;
	il_alloc_fw_desc(il->pci_dev, &il->ucode_data);

	il->ucode_data_backup.len = data_size;
	il_alloc_fw_desc(il->pci_dev, &il->ucode_data_backup);

	अगर (!il->ucode_code.v_addr || !il->ucode_data.v_addr ||
	    !il->ucode_data_backup.v_addr)
		जाओ err_pci_alloc;

	/* Initialization inकाष्ठाions and data */
	अगर (init_size && init_data_size) अणु
		il->ucode_init.len = init_size;
		il_alloc_fw_desc(il->pci_dev, &il->ucode_init);

		il->ucode_init_data.len = init_data_size;
		il_alloc_fw_desc(il->pci_dev, &il->ucode_init_data);

		अगर (!il->ucode_init.v_addr || !il->ucode_init_data.v_addr)
			जाओ err_pci_alloc;
	पूर्ण

	/* Bootstrap (inकाष्ठाions only, no data) */
	अगर (boot_size) अणु
		il->ucode_boot.len = boot_size;
		il_alloc_fw_desc(il->pci_dev, &il->ucode_boot);

		अगर (!il->ucode_boot.v_addr)
			जाओ err_pci_alloc;
	पूर्ण

	/* Copy images पूर्णांकo buffers क्रम card's bus-master पढ़ोs ... */

	/* Runसमय inकाष्ठाions (first block of data in file) */
	len = inst_size;
	D_INFO("Copying (but not loading) uCode instr len %zd\n", len);
	स_नकल(il->ucode_code.v_addr, src, len);
	src += len;

	D_INFO("uCode instr buf vaddr = 0x%p, paddr = 0x%08x\n",
	       il->ucode_code.v_addr, (u32) il->ucode_code.p_addr);

	/* Runसमय data (2nd block)
	 * NOTE:  Copy पूर्णांकo backup buffer will be करोne in il3945_up()  */
	len = data_size;
	D_INFO("Copying (but not loading) uCode data len %zd\n", len);
	स_नकल(il->ucode_data.v_addr, src, len);
	स_नकल(il->ucode_data_backup.v_addr, src, len);
	src += len;

	/* Initialization inकाष्ठाions (3rd block) */
	अगर (init_size) अणु
		len = init_size;
		D_INFO("Copying (but not loading) init instr len %zd\n", len);
		स_नकल(il->ucode_init.v_addr, src, len);
		src += len;
	पूर्ण

	/* Initialization data (4th block) */
	अगर (init_data_size) अणु
		len = init_data_size;
		D_INFO("Copying (but not loading) init data len %zd\n", len);
		स_नकल(il->ucode_init_data.v_addr, src, len);
		src += len;
	पूर्ण

	/* Bootstrap inकाष्ठाions (5th block) */
	len = boot_size;
	D_INFO("Copying (but not loading) boot instr len %zd\n", len);
	स_नकल(il->ucode_boot.v_addr, src, len);

	/* We have our copies now, allow OS release its copies */
	release_firmware(ucode_raw);
	वापस 0;

err_pci_alloc:
	IL_ERR("failed to allocate pci memory\n");
	ret = -ENOMEM;
	il3945_dealloc_ucode_pci(il);

err_release:
	release_firmware(ucode_raw);

error:
	वापस ret;
पूर्ण

/*
 * il3945_set_ucode_ptrs - Set uCode address location
 *
 * Tell initialization uCode where to find runसमय uCode.
 *
 * BSM रेजिस्टरs initially contain poपूर्णांकers to initialization uCode.
 * We need to replace them to load runसमय uCode inst and data,
 * and to save runसमय data when घातering करोwn.
 */
अटल पूर्णांक
il3945_set_ucode_ptrs(काष्ठा il_priv *il)
अणु
	dma_addr_t pinst;
	dma_addr_t pdata;

	/* bits 31:0 क्रम 3945 */
	pinst = il->ucode_code.p_addr;
	pdata = il->ucode_data_backup.p_addr;

	/* Tell bootstrap uCode where to find image to load */
	il_wr_prph(il, BSM_DRAM_INST_PTR_REG, pinst);
	il_wr_prph(il, BSM_DRAM_DATA_PTR_REG, pdata);
	il_wr_prph(il, BSM_DRAM_DATA_BYTECOUNT_REG, il->ucode_data.len);

	/* Inst byte count must be last to set up, bit 31 संकेतs uCode
	 *   that all new ptr/size info is in place */
	il_wr_prph(il, BSM_DRAM_INST_BYTECOUNT_REG,
		   il->ucode_code.len | BSM_DRAM_INST_LOAD);

	D_INFO("Runtime uCode pointers are set.\n");

	वापस 0;
पूर्ण

/*
 * il3945_init_alive_start - Called after N_ALIVE notअगरication received
 *
 * Called after N_ALIVE notअगरication received from "initialize" uCode.
 *
 * Tell "initialize" uCode to go ahead and load the runसमय uCode.
 */
अटल व्योम
il3945_init_alive_start(काष्ठा il_priv *il)
अणु
	/* Check alive response क्रम "valid" sign from uCode */
	अगर (il->card_alive_init.is_valid != UCODE_VALID_OK) अणु
		/* We had an error bringing up the hardware, so take it
		 * all the way back करोwn so we can try again */
		D_INFO("Initialize Alive failed.\n");
		जाओ restart;
	पूर्ण

	/* Bootstrap uCode has loaded initialize uCode ... verअगरy inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "initialize" alive अगर code weren't properly loaded.  */
	अगर (il3945_verअगरy_ucode(il)) अणु
		/* Runसमय inकाष्ठाion load was bad;
		 * take it all the way back करोwn so we can try again */
		D_INFO("Bad \"initialize\" uCode load.\n");
		जाओ restart;
	पूर्ण

	/* Send poपूर्णांकers to protocol/runसमय uCode image ... init code will
	 * load and launch runसमय uCode, which will send us another "Alive"
	 * notअगरication. */
	D_INFO("Initialization Alive received.\n");
	अगर (il3945_set_ucode_ptrs(il)) अणु
		/* Runसमय inकाष्ठाion load won't happen;
		 * take it all the way back करोwn so we can try again */
		D_INFO("Couldn't set up uCode pointers.\n");
		जाओ restart;
	पूर्ण
	वापस;

restart:
	queue_work(il->workqueue, &il->restart);
पूर्ण

/*
 * il3945_alive_start - called after N_ALIVE notअगरication received
 *                   from protocol/runसमय uCode (initialization uCode's
 *                   Alive माला_लो handled by il3945_init_alive_start()).
 */
अटल व्योम
il3945_alive_start(काष्ठा il_priv *il)
अणु
	पूर्णांक thermal_spin = 0;
	u32 rfसमाप्त;

	D_INFO("Runtime Alive received.\n");

	अगर (il->card_alive.is_valid != UCODE_VALID_OK) अणु
		/* We had an error bringing up the hardware, so take it
		 * all the way back करोwn so we can try again */
		D_INFO("Alive failed.\n");
		जाओ restart;
	पूर्ण

	/* Initialize uCode has loaded Runसमय uCode ... verअगरy inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "runtime" alive अगर code weren't properly loaded.  */
	अगर (il3945_verअगरy_ucode(il)) अणु
		/* Runसमय inकाष्ठाion load was bad;
		 * take it all the way back करोwn so we can try again */
		D_INFO("Bad runtime uCode load.\n");
		जाओ restart;
	पूर्ण

	rfसमाप्त = il_rd_prph(il, APMG_RFKILL_REG);
	D_INFO("RFKILL status: 0x%x\n", rfसमाप्त);

	अगर (rfसमाप्त & 0x1) अणु
		clear_bit(S_RFKILL, &il->status);
		/* अगर RFKILL is not on, then रुको क्रम thermal
		 * sensor in adapter to kick in */
		जबतक (il3945_hw_get_temperature(il) == 0) अणु
			thermal_spin++;
			udelay(10);
		पूर्ण

		अगर (thermal_spin)
			D_INFO("Thermal calibration took %dus\n",
			       thermal_spin * 10);
	पूर्ण अन्यथा
		set_bit(S_RFKILL, &il->status);

	/* After the ALIVE response, we can send commands to 3945 uCode */
	set_bit(S_ALIVE, &il->status);

	/* Enable watchकरोg to monitor the driver tx queues */
	il_setup_watchकरोg(il);

	अगर (il_is_rfसमाप्त(il))
		वापस;

	ieee80211_wake_queues(il->hw);

	il->active_rate = RATES_MASK_3945;

	il_घातer_update_mode(il, true);

	अगर (il_is_associated(il)) अणु
		काष्ठा il3945_rxon_cmd *active_rxon =
		    (काष्ठा il3945_rxon_cmd *)(&il->active);

		il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	पूर्ण अन्यथा अणु
		/* Initialize our rx_config data */
		il_connection_init_rx_config(il);
	पूर्ण

	/* Configure Bluetooth device coexistence support */
	il_send_bt_config(il);

	set_bit(S_READY, &il->status);

	/* Configure the adapter क्रम unassociated operation */
	il3945_commit_rxon(il);

	il3945_reg_txघातer_periodic(il);

	D_INFO("ALIVE processing complete.\n");
	wake_up(&il->रुको_command_queue);

	वापस;

restart:
	queue_work(il->workqueue, &il->restart);
पूर्ण

अटल व्योम il3945_cancel_deferred_work(काष्ठा il_priv *il);

अटल व्योम
__il3945_करोwn(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक निकास_pending;

	D_INFO(DRV_NAME " is going down\n");

	il_scan_cancel_समयout(il, 200);

	निकास_pending = test_and_set_bit(S_EXIT_PENDING, &il->status);

	/* Stop TX queues watchकरोg. We need to have S_EXIT_PENDING bit set
	 * to prevent rearm समयr */
	del_समयr_sync(&il->watchकरोg);

	/* Station inक्रमmation will now be cleared in device */
	il_clear_ucode_stations(il);
	il_dealloc_bcast_stations(il);
	il_clear_driver_stations(il);

	/* Unblock any रुकोing calls */
	wake_up_all(&il->रुको_command_queue);

	/* Wipe out the EXIT_PENDING status bit अगर we are not actually
	 * निकासing the module */
	अगर (!निकास_pending)
		clear_bit(S_EXIT_PENDING, &il->status);

	/* stop and reset the on-board processor */
	_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_NEVO_RESET);

	/* tell the device to stop sending पूर्णांकerrupts */
	spin_lock_irqsave(&il->lock, flags);
	il_disable_पूर्णांकerrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);
	il3945_synchronize_irq(il);

	अगर (il->mac80211_रेजिस्टरed)
		ieee80211_stop_queues(il->hw);

	/* If we have not previously called il3945_init() then
	 * clear all bits but the RF Kill bits and वापस */
	अगर (!il_is_init(il)) अणु
		il->status =
		    test_bit(S_RFKILL, &il->status) << S_RFKILL |
		    test_bit(S_GEO_CONFIGURED, &il->status) << S_GEO_CONFIGURED |
		    test_bit(S_EXIT_PENDING, &il->status) << S_EXIT_PENDING;
		जाओ निकास;
	पूर्ण

	/* ...otherwise clear out all the status bits but the RF Kill
	 * bit and जारी taking the NIC करोwn. */
	il->status &=
	    test_bit(S_RFKILL, &il->status) << S_RFKILL |
	    test_bit(S_GEO_CONFIGURED, &il->status) << S_GEO_CONFIGURED |
	    test_bit(S_FW_ERROR, &il->status) << S_FW_ERROR |
	    test_bit(S_EXIT_PENDING, &il->status) << S_EXIT_PENDING;

	/*
	 * We disabled and synchronized पूर्णांकerrupt, and priv->mutex is taken, so
	 * here is the only thपढ़ो which will program device रेजिस्टरs, but
	 * still have lockdep निश्चितions, so we are taking reg_lock.
	 */
	spin_lock_irq(&il->reg_lock);
	/* FIXME: il_grab_nic_access अगर rfसमाप्त is off ? */

	il3945_hw_txq_ctx_stop(il);
	il3945_hw_rxq_stop(il);
	/* Power-करोwn device's busmaster DMA घड़ीs */
	_il_wr_prph(il, APMG_CLK_DIS_REG, APMG_CLK_VAL_DMA_CLK_RQT);
	udelay(5);
	/* Stop the device, and put it in low घातer state */
	_il_apm_stop(il);

	spin_unlock_irq(&il->reg_lock);

	il3945_hw_txq_ctx_मुक्त(il);
निकास:
	स_रखो(&il->card_alive, 0, माप(काष्ठा il_alive_resp));
	dev_kमुक्त_skb(il->beacon_skb);
	il->beacon_skb = शून्य;

	/* clear out any मुक्त frames */
	il3945_clear_मुक्त_frames(il);
पूर्ण

अटल व्योम
il3945_करोwn(काष्ठा il_priv *il)
अणु
	mutex_lock(&il->mutex);
	__il3945_करोwn(il);
	mutex_unlock(&il->mutex);

	il3945_cancel_deferred_work(il);
पूर्ण

#घोषणा MAX_HW_RESTARTS 5

अटल पूर्णांक
il3945_alloc_bcast_station(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;
	u8 sta_id;

	spin_lock_irqsave(&il->sta_lock, flags);
	sta_id = il_prep_station(il, il_bcast_addr, false, शून्य);
	अगर (sta_id == IL_INVALID_STATION) अणु
		IL_ERR("Unable to prepare broadcast station\n");
		spin_unlock_irqrestore(&il->sta_lock, flags);

		वापस -EINVAL;
	पूर्ण

	il->stations[sta_id].used |= IL_STA_DRIVER_ACTIVE;
	il->stations[sta_id].used |= IL_STA_BCAST;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
__il3945_up(काष्ठा il_priv *il)
अणु
	पूर्णांक rc, i;

	rc = il3945_alloc_bcast_station(il);
	अगर (rc)
		वापस rc;

	अगर (test_bit(S_EXIT_PENDING, &il->status)) अणु
		IL_WARN("Exit pending; will not bring the NIC up\n");
		वापस -EIO;
	पूर्ण

	अगर (!il->ucode_data_backup.v_addr || !il->ucode_data.v_addr) अणु
		IL_ERR("ucode not available for device bring up\n");
		वापस -EIO;
	पूर्ण

	/* If platक्रमm's RF_KILL चयन is NOT set to KILL */
	अगर (_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW)
		clear_bit(S_RFKILL, &il->status);
	अन्यथा अणु
		set_bit(S_RFKILL, &il->status);
		वापस -ERFKILL;
	पूर्ण

	_il_wr(il, CSR_INT, 0xFFFFFFFF);

	rc = il3945_hw_nic_init(il);
	अगर (rc) अणु
		IL_ERR("Unable to int nic\n");
		वापस rc;
	पूर्ण

	/* make sure rfसमाप्त handshake bits are cleared */
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

	/* clear (again), then enable host पूर्णांकerrupts */
	_il_wr(il, CSR_INT, 0xFFFFFFFF);
	il_enable_पूर्णांकerrupts(il);

	/* really make sure rfसमाप्त handshake bits are cleared */
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);

	/* Copy original ucode data image from disk पूर्णांकo backup cache.
	 * This will be used to initialize the on-board processor's
	 * data SRAM क्रम a clean start when the runसमय program first loads. */
	स_नकल(il->ucode_data_backup.v_addr, il->ucode_data.v_addr,
	       il->ucode_data.len);

	/* We वापस success when we resume from suspend and rf_समाप्त is on. */
	अगर (test_bit(S_RFKILL, &il->status))
		वापस 0;

	क्रम (i = 0; i < MAX_HW_RESTARTS; i++) अणु

		/* load bootstrap state machine,
		 * load bootstrap program पूर्णांकo processor's memory,
		 * prepare to load the "initialize" uCode */
		rc = il->ops->load_ucode(il);

		अगर (rc) अणु
			IL_ERR("Unable to set up bootstrap uCode: %d\n", rc);
			जारी;
		पूर्ण

		/* start card; "initialize" will load runसमय ucode */
		il3945_nic_start(il);

		D_INFO(DRV_NAME " is coming up\n");

		वापस 0;
	पूर्ण

	set_bit(S_EXIT_PENDING, &il->status);
	__il3945_करोwn(il);
	clear_bit(S_EXIT_PENDING, &il->status);

	/* tried to restart and config the device क्रम as दीर्घ as our
	 * patience could withstand */
	IL_ERR("Unable to initialize device after %d attempts.\n", i);
	वापस -EIO;
पूर्ण

/*****************************************************************************
 *
 * Workqueue callbacks
 *
 *****************************************************************************/

अटल व्योम
il3945_bg_init_alive_start(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il =
	    container_of(data, काष्ठा il_priv, init_alive_start.work);

	mutex_lock(&il->mutex);
	अगर (test_bit(S_EXIT_PENDING, &il->status))
		जाओ out;

	il3945_init_alive_start(il);
out:
	mutex_unlock(&il->mutex);
पूर्ण

अटल व्योम
il3945_bg_alive_start(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il =
	    container_of(data, काष्ठा il_priv, alive_start.work);

	mutex_lock(&il->mutex);
	अगर (test_bit(S_EXIT_PENDING, &il->status) || il->txq == शून्य)
		जाओ out;

	il3945_alive_start(il);
out:
	mutex_unlock(&il->mutex);
पूर्ण

/*
 * 3945 cannot पूर्णांकerrupt driver when hardware rf समाप्त चयन toggles;
 * driver must poll CSR_GP_CNTRL_REG रेजिस्टर क्रम change.  This रेजिस्टर
 * *is* पढ़ोable even when device has been SW_RESET पूर्णांकo low घातer mode
 * (e.g. during RF KILL).
 */
अटल व्योम
il3945_rfसमाप्त_poll(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il =
	    container_of(data, काष्ठा il_priv, _3945.rfसमाप्त_poll.work);
	bool old_rfसमाप्त = test_bit(S_RFKILL, &il->status);
	bool new_rfसमाप्त =
	    !(_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW);

	अगर (new_rfसमाप्त != old_rfसमाप्त) अणु
		अगर (new_rfसमाप्त)
			set_bit(S_RFKILL, &il->status);
		अन्यथा
			clear_bit(S_RFKILL, &il->status);

		wiphy_rfसमाप्त_set_hw_state(il->hw->wiphy, new_rfसमाप्त);

		D_RF_KILL("RF_KILL bit toggled to %s.\n",
			  new_rfसमाप्त ? "disable radio" : "enable radio");
	पूर्ण

	/* Keep this running, even अगर radio now enabled.  This will be
	 * cancelled in mac_start() अगर प्रणाली decides to start again */
	queue_delayed_work(il->workqueue, &il->_3945.rfसमाप्त_poll,
			   round_jअगरfies_relative(2 * HZ));

पूर्ण

पूर्णांक
il3945_request_scan(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा il_host_cmd cmd = अणु
		.id = C_SCAN,
		.len = माप(काष्ठा il3945_scan_cmd),
		.flags = CMD_SIZE_HUGE,
	पूर्ण;
	काष्ठा il3945_scan_cmd *scan;
	u8 n_probes = 0;
	क्रमागत nl80211_band band;
	bool is_active = false;
	पूर्णांक ret;
	u16 len;

	lockdep_निश्चित_held(&il->mutex);

	अगर (!il->scan_cmd) अणु
		il->scan_cmd =
		    kदो_स्मृति(माप(काष्ठा il3945_scan_cmd) + IL_MAX_SCAN_SIZE,
			    GFP_KERNEL);
		अगर (!il->scan_cmd) अणु
			D_SCAN("Fail to allocate scan memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	scan = il->scan_cmd;
	स_रखो(scan, 0, माप(काष्ठा il3945_scan_cmd) + IL_MAX_SCAN_SIZE);

	scan->quiet_plcp_th = IL_PLCP_QUIET_THRESH;
	scan->quiet_समय = IL_ACTIVE_QUIET_TIME;

	अगर (il_is_associated(il)) अणु
		u16 पूर्णांकerval;
		u32 extra;
		u32 suspend_समय = 100;
		u32 scan_suspend_समय = 100;

		D_INFO("Scanning while associated...\n");

		पूर्णांकerval = vअगर->bss_conf.beacon_पूर्णांक;

		scan->suspend_समय = 0;
		scan->max_out_समय = cpu_to_le32(200 * 1024);
		अगर (!पूर्णांकerval)
			पूर्णांकerval = suspend_समय;
		/*
		 * suspend समय क्रमmat:
		 *  0-19: beacon पूर्णांकerval in usec (समय beक्रमe exec.)
		 * 20-23: 0
		 * 24-31: number of beacons (suspend between channels)
		 */

		extra = (suspend_समय / पूर्णांकerval) << 24;
		scan_suspend_समय =
		    0xFF0FFFFF & (extra | ((suspend_समय % पूर्णांकerval) * 1024));

		scan->suspend_समय = cpu_to_le32(scan_suspend_समय);
		D_SCAN("suspend_time 0x%X beacon interval %d\n",
		       scan_suspend_समय, पूर्णांकerval);
	पूर्ण

	अगर (il->scan_request->n_ssids) अणु
		पूर्णांक i, p = 0;
		D_SCAN("Kicking off active scan\n");
		क्रम (i = 0; i < il->scan_request->n_ssids; i++) अणु
			/* always करोes wildcard anyway */
			अगर (!il->scan_request->ssids[i].ssid_len)
				जारी;
			scan->direct_scan[p].id = WLAN_EID_SSID;
			scan->direct_scan[p].len =
			    il->scan_request->ssids[i].ssid_len;
			स_नकल(scan->direct_scan[p].ssid,
			       il->scan_request->ssids[i].ssid,
			       il->scan_request->ssids[i].ssid_len);
			n_probes++;
			p++;
		पूर्ण
		is_active = true;
	पूर्ण अन्यथा
		D_SCAN("Kicking off passive scan.\n");

	/* We करोn't build a direct scan probe request; the uCode will करो
	 * that based on the direct_mask added to each channel entry */
	scan->tx_cmd.tx_flags = TX_CMD_FLG_SEQ_CTL_MSK;
	scan->tx_cmd.sta_id = il->hw_params.bcast_id;
	scan->tx_cmd.stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;

	/* flags + rate selection */

	चयन (il->scan_band) अणु
	हाल NL80211_BAND_2GHZ:
		scan->flags = RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK;
		scan->tx_cmd.rate = RATE_1M_PLCP;
		band = NL80211_BAND_2GHZ;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		scan->tx_cmd.rate = RATE_6M_PLCP;
		band = NL80211_BAND_5GHZ;
		अवरोध;
	शेष:
		IL_WARN("Invalid scan band\n");
		वापस -EIO;
	पूर्ण

	/*
	 * If active scaning is requested but a certain channel is marked
	 * passive, we can करो active scanning अगर we detect transmissions. For
	 * passive only scanning disable चयनing to active on any channel.
	 */
	scan->good_CRC_th =
	    is_active ? IL_GOOD_CRC_TH_DEFAULT : IL_GOOD_CRC_TH_NEVER;

	len =
	    il_fill_probe_req(il, (काष्ठा ieee80211_mgmt *)scan->data,
			      vअगर->addr, il->scan_request->ie,
			      il->scan_request->ie_len,
			      IL_MAX_SCAN_SIZE - माप(*scan));
	scan->tx_cmd.len = cpu_to_le16(len);

	/* select Rx antennas */
	scan->flags |= il3945_get_antenna_flags(il);

	scan->channel_count =
	    il3945_get_channels_क्रम_scan(il, band, is_active, n_probes,
					 (व्योम *)&scan->data[len], vअगर);
	अगर (scan->channel_count == 0) अणु
		D_SCAN("channel count %d\n", scan->channel_count);
		वापस -EIO;
	पूर्ण

	cmd.len +=
	    le16_to_cpu(scan->tx_cmd.len) +
	    scan->channel_count * माप(काष्ठा il3945_scan_channel);
	cmd.data = scan;
	scan->len = cpu_to_le16(cmd.len);

	set_bit(S_SCAN_HW, &il->status);
	ret = il_send_cmd_sync(il, &cmd);
	अगर (ret)
		clear_bit(S_SCAN_HW, &il->status);
	वापस ret;
पूर्ण

व्योम
il3945_post_scan(काष्ठा il_priv *il)
अणु
	/*
	 * Since setting the RXON may have been deferred जबतक
	 * perक्रमming the scan, fire one off अगर needed
	 */
	अगर (स_भेद(&il->staging, &il->active, माप(il->staging)))
		il3945_commit_rxon(il);
पूर्ण

अटल व्योम
il3945_bg_restart(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il = container_of(data, काष्ठा il_priv, restart);

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	अगर (test_and_clear_bit(S_FW_ERROR, &il->status)) अणु
		mutex_lock(&il->mutex);
		il->is_खोलो = 0;
		mutex_unlock(&il->mutex);
		il3945_करोwn(il);
		ieee80211_restart_hw(il->hw);
	पूर्ण अन्यथा अणु
		il3945_करोwn(il);

		mutex_lock(&il->mutex);
		अगर (test_bit(S_EXIT_PENDING, &il->status)) अणु
			mutex_unlock(&il->mutex);
			वापस;
		पूर्ण

		__il3945_up(il);
		mutex_unlock(&il->mutex);
	पूर्ण
पूर्ण

अटल व्योम
il3945_bg_rx_replenish(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il = container_of(data, काष्ठा il_priv, rx_replenish);

	mutex_lock(&il->mutex);
	अगर (test_bit(S_EXIT_PENDING, &il->status))
		जाओ out;

	il3945_rx_replenish(il);
out:
	mutex_unlock(&il->mutex);
पूर्ण

व्योम
il3945_post_associate(काष्ठा il_priv *il)
अणु
	पूर्णांक rc = 0;

	अगर (!il->vअगर || !il->is_खोलो)
		वापस;

	D_ASSOC("Associated as %d to: %pM\n", il->vअगर->bss_conf.aid,
		il->active.bssid_addr);

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	il_scan_cancel_समयout(il, 200);

	il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	il3945_commit_rxon(il);

	rc = il_send_rxon_timing(il);
	अगर (rc)
		IL_WARN("C_RXON_TIMING failed - " "Attempting to continue.\n");

	il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;

	il->staging.assoc_id = cpu_to_le16(il->vअगर->bss_conf.aid);

	D_ASSOC("assoc id %d beacon interval %d\n", il->vअगर->bss_conf.aid,
		il->vअगर->bss_conf.beacon_पूर्णांक);

	अगर (il->vअगर->bss_conf.use_लघु_preamble)
		il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
	अन्यथा
		il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;

	अगर (il->staging.flags & RXON_FLG_BAND_24G_MSK) अणु
		अगर (il->vअगर->bss_conf.use_लघु_slot)
			il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;
	पूर्ण

	il3945_commit_rxon(il);

	चयन (il->vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		il3945_rate_scale_init(il->hw, IL_AP_ID);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		il3945_send_beacon_cmd(il);
		अवरोध;
	शेष:
		IL_ERR("%s Should not be called in %d mode\n", __func__,
		      il->vअगर->type);
		अवरोध;
	पूर्ण
पूर्ण

/*****************************************************************************
 *
 * mac80211 entry poपूर्णांक functions
 *
 *****************************************************************************/

#घोषणा UCODE_READY_TIMEOUT	(2 * HZ)

अटल पूर्णांक
il3945_mac_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret;

	/* we should be verअगरying the device is पढ़ोy to be खोलोed */
	mutex_lock(&il->mutex);
	D_MAC80211("enter\n");

	/* fetch ucode file from disk, alloc and copy to bus-master buffers ...
	 * ucode filename and max sizes are card-specअगरic. */

	अगर (!il->ucode_code.len) अणु
		ret = il3945_पढ़ो_ucode(il);
		अगर (ret) अणु
			IL_ERR("Could not read microcode: %d\n", ret);
			mutex_unlock(&il->mutex);
			जाओ out_release_irq;
		पूर्ण
	पूर्ण

	ret = __il3945_up(il);

	mutex_unlock(&il->mutex);

	अगर (ret)
		जाओ out_release_irq;

	D_INFO("Start UP work.\n");

	/* Wait क्रम START_ALIVE from ucode. Otherwise callbacks from
	 * mac80211 will not be run successfully. */
	ret = रुको_event_समयout(il->रुको_command_queue,
				 test_bit(S_READY, &il->status),
				 UCODE_READY_TIMEOUT);
	अगर (!ret) अणु
		अगर (!test_bit(S_READY, &il->status)) अणु
			IL_ERR("Wait for START_ALIVE timeout after %dms.\n",
			       jअगरfies_to_msecs(UCODE_READY_TIMEOUT));
			ret = -ETIMEDOUT;
			जाओ out_release_irq;
		पूर्ण
	पूर्ण

	/* ucode is running and will send rfसमाप्त notअगरications,
	 * no need to poll the समाप्तचयन state anymore */
	cancel_delayed_work(&il->_3945.rfसमाप्त_poll);

	il->is_खोलो = 1;
	D_MAC80211("leave\n");
	वापस 0;

out_release_irq:
	il->is_खोलो = 0;
	D_MAC80211("leave - failed\n");
	वापस ret;
पूर्ण

अटल व्योम
il3945_mac_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा il_priv *il = hw->priv;

	D_MAC80211("enter\n");

	अगर (!il->is_खोलो) अणु
		D_MAC80211("leave - skip\n");
		वापस;
	पूर्ण

	il->is_खोलो = 0;

	il3945_करोwn(il);

	flush_workqueue(il->workqueue);

	/* start polling the समाप्तचयन state again */
	queue_delayed_work(il->workqueue, &il->_3945.rfसमाप्त_poll,
			   round_jअगरfies_relative(2 * HZ));

	D_MAC80211("leave\n");
पूर्ण

अटल व्योम
il3945_mac_tx(काष्ठा ieee80211_hw *hw,
	       काष्ठा ieee80211_tx_control *control,
	       काष्ठा sk_buff *skb)
अणु
	काष्ठा il_priv *il = hw->priv;

	D_MAC80211("enter\n");

	D_TX("dev->xmit(%d bytes) at rate 0x%02x\n", skb->len,
	     ieee80211_get_tx_rate(hw, IEEE80211_SKB_CB(skb))->bitrate);

	अगर (il3945_tx_skb(il, control->sta, skb))
		dev_kमुक्त_skb_any(skb);

	D_MAC80211("leave\n");
पूर्ण

व्योम
il3945_config_ap(काष्ठा il_priv *il)
अणु
	काष्ठा ieee80211_vअगर *vअगर = il->vअगर;
	पूर्णांक rc = 0;

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	/* The following should be करोne only at AP bring up */
	अगर (!(il_is_associated(il))) अणु

		/* RXON - unassoc (to set timing command) */
		il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
		il3945_commit_rxon(il);

		/* RXON Timing */
		rc = il_send_rxon_timing(il);
		अगर (rc)
			IL_WARN("C_RXON_TIMING failed - "
				"Attempting to continue.\n");

		il->staging.assoc_id = 0;

		अगर (vअगर->bss_conf.use_लघु_preamble)
			il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;

		अगर (il->staging.flags & RXON_FLG_BAND_24G_MSK) अणु
			अगर (vअगर->bss_conf.use_लघु_slot)
				il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
			अन्यथा
				il->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;
		पूर्ण
		/* restore RXON assoc */
		il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		il3945_commit_rxon(il);
	पूर्ण
	il3945_send_beacon_cmd(il);
पूर्ण

अटल पूर्णांक
il3945_mac_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		   काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		   काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret = 0;
	u8 sta_id = IL_INVALID_STATION;
	u8 अटल_key;

	D_MAC80211("enter\n");

	अगर (il3945_mod_params.sw_crypto) अणु
		D_MAC80211("leave - hwcrypto disabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * To support IBSS RSN, करोn't program group keys in IBSS, the
	 * hardware will then not attempt to decrypt the frames.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		D_MAC80211("leave - IBSS RSN\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अटल_key = !il_is_associated(il);

	अगर (!अटल_key) अणु
		sta_id = il_sta_id_or_broadcast(il, sta);
		अगर (sta_id == IL_INVALID_STATION) अणु
			D_MAC80211("leave - station not found\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	mutex_lock(&il->mutex);
	il_scan_cancel_समयout(il, 100);

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (अटल_key)
			ret = il3945_set_अटल_key(il, key);
		अन्यथा
			ret = il3945_set_dynamic_key(il, key, sta_id);
		D_MAC80211("enable hwcrypto key\n");
		अवरोध;
	हाल DISABLE_KEY:
		अगर (अटल_key)
			ret = il3945_हटाओ_अटल_key(il);
		अन्यथा
			ret = il3945_clear_sta_key_info(il, sta_id);
		D_MAC80211("disable hwcrypto key\n");
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	D_MAC80211("leave ret %d\n", ret);
	mutex_unlock(&il->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
il3945_mac_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा il_priv *il = hw->priv;
	काष्ठा il3945_sta_priv *sta_priv = (व्योम *)sta->drv_priv;
	पूर्णांक ret;
	bool is_ap = vअगर->type == NL80211_IFTYPE_STATION;
	u8 sta_id;

	mutex_lock(&il->mutex);
	D_INFO("station %pM\n", sta->addr);
	sta_priv->common.sta_id = IL_INVALID_STATION;

	ret = il_add_station_common(il, sta->addr, is_ap, sta, &sta_id);
	अगर (ret) अणु
		IL_ERR("Unable to add station %pM (%d)\n", sta->addr, ret);
		/* Should we वापस success अगर वापस code is EEXIST ? */
		mutex_unlock(&il->mutex);
		वापस ret;
	पूर्ण

	sta_priv->common.sta_id = sta_id;

	/* Initialize rate scaling */
	D_INFO("Initializing rate scaling for station %pM\n", sta->addr);
	il3945_rs_rate_init(il, sta, sta_id);
	mutex_unlock(&il->mutex);

	वापस 0;
पूर्ण

अटल व्योम
il3945_configure_filter(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक changed_flags,
			अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा il_priv *il = hw->priv;
	__le32 filter_or = 0, filter_nand = 0;

#घोषणा CHK(test, flag)	करो अणु \
	अगर (*total_flags & (test))		\
		filter_or |= (flag);		\
	अन्यथा					\
		filter_nand |= (flag);		\
	पूर्ण जबतक (0)

	D_MAC80211("Enter: changed: 0x%x, total: 0x%x\n", changed_flags,
		   *total_flags);

	CHK(FIF_OTHER_BSS, RXON_FILTER_PROMISC_MSK);
	CHK(FIF_CONTROL, RXON_FILTER_CTL2HOST_MSK);
	CHK(FIF_BCN_PRBRESP_PROMISC, RXON_FILTER_BCON_AWARE_MSK);

#अघोषित CHK

	mutex_lock(&il->mutex);

	il->staging.filter_flags &= ~filter_nand;
	il->staging.filter_flags |= filter_or;

	/*
	 * Not committing directly because hardware can perक्रमm a scan,
	 * but even अगर hw is पढ़ोy, committing here अवरोधs क्रम some reason,
	 * we'll eventually commit the filter flags change anyway.
	 */

	mutex_unlock(&il->mutex);

	/*
	 * Receiving all multicast frames is always enabled by the
	 * शेष flags setup in il_connection_init_rx_config()
	 * since we currently करो not support programming multicast
	 * filters पूर्णांकo the device.
	 */
	*total_flags &=
	    FIF_OTHER_BSS | FIF_ALLMULTI |
	    FIF_BCN_PRBRESP_PROMISC | FIF_CONTROL;
पूर्ण

/*****************************************************************************
 *
 * sysfs attributes
 *
 *****************************************************************************/

#अगर_घोषित CONFIG_IWLEGACY_DEBUG

/*
 * The following adds a new attribute to the sysfs representation
 * of this device driver (i.e. a new file in /sys/bus/pci/drivers/iwl/)
 * used क्रम controlling the debug level.
 *
 * See the level definitions in iwl क्रम details.
 *
 * The debug_level being managed using sysfs below is a per device debug
 * level that is used instead of the global debug level अगर it (the per
 * device debug level) is set.
 */
अटल sमाप_प्रकार
il3945_show_debug_level(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%08X\n", il_get_debug_level(il));
पूर्ण

अटल sमाप_प्रकार
il3945_store_debug_level(काष्ठा device *d, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		IL_INFO("%s is not in hex or decimal form.\n", buf);
	अन्यथा
		il->debug_level = val;

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(debug_level, 0644, il3945_show_debug_level,
		   il3945_store_debug_level);

#पूर्ण_अगर /* CONFIG_IWLEGACY_DEBUG */

अटल sमाप_प्रकार
il3945_show_temperature(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);

	अगर (!il_is_alive(il))
		वापस -EAGAIN;

	वापस प्र_लिखो(buf, "%d\n", il3945_hw_get_temperature(il));
पूर्ण

अटल DEVICE_ATTR(temperature, 0444, il3945_show_temperature, शून्य);

अटल sमाप_प्रकार
il3945_show_tx_घातer(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "%d\n", il->tx_घातer_user_lmt);
पूर्ण

अटल sमाप_प्रकार
il3945_store_tx_घातer(काष्ठा device *d, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	अक्षर *p = (अक्षर *)buf;
	u32 val;

	val = simple_म_से_अदीर्घ(p, &p, 10);
	अगर (p == buf)
		IL_INFO(": %s is not in decimal form.\n", buf);
	अन्यथा
		il3945_hw_reg_set_txघातer(il, val);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(tx_घातer, 0644, il3945_show_tx_घातer, il3945_store_tx_घातer);

अटल sमाप_प्रकार
il3945_show_flags(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);

	वापस प्र_लिखो(buf, "0x%04X\n", il->active.flags);
पूर्ण

अटल sमाप_प्रकार
il3945_store_flags(काष्ठा device *d, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	u32 flags = simple_म_से_अदीर्घ(buf, शून्य, 0);

	mutex_lock(&il->mutex);
	अगर (le32_to_cpu(il->staging.flags) != flags) अणु
		/* Cancel any currently running scans... */
		अगर (il_scan_cancel_समयout(il, 100))
			IL_WARN("Could not cancel scan.\n");
		अन्यथा अणु
			D_INFO("Committing rxon.flags = 0x%04X\n", flags);
			il->staging.flags = cpu_to_le32(flags);
			il3945_commit_rxon(il);
		पूर्ण
	पूर्ण
	mutex_unlock(&il->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(flags, 0644, il3945_show_flags, il3945_store_flags);

अटल sमाप_प्रकार
il3945_show_filter_flags(काष्ठा device *d, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);

	वापस प्र_लिखो(buf, "0x%04X\n", le32_to_cpu(il->active.filter_flags));
पूर्ण

अटल sमाप_प्रकार
il3945_store_filter_flags(काष्ठा device *d, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	u32 filter_flags = simple_म_से_अदीर्घ(buf, शून्य, 0);

	mutex_lock(&il->mutex);
	अगर (le32_to_cpu(il->staging.filter_flags) != filter_flags) अणु
		/* Cancel any currently running scans... */
		अगर (il_scan_cancel_समयout(il, 100))
			IL_WARN("Could not cancel scan.\n");
		अन्यथा अणु
			D_INFO("Committing rxon.filter_flags = " "0x%04X\n",
			       filter_flags);
			il->staging.filter_flags = cpu_to_le32(filter_flags);
			il3945_commit_rxon(il);
		पूर्ण
	पूर्ण
	mutex_unlock(&il->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(filter_flags, 0644, il3945_show_filter_flags,
		   il3945_store_filter_flags);

अटल sमाप_प्रकार
il3945_show_measurement(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	काष्ठा il_spectrum_notअगरication measure_report;
	u32 size = माप(measure_report), len = 0, ofs = 0;
	u8 *data = (u8 *) &measure_report;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&il->lock, flags);
	अगर (!(il->measurement_status & MEASUREMENT_READY)) अणु
		spin_unlock_irqrestore(&il->lock, flags);
		वापस 0;
	पूर्ण
	स_नकल(&measure_report, &il->measure_report, size);
	il->measurement_status = 0;
	spin_unlock_irqrestore(&il->lock, flags);

	जबतक (size && PAGE_SIZE - len) अणु
		hex_dump_to_buffer(data + ofs, size, 16, 1, buf + len,
				   PAGE_SIZE - len, true);
		len = म_माप(buf);
		अगर (PAGE_SIZE - len)
			buf[len++] = '\n';

		ofs += 16;
		size -= min(size, 16U);
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार
il3945_store_measurement(काष्ठा device *d, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	काष्ठा ieee80211_measurement_params params = अणु
		.channel = le16_to_cpu(il->active.channel),
		.start_समय = cpu_to_le64(il->_3945.last_tsf),
		.duration = cpu_to_le16(1),
	पूर्ण;
	u8 type = IL_MEASURE_BASIC;
	u8 buffer[32];
	u8 channel;

	अगर (count) अणु
		अक्षर *p = buffer;
		strlcpy(buffer, buf, माप(buffer));
		channel = simple_म_से_अदीर्घ(p, शून्य, 0);
		अगर (channel)
			params.channel = channel;

		p = buffer;
		जबतक (*p && *p != ' ')
			p++;
		अगर (*p)
			type = simple_म_से_अदीर्घ(p + 1, शून्य, 0);
	पूर्ण

	D_INFO("Invoking measurement of type %d on " "channel %d (for '%s')\n",
	       type, params.channel, buf);
	il3945_get_measurement(il, &params, type);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(measurement, 0600, il3945_show_measurement,
		   il3945_store_measurement);

अटल sमाप_प्रकार
il3945_store_retry_rate(काष्ठा device *d, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);

	il->retry_rate = simple_म_से_अदीर्घ(buf, शून्य, 0);
	अगर (il->retry_rate <= 0)
		il->retry_rate = 1;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
il3945_show_retry_rate(काष्ठा device *d, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "%d", il->retry_rate);
पूर्ण

अटल DEVICE_ATTR(retry_rate, 0600, il3945_show_retry_rate,
		   il3945_store_retry_rate);

अटल sमाप_प्रकार
il3945_show_channels(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	/* all this shit करोesn't beदीर्घ पूर्णांकo sysfs anyway */
	वापस 0;
पूर्ण

अटल DEVICE_ATTR(channels, 0400, il3945_show_channels, शून्य);

अटल sमाप_प्रकार
il3945_show_antenna(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);

	अगर (!il_is_alive(il))
		वापस -EAGAIN;

	वापस प्र_लिखो(buf, "%d\n", il3945_mod_params.antenna);
पूर्ण

अटल sमाप_प्रकार
il3945_store_antenna(काष्ठा device *d, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il __maybe_unused = dev_get_drvdata(d);
	पूर्णांक ant;

	अगर (count == 0)
		वापस 0;

	अगर (माला_पूछो(buf, "%1i", &ant) != 1) अणु
		D_INFO("not in hex or decimal form.\n");
		वापस count;
	पूर्ण

	अगर (ant >= 0 && ant <= 2) अणु
		D_INFO("Setting antenna select to %d.\n", ant);
		il3945_mod_params.antenna = (क्रमागत il3945_antenna)ant;
	पूर्ण अन्यथा
		D_INFO("Bad antenna select value %d.\n", ant);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(antenna, 0644, il3945_show_antenna, il3945_store_antenna);

अटल sमाप_प्रकार
il3945_show_status(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	अगर (!il_is_alive(il))
		वापस -EAGAIN;
	वापस प्र_लिखो(buf, "0x%08x\n", (पूर्णांक)il->status);
पूर्ण

अटल DEVICE_ATTR(status, 0444, il3945_show_status, शून्य);

अटल sमाप_प्रकार
il3945_dump_error_log(काष्ठा device *d, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	अक्षर *p = (अक्षर *)buf;

	अगर (p[0] == '1')
		il3945_dump_nic_error_log(il);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(dump_errors, 0200, शून्य, il3945_dump_error_log);

/*****************************************************************************
 *
 * driver setup and tear करोwn
 *
 *****************************************************************************/

अटल व्योम
il3945_setup_deferred_work(काष्ठा il_priv *il)
अणु
	il->workqueue = create_singlethपढ़ो_workqueue(DRV_NAME);

	init_रुकोqueue_head(&il->रुको_command_queue);

	INIT_WORK(&il->restart, il3945_bg_restart);
	INIT_WORK(&il->rx_replenish, il3945_bg_rx_replenish);
	INIT_DELAYED_WORK(&il->init_alive_start, il3945_bg_init_alive_start);
	INIT_DELAYED_WORK(&il->alive_start, il3945_bg_alive_start);
	INIT_DELAYED_WORK(&il->_3945.rfसमाप्त_poll, il3945_rfसमाप्त_poll);

	il_setup_scan_deferred_work(il);

	il3945_hw_setup_deferred_work(il);

	समयr_setup(&il->watchकरोg, il_bg_watchकरोg, 0);

	tasklet_setup(&il->irq_tasklet, il3945_irq_tasklet);
पूर्ण

अटल व्योम
il3945_cancel_deferred_work(काष्ठा il_priv *il)
अणु
	il3945_hw_cancel_deferred_work(il);

	cancel_delayed_work_sync(&il->init_alive_start);
	cancel_delayed_work(&il->alive_start);

	il_cancel_scan_deferred_work(il);
पूर्ण

अटल काष्ठा attribute *il3945_sysfs_entries[] = अणु
	&dev_attr_antenna.attr,
	&dev_attr_channels.attr,
	&dev_attr_dump_errors.attr,
	&dev_attr_flags.attr,
	&dev_attr_filter_flags.attr,
	&dev_attr_measurement.attr,
	&dev_attr_retry_rate.attr,
	&dev_attr_status.attr,
	&dev_attr_temperature.attr,
	&dev_attr_tx_घातer.attr,
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	&dev_attr_debug_level.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group il3945_attribute_group = अणु
	.name = शून्य,		/* put in device directory */
	.attrs = il3945_sysfs_entries,
पूर्ण;

अटल काष्ठा ieee80211_ops il3945_mac_ops __ro_after_init = अणु
	.tx = il3945_mac_tx,
	.start = il3945_mac_start,
	.stop = il3945_mac_stop,
	.add_पूर्णांकerface = il_mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = il_mac_हटाओ_पूर्णांकerface,
	.change_पूर्णांकerface = il_mac_change_पूर्णांकerface,
	.config = il_mac_config,
	.configure_filter = il3945_configure_filter,
	.set_key = il3945_mac_set_key,
	.conf_tx = il_mac_conf_tx,
	.reset_tsf = il_mac_reset_tsf,
	.bss_info_changed = il_mac_bss_info_changed,
	.hw_scan = il_mac_hw_scan,
	.sta_add = il3945_mac_sta_add,
	.sta_हटाओ = il_mac_sta_हटाओ,
	.tx_last_beacon = il_mac_tx_last_beacon,
	.flush = il_mac_flush,
पूर्ण;

अटल पूर्णांक
il3945_init_drv(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;

	il->retry_rate = 1;
	il->beacon_skb = शून्य;

	spin_lock_init(&il->sta_lock);
	spin_lock_init(&il->hcmd_lock);

	INIT_LIST_HEAD(&il->मुक्त_frames);

	mutex_init(&il->mutex);

	il->ieee_channels = शून्य;
	il->ieee_rates = शून्य;
	il->band = NL80211_BAND_2GHZ;

	il->iw_mode = NL80211_IFTYPE_STATION;
	il->missed_beacon_threshold = IL_MISSED_BEACON_THRESHOLD_DEF;

	/* initialize क्रमce reset */
	il->क्रमce_reset.reset_duration = IL_DELAY_NEXT_FORCE_FW_RELOAD;

	अगर (eeprom->version < EEPROM_3945_EEPROM_VERSION) अणु
		IL_WARN("Unsupported EEPROM version: 0x%04X\n",
			eeprom->version);
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	ret = il_init_channel_map(il);
	अगर (ret) अणु
		IL_ERR("initializing regulatory failed: %d\n", ret);
		जाओ err;
	पूर्ण

	/* Set up txघातer settings in driver क्रम all channels */
	अगर (il3945_txघातer_set_from_eeprom(il)) अणु
		ret = -EIO;
		जाओ err_मुक्त_channel_map;
	पूर्ण

	ret = il_init_geos(il);
	अगर (ret) अणु
		IL_ERR("initializing geos failed: %d\n", ret);
		जाओ err_मुक्त_channel_map;
	पूर्ण
	il3945_init_hw_rates(il, il->ieee_rates);

	वापस 0;

err_मुक्त_channel_map:
	il_मुक्त_channel_map(il);
err:
	वापस ret;
पूर्ण

#घोषणा IL3945_MAX_PROBE_REQUEST	200

अटल पूर्णांक
il3945_setup_mac(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;
	काष्ठा ieee80211_hw *hw = il->hw;

	hw->rate_control_algorithm = "iwl-3945-rs";
	hw->sta_data_size = माप(काष्ठा il3945_sta_priv);
	hw->vअगर_data_size = माप(काष्ठा il_vअगर_priv);

	/* Tell mac80211 our अक्षरacteristics */
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, SPECTRUM_MGMT);

	hw->wiphy->पूर्णांकerface_modes =
	    BIT(NL80211_IFTYPE_STATION) | BIT(NL80211_IFTYPE_ADHOC);

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	hw->wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
				       REGULATORY_DISABLE_BEACON_HINTS;

	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->max_scan_ssids = PROBE_OPTION_MAX_3945;
	/* we create the 802.11 header and a zero-length SSID element */
	hw->wiphy->max_scan_ie_len = IL3945_MAX_PROBE_REQUEST - 24 - 2;

	/* Default value; 4 EDCA QOS priorities */
	hw->queues = 4;

	अगर (il->bands[NL80211_BAND_2GHZ].n_channels)
		il->hw->wiphy->bands[NL80211_BAND_2GHZ] =
		    &il->bands[NL80211_BAND_2GHZ];

	अगर (il->bands[NL80211_BAND_5GHZ].n_channels)
		il->hw->wiphy->bands[NL80211_BAND_5GHZ] =
		    &il->bands[NL80211_BAND_5GHZ];

	il_leds_init(il);

	wiphy_ext_feature_set(il->hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	ret = ieee80211_रेजिस्टर_hw(il->hw);
	अगर (ret) अणु
		IL_ERR("Failed to register hw (error %d)\n", ret);
		वापस ret;
	पूर्ण
	il->mac80211_रेजिस्टरed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
il3945_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = 0;
	काष्ठा il_priv *il;
	काष्ठा ieee80211_hw *hw;
	काष्ठा il_cfg *cfg = (काष्ठा il_cfg *)(ent->driver_data);
	काष्ठा il3945_eeprom *eeprom;
	अचिन्हित दीर्घ flags;

	/***********************
	 * 1. Allocating HW data
	 * ********************/

	hw = ieee80211_alloc_hw(माप(काष्ठा il_priv), &il3945_mac_ops);
	अगर (!hw) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	il = hw->priv;
	il->hw = hw;
	SET_IEEE80211_DEV(hw, &pdev->dev);

	il->cmd_queue = IL39_CMD_QUEUE_NUM;

	D_INFO("*** LOAD DRIVER ***\n");
	il->cfg = cfg;
	il->ops = &il3945_ops;
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	il->debugfs_ops = &il3945_debugfs_ops;
#पूर्ण_अगर
	il->pci_dev = pdev;
	il->पूर्णांकa_mask = CSR_INI_SET_MASK;

	/***************************
	 * 2. Initializing PCI bus
	 * *************************/
	pci_disable_link_state(pdev,
			       PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
			       PCIE_LINK_STATE_CLKPM);

	अगर (pci_enable_device(pdev)) अणु
		err = -ENODEV;
		जाओ out_ieee80211_मुक्त_hw;
	पूर्ण

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (!err)
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (err) अणु
		IL_WARN("No suitable DMA available.\n");
		जाओ out_pci_disable_device;
	पूर्ण

	pci_set_drvdata(pdev, il);
	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err)
		जाओ out_pci_disable_device;

	/***********************
	 * 3. Read REV Register
	 * ********************/
	il->hw_base = pci_ioremap_bar(pdev, 0);
	अगर (!il->hw_base) अणु
		err = -ENODEV;
		जाओ out_pci_release_regions;
	पूर्ण

	D_INFO("pci_resource_len = 0x%08llx\n",
	       (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 0));
	D_INFO("pci_resource_base = %p\n", il->hw_base);

	/* We disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state */
	pci_ग_लिखो_config_byte(pdev, 0x41, 0x00);

	/* these spin locks will be used in apm_init and EEPROM access
	 * we should init now
	 */
	spin_lock_init(&il->reg_lock);
	spin_lock_init(&il->lock);

	/*
	 * stop and reset the on-board processor just in हाल it is in a
	 * strange state ... like being left stअक्रमed by a primary kernel
	 * and this is now the kdump kernel trying to start up
	 */
	_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_NEVO_RESET);

	/***********************
	 * 4. Read EEPROM
	 * ********************/

	/* Read the EEPROM */
	err = il_eeprom_init(il);
	अगर (err) अणु
		IL_ERR("Unable to init EEPROM\n");
		जाओ out_iounmap;
	पूर्ण
	/* MAC Address location in EEPROM same क्रम 3945/4965 */
	eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	D_INFO("MAC address: %pM\n", eeprom->mac_address);
	SET_IEEE80211_PERM_ADDR(il->hw, eeprom->mac_address);

	/***********************
	 * 5. Setup HW Constants
	 * ********************/
	/* Device-specअगरic setup */
	err = il3945_hw_set_hw_params(il);
	अगर (err) अणु
		IL_ERR("failed to set hw settings\n");
		जाओ out_eeprom_मुक्त;
	पूर्ण

	/***********************
	 * 6. Setup il
	 * ********************/

	err = il3945_init_drv(il);
	अगर (err) अणु
		IL_ERR("initializing driver failed\n");
		जाओ out_unset_hw_params;
	पूर्ण

	IL_INFO("Detected Intel Wireless WiFi Link %s\n", il->cfg->name);

	/***********************
	 * 7. Setup Services
	 * ********************/

	spin_lock_irqsave(&il->lock, flags);
	il_disable_पूर्णांकerrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	pci_enable_msi(il->pci_dev);

	err = request_irq(il->pci_dev->irq, il_isr, IRQF_SHARED, DRV_NAME, il);
	अगर (err) अणु
		IL_ERR("Error allocating IRQ %d\n", il->pci_dev->irq);
		जाओ out_disable_msi;
	पूर्ण

	err = sysfs_create_group(&pdev->dev.kobj, &il3945_attribute_group);
	अगर (err) अणु
		IL_ERR("failed to create sysfs device attributes\n");
		जाओ out_release_irq;
	पूर्ण

	il_set_rxon_channel(il, &il->bands[NL80211_BAND_2GHZ].channels[5]);
	il3945_setup_deferred_work(il);
	il3945_setup_handlers(il);
	il_घातer_initialize(il);

	/*********************************
	 * 8. Setup and Register mac80211
	 * *******************************/

	il_enable_पूर्णांकerrupts(il);

	err = il3945_setup_mac(il);
	अगर (err)
		जाओ out_हटाओ_sysfs;

	il_dbgfs_रेजिस्टर(il, DRV_NAME);

	/* Start monitoring the समाप्तचयन */
	queue_delayed_work(il->workqueue, &il->_3945.rfसमाप्त_poll, 2 * HZ);

	वापस 0;

out_हटाओ_sysfs:
	destroy_workqueue(il->workqueue);
	il->workqueue = शून्य;
	sysfs_हटाओ_group(&pdev->dev.kobj, &il3945_attribute_group);
out_release_irq:
	मुक्त_irq(il->pci_dev->irq, il);
out_disable_msi:
	pci_disable_msi(il->pci_dev);
	il_मुक्त_geos(il);
	il_मुक्त_channel_map(il);
out_unset_hw_params:
	il3945_unset_hw_params(il);
out_eeprom_मुक्त:
	il_eeprom_मुक्त(il);
out_iounmap:
	iounmap(il->hw_base);
out_pci_release_regions:
	pci_release_regions(pdev);
out_pci_disable_device:
	pci_disable_device(pdev);
out_ieee80211_मुक्त_hw:
	ieee80211_मुक्त_hw(il->hw);
out:
	वापस err;
पूर्ण

अटल व्योम
il3945_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा il_priv *il = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	अगर (!il)
		वापस;

	D_INFO("*** UNLOAD DRIVER ***\n");

	il_dbgfs_unरेजिस्टर(il);

	set_bit(S_EXIT_PENDING, &il->status);

	il_leds_निकास(il);

	अगर (il->mac80211_रेजिस्टरed) अणु
		ieee80211_unरेजिस्टर_hw(il->hw);
		il->mac80211_रेजिस्टरed = 0;
	पूर्ण अन्यथा अणु
		il3945_करोwn(il);
	पूर्ण

	/*
	 * Make sure device is reset to low घातer beक्रमe unloading driver.
	 * This may be redundant with il_करोwn(), but there are paths to
	 * run il_करोwn() without calling apm_ops.stop(), and there are
	 * paths to aव्योम running il_करोwn() at all beक्रमe leaving driver.
	 * This (inexpensive) call *makes sure* device is reset.
	 */
	il_apm_stop(il);

	/* make sure we flush any pending irq or
	 * tasklet क्रम the driver
	 */
	spin_lock_irqsave(&il->lock, flags);
	il_disable_पूर्णांकerrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	il3945_synchronize_irq(il);

	sysfs_हटाओ_group(&pdev->dev.kobj, &il3945_attribute_group);

	cancel_delayed_work_sync(&il->_3945.rfसमाप्त_poll);

	il3945_dealloc_ucode_pci(il);

	अगर (il->rxq.bd)
		il3945_rx_queue_मुक्त(il, &il->rxq);
	il3945_hw_txq_ctx_मुक्त(il);

	il3945_unset_hw_params(il);

	/*netअगर_stop_queue(dev); */
	flush_workqueue(il->workqueue);

	/* ieee80211_unरेजिस्टर_hw calls il3945_mac_stop, which flushes
	 * il->workqueue... so we can't take करोwn the workqueue
	 * until now... */
	destroy_workqueue(il->workqueue);
	il->workqueue = शून्य;

	मुक्त_irq(pdev->irq, il);
	pci_disable_msi(pdev);

	iounmap(il->hw_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	il_मुक्त_channel_map(il);
	il_मुक्त_geos(il);
	kमुक्त(il->scan_cmd);
	dev_kमुक्त_skb(il->beacon_skb);
	ieee80211_मुक्त_hw(il->hw);
पूर्ण

/*****************************************************************************
 *
 * driver and module entry poपूर्णांक
 *
 *****************************************************************************/

अटल काष्ठा pci_driver il3945_driver = अणु
	.name = DRV_NAME,
	.id_table = il3945_hw_card_ids,
	.probe = il3945_pci_probe,
	.हटाओ = il3945_pci_हटाओ,
	.driver.pm = IL_LEGACY_PM_OPS,
पूर्ण;

अटल पूर्णांक __init
il3945_init(व्योम)
अणु

	पूर्णांक ret;
	pr_info(DRV_DESCRIPTION ", " DRV_VERSION "\n");
	pr_info(DRV_COPYRIGHT "\n");

	/*
	 * Disabling hardware scan means that mac80211 will perक्रमm scans
	 * "the hard way", rather than using device's scan.
	 */
	अगर (il3945_mod_params.disable_hw_scan) अणु
		pr_info("hw_scan is disabled\n");
		il3945_mac_ops.hw_scan = शून्य;
	पूर्ण

	ret = il3945_rate_control_रेजिस्टर();
	अगर (ret) अणु
		pr_err("Unable to register rate control algorithm: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pci_रेजिस्टर_driver(&il3945_driver);
	अगर (ret) अणु
		pr_err("Unable to initialize PCI module\n");
		जाओ error_रेजिस्टर;
	पूर्ण

	वापस ret;

error_रेजिस्टर:
	il3945_rate_control_unरेजिस्टर();
	वापस ret;
पूर्ण

अटल व्योम __निकास
il3945_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&il3945_driver);
	il3945_rate_control_unरेजिस्टर();
पूर्ण

MODULE_FIRMWARE(IL3945_MODULE_FIRMWARE(IL3945_UCODE_API_MAX));

module_param_named(antenna, il3945_mod_params.antenna, पूर्णांक, 0444);
MODULE_PARM_DESC(antenna, "select antenna (1=Main, 2=Aux, default 0 [both])");
module_param_named(swcrypto, il3945_mod_params.sw_crypto, पूर्णांक, 0444);
MODULE_PARM_DESC(swcrypto, "using software crypto (default 1 [software])");
module_param_named(disable_hw_scan, il3945_mod_params.disable_hw_scan, पूर्णांक,
		   0444);
MODULE_PARM_DESC(disable_hw_scan, "disable hardware scanning (default 1)");
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
module_param_named(debug, il_debug_level, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug output mask");
#पूर्ण_अगर
module_param_named(fw_restart, il3945_mod_params.restart_fw, पूर्णांक, 0444);
MODULE_PARM_DESC(fw_restart, "restart firmware in case of error");

module_निकास(il3945_निकास);
module_init(il3945_init);
