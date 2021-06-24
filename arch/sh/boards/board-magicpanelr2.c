<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/magicpanel/setup.c
 *
 *  Copyright (C) 2007  Markus Brunner, Mark Jonas
 *
 *  Magic Panel Release 2 board setup
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <mach/magicpanelr2.h>
#समावेश <यंत्र/heartbeat.h>
#समावेश <cpu/sh7720.h>

/* Dummy supplies, where voltage करोesn't matter */
अटल काष्ठा regulator_consumer_supply dummy_supplies[] = अणु
	REGULATOR_SUPPLY("vddvario", "smsc911x"),
	REGULATOR_SUPPLY("vdd33a", "smsc911x"),
पूर्ण;

#घोषणा LAN9115_READY	(__raw_पढ़ोl(0xA8000084UL) & 0x00000001UL)

/* Wait until reset finished. Timeout is 100ms. */
अटल पूर्णांक __init ethernet_reset_finished(व्योम)
अणु
	पूर्णांक i;

	अगर (LAN9115_READY)
		वापस 1;

	क्रम (i = 0; i < 10; ++i) अणु
		mdelay(10);
		अगर (LAN9115_READY)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init reset_ethernet(व्योम)
अणु
	/* PMDR: LAN_RESET=on */
	CLRBITS_OUTB(0x10, PORT_PMDR);

	udelay(200);

	/* PMDR: LAN_RESET=off */
	SETBITS_OUTB(0x10, PORT_PMDR);
पूर्ण

अटल व्योम __init setup_chip_select(व्योम)
अणु
	/* CS2: LAN (0x08000000 - 0x0bffffff) */
	/* no idle cycles, normal space, 8 bit data bus */
	__raw_ग_लिखोl(0x36db0400, CS2BCR);
	/* (SW:1.5 WR:3 HW:1.5), ext. रुको */
	__raw_ग_लिखोl(0x000003c0, CS2WCR);

	/* CS4: CAN1 (0xb0000000 - 0xb3ffffff) */
	/* no idle cycles, normal space, 8 bit data bus */
	__raw_ग_लिखोl(0x00000200, CS4BCR);
	/* (SW:1.5 WR:3 HW:1.5), ext. रुको */
	__raw_ग_लिखोl(0x00100981, CS4WCR);

	/* CS5a: CAN2 (0xb4000000 - 0xb5ffffff) */
	/* no idle cycles, normal space, 8 bit data bus */
	__raw_ग_लिखोl(0x00000200, CS5ABCR);
	/* (SW:1.5 WR:3 HW:1.5), ext. रुको */
	__raw_ग_लिखोl(0x00100981, CS5AWCR);

	/* CS5b: CAN3 (0xb6000000 - 0xb7ffffff) */
	/* no idle cycles, normal space, 8 bit data bus */
	__raw_ग_लिखोl(0x00000200, CS5BBCR);
	/* (SW:1.5 WR:3 HW:1.5), ext. रुको */
	__raw_ग_लिखोl(0x00100981, CS5BWCR);

	/* CS6a: Rotary (0xb8000000 - 0xb9ffffff) */
	/* no idle cycles, normal space, 8 bit data bus */
	__raw_ग_लिखोl(0x00000200, CS6ABCR);
	/* (SW:1.5 WR:3 HW:1.5), no ext. रुको */
	__raw_ग_लिखोl(0x001009C1, CS6AWCR);
पूर्ण

