<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Manager Driver क्रम FPGA Management Engine (FME)
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Christopher Rauer <christopher.rauer@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/module.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/fpga/fpga-mgr.h>

#समावेश "dfl-fme-pr.h"

/* FME Partial Reconfiguration Sub Feature Register Set */
#घोषणा FME_PR_DFH		0x0
#घोषणा FME_PR_CTRL		0x8
#घोषणा FME_PR_STS		0x10
#घोषणा FME_PR_DATA		0x18
#घोषणा FME_PR_ERR		0x20
#घोषणा FME_PR_INTFC_ID_L	0xA8
#घोषणा FME_PR_INTFC_ID_H	0xB0

/* FME PR Control Register Bitfield */
#घोषणा FME_PR_CTRL_PR_RST	BIT_ULL(0)  /* Reset PR engine */
#घोषणा FME_PR_CTRL_PR_RSTACK	BIT_ULL(4)  /* Ack क्रम PR engine reset */
#घोषणा FME_PR_CTRL_PR_RGN_ID	GENMASK_ULL(9, 7)       /* PR Region ID */
#घोषणा FME_PR_CTRL_PR_START	BIT_ULL(12) /* Start to request PR service */
#घोषणा FME_PR_CTRL_PR_COMPLETE	BIT_ULL(13) /* PR data push completion */

/* FME PR Status Register Bitfield */
/* Number of available entries in HW queue inside the PR engine. */
#घोषणा FME_PR_STS_PR_CREDIT	GENMASK_ULL(8, 0)
#घोषणा FME_PR_STS_PR_STS	BIT_ULL(16) /* PR operation status */
#घोषणा FME_PR_STS_PR_STS_IDLE	0
#घोषणा FME_PR_STS_PR_CTRLR_STS	GENMASK_ULL(22, 20)     /* Controller status */
#घोषणा FME_PR_STS_PR_HOST_STS	GENMASK_ULL(27, 24)     /* PR host status */

/* FME PR Data Register Bitfield */
/* PR data from the raw-binary file. */
#घोषणा FME_PR_DATA_PR_DATA_RAW	GENMASK_ULL(32, 0)

/* FME PR Error Register */
/* PR Operation errors detected. */
#घोषणा FME_PR_ERR_OPERATION_ERR	BIT_ULL(0)
/* CRC error detected. */
#घोषणा FME_PR_ERR_CRC_ERR		BIT_ULL(1)
/* Incompatible PR bitstream detected. */
#घोषणा FME_PR_ERR_INCOMPATIBLE_BS	BIT_ULL(2)
/* PR data push protocol violated. */
#घोषणा FME_PR_ERR_PROTOCOL_ERR		BIT_ULL(3)
/* PR data fअगरo overflow error detected */
#घोषणा FME_PR_ERR_FIFO_OVERFLOW	BIT_ULL(4)

#घोषणा PR_WAIT_TIMEOUT   8000000
#घोषणा PR_HOST_STATUS_IDLE	0

काष्ठा fme_mgr_priv अणु
	व्योम __iomem *ioaddr;
	u64 pr_error;
पूर्ण;

अटल u64 pr_error_to_mgr_status(u64 err)
अणु
	u64 status = 0;

	अगर (err & FME_PR_ERR_OPERATION_ERR)
		status |= FPGA_MGR_STATUS_OPERATION_ERR;
	अगर (err & FME_PR_ERR_CRC_ERR)
		status |= FPGA_MGR_STATUS_CRC_ERR;
	अगर (err & FME_PR_ERR_INCOMPATIBLE_BS)
		status |= FPGA_MGR_STATUS_INCOMPATIBLE_IMAGE_ERR;
	अगर (err & FME_PR_ERR_PROTOCOL_ERR)
		status |= FPGA_MGR_STATUS_IP_PROTOCOL_ERR;
	अगर (err & FME_PR_ERR_FIFO_OVERFLOW)
		status |= FPGA_MGR_STATUS_FIFO_OVERFLOW_ERR;

	वापस status;
पूर्ण

अटल u64 fme_mgr_pr_error_handle(व्योम __iomem *fme_pr)
अणु
	u64 pr_status, pr_error;

	pr_status = पढ़ोq(fme_pr + FME_PR_STS);
	अगर (!(pr_status & FME_PR_STS_PR_STS))
		वापस 0;

	pr_error = पढ़ोq(fme_pr + FME_PR_ERR);
	ग_लिखोq(pr_error, fme_pr + FME_PR_ERR);

	वापस pr_error;
