<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * System on Chip (SoC) Host
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश "scan.h"
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/bcma/bcma_soc.h>

अटल u8 bcma_host_soc_पढ़ो8(काष्ठा bcma_device *core, u16 offset)
अणु
	वापस पढ़ोb(core->io_addr + offset);
पूर्ण

अटल u16 bcma_host_soc_पढ़ो16(काष्ठा bcma_device *core, u16 offset)
अणु
	वापस पढ़ोw(core->io_addr + offset);
पूर्ण

अटल u32 bcma_host_soc_पढ़ो32(काष्ठा bcma_device *core, u16 offset)
अणु
	वापस पढ़ोl(core->io_addr + offset);
पूर्ण

अटल व्योम bcma_host_soc_ग_लिखो8(काष्ठा bcma_device *core, u16 offset,
				 u8 value)
अणु
	ग_लिखोb(value, core->io_addr + offset);
पूर्ण

अटल व्योम bcma_host_soc_ग_लिखो16(काष्ठा bcma_device *core, u16 offset,
				 u16 value)
अणु
	ग_लिखोw(value, core->io_addr + offset);
पूर्ण

अटल व्योम bcma_host_soc_ग_लिखो32(काष्ठा bcma_device *core, u16 offset,
				 u32 value)
अणु
	ग_लिखोl(value, core->io_addr + offset);
पूर्ण

#अगर_घोषित CONFIG_BCMA_BLOCKIO
अटल व्योम bcma_host_soc_block_पढ़ो(काष्ठा bcma_device *core, व्योम *buffer,
				     माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	व्योम __iomem *addr = core->io_addr + offset;

	चयन (reg_width) अणु
	हाल माप(u8): अणु
		u8 *buf = buffer;

		जबतक (count) अणु
			*buf = __raw_पढ़ोb(addr);
			buf++;
			count--;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u16): अणु
		__le16 *buf = buffer;

		WARN_ON(count & 1);
		जबतक (count) अणु
			*buf = (__क्रमce __le16)__raw_पढ़ोw(addr);
			buf++;
			count -= 2;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u32): अणु
		__le32 *buf = buffer;

		WARN_ON(count & 3);
		जबतक (count) अणु
			*buf = (__क्रमce __le32)__raw_पढ़ोl(addr);
			buf++;
			count -= 4;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम bcma_host_soc_block_ग_लिखो(काष्ठा bcma_device *core,
				      स्थिर व्योम *buffer,
				      माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	व्योम __iomem *addr = core->io_addr + offset;

	चयन (reg_width) अणु
	हाल माप(u8): अणु
		स्थिर u8 *buf = buffer;

		जबतक (count) अणु
			__raw_ग_लिखोb(*buf, addr);
			buf++;
			count--;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u16): अणु
		स्थिर __le16 *buf = buffer;

		WARN_ON(count & 1);
		जबतक (count) अणु
			__raw_ग_लिखोw((__क्रमce u16)(*buf), addr);
			buf++;
			count -= 2;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u32): अणु
		स्थिर __le32 *buf = buffer;

		WARN_ON(count & 3);
		जबतक (count) अणु
			__raw_ग_लिखोl((__क्रमce u32)(*buf), addr);
			buf++;
			count -= 4;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_BLOCKIO */

अटल u32 bcma_host_soc_aपढ़ो32(काष्ठा bcma_device *core, u16 offset)
अणु
	अगर (WARN_ONCE(!core->io_wrap, "Accessed core has no wrapper/agent\n"))
		वापस ~0;
	वापस पढ़ोl(core->io_wrap + offset);
पूर्ण

अटल व्योम bcma_host_soc_aग_लिखो32(काष्ठा bcma_device *core, u16 offset,
				  u32 value)
अणु
	अगर (WARN_ONCE(!core->io_wrap, "Accessed core has no wrapper/agent\n"))
		वापस;
	ग_लिखोl(value, core->io_wrap + offset);
पूर्ण

