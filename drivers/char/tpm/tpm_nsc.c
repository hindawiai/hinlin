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

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश "tpm.h"

/* National definitions */
क्रमागत tpm_nsc_addrअणु
	TPM_NSC_IRQ = 0x07,
	TPM_NSC_BASE0_HI = 0x60,
	TPM_NSC_BASE0_LO = 0x61,
	TPM_NSC_BASE1_HI = 0x62,
	TPM_NSC_BASE1_LO = 0x63
पूर्ण;

क्रमागत tpm_nsc_index अणु
	NSC_LDN_INDEX = 0x07,
	NSC_SID_INDEX = 0x20,
	NSC_LDC_INDEX = 0x30,
	NSC_DIO_INDEX = 0x60,
	NSC_CIO_INDEX = 0x62,
	NSC_IRQ_INDEX = 0x70,
	NSC_ITS_INDEX = 0x71
पूर्ण;

क्रमागत tpm_nsc_status_loc अणु
	NSC_STATUS = 0x01,
	NSC_COMMAND = 0x01,
	NSC_DATA = 0x00
पूर्ण;

/* status bits */
क्रमागत tpm_nsc_status अणु
	NSC_STATUS_OBF = 0x01,	/* output buffer full */
	NSC_STATUS_IBF = 0x02,	/* input buffer full */
	NSC_STATUS_F0 = 0x04,	/* F0 */
	NSC_STATUS_A2 = 0x08,	/* A2 */
	NSC_STATUS_RDY = 0x10,	/* पढ़ोy to receive command */
	NSC_STATUS_IBR = 0x20	/* पढ़ोy to receive data */
पूर्ण;

/* command bits */
क्रमागत tpm_nsc_cmd_mode अणु
	NSC_COMMAND_NORMAL = 0x01,	/* normal mode */
	NSC_COMMAND_EOC = 0x03,
	NSC_COMMAND_CANCEL = 0x22
पूर्ण;

काष्ठा tpm_nsc_priv अणु
	अचिन्हित दीर्घ base;
पूर्ण;

/*
 * Wait क्रम a certain status to appear
 */
अटल पूर्णांक रुको_क्रम_stat(काष्ठा tpm_chip *chip, u8 mask, u8 val, u8 * data)
अणु
	काष्ठा tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);
	अचिन्हित दीर्घ stop;

	/* status immediately available check */
	*data = inb(priv->base + NSC_STATUS);
	अगर ((*data & mask) == val)
		वापस 0;

	/* रुको क्रम status */
	stop = jअगरfies + 10 * HZ;
	करो अणु
		msleep(TPM_TIMEOUT);
		*data = inb(priv->base + 1);
		अगर ((*data & mask) == val)
			वापस 0;
	पूर्ण
	जबतक (समय_beक्रमe(jअगरfies, stop));

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक nsc_रुको_क्रम_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक status;
	अचिन्हित दीर्घ stop;

	/* status immediately available check */
	status = inb(priv->base + NSC_STATUS);
	अगर (status & NSC_STATUS_OBF)
		status = inb(priv->base + NSC_DATA);
	अगर (status & NSC_STATUS_RDY)
		वापस 0;

	/* रुको क्रम status */
	stop = jअगरfies + 100;
	करो अणु
		msleep(TPM_TIMEOUT);
		status = inb(priv->base + NSC_STATUS);
		अगर (status & NSC_STATUS_OBF)
			status = inb(priv->base + NSC_DATA);
		अगर (status & NSC_STATUS_RDY)
			वापस 0;
	पूर्ण
	जबतक (समय_beक्रमe(jअगरfies, stop));

	dev_info(&chip->dev, "wait for ready failed\n");
	वापस -EBUSY;
पूर्ण


अटल पूर्णांक tpm_nsc_recv(काष्ठा tpm_chip *chip, u8 * buf, माप_प्रकार count)
अणु
	काष्ठा tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);
	u8 *buffer = buf;
	u8 data, *p;
	u32 size;
	__be32 *native_size;

	अगर (count < 6)
		वापस -EIO;

	अगर (रुको_क्रम_stat(chip, NSC_STATUS_F0, NSC_STATUS_F0, &data) < 0) अणु
		dev_err(&chip->dev, "F0 timeout\n");
		वापस -EIO;
	पूर्ण

	data = inb(priv->base + NSC_DATA);
	अगर (data != NSC_COMMAND_NORMAL) अणु
		dev_err(&chip->dev, "not in normal mode (0x%x)\n",
			data);
		वापस -EIO;
	पूर्ण

	/* पढ़ो the whole packet */
	क्रम (p = buffer; p < &buffer[count]; p++) अणु
		अगर (रुको_क्रम_stat
		    (chip, NSC_STATUS_OBF, NSC_STATUS_OBF, &data) < 0) अणु
			dev_err(&chip->dev,
				"OBF timeout (while reading data)\n");
			वापस -EIO;
		पूर्ण
		अगर (data & NSC_STATUS_F0)
			अवरोध;
		*p = inb(priv->base + NSC_DATA);
	पूर्ण

	अगर ((data & NSC_STATUS_F0) == 0 &&
	(रुको_क्रम_stat(chip, NSC_STATUS_F0, NSC_STATUS_F0, &data) < 0)) अणु
		dev_err(&chip->dev, "F0 not set\n");
		वापस -EIO;
	पूर्ण

	data = inb(priv->base + NSC_DATA);
	अगर (data != NSC_COMMAND_EOC) अणु
		dev_err(&chip->dev,
			"expected end of command(0x%x)\n", data);
		वापस -EIO;
	पूर्ण

	native_size = (__क्रमce __be32 *) (buf + 2);
	size = be32_to_cpu(*native_size);

	अगर (count < size)
		वापस -EIO;

	वापस size;
