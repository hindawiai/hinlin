<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rsparser.c - parses and encodes pnpbios resource data streams
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/pnp.h>
#समावेश <linux/माला.स>

#अगर_घोषित CONFIG_PCI
#समावेश <linux/pci.h>
#अन्यथा
अंतरभूत व्योम pcibios_penalize_isa_irq(पूर्णांक irq, पूर्णांक active)
अणु
पूर्ण
#पूर्ण_अगर				/* CONFIG_PCI */

#समावेश "../base.h"
#समावेश "pnpbios.h"

/* standard resource tags */
#घोषणा SMALL_TAG_PNPVERNO		0x01
#घोषणा SMALL_TAG_LOGDEVID		0x02
#घोषणा SMALL_TAG_COMPATDEVID		0x03
#घोषणा SMALL_TAG_IRQ			0x04
#घोषणा SMALL_TAG_DMA			0x05
#घोषणा SMALL_TAG_STARTDEP		0x06
#घोषणा SMALL_TAG_ENDDEP		0x07
#घोषणा SMALL_TAG_PORT			0x08
#घोषणा SMALL_TAG_FIXEDPORT		0x09
#घोषणा SMALL_TAG_VENDOR		0x0e
#घोषणा SMALL_TAG_END			0x0f
#घोषणा LARGE_TAG			0x80
#घोषणा LARGE_TAG_MEM			0x81
#घोषणा LARGE_TAG_ANSISTR		0x82
#घोषणा LARGE_TAG_UNICODESTR		0x83
#घोषणा LARGE_TAG_VENDOR		0x84
#घोषणा LARGE_TAG_MEM32			0x85
#घोषणा LARGE_TAG_FIXEDMEM32		0x86

/*
 * Resource Data Stream Format:
 *
 * Allocated Resources (required)
 * end tag ->
 * Resource Configuration Options (optional)
 * end tag ->
 * Compitable Device IDs (optional)
 * final end tag ->
 */

/*
 * Allocated Resources
 */

अटल व्योम pnpbios_parse_allocated_ioresource(काष्ठा pnp_dev *dev,
					       पूर्णांक start, पूर्णांक len)
अणु
	पूर्णांक flags = 0;
	पूर्णांक end = start + len - 1;

	अगर (len <= 0 || end >= 0x10003)
		flags |= IORESOURCE_DISABLED;

	pnp_add_io_resource(dev, start, end, flags);
पूर्ण

अटल व्योम pnpbios_parse_allocated_memresource(काष्ठा pnp_dev *dev,
						पूर्णांक start, पूर्णांक len)
अणु
	पूर्णांक flags = 0;
	पूर्णांक end = start + len - 1;

	अगर (len <= 0)
		flags |= IORESOURCE_DISABLED;

	pnp_add_mem_resource(dev, start, end, flags);
पूर्ण

अटल अचिन्हित अक्षर *pnpbios_parse_allocated_resource_data(काष्ठा pnp_dev *dev,
							    अचिन्हित अक्षर *p,
							    अचिन्हित अक्षर *end)
अणु
	अचिन्हित पूर्णांक len, tag;
	पूर्णांक io, size, mask, i, flags;

	अगर (!p)
		वापस शून्य;

	pnp_dbg(&dev->dev, "parse allocated resources\n");

	pnp_init_resources(dev);

	जबतक ((अक्षर *)p < (अक्षर *)end) अणु

		/* determine the type of tag */
		अगर (p[0] & LARGE_TAG) अणु	/* large tag */
			len = (p[2] << 8) | p[1];
			tag = p[0];
		पूर्ण अन्यथा अणु	/* small tag */
			len = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		पूर्ण

		चयन (tag) अणु

		हाल LARGE_TAG_MEM:
			अगर (len != 9)
				जाओ len_err;
			io = *(लघु *)&p[4];
			size = *(लघु *)&p[10];
			pnpbios_parse_allocated_memresource(dev, io, size);
			अवरोध;

		हाल LARGE_TAG_ANSISTR:
			/* ignore this क्रम now */
			अवरोध;

		हाल LARGE_TAG_VENDOR:
			/* करो nothing */
			अवरोध;

		हाल LARGE_TAG_MEM32:
			अगर (len != 17)
				जाओ len_err;
			io = *(पूर्णांक *)&p[4];
			size = *(पूर्णांक *)&p[16];
			pnpbios_parse_allocated_memresource(dev, io, size);
			अवरोध;

		हाल LARGE_TAG_FIXEDMEM32:
			अगर (len != 9)
				जाओ len_err;
			io = *(पूर्णांक *)&p[4];
			size = *(पूर्णांक *)&p[8];
			pnpbios_parse_allocated_memresource(dev, io, size);
			अवरोध;

		हाल SMALL_TAG_IRQ:
			अगर (len < 2 || len > 3)
				जाओ len_err;
			flags = 0;
			io = -1;
			mask = p[1] + p[2] * 256;
			क्रम (i = 0; i < 16; i++, mask = mask >> 1)
				अगर (mask & 0x01)
					io = i;
			अगर (io != -1)
				pcibios_penalize_isa_irq(io, 1);
			अन्यथा
				flags = IORESOURCE_DISABLED;
			pnp_add_irq_resource(dev, io, flags);
			अवरोध;

		हाल SMALL_TAG_DMA:
			अगर (len != 2)
				जाओ len_err;
			flags = 0;
			io = -1;
			mask = p[1];
			क्रम (i = 0; i < 8; i++, mask = mask >> 1)
				अगर (mask & 0x01)
					io = i;
			अगर (io == -1)
				flags = IORESOURCE_DISABLED;
			pnp_add_dma_resource(dev, io, flags);
			अवरोध;

		हाल SMALL_TAG_PORT:
			अगर (len != 7)
				जाओ len_err;
			io = p[2] + p[3] * 256;
			size = p[7];
			pnpbios_parse_allocated_ioresource(dev, io, size);
			अवरोध;

		हाल SMALL_TAG_VENDOR:
			/* करो nothing */
			अवरोध;

		हाल SMALL_TAG_FIXEDPORT:
			अगर (len != 3)
				जाओ len_err;
			io = p[1] + p[2] * 256;
			size = p[3];
			pnpbios_parse_allocated_ioresource(dev, io, size);
			अवरोध;

		हाल SMALL_TAG_END:
			p = p + 2;
			वापस (अचिन्हित अक्षर *)p;
			अवरोध;

		शेष:	/* an unknown tag */
len_err:
			dev_err(&dev->dev, "unknown tag %#x length %d\n",
				tag, len);
			अवरोध;
		पूर्ण

		/* जारी to the next tag */
		अगर (p[0] & LARGE_TAG)
			p += len + 3;
		अन्यथा
			p += len + 1;
	पूर्ण

	dev_err(&dev->dev, "no end tag in resource structure\n");

	वापस शून्य;
पूर्ण

/*
 * Resource Configuration Options
 */

अटल __init व्योम pnpbios_parse_mem_option(काष्ठा pnp_dev *dev,
					    अचिन्हित अक्षर *p, पूर्णांक size,
					    अचिन्हित पूर्णांक option_flags)
अणु
	resource_माप_प्रकार min, max, align, len;
	अचिन्हित अक्षर flags;

	min = ((p[5] << 8) | p[4]) << 8;
	max = ((p[7] << 8) | p[6]) << 8;
	align = (p[9] << 8) | p[8];
	len = ((p[11] << 8) | p[10]) << 8;
	flags = p[3];
	pnp_रेजिस्टर_mem_resource(dev, option_flags, min, max, align, len,
				  flags);
पूर्ण

