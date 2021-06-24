<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  Bus असलtraction layer

  Copyright (c) 2011 Rafaध Miधecki <zajec5@gmail.com>


*/

#अगर_घोषित CONFIG_BCM47XX_BCMA
#समावेश <यंत्र/mach-bcm47xx/bcm47xx.h>
#पूर्ण_अगर

#समावेश "b43.h"
#समावेश "bus.h"

/* BCMA */
#अगर_घोषित CONFIG_B43_BCMA
अटल पूर्णांक b43_bus_bcma_bus_may_घातerकरोwn(काष्ठा b43_bus_dev *dev)
अणु
	वापस 0; /* bcma_bus_may_घातerकरोwn(dev->bdev->bus); */
पूर्ण
अटल पूर्णांक b43_bus_bcma_bus_घातerup(काष्ठा b43_bus_dev *dev,
					  bool dynamic_pctl)
अणु
	वापस 0; /* bcma_bus_घातerup(dev->sdev->bus, dynamic_pctl); */
पूर्ण
अटल पूर्णांक b43_bus_bcma_device_is_enabled(काष्ठा b43_bus_dev *dev)
अणु
	वापस bcma_core_is_enabled(dev->bdev);
पूर्ण
अटल व्योम b43_bus_bcma_device_enable(काष्ठा b43_bus_dev *dev,
					     u32 core_specअगरic_flags)
अणु
	bcma_core_enable(dev->bdev, core_specअगरic_flags);
पूर्ण
अटल व्योम b43_bus_bcma_device_disable(काष्ठा b43_bus_dev *dev,
					      u32 core_specअगरic_flags)
अणु
	bcma_core_disable(dev->bdev, core_specअगरic_flags);
पूर्ण
अटल u16 b43_bus_bcma_पढ़ो16(काष्ठा b43_bus_dev *dev, u16 offset)
अणु
	वापस bcma_पढ़ो16(dev->bdev, offset);
पूर्ण
अटल u32 b43_bus_bcma_पढ़ो32(काष्ठा b43_bus_dev *dev, u16 offset)
अणु
	वापस bcma_पढ़ो32(dev->bdev, offset);
पूर्ण
अटल
व्योम b43_bus_bcma_ग_लिखो16(काष्ठा b43_bus_dev *dev, u16 offset, u16 value)
अणु
	bcma_ग_लिखो16(dev->bdev, offset, value);
पूर्ण
अटल
व्योम b43_bus_bcma_ग_लिखो32(काष्ठा b43_bus_dev *dev, u16 offset, u32 value)
अणु
	bcma_ग_लिखो32(dev->bdev, offset, value);
