<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IDT RXS Gen.3 Serial RapidIO चयन family support
 *
 * Copyright 2016 Integrated Device Technology, Inc.
 */

#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/rio_ids.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/page.h>
#समावेश "../rio.h"

#घोषणा RIO_EM_PW_STAT		0x40020
#घोषणा RIO_PW_CTL		0x40204
#घोषणा RIO_PW_CTL_PW_TMR		0xffffff00
#घोषणा RIO_PW_ROUTE		0x40208

#घोषणा RIO_EM_DEV_INT_EN	0x40030

#घोषणा RIO_PLM_SPx_IMP_SPEC_CTL(x)	(0x10100 + (x)*0x100)
#घोषणा RIO_PLM_SPx_IMP_SPEC_CTL_SOFT_RST	0x02000000

#घोषणा RIO_PLM_SPx_PW_EN(x)	(0x10118 + (x)*0x100)
#घोषणा RIO_PLM_SPx_PW_EN_OK2U	0x40000000
#घोषणा RIO_PLM_SPx_PW_EN_LINIT 0x10000000

#घोषणा RIO_BC_L2_Gn_ENTRYx_CSR(n, x)	(0x31000 + (n)*0x400 + (x)*0x4)
#घोषणा RIO_SPx_L2_Gn_ENTRYy_CSR(x, n, y) \
				(0x51000 + (x)*0x2000 + (n)*0x400 + (y)*0x4)

अटल पूर्णांक
idtg3_route_add_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 route_port)
अणु
	u32 rval;
	u32 entry = route_port;
	पूर्णांक err = 0;

	pr_debug("RIO: %s t=0x%x did_%x to p_%x\n",
		 __func__, table, route_destid, entry);

	अगर (route_destid > 0xFF)
		वापस -EINVAL;

	अगर (route_port == RIO_INVALID_ROUTE)
		entry = RIO_RT_ENTRY_DROP_PKT;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		/* Use broadcast रेजिस्टर to update all per-port tables */
		err = rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_BC_L2_Gn_ENTRYx_CSR(0, route_destid),
				entry);
		वापस err;
	पूर्ण

	/*
	 * Verअगरy that specअगरied port/table number is valid
	 */
	err = rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				       RIO_SWP_INFO_CAR, &rval);
	अगर (err)
		वापस err;

	अगर (table >= RIO_GET_TOTAL_PORTS(rval))
		वापस -EINVAL;

	err = rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
			RIO_SPx_L2_Gn_ENTRYy_CSR(table, 0, route_destid),
			entry);
	वापस err;
पूर्ण

अटल पूर्णांक
idtg3_route_get_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
अणु
	u32 rval;
	पूर्णांक err;

	अगर (route_destid > 0xFF)
		वापस -EINVAL;

	err = rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				       RIO_SWP_INFO_CAR, &rval);
	अगर (err)
		वापस err;

	/*
	 * This चयन device करोes not have the dedicated global routing table.
	 * It is substituted by पढ़ोing routing table of the ingress port of
	 * मुख्यtenance पढ़ो requests.
	 */
	अगर (table == RIO_GLOBAL_TABLE)
		table = RIO_GET_PORT_NUM(rval);
	अन्यथा अगर (table >= RIO_GET_TOTAL_PORTS(rval))
		वापस -EINVAL;

	err = rio_mport_पढ़ो_config_32(mport, destid, hopcount,
			RIO_SPx_L2_Gn_ENTRYy_CSR(table, 0, route_destid),
			&rval);
	अगर (err)
		वापस err;

	अगर (rval == RIO_RT_ENTRY_DROP_PKT)
		*route_port = RIO_INVALID_ROUTE;
	अन्यथा
		*route_port = (u8)rval;

	वापस 0;
पूर्ण

अटल पूर्णांक
idtg3_route_clr_table(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table)
अणु
	u32 i;
	u32 rval;
	पूर्णांक err;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		क्रम (i = 0; i <= 0xff; i++) अणु
			err = rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
						RIO_BC_L2_Gn_ENTRYx_CSR(0, i),
						RIO_RT_ENTRY_DROP_PKT);
			अगर (err)
				अवरोध;
		पूर्ण

		वापस err;
	पूर्ण

	err = rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				       RIO_SWP_INFO_CAR, &rval);
	अगर (err)
		वापस err;

	अगर (table >= RIO_GET_TOTAL_PORTS(rval))
		वापस -EINVAL;

	क्रम (i = 0; i <= 0xff; i++) अणु
		err = rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					RIO_SPx_L2_Gn_ENTRYy_CSR(table, 0, i),
					RIO_RT_ENTRY_DROP_PKT);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/*
 * This routine perक्रमms device-specअगरic initialization only.
 * All standard EM configuration should be perक्रमmed at upper level.
 */
