<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
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

#समावेश "core_priv.h"

#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_pma.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/rdma_counter.h>

काष्ठा ib_port;

काष्ठा gid_attr_group अणु
	काष्ठा ib_port		*port;
	काष्ठा kobject		kobj;
	काष्ठा attribute_group	ndev;
	काष्ठा attribute_group	type;
पूर्ण;
काष्ठा ib_port अणु
	काष्ठा kobject         kobj;
	काष्ठा ib_device      *ibdev;
	काष्ठा gid_attr_group *gid_attr_group;
	काष्ठा attribute_group gid_group;
	काष्ठा attribute_group *pkey_group;
	स्थिर काष्ठा attribute_group *pma_table;
	काष्ठा attribute_group *hw_stats_ag;
	काष्ठा rdma_hw_stats   *hw_stats;
	u32                     port_num;
पूर्ण;

काष्ठा port_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा ib_port *, काष्ठा port_attribute *, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा ib_port *, काष्ठा port_attribute *,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

#घोषणा PORT_ATTR(_name, _mode, _show, _store) \
काष्ठा port_attribute port_attr_##_name = __ATTR(_name, _mode, _show, _store)

#घोषणा PORT_ATTR_RO(_name) \
काष्ठा port_attribute port_attr_##_name = __ATTR_RO(_name)

काष्ठा port_table_attribute अणु
	काष्ठा port_attribute	attr;
	अक्षर			name[8];
	पूर्णांक			index;
	__be16			attr_id;
पूर्ण;

काष्ठा hw_stats_attribute अणु
	काष्ठा attribute	attr;
	sमाप_प्रकार			(*show)(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, अक्षर *buf);
	sमाप_प्रकार			(*store)(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr,
					 स्थिर अक्षर *buf,
					 माप_प्रकार count);
	पूर्णांक			index;
	u32			port_num;
पूर्ण;

अटल sमाप_प्रकार port_attr_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा port_attribute *port_attr =
		container_of(attr, काष्ठा port_attribute, attr);
	काष्ठा ib_port *p = container_of(kobj, काष्ठा ib_port, kobj);

	अगर (!port_attr->show)
		वापस -EIO;

	वापस port_attr->show(p, port_attr, buf);
पूर्ण

अटल sमाप_प्रकार port_attr_store(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा port_attribute *port_attr =
		container_of(attr, काष्ठा port_attribute, attr);
	काष्ठा ib_port *p = container_of(kobj, काष्ठा ib_port, kobj);

	अगर (!port_attr->store)
		वापस -EIO;
	वापस port_attr->store(p, port_attr, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops port_sysfs_ops = अणु
	.show	= port_attr_show,
	.store	= port_attr_store
पूर्ण;

अटल sमाप_प्रकार gid_attr_show(काष्ठा kobject *kobj,
			     काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा port_attribute *port_attr =
		container_of(attr, काष्ठा port_attribute, attr);
	काष्ठा ib_port *p = container_of(kobj, काष्ठा gid_attr_group,
					 kobj)->port;

	अगर (!port_attr->show)
		वापस -EIO;

	वापस port_attr->show(p, port_attr, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops gid_attr_sysfs_ops = अणु
	.show = gid_attr_show
पूर्ण;

अटल sमाप_प्रकार state_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			  अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;
	sमाप_प्रकार ret;

	अटल स्थिर अक्षर *state_name[] = अणु
		[IB_PORT_NOP]		= "NOP",
		[IB_PORT_DOWN]		= "DOWN",
		[IB_PORT_INIT]		= "INIT",
		[IB_PORT_ARMED]		= "ARMED",
		[IB_PORT_ACTIVE]	= "ACTIVE",
		[IB_PORT_ACTIVE_DEFER]	= "ACTIVE_DEFER"
	पूर्ण;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%d: %s\n", attr.state,
			  attr.state >= 0 &&
					  attr.state < ARRAY_SIZE(state_name) ?
				  state_name[attr.state] :
				  "UNKNOWN");
पूर्ण

अटल sमाप_प्रकार lid_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;
	sमाप_प्रकार ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "0x%x\n", attr.lid);
पूर्ण

अटल sमाप_प्रकार lid_mask_count_show(काष्ठा ib_port *p,
				   काष्ठा port_attribute *unused,
				   अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;
	sमाप_प्रकार ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", attr.lmc);
पूर्ण

अटल sमाप_प्रकार sm_lid_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			   अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;
	sमाप_प्रकार ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "0x%x\n", attr.sm_lid);
पूर्ण

अटल sमाप_प्रकार sm_sl_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			  अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;
	sमाप_प्रकार ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", attr.sm_sl);
पूर्ण

अटल sमाप_प्रकार cap_mask_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			     अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;
	sमाप_प्रकार ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "0x%08x\n", attr.port_cap_flags);
पूर्ण

अटल sमाप_प्रकार rate_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			 अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;
	अक्षर *speed = "";
	पूर्णांक rate;		/* in deci-Gb/sec */
	sमाप_प्रकार ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	चयन (attr.active_speed) अणु
	हाल IB_SPEED_DDR:
		speed = " DDR";
		rate = 50;
		अवरोध;
	हाल IB_SPEED_QDR:
		speed = " QDR";
		rate = 100;
		अवरोध;
	हाल IB_SPEED_FDR10:
		speed = " FDR10";
		rate = 100;
		अवरोध;
	हाल IB_SPEED_FDR:
		speed = " FDR";
		rate = 140;
		अवरोध;
	हाल IB_SPEED_EDR:
		speed = " EDR";
		rate = 250;
		अवरोध;
	हाल IB_SPEED_HDR:
		speed = " HDR";
		rate = 500;
		अवरोध;
	हाल IB_SPEED_NDR:
		speed = " NDR";
		rate = 1000;
		अवरोध;
	हाल IB_SPEED_SDR:
	शेष:		/* शेष to SDR क्रम invalid rates */
		speed = " SDR";
		rate = 25;
		अवरोध;
	पूर्ण

	rate *= ib_width_क्रमागत_to_पूर्णांक(attr.active_width);
	अगर (rate < 0)
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%d%s Gb/sec (%dX%s)\n", rate / 10,
			  rate % 10 ? ".5" : "",
			  ib_width_क्रमागत_to_पूर्णांक(attr.active_width), speed);
