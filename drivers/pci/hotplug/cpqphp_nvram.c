<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Compaq Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/uaccess.h>
#समावेश "cpqphp.h"
#समावेश "cpqphp_nvram.h"


#घोषणा ROM_INT15_PHY_ADDR		0x0FF859
#घोषणा READ_EV				0xD8A4
#घोषणा WRITE_EV			0xD8A5

काष्ठा रेजिस्टर_foo अणु
	जोड़ अणु
		अचिन्हित दीर्घ lword;		/* eax */
		अचिन्हित लघु word;		/* ax */

		काष्ठा अणु
			अचिन्हित अक्षर low;	/* al */
			अचिन्हित अक्षर high;	/* ah */
		पूर्ण byte;
	पूर्ण data;

	अचिन्हित अक्षर opcode;	/* see below */
	अचिन्हित दीर्घ length;	/* अगर the reg. is a poपूर्णांकer, how much data */
पूर्ण __attribute__ ((packed));

काष्ठा all_reg अणु
	काष्ठा रेजिस्टर_foo eax_reg;
	काष्ठा रेजिस्टर_foo ebx_reg;
	काष्ठा रेजिस्टर_foo ecx_reg;
	काष्ठा रेजिस्टर_foo edx_reg;
	काष्ठा रेजिस्टर_foo edi_reg;
	काष्ठा रेजिस्टर_foo esi_reg;
	काष्ठा रेजिस्टर_foo eflags_reg;
पूर्ण __attribute__ ((packed));


काष्ठा ev_hrt_header अणु
	u8 Version;
	u8 num_of_ctrl;
	u8 next;
पूर्ण;

काष्ठा ev_hrt_ctrl अणु
	u8 bus;
	u8 device;
	u8 function;
	u8 mem_avail;
	u8 p_mem_avail;
	u8 io_avail;
	u8 bus_avail;
	u8 next;
पूर्ण;


अटल u8 evbuffer_init;
अटल u8 evbuffer_length;
अटल u8 evbuffer[1024];

अटल व्योम __iomem *compaq_पूर्णांक15_entry_poपूर्णांक;

/* lock क्रम ordering पूर्णांक15_bios_call() */
अटल DEFINE_SPINLOCK(पूर्णांक15_lock);


/* This is a series of function that deals with
 * setting & getting the hotplug resource table in some environment variable.
 */

/*
 * We really shouldn't be करोing this unless there is a _very_ good reason to!!!
 * greg k-h
 */


अटल u32 add_byte(u32 **p_buffer, u8 value, u32 *used, u32 *avail)
अणु
	u8 **tByte;

	अगर ((*used + 1) > *avail)
		वापस(1);

	*((u8 *)*p_buffer) = value;
	tByte = (u8 **)p_buffer;
	(*tByte)++;
	*used += 1;
	वापस(0);
पूर्ण


अटल u32 add_dword(u32 **p_buffer, u32 value, u32 *used, u32 *avail)
अणु
	अगर ((*used + 4) > *avail)
		वापस(1);

	**p_buffer = value;
	(*p_buffer)++;
	*used += 4;
	वापस(0);
पूर्ण


/*
 * check_क्रम_compaq_ROM
 *
 * this routine verअगरies that the ROM OEM string is 'COMPAQ'
 *
 * वापसs 0 क्रम non-Compaq ROM, 1 क्रम Compaq ROM
 */
अटल पूर्णांक check_क्रम_compaq_ROM(व्योम __iomem *rom_start)
अणु
	u8 temp1, temp2, temp3, temp4, temp5, temp6;
	पूर्णांक result = 0;

	temp1 = पढ़ोb(rom_start + 0xffea + 0);
	temp2 = पढ़ोb(rom_start + 0xffea + 1);
	temp3 = पढ़ोb(rom_start + 0xffea + 2);
	temp4 = पढ़ोb(rom_start + 0xffea + 3);
	temp5 = पढ़ोb(rom_start + 0xffea + 4);
	temp6 = पढ़ोb(rom_start + 0xffea + 5);
	अगर ((temp1 == 'C') &&
	    (temp2 == 'O') &&
	    (temp3 == 'M') &&
	    (temp4 == 'P') &&
	    (temp5 == 'A') &&
	    (temp6 == 'Q')) अणु
		result = 1;
	पूर्ण
	dbg("%s - returned %d\n", __func__, result);
	वापस result;
पूर्ण