अटल __init व्योम pnpbios_parse_mem32_option(काष्ठा pnp_dev *dev,
					      अचिन्हित अक्षर *p, पूर्णांक size,
					      अचिन्हित पूर्णांक option_flags)
अणु
	resource_माप_प्रकार min, max, align, len;
	अचिन्हित अक्षर flags;

	min = (p[7] << 24) | (p[6] << 16) | (p[5] << 8) | p[4];
	max = (p[11] << 24) | (p[10] << 16) | (p[9] << 8) | p[8];
	align = (p[15] << 24) | (p[14] << 16) | (p[13] << 8) | p[12];
	len = (p[19] << 24) | (p[18] << 16) | (p[17] << 8) | p[16];
	flags = p[3];
	pnp_रेजिस्टर_mem_resource(dev, option_flags, min, max, align, len,
				  flags);
पूर्ण

अटल __init व्योम pnpbios_parse_fixed_mem32_option(काष्ठा pnp_dev *dev,
						    अचिन्हित अक्षर *p, पूर्णांक size,
						    अचिन्हित पूर्णांक option_flags)
अणु
	resource_माप_प्रकार base, len;
	अचिन्हित अक्षर flags;

	base = (p[7] << 24) | (p[6] << 16) | (p[5] << 8) | p[4];
	len = (p[11] << 24) | (p[10] << 16) | (p[9] << 8) | p[8];
	flags = p[3];
	pnp_रेजिस्टर_mem_resource(dev, option_flags, base, base, 0, len, flags);
पूर्ण

अटल __init व्योम pnpbios_parse_irq_option(काष्ठा pnp_dev *dev,
					    अचिन्हित अक्षर *p, पूर्णांक size,
					    अचिन्हित पूर्णांक option_flags)
अणु
	अचिन्हित दीर्घ bits;
	pnp_irq_mask_t map;
	अचिन्हित अक्षर flags = IORESOURCE_IRQ_HIGHEDGE;

	bits = (p[2] << 8) | p[1];

	biपंचांगap_zero(map.bits, PNP_IRQ_NR);
	biपंचांगap_copy(map.bits, &bits, 16);

	अगर (size > 2)
		flags = p[3];

	pnp_रेजिस्टर_irq_resource(dev, option_flags, &map, flags);
पूर्ण

अटल __init व्योम pnpbios_parse_dma_option(काष्ठा pnp_dev *dev,
					    अचिन्हित अक्षर *p, पूर्णांक size,
					    अचिन्हित पूर्णांक option_flags)
अणु
	pnp_रेजिस्टर_dma_resource(dev, option_flags, p[1], p[2]);
पूर्ण

अटल __init व्योम pnpbios_parse_port_option(काष्ठा pnp_dev *dev,
					     अचिन्हित अक्षर *p, पूर्णांक size,
					     अचिन्हित पूर्णांक option_flags)
अणु
	resource_माप_प्रकार min, max, align, len;
	अचिन्हित अक्षर flags;

	min = (p[3] << 8) | p[2];
	max = (p[5] << 8) | p[4];
	align = p[6];
	len = p[7];
	flags = p[1] ? IORESOURCE_IO_16BIT_ADDR : 0;
	pnp_रेजिस्टर_port_resource(dev, option_flags, min, max, align, len,
				   flags);
पूर्ण

अटल __init व्योम pnpbios_parse_fixed_port_option(काष्ठा pnp_dev *dev,
						   अचिन्हित अक्षर *p, पूर्णांक size,
						   अचिन्हित पूर्णांक option_flags)
अणु
	resource_माप_प्रकार base, len;

	base = (p[2] << 8) | p[1];
	len = p[3];
	pnp_रेजिस्टर_port_resource(dev, option_flags, base, base, 0, len,
				   IORESOURCE_IO_FIXED);
पूर्ण

अटल __init अचिन्हित अक्षर *
pnpbios_parse_resource_option_data(अचिन्हित अक्षर *p, अचिन्हित अक्षर *end,
				   काष्ठा pnp_dev *dev)
