<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Broadcom MIPS core driver
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>

#समावेश <linux/mtd/physmap.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/समय.स>
#अगर_घोषित CONFIG_BCM47XX
#समावेश <linux/bcm47xx_nvram.h>
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर part_probes[] = अणु "bcm47xxpart", शून्य पूर्ण;

अटल काष्ठा physmap_flash_data ssb_pflash_data = अणु
	.part_probe_types	= part_probes,
पूर्ण;

अटल काष्ठा resource ssb_pflash_resource = अणु
	.name	= "ssb_pflash",
	.flags  = IORESOURCE_MEM,
पूर्ण;

काष्ठा platक्रमm_device ssb_pflash_dev = अणु
	.name		= "physmap-flash",
	.dev		= अणु
		.platक्रमm_data  = &ssb_pflash_data,
	पूर्ण,
	.resource	= &ssb_pflash_resource,
	.num_resources	= 1,
पूर्ण;

अटल अंतरभूत u32 mips_पढ़ो32(काष्ठा ssb_mipscore *mcore,
			      u16 offset)
अणु
	वापस ssb_पढ़ो32(mcore->dev, offset);
पूर्ण

अटल अंतरभूत व्योम mips_ग_लिखो32(काष्ठा ssb_mipscore *mcore,
				u16 offset,
				u32 value)
अणु
	ssb_ग_लिखो32(mcore->dev, offset, value);
पूर्ण

अटल स्थिर u32 ipsflag_irq_mask[] = अणु
	0,
	SSB_IPSFLAG_IRQ1,
	SSB_IPSFLAG_IRQ2,
	SSB_IPSFLAG_IRQ3,
	SSB_IPSFLAG_IRQ4,
पूर्ण;

अटल स्थिर u32 ipsflag_irq_shअगरt[] = अणु
	0,
	SSB_IPSFLAG_IRQ1_SHIFT,
	SSB_IPSFLAG_IRQ2_SHIFT,
	SSB_IPSFLAG_IRQ3_SHIFT,
	SSB_IPSFLAG_IRQ4_SHIFT,
पूर्ण;

अटल अंतरभूत u32 ssb_irqflag(काष्ठा ssb_device *dev)
अणु
	u32 tpsflag = ssb_पढ़ो32(dev, SSB_TPSFLAG);
	अगर (tpsflag)
		वापस ssb_पढ़ो32(dev, SSB_TPSFLAG) & SSB_TPSFLAG_BPFLAG;
	अन्यथा
		/* not irq supported */
		वापस 0x3f;
पूर्ण

अटल काष्ठा ssb_device *find_device(काष्ठा ssb_device *rdev, पूर्णांक irqflag)
अणु
	काष्ठा ssb_bus *bus = rdev->bus;
	पूर्णांक i;
	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		काष्ठा ssb_device *dev;
		dev = &(bus->devices[i]);
		अगर (ssb_irqflag(dev) == irqflag)
			वापस dev;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Get the MIPS IRQ assignment क्रम a specअगरied device.
 * If unasचिन्हित, 0 is वापसed.
 * If disabled, 5 is वापसed.
 * If not supported, 6 is वापसed.
 */
अचिन्हित पूर्णांक ssb_mips_irq(काष्ठा ssb_device *dev)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	काष्ठा ssb_device *mdev = bus->mipscore.dev;
	u32 irqflag;
	u32 ipsflag;
	u32 पंचांगp;
	अचिन्हित पूर्णांक irq;

	irqflag = ssb_irqflag(dev);
	अगर (irqflag == 0x3f)
		वापस 6;
	ipsflag = ssb_पढ़ो32(bus->mipscore.dev, SSB_IPSFLAG);
	क्रम (irq = 1; irq <= 4; irq++) अणु
		पंचांगp = ((ipsflag & ipsflag_irq_mask[irq]) >> ipsflag_irq_shअगरt[irq]);
		अगर (पंचांगp == irqflag)
			अवरोध;
	पूर्ण
	अगर (irq	== 5) अणु
		अगर ((1 << irqflag) & ssb_पढ़ो32(mdev, SSB_INTVEC))
			irq = 0;
	पूर्ण

	वापस irq;
पूर्ण

