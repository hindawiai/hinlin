<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IBM Hot Plug Controller Driver
 *
 * Written By: Tong Yu, IBM Corporation
 *
 * Copyright (C) 2001,2003 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001-2003 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <gregkh@us.ibm.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश "ibmphp.h"

/*
 * POST builds data blocks(in this data block definition, a अक्षर-1
 * byte, लघु(or word)-2 byte, दीर्घ(dword)-4 byte) in the Extended
 * BIOS Data Area which describe the configuration of the hot-plug
 * controllers and resources used by the PCI Hot-Plug devices.
 *
 * This file walks EBDA, maps data block from physical addr,
 * reस्थिरruct linked lists about all प्रणाली resource(MEM, PFM, IO)
 * alपढ़ोy asचिन्हित by POST, as well as linked lists about hot plug
 * controllers (ctlr#, slot#, bus&slot features...)
 */

/* Global lists */
LIST_HEAD(ibmphp_ebda_pci_rsrc_head);
LIST_HEAD(ibmphp_slot_head);

/* Local variables */
अटल काष्ठा ebda_hpc_list *hpc_list_ptr;
अटल काष्ठा ebda_rsrc_list *rsrc_list_ptr;
अटल काष्ठा rio_table_hdr *rio_table_ptr = शून्य;
अटल LIST_HEAD(ebda_hpc_head);
अटल LIST_HEAD(bus_info_head);
अटल LIST_HEAD(rio_vg_head);
अटल LIST_HEAD(rio_lo_head);
अटल LIST_HEAD(opt_vg_head);
अटल LIST_HEAD(opt_lo_head);
अटल व्योम __iomem *io_mem;

/* Local functions */
अटल पूर्णांक ebda_rsrc_controller(व्योम);
अटल पूर्णांक ebda_rsrc_rsrc(व्योम);
अटल पूर्णांक ebda_rio_table(व्योम);

अटल काष्ठा ebda_hpc_list * __init alloc_ebda_hpc_list(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा ebda_hpc_list), GFP_KERNEL);
पूर्ण

अटल काष्ठा controller *alloc_ebda_hpc(u32 slot_count, u32 bus_count)
अणु
	काष्ठा controller *controller;
	काष्ठा ebda_hpc_slot *slots;
	काष्ठा ebda_hpc_bus *buses;

	controller = kzalloc(माप(काष्ठा controller), GFP_KERNEL);
	अगर (!controller)
		जाओ error;

	slots = kसुस्मृति(slot_count, माप(काष्ठा ebda_hpc_slot), GFP_KERNEL);
	अगर (!slots)
		जाओ error_contr;
	controller->slots = slots;

	buses = kसुस्मृति(bus_count, माप(काष्ठा ebda_hpc_bus), GFP_KERNEL);
	अगर (!buses)
		जाओ error_slots;
	controller->buses = buses;

	वापस controller;
error_slots:
	kमुक्त(controller->slots);
error_contr:
	kमुक्त(controller);
error:
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_ebda_hpc(काष्ठा controller *controller)
अणु
	kमुक्त(controller->slots);
	kमुक्त(controller->buses);
	kमुक्त(controller);
पूर्ण

अटल काष्ठा ebda_rsrc_list * __init alloc_ebda_rsrc_list(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा ebda_rsrc_list), GFP_KERNEL);
पूर्ण

अटल काष्ठा ebda_pci_rsrc *alloc_ebda_pci_rsrc(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा ebda_pci_rsrc), GFP_KERNEL);
पूर्ण

अटल व्योम __init prपूर्णांक_bus_info(व्योम)
अणु
	काष्ठा bus_info *ptr;

	list_क्रम_each_entry(ptr, &bus_info_head, bus_info_list) अणु
		debug("%s - slot_min = %x\n", __func__, ptr->slot_min);
		debug("%s - slot_max = %x\n", __func__, ptr->slot_max);
		debug("%s - slot_count = %x\n", __func__, ptr->slot_count);
		debug("%s - bus# = %x\n", __func__, ptr->busno);
		debug("%s - current_speed = %x\n", __func__, ptr->current_speed);
		debug("%s - controller_id = %x\n", __func__, ptr->controller_id);

		debug("%s - slots_at_33_conv = %x\n", __func__, ptr->slots_at_33_conv);
		debug("%s - slots_at_66_conv = %x\n", __func__, ptr->slots_at_66_conv);
		debug("%s - slots_at_66_pcix = %x\n", __func__, ptr->slots_at_66_pcix);
		debug("%s - slots_at_100_pcix = %x\n", __func__, ptr->slots_at_100_pcix);
		debug("%s - slots_at_133_pcix = %x\n", __func__, ptr->slots_at_133_pcix);

	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_lo_info(व्योम)
अणु
	काष्ठा rio_detail *ptr;
	debug("print_lo_info ----\n");
	list_क्रम_each_entry(ptr, &rio_lo_head, rio_detail_list) अणु
		debug("%s - rio_node_id = %x\n", __func__, ptr->rio_node_id);
		debug("%s - rio_type = %x\n", __func__, ptr->rio_type);
		debug("%s - owner_id = %x\n", __func__, ptr->owner_id);
		debug("%s - first_slot_num = %x\n", __func__, ptr->first_slot_num);
		debug("%s - wpindex = %x\n", __func__, ptr->wpindex);
		debug("%s - chassis_num = %x\n", __func__, ptr->chassis_num);

	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_vg_info(व्योम)
अणु
	काष्ठा rio_detail *ptr;
	debug("%s ---\n", __func__);
	list_क्रम_each_entry(ptr, &rio_vg_head, rio_detail_list) अणु
		debug("%s - rio_node_id = %x\n", __func__, ptr->rio_node_id);
		debug("%s - rio_type = %x\n", __func__, ptr->rio_type);
		debug("%s - owner_id = %x\n", __func__, ptr->owner_id);
		debug("%s - first_slot_num = %x\n", __func__, ptr->first_slot_num);
		debug("%s - wpindex = %x\n", __func__, ptr->wpindex);
		debug("%s - chassis_num = %x\n", __func__, ptr->chassis_num);

	पूर्ण
पूर्ण

