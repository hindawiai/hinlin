<शैली गुरु>
/*
 * Toshiba RBTX4939 setup routines.
 * Based on linux/arch/mips/txx9/rbtx4938/setup.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * Copyright (C) 2000-2001,2005-2007 Toshiba Corporation
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/map.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/rbtx4939.h>

अटल व्योम rbtx4939_machine_restart(अक्षर *command)
अणु
	local_irq_disable();
	ग_लिखोb(1, rbtx4939_reseten_addr);
	ग_लिखोb(1, rbtx4939_softreset_addr);
	जबतक (1)
		;
पूर्ण

अटल व्योम __init rbtx4939_समय_init(व्योम)
अणु
	tx4939_समय_init(0);
पूर्ण

#अगर defined(__BIG_ENDIAN) && IS_ENABLED(CONFIG_SMC91X)
#घोषणा HAVE_RBTX4939_IOSWAB
#घोषणा IS_CE1_ADDR(addr) \
	((((अचिन्हित दीर्घ)(addr) - IO_BASE) & 0xfff00000) == TXX9_CE(1))
अटल u16 rbtx4939_ioswabw(अस्थिर u16 *a, u16 x)
अणु
	वापस IS_CE1_ADDR(a) ? x : le16_to_cpu(x);
पूर्ण
अटल u16 rbtx4939_mem_ioswabw(अस्थिर u16 *a, u16 x)
अणु
	वापस !IS_CE1_ADDR(a) ? x : le16_to_cpu(x);
पूर्ण
#पूर्ण_अगर /* __BIG_ENDIAN && CONFIG_SMC91X */

