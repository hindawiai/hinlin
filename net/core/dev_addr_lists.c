<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/core/dev_addr_lists.c - Functions क्रम handling net device lists
 * Copyright (c) 2010 Jiri Pirko <jpirko@redhat.com>
 *
 * This file contains functions क्रम working with unicast, multicast and device
 * addresses lists.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>

/*
 * General list handling functions
 */

अटल पूर्णांक __hw_addr_create_ex(काष्ठा netdev_hw_addr_list *list,
			       स्थिर अचिन्हित अक्षर *addr, पूर्णांक addr_len,
			       अचिन्हित अक्षर addr_type, bool global,
			       bool sync)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक alloc_size;

	alloc_size = माप(*ha);
	अगर (alloc_size < L1_CACHE_BYTES)
		alloc_size = L1_CACHE_BYTES;
	ha = kदो_स्मृति(alloc_size, GFP_ATOMIC);
	अगर (!ha)
		वापस -ENOMEM;
	स_नकल(ha->addr, addr, addr_len);
	ha->type = addr_type;
	ha->refcount = 1;
	ha->global_use = global;
	ha->synced = sync ? 1 : 0;
	ha->sync_cnt = 0;
	list_add_tail_rcu(&ha->list, &list->list);
	list->count++;

	वापस 0;
पूर्ण

अटल पूर्णांक __hw_addr_add_ex(काष्ठा netdev_hw_addr_list *list,
			    स्थिर अचिन्हित अक्षर *addr, पूर्णांक addr_len,
			    अचिन्हित अक्षर addr_type, bool global, bool sync,
			    पूर्णांक sync_count)
अणु
	काष्ठा netdev_hw_addr *ha;

	अगर (addr_len > MAX_ADDR_LEN)
		वापस -EINVAL;

	list_क्रम_each_entry(ha, &list->list, list) अणु
		अगर (ha->type == addr_type &&
		    !स_भेद(ha->addr, addr, addr_len)) अणु
			अगर (global) अणु
				/* check अगर addr is alपढ़ोy used as global */
				अगर (ha->global_use)
					वापस 0;
				अन्यथा
					ha->global_use = true;
			पूर्ण
			अगर (sync) अणु
				अगर (ha->synced && sync_count)
					वापस -EEXIST;
				अन्यथा
					ha->synced++;
			पूर्ण
			ha->refcount++;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस __hw_addr_create_ex(list, addr, addr_len, addr_type, global,
				   sync);
पूर्ण

अटल पूर्णांक __hw_addr_add(काष्ठा netdev_hw_addr_list *list,
			 स्थिर अचिन्हित अक्षर *addr, पूर्णांक addr_len,
			 अचिन्हित अक्षर addr_type)
अणु
	वापस __hw_addr_add_ex(list, addr, addr_len, addr_type, false, false,
				0);
पूर्ण

अटल पूर्णांक __hw_addr_del_entry(काष्ठा netdev_hw_addr_list *list,
			       काष्ठा netdev_hw_addr *ha, bool global,
			       bool sync)
अणु
	अगर (global && !ha->global_use)
		वापस -ENOENT;

	अगर (sync && !ha->synced)
		वापस -ENOENT;

	अगर (global)
		ha->global_use = false;

	अगर (sync)
		ha->synced--;

	अगर (--ha->refcount)
		वापस 0;
	list_del_rcu(&ha->list);
	kमुक्त_rcu(ha, rcu_head);
	list->count--;
	वापस 0;
पूर्ण

अटल पूर्णांक __hw_addr_del_ex(काष्ठा netdev_hw_addr_list *list,
			    स्थिर अचिन्हित अक्षर *addr, पूर्णांक addr_len,
			    अचिन्हित अक्षर addr_type, bool global, bool sync)
अणु
	काष्ठा netdev_hw_addr *ha;

	list_क्रम_each_entry(ha, &list->list, list) अणु
		अगर (!स_भेद(ha->addr, addr, addr_len) &&
		    (ha->type == addr_type || !addr_type))
			वापस __hw_addr_del_entry(list, ha, global, sync);
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक __hw_addr_del(काष्ठा netdev_hw_addr_list *list,
			 स्थिर अचिन्हित अक्षर *addr, पूर्णांक addr_len,
			 अचिन्हित अक्षर addr_type)