अटल व्योम __init prपूर्णांक_ebda_pci_rsrc(व्योम)
अणु
	काष्ठा ebda_pci_rsrc *ptr;

	list_क्रम_each_entry(ptr, &ibmphp_ebda_pci_rsrc_head, ebda_pci_rsrc_list) अणु
		debug("%s - rsrc type: %x bus#: %x dev_func: %x start addr: %x end addr: %x\n",
			__func__, ptr->rsrc_type, ptr->bus_num, ptr->dev_fun, ptr->start_addr, ptr->end_addr);
	पूर्ण
पूर्ण

अटल व्योम __init prपूर्णांक_ibm_slot(व्योम)
अणु
	काष्ठा slot *ptr;

	list_क्रम_each_entry(ptr, &ibmphp_slot_head, ibm_slot_list) अणु
		debug("%s - slot_number: %x\n", __func__, ptr->number);
	पूर्ण
पूर्ण

अटल व्योम __init prपूर्णांक_opt_vg(व्योम)
अणु
	काष्ठा opt_rio *ptr;
	debug("%s ---\n", __func__);
	list_क्रम_each_entry(ptr, &opt_vg_head, opt_rio_list) अणु
		debug("%s - rio_type %x\n", __func__, ptr->rio_type);
		debug("%s - chassis_num: %x\n", __func__, ptr->chassis_num);
		debug("%s - first_slot_num: %x\n", __func__, ptr->first_slot_num);
		debug("%s - middle_num: %x\n", __func__, ptr->middle_num);
	पूर्ण
पूर्ण

अटल व्योम __init prपूर्णांक_ebda_hpc(व्योम)
अणु
	काष्ठा controller *hpc_ptr;
	u16 index;

	list_क्रम_each_entry(hpc_ptr, &ebda_hpc_head, ebda_hpc_list) अणु
		क्रम (index = 0; index < hpc_ptr->slot_count; index++) अणु
			debug("%s - physical slot#: %x\n", __func__, hpc_ptr->slots[index].slot_num);
			debug("%s - pci bus# of the slot: %x\n", __func__, hpc_ptr->slots[index].slot_bus_num);
			debug("%s - index into ctlr addr: %x\n", __func__, hpc_ptr->slots[index].ctl_index);
			debug("%s - cap of the slot: %x\n", __func__, hpc_ptr->slots[index].slot_cap);
		पूर्ण

		क्रम (index = 0; index < hpc_ptr->bus_count; index++)
			debug("%s - bus# of each bus controlled by this ctlr: %x\n", __func__, hpc_ptr->buses[index].bus_num);

		debug("%s - type of hpc: %x\n", __func__, hpc_ptr->ctlr_type);
		चयन (hpc_ptr->ctlr_type) अणु
		हाल 1:
			debug("%s - bus: %x\n", __func__, hpc_ptr->u.pci_ctlr.bus);
			debug("%s - dev_fun: %x\n", __func__, hpc_ptr->u.pci_ctlr.dev_fun);
			debug("%s - irq: %x\n", __func__, hpc_ptr->irq);
			अवरोध;

		हाल 0:
			debug("%s - io_start: %x\n", __func__, hpc_ptr->u.isa_ctlr.io_start);
			debug("%s - io_end: %x\n", __func__, hpc_ptr->u.isa_ctlr.io_end);
			debug("%s - irq: %x\n", __func__, hpc_ptr->irq);
			अवरोध;

		हाल 2:
		हाल 4:
			debug("%s - wpegbbar: %lx\n", __func__, hpc_ptr->u.wpeg_ctlr.wpegbbar);
			debug("%s - i2c_addr: %x\n", __func__, hpc_ptr->u.wpeg_ctlr.i2c_addr);
			debug("%s - irq: %x\n", __func__, hpc_ptr->irq);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __init ibmphp_access_ebda(व्योम)
