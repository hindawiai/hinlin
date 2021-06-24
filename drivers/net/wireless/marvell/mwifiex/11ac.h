<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11ac
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित _MWIFIEX_11AC_H_
#घोषणा _MWIFIEX_11AC_H_

#घोषणा VHT_CFG_2GHZ BIT(0)
#घोषणा VHT_CFG_5GHZ BIT(1)

क्रमागत vht_cfg_misc_config अणु
	VHT_CAP_TX_OPERATION = 1,
	VHT_CAP_ASSOCIATION,
	VHT_CAP_UAP_ONLY
पूर्ण;

#घोषणा DEFAULT_VHT_MCS_SET 0xfffa
#घोषणा DISABLE_VHT_MCS_SET 0xffff

#घोषणा VHT_BW_80_160_80P80 BIT(2)

पूर्णांक mwअगरiex_cmd_append_11ac_tlv(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा mwअगरiex_bssdescriptor *bss_desc,
				u8 **buffer);
पूर्णांक mwअगरiex_cmd_11ac_cfg(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा host_cmd_ds_command *cmd, u16 cmd_action,
			 काष्ठा mwअगरiex_11ac_vht_cfg *cfg);
व्योम mwअगरiex_fill_vht_cap_tlv(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा ieee80211_vht_cap *vht_cap, u8 bands);
#पूर्ण_अगर /* _MWIFIEX_11AC_H_ */
