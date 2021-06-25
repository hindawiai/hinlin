<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004, 2005 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004, 2005 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004, 2005 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004-2007 Voltaire Corporation.  All rights reserved.
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
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "agent.h"
#समावेश "smi.h"
#समावेश "mad_priv.h"

#घोषणा SPFX "ib_agent: "

काष्ठा ib_agent_port_निजी अणु
	काष्ठा list_head port_list;
	काष्ठा ib_mad_agent *agent[2];
पूर्ण;

अटल DEFINE_SPINLOCK(ib_agent_port_list_lock);
अटल LIST_HEAD(ib_agent_port_list);

अटल काष्ठा ib_agent_port_निजी *
__ib_get_agent_port(स्थिर काष्ठा ib_device *device, पूर्णांक port_num)
अणु
	काष्ठा ib_agent_port_निजी *entry;

	list_क्रम_each_entry(entry, &ib_agent_port_list, port_list) अणु
		अगर (entry->agent[1]->device == device &&
		    entry->agent[1]->port_num == port_num)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा ib_agent_port_निजी *
ib_get_agent_port(स्थिर काष्ठा ib_device *device, पूर्णांक port_num)
अणु
	काष्ठा ib_agent_port_निजी *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ib_agent_port_list_lock, flags);
	entry = __ib_get_agent_port(device, port_num);
	spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);
	वापस entry;
पूर्ण

व्योम agent_send_response(स्थिर काष्ठा ib_mad_hdr *mad_hdr, स्थिर काष्ठा ib_grh *grh,
			 स्थिर काष्ठा ib_wc *wc, स्थिर काष्ठा ib_device *device,
			 पूर्णांक port_num, पूर्णांक qpn, माप_प्रकार resp_mad_len, bool opa)
अणु
	काष्ठा ib_agent_port_निजी *port_priv;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा ib_ah *ah;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;

	अगर (rdma_cap_ib_चयन(device))
		port_priv = ib_get_agent_port(device, 0);
	अन्यथा
		port_priv = ib_get_agent_port(device, port_num);

	अगर (!port_priv) अणु
		dev_err(&device->dev, "Unable to find port agent\n");
		वापस;
	पूर्ण

	agent = port_priv->agent[qpn];
	ah = ib_create_ah_from_wc(agent->qp->pd, wc, grh, port_num);
	अगर (IS_ERR(ah)) अणु
		dev_err(&device->dev, "ib_create_ah_from_wc error %ld\n",
			PTR_ERR(ah));
		वापस;
	पूर्ण

	अगर (opa && mad_hdr->base_version != OPA_MGMT_BASE_VERSION)
		resp_mad_len = IB_MGMT_MAD_SIZE;

	send_buf = ib_create_send_mad(agent, wc->src_qp, wc->pkey_index, 0,
				      IB_MGMT_MAD_HDR,
				      resp_mad_len - IB_MGMT_MAD_HDR,
				      GFP_KERNEL,
				      mad_hdr->base_version);
	अगर (IS_ERR(send_buf)) अणु
		dev_err(&device->dev, "ib_create_send_mad error\n");
		जाओ err1;
	पूर्ण

	स_नकल(send_buf->mad, mad_hdr, resp_mad_len);
	send_buf->ah = ah;

	अगर (rdma_cap_ib_चयन(device)) अणु
		mad_send_wr = container_of(send_buf,
					   काष्ठा ib_mad_send_wr_निजी,
					   send_buf);
		mad_send_wr->send_wr.port_num = port_num;
	पूर्ण

	अगर (ib_post_send_mad(send_buf, शून्य)) अणु
		dev_err(&device->dev, "ib_post_send_mad error\n");
		जाओ err2;
	पूर्ण
	वापस;
err2:
	ib_मुक्त_send_mad(send_buf);
err1:
	rdma_destroy_ah(ah, RDMA_DESTROY_AH_SLEEPABLE);
पूर्ण

अटल व्योम agent_send_handler(काष्ठा ib_mad_agent *mad_agent,
			       काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	rdma_destroy_ah(mad_send_wc->send_buf->ah, RDMA_DESTROY_AH_SLEEPABLE);
	ib_मुक्त_send_mad(mad_send_wc->send_buf);
पूर्ण

पूर्णांक ib_agent_port_खोलो(काष्ठा ib_device *device, पूर्णांक port_num)
अणु
	काष्ठा ib_agent_port_निजी *port_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Create new device info */
	port_priv = kzalloc(माप *port_priv, GFP_KERNEL);
	अगर (!port_priv) अणु
		ret = -ENOMEM;
		जाओ error1;
	पूर्ण

	अगर (rdma_cap_ib_smi(device, port_num)) अणु
		/* Obtain send only MAD agent क्रम SMI QP */
		port_priv->agent[0] = ib_रेजिस्टर_mad_agent(device, port_num,
							    IB_QPT_SMI, शून्य, 0,
							    &agent_send_handler,
							    शून्य, शून्य, 0);
		अगर (IS_ERR(port_priv->agent[0])) अणु
			ret = PTR_ERR(port_priv->agent[0]);
			जाओ error2;
		पूर्ण
	पूर्ण

	/* Obtain send only MAD agent क्रम GSI QP */
	port_priv->agent[1] = ib_रेजिस्टर_mad_agent(device, port_num,
						    IB_QPT_GSI, शून्य, 0,
						    &agent_send_handler,
						    शून्य, शून्य, 0);
	अगर (IS_ERR(port_priv->agent[1])) अणु
		ret = PTR_ERR(port_priv->agent[1]);
		जाओ error3;
	पूर्ण

	spin_lock_irqsave(&ib_agent_port_list_lock, flags);
	list_add_tail(&port_priv->port_list, &ib_agent_port_list);
	spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);

	वापस 0;

error3:
	अगर (port_priv->agent[0])
		ib_unरेजिस्टर_mad_agent(port_priv->agent[0]);
error2:
	kमुक्त(port_priv);
error1:
	वापस ret;
पूर्ण

पूर्णांक ib_agent_port_बंद(काष्ठा ib_device *device, पूर्णांक port_num)
अणु
	काष्ठा ib_agent_port_निजी *port_priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ib_agent_port_list_lock, flags);
	port_priv = __ib_get_agent_port(device, port_num);
	अगर (port_priv == शून्य) अणु
		spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);
		dev_err(&device->dev, "Port %d not found\n", port_num);
		वापस -ENODEV;
	पूर्ण
	list_del(&port_priv->port_list);
	spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);

	ib_unरेजिस्टर_mad_agent(port_priv->agent[1]);
	अगर (port_priv->agent[0])
		ib_unरेजिस्टर_mad_agent(port_priv->agent[0]);

	kमुक्त(port_priv);
	वापस 0;
पूर्ण