अटल u32 access_EV(u16 operation, u8 *ev_name, u8 *buffer, u32 *buf_size)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक op = operation;
	पूर्णांक ret_val;

	अगर (!compaq_पूर्णांक15_entry_poपूर्णांक)
		वापस -ENODEV;

	spin_lock_irqsave(&पूर्णांक15_lock, flags);
	__यंत्र__ (
		"xorl   %%ebx,%%ebx\n" \
		"xorl    %%edx,%%edx\n" \
		"pushf\n" \
		"push %%cs\n" \
		"cli\n" \
		"call *%6\n"
		: "=c" (*buf_size), "=a" (ret_val)
		: "a" (op), "c" (*buf_size), "S" (ev_name),
		"D" (buffer), "m" (compaq_पूर्णांक15_entry_poपूर्णांक)
		: "%ebx", "%edx");
	spin_unlock_irqrestore(&पूर्णांक15_lock, flags);

	वापस((ret_val & 0xFF00) >> 8);
पूर्ण


/*
 * load_HRT
 *
 * Read the hot plug Resource Table from NVRAM
 */
अटल पूर्णांक load_HRT(व्योम __iomem *rom_start)
अणु
	u32 available;
	u32 temp_dword;
	u8 temp_byte = 0xFF;
	u32 rc;

	अगर (!check_क्रम_compaq_ROM(rom_start))
		वापस -ENODEV;

	available = 1024;

	/* Now load the EV */
	temp_dword = available;

	rc = access_EV(READ_EV, "CQTHPS", evbuffer, &temp_dword);

	evbuffer_length = temp_dword;

	/* We're मुख्यtaining the resource lists so ग_लिखो FF to invalidate old
	 * info
	 */
	temp_dword = 1;

	rc = access_EV(WRITE_EV, "CQTHPS", &temp_byte, &temp_dword);

	वापस rc;
पूर्ण


/*
 * store_HRT
 *
 * Save the hot plug Resource Table in NVRAM
 */
अटल u32 store_HRT(व्योम __iomem *rom_start)
अणु
	u32 *buffer;
	u32 *pFill;
	u32 usedbytes;
	u32 available;
	u32 temp_dword;
	u32 rc;
	u8 loop;
	u8 numCtrl = 0;
	काष्ठा controller *ctrl;
	काष्ठा pci_resource *resNode;
	काष्ठा ev_hrt_header *p_EV_header;
	काष्ठा ev_hrt_ctrl *p_ev_ctrl;

	available = 1024;

	अगर (!check_क्रम_compaq_ROM(rom_start))
		वापस(1);

	buffer = (u32 *) evbuffer;

	अगर (!buffer)
		वापस(1);

	pFill = buffer;
	usedbytes = 0;

	p_EV_header = (काष्ठा ev_hrt_header *) pFill;

	ctrl = cpqhp_ctrl_list;

	/* The revision of this काष्ठाure */
	rc = add_byte(&pFill, 1 + ctrl->push_flag, &usedbytes, &available);
	अगर (rc)
		वापस(rc);

	/* The number of controllers */
	rc = add_byte(&pFill, 1, &usedbytes, &available);
	अगर (rc)
		वापस(rc);

	जबतक (ctrl) अणु
		p_ev_ctrl = (काष्ठा ev_hrt_ctrl *) pFill;

		numCtrl++;

		/* The bus number */
		rc = add_byte(&pFill, ctrl->bus, &usedbytes, &available);
		अगर (rc)
			वापस(rc);

		/* The device Number */
		rc = add_byte(&pFill, PCI_SLOT(ctrl->pci_dev->devfn), &usedbytes, &available);
		अगर (rc)
			वापस(rc);

		/* The function Number */
		rc = add_byte(&pFill, PCI_FUNC(ctrl->pci_dev->devfn), &usedbytes, &available);
		अगर (rc)
			वापस(rc);

		/* Skip the number of available entries */
		rc = add_dword(&pFill, 0, &usedbytes, &available);
		अगर (rc)
			वापस(rc);

		/* Figure out memory Available */

		resNode = ctrl->mem_head;

		loop = 0;

		जबतक (resNode) अणु
			loop++;

			/* base */
			rc = add_dword(&pFill, resNode->base, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			/* length */
			rc = add_dword(&pFill, resNode->length, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			resNode = resNode->next;
		पूर्ण

		/* Fill in the number of entries */
		p_ev_ctrl->mem_avail = loop;

		/* Figure out prefetchable memory Available */

		resNode = ctrl->p_mem_head;

		loop = 0;

		जबतक (resNode) अणु
			loop++;

			/* base */
			rc = add_dword(&pFill, resNode->base, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			/* length */
			rc = add_dword(&pFill, resNode->length, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			resNode = resNode->next;
		पूर्ण

		/* Fill in the number of entries */
		p_ev_ctrl->p_mem_avail = loop;

		/* Figure out IO Available */

		resNode = ctrl->io_head;

		loop = 0;

		जबतक (resNode) अणु
			loop++;

			/* base */
			rc = add_dword(&pFill, resNode->base, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			/* length */
			rc = add_dword(&pFill, resNode->length, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			resNode = resNode->next;
		पूर्ण

		/* Fill in the number of entries */
		p_ev_ctrl->io_avail = loop;

		/* Figure out bus Available */

		resNode = ctrl->bus_head;

		loop = 0;

		जबतक (resNode) अणु
			loop++;

			/* base */
			rc = add_dword(&pFill, resNode->base, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			/* length */
			rc = add_dword(&pFill, resNode->length, &usedbytes, &available);
			अगर (rc)
				वापस(rc);

			resNode = resNode->next;
		पूर्ण

		/* Fill in the number of entries */
		p_ev_ctrl->bus_avail = loop;

		ctrl = ctrl->next;
	पूर्ण

	p_EV_header->num_of_ctrl = numCtrl;

	/* Now store the EV */

	temp_dword = usedbytes;

	rc = access_EV(WRITE_EV, "CQTHPS", (u8 *) buffer, &temp_dword);

	dbg("usedbytes = 0x%x, length = 0x%x\n", usedbytes, temp_dword);

	evbuffer_length = temp_dword;

	अगर (rc) अणु
		err(msg_unable_to_save);
		वापस(1);
	पूर्ण

	वापस(0);
पूर्ण


व्योम compaq_nvram_init(व्योम __iomem *rom_start)
अणु
	अगर (rom_start)
		compaq_पूर्णांक15_entry_poपूर्णांक = (rom_start + ROM_INT15_PHY_ADDR - ROM_PHY_ADDR);

	dbg("int15 entry  = %p\n", compaq_पूर्णांक15_entry_poपूर्णांक);
पूर्ण


पूर्णांक compaq_nvram_load(व्योम __iomem *rom_start, काष्ठा controller *ctrl)
अणु
	u8 bus, device, function;
	u8 nummem, numpmem, numio, numbus;
	u32 rc;
	u8 *p_byte;
	काष्ठा pci_resource *mem_node;
	काष्ठा pci_resource *p_mem_node;
	काष्ठा pci_resource *io_node;
	काष्ठा pci_resource *bus_node;
	काष्ठा ev_hrt_ctrl *p_ev_ctrl;
	काष्ठा ev_hrt_header *p_EV_header;

	अगर (!evbuffer_init) अणु
		/* Read the resource list inक्रमmation in from NVRAM */
		अगर (load_HRT(rom_start))
			स_रखो(evbuffer, 0, 1024);

		evbuffer_init = 1;
	पूर्ण

	/* If we saved inक्रमmation in NVRAM, use it now */
	p_EV_header = (काष्ठा ev_hrt_header *) evbuffer;

	/* The following code is क्रम प्रणालीs where version 1.0 of this
	 * driver has been loaded, but करोesn't support the hardware.
	 * In that हाल, the driver would incorrectly store something
	 * in NVRAM.
	 */
	अगर ((p_EV_header->Version == 2) ||
	    ((p_EV_header->Version == 1) && !ctrl->push_flag)) अणु
		p_byte = &(p_EV_header->next);

		p_ev_ctrl = (काष्ठा ev_hrt_ctrl *) &(p_EV_header->next);

		p_byte += 3;

		अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length))
			वापस 2;

		bus = p_ev_ctrl->bus;
		device = p_ev_ctrl->device;
		function = p_ev_ctrl->function;

		जबतक ((bus != ctrl->bus) ||
		       (device != PCI_SLOT(ctrl->pci_dev->devfn)) ||
		       (function != PCI_FUNC(ctrl->pci_dev->devfn))) अणु
			nummem = p_ev_ctrl->mem_avail;
			numpmem = p_ev_ctrl->p_mem_avail;
			numio = p_ev_ctrl->io_avail;
			numbus = p_ev_ctrl->bus_avail;

			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length))
				वापस 2;

			/* Skip क्रमward to the next entry */
			p_byte += (nummem + numpmem + numio + numbus) * 8;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length))
				वापस 2;

			p_ev_ctrl = (काष्ठा ev_hrt_ctrl *) p_byte;

			p_byte += 3;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length))
				वापस 2;

			bus = p_ev_ctrl->bus;
			device = p_ev_ctrl->device;
			function = p_ev_ctrl->function;
		पूर्ण

		nummem = p_ev_ctrl->mem_avail;
		numpmem = p_ev_ctrl->p_mem_avail;
		numio = p_ev_ctrl->io_avail;
		numbus = p_ev_ctrl->bus_avail;

		p_byte += 4;

		अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length))
			वापस 2;

		जबतक (nummem--) अणु
			mem_node = kदो_स्मृति(माप(काष्ठा pci_resource), GFP_KERNEL);

			अगर (!mem_node)
				अवरोध;

			mem_node->base = *(u32 *)p_byte;
			dbg("mem base = %8.8x\n", mem_node->base);
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(mem_node);
				वापस 2;
			पूर्ण

			mem_node->length = *(u32 *)p_byte;
			dbg("mem length = %8.8x\n", mem_node->length);
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(mem_node);
				वापस 2;
			पूर्ण

			mem_node->next = ctrl->mem_head;
			ctrl->mem_head = mem_node;
		पूर्ण

		जबतक (numpmem--) अणु
			p_mem_node = kदो_स्मृति(माप(काष्ठा pci_resource), GFP_KERNEL);

			अगर (!p_mem_node)
				अवरोध;

			p_mem_node->base = *(u32 *)p_byte;
			dbg("pre-mem base = %8.8x\n", p_mem_node->base);
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(p_mem_node);
				वापस 2;
			पूर्ण

			p_mem_node->length = *(u32 *)p_byte;
			dbg("pre-mem length = %8.8x\n", p_mem_node->length);
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(p_mem_node);
				वापस 2;
			पूर्ण

			p_mem_node->next = ctrl->p_mem_head;
			ctrl->p_mem_head = p_mem_node;
		पूर्ण

		जबतक (numio--) अणु
			io_node = kदो_स्मृति(माप(काष्ठा pci_resource), GFP_KERNEL);

			अगर (!io_node)
				अवरोध;

			io_node->base = *(u32 *)p_byte;
			dbg("io base = %8.8x\n", io_node->base);
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(io_node);
				वापस 2;
			पूर्ण

			io_node->length = *(u32 *)p_byte;
			dbg("io length = %8.8x\n", io_node->length);
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(io_node);
				वापस 2;
			पूर्ण

			io_node->next = ctrl->io_head;
			ctrl->io_head = io_node;
		पूर्ण

		जबतक (numbus--) अणु
			bus_node = kदो_स्मृति(माप(काष्ठा pci_resource), GFP_KERNEL);

			अगर (!bus_node)
				अवरोध;

			bus_node->base = *(u32 *)p_byte;
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(bus_node);
				वापस 2;
			पूर्ण

			bus_node->length = *(u32 *)p_byte;
			p_byte += 4;

			अगर (p_byte > ((u8 *)p_EV_header + evbuffer_length)) अणु
				kमुक्त(bus_node);
				वापस 2;
			पूर्ण

			bus_node->next = ctrl->bus_head;
			ctrl->bus_head = bus_node;
		पूर्ण

		/* If all of the following fail, we करोn't have any resources क्रम
		 * hot plug add
		 */
		rc = 1;
		rc &= cpqhp_resource_sort_and_combine(&(ctrl->mem_head));
		rc &= cpqhp_resource_sort_and_combine(&(ctrl->p_mem_head));
		rc &= cpqhp_resource_sort_and_combine(&(ctrl->io_head));
		rc &= cpqhp_resource_sort_and_combine(&(ctrl->bus_head));

		अगर (rc)
			वापस(rc);
	पूर्ण अन्यथा अणु
		अगर ((evbuffer[0] != 0) && (!ctrl->push_flag))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक compaq_nvram_store(व्योम __iomem *rom_start)
अणु
	पूर्णांक rc = 1;

	अगर (rom_start == शून्य)
		वापस -ENODEV;

	अगर (evbuffer_init) अणु
		rc = store_HRT(rom_start);
		अगर (rc)
			err(msg_unable_to_save);
	पूर्ण
	वापस rc;
पूर्ण

