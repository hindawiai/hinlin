<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Low-level PCI config space access क्रम OLPC प्रणालीs who lack the VSA
 * PCI भवization software.
 *
 * Copyright तऊ 2006  Advanced Micro Devices, Inc.
 *
 * The AMD Geode chipset (ie: GX2 processor, cs5536 I/O companion device)
 * has some I/O functions (display, southbridge, sound, USB HCIs, etc)
 * that more or less behave like PCI devices, but the hardware करोesn't
 * directly implement the PCI configuration space headers.  AMD provides
 * "VSA" (Virtual System Architecture) software that emulates PCI config
 * space क्रम these devices, by trapping I/O accesses to PCI config रेजिस्टर
 * (CF8/CFC) and running some code in System Management Mode पूर्णांकerrupt state.
 * On the OLPC platक्रमm, we करोn't want to use that VSA code because
 * (a) it slows करोwn suspend/resume, and (b) recompiling it requires special
 * compilers that are hard to get.  So instead of letting the complex VSA
 * code simulate the PCI config रेजिस्टरs क्रम the on-chip devices, we
 * just simulate them the easy way, by inserting the code पूर्णांकo the
 * pci_ग_लिखो_config and pci_पढ़ो_config path.  Most of the config रेजिस्टरs
 * are पढ़ो-only anyway, so the bulk of the simulation is just table lookup.
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/olpc.h>
#समावेश <यंत्र/geode.h>
#समावेश <यंत्र/pci_x86.h>

/*
 * In the tables below, the first two line (8 दीर्घwords) are the
 * size masks that are used when the higher level PCI code determines
 * the size of the region by writing ~0 to a base address रेजिस्टर
 * and पढ़ोing back the result.
 *
 * The following lines are the values that are पढ़ो during normal
 * PCI config access cycles, i.e. not after just having written
 * ~0 to a base address रेजिस्टर.
 */

अटल स्थिर uपूर्णांक32_t lxnb_hdr[] = अणु  /* dev 1 function 0 - devfn = 8 */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x281022, 0x2200005, 0x6000021, 0x80f808,	/* AMD Venकरोr ID */
	0x0,	0x0,	0x0,	0x0,   /* No भव रेजिस्टरs, hence no BAR */
	0x0,	0x0,	0x0,	0x28100b,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
पूर्ण;

अटल स्थिर uपूर्णांक32_t gxnb_hdr[] = अणु  /* dev 1 function 0 - devfn = 8 */
	0xfffffffd, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x28100b, 0x2200005, 0x6000021, 0x80f808,	/* NSC Venकरोr ID */
	0xac1d,	0x0,	0x0,	0x0,  /* I/O BAR - base of भव रेजिस्टरs */
	0x0,	0x0,	0x0,	0x28100b,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lxfb_hdr[] = अणु  /* dev 1 function 1 - devfn = 9 */
	0xff000008, 0xffffc000, 0xffffc000, 0xffffc000,
	0xffffc000,	0x0,	0x0,	0x0,

	0x20811022, 0x2200003, 0x3000000, 0x0,		/* AMD Venकरोr ID */
	0xfd000000, 0xfe000000, 0xfe004000, 0xfe008000, /* FB, GP, VG, DF */
	0xfe00c000, 0x0, 0x0,	0x30100b,		/* VIP */
	0x0,	0x0,	0x0,	0x10e,	   /* INTA, IRQ14 क्रम graphics accel */
	0x0,	0x0,	0x0,	0x0,
	0x3d0,	0x3c0,	0xa0000, 0x0,	    /* VG IO, VG IO, EGA FB, MONO FB */
	0x0,	0x0,	0x0,	0x0,
पूर्ण;

अटल स्थिर uपूर्णांक32_t gxfb_hdr[] = अणु  /* dev 1 function 1 - devfn = 9 */
	0xff800008, 0xffffc000, 0xffffc000, 0xffffc000,
	0x0,	0x0,	0x0,	0x0,

	0x30100b, 0x2200003, 0x3000000, 0x0,		/* NSC Venकरोr ID */
	0xfd000000, 0xfe000000, 0xfe004000, 0xfe008000,	/* FB, GP, VG, DF */
	0x0,	0x0,	0x0,	0x30100b,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x3d0,	0x3c0,	0xa0000, 0x0,  	    /* VG IO, VG IO, EGA FB, MONO FB */
	0x0,	0x0,	0x0,	0x0,
पूर्ण;

