<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Type-C Connector Class Port Mapping Utility
 *
 * Copyright (C) 2021, Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/typec.h>

#समावेश "class.h"

काष्ठा port_node अणु
	काष्ठा list_head list;
	काष्ठा device *dev;
	व्योम *pld;
पूर्ण;

अटल पूर्णांक acpi_pld_match(स्थिर काष्ठा acpi_pld_info *pld1,
			  स्थिर काष्ठा acpi_pld_info *pld2)
अणु
	अगर (!pld1 || !pld2)
		वापस 0;

	/*
	 * To speed things up, first checking only the group_position. It seems
	 * to often have the first unique value in the _PLD.
	 */
	अगर (pld1->group_position == pld2->group_position)
		वापस !स_भेद(pld1, pld2, माप(काष्ठा acpi_pld_info));

	वापस 0;
पूर्ण

अटल व्योम *get_pld(काष्ठा device *dev)
अणु
#अगर_घोषित CONFIG_ACPI
	काष्ठा acpi_pld_info *pld;
	acpi_status status;

	अगर (!has_acpi_companion(dev))
		वापस शून्य;

	status = acpi_get_physical_device_location(ACPI_HANDLE(dev), &pld);
	अगर (ACPI_FAILURE(status))
		वापस शून्य;

	वापस pld;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल व्योम मुक्त_pld(व्योम *pld)
अणु
#अगर_घोषित CONFIG_ACPI
	ACPI_FREE(pld);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __link_port(काष्ठा typec_port *con, काष्ठा port_node *node)
अणु
	पूर्णांक ret;

	ret = sysfs_create_link(&node->dev->kobj, &con->dev.kobj, "connector");
	अगर (ret)
		वापस ret;

	ret = sysfs_create_link(&con->dev.kobj, &node->dev->kobj,
				dev_name(node->dev));
	अगर (ret) अणु
		sysfs_हटाओ_link(&node->dev->kobj, "connector");
		वापस ret;
	पूर्ण

	list_add_tail(&node->list, &con->port_list);

	वापस 0;
पूर्ण

अटल पूर्णांक link_port(काष्ठा typec_port *con, काष्ठा port_node *node)
अणु
	पूर्णांक ret;

	mutex_lock(&con->port_list_lock);
	ret = __link_port(con, node);
	mutex_unlock(&con->port_list_lock);

	वापस ret;
पूर्ण

अटल व्योम __unlink_port(काष्ठा typec_port *con, काष्ठा port_node *node)
अणु
	sysfs_हटाओ_link(&con->dev.kobj, dev_name(node->dev));
	sysfs_हटाओ_link(&node->dev->kobj, "connector");
	list_del(&node->list);
पूर्ण

अटल व्योम unlink_port(काष्ठा typec_port *con, काष्ठा port_node *node)
अणु
	mutex_lock(&con->port_list_lock);
	__unlink_port(con, node);
	mutex_unlock(&con->port_list_lock);
पूर्ण

अटल काष्ठा port_node *create_port_node(काष्ठा device *port)
अणु
	काष्ठा port_node *node;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);

	node->dev = get_device(port);
	node->pld = get_pld(port);

	वापस node;
पूर्ण

अटल व्योम हटाओ_port_node(काष्ठा port_node *node)
अणु
	put_device(node->dev);
	मुक्त_pld(node->pld);
	kमुक्त(node);
पूर्ण

अटल पूर्णांक connector_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा port_node *node = data;

	अगर (!is_typec_port(dev))
		वापस 0;

	वापस acpi_pld_match(to_typec_port(dev)->pld, node->pld);
पूर्ण

अटल काष्ठा device *find_connector(काष्ठा port_node *node)
अणु
	अगर (!node->pld)
		वापस शून्य;

	वापस class_find_device(&typec_class, शून्य, node, connector_match);
पूर्ण

/**
 * typec_link_port - Link a port to its connector
 * @port: The port device
 *
 * Find the connector of @port and create symlink named "connector" क्रम it.
 * Returns 0 on success, or त्रुटि_सं in हाल of a failure.
 *
 * NOTE. The function increments the reference count of @port on success.
 */
पूर्णांक typec_link_port(काष्ठा device *port)
अणु
	काष्ठा device *connector;
	काष्ठा port_node *node;
	पूर्णांक ret;

	node = create_port_node(port);
	अगर (IS_ERR(node))
		वापस PTR_ERR(node);

	connector = find_connector(node);
	अगर (!connector) अणु
		ret = 0;
		जाओ हटाओ_node;
	पूर्ण

	ret = link_port(to_typec_port(connector), node);
	अगर (ret)
		जाओ put_connector;

	वापस 0;

put_connector:
	put_device(connector);
हटाओ_node:
	हटाओ_port_node(node);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(typec_link_port);

अटल पूर्णांक port_match_and_unlink(काष्ठा device *connector, व्योम *port)
अणु
	काष्ठा port_node *node;
	काष्ठा port_node *पंचांगp;
	पूर्णांक ret = 0;

	अगर (!is_typec_port(connector))
		वापस 0;

	mutex_lock(&to_typec_port(connector)->port_list_lock);
	list_क्रम_each_entry_safe(node, पंचांगp, &to_typec_port(connector)->port_list, list) अणु
		ret = node->dev == port;
		अगर (ret) अणु
			unlink_port(to_typec_port(connector), node);
			हटाओ_port_node(node);
			put_device(connector);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&to_typec_port(connector)->port_list_lock);

	वापस ret;
पूर्ण

/**
 * typec_unlink_port - Unlink port from its connector
 * @port: The port device
 *
 * Removes the symlink "connector" and decrements the reference count of @port.
 */
व्योम typec_unlink_port(काष्ठा device *port)
अणु
	class_क्रम_each_device(&typec_class, शून्य, port, port_match_and_unlink);
पूर्ण
EXPORT_SYMBOL_GPL(typec_unlink_port);

अटल पूर्णांक each_port(काष्ठा device *port, व्योम *connector)
अणु
	काष्ठा port_node *node;
	पूर्णांक ret;

	node = create_port_node(port);
	अगर (IS_ERR(node))
		वापस PTR_ERR(node);

	अगर (!connector_match(connector, node)) अणु
		हटाओ_port_node(node);
		वापस 0;
	पूर्ण

	ret = link_port(to_typec_port(connector), node);
	अगर (ret) अणु
		हटाओ_port_node(node->pld);
		वापस ret;
	पूर्ण

	get_device(connector);

	वापस 0;
पूर्ण

पूर्णांक typec_link_ports(काष्ठा typec_port *con)
अणु
	पूर्णांक ret = 0;

	con->pld = get_pld(&con->dev);
	अगर (!con->pld)
		वापस 0;

	ret = usb_क्रम_each_port(&con->dev, each_port);
	अगर (ret)
		typec_unlink_ports(con);

	वापस ret;
पूर्ण

व्योम typec_unlink_ports(काष्ठा typec_port *con)
अणु
	काष्ठा port_node *node;
	काष्ठा port_node *पंचांगp;

	mutex_lock(&con->port_list_lock);

	list_क्रम_each_entry_safe(node, पंचांगp, &con->port_list, list) अणु
		__unlink_port(con, node);
		हटाओ_port_node(node);
		put_device(&con->dev);
	पूर्ण

	mutex_unlock(&con->port_list_lock);

	मुक्त_pld(con->pld);
पूर्ण
