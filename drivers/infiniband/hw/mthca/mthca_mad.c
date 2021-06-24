<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_smi.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"

क्रमागत अणु
	MTHCA_VENDOR_CLASS1 = 0x9,
	MTHCA_VENDOR_CLASS2 = 0xa
पूर्ण;

अटल पूर्णांक mthca_update_rate(काष्ठा mthca_dev *dev, u8 port_num)
अणु
	काष्ठा ib_port_attr *tprops = शून्य;
	पूर्णांक                  ret;

	tprops = kदो_स्मृति(माप *tprops, GFP_KERNEL);
	अगर (!tprops)
		वापस -ENOMEM;

	ret = ib_query_port(&dev->ib_dev, port_num, tprops);
	अगर (ret) अणु
		dev_warn(&dev->ib_dev.dev,
			 "ib_query_port failed (%d) forport %d\n", ret,
			 port_num);
		जाओ out;
	पूर्ण

	dev->rate[port_num - 1] = tprops->active_speed *
				  ib_width_क्रमागत_to_पूर्णांक(tprops->active_width);

out:
	kमुक्त(tprops);
	वापस ret;
पूर्ण

अटल व्योम update_sm_ah(काष्ठा mthca_dev *dev,
			 u8 port_num, u16 lid, u8 sl)
अणु
	काष्ठा ib_ah *new_ah;
	काष्ठा rdma_ah_attr ah_attr;
	अचिन्हित दीर्घ flags;

	अगर (!dev->send_agent[port_num - 1][0])
		वापस;

	स_रखो(&ah_attr, 0, माप ah_attr);
	ah_attr.type = rdma_ah_find_type(&dev->ib_dev, port_num);
	rdma_ah_set_dlid(&ah_attr, lid);
	rdma_ah_set_sl(&ah_attr, sl);
	rdma_ah_set_port_num(&ah_attr, port_num);

	new_ah = rdma_create_ah(dev->send_agent[port_num - 1][0]->qp->pd,
				&ah_attr, 0);
	अगर (IS_ERR(new_ah))
		वापस;

	spin_lock_irqsave(&dev->sm_lock, flags);
	अगर (dev->sm_ah[port_num - 1])
		rdma_destroy_ah(dev->sm_ah[port_num - 1], 0);
	dev->sm_ah[port_num - 1] = new_ah;
	spin_unlock_irqrestore(&dev->sm_lock, flags);
पूर्ण

/*
 * Snoop SM MADs क्रम port info and P_Key table sets, so we can
 * synthesize LID change and P_Key change events.
 */
अटल व्योम smp_snoop(काष्ठा ib_device *ibdev,
		      u8 port_num,
		      स्थिर काष्ठा ib_mad *mad,
		      u16 prev_lid)
अणु
	काष्ठा ib_event event;

	अगर ((mad->mad_hdr.mgmt_class  == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     mad->mad_hdr.mgmt_class  == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) &&
	    mad->mad_hdr.method     == IB_MGMT_METHOD_SET) अणु
		अगर (mad->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO) अणु
			काष्ठा ib_port_info *pinfo =
				(काष्ठा ib_port_info *) ((काष्ठा ib_smp *) mad)->data;
			u16 lid = be16_to_cpu(pinfo->lid);

			mthca_update_rate(to_mdev(ibdev), port_num);
			update_sm_ah(to_mdev(ibdev), port_num,
				     be16_to_cpu(pinfo->sm_lid),
				     pinfo->neighbormtu_mastersmsl & 0xf);

			event.device           = ibdev;
			event.element.port_num = port_num;

			अगर (pinfo->clientrereg_resv_subnetto & 0x80) अणु
				event.event    = IB_EVENT_CLIENT_REREGISTER;
				ib_dispatch_event(&event);
			पूर्ण

			अगर (prev_lid != lid) अणु
				event.event    = IB_EVENT_LID_CHANGE;
				ib_dispatch_event(&event);
			पूर्ण
		पूर्ण

		अगर (mad->mad_hdr.attr_id == IB_SMP_ATTR_PKEY_TABLE) अणु
			event.device           = ibdev;
			event.event            = IB_EVENT_PKEY_CHANGE;
			event.element.port_num = port_num;
			ib_dispatch_event(&event);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम node_desc_override(काष्ठा ib_device *dev,
			       काष्ठा ib_mad *mad)
