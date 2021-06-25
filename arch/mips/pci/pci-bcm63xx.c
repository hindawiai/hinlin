<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <यंत्र/bootinfo.h>

#समावेश <bcm63xx_reset.h>

#समावेश "pci-bcm63xx.h"

/*
 * Allow PCI to be disabled at runसमय depending on board nvram
 * configuration
 */
पूर्णांक bcm63xx_pci_enabled;

अटल काष्ठा resource bcm_pci_mem_resource = अणु
	.name	= "bcm63xx PCI memory space",
	.start	= BCM_PCI_MEM_BASE_PA,
	.end	= BCM_PCI_MEM_END_PA,
	.flags	= IORESOURCE_MEM
पूर्ण;

अटल काष्ठा resource bcm_pci_io_resource = अणु
	.name	= "bcm63xx PCI IO space",
	.start	= BCM_PCI_IO_BASE_PA,
#अगर_घोषित CONFIG_CARDBUS
	.end	= BCM_PCI_IO_HALF_PA,
#अन्यथा
	.end	= BCM_PCI_IO_END_PA,
#पूर्ण_अगर
	.flags	= IORESOURCE_IO
पूर्ण;

काष्ठा pci_controller bcm63xx_controller = अणु
	.pci_ops	= &bcm63xx_pci_ops,
	.io_resource	= &bcm_pci_io_resource,
	.mem_resource	= &bcm_pci_mem_resource,
पूर्ण;

/*
 * We handle cardbus  via a fake Cardbus bridge,  memory and io spaces
 * have to be  clearly separated from PCI one  since we have dअगरferent
 * memory decoder.
 */
#अगर_घोषित CONFIG_CARDBUS
अटल काष्ठा resource bcm_cb_mem_resource = अणु
	.name	= "bcm63xx Cardbus memory space",
	.start	= BCM_CB_MEM_BASE_PA,
	.end	= BCM_CB_MEM_END_PA,
	.flags	= IORESOURCE_MEM
पूर्ण;

अटल काष्ठा resource bcm_cb_io_resource = अणु
	.name	= "bcm63xx Cardbus IO space",
	.start	= BCM_PCI_IO_HALF_PA + 1,
	.end	= BCM_PCI_IO_END_PA,
	.flags	= IORESOURCE_IO
पूर्ण;

काष्ठा pci_controller bcm63xx_cb_controller = अणु
	.pci_ops	= &bcm63xx_cb_ops,
	.io_resource	= &bcm_cb_io_resource,
	.mem_resource	= &bcm_cb_mem_resource,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा resource bcm_pcie_mem_resource = अणु
	.name	= "bcm63xx PCIe memory space",
	.start	= BCM_PCIE_MEM_BASE_PA,
	.end	= BCM_PCIE_MEM_END_PA,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource bcm_pcie_io_resource = अणु
	.name	= "bcm63xx PCIe IO space",
	.start	= 0,
	.end	= 0,
	.flags	= 0,
पूर्ण;

काष्ठा pci_controller bcm63xx_pcie_controller = अणु
	.pci_ops	= &bcm63xx_pcie_ops,
	.io_resource	= &bcm_pcie_io_resource,
	.mem_resource	= &bcm_pcie_mem_resource,
पूर्ण;

अटल u32 bcm63xx_पूर्णांक_cfg_पढ़ोl(u32 reg)
अणु
	u32 पंचांगp;

	पंचांगp = reg & MPI_PCICFGCTL_CFGADDR_MASK;
	पंचांगp |= MPI_PCICFGCTL_WRITEEN_MASK;
	bcm_mpi_ग_लिखोl(पंचांगp, MPI_PCICFGCTL_REG);
	iob();
	वापस bcm_mpi_पढ़ोl(MPI_PCICFGDATA_REG);
पूर्ण

अटल व्योम bcm63xx_पूर्णांक_cfg_ग_लिखोl(u32 val, u32 reg)
अणु
	u32 पंचांगp;

	पंचांगp = reg & MPI_PCICFGCTL_CFGADDR_MASK;
	पंचांगp |=	MPI_PCICFGCTL_WRITEEN_MASK;
	bcm_mpi_ग_लिखोl(पंचांगp, MPI_PCICFGCTL_REG);
	bcm_mpi_ग_लिखोl(val, MPI_PCICFGDATA_REG);
