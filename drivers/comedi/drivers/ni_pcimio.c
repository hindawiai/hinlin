<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम NI PCI-MIO E series cards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_pcimio
 * Description: National Instruments PCI-MIO-E series and M series (all boards)
 * Author: ds, John Hallen, Frank Mori Hess, Rolf Mueller, Herbert Peremans,
 *   Herman Bruyninckx, Terry Barnaby
 * Status: works
 * Devices: [National Instruments] PCI-MIO-16XE-50 (ni_pcimio),
 *   PCI-MIO-16XE-10, PXI-6030E, PCI-MIO-16E-1, PCI-MIO-16E-4, PCI-6014,
 *   PCI-6040E, PXI-6040E, PCI-6030E, PCI-6031E, PCI-6032E, PCI-6033E,
 *   PCI-6071E, PCI-6023E, PCI-6024E, PCI-6025E, PXI-6025E, PCI-6034E,
 *   PCI-6035E, PCI-6052E, PCI-6110, PCI-6111, PCI-6220, PXI-6220,
 *   PCI-6221, PXI-6221, PCI-6224, PXI-6224, PCI-6225, PXI-6225,
 *   PCI-6229, PXI-6229, PCI-6250, PXI-6250, PCI-6251, PXI-6251,
 *   PCIe-6251, PXIe-6251, PCI-6254, PXI-6254, PCI-6259, PXI-6259,
 *   PCIe-6259, PXIe-6259, PCI-6280, PXI-6280, PCI-6281, PXI-6281,
 *   PCI-6284, PXI-6284, PCI-6289, PXI-6289, PCI-6711, PXI-6711,
 *   PCI-6713, PXI-6713, PXI-6071E, PCI-6070E, PXI-6070E,
 *   PXI-6052E, PCI-6036E, PCI-6731, PCI-6733, PXI-6733,
 *   PCI-6143, PXI-6143
 * Updated: Mon, 16 Jan 2017 12:56:04 +0000
 *
 * These boards are almost identical to the AT-MIO E series, except that
 * they use the PCI bus instead of ISA (i.e., AT). See the notes क्रम the
 * ni_aपंचांगio.o driver क्रम additional inक्रमmation about these boards.
 *
 * Autocalibration is supported on many of the devices, using the
 * comedi_calibrate (or comedi_soft_calibrate क्रम m-series) utility.
 * M-Series boards करो analog input and analog output calibration entirely
 * in software. The software calibration corrects the analog input क्रम
 * offset, gain and nonlinearity. The analog outमाला_दो are corrected क्रम
 * offset and gain. See the comedilib करोcumentation on
 * comedi_get_softcal_converter() क्रम more inक्रमmation.
 *
 * By शेष, the driver uses DMA to transfer analog input data to
 * memory.  When DMA is enabled, not all triggering features are
 * supported.
 *
 * Digital I/O may not work on 673x.
 *
 * Note that the PCI-6143 is a simultaineous sampling device with 8
 * convertors. With this board all of the convertors perक्रमm one
 * simultaineous sample during a scan पूर्णांकerval. The period क्रम a scan
 * is used क्रम the convert समय in a Comedi cmd. The convert trigger
 * source is normally set to TRIG_NOW by शेष.
 *
 * The RTSI trigger bus is supported on these cards on subdevice 10.
 * See the comedilib करोcumentation क्रम details.
 *
 * Inक्रमmation (number of channels, bits, etc.) क्रम some devices may be
 * incorrect. Please check this and submit a bug अगर there are problems
 * क्रम your device.
 *
 * SCXI is probably broken क्रम m-series boards.
 *
 * Bugs:
 * - When DMA is enabled, COMEDI_EV_CONVERT करोes not work correctly.
 */