अणु
	वापस __hw_addr_del_ex(list, addr, addr_len, addr_type, false, false);
पूर्ण

अटल पूर्णांक __hw_addr_sync_one(काष्ठा netdev_hw_addr_list *to_list,
			       काष्ठा netdev_hw_addr *ha,
			       पूर्णांक addr_len)
अणु
	पूर्णांक err;

	err = __hw_addr_add_ex(to_list, ha->addr, addr_len, ha->type,
			       false, true, ha->sync_cnt);
	अगर (err && err != -EEXIST)
		वापस err;

	अगर (!err) अणु
		ha->sync_cnt++;
		ha->refcount++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __hw_addr_unsync_one(काष्ठा netdev_hw_addr_list *to_list,
				 काष्ठा netdev_hw_addr_list *from_list,
				 काष्ठा netdev_hw_addr *ha,
				 पूर्णांक addr_len)
अणु
	पूर्णांक err;

	err = __hw_addr_del_ex(to_list, ha->addr, addr_len, ha->type,
			       false, true);
	अगर (err)
		वापस;
	ha->sync_cnt--;
	/* address on from list is not marked synced */
	__hw_addr_del_entry(from_list, ha, false, false);
पूर्ण

अटल पूर्णांक __hw_addr_sync_multiple(काष्ठा netdev_hw_addr_list *to_list,
				   काष्ठा netdev_hw_addr_list *from_list,
				   पूर्णांक addr_len)
अणु
	पूर्णांक err = 0;
	काष्ठा netdev_hw_addr *ha, *पंचांगp;

	list_क्रम_each_entry_safe(ha, पंचांगp, &from_list->list, list) अणु
		अगर (ha->sync_cnt == ha->refcount) अणु
			__hw_addr_unsync_one(to_list, from_list, ha, addr_len);
		पूर्ण अन्यथा अणु
			err = __hw_addr_sync_one(to_list, ha, addr_len);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* This function only works where there is a strict 1-1 relationship
 * between source and destionation of they synch. If you ever need to
 * sync addresses to more then 1 destination, you need to use
 * __hw_addr_sync_multiple().
 */
पूर्णांक __hw_addr_sync(काष्ठा netdev_hw_addr_list *to_list,
		   काष्ठा netdev_hw_addr_list *from_list,
		   पूर्णांक addr_len)
अणु
	पूर्णांक err = 0;
	काष्ठा netdev_hw_addr *ha, *पंचांगp;

	list_क्रम_each_entry_safe(ha, पंचांगp, &from_list->list, list) अणु
		अगर (!ha->sync_cnt) अणु
			err = __hw_addr_sync_one(to_list, ha, addr_len);
			अगर (err)
				अवरोध;
		पूर्ण अन्यथा अगर (ha->refcount == 1)
			__hw_addr_unsync_one(to_list, from_list, ha, addr_len);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(__hw_addr_sync);

व्योम __hw_addr_unsync(काष्ठा netdev_hw_addr_list *to_list,
		      काष्ठा netdev_hw_addr_list *from_list,
		      पूर्णांक addr_len)
अणु
	काष्ठा netdev_hw_addr *ha, *पंचांगp;

	list_क्रम_each_entry_safe(ha, पंचांगp, &from_list->list, list) अणु
		अगर (ha->sync_cnt)
			__hw_addr_unsync_one(to_list, from_list, ha, addr_len);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__hw_addr_unsync);

/**
 *  __hw_addr_sync_dev - Synchonize device's multicast list
 *  @list: address list to syncronize
 *  @dev:  device to sync
 *  @sync: function to call अगर address should be added
 *  @unsync: function to call अगर address should be हटाओd
 *
 *  This function is पूर्णांकended to be called from the nकरो_set_rx_mode
 *  function of devices that require explicit address add/हटाओ
 *  notअगरications.  The unsync function may be शून्य in which हाल
 *  the addresses requiring removal will simply be हटाओd without
 *  any notअगरication to the device.
 **/