पूर्ण

व्योम __iomem *pci_iospace_start;

अटल व्योम __init bcm63xx_reset_pcie(व्योम)
अणु
	u32 val;
	u32 reg;

	/* enable SERDES */
	अगर (BCMCPU_IS_6328())
		reg = MISC_SERDES_CTRL_6328_REG;
	अन्यथा
		reg = MISC_SERDES_CTRL_6362_REG;

	val = bcm_misc_पढ़ोl(reg);
	val |= SERDES_PCIE_EN | SERDES_PCIE_EXD_EN;
	bcm_misc_ग_लिखोl(val, reg);

	/* reset the PCIe core */
	bcm63xx_core_set_reset(BCM63XX_RESET_PCIE, 1);
	bcm63xx_core_set_reset(BCM63XX_RESET_PCIE_EXT, 1);
	mdelay(10);

	bcm63xx_core_set_reset(BCM63XX_RESET_PCIE, 0);
	mdelay(10);

	bcm63xx_core_set_reset(BCM63XX_RESET_PCIE_EXT, 0);
	mdelay(200);
पूर्ण

अटल काष्ठा clk *pcie_clk;

अटल पूर्णांक __init bcm63xx_रेजिस्टर_pcie(व्योम)
अणु
	u32 val;

	/* enable घड़ी */
	pcie_clk = clk_get(शून्य, "pcie");
	अगर (IS_ERR_OR_शून्य(pcie_clk))
		वापस -ENODEV;

	clk_prepare_enable(pcie_clk);

	bcm63xx_reset_pcie();

	/* configure the PCIe bridge */
	val = bcm_pcie_पढ़ोl(PCIE_BRIDGE_OPT1_REG);
	val |= OPT1_RD_BE_OPT_EN;
	val |= OPT1_RD_REPLY_BE_FIX_EN;
	val |= OPT1_PCIE_BRIDGE_HOLE_DET_EN;
	val |= OPT1_L1_INT_STATUS_MASK_POL;
	bcm_pcie_ग_लिखोl(val, PCIE_BRIDGE_OPT1_REG);

	/* setup the पूर्णांकerrupts */
	val = bcm_pcie_पढ़ोl(PCIE_BRIDGE_RC_INT_MASK_REG);
	val |= PCIE_RC_INT_A | PCIE_RC_INT_B | PCIE_RC_INT_C | PCIE_RC_INT_D;
	bcm_pcie_ग_लिखोl(val, PCIE_BRIDGE_RC_INT_MASK_REG);

	val = bcm_pcie_पढ़ोl(PCIE_BRIDGE_OPT2_REG);
	/* enable credit checking and error checking */
	val |= OPT2_TX_CREDIT_CHK_EN;
	val |= OPT2_UBUS_UR_DECODE_DIS;

	/* set device bus/func क्रम the pcie device */
	val |= (PCIE_BUS_DEVICE << OPT2_CFG_TYPE1_BUS_NO_SHIFT);
	val |= OPT2_CFG_TYPE1_BD_SEL;
	bcm_pcie_ग_लिखोl(val, PCIE_BRIDGE_OPT2_REG);

	/* setup class code as bridge */
	val = bcm_pcie_पढ़ोl(PCIE_IDVAL3_REG);
	val &= ~IDVAL3_CLASS_CODE_MASK;
	val |= (PCI_CLASS_BRIDGE_PCI << IDVAL3_SUBCLASS_SHIFT);
	bcm_pcie_ग_लिखोl(val, PCIE_IDVAL3_REG);

	/* disable bar1 size */
	val = bcm_pcie_पढ़ोl(PCIE_CONFIG2_REG);
	val &= ~CONFIG2_BAR1_SIZE_MASK;
	bcm_pcie_ग_लिखोl(val, PCIE_CONFIG2_REG);

	/* set bar0 to little endian */
	val = (BCM_PCIE_MEM_BASE_PA >> 20) << BASEMASK_BASE_SHIFT;
	val |= (BCM_PCIE_MEM_BASE_PA >> 20) << BASEMASK_MASK_SHIFT;
	val |= BASEMASK_REMAP_EN;
	bcm_pcie_ग_लिखोl(val, PCIE_BRIDGE_BAR0_BASEMASK_REG);

	val = (BCM_PCIE_MEM_BASE_PA >> 20) << REBASE_ADDR_BASE_SHIFT;
	bcm_pcie_ग_लिखोl(val, PCIE_BRIDGE_BAR0_REBASE_ADDR_REG);

	रेजिस्टर_pci_controller(&bcm63xx_pcie_controller);

	वापस 0;