अटल पूर्णांक
idtg3_em_init(काष्ठा rio_dev *rdev)
अणु
	पूर्णांक i, पंचांगp;
	u32 rval;

	pr_debug("RIO: %s [%d:%d]\n", __func__, rdev->destid, rdev->hopcount);

	/* Disable निश्चितion of पूर्णांकerrupt संकेत */
	rio_ग_लिखो_config_32(rdev, RIO_EM_DEV_INT_EN, 0);

	/* Disable port-ग_लिखो event notअगरications during initialization */
	rio_ग_लिखो_config_32(rdev, rdev->em_efptr + RIO_EM_PW_TX_CTRL,
			    RIO_EM_PW_TX_CTRL_PW_DIS);

	/* Configure Port-Write notअगरications क्रम hot-swap events */
	पंचांगp = RIO_GET_TOTAL_PORTS(rdev->swpinfo);
	क्रम (i = 0; i < पंचांगp; i++) अणु

		rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_ERR_STS_CSR(rdev, i),
			&rval);
		अगर (rval & RIO_PORT_N_ERR_STS_PORT_UA)
			जारी;

		/* Clear events संकेतed beक्रमe enabling notअगरication */
		rio_ग_लिखो_config_32(rdev,
			rdev->em_efptr + RIO_EM_PN_ERR_DETECT(i), 0);

		/* Enable event notअगरications */
		rio_ग_लिखो_config_32(rdev,
			rdev->em_efptr + RIO_EM_PN_ERRRATE_EN(i),
			RIO_EM_PN_ERRRATE_EN_OK2U | RIO_EM_PN_ERRRATE_EN_U2OK);
		/* Enable port-ग_लिखो generation on events */
		rio_ग_लिखो_config_32(rdev, RIO_PLM_SPx_PW_EN(i),
			RIO_PLM_SPx_PW_EN_OK2U | RIO_PLM_SPx_PW_EN_LINIT);

	पूर्ण

	/* Set Port-Write destination port */
	पंचांगp = RIO_GET_PORT_NUM(rdev->swpinfo);
	rio_ग_लिखो_config_32(rdev, RIO_PW_ROUTE, 1 << पंचांगp);


	/* Enable sending port-ग_लिखो event notअगरications */
	rio_ग_लिखो_config_32(rdev, rdev->em_efptr + RIO_EM_PW_TX_CTRL, 0);

	/* set TVAL = ~50us */
	rio_ग_लिखो_config_32(rdev,
		rdev->phys_efptr + RIO_PORT_LINKTO_CTL_CSR, 0x8e << 8);
	वापस 0;
पूर्ण


/*
 * idtg3_em_handler - device-specअगरic error handler
 *
 * If the link is करोwn (PORT_UNINIT) करोes nothing - this is considered
 * as link partner removal from the port.
 *
 * If the link is up (PORT_OK) - situation is handled as *new* device insertion.
 * In this हाल ERR_STOP bits are cleared by issuing soft reset command to the
 * reporting port. Inbound and outbound ackIDs are cleared by the reset as well.
 * This way the port is synchronized with freshly inserted device (assuming it
 * was reset/घातered-up on insertion).
 *
 * TODO: This is not sufficient in a situation when a link between two devices
 * was करोwn and up again (e.g. cable disconnect). For that situation full ackID
 * realignment process has to be implemented.
 */
अटल पूर्णांक
idtg3_em_handler(काष्ठा rio_dev *rdev, u8 pnum)
अणु
	u32 err_status;
	u32 rval;

	rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_ERR_STS_CSR(rdev, pnum),
			&err_status);

	/* Do nothing क्रम device/link removal */
	अगर (err_status & RIO_PORT_N_ERR_STS_PORT_UNINIT)
		वापस 0;

	/* When link is OK we have a device insertion.
	 * Request port soft reset to clear errors अगर they present.
	 * Inbound and outbound ackIDs will be 0 after reset.
	 */
	अगर (err_status & (RIO_PORT_N_ERR_STS_OUT_ES |
				RIO_PORT_N_ERR_STS_INP_ES)) अणु
		rio_पढ़ो_config_32(rdev, RIO_PLM_SPx_IMP_SPEC_CTL(pnum), &rval);
		rio_ग_लिखो_config_32(rdev, RIO_PLM_SPx_IMP_SPEC_CTL(pnum),
				    rval | RIO_PLM_SPx_IMP_SPEC_CTL_SOFT_RST);
		udelay(10);
		rio_ग_लिखो_config_32(rdev, RIO_PLM_SPx_IMP_SPEC_CTL(pnum), rval);
		msleep(500);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा rio_चयन_ops idtg3_चयन_ops = अणु
	.owner = THIS_MODULE,
	.add_entry = idtg3_route_add_entry,
	.get_entry = idtg3_route_get_entry,
	.clr_table = idtg3_route_clr_table,
	.em_init   = idtg3_em_init,
	.em_handle = idtg3_em_handler,