पूर्णांक __hw_addr_sync_dev(काष्ठा netdev_hw_addr_list *list,
		       काष्ठा net_device *dev,
		       पूर्णांक (*sync)(काष्ठा net_device *, स्थिर अचिन्हित अक्षर *),
		       पूर्णांक (*unsync)(काष्ठा net_device *,
				     स्थिर अचिन्हित अक्षर *))
अणु
	काष्ठा netdev_hw_addr *ha, *पंचांगp;
	पूर्णांक err;

	/* first go through and flush out any stale entries */
	list_क्रम_each_entry_safe(ha, पंचांगp, &list->list, list) अणु
		अगर (!ha->sync_cnt || ha->refcount != 1)
			जारी;

		/* अगर unsync is defined and fails defer unsyncing address */
		अगर (unsync && unsync(dev, ha->addr))
			जारी;

		ha->sync_cnt--;
		__hw_addr_del_entry(list, ha, false, false);
	पूर्ण

	/* go through and sync new entries to the list */
	list_क्रम_each_entry_safe(ha, पंचांगp, &list->list, list) अणु
		अगर (ha->sync_cnt)
			जारी;

		err = sync(dev, ha->addr);
		अगर (err)
			वापस err;

		ha->sync_cnt++;
		ha->refcount++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__hw_addr_sync_dev);

/**
 *  __hw_addr_ref_sync_dev - Synchronize device's multicast address list taking
 *  पूर्णांकo account references
 *  @list: address list to synchronize
 *  @dev:  device to sync
 *  @sync: function to call अगर address or reference on it should be added
 *  @unsync: function to call अगर address or some reference on it should हटाओd
 *
 *  This function is पूर्णांकended to be called from the nकरो_set_rx_mode
 *  function of devices that require explicit address or references on it
 *  add/हटाओ notअगरications. The unsync function may be शून्य in which हाल
 *  the addresses or references on it requiring removal will simply be
 *  हटाओd without any notअगरication to the device. That is responsibility of
 *  the driver to identअगरy and distribute address or references on it between
 *  पूर्णांकernal address tables.
 **/
पूर्णांक __hw_addr_ref_sync_dev(काष्ठा netdev_hw_addr_list *list,
			   काष्ठा net_device *dev,
			   पूर्णांक (*sync)(काष्ठा net_device *,
				       स्थिर अचिन्हित अक्षर *, पूर्णांक),
			   पूर्णांक (*unsync)(काष्ठा net_device *,
					 स्थिर अचिन्हित अक्षर *, पूर्णांक))
अणु
	काष्ठा netdev_hw_addr *ha, *पंचांगp;
	पूर्णांक err, ref_cnt;

	/* first go through and flush out any unsynced/stale entries */
	list_क्रम_each_entry_safe(ha, पंचांगp, &list->list, list) अणु
		/* sync अगर address is not used */
		अगर ((ha->sync_cnt << 1) <= ha->refcount)
			जारी;

		/* अगर fails defer unsyncing address */
		ref_cnt = ha->refcount - ha->sync_cnt;
		अगर (unsync && unsync(dev, ha->addr, ref_cnt))
			जारी;

		ha->refcount = (ref_cnt << 1) + 1;
		ha->sync_cnt = ref_cnt;
		__hw_addr_del_entry(list, ha, false, false);
	पूर्ण

	/* go through and sync updated/new entries to the list */
	list_क्रम_each_entry_safe(ha, पंचांगp, &list->list, list) अणु
		/* sync अगर address added or reused */
		अगर ((ha->sync_cnt << 1) >= ha->refcount)
			जारी;

		ref_cnt = ha->refcount - ha->sync_cnt;
		err = sync(dev, ha->addr, ref_cnt);
		अगर (err)
			वापस err;

		ha->refcount = ref_cnt << 1;
		ha->sync_cnt = ref_cnt;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__hw_addr_ref_sync_dev);

/**
 *  __hw_addr_ref_unsync_dev - Remove synchronized addresses and references on
 *  it from device
 *  @list: address list to हटाओ synchronized addresses (references on it) from
 *  @dev:  device to sync
 *  @unsync: function to call अगर address and references on it should be हटाओd
 *
 *  Remove all addresses that were added to the device by
 *  __hw_addr_ref_sync_dev(). This function is पूर्णांकended to be called from the
 *  nकरो_stop or nकरो_खोलो functions on devices that require explicit address (or
 *  references on it) add/हटाओ notअगरications. If the unsync function poपूर्णांकer
 *  is शून्य then this function can be used to just reset the sync_cnt क्रम the
 *  addresses in the list.
 **/
व्योम __hw_addr_ref_unsync_dev(काष्ठा netdev_hw_addr_list *list,
			      काष्ठा net_device *dev,
			      पूर्णांक (*unsync)(काष्ठा net_device *,
					    स्थिर अचिन्हित अक्षर *, पूर्णांक))
अणु
	काष्ठा netdev_hw_addr *ha, *पंचांगp;

	list_क्रम_each_entry_safe(ha, पंचांगp, &list->list, list) अणु
		अगर (!ha->sync_cnt)
			जारी;

		/* अगर fails defer unsyncing address */
		अगर (unsync && unsync(dev, ha->addr, ha->sync_cnt))
			जारी;

		ha->refcount -= ha->sync_cnt - 1;
		ha->sync_cnt = 0;
		__hw_addr_del_entry(list, ha, false, false);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__hw_addr_ref_unsync_dev);

/**
 *  __hw_addr_unsync_dev - Remove synchronized addresses from device
 *  @list: address list to हटाओ synchronized addresses from
 *  @dev:  device to sync
 *  @unsync: function to call अगर address should be हटाओd
 *
 *  Remove all addresses that were added to the device by __hw_addr_sync_dev().
 *  This function is पूर्णांकended to be called from the nकरो_stop or nकरो_खोलो
 *  functions on devices that require explicit address add/हटाओ
 *  notअगरications.  If the unsync function poपूर्णांकer is शून्य then this function
 *  can be used to just reset the sync_cnt क्रम the addresses in the list.
 **/
व्योम __hw_addr_unsync_dev(काष्ठा netdev_hw_addr_list *list,
			  काष्ठा net_device *dev,
			  पूर्णांक (*unsync)(काष्ठा net_device *,
					स्थिर अचिन्हित अक्षर *))
अणु
	काष्ठा netdev_hw_addr *ha, *पंचांगp;

	list_क्रम_each_entry_safe(ha, पंचांगp, &list->list, list) अणु
		अगर (!ha->sync_cnt)
			जारी;

		/* अगर unsync is defined and fails defer unsyncing address */
		अगर (unsync && unsync(dev, ha->addr))
			जारी;

		ha->sync_cnt--;
		__hw_addr_del_entry(list, ha, false, false);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__hw_addr_unsync_dev);

अटल व्योम __hw_addr_flush(काष्ठा netdev_hw_addr_list *list)
अणु
	काष्ठा netdev_hw_addr *ha, *पंचांगp;

	list_क्रम_each_entry_safe(ha, पंचांगp, &list->list, list) अणु
		list_del_rcu(&ha->list);
		kमुक्त_rcu(ha, rcu_head);
	पूर्ण
	list->count = 0;
पूर्ण

व्योम __hw_addr_init(काष्ठा netdev_hw_addr_list *list)
अणु
	INIT_LIST_HEAD(&list->list);
	list->count = 0;
पूर्ण
EXPORT_SYMBOL(__hw_addr_init);

/*
 * Device addresses handling functions
 */

/**
 *	dev_addr_flush - Flush device address list
 *	@dev: device
 *
 *	Flush device address list and reset ->dev_addr.
 *
 *	The caller must hold the rtnl_mutex.
 */
