<शैली गुरु>
/*
 * Copyright(c) 2015-2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <linux/प्रकार.स>

#समावेश "hfi.h"
#समावेश "mad.h"
#समावेश "trace.h"

/*
 * Start of per-port congestion control काष्ठाures and support code
 */

/*
 * Congestion control table size followed by table entries
 */
अटल sमाप_प्रकार पढ़ो_cc_table_bin(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr,
				 अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा hfi1_pportdata *ppd =
		container_of(kobj, काष्ठा hfi1_pportdata, pport_cc_kobj);
	काष्ठा cc_state *cc_state;

	ret = ppd->total_cct_entry * माप(काष्ठा ib_cc_table_entry_shaकरोw)
		 + माप(__be16);

	अगर (pos > ret)
		वापस -EINVAL;

	अगर (count > ret - pos)
		count = ret - pos;

	अगर (!count)
		वापस count;

	rcu_पढ़ो_lock();
	cc_state = get_cc_state(ppd);
	अगर (!cc_state) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	स_नकल(buf, (व्योम *)&cc_state->cct + pos, count);
	rcu_पढ़ो_unlock();

	वापस count;
पूर्ण

अटल व्योम port_release(काष्ठा kobject *kobj)
अणु
	/* nothing to करो since memory is मुक्तd by hfi1_मुक्त_devdata() */
पूर्ण

अटल स्थिर काष्ठा bin_attribute cc_table_bin_attr = अणु
	.attr = अणु.name = "cc_table_bin", .mode = 0444पूर्ण,
	.पढ़ो = पढ़ो_cc_table_bin,
	.size = PAGE_SIZE,
पूर्ण;

/*
 * Congestion settings: port control, control map and an array of 16
 * entries क्रम the congestion entries - increase, समयr, event log
 * trigger threshold and the minimum injection rate delay.
 */
अटल sमाप_प्रकार पढ़ो_cc_setting_bin(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *bin_attr,
				   अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा hfi1_pportdata *ppd =
		container_of(kobj, काष्ठा hfi1_pportdata, pport_cc_kobj);
	काष्ठा cc_state *cc_state;

	ret = माप(काष्ठा opa_congestion_setting_attr_shaकरोw);

	अगर (pos > ret)
		वापस -EINVAL;
	अगर (count > ret - pos)
		count = ret - pos;

	अगर (!count)
		वापस count;

	rcu_पढ़ो_lock();
	cc_state = get_cc_state(ppd);
	अगर (!cc_state) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	स_नकल(buf, (व्योम *)&cc_state->cong_setting + pos, count);
	rcu_पढ़ो_unlock();

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute cc_setting_bin_attr = अणु
	.attr = अणु.name = "cc_settings_bin", .mode = 0444पूर्ण,
	.पढ़ो = पढ़ो_cc_setting_bin,
	.size = PAGE_SIZE,
पूर्ण;

काष्ठा hfi1_port_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार	(*show)(काष्ठा hfi1_pportdata *, अक्षर *);
	sमाप_प्रकार	(*store)(काष्ठा hfi1_pportdata *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार cc_prescan_show(काष्ठा hfi1_pportdata *ppd, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n", ppd->cc_prescan ? "on" : "off");
पूर्ण

अटल sमाप_प्रकार cc_prescan_store(काष्ठा hfi1_pportdata *ppd, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	अगर (!स_भेद(buf, "on", 2))
		ppd->cc_prescan = true;
	अन्यथा अगर (!स_भेद(buf, "off", 3))
		ppd->cc_prescan = false;

	वापस count;
पूर्ण

अटल काष्ठा hfi1_port_attr cc_prescan_attr =
		__ATTR(cc_prescan, 0600, cc_prescan_show, cc_prescan_store);

अटल sमाप_प्रकार cc_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा hfi1_port_attr *port_attr =
		container_of(attr, काष्ठा hfi1_port_attr, attr);
	काष्ठा hfi1_pportdata *ppd =
		container_of(kobj, काष्ठा hfi1_pportdata, pport_cc_kobj);

	वापस port_attr->show(ppd, buf);
पूर्ण

अटल sमाप_प्रकार cc_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hfi1_port_attr *port_attr =
		container_of(attr, काष्ठा hfi1_port_attr, attr);
	काष्ठा hfi1_pportdata *ppd =
		container_of(kobj, काष्ठा hfi1_pportdata, pport_cc_kobj);

	वापस port_attr->store(ppd, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops port_cc_sysfs_ops = अणु
	.show = cc_attr_show,
	.store = cc_attr_store
पूर्ण;

अटल काष्ठा attribute *port_cc_शेष_attributes[] = अणु
	&cc_prescan_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा kobj_type port_cc_ktype = अणु
	.release = port_release,
	.sysfs_ops = &port_cc_sysfs_ops,
	.शेष_attrs = port_cc_शेष_attributes
पूर्ण;

/* Start sc2vl */
#घोषणा HFI1_SC2VL_ATTR(N)				    \
	अटल काष्ठा hfi1_sc2vl_attr hfi1_sc2vl_attr_##N = अणु \
		.attr = अणु .name = __stringअगरy(N), .mode = 0444 पूर्ण, \
		.sc = N \
	पूर्ण

काष्ठा hfi1_sc2vl_attr अणु
	काष्ठा attribute attr;
	पूर्णांक sc;
पूर्ण;

HFI1_SC2VL_ATTR(0);
HFI1_SC2VL_ATTR(1);
HFI1_SC2VL_ATTR(2);
HFI1_SC2VL_ATTR(3);
HFI1_SC2VL_ATTR(4);
HFI1_SC2VL_ATTR(5);
HFI1_SC2VL_ATTR(6);
HFI1_SC2VL_ATTR(7);
HFI1_SC2VL_ATTR(8);
HFI1_SC2VL_ATTR(9);
HFI1_SC2VL_ATTR(10);
HFI1_SC2VL_ATTR(11);
HFI1_SC2VL_ATTR(12);
HFI1_SC2VL_ATTR(13);
HFI1_SC2VL_ATTR(14);
HFI1_SC2VL_ATTR(15);
HFI1_SC2VL_ATTR(16);
HFI1_SC2VL_ATTR(17);
HFI1_SC2VL_ATTR(18);
HFI1_SC2VL_ATTR(19);
HFI1_SC2VL_ATTR(20);
HFI1_SC2VL_ATTR(21);
HFI1_SC2VL_ATTR(22);
HFI1_SC2VL_ATTR(23);
HFI1_SC2VL_ATTR(24);
HFI1_SC2VL_ATTR(25);
HFI1_SC2VL_ATTR(26);
HFI1_SC2VL_ATTR(27);
HFI1_SC2VL_ATTR(28);
HFI1_SC2VL_ATTR(29);
HFI1_SC2VL_ATTR(30);
HFI1_SC2VL_ATTR(31);

अटल काष्ठा attribute *sc2vl_शेष_attributes[] = अणु
	&hfi1_sc2vl_attr_0.attr,
	&hfi1_sc2vl_attr_1.attr,
	&hfi1_sc2vl_attr_2.attr,
	&hfi1_sc2vl_attr_3.attr,
	&hfi1_sc2vl_attr_4.attr,
	&hfi1_sc2vl_attr_5.attr,
	&hfi1_sc2vl_attr_6.attr,
	&hfi1_sc2vl_attr_7.attr,
	&hfi1_sc2vl_attr_8.attr,
	&hfi1_sc2vl_attr_9.attr,
	&hfi1_sc2vl_attr_10.attr,
	&hfi1_sc2vl_attr_11.attr,
	&hfi1_sc2vl_attr_12.attr,
	&hfi1_sc2vl_attr_13.attr,
	&hfi1_sc2vl_attr_14.attr,
	&hfi1_sc2vl_attr_15.attr,
	&hfi1_sc2vl_attr_16.attr,
	&hfi1_sc2vl_attr_17.attr,
	&hfi1_sc2vl_attr_18.attr,
	&hfi1_sc2vl_attr_19.attr,
	&hfi1_sc2vl_attr_20.attr,
	&hfi1_sc2vl_attr_21.attr,
	&hfi1_sc2vl_attr_22.attr,
	&hfi1_sc2vl_attr_23.attr,
	&hfi1_sc2vl_attr_24.attr,
	&hfi1_sc2vl_attr_25.attr,
	&hfi1_sc2vl_attr_26.attr,
	&hfi1_sc2vl_attr_27.attr,
	&hfi1_sc2vl_attr_28.attr,
	&hfi1_sc2vl_attr_29.attr,
	&hfi1_sc2vl_attr_30.attr,
	&hfi1_sc2vl_attr_31.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार sc2vl_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा hfi1_sc2vl_attr *sattr =
		container_of(attr, काष्ठा hfi1_sc2vl_attr, attr);
	काष्ठा hfi1_pportdata *ppd =
		container_of(kobj, काष्ठा hfi1_pportdata, sc2vl_kobj);
	काष्ठा hfi1_devdata *dd = ppd->dd;

	वापस sysfs_emit(buf, "%u\n", *((u8 *)dd->sc2vl + sattr->sc));
पूर्ण

अटल स्थिर काष्ठा sysfs_ops hfi1_sc2vl_ops = अणु
	.show = sc2vl_attr_show,
पूर्ण;

अटल काष्ठा kobj_type hfi1_sc2vl_ktype = अणु
	.release = port_release,
	.sysfs_ops = &hfi1_sc2vl_ops,
	.शेष_attrs = sc2vl_शेष_attributes
पूर्ण;

/* End sc2vl */

/* Start sl2sc */
#घोषणा HFI1_SL2SC_ATTR(N)				    \
	अटल काष्ठा hfi1_sl2sc_attr hfi1_sl2sc_attr_##N = अणु	  \
		.attr = अणु .name = __stringअगरy(N), .mode = 0444 पूर्ण, \
		.sl = N						  \
	पूर्ण

काष्ठा hfi1_sl2sc_attr अणु
	काष्ठा attribute attr;
	पूर्णांक sl;
पूर्ण;

HFI1_SL2SC_ATTR(0);
HFI1_SL2SC_ATTR(1);
HFI1_SL2SC_ATTR(2);
HFI1_SL2SC_ATTR(3);
HFI1_SL2SC_ATTR(4);
HFI1_SL2SC_ATTR(5);
HFI1_SL2SC_ATTR(6);
HFI1_SL2SC_ATTR(7);
HFI1_SL2SC_ATTR(8);
HFI1_SL2SC_ATTR(9);
HFI1_SL2SC_ATTR(10);
HFI1_SL2SC_ATTR(11);
HFI1_SL2SC_ATTR(12);
HFI1_SL2SC_ATTR(13);
HFI1_SL2SC_ATTR(14);
HFI1_SL2SC_ATTR(15);
HFI1_SL2SC_ATTR(16);
HFI1_SL2SC_ATTR(17);
HFI1_SL2SC_ATTR(18);
HFI1_SL2SC_ATTR(19);
HFI1_SL2SC_ATTR(20);
HFI1_SL2SC_ATTR(21);
HFI1_SL2SC_ATTR(22);
HFI1_SL2SC_ATTR(23);
HFI1_SL2SC_ATTR(24);
HFI1_SL2SC_ATTR(25);
HFI1_SL2SC_ATTR(26);
HFI1_SL2SC_ATTR(27);
HFI1_SL2SC_ATTR(28);
HFI1_SL2SC_ATTR(29);
HFI1_SL2SC_ATTR(30);
HFI1_SL2SC_ATTR(31);

अटल काष्ठा attribute *sl2sc_शेष_attributes[] = अणु
	&hfi1_sl2sc_attr_0.attr,
	&hfi1_sl2sc_attr_1.attr,
	&hfi1_sl2sc_attr_2.attr,
	&hfi1_sl2sc_attr_3.attr,
	&hfi1_sl2sc_attr_4.attr,
	&hfi1_sl2sc_attr_5.attr,
	&hfi1_sl2sc_attr_6.attr,
	&hfi1_sl2sc_attr_7.attr,
	&hfi1_sl2sc_attr_8.attr,
	&hfi1_sl2sc_attr_9.attr,
	&hfi1_sl2sc_attr_10.attr,
	&hfi1_sl2sc_attr_11.attr,
	&hfi1_sl2sc_attr_12.attr,
	&hfi1_sl2sc_attr_13.attr,
	&hfi1_sl2sc_attr_14.attr,
	&hfi1_sl2sc_attr_15.attr,
	&hfi1_sl2sc_attr_16.attr,
	&hfi1_sl2sc_attr_17.attr,
	&hfi1_sl2sc_attr_18.attr,
	&hfi1_sl2sc_attr_19.attr,
	&hfi1_sl2sc_attr_20.attr,
	&hfi1_sl2sc_attr_21.attr,
	&hfi1_sl2sc_attr_22.attr,
	&hfi1_sl2sc_attr_23.attr,
	&hfi1_sl2sc_attr_24.attr,
	&hfi1_sl2sc_attr_25.attr,
	&hfi1_sl2sc_attr_26.attr,
	&hfi1_sl2sc_attr_27.attr,
	&hfi1_sl2sc_attr_28.attr,
	&hfi1_sl2sc_attr_29.attr,
	&hfi1_sl2sc_attr_30.attr,
	&hfi1_sl2sc_attr_31.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार sl2sc_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा hfi1_sl2sc_attr *sattr =
		container_of(attr, काष्ठा hfi1_sl2sc_attr, attr);
	काष्ठा hfi1_pportdata *ppd =
		container_of(kobj, काष्ठा hfi1_pportdata, sl2sc_kobj);
	काष्ठा hfi1_ibport *ibp = &ppd->ibport_data;

	वापस sysfs_emit(buf, "%u\n", ibp->sl_to_sc[sattr->sl]);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops hfi1_sl2sc_ops = अणु
	.show = sl2sc_attr_show,
पूर्ण;

अटल काष्ठा kobj_type hfi1_sl2sc_ktype = अणु
	.release = port_release,
	.sysfs_ops = &hfi1_sl2sc_ops,
	.शेष_attrs = sl2sc_शेष_attributes
पूर्ण;

/* End sl2sc */

/* Start vl2mtu */

#घोषणा HFI1_VL2MTU_ATTR(N) \
	अटल काष्ठा hfi1_vl2mtu_attr hfi1_vl2mtu_attr_##N = अणु \
		.attr = अणु .name = __stringअगरy(N), .mode = 0444 पूर्ण, \
		.vl = N						  \
	पूर्ण

काष्ठा hfi1_vl2mtu_attr अणु
	काष्ठा attribute attr;
	पूर्णांक vl;
पूर्ण;

HFI1_VL2MTU_ATTR(0);
HFI1_VL2MTU_ATTR(1);
HFI1_VL2MTU_ATTR(2);
HFI1_VL2MTU_ATTR(3);
HFI1_VL2MTU_ATTR(4);
HFI1_VL2MTU_ATTR(5);
HFI1_VL2MTU_ATTR(6);
HFI1_VL2MTU_ATTR(7);
HFI1_VL2MTU_ATTR(8);
HFI1_VL2MTU_ATTR(9);
HFI1_VL2MTU_ATTR(10);
HFI1_VL2MTU_ATTR(11);
HFI1_VL2MTU_ATTR(12);
HFI1_VL2MTU_ATTR(13);
HFI1_VL2MTU_ATTR(14);
HFI1_VL2MTU_ATTR(15);

अटल काष्ठा attribute *vl2mtu_शेष_attributes[] = अणु
	&hfi1_vl2mtu_attr_0.attr,
	&hfi1_vl2mtu_attr_1.attr,
	&hfi1_vl2mtu_attr_2.attr,
	&hfi1_vl2mtu_attr_3.attr,
	&hfi1_vl2mtu_attr_4.attr,
	&hfi1_vl2mtu_attr_5.attr,
	&hfi1_vl2mtu_attr_6.attr,
	&hfi1_vl2mtu_attr_7.attr,
	&hfi1_vl2mtu_attr_8.attr,
	&hfi1_vl2mtu_attr_9.attr,
	&hfi1_vl2mtu_attr_10.attr,
	&hfi1_vl2mtu_attr_11.attr,
	&hfi1_vl2mtu_attr_12.attr,
	&hfi1_vl2mtu_attr_13.attr,
	&hfi1_vl2mtu_attr_14.attr,
	&hfi1_vl2mtu_attr_15.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार vl2mtu_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hfi1_vl2mtu_attr *vlattr =
		container_of(attr, काष्ठा hfi1_vl2mtu_attr, attr);
	काष्ठा hfi1_pportdata *ppd =
		container_of(kobj, काष्ठा hfi1_pportdata, vl2mtu_kobj);
	काष्ठा hfi1_devdata *dd = ppd->dd;

	वापस sysfs_emit(buf, "%u\n", dd->vld[vlattr->vl].mtu);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops hfi1_vl2mtu_ops = अणु
	.show = vl2mtu_attr_show,
पूर्ण;

अटल काष्ठा kobj_type hfi1_vl2mtu_ktype = अणु
	.release = port_release,
	.sysfs_ops = &hfi1_vl2mtu_ops,
	.शेष_attrs = vl2mtu_शेष_attributes
पूर्ण;

/* end of per-port file काष्ठाures and support code */

/*
 * Start of per-unit (or driver, in some हालs, but replicated
 * per unit) functions (these get a device *)
 */
अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);

	वापस sysfs_emit(buf, "%x\n", dd_from_dev(dev)->minrev);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार board_id_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);

	अगर (!dd->boardname)
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%s\n", dd->boardname);
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

अटल sमाप_प्रकार boardversion_show(काष्ठा device *device,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);

	/* The string prपूर्णांकed here is alपढ़ोy newline-terminated. */
	वापस sysfs_emit(buf, "%s", dd->boardversion);
पूर्ण
अटल DEVICE_ATTR_RO(boardversion);

अटल sमाप_प्रकार nctxts_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);

	/*
	 * Return the smaller of send and receive contexts.
	 * Normally, user level applications would require both a send
	 * and a receive context, so वापसing the smaller of the two counts
	 * give a more accurate picture of total contexts available.
	 */
	वापस sysfs_emit(buf, "%u\n",
			  min(dd->num_user_contexts,
			      (u32)dd->sc_sizes[SC_USER].count));
पूर्ण
अटल DEVICE_ATTR_RO(nctxts);

अटल sमाप_प्रकार nमुक्तctxts_show(काष्ठा device *device,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);

	/* Return the number of मुक्त user ports (contexts) available. */
	वापस sysfs_emit(buf, "%u\n", dd->मुक्तctxts);
पूर्ण
अटल DEVICE_ATTR_RO(nमुक्तctxts);

अटल sमाप_प्रकार serial_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);

	/* dd->serial is alपढ़ोy newline terminated in chip.c */
	वापस sysfs_emit(buf, "%s", dd->serial);
पूर्ण
अटल DEVICE_ATTR_RO(serial);

अटल sमाप_प्रकार chip_reset_store(काष्ठा device *device,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);
	पूर्णांक ret;

	अगर (count < 5 || स_भेद(buf, "reset", 5) || !dd->diag_client) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	ret = hfi1_reset_device(dd->unit);
bail:
	वापस ret < 0 ? ret : count;
पूर्ण
अटल DEVICE_ATTR_WO(chip_reset);

/*
 * Convert the reported temperature from an पूर्णांकeger (reported in
 * units of 0.25C) to a भग्नing poपूर्णांक number.
 */
#घोषणा temp_d(t) ((t) >> 2)
#घोषणा temp_f(t) (((t)&0x3) * 25u)

/*
 * Dump tempsense values, in decimal, to ease shell-scripts.
 */
अटल sमाप_प्रकार tempsense_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hfi1_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा hfi1_ibdev, rdi.ibdev);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);
	काष्ठा hfi1_temp temp;
	पूर्णांक ret;

	ret = hfi1_tempsense_rd(dd, &temp);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%u.%02u %u.%02u %u.%02u %u.%02u %u %u %u\n",
			  temp_d(temp.curr), temp_f(temp.curr),
			  temp_d(temp.lo_lim), temp_f(temp.lo_lim),
			  temp_d(temp.hi_lim), temp_f(temp.hi_lim),
			  temp_d(temp.crit_lim), temp_f(temp.crit_lim),
			  temp.triggers & 0x1,
			  temp.triggers & 0x2,
			  temp.triggers & 0x4);
