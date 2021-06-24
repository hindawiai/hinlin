<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/mcb.h>

#समावेश "mcb-internal.h"

काष्ठा mcb_parse_priv अणु
	phys_addr_t mapbase;
	व्योम __iomem *base;
पूर्ण;

#घोषणा क्रम_each_chameleon_cell(dtype, p)	\
	क्रम ((dtype) = get_next_dtype((p));	\
	     (dtype) != CHAMELEON_DTYPE_END;	\
	     (dtype) = get_next_dtype((p)))

अटल अंतरभूत uपूर्णांक32_t get_next_dtype(व्योम __iomem *p)
अणु
	uपूर्णांक32_t dtype;

	dtype = पढ़ोl(p);
	वापस dtype >> 28;
पूर्ण

अटल पूर्णांक chameleon_parse_bdd(काष्ठा mcb_bus *bus,
			काष्ठा chameleon_bar *cb,
			व्योम __iomem *base)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक chameleon_parse_gdd(काष्ठा mcb_bus *bus,
			काष्ठा chameleon_bar *cb,
			व्योम __iomem *base, पूर्णांक bar_count)
अणु
	काष्ठा chameleon_gdd __iomem *gdd =
		(काष्ठा chameleon_gdd __iomem *) base;
	काष्ठा mcb_device *mdev;
	u32 dev_mapbase;
	u32 offset;
	u32 size;
	पूर्णांक ret;
	__le32 reg1;
	__le32 reg2;

	mdev = mcb_alloc_dev(bus);
	अगर (!mdev)
		वापस -ENOMEM;

	reg1 = पढ़ोl(&gdd->reg1);
	reg2 = पढ़ोl(&gdd->reg2);
	offset = पढ़ोl(&gdd->offset);
	size = पढ़ोl(&gdd->size);

	mdev->id = GDD_DEV(reg1);
	mdev->rev = GDD_REV(reg1);
	mdev->var = GDD_VAR(reg1);
	mdev->bar = GDD_BAR(reg2);
	mdev->group = GDD_GRP(reg2);
	mdev->inst = GDD_INS(reg2);

	/*
	 * If the BAR is missing, dev_mapbase is zero, or अगर the
	 * device is IO mapped we just prपूर्णांक a warning and go on with the
	 * next device, instead of completely stop the gdd parser
	 */
	अगर (mdev->bar > bar_count - 1) अणु
		pr_info("No BAR for 16z%03d\n", mdev->id);
		ret = 0;
		जाओ err;
	पूर्ण

	dev_mapbase = cb[mdev->bar].addr;
	अगर (!dev_mapbase) अणु
		pr_info("BAR not assigned for 16z%03d\n", mdev->id);
		ret = 0;
		जाओ err;
	पूर्ण

	अगर (dev_mapbase & 0x01) अणु
		pr_info("IO mapped Device (16z%03d) not yet supported\n",
			mdev->id);
		ret = 0;
		जाओ err;
	पूर्ण

	pr_debug("Found a 16z%03d\n", mdev->id);

	mdev->irq.start = GDD_IRQ(reg1);
	mdev->irq.end = GDD_IRQ(reg1);
	mdev->irq.flags = IORESOURCE_IRQ;

	mdev->mem.start = dev_mapbase + offset;

	mdev->mem.end = mdev->mem.start + size - 1;
	mdev->mem.flags = IORESOURCE_MEM;

	mdev->is_added = false;

	ret = mcb_device_रेजिस्टर(bus, mdev);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	mcb_मुक्त_dev(mdev);

	वापस ret;
पूर्ण

अटल व्योम chameleon_parse_bar(व्योम __iomem *base,
				काष्ठा chameleon_bar *cb, पूर्णांक bar_count)
अणु
	अक्षर __iomem *p = base;
	पूर्णांक i;

	/* skip reg1 */
	p += माप(__le32);

	क्रम (i = 0; i < bar_count; i++) अणु
		cb[i].addr = पढ़ोl(p);
		cb[i].size = पढ़ोl(p + 4);

		p += माप(काष्ठा chameleon_bar);
	पूर्ण
पूर्ण