अटल व्योम __init setup_port_multiplexing(व्योम)
अणु
	/* A7 GPO(LED8);     A6 GPO(LED7);     A5 GPO(LED6);	  A4 GPO(LED5);
	 * A3 GPO(LED4);     A2 GPO(LED3);     A1 GPO(LED2);	  A0 GPO(LED1);
	 */
	__raw_ग_लिखोw(0x5555, PORT_PACR);	/* 01 01 01 01 01 01 01 01 */

	/* B7 GPO(RST4);   B6 GPO(RST3);  B5 GPO(RST2);    B4 GPO(RST1);
	 * B3 GPO(PB3);	   B2 GPO(PB2);	  B1 GPO(PB1);	   B0 GPO(PB0);
	 */
	__raw_ग_लिखोw(0x5555, PORT_PBCR);	/* 01 01 01 01 01 01 01 01 */

	/* C7 GPO(PC7);	  C6 GPO(PC6);	  C5 GPO(PC5);	   C4 GPO(PC4);
	 * C3 LCD_DATA3;  C2 LCD_DATA2;   C1 LCD_DATA1;	   C0 LCD_DATA0;
	 */
	__raw_ग_लिखोw(0x5500, PORT_PCCR);	/* 01 01 01 01 00 00 00 00 */

	/* D7 GPO(PD7);	D6 GPO(PD6);	D5 GPO(PD5);	   D4 GPO(PD4);
	 * D3 GPO(PD3);	D2 GPO(PD2);	D1 GPO(PD1);	   D0 GPO(PD0);
	 */
	__raw_ग_लिखोw(0x5555, PORT_PDCR);	/* 01 01 01 01 01 01 01 01 */

	/* E7 (x);	  E6 GPI(nu);	 E5 GPI(nu);	  E4 LCD_M_DISP;
	 * E3 LCD_CL1;	  E2 LCD_CL2;	 E1 LCD_DON;	  E0 LCD_FLM;
	 */
	__raw_ग_लिखोw(0x3C00, PORT_PECR);	/* 00 11 11 00 00 00 00 00 */

	/* F7 (x);	     F6 DA1(VLCD);     F5 DA0(nc);	  F4 AN3;
	 * F3 AN2(MID_AD);   F2 AN1(EARTH_AD); F1 AN0(TEMP);	  F0 GPI+(nc);
	 */
	__raw_ग_लिखोw(0x0002, PORT_PFCR);	/* 00 00 00 00 00 00 00 10 */

	/* G7 (x);	  G6 IRQ5(TOUCH_BUSY); G5 IRQ4(TOUCH_IRQ); G4 GPI(KEY2);
	 * G3 GPI(KEY1);  G2 GPO(LED11);	G1 GPO(LED10);     G0 GPO(LED9);
	 */
	__raw_ग_लिखोw(0x03D5, PORT_PGCR);	/* 00 00 00 11 11 01 01 01 */

	/* H7 (x);	      H6 /RAS(BRAS);	  H5 /CAS(BCAS); H4 CKE(BCKE);
	 * H3 GPO(EARTH_OFF); H2 GPO(EARTH_TEST); H1 USB2_PWR;	 H0 USB1_PWR;
	 */
	__raw_ग_लिखोw(0x0050, PORT_PHCR);	/* 00 00 00 00 01 01 00 00 */

	/* J7 (x);	  J6 AUDCK;	   J5 ASEBRKAK;	    J4 AUDATA3;
	 * J3 AUDATA2;	  J2 AUDATA1;	   J1 AUDATA0;	    J0 AUDSYNC;
	 */
	__raw_ग_लिखोw(0x0000, PORT_PJCR);	/* 00 00 00 00 00 00 00 00 */

	/* K7 (x);	    K6 (x);	     K5 (x);	   K4 (x);
	 * K3 PINT7(/PWR2); K2 PINT6(/PWR1); K1 PINT5(nu); K0 PINT4(FLASH_READY)
	 */
	__raw_ग_लिखोw(0x00FF, PORT_PKCR);	/* 00 00 00 00 11 11 11 11 */

	/* L7 TRST;	   L6 TMS;	     L5 TDO;		  L4 TDI;
	 * L3 TCK;	   L2 (x);	     L1 (x);		  L0 (x);
	 */
	__raw_ग_लिखोw(0x0000, PORT_PLCR);	/* 00 00 00 00 00 00 00 00 */

	/* M7 GPO(CURRENT_SINK);    M6 GPO(PWR_SWITCH);     M5 GPO(LAN_SPEED);
	 * M4 GPO(LAN_RESET);       M3 GPO(BUZZER);	    M2 GPO(LCD_BL);
	 * M1 CS5B(CAN3_CS);	    M0 GPI+(nc);
	 */
	__raw_ग_लिखोw(0x5552, PORT_PMCR);	   /* 01 01 01 01 01 01 00 10 */

	/* CURRENT_SINK=off,	PWR_SWITCH=off, LAN_SPEED=100MBit,
	 * LAN_RESET=off,	BUZZER=off,	LCD_BL=off
	 */
#अगर CONFIG_SH_MAGIC_PANEL_R2_VERSION == 2
	__raw_ग_लिखोb(0x30, PORT_PMDR);
#या_अगर CONFIG_SH_MAGIC_PANEL_R2_VERSION == 3
	__raw_ग_लिखोb(0xF0, PORT_PMDR);
