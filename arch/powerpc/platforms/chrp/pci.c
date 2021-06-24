<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CHRP pci routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hydra.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/grackle.h>
#समावेश <यंत्र/rtas.h>

#समावेश "chrp.h"
#समावेश "gg2.h"

/* LongTrail */
व्योम __iomem *gg2_pci_config_base;

/*
 * The VLSI Golden Gate II has only 512K of PCI configuration space, so we
 * limit the bus number to 3 bits
 */

अटल पूर्णांक gg2_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक off,
			   पूर्णांक len, u32 *val)
अणु
	अस्थिर व्योम __iomem *cfg_data;
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	अगर (bus->number > 7)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Note: the caller has alपढ़ोy checked that off is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	cfg_data = hose->cfg_data + ((bus->number<<16) | (devfn<<8) | off);
	चयन (len) अणु
	हाल 1:
		*val =  in_8(cfg_data);
		अवरोध;
	हाल 2:
		*val = in_le16(cfg_data);
		अवरोध;
	शेष:
		*val = in_le32(cfg_data);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक gg2_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक off,
			    पूर्णांक len, u32 val)
अणु
	अस्थिर व्योम __iomem *cfg_data;
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	अगर (bus->number > 7)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Note: the caller has alपढ़ोy checked that off is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	cfg_data = hose->cfg_data + ((bus->number<<16) | (devfn<<8) | off);
	चयन (len) अणु
	हाल 1:
		out_8(cfg_data, val);
		अवरोध;
	हाल 2:
		out_le16(cfg_data, val);
		अवरोध;
	शेष:
		out_le32(cfg_data, val);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops gg2_pci_ops =
अणु
	.पढ़ो = gg2_पढ़ो_config,
	.ग_लिखो = gg2_ग_लिखो_config,
पूर्ण;

/*
 * Access functions क्रम PCI config space using RTAS calls.
 */
अटल पूर्णांक rtas_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
			    पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	अचिन्हित दीर्घ addr = (offset & 0xff) | ((devfn & 0xff) << 8)
		| (((bus->number - hose->first_busno) & 0xff) << 16)
		| (hose->global_number << 24);
        पूर्णांक ret = -1;
	पूर्णांक rval;

	rval = rtas_call(rtas_token("read-pci-config"), 2, 2, &ret, addr, len);
	*val = ret;
	वापस rval? PCIBIOS_DEVICE_NOT_FOUND: PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rtas_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
			     पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	अचिन्हित दीर्घ addr = (offset & 0xff) | ((devfn & 0xff) << 8)
		| (((bus->number - hose->first_busno) & 0xff) << 16)
		| (hose->global_number << 24);
	पूर्णांक rval;

	rval = rtas_call(rtas_token("write-pci-config"), 3, 1, शून्य,
			 addr, len, val);
	वापस rval? PCIBIOS_DEVICE_NOT_FOUND: PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops rtas_pci_ops =
अणु
	.पढ़ो = rtas_पढ़ो_config,
	.ग_लिखो = rtas_ग_लिखो_config,
पूर्ण;

अस्थिर काष्ठा Hydra __iomem *Hydra = शून्य;

अटल पूर्णांक __init hydra_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource r;

	np = of_find_node_by_name(शून्य, "mac-io");
	अगर (np == शून्य || of_address_to_resource(np, 0, &r)) अणु
		of_node_put(np);
		वापस 0;
	पूर्ण
	of_node_put(np);
	Hydra = ioremap(r.start, resource_size(&r));
	prपूर्णांकk("Hydra Mac I/O at %llx\n", (अचिन्हित दीर्घ दीर्घ)r.start);
	prपूर्णांकk("Hydra Feature_Control was %x",
	       in_le32(&Hydra->Feature_Control));
	out_le32(&Hydra->Feature_Control, (HYDRA_FC_SCC_CELL_EN |
					   HYDRA_FC_SCSI_CELL_EN |
					   HYDRA_FC_SCCA_ENABLE |
					   HYDRA_FC_SCCB_ENABLE |
					   HYDRA_FC_ARB_BYPASS |
					   HYDRA_FC_MPIC_ENABLE |
					   HYDRA_FC_SLOW_SCC_PCLK |
					   HYDRA_FC_MPIC_IS_MASTER));
	prपूर्णांकk(", now %x\n", in_le32(&Hydra->Feature_Control));
	वापस 1;
पूर्ण

#घोषणा PRG_CL_RESET_VALID 0x00010000