अणु
	अगर ((mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) &&
	    mad->mad_hdr.method == IB_MGMT_METHOD_GET_RESP &&
	    mad->mad_hdr.attr_id == IB_SMP_ATTR_NODE_DESC) अणु
		mutex_lock(&to_mdev(dev)->cap_mask_mutex);
		स_नकल(((काष्ठा ib_smp *) mad)->data, dev->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		mutex_unlock(&to_mdev(dev)->cap_mask_mutex);
	पूर्ण
पूर्ण

अटल व्योम क्रमward_trap(काष्ठा mthca_dev *dev,
			 u32 port_num,
			 स्थिर काष्ठा ib_mad *mad)
अणु
	पूर्णांक qpn = mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_SUBN_LID_ROUTED;
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा ib_mad_agent *agent = dev->send_agent[port_num - 1][qpn];
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (agent) अणु
		send_buf = ib_create_send_mad(agent, qpn, 0, 0, IB_MGMT_MAD_HDR,
					      IB_MGMT_MAD_DATA, GFP_ATOMIC,
					      IB_MGMT_BASE_VERSION);
		अगर (IS_ERR(send_buf))
			वापस;
		/*
		 * We rely here on the fact that MLX QPs करोn't use the
		 * address handle after the send is posted (this is
		 * wrong following the IB spec strictly, but we know
		 * it's OK क्रम our devices).
		 */
		spin_lock_irqsave(&dev->sm_lock, flags);
		स_नकल(send_buf->mad, mad, माप *mad);
		अगर ((send_buf->ah = dev->sm_ah[port_num - 1]))
			ret = ib_post_send_mad(send_buf, शून्य);
		अन्यथा
			ret = -EINVAL;
		spin_unlock_irqrestore(&dev->sm_lock, flags);

		अगर (ret)
			ib_मुक्त_send_mad(send_buf);
	पूर्ण
पूर्ण

पूर्णांक mthca_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
		      स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		      स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
		      माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index)
