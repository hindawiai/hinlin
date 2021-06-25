<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_si_platक्रमm.c
 *
 * Handling क्रम platक्रमm devices in IPMI (ACPI, OF, and things
 * coming from the platक्रमm.
 */

#घोषणा pr_fmt(fmt) "ipmi_platform: " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/acpi.h>
#समावेश "ipmi_si.h"
#समावेश "ipmi_dmi.h"

अटल bool platक्रमm_रेजिस्टरed;
अटल bool si_tryplatक्रमm = true;
#अगर_घोषित CONFIG_ACPI
अटल bool          si_tryacpi = true;
#पूर्ण_अगर
#अगर_घोषित CONFIG_OF
अटल bool          si_tryखोलोfirmware = true;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DMI
अटल bool          si_trydmi = true;
#अन्यथा
अटल bool          si_trydmi = false;
#पूर्ण_अगर

module_param_named(tryplatक्रमm, si_tryplatक्रमm, bool, 0);
MODULE_PARM_DESC(tryplatक्रमm,
		 "Setting this to zero will disable the default scan of the interfaces identified via platform interfaces besides ACPI, OpenFirmware, and DMI");
#अगर_घोषित CONFIG_ACPI
module_param_named(tryacpi, si_tryacpi, bool, 0);
MODULE_PARM_DESC(tryacpi,
		 "Setting this to zero will disable the default scan of the interfaces identified via ACPI");
#पूर्ण_अगर
#अगर_घोषित CONFIG_OF
module_param_named(tryखोलोfirmware, si_tryखोलोfirmware, bool, 0);
MODULE_PARM_DESC(tryखोलोfirmware,
		 "Setting this to zero will disable the default scan of the interfaces identified via OpenFirmware");
#पूर्ण_अगर
#अगर_घोषित CONFIG_DMI
module_param_named(trydmi, si_trydmi, bool, 0);
MODULE_PARM_DESC(trydmi,
		 "Setting this to zero will disable the default scan of the interfaces identified via DMI");
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
/* For GPE-type पूर्णांकerrupts. */
अटल u32 ipmi_acpi_gpe(acpi_handle gpe_device,
	u32 gpe_number, व्योम *context)
अणु
	काष्ठा si_sm_io *io = context;

	ipmi_si_irq_handler(io->irq, io->irq_handler_data);
	वापस ACPI_INTERRUPT_HANDLED;
पूर्ण

अटल व्योम acpi_gpe_irq_cleanup(काष्ठा si_sm_io *io)
अणु
	अगर (!io->irq)
		वापस;

	ipmi_irq_start_cleanup(io);
	acpi_हटाओ_gpe_handler(शून्य, io->irq, &ipmi_acpi_gpe);
पूर्ण

अटल पूर्णांक acpi_gpe_irq_setup(काष्ठा si_sm_io *io)
अणु
	acpi_status status;

	अगर (!io->irq)
		वापस 0;

	status = acpi_install_gpe_handler(शून्य,
					  io->irq,
					  ACPI_GPE_LEVEL_TRIGGERED,
					  &ipmi_acpi_gpe,
					  io);
	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(io->dev,
			 "Unable to claim ACPI GPE %d, running polled\n",
			 io->irq);
		io->irq = 0;
		वापस -EINVAL;
	पूर्ण

	io->irq_cleanup = acpi_gpe_irq_cleanup;
	ipmi_irq_finish_setup(io);
	dev_info(io->dev, "Using ACPI GPE %d\n", io->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम ipmi_set_addr_data_and_space(काष्ठा resource *r, काष्ठा si_sm_io *io)
अणु
	अगर (resource_type(r) == IORESOURCE_IO)
		io->addr_space = IPMI_IO_ADDR_SPACE;
	अन्यथा
		io->addr_space = IPMI_MEM_ADDR_SPACE;
	io->addr_data = r->start;
पूर्ण

अटल काष्ठा resource *
ipmi_get_info_from_resources(काष्ठा platक्रमm_device *pdev,
			     काष्ठा si_sm_io *io)
अणु
	काष्ठा resource *res, *res_second;

	res = platक्रमm_get_mem_or_io(pdev, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no I/O or memory address\n");
		वापस शून्य;
	पूर्ण
	ipmi_set_addr_data_and_space(res, io);

	io->regspacing = DEFAULT_REGSPACING;
	res_second = platक्रमm_get_mem_or_io(pdev, 1);
	अगर (res_second && resource_type(res_second) == resource_type(res)) अणु
		अगर (res_second->start > io->addr_data)
			io->regspacing = res_second->start - io->addr_data;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक platक्रमm_ipmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा si_sm_io io;
	u8 type, slave_addr, addr_source, regsize, regshअगरt;
	पूर्णांक rv;

	rv = device_property_पढ़ो_u8(&pdev->dev, "addr-source", &addr_source);
	अगर (rv)
		addr_source = SI_PLATFORM;
	अगर (addr_source >= SI_LAST)
		वापस -EINVAL;

	अगर (addr_source == SI_SMBIOS) अणु
		अगर (!si_trydmi)
			वापस -ENODEV;
	पूर्ण अन्यथा अगर (addr_source != SI_HARDCODED) अणु
		अगर (!si_tryplatक्रमm)
			वापस -ENODEV;
	पूर्ण

	rv = device_property_पढ़ो_u8(&pdev->dev, "ipmi-type", &type);
	अगर (rv)
		वापस -ENODEV;

	स_रखो(&io, 0, माप(io));
	io.addr_source = addr_source;
	dev_info(&pdev->dev, "probing via %s\n",
		 ipmi_addr_src_to_str(addr_source));

	चयन (type) अणु
	हाल SI_KCS:
	हाल SI_SMIC:
	हाल SI_BT:
		io.si_type = type;
		अवरोध;
	हाल SI_TYPE_INVALID: /* User disabled this in hardcode. */
		वापस -ENODEV;
	शेष:
		dev_err(&pdev->dev, "ipmi-type property is invalid\n");
		वापस -EINVAL;
	पूर्ण

	io.regsize = DEFAULT_REGSIZE;
	rv = device_property_पढ़ो_u8(&pdev->dev, "reg-size", &regsize);
	अगर (!rv)
		io.regsize = regsize;

	io.regshअगरt = 0;
	rv = device_property_पढ़ो_u8(&pdev->dev, "reg-shift", &regshअगरt);
	अगर (!rv)
		io.regshअगरt = regshअगरt;

	अगर (!ipmi_get_info_from_resources(pdev, &io))
		वापस -EINVAL;

	rv = device_property_पढ़ो_u8(&pdev->dev, "slave-addr", &slave_addr);
	अगर (rv)
		io.slave_addr = 0x20;
	अन्यथा
		io.slave_addr = slave_addr;

	io.irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (io.irq > 0)
		io.irq_setup = ipmi_std_irq_setup;
	अन्यथा
		io.irq = 0;

	io.dev = &pdev->dev;

	pr_info("ipmi_si: %s: %s %#lx regsize %d spacing %d irq %d\n",
		ipmi_addr_src_to_str(addr_source),
		(io.addr_space == IPMI_IO_ADDR_SPACE) ? "io" : "mem",
		io.addr_data, io.regsize, io.regspacing, io.irq);

	ipmi_si_add_smi(&io);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_ipmi_match[] = अणु
	अणु .type = "ipmi", .compatible = "ipmi-kcs",
	  .data = (व्योम *)(अचिन्हित दीर्घ) SI_KCS पूर्ण,
	अणु .type = "ipmi", .compatible = "ipmi-smic",
	  .data = (व्योम *)(अचिन्हित दीर्घ) SI_SMIC पूर्ण,
	अणु .type = "ipmi", .compatible = "ipmi-bt",
	  .data = (व्योम *)(अचिन्हित दीर्घ) SI_BT पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ipmi_match);

अटल पूर्णांक of_ipmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा si_sm_io io;
	काष्ठा resource resource;
	स्थिर __be32 *regsize, *regspacing, *regshअगरt;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;
	पूर्णांक proplen;

	अगर (!si_tryखोलोfirmware)
		वापस -ENODEV;

	dev_info(&pdev->dev, "probing via device tree\n");

	match = of_match_device(of_ipmi_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	अगर (!of_device_is_available(np))
		वापस -EINVAL;

	ret = of_address_to_resource(np, 0, &resource);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "invalid address from OF\n");
		वापस ret;
	पूर्ण

	regsize = of_get_property(np, "reg-size", &proplen);
	अगर (regsize && proplen != 4) अणु
		dev_warn(&pdev->dev, "invalid regsize from OF\n");
		वापस -EINVAL;
	पूर्ण

	regspacing = of_get_property(np, "reg-spacing", &proplen);
	अगर (regspacing && proplen != 4) अणु
		dev_warn(&pdev->dev, "invalid regspacing from OF\n");
		वापस -EINVAL;
	पूर्ण

	regshअगरt = of_get_property(np, "reg-shift", &proplen);
	अगर (regshअगरt && proplen != 4) अणु
		dev_warn(&pdev->dev, "invalid regshift from OF\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&io, 0, माप(io));
	io.si_type	= (क्रमागत si_type) match->data;
	io.addr_source	= SI_DEVICETREE;
	io.irq_setup	= ipmi_std_irq_setup;

	ipmi_set_addr_data_and_space(&resource, &io);

	io.regsize	= regsize ? be32_to_cpup(regsize) : DEFAULT_REGSIZE;
	io.regspacing	= regspacing ? be32_to_cpup(regspacing) : DEFAULT_REGSPACING;
	io.regshअगरt	= regshअगरt ? be32_to_cpup(regshअगरt) : 0;

	io.irq		= irq_of_parse_and_map(pdev->dev.of_node, 0);
	io.dev		= &pdev->dev;

	dev_dbg(&pdev->dev, "addr 0x%lx regsize %d spacing %d irq %d\n",
		io.addr_data, io.regsize, io.regspacing, io.irq);

	वापस ipmi_si_add_smi(&io);
पूर्ण
#अन्यथा
#घोषणा of_ipmi_match शून्य
अटल पूर्णांक of_ipmi_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक find_slave_address(काष्ठा si_sm_io *io, पूर्णांक slave_addr)
अणु
#अगर_घोषित CONFIG_IPMI_DMI_DECODE
	अगर (!slave_addr)
		slave_addr = ipmi_dmi_get_slave_addr(io->si_type,
						     io->addr_space,
						     io->addr_data);
#पूर्ण_अगर

	वापस slave_addr;
पूर्ण

अटल पूर्णांक acpi_ipmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा si_sm_io io;
	acpi_handle handle;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	काष्ठा resource *res;

	अगर (!si_tryacpi)
		वापस -ENODEV;

	handle = ACPI_HANDLE(dev);
	अगर (!handle)
		वापस -ENODEV;

	स_रखो(&io, 0, माप(io));
	io.addr_source = SI_ACPI;
	dev_info(dev, "probing via ACPI\n");

	io.addr_info.acpi_info.acpi_handle = handle;

	/* _IFT tells us the पूर्णांकerface type: KCS, BT, etc */
	status = acpi_evaluate_पूर्णांकeger(handle, "_IFT", शून्य, &पंचांगp);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "Could not find ACPI IPMI interface type\n");
		वापस -EINVAL;
	पूर्ण

	चयन (पंचांगp) अणु
	हाल 1:
		io.si_type = SI_KCS;
		अवरोध;
	हाल 2:
		io.si_type = SI_SMIC;
		अवरोध;
	हाल 3:
		io.si_type = SI_BT;
		अवरोध;
	हाल 4: /* SSIF, just ignore */
		वापस -ENODEV;
	शेष:
		dev_info(dev, "unknown IPMI type %lld\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण

	io.dev = dev;
	io.regsize = DEFAULT_REGSIZE;
	io.regshअगरt = 0;

	res = ipmi_get_info_from_resources(pdev, &io);
	अगर (!res)
		वापस -EINVAL;

	/* If _GPE exists, use it; otherwise use standard पूर्णांकerrupts */
	status = acpi_evaluate_पूर्णांकeger(handle, "_GPE", शून्य, &पंचांगp);
	अगर (ACPI_SUCCESS(status)) अणु
		io.irq = पंचांगp;
		io.irq_setup = acpi_gpe_irq_setup;
	पूर्ण अन्यथा अणु
		पूर्णांक irq = platक्रमm_get_irq_optional(pdev, 0);

		अगर (irq > 0) अणु
			io.irq = irq;
			io.irq_setup = ipmi_std_irq_setup;
		पूर्ण
	पूर्ण

	io.slave_addr = find_slave_address(&io, io.slave_addr);

	dev_info(dev, "%pR regsize %d spacing %d irq %d\n",
		 res, io.regsize, io.regspacing, io.irq);

	request_module("acpi_ipmi");

	वापस ipmi_si_add_smi(&io);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id acpi_ipmi_match[] = अणु
	अणु "IPI0001", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_ipmi_match);
#अन्यथा
अटल पूर्णांक acpi_ipmi_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ipmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node && of_ipmi_probe(pdev) == 0)
		वापस 0;

	अगर (acpi_ipmi_probe(pdev) == 0)
		वापस 0;

	वापस platक्रमm_ipmi_probe(pdev);
पूर्ण

अटल पूर्णांक ipmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस ipmi_si_हटाओ_by_dev(&pdev->dev);
पूर्ण

अटल पूर्णांक pdev_match_name(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर अक्षर *name = data;

	वापस म_भेद(pdev->name, name) == 0;
पूर्ण

व्योम ipmi_हटाओ_platक्रमm_device_by_name(अक्षर *name)
अणु
	काष्ठा device *dev;

	जबतक ((dev = bus_find_device(&platक्रमm_bus_type, शून्य, name,
				      pdev_match_name))) अणु
		काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

		platक्रमm_device_unरेजिस्टर(pdev);
		put_device(dev);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id si_plat_ids[] = अणु
	अणु "dmi-ipmi-si", 0 पूर्ण,
	अणु "hardcode-ipmi-si", 0 पूर्ण,
	अणु "hotmod-ipmi-si", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा platक्रमm_driver ipmi_platक्रमm_driver = अणु
	.driver = अणु
		.name = SI_DEVICE_NAME,
		.of_match_table = of_ipmi_match,
		.acpi_match_table = ACPI_PTR(acpi_ipmi_match),
	पूर्ण,
	.probe		= ipmi_probe,
	.हटाओ		= ipmi_हटाओ,
	.id_table       = si_plat_ids
पूर्ण;

व्योम ipmi_si_platक्रमm_init(व्योम)
अणु
	पूर्णांक rv = platक्रमm_driver_रेजिस्टर(&ipmi_platक्रमm_driver);
	अगर (rv)
		pr_err("Unable to register driver: %d\n", rv);
	अन्यथा
		platक्रमm_रेजिस्टरed = true;
पूर्ण

व्योम ipmi_si_platक्रमm_shutकरोwn(व्योम)
अणु
	अगर (platक्रमm_रेजिस्टरed)
		platक्रमm_driver_unरेजिस्टर(&ipmi_platक्रमm_driver);
पूर्ण
