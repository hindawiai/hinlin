<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DBAu1300 init and platक्रमm device setup.
 *
 * (c) 2009 Manuel Lauss <manuel.lauss@googlemail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>	/* KEY_* codes */
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/wm97xx.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1300.h>
#समावेश <यंत्र/mach-au1x00/au1100_mmc.h>
#समावेश <यंत्र/mach-au1x00/au1200fb.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>
#समावेश <यंत्र/mach-au1x00/prom.h>

#समावेश "platform.h"

/* FPGA (बाह्यal mux) पूर्णांकerrupt sources */
#घोषणा DB1300_FIRST_INT	(ALCHEMY_GPIC_INT_LAST + 1)
#घोषणा DB1300_IDE_INT		(DB1300_FIRST_INT + 0)
#घोषणा DB1300_ETH_INT		(DB1300_FIRST_INT + 1)
#घोषणा DB1300_CF_INT		(DB1300_FIRST_INT + 2)
#घोषणा DB1300_VIDEO_INT	(DB1300_FIRST_INT + 4)
#घोषणा DB1300_HDMI_INT		(DB1300_FIRST_INT + 5)
#घोषणा DB1300_DC_INT		(DB1300_FIRST_INT + 6)
#घोषणा DB1300_FLASH_INT	(DB1300_FIRST_INT + 7)
#घोषणा DB1300_CF_INSERT_INT	(DB1300_FIRST_INT + 8)
#घोषणा DB1300_CF_EJECT_INT	(DB1300_FIRST_INT + 9)
#घोषणा DB1300_AC97_INT		(DB1300_FIRST_INT + 10)
#घोषणा DB1300_AC97_PEN_INT	(DB1300_FIRST_INT + 11)
#घोषणा DB1300_SD1_INSERT_INT	(DB1300_FIRST_INT + 12)
#घोषणा DB1300_SD1_EJECT_INT	(DB1300_FIRST_INT + 13)
#घोषणा DB1300_OTG_VBUS_OC_INT	(DB1300_FIRST_INT + 14)
#घोषणा DB1300_HOST_VBUS_OC_INT (DB1300_FIRST_INT + 15)
#घोषणा DB1300_LAST_INT		(DB1300_FIRST_INT + 15)

/* SMSC9210 CS */
#घोषणा DB1300_ETH_PHYS_ADDR	0x19000000
#घोषणा DB1300_ETH_PHYS_END	0x197fffff

/* ATA CS */
#घोषणा DB1300_IDE_PHYS_ADDR	0x18800000
#घोषणा DB1300_IDE_REG_SHIFT	5
#घोषणा DB1300_IDE_PHYS_LEN	(16 << DB1300_IDE_REG_SHIFT)

/* न_अंकD CS */
#घोषणा DB1300_न_अंकD_PHYS_ADDR	0x20000000
#घोषणा DB1300_न_अंकD_PHYS_END	0x20000fff


अटल काष्ठा i2c_board_info db1300_i2c_devs[] __initdata = अणु
	अणु I2C_BOARD_INFO("wm8731", 0x1b), पूर्ण,	/* I2S audio codec */
	अणु I2C_BOARD_INFO("ne1619", 0x2d), पूर्ण,	/* adm1025-compat hwmon */
पूर्ण;

/* multअगरunction pins to assign to GPIO controller */
अटल पूर्णांक db1300_gpio_pins[] __initdata = अणु
	AU1300_PIN_LCDPWM0, AU1300_PIN_PSC2SYNC1, AU1300_PIN_WAKE1,
	AU1300_PIN_WAKE2, AU1300_PIN_WAKE3, AU1300_PIN_FG3AUX,
	AU1300_PIN_EXTCLK1,
	-1,	/* terminator */
पूर्ण;

