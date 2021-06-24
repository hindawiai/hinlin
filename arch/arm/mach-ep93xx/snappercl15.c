<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/snappercl15.c
 * Bluewater Systems Snapper CL15 प्रणाली module
 *
 * Copyright (C) 2009 Bluewater Systems Ltd
 * Author: Ryan Mallon
 *
 * न_अंकD code adapted from driver by:
 *   Andre Renaud <andre@bluewatersys.com>
 *   James R. McKasसमाप्त
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/fb.h>

#समावेश <linux/mtd/platnand.h>

#समावेश "hardware.h"
#समावेश <linux/platक्रमm_data/video-ep93xx.h>
#समावेश "gpio-ep93xx.h"

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "soc.h"

#घोषणा SNAPPERCL15_न_अंकD_BASE	(EP93XX_CS7_PHYS_BASE + SZ_16M)

#घोषणा SNAPPERCL15_न_अंकD_WPN	(1 << 8)  /* Write protect (active low) */
#घोषणा SNAPPERCL15_न_अंकD_ALE	(1 << 9)  /* Address latch */
#घोषणा SNAPPERCL15_न_अंकD_CLE	(1 << 10) /* Command latch */
#घोषणा SNAPPERCL15_न_अंकD_CEN	(1 << 11) /* Chip enable (active low) */
#घोषणा SNAPPERCL15_न_अंकD_RDY	(1 << 14) /* Device पढ़ोy */

#घोषणा न_अंकD_CTRL_ADDR(chip) 	(chip->legacy.IO_ADDR_W + 0x40)

अटल व्योम snappercl15_nand_cmd_ctrl(काष्ठा nand_chip *chip, पूर्णांक cmd,
				      अचिन्हित पूर्णांक ctrl)
अणु
	अटल u16 nand_state = SNAPPERCL15_न_अंकD_WPN;
	u16 set;

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		set = SNAPPERCL15_न_अंकD_CEN | SNAPPERCL15_न_अंकD_WPN;

		अगर (ctrl & न_अंकD_NCE)
			set &= ~SNAPPERCL15_न_अंकD_CEN;
		अगर (ctrl & न_अंकD_CLE)
			set |= SNAPPERCL15_न_अंकD_CLE;
		अगर (ctrl & न_अंकD_ALE)
			set |= SNAPPERCL15_न_अंकD_ALE;

		nand_state &= ~(SNAPPERCL15_न_अंकD_CEN |
				SNAPPERCL15_न_अंकD_CLE |
				SNAPPERCL15_न_अंकD_ALE);
		nand_state |= set;
		__raw_ग_लिखोw(nand_state, न_अंकD_CTRL_ADDR(chip));
	पूर्ण

	अगर (cmd != न_अंकD_CMD_NONE)
		__raw_ग_लिखोw((cmd & 0xff) | nand_state,
			     chip->legacy.IO_ADDR_W);
पूर्ण

अटल पूर्णांक snappercl15_nand_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस !!(__raw_पढ़ोw(न_अंकD_CTRL_ADDR(chip)) & SNAPPERCL15_न_अंकD_RDY);
पूर्ण

अटल काष्ठा mtd_partition snappercl15_nand_parts[] = अणु
	अणु
		.name		= "Kernel",
		.offset		= 0,
		.size		= SZ_2M,
	पूर्ण,
	अणु
		.name		= "Filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_nand_data snappercl15_nand_data = अणु
	.chip = अणु
		.nr_chips		= 1,
		.partitions		= snappercl15_nand_parts,
		.nr_partitions		= ARRAY_SIZE(snappercl15_nand_parts),
		.chip_delay		= 25,
	पूर्ण,
	.ctrl = अणु
		.dev_पढ़ोy		= snappercl15_nand_dev_पढ़ोy,
		.cmd_ctrl		= snappercl15_nand_cmd_ctrl,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource snappercl15_nand_resource[] = अणु
	अणु
		.start		= SNAPPERCL15_न_अंकD_BASE,
		.end		= SNAPPERCL15_न_अंकD_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device snappercl15_nand_device = अणु
	.name			= "gen_nand",
	.id			= -1,
	.dev.platक्रमm_data	= &snappercl15_nand_data,
	.resource		= snappercl15_nand_resource,
	.num_resources		= ARRAY_SIZE(snappercl15_nand_resource),
पूर्ण;

अटल काष्ठा ep93xx_eth_data __initdata snappercl15_eth_data = अणु
	.phy_id			= 1,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata snappercl15_i2c_data[] = अणु
	अणु
		/* Audio codec */
		I2C_BOARD_INFO("tlv320aic23", 0x1a),
	पूर्ण,
पूर्ण;

अटल काष्ठा ep93xxfb_mach_info __initdata snappercl15_fb_info = अणु
पूर्ण;

अटल काष्ठा platक्रमm_device snappercl15_audio_device = अणु
	.name		= "snappercl15-audio",
	.id		= -1,
पूर्ण;

अटल व्योम __init snappercl15_रेजिस्टर_audio(व्योम)
अणु
	ep93xx_रेजिस्टर_i2s();
	platक्रमm_device_रेजिस्टर(&snappercl15_audio_device);
पूर्ण

अटल व्योम __init snappercl15_init_machine(व्योम)
अणु
	ep93xx_init_devices();
	ep93xx_रेजिस्टर_eth(&snappercl15_eth_data, 1);
	ep93xx_रेजिस्टर_i2c(snappercl15_i2c_data,
			    ARRAY_SIZE(snappercl15_i2c_data));
	ep93xx_रेजिस्टर_fb(&snappercl15_fb_info);
	snappercl15_रेजिस्टर_audio();
	platक्रमm_device_रेजिस्टर(&snappercl15_nand_device);
पूर्ण

MACHINE_START(SNAPPER_CL15, "Bluewater Systems Snapper CL15")
	/* Maपूर्णांकainer: Ryan Mallon */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= snappercl15_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
