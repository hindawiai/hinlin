<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IBM Hot Plug Controller Driver
 *
 * Written By: Irene Zubarev, IBM Corporation
 *
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001,2002 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <gregkh@us.ibm.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश "ibmphp.h"


अटल पूर्णांक configure_device(काष्ठा pci_func *);
अटल पूर्णांक configure_bridge(काष्ठा pci_func **, u8);
अटल काष्ठा res_needed *scan_behind_bridge(काष्ठा pci_func *, u8);
अटल पूर्णांक add_new_bus(काष्ठा bus_node *, काष्ठा resource_node *, काष्ठा resource_node *, काष्ठा resource_node *, u8);
अटल u8 find_sec_number(u8 primary_busno, u8 slotno);

/*
 * NOTE..... If BIOS करोesn't provide शेष routing, we assign:
 * 9 क्रम SCSI, 10 क्रम LAN adapters, and 11 क्रम everything अन्यथा.
 * If adapter is bridged, then we assign 11 to it and devices behind it.
 * We also assign the same irq numbers क्रम multi function devices.
 * These are PIC mode, so shouldn't matter n.e.ways (hopefully)
 */
अटल व्योम assign_alt_irq(काष्ठा pci_func *cur_func, u8 class_code)
अणु
	पूर्णांक j;
	क्रम (j = 0; j < 4; j++) अणु
		अगर (cur_func->irq[j] == 0xff) अणु
			चयन (class_code) अणु
				हाल PCI_BASE_CLASS_STORAGE:
					cur_func->irq[j] = SCSI_IRQ;
					अवरोध;
				हाल PCI_BASE_CLASS_NETWORK:
					cur_func->irq[j] = LAN_IRQ;
					अवरोध;
				शेष:
					cur_func->irq[j] = OTHER_IRQ;
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Configures the device to be added (will allocate needed resources अगर it
 * can), the device can be a bridge or a regular pci device, can also be
 * multi-functional
 *
 * Input: function to be added
 *
 * TO DO:  The error हाल with Multअगरunction device or multi function bridge,
 * अगर there is an error, will need to go through all previous functions and
 * unconfigure....or can add some code पूर्णांकo unconfigure_card....
 */
