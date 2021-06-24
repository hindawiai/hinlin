<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file supports the /sys/firmware/sgi_uv topology tree on HPE UV.
 *
 *  Copyright (c) 2020 Hewlett Packard Enterprise.  All Rights Reserved.
 *  Copyright (c) Justin Ernst
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/kobject.h>
#समावेश <यंत्र/uv/मूलप्रण.स>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/uv/uv_hub.h>
#समावेश <यंत्र/uv/uv_geo.h>

#घोषणा INVALID_CNODE -1

काष्ठा kobject *sgi_uv_kobj;
अटल काष्ठा kset *uv_pcibus_kset;
अटल काष्ठा kset *uv_hubs_kset;
अटल काष्ठा uv_bios_hub_info *hub_buf;
अटल काष्ठा uv_bios_port_info **port_buf;
अटल काष्ठा uv_hub **uv_hubs;
अटल काष्ठा uv_pci_top_obj **uv_pci_objs;
अटल पूर्णांक num_pci_lines;
अटल पूर्णांक num_cnodes;
अटल पूर्णांक *prev_obj_to_cnode;
अटल पूर्णांक uv_bios_obj_cnt;
अटल चिन्हित लघु uv_master_nasid = -1;
अटल व्योम *uv_biosheap;

अटल स्थिर अक्षर *uv_type_string(व्योम)
अणु
	अगर (is_uv5_hub())
		वापस "9.0";
	अन्यथा अगर (is_uv4a_hub())
		वापस "7.1";
	अन्यथा अगर (is_uv4_hub())
		वापस "7.0";
	अन्यथा अगर (is_uv3_hub())
		वापस "5.0";
	अन्यथा अगर (is_uv2_hub())
		वापस "3.0";
	अन्यथा अगर (uv_get_hubless_प्रणाली())
		वापस "0.1";
	अन्यथा
		वापस "unknown";
पूर्ण

अटल पूर्णांक ordinal_to_nasid(पूर्णांक ordinal)
अणु
	अगर (ordinal < num_cnodes && ordinal >= 0)
		वापस UV_PNODE_TO_NASID(uv_blade_to_pnode(ordinal));
	अन्यथा
		वापस -1;
पूर्ण

अटल जोड़ geoid_u cnode_to_geoid(पूर्णांक cnode)
अणु
	जोड़ geoid_u geoid;

	uv_bios_get_geoinfo(ordinal_to_nasid(cnode), (u64)माप(जोड़ geoid_u), (u64 *)&geoid);
	वापस geoid;
पूर्ण

अटल पूर्णांक location_to_bpos(अक्षर *location, पूर्णांक *rack, पूर्णांक *slot, पूर्णांक *blade)
अणु
	अक्षर type, r, b, h;
	पूर्णांक idb, idh;

	अगर (माला_पूछो(location, "%c%03d%c%02d%c%2d%c%d",
			 &r, rack, &type, slot, &b, &idb, &h, &idh) != 8)
		वापस -1;
	*blade = idb * 2 + idh;

	वापस 0;
पूर्ण

अटल पूर्णांक cache_obj_to_cnode(काष्ठा uv_bios_hub_info *obj)
अणु
	पूर्णांक cnode;
	जोड़ geoid_u geoid;
	पूर्णांक obj_rack, obj_slot, obj_blade;
	पूर्णांक rack, slot, blade;

	अगर (!obj->f.fields.this_part && !obj->f.fields.is_shared)
		वापस 0;

	अगर (location_to_bpos(obj->location, &obj_rack, &obj_slot, &obj_blade))
		वापस -1;

	क्रम (cnode = 0; cnode < num_cnodes; cnode++) अणु
		geoid = cnode_to_geoid(cnode);
		rack = geo_rack(geoid);
		slot = geo_slot(geoid);
		blade = geo_blade(geoid);
		अगर (obj_rack == rack && obj_slot == slot && obj_blade == blade)
			prev_obj_to_cnode[obj->id] = cnode;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_obj_to_cnode(पूर्णांक obj_id)
अणु
	वापस prev_obj_to_cnode[obj_id];
पूर्ण

काष्ठा uv_hub अणु
	काष्ठा kobject kobj;
	काष्ठा uv_bios_hub_info *hub_info;
	काष्ठा uv_port **ports;
पूर्ण;