पूर्ण
अटल DEVICE_ATTR_RO(tempsense);

/*
 * end of per-unit (or driver, in some हालs, but replicated
 * per unit) functions
 */

/* start of per-unit file काष्ठाures and support code */
अटल काष्ठा attribute *hfi1_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_board_id.attr,
	&dev_attr_nctxts.attr,
	&dev_attr_nमुक्तctxts.attr,
	&dev_attr_serial.attr,
	&dev_attr_boardversion.attr,
	&dev_attr_tempsense.attr,
	&dev_attr_chip_reset.attr,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group ib_hfi1_attr_group = अणु
	.attrs = hfi1_attributes,
पूर्ण;

पूर्णांक hfi1_create_port_files(काष्ठा ib_device *ibdev, u32 port_num,
			   काष्ठा kobject *kobj)
अणु
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	पूर्णांक ret;

	अगर (!port_num || port_num > dd->num_pports) अणु
		dd_dev_err(dd,
			   "Skipping infiniband class with invalid port %u\n",
			   port_num);
		वापस -ENODEV;
	पूर्ण
	ppd = &dd->pport[port_num - 1];

	ret = kobject_init_and_add(&ppd->sc2vl_kobj, &hfi1_sc2vl_ktype, kobj,
				   "sc2vl");
	अगर (ret) अणु
		dd_dev_err(dd,
			   "Skipping sc2vl sysfs info, (err %d) port %u\n",
			   ret, port_num);
		/*
		 * Based on the करोcumentation क्रम kobject_init_and_add(), the
		 * caller should call kobject_put even अगर this call fails.
		 */
		जाओ bail_sc2vl;
	पूर्ण
	kobject_uevent(&ppd->sc2vl_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->sl2sc_kobj, &hfi1_sl2sc_ktype, kobj,
				   "sl2sc");
	अगर (ret) अणु
		dd_dev_err(dd,
			   "Skipping sl2sc sysfs info, (err %d) port %u\n",
			   ret, port_num);
		जाओ bail_sl2sc;
	पूर्ण
	kobject_uevent(&ppd->sl2sc_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->vl2mtu_kobj, &hfi1_vl2mtu_ktype, kobj,
				   "vl2mtu");
	अगर (ret) अणु
		dd_dev_err(dd,
			   "Skipping vl2mtu sysfs info, (err %d) port %u\n",
			   ret, port_num);
		जाओ bail_vl2mtu;
	पूर्ण
	kobject_uevent(&ppd->vl2mtu_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->pport_cc_kobj, &port_cc_ktype,
				   kobj, "CCMgtA");
	अगर (ret) अणु
		dd_dev_err(dd,
			   "Skipping Congestion Control sysfs info, (err %d) port %u\n",
			   ret, port_num);
		जाओ bail_cc;
	पूर्ण

	kobject_uevent(&ppd->pport_cc_kobj, KOBJ_ADD);

	ret = sysfs_create_bin_file(&ppd->pport_cc_kobj, &cc_setting_bin_attr);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "Skipping Congestion Control setting sysfs info, (err %d) port %u\n",
			   ret, port_num);
		जाओ bail_cc;
	पूर्ण

	ret = sysfs_create_bin_file(&ppd->pport_cc_kobj, &cc_table_bin_attr);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "Skipping Congestion Control table sysfs info, (err %d) port %u\n",
			   ret, port_num);
		जाओ bail_cc_entry_bin;
	पूर्ण

	dd_dev_info(dd,
		    "Congestion Control Agent enabled for port %d\n",
		    port_num);

	वापस 0;