अटल व्योम __init rbtx4939_pci_setup(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	पूर्णांक extarb = !(__raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_PCIARB);
	काष्ठा pci_controller *c = &txx9_primary_pcic;

	रेजिस्टर_pci_controller(c);

	tx4939_report_pciclk();
	tx4927_pcic_setup(tx4939_pcicptr, c, extarb);
	अगर (!(__raw_पढ़ोq(&tx4939_ccfgptr->pcfg) & TX4939_PCFG_ATA1MODE) &&
	    (__raw_पढ़ोq(&tx4939_ccfgptr->pcfg) &
	     (TX4939_PCFG_ET0MODE | TX4939_PCFG_ET1MODE))) अणु
		tx4939_report_pci1clk();

		/* mem:64K(max), io:64K(max) (enough क्रम ETH0,ETH1) */
		c = txx9_alloc_pci_controller(शून्य, 0, 0x10000, 0, 0x10000);
		रेजिस्टर_pci_controller(c);
		tx4927_pcic_setup(tx4939_pcic1ptr, c, 0);
	पूर्ण

	tx4939_setup_pcierr_irq();
#पूर्ण_अगर /* CONFIG_PCI */
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ शेष_ebccr[] __initdata = अणु
	0x01c0000000007608ULL, /* 64M ROM */
	0x017f000000007049ULL, /* 1M IOC */
	0x0180000000408608ULL, /* ISA */
	0,
पूर्ण;

अटल व्योम __init rbtx4939_ebusc_setup(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक sp;

	/* use user-configured speed */
	sp = TX4939_EBUSC_CR(0) & 0x30;
	शेष_ebccr[0] |= sp;
	शेष_ebccr[1] |= sp;
	शेष_ebccr[2] |= sp;
	/* initialise by myself */
	क्रम (i = 0; i < ARRAY_SIZE(शेष_ebccr); i++) अणु
		अगर (शेष_ebccr[i])
			____raw_ग_लिखोq(शेष_ebccr[i],
				       &tx4939_ebuscptr->cr[i]);
		अन्यथा
			____raw_ग_लिखोq(____raw_पढ़ोq(&tx4939_ebuscptr->cr[i])
				       & ~8,
				       &tx4939_ebuscptr->cr[i]);
	पूर्ण
पूर्ण

अटल व्योम __init rbtx4939_update_ioc_pen(व्योम)
अणु
	__u64 pcfg = ____raw_पढ़ोq(&tx4939_ccfgptr->pcfg);
	__u64 ccfg = ____raw_पढ़ोq(&tx4939_ccfgptr->ccfg);
	__u8 pe1 = पढ़ोb(rbtx4939_pe1_addr);
	__u8 pe2 = पढ़ोb(rbtx4939_pe2_addr);
	__u8 pe3 = पढ़ोb(rbtx4939_pe3_addr);
	अगर (pcfg & TX4939_PCFG_ATA0MODE)
		pe1 |= RBTX4939_PE1_ATA(0);
	अन्यथा
		pe1 &= ~RBTX4939_PE1_ATA(0);
	अगर (pcfg & TX4939_PCFG_ATA1MODE) अणु
		pe1 |= RBTX4939_PE1_ATA(1);
		pe1 &= ~(RBTX4939_PE1_RMII(0) | RBTX4939_PE1_RMII(1));
	पूर्ण अन्यथा अणु
		pe1 &= ~RBTX4939_PE1_ATA(1);
		अगर (pcfg & TX4939_PCFG_ET0MODE)
			pe1 |= RBTX4939_PE1_RMII(0);
		अन्यथा
			pe1 &= ~RBTX4939_PE1_RMII(0);
		अगर (pcfg & TX4939_PCFG_ET1MODE)
			pe1 |= RBTX4939_PE1_RMII(1);
		अन्यथा
			pe1 &= ~RBTX4939_PE1_RMII(1);
	पूर्ण
	अगर (ccfg & TX4939_CCFG_PTSEL)
		pe3 &= ~(RBTX4939_PE3_VP | RBTX4939_PE3_VP_P |
			 RBTX4939_PE3_VP_S);
	अन्यथा अणु
		__u64 vmode = pcfg &
			(TX4939_PCFG_VSSMODE | TX4939_PCFG_VPSMODE);
		अगर (vmode == 0)
			pe3 &= ~(RBTX4939_PE3_VP | RBTX4939_PE3_VP_P |
				 RBTX4939_PE3_VP_S);
		अन्यथा अगर (vmode == TX4939_PCFG_VPSMODE) अणु
			pe3 |= RBTX4939_PE3_VP_P;
			pe3 &= ~(RBTX4939_PE3_VP | RBTX4939_PE3_VP_S);
		पूर्ण अन्यथा अगर (vmode == TX4939_PCFG_VSSMODE) अणु
			pe3 |= RBTX4939_PE3_VP | RBTX4939_PE3_VP_S;
			pe3 &= ~RBTX4939_PE3_VP_P;
		पूर्ण अन्यथा अणु
			pe3 |= RBTX4939_PE3_VP | RBTX4939_PE3_VP_P;
			pe3 &= ~RBTX4939_PE3_VP_S;
		पूर्ण
	पूर्ण
	अगर (pcfg & TX4939_PCFG_SPIMODE) अणु
		अगर (pcfg & TX4939_PCFG_SIO2MODE_GPIO)
			pe2 &= ~(RBTX4939_PE2_SIO2 | RBTX4939_PE2_SIO0);
		अन्यथा अणु
			अगर (pcfg & TX4939_PCFG_SIO2MODE_SIO2) अणु
				pe2 |= RBTX4939_PE2_SIO2;
				pe2 &= ~RBTX4939_PE2_SIO0;
			पूर्ण अन्यथा अणु
				pe2 |= RBTX4939_PE2_SIO0;
				pe2 &= ~RBTX4939_PE2_SIO2;
			पूर्ण
		पूर्ण
		अगर (pcfg & TX4939_PCFG_SIO3MODE)
			pe2 |= RBTX4939_PE2_SIO3;
		अन्यथा
			pe2 &= ~RBTX4939_PE2_SIO3;
		pe2 &= ~RBTX4939_PE2_SPI;
	पूर्ण अन्यथा अणु
		pe2 |= RBTX4939_PE2_SPI;
		pe2 &= ~(RBTX4939_PE2_SIO3 | RBTX4939_PE2_SIO2 |
			 RBTX4939_PE2_SIO0);
	पूर्ण
	अगर ((pcfg & TX4939_PCFG_I2SMODE_MASK) == TX4939_PCFG_I2SMODE_GPIO)
		pe2 |= RBTX4939_PE2_GPIO;
	अन्यथा
		pe2 &= ~RBTX4939_PE2_GPIO;
	ग_लिखोb(pe1, rbtx4939_pe1_addr);
	ग_लिखोb(pe2, rbtx4939_pe2_addr);
	ग_लिखोb(pe3, rbtx4939_pe3_addr);
पूर्ण

#घोषणा RBTX4939_MAX_7SEGLEDS	8

#अगर IS_BUILTIN(CONFIG_LEDS_CLASS)
अटल u8 led_val[RBTX4939_MAX_7SEGLEDS];
काष्ठा rbtx4939_led_data अणु
	काष्ठा led_classdev cdev;
	अक्षर name[32];
	अचिन्हित पूर्णांक num;
पूर्ण;

/* Use "dot" in 7seg LEDs */
अटल व्योम rbtx4939_led_brightness_set(काष्ठा led_classdev *led_cdev,
					क्रमागत led_brightness value)
अणु
	काष्ठा rbtx4939_led_data *led_dat =
		container_of(led_cdev, काष्ठा rbtx4939_led_data, cdev);
	अचिन्हित पूर्णांक num = led_dat->num;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	led_val[num] = (led_val[num] & 0x7f) | (value ? 0x80 : 0);
	ग_लिखोb(led_val[num], rbtx4939_7seg_addr(num / 4, num % 4));
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __init rbtx4939_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rbtx4939_led_data *leds_data;
	पूर्णांक i;
	अटल अक्षर *शेष_triggers[] __initdata = अणु
		"heartbeat",
		"disk-activity",
		"nand-disk",
	पूर्ण;

	leds_data = kसुस्मृति(RBTX4939_MAX_7SEGLEDS, माप(*leds_data),
			    GFP_KERNEL);
	अगर (!leds_data)
		वापस -ENOMEM;
	क्रम (i = 0; i < RBTX4939_MAX_7SEGLEDS; i++) अणु
		पूर्णांक rc;
		काष्ठा rbtx4939_led_data *led_dat = &leds_data[i];

		led_dat->num = i;
		led_dat->cdev.brightness_set = rbtx4939_led_brightness_set;
		प्र_लिखो(led_dat->name, "rbtx4939:amber:%u", i);
		led_dat->cdev.name = led_dat->name;
		अगर (i < ARRAY_SIZE(शेष_triggers))
			led_dat->cdev.शेष_trigger = शेष_triggers[i];
		rc = led_classdev_रेजिस्टर(&pdev->dev, &led_dat->cdev);
		अगर (rc < 0)
			वापस rc;
		led_dat->cdev.brightness_set(&led_dat->cdev, 0);
	पूर्ण
	वापस 0;

पूर्ण

अटल काष्ठा platक्रमm_driver rbtx4939_led_driver = अणु
	.driver	 = अणु
		.name = "rbtx4939-led",
	पूर्ण,
पूर्ण;

अटल व्योम __init rbtx4939_led_setup(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("rbtx4939-led", -1, शून्य, 0);
	platक्रमm_driver_probe(&rbtx4939_led_driver, rbtx4939_led_probe);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम rbtx4939_led_setup(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __rbtx4939_7segled_अ_दो(अचिन्हित पूर्णांक pos, अचिन्हित अक्षर val)
अणु
#अगर IS_BUILTIN(CONFIG_LEDS_CLASS)
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	/* bit7: reserved क्रम LED class */
	led_val[pos] = (led_val[pos] & 0x80) | (val & 0x7f);
	val = led_val[pos];
	local_irq_restore(flags);
#पूर्ण_अगर
	ग_लिखोb(val, rbtx4939_7seg_addr(pos / 4, pos % 4));
पूर्ण

अटल व्योम rbtx4939_7segled_अ_दो(अचिन्हित पूर्णांक pos, अचिन्हित अक्षर val)
अणु
	/* convert from map_to_seg7() notation */
	val = (val & 0x88) |
		((val & 0x40) >> 6) |
		((val & 0x20) >> 4) |
		((val & 0x10) >> 2) |
		((val & 0x04) << 2) |
		((val & 0x02) << 4) |
		((val & 0x01) << 6);
	__rbtx4939_7segled_अ_दो(pos, val);
पूर्ण

#अगर IS_ENABLED(CONFIG_MTD_RBTX4939)
/* special mapping क्रम boot rom */
अटल अचिन्हित दीर्घ rbtx4939_flash_fixup_ofs(अचिन्हित दीर्घ ofs)
अणु
	u8 bdipsw = पढ़ोb(rbtx4939_bdipsw_addr) & 0x0f;
	अचिन्हित अक्षर shअगरt;

	अगर (bdipsw & 8) अणु
		/* BOOT Mode: USER ROM1 / USER ROM2 */
		shअगरt = bdipsw & 3;
		/* rotate A[23:22] */
		वापस (ofs & ~0xc00000) | ((((ofs >> 22) + shअगरt) & 3) << 22);
	पूर्ण
#अगर_घोषित __BIG_ENDIAN
	अगर (bdipsw == 0)
		/* BOOT Mode: Monitor ROM */
		ofs ^= 0x400000;	/* swap A[22] */
#पूर्ण_अगर
	वापस ofs;
पूर्ण

अटल map_word rbtx4939_flash_पढ़ो16(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word r;

	ofs = rbtx4939_flash_fixup_ofs(ofs);
	r.x[0] = __raw_पढ़ोw(map->virt + ofs);
	वापस r;
पूर्ण

अटल व्योम rbtx4939_flash_ग_लिखो16(काष्ठा map_info *map, स्थिर map_word datum,
				   अचिन्हित दीर्घ ofs)
अणु
	ofs = rbtx4939_flash_fixup_ofs(ofs);
	__raw_ग_लिखोw(datum.x[0], map->virt + ofs);
	mb();	/* see अंतरभूत_map_ग_लिखो() in mtd/map.h */
पूर्ण

अटल व्योम rbtx4939_flash_copy_from(काष्ठा map_info *map, व्योम *to,
				     अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	u8 bdipsw = पढ़ोb(rbtx4939_bdipsw_addr) & 0x0f;
	अचिन्हित अक्षर shअगरt;
	sमाप_प्रकार curlen;

	from += (अचिन्हित दीर्घ)map->virt;
	अगर (bdipsw & 8) अणु
		/* BOOT Mode: USER ROM1 / USER ROM2 */
		shअगरt = bdipsw & 3;
		जबतक (len) अणु
			curlen = min_t(अचिन्हित दीर्घ, len,
				     0x400000 - (from & (0x400000 - 1)));
			स_नकल(to,
			       (व्योम *)((from & ~0xc00000) |
					((((from >> 22) + shअगरt) & 3) << 22)),
			       curlen);
			len -= curlen;
			from += curlen;
			to += curlen;
		पूर्ण
		वापस;
	पूर्ण
#अगर_घोषित __BIG_ENDIAN
	अगर (bdipsw == 0) अणु
		/* BOOT Mode: Monitor ROM */
		जबतक (len) अणु
			curlen = min_t(अचिन्हित दीर्घ, len,
				     0x400000 - (from & (0x400000 - 1)));
			स_नकल(to, (व्योम *)(from ^ 0x400000), curlen);
			len -= curlen;
			from += curlen;
			to += curlen;
		पूर्ण
		वापस;
	पूर्ण
#पूर्ण_अगर
	स_नकल(to, (व्योम *)from, len);
पूर्ण

अटल व्योम rbtx4939_flash_map_init(काष्ठा map_info *map)
अणु
	map->पढ़ो = rbtx4939_flash_पढ़ो16;
	map->ग_लिखो = rbtx4939_flash_ग_लिखो16;
	map->copy_from = rbtx4939_flash_copy_from;
पूर्ण

अटल व्योम __init rbtx4939_mtd_init(व्योम)
अणु
	अटल काष्ठा अणु
		काष्ठा platक्रमm_device dev;
		काष्ठा resource res;
		काष्ठा rbtx4939_flash_data data;
	पूर्ण pdevs[4];
	पूर्णांक i;
	अटल अक्षर names[4][8];
	अटल काष्ठा mtd_partition parts[4];
	काष्ठा rbtx4939_flash_data *boot_pdata = &pdevs[0].data;
	u8 bdipsw = पढ़ोb(rbtx4939_bdipsw_addr) & 0x0f;

	अगर (bdipsw & 8) अणु
		/* BOOT Mode: USER ROM1 / USER ROM2 */
		boot_pdata->nr_parts = 4;
		क्रम (i = 0; i < boot_pdata->nr_parts; i++) अणु
			प्र_लिखो(names[i], "img%d", 4 - i);
			parts[i].name = names[i];
			parts[i].size = 0x400000;
			parts[i].offset = MTDPART_OFS_NXTBLK;
		पूर्ण
	पूर्ण अन्यथा अगर (bdipsw == 0) अणु
		/* BOOT Mode: Monitor ROM */
		boot_pdata->nr_parts = 2;
		म_नकल(names[0], "big");
		म_नकल(names[1], "little");
		क्रम (i = 0; i < boot_pdata->nr_parts; i++) अणु
			parts[i].name = names[i];
			parts[i].size = 0x400000;
			parts[i].offset = MTDPART_OFS_NXTBLK;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* BOOT Mode: ROM Emulator */
		boot_pdata->nr_parts = 2;
		parts[0].name = "boot";
		parts[0].offset = 0xc00000;
		parts[0].size = 0x400000;
		parts[1].name = "user";
		parts[1].offset = 0;
		parts[1].size = 0xc00000;
	पूर्ण
	boot_pdata->parts = parts;
	boot_pdata->map_init = rbtx4939_flash_map_init;

	क्रम (i = 0; i < ARRAY_SIZE(pdevs); i++) अणु
		काष्ठा resource *r = &pdevs[i].res;
		काष्ठा platक्रमm_device *dev = &pdevs[i].dev;

		r->start = 0x1f000000 - i * 0x1000000;
		r->end = r->start + 0x1000000 - 1;
		r->flags = IORESOURCE_MEM;
		pdevs[i].data.width = 2;
		dev->num_resources = 1;
		dev->resource = r;
		dev->id = i;
		dev->name = "rbtx4939-flash";
		dev->dev.platक्रमm_data = &pdevs[i].data;
		platक्रमm_device_रेजिस्टर(dev);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init rbtx4939_mtd_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __init rbtx4939_arch_init(व्योम)
अणु
	rbtx4939_pci_setup();
पूर्ण

अटल व्योम __init rbtx4939_device_init(व्योम)
अणु
	अचिन्हित दीर्घ smc_addr = RBTX4939_ETHER_ADDR - IO_BASE;
	काष्ठा resource smc_res[] = अणु
		अणु
			.start	= smc_addr,
			.end	= smc_addr + 0x10 - 1,
			.flags	= IORESOURCE_MEM,
		पूर्ण, अणु
			.start	= RBTX4939_IRQ_ETHER,
			/* override शेष irq flag defined in smc91x.h */
			.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
		पूर्ण,
	पूर्ण;
	काष्ठा smc91x_platdata smc_pdata = अणु
		.flags = SMC91X_USE_16BIT,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev;
#अगर IS_ENABLED(CONFIG_TC35815)
	पूर्णांक i, j;
	अचिन्हित अक्षर ethaddr[2][6];
	u8 bdipsw = पढ़ोb(rbtx4939_bdipsw_addr) & 0x0f;

	क्रम (i = 0; i < 2; i++) अणु
		अचिन्हित दीर्घ area = CKSEG1 + 0x1fff0000 + (i * 0x10);
		अगर (bdipsw == 0)
			स_नकल(ethaddr[i], (व्योम *)area, 6);
		अन्यथा अणु
			u16 buf[3];
			अगर (bdipsw & 8)
				area -= 0x03000000;
			अन्यथा
				area -= 0x01000000;
			क्रम (j = 0; j < 3; j++)
				buf[j] = le16_to_cpup((u16 *)(area + j * 2));
			स_नकल(ethaddr[i], buf, 6);
		पूर्ण
	पूर्ण
	tx4939_ethaddr_init(ethaddr[0], ethaddr[1]);
#पूर्ण_अगर
	pdev = platक्रमm_device_alloc("smc91x", -1);
	अगर (!pdev ||
	    platक्रमm_device_add_resources(pdev, smc_res, ARRAY_SIZE(smc_res)) ||
	    platक्रमm_device_add_data(pdev, &smc_pdata, माप(smc_pdata)) ||
	    platक्रमm_device_add(pdev))
		platक्रमm_device_put(pdev);
	rbtx4939_mtd_init();
	/* TC58DVM82A1FT: tDH=10ns, tWP=tRP=tREADID=35ns */
	tx4939_ndfmc_init(10, 35,
			  (1 << 1) | (1 << 2),
			  (1 << 2)); /* ch1:8bit, ch2:16bit */
	rbtx4939_led_setup();
	tx4939_wdt_init();
	tx4939_ata_init();
	tx4939_rtc_init();
	tx4939_dmac_init(0, 2);
	tx4939_aclc_init();
	platक्रमm_device_रेजिस्टर_simple("txx9aclc-generic", -1, शून्य, 0);
	tx4939_sramc_init();
	tx4939_rng_init();
पूर्ण

अटल व्योम __init rbtx4939_setup(व्योम)
अणु
	पूर्णांक i;

	rbtx4939_ebusc_setup();
	/* always enable ATA0 */
	txx9_set64(&tx4939_ccfgptr->pcfg, TX4939_PCFG_ATA0MODE);
	अगर (txx9_master_घड़ी == 0)
		txx9_master_घड़ी = 20000000;
	tx4939_setup();
	rbtx4939_update_ioc_pen();
#अगर_घोषित HAVE_RBTX4939_IOSWAB
	ioswabw = rbtx4939_ioswabw;
	__mem_ioswabw = rbtx4939_mem_ioswabw;
#पूर्ण_अगर

	_machine_restart = rbtx4939_machine_restart;

	txx9_7segled_init(RBTX4939_MAX_7SEGLEDS, rbtx4939_7segled_अ_दो);
	क्रम (i = 0; i < RBTX4939_MAX_7SEGLEDS; i++)
		txx9_7segled_अ_दो(i, '-');
	pr_info("RBTX4939 (Rev %02x) --- FPGA(Rev %02x) DIPSW:%02x,%02x\n",
		पढ़ोb(rbtx4939_board_rev_addr), पढ़ोb(rbtx4939_ioc_rev_addr),
		पढ़ोb(rbtx4939_udipsw_addr), पढ़ोb(rbtx4939_bdipsw_addr));

#अगर_घोषित CONFIG_PCI
	txx9_alloc_pci_controller(&txx9_primary_pcic, 0, 0, 0, 0);
	txx9_board_pcibios_setup = tx4927_pcibios_setup;
#अन्यथा
	set_io_port_base(RBTX4939_ETHER_BASE);
#पूर्ण_अगर

	tx4939_sio_init(TX4939_SCLK0(txx9_master_घड़ी), 0);
पूर्ण

काष्ठा txx9_board_vec rbtx4939_vec __initdata = अणु
	.प्रणाली = "Toshiba RBTX4939",
	.prom_init = rbtx4939_prom_init,
	.mem_setup = rbtx4939_setup,
	.irq_setup = rbtx4939_irq_setup,
	.समय_init = rbtx4939_समय_init,
	.device_init = rbtx4939_device_init,
	.arch_init = rbtx4939_arch_init,
#अगर_घोषित CONFIG_PCI
	.pci_map_irq = tx4939_pci_map_irq,
#पूर्ण_अगर
पूर्ण;
