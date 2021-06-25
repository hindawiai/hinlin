<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-footbridge/netwinder-hw.c
 *
 * Netwinder machine fixup
 *
 * Copyright (C) 1998, 1999 Russell King, Phil Blundell
 */
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>

#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

#घोषणा IRDA_IO_BASE		0x180
#घोषणा GP1_IO_BASE		0x338
#घोषणा GP2_IO_BASE		0x33a

/*
 * Winbond WB83977F accessibility stuff
 */
अटल अंतरभूत व्योम wb977_खोलो(व्योम)
अणु
	outb(0x87, 0x370);
	outb(0x87, 0x370);
पूर्ण

अटल अंतरभूत व्योम wb977_बंद(व्योम)
अणु
	outb(0xaa, 0x370);
पूर्ण

अटल अंतरभूत व्योम wb977_wb(पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, 0x370);
	outb(val, 0x371);
पूर्ण

अटल अंतरभूत व्योम wb977_ww(पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, 0x370);
	outb(val >> 8, 0x371);
	outb(reg + 1, 0x370);
	outb(val & 255, 0x371);
पूर्ण

#घोषणा wb977_device_select(dev)	wb977_wb(0x07, dev)
#घोषणा wb977_device_disable()		wb977_wb(0x30, 0x00)
#घोषणा wb977_device_enable()		wb977_wb(0x30, 0x01)

/*
 * This is a lock क्रम accessing ports GP1_IO_BASE and GP2_IO_BASE
 */
DEFINE_RAW_SPINLOCK(nw_gpio_lock);
EXPORT_SYMBOL(nw_gpio_lock);

अटल अचिन्हित पूर्णांक current_gpio_op;
अटल अचिन्हित पूर्णांक current_gpio_io;
अटल अचिन्हित पूर्णांक current_cpld;

व्योम nw_gpio_modअगरy_op(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक set)
अणु
	अचिन्हित पूर्णांक new_gpio, changed;

	new_gpio = (current_gpio_op & ~mask) | set;
	changed = new_gpio ^ current_gpio_op;
	current_gpio_op = new_gpio;

	अगर (changed & 0xff)
		outb(new_gpio, GP1_IO_BASE);
	अगर (changed & 0xff00)
		outb(new_gpio >> 8, GP2_IO_BASE);
पूर्ण
EXPORT_SYMBOL(nw_gpio_modअगरy_op);

अटल अंतरभूत व्योम __gpio_modअगरy_io(पूर्णांक mask, पूर्णांक in)
अणु
	अचिन्हित पूर्णांक new_gpio, changed;
	पूर्णांक port;

	new_gpio = (current_gpio_io & ~mask) | in;
	changed = new_gpio ^ current_gpio_io;
	current_gpio_io = new_gpio;

	changed >>= 1;
	new_gpio >>= 1;

	wb977_device_select(7);

	क्रम (port = 0xe1; changed && port < 0xe8; changed >>= 1) अणु
		wb977_wb(port, new_gpio & 1);

		port += 1;
		new_gpio >>= 1;
	पूर्ण

	wb977_device_select(8);

	क्रम (port = 0xe8; changed && port < 0xec; changed >>= 1) अणु
		wb977_wb(port, new_gpio & 1);

		port += 1;
		new_gpio >>= 1;
	पूर्ण
पूर्ण

व्योम nw_gpio_modअगरy_io(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक in)
अणु
	/* Open up the SuperIO chip */
	wb977_खोलो();

	__gpio_modअगरy_io(mask, in);

	/* Close up the EFER gate */
	wb977_बंद();
पूर्ण
EXPORT_SYMBOL(nw_gpio_modअगरy_io);

अचिन्हित पूर्णांक nw_gpio_पढ़ो(व्योम)
अणु
	वापस inb(GP1_IO_BASE) | inb(GP2_IO_BASE) << 8;
पूर्ण
EXPORT_SYMBOL(nw_gpio_पढ़ो);

/*
 * Initialise the Winbond W83977F global रेजिस्टरs
 */
अटल अंतरभूत व्योम wb977_init_global(व्योम)
अणु
	/*
	 * Enable R/W config रेजिस्टरs
	 */
	wb977_wb(0x26, 0x40);

	/*
	 * Power करोwn FDC (not used)
	 */
	wb977_wb(0x22, 0xfe);

	/*
	 * GP12, GP11, CIRRX, IRRXH, GP10
	 */
	wb977_wb(0x2a, 0xc1);

	/*
	 * GP23, GP22, GP21, GP20, GP13
	 */
	wb977_wb(0x2b, 0x6b);

	/*
	 * GP17, GP16, GP15, GP14
	 */
	wb977_wb(0x2c, 0x55);