#घोषणा to_uv_hub(kobj_ptr) container_of(kobj_ptr, काष्ठा uv_hub, kobj)

अटल sमाप_प्रकार hub_name_show(काष्ठा uv_bios_hub_info *hub_info, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", hub_info->name);
पूर्ण

अटल sमाप_प्रकार hub_location_show(काष्ठा uv_bios_hub_info *hub_info, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", hub_info->location);
पूर्ण

अटल sमाप_प्रकार hub_partition_show(काष्ठा uv_bios_hub_info *hub_info, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", hub_info->f.fields.this_part);
पूर्ण

अटल sमाप_प्रकार hub_shared_show(काष्ठा uv_bios_hub_info *hub_info, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", hub_info->f.fields.is_shared);
पूर्ण
अटल sमाप_प्रकार hub_nasid_show(काष्ठा uv_bios_hub_info *hub_info, अक्षर *buf)
अणु
	पूर्णांक cnode = get_obj_to_cnode(hub_info->id);

	वापस प्र_लिखो(buf, "%d\n", ordinal_to_nasid(cnode));
पूर्ण
अटल sमाप_प्रकार hub_cnode_show(काष्ठा uv_bios_hub_info *hub_info, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", get_obj_to_cnode(hub_info->id));
पूर्ण

काष्ठा hub_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा uv_bios_hub_info *hub_info, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा uv_bios_hub_info *hub_info, स्थिर अक्षर *buf, माप_प्रकार sz);
पूर्ण;

अटल काष्ठा hub_sysfs_entry name_attribute =
	__ATTR(name, 0444, hub_name_show, शून्य);
अटल काष्ठा hub_sysfs_entry location_attribute =
	__ATTR(location, 0444, hub_location_show, शून्य);
अटल काष्ठा hub_sysfs_entry partition_attribute =
	__ATTR(this_partition, 0444, hub_partition_show, शून्य);
अटल काष्ठा hub_sysfs_entry shared_attribute =
	__ATTR(shared, 0444, hub_shared_show, शून्य);
अटल काष्ठा hub_sysfs_entry nasid_attribute =
	__ATTR(nasid, 0444, hub_nasid_show, शून्य);
अटल काष्ठा hub_sysfs_entry cnode_attribute =
	__ATTR(cnode, 0444, hub_cnode_show, शून्य);

अटल काष्ठा attribute *uv_hub_attrs[] = अणु
	&name_attribute.attr,
	&location_attribute.attr,
	&partition_attribute.attr,
	&shared_attribute.attr,
	&nasid_attribute.attr,
	&cnode_attribute.attr,
	शून्य,
पूर्ण;

अटल व्योम hub_release(काष्ठा kobject *kobj)
अणु
	काष्ठा uv_hub *hub = to_uv_hub(kobj);

	kमुक्त(hub);
पूर्ण

अटल sमाप_प्रकार hub_type_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा uv_hub *hub = to_uv_hub(kobj);
	काष्ठा uv_bios_hub_info *bios_hub_info = hub->hub_info;
	काष्ठा hub_sysfs_entry *entry;

	entry = container_of(attr, काष्ठा hub_sysfs_entry, attr);

	अगर (!entry->show)
		वापस -EIO;

	वापस entry->show(bios_hub_info, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops hub_sysfs_ops = अणु
	.show = hub_type_show,
पूर्ण;

अटल काष्ठा kobj_type hub_attr_type = अणु
	.release	= hub_release,
	.sysfs_ops	= &hub_sysfs_ops,
	.शेष_attrs	= uv_hub_attrs,
पूर्ण;

अटल पूर्णांक uv_hubs_init(व्योम)
अणु
	s64 biosr;
	u64 sz;
	पूर्णांक i, ret;

	prev_obj_to_cnode = kदो_स्मृति_array(uv_bios_obj_cnt, माप(*prev_obj_to_cnode),
					 GFP_KERNEL);
	अगर (!prev_obj_to_cnode)
		वापस -ENOMEM;

	क्रम (i = 0; i < uv_bios_obj_cnt; i++)
		prev_obj_to_cnode[i] = INVALID_CNODE;

	uv_hubs_kset = kset_create_and_add("hubs", शून्य, sgi_uv_kobj);
	अगर (!uv_hubs_kset) अणु
		ret = -ENOMEM;
		जाओ err_hubs_kset;
	पूर्ण
	sz = uv_bios_obj_cnt * माप(*hub_buf);
	hub_buf = kzalloc(sz, GFP_KERNEL);
	अगर (!hub_buf) अणु
		ret = -ENOMEM;
		जाओ err_hub_buf;
	पूर्ण

	biosr = uv_bios_क्रमागत_objs((u64)uv_master_nasid, sz, (u64 *)hub_buf);
	अगर (biosr) अणु
		ret = -EINVAL;
		जाओ err_क्रमागत_objs;
	पूर्ण

	uv_hubs = kसुस्मृति(uv_bios_obj_cnt, माप(*uv_hubs), GFP_KERNEL);
	अगर (!uv_hubs) अणु
		ret = -ENOMEM;
		जाओ err_क्रमागत_objs;
	पूर्ण

	क्रम (i = 0; i < uv_bios_obj_cnt; i++) अणु
		uv_hubs[i] = kzalloc(माप(*uv_hubs[i]), GFP_KERNEL);
		अगर (!uv_hubs[i]) अणु
			i--;
			ret = -ENOMEM;
			जाओ err_hubs;
		पूर्ण

		uv_hubs[i]->hub_info = &hub_buf[i];
		cache_obj_to_cnode(uv_hubs[i]->hub_info);

		uv_hubs[i]->kobj.kset = uv_hubs_kset;

		ret = kobject_init_and_add(&uv_hubs[i]->kobj, &hub_attr_type,
					  शून्य, "hub_%u", hub_buf[i].id);
		अगर (ret)
			जाओ err_hubs;
		kobject_uevent(&uv_hubs[i]->kobj, KOBJ_ADD);
	पूर्ण
	वापस 0;

err_hubs:
	क्रम (; i >= 0; i--)
		kobject_put(&uv_hubs[i]->kobj);
	kमुक्त(uv_hubs);
err_क्रमागत_objs:
	kमुक्त(hub_buf);
err_hub_buf:
	kset_unरेजिस्टर(uv_hubs_kset);
err_hubs_kset:
	kमुक्त(prev_obj_to_cnode);
	वापस ret;

पूर्ण

अटल व्योम uv_hubs_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < uv_bios_obj_cnt; i++)
		kobject_put(&uv_hubs[i]->kobj);

	kमुक्त(uv_hubs);
	kमुक्त(hub_buf);
	kset_unरेजिस्टर(uv_hubs_kset);
	kमुक्त(prev_obj_to_cnode);
पूर्ण

काष्ठा uv_port अणु
	काष्ठा kobject kobj;
	काष्ठा uv_bios_port_info *port_info;
पूर्ण;

#घोषणा to_uv_port(kobj_ptr) container_of(kobj_ptr, काष्ठा uv_port, kobj)

अटल sमाप_प्रकार uv_port_conn_hub_show(काष्ठा uv_bios_port_info *port, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", port->conn_id);
पूर्ण

अटल sमाप_प्रकार uv_port_conn_port_show(काष्ठा uv_bios_port_info *port, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", port->conn_port);
पूर्ण

काष्ठा uv_port_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा uv_bios_port_info *port_info, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा uv_bios_port_info *port_info, स्थिर अक्षर *buf, माप_प्रकार size);
पूर्ण;

अटल काष्ठा uv_port_sysfs_entry uv_port_conn_hub_attribute =
	__ATTR(conn_hub, 0444, uv_port_conn_hub_show, शून्य);
अटल काष्ठा uv_port_sysfs_entry uv_port_conn_port_attribute =
	__ATTR(conn_port, 0444, uv_port_conn_port_show, शून्य);

अटल काष्ठा attribute *uv_port_attrs[] = अणु
	&uv_port_conn_hub_attribute.attr,
	&uv_port_conn_port_attribute.attr,
	शून्य,
पूर्ण;

अटल व्योम uv_port_release(काष्ठा kobject *kobj)
अणु
	काष्ठा uv_port *port = to_uv_port(kobj);

	kमुक्त(port);
पूर्ण

अटल sमाप_प्रकार uv_port_type_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा uv_port *port = to_uv_port(kobj);
	काष्ठा uv_bios_port_info *port_info = port->port_info;
	काष्ठा uv_port_sysfs_entry *entry;

	entry = container_of(attr, काष्ठा uv_port_sysfs_entry, attr);

	अगर (!entry->show)
		वापस -EIO;

	वापस entry->show(port_info, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops uv_port_sysfs_ops = अणु
	.show = uv_port_type_show,
पूर्ण;

अटल काष्ठा kobj_type uv_port_attr_type = अणु
	.release	= uv_port_release,
	.sysfs_ops	= &uv_port_sysfs_ops,
	.शेष_attrs	= uv_port_attrs,
पूर्ण;

अटल पूर्णांक uv_ports_init(व्योम)
अणु
	s64 biosr;
	पूर्णांक j = 0, k = 0, ret, sz;

	port_buf = kसुस्मृति(uv_bios_obj_cnt, माप(*port_buf), GFP_KERNEL);
	अगर (!port_buf)
		वापस -ENOMEM;

	क्रम (j = 0; j < uv_bios_obj_cnt; j++) अणु
		sz = hub_buf[j].ports * माप(*port_buf[j]);
		port_buf[j] = kzalloc(sz, GFP_KERNEL);
		अगर (!port_buf[j]) अणु
			ret = -ENOMEM;
			j--;
			जाओ err_port_info;
		पूर्ण
		biosr = uv_bios_क्रमागत_ports((u64)uv_master_nasid, (u64)hub_buf[j].id, sz,
					(u64 *)port_buf[j]);
		अगर (biosr) अणु
			ret = -EINVAL;
			जाओ err_port_info;
		पूर्ण
	पूर्ण
	क्रम (j = 0; j < uv_bios_obj_cnt; j++) अणु
		uv_hubs[j]->ports = kसुस्मृति(hub_buf[j].ports,
					   माप(*uv_hubs[j]->ports), GFP_KERNEL);
		अगर (!uv_hubs[j]->ports) अणु
			ret = -ENOMEM;
			j--;
			जाओ err_ports;
		पूर्ण
	पूर्ण
	क्रम (j = 0; j < uv_bios_obj_cnt; j++) अणु
		क्रम (k = 0; k < hub_buf[j].ports; k++) अणु
			uv_hubs[j]->ports[k] = kzalloc(माप(*uv_hubs[j]->ports[k]), GFP_KERNEL);
			अगर (!uv_hubs[j]->ports[k]) अणु
				ret = -ENOMEM;
				k--;
				जाओ err_kobj_ports;
			पूर्ण
			uv_hubs[j]->ports[k]->port_info = &port_buf[j][k];
			ret = kobject_init_and_add(&uv_hubs[j]->ports[k]->kobj, &uv_port_attr_type,
					&uv_hubs[j]->kobj, "port_%d", port_buf[j][k].port);
			अगर (ret)
				जाओ err_kobj_ports;
			kobject_uevent(&uv_hubs[j]->ports[k]->kobj, KOBJ_ADD);
		पूर्ण
	पूर्ण
	वापस 0;

err_kobj_ports:
	क्रम (; j >= 0; j--) अणु
		क्रम (; k >= 0; k--)
			kobject_put(&uv_hubs[j]->ports[k]->kobj);
		अगर (j > 0)
			k = hub_buf[j-1].ports - 1;
	पूर्ण
	j = uv_bios_obj_cnt - 1;
err_ports:
	क्रम (; j >= 0; j--)
		kमुक्त(uv_hubs[j]->ports);
	j = uv_bios_obj_cnt - 1;
err_port_info:
	क्रम (; j >= 0; j--)
		kमुक्त(port_buf[j]);
	kमुक्त(port_buf);
	वापस ret;
पूर्ण

अटल व्योम uv_ports_निकास(व्योम)
अणु
	पूर्णांक j, k;

	क्रम (j = 0; j < uv_bios_obj_cnt; j++) अणु
		क्रम (k = hub_buf[j].ports - 1; k >= 0; k--)
			kobject_put(&uv_hubs[j]->ports[k]->kobj);
	पूर्ण
	क्रम (j = 0; j < uv_bios_obj_cnt; j++) अणु
		kमुक्त(uv_hubs[j]->ports);
		kमुक्त(port_buf[j]);
	पूर्ण
	kमुक्त(port_buf);
पूर्ण

काष्ठा uv_pci_top_obj अणु
	काष्ठा kobject kobj;
	अक्षर *type;
	अक्षर *location;
	पूर्णांक iio_stack;
	अक्षर *ppb_addr;
	पूर्णांक slot;
पूर्ण;

#घोषणा to_uv_pci_top_obj(kobj_ptr) container_of(kobj_ptr, काष्ठा uv_pci_top_obj, kobj)

अटल sमाप_प्रकार uv_pci_type_show(काष्ठा uv_pci_top_obj *top_obj, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", top_obj->type);
पूर्ण

अटल sमाप_प्रकार uv_pci_location_show(काष्ठा uv_pci_top_obj *top_obj, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", top_obj->location);
पूर्ण

अटल sमाप_प्रकार uv_pci_iio_stack_show(काष्ठा uv_pci_top_obj *top_obj, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", top_obj->iio_stack);
पूर्ण

अटल sमाप_प्रकार uv_pci_ppb_addr_show(काष्ठा uv_pci_top_obj *top_obj, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", top_obj->ppb_addr);
पूर्ण

अटल sमाप_प्रकार uv_pci_slot_show(काष्ठा uv_pci_top_obj *top_obj, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", top_obj->slot);
पूर्ण

काष्ठा uv_pci_top_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा uv_pci_top_obj *top_obj, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा uv_pci_top_obj *top_obj, स्थिर अक्षर *buf, माप_प्रकार size);
पूर्ण;

अटल काष्ठा uv_pci_top_sysfs_entry uv_pci_type_attribute =
	__ATTR(type, 0444, uv_pci_type_show, शून्य);
अटल काष्ठा uv_pci_top_sysfs_entry uv_pci_location_attribute =
	__ATTR(location, 0444, uv_pci_location_show, शून्य);
अटल काष्ठा uv_pci_top_sysfs_entry uv_pci_iio_stack_attribute =
	__ATTR(iio_stack, 0444, uv_pci_iio_stack_show, शून्य);
अटल काष्ठा uv_pci_top_sysfs_entry uv_pci_ppb_addr_attribute =
	__ATTR(ppb_addr, 0444, uv_pci_ppb_addr_show, शून्य);
अटल काष्ठा uv_pci_top_sysfs_entry uv_pci_slot_attribute =
	__ATTR(slot, 0444, uv_pci_slot_show, शून्य);

अटल व्योम uv_pci_top_release(काष्ठा kobject *kobj)
अणु
	काष्ठा uv_pci_top_obj *top_obj = to_uv_pci_top_obj(kobj);

	kमुक्त(top_obj->type);
	kमुक्त(top_obj->location);
	kमुक्त(top_obj->ppb_addr);
	kमुक्त(top_obj);
पूर्ण

अटल sमाप_प्रकार pci_top_type_show(काष्ठा kobject *kobj,
			काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा uv_pci_top_obj *top_obj = to_uv_pci_top_obj(kobj);
	काष्ठा uv_pci_top_sysfs_entry *entry;

	entry = container_of(attr, काष्ठा uv_pci_top_sysfs_entry, attr);

	अगर (!entry->show)
		वापस -EIO;

	वापस entry->show(top_obj, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops uv_pci_top_sysfs_ops = अणु
	.show = pci_top_type_show,
पूर्ण;

अटल काष्ठा kobj_type uv_pci_top_attr_type = अणु
	.release	= uv_pci_top_release,
	.sysfs_ops	= &uv_pci_top_sysfs_ops,
पूर्ण;

अटल पूर्णांक init_pci_top_obj(काष्ठा uv_pci_top_obj *top_obj, अक्षर *line)
अणु
	अक्षर *start;
	अक्षर type[11], location[14], ppb_addr[15];
	पूर्णांक str_cnt, ret;
	अचिन्हित पूर्णांक पंचांगp_match[2];

	// Minimum line length
	अगर (म_माप(line) < 36)
		वापस -EINVAL;

	//Line must match क्रमmat "pcibus %4x:%2x" to be valid
	str_cnt = माला_पूछो(line, "pcibus %4x:%2x", &पंचांगp_match[0], &पंचांगp_match[1]);
	अगर (str_cnt < 2)
		वापस -EINVAL;

	/* Connect pcibus to segment:bus number with '_'
	 * to concatenate name tokens.
	 * pcibus 0000:00 ... -> pcibus_0000:00 ...
	 */
	line[6] = '_';

	/* Null terminate after the concatencated name tokens
	 * to produce kobj name string.
	 */
	line[14] = '\0';

	// Use start to index after name tokens string क्रम reमुख्यder of line info.
	start = &line[15];

	top_obj->iio_stack = -1;
	top_obj->slot = -1;

	/* r001i01b00h0 BASE IO (IIO Stack 0)
	 * r001i01b00h1 PCIe IO (IIO Stack 1)
	 * r001i01b03h1 PCIe SLOT
	 * r001i01b00h0 NODE IO
	 * r001i01b00h0 Riser
	 * (IIO Stack #) may not be present.
	 */
	अगर (start[0] == 'r') अणु
		str_cnt = माला_पूछो(start, "%13s %10[^(] %*s %*s %d)",
				location, type, &top_obj->iio_stack);
		अगर (str_cnt < 2)
			वापस -EINVAL;
		top_obj->type = kstrdup(type, GFP_KERNEL);
		अगर (!top_obj->type)
			वापस -ENOMEM;
		top_obj->location = kstrdup(location, GFP_KERNEL);
		अगर (!top_obj->location) अणु
			kमुक्त(top_obj->type);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	/* PPB at 0000:80:00.00 (slot 3)
	 * (slot #) may not be present.
	 */
	अन्यथा अगर (start[0] == 'P') अणु
		str_cnt = माला_पूछो(start, "%10s %*s %14s %*s %d)",
				type, ppb_addr, &top_obj->slot);
		अगर (str_cnt < 2)
			वापस -EINVAL;
		top_obj->type = kstrdup(type, GFP_KERNEL);
		अगर (!top_obj->type)
			वापस -ENOMEM;
		top_obj->ppb_addr = kstrdup(ppb_addr, GFP_KERNEL);
		अगर (!top_obj->ppb_addr) अणु
			kमुक्त(top_obj->type);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;

	top_obj->kobj.kset = uv_pcibus_kset;

	ret = kobject_init_and_add(&top_obj->kobj, &uv_pci_top_attr_type, शून्य, "%s", line);
	अगर (ret)
		जाओ err_add_sysfs;

	अगर (top_obj->type) अणु
		ret = sysfs_create_file(&top_obj->kobj, &uv_pci_type_attribute.attr);
		अगर (ret)
			जाओ err_add_sysfs;
	पूर्ण
	अगर (top_obj->location) अणु
		ret = sysfs_create_file(&top_obj->kobj, &uv_pci_location_attribute.attr);
		अगर (ret)
			जाओ err_add_sysfs;
	पूर्ण
	अगर (top_obj->iio_stack >= 0) अणु
		ret = sysfs_create_file(&top_obj->kobj, &uv_pci_iio_stack_attribute.attr);
		अगर (ret)
			जाओ err_add_sysfs;
	पूर्ण
	अगर (top_obj->ppb_addr) अणु
		ret = sysfs_create_file(&top_obj->kobj, &uv_pci_ppb_addr_attribute.attr);
		अगर (ret)
			जाओ err_add_sysfs;
	पूर्ण
	अगर (top_obj->slot >= 0) अणु
		ret = sysfs_create_file(&top_obj->kobj, &uv_pci_slot_attribute.attr);
		अगर (ret)
			जाओ err_add_sysfs;
	पूर्ण

	kobject_uevent(&top_obj->kobj, KOBJ_ADD);
	वापस 0;

err_add_sysfs:
	kobject_put(&top_obj->kobj);
	वापस ret;
पूर्ण

अटल पूर्णांक pci_topology_init(व्योम)
अणु
	अक्षर *pci_top_str, *start, *found, *count;
	माप_प्रकार sz;
	s64 biosr;
	पूर्णांक l = 0, k = 0;
	पूर्णांक len, ret;

	uv_pcibus_kset = kset_create_and_add("pcibuses", शून्य, sgi_uv_kobj);
	अगर (!uv_pcibus_kset)
		वापस -ENOMEM;

	क्रम (sz = PAGE_SIZE; sz < 16 * PAGE_SIZE; sz += PAGE_SIZE) अणु
		pci_top_str = kदो_स्मृति(sz, GFP_KERNEL);
		अगर (!pci_top_str) अणु
			ret = -ENOMEM;
			जाओ err_pci_top_str;
		पूर्ण
		biosr = uv_bios_get_pci_topology((u64)sz, (u64 *)pci_top_str);
		अगर (biosr == BIOS_STATUS_SUCCESS) अणु
			len = strnlen(pci_top_str, sz);
			क्रम (count = pci_top_str; count < pci_top_str + len; count++) अणु
				अगर (*count == '\n')
					l++;
			पूर्ण
			num_pci_lines = l;

			uv_pci_objs = kसुस्मृति(num_pci_lines,
					     माप(*uv_pci_objs), GFP_KERNEL);
			अगर (!uv_pci_objs) अणु
				kमुक्त(pci_top_str);
				ret = -ENOMEM;
				जाओ err_pci_top_str;
			पूर्ण
			start = pci_top_str;
			जबतक ((found = strsep(&start, "\n")) != शून्य) अणु
				uv_pci_objs[k] = kzalloc(माप(*uv_pci_objs[k]), GFP_KERNEL);
				अगर (!uv_pci_objs[k]) अणु
					ret = -ENOMEM;
					जाओ err_pci_obj;
				पूर्ण
				ret = init_pci_top_obj(uv_pci_objs[k], found);
				अगर (ret)
					जाओ err_pci_obj;
				k++;
				अगर (k == num_pci_lines)
					अवरोध;
			पूर्ण
		पूर्ण
		kमुक्त(pci_top_str);
		अगर (biosr == BIOS_STATUS_SUCCESS || biosr == BIOS_STATUS_UNIMPLEMENTED)
			अवरोध;
	पूर्ण

	वापस 0;
err_pci_obj:
	k--;
	क्रम (; k >= 0; k--)
		kobject_put(&uv_pci_objs[k]->kobj);
	kमुक्त(uv_pci_objs);
	kमुक्त(pci_top_str);
err_pci_top_str:
	kset_unरेजिस्टर(uv_pcibus_kset);
	वापस ret;
पूर्ण

अटल व्योम pci_topology_निकास(व्योम)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < num_pci_lines; k++)
		kobject_put(&uv_pci_objs[k]->kobj);
	kset_unरेजिस्टर(uv_pcibus_kset);
	kमुक्त(uv_pci_objs);
पूर्ण

अटल sमाप_प्रकार partition_id_show(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%ld\n", sn_partition_id);
पूर्ण

अटल sमाप_प्रकार coherence_id_show(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%ld\n", sn_coherency_id);
पूर्ण

अटल sमाप_प्रकार uv_type_show(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", uv_type_string());
पूर्ण

अटल sमाप_प्रकार uv_archtype_show(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस uv_get_archtype(buf, PAGE_SIZE);
पूर्ण

अटल sमाप_प्रकार uv_hub_type_show(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%x\n", uv_hub_type());
पूर्ण

अटल sमाप_प्रकार uv_hubless_show(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%x\n", uv_get_hubless_प्रणाली());
पूर्ण

अटल काष्ठा kobj_attribute partition_id_attr =
	__ATTR(partition_id, 0444, partition_id_show, शून्य);
अटल काष्ठा kobj_attribute coherence_id_attr =
	__ATTR(coherence_id, 0444, coherence_id_show, शून्य);
अटल काष्ठा kobj_attribute uv_type_attr =
	__ATTR(uv_type, 0444, uv_type_show, शून्य);
अटल काष्ठा kobj_attribute uv_archtype_attr =
	__ATTR(archtype, 0444, uv_archtype_show, शून्य);
अटल काष्ठा kobj_attribute uv_hub_type_attr =
	__ATTR(hub_type, 0444, uv_hub_type_show, शून्य);
अटल काष्ठा kobj_attribute uv_hubless_attr =
	__ATTR(hubless, 0444, uv_hubless_show, शून्य);

अटल काष्ठा attribute *base_attrs[] = अणु
	&partition_id_attr.attr,
	&coherence_id_attr.attr,
	&uv_type_attr.attr,
	&uv_archtype_attr.attr,
	&uv_hub_type_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group base_attr_group = अणु
	.attrs = base_attrs
पूर्ण;

अटल पूर्णांक initial_bios_setup(व्योम)
अणु
	u64 v;
	s64 biosr;

	biosr = uv_bios_get_master_nasid((u64)माप(uv_master_nasid), (u64 *)&uv_master_nasid);
	अगर (biosr)
		वापस -EINVAL;

	biosr = uv_bios_get_heapsize((u64)uv_master_nasid, (u64)माप(u64), &v);
	अगर (biosr)
		वापस -EINVAL;

	uv_biosheap = vदो_स्मृति(v);
	अगर (!uv_biosheap)
		वापस -ENOMEM;

	biosr = uv_bios_install_heap((u64)uv_master_nasid, v, (u64 *)uv_biosheap);
	अगर (biosr) अणु
		vमुक्त(uv_biosheap);
		वापस -EINVAL;
	पूर्ण

	biosr = uv_bios_obj_count((u64)uv_master_nasid, माप(u64), &v);
	अगर (biosr) अणु
		vमुक्त(uv_biosheap);
		वापस -EINVAL;
	पूर्ण
	uv_bios_obj_cnt = (पूर्णांक)v;

	वापस 0;
पूर्ण

अटल काष्ठा attribute *hubless_base_attrs[] = अणु
	&partition_id_attr.attr,
	&uv_type_attr.attr,
	&uv_archtype_attr.attr,
	&uv_hubless_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group hubless_base_attr_group = अणु
	.attrs = hubless_base_attrs
पूर्ण;


अटल पूर्णांक __init uv_sysfs_hubless_init(व्योम)
अणु
	पूर्णांक ret;

	ret = sysfs_create_group(sgi_uv_kobj, &hubless_base_attr_group);
	अगर (ret) अणु
		pr_warn("sysfs_create_group hubless_base_attr_group failed\n");
		kobject_put(sgi_uv_kobj);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __init uv_sysfs_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (!is_uv_प्रणाली() && !uv_get_hubless_प्रणाली())
		वापस -ENODEV;

	num_cnodes = uv_num_possible_blades();

	अगर (!sgi_uv_kobj)
		sgi_uv_kobj = kobject_create_and_add("sgi_uv", firmware_kobj);
	अगर (!sgi_uv_kobj) अणु
		pr_warn("kobject_create_and_add sgi_uv failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (uv_get_hubless_प्रणाली())
		वापस uv_sysfs_hubless_init();

	ret = sysfs_create_group(sgi_uv_kobj, &base_attr_group);
	अगर (ret) अणु
		pr_warn("sysfs_create_group base_attr_group failed\n");
		जाओ err_create_group;
	पूर्ण

	ret = initial_bios_setup();
	अगर (ret)
		जाओ err_bios_setup;

	ret = uv_hubs_init();
	अगर (ret)
		जाओ err_hubs_init;

	ret = uv_ports_init();
	अगर (ret)
		जाओ err_ports_init;

	ret = pci_topology_init();
	अगर (ret)
		जाओ err_pci_init;

	वापस 0;

err_pci_init:
	uv_ports_निकास();
err_ports_init:
	uv_hubs_निकास();
err_hubs_init:
	vमुक्त(uv_biosheap);
err_bios_setup:
	sysfs_हटाओ_group(sgi_uv_kobj, &base_attr_group);
err_create_group:
	kobject_put(sgi_uv_kobj);
	वापस ret;
पूर्ण

अटल व्योम __निकास uv_sysfs_hubless_निकास(व्योम)
अणु
	sysfs_हटाओ_group(sgi_uv_kobj, &hubless_base_attr_group);
	kobject_put(sgi_uv_kobj);
पूर्ण

अटल व्योम __निकास uv_sysfs_निकास(व्योम)
अणु
	अगर (!is_uv_प्रणाली()) अणु
		अगर (uv_get_hubless_प्रणाली())
			uv_sysfs_hubless_निकास();
		वापस;
	पूर्ण

	pci_topology_निकास();
	uv_ports_निकास();
	uv_hubs_निकास();
	vमुक्त(uv_biosheap);
	sysfs_हटाओ_group(sgi_uv_kobj, &base_attr_group);
	kobject_put(sgi_uv_kobj);
पूर्ण

#अगर_अघोषित MODULE
device_initcall(uv_sysfs_init);
#अन्यथा
module_init(uv_sysfs_init);
#पूर्ण_अगर
module_निकास(uv_sysfs_निकास);

MODULE_AUTHOR("Hewlett Packard Enterprise");
MODULE_LICENSE("GPL");