bail_cc_entry_bin:
	sysfs_हटाओ_bin_file(&ppd->pport_cc_kobj,
			      &cc_setting_bin_attr);
bail_cc:
	kobject_put(&ppd->pport_cc_kobj);
bail_vl2mtu:
	kobject_put(&ppd->vl2mtu_kobj);
bail_sl2sc:
	kobject_put(&ppd->sl2sc_kobj);
bail_sc2vl:
	kobject_put(&ppd->sc2vl_kobj);
	वापस ret;
पूर्ण

काष्ठा sde_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा sdma_engine *sde, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा sdma_engine *sde, स्थिर अक्षर *buf, माप_प्रकार cnt);
पूर्ण;

अटल sमाप_प्रकार sde_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा sde_attribute *sde_attr =
		container_of(attr, काष्ठा sde_attribute, attr);
	काष्ठा sdma_engine *sde =
		container_of(kobj, काष्ठा sdma_engine, kobj);

	अगर (!sde_attr->show)
		वापस -EINVAL;

	वापस sde_attr->show(sde, buf);
पूर्ण

अटल sमाप_प्रकार sde_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sde_attribute *sde_attr =
		container_of(attr, काष्ठा sde_attribute, attr);
	काष्ठा sdma_engine *sde =
		container_of(kobj, काष्ठा sdma_engine, kobj);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!sde_attr->store)
		वापस -EINVAL;

	वापस sde_attr->store(sde, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops sde_sysfs_ops = अणु
	.show = sde_show,
	.store = sde_store,
पूर्ण;

अटल काष्ठा kobj_type sde_ktype = अणु
	.sysfs_ops = &sde_sysfs_ops,
पूर्ण;

#घोषणा SDE_ATTR(_name, _mode, _show, _store) \
	काष्ठा sde_attribute sde_attr_##_name = \
		__ATTR(_name, _mode, _show, _store)

अटल sमाप_प्रकार sde_show_cpu_to_sde_map(काष्ठा sdma_engine *sde, अक्षर *buf)
अणु
	वापस sdma_get_cpu_to_sde_map(sde, buf);
पूर्ण

अटल sमाप_प्रकार sde_store_cpu_to_sde_map(काष्ठा sdma_engine *sde,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sdma_set_cpu_to_sde_map(sde, buf, count);
पूर्ण

अटल sमाप_प्रकार sde_show_vl(काष्ठा sdma_engine *sde, अक्षर *buf)
अणु
	पूर्णांक vl;

	vl = sdma_engine_get_vl(sde);
	अगर (vl < 0)
		वापस vl;

	वापस sysfs_emit(buf, "%d\n", vl);
पूर्ण

अटल SDE_ATTR(cpu_list, S_IWUSR | S_IRUGO,
		sde_show_cpu_to_sde_map,
		sde_store_cpu_to_sde_map);
अटल SDE_ATTR(vl, S_IRUGO, sde_show_vl, शून्य);

अटल काष्ठा sde_attribute *sde_attribs[] = अणु
	&sde_attr_cpu_list,
	&sde_attr_vl
पूर्ण;

/*
 * Register and create our files in /sys/class/infiniband.
 */
पूर्णांक hfi1_verbs_रेजिस्टर_sysfs(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा ib_device *dev = &dd->verbs_dev.rdi.ibdev;
	काष्ठा device *class_dev = &dev->dev;
	पूर्णांक i, j, ret;

	क्रम (i = 0; i < dd->num_sdma; i++) अणु
		ret = kobject_init_and_add(&dd->per_sdma[i].kobj,
					   &sde_ktype, &class_dev->kobj,
					   "sdma%d", i);
		अगर (ret)
			जाओ bail;

		क्रम (j = 0; j < ARRAY_SIZE(sde_attribs); j++) अणु
			ret = sysfs_create_file(&dd->per_sdma[i].kobj,
						&sde_attribs[j]->attr);
			अगर (ret)
				जाओ bail;
		पूर्ण
	पूर्ण

	वापस 0;
bail:
	/*
	 * The function kobject_put() will call kobject_del() अगर the kobject
	 * has been added successfully. The sysfs files created under the
	 * kobject directory will also be हटाओd during the process.
	 */
	क्रम (; i >= 0; i--)
		kobject_put(&dd->per_sdma[i].kobj);

	वापस ret;
पूर्ण

/*
 * Unरेजिस्टर and हटाओ our files in /sys/class/infiniband.
 */
व्योम hfi1_verbs_unरेजिस्टर_sysfs(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक i;

	/* Unwind operations in hfi1_verbs_रेजिस्टर_sysfs() */
	क्रम (i = 0; i < dd->num_sdma; i++)
		kobject_put(&dd->per_sdma[i].kobj);

	क्रम (i = 0; i < dd->num_pports; i++) अणु
		ppd = &dd->pport[i];

		sysfs_हटाओ_bin_file(&ppd->pport_cc_kobj,
				      &cc_setting_bin_attr);
		sysfs_हटाओ_bin_file(&ppd->pport_cc_kobj,
				      &cc_table_bin_attr);
		kobject_put(&ppd->pport_cc_kobj);
		kobject_put(&ppd->vl2mtu_kobj);
		kobject_put(&ppd->sl2sc_kobj);
		kobject_put(&ppd->sc2vl_kobj);
	पूर्ण
पूर्ण
