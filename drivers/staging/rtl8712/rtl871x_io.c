<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_io.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
/*
 *
 * The purpose of rtl871x_io.c
 *
 * a. provides the API
 * b. provides the protocol engine
 * c. provides the software पूर्णांकerface between caller and the hardware पूर्णांकerface
 *
 * For r8712u, both sync/async operations are provided.
 *
 * Only sync पढ़ो/ग_लिखो_mem operations are provided.
 *
 */

#घोषणा _RTL871X_IO_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "rtl871x_io.h"
#समावेश "osdep_intf.h"
#समावेश "usb_ops.h"

अटल uपूर्णांक _init_पूर्णांकf_hdl(काष्ठा _adapter *padapter,
			   काष्ठा पूर्णांकf_hdl *pपूर्णांकf_hdl)
अणु
	काष्ठा	पूर्णांकf_priv	*pपूर्णांकf_priv;
	व्योम (*set_पूर्णांकf_option)(u32 *poption) = शून्य;
	व्योम (*set_पूर्णांकf_funs)(काष्ठा पूर्णांकf_hdl *pपूर्णांकf_hdl);
	व्योम (*set_पूर्णांकf_ops)(काष्ठा _io_ops	*pops);
	uपूर्णांक (*init_पूर्णांकf_priv)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv);

	set_पूर्णांकf_option = &(r8712_usb_set_पूर्णांकf_option);
	set_पूर्णांकf_funs = &(r8712_usb_set_पूर्णांकf_funs);
	set_पूर्णांकf_ops = &r8712_usb_set_पूर्णांकf_ops;
	init_पूर्णांकf_priv = &r8712_usb_init_पूर्णांकf_priv;
	pपूर्णांकf_priv = pपूर्णांकf_hdl->pपूर्णांकfpriv = kदो_स्मृति(माप(काष्ठा पूर्णांकf_priv),
						    GFP_ATOMIC);
	अगर (!pपूर्णांकf_priv)
		जाओ _init_पूर्णांकf_hdl_fail;
	pपूर्णांकf_hdl->adapter = (u8 *)padapter;
	set_पूर्णांकf_option(&pपूर्णांकf_hdl->पूर्णांकf_option);
	set_पूर्णांकf_funs(pपूर्णांकf_hdl);
	set_पूर्णांकf_ops(&pपूर्णांकf_hdl->io_ops);
	pपूर्णांकf_priv->पूर्णांकf_dev = (u8 *)&padapter->dvobjpriv;
	अगर (init_पूर्णांकf_priv(pपूर्णांकf_priv) == _FAIL)
		जाओ _init_पूर्णांकf_hdl_fail;
	वापस _SUCCESS;
_init_पूर्णांकf_hdl_fail:
	kमुक्त(pपूर्णांकf_priv);
	वापस _FAIL;
पूर्ण

अटल व्योम _unload_पूर्णांकf_hdl(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv)
अणु
	व्योम (*unload_पूर्णांकf_priv)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv);

	unload_पूर्णांकf_priv = &r8712_usb_unload_पूर्णांकf_priv;
	unload_पूर्णांकf_priv(pपूर्णांकfpriv);
	kमुक्त(pपूर्णांकfpriv);
पूर्ण

अटल uपूर्णांक रेजिस्टर_पूर्णांकf_hdl(u8 *dev, काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl)
अणु
	काष्ठा _adapter *adapter = (काष्ठा _adapter *)dev;

	pपूर्णांकfhdl->पूर्णांकf_option = 0;
	pपूर्णांकfhdl->adapter = dev;
	pपूर्णांकfhdl->पूर्णांकf_dev = (u8 *)&adapter->dvobjpriv;
	अगर (!_init_पूर्णांकf_hdl(adapter, pपूर्णांकfhdl))
		जाओ रेजिस्टर_पूर्णांकf_hdl_fail;
	वापस _SUCCESS;
रेजिस्टर_पूर्णांकf_hdl_fail:
	वापस false;
पूर्ण

अटल  व्योम unरेजिस्टर_पूर्णांकf_hdl(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl)
अणु
	_unload_पूर्णांकf_hdl(pपूर्णांकfhdl->pपूर्णांकfpriv);
	स_रखो((u8 *)pपूर्णांकfhdl, 0, माप(काष्ठा पूर्णांकf_hdl));
पूर्ण

uपूर्णांक r8712_alloc_io_queue(काष्ठा _adapter *adapter)
अणु
	u32 i;
	काष्ठा io_queue *pio_queue;
	काष्ठा io_req *pio_req;

	pio_queue = kदो_स्मृति(माप(*pio_queue), GFP_ATOMIC);
	अगर (!pio_queue)
		जाओ alloc_io_queue_fail;
	INIT_LIST_HEAD(&pio_queue->मुक्त_ioreqs);
	INIT_LIST_HEAD(&pio_queue->processing);
	INIT_LIST_HEAD(&pio_queue->pending);
	spin_lock_init(&pio_queue->lock);
	pio_queue->pallocated_मुक्त_ioreqs_buf = kzalloc(NUM_IOREQ *
						(माप(काष्ठा io_req)) + 4,
						GFP_ATOMIC);
	अगर ((pio_queue->pallocated_मुक्त_ioreqs_buf) == शून्य)
		जाओ alloc_io_queue_fail;
	pio_queue->मुक्त_ioreqs_buf = pio_queue->pallocated_मुक्त_ioreqs_buf + 4
			- ((addr_t)(pio_queue->pallocated_मुक्त_ioreqs_buf)
			& 3);
	pio_req = (काष्ठा io_req *)(pio_queue->मुक्त_ioreqs_buf);
	क्रम (i = 0; i < NUM_IOREQ; i++) अणु
		INIT_LIST_HEAD(&pio_req->list);
		list_add_tail(&pio_req->list, &pio_queue->मुक्त_ioreqs);
		pio_req++;
	पूर्ण
	अगर ((रेजिस्टर_पूर्णांकf_hdl((u8 *)adapter, &pio_queue->पूर्णांकf)) == _FAIL)
		जाओ alloc_io_queue_fail;
	adapter->pio_queue = pio_queue;
	वापस _SUCCESS;
alloc_io_queue_fail:
	अगर (pio_queue) अणु
		kमुक्त(pio_queue->pallocated_मुक्त_ioreqs_buf);
		kमुक्त(pio_queue);
	पूर्ण
	adapter->pio_queue = शून्य;
	वापस _FAIL;
पूर्ण

व्योम r8712_मुक्त_io_queue(काष्ठा _adapter *adapter)
अणु
	काष्ठा io_queue *pio_queue = adapter->pio_queue;

	अगर (pio_queue) अणु
		kमुक्त(pio_queue->pallocated_मुक्त_ioreqs_buf);
		adapter->pio_queue = शून्य;
		unरेजिस्टर_पूर्णांकf_hdl(&pio_queue->पूर्णांकf);
		kमुक्त(pio_queue);
	पूर्ण
पूर्ण