पूर्ण

अटल पूर्णांक __init bcm63xx_रेजिस्टर_pci(व्योम)
अणु
	अचिन्हित पूर्णांक mem_size;
	u32 val;
	/*
	 * configuration  access are  करोne through  IO space,  remap 4
	 * first bytes to access it from CPU.
	 *
	 * this means that  no io access from CPU  should happen जबतक
	 * we करो a configuration cycle,	 but there's no way we can add
	 * a spinlock क्रम each io access, so this is currently kind of
	 * broken on SMP.
	 */
	pci_iospace_start = ioremap(BCM_PCI_IO_BASE_PA, 4);
	अगर (!pci_iospace_start)
		वापस -ENOMEM;

	/* setup local bus to PCI access (PCI memory) */
	val = BCM_PCI_MEM_BASE_PA & MPI_L2P_BASE_MASK;
	bcm_mpi_ग_लिखोl(val, MPI_L2PMEMBASE1_REG);
	bcm_mpi_ग_लिखोl(~(BCM_PCI_MEM_SIZE - 1), MPI_L2PMEMRANGE1_REG);
	bcm_mpi_ग_लिखोl(val | MPI_L2PREMAP_ENABLED_MASK, MPI_L2PMEMREMAP1_REG);

	/* set Cardbus IDSEL (type 0 cfg access on primary bus क्रम
	 * this IDSEL will be करोne on Cardbus instead) */
	val = bcm_pcmcia_पढ़ोl(PCMCIA_C1_REG);
	val &= ~PCMCIA_C1_CBIDSEL_MASK;
	val |= (CARDBUS_PCI_IDSEL << PCMCIA_C1_CBIDSEL_SHIFT);
	bcm_pcmcia_ग_लिखोl(val, PCMCIA_C1_REG);

#अगर_घोषित CONFIG_CARDBUS
	/* setup local bus to PCI access (Cardbus memory) */
	val = BCM_CB_MEM_BASE_PA & MPI_L2P_BASE_MASK;
	bcm_mpi_ग_लिखोl(val, MPI_L2PMEMBASE2_REG);
	bcm_mpi_ग_लिखोl(~(BCM_CB_MEM_SIZE - 1), MPI_L2PMEMRANGE2_REG);
	val |= MPI_L2PREMAP_ENABLED_MASK | MPI_L2PREMAP_IS_CARDBUS_MASK;
	bcm_mpi_ग_लिखोl(val, MPI_L2PMEMREMAP2_REG);
#अन्यथा
	/* disable second access winकरोws */
	bcm_mpi_ग_लिखोl(0, MPI_L2PMEMREMAP2_REG);