अणु
	u8 क्रमmat, num_ctlrs, rio_complete, hs_complete, ebda_sz;
	u16 ebda_seg, num_entries, next_offset, offset, blk_id, sub_addr, re, rc_id, re_id, base;
	पूर्णांक rc = 0;


	rio_complete = 0;
	hs_complete = 0;

	io_mem = ioremap((0x40 << 4) + 0x0e, 2);
	अगर (!io_mem)
		वापस -ENOMEM;
	ebda_seg = पढ़ोw(io_mem);
	iounmap(io_mem);
	debug("returned ebda segment: %x\n", ebda_seg);

	io_mem = ioremap(ebda_seg<<4, 1);
	अगर (!io_mem)
		वापस -ENOMEM;
	ebda_sz = पढ़ोb(io_mem);
	iounmap(io_mem);
	debug("ebda size: %d(KiB)\n", ebda_sz);
	अगर (ebda_sz == 0)
		वापस -ENOMEM;

	io_mem = ioremap(ebda_seg<<4, (ebda_sz * 1024));
	अगर (!io_mem)
		वापस -ENOMEM;
	next_offset = 0x180;

	क्रम (;;) अणु
		offset = next_offset;

		/* Make sure what we पढ़ो is still in the mapped section */
		अगर (WARN(offset > (ebda_sz * 1024 - 4),
			 "ibmphp_ebda: next read is beyond ebda_sz\n"))
			अवरोध;

		next_offset = पढ़ोw(io_mem + offset);	/* offset of next blk */

		offset += 2;
		अगर (next_offset == 0)	/* 0 indicate it's last blk */
			अवरोध;
		blk_id = पढ़ोw(io_mem + offset);	/* this blk id */

		offset += 2;
		/* check अगर it is hot swap block or rio block */
		अगर (blk_id != 0x4853 && blk_id != 0x4752)
			जारी;
		/* found hs table */
		अगर (blk_id == 0x4853) अणु
			debug("now enter hot swap block---\n");
			debug("hot blk id: %x\n", blk_id);
			क्रमmat = पढ़ोb(io_mem + offset);

			offset += 1;
			अगर (क्रमmat != 4)
				जाओ error_nodev;
			debug("hot blk format: %x\n", क्रमmat);
			/* hot swap sub blk */
			base = offset;

			sub_addr = base;
			re = पढ़ोw(io_mem + sub_addr);	/* next sub blk */

			sub_addr += 2;
			rc_id = पढ़ोw(io_mem + sub_addr);	/* sub blk id */

			sub_addr += 2;
			अगर (rc_id != 0x5243)
				जाओ error_nodev;
			/* rc sub blk signature  */
			num_ctlrs = पढ़ोb(io_mem + sub_addr);

			sub_addr += 1;
			hpc_list_ptr = alloc_ebda_hpc_list();
			अगर (!hpc_list_ptr) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			hpc_list_ptr->क्रमmat = क्रमmat;
			hpc_list_ptr->num_ctlrs = num_ctlrs;
			hpc_list_ptr->phys_addr = sub_addr;	/*  offset of RSRC_CONTROLLER blk */
			debug("info about hpc descriptor---\n");
			debug("hot blk format: %x\n", क्रमmat);
			debug("num of controller: %x\n", num_ctlrs);
			debug("offset of hpc data structure entries: %x\n ", sub_addr);

			sub_addr = base + re;	/* re sub blk */
			/* FIXME: rc is never used/checked */
			rc = पढ़ोw(io_mem + sub_addr);	/* next sub blk */

			sub_addr += 2;
			re_id = पढ़ोw(io_mem + sub_addr);	/* sub blk id */

			sub_addr += 2;
			अगर (re_id != 0x5245)
				जाओ error_nodev;

			/* signature of re */
			num_entries = पढ़ोw(io_mem + sub_addr);

			sub_addr += 2;	/* offset of RSRC_ENTRIES blk */
			rsrc_list_ptr = alloc_ebda_rsrc_list();
			अगर (!rsrc_list_ptr) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			rsrc_list_ptr->क्रमmat = क्रमmat;
			rsrc_list_ptr->num_entries = num_entries;
			rsrc_list_ptr->phys_addr = sub_addr;

			debug("info about rsrc descriptor---\n");
			debug("format: %x\n", क्रमmat);
			debug("num of rsrc: %x\n", num_entries);
			debug("offset of rsrc data structure entries: %x\n ", sub_addr);

			hs_complete = 1;
		पूर्ण अन्यथा अणु
		/* found rio table, blk_id == 0x4752 */
			debug("now enter io table ---\n");
			debug("rio blk id: %x\n", blk_id);

			rio_table_ptr = kzalloc(माप(काष्ठा rio_table_hdr), GFP_KERNEL);
			अगर (!rio_table_ptr) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			rio_table_ptr->ver_num = पढ़ोb(io_mem + offset);
			rio_table_ptr->scal_count = पढ़ोb(io_mem + offset + 1);
			rio_table_ptr->riodev_count = पढ़ोb(io_mem + offset + 2);
			rio_table_ptr->offset = offset + 3 ;

			debug("info about rio table hdr ---\n");
			debug("ver_num: %x\nscal_count: %x\nriodev_count: %x\noffset of rio table: %x\n ",
				rio_table_ptr->ver_num, rio_table_ptr->scal_count,
				rio_table_ptr->riodev_count, rio_table_ptr->offset);

			rio_complete = 1;
		पूर्ण
	पूर्ण

	अगर (!hs_complete && !rio_complete)
		जाओ error_nodev;

	अगर (rio_table_ptr) अणु
		अगर (rio_complete && rio_table_ptr->ver_num == 3) अणु
			rc = ebda_rio_table();
			अगर (rc)
				जाओ out;
		पूर्ण
	पूर्ण
	rc = ebda_rsrc_controller();
	अगर (rc)
		जाओ out;

	rc = ebda_rsrc_rsrc();
	जाओ out;
error_nodev:
	rc = -ENODEV;
out:
	iounmap(io_mem);
	वापस rc;
पूर्ण

/*
 * map info of scalability details and rio details from physical address
 */
अटल पूर्णांक __init ebda_rio_table(व्योम)
अणु
	u16 offset;
	u8 i;
	काष्ठा rio_detail *rio_detail_ptr;

	offset = rio_table_ptr->offset;
	offset += 12 * rio_table_ptr->scal_count;

	// we करो concern about rio details
	क्रम (i = 0; i < rio_table_ptr->riodev_count; i++) अणु
		rio_detail_ptr = kzalloc(माप(काष्ठा rio_detail), GFP_KERNEL);
		अगर (!rio_detail_ptr)
			वापस -ENOMEM;
		rio_detail_ptr->rio_node_id = पढ़ोb(io_mem + offset);
		rio_detail_ptr->bbar = पढ़ोl(io_mem + offset + 1);
		rio_detail_ptr->rio_type = पढ़ोb(io_mem + offset + 5);
		rio_detail_ptr->owner_id = पढ़ोb(io_mem + offset + 6);
		rio_detail_ptr->port0_node_connect = पढ़ोb(io_mem + offset + 7);
		rio_detail_ptr->port0_port_connect = पढ़ोb(io_mem + offset + 8);
		rio_detail_ptr->port1_node_connect = पढ़ोb(io_mem + offset + 9);
		rio_detail_ptr->port1_port_connect = पढ़ोb(io_mem + offset + 10);
		rio_detail_ptr->first_slot_num = पढ़ोb(io_mem + offset + 11);
		rio_detail_ptr->status = पढ़ोb(io_mem + offset + 12);
		rio_detail_ptr->wpindex = पढ़ोb(io_mem + offset + 13);
		rio_detail_ptr->chassis_num = पढ़ोb(io_mem + offset + 14);
//		debug("rio_node_id: %x\nbbar: %x\nrio_type: %x\nowner_id: %x\nport0_node: %x\nport0_port: %x\nport1_node: %x\nport1_port: %x\nfirst_slot_num: %x\nstatus: %x\n", rio_detail_ptr->rio_node_id, rio_detail_ptr->bbar, rio_detail_ptr->rio_type, rio_detail_ptr->owner_id, rio_detail_ptr->port0_node_connect, rio_detail_ptr->port0_port_connect, rio_detail_ptr->port1_node_connect, rio_detail_ptr->port1_port_connect, rio_detail_ptr->first_slot_num, rio_detail_ptr->status);
		//create linked list of chassis
		अगर (rio_detail_ptr->rio_type == 4 || rio_detail_ptr->rio_type == 5)
			list_add(&rio_detail_ptr->rio_detail_list, &rio_vg_head);
		//create linked list of expansion box
		अन्यथा अगर (rio_detail_ptr->rio_type == 6 || rio_detail_ptr->rio_type == 7)
			list_add(&rio_detail_ptr->rio_detail_list, &rio_lo_head);
		अन्यथा
			// not in my concern
			kमुक्त(rio_detail_ptr);
		offset += 15;
	पूर्ण
	prपूर्णांक_lo_info();
	prपूर्णांक_vg_info();
	वापस 0;
