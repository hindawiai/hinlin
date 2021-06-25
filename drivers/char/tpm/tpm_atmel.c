<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004 IBM Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safक्रमd <safक्रमd@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org	 
 */

#समावेश "tpm.h"
#समावेश "tpm_atmel.h"

/* ग_लिखो status bits */
क्रमागत tpm_aपंचांगel_ग_लिखो_status अणु
	ATML_STATUS_ABORT = 0x01,
	ATML_STATUS_LASTBYTE = 0x04
पूर्ण;
/* पढ़ो status bits */
क्रमागत tpm_aपंचांगel_पढ़ो_status अणु
	ATML_STATUS_BUSY = 0x01,
	ATML_STATUS_DATA_AVAIL = 0x02,
	ATML_STATUS_REWRITE = 0x04,
	ATML_STATUS_READY = 0x08
पूर्ण;

अटल पूर्णांक tpm_aपंचांगl_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_aपंचांगel_priv *priv = dev_get_drvdata(&chip->dev);
	u8 status, *hdr = buf;
	u32 size;
	पूर्णांक i;
	__be32 *native_size;

	/* start पढ़ोing header */
	अगर (count < 6)
		वापस -EIO;

	क्रम (i = 0; i < 6; i++) अणु
		status = ioपढ़ो8(priv->iobase + 1);
		अगर ((status & ATML_STATUS_DATA_AVAIL) == 0) अणु
			dev_err(&chip->dev, "error reading header\n");
			वापस -EIO;
		पूर्ण
		*buf++ = ioपढ़ो8(priv->iobase);
	पूर्ण

	/* size of the data received */
	native_size = (__क्रमce __be32 *) (hdr + 2);
	size = be32_to_cpu(*native_size);

	अगर (count < size) अणु
		dev_err(&chip->dev,
			"Recv size(%d) less than available space\n", size);
		क्रम (; i < size; i++) अणु	/* clear the रुकोing data anyway */
			status = ioपढ़ो8(priv->iobase + 1);
			अगर ((status & ATML_STATUS_DATA_AVAIL) == 0) अणु
				dev_err(&chip->dev, "error reading data\n");
				वापस -EIO;
			पूर्ण
		पूर्ण
		वापस -EIO;
	पूर्ण

	/* पढ़ो all the data available */
	क्रम (; i < size; i++) अणु
		status = ioपढ़ो8(priv->iobase + 1);
		अगर ((status & ATML_STATUS_DATA_AVAIL) == 0) अणु
			dev_err(&chip->dev, "error reading data\n");
			वापस -EIO;
		पूर्ण
		*buf++ = ioपढ़ो8(priv->iobase);
	पूर्ण

	/* make sure data available is gone */
	status = ioपढ़ो8(priv->iobase + 1);

	अगर (status & ATML_STATUS_DATA_AVAIL) अणु
		dev_err(&chip->dev, "data available is stuck\n");
		वापस -EIO;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक tpm_aपंचांगl_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_aपंचांगel_priv *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक i;

	dev_dbg(&chip->dev, "tpm_atml_send:\n");
	क्रम (i = 0; i < count; i++) अणु
		dev_dbg(&chip->dev, "%d 0x%x(%d)\n",  i, buf[i], buf[i]);
		ioग_लिखो8(buf[i], priv->iobase);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tpm_aपंचांगl_cancel(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_aपंचांगel_priv *priv = dev_get_drvdata(&chip->dev);

	ioग_लिखो8(ATML_STATUS_ABORT, priv->iobase + 1);
पूर्ण

अटल u8 tpm_aपंचांगl_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_aपंचांगel_priv *priv = dev_get_drvdata(&chip->dev);

	वापस ioपढ़ो8(priv->iobase + 1);
पूर्ण

अटल bool tpm_aपंचांगl_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस (status == ATML_STATUS_READY);
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_aपंचांगel = अणु
	.recv = tpm_aपंचांगl_recv,
	.send = tpm_aपंचांगl_send,
	.cancel = tpm_aपंचांगl_cancel,
	.status = tpm_aपंचांगl_status,
	.req_complete_mask = ATML_STATUS_BUSY | ATML_STATUS_DATA_AVAIL,
	.req_complete_val = ATML_STATUS_DATA_AVAIL,
	.req_canceled = tpm_aपंचांगl_req_canceled,
पूर्ण;

अटल काष्ठा platक्रमm_device *pdev;

अटल व्योम aपंचांगl_plat_हटाओ(व्योम)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(&pdev->dev);
	काष्ठा tpm_aपंचांगel_priv *priv = dev_get_drvdata(&chip->dev);

	tpm_chip_unरेजिस्टर(chip);
	अगर (priv->have_region)
		aपंचांगel_release_region(priv->base, priv->region_size);
	aपंचांगel_put_base_addr(priv->iobase);
	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tpm_aपंचांगl_pm, tpm_pm_suspend, tpm_pm_resume);

अटल काष्ठा platक्रमm_driver aपंचांगl_drv = अणु
	.driver = अणु
		.name = "tpm_atmel",
		.pm		= &tpm_aपंचांगl_pm,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init init_aपंचांगel(व्योम)
अणु
	पूर्णांक rc = 0;
	व्योम __iomem *iobase = शून्य;
	पूर्णांक have_region, region_size;
	अचिन्हित दीर्घ base;
	काष्ठा  tpm_chip *chip;
	काष्ठा tpm_aपंचांगel_priv *priv;

	rc = platक्रमm_driver_रेजिस्टर(&aपंचांगl_drv);
	अगर (rc)
		वापस rc;

	अगर ((iobase = aपंचांगel_get_base_addr(&base, &region_size)) == शून्य) अणु
		rc = -ENODEV;
		जाओ err_unreg_drv;
	पूर्ण

	have_region =
	    (aपंचांगel_request_region
	     (base, region_size, "tpm_atmel0") == शून्य) ? 0 : 1;

	pdev = platक्रमm_device_रेजिस्टर_simple("tpm_atmel", -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		rc = PTR_ERR(pdev);
		जाओ err_rel_reg;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		rc = -ENOMEM;
		जाओ err_unreg_dev;
	पूर्ण

	priv->iobase = iobase;
	priv->base = base;
	priv->have_region = have_region;
	priv->region_size = region_size;

	chip = tpmm_chip_alloc(&pdev->dev, &tpm_aपंचांगel);
	अगर (IS_ERR(chip)) अणु
		rc = PTR_ERR(chip);
		जाओ err_unreg_dev;
	पूर्ण

	dev_set_drvdata(&chip->dev, priv);

	rc = tpm_chip_रेजिस्टर(chip);
	अगर (rc)
		जाओ err_unreg_dev;

	वापस 0;

err_unreg_dev:
	platक्रमm_device_unरेजिस्टर(pdev);
err_rel_reg:
	aपंचांगel_put_base_addr(iobase);
	अगर (have_region)
		aपंचांगel_release_region(base,
				     region_size);
err_unreg_drv:
	platक्रमm_driver_unरेजिस्टर(&aपंचांगl_drv);
	वापस rc;
पूर्ण

अटल व्योम __निकास cleanup_aपंचांगel(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&aपंचांगl_drv);
	aपंचांगl_plat_हटाओ();
पूर्ण

module_init(init_aपंचांगel);
module_निकास(cleanup_aपंचांगel);

MODULE_AUTHOR("Leendert van Doorn (leendert@watson.ibm.com)");
MODULE_DESCRIPTION("TPM Driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