पूर्ण

अटल स्थिर अक्षर *phys_state_to_str(क्रमागत ib_port_phys_state phys_state)
अणु
	अटल स्थिर अक्षर *phys_state_str[] = अणु
		"<unknown>",
		"Sleep",
		"Polling",
		"Disabled",
		"PortConfigurationTraining",
		"LinkUp",
		"LinkErrorRecovery",
		"Phy Test",
	पूर्ण;

	अगर (phys_state < ARRAY_SIZE(phys_state_str))
		वापस phys_state_str[phys_state];
	वापस "<unknown>";
पूर्ण

अटल sमाप_प्रकार phys_state_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			       अक्षर *buf)
अणु
	काष्ठा ib_port_attr attr;

	sमाप_प्रकार ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%d: %s\n", attr.phys_state,
			  phys_state_to_str(attr.phys_state));
पूर्ण

अटल sमाप_प्रकार link_layer_show(काष्ठा ib_port *p, काष्ठा port_attribute *unused,
			       अक्षर *buf)
अणु
	स्थिर अक्षर *output;

	चयन (rdma_port_get_link_layer(p->ibdev, p->port_num)) अणु
	हाल IB_LINK_LAYER_INFINIBAND:
		output = "InfiniBand";
		अवरोध;
	हाल IB_LINK_LAYER_ETHERNET:
		output = "Ethernet";
		अवरोध;
	शेष:
		output = "Unknown";
		अवरोध;
	पूर्ण

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

अटल PORT_ATTR_RO(state);
अटल PORT_ATTR_RO(lid);
अटल PORT_ATTR_RO(lid_mask_count);
अटल PORT_ATTR_RO(sm_lid);
अटल PORT_ATTR_RO(sm_sl);
अटल PORT_ATTR_RO(cap_mask);
अटल PORT_ATTR_RO(rate);
अटल PORT_ATTR_RO(phys_state);
अटल PORT_ATTR_RO(link_layer);

अटल काष्ठा attribute *port_शेष_attrs[] = अणु
	&port_attr_state.attr,
	&port_attr_lid.attr,
	&port_attr_lid_mask_count.attr,
	&port_attr_sm_lid.attr,
	&port_attr_sm_sl.attr,
	&port_attr_cap_mask.attr,
	&port_attr_rate.attr,
	&port_attr_phys_state.attr,
	&port_attr_link_layer.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार prपूर्णांक_ndev(स्थिर काष्ठा ib_gid_attr *gid_attr, अक्षर *buf)
अणु
	काष्ठा net_device *ndev;
	पूर्णांक ret = -EINVAL;

	rcu_पढ़ो_lock();
	ndev = rcu_dereference(gid_attr->ndev);
	अगर (ndev)
		ret = sysfs_emit(buf, "%s\n", ndev->name);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार prपूर्णांक_gid_type(स्थिर काष्ठा ib_gid_attr *gid_attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n",
			  ib_cache_gid_type_str(gid_attr->gid_type));
पूर्ण

अटल sमाप_प्रकार _show_port_gid_attr(
	काष्ठा ib_port *p, काष्ठा port_attribute *attr, अक्षर *buf,
	sमाप_प्रकार (*prपूर्णांक)(स्थिर काष्ठा ib_gid_attr *gid_attr, अक्षर *buf))
