<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2018 NXP
 *
 * Header file क्रम the IPC implementation.
 */

#अगर_अघोषित _SC_IPC_H
#घोषणा _SC_IPC_H

#समावेश <linux/device.h>
#समावेश <linux/types.h>

#घोषणा IMX_SC_RPC_VERSION	1
#घोषणा IMX_SC_RPC_MAX_MSG	8

काष्ठा imx_sc_ipc;

क्रमागत imx_sc_rpc_svc अणु
	IMX_SC_RPC_SVC_UNKNOWN = 0,
	IMX_SC_RPC_SVC_RETURN = 1,
	IMX_SC_RPC_SVC_PM = 2,
	IMX_SC_RPC_SVC_RM = 3,
	IMX_SC_RPC_SVC_TIMER = 5,
	IMX_SC_RPC_SVC_PAD = 6,
	IMX_SC_RPC_SVC_MISC = 7,
	IMX_SC_RPC_SVC_IRQ = 8,
पूर्ण;

काष्ठा imx_sc_rpc_msg अणु
	uपूर्णांक8_t ver;
	uपूर्णांक8_t size;
	uपूर्णांक8_t svc;
	uपूर्णांक8_t func;
पूर्ण;

#अगर_घोषित CONFIG_IMX_SCU
/*
 * This is an function to send an RPC message over an IPC channel.
 * It is called by client-side SCFW API function shims.
 *
 * @param[in]     ipc         IPC handle
 * @param[in,out] msg         handle to a message
 * @param[in]     have_resp   response flag
 *
 * If have_resp is true then this function रुकोs क्रम a response
 * and वापसs the result in msg.
 */
पूर्णांक imx_scu_call_rpc(काष्ठा imx_sc_ipc *ipc, व्योम *msg, bool have_resp);

/*
 * This function माला_लो the शेष ipc handle used by SCU
 *
 * @param[out]	ipc	sc ipc handle
 *
 * @वापस Returns an error code (0 = success, failed अगर < 0)
 */
पूर्णांक imx_scu_get_handle(काष्ठा imx_sc_ipc **ipc);
#अन्यथा
अटल अंतरभूत पूर्णांक imx_scu_call_rpc(काष्ठा imx_sc_ipc *ipc, व्योम *msg,
				   bool have_resp)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक imx_scu_get_handle(काष्ठा imx_sc_ipc **ipc)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _SC_IPC_H */
