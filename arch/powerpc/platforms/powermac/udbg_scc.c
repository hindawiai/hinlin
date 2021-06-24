<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * udbg क्रम zilog scc ports as found on Apple PowerMacs
 *
 * Copyright (C) 2001-2005 PPC 64 Team, IBM Corp
 */
#समावेश <linux/types.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmac_feature.h>

बाह्य u8 real_पढ़ोb(अस्थिर u8 __iomem  *addr);
बाह्य व्योम real_ग_लिखोb(u8 data, अस्थिर u8 __iomem *addr);

#घोषणा	SCC_TXRDY	4
#घोषणा SCC_RXRDY	1

अटल अस्थिर u8 __iomem *sccc;
अटल अस्थिर u8 __iomem *sccd;

अटल व्योम udbg_scc_अ_दो(अक्षर c)
अणु
	अगर (sccc) अणु
		जबतक ((in_8(sccc) & SCC_TXRDY) == 0)
			;
		out_8(sccd,  c);
		अगर (c == '\n')
			udbg_scc_अ_दो('\r');
	पूर्ण
पूर्ण

अटल पूर्णांक udbg_scc_अ_लो_poll(व्योम)
अणु
	अगर (sccc) अणु
		अगर ((in_8(sccc) & SCC_RXRDY) != 0)
			वापस in_8(sccd);
		अन्यथा
			वापस -1;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक udbg_scc_अ_लो(व्योम)
अणु
	अगर (sccc) अणु
		जबतक ((in_8(sccc) & SCC_RXRDY) == 0)
			;
		वापस in_8(sccd);
	पूर्ण
	वापस -1;
पूर्ण

अटल अचिन्हित अक्षर scc_inittab[] = अणु
    13, 0,		/* set baud rate भागisor */
    12, 0,
    14, 1,		/* baud rate gen enable, src=rtxc */
    11, 0x50,		/* घड़ीs = br gen */
    5,  0xea,		/* tx 8 bits, निश्चित DTR & RTS */
    4,  0x46,		/* x16 घड़ी, 1 stop */
    3,  0xc1,		/* rx enable, 8 bits */
पूर्ण;

व्योम udbg_scc_init(पूर्णांक क्रमce_scc)
अणु
	स्थिर u32 *reg;
	अचिन्हित दीर्घ addr;
	काष्ठा device_node *मानक_निकास = शून्य, *escc = शून्य, *macio = शून्य;
	काष्ठा device_node *ch, *ch_def = शून्य, *ch_a = शून्य;
	स्थिर अक्षर *path;
	पूर्णांक i;

	escc = of_find_node_by_name(शून्य, "escc");
	अगर (escc == शून्य)
		जाओ bail;
	macio = of_get_parent(escc);
	अगर (macio == शून्य)
		जाओ bail;
	path = of_get_property(of_chosen, "linux,stdout-path", शून्य);
	अगर (path != शून्य)
		मानक_निकास = of_find_node_by_path(path);
	क्रम_each_child_of_node(escc, ch) अणु
		अगर (ch == मानक_निकास)
			ch_def = of_node_get(ch);
		अगर (of_node_name_eq(ch, "ch-a"))
			ch_a = of_node_get(ch);
	पूर्ण
	अगर (ch_def == शून्य && !क्रमce_scc)
		जाओ bail;

	ch = ch_def ? ch_def : ch_a;

	/* Get address within mac-io ASIC */
	reg = of_get_property(escc, "reg", शून्य);
	अगर (reg == शून्य)
		जाओ bail;
	addr = reg[0];

	/* Get address of mac-io PCI itself */
	reg = of_get_property(macio, "assigned-addresses", शून्य);
	अगर (reg == शून्य)
		जाओ bail;
	addr += reg[2];

	/* Lock the serial port */
	pmac_call_feature(PMAC_FTR_SCC_ENABLE, ch,
			  PMAC_SCC_ASYNC | PMAC_SCC_FLAG_XMON, 1);

	अगर (ch == ch_a)
		addr += 0x20;
	sccc = ioremap(addr & PAGE_MASK, PAGE_SIZE) ;
	sccc += addr & ~PAGE_MASK;
	sccd = sccc + 0x10;

	mb();

	क्रम (i = 20000; i != 0; --i)
		in_8(sccc);
	out_8(sccc, 0x09);		/* reset A or B side */
	out_8(sccc, 0xc0);

	/* If SCC was the OF output port, पढ़ो the BRG value, अन्यथा
	 * Setup क्रम 38400 or 57600 8N1 depending on the machine
	 */
	अगर (ch_def != शून्य) अणु
		out_8(sccc, 13);
		scc_inittab[1] = in_8(sccc);
		out_8(sccc, 12);
		scc_inittab[3] = in_8(sccc);
	पूर्ण अन्यथा अगर (of_machine_is_compatible("RackMac1,1")
		   || of_machine_is_compatible("RackMac1,2")
		   || of_machine_is_compatible("MacRISC4")) अणु
		/* Xserves and G5s शेष to 57600 */
		scc_inittab[1] = 0;
		scc_inittab[3] = 0;
	पूर्ण अन्यथा अणु
		/* Others शेष to 38400 */
		scc_inittab[1] = 0;
		scc_inittab[3] = 1;
	पूर्ण

	क्रम (i = 0; i < माप(scc_inittab); ++i)
		out_8(sccc, scc_inittab[i]);


	udbg_अ_दो = udbg_scc_अ_दो;
	udbg_अ_लो = udbg_scc_अ_लो;
	udbg_अ_लो_poll = udbg_scc_अ_लो_poll;

	udbg_माला_दो("Hello World !\n");

 bail:
	of_node_put(macio);
	of_node_put(escc);
	of_node_put(मानक_निकास);
	of_node_put(ch_def);
	of_node_put(ch_a);
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम udbg_real_scc_अ_दो(अक्षर c)
अणु
	जबतक ((real_पढ़ोb(sccc) & SCC_TXRDY) == 0)
		;
	real_ग_लिखोb(c, sccd);
	अगर (c == '\n')
		udbg_real_scc_अ_दो('\r');
पूर्ण

व्योम __init udbg_init_pmac_realmode(व्योम)
अणु
	sccc = (अस्थिर u8 __iomem *)0x80013020ul;
	sccd = (अस्थिर u8 __iomem *)0x80013030ul;

	udbg_अ_दो = udbg_real_scc_अ_दो;
	udbg_अ_लो = शून्य;
	udbg_अ_लो_poll = शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */
