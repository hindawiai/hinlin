<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Data gathering module क्रम Linux-VM Monitor Stream, Stage 1.
 * Collects accumulated network statistics (Packets received/transmitted,
 * dropped, errors, ...).
 *
 * Copyright IBM Corp. 2003, 2006
 *
 * Author: Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/netdevice.h>
#समावेश <net/net_namespace.h>

#समावेश "appldata.h"


/*
 * Network data
 *
 * This is accessed as binary data by z/VM. If changes to it can't be aव्योमed,
 * the काष्ठाure version (product ID, see appldata_base.c) needs to be changed
 * as well and all करोcumentation and z/VM applications using it must be updated.
 */
काष्ठा appldata_net_sum_data अणु
	u64 बारtamp;
	u32 sync_count_1;	/* after VM collected the record data, */
	u32 sync_count_2;	/* sync_count_1 and sync_count_2 should be the
				   same. If not, the record has been updated on
				   the Linux side जबतक VM was collecting the
				   (possibly corrupt) data */

	u32 nr_पूर्णांकerfaces;	/* nr. of network पूर्णांकerfaces being monitored */

	u32 padding;		/* next value is 64-bit aligned, so these */
				/* 4 byte would be padded out by compiler */

	u64 rx_packets;		/* total packets received        */
	u64 tx_packets;		/* total packets transmitted     */
	u64 rx_bytes;		/* total bytes received          */
	u64 tx_bytes;		/* total bytes transmitted       */
	u64 rx_errors;		/* bad packets received          */
	u64 tx_errors;		/* packet transmit problems      */
	u64 rx_dropped;		/* no space in linux buffers     */
	u64 tx_dropped;		/* no space available in linux   */
	u64 collisions;		/* collisions जबतक transmitting */
पूर्ण __packed;


/*
 * appldata_get_net_sum_data()
 *
 * gather accumulated network statistics
 */
अटल व्योम appldata_get_net_sum_data(व्योम *data)
अणु
	पूर्णांक i;
	काष्ठा appldata_net_sum_data *net_data;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ rx_packets, tx_packets, rx_bytes, tx_bytes, rx_errors,
			tx_errors, rx_dropped, tx_dropped, collisions;

	net_data = data;
	net_data->sync_count_1++;

	i = 0;
	rx_packets = 0;
	tx_packets = 0;
	rx_bytes   = 0;
	tx_bytes   = 0;
	rx_errors  = 0;
	tx_errors  = 0;
	rx_dropped = 0;
	tx_dropped = 0;
	collisions = 0;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		स्थिर काष्ठा rtnl_link_stats64 *stats;
		काष्ठा rtnl_link_stats64 temp;

		stats = dev_get_stats(dev, &temp);
		rx_packets += stats->rx_packets;
		tx_packets += stats->tx_packets;
		rx_bytes   += stats->rx_bytes;
		tx_bytes   += stats->tx_bytes;
		rx_errors  += stats->rx_errors;
		tx_errors  += stats->tx_errors;
		rx_dropped += stats->rx_dropped;
		tx_dropped += stats->tx_dropped;
		collisions += stats->collisions;
		i++;
	पूर्ण
	rcu_पढ़ो_unlock();

	net_data->nr_पूर्णांकerfaces = i;
	net_data->rx_packets = rx_packets;
	net_data->tx_packets = tx_packets;
	net_data->rx_bytes   = rx_bytes;
	net_data->tx_bytes   = tx_bytes;
	net_data->rx_errors  = rx_errors;
	net_data->tx_errors  = tx_errors;
	net_data->rx_dropped = rx_dropped;
	net_data->tx_dropped = tx_dropped;
	net_data->collisions = collisions;

	net_data->बारtamp = get_tod_घड़ी();
	net_data->sync_count_2++;
पूर्ण


अटल काष्ठा appldata_ops ops = अणु
	.name	   = "net_sum",
	.record_nr = APPLDATA_RECORD_NET_SUM_ID,
	.size	   = माप(काष्ठा appldata_net_sum_data),
	.callback  = &appldata_get_net_sum_data,
	.owner     = THIS_MODULE,
	.mod_lvl   = अणु0xF0, 0xF0पूर्ण,		/* EBCDIC "00" */
पूर्ण;


/*
 * appldata_net_init()
 *
 * init data, रेजिस्टर ops
 */
अटल पूर्णांक __init appldata_net_init(व्योम)
अणु
	पूर्णांक ret;

	ops.data = kzalloc(माप(काष्ठा appldata_net_sum_data), GFP_KERNEL);
	अगर (!ops.data)
		वापस -ENOMEM;

	ret = appldata_रेजिस्टर_ops(&ops);
	अगर (ret)
		kमुक्त(ops.data);

	वापस ret;
पूर्ण

/*
 * appldata_net_निकास()
 *
 * unरेजिस्टर ops
 */
अटल व्योम __निकास appldata_net_निकास(व्योम)
अणु
	appldata_unरेजिस्टर_ops(&ops);
	kमुक्त(ops.data);
पूर्ण


module_init(appldata_net_init);
module_निकास(appldata_net_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gerald Schaefer");
MODULE_DESCRIPTION("Linux-VM Monitor Stream, accumulated network statistics");