पूर्ण

/*
 * Initialise the Winbond W83977F prपूर्णांकer port
 */
अटल अंतरभूत व्योम wb977_init_prपूर्णांकer(व्योम)
अणु
	wb977_device_select(1);

	/*
	 * mode 1 == EPP
	 */
	wb977_wb(0xf0, 0x01);
पूर्ण

/*
 * Initialise the Winbond W83977F keyboard controller
 */
अटल अंतरभूत व्योम wb977_init_keyboard(व्योम)
अणु
	wb977_device_select(5);

	/*
	 * Keyboard controller address
	 */
	wb977_ww(0x60, 0x0060);
	wb977_ww(0x62, 0x0064);

	/*
	 * Keyboard IRQ 1, active high, edge trigger
	 */
	wb977_wb(0x70, 1);
	wb977_wb(0x71, 0x02);

	/*
	 * Mouse IRQ 5, active high, edge trigger
	 */
	wb977_wb(0x72, 5);
	wb977_wb(0x73, 0x02);

	/*
	 * KBC 8MHz
	 */
	wb977_wb(0xf0, 0x40);

	/*
	 * Enable device
	 */
	wb977_device_enable();
पूर्ण

/*
 * Initialise the Winbond W83977F Infra-Red device
 */
अटल अंतरभूत व्योम wb977_init_irda(व्योम)
अणु
	wb977_device_select(6);

	/*
	 * IR base address
	 */
	wb977_ww(0x60, IRDA_IO_BASE);

	/*
	 * IRDA IRQ 6, active high, edge trigger
	 */
	wb977_wb(0x70, 6);
	wb977_wb(0x71, 0x02);

	/*
	 * RX DMA - ISA DMA 0
	 */
	wb977_wb(0x74, 0x00);

	/*
	 * TX DMA - Disable Tx DMA
	 */
	wb977_wb(0x75, 0x04);

	/*
	 * Append CRC, Enable bank selection
	 */
	wb977_wb(0xf0, 0x03);

	/*
	 * Enable device
	 */
	wb977_device_enable();
पूर्ण

/*
 * Initialise Winbond W83977F general purpose IO
 */
अटल अंतरभूत व्योम wb977_init_gpio(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Set up initial I/O definitions
	 */
	current_gpio_io = -1;
	__gpio_modअगरy_io(-1, GPIO_DONE | GPIO_WDTIMER);

	wb977_device_select(7);

	/*
	 * Group1 base address
	 */
	wb977_ww(0x60, GP1_IO_BASE);
	wb977_ww(0x62, 0);
	wb977_ww(0x64, 0);

	/*
	 * GP10 (Orage button) IRQ 10, active high, edge trigger
	 */
	wb977_wb(0x70, 10);
	wb977_wb(0x71, 0x02);

	/*
	 * GP10: Debounce filter enabled, IRQ, input
	 */
	wb977_wb(0xe0, 0x19);

	/*
	 * Enable Group1
	 */
	wb977_device_enable();

	wb977_device_select(8);

	/*
	 * Group2 base address
	 */
	wb977_ww(0x60, GP2_IO_BASE);

	/*
	 * Clear watchकरोg समयr regs
	 *  - समयr disable
	 */
	wb977_wb(0xf2, 0x00);

	/*
	 *  - disable LED, no mouse nor keyboard IRQ
	 */
	wb977_wb(0xf3, 0x00);

	/*
	 *  - समयr counting, disable घातer LED, disable समयouot
	 */
	wb977_wb(0xf4, 0x00);

	/*
	 * Enable group2
	 */
	wb977_device_enable();

	/*
	 * Set Group1/Group2 outमाला_दो
	 */
	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_gpio_modअगरy_op(-1, GPIO_RED_LED | GPIO_FAN);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);
पूर्ण

/*
 * Initialise the Winbond W83977F chip.
 */
अटल व्योम __init wb977_init(व्योम)
अणु
	request_region(0x370, 2, "W83977AF configuration");

	/*
	 * Open up the SuperIO chip
	 */
	wb977_खोलो();

	/*
	 * Initialise the global रेजिस्टरs
	 */
	wb977_init_global();

	/*
	 * Initialise the various devices in
	 * the multi-IO chip.
	 */
	wb977_init_prपूर्णांकer();
	wb977_init_keyboard();
	wb977_init_irda();
	wb977_init_gpio();

	/*
	 * Close up the EFER gate
	 */
	wb977_बंद();
