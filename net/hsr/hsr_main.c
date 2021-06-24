<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * Event handling क्रम HSR and PRP devices.
 */

#समावेश <linux/netdevice.h>
#समावेश <net/rtnetlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/समयr.h>
#समावेश <linux/etherdevice.h>
#समावेश "hsr_main.h"
#समावेश "hsr_device.h"
#समावेश "hsr_netlink.h"
#समावेश "hsr_framereg.h"
#समावेश "hsr_slave.h"

अटल bool hsr_slave_empty(काष्ठा hsr_priv *hsr)
अणु
	काष्ठा hsr_port *port;

	hsr_क्रम_each_port(hsr, port)
		अगर (port->type != HSR_PT_MASTER)
			वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक hsr_netdev_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा hsr_port *port, *master;
	काष्ठा net_device *dev;
	काष्ठा hsr_priv *hsr;
	LIST_HEAD(list_समाप्त);
	पूर्णांक mtu_max;
	पूर्णांक res;

	dev = netdev_notअगरier_info_to_dev(ptr);
	port = hsr_port_get_rtnl(dev);
	अगर (!port) अणु
		अगर (!is_hsr_master(dev))
			वापस NOTIFY_DONE;	/* Not an HSR device */
		hsr = netdev_priv(dev);
		port = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
		अगर (!port) अणु
			/* Resend of notअगरication concerning हटाओd device? */
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण अन्यथा अणु
		hsr = port->hsr;
	पूर्ण

	चयन (event) अणु
	हाल NETDEV_UP:		/* Administrative state DOWN */
	हाल NETDEV_DOWN:	/* Administrative state UP */
	हाल NETDEV_CHANGE:	/* Link (carrier) state changes */
		hsr_check_carrier_and_operstate(hsr);
		अवरोध;
	हाल NETDEV_CHANGENAME:
		अगर (is_hsr_master(dev))
			hsr_debugfs_नाम(dev);
		अवरोध;
	हाल NETDEV_CHANGEADDR:
		अगर (port->type == HSR_PT_MASTER) अणु
			/* This should not happen since there's no
			 * nकरो_set_mac_address() क्रम HSR devices - i.e. not
			 * supported.
			 */
			अवरोध;
		पूर्ण

		master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);

		अगर (port->type == HSR_PT_SLAVE_A) अणु
			ether_addr_copy(master->dev->dev_addr, dev->dev_addr);
			call_netdevice_notअगरiers(NETDEV_CHANGEADDR,
						 master->dev);
		पूर्ण

		/* Make sure we recognize frames from ourselves in hsr_rcv() */
		port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
		res = hsr_create_self_node(hsr,
					   master->dev->dev_addr,
					   port ?
						port->dev->dev_addr :
						master->dev->dev_addr);
		अगर (res)
			netdev_warn(master->dev,
				    "Could not update HSR node address.\n");
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		अगर (port->type == HSR_PT_MASTER)
			अवरोध; /* Handled in nकरो_change_mtu() */
		mtu_max = hsr_get_max_mtu(port->hsr);
		master = hsr_port_get_hsr(port->hsr, HSR_PT_MASTER);
		master->dev->mtu = mtu_max;
		अवरोध;
	हाल NETDEV_UNREGISTER:
		अगर (!is_hsr_master(dev)) अणु
			master = hsr_port_get_hsr(port->hsr, HSR_PT_MASTER);
			hsr_del_port(port);
			अगर (hsr_slave_empty(master->hsr)) अणु
				स्थिर काष्ठा rtnl_link_ops *ops;

				ops = master->dev->rtnl_link_ops;
				ops->dellink(master->dev, &list_समाप्त);
				unरेजिस्टर_netdevice_many(&list_समाप्त);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NETDEV_PRE_TYPE_CHANGE:
		/* HSR works only on Ethernet devices. Refuse slave to change
		 * its type.
		 */
		वापस NOTIFY_BAD;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा hsr_port *hsr_port_get_hsr(काष्ठा hsr_priv *hsr, क्रमागत hsr_port_type pt)
अणु
	काष्ठा hsr_port *port;

	hsr_क्रम_each_port(hsr, port)
		अगर (port->type == pt)
			वापस port;
	वापस शून्य;
पूर्ण

पूर्णांक hsr_get_version(काष्ठा net_device *dev, क्रमागत hsr_version *ver)
अणु
	काष्ठा hsr_priv *hsr;

	hsr = netdev_priv(dev);
	*ver = hsr->prot_version;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hsr_get_version);

अटल काष्ठा notअगरier_block hsr_nb = अणु
	.notअगरier_call = hsr_netdev_notअगरy,	/* Slave event notअगरications */
पूर्ण;

अटल पूर्णांक __init hsr_init(व्योम)
अणु
	पूर्णांक res;

	BUILD_BUG_ON(माप(काष्ठा hsr_tag) != HSR_HLEN);

	रेजिस्टर_netdevice_notअगरier(&hsr_nb);
	res = hsr_netlink_init();

	वापस res;
पूर्ण

अटल व्योम __निकास hsr_निकास(व्योम)
अणु
	hsr_netlink_निकास();
	hsr_debugfs_हटाओ_root();
	unरेजिस्टर_netdevice_notअगरier(&hsr_nb);
पूर्ण

module_init(hsr_init);
module_निकास(hsr_निकास);
MODULE_LICENSE("GPL");
