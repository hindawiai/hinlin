<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IDT CPS Gen.2 Serial RapidIO चयन family support
 *
 * Copyright 2010 Integrated Device Technology, Inc.
 * Alexandre Bounine <alexandre.bounine@idt.com>
 */

#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/rio_ids.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/page.h>
#समावेश "../rio.h"

#घोषणा LOCAL_RTE_CONF_DESTID_SEL	0x010070
#घोषणा LOCAL_RTE_CONF_DESTID_SEL_PSEL	0x0000001f

#घोषणा IDT_LT_ERR_REPORT_EN	0x03100c

#घोषणा IDT_PORT_ERR_REPORT_EN(n)	(0x031044 + (n)*0x40)
#घोषणा IDT_PORT_ERR_REPORT_EN_BC	0x03ff04

#घोषणा IDT_PORT_ISERR_REPORT_EN(n)	(0x03104C + (n)*0x40)
#घोषणा IDT_PORT_ISERR_REPORT_EN_BC	0x03ff0c
#घोषणा IDT_PORT_INIT_TX_ACQUIRED	0x00000020

#घोषणा IDT_LANE_ERR_REPORT_EN(n)	(0x038010 + (n)*0x100)
#घोषणा IDT_LANE_ERR_REPORT_EN_BC	0x03ff10

#घोषणा IDT_DEV_CTRL_1		0xf2000c
#घोषणा IDT_DEV_CTRL_1_GENPW		0x02000000
#घोषणा IDT_DEV_CTRL_1_PRSTBEH		0x00000001

#घोषणा IDT_CFGBLK_ERR_CAPTURE_EN	0x020008
#घोषणा IDT_CFGBLK_ERR_REPORT		0xf20014
#घोषणा IDT_CFGBLK_ERR_REPORT_GENPW		0x00000002

#घोषणा IDT_AUX_PORT_ERR_CAP_EN	0x020000
#घोषणा IDT_AUX_ERR_REPORT_EN	0xf20018
#घोषणा IDT_AUX_PORT_ERR_LOG_I2C	0x00000002
#घोषणा IDT_AUX_PORT_ERR_LOG_JTAG	0x00000001

#घोषणा	IDT_ISLTL_ADDRESS_CAP	0x021014

#घोषणा IDT_RIO_DOMAIN		0xf20020
#घोषणा IDT_RIO_DOMAIN_MASK		0x000000ff

#घोषणा IDT_PW_INFO_CSR		0xf20024

#घोषणा IDT_SOFT_RESET		0xf20040
#घोषणा IDT_SOFT_RESET_REQ		0x00030097

#घोषणा IDT_I2C_MCTRL		0xf20050
#घोषणा IDT_I2C_MCTRL_GENPW		0x04000000

#घोषणा IDT_JTAG_CTRL		0xf2005c
#घोषणा IDT_JTAG_CTRL_GENPW		0x00000002

#घोषणा IDT_LANE_CTRL(n)	(0xff8000 + (n)*0x100)
#घोषणा IDT_LANE_CTRL_BC	0xffff00
#घोषणा IDT_LANE_CTRL_GENPW		0x00200000
#घोषणा IDT_LANE_DFE_1_BC	0xffff18
#घोषणा IDT_LANE_DFE_2_BC	0xffff1c

#घोषणा IDT_PORT_OPS(n)		(0xf40004 + (n)*0x100)
#घोषणा IDT_PORT_OPS_GENPW		0x08000000
#घोषणा IDT_PORT_OPS_PL_ELOG		0x00000040
#घोषणा IDT_PORT_OPS_LL_ELOG		0x00000020
#घोषणा IDT_PORT_OPS_LT_ELOG		0x00000010
#घोषणा IDT_PORT_OPS_BC		0xf4ff04

#घोषणा IDT_PORT_ISERR_DET(n)	(0xf40008 + (n)*0x100)

#घोषणा IDT_ERR_CAP		0xfd0000
#घोषणा IDT_ERR_CAP_LOG_OVERWR		0x00000004

#घोषणा IDT_ERR_RD		0xfd0004

#घोषणा IDT_DEFAULT_ROUTE	0xde
#घोषणा IDT_NO_ROUTE		0xdf

अटल पूर्णांक
idtg2_route_add_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 route_port)
अणु
	/*
	 * Select routing table to update
	 */
	अगर (table == RIO_GLOBAL_TABLE)
		table = 0;
	अन्यथा
		table++;

	अगर (route_port == RIO_INVALID_ROUTE)
		route_port = IDT_DEFAULT_ROUTE;

	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  LOCAL_RTE_CONF_DESTID_SEL, table);

	/*
	 * Program destination port क्रम the specअगरied destID
	 */
	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  RIO_STD_RTE_CONF_DESTID_SEL_CSR,
				  (u32)route_destid);

	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  RIO_STD_RTE_CONF_PORT_SEL_CSR,
				  (u32)route_port);
	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक
idtg2_route_get_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
अणु
	u32 result;

	/*
	 * Select routing table to पढ़ो
	 */
	अगर (table == RIO_GLOBAL_TABLE)
		table = 0;
	अन्यथा
		table++;

	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  LOCAL_RTE_CONF_DESTID_SEL, table);

	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  RIO_STD_RTE_CONF_DESTID_SEL_CSR,
				  route_destid);

	rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				 RIO_STD_RTE_CONF_PORT_SEL_CSR, &result);

	अगर (IDT_DEFAULT_ROUTE == (u8)result || IDT_NO_ROUTE == (u8)result)
		*route_port = RIO_INVALID_ROUTE;
	अन्यथा
		*route_port = (u8)result;

	वापस 0;
पूर्ण

अटल पूर्णांक
idtg2_route_clr_table(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table)
अणु
	u32 i;

	/*
	 * Select routing table to पढ़ो
	 */
	अगर (table == RIO_GLOBAL_TABLE)
		table = 0;
	अन्यथा
		table++;

	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  LOCAL_RTE_CONF_DESTID_SEL, table);

	क्रम (i = RIO_STD_RTE_CONF_EXTCFGEN;
	     i <= (RIO_STD_RTE_CONF_EXTCFGEN | 0xff);) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
			RIO_STD_RTE_CONF_DESTID_SEL_CSR, i);
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
			RIO_STD_RTE_CONF_PORT_SEL_CSR,
			(IDT_DEFAULT_ROUTE << 24) | (IDT_DEFAULT_ROUTE << 16) |
			(IDT_DEFAULT_ROUTE << 8) | IDT_DEFAULT_ROUTE);
		i += 4;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक
idtg2_set_करोमुख्य(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u8 sw_करोमुख्य)
अणु
	/*
	 * Switch करोमुख्य configuration operates only at global level
	 */
	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  IDT_RIO_DOMAIN, (u32)sw_करोमुख्य);
	वापस 0;
पूर्ण

