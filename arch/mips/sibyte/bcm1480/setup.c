<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000,2001,2002,2003,2004 Broadcom Corporation
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/reboot.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sibyte/sb1250.h>

#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_scd.h>
#समावेश <यंत्र/sibyte/sb1250_scd.h>

अचिन्हित पूर्णांक sb1_pass;
अचिन्हित पूर्णांक soc_pass;
अचिन्हित पूर्णांक soc_type;
EXPORT_SYMBOL(soc_type);
अचिन्हित पूर्णांक periph_rev;
EXPORT_SYMBOL_GPL(periph_rev);
अचिन्हित पूर्णांक zbbus_mhz;
EXPORT_SYMBOL(zbbus_mhz);

अटल अचिन्हित पूर्णांक part_type;

अटल अक्षर *soc_str;
अटल अक्षर *pass_str;

अटल पूर्णांक __init setup_bcm1x80_bcm1x55(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (soc_pass) अणु
	हाल K_SYS_REVISION_BCM1480_S0:
		periph_rev = 1;
		pass_str = "S0 (pass1)";
		अवरोध;
	हाल K_SYS_REVISION_BCM1480_A1:
		periph_rev = 1;
		pass_str = "A1 (pass1)";
		अवरोध;
	हाल K_SYS_REVISION_BCM1480_A2:
		periph_rev = 1;
		pass_str = "A2 (pass1)";
		अवरोध;
	हाल K_SYS_REVISION_BCM1480_A3:
		periph_rev = 1;
		pass_str = "A3 (pass1)";
		अवरोध;
	हाल K_SYS_REVISION_BCM1480_B0:
		periph_rev = 1;
		pass_str = "B0 (pass2)";
		अवरोध;
	शेष:
		prपूर्णांकk("Unknown %s rev %x\n", soc_str, soc_pass);
		periph_rev = 1;
		pass_str = "Unknown Revision";
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Setup code likely to be common to all SiByte platक्रमms */

अटल पूर्णांक __init sys_rev_decode(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (soc_type) अणु
	हाल K_SYS_SOC_TYPE_BCM1x80:
		अगर (part_type == K_SYS_PART_BCM1480)
		    soc_str = "BCM1480";
		अन्यथा अगर (part_type == K_SYS_PART_BCM1280)
		    soc_str = "BCM1280";
		अन्यथा
		    soc_str = "BCM1x80";
		ret = setup_bcm1x80_bcm1x55();
		अवरोध;

	हाल K_SYS_SOC_TYPE_BCM1x55:
		अगर (part_type == K_SYS_PART_BCM1455)
		    soc_str = "BCM1455";
		अन्यथा अगर (part_type == K_SYS_PART_BCM1255)
		    soc_str = "BCM1255";
		अन्यथा
		    soc_str = "BCM1x55";
		ret = setup_bcm1x80_bcm1x55();
		अवरोध;

	शेष:
		prपूर्णांकk("Unknown part type %x\n", part_type);
		ret = 1;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम __init bcm1480_setup(व्योम)
अणु
	uपूर्णांक64_t sys_rev;
	पूर्णांक plद_भाग;

	sb1_pass = पढ़ो_c0_prid() & PRID_REV_MASK;
	sys_rev = __raw_पढ़ोq(IOADDR(A_SCD_SYSTEM_REVISION));
	soc_type = SYS_SOC_TYPE(sys_rev);
	part_type = G_SYS_PART(sys_rev);
	soc_pass = G_SYS_REVISION(sys_rev);

	अगर (sys_rev_decode()) अणु
		prपूर्णांकk("Restart after failure to identify SiByte chip\n");
		machine_restart(शून्य);
	पूर्ण

	plद_भाग = G_BCM1480_SYS_PLL_DIV(__raw_पढ़ोq(IOADDR(A_SCD_SYSTEM_CFG)));
	zbbus_mhz = ((plद_भाग >> 1) * 50) + ((plद_भाग & 1) * 25);

	prपूर्णांकk("Broadcom SiByte %s %s @ %d MHz (SB-1A rev %d)\n",
		    soc_str, pass_str, zbbus_mhz * 2, sb1_pass);
	prपूर्णांकk("Board type: %s\n", get_प्रणाली_type());
पूर्ण
