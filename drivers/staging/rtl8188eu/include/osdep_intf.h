<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित __OSDEP_INTF_H_
#घोषणा __OSDEP_INTF_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

बाह्य अक्षर *rtw_iniपंचांगac;
बाह्य पूर्णांक rtw_mc2u_disable;

u8 rtw_init_drv_sw(काष्ठा adapter *padapter);
u8 rtw_मुक्त_drv_sw(काष्ठा adapter *padapter);
u8 rtw_reset_drv_sw(काष्ठा adapter *padapter);

व्योम rtw_stop_drv_thपढ़ोs(काष्ठा adapter *padapter);
व्योम rtw_cancel_all_समयr(काष्ठा adapter *padapter);

पूर्णांक rtw_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);

काष्ठा net_device *rtw_init_netdev(व्योम);
u16 rtw_recv_select_queue(काष्ठा sk_buff *skb);

पूर्णांक netdev_खोलो(काष्ठा net_device *pnetdev);
पूर्णांक ips_netdrv_खोलो(काष्ठा adapter *padapter);
व्योम rtw_ips_dev_unload(काष्ठा adapter *padapter);
पूर्णांक rtw_ips_pwr_up(काष्ठा adapter *padapter);
व्योम rtw_ips_pwr_करोwn(काष्ठा adapter *padapter);

#पूर्ण_अगर	/* _OSDEP_INTF_H_ */
