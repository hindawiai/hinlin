<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alchemy PCI host mode support.
 *
 * Copyright 2001-2003, 2007-2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 *
 * Support क्रम all devices (greater than 16) added by David Gathright.
 */

#समावेश <linux/clk.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-map-ops.h> /* क्रम dma_शेष_coherent */

#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/tlbmisc.h>

#अगर_घोषित CONFIG_PCI_DEBUG
#घोषणा DBG(x...) prपूर्णांकk(KERN_DEBUG x)
#अन्यथा
#घोषणा DBG(x...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा PCI_ACCESS_READ		0
#घोषणा PCI_ACCESS_WRITE	1

काष्ठा alchemy_pci_context अणु
	काष्ठा pci_controller alchemy_pci_ctrl; /* leave as first member! */
	व्योम __iomem *regs;			/* ctrl base */
	/* tools क्रम wired entry क्रम config space access */
	अचिन्हित दीर्घ last_elo0;
	अचिन्हित दीर्घ last_elo1;
	पूर्णांक wired_entry;
	काष्ठा vm_काष्ठा *pci_cfg_vm;

	अचिन्हित दीर्घ pm[12];

	पूर्णांक (*board_map_irq)(स्थिर काष्ठा pci_dev *d, u8 slot, u8 pin);
	पूर्णांक (*board_pci_idsel)(अचिन्हित पूर्णांक devsel, पूर्णांक निश्चित);
पूर्ण;

/* क्रम syscore_ops. There's only one PCI controller on Alchemy chips, so this
 * should suffice क्रम now.
 */
अटल काष्ठा alchemy_pci_context *__alchemy_pci_ctx;


/* IO/MEM resources क्रम PCI. Keep the memres in sync with fixup_bigphys_addr
 * in arch/mips/alchemy/common/setup.c
 */
अटल काष्ठा resource alchemy_pci_def_memres = अणु
	.start	= ALCHEMY_PCI_MEMWIN_START,
	.end	= ALCHEMY_PCI_MEMWIN_END,
	.name	= "PCI memory space",
	.flags	= IORESOURCE_MEM
पूर्ण;

अटल काष्ठा resource alchemy_pci_def_iores = अणु
	.start	= ALCHEMY_PCI_IOWIN_START,
	.end	= ALCHEMY_PCI_IOWIN_END,
	.name	= "PCI IO space",
	.flags	= IORESOURCE_IO
पूर्ण;

अटल व्योम mod_wired_entry(पूर्णांक entry, अचिन्हित दीर्घ entrylo0,
		अचिन्हित दीर्घ entrylo1, अचिन्हित दीर्घ entryhi,
		अचिन्हित दीर्घ pagemask)
अणु
	अचिन्हित दीर्घ old_pagemask;
	अचिन्हित दीर्घ old_ctx;

	/* Save old context and create impossible VPN2 value */
	old_ctx = पढ़ो_c0_entryhi() & MIPS_ENTRYHI_ASID;
	old_pagemask = पढ़ो_c0_pagemask();
	ग_लिखो_c0_index(entry);
	ग_लिखो_c0_pagemask(pagemask);
	ग_लिखो_c0_entryhi(entryhi);
	ग_लिखो_c0_entrylo0(entrylo0);
	ग_लिखो_c0_entrylo1(entrylo1);
	tlb_ग_लिखो_indexed();
	ग_लिखो_c0_entryhi(old_ctx);
	ग_लिखो_c0_pagemask(old_pagemask);
पूर्ण

अटल व्योम alchemy_pci_wired_entry(काष्ठा alchemy_pci_context *ctx)
अणु
	ctx->wired_entry = पढ़ो_c0_wired();
	add_wired_entry(0, 0, (अचिन्हित दीर्घ)ctx->pci_cfg_vm->addr, PM_4K);
	ctx->last_elo0 = ctx->last_elo1 = ~0;
पूर्ण

अटल पूर्णांक config_access(अचिन्हित अक्षर access_type, काष्ठा pci_bus *bus,
			 अचिन्हित पूर्णांक dev_fn, अचिन्हित अक्षर where, u32 *data)
