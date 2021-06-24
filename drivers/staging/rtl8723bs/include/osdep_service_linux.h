<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __OSDEP_LINUX_SERVICE_H_
#घोषणा __OSDEP_LINUX_SERVICE_H_

	#समावेश <linux/spinlock.h>
	#समावेश <linux/compiler.h>
	#समावेश <linux/kernel.h>
	#समावेश <linux/त्रुटिसं.स>
	#समावेश <linux/init.h>
	#समावेश <linux/slab.h>
	#समावेश <linux/module.h>
	#समावेश <linux/kref.h>
	/* include <linux/smp_lock.h> */
	#समावेश <linux/netdevice.h>
	#समावेश <linux/skbuff.h>
	#समावेश <linux/uaccess.h>
	#समावेश <यंत्र/byteorder.h>
	#समावेश <linux/atomic.h>
	#समावेश <linux/पन.स>
	#समावेश <linux/sem.h>
	#समावेश <linux/sched.h>
	#समावेश <linux/etherdevice.h>
	#समावेश <linux/wireless.h>
	#समावेश <net/iw_handler.h>
	#समावेश <linux/अगर_arp.h>
	#समावेश <linux/rtnetlink.h>
	#समावेश <linux/delay.h>
	#समावेश <linux/पूर्णांकerrupt.h>	/*  क्रम काष्ठा tasklet_काष्ठा */
	#समावेश <linux/ip.h>
	#समावेश <linux/kthपढ़ो.h>
	#समावेश <linux/list.h>
	#समावेश <linux/vदो_स्मृति.h>

/* 	#समावेश <linux/ieee80211.h> */
        #समावेश <net/ieee80211_radiotap.h>
	#समावेश <net/cfg80211.h>

	काष्ठा	__queue	अणु
		काष्ठा	list_head	queue;
		spinlock_t	lock;
	पूर्ण;

	#घोषणा thपढ़ो_निकास() complete_and_निकास(शून्य, 0)

अटल अंतरभूत काष्ठा list_head *get_next(काष्ठा list_head	*list)
अणु
	वापस list->next;
पूर्ण

अटल अंतरभूत काष्ठा list_head	*get_list_head(काष्ठा __queue	*queue)
अणु
	वापस (&(queue->queue));
पूर्ण

अटल अंतरभूत व्योम _set_समयr(काष्ठा समयr_list *pसमयr, u32 delay_समय)
अणु
	mod_समयr(pसमयr, (jअगरfies + (delay_समय * HZ / 1000)));
पूर्ण

अटल अंतरभूत व्योम _init_workitem(काष्ठा work_काष्ठा *pwork, व्योम *pfunc, व्योम *cntx)
अणु
	INIT_WORK(pwork, pfunc);
पूर्ण

अटल अंतरभूत व्योम _set_workitem(काष्ठा work_काष्ठा *pwork)
अणु
	schedule_work(pwork);
पूर्ण

अटल अंतरभूत व्योम _cancel_workitem_sync(काष्ठा work_काष्ठा *pwork)
अणु
	cancel_work_sync(pwork);
पूर्ण

अटल अंतरभूत पूर्णांक rtw_netअगर_queue_stopped(काष्ठा net_device *pnetdev)
अणु
	वापस (netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 0)) &&
		netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 1)) &&
		netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 2)) &&
		netअगर_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 3)));
पूर्ण

अटल अंतरभूत व्योम rtw_netअगर_wake_queue(काष्ठा net_device *pnetdev)
अणु
	netअगर_tx_wake_all_queues(pnetdev);
पूर्ण

अटल अंतरभूत व्योम rtw_netअगर_start_queue(काष्ठा net_device *pnetdev)
अणु
	netअगर_tx_start_all_queues(pnetdev);
पूर्ण

अटल अंतरभूत व्योम rtw_netअगर_stop_queue(काष्ठा net_device *pnetdev)
अणु
	netअगर_tx_stop_all_queues(pnetdev);
पूर्ण

#घोषणा rtw_संकेत_process(pid, sig) समाप्त_pid(find_vpid((pid)), (sig), 1)

#घोषणा NDEV_ARG(ndev) ndev->name
#घोषणा ADPT_ARG(adapter) adapter->pnetdev->name
#घोषणा FUNC_NDEV_FMT "%s(%s)"
#घोषणा FUNC_NDEV_ARG(ndev) __func__, ndev->name
#घोषणा FUNC_ADPT_FMT "%s(%s)"
#घोषणा FUNC_ADPT_ARG(adapter) __func__, adapter->pnetdev->name

काष्ठा rtw_netdev_priv_indicator अणु
	व्योम *priv;
	u32 माप_priv;
पूर्ण;

अटल अंतरभूत काष्ठा adapter *rtw_netdev_priv(काष्ठा net_device *netdev)
अणु
	वापस ((काष्ठा rtw_netdev_priv_indicator *)netdev_priv(netdev))->priv;
पूर्ण

काष्ठा net_device *rtw_alloc_etherdev_with_old_priv(पूर्णांक माप_priv, व्योम *old_priv);
बाह्य काष्ठा net_device *rtw_alloc_etherdev(पूर्णांक माप_priv);

#पूर्ण_अगर
