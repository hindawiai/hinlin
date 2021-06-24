<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DBAu1200/PBAu1200 board platक्रमm device registration
 *
 * Copyright (C) 2008-2011 Manuel Lauss
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1100_mmc.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>
#समावेश <यंत्र/mach-au1x00/au1200fb.h>
#समावेश <यंत्र/mach-au1x00/au1550_spi.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

#समावेश "platform.h"

#घोषणा BCSR_INT_IDE		0x0001
#घोषणा BCSR_INT_ETH		0x0002
#घोषणा BCSR_INT_PC0		0x0004
#घोषणा BCSR_INT_PC0STSCHG	0x0008
#घोषणा BCSR_INT_PC1		0x0010
#घोषणा BCSR_INT_PC1STSCHG	0x0020
#घोषणा BCSR_INT_DC		0x0040
#घोषणा BCSR_INT_FLASHBUSY	0x0080
#घोषणा BCSR_INT_PC0INSERT	0x0100
#घोषणा BCSR_INT_PC0EJECT	0x0200
#घोषणा BCSR_INT_PC1INSERT	0x0400
#घोषणा BCSR_INT_PC1EJECT	0x0800
#घोषणा BCSR_INT_SD0INSERT	0x1000
#घोषणा BCSR_INT_SD0EJECT	0x2000
#घोषणा BCSR_INT_SD1INSERT	0x4000
#घोषणा BCSR_INT_SD1EJECT	0x8000

#घोषणा DB1200_IDE_PHYS_ADDR	0x18800000
#घोषणा DB1200_IDE_REG_SHIFT	5
#घोषणा DB1200_IDE_PHYS_LEN	(16 << DB1200_IDE_REG_SHIFT)
#घोषणा DB1200_ETH_PHYS_ADDR	0x19000300
#घोषणा DB1200_न_अंकD_PHYS_ADDR	0x20000000

#घोषणा PB1200_IDE_PHYS_ADDR	0x0C800000
#घोषणा PB1200_ETH_PHYS_ADDR	0x0D000300
#घोषणा PB1200_न_अंकD_PHYS_ADDR	0x1C000000

#घोषणा DB1200_INT_BEGIN	(AU1000_MAX_INTR + 1)
#घोषणा DB1200_IDE_INT		(DB1200_INT_BEGIN + 0)
#घोषणा DB1200_ETH_INT		(DB1200_INT_BEGIN + 1)
#घोषणा DB1200_PC0_INT		(DB1200_INT_BEGIN + 2)
#घोषणा DB1200_PC0_STSCHG_INT	(DB1200_INT_BEGIN + 3)
#घोषणा DB1200_PC1_INT		(DB1200_INT_BEGIN + 4)
#घोषणा DB1200_PC1_STSCHG_INT	(DB1200_INT_BEGIN + 5)
#घोषणा DB1200_DC_INT		(DB1200_INT_BEGIN + 6)
#घोषणा DB1200_FLASHBUSY_INT	(DB1200_INT_BEGIN + 7)
#घोषणा DB1200_PC0_INSERT_INT	(DB1200_INT_BEGIN + 8)
#घोषणा DB1200_PC0_EJECT_INT	(DB1200_INT_BEGIN + 9)
#घोषणा DB1200_PC1_INSERT_INT	(DB1200_INT_BEGIN + 10)
#घोषणा DB1200_PC1_EJECT_INT	(DB1200_INT_BEGIN + 11)
#घोषणा DB1200_SD0_INSERT_INT	(DB1200_INT_BEGIN + 12)
#घोषणा DB1200_SD0_EJECT_INT	(DB1200_INT_BEGIN + 13)
#घोषणा PB1200_SD1_INSERT_INT	(DB1200_INT_BEGIN + 14)
#घोषणा PB1200_SD1_EJECT_INT	(DB1200_INT_BEGIN + 15)
#घोषणा DB1200_INT_END		(DB1200_INT_BEGIN + 15)

स्थिर अक्षर *get_प्रणाली_type(व्योम);