/*
 * The PCI-MIO E series driver was originally written by
 * Tomasz Motylewski <...>, and ported to comedi by ds.
 *
 * References:
 *	341079b.pdf  PCI E Series Register-Level Programmer Manual
 *	340934b.pdf  DAQ-STC reference manual
 *
 *	322080b.pdf  6711/6713/6715 User Manual
 *
 *	320945c.pdf  PCI E Series User Manual
 *	322138a.pdf  PCI-6052E and DAQPad-6052E User Manual
 *
 * ISSUES:
 * - need to deal with बाह्यal reference क्रम DAC, and other DAC
 *   properties in board properties
 * - deal with at-mio-16de-10 revision D to N changes, etc.
 * - need to add other CALDAC type
 * - need to slow करोwn DAC loading. I करोn't trust NI's claim that
 *   two ग_लिखोs to the PCI bus slows IO enough. I would prefer to
 *   use udelay().
 *   Timing specs: (घड़ी)
 *	AD8522		30ns
 *	DAC8043		120ns
 *	DAC8800		60ns
 *	MB88341		?
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pci.h"

#समावेश <यंत्र/byteorder.h>

#समावेश "ni_stc.h"
#समावेश "mite.h"

#घोषणा PCIDMA

/*
 * These are not all the possible ao ranges क्रम 628x boards.
 * They can करो OFFSET +- REFERENCE where OFFSET can be
 * 0V, 5V, APFI<0,1>, or AO<0...3> and RANGE can
 * be 10V, 5V, 2V, 1V, APFI<0,1>, AO<0...3>.  That's
 * 63 dअगरferent possibilities.  An AO channel
 * can not act as it's own OFFSET or REFERENCE.
 */
अटल स्थिर काष्ठा comedi_lrange range_ni_M_628x_ao = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		RANGE(-5, 15),
		UNI_RANGE(10),
		RANGE(3, 7),
		RANGE(4, 6),
		RANGE_ext(-1, 1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_M_625x_ao = अणु
	3, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		RANGE_ext(-1, 1)
	पूर्ण
पूर्ण;

क्रमागत ni_pcimio_boardid अणु
	BOARD_PCIMIO_16XE_50,
	BOARD_PCIMIO_16XE_10,
	BOARD_PCI6014,
	BOARD_PXI6030E,
	BOARD_PCIMIO_16E_1,
	BOARD_PCIMIO_16E_4,
	BOARD_PXI6040E,
	BOARD_PCI6031E,
	BOARD_PCI6032E,
	BOARD_PCI6033E,
	BOARD_PCI6071E,
	BOARD_PCI6023E,
	BOARD_PCI6024E,
	BOARD_PCI6025E,
	BOARD_PXI6025E,
	BOARD_PCI6034E,
	BOARD_PCI6035E,
	BOARD_PCI6052E,
	BOARD_PCI6110,
	BOARD_PCI6111,
	/* BOARD_PCI6115, */
	/* BOARD_PXI6115, */
	BOARD_PCI6711,
	BOARD_PXI6711,
	BOARD_PCI6713,
	BOARD_PXI6713,
	BOARD_PCI6731,
	/* BOARD_PXI6731, */
	BOARD_PCI6733,
	BOARD_PXI6733,
	BOARD_PXI6071E,
	BOARD_PXI6070E,
	BOARD_PXI6052E,
	BOARD_PXI6031E,
	BOARD_PCI6036E,
	BOARD_PCI6220,
	BOARD_PXI6220,
	BOARD_PCI6221,
	BOARD_PCI6221_37PIN,
	BOARD_PXI6221,
	BOARD_PCI6224,
	BOARD_PXI6224,
	BOARD_PCI6225,
	BOARD_PXI6225,
	BOARD_PCI6229,
	BOARD_PXI6229,
	BOARD_PCI6250,
	BOARD_PXI6250,
	BOARD_PCI6251,
	BOARD_PXI6251,
	BOARD_PCIE6251,
	BOARD_PXIE6251,
	BOARD_PCI6254,
	BOARD_PXI6254,
	BOARD_PCI6259,
	BOARD_PXI6259,
	BOARD_PCIE6259,
	BOARD_PXIE6259,
	BOARD_PCI6280,
	BOARD_PXI6280,
	BOARD_PCI6281,
	BOARD_PXI6281,
	BOARD_PCI6284,
	BOARD_PXI6284,
	BOARD_PCI6289,
	BOARD_PXI6289,
	BOARD_PCI6143,
	BOARD_PXI6143,
पूर्ण;

अटल स्थिर काष्ठा ni_board_काष्ठा ni_boards[] = अणु
	[BOARD_PCIMIO_16XE_50] = अणु
		.name		= "pci-mio-16xe-50",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 2048,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_8,
		.ai_speed	= 50000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 50000,
		.caldac		= अणु dac8800, dac8043 पूर्ण,
	पूर्ण,
	[BOARD_PCIMIO_16XE_10] = अणु
		.name		= "pci-mio-16xe-10",	/*  aka pci-6030E */
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 10000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PCI6014] = अणु
		.name		= "pci-6014",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 100000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6030E] = अणु
		.name		= "pxi-6030e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 10000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PCIMIO_16E_1] = अणु
		.name		= "pci-mio-16e-1",	/* aka pci-6070e */
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु mb88341 पूर्ण,
	पूर्ण,
	[BOARD_PCIMIO_16E_4] = अणु
		.name		= "pci-mio-16e-4",	/* aka pci-6040e */
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_16,
		/*
		 * there have been reported problems with
		 * full speed on this board
		 */
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 512,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु ad8804_debug पूर्ण,	/* करोc says mb88341 */
	पूर्ण,
	[BOARD_PXI6040E] = अणु
		.name		= "pxi-6040e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 512,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु mb88341 पूर्ण,
	पूर्ण,
	[BOARD_PCI6031E] = अणु
		.name		= "pci-6031e",
		.n_adchan	= 64,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 10000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PCI6032E] = अणु
		.name		= "pci-6032e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PCI6033E] = अणु
		.name		= "pci-6033e",
		.n_adchan	= 64,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PCI6071E] = अणु
		.name		= "pci-6071e",
		.n_adchan	= 64,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PCI6023E] = अणु
		.name		= "pci-6023e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.caldac		= अणु ad8804_debug पूर्ण,	/* manual is wrong */
	पूर्ण,
	[BOARD_PCI6024E] = अणु
		.name		= "pci-6024e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 100000,
		.caldac		= अणु ad8804_debug पूर्ण,	/* manual is wrong */
	पूर्ण,
	[BOARD_PCI6025E] = अणु
		.name		= "pci-6025e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 100000,
		.caldac		= अणु ad8804_debug पूर्ण,	/* manual is wrong */
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PXI6025E] = अणु
		.name		= "pxi-6025e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 100000,
		.caldac		= अणु ad8804_debug पूर्ण,	/* manual is wrong */
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCI6034E] = अणु
		.name		= "pci-6034e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PCI6035E] = अणु
		.name		= "pci-6035e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 100000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PCI6052E] = अणु
		.name		= "pci-6052e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 3000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 3000,
		/* manual is wrong */
		.caldac		= अणु ad8804_debug, ad8804_debug, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PCI6110] = अणु
		.name		= "pci-6110",
		.n_adchan	= 4,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 8192,
		.alwaysdither	= 0,
		.gainlkup	= ai_gain_611x,
		.ai_speed	= 200,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.reg_type	= ni_reg_611x,
		.ao_range_table	= &range_bipolar10,
		.ao_fअगरo_depth	= 2048,
		.ao_speed	= 250,
		.caldac		= अणु ad8804, ad8804 पूर्ण,
	पूर्ण,
	[BOARD_PCI6111] = अणु
		.name		= "pci-6111",
		.n_adchan	= 2,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 8192,
		.gainlkup	= ai_gain_611x,
		.ai_speed	= 200,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.reg_type	= ni_reg_611x,
		.ao_range_table	= &range_bipolar10,
		.ao_fअगरo_depth	= 2048,
		.ao_speed	= 250,
		.caldac		= अणु ad8804, ad8804 पूर्ण,
	पूर्ण,
