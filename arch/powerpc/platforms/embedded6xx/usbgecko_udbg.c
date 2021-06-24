<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/embedded6xx/usbgecko_udbg.c
 *
 * udbg serial input/output routines क्रम the USB Gecko adapter.
 * Copyright (C) 2008-2009 The GameCube Linux Team
 * Copyright (C) 2008,2009 Albert Herranz
 */

#समावेश <mm/mmu_decl.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/fixmap.h>

#समावेश "usbgecko_udbg.h"


#घोषणा EXI_CLK_32MHZ           5

#घोषणा EXI_CSR                 0x00
#घोषणा   EXI_CSR_CLKMASK       (0x7<<4)
#घोषणा     EXI_CSR_CLK_32MHZ   (EXI_CLK_32MHZ<<4)
#घोषणा   EXI_CSR_CSMASK        (0x7<<7)
#घोषणा     EXI_CSR_CS_0        (0x1<<7)  /* Chip Select 001 */

#घोषणा EXI_CR                  0x0c
#घोषणा   EXI_CR_TSTART         (1<<0)
#घोषणा   EXI_CR_WRITE		(1<<2)
#घोषणा   EXI_CR_READ_WRITE     (2<<2)
#घोषणा   EXI_CR_TLEN(len)      (((len)-1)<<4)

#घोषणा EXI_DATA                0x10

#घोषणा UG_READ_ATTEMPTS	100
#घोषणा UG_WRITE_ATTEMPTS	100


अटल व्योम __iomem *ug_io_base;

/*
 * Perक्रमms one input/output transaction between the exi host and the usbgecko.
 */
अटल u32 ug_io_transaction(u32 in)
अणु
	u32 __iomem *csr_reg = ug_io_base + EXI_CSR;
	u32 __iomem *data_reg = ug_io_base + EXI_DATA;
	u32 __iomem *cr_reg = ug_io_base + EXI_CR;
	u32 csr, data, cr;

	/* select */
	csr = EXI_CSR_CLK_32MHZ | EXI_CSR_CS_0;
	out_be32(csr_reg, csr);

	/* पढ़ो/ग_लिखो */
	data = in;
	out_be32(data_reg, data);
	cr = EXI_CR_TLEN(2) | EXI_CR_READ_WRITE | EXI_CR_TSTART;
	out_be32(cr_reg, cr);

	जबतक (in_be32(cr_reg) & EXI_CR_TSTART)
		barrier();

	/* deselect */
	out_be32(csr_reg, 0);

	/* result */
	data = in_be32(data_reg);

	वापस data;
पूर्ण

/*
 * Returns true अगर an usbgecko adapter is found.
 */
अटल पूर्णांक ug_is_adapter_present(व्योम)
अणु
	अगर (!ug_io_base)
		वापस 0;

	वापस ug_io_transaction(0x90000000) == 0x04700000;
पूर्ण

/*
 * Returns true अगर the TX fअगरo is पढ़ोy क्रम transmission.
 */
अटल पूर्णांक ug_is_txfअगरo_पढ़ोy(व्योम)
अणु
	वापस ug_io_transaction(0xc0000000) & 0x04000000;
पूर्ण

/*
 * Tries to transmit a अक्षरacter.
 * If the TX fअगरo is not पढ़ोy the result is undefined.
 */
अटल व्योम ug_raw_अ_दो(अक्षर ch)
अणु
	ug_io_transaction(0xb0000000 | (ch << 20));
पूर्ण

/*
 * Transmits a अक्षरacter.
 * It silently fails अगर the TX fअगरo is not पढ़ोy after a number of retries.
 */
अटल व्योम ug_अ_दो(अक्षर ch)
अणु
	पूर्णांक count = UG_WRITE_ATTEMPTS;

	अगर (!ug_io_base)
		वापस;

	अगर (ch == '\n')
		ug_अ_दो('\r');

	जबतक (!ug_is_txfअगरo_पढ़ोy() && count--)
		barrier();
	अगर (count >= 0)
		ug_raw_अ_दो(ch);
पूर्ण

/*
 * Returns true अगर the RX fअगरo is पढ़ोy क्रम transmission.
 */
अटल पूर्णांक ug_is_rxfअगरo_पढ़ोy(व्योम)
अणु
	वापस ug_io_transaction(0xd0000000) & 0x04000000;
पूर्ण

/*
 * Tries to receive a अक्षरacter.
 * If a अक्षरacter is unavailable the function वापसs -1.
 */
अटल पूर्णांक ug_raw_अ_लो(व्योम)
अणु
	u32 data = ug_io_transaction(0xa0000000);
	अगर (data & 0x08000000)
		वापस (data >> 16) & 0xff;
	अन्यथा
		वापस -1;
पूर्ण

/*
 * Receives a अक्षरacter.
 * It fails अगर the RX fअगरo is not पढ़ोy after a number of retries.
 */
अटल पूर्णांक ug_अ_लो(व्योम)
अणु
	पूर्णांक count = UG_READ_ATTEMPTS;

	अगर (!ug_io_base)
		वापस -1;

	जबतक (!ug_is_rxfअगरo_पढ़ोy() && count--)
		barrier();
	वापस ug_raw_अ_लो();
पूर्ण

/*
 * udbg functions.
 *
 */

/*
 * Transmits a अक्षरacter.
 */
