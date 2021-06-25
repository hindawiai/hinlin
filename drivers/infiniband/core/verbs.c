<शैली गुरु>
/*
 * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <net/addrconf.h>
#समावेश <linux/security.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/rw.h>
#समावेश <rdma/lag.h>

#समावेश "core_priv.h"
#समावेश <trace/events/rdma_core.h>

अटल पूर्णांक ib_resolve_eth_dmac(काष्ठा ib_device *device,
			       काष्ठा rdma_ah_attr *ah_attr);

अटल स्थिर अक्षर * स्थिर ib_events[] = अणु
	[IB_EVENT_CQ_ERR]		= "CQ error",
	[IB_EVENT_QP_FATAL]		= "QP fatal error",
	[IB_EVENT_QP_REQ_ERR]		= "QP request error",
	[IB_EVENT_QP_ACCESS_ERR]	= "QP access error",
	[IB_EVENT_COMM_EST]		= "communication established",
	[IB_EVENT_SQ_DRAINED]		= "send queue drained",
	[IB_EVENT_PATH_MIG]		= "path migration successful",
	[IB_EVENT_PATH_MIG_ERR]		= "path migration error",
	[IB_EVENT_DEVICE_FATAL]		= "device fatal error",
	[IB_EVENT_PORT_ACTIVE]		= "port active",
	[IB_EVENT_PORT_ERR]		= "port error",
	[IB_EVENT_LID_CHANGE]		= "LID change",
	[IB_EVENT_PKEY_CHANGE]		= "P_key change",
	[IB_EVENT_SM_CHANGE]		= "SM change",
	[IB_EVENT_SRQ_ERR]		= "SRQ error",
	[IB_EVENT_SRQ_LIMIT_REACHED]	= "SRQ limit reached",
	[IB_EVENT_QP_LAST_WQE_REACHED]	= "last WQE reached",
	[IB_EVENT_CLIENT_REREGISTER]	= "client reregister",
	[IB_EVENT_GID_CHANGE]		= "GID changed",
पूर्ण;

स्थिर अक्षर *__attribute_स्थिर__ ib_event_msg(क्रमागत ib_event_type event)
अणु
	माप_प्रकार index = event;

	वापस (index < ARRAY_SIZE(ib_events) && ib_events[index]) ?
			ib_events[index] : "unrecognized event";
पूर्ण
EXPORT_SYMBOL(ib_event_msg);

अटल स्थिर अक्षर * स्थिर wc_statuses[] = अणु
	[IB_WC_SUCCESS]			= "success",
	[IB_WC_LOC_LEN_ERR]		= "local length error",
	[IB_WC_LOC_QP_OP_ERR]		= "local QP operation error",
	[IB_WC_LOC_EEC_OP_ERR]		= "local EE context operation error",
	[IB_WC_LOC_PROT_ERR]		= "local protection error",
	[IB_WC_WR_FLUSH_ERR]		= "WR flushed",
	[IB_WC_MW_BIND_ERR]		= "memory bind operation error",
	[IB_WC_BAD_RESP_ERR]		= "bad response error",
	[IB_WC_LOC_ACCESS_ERR]		= "local access error",
	[IB_WC_REM_INV_REQ_ERR]		= "remote invalid request error",
	[IB_WC_REM_ACCESS_ERR]		= "remote access error",
	[IB_WC_REM_OP_ERR]		= "remote operation error",
	[IB_WC_RETRY_EXC_ERR]		= "transport retry counter exceeded",
	[IB_WC_RNR_RETRY_EXC_ERR]	= "RNR retry counter exceeded",
	[IB_WC_LOC_RDD_VIOL_ERR]	= "local RDD violation error",
	[IB_WC_REM_INV_RD_REQ_ERR]	= "remote invalid RD request",
	[IB_WC_REM_ABORT_ERR]		= "operation aborted",
	[IB_WC_INV_EECN_ERR]		= "invalid EE context number",
	[IB_WC_INV_EEC_STATE_ERR]	= "invalid EE context state",
	[IB_WC_FATAL_ERR]		= "fatal error",
	[IB_WC_RESP_TIMEOUT_ERR]	= "response timeout error",
	[IB_WC_GENERAL_ERR]		= "general error",
पूर्ण;

स्थिर अक्षर *__attribute_स्थिर__ ib_wc_status_msg(क्रमागत ib_wc_status status)
अणु
	माप_प्रकार index = status;

	वापस (index < ARRAY_SIZE(wc_statuses) && wc_statuses[index]) ?
			wc_statuses[index] : "unrecognized status";
पूर्ण
EXPORT_SYMBOL(ib_wc_status_msg);

__attribute_स्थिर__ पूर्णांक ib_rate_to_mult(क्रमागत ib_rate rate)
अणु
	चयन (rate) अणु
	हाल IB_RATE_2_5_GBPS: वापस   1;
	हाल IB_RATE_5_GBPS:   वापस   2;
	हाल IB_RATE_10_GBPS:  वापस   4;
	हाल IB_RATE_20_GBPS:  वापस   8;
	हाल IB_RATE_30_GBPS:  वापस  12;
	हाल IB_RATE_40_GBPS:  वापस  16;
	हाल IB_RATE_60_GBPS:  वापस  24;
	हाल IB_RATE_80_GBPS:  वापस  32;
	हाल IB_RATE_120_GBPS: वापस  48;
	हाल IB_RATE_14_GBPS:  वापस   6;
	हाल IB_RATE_56_GBPS:  वापस  22;
	हाल IB_RATE_112_GBPS: वापस  45;
	हाल IB_RATE_168_GBPS: वापस  67;
	हाल IB_RATE_25_GBPS:  वापस  10;
	हाल IB_RATE_100_GBPS: वापस  40;
	हाल IB_RATE_200_GBPS: वापस  80;
	हाल IB_RATE_300_GBPS: वापस 120;
	हाल IB_RATE_28_GBPS:  वापस  11;
	हाल IB_RATE_50_GBPS:  वापस  20;
	हाल IB_RATE_400_GBPS: वापस 160;
	हाल IB_RATE_600_GBPS: वापस 240;
	शेष:	       वापस  -1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_rate_to_mult);

__attribute_स्थिर__ क्रमागत ib_rate mult_to_ib_rate(पूर्णांक mult)
अणु
	चयन (mult) अणु
	हाल 1:   वापस IB_RATE_2_5_GBPS;
	हाल 2:   वापस IB_RATE_5_GBPS;
	हाल 4:   वापस IB_RATE_10_GBPS;
	हाल 8:   वापस IB_RATE_20_GBPS;
	हाल 12:  वापस IB_RATE_30_GBPS;
	हाल 16:  वापस IB_RATE_40_GBPS;
	हाल 24:  वापस IB_RATE_60_GBPS;
	हाल 32:  वापस IB_RATE_80_GBPS;
	हाल 48:  वापस IB_RATE_120_GBPS;
	हाल 6:   वापस IB_RATE_14_GBPS;
	हाल 22:  वापस IB_RATE_56_GBPS;
	हाल 45:  वापस IB_RATE_112_GBPS;
	हाल 67:  वापस IB_RATE_168_GBPS;
	हाल 10:  वापस IB_RATE_25_GBPS;
	हाल 40:  वापस IB_RATE_100_GBPS;
	हाल 80:  वापस IB_RATE_200_GBPS;
	हाल 120: वापस IB_RATE_300_GBPS;
	हाल 11:  वापस IB_RATE_28_GBPS;
	हाल 20:  वापस IB_RATE_50_GBPS;
	हाल 160: वापस IB_RATE_400_GBPS;
	हाल 240: वापस IB_RATE_600_GBPS;
	शेष:  वापस IB_RATE_PORT_CURRENT;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mult_to_ib_rate);

__attribute_स्थिर__ पूर्णांक ib_rate_to_mbps(क्रमागत ib_rate rate)
अणु
	चयन (rate) अणु
	हाल IB_RATE_2_5_GBPS: वापस 2500;
	हाल IB_RATE_5_GBPS:   वापस 5000;
	हाल IB_RATE_10_GBPS:  वापस 10000;
	हाल IB_RATE_20_GBPS:  वापस 20000;
	हाल IB_RATE_30_GBPS:  वापस 30000;
	हाल IB_RATE_40_GBPS:  वापस 40000;
	हाल IB_RATE_60_GBPS:  वापस 60000;
	हाल IB_RATE_80_GBPS:  वापस 80000;
	हाल IB_RATE_120_GBPS: वापस 120000;
	हाल IB_RATE_14_GBPS:  वापस 14062;
	हाल IB_RATE_56_GBPS:  वापस 56250;
	हाल IB_RATE_112_GBPS: वापस 112500;
	हाल IB_RATE_168_GBPS: वापस 168750;
	हाल IB_RATE_25_GBPS:  वापस 25781;
	हाल IB_RATE_100_GBPS: वापस 103125;
	हाल IB_RATE_200_GBPS: वापस 206250;
	हाल IB_RATE_300_GBPS: वापस 309375;
	हाल IB_RATE_28_GBPS:  वापस 28125;
	हाल IB_RATE_50_GBPS:  वापस 53125;
	हाल IB_RATE_400_GBPS: वापस 425000;
	हाल IB_RATE_600_GBPS: वापस 637500;
	शेष:	       वापस -1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_rate_to_mbps);

__attribute_स्थिर__ क्रमागत rdma_transport_type
rdma_node_get_transport(अचिन्हित पूर्णांक node_type)
अणु

	अगर (node_type == RDMA_NODE_USNIC)
		वापस RDMA_TRANSPORT_USNIC;
	अगर (node_type == RDMA_NODE_USNIC_UDP)
		वापस RDMA_TRANSPORT_USNIC_UDP;
	अगर (node_type == RDMA_NODE_RNIC)
		वापस RDMA_TRANSPORT_IWARP;
	अगर (node_type == RDMA_NODE_UNSPECIFIED)
		वापस RDMA_TRANSPORT_UNSPECIFIED;

	वापस RDMA_TRANSPORT_IB;
पूर्ण
EXPORT_SYMBOL(rdma_node_get_transport);

क्रमागत rdma_link_layer rdma_port_get_link_layer(काष्ठा ib_device *device,
					      u32 port_num)
अणु
	क्रमागत rdma_transport_type lt;
	अगर (device->ops.get_link_layer)
		वापस device->ops.get_link_layer(device, port_num);

	lt = rdma_node_get_transport(device->node_type);
	अगर (lt == RDMA_TRANSPORT_IB)
		वापस IB_LINK_LAYER_INFINIBAND;

	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण
EXPORT_SYMBOL(rdma_port_get_link_layer);

/* Protection करोमुख्यs */

/**
 * __ib_alloc_pd - Allocates an unused protection करोमुख्य.
 * @device: The device on which to allocate the protection करोमुख्य.
 * @flags: protection करोमुख्य flags
 * @caller: caller's build-समय module name
 *
 * A protection करोमुख्य object provides an association between QPs, shared
 * receive queues, address handles, memory regions, and memory winकरोws.
 *
 * Every PD has a local_dma_lkey which can be used as the lkey value क्रम local
 * memory operations.
 */
काष्ठा ib_pd *__ib_alloc_pd(काष्ठा ib_device *device, अचिन्हित पूर्णांक flags,
		स्थिर अक्षर *caller)
अणु
	काष्ठा ib_pd *pd;
	पूर्णांक mr_access_flags = 0;
	पूर्णांक ret;

	pd = rdma_zalloc_drv_obj(device, ib_pd);
	अगर (!pd)
		वापस ERR_PTR(-ENOMEM);

	pd->device = device;
	pd->uobject = शून्य;
	pd->__पूर्णांकernal_mr = शून्य;
	atomic_set(&pd->usecnt, 0);
	pd->flags = flags;

	rdma_restrack_new(&pd->res, RDMA_RESTRACK_PD);
	rdma_restrack_set_name(&pd->res, caller);

	ret = device->ops.alloc_pd(pd, शून्य);
	अगर (ret) अणु
		rdma_restrack_put(&pd->res);
		kमुक्त(pd);
		वापस ERR_PTR(ret);
	पूर्ण
	rdma_restrack_add(&pd->res);

	अगर (device->attrs.device_cap_flags & IB_DEVICE_LOCAL_DMA_LKEY)
		pd->local_dma_lkey = device->local_dma_lkey;
	अन्यथा
		mr_access_flags |= IB_ACCESS_LOCAL_WRITE;

	अगर (flags & IB_PD_UNSAFE_GLOBAL_RKEY) अणु
		pr_warn("%s: enabling unsafe global rkey\n", caller);
		mr_access_flags |= IB_ACCESS_REMOTE_READ | IB_ACCESS_REMOTE_WRITE;
	पूर्ण

	अगर (mr_access_flags) अणु
		काष्ठा ib_mr *mr;

		mr = pd->device->ops.get_dma_mr(pd, mr_access_flags);
		अगर (IS_ERR(mr)) अणु
			ib_dealloc_pd(pd);
			वापस ERR_CAST(mr);
		पूर्ण

		mr->device	= pd->device;
		mr->pd		= pd;
		mr->type        = IB_MR_TYPE_DMA;
		mr->uobject	= शून्य;
		mr->need_inval	= false;

		pd->__पूर्णांकernal_mr = mr;

		अगर (!(device->attrs.device_cap_flags & IB_DEVICE_LOCAL_DMA_LKEY))
			pd->local_dma_lkey = pd->__पूर्णांकernal_mr->lkey;

		अगर (flags & IB_PD_UNSAFE_GLOBAL_RKEY)
			pd->unsafe_global_rkey = pd->__पूर्णांकernal_mr->rkey;
	पूर्ण

	वापस pd;
पूर्ण
EXPORT_SYMBOL(__ib_alloc_pd);

/**
 * ib_dealloc_pd_user - Deallocates a protection करोमुख्य.
 * @pd: The protection करोमुख्य to deallocate.
 * @udata: Valid user data or शून्य क्रम kernel object
 *
 * It is an error to call this function जबतक any resources in the pd still
 * exist.  The caller is responsible to synchronously destroy them and
 * guarantee no new allocations will happen.
 */