पूर्ण

अटल पूर्णांक tpm_nsc_send(काष्ठा tpm_chip *chip, u8 * buf, माप_प्रकार count)
अणु
	काष्ठा tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);
	u8 data;
	पूर्णांक i;

	/*
	 * If we hit the chip with back to back commands it locks up
	 * and never set IBF. Hitting it with this "hammer" seems to
	 * fix it. Not sure why this is needed, we followed the flow
	 * अक्षरt in the manual to the letter.
	 */
	outb(NSC_COMMAND_CANCEL, priv->base + NSC_COMMAND);

	अगर (nsc_रुको_क्रम_पढ़ोy(chip) != 0)
		वापस -EIO;

	अगर (रुको_क्रम_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) अणु
		dev_err(&chip->dev, "IBF timeout\n");
		वापस -EIO;
	पूर्ण

	outb(NSC_COMMAND_NORMAL, priv->base + NSC_COMMAND);
	अगर (रुको_क्रम_stat(chip, NSC_STATUS_IBR, NSC_STATUS_IBR, &data) < 0) अणु
		dev_err(&chip->dev, "IBR timeout\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (रुको_क्रम_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) अणु
			dev_err(&chip->dev,
				"IBF timeout (while writing data)\n");
			वापस -EIO;
		पूर्ण
		outb(buf[i], priv->base + NSC_DATA);
	पूर्ण

	अगर (रुको_क्रम_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) अणु
		dev_err(&chip->dev, "IBF timeout\n");
		वापस -EIO;
	पूर्ण
	outb(NSC_COMMAND_EOC, priv->base + NSC_COMMAND);

	वापस 0;
पूर्ण

अटल व्योम tpm_nsc_cancel(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);

	outb(NSC_COMMAND_CANCEL, priv->base + NSC_COMMAND);
पूर्ण

अटल u8 tpm_nsc_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);

	वापस inb(priv->base + NSC_STATUS);
पूर्ण

अटल bool tpm_nsc_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस (status == NSC_STATUS_RDY);
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_nsc = अणु
	.recv = tpm_nsc_recv,
	.send = tpm_nsc_send,
	.cancel = tpm_nsc_cancel,
	.status = tpm_nsc_status,
	.req_complete_mask = NSC_STATUS_OBF,
	.req_complete_val = NSC_STATUS_OBF,
	.req_canceled = tpm_nsc_req_canceled,
पूर्ण;

अटल काष्ठा platक्रमm_device *pdev = शून्य;

अटल व्योम tpm_nsc_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	काष्ठा tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);

	tpm_chip_unरेजिस्टर(chip);
	release_region(priv->base, 2);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tpm_nsc_pm, tpm_pm_suspend, tpm_pm_resume);

अटल काष्ठा platक्रमm_driver nsc_drv = अणु
	.driver          = अणु
		.name    = "tpm_nsc",
		.pm      = &tpm_nsc_pm,
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक tpm_पढ़ो_index(पूर्णांक base, पूर्णांक index)
अणु
	outb(index, base);
	वापस inb(base+1) & 0xFF;
पूर्ण

अटल अंतरभूत व्योम tpm_ग_लिखो_index(पूर्णांक base, पूर्णांक index, पूर्णांक value)
अणु
	outb(index, base);
	outb(value & 0xFF, base+1);
पूर्ण