पूर्ण

/*
 * reorganizing linked list of chassis
 */
अटल काष्ठा opt_rio *search_opt_vg(u8 chassis_num)
अणु
	काष्ठा opt_rio *ptr;
	list_क्रम_each_entry(ptr, &opt_vg_head, opt_rio_list) अणु
		अगर (ptr->chassis_num == chassis_num)
			वापस ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init combine_wpg_क्रम_chassis(व्योम)
अणु
	काष्ठा opt_rio *opt_rio_ptr = शून्य;
	काष्ठा rio_detail *rio_detail_ptr = शून्य;

	list_क्रम_each_entry(rio_detail_ptr, &rio_vg_head, rio_detail_list) अणु
		opt_rio_ptr = search_opt_vg(rio_detail_ptr->chassis_num);
		अगर (!opt_rio_ptr) अणु
			opt_rio_ptr = kzalloc(माप(काष्ठा opt_rio), GFP_KERNEL);
			अगर (!opt_rio_ptr)
				वापस -ENOMEM;
			opt_rio_ptr->rio_type = rio_detail_ptr->rio_type;
			opt_rio_ptr->chassis_num = rio_detail_ptr->chassis_num;
			opt_rio_ptr->first_slot_num = rio_detail_ptr->first_slot_num;
			opt_rio_ptr->middle_num = rio_detail_ptr->first_slot_num;
			list_add(&opt_rio_ptr->opt_rio_list, &opt_vg_head);
		पूर्ण अन्यथा अणु
			opt_rio_ptr->first_slot_num = min(opt_rio_ptr->first_slot_num, rio_detail_ptr->first_slot_num);
			opt_rio_ptr->middle_num = max(opt_rio_ptr->middle_num, rio_detail_ptr->first_slot_num);
		पूर्ण
	पूर्ण
	prपूर्णांक_opt_vg();
	वापस 0;
पूर्ण

/*
 * reorganizing linked list of expansion box
 */
अटल काष्ठा opt_rio_lo *search_opt_lo(u8 chassis_num)
अणु
	काष्ठा opt_rio_lo *ptr;
	list_क्रम_each_entry(ptr, &opt_lo_head, opt_rio_lo_list) अणु
		अगर (ptr->chassis_num == chassis_num)
			वापस ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक combine_wpg_क्रम_expansion(व्योम)
अणु
	काष्ठा opt_rio_lo *opt_rio_lo_ptr = शून्य;
	काष्ठा rio_detail *rio_detail_ptr = शून्य;

	list_क्रम_each_entry(rio_detail_ptr, &rio_lo_head, rio_detail_list) अणु
		opt_rio_lo_ptr = search_opt_lo(rio_detail_ptr->chassis_num);
		अगर (!opt_rio_lo_ptr) अणु
			opt_rio_lo_ptr = kzalloc(माप(काष्ठा opt_rio_lo), GFP_KERNEL);
			अगर (!opt_rio_lo_ptr)
				वापस -ENOMEM;
			opt_rio_lo_ptr->rio_type = rio_detail_ptr->rio_type;
			opt_rio_lo_ptr->chassis_num = rio_detail_ptr->chassis_num;
			opt_rio_lo_ptr->first_slot_num = rio_detail_ptr->first_slot_num;
			opt_rio_lo_ptr->middle_num = rio_detail_ptr->first_slot_num;
			opt_rio_lo_ptr->pack_count = 1;

			list_add(&opt_rio_lo_ptr->opt_rio_lo_list, &opt_lo_head);
		पूर्ण अन्यथा अणु
			opt_rio_lo_ptr->first_slot_num = min(opt_rio_lo_ptr->first_slot_num, rio_detail_ptr->first_slot_num);
			opt_rio_lo_ptr->middle_num = max(opt_rio_lo_ptr->middle_num, rio_detail_ptr->first_slot_num);
			opt_rio_lo_ptr->pack_count = 2;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/* Since we करोn't know the max slot number per each chassis, hence go
 * through the list of all chassis to find out the range
 * Arguments: slot_num, 1st slot number of the chassis we think we are on,
 * var (0 = chassis, 1 = expansion box)
 */
अटल पूर्णांक first_slot_num(u8 slot_num, u8 first_slot, u8 var)
अणु
	काष्ठा opt_rio *opt_vg_ptr = शून्य;
	काष्ठा opt_rio_lo *opt_lo_ptr = शून्य;
	पूर्णांक rc = 0;

	अगर (!var) अणु
		list_क्रम_each_entry(opt_vg_ptr, &opt_vg_head, opt_rio_list) अणु
			अगर ((first_slot < opt_vg_ptr->first_slot_num) && (slot_num >= opt_vg_ptr->first_slot_num)) अणु
				rc = -ENODEV;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(opt_lo_ptr, &opt_lo_head, opt_rio_lo_list) अणु
			अगर ((first_slot < opt_lo_ptr->first_slot_num) && (slot_num >= opt_lo_ptr->first_slot_num)) अणु
				rc = -ENODEV;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा opt_rio_lo *find_rxe_num(u8 slot_num)
अणु
	काष्ठा opt_rio_lo *opt_lo_ptr;

	list_क्रम_each_entry(opt_lo_ptr, &opt_lo_head, opt_rio_lo_list) अणु
		//check to see अगर this slot_num beदीर्घs to expansion box
		अगर ((slot_num >= opt_lo_ptr->first_slot_num) && (!first_slot_num(slot_num, opt_lo_ptr->first_slot_num, 1)))
			वापस opt_lo_ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा opt_rio *find_chassis_num(u8 slot_num)