अटल व्योम __init
setup_python(काष्ठा pci_controller *hose, काष्ठा device_node *dev)
अणु
	u32 __iomem *reg;
	u32 val;
	काष्ठा resource r;

	अगर (of_address_to_resource(dev, 0, &r)) अणु
		prपूर्णांकk(KERN_ERR "No address for Python PCI controller\n");
		वापस;
	पूर्ण

	/* Clear the magic go-slow bit */
	reg = ioremap(r.start + 0xf6000, 0x40);
	BUG_ON(!reg); 
	val = in_be32(&reg[12]);
	अगर (val & PRG_CL_RESET_VALID) अणु
		out_be32(&reg[12], val & ~PRG_CL_RESET_VALID);
		in_be32(&reg[12]);
	पूर्ण
	iounmap(reg);

	setup_indirect_pci(hose, r.start + 0xf8000, r.start + 0xf8010, 0);
पूर्ण

/* Marvell Discovery II based Pegasos 2 */
अटल व्योम __init setup_peg2(काष्ठा pci_controller *hose, काष्ठा device_node *dev)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	काष्ठा device_node *rtas;

	rtas = of_find_node_by_name (root, "rtas");
	अगर (rtas) अणु
		hose->ops = &rtas_pci_ops;
		of_node_put(rtas);
	पूर्ण अन्यथा अणु
		prपूर्णांकk ("RTAS supporting Pegasos OF not found, please upgrade"
			" your firmware\n");
	पूर्ण
	pci_add_flags(PCI_REASSIGN_ALL_BUS);
	/* keep the reference to the root node */
पूर्ण

व्योम __init
chrp_find_bridges(व्योम)
अणु
	काष्ठा device_node *dev;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक len, index = -1;
	काष्ठा pci_controller *hose;
	स्थिर अचिन्हित पूर्णांक *dma;
	स्थिर अक्षर *model, *machine;
	पूर्णांक is_दीर्घtrail = 0, is_mot = 0, is_pegasos = 0;
	काष्ठा device_node *root = of_find_node_by_path("/");
	काष्ठा resource r;
	/*
	 * The PCI host bridge nodes on some machines करोn't have
	 * properties to adequately identअगरy them, so we have to
	 * look at what sort of machine this is as well.
	 */
	machine = of_get_property(root, "model", शून्य);
	अगर (machine != शून्य) अणु
		is_दीर्घtrail = म_भेदन(machine, "IBM,LongTrail", 13) == 0;
		is_mot = म_भेदन(machine, "MOT", 3) == 0;
		अगर (म_भेदन(machine, "Pegasos2", 8) == 0)
			is_pegasos = 2;
		अन्यथा अगर (म_भेदन(machine, "Pegasos", 7) == 0)
			is_pegasos = 1;
	पूर्ण
	क्रम_each_child_of_node(root, dev) अणु
		अगर (!of_node_is_type(dev, "pci"))
			जारी;
		++index;
		/* The GG2 bridge on the LongTrail करोesn't have an address */
		अगर (of_address_to_resource(dev, 0, &r) && !is_दीर्घtrail) अणु
			prपूर्णांकk(KERN_WARNING "Can't use %pOF: no address\n",
			       dev);
			जारी;
		पूर्ण
		bus_range = of_get_property(dev, "bus-range", &len);
		अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
			prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF\n",
				dev);
			जारी;
		पूर्ण
		अगर (bus_range[1] == bus_range[0])
			prपूर्णांकk(KERN_INFO "PCI bus %d", bus_range[0]);
		अन्यथा
			prपूर्णांकk(KERN_INFO "PCI buses %d..%d",
			       bus_range[0], bus_range[1]);
		prपूर्णांकk(" controlled by %pOF", dev);
		अगर (!is_दीर्घtrail)
			prपूर्णांकk(" at %llx", (अचिन्हित दीर्घ दीर्घ)r.start);
		prपूर्णांकk("\n");

		hose = pcibios_alloc_controller(dev);
		अगर (!hose) अणु
			prपूर्णांकk("Can't allocate PCI controller structure for %pOF\n",
				dev);
			जारी;
		पूर्ण
		hose->first_busno = hose->self_busno = bus_range[0];
		hose->last_busno = bus_range[1];

		model = of_get_property(dev, "model", शून्य);
		अगर (model == शून्य)
			model = "<none>";
		अगर (म_भेदन(model, "IBM, Python", 11) == 0) अणु
			setup_python(hose, dev);
		पूर्ण अन्यथा अगर (is_mot
			   || म_भेदन(model, "Motorola, Grackle", 17) == 0) अणु
			setup_grackle(hose);
		पूर्ण अन्यथा अगर (is_दीर्घtrail) अणु
			व्योम __iomem *p = ioremap(GG2_PCI_CONFIG_BASE, 0x80000);
			hose->ops = &gg2_pci_ops;
			hose->cfg_data = p;
			gg2_pci_config_base = p;
		पूर्ण अन्यथा अगर (is_pegasos == 1) अणु
			setup_indirect_pci(hose, 0xfec00cf8, 0xfee00cfc, 0);
		पूर्ण अन्यथा अगर (is_pegasos == 2) अणु
			setup_peg2(hose, dev);
		पूर्ण अन्यथा अगर (!म_भेदन(model, "IBM,CPC710", 10)) अणु
			setup_indirect_pci(hose,
					   r.start + 0x000f8000,
					   r.start + 0x000f8010,
					   0);
			अगर (index == 0) अणु
				dma = of_get_property(dev, "system-dma-base",
							&len);
				अगर (dma && len >= माप(*dma)) अणु
					dma = (अचिन्हित पूर्णांक *)
						(((अचिन्हित दीर्घ)dma) +
						len - माप(*dma));
						pci_dram_offset = *dma;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk("No methods for %pOF (model %s), using RTAS\n",
			       dev, model);
			hose->ops = &rtas_pci_ops;
		पूर्ण

		pci_process_bridge_OF_ranges(hose, dev, index == 0);

		/* check the first bridge क्रम a property that we can
		   use to set pci_dram_offset */
		dma = of_get_property(dev, "ibm,dma-ranges", &len);
		अगर (index == 0 && dma != शून्य && len >= 6 * माप(*dma)) अणु
			pci_dram_offset = dma[2] - dma[3];
			prपूर्णांकk("pci_dram_offset = %lx\n", pci_dram_offset);
		पूर्ण
	पूर्ण
	of_node_put(root);

	/*
	 *  "Temporary" fixes क्रम PCI devices.
	 *  -- Geert
	 */
	hydra_init();		/* Mac I/O */

	pci_create_OF_bus_map();
