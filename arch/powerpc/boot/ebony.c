<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2007 David Gibson, IBM Corporation.
 *
 * Based on earlier code:
 *   Copyright (C) Paul Mackerras 1997.
 *
 *   Matt Porter <mporter@kernel.crashing.org>
 *   Copyright 2002-2005 MontaVista Software Inc.
 *
 *   Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *   Copyright (c) 2003, 2004 Zultys Technologies
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"
#समावेश "reg.h"
#समावेश "io.h"
#समावेश "dcr.h"
#समावेश "4xx.h"
#समावेश "44x.h"

अटल u8 *ebony_mac0, *ebony_mac1;

#घोषणा EBONY_FPGA_PATH		"/plb/opb/ebc/fpga"
#घोषणा	EBONY_FPGA_FLASH_SEL	0x01
#घोषणा EBONY_SMALL_FLASH_PATH	"/plb/opb/ebc/small-flash"

अटल व्योम ebony_flashsel_fixup(व्योम)
अणु
	व्योम *devp;
	u32 reg[3] = अणु0x0, 0x0, 0x80000पूर्ण;
	u8 *fpga;
	u8 fpga_reg0 = 0x0;

	devp = finddevice(EBONY_FPGA_PATH);
	अगर (!devp)
		fatal("Couldn't locate FPGA node %s\n\r", EBONY_FPGA_PATH);

	अगर (getprop(devp, "virtual-reg", &fpga, माप(fpga)) != माप(fpga))
		fatal("%s has missing or invalid virtual-reg property\n\r",
		      EBONY_FPGA_PATH);

	fpga_reg0 = in_8(fpga);

	devp = finddevice(EBONY_SMALL_FLASH_PATH);
	अगर (!devp)
		fatal("Couldn't locate small flash node %s\n\r",
		      EBONY_SMALL_FLASH_PATH);

	अगर (getprop(devp, "reg", reg, माप(reg)) != माप(reg))
		fatal("%s has reg property of unexpected size\n\r",
		      EBONY_SMALL_FLASH_PATH);

	/* Invert address bit 14 (IBM-endian) अगर FLASH_SEL fpga bit is set */
	अगर (fpga_reg0 & EBONY_FPGA_FLASH_SEL)
		reg[1] ^= 0x80000;

	setprop(devp, "reg", reg, माप(reg));
पूर्ण

अटल व्योम ebony_fixups(व्योम)
अणु
	// FIXME: sysclk should be derived by पढ़ोing the FPGA रेजिस्टरs
	अचिन्हित दीर्घ sysclk = 33000000;

	ibm440gp_fixup_घड़ीs(sysclk, 6 * 1843200);
	ibm4xx_sdram_fixup_memsize();
	dt_fixup_mac_address_by_alias("ethernet0", ebony_mac0);
	dt_fixup_mac_address_by_alias("ethernet1", ebony_mac1);
	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
	ebony_flashsel_fixup();
पूर्ण

व्योम ebony_init(व्योम *mac0, व्योम *mac1)
अणु
	platक्रमm_ops.fixups = ebony_fixups;
	platक्रमm_ops.निकास = ibm44x_dbcr_reset;
	ebony_mac0 = mac0;
	ebony_mac1 = mac1;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