व्योम dev_addr_flush(काष्ठा net_device *dev)
अणु
	/* rtnl_mutex must be held here */

	__hw_addr_flush(&dev->dev_addrs);
	dev->dev_addr = शून्य;
पूर्ण
EXPORT_SYMBOL(dev_addr_flush);

/**
 *	dev_addr_init - Init device address list
 *	@dev: device
 *
 *	Init device address list and create the first element,
 *	used by ->dev_addr.
 *
 *	The caller must hold the rtnl_mutex.
 */
पूर्णांक dev_addr_init(काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर addr[MAX_ADDR_LEN];
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक err;

	/* rtnl_mutex must be held here */

	__hw_addr_init(&dev->dev_addrs);
	स_रखो(addr, 0, माप(addr));
	err = __hw_addr_add(&dev->dev_addrs, addr, माप(addr),
			    NETDEV_HW_ADDR_T_LAN);
	अगर (!err) अणु
		/*
		 * Get the first (previously created) address from the list
		 * and set dev_addr poपूर्णांकer to this location.
		 */
		ha = list_first_entry(&dev->dev_addrs.list,
				      काष्ठा netdev_hw_addr, list);
		dev->dev_addr = ha->addr;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_addr_init);

/**
 *	dev_addr_add - Add a device address
 *	@dev: device
 *	@addr: address to add
 *	@addr_type: address type
 *
 *	Add a device address to the device or increase the reference count अगर
 *	it alपढ़ोy exists.
 *
 *	The caller must hold the rtnl_mutex.
 */
पूर्णांक dev_addr_add(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr,
		 अचिन्हित अक्षर addr_type)
अणु
	पूर्णांक err;

	ASSERT_RTNL();

	err = dev_pre_changeaddr_notअगरy(dev, addr, शून्य);
	अगर (err)
		वापस err;
	err = __hw_addr_add(&dev->dev_addrs, addr, dev->addr_len, addr_type);
	अगर (!err)
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_addr_add);

/**
 *	dev_addr_del - Release a device address.
 *	@dev: device
 *	@addr: address to delete
 *	@addr_type: address type
 *
 *	Release reference to a device address and हटाओ it from the device
 *	अगर the reference count drops to zero.
 *
 *	The caller must hold the rtnl_mutex.
 */
पूर्णांक dev_addr_del(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr,
		 अचिन्हित अक्षर addr_type)
अणु
	पूर्णांक err;
	काष्ठा netdev_hw_addr *ha;

	ASSERT_RTNL();

	/*
	 * We can not हटाओ the first address from the list because
	 * dev->dev_addr poपूर्णांकs to that.
	 */
	ha = list_first_entry(&dev->dev_addrs.list,
			      काष्ठा netdev_hw_addr, list);
	अगर (!स_भेद(ha->addr, addr, dev->addr_len) &&
	    ha->type == addr_type && ha->refcount == 1)
		वापस -ENOENT;

	err = __hw_addr_del(&dev->dev_addrs, addr, dev->addr_len,
			    addr_type);
	अगर (!err)
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_addr_del);

/*
 * Unicast list handling functions
 */

/**
 *	dev_uc_add_excl - Add a global secondary unicast address
 *	@dev: device
 *	@addr: address to add
 */
