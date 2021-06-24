<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO Tsi57x चयन family support
 *
 * Copyright 2009-2010 Integrated Device Technology, Inc.
 * Alexandre Bounine <alexandre.bounine@idt.com>
 *  - Added EM support
 *  - Modअगरied चयन operations initialization.
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/rio_ids.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश "../rio.h"

/* Global (broadcast) route रेजिस्टरs */
#घोषणा SPBC_ROUTE_CFG_DESTID	0x10070
#घोषणा SPBC_ROUTE_CFG_PORT	0x10074

/* Per port route रेजिस्टरs */
#घोषणा SPP_ROUTE_CFG_DESTID(n)	(0x11070 + 0x100*n)
#घोषणा SPP_ROUTE_CFG_PORT(n)	(0x11074 + 0x100*n)

#घोषणा TSI578_SP_MODE(n)	(0x11004 + n*0x100)
#घोषणा TSI578_SP_MODE_GLBL	0x10004
#घोषणा  TSI578_SP_MODE_PW_DIS	0x08000000
#घोषणा  TSI578_SP_MODE_LUT_512	0x01000000

#घोषणा TSI578_SP_CTL_INDEP(n)	(0x13004 + n*0x100)
#घोषणा TSI578_SP_LUT_PEINF(n)	(0x13010 + n*0x100)
#घोषणा TSI578_SP_CS_TX(n)	(0x13014 + n*0x100)
#घोषणा TSI578_SP_INT_STATUS(n) (0x13018 + n*0x100)

#घोषणा TSI578_GLBL_ROUTE_BASE	0x10078

अटल पूर्णांक
tsi57x_route_add_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 route_port)
अणु
	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					  SPBC_ROUTE_CFG_DESTID, route_destid);
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					  SPBC_ROUTE_CFG_PORT, route_port);
	पूर्ण अन्यथा अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_DESTID(table), route_destid);
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_PORT(table), route_port);
	पूर्ण

	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक
tsi57x_route_get_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
अणु
	पूर्णांक ret = 0;
	u32 result;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		/* Use local RT of the ingress port to aव्योम possible
		   race condition */
		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
			RIO_SWP_INFO_CAR, &result);
		table = (result & RIO_SWP_INFO_PORT_NUM_MASK);
	पूर्ण

	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_DESTID(table), route_destid);
	rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_PORT(table), &result);

	*route_port = (u8)result;
	अगर (*route_port > 15)
		ret = -1;

	वापस ret;
पूर्ण

अटल पूर्णांक
tsi57x_route_clr_table(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table)
अणु
	u32 route_idx;
	u32 lut_size;

	lut_size = (mport->sys_size) ? 0x1ff : 0xff;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					  SPBC_ROUTE_CFG_DESTID, 0x80000000);
		क्रम (route_idx = 0; route_idx <= lut_size; route_idx++)
			rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
						  SPBC_ROUTE_CFG_PORT,
						  RIO_INVALID_ROUTE);
	पूर्ण अन्यथा अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_DESTID(table), 0x80000000);
		क्रम (route_idx = 0; route_idx <= lut_size; route_idx++)
			rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_PORT(table) , RIO_INVALID_ROUTE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
tsi57x_set_करोमुख्य(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u8 sw_करोमुख्य)
अणु
	u32 regval;

	/*
	 * Switch करोमुख्य configuration operates only at global level
	 */

	/* Turn off flat (LUT_512) mode */
	rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				 TSI578_SP_MODE_GLBL, &regval);
	rio_mport_ग_लिखो_config_32(mport, destid, hopcount, TSI578_SP_MODE_GLBL,
				  regval & ~TSI578_SP_MODE_LUT_512);
	/* Set चयन करोमुख्य base */
	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  TSI578_GLBL_ROUTE_BASE,
				  (u32)(sw_करोमुख्य << 24));
	वापस 0;
पूर्ण

अटल पूर्णांक
tsi57x_get_करोमुख्य(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u8 *sw_करोमुख्य)
अणु
	u32 regval;

	/*
	 * Switch करोमुख्य configuration operates only at global level
	 */
	rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				TSI578_GLBL_ROUTE_BASE, &regval);

	*sw_करोमुख्य = (u8)(regval >> 24);

	वापस 0;
पूर्ण