अणु
	पूर्णांक err;
	u16 slid = in_wc ? ib_lid_cpu16(in_wc->slid) : be16_to_cpu(IB_LID_PERMISSIVE);
	u16 prev_lid = 0;
	काष्ठा ib_port_attr pattr;

	/* Forward locally generated traps to the SM */
	अगर (in->mad_hdr.method == IB_MGMT_METHOD_TRAP && !slid) अणु
		क्रमward_trap(to_mdev(ibdev), port_num, in);
		वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
	पूर्ण

	/*
	 * Only handle SM माला_लो, sets and trap represses क्रम SM class
	 *
	 * Only handle PMA and Mellanox venकरोr-specअगरic class माला_लो and
	 * sets क्रम other classes.
	 */
	अगर (in->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	    in->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
		अगर (in->mad_hdr.method != IB_MGMT_METHOD_GET &&
		    in->mad_hdr.method != IB_MGMT_METHOD_SET &&
		    in->mad_hdr.method != IB_MGMT_METHOD_TRAP_REPRESS)
			वापस IB_MAD_RESULT_SUCCESS;

		/*
		 * Don't process SMInfo queries or venकरोr-specअगरic
		 * MADs -- the SMA can't handle them.
		 */
		अगर (in->mad_hdr.attr_id == IB_SMP_ATTR_SM_INFO ||
		    ((in->mad_hdr.attr_id & IB_SMP_ATTR_VENDOR_MASK) ==
		     IB_SMP_ATTR_VENDOR_MASK))
			वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण अन्यथा अगर (in->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT ||
		   in->mad_hdr.mgmt_class == MTHCA_VENDOR_CLASS1     ||
		   in->mad_hdr.mgmt_class == MTHCA_VENDOR_CLASS2) अणु
		अगर (in->mad_hdr.method != IB_MGMT_METHOD_GET &&
		    in->mad_hdr.method != IB_MGMT_METHOD_SET)
			वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण अन्यथा
		वापस IB_MAD_RESULT_SUCCESS;
	अगर ((in->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     in->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) &&
	    in->mad_hdr.method == IB_MGMT_METHOD_SET &&
	    in->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO &&
	    !ib_query_port(ibdev, port_num, &pattr))
		prev_lid = ib_lid_cpu16(pattr.lid);

	err = mthca_MAD_IFC(to_mdev(ibdev), mad_flags & IB_MAD_IGNORE_MKEY,
			    mad_flags & IB_MAD_IGNORE_BKEY, port_num, in_wc,
			    in_grh, in, out);
	अगर (err == -EBADMSG)
		वापस IB_MAD_RESULT_SUCCESS;
	अन्यथा अगर (err) अणु
		mthca_err(to_mdev(ibdev), "MAD_IFC returned %d\n", err);
		वापस IB_MAD_RESULT_FAILURE;
	पूर्ण

	अगर (!out->mad_hdr.status) अणु
		smp_snoop(ibdev, port_num, in, prev_lid);
		node_desc_override(ibdev, out);
	पूर्ण

	/* set वापस bit in status of directed route responses */
	अगर (in->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		out->mad_hdr.status |= cpu_to_be16(1 << 15);

	अगर (in->mad_hdr.method == IB_MGMT_METHOD_TRAP_REPRESS)
		/* no response क्रम trap repress */
		वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;

	वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
पूर्ण

अटल व्योम send_handler(काष्ठा ib_mad_agent *agent,
			 काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	ib_मुक्त_send_mad(mad_send_wc->send_buf);
पूर्ण

पूर्णांक mthca_create_agents(काष्ठा mthca_dev *dev)
अणु
	काष्ठा ib_mad_agent *agent;
	पूर्णांक p, q;
	पूर्णांक ret;

	spin_lock_init(&dev->sm_lock);

	क्रम (p = 0; p < dev->limits.num_ports; ++p)
		क्रम (q = 0; q <= 1; ++q) अणु
			agent = ib_रेजिस्टर_mad_agent(&dev->ib_dev, p + 1,
						      q ? IB_QPT_GSI : IB_QPT_SMI,
						      शून्य, 0, send_handler,
						      शून्य, शून्य, 0);
			अगर (IS_ERR(agent)) अणु
				ret = PTR_ERR(agent);
				जाओ err;
			पूर्ण
			dev->send_agent[p][q] = agent;
		पूर्ण


	क्रम (p = 1; p <= dev->limits.num_ports; ++p) अणु
		ret = mthca_update_rate(dev, p);
		अगर (ret) अणु
			mthca_err(dev, "Failed to obtain port %d rate."
				  " aborting.\n", p);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	क्रम (p = 0; p < dev->limits.num_ports; ++p)
		क्रम (q = 0; q <= 1; ++q)
			अगर (dev->send_agent[p][q])
				ib_unरेजिस्टर_mad_agent(dev->send_agent[p][q]);

	वापस ret;
पूर्ण

व्योम mthca_मुक्त_agents(काष्ठा mthca_dev *dev)
अणु
	काष्ठा ib_mad_agent *agent;
	पूर्णांक p, q;

	क्रम (p = 0; p < dev->limits.num_ports; ++p) अणु
		क्रम (q = 0; q <= 1; ++q) अणु
			agent = dev->send_agent[p][q];
			dev->send_agent[p][q] = शून्य;
			ib_unरेजिस्टर_mad_agent(agent);
		पूर्ण

		अगर (dev->sm_ah[p])
			rdma_destroy_ah(dev->sm_ah[p],
					RDMA_DESTROY_AH_SLEEPABLE);
	पूर्ण
पूर्ण
