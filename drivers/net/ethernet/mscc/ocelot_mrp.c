<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2017, 2019 Microsemi Corporation
 * Copyright 2020-2021 NXP Semiconductors
 */

#समावेश <linux/अगर_bridge.h>
#समावेश <linux/mrp_bridge.h>
#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश <uapi/linux/mrp_bridge.h>
#समावेश "ocelot.h"
#समावेश "ocelot_vcap.h"

अटल स्थिर u8 mrp_test_dmac[] = अणु 0x01, 0x15, 0x4e, 0x00, 0x00, 0x01 पूर्ण;
अटल स्थिर u8 mrp_control_dmac[] = अणु 0x01, 0x15, 0x4e, 0x00, 0x00, 0x02 पूर्ण;

अटल पूर्णांक ocelot_mrp_find_partner_port(काष्ठा ocelot *ocelot,
					काष्ठा ocelot_port *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ocelot->num_phys_ports; ++i) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[i];

		अगर (!ocelot_port || p == ocelot_port)
			जारी;

		अगर (ocelot_port->mrp_ring_id == p->mrp_ring_id)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक ocelot_mrp_del_vcap(काष्ठा ocelot *ocelot, पूर्णांक id)
अणु
	काष्ठा ocelot_vcap_block *block_vcap_is2;
	काष्ठा ocelot_vcap_filter *filter;

	block_vcap_is2 = &ocelot->block[VCAP_IS2];
	filter = ocelot_vcap_block_find_filter_by_id(block_vcap_is2, id,
						     false);
	अगर (!filter)
		वापस 0;

	वापस ocelot_vcap_filter_del(ocelot, filter);
पूर्ण

अटल पूर्णांक ocelot_mrp_redirect_add_vcap(काष्ठा ocelot *ocelot, पूर्णांक src_port,
					पूर्णांक dst_port)
अणु
	स्थिर u8 mrp_test_mask[] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;
	काष्ठा ocelot_vcap_filter *filter;
	पूर्णांक err;

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	filter->key_type = OCELOT_VCAP_KEY_ETYPE;
	filter->prio = 1;
	filter->id.cookie = src_port;
	filter->id.tc_offload = false;
	filter->block_id = VCAP_IS2;
	filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
	filter->ingress_port_mask = BIT(src_port);
	ether_addr_copy(filter->key.etype.dmac.value, mrp_test_dmac);
	ether_addr_copy(filter->key.etype.dmac.mask, mrp_test_mask);
	filter->action.mask_mode = OCELOT_MASK_MODE_REसूचीECT;
	filter->action.port_mask = BIT(dst_port);

	err = ocelot_vcap_filter_add(ocelot, filter, शून्य);
	अगर (err)
		kमुक्त(filter);

	वापस err;
पूर्ण

अटल पूर्णांक ocelot_mrp_copy_add_vcap(काष्ठा ocelot *ocelot, पूर्णांक port,
				    पूर्णांक prio, अचिन्हित दीर्घ cookie)
अणु
	स्थिर u8 mrp_mask[] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 पूर्ण;
	काष्ठा ocelot_vcap_filter *filter;
	पूर्णांक err;

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	filter->key_type = OCELOT_VCAP_KEY_ETYPE;
	filter->prio = prio;
	filter->id.cookie = cookie;
	filter->id.tc_offload = false;
	filter->block_id = VCAP_IS2;
	filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
	filter->ingress_port_mask = BIT(port);
	/* Here is possible to use control or test dmac because the mask
	 * करोesn't cover the LSB
	 */
	ether_addr_copy(filter->key.etype.dmac.value, mrp_test_dmac);
	ether_addr_copy(filter->key.etype.dmac.mask, mrp_mask);
	filter->action.mask_mode = OCELOT_MASK_MODE_PERMIT_DENY;
	filter->action.port_mask = 0x0;
	filter->action.cpu_copy_ena = true;
	filter->action.cpu_qu_num = OCELOT_MRP_CPUQ;

	err = ocelot_vcap_filter_add(ocelot, filter, शून्य);
	अगर (err)
		kमुक्त(filter);

	वापस err;