अणु
	काष्ठा alchemy_pci_context *ctx = bus->sysdata;
	अचिन्हित पूर्णांक device = PCI_SLOT(dev_fn);
	अचिन्हित पूर्णांक function = PCI_FUNC(dev_fn);
	अचिन्हित दीर्घ offset, status, cfg_base, flags, entryLo0, entryLo1, r;
	पूर्णांक error = PCIBIOS_SUCCESSFUL;

	अगर (device > 19) अणु
		*data = 0xffffffff;
		वापस -1;
	पूर्ण

	local_irq_save(flags);
	r = __raw_पढ़ोl(ctx->regs + PCI_REG_STATCMD) & 0x0000ffff;
	r |= PCI_STATCMD_STATUS(0x2000);
	__raw_ग_लिखोl(r, ctx->regs + PCI_REG_STATCMD);
	wmb();

	/* Allow board venकरोrs to implement their own off-chip IDSEL.
	 * If it करोesn't succeed, may as well bail out at this poपूर्णांक.
	 */
	अगर (ctx->board_pci_idsel(device, 1) == 0) अणु
		*data = 0xffffffff;
		local_irq_restore(flags);
		वापस -1;
	पूर्ण

	/* Setup the config winकरोw */
	अगर (bus->number == 0)
		cfg_base = (1 << device) << 11;
	अन्यथा
		cfg_base = 0x80000000 | (bus->number << 16) | (device << 11);

	/* Setup the lower bits of the 36-bit address */
	offset = (function << 8) | (where & ~0x3);
	/* Pick up any address that falls below the page mask */
	offset |= cfg_base & ~PAGE_MASK;

	/* Page boundary */
	cfg_base = cfg_base & PAGE_MASK;

	/* To improve perक्रमmance, अगर the current device is the same as
	 * the last device accessed, we करोn't touch the TLB.
	 */
	entryLo0 = (6 << 26) | (cfg_base >> 6) | (2 << 3) | 7;
	entryLo1 = (6 << 26) | (cfg_base >> 6) | (0x1000 >> 6) | (2 << 3) | 7;
	अगर ((entryLo0 != ctx->last_elo0) || (entryLo1 != ctx->last_elo1)) अणु
		mod_wired_entry(ctx->wired_entry, entryLo0, entryLo1,
				(अचिन्हित दीर्घ)ctx->pci_cfg_vm->addr, PM_4K);
		ctx->last_elo0 = entryLo0;
		ctx->last_elo1 = entryLo1;
	पूर्ण

	अगर (access_type == PCI_ACCESS_WRITE)
		__raw_ग_लिखोl(*data, ctx->pci_cfg_vm->addr + offset);
	अन्यथा
		*data = __raw_पढ़ोl(ctx->pci_cfg_vm->addr + offset);
	wmb();

	DBG("alchemy-pci: cfg access %d bus %u dev %u at %x dat %x conf %lx\n",
	    access_type, bus->number, device, where, *data, offset);

	/* check क्रम errors, master पात */
	status = __raw_पढ़ोl(ctx->regs + PCI_REG_STATCMD);
	अगर (status & (1 << 29)) अणु
		*data = 0xffffffff;
		error = -1;
		DBG("alchemy-pci: master abort on cfg access %d bus %d dev %d\n",
		    access_type, bus->number, device);
	पूर्ण अन्यथा अगर ((status >> 28) & 0xf) अणु
		DBG("alchemy-pci: PCI ERR detected: dev %d, status %lx\n",
		    device, (status >> 28) & 0xf);

		/* clear errors */
		__raw_ग_लिखोl(status & 0xf000ffff, ctx->regs + PCI_REG_STATCMD);

		*data = 0xffffffff;
		error = -1;
	पूर्ण

	/* Take away the IDSEL. */
	(व्योम)ctx->board_pci_idsel(device, 0);

	local_irq_restore(flags);
	वापस error;
पूर्ण

अटल पूर्णांक पढ़ो_config_byte(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where,	u8 *val)
अणु
	u32 data;
	पूर्णांक ret = config_access(PCI_ACCESS_READ, bus, devfn, where, &data);

	अगर (where & 1)
		data >>= 8;
	अगर (where & 2)
		data >>= 16;
	*val = data & 0xff;
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_config_word(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, u16 *val)
अणु
	u32 data;
	पूर्णांक ret = config_access(PCI_ACCESS_READ, bus, devfn, where, &data);

	अगर (where & 2)
		data >>= 16;
	*val = data & 0xffff;
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, u32 *val)
अणु
	वापस config_access(PCI_ACCESS_READ, bus, devfn, where, val);