अटल पूर्णांक
tsi57x_em_init(काष्ठा rio_dev *rdev)
अणु
	u32 regval;
	पूर्णांक portnum;

	pr_debug("TSI578 %s [%d:%d]\n", __func__, rdev->destid, rdev->hopcount);

	क्रम (portnum = 0;
	     portnum < RIO_GET_TOTAL_PORTS(rdev->swpinfo); portnum++) अणु
		/* Make sure that Port-Writes are enabled (क्रम all ports) */
		rio_पढ़ो_config_32(rdev,
				TSI578_SP_MODE(portnum), &regval);
		rio_ग_लिखो_config_32(rdev,
				TSI578_SP_MODE(portnum),
				regval & ~TSI578_SP_MODE_PW_DIS);

		/* Clear all pending पूर्णांकerrupts */
		rio_पढ़ो_config_32(rdev,
				RIO_DEV_PORT_N_ERR_STS_CSR(rdev, portnum),
				&regval);
		rio_ग_लिखो_config_32(rdev,
				RIO_DEV_PORT_N_ERR_STS_CSR(rdev, portnum),
				regval & 0x07120214);

		rio_पढ़ो_config_32(rdev,
				TSI578_SP_INT_STATUS(portnum), &regval);
		rio_ग_लिखो_config_32(rdev,
				TSI578_SP_INT_STATUS(portnum),
				regval & 0x000700bd);

		/* Enable all पूर्णांकerrupts to allow ports to send a port-ग_लिखो */
		rio_पढ़ो_config_32(rdev,
				TSI578_SP_CTL_INDEP(portnum), &regval);
		rio_ग_लिखो_config_32(rdev,
				TSI578_SP_CTL_INDEP(portnum),
				regval | 0x000b0000);

		/* Skip next (odd) port अगर the current port is in x4 mode */
		rio_पढ़ो_config_32(rdev,
				RIO_DEV_PORT_N_CTL_CSR(rdev, portnum),
				&regval);
		अगर ((regval & RIO_PORT_N_CTL_PWIDTH) == RIO_PORT_N_CTL_PWIDTH_4)
			portnum++;
	पूर्ण

	/* set TVAL = ~50us */
	rio_ग_लिखो_config_32(rdev,
		rdev->phys_efptr + RIO_PORT_LINKTO_CTL_CSR, 0x9a << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक
tsi57x_em_handler(काष्ठा rio_dev *rdev, u8 portnum)
अणु
	काष्ठा rio_mport *mport = rdev->net->hport;
	u32 पूर्णांकstat, err_status;
	पूर्णांक sendcount, checkcount;
	u8 route_port;
	u32 regval;

	rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_ERR_STS_CSR(rdev, portnum),
			&err_status);

	अगर ((err_status & RIO_PORT_N_ERR_STS_PORT_OK) &&
	    (err_status & (RIO_PORT_N_ERR_STS_OUT_ES |
			  RIO_PORT_N_ERR_STS_INP_ES))) अणु
		/* Remove any queued packets by locking/unlocking port */
		rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_CTL_CSR(rdev, portnum),
			&regval);
		अगर (!(regval & RIO_PORT_N_CTL_LOCKOUT)) अणु
			rio_ग_लिखो_config_32(rdev,
				RIO_DEV_PORT_N_CTL_CSR(rdev, portnum),
				regval | RIO_PORT_N_CTL_LOCKOUT);
			udelay(50);
			rio_ग_लिखो_config_32(rdev,
				RIO_DEV_PORT_N_CTL_CSR(rdev, portnum),
				regval);
		पूर्ण

		/* Read from link मुख्यtenance response रेजिस्टर to clear
		 * valid bit
		 */
		rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_MNT_RSP_CSR(rdev, portnum),
			&regval);

		/* Send a Packet-Not-Accepted/Link-Request-Input-Status control
		 * symbol to recover from IES/OES
		 */
		sendcount = 3;
		जबतक (sendcount) अणु
			rio_ग_लिखो_config_32(rdev,
					  TSI578_SP_CS_TX(portnum), 0x40fc8000);
			checkcount = 3;
			जबतक (checkcount--) अणु
				udelay(50);
				rio_पढ़ो_config_32(rdev,
					RIO_DEV_PORT_N_MNT_RSP_CSR(rdev,
								   portnum),
					&regval);
				अगर (regval & RIO_PORT_N_MNT_RSP_RVAL)
					जाओ निकास_es;
			पूर्ण

			sendcount--;
		पूर्ण
	पूर्ण