अटल पूर्णांक
idtg2_get_करोमुख्य(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u8 *sw_करोमुख्य)
अणु
	u32 regval;

	/*
	 * Switch करोमुख्य configuration operates only at global level
	 */
	rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				IDT_RIO_DOMAIN, &regval);

	*sw_करोमुख्य = (u8)(regval & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक
idtg2_em_init(काष्ठा rio_dev *rdev)
अणु
	u32 regval;
	पूर्णांक i, पंचांगp;

	/*
	 * This routine perक्रमms device-specअगरic initialization only.
	 * All standard EM configuration should be perक्रमmed at upper level.
	 */

	pr_debug("RIO: %s [%d:%d]\n", __func__, rdev->destid, rdev->hopcount);

	/* Set Port-Write info CSR: PRIO=3 and CRF=1 */
	rio_ग_लिखो_config_32(rdev, IDT_PW_INFO_CSR, 0x0000e000);

	/*
	 * Configure LT LAYER error reporting.
	 */

	/* Enable standard (RIO.p8) error reporting */
	rio_ग_लिखो_config_32(rdev, IDT_LT_ERR_REPORT_EN,
			REM_LTL_ERR_ILLTRAN | REM_LTL_ERR_UNSOLR |
			REM_LTL_ERR_UNSUPTR);

	/* Use Port-Writes क्रम LT layer error reporting.
	 * Enable per-port reset
	 */
	rio_पढ़ो_config_32(rdev, IDT_DEV_CTRL_1, &regval);
	rio_ग_लिखो_config_32(rdev, IDT_DEV_CTRL_1,
			regval | IDT_DEV_CTRL_1_GENPW | IDT_DEV_CTRL_1_PRSTBEH);

	/*
	 * Configure PORT error reporting.
	 */

	/* Report all RIO.p8 errors supported by device */
	rio_ग_लिखो_config_32(rdev, IDT_PORT_ERR_REPORT_EN_BC, 0x807e8037);

	/* Configure reporting of implementation specअगरic errors/events */
	rio_ग_लिखो_config_32(rdev, IDT_PORT_ISERR_REPORT_EN_BC,
			    IDT_PORT_INIT_TX_ACQUIRED);

	/* Use Port-Writes क्रम port error reporting and enable error logging */
	पंचांगp = RIO_GET_TOTAL_PORTS(rdev->swpinfo);
	क्रम (i = 0; i < पंचांगp; i++) अणु
		rio_पढ़ो_config_32(rdev, IDT_PORT_OPS(i), &regval);
		rio_ग_लिखो_config_32(rdev,
				IDT_PORT_OPS(i), regval | IDT_PORT_OPS_GENPW |
				IDT_PORT_OPS_PL_ELOG |
				IDT_PORT_OPS_LL_ELOG |
				IDT_PORT_OPS_LT_ELOG);
	पूर्ण
	/* Overग_लिखो error log अगर full */
	rio_ग_लिखो_config_32(rdev, IDT_ERR_CAP, IDT_ERR_CAP_LOG_OVERWR);

	/*
	 * Configure LANE error reporting.
	 */

	/* Disable line error reporting */
	rio_ग_लिखो_config_32(rdev, IDT_LANE_ERR_REPORT_EN_BC, 0);

	/* Use Port-Writes क्रम lane error reporting (when enabled)
	 * (करो per-lane update because lanes may have dअगरferent configuration)
	 */
	पंचांगp = (rdev->did == RIO_DID_IDTCPS1848) ? 48 : 16;
	क्रम (i = 0; i < पंचांगp; i++) अणु
		rio_पढ़ो_config_32(rdev, IDT_LANE_CTRL(i), &regval);
		rio_ग_लिखो_config_32(rdev, IDT_LANE_CTRL(i),
				    regval | IDT_LANE_CTRL_GENPW);
	पूर्ण

	/*
	 * Configure AUX error reporting.
	 */

	/* Disable JTAG and I2C Error capture */
	rio_ग_लिखो_config_32(rdev, IDT_AUX_PORT_ERR_CAP_EN, 0);

	/* Disable JTAG and I2C Error reporting/logging */
	rio_ग_लिखो_config_32(rdev, IDT_AUX_ERR_REPORT_EN, 0);

	/* Disable Port-Write notअगरication from JTAG */
	rio_ग_लिखो_config_32(rdev, IDT_JTAG_CTRL, 0);

	/* Disable Port-Write notअगरication from I2C */
	rio_पढ़ो_config_32(rdev, IDT_I2C_MCTRL, &regval);
	rio_ग_लिखो_config_32(rdev, IDT_I2C_MCTRL, regval & ~IDT_I2C_MCTRL_GENPW);

	/*
	 * Configure CFG_BLK error reporting.
	 */

	/* Disable Configuration Block error capture */
	rio_ग_लिखो_config_32(rdev, IDT_CFGBLK_ERR_CAPTURE_EN, 0);

	/* Disable Port-Writes क्रम Configuration Block error reporting */
	rio_पढ़ो_config_32(rdev, IDT_CFGBLK_ERR_REPORT, &regval);
	rio_ग_लिखो_config_32(rdev, IDT_CFGBLK_ERR_REPORT,
			    regval & ~IDT_CFGBLK_ERR_REPORT_GENPW);

	/* set TVAL = ~50us */
	rio_ग_लिखो_config_32(rdev,
		rdev->phys_efptr + RIO_PORT_LINKTO_CTL_CSR, 0x8e << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक
idtg2_em_handler(काष्ठा rio_dev *rdev, u8 portnum)
अणु
	u32 regval, em_perrdet, em_ltlerrdet;

	rio_पढ़ो_config_32(rdev,
		rdev->em_efptr + RIO_EM_LTL_ERR_DETECT, &em_ltlerrdet);
	अगर (em_ltlerrdet) अणु
		/* Service Logical/Transport Layer Error(s) */
		अगर (em_ltlerrdet & REM_LTL_ERR_IMPSPEC) अणु
			/* Implementation specअगरic error reported */
			rio_पढ़ो_config_32(rdev,
					IDT_ISLTL_ADDRESS_CAP, &regval);

			pr_debug("RIO: %s Implementation Specific LTL errors" \
				 " 0x%x @(0x%x)\n",
				 rio_name(rdev), em_ltlerrdet, regval);

			/* Clear implementation specअगरic address capture CSR */
			rio_ग_लिखो_config_32(rdev, IDT_ISLTL_ADDRESS_CAP, 0);

		पूर्ण
	पूर्ण

	rio_पढ़ो_config_32(rdev,
		rdev->em_efptr + RIO_EM_PN_ERR_DETECT(portnum), &em_perrdet);
	अगर (em_perrdet) अणु
		/* Service Port-Level Error(s) */
		अगर (em_perrdet & REM_PED_IMPL_SPEC) अणु
			/* Implementation Specअगरic port error reported */

			/* Get IS errors reported */
			rio_पढ़ो_config_32(rdev,
					IDT_PORT_ISERR_DET(portnum), &regval);

			pr_debug("RIO: %s Implementation Specific Port" \
				 " errors 0x%x\n", rio_name(rdev), regval);

			/* Clear all implementation specअगरic events */
			rio_ग_लिखो_config_32(rdev,
					IDT_PORT_ISERR_DET(portnum), 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
idtg2_show_errlog(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	sमाप_प्रकार len = 0;
	u32 regval;

	जबतक (!rio_पढ़ो_config_32(rdev, IDT_ERR_RD, &regval)) अणु
		अगर (!regval)    /* 0 = end of log */
			अवरोध;
		len += snम_लिखो(buf + len, PAGE_SIZE - len,
					"%08x\n", regval);
		अगर (len >= (PAGE_SIZE - 10))
			अवरोध;
	पूर्ण

	वापस len;
पूर्ण

अटल DEVICE_ATTR(errlog, S_IRUGO, idtg2_show_errlog, शून्य);

अटल पूर्णांक idtg2_sysfs(काष्ठा rio_dev *rdev, bool create)
अणु
	काष्ठा device *dev = &rdev->dev;
	पूर्णांक err = 0;

	अगर (create) अणु
		/* Initialize sysfs entries */
		err = device_create_file(dev, &dev_attr_errlog);
		अगर (err)
			dev_err(dev, "Unable create sysfs errlog file\n");
	पूर्ण अन्यथा
		device_हटाओ_file(dev, &dev_attr_errlog);

	वापस err;
पूर्ण

अटल काष्ठा rio_चयन_ops idtg2_चयन_ops = अणु
	.owner = THIS_MODULE,
	.add_entry = idtg2_route_add_entry,
	.get_entry = idtg2_route_get_entry,
	.clr_table = idtg2_route_clr_table,
	.set_करोमुख्य = idtg2_set_करोमुख्य,
	.get_करोमुख्य = idtg2_get_करोमुख्य,
	.em_init = idtg2_em_init,
	.em_handle = idtg2_em_handler,
पूर्ण;

अटल पूर्णांक idtg2_probe(काष्ठा rio_dev *rdev, स्थिर काष्ठा rio_device_id *id)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));

	spin_lock(&rdev->rचयन->lock);

	अगर (rdev->rचयन->ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस -EINVAL;
	पूर्ण

	rdev->rचयन->ops = &idtg2_चयन_ops;

	अगर (rdev->करो_क्रमागत) अणु
		/* Ensure that शेष routing is disabled on startup */
		rio_ग_लिखो_config_32(rdev,
				    RIO_STD_RTE_DEFAULT_PORT, IDT_NO_ROUTE);
	पूर्ण

	spin_unlock(&rdev->rचयन->lock);

	/* Create device-specअगरic sysfs attributes */
	idtg2_sysfs(rdev, true);

	वापस 0;
पूर्ण

अटल व्योम idtg2_हटाओ(काष्ठा rio_dev *rdev)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));
	spin_lock(&rdev->rचयन->lock);
	अगर (rdev->rचयन->ops != &idtg2_चयन_ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस;
	पूर्ण
	rdev->rचयन->ops = शून्य;
	spin_unlock(&rdev->rचयन->lock);
	/* Remove device-specअगरic sysfs attributes */
	idtg2_sysfs(rdev, false);
पूर्ण

अटल स्थिर काष्ठा rio_device_id idtg2_id_table[] = अणु
	अणुRIO_DEVICE(RIO_DID_IDTCPS1848, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTCPS1616, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTVPS1616, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTSPS1616, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTCPS1432, RIO_VID_IDT)पूर्ण,
	अणु 0, पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा rio_driver idtg2_driver = अणु
	.name = "idt_gen2",
	.id_table = idtg2_id_table,
	.probe = idtg2_probe,
	.हटाओ = idtg2_हटाओ,
पूर्ण;

अटल पूर्णांक __init idtg2_init(व्योम)
अणु
	वापस rio_रेजिस्टर_driver(&idtg2_driver);
पूर्ण

अटल व्योम __निकास idtg2_निकास(व्योम)
अणु
	pr_debug("RIO: %s\n", __func__);
	rio_unरेजिस्टर_driver(&idtg2_driver);
	pr_debug("RIO: %s done\n", __func__);
पूर्ण

device_initcall(idtg2_init);
module_निकास(idtg2_निकास);

MODULE_DESCRIPTION("IDT CPS Gen.2 Serial RapidIO switch family driver");
MODULE_AUTHOR("Integrated Device Technology, Inc.");
MODULE_LICENSE("GPL");