पूर्ण

अटल पूर्णांक ग_लिखो_config_byte(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, u8 val)
अणु
	u32 data = 0;

	अगर (config_access(PCI_ACCESS_READ, bus, devfn, where, &data))
		वापस -1;

	data = (data & ~(0xff << ((where & 3) << 3))) |
	       (val << ((where & 3) << 3));

	अगर (config_access(PCI_ACCESS_WRITE, bus, devfn, where, &data))
		वापस -1;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ग_लिखो_config_word(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, u16 val)
अणु
	u32 data = 0;

	अगर (config_access(PCI_ACCESS_READ, bus, devfn, where, &data))
		वापस -1;

	data = (data & ~(0xffff << ((where & 3) << 3))) |
	       (val << ((where & 3) << 3));

	अगर (config_access(PCI_ACCESS_WRITE, bus, devfn, where, &data))
		वापस -1;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ग_लिखो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, u32 val)
अणु
	वापस config_access(PCI_ACCESS_WRITE, bus, devfn, where, &val);
पूर्ण

अटल पूर्णांक alchemy_pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
		       पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	चयन (size) अणु
	हाल 1: अणु
			u8 _val;
			पूर्णांक rc = पढ़ो_config_byte(bus, devfn, where, &_val);

			*val = _val;
			वापस rc;
		पूर्ण
	हाल 2: अणु
			u16 _val;
			पूर्णांक rc = पढ़ो_config_word(bus, devfn, where, &_val);

			*val = _val;
			वापस rc;
		पूर्ण
	शेष:
		वापस पढ़ो_config_dword(bus, devfn, where, val);
	पूर्ण
पूर्ण

अटल पूर्णांक alchemy_pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 val)
अणु
	चयन (size) अणु
	हाल 1:
		वापस ग_लिखो_config_byte(bus, devfn, where, (u8) val);
	हाल 2:
		वापस ग_लिखो_config_word(bus, devfn, where, (u16) val);
	शेष:
		वापस ग_लिखो_config_dword(bus, devfn, where, val);
	पूर्ण
पूर्ण

अटल काष्ठा pci_ops alchemy_pci_ops = अणु
	.पढ़ो	= alchemy_pci_पढ़ो,
	.ग_लिखो	= alchemy_pci_ग_लिखो,
पूर्ण;

अटल पूर्णांक alchemy_pci_def_idsel(अचिन्हित पूर्णांक devsel, पूर्णांक निश्चित)
अणु
	वापस 1;	/* success */
पूर्ण

/* save PCI controller रेजिस्टर contents. */
अटल पूर्णांक alchemy_pci_suspend(व्योम)
अणु
	काष्ठा alchemy_pci_context *ctx = __alchemy_pci_ctx;
	अगर (!ctx)
		वापस 0;

	ctx->pm[0]  = __raw_पढ़ोl(ctx->regs + PCI_REG_CMEM);
	ctx->pm[1]  = __raw_पढ़ोl(ctx->regs + PCI_REG_CONFIG) & 0x0009ffff;
	ctx->pm[2]  = __raw_पढ़ोl(ctx->regs + PCI_REG_B2BMASK_CCH);
	ctx->pm[3]  = __raw_पढ़ोl(ctx->regs + PCI_REG_B2BBASE0_VID);
	ctx->pm[4]  = __raw_पढ़ोl(ctx->regs + PCI_REG_B2BBASE1_SID);
	ctx->pm[5]  = __raw_पढ़ोl(ctx->regs + PCI_REG_MWMASK_DEV);
	ctx->pm[6]  = __raw_पढ़ोl(ctx->regs + PCI_REG_MWBASE_REV_CCL);
	ctx->pm[7]  = __raw_पढ़ोl(ctx->regs + PCI_REG_ID);
	ctx->pm[8]  = __raw_पढ़ोl(ctx->regs + PCI_REG_CLASSREV);
	ctx->pm[9]  = __raw_पढ़ोl(ctx->regs + PCI_REG_PARAM);
	ctx->pm[10] = __raw_पढ़ोl(ctx->regs + PCI_REG_MBAR);
	ctx->pm[11] = __raw_पढ़ोl(ctx->regs + PCI_REG_TIMEOUT);

	वापस 0;