पूर्णांक ib_dealloc_pd_user(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret;

	अगर (pd->__पूर्णांकernal_mr) अणु
		ret = pd->device->ops.dereg_mr(pd->__पूर्णांकernal_mr, शून्य);
		WARN_ON(ret);
		pd->__पूर्णांकernal_mr = शून्य;
	पूर्ण

	/* uverbs manipulates usecnt with proper locking, जबतक the kabi
	 * requires the caller to guarantee we can't race here.
	 */
	WARN_ON(atomic_पढ़ो(&pd->usecnt));

	ret = pd->device->ops.dealloc_pd(pd, udata);
	अगर (ret)
		वापस ret;

	rdma_restrack_del(&pd->res);
	kमुक्त(pd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_dealloc_pd_user);

/* Address handles */

/**
 * rdma_copy_ah_attr - Copy rdma ah attribute from source to destination.
 * @dest:       Poपूर्णांकer to destination ah_attr. Contents of the destination
 *              poपूर्णांकer is assumed to be invalid and attribute are overwritten.
 * @src:        Poपूर्णांकer to source ah_attr.
 */
व्योम rdma_copy_ah_attr(काष्ठा rdma_ah_attr *dest,
		       स्थिर काष्ठा rdma_ah_attr *src)
अणु
	*dest = *src;
	अगर (dest->grh.sgid_attr)
		rdma_hold_gid_attr(dest->grh.sgid_attr);
पूर्ण
EXPORT_SYMBOL(rdma_copy_ah_attr);

/**
 * rdma_replace_ah_attr - Replace valid ah_attr with new new one.
 * @old:        Poपूर्णांकer to existing ah_attr which needs to be replaced.
 *              old is assumed to be valid or zero'd
 * @new:        Poपूर्णांकer to the new ah_attr.
 *
 * rdma_replace_ah_attr() first releases any reference in the old ah_attr अगर
 * old the ah_attr is valid; after that it copies the new attribute and holds
 * the reference to the replaced ah_attr.
 */
व्योम rdma_replace_ah_attr(काष्ठा rdma_ah_attr *old,
			  स्थिर काष्ठा rdma_ah_attr *new)
अणु
	rdma_destroy_ah_attr(old);
	*old = *new;
	अगर (old->grh.sgid_attr)
		rdma_hold_gid_attr(old->grh.sgid_attr);
पूर्ण
EXPORT_SYMBOL(rdma_replace_ah_attr);

/**
 * rdma_move_ah_attr - Move ah_attr poपूर्णांकed by source to destination.
 * @dest:       Poपूर्णांकer to destination ah_attr to copy to.
 *              dest is assumed to be valid or zero'd
 * @src:        Poपूर्णांकer to the new ah_attr.
 *
 * rdma_move_ah_attr() first releases any reference in the destination ah_attr
 * अगर it is valid. This also transfers ownership of पूर्णांकernal references from
 * src to dest, making src invalid in the process. No new reference of the src
 * ah_attr is taken.
 */
व्योम rdma_move_ah_attr(काष्ठा rdma_ah_attr *dest, काष्ठा rdma_ah_attr *src)
अणु
	rdma_destroy_ah_attr(dest);
	*dest = *src;
	src->grh.sgid_attr = शून्य;
पूर्ण
EXPORT_SYMBOL(rdma_move_ah_attr);

/*
 * Validate that the rdma_ah_attr is valid क्रम the device beक्रमe passing it
 * off to the driver.
 */
अटल पूर्णांक rdma_check_ah_attr(काष्ठा ib_device *device,
			      काष्ठा rdma_ah_attr *ah_attr)
अणु
	अगर (!rdma_is_port_valid(device, ah_attr->port_num))
		वापस -EINVAL;

	अगर ((rdma_is_grh_required(device, ah_attr->port_num) ||
	     ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) &&
	    !(ah_attr->ah_flags & IB_AH_GRH))
		वापस -EINVAL;

	अगर (ah_attr->grh.sgid_attr) अणु
		/*
		 * Make sure the passed sgid_attr is consistent with the
		 * parameters
		 */
		अगर (ah_attr->grh.sgid_attr->index != ah_attr->grh.sgid_index ||
		    ah_attr->grh.sgid_attr->port_num != ah_attr->port_num)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * If the ah requires a GRH then ensure that sgid_attr poपूर्णांकer is filled in.
 * On success the caller is responsible to call rdma_unfill_sgid_attr().
 */
अटल पूर्णांक rdma_fill_sgid_attr(काष्ठा ib_device *device,
			       काष्ठा rdma_ah_attr *ah_attr,
			       स्थिर काष्ठा ib_gid_attr **old_sgid_attr)
अणु
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	काष्ठा ib_global_route *grh;
	पूर्णांक ret;

	*old_sgid_attr = ah_attr->grh.sgid_attr;

	ret = rdma_check_ah_attr(device, ah_attr);
	अगर (ret)
		वापस ret;

	अगर (!(ah_attr->ah_flags & IB_AH_GRH))
		वापस 0;

	grh = rdma_ah_retrieve_grh(ah_attr);
	अगर (grh->sgid_attr)
		वापस 0;

	sgid_attr =
		rdma_get_gid_attr(device, ah_attr->port_num, grh->sgid_index);
	अगर (IS_ERR(sgid_attr))
		वापस PTR_ERR(sgid_attr);

	/* Move ownerhip of the kref पूर्णांकo the ah_attr */
	grh->sgid_attr = sgid_attr;
	वापस 0;
पूर्ण

अटल व्योम rdma_unfill_sgid_attr(काष्ठा rdma_ah_attr *ah_attr,
				  स्थिर काष्ठा ib_gid_attr *old_sgid_attr)
अणु
	/*
	 * Fill didn't change anything, the caller retains ownership of
	 * whatever it passed
	 */
	अगर (ah_attr->grh.sgid_attr == old_sgid_attr)
		वापस;

	/*
	 * Otherwise, we need to unकरो what rdma_fill_sgid_attr so the caller
	 * करोesn't see any change in the rdma_ah_attr. If we get here
	 * old_sgid_attr is शून्य.
	 */
	rdma_destroy_ah_attr(ah_attr);
पूर्ण

अटल स्थिर काष्ठा ib_gid_attr *
rdma_update_sgid_attr(काष्ठा rdma_ah_attr *ah_attr,
		      स्थिर काष्ठा ib_gid_attr *old_attr)
अणु
	अगर (old_attr)
		rdma_put_gid_attr(old_attr);
	अगर (ah_attr->ah_flags & IB_AH_GRH) अणु
		rdma_hold_gid_attr(ah_attr->grh.sgid_attr);
		वापस ah_attr->grh.sgid_attr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा ib_ah *_rdma_create_ah(काष्ठा ib_pd *pd,
				     काष्ठा rdma_ah_attr *ah_attr,
				     u32 flags,
				     काष्ठा ib_udata *udata,
				     काष्ठा net_device *xmit_slave)
अणु
	काष्ठा rdma_ah_init_attr init_attr = अणुपूर्ण;
	काष्ठा ib_device *device = pd->device;
	काष्ठा ib_ah *ah;
	पूर्णांक ret;

	might_sleep_अगर(flags & RDMA_CREATE_AH_SLEEPABLE);

	अगर (!udata && !device->ops.create_ah)
		वापस ERR_PTR(-EOPNOTSUPP);

	ah = rdma_zalloc_drv_obj_gfp(
		device, ib_ah,
		(flags & RDMA_CREATE_AH_SLEEPABLE) ? GFP_KERNEL : GFP_ATOMIC);
	अगर (!ah)
		वापस ERR_PTR(-ENOMEM);

	ah->device = device;
	ah->pd = pd;
	ah->type = ah_attr->type;
	ah->sgid_attr = rdma_update_sgid_attr(ah_attr, शून्य);
	init_attr.ah_attr = ah_attr;
	init_attr.flags = flags;
	init_attr.xmit_slave = xmit_slave;

	अगर (udata)
		ret = device->ops.create_user_ah(ah, &init_attr, udata);
	अन्यथा
		ret = device->ops.create_ah(ah, &init_attr, शून्य);
	अगर (ret) अणु
		kमुक्त(ah);
		वापस ERR_PTR(ret);
	पूर्ण

	atomic_inc(&pd->usecnt);
	वापस ah;
पूर्ण

/**
 * rdma_create_ah - Creates an address handle क्रम the
 * given address vector.
 * @pd: The protection करोमुख्य associated with the address handle.
 * @ah_attr: The attributes of the address vector.
 * @flags: Create address handle flags (see क्रमागत rdma_create_ah_flags).
 *
 * It वापसs 0 on success and वापसs appropriate error code on error.
 * The address handle is used to reference a local or global destination
 * in all UD QP post sends.
 */
काष्ठा ib_ah *rdma_create_ah(काष्ठा ib_pd *pd, काष्ठा rdma_ah_attr *ah_attr,
			     u32 flags)
अणु
	स्थिर काष्ठा ib_gid_attr *old_sgid_attr;
	काष्ठा net_device *slave;
	काष्ठा ib_ah *ah;
	पूर्णांक ret;

	ret = rdma_fill_sgid_attr(pd->device, ah_attr, &old_sgid_attr);
	अगर (ret)
		वापस ERR_PTR(ret);
	slave = rdma_lag_get_ah_roce_slave(pd->device, ah_attr,
					   (flags & RDMA_CREATE_AH_SLEEPABLE) ?
					   GFP_KERNEL : GFP_ATOMIC);
	अगर (IS_ERR(slave)) अणु
		rdma_unfill_sgid_attr(ah_attr, old_sgid_attr);
		वापस (व्योम *)slave;
	पूर्ण
	ah = _rdma_create_ah(pd, ah_attr, flags, शून्य, slave);
	rdma_lag_put_ah_roce_slave(slave);
	rdma_unfill_sgid_attr(ah_attr, old_sgid_attr);
	वापस ah;
पूर्ण
EXPORT_SYMBOL(rdma_create_ah);

/**
 * rdma_create_user_ah - Creates an address handle क्रम the
 * given address vector.
 * It resolves destination mac address क्रम ah attribute of RoCE type.
 * @pd: The protection करोमुख्य associated with the address handle.
 * @ah_attr: The attributes of the address vector.
 * @udata: poपूर्णांकer to user's input output buffer inक्रमmation need by
 *         provider driver.
 *
 * It वापसs 0 on success and वापसs appropriate error code on error.
 * The address handle is used to reference a local or global destination
 * in all UD QP post sends.
 */
काष्ठा ib_ah *rdma_create_user_ah(काष्ठा ib_pd *pd,
				  काष्ठा rdma_ah_attr *ah_attr,
				  काष्ठा ib_udata *udata)
अणु
	स्थिर काष्ठा ib_gid_attr *old_sgid_attr;
	काष्ठा ib_ah *ah;
	पूर्णांक err;

	err = rdma_fill_sgid_attr(pd->device, ah_attr, &old_sgid_attr);
	अगर (err)
		वापस ERR_PTR(err);

	अगर (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		err = ib_resolve_eth_dmac(pd->device, ah_attr);
		अगर (err) अणु
			ah = ERR_PTR(err);
			जाओ out;
		पूर्ण
	पूर्ण

	ah = _rdma_create_ah(pd, ah_attr, RDMA_CREATE_AH_SLEEPABLE,
			     udata, शून्य);

out:
	rdma_unfill_sgid_attr(ah_attr, old_sgid_attr);
	वापस ah;
पूर्ण
EXPORT_SYMBOL(rdma_create_user_ah);

पूर्णांक ib_get_rdma_header_version(स्थिर जोड़ rdma_network_hdr *hdr)
अणु
	स्थिर काष्ठा iphdr *ip4h = (काष्ठा iphdr *)&hdr->roce4grh;
	काष्ठा iphdr ip4h_checked;
	स्थिर काष्ठा ipv6hdr *ip6h = (काष्ठा ipv6hdr *)&hdr->ibgrh;

	/* If it's IPv6, the version must be 6, otherwise, the first
	 * 20 bytes (beक्रमe the IPv4 header) are garbled.
	 */
	अगर (ip6h->version != 6)
		वापस (ip4h->version == 4) ? 4 : 0;
	/* version may be 6 or 4 because the first 20 bytes could be garbled */

	/* RoCE v2 requires no options, thus header length
	 * must be 5 words
	 */
	अगर (ip4h->ihl != 5)
		वापस 6;

	/* Verअगरy checksum.
	 * We can't ग_लिखो on scattered buffers so we need to copy to
	 * temp buffer.
	 */
	स_नकल(&ip4h_checked, ip4h, माप(ip4h_checked));
	ip4h_checked.check = 0;
	ip4h_checked.check = ip_fast_csum((u8 *)&ip4h_checked, 5);
	/* अगर IPv4 header checksum is OK, believe it */
	अगर (ip4h->check == ip4h_checked.check)
		वापस 4;
	वापस 6;
पूर्ण
EXPORT_SYMBOL(ib_get_rdma_header_version);

अटल क्रमागत rdma_network_type ib_get_net_type_by_grh(काष्ठा ib_device *device,
						     u32 port_num,
						     स्थिर काष्ठा ib_grh *grh)
अणु
	पूर्णांक grh_version;

	अगर (rdma_protocol_ib(device, port_num))
		वापस RDMA_NETWORK_IB;

	grh_version = ib_get_rdma_header_version((जोड़ rdma_network_hdr *)grh);

	अगर (grh_version == 4)
		वापस RDMA_NETWORK_IPV4;

	अगर (grh->next_hdr == IPPROTO_UDP)
		वापस RDMA_NETWORK_IPV6;

	वापस RDMA_NETWORK_ROCE_V1;
पूर्ण

काष्ठा find_gid_index_context अणु
	u16 vlan_id;
	क्रमागत ib_gid_type gid_type;
पूर्ण;

अटल bool find_gid_index(स्थिर जोड़ ib_gid *gid,
			   स्थिर काष्ठा ib_gid_attr *gid_attr,
			   व्योम *context)
अणु
	काष्ठा find_gid_index_context *ctx = context;
	u16 vlan_id = 0xffff;
	पूर्णांक ret;

	अगर (ctx->gid_type != gid_attr->gid_type)
		वापस false;

	ret = rdma_पढ़ो_gid_l2_fields(gid_attr, &vlan_id, शून्य);
	अगर (ret)
		वापस false;

	वापस ctx->vlan_id == vlan_id;
पूर्ण

अटल स्थिर काष्ठा ib_gid_attr *
get_sgid_attr_from_eth(काष्ठा ib_device *device, u32 port_num,
		       u16 vlan_id, स्थिर जोड़ ib_gid *sgid,
		       क्रमागत ib_gid_type gid_type)
अणु
	काष्ठा find_gid_index_context context = अणु.vlan_id = vlan_id,
						 .gid_type = gid_typeपूर्ण;

	वापस rdma_find_gid_by_filter(device, sgid, port_num, find_gid_index,
				       &context);
पूर्ण

पूर्णांक ib_get_gids_from_rdma_hdr(स्थिर जोड़ rdma_network_hdr *hdr,
			      क्रमागत rdma_network_type net_type,
			      जोड़ ib_gid *sgid, जोड़ ib_gid *dgid)
अणु
	काष्ठा sockaddr_in  src_in;
	काष्ठा sockaddr_in  dst_in;
	__be32 src_saddr, dst_saddr;

	अगर (!sgid || !dgid)
		वापस -EINVAL;

	अगर (net_type == RDMA_NETWORK_IPV4) अणु
		स_नकल(&src_in.sin_addr.s_addr,
		       &hdr->roce4grh.saddr, 4);
		स_नकल(&dst_in.sin_addr.s_addr,
		       &hdr->roce4grh.daddr, 4);
		src_saddr = src_in.sin_addr.s_addr;
		dst_saddr = dst_in.sin_addr.s_addr;
		ipv6_addr_set_v4mapped(src_saddr,
				       (काष्ठा in6_addr *)sgid);
		ipv6_addr_set_v4mapped(dst_saddr,
				       (काष्ठा in6_addr *)dgid);
		वापस 0;
	पूर्ण अन्यथा अगर (net_type == RDMA_NETWORK_IPV6 ||
		   net_type == RDMA_NETWORK_IB || RDMA_NETWORK_ROCE_V1) अणु
		*dgid = hdr->ibgrh.dgid;
		*sgid = hdr->ibgrh.sgid;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_get_gids_from_rdma_hdr);

/* Resolve destination mac address and hop limit क्रम unicast destination
 * GID entry, considering the source GID entry as well.
 * ah_attribute must have have valid port_num, sgid_index.
 */
अटल पूर्णांक ib_resolve_unicast_gid_dmac(काष्ठा ib_device *device,
				       काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(ah_attr);
	स्थिर काष्ठा ib_gid_attr *sgid_attr = grh->sgid_attr;
	पूर्णांक hop_limit = 0xff;
	पूर्णांक ret = 0;

	/* If destination is link local and source GID is RoCEv1,
	 * IP stack is not used.
	 */
	अगर (rdma_link_local_addr((काष्ठा in6_addr *)grh->dgid.raw) &&
	    sgid_attr->gid_type == IB_GID_TYPE_ROCE) अणु
		rdma_get_ll_mac((काष्ठा in6_addr *)grh->dgid.raw,
				ah_attr->roce.dmac);
		वापस ret;
	पूर्ण

	ret = rdma_addr_find_l2_eth_by_grh(&sgid_attr->gid, &grh->dgid,
					   ah_attr->roce.dmac,
					   sgid_attr, &hop_limit);

	grh->hop_limit = hop_limit;
	वापस ret;
पूर्ण

/*
 * This function initializes address handle attributes from the incoming packet.
 * Incoming packet has dgid of the receiver node on which this code is
 * getting executed and, sgid contains the GID of the sender.
 *
 * When resolving mac address of destination, the arrived dgid is used
 * as sgid and, sgid is used as dgid because sgid contains destinations
 * GID whom to respond to.
 *
 * On success the caller is responsible to call rdma_destroy_ah_attr on the
 * attr.
 */
पूर्णांक ib_init_ah_attr_from_wc(काष्ठा ib_device *device, u32 port_num,
			    स्थिर काष्ठा ib_wc *wc, स्थिर काष्ठा ib_grh *grh,
			    काष्ठा rdma_ah_attr *ah_attr)
अणु
	u32 flow_class;
	पूर्णांक ret;
	क्रमागत rdma_network_type net_type = RDMA_NETWORK_IB;
	क्रमागत ib_gid_type gid_type = IB_GID_TYPE_IB;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	पूर्णांक hoplimit = 0xff;
	जोड़ ib_gid dgid;
	जोड़ ib_gid sgid;

	might_sleep();

	स_रखो(ah_attr, 0, माप *ah_attr);
	ah_attr->type = rdma_ah_find_type(device, port_num);
	अगर (rdma_cap_eth_ah(device, port_num)) अणु
		अगर (wc->wc_flags & IB_WC_WITH_NETWORK_HDR_TYPE)
			net_type = wc->network_hdr_type;
		अन्यथा
			net_type = ib_get_net_type_by_grh(device, port_num, grh);
		gid_type = ib_network_to_gid_type(net_type);
	पूर्ण
	ret = ib_get_gids_from_rdma_hdr((जोड़ rdma_network_hdr *)grh, net_type,
					&sgid, &dgid);
	अगर (ret)
		वापस ret;

	rdma_ah_set_sl(ah_attr, wc->sl);
	rdma_ah_set_port_num(ah_attr, port_num);

	अगर (rdma_protocol_roce(device, port_num)) अणु
		u16 vlan_id = wc->wc_flags & IB_WC_WITH_VLAN ?
				wc->vlan_id : 0xffff;

		अगर (!(wc->wc_flags & IB_WC_GRH))
			वापस -EPROTOTYPE;

		sgid_attr = get_sgid_attr_from_eth(device, port_num,
						   vlan_id, &dgid,
						   gid_type);
		अगर (IS_ERR(sgid_attr))
			वापस PTR_ERR(sgid_attr);

		flow_class = be32_to_cpu(grh->version_tclass_flow);
		rdma_move_grh_sgid_attr(ah_attr,
					&sgid,
					flow_class & 0xFFFFF,
					hoplimit,
					(flow_class >> 20) & 0xFF,
					sgid_attr);

		ret = ib_resolve_unicast_gid_dmac(device, ah_attr);
		अगर (ret)
			rdma_destroy_ah_attr(ah_attr);

		वापस ret;
	पूर्ण अन्यथा अणु
		rdma_ah_set_dlid(ah_attr, wc->slid);
		rdma_ah_set_path_bits(ah_attr, wc->dlid_path_bits);

		अगर ((wc->wc_flags & IB_WC_GRH) == 0)
			वापस 0;

		अगर (dgid.global.पूर्णांकerface_id !=
					cpu_to_be64(IB_SA_WELL_KNOWN_GUID)) अणु
			sgid_attr = rdma_find_gid_by_port(
				device, &dgid, IB_GID_TYPE_IB, port_num, शून्य);
		पूर्ण अन्यथा
			sgid_attr = rdma_get_gid_attr(device, port_num, 0);

		अगर (IS_ERR(sgid_attr))
			वापस PTR_ERR(sgid_attr);
		flow_class = be32_to_cpu(grh->version_tclass_flow);
		rdma_move_grh_sgid_attr(ah_attr,
					&sgid,
					flow_class & 0xFFFFF,
					hoplimit,
					(flow_class >> 20) & 0xFF,
					sgid_attr);

		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_init_ah_attr_from_wc);

/**
 * rdma_move_grh_sgid_attr - Sets the sgid attribute of GRH, taking ownership
 * of the reference
 *
 * @attr:	Poपूर्णांकer to AH attribute काष्ठाure
 * @dgid:	Destination GID
 * @flow_label:	Flow label
 * @hop_limit:	Hop limit
 * @traffic_class: traffic class
 * @sgid_attr:	Poपूर्णांकer to SGID attribute
 *
 * This takes ownership of the sgid_attr reference. The caller must ensure
 * rdma_destroy_ah_attr() is called beक्रमe destroying the rdma_ah_attr after
 * calling this function.
 */
व्योम rdma_move_grh_sgid_attr(काष्ठा rdma_ah_attr *attr, जोड़ ib_gid *dgid,
			     u32 flow_label, u8 hop_limit, u8 traffic_class,
			     स्थिर काष्ठा ib_gid_attr *sgid_attr)
अणु
	rdma_ah_set_grh(attr, dgid, flow_label, sgid_attr->index, hop_limit,
			traffic_class);
	attr->grh.sgid_attr = sgid_attr;
पूर्ण
EXPORT_SYMBOL(rdma_move_grh_sgid_attr);

/**
 * rdma_destroy_ah_attr - Release reference to SGID attribute of
 * ah attribute.
 * @ah_attr: Poपूर्णांकer to ah attribute
 *
 * Release reference to the SGID attribute of the ah attribute अगर it is
 * non शून्य. It is safe to call this multiple बार, and safe to call it on
 * a zero initialized ah_attr.
 */
व्योम rdma_destroy_ah_attr(काष्ठा rdma_ah_attr *ah_attr)
अणु
	अगर (ah_attr->grh.sgid_attr) अणु
		rdma_put_gid_attr(ah_attr->grh.sgid_attr);
		ah_attr->grh.sgid_attr = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rdma_destroy_ah_attr);

