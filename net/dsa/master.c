<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Handling of a master device, चयनing frames via its चयन fabric CPU port
 *
 * Copyright (c) 2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#समावेश "dsa_priv.h"

अटल पूर्णांक dsa_master_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	स्थिर काष्ठा ethtool_ops *ops = cpu_dp->orig_ethtool_ops;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	पूर्णांक port = cpu_dp->index;
	पूर्णांक ret = 0;
	पूर्णांक len;

	अगर (ops->get_regs_len) अणु
		len = ops->get_regs_len(dev);
		अगर (len < 0)
			वापस len;
		ret += len;
	पूर्ण

	ret += माप(काष्ठा ethtool_drvinfo);
	ret += माप(काष्ठा ethtool_regs);

	अगर (ds->ops->get_regs_len) अणु
		len = ds->ops->get_regs_len(ds, port);
		अगर (len < 0)
			वापस len;
		ret += len;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dsa_master_get_regs(काष्ठा net_device *dev,
				काष्ठा ethtool_regs *regs, व्योम *data)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	स्थिर काष्ठा ethtool_ops *ops = cpu_dp->orig_ethtool_ops;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	काष्ठा ethtool_drvinfo *cpu_info;
	काष्ठा ethtool_regs *cpu_regs;
	पूर्णांक port = cpu_dp->index;
	पूर्णांक len;

	अगर (ops->get_regs_len && ops->get_regs) अणु
		len = ops->get_regs_len(dev);
		अगर (len < 0)
			वापस;
		regs->len = len;
		ops->get_regs(dev, regs, data);
		data += regs->len;
	पूर्ण

	cpu_info = (काष्ठा ethtool_drvinfo *)data;
	strlcpy(cpu_info->driver, "dsa", माप(cpu_info->driver));
	data += माप(*cpu_info);
	cpu_regs = (काष्ठा ethtool_regs *)data;
	data += माप(*cpu_regs);

	अगर (ds->ops->get_regs_len && ds->ops->get_regs) अणु
		len = ds->ops->get_regs_len(ds, port);
		अगर (len < 0)
			वापस;
		cpu_regs->len = len;
		ds->ops->get_regs(ds, port, cpu_regs, data);
	पूर्ण
पूर्ण

अटल व्योम dsa_master_get_ethtool_stats(काष्ठा net_device *dev,
					 काष्ठा ethtool_stats *stats,
					 uपूर्णांक64_t *data)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	स्थिर काष्ठा ethtool_ops *ops = cpu_dp->orig_ethtool_ops;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	पूर्णांक port = cpu_dp->index;
	पूर्णांक count = 0;

	अगर (ops->get_sset_count && ops->get_ethtool_stats) अणु
		count = ops->get_sset_count(dev, ETH_SS_STATS);
		ops->get_ethtool_stats(dev, stats, data);
	पूर्ण

	अगर (ds->ops->get_ethtool_stats)
		ds->ops->get_ethtool_stats(ds, port, data + count);
पूर्ण

अटल व्योम dsa_master_get_ethtool_phy_stats(काष्ठा net_device *dev,
					     काष्ठा ethtool_stats *stats,
					     uपूर्णांक64_t *data)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	स्थिर काष्ठा ethtool_ops *ops = cpu_dp->orig_ethtool_ops;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	पूर्णांक port = cpu_dp->index;
	पूर्णांक count = 0;

	अगर (dev->phydev && !ops->get_ethtool_phy_stats) अणु
		count = phy_ethtool_get_sset_count(dev->phydev);
		अगर (count >= 0)
			phy_ethtool_get_stats(dev->phydev, stats, data);
	पूर्ण अन्यथा अगर (ops->get_sset_count && ops->get_ethtool_phy_stats) अणु
		count = ops->get_sset_count(dev, ETH_SS_PHY_STATS);
		ops->get_ethtool_phy_stats(dev, stats, data);
	पूर्ण

	अगर (count < 0)
		count = 0;

	अगर (ds->ops->get_ethtool_phy_stats)
		ds->ops->get_ethtool_phy_stats(ds, port, data + count);
पूर्ण

अटल पूर्णांक dsa_master_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	स्थिर काष्ठा ethtool_ops *ops = cpu_dp->orig_ethtool_ops;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	पूर्णांक count = 0;

	अगर (sset == ETH_SS_PHY_STATS && dev->phydev &&
	    !ops->get_ethtool_phy_stats)
		count = phy_ethtool_get_sset_count(dev->phydev);
	अन्यथा अगर (ops->get_sset_count)
		count = ops->get_sset_count(dev, sset);

	अगर (count < 0)
		count = 0;

	अगर (ds->ops->get_sset_count)
		count += ds->ops->get_sset_count(ds, cpu_dp->index, sset);

	वापस count;
पूर्ण