पूर्ण

अटल व्योम alchemy_pci_resume(व्योम)
अणु
	काष्ठा alchemy_pci_context *ctx = __alchemy_pci_ctx;
	अगर (!ctx)
		वापस;

	__raw_ग_लिखोl(ctx->pm[0],  ctx->regs + PCI_REG_CMEM);
	__raw_ग_लिखोl(ctx->pm[2],  ctx->regs + PCI_REG_B2BMASK_CCH);
	__raw_ग_लिखोl(ctx->pm[3],  ctx->regs + PCI_REG_B2BBASE0_VID);
	__raw_ग_लिखोl(ctx->pm[4],  ctx->regs + PCI_REG_B2BBASE1_SID);
	__raw_ग_लिखोl(ctx->pm[5],  ctx->regs + PCI_REG_MWMASK_DEV);
	__raw_ग_लिखोl(ctx->pm[6],  ctx->regs + PCI_REG_MWBASE_REV_CCL);
	__raw_ग_लिखोl(ctx->pm[7],  ctx->regs + PCI_REG_ID);
	__raw_ग_लिखोl(ctx->pm[8],  ctx->regs + PCI_REG_CLASSREV);
	__raw_ग_लिखोl(ctx->pm[9],  ctx->regs + PCI_REG_PARAM);
	__raw_ग_लिखोl(ctx->pm[10], ctx->regs + PCI_REG_MBAR);
	__raw_ग_लिखोl(ctx->pm[11], ctx->regs + PCI_REG_TIMEOUT);
	wmb();
	__raw_ग_लिखोl(ctx->pm[1],  ctx->regs + PCI_REG_CONFIG);
	wmb();

	/* YAMON on all db1xxx boards wipes the TLB and ग_लिखोs zero to C0_wired
	 * on resume, making it necessary to recreate it as soon as possible.
	 */
	ctx->wired_entry = 8191;	/* impossibly high value */
	alchemy_pci_wired_entry(ctx);	/* install it */
पूर्ण

अटल काष्ठा syscore_ops alchemy_pci_pmops = अणु
	.suspend	= alchemy_pci_suspend,
	.resume		= alchemy_pci_resume,
पूर्ण;

