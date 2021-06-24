<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Intel Corporation. All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/netdevice.h>
#समावेश <net/addrconf.h>

#समावेश <rdma/ib_cache.h>

#समावेश "core_priv.h"

काष्ठा ib_pkey_cache अणु
	पूर्णांक             table_len;
	u16             table[];
पूर्ण;

काष्ठा ib_update_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ib_event event;
	bool enक्रमce_security;
पूर्ण;

जोड़ ib_gid zgid;
EXPORT_SYMBOL(zgid);

क्रमागत gid_attr_find_mask अणु
	GID_ATTR_FIND_MASK_GID          = 1UL << 0,
	GID_ATTR_FIND_MASK_NETDEV	= 1UL << 1,
	GID_ATTR_FIND_MASK_DEFAULT	= 1UL << 2,
	GID_ATTR_FIND_MASK_GID_TYPE	= 1UL << 3,
पूर्ण;

क्रमागत gid_table_entry_state अणु
	GID_TABLE_ENTRY_INVALID		= 1,
	GID_TABLE_ENTRY_VALID		= 2,
	/*
	 * Indicates that entry is pending to be हटाओd, there may
	 * be active users of this GID entry.
	 * When last user of the GID entry releases reference to it,
	 * GID entry is detached from the table.
	 */
	GID_TABLE_ENTRY_PENDING_DEL	= 3,
पूर्ण;

काष्ठा roce_gid_ndev_storage अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा net_device *ndev;
पूर्ण;

काष्ठा ib_gid_table_entry अणु
	काष्ठा kref			kref;
	काष्ठा work_काष्ठा		del_work;
	काष्ठा ib_gid_attr		attr;
	व्योम				*context;
	/* Store the ndev poपूर्णांकer to release reference later on in
	 * call_rcu context because by that समय gid_table_entry
	 * and attr might be alपढ़ोy मुक्तd. So keep a copy of it.
	 * ndev_storage is मुक्तd by rcu callback.
	 */
	काष्ठा roce_gid_ndev_storage	*ndev_storage;
	क्रमागत gid_table_entry_state	state;
पूर्ण;

काष्ठा ib_gid_table अणु
	पूर्णांक				sz;
	/* In RoCE, adding a GID to the table requires:
	 * (a) Find अगर this GID is alपढ़ोy exists.
	 * (b) Find a मुक्त space.
	 * (c) Write the new GID
	 *
	 * Delete requires dअगरferent set of operations:
	 * (a) Find the GID
	 * (b) Delete it.
	 *
	 **/
	/* Any ग_लिखोr to data_vec must hold this lock and the ग_लिखो side of
	 * rwlock. Readers must hold only rwlock. All ग_लिखोrs must be in a
	 * sleepable context.
	 */
	काष्ठा mutex			lock;
	/* rwlock protects data_vec[ix]->state and entry poपूर्णांकer.
	 */
	rwlock_t			rwlock;
	काष्ठा ib_gid_table_entry	**data_vec;
	/* bit field, each bit indicates the index of शेष GID */
	u32				शेष_gid_indices;
पूर्ण;

अटल व्योम dispatch_gid_change_event(काष्ठा ib_device *ib_dev, u32 port)
अणु
	काष्ठा ib_event event;

	event.device		= ib_dev;
	event.element.port_num	= port;
	event.event		= IB_EVENT_GID_CHANGE;

	ib_dispatch_event_clients(&event);
पूर्ण

अटल स्थिर अक्षर * स्थिर gid_type_str[] = अणु
	/* IB/RoCE v1 value is set क्रम IB_GID_TYPE_IB and IB_GID_TYPE_ROCE क्रम
	 * user space compatibility reasons.
	 */
	[IB_GID_TYPE_IB]	= "IB/RoCE v1",
	[IB_GID_TYPE_ROCE]	= "IB/RoCE v1",
	[IB_GID_TYPE_ROCE_UDP_ENCAP]	= "RoCE v2",
पूर्ण;

स्थिर अक्षर *ib_cache_gid_type_str(क्रमागत ib_gid_type gid_type)
अणु
	अगर (gid_type < ARRAY_SIZE(gid_type_str) && gid_type_str[gid_type])
		वापस gid_type_str[gid_type];

	वापस "Invalid GID type";
पूर्ण
EXPORT_SYMBOL(ib_cache_gid_type_str);

/** rdma_is_zero_gid - Check अगर given GID is zero or not.
 * @gid:	GID to check
 * Returns true अगर given GID is zero, वापसs false otherwise.
 */
bool rdma_is_zero_gid(स्थिर जोड़ ib_gid *gid)
अणु
	वापस !स_भेद(gid, &zgid, माप(*gid));
पूर्ण
EXPORT_SYMBOL(rdma_is_zero_gid);

/** is_gid_index_शेष - Check अगर a given index beदीर्घs to
 * reserved शेष GIDs or not.
 * @table:	GID table poपूर्णांकer
 * @index:	Index to check in GID table
 * Returns true अगर index is one of the reserved शेष GID index otherwise
 * वापसs false.
 */
अटल bool is_gid_index_शेष(स्थिर काष्ठा ib_gid_table *table,
				 अचिन्हित पूर्णांक index)
अणु
	वापस index < 32 && (BIT(index) & table->शेष_gid_indices);
पूर्ण

पूर्णांक ib_cache_gid_parse_type_str(स्थिर अक्षर *buf)
अणु
	अचिन्हित पूर्णांक i;
	माप_प्रकार len;
	पूर्णांक err = -EINVAL;

	len = म_माप(buf);
	अगर (len == 0)
		वापस -EINVAL;

	अगर (buf[len - 1] == '\n')
		len--;

	क्रम (i = 0; i < ARRAY_SIZE(gid_type_str); ++i)
		अगर (gid_type_str[i] && !म_भेदन(buf, gid_type_str[i], len) &&
		    len == म_माप(gid_type_str[i])) अणु
			err = i;
			अवरोध;
		पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(ib_cache_gid_parse_type_str);

अटल काष्ठा ib_gid_table *rdma_gid_table(काष्ठा ib_device *device, u32 port)
अणु
	वापस device->port_data[port].cache.gid;
पूर्ण

अटल bool is_gid_entry_मुक्त(स्थिर काष्ठा ib_gid_table_entry *entry)
अणु
	वापस !entry;
पूर्ण

अटल bool is_gid_entry_valid(स्थिर काष्ठा ib_gid_table_entry *entry)
अणु
	वापस entry && entry->state == GID_TABLE_ENTRY_VALID;
पूर्ण

अटल व्योम schedule_मुक्त_gid(काष्ठा kref *kref)
अणु
	काष्ठा ib_gid_table_entry *entry =
			container_of(kref, काष्ठा ib_gid_table_entry, kref);

	queue_work(ib_wq, &entry->del_work);
पूर्ण

