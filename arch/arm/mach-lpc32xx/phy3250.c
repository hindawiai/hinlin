<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Platक्रमm support क्रम LPC32xx SoC
 *
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2012 Roland Stigge <stigge@antcom.de>
 * Copyright (C) 2010 NXP Semiconductors
 */

#समावेश <linux/amba/pl08x.h>
#समावेश <linux/mtd/lpc32xx_mlc.h>
#समावेश <linux/mtd/lpc32xx_slc.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश "common.h"

अटल काष्ठा pl08x_channel_data pl08x_slave_channels[] = अणु
	अणु
		.bus_id = "nand-slc",
		.min_संकेत = 1, /* SLC न_अंकD Flash */
		.max_संकेत = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण,
	अणु
		.bus_id = "nand-mlc",
		.min_संकेत = 12, /* MLC न_अंकD Flash */
		.max_संकेत = 12,
		.periph_buses = PL08X_AHB1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक pl08x_get_संकेत(स्थिर काष्ठा pl08x_channel_data *cd)
अणु
	वापस cd->min_संकेत;
पूर्ण

अटल व्योम pl08x_put_संकेत(स्थिर काष्ठा pl08x_channel_data *cd, पूर्णांक ch)
अणु
पूर्ण

अटल काष्ठा pl08x_platक्रमm_data pl08x_pd = अणु
	/* Some reasonable स_नकल शेषs */
	.स_नकल_burst_size = PL08X_BURST_SZ_256,
	.स_नकल_bus_width = PL08X_BUS_WIDTH_32_BITS,
	.slave_channels = &pl08x_slave_channels[0],
	.num_slave_channels = ARRAY_SIZE(pl08x_slave_channels),
	.get_xfer_संकेत = pl08x_get_संकेत,
	.put_xfer_संकेत = pl08x_put_संकेत,
	.lli_buses = PL08X_AHB1,
	.mem_buses = PL08X_AHB1,
पूर्ण;

अटल काष्ठा lpc32xx_slc_platक्रमm_data lpc32xx_slc_data = अणु
	.dma_filter = pl08x_filter_id,
पूर्ण;

अटल काष्ठा lpc32xx_mlc_platक्रमm_data lpc32xx_mlc_data = अणु
	.dma_filter = pl08x_filter_id,
पूर्ण;

अटल स्थिर काष्ठा of_dev_auxdata lpc32xx_auxdata_lookup[] __initस्थिर = अणु
	OF_DEV_AUXDATA("arm,pl080", 0x31000000, "pl08xdmac", &pl08x_pd),
	OF_DEV_AUXDATA("nxp,lpc3220-slc", 0x20020000, "20020000.flash",
		       &lpc32xx_slc_data),
	OF_DEV_AUXDATA("nxp,lpc3220-mlc", 0x200a8000, "200a8000.flash",
		       &lpc32xx_mlc_data),
	अणु पूर्ण
पूर्ण;

अटल व्योम __init lpc3250_machine_init(व्योम)
अणु
	lpc32xx_serial_init();

	of_platक्रमm_शेष_populate(शून्य, lpc32xx_auxdata_lookup, शून्य);
पूर्ण

अटल स्थिर अक्षर *स्थिर lpc32xx_dt_compat[] __initस्थिर = अणु
	"nxp,lpc3220",
	"nxp,lpc3230",
	"nxp,lpc3240",
	"nxp,lpc3250",
	शून्य
पूर्ण;

DT_MACHINE_START(LPC32XX_DT, "LPC32XX SoC (Flattened Device Tree)")
	.atag_offset	= 0x100,
	.map_io		= lpc32xx_map_io,
	.init_machine	= lpc3250_machine_init,
	.dt_compat	= lpc32xx_dt_compat,
MACHINE_END