अटल पूर्णांक chameleon_get_bar(अक्षर __iomem **base, phys_addr_t mapbase,
			     काष्ठा chameleon_bar **cb)
अणु
	काष्ठा chameleon_bar *c;
	पूर्णांक bar_count;
	__le32 reg;
	u32 dtype;

	/*
	 * For those devices which are not connected
	 * to the PCI Bus (e.g. LPC) there is a bar
	 * descriptor located directly after the
	 * chameleon header. This header is comparable
	 * to a PCI header.
	 */
	dtype = get_next_dtype(*base);
	अगर (dtype == CHAMELEON_DTYPE_BAR) अणु
		reg = पढ़ोl(*base);

		bar_count = BAR_CNT(reg);
		अगर (bar_count <= 0 || bar_count > CHAMELEON_BAR_MAX)
			वापस -ENODEV;

		c = kसुस्मृति(bar_count, माप(काष्ठा chameleon_bar),
			    GFP_KERNEL);
		अगर (!c)
			वापस -ENOMEM;

		chameleon_parse_bar(*base, c, bar_count);
		*base += BAR_DESC_SIZE(bar_count);
	पूर्ण अन्यथा अणु
		c = kzalloc(माप(काष्ठा chameleon_bar), GFP_KERNEL);
		अगर (!c)
			वापस -ENOMEM;

		bar_count = 1;
		c->addr = mapbase;
	पूर्ण

	*cb = c;

	वापस bar_count;
पूर्ण

पूर्णांक chameleon_parse_cells(काष्ठा mcb_bus *bus, phys_addr_t mapbase,
			व्योम __iomem *base)
अणु
	काष्ठा chameleon_fpga_header *header;
	काष्ठा chameleon_bar *cb;
	अक्षर __iomem *p = base;
	पूर्णांक num_cells = 0;
	uपूर्णांक32_t dtype;
	पूर्णांक bar_count;
	पूर्णांक ret;
	u32 hsize;

	hsize = माप(काष्ठा chameleon_fpga_header);

	header = kzalloc(hsize, GFP_KERNEL);
	अगर (!header)
		वापस -ENOMEM;

	/* Extract header inक्रमmation */
	स_नकल_fromio(header, p, hsize);
	/* We only support chameleon v2 at the moment */
	header->magic = le16_to_cpu(header->magic);
	अगर (header->magic != CHAMELEONV2_MAGIC) अणु
		pr_err("Unsupported chameleon version 0x%x\n",
				header->magic);
		ret = -ENODEV;
		जाओ मुक्त_header;
	पूर्ण
	p += hsize;

	bus->revision = header->revision;
	bus->model = header->model;
	bus->minor = header->minor;
	snम_लिखो(bus->name, CHAMELEON_खाताNAME_LEN + 1, "%s",
		 header->filename);

	bar_count = chameleon_get_bar(&p, mapbase, &cb);
	अगर (bar_count < 0) अणु
		ret = bar_count;
		जाओ मुक्त_header;
	पूर्ण

	क्रम_each_chameleon_cell(dtype, p) अणु
		चयन (dtype) अणु
		हाल CHAMELEON_DTYPE_GENERAL:
			ret = chameleon_parse_gdd(bus, cb, p, bar_count);
			अगर (ret < 0)
				जाओ मुक्त_bar;
			p += माप(काष्ठा chameleon_gdd);
			अवरोध;
		हाल CHAMELEON_DTYPE_BRIDGE:
			chameleon_parse_bdd(bus, cb, p);
			p += माप(काष्ठा chameleon_bdd);
			अवरोध;
		हाल CHAMELEON_DTYPE_END:
			अवरोध;
		शेष:
			pr_err("Invalid chameleon descriptor type 0x%x\n",
				dtype);
			ret = -EINVAL;
			जाओ मुक्त_bar;
		पूर्ण
		num_cells++;
	पूर्ण

	अगर (num_cells == 0)
		num_cells = -EINVAL;

	kमुक्त(cb);
	kमुक्त(header);
	वापस num_cells;

मुक्त_bar:
	kमुक्त(cb);
मुक्त_header:
	kमुक्त(header);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_NS_GPL(chameleon_parse_cells, MCB);