पूर्ण

/* SL82C105 IDE Control/Status Register */
#घोषणा SL82C105_IDECSR                0x40

/* Fixup क्रम Winbond ATA quirk, required क्रम briq mostly because the
 * 8259 is configured क्रम level sensitive IRQ 14 and so wants the
 * ATA controller to be set to fully native mode or bad things
 * will happen.
 */
अटल व्योम chrp_pci_fixup_winbond_ata(काष्ठा pci_dev *sl82c105)
अणु
	u8 progअगर;

	/* If non-briq machines need that fixup too, please speak up */
	अगर (!machine_is(chrp) || _chrp_type != _CHRP_briq)
		वापस;

	अगर ((sl82c105->class & 5) != 5) अणु
		prपूर्णांकk("W83C553: Switching SL82C105 IDE to PCI native mode\n");
		/* Enable SL82C105 PCI native IDE mode */
		pci_पढ़ो_config_byte(sl82c105, PCI_CLASS_PROG, &progअगर);
		pci_ग_लिखो_config_byte(sl82c105, PCI_CLASS_PROG, progअगर | 0x05);
		sl82c105->class |= 0x05;
		/* Disable SL82C105 second port */
		pci_ग_लिखो_config_word(sl82c105, SL82C105_IDECSR, 0x0003);
		/* Clear IO BARs, they will be reasचिन्हित */
		pci_ग_लिखो_config_dword(sl82c105, PCI_BASE_ADDRESS_0, 0);
		pci_ग_लिखो_config_dword(sl82c105, PCI_BASE_ADDRESS_1, 0);
		pci_ग_लिखो_config_dword(sl82c105, PCI_BASE_ADDRESS_2, 0);
		pci_ग_लिखो_config_dword(sl82c105, PCI_BASE_ADDRESS_3, 0);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_WINBOND, PCI_DEVICE_ID_WINBOND_82C105,
			chrp_pci_fixup_winbond_ata);

/* Pegasos2 firmware version 20040810 configures the built-in IDE controller
 * in legacy mode, but sets the PCI रेजिस्टरs to PCI native mode.
 * The chip can only operate in legacy mode, so क्रमce the PCI class पूर्णांकo legacy
 * mode as well. The same fixup must be करोne to the class-code property in
 * the IDE node /pci@80000000/ide@C,1
 */
अटल व्योम chrp_pci_fixup_vt8231_ata(काष्ठा pci_dev *viaide)
अणु
	u8 progअगर;
	काष्ठा pci_dev *viaisa;

	अगर (!machine_is(chrp) || _chrp_type != _CHRP_Pegasos)
		वापस;
	अगर (viaide->irq != 14)
		वापस;

	viaisa = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8231, शून्य);
	अगर (!viaisa)
		वापस;
	dev_info(&viaide->dev, "Fixing VIA IDE, force legacy mode on\n");

	pci_पढ़ो_config_byte(viaide, PCI_CLASS_PROG, &progअगर);
	pci_ग_लिखो_config_byte(viaide, PCI_CLASS_PROG, progअगर & ~0x5);
	viaide->class &= ~0x5;

	pci_dev_put(viaisa);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C586_1, chrp_pci_fixup_vt8231_ata);