पूर्ण
अटल
व्योम b43_bus_bcma_block_पढ़ो(काष्ठा b43_bus_dev *dev, व्योम *buffer,
			     माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	bcma_block_पढ़ो(dev->bdev, buffer, count, offset, reg_width);
पूर्ण
अटल
व्योम b43_bus_bcma_block_ग_लिखो(काष्ठा b43_bus_dev *dev, स्थिर व्योम *buffer,
			      माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	bcma_block_ग_लिखो(dev->bdev, buffer, count, offset, reg_width);
पूर्ण

काष्ठा b43_bus_dev *b43_bus_dev_bcma_init(काष्ठा bcma_device *core)
अणु
	काष्ठा b43_bus_dev *dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	dev->bus_type = B43_BUS_BCMA;
	dev->bdev = core;

	dev->bus_may_घातerकरोwn = b43_bus_bcma_bus_may_घातerकरोwn;
	dev->bus_घातerup = b43_bus_bcma_bus_घातerup;
	dev->device_is_enabled = b43_bus_bcma_device_is_enabled;
	dev->device_enable = b43_bus_bcma_device_enable;
	dev->device_disable = b43_bus_bcma_device_disable;

	dev->पढ़ो16 = b43_bus_bcma_पढ़ो16;
	dev->पढ़ो32 = b43_bus_bcma_पढ़ो32;
	dev->ग_लिखो16 = b43_bus_bcma_ग_लिखो16;
	dev->ग_लिखो32 = b43_bus_bcma_ग_लिखो32;
	dev->block_पढ़ो = b43_bus_bcma_block_पढ़ो;
	dev->block_ग_लिखो = b43_bus_bcma_block_ग_लिखो;
#अगर_घोषित CONFIG_BCM47XX_BCMA
	अगर (b43_bus_host_is_pci(dev) &&
	    bcm47xx_bus_type == BCM47XX_BUS_TYPE_BCMA &&
	    bcm47xx_bus.bcma.bus.chipinfo.id == BCMA_CHIP_ID_BCM4716)
		dev->flush_ग_लिखोs = true;
#पूर्ण_अगर

	dev->dev = &core->dev;
	dev->dma_dev = core->dma_dev;
	dev->irq = core->irq;

	dev->board_venकरोr = core->bus->boardinfo.venकरोr;
	dev->board_type = core->bus->boardinfo.type;
	dev->board_rev = core->bus->sprom.board_rev;

	dev->chip_id = core->bus->chipinfo.id;
	dev->chip_rev = core->bus->chipinfo.rev;
	dev->chip_pkg = core->bus->chipinfo.pkg;

	dev->bus_sprom = &core->bus->sprom;

	dev->core_id = core->id.id;
	dev->core_rev = core->id.rev;

	वापस dev;
पूर्ण
#पूर्ण_अगर /* CONFIG_B43_BCMA */

/* SSB */
#अगर_घोषित CONFIG_B43_SSB
अटल पूर्णांक b43_bus_ssb_bus_may_घातerकरोwn(काष्ठा b43_bus_dev *dev)
अणु
	वापस ssb_bus_may_घातerकरोwn(dev->sdev->bus);
पूर्ण
अटल पूर्णांक b43_bus_ssb_bus_घातerup(काष्ठा b43_bus_dev *dev,
					  bool dynamic_pctl)
अणु
	वापस ssb_bus_घातerup(dev->sdev->bus, dynamic_pctl);
पूर्ण
अटल पूर्णांक b43_bus_ssb_device_is_enabled(काष्ठा b43_bus_dev *dev)
अणु
	वापस ssb_device_is_enabled(dev->sdev);
पूर्ण
अटल व्योम b43_bus_ssb_device_enable(काष्ठा b43_bus_dev *dev,
					     u32 core_specअगरic_flags)
अणु
	ssb_device_enable(dev->sdev, core_specअगरic_flags);
पूर्ण
अटल व्योम b43_bus_ssb_device_disable(काष्ठा b43_bus_dev *dev,
					      u32 core_specअगरic_flags)
अणु
	ssb_device_disable(dev->sdev, core_specअगरic_flags);
पूर्ण

अटल u16 b43_bus_ssb_पढ़ो16(काष्ठा b43_bus_dev *dev, u16 offset)
अणु
	वापस ssb_पढ़ो16(dev->sdev, offset);
पूर्ण
अटल u32 b43_bus_ssb_पढ़ो32(काष्ठा b43_bus_dev *dev, u16 offset)
अणु
	वापस ssb_पढ़ो32(dev->sdev, offset);
पूर्ण
अटल व्योम b43_bus_ssb_ग_लिखो16(काष्ठा b43_bus_dev *dev, u16 offset, u16 value)
अणु
	ssb_ग_लिखो16(dev->sdev, offset, value);
पूर्ण
अटल व्योम b43_bus_ssb_ग_लिखो32(काष्ठा b43_bus_dev *dev, u16 offset, u32 value)
अणु
	ssb_ग_लिखो32(dev->sdev, offset, value);
पूर्ण
अटल व्योम b43_bus_ssb_block_पढ़ो(काष्ठा b43_bus_dev *dev, व्योम *buffer,
				   माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	ssb_block_पढ़ो(dev->sdev, buffer, count, offset, reg_width);
पूर्ण
अटल
व्योम b43_bus_ssb_block_ग_लिखो(काष्ठा b43_bus_dev *dev, स्थिर व्योम *buffer,
			     माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	ssb_block_ग_लिखो(dev->sdev, buffer, count, offset, reg_width);
पूर्ण

काष्ठा b43_bus_dev *b43_bus_dev_ssb_init(काष्ठा ssb_device *sdev)
अणु
	काष्ठा b43_bus_dev *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	dev->bus_type = B43_BUS_SSB;
	dev->sdev = sdev;

	dev->bus_may_घातerकरोwn = b43_bus_ssb_bus_may_घातerकरोwn;
	dev->bus_घातerup = b43_bus_ssb_bus_घातerup;
	dev->device_is_enabled = b43_bus_ssb_device_is_enabled;
	dev->device_enable = b43_bus_ssb_device_enable;
	dev->device_disable = b43_bus_ssb_device_disable;

	dev->पढ़ो16 = b43_bus_ssb_पढ़ो16;
	dev->पढ़ो32 = b43_bus_ssb_पढ़ो32;
	dev->ग_लिखो16 = b43_bus_ssb_ग_लिखो16;
	dev->ग_लिखो32 = b43_bus_ssb_ग_लिखो32;
	dev->block_पढ़ो = b43_bus_ssb_block_पढ़ो;
	dev->block_ग_लिखो = b43_bus_ssb_block_ग_लिखो;

	dev->dev = sdev->dev;
	dev->dma_dev = sdev->dma_dev;
	dev->irq = sdev->irq;

	dev->board_venकरोr = sdev->bus->boardinfo.venकरोr;
	dev->board_type = sdev->bus->boardinfo.type;
	dev->board_rev = sdev->bus->sprom.board_rev;

	dev->chip_id = sdev->bus->chip_id;
	dev->chip_rev = sdev->bus->chip_rev;
	dev->chip_pkg = sdev->bus->chip_package;

	dev->bus_sprom = &sdev->bus->sprom;

	dev->core_id = sdev->id.coreid;
	dev->core_rev = sdev->id.revision;

	वापस dev;
पूर्ण
#पूर्ण_अगर /* CONFIG_B43_SSB */

व्योम *b43_bus_get_wldev(काष्ठा b43_bus_dev *dev)
अणु
	चयन (dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		वापस bcma_get_drvdata(dev->bdev);
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		वापस ssb_get_drvdata(dev->sdev);
#पूर्ण_अगर
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम b43_bus_set_wldev(काष्ठा b43_bus_dev *dev, व्योम *wldev)
अणु
	चयन (dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		bcma_set_drvdata(dev->bdev, wldev);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		ssb_set_drvdata(dev->sdev, wldev);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण
