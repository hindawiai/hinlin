<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2020 NXP
 *
 * File containing client-side RPC functions क्रम the RM service. These
 * function are ported to clients that communicate to the SC.
 */

#समावेश <linux/firmware/imx/svc/rm.h>

काष्ठा imx_sc_msg_rm_rsrc_owned अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u16 resource;
पूर्ण __packed __aligned(4);

/*
 * This function check @resource is owned by current partition or not
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    resource the control is associated with
 *
 * @वापस Returns 0 क्रम not owned and 1 क्रम owned.
 */
bool imx_sc_rm_is_resource_owned(काष्ठा imx_sc_ipc *ipc, u16 resource)
अणु
	काष्ठा imx_sc_msg_rm_rsrc_owned msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_RM;
	hdr->func = IMX_SC_RM_FUNC_IS_RESOURCE_OWNED;
	hdr->size = 2;

	msg.resource = resource;

	/*
	 * SCU firmware only वापसs value 0 or 1
	 * क्रम resource owned check which means not owned or owned.
	 * So it is always successful.
	 */
	imx_scu_call_rpc(ipc, &msg, true);

	वापस hdr->func;
पूर्ण
EXPORT_SYMBOL(imx_sc_rm_is_resource_owned);