पूर्ण

अटल पूर्णांक fme_mgr_ग_लिखो_init(काष्ठा fpga_manager *mgr,
			      काष्ठा fpga_image_info *info,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा device *dev = &mgr->dev;
	काष्ठा fme_mgr_priv *priv = mgr->priv;
	व्योम __iomem *fme_pr = priv->ioaddr;
	u64 pr_ctrl, pr_status;

	अगर (!(info->flags & FPGA_MGR_PARTIAL_RECONFIG)) अणु
		dev_err(dev, "only supports partial reconfiguration.\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "resetting PR before initiated PR\n");

	pr_ctrl = पढ़ोq(fme_pr + FME_PR_CTRL);
	pr_ctrl |= FME_PR_CTRL_PR_RST;
	ग_लिखोq(pr_ctrl, fme_pr + FME_PR_CTRL);

	अगर (पढ़ोq_poll_समयout(fme_pr + FME_PR_CTRL, pr_ctrl,
			       pr_ctrl & FME_PR_CTRL_PR_RSTACK, 1,
			       PR_WAIT_TIMEOUT)) अणु
		dev_err(dev, "PR Reset ACK timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	pr_ctrl = पढ़ोq(fme_pr + FME_PR_CTRL);
	pr_ctrl &= ~FME_PR_CTRL_PR_RST;
	ग_लिखोq(pr_ctrl, fme_pr + FME_PR_CTRL);

	dev_dbg(dev,
		"waiting for PR resource in HW to be initialized and ready\n");

	अगर (पढ़ोq_poll_समयout(fme_pr + FME_PR_STS, pr_status,
			       (pr_status & FME_PR_STS_PR_STS) ==
			       FME_PR_STS_PR_STS_IDLE, 1, PR_WAIT_TIMEOUT)) अणु
		dev_err(dev, "PR Status timeout\n");
		priv->pr_error = fme_mgr_pr_error_handle(fme_pr);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(dev, "check and clear previous PR error\n");
	priv->pr_error = fme_mgr_pr_error_handle(fme_pr);
	अगर (priv->pr_error)
		dev_dbg(dev, "previous PR error detected %llx\n",
			(अचिन्हित दीर्घ दीर्घ)priv->pr_error);

	dev_dbg(dev, "set PR port ID\n");

	pr_ctrl = पढ़ोq(fme_pr + FME_PR_CTRL);
	pr_ctrl &= ~FME_PR_CTRL_PR_RGN_ID;
	pr_ctrl |= FIELD_PREP(FME_PR_CTRL_PR_RGN_ID, info->region_id);
	ग_लिखोq(pr_ctrl, fme_pr + FME_PR_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक fme_mgr_ग_लिखो(काष्ठा fpga_manager *mgr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा device *dev = &mgr->dev;
	काष्ठा fme_mgr_priv *priv = mgr->priv;
	व्योम __iomem *fme_pr = priv->ioaddr;
	u64 pr_ctrl, pr_status, pr_data;
	पूर्णांक delay = 0, pr_credit, i = 0;

	dev_dbg(dev, "start request\n");

	pr_ctrl = पढ़ोq(fme_pr + FME_PR_CTRL);
	pr_ctrl |= FME_PR_CTRL_PR_START;
	ग_लिखोq(pr_ctrl, fme_pr + FME_PR_CTRL);

	dev_dbg(dev, "pushing data from bitstream to HW\n");

	/*
	 * driver can push data to PR hardware using PR_DATA रेजिस्टर once HW
	 * has enough pr_credit (> 1), pr_credit reduces one क्रम every 32bit
	 * pr data ग_लिखो to PR_DATA रेजिस्टर. If pr_credit <= 1, driver needs
	 * to रुको क्रम enough pr_credit from hardware by polling.
	 */
	pr_status = पढ़ोq(fme_pr + FME_PR_STS);
	pr_credit = FIELD_GET(FME_PR_STS_PR_CREDIT, pr_status);

	जबतक (count > 0) अणु
		जबतक (pr_credit <= 1) अणु
			अगर (delay++ > PR_WAIT_TIMEOUT) अणु
				dev_err(dev, "PR_CREDIT timeout\n");
				वापस -ETIMEDOUT;
			पूर्ण
			udelay(1);

			pr_status = पढ़ोq(fme_pr + FME_PR_STS);
			pr_credit = FIELD_GET(FME_PR_STS_PR_CREDIT, pr_status);
		पूर्ण

		अगर (count < 4) अणु
			dev_err(dev, "Invalid PR bitstream size\n");
			वापस -EINVAL;
		पूर्ण

		pr_data = 0;
		pr_data |= FIELD_PREP(FME_PR_DATA_PR_DATA_RAW,
				      *(((u32 *)buf) + i));
		ग_लिखोq(pr_data, fme_pr + FME_PR_DATA);
		count -= 4;
		pr_credit--;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fme_mgr_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				  काष्ठा fpga_image_info *info)
अणु
	काष्ठा device *dev = &mgr->dev;
	काष्ठा fme_mgr_priv *priv = mgr->priv;
	व्योम __iomem *fme_pr = priv->ioaddr;
	u64 pr_ctrl;

	pr_ctrl = पढ़ोq(fme_pr + FME_PR_CTRL);
	pr_ctrl |= FME_PR_CTRL_PR_COMPLETE;
	ग_लिखोq(pr_ctrl, fme_pr + FME_PR_CTRL);

	dev_dbg(dev, "green bitstream push complete\n");
	dev_dbg(dev, "waiting for HW to release PR resource\n");

	अगर (पढ़ोq_poll_समयout(fme_pr + FME_PR_CTRL, pr_ctrl,
			       !(pr_ctrl & FME_PR_CTRL_PR_START), 1,
			       PR_WAIT_TIMEOUT)) अणु
		dev_err(dev, "PR Completion ACK timeout.\n");
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(dev, "PR operation complete, checking status\n");
	priv->pr_error = fme_mgr_pr_error_handle(fme_pr);
	अगर (priv->pr_error) अणु
		dev_dbg(dev, "PR error detected %llx\n",
			(अचिन्हित दीर्घ दीर्घ)priv->pr_error);
		वापस -EIO;
	पूर्ण

	dev_dbg(dev, "PR done successfully\n");

	वापस 0;
पूर्ण

अटल क्रमागत fpga_mgr_states fme_mgr_state(काष्ठा fpga_manager *mgr)
अणु
	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल u64 fme_mgr_status(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा fme_mgr_priv *priv = mgr->priv;

	वापस pr_error_to_mgr_status(priv->pr_error);
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops fme_mgr_ops = अणु
	.ग_लिखो_init = fme_mgr_ग_लिखो_init,
	.ग_लिखो = fme_mgr_ग_लिखो,
	.ग_लिखो_complete = fme_mgr_ग_लिखो_complete,
	.state = fme_mgr_state,
	.status = fme_mgr_status,
पूर्ण;

अटल व्योम fme_mgr_get_compat_id(व्योम __iomem *fme_pr,
				  काष्ठा fpga_compat_id *id)
अणु
	id->id_l = पढ़ोq(fme_pr + FME_PR_INTFC_ID_L);
	id->id_h = पढ़ोq(fme_pr + FME_PR_INTFC_ID_H);
पूर्ण

अटल पूर्णांक fme_mgr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_fme_mgr_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा fpga_compat_id *compat_id;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fme_mgr_priv *priv;
	काष्ठा fpga_manager *mgr;
	काष्ठा resource *res;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (pdata->ioaddr)
		priv->ioaddr = pdata->ioaddr;

	अगर (!priv->ioaddr) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		priv->ioaddr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(priv->ioaddr))
			वापस PTR_ERR(priv->ioaddr);
	पूर्ण

	compat_id = devm_kzalloc(dev, माप(*compat_id), GFP_KERNEL);
	अगर (!compat_id)
		वापस -ENOMEM;

	fme_mgr_get_compat_id(priv->ioaddr, compat_id);

	mgr = devm_fpga_mgr_create(dev, "DFL FME FPGA Manager",
				   &fme_mgr_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	mgr->compat_id = compat_id;

	वापस devm_fpga_mgr_रेजिस्टर(dev, mgr);
पूर्ण

अटल काष्ठा platक्रमm_driver fme_mgr_driver = अणु
	.driver	= अणु
		.name    = DFL_FPGA_FME_MGR,
	पूर्ण,
	.probe   = fme_mgr_probe,
पूर्ण;

module_platक्रमm_driver(fme_mgr_driver);

MODULE_DESCRIPTION("FPGA Manager for DFL FPGA Management Engine");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dfl-fme-mgr");
