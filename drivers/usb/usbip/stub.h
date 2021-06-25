<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 */

#अगर_अघोषित __USBIP_STUB_H
#घोषणा __USBIP_STUB_H

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>

#घोषणा STUB_BUSID_OTHER 0
#घोषणा STUB_BUSID_REMOV 1
#घोषणा STUB_BUSID_ADDED 2
#घोषणा STUB_BUSID_ALLOC 3

काष्ठा stub_device अणु
	काष्ठा usb_device *udev;

	काष्ठा usbip_device ud;
	__u32 devid;

	/*
	 * stub_priv preserves निजी data of each urb.
	 * It is allocated as stub_priv_cache and asचिन्हित to urb->context.
	 *
	 * stub_priv is always linked to any one of 3 lists;
	 *	priv_init: linked to this until the comletion of a urb.
	 *	priv_tx  : linked to this after the completion of a urb.
	 *	priv_मुक्त: linked to this after the sending of the result.
	 *
	 * Any of these list operations should be locked by priv_lock.
	 */
	spinlock_t priv_lock;
	काष्ठा list_head priv_init;
	काष्ठा list_head priv_tx;
	काष्ठा list_head priv_मुक्त;

	/* see comments क्रम unlinking in stub_rx.c */
	काष्ठा list_head unlink_tx;
	काष्ठा list_head unlink_मुक्त;

	रुको_queue_head_t tx_रुकोq;
पूर्ण;

/* निजी data पूर्णांकo urb->priv */
काष्ठा stub_priv अणु
	अचिन्हित दीर्घ seqnum;
	काष्ठा list_head list;
	काष्ठा stub_device *sdev;
	काष्ठा urb **urbs;
	काष्ठा scatterlist *sgl;
	पूर्णांक num_urbs;
	पूर्णांक completed_urbs;
	पूर्णांक urb_status;

	पूर्णांक unlinking;
पूर्ण;

काष्ठा stub_unlink अणु
	अचिन्हित दीर्घ seqnum;
	काष्ठा list_head list;
	__u32 status;
पूर्ण;

/* same as SYSFS_BUS_ID_SIZE */
#घोषणा BUSID_SIZE 32

काष्ठा bus_id_priv अणु
	अक्षर name[BUSID_SIZE];
	अक्षर status;
	पूर्णांक पूर्णांकerf_count;
	काष्ठा stub_device *sdev;
	काष्ठा usb_device *udev;
	अक्षर shutकरोwn_busid;
	spinlock_t busid_lock;
पूर्ण;

/* stub_priv is allocated from stub_priv_cache */
बाह्य काष्ठा kmem_cache *stub_priv_cache;

/* stub_dev.c */
बाह्य काष्ठा usb_device_driver stub_driver;

/* stub_मुख्य.c */
काष्ठा bus_id_priv *get_busid_priv(स्थिर अक्षर *busid);
व्योम put_busid_priv(काष्ठा bus_id_priv *bid);
पूर्णांक del_match_busid(अक्षर *busid);
व्योम stub_मुक्त_priv_and_urb(काष्ठा stub_priv *priv);
व्योम stub_device_cleanup_urbs(काष्ठा stub_device *sdev);

/* stub_rx.c */
पूर्णांक stub_rx_loop(व्योम *data);

/* stub_tx.c */
व्योम stub_enqueue_ret_unlink(काष्ठा stub_device *sdev, __u32 seqnum,
			     __u32 status);
व्योम stub_complete(काष्ठा urb *urb);
पूर्णांक stub_tx_loop(व्योम *data);

#पूर्ण_अगर /* __USBIP_STUB_H */
