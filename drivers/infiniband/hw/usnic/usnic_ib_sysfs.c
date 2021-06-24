<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_addr.h>

#समावेश "usnic_common_util.h"
#समावेश "usnic_ib.h"
#समावेश "usnic_ib_qp_grp.h"
#समावेश "usnic_vnic.h"
#समावेश "usnic_ib_verbs.h"
#समावेश "usnic_ib_sysfs.h"
#समावेश "usnic_log.h"

अटल sमाप_प्रकार board_id_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usnic_ib_dev *us_ibdev =
		rdma_device_to_drv_device(device, काष्ठा usnic_ib_dev, ib_dev);
	अचिन्हित लघु subप्रणाली_device_id;

	mutex_lock(&us_ibdev->usdev_lock);
	subप्रणाली_device_id = us_ibdev->pdev->subप्रणाली_device;
	mutex_unlock(&us_ibdev->usdev_lock);

	वापस sysfs_emit(buf, "%u\n", subप्रणाली_device_id);
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

/*
 * Report the configuration क्रम this PF
 */
अटल sमाप_प्रकार
config_show(काष्ठा device *device, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usnic_ib_dev *us_ibdev =
		rdma_device_to_drv_device(device, काष्ठा usnic_ib_dev, ib_dev);
	क्रमागत usnic_vnic_res_type res_type;
	पूर्णांक len;

	mutex_lock(&us_ibdev->usdev_lock);
	अगर (kref_पढ़ो(&us_ibdev->vf_cnt) > 0) अणु
		अक्षर *busname;
		अक्षर *sep = "";
		/*
		 * bus name seems to come with annoying prefix.
		 * Remove it अगर it is predictable
		 */
		busname = us_ibdev->pdev->bus->name;
		अगर (म_भेदन(busname, "PCI Bus ", 8) == 0)
			busname += 8;

		len = sysfs_emit(buf, "%s: %s:%d.%d, %s, %pM, %u VFs\n",
				 dev_name(&us_ibdev->ib_dev.dev),
				 busname,
				 PCI_SLOT(us_ibdev->pdev->devfn),
				 PCI_FUNC(us_ibdev->pdev->devfn),
				 netdev_name(us_ibdev->netdev),
				 us_ibdev->ufdev->mac,
				 kref_पढ़ो(&us_ibdev->vf_cnt));

		len += sysfs_emit_at(buf, len, " Per VF:");
		क्रम (res_type = USNIC_VNIC_RES_TYPE_EOL;
		     res_type < USNIC_VNIC_RES_TYPE_MAX; res_type++) अणु
			अगर (us_ibdev->vf_res_cnt[res_type] == 0)
				जारी;
			len += sysfs_emit_at(buf, len, "%s %d %s",
					     sep,
					     us_ibdev->vf_res_cnt[res_type],
					     usnic_vnic_res_type_to_str(res_type));
			sep = ",";
		पूर्ण
		len += sysfs_emit_at(buf, len, "\n");
	पूर्ण अन्यथा अणु
		len = sysfs_emit(buf, "%s: no VFs\n",
				 dev_name(&us_ibdev->ib_dev.dev));
	पूर्ण

	mutex_unlock(&us_ibdev->usdev_lock);

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(config);

अटल sमाप_प्रकार
अगरace_show(काष्ठा device *device, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usnic_ib_dev *us_ibdev =
		rdma_device_to_drv_device(device, काष्ठा usnic_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%s\n", netdev_name(us_ibdev->netdev));
पूर्ण
अटल DEVICE_ATTR_RO(अगरace);

अटल sमाप_प्रकार
max_vf_show(काष्ठा device *device, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usnic_ib_dev *us_ibdev =
		rdma_device_to_drv_device(device, काष्ठा usnic_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%u\n", kref_पढ़ो(&us_ibdev->vf_cnt));
पूर्ण
अटल DEVICE_ATTR_RO(max_vf);

अटल sमाप_प्रकार
qp_per_vf_show(काष्ठा device *device, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usnic_ib_dev *us_ibdev =
		rdma_device_to_drv_device(device, काष्ठा usnic_ib_dev, ib_dev);
	पूर्णांक qp_per_vf;

	qp_per_vf = max(us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_WQ],
			us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_RQ]);

	वापस sysfs_emit(buf, "%d\n", qp_per_vf);
पूर्ण
अटल DEVICE_ATTR_RO(qp_per_vf);

अटल sमाप_प्रकार
cq_per_vf_show(काष्ठा device *device, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usnic_ib_dev *us_ibdev =
		rdma_device_to_drv_device(device, काष्ठा usnic_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%d\n",
			  us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_CQ]);
पूर्ण
अटल DEVICE_ATTR_RO(cq_per_vf);

अटल काष्ठा attribute *usnic_class_attributes[] = अणु
	&dev_attr_board_id.attr,
	&dev_attr_config.attr,
	&dev_attr_अगरace.attr,
	&dev_attr_max_vf.attr,
	&dev_attr_qp_per_vf.attr,
	&dev_attr_cq_per_vf.attr,
	शून्य
पूर्ण;

स्थिर काष्ठा attribute_group usnic_attr_group = अणु
	.attrs = usnic_class_attributes,
पूर्ण;

काष्ठा qpn_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा usnic_ib_qp_grp *, अक्षर *buf);
पूर्ण;

/*
 * Definitions क्रम supporting QPN entries in sysfs
 */
अटल sमाप_प्रकार
usnic_ib_qpn_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा usnic_ib_qp_grp *qp_grp;
	काष्ठा qpn_attribute *qpn_attr;

	qp_grp = container_of(kobj, काष्ठा usnic_ib_qp_grp, kobj);
	qpn_attr = container_of(attr, काष्ठा qpn_attribute, attr);

	वापस qpn_attr->show(qp_grp, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops usnic_ib_qpn_sysfs_ops = अणु
	.show = usnic_ib_qpn_attr_show
पूर्ण;

#घोषणा QPN_ATTR_RO(NAME) \
काष्ठा qpn_attribute qpn_attr_##NAME = __ATTR_RO(NAME)

अटल sमाप_प्रकार context_show(काष्ठा usnic_ib_qp_grp *qp_grp, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "0x%p\n", qp_grp->ctx);
पूर्ण

अटल sमाप_प्रकार summary_show(काष्ठा usnic_ib_qp_grp *qp_grp, अक्षर *buf)
अणु
	पूर्णांक i, j;
	काष्ठा usnic_vnic_res_chunk *res_chunk;
	काष्ठा usnic_vnic_res *vnic_res;
	पूर्णांक len;

	len = sysfs_emit(buf, "QPN: %d State: (%s) PID: %u VF Idx: %hu",
			 qp_grp->ibqp.qp_num,
			 usnic_ib_qp_grp_state_to_string(qp_grp->state),
			 qp_grp->owner_pid,
			 usnic_vnic_get_index(qp_grp->vf->vnic));

	क्रम (i = 0; qp_grp->res_chunk_list[i]; i++) अणु
		res_chunk = qp_grp->res_chunk_list[i];
		क्रम (j = 0; j < res_chunk->cnt; j++) अणु
			vnic_res = res_chunk->res[j];
			len += sysfs_emit_at(buf, len, " %s[%d]",
				usnic_vnic_res_type_to_str(vnic_res->type),
				vnic_res->vnic_idx);
		पूर्ण
	पूर्ण

	len += sysfs_emit_at(buf, len, "\n");

	वापस len;
पूर्ण

अटल QPN_ATTR_RO(context);
अटल QPN_ATTR_RO(summary);

अटल काष्ठा attribute *usnic_ib_qpn_शेष_attrs[] = अणु
	&qpn_attr_context.attr,
	&qpn_attr_summary.attr,
	शून्य
पूर्ण;

अटल काष्ठा kobj_type usnic_ib_qpn_type = अणु
	.sysfs_ops = &usnic_ib_qpn_sysfs_ops,
	.शेष_attrs = usnic_ib_qpn_शेष_attrs
पूर्ण;

पूर्णांक usnic_ib_sysfs_रेजिस्टर_usdev(काष्ठा usnic_ib_dev *us_ibdev)
अणु
	/* create kernel object क्रम looking at inभागidual QPs */
	kobject_get(&us_ibdev->ib_dev.dev.kobj);
	us_ibdev->qpn_kobj = kobject_create_and_add("qpn",
			&us_ibdev->ib_dev.dev.kobj);
	अगर (us_ibdev->qpn_kobj == शून्य) अणु
		kobject_put(&us_ibdev->ib_dev.dev.kobj);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम usnic_ib_sysfs_unरेजिस्टर_usdev(काष्ठा usnic_ib_dev *us_ibdev)
अणु
	kobject_put(us_ibdev->qpn_kobj);
पूर्ण

व्योम usnic_ib_sysfs_qpn_add(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	काष्ठा usnic_ib_dev *us_ibdev;
	पूर्णांक err;

	us_ibdev = qp_grp->vf->pf;

	err = kobject_init_and_add(&qp_grp->kobj, &usnic_ib_qpn_type,
			kobject_get(us_ibdev->qpn_kobj),
			"%d", qp_grp->grp_id);
	अगर (err) अणु
		kobject_put(us_ibdev->qpn_kobj);
		वापस;
	पूर्ण
पूर्ण

व्योम usnic_ib_sysfs_qpn_हटाओ(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	काष्ठा usnic_ib_dev *us_ibdev;

	us_ibdev = qp_grp->vf->pf;

	kobject_put(&qp_grp->kobj);
	kobject_put(us_ibdev->qpn_kobj);
पूर्ण
