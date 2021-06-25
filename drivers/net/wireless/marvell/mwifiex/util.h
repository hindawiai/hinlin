<शैली गुरु>
/*
 * NXP Wireless LAN device driver: utility functions
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

#अगर_अघोषित _MWIFIEX_UTIL_H_
#घोषणा _MWIFIEX_UTIL_H_

काष्ठा mwअगरiex_निजी;

काष्ठा mwअगरiex_dma_mapping अणु
	dma_addr_t addr;
	माप_प्रकार len;
पूर्ण;

काष्ठा mwअगरiex_cb अणु
	काष्ठा mwअगरiex_dma_mapping dma_mapping;
	जोड़ अणु
		काष्ठा mwअगरiex_rxinfo rx_info;
		काष्ठा mwअगरiex_txinfo tx_info;
	पूर्ण;
पूर्ण;

/* size/addr क्रम mwअगरiex_debug_info */
#घोषणा item_size(n)		(माप_field(काष्ठा mwअगरiex_debug_info, n))
#घोषणा item_addr(n)		(दुरत्व(काष्ठा mwअगरiex_debug_info, n))

/* size/addr क्रम काष्ठा mwअगरiex_adapter */
#घोषणा adapter_item_size(n)	(माप_field(काष्ठा mwअगरiex_adapter, n))
#घोषणा adapter_item_addr(n)	(दुरत्व(काष्ठा mwअगरiex_adapter, n))

काष्ठा mwअगरiex_debug_data अणु
	अक्षर name[32];		/* variable/array name */
	u32 size;		/* size of the variable/array */
	माप_प्रकार addr;		/* address of the variable/array */
	पूर्णांक num;		/* number of variables in an array */
पूर्ण;

अटल अंतरभूत काष्ठा mwअगरiex_rxinfo *MWIFIEX_SKB_RXCB(काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_cb *cb = (काष्ठा mwअगरiex_cb *)skb->cb;

	BUILD_BUG_ON(माप(काष्ठा mwअगरiex_cb) > माप(skb->cb));
	वापस &cb->rx_info;
पूर्ण

अटल अंतरभूत काष्ठा mwअगरiex_txinfo *MWIFIEX_SKB_TXCB(काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_cb *cb = (काष्ठा mwअगरiex_cb *)skb->cb;

	वापस &cb->tx_info;
पूर्ण

अटल अंतरभूत व्योम mwअगरiex_store_mapping(काष्ठा sk_buff *skb,
					 काष्ठा mwअगरiex_dma_mapping *mapping)
अणु
	काष्ठा mwअगरiex_cb *cb = (काष्ठा mwअगरiex_cb *)skb->cb;

	स_नकल(&cb->dma_mapping, mapping, माप(*mapping));
पूर्ण

अटल अंतरभूत व्योम mwअगरiex_get_mapping(काष्ठा sk_buff *skb,
				       काष्ठा mwअगरiex_dma_mapping *mapping)
अणु
	काष्ठा mwअगरiex_cb *cb = (काष्ठा mwअगरiex_cb *)skb->cb;

	स_नकल(mapping, &cb->dma_mapping, माप(*mapping));
पूर्ण

अटल अंतरभूत dma_addr_t MWIFIEX_SKB_DMA_ADDR(काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_dma_mapping mapping;

	mwअगरiex_get_mapping(skb, &mapping);

	वापस mapping.addr;
पूर्ण

पूर्णांक mwअगरiex_debug_info_to_buffer(काष्ठा mwअगरiex_निजी *priv, अक्षर *buf,
				 काष्ठा mwअगरiex_debug_info *info);

अटल अंतरभूत व्योम le16_unaligned_add_cpu(__le16 *var, u16 val)
अणु
	put_unaligned_le16(get_unaligned_le16(var) + val, var);
पूर्ण

#पूर्ण_अगर /* !_MWIFIEX_UTIL_H_ */
