<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/amplc_dio200.c
 *
 * Driver क्रम Amplicon PC212E, PC214E, PC215E, PC218E, PC272E.
 *
 * Copyright (C) 2005-2013 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998,2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: amplc_dio200
 * Description: Amplicon 200 Series ISA Digital I/O
 * Author: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Amplicon] PC212E (pc212e), PC214E (pc214e), PC215E (pc215e),
 *   PC218E (pc218e), PC272E (pc272e)
 * Updated: Mon, 18 Mar 2013 14:40:41 +0000
 *
 * Status: works
 *
 * Configuration options:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional, but commands won't work without it)
 *
 * Passing a zero क्रम an option is the same as leaving it unspecअगरied.
 *
 * SUBDEVICES
 *
 *                     PC212E         PC214E         PC215E
 *                  -------------  -------------  -------------
 *   Subdevices           6              4              5
 *    0                 PPI-X          PPI-X          PPI-X
 *    1                 CTR-Y1         PPI-Y          PPI-Y
 *    2                 CTR-Y2         CTR-Z1*        CTR-Z1
 *    3                 CTR-Z1       INTERRUPT*       CTR-Z2
 *    4                 CTR-Z2                      INTERRUPT
 *    5               INTERRUPT
 *
 *                     PC218E         PC272E
 *                  -------------  -------------
 *   Subdevices           7              4
 *    0                 CTR-X1         PPI-X
 *    1                 CTR-X2         PPI-Y
 *    2                 CTR-Y1         PPI-Z
 *    3                 CTR-Y2       INTERRUPT
 *    4                 CTR-Z1
 *    5                 CTR-Z2
 *    6               INTERRUPT
 *
 * Each PPI is a 8255 chip providing 24 DIO channels.  The DIO channels
 * are configurable as inमाला_दो or outमाला_दो in four groups:
 *
 *   Port A  - channels  0 to  7
 *   Port B  - channels  8 to 15
 *   Port CL - channels 16 to 19
 *   Port CH - channels 20 to 23
 *
 * Only mode 0 of the 8255 chips is supported.
 *
 * Each CTR is a 8254 chip providing 3 16-bit counter channels.  Each
 * channel is configured inभागidually with INSN_CONFIG inकाष्ठाions.  The
 * specअगरic type of configuration inकाष्ठाion is specअगरied in data[0].
 * Some configuration inकाष्ठाions expect an additional parameter in
 * data[1]; others वापस a value in data[1].  The following configuration
 * inकाष्ठाions are supported:
 *
 *   INSN_CONFIG_SET_COUNTER_MODE.  Sets the counter channel's mode and
 *     BCD/binary setting specअगरied in data[1].
 *
 *   INSN_CONFIG_8254_READ_STATUS.  Reads the status रेजिस्टर value क्रम the
 *     counter channel पूर्णांकo data[1].
 *
 *   INSN_CONFIG_SET_CLOCK_SRC.  Sets the counter channel's घड़ी source as
 *     specअगरied in data[1] (this is a hardware-specअगरic value).  Not
 *     supported on PC214E.  For the other boards, valid घड़ी sources are
 *     0 to 7 as follows:
 *
 *       0.  CLK n, the counter channel's dedicated CLK input from the SK1
 *         connector.  (N.B. क्रम other values, the counter channel's CLKn
 *         pin on the SK1 connector is an output!)
 *       1.  Internal 10 MHz घड़ी.
 *       2.  Internal 1 MHz घड़ी.
 *       3.  Internal 100 kHz घड़ी.
 *       4.  Internal 10 kHz घड़ी.
 *       5.  Internal 1 kHz घड़ी.
 *       6.  OUT n-1, the output of counter channel n-1 (see note 1 below).
 *       7.  Ext Clock, the counter chip's dedicated Ext Clock input from
 *         the SK1 connector.  This pin is shared by all three counter
 *         channels on the chip.
 *
 *   INSN_CONFIG_GET_CLOCK_SRC.  Returns the counter channel's current
 *     घड़ी source in data[1].  For पूर्णांकernal घड़ी sources, data[2] is set
 *     to the period in ns.
 *
 *   INSN_CONFIG_SET_GATE_SRC.  Sets the counter channel's gate source as
 *     specअगरied in data[2] (this is a hardware-specअगरic value).  Not
 *     supported on PC214E.  For the other boards, valid gate sources are 0
 *     to 7 as follows:
 *
 *       0.  VCC (पूर्णांकernal +5V d.c.), i.e. gate permanently enabled.
 *       1.  GND (पूर्णांकernal 0V d.c.), i.e. gate permanently disabled.
 *       2.  GAT n, the counter channel's dedicated GAT input from the SK1
 *         connector.  (N.B. क्रम other values, the counter channel's GATn
 *         pin on the SK1 connector is an output!)
 *       3.  /OUT n-2, the inverted output of counter channel n-2 (see note
 *         2 below).
 *       4.  Reserved.
 *       5.  Reserved.
 *       6.  Reserved.
 *       7.  Reserved.
 *
 *   INSN_CONFIG_GET_GATE_SRC.  Returns the counter channel's current gate
 *     source in data[2].
 *
 * Clock and gate पूर्णांकerconnection notes:
 *
 *   1.  Clock source OUT n-1 is the output of the preceding channel on the
 *   same counter subdevice अगर n > 0, or the output of channel 2 on the
 *   preceding counter subdevice (see note 3) अगर n = 0.
 *
 *   2.  Gate source /OUT n-2 is the inverted output of channel 0 on the
 *   same counter subdevice अगर n = 2, or the inverted output of channel n+1
 *   on the preceding counter subdevice (see note 3) अगर n < 2.
 *
 *   3.  The counter subdevices are connected in a ring, so the highest
 *   counter subdevice precedes the lowest.
 *
 * The 'INTERRUPT' subdevice pretends to be a digital input subdevice.  The
 * digital inमाला_दो come from the पूर्णांकerrupt status रेजिस्टर.  The number of
 * channels matches the number of पूर्णांकerrupt sources.  The PC214E करोes not
 * have an पूर्णांकerrupt status रेजिस्टर; see notes on 'INTERRUPT SOURCES'
 * below.
 *
 * INTERRUPT SOURCES
 *
 *                     PC212E         PC214E         PC215E
 *                  -------------  -------------  -------------
 *   Sources              6              1              6
 *    0               PPI-X-C0       JUMPER-J5      PPI-X-C0
 *    1               PPI-X-C3                      PPI-X-C3
 *    2              CTR-Y1-OUT1                    PPI-Y-C0
 *    3              CTR-Y2-OUT1                    PPI-Y-C3
 *    4              CTR-Z1-OUT1                   CTR-Z1-OUT1
 *    5              CTR-Z2-OUT1                   CTR-Z2-OUT1
 *
 *                     PC218E         PC272E
 *                  -------------  -------------
 *   Sources              6              6
 *    0              CTR-X1-OUT1     PPI-X-C0
 *    1              CTR-X2-OUT1     PPI-X-C3
 *    2              CTR-Y1-OUT1     PPI-Y-C0
 *    3              CTR-Y2-OUT1     PPI-Y-C3
 *    4              CTR-Z1-OUT1     PPI-Z-C0
 *    5              CTR-Z2-OUT1     PPI-Z-C3
 *
 * When an पूर्णांकerrupt source is enabled in the पूर्णांकerrupt source enable
 * रेजिस्टर, a rising edge on the source संकेत latches the corresponding
 * bit to 1 in the पूर्णांकerrupt status रेजिस्टर.
 *
 * When the पूर्णांकerrupt status रेजिस्टर value as a whole (actually, just the
 * 6 least signअगरicant bits) goes from zero to non-zero, the board will
 * generate an पूर्णांकerrupt.  No further पूर्णांकerrupts will occur until the
 * पूर्णांकerrupt status रेजिस्टर is cleared to zero.  To clear a bit to zero in
 * the पूर्णांकerrupt status रेजिस्टर, the corresponding पूर्णांकerrupt source must
 * be disabled in the पूर्णांकerrupt source enable रेजिस्टर (there is no
 * separate पूर्णांकerrupt clear रेजिस्टर).
 *
 * The PC214E करोes not have an पूर्णांकerrupt source enable रेजिस्टर or an
 * पूर्णांकerrupt status रेजिस्टर; its 'INTERRUPT' subdevice has a single
 * channel and its पूर्णांकerrupt source is selected by the position of jumper
 * J5.
 *
 * COMMANDS
 *
 * The driver supports a पढ़ो streaming acquisition command on the
 * 'INTERRUPT' subdevice.  The channel list selects the पूर्णांकerrupt sources
 * to be enabled.  All channels will be sampled together (convert_src ==
 * TRIG_NOW).  The scan begins a लघु समय after the hardware पूर्णांकerrupt
 * occurs, subject to पूर्णांकerrupt latencies (scan_begin_src == TRIG_EXT,
 * scan_begin_arg == 0).  The value पढ़ो from the पूर्णांकerrupt status रेजिस्टर
 * is packed पूर्णांकo a लघु value, one bit per requested channel, in the
 * order they appear in the channel list.
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश "amplc_dio200.h"