पूर्णांक ibmphp_configure_card(काष्ठा pci_func *func, u8 slotno)
अणु
	u16 venकरोr_id;
	u32 class;
	u8 class_code;
	u8 hdr_type, device, sec_number;
	u8 function;
	काष्ठा pci_func *newfunc;	/* क्रम multi devices */
	काष्ठा pci_func *cur_func, *prev_func;
	पूर्णांक rc, i, j;
	पूर्णांक cleanup_count;
	u8 flag;
	u8 valid_device = 0x00; /* to see अगर we are able to पढ़ो from card any device info at all */

	debug("inside configure_card, func->busno = %x\n", func->busno);

	device = func->device;
	cur_func = func;

	/* We only get bus and device from IRQ routing table.  So at this poपूर्णांक,
	 * func->busno is correct, and func->device contains only device (at the 5
	 * highest bits)
	 */

	/* For every function on the card */
	क्रम (function = 0x00; function < 0x08; function++) अणु
		अचिन्हित पूर्णांक devfn = PCI_DEVFN(device, function);
		ibmphp_pci_bus->number = cur_func->busno;

		cur_func->function = function;

		debug("inside the loop, cur_func->busno = %x, cur_func->device = %x, cur_func->function = %x\n",
			cur_func->busno, cur_func->device, cur_func->function);

		pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_VENDOR_ID, &venकरोr_id);

		debug("vendor_id is %x\n", venकरोr_id);
		अगर (venकरोr_id != PCI_VENDOR_ID_NOTVALID) अणु
			/* found correct device!!! */
			debug("found valid device, vendor_id = %x\n", venकरोr_id);

			++valid_device;

			/* header: x x x x x x x x
			 *         | |___________|=> 1=PPB bridge, 0=normal device, 2=CardBus Bridge
			 *         |_=> 0 = single function device, 1 = multi-function device
			 */

			pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_HEADER_TYPE, &hdr_type);
			pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, PCI_CLASS_REVISION, &class);

			class_code = class >> 24;
			debug("hrd_type = %x, class = %x, class_code %x\n", hdr_type, class, class_code);
			class >>= 8;	/* to take revision out, class = class.subclass.prog i/f */
			अगर (class == PCI_CLASS_NOT_DEFINED_VGA) अणु
				err("The device %x is VGA compatible and as is not supported for hot plugging. "
				     "Please choose another device.\n", cur_func->device);
				वापस -ENODEV;
			पूर्ण अन्यथा अगर (class == PCI_CLASS_DISPLAY_VGA) अणु
				err("The device %x is not supported for hot plugging. Please choose another device.\n",
				     cur_func->device);
				वापस -ENODEV;
			पूर्ण
			चयन (hdr_type) अणु
				हाल PCI_HEADER_TYPE_NORMAL:
					debug("single device case.... vendor id = %x, hdr_type = %x, class = %x\n", venकरोr_id, hdr_type, class);
					assign_alt_irq(cur_func, class_code);
					rc = configure_device(cur_func);
					अगर (rc < 0) अणु
						/* We need to करो this in हाल some other BARs were properly inserted */
						err("was not able to configure devfunc %x on bus %x.\n",
						     cur_func->device, cur_func->busno);
						cleanup_count = 6;
						जाओ error;
					पूर्ण
					cur_func->next = शून्य;
					function = 0x8;
					अवरोध;
				हाल PCI_HEADER_TYPE_MULTIDEVICE:
					assign_alt_irq(cur_func, class_code);
					rc = configure_device(cur_func);
					अगर (rc < 0) अणु
						/* We need to करो this in हाल some other BARs were properly inserted */
						err("was not able to configure devfunc %x on bus %x...bailing out\n",
						     cur_func->device, cur_func->busno);
						cleanup_count = 6;
						जाओ error;
					पूर्ण
					newfunc = kzalloc(माप(*newfunc), GFP_KERNEL);
					अगर (!newfunc)
						वापस -ENOMEM;

					newfunc->busno = cur_func->busno;
					newfunc->device = device;
					cur_func->next = newfunc;
					cur_func = newfunc;
					क्रम (j = 0; j < 4; j++)
						newfunc->irq[j] = cur_func->irq[j];
					अवरोध;
				हाल PCI_HEADER_TYPE_MULTIBRIDGE:
					class >>= 8;
					अगर (class != PCI_CLASS_BRIDGE_PCI) अणु
						err("This %x is not PCI-to-PCI bridge, and as is not supported for hot-plugging.  Please insert another card.\n",
						     cur_func->device);
						वापस -ENODEV;
					पूर्ण
					assign_alt_irq(cur_func, class_code);
					rc = configure_bridge(&cur_func, slotno);
					अगर (rc == -ENODEV) अणु
						err("You chose to insert Single Bridge, or nested bridges, this is not supported...\n");
						err("Bus %x, devfunc %x\n", cur_func->busno, cur_func->device);
						वापस rc;
					पूर्ण
					अगर (rc) अणु
						/* We need to करो this in हाल some other BARs were properly inserted */
						err("was not able to hot-add PPB properly.\n");
						func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
						cleanup_count = 2;
						जाओ error;
					पूर्ण

					pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, &sec_number);
					flag = 0;
					क्रम (i = 0; i < 32; i++) अणु
						अगर (func->devices[i]) अणु
							newfunc = kzalloc(माप(*newfunc), GFP_KERNEL);
							अगर (!newfunc)
								वापस -ENOMEM;

							newfunc->busno = sec_number;
							newfunc->device = (u8) i;
							क्रम (j = 0; j < 4; j++)
								newfunc->irq[j] = cur_func->irq[j];

							अगर (flag) अणु
								क्रम (prev_func = cur_func; prev_func->next; prev_func = prev_func->next) ;
								prev_func->next = newfunc;
							पूर्ण अन्यथा
								cur_func->next = newfunc;

							rc = ibmphp_configure_card(newfunc, slotno);
							/* This could only happen अगर kदो_स्मृति failed */
							अगर (rc) अणु
								/* We need to करो this in हाल bridge itself got configured properly, but devices behind it failed */
								func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
								cleanup_count = 2;
								जाओ error;
							पूर्ण
							flag = 1;
						पूर्ण
					पूर्ण

					newfunc = kzalloc(माप(*newfunc), GFP_KERNEL);
					अगर (!newfunc)
						वापस -ENOMEM;

					newfunc->busno = cur_func->busno;
					newfunc->device = device;
					क्रम (j = 0; j < 4; j++)
						newfunc->irq[j] = cur_func->irq[j];
					क्रम (prev_func = cur_func; prev_func->next; prev_func = prev_func->next);
					prev_func->next = newfunc;
					cur_func = newfunc;
					अवरोध;
				हाल PCI_HEADER_TYPE_BRIDGE:
					class >>= 8;
					debug("class now is %x\n", class);
					अगर (class != PCI_CLASS_BRIDGE_PCI) अणु
						err("This %x is not PCI-to-PCI bridge, and as is not supported for hot-plugging.  Please insert another card.\n",
						     cur_func->device);
						वापस -ENODEV;
					पूर्ण

					assign_alt_irq(cur_func, class_code);

					debug("cur_func->busno b4 configure_bridge is %x\n", cur_func->busno);
					rc = configure_bridge(&cur_func, slotno);
					अगर (rc == -ENODEV) अणु
						err("You chose to insert Single Bridge, or nested bridges, this is not supported...\n");
						err("Bus %x, devfunc %x\n", cur_func->busno, cur_func->device);
						वापस rc;
					पूर्ण
					अगर (rc) अणु
						/* We need to करो this in हाल some other BARs were properly inserted */
						func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
						err("was not able to hot-add PPB properly.\n");
						cleanup_count = 2;
						जाओ error;
					पूर्ण
					debug("cur_func->busno = %x, device = %x, function = %x\n",
						cur_func->busno, device, function);
					pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, &sec_number);
					debug("after configuring bridge..., sec_number = %x\n", sec_number);
					flag = 0;
					क्रम (i = 0; i < 32; i++) अणु
						अगर (func->devices[i]) अणु
							debug("inside for loop, device is %x\n", i);
							newfunc = kzalloc(माप(*newfunc), GFP_KERNEL);
							अगर (!newfunc)
								वापस -ENOMEM;

							newfunc->busno = sec_number;
							newfunc->device = (u8) i;
							क्रम (j = 0; j < 4; j++)
								newfunc->irq[j] = cur_func->irq[j];

							अगर (flag) अणु
								क्रम (prev_func = cur_func; prev_func->next; prev_func = prev_func->next);
								prev_func->next = newfunc;
							पूर्ण अन्यथा
								cur_func->next = newfunc;

							rc = ibmphp_configure_card(newfunc, slotno);

							/* Again, this हाल should not happen... For complete paranoia, will need to call हटाओ_bus */
							अगर (rc) अणु
								/* We need to करो this in हाल some other BARs were properly inserted */
								func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
								cleanup_count = 2;
								जाओ error;
							पूर्ण
							flag = 1;
						पूर्ण
					पूर्ण

					function = 0x8;
					अवरोध;
				शेष:
					err("MAJOR PROBLEM!!!!, header type not supported? %x\n", hdr_type);
					वापस -ENXIO;
			पूर्ण	/* end of चयन */
		पूर्ण	/* end of valid device */
	पूर्ण	/* end of क्रम */

	अगर (!valid_device) अणु
		err("Cannot find any valid devices on the card.  Or unable to read from card.\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;

error:
	क्रम (i = 0; i < cleanup_count; i++) अणु
		अगर (cur_func->io[i]) अणु
			ibmphp_हटाओ_resource(cur_func->io[i]);
			cur_func->io[i] = शून्य;
		पूर्ण अन्यथा अगर (cur_func->pfmem[i]) अणु
			ibmphp_हटाओ_resource(cur_func->pfmem[i]);
			cur_func->pfmem[i] = शून्य;
		पूर्ण अन्यथा अगर (cur_func->mem[i]) अणु
			ibmphp_हटाओ_resource(cur_func->mem[i]);
			cur_func->mem[i] = शून्य;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/*
 * This function configures the pci BARs of a single device.
 * Input: poपूर्णांकer to the pci_func
 * Output: configured PCI, 0, or error
 */
अटल पूर्णांक configure_device(काष्ठा pci_func *func)
अणु
	u32 bar[6];
	u32 address[] = अणु
		PCI_BASE_ADDRESS_0,
		PCI_BASE_ADDRESS_1,
		PCI_BASE_ADDRESS_2,
		PCI_BASE_ADDRESS_3,
		PCI_BASE_ADDRESS_4,
		PCI_BASE_ADDRESS_5,
		0
	पूर्ण;
	u8 irq;
	पूर्णांक count;
	पूर्णांक len[6];
	काष्ठा resource_node *io[6];
	काष्ठा resource_node *mem[6];
	काष्ठा resource_node *mem_पंचांगp;
	काष्ठा resource_node *pfmem[6];
	अचिन्हित पूर्णांक devfn;

	debug("%s - inside\n", __func__);

	devfn = PCI_DEVFN(func->device, func->function);
	ibmphp_pci_bus->number = func->busno;

	क्रम (count = 0; address[count]; count++) अणु	/* क्रम 6 BARs */

		/* not sure अगर i need this.  per scott, said maybe need * something like this
		   अगर devices करोn't adhere 100% to the spec, so don't want to ग_लिखो
		   to the reserved bits

		pcibios_पढ़ो_config_byte(cur_func->busno, cur_func->device,
		PCI_BASE_ADDRESS_0 + 4 * count, &पंचांगp);
		अगर (पंचांगp & 0x01) // IO
			pcibios_ग_लिखो_config_dword(cur_func->busno, cur_func->device,
			PCI_BASE_ADDRESS_0 + 4 * count, 0xFFFFFFFD);
		अन्यथा  // Memory
			pcibios_ग_लिखो_config_dword(cur_func->busno, cur_func->device,
			PCI_BASE_ADDRESS_0 + 4 * count, 0xFFFFFFFF);
		 */
		pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0xFFFFFFFF);
		pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &bar[count]);

		अगर (!bar[count])	/* This BAR is not implemented */
			जारी;

		debug("Device %x BAR %d wants %x\n", func->device, count, bar[count]);

		अगर (bar[count] & PCI_BASE_ADDRESS_SPACE_IO) अणु
			/* This is IO */
			debug("inside IO SPACE\n");

			len[count] = bar[count] & 0xFFFFFFFC;
			len[count] = ~len[count] + 1;

			debug("len[count] in IO %x, count %d\n", len[count], count);

			io[count] = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);

			अगर (!io[count])
				वापस -ENOMEM;

			io[count]->type = IO;
			io[count]->busno = func->busno;
			io[count]->devfunc = PCI_DEVFN(func->device, func->function);
			io[count]->len = len[count];
			अगर (ibmphp_check_resource(io[count], 0) == 0) अणु
				ibmphp_add_resource(io[count]);
				func->io[count] = io[count];
			पूर्ण अन्यथा अणु
				err("cannot allocate requested io for bus %x device %x function %x len %x\n",
				     func->busno, func->device, func->function, len[count]);
				kमुक्त(io[count]);
				वापस -EIO;
			पूर्ण
			pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], func->io[count]->start);

			/* _______________This is क्रम debugging purposes only_____________________ */
			debug("b4 writing, the IO address is %x\n", func->io[count]->start);
			pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &bar[count]);
			debug("after writing.... the start address is %x\n", bar[count]);
			/* _________________________________________________________________________*/

		पूर्ण अन्यथा अणु
			/* This is Memory */
			अगर (bar[count] & PCI_BASE_ADDRESS_MEM_PREFETCH) अणु
				/* pfmem */
				debug("PFMEM SPACE\n");

				len[count] = bar[count] & 0xFFFFFFF0;
				len[count] = ~len[count] + 1;

				debug("len[count] in PFMEM %x, count %d\n", len[count], count);

				pfmem[count] = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
				अगर (!pfmem[count])
					वापस -ENOMEM;

				pfmem[count]->type = PFMEM;
				pfmem[count]->busno = func->busno;
				pfmem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				pfmem[count]->len = len[count];
				pfmem[count]->fromMem = 0;
				अगर (ibmphp_check_resource(pfmem[count], 0) == 0) अणु
					ibmphp_add_resource(pfmem[count]);
					func->pfmem[count] = pfmem[count];
				पूर्ण अन्यथा अणु
					mem_पंचांगp = kzalloc(माप(*mem_पंचांगp), GFP_KERNEL);
					अगर (!mem_पंचांगp) अणु
						kमुक्त(pfmem[count]);
						वापस -ENOMEM;
					पूर्ण
					mem_पंचांगp->type = MEM;
					mem_पंचांगp->busno = pfmem[count]->busno;
					mem_पंचांगp->devfunc = pfmem[count]->devfunc;
					mem_पंचांगp->len = pfmem[count]->len;
					debug("there's no pfmem... going into mem.\n");
					अगर (ibmphp_check_resource(mem_पंचांगp, 0) == 0) अणु
						ibmphp_add_resource(mem_पंचांगp);
						pfmem[count]->fromMem = 1;
						pfmem[count]->rangeno = mem_पंचांगp->rangeno;
						pfmem[count]->start = mem_पंचांगp->start;
						pfmem[count]->end = mem_पंचांगp->end;
						ibmphp_add_pfmem_from_mem(pfmem[count]);
						func->pfmem[count] = pfmem[count];
					पूर्ण अन्यथा अणु
						err("cannot allocate requested pfmem for bus %x, device %x, len %x\n",
						     func->busno, func->device, len[count]);
						kमुक्त(mem_पंचांगp);
						kमुक्त(pfmem[count]);
						वापस -EIO;
					पूर्ण
				पूर्ण

				pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], func->pfmem[count]->start);

				/*_______________This is क्रम debugging purposes only______________________________*/
				debug("b4 writing, start address is %x\n", func->pfmem[count]->start);
				pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &bar[count]);
				debug("after writing, start address is %x\n", bar[count]);
				/*_________________________________________________________________________________*/

				अगर (bar[count] & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु	/* takes up another dword */
					debug("inside the mem 64 case, count %d\n", count);
					count += 1;
					/* on the 2nd dword, ग_लिखो all 0s, since we can't handle them n.e.ways */
					pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0x00000000);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* regular memory */
				debug("REGULAR MEM SPACE\n");

				len[count] = bar[count] & 0xFFFFFFF0;
				len[count] = ~len[count] + 1;

				debug("len[count] in Mem %x, count %d\n", len[count], count);

				mem[count] = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
				अगर (!mem[count])
					वापस -ENOMEM;

				mem[count]->type = MEM;
				mem[count]->busno = func->busno;
				mem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				mem[count]->len = len[count];
				अगर (ibmphp_check_resource(mem[count], 0) == 0) अणु
					ibmphp_add_resource(mem[count]);
					func->mem[count] = mem[count];
				पूर्ण अन्यथा अणु
					err("cannot allocate requested mem for bus %x, device %x, len %x\n",
					     func->busno, func->device, len[count]);
					kमुक्त(mem[count]);
					वापस -EIO;
				पूर्ण
				pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], func->mem[count]->start);
				/* _______________________This is क्रम debugging purposes only _______________________*/
				debug("b4 writing, start address is %x\n", func->mem[count]->start);
				pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &bar[count]);
				debug("after writing, the address is %x\n", bar[count]);
				/* __________________________________________________________________________________*/

				अगर (bar[count] & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
					/* takes up another dword */
					debug("inside mem 64 case, reg. mem, count %d\n", count);
					count += 1;
					/* on the 2nd dword, ग_लिखो all 0s, since we can't handle them n.e.ways */
					pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0x00000000);
				पूर्ण
			पूर्ण
		पूर्ण		/* end of mem */
	पूर्ण			/* end of क्रम */

	func->bus = 0;		/* To indicate that this is not a PPB */
	pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_INTERRUPT_PIN, &irq);
	अगर ((irq > 0x00) && (irq < 0x05))
		pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_INTERRUPT_LINE, func->irq[irq - 1]);

	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_CACHE_LINE_SIZE, CACHE);
	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_LATENCY_TIMER, LATENCY);

	pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, PCI_ROM_ADDRESS, 0x00L);
	pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_COMMAND, DEVICEENABLE);

	वापस 0;
