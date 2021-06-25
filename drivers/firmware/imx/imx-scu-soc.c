<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

अटल काष्ठा imx_sc_ipc *imx_sc_soc_ipc_handle;

काष्ठा imx_sc_msg_misc_get_soc_id अणु
	काष्ठा imx_sc_rpc_msg hdr;
	जोड़ अणु
		काष्ठा अणु
			u32 control;
			u16 resource;
		पूर्ण __packed req;
		काष्ठा अणु
			u32 id;
		पूर्ण resp;
	पूर्ण data;
पूर्ण __packed __aligned(4);

काष्ठा imx_sc_msg_misc_get_soc_uid अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 uid_low;
	u32 uid_high;
पूर्ण __packed;

अटल पूर्णांक imx_scu_soc_uid(u64 *soc_uid)
अणु
	काष्ठा imx_sc_msg_misc_get_soc_uid msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_MISC;
	hdr->func = IMX_SC_MISC_FUNC_UNIQUE_ID;
	hdr->size = 1;

	ret = imx_scu_call_rpc(imx_sc_soc_ipc_handle, &msg, true);
	अगर (ret) अणु
		pr_err("%s: get soc uid failed, ret %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	*soc_uid = msg.uid_high;
	*soc_uid <<= 32;
	*soc_uid |= msg.uid_low;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_scu_soc_id(व्योम)
अणु
	काष्ठा imx_sc_msg_misc_get_soc_id msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_MISC;
	hdr->func = IMX_SC_MISC_FUNC_GET_CONTROL;
	hdr->size = 3;

	msg.data.req.control = IMX_SC_C_ID;
	msg.data.req.resource = IMX_SC_R_SYSTEM;

	ret = imx_scu_call_rpc(imx_sc_soc_ipc_handle, &msg, true);
	अगर (ret) अणु
		pr_err("%s: get soc info failed, ret %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस msg.data.resp.id;
पूर्ण

पूर्णांक imx_scu_soc_init(काष्ठा device *dev)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;
	पूर्णांक id, ret;
	u64 uid = 0;
	u32 val;

	ret = imx_scu_get_handle(&imx_sc_soc_ipc_handle);
	अगर (ret)
		वापस ret;

	soc_dev_attr = devm_kzalloc(dev, माप(*soc_dev_attr),
				    GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	soc_dev_attr->family = "Freescale i.MX";

	ret = of_property_पढ़ो_string(of_root,
				      "model",
				      &soc_dev_attr->machine);
	अगर (ret)
		वापस ret;

	id = imx_scu_soc_id();
	अगर (id < 0)
		वापस -EINVAL;

	ret = imx_scu_soc_uid(&uid);
	अगर (ret < 0)
		वापस -EINVAL;

	/* क्रमmat soc_id value passed from SCU firmware */
	val = id & 0x1f;
	soc_dev_attr->soc_id = devm_kaप्र_लिखो(dev, GFP_KERNEL, "0x%x", val);
	अगर (!soc_dev_attr->soc_id)
		वापस -ENOMEM;

	/* क्रमmat revision value passed from SCU firmware */
	val = (id >> 5) & 0xf;
	val = (((val >> 2) + 1) << 4) | (val & 0x3);
	soc_dev_attr->revision = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%d.%d",
						(val >> 4) & 0xf, val & 0xf);
	अगर (!soc_dev_attr->revision)
		वापस -ENOMEM;

	soc_dev_attr->serial_number = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						     "%016llX", uid);
	अगर (!soc_dev_attr->serial_number)
		वापस -ENOMEM;

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev))
		वापस PTR_ERR(soc_dev);

	वापस 0;
पूर्ण