अटल व्योम dsa_master_get_strings(काष्ठा net_device *dev, uपूर्णांक32_t stringset,
				   uपूर्णांक8_t *data)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	स्थिर काष्ठा ethtool_ops *ops = cpu_dp->orig_ethtool_ops;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	पूर्णांक port = cpu_dp->index;
	पूर्णांक len = ETH_GSTRING_LEN;
	पूर्णांक mcount = 0, count, i;
	uपूर्णांक8_t pfx[4];
	uपूर्णांक8_t *ndata;

	snम_लिखो(pfx, माप(pfx), "p%.2d", port);
	/* We करो not want to be शून्य-terminated, since this is a prefix */
	pfx[माप(pfx) - 1] = '_';

	अगर (stringset == ETH_SS_PHY_STATS && dev->phydev &&
	    !ops->get_ethtool_phy_stats) अणु
		mcount = phy_ethtool_get_sset_count(dev->phydev);
		अगर (mcount < 0)
			mcount = 0;
		अन्यथा
			phy_ethtool_get_strings(dev->phydev, data);
	पूर्ण अन्यथा अगर (ops->get_sset_count && ops->get_strings) अणु
		mcount = ops->get_sset_count(dev, stringset);
		अगर (mcount < 0)
			mcount = 0;
		ops->get_strings(dev, stringset, data);
	पूर्ण

	अगर (ds->ops->get_strings) अणु
		ndata = data + mcount * len;
		/* This function copies ETH_GSTRINGS_LEN bytes, we will mangle
		 * the output after to prepend our CPU port prefix we
		 * स्थिरructed earlier
		 */
		ds->ops->get_strings(ds, port, stringset, ndata);
		count = ds->ops->get_sset_count(ds, port, stringset);
		अगर (count < 0)
			वापस;
		क्रम (i = 0; i < count; i++) अणु
			स_हटाओ(ndata + (i * len + माप(pfx)),
				ndata + i * len, len - माप(pfx));
			स_नकल(ndata + i * len, pfx, माप(pfx));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dsa_master_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	काष्ठा dsa_चयन_tree *dst;
	पूर्णांक err = -EOPNOTSUPP;
	काष्ठा dsa_port *dp;

	dst = ds->dst;

	चयन (cmd) अणु
	हाल SIOCGHWTSTAMP:
	हाल SIOCSHWTSTAMP:
		/* Deny PTP operations on master अगर there is at least one
		 * चयन in the tree that is PTP capable.
		 */
		list_क्रम_each_entry(dp, &dst->ports, list)
			अगर (dp->ds->ops->port_hwtstamp_get ||
			    dp->ds->ops->port_hwtstamp_set)
				वापस -EBUSY;
		अवरोध;
	पूर्ण

	अगर (dev->netdev_ops->nकरो_करो_ioctl)
		err = dev->netdev_ops->nकरो_करो_ioctl(dev, अगरr, cmd);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dsa_netdevice_ops dsa_netdev_ops = अणु
	.nकरो_करो_ioctl = dsa_master_ioctl,
पूर्ण;

