<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __OSDEP_SERVICE_H_
#घोषणा __OSDEP_SERVICE_H_

#समावेश <basic_types.h>

#घोषणा _FAIL		0
#घोषणा _SUCCESS	1
#घोषणा RTW_RX_HANDLED	2

#समावेश <linux/spinlock.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/sem.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>	/*  क्रम काष्ठा tasklet_काष्ठा */
#समावेश <linux/ip.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>

काष्ठा	__queue	अणु
	काष्ठा	list_head	queue;
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत काष्ठा list_head *get_list_head(काष्ठा __queue *queue)
अणु
	वापस &queue->queue;
पूर्ण

अटल अंतरभूत पूर्णांक rtw_netअगर_queue_stopped(काष्ठा net_device *pnetdev)
अणु
	वापस  netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 0)) &&
		netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 1)) &&
		netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 2)) &&
		netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 3));
पूर्ण

u8 *_rtw_दो_स्मृति(u32 sz);
#घोषणा rtw_दो_स्मृति(sz)			_rtw_दो_स्मृति((sz))

व्योम _rtw_init_queue(काष्ठा __queue *pqueue);

#घोषणा FUNC_NDEV_FMT "%s(%s)"
#घोषणा FUNC_NDEV_ARG(ndev) __func__, ndev->name
#घोषणा FUNC_ADPT_FMT "%s(%s)"
#घोषणा FUNC_ADPT_ARG(adapter) __func__, adapter->pnetdev->name

/* Macros क्रम handling unaligned memory accesses */

#घोषणा RTW_GET_BE24(a) ((((u32)(a)[0]) << 16) | (((u32)(a)[1]) << 8) | \
			 ((u32)(a)[2]))

व्योम rtw_buf_मुक्त(u8 **buf, u32 *buf_len);
व्योम rtw_buf_update(u8 **buf, u32 *buf_len, u8 *src, u32 src_len);
#पूर्ण_अगर