अणु
	काष्ठा opt_rio *opt_vg_ptr;

	list_क्रम_each_entry(opt_vg_ptr, &opt_vg_head, opt_rio_list) अणु
		//check to see अगर this slot_num beदीर्घs to chassis
		अगर ((slot_num >= opt_vg_ptr->first_slot_num) && (!first_slot_num(slot_num, opt_vg_ptr->first_slot_num, 0)))
			वापस opt_vg_ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

/* This routine will find out how many slots are in the chassis, so that
 * the slot numbers क्रम rxe100 would start from 1, and not from 7, or 6 etc
 */
अटल u8 calculate_first_slot(u8 slot_num)
अणु
	u8 first_slot = 1;
	काष्ठा slot *slot_cur;

	list_क्रम_each_entry(slot_cur, &ibmphp_slot_head, ibm_slot_list) अणु
		अगर (slot_cur->ctrl) अणु
			अगर ((slot_cur->ctrl->ctlr_type != 4) && (slot_cur->ctrl->ending_slot_num > first_slot) && (slot_num > slot_cur->ctrl->ending_slot_num))
				first_slot = slot_cur->ctrl->ending_slot_num;
		पूर्ण
	पूर्ण
	वापस first_slot + 1;

पूर्ण

#घोषणा SLOT_NAME_SIZE 30

अटल अक्षर *create_file_name(काष्ठा slot *slot_cur)
अणु
	काष्ठा opt_rio *opt_vg_ptr = शून्य;
	काष्ठा opt_rio_lo *opt_lo_ptr = शून्य;
	अटल अक्षर str[SLOT_NAME_SIZE];
	पूर्णांक which = 0; /* rxe = 1, chassis = 0 */
	u8 number = 1; /* either chassis or rxe # */
	u8 first_slot = 1;
	u8 slot_num;
	u8 flag = 0;

	अगर (!slot_cur) अणु
		err("Structure passed is empty\n");
		वापस शून्य;
	पूर्ण

	slot_num = slot_cur->number;

	स_रखो(str, 0, माप(str));

	अगर (rio_table_ptr) अणु
		अगर (rio_table_ptr->ver_num == 3) अणु
			opt_vg_ptr = find_chassis_num(slot_num);
			opt_lo_ptr = find_rxe_num(slot_num);
		पूर्ण
	पूर्ण
	अगर (opt_vg_ptr) अणु
		अगर (opt_lo_ptr) अणु
			अगर ((slot_num - opt_vg_ptr->first_slot_num) > (slot_num - opt_lo_ptr->first_slot_num)) अणु
				number = opt_lo_ptr->chassis_num;
				first_slot = opt_lo_ptr->first_slot_num;
				which = 1; /* it is RXE */
			पूर्ण अन्यथा अणु
				first_slot = opt_vg_ptr->first_slot_num;
				number = opt_vg_ptr->chassis_num;
				which = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			first_slot = opt_vg_ptr->first_slot_num;
			number = opt_vg_ptr->chassis_num;
			which = 0;
		पूर्ण
		++flag;
	पूर्ण अन्यथा अगर (opt_lo_ptr) अणु
		number = opt_lo_ptr->chassis_num;
		first_slot = opt_lo_ptr->first_slot_num;
		which = 1;
		++flag;
	पूर्ण अन्यथा अगर (rio_table_ptr) अणु
		अगर (rio_table_ptr->ver_num == 3) अणु
			/* अगर both शून्य and we DO have correct RIO table in BIOS */
			वापस शून्य;
		पूर्ण
	पूर्ण
	अगर (!flag) अणु
		अगर (slot_cur->ctrl->ctlr_type == 4) अणु
			first_slot = calculate_first_slot(slot_num);
			which = 1;
		पूर्ण अन्यथा अणु
			which = 0;
		पूर्ण
	पूर्ण

	प्र_लिखो(str, "%s%dslot%d",
		which == 0 ? "chassis" : "rxe",
		number, slot_num - first_slot + 1);
	वापस str;
पूर्ण

