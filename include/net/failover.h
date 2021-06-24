<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _FAILOVER_H
#घोषणा _FAILOVER_H

#समावेश <linux/netdevice.h>

काष्ठा failover_ops अणु
	पूर्णांक (*slave_pre_रेजिस्टर)(काष्ठा net_device *slave_dev,
				  काष्ठा net_device *failover_dev);
	पूर्णांक (*slave_रेजिस्टर)(काष्ठा net_device *slave_dev,
			      काष्ठा net_device *failover_dev);
	पूर्णांक (*slave_pre_unरेजिस्टर)(काष्ठा net_device *slave_dev,
				    काष्ठा net_device *failover_dev);
	पूर्णांक (*slave_unरेजिस्टर)(काष्ठा net_device *slave_dev,
				काष्ठा net_device *failover_dev);
	पूर्णांक (*slave_link_change)(काष्ठा net_device *slave_dev,
				 काष्ठा net_device *failover_dev);
	पूर्णांक (*slave_name_change)(काष्ठा net_device *slave_dev,
				 काष्ठा net_device *failover_dev);
	rx_handler_result_t (*slave_handle_frame)(काष्ठा sk_buff **pskb);
पूर्ण;

काष्ठा failover अणु
	काष्ठा list_head list;
	काष्ठा net_device __rcu *failover_dev;
	काष्ठा failover_ops __rcu *ops;
पूर्ण;

काष्ठा failover *failover_रेजिस्टर(काष्ठा net_device *dev,
				   काष्ठा failover_ops *ops);
व्योम failover_unरेजिस्टर(काष्ठा failover *failover);
पूर्णांक failover_slave_unरेजिस्टर(काष्ठा net_device *slave_dev);

#पूर्ण_अगर /* _FAILOVER_H */
