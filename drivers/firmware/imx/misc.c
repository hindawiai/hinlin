<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2018 NXP
 *  Author: Dong Aisheng <aisheng.करोng@nxp.com>
 *
 * File containing client-side RPC functions क्रम the MISC service. These
 * function are ported to clients that communicate to the SC.
 *
 */

#समावेश <linux/firmware/imx/svc/misc.h>

काष्ठा imx_sc_msg_req_misc_set_ctrl अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 ctrl;
	u32 val;
	u16 resource;
पूर्ण __packed __aligned(4);

काष्ठा imx_sc_msg_req_cpu_start अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 address_hi;
	u32 address_lo;
	u16 resource;
	u8 enable;
पूर्ण __packed __aligned(4);

काष्ठा imx_sc_msg_req_misc_get_ctrl अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 ctrl;
	u16 resource;
पूर्ण __packed __aligned(4);

काष्ठा imx_sc_msg_resp_misc_get_ctrl अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 val;
पूर्ण __packed __aligned(4);

/*
 * This function sets a miscellaneous control value.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    resource the control is associated with
 * @param[in]     ctrl        control to change
 * @param[in]     val         value to apply to the control
 *
 * @वापस Returns 0 क्रम success and < 0 क्रम errors.
 */

पूर्णांक imx_sc_misc_set_control(काष्ठा imx_sc_ipc *ipc, u32 resource,
			    u8 ctrl, u32 val)
अणु
	काष्ठा imx_sc_msg_req_misc_set_ctrl msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = (uपूर्णांक8_t)IMX_SC_RPC_SVC_MISC;
	hdr->func = (uपूर्णांक8_t)IMX_SC_MISC_FUNC_SET_CONTROL;
	hdr->size = 4;

	msg.ctrl = ctrl;
	msg.val = val;
	msg.resource = resource;

	वापस imx_scu_call_rpc(ipc, &msg, true);
पूर्ण
EXPORT_SYMBOL(imx_sc_misc_set_control);

/*
 * This function माला_लो a miscellaneous control value.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    resource the control is associated with
 * @param[in]     ctrl        control to get
 * @param[out]    val         poपूर्णांकer to वापस the control value
 *
 * @वापस Returns 0 क्रम success and < 0 क्रम errors.
 */

पूर्णांक imx_sc_misc_get_control(काष्ठा imx_sc_ipc *ipc, u32 resource,
			    u8 ctrl, u32 *val)
अणु
	काष्ठा imx_sc_msg_req_misc_get_ctrl msg;
	काष्ठा imx_sc_msg_resp_misc_get_ctrl *resp;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = (uपूर्णांक8_t)IMX_SC_RPC_SVC_MISC;
	hdr->func = (uपूर्णांक8_t)IMX_SC_MISC_FUNC_GET_CONTROL;
	hdr->size = 3;

	msg.ctrl = ctrl;
	msg.resource = resource;

	ret = imx_scu_call_rpc(ipc, &msg, true);
	अगर (ret)
		वापस ret;

	resp = (काष्ठा imx_sc_msg_resp_misc_get_ctrl *)&msg;
	अगर (val != शून्य)
		*val = resp->val;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(imx_sc_misc_get_control);

/*
 * This function starts/stops a CPU identअगरied by @resource
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    resource the control is associated with
 * @param[in]     enable      true क्रम start, false क्रम stop
 * @param[in]     phys_addr   initial inकाष्ठाion address to be executed
 *
 * @वापस Returns 0 क्रम success and < 0 क्रम errors.
 */
पूर्णांक imx_sc_pm_cpu_start(काष्ठा imx_sc_ipc *ipc, u32 resource,
			bool enable, u64 phys_addr)
अणु
	काष्ठा imx_sc_msg_req_cpu_start msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_CPU_START;
	hdr->size = 4;

	msg.address_hi = phys_addr >> 32;
	msg.address_lo = phys_addr;
	msg.resource = resource;
	msg.enable = enable;

	वापस imx_scu_call_rpc(ipc, &msg, true);
पूर्ण
EXPORT_SYMBOL(imx_sc_pm_cpu_start);