पूर्णांक dev_uc_add_excl(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक err;

	netअगर_addr_lock_bh(dev);
	list_क्रम_each_entry(ha, &dev->uc.list, list) अणु
		अगर (!स_भेद(ha->addr, addr, dev->addr_len) &&
		    ha->type == NETDEV_HW_ADDR_T_UNICAST) अणु
			err = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण
	err = __hw_addr_create_ex(&dev->uc, addr, dev->addr_len,
				  NETDEV_HW_ADDR_T_UNICAST, true, false);
	अगर (!err)
		__dev_set_rx_mode(dev);
out:
	netअगर_addr_unlock_bh(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_uc_add_excl);

/**
 *	dev_uc_add - Add a secondary unicast address
 *	@dev: device
 *	@addr: address to add
 *
 *	Add a secondary unicast address to the device or increase
 *	the reference count अगर it alपढ़ोy exists.
 */
पूर्णांक dev_uc_add(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	पूर्णांक err;

	netअगर_addr_lock_bh(dev);
	err = __hw_addr_add(&dev->uc, addr, dev->addr_len,
			    NETDEV_HW_ADDR_T_UNICAST);
	अगर (!err)
		__dev_set_rx_mode(dev);
	netअगर_addr_unlock_bh(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_uc_add);

/**
 *	dev_uc_del - Release secondary unicast address.
 *	@dev: device
 *	@addr: address to delete
 *
 *	Release reference to a secondary unicast address and हटाओ it
 *	from the device अगर the reference count drops to zero.
 */
पूर्णांक dev_uc_del(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	पूर्णांक err;

	netअगर_addr_lock_bh(dev);
	err = __hw_addr_del(&dev->uc, addr, dev->addr_len,
			    NETDEV_HW_ADDR_T_UNICAST);
	अगर (!err)
		__dev_set_rx_mode(dev);
	netअगर_addr_unlock_bh(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_uc_del);

/**
 *	dev_uc_sync - Synchronize device's unicast list to another device
 *	@to: destination device
 *	@from: source device
 *
 *	Add newly added addresses to the destination device and release
 *	addresses that have no users left. The source device must be
 *	locked by netअगर_addr_lock_bh.
 *
 *	This function is पूर्णांकended to be called from the dev->set_rx_mode
 *	function of layered software devices.  This function assumes that
 *	addresses will only ever be synced to the @to devices and no other.
 */
पूर्णांक dev_uc_sync(काष्ठा net_device *to, काष्ठा net_device *from)
अणु
	पूर्णांक err = 0;

	अगर (to->addr_len != from->addr_len)
		वापस -EINVAL;

	netअगर_addr_lock(to);
	err = __hw_addr_sync(&to->uc, &from->uc, to->addr_len);
	अगर (!err)
		__dev_set_rx_mode(to);
	netअगर_addr_unlock(to);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_uc_sync);

/**
 *	dev_uc_sync_multiple - Synchronize device's unicast list to another
 *	device, but allow क्रम multiple calls to sync to multiple devices.
 *	@to: destination device
 *	@from: source device
 *
 *	Add newly added addresses to the destination device and release
 *	addresses that have been deleted from the source. The source device
 *	must be locked by netअगर_addr_lock_bh.
 *
 *	This function is पूर्णांकended to be called from the dev->set_rx_mode
 *	function of layered software devices.  It allows क्रम a single source
 *	device to be synced to multiple destination devices.
 */
पूर्णांक dev_uc_sync_multiple(काष्ठा net_device *to, काष्ठा net_device *from)
अणु
	पूर्णांक err = 0;

	अगर (to->addr_len != from->addr_len)
		वापस -EINVAL;

	netअगर_addr_lock(to);
	err = __hw_addr_sync_multiple(&to->uc, &from->uc, to->addr_len);
	अगर (!err)
		__dev_set_rx_mode(to);
	netअगर_addr_unlock(to);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_uc_sync_multiple);

/**
 *	dev_uc_unsync - Remove synchronized addresses from the destination device
 *	@to: destination device
 *	@from: source device
 *
 *	Remove all addresses that were added to the destination device by
 *	dev_uc_sync(). This function is पूर्णांकended to be called from the
 *	dev->stop function of layered software devices.
 */
व्योम dev_uc_unsync(काष्ठा net_device *to, काष्ठा net_device *from)
अणु
	अगर (to->addr_len != from->addr_len)
		वापस;

	/* netअगर_addr_lock_bh() uses lockdep subclass 0, this is okay क्रम two
	 * reasons:
	 * 1) This is always called without any addr_list_lock, so as the
	 *    outermost one here, it must be 0.
	 * 2) This is called by some callers after unlinking the upper device,
	 *    so the dev->lower_level becomes 1 again.
	 * Thereक्रमe, the subclass क्रम 'from' is 0, for 'to' is either 1 or
	 * larger.
	 */
	netअगर_addr_lock_bh(from);
	netअगर_addr_lock(to);
	__hw_addr_unsync(&to->uc, &from->uc, to->addr_len);
	__dev_set_rx_mode(to);
	netअगर_addr_unlock(to);
	netअगर_addr_unlock_bh(from);
पूर्ण
EXPORT_SYMBOL(dev_uc_unsync);

/**
 *	dev_uc_flush - Flush unicast addresses
 *	@dev: device
 *
 *	Flush unicast addresses.
 */
व्योम dev_uc_flush(काष्ठा net_device *dev)
अणु
	netअगर_addr_lock_bh(dev);
	__hw_addr_flush(&dev->uc);
	netअगर_addr_unlock_bh(dev);
पूर्ण
EXPORT_SYMBOL(dev_uc_flush);

/**
 *	dev_uc_init - Init unicast address list
 *	@dev: device
 *
 *	Init unicast address list.
 */
व्योम dev_uc_init(काष्ठा net_device *dev)
अणु
	__hw_addr_init(&dev->uc);
पूर्ण
EXPORT_SYMBOL(dev_uc_init);

/*
 * Multicast list handling functions
 */

/**
 *	dev_mc_add_excl - Add a global secondary multicast address
 *	@dev: device
 *	@addr: address to add
 */
पूर्णांक dev_mc_add_excl(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक err;

	netअगर_addr_lock_bh(dev);
	list_क्रम_each_entry(ha, &dev->mc.list, list) अणु
		अगर (!स_भेद(ha->addr, addr, dev->addr_len) &&
		    ha->type == NETDEV_HW_ADDR_T_MULTICAST) अणु
			err = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण
	err = __hw_addr_create_ex(&dev->mc, addr, dev->addr_len,
				  NETDEV_HW_ADDR_T_MULTICAST, true, false);
	अगर (!err)
		__dev_set_rx_mode(dev);
out:
	netअगर_addr_unlock_bh(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_mc_add_excl);

अटल पूर्णांक __dev_mc_add(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr,
			bool global)
अणु
	पूर्णांक err;

	netअगर_addr_lock_bh(dev);
	err = __hw_addr_add_ex(&dev->mc, addr, dev->addr_len,
			       NETDEV_HW_ADDR_T_MULTICAST, global, false, 0);
	अगर (!err)
		__dev_set_rx_mode(dev);
	netअगर_addr_unlock_bh(dev);
	वापस err;
पूर्ण
/**
 *	dev_mc_add - Add a multicast address
 *	@dev: device
 *	@addr: address to add
 *
 *	Add a multicast address to the device or increase
 *	the reference count अगर it alपढ़ोy exists.
 */
पूर्णांक dev_mc_add(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __dev_mc_add(dev, addr, false);
पूर्ण
EXPORT_SYMBOL(dev_mc_add);

/**
 *	dev_mc_add_global - Add a global multicast address
 *	@dev: device
 *	@addr: address to add
 *
 *	Add a global multicast address to the device.
 */
पूर्णांक dev_mc_add_global(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __dev_mc_add(dev, addr, true);
पूर्ण
EXPORT_SYMBOL(dev_mc_add_global);

अटल पूर्णांक __dev_mc_del(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr,
			bool global)
अणु
	पूर्णांक err;

	netअगर_addr_lock_bh(dev);
	err = __hw_addr_del_ex(&dev->mc, addr, dev->addr_len,
			       NETDEV_HW_ADDR_T_MULTICAST, global, false);
	अगर (!err)
		__dev_set_rx_mode(dev);
	netअगर_addr_unlock_bh(dev);
	वापस err;
पूर्ण

/**
 *	dev_mc_del - Delete a multicast address.
 *	@dev: device
 *	@addr: address to delete
 *
 *	Release reference to a multicast address and हटाओ it
 *	from the device अगर the reference count drops to zero.
 */
पूर्णांक dev_mc_del(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __dev_mc_del(dev, addr, false);
पूर्ण
EXPORT_SYMBOL(dev_mc_del);

/**
 *	dev_mc_del_global - Delete a global multicast address.
 *	@dev: device
 *	@addr: address to delete
 *
 *	Release reference to a multicast address and हटाओ it
 *	from the device अगर the reference count drops to zero.
 */
पूर्णांक dev_mc_del_global(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __dev_mc_del(dev, addr, true);
पूर्ण
EXPORT_SYMBOL(dev_mc_del_global);

/**
 *	dev_mc_sync - Synchronize device's multicast list to another device
 *	@to: destination device
 *	@from: source device
 *
 *	Add newly added addresses to the destination device and release
 *	addresses that have no users left. The source device must be
 *	locked by netअगर_addr_lock_bh.
 *
 *	This function is पूर्णांकended to be called from the nकरो_set_rx_mode
 *	function of layered software devices.
 */
पूर्णांक dev_mc_sync(काष्ठा net_device *to, काष्ठा net_device *from)
अणु
	पूर्णांक err = 0;

	अगर (to->addr_len != from->addr_len)
		वापस -EINVAL;

	netअगर_addr_lock(to);
	err = __hw_addr_sync(&to->mc, &from->mc, to->addr_len);
	अगर (!err)
		__dev_set_rx_mode(to);
	netअगर_addr_unlock(to);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_mc_sync);

/**
 *	dev_mc_sync_multiple - Synchronize device's multicast list to another
 *	device, but allow क्रम multiple calls to sync to multiple devices.
 *	@to: destination device
 *	@from: source device
 *
 *	Add newly added addresses to the destination device and release
 *	addresses that have no users left. The source device must be
 *	locked by netअगर_addr_lock_bh.
 *
 *	This function is पूर्णांकended to be called from the nकरो_set_rx_mode
 *	function of layered software devices.  It allows क्रम a single
 *	source device to be synced to multiple destination devices.
 */
पूर्णांक dev_mc_sync_multiple(काष्ठा net_device *to, काष्ठा net_device *from)
अणु
	पूर्णांक err = 0;

	अगर (to->addr_len != from->addr_len)
		वापस -EINVAL;

	netअगर_addr_lock(to);
	err = __hw_addr_sync_multiple(&to->mc, &from->mc, to->addr_len);
	अगर (!err)
		__dev_set_rx_mode(to);
	netअगर_addr_unlock(to);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_mc_sync_multiple);

/**
 *	dev_mc_unsync - Remove synchronized addresses from the destination device
 *	@to: destination device
 *	@from: source device
 *
 *	Remove all addresses that were added to the destination device by
 *	dev_mc_sync(). This function is पूर्णांकended to be called from the
 *	dev->stop function of layered software devices.
 */
व्योम dev_mc_unsync(काष्ठा net_device *to, काष्ठा net_device *from)
अणु
	अगर (to->addr_len != from->addr_len)
		वापस;

	/* See the above comments inside dev_uc_unsync(). */
	netअगर_addr_lock_bh(from);
	netअगर_addr_lock(to);
	__hw_addr_unsync(&to->mc, &from->mc, to->addr_len);
	__dev_set_rx_mode(to);
	netअगर_addr_unlock(to);
	netअगर_addr_unlock_bh(from);
पूर्ण
EXPORT_SYMBOL(dev_mc_unsync);

/**
 *	dev_mc_flush - Flush multicast addresses
 *	@dev: device
 *
 *	Flush multicast addresses.
 */
व्योम dev_mc_flush(काष्ठा net_device *dev)
अणु
	netअगर_addr_lock_bh(dev);
	__hw_addr_flush(&dev->mc);
	netअगर_addr_unlock_bh(dev);
पूर्ण
EXPORT_SYMBOL(dev_mc_flush);

/**
 *	dev_mc_init - Init multicast address list
 *	@dev: device
 *
 *	Init multicast address list.
 */
व्योम dev_mc_init(काष्ठा net_device *dev)
अणु
	__hw_addr_init(&dev->mc);
पूर्ण
EXPORT_SYMBOL(dev_mc_init);