पूर्ण

व्योम nw_cpld_modअगरy(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक set)
अणु
	पूर्णांक msk;

	current_cpld = (current_cpld & ~mask) | set;

	nw_gpio_modअगरy_io(GPIO_DATA | GPIO_IOCLK | GPIO_IOLOAD, 0);
	nw_gpio_modअगरy_op(GPIO_IOLOAD, 0);

	क्रम (msk = 8; msk; msk >>= 1) अणु
		पूर्णांक bit = current_cpld & msk;

		nw_gpio_modअगरy_op(GPIO_DATA | GPIO_IOCLK, bit ? GPIO_DATA : 0);
		nw_gpio_modअगरy_op(GPIO_IOCLK, GPIO_IOCLK);
	पूर्ण

	nw_gpio_modअगरy_op(GPIO_IOCLK|GPIO_DATA, 0);
	nw_gpio_modअगरy_op(GPIO_IOLOAD|GPIO_DSCLK, GPIO_IOLOAD|GPIO_DSCLK);
	nw_gpio_modअगरy_op(GPIO_IOLOAD, 0);
पूर्ण
EXPORT_SYMBOL(nw_cpld_modअगरy);

अटल व्योम __init cpld_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_cpld_modअगरy(-1, CPLD_UNMUTE | CPLD_7111_DISABLE);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);
पूर्ण

अटल अचिन्हित अक्षर rwa_unlock[] __initdata =
अणु 0x00, 0x00, 0x6a, 0xb5, 0xda, 0xed, 0xf6, 0xfb, 0x7d, 0xbe, 0xdf, 0x6f, 0x37, 0x1b,
  0x0d, 0x86, 0xc3, 0x61, 0xb0, 0x58, 0x2c, 0x16, 0x8b, 0x45, 0xa2, 0xd1, 0xe8, 0x74,
  0x3a, 0x9d, 0xce, 0xe7, 0x73, 0x39 पूर्ण;

#अगर_अघोषित DEBUG
#घोषणा dprपूर्णांकk(x...)
#अन्यथा
#घोषणा dprपूर्णांकk(x...) prपूर्णांकk(x)
#पूर्ण_अगर

#घोषणा WRITE_RWA(r,v) करो अणु outb((r), 0x279); udelay(10); outb((v), 0xa79); पूर्ण जबतक (0)

अटल अंतरभूत व्योम rwa010_unlock(व्योम)
अणु
	पूर्णांक i;

	WRITE_RWA(2, 2);
	mdelay(10);

	क्रम (i = 0; i < माप(rwa_unlock); i++) अणु
		outb(rwa_unlock[i], 0x279);
		udelay(10);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rwa010_पढ़ो_ident(व्योम)
अणु
	अचिन्हित अक्षर si[9];
	पूर्णांक i, j;

	WRITE_RWA(3, 0);
	WRITE_RWA(0, 128);

	outb(1, 0x279);

	mdelay(1);

	dprपूर्णांकk("Identifier: ");
	क्रम (i = 0; i < 9; i++) अणु
		si[i] = 0;
		क्रम (j = 0; j < 8; j++) अणु
			पूर्णांक bit;
			udelay(250);
			inb(0x203);
			udelay(250);
			bit = inb(0x203);
			dprपूर्णांकk("%02X ", bit);
			bit = (bit == 0xaa) ? 1 : 0;
			si[i] |= bit << j;
		पूर्ण
		dprपूर्णांकk("(%02X) ", si[i]);
	पूर्ण
	dprपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम rwa010_global_init(व्योम)
अणु
	WRITE_RWA(6, 2);	// Assign a card no = 2

	dprपूर्णांकk("Card no = %d\n", inb(0x203));

	/* disable the modem section of the chip */
	WRITE_RWA(7, 3);
	WRITE_RWA(0x30, 0);

	/* disable the cdrom section of the chip */
	WRITE_RWA(7, 4);
	WRITE_RWA(0x30, 0);

	/* disable the MPU-401 section of the chip */
	WRITE_RWA(7, 2);
	WRITE_RWA(0x30, 0);
पूर्ण

अटल अंतरभूत व्योम rwa010_game_port_init(व्योम)
अणु
	पूर्णांक i;

	WRITE_RWA(7, 5);

	dprपूर्णांकk("Slider base: ");
	WRITE_RWA(0x61, 1);
	i = inb(0x203);

	WRITE_RWA(0x60, 2);
	dprपूर्णांकk("%02X%02X (201)\n", inb(0x203), i);

	WRITE_RWA(0x30, 1);
