<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित _RTL8192E_H
#घोषणा _RTL8192E_H

#समावेश "r8190P_def.h"

bool rtl92e_is_halfn_supported_by_ap(काष्ठा net_device *dev);
bool rtl92e_get_nmode_support_by_sec(काष्ठा net_device *dev);
bool rtl92e_is_tx_stuck(काष्ठा net_device *dev);
bool rtl92e_is_rx_stuck(काष्ठा net_device *dev);
व्योम rtl92e_ack_irq(काष्ठा net_device *dev, u32 *p_पूर्णांकa, u32 *p_पूर्णांकb);
व्योम rtl92e_enable_rx(काष्ठा net_device *dev);
व्योम rtl92e_enable_tx(काष्ठा net_device *dev);
व्योम rtl92e_enable_irq(काष्ठा net_device *dev);
व्योम rtl92e_disable_irq(काष्ठा net_device *dev);
व्योम rtl92e_clear_irq(काष्ठा net_device *dev);
व्योम rtl92e_init_variables(काष्ठा net_device  *dev);
व्योम rtl92e_start_beacon(काष्ठा net_device *dev);
व्योम rtl92e_set_reg(काष्ठा net_device *dev, u8 variable, u8 *val);
व्योम rtl92e_get_eeprom_size(काष्ठा net_device *dev);
bool rtl92e_start_adapter(काष्ठा net_device *dev);
व्योम rtl92e_link_change(काष्ठा net_device *dev);
व्योम rtl92e_set_monitor_mode(काष्ठा net_device *dev, bool bAllowAllDA,
			     bool WriteIntoReg);
व्योम  rtl92e_fill_tx_desc(काष्ठा net_device *dev, काष्ठा tx_desc *pdesc,
			  काष्ठा cb_desc *cb_desc, काष्ठा sk_buff *skb);
व्योम  rtl92e_fill_tx_cmd_desc(काष्ठा net_device *dev, काष्ठा tx_desc_cmd *entry,
			      काष्ठा cb_desc *cb_desc, काष्ठा sk_buff *skb);
bool rtl92e_get_rx_stats(काष्ठा net_device *dev, काष्ठा rtllib_rx_stats *stats,
			 काष्ठा rx_desc *pdesc, काष्ठा sk_buff *skb);
व्योम rtl92e_stop_adapter(काष्ठा net_device *dev, bool reset);
व्योम rtl92e_update_ratr_table(काष्ठा net_device *dev);
#पूर्ण_अगर
