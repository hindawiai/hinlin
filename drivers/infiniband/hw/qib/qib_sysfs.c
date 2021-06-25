<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2006 PathScale, Inc. All rights reserved.
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
#समावेश <linux/प्रकार.स>

#समावेश "qib.h"
#समावेश "qib_mad.h"

/* start of per-port functions */
/*
 * Get/Set heartbeat enable. OR of 1=enabled, 2=स्वतः
 */
अटल sमाप_प्रकार show_hrtbt_enb(काष्ठा qib_pportdata *ppd, अक्षर *buf)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;

	वापस sysfs_emit(buf, "%d\n", dd->f_get_ib_cfg(ppd, QIB_IB_CFG_HRTBT));
पूर्ण

अटल sमाप_प्रकार store_hrtbt_enb(काष्ठा qib_pportdata *ppd, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक ret;
	u16 val;

	ret = kstrtou16(buf, 0, &val);
	अगर (ret) अणु
		qib_dev_err(dd, "attempt to set invalid Heartbeat enable\n");
		वापस ret;
	पूर्ण

	/*
	 * Set the "intentional" heartbeat enable per either of
	 * "Enable" and "Auto", as these are normally set together.
	 * This bit is consulted when leaving loopback mode,
	 * because entering loopback mode overrides it and स्वतःmatically
	 * disables heartbeat.
	 */
	ret = dd->f_set_ib_cfg(ppd, QIB_IB_CFG_HRTBT, val);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार store_loopback(काष्ठा qib_pportdata *ppd, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक ret = count, r;

	r = dd->f_set_ib_loopback(ppd, buf);
	अगर (r < 0)
		ret = r;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_led_override(काष्ठा qib_pportdata *ppd, स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक ret;
	u16 val;

	ret = kstrtou16(buf, 0, &val);
	अगर (ret) अणु
		qib_dev_err(dd, "attempt to set invalid LED override\n");
		वापस ret;
	पूर्ण

	qib_set_led_override(ppd, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_status(काष्ठा qib_pportdata *ppd, अक्षर *buf)
अणु
	अगर (!ppd->statusp)
		वापस -EINVAL;

	वापस sysfs_emit(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)*(ppd->statusp));
पूर्ण

/*
 * For userland compatibility, these offsets must reमुख्य fixed.
 * They are strings क्रम QIB_STATUS_*
 */
अटल स्थिर अक्षर * स्थिर qib_status_str[] = अणु
	"Initted",
	"",
	"",
	"",
	"",
	"Present",
	"IB_link_up",
	"IB_configured",
	"",
	"Fatal_Hardware_Error",
	शून्य,
पूर्ण;

अटल sमाप_प्रकार show_status_str(काष्ठा qib_pportdata *ppd, अक्षर *buf)
अणु
	पूर्णांक i, any;
	u64 s;
	sमाप_प्रकार ret;

	अगर (!ppd->statusp) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	s = *(ppd->statusp);
	*buf = '\0';
	क्रम (any = i = 0; s && qib_status_str[i]; i++) अणु
		अगर (s & 1) अणु
			/* अगर overflow */
			अगर (any && strlcat(buf, " ", PAGE_SIZE) >= PAGE_SIZE)
				अवरोध;
			अगर (strlcat(buf, qib_status_str[i], PAGE_SIZE) >=
					PAGE_SIZE)
				अवरोध;
			any = 1;
		पूर्ण
		s >>= 1;
	पूर्ण
	अगर (any)
		strlcat(buf, "\n", PAGE_SIZE);

	ret = म_माप(buf);

bail:
	वापस ret;
पूर्ण

/* end of per-port functions */

/*
 * Start of per-port file काष्ठाures and support code
 * Because we are fitting पूर्णांकo other infraकाष्ठाure, we have to supply the
 * full set of kobject/sysfs_ops काष्ठाures and routines.
 */
#घोषणा QIB_PORT_ATTR(name, mode, show, store) \
	अटल काष्ठा qib_port_attr qib_port_attr_##name = \
		__ATTR(name, mode, show, store)

काष्ठा qib_port_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा qib_pportdata *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा qib_pportdata *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

QIB_PORT_ATTR(loopback, S_IWUSR, शून्य, store_loopback);
QIB_PORT_ATTR(led_override, S_IWUSR, शून्य, store_led_override);
QIB_PORT_ATTR(hrtbt_enable, S_IWUSR | S_IRUGO, show_hrtbt_enb,
	      store_hrtbt_enb);
QIB_PORT_ATTR(status, S_IRUGO, show_status, शून्य);
QIB_PORT_ATTR(status_str, S_IRUGO, show_status_str, शून्य);

अटल काष्ठा attribute *port_शेष_attributes[] = अणु
	&qib_port_attr_loopback.attr,
	&qib_port_attr_led_override.attr,
	&qib_port_attr_hrtbt_enable.attr,
	&qib_port_attr_status.attr,
	&qib_port_attr_status_str.attr,
	शून्य
पूर्ण;

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
	काष्ठा qib_pportdata *ppd =
		container_of(kobj, काष्ठा qib_pportdata, pport_cc_kobj);

	अगर (!qib_cc_table_size || !ppd->ccti_entries_shaकरोw)
		वापस -EINVAL;

	ret = ppd->total_cct_entry * माप(काष्ठा ib_cc_table_entry_shaकरोw)
		 + माप(__be16);

	अगर (pos > ret)
		वापस -EINVAL;

	अगर (count > ret - pos)
		count = ret - pos;

	अगर (!count)
		वापस count;

	spin_lock(&ppd->cc_shaकरोw_lock);
	स_नकल(buf, ppd->ccti_entries_shaकरोw, count);
	spin_unlock(&ppd->cc_shaकरोw_lock);

	वापस count;
पूर्ण

अटल व्योम qib_port_release(काष्ठा kobject *kobj)
अणु
	/* nothing to करो since memory is मुक्तd by qib_मुक्त_devdata() */
पूर्ण

अटल काष्ठा kobj_type qib_port_cc_ktype = अणु
	.release = qib_port_release,
पूर्ण;

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
	काष्ठा qib_pportdata *ppd =
		container_of(kobj, काष्ठा qib_pportdata, pport_cc_kobj);

	अगर (!qib_cc_table_size || !ppd->congestion_entries_shaकरोw)
		वापस -EINVAL;

	ret = माप(काष्ठा ib_cc_congestion_setting_attr_shaकरोw);

	अगर (pos > ret)
		वापस -EINVAL;
	अगर (count > ret - pos)
		count = ret - pos;

	अगर (!count)
		वापस count;

	spin_lock(&ppd->cc_shaकरोw_lock);
	स_नकल(buf, ppd->congestion_entries_shaकरोw, count);
	spin_unlock(&ppd->cc_shaकरोw_lock);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute cc_setting_bin_attr = अणु
	.attr = अणु.name = "cc_settings_bin", .mode = 0444पूर्ण,
	.पढ़ो = पढ़ो_cc_setting_bin,
	.size = PAGE_SIZE,
पूर्ण;


अटल sमाप_प्रकार qib_portattr_show(काष्ठा kobject *kobj,
	काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा qib_port_attr *pattr =
		container_of(attr, काष्ठा qib_port_attr, attr);
	काष्ठा qib_pportdata *ppd =
		container_of(kobj, काष्ठा qib_pportdata, pport_kobj);

	अगर (!pattr->show)
		वापस -EIO;

	वापस pattr->show(ppd, buf);
पूर्ण

अटल sमाप_प्रकार qib_portattr_store(काष्ठा kobject *kobj,
	काष्ठा attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा qib_port_attr *pattr =
		container_of(attr, काष्ठा qib_port_attr, attr);
	काष्ठा qib_pportdata *ppd =
		container_of(kobj, काष्ठा qib_pportdata, pport_kobj);

	अगर (!pattr->store)
		वापस -EIO;

	वापस pattr->store(ppd, buf, len);
पूर्ण


अटल स्थिर काष्ठा sysfs_ops qib_port_ops = अणु
	.show = qib_portattr_show,
	.store = qib_portattr_store,
पूर्ण;

अटल काष्ठा kobj_type qib_port_ktype = अणु
	.release = qib_port_release,
	.sysfs_ops = &qib_port_ops,
	.शेष_attrs = port_शेष_attributes
पूर्ण;

/* Start sl2vl */

#घोषणा QIB_SL2VL_ATTR(N) \
	अटल काष्ठा qib_sl2vl_attr qib_sl2vl_attr_##N = अणु \
		.attr = अणु .name = __stringअगरy(N), .mode = 0444 पूर्ण, \
		.sl = N \
	पूर्ण

काष्ठा qib_sl2vl_attr अणु
	काष्ठा attribute attr;
	पूर्णांक sl;
पूर्ण;

QIB_SL2VL_ATTR(0);
QIB_SL2VL_ATTR(1);
QIB_SL2VL_ATTR(2);
QIB_SL2VL_ATTR(3);
QIB_SL2VL_ATTR(4);
QIB_SL2VL_ATTR(5);
QIB_SL2VL_ATTR(6);
QIB_SL2VL_ATTR(7);
QIB_SL2VL_ATTR(8);
QIB_SL2VL_ATTR(9);
QIB_SL2VL_ATTR(10);
QIB_SL2VL_ATTR(11);
QIB_SL2VL_ATTR(12);
QIB_SL2VL_ATTR(13);
QIB_SL2VL_ATTR(14);
QIB_SL2VL_ATTR(15);

अटल काष्ठा attribute *sl2vl_शेष_attributes[] = अणु
	&qib_sl2vl_attr_0.attr,
	&qib_sl2vl_attr_1.attr,
	&qib_sl2vl_attr_2.attr,
	&qib_sl2vl_attr_3.attr,
	&qib_sl2vl_attr_4.attr,
	&qib_sl2vl_attr_5.attr,
	&qib_sl2vl_attr_6.attr,
	&qib_sl2vl_attr_7.attr,
	&qib_sl2vl_attr_8.attr,
	&qib_sl2vl_attr_9.attr,
	&qib_sl2vl_attr_10.attr,
	&qib_sl2vl_attr_11.attr,
	&qib_sl2vl_attr_12.attr,
	&qib_sl2vl_attr_13.attr,
	&qib_sl2vl_attr_14.attr,
	&qib_sl2vl_attr_15.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार sl2vl_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा qib_sl2vl_attr *sattr =
		container_of(attr, काष्ठा qib_sl2vl_attr, attr);
	काष्ठा qib_pportdata *ppd =
		container_of(kobj, काष्ठा qib_pportdata, sl2vl_kobj);
	काष्ठा qib_ibport *qibp = &ppd->ibport_data;

	वापस sysfs_emit(buf, "%u\n", qibp->sl_to_vl[sattr->sl]);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops qib_sl2vl_ops = अणु
	.show = sl2vl_attr_show,
पूर्ण;

अटल काष्ठा kobj_type qib_sl2vl_ktype = अणु
	.release = qib_port_release,
	.sysfs_ops = &qib_sl2vl_ops,
	.शेष_attrs = sl2vl_शेष_attributes
पूर्ण;

/* End sl2vl */

/* Start diag_counters */

#घोषणा QIB_DIAGC_ATTR(N) \
	अटल काष्ठा qib_diagc_attr qib_diagc_attr_##N = अणु \
		.attr = अणु .name = __stringअगरy(N), .mode = 0664 पूर्ण, \
		.counter = दुरत्व(काष्ठा qib_ibport, rvp.n_##N) \
	पूर्ण

#घोषणा QIB_DIAGC_ATTR_PER_CPU(N) \
	अटल काष्ठा qib_diagc_attr qib_diagc_attr_##N = अणु \
		.attr = अणु .name = __stringअगरy(N), .mode = 0664 पूर्ण, \
		.counter = दुरत्व(काष्ठा qib_ibport, rvp.z_##N) \
	पूर्ण

काष्ठा qib_diagc_attr अणु
	काष्ठा attribute attr;
	माप_प्रकार counter;
पूर्ण;

QIB_DIAGC_ATTR_PER_CPU(rc_acks);
QIB_DIAGC_ATTR_PER_CPU(rc_qacks);
QIB_DIAGC_ATTR_PER_CPU(rc_delayed_comp);

QIB_DIAGC_ATTR(rc_resends);
QIB_DIAGC_ATTR(seq_naks);
QIB_DIAGC_ATTR(rdma_seq);
QIB_DIAGC_ATTR(rnr_naks);
QIB_DIAGC_ATTR(other_naks);
QIB_DIAGC_ATTR(rc_समयouts);
QIB_DIAGC_ATTR(loop_pkts);
QIB_DIAGC_ATTR(pkt_drops);
QIB_DIAGC_ATTR(dmaरुको);
QIB_DIAGC_ATTR(unaligned);
QIB_DIAGC_ATTR(rc_dupreq);
QIB_DIAGC_ATTR(rc_seqnak);
QIB_DIAGC_ATTR(rc_crरुकोs);

अटल काष्ठा attribute *diagc_शेष_attributes[] = अणु
	&qib_diagc_attr_rc_resends.attr,
	&qib_diagc_attr_rc_acks.attr,
	&qib_diagc_attr_rc_qacks.attr,
	&qib_diagc_attr_rc_delayed_comp.attr,
	&qib_diagc_attr_seq_naks.attr,
	&qib_diagc_attr_rdma_seq.attr,
	&qib_diagc_attr_rnr_naks.attr,
	&qib_diagc_attr_other_naks.attr,
	&qib_diagc_attr_rc_समयouts.attr,
	&qib_diagc_attr_loop_pkts.attr,
	&qib_diagc_attr_pkt_drops.attr,
	&qib_diagc_attr_dmaरुको.attr,
	&qib_diagc_attr_unaligned.attr,
	&qib_diagc_attr_rc_dupreq.attr,
	&qib_diagc_attr_rc_seqnak.attr,
	&qib_diagc_attr_rc_crरुकोs.attr,
	शून्य
पूर्ण;

अटल u64 get_all_cpu_total(u64 __percpu *cntr)
अणु
	पूर्णांक cpu;
	u64 counter = 0;

	क्रम_each_possible_cpu(cpu)
		counter += *per_cpu_ptr(cntr, cpu);
	वापस counter;
पूर्ण

#घोषणा def_ग_लिखो_per_cpu(cntr) \
अटल व्योम ग_लिखो_per_cpu_##cntr(काष्ठा qib_pportdata *ppd, u32 data)	\
अणु									\
	काष्ठा qib_devdata *dd = ppd->dd;				\
	काष्ठा qib_ibport *qibp = &ppd->ibport_data;			\
	/*  A ग_लिखो can only zero the counter */			\
	अगर (data == 0)							\
		qibp->rvp.z_##cntr = get_all_cpu_total(qibp->rvp.cntr); \
	अन्यथा								\
		qib_dev_err(dd, "Per CPU cntrs can only be zeroed");	\
पूर्ण

def_ग_लिखो_per_cpu(rc_acks)
def_ग_लिखो_per_cpu(rc_qacks)
def_ग_लिखो_per_cpu(rc_delayed_comp)

#घोषणा READ_PER_CPU_CNTR(cntr) (get_all_cpu_total(qibp->rvp.cntr) - \
							qibp->rvp.z_##cntr)

अटल sमाप_प्रकार diagc_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा qib_diagc_attr *dattr =
		container_of(attr, काष्ठा qib_diagc_attr, attr);
	काष्ठा qib_pportdata *ppd =
		container_of(kobj, काष्ठा qib_pportdata, diagc_kobj);
	काष्ठा qib_ibport *qibp = &ppd->ibport_data;
	u64 val;

	अगर (!म_भेदन(dattr->attr.name, "rc_acks", 7))
		val = READ_PER_CPU_CNTR(rc_acks);
	अन्यथा अगर (!म_भेदन(dattr->attr.name, "rc_qacks", 8))
		val = READ_PER_CPU_CNTR(rc_qacks);
	अन्यथा अगर (!म_भेदन(dattr->attr.name, "rc_delayed_comp", 15))
		val = READ_PER_CPU_CNTR(rc_delayed_comp);
	अन्यथा
		val = *(u32 *)((अक्षर *)qibp + dattr->counter);

	वापस sysfs_emit(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार diagc_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा qib_diagc_attr *dattr =
		container_of(attr, काष्ठा qib_diagc_attr, attr);
	काष्ठा qib_pportdata *ppd =
		container_of(kobj, काष्ठा qib_pportdata, diagc_kobj);
	काष्ठा qib_ibport *qibp = &ppd->ibport_data;
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (!म_भेदन(dattr->attr.name, "rc_acks", 7))
		ग_लिखो_per_cpu_rc_acks(ppd, val);
	अन्यथा अगर (!म_भेदन(dattr->attr.name, "rc_qacks", 8))
		ग_लिखो_per_cpu_rc_qacks(ppd, val);
	अन्यथा अगर (!म_भेदन(dattr->attr.name, "rc_delayed_comp", 15))
		ग_लिखो_per_cpu_rc_delayed_comp(ppd, val);
	अन्यथा
		*(u32 *)((अक्षर *)qibp + dattr->counter) = val;
	वापस size;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops qib_diagc_ops = अणु
	.show = diagc_attr_show,
	.store = diagc_attr_store,
पूर्ण;

अटल काष्ठा kobj_type qib_diagc_ktype = अणु
	.release = qib_port_release,
	.sysfs_ops = &qib_diagc_ops,
	.शेष_attrs = diagc_शेष_attributes
पूर्ण;

/* End diag_counters */

/* end of per-port file काष्ठाures and support code */

/*
 * Start of per-unit (or driver, in some हालs, but replicated
 * per unit) functions (these get a device *)
 */
अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);

	वापस sysfs_emit(buf, "%x\n", dd_from_dev(dev)->minrev);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);

	अगर (!dd->boardname)
		वापस -EINVAL;
	वापस sysfs_emit(buf, "%s\n", dd->boardname);
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);
अटल DEVICE_ATTR(board_id, 0444, hca_type_show, शून्य);

अटल sमाप_प्रकार version_show(काष्ठा device *device,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	/* The string prपूर्णांकed here is alपढ़ोy newline-terminated. */
	वापस sysfs_emit(buf, "%s", (अक्षर *)ib_qib_version);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार boardversion_show(काष्ठा device *device,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);

	/* The string prपूर्णांकed here is alपढ़ोy newline-terminated. */
	वापस sysfs_emit(buf, "%s", dd->boardversion);
पूर्ण
अटल DEVICE_ATTR_RO(boardversion);

अटल sमाप_प्रकार localbus_info_show(काष्ठा device *device,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);

	/* The string prपूर्णांकed here is alपढ़ोy newline-terminated. */
	वापस sysfs_emit(buf, "%s", dd->lbus_info);
पूर्ण
अटल DEVICE_ATTR_RO(localbus_info);

अटल sमाप_प्रकार nctxts_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);

	/* Return the number of user ports (contexts) available. */
	/* The calculation below deals with a special हाल where
	 * cfgctxts is set to 1 on a single-port board. */
	वापस sysfs_emit(buf, "%u\n",
			  (dd->first_user_ctxt > dd->cfgctxts) ?
				  0 :
				  (dd->cfgctxts - dd->first_user_ctxt));
पूर्ण
अटल DEVICE_ATTR_RO(nctxts);

अटल sमाप_प्रकार nमुक्तctxts_show(काष्ठा device *device,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);

	/* Return the number of मुक्त user ports (contexts) available. */
	वापस sysfs_emit(buf, "%u\n", dd->मुक्तctxts);
पूर्ण
अटल DEVICE_ATTR_RO(nमुक्तctxts);

अटल sमाप_प्रकार serial_show(काष्ठा device *device, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	स्थिर u8 *end = स_प्रथम(dd->serial, 0, ARRAY_SIZE(dd->serial));
	पूर्णांक size = end ? end - dd->serial : ARRAY_SIZE(dd->serial);

	वापस sysfs_emit(buf, ".%*s\n", size, dd->serial);
पूर्ण
अटल DEVICE_ATTR_RO(serial);

अटल sमाप_प्रकार chip_reset_store(काष्ठा device *device,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	पूर्णांक ret;

	अगर (count < 5 || स_भेद(buf, "reset", 5) || !dd->diag_client) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	ret = qib_reset_device(dd->unit);
bail:
	वापस ret < 0 ? ret : count;
पूर्ण
अटल DEVICE_ATTR_WO(chip_reset);

/*
 * Dump tempsense regs. in decimal, to ease shell-scripts.
 */
अटल sमाप_प्रकार tempsense_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qib_ibdev *dev =
		rdma_device_to_drv_device(device, काष्ठा qib_ibdev, rdi.ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	पूर्णांक i;
	u8 regvals[8];

	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक ret;

		अगर (i == 6)
			जारी;
		ret = dd->f_tempsense_rd(dd, i);
		अगर (ret < 0)
			वापस ret;	/* वापस error on bad पढ़ो */
		regvals[i] = ret;
	पूर्ण
	वापस sysfs_emit(buf, "%d %d %02X %02X %d %d\n",
			  (चिन्हित अक्षर)regvals[0],
			  (चिन्हित अक्षर)regvals[1],
			  regvals[2],
			  regvals[3],
			  (चिन्हित अक्षर)regvals[5],
			  (चिन्हित अक्षर)regvals[7]);
पूर्ण
अटल DEVICE_ATTR_RO(tempsense);

/*
 * end of per-unit (or driver, in some हालs, but replicated
 * per unit) functions
 */

/* start of per-unit file काष्ठाures and support code */
अटल काष्ठा attribute *qib_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	&dev_attr_board_id.attr,
	&dev_attr_version.attr,
	&dev_attr_nctxts.attr,
	&dev_attr_nमुक्तctxts.attr,
	&dev_attr_serial.attr,
	&dev_attr_boardversion.attr,
	&dev_attr_tempsense.attr,
	&dev_attr_localbus_info.attr,
	&dev_attr_chip_reset.attr,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group qib_attr_group = अणु
	.attrs = qib_attributes,
पूर्ण;

पूर्णांक qib_create_port_files(काष्ठा ib_device *ibdev, u32 port_num,
			  काष्ठा kobject *kobj)
अणु
	काष्ठा qib_pportdata *ppd;
	काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);
	पूर्णांक ret;

	अगर (!port_num || port_num > dd->num_pports) अणु
		qib_dev_err(dd,
			"Skipping infiniband class with invalid port %u\n",
			port_num);
		ret = -ENODEV;
		जाओ bail;
	पूर्ण
	ppd = &dd->pport[port_num - 1];

	ret = kobject_init_and_add(&ppd->pport_kobj, &qib_port_ktype, kobj,
				   "linkcontrol");
	अगर (ret) अणु
		qib_dev_err(dd,
			"Skipping linkcontrol sysfs info, (err %d) port %u\n",
			ret, port_num);
		जाओ bail_link;
	पूर्ण
	kobject_uevent(&ppd->pport_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->sl2vl_kobj, &qib_sl2vl_ktype, kobj,
				   "sl2vl");
	अगर (ret) अणु
		qib_dev_err(dd,
			"Skipping sl2vl sysfs info, (err %d) port %u\n",
			ret, port_num);
		जाओ bail_sl;
	पूर्ण
	kobject_uevent(&ppd->sl2vl_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->diagc_kobj, &qib_diagc_ktype, kobj,
				   "diag_counters");
	अगर (ret) अणु
		qib_dev_err(dd,
			"Skipping diag_counters sysfs info, (err %d) port %u\n",
			ret, port_num);
		जाओ bail_diagc;
	पूर्ण
	kobject_uevent(&ppd->diagc_kobj, KOBJ_ADD);

	अगर (!qib_cc_table_size || !ppd->congestion_entries_shaकरोw)
		वापस 0;

	ret = kobject_init_and_add(&ppd->pport_cc_kobj, &qib_port_cc_ktype,
				kobj, "CCMgtA");
	अगर (ret) अणु
		qib_dev_err(dd,
		 "Skipping Congestion Control sysfs info, (err %d) port %u\n",
		 ret, port_num);
		जाओ bail_cc;
	पूर्ण

	kobject_uevent(&ppd->pport_cc_kobj, KOBJ_ADD);

	ret = sysfs_create_bin_file(&ppd->pport_cc_kobj,
				&cc_setting_bin_attr);
	अगर (ret) अणु
		qib_dev_err(dd,
		 "Skipping Congestion Control setting sysfs info, (err %d) port %u\n",
		 ret, port_num);
		जाओ bail_cc;
	पूर्ण

	ret = sysfs_create_bin_file(&ppd->pport_cc_kobj,
				&cc_table_bin_attr);
	अगर (ret) अणु
		qib_dev_err(dd,
		 "Skipping Congestion Control table sysfs info, (err %d) port %u\n",
		 ret, port_num);
		जाओ bail_cc_entry_bin;
	पूर्ण

	qib_devinfo(dd->pcidev,
		"IB%u: Congestion Control Agent enabled for port %d\n",
		dd->unit, port_num);

	वापस 0;

bail_cc_entry_bin:
	sysfs_हटाओ_bin_file(&ppd->pport_cc_kobj, &cc_setting_bin_attr);
bail_cc:
	kobject_put(&ppd->pport_cc_kobj);
bail_diagc:
	kobject_put(&ppd->diagc_kobj);
bail_sl:
	kobject_put(&ppd->sl2vl_kobj);
bail_link:
	kobject_put(&ppd->pport_kobj);
bail:
	वापस ret;
पूर्ण

/*
 * Unरेजिस्टर and हटाओ our files in /sys/class/infiniband.
 */
व्योम qib_verbs_unरेजिस्टर_sysfs(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_pportdata *ppd;
	पूर्णांक i;

	क्रम (i = 0; i < dd->num_pports; i++) अणु
		ppd = &dd->pport[i];
		अगर (qib_cc_table_size &&
			ppd->congestion_entries_shaकरोw) अणु
			sysfs_हटाओ_bin_file(&ppd->pport_cc_kobj,
				&cc_setting_bin_attr);
			sysfs_हटाओ_bin_file(&ppd->pport_cc_kobj,
				&cc_table_bin_attr);
			kobject_put(&ppd->pport_cc_kobj);
		पूर्ण
		kobject_put(&ppd->diagc_kobj);
		kobject_put(&ppd->sl2vl_kobj);
		kobject_put(&ppd->pport_kobj);
	पूर्ण
पूर्ण