अटल व्योम clear_irq(काष्ठा ssb_bus *bus, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा ssb_device *dev = bus->mipscore.dev;

	/* Clear the IRQ in the MIPScore backplane रेजिस्टरs */
	अगर (irq == 0) अणु
		ssb_ग_लिखो32(dev, SSB_INTVEC, 0);
	पूर्ण अन्यथा अणु
		ssb_ग_लिखो32(dev, SSB_IPSFLAG,
			    ssb_पढ़ो32(dev, SSB_IPSFLAG) |
			    ipsflag_irq_mask[irq]);
	पूर्ण
पूर्ण

अटल व्योम set_irq(काष्ठा ssb_device *dev, अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक oldirq = ssb_mips_irq(dev);
	काष्ठा ssb_bus *bus = dev->bus;
	काष्ठा ssb_device *mdev = bus->mipscore.dev;
	u32 irqflag = ssb_irqflag(dev);

	BUG_ON(oldirq == 6);

	dev->irq = irq + 2;

	/* clear the old irq */
	अगर (oldirq == 0)
		ssb_ग_लिखो32(mdev, SSB_INTVEC, (~(1 << irqflag) & ssb_पढ़ो32(mdev, SSB_INTVEC)));
	अन्यथा अगर (oldirq != 5)
		clear_irq(bus, oldirq);

	/* assign the new one */
	अगर (irq == 0) अणु
		ssb_ग_लिखो32(mdev, SSB_INTVEC, ((1 << irqflag) | ssb_पढ़ो32(mdev, SSB_INTVEC)));
	पूर्ण अन्यथा अणु
		u32 ipsflag = ssb_पढ़ो32(mdev, SSB_IPSFLAG);
		अगर ((ipsflag & ipsflag_irq_mask[irq]) != ipsflag_irq_mask[irq]) अणु
			u32 oldipsflag = (ipsflag & ipsflag_irq_mask[irq]) >> ipsflag_irq_shअगरt[irq];
			काष्ठा ssb_device *olddev = find_device(dev, oldipsflag);
			अगर (olddev)
				set_irq(olddev, 0);
		पूर्ण
		irqflag <<= ipsflag_irq_shअगरt[irq];
		irqflag |= (ipsflag & ~ipsflag_irq_mask[irq]);
		ssb_ग_लिखो32(mdev, SSB_IPSFLAG, irqflag);
	पूर्ण
	dev_dbg(dev->dev, "set_irq: core 0x%04x, irq %d => %d\n",
		dev->id.coreid, oldirq+2, irq+2);
पूर्ण

अटल व्योम prपूर्णांक_irq(काष्ठा ssb_device *dev, अचिन्हित पूर्णांक irq)
अणु
	अटल स्थिर अक्षर *irq_name[] = अणु"2(S)", "3", "4", "5", "6", "D", "I"पूर्ण;
	dev_dbg(dev->dev,
		"core 0x%04x, irq : %s%s %s%s %s%s %s%s %s%s %s%s %s%s\n",
		dev->id.coreid,
		irq_name[0], irq == 0 ? "*" : " ",
		irq_name[1], irq == 1 ? "*" : " ",
		irq_name[2], irq == 2 ? "*" : " ",
		irq_name[3], irq == 3 ? "*" : " ",
		irq_name[4], irq == 4 ? "*" : " ",
		irq_name[5], irq == 5 ? "*" : " ",
		irq_name[6], irq == 6 ? "*" : " ");
पूर्ण

अटल व्योम dump_irq(काष्ठा ssb_bus *bus)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		काष्ठा ssb_device *dev;
		dev = &(bus->devices[i]);
		prपूर्णांक_irq(dev, ssb_mips_irq(dev));
	पूर्ण
पूर्ण

अटल व्योम ssb_mips_serial_init(काष्ठा ssb_mipscore *mcore)
अणु
	काष्ठा ssb_bus *bus = mcore->dev->bus;

	अगर (ssb_extअगर_available(&bus->extअगर))
		mcore->nr_serial_ports = ssb_extअगर_serial_init(&bus->extअगर, mcore->serial_ports);
	अन्यथा अगर (ssb_chipco_available(&bus->chipco))
		mcore->nr_serial_ports = ssb_chipco_serial_init(&bus->chipco, mcore->serial_ports);
	अन्यथा
		mcore->nr_serial_ports = 0;
पूर्ण

अटल व्योम ssb_mips_flash_detect(काष्ठा ssb_mipscore *mcore)
अणु
	काष्ठा ssb_bus *bus = mcore->dev->bus;
	काष्ठा ssb_sflash *sflash = &mcore->sflash;
	काष्ठा ssb_pflash *pflash = &mcore->pflash;

	/* When there is no chipcommon on the bus there is 4MB flash */
	अगर (!ssb_chipco_available(&bus->chipco)) अणु
		pflash->present = true;
		pflash->buswidth = 2;
		pflash->winकरोw = SSB_FLASH1;
		pflash->winकरोw_size = SSB_FLASH1_SZ;
		जाओ ssb_pflash;
	पूर्ण

	/* There is ChipCommon, so use it to पढ़ो info about flash */
	चयन (bus->chipco.capabilities & SSB_CHIPCO_CAP_FLASHT) अणु
	हाल SSB_CHIPCO_FLASHT_STSER:
	हाल SSB_CHIPCO_FLASHT_ATSER:
		dev_dbg(mcore->dev->dev, "Found serial flash\n");
		ssb_sflash_init(&bus->chipco);
		अवरोध;
	हाल SSB_CHIPCO_FLASHT_PARA:
		dev_dbg(mcore->dev->dev, "Found parallel flash\n");
		pflash->present = true;
		pflash->winकरोw = SSB_FLASH2;
		pflash->winकरोw_size = SSB_FLASH2_SZ;
		अगर ((ssb_पढ़ो32(bus->chipco.dev, SSB_CHIPCO_FLASH_CFG)
		               & SSB_CHIPCO_CFG_DS16) == 0)
			pflash->buswidth = 1;
		अन्यथा
			pflash->buswidth = 2;
		अवरोध;
	पूर्ण

ssb_pflash:
	अगर (sflash->present) अणु
#अगर_घोषित CONFIG_BCM47XX
		bcm47xx_nvram_init_from_mem(sflash->winकरोw, sflash->size);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (pflash->present) अणु
#अगर_घोषित CONFIG_BCM47XX
		bcm47xx_nvram_init_from_mem(pflash->winकरोw, pflash->winकरोw_size);
#पूर्ण_अगर

		ssb_pflash_data.width = pflash->buswidth;
		ssb_pflash_resource.start = pflash->winकरोw;
		ssb_pflash_resource.end = pflash->winकरोw + pflash->winकरोw_size;
	पूर्ण
पूर्ण

u32 ssb_cpu_घड़ी(काष्ठा ssb_mipscore *mcore)
अणु
	काष्ठा ssb_bus *bus = mcore->dev->bus;
	u32 pll_type, n, m, rate = 0;

	अगर (bus->chipco.capabilities & SSB_CHIPCO_CAP_PMU)
		वापस ssb_pmu_get_cpu_घड़ी(&bus->chipco);

	अगर (ssb_extअगर_available(&bus->extअगर)) अणु
		ssb_extअगर_get_घड़ीcontrol(&bus->extअगर, &pll_type, &n, &m);
	पूर्ण अन्यथा अगर (ssb_chipco_available(&bus->chipco)) अणु
		ssb_chipco_get_घड़ीcpu(&bus->chipco, &pll_type, &n, &m);
	पूर्ण अन्यथा
		वापस 0;

	अगर ((pll_type == SSB_PLLTYPE_5) || (bus->chip_id == 0x5365)) अणु
		rate = 200000000;
	पूर्ण अन्यथा अणु
		rate = ssb_calc_घड़ी_rate(pll_type, n, m);
	पूर्ण

	अगर (pll_type == SSB_PLLTYPE_6) अणु
		rate *= 2;
	पूर्ण

	वापस rate;
पूर्ण

व्योम ssb_mipscore_init(काष्ठा ssb_mipscore *mcore)
अणु
	काष्ठा ssb_bus *bus;
	काष्ठा ssb_device *dev;
	अचिन्हित दीर्घ hz, ns;
	अचिन्हित पूर्णांक irq, i;

	अगर (!mcore->dev)
		वापस; /* We करोn't have a MIPS core */

	dev_dbg(mcore->dev->dev, "Initializing MIPS core...\n");

	bus = mcore->dev->bus;
	hz = ssb_घड़ीspeed(bus);
	अगर (!hz)
		hz = 100000000;
	ns = 1000000000 / hz;

	अगर (ssb_extअगर_available(&bus->extअगर))
		ssb_extअगर_timing_init(&bus->extअगर, ns);
	अन्यथा अगर (ssb_chipco_available(&bus->chipco))
		ssb_chipco_timing_init(&bus->chipco, ns);

	/* Assign IRQs to all cores on the bus, start with irq line 2, because serial usually takes 1 */
	क्रम (irq = 2, i = 0; i < bus->nr_devices; i++) अणु
		पूर्णांक mips_irq;
		dev = &(bus->devices[i]);
		mips_irq = ssb_mips_irq(dev);
		अगर (mips_irq > 4)
			dev->irq = 0;
		अन्यथा
			dev->irq = mips_irq + 2;
		अगर (dev->irq > 5)
			जारी;
		चयन (dev->id.coreid) अणु
		हाल SSB_DEV_USB11_HOST:
			/* shouldn't need a separate irq line क्रम non-4710, most of them have a proper
			 * बाह्यal usb controller on the pci */
			अगर ((bus->chip_id == 0x4710) && (irq <= 4)) अणु
				set_irq(dev, irq++);
			पूर्ण
			अवरोध;
		हाल SSB_DEV_PCI:
		हाल SSB_DEV_ETHERNET:
		हाल SSB_DEV_ETHERNET_GBIT:
		हाल SSB_DEV_80211:
		हाल SSB_DEV_USB20_HOST:
			/* These devices get their own IRQ line अगर available, the rest goes on IRQ0 */
			अगर (irq <= 4) अणु
				set_irq(dev, irq++);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल SSB_DEV_EXTIF:
			set_irq(dev, 0);
			अवरोध;
		पूर्ण
	पूर्ण
	dev_dbg(mcore->dev->dev, "after irq reconfiguration\n");
	dump_irq(bus);

	ssb_mips_serial_init(mcore);
	ssb_mips_flash_detect(mcore);
पूर्ण