काष्ठा ib_ah *ib_create_ah_from_wc(काष्ठा ib_pd *pd, स्थिर काष्ठा ib_wc *wc,
				   स्थिर काष्ठा ib_grh *grh, u32 port_num)
अणु
	काष्ठा rdma_ah_attr ah_attr;
	काष्ठा ib_ah *ah;
	पूर्णांक ret;

	ret = ib_init_ah_attr_from_wc(pd->device, port_num, wc, grh, &ah_attr);
	अगर (ret)
		वापस ERR_PTR(ret);

	ah = rdma_create_ah(pd, &ah_attr, RDMA_CREATE_AH_SLEEPABLE);

	rdma_destroy_ah_attr(&ah_attr);
	वापस ah;
पूर्ण
EXPORT_SYMBOL(ib_create_ah_from_wc);

पूर्णांक rdma_modअगरy_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	स्थिर काष्ठा ib_gid_attr *old_sgid_attr;
	पूर्णांक ret;

	अगर (ah->type != ah_attr->type)
		वापस -EINVAL;

	ret = rdma_fill_sgid_attr(ah->device, ah_attr, &old_sgid_attr);
	अगर (ret)
		वापस ret;

	ret = ah->device->ops.modअगरy_ah ?
		ah->device->ops.modअगरy_ah(ah, ah_attr) :
		-EOPNOTSUPP;

	ah->sgid_attr = rdma_update_sgid_attr(ah_attr, ah->sgid_attr);
	rdma_unfill_sgid_attr(ah_attr, old_sgid_attr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_modअगरy_ah);

पूर्णांक rdma_query_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	ah_attr->grh.sgid_attr = शून्य;

	वापस ah->device->ops.query_ah ?
		ah->device->ops.query_ah(ah, ah_attr) :
		-EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(rdma_query_ah);

पूर्णांक rdma_destroy_ah_user(काष्ठा ib_ah *ah, u32 flags, काष्ठा ib_udata *udata)
अणु
	स्थिर काष्ठा ib_gid_attr *sgid_attr = ah->sgid_attr;
	काष्ठा ib_pd *pd;
	पूर्णांक ret;

	might_sleep_अगर(flags & RDMA_DESTROY_AH_SLEEPABLE);

	pd = ah->pd;

	ret = ah->device->ops.destroy_ah(ah, flags);
	अगर (ret)
		वापस ret;

	atomic_dec(&pd->usecnt);
	अगर (sgid_attr)
		rdma_put_gid_attr(sgid_attr);

	kमुक्त(ah);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_destroy_ah_user);

/* Shared receive queues */

/**
 * ib_create_srq_user - Creates a SRQ associated with the specअगरied protection
 *   करोमुख्य.
 * @pd: The protection करोमुख्य associated with the SRQ.
 * @srq_init_attr: A list of initial attributes required to create the
 *   SRQ.  If SRQ creation succeeds, then the attributes are updated to
 *   the actual capabilities of the created SRQ.
 * @uobject: uobject poपूर्णांकer अगर this is not a kernel SRQ
 * @udata: udata poपूर्णांकer अगर this is not a kernel SRQ
 *
 * srq_attr->max_wr and srq_attr->max_sge are पढ़ो the determine the
 * requested size of the SRQ, and set to the actual values allocated
 * on वापस.  If ib_create_srq() succeeds, then max_wr and max_sge
 * will always be at least as large as the requested values.
 */
काष्ठा ib_srq *ib_create_srq_user(काष्ठा ib_pd *pd,
				  काष्ठा ib_srq_init_attr *srq_init_attr,
				  काष्ठा ib_usrq_object *uobject,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_srq *srq;
	पूर्णांक ret;

	srq = rdma_zalloc_drv_obj(pd->device, ib_srq);
	अगर (!srq)
		वापस ERR_PTR(-ENOMEM);

	srq->device = pd->device;
	srq->pd = pd;
	srq->event_handler = srq_init_attr->event_handler;
	srq->srq_context = srq_init_attr->srq_context;
	srq->srq_type = srq_init_attr->srq_type;
	srq->uobject = uobject;

	अगर (ib_srq_has_cq(srq->srq_type)) अणु
		srq->ext.cq = srq_init_attr->ext.cq;
		atomic_inc(&srq->ext.cq->usecnt);
	पूर्ण
	अगर (srq->srq_type == IB_SRQT_XRC) अणु
		srq->ext.xrc.xrcd = srq_init_attr->ext.xrc.xrcd;
		atomic_inc(&srq->ext.xrc.xrcd->usecnt);
	पूर्ण
	atomic_inc(&pd->usecnt);

	rdma_restrack_new(&srq->res, RDMA_RESTRACK_SRQ);
	rdma_restrack_parent_name(&srq->res, &pd->res);

	ret = pd->device->ops.create_srq(srq, srq_init_attr, udata);
	अगर (ret) अणु
		rdma_restrack_put(&srq->res);
		atomic_dec(&srq->pd->usecnt);
		अगर (srq->srq_type == IB_SRQT_XRC)
			atomic_dec(&srq->ext.xrc.xrcd->usecnt);
		अगर (ib_srq_has_cq(srq->srq_type))
			atomic_dec(&srq->ext.cq->usecnt);
		kमुक्त(srq);
		वापस ERR_PTR(ret);
	पूर्ण

	rdma_restrack_add(&srq->res);

	वापस srq;
पूर्ण
EXPORT_SYMBOL(ib_create_srq_user);

पूर्णांक ib_modअगरy_srq(काष्ठा ib_srq *srq,
		  काष्ठा ib_srq_attr *srq_attr,
		  क्रमागत ib_srq_attr_mask srq_attr_mask)
अणु
	वापस srq->device->ops.modअगरy_srq ?
		srq->device->ops.modअगरy_srq(srq, srq_attr, srq_attr_mask,
					    शून्य) : -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_srq);

पूर्णांक ib_query_srq(काष्ठा ib_srq *srq,
		 काष्ठा ib_srq_attr *srq_attr)
अणु
	वापस srq->device->ops.query_srq ?
		srq->device->ops.query_srq(srq, srq_attr) : -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(ib_query_srq);

पूर्णांक ib_destroy_srq_user(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&srq->usecnt))
		वापस -EBUSY;

	ret = srq->device->ops.destroy_srq(srq, udata);
	अगर (ret)
		वापस ret;

	atomic_dec(&srq->pd->usecnt);
	अगर (srq->srq_type == IB_SRQT_XRC)
		atomic_dec(&srq->ext.xrc.xrcd->usecnt);
	अगर (ib_srq_has_cq(srq->srq_type))
		atomic_dec(&srq->ext.cq->usecnt);
	rdma_restrack_del(&srq->res);
	kमुक्त(srq);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_destroy_srq_user);

/* Queue pairs */

अटल व्योम __ib_shared_qp_event_handler(काष्ठा ib_event *event, व्योम *context)
अणु
	काष्ठा ib_qp *qp = context;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->device->qp_खोलो_list_lock, flags);
	list_क्रम_each_entry(event->element.qp, &qp->खोलो_list, खोलो_list)
		अगर (event->element.qp->event_handler)
			event->element.qp->event_handler(event, event->element.qp->qp_context);
	spin_unlock_irqrestore(&qp->device->qp_खोलो_list_lock, flags);
पूर्ण

अटल काष्ठा ib_qp *__ib_खोलो_qp(काष्ठा ib_qp *real_qp,
				  व्योम (*event_handler)(काष्ठा ib_event *, व्योम *),
				  व्योम *qp_context)
अणु
	काष्ठा ib_qp *qp;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	qp = kzalloc(माप *qp, GFP_KERNEL);
	अगर (!qp)
		वापस ERR_PTR(-ENOMEM);

	qp->real_qp = real_qp;
	err = ib_खोलो_shared_qp_security(qp, real_qp->device);
	अगर (err) अणु
		kमुक्त(qp);
		वापस ERR_PTR(err);
	पूर्ण

	qp->real_qp = real_qp;
	atomic_inc(&real_qp->usecnt);
	qp->device = real_qp->device;
	qp->event_handler = event_handler;
	qp->qp_context = qp_context;
	qp->qp_num = real_qp->qp_num;
	qp->qp_type = real_qp->qp_type;

	spin_lock_irqsave(&real_qp->device->qp_खोलो_list_lock, flags);
	list_add(&qp->खोलो_list, &real_qp->खोलो_list);
	spin_unlock_irqrestore(&real_qp->device->qp_खोलो_list_lock, flags);

	वापस qp;
पूर्ण

काष्ठा ib_qp *ib_खोलो_qp(काष्ठा ib_xrcd *xrcd,
			 काष्ठा ib_qp_खोलो_attr *qp_खोलो_attr)
अणु
	काष्ठा ib_qp *qp, *real_qp;

	अगर (qp_खोलो_attr->qp_type != IB_QPT_XRC_TGT)
		वापस ERR_PTR(-EINVAL);

	करोwn_पढ़ो(&xrcd->tgt_qps_rwsem);
	real_qp = xa_load(&xrcd->tgt_qps, qp_खोलो_attr->qp_num);
	अगर (!real_qp) अणु
		up_पढ़ो(&xrcd->tgt_qps_rwsem);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	qp = __ib_खोलो_qp(real_qp, qp_खोलो_attr->event_handler,
			  qp_खोलो_attr->qp_context);
	up_पढ़ो(&xrcd->tgt_qps_rwsem);
	वापस qp;
पूर्ण
EXPORT_SYMBOL(ib_खोलो_qp);

अटल काष्ठा ib_qp *create_xrc_qp_user(काष्ठा ib_qp *qp,
					काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा ib_qp *real_qp = qp;
	पूर्णांक err;

	qp->event_handler = __ib_shared_qp_event_handler;
	qp->qp_context = qp;
	qp->pd = शून्य;
	qp->send_cq = qp->recv_cq = शून्य;
	qp->srq = शून्य;
	qp->xrcd = qp_init_attr->xrcd;
	atomic_inc(&qp_init_attr->xrcd->usecnt);
	INIT_LIST_HEAD(&qp->खोलो_list);

	qp = __ib_खोलो_qp(real_qp, qp_init_attr->event_handler,
			  qp_init_attr->qp_context);
	अगर (IS_ERR(qp))
		वापस qp;

	err = xa_err(xa_store(&qp_init_attr->xrcd->tgt_qps, real_qp->qp_num,
			      real_qp, GFP_KERNEL));
	अगर (err) अणु
		ib_बंद_qp(qp);
		वापस ERR_PTR(err);
	पूर्ण
	वापस qp;
पूर्ण

/**
 * ib_create_named_qp - Creates a kernel QP associated with the specअगरied protection
 *   करोमुख्य.
 * @pd: The protection करोमुख्य associated with the QP.
 * @qp_init_attr: A list of initial attributes required to create the
 *   QP.  If QP creation succeeds, then the attributes are updated to
 *   the actual capabilities of the created QP.
 * @caller: caller's build-समय module name
 *
 * NOTE: क्रम user qp use ib_create_qp_user with valid udata!
 */
काष्ठा ib_qp *ib_create_named_qp(काष्ठा ib_pd *pd,
				 काष्ठा ib_qp_init_attr *qp_init_attr,
				 स्थिर अक्षर *caller)
अणु
	काष्ठा ib_device *device = pd ? pd->device : qp_init_attr->xrcd->device;
	काष्ठा ib_qp *qp;
	पूर्णांक ret;

	अगर (qp_init_attr->rwq_ind_tbl &&
	    (qp_init_attr->recv_cq ||
	    qp_init_attr->srq || qp_init_attr->cap.max_recv_wr ||
	    qp_init_attr->cap.max_recv_sge))
		वापस ERR_PTR(-EINVAL);

	अगर ((qp_init_attr->create_flags & IB_QP_CREATE_INTEGRITY_EN) &&
	    !(device->attrs.device_cap_flags & IB_DEVICE_INTEGRITY_HANDOVER))
		वापस ERR_PTR(-EINVAL);

	/*
	 * If the callers is using the RDMA API calculate the resources
	 * needed क्रम the RDMA READ/WRITE operations.
	 *
	 * Note that these callers need to pass in a port number.
	 */
	अगर (qp_init_attr->cap.max_rdma_ctxs)
		rdma_rw_init_qp(device, qp_init_attr);

	qp = _ib_create_qp(device, pd, qp_init_attr, शून्य, शून्य, caller);
	अगर (IS_ERR(qp))
		वापस qp;

	ret = ib_create_qp_security(qp, device);
	अगर (ret)
		जाओ err;

	अगर (qp_init_attr->qp_type == IB_QPT_XRC_TGT) अणु
		काष्ठा ib_qp *xrc_qp =
			create_xrc_qp_user(qp, qp_init_attr);

		अगर (IS_ERR(xrc_qp)) अणु
			ret = PTR_ERR(xrc_qp);
			जाओ err;
		पूर्ण
		वापस xrc_qp;
	पूर्ण

	qp->event_handler = qp_init_attr->event_handler;
	qp->qp_context = qp_init_attr->qp_context;
	अगर (qp_init_attr->qp_type == IB_QPT_XRC_INI) अणु
		qp->recv_cq = शून्य;
		qp->srq = शून्य;
	पूर्ण अन्यथा अणु
		qp->recv_cq = qp_init_attr->recv_cq;
		अगर (qp_init_attr->recv_cq)
			atomic_inc(&qp_init_attr->recv_cq->usecnt);
		qp->srq = qp_init_attr->srq;
		अगर (qp->srq)
			atomic_inc(&qp_init_attr->srq->usecnt);
	पूर्ण

	qp->send_cq = qp_init_attr->send_cq;
	qp->xrcd    = शून्य;

	atomic_inc(&pd->usecnt);
	अगर (qp_init_attr->send_cq)
		atomic_inc(&qp_init_attr->send_cq->usecnt);
	अगर (qp_init_attr->rwq_ind_tbl)
		atomic_inc(&qp->rwq_ind_tbl->usecnt);

	अगर (qp_init_attr->cap.max_rdma_ctxs) अणु
		ret = rdma_rw_init_mrs(qp, qp_init_attr);
		अगर (ret)
			जाओ err;
	पूर्ण

	/*
	 * Note: all hw drivers guarantee that max_send_sge is lower than
	 * the device RDMA WRITE SGE limit but not all hw drivers ensure that
	 * max_send_sge <= max_sge_rd.
	 */
	qp->max_ग_लिखो_sge = qp_init_attr->cap.max_send_sge;
	qp->max_पढ़ो_sge = min_t(u32, qp_init_attr->cap.max_send_sge,
				 device->attrs.max_sge_rd);
	अगर (qp_init_attr->create_flags & IB_QP_CREATE_INTEGRITY_EN)
		qp->पूर्णांकegrity_en = true;

	वापस qp;

err:
	ib_destroy_qp(qp);
	वापस ERR_PTR(ret);

पूर्ण
EXPORT_SYMBOL(ib_create_named_qp);

अटल स्थिर काष्ठा अणु
	पूर्णांक			valid;
	क्रमागत ib_qp_attr_mask	req_param[IB_QPT_MAX];
	क्रमागत ib_qp_attr_mask	opt_param[IB_QPT_MAX];
पूर्ण qp_state_table[IB_QPS_ERR + 1][IB_QPS_ERR + 1] = अणु
	[IB_QPS_RESET] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_INIT]  = अणु
			.valid = 1,
			.req_param = अणु
				[IB_QPT_UD]  = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_QKEY),
				[IB_QPT_RAW_PACKET] = IB_QP_PORT,
				[IB_QPT_UC]  = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_RC]  = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_XRC_INI] = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_XRC_TGT] = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_SMI] = (IB_QP_PKEY_INDEX		|
						IB_QP_QKEY),
				[IB_QPT_GSI] = (IB_QP_PKEY_INDEX		|
						IB_QP_QKEY),
			पूर्ण
		पूर्ण,
	पूर्ण,
	[IB_QPS_INIT]  = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR] =   अणु .valid = 1 पूर्ण,
		[IB_QPS_INIT]  = अणु
			.valid = 1,
			.opt_param = अणु
				[IB_QPT_UD]  = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_QKEY),
				[IB_QPT_UC]  = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_RC]  = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_XRC_INI] = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_XRC_TGT] = (IB_QP_PKEY_INDEX		|
						IB_QP_PORT			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_SMI] = (IB_QP_PKEY_INDEX		|
						IB_QP_QKEY),
				[IB_QPT_GSI] = (IB_QP_PKEY_INDEX		|
						IB_QP_QKEY),
			पूर्ण
		पूर्ण,
		[IB_QPS_RTR]   = अणु
			.valid = 1,
			.req_param = अणु
				[IB_QPT_UC]  = (IB_QP_AV			|
						IB_QP_PATH_MTU			|
						IB_QP_DEST_QPN			|
						IB_QP_RQ_PSN),
				[IB_QPT_RC]  = (IB_QP_AV			|
						IB_QP_PATH_MTU			|
						IB_QP_DEST_QPN			|
						IB_QP_RQ_PSN			|
						IB_QP_MAX_DEST_RD_ATOMIC	|
						IB_QP_MIN_RNR_TIMER),
				[IB_QPT_XRC_INI] = (IB_QP_AV			|
						IB_QP_PATH_MTU			|
						IB_QP_DEST_QPN			|
						IB_QP_RQ_PSN),
				[IB_QPT_XRC_TGT] = (IB_QP_AV			|
						IB_QP_PATH_MTU			|
						IB_QP_DEST_QPN			|
						IB_QP_RQ_PSN			|
						IB_QP_MAX_DEST_RD_ATOMIC	|
						IB_QP_MIN_RNR_TIMER),
			पूर्ण,
			.opt_param = अणु
				 [IB_QPT_UD]  = (IB_QP_PKEY_INDEX		|
						 IB_QP_QKEY),
				 [IB_QPT_UC]  = (IB_QP_ALT_PATH			|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_PKEY_INDEX),
				 [IB_QPT_RC]  = (IB_QP_ALT_PATH			|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_PKEY_INDEX),
				 [IB_QPT_XRC_INI] = (IB_QP_ALT_PATH		|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_PKEY_INDEX),
				 [IB_QPT_XRC_TGT] = (IB_QP_ALT_PATH		|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_PKEY_INDEX),
				 [IB_QPT_SMI] = (IB_QP_PKEY_INDEX		|
						 IB_QP_QKEY),
				 [IB_QPT_GSI] = (IB_QP_PKEY_INDEX		|
						 IB_QP_QKEY),
			 पूर्ण,
		पूर्ण,
	पूर्ण,
	[IB_QPS_RTR]   = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR] =   अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.req_param = अणु
				[IB_QPT_UD]  = IB_QP_SQ_PSN,
				[IB_QPT_UC]  = IB_QP_SQ_PSN,
				[IB_QPT_RC]  = (IB_QP_TIMEOUT			|
						IB_QP_RETRY_CNT			|
						IB_QP_RNR_RETRY			|
						IB_QP_SQ_PSN			|
						IB_QP_MAX_QP_RD_ATOMIC),
				[IB_QPT_XRC_INI] = (IB_QP_TIMEOUT		|
						IB_QP_RETRY_CNT			|
						IB_QP_RNR_RETRY			|
						IB_QP_SQ_PSN			|
						IB_QP_MAX_QP_RD_ATOMIC),
				[IB_QPT_XRC_TGT] = (IB_QP_TIMEOUT		|
						IB_QP_SQ_PSN),
				[IB_QPT_SMI] = IB_QP_SQ_PSN,
				[IB_QPT_GSI] = IB_QP_SQ_PSN,
			पूर्ण,
			.opt_param = अणु
				 [IB_QPT_UD]  = (IB_QP_CUR_STATE		|
						 IB_QP_QKEY),
				 [IB_QPT_UC]  = (IB_QP_CUR_STATE		|
						 IB_QP_ALT_PATH			|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_PATH_MIG_STATE),
				 [IB_QPT_RC]  = (IB_QP_CUR_STATE		|
						 IB_QP_ALT_PATH			|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_MIN_RNR_TIMER		|
						 IB_QP_PATH_MIG_STATE),
				 [IB_QPT_XRC_INI] = (IB_QP_CUR_STATE		|
						 IB_QP_ALT_PATH			|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_PATH_MIG_STATE),
				 [IB_QPT_XRC_TGT] = (IB_QP_CUR_STATE		|
						 IB_QP_ALT_PATH			|
						 IB_QP_ACCESS_FLAGS		|
						 IB_QP_MIN_RNR_TIMER		|
						 IB_QP_PATH_MIG_STATE),
				 [IB_QPT_SMI] = (IB_QP_CUR_STATE		|
						 IB_QP_QKEY),
				 [IB_QPT_GSI] = (IB_QP_CUR_STATE		|
						 IB_QP_QKEY),
				 [IB_QPT_RAW_PACKET] = IB_QP_RATE_LIMIT,
			 पूर्ण
		पूर्ण
	पूर्ण,
	[IB_QPS_RTS]   = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR] =   अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.opt_param = अणु
				[IB_QPT_UD]  = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
				[IB_QPT_UC]  = (IB_QP_CUR_STATE			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_ALT_PATH			|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_RC]  = (IB_QP_CUR_STATE			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_ALT_PATH			|
						IB_QP_PATH_MIG_STATE		|
						IB_QP_MIN_RNR_TIMER),
				[IB_QPT_XRC_INI] = (IB_QP_CUR_STATE		|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_ALT_PATH			|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_XRC_TGT] = (IB_QP_CUR_STATE		|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_ALT_PATH			|
						IB_QP_PATH_MIG_STATE		|
						IB_QP_MIN_RNR_TIMER),
				[IB_QPT_SMI] = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
				[IB_QPT_GSI] = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
				[IB_QPT_RAW_PACKET] = IB_QP_RATE_LIMIT,
			पूर्ण
		पूर्ण,
		[IB_QPS_SQD]   = अणु
			.valid = 1,
			.opt_param = अणु
				[IB_QPT_UD]  = IB_QP_EN_SQD_ASYNC_NOTIFY,
				[IB_QPT_UC]  = IB_QP_EN_SQD_ASYNC_NOTIFY,
				[IB_QPT_RC]  = IB_QP_EN_SQD_ASYNC_NOTIFY,
				[IB_QPT_XRC_INI] = IB_QP_EN_SQD_ASYNC_NOTIFY,
				[IB_QPT_XRC_TGT] = IB_QP_EN_SQD_ASYNC_NOTIFY, /* ??? */
				[IB_QPT_SMI] = IB_QP_EN_SQD_ASYNC_NOTIFY,
				[IB_QPT_GSI] = IB_QP_EN_SQD_ASYNC_NOTIFY
			पूर्ण
		पूर्ण,
	पूर्ण,
	[IB_QPS_SQD]   = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR] =   अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.opt_param = अणु
				[IB_QPT_UD]  = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
				[IB_QPT_UC]  = (IB_QP_CUR_STATE			|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_RC]  = (IB_QP_CUR_STATE			|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_MIN_RNR_TIMER		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_XRC_INI] = (IB_QP_CUR_STATE		|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_XRC_TGT] = (IB_QP_CUR_STATE		|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_MIN_RNR_TIMER		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_SMI] = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
				[IB_QPT_GSI] = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
			पूर्ण
		पूर्ण,
		[IB_QPS_SQD]   = अणु
			.valid = 1,
			.opt_param = अणु
				[IB_QPT_UD]  = (IB_QP_PKEY_INDEX		|
						IB_QP_QKEY),
				[IB_QPT_UC]  = (IB_QP_AV			|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_PKEY_INDEX		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_RC]  = (IB_QP_PORT			|
						IB_QP_AV			|
						IB_QP_TIMEOUT			|
						IB_QP_RETRY_CNT			|
						IB_QP_RNR_RETRY			|
						IB_QP_MAX_QP_RD_ATOMIC		|
						IB_QP_MAX_DEST_RD_ATOMIC	|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_PKEY_INDEX		|
						IB_QP_MIN_RNR_TIMER		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_XRC_INI] = (IB_QP_PORT			|
						IB_QP_AV			|
						IB_QP_TIMEOUT			|
						IB_QP_RETRY_CNT			|
						IB_QP_RNR_RETRY			|
						IB_QP_MAX_QP_RD_ATOMIC		|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_PKEY_INDEX		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_XRC_TGT] = (IB_QP_PORT			|
						IB_QP_AV			|
						IB_QP_TIMEOUT			|
						IB_QP_MAX_DEST_RD_ATOMIC	|
						IB_QP_ALT_PATH			|
						IB_QP_ACCESS_FLAGS		|
						IB_QP_PKEY_INDEX		|
						IB_QP_MIN_RNR_TIMER		|
						IB_QP_PATH_MIG_STATE),
				[IB_QPT_SMI] = (IB_QP_PKEY_INDEX		|
						IB_QP_QKEY),
				[IB_QPT_GSI] = (IB_QP_PKEY_INDEX		|
						IB_QP_QKEY),
			पूर्ण
		पूर्ण
	पूर्ण,
	[IB_QPS_SQE]   = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR] =   अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.opt_param = अणु
				[IB_QPT_UD]  = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
				[IB_QPT_UC]  = (IB_QP_CUR_STATE			|
						IB_QP_ACCESS_FLAGS),
				[IB_QPT_SMI] = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
				[IB_QPT_GSI] = (IB_QP_CUR_STATE			|
						IB_QP_QKEY),
			पूर्ण
		पूर्ण
	पूर्ण,
	[IB_QPS_ERR] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR] =   अणु .valid = 1 पूर्ण
	पूर्ण
पूर्ण;

bool ib_modअगरy_qp_is_ok(क्रमागत ib_qp_state cur_state, क्रमागत ib_qp_state next_state,
			क्रमागत ib_qp_type type, क्रमागत ib_qp_attr_mask mask)
अणु
	क्रमागत ib_qp_attr_mask req_param, opt_param;

	अगर (mask & IB_QP_CUR_STATE  &&
	    cur_state != IB_QPS_RTR && cur_state != IB_QPS_RTS &&
	    cur_state != IB_QPS_SQD && cur_state != IB_QPS_SQE)
		वापस false;

	अगर (!qp_state_table[cur_state][next_state].valid)
		वापस false;

	req_param = qp_state_table[cur_state][next_state].req_param[type];
	opt_param = qp_state_table[cur_state][next_state].opt_param[type];

	अगर ((mask & req_param) != req_param)
		वापस false;

	अगर (mask & ~(req_param | opt_param | IB_QP_STATE))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_qp_is_ok);

/**
 * ib_resolve_eth_dmac - Resolve destination mac address
 * @device:		Device to consider
 * @ah_attr:		address handle attribute which describes the
 *			source and destination parameters
 * ib_resolve_eth_dmac() resolves destination mac address and L3 hop limit It
 * वापसs 0 on success or appropriate error code. It initializes the
 * necessary ah_attr fields when call is successful.
 */
अटल पूर्णांक ib_resolve_eth_dmac(काष्ठा ib_device *device,
			       काष्ठा rdma_ah_attr *ah_attr)
अणु
	पूर्णांक ret = 0;

	अगर (rdma_is_multicast_addr((काष्ठा in6_addr *)ah_attr->grh.dgid.raw)) अणु
		अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)ah_attr->grh.dgid.raw)) अणु
			__be32 addr = 0;

			स_नकल(&addr, ah_attr->grh.dgid.raw + 12, 4);
			ip_eth_mc_map(addr, (अक्षर *)ah_attr->roce.dmac);
		पूर्ण अन्यथा अणु
			ipv6_eth_mc_map((काष्ठा in6_addr *)ah_attr->grh.dgid.raw,
					(अक्षर *)ah_attr->roce.dmac);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ib_resolve_unicast_gid_dmac(device, ah_attr);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool is_qp_type_connected(स्थिर काष्ठा ib_qp *qp)
अणु
	वापस (qp->qp_type == IB_QPT_UC ||
		qp->qp_type == IB_QPT_RC ||
		qp->qp_type == IB_QPT_XRC_INI ||
		qp->qp_type == IB_QPT_XRC_TGT);
पूर्ण

/*
 * IB core पूर्णांकernal function to perक्रमm QP attributes modअगरication.
 */
अटल पूर्णांक _ib_modअगरy_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *attr,
			 पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	u32 port = attr_mask & IB_QP_PORT ? attr->port_num : qp->port;
	स्थिर काष्ठा ib_gid_attr *old_sgid_attr_av;
	स्थिर काष्ठा ib_gid_attr *old_sgid_attr_alt_av;
	पूर्णांक ret;

	attr->xmit_slave = शून्य;
	अगर (attr_mask & IB_QP_AV) अणु
		ret = rdma_fill_sgid_attr(qp->device, &attr->ah_attr,
					  &old_sgid_attr_av);
		अगर (ret)
			वापस ret;

		अगर (attr->ah_attr.type == RDMA_AH_ATTR_TYPE_ROCE &&
		    is_qp_type_connected(qp)) अणु
			काष्ठा net_device *slave;

			/*
			 * If the user provided the qp_attr then we have to
			 * resolve it. Kerne users have to provide alपढ़ोy
			 * resolved rdma_ah_attr's.
			 */
			अगर (udata) अणु
				ret = ib_resolve_eth_dmac(qp->device,
							  &attr->ah_attr);
				अगर (ret)
					जाओ out_av;
			पूर्ण
			slave = rdma_lag_get_ah_roce_slave(qp->device,
							   &attr->ah_attr,
							   GFP_KERNEL);
			अगर (IS_ERR(slave)) अणु
				ret = PTR_ERR(slave);
				जाओ out_av;
			पूर्ण
			attr->xmit_slave = slave;
		पूर्ण
	पूर्ण
	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		/*
		 * FIXME: This करोes not track the migration state, so अगर the
		 * user loads a new alternate path after the HW has migrated
		 * from primary->alternate we will keep the wrong
		 * references. This is OK क्रम IB because the reference
		 * counting करोes not serve any functional purpose.
		 */
		ret = rdma_fill_sgid_attr(qp->device, &attr->alt_ah_attr,
					  &old_sgid_attr_alt_av);
		अगर (ret)
			जाओ out_av;

		/*
		 * Today the core code can only handle alternate paths and APM
		 * क्रम IB. Ban them in roce mode.
		 */
		अगर (!(rdma_protocol_ib(qp->device,
				       attr->alt_ah_attr.port_num) &&
		      rdma_protocol_ib(qp->device, port))) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rdma_ib_or_roce(qp->device, port)) अणु
		अगर (attr_mask & IB_QP_RQ_PSN && attr->rq_psn & ~0xffffff) अणु
			dev_warn(&qp->device->dev,
				 "%s rq_psn overflow, masking to 24 bits\n",
				 __func__);
			attr->rq_psn &= 0xffffff;
		पूर्ण

		अगर (attr_mask & IB_QP_SQ_PSN && attr->sq_psn & ~0xffffff) अणु
			dev_warn(&qp->device->dev,
				 " %s sq_psn overflow, masking to 24 bits\n",
				 __func__);
			attr->sq_psn &= 0xffffff;
		पूर्ण
	पूर्ण

	/*
	 * Bind this qp to a counter स्वतःmatically based on the rdma counter
	 * rules. This only set in RST2INIT with port specअगरied
	 */
	अगर (!qp->counter && (attr_mask & IB_QP_PORT) &&
	    ((attr_mask & IB_QP_STATE) && attr->qp_state == IB_QPS_INIT))
		rdma_counter_bind_qp_स्वतः(qp, attr->port_num);

	ret = ib_security_modअगरy_qp(qp, attr, attr_mask, udata);
	अगर (ret)
		जाओ out;

	अगर (attr_mask & IB_QP_PORT)
		qp->port = attr->port_num;
	अगर (attr_mask & IB_QP_AV)
		qp->av_sgid_attr =
			rdma_update_sgid_attr(&attr->ah_attr, qp->av_sgid_attr);
	अगर (attr_mask & IB_QP_ALT_PATH)
		qp->alt_path_sgid_attr = rdma_update_sgid_attr(
			&attr->alt_ah_attr, qp->alt_path_sgid_attr);

out:
	अगर (attr_mask & IB_QP_ALT_PATH)
		rdma_unfill_sgid_attr(&attr->alt_ah_attr, old_sgid_attr_alt_av);
out_av:
	अगर (attr_mask & IB_QP_AV) अणु
		rdma_lag_put_ah_roce_slave(attr->xmit_slave);
		rdma_unfill_sgid_attr(&attr->ah_attr, old_sgid_attr_av);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ib_modअगरy_qp_with_udata - Modअगरies the attributes क्रम the specअगरied QP.
 * @ib_qp: The QP to modअगरy.
 * @attr: On input, specअगरies the QP attributes to modअगरy.  On output,
 *   the current values of selected QP attributes are वापसed.
 * @attr_mask: A bit-mask used to specअगरy which attributes of the QP
 *   are being modअगरied.
 * @udata: poपूर्णांकer to user's input output buffer inक्रमmation
 *   are being modअगरied.
 * It वापसs 0 on success and वापसs appropriate error code on error.
 */
पूर्णांक ib_modअगरy_qp_with_udata(काष्ठा ib_qp *ib_qp, काष्ठा ib_qp_attr *attr,
			    पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	वापस _ib_modअगरy_qp(ib_qp->real_qp, attr, attr_mask, udata);
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_qp_with_udata);

पूर्णांक ib_get_eth_speed(काष्ठा ib_device *dev, u32 port_num, u16 *speed, u8 *width)
अणु
	पूर्णांक rc;
	u32 netdev_speed;
	काष्ठा net_device *netdev;
	काष्ठा ethtool_link_ksettings lksettings;

	अगर (rdma_port_get_link_layer(dev, port_num) != IB_LINK_LAYER_ETHERNET)
		वापस -EINVAL;

	netdev = ib_device_get_netdev(dev, port_num);
	अगर (!netdev)
		वापस -ENODEV;

	rtnl_lock();
	rc = __ethtool_get_link_ksettings(netdev, &lksettings);
	rtnl_unlock();

	dev_put(netdev);

	अगर (!rc && lksettings.base.speed != (u32)SPEED_UNKNOWN) अणु
		netdev_speed = lksettings.base.speed;
	पूर्ण अन्यथा अणु
		netdev_speed = SPEED_1000;
		pr_warn("%s speed is unknown, defaulting to %d\n", netdev->name,
			netdev_speed);
	पूर्ण

	अगर (netdev_speed <= SPEED_1000) अणु
		*width = IB_WIDTH_1X;
		*speed = IB_SPEED_SDR;
	पूर्ण अन्यथा अगर (netdev_speed <= SPEED_10000) अणु
		*width = IB_WIDTH_1X;
		*speed = IB_SPEED_FDR10;
	पूर्ण अन्यथा अगर (netdev_speed <= SPEED_20000) अणु
		*width = IB_WIDTH_4X;
		*speed = IB_SPEED_DDR;
	पूर्ण अन्यथा अगर (netdev_speed <= SPEED_25000) अणु
		*width = IB_WIDTH_1X;
		*speed = IB_SPEED_EDR;
	पूर्ण अन्यथा अगर (netdev_speed <= SPEED_40000) अणु
		*width = IB_WIDTH_4X;
		*speed = IB_SPEED_FDR10;
	पूर्ण अन्यथा अणु
		*width = IB_WIDTH_4X;
		*speed = IB_SPEED_EDR;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_get_eth_speed);

पूर्णांक ib_modअगरy_qp(काष्ठा ib_qp *qp,
		 काष्ठा ib_qp_attr *qp_attr,
		 पूर्णांक qp_attr_mask)
अणु
	वापस _ib_modअगरy_qp(qp->real_qp, qp_attr, qp_attr_mask, शून्य);
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_qp);

पूर्णांक ib_query_qp(काष्ठा ib_qp *qp,
		काष्ठा ib_qp_attr *qp_attr,
		पूर्णांक qp_attr_mask,
		काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	qp_attr->ah_attr.grh.sgid_attr = शून्य;
	qp_attr->alt_ah_attr.grh.sgid_attr = शून्य;

	वापस qp->device->ops.query_qp ?
		qp->device->ops.query_qp(qp->real_qp, qp_attr, qp_attr_mask,
					 qp_init_attr) : -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(ib_query_qp);

पूर्णांक ib_बंद_qp(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp *real_qp;
	अचिन्हित दीर्घ flags;

	real_qp = qp->real_qp;
	अगर (real_qp == qp)
		वापस -EINVAL;

	spin_lock_irqsave(&real_qp->device->qp_खोलो_list_lock, flags);
	list_del(&qp->खोलो_list);
	spin_unlock_irqrestore(&real_qp->device->qp_खोलो_list_lock, flags);

	atomic_dec(&real_qp->usecnt);
	अगर (qp->qp_sec)
		ib_बंद_shared_qp_security(qp->qp_sec);
	kमुक्त(qp);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_बंद_qp);

अटल पूर्णांक __ib_destroy_shared_qp(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_xrcd *xrcd;
	काष्ठा ib_qp *real_qp;
	पूर्णांक ret;

	real_qp = qp->real_qp;
	xrcd = real_qp->xrcd;
	करोwn_ग_लिखो(&xrcd->tgt_qps_rwsem);
	ib_बंद_qp(qp);
	अगर (atomic_पढ़ो(&real_qp->usecnt) == 0)
		xa_erase(&xrcd->tgt_qps, real_qp->qp_num);
	अन्यथा
		real_qp = शून्य;
	up_ग_लिखो(&xrcd->tgt_qps_rwsem);

	अगर (real_qp) अणु
		ret = ib_destroy_qp(real_qp);
		अगर (!ret)
			atomic_dec(&xrcd->usecnt);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ib_destroy_qp_user(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata)
अणु
	स्थिर काष्ठा ib_gid_attr *alt_path_sgid_attr = qp->alt_path_sgid_attr;
	स्थिर काष्ठा ib_gid_attr *av_sgid_attr = qp->av_sgid_attr;
	काष्ठा ib_pd *pd;
	काष्ठा ib_cq *scq, *rcq;
	काष्ठा ib_srq *srq;
	काष्ठा ib_rwq_ind_table *ind_tbl;
	काष्ठा ib_qp_security *sec;
	पूर्णांक ret;

	WARN_ON_ONCE(qp->mrs_used > 0);

	अगर (atomic_पढ़ो(&qp->usecnt))
		वापस -EBUSY;

	अगर (qp->real_qp != qp)
		वापस __ib_destroy_shared_qp(qp);

	pd   = qp->pd;
	scq  = qp->send_cq;
	rcq  = qp->recv_cq;
	srq  = qp->srq;
	ind_tbl = qp->rwq_ind_tbl;
	sec  = qp->qp_sec;
	अगर (sec)
		ib_destroy_qp_security_begin(sec);

	अगर (!qp->uobject)
		rdma_rw_cleanup_mrs(qp);

	rdma_counter_unbind_qp(qp, true);
	rdma_restrack_del(&qp->res);
	ret = qp->device->ops.destroy_qp(qp, udata);
	अगर (!ret) अणु
		अगर (alt_path_sgid_attr)
			rdma_put_gid_attr(alt_path_sgid_attr);
		अगर (av_sgid_attr)
			rdma_put_gid_attr(av_sgid_attr);
		अगर (pd)
			atomic_dec(&pd->usecnt);
		अगर (scq)
			atomic_dec(&scq->usecnt);
		अगर (rcq)
			atomic_dec(&rcq->usecnt);
		अगर (srq)
			atomic_dec(&srq->usecnt);
		अगर (ind_tbl)
			atomic_dec(&ind_tbl->usecnt);
		अगर (sec)
			ib_destroy_qp_security_end(sec);
	पूर्ण अन्यथा अणु
		अगर (sec)
			ib_destroy_qp_security_पात(sec);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_destroy_qp_user);

/* Completion queues */

काष्ठा ib_cq *__ib_create_cq(काष्ठा ib_device *device,
			     ib_comp_handler comp_handler,
			     व्योम (*event_handler)(काष्ठा ib_event *, व्योम *),
			     व्योम *cq_context,
			     स्थिर काष्ठा ib_cq_init_attr *cq_attr,
			     स्थिर अक्षर *caller)
अणु
	काष्ठा ib_cq *cq;
	पूर्णांक ret;

	cq = rdma_zalloc_drv_obj(device, ib_cq);
	अगर (!cq)
		वापस ERR_PTR(-ENOMEM);

	cq->device = device;
	cq->uobject = शून्य;
	cq->comp_handler = comp_handler;
	cq->event_handler = event_handler;
	cq->cq_context = cq_context;
	atomic_set(&cq->usecnt, 0);

	rdma_restrack_new(&cq->res, RDMA_RESTRACK_CQ);
	rdma_restrack_set_name(&cq->res, caller);

	ret = device->ops.create_cq(cq, cq_attr, शून्य);
	अगर (ret) अणु
		rdma_restrack_put(&cq->res);
		kमुक्त(cq);
		वापस ERR_PTR(ret);
	पूर्ण

	rdma_restrack_add(&cq->res);
	वापस cq;
पूर्ण
EXPORT_SYMBOL(__ib_create_cq);

पूर्णांक rdma_set_cq_moderation(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period)
अणु
	अगर (cq->shared)
		वापस -EOPNOTSUPP;

	वापस cq->device->ops.modअगरy_cq ?
		cq->device->ops.modअगरy_cq(cq, cq_count,
					  cq_period) : -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(rdma_set_cq_moderation);

पूर्णांक ib_destroy_cq_user(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(cq->shared))
		वापस -EOPNOTSUPP;

	अगर (atomic_पढ़ो(&cq->usecnt))
		वापस -EBUSY;

	ret = cq->device->ops.destroy_cq(cq, udata);
	अगर (ret)
		वापस ret;

	rdma_restrack_del(&cq->res);
	kमुक्त(cq);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_destroy_cq_user);

पूर्णांक ib_resize_cq(काष्ठा ib_cq *cq, पूर्णांक cqe)
अणु
	अगर (cq->shared)
		वापस -EOPNOTSUPP;

	वापस cq->device->ops.resize_cq ?
		cq->device->ops.resize_cq(cq, cqe, शून्य) : -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(ib_resize_cq);

/* Memory regions */

काष्ठा ib_mr *ib_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
			     u64 virt_addr, पूर्णांक access_flags)
अणु
	काष्ठा ib_mr *mr;

	अगर (access_flags & IB_ACCESS_ON_DEMAND) अणु
		अगर (!(pd->device->attrs.device_cap_flags &
		      IB_DEVICE_ON_DEMAND_PAGING)) अणु
			pr_debug("ODP support not available\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	mr = pd->device->ops.reg_user_mr(pd, start, length, virt_addr,
					 access_flags, शून्य);

	अगर (IS_ERR(mr))
		वापस mr;

	mr->device = pd->device;
	mr->pd = pd;
	mr->dm = शून्य;
	atomic_inc(&pd->usecnt);

	rdma_restrack_new(&mr->res, RDMA_RESTRACK_MR);
	rdma_restrack_parent_name(&mr->res, &pd->res);
	rdma_restrack_add(&mr->res);

	वापस mr;
पूर्ण
EXPORT_SYMBOL(ib_reg_user_mr);

पूर्णांक ib_advise_mr(काष्ठा ib_pd *pd, क्रमागत ib_uverbs_advise_mr_advice advice,
		 u32 flags, काष्ठा ib_sge *sg_list, u32 num_sge)
अणु
	अगर (!pd->device->ops.advise_mr)
		वापस -EOPNOTSUPP;

	अगर (!num_sge)
		वापस 0;

	वापस pd->device->ops.advise_mr(pd, advice, flags, sg_list, num_sge,
					 शून्य);
पूर्ण
EXPORT_SYMBOL(ib_advise_mr);

पूर्णांक ib_dereg_mr_user(काष्ठा ib_mr *mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_pd *pd = mr->pd;
	काष्ठा ib_dm *dm = mr->dm;
	काष्ठा ib_sig_attrs *sig_attrs = mr->sig_attrs;
	पूर्णांक ret;

	trace_mr_dereg(mr);
	rdma_restrack_del(&mr->res);
	ret = mr->device->ops.dereg_mr(mr, udata);
	अगर (!ret) अणु
		atomic_dec(&pd->usecnt);
		अगर (dm)
			atomic_dec(&dm->usecnt);
		kमुक्त(sig_attrs);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_dereg_mr_user);

/**
 * ib_alloc_mr() - Allocates a memory region
 * @pd:            protection करोमुख्य associated with the region
 * @mr_type:       memory region type
 * @max_num_sg:    maximum sg entries available क्रम registration.
 *
 * Notes:
 * Memory रेजिस्टरation page/sg lists must not exceed max_num_sg.
 * For mr_type IB_MR_TYPE_MEM_REG, the total length cannot exceed
 * max_num_sg * used_page_size.
 *
 */
काष्ठा ib_mr *ib_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			  u32 max_num_sg)
अणु
	काष्ठा ib_mr *mr;

	अगर (!pd->device->ops.alloc_mr) अणु
		mr = ERR_PTR(-EOPNOTSUPP);
		जाओ out;
	पूर्ण

	अगर (mr_type == IB_MR_TYPE_INTEGRITY) अणु
		WARN_ON_ONCE(1);
		mr = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	mr = pd->device->ops.alloc_mr(pd, mr_type, max_num_sg);
	अगर (IS_ERR(mr))
		जाओ out;

	mr->device = pd->device;
	mr->pd = pd;
	mr->dm = शून्य;
	mr->uobject = शून्य;
	atomic_inc(&pd->usecnt);
	mr->need_inval = false;
	mr->type = mr_type;
	mr->sig_attrs = शून्य;

	rdma_restrack_new(&mr->res, RDMA_RESTRACK_MR);
	rdma_restrack_parent_name(&mr->res, &pd->res);
	rdma_restrack_add(&mr->res);
out:
	trace_mr_alloc(pd, mr_type, max_num_sg, mr);
	वापस mr;
पूर्ण
EXPORT_SYMBOL(ib_alloc_mr);

/**
 * ib_alloc_mr_पूर्णांकegrity() - Allocates an पूर्णांकegrity memory region
 * @pd:                      protection करोमुख्य associated with the region
 * @max_num_data_sg:         maximum data sg entries available क्रम registration
 * @max_num_meta_sg:         maximum metadata sg entries available क्रम
 *                           registration
 *
 * Notes:
 * Memory registration page/sg lists must not exceed max_num_sg,
 * also the पूर्णांकegrity page/sg lists must not exceed max_num_meta_sg.
 *
 */
काष्ठा ib_mr *ib_alloc_mr_पूर्णांकegrity(काष्ठा ib_pd *pd,
				    u32 max_num_data_sg,
				    u32 max_num_meta_sg)
अणु
	काष्ठा ib_mr *mr;
	काष्ठा ib_sig_attrs *sig_attrs;

	अगर (!pd->device->ops.alloc_mr_पूर्णांकegrity ||
	    !pd->device->ops.map_mr_sg_pi) अणु
		mr = ERR_PTR(-EOPNOTSUPP);
		जाओ out;
	पूर्ण

	अगर (!max_num_meta_sg) अणु
		mr = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	sig_attrs = kzalloc(माप(काष्ठा ib_sig_attrs), GFP_KERNEL);
	अगर (!sig_attrs) अणु
		mr = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	mr = pd->device->ops.alloc_mr_पूर्णांकegrity(pd, max_num_data_sg,
						max_num_meta_sg);
	अगर (IS_ERR(mr)) अणु
		kमुक्त(sig_attrs);
		जाओ out;
	पूर्ण

	mr->device = pd->device;
	mr->pd = pd;
	mr->dm = शून्य;
	mr->uobject = शून्य;
	atomic_inc(&pd->usecnt);
	mr->need_inval = false;
	mr->type = IB_MR_TYPE_INTEGRITY;
	mr->sig_attrs = sig_attrs;

	rdma_restrack_new(&mr->res, RDMA_RESTRACK_MR);
	rdma_restrack_parent_name(&mr->res, &pd->res);
	rdma_restrack_add(&mr->res);
out:
	trace_mr_पूर्णांकeg_alloc(pd, max_num_data_sg, max_num_meta_sg, mr);
	वापस mr;
पूर्ण
EXPORT_SYMBOL(ib_alloc_mr_पूर्णांकegrity);

/* Multicast groups */

अटल bool is_valid_mcast_lid(काष्ठा ib_qp *qp, u16 lid)
अणु
	काष्ठा ib_qp_init_attr init_attr = अणुपूर्ण;
	काष्ठा ib_qp_attr attr = अणुपूर्ण;
	पूर्णांक num_eth_ports = 0;
	अचिन्हित पूर्णांक port;

	/* If QP state >= init, it is asचिन्हित to a port and we can check this
	 * port only.
	 */
	अगर (!ib_query_qp(qp, &attr, IB_QP_STATE | IB_QP_PORT, &init_attr)) अणु
		अगर (attr.qp_state >= IB_QPS_INIT) अणु
			अगर (rdma_port_get_link_layer(qp->device, attr.port_num) !=
			    IB_LINK_LAYER_INFINIBAND)
				वापस true;
			जाओ lid_check;
		पूर्ण
	पूर्ण

	/* Can't get a quick answer, iterate over all ports */
	rdma_क्रम_each_port(qp->device, port)
		अगर (rdma_port_get_link_layer(qp->device, port) !=
		    IB_LINK_LAYER_INFINIBAND)
			num_eth_ports++;

	/* If we have at lease one Ethernet port, RoCE annex declares that
	 * multicast LID should be ignored. We can't tell at this step अगर the
	 * QP beदीर्घs to an IB or Ethernet port.
	 */
	अगर (num_eth_ports)
		वापस true;

	/* If all the ports are IB, we can check according to IB spec. */
lid_check:
	वापस !(lid < be16_to_cpu(IB_MULTICAST_LID_BASE) ||
		 lid == be16_to_cpu(IB_LID_PERMISSIVE));
पूर्ण

पूर्णांक ib_attach_mcast(काष्ठा ib_qp *qp, जोड़ ib_gid *gid, u16 lid)
अणु
	पूर्णांक ret;

	अगर (!qp->device->ops.attach_mcast)
		वापस -EOPNOTSUPP;

	अगर (!rdma_is_multicast_addr((काष्ठा in6_addr *)gid->raw) ||
	    qp->qp_type != IB_QPT_UD || !is_valid_mcast_lid(qp, lid))
		वापस -EINVAL;

	ret = qp->device->ops.attach_mcast(qp, gid, lid);
	अगर (!ret)
		atomic_inc(&qp->usecnt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_attach_mcast);

पूर्णांक ib_detach_mcast(काष्ठा ib_qp *qp, जोड़ ib_gid *gid, u16 lid)
अणु
	पूर्णांक ret;

	अगर (!qp->device->ops.detach_mcast)
		वापस -EOPNOTSUPP;

	अगर (!rdma_is_multicast_addr((काष्ठा in6_addr *)gid->raw) ||
	    qp->qp_type != IB_QPT_UD || !is_valid_mcast_lid(qp, lid))
		वापस -EINVAL;

	ret = qp->device->ops.detach_mcast(qp, gid, lid);
	अगर (!ret)
		atomic_dec(&qp->usecnt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_detach_mcast);

/**
 * ib_alloc_xrcd_user - Allocates an XRC करोमुख्य.
 * @device: The device on which to allocate the XRC करोमुख्य.
 * @inode: inode to connect XRCD
 * @udata: Valid user data or शून्य क्रम kernel object
 */
काष्ठा ib_xrcd *ib_alloc_xrcd_user(काष्ठा ib_device *device,
				   काष्ठा inode *inode, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_xrcd *xrcd;
	पूर्णांक ret;

	अगर (!device->ops.alloc_xrcd)
		वापस ERR_PTR(-EOPNOTSUPP);

	xrcd = rdma_zalloc_drv_obj(device, ib_xrcd);
	अगर (!xrcd)
		वापस ERR_PTR(-ENOMEM);

	xrcd->device = device;
	xrcd->inode = inode;
	atomic_set(&xrcd->usecnt, 0);
	init_rwsem(&xrcd->tgt_qps_rwsem);
	xa_init(&xrcd->tgt_qps);

	ret = device->ops.alloc_xrcd(xrcd, udata);
	अगर (ret)
		जाओ err;
	वापस xrcd;
err:
	kमुक्त(xrcd);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(ib_alloc_xrcd_user);

/**
 * ib_dealloc_xrcd_user - Deallocates an XRC करोमुख्य.
 * @xrcd: The XRC करोमुख्य to deallocate.
 * @udata: Valid user data or शून्य क्रम kernel object
 */
पूर्णांक ib_dealloc_xrcd_user(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&xrcd->usecnt))
		वापस -EBUSY;

	WARN_ON(!xa_empty(&xrcd->tgt_qps));
	ret = xrcd->device->ops.dealloc_xrcd(xrcd, udata);
	अगर (ret)
		वापस ret;
	kमुक्त(xrcd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_dealloc_xrcd_user);

/**
 * ib_create_wq - Creates a WQ associated with the specअगरied protection
 * करोमुख्य.
 * @pd: The protection करोमुख्य associated with the WQ.
 * @wq_attr: A list of initial attributes required to create the
 * WQ. If WQ creation succeeds, then the attributes are updated to
 * the actual capabilities of the created WQ.
 *
 * wq_attr->max_wr and wq_attr->max_sge determine
 * the requested size of the WQ, and set to the actual values allocated
 * on वापस.
 * If ib_create_wq() succeeds, then max_wr and max_sge will always be
 * at least as large as the requested values.
 */
काष्ठा ib_wq *ib_create_wq(काष्ठा ib_pd *pd,
			   काष्ठा ib_wq_init_attr *wq_attr)
अणु
	काष्ठा ib_wq *wq;

	अगर (!pd->device->ops.create_wq)
		वापस ERR_PTR(-EOPNOTSUPP);

	wq = pd->device->ops.create_wq(pd, wq_attr, शून्य);
	अगर (!IS_ERR(wq)) अणु
		wq->event_handler = wq_attr->event_handler;
		wq->wq_context = wq_attr->wq_context;
		wq->wq_type = wq_attr->wq_type;
		wq->cq = wq_attr->cq;
		wq->device = pd->device;
		wq->pd = pd;
		wq->uobject = शून्य;
		atomic_inc(&pd->usecnt);
		atomic_inc(&wq_attr->cq->usecnt);
		atomic_set(&wq->usecnt, 0);
	पूर्ण
	वापस wq;
पूर्ण
EXPORT_SYMBOL(ib_create_wq);

/**
 * ib_destroy_wq_user - Destroys the specअगरied user WQ.
 * @wq: The WQ to destroy.
 * @udata: Valid user data
 */
पूर्णांक ib_destroy_wq_user(काष्ठा ib_wq *wq, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_cq *cq = wq->cq;
	काष्ठा ib_pd *pd = wq->pd;
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&wq->usecnt))
		वापस -EBUSY;

	ret = wq->device->ops.destroy_wq(wq, udata);
	अगर (ret)
		वापस ret;

	atomic_dec(&pd->usecnt);
	atomic_dec(&cq->usecnt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_destroy_wq_user);

/**
 * ib_modअगरy_wq - Modअगरies the specअगरied WQ.
 * @wq: The WQ to modअगरy.
 * @wq_attr: On input, specअगरies the WQ attributes to modअगरy.
 * @wq_attr_mask: A bit-mask used to specअगरy which attributes of the WQ
 *   are being modअगरied.
 * On output, the current values of selected WQ attributes are वापसed.
 */
पूर्णांक ib_modअगरy_wq(काष्ठा ib_wq *wq, काष्ठा ib_wq_attr *wq_attr,
		 u32 wq_attr_mask)
अणु
	पूर्णांक err;

	अगर (!wq->device->ops.modअगरy_wq)
		वापस -EOPNOTSUPP;

	err = wq->device->ops.modअगरy_wq(wq, wq_attr, wq_attr_mask, शून्य);
	वापस err;
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_wq);

पूर्णांक ib_check_mr_status(काष्ठा ib_mr *mr, u32 check_mask,
		       काष्ठा ib_mr_status *mr_status)
अणु
	अगर (!mr->device->ops.check_mr_status)
		वापस -EOPNOTSUPP;

	वापस mr->device->ops.check_mr_status(mr, check_mask, mr_status);
पूर्ण
EXPORT_SYMBOL(ib_check_mr_status);

पूर्णांक ib_set_vf_link_state(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			 पूर्णांक state)
अणु
	अगर (!device->ops.set_vf_link_state)
		वापस -EOPNOTSUPP;

	वापस device->ops.set_vf_link_state(device, vf, port, state);
पूर्ण
EXPORT_SYMBOL(ib_set_vf_link_state);

पूर्णांक ib_get_vf_config(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
		     काष्ठा अगरla_vf_info *info)
अणु
	अगर (!device->ops.get_vf_config)
		वापस -EOPNOTSUPP;

	वापस device->ops.get_vf_config(device, vf, port, info);
पूर्ण
EXPORT_SYMBOL(ib_get_vf_config);

पूर्णांक ib_get_vf_stats(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
		    काष्ठा अगरla_vf_stats *stats)
अणु
	अगर (!device->ops.get_vf_stats)
		वापस -EOPNOTSUPP;

	वापस device->ops.get_vf_stats(device, vf, port, stats);
पूर्ण
EXPORT_SYMBOL(ib_get_vf_stats);

पूर्णांक ib_set_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port, u64 guid,
		   पूर्णांक type)
अणु
	अगर (!device->ops.set_vf_guid)
		वापस -EOPNOTSUPP;

	वापस device->ops.set_vf_guid(device, vf, port, guid, type);
पूर्ण
EXPORT_SYMBOL(ib_set_vf_guid);

पूर्णांक ib_get_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
		   काष्ठा अगरla_vf_guid *node_guid,
		   काष्ठा अगरla_vf_guid *port_guid)
अणु
	अगर (!device->ops.get_vf_guid)
		वापस -EOPNOTSUPP;

	वापस device->ops.get_vf_guid(device, vf, port, node_guid, port_guid);
पूर्ण
EXPORT_SYMBOL(ib_get_vf_guid);
/**
 * ib_map_mr_sg_pi() - Map the dma mapped SG lists क्रम PI (protection
 *     inक्रमmation) and set an appropriate memory region क्रम registration.
 * @mr:             memory region
 * @data_sg:        dma mapped scatterlist क्रम data
 * @data_sg_nents:  number of entries in data_sg
 * @data_sg_offset: offset in bytes पूर्णांकo data_sg
 * @meta_sg:        dma mapped scatterlist क्रम metadata
 * @meta_sg_nents:  number of entries in meta_sg
 * @meta_sg_offset: offset in bytes पूर्णांकo meta_sg
 * @page_size:      page vector desired page size
 *
 * Constraपूर्णांकs:
 * - The MR must be allocated with type IB_MR_TYPE_INTEGRITY.
 *
 * Return: 0 on success.
 *
 * After this completes successfully, the  memory region
 * is पढ़ोy क्रम registration.
 */
पूर्णांक ib_map_mr_sg_pi(काष्ठा ib_mr *mr, काष्ठा scatterlist *data_sg,
		    पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
		    काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
		    अचिन्हित पूर्णांक *meta_sg_offset, अचिन्हित पूर्णांक page_size)