अटल स्थिर uपूर्णांक32_t aes_hdr[] = अणु	/* dev 1 function 2 - devfn = 0xa */
	0xffffc000, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20821022, 0x2a00006, 0x10100000, 0x8,		/* NSC Venकरोr ID */
	0xfe010000, 0x0, 0x0,	0x0,			/* AES रेजिस्टरs */
	0x0,	0x0,	0x0,	0x20821022,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
पूर्ण;


अटल स्थिर uपूर्णांक32_t isa_hdr[] = अणु  /* dev f function 0 - devfn = 78 */
	0xfffffff9, 0xffffff01, 0xffffffc1, 0xffffffe1,
	0xffffff81, 0xffffffc1, 0x0, 0x0,

	0x20901022, 0x2a00049, 0x6010003, 0x802000,
	0x18b1,	0x1001,	0x1801,	0x1881,	/* SMB-8   GPIO-256 MFGPT-64  IRQ-32 */
	0x1401,	0x1841,	0x0,	0x20901022,		/* PMS-128 ACPI-64 */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0xaa5b,			/* IRQ steering */
	0x0,	0x0,	0x0,	0x0,
पूर्ण;

अटल स्थिर uपूर्णांक32_t ac97_hdr[] = अणु  /* dev f function 3 - devfn = 7b */
	0xffffff81, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20931022, 0x2a00041, 0x4010001, 0x0,
	0x1481,	0x0,	0x0,	0x0,			/* I/O BAR-128 */
	0x0,	0x0,	0x0,	0x20931022,
	0x0,	0x0,	0x0,	0x205,			/* IntB, IRQ5 */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
पूर्ण;

अटल स्थिर uपूर्णांक32_t ohci_hdr[] = अणु  /* dev f function 4 - devfn = 7c */
	0xfffff000, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20941022, 0x2300006, 0xc031002, 0x0,
	0xfe01a000, 0x0, 0x0,	0x0,			/* MEMBAR-1000 */
	0x0,	0x0,	0x0,	0x20941022,
	0x0,	0x40,	0x0,	0x40a,			/* CapPtr INT-D, IRQA */
	0xc8020001, 0x0, 0x0,	0x0,	/* Capabilities - 40 is R/O,
					   44 is mask 8103 (घातer control) */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
पूर्ण;

अटल स्थिर uपूर्णांक32_t ehci_hdr[] = अणु  /* dev f function 4 - devfn = 7d */
	0xfffff000, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20951022, 0x2300006, 0xc032002, 0x0,
	0xfe01b000, 0x0, 0x0,	0x0,			/* MEMBAR-1000 */
	0x0,	0x0,	0x0,	0x20951022,
	0x0,	0x40,	0x0,	0x40a,			/* CapPtr INT-D, IRQA */
	0xc8020001, 0x0, 0x0,	0x0,	/* Capabilities - 40 is R/O, 44 is
					   mask 8103 (घातer control) */
#अगर 0
	0x1,	0x40080000, 0x0, 0x0,	/* EECP - see EHCI spec section 2.1.7 */
#पूर्ण_अगर
	0x01000001, 0x0, 0x0,	0x0,	/* EECP - see EHCI spec section 2.1.7 */
	0x2020,	0x0,	0x0,	0x0,	/* (EHCI page 8) 60 SBRN (R/O),
					   61 FLADJ (R/W), PORTWAKECAP  */
पूर्ण;

अटल uपूर्णांक32_t ff_loc = ~0;
अटल uपूर्णांक32_t zero_loc;
अटल पूर्णांक bar_probing;		/* Set after a ग_लिखो of ~0 to a BAR */
अटल पूर्णांक is_lx;

#घोषणा NB_SLOT 0x1	/* Northbridge - GX chip - Device 1 */
#घोषणा SB_SLOT 0xf	/* Southbridge - CS5536 chip - Device F */

अटल पूर्णांक is_simulated(अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn)
अणु
	वापस (!bus && ((PCI_SLOT(devfn) == NB_SLOT) ||
			(PCI_SLOT(devfn) == SB_SLOT)));
पूर्ण

