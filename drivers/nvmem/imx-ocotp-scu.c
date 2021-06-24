<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX8 OCOTP fusebox driver
 *
 * Copyright 2019 NXP
 *
 * Peng Fan <peng.fan@nxp.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा IMX_SIP_OTP_WRITE		0xc200000B

क्रमागत ocotp_devtype अणु
	IMX8QXP,
	IMX8QM,
पूर्ण;

#घोषणा ECC_REGION	BIT(0)
#घोषणा HOLE_REGION	BIT(1)

काष्ठा ocotp_region अणु
	u32 start;
	u32 end;
	u32 flag;
पूर्ण;

काष्ठा ocotp_devtype_data अणु
	पूर्णांक devtype;
	पूर्णांक nregs;
	u32 num_region;
	काष्ठा ocotp_region region[];
पूर्ण;

काष्ठा ocotp_priv अणु
	काष्ठा device *dev;
	स्थिर काष्ठा ocotp_devtype_data *data;
	काष्ठा imx_sc_ipc *nvmem_ipc;
पूर्ण;

काष्ठा imx_sc_msg_misc_fuse_पढ़ो अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 word;
पूर्ण __packed;

अटल DEFINE_MUTEX(scu_ocotp_mutex);

अटल काष्ठा ocotp_devtype_data imx8qxp_data = अणु
	.devtype = IMX8QXP,
	.nregs = 800,
	.num_region = 3,
	.region = अणु
		अणु0x10, 0x10f, ECC_REGIONपूर्ण,
		अणु0x110, 0x21F, HOLE_REGIONपूर्ण,
		अणु0x220, 0x31F, ECC_REGIONपूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ocotp_devtype_data imx8qm_data = अणु
	.devtype = IMX8QM,
	.nregs = 800,
	.num_region = 2,
	.region = अणु
		अणु0x10, 0x10f, ECC_REGIONपूर्ण,
		अणु0x1a0, 0x1ff, ECC_REGIONपूर्ण,
	पूर्ण,
पूर्ण;

अटल bool in_hole(व्योम *context, u32 index)
अणु
	काष्ठा ocotp_priv *priv = context;
	स्थिर काष्ठा ocotp_devtype_data *data = priv->data;
	पूर्णांक i;

	क्रम (i = 0; i < data->num_region; i++) अणु
		अगर (data->region[i].flag & HOLE_REGION) अणु
			अगर ((index >= data->region[i].start) &&
			    (index <= data->region[i].end))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool in_ecc(व्योम *context, u32 index)
अणु
	काष्ठा ocotp_priv *priv = context;
	स्थिर काष्ठा ocotp_devtype_data *data = priv->data;
	पूर्णांक i;

	क्रम (i = 0; i < data->num_region; i++) अणु
		अगर (data->region[i].flag & ECC_REGION) अणु
			अगर ((index >= data->region[i].start) &&
			    (index <= data->region[i].end))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक imx_sc_misc_otp_fuse_पढ़ो(काष्ठा imx_sc_ipc *ipc, u32 word,
				     u32 *val)
अणु
	काष्ठा imx_sc_msg_misc_fuse_पढ़ो msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_MISC;
	hdr->func = IMX_SC_MISC_FUNC_OTP_FUSE_READ;
	hdr->size = 2;

	msg.word = word;

	ret = imx_scu_call_rpc(ipc, &msg, true);
	अगर (ret)
		वापस ret;

	*val = msg.word;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_scu_ocotp_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			      व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा ocotp_priv *priv = context;
	u32 count, index, num_bytes;
	u32 *buf;
	व्योम *p;
	पूर्णांक i, ret;

	index = offset;
	num_bytes = round_up(bytes, 4);
	count = num_bytes >> 2;

	अगर (count > (priv->data->nregs - index))
		count = priv->data->nregs - index;

	p = kzalloc(num_bytes, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	mutex_lock(&scu_ocotp_mutex);

	buf = p;

	क्रम (i = index; i < (index + count); i++) अणु
		अगर (in_hole(context, i)) अणु
			*buf++ = 0;
			जारी;
		पूर्ण

		ret = imx_sc_misc_otp_fuse_पढ़ो(priv->nvmem_ipc, i, buf);
		अगर (ret) अणु
			mutex_unlock(&scu_ocotp_mutex);
			kमुक्त(p);
			वापस ret;
		पूर्ण
		buf++;
	पूर्ण

	स_नकल(val, (u8 *)p, bytes);

	mutex_unlock(&scu_ocotp_mutex);

	kमुक्त(p);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_scu_ocotp_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक offset,
			       व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा ocotp_priv *priv = context;
	काष्ठा arm_smccc_res res;
	u32 *buf = val;
	u32 पंचांगp;
	u32 index;
	पूर्णांक ret;

	/* allow only writing one complete OTP word at a समय */
	अगर (bytes != 4)
		वापस -EINVAL;

	index = offset;

	अगर (in_hole(context, index))
		वापस -EINVAL;

	अगर (in_ecc(context, index)) अणु
		pr_warn("ECC region, only program once\n");
		mutex_lock(&scu_ocotp_mutex);
		ret = imx_sc_misc_otp_fuse_पढ़ो(priv->nvmem_ipc, index, &पंचांगp);
		mutex_unlock(&scu_ocotp_mutex);
		अगर (ret)
			वापस ret;
		अगर (पंचांगp) अणु
			pr_warn("ECC region, already has value: %x\n", पंचांगp);
			वापस -EIO;
		पूर्ण
	पूर्ण

	mutex_lock(&scu_ocotp_mutex);

	arm_smccc_smc(IMX_SIP_OTP_WRITE, index, *buf, 0, 0, 0, 0, 0, &res);

	mutex_unlock(&scu_ocotp_mutex);

	वापस res.a0;
पूर्ण

अटल काष्ठा nvmem_config imx_scu_ocotp_nvmem_config = अणु
	.name = "imx-scu-ocotp",
	.पढ़ो_only = false,
	.word_size = 4,
	.stride = 1,
	.owner = THIS_MODULE,
	.reg_पढ़ो = imx_scu_ocotp_पढ़ो,
	.reg_ग_लिखो = imx_scu_ocotp_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_scu_ocotp_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8qxp-scu-ocotp", (व्योम *)&imx8qxp_data पूर्ण,
	अणु .compatible = "fsl,imx8qm-scu-ocotp", (व्योम *)&imx8qm_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_scu_ocotp_dt_ids);

अटल पूर्णांक imx_scu_ocotp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ocotp_priv *priv;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = imx_scu_get_handle(&priv->nvmem_ipc);
	अगर (ret)
		वापस ret;

	priv->data = of_device_get_match_data(dev);
	priv->dev = dev;
	imx_scu_ocotp_nvmem_config.size = 4 * priv->data->nregs;
	imx_scu_ocotp_nvmem_config.dev = dev;
	imx_scu_ocotp_nvmem_config.priv = priv;
	nvmem = devm_nvmem_रेजिस्टर(dev, &imx_scu_ocotp_nvmem_config);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver imx_scu_ocotp_driver = अणु
	.probe	= imx_scu_ocotp_probe,
	.driver = अणु
		.name	= "imx_scu_ocotp",
		.of_match_table = imx_scu_ocotp_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_scu_ocotp_driver);

MODULE_AUTHOR("Peng Fan <peng.fan@nxp.com>");
MODULE_DESCRIPTION("i.MX8 SCU OCOTP fuse box driver");
MODULE_LICENSE("GPL v2");
