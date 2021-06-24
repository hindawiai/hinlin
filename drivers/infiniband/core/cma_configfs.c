<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies inc.  All rights reserved.
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
#समावेश <linux/configfs.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>

#समावेश "core_priv.h"
#समावेश "cma_priv.h"

काष्ठा cma_device;

काष्ठा cma_dev_group;

काष्ठा cma_dev_port_group अणु
	u32			port_num;
	काष्ठा cma_dev_group	*cma_dev_group;
	काष्ठा config_group	group;
पूर्ण;

काष्ठा cma_dev_group अणु
	अक्षर				name[IB_DEVICE_NAME_MAX];
	काष्ठा config_group		device_group;
	काष्ठा config_group		ports_group;
	काष्ठा cma_dev_port_group	*ports;
पूर्ण;

अटल काष्ठा cma_dev_port_group *to_dev_port_group(काष्ठा config_item *item)
अणु
	काष्ठा config_group *group;

	अगर (!item)
		वापस शून्य;

	group = container_of(item, काष्ठा config_group, cg_item);
	वापस container_of(group, काष्ठा cma_dev_port_group, group);
पूर्ण

अटल bool filter_by_name(काष्ठा ib_device *ib_dev, व्योम *cookie)
अणु
	वापस !म_भेद(dev_name(&ib_dev->dev), cookie);
पूर्ण

अटल पूर्णांक cma_configfs_params_get(काष्ठा config_item *item,
				   काष्ठा cma_device **pcma_dev,
				   काष्ठा cma_dev_port_group **pgroup)
अणु
	काष्ठा cma_dev_port_group *group = to_dev_port_group(item);
	काष्ठा cma_device *cma_dev;

	अगर (!group)
		वापस -ENODEV;

	cma_dev = cma_क्रमागत_devices_by_ibdev(filter_by_name,
					    group->cma_dev_group->name);
	अगर (!cma_dev)
		वापस -ENODEV;

	*pcma_dev = cma_dev;
	*pgroup = group;

	वापस 0;
पूर्ण

अटल व्योम cma_configfs_params_put(काष्ठा cma_device *cma_dev)
अणु
	cma_dev_put(cma_dev);
पूर्ण

अटल sमाप_प्रकार शेष_roce_mode_show(काष्ठा config_item *item,
				      अक्षर *buf)
अणु
	काष्ठा cma_device *cma_dev;
	काष्ठा cma_dev_port_group *group;
	पूर्णांक gid_type;
	sमाप_प्रकार ret;

	ret = cma_configfs_params_get(item, &cma_dev, &group);
	अगर (ret)
		वापस ret;

	gid_type = cma_get_शेष_gid_type(cma_dev, group->port_num);
	cma_configfs_params_put(cma_dev);

	अगर (gid_type < 0)
		वापस gid_type;

	वापस sysfs_emit(buf, "%s\n", ib_cache_gid_type_str(gid_type));
पूर्ण