पूर्ण

अटल अंतरभूत व्योम rwa010_waveartist_init(पूर्णांक base, पूर्णांक irq, पूर्णांक dma)
अणु
	पूर्णांक i;

	WRITE_RWA(7, 0);

	dprपूर्णांकk("WaveArtist base: ");
	WRITE_RWA(0x61, base & 255);
	i = inb(0x203);

	WRITE_RWA(0x60, base >> 8);
	dprपूर्णांकk("%02X%02X (%X),", inb(0x203), i, base);

	WRITE_RWA(0x70, irq);
	dprपूर्णांकk(" irq: %d (%d),", inb(0x203), irq);

	WRITE_RWA(0x74, dma);
	dprपूर्णांकk(" dma: %d (%d)\n", inb(0x203), dma);

	WRITE_RWA(0x30, 1);
पूर्ण

अटल अंतरभूत व्योम rwa010_soundblaster_init(पूर्णांक sb_base, पूर्णांक al_base, पूर्णांक irq, पूर्णांक dma)
अणु
	पूर्णांक i;

	WRITE_RWA(7, 1);

	dprपूर्णांकk("SoundBlaster base: ");
	WRITE_RWA(0x61, sb_base & 255);
	i = inb(0x203);

	WRITE_RWA(0x60, sb_base >> 8);
	dprपूर्णांकk("%02X%02X (%X),", inb(0x203), i, sb_base);

	dprपूर्णांकk(" irq: ");
	WRITE_RWA(0x70, irq);
	dprपूर्णांकk("%d (%d),", inb(0x203), irq);

	dprपूर्णांकk(" 8-bit DMA: ");
	WRITE_RWA(0x74, dma);
	dprपूर्णांकk("%d (%d)\n", inb(0x203), dma);

	dprपूर्णांकk("AdLib base: ");
	WRITE_RWA(0x63, al_base & 255);
	i = inb(0x203);

	WRITE_RWA(0x62, al_base >> 8);
	dprपूर्णांकk("%02X%02X (%X)\n", inb(0x203), i, al_base);

	WRITE_RWA(0x30, 1);
पूर्ण

अटल व्योम rwa010_soundblaster_reset(व्योम)
अणु
	पूर्णांक i;

	outb(1, 0x226);
	udelay(3);
	outb(0, 0x226);

	क्रम (i = 0; i < 5; i++) अणु
		अगर (inb(0x22e) & 0x80)
			अवरोध;
		mdelay(1);
	पूर्ण
	अगर (i == 5)
		prपूर्णांकk("SoundBlaster: DSP reset failed\n");

	dprपूर्णांकk("SoundBlaster DSP reset: %02X (AA)\n", inb(0x22a));

	क्रम (i = 0; i < 5; i++) अणु
		अगर ((inb(0x22c) & 0x80) == 0)
			अवरोध;
		mdelay(1);
	पूर्ण

	अगर (i == 5)
		prपूर्णांकk("SoundBlaster: DSP not ready\n");
	अन्यथा अणु
		outb(0xe1, 0x22c);

		dprपूर्णांकk("SoundBlaster DSP id: ");
		i = inb(0x22a);
		udelay(1);
		i |= inb(0x22a) << 8;
		dprपूर्णांकk("%04X\n", i);

		क्रम (i = 0; i < 5; i++) अणु
			अगर ((inb(0x22c) & 0x80) == 0)
				अवरोध;
			mdelay(1);
		पूर्ण

		अगर (i == 5)
			prपूर्णांकk("SoundBlaster: could not turn speaker off\n");

		outb(0xd3, 0x22c);
	पूर्ण

	/* turn on OPL3 */
	outb(5, 0x38a);
	outb(1, 0x38b);
पूर्ण

अटल व्योम __init rwa010_init(व्योम)
अणु
	rwa010_unlock();
	rwa010_पढ़ो_ident();
	rwa010_global_init();
	rwa010_game_port_init();
	rwa010_waveartist_init(0x250, 3, 7);
	rwa010_soundblaster_init(0x220, 0x388, 3, 1);
	rwa010_soundblaster_reset();
पूर्ण

/*
 * Initialise any other hardware after we've got the PCI bus
 * initialised.  We may need the PCI bus to talk to this other
 * hardware.
 */
अटल पूर्णांक __init nw_hw_init(व्योम)
अणु
	अगर (machine_is_netwinder()) अणु
		wb977_init();
		cpld_init();
		rwa010_init();
	पूर्ण
	वापस 0;
