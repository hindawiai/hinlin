<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IDT CPS RapidIO चयनes support
 *
 * Copyright 2009-2010 Integrated Device Technology, Inc.
 * Alexandre Bounine <alexandre.bounine@idt.com>
 */

#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/rio_ids.h>
#समावेश <linux/module.h>
#समावेश "../rio.h"

#घोषणा CPS_DEFAULT_ROUTE	0xde
#घोषणा CPS_NO_ROUTE		0xdf

#घोषणा IDTCPS_RIO_DOMAIN 0xf20020

अटल पूर्णांक
idtcps_route_add_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 route_port)
अणु
	u32 result;

	अगर (route_port == RIO_INVALID_ROUTE)
		route_port = CPS_DEFAULT_ROUTE;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_DESTID_SEL_CSR, route_destid);

		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_PORT_SEL_CSR, &result);

		result = (0xffffff00 & result) | (u32)route_port;
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_PORT_SEL_CSR, result);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
idtcps_route_get_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
अणु
	u32 result;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_DESTID_SEL_CSR, route_destid);

		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_PORT_SEL_CSR, &result);

		अगर (CPS_DEFAULT_ROUTE == (u8)result ||
		    CPS_NO_ROUTE == (u8)result)
			*route_port = RIO_INVALID_ROUTE;
		अन्यथा
			*route_port = (u8)result;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
idtcps_route_clr_table(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table)
अणु
	u32 i;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		क्रम (i = 0x80000000; i <= 0x800000ff;) अणु
			rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_DESTID_SEL_CSR, i);
			rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_PORT_SEL_CSR,
				(CPS_DEFAULT_ROUTE << 24) |
				(CPS_DEFAULT_ROUTE << 16) |
				(CPS_DEFAULT_ROUTE << 8) | CPS_DEFAULT_ROUTE);
			i += 4;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
idtcps_set_करोमुख्य(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u8 sw_करोमुख्य)
अणु
	/*
	 * Switch करोमुख्य configuration operates only at global level
	 */
	rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				  IDTCPS_RIO_DOMAIN, (u32)sw_करोमुख्य);
	वापस 0;
पूर्ण

अटल पूर्णांक
idtcps_get_करोमुख्य(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
		       u8 *sw_करोमुख्य)
अणु
	u32 regval;

	/*
	 * Switch करोमुख्य configuration operates only at global level
	 */
	rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				IDTCPS_RIO_DOMAIN, &regval);

	*sw_करोमुख्य = (u8)(regval & 0xff);

	वापस 0;
पूर्ण

अटल काष्ठा rio_चयन_ops idtcps_चयन_ops = अणु
	.owner = THIS_MODULE,
	.add_entry = idtcps_route_add_entry,
	.get_entry = idtcps_route_get_entry,
	.clr_table = idtcps_route_clr_table,
	.set_करोमुख्य = idtcps_set_करोमुख्य,
	.get_करोमुख्य = idtcps_get_करोमुख्य,
	.em_init = शून्य,
	.em_handle = शून्य,
पूर्ण;

अटल पूर्णांक idtcps_probe(काष्ठा rio_dev *rdev, स्थिर काष्ठा rio_device_id *id)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));

	spin_lock(&rdev->rचयन->lock);

	अगर (rdev->rचयन->ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस -EINVAL;
	पूर्ण

	rdev->rचयन->ops = &idtcps_चयन_ops;

	अगर (rdev->करो_क्रमागत) अणु
		/* set TVAL = ~50us */
		rio_ग_लिखो_config_32(rdev,
			rdev->phys_efptr + RIO_PORT_LINKTO_CTL_CSR, 0x8e << 8);
		/* Ensure that शेष routing is disabled on startup */
		rio_ग_लिखो_config_32(rdev,
				    RIO_STD_RTE_DEFAULT_PORT, CPS_NO_ROUTE);
	पूर्ण

	spin_unlock(&rdev->rचयन->lock);
	वापस 0;
पूर्ण

अटल व्योम idtcps_हटाओ(काष्ठा rio_dev *rdev)
अणु
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));
	spin_lock(&rdev->rचयन->lock);
	अगर (rdev->rचयन->ops != &idtcps_चयन_ops) अणु
		spin_unlock(&rdev->rचयन->lock);
		वापस;
	पूर्ण
	rdev->rचयन->ops = शून्य;
	spin_unlock(&rdev->rचयन->lock);
पूर्ण

अटल स्थिर काष्ठा rio_device_id idtcps_id_table[] = अणु
	अणुRIO_DEVICE(RIO_DID_IDTCPS6Q, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTCPS8, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTCPS10Q, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTCPS12, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDTCPS16, RIO_VID_IDT)पूर्ण,
	अणुRIO_DEVICE(RIO_DID_IDT70K200, RIO_VID_IDT)पूर्ण,
	अणु 0, पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा rio_driver idtcps_driver = अणु
	.name = "idtcps",
	.id_table = idtcps_id_table,
	.probe = idtcps_probe,
	.हटाओ = idtcps_हटाओ,
पूर्ण;

अटल पूर्णांक __init idtcps_init(व्योम)
अणु
	वापस rio_रेजिस्टर_driver(&idtcps_driver);
पूर्ण

अटल व्योम __निकास idtcps_निकास(व्योम)
अणु
	rio_unरेजिस्टर_driver(&idtcps_driver);
पूर्ण

device_initcall(idtcps_init);
module_निकास(idtcps_निकास);

MODULE_DESCRIPTION("IDT CPS Gen.1 Serial RapidIO switch family driver");
MODULE_AUTHOR("Integrated Device Technology, Inc.");
MODULE_LICENSE("GPL");
