<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation
 */
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_scd.h>

अचिन्हित पूर्णांक sb1_pass;
अचिन्हित पूर्णांक soc_pass;
अचिन्हित पूर्णांक soc_type;
EXPORT_SYMBOL(soc_type);
अचिन्हित पूर्णांक periph_rev;
EXPORT_SYMBOL_GPL(periph_rev);
अचिन्हित पूर्णांक zbbus_mhz;
EXPORT_SYMBOL(zbbus_mhz);

अटल अक्षर *soc_str;
अटल अक्षर *pass_str;
अटल अचिन्हित पूर्णांक war_pass;	/* XXXKW करोn't overload PASS defines? */

अटल पूर्णांक __init setup_bcm1250(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (soc_pass) अणु
	हाल K_SYS_REVISION_BCM1250_PASS1:
		periph_rev = 1;
		pass_str = "Pass 1";
		अवरोध;
	हाल K_SYS_REVISION_BCM1250_A10:
		periph_rev = 2;
		pass_str = "A8/A10";
		/* XXXKW dअगरferent war_pass? */
		war_pass = K_SYS_REVISION_BCM1250_PASS2;
		अवरोध;
	हाल K_SYS_REVISION_BCM1250_PASS2_2:
		periph_rev = 2;
		pass_str = "B1";
		अवरोध;
	हाल K_SYS_REVISION_BCM1250_B2:
		periph_rev = 2;
		pass_str = "B2";
		war_pass = K_SYS_REVISION_BCM1250_PASS2_2;
		अवरोध;
	हाल K_SYS_REVISION_BCM1250_PASS3:
		periph_rev = 3;
		pass_str = "C0";
		अवरोध;
	हाल K_SYS_REVISION_BCM1250_C1:
		periph_rev = 3;
		pass_str = "C1";
		अवरोध;
	शेष:
		अगर (soc_pass < K_SYS_REVISION_BCM1250_PASS2_2) अणु
			periph_rev = 2;
			pass_str = "A0-A6";
			war_pass = K_SYS_REVISION_BCM1250_PASS2;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("Unknown BCM1250 rev %x\n", soc_pass);
			ret = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक sb1250_m3_workaround_needed(व्योम)
अणु
	चयन (soc_type) अणु
	हाल K_SYS_SOC_TYPE_BCM1250:
	हाल K_SYS_SOC_TYPE_BCM1250_ALT:
	हाल K_SYS_SOC_TYPE_BCM1250_ALT2:
	हाल K_SYS_SOC_TYPE_BCM1125:
	हाल K_SYS_SOC_TYPE_BCM1125H:
		वापस soc_pass < K_SYS_REVISION_BCM1250_C0;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक __init setup_bcm112x(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (soc_pass) अणु
	हाल 0:
		/* Early build didn't have revid set */
		periph_rev = 3;
		pass_str = "A1";
		war_pass = K_SYS_REVISION_BCM112x_A1;
		अवरोध;
	हाल K_SYS_REVISION_BCM112x_A1:
		periph_rev = 3;
		pass_str = "A1";
		अवरोध;
	हाल K_SYS_REVISION_BCM112x_A2:
		periph_rev = 3;
		pass_str = "A2";
		अवरोध;
	हाल K_SYS_REVISION_BCM112x_A3:
		periph_rev = 3;
		pass_str = "A3";
		अवरोध;
	हाल K_SYS_REVISION_BCM112x_A4:
		periph_rev = 3;
		pass_str = "A4";
		अवरोध;
	हाल K_SYS_REVISION_BCM112x_B0:
		periph_rev = 3;
		pass_str = "B0";
		अवरोध;
	शेष:
		prपूर्णांकk("Unknown %s rev %x\n", soc_str, soc_pass);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

/* Setup code likely to be common to all SiByte platक्रमms */

अटल पूर्णांक __init sys_rev_decode(व्योम)
अणु
	पूर्णांक ret = 0;

	war_pass = soc_pass;
	चयन (soc_type) अणु
	हाल K_SYS_SOC_TYPE_BCM1250:
	हाल K_SYS_SOC_TYPE_BCM1250_ALT:
	हाल K_SYS_SOC_TYPE_BCM1250_ALT2:
		soc_str = "BCM1250";
		ret = setup_bcm1250();
		अवरोध;
	हाल K_SYS_SOC_TYPE_BCM1120:
		soc_str = "BCM1120";
		ret = setup_bcm112x();
		अवरोध;
	हाल K_SYS_SOC_TYPE_BCM1125:
		soc_str = "BCM1125";
		ret = setup_bcm112x();
		अवरोध;
	हाल K_SYS_SOC_TYPE_BCM1125H:
		soc_str = "BCM1125H";
		ret = setup_bcm112x();
		अवरोध;
	शेष:
		prपूर्णांकk("Unknown SOC type %x\n", soc_type);
		ret = 1;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम __init sb1250_setup(व्योम)
अणु
	uपूर्णांक64_t sys_rev;
	पूर्णांक plद_भाग;
	पूर्णांक bad_config = 0;

	sb1_pass = पढ़ो_c0_prid() & PRID_REV_MASK;
	sys_rev = __raw_पढ़ोq(IOADDR(A_SCD_SYSTEM_REVISION));
	soc_type = SYS_SOC_TYPE(sys_rev);
	soc_pass = G_SYS_REVISION(sys_rev);

	अगर (sys_rev_decode()) अणु
		prपूर्णांकk("Restart after failure to identify SiByte chip\n");
		machine_restart(शून्य);
	पूर्ण

	plद_भाग = G_SYS_PLL_DIV(__raw_पढ़ोq(IOADDR(A_SCD_SYSTEM_CFG)));
	zbbus_mhz = ((plद_भाग >> 1) * 50) + ((plद_भाग & 1) * 25);

	prपूर्णांकk("Broadcom SiByte %s %s @ %d MHz (SB1 rev %d)\n",
		    soc_str, pass_str, zbbus_mhz * 2, sb1_pass);
	prपूर्णांकk("Board type: %s\n", get_प्रणाली_type());

	चयन (war_pass) अणु
	हाल K_SYS_REVISION_BCM1250_PASS1:
		prपूर्णांकk("@@@@ This is a BCM1250 A0-A2 (Pass 1) board, "
			    "and the kernel doesn't have the proper "
			    "workarounds compiled in. @@@@\n");
		bad_config = 1;
		अवरोध;
	हाल K_SYS_REVISION_BCM1250_PASS2:
		/* Pass 2 - easiest as शेष क्रम now - so many numbers */
#अगर !defined(CONFIG_SB1_PASS_2_WORKAROUNDS) || \
    !defined(CONFIG_SB1_PASS_2_1_WORKAROUNDS)
		prपूर्णांकk("@@@@ This is a BCM1250 A3-A10 board, and the "
			    "kernel doesn't have the proper workarounds "
			    "compiled in. @@@@\n");
		bad_config = 1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_HAS_PREFETCH
		prपूर्णांकk("@@@@ Prefetches may be enabled in this kernel, "
			    "but are buggy on this board.  @@@@\n");
		bad_config = 1;
#पूर्ण_अगर
		अवरोध;
	हाल K_SYS_REVISION_BCM1250_PASS2_2:
#अगर_अघोषित CONFIG_SB1_PASS_2_WORKAROUNDS
		prपूर्णांकk("@@@@ This is a BCM1250 B1/B2. board, and the "
			    "kernel doesn't have the proper workarounds "
			    "compiled in. @@@@\n");
		bad_config = 1;
#पूर्ण_अगर
#अगर defined(CONFIG_SB1_PASS_2_1_WORKAROUNDS) || \
    !defined(CONFIG_CPU_HAS_PREFETCH)
		prपूर्णांकk("@@@@ This is a BCM1250 B1/B2, but the kernel is "
			    "conservatively configured for an 'A' stepping. "
			    "@@@@\n");
#पूर्ण_अगर
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (bad_config) अणु
		prपूर्णांकk("Invalid configuration for this chip.\n");
		machine_restart(शून्य);
	पूर्ण
पूर्ण