#पूर्ण_अगर

	/* setup local bus  to PCI access (IO memory),	we have only 1
	 * IO winकरोw  क्रम both PCI  and cardbus, but it	 cannot handle
	 * both	 at the	 same समय,  assume standard  PCI क्रम  now, अगर
	 * cardbus card has  IO zone, PCI fixup will  change winकरोw to
	 * cardbus */
	val = BCM_PCI_IO_BASE_PA & MPI_L2P_BASE_MASK;
	bcm_mpi_ग_लिखोl(val, MPI_L2PIOBASE_REG);
	bcm_mpi_ग_लिखोl(~(BCM_PCI_IO_SIZE - 1), MPI_L2PIORANGE_REG);
	bcm_mpi_ग_लिखोl(val | MPI_L2PREMAP_ENABLED_MASK, MPI_L2PIOREMAP_REG);

	/* enable PCI related GPIO pins */
	bcm_mpi_ग_लिखोl(MPI_LOCBUSCTL_EN_PCI_GPIO_MASK, MPI_LOCBUSCTL_REG);

	/* setup PCI to local bus access, used by PCI device to target
	 * local RAM जबतक bus mastering */
	bcm63xx_पूर्णांक_cfg_ग_लिखोl(0, PCI_BASE_ADDRESS_3);
	अगर (BCMCPU_IS_3368() || BCMCPU_IS_6358() || BCMCPU_IS_6368())
		val = MPI_SP0_REMAP_ENABLE_MASK;
	अन्यथा
		val = 0;
	bcm_mpi_ग_लिखोl(val, MPI_SP0_REMAP_REG);

	bcm63xx_पूर्णांक_cfg_ग_लिखोl(0x0, PCI_BASE_ADDRESS_4);
	bcm_mpi_ग_लिखोl(0, MPI_SP1_REMAP_REG);

	mem_size = bcm63xx_get_memory_size();

	/* 6348 beक्रमe rev b0 exposes only 16 MB of RAM memory through
	 * PCI, throw a warning अगर we have more memory */
	अगर (BCMCPU_IS_6348() && (bcm63xx_get_cpu_rev() & 0xf0) == 0xa0) अणु
		अगर (mem_size > (16 * 1024 * 1024))
			prपूर्णांकk(KERN_WARNING "bcm63xx: this CPU "
			       "revision cannot handle more than 16MB "
			       "of RAM for PCI bus mastering\n");
	पूर्ण अन्यथा अणु
		/* setup sp0 range to local RAM size */
		bcm_mpi_ग_लिखोl(~(mem_size - 1), MPI_SP0_RANGE_REG);
		bcm_mpi_ग_लिखोl(0, MPI_SP1_RANGE_REG);
	पूर्ण

	/* change  host bridge	retry  counter to  infinite number  of
	 * retry,  needed क्रम  some broadcom  wअगरi cards  with Silicon
	 * Backplane bus where access to srom seems very slow  */
	val = bcm63xx_पूर्णांक_cfg_पढ़ोl(BCMPCI_REG_TIMERS);
	val &= ~REG_TIMER_RETRY_MASK;
	bcm63xx_पूर्णांक_cfg_ग_लिखोl(val, BCMPCI_REG_TIMERS);

	/* enable memory decoder and bus mastering */
	val = bcm63xx_पूर्णांक_cfg_पढ़ोl(PCI_COMMAND);
	val |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	bcm63xx_पूर्णांक_cfg_ग_लिखोl(val, PCI_COMMAND);

	/* enable पढ़ो prefetching & disable byte swapping क्रम bus
	 * mastering transfers */
	val = bcm_mpi_पढ़ोl(MPI_PCIMODESEL_REG);
	val &= ~MPI_PCIMODESEL_BAR1_NOSWAP_MASK;
	val &= ~MPI_PCIMODESEL_BAR2_NOSWAP_MASK;
	val &= ~MPI_PCIMODESEL_PREFETCH_MASK;
	val |= (8 << MPI_PCIMODESEL_PREFETCH_SHIFT);
	bcm_mpi_ग_लिखोl(val, MPI_PCIMODESEL_REG);

	/* enable pci पूर्णांकerrupt */
	val = bcm_mpi_पढ़ोl(MPI_LOCINT_REG);
	val |= MPI_LOCINT_MASK(MPI_LOCINT_EXT_PCI_INT);
	bcm_mpi_ग_लिखोl(val, MPI_LOCINT_REG);

	रेजिस्टर_pci_controller(&bcm63xx_controller);

#अगर_घोषित CONFIG_CARDBUS
	रेजिस्टर_pci_controller(&bcm63xx_cb_controller);
#पूर्ण_अगर

	/* mark memory space used क्रम IO mapping as reserved */
	request_mem_region(BCM_PCI_IO_BASE_PA, BCM_PCI_IO_SIZE,
			   "bcm63xx PCI IO space");
	वापस 0;
पूर्ण


अटल पूर्णांक __init bcm63xx_pci_init(व्योम)
अणु
	अगर (!bcm63xx_pci_enabled)
		वापस -ENODEV;

	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM6328_CPU_ID:
	हाल BCM6362_CPU_ID:
		वापस bcm63xx_रेजिस्टर_pcie();
	हाल BCM3368_CPU_ID:
	हाल BCM6348_CPU_ID:
	हाल BCM6358_CPU_ID:
	हाल BCM6368_CPU_ID:
		वापस bcm63xx_रेजिस्टर_pci();
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

arch_initcall(bcm63xx_pci_init);