#अन्यथा
#त्रुटि Unknown revision of PLATFORM_MP_R2
#पूर्ण_अगर

	/* P7 (x);	       P6 (x);		  P5 (x);
	 * P4 GPO(nu);	       P3 IRQ3(LAN_IRQ);  P2 IRQ2(CAN3_IRQ);
	 * P1 IRQ1(CAN2_IRQ);  P0 IRQ0(CAN1_IRQ)
	 */
	__raw_ग_लिखोw(0x0100, PORT_PPCR);	/* 00 00 00 01 00 00 00 00 */
	__raw_ग_लिखोb(0x10, PORT_PPDR);

	/* R7 A25;	     R6 A24;	     R5 A23;		  R4 A22;
	 * R3 A21;	     R2 A20;	     R1 A19;		  R0 A0;
	 */
	gpio_request(GPIO_FN_A25, शून्य);
	gpio_request(GPIO_FN_A24, शून्य);
	gpio_request(GPIO_FN_A23, शून्य);
	gpio_request(GPIO_FN_A22, शून्य);
	gpio_request(GPIO_FN_A21, शून्य);
	gpio_request(GPIO_FN_A20, शून्य);
	gpio_request(GPIO_FN_A19, शून्य);
	gpio_request(GPIO_FN_A0, शून्य);

	/* S7 (x);		S6 (x);        S5 (x);	     S4 GPO(EEPROM_CS2);
	 * S3 GPO(EEPROM_CS1);  S2 SIOF0_TXD;  S1 SIOF0_RXD; S0 SIOF0_SCK;
	 */
	__raw_ग_लिखोw(0x0140, PORT_PSCR);	/* 00 00 00 01 01 00 00 00 */

	/* T7 (x);	   T6 (x);	  T5 (x);	  T4 COM1_CTS;
	 * T3 COM1_RTS;	   T2 COM1_TXD;	  T1 COM1_RXD;	  T0 GPO(WDOG)
	 */
	__raw_ग_लिखोw(0x0001, PORT_PTCR);	/* 00 00 00 00 00 00 00 01 */

	/* U7 (x);	     U6 (x);	   U5 (x);	  U4 GPI+(/AC_FAULT);
	 * U3 GPO(TOUCH_CS); U2 TOUCH_TXD; U1 TOUCH_RXD;  U0 TOUCH_SCK;
	 */
	__raw_ग_लिखोw(0x0240, PORT_PUCR);	/* 00 00 00 10 01 00 00 00 */

	/* V7 (x);	  V6 (x);	V5 (x);		  V4 GPO(MID2);
	 * V3 GPO(MID1);  V2 CARD_TxD;	V1 CARD_RxD;	  V0 GPI+(/BAT_FAULT);
	 */
	__raw_ग_लिखोw(0x0142, PORT_PVCR);	/* 00 00 00 01 01 00 00 10 */
पूर्ण

अटल व्योम __init mpr2_setup(अक्षर **cmdline_p)
अणु
	/* set Pin Select Register A:
	 * /PCC_CD1, /PCC_CD2,  PCC_BVD1, PCC_BVD2,
	 * /IOIS16,  IRQ4,	IRQ5,	  USB1d_SUSPEND
	 */
	__raw_ग_लिखोw(0xAABC, PORT_PSELA);
	/* set Pin Select Register B:
	 * /SCIF0_RTS, /SCIF0_CTS, LCD_VCPWC,
	 * LCD_VEPWC,  IIC_SDA,    IIC_SCL, Reserved
	 */
	__raw_ग_लिखोw(0x3C00, PORT_PSELB);
	/* set Pin Select Register C:
	 * SIOF1_SCK, SIOF1_RxD, SCIF1_RxD, SCIF1_TxD, Reserved
	 */
	__raw_ग_लिखोw(0x0000, PORT_PSELC);
	/* set Pin Select Register D: Reserved, SIOF1_TxD, Reserved, SIOF1_MCLK,
	 * Reserved, SIOF1_SYNC, Reserved, SCIF1_SCK, Reserved
	 */
	__raw_ग_लिखोw(0x0000, PORT_PSELD);
	/* set USB TxRx Control: Reserved, DRV, Reserved, USB_TRANS, USB_SEL */
	__raw_ग_लिखोw(0x0101, PORT_UTRCTL);
	/* set USB Clock Control: USSCS, USSTB, Reserved (HighByte always A5) */
	__raw_ग_लिखोw(0xA5C0, PORT_UCLKCR_W);

	setup_chip_select();

	setup_port_multiplexing();

	reset_ethernet();

	prपूर्णांकk(KERN_INFO "Magic Panel Release 2 A.%i\n",
				CONFIG_SH_MAGIC_PANEL_R2_VERSION);

	अगर (ethernet_reset_finished() == 0)
		prपूर्णांकk(KERN_WARNING "Ethernet not ready\n");
