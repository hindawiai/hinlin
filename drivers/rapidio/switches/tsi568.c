<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO Tsi568 चयन support
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

#घोषणा TSI568_SP_MODE(n)	(0x11004 + 0x100*n)
#घोषणा  TSI568_SP_MODE_PW_DIS	0x08000000

अटल पूर्णांक
tsi568_route_add_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 route_port)
अणु
	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					SPBC_ROUTE_CFG_DESTID, route_destid);
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					SPBC_ROUTE_CFG_PORT, route_port);
	पूर्ण अन्यथा अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					SPP_ROUTE_CFG_DESTID(table),
					route_destid);
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					SPP_ROUTE_CFG_PORT(table), route_port);
	पूर्ण

	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक
tsi568_route_get_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
अणु
	पूर्णांक ret = 0;
	u32 result;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					SPBC_ROUTE_CFG_DESTID, route_destid);
		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
					SPBC_ROUTE_CFG_PORT, &result);
	पूर्ण अन्यथा अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					SPP_ROUTE_CFG_DESTID(table),
					route_destid);
		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
					SPP_ROUTE_CFG_PORT(table), &result);
	पूर्ण

	*route_port = result;
	अगर (*route_port > 15)
		ret = -1;

	वापस ret;
पूर्ण

अटल पूर्णांक
tsi568_route_clr_table(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
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
					SPP_ROUTE_CFG_DESTID(table),
					0x80000000);
		क्रम (route_idx = 0; route_idx <= lut_size; route_idx++)
			rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
						SPP_ROUTE_CFG_PORT(table),
						RIO_INVALID_ROUTE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
tsi568_em_init(काष्ठा rio_dev *rdev)
अणु
	u32 regval;
	पूर्णांक portnum;

	pr_debug("TSI568 %s [%d:%d]\n", __func__, rdev->destid, rdev->hopcount);

	/* Make sure that Port-Writes are disabled (क्रम all ports) */
	क्रम (portnum = 0;
	     portnum < RIO_GET_TOTAL_PORTS(rdev->swpinfo); portnum++) अणु
		rio_पढ़ो_config_32(rdev, TSI568_SP_MODE(portnum), &regval);
		rio_ग_लिखो_config_32(rdev, TSI568_SP_MODE(portnum),
				    regval | TSI568_SP_MODE_PW_DIS);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा rio_चयन_ops tsi568_चयन_ops = अणु
	.owner = THIS_MODULE,
	.add_entry = tsi568_route_add_entry,
	.get_entry = tsi568_route_get_entry,
	.clr_table = tsi568_route_clr_table,
	.set_करोमुख्य = शून्य,
	.get_करोमुख्य = शून्य,
	.em_init = tsi568_em_init,
	.em_handle = शून्य,
पूर्ण;

अटल पूर्णांक tsi568_probe(काष्ठा rio_dev *rdev, स्थिर काष्ठा rio_device_id *id)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));

	spin_lock(&rdev->rचयन->lock);

	अगर (rdev->rचयन->ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस -EINVAL;
	पूर्ण

	rdev->rचयन->ops = &tsi568_चयन_ops;
	spin_unlock(&rdev->rचयन->lock);
	वापस 0;
पूर्ण

अटल व्योम tsi568_हटाओ(काष्ठा rio_dev *rdev)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));
	spin_lock(&rdev->rचयन->lock);
	अगर (rdev->rचयन->ops != &tsi568_चयन_ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस;
	पूर्ण
	rdev->rचयन->ops = शून्य;
	spin_unlock(&rdev->rचयन->lock);
पूर्ण

अटल स्थिर काष्ठा rio_device_id tsi568_id_table[] = अणु
	अणुRIO_DEVICE(RIO_DID_TSI568, RIO_VID_TUNDRA)पूर्ण,
	अणु 0, पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा rio_driver tsi568_driver = अणु
	.name = "tsi568",
	.id_table = tsi568_id_table,
	.probe = tsi568_probe,
	.हटाओ = tsi568_हटाओ,
पूर्ण;

अटल पूर्णांक __init tsi568_init(व्योम)
अणु
	वापस rio_रेजिस्टर_driver(&tsi568_driver);
पूर्ण

अटल व्योम __निकास tsi568_निकास(व्योम)
अणु
	rio_unरेजिस्टर_driver(&tsi568_driver);
पूर्ण

device_initcall(tsi568_init);
module_निकास(tsi568_निकास);

MODULE_DESCRIPTION("IDT Tsi568 Serial RapidIO switch driver");
MODULE_AUTHOR("Integrated Device Technology, Inc.");
MODULE_LICENSE("GPL");
