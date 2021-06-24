<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * Broadcom MIPS32 74K core driver
 *
 * Copyright 2009, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <mb@bu3sch.de>
 * Copyright 2010, Bernhard Loos <bernhardloos@googlemail.com>
 * Copyright 2011, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"

#समावेश <linux/bcma/bcma.h>

#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/समय.स>
#अगर_घोषित CONFIG_BCM47XX
#समावेश <linux/bcm47xx_nvram.h>
#पूर्ण_अगर

क्रमागत bcma_boot_dev अणु
	BCMA_BOOT_DEV_UNK = 0,
	BCMA_BOOT_DEV_ROM,
	BCMA_BOOT_DEV_PARALLEL,
	BCMA_BOOT_DEV_SERIAL,
	BCMA_BOOT_DEV_न_अंकD,
पूर्ण;

/* The 47162a0 hangs when पढ़ोing MIPS DMP रेजिस्टरs रेजिस्टरs */
अटल अंतरभूत bool bcma_core_mips_bcm47162a0_quirk(काष्ठा bcma_device *dev)
अणु
	वापस dev->bus->chipinfo.id == BCMA_CHIP_ID_BCM47162 &&
	       dev->bus->chipinfo.rev == 0 && dev->id.id == BCMA_CORE_MIPS_74K;
पूर्ण

/* The 5357b0 hangs when पढ़ोing USB20H DMP रेजिस्टरs */
अटल अंतरभूत bool bcma_core_mips_bcm5357b0_quirk(काष्ठा bcma_device *dev)
अणु
	वापस (dev->bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
		dev->bus->chipinfo.id == BCMA_CHIP_ID_BCM4749) &&
	       dev->bus->chipinfo.pkg == 11 &&
	       dev->id.id == BCMA_CORE_USB20_HOST;
पूर्ण

अटल अंतरभूत u32 mips_पढ़ो32(काष्ठा bcma_drv_mips *mcore,
			      u16 offset)
अणु
	वापस bcma_पढ़ो32(mcore->core, offset);
पूर्ण

अटल u32 bcma_core_mips_irqflag(काष्ठा bcma_device *dev)
अणु
	u32 flag;

	अगर (bcma_core_mips_bcm47162a0_quirk(dev))
		वापस dev->core_index;
	अगर (bcma_core_mips_bcm5357b0_quirk(dev))
		वापस dev->core_index;
	flag = bcma_aपढ़ो32(dev, BCMA_MIPS_OOBSELOUTA30);

	अगर (flag)
		वापस flag & 0x1F;
	अन्यथा
		वापस 0x3f;
पूर्ण

/* Get the MIPS IRQ assignment क्रम a specअगरied device.
 * If unasचिन्हित, 0 is वापसed.
 * If disabled, 5 is वापसed.
 * If not supported, 6 is वापसed.
 */
अचिन्हित पूर्णांक bcma_core_mips_irq(काष्ठा bcma_device *dev)
अणु
	काष्ठा bcma_device *mdev = dev->bus->drv_mips.core;
	u32 irqflag;
	अचिन्हित पूर्णांक irq;

	irqflag = bcma_core_mips_irqflag(dev);
	अगर (irqflag == 0x3f)
		वापस 6;

	क्रम (irq = 0; irq <= 4; irq++)
		अगर (bcma_पढ़ो32(mdev, BCMA_MIPS_MIPS74K_INTMASK(irq)) &
		    (1 << irqflag))
			वापस irq;

	वापस 5;
पूर्ण

