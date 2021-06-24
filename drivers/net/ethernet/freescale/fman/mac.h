<शैली गुरु>
/* Copyright 2008-2015 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __MAC_H
#घोषणा __MAC_H

#समावेश <linux/device.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/phy.h>
#समावेश <linux/list.h>

#समावेश "fman_port.h"
#समावेश "fman.h"
#समावेश "fman_mac.h"

काष्ठा fman_mac;
काष्ठा mac_priv_s;

काष्ठा mac_device अणु
	काष्ठा resource		*res;
	u8			 addr[ETH_ALEN];
	काष्ठा fman_port	*port[2];
	u32			 अगर_support;
	काष्ठा phy_device	*phy_dev;
	phy_पूर्णांकerface_t		phy_अगर;
	काष्ठा device_node	*phy_node;

	bool स्वतःneg_छोड़ो;
	bool rx_छोड़ो_req;
	bool tx_छोड़ो_req;
	bool rx_छोड़ो_active;
	bool tx_छोड़ो_active;
	bool promisc;
	bool allmulti;

	पूर्णांक (*init)(काष्ठा mac_device *mac_dev);
	पूर्णांक (*start)(काष्ठा mac_device *mac_dev);
	पूर्णांक (*stop)(काष्ठा mac_device *mac_dev);
	व्योम (*adjust_link)(काष्ठा mac_device *mac_dev);
	पूर्णांक (*set_promisc)(काष्ठा fman_mac *mac_dev, bool enable);
	पूर्णांक (*change_addr)(काष्ठा fman_mac *mac_dev, enet_addr_t *enet_addr);
	पूर्णांक (*set_allmulti)(काष्ठा fman_mac *mac_dev, bool enable);
	पूर्णांक (*set_tstamp)(काष्ठा fman_mac *mac_dev, bool enable);
	पूर्णांक (*set_multi)(काष्ठा net_device *net_dev,
			 काष्ठा mac_device *mac_dev);
	पूर्णांक (*set_rx_छोड़ो)(काष्ठा fman_mac *mac_dev, bool en);
	पूर्णांक (*set_tx_छोड़ो)(काष्ठा fman_mac *mac_dev, u8 priority,
			    u16 छोड़ो_समय, u16 thresh_समय);
	पूर्णांक (*set_exception)(काष्ठा fman_mac *mac_dev,
			     क्रमागत fman_mac_exceptions exception, bool enable);
	पूर्णांक (*add_hash_mac_addr)(काष्ठा fman_mac *mac_dev,
				 enet_addr_t *eth_addr);
	पूर्णांक (*हटाओ_hash_mac_addr)(काष्ठा fman_mac *mac_dev,
				    enet_addr_t *eth_addr);

	काष्ठा fman_mac		*fman_mac;
	काष्ठा mac_priv_s	*priv;
पूर्ण;

काष्ठा dpaa_eth_data अणु
	काष्ठा mac_device *mac_dev;
	पूर्णांक mac_hw_id;
	पूर्णांक fman_hw_id;
पूर्ण;

बाह्य स्थिर अक्षर	*mac_driver_description;

पूर्णांक fman_set_mac_active_छोड़ो(काष्ठा mac_device *mac_dev, bool rx, bool tx);

व्योम fman_get_छोड़ो_cfg(काष्ठा mac_device *mac_dev, bool *rx_छोड़ो,
			bool *tx_छोड़ो);

#पूर्ण_अगर	/* __MAC_H */
