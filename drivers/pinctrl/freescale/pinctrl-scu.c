<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *	Dong Aisheng <aisheng.करोng@nxp.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../core.h"
#समावेश "pinctrl-imx.h"

क्रमागत pad_func_e अणु
	IMX_SC_PAD_FUNC_SET = 15,
	IMX_SC_PAD_FUNC_GET = 16,
पूर्ण;

काष्ठा imx_sc_msg_req_pad_set अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 val;
	u16 pad;
पूर्ण __packed __aligned(4);

काष्ठा imx_sc_msg_req_pad_get अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u16 pad;
पूर्ण __packed __aligned(4);

काष्ठा imx_sc_msg_resp_pad_get अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 val;
पूर्ण __packed;

अटल काष्ठा imx_sc_ipc *pinctrl_ipc_handle;

पूर्णांक imx_pinctrl_sc_ipc_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस imx_scu_get_handle(&pinctrl_ipc_handle);
पूर्ण
EXPORT_SYMBOL_GPL(imx_pinctrl_sc_ipc_init);

पूर्णांक imx_pinconf_get_scu(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin_id,
			अचिन्हित दीर्घ *config)
अणु
	काष्ठा imx_sc_msg_req_pad_get msg;
	काष्ठा imx_sc_msg_resp_pad_get *resp;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PAD;
	hdr->func = IMX_SC_PAD_FUNC_GET;
	hdr->size = 2;

	msg.pad = pin_id;

	ret = imx_scu_call_rpc(pinctrl_ipc_handle, &msg, true);
	अगर (ret)
		वापस ret;

	resp = (काष्ठा imx_sc_msg_resp_pad_get *)&msg;
	*config = resp->val;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_pinconf_get_scu);

पूर्णांक imx_pinconf_set_scu(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin_id,
			अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा imx_sc_msg_req_pad_set msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	अचिन्हित पूर्णांक mux = configs[0];
	अचिन्हित पूर्णांक conf = configs[1];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/*
	 * Set mux and conf together in one IPC call
	 */
	WARN_ON(num_configs != 2);

	val = conf | BM_PAD_CTL_IFMUX_ENABLE | BM_PAD_CTL_GP_ENABLE;
	val |= mux << BP_PAD_CTL_IFMUX;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PAD;
	hdr->func = IMX_SC_PAD_FUNC_SET;
	hdr->size = 3;

	msg.pad = pin_id;
	msg.val = val;

	ret = imx_scu_call_rpc(pinctrl_ipc_handle, &msg, true);

	dev_dbg(ipctl->dev, "write: pin_id %u config 0x%x val 0x%x\n",
		pin_id, conf, val);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_pinconf_set_scu);

व्योम imx_pinctrl_parse_pin_scu(काष्ठा imx_pinctrl *ipctl,
			       अचिन्हित पूर्णांक *pin_id, काष्ठा imx_pin *pin,
			       स्थिर __be32 **list_p)
अणु
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	काष्ठा imx_pin_scu *pin_scu = &pin->conf.scu;
	स्थिर __be32 *list = *list_p;

	pin->pin = be32_to_cpu(*list++);
	*pin_id = pin->pin;
	pin_scu->mux_mode = be32_to_cpu(*list++);
	pin_scu->config = be32_to_cpu(*list++);
	*list_p = list;

	dev_dbg(ipctl->dev, "%s: 0x%x 0x%08lx", info->pins[pin->pin].name,
		pin_scu->mux_mode, pin_scu->config);
पूर्ण
EXPORT_SYMBOL_GPL(imx_pinctrl_parse_pin_scu);

MODULE_AUTHOR("Dong Aisheng <aisheng.dong@nxp.com>");
MODULE_DESCRIPTION("NXP i.MX SCU common pinctrl driver");
MODULE_LICENSE("GPL v2");