अटल पूर्णांक fillslotinfo(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot;
	पूर्णांक rc = 0;

	slot = to_slot(hotplug_slot);
	rc = ibmphp_hpc_पढ़ोslot(slot, READ_ALLSTAT, शून्य);
	वापस rc;
पूर्ण

अटल काष्ठा pci_driver ibmphp_driver;

/*
 * map info (ctlr-id, slot count, slot#.. bus count, bus#, ctlr type...) of
 * each hpc from physical address to a list of hot plug controllers based on
 * hpc descriptors.
 */
अटल पूर्णांक __init ebda_rsrc_controller(व्योम)
अणु
	u16 addr, addr_slot, addr_bus;
	u8 ctlr_id, temp, bus_index;
	u16 ctlr, slot, bus;
	u16 slot_num, bus_num, index;
	काष्ठा controller *hpc_ptr;
	काष्ठा ebda_hpc_bus *bus_ptr;
	काष्ठा ebda_hpc_slot *slot_ptr;
	काष्ठा bus_info *bus_info_ptr1, *bus_info_ptr2;
	पूर्णांक rc;
	काष्ठा slot *पंचांगp_slot;
	अक्षर name[SLOT_NAME_SIZE];

	addr = hpc_list_ptr->phys_addr;
	क्रम (ctlr = 0; ctlr < hpc_list_ptr->num_ctlrs; ctlr++) अणु
		bus_index = 1;
		ctlr_id = पढ़ोb(io_mem + addr);
		addr += 1;
		slot_num = पढ़ोb(io_mem + addr);

		addr += 1;
		addr_slot = addr;	/* offset of slot काष्ठाure */
		addr += (slot_num * 4);

		bus_num = पढ़ोb(io_mem + addr);

		addr += 1;
		addr_bus = addr;	/* offset of bus */
		addr += (bus_num * 9);	/* offset of ctlr_type */
		temp = पढ़ोb(io_mem + addr);

		addr += 1;
		/* init hpc काष्ठाure */
		hpc_ptr = alloc_ebda_hpc(slot_num, bus_num);
		अगर (!hpc_ptr) अणु
			rc = -ENOMEM;
			जाओ error_no_hpc;
		पूर्ण
		hpc_ptr->ctlr_id = ctlr_id;
		hpc_ptr->ctlr_relative_id = ctlr;
		hpc_ptr->slot_count = slot_num;
		hpc_ptr->bus_count = bus_num;
		debug("now enter ctlr data structure ---\n");
		debug("ctlr id: %x\n", ctlr_id);
		debug("ctlr_relative_id: %x\n", hpc_ptr->ctlr_relative_id);
		debug("count of slots controlled by this ctlr: %x\n", slot_num);
		debug("count of buses controlled by this ctlr: %x\n", bus_num);

		/* init slot काष्ठाure, fetch slot, bus, cap... */
		slot_ptr = hpc_ptr->slots;
		क्रम (slot = 0; slot < slot_num; slot++) अणु
			slot_ptr->slot_num = पढ़ोb(io_mem + addr_slot);
			slot_ptr->slot_bus_num = पढ़ोb(io_mem + addr_slot + slot_num);
			slot_ptr->ctl_index = पढ़ोb(io_mem + addr_slot + 2*slot_num);
			slot_ptr->slot_cap = पढ़ोb(io_mem + addr_slot + 3*slot_num);

			// create bus_info lined list --- अगर only one slot per bus: slot_min = slot_max

			bus_info_ptr2 = ibmphp_find_same_bus_num(slot_ptr->slot_bus_num);
			अगर (!bus_info_ptr2) अणु
				bus_info_ptr1 = kzalloc(माप(काष्ठा bus_info), GFP_KERNEL);
				अगर (!bus_info_ptr1) अणु
					rc = -ENOMEM;
					जाओ error_no_slot;
				पूर्ण
				bus_info_ptr1->slot_min = slot_ptr->slot_num;
				bus_info_ptr1->slot_max = slot_ptr->slot_num;
				bus_info_ptr1->slot_count += 1;
				bus_info_ptr1->busno = slot_ptr->slot_bus_num;
				bus_info_ptr1->index = bus_index++;
				bus_info_ptr1->current_speed = 0xff;
				bus_info_ptr1->current_bus_mode = 0xff;

				bus_info_ptr1->controller_id = hpc_ptr->ctlr_id;

				list_add_tail(&bus_info_ptr1->bus_info_list, &bus_info_head);

			पूर्ण अन्यथा अणु
				bus_info_ptr2->slot_min = min(bus_info_ptr2->slot_min, slot_ptr->slot_num);
				bus_info_ptr2->slot_max = max(bus_info_ptr2->slot_max, slot_ptr->slot_num);
				bus_info_ptr2->slot_count += 1;

			पूर्ण

			// end of creating the bus_info linked list

			slot_ptr++;
			addr_slot += 1;
		पूर्ण

		/* init bus काष्ठाure */
		bus_ptr = hpc_ptr->buses;
		क्रम (bus = 0; bus < bus_num; bus++) अणु
			bus_ptr->bus_num = पढ़ोb(io_mem + addr_bus + bus);
			bus_ptr->slots_at_33_conv = पढ़ोb(io_mem + addr_bus + bus_num + 8 * bus);
			bus_ptr->slots_at_66_conv = पढ़ोb(io_mem + addr_bus + bus_num + 8 * bus + 1);

			bus_ptr->slots_at_66_pcix = पढ़ोb(io_mem + addr_bus + bus_num + 8 * bus + 2);

			bus_ptr->slots_at_100_pcix = पढ़ोb(io_mem + addr_bus + bus_num + 8 * bus + 3);

			bus_ptr->slots_at_133_pcix = पढ़ोb(io_mem + addr_bus + bus_num + 8 * bus + 4);

			bus_info_ptr2 = ibmphp_find_same_bus_num(bus_ptr->bus_num);
			अगर (bus_info_ptr2) अणु
				bus_info_ptr2->slots_at_33_conv = bus_ptr->slots_at_33_conv;
				bus_info_ptr2->slots_at_66_conv = bus_ptr->slots_at_66_conv;
				bus_info_ptr2->slots_at_66_pcix = bus_ptr->slots_at_66_pcix;
				bus_info_ptr2->slots_at_100_pcix = bus_ptr->slots_at_100_pcix;
				bus_info_ptr2->slots_at_133_pcix = bus_ptr->slots_at_133_pcix;
			पूर्ण
			bus_ptr++;
		पूर्ण

		hpc_ptr->ctlr_type = temp;

		चयन (hpc_ptr->ctlr_type) अणु
			हाल 1:
				hpc_ptr->u.pci_ctlr.bus = पढ़ोb(io_mem + addr);
				hpc_ptr->u.pci_ctlr.dev_fun = पढ़ोb(io_mem + addr + 1);
				hpc_ptr->irq = पढ़ोb(io_mem + addr + 2);
				addr += 3;
				debug("ctrl bus = %x, ctlr devfun = %x, irq = %x\n",
					hpc_ptr->u.pci_ctlr.bus,
					hpc_ptr->u.pci_ctlr.dev_fun, hpc_ptr->irq);
				अवरोध;

			हाल 0:
				hpc_ptr->u.isa_ctlr.io_start = पढ़ोw(io_mem + addr);
				hpc_ptr->u.isa_ctlr.io_end = पढ़ोw(io_mem + addr + 2);
				अगर (!request_region(hpc_ptr->u.isa_ctlr.io_start,
						     (hpc_ptr->u.isa_ctlr.io_end - hpc_ptr->u.isa_ctlr.io_start + 1),
						     "ibmphp")) अणु
					rc = -ENODEV;
					जाओ error_no_slot;
				पूर्ण
				hpc_ptr->irq = पढ़ोb(io_mem + addr + 4);
				addr += 5;
				अवरोध;

			हाल 2:
			हाल 4:
				hpc_ptr->u.wpeg_ctlr.wpegbbar = पढ़ोl(io_mem + addr);
				hpc_ptr->u.wpeg_ctlr.i2c_addr = पढ़ोb(io_mem + addr + 4);
				hpc_ptr->irq = पढ़ोb(io_mem + addr + 5);
				addr += 6;
				अवरोध;
			शेष:
				rc = -ENODEV;
				जाओ error_no_slot;
		पूर्ण

		//reorganize chassis' linked list
		combine_wpg_क्रम_chassis();
		combine_wpg_क्रम_expansion();
		hpc_ptr->revision = 0xff;
		hpc_ptr->options = 0xff;
		hpc_ptr->starting_slot_num = hpc_ptr->slots[0].slot_num;
		hpc_ptr->ending_slot_num = hpc_ptr->slots[slot_num-1].slot_num;

		// रेजिस्टर slots with hpc core as well as create linked list of ibm slot
		क्रम (index = 0; index < hpc_ptr->slot_count; index++) अणु
			पंचांगp_slot = kzalloc(माप(*पंचांगp_slot), GFP_KERNEL);
			अगर (!पंचांगp_slot) अणु
				rc = -ENOMEM;
				जाओ error_no_slot;
			पूर्ण

			पंचांगp_slot->flag = 1;

			पंचांगp_slot->capabilities = hpc_ptr->slots[index].slot_cap;
			अगर ((hpc_ptr->slots[index].slot_cap & EBDA_SLOT_133_MAX) == EBDA_SLOT_133_MAX)
				पंचांगp_slot->supported_speed =  3;
			अन्यथा अगर ((hpc_ptr->slots[index].slot_cap & EBDA_SLOT_100_MAX) == EBDA_SLOT_100_MAX)
				पंचांगp_slot->supported_speed =  2;
			अन्यथा अगर ((hpc_ptr->slots[index].slot_cap & EBDA_SLOT_66_MAX) == EBDA_SLOT_66_MAX)
				पंचांगp_slot->supported_speed =  1;

			अगर ((hpc_ptr->slots[index].slot_cap & EBDA_SLOT_PCIX_CAP) == EBDA_SLOT_PCIX_CAP)
				पंचांगp_slot->supported_bus_mode = 1;
			अन्यथा
				पंचांगp_slot->supported_bus_mode = 0;


			पंचांगp_slot->bus = hpc_ptr->slots[index].slot_bus_num;

			bus_info_ptr1 = ibmphp_find_same_bus_num(hpc_ptr->slots[index].slot_bus_num);
			अगर (!bus_info_ptr1) अणु
				rc = -ENODEV;
				जाओ error;
			पूर्ण
			पंचांगp_slot->bus_on = bus_info_ptr1;
			bus_info_ptr1 = शून्य;
			पंचांगp_slot->ctrl = hpc_ptr;

			पंचांगp_slot->ctlr_index = hpc_ptr->slots[index].ctl_index;
			पंचांगp_slot->number = hpc_ptr->slots[index].slot_num;

			rc = fillslotinfo(&पंचांगp_slot->hotplug_slot);
			अगर (rc)
				जाओ error;

			rc = ibmphp_init_devno(&पंचांगp_slot);
			अगर (rc)
				जाओ error;
			पंचांगp_slot->hotplug_slot.ops = &ibmphp_hotplug_slot_ops;

			// end of रेजिस्टरing ibm slot with hotplug core

			list_add(&पंचांगp_slot->ibm_slot_list, &ibmphp_slot_head);
		पूर्ण

		prपूर्णांक_bus_info();
		list_add(&hpc_ptr->ebda_hpc_list, &ebda_hpc_head);

	पूर्ण			/* each hpc  */

	list_क्रम_each_entry(पंचांगp_slot, &ibmphp_slot_head, ibm_slot_list) अणु
		snम_लिखो(name, SLOT_NAME_SIZE, "%s", create_file_name(पंचांगp_slot));
		pci_hp_रेजिस्टर(&पंचांगp_slot->hotplug_slot,
			pci_find_bus(0, पंचांगp_slot->bus), पंचांगp_slot->device, name);
	पूर्ण

	prपूर्णांक_ebda_hpc();
	prपूर्णांक_ibm_slot();
	वापस 0;

error:
	kमुक्त(पंचांगp_slot);
error_no_slot:
	मुक्त_ebda_hpc(hpc_ptr);
error_no_hpc:
	iounmap(io_mem);
	वापस rc;
पूर्ण

/*
 * map info (bus, devfun, start addr, end addr..) of i/o, memory,
 * pfm from the physical addr to a list of resource.
 */
अटल पूर्णांक __init ebda_rsrc_rsrc(व्योम)
अणु
	u16 addr;
	लघु rsrc;
	u8 type, rsrc_type;
	काष्ठा ebda_pci_rsrc *rsrc_ptr;

	addr = rsrc_list_ptr->phys_addr;
	debug("now entering rsrc land\n");
	debug("offset of rsrc: %x\n", rsrc_list_ptr->phys_addr);

	क्रम (rsrc = 0; rsrc < rsrc_list_ptr->num_entries; rsrc++) अणु
		type = पढ़ोb(io_mem + addr);

		addr += 1;
		rsrc_type = type & EBDA_RSRC_TYPE_MASK;

		अगर (rsrc_type == EBDA_IO_RSRC_TYPE) अणु
			rsrc_ptr = alloc_ebda_pci_rsrc();
			अगर (!rsrc_ptr) अणु
				iounmap(io_mem);
				वापस -ENOMEM;
			पूर्ण
			rsrc_ptr->rsrc_type = type;

			rsrc_ptr->bus_num = पढ़ोb(io_mem + addr);
			rsrc_ptr->dev_fun = पढ़ोb(io_mem + addr + 1);
			rsrc_ptr->start_addr = पढ़ोw(io_mem + addr + 2);
			rsrc_ptr->end_addr = पढ़ोw(io_mem + addr + 4);
			addr += 6;

			debug("rsrc from io type ----\n");
			debug("rsrc type: %x bus#: %x dev_func: %x start addr: %x end addr: %x\n",
				rsrc_ptr->rsrc_type, rsrc_ptr->bus_num, rsrc_ptr->dev_fun, rsrc_ptr->start_addr, rsrc_ptr->end_addr);

			list_add(&rsrc_ptr->ebda_pci_rsrc_list, &ibmphp_ebda_pci_rsrc_head);
		पूर्ण

		अगर (rsrc_type == EBDA_MEM_RSRC_TYPE || rsrc_type == EBDA_PFM_RSRC_TYPE) अणु
			rsrc_ptr = alloc_ebda_pci_rsrc();
			अगर (!rsrc_ptr) अणु
				iounmap(io_mem);
				वापस -ENOMEM;
			पूर्ण
			rsrc_ptr->rsrc_type = type;

			rsrc_ptr->bus_num = पढ़ोb(io_mem + addr);
			rsrc_ptr->dev_fun = पढ़ोb(io_mem + addr + 1);
			rsrc_ptr->start_addr = पढ़ोl(io_mem + addr + 2);
			rsrc_ptr->end_addr = पढ़ोl(io_mem + addr + 6);
			addr += 10;

			debug("rsrc from mem or pfm ---\n");
			debug("rsrc type: %x bus#: %x dev_func: %x start addr: %x end addr: %x\n",
				rsrc_ptr->rsrc_type, rsrc_ptr->bus_num, rsrc_ptr->dev_fun, rsrc_ptr->start_addr, rsrc_ptr->end_addr);

			list_add(&rsrc_ptr->ebda_pci_rsrc_list, &ibmphp_ebda_pci_rsrc_head);
		पूर्ण
	पूर्ण
	kमुक्त(rsrc_list_ptr);
	rsrc_list_ptr = शून्य;
	prपूर्णांक_ebda_pci_rsrc();
	वापस 0;
पूर्ण

u16 ibmphp_get_total_controllers(व्योम)
अणु
	वापस hpc_list_ptr->num_ctlrs;
पूर्ण

काष्ठा slot *ibmphp_get_slot_from_physical_num(u8 physical_num)
अणु
	काष्ठा slot *slot;

	list_क्रम_each_entry(slot, &ibmphp_slot_head, ibm_slot_list) अणु
		अगर (slot->number == physical_num)
			वापस slot;
	पूर्ण
	वापस शून्य;
पूर्ण

/* To find:
 *	- the smallest slot number
 *	- the largest slot number
 *	- the total number of the slots based on each bus
 *	  (अगर only one slot per bus slot_min = slot_max )
 */
काष्ठा bus_info *ibmphp_find_same_bus_num(u32 num)
अणु
	काष्ठा bus_info *ptr;

	list_क्रम_each_entry(ptr, &bus_info_head, bus_info_list) अणु
		अगर (ptr->busno == num)
			 वापस ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

/*  Finding relative bus number, in order to map corresponding
 *  bus रेजिस्टर
 */
पूर्णांक ibmphp_get_bus_index(u8 num)
अणु
	काष्ठा bus_info *ptr;

	list_क्रम_each_entry(ptr, &bus_info_head, bus_info_list) अणु
		अगर (ptr->busno == num)
			वापस ptr->index;
	पूर्ण
	वापस -ENODEV;
पूर्ण

व्योम ibmphp_मुक्त_bus_info_queue(व्योम)
अणु
	काष्ठा bus_info *bus_info, *next;

	list_क्रम_each_entry_safe(bus_info, next, &bus_info_head,
				 bus_info_list) अणु
		kमुक्त (bus_info);
	पूर्ण
पूर्ण

व्योम ibmphp_मुक्त_ebda_hpc_queue(व्योम)
अणु
	काष्ठा controller *controller = शून्य, *next;
	पूर्णांक pci_flag = 0;

	list_क्रम_each_entry_safe(controller, next, &ebda_hpc_head,
				 ebda_hpc_list) अणु
		अगर (controller->ctlr_type == 0)
			release_region(controller->u.isa_ctlr.io_start, (controller->u.isa_ctlr.io_end - controller->u.isa_ctlr.io_start + 1));
		अन्यथा अगर ((controller->ctlr_type == 1) && (!pci_flag)) अणु
			++pci_flag;
			pci_unरेजिस्टर_driver(&ibmphp_driver);
		पूर्ण
		मुक्त_ebda_hpc(controller);
	पूर्ण
पूर्ण

व्योम ibmphp_मुक्त_ebda_pci_rsrc_queue(व्योम)
अणु
	काष्ठा ebda_pci_rsrc *resource, *next;

	list_क्रम_each_entry_safe(resource, next, &ibmphp_ebda_pci_rsrc_head,
				 ebda_pci_rsrc_list) अणु
		kमुक्त (resource);
		resource = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id id_table[] = अणु
	अणु
		.venकरोr		= PCI_VENDOR_ID_IBM,
		.device		= HPC_DEVICE_ID,
		.subvenकरोr	= PCI_VENDOR_ID_IBM,
		.subdevice	= HPC_SUBSYSTEM_ID,
		.class		= ((PCI_CLASS_SYSTEM_PCI_HOTPLUG << 8) | 0x00),
	पूर्ण, अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, id_table);

