<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005 IBM Corporation
 *
 * Authors:
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * These dअगरference are required on घातer because the device must be
 * discovered through the device tree and iomap must be used to get
 * around the need क्रम holes in the io_page_mask.  This करोes not happen
 * स्वतःmatically because the tpm is not a normal pci device and lives
 * under the root node.
 */

काष्ठा tpm_aपंचांगel_priv अणु
	पूर्णांक region_size;
	पूर्णांक have_region;
	अचिन्हित दीर्घ base;
	व्योम __iomem *iobase;
पूर्ण;

#अगर_घोषित CONFIG_PPC64

#समावेश <यंत्र/prom.h>

#घोषणा aपंचांगel_getb(priv, offset) पढ़ोb(priv->iobase + offset)
#घोषणा aपंचांगel_putb(val, priv, offset) ग_लिखोb(val, priv->iobase + offset)
#घोषणा aपंचांगel_request_region request_mem_region
#घोषणा aपंचांगel_release_region release_mem_region

अटल अंतरभूत व्योम aपंचांगel_put_base_addr(व्योम __iomem *iobase)
अणु
	iounmap(iobase);
पूर्ण

अटल व्योम __iomem * aपंचांगel_get_base_addr(अचिन्हित दीर्घ *base, पूर्णांक *region_size)
अणु
	काष्ठा device_node *dn;
	अचिन्हित दीर्घ address, size;
	स्थिर अचिन्हित पूर्णांक *reg;
	पूर्णांक reglen;
	पूर्णांक naddrc;
	पूर्णांक nsizec;

	dn = of_find_node_by_name(शून्य, "tpm");

	अगर (!dn)
		वापस शून्य;

	अगर (!of_device_is_compatible(dn, "AT97SC3201")) अणु
		of_node_put(dn);
		वापस शून्य;
	पूर्ण

	reg = of_get_property(dn, "reg", &reglen);
	naddrc = of_n_addr_cells(dn);
	nsizec = of_n_size_cells(dn);

	of_node_put(dn);


	अगर (naddrc == 2)
		address = ((अचिन्हित दीर्घ) reg[0] << 32) | reg[1];
	अन्यथा
		address = reg[0];

	अगर (nsizec == 2)
		size =
		    ((अचिन्हित दीर्घ) reg[naddrc] << 32) | reg[naddrc + 1];
	अन्यथा
		size = reg[naddrc];

	*base = address;
	*region_size = size;
	वापस ioremap(*base, *region_size);
पूर्ण
#अन्यथा
#घोषणा aपंचांगel_getb(chip, offset) inb(aपंचांगel_get_priv(chip)->base + offset)
#घोषणा aपंचांगel_putb(val, chip, offset) \
	outb(val, aपंचांगel_get_priv(chip)->base + offset)
#घोषणा aपंचांगel_request_region request_region
#घोषणा aपंचांगel_release_region release_region
/* Aपंचांगel definitions */
क्रमागत tpm_aपंचांगel_addr अणु
	TPM_ATMEL_BASE_ADDR_LO = 0x08,
	TPM_ATMEL_BASE_ADDR_HI = 0x09
पूर्ण;

अटल अंतरभूत पूर्णांक tpm_पढ़ो_index(पूर्णांक base, पूर्णांक index)
अणु
	outb(index, base);
	वापस inb(base+1) & 0xFF;
पूर्ण

/* Verअगरy this is a 1.1 Aपंचांगel TPM */
अटल पूर्णांक aपंचांगel_verअगरy_tpm11(व्योम)
अणु

	/* verअगरy that it is an Aपंचांगel part */
	अगर (tpm_पढ़ो_index(TPM_ADDR, 4) != 'A' ||
	    tpm_पढ़ो_index(TPM_ADDR, 5) != 'T' ||
	    tpm_पढ़ो_index(TPM_ADDR, 6) != 'M' ||
	    tpm_पढ़ो_index(TPM_ADDR, 7) != 'L')
		वापस 1;

	/* query chip क्रम its version number */
	अगर (tpm_पढ़ो_index(TPM_ADDR, 0x00) != 1 ||
	    tpm_पढ़ो_index(TPM_ADDR, 0x01) != 1)
		वापस 1;

	/* This is an aपंचांगel supported part */
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_put_base_addr(व्योम __iomem *iobase)
अणु
पूर्ण

/* Determine where to talk to device */
अटल व्योम __iomem * aपंचांगel_get_base_addr(अचिन्हित दीर्घ *base, पूर्णांक *region_size)
अणु
	पूर्णांक lo, hi;

	अगर (aपंचांगel_verअगरy_tpm11() != 0)
		वापस शून्य;

	lo = tpm_पढ़ो_index(TPM_ADDR, TPM_ATMEL_BASE_ADDR_LO);
	hi = tpm_पढ़ो_index(TPM_ADDR, TPM_ATMEL_BASE_ADDR_HI);

	*base = (hi << 8) | lo;
	*region_size = 2;

	वापस ioport_map(*base, *region_size);
पूर्ण
#पूर्ण_अगर
