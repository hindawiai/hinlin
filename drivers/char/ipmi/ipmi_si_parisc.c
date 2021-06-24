<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/module.h>
#समावेश <यंत्र/hardware.h>	/* क्रम रेजिस्टर_parisc_driver() stuff */
#समावेश <यंत्र/parisc-device.h>
#समावेश "ipmi_si.h"

अटल bool parisc_रेजिस्टरed;

अटल पूर्णांक __init ipmi_parisc_probe(काष्ठा parisc_device *dev)
अणु
	काष्ठा si_sm_io io;

	स_रखो(&io, 0, माप(io));

	io.si_type	= SI_KCS;
	io.addr_source	= SI_DEVICETREE;
	io.addr_space	= IPMI_MEM_ADDR_SPACE;
	io.addr_data	= dev->hpa.start;
	io.regsize	= 1;
	io.regspacing	= 1;
	io.regshअगरt	= 0;
	io.irq		= 0; /* no पूर्णांकerrupt */
	io.irq_setup	= शून्य;
	io.dev		= &dev->dev;

	dev_dbg(&dev->dev, "addr 0x%lx\n", io.addr_data);

	वापस ipmi_si_add_smi(&io);
पूर्ण

अटल पूर्णांक __निकास ipmi_parisc_हटाओ(काष्ठा parisc_device *dev)
अणु
	वापस ipmi_si_हटाओ_by_dev(&dev->dev);
पूर्ण

अटल स्थिर काष्ठा parisc_device_id ipmi_parisc_tbl[] __initस्थिर = अणु
	अणु HPHW_MC, HVERSION_REV_ANY_ID, 0x004, 0xC0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, ipmi_parisc_tbl);

अटल काष्ठा parisc_driver ipmi_parisc_driver __refdata = अणु
	.name =		"ipmi",
	.id_table =	ipmi_parisc_tbl,
	.probe =	ipmi_parisc_probe,
	.हटाओ =	__निकास_p(ipmi_parisc_हटाओ),
पूर्ण;

व्योम ipmi_si_parisc_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&ipmi_parisc_driver);
	parisc_रेजिस्टरed = true;
पूर्ण

व्योम ipmi_si_parisc_shutकरोwn(व्योम)
अणु
	अगर (parisc_रेजिस्टरed)
		unरेजिस्टर_parisc_driver(&ipmi_parisc_driver);
पूर्ण