अटल व्योम bcma_core_mips_set_irq(काष्ठा bcma_device *dev, अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक oldirq = bcma_core_mips_irq(dev);
	काष्ठा bcma_bus *bus = dev->bus;
	काष्ठा bcma_device *mdev = bus->drv_mips.core;
	u32 irqflag;

	irqflag = bcma_core_mips_irqflag(dev);
	BUG_ON(oldirq == 6);

	dev->irq = irq + 2;

	/* clear the old irq */
	अगर (oldirq == 0)
		bcma_ग_लिखो32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0),
			    bcma_पढ़ो32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0)) &
			    ~(1 << irqflag));
	अन्यथा अगर (oldirq != 5)
		bcma_ग_लिखो32(mdev, BCMA_MIPS_MIPS74K_INTMASK(oldirq), 0);

	/* assign the new one */
	अगर (irq == 0) अणु
		bcma_ग_लिखो32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0),
			    bcma_पढ़ो32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0)) |
			    (1 << irqflag));
	पूर्ण अन्यथा अणु
		u32 irqiniपंचांगask = bcma_पढ़ो32(mdev,
					      BCMA_MIPS_MIPS74K_INTMASK(irq));
		अगर (irqiniपंचांगask) अणु
			काष्ठा bcma_device *core;

			/* backplane irq line is in use, find out who uses
			 * it and set user to irq 0
			 */
			list_क्रम_each_entry(core, &bus->cores, list) अणु
				अगर ((1 << bcma_core_mips_irqflag(core)) ==
				    irqiniपंचांगask) अणु
					bcma_core_mips_set_irq(core, 0);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		bcma_ग_लिखो32(mdev, BCMA_MIPS_MIPS74K_INTMASK(irq),
			     1 << irqflag);
	पूर्ण

	bcma_debug(bus, "set_irq: core 0x%04x, irq %d => %d\n",
		   dev->id.id, oldirq <= 4 ? oldirq + 2 : 0, irq + 2);
पूर्ण

अटल व्योम bcma_core_mips_set_irq_name(काष्ठा bcma_bus *bus, अचिन्हित पूर्णांक irq,
					u16 coreid, u8 unit)
अणु
	काष्ठा bcma_device *core;

	core = bcma_find_core_unit(bus, coreid, unit);
	अगर (!core) अणु
		bcma_warn(bus,
			  "Can not find core (id: 0x%x, unit %i) for IRQ configuration.\n",
			  coreid, unit);
		वापस;
	पूर्ण

	bcma_core_mips_set_irq(core, irq);
पूर्ण