अटल व्योम put_gid_ndev(काष्ठा rcu_head *head)
अणु
	काष्ठा roce_gid_ndev_storage *storage =
		container_of(head, काष्ठा roce_gid_ndev_storage, rcu_head);

	WARN_ON(!storage->ndev);
	/* At this poपूर्णांक its safe to release netdev reference,
	 * as all callers working on gid_attr->ndev are करोne
	 * using this netdev.
	 */
	dev_put(storage->ndev);
	kमुक्त(storage);
पूर्ण

अटल व्योम मुक्त_gid_entry_locked(काष्ठा ib_gid_table_entry *entry)
अणु
	काष्ठा ib_device *device = entry->attr.device;
	u32 port_num = entry->attr.port_num;
	काष्ठा ib_gid_table *table = rdma_gid_table(device, port_num);

	dev_dbg(&device->dev, "%s port=%u index=%d gid %pI6\n", __func__,
		port_num, entry->attr.index, entry->attr.gid.raw);

	ग_लिखो_lock_irq(&table->rwlock);

	/*
	 * The only way to aव्योम overwriting शून्य in table is
	 * by comparing अगर it is same entry in table or not!
	 * If new entry in table is added by the समय we मुक्त here,
	 * करोn't overग_लिखो the table entry.
	 */
	अगर (entry == table->data_vec[entry->attr.index])
		table->data_vec[entry->attr.index] = शून्य;
	/* Now this index is पढ़ोy to be allocated */
	ग_लिखो_unlock_irq(&table->rwlock);

	अगर (entry->ndev_storage)
		call_rcu(&entry->ndev_storage->rcu_head, put_gid_ndev);
	kमुक्त(entry);
पूर्ण

अटल व्योम मुक्त_gid_entry(काष्ठा kref *kref)
अणु
	काष्ठा ib_gid_table_entry *entry =
			container_of(kref, काष्ठा ib_gid_table_entry, kref);

	मुक्त_gid_entry_locked(entry);
पूर्ण

/**
 * मुक्त_gid_work - Release reference to the GID entry
 * @work: Work काष्ठाure to refer to GID entry which needs to be
 * deleted.
 *
 * मुक्त_gid_work() मुक्तs the entry from the HCA's hardware table
 * अगर provider supports it. It releases reference to netdevice.
 */
अटल व्योम मुक्त_gid_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_gid_table_entry *entry =
		container_of(work, काष्ठा ib_gid_table_entry, del_work);
	काष्ठा ib_device *device = entry->attr.device;
	u32 port_num = entry->attr.port_num;
	काष्ठा ib_gid_table *table = rdma_gid_table(device, port_num);

	mutex_lock(&table->lock);
	मुक्त_gid_entry_locked(entry);
	mutex_unlock(&table->lock);
पूर्ण