पूर्ण;

अटल पूर्णांक idtg3_probe(काष्ठा rio_dev *rdev, स्थिर काष्ठा rio_device_id *id)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));

	spin_lock(&rdev->rचयन->lock);

	अगर (rdev->rचयन->ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस -EINVAL;
	पूर्ण

	rdev->rचयन->ops = &idtg3_चयन_ops;

	अगर (rdev->करो_क्रमागत) अणु
		/* Disable hierarchical routing support: Existing fabric
		 * क्रमागतeration/discovery process (see rio-scan.c) uses 8-bit
		 * flat destination ID routing only.
		 */
		rio_ग_लिखो_config_32(rdev, 0x5000 + RIO_BC_RT_CTL_CSR, 0);
	पूर्ण

	spin_unlock(&rdev->rचयन->lock);

	वापस 0;
पूर्ण

अटल व्योम idtg3_हटाओ(काष्ठा rio_dev *rdev)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));
	spin_lock(&rdev->rचयन->lock);
	अगर (rdev->rचयन->ops == &idtg3_चयन_ops)
		rdev->rचयन->ops = शून्य;
	spin_unlock(&rdev->rचयन->lock);
पूर्ण

/*
 * Gen3 चयनes repeat sending PW messages until a corresponding event flag
 * is cleared. Use shutकरोwn notअगरication to disable generation of port-ग_लिखो
 * messages अगर their destination node is shut करोwn.
 */
अटल व्योम idtg3_shutकरोwn(काष्ठा rio_dev *rdev)
अणु
	पूर्णांक i;
	u32 rval;
	u16 destid;

	/* Currently the क्रमागतerator node acts also as PW handler */
	अगर (!rdev->करो_क्रमागत)
		वापस;

	pr_debug("RIO: %s(%s)\n", __func__, rio_name(rdev));

	rio_पढ़ो_config_32(rdev, RIO_PW_ROUTE, &rval);
	i = RIO_GET_PORT_NUM(rdev->swpinfo);

	/* Check port-ग_लिखो destination port */
	अगर (!((1 << i) & rval))
		वापस;

	/* Disable sending port-ग_लिखो event notअगरications अगर PW destID
	 * matches to one of the क्रमागतerator node
	 */
	rio_पढ़ो_config_32(rdev, rdev->em_efptr + RIO_EM_PW_TGT_DEVID, &rval);

	अगर (rval & RIO_EM_PW_TGT_DEVID_DEV16)
		destid = rval >> 16;
	अन्यथा
		destid = ((rval & RIO_EM_PW_TGT_DEVID_D8) >> 16);

	अगर (rdev->net->hport->host_deviceid == destid) अणु
		rio_ग_लिखो_config_32(rdev,
				    rdev->em_efptr + RIO_EM_PW_TX_CTRL, 0);
		pr_debug("RIO: %s(%s) PW transmission disabled\n",
			 __func__, rio_name(rdev));
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rio_device_id idtg3_id_table[] = अणु
	अणुRIO_DEVICE(RIO_DID_IDTRXS1632, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTRXS2448, RIO_VID_IDT)पूर्ण,
	अणु 0, पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा rio_driver idtg3_driver = अणु
	.name = "idt_gen3",
	.id_table = idtg3_id_table,
	.probe = idtg3_probe,
	.हटाओ = idtg3_हटाओ,
	.shutकरोwn = idtg3_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init idtg3_init(व्योम)
अणु
	वापस rio_रेजिस्टर_driver(&idtg3_driver);
पूर्ण

अटल व्योम __निकास idtg3_निकास(व्योम)
अणु
	pr_debug("RIO: %s\n", __func__);
	rio_unरेजिस्टर_driver(&idtg3_driver);
	pr_debug("RIO: %s done\n", __func__);
पूर्ण

device_initcall(idtg3_init);
module_निकास(idtg3_निकास);

MODULE_DESCRIPTION("IDT RXS Gen.3 Serial RapidIO switch family driver");
MODULE_AUTHOR("Integrated Device Technology, Inc.");
MODULE_LICENSE("GPL");
