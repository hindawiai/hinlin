<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/prom.h>

व्योम of_parse_dma_winकरोw(काष्ठा device_node *dn, स्थिर __be32 *dma_winकरोw,
			 अचिन्हित दीर्घ *busno, अचिन्हित दीर्घ *phys,
			 अचिन्हित दीर्घ *size)
अणु
	u32 cells;
	स्थिर __be32 *prop;

	/* busno is always one cell */
	*busno = of_पढ़ो_number(dma_winकरोw, 1);
	dma_winकरोw++;

	prop = of_get_property(dn, "ibm,#dma-address-cells", शून्य);
	अगर (!prop)
		prop = of_get_property(dn, "#address-cells", शून्य);

	cells = prop ? of_पढ़ो_number(prop, 1) : of_n_addr_cells(dn);
	*phys = of_पढ़ो_number(dma_winकरोw, cells);

	dma_winकरोw += cells;

	prop = of_get_property(dn, "ibm,#dma-size-cells", शून्य);
	cells = prop ? of_पढ़ो_number(prop, 1) : of_n_size_cells(dn);
	*size = of_पढ़ो_number(dma_winकरोw, cells);
पूर्ण