अटल पूर्णांक __init db1200_detect_board(व्योम)
अणु
	पूर्णांक bid;

	/* try the DB1200 first */
	bcsr_init(DB1200_BCSR_PHYS_ADDR,
		  DB1200_BCSR_PHYS_ADDR + DB1200_BCSR_HEXLED_OFS);
	अगर (BCSR_WHOAMI_DB1200 == BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI))) अणु
		अचिन्हित लघु t = bcsr_पढ़ो(BCSR_HEXLEDS);
		bcsr_ग_लिखो(BCSR_HEXLEDS, ~t);
		अगर (bcsr_पढ़ो(BCSR_HEXLEDS) != t) अणु
			bcsr_ग_लिखो(BCSR_HEXLEDS, t);
			वापस 0;
		पूर्ण
	पूर्ण

	/* okay, try the PB1200 then */
	bcsr_init(PB1200_BCSR_PHYS_ADDR,
		  PB1200_BCSR_PHYS_ADDR + PB1200_BCSR_HEXLED_OFS);
	bid = BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI));
	अगर ((bid == BCSR_WHOAMI_PB1200_DDR1) ||
	    (bid == BCSR_WHOAMI_PB1200_DDR2)) अणु
		अचिन्हित लघु t = bcsr_पढ़ो(BCSR_HEXLEDS);
		bcsr_ग_लिखो(BCSR_HEXLEDS, ~t);
		अगर (bcsr_पढ़ो(BCSR_HEXLEDS) != t) अणु
			bcsr_ग_लिखो(BCSR_HEXLEDS, t);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;	/* it's neither */
पूर्ण

पूर्णांक __init db1200_board_setup(व्योम)
अणु
	अचिन्हित लघु whoami;

	अगर (db1200_detect_board())
		वापस -ENODEV;

	whoami = bcsr_पढ़ो(BCSR_WHOAMI);
	चयन (BCSR_WHOAMI_BOARD(whoami)) अणु
	हाल BCSR_WHOAMI_PB1200_DDR1:
	हाल BCSR_WHOAMI_PB1200_DDR2:
	हाल BCSR_WHOAMI_DB1200:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Alchemy/AMD/RMI %s Board, CPLD Rev %d"
		"  Board-ID %d	Daughtercard ID %d\n", get_प्रणाली_type(),
		(whoami >> 4) & 0xf, (whoami >> 8) & 0xf, whoami & 0xf);

	वापस 0;
पूर्ण

/******************************************************************************/

अटल u64 au1200_all_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा mtd_partition db1200_spअगरlash_parts[] = अणु
	अणु
		.name	= "spi_flash",
		.offset = 0,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data db1200_spअगरlash_data = अणु
	.name		= "s25fl001",
	.parts		= db1200_spअगरlash_parts,
	.nr_parts	= ARRAY_SIZE(db1200_spअगरlash_parts),
	.type		= "m25p10",
पूर्ण;

अटल काष्ठा spi_board_info db1200_spi_devs[] __initdata = अणु
	अणु
		/* TI TMP121AIDBVR temp sensor */
		.modalias	= "tmp121",
		.max_speed_hz	= 2000000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= 0,
	पूर्ण,
	अणु
		/* Spansion S25FL001D0FMA SPI flash */
		.modalias	= "m25p80",
		.max_speed_hz	= 50000000,
		.bus_num	= 0,
		.chip_select	= 1,
		.mode		= 0,
		.platक्रमm_data	= &db1200_spअगरlash_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info db1200_i2c_devs[] __initdata = अणु
	अणु I2C_BOARD_INFO("24c04", 0x52),  पूर्ण, /* AT24C04-10 I2C eeprom */
	अणु I2C_BOARD_INFO("ne1619", 0x2d), पूर्ण, /* adm1025-compat hwmon */
	अणु I2C_BOARD_INFO("wm8731", 0x1b), पूर्ण, /* I2S audio codec WM8731 */
पूर्ण;

/**********************************************************************/

अटल व्योम au1200_nand_cmd_ctrl(काष्ठा nand_chip *this, पूर्णांक cmd,
				 अचिन्हित पूर्णांक ctrl)
अणु
	अचिन्हित दीर्घ ioaddr = (अचिन्हित दीर्घ)this->legacy.IO_ADDR_W;

	ioaddr &= 0xffffff00;

	अगर (ctrl & न_अंकD_CLE) अणु
		ioaddr += MEM_STन_अंकD_CMD;
	पूर्ण अन्यथा अगर (ctrl & न_अंकD_ALE) अणु
		ioaddr += MEM_STन_अंकD_ADDR;
	पूर्ण अन्यथा अणु
		/* assume we want to r/w real data  by शेष */
		ioaddr += MEM_STन_अंकD_DATA;
	पूर्ण
	this->legacy.IO_ADDR_R = this->legacy.IO_ADDR_W = (व्योम __iomem *)ioaddr;
	अगर (cmd != न_अंकD_CMD_NONE) अणु
		__raw_ग_लिखोb(cmd, this->legacy.IO_ADDR_W);
		wmb();
	पूर्ण
पूर्ण

अटल पूर्णांक au1200_nand_device_पढ़ोy(काष्ठा nand_chip *this)
अणु
	वापस alchemy_rdsmem(AU1000_MEM_STSTAT) & 1;
पूर्ण

