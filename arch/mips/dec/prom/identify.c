<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * identअगरy.c: machine identअगरication code.
 *
 * Copyright (C) 1998 Harald Koerfgen and Paul M. Antoine
 * Copyright (C) 2002, 2003, 2004, 2005  Maciej W. Rozycki
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/bootinfo.h>

#समावेश <यंत्र/dec/ioasic.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>
#समावेश <यंत्र/dec/kn01.h>
#समावेश <यंत्र/dec/kn02.h>
#समावेश <यंत्र/dec/kn02ba.h>
#समावेश <यंत्र/dec/kn02ca.h>
#समावेश <यंत्र/dec/kn03.h>
#समावेश <यंत्र/dec/kn230.h>
#समावेश <यंत्र/dec/prom.h>
#समावेश <यंत्र/dec/प्रणाली.h>

#समावेश "dectypes.h"

अटल स्थिर अक्षर *dec_प्रणाली_strings[] = अणु
	[MACH_DSUNKNOWN]	"unknown DECstation",
	[MACH_DS23100]		"DECstation 2100/3100",
	[MACH_DS5100]		"DECsystem 5100",
	[MACH_DS5000_200]	"DECstation 5000/200",
	[MACH_DS5000_1XX]	"DECstation 5000/1xx",
	[MACH_DS5000_XX]	"Personal DECstation 5000/xx",
	[MACH_DS5000_2X0]	"DECstation 5000/2x0",
	[MACH_DS5400]		"DECsystem 5400",
	[MACH_DS5500]		"DECsystem 5500",
	[MACH_DS5800]		"DECsystem 5800",
	[MACH_DS5900]		"DECsystem 5900",
पूर्ण;

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
#घोषणा STR_BUF_LEN	64
	अटल अक्षर प्रणाली[STR_BUF_LEN];
	अटल पूर्णांक called = 0;

	अगर (called == 0) अणु
		called = 1;
		snम_लिखो(प्रणाली, STR_BUF_LEN, "Digital %s",
			 dec_प्रणाली_strings[mips_machtype]);
	पूर्ण

	वापस प्रणाली;
पूर्ण


/*
 * Setup essential प्रणाली-specअगरic memory addresses.  We need them
 * early.  Semantically the functions beदीर्घ to prom/init.c, but they
 * are compact enough we want them अंतरभूतd. --macro
 */
अस्थिर u8 *dec_rtc_base;

EXPORT_SYMBOL(dec_rtc_base);

अटल अंतरभूत व्योम prom_init_kn01(व्योम)
अणु
	dec_kn_slot_base = KN01_SLOT_BASE;
	dec_kn_slot_size = KN01_SLOT_SIZE;

	dec_rtc_base = (व्योम *)CKSEG1ADDR(dec_kn_slot_base + KN01_RTC);
पूर्ण

अटल अंतरभूत व्योम prom_init_kn230(व्योम)
अणु
	dec_kn_slot_base = KN01_SLOT_BASE;
	dec_kn_slot_size = KN01_SLOT_SIZE;

	dec_rtc_base = (व्योम *)CKSEG1ADDR(dec_kn_slot_base + KN01_RTC);
पूर्ण

अटल अंतरभूत व्योम prom_init_kn02(व्योम)
अणु
	dec_kn_slot_base = KN02_SLOT_BASE;
	dec_kn_slot_size = KN02_SLOT_SIZE;
	dec_tc_bus = 1;

	dec_rtc_base = (व्योम *)CKSEG1ADDR(dec_kn_slot_base + KN02_RTC);
पूर्ण

अटल अंतरभूत व्योम prom_init_kn02xa(व्योम)
अणु
	dec_kn_slot_base = KN02XA_SLOT_BASE;
	dec_kn_slot_size = IOASIC_SLOT_SIZE;
	dec_tc_bus = 1;

	ioasic_base = (व्योम *)CKSEG1ADDR(dec_kn_slot_base + IOASIC_IOCTL);
	dec_rtc_base = (व्योम *)CKSEG1ADDR(dec_kn_slot_base + IOASIC_TOY);
