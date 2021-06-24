<शैली गुरु>
/*
 * Multiplexed I2C bus driver.
 *
 * Copyright (c) 2008-2009 Roकरोlfo Giometti <giometti@linux.it>
 * Copyright (c) 2008-2009 Eurotech S.p.A. <info@eurotech.it>
 * Copyright (c) 2009-2010 NSN GmbH & Co KG <michael.lawnick.ext@nsn.com>
 *
 * Simplअगरies access to complex multiplexed I2C bus topologies, by presenting
 * each multiplexed bus segment as an additional I2C adapter.
 * Supports multi-level mux'ing (mux behind a mux).
 *
 * Based on:
 *	i2c-virt.c from Kumar Gala <galak@kernel.crashing.org>
 *	i2c-भव.c from Ken Harrenstien, Copyright (c) 2004 Google, Inc.
 *	i2c-भव.c from Brian Kuschak <bkuschak@yahoo.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

/* multiplexer per channel data */
काष्ठा i2c_mux_priv अणु
	काष्ठा i2c_adapter adap;
	काष्ठा i2c_algorithm algo;
	काष्ठा i2c_mux_core *muxc;
	u32 chan_id;
पूर्ण;

अटल पूर्णांक __i2c_mux_master_xfer(काष्ठा i2c_adapter *adap,
				 काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा i2c_mux_priv *priv = adap->algo_data;
	काष्ठा i2c_mux_core *muxc = priv->muxc;
	काष्ठा i2c_adapter *parent = muxc->parent;
	पूर्णांक ret;

	/* Switch to the right mux port and perक्रमm the transfer. */

	ret = muxc->select(muxc, priv->chan_id);
	अगर (ret >= 0)
		ret = __i2c_transfer(parent, msgs, num);
	अगर (muxc->deselect)
		muxc->deselect(muxc, priv->chan_id);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_mux_master_xfer(काष्ठा i2c_adapter *adap,
			       काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा i2c_mux_priv *priv = adap->algo_data;
	काष्ठा i2c_mux_core *muxc = priv->muxc;
	काष्ठा i2c_adapter *parent = muxc->parent;
	पूर्णांक ret;

	/* Switch to the right mux port and perक्रमm the transfer. */

	ret = muxc->select(muxc, priv->chan_id);
	अगर (ret >= 0)
		ret = i2c_transfer(parent, msgs, num);
	अगर (muxc->deselect)
		muxc->deselect(muxc, priv->chan_id);

	वापस ret;
पूर्ण

अटल पूर्णांक __i2c_mux_smbus_xfer(काष्ठा i2c_adapter *adap,
				u16 addr, अचिन्हित लघु flags,
				अक्षर पढ़ो_ग_लिखो, u8 command,
				पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा i2c_mux_priv *priv = adap->algo_data;
	काष्ठा i2c_mux_core *muxc = priv->muxc;
	काष्ठा i2c_adapter *parent = muxc->parent;
	पूर्णांक ret;

	/* Select the right mux port and perक्रमm the transfer. */

	ret = muxc->select(muxc, priv->chan_id);
	अगर (ret >= 0)
		ret = __i2c_smbus_xfer(parent, addr, flags,
				       पढ़ो_ग_लिखो, command, size, data);
	अगर (muxc->deselect)
		muxc->deselect(muxc, priv->chan_id);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_mux_smbus_xfer(काष्ठा i2c_adapter *adap,
			      u16 addr, अचिन्हित लघु flags,
			      अक्षर पढ़ो_ग_लिखो, u8 command,
			      पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा i2c_mux_priv *priv = adap->algo_data;
	काष्ठा i2c_mux_core *muxc = priv->muxc;
	काष्ठा i2c_adapter *parent = muxc->parent;
	पूर्णांक ret;

	/* Select the right mux port and perक्रमm the transfer. */

	ret = muxc->select(muxc, priv->chan_id);
	अगर (ret >= 0)
		ret = i2c_smbus_xfer(parent, addr, flags,
				     पढ़ो_ग_लिखो, command, size, data);
	अगर (muxc->deselect)
		muxc->deselect(muxc, priv->chan_id);

	वापस ret;
पूर्ण

/* Return the parent's functionality */
अटल u32 i2c_mux_functionality(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_mux_priv *priv = adap->algo_data;
	काष्ठा i2c_adapter *parent = priv->muxc->parent;

	वापस parent->algo->functionality(parent);
पूर्ण

/* Return all parent classes, merged */
अटल अचिन्हित पूर्णांक i2c_mux_parent_classes(काष्ठा i2c_adapter *parent)
अणु
	अचिन्हित पूर्णांक class = 0;

	करो अणु
		class |= parent->class;
		parent = i2c_parent_is_i2c_adapter(parent);
	पूर्ण जबतक (parent);

	वापस class;
पूर्ण

अटल व्योम i2c_mux_lock_bus(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i2c_mux_priv *priv = adapter->algo_data;
	काष्ठा i2c_adapter *parent = priv->muxc->parent;

	rt_mutex_lock_nested(&parent->mux_lock, i2c_adapter_depth(adapter));
	अगर (!(flags & I2C_LOCK_ROOT_ADAPTER))
		वापस;
	i2c_lock_bus(parent, flags);
पूर्ण

अटल पूर्णांक i2c_mux_trylock_bus(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i2c_mux_priv *priv = adapter->algo_data;
	काष्ठा i2c_adapter *parent = priv->muxc->parent;

	अगर (!rt_mutex_trylock(&parent->mux_lock))
		वापस 0;	/* mux_lock not locked, failure */
	अगर (!(flags & I2C_LOCK_ROOT_ADAPTER))
		वापस 1;	/* we only want mux_lock, success */
	अगर (i2c_trylock_bus(parent, flags))
		वापस 1;	/* parent locked too, success */
	rt_mutex_unlock(&parent->mux_lock);
	वापस 0;		/* parent not locked, failure */
पूर्ण

अटल व्योम i2c_mux_unlock_bus(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i2c_mux_priv *priv = adapter->algo_data;
	काष्ठा i2c_adapter *parent = priv->muxc->parent;

	अगर (flags & I2C_LOCK_ROOT_ADAPTER)
		i2c_unlock_bus(parent, flags);
	rt_mutex_unlock(&parent->mux_lock);
पूर्ण

अटल व्योम i2c_parent_lock_bus(काष्ठा i2c_adapter *adapter,
				अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i2c_mux_priv *priv = adapter->algo_data;
	काष्ठा i2c_adapter *parent = priv->muxc->parent;

	rt_mutex_lock_nested(&parent->mux_lock, i2c_adapter_depth(adapter));
	i2c_lock_bus(parent, flags);
पूर्ण

अटल पूर्णांक i2c_parent_trylock_bus(काष्ठा i2c_adapter *adapter,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i2c_mux_priv *priv = adapter->algo_data;
	काष्ठा i2c_adapter *parent = priv->muxc->parent;

	अगर (!rt_mutex_trylock(&parent->mux_lock))
		वापस 0;	/* mux_lock not locked, failure */
	अगर (i2c_trylock_bus(parent, flags))
		वापस 1;	/* parent locked too, success */
	rt_mutex_unlock(&parent->mux_lock);
	वापस 0;		/* parent not locked, failure */
पूर्ण

अटल व्योम i2c_parent_unlock_bus(काष्ठा i2c_adapter *adapter,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i2c_mux_priv *priv = adapter->algo_data;
	काष्ठा i2c_adapter *parent = priv->muxc->parent;

	i2c_unlock_bus(parent, flags);
	rt_mutex_unlock(&parent->mux_lock);
पूर्ण

काष्ठा i2c_adapter *i2c_root_adapter(काष्ठा device *dev)
अणु
	काष्ठा device *i2c;
	काष्ठा i2c_adapter *i2c_root;

	/*
	 * Walk up the device tree to find an i2c adapter, indicating
	 * that this is an i2c client device. Check all ancestors to
	 * handle mfd devices etc.
	 */
	क्रम (i2c = dev; i2c; i2c = i2c->parent) अणु
		अगर (i2c->type == &i2c_adapter_type)
			अवरोध;
	पूर्ण
	अगर (!i2c)
		वापस शून्य;

	/* Continue up the tree to find the root i2c adapter */
	i2c_root = to_i2c_adapter(i2c);
	जबतक (i2c_parent_is_i2c_adapter(i2c_root))
		i2c_root = i2c_parent_is_i2c_adapter(i2c_root);

	वापस i2c_root;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_root_adapter);

काष्ठा i2c_mux_core *i2c_mux_alloc(काष्ठा i2c_adapter *parent,
				   काष्ठा device *dev, पूर्णांक max_adapters,
				   पूर्णांक माप_priv, u32 flags,
				   पूर्णांक (*select)(काष्ठा i2c_mux_core *, u32),
				   पूर्णांक (*deselect)(काष्ठा i2c_mux_core *, u32))
अणु
	काष्ठा i2c_mux_core *muxc;

	muxc = devm_kzalloc(dev, काष्ठा_size(muxc, adapter, max_adapters)
			    + माप_priv, GFP_KERNEL);
	अगर (!muxc)
		वापस शून्य;
	अगर (माप_priv)
		muxc->priv = &muxc->adapter[max_adapters];

	muxc->parent = parent;
	muxc->dev = dev;
	अगर (flags & I2C_MUX_LOCKED)
		muxc->mux_locked = true;
	अगर (flags & I2C_MUX_ARBITRATOR)
		muxc->arbitrator = true;
	अगर (flags & I2C_MUX_GATE)
		muxc->gate = true;
	muxc->select = select;
	muxc->deselect = deselect;
	muxc->max_adapters = max_adapters;

	वापस muxc;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_mux_alloc);

अटल स्थिर काष्ठा i2c_lock_operations i2c_mux_lock_ops = अणु
	.lock_bus =    i2c_mux_lock_bus,
	.trylock_bus = i2c_mux_trylock_bus,
	.unlock_bus =  i2c_mux_unlock_bus,
पूर्ण;

अटल स्थिर काष्ठा i2c_lock_operations i2c_parent_lock_ops = अणु
	.lock_bus =    i2c_parent_lock_bus,
	.trylock_bus = i2c_parent_trylock_bus,
	.unlock_bus =  i2c_parent_unlock_bus,
पूर्ण;

पूर्णांक i2c_mux_add_adapter(काष्ठा i2c_mux_core *muxc,
			u32 क्रमce_nr, u32 chan_id,
			अचिन्हित पूर्णांक class)
अणु
	काष्ठा i2c_adapter *parent = muxc->parent;
	काष्ठा i2c_mux_priv *priv;
	अक्षर symlink_name[20];
	पूर्णांक ret;

	अगर (muxc->num_adapters >= muxc->max_adapters) अणु
		dev_err(muxc->dev, "No room for more i2c-mux adapters\n");
		वापस -EINVAL;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Set up निजी adapter data */
	priv->muxc = muxc;
	priv->chan_id = chan_id;

	/* Need to करो algo dynamically because we करोn't know ahead
	 * of समय what sort of physical adapter we'll be dealing with.
	 */
	अगर (parent->algo->master_xfer) अणु
		अगर (muxc->mux_locked)
			priv->algo.master_xfer = i2c_mux_master_xfer;
		अन्यथा
			priv->algo.master_xfer = __i2c_mux_master_xfer;
	पूर्ण
	अगर (parent->algo->master_xfer_atomic)
		priv->algo.master_xfer_atomic = priv->algo.master_xfer;

	अगर (parent->algo->smbus_xfer) अणु
		अगर (muxc->mux_locked)
			priv->algo.smbus_xfer = i2c_mux_smbus_xfer;
		अन्यथा
			priv->algo.smbus_xfer = __i2c_mux_smbus_xfer;
	पूर्ण
	अगर (parent->algo->smbus_xfer_atomic)
		priv->algo.smbus_xfer_atomic = priv->algo.smbus_xfer;

	priv->algo.functionality = i2c_mux_functionality;

	/* Now fill out new adapter काष्ठाure */
	snम_लिखो(priv->adap.name, माप(priv->adap.name),
		 "i2c-%d-mux (chan_id %d)", i2c_adapter_id(parent), chan_id);
	priv->adap.owner = THIS_MODULE;
	priv->adap.algo = &priv->algo;
	priv->adap.algo_data = priv;
	priv->adap.dev.parent = &parent->dev;
	priv->adap.retries = parent->retries;
	priv->adap.समयout = parent->समयout;
	priv->adap.quirks = parent->quirks;
	अगर (muxc->mux_locked)
		priv->adap.lock_ops = &i2c_mux_lock_ops;
	अन्यथा
		priv->adap.lock_ops = &i2c_parent_lock_ops;

	/* Sanity check on class */
	अगर (i2c_mux_parent_classes(parent) & class)
		dev_err(&parent->dev,
			"Segment %d behind mux can't share classes with ancestors\n",
			chan_id);
	अन्यथा
		priv->adap.class = class;

	/*
	 * Try to populate the mux adapter's of_node, expands to
	 * nothing अगर !CONFIG_OF.
	 */
	अगर (muxc->dev->of_node) अणु
		काष्ठा device_node *dev_node = muxc->dev->of_node;
		काष्ठा device_node *mux_node, *child = शून्य;
		u32 reg;

		अगर (muxc->arbitrator)
			mux_node = of_get_child_by_name(dev_node, "i2c-arb");
		अन्यथा अगर (muxc->gate)
			mux_node = of_get_child_by_name(dev_node, "i2c-gate");
		अन्यथा
			mux_node = of_get_child_by_name(dev_node, "i2c-mux");

		अगर (mux_node) अणु
			/* A "reg" property indicates an old-style DT entry */
			अगर (!of_property_पढ़ो_u32(mux_node, "reg", &reg)) अणु
				of_node_put(mux_node);
				mux_node = शून्य;
			पूर्ण
		पूर्ण

		अगर (!mux_node)
			mux_node = of_node_get(dev_node);
		अन्यथा अगर (muxc->arbitrator || muxc->gate)
			child = of_node_get(mux_node);

		अगर (!child) अणु
			क्रम_each_child_of_node(mux_node, child) अणु
				ret = of_property_पढ़ो_u32(child, "reg", &reg);
				अगर (ret)
					जारी;
				अगर (chan_id == reg)
					अवरोध;
			पूर्ण
		पूर्ण

		priv->adap.dev.of_node = child;
		of_node_put(mux_node);
	पूर्ण

	/*
	 * Associate the mux channel with an ACPI node.
	 */
	अगर (has_acpi_companion(muxc->dev))
		acpi_preset_companion(&priv->adap.dev,
				      ACPI_COMPANION(muxc->dev),
				      chan_id);

	अगर (क्रमce_nr) अणु
		priv->adap.nr = क्रमce_nr;
		ret = i2c_add_numbered_adapter(&priv->adap);
		अगर (ret < 0) अणु
			dev_err(&parent->dev,
				"failed to add mux-adapter %u as bus %u (error=%d)\n",
				chan_id, क्रमce_nr, ret);
			जाओ err_मुक्त_priv;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = i2c_add_adapter(&priv->adap);
		अगर (ret < 0) अणु
			dev_err(&parent->dev,
				"failed to add mux-adapter %u (error=%d)\n",
				chan_id, ret);
			जाओ err_मुक्त_priv;
		पूर्ण
	पूर्ण

	WARN(sysfs_create_link(&priv->adap.dev.kobj, &muxc->dev->kobj,
			       "mux_device"),
	     "can't create symlink to mux device\n");

	snम_लिखो(symlink_name, माप(symlink_name), "channel-%u", chan_id);
	WARN(sysfs_create_link(&muxc->dev->kobj, &priv->adap.dev.kobj,
			       symlink_name),
	     "can't create symlink to channel %u\n", chan_id);
	dev_info(&parent->dev, "Added multiplexed i2c bus %d\n",
		 i2c_adapter_id(&priv->adap));

	muxc->adapter[muxc->num_adapters++] = &priv->adap;
	वापस 0;

err_मुक्त_priv:
	kमुक्त(priv);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_mux_add_adapter);

व्योम i2c_mux_del_adapters(काष्ठा i2c_mux_core *muxc)
अणु
	अक्षर symlink_name[20];

	जबतक (muxc->num_adapters) अणु
		काष्ठा i2c_adapter *adap = muxc->adapter[--muxc->num_adapters];
		काष्ठा i2c_mux_priv *priv = adap->algo_data;
		काष्ठा device_node *np = adap->dev.of_node;

		muxc->adapter[muxc->num_adapters] = शून्य;

		snम_लिखो(symlink_name, माप(symlink_name),
			 "channel-%u", priv->chan_id);
		sysfs_हटाओ_link(&muxc->dev->kobj, symlink_name);

		sysfs_हटाओ_link(&priv->adap.dev.kobj, "mux_device");
		i2c_del_adapter(adap);
		of_node_put(np);
		kमुक्त(priv);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(i2c_mux_del_adapters);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("I2C driver for multiplexed I2C busses");
MODULE_LICENSE("GPL v2");