अणु
	अचिन्हित पूर्णांक len, tag;
	पूर्णांक priority;
	अचिन्हित पूर्णांक option_flags;

	अगर (!p)
		वापस शून्य;

	pnp_dbg(&dev->dev, "parse resource options\n");
	option_flags = 0;
	जबतक ((अक्षर *)p < (अक्षर *)end) अणु

		/* determine the type of tag */
		अगर (p[0] & LARGE_TAG) अणु	/* large tag */
			len = (p[2] << 8) | p[1];
			tag = p[0];
		पूर्ण अन्यथा अणु	/* small tag */
			len = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		पूर्ण

		चयन (tag) अणु

		हाल LARGE_TAG_MEM:
			अगर (len != 9)
				जाओ len_err;
			pnpbios_parse_mem_option(dev, p, len, option_flags);
			अवरोध;

		हाल LARGE_TAG_MEM32:
			अगर (len != 17)
				जाओ len_err;
			pnpbios_parse_mem32_option(dev, p, len, option_flags);
			अवरोध;

		हाल LARGE_TAG_FIXEDMEM32:
			अगर (len != 9)
				जाओ len_err;
			pnpbios_parse_fixed_mem32_option(dev, p, len,
							 option_flags);
			अवरोध;

		हाल SMALL_TAG_IRQ:
			अगर (len < 2 || len > 3)
				जाओ len_err;
			pnpbios_parse_irq_option(dev, p, len, option_flags);
			अवरोध;

		हाल SMALL_TAG_DMA:
			अगर (len != 2)
				जाओ len_err;
			pnpbios_parse_dma_option(dev, p, len, option_flags);
			अवरोध;

		हाल SMALL_TAG_PORT:
			अगर (len != 7)
				जाओ len_err;
			pnpbios_parse_port_option(dev, p, len, option_flags);
			अवरोध;

		हाल SMALL_TAG_VENDOR:
			/* करो nothing */
			अवरोध;

		हाल SMALL_TAG_FIXEDPORT:
			अगर (len != 3)
				जाओ len_err;
			pnpbios_parse_fixed_port_option(dev, p, len,
							option_flags);
			अवरोध;

		हाल SMALL_TAG_STARTDEP:
			अगर (len > 1)
				जाओ len_err;
			priority = PNP_RES_PRIORITY_ACCEPTABLE;
			अगर (len > 0)
				priority = p[1];
			option_flags = pnp_new_dependent_set(dev, priority);
			अवरोध;

		हाल SMALL_TAG_ENDDEP:
			अगर (len != 0)
				जाओ len_err;
			option_flags = 0;
			अवरोध;

		हाल SMALL_TAG_END:
			वापस p + 2;

		शेष:	/* an unknown tag */
len_err:
			dev_err(&dev->dev, "unknown tag %#x length %d\n",
				tag, len);
			अवरोध;
		पूर्ण

		/* जारी to the next tag */
		अगर (p[0] & LARGE_TAG)
			p += len + 3;
		अन्यथा
			p += len + 1;
	पूर्ण

	dev_err(&dev->dev, "no end tag in resource structure\n");

	वापस शून्य;
पूर्ण

/*
 * Compatible Device IDs
 */

अटल अचिन्हित अक्षर *pnpbios_parse_compatible_ids(अचिन्हित अक्षर *p,
						   अचिन्हित अक्षर *end,
						   काष्ठा pnp_dev *dev)