अटल uपूर्णांक32_t *hdr_addr(स्थिर uपूर्णांक32_t *hdr, पूर्णांक reg)
अणु
	uपूर्णांक32_t addr;

	/*
	 * This is a little bit tricky.  The header maps consist of
	 * 0x20 bytes of size masks, followed by 0x70 bytes of header data.
	 * In the normal हाल, when not probing a BAR's size, we want
	 * to access the header data, so we add 0x20 to the reg offset,
	 * thus skipping the size mask area.
	 * In the BAR probing हाल, we want to access the size mask क्रम
	 * the BAR, so we subtract 0x10 (the config header offset क्रम
	 * BAR0), and करोn't skip the size mask area.
	 */

	addr = (uपूर्णांक32_t)hdr + reg + (bar_probing ? -0x10 : 0x20);

	bar_probing = 0;
	वापस (uपूर्णांक32_t *)addr;
पूर्ण

अटल पूर्णांक pci_olpc_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
		अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, uपूर्णांक32_t *value)
अणु
	uपूर्णांक32_t *addr;

	WARN_ON(seg);

	/* Use the hardware mechanism क्रम non-simulated devices */
	अगर (!is_simulated(bus, devfn))
		वापस pci_direct_conf1.पढ़ो(seg, bus, devfn, reg, len, value);

	/*
	 * No device has config रेजिस्टरs past 0x70, so we save table space
	 * by not storing entries क्रम the nonexistent रेजिस्टरs
	 */
	अगर (reg >= 0x70)
		addr = &zero_loc;
	अन्यथा अणु
		चयन (devfn) अणु
		हाल  0x8:
			addr = hdr_addr(is_lx ? lxnb_hdr : gxnb_hdr, reg);
			अवरोध;
		हाल  0x9:
			addr = hdr_addr(is_lx ? lxfb_hdr : gxfb_hdr, reg);
			अवरोध;
		हाल  0xa:
			addr = is_lx ? hdr_addr(aes_hdr, reg) : &ff_loc;
			अवरोध;
		हाल 0x78:
			addr = hdr_addr(isa_hdr, reg);
			अवरोध;
		हाल 0x7b:
			addr = hdr_addr(ac97_hdr, reg);
			अवरोध;
		हाल 0x7c:
			addr = hdr_addr(ohci_hdr, reg);
			अवरोध;
		हाल 0x7d:
			addr = hdr_addr(ehci_hdr, reg);
			अवरोध;
		शेष:
			addr = &ff_loc;
			अवरोध;
		पूर्ण
	पूर्ण
	चयन (len) अणु
	हाल 1:
		*value = *(uपूर्णांक8_t *)addr;
		अवरोध;
	हाल 2:
		*value = *(uपूर्णांक16_t *)addr;
		अवरोध;
	हाल 4:
		*value = *addr;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_olpc_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
		अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, uपूर्णांक32_t value)
अणु
	WARN_ON(seg);

	/* Use the hardware mechanism क्रम non-simulated devices */
	अगर (!is_simulated(bus, devfn))
		वापस pci_direct_conf1.ग_लिखो(seg, bus, devfn, reg, len, value);

	/* XXX we may want to extend this to simulate EHCI घातer management */

	/*
	 * Mostly we just discard ग_लिखोs, but अगर the ग_लिखो is a size probe
	 * (i.e. writing ~0 to a BAR), we remember it and arrange to वापस
	 * the appropriate size mask on the next पढ़ो.  This is cheating
	 * to some extent, because it depends on the fact that the next
	 * access after such a ग_लिखो will always be a पढ़ो to the same BAR.
	 */

	अगर ((reg >= 0x10) && (reg < 0x2c)) अणु
		/* ग_लिखो is to a BAR */
		अगर (value == ~0)
			bar_probing = 1;
	पूर्ण अन्यथा अणु
		/*
		 * No warning on ग_लिखोs to ROM BAR, CMD, LATENCY_TIMER,
		 * CACHE_LINE_SIZE, or PM रेजिस्टरs.
		 */
		अगर ((reg != PCI_ROM_ADDRESS) && (reg != PCI_COMMAND_MASTER) &&
				(reg != PCI_LATENCY_TIMER) &&
				(reg != PCI_CACHE_LINE_SIZE) && (reg != 0x44))
			prपूर्णांकk(KERN_WARNING "OLPC PCI: Config write to devfn"
				" %x reg %x value %x\n", devfn, reg, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_raw_ops pci_olpc_conf = अणु
	.पढ़ो =	pci_olpc_पढ़ो,
	.ग_लिखो = pci_olpc_ग_लिखो,
पूर्ण;

पूर्णांक __init pci_olpc_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "PCI: Using configuration type OLPC XO-1\n");
	raw_pci_ops = &pci_olpc_conf;
	is_lx = is_geode_lx();
	वापस 0;
पूर्ण