पूर्ण

__initcall(nw_hw_init);

/*
 * Older NeTTroms either करो not provide a parameters
 * page, or they करोn't supply correct inक्रमmation in
 * the parameter page.
 */
अटल व्योम __init
fixup_netwinder(काष्ठा tag *tags, अक्षर **cmdline)
अणु
#अगर_घोषित CONFIG_ISAPNP
	बाह्य पूर्णांक isapnp_disable;

	/*
	 * We must not use the kernels ISAPnP code
	 * on the NetWinder - it will reset the settings
	 * क्रम the WaveArtist chip and render it inoperable.
	 */
	isapnp_disable = 1;
#पूर्ण_अगर
पूर्ण

अटल व्योम netwinder_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (mode == REBOOT_SOFT) अणु
		/* Jump पूर्णांकo the ROM */
		soft_restart(0x41000000);
	पूर्ण अन्यथा अणु
		local_irq_disable();
		local_fiq_disable();

		/* खोलो up the SuperIO chip */
		outb(0x87, 0x370);
		outb(0x87, 0x370);

		/* aux function group 1 (logical device 7) */
		outb(0x07, 0x370);
		outb(0x07, 0x371);

		/* set GP16 क्रम WD-TIMER output */
		outb(0xe6, 0x370);
		outb(0x00, 0x371);

		/* set a RED LED and toggle WD_TIMER क्रम rebooting */
		outb(0xc4, 0x338);
	पूर्ण
पूर्ण

/* LEDs */
#अगर defined(CONFIG_NEW_LEDS) && defined(CONFIG_LEDS_CLASS)
काष्ठा netwinder_led अणु
	काष्ठा led_classdev     cdev;
	u8                      mask;
पूर्ण;

/*
 * The triggers lines up below will only be used अगर the
 * LED triggers are compiled in.
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण netwinder_leds[] = अणु
	अणु "netwinder:green", "heartbeat", पूर्ण,
	अणु "netwinder:red", "cpu0", पूर्ण,
पूर्ण;

/*
 * The LED control in Netwinder is reversed:
 *  - setting bit means turn off LED
 *  - clearing bit means turn on LED
 */
अटल व्योम netwinder_led_set(काष्ठा led_classdev *cdev,
		क्रमागत led_brightness b)
अणु
	काष्ठा netwinder_led *led = container_of(cdev,
			काष्ठा netwinder_led, cdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	reg = nw_gpio_पढ़ो();
	अगर (b != LED_OFF)
		reg &= ~led->mask;
	अन्यथा
		reg |= led->mask;
	nw_gpio_modअगरy_op(led->mask, reg);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);
पूर्ण

अटल क्रमागत led_brightness netwinder_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा netwinder_led *led = container_of(cdev,
			काष्ठा netwinder_led, cdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	reg = nw_gpio_पढ़ो();
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);

	वापस (reg & led->mask) ? LED_OFF : LED_FULL;
पूर्ण

अटल पूर्णांक __init netwinder_leds_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!machine_is_netwinder())
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(netwinder_leds); i++) अणु
		काष्ठा netwinder_led *led;

		led = kzalloc(माप(*led), GFP_KERNEL);
		अगर (!led)
			अवरोध;

		led->cdev.name = netwinder_leds[i].name;
		led->cdev.brightness_set = netwinder_led_set;
		led->cdev.brightness_get = netwinder_led_get;
		led->cdev.शेष_trigger = netwinder_leds[i].trigger;

		अगर (i == 0)
			led->mask = GPIO_GREEN_LED;
		अन्यथा
			led->mask = GPIO_RED_LED;

		अगर (led_classdev_रेजिस्टर(शून्य, &led->cdev) < 0) अणु
			kमुक्त(led);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Since we may have triggers on any subप्रणाली, defer registration
 * until after subप्रणाली_init.
 */
fs_initcall(netwinder_leds_init);
#पूर्ण_अगर

MACHINE_START(NETWINDER, "Rebel-NetWinder")
	/* Maपूर्णांकainer: Russell King/Rebel.com */
	.atag_offset	= 0x100,
	.video_start	= 0x000a0000,
	.video_end	= 0x000bffff,
	.reserve_lp0	= 1,
	.reserve_lp2	= 1,
	.fixup		= fixup_netwinder,
	.map_io		= footbridge_map_io,
	.init_irq	= footbridge_init_irq,
	.init_समय	= isa_समयr_init,
	.restart	= netwinder_restart,
MACHINE_END