अटल स्थिर काष्ठा bcma_host_ops bcma_host_soc_ops = अणु
	.पढ़ो8		= bcma_host_soc_पढ़ो8,
	.पढ़ो16		= bcma_host_soc_पढ़ो16,
	.पढ़ो32		= bcma_host_soc_पढ़ो32,
	.ग_लिखो8		= bcma_host_soc_ग_लिखो8,
	.ग_लिखो16	= bcma_host_soc_ग_लिखो16,
	.ग_लिखो32	= bcma_host_soc_ग_लिखो32,
#अगर_घोषित CONFIG_BCMA_BLOCKIO
	.block_पढ़ो	= bcma_host_soc_block_पढ़ो,
	.block_ग_लिखो	= bcma_host_soc_block_ग_लिखो,
#पूर्ण_अगर
	.aपढ़ो32	= bcma_host_soc_aपढ़ो32,
	.aग_लिखो32	= bcma_host_soc_aग_लिखो32,
पूर्ण;

पूर्णांक __init bcma_host_soc_रेजिस्टर(काष्ठा bcma_soc *soc)
अणु
	काष्ठा bcma_bus *bus = &soc->bus;

	/* iomap only first core. We have to पढ़ो some रेजिस्टर on this core
	 * to scan the bus.
	 */
	bus->mmio = ioremap(BCMA_ADDR_BASE, BCMA_CORE_SIZE * 1);
	अगर (!bus->mmio)
		वापस -ENOMEM;

	/* Host specअगरic */
	bus->hosttype = BCMA_HOSTTYPE_SOC;
	bus->ops = &bcma_host_soc_ops;

	/* Initialize काष्ठा, detect chip */
	bcma_init_bus(bus);

	वापस 0;
पूर्ण

पूर्णांक __init bcma_host_soc_init(काष्ठा bcma_soc *soc)
अणु
	काष्ठा bcma_bus *bus = &soc->bus;
	पूर्णांक err;

	/* Scan bus and initialize it */
	err = bcma_bus_early_रेजिस्टर(bus);
	अगर (err)
		iounmap(bus->mmio);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक bcma_host_soc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा bcma_bus *bus;
	पूर्णांक err;

	/* Alloc */
	bus = devm_kzalloc(dev, माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस -ENOMEM;

	bus->dev = dev;

	/* Map MMIO */
	bus->mmio = of_iomap(np, 0);
	अगर (!bus->mmio)
		वापस -ENOMEM;

	/* Host specअगरic */
	bus->hosttype = BCMA_HOSTTYPE_SOC;
	bus->ops = &bcma_host_soc_ops;

	/* Initialize काष्ठा, detect chip */
	bcma_init_bus(bus);

	/* Register */
	err = bcma_bus_रेजिस्टर(bus);
	अगर (err)
		जाओ err_unmap_mmio;

	platक्रमm_set_drvdata(pdev, bus);

	वापस err;

err_unmap_mmio:
	iounmap(bus->mmio);
	वापस err;
पूर्ण

अटल पूर्णांक bcma_host_soc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcma_bus *bus = platक्रमm_get_drvdata(pdev);

	bcma_bus_unरेजिस्टर(bus);
	iounmap(bus->mmio);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcma_host_soc_of_match[] = अणु
	अणु .compatible = "brcm,bus-axi", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcma_host_soc_of_match);

अटल काष्ठा platक्रमm_driver bcma_host_soc_driver = अणु
	.driver = अणु
		.name = "bcma-host-soc",
		.of_match_table = bcma_host_soc_of_match,
	पूर्ण,
	.probe		= bcma_host_soc_probe,
	.हटाओ		= bcma_host_soc_हटाओ,
पूर्ण;

पूर्णांक __init bcma_host_soc_रेजिस्टर_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&bcma_host_soc_driver);
पूर्ण

व्योम __निकास bcma_host_soc_unरेजिस्टर_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&bcma_host_soc_driver);
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */
