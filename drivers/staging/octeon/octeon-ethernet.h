<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2010 Cavium Networks
 */

/*
 * External पूर्णांकerface क्रम the Cavium Octeon ethernet driver.
 */
#अगर_अघोषित OCTEON_ETHERNET_H
#घोषणा OCTEON_ETHERNET_H

#समावेश <linux/of.h>
#समावेश <linux/phy.h>

#अगर_घोषित CONFIG_CAVIUM_OCTEON_SOC

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-asxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-config.h>
#समावेश <यंत्र/octeon/cvmx-fau.h>
#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-helper.h>
#समावेश <यंत्र/octeon/cvmx-helper-util.h>
#समावेश <यंत्र/octeon/cvmx-ipd.h>
#समावेश <यंत्र/octeon/cvmx-ipd-defs.h>
#समावेश <यंत्र/octeon/cvmx-npi-defs.h>
#समावेश <यंत्र/octeon/cvmx-pip.h>
#समावेश <यंत्र/octeon/cvmx-pko.h>
#समावेश <यंत्र/octeon/cvmx-घात.h>
#समावेश <यंत्र/octeon/cvmx-scratch.h>
#समावेश <यंत्र/octeon/cvmx-spi.h>
#समावेश <यंत्र/octeon/cvmx-spxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-stxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-wqe.h>

#अन्यथा

#समावेश "octeon-stubs.h"

#पूर्ण_अगर

/**
 * This is the definition of the Ethernet driver's निजी
 * driver state stored in netdev_priv(dev).
 */
काष्ठा octeon_ethernet अणु
	/* PKO hardware output port */
	पूर्णांक port;
	/* PKO hardware queue क्रम the port */
	पूर्णांक queue;
	/* Hardware fetch and add to count outstanding tx buffers */
	पूर्णांक fau;
	/* My netdev. */
	काष्ठा net_device *netdev;
	/*
	 * Type of port. This is one of the क्रमागतs in
	 * cvmx_helper_पूर्णांकerface_mode_t
	 */
	पूर्णांक imode;
	/* PHY mode */
	phy_पूर्णांकerface_t phy_mode;
	/* List of outstanding tx buffers per queue */
	काष्ठा sk_buff_head tx_मुक्त_list[16];
	अचिन्हित पूर्णांक last_speed;
	अचिन्हित पूर्णांक last_link;
	/* Last negotiated link state */
	u64 link_info;
	/* Called periodically to check link status */
	व्योम (*poll)(काष्ठा net_device *dev);
	काष्ठा delayed_work	port_periodic_work;
	काष्ठा device_node	*of_node;
पूर्ण;

पूर्णांक cvm_oct_मुक्त_work(व्योम *work_queue_entry);

पूर्णांक cvm_oct_rgmii_खोलो(काष्ठा net_device *dev);

पूर्णांक cvm_oct_sgmii_init(काष्ठा net_device *dev);
पूर्णांक cvm_oct_sgmii_खोलो(काष्ठा net_device *dev);

पूर्णांक cvm_oct_spi_init(काष्ठा net_device *dev);
व्योम cvm_oct_spi_uninit(काष्ठा net_device *dev);

पूर्णांक cvm_oct_common_init(काष्ठा net_device *dev);
व्योम cvm_oct_common_uninit(काष्ठा net_device *dev);
व्योम cvm_oct_adjust_link(काष्ठा net_device *dev);
पूर्णांक cvm_oct_common_stop(काष्ठा net_device *dev);
पूर्णांक cvm_oct_common_खोलो(काष्ठा net_device *dev,
			व्योम (*link_poll)(काष्ठा net_device *));
व्योम cvm_oct_note_carrier(काष्ठा octeon_ethernet *priv,
			  जोड़ cvmx_helper_link_info li);
व्योम cvm_oct_link_poll(काष्ठा net_device *dev);

बाह्य पूर्णांक always_use_घात;
बाह्य पूर्णांक घात_send_group;
बाह्य पूर्णांक घात_receive_groups;
बाह्य अक्षर घात_send_list[];
बाह्य काष्ठा net_device *cvm_oct_device[];
बाह्य atomic_t cvm_oct_poll_queue_stopping;
बाह्य u64 cvm_oct_tx_poll_पूर्णांकerval;

बाह्य पूर्णांक rx_napi_weight;

#पूर्ण_अगर