निकास_es:
	/* Clear implementation specअगरic error status bits */
	rio_पढ़ो_config_32(rdev, TSI578_SP_INT_STATUS(portnum), &पूर्णांकstat);
	pr_debug("TSI578[%x:%x] SP%d_INT_STATUS=0x%08x\n",
		 rdev->destid, rdev->hopcount, portnum, पूर्णांकstat);

	अगर (पूर्णांकstat & 0x10000) अणु
		rio_पढ़ो_config_32(rdev,
				TSI578_SP_LUT_PEINF(portnum), &regval);
		regval = (mport->sys_size) ? (regval >> 16) : (regval >> 24);
		route_port = rdev->rचयन->route_table[regval];
		pr_debug("RIO: TSI578[%s] P%d LUT Parity Error (destID=%d)\n",
			rio_name(rdev), portnum, regval);
		tsi57x_route_add_entry(mport, rdev->destid, rdev->hopcount,
				RIO_GLOBAL_TABLE, regval, route_port);
	पूर्ण

	rio_ग_लिखो_config_32(rdev, TSI578_SP_INT_STATUS(portnum),
			    पूर्णांकstat & 0x000700bd);

	वापस 0;
पूर्ण

अटल काष्ठा rio_चयन_ops tsi57x_चयन_ops = अणु
	.owner = THIS_MODULE,
	.add_entry = tsi57x_route_add_entry,
	.get_entry = tsi57x_route_get_entry,
	.clr_table = tsi57x_route_clr_table,
	.set_करोमुख्य = tsi57x_set_करोमुख्य,
	.get_करोमुख्य = tsi57x_get_करोमुख्य,
	.em_init = tsi57x_em_init,
	.em_handle = tsi57x_em_handler,
पूर्ण;

अटल पूर्णांक tsi57x_probe(काष्ठा rio_dev *rdev, स्थिर काष्ठा rio_device_id *id)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));

	spin_lock(&rdev->rचयन->lock);

	अगर (rdev->rचयन->ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस -EINVAL;
	पूर्ण
	rdev->rचयन->ops = &tsi57x_चयन_ops;

	अगर (rdev->करो_क्रमागत) अणु
		/* Ensure that शेष routing is disabled on startup */
		rio_ग_लिखो_config_32(rdev, RIO_STD_RTE_DEFAULT_PORT,
				    RIO_INVALID_ROUTE);
	पूर्ण

	spin_unlock(&rdev->rचयन->lock);
	वापस 0;
पूर्ण

अटल व्योम tsi57x_हटाओ(काष्ठा rio_dev *rdev)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));
	spin_lock(&rdev->rचयन->lock);
	अगर (rdev->rचयन->ops != &tsi57x_चयन_ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस;
	पूर्ण
	rdev->rचयन->ops = शून्य;
	spin_unlock(&rdev->rचयन->lock);
पूर्ण

अटल स्थिर काष्ठा rio_device_id tsi57x_id_table[] = अणु
	अणुRIO_DEVICE(RIO_DID_TSI572, RIO_VID_TUNDRA)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_TSI574, RIO_VID_TUNDRA)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_TSI577, RIO_VID_TUNDRA)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_TSI578, RIO_VID_TUNDRA)पूर्ण,
	अणु 0, पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा rio_driver tsi57x_driver = अणु
	.name = "tsi57x",
	.id_table = tsi57x_id_table,
	.probe = tsi57x_probe,
	.हटाओ = tsi57x_हटाओ,
पूर्ण;

अटल पूर्णांक __init tsi57x_init(व्योम)
अणु
	वापस rio_रेजिस्टर_driver(&tsi57x_driver);
पूर्ण

अटल व्योम __निकास tsi57x_निकास(व्योम)
अणु
	rio_unरेजिस्टर_driver(&tsi57x_driver);
पूर्ण

device_initcall(tsi57x_init);
module_निकास(tsi57x_निकास);

MODULE_DESCRIPTION("IDT Tsi57x Serial RapidIO switch family driver");
MODULE_AUTHOR("Integrated Device Technology, Inc.");
MODULE_LICENSE("GPL");