अटल पूर्णांक __init init_nsc(व्योम)
अणु
	पूर्णांक rc = 0;
	पूर्णांक lo, hi, err;
	पूर्णांक nscAddrBase = TPM_ADDR;
	काष्ठा tpm_chip *chip;
	अचिन्हित दीर्घ base;
	काष्ठा tpm_nsc_priv *priv;

	/* verअगरy that it is a National part (SID) */
	अगर (tpm_पढ़ो_index(TPM_ADDR, NSC_SID_INDEX) != 0xEF) अणु
		nscAddrBase = (tpm_पढ़ो_index(TPM_SUPERIO_ADDR, 0x2C)<<8)|
			(tpm_पढ़ो_index(TPM_SUPERIO_ADDR, 0x2B)&0xFE);
		अगर (tpm_पढ़ो_index(nscAddrBase, NSC_SID_INDEX) != 0xF6)
			वापस -ENODEV;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&nsc_drv);
	अगर (err)
		वापस err;

	hi = tpm_पढ़ो_index(nscAddrBase, TPM_NSC_BASE0_HI);
	lo = tpm_पढ़ो_index(nscAddrBase, TPM_NSC_BASE0_LO);
	base = (hi<<8) | lo;

	/* enable the DPM module */
	tpm_ग_लिखो_index(nscAddrBase, NSC_LDC_INDEX, 0x01);

	pdev = platक्रमm_device_alloc("tpm_nscl0", -1);
	अगर (!pdev) अणु
		rc = -ENOMEM;
		जाओ err_unreg_drv;
	पूर्ण

	pdev->num_resources = 0;
	pdev->dev.driver = &nsc_drv.driver;
	pdev->dev.release = tpm_nsc_हटाओ;

	अगर ((rc = platक्रमm_device_add(pdev)) < 0)
		जाओ err_put_dev;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		rc = -ENOMEM;
		जाओ err_del_dev;
	पूर्ण

	priv->base = base;

	अगर (request_region(base, 2, "tpm_nsc0") == शून्य ) अणु
		rc = -EBUSY;
		जाओ err_del_dev;
	पूर्ण

	chip = tpmm_chip_alloc(&pdev->dev, &tpm_nsc);
	अगर (IS_ERR(chip)) अणु
		rc = -ENODEV;
		जाओ err_rel_reg;
	पूर्ण

	dev_set_drvdata(&chip->dev, priv);

	rc = tpm_chip_रेजिस्टर(chip);
	अगर (rc)
		जाओ err_rel_reg;

	dev_dbg(&pdev->dev, "NSC TPM detected\n");
	dev_dbg(&pdev->dev,
		"NSC LDN 0x%x, SID 0x%x, SRID 0x%x\n",
		tpm_पढ़ो_index(nscAddrBase,0x07), tpm_पढ़ो_index(nscAddrBase,0x20),
		tpm_पढ़ो_index(nscAddrBase,0x27));
	dev_dbg(&pdev->dev,
		"NSC SIOCF1 0x%x SIOCF5 0x%x SIOCF6 0x%x SIOCF8 0x%x\n",
		tpm_पढ़ो_index(nscAddrBase,0x21), tpm_पढ़ो_index(nscAddrBase,0x25),
		tpm_पढ़ो_index(nscAddrBase,0x26), tpm_पढ़ो_index(nscAddrBase,0x28));
	dev_dbg(&pdev->dev, "NSC IO Base0 0x%x\n",
		(tpm_पढ़ो_index(nscAddrBase,0x60) << 8) | tpm_पढ़ो_index(nscAddrBase,0x61));
	dev_dbg(&pdev->dev, "NSC IO Base1 0x%x\n",
		(tpm_पढ़ो_index(nscAddrBase,0x62) << 8) | tpm_पढ़ो_index(nscAddrBase,0x63));
	dev_dbg(&pdev->dev, "NSC Interrupt number and wakeup 0x%x\n",
		tpm_पढ़ो_index(nscAddrBase,0x70));
	dev_dbg(&pdev->dev, "NSC IRQ type select 0x%x\n",
		tpm_पढ़ो_index(nscAddrBase,0x71));
	dev_dbg(&pdev->dev,
		"NSC DMA channel select0 0x%x, select1 0x%x\n",
		tpm_पढ़ो_index(nscAddrBase,0x74), tpm_पढ़ो_index(nscAddrBase,0x75));
	dev_dbg(&pdev->dev,
		"NSC Config "
		"0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
		tpm_पढ़ो_index(nscAddrBase,0xF0), tpm_पढ़ो_index(nscAddrBase,0xF1),
		tpm_पढ़ो_index(nscAddrBase,0xF2), tpm_पढ़ो_index(nscAddrBase,0xF3),
		tpm_पढ़ो_index(nscAddrBase,0xF4), tpm_पढ़ो_index(nscAddrBase,0xF5),
		tpm_पढ़ो_index(nscAddrBase,0xF6), tpm_पढ़ो_index(nscAddrBase,0xF7),
		tpm_पढ़ो_index(nscAddrBase,0xF8), tpm_पढ़ो_index(nscAddrBase,0xF9));

	dev_info(&pdev->dev,
		 "NSC TPM revision %d\n",
		 tpm_पढ़ो_index(nscAddrBase, 0x27) & 0x1F);

	वापस 0;

err_rel_reg:
	release_region(base, 2);
err_del_dev:
	platक्रमm_device_del(pdev);
err_put_dev:
	platक्रमm_device_put(pdev);
err_unreg_drv:
	platक्रमm_driver_unरेजिस्टर(&nsc_drv);
	वापस rc;
पूर्ण

अटल व्योम __निकास cleanup_nsc(व्योम)
अणु
	अगर (pdev) अणु
		tpm_nsc_हटाओ(&pdev->dev);
		platक्रमm_device_unरेजिस्टर(pdev);
	पूर्ण

	platक्रमm_driver_unरेजिस्टर(&nsc_drv);
पूर्ण

module_init(init_nsc);
module_निकास(cleanup_nsc);

MODULE_AUTHOR("Leendert van Doorn (leendert@watson.ibm.com)");
MODULE_DESCRIPTION("TPM Driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
