<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011, 2012 Cavium, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/mdio-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_DESCRIPTION "MDIO bus multiplexer driver"

काष्ठा mdio_mux_child_bus;

काष्ठा mdio_mux_parent_bus अणु
	काष्ठा mii_bus *mii_bus;
	पूर्णांक current_child;
	पूर्णांक parent_id;
	व्योम *चयन_data;
	पूर्णांक (*चयन_fn)(पूर्णांक current_child, पूर्णांक desired_child, व्योम *data);

	/* List of our children linked through their next fields. */
	काष्ठा mdio_mux_child_bus *children;
पूर्ण;

काष्ठा mdio_mux_child_bus अणु
	काष्ठा mii_bus *mii_bus;
	काष्ठा mdio_mux_parent_bus *parent;
	काष्ठा mdio_mux_child_bus *next;
	पूर्णांक bus_number;
पूर्ण;

/*
 * The parent bus' lock is used to order access to the चयन_fn.
 */
अटल पूर्णांक mdio_mux_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	काष्ठा mdio_mux_child_bus *cb = bus->priv;
	काष्ठा mdio_mux_parent_bus *pb = cb->parent;
	पूर्णांक r;

	mutex_lock_nested(&pb->mii_bus->mdio_lock, MDIO_MUTEX_MUX);
	r = pb->चयन_fn(pb->current_child, cb->bus_number, pb->चयन_data);
	अगर (r)
		जाओ out;

	pb->current_child = cb->bus_number;

	r = pb->mii_bus->पढ़ो(pb->mii_bus, phy_id, regnum);
out:
	mutex_unlock(&pb->mii_bus->mdio_lock);

	वापस r;
पूर्ण

/*
 * The parent bus' lock is used to order access to the चयन_fn.
 */
अटल पूर्णांक mdio_mux_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id,
			  पूर्णांक regnum, u16 val)
अणु
	काष्ठा mdio_mux_child_bus *cb = bus->priv;
	काष्ठा mdio_mux_parent_bus *pb = cb->parent;

	पूर्णांक r;

	mutex_lock_nested(&pb->mii_bus->mdio_lock, MDIO_MUTEX_MUX);
	r = pb->चयन_fn(pb->current_child, cb->bus_number, pb->चयन_data);
	अगर (r)
		जाओ out;

	pb->current_child = cb->bus_number;

	r = pb->mii_bus->ग_लिखो(pb->mii_bus, phy_id, regnum, val);
out:
	mutex_unlock(&pb->mii_bus->mdio_lock);

	वापस r;
पूर्ण

अटल पूर्णांक parent_count;

पूर्णांक mdio_mux_init(काष्ठा device *dev,
		  काष्ठा device_node *mux_node,
		  पूर्णांक (*चयन_fn)(पूर्णांक cur, पूर्णांक desired, व्योम *data),
		  व्योम **mux_handle,
		  व्योम *data,
		  काष्ठा mii_bus *mux_bus)
अणु
	काष्ठा device_node *parent_bus_node;
	काष्ठा device_node *child_bus_node;
	पूर्णांक r, ret_val;
	काष्ठा mii_bus *parent_bus;
	काष्ठा mdio_mux_parent_bus *pb;
	काष्ठा mdio_mux_child_bus *cb;

	अगर (!mux_node)
		वापस -ENODEV;

	अगर (!mux_bus) अणु
		parent_bus_node = of_parse_phandle(mux_node,
						   "mdio-parent-bus", 0);

		अगर (!parent_bus_node)
			वापस -ENODEV;

		parent_bus = of_mdio_find_bus(parent_bus_node);
		अगर (!parent_bus) अणु
			ret_val = -EPROBE_DEFER;
			जाओ err_parent_bus;
		पूर्ण
	पूर्ण अन्यथा अणु
		parent_bus_node = शून्य;
		parent_bus = mux_bus;
		get_device(&parent_bus->dev);
	पूर्ण

	pb = devm_kzalloc(dev, माप(*pb), GFP_KERNEL);
	अगर (!pb) अणु
		ret_val = -ENOMEM;
		जाओ err_pb_kz;
	पूर्ण

	pb->चयन_data = data;
	pb->चयन_fn = चयन_fn;
	pb->current_child = -1;
	pb->parent_id = parent_count++;
	pb->mii_bus = parent_bus;

	ret_val = -ENODEV;
	क्रम_each_available_child_of_node(mux_node, child_bus_node) अणु
		पूर्णांक v;

		r = of_property_पढ़ो_u32(child_bus_node, "reg", &v);
		अगर (r) अणु
			dev_err(dev,
				"Error: Failed to find reg for child %pOF\n",
				child_bus_node);
			जारी;
		पूर्ण

		cb = devm_kzalloc(dev, माप(*cb), GFP_KERNEL);
		अगर (!cb) अणु
			ret_val = -ENOMEM;
			जारी;
		पूर्ण
		cb->bus_number = v;
		cb->parent = pb;

		cb->mii_bus = mdiobus_alloc();
		अगर (!cb->mii_bus) अणु
			ret_val = -ENOMEM;
			devm_kमुक्त(dev, cb);
			जारी;
		पूर्ण
		cb->mii_bus->priv = cb;

		cb->mii_bus->name = "mdio_mux";
		snम_लिखो(cb->mii_bus->id, MII_BUS_ID_SIZE, "%x.%x",
			 pb->parent_id, v);
		cb->mii_bus->parent = dev;
		cb->mii_bus->पढ़ो = mdio_mux_पढ़ो;
		cb->mii_bus->ग_लिखो = mdio_mux_ग_लिखो;
		r = of_mdiobus_रेजिस्टर(cb->mii_bus, child_bus_node);
		अगर (r) अणु
			dev_err(dev,
				"Error: Failed to register MDIO bus for child %pOF\n",
				child_bus_node);
			mdiobus_मुक्त(cb->mii_bus);
			devm_kमुक्त(dev, cb);
		पूर्ण अन्यथा अणु
			cb->next = pb->children;
			pb->children = cb;
		पूर्ण
	पूर्ण
	अगर (pb->children) अणु
		*mux_handle = pb;
		वापस 0;
	पूर्ण

	dev_err(dev, "Error: No acceptable child buses found\n");
	devm_kमुक्त(dev, pb);
err_pb_kz:
	put_device(&parent_bus->dev);
err_parent_bus:
	of_node_put(parent_bus_node);
	वापस ret_val;
पूर्ण
EXPORT_SYMBOL_GPL(mdio_mux_init);

व्योम mdio_mux_uninit(व्योम *mux_handle)
अणु
	काष्ठा mdio_mux_parent_bus *pb = mux_handle;
	काष्ठा mdio_mux_child_bus *cb = pb->children;

	जबतक (cb) अणु
		mdiobus_unरेजिस्टर(cb->mii_bus);
		mdiobus_मुक्त(cb->mii_bus);
		cb = cb->next;
	पूर्ण

	put_device(&pb->mii_bus->dev);
पूर्ण
EXPORT_SYMBOL_GPL(mdio_mux_uninit);

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL v2");