पूर्ण

अटल काष्ठा resource smsc911x_resources[] = अणु
	[0] = अणु
		.start		= 0xa8000000,
		.end		= 0xabffffff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start		= evt2irq(0x660),
		.end		= evt2irq(0x660),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा smsc911x_platक्रमm_config smsc911x_config = अणु
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_32BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device smsc911x_device = अणु
	.name		= "smsc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev = अणु
		.platक्रमm_data = &smsc911x_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource heartbeat_resources[] = अणु
	[0] = अणु
		.start	= PA_LED,
		.end	= PA_LED,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.flags		= HEARTBEAT_INVERTED,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.dev	= अणु
		.platक्रमm_data	= &heartbeat_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(heartbeat_resources),
	.resource	= heartbeat_resources,
पूर्ण;

अटल काष्ठा mtd_partition mpr2_partitions[] = अणु
	/* Reserved क्रम bootloader, पढ़ो-only */
	अणु
		.name = "Bootloader",
		.offset = 0x00000000UL,
		.size = MPR2_MTD_BOOTLOADER_SIZE,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	/* Reserved क्रम kernel image */
	अणु
		.name = "Kernel",
		.offset = MTDPART_OFS_NXTBLK,
		.size = MPR2_MTD_KERNEL_SIZE,
	पूर्ण,
	/* Rest is used क्रम Flash FS */
	अणु
		.name = "Flash_FS",
		.offset = MTDPART_OFS_NXTBLK,
		.size = MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data flash_data = अणु
	.parts		= mpr2_partitions,
	.nr_parts	= ARRAY_SIZE(mpr2_partitions),
	.width		= 2,
पूर्ण;

अटल काष्ठा resource flash_resource = अणु
	.start		= 0x00000000,
	.end		= 0x2000000UL,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device flash_device = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= &flash_resource,
	.num_resources	= 1,
	.dev		= अणु
		.platक्रमm_data = &flash_data,
	पूर्ण,
पूर्ण;

/*
 * Add all resources to the platक्रमm_device
 */

अटल काष्ठा platक्रमm_device *mpr2_devices[] __initdata = अणु
	&heartbeat_device,
	&smsc911x_device,
	&flash_device,
पूर्ण;


अटल पूर्णांक __init mpr2_devices_setup(व्योम)
अणु
	regulator_रेजिस्टर_fixed(0, dummy_supplies, ARRAY_SIZE(dummy_supplies));

	वापस platक्रमm_add_devices(mpr2_devices, ARRAY_SIZE(mpr2_devices));
पूर्ण
device_initcall(mpr2_devices_setup);

/*
 * Initialize IRQ setting
 */
अटल व्योम __init init_mpr2_IRQ(व्योम)
अणु
	plat_irq_setup_pins(IRQ_MODE_IRQ); /* install handlers क्रम IRQ0-5 */

	irq_set_irq_type(evt2irq(0x600), IRQ_TYPE_LEVEL_LOW);    /* IRQ0 CAN1 */
	irq_set_irq_type(evt2irq(0x620), IRQ_TYPE_LEVEL_LOW);    /* IRQ1 CAN2 */
	irq_set_irq_type(evt2irq(0x640), IRQ_TYPE_LEVEL_LOW);    /* IRQ2 CAN3 */
	irq_set_irq_type(evt2irq(0x660), IRQ_TYPE_LEVEL_LOW);    /* IRQ3 SMSC9115 */
	irq_set_irq_type(evt2irq(0x680), IRQ_TYPE_EDGE_RISING);  /* IRQ4 touchscreen */
	irq_set_irq_type(evt2irq(0x6a0), IRQ_TYPE_EDGE_FALLING); /* IRQ5 touchscreen */

	पूर्णांकc_set_priority(evt2irq(0x600), 13);		/* IRQ0 CAN1 */
	पूर्णांकc_set_priority(evt2irq(0x620), 13);		/* IRQ0 CAN2 */
	पूर्णांकc_set_priority(evt2irq(0x640), 13);		/* IRQ0 CAN3 */
	पूर्णांकc_set_priority(evt2irq(0x660), 6);		/* IRQ3 SMSC9115 */
पूर्ण

/*
 * The Machine Vector
 */

अटल काष्ठा sh_machine_vector mv_mpr2 __iniपंचांगv = अणु
	.mv_name		= "mpr2",
	.mv_setup		= mpr2_setup,
	.mv_init_irq		= init_mpr2_IRQ,
पूर्ण;