अणु
	पूर्णांक len, tag;
	u32 eisa_id;
	अक्षर id[8];
	काष्ठा pnp_id *dev_id;

	अगर (!p)
		वापस शून्य;

	जबतक ((अक्षर *)p < (अक्षर *)end) अणु

		/* determine the type of tag */
		अगर (p[0] & LARGE_TAG) अणु	/* large tag */
			len = (p[2] << 8) | p[1];
			tag = p[0];
		पूर्ण अन्यथा अणु	/* small tag */
			len = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		पूर्ण

		चयन (tag) अणु

		हाल LARGE_TAG_ANSISTR:
			म_नकलन(dev->name, p + 3,
				len >= PNP_NAME_LEN ? PNP_NAME_LEN - 2 : len);
			dev->name[len >=
				  PNP_NAME_LEN ? PNP_NAME_LEN - 1 : len] = '\0';
			अवरोध;

		हाल SMALL_TAG_COMPATDEVID:	/* compatible ID */
			अगर (len != 4)
				जाओ len_err;
			eisa_id = p[1] | p[2] << 8 | p[3] << 16 | p[4] << 24;
			pnp_eisa_id_to_string(eisa_id & PNP_EISA_ID_MASK, id);
			dev_id = pnp_add_id(dev, id);
			अगर (!dev_id)
				वापस शून्य;
			अवरोध;

		हाल SMALL_TAG_END:
			p = p + 2;
			वापस (अचिन्हित अक्षर *)p;
			अवरोध;

		शेष:	/* an unknown tag */
len_err:
			dev_err(&dev->dev, "unknown tag %#x length %d\n",
				tag, len);
			अवरोध;
		पूर्ण

		/* जारी to the next tag */
		अगर (p[0] & LARGE_TAG)
			p += len + 3;
		अन्यथा
			p += len + 1;
	पूर्ण

	dev_err(&dev->dev, "no end tag in resource structure\n");

	वापस शून्य;
पूर्ण

/*
 * Allocated Resource Encoding
 */

