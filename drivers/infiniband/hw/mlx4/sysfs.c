<शैली गुरु>
/*
 * Copyright (c) 2012 Mellanox Technologies.  All rights reserved.
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

/*#समावेश "core_priv.h"*/
#समावेश "mlx4_ib.h"
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>

#समावेश <rdma/ib_mad.h>
/*show_admin_alias_guid वापसs the administratively asचिन्हित value of that GUID.
 * Values वापसed in buf parameter string:
 *	0			- requests खोलोsm to assign a value.
 *	ffffffffffffffff	- delete this entry.
 *	other			- value asचिन्हित by administrator.
 */
अटल sमाप_प्रकार show_admin_alias_guid(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx4_ib_iov_sysfs_attr *mlx4_ib_iov_dentry =
		container_of(attr, काष्ठा mlx4_ib_iov_sysfs_attr, dentry);
	काष्ठा mlx4_ib_iov_port *port = mlx4_ib_iov_dentry->ctx;
	काष्ठा mlx4_ib_dev *mdev = port->dev;
	__be64 sysadmin_ag_val;

	sysadmin_ag_val = mlx4_get_admin_guid(mdev->dev,
					      mlx4_ib_iov_dentry->entry_num,
					      port->num);

	वापस sysfs_emit(buf, "%llx\n", be64_to_cpu(sysadmin_ag_val));
पूर्ण

/* store_admin_alias_guid stores the (new) administratively asचिन्हित value of that GUID.
 * Values in buf parameter string:
 *	0			- requests खोलोsm to assign a value.
 *	0xffffffffffffffff	- delete this entry.
 *	other			- guid value asचिन्हित by the administrator.
 */
अटल sमाप_प्रकार store_admin_alias_guid(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक record_num;/*0-15*/
	पूर्णांक guid_index_in_rec; /*0 - 7*/
	काष्ठा mlx4_ib_iov_sysfs_attr *mlx4_ib_iov_dentry =
		container_of(attr, काष्ठा mlx4_ib_iov_sysfs_attr, dentry);
	काष्ठा mlx4_ib_iov_port *port = mlx4_ib_iov_dentry->ctx;
	काष्ठा mlx4_ib_dev *mdev = port->dev;
	u64 sysadmin_ag_val;
	अचिन्हित दीर्घ flags;

	record_num = mlx4_ib_iov_dentry->entry_num / 8;
	guid_index_in_rec = mlx4_ib_iov_dentry->entry_num % 8;
	अगर (0 == record_num && 0 == guid_index_in_rec) अणु
		pr_err("GUID 0 block 0 is RO\n");
		वापस count;
	पूर्ण
	spin_lock_irqsave(&mdev->sriov.alias_guid.ag_work_lock, flags);
	माला_पूछो(buf, "%llx", &sysadmin_ag_val);
	*(__be64 *)&mdev->sriov.alias_guid.ports_guid[port->num - 1].
		all_rec_per_port[record_num].
		all_recs[GUID_REC_SIZE * guid_index_in_rec] =
			cpu_to_be64(sysadmin_ag_val);

	/* Change the state to be pending क्रम update */
	mdev->sriov.alias_guid.ports_guid[port->num - 1].all_rec_per_port[record_num].status
		= MLX4_GUID_INFO_STATUS_IDLE ;
	mlx4_set_admin_guid(mdev->dev, cpu_to_be64(sysadmin_ag_val),
			    mlx4_ib_iov_dentry->entry_num,
			    port->num);

	/* set the record index */
	mdev->sriov.alias_guid.ports_guid[port->num - 1].all_rec_per_port[record_num].guid_indexes
		|= mlx4_ib_get_aguid_comp_mask_from_ix(guid_index_in_rec);

	spin_unlock_irqrestore(&mdev->sriov.alias_guid.ag_work_lock, flags);
	mlx4_ib_init_alias_guid_work(mdev, port->num - 1);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_port_gid(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा mlx4_ib_iov_sysfs_attr *mlx4_ib_iov_dentry =
		container_of(attr, काष्ठा mlx4_ib_iov_sysfs_attr, dentry);
	काष्ठा mlx4_ib_iov_port *port = mlx4_ib_iov_dentry->ctx;
	काष्ठा mlx4_ib_dev *mdev = port->dev;
	जोड़ ib_gid gid;
	पूर्णांक ret;
	__be16 *raw;

	ret = __mlx4_ib_query_gid(&mdev->ib_dev, port->num,
				  mlx4_ib_iov_dentry->entry_num, &gid, 1);
	अगर (ret)
		वापस ret;

	raw = (__be16 *)gid.raw;
	वापस sysfs_emit(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
			  be16_to_cpu(raw[0]),
			  be16_to_cpu(raw[1]),
			  be16_to_cpu(raw[2]),
			  be16_to_cpu(raw[3]),
			  be16_to_cpu(raw[4]),
			  be16_to_cpu(raw[5]),
			  be16_to_cpu(raw[6]),
			  be16_to_cpu(raw[7]));
पूर्ण

अटल sमाप_प्रकार show_phys_port_pkey(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा mlx4_ib_iov_sysfs_attr *mlx4_ib_iov_dentry =
		container_of(attr, काष्ठा mlx4_ib_iov_sysfs_attr, dentry);
	काष्ठा mlx4_ib_iov_port *port = mlx4_ib_iov_dentry->ctx;
	काष्ठा mlx4_ib_dev *mdev = port->dev;
	u16 pkey;
	sमाप_प्रकार ret;

	ret = __mlx4_ib_query_pkey(&mdev->ib_dev, port->num,
				   mlx4_ib_iov_dentry->entry_num, &pkey, 1);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "0x%04x\n", pkey);
पूर्ण

#घोषणा DENTRY_REMOVE(_dentry)						\
करो अणु									\
	sysfs_हटाओ_file((_dentry)->kobj, &(_dentry)->dentry.attr);	\
पूर्ण जबतक (0);

अटल पूर्णांक create_sysfs_entry(व्योम *_ctx, काष्ठा mlx4_ib_iov_sysfs_attr *_dentry,
			      अक्षर *_name, काष्ठा kobject *_kobj,
			      sमाप_प्रकार (*show)(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf),
			      sमाप_प्रकार (*store)(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf, माप_प्रकार count)
			      )
अणु
	पूर्णांक ret = 0;
	काष्ठा mlx4_ib_iov_sysfs_attr *vdentry = _dentry;

	vdentry->ctx = _ctx;
	vdentry->dentry.show = show;
	vdentry->dentry.store = store;
	sysfs_attr_init(&vdentry->dentry.attr);
	vdentry->dentry.attr.name = vdentry->name;
	vdentry->dentry.attr.mode = 0;
	vdentry->kobj = _kobj;
	snम_लिखो(vdentry->name, 15, "%s", _name);

	अगर (vdentry->dentry.store)
		vdentry->dentry.attr.mode |= S_IWUSR;

	अगर (vdentry->dentry.show)
		vdentry->dentry.attr.mode |= S_IRUGO;

	ret = sysfs_create_file(vdentry->kobj, &vdentry->dentry.attr);
	अगर (ret) अणु
		pr_err("failed to create %s\n", vdentry->dentry.attr.name);
		vdentry->ctx = शून्य;
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक add_sysfs_port_mcg_attr(काष्ठा mlx4_ib_dev *device, पूर्णांक port_num,
		काष्ठा attribute *attr)
अणु
	काष्ठा mlx4_ib_iov_port *port = &device->iov_ports[port_num - 1];
	पूर्णांक ret;

	ret = sysfs_create_file(port->mcgs_parent, attr);
	अगर (ret)
		pr_err("failed to create %s\n", attr->name);

	वापस ret;
पूर्ण

व्योम del_sysfs_port_mcg_attr(काष्ठा mlx4_ib_dev *device, पूर्णांक port_num,
		काष्ठा attribute *attr)
अणु
	काष्ठा mlx4_ib_iov_port *port = &device->iov_ports[port_num - 1];

	sysfs_हटाओ_file(port->mcgs_parent, attr);
पूर्ण

अटल पूर्णांक add_port_entries(काष्ठा mlx4_ib_dev *device, पूर्णांक port_num)
अणु
	पूर्णांक i;
	अक्षर buff[11];
	काष्ठा mlx4_ib_iov_port *port = शून्य;
	पूर्णांक ret = 0 ;
	काष्ठा ib_port_attr attr;

	स_रखो(&attr, 0, माप(attr));
	/* get the physical gid and pkey table sizes.*/
	ret = __mlx4_ib_query_port(&device->ib_dev, port_num, &attr, 1);
	अगर (ret)
		जाओ err;

	port = &device->iov_ports[port_num - 1];
	port->dev = device;
	port->num = port_num;
	/* Directory काष्ठाure:
	 * iov -
	 *   port num -
	 *	admin_guids
	 *	gids (operational)
	 *	mcg_table
	 */
	port->dentr_ar = kzalloc(माप (काष्ठा mlx4_ib_iov_sysfs_attr_ar),
				 GFP_KERNEL);
	अगर (!port->dentr_ar) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	प्र_लिखो(buff, "%d", port_num);
	port->cur_port = kobject_create_and_add(buff,
				 kobject_get(device->ports_parent));
	अगर (!port->cur_port) अणु
		ret = -ENOMEM;
		जाओ kobj_create_err;
	पूर्ण
	/* admin GUIDs */
	port->admin_alias_parent = kobject_create_and_add("admin_guids",
						  kobject_get(port->cur_port));
	अगर (!port->admin_alias_parent) अणु
		ret = -ENOMEM;
		जाओ err_admin_guids;
	पूर्ण
	क्रम (i = 0 ; i < attr.gid_tbl_len; i++) अणु
		प्र_लिखो(buff, "%d", i);
		port->dentr_ar->dentries[i].entry_num = i;
		ret = create_sysfs_entry(port, &port->dentr_ar->dentries[i],
					  buff, port->admin_alias_parent,
					  show_admin_alias_guid, store_admin_alias_guid);
		अगर (ret)
			जाओ err_admin_alias_parent;
	पूर्ण

	/* gids subdirectory (operational gids) */
	port->gids_parent = kobject_create_and_add("gids",
						  kobject_get(port->cur_port));
	अगर (!port->gids_parent) अणु
		ret = -ENOMEM;
		जाओ err_gids;
	पूर्ण

	क्रम (i = 0 ; i < attr.gid_tbl_len; i++) अणु
		प्र_लिखो(buff, "%d", i);
		port->dentr_ar->dentries[attr.gid_tbl_len + i].entry_num = i;
		ret = create_sysfs_entry(port,
					 &port->dentr_ar->dentries[attr.gid_tbl_len + i],
					 buff,
					 port->gids_parent, show_port_gid, शून्य);
		अगर (ret)
			जाओ err_gids_parent;
	पूर्ण

	/* physical port pkey table */
	port->pkeys_parent =
		kobject_create_and_add("pkeys", kobject_get(port->cur_port));
	अगर (!port->pkeys_parent) अणु
		ret = -ENOMEM;
		जाओ err_pkeys;
	पूर्ण

	क्रम (i = 0 ; i < attr.pkey_tbl_len; i++) अणु
		प्र_लिखो(buff, "%d", i);
		port->dentr_ar->dentries[2 * attr.gid_tbl_len + i].entry_num = i;
		ret = create_sysfs_entry(port,
					 &port->dentr_ar->dentries[2 * attr.gid_tbl_len + i],
					 buff, port->pkeys_parent,
					 show_phys_port_pkey, शून्य);
		अगर (ret)
			जाओ err_pkeys_parent;
	पूर्ण

	/* MCGs table */
	port->mcgs_parent =
		kobject_create_and_add("mcgs", kobject_get(port->cur_port));
	अगर (!port->mcgs_parent) अणु
		ret = -ENOMEM;
		जाओ err_mcgs;
	पूर्ण
	वापस 0;

err_mcgs:
	kobject_put(port->cur_port);

err_pkeys_parent:
	kobject_put(port->pkeys_parent);

err_pkeys:
	kobject_put(port->cur_port);

err_gids_parent:
	kobject_put(port->gids_parent);

err_gids:
	kobject_put(port->cur_port);

err_admin_alias_parent:
	kobject_put(port->admin_alias_parent);

err_admin_guids:
	kobject_put(port->cur_port);
	kobject_put(port->cur_port); /* once more क्रम create_and_add buff */

kobj_create_err:
	kobject_put(device->ports_parent);
	kमुक्त(port->dentr_ar);

err:
	pr_err("add_port_entries FAILED: for port:%d, error: %d\n",
	       port_num, ret);
	वापस ret;
पूर्ण

अटल व्योम get_name(काष्ठा mlx4_ib_dev *dev, अक्षर *name, पूर्णांक i, पूर्णांक max)
अणु
	/* pci_name क्रमmat is: bus:dev:func -> xxxx:yy:zz.n
	 * with no ARI only 3 last bits are used so when the fn is higher than 8
	 * need to add it to the dev num, so count in the last number will be
	 * modulo 8 */
	snम_लिखो(name, max, "%.8s%.2d.%d", pci_name(dev->dev->persist->pdev),
		 i / 8, i % 8);
पूर्ण

काष्ठा mlx4_port अणु
	काष्ठा kobject         kobj;
	काष्ठा mlx4_ib_dev    *dev;
	काष्ठा attribute_group pkey_group;
	काष्ठा attribute_group gid_group;
	काष्ठा device_attribute	enable_smi_admin;
	काष्ठा device_attribute	smi_enabled;
	पूर्णांक		       slave;
	u8                     port_num;
पूर्ण;


अटल व्योम mlx4_port_release(काष्ठा kobject *kobj)
अणु
	काष्ठा mlx4_port *p = container_of(kobj, काष्ठा mlx4_port, kobj);
	काष्ठा attribute *a;
	पूर्णांक i;

	क्रम (i = 0; (a = p->pkey_group.attrs[i]); ++i)
		kमुक्त(a);
	kमुक्त(p->pkey_group.attrs);
	क्रम (i = 0; (a = p->gid_group.attrs[i]); ++i)
		kमुक्त(a);
	kमुक्त(p->gid_group.attrs);
	kमुक्त(p);
पूर्ण

काष्ठा port_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा mlx4_port *, काष्ठा port_attribute *, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा mlx4_port *, काष्ठा port_attribute *,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

अटल sमाप_प्रकार port_attr_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा port_attribute *port_attr =
		container_of(attr, काष्ठा port_attribute, attr);
	काष्ठा mlx4_port *p = container_of(kobj, काष्ठा mlx4_port, kobj);

	अगर (!port_attr->show)
		वापस -EIO;
	वापस port_attr->show(p, port_attr, buf);
पूर्ण

अटल sमाप_प्रकार port_attr_store(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा port_attribute *port_attr =
		container_of(attr, काष्ठा port_attribute, attr);
	काष्ठा mlx4_port *p = container_of(kobj, काष्ठा mlx4_port, kobj);

	अगर (!port_attr->store)
		वापस -EIO;
	वापस port_attr->store(p, port_attr, buf, size);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops port_sysfs_ops = अणु
	.show = port_attr_show,
	.store = port_attr_store,
पूर्ण;

अटल काष्ठा kobj_type port_type = अणु
	.release    = mlx4_port_release,
	.sysfs_ops  = &port_sysfs_ops,
पूर्ण;

काष्ठा port_table_attribute अणु
	काष्ठा port_attribute	attr;
	अक्षर			name[8];
	पूर्णांक			index;
पूर्ण;

अटल sमाप_प्रकार show_port_pkey(काष्ठा mlx4_port *p, काष्ठा port_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा port_table_attribute *tab_attr =
		container_of(attr, काष्ठा port_table_attribute, attr);
	काष्ठा pkey_mgt *m = &p->dev->pkeys;
	u8 key = m->virt2phys_pkey[p->slave][p->port_num - 1][tab_attr->index];

	अगर (key >= p->dev->dev->caps.pkey_table_len[p->port_num])
		वापस sysfs_emit(buf, "none\n");
	वापस sysfs_emit(buf, "%d\n", key);
पूर्ण

अटल sमाप_प्रकार store_port_pkey(काष्ठा mlx4_port *p, काष्ठा port_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा port_table_attribute *tab_attr =
		container_of(attr, काष्ठा port_table_attribute, attr);
	पूर्णांक idx;
	पूर्णांक err;

	/* करो not allow remapping Dom0 भव pkey table */
	अगर (p->slave == mlx4_master_func_num(p->dev->dev))
		वापस -EINVAL;

	अगर (!strnहालcmp(buf, "no", 2))
		idx = p->dev->dev->phys_caps.pkey_phys_table_len[p->port_num] - 1;
	अन्यथा अगर (माला_पूछो(buf, "%i", &idx) != 1 ||
		 idx >= p->dev->dev->caps.pkey_table_len[p->port_num] ||
		 idx < 0)
		वापस -EINVAL;

	p->dev->pkeys.virt2phys_pkey[p->slave][p->port_num - 1]
				    [tab_attr->index] = idx;
	mlx4_sync_pkey_table(p->dev->dev, p->slave, p->port_num,
			     tab_attr->index, idx);
	err = mlx4_gen_pkey_eqe(p->dev->dev, p->slave, p->port_num);
	अगर (err) अणु
		pr_err("mlx4_gen_pkey_eqe failed for slave %d,"
		       " port %d, index %d\n", p->slave, p->port_num, idx);
		वापस err;
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_port_gid_idx(काष्ठा mlx4_port *p,
				 काष्ठा port_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", p->slave);
पूर्ण

अटल काष्ठा attribute **
alloc_group_attrs(sमाप_प्रकार (*show)(काष्ठा mlx4_port *,
				  काष्ठा port_attribute *, अक्षर *buf),
		  sमाप_प्रकार (*store)(काष्ठा mlx4_port *, काष्ठा port_attribute *,
				   स्थिर अक्षर *buf, माप_प्रकार count),
		  पूर्णांक len)
अणु
	काष्ठा attribute **tab_attr;
	काष्ठा port_table_attribute *element;
	पूर्णांक i;

	tab_attr = kसुस्मृति(1 + len, माप (काष्ठा attribute *), GFP_KERNEL);
	अगर (!tab_attr)
		वापस शून्य;

	क्रम (i = 0; i < len; i++) अणु
		element = kzalloc(माप (काष्ठा port_table_attribute),
				  GFP_KERNEL);
		अगर (!element)
			जाओ err;
		अगर (snम_लिखो(element->name, माप (element->name),
			     "%d", i) >= माप (element->name)) अणु
			kमुक्त(element);
			जाओ err;
		पूर्ण
		sysfs_attr_init(&element->attr.attr);
		element->attr.attr.name  = element->name;
		अगर (store) अणु
			element->attr.attr.mode  = S_IWUSR | S_IRUGO;
			element->attr.store	 = store;
		पूर्ण अन्यथा
			element->attr.attr.mode  = S_IRUGO;

		element->attr.show       = show;
		element->index		 = i;
		tab_attr[i] = &element->attr.attr;
	पूर्ण
	वापस tab_attr;

err:
	जबतक (--i >= 0)
		kमुक्त(tab_attr[i]);
	kमुक्त(tab_attr);
	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार sysfs_show_smi_enabled(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx4_port *p =
		container_of(attr, काष्ठा mlx4_port, smi_enabled);

	वापस sysfs_emit(buf, "%d\n",
			  !!mlx4_vf_smi_enabled(p->dev->dev, p->slave,
						p->port_num));
पूर्ण

अटल sमाप_प्रकार sysfs_show_enable_smi_admin(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा mlx4_port *p =
		container_of(attr, काष्ठा mlx4_port, enable_smi_admin);

	वापस sysfs_emit(buf, "%d\n",
			  !!mlx4_vf_get_enable_smi_admin(p->dev->dev, p->slave,
							 p->port_num));
पूर्ण

अटल sमाप_प्रकार sysfs_store_enable_smi_admin(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mlx4_port *p =
		container_of(attr, काष्ठा mlx4_port, enable_smi_admin);
	पूर्णांक enable;

	अगर (माला_पूछो(buf, "%i", &enable) != 1 ||
	    enable < 0 || enable > 1)
		वापस -EINVAL;

	अगर (mlx4_vf_set_enable_smi_admin(p->dev->dev, p->slave, p->port_num, enable))
		वापस -EINVAL;
	वापस count;
पूर्ण

अटल पूर्णांक add_vf_smi_entries(काष्ठा mlx4_port *p)
अणु
	पूर्णांक is_eth = rdma_port_get_link_layer(&p->dev->ib_dev, p->port_num) ==
			IB_LINK_LAYER_ETHERNET;
	पूर्णांक ret;

	/* करो not display entries अगर eth transport, or अगर master */
	अगर (is_eth || p->slave == mlx4_master_func_num(p->dev->dev))
		वापस 0;

	sysfs_attr_init(&p->smi_enabled.attr);
	p->smi_enabled.show = sysfs_show_smi_enabled;
	p->smi_enabled.store = शून्य;
	p->smi_enabled.attr.name = "smi_enabled";
	p->smi_enabled.attr.mode = 0444;
	ret = sysfs_create_file(&p->kobj, &p->smi_enabled.attr);
	अगर (ret) अणु
		pr_err("failed to create smi_enabled\n");
		वापस ret;
	पूर्ण

	sysfs_attr_init(&p->enable_smi_admin.attr);
	p->enable_smi_admin.show = sysfs_show_enable_smi_admin;
	p->enable_smi_admin.store = sysfs_store_enable_smi_admin;
	p->enable_smi_admin.attr.name = "enable_smi_admin";
	p->enable_smi_admin.attr.mode = 0644;
	ret = sysfs_create_file(&p->kobj, &p->enable_smi_admin.attr);
	अगर (ret) अणु
		pr_err("failed to create enable_smi_admin\n");
		sysfs_हटाओ_file(&p->kobj, &p->smi_enabled.attr);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम हटाओ_vf_smi_entries(काष्ठा mlx4_port *p)
अणु
	पूर्णांक is_eth = rdma_port_get_link_layer(&p->dev->ib_dev, p->port_num) ==
			IB_LINK_LAYER_ETHERNET;

	अगर (is_eth || p->slave == mlx4_master_func_num(p->dev->dev))
		वापस;

	sysfs_हटाओ_file(&p->kobj, &p->smi_enabled.attr);
	sysfs_हटाओ_file(&p->kobj, &p->enable_smi_admin.attr);
पूर्ण

अटल पूर्णांक add_port(काष्ठा mlx4_ib_dev *dev, पूर्णांक port_num, पूर्णांक slave)
अणु
	काष्ठा mlx4_port *p;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक is_eth = rdma_port_get_link_layer(&dev->ib_dev, port_num) ==
			IB_LINK_LAYER_ETHERNET;

	p = kzalloc(माप *p, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->dev = dev;
	p->port_num = port_num;
	p->slave = slave;

	ret = kobject_init_and_add(&p->kobj, &port_type,
				   kobject_get(dev->dev_ports_parent[slave]),
				   "%d", port_num);
	अगर (ret)
		जाओ err_alloc;

	p->pkey_group.name  = "pkey_idx";
	p->pkey_group.attrs =
		alloc_group_attrs(show_port_pkey,
				  is_eth ? शून्य : store_port_pkey,
				  dev->dev->caps.pkey_table_len[port_num]);
	अगर (!p->pkey_group.attrs) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	ret = sysfs_create_group(&p->kobj, &p->pkey_group);
	अगर (ret)
		जाओ err_मुक्त_pkey;

	p->gid_group.name  = "gid_idx";
	p->gid_group.attrs = alloc_group_attrs(show_port_gid_idx, शून्य, 1);
	अगर (!p->gid_group.attrs) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_pkey;
	पूर्ण

	ret = sysfs_create_group(&p->kobj, &p->gid_group);
	अगर (ret)
		जाओ err_मुक्त_gid;

	ret = add_vf_smi_entries(p);
	अगर (ret)
		जाओ err_मुक्त_gid;

	list_add_tail(&p->kobj.entry, &dev->pkeys.pkey_port_list[slave]);
	वापस 0;

err_मुक्त_gid:
	kमुक्त(p->gid_group.attrs[0]);
	kमुक्त(p->gid_group.attrs);

err_मुक्त_pkey:
	क्रम (i = 0; i < dev->dev->caps.pkey_table_len[port_num]; ++i)
		kमुक्त(p->pkey_group.attrs[i]);
	kमुक्त(p->pkey_group.attrs);

err_alloc:
	kobject_put(dev->dev_ports_parent[slave]);
	kमुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक रेजिस्टर_one_pkey_tree(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave)
अणु
	अक्षर name[32];
	पूर्णांक err;
	पूर्णांक port;
	काष्ठा kobject *p, *t;
	काष्ठा mlx4_port *mport;
	काष्ठा mlx4_active_ports actv_ports;

	get_name(dev, name, slave, माप name);

	dev->pkeys.device_parent[slave] =
		kobject_create_and_add(name, kobject_get(dev->iov_parent));

	अगर (!dev->pkeys.device_parent[slave]) अणु
		err = -ENOMEM;
		जाओ fail_dev;
	पूर्ण

	INIT_LIST_HEAD(&dev->pkeys.pkey_port_list[slave]);

	dev->dev_ports_parent[slave] =
		kobject_create_and_add("ports",
				       kobject_get(dev->pkeys.device_parent[slave]));

	अगर (!dev->dev_ports_parent[slave]) अणु
		err = -ENOMEM;
		जाओ err_ports;
	पूर्ण

	actv_ports = mlx4_get_active_ports(dev->dev, slave);

	क्रम (port = 1; port <= dev->dev->caps.num_ports; ++port) अणु
		अगर (!test_bit(port - 1, actv_ports.ports))
			जारी;
		err = add_port(dev, port, slave);
		अगर (err)
			जाओ err_add;
	पूर्ण
	वापस 0;

err_add:
	list_क्रम_each_entry_safe(p, t,
				 &dev->pkeys.pkey_port_list[slave],
				 entry) अणु
		list_del(&p->entry);
		mport = container_of(p, काष्ठा mlx4_port, kobj);
		sysfs_हटाओ_group(p, &mport->pkey_group);
		sysfs_हटाओ_group(p, &mport->gid_group);
		हटाओ_vf_smi_entries(mport);
		kobject_put(p);
	पूर्ण
	kobject_put(dev->dev_ports_parent[slave]);

err_ports:
	kobject_put(dev->pkeys.device_parent[slave]);
	/* extra put क्रम the device_parent create_and_add */
	kobject_put(dev->pkeys.device_parent[slave]);

fail_dev:
	kobject_put(dev->iov_parent);
	वापस err;
पूर्ण

अटल पूर्णांक रेजिस्टर_pkey_tree(काष्ठा mlx4_ib_dev *device)
अणु
	पूर्णांक i;

	अगर (!mlx4_is_master(device->dev))
		वापस 0;

	क्रम (i = 0; i <= device->dev->persist->num_vfs; ++i)
		रेजिस्टर_one_pkey_tree(device, i);

	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_pkey_tree(काष्ठा mlx4_ib_dev *device)
अणु
	पूर्णांक slave;
	काष्ठा kobject *p, *t;
	काष्ठा mlx4_port *port;

	अगर (!mlx4_is_master(device->dev))
		वापस;

	क्रम (slave = device->dev->persist->num_vfs; slave >= 0; --slave) अणु
		list_क्रम_each_entry_safe(p, t,
					 &device->pkeys.pkey_port_list[slave],
					 entry) अणु
			list_del(&p->entry);
			port = container_of(p, काष्ठा mlx4_port, kobj);
			sysfs_हटाओ_group(p, &port->pkey_group);
			sysfs_हटाओ_group(p, &port->gid_group);
			हटाओ_vf_smi_entries(port);
			kobject_put(p);
			kobject_put(device->dev_ports_parent[slave]);
		पूर्ण
		kobject_put(device->dev_ports_parent[slave]);
		kobject_put(device->pkeys.device_parent[slave]);
		kobject_put(device->pkeys.device_parent[slave]);
		kobject_put(device->iov_parent);
	पूर्ण
पूर्ण

पूर्णांक mlx4_ib_device_रेजिस्टर_sysfs(काष्ठा mlx4_ib_dev *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!mlx4_is_master(dev->dev))
		वापस 0;

	dev->iov_parent = kobject_create_and_add("iov", &dev->ib_dev.dev.kobj);
	अगर (!dev->iov_parent) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	dev->ports_parent =
		kobject_create_and_add("ports",
				       kobject_get(dev->iov_parent));
	अगर (!dev->ports_parent) अणु
		ret = -ENOMEM;
		जाओ err_ports;
	पूर्ण

	rdma_क्रम_each_port(&dev->ib_dev, i) अणु
		ret = add_port_entries(dev, i);
		अगर (ret)
			जाओ err_add_entries;
	पूर्ण

	ret = रेजिस्टर_pkey_tree(dev);
	अगर (ret)
		जाओ err_add_entries;
	वापस 0;

err_add_entries:
	kobject_put(dev->ports_parent);

err_ports:
	kobject_put(dev->iov_parent);
err:
	pr_err("mlx4_ib_device_register_sysfs error (%d)\n", ret);
	वापस ret;
पूर्ण

अटल व्योम unरेजिस्टर_alias_guid_tree(काष्ठा mlx4_ib_dev *device)
अणु
	काष्ठा mlx4_ib_iov_port *p;
	पूर्णांक i;

	अगर (!mlx4_is_master(device->dev))
		वापस;

	क्रम (i = 0; i < device->dev->caps.num_ports; i++) अणु
		p = &device->iov_ports[i];
		kobject_put(p->admin_alias_parent);
		kobject_put(p->gids_parent);
		kobject_put(p->pkeys_parent);
		kobject_put(p->mcgs_parent);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->dev->ports_parent);
		kमुक्त(p->dentr_ar);
	पूर्ण
पूर्ण

व्योम mlx4_ib_device_unरेजिस्टर_sysfs(काष्ठा mlx4_ib_dev *device)
अणु
	unरेजिस्टर_alias_guid_tree(device);
	unरेजिस्टर_pkey_tree(device);
	kobject_put(device->ports_parent);
	kobject_put(device->iov_parent);
	kobject_put(device->iov_parent);
पूर्ण