अटल पूर्णांक ibmphp_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल काष्ठा pci_driver ibmphp_driver = अणु
	.name		= "ibmphp",
	.id_table	= id_table,
	.probe		= ibmphp_probe,
पूर्ण;

पूर्णांक ibmphp_रेजिस्टर_pci(व्योम)
अणु
	काष्ठा controller *ctrl;
	पूर्णांक rc = 0;

	list_क्रम_each_entry(ctrl, &ebda_hpc_head, ebda_hpc_list) अणु
		अगर (ctrl->ctlr_type == 1) अणु
			rc = pci_रेजिस्टर_driver(&ibmphp_driver);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण
अटल पूर्णांक ibmphp_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ids)
अणु
	काष्ठा controller *ctrl;

	debug("inside ibmphp_probe\n");

	list_क्रम_each_entry(ctrl, &ebda_hpc_head, ebda_hpc_list) अणु
		अगर (ctrl->ctlr_type == 1) अणु
			अगर ((dev->devfn == ctrl->u.pci_ctlr.dev_fun) && (dev->bus->number == ctrl->u.pci_ctlr.bus)) अणु
				ctrl->ctrl_dev = dev;
				debug("found device!!!\n");
				debug("dev->device = %x, dev->subsystem_device = %x\n", dev->device, dev->subप्रणाली_device);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण
