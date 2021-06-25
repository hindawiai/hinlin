<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/


#घोषणा _OSDEP_SERVICE_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

/*
* Translate the OS dependent @param error_code to OS independent RTW_STATUS_CODE
* @वापस: one of RTW_STATUS_CODE
*/
अंतरभूत पूर्णांक RTW_STATUS_CODE(पूर्णांक error_code)
अणु
	अगर (error_code >= 0)
		वापस _SUCCESS;
	वापस _FAIL;
पूर्ण

व्योम *_rtw_दो_स्मृति(u32 sz)
अणु
	वापस kदो_स्मृति(sz, in_पूर्णांकerrupt() ? GFP_ATOMIC : GFP_KERNEL);
पूर्ण

व्योम *_rtw_zदो_स्मृति(u32 sz)
अणु
	व्योम *pbuf = _rtw_दो_स्मृति(sz);

	अगर (pbuf)
		स_रखो(pbuf, 0, sz);

	वापस pbuf;
पूर्ण

अंतरभूत काष्ठा sk_buff *_rtw_skb_alloc(u32 sz)
अणु
	वापस __dev_alloc_skb(sz, in_पूर्णांकerrupt() ? GFP_ATOMIC : GFP_KERNEL);
पूर्ण

अंतरभूत काष्ठा sk_buff *_rtw_skb_copy(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_copy(skb, in_पूर्णांकerrupt() ? GFP_ATOMIC : GFP_KERNEL);
पूर्ण

अंतरभूत पूर्णांक _rtw_netअगर_rx(काष्ठा net_device *ndev, काष्ठा sk_buff *skb)
अणु
	skb->dev = ndev;
	वापस netअगर_rx(skb);
पूर्ण

व्योम _rtw_init_queue(काष्ठा __queue *pqueue)
अणु
	INIT_LIST_HEAD(&(pqueue->queue));

	spin_lock_init(&(pqueue->lock));
पूर्ण

काष्ठा net_device *rtw_alloc_etherdev_with_old_priv(पूर्णांक माप_priv, व्योम *old_priv)
अणु
	काष्ठा net_device *pnetdev;
	काष्ठा rtw_netdev_priv_indicator *pnpi;

	pnetdev = alloc_etherdev_mq(माप(काष्ठा rtw_netdev_priv_indicator), 4);
	अगर (!pnetdev)
		जाओ RETURN;

	pnpi = netdev_priv(pnetdev);
	pnpi->priv = old_priv;
	pnpi->माप_priv = माप_priv;

RETURN:
	वापस pnetdev;
पूर्ण

काष्ठा net_device *rtw_alloc_etherdev(पूर्णांक माप_priv)
अणु
	काष्ठा net_device *pnetdev;
	काष्ठा rtw_netdev_priv_indicator *pnpi;

	pnetdev = alloc_etherdev_mq(माप(काष्ठा rtw_netdev_priv_indicator), 4);
	अगर (!pnetdev)
		जाओ RETURN;

	pnpi = netdev_priv(pnetdev);

	pnpi->priv = vzalloc(माप_priv);
	अगर (!pnpi->priv) अणु
		मुक्त_netdev(pnetdev);
		pnetdev = शून्य;
		जाओ RETURN;
	पूर्ण

	pnpi->माप_priv = माप_priv;
RETURN:
	वापस pnetdev;
पूर्ण

व्योम rtw_मुक्त_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा rtw_netdev_priv_indicator *pnpi;

	अगर (!netdev)
		जाओ RETURN;

	pnpi = netdev_priv(netdev);

	अगर (!pnpi->priv)
		जाओ RETURN;

	vमुक्त(pnpi->priv);
	मुक्त_netdev(netdev);

RETURN:
	वापस;
पूर्ण

पूर्णांक rtw_change_अगरname(काष्ठा adapter *padapter, स्थिर अक्षर *अगरname)
अणु
	काष्ठा net_device *pnetdev;
	काष्ठा net_device *cur_pnetdev;
	काष्ठा rereg_nd_name_data *rereg_priv;
	पूर्णांक ret;

	अगर (!padapter)
		जाओ error;

	cur_pnetdev = padapter->pnetdev;
	rereg_priv = &padapter->rereg_nd_name_priv;

	/* मुक्त the old_pnetdev */
	अगर (rereg_priv->old_pnetdev) अणु
		मुक्त_netdev(rereg_priv->old_pnetdev);
		rereg_priv->old_pnetdev = शून्य;
	पूर्ण

	अगर (!rtnl_is_locked())
		unरेजिस्टर_netdev(cur_pnetdev);
	अन्यथा
		unरेजिस्टर_netdevice(cur_pnetdev);

	rereg_priv->old_pnetdev = cur_pnetdev;

	pnetdev = rtw_init_netdev(padapter);
	अगर (!pnetdev)
		जाओ error;

	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(adapter_to_dvobj(padapter)));

	rtw_init_netdev_name(pnetdev, अगरname);

	स_नकल(pnetdev->dev_addr, padapter->eeprompriv.mac_addr, ETH_ALEN);

	अगर (!rtnl_is_locked())
		ret = रेजिस्टर_netdev(pnetdev);
	अन्यथा
		ret = रेजिस्टर_netdevice(pnetdev);

	अगर (ret != 0)
		जाओ error;

	वापस 0;

error:
	वापस -1;
पूर्ण

व्योम rtw_buf_मुक्त(u8 **buf, u32 *buf_len)
अणु
	अगर (!buf || !buf_len)
		वापस;

	अगर (*buf) अणु
		*buf_len = 0;
		kमुक्त(*buf);
		*buf = शून्य;
	पूर्ण
पूर्ण

व्योम rtw_buf_update(u8 **buf, u32 *buf_len, u8 *src, u32 src_len)
अणु
	u32 ori_len = 0, dup_len = 0;
	u8 *ori = शून्य;
	u8 *dup = शून्य;

	अगर (!buf || !buf_len)
		वापस;

	अगर (!src || !src_len)
		जाओ keep_ori;

	/* duplicate src */
	dup = rtw_दो_स्मृति(src_len);
	अगर (dup) अणु
		dup_len = src_len;
		स_नकल(dup, src, dup_len);
	पूर्ण

keep_ori:
	ori = *buf;
	ori_len = *buf_len;

	/* replace buf with dup */
	*buf_len = 0;
	*buf = dup;
	*buf_len = dup_len;

	/* मुक्त ori */
	अगर (ori && ori_len > 0)
		kमुक्त(ori);
पूर्ण


/**
 * rtw_cbuf_full - test अगर cbuf is full
 * @cbuf: poपूर्णांकer of काष्ठा rtw_cbuf
 *
 * Returns: true अगर cbuf is full
 */
अंतरभूत bool rtw_cbuf_full(काष्ठा rtw_cbuf *cbuf)
अणु
	वापस (cbuf->ग_लिखो == cbuf->पढ़ो - 1) ? true : false;
पूर्ण

/**
 * rtw_cbuf_empty - test अगर cbuf is empty
 * @cbuf: poपूर्णांकer of काष्ठा rtw_cbuf
 *
 * Returns: true अगर cbuf is empty
 */
अंतरभूत bool rtw_cbuf_empty(काष्ठा rtw_cbuf *cbuf)
अणु
	वापस (cbuf->ग_लिखो == cbuf->पढ़ो) ? true : false;
पूर्ण

/**
 * rtw_cbuf_push - push a poपूर्णांकer पूर्णांकo cbuf
 * @cbuf: poपूर्णांकer of काष्ठा rtw_cbuf
 * @buf: poपूर्णांकer to push in
 *
 * Lock मुक्त operation, be careful of the use scheme
 * Returns: true push success
 */
bool rtw_cbuf_push(काष्ठा rtw_cbuf *cbuf, व्योम *buf)
अणु
	अगर (rtw_cbuf_full(cbuf))
		वापस _FAIL;

	cbuf->bufs[cbuf->ग_लिखो] = buf;
	cbuf->ग_लिखो = (cbuf->ग_लिखो + 1) % cbuf->size;

	वापस _SUCCESS;
पूर्ण

/**
 * rtw_cbuf_pop - pop a poपूर्णांकer from cbuf
 * @cbuf: poपूर्णांकer of काष्ठा rtw_cbuf
 *
 * Lock मुक्त operation, be careful of the use scheme
 * Returns: poपूर्णांकer popped out
 */
व्योम *rtw_cbuf_pop(काष्ठा rtw_cbuf *cbuf)
अणु
	व्योम *buf;
	अगर (rtw_cbuf_empty(cbuf))
		वापस शून्य;

	buf = cbuf->bufs[cbuf->पढ़ो];
	cbuf->पढ़ो = (cbuf->पढ़ो + 1) % cbuf->size;

	वापस buf;
पूर्ण

/**
 * rtw_cbuf_alloc - allocate a rtw_cbuf with given size and करो initialization
 * @size: size of poपूर्णांकer
 *
 * Returns: poपूर्णांकer of srtuct rtw_cbuf, शून्य क्रम allocation failure
 */
काष्ठा rtw_cbuf *rtw_cbuf_alloc(u32 size)
अणु
	काष्ठा rtw_cbuf *cbuf;

	cbuf = rtw_दो_स्मृति(माप(*cbuf) + माप(व्योम *) * size);

	अगर (cbuf) अणु
		cbuf->ग_लिखो = cbuf->पढ़ो = 0;
		cbuf->size = size;
	पूर्ण

	वापस cbuf;
पूर्ण
