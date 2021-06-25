<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11n Aggregation
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

#अगर_अघोषित _MWIFIEX_11N_AGGR_H_
#घोषणा _MWIFIEX_11N_AGGR_H_

#घोषणा PKT_TYPE_AMSDU	0xE6
#घोषणा MIN_NUM_AMSDU 2

पूर्णांक mwअगरiex_11n_deaggregate_pkt(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_11n_aggregate_pkt(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_ra_list_tbl *ptr,
			      पूर्णांक ptr_index)
			      __releases(&priv->wmm.ra_list_spinlock);

#पूर्ण_अगर /* !_MWIFIEX_11N_AGGR_H_ */