पूर्ण

अटल व्योम ocelot_mrp_save_mac(काष्ठा ocelot *ocelot,
				काष्ठा ocelot_port *port)
अणु
	ocelot_mact_learn(ocelot, PGID_BLACKHOLE, mrp_test_dmac,
			  port->pvid_vlan.vid, ENTRYTYPE_LOCKED);
	ocelot_mact_learn(ocelot, PGID_BLACKHOLE, mrp_control_dmac,
			  port->pvid_vlan.vid, ENTRYTYPE_LOCKED);
पूर्ण

अटल व्योम ocelot_mrp_del_mac(काष्ठा ocelot *ocelot,
			       काष्ठा ocelot_port *port)
अणु
	ocelot_mact_क्रमget(ocelot, mrp_test_dmac, port->pvid_vlan.vid);
	ocelot_mact_क्रमget(ocelot, mrp_control_dmac, port->pvid_vlan.vid);
पूर्ण

पूर्णांक ocelot_mrp_add(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	काष्ठा ocelot_port_निजी *priv;
	काष्ठा net_device *dev;

	अगर (!ocelot_port)
		वापस -EOPNOTSUPP;

	priv = container_of(ocelot_port, काष्ठा ocelot_port_निजी, port);
	dev = priv->dev;

	अगर (mrp->p_port != dev && mrp->s_port != dev)
		वापस 0;

	ocelot_port->mrp_ring_id = mrp->ring_id;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_mrp_add);

पूर्णांक ocelot_mrp_del(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	अगर (!ocelot_port)
		वापस -EOPNOTSUPP;

	अगर (ocelot_port->mrp_ring_id != mrp->ring_id)
		वापस 0;

	ocelot_port->mrp_ring_id = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_mrp_del);

पूर्णांक ocelot_mrp_add_ring_role(काष्ठा ocelot *ocelot, पूर्णांक port,
			     स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	पूर्णांक dst_port;
	पूर्णांक err;

	अगर (!ocelot_port)
		वापस -EOPNOTSUPP;

	अगर (mrp->ring_role != BR_MRP_RING_ROLE_MRC && !mrp->sw_backup)
		वापस -EOPNOTSUPP;

	अगर (ocelot_port->mrp_ring_id != mrp->ring_id)
		वापस 0;

	ocelot_mrp_save_mac(ocelot, ocelot_port);

	अगर (mrp->ring_role != BR_MRP_RING_ROLE_MRC)
		वापस ocelot_mrp_copy_add_vcap(ocelot, port, 1, port);

	dst_port = ocelot_mrp_find_partner_port(ocelot, ocelot_port);
	अगर (dst_port == -1)
		वापस -EINVAL;

	err = ocelot_mrp_redirect_add_vcap(ocelot, port, dst_port);
	अगर (err)
		वापस err;

	err = ocelot_mrp_copy_add_vcap(ocelot, port, 2,
				       port + ocelot->num_phys_ports);
	अगर (err) अणु
		ocelot_mrp_del_vcap(ocelot, port);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_mrp_add_ring_role);

पूर्णांक ocelot_mrp_del_ring_role(काष्ठा ocelot *ocelot, पूर्णांक port,
			     स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	पूर्णांक i;

	अगर (!ocelot_port)
		वापस -EOPNOTSUPP;

	अगर (mrp->ring_role != BR_MRP_RING_ROLE_MRC && !mrp->sw_backup)
		वापस -EOPNOTSUPP;

	अगर (ocelot_port->mrp_ring_id != mrp->ring_id)
		वापस 0;

	ocelot_mrp_del_vcap(ocelot, port);
	ocelot_mrp_del_vcap(ocelot, port + ocelot->num_phys_ports);

	क्रम (i = 0; i < ocelot->num_phys_ports; ++i) अणु
		ocelot_port = ocelot->ports[i];

		अगर (!ocelot_port)
			जारी;

		अगर (ocelot_port->mrp_ring_id != 0)
			जाओ out;
	पूर्ण

	ocelot_mrp_del_mac(ocelot, ocelot->ports[port]);
out:
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_mrp_del_ring_role);
