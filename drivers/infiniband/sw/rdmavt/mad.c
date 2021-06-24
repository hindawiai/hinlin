<शैली गुरु>
/*
 * Copyright(c) 2016 Intel Corporation.
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

#समावेश <rdma/ib_mad.h>
#समावेश "mad.h"
#समावेश "vt.h"

/**
 * rvt_process_mad - process an incoming MAD packet
 * @ibdev: the infiniband device this packet came in on
 * @mad_flags: MAD flags
 * @port_num: the port number this packet came in on, 1 based from ib core
 * @in_wc: the work completion entry क्रम this packet
 * @in_grh: the global route header क्रम this packet
 * @in: the incoming MAD
 * @in_mad_size: size of the incoming MAD reply
 * @out: any outgoing MAD reply
 * @out_mad_size: size of the outgoing MAD reply
 * @out_mad_pkey_index: unused
 *
 * Note that the verbs framework has alपढ़ोy करोne the MAD sanity checks,
 * and hop count/poपूर्णांकer updating क्रम IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE
 * MADs.
 *
 * This is called by the ib_mad module.
 *
 * Return: IB_MAD_RESULT_SUCCESS or error
 */
पूर्णांक rvt_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
		    स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		    स्थिर काष्ठा ib_mad_hdr *in, माप_प्रकार in_mad_size,
		    काष्ठा ib_mad_hdr *out, माप_प्रकार *out_mad_size,
		    u16 *out_mad_pkey_index)
अणु
	/*
	 * MAD processing is quite dअगरferent between hfi1 and qib. Thereक्रमe
	 * this is expected to be provided by the driver. Other drivers in the
	 * future may choose to implement this but it should not be made पूर्णांकo a
	 * requirement.
	 */
	वापस IB_MAD_RESULT_FAILURE;
पूर्ण

अटल व्योम rvt_send_mad_handler(काष्ठा ib_mad_agent *agent,
				 काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	ib_मुक्त_send_mad(mad_send_wc->send_buf);
पूर्ण

/**
 * rvt_create_mad_agents - create mad agents
 * @rdi: rvt dev काष्ठा
 *
 * If driver needs to be notअगरied of mad agent creation then call back
 *
 * Return 0 on success
 */
पूर्णांक rvt_create_mad_agents(काष्ठा rvt_dev_info *rdi)
अणु
	काष्ठा ib_mad_agent *agent;
	काष्ठा rvt_ibport *rvp;
	पूर्णांक p;
	पूर्णांक ret;

	क्रम (p = 0; p < rdi->dparms.nports; p++) अणु
		rvp = rdi->ports[p];
		agent = ib_रेजिस्टर_mad_agent(&rdi->ibdev, p + 1,
					      IB_QPT_SMI,
					      शून्य, 0, rvt_send_mad_handler,
					      शून्य, शून्य, 0);
		अगर (IS_ERR(agent)) अणु
			ret = PTR_ERR(agent);
			जाओ err;
		पूर्ण

		rvp->send_agent = agent;

		अगर (rdi->driver_f.notअगरy_create_mad_agent)
			rdi->driver_f.notअगरy_create_mad_agent(rdi, p);
	पूर्ण

	वापस 0;

err:
	क्रम (p = 0; p < rdi->dparms.nports; p++) अणु
		rvp = rdi->ports[p];
		अगर (rvp->send_agent) अणु
			agent = rvp->send_agent;
			rvp->send_agent = शून्य;
			ib_unरेजिस्टर_mad_agent(agent);
			अगर (rdi->driver_f.notअगरy_मुक्त_mad_agent)
				rdi->driver_f.notअगरy_मुक्त_mad_agent(rdi, p);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * rvt_मुक्त_mad_agents - मुक्त up mad agents
 * @rdi: rvt dev काष्ठा
 *
 * If driver needs notअगरication of mad agent removal make the call back
 */
व्योम rvt_मुक्त_mad_agents(काष्ठा rvt_dev_info *rdi)
अणु
	काष्ठा ib_mad_agent *agent;
	काष्ठा rvt_ibport *rvp;
	पूर्णांक p;

	क्रम (p = 0; p < rdi->dparms.nports; p++) अणु
		rvp = rdi->ports[p];
		अगर (rvp->send_agent) अणु
			agent = rvp->send_agent;
			rvp->send_agent = शून्य;
			ib_unरेजिस्टर_mad_agent(agent);
		पूर्ण
		अगर (rvp->sm_ah) अणु
			rdma_destroy_ah(&rvp->sm_ah->ibah,
					RDMA_DESTROY_AH_SLEEPABLE);
			rvp->sm_ah = शून्य;
		पूर्ण

		अगर (rdi->driver_f.notअगरy_मुक्त_mad_agent)
			rdi->driver_f.notअगरy_मुक्त_mad_agent(rdi, p);
	पूर्ण
पूर्ण