#अगर 0
	/* The 6115 boards probably need their own driver */
	[BOARD_PCI6115] = अणु	/* .device_id = 0x2ed0, */
		.name		= "pci-6115",
		.n_adchan	= 4,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 8192,
		.gainlkup	= ai_gain_611x,
		.ai_speed	= 100,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_671x	= 1,
		.ao_fअगरo_depth	= 2048,
		.ao_speed	= 250,
		.reg_611x	= 1,
		/* XXX */
		.caldac		= अणु ad8804_debug, ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
#पूर्ण_अगर
#अगर 0
	[BOARD_PXI6115] = अणु	/* .device_id = ????, */
		.name		= "pxi-6115",
		.n_adchan	= 4,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 8192,
		.gainlkup	= ai_gain_611x,
		.ai_speed	= 100,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_671x	= 1,
		.ao_fअगरo_depth	= 2048,
		.ao_speed	= 250,
		.reg_611x	= 1,
		/* XXX */
		.caldac		= अणु ad8804_debug, ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	[BOARD_PCI6711] = अणु
		.name = "pci-6711",
		.n_aochan	= 4,
		.ao_maxdata	= 0x0fff,
		/* data sheet says 8192, but fअगरo really holds 16384 samples */
		.ao_fअगरo_depth	= 16384,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000,
		.reg_type	= ni_reg_6711,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6711] = अणु
		.name		= "pxi-6711",
		.n_aochan	= 4,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 16384,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000,
		.reg_type	= ni_reg_6711,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PCI6713] = अणु
		.name		= "pci-6713",
		.n_aochan	= 8,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 16384,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000,
		.reg_type	= ni_reg_6713,
		.caldac		= अणु ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6713] = अणु
		.name		= "pxi-6713",
		.n_aochan	= 8,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 16384,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000,
		.reg_type	= ni_reg_6713,
		.caldac		= अणु ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PCI6731] = अणु
		.name		= "pci-6731",
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8192,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000,
		.reg_type	= ni_reg_6711,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