अटल काष्ठा mtd_partition db1200_nand_parts[] = अणु
	अणु
		.name	= "NAND FS 0",
		.offset = 0,
		.size	= 8 * 1024 * 1024,
	पूर्ण,
	अणु
		.name	= "NAND FS 1",
		.offset = MTDPART_OFS_APPEND,
		.size	= MTDPART_SIZ_FULL
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_nand_data db1200_nand_platdata = अणु
	.chip = अणु
		.nr_chips	= 1,
		.chip_offset	= 0,
		.nr_partitions	= ARRAY_SIZE(db1200_nand_parts),
		.partitions	= db1200_nand_parts,
		.chip_delay	= 20,
	पूर्ण,
	.ctrl = अणु
		.dev_पढ़ोy	= au1200_nand_device_पढ़ोy,
		.cmd_ctrl	= au1200_nand_cmd_ctrl,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource db1200_nand_res[] = अणु
	[0] = अणु
		.start	= DB1200_न_अंकD_PHYS_ADDR,
		.end	= DB1200_न_अंकD_PHYS_ADDR + 0xff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_nand_dev = अणु
	.name		= "gen_nand",
	.num_resources	= ARRAY_SIZE(db1200_nand_res),
	.resource	= db1200_nand_res,
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &db1200_nand_platdata,
	पूर्ण
पूर्ण;

/**********************************************************************/

अटल काष्ठा smc91x_platdata db1200_eth_data = अणु
	.flags	= SMC91X_NOWAIT | SMC91X_USE_16BIT,
	.leda	= RPC_LED_100_10,
	.ledb	= RPC_LED_TX_RX,
पूर्ण;

अटल काष्ठा resource db1200_eth_res[] = अणु
	[0] = अणु
		.start	= DB1200_ETH_PHYS_ADDR,
		.end	= DB1200_ETH_PHYS_ADDR + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= DB1200_ETH_INT,
		.end	= DB1200_ETH_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_eth_dev = अणु
	.dev	= अणु
		.platक्रमm_data	= &db1200_eth_data,
	पूर्ण,
	.name		= "smc91x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(db1200_eth_res),
	.resource	= db1200_eth_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा pata_platक्रमm_info db1200_ide_info = अणु
	.ioport_shअगरt	= DB1200_IDE_REG_SHIFT,
पूर्ण;

#घोषणा IDE_ALT_START	(14 << DB1200_IDE_REG_SHIFT)
अटल काष्ठा resource db1200_ide_res[] = अणु
	[0] = अणु
		.start	= DB1200_IDE_PHYS_ADDR,
		.end	= DB1200_IDE_PHYS_ADDR + IDE_ALT_START - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= DB1200_IDE_PHYS_ADDR + IDE_ALT_START,
		.end	= DB1200_IDE_PHYS_ADDR + DB1200_IDE_PHYS_LEN - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start	= DB1200_IDE_INT,
		.end	= DB1200_IDE_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_ide_dev = अणु
	.name		= "pata_platform",
	.id		= 0,
	.dev = अणु
		.dma_mask		= &au1200_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1200_ide_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(db1200_ide_res),
	.resource	= db1200_ide_res,
पूर्ण;

/**********************************************************************/

/* SD carddetects:  they're supposed to be edge-triggered, but ack
 * करोesn't seem to work (CPLD Rev 2).  Instead, the screaming one
 * is disabled and its counterpart enabled.  The 200ms समयout is
 * because the carddetect usually triggers twice, after debounce.
 */
अटल irqवापस_t db1200_mmc_cd(पूर्णांक irq, व्योम *ptr)
अणु
	disable_irq_nosync(irq);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t db1200_mmc_cdfn(पूर्णांक irq, व्योम *ptr)
अणु
	व्योम (*mmc_cd)(काष्ठा mmc_host *, अचिन्हित दीर्घ);

	/* link against CONFIG_MMC=m */
	mmc_cd = symbol_get(mmc_detect_change);
	अगर (mmc_cd) अणु
		mmc_cd(ptr, msecs_to_jअगरfies(200));
		symbol_put(mmc_detect_change);
	पूर्ण

	msleep(100);	/* debounce */
	अगर (irq == DB1200_SD0_INSERT_INT)
		enable_irq(DB1200_SD0_EJECT_INT);
	अन्यथा
		enable_irq(DB1200_SD0_INSERT_INT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक db1200_mmc_cd_setup(व्योम *mmc_host, पूर्णांक en)
अणु
	पूर्णांक ret;

	अगर (en) अणु
		ret = request_thपढ़ोed_irq(DB1200_SD0_INSERT_INT, db1200_mmc_cd,
				db1200_mmc_cdfn, 0, "sd_insert", mmc_host);
		अगर (ret)
			जाओ out;

		ret = request_thपढ़ोed_irq(DB1200_SD0_EJECT_INT, db1200_mmc_cd,
				db1200_mmc_cdfn, 0, "sd_eject", mmc_host);
		अगर (ret) अणु
			मुक्त_irq(DB1200_SD0_INSERT_INT, mmc_host);
			जाओ out;
		पूर्ण

		अगर (bcsr_पढ़ो(BCSR_SIGSTAT) & BCSR_INT_SD0INSERT)
			enable_irq(DB1200_SD0_EJECT_INT);
		अन्यथा
			enable_irq(DB1200_SD0_INSERT_INT);

	पूर्ण अन्यथा अणु
		मुक्त_irq(DB1200_SD0_INSERT_INT, mmc_host);
		मुक्त_irq(DB1200_SD0_EJECT_INT, mmc_host);
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल व्योम db1200_mmc_set_घातer(व्योम *mmc_host, पूर्णांक state)
अणु
	अगर (state) अणु
		bcsr_mod(BCSR_BOARD, 0, BCSR_BOARD_SD0PWR);
		msleep(400);	/* stabilization समय */
	पूर्ण अन्यथा
		bcsr_mod(BCSR_BOARD, BCSR_BOARD_SD0PWR, 0);
पूर्ण

अटल पूर्णांक db1200_mmc_card_पढ़ोonly(व्योम *mmc_host)
अणु
	वापस (bcsr_पढ़ो(BCSR_STATUS) & BCSR_STATUS_SD0WP) ? 1 : 0;
पूर्ण

अटल पूर्णांक db1200_mmc_card_inserted(व्योम *mmc_host)
अणु
	वापस (bcsr_पढ़ो(BCSR_SIGSTAT) & BCSR_INT_SD0INSERT) ? 1 : 0;
पूर्ण

अटल व्योम db1200_mmcled_set(काष्ठा led_classdev *led,
			      क्रमागत led_brightness brightness)
अणु
	अगर (brightness != LED_OFF)
		bcsr_mod(BCSR_LEDS, BCSR_LEDS_LED0, 0);
	अन्यथा
		bcsr_mod(BCSR_LEDS, 0, BCSR_LEDS_LED0);
पूर्ण

अटल काष्ठा led_classdev db1200_mmc_led = अणु
	.brightness_set = db1200_mmcled_set,
पूर्ण;

/* -- */

अटल irqवापस_t pb1200_mmc1_cd(पूर्णांक irq, व्योम *ptr)
अणु
	disable_irq_nosync(irq);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t pb1200_mmc1_cdfn(पूर्णांक irq, व्योम *ptr)
अणु
	व्योम (*mmc_cd)(काष्ठा mmc_host *, अचिन्हित दीर्घ);

	/* link against CONFIG_MMC=m */
	mmc_cd = symbol_get(mmc_detect_change);
	अगर (mmc_cd) अणु
		mmc_cd(ptr, msecs_to_jअगरfies(200));
		symbol_put(mmc_detect_change);
	पूर्ण

	msleep(100);	/* debounce */
	अगर (irq == PB1200_SD1_INSERT_INT)
		enable_irq(PB1200_SD1_EJECT_INT);
	अन्यथा
		enable_irq(PB1200_SD1_INSERT_INT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pb1200_mmc1_cd_setup(व्योम *mmc_host, पूर्णांक en)
अणु
	पूर्णांक ret;

	अगर (en) अणु
		ret = request_thपढ़ोed_irq(PB1200_SD1_INSERT_INT, pb1200_mmc1_cd,
				pb1200_mmc1_cdfn, 0, "sd1_insert", mmc_host);
		अगर (ret)
			जाओ out;

		ret = request_thपढ़ोed_irq(PB1200_SD1_EJECT_INT, pb1200_mmc1_cd,
				pb1200_mmc1_cdfn, 0, "sd1_eject", mmc_host);
		अगर (ret) अणु
			मुक्त_irq(PB1200_SD1_INSERT_INT, mmc_host);
			जाओ out;
		पूर्ण

		अगर (bcsr_पढ़ो(BCSR_SIGSTAT) & BCSR_INT_SD1INSERT)
			enable_irq(PB1200_SD1_EJECT_INT);
		अन्यथा
			enable_irq(PB1200_SD1_INSERT_INT);

	पूर्ण अन्यथा अणु
		मुक्त_irq(PB1200_SD1_INSERT_INT, mmc_host);
		मुक्त_irq(PB1200_SD1_EJECT_INT, mmc_host);
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल व्योम pb1200_mmc1led_set(काष्ठा led_classdev *led,
			क्रमागत led_brightness brightness)
अणु
	अगर (brightness != LED_OFF)
			bcsr_mod(BCSR_LEDS, BCSR_LEDS_LED1, 0);
	अन्यथा
			bcsr_mod(BCSR_LEDS, 0, BCSR_LEDS_LED1);
पूर्ण

अटल काष्ठा led_classdev pb1200_mmc1_led = अणु
	.brightness_set = pb1200_mmc1led_set,
पूर्ण;

अटल व्योम pb1200_mmc1_set_घातer(व्योम *mmc_host, पूर्णांक state)
अणु
	अगर (state) अणु
		bcsr_mod(BCSR_BOARD, 0, BCSR_BOARD_SD1PWR);
		msleep(400);	/* stabilization समय */
	पूर्ण अन्यथा
		bcsr_mod(BCSR_BOARD, BCSR_BOARD_SD1PWR, 0);
पूर्ण

अटल पूर्णांक pb1200_mmc1_card_पढ़ोonly(व्योम *mmc_host)
अणु
	वापस (bcsr_पढ़ो(BCSR_STATUS) & BCSR_STATUS_SD1WP) ? 1 : 0;
पूर्ण

अटल पूर्णांक pb1200_mmc1_card_inserted(व्योम *mmc_host)
अणु
	वापस (bcsr_पढ़ो(BCSR_SIGSTAT) & BCSR_INT_SD1INSERT) ? 1 : 0;
पूर्ण


अटल काष्ठा au1xmmc_platक्रमm_data db1200_mmc_platdata[2] = अणु
	[0] = अणु
		.cd_setup	= db1200_mmc_cd_setup,
		.set_घातer	= db1200_mmc_set_घातer,
		.card_inserted	= db1200_mmc_card_inserted,
		.card_पढ़ोonly	= db1200_mmc_card_पढ़ोonly,
		.led		= &db1200_mmc_led,
	पूर्ण,
	[1] = अणु
		.cd_setup	= pb1200_mmc1_cd_setup,
		.set_घातer	= pb1200_mmc1_set_घातer,
		.card_inserted	= pb1200_mmc1_card_inserted,
		.card_पढ़ोonly	= pb1200_mmc1_card_पढ़ोonly,
		.led		= &pb1200_mmc1_led,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource au1200_mmc0_resources[] = अणु
	[0] = अणु
		.start	= AU1100_SD0_PHYS_ADDR,
		.end	= AU1100_SD0_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1200_SD_INT,
		.end	= AU1200_SD_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1200_DSCR_CMD0_SDMS_TX0,
		.end	= AU1200_DSCR_CMD0_SDMS_TX0,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1200_DSCR_CMD0_SDMS_RX0,
		.end	= AU1200_DSCR_CMD0_SDMS_RX0,
		.flags	= IORESOURCE_DMA,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_mmc0_dev = अणु
	.name		= "au1xxx-mmc",
	.id		= 0,
	.dev = अणु
		.dma_mask		= &au1200_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1200_mmc_platdata[0],
	पूर्ण,
	.num_resources	= ARRAY_SIZE(au1200_mmc0_resources),
	.resource	= au1200_mmc0_resources,
पूर्ण;

अटल काष्ठा resource au1200_mmc1_res[] = अणु
	[0] = अणु
		.start	= AU1100_SD1_PHYS_ADDR,
		.end	= AU1100_SD1_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1200_SD_INT,
		.end	= AU1200_SD_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1200_DSCR_CMD0_SDMS_TX1,
		.end	= AU1200_DSCR_CMD0_SDMS_TX1,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1200_DSCR_CMD0_SDMS_RX1,
		.end	= AU1200_DSCR_CMD0_SDMS_RX1,
		.flags	= IORESOURCE_DMA,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device pb1200_mmc1_dev = अणु
	.name		= "au1xxx-mmc",
	.id		= 1,
	.dev = अणु
		.dma_mask		= &au1200_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1200_mmc_platdata[1],
	पूर्ण,
	.num_resources	= ARRAY_SIZE(au1200_mmc1_res),
	.resource	= au1200_mmc1_res,
पूर्ण;

/**********************************************************************/

अटल पूर्णांक db1200fb_panel_index(व्योम)
अणु
	वापस (bcsr_पढ़ो(BCSR_SWITCHES) >> 8) & 0x0f;
पूर्ण

अटल पूर्णांक db1200fb_panel_init(व्योम)
अणु
	/* Apply घातer */
	bcsr_mod(BCSR_BOARD, 0, BCSR_BOARD_LCDVEE | BCSR_BOARD_LCDVDD |
				BCSR_BOARD_LCDBL);
	वापस 0;
पूर्ण

अटल पूर्णांक db1200fb_panel_shutकरोwn(व्योम)
अणु
	/* Remove घातer */
	bcsr_mod(BCSR_BOARD, BCSR_BOARD_LCDVEE | BCSR_BOARD_LCDVDD |
			     BCSR_BOARD_LCDBL, 0);
	वापस 0;
पूर्ण

अटल काष्ठा au1200fb_platdata db1200fb_pd = अणु
	.panel_index	= db1200fb_panel_index,
	.panel_init	= db1200fb_panel_init,
	.panel_shutकरोwn = db1200fb_panel_shutकरोwn,
पूर्ण;

अटल काष्ठा resource au1200_lcd_res[] = अणु
	[0] = अणु
		.start	= AU1200_LCD_PHYS_ADDR,
		.end	= AU1200_LCD_PHYS_ADDR + 0x800 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1200_LCD_INT,
		.end	= AU1200_LCD_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device au1200_lcd_dev = अणु
	.name		= "au1200-lcd",
	.id		= 0,
	.dev = अणु
		.dma_mask		= &au1200_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1200fb_pd,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(au1200_lcd_res),
	.resource	= au1200_lcd_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा resource au1200_psc0_res[] = अणु
	[0] = अणु
		.start	= AU1550_PSC0_PHYS_ADDR,
		.end	= AU1550_PSC0_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1200_PSC0_INT,
		.end	= AU1200_PSC0_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1200_DSCR_CMD0_PSC0_TX,
		.end	= AU1200_DSCR_CMD0_PSC0_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1200_DSCR_CMD0_PSC0_RX,
		.end	= AU1200_DSCR_CMD0_PSC0_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_i2c_dev = अणु
	.name		= "au1xpsc_smbus",
	.id		= 0,	/* bus number */
	.num_resources	= ARRAY_SIZE(au1200_psc0_res),
	.resource	= au1200_psc0_res,
पूर्ण;

अटल व्योम db1200_spi_cs_en(काष्ठा au1550_spi_info *spi, पूर्णांक cs, पूर्णांक pol)
अणु
	अगर (cs)
		bcsr_mod(BCSR_RESETS, 0, BCSR_RESETS_SPISEL);
	अन्यथा
		bcsr_mod(BCSR_RESETS, BCSR_RESETS_SPISEL, 0);
पूर्ण

अटल काष्ठा au1550_spi_info db1200_spi_platdata = अणु
	.मुख्यclk_hz	= 50000000,	/* PSC0 घड़ी */
	.num_chipselect = 2,
	.activate_cs	= db1200_spi_cs_en,
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_spi_dev = अणु
	.dev	= अणु
		.dma_mask		= &au1200_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1200_spi_platdata,
	पूर्ण,
	.name		= "au1550-spi",
	.id		= 0,	/* bus number */
	.num_resources	= ARRAY_SIZE(au1200_psc0_res),
	.resource	= au1200_psc0_res,
पूर्ण;

अटल काष्ठा resource au1200_psc1_res[] = अणु
	[0] = अणु
		.start	= AU1550_PSC1_PHYS_ADDR,
		.end	= AU1550_PSC1_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1200_PSC1_INT,
		.end	= AU1200_PSC1_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1200_DSCR_CMD0_PSC1_TX,
		.end	= AU1200_DSCR_CMD0_PSC1_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1200_DSCR_CMD0_PSC1_RX,
		.end	= AU1200_DSCR_CMD0_PSC1_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

/* AC97 or I2S device */
अटल काष्ठा platक्रमm_device db1200_audio_dev = अणु
	/* name asचिन्हित later based on चयन setting */
	.id		= 1,	/* PSC ID */
	.num_resources	= ARRAY_SIZE(au1200_psc1_res),
	.resource	= au1200_psc1_res,
पूर्ण;

/* DB1200 ASoC card device */
अटल काष्ठा platक्रमm_device db1200_sound_dev = अणु
	/* name asचिन्हित later based on चयन setting */
	.id		= 1,	/* PSC ID */
	.dev = अणु
		.dma_mask		= &au1200_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_stac_dev = अणु
	.name		= "ac97-codec",
	.id		= 1,	/* on PSC1 */
पूर्ण;

अटल काष्ठा platक्रमm_device db1200_audiodma_dev = अणु
	.name		= "au1xpsc-pcm",
	.id		= 1,	/* PSC ID */
पूर्ण;

अटल काष्ठा platक्रमm_device *db1200_devs[] __initdata = अणु
	शून्य,		/* PSC0, selected by S6.8 */
	&db1200_ide_dev,
	&db1200_mmc0_dev,
	&au1200_lcd_dev,
	&db1200_eth_dev,
	&db1200_nand_dev,
	&db1200_audiodma_dev,
	&db1200_audio_dev,
	&db1200_stac_dev,
	&db1200_sound_dev,
पूर्ण;

अटल काष्ठा platक्रमm_device *pb1200_devs[] __initdata = अणु
	&pb1200_mmc1_dev,
पूर्ण;

/* Some peripheral base addresses dअगरfer on the PB1200 */
अटल पूर्णांक __init pb1200_res_fixup(व्योम)
अणु
	/* CPLD Revs earlier than 4 cause problems */
	अगर (BCSR_WHOAMI_CPLD(bcsr_पढ़ो(BCSR_WHOAMI)) <= 3) अणु
		prपूर्णांकk(KERN_ERR "WARNING!!!\n");
		prपूर्णांकk(KERN_ERR "WARNING!!!\n");
		prपूर्णांकk(KERN_ERR "PB1200 must be at CPLD rev 4. Please have\n");
		prपूर्णांकk(KERN_ERR "the board updated to latest revisions.\n");
		prपूर्णांकk(KERN_ERR "This software will not work reliably\n");
		prपूर्णांकk(KERN_ERR "on anything older than CPLD rev 4.!\n");
		prपूर्णांकk(KERN_ERR "WARNING!!!\n");
		prपूर्णांकk(KERN_ERR "WARNING!!!\n");
		वापस 1;
	पूर्ण

	db1200_nand_res[0].start = PB1200_न_अंकD_PHYS_ADDR;
	db1200_nand_res[0].end	 = PB1200_न_अंकD_PHYS_ADDR + 0xff;
	db1200_ide_res[0].start = PB1200_IDE_PHYS_ADDR;
	db1200_ide_res[0].end	= PB1200_IDE_PHYS_ADDR + DB1200_IDE_PHYS_LEN - 1;
	db1200_eth_res[0].start = PB1200_ETH_PHYS_ADDR;
	db1200_eth_res[0].end	= PB1200_ETH_PHYS_ADDR + 0xff;
	वापस 0;
पूर्ण

पूर्णांक __init db1200_dev_setup(व्योम)
अणु
	अचिन्हित दीर्घ pfc;
	अचिन्हित लघु sw;
	पूर्णांक swapped, bid;
	काष्ठा clk *c;

	bid = BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI));
	अगर ((bid == BCSR_WHOAMI_PB1200_DDR1) ||
	    (bid == BCSR_WHOAMI_PB1200_DDR2)) अणु
		अगर (pb1200_res_fixup())
			वापस -ENODEV;
	पूर्ण

	/* GPIO7 is low-level triggered CPLD cascade */
	irq_set_irq_type(AU1200_GPIO7_INT, IRQ_TYPE_LEVEL_LOW);
	bcsr_init_irq(DB1200_INT_BEGIN, DB1200_INT_END, AU1200_GPIO7_INT);

	/* SMBus/SPI on PSC0, Audio on PSC1 */
	pfc = alchemy_rdsys(AU1000_SYS_PINFUNC);
	pfc &= ~(SYS_PINFUNC_P0A | SYS_PINFUNC_P0B);
	pfc &= ~(SYS_PINFUNC_P1A | SYS_PINFUNC_P1B | SYS_PINFUNC_FS3);
	pfc |= SYS_PINFUNC_P1C; /* SPI is configured later */
	alchemy_wrsys(pfc, AU1000_SYS_PINFUNC);

	/* get 50MHz क्रम I2C driver on PSC0 */
	c = clk_get(शून्य, "psc0_intclk");
	अगर (!IS_ERR(c)) अणु
		pfc = clk_round_rate(c, 50000000);
		अगर ((pfc < 1) || (असल(50000000 - pfc) > 2500000))
			pr_warn("DB1200: cant get I2C close to 50MHz\n");
		अन्यथा
			clk_set_rate(c, pfc);
		clk_prepare_enable(c);
		clk_put(c);
	पूर्ण

	/* insert/eject pairs: one of both is always screaming.	 To aव्योम
	 * issues they must not be स्वतःmatically enabled when initially
	 * requested.
	 */
	irq_set_status_flags(DB1200_SD0_INSERT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1200_SD0_EJECT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1200_PC0_INSERT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1200_PC0_EJECT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1200_PC1_INSERT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1200_PC1_EJECT_INT, IRQ_NOAUTOEN);

	i2c_रेजिस्टर_board_info(0, db1200_i2c_devs,
				ARRAY_SIZE(db1200_i2c_devs));
	spi_रेजिस्टर_board_info(db1200_spi_devs,
				ARRAY_SIZE(db1200_i2c_devs));

	/* SWITCHES:	S6.8 I2C/SPI selector  (OFF=I2C	 ON=SPI)
	 *		S6.7 AC97/I2S selector (OFF=AC97 ON=I2S)
	 *		or S12 on the PB1200.
	 */

	/* NOTE: GPIO215 controls OTG VBUS supply.  In SPI mode however
	 * this pin is claimed by PSC0 (unused though, but pinmux करोesn't
	 * allow to मुक्त it without crippling the SPI पूर्णांकerface).
	 * As a result, in SPI mode, OTG simply won't work (PSC0 uses
	 * it as an input pin which is pulled high on the boards).
	 */
	pfc = alchemy_rdsys(AU1000_SYS_PINFUNC) & ~SYS_PINFUNC_P0A;

	/* चयन off OTG VBUS supply */
	gpio_request(215, "otg-vbus");
	gpio_direction_output(215, 1);

	prपूर्णांकk(KERN_INFO "%s device configuration:\n", get_प्रणाली_type());

	sw = bcsr_पढ़ो(BCSR_SWITCHES);
	अगर (sw & BCSR_SWITCHES_DIP_8) अणु
		db1200_devs[0] = &db1200_i2c_dev;
		bcsr_mod(BCSR_RESETS, BCSR_RESETS_PSC0MUX, 0);

		pfc |= (2 << 17);	/* GPIO2 block owns GPIO215 */

		prपूर्णांकk(KERN_INFO " S6.8 OFF: PSC0 mode I2C\n");
		prपूर्णांकk(KERN_INFO "   OTG port VBUS supply available!\n");
	पूर्ण अन्यथा अणु
		db1200_devs[0] = &db1200_spi_dev;
		bcsr_mod(BCSR_RESETS, 0, BCSR_RESETS_PSC0MUX);

		pfc |= (1 << 17);	/* PSC0 owns GPIO215 */

		prपूर्णांकk(KERN_INFO " S6.8 ON : PSC0 mode SPI\n");
		prपूर्णांकk(KERN_INFO "   OTG port VBUS supply disabled\n");
	पूर्ण
	alchemy_wrsys(pfc, AU1000_SYS_PINFUNC);

	/* Audio: DIP7 selects I2S(0)/AC97(1), but need I2C क्रम I2S!
	 * so: DIP7=1 || DIP8=0 => AC97, DIP7=0 && DIP8=1 => I2S
	 */
	sw &= BCSR_SWITCHES_DIP_8 | BCSR_SWITCHES_DIP_7;
	अगर (sw == BCSR_SWITCHES_DIP_8) अणु
		bcsr_mod(BCSR_RESETS, 0, BCSR_RESETS_PSC1MUX);
		db1200_audio_dev.name = "au1xpsc_i2s";
		db1200_sound_dev.name = "db1200-i2s";
		prपूर्णांकk(KERN_INFO " S6.7 ON : PSC1 mode I2S\n");
	पूर्ण अन्यथा अणु
		bcsr_mod(BCSR_RESETS, BCSR_RESETS_PSC1MUX, 0);
		db1200_audio_dev.name = "au1xpsc_ac97";
		db1200_sound_dev.name = "db1200-ac97";
		prपूर्णांकk(KERN_INFO " S6.7 OFF: PSC1 mode AC97\n");
	पूर्ण

	/* Audio PSC घड़ी is supplied बाह्यally. (FIXME: platdata!!) */
	__raw_ग_लिखोl(PSC_SEL_CLK_SERCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1550_PSC1_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();

	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x000400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x000400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x000010000 - 1,
		DB1200_PC0_INT, DB1200_PC0_INSERT_INT,
		/*DB1200_PC0_STSCHG_INT*/0, DB1200_PC0_EJECT_INT, 0);

	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x004000000,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x004400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x004000000,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x004400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x004000000,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x004010000 - 1,
		DB1200_PC1_INT, DB1200_PC1_INSERT_INT,
		/*DB1200_PC1_STSCHG_INT*/0, DB1200_PC1_EJECT_INT, 1);

	swapped = bcsr_पढ़ो(BCSR_STATUS) & BCSR_STATUS_DB1200_SWAPBOOT;
	db1x_रेजिस्टर_norflash(64 << 20, 2, swapped);

	platक्रमm_add_devices(db1200_devs, ARRAY_SIZE(db1200_devs));

	/* PB1200 is a DB1200 with a 2nd MMC and Camera connector */
	अगर ((bid == BCSR_WHOAMI_PB1200_DDR1) ||
	    (bid == BCSR_WHOAMI_PB1200_DDR2))
		platक्रमm_add_devices(pb1200_devs, ARRAY_SIZE(pb1200_devs));

	वापस 0;
पूर्ण