अणु
	काष्ठा port_table_attribute *tab_attr =
		container_of(attr, काष्ठा port_table_attribute, attr);
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	sमाप_प्रकार ret;

	gid_attr = rdma_get_gid_attr(p->ibdev, p->port_num, tab_attr->index);
	अगर (IS_ERR(gid_attr))
		/* -EINVAL is वापसed क्रम user space compatibility reasons. */
		वापस -EINVAL;

	ret = prपूर्णांक(gid_attr, buf);
	rdma_put_gid_attr(gid_attr);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_port_gid(काष्ठा ib_port *p, काष्ठा port_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा port_table_attribute *tab_attr =
		container_of(attr, काष्ठा port_table_attribute, attr);
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	पूर्णांक len;

	gid_attr = rdma_get_gid_attr(p->ibdev, p->port_num, tab_attr->index);
	अगर (IS_ERR(gid_attr)) अणु
		स्थिर जोड़ ib_gid zgid = अणुपूर्ण;

		/* If पढ़ोing GID fails, it is likely due to GID entry being
		 * empty (invalid) or reserved GID in the table.  User space
		 * expects to पढ़ो GID table entries as दीर्घ as it given index
		 * is within GID table size.  Administrative/debugging tool
		 * fails to query rest of the GID entries अगर it hits error
		 * जबतक querying a GID of the given index.  To aव्योम user
		 * space throwing such error on fail to पढ़ो gid, वापस zero
		 * GID as beक्रमe. This मुख्यtains backward compatibility.
		 */
		वापस sysfs_emit(buf, "%pI6\n", zgid.raw);
	पूर्ण

	len = sysfs_emit(buf, "%pI6\n", gid_attr->gid.raw);
	rdma_put_gid_attr(gid_attr);
	वापस len;
पूर्ण

अटल sमाप_प्रकार show_port_gid_attr_ndev(काष्ठा ib_port *p,
				       काष्ठा port_attribute *attr, अक्षर *buf)
अणु
	वापस _show_port_gid_attr(p, attr, buf, prपूर्णांक_ndev);
पूर्ण

अटल sमाप_प्रकार show_port_gid_attr_gid_type(काष्ठा ib_port *p,
					   काष्ठा port_attribute *attr,
					   अक्षर *buf)
अणु
	वापस _show_port_gid_attr(p, attr, buf, prपूर्णांक_gid_type);
पूर्ण

अटल sमाप_प्रकार show_port_pkey(काष्ठा ib_port *p, काष्ठा port_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा port_table_attribute *tab_attr =
		container_of(attr, काष्ठा port_table_attribute, attr);
	u16 pkey;
	पूर्णांक ret;

	ret = ib_query_pkey(p->ibdev, p->port_num, tab_attr->index, &pkey);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "0x%04x\n", pkey);
पूर्ण

#घोषणा PORT_PMA_ATTR(_name, _counter, _width, _offset)			\
काष्ठा port_table_attribute port_pma_attr_##_name = अणु			\
	.attr  = __ATTR(_name, S_IRUGO, show_pma_counter, शून्य),	\
	.index = (_offset) | ((_width) << 16) | ((_counter) << 24),	\
	.attr_id = IB_PMA_PORT_COUNTERS,				\
पूर्ण

#घोषणा PORT_PMA_ATTR_EXT(_name, _width, _offset)			\
काष्ठा port_table_attribute port_pma_attr_ext_##_name = अणु		\
	.attr  = __ATTR(_name, S_IRUGO, show_pma_counter, शून्य),	\
	.index = (_offset) | ((_width) << 16),				\
	.attr_id = IB_PMA_PORT_COUNTERS_EXT,				\
पूर्ण

/*
 * Get a Perfmgmt MAD block of data.
 * Returns error code or the number of bytes retrieved.
 */
अटल पूर्णांक get_perf_mad(काष्ठा ib_device *dev, पूर्णांक port_num, __be16 attr,
		व्योम *data, पूर्णांक offset, माप_प्रकार size)
अणु
	काष्ठा ib_mad *in_mad;
	काष्ठा ib_mad *out_mad;
	माप_प्रकार mad_size = माप(*out_mad);
	u16 out_mad_pkey_index = 0;
	sमाप_प्रकार ret;

	अगर (!dev->ops.process_mad)
		वापस -ENOSYS;

	in_mad = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kzalloc(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	in_mad->mad_hdr.base_version  = 1;
	in_mad->mad_hdr.mgmt_class    = IB_MGMT_CLASS_PERF_MGMT;
	in_mad->mad_hdr.class_version = 1;
	in_mad->mad_hdr.method        = IB_MGMT_METHOD_GET;
	in_mad->mad_hdr.attr_id       = attr;

	अगर (attr != IB_PMA_CLASS_PORT_INFO)
		in_mad->data[41] = port_num;	/* PortSelect field */

	अगर ((dev->ops.process_mad(dev, IB_MAD_IGNORE_MKEY, port_num, शून्य, शून्य,
				  in_mad, out_mad, &mad_size,
				  &out_mad_pkey_index) &
	     (IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY)) !=
	    (IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	स_नकल(data, out_mad->data + offset, size);
	ret = size;
out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_pma_counter(काष्ठा ib_port *p, काष्ठा port_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा port_table_attribute *tab_attr =
		container_of(attr, काष्ठा port_table_attribute, attr);
	पूर्णांक offset = tab_attr->index & 0xffff;
	पूर्णांक width  = (tab_attr->index >> 16) & 0xff;
	पूर्णांक ret;
	u8 data[8];
	पूर्णांक len;

	ret = get_perf_mad(p->ibdev, p->port_num, tab_attr->attr_id, &data,
			40 + offset / 8, माप(data));
	अगर (ret < 0)
		वापस ret;

	चयन (width) अणु
	हाल 4:
		len = sysfs_emit(buf, "%u\n",
				 (*data >> (4 - (offset % 8))) & 0xf);
		अवरोध;
	हाल 8:
		len = sysfs_emit(buf, "%u\n", *data);
		अवरोध;
	हाल 16:
		len = sysfs_emit(buf, "%u\n", be16_to_cpup((__be16 *)data));
		अवरोध;
	हाल 32:
		len = sysfs_emit(buf, "%u\n", be32_to_cpup((__be32 *)data));
		अवरोध;
	हाल 64:
		len = sysfs_emit(buf, "%llu\n", be64_to_cpup((__be64 *)data));
		अवरोध;
	शेष:
		len = 0;
		अवरोध;
	पूर्ण

	वापस len;
पूर्ण

अटल PORT_PMA_ATTR(symbol_error		    ,  0, 16,  32);
अटल PORT_PMA_ATTR(link_error_recovery	    ,  1,  8,  48);
अटल PORT_PMA_ATTR(link_करोwned		    ,  2,  8,  56);
अटल PORT_PMA_ATTR(port_rcv_errors		    ,  3, 16,  64);
अटल PORT_PMA_ATTR(port_rcv_remote_physical_errors,  4, 16,  80);
अटल PORT_PMA_ATTR(port_rcv_चयन_relay_errors   ,  5, 16,  96);
अटल PORT_PMA_ATTR(port_xmit_discards		    ,  6, 16, 112);
अटल PORT_PMA_ATTR(port_xmit_स्थिरraपूर्णांक_errors    ,  7,  8, 128);
अटल PORT_PMA_ATTR(port_rcv_स्थिरraपूर्णांक_errors	    ,  8,  8, 136);
अटल PORT_PMA_ATTR(local_link_पूर्णांकegrity_errors    ,  9,  4, 152);
अटल PORT_PMA_ATTR(excessive_buffer_overrun_errors, 10,  4, 156);
अटल PORT_PMA_ATTR(VL15_dropped		    , 11, 16, 176);
अटल PORT_PMA_ATTR(port_xmit_data		    , 12, 32, 192);
अटल PORT_PMA_ATTR(port_rcv_data		    , 13, 32, 224);
अटल PORT_PMA_ATTR(port_xmit_packets		    , 14, 32, 256);
अटल PORT_PMA_ATTR(port_rcv_packets		    , 15, 32, 288);
अटल PORT_PMA_ATTR(port_xmit_रुको		    ,  0, 32, 320);

/*
 * Counters added by extended set
 */
अटल PORT_PMA_ATTR_EXT(port_xmit_data		    , 64,  64);
अटल PORT_PMA_ATTR_EXT(port_rcv_data		    , 64, 128);
अटल PORT_PMA_ATTR_EXT(port_xmit_packets	    , 64, 192);
अटल PORT_PMA_ATTR_EXT(port_rcv_packets	    , 64, 256);
अटल PORT_PMA_ATTR_EXT(unicast_xmit_packets	    , 64, 320);
अटल PORT_PMA_ATTR_EXT(unicast_rcv_packets	    , 64, 384);
अटल PORT_PMA_ATTR_EXT(multicast_xmit_packets	    , 64, 448);
अटल PORT_PMA_ATTR_EXT(multicast_rcv_packets	    , 64, 512);

अटल काष्ठा attribute *pma_attrs[] = अणु
	&port_pma_attr_symbol_error.attr.attr,
	&port_pma_attr_link_error_recovery.attr.attr,
	&port_pma_attr_link_करोwned.attr.attr,
	&port_pma_attr_port_rcv_errors.attr.attr,
	&port_pma_attr_port_rcv_remote_physical_errors.attr.attr,
	&port_pma_attr_port_rcv_चयन_relay_errors.attr.attr,
	&port_pma_attr_port_xmit_discards.attr.attr,
	&port_pma_attr_port_xmit_स्थिरraपूर्णांक_errors.attr.attr,
	&port_pma_attr_port_rcv_स्थिरraपूर्णांक_errors.attr.attr,
	&port_pma_attr_local_link_पूर्णांकegrity_errors.attr.attr,
	&port_pma_attr_excessive_buffer_overrun_errors.attr.attr,
	&port_pma_attr_VL15_dropped.attr.attr,
	&port_pma_attr_port_xmit_data.attr.attr,
	&port_pma_attr_port_rcv_data.attr.attr,
	&port_pma_attr_port_xmit_packets.attr.attr,
	&port_pma_attr_port_rcv_packets.attr.attr,
	&port_pma_attr_port_xmit_रुको.attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *pma_attrs_ext[] = अणु
	&port_pma_attr_symbol_error.attr.attr,
	&port_pma_attr_link_error_recovery.attr.attr,
	&port_pma_attr_link_करोwned.attr.attr,
	&port_pma_attr_port_rcv_errors.attr.attr,
	&port_pma_attr_port_rcv_remote_physical_errors.attr.attr,
	&port_pma_attr_port_rcv_चयन_relay_errors.attr.attr,
	&port_pma_attr_port_xmit_discards.attr.attr,
	&port_pma_attr_port_xmit_स्थिरraपूर्णांक_errors.attr.attr,
	&port_pma_attr_port_rcv_स्थिरraपूर्णांक_errors.attr.attr,
	&port_pma_attr_local_link_पूर्णांकegrity_errors.attr.attr,
	&port_pma_attr_excessive_buffer_overrun_errors.attr.attr,
	&port_pma_attr_VL15_dropped.attr.attr,
	&port_pma_attr_ext_port_xmit_data.attr.attr,
	&port_pma_attr_ext_port_rcv_data.attr.attr,
	&port_pma_attr_ext_port_xmit_packets.attr.attr,
	&port_pma_attr_port_xmit_रुको.attr.attr,
	&port_pma_attr_ext_port_rcv_packets.attr.attr,
	&port_pma_attr_ext_unicast_rcv_packets.attr.attr,
	&port_pma_attr_ext_unicast_xmit_packets.attr.attr,
	&port_pma_attr_ext_multicast_rcv_packets.attr.attr,
	&port_pma_attr_ext_multicast_xmit_packets.attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *pma_attrs_noietf[] = अणु
	&port_pma_attr_symbol_error.attr.attr,
	&port_pma_attr_link_error_recovery.attr.attr,
	&port_pma_attr_link_करोwned.attr.attr,
	&port_pma_attr_port_rcv_errors.attr.attr,
	&port_pma_attr_port_rcv_remote_physical_errors.attr.attr,
	&port_pma_attr_port_rcv_चयन_relay_errors.attr.attr,
	&port_pma_attr_port_xmit_discards.attr.attr,
	&port_pma_attr_port_xmit_स्थिरraपूर्णांक_errors.attr.attr,
	&port_pma_attr_port_rcv_स्थिरraपूर्णांक_errors.attr.attr,
	&port_pma_attr_local_link_पूर्णांकegrity_errors.attr.attr,
	&port_pma_attr_excessive_buffer_overrun_errors.attr.attr,
	&port_pma_attr_VL15_dropped.attr.attr,
	&port_pma_attr_ext_port_xmit_data.attr.attr,
	&port_pma_attr_ext_port_rcv_data.attr.attr,
	&port_pma_attr_ext_port_xmit_packets.attr.attr,
	&port_pma_attr_ext_port_rcv_packets.attr.attr,
	&port_pma_attr_port_xmit_रुको.attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pma_group = अणु
	.name  = "counters",
	.attrs  = pma_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group pma_group_ext = अणु
	.name  = "counters",
	.attrs  = pma_attrs_ext
पूर्ण;

अटल स्थिर काष्ठा attribute_group pma_group_noietf = अणु
	.name  = "counters",
	.attrs  = pma_attrs_noietf
पूर्ण;

अटल व्योम ib_port_release(काष्ठा kobject *kobj)
अणु
	काष्ठा ib_port *p = container_of(kobj, काष्ठा ib_port, kobj);
	काष्ठा attribute *a;
	पूर्णांक i;

	अगर (p->gid_group.attrs) अणु
		क्रम (i = 0; (a = p->gid_group.attrs[i]); ++i)
			kमुक्त(a);

		kमुक्त(p->gid_group.attrs);
	पूर्ण

	अगर (p->pkey_group) अणु
		अगर (p->pkey_group->attrs) अणु
			क्रम (i = 0; (a = p->pkey_group->attrs[i]); ++i)
				kमुक्त(a);

			kमुक्त(p->pkey_group->attrs);
		पूर्ण

		kमुक्त(p->pkey_group);
		p->pkey_group = शून्य;
	पूर्ण

	kमुक्त(p);
पूर्ण

अटल व्योम ib_port_gid_attr_release(काष्ठा kobject *kobj)
अणु
	काष्ठा gid_attr_group *g = container_of(kobj, काष्ठा gid_attr_group,
						kobj);
	काष्ठा attribute *a;
	पूर्णांक i;

	अगर (g->ndev.attrs) अणु
		क्रम (i = 0; (a = g->ndev.attrs[i]); ++i)
			kमुक्त(a);

		kमुक्त(g->ndev.attrs);
	पूर्ण

	अगर (g->type.attrs) अणु
		क्रम (i = 0; (a = g->type.attrs[i]); ++i)
			kमुक्त(a);

		kमुक्त(g->type.attrs);
	पूर्ण

	kमुक्त(g);
पूर्ण

अटल काष्ठा kobj_type port_type = अणु
	.release       = ib_port_release,
	.sysfs_ops     = &port_sysfs_ops,
	.शेष_attrs = port_शेष_attrs
पूर्ण;

अटल काष्ठा kobj_type gid_attr_type = अणु
	.sysfs_ops      = &gid_attr_sysfs_ops,
	.release        = ib_port_gid_attr_release
पूर्ण;

अटल काष्ठा attribute **
alloc_group_attrs(sमाप_प्रकार (*show)(काष्ठा ib_port *,
				  काष्ठा port_attribute *, अक्षर *buf),
		  पूर्णांक len)
अणु
	काष्ठा attribute **tab_attr;
	काष्ठा port_table_attribute *element;
	पूर्णांक i;

	tab_attr = kसुस्मृति(1 + len, माप(काष्ठा attribute *), GFP_KERNEL);
	अगर (!tab_attr)
		वापस शून्य;

	क्रम (i = 0; i < len; i++) अणु
		element = kzalloc(माप(काष्ठा port_table_attribute),
				  GFP_KERNEL);
		अगर (!element)
			जाओ err;

		अगर (snम_लिखो(element->name, माप(element->name),
			     "%d", i) >= माप(element->name)) अणु
			kमुक्त(element);
			जाओ err;
		पूर्ण

		element->attr.attr.name  = element->name;
		element->attr.attr.mode  = S_IRUGO;
		element->attr.show       = show;
		element->index		 = i;
		sysfs_attr_init(&element->attr.attr);

		tab_attr[i] = &element->attr.attr;
	पूर्ण

	वापस tab_attr;

err:
	जबतक (--i >= 0)
		kमुक्त(tab_attr[i]);
	kमुक्त(tab_attr);
	वापस शून्य;
पूर्ण

/*
 * Figure out which counter table to use depending on
 * the device capabilities.
 */
अटल स्थिर काष्ठा attribute_group *get_counter_table(काष्ठा ib_device *dev,
						       पूर्णांक port_num)
अणु
	काष्ठा ib_class_port_info cpi;

	अगर (get_perf_mad(dev, port_num, IB_PMA_CLASS_PORT_INFO,
				&cpi, 40, माप(cpi)) >= 0) अणु
		अगर (cpi.capability_mask & IB_PMA_CLASS_CAP_EXT_WIDTH)
			/* We have extended counters */
			वापस &pma_group_ext;

		अगर (cpi.capability_mask & IB_PMA_CLASS_CAP_EXT_WIDTH_NOIETF)
			/* But not the IETF ones */
			वापस &pma_group_noietf;
	पूर्ण

	/* Fall back to normal counters */
	वापस &pma_group;
पूर्ण

अटल पूर्णांक update_hw_stats(काष्ठा ib_device *dev, काष्ठा rdma_hw_stats *stats,
			   u32 port_num, पूर्णांक index)
अणु
	पूर्णांक ret;

	अगर (समय_is_after_eq_jअगरfies(stats->बारtamp + stats->lअगरespan))
		वापस 0;
	ret = dev->ops.get_hw_stats(dev, stats, port_num, index);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == stats->num_counters)
		stats->बारtamp = jअगरfies;

	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांक_hw_stat(काष्ठा ib_device *dev, पूर्णांक port_num,
			 काष्ठा rdma_hw_stats *stats, पूर्णांक index, अक्षर *buf)
अणु
	u64 v = rdma_counter_get_hwstat_value(dev, port_num, index);

	वापस sysfs_emit(buf, "%llu\n", stats->value[index] + v);
पूर्ण

अटल sमाप_प्रकार show_hw_stats(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ib_device *dev;
	काष्ठा ib_port *port;
	काष्ठा hw_stats_attribute *hsa;
	काष्ठा rdma_hw_stats *stats;
	पूर्णांक ret;

	hsa = container_of(attr, काष्ठा hw_stats_attribute, attr);
	अगर (!hsa->port_num) अणु
		dev = container_of((काष्ठा device *)kobj,
				   काष्ठा ib_device, dev);
		stats = dev->hw_stats;
	पूर्ण अन्यथा अणु
		port = container_of(kobj, काष्ठा ib_port, kobj);
		dev = port->ibdev;
		stats = port->hw_stats;
	पूर्ण
	mutex_lock(&stats->lock);
	ret = update_hw_stats(dev, stats, hsa->port_num, hsa->index);
	अगर (ret)
		जाओ unlock;
	ret = prपूर्णांक_hw_stat(dev, hsa->port_num, stats, hsa->index, buf);
unlock:
	mutex_unlock(&stats->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_stats_lअगरespan(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा hw_stats_attribute *hsa;
	काष्ठा rdma_hw_stats *stats;
	पूर्णांक msecs;

	hsa = container_of(attr, काष्ठा hw_stats_attribute, attr);
	अगर (!hsa->port_num) अणु
		काष्ठा ib_device *dev = container_of((काष्ठा device *)kobj,
						     काष्ठा ib_device, dev);

		stats = dev->hw_stats;
	पूर्ण अन्यथा अणु
		काष्ठा ib_port *p = container_of(kobj, काष्ठा ib_port, kobj);

		stats = p->hw_stats;
	पूर्ण

	mutex_lock(&stats->lock);
	msecs = jअगरfies_to_msecs(stats->lअगरespan);
	mutex_unlock(&stats->lock);

	वापस sysfs_emit(buf, "%d\n", msecs);
पूर्ण

अटल sमाप_प्रकार set_stats_lअगरespan(काष्ठा kobject *kobj,
				  काष्ठा attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hw_stats_attribute *hsa;
	काष्ठा rdma_hw_stats *stats;
	पूर्णांक msecs;
	पूर्णांक jअगरfies;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 10, &msecs);
	अगर (ret)
		वापस ret;
	अगर (msecs < 0 || msecs > 10000)
		वापस -EINVAL;
	jअगरfies = msecs_to_jअगरfies(msecs);
	hsa = container_of(attr, काष्ठा hw_stats_attribute, attr);
	अगर (!hsa->port_num) अणु
		काष्ठा ib_device *dev = container_of((काष्ठा device *)kobj,
						     काष्ठा ib_device, dev);

		stats = dev->hw_stats;
	पूर्ण अन्यथा अणु
		काष्ठा ib_port *p = container_of(kobj, काष्ठा ib_port, kobj);

		stats = p->hw_stats;
	पूर्ण

	mutex_lock(&stats->lock);
	stats->lअगरespan = jअगरfies;
	mutex_unlock(&stats->lock);

	वापस count;
पूर्ण

अटल व्योम मुक्त_hsag(काष्ठा kobject *kobj, काष्ठा attribute_group *attr_group)
अणु
	काष्ठा attribute **attr;

	sysfs_हटाओ_group(kobj, attr_group);

	क्रम (attr = attr_group->attrs; *attr; attr++)
		kमुक्त(*attr);
	kमुक्त(attr_group);
पूर्ण

अटल काष्ठा attribute *alloc_hsa(पूर्णांक index, u32 port_num, स्थिर अक्षर *name)
अणु
	काष्ठा hw_stats_attribute *hsa;

	hsa = kदो_स्मृति(माप(*hsa), GFP_KERNEL);
	अगर (!hsa)
		वापस शून्य;

	hsa->attr.name = (अक्षर *)name;
	hsa->attr.mode = S_IRUGO;
	hsa->show = show_hw_stats;
	hsa->store = शून्य;
	hsa->index = index;
	hsa->port_num = port_num;

	वापस &hsa->attr;
पूर्ण

अटल काष्ठा attribute *alloc_hsa_lअगरespan(अक्षर *name, u32 port_num)
अणु
	काष्ठा hw_stats_attribute *hsa;

	hsa = kदो_स्मृति(माप(*hsa), GFP_KERNEL);
	अगर (!hsa)
		वापस शून्य;

	hsa->attr.name = name;
	hsa->attr.mode = S_IWUSR | S_IRUGO;
	hsa->show = show_stats_lअगरespan;
	hsa->store = set_stats_lअगरespan;
	hsa->index = 0;
	hsa->port_num = port_num;

	वापस &hsa->attr;
पूर्ण

अटल व्योम setup_hw_stats(काष्ठा ib_device *device, काष्ठा ib_port *port,
			   u32 port_num)
अणु
	काष्ठा attribute_group *hsag;
	काष्ठा rdma_hw_stats *stats;
	पूर्णांक i, ret;

	stats = device->ops.alloc_hw_stats(device, port_num);

	अगर (!stats)
		वापस;

	अगर (!stats->names || stats->num_counters <= 0)
		जाओ err_मुक्त_stats;

	/*
	 * Two extra attribue elements here, one क्रम the lअगरespan entry and
	 * one to शून्य terminate the list क्रम the sysfs core code
	 */
	hsag = kzalloc(माप(*hsag) +
		       माप(व्योम *) * (stats->num_counters + 2),
		       GFP_KERNEL);
	अगर (!hsag)
		जाओ err_मुक्त_stats;

	ret = device->ops.get_hw_stats(device, stats, port_num,
				       stats->num_counters);
	अगर (ret != stats->num_counters)
		जाओ err_मुक्त_hsag;

	stats->बारtamp = jअगरfies;

	hsag->name = "hw_counters";
	hsag->attrs = (व्योम *)hsag + माप(*hsag);

	क्रम (i = 0; i < stats->num_counters; i++) अणु
		hsag->attrs[i] = alloc_hsa(i, port_num, stats->names[i]);
		अगर (!hsag->attrs[i])
			जाओ err;
		sysfs_attr_init(hsag->attrs[i]);
	पूर्ण

	mutex_init(&stats->lock);
	/* treat an error here as non-fatal */
	hsag->attrs[i] = alloc_hsa_lअगरespan("lifespan", port_num);
	अगर (hsag->attrs[i])
		sysfs_attr_init(hsag->attrs[i]);

	अगर (port) अणु
		काष्ठा kobject *kobj = &port->kobj;
		ret = sysfs_create_group(kobj, hsag);
		अगर (ret)
			जाओ err;
		port->hw_stats_ag = hsag;
		port->hw_stats = stats;
		अगर (device->port_data)
			device->port_data[port_num].hw_stats = stats;
	पूर्ण अन्यथा अणु
		काष्ठा kobject *kobj = &device->dev.kobj;
		ret = sysfs_create_group(kobj, hsag);
		अगर (ret)
			जाओ err;
		device->hw_stats_ag = hsag;
		device->hw_stats = stats;
	पूर्ण

	वापस;

err:
	क्रम (; i >= 0; i--)
		kमुक्त(hsag->attrs[i]);
err_मुक्त_hsag:
	kमुक्त(hsag);
err_मुक्त_stats:
	kमुक्त(stats);
पूर्ण

अटल पूर्णांक add_port(काष्ठा ib_core_device *coredev, पूर्णांक port_num)
अणु
	काष्ठा ib_device *device = rdma_device_to_ibdev(&coredev->dev);
	bool is_full_dev = &device->coredev == coredev;
	काष्ठा ib_port *p;
	काष्ठा ib_port_attr attr;
	पूर्णांक i;
	पूर्णांक ret;

	ret = ib_query_port(device, port_num, &attr);
	अगर (ret)
		वापस ret;

	p = kzalloc(माप *p, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->ibdev      = device;
	p->port_num   = port_num;

	ret = kobject_init_and_add(&p->kobj, &port_type,
				   coredev->ports_kobj,
				   "%d", port_num);
	अगर (ret)
		जाओ err_put;

	p->gid_attr_group = kzalloc(माप(*p->gid_attr_group), GFP_KERNEL);
	अगर (!p->gid_attr_group) अणु
		ret = -ENOMEM;
		जाओ err_put;
	पूर्ण

	p->gid_attr_group->port = p;
	ret = kobject_init_and_add(&p->gid_attr_group->kobj, &gid_attr_type,
				   &p->kobj, "gid_attrs");
	अगर (ret)
		जाओ err_put_gid_attrs;

	अगर (device->ops.process_mad && is_full_dev) अणु
		p->pma_table = get_counter_table(device, port_num);
		ret = sysfs_create_group(&p->kobj, p->pma_table);
		अगर (ret)
			जाओ err_put_gid_attrs;
	पूर्ण

	p->gid_group.name  = "gids";
	p->gid_group.attrs = alloc_group_attrs(show_port_gid, attr.gid_tbl_len);
	अगर (!p->gid_group.attrs) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_pma;
	पूर्ण

	ret = sysfs_create_group(&p->kobj, &p->gid_group);
	अगर (ret)
		जाओ err_मुक्त_gid;

	p->gid_attr_group->ndev.name = "ndevs";
	p->gid_attr_group->ndev.attrs = alloc_group_attrs(show_port_gid_attr_ndev,
							  attr.gid_tbl_len);
	अगर (!p->gid_attr_group->ndev.attrs) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_gid;
	पूर्ण

	ret = sysfs_create_group(&p->gid_attr_group->kobj,
				 &p->gid_attr_group->ndev);
	अगर (ret)
		जाओ err_मुक्त_gid_ndev;

	p->gid_attr_group->type.name = "types";
	p->gid_attr_group->type.attrs = alloc_group_attrs(show_port_gid_attr_gid_type,
							  attr.gid_tbl_len);
	अगर (!p->gid_attr_group->type.attrs) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_gid_ndev;
	पूर्ण

	ret = sysfs_create_group(&p->gid_attr_group->kobj,
				 &p->gid_attr_group->type);
	अगर (ret)
		जाओ err_मुक्त_gid_type;

	अगर (attr.pkey_tbl_len) अणु
		p->pkey_group = kzalloc(माप(*p->pkey_group), GFP_KERNEL);
		अगर (!p->pkey_group) अणु
			ret = -ENOMEM;
			जाओ err_हटाओ_gid_type;
		पूर्ण

		p->pkey_group->name  = "pkeys";
		p->pkey_group->attrs = alloc_group_attrs(show_port_pkey,
							 attr.pkey_tbl_len);
		अगर (!p->pkey_group->attrs) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_pkey_group;
		पूर्ण

		ret = sysfs_create_group(&p->kobj, p->pkey_group);
		अगर (ret)
			जाओ err_मुक्त_pkey;
	पूर्ण


	अगर (device->ops.init_port && is_full_dev) अणु
		ret = device->ops.init_port(device, port_num, &p->kobj);
		अगर (ret)
			जाओ err_हटाओ_pkey;
	पूर्ण

	/*
	 * If port == 0, it means hw_counters are per device and not per
	 * port, so holder should be device. Thereक्रमe skip per port conunter
	 * initialization.
	 */
	अगर (device->ops.alloc_hw_stats && port_num && is_full_dev)
		setup_hw_stats(device, p, port_num);

	list_add_tail(&p->kobj.entry, &coredev->port_list);

	kobject_uevent(&p->kobj, KOBJ_ADD);
	वापस 0;

err_हटाओ_pkey:
	अगर (p->pkey_group)
		sysfs_हटाओ_group(&p->kobj, p->pkey_group);

err_मुक्त_pkey:
	अगर (p->pkey_group) अणु
		क्रम (i = 0; i < attr.pkey_tbl_len; ++i)
			kमुक्त(p->pkey_group->attrs[i]);

		kमुक्त(p->pkey_group->attrs);
		p->pkey_group->attrs = शून्य;
	पूर्ण

err_मुक्त_pkey_group:
	kमुक्त(p->pkey_group);

err_हटाओ_gid_type:
	sysfs_हटाओ_group(&p->gid_attr_group->kobj,
			   &p->gid_attr_group->type);

err_मुक्त_gid_type:
	क्रम (i = 0; i < attr.gid_tbl_len; ++i)
		kमुक्त(p->gid_attr_group->type.attrs[i]);

	kमुक्त(p->gid_attr_group->type.attrs);
	p->gid_attr_group->type.attrs = शून्य;

err_हटाओ_gid_ndev:
	sysfs_हटाओ_group(&p->gid_attr_group->kobj,
			   &p->gid_attr_group->ndev);

err_मुक्त_gid_ndev:
	क्रम (i = 0; i < attr.gid_tbl_len; ++i)
		kमुक्त(p->gid_attr_group->ndev.attrs[i]);

	kमुक्त(p->gid_attr_group->ndev.attrs);
	p->gid_attr_group->ndev.attrs = शून्य;

err_हटाओ_gid:
	sysfs_हटाओ_group(&p->kobj, &p->gid_group);

err_मुक्त_gid:
	क्रम (i = 0; i < attr.gid_tbl_len; ++i)
		kमुक्त(p->gid_group.attrs[i]);

	kमुक्त(p->gid_group.attrs);
	p->gid_group.attrs = शून्य;

err_हटाओ_pma:
	अगर (p->pma_table)
		sysfs_हटाओ_group(&p->kobj, p->pma_table);

err_put_gid_attrs:
	kobject_put(&p->gid_attr_group->kobj);

err_put:
	kobject_put(&p->kobj);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *node_type_string(पूर्णांक node_type)
अणु
	चयन (node_type) अणु
	हाल RDMA_NODE_IB_CA:
		वापस "CA";
	हाल RDMA_NODE_IB_SWITCH:
		वापस "switch";
	हाल RDMA_NODE_IB_ROUTER:
		वापस "router";
	हाल RDMA_NODE_RNIC:
		वापस "RNIC";
	हाल RDMA_NODE_USNIC:
		वापस "usNIC";
	हाल RDMA_NODE_USNIC_UDP:
		वापस "usNIC UDP";
	हाल RDMA_NODE_UNSPECIFIED:
		वापस "unspecified";
	पूर्ण
	वापस "<unknown>";
पूर्ण

अटल sमाप_प्रकार node_type_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ib_device *dev = rdma_device_to_ibdev(device);

	वापस sysfs_emit(buf, "%d: %s\n", dev->node_type,
			  node_type_string(dev->node_type));
पूर्ण
अटल DEVICE_ATTR_RO(node_type);

अटल sमाप_प्रकार sys_image_guid_show(काष्ठा device *device,
				   काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा ib_device *dev = rdma_device_to_ibdev(device);
	__be16 *guid = (__be16 *)&dev->attrs.sys_image_guid;

	वापस sysfs_emit(buf, "%04x:%04x:%04x:%04x\n",
			  be16_to_cpu(guid[0]),
			  be16_to_cpu(guid[1]),
			  be16_to_cpu(guid[2]),
			  be16_to_cpu(guid[3]));
पूर्ण
अटल DEVICE_ATTR_RO(sys_image_guid);

अटल sमाप_प्रकार node_guid_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ib_device *dev = rdma_device_to_ibdev(device);
	__be16 *node_guid = (__be16 *)&dev->node_guid;

	वापस sysfs_emit(buf, "%04x:%04x:%04x:%04x\n",
			  be16_to_cpu(node_guid[0]),
			  be16_to_cpu(node_guid[1]),
			  be16_to_cpu(node_guid[2]),
			  be16_to_cpu(node_guid[3]));
पूर्ण
अटल DEVICE_ATTR_RO(node_guid);

अटल sमाप_प्रकार node_desc_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ib_device *dev = rdma_device_to_ibdev(device);

	वापस sysfs_emit(buf, "%.64s\n", dev->node_desc);
पूर्ण

अटल sमाप_प्रकार node_desc_store(काष्ठा device *device,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ib_device *dev = rdma_device_to_ibdev(device);
	काष्ठा ib_device_modअगरy desc = अणुपूर्ण;
	पूर्णांक ret;

	अगर (!dev->ops.modअगरy_device)
		वापस -EOPNOTSUPP;

	स_नकल(desc.node_desc, buf, min_t(पूर्णांक, count, IB_DEVICE_NODE_DESC_MAX));
	ret = ib_modअगरy_device(dev, IB_DEVICE_MODIFY_NODE_DESC, &desc);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(node_desc);

अटल sमाप_प्रकार fw_ver_show(काष्ठा device *device, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा ib_device *dev = rdma_device_to_ibdev(device);
	अक्षर version[IB_FW_VERSION_NAME_MAX] = अणुपूर्ण;

	ib_get_device_fw_str(dev, version);

	वापस sysfs_emit(buf, "%s\n", version);
पूर्ण
अटल DEVICE_ATTR_RO(fw_ver);

अटल काष्ठा attribute *ib_dev_attrs[] = अणु
	&dev_attr_node_type.attr,
	&dev_attr_node_guid.attr,
	&dev_attr_sys_image_guid.attr,
	&dev_attr_fw_ver.attr,
	&dev_attr_node_desc.attr,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group ib_dev_attr_group = अणु
	.attrs = ib_dev_attrs,
पूर्ण;

व्योम ib_मुक्त_port_attrs(काष्ठा ib_core_device *coredev)
अणु
	काष्ठा ib_device *device = rdma_device_to_ibdev(&coredev->dev);
	bool is_full_dev = &device->coredev == coredev;
	काष्ठा kobject *p, *t;

	list_क्रम_each_entry_safe(p, t, &coredev->port_list, entry) अणु
		काष्ठा ib_port *port = container_of(p, काष्ठा ib_port, kobj);

		list_del(&p->entry);
		अगर (port->hw_stats_ag)
			मुक्त_hsag(&port->kobj, port->hw_stats_ag);
		kमुक्त(port->hw_stats);
		अगर (device->port_data && is_full_dev)
			device->port_data[port->port_num].hw_stats = शून्य;

		अगर (port->pma_table)
			sysfs_हटाओ_group(p, port->pma_table);
		अगर (port->pkey_group)
			sysfs_हटाओ_group(p, port->pkey_group);
		sysfs_हटाओ_group(p, &port->gid_group);
		sysfs_हटाओ_group(&port->gid_attr_group->kobj,
				   &port->gid_attr_group->ndev);
		sysfs_हटाओ_group(&port->gid_attr_group->kobj,
				   &port->gid_attr_group->type);
		kobject_put(&port->gid_attr_group->kobj);
		kobject_put(p);
	पूर्ण

	kobject_put(coredev->ports_kobj);
पूर्ण

पूर्णांक ib_setup_port_attrs(काष्ठा ib_core_device *coredev)
अणु
	काष्ठा ib_device *device = rdma_device_to_ibdev(&coredev->dev);
	u32 port;
	पूर्णांक ret;

	coredev->ports_kobj = kobject_create_and_add("ports",
						     &coredev->dev.kobj);
	अगर (!coredev->ports_kobj)
		वापस -ENOMEM;

	rdma_क्रम_each_port (device, port) अणु
		ret = add_port(coredev, port);
		अगर (ret)
			जाओ err_put;
	पूर्ण

	वापस 0;

err_put:
	ib_मुक्त_port_attrs(coredev);
	वापस ret;
पूर्ण

पूर्णांक ib_device_रेजिस्टर_sysfs(काष्ठा ib_device *device)
अणु
	पूर्णांक ret;

	ret = ib_setup_port_attrs(&device->coredev);
	अगर (ret)
		वापस ret;

	अगर (device->ops.alloc_hw_stats)
		setup_hw_stats(device, शून्य, 0);

	वापस 0;
पूर्ण

व्योम ib_device_unरेजिस्टर_sysfs(काष्ठा ib_device *device)
अणु
	अगर (device->hw_stats_ag)
		मुक्त_hsag(&device->dev.kobj, device->hw_stats_ag);
	kमुक्त(device->hw_stats);

	ib_मुक्त_port_attrs(&device->coredev);
पूर्ण

/**
 * ib_port_रेजिस्टर_module_stat - add module counters under relevant port
 *  of IB device.
 *
 * @device: IB device to add counters
 * @port_num: valid port number
 * @kobj: poपूर्णांकer to the kobject to initialize
 * @ktype: poपूर्णांकer to the ktype क्रम this kobject.
 * @name: the name of the kobject
 */
पूर्णांक ib_port_रेजिस्टर_module_stat(काष्ठा ib_device *device, u32 port_num,
				 काष्ठा kobject *kobj, काष्ठा kobj_type *ktype,
				 स्थिर अक्षर *name)
अणु
	काष्ठा kobject *p, *t;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(p, t, &device->coredev.port_list, entry) अणु
		काष्ठा ib_port *port = container_of(p, काष्ठा ib_port, kobj);

		अगर (port->port_num != port_num)
			जारी;

		ret = kobject_init_and_add(kobj, ktype, &port->kobj, "%s",
					   name);
		अगर (ret) अणु
			kobject_put(kobj);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_port_रेजिस्टर_module_stat);

/**
 * ib_port_unरेजिस्टर_module_stat - release module counters
 * @kobj: poपूर्णांकer to the kobject to release
 */
व्योम ib_port_unरेजिस्टर_module_stat(काष्ठा kobject *kobj)
अणु
	kobject_put(kobj);
पूर्ण
EXPORT_SYMBOL(ib_port_unरेजिस्टर_module_stat);
