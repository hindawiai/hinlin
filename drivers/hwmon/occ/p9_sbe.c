<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright IBM Corp 2019

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fsi-occ.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "common.h"

काष्ठा p9_sbe_occ अणु
	काष्ठा occ occ;
	काष्ठा device *sbe;
पूर्ण;

#घोषणा to_p9_sbe_occ(x)	container_of((x), काष्ठा p9_sbe_occ, occ)

अटल पूर्णांक p9_sbe_occ_send_cmd(काष्ठा occ *occ, u8 *cmd)
अणु
	काष्ठा occ_response *resp = &occ->resp;
	काष्ठा p9_sbe_occ *ctx = to_p9_sbe_occ(occ);
	माप_प्रकार resp_len = माप(*resp);
	पूर्णांक rc;

	rc = fsi_occ_submit(ctx->sbe, cmd, 8, resp, &resp_len);
	अगर (rc < 0)
		वापस rc;

	चयन (resp->वापस_status) अणु
	हाल OCC_RESP_CMD_IN_PRG:
		rc = -ETIMEDOUT;
		अवरोध;
	हाल OCC_RESP_SUCCESS:
		rc = 0;
		अवरोध;
	हाल OCC_RESP_CMD_INVAL:
	हाल OCC_RESP_CMD_LEN_INVAL:
	हाल OCC_RESP_DATA_INVAL:
	हाल OCC_RESP_CHKSUM_ERR:
		rc = -EINVAL;
		अवरोध;
	हाल OCC_RESP_INT_ERR:
	हाल OCC_RESP_BAD_STATE:
	हाल OCC_RESP_CRIT_EXCEPT:
	हाल OCC_RESP_CRIT_INIT:
	हाल OCC_RESP_CRIT_WATCHDOG:
	हाल OCC_RESP_CRIT_OCB:
	हाल OCC_RESP_CRIT_HW:
		rc = -EREMOTEIO;
		अवरोध;
	शेष:
		rc = -EPROTO;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक p9_sbe_occ_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	काष्ठा occ *occ;
	काष्ठा p9_sbe_occ *ctx = devm_kzalloc(&pdev->dev, माप(*ctx),
					      GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->sbe = pdev->dev.parent;
	occ = &ctx->occ;
	occ->bus_dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, occ);

	occ->घातr_sample_समय_us = 500;
	occ->poll_cmd_data = 0x20;		/* P9 OCC poll data */
	occ->send_cmd = p9_sbe_occ_send_cmd;

	rc = occ_setup(occ, "p9_occ");
	अगर (rc == -ESHUTDOWN)
		rc = -ENODEV;	/* Host is shutकरोwn, करोn't spew errors */

	वापस rc;
पूर्ण

अटल पूर्णांक p9_sbe_occ_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा occ *occ = platक्रमm_get_drvdata(pdev);
	काष्ठा p9_sbe_occ *ctx = to_p9_sbe_occ(occ);

	ctx->sbe = शून्य;
	occ_shutकरोwn(occ);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver p9_sbe_occ_driver = अणु
	.driver = अणु
		.name = "occ-hwmon",
	पूर्ण,
	.probe	= p9_sbe_occ_probe,
	.हटाओ = p9_sbe_occ_हटाओ,
पूर्ण;

module_platक्रमm_driver(p9_sbe_occ_driver);

MODULE_AUTHOR("Eddie James <eajames@linux.ibm.com>");
MODULE_DESCRIPTION("BMC P9 OCC hwmon driver");
MODULE_LICENSE("GPL");