अटल काष्ठा ib_gid_table_entry *
alloc_gid_entry(स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा ib_gid_table_entry *entry;
	काष्ठा net_device *ndev;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस शून्य;

	ndev = rcu_dereference_रक्षित(attr->ndev, 1);
	अगर (ndev) अणु
		entry->ndev_storage = kzalloc(माप(*entry->ndev_storage),
					      GFP_KERNEL);
		अगर (!entry->ndev_storage) अणु
			kमुक्त(entry);
			वापस शून्य;
		पूर्ण
		dev_hold(ndev);
		entry->ndev_storage->ndev = ndev;
	पूर्ण
	kref_init(&entry->kref);
	स_नकल(&entry->attr, attr, माप(*attr));
	INIT_WORK(&entry->del_work, मुक्त_gid_work);
	entry->state = GID_TABLE_ENTRY_INVALID;
	वापस entry;
पूर्ण

अटल व्योम store_gid_entry(काष्ठा ib_gid_table *table,
			    काष्ठा ib_gid_table_entry *entry)
अणु
	entry->state = GID_TABLE_ENTRY_VALID;

	dev_dbg(&entry->attr.device->dev, "%s port=%d index=%d gid %pI6\n",
		__func__, entry->attr.port_num, entry->attr.index,
		entry->attr.gid.raw);

	lockdep_निश्चित_held(&table->lock);
	ग_लिखो_lock_irq(&table->rwlock);
	table->data_vec[entry->attr.index] = entry;
	ग_लिखो_unlock_irq(&table->rwlock);
पूर्ण

अटल व्योम get_gid_entry(काष्ठा ib_gid_table_entry *entry)
अणु
	kref_get(&entry->kref);
पूर्ण

अटल व्योम put_gid_entry(काष्ठा ib_gid_table_entry *entry)
अणु
	kref_put(&entry->kref, schedule_मुक्त_gid);
पूर्ण

अटल व्योम put_gid_entry_locked(काष्ठा ib_gid_table_entry *entry)
अणु
	kref_put(&entry->kref, मुक्त_gid_entry);
पूर्ण

अटल पूर्णांक add_roce_gid(काष्ठा ib_gid_table_entry *entry)
अणु
	स्थिर काष्ठा ib_gid_attr *attr = &entry->attr;
	पूर्णांक ret;

	अगर (!attr->ndev) अणु
		dev_err(&attr->device->dev, "%s NULL netdev port=%d index=%d\n",
			__func__, attr->port_num, attr->index);
		वापस -EINVAL;
	पूर्ण
	अगर (rdma_cap_roce_gid_table(attr->device, attr->port_num)) अणु
		ret = attr->device->ops.add_gid(attr, &entry->context);
		अगर (ret) अणु
			dev_err(&attr->device->dev,
				"%s GID add failed port=%d index=%d\n",
				__func__, attr->port_num, attr->index);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * del_gid - Delete GID table entry
 *
 * @ib_dev:	IB device whose GID entry to be deleted
 * @port:	Port number of the IB device
 * @table:	GID table of the IB device क्रम a port
 * @ix:		GID entry index to delete
 *
 */
अटल व्योम del_gid(काष्ठा ib_device *ib_dev, u32 port,
		    काष्ठा ib_gid_table *table, पूर्णांक ix)
अणु
	काष्ठा roce_gid_ndev_storage *ndev_storage;
	काष्ठा ib_gid_table_entry *entry;

	lockdep_निश्चित_held(&table->lock);

	dev_dbg(&ib_dev->dev, "%s port=%u index=%d gid %pI6\n", __func__, port,
		ix, table->data_vec[ix]->attr.gid.raw);

	ग_लिखो_lock_irq(&table->rwlock);
	entry = table->data_vec[ix];
	entry->state = GID_TABLE_ENTRY_PENDING_DEL;
	/*
	 * For non RoCE protocol, GID entry slot is पढ़ोy to use.
	 */
	अगर (!rdma_protocol_roce(ib_dev, port))
		table->data_vec[ix] = शून्य;
	ग_लिखो_unlock_irq(&table->rwlock);

	ndev_storage = entry->ndev_storage;
	अगर (ndev_storage) अणु
		entry->ndev_storage = शून्य;
		rcu_assign_poपूर्णांकer(entry->attr.ndev, शून्य);
		call_rcu(&ndev_storage->rcu_head, put_gid_ndev);
	पूर्ण

	अगर (rdma_cap_roce_gid_table(ib_dev, port))
		ib_dev->ops.del_gid(&entry->attr, &entry->context);

	put_gid_entry_locked(entry);
पूर्ण

/**
 * add_modअगरy_gid - Add or modअगरy GID table entry
 *
 * @table:	GID table in which GID to be added or modअगरied
 * @attr:	Attributes of the GID
 *
 * Returns 0 on success or appropriate error code. It accepts zero
 * GID addition क्रम non RoCE ports क्रम HCA's who report them as valid
 * GID. However such zero GIDs are not added to the cache.
 */
अटल पूर्णांक add_modअगरy_gid(काष्ठा ib_gid_table *table,
			  स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा ib_gid_table_entry *entry;
	पूर्णांक ret = 0;

	/*
	 * Invalidate any old entry in the table to make it safe to ग_लिखो to
	 * this index.
	 */
	अगर (is_gid_entry_valid(table->data_vec[attr->index]))
		del_gid(attr->device, attr->port_num, table, attr->index);

	/*
	 * Some HCA's report multiple GID entries with only one valid GID, and
	 * leave other unused entries as the zero GID. Convert zero GIDs to
	 * empty table entries instead of storing them.
	 */
	अगर (rdma_is_zero_gid(&attr->gid))
		वापस 0;

	entry = alloc_gid_entry(attr);
	अगर (!entry)
		वापस -ENOMEM;

	अगर (rdma_protocol_roce(attr->device, attr->port_num)) अणु
		ret = add_roce_gid(entry);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	store_gid_entry(table, entry);
	वापस 0;

करोne:
	put_gid_entry(entry);
	वापस ret;
पूर्ण

/* rwlock should be पढ़ो locked, or lock should be held */
अटल पूर्णांक find_gid(काष्ठा ib_gid_table *table, स्थिर जोड़ ib_gid *gid,
		    स्थिर काष्ठा ib_gid_attr *val, bool शेष_gid,
		    अचिन्हित दीर्घ mask, पूर्णांक *pempty)
अणु
	पूर्णांक i = 0;
	पूर्णांक found = -1;
	पूर्णांक empty = pempty ? -1 : 0;

	जबतक (i < table->sz && (found < 0 || empty < 0)) अणु
		काष्ठा ib_gid_table_entry *data = table->data_vec[i];
		काष्ठा ib_gid_attr *attr;
		पूर्णांक curr_index = i;

		i++;

		/* find_gid() is used during GID addition where it is expected
		 * to वापस a मुक्त entry slot which is not duplicate.
		 * Free entry slot is requested and वापसed अगर pempty is set,
		 * so lookup मुक्त slot only अगर requested.
		 */
		अगर (pempty && empty < 0) अणु
			अगर (is_gid_entry_मुक्त(data) &&
			    शेष_gid ==
				is_gid_index_शेष(table, curr_index)) अणु
				/*
				 * Found an invalid (मुक्त) entry; allocate it.
				 * If शेष GID is requested, then our
				 * found slot must be one of the DEFAULT
				 * reserved slots or we fail.
				 * This ensures that only DEFAULT reserved
				 * slots are used क्रम शेष property GIDs.
				 */
				empty = curr_index;
			पूर्ण
		पूर्ण

		/*
		 * Additionally find_gid() is used to find valid entry during
		 * lookup operation; so ignore the entries which are marked as
		 * pending क्रम removal and the entries which are marked as
		 * invalid.
		 */
		अगर (!is_gid_entry_valid(data))
			जारी;

		अगर (found >= 0)
			जारी;

		attr = &data->attr;
		अगर (mask & GID_ATTR_FIND_MASK_GID_TYPE &&
		    attr->gid_type != val->gid_type)
			जारी;

		अगर (mask & GID_ATTR_FIND_MASK_GID &&
		    स_भेद(gid, &data->attr.gid, माप(*gid)))
			जारी;

		अगर (mask & GID_ATTR_FIND_MASK_NETDEV &&
		    attr->ndev != val->ndev)
			जारी;

		अगर (mask & GID_ATTR_FIND_MASK_DEFAULT &&
		    is_gid_index_शेष(table, curr_index) != शेष_gid)
			जारी;

		found = curr_index;
	पूर्ण

	अगर (pempty)
		*pempty = empty;

	वापस found;
पूर्ण

अटल व्योम make_शेष_gid(काष्ठा  net_device *dev, जोड़ ib_gid *gid)
अणु
	gid->global.subnet_prefix = cpu_to_be64(0xfe80000000000000LL);
	addrconf_अगरid_eui48(&gid->raw[8], dev);
पूर्ण

अटल पूर्णांक __ib_cache_gid_add(काष्ठा ib_device *ib_dev, u32 port,
			      जोड़ ib_gid *gid, काष्ठा ib_gid_attr *attr,
			      अचिन्हित दीर्घ mask, bool शेष_gid)
अणु
	काष्ठा ib_gid_table *table;
	पूर्णांक ret = 0;
	पूर्णांक empty;
	पूर्णांक ix;

	/* Do not allow adding zero GID in support of
	 * IB spec version 1.3 section 4.1.1 poपूर्णांक (6) and
	 * section 12.7.10 and section 12.7.20
	 */
	अगर (rdma_is_zero_gid(gid))
		वापस -EINVAL;

	table = rdma_gid_table(ib_dev, port);

	mutex_lock(&table->lock);

	ix = find_gid(table, gid, attr, शेष_gid, mask, &empty);
	अगर (ix >= 0)
		जाओ out_unlock;

	अगर (empty < 0) अणु
		ret = -ENOSPC;
		जाओ out_unlock;
	पूर्ण
	attr->device = ib_dev;
	attr->index = empty;
	attr->port_num = port;
	attr->gid = *gid;
	ret = add_modअगरy_gid(table, attr);
	अगर (!ret)
		dispatch_gid_change_event(ib_dev, port);

out_unlock:
	mutex_unlock(&table->lock);
	अगर (ret)
		pr_warn("%s: unable to add gid %pI6 error=%d\n",
			__func__, gid->raw, ret);
	वापस ret;
पूर्ण

पूर्णांक ib_cache_gid_add(काष्ठा ib_device *ib_dev, u32 port,
		     जोड़ ib_gid *gid, काष्ठा ib_gid_attr *attr)
अणु
	अचिन्हित दीर्घ mask = GID_ATTR_FIND_MASK_GID |
			     GID_ATTR_FIND_MASK_GID_TYPE |
			     GID_ATTR_FIND_MASK_NETDEV;

	वापस __ib_cache_gid_add(ib_dev, port, gid, attr, mask, false);
पूर्ण

अटल पूर्णांक
_ib_cache_gid_del(काष्ठा ib_device *ib_dev, u32 port,
		  जोड़ ib_gid *gid, काष्ठा ib_gid_attr *attr,
		  अचिन्हित दीर्घ mask, bool शेष_gid)
अणु
	काष्ठा ib_gid_table *table;
	पूर्णांक ret = 0;
	पूर्णांक ix;

	table = rdma_gid_table(ib_dev, port);

	mutex_lock(&table->lock);

	ix = find_gid(table, gid, attr, शेष_gid, mask, शून्य);
	अगर (ix < 0) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	del_gid(ib_dev, port, table, ix);
	dispatch_gid_change_event(ib_dev, port);

out_unlock:
	mutex_unlock(&table->lock);
	अगर (ret)
		pr_debug("%s: can't delete gid %pI6 error=%d\n",
			 __func__, gid->raw, ret);
	वापस ret;
पूर्ण

पूर्णांक ib_cache_gid_del(काष्ठा ib_device *ib_dev, u32 port,
		     जोड़ ib_gid *gid, काष्ठा ib_gid_attr *attr)
अणु
	अचिन्हित दीर्घ mask = GID_ATTR_FIND_MASK_GID	  |
			     GID_ATTR_FIND_MASK_GID_TYPE |
			     GID_ATTR_FIND_MASK_DEFAULT  |
			     GID_ATTR_FIND_MASK_NETDEV;

	वापस _ib_cache_gid_del(ib_dev, port, gid, attr, mask, false);
पूर्ण

पूर्णांक ib_cache_gid_del_all_netdev_gids(काष्ठा ib_device *ib_dev, u32 port,
				     काष्ठा net_device *ndev)
अणु
	काष्ठा ib_gid_table *table;
	पूर्णांक ix;
	bool deleted = false;

	table = rdma_gid_table(ib_dev, port);

	mutex_lock(&table->lock);

	क्रम (ix = 0; ix < table->sz; ix++) अणु
		अगर (is_gid_entry_valid(table->data_vec[ix]) &&
		    table->data_vec[ix]->attr.ndev == ndev) अणु
			del_gid(ib_dev, port, table, ix);
			deleted = true;
		पूर्ण
	पूर्ण

	mutex_unlock(&table->lock);

	अगर (deleted)
		dispatch_gid_change_event(ib_dev, port);

	वापस 0;
पूर्ण

/**
 * rdma_find_gid_by_port - Returns the GID entry attributes when it finds
 * a valid GID entry क्रम given search parameters. It searches क्रम the specअगरied
 * GID value in the local software cache.
 * @ib_dev: The device to query.
 * @gid: The GID value to search क्रम.
 * @gid_type: The GID type to search क्रम.
 * @port: The port number of the device where the GID value should be searched.
 * @ndev: In RoCE, the net device of the device. शून्य means ignore.
 *
 * Returns sgid attributes अगर the GID is found with valid reference or
 * वापसs ERR_PTR क्रम the error.
 * The caller must invoke rdma_put_gid_attr() to release the reference.
 */
स्थिर काष्ठा ib_gid_attr *
rdma_find_gid_by_port(काष्ठा ib_device *ib_dev,
		      स्थिर जोड़ ib_gid *gid,
		      क्रमागत ib_gid_type gid_type,
		      u32 port, काष्ठा net_device *ndev)
अणु
	पूर्णांक local_index;
	काष्ठा ib_gid_table *table;
	अचिन्हित दीर्घ mask = GID_ATTR_FIND_MASK_GID |
			     GID_ATTR_FIND_MASK_GID_TYPE;
	काष्ठा ib_gid_attr val = अणु.ndev = ndev, .gid_type = gid_typeपूर्ण;
	स्थिर काष्ठा ib_gid_attr *attr;
	अचिन्हित दीर्घ flags;

	अगर (!rdma_is_port_valid(ib_dev, port))
		वापस ERR_PTR(-ENOENT);

	table = rdma_gid_table(ib_dev, port);

	अगर (ndev)
		mask |= GID_ATTR_FIND_MASK_NETDEV;

	पढ़ो_lock_irqsave(&table->rwlock, flags);
	local_index = find_gid(table, gid, &val, false, mask, शून्य);
	अगर (local_index >= 0) अणु
		get_gid_entry(table->data_vec[local_index]);
		attr = &table->data_vec[local_index]->attr;
		पढ़ो_unlock_irqrestore(&table->rwlock, flags);
		वापस attr;
	पूर्ण

	पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL(rdma_find_gid_by_port);

/**
 * rdma_find_gid_by_filter - Returns the GID table attribute where a
 * specअगरied GID value occurs
 * @ib_dev: The device to query.
 * @gid: The GID value to search क्रम.
 * @port: The port number of the device where the GID value could be
 *   searched.
 * @filter: The filter function is executed on any matching GID in the table.
 *   If the filter function वापसs true, the corresponding index is वापसed,
 *   otherwise, we जारी searching the GID table. It's guaranteed that
 *   जबतक filter is executed, ndev field is valid and the काष्ठाure won't
 *   change. filter is executed in an atomic context. filter must not be शून्य.
 * @context: Private data to pass पूर्णांकo the call-back.
 *
 * rdma_find_gid_by_filter() searches क्रम the specअगरied GID value
 * of which the filter function वापसs true in the port's GID table.
 *
 */
स्थिर काष्ठा ib_gid_attr *rdma_find_gid_by_filter(
	काष्ठा ib_device *ib_dev, स्थिर जोड़ ib_gid *gid, u32 port,
	bool (*filter)(स्थिर जोड़ ib_gid *gid, स्थिर काष्ठा ib_gid_attr *,
		       व्योम *),
	व्योम *context)
अणु
	स्थिर काष्ठा ib_gid_attr *res = ERR_PTR(-ENOENT);
	काष्ठा ib_gid_table *table;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (!rdma_is_port_valid(ib_dev, port))
		वापस ERR_PTR(-EINVAL);

	table = rdma_gid_table(ib_dev, port);

	पढ़ो_lock_irqsave(&table->rwlock, flags);
	क्रम (i = 0; i < table->sz; i++) अणु
		काष्ठा ib_gid_table_entry *entry = table->data_vec[i];

		अगर (!is_gid_entry_valid(entry))
			जारी;

		अगर (स_भेद(gid, &entry->attr.gid, माप(*gid)))
			जारी;

		अगर (filter(gid, &entry->attr, context)) अणु
			get_gid_entry(entry);
			res = &entry->attr;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	वापस res;
पूर्ण

अटल काष्ठा ib_gid_table *alloc_gid_table(पूर्णांक sz)
अणु
	काष्ठा ib_gid_table *table = kzalloc(माप(*table), GFP_KERNEL);

	अगर (!table)
		वापस शून्य;

	table->data_vec = kसुस्मृति(sz, माप(*table->data_vec), GFP_KERNEL);
	अगर (!table->data_vec)
		जाओ err_मुक्त_table;

	mutex_init(&table->lock);

	table->sz = sz;
	rwlock_init(&table->rwlock);
	वापस table;

err_मुक्त_table:
	kमुक्त(table);
	वापस शून्य;
पूर्ण

अटल व्योम release_gid_table(काष्ठा ib_device *device,
			      काष्ठा ib_gid_table *table)
अणु
	bool leak = false;
	पूर्णांक i;

	अगर (!table)
		वापस;

	क्रम (i = 0; i < table->sz; i++) अणु
		अगर (is_gid_entry_मुक्त(table->data_vec[i]))
			जारी;
		अगर (kref_पढ़ो(&table->data_vec[i]->kref) > 1) अणु
			dev_err(&device->dev,
				"GID entry ref leak for index %d ref=%d\n", i,
				kref_पढ़ो(&table->data_vec[i]->kref));
			leak = true;
		पूर्ण
	पूर्ण
	अगर (leak)
		वापस;

	mutex_destroy(&table->lock);
	kमुक्त(table->data_vec);
	kमुक्त(table);
पूर्ण

अटल व्योम cleanup_gid_table_port(काष्ठा ib_device *ib_dev, u32 port,
				   काष्ठा ib_gid_table *table)
अणु
	पूर्णांक i;

	अगर (!table)
		वापस;

	mutex_lock(&table->lock);
	क्रम (i = 0; i < table->sz; ++i) अणु
		अगर (is_gid_entry_valid(table->data_vec[i]))
			del_gid(ib_dev, port, table, i);
	पूर्ण
	mutex_unlock(&table->lock);
पूर्ण

व्योम ib_cache_gid_set_शेष_gid(काष्ठा ib_device *ib_dev, u32 port,
				  काष्ठा net_device *ndev,
				  अचिन्हित दीर्घ gid_type_mask,
				  क्रमागत ib_cache_gid_शेष_mode mode)
अणु
	जोड़ ib_gid gid = अणु पूर्ण;
	काष्ठा ib_gid_attr gid_attr;
	अचिन्हित पूर्णांक gid_type;
	अचिन्हित दीर्घ mask;

	mask = GID_ATTR_FIND_MASK_GID_TYPE |
	       GID_ATTR_FIND_MASK_DEFAULT |
	       GID_ATTR_FIND_MASK_NETDEV;
	स_रखो(&gid_attr, 0, माप(gid_attr));
	gid_attr.ndev = ndev;

	क्रम (gid_type = 0; gid_type < IB_GID_TYPE_SIZE; ++gid_type) अणु
		अगर (1UL << gid_type & ~gid_type_mask)
			जारी;

		gid_attr.gid_type = gid_type;

		अगर (mode == IB_CACHE_GID_DEFAULT_MODE_SET) अणु
			make_शेष_gid(ndev, &gid);
			__ib_cache_gid_add(ib_dev, port, &gid,
					   &gid_attr, mask, true);
		पूर्ण अन्यथा अगर (mode == IB_CACHE_GID_DEFAULT_MODE_DELETE) अणु
			_ib_cache_gid_del(ib_dev, port, &gid,
					  &gid_attr, mask, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gid_table_reserve_शेष(काष्ठा ib_device *ib_dev, u32 port,
				      काष्ठा ib_gid_table *table)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ roce_gid_type_mask;
	अचिन्हित पूर्णांक num_शेष_gids;

	roce_gid_type_mask = roce_gid_type_mask_support(ib_dev, port);
	num_शेष_gids = hweight_दीर्घ(roce_gid_type_mask);
	/* Reserve starting indices क्रम शेष GIDs */
	क्रम (i = 0; i < num_शेष_gids && i < table->sz; i++)
		table->शेष_gid_indices |= BIT(i);
पूर्ण


अटल व्योम gid_table_release_one(काष्ठा ib_device *ib_dev)
अणु
	u32 p;

	rdma_क्रम_each_port (ib_dev, p) अणु
		release_gid_table(ib_dev, ib_dev->port_data[p].cache.gid);
		ib_dev->port_data[p].cache.gid = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक _gid_table_setup_one(काष्ठा ib_device *ib_dev)
अणु
	काष्ठा ib_gid_table *table;
	u32 rdma_port;

	rdma_क्रम_each_port (ib_dev, rdma_port) अणु
		table = alloc_gid_table(
			ib_dev->port_data[rdma_port].immutable.gid_tbl_len);
		अगर (!table)
			जाओ rollback_table_setup;

		gid_table_reserve_शेष(ib_dev, rdma_port, table);
		ib_dev->port_data[rdma_port].cache.gid = table;
	पूर्ण
	वापस 0;

rollback_table_setup:
	gid_table_release_one(ib_dev);
	वापस -ENOMEM;
पूर्ण

अटल व्योम gid_table_cleanup_one(काष्ठा ib_device *ib_dev)
अणु
	u32 p;

	rdma_क्रम_each_port (ib_dev, p)
		cleanup_gid_table_port(ib_dev, p,
				       ib_dev->port_data[p].cache.gid);
पूर्ण

अटल पूर्णांक gid_table_setup_one(काष्ठा ib_device *ib_dev)
अणु
	पूर्णांक err;

	err = _gid_table_setup_one(ib_dev);

	अगर (err)
		वापस err;

	rdma_roce_rescan_device(ib_dev);

	वापस err;
पूर्ण

/**
 * rdma_query_gid - Read the GID content from the GID software cache
 * @device:		Device to query the GID
 * @port_num:		Port number of the device
 * @index:		Index of the GID table entry to पढ़ो
 * @gid:		Poपूर्णांकer to GID where to store the entry's GID
 *
 * rdma_query_gid() only पढ़ोs the GID entry content क्रम requested device,
 * port and index. It पढ़ोs क्रम IB, RoCE and iWarp link layers.  It करोesn't
 * hold any reference to the GID table entry in the HCA or software cache.
 *
 * Returns 0 on success or appropriate error code.
 *
 */
पूर्णांक rdma_query_gid(काष्ठा ib_device *device, u32 port_num,
		   पूर्णांक index, जोड़ ib_gid *gid)
अणु
	काष्ठा ib_gid_table *table;
	अचिन्हित दीर्घ flags;
	पूर्णांक res = -EINVAL;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	table = rdma_gid_table(device, port_num);
	पढ़ो_lock_irqsave(&table->rwlock, flags);

	अगर (index < 0 || index >= table->sz ||
	    !is_gid_entry_valid(table->data_vec[index]))
		जाओ करोne;

	स_नकल(gid, &table->data_vec[index]->attr.gid, माप(*gid));
	res = 0;

करोne:
	पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	वापस res;
पूर्ण
EXPORT_SYMBOL(rdma_query_gid);

/**
 * rdma_पढ़ो_gid_hw_context - Read the HW GID context from GID attribute
 * @attr:		Potपूर्णांकer to the GID attribute
 *
 * rdma_पढ़ो_gid_hw_context() पढ़ोs the drivers GID HW context corresponding
 * to the SGID attr. Callers are required to alपढ़ोy be holding the reference
 * to an existing GID entry.
 *
 * Returns the HW GID context
 *
 */
व्योम *rdma_पढ़ो_gid_hw_context(स्थिर काष्ठा ib_gid_attr *attr)
अणु
	वापस container_of(attr, काष्ठा ib_gid_table_entry, attr)->context;
पूर्ण
EXPORT_SYMBOL(rdma_पढ़ो_gid_hw_context);

/**
 * rdma_find_gid - Returns SGID attributes अगर the matching GID is found.
 * @device: The device to query.
 * @gid: The GID value to search क्रम.
 * @gid_type: The GID type to search क्रम.
 * @ndev: In RoCE, the net device of the device. शून्य means ignore.
 *
 * rdma_find_gid() searches क्रम the specअगरied GID value in the software cache.
 *
 * Returns GID attributes अगर a valid GID is found or वापसs ERR_PTR क्रम the
 * error. The caller must invoke rdma_put_gid_attr() to release the reference.
 *
 */
स्थिर काष्ठा ib_gid_attr *rdma_find_gid(काष्ठा ib_device *device,
					स्थिर जोड़ ib_gid *gid,
					क्रमागत ib_gid_type gid_type,
					काष्ठा net_device *ndev)
अणु
	अचिन्हित दीर्घ mask = GID_ATTR_FIND_MASK_GID |
			     GID_ATTR_FIND_MASK_GID_TYPE;
	काष्ठा ib_gid_attr gid_attr_val = अणु.ndev = ndev, .gid_type = gid_typeपूर्ण;
	u32 p;

	अगर (ndev)
		mask |= GID_ATTR_FIND_MASK_NETDEV;

	rdma_क्रम_each_port(device, p) अणु
		काष्ठा ib_gid_table *table;
		अचिन्हित दीर्घ flags;
		पूर्णांक index;

		table = device->port_data[p].cache.gid;
		पढ़ो_lock_irqsave(&table->rwlock, flags);
		index = find_gid(table, gid, &gid_attr_val, false, mask, शून्य);
		अगर (index >= 0) अणु
			स्थिर काष्ठा ib_gid_attr *attr;

			get_gid_entry(table->data_vec[index]);
			attr = &table->data_vec[index]->attr;
			पढ़ो_unlock_irqrestore(&table->rwlock, flags);
			वापस attr;
		पूर्ण
		पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL(rdma_find_gid);

पूर्णांक ib_get_cached_pkey(काष्ठा ib_device *device,
		       u32               port_num,
		       पूर्णांक               index,
		       u16              *pkey)
अणु
	काष्ठा ib_pkey_cache *cache;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	पढ़ो_lock_irqsave(&device->cache_lock, flags);

	cache = device->port_data[port_num].cache.pkey;

	अगर (!cache || index < 0 || index >= cache->table_len)
		ret = -EINVAL;
	अन्यथा
		*pkey = cache->table[index];

	पढ़ो_unlock_irqrestore(&device->cache_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_get_cached_pkey);

पूर्णांक ib_get_cached_subnet_prefix(काष्ठा ib_device *device, u32 port_num,
				u64 *sn_pfx)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	पढ़ो_lock_irqsave(&device->cache_lock, flags);
	*sn_pfx = device->port_data[port_num].cache.subnet_prefix;
	पढ़ो_unlock_irqrestore(&device->cache_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_get_cached_subnet_prefix);

पूर्णांक ib_find_cached_pkey(काष्ठा ib_device *device, u32 port_num,
			u16 pkey, u16 *index)
अणु
	काष्ठा ib_pkey_cache *cache;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक ret = -ENOENT;
	पूर्णांक partial_ix = -1;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	पढ़ो_lock_irqsave(&device->cache_lock, flags);

	cache = device->port_data[port_num].cache.pkey;
	अगर (!cache) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	*index = -1;

	क्रम (i = 0; i < cache->table_len; ++i)
		अगर ((cache->table[i] & 0x7fff) == (pkey & 0x7fff)) अणु
			अगर (cache->table[i] & 0x8000) अणु
				*index = i;
				ret = 0;
				अवरोध;
			पूर्ण अन्यथा अणु
				partial_ix = i;
			पूर्ण
		पूर्ण

	अगर (ret && partial_ix >= 0) अणु
		*index = partial_ix;
		ret = 0;
	पूर्ण

err:
	पढ़ो_unlock_irqrestore(&device->cache_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_find_cached_pkey);

पूर्णांक ib_find_exact_cached_pkey(काष्ठा ib_device *device, u32 port_num,
			      u16 pkey, u16 *index)
अणु
	काष्ठा ib_pkey_cache *cache;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक ret = -ENOENT;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	पढ़ो_lock_irqsave(&device->cache_lock, flags);

	cache = device->port_data[port_num].cache.pkey;
	अगर (!cache) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	*index = -1;

	क्रम (i = 0; i < cache->table_len; ++i)
		अगर (cache->table[i] == pkey) अणु
			*index = i;
			ret = 0;
			अवरोध;
		पूर्ण

err:
	पढ़ो_unlock_irqrestore(&device->cache_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_find_exact_cached_pkey);

पूर्णांक ib_get_cached_lmc(काष्ठा ib_device *device, u32 port_num, u8 *lmc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	पढ़ो_lock_irqsave(&device->cache_lock, flags);
	*lmc = device->port_data[port_num].cache.lmc;
	पढ़ो_unlock_irqrestore(&device->cache_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_get_cached_lmc);

पूर्णांक ib_get_cached_port_state(काष्ठा ib_device *device, u32 port_num,
			     क्रमागत ib_port_state *port_state)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	पढ़ो_lock_irqsave(&device->cache_lock, flags);
	*port_state = device->port_data[port_num].cache.port_state;
	पढ़ो_unlock_irqrestore(&device->cache_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_get_cached_port_state);

/**
 * rdma_get_gid_attr - Returns GID attributes क्रम a port of a device
 * at a requested gid_index, अगर a valid GID entry exists.
 * @device:		The device to query.
 * @port_num:		The port number on the device where the GID value
 *			is to be queried.
 * @index:		Index of the GID table entry whose attributes are to
 *                      be queried.
 *
 * rdma_get_gid_attr() acquires reference count of gid attributes from the
 * cached GID table. Caller must invoke rdma_put_gid_attr() to release
 * reference to gid attribute regardless of link layer.
 *
 * Returns poपूर्णांकer to valid gid attribute or ERR_PTR क्रम the appropriate error
 * code.
 */
स्थिर काष्ठा ib_gid_attr *
rdma_get_gid_attr(काष्ठा ib_device *device, u32 port_num, पूर्णांक index)
अणु
	स्थिर काष्ठा ib_gid_attr *attr = ERR_PTR(-ENODATA);
	काष्ठा ib_gid_table *table;
	अचिन्हित दीर्घ flags;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस ERR_PTR(-EINVAL);

	table = rdma_gid_table(device, port_num);
	अगर (index < 0 || index >= table->sz)
		वापस ERR_PTR(-EINVAL);

	पढ़ो_lock_irqsave(&table->rwlock, flags);
	अगर (!is_gid_entry_valid(table->data_vec[index]))
		जाओ करोne;

	get_gid_entry(table->data_vec[index]);
	attr = &table->data_vec[index]->attr;
करोne:
	पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	वापस attr;
पूर्ण
EXPORT_SYMBOL(rdma_get_gid_attr);

/**
 * rdma_query_gid_table - Reads GID table entries of all the ports of a device up to max_entries.
 * @device: The device to query.
 * @entries: Entries where GID entries are वापसed.
 * @max_entries: Maximum number of entries that can be वापसed.
 * Entries array must be allocated to hold max_entries number of entries.
 *
 * Returns number of entries on success or appropriate error code.
 */
sमाप_प्रकार rdma_query_gid_table(काष्ठा ib_device *device,
			     काष्ठा ib_uverbs_gid_entry *entries,
			     माप_प्रकार max_entries)
अणु
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	sमाप_प्रकार num_entries = 0, ret;
	काष्ठा ib_gid_table *table;
	u32 port_num, i;
	काष्ठा net_device *ndev;
	अचिन्हित दीर्घ flags;

	rdma_क्रम_each_port(device, port_num) अणु
		table = rdma_gid_table(device, port_num);
		पढ़ो_lock_irqsave(&table->rwlock, flags);
		क्रम (i = 0; i < table->sz; i++) अणु
			अगर (!is_gid_entry_valid(table->data_vec[i]))
				जारी;
			अगर (num_entries >= max_entries) अणु
				ret = -EINVAL;
				जाओ err;
			पूर्ण

			gid_attr = &table->data_vec[i]->attr;

			स_नकल(&entries->gid, &gid_attr->gid,
			       माप(gid_attr->gid));
			entries->gid_index = gid_attr->index;
			entries->port_num = gid_attr->port_num;
			entries->gid_type = gid_attr->gid_type;
			ndev = rcu_dereference_रक्षित(
				gid_attr->ndev,
				lockdep_is_held(&table->rwlock));
			अगर (ndev)
				entries->netdev_अगरindex = ndev->अगरindex;

			num_entries++;
			entries++;
		पूर्ण
		पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	पूर्ण

	वापस num_entries;
err:
	पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_query_gid_table);

/**
 * rdma_put_gid_attr - Release reference to the GID attribute
 * @attr:		Poपूर्णांकer to the GID attribute whose reference
 *			needs to be released.
 *
 * rdma_put_gid_attr() must be used to release reference whose
 * reference is acquired using rdma_get_gid_attr() or any APIs
 * which वापसs a poपूर्णांकer to the ib_gid_attr regardless of link layer
 * of IB or RoCE.
 *
 */
व्योम rdma_put_gid_attr(स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा ib_gid_table_entry *entry =
		container_of(attr, काष्ठा ib_gid_table_entry, attr);

	put_gid_entry(entry);
पूर्ण
EXPORT_SYMBOL(rdma_put_gid_attr);

/**
 * rdma_hold_gid_attr - Get reference to existing GID attribute
 *
 * @attr:		Poपूर्णांकer to the GID attribute whose reference
 *			needs to be taken.
 *
 * Increase the reference count to a GID attribute to keep it from being
 * मुक्तd. Callers are required to alपढ़ोy be holding a reference to attribute.
 *
 */
व्योम rdma_hold_gid_attr(स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा ib_gid_table_entry *entry =
		container_of(attr, काष्ठा ib_gid_table_entry, attr);

	get_gid_entry(entry);
पूर्ण
EXPORT_SYMBOL(rdma_hold_gid_attr);

/**
 * rdma_पढ़ो_gid_attr_ndev_rcu - Read GID attribute netdevice
 * which must be in UP state.
 *
 * @attr:Poपूर्णांकer to the GID attribute
 *
 * Returns poपूर्णांकer to netdevice अगर the netdevice was attached to GID and
 * netdevice is in UP state. Caller must hold RCU lock as this API
 * पढ़ोs the netdev flags which can change जबतक netdevice migrates to
 * dअगरferent net namespace. Returns ERR_PTR with error code otherwise.
 *
 */
काष्ठा net_device *rdma_पढ़ो_gid_attr_ndev_rcu(स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा ib_gid_table_entry *entry =
			container_of(attr, काष्ठा ib_gid_table_entry, attr);
	काष्ठा ib_device *device = entry->attr.device;
	काष्ठा net_device *ndev = ERR_PTR(-EINVAL);
	u32 port_num = entry->attr.port_num;
	काष्ठा ib_gid_table *table;
	अचिन्हित दीर्घ flags;
	bool valid;

	table = rdma_gid_table(device, port_num);

	पढ़ो_lock_irqsave(&table->rwlock, flags);
	valid = is_gid_entry_valid(table->data_vec[attr->index]);
	अगर (valid) अणु
		ndev = rcu_dereference(attr->ndev);
		अगर (!ndev)
			ndev = ERR_PTR(-ENODEV);
	पूर्ण
	पढ़ो_unlock_irqrestore(&table->rwlock, flags);
	वापस ndev;
पूर्ण
EXPORT_SYMBOL(rdma_पढ़ो_gid_attr_ndev_rcu);

अटल पूर्णांक get_lower_dev_vlan(काष्ठा net_device *lower_dev,
			      काष्ठा netdev_nested_priv *priv)
अणु
	u16 *vlan_id = (u16 *)priv->data;

	अगर (is_vlan_dev(lower_dev))
		*vlan_id = vlan_dev_vlan_id(lower_dev);

	/* We are पूर्णांकerested only in first level vlan device, so
	 * always वापस 1 to stop iterating over next level devices.
	 */
	वापस 1;
पूर्ण

/**
 * rdma_पढ़ो_gid_l2_fields - Read the vlan ID and source MAC address
 *			     of a GID entry.
 *
 * @attr:	GID attribute poपूर्णांकer whose L2 fields to be पढ़ो
 * @vlan_id:	Poपूर्णांकer to vlan id to fill up अगर the GID entry has
 *		vlan id. It is optional.
 * @smac:	Poपूर्णांकer to smac to fill up क्रम a GID entry. It is optional.
 *
 * rdma_पढ़ो_gid_l2_fields() वापसs 0 on success and वापसs vlan id
 * (अगर gid entry has vlan) and source MAC, or वापसs error.
 */
पूर्णांक rdma_पढ़ो_gid_l2_fields(स्थिर काष्ठा ib_gid_attr *attr,
			    u16 *vlan_id, u8 *smac)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)vlan_id,
	पूर्ण;
	काष्ठा net_device *ndev;

	rcu_पढ़ो_lock();
	ndev = rcu_dereference(attr->ndev);
	अगर (!ndev) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	अगर (smac)
		ether_addr_copy(smac, ndev->dev_addr);
	अगर (vlan_id) अणु
		*vlan_id = 0xffff;
		अगर (is_vlan_dev(ndev)) अणु
			*vlan_id = vlan_dev_vlan_id(ndev);
		पूर्ण अन्यथा अणु
			/* If the netdev is upper device and अगर it's lower
			 * device is vlan device, consider vlan id of the
			 * the lower vlan device क्रम this gid entry.
			 */
			netdev_walk_all_lower_dev_rcu(attr->ndev,
					get_lower_dev_vlan, &priv);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rdma_पढ़ो_gid_l2_fields);

अटल पूर्णांक config_non_roce_gid_cache(काष्ठा ib_device *device,
				     u32 port, पूर्णांक gid_tbl_len)
अणु
	काष्ठा ib_gid_attr gid_attr = अणुपूर्ण;
	काष्ठा ib_gid_table *table;
	पूर्णांक ret = 0;
	पूर्णांक i;

	gid_attr.device = device;
	gid_attr.port_num = port;
	table = rdma_gid_table(device, port);

	mutex_lock(&table->lock);
	क्रम (i = 0; i < gid_tbl_len; ++i) अणु
		अगर (!device->ops.query_gid)
			जारी;
		ret = device->ops.query_gid(device, port, i, &gid_attr.gid);
		अगर (ret) अणु
			dev_warn(&device->dev,
				 "query_gid failed (%d) for index %d\n", ret,
				 i);
			जाओ err;
		पूर्ण
		gid_attr.index = i;
		add_modअगरy_gid(table, &gid_attr);
	पूर्ण
err:
	mutex_unlock(&table->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
ib_cache_update(काष्ठा ib_device *device, u32 port, bool enक्रमce_security)
अणु
	काष्ठा ib_port_attr       *tprops = शून्य;
	काष्ठा ib_pkey_cache      *pkey_cache = शून्य, *old_pkey_cache;
	पूर्णांक                        i;
	पूर्णांक                        ret;

	अगर (!rdma_is_port_valid(device, port))
		वापस -EINVAL;

	tprops = kदो_स्मृति(माप *tprops, GFP_KERNEL);
	अगर (!tprops)
		वापस -ENOMEM;

	ret = ib_query_port(device, port, tprops);
	अगर (ret) अणु
		dev_warn(&device->dev, "ib_query_port failed (%d)\n", ret);
		जाओ err;
	पूर्ण

	अगर (!rdma_protocol_roce(device, port)) अणु
		ret = config_non_roce_gid_cache(device, port,
						tprops->gid_tbl_len);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (tprops->pkey_tbl_len) अणु
		pkey_cache = kदो_स्मृति(काष्ठा_size(pkey_cache, table,
						 tprops->pkey_tbl_len),
				     GFP_KERNEL);
		अगर (!pkey_cache) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		pkey_cache->table_len = tprops->pkey_tbl_len;

		क्रम (i = 0; i < pkey_cache->table_len; ++i) अणु
			ret = ib_query_pkey(device, port, i,
					    pkey_cache->table + i);
			अगर (ret) अणु
				dev_warn(&device->dev,
					 "ib_query_pkey failed (%d) for index %d\n",
					 ret, i);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	ग_लिखो_lock_irq(&device->cache_lock);

	old_pkey_cache = device->port_data[port].cache.pkey;

	device->port_data[port].cache.pkey = pkey_cache;
	device->port_data[port].cache.lmc = tprops->lmc;
	device->port_data[port].cache.port_state = tprops->state;

	device->port_data[port].cache.subnet_prefix = tprops->subnet_prefix;
	ग_लिखो_unlock_irq(&device->cache_lock);

	अगर (enक्रमce_security)
		ib_security_cache_change(device,
					 port,
					 tprops->subnet_prefix);

	kमुक्त(old_pkey_cache);
	kमुक्त(tprops);
	वापस 0;

err:
	kमुक्त(pkey_cache);
	kमुक्त(tprops);
	वापस ret;
पूर्ण

अटल व्योम ib_cache_event_task(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा ib_update_work *work =
		container_of(_work, काष्ठा ib_update_work, work);
	पूर्णांक ret;

	/* Beक्रमe distributing the cache update event, first sync
	 * the cache.
	 */
	ret = ib_cache_update(work->event.device, work->event.element.port_num,
			      work->enक्रमce_security);

	/* GID event is notअगरied alपढ़ोy क्रम inभागidual GID entries by
	 * dispatch_gid_change_event(). Hence, notअगरiy क्रम rest of the
	 * events.
	 */
	अगर (!ret && work->event.event != IB_EVENT_GID_CHANGE)
		ib_dispatch_event_clients(&work->event);

	kमुक्त(work);
पूर्ण

अटल व्योम ib_generic_event_task(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा ib_update_work *work =
		container_of(_work, काष्ठा ib_update_work, work);

	ib_dispatch_event_clients(&work->event);
	kमुक्त(work);
पूर्ण

अटल bool is_cache_update_event(स्थिर काष्ठा ib_event *event)
अणु
	वापस (event->event == IB_EVENT_PORT_ERR    ||
		event->event == IB_EVENT_PORT_ACTIVE ||
		event->event == IB_EVENT_LID_CHANGE  ||
		event->event == IB_EVENT_PKEY_CHANGE ||
		event->event == IB_EVENT_CLIENT_REREGISTER ||
		event->event == IB_EVENT_GID_CHANGE);
पूर्ण

/**
 * ib_dispatch_event - Dispatch an asynchronous event
 * @event:Event to dispatch
 *
 * Low-level drivers must call ib_dispatch_event() to dispatch the
 * event to all रेजिस्टरed event handlers when an asynchronous event
 * occurs.
 */
व्योम ib_dispatch_event(स्थिर काष्ठा ib_event *event)
अणु
	काष्ठा ib_update_work *work;

	work = kzalloc(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस;

	अगर (is_cache_update_event(event))
		INIT_WORK(&work->work, ib_cache_event_task);
	अन्यथा
		INIT_WORK(&work->work, ib_generic_event_task);

	work->event = *event;
	अगर (event->event == IB_EVENT_PKEY_CHANGE ||
	    event->event == IB_EVENT_GID_CHANGE)
		work->enक्रमce_security = true;

	queue_work(ib_wq, &work->work);
पूर्ण
EXPORT_SYMBOL(ib_dispatch_event);

पूर्णांक ib_cache_setup_one(काष्ठा ib_device *device)
अणु
	u32 p;
	पूर्णांक err;

	rwlock_init(&device->cache_lock);

	err = gid_table_setup_one(device);
	अगर (err)
		वापस err;

	rdma_क्रम_each_port (device, p) अणु
		err = ib_cache_update(device, p, true);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ib_cache_release_one(काष्ठा ib_device *device)
अणु
	u32 p;

	/*
	 * The release function मुक्तs all the cache elements.
	 * This function should be called as part of मुक्तing
	 * all the device's resources when the cache could no
	 * दीर्घer be accessed.
	 */
	rdma_क्रम_each_port (device, p)
		kमुक्त(device->port_data[p].cache.pkey);

	gid_table_release_one(device);
पूर्ण

व्योम ib_cache_cleanup_one(काष्ठा ib_device *device)
अणु
	/* The cleanup function रुकोs क्रम all in-progress workqueue
	 * elements and cleans up the GID cache. This function should be
	 * called after the device was हटाओd from the devices list and
	 * all clients were हटाओd, so the cache exists but is
	 * non-functional and shouldn't be updated anymore.
	 */
	flush_workqueue(ib_wq);
	gid_table_cleanup_one(device);

	/*
	 * Flush the wq second समय क्रम any pending GID delete work.
	 */
	flush_workqueue(ib_wq);
पूर्ण