अणु
	अगर (unlikely(!mr->device->ops.map_mr_sg_pi ||
		     WARN_ON_ONCE(mr->type != IB_MR_TYPE_INTEGRITY)))
		वापस -EOPNOTSUPP;

	mr->page_size = page_size;

	वापस mr->device->ops.map_mr_sg_pi(mr, data_sg, data_sg_nents,
					    data_sg_offset, meta_sg,
					    meta_sg_nents, meta_sg_offset);
पूर्ण
EXPORT_SYMBOL(ib_map_mr_sg_pi);

/**
 * ib_map_mr_sg() - Map the largest prefix of a dma mapped SG list
 *     and set it the memory region.
 * @mr:            memory region
 * @sg:            dma mapped scatterlist
 * @sg_nents:      number of entries in sg
 * @sg_offset:     offset in bytes पूर्णांकo sg
 * @page_size:     page vector desired page size
 *
 * Constraपूर्णांकs:
 *
 * - The first sg element is allowed to have an offset.
 * - Each sg element must either be aligned to page_size or भवly
 *   contiguous to the previous element. In हाल an sg element has a
 *   non-contiguous offset, the mapping prefix will not include it.
 * - The last sg element is allowed to have length less than page_size.
 * - If sg_nents total byte length exceeds the mr max_num_sge * page_size
 *   then only max_num_sg entries will be mapped.
 * - If the MR was allocated with type IB_MR_TYPE_SG_GAPS, none of these
 *   स्थिरraपूर्णांकs holds and the page_size argument is ignored.
 *
 * Returns the number of sg elements that were mapped to the memory region.
 *
 * After this completes successfully, the  memory region
 * is पढ़ोy क्रम registration.
 */
पूर्णांक ib_map_mr_sg(काष्ठा ib_mr *mr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		 अचिन्हित पूर्णांक *sg_offset, अचिन्हित पूर्णांक page_size)
अणु
	अगर (unlikely(!mr->device->ops.map_mr_sg))
		वापस -EOPNOTSUPP;

	mr->page_size = page_size;

	वापस mr->device->ops.map_mr_sg(mr, sg, sg_nents, sg_offset);
पूर्ण
EXPORT_SYMBOL(ib_map_mr_sg);

/**
 * ib_sg_to_pages() - Convert the largest prefix of a sg list
 *     to a page vector
 * @mr:            memory region
 * @sgl:           dma mapped scatterlist
 * @sg_nents:      number of entries in sg
 * @sg_offset_p:   ==== =======================================================
 *                 IN   start offset in bytes पूर्णांकo sg
 *                 OUT  offset in bytes क्रम element n of the sg of the first
 *                      byte that has not been processed where n is the वापस
 *                      value of this function.
 *                 ==== =======================================================
 * @set_page:      driver page assignment function poपूर्णांकer
 *
 * Core service helper क्रम drivers to convert the largest
 * prefix of given sg list to a page vector. The sg list
 * prefix converted is the prefix that meet the requirements
 * of ib_map_mr_sg.
 *
 * Returns the number of sg elements that were asचिन्हित to
 * a page vector.
 */
पूर्णांक ib_sg_to_pages(काष्ठा ib_mr *mr, काष्ठा scatterlist *sgl, पूर्णांक sg_nents,
		अचिन्हित पूर्णांक *sg_offset_p, पूर्णांक (*set_page)(काष्ठा ib_mr *, u64))
अणु
	काष्ठा scatterlist *sg;
	u64 last_end_dma_addr = 0;
	अचिन्हित पूर्णांक sg_offset = sg_offset_p ? *sg_offset_p : 0;
	अचिन्हित पूर्णांक last_page_off = 0;
	u64 page_mask = ~((u64)mr->page_size - 1);
	पूर्णांक i, ret;

	अगर (unlikely(sg_nents <= 0 || sg_offset > sg_dma_len(&sgl[0])))
		वापस -EINVAL;

	mr->iova = sg_dma_address(&sgl[0]) + sg_offset;
	mr->length = 0;

	क्रम_each_sg(sgl, sg, sg_nents, i) अणु
		u64 dma_addr = sg_dma_address(sg) + sg_offset;
		u64 prev_addr = dma_addr;
		अचिन्हित पूर्णांक dma_len = sg_dma_len(sg) - sg_offset;
		u64 end_dma_addr = dma_addr + dma_len;
		u64 page_addr = dma_addr & page_mask;

		/*
		 * For the second and later elements, check whether either the
		 * end of element i-1 or the start of element i is not aligned
		 * on a page boundary.
		 */
		अगर (i && (last_page_off != 0 || page_addr != dma_addr)) अणु
			/* Stop mapping अगर there is a gap. */
			अगर (last_end_dma_addr != dma_addr)
				अवरोध;

			/*
			 * Coalesce this element with the last. If it is small
			 * enough just update mr->length. Otherwise start
			 * mapping from the next page.
			 */
			जाओ next_page;
		पूर्ण

		करो अणु
			ret = set_page(mr, page_addr);
			अगर (unlikely(ret < 0)) अणु
				sg_offset = prev_addr - sg_dma_address(sg);
				mr->length += prev_addr - dma_addr;
				अगर (sg_offset_p)
					*sg_offset_p = sg_offset;
				वापस i || sg_offset ? i : ret;
			पूर्ण
			prev_addr = page_addr;
next_page:
			page_addr += mr->page_size;
		पूर्ण जबतक (page_addr < end_dma_addr);

		mr->length += dma_len;
		last_end_dma_addr = end_dma_addr;
		last_page_off = end_dma_addr & ~page_mask;

		sg_offset = 0;
	पूर्ण

	अगर (sg_offset_p)
		*sg_offset_p = 0;
	वापस i;
पूर्ण
EXPORT_SYMBOL(ib_sg_to_pages);

काष्ठा ib_drain_cqe अणु
	काष्ठा ib_cqe cqe;
	काष्ठा completion करोne;
पूर्ण;

अटल व्योम ib_drain_qp_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_drain_cqe *cqe = container_of(wc->wr_cqe, काष्ठा ib_drain_cqe,
						cqe);

	complete(&cqe->करोne);
पूर्ण

/*
 * Post a WR and block until its completion is reaped क्रम the SQ.
 */
अटल व्योम __ib_drain_sq(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_cq *cq = qp->send_cq;
	काष्ठा ib_qp_attr attr = अणु .qp_state = IB_QPS_ERR पूर्ण;
	काष्ठा ib_drain_cqe sdrain;
	काष्ठा ib_rdma_wr swr = अणु
		.wr = अणु
			.next = शून्य,
			अणु .wr_cqe	= &sdrain.cqe, पूर्ण,
			.opcode	= IB_WR_RDMA_WRITE,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain send queue: %d\n", ret);
		वापस;
	पूर्ण

	sdrain.cqe.करोne = ib_drain_qp_करोne;
	init_completion(&sdrain.करोne);

	ret = ib_post_send(qp, &swr.wr, शून्य);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain send queue: %d\n", ret);
		वापस;
	पूर्ण

	अगर (cq->poll_ctx == IB_POLL_सूचीECT)
		जबतक (रुको_क्रम_completion_समयout(&sdrain.करोne, HZ / 10) <= 0)
			ib_process_cq_direct(cq, -1);
	अन्यथा
		रुको_क्रम_completion(&sdrain.करोne);
पूर्ण

/*
 * Post a WR and block until its completion is reaped क्रम the RQ.
 */
अटल व्योम __ib_drain_rq(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_cq *cq = qp->recv_cq;
	काष्ठा ib_qp_attr attr = अणु .qp_state = IB_QPS_ERR पूर्ण;
	काष्ठा ib_drain_cqe rdrain;
	काष्ठा ib_recv_wr rwr = अणुपूर्ण;
	पूर्णांक ret;

	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		वापस;
	पूर्ण

	rwr.wr_cqe = &rdrain.cqe;
	rdrain.cqe.करोne = ib_drain_qp_करोne;
	init_completion(&rdrain.करोne);

	ret = ib_post_recv(qp, &rwr, शून्य);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		वापस;
	पूर्ण

	अगर (cq->poll_ctx == IB_POLL_सूचीECT)
		जबतक (रुको_क्रम_completion_समयout(&rdrain.करोne, HZ / 10) <= 0)
			ib_process_cq_direct(cq, -1);
	अन्यथा
		रुको_क्रम_completion(&rdrain.करोne);
पूर्ण

/**
 * ib_drain_sq() - Block until all SQ CQEs have been consumed by the
 *		   application.
 * @qp:            queue pair to drain
 *
 * If the device has a provider-specअगरic drain function, then
 * call that.  Otherwise call the generic drain function
 * __ib_drain_sq().
 *
 * The caller must:
 *
 * ensure there is room in the CQ and SQ क्रम the drain work request and
 * completion.
 *
 * allocate the CQ using ib_alloc_cq().
 *
 * ensure that there are no other contexts that are posting WRs concurrently.
 * Otherwise the drain is not guaranteed.
 */
व्योम ib_drain_sq(काष्ठा ib_qp *qp)
अणु
	अगर (qp->device->ops.drain_sq)
		qp->device->ops.drain_sq(qp);
	अन्यथा
		__ib_drain_sq(qp);
	trace_cq_drain_complete(qp->send_cq);
पूर्ण
EXPORT_SYMBOL(ib_drain_sq);

/**
 * ib_drain_rq() - Block until all RQ CQEs have been consumed by the
 *		   application.
 * @qp:            queue pair to drain
 *
 * If the device has a provider-specअगरic drain function, then
 * call that.  Otherwise call the generic drain function
 * __ib_drain_rq().
 *
 * The caller must:
 *
 * ensure there is room in the CQ and RQ क्रम the drain work request and
 * completion.
 *
 * allocate the CQ using ib_alloc_cq().
 *
 * ensure that there are no other contexts that are posting WRs concurrently.
 * Otherwise the drain is not guaranteed.
 */
व्योम ib_drain_rq(काष्ठा ib_qp *qp)
अणु
	अगर (qp->device->ops.drain_rq)
		qp->device->ops.drain_rq(qp);
	अन्यथा
		__ib_drain_rq(qp);
	trace_cq_drain_complete(qp->recv_cq);
पूर्ण
EXPORT_SYMBOL(ib_drain_rq);

/**
 * ib_drain_qp() - Block until all CQEs have been consumed by the
 *		   application on both the RQ and SQ.
 * @qp:            queue pair to drain
 *
 * The caller must:
 *
 * ensure there is room in the CQ(s), SQ, and RQ क्रम drain work requests
 * and completions.
 *
 * allocate the CQs using ib_alloc_cq().
 *
 * ensure that there are no other contexts that are posting WRs concurrently.
 * Otherwise the drain is not guaranteed.
 */
व्योम ib_drain_qp(काष्ठा ib_qp *qp)
अणु
	ib_drain_sq(qp);
	अगर (!qp->srq)
		ib_drain_rq(qp);
पूर्ण
EXPORT_SYMBOL(ib_drain_qp);

काष्ठा net_device *rdma_alloc_netdev(काष्ठा ib_device *device, u32 port_num,
				     क्रमागत rdma_netdev_t type, स्थिर अक्षर *name,
				     अचिन्हित अक्षर name_assign_type,
				     व्योम (*setup)(काष्ठा net_device *))
अणु
	काष्ठा rdma_netdev_alloc_params params;
	काष्ठा net_device *netdev;
	पूर्णांक rc;

	अगर (!device->ops.rdma_netdev_get_params)
		वापस ERR_PTR(-EOPNOTSUPP);

	rc = device->ops.rdma_netdev_get_params(device, port_num, type,
						&params);
	अगर (rc)
		वापस ERR_PTR(rc);

	netdev = alloc_netdev_mqs(params.माप_priv, name, name_assign_type,
				  setup, params.txqs, params.rxqs);
	अगर (!netdev)
		वापस ERR_PTR(-ENOMEM);

	वापस netdev;
पूर्ण
EXPORT_SYMBOL(rdma_alloc_netdev);

पूर्णांक rdma_init_netdev(काष्ठा ib_device *device, u32 port_num,
		     क्रमागत rdma_netdev_t type, स्थिर अक्षर *name,
		     अचिन्हित अक्षर name_assign_type,
		     व्योम (*setup)(काष्ठा net_device *),
		     काष्ठा net_device *netdev)
अणु
	काष्ठा rdma_netdev_alloc_params params;
	पूर्णांक rc;

	अगर (!device->ops.rdma_netdev_get_params)
		वापस -EOPNOTSUPP;

	rc = device->ops.rdma_netdev_get_params(device, port_num, type,
						&params);
	अगर (rc)
		वापस rc;

	वापस params.initialize_rdma_netdev(device, port_num,
					     netdev, params.param);
पूर्ण
EXPORT_SYMBOL(rdma_init_netdev);

व्योम __rdma_block_iter_start(काष्ठा ib_block_iter *biter,
			     काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक nents,
			     अचिन्हित दीर्घ pgsz)
अणु
	स_रखो(biter, 0, माप(काष्ठा ib_block_iter));
	biter->__sg = sglist;
	biter->__sg_nents = nents;

	/* Driver provides best block size to use */
	biter->__pg_bit = __fls(pgsz);
पूर्ण
EXPORT_SYMBOL(__rdma_block_iter_start);

bool __rdma_block_iter_next(काष्ठा ib_block_iter *biter)
अणु
	अचिन्हित पूर्णांक block_offset;

	अगर (!biter->__sg_nents || !biter->__sg)
		वापस false;

	biter->__dma_addr = sg_dma_address(biter->__sg) + biter->__sg_advance;
	block_offset = biter->__dma_addr & (BIT_ULL(biter->__pg_bit) - 1);
	biter->__sg_advance += BIT_ULL(biter->__pg_bit) - block_offset;

	अगर (biter->__sg_advance >= sg_dma_len(biter->__sg)) अणु
		biter->__sg_advance = 0;
		biter->__sg = sg_next(biter->__sg);
		biter->__sg_nents--;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(__rdma_block_iter_next);