अटल पूर्णांक dsa_master_ethtool_setup(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	काष्ठा ethtool_ops *ops;

	ops = devm_kzalloc(ds->dev, माप(*ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	cpu_dp->orig_ethtool_ops = dev->ethtool_ops;
	अगर (cpu_dp->orig_ethtool_ops)
		स_नकल(ops, cpu_dp->orig_ethtool_ops, माप(*ops));

	ops->get_regs_len = dsa_master_get_regs_len;
	ops->get_regs = dsa_master_get_regs;
	ops->get_sset_count = dsa_master_get_sset_count;
	ops->get_ethtool_stats = dsa_master_get_ethtool_stats;
	ops->get_strings = dsa_master_get_strings;
	ops->get_ethtool_phy_stats = dsa_master_get_ethtool_phy_stats;

	dev->ethtool_ops = ops;

	वापस 0;
पूर्ण

अटल व्योम dsa_master_ethtool_tearकरोwn(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;

	dev->ethtool_ops = cpu_dp->orig_ethtool_ops;
	cpu_dp->orig_ethtool_ops = शून्य;
पूर्ण

अटल व्योम dsa_netdev_ops_set(काष्ठा net_device *dev,
			       स्थिर काष्ठा dsa_netdevice_ops *ops)
अणु
	dev->dsa_ptr->netdev_ops = ops;
पूर्ण

अटल व्योम dsa_master_set_promiscuity(काष्ठा net_device *dev, पूर्णांक inc)
अणु
	स्थिर काष्ठा dsa_device_ops *ops = dev->dsa_ptr->tag_ops;

	अगर (!ops->promisc_on_master)
		वापस;

	rtnl_lock();
	dev_set_promiscuity(dev, inc);
	rtnl_unlock();
पूर्ण

अटल sमाप_प्रकार tagging_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;

	वापस प्र_लिखो(buf, "%s\n",
		       dsa_tag_protocol_to_str(cpu_dp->tag_ops));
पूर्ण

अटल sमाप_प्रकार tagging_store(काष्ठा device *d, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	स्थिर काष्ठा dsa_device_ops *new_tag_ops, *old_tag_ops;
	काष्ठा net_device *dev = to_net_dev(d);
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	पूर्णांक err;

	old_tag_ops = cpu_dp->tag_ops;
	new_tag_ops = dsa_find_tagger_by_name(buf);
	/* Bad tagger name, or module is not loaded? */
	अगर (IS_ERR(new_tag_ops))
		वापस PTR_ERR(new_tag_ops);

	अगर (new_tag_ops == old_tag_ops)
		/* Drop the temporarily held duplicate reference, since
		 * the DSA चयन tree uses this tagger.
		 */
		जाओ out;

	err = dsa_tree_change_tag_proto(cpu_dp->ds->dst, dev, new_tag_ops,
					old_tag_ops);
	अगर (err) अणु
		/* On failure the old tagger is restored, so we करोn't need the
		 * driver क्रम the new one.
		 */
		dsa_tag_driver_put(new_tag_ops);
		वापस err;
	पूर्ण

	/* On success we no दीर्घer need the module क्रम the old tagging protocol
	 */
out:
	dsa_tag_driver_put(old_tag_ops);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(tagging);

अटल काष्ठा attribute *dsa_slave_attrs[] = अणु
	&dev_attr_tagging.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dsa_group = अणु
	.name	= "dsa",
	.attrs	= dsa_slave_attrs,
पूर्ण;

अटल व्योम dsa_master_reset_mtu(काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = dev_set_mtu(dev, ETH_DATA_LEN);
	अगर (err)
		netdev_dbg(dev,
			   "Unable to reset MTU to exclude DSA overheads\n");
	rtnl_unlock();
पूर्ण

अटल काष्ठा lock_class_key dsa_master_addr_list_lock_key;

पूर्णांक dsa_master_setup(काष्ठा net_device *dev, काष्ठा dsa_port *cpu_dp)
अणु
	पूर्णांक mtu = ETH_DATA_LEN + cpu_dp->tag_ops->overhead;
	काष्ठा dsa_चयन *ds = cpu_dp->ds;
	काष्ठा device_link *consumer_link;
	पूर्णांक ret;

	/* The DSA master must use SET_NETDEV_DEV क्रम this to work. */
	consumer_link = device_link_add(ds->dev, dev->dev.parent,
					DL_FLAG_AUTOREMOVE_CONSUMER);
	अगर (!consumer_link)
		netdev_err(dev,
			   "Failed to create a device link to DSA switch %s\n",
			   dev_name(ds->dev));

	rtnl_lock();
	ret = dev_set_mtu(dev, mtu);
	rtnl_unlock();
	अगर (ret)
		netdev_warn(dev, "error %d setting MTU to %d to include DSA overhead\n",
			    ret, mtu);

	/* If we use a tagging क्रमmat that करोesn't have an ethertype
	 * field, make sure that all packets from this poपूर्णांक on get
	 * sent to the tag क्रमmat's receive function.
	 */
	wmb();

	dev->dsa_ptr = cpu_dp;
	lockdep_set_class(&dev->addr_list_lock,
			  &dsa_master_addr_list_lock_key);

	dsa_master_set_promiscuity(dev, 1);

	ret = dsa_master_ethtool_setup(dev);
	अगर (ret)
		जाओ out_err_reset_promisc;

	dsa_netdev_ops_set(dev, &dsa_netdev_ops);

	ret = sysfs_create_group(&dev->dev.kobj, &dsa_group);
	अगर (ret)
		जाओ out_err_nकरो_tearकरोwn;

	वापस ret;

out_err_nकरो_tearकरोwn:
	dsa_netdev_ops_set(dev, शून्य);
	dsa_master_ethtool_tearकरोwn(dev);
out_err_reset_promisc:
	dsa_master_set_promiscuity(dev, -1);
	वापस ret;
पूर्ण

व्योम dsa_master_tearकरोwn(काष्ठा net_device *dev)
अणु
	sysfs_हटाओ_group(&dev->dev.kobj, &dsa_group);
	dsa_netdev_ops_set(dev, शून्य);
	dsa_master_ethtool_tearकरोwn(dev);
	dsa_master_reset_mtu(dev);
	dsa_master_set_promiscuity(dev, -1);

	dev->dsa_ptr = शून्य;

	/* If we used a tagging क्रमmat that करोesn't have an ethertype
	 * field, make sure that all packets from this poपूर्णांक get sent
	 * without the tag and go through the regular receive path.
	 */
	wmb();
पूर्ण