अटल पूर्णांक alchemy_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा alchemy_pci_platdata *pd = pdev->dev.platक्रमm_data;
	काष्ठा alchemy_pci_context *ctx;
	व्योम __iomem *virt_io;
	अचिन्हित दीर्घ val;
	काष्ठा resource *r;
	काष्ठा clk *c;
	पूर्णांक ret;

	/* need at least PCI IRQ mapping table */
	अगर (!pd) अणु
		dev_err(&pdev->dev, "need platform data for PCI setup\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		dev_err(&pdev->dev, "no memory for pcictl context\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "no	 pcictl ctrl regs resource\n");
		ret = -ENODEV;
		जाओ out1;
	पूर्ण

	अगर (!request_mem_region(r->start, resource_size(r), pdev->name)) अणु
		dev_err(&pdev->dev, "cannot claim pci regs\n");
		ret = -ENODEV;
		जाओ out1;
	पूर्ण

	c = clk_get(&pdev->dev, "pci_clko");
	अगर (IS_ERR(c)) अणु
		dev_err(&pdev->dev, "unable to find PCI clock\n");
		ret = PTR_ERR(c);
		जाओ out2;
	पूर्ण

	ret = clk_prepare_enable(c);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot enable PCI clock\n");
		जाओ out6;
	पूर्ण

	ctx->regs = ioremap(r->start, resource_size(r));
	अगर (!ctx->regs) अणु
		dev_err(&pdev->dev, "cannot map pci regs\n");
		ret = -ENODEV;
		जाओ out5;
	पूर्ण

	/* map parts of the PCI IO area */
	/* REVISIT: अगर this changes with a newer variant (करोubt it) make this
	 * a platक्रमm resource.
	 */
	virt_io = ioremap(AU1500_PCI_IO_PHYS_ADDR, 0x00100000);
	अगर (!virt_io) अणु
		dev_err(&pdev->dev, "cannot remap pci io space\n");
		ret = -ENODEV;
		जाओ out3;
	पूर्ण
	ctx->alchemy_pci_ctrl.io_map_base = (अचिन्हित दीर्घ)virt_io;

	/* Au1500 revisions older than AD have borked coherent PCI */
	अगर (alchemy_get_cputype() == ALCHEMY_CPU_AU1500 &&
	    पढ़ो_c0_prid() < 0x01030202 && !dma_शेष_coherent) अणु
		val = __raw_पढ़ोl(ctx->regs + PCI_REG_CONFIG);
		val |= PCI_CONFIG_NC;
		__raw_ग_लिखोl(val, ctx->regs + PCI_REG_CONFIG);
		wmb();
		dev_info(&pdev->dev, "non-coherent PCI on Au1500 AA/AB/AC\n");
	पूर्ण

	अगर (pd->board_map_irq)
		ctx->board_map_irq = pd->board_map_irq;

	अगर (pd->board_pci_idsel)
		ctx->board_pci_idsel = pd->board_pci_idsel;
	अन्यथा
		ctx->board_pci_idsel = alchemy_pci_def_idsel;

	/* fill in relevant pci_controller members */
	ctx->alchemy_pci_ctrl.pci_ops = &alchemy_pci_ops;
	ctx->alchemy_pci_ctrl.mem_resource = &alchemy_pci_def_memres;
	ctx->alchemy_pci_ctrl.io_resource = &alchemy_pci_def_iores;

	/* we can't ioremap the entire pci config space because it's too large,
	 * nor can we dynamically ioremap it because some drivers use the
	 * PCI config routines from within atomic contex and that becomes a
	 * problem in get_vm_area().  Instead we use one wired TLB entry to
	 * handle all config accesses क्रम all busses.
	 */
	ctx->pci_cfg_vm = get_vm_area(0x2000, VM_IOREMAP);
	अगर (!ctx->pci_cfg_vm) अणु
		dev_err(&pdev->dev, "unable to get vm area\n");
		ret = -ENOMEM;
		जाओ out4;
	पूर्ण
	ctx->wired_entry = 8191;	/* impossibly high value */
	alchemy_pci_wired_entry(ctx);	/* install it */

	set_io_port_base((अचिन्हित दीर्घ)ctx->alchemy_pci_ctrl.io_map_base);

	/* board may want to modअगरy bits in the config रेजिस्टर, करो it now */
	val = __raw_पढ़ोl(ctx->regs + PCI_REG_CONFIG);
	val &= ~pd->pci_cfg_clr;
	val |= pd->pci_cfg_set;
	val &= ~PCI_CONFIG_PD;		/* clear disable bit */
	__raw_ग_लिखोl(val, ctx->regs + PCI_REG_CONFIG);
	wmb();

	__alchemy_pci_ctx = ctx;
	platक्रमm_set_drvdata(pdev, ctx);
	रेजिस्टर_syscore_ops(&alchemy_pci_pmops);
	रेजिस्टर_pci_controller(&ctx->alchemy_pci_ctrl);

	dev_info(&pdev->dev, "PCI controller at %ld MHz\n",
		 clk_get_rate(c) / 1000000);

	वापस 0;

out4:
	iounmap(virt_io);
out3:
	iounmap(ctx->regs);
out5:
	clk_disable_unprepare(c);
out6:
	clk_put(c);
out2:
	release_mem_region(r->start, resource_size(r));
out1:
	kमुक्त(ctx);
out:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver alchemy_pcictl_driver = अणु
	.probe		= alchemy_pci_probe,
	.driver = अणु
		.name	= "alchemy-pci",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init alchemy_pci_init(व्योम)
अणु
	/* Au1500/Au1550 have PCI */
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1550:
		वापस platक्रमm_driver_रेजिस्टर(&alchemy_pcictl_driver);
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(alchemy_pci_init);


पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा alchemy_pci_context *ctx = dev->sysdata;
	अगर (ctx && ctx->board_map_irq)
		वापस ctx->board_map_irq(dev, slot, pin);
	वापस -1;
पूर्ण

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
