<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

पूर्णांक cvm_oct_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक cvm_oct_xmit_घात(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक cvm_oct_transmit_qos(काष्ठा net_device *dev, व्योम *work_queue_entry,
			 पूर्णांक करो_मुक्त, पूर्णांक qos);
व्योम cvm_oct_tx_initialize(व्योम);
व्योम cvm_oct_tx_shutकरोwn(व्योम);
व्योम cvm_oct_tx_shutकरोwn_dev(काष्ठा net_device *dev);