/*
 * Board descriptions.
 */
अटल स्थिर काष्ठा dio200_board dio200_isa_boards[] = अणु
	अणु
		.name		= "pc212e",
		.n_subdevs	= 6,
		.sdtype		= अणु
			sd_8255, sd_8254, sd_8254, sd_8254, sd_8254, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु 0x00, 0x08, 0x0c, 0x10, 0x14, 0x3f पूर्ण,
		.has_पूर्णांक_sce	= true,
		.has_clk_gat_sce = true,
	पूर्ण, अणु
		.name		= "pc214e",
		.n_subdevs	= 4,
		.sdtype		= अणु
			sd_8255, sd_8255, sd_8254, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु 0x00, 0x08, 0x10, 0x01 पूर्ण,
	पूर्ण, अणु
		.name		= "pc215e",
		.n_subdevs	= 5,
		.sdtype		= अणु
			sd_8255, sd_8255, sd_8254, sd_8254, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु 0x00, 0x08, 0x10, 0x14, 0x3f पूर्ण,
		.has_पूर्णांक_sce	= true,
		.has_clk_gat_sce = true,
	पूर्ण, अणु
		.name		= "pc218e",
		.n_subdevs	= 7,
		.sdtype		= अणु
			sd_8254, sd_8254, sd_8255, sd_8254, sd_8254, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x3f पूर्ण,
		.has_पूर्णांक_sce	= true,
		.has_clk_gat_sce = true,
	पूर्ण, अणु
		.name		= "pc272e",
		.n_subdevs	= 4,
		.sdtype		= अणु
			sd_8255, sd_8255, sd_8255, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु 0x00, 0x08, 0x10, 0x3f पूर्ण,
		.has_पूर्णांक_sce = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dio200_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x20);
	अगर (ret)
		वापस ret;

	वापस amplc_dio200_common_attach(dev, it->options[1], 0);
पूर्ण

अटल काष्ठा comedi_driver amplc_dio200_driver = अणु
	.driver_name	= "amplc_dio200",
	.module		= THIS_MODULE,
	.attach		= dio200_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &dio200_isa_boards[0].name,
	.offset		= माप(काष्ठा dio200_board),
	.num_names	= ARRAY_SIZE(dio200_isa_boards),
पूर्ण;
module_comedi_driver(amplc_dio200_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon 200 Series ISA DIO boards");
MODULE_LICENSE("GPL");