अटल sमाप_प्रकार शेष_roce_mode_store(काष्ठा config_item *item,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cma_device *cma_dev;
	काष्ठा cma_dev_port_group *group;
	पूर्णांक gid_type;
	sमाप_प्रकार ret;

	ret = cma_configfs_params_get(item, &cma_dev, &group);
	अगर (ret)
		वापस ret;

	gid_type = ib_cache_gid_parse_type_str(buf);
	अगर (gid_type < 0) अणु
		cma_configfs_params_put(cma_dev);
		वापस -EINVAL;
	पूर्ण

	ret = cma_set_शेष_gid_type(cma_dev, group->port_num, gid_type);

	cma_configfs_params_put(cma_dev);

	वापस !ret ? strnlen(buf, count) : ret;
पूर्ण

CONFIGFS_ATTR(, शेष_roce_mode);

अटल sमाप_प्रकार शेष_roce_tos_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	काष्ठा cma_device *cma_dev;
	काष्ठा cma_dev_port_group *group;
	sमाप_प्रकार ret;
	u8 tos;

	ret = cma_configfs_params_get(item, &cma_dev, &group);
	अगर (ret)
		वापस ret;

	tos = cma_get_शेष_roce_tos(cma_dev, group->port_num);
	cma_configfs_params_put(cma_dev);

	वापस sysfs_emit(buf, "%u\n", tos);
पूर्ण

अटल sमाप_प्रकार शेष_roce_tos_store(काष्ठा config_item *item,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cma_device *cma_dev;
	काष्ठा cma_dev_port_group *group;
	sमाप_प्रकार ret;
	u8 tos;

	ret = kstrtou8(buf, 0, &tos);
	अगर (ret)
		वापस ret;

	ret = cma_configfs_params_get(item, &cma_dev, &group);
	अगर (ret)
		वापस ret;

	ret = cma_set_शेष_roce_tos(cma_dev, group->port_num, tos);
	cma_configfs_params_put(cma_dev);

	वापस ret ? ret : strnlen(buf, count);
पूर्ण

CONFIGFS_ATTR(, शेष_roce_tos);

अटल काष्ठा configfs_attribute *cma_configfs_attributes[] = अणु
	&attr_शेष_roce_mode,
	&attr_शेष_roce_tos,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type cma_port_group_type = अणु
	.ct_attrs	= cma_configfs_attributes,
	.ct_owner	= THIS_MODULE
पूर्ण;

अटल पूर्णांक make_cma_ports(काष्ठा cma_dev_group *cma_dev_group,
			  काष्ठा cma_device *cma_dev)
अणु
	काष्ठा cma_dev_port_group *ports;
	काष्ठा ib_device *ibdev;
	u32 ports_num;
	u32 i;

	ibdev = cma_get_ib_dev(cma_dev);

	अगर (!ibdev)
		वापस -ENODEV;

	ports_num = ibdev->phys_port_cnt;
	ports = kसुस्मृति(ports_num, माप(*cma_dev_group->ports),
			GFP_KERNEL);

	अगर (!ports)
		वापस -ENOMEM;

	क्रम (i = 0; i < ports_num; i++) अणु
		अक्षर port_str[10];

		ports[i].port_num = i + 1;
		snम_लिखो(port_str, माप(port_str), "%u", i + 1);
		ports[i].cma_dev_group = cma_dev_group;
		config_group_init_type_name(&ports[i].group,
					    port_str,
					    &cma_port_group_type);
		configfs_add_शेष_group(&ports[i].group,
				&cma_dev_group->ports_group);

	पूर्ण
	cma_dev_group->ports = ports;
	वापस 0;
पूर्ण

अटल व्योम release_cma_dev(काष्ठा config_item  *item)
अणु
	काष्ठा config_group *group = container_of(item, काष्ठा config_group,
						  cg_item);
	काष्ठा cma_dev_group *cma_dev_group = container_of(group,
							   काष्ठा cma_dev_group,
							   device_group);

	kमुक्त(cma_dev_group);
पूर्ण;

अटल व्योम release_cma_ports_group(काष्ठा config_item  *item)
अणु
	काष्ठा config_group *group = container_of(item, काष्ठा config_group,
						  cg_item);
	काष्ठा cma_dev_group *cma_dev_group = container_of(group,
							   काष्ठा cma_dev_group,
							   ports_group);

	kमुक्त(cma_dev_group->ports);
	cma_dev_group->ports = शून्य;
पूर्ण;

अटल काष्ठा configfs_item_operations cma_ports_item_ops = अणु
	.release = release_cma_ports_group
पूर्ण;

अटल स्थिर काष्ठा config_item_type cma_ports_group_type = अणु
	.ct_item_ops	= &cma_ports_item_ops,
	.ct_owner	= THIS_MODULE
पूर्ण;

अटल काष्ठा configfs_item_operations cma_device_item_ops = अणु
	.release = release_cma_dev
पूर्ण;

अटल स्थिर काष्ठा config_item_type cma_device_group_type = अणु
	.ct_item_ops	= &cma_device_item_ops,
	.ct_owner	= THIS_MODULE
पूर्ण;

अटल काष्ठा config_group *make_cma_dev(काष्ठा config_group *group,
					 स्थिर अक्षर *name)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा cma_device *cma_dev = cma_क्रमागत_devices_by_ibdev(filter_by_name,
							       (व्योम *)name);
	काष्ठा cma_dev_group *cma_dev_group = शून्य;

	अगर (!cma_dev)
		जाओ fail;

	cma_dev_group = kzalloc(माप(*cma_dev_group), GFP_KERNEL);

	अगर (!cma_dev_group) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	strlcpy(cma_dev_group->name, name, माप(cma_dev_group->name));

	config_group_init_type_name(&cma_dev_group->ports_group, "ports",
				    &cma_ports_group_type);

	err = make_cma_ports(cma_dev_group, cma_dev);
	अगर (err)
		जाओ fail;

	config_group_init_type_name(&cma_dev_group->device_group, name,
				    &cma_device_group_type);
	configfs_add_शेष_group(&cma_dev_group->ports_group,
			&cma_dev_group->device_group);

	cma_dev_put(cma_dev);
	वापस &cma_dev_group->device_group;

fail:
	अगर (cma_dev)
		cma_dev_put(cma_dev);
	kमुक्त(cma_dev_group);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम drop_cma_dev(काष्ठा config_group *cgroup, काष्ठा config_item *item)
अणु
	काष्ठा config_group *group =
		container_of(item, काष्ठा config_group, cg_item);
	काष्ठा cma_dev_group *cma_dev_group =
		container_of(group, काष्ठा cma_dev_group, device_group);

	configfs_हटाओ_शेष_groups(&cma_dev_group->ports_group);
	configfs_हटाओ_शेष_groups(&cma_dev_group->device_group);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations cma_subsys_group_ops = अणु
	.make_group	= make_cma_dev,
	.drop_item	= drop_cma_dev,
पूर्ण;

अटल स्थिर काष्ठा config_item_type cma_subsys_type = अणु
	.ct_group_ops	= &cma_subsys_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली cma_subsys = अणु
	.su_group	= अणु
		.cg_item	= अणु
			.ci_namebuf	= "rdma_cm",
			.ci_type	= &cma_subsys_type,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक __init cma_configfs_init(व्योम)
अणु
	पूर्णांक ret;

	config_group_init(&cma_subsys.su_group);
	mutex_init(&cma_subsys.su_mutex);
	ret = configfs_रेजिस्टर_subप्रणाली(&cma_subsys);
	अगर (ret)
		mutex_destroy(&cma_subsys.su_mutex);
	वापस ret;
पूर्ण

व्योम __निकास cma_configfs_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_subप्रणाली(&cma_subsys);
	mutex_destroy(&cma_subsys.su_mutex);
पूर्ण