पूर्ण

/******************************************************************************
 * This routine configures a PCI-2-PCI bridge and the functions behind it
 * Parameters: pci_func
 * Returns:
 ******************************************************************************/
अटल पूर्णांक configure_bridge(काष्ठा pci_func **func_passed, u8 slotno)
अणु
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक rc;
	u8 sec_number;
	u8 io_base;
	u16 pfmem_base;
	u32 bar[2];
	u32 len[2];
	u8 flag_io = 0;
	u8 flag_mem = 0;
	u8 flag_pfmem = 0;
	u8 need_io_upper = 0;
	u8 need_pfmem_upper = 0;
	काष्ठा res_needed *amount_needed = शून्य;
	काष्ठा resource_node *io = शून्य;
	काष्ठा resource_node *bus_io[2] = अणुशून्य, शून्यपूर्ण;
	काष्ठा resource_node *mem = शून्य;
	काष्ठा resource_node *bus_mem[2] = अणुशून्य, शून्यपूर्ण;
	काष्ठा resource_node *mem_पंचांगp = शून्य;
	काष्ठा resource_node *pfmem = शून्य;
	काष्ठा resource_node *bus_pfmem[2] = अणुशून्य, शून्यपूर्ण;
	काष्ठा bus_node *bus;
	u32 address[] = अणु
		PCI_BASE_ADDRESS_0,
		PCI_BASE_ADDRESS_1,
		0
	पूर्ण;
	काष्ठा pci_func *func = *func_passed;
	अचिन्हित पूर्णांक devfn;
	u8 irq;
	पूर्णांक retval;

	debug("%s - enter\n", __func__);

	devfn = PCI_DEVFN(func->function, func->device);
	ibmphp_pci_bus->number = func->busno;

	/* Configuring necessary info क्रम the bridge so that we could see the devices
	 * behind it
	 */

	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_PRIMARY_BUS, func->busno);

	/* _____________________For debugging purposes only __________________________
	pci_bus_config_byte(ibmphp_pci_bus, devfn, PCI_PRIMARY_BUS, &pri_number);
	debug("primary # written into the bridge is %x\n", pri_number);
	 ___________________________________________________________________________*/

	/* in EBDA, only get allocated 1 additional bus # per slot */
	sec_number = find_sec_number(func->busno, slotno);
	अगर (sec_number == 0xff) अणु
		err("cannot allocate secondary bus number for the bridged device\n");
		वापस -EINVAL;
	पूर्ण

	debug("after find_sec_number, the number we got is %x\n", sec_number);
	debug("AFTER FIND_SEC_NUMBER, func->busno IS %x\n", func->busno);

	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, sec_number);

	/* __________________For debugging purposes only __________________________________
	pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, &sec_number);
	debug("sec_number after write/read is %x\n", sec_number);
	 ________________________________________________________________________________*/

	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_SUBORDINATE_BUS, sec_number);

	/* __________________For debugging purposes only ____________________________________
	pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_SUBORDINATE_BUS, &sec_number);
	debug("subordinate number after write/read is %x\n", sec_number);
	 __________________________________________________________________________________*/

	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_CACHE_LINE_SIZE, CACHE);
	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_LATENCY_TIMER, LATENCY);
	pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_SEC_LATENCY_TIMER, LATENCY);

	debug("func->busno is %x\n", func->busno);
	debug("sec_number after writing is %x\n", sec_number);


	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   !!!!!!!!!!!!!!!NEED TO ADD!!!  FAST BACK-TO-BACK ENABLE!!!!!!!!!!!!!!!!!!!!
	   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


	/* First we need to allocate mem/io क्रम the bridge itself in हाल it needs it */
	क्रम (count = 0; address[count]; count++) अणु	/* क्रम 2 BARs */
		pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0xFFFFFFFF);
		pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &bar[count]);

		अगर (!bar[count]) अणु
			/* This BAR is not implemented */
			debug("so we come here then, eh?, count = %d\n", count);
			जारी;
		पूर्ण
		//  पंचांगp_bar = bar[count];

		debug("Bar %d wants %x\n", count, bar[count]);

		अगर (bar[count] & PCI_BASE_ADDRESS_SPACE_IO) अणु
			/* This is IO */
			len[count] = bar[count] & 0xFFFFFFFC;
			len[count] = ~len[count] + 1;

			debug("len[count] in IO = %x\n", len[count]);

			bus_io[count] = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);

			अगर (!bus_io[count]) अणु
				retval = -ENOMEM;
				जाओ error;
			पूर्ण
			bus_io[count]->type = IO;
			bus_io[count]->busno = func->busno;
			bus_io[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
			bus_io[count]->len = len[count];
			अगर (ibmphp_check_resource(bus_io[count], 0) == 0) अणु
				ibmphp_add_resource(bus_io[count]);
				func->io[count] = bus_io[count];
			पूर्ण अन्यथा अणु
				err("cannot allocate requested io for bus %x, device %x, len %x\n",
				     func->busno, func->device, len[count]);
				kमुक्त(bus_io[count]);
				वापस -EIO;
			पूर्ण

			pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], func->io[count]->start);

		पूर्ण अन्यथा अणु
			/* This is Memory */
			अगर (bar[count] & PCI_BASE_ADDRESS_MEM_PREFETCH) अणु
				/* pfmem */
				len[count] = bar[count] & 0xFFFFFFF0;
				len[count] = ~len[count] + 1;

				debug("len[count] in PFMEM = %x\n", len[count]);

				bus_pfmem[count] = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
				अगर (!bus_pfmem[count]) अणु
					retval = -ENOMEM;
					जाओ error;
				पूर्ण
				bus_pfmem[count]->type = PFMEM;
				bus_pfmem[count]->busno = func->busno;
				bus_pfmem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				bus_pfmem[count]->len = len[count];
				bus_pfmem[count]->fromMem = 0;
				अगर (ibmphp_check_resource(bus_pfmem[count], 0) == 0) अणु
					ibmphp_add_resource(bus_pfmem[count]);
					func->pfmem[count] = bus_pfmem[count];
				पूर्ण अन्यथा अणु
					mem_पंचांगp = kzalloc(माप(*mem_पंचांगp), GFP_KERNEL);
					अगर (!mem_पंचांगp) अणु
						retval = -ENOMEM;
						जाओ error;
					पूर्ण
					mem_पंचांगp->type = MEM;
					mem_पंचांगp->busno = bus_pfmem[count]->busno;
					mem_पंचांगp->devfunc = bus_pfmem[count]->devfunc;
					mem_पंचांगp->len = bus_pfmem[count]->len;
					अगर (ibmphp_check_resource(mem_पंचांगp, 0) == 0) अणु
						ibmphp_add_resource(mem_पंचांगp);
						bus_pfmem[count]->fromMem = 1;
						bus_pfmem[count]->rangeno = mem_पंचांगp->rangeno;
						ibmphp_add_pfmem_from_mem(bus_pfmem[count]);
						func->pfmem[count] = bus_pfmem[count];
					पूर्ण अन्यथा अणु
						err("cannot allocate requested pfmem for bus %x, device %x, len %x\n",
						     func->busno, func->device, len[count]);
						kमुक्त(mem_पंचांगp);
						kमुक्त(bus_pfmem[count]);
						वापस -EIO;
					पूर्ण
				पूर्ण

				pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], func->pfmem[count]->start);

				अगर (bar[count] & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
					/* takes up another dword */
					count += 1;
					/* on the 2nd dword, ग_लिखो all 0s, since we can't handle them n.e.ways */
					pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0x00000000);

				पूर्ण
			पूर्ण अन्यथा अणु
				/* regular memory */
				len[count] = bar[count] & 0xFFFFFFF0;
				len[count] = ~len[count] + 1;

				debug("len[count] in Memory is %x\n", len[count]);

				bus_mem[count] = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
				अगर (!bus_mem[count]) अणु
					retval = -ENOMEM;
					जाओ error;
				पूर्ण
				bus_mem[count]->type = MEM;
				bus_mem[count]->busno = func->busno;
				bus_mem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				bus_mem[count]->len = len[count];
				अगर (ibmphp_check_resource(bus_mem[count], 0) == 0) अणु
					ibmphp_add_resource(bus_mem[count]);
					func->mem[count] = bus_mem[count];
				पूर्ण अन्यथा अणु
					err("cannot allocate requested mem for bus %x, device %x, len %x\n",
					     func->busno, func->device, len[count]);
					kमुक्त(bus_mem[count]);
					वापस -EIO;
				पूर्ण

				pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], func->mem[count]->start);

				अगर (bar[count] & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
					/* takes up another dword */
					count += 1;
					/* on the 2nd dword, ग_लिखो all 0s, since we can't handle them n.e.ways */
					pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0x00000000);

				पूर्ण
			पूर्ण
		पूर्ण		/* end of mem */
	पूर्ण			/* end of क्रम  */

	/* Now need to see how much space the devices behind the bridge needed */
	amount_needed = scan_behind_bridge(func, sec_number);
	अगर (amount_needed == शून्य)
		वापस -ENOMEM;

	ibmphp_pci_bus->number = func->busno;
	debug("after coming back from scan_behind_bridge\n");
	debug("amount_needed->not_correct = %x\n", amount_needed->not_correct);
	debug("amount_needed->io = %x\n", amount_needed->io);
	debug("amount_needed->mem = %x\n", amount_needed->mem);
	debug("amount_needed->pfmem =  %x\n", amount_needed->pfmem);

	अगर (amount_needed->not_correct) अणु
		debug("amount_needed is not correct\n");
		क्रम (count = 0; address[count]; count++) अणु
			/* क्रम 2 BARs */
			अगर (bus_io[count]) अणु
				ibmphp_हटाओ_resource(bus_io[count]);
				func->io[count] = शून्य;
			पूर्ण अन्यथा अगर (bus_pfmem[count]) अणु
				ibmphp_हटाओ_resource(bus_pfmem[count]);
				func->pfmem[count] = शून्य;
			पूर्ण अन्यथा अगर (bus_mem[count]) अणु
				ibmphp_हटाओ_resource(bus_mem[count]);
				func->mem[count] = शून्य;
			पूर्ण
		पूर्ण
		kमुक्त(amount_needed);
		वापस -ENODEV;
	पूर्ण

	अगर (!amount_needed->io) अणु
		debug("it doesn't want IO?\n");
		flag_io = 1;
	पूर्ण अन्यथा अणु
		debug("it wants %x IO behind the bridge\n", amount_needed->io);
		io = kzalloc(माप(*io), GFP_KERNEL);

		अगर (!io) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण
		io->type = IO;
		io->busno = func->busno;
		io->devfunc = PCI_DEVFN(func->device, func->function);
		io->len = amount_needed->io;
		अगर (ibmphp_check_resource(io, 1) == 0) अणु
			debug("were we able to add io\n");
			ibmphp_add_resource(io);
			flag_io = 1;
		पूर्ण
	पूर्ण

	अगर (!amount_needed->mem) अणु
		debug("it doesn't want n.e.memory?\n");
		flag_mem = 1;
	पूर्ण अन्यथा अणु
		debug("it wants %x memory behind the bridge\n", amount_needed->mem);
		mem = kzalloc(माप(*mem), GFP_KERNEL);
		अगर (!mem) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण
		mem->type = MEM;
		mem->busno = func->busno;
		mem->devfunc = PCI_DEVFN(func->device, func->function);
		mem->len = amount_needed->mem;
		अगर (ibmphp_check_resource(mem, 1) == 0) अणु
			ibmphp_add_resource(mem);
			flag_mem = 1;
			debug("were we able to add mem\n");
		पूर्ण
	पूर्ण

	अगर (!amount_needed->pfmem) अणु
		debug("it doesn't want n.e.pfmem mem?\n");
		flag_pfmem = 1;
	पूर्ण अन्यथा अणु
		debug("it wants %x pfmemory behind the bridge\n", amount_needed->pfmem);
		pfmem = kzalloc(माप(*pfmem), GFP_KERNEL);
		अगर (!pfmem) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण
		pfmem->type = PFMEM;
		pfmem->busno = func->busno;
		pfmem->devfunc = PCI_DEVFN(func->device, func->function);
		pfmem->len = amount_needed->pfmem;
		pfmem->fromMem = 0;
		अगर (ibmphp_check_resource(pfmem, 1) == 0) अणु
			ibmphp_add_resource(pfmem);
			flag_pfmem = 1;
		पूर्ण अन्यथा अणु
			mem_पंचांगp = kzalloc(माप(*mem_पंचांगp), GFP_KERNEL);
			अगर (!mem_पंचांगp) अणु
				retval = -ENOMEM;
				जाओ error;
			पूर्ण
			mem_पंचांगp->type = MEM;
			mem_पंचांगp->busno = pfmem->busno;
			mem_पंचांगp->devfunc = pfmem->devfunc;
			mem_पंचांगp->len = pfmem->len;
			अगर (ibmphp_check_resource(mem_पंचांगp, 1) == 0) अणु
				ibmphp_add_resource(mem_पंचांगp);
				pfmem->fromMem = 1;
				pfmem->rangeno = mem_पंचांगp->rangeno;
				ibmphp_add_pfmem_from_mem(pfmem);
				flag_pfmem = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	debug("b4 if (flag_io && flag_mem && flag_pfmem)\n");
	debug("flag_io = %x, flag_mem = %x, flag_pfmem = %x\n", flag_io, flag_mem, flag_pfmem);

	अगर (flag_io && flag_mem && flag_pfmem) अणु
		/* If on bootup, there was a bridged card in this slot,
		 * then card was हटाओd and ibmphp got unloaded and loaded
		 * back again, there's no way क्रम us to हटाओ the bus
		 * काष्ठा, so no need to kदो_स्मृति, can use existing node
		 */
		bus = ibmphp_find_res_bus(sec_number);
		अगर (!bus) अणु
			bus = kzalloc(माप(*bus), GFP_KERNEL);
			अगर (!bus) अणु
				retval = -ENOMEM;
				जाओ error;
			पूर्ण
			bus->busno = sec_number;
			debug("b4 adding new bus\n");
			rc = add_new_bus(bus, io, mem, pfmem, func->busno);
		पूर्ण अन्यथा अगर (!(bus->rangeIO) && !(bus->rangeMem) && !(bus->rangePFMem))
			rc = add_new_bus(bus, io, mem, pfmem, 0xFF);
		अन्यथा अणु
			err("expected bus structure not empty?\n");
			retval = -EIO;
			जाओ error;
		पूर्ण
		अगर (rc) अणु
			अगर (rc == -ENOMEM) अणु
				ibmphp_हटाओ_bus(bus, func->busno);
				kमुक्त(amount_needed);
				वापस rc;
			पूर्ण
			retval = rc;
			जाओ error;
		पूर्ण
		pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, &io_base);
		pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_BASE, &pfmem_base);

		अगर ((io_base & PCI_IO_RANGE_TYPE_MASK) == PCI_IO_RANGE_TYPE_32) अणु
			debug("io 32\n");
			need_io_upper = 1;
		पूर्ण
		अगर ((pfmem_base & PCI_PREF_RANGE_TYPE_MASK) == PCI_PREF_RANGE_TYPE_64) अणु
			debug("pfmem 64\n");
			need_pfmem_upper = 1;
		पूर्ण

		अगर (bus->noIORanges) अणु
			pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, 0x00 | bus->rangeIO->start >> 8);
			pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_LIMIT, 0x00 | bus->rangeIO->end >> 8);

			/* _______________This is क्रम debugging purposes only ____________________
			pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, &temp);
			debug("io_base = %x\n", (temp & PCI_IO_RANGE_TYPE_MASK) << 8);
			pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_LIMIT, &temp);
			debug("io_limit = %x\n", (temp & PCI_IO_RANGE_TYPE_MASK) << 8);
			 ________________________________________________________________________*/

			अगर (need_io_upper) अणु	/* since can't support n.e.ways */
				pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_IO_BASE_UPPER16, 0x0000);
				pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_IO_LIMIT_UPPER16, 0x0000);
			पूर्ण
		पूर्ण अन्यथा अणु
			pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, 0x00);
			pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_LIMIT, 0x00);
		पूर्ण

		अगर (bus->noMemRanges) अणु
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_BASE, 0x0000 | bus->rangeMem->start >> 16);
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_LIMIT, 0x0000 | bus->rangeMem->end >> 16);

			/* ____________________This is क्रम debugging purposes only ________________________
			pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_BASE, &temp);
			debug("mem_base = %x\n", (temp & PCI_MEMORY_RANGE_TYPE_MASK) << 16);
			pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_LIMIT, &temp);
			debug("mem_limit = %x\n", (temp & PCI_MEMORY_RANGE_TYPE_MASK) << 16);
			 __________________________________________________________________________________*/

		पूर्ण अन्यथा अणु
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_BASE, 0xffff);
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_LIMIT, 0x0000);
		पूर्ण
		अगर (bus->noPFMemRanges) अणु
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_BASE, 0x0000 | bus->rangePFMem->start >> 16);
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, 0x0000 | bus->rangePFMem->end >> 16);

			/* __________________________This is क्रम debugging purposes only _______________________
			pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_BASE, &temp);
			debug("pfmem_base = %x", (temp & PCI_MEMORY_RANGE_TYPE_MASK) << 16);
			pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, &temp);
			debug("pfmem_limit = %x\n", (temp & PCI_MEMORY_RANGE_TYPE_MASK) << 16);
			 ______________________________________________________________________________________*/

			अगर (need_pfmem_upper) अणु	/* since can't support n.e.ways */
				pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, PCI_PREF_BASE_UPPER32, 0x00000000);
				pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, PCI_PREF_LIMIT_UPPER32, 0x00000000);
			पूर्ण
		पूर्ण अन्यथा अणु
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_BASE, 0xffff);
			pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, 0x0000);
		पूर्ण

		debug("b4 writing control information\n");

		pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_INTERRUPT_PIN, &irq);
		अगर ((irq > 0x00) && (irq < 0x05))
			pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_INTERRUPT_LINE, func->irq[irq - 1]);
		/*
		pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_BRIDGE_CONTROL, ctrl);
		pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_BRIDGE_CONTROL, PCI_BRIDGE_CTL_PARITY);
		pci_bus_ग_लिखो_config_byte(ibmphp_pci_bus, devfn, PCI_BRIDGE_CONTROL, PCI_BRIDGE_CTL_SERR);
		 */

		pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_COMMAND, DEVICEENABLE);
		pci_bus_ग_लिखो_config_word(ibmphp_pci_bus, devfn, PCI_BRIDGE_CONTROL, 0x07);
		क्रम (i = 0; i < 32; i++) अणु
			अगर (amount_needed->devices[i]) अणु
				debug("device where devices[i] is 1 = %x\n", i);
				func->devices[i] = 1;
			पूर्ण
		पूर्ण
		func->bus = 1;	/* For unconfiguring, to indicate it's PPB */
		func_passed = &func;
		debug("func->busno b4 returning is %x\n", func->busno);
		debug("func->busno b4 returning in the other structure is %x\n", (*func_passed)->busno);
		kमुक्त(amount_needed);
		वापस 0;
	पूर्ण अन्यथा अणु
		err("Configuring bridge was unsuccessful...\n");
		mem_पंचांगp = शून्य;
		retval = -EIO;
		जाओ error;
	पूर्ण

error:
	kमुक्त(amount_needed);
	अगर (pfmem)
		ibmphp_हटाओ_resource(pfmem);
	अगर (io)
		ibmphp_हटाओ_resource(io);
	अगर (mem)
		ibmphp_हटाओ_resource(mem);
	क्रम (i = 0; i < 2; i++) अणु	/* क्रम 2 BARs */
		अगर (bus_io[i]) अणु
			ibmphp_हटाओ_resource(bus_io[i]);
			func->io[i] = शून्य;
		पूर्ण अन्यथा अगर (bus_pfmem[i]) अणु
			ibmphp_हटाओ_resource(bus_pfmem[i]);
			func->pfmem[i] = शून्य;
		पूर्ण अन्यथा अगर (bus_mem[i]) अणु
			ibmphp_हटाओ_resource(bus_mem[i]);
			func->mem[i] = शून्य;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

/*****************************************************************************
 * This function adds up the amount of resources needed behind the PPB bridge
 * and passes it to the configure_bridge function
 * Input: bridge function
 * Output: amount of resources needed
 *****************************************************************************/
अटल काष्ठा res_needed *scan_behind_bridge(काष्ठा pci_func *func, u8 busno)
अणु
	पूर्णांक count, len[6];
	u16 venकरोr_id;
	u8 hdr_type;
	u8 device, function;
	अचिन्हित पूर्णांक devfn;
	पूर्णांक howmany = 0;	/*this is to see अगर there are any devices behind the bridge */

	u32 bar[6], class;
	u32 address[] = अणु
		PCI_BASE_ADDRESS_0,
		PCI_BASE_ADDRESS_1,
		PCI_BASE_ADDRESS_2,
		PCI_BASE_ADDRESS_3,
		PCI_BASE_ADDRESS_4,
		PCI_BASE_ADDRESS_5,
		0
	पूर्ण;
	काष्ठा res_needed *amount;

	amount = kzalloc(माप(*amount), GFP_KERNEL);
	अगर (amount == शून्य)
		वापस शून्य;

	ibmphp_pci_bus->number = busno;

	debug("the bus_no behind the bridge is %x\n", busno);
	debug("scanning devices behind the bridge...\n");
	क्रम (device = 0; device < 32; device++) अणु
		amount->devices[device] = 0;
		क्रम (function = 0; function < 8; function++) अणु
			devfn = PCI_DEVFN(device, function);

			pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_VENDOR_ID, &venकरोr_id);

			अगर (venकरोr_id != PCI_VENDOR_ID_NOTVALID) अणु
				/* found correct device!!! */
				howmany++;

				pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_HEADER_TYPE, &hdr_type);
				pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, PCI_CLASS_REVISION, &class);

				debug("hdr_type behind the bridge is %x\n", hdr_type);
				अगर ((hdr_type & 0x7f) == PCI_HEADER_TYPE_BRIDGE) अणु
					err("embedded bridges not supported for hot-plugging.\n");
					amount->not_correct = 1;
					वापस amount;
				पूर्ण

				class >>= 8;	/* to take revision out, class = class.subclass.prog i/f */
				अगर (class == PCI_CLASS_NOT_DEFINED_VGA) अणु
					err("The device %x is VGA compatible and as is not supported for hot plugging.  Please choose another device.\n", device);
					amount->not_correct = 1;
					वापस amount;
				पूर्ण अन्यथा अगर (class == PCI_CLASS_DISPLAY_VGA) अणु
					err("The device %x is not supported for hot plugging.  Please choose another device.\n", device);
					amount->not_correct = 1;
					वापस amount;
				पूर्ण

				amount->devices[device] = 1;

				क्रम (count = 0; address[count]; count++) अणु
					/* क्रम 6 BARs */
					/*
					pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, address[count], &पंचांगp);
					अगर (पंचांगp & 0x01) // IO
						pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0xFFFFFFFD);
					अन्यथा // MEMORY
						pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0xFFFFFFFF);
					*/
					pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0xFFFFFFFF);
					pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &bar[count]);

					debug("what is bar[count]? %x, count = %d\n", bar[count], count);

					अगर (!bar[count])	/* This BAR is not implemented */
						जारी;

					//पंचांगp_bar = bar[count];

					debug("count %d device %x function %x wants %x resources\n", count, device, function, bar[count]);

					अगर (bar[count] & PCI_BASE_ADDRESS_SPACE_IO) अणु
						/* This is IO */
						len[count] = bar[count] & 0xFFFFFFFC;
						len[count] = ~len[count] + 1;
						amount->io += len[count];
					पूर्ण अन्यथा अणु
						/* This is Memory */
						अगर (bar[count] & PCI_BASE_ADDRESS_MEM_PREFETCH) अणु
							/* pfmem */
							len[count] = bar[count] & 0xFFFFFFF0;
							len[count] = ~len[count] + 1;
							amount->pfmem += len[count];
							अगर (bar[count] & PCI_BASE_ADDRESS_MEM_TYPE_64)
								/* takes up another dword */
								count += 1;

						पूर्ण अन्यथा अणु
							/* regular memory */
							len[count] = bar[count] & 0xFFFFFFF0;
							len[count] = ~len[count] + 1;
							amount->mem += len[count];
							अगर (bar[count] & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
								/* takes up another dword */
								count += 1;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण	/* end क्रम */
			पूर्ण	/* end अगर (valid) */
		पूर्ण	/* end क्रम */
	पूर्ण	/* end क्रम */

	अगर (!howmany)
		amount->not_correct = 1;
	अन्यथा
		amount->not_correct = 0;
	अगर ((amount->io) && (amount->io < IOBRIDGE))
		amount->io = IOBRIDGE;
	अगर ((amount->mem) && (amount->mem < MEMBRIDGE))
		amount->mem = MEMBRIDGE;
	अगर ((amount->pfmem) && (amount->pfmem < MEMBRIDGE))
		amount->pfmem = MEMBRIDGE;
	वापस amount;
पूर्ण

/* The following 3 unconfigure_boot_ routines deal with the हाल when we had the card
 * upon bootup in the प्रणाली, since we करोn't allocate func to such हाल, we need to पढ़ो
 * the start addresses from pci config space and then find the corresponding entries in
 * our resource lists.  The functions वापस either 0, -ENODEV, or -1 (general failure)
 * Change: we also call these functions even अगर we configured the card ourselves (i.e., not
 * the bootup हाल), since it should work same way
 */
अटल पूर्णांक unconfigure_boot_device(u8 busno, u8 device, u8 function)
अणु
	u32 start_address;
	u32 address[] = अणु
		PCI_BASE_ADDRESS_0,
		PCI_BASE_ADDRESS_1,
		PCI_BASE_ADDRESS_2,
		PCI_BASE_ADDRESS_3,
		PCI_BASE_ADDRESS_4,
		PCI_BASE_ADDRESS_5,
		0
	पूर्ण;
	पूर्णांक count;
	काष्ठा resource_node *io;
	काष्ठा resource_node *mem;
	काष्ठा resource_node *pfmem;
	काष्ठा bus_node *bus;
	u32 end_address;
	u32 temp_end;
	u32 size;
	u32 पंचांगp_address;
	अचिन्हित पूर्णांक devfn;

	debug("%s - enter\n", __func__);

	bus = ibmphp_find_res_bus(busno);
	अगर (!bus) अणु
		debug("cannot find corresponding bus.\n");
		वापस -EINVAL;
	पूर्ण

	devfn = PCI_DEVFN(device, function);
	ibmphp_pci_bus->number = busno;
	क्रम (count = 0; address[count]; count++) अणु	/* क्रम 6 BARs */
		pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &start_address);

		/* We can करो this here, b/c by that समय the device driver of the card has been stopped */

		pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], 0xFFFFFFFF);
		pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &size);
		pci_bus_ग_लिखो_config_dword(ibmphp_pci_bus, devfn, address[count], start_address);

		debug("start_address is %x\n", start_address);
		debug("busno, device, function %x %x %x\n", busno, device, function);
		अगर (!size) अणु
			/* This BAR is not implemented */
			debug("is this bar no implemented?, count = %d\n", count);
			जारी;
		पूर्ण
		पंचांगp_address = start_address;
		अगर (start_address & PCI_BASE_ADDRESS_SPACE_IO) अणु
			/* This is IO */
			start_address &= PCI_BASE_ADDRESS_IO_MASK;
			size = size & 0xFFFFFFFC;
			size = ~size + 1;
			end_address = start_address + size - 1;
			अगर (ibmphp_find_resource(bus, start_address, &io, IO))
				जाओ report_search_failure;

			debug("io->start = %x\n", io->start);
			temp_end = io->end;
			start_address = io->end + 1;
			ibmphp_हटाओ_resource(io);
			/* This is needed b/c of the old I/O restrictions in the BIOS */
			जबतक (temp_end < end_address) अणु
				अगर (ibmphp_find_resource(bus, start_address,
							 &io, IO))
					जाओ report_search_failure;

				debug("io->start = %x\n", io->start);
				temp_end = io->end;
				start_address = io->end + 1;
				ibmphp_हटाओ_resource(io);
			पूर्ण

			/* ????????? DO WE NEED TO WRITE ANYTHING INTO THE PCI CONFIG SPACE BACK ?????????? */
		पूर्ण अन्यथा अणु
			/* This is Memory */
			अगर (start_address & PCI_BASE_ADDRESS_MEM_PREFETCH) अणु
				/* pfmem */
				debug("start address of pfmem is %x\n", start_address);
				start_address &= PCI_BASE_ADDRESS_MEM_MASK;

				अगर (ibmphp_find_resource(bus, start_address, &pfmem, PFMEM) < 0) अणु
					err("cannot find corresponding PFMEM resource to remove\n");
					वापस -EIO;
				पूर्ण
				अगर (pfmem) अणु
					debug("pfmem->start = %x\n", pfmem->start);

					ibmphp_हटाओ_resource(pfmem);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* regular memory */
				debug("start address of mem is %x\n", start_address);
				start_address &= PCI_BASE_ADDRESS_MEM_MASK;

				अगर (ibmphp_find_resource(bus, start_address, &mem, MEM) < 0) अणु
					err("cannot find corresponding MEM resource to remove\n");
					वापस -EIO;
				पूर्ण
				अगर (mem) अणु
					debug("mem->start = %x\n", mem->start);

					ibmphp_हटाओ_resource(mem);
				पूर्ण
			पूर्ण
			अगर (पंचांगp_address & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
				/* takes up another dword */
				count += 1;
			पूर्ण
		पूर्ण	/* end of mem */
	पूर्ण	/* end of क्रम */

	वापस 0;

report_search_failure:
	err("cannot find corresponding IO resource to remove\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक unconfigure_boot_bridge(u8 busno, u8 device, u8 function)
अणु
	पूर्णांक count;
	पूर्णांक bus_no, pri_no, sub_no, sec_no = 0;
	u32 start_address, पंचांगp_address;
	u8 sec_number, sub_number, pri_number;
	काष्ठा resource_node *io = शून्य;
	काष्ठा resource_node *mem = शून्य;
	काष्ठा resource_node *pfmem = शून्य;
	काष्ठा bus_node *bus;
	u32 address[] = अणु
		PCI_BASE_ADDRESS_0,
		PCI_BASE_ADDRESS_1,
		0
	पूर्ण;
	अचिन्हित पूर्णांक devfn;

	devfn = PCI_DEVFN(device, function);
	ibmphp_pci_bus->number = busno;
	bus_no = (पूर्णांक) busno;
	debug("busno is %x\n", busno);
	pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_PRIMARY_BUS, &pri_number);
	debug("%s - busno = %x, primary_number = %x\n", __func__, busno, pri_number);

	pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, &sec_number);
	debug("sec_number is %x\n", sec_number);
	sec_no = (पूर्णांक) sec_number;
	pri_no = (पूर्णांक) pri_number;
	अगर (pri_no != bus_no) अणु
		err("primary numbers in our structures and pci config space don't match.\n");
		वापस -EINVAL;
	पूर्ण

	pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_SUBORDINATE_BUS, &sub_number);
	sub_no = (पूर्णांक) sub_number;
	debug("sub_no is %d, sec_no is %d\n", sub_no, sec_no);
	अगर (sec_no != sub_number) अणु
		err("there're more buses behind this bridge.  Hot removal is not supported.  Please choose another card\n");
		वापस -ENODEV;
	पूर्ण

	bus = ibmphp_find_res_bus(sec_number);
	अगर (!bus) अणु
		err("cannot find Bus structure for the bridged device\n");
		वापस -EINVAL;
	पूर्ण
	debug("bus->busno is %x\n", bus->busno);
	debug("sec_number is %x\n", sec_number);

	ibmphp_हटाओ_bus(bus, busno);

	क्रम (count = 0; address[count]; count++) अणु
		/* क्रम 2 BARs */
		pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, address[count], &start_address);

		अगर (!start_address) अणु
			/* This BAR is not implemented */
			जारी;
		पूर्ण

		पंचांगp_address = start_address;

		अगर (start_address & PCI_BASE_ADDRESS_SPACE_IO) अणु
			/* This is IO */
			start_address &= PCI_BASE_ADDRESS_IO_MASK;
			अगर (ibmphp_find_resource(bus, start_address, &io, IO) < 0) अणु
				err("cannot find corresponding IO resource to remove\n");
				वापस -EIO;
			पूर्ण
			अगर (io)
				debug("io->start = %x\n", io->start);

			ibmphp_हटाओ_resource(io);

			/* ????????? DO WE NEED TO WRITE ANYTHING INTO THE PCI CONFIG SPACE BACK ?????????? */
		पूर्ण अन्यथा अणु
			/* This is Memory */
			अगर (start_address & PCI_BASE_ADDRESS_MEM_PREFETCH) अणु
				/* pfmem */
				start_address &= PCI_BASE_ADDRESS_MEM_MASK;
				अगर (ibmphp_find_resource(bus, start_address, &pfmem, PFMEM) < 0) अणु
					err("cannot find corresponding PFMEM resource to remove\n");
					वापस -EINVAL;
				पूर्ण
				अगर (pfmem) अणु
					debug("pfmem->start = %x\n", pfmem->start);

					ibmphp_हटाओ_resource(pfmem);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* regular memory */
				start_address &= PCI_BASE_ADDRESS_MEM_MASK;
				अगर (ibmphp_find_resource(bus, start_address, &mem, MEM) < 0) अणु
					err("cannot find corresponding MEM resource to remove\n");
					वापस -EINVAL;
				पूर्ण
				अगर (mem) अणु
					debug("mem->start = %x\n", mem->start);

					ibmphp_हटाओ_resource(mem);
				पूर्ण
			पूर्ण
			अगर (पंचांगp_address & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
				/* takes up another dword */
				count += 1;
			पूर्ण
		पूर्ण	/* end of mem */
	पूर्ण	/* end of क्रम */
	debug("%s - exiting, returning success\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक unconfigure_boot_card(काष्ठा slot *slot_cur)
अणु
	u16 venकरोr_id;
	u32 class;
	u8 hdr_type;
	u8 device;
	u8 busno;
	u8 function;
	पूर्णांक rc;
	अचिन्हित पूर्णांक devfn;
	u8 valid_device = 0x00; /* To see अगर we are ever able to find valid device and पढ़ो it */

	debug("%s - enter\n", __func__);

	device = slot_cur->device;
	busno = slot_cur->bus;

	debug("b4 for loop, device is %x\n", device);
	/* For every function on the card */
	क्रम (function = 0x0; function < 0x08; function++) अणु
		devfn = PCI_DEVFN(device, function);
		ibmphp_pci_bus->number = busno;

		pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_VENDOR_ID, &venकरोr_id);

		अगर (venकरोr_id != PCI_VENDOR_ID_NOTVALID) अणु
			/* found correct device!!! */
			++valid_device;

			debug("%s - found correct device\n", __func__);

			/* header: x x x x x x x x
			 *         | |___________|=> 1=PPB bridge, 0=normal device, 2=CardBus Bridge
			 *         |_=> 0 = single function device, 1 = multi-function device
			 */

			pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_HEADER_TYPE, &hdr_type);
			pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, PCI_CLASS_REVISION, &class);

			debug("hdr_type %x, class %x\n", hdr_type, class);
			class >>= 8;	/* to take revision out, class = class.subclass.prog i/f */
			अगर (class == PCI_CLASS_NOT_DEFINED_VGA) अणु
				err("The device %x function %x is VGA compatible and is not supported for hot removing.  Please choose another device.\n", device, function);
				वापस -ENODEV;
			पूर्ण अन्यथा अगर (class == PCI_CLASS_DISPLAY_VGA) अणु
				err("The device %x function %x is not supported for hot removing.  Please choose another device.\n", device, function);
				वापस -ENODEV;
			पूर्ण

			चयन (hdr_type) अणु
				हाल PCI_HEADER_TYPE_NORMAL:
					rc = unconfigure_boot_device(busno, device, function);
					अगर (rc) अणु
						err("was not able to unconfigure device %x func %x on bus %x. bailing out...\n",
						     device, function, busno);
						वापस rc;
					पूर्ण
					function = 0x8;
					अवरोध;
				हाल PCI_HEADER_TYPE_MULTIDEVICE:
					rc = unconfigure_boot_device(busno, device, function);
					अगर (rc) अणु
						err("was not able to unconfigure device %x func %x on bus %x. bailing out...\n",
						     device, function, busno);
						वापस rc;
					पूर्ण
					अवरोध;
				हाल PCI_HEADER_TYPE_BRIDGE:
					class >>= 8;
					अगर (class != PCI_CLASS_BRIDGE_PCI) अणु
						err("This device %x function %x is not PCI-to-PCI bridge, and is not supported for hot-removing.  Please try another card.\n", device, function);
						वापस -ENODEV;
					पूर्ण
					rc = unconfigure_boot_bridge(busno, device, function);
					अगर (rc != 0) अणु
						err("was not able to hot-remove PPB properly.\n");
						वापस rc;
					पूर्ण

					function = 0x8;
					अवरोध;
				हाल PCI_HEADER_TYPE_MULTIBRIDGE:
					class >>= 8;
					अगर (class != PCI_CLASS_BRIDGE_PCI) अणु
						err("This device %x function %x is not PCI-to-PCI bridge,  and is not supported for hot-removing.  Please try another card.\n", device, function);
						वापस -ENODEV;
					पूर्ण
					rc = unconfigure_boot_bridge(busno, device, function);
					अगर (rc != 0) अणु
						err("was not able to hot-remove PPB properly.\n");
						वापस rc;
					पूर्ण
					अवरोध;
				शेष:
					err("MAJOR PROBLEM!!!! Cannot read device's header\n");
					वापस -1;
			पूर्ण	/* end of चयन */
		पूर्ण	/* end of valid device */
	पूर्ण	/* end of क्रम */

	अगर (!valid_device) अणु
		err("Could not find device to unconfigure.  Or could not read the card.\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * मुक्त the resources of the card (multi, single, or bridged)
 * Parameters: slot, flag to say अगर this is क्रम removing entire module or just
 * unconfiguring the device
 * TO DO:  will probably need to add some code in हाल there was some resource,
 * to हटाओ it... this is from when we have errors in the configure_card...
 *			!!!!!!!!!!!!!!!!!!!!!!!!!FOR BUSES!!!!!!!!!!!!
 * Returns: 0, -1, -ENODEV
 */
पूर्णांक ibmphp_unconfigure_card(काष्ठा slot **slot_cur, पूर्णांक the_end)
अणु
	पूर्णांक i;
	पूर्णांक count;
	पूर्णांक rc;
	काष्ठा slot *sl = *slot_cur;
	काष्ठा pci_func *cur_func = शून्य;
	काष्ठा pci_func *temp_func;

	debug("%s - enter\n", __func__);

	अगर (!the_end) अणु
		/* Need to unconfigure the card */
		rc = unconfigure_boot_card(sl);
		अगर ((rc == -ENODEV) || (rc == -EIO) || (rc == -EINVAL)) अणु
			/* In all other हालs, will still need to get rid of func काष्ठाure अगर it exists */
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (sl->func) अणु
		cur_func = sl->func;
		जबतक (cur_func) अणु
			/* TO DO: WILL MOST LIKELY NEED TO GET RID OF THE BUS STRUCTURE FROM RESOURCES AS WELL */
			अगर (cur_func->bus) अणु
				/* in other words, it's a PPB */
				count = 2;
			पूर्ण अन्यथा अणु
				count = 6;
			पूर्ण

			क्रम (i = 0; i < count; i++) अणु
				अगर (cur_func->io[i]) अणु
					debug("io[%d] exists\n", i);
					अगर (the_end > 0)
						ibmphp_हटाओ_resource(cur_func->io[i]);
					cur_func->io[i] = शून्य;
				पूर्ण
				अगर (cur_func->mem[i]) अणु
					debug("mem[%d] exists\n", i);
					अगर (the_end > 0)
						ibmphp_हटाओ_resource(cur_func->mem[i]);
					cur_func->mem[i] = शून्य;
				पूर्ण
				अगर (cur_func->pfmem[i]) अणु
					debug("pfmem[%d] exists\n", i);
					अगर (the_end > 0)
						ibmphp_हटाओ_resource(cur_func->pfmem[i]);
					cur_func->pfmem[i] = शून्य;
				पूर्ण
			पूर्ण

			temp_func = cur_func->next;
			kमुक्त(cur_func);
			cur_func = temp_func;
		पूर्ण
	पूर्ण

	sl->func = शून्य;
	*slot_cur = sl;
	debug("%s - exit\n", __func__);
	वापस 0;
पूर्ण

/*
 * add a new bus resulting from hot-plugging a PPB bridge with devices
 *
 * Input: bus and the amount of resources needed (we know we can assign those,
 *        since they've been checked alपढ़ोy
 * Output: bus added to the correct spot
 *         0, -1, error
 */
अटल पूर्णांक add_new_bus(काष्ठा bus_node *bus, काष्ठा resource_node *io, काष्ठा resource_node *mem, काष्ठा resource_node *pfmem, u8 parent_busno)
अणु
	काष्ठा range_node *io_range = शून्य;
	काष्ठा range_node *mem_range = शून्य;
	काष्ठा range_node *pfmem_range = शून्य;
	काष्ठा bus_node *cur_bus = शून्य;

	/* Trying to find the parent bus number */
	अगर (parent_busno != 0xFF) अणु
		cur_bus	= ibmphp_find_res_bus(parent_busno);
		अगर (!cur_bus) अणु
			err("strange, cannot find bus which is supposed to be at the system... something is terribly wrong...\n");
			वापस -ENODEV;
		पूर्ण

		list_add(&bus->bus_list, &cur_bus->bus_list);
	पूर्ण
	अगर (io) अणु
		io_range = kzalloc(माप(*io_range), GFP_KERNEL);
		अगर (!io_range)
			वापस -ENOMEM;

		io_range->start = io->start;
		io_range->end = io->end;
		io_range->rangeno = 1;
		bus->noIORanges = 1;
		bus->rangeIO = io_range;
	पूर्ण
	अगर (mem) अणु
		mem_range = kzalloc(माप(*mem_range), GFP_KERNEL);
		अगर (!mem_range)
			वापस -ENOMEM;

		mem_range->start = mem->start;
		mem_range->end = mem->end;
		mem_range->rangeno = 1;
		bus->noMemRanges = 1;
		bus->rangeMem = mem_range;
	पूर्ण
	अगर (pfmem) अणु
		pfmem_range = kzalloc(माप(*pfmem_range), GFP_KERNEL);
		अगर (!pfmem_range)
			वापस -ENOMEM;

		pfmem_range->start = pfmem->start;
		pfmem_range->end = pfmem->end;
		pfmem_range->rangeno = 1;
		bus->noPFMemRanges = 1;
		bus->rangePFMem = pfmem_range;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * find the 1st available bus number क्रम PPB to set as its secondary bus
 * Parameters: bus_number of the primary bus
 * Returns: bus_number of the secondary bus or 0xff in हाल of failure
 */
अटल u8 find_sec_number(u8 primary_busno, u8 slotno)
अणु
	पूर्णांक min, max;
	u8 busno;
	काष्ठा bus_info *bus;
	काष्ठा bus_node *bus_cur;

	bus = ibmphp_find_same_bus_num(primary_busno);
	अगर (!bus) अणु
		err("cannot get slot range of the bus from the BIOS\n");
		वापस 0xff;
	पूर्ण
	max = bus->slot_max;
	min = bus->slot_min;
	अगर ((slotno > max) || (slotno < min)) अणु
		err("got the wrong range\n");
		वापस 0xff;
	पूर्ण
	busno = (u8) (slotno - (u8) min);
	busno += primary_busno + 0x01;
	bus_cur = ibmphp_find_res_bus(busno);
	/* either there is no such bus number, or there are no ranges, which
	 * can only happen अगर we हटाओd the bridged device in previous load
	 * of the driver, and now only have the skeleton bus काष्ठा
	 */
	अगर ((!bus_cur) || (!(bus_cur->rangeIO) && !(bus_cur->rangeMem) && !(bus_cur->rangePFMem)))
		वापस busno;
	वापस 0xff;
पूर्ण
