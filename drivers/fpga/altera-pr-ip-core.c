<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Altera Partial Reconfiguration IP Core
 *
 * Copyright (C) 2016-2017 Intel Corporation
 *
 * Based on socfpga-a10.c Copyright (C) 2015-2016 Altera Corporation
 *  by Alan Tull <atull@खोलोsource.altera.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/fpga/altera-pr-ip-core.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/module.h>

#घोषणा ALT_PR_DATA_OFST		0x00
#घोषणा ALT_PR_CSR_OFST			0x04

#घोषणा ALT_PR_CSR_PR_START		BIT(0)
#घोषणा ALT_PR_CSR_STATUS_SFT		2
#घोषणा ALT_PR_CSR_STATUS_MSK		(7 << ALT_PR_CSR_STATUS_SFT)
#घोषणा ALT_PR_CSR_STATUS_NRESET	(0 << ALT_PR_CSR_STATUS_SFT)
#घोषणा ALT_PR_CSR_STATUS_PR_ERR	(1 << ALT_PR_CSR_STATUS_SFT)
#घोषणा ALT_PR_CSR_STATUS_CRC_ERR	(2 << ALT_PR_CSR_STATUS_SFT)
#घोषणा ALT_PR_CSR_STATUS_BAD_BITS	(3 << ALT_PR_CSR_STATUS_SFT)
#घोषणा ALT_PR_CSR_STATUS_PR_IN_PROG	(4 << ALT_PR_CSR_STATUS_SFT)
#घोषणा ALT_PR_CSR_STATUS_PR_SUCCESS	(5 << ALT_PR_CSR_STATUS_SFT)

काष्ठा alt_pr_priv अणु
	व्योम __iomem *reg_base;
पूर्ण;

अटल क्रमागत fpga_mgr_states alt_pr_fpga_state(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा alt_pr_priv *priv = mgr->priv;
	स्थिर अक्षर *err = "unknown";
	क्रमागत fpga_mgr_states ret = FPGA_MGR_STATE_UNKNOWN;
	u32 val;

	val = पढ़ोl(priv->reg_base + ALT_PR_CSR_OFST);

	val &= ALT_PR_CSR_STATUS_MSK;

	चयन (val) अणु
	हाल ALT_PR_CSR_STATUS_NRESET:
		वापस FPGA_MGR_STATE_RESET;

	हाल ALT_PR_CSR_STATUS_PR_ERR:
		err = "pr error";
		ret = FPGA_MGR_STATE_WRITE_ERR;
		अवरोध;

	हाल ALT_PR_CSR_STATUS_CRC_ERR:
		err = "crc error";
		ret = FPGA_MGR_STATE_WRITE_ERR;
		अवरोध;

	हाल ALT_PR_CSR_STATUS_BAD_BITS:
		err = "bad bits";
		ret = FPGA_MGR_STATE_WRITE_ERR;
		अवरोध;

	हाल ALT_PR_CSR_STATUS_PR_IN_PROG:
		वापस FPGA_MGR_STATE_WRITE;

	हाल ALT_PR_CSR_STATUS_PR_SUCCESS:
		वापस FPGA_MGR_STATE_OPERATING;

	शेष:
		अवरोध;
	पूर्ण

	dev_err(&mgr->dev, "encountered error code %d (%s) in %s()\n",
		val, err, __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक alt_pr_fpga_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				  काष्ठा fpga_image_info *info,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा alt_pr_priv *priv = mgr->priv;
	u32 val;

	अगर (!(info->flags & FPGA_MGR_PARTIAL_RECONFIG)) अणु
		dev_err(&mgr->dev, "%s Partial Reconfiguration flag not set\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	val = पढ़ोl(priv->reg_base + ALT_PR_CSR_OFST);

	अगर (val & ALT_PR_CSR_PR_START) अणु
		dev_err(&mgr->dev,
			"%s Partial Reconfiguration already started\n",
		       __func__);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(val | ALT_PR_CSR_PR_START, priv->reg_base + ALT_PR_CSR_OFST);

	वापस 0;
पूर्ण

अटल पूर्णांक alt_pr_fpga_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा alt_pr_priv *priv = mgr->priv;
	u32 *buffer_32 = (u32 *)buf;
	माप_प्रकार i = 0;

	अगर (count <= 0)
		वापस -EINVAL;

	/* Write out the complete 32-bit chunks */
	जबतक (count >= माप(u32)) अणु
		ग_लिखोl(buffer_32[i++], priv->reg_base);
		count -= माप(u32);
	पूर्ण

	/* Write out reमुख्यing non 32-bit chunks */
	चयन (count) अणु
	हाल 3:
		ग_लिखोl(buffer_32[i++] & 0x00ffffff, priv->reg_base);
		अवरोध;
	हाल 2:
		ग_लिखोl(buffer_32[i++] & 0x0000ffff, priv->reg_base);
		अवरोध;
	हाल 1:
		ग_लिखोl(buffer_32[i++] & 0x000000ff, priv->reg_base);
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		/* This will never happen */
		वापस -EFAULT;
	पूर्ण

	अगर (alt_pr_fpga_state(mgr) == FPGA_MGR_STATE_WRITE_ERR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक alt_pr_fpga_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				      काष्ठा fpga_image_info *info)
अणु
	u32 i = 0;

	करो अणु
		चयन (alt_pr_fpga_state(mgr)) अणु
		हाल FPGA_MGR_STATE_WRITE_ERR:
			वापस -EIO;

		हाल FPGA_MGR_STATE_OPERATING:
			dev_info(&mgr->dev,
				 "successful partial reconfiguration\n");
			वापस 0;

		शेष:
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (info->config_complete_समयout_us > i++);

	dev_err(&mgr->dev, "timed out waiting for write to complete\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops alt_pr_ops = अणु
	.state = alt_pr_fpga_state,
	.ग_लिखो_init = alt_pr_fpga_ग_लिखो_init,
	.ग_लिखो = alt_pr_fpga_ग_लिखो,
	.ग_लिखो_complete = alt_pr_fpga_ग_लिखो_complete,
पूर्ण;

पूर्णांक alt_pr_रेजिस्टर(काष्ठा device *dev, व्योम __iomem *reg_base)
अणु
	काष्ठा alt_pr_priv *priv;
	काष्ठा fpga_manager *mgr;
	u32 val;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->reg_base = reg_base;

	val = पढ़ोl(priv->reg_base + ALT_PR_CSR_OFST);

	dev_dbg(dev, "%s status=%d start=%d\n", __func__,
		(val & ALT_PR_CSR_STATUS_MSK) >> ALT_PR_CSR_STATUS_SFT,
		(पूर्णांक)(val & ALT_PR_CSR_PR_START));

	mgr = devm_fpga_mgr_create(dev, dev_name(dev), &alt_pr_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(dev, mgr);
पूर्ण
EXPORT_SYMBOL_GPL(alt_pr_रेजिस्टर);

व्योम alt_pr_unरेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा fpga_manager *mgr = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	fpga_mgr_unरेजिस्टर(mgr);
पूर्ण
EXPORT_SYMBOL_GPL(alt_pr_unरेजिस्टर);

MODULE_AUTHOR("Matthew Gerlach <matthew.gerlach@linux.intel.com>");
MODULE_DESCRIPTION("Altera Partial Reconfiguration IP Core");
MODULE_LICENSE("GPL v2");