#अगर 0
	[BOARD_PXI6731] = अणु	/* .device_id = ????, */
		.name		= "pxi-6731",
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8192,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_6711,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	[BOARD_PCI6733] = अणु
		.name		= "pci-6733",
		.n_aochan	= 8,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 16384,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000,
		.reg_type	= ni_reg_6713,
		.caldac		= अणु ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6733] = अणु
		.name		= "pxi-6733",
		.n_aochan	= 8,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 16384,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000,
		.reg_type	= ni_reg_6713,
		.caldac		= अणु ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6071E] = अणु
		.name		= "pxi-6071e",
		.n_adchan	= 64,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6070E] = अणु
		.name		= "pxi-6070e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6052E] = अणु
		.name		= "pxi-6052e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 3000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 3000,
		.caldac		= अणु mb88341, mb88341, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PXI6031E] = अणु
		.name		= "pxi-6031e",
		.n_adchan	= 64,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 10000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण,
	[BOARD_PCI6036E] = अणु
		.name = "pci-6036e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 100000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PCI6220] = अणु
		.name		= "pci-6220",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,		/* FIXME: guess */
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.reg_type	= ni_reg_622x,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6220] = अणु
		.name		= "pxi-6220",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,		/* FIXME: guess */
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.reg_type	= ni_reg_622x,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PCI6221] = अणु
		.name		= "pci-6221",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_622x,
		.ao_speed	= 1200,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PCI6221_37PIN] = अणु
		.name		= "pci-6221_37pin",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_622x,
		.ao_speed	= 1200,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6221] = अणु
		.name		= "pxi-6221",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_622x,
		.ao_speed	= 1200,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PCI6224] = अणु
		.name		= "pci-6224",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.reg_type	= ni_reg_622x,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PXI6224] = अणु
		.name		= "pxi-6224",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.reg_type	= ni_reg_622x,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PCI6225] = अणु
		.name		= "pci-6225",
		.n_adchan	= 80,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PXI6225] = अणु
		.name		= "pxi-6225",
		.n_adchan	= 80,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PCI6229] = अणु
		.name		= "pci-6229",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6229] = अणु
		.name		= "pxi-6229",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_bipolar10,
		.reg_type	= ni_reg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 1000,
	पूर्ण,
	[BOARD_PCI6250] = अणु
		.name		= "pci-6250",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.reg_type	= ni_reg_625x,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6250] = अणु
		.name		= "pxi-6250",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.reg_type	= ni_reg_625x,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6251] = अणु
		.name		= "pci-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PXI6251] = अणु
		.name		= "pxi-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCIE6251] = अणु
		.name		= "pcie-6251",
		.alt_route_name	= "pci-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PXIE6251] = अणु
		.name		= "pxie-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6254] = अणु
		.name		= "pci-6254",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.reg_type	= ni_reg_625x,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6254] = अणु
		.name		= "pxi-6254",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.reg_type	= ni_reg_625x,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6259] = अणु
		.name		= "pci-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6259] = अणु
		.name		= "pxi-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCIE6259] = अणु
		.name		= "pcie-6259",
		.alt_route_name	= "pci-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXIE6259] = अणु
		.name		= "pxie-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 4095,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_625x_ao,
		.reg_type	= ni_reg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6280] = अणु
		.name		= "pci-6280",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.ao_fअगरo_depth	= 8191,
		.reg_type	= ni_reg_628x,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6280] = अणु
		.name		= "pxi-6280",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.ao_fअगरo_depth	= 8191,
		.reg_type	= ni_reg_628x,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6281] = अणु
		.name		= "pci-6281",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table = &range_ni_M_628x_ao,
		.reg_type	= ni_reg_628x,
		.ao_speed	= 350,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PXI6281] = अणु
		.name		= "pxi-6281",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_628x_ao,
		.reg_type	= ni_reg_628x,
		.ao_speed	= 350,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6284] = अणु
		.name		= "pci-6284",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.reg_type	= ni_reg_628x,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6284] = अणु
		.name		= "pxi-6284",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.reg_type	= ni_reg_628x,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6289] = अणु
		.name		= "pci-6289",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_628x_ao,
		.reg_type	= ni_reg_628x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
	पूर्ण,
	[BOARD_PXI6289] = अणु
		.name		= "pxi-6289",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fअगरo_depth	= 2047,
		.gainlkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 8191,
		.ao_range_table	= &range_ni_M_628x_ao,
		.reg_type	= ni_reg_628x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.caldac		= अणु caldac_none पूर्ण,
		.dio_speed	= 100,
	पूर्ण,
	[BOARD_PCI6143] = अणु
		.name		= "pci-6143",
		.n_adchan	= 8,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 1024,
		.gainlkup	= ai_gain_6143,
		.ai_speed	= 4000,
		.reg_type	= ni_reg_6143,
		.caldac		= अणु ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
	[BOARD_PXI6143] = अणु
		.name		= "pxi-6143",
		.n_adchan	= 8,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 1024,
		.gainlkup	= ai_gain_6143,
		.ai_speed	= 4000,
		.reg_type	= ni_reg_6143,
		.caldac		= अणु ad8804_debug, ad8804_debug पूर्ण,
	पूर्ण,