अटल व्योम ug_udbg_अ_दो(अक्षर ch)
अणु
	ug_अ_दो(ch);
पूर्ण

/*
 * Receives a अक्षरacter. Waits until a अक्षरacter is available.
 */
अटल पूर्णांक ug_udbg_अ_लो(व्योम)
अणु
	पूर्णांक ch;

	जबतक ((ch = ug_अ_लो()) == -1)
		barrier();
	वापस ch;
पूर्ण

/*
 * Receives a अक्षरacter. If a अक्षरacter is not available, वापसs -1.
 */
अटल पूर्णांक ug_udbg_अ_लो_poll(व्योम)
अणु
	अगर (!ug_is_rxfअगरo_पढ़ोy())
		वापस -1;
	वापस ug_अ_लो();
पूर्ण

/*
 * Retrieves and prepares the भव address needed to access the hardware.
 */
अटल व्योम __iomem *ug_udbg_setup_exi_io_base(काष्ठा device_node *np)
अणु
	व्योम __iomem *exi_io_base = शून्य;
	phys_addr_t paddr;
	स्थिर अचिन्हित पूर्णांक *reg;

	reg = of_get_property(np, "reg", शून्य);
	अगर (reg) अणु
		paddr = of_translate_address(np, reg);
		अगर (paddr)
			exi_io_base = ioremap(paddr, reg[1]);
	पूर्ण
	वापस exi_io_base;
पूर्ण

/*
 * Checks अगर a USB Gecko adapter is inserted in any memory card slot.
 */
अटल व्योम __iomem *ug_udbg_probe(व्योम __iomem *exi_io_base)
अणु
	पूर्णांक i;

	/* look क्रम a usbgecko on memcard slots A and B */
	क्रम (i = 0; i < 2; i++) अणु
		ug_io_base = exi_io_base + 0x14 * i;
		अगर (ug_is_adapter_present())
			अवरोध;
	पूर्ण
	अगर (i == 2)
		ug_io_base = शून्य;
	वापस ug_io_base;

पूर्ण

/*
 * USB Gecko udbg support initialization.
 */
व्योम __init ug_udbg_init(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *exi_io_base;

	अगर (ug_io_base)
		udbg_म_लिखो("%s: early -> final\n", __func__);

	np = of_find_compatible_node(शून्य, शून्य, "nintendo,flipper-exi");
	अगर (!np) अणु
		udbg_म_लिखो("%s: EXI node not found\n", __func__);
		जाओ out;
	पूर्ण

	exi_io_base = ug_udbg_setup_exi_io_base(np);
	अगर (!exi_io_base) अणु
		udbg_म_लिखो("%s: failed to setup EXI io base\n", __func__);
		जाओ करोne;
	पूर्ण

	अगर (!ug_udbg_probe(exi_io_base)) अणु
		udbg_म_लिखो("usbgecko_udbg: not found\n");
		iounmap(exi_io_base);
	पूर्ण अन्यथा अणु
		udbg_अ_दो = ug_udbg_अ_दो;
		udbg_अ_लो = ug_udbg_अ_लो;
		udbg_अ_लो_poll = ug_udbg_अ_लो_poll;
		udbg_म_लिखो("usbgecko_udbg: ready\n");
	पूर्ण

करोne:
	of_node_put(np);
out:
	वापस;
पूर्ण

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_USBGECKO

अटल phys_addr_t __init ug_early_grab_io_addr(व्योम)
अणु
#अगर defined(CONFIG_GAMECUBE)
	वापस 0x0c000000;
#या_अगर defined(CONFIG_WII)
	वापस 0x0d000000;
#अन्यथा
#त्रुटि Invalid platक्रमm क्रम USB Gecko based early debugging.
#पूर्ण_अगर
पूर्ण

/*
 * USB Gecko early debug support initialization क्रम udbg.
 */
व्योम __init udbg_init_usbgecko(व्योम)
अणु
	व्योम __iomem *early_debug_area;
	व्योम __iomem *exi_io_base;

	/*
	 * At this poपूर्णांक we have a BAT alपढ़ोy setup that enables I/O
	 * to the EXI hardware.
	 *
	 * The BAT uses a भव address range reserved at the fixmap.
	 * This must match the भव address configured in
	 * head_32.S:setup_usbgecko_bat().
	 */
	early_debug_area = (व्योम __iomem *)__fix_to_virt(FIX_EARLY_DEBUG_BASE);
	exi_io_base = early_debug_area + 0x00006800;

	/* try to detect a USB Gecko */
	अगर (!ug_udbg_probe(exi_io_base))
		वापस;

	/* we found a USB Gecko, load udbg hooks */
	udbg_अ_दो = ug_udbg_अ_दो;
	udbg_अ_लो = ug_udbg_अ_लो;
	udbg_अ_लो_poll = ug_udbg_अ_लो_poll;

	/*
	 * Prepare again the same BAT क्रम MMU_init.
	 * This allows udbg I/O to जारी working after the MMU is
	 * turned on क्रम real.
	 * It is safe to जारी using the same भव address as it is
	 * a reserved fixmap area.
	 */
	setbat(1, (अचिन्हित दीर्घ)early_debug_area,
	       ug_early_grab_io_addr(), 128*1024, PAGE_KERNEL_NCG);
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_USBGECKO */