पूर्ण

अटल अंतरभूत व्योम prom_init_kn03(व्योम)
अणु
	dec_kn_slot_base = KN03_SLOT_BASE;
	dec_kn_slot_size = IOASIC_SLOT_SIZE;
	dec_tc_bus = 1;

	ioasic_base = (व्योम *)CKSEG1ADDR(dec_kn_slot_base + IOASIC_IOCTL);
	dec_rtc_base = (व्योम *)CKSEG1ADDR(dec_kn_slot_base + IOASIC_TOY);
पूर्ण


व्योम __init prom_identअगरy_arch(u32 magic)
अणु
	अचिन्हित अक्षर dec_cpunum, dec_firmrev, dec_etc, dec_systype;
	u32 dec_sysid;

	अगर (!prom_is_rex(magic)) अणु
		dec_sysid = simple_म_से_अदीर्घ(prom_दो_पर्या("systype"),
					   (अक्षर **)0, 0);
	पूर्ण अन्यथा अणु
		dec_sysid = rex_माला_लोysid();
		अगर (dec_sysid == 0) अणु
			prपूर्णांकk("Zero sysid returned from PROM! "
			       "Assuming a PMAX-like machine.\n");
			dec_sysid = 1;
		पूर्ण
	पूर्ण

	dec_cpunum = (dec_sysid & 0xff000000) >> 24;
	dec_systype = (dec_sysid & 0xff0000) >> 16;
	dec_firmrev = (dec_sysid & 0xff00) >> 8;
	dec_etc = dec_sysid & 0xff;

	/*
	 * FIXME: This may not be an exhaustive list of DECStations/Servers!
	 * Put all model-specअगरic initialisation calls here.
	 */
	चयन (dec_systype) अणु
	हाल DS2100_3100:
		mips_machtype = MACH_DS23100;
		prom_init_kn01();
		अवरोध;
	हाल DS5100:		/* DS5100 MIPSMATE */
		mips_machtype = MACH_DS5100;
		prom_init_kn230();
		अवरोध;
	हाल DS5000_200:	/* DS5000 3max */
		mips_machtype = MACH_DS5000_200;
		prom_init_kn02();
		अवरोध;
	हाल DS5000_1XX:	/* DS5000/100 3min */
		mips_machtype = MACH_DS5000_1XX;
		prom_init_kn02xa();
		अवरोध;
	हाल DS5000_2X0:	/* DS5000/240 3max+ or DS5900 bigmax */
		mips_machtype = MACH_DS5000_2X0;
		prom_init_kn03();
		अगर (!(ioasic_पढ़ो(IO_REG_SIR) & KN03_IO_INR_3MAXP))
			mips_machtype = MACH_DS5900;
		अवरोध;
	हाल DS5000_XX:		/* Personal DS5000/xx maxine */
		mips_machtype = MACH_DS5000_XX;
		prom_init_kn02xa();
		अवरोध;
	हाल DS5800:		/* DS5800 Isis */
		mips_machtype = MACH_DS5800;
		अवरोध;
	हाल DS5400:		/* DS5400 MIPSfair */
		mips_machtype = MACH_DS5400;
		अवरोध;
	हाल DS5500:		/* DS5500 MIPSfair-2 */
		mips_machtype = MACH_DS5500;
		अवरोध;
	शेष:
		mips_machtype = MACH_DSUNKNOWN;
		अवरोध;
	पूर्ण

	अगर (mips_machtype == MACH_DSUNKNOWN)
		prपूर्णांकk("This is an %s, id is %x\n",
		       dec_प्रणाली_strings[mips_machtype], dec_systype);
	अन्यथा
		prपूर्णांकk("This is a %s\n", dec_प्रणाली_strings[mips_machtype]);
पूर्ण