अटल व्योम pnpbios_encode_mem(काष्ठा pnp_dev *dev, अचिन्हित अक्षर *p,
			       काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ len;

	अगर (pnp_resource_enabled(res)) अणु
		base = res->start;
		len = resource_size(res);
	पूर्ण अन्यथा अणु
		base = 0;
		len = 0;
	पूर्ण

	p[4] = (base >> 8) & 0xff;
	p[5] = ((base >> 8) >> 8) & 0xff;
	p[6] = (base >> 8) & 0xff;
	p[7] = ((base >> 8) >> 8) & 0xff;
	p[10] = (len >> 8) & 0xff;
	p[11] = ((len >> 8) >> 8) & 0xff;

	pnp_dbg(&dev->dev, "  encode mem %#lx-%#lx\n", base, base + len - 1);
पूर्ण

अटल व्योम pnpbios_encode_mem32(काष्ठा pnp_dev *dev, अचिन्हित अक्षर *p,
				 काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ len;

	अगर (pnp_resource_enabled(res)) अणु
		base = res->start;
		len = resource_size(res);
	पूर्ण अन्यथा अणु
		base = 0;
		len = 0;
	पूर्ण

	p[4] = base & 0xff;
	p[5] = (base >> 8) & 0xff;
	p[6] = (base >> 16) & 0xff;
	p[7] = (base >> 24) & 0xff;
	p[8] = base & 0xff;
	p[9] = (base >> 8) & 0xff;
	p[10] = (base >> 16) & 0xff;
	p[11] = (base >> 24) & 0xff;
	p[16] = len & 0xff;
	p[17] = (len >> 8) & 0xff;
	p[18] = (len >> 16) & 0xff;
	p[19] = (len >> 24) & 0xff;

	pnp_dbg(&dev->dev, "  encode mem32 %#lx-%#lx\n", base, base + len - 1);
पूर्ण

अटल व्योम pnpbios_encode_fixed_mem32(काष्ठा pnp_dev *dev, अचिन्हित अक्षर *p,
				       काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ len;

	अगर (pnp_resource_enabled(res)) अणु
		base = res->start;
		len = resource_size(res);
	पूर्ण अन्यथा अणु
		base = 0;
		len = 0;
	पूर्ण

	p[4] = base & 0xff;
	p[5] = (base >> 8) & 0xff;
	p[6] = (base >> 16) & 0xff;
	p[7] = (base >> 24) & 0xff;
	p[8] = len & 0xff;
	p[9] = (len >> 8) & 0xff;
	p[10] = (len >> 16) & 0xff;
	p[11] = (len >> 24) & 0xff;

	pnp_dbg(&dev->dev, "  encode fixed_mem32 %#lx-%#lx\n", base,
		base + len - 1);
पूर्ण

अटल व्योम pnpbios_encode_irq(काष्ठा pnp_dev *dev, अचिन्हित अक्षर *p,
			       काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ map;

	अगर (pnp_resource_enabled(res))
		map = 1 << res->start;
	अन्यथा
		map = 0;

	p[1] = map & 0xff;
	p[2] = (map >> 8) & 0xff;

	pnp_dbg(&dev->dev, "  encode irq mask %#lx\n", map);
पूर्ण

अटल व्योम pnpbios_encode_dma(काष्ठा pnp_dev *dev, अचिन्हित अक्षर *p,
			       काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ map;

	अगर (pnp_resource_enabled(res))
		map = 1 << res->start;
	अन्यथा
		map = 0;

	p[1] = map & 0xff;

	pnp_dbg(&dev->dev, "  encode dma mask %#lx\n", map);
पूर्ण

अटल व्योम pnpbios_encode_port(काष्ठा pnp_dev *dev, अचिन्हित अक्षर *p,
				काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ len;

	अगर (pnp_resource_enabled(res)) अणु
		base = res->start;
		len = resource_size(res);
	पूर्ण अन्यथा अणु
		base = 0;
		len = 0;
	पूर्ण

	p[2] = base & 0xff;
	p[3] = (base >> 8) & 0xff;
	p[4] = base & 0xff;
	p[5] = (base >> 8) & 0xff;
	p[7] = len & 0xff;

	pnp_dbg(&dev->dev, "  encode io %#lx-%#lx\n", base, base + len - 1);
पूर्ण

अटल व्योम pnpbios_encode_fixed_port(काष्ठा pnp_dev *dev, अचिन्हित अक्षर *p,
				      काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ base = res->start;
	अचिन्हित दीर्घ len = resource_size(res);

	अगर (pnp_resource_enabled(res)) अणु
		base = res->start;
		len = resource_size(res);
	पूर्ण अन्यथा अणु
		base = 0;
		len = 0;
	पूर्ण

	p[1] = base & 0xff;
	p[2] = (base >> 8) & 0xff;
	p[3] = len & 0xff;

	pnp_dbg(&dev->dev, "  encode fixed_io %#lx-%#lx\n", base,
		base + len - 1);
पूर्ण

अटल अचिन्हित अक्षर *pnpbios_encode_allocated_resource_data(काष्ठा pnp_dev
								*dev,
							     अचिन्हित अक्षर *p,
							     अचिन्हित अक्षर *end)
अणु
	अचिन्हित पूर्णांक len, tag;
	पूर्णांक port = 0, irq = 0, dma = 0, mem = 0;

	अगर (!p)
		वापस शून्य;

	जबतक ((अक्षर *)p < (अक्षर *)end) अणु

		/* determine the type of tag */
		अगर (p[0] & LARGE_TAG) अणु	/* large tag */
			len = (p[2] << 8) | p[1];
			tag = p[0];
		पूर्ण अन्यथा अणु	/* small tag */
			len = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		पूर्ण

		चयन (tag) अणु

		हाल LARGE_TAG_MEM:
			अगर (len != 9)
				जाओ len_err;
			pnpbios_encode_mem(dev, p,
				pnp_get_resource(dev, IORESOURCE_MEM, mem));
			mem++;
			अवरोध;

		हाल LARGE_TAG_MEM32:
			अगर (len != 17)
				जाओ len_err;
			pnpbios_encode_mem32(dev, p,
				pnp_get_resource(dev, IORESOURCE_MEM, mem));
			mem++;
			अवरोध;

		हाल LARGE_TAG_FIXEDMEM32:
			अगर (len != 9)
				जाओ len_err;
			pnpbios_encode_fixed_mem32(dev, p,
				pnp_get_resource(dev, IORESOURCE_MEM, mem));
			mem++;
			अवरोध;

		हाल SMALL_TAG_IRQ:
			अगर (len < 2 || len > 3)
				जाओ len_err;
			pnpbios_encode_irq(dev, p,
				pnp_get_resource(dev, IORESOURCE_IRQ, irq));
			irq++;
			अवरोध;

		हाल SMALL_TAG_DMA:
			अगर (len != 2)
				जाओ len_err;
			pnpbios_encode_dma(dev, p,
				pnp_get_resource(dev, IORESOURCE_DMA, dma));
			dma++;
			अवरोध;

		हाल SMALL_TAG_PORT:
			अगर (len != 7)
				जाओ len_err;
			pnpbios_encode_port(dev, p,
				pnp_get_resource(dev, IORESOURCE_IO, port));
			port++;
			अवरोध;

		हाल SMALL_TAG_VENDOR:
			/* करो nothing */
			अवरोध;

		हाल SMALL_TAG_FIXEDPORT:
			अगर (len != 3)
				जाओ len_err;
			pnpbios_encode_fixed_port(dev, p,
				pnp_get_resource(dev, IORESOURCE_IO, port));
			port++;
			अवरोध;

		हाल SMALL_TAG_END:
			p = p + 2;
			वापस (अचिन्हित अक्षर *)p;
			अवरोध;

		शेष:	/* an unknown tag */
len_err:
			dev_err(&dev->dev, "unknown tag %#x length %d\n",
				tag, len);
			अवरोध;
		पूर्ण

		/* जारी to the next tag */
		अगर (p[0] & LARGE_TAG)
			p += len + 3;
		अन्यथा
			p += len + 1;
	पूर्ण

	dev_err(&dev->dev, "no end tag in resource structure\n");

	वापस शून्य;
पूर्ण

/*
 * Core Parsing Functions
 */

पूर्णांक __init pnpbios_parse_data_stream(काष्ठा pnp_dev *dev,
					काष्ठा pnp_bios_node *node)
अणु
	अचिन्हित अक्षर *p = (अक्षर *)node->data;
	अचिन्हित अक्षर *end = (अक्षर *)(node->data + node->size);

	p = pnpbios_parse_allocated_resource_data(dev, p, end);
	अगर (!p)
		वापस -EIO;
	p = pnpbios_parse_resource_option_data(p, end, dev);
	अगर (!p)
		वापस -EIO;
	p = pnpbios_parse_compatible_ids(p, end, dev);
	अगर (!p)
		वापस -EIO;
	वापस 0;
पूर्ण

पूर्णांक pnpbios_पढ़ो_resources_from_node(काष्ठा pnp_dev *dev,
				     काष्ठा pnp_bios_node *node)
अणु
	अचिन्हित अक्षर *p = (अक्षर *)node->data;
	अचिन्हित अक्षर *end = (अक्षर *)(node->data + node->size);

	p = pnpbios_parse_allocated_resource_data(dev, p, end);
	अगर (!p)
		वापस -EIO;
	वापस 0;
पूर्ण

पूर्णांक pnpbios_ग_लिखो_resources_to_node(काष्ठा pnp_dev *dev,
				    काष्ठा pnp_bios_node *node)
अणु
	अचिन्हित अक्षर *p = (अक्षर *)node->data;
	अचिन्हित अक्षर *end = (अक्षर *)(node->data + node->size);

	p = pnpbios_encode_allocated_resource_data(dev, p, end);
	अगर (!p)
		वापस -EIO;
	वापस 0;
पूर्ण
