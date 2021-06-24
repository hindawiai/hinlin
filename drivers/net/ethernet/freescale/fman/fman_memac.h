<शैली गुरु>
/*
 * Copyright 2008-2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
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

#अगर_अघोषित __MEMAC_H
#घोषणा __MEMAC_H

#समावेश "fman_mac.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/phy_fixed.h>

काष्ठा fman_mac *memac_config(काष्ठा fman_mac_params *params);
पूर्णांक memac_set_promiscuous(काष्ठा fman_mac *memac, bool new_val);
पूर्णांक memac_modअगरy_mac_address(काष्ठा fman_mac *memac, enet_addr_t *enet_addr);
पूर्णांक memac_adjust_link(काष्ठा fman_mac *memac, u16 speed);
पूर्णांक memac_cfg_max_frame_len(काष्ठा fman_mac *memac, u16 new_val);
पूर्णांक memac_cfg_reset_on_init(काष्ठा fman_mac *memac, bool enable);
पूर्णांक memac_cfg_fixed_link(काष्ठा fman_mac *memac,
			 काष्ठा fixed_phy_status *fixed_link);
पूर्णांक memac_enable(काष्ठा fman_mac *memac, क्रमागत comm_mode mode);
पूर्णांक memac_disable(काष्ठा fman_mac *memac, क्रमागत comm_mode mode);
पूर्णांक memac_init(काष्ठा fman_mac *memac);
पूर्णांक memac_मुक्त(काष्ठा fman_mac *memac);
पूर्णांक memac_accept_rx_छोड़ो_frames(काष्ठा fman_mac *memac, bool en);
पूर्णांक memac_set_tx_छोड़ो_frames(काष्ठा fman_mac *memac, u8 priority,
			      u16 छोड़ो_समय, u16 thresh_समय);
पूर्णांक memac_set_exception(काष्ठा fman_mac *memac,
			क्रमागत fman_mac_exceptions exception, bool enable);
पूर्णांक memac_add_hash_mac_address(काष्ठा fman_mac *memac, enet_addr_t *eth_addr);
पूर्णांक memac_del_hash_mac_address(काष्ठा fman_mac *memac, enet_addr_t *eth_addr);
पूर्णांक memac_set_allmulti(काष्ठा fman_mac *memac, bool enable);
पूर्णांक memac_set_tstamp(काष्ठा fman_mac *memac, bool enable);

#पूर्ण_अगर /* __MEMAC_H */