अटल व्योम bcma_core_mips_prपूर्णांक_irq(काष्ठा bcma_device *dev, अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक i;
	अटल स्थिर अक्षर *irq_name[] = अणु"2(S)", "3", "4", "5", "6", "D", "I"पूर्ण;
	अक्षर पूर्णांकerrupts[25];
	अक्षर *पूर्णांकs = पूर्णांकerrupts;

	क्रम (i = 0; i < ARRAY_SIZE(irq_name); i++)
		पूर्णांकs += प्र_लिखो(पूर्णांकs, " %s%c",
				irq_name[i], i == irq ? '*' : ' ');

	bcma_debug(dev->bus, "core 0x%04x, irq:%s\n", dev->id.id, पूर्णांकerrupts);
पूर्ण

अटल व्योम bcma_core_mips_dump_irq(काष्ठा bcma_bus *bus)
अणु
	काष्ठा bcma_device *core;

	list_क्रम_each_entry(core, &bus->cores, list) अणु
		bcma_core_mips_prपूर्णांक_irq(core, bcma_core_mips_irq(core));
	पूर्ण
पूर्ण

u32 bcma_cpu_घड़ी(काष्ठा bcma_drv_mips *mcore)
अणु
	काष्ठा bcma_bus *bus = mcore->core->bus;

	अगर (bus->drv_cc.capabilities & BCMA_CC_CAP_PMU)
		वापस bcma_pmu_get_cpu_घड़ी(&bus->drv_cc);

	bcma_err(bus, "No PMU available, need this to get the cpu clock\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bcma_cpu_घड़ी);

अटल क्रमागत bcma_boot_dev bcma_boot_dev(काष्ठा bcma_bus *bus)
अणु
	काष्ठा bcma_drv_cc *cc = &bus->drv_cc;
	u8 cc_rev = cc->core->id.rev;

	अगर (cc_rev == 42) अणु
		काष्ठा bcma_device *core;

		core = bcma_find_core(bus, BCMA_CORE_NS_ROM);
		अगर (core) अणु
			चयन (bcma_aपढ़ो32(core, BCMA_IOST) &
				BCMA_NS_ROM_IOST_BOOT_DEV_MASK) अणु
			हाल BCMA_NS_ROM_IOST_BOOT_DEV_NOR:
				वापस BCMA_BOOT_DEV_SERIAL;
			हाल BCMA_NS_ROM_IOST_BOOT_DEV_न_अंकD:
				वापस BCMA_BOOT_DEV_न_अंकD;
			हाल BCMA_NS_ROM_IOST_BOOT_DEV_ROM:
			शेष:
				वापस BCMA_BOOT_DEV_ROM;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cc_rev == 38) अणु
			अगर (cc->status & BCMA_CC_CHIPST_5357_न_अंकD_BOOT)
				वापस BCMA_BOOT_DEV_न_अंकD;
			अन्यथा अगर (cc->status & BIT(5))
				वापस BCMA_BOOT_DEV_ROM;
		पूर्ण

		अगर ((cc->capabilities & BCMA_CC_CAP_FLASHT) ==
		    BCMA_CC_FLASHT_PARA)
			वापस BCMA_BOOT_DEV_PARALLEL;
		अन्यथा
			वापस BCMA_BOOT_DEV_SERIAL;
	पूर्ण

	वापस BCMA_BOOT_DEV_SERIAL;
पूर्ण

अटल व्योम bcma_core_mips_nvram_init(काष्ठा bcma_drv_mips *mcore)
अणु
	काष्ठा bcma_bus *bus = mcore->core->bus;
	क्रमागत bcma_boot_dev boot_dev;

	/* Determine flash type this SoC boots from */
	boot_dev = bcma_boot_dev(bus);
	चयन (boot_dev) अणु
	हाल BCMA_BOOT_DEV_PARALLEL:
	हाल BCMA_BOOT_DEV_SERIAL:
#अगर_घोषित CONFIG_BCM47XX
		bcm47xx_nvram_init_from_mem(BCMA_SOC_FLASH2,
					    BCMA_SOC_FLASH2_SZ);
#पूर्ण_अगर
		अवरोध;
	हाल BCMA_BOOT_DEV_न_अंकD:
#अगर_घोषित CONFIG_BCM47XX
		bcm47xx_nvram_init_from_mem(BCMA_SOC_FLASH1,
					    BCMA_SOC_FLASH1_SZ);
#पूर्ण_अगर
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम bcma_core_mips_early_init(काष्ठा bcma_drv_mips *mcore)
अणु
	काष्ठा bcma_bus *bus = mcore->core->bus;

	अगर (mcore->early_setup_करोne)
		वापस;

	bcma_chipco_serial_init(&bus->drv_cc);
	bcma_core_mips_nvram_init(mcore);

	mcore->early_setup_करोne = true;
पूर्ण

अटल व्योम bcma_fix_i2s_irqflag(काष्ठा bcma_bus *bus)
अणु
	काष्ठा bcma_device *cpu, *pcie, *i2s;

	/* Fixup the पूर्णांकerrupts in 4716/4748 क्रम i2s core (2010 Broadcom SDK)
	 * (IRQ flags > 7 are ignored when setting the पूर्णांकerrupt masks)
	 */
	अगर (bus->chipinfo.id != BCMA_CHIP_ID_BCM4716 &&
	    bus->chipinfo.id != BCMA_CHIP_ID_BCM4748)
		वापस;

	cpu = bcma_find_core(bus, BCMA_CORE_MIPS_74K);
	pcie = bcma_find_core(bus, BCMA_CORE_PCIE);
	i2s = bcma_find_core(bus, BCMA_CORE_I2S);
	अगर (cpu && pcie && i2s &&
	    bcma_aपढ़ो32(cpu, BCMA_MIPS_OOBSELINA74) == 0x08060504 &&
	    bcma_aपढ़ो32(pcie, BCMA_MIPS_OOBSELINA74) == 0x08060504 &&
	    bcma_aपढ़ो32(i2s, BCMA_MIPS_OOBSELOUTA30) == 0x88) अणु
		bcma_aग_लिखो32(cpu, BCMA_MIPS_OOBSELINA74, 0x07060504);
		bcma_aग_लिखो32(pcie, BCMA_MIPS_OOBSELINA74, 0x07060504);
		bcma_aग_लिखो32(i2s, BCMA_MIPS_OOBSELOUTA30, 0x87);
		bcma_debug(bus,
			   "Moved i2s interrupt to oob line 7 instead of 8\n");
	पूर्ण
पूर्ण

व्योम bcma_core_mips_init(काष्ठा bcma_drv_mips *mcore)
अणु
	काष्ठा bcma_bus *bus;
	काष्ठा bcma_device *core;
	bus = mcore->core->bus;

	अगर (mcore->setup_करोne)
		वापस;

	bcma_debug(bus, "Initializing MIPS core...\n");

	bcma_core_mips_early_init(mcore);

	bcma_fix_i2s_irqflag(bus);

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4716:
	हाल BCMA_CHIP_ID_BCM4748:
		bcma_core_mips_set_irq_name(bus, 1, BCMA_CORE_80211, 0);
		bcma_core_mips_set_irq_name(bus, 2, BCMA_CORE_MAC_GBIT, 0);
		bcma_core_mips_set_irq_name(bus, 3, BCMA_CORE_USB20_HOST, 0);
		bcma_core_mips_set_irq_name(bus, 4, BCMA_CORE_PCIE, 0);
		bcma_core_mips_set_irq_name(bus, 0, BCMA_CORE_CHIPCOMMON, 0);
		bcma_core_mips_set_irq_name(bus, 0, BCMA_CORE_I2S, 0);
		अवरोध;
	हाल BCMA_CHIP_ID_BCM5356:
	हाल BCMA_CHIP_ID_BCM47162:
	हाल BCMA_CHIP_ID_BCM53572:
		bcma_core_mips_set_irq_name(bus, 1, BCMA_CORE_80211, 0);
		bcma_core_mips_set_irq_name(bus, 2, BCMA_CORE_MAC_GBIT, 0);
		bcma_core_mips_set_irq_name(bus, 0, BCMA_CORE_CHIPCOMMON, 0);
		अवरोध;
	हाल BCMA_CHIP_ID_BCM5357:
	हाल BCMA_CHIP_ID_BCM4749:
		bcma_core_mips_set_irq_name(bus, 1, BCMA_CORE_80211, 0);
		bcma_core_mips_set_irq_name(bus, 2, BCMA_CORE_MAC_GBIT, 0);
		bcma_core_mips_set_irq_name(bus, 3, BCMA_CORE_USB20_HOST, 0);
		bcma_core_mips_set_irq_name(bus, 0, BCMA_CORE_CHIPCOMMON, 0);
		bcma_core_mips_set_irq_name(bus, 0, BCMA_CORE_I2S, 0);
		अवरोध;
	हाल BCMA_CHIP_ID_BCM4706:
		bcma_core_mips_set_irq_name(bus, 1, BCMA_CORE_PCIE, 0);
		bcma_core_mips_set_irq_name(bus, 2, BCMA_CORE_4706_MAC_GBIT,
					    0);
		bcma_core_mips_set_irq_name(bus, 3, BCMA_CORE_PCIE, 1);
		bcma_core_mips_set_irq_name(bus, 4, BCMA_CORE_USB20_HOST, 0);
		bcma_core_mips_set_irq_name(bus, 0, BCMA_CORE_4706_CHIPCOMMON,
					    0);
		अवरोध;
	शेष:
		list_क्रम_each_entry(core, &bus->cores, list) अणु
			core->irq = bcma_core_irq(core, 0);
		पूर्ण
		bcma_err(bus,
			 "Unknown device (0x%x) found, can not configure IRQs\n",
			 bus->chipinfo.id);
	पूर्ण
	bcma_debug(bus, "IRQ reconfiguration done\n");
	bcma_core_mips_dump_irq(bus);

	mcore->setup_करोne = true;
पूर्ण
