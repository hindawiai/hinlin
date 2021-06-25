<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित __OSDEP_INTF_H_
#घोषणा __OSDEP_INTF_H_


काष्ठा पूर्णांकf_priv अणु

	u8 *पूर्णांकf_dev;
	u32 max_iosz;	/* USB2.0: 128, USB1.1: 64, SDIO:64 */
	u32 max_xmitsz; /* USB2.0: unlimited, SDIO:512 */
	u32 max_recvsz; /* USB2.0: unlimited, SDIO:512 */

	अस्थिर u8 *io_rwmem;
	अस्थिर u8 *allocated_io_rwmem;
	u32 io_wsz; /* unit: 4bytes */
	u32 io_rsz;/* unit: 4bytes */
	u8 पूर्णांकf_status;

	व्योम (*_bus_io)(u8 *priv);

/*
Under Sync. IRP (SDIO/USB)
A protection mechanism is necessary क्रम the io_rwmem(पढ़ो/ग_लिखो protocol)

Under Async. IRP (SDIO/USB)
The protection mechanism is through the pending queue.
*/

	काष्ठा mutex ioctl_mutex;
पूर्ण;

काष्ठा dvobj_priv *devobj_init(व्योम);
व्योम devobj_deinit(काष्ठा dvobj_priv *pdvobj);

u8 rtw_init_drv_sw(काष्ठा adapter *padapter);
u8 rtw_मुक्त_drv_sw(काष्ठा adapter *padapter);
व्योम rtw_reset_drv_sw(काष्ठा adapter *padapter);
व्योम rtw_dev_unload(काष्ठा adapter *padapter);

u32 rtw_start_drv_thपढ़ोs(काष्ठा adapter *padapter);
व्योम rtw_stop_drv_thपढ़ोs(काष्ठा adapter *padapter);
व्योम rtw_cancel_all_समयr(काष्ठा adapter *padapter);

पूर्णांक rtw_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);

पूर्णांक rtw_init_netdev_name(काष्ठा net_device *pnetdev, स्थिर अक्षर *अगरname);
काष्ठा net_device *rtw_init_netdev(काष्ठा adapter *padapter);
व्योम rtw_unरेजिस्टर_netdevs(काष्ठा dvobj_priv *dvobj);

u16 rtw_recv_select_queue(काष्ठा sk_buff *skb);

पूर्णांक rtw_ndev_notअगरier_रेजिस्टर(व्योम);
व्योम rtw_ndev_notअगरier_unरेजिस्टर(व्योम);

व्योम rtw_ips_dev_unload(काष्ठा adapter *padapter);

पूर्णांक rtw_ips_pwr_up(काष्ठा adapter *padapter);
व्योम rtw_ips_pwr_करोwn(काष्ठा adapter *padapter);

पूर्णांक rtw_drv_रेजिस्टर_netdev(काष्ठा adapter *padapter);
व्योम rtw_ndev_deकाष्ठाor(काष्ठा net_device *ndev);

पूर्णांक rtw_suspend_common(काष्ठा adapter *padapter);
पूर्णांक rtw_resume_common(काष्ठा adapter *padapter);

पूर्णांक netdev_खोलो(काष्ठा net_device *pnetdev);

#पूर्ण_अगर	/* _OSDEP_INTF_H_ */