पूर्ण;

#समावेश "ni_mio_common.c"

अटल पूर्णांक pcimio_ai_change(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	ret = mite_buf_change(devpriv->ai_mite_ring, s);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pcimio_ao_change(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	ret = mite_buf_change(devpriv->ao_mite_ring, s);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pcimio_gpct0_change(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	ret = mite_buf_change(devpriv->gpct_mite_ring[0], s);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pcimio_gpct1_change(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	ret = mite_buf_change(devpriv->gpct_mite_ring[1], s);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pcimio_dio_change(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	ret = mite_buf_change(devpriv->cकरो_mite_ring, s);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम m_series_init_eeprom_buffer(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा mite *mite = devpriv->mite;
	resource_माप_प्रकार daq_phys_addr;
	अटल स्थिर पूर्णांक start_cal_eeprom = 0x400;
	अटल स्थिर अचिन्हित पूर्णांक winकरोw_size = 10;
	अचिन्हित पूर्णांक old_iodwbsr_bits;
	अचिन्हित पूर्णांक old_iodwbsr1_bits;
	अचिन्हित पूर्णांक old_iodwcr1_bits;
	पूर्णांक i;

	/* IO Winकरोw 1 needs to be temporarily mapped to पढ़ो the eeprom */
	daq_phys_addr = pci_resource_start(mite->pcidev, 1);

	old_iodwbsr_bits = पढ़ोl(mite->mmio + MITE_IODWBSR);
	old_iodwbsr1_bits = पढ़ोl(mite->mmio + MITE_IODWBSR_1);
	old_iodwcr1_bits = पढ़ोl(mite->mmio + MITE_IODWCR_1);
	ग_लिखोl(0x0, mite->mmio + MITE_IODWBSR);
	ग_लिखोl(((0x80 | winकरोw_size) | daq_phys_addr),
	       mite->mmio + MITE_IODWBSR_1);
	ग_लिखोl(0x1 | old_iodwcr1_bits, mite->mmio + MITE_IODWCR_1);
	ग_लिखोl(0xf, mite->mmio + 0x30);

	क्रम (i = 0; i < M_SERIES_EEPROM_SIZE; ++i)
		devpriv->eeprom_buffer[i] = ni_पढ़ोb(dev, start_cal_eeprom + i);

	ग_लिखोl(old_iodwbsr1_bits, mite->mmio + MITE_IODWBSR_1);
	ग_लिखोl(old_iodwbsr_bits, mite->mmio + MITE_IODWBSR);
	ग_लिखोl(old_iodwcr1_bits, mite->mmio + MITE_IODWCR_1);
	ग_लिखोl(0x0, mite->mmio + 0x30);
पूर्ण

अटल व्योम init_6143(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;

	/*  Disable पूर्णांकerrupts */
	ni_stc_ग_लिखोw(dev, 0, NISTC_INT_CTRL_REG);

	/*  Initialise 6143 AI specअगरic bits */

	/* Set G0,G1 DMA mode to E series version */
	ni_ग_लिखोb(dev, 0x00, NI6143_MAGIC_REG);
	/* Set EOCMode, ADCMode and pipelinedelay */
	ni_ग_लिखोb(dev, 0x80, NI6143_PIPELINE_DELAY_REG);
	/* Set EOC Delay */
	ni_ग_लिखोb(dev, 0x00, NI6143_EOC_SET_REG);

	/* Set the FIFO half full level */
	ni_ग_लिखोl(dev, board->ai_fअगरo_depth / 2, NI6143_AI_FIFO_FLAG_REG);

	/*  Strobe Relay disable bit */
	devpriv->ai_calib_source_enabled = 0;
	ni_ग_लिखोw(dev, devpriv->ai_calib_source | NI6143_CALIB_CHAN_RELAY_OFF,
		  NI6143_CALIB_CHAN_REG);
	ni_ग_लिखोw(dev, devpriv->ai_calib_source, NI6143_CALIB_CHAN_REG);
पूर्ण

अटल व्योम pcimio_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	mio_common_detach(dev);
	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);
	अगर (devpriv) अणु
		mite_मुक्त_ring(devpriv->ai_mite_ring);
		mite_मुक्त_ring(devpriv->ao_mite_ring);
		mite_मुक्त_ring(devpriv->cकरो_mite_ring);
		mite_मुक्त_ring(devpriv->gpct_mite_ring[0]);
		mite_मुक्त_ring(devpriv->gpct_mite_ring[1]);
		mite_detach(devpriv->mite);
	पूर्ण
	अगर (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disable(dev);
पूर्ण

अटल पूर्णांक pcimio_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा ni_board_काष्ठा *board = शून्य;
	काष्ठा ni_निजी *devpriv;
	अचिन्हित पूर्णांक irq;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(ni_boards))
		board = &ni_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	ret = ni_alloc_निजी(dev);
	अगर (ret)
		वापस ret;
	devpriv = dev->निजी;

	devpriv->mite = mite_attach(dev, false);	/* use win0 */
	अगर (!devpriv->mite)
		वापस -ENOMEM;

	अगर (board->reg_type & ni_reg_m_series_mask)
		devpriv->is_m_series = 1;
	अगर (board->reg_type & ni_reg_6xxx_mask)
		devpriv->is_6xxx = 1;
	अगर (board->reg_type == ni_reg_611x)
		devpriv->is_611x = 1;
	अगर (board->reg_type == ni_reg_6143)
		devpriv->is_6143 = 1;
	अगर (board->reg_type == ni_reg_622x)
		devpriv->is_622x = 1;
	अगर (board->reg_type == ni_reg_625x)
		devpriv->is_625x = 1;
	अगर (board->reg_type == ni_reg_628x)
		devpriv->is_628x = 1;
	अगर (board->reg_type & ni_reg_67xx_mask)
		devpriv->is_67xx = 1;
	अगर (board->reg_type == ni_reg_6711)
		devpriv->is_6711 = 1;
	अगर (board->reg_type == ni_reg_6713)
		devpriv->is_6713 = 1;

	devpriv->ai_mite_ring = mite_alloc_ring(devpriv->mite);
	अगर (!devpriv->ai_mite_ring)
		वापस -ENOMEM;
	devpriv->ao_mite_ring = mite_alloc_ring(devpriv->mite);
	अगर (!devpriv->ao_mite_ring)
		वापस -ENOMEM;
	devpriv->cकरो_mite_ring = mite_alloc_ring(devpriv->mite);
	अगर (!devpriv->cकरो_mite_ring)
		वापस -ENOMEM;
	devpriv->gpct_mite_ring[0] = mite_alloc_ring(devpriv->mite);
	अगर (!devpriv->gpct_mite_ring[0])
		वापस -ENOMEM;
	devpriv->gpct_mite_ring[1] = mite_alloc_ring(devpriv->mite);
	अगर (!devpriv->gpct_mite_ring[1])
		वापस -ENOMEM;

	अगर (devpriv->is_m_series)
		m_series_init_eeprom_buffer(dev);
	अगर (devpriv->is_6143)
		init_6143(dev);

	irq = pcidev->irq;
	अगर (irq) अणु
		ret = request_irq(irq, ni_E_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = irq;
	पूर्ण

	ret = ni_E_init(dev, 0, 1);
	अगर (ret < 0)
		वापस ret;

	dev->subdevices[NI_AI_SUBDEV].buf_change = &pcimio_ai_change;
	dev->subdevices[NI_AO_SUBDEV].buf_change = &pcimio_ao_change;
	dev->subdevices[NI_GPCT_SUBDEV(0)].buf_change = &pcimio_gpct0_change;
	dev->subdevices[NI_GPCT_SUBDEV(1)].buf_change = &pcimio_gpct1_change;
	dev->subdevices[NI_DIO_SUBDEV].buf_change = &pcimio_dio_change;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver ni_pcimio_driver = अणु
	.driver_name	= "ni_pcimio",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pcimio_स्वतः_attach,
	.detach		= pcimio_detach,
पूर्ण;

अटल पूर्णांक ni_pcimio_pci_probe(काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &ni_pcimio_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ni_pcimio_pci_table[] = अणु
	अणु PCI_VDEVICE(NI, 0x0162), BOARD_PCIMIO_16XE_50 पूर्ण,	/* 0x1620? */
	अणु PCI_VDEVICE(NI, 0x1170), BOARD_PCIMIO_16XE_10 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1180), BOARD_PCIMIO_16E_1 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1190), BOARD_PCIMIO_16E_4 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x11b0), BOARD_PXI6070E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x11c0), BOARD_PXI6040E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x11d0), BOARD_PXI6030E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1270), BOARD_PCI6032E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1330), BOARD_PCI6031E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1340), BOARD_PCI6033E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1350), BOARD_PCI6071E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x14e0), BOARD_PCI6110 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x14f0), BOARD_PCI6111 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1580), BOARD_PXI6031E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x15b0), BOARD_PXI6071E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1880), BOARD_PCI6711 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1870), BOARD_PCI6713 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x18b0), BOARD_PCI6052E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x18c0), BOARD_PXI6052E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2410), BOARD_PCI6733 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2420), BOARD_PXI6733 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2430), BOARD_PCI6731 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2890), BOARD_PCI6036E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x28c0), BOARD_PCI6014 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2a60), BOARD_PCI6023E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2a70), BOARD_PCI6024E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2a80), BOARD_PCI6025E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2ab0), BOARD_PXI6025E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2b80), BOARD_PXI6713 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2b90), BOARD_PXI6711 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2c80), BOARD_PCI6035E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2ca0), BOARD_PCI6034E पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70aa), BOARD_PCI6229 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70ab), BOARD_PCI6259 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70ac), BOARD_PCI6289 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70ad), BOARD_PXI6251 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70ae), BOARD_PXI6220 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70af), BOARD_PCI6221 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b0), BOARD_PCI6220 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b1), BOARD_PXI6229 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b2), BOARD_PXI6259 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b3), BOARD_PXI6289 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b4), BOARD_PCI6250 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b5), BOARD_PXI6221 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b6), BOARD_PCI6280 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b7), BOARD_PCI6254 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b8), BOARD_PCI6251 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70b9), BOARD_PXI6250 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70ba), BOARD_PXI6254 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70bb), BOARD_PXI6280 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70bc), BOARD_PCI6284 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70bd), BOARD_PCI6281 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70be), BOARD_PXI6284 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70bf), BOARD_PXI6281 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70c0), BOARD_PCI6143 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70f2), BOARD_PCI6224 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70f3), BOARD_PXI6224 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x710d), BOARD_PXI6143 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x716c), BOARD_PCI6225 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x716d), BOARD_PXI6225 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x717d), BOARD_PCIE6251 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x717f), BOARD_PCIE6259 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x71bc), BOARD_PCI6221_37PIN पूर्ण,
	अणु PCI_VDEVICE(NI, 0x72e8), BOARD_PXIE6251 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x72e9), BOARD_PXIE6259 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ni_pcimio_pci_table);

अटल काष्ठा pci_driver ni_pcimio_pci_driver = अणु
	.name		= "ni_pcimio",
	.id_table	= ni_pcimio_pci_table,
	.probe		= ni_pcimio_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(ni_pcimio_driver, ni_pcimio_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
