<शैली गुरु>
/*
 * Copyright 2012 (C), Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * arch/arm/mach-orion5x/board-dt.c
 *
 * Flattened Device Tree board initialization
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mbus.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <plat/irq.h>
#समावेश <plat/समय.स>
#समावेश "orion5x.h"
#समावेश "bridge-regs.h"
#समावेश "common.h"

अटल काष्ठा of_dev_auxdata orion5x_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("marvell,orion-spi", 0xf1010600, "orion_spi.0", शून्य),
	OF_DEV_AUXDATA("marvell,mv64xxx-i2c", 0xf1011000, "mv64xxx_i2c.0",
		       शून्य),
	OF_DEV_AUXDATA("marvell,orion-wdt", 0xf1020300, "orion_wdt", शून्य),
	OF_DEV_AUXDATA("marvell,orion-sata", 0xf1080000, "sata_mv.0", शून्य),
	OF_DEV_AUXDATA("marvell,orion-crypto", 0xf1090000, "mv_crypto", शून्य),
	अणुपूर्ण,
पूर्ण;

अटल व्योम __init orion5x_dt_init(व्योम)
अणु
	अक्षर *dev_name;
	u32 dev, rev;

	orion5x_id(&dev, &rev, &dev_name);
	prपूर्णांकk(KERN_INFO "Orion ID: %s. TCLK=%d.\n", dev_name, orion5x_tclk);

	BUG_ON(mvebu_mbus_dt_init(false));

	/*
	 * Setup Orion address map
	 */
	orion5x_setup_wins();

	/*
	 * Don't issue "Wait for Interrupt" inकाष्ठाion अगर we are
	 * running on D0 5281 silicon.
	 */
	अगर (dev == MV88F5281_DEV_ID && rev == MV88F5281_REV_D0) अणु
		prपूर्णांकk(KERN_INFO "Orion: Applying 5281 D0 WFI workaround.\n");
		cpu_idle_poll_ctrl(true);
	पूर्ण

	अगर (of_machine_is_compatible("maxtor,shared-storage-2"))
		mss2_init();

	of_platक्रमm_शेष_populate(शून्य, orion5x_auxdata_lookup, शून्य);
पूर्ण

अटल स्थिर अक्षर *orion5x_dt_compat[] = अणु
	"marvell,orion5x",
	शून्य,
पूर्ण;

DT_MACHINE_START(ORION5X_DT, "Marvell Orion5x (Flattened Device Tree)")
	/* Maपूर्णांकainer: Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com> */
	.map_io		= orion5x_map_io,
	.init_machine	= orion5x_dt_init,
	.restart	= orion5x_restart,
	.dt_compat	= orion5x_dt_compat,
MACHINE_END