/* multअगरunction pins to assign to device functions */
अटल पूर्णांक db1300_dev_pins[] __initdata = अणु
	/* wake-from-str pins 0-3 */
	AU1300_PIN_WAKE0,
	/* बाह्यal घड़ी sources क्रम PSC0 */
	AU1300_PIN_EXTCLK0,
	/* 8bit MMC पूर्णांकerface on SD0: 6-9 */
	AU1300_PIN_SD0DAT4, AU1300_PIN_SD0DAT5, AU1300_PIN_SD0DAT6,
	AU1300_PIN_SD0DAT7,
	/* UART1 pins: 11-18 */
	AU1300_PIN_U1RI, AU1300_PIN_U1DCD, AU1300_PIN_U1DSR,
	AU1300_PIN_U1CTS, AU1300_PIN_U1RTS, AU1300_PIN_U1DTR,
	AU1300_PIN_U1RX, AU1300_PIN_U1TX,
	/* UART0 pins: 19-24 */
	AU1300_PIN_U0RI, AU1300_PIN_U0DCD, AU1300_PIN_U0DSR,
	AU1300_PIN_U0CTS, AU1300_PIN_U0RTS, AU1300_PIN_U0DTR,
	/* UART2: 25-26 */
	AU1300_PIN_U2RX, AU1300_PIN_U2TX,
	/* UART3: 27-28 */
	AU1300_PIN_U3RX, AU1300_PIN_U3TX,
	/* LCD controller PWMs, ext pixघड़ी: 30-31 */
	AU1300_PIN_LCDPWM1, AU1300_PIN_LCDCLKIN,
	/* SD1 पूर्णांकerface: 32-37 */
	AU1300_PIN_SD1DAT0, AU1300_PIN_SD1DAT1, AU1300_PIN_SD1DAT2,
	AU1300_PIN_SD1DAT3, AU1300_PIN_SD1CMD, AU1300_PIN_SD1CLK,
	/* SD2 पूर्णांकerface: 38-43 */
	AU1300_PIN_SD2DAT0, AU1300_PIN_SD2DAT1, AU1300_PIN_SD2DAT2,
	AU1300_PIN_SD2DAT3, AU1300_PIN_SD2CMD, AU1300_PIN_SD2CLK,
	/* PSC0/1 घड़ीs: 44-45 */
	AU1300_PIN_PSC0CLK, AU1300_PIN_PSC1CLK,
	/* PSCs: 46-49/50-53/54-57/58-61 */
	AU1300_PIN_PSC0SYNC0, AU1300_PIN_PSC0SYNC1, AU1300_PIN_PSC0D0,
	AU1300_PIN_PSC0D1,
	AU1300_PIN_PSC1SYNC0, AU1300_PIN_PSC1SYNC1, AU1300_PIN_PSC1D0,
	AU1300_PIN_PSC1D1,
	AU1300_PIN_PSC2SYNC0,			    AU1300_PIN_PSC2D0,
	AU1300_PIN_PSC2D1,
	AU1300_PIN_PSC3SYNC0, AU1300_PIN_PSC3SYNC1, AU1300_PIN_PSC3D0,
	AU1300_PIN_PSC3D1,
	/* PCMCIA पूर्णांकerface: 62-70 */
	AU1300_PIN_PCE2, AU1300_PIN_PCE1, AU1300_PIN_PIOS16,
	AU1300_PIN_PIOR, AU1300_PIN_PWE, AU1300_PIN_PWAIT,
	AU1300_PIN_PREG, AU1300_PIN_POE, AU1300_PIN_PIOW,
	/* camera पूर्णांकerface H/V sync inमाला_दो: 71-72 */
	AU1300_PIN_CIMLS, AU1300_PIN_CIMFS,
	/* PSC2/3 घड़ीs: 73-74 */
	AU1300_PIN_PSC2CLK, AU1300_PIN_PSC3CLK,
	-1,	/* terminator */
पूर्ण;

अटल व्योम __init db1300_gpio_config(व्योम)
अणु
	पूर्णांक *i;

	i = &db1300_dev_pins[0];
	जबतक (*i != -1)
		au1300_pinfunc_to_dev(*i++);

	i = &db1300_gpio_pins[0];
	जबतक (*i != -1)
		au1300_gpio_direction_input(*i++);/* implies pin_to_gpio */

	au1300_set_dbdma_gpio(1, AU1300_PIN_FG3AUX);
पूर्ण

/**********************************************************************/

अटल u64 au1300_all_dmamask = DMA_BIT_MASK(32);

अटल व्योम au1300_nand_cmd_ctrl(काष्ठा nand_chip *this, पूर्णांक cmd,
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

अटल पूर्णांक au1300_nand_device_पढ़ोy(काष्ठा nand_chip *this)
अणु
	वापस alchemy_rdsmem(AU1000_MEM_STSTAT) & 1;
पूर्ण

अटल काष्ठा mtd_partition db1300_nand_parts[] = अणु
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

काष्ठा platक्रमm_nand_data db1300_nand_platdata = अणु
	.chip = अणु
		.nr_chips	= 1,
		.chip_offset	= 0,
		.nr_partitions	= ARRAY_SIZE(db1300_nand_parts),
		.partitions	= db1300_nand_parts,
		.chip_delay	= 20,
	पूर्ण,
	.ctrl = अणु
		.dev_पढ़ोy	= au1300_nand_device_पढ़ोy,
		.cmd_ctrl	= au1300_nand_cmd_ctrl,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource db1300_nand_res[] = अणु
	[0] = अणु
		.start	= DB1300_न_अंकD_PHYS_ADDR,
		.end	= DB1300_न_अंकD_PHYS_ADDR + 0xff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_nand_dev = अणु
	.name		= "gen_nand",
	.num_resources	= ARRAY_SIZE(db1300_nand_res),
	.resource	= db1300_nand_res,
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &db1300_nand_platdata,
	पूर्ण
पूर्ण;

/**********************************************************************/

अटल काष्ठा resource db1300_eth_res[] = अणु
	[0] = अणु
		.start		= DB1300_ETH_PHYS_ADDR,
		.end		= DB1300_ETH_PHYS_END,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start		= DB1300_ETH_INT,
		.end		= DB1300_ETH_INT,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा smsc911x_platक्रमm_config db1300_eth_config = अणु
	.phy_पूर्णांकerface		= PHY_INTERFACE_MODE_MII,
	.irq_polarity		= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type		= SMSC911X_IRQ_TYPE_PUSH_PULL,
	.flags			= SMSC911X_USE_32BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_eth_dev = अणु
	.name			= "smsc911x",
	.id			= -1,
	.num_resources		= ARRAY_SIZE(db1300_eth_res),
	.resource		= db1300_eth_res,
	.dev = अणु
		.platक्रमm_data	= &db1300_eth_config,
	पूर्ण,
पूर्ण;

/**********************************************************************/

अटल काष्ठा resource au1300_psc1_res[] = अणु
	[0] = अणु
		.start	= AU1300_PSC1_PHYS_ADDR,
		.end	= AU1300_PSC1_PHYS_ADDR + 0x0fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1300_PSC1_INT,
		.end	= AU1300_PSC1_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1300_DSCR_CMD0_PSC1_TX,
		.end	= AU1300_DSCR_CMD0_PSC1_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1300_DSCR_CMD0_PSC1_RX,
		.end	= AU1300_DSCR_CMD0_PSC1_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_ac97_dev = अणु
	.name		= "au1xpsc_ac97",
	.id		= 1,	/* PSC ID. match with AC97 codec ID! */
	.num_resources	= ARRAY_SIZE(au1300_psc1_res),
	.resource	= au1300_psc1_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा resource au1300_psc2_res[] = अणु
	[0] = अणु
		.start	= AU1300_PSC2_PHYS_ADDR,
		.end	= AU1300_PSC2_PHYS_ADDR + 0x0fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1300_PSC2_INT,
		.end	= AU1300_PSC2_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1300_DSCR_CMD0_PSC2_TX,
		.end	= AU1300_DSCR_CMD0_PSC2_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1300_DSCR_CMD0_PSC2_RX,
		.end	= AU1300_DSCR_CMD0_PSC2_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_i2s_dev = अणु
	.name		= "au1xpsc_i2s",
	.id		= 2,	/* PSC ID */
	.num_resources	= ARRAY_SIZE(au1300_psc2_res),
	.resource	= au1300_psc2_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा resource au1300_psc3_res[] = अणु
	[0] = अणु
		.start	= AU1300_PSC3_PHYS_ADDR,
		.end	= AU1300_PSC3_PHYS_ADDR + 0x0fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1300_PSC3_INT,
		.end	= AU1300_PSC3_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1300_DSCR_CMD0_PSC3_TX,
		.end	= AU1300_DSCR_CMD0_PSC3_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1300_DSCR_CMD0_PSC3_RX,
		.end	= AU1300_DSCR_CMD0_PSC3_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_i2c_dev = अणु
	.name		= "au1xpsc_smbus",
	.id		= 0,	/* bus number */
	.num_resources	= ARRAY_SIZE(au1300_psc3_res),
	.resource	= au1300_psc3_res,
पूर्ण;

/**********************************************************************/

/* proper key assignments when facing the LCD panel.  For key assignments
 * according to the schematics swap up with करोwn and left with right.
 * I chose to use it to emulate the arrow keys of a keyboard.
 */
अटल काष्ठा gpio_keys_button db1300_5waysw_arrowkeys[] = अणु
	अणु
		.code			= KEY_DOWN,
		.gpio			= AU1300_PIN_LCDPWM0,
		.type			= EV_KEY,
		.debounce_पूर्णांकerval	= 1,
		.active_low		= 1,
		.desc			= "5waysw-down",
	पूर्ण,
	अणु
		.code			= KEY_UP,
		.gpio			= AU1300_PIN_PSC2SYNC1,
		.type			= EV_KEY,
		.debounce_पूर्णांकerval	= 1,
		.active_low		= 1,
		.desc			= "5waysw-up",
	पूर्ण,
	अणु
		.code			= KEY_RIGHT,
		.gpio			= AU1300_PIN_WAKE3,
		.type			= EV_KEY,
		.debounce_पूर्णांकerval	= 1,
		.active_low		= 1,
		.desc			= "5waysw-right",
	पूर्ण,
	अणु
		.code			= KEY_LEFT,
		.gpio			= AU1300_PIN_WAKE2,
		.type			= EV_KEY,
		.debounce_पूर्णांकerval	= 1,
		.active_low		= 1,
		.desc			= "5waysw-left",
	पूर्ण,
	अणु
		.code			= KEY_ENTER,
		.gpio			= AU1300_PIN_WAKE1,
		.type			= EV_KEY,
		.debounce_पूर्णांकerval	= 1,
		.active_low		= 1,
		.desc			= "5waysw-push",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data db1300_5waysw_data = अणु
	.buttons	= db1300_5waysw_arrowkeys,
	.nbuttons	= ARRAY_SIZE(db1300_5waysw_arrowkeys),
	.rep		= 1,
	.name		= "db1300-5wayswitch",
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_5waysw_dev = अणु
	.name		= "gpio-keys",
	.dev	= अणु
		.platक्रमm_data	= &db1300_5waysw_data,
	पूर्ण,
पूर्ण;

/**********************************************************************/

अटल काष्ठा pata_platक्रमm_info db1300_ide_info = अणु
	.ioport_shअगरt	= DB1300_IDE_REG_SHIFT,
पूर्ण;

#घोषणा IDE_ALT_START	(14 << DB1300_IDE_REG_SHIFT)
अटल काष्ठा resource db1300_ide_res[] = अणु
	[0] = अणु
		.start	= DB1300_IDE_PHYS_ADDR,
		.end	= DB1300_IDE_PHYS_ADDR + IDE_ALT_START - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= DB1300_IDE_PHYS_ADDR + IDE_ALT_START,
		.end	= DB1300_IDE_PHYS_ADDR + DB1300_IDE_PHYS_LEN - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start	= DB1300_IDE_INT,
		.end	= DB1300_IDE_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_ide_dev = अणु
	.dev	= अणु
		.dma_mask		= &au1300_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data	= &db1300_ide_info,
	पूर्ण,
	.name		= "pata_platform",
	.resource	= db1300_ide_res,
	.num_resources	= ARRAY_SIZE(db1300_ide_res),
पूर्ण;

/**********************************************************************/

अटल irqवापस_t db1300_mmc_cd(पूर्णांक irq, व्योम *ptr)
अणु
	disable_irq_nosync(irq);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t db1300_mmc_cdfn(पूर्णांक irq, व्योम *ptr)
अणु
	व्योम (*mmc_cd)(काष्ठा mmc_host *, अचिन्हित दीर्घ);

	/* link against CONFIG_MMC=m.  We can only be called once MMC core has
	 * initialized the controller, so symbol_get() should always succeed.
	 */
	mmc_cd = symbol_get(mmc_detect_change);
	mmc_cd(ptr, msecs_to_jअगरfies(200));
	symbol_put(mmc_detect_change);

	msleep(100);	/* debounce */
	अगर (irq == DB1300_SD1_INSERT_INT)
		enable_irq(DB1300_SD1_EJECT_INT);
	अन्यथा
		enable_irq(DB1300_SD1_INSERT_INT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक db1300_mmc_card_पढ़ोonly(व्योम *mmc_host)
अणु
	/* it uses SD1 पूर्णांकerface, but the DB1200's SD0 bit in the CPLD */
	वापस bcsr_पढ़ो(BCSR_STATUS) & BCSR_STATUS_SD0WP;
पूर्ण

अटल पूर्णांक db1300_mmc_card_inserted(व्योम *mmc_host)
अणु
	वापस bcsr_पढ़ो(BCSR_SIGSTAT) & (1 << 12); /* insertion irq संकेत */
पूर्ण

अटल पूर्णांक db1300_mmc_cd_setup(व्योम *mmc_host, पूर्णांक en)
अणु
	पूर्णांक ret;

	अगर (en) अणु
		ret = request_thपढ़ोed_irq(DB1300_SD1_INSERT_INT, db1300_mmc_cd,
				db1300_mmc_cdfn, 0, "sd_insert", mmc_host);
		अगर (ret)
			जाओ out;

		ret = request_thपढ़ोed_irq(DB1300_SD1_EJECT_INT, db1300_mmc_cd,
				db1300_mmc_cdfn, 0, "sd_eject", mmc_host);
		अगर (ret) अणु
			मुक्त_irq(DB1300_SD1_INSERT_INT, mmc_host);
			जाओ out;
		पूर्ण

		अगर (db1300_mmc_card_inserted(mmc_host))
			enable_irq(DB1300_SD1_EJECT_INT);
		अन्यथा
			enable_irq(DB1300_SD1_INSERT_INT);

	पूर्ण अन्यथा अणु
		मुक्त_irq(DB1300_SD1_INSERT_INT, mmc_host);
		मुक्त_irq(DB1300_SD1_EJECT_INT, mmc_host);
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल व्योम db1300_mmcled_set(काष्ठा led_classdev *led,
			      क्रमागत led_brightness brightness)
अणु
	अगर (brightness != LED_OFF)
		bcsr_mod(BCSR_LEDS, BCSR_LEDS_LED0, 0);
	अन्यथा
		bcsr_mod(BCSR_LEDS, 0, BCSR_LEDS_LED0);
पूर्ण

अटल काष्ठा led_classdev db1300_mmc_led = अणु
	.brightness_set = db1300_mmcled_set,
पूर्ण;

काष्ठा au1xmmc_platक्रमm_data db1300_sd1_platdata = अणु
	.cd_setup	= db1300_mmc_cd_setup,
	.card_inserted	= db1300_mmc_card_inserted,
	.card_पढ़ोonly	= db1300_mmc_card_पढ़ोonly,
	.led		= &db1300_mmc_led,
पूर्ण;

अटल काष्ठा resource au1300_sd1_res[] = अणु
	[0] = अणु
		.start	= AU1300_SD1_PHYS_ADDR,
		.end	= AU1300_SD1_PHYS_ADDR,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1300_SD1_INT,
		.end	= AU1300_SD1_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1300_DSCR_CMD0_SDMS_TX1,
		.end	= AU1300_DSCR_CMD0_SDMS_TX1,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1300_DSCR_CMD0_SDMS_RX1,
		.end	= AU1300_DSCR_CMD0_SDMS_RX1,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_sd1_dev = अणु
	.dev = अणु
		.dma_mask		= &au1300_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1300_sd1_platdata,
	पूर्ण,
	.name		= "au1xxx-mmc",
	.id		= 1,
	.resource	= au1300_sd1_res,
	.num_resources	= ARRAY_SIZE(au1300_sd1_res),
पूर्ण;

/**********************************************************************/

अटल पूर्णांक db1300_movinand_inserted(व्योम *mmc_host)
अणु
	वापस 0; /* disable क्रम now, it करोesn't work yet */
पूर्ण

अटल पूर्णांक db1300_movinand_पढ़ोonly(व्योम *mmc_host)
अणु
	वापस 0;
पूर्ण

अटल व्योम db1300_movinand_led_set(काष्ठा led_classdev *led,
				    क्रमागत led_brightness brightness)
अणु
	अगर (brightness != LED_OFF)
		bcsr_mod(BCSR_LEDS, BCSR_LEDS_LED1, 0);
	अन्यथा
		bcsr_mod(BCSR_LEDS, 0, BCSR_LEDS_LED1);
पूर्ण

अटल काष्ठा led_classdev db1300_movinand_led = अणु
	.brightness_set		= db1300_movinand_led_set,
पूर्ण;

काष्ठा au1xmmc_platक्रमm_data db1300_sd0_platdata = अणु
	.card_inserted		= db1300_movinand_inserted,
	.card_पढ़ोonly		= db1300_movinand_पढ़ोonly,
	.led			= &db1300_movinand_led,
	.mask_host_caps		= MMC_CAP_NEEDS_POLL,
पूर्ण;

अटल काष्ठा resource au1300_sd0_res[] = अणु
	[0] = अणु
		.start	= AU1100_SD0_PHYS_ADDR,
		.end	= AU1100_SD0_PHYS_ADDR,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1300_SD0_INT,
		.end	= AU1300_SD0_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1300_DSCR_CMD0_SDMS_TX0,
		.end	= AU1300_DSCR_CMD0_SDMS_TX0,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1300_DSCR_CMD0_SDMS_RX0,
		.end	= AU1300_DSCR_CMD0_SDMS_RX0,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_sd0_dev = अणु
	.dev = अणु
		.dma_mask		= &au1300_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1300_sd0_platdata,
	पूर्ण,
	.name		= "au1xxx-mmc",
	.id		= 0,
	.resource	= au1300_sd0_res,
	.num_resources	= ARRAY_SIZE(au1300_sd0_res),
पूर्ण;

/**********************************************************************/

अटल काष्ठा platक्रमm_device db1300_wm9715_dev = अणु
	.name		= "wm9712-codec",
	.id		= 1,	/* ID of PSC क्रम AC97 audio, see asoc glue! */
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_ac97dma_dev = अणु
	.name		= "au1xpsc-pcm",
	.id		= 1,	/* PSC ID */
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_i2sdma_dev = अणु
	.name		= "au1xpsc-pcm",
	.id		= 2,	/* PSC ID */
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_sndac97_dev = अणु
	.name		= "db1300-ac97",
	.dev = अणु
		.dma_mask		= &au1300_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1300_sndi2s_dev = अणु
	.name		= "db1300-i2s",
	.dev = अणु
		.dma_mask		= &au1300_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

/**********************************************************************/

अटल पूर्णांक db1300fb_panel_index(व्योम)
अणु
	वापस 9;	/* DB1300_800x480 */
पूर्ण

अटल पूर्णांक db1300fb_panel_init(व्योम)
अणु
	/* Apply घातer (Vee/Vdd logic is inverted on Panel DB1300_800x480) */
	bcsr_mod(BCSR_BOARD, BCSR_BOARD_LCDVEE | BCSR_BOARD_LCDVDD,
			     BCSR_BOARD_LCDBL);
	वापस 0;
पूर्ण

अटल पूर्णांक db1300fb_panel_shutकरोwn(व्योम)
अणु
	/* Remove घातer (Vee/Vdd logic is inverted on Panel DB1300_800x480) */
	bcsr_mod(BCSR_BOARD, BCSR_BOARD_LCDBL,
			     BCSR_BOARD_LCDVEE | BCSR_BOARD_LCDVDD);
	वापस 0;
पूर्ण

अटल काष्ठा au1200fb_platdata db1300fb_pd = अणु
	.panel_index	= db1300fb_panel_index,
	.panel_init	= db1300fb_panel_init,
	.panel_shutकरोwn = db1300fb_panel_shutकरोwn,
पूर्ण;

अटल काष्ठा resource au1300_lcd_res[] = अणु
	[0] = अणु
		.start	= AU1200_LCD_PHYS_ADDR,
		.end	= AU1200_LCD_PHYS_ADDR + 0x800 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1300_LCD_INT,
		.end	= AU1300_LCD_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;


अटल काष्ठा platक्रमm_device db1300_lcd_dev = अणु
	.name		= "au1200-lcd",
	.id		= 0,
	.dev = अणु
		.dma_mask		= &au1300_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1300fb_pd,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(au1300_lcd_res),
	.resource	= au1300_lcd_res,
पूर्ण;

/**********************************************************************/

#अगर IS_ENABLED(CONFIG_TOUCHSCREEN_WM97XX)
अटल व्योम db1300_wm97xx_irqen(काष्ठा wm97xx *wm, पूर्णांक enable)
अणु
	अगर (enable)
		enable_irq(DB1300_AC97_PEN_INT);
	अन्यथा
		disable_irq_nosync(DB1300_AC97_PEN_INT);
पूर्ण

अटल काष्ठा wm97xx_mach_ops db1300_wm97xx_ops = अणु
	.irq_enable	= db1300_wm97xx_irqen,
	.irq_gpio	= WM97XX_GPIO_3,
पूर्ण;

अटल पूर्णांक db1300_wm97xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm97xx *wm = platक्रमm_get_drvdata(pdev);

	/* बाह्यal penकरोwn indicator */
	wm97xx_config_gpio(wm, WM97XX_GPIO_13, WM97XX_GPIO_IN,
			   WM97XX_GPIO_POL_LOW, WM97XX_GPIO_STICKY,
			   WM97XX_GPIO_WAKE);

	/* पूर्णांकernal "virtual" penकरोwn gpio */
	wm97xx_config_gpio(wm, WM97XX_GPIO_3, WM97XX_GPIO_OUT,
			   WM97XX_GPIO_POL_LOW, WM97XX_GPIO_NOTSTICKY,
			   WM97XX_GPIO_NOWAKE);

	wm->pen_irq = DB1300_AC97_PEN_INT;

	वापस wm97xx_रेजिस्टर_mach_ops(wm, &db1300_wm97xx_ops);
पूर्ण
#अन्यथा
अटल पूर्णांक db1300_wm97xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver db1300_wm97xx_driver = अणु
	.driver.name	= "wm97xx-touch",
	.driver.owner	= THIS_MODULE,
	.probe		= db1300_wm97xx_probe,
पूर्ण;

/**********************************************************************/

अटल काष्ठा platक्रमm_device *db1300_dev[] __initdata = अणु
	&db1300_eth_dev,
	&db1300_i2c_dev,
	&db1300_5waysw_dev,
	&db1300_nand_dev,
	&db1300_ide_dev,
	&db1300_sd0_dev,
	&db1300_sd1_dev,
	&db1300_lcd_dev,
	&db1300_ac97_dev,
	&db1300_i2s_dev,
	&db1300_wm9715_dev,
	&db1300_ac97dma_dev,
	&db1300_i2sdma_dev,
	&db1300_sndac97_dev,
	&db1300_sndi2s_dev,
पूर्ण;

पूर्णांक __init db1300_dev_setup(व्योम)
अणु
	पूर्णांक swapped, cpldirq;
	काष्ठा clk *c;

	/* setup CPLD IRQ muxer */
	cpldirq = au1300_gpio_to_irq(AU1300_PIN_EXTCLK1);
	irq_set_irq_type(cpldirq, IRQ_TYPE_LEVEL_HIGH);
	bcsr_init_irq(DB1300_FIRST_INT, DB1300_LAST_INT, cpldirq);

	/* insert/eject IRQs: one always triggers so करोn't enable them
	 * when करोing request_irq() on them.  DB1200 has this bug too.
	 */
	irq_set_status_flags(DB1300_SD1_INSERT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1300_SD1_EJECT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1300_CF_INSERT_INT, IRQ_NOAUTOEN);
	irq_set_status_flags(DB1300_CF_EJECT_INT, IRQ_NOAUTOEN);

	/*
	 * setup board
	 */
	prom_get_ethernet_addr(&db1300_eth_config.mac[0]);

	i2c_रेजिस्टर_board_info(0, db1300_i2c_devs,
				ARRAY_SIZE(db1300_i2c_devs));

	अगर (platक्रमm_driver_रेजिस्टर(&db1300_wm97xx_driver))
		pr_warn("DB1300: failed to init touch pen irq support!\n");

	/* Audio PSC घड़ी is supplied by codecs (PSC1, 2) */
	__raw_ग_लिखोl(PSC_SEL_CLK_SERCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1300_PSC1_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();
	__raw_ग_लिखोl(PSC_SEL_CLK_SERCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1300_PSC2_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();
	/* I2C driver wants 50MHz, get as बंद as possible */
	c = clk_get(शून्य, "psc3_intclk");
	अगर (!IS_ERR(c)) अणु
		clk_set_rate(c, 50000000);
		clk_prepare_enable(c);
		clk_put(c);
	पूर्ण
	__raw_ग_लिखोl(PSC_SEL_CLK_INTCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1300_PSC3_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();

	/* enable घातer to USB ports */
	bcsr_mod(BCSR_RESETS, 0, BCSR_RESETS_USBHPWR | BCSR_RESETS_OTGPWR);

	/* although it is socket #0, it uses the CPLD bits which previous boards
	 * have used क्रम socket #1.
	 */
	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x00400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x00400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x00010000 - 1,
		DB1300_CF_INT, DB1300_CF_INSERT_INT, 0, DB1300_CF_EJECT_INT, 1);

	swapped = bcsr_पढ़ो(BCSR_STATUS) & BCSR_STATUS_DB1200_SWAPBOOT;
	db1x_रेजिस्टर_norflash(64 << 20, 2, swapped);

	वापस platक्रमm_add_devices(db1300_dev, ARRAY_SIZE(db1300_dev));
पूर्ण


पूर्णांक __init db1300_board_setup(व्योम)
अणु
	अचिन्हित लघु whoami;

	bcsr_init(DB1300_BCSR_PHYS_ADDR,
		  DB1300_BCSR_PHYS_ADDR + DB1300_BCSR_HEXLED_OFS);

	whoami = bcsr_पढ़ो(BCSR_WHOAMI);
	अगर (BCSR_WHOAMI_BOARD(whoami) != BCSR_WHOAMI_DB1300)
		वापस -ENODEV;

	db1300_gpio_config();

	prपूर्णांकk(KERN_INFO "NetLogic DBAu1300 Development Platform.\n\t"
		"BoardID %d   CPLD Rev %d   DaughtercardID %d\n",
		BCSR_WHOAMI_BOARD(whoami), BCSR_WHOAMI_CPLD(whoami),
		BCSR_WHOAMI_DCID(whoami));

	/* enable UARTs, YAMON only enables #2 */
	alchemy_uart_enable(AU1300_UART0_PHYS_ADDR);
	alchemy_uart_enable(AU1300_UART1_PHYS_ADDR);
	alchemy_uart_enable(AU1300_UART3_PHYS_ADDR);

	वापस 0;
पूर्ण
