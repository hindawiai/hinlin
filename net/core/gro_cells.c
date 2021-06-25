<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <net/gro_cells.h>

काष्ठा gro_cell अणु
	काष्ठा sk_buff_head	napi_skbs;
	काष्ठा napi_काष्ठा	napi;
पूर्ण;

पूर्णांक gro_cells_receive(काष्ठा gro_cells *gcells, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा gro_cell *cell;
	पूर्णांक res;

	rcu_पढ़ो_lock();
	अगर (unlikely(!(dev->flags & IFF_UP)))
		जाओ drop;

	अगर (!gcells->cells || skb_cloned(skb) || netअगर_elide_gro(dev)) अणु
		res = netअगर_rx(skb);
		जाओ unlock;
	पूर्ण

	cell = this_cpu_ptr(gcells->cells);

	अगर (skb_queue_len(&cell->napi_skbs) > netdev_max_backlog) अणु
drop:
		atomic_दीर्घ_inc(&dev->rx_dropped);
		kमुक्त_skb(skb);
		res = NET_RX_DROP;
		जाओ unlock;
	पूर्ण

	__skb_queue_tail(&cell->napi_skbs, skb);
	अगर (skb_queue_len(&cell->napi_skbs) == 1)
		napi_schedule(&cell->napi);

	res = NET_RX_SUCCESS;

unlock:
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण
EXPORT_SYMBOL(gro_cells_receive);

/* called under BH context */
अटल पूर्णांक gro_cell_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gro_cell *cell = container_of(napi, काष्ठा gro_cell, napi);
	काष्ठा sk_buff *skb;
	पूर्णांक work_करोne = 0;

	जबतक (work_करोne < budget) अणु
		skb = __skb_dequeue(&cell->napi_skbs);
		अगर (!skb)
			अवरोध;
		napi_gro_receive(napi, skb);
		work_करोne++;
	पूर्ण

	अगर (work_करोne < budget)
		napi_complete_करोne(napi, work_करोne);
	वापस work_करोne;
पूर्ण

पूर्णांक gro_cells_init(काष्ठा gro_cells *gcells, काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	gcells->cells = alloc_percpu(काष्ठा gro_cell);
	अगर (!gcells->cells)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा gro_cell *cell = per_cpu_ptr(gcells->cells, i);

		__skb_queue_head_init(&cell->napi_skbs);

		set_bit(NAPI_STATE_NO_BUSY_POLL, &cell->napi.state);

		netअगर_napi_add(dev, &cell->napi, gro_cell_poll,
			       NAPI_POLL_WEIGHT);
		napi_enable(&cell->napi);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(gro_cells_init);

व्योम gro_cells_destroy(काष्ठा gro_cells *gcells)
अणु
	पूर्णांक i;

	अगर (!gcells->cells)
		वापस;
	क्रम_each_possible_cpu(i) अणु
		काष्ठा gro_cell *cell = per_cpu_ptr(gcells->cells, i);

		napi_disable(&cell->napi);
		__netअगर_napi_del(&cell->napi);
		__skb_queue_purge(&cell->napi_skbs);
	पूर्ण
	/* This barrier is needed because netpoll could access dev->napi_list
	 * under rcu protection.
	 */
	synchronize_net();

	मुक्त_percpu(gcells->cells);
	gcells->cells = शून्य;
पूर्ण
EXPORT_SYMBOL(gro_cells_destroy);
