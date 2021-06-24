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
#समावेश <linux/init.h>
#समावेश "ibmphp.h"

अटल पूर्णांक flags = 0;		/* क्रम testing */

अटल व्योम update_resources(काष्ठा bus_node *bus_cur, पूर्णांक type, पूर्णांक rangeno);
अटल पूर्णांक once_over(व्योम);
अटल पूर्णांक हटाओ_ranges(काष्ठा bus_node *, काष्ठा bus_node *);
अटल पूर्णांक update_bridge_ranges(काष्ठा bus_node **);
अटल पूर्णांक add_bus_range(पूर्णांक type, काष्ठा range_node *, काष्ठा bus_node *);
अटल व्योम fix_resources(काष्ठा bus_node *);
अटल काष्ठा bus_node *find_bus_wprev(u8, काष्ठा bus_node **, u8);

अटल LIST_HEAD(gbuses);

अटल काष्ठा bus_node * __init alloc_error_bus(काष्ठा ebda_pci_rsrc *curr, u8 busno, पूर्णांक flag)
अणु
	काष्ठा bus_node *newbus;

	अगर (!(curr) && !(flag)) अणु
		err("NULL pointer passed\n");
		वापस शून्य;
	पूर्ण

	newbus = kzalloc(माप(काष्ठा bus_node), GFP_KERNEL);
	अगर (!newbus)
		वापस शून्य;

	अगर (flag)
		newbus->busno = busno;
	अन्यथा
		newbus->busno = curr->bus_num;
	list_add_tail(&newbus->bus_list, &gbuses);
	वापस newbus;
पूर्ण

अटल काष्ठा resource_node * __init alloc_resources(काष्ठा ebda_pci_rsrc *curr)
अणु
	काष्ठा resource_node *rs;

	अगर (!curr) अणु
		err("NULL passed to allocate\n");
		वापस शून्य;
	पूर्ण

	rs = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
	अगर (!rs)
		वापस शून्य;

	rs->busno = curr->bus_num;
	rs->devfunc = curr->dev_fun;
	rs->start = curr->start_addr;
	rs->end = curr->end_addr;
	rs->len = curr->end_addr - curr->start_addr + 1;
	वापस rs;
पूर्ण

अटल पूर्णांक __init alloc_bus_range(काष्ठा bus_node **new_bus, काष्ठा range_node **new_range, काष्ठा ebda_pci_rsrc *curr, पूर्णांक flag, u8 first_bus)
अणु
	काष्ठा bus_node *newbus;
	काष्ठा range_node *newrange;
	u8 num_ranges = 0;

	अगर (first_bus) अणु
		newbus = kzalloc(माप(काष्ठा bus_node), GFP_KERNEL);
		अगर (!newbus)
			वापस -ENOMEM;

		newbus->busno = curr->bus_num;
	पूर्ण अन्यथा अणु
		newbus = *new_bus;
		चयन (flag) अणु
			हाल MEM:
				num_ranges = newbus->noMemRanges;
				अवरोध;
			हाल PFMEM:
				num_ranges = newbus->noPFMemRanges;
				अवरोध;
			हाल IO:
				num_ranges = newbus->noIORanges;
				अवरोध;
		पूर्ण
	पूर्ण

	newrange = kzalloc(माप(काष्ठा range_node), GFP_KERNEL);
	अगर (!newrange) अणु
		अगर (first_bus)
			kमुक्त(newbus);
		वापस -ENOMEM;
	पूर्ण
	newrange->start = curr->start_addr;
	newrange->end = curr->end_addr;

	अगर (first_bus || (!num_ranges))
		newrange->rangeno = 1;
	अन्यथा अणु
		/* need to insert our range */
		add_bus_range(flag, newrange, newbus);
		debug("%d resource Primary Bus inserted on bus %x [%x - %x]\n", flag, newbus->busno, newrange->start, newrange->end);
	पूर्ण

	चयन (flag) अणु
		हाल MEM:
			newbus->rangeMem = newrange;
			अगर (first_bus)
				newbus->noMemRanges = 1;
			अन्यथा अणु
				debug("First Memory Primary on bus %x, [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
				++newbus->noMemRanges;
				fix_resources(newbus);
			पूर्ण
			अवरोध;
		हाल IO:
			newbus->rangeIO = newrange;
			अगर (first_bus)
				newbus->noIORanges = 1;
			अन्यथा अणु
				debug("First IO Primary on bus %x, [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
				++newbus->noIORanges;
				fix_resources(newbus);
			पूर्ण
			अवरोध;
		हाल PFMEM:
			newbus->rangePFMem = newrange;
			अगर (first_bus)
				newbus->noPFMemRanges = 1;
			अन्यथा अणु
				debug("1st PFMemory Primary on Bus %x [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
				++newbus->noPFMemRanges;
				fix_resources(newbus);
			पूर्ण

			अवरोध;
	पूर्ण

	*new_bus = newbus;
	*new_range = newrange;
	वापस 0;
पूर्ण


/* Notes:
 * 1. The ranges are ordered.  The buses are not ordered.  (First come)
 *
 * 2. If cannot allocate out of PFMem range, allocate from Mem ranges.  PFmemFromMem
 * are not sorted. (no need since use mem node). To not change the entire code, we
 * also add mem node whenever this हाल happens so as not to change
 * ibmphp_check_mem_resource etc(and since it really is taking Mem resource)
 */

/*****************************************************************************
 * This is the Resource Management initialization function.  It will go through
 * the Resource list taken from EBDA and fill in this module's data काष्ठाures
 *
 * THIS IS NOT TAKING INTO CONSIDERATION IO RESTRICTIONS OF PRIMARY BUSES,
 * SINCE WE'RE GOING TO ASSUME FOR NOW WE DON'T HAVE THOSE ON OUR BUSES FOR NOW
 *
 * Input: ptr to the head of the resource list from EBDA
 * Output: 0, -1 or error codes
 ***************************************************************************/
पूर्णांक __init ibmphp_rsrc_init(व्योम)
अणु
	काष्ठा ebda_pci_rsrc *curr;
	काष्ठा range_node *newrange = शून्य;
	काष्ठा bus_node *newbus = शून्य;
	काष्ठा bus_node *bus_cur;
	काष्ठा bus_node *bus_prev;
	काष्ठा resource_node *new_io = शून्य;
	काष्ठा resource_node *new_mem = शून्य;
	काष्ठा resource_node *new_pfmem = शून्य;
	पूर्णांक rc;

	list_क्रम_each_entry(curr, &ibmphp_ebda_pci_rsrc_head,
			    ebda_pci_rsrc_list) अणु
		अगर (!(curr->rsrc_type & PCIDEVMASK)) अणु
			/* EBDA still lists non PCI devices, so ignore... */
			debug("this is not a PCI DEVICE in rsrc_init, please take care\n");
			// जारी;
		पूर्ण

		/* this is a primary bus resource */
		अगर (curr->rsrc_type & PRIMARYBUSMASK) अणु
			/* memory */
			अगर ((curr->rsrc_type & RESTYPE) == MMASK) अणु
				/* no bus काष्ठाure exists in place yet */
				अगर (list_empty(&gbuses)) अणु
					rc = alloc_bus_range(&newbus, &newrange, curr, MEM, 1);
					अगर (rc)
						वापस rc;
					list_add_tail(&newbus->bus_list, &gbuses);
					debug("gbuses = NULL, Memory Primary Bus %x [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
				पूर्ण अन्यथा अणु
					bus_cur = find_bus_wprev(curr->bus_num, &bus_prev, 1);
					/* found our bus */
					अगर (bus_cur) अणु
						rc = alloc_bus_range(&bus_cur, &newrange, curr, MEM, 0);
						अगर (rc)
							वापस rc;
					पूर्ण अन्यथा अणु
						/* went through all the buses and didn't find ours, need to create a new bus node */
						rc = alloc_bus_range(&newbus, &newrange, curr, MEM, 1);
						अगर (rc)
							वापस rc;

						list_add_tail(&newbus->bus_list, &gbuses);
						debug("New Bus, Memory Primary Bus %x [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर ((curr->rsrc_type & RESTYPE) == PFMASK) अणु
				/* prefetchable memory */
				अगर (list_empty(&gbuses)) अणु
					/* no bus काष्ठाure exists in place yet */
					rc = alloc_bus_range(&newbus, &newrange, curr, PFMEM, 1);
					अगर (rc)
						वापस rc;
					list_add_tail(&newbus->bus_list, &gbuses);
					debug("gbuses = NULL, PFMemory Primary Bus %x [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
				पूर्ण अन्यथा अणु
					bus_cur = find_bus_wprev(curr->bus_num, &bus_prev, 1);
					अगर (bus_cur) अणु
						/* found our bus */
						rc = alloc_bus_range(&bus_cur, &newrange, curr, PFMEM, 0);
						अगर (rc)
							वापस rc;
					पूर्ण अन्यथा अणु
						/* went through all the buses and didn't find ours, need to create a new bus node */
						rc = alloc_bus_range(&newbus, &newrange, curr, PFMEM, 1);
						अगर (rc)
							वापस rc;
						list_add_tail(&newbus->bus_list, &gbuses);
						debug("1st Bus, PFMemory Primary Bus %x [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर ((curr->rsrc_type & RESTYPE) == IOMASK) अणु
				/* IO */
				अगर (list_empty(&gbuses)) अणु
					/* no bus काष्ठाure exists in place yet */
					rc = alloc_bus_range(&newbus, &newrange, curr, IO, 1);
					अगर (rc)
						वापस rc;
					list_add_tail(&newbus->bus_list, &gbuses);
					debug("gbuses = NULL, IO Primary Bus %x [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
				पूर्ण अन्यथा अणु
					bus_cur = find_bus_wprev(curr->bus_num, &bus_prev, 1);
					अगर (bus_cur) अणु
						rc = alloc_bus_range(&bus_cur, &newrange, curr, IO, 0);
						अगर (rc)
							वापस rc;
					पूर्ण अन्यथा अणु
						/* went through all the buses and didn't find ours, need to create a new bus node */
						rc = alloc_bus_range(&newbus, &newrange, curr, IO, 1);
						अगर (rc)
							वापस rc;
						list_add_tail(&newbus->bus_list, &gbuses);
						debug("1st Bus, IO Primary Bus %x [%x - %x]\n", newbus->busno, newrange->start, newrange->end);
					पूर्ण
				पूर्ण

			पूर्ण अन्यथा अणु
				;	/* type is reserved  WHAT TO DO IN THIS CASE???
					   NOTHING TO DO??? */
			पूर्ण
		पूर्ण अन्यथा अणु
			/* regular pci device resource */
			अगर ((curr->rsrc_type & RESTYPE) == MMASK) अणु
				/* Memory resource */
				new_mem = alloc_resources(curr);
				अगर (!new_mem)
					वापस -ENOMEM;
				new_mem->type = MEM;
				/*
				 * अगर it didn't find the bus, means PCI dev
				 * came b4 the Primary Bus info, so need to
				 * create a bus rangeno becomes a problem...
				 * assign a -1 and then update once the range
				 * actually appears...
				 */
				अगर (ibmphp_add_resource(new_mem) < 0) अणु
					newbus = alloc_error_bus(curr, 0, 0);
					अगर (!newbus)
						वापस -ENOMEM;
					newbus->firstMem = new_mem;
					++newbus->needMemUpdate;
					new_mem->rangeno = -1;
				पूर्ण
				debug("Memory resource for device %x, bus %x, [%x - %x]\n", new_mem->devfunc, new_mem->busno, new_mem->start, new_mem->end);

			पूर्ण अन्यथा अगर ((curr->rsrc_type & RESTYPE) == PFMASK) अणु
				/* PFMemory resource */
				new_pfmem = alloc_resources(curr);
				अगर (!new_pfmem)
					वापस -ENOMEM;
				new_pfmem->type = PFMEM;
				new_pfmem->fromMem = 0;
				अगर (ibmphp_add_resource(new_pfmem) < 0) अणु
					newbus = alloc_error_bus(curr, 0, 0);
					अगर (!newbus)
						वापस -ENOMEM;
					newbus->firstPFMem = new_pfmem;
					++newbus->needPFMemUpdate;
					new_pfmem->rangeno = -1;
				पूर्ण

				debug("PFMemory resource for device %x, bus %x, [%x - %x]\n", new_pfmem->devfunc, new_pfmem->busno, new_pfmem->start, new_pfmem->end);
			पूर्ण अन्यथा अगर ((curr->rsrc_type & RESTYPE) == IOMASK) अणु
				/* IO resource */
				new_io = alloc_resources(curr);
				अगर (!new_io)
					वापस -ENOMEM;
				new_io->type = IO;

				/*
				 * अगर it didn't find the bus, means PCI dev
				 * came b4 the Primary Bus info, so need to
				 * create a bus rangeno becomes a problem...
				 * Can assign a -1 and then update once the
				 * range actually appears...
				 */
				अगर (ibmphp_add_resource(new_io) < 0) अणु
					newbus = alloc_error_bus(curr, 0, 0);
					अगर (!newbus)
						वापस -ENOMEM;
					newbus->firstIO = new_io;
					++newbus->needIOUpdate;
					new_io->rangeno = -1;
				पूर्ण
				debug("IO resource for device %x, bus %x, [%x - %x]\n", new_io->devfunc, new_io->busno, new_io->start, new_io->end);
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(bus_cur, &gbuses, bus_list) अणु
		/* This is to get info about PPB resources, since EBDA करोesn't put this info पूर्णांकo the primary bus info */
		rc = update_bridge_ranges(&bus_cur);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस once_over();	/* This is to align ranges (so no -1) */
पूर्ण

/********************************************************************************
 * This function adds a range पूर्णांकo a sorted list of ranges per bus क्रम a particular
 * range type, it then calls another routine to update the range numbers on the
 * pci devices' resources क्रम the appropriate resource
 *
 * Input: type of the resource, range to add, current bus
 * Output: 0 or -1, bus and range ptrs
 ********************************************************************************/
अटल पूर्णांक add_bus_range(पूर्णांक type, काष्ठा range_node *range, काष्ठा bus_node *bus_cur)
अणु
	काष्ठा range_node *range_cur = शून्य;
	काष्ठा range_node *range_prev;
	पूर्णांक count = 0, i_init;
	पूर्णांक noRanges = 0;

	चयन (type) अणु
		हाल MEM:
			range_cur = bus_cur->rangeMem;
			noRanges = bus_cur->noMemRanges;
			अवरोध;
		हाल PFMEM:
			range_cur = bus_cur->rangePFMem;
			noRanges = bus_cur->noPFMemRanges;
			अवरोध;
		हाल IO:
			range_cur = bus_cur->rangeIO;
			noRanges = bus_cur->noIORanges;
			अवरोध;
	पूर्ण

	range_prev = शून्य;
	जबतक (range_cur) अणु
		अगर (range->start < range_cur->start)
			अवरोध;
		range_prev = range_cur;
		range_cur = range_cur->next;
		count = count + 1;
	पूर्ण
	अगर (!count) अणु
		/* our range will go at the beginning of the list */
		चयन (type) अणु
			हाल MEM:
				bus_cur->rangeMem = range;
				अवरोध;
			हाल PFMEM:
				bus_cur->rangePFMem = range;
				अवरोध;
			हाल IO:
				bus_cur->rangeIO = range;
				अवरोध;
		पूर्ण
		range->next = range_cur;
		range->rangeno = 1;
		i_init = 0;
	पूर्ण अन्यथा अगर (!range_cur) अणु
		/* our range will go at the end of the list */
		range->next = शून्य;
		range_prev->next = range;
		range->rangeno = range_prev->rangeno + 1;
		वापस 0;
	पूर्ण अन्यथा अणु
		/* the range is in the middle */
		range_prev->next = range;
		range->next = range_cur;
		range->rangeno = range_cur->rangeno;
		i_init = range_prev->rangeno;
	पूर्ण

	क्रम (count = i_init; count < noRanges; ++count) अणु
		++range_cur->rangeno;
		range_cur = range_cur->next;
	पूर्ण

	update_resources(bus_cur, type, i_init + 1);
	वापस 0;
पूर्ण

/*******************************************************************************
 * This routine goes through the list of resources of type 'type' and updates
 * the range numbers that they correspond to.  It was called from add_bus_range fnc
 *
 * Input: bus, type of the resource, the rangeno starting from which to update
 ******************************************************************************/
अटल व्योम update_resources(काष्ठा bus_node *bus_cur, पूर्णांक type, पूर्णांक rangeno)
अणु
	काष्ठा resource_node *res = शून्य;
	u8 eol = 0;	/* end of list indicator */

	चयन (type) अणु
		हाल MEM:
			अगर (bus_cur->firstMem)
				res = bus_cur->firstMem;
			अवरोध;
		हाल PFMEM:
			अगर (bus_cur->firstPFMem)
				res = bus_cur->firstPFMem;
			अवरोध;
		हाल IO:
			अगर (bus_cur->firstIO)
				res = bus_cur->firstIO;
			अवरोध;
	पूर्ण

	अगर (res) अणु
		जबतक (res) अणु
			अगर (res->rangeno == rangeno)
				अवरोध;
			अगर (res->next)
				res = res->next;
			अन्यथा अगर (res->nextRange)
				res = res->nextRange;
			अन्यथा अणु
				eol = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!eol) अणु
			/* found the range */
			जबतक (res) अणु
				++res->rangeno;
				res = res->next;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fix_me(काष्ठा resource_node *res, काष्ठा bus_node *bus_cur, काष्ठा range_node *range)
अणु
	अक्षर *str = "";
	चयन (res->type) अणु
		हाल IO:
			str = "io";
			अवरोध;
		हाल MEM:
			str = "mem";
			अवरोध;
		हाल PFMEM:
			str = "pfmem";
			अवरोध;
	पूर्ण

	जबतक (res) अणु
		अगर (res->rangeno == -1) अणु
			जबतक (range) अणु
				अगर ((res->start >= range->start) && (res->end <= range->end)) अणु
					res->rangeno = range->rangeno;
					debug("%s->rangeno in fix_resources is %d\n", str, res->rangeno);
					चयन (res->type) अणु
						हाल IO:
							--bus_cur->needIOUpdate;
							अवरोध;
						हाल MEM:
							--bus_cur->needMemUpdate;
							अवरोध;
						हाल PFMEM:
							--bus_cur->needPFMemUpdate;
							अवरोध;
					पूर्ण
					अवरोध;
				पूर्ण
				range = range->next;
			पूर्ण
		पूर्ण
		अगर (res->next)
			res = res->next;
		अन्यथा
			res = res->nextRange;
	पूर्ण

पूर्ण

/*****************************************************************************
 * This routine reassigns the range numbers to the resources that had a -1
 * This हाल can happen only अगर upon initialization, resources taken by pci dev
 * appear in EBDA beक्रमe the resources allocated क्रम that bus, since we करोn't
 * know the range, we assign -1, and this routine is called after a new range
 * is asचिन्हित to see the resources with unknown range beदीर्घ to the added range
 *
 * Input: current bus
 * Output: none, list of resources क्रम that bus are fixed अगर can be
 *******************************************************************************/
अटल व्योम fix_resources(काष्ठा bus_node *bus_cur)
अणु
	काष्ठा range_node *range;
	काष्ठा resource_node *res;

	debug("%s - bus_cur->busno = %d\n", __func__, bus_cur->busno);

	अगर (bus_cur->needIOUpdate) अणु
		res = bus_cur->firstIO;
		range = bus_cur->rangeIO;
		fix_me(res, bus_cur, range);
	पूर्ण
	अगर (bus_cur->needMemUpdate) अणु
		res = bus_cur->firstMem;
		range = bus_cur->rangeMem;
		fix_me(res, bus_cur, range);
	पूर्ण
	अगर (bus_cur->needPFMemUpdate) अणु
		res = bus_cur->firstPFMem;
		range = bus_cur->rangePFMem;
		fix_me(res, bus_cur, range);
	पूर्ण
पूर्ण

/*******************************************************************************
 * This routine adds a resource to the list of resources to the appropriate bus
 * based on their resource type and sorted by their starting addresses.  It assigns
 * the ptrs to next and nextRange अगर needed.
 *
 * Input: resource ptr
 * Output: ptrs asचिन्हित (to the node)
 * 0 or -1
 *******************************************************************************/
पूर्णांक ibmphp_add_resource(काष्ठा resource_node *res)
अणु
	काष्ठा resource_node *res_cur;
	काष्ठा resource_node *res_prev;
	काष्ठा bus_node *bus_cur;
	काष्ठा range_node *range_cur = शून्य;
	काष्ठा resource_node *res_start = शून्य;

	debug("%s - enter\n", __func__);

	अगर (!res) अणु
		err("NULL passed to add\n");
		वापस -ENODEV;
	पूर्ण

	bus_cur = find_bus_wprev(res->busno, शून्य, 0);

	अगर (!bus_cur) अणु
		/* didn't find a bus, something's wrong!!! */
		debug("no bus in the system, either pci_dev's wrong or allocation failed\n");
		वापस -ENODEV;
	पूर्ण

	/* Normal हाल */
	चयन (res->type) अणु
		हाल IO:
			range_cur = bus_cur->rangeIO;
			res_start = bus_cur->firstIO;
			अवरोध;
		हाल MEM:
			range_cur = bus_cur->rangeMem;
			res_start = bus_cur->firstMem;
			अवरोध;
		हाल PFMEM:
			range_cur = bus_cur->rangePFMem;
			res_start = bus_cur->firstPFMem;
			अवरोध;
		शेष:
			err("cannot read the type of the resource to add... problem\n");
			वापस -EINVAL;
	पूर्ण
	जबतक (range_cur) अणु
		अगर ((res->start >= range_cur->start) && (res->end <= range_cur->end)) अणु
			res->rangeno = range_cur->rangeno;
			अवरोध;
		पूर्ण
		range_cur = range_cur->next;
	पूर्ण

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * this is again the हाल of rangeno = -1
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 */

	अगर (!range_cur) अणु
		चयन (res->type) अणु
			हाल IO:
				++bus_cur->needIOUpdate;
				अवरोध;
			हाल MEM:
				++bus_cur->needMemUpdate;
				अवरोध;
			हाल PFMEM:
				++bus_cur->needPFMemUpdate;
				अवरोध;
		पूर्ण
		res->rangeno = -1;
	पूर्ण

	debug("The range is %d\n", res->rangeno);
	अगर (!res_start) अणु
		/* no firstअणुIO,Mem,Pfmemपूर्ण on the bus, 1st IO/Mem/Pfmem resource ever */
		चयन (res->type) अणु
			हाल IO:
				bus_cur->firstIO = res;
				अवरोध;
			हाल MEM:
				bus_cur->firstMem = res;
				अवरोध;
			हाल PFMEM:
				bus_cur->firstPFMem = res;
				अवरोध;
		पूर्ण
		res->next = शून्य;
		res->nextRange = शून्य;
	पूर्ण अन्यथा अणु
		res_cur = res_start;
		res_prev = शून्य;

		debug("res_cur->rangeno is %d\n", res_cur->rangeno);

		जबतक (res_cur) अणु
			अगर (res_cur->rangeno >= res->rangeno)
				अवरोध;
			res_prev = res_cur;
			अगर (res_cur->next)
				res_cur = res_cur->next;
			अन्यथा
				res_cur = res_cur->nextRange;
		पूर्ण

		अगर (!res_cur) अणु
			/* at the end of the resource list */
			debug("i should be here, [%x - %x]\n", res->start, res->end);
			res_prev->nextRange = res;
			res->next = शून्य;
			res->nextRange = शून्य;
		पूर्ण अन्यथा अगर (res_cur->rangeno == res->rangeno) अणु
			/* in the same range */
			जबतक (res_cur) अणु
				अगर (res->start < res_cur->start)
					अवरोध;
				res_prev = res_cur;
				res_cur = res_cur->next;
			पूर्ण
			अगर (!res_cur) अणु
				/* the last resource in this range */
				res_prev->next = res;
				res->next = शून्य;
				res->nextRange = res_prev->nextRange;
				res_prev->nextRange = शून्य;
			पूर्ण अन्यथा अगर (res->start < res_cur->start) अणु
				/* at the beginning or middle of the range */
				अगर (!res_prev)	अणु
					चयन (res->type) अणु
						हाल IO:
							bus_cur->firstIO = res;
							अवरोध;
						हाल MEM:
							bus_cur->firstMem = res;
							अवरोध;
						हाल PFMEM:
							bus_cur->firstPFMem = res;
							अवरोध;
					पूर्ण
				पूर्ण अन्यथा अगर (res_prev->rangeno == res_cur->rangeno)
					res_prev->next = res;
				अन्यथा
					res_prev->nextRange = res;

				res->next = res_cur;
				res->nextRange = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* this is the हाल where it is 1st occurrence of the range */
			अगर (!res_prev) अणु
				/* at the beginning of the resource list */
				res->next = शून्य;
				चयन (res->type) अणु
					हाल IO:
						res->nextRange = bus_cur->firstIO;
						bus_cur->firstIO = res;
						अवरोध;
					हाल MEM:
						res->nextRange = bus_cur->firstMem;
						bus_cur->firstMem = res;
						अवरोध;
					हाल PFMEM:
						res->nextRange = bus_cur->firstPFMem;
						bus_cur->firstPFMem = res;
						अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (res_cur->rangeno > res->rangeno) अणु
				/* in the middle of the resource list */
				res_prev->nextRange = res;
				res->next = शून्य;
				res->nextRange = res_cur;
			पूर्ण
		पूर्ण
	पूर्ण

	debug("%s - exit\n", __func__);
	वापस 0;
पूर्ण

/****************************************************************************
 * This routine will हटाओ the resource from the list of resources
 *
 * Input: io, mem, and/or pfmem resource to be deleted
 * Output: modअगरied resource list
 *        0 or error code
 ****************************************************************************/
पूर्णांक ibmphp_हटाओ_resource(काष्ठा resource_node *res)
अणु
	काष्ठा bus_node *bus_cur;
	काष्ठा resource_node *res_cur = शून्य;
	काष्ठा resource_node *res_prev;
	काष्ठा resource_node *mem_cur;
	अक्षर *type = "";

	अगर (!res)  अणु
		err("resource to remove is NULL\n");
		वापस -ENODEV;
	पूर्ण

	bus_cur = find_bus_wprev(res->busno, शून्य, 0);

	अगर (!bus_cur) अणु
		err("cannot find corresponding bus of the io resource to remove  bailing out...\n");
		वापस -ENODEV;
	पूर्ण

	चयन (res->type) अणु
		हाल IO:
			res_cur = bus_cur->firstIO;
			type = "io";
			अवरोध;
		हाल MEM:
			res_cur = bus_cur->firstMem;
			type = "mem";
			अवरोध;
		हाल PFMEM:
			res_cur = bus_cur->firstPFMem;
			type = "pfmem";
			अवरोध;
		शेष:
			err("unknown type for resource to remove\n");
			वापस -EINVAL;
	पूर्ण
	res_prev = शून्य;

	जबतक (res_cur) अणु
		अगर ((res_cur->start == res->start) && (res_cur->end == res->end))
			अवरोध;
		res_prev = res_cur;
		अगर (res_cur->next)
			res_cur = res_cur->next;
		अन्यथा
			res_cur = res_cur->nextRange;
	पूर्ण

	अगर (!res_cur) अणु
		अगर (res->type == PFMEM) अणु
			/*
			 * हाल where pfmem might be in the PFMemFromMem list
			 * so will also need to हटाओ the corresponding mem
			 * entry
			 */
			res_cur = bus_cur->firstPFMemFromMem;
			res_prev = शून्य;

			जबतक (res_cur) अणु
				अगर ((res_cur->start == res->start) && (res_cur->end == res->end)) अणु
					mem_cur = bus_cur->firstMem;
					जबतक (mem_cur) अणु
						अगर ((mem_cur->start == res_cur->start)
						    && (mem_cur->end == res_cur->end))
							अवरोध;
						अगर (mem_cur->next)
							mem_cur = mem_cur->next;
						अन्यथा
							mem_cur = mem_cur->nextRange;
					पूर्ण
					अगर (!mem_cur) अणु
						err("cannot find corresponding mem node for pfmem...\n");
						वापस -EINVAL;
					पूर्ण

					ibmphp_हटाओ_resource(mem_cur);
					अगर (!res_prev)
						bus_cur->firstPFMemFromMem = res_cur->next;
					अन्यथा
						res_prev->next = res_cur->next;
					kमुक्त(res_cur);
					वापस 0;
				पूर्ण
				res_prev = res_cur;
				अगर (res_cur->next)
					res_cur = res_cur->next;
				अन्यथा
					res_cur = res_cur->nextRange;
			पूर्ण
			अगर (!res_cur) अणु
				err("cannot find pfmem to delete...\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			err("the %s resource is not in the list to be deleted...\n", type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (!res_prev) अणु
		/* first device to be deleted */
		अगर (res_cur->next) अणु
			चयन (res->type) अणु
				हाल IO:
					bus_cur->firstIO = res_cur->next;
					अवरोध;
				हाल MEM:
					bus_cur->firstMem = res_cur->next;
					अवरोध;
				हाल PFMEM:
					bus_cur->firstPFMem = res_cur->next;
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (res_cur->nextRange) अणु
			चयन (res->type) अणु
				हाल IO:
					bus_cur->firstIO = res_cur->nextRange;
					अवरोध;
				हाल MEM:
					bus_cur->firstMem = res_cur->nextRange;
					अवरोध;
				हाल PFMEM:
					bus_cur->firstPFMem = res_cur->nextRange;
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (res->type) अणु
				हाल IO:
					bus_cur->firstIO = शून्य;
					अवरोध;
				हाल MEM:
					bus_cur->firstMem = शून्य;
					अवरोध;
				हाल PFMEM:
					bus_cur->firstPFMem = शून्य;
					अवरोध;
			पूर्ण
		पूर्ण
		kमुक्त(res_cur);
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (res_cur->next) अणु
			अगर (res_prev->rangeno == res_cur->rangeno)
				res_prev->next = res_cur->next;
			अन्यथा
				res_prev->nextRange = res_cur->next;
		पूर्ण अन्यथा अगर (res_cur->nextRange) अणु
			res_prev->next = शून्य;
			res_prev->nextRange = res_cur->nextRange;
		पूर्ण अन्यथा अणु
			res_prev->next = शून्य;
			res_prev->nextRange = शून्य;
		पूर्ण
		kमुक्त(res_cur);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा range_node *find_range(काष्ठा bus_node *bus_cur, काष्ठा resource_node *res)
अणु
	काष्ठा range_node *range = शून्य;

	चयन (res->type) अणु
		हाल IO:
			range = bus_cur->rangeIO;
			अवरोध;
		हाल MEM:
			range = bus_cur->rangeMem;
			अवरोध;
		हाल PFMEM:
			range = bus_cur->rangePFMem;
			अवरोध;
		शेष:
			err("cannot read resource type in find_range\n");
	पूर्ण

	जबतक (range) अणु
		अगर (res->rangeno == range->rangeno)
			अवरोध;
		range = range->next;
	पूर्ण
	वापस range;
पूर्ण

/*****************************************************************************
 * This routine will check to make sure the io/mem/pfmem->len that the device asked क्रम
 * can fit w/i our list of available IO/MEM/PFMEM resources.  If cannot, वापसs -EINVAL,
 * otherwise, वापसs 0
 *
 * Input: resource
 * Output: the correct start and end address are inputted पूर्णांकo the resource node,
 *        0 or -EINVAL
 *****************************************************************************/
पूर्णांक ibmphp_check_resource(काष्ठा resource_node *res, u8 bridge)
अणु
	काष्ठा bus_node *bus_cur;
	काष्ठा range_node *range = शून्य;
	काष्ठा resource_node *res_prev;
	काष्ठा resource_node *res_cur = शून्य;
	u32 len_cur = 0, start_cur = 0, len_पंचांगp = 0;
	पूर्णांक noranges = 0;
	u32 पंचांगp_start;		/* this is to make sure start address is भागisible by the length needed */
	u32 पंचांगp_भागide;
	u8 flag = 0;

	अगर (!res)
		वापस -EINVAL;

	अगर (bridge) अणु
		/* The rules क्रम bridges are dअगरferent, 4K भागisible क्रम IO, 1M क्रम (pf)mem*/
		अगर (res->type == IO)
			पंचांगp_भागide = IOBRIDGE;
		अन्यथा
			पंचांगp_भागide = MEMBRIDGE;
	पूर्ण अन्यथा
		पंचांगp_भागide = res->len;

	bus_cur = find_bus_wprev(res->busno, शून्य, 0);

	अगर (!bus_cur) अणु
		/* didn't find a bus, something's wrong!!! */
		debug("no bus in the system, either pci_dev's wrong or allocation failed\n");
		वापस -EINVAL;
	पूर्ण

	debug("%s - enter\n", __func__);
	debug("bus_cur->busno is %d\n", bus_cur->busno);

	/* This is a quick fix to not mess up with the code very much.  i.e.,
	 * 2000-2fff, len = 1000, but when we compare, we need it to be fff */
	res->len -= 1;

	चयन (res->type) अणु
		हाल IO:
			res_cur = bus_cur->firstIO;
			noranges = bus_cur->noIORanges;
			अवरोध;
		हाल MEM:
			res_cur = bus_cur->firstMem;
			noranges = bus_cur->noMemRanges;
			अवरोध;
		हाल PFMEM:
			res_cur = bus_cur->firstPFMem;
			noranges = bus_cur->noPFMemRanges;
			अवरोध;
		शेष:
			err("wrong type of resource to check\n");
			वापस -EINVAL;
	पूर्ण
	res_prev = शून्य;

	जबतक (res_cur) अणु
		range = find_range(bus_cur, res_cur);
		debug("%s - rangeno = %d\n", __func__, res_cur->rangeno);

		अगर (!range) अणु
			err("no range for the device exists... bailing out...\n");
			वापस -EINVAL;
		पूर्ण

		/* found our range */
		अगर (!res_prev) अणु
			/* first समय in the loop */
			len_पंचांगp = res_cur->start - 1 - range->start;

			अगर ((res_cur->start != range->start) && (len_पंचांगp >= res->len)) अणु
				debug("len_tmp = %x\n", len_पंचांगp);

				अगर ((len_पंचांगp < len_cur) || (len_cur == 0)) अणु

					अगर ((range->start % पंचांगp_भागide) == 0) अणु
						/* just perfect, starting address is भागisible by length */
						flag = 1;
						len_cur = len_पंचांगp;
						start_cur = range->start;
					पूर्ण अन्यथा अणु
						/* Needs adjusting */
						पंचांगp_start = range->start;
						flag = 0;

						जबतक ((len_पंचांगp = res_cur->start - 1 - पंचांगp_start) >= res->len) अणु
							अगर ((पंचांगp_start % पंचांगp_भागide) == 0) अणु
								flag = 1;
								len_cur = len_पंचांगp;
								start_cur = पंचांगp_start;
								अवरोध;
							पूर्ण
							पंचांगp_start += पंचांगp_भागide - पंचांगp_start % पंचांगp_भागide;
							अगर (पंचांगp_start >= res_cur->start - 1)
								अवरोध;
						पूर्ण
					पूर्ण

					अगर (flag && len_cur == res->len) अणु
						debug("but we are not here, right?\n");
						res->start = start_cur;
						res->len += 1; /* To restore the balance */
						res->end = res->start + res->len - 1;
						वापस 0;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!res_cur->next) अणु
			/* last device on the range */
			len_पंचांगp = range->end - (res_cur->end + 1);

			अगर ((range->end != res_cur->end) && (len_पंचांगp >= res->len)) अणु
				debug("len_tmp = %x\n", len_पंचांगp);
				अगर ((len_पंचांगp < len_cur) || (len_cur == 0)) अणु

					अगर (((res_cur->end + 1) % पंचांगp_भागide) == 0) अणु
						/* just perfect, starting address is भागisible by length */
						flag = 1;
						len_cur = len_पंचांगp;
						start_cur = res_cur->end + 1;
					पूर्ण अन्यथा अणु
						/* Needs adjusting */
						पंचांगp_start = res_cur->end + 1;
						flag = 0;

						जबतक ((len_पंचांगp = range->end - पंचांगp_start) >= res->len) अणु
							अगर ((पंचांगp_start % पंचांगp_भागide) == 0) अणु
								flag = 1;
								len_cur = len_पंचांगp;
								start_cur = पंचांगp_start;
								अवरोध;
							पूर्ण
							पंचांगp_start += पंचांगp_भागide - पंचांगp_start % पंचांगp_भागide;
							अगर (पंचांगp_start >= range->end)
								अवरोध;
						पूर्ण
					पूर्ण
					अगर (flag && len_cur == res->len) अणु
						res->start = start_cur;
						res->len += 1; /* To restore the balance */
						res->end = res->start + res->len - 1;
						वापस 0;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (res_prev) अणु
			अगर (res_prev->rangeno != res_cur->rangeno) अणु
				/* 1st device on this range */
				len_पंचांगp = res_cur->start - 1 - range->start;

				अगर ((res_cur->start != range->start) &&	(len_पंचांगp >= res->len)) अणु
					अगर ((len_पंचांगp < len_cur) || (len_cur == 0)) अणु
						अगर ((range->start % पंचांगp_भागide) == 0) अणु
							/* just perfect, starting address is भागisible by length */
							flag = 1;
							len_cur = len_पंचांगp;
							start_cur = range->start;
						पूर्ण अन्यथा अणु
							/* Needs adjusting */
							पंचांगp_start = range->start;
							flag = 0;

							जबतक ((len_पंचांगp = res_cur->start - 1 - पंचांगp_start) >= res->len) अणु
								अगर ((पंचांगp_start % पंचांगp_भागide) == 0) अणु
									flag = 1;
									len_cur = len_पंचांगp;
									start_cur = पंचांगp_start;
									अवरोध;
								पूर्ण
								पंचांगp_start += पंचांगp_भागide - पंचांगp_start % पंचांगp_भागide;
								अगर (पंचांगp_start >= res_cur->start - 1)
									अवरोध;
							पूर्ण
						पूर्ण

						अगर (flag && len_cur == res->len) अणु
							res->start = start_cur;
							res->len += 1; /* To restore the balance */
							res->end = res->start + res->len - 1;
							वापस 0;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				/* in the same range */
				len_पंचांगp = res_cur->start - 1 - res_prev->end - 1;

				अगर (len_पंचांगp >= res->len) अणु
					अगर ((len_पंचांगp < len_cur) || (len_cur == 0)) अणु
						अगर (((res_prev->end + 1) % पंचांगp_भागide) == 0) अणु
							/* just perfect, starting address's भागisible by length */
							flag = 1;
							len_cur = len_पंचांगp;
							start_cur = res_prev->end + 1;
						पूर्ण अन्यथा अणु
							/* Needs adjusting */
							पंचांगp_start = res_prev->end + 1;
							flag = 0;

							जबतक ((len_पंचांगp = res_cur->start - 1 - पंचांगp_start) >= res->len) अणु
								अगर ((पंचांगp_start % पंचांगp_भागide) == 0) अणु
									flag = 1;
									len_cur = len_पंचांगp;
									start_cur = पंचांगp_start;
									अवरोध;
								पूर्ण
								पंचांगp_start += पंचांगp_भागide - पंचांगp_start % पंचांगp_भागide;
								अगर (पंचांगp_start >= res_cur->start - 1)
									अवरोध;
							पूर्ण
						पूर्ण

						अगर (flag && len_cur == res->len) अणु
							res->start = start_cur;
							res->len += 1; /* To restore the balance */
							res->end = res->start + res->len - 1;
							वापस 0;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		/* end अगर (res_prev) */
		res_prev = res_cur;
		अगर (res_cur->next)
			res_cur = res_cur->next;
		अन्यथा
			res_cur = res_cur->nextRange;
	पूर्ण	/* end of जबतक */


	अगर (!res_prev) अणु
		/* 1st device ever */
		/* need to find appropriate range */
		चयन (res->type) अणु
			हाल IO:
				range = bus_cur->rangeIO;
				अवरोध;
			हाल MEM:
				range = bus_cur->rangeMem;
				अवरोध;
			हाल PFMEM:
				range = bus_cur->rangePFMem;
				अवरोध;
		पूर्ण
		जबतक (range) अणु
			len_पंचांगp = range->end - range->start;

			अगर (len_पंचांगp >= res->len) अणु
				अगर ((len_पंचांगp < len_cur) || (len_cur == 0)) अणु
					अगर ((range->start % पंचांगp_भागide) == 0) अणु
						/* just perfect, starting address's भागisible by length */
						flag = 1;
						len_cur = len_पंचांगp;
						start_cur = range->start;
					पूर्ण अन्यथा अणु
						/* Needs adjusting */
						पंचांगp_start = range->start;
						flag = 0;

						जबतक ((len_पंचांगp = range->end - पंचांगp_start) >= res->len) अणु
							अगर ((पंचांगp_start % पंचांगp_भागide) == 0) अणु
								flag = 1;
								len_cur = len_पंचांगp;
								start_cur = पंचांगp_start;
								अवरोध;
							पूर्ण
							पंचांगp_start += पंचांगp_भागide - पंचांगp_start % पंचांगp_भागide;
							अगर (पंचांगp_start >= range->end)
								अवरोध;
						पूर्ण
					पूर्ण

					अगर (flag && len_cur == res->len) अणु
						res->start = start_cur;
						res->len += 1; /* To restore the balance */
						res->end = res->start + res->len - 1;
						वापस 0;
					पूर्ण
				पूर्ण
			पूर्ण
			range = range->next;
		पूर्ण		/* end of जबतक */

		अगर ((!range) && (len_cur == 0)) अणु
			/* have gone through the list of devices and ranges and haven't found n.e.thing */
			err("no appropriate range.. bailing out...\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (len_cur) अणु
			res->start = start_cur;
			res->len += 1; /* To restore the balance */
			res->end = res->start + res->len - 1;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!res_cur) अणु
		debug("prev->rangeno = %d, noranges = %d\n", res_prev->rangeno, noranges);
		अगर (res_prev->rangeno < noranges) अणु
			/* अगर there're more ranges out there to check */
			चयन (res->type) अणु
				हाल IO:
					range = bus_cur->rangeIO;
					अवरोध;
				हाल MEM:
					range = bus_cur->rangeMem;
					अवरोध;
				हाल PFMEM:
					range = bus_cur->rangePFMem;
					अवरोध;
			पूर्ण
			जबतक (range) अणु
				len_पंचांगp = range->end - range->start;

				अगर (len_पंचांगp >= res->len) अणु
					अगर ((len_पंचांगp < len_cur) || (len_cur == 0)) अणु
						अगर ((range->start % पंचांगp_भागide) == 0) अणु
							/* just perfect, starting address's भागisible by length */
							flag = 1;
							len_cur = len_पंचांगp;
							start_cur = range->start;
						पूर्ण अन्यथा अणु
							/* Needs adjusting */
							पंचांगp_start = range->start;
							flag = 0;

							जबतक ((len_पंचांगp = range->end - पंचांगp_start) >= res->len) अणु
								अगर ((पंचांगp_start % पंचांगp_भागide) == 0) अणु
									flag = 1;
									len_cur = len_पंचांगp;
									start_cur = पंचांगp_start;
									अवरोध;
								पूर्ण
								पंचांगp_start += पंचांगp_भागide - पंचांगp_start % पंचांगp_भागide;
								अगर (पंचांगp_start >= range->end)
									अवरोध;
							पूर्ण
						पूर्ण

						अगर (flag && len_cur == res->len) अणु
							res->start = start_cur;
							res->len += 1; /* To restore the balance */
							res->end = res->start + res->len - 1;
							वापस 0;
						पूर्ण
					पूर्ण
				पूर्ण
				range = range->next;
			पूर्ण	/* end of जबतक */

			अगर ((!range) && (len_cur == 0)) अणु
				/* have gone through the list of devices and ranges and haven't found n.e.thing */
				err("no appropriate range.. bailing out...\n");
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (len_cur) अणु
				res->start = start_cur;
				res->len += 1; /* To restore the balance */
				res->end = res->start + res->len - 1;
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* no more ranges to check on */
			अगर (len_cur) अणु
				res->start = start_cur;
				res->len += 1; /* To restore the balance */
				res->end = res->start + res->len - 1;
				वापस 0;
			पूर्ण अन्यथा अणु
				/* have gone through the list of devices and haven't found n.e.thing */
				err("no appropriate range.. bailing out...\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण	/* end अगर (!res_cur) */
	वापस -EINVAL;
पूर्ण

/********************************************************************************
 * This routine is called from हटाओ_card अगर the card contained PPB.
 * It will हटाओ all the resources on the bus as well as the bus itself
 * Input: Bus
 * Output: 0, -ENODEV
 ********************************************************************************/
पूर्णांक ibmphp_हटाओ_bus(काष्ठा bus_node *bus, u8 parent_busno)
अणु
	काष्ठा resource_node *res_cur;
	काष्ठा resource_node *res_पंचांगp;
	काष्ठा bus_node *prev_bus;
	पूर्णांक rc;

	prev_bus = find_bus_wprev(parent_busno, शून्य, 0);

	अगर (!prev_bus) अणु
		debug("something terribly wrong. Cannot find parent bus to the one to remove\n");
		वापस -ENODEV;
	पूर्ण

	debug("In ibmphp_remove_bus... prev_bus->busno is %x\n", prev_bus->busno);

	rc = हटाओ_ranges(bus, prev_bus);
	अगर (rc)
		वापस rc;

	अगर (bus->firstIO) अणु
		res_cur = bus->firstIO;
		जबतक (res_cur) अणु
			res_पंचांगp = res_cur;
			अगर (res_cur->next)
				res_cur = res_cur->next;
			अन्यथा
				res_cur = res_cur->nextRange;
			kमुक्त(res_पंचांगp);
			res_पंचांगp = शून्य;
		पूर्ण
		bus->firstIO = शून्य;
	पूर्ण
	अगर (bus->firstMem) अणु
		res_cur = bus->firstMem;
		जबतक (res_cur) अणु
			res_पंचांगp = res_cur;
			अगर (res_cur->next)
				res_cur = res_cur->next;
			अन्यथा
				res_cur = res_cur->nextRange;
			kमुक्त(res_पंचांगp);
			res_पंचांगp = शून्य;
		पूर्ण
		bus->firstMem = शून्य;
	पूर्ण
	अगर (bus->firstPFMem) अणु
		res_cur = bus->firstPFMem;
		जबतक (res_cur) अणु
			res_पंचांगp = res_cur;
			अगर (res_cur->next)
				res_cur = res_cur->next;
			अन्यथा
				res_cur = res_cur->nextRange;
			kमुक्त(res_पंचांगp);
			res_पंचांगp = शून्य;
		पूर्ण
		bus->firstPFMem = शून्य;
	पूर्ण

	अगर (bus->firstPFMemFromMem) अणु
		res_cur = bus->firstPFMemFromMem;
		जबतक (res_cur) अणु
			res_पंचांगp = res_cur;
			res_cur = res_cur->next;

			kमुक्त(res_पंचांगp);
			res_पंचांगp = शून्य;
		पूर्ण
		bus->firstPFMemFromMem = शून्य;
	पूर्ण

	list_del(&bus->bus_list);
	kमुक्त(bus);
	वापस 0;
पूर्ण

/******************************************************************************
 * This routine deletes the ranges from a given bus, and the entries from the
 * parent's bus in the resources
 * Input: current bus, previous bus
 * Output: 0, -EINVAL
 ******************************************************************************/
अटल पूर्णांक हटाओ_ranges(काष्ठा bus_node *bus_cur, काष्ठा bus_node *bus_prev)
अणु
	काष्ठा range_node *range_cur;
	काष्ठा range_node *range_पंचांगp;
	पूर्णांक i;
	काष्ठा resource_node *res = शून्य;

	अगर (bus_cur->noIORanges) अणु
		range_cur = bus_cur->rangeIO;
		क्रम (i = 0; i < bus_cur->noIORanges; i++) अणु
			अगर (ibmphp_find_resource(bus_prev, range_cur->start, &res, IO) < 0)
				वापस -EINVAL;
			ibmphp_हटाओ_resource(res);

			range_पंचांगp = range_cur;
			range_cur = range_cur->next;
			kमुक्त(range_पंचांगp);
			range_पंचांगp = शून्य;
		पूर्ण
		bus_cur->rangeIO = शून्य;
	पूर्ण
	अगर (bus_cur->noMemRanges) अणु
		range_cur = bus_cur->rangeMem;
		क्रम (i = 0; i < bus_cur->noMemRanges; i++) अणु
			अगर (ibmphp_find_resource(bus_prev, range_cur->start, &res, MEM) < 0)
				वापस -EINVAL;

			ibmphp_हटाओ_resource(res);
			range_पंचांगp = range_cur;
			range_cur = range_cur->next;
			kमुक्त(range_पंचांगp);
			range_पंचांगp = शून्य;
		पूर्ण
		bus_cur->rangeMem = शून्य;
	पूर्ण
	अगर (bus_cur->noPFMemRanges) अणु
		range_cur = bus_cur->rangePFMem;
		क्रम (i = 0; i < bus_cur->noPFMemRanges; i++) अणु
			अगर (ibmphp_find_resource(bus_prev, range_cur->start, &res, PFMEM) < 0)
				वापस -EINVAL;

			ibmphp_हटाओ_resource(res);
			range_पंचांगp = range_cur;
			range_cur = range_cur->next;
			kमुक्त(range_पंचांगp);
			range_पंचांगp = शून्य;
		पूर्ण
		bus_cur->rangePFMem = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * find the resource node in the bus
 * Input: Resource needed, start address of the resource, type of resource
 */
पूर्णांक ibmphp_find_resource(काष्ठा bus_node *bus, u32 start_address, काष्ठा resource_node **res, पूर्णांक flag)
अणु
	काष्ठा resource_node *res_cur = शून्य;
	अक्षर *type = "";

	अगर (!bus) अणु
		err("The bus passed in NULL to find resource\n");
		वापस -ENODEV;
	पूर्ण

	चयन (flag) अणु
		हाल IO:
			res_cur = bus->firstIO;
			type = "io";
			अवरोध;
		हाल MEM:
			res_cur = bus->firstMem;
			type = "mem";
			अवरोध;
		हाल PFMEM:
			res_cur = bus->firstPFMem;
			type = "pfmem";
			अवरोध;
		शेष:
			err("wrong type of flag\n");
			वापस -EINVAL;
	पूर्ण

	जबतक (res_cur) अणु
		अगर (res_cur->start == start_address) अणु
			*res = res_cur;
			अवरोध;
		पूर्ण
		अगर (res_cur->next)
			res_cur = res_cur->next;
		अन्यथा
			res_cur = res_cur->nextRange;
	पूर्ण

	अगर (!res_cur) अणु
		अगर (flag == PFMEM) अणु
			res_cur = bus->firstPFMemFromMem;
			जबतक (res_cur) अणु
				अगर (res_cur->start == start_address) अणु
					*res = res_cur;
					अवरोध;
				पूर्ण
				res_cur = res_cur->next;
			पूर्ण
			अगर (!res_cur) अणु
				debug("SOS...cannot find %s resource in the bus.\n", type);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			debug("SOS... cannot find %s resource in the bus.\n", type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (*res)
		debug("*res->start = %x\n", (*res)->start);

	वापस 0;
पूर्ण

/***********************************************************************
 * This routine will मुक्त the resource काष्ठाures used by the
 * प्रणाली.  It is called from cleanup routine क्रम the module
 * Parameters: none
 * Returns: none
 ***********************************************************************/
व्योम ibmphp_मुक्त_resources(व्योम)
अणु
	काष्ठा bus_node *bus_cur = शून्य, *next;
	काष्ठा bus_node *bus_पंचांगp;
	काष्ठा range_node *range_cur;
	काष्ठा range_node *range_पंचांगp;
	काष्ठा resource_node *res_cur;
	काष्ठा resource_node *res_पंचांगp;
	पूर्णांक i = 0;
	flags = 1;

	list_क्रम_each_entry_safe(bus_cur, next, &gbuses, bus_list) अणु
		अगर (bus_cur->noIORanges) अणु
			range_cur = bus_cur->rangeIO;
			क्रम (i = 0; i < bus_cur->noIORanges; i++) अणु
				अगर (!range_cur)
					अवरोध;
				range_पंचांगp = range_cur;
				range_cur = range_cur->next;
				kमुक्त(range_पंचांगp);
				range_पंचांगp = शून्य;
			पूर्ण
		पूर्ण
		अगर (bus_cur->noMemRanges) अणु
			range_cur = bus_cur->rangeMem;
			क्रम (i = 0; i < bus_cur->noMemRanges; i++) अणु
				अगर (!range_cur)
					अवरोध;
				range_पंचांगp = range_cur;
				range_cur = range_cur->next;
				kमुक्त(range_पंचांगp);
				range_पंचांगp = शून्य;
			पूर्ण
		पूर्ण
		अगर (bus_cur->noPFMemRanges) अणु
			range_cur = bus_cur->rangePFMem;
			क्रम (i = 0; i < bus_cur->noPFMemRanges; i++) अणु
				अगर (!range_cur)
					अवरोध;
				range_पंचांगp = range_cur;
				range_cur = range_cur->next;
				kमुक्त(range_पंचांगp);
				range_पंचांगp = शून्य;
			पूर्ण
		पूर्ण

		अगर (bus_cur->firstIO) अणु
			res_cur = bus_cur->firstIO;
			जबतक (res_cur) अणु
				res_पंचांगp = res_cur;
				अगर (res_cur->next)
					res_cur = res_cur->next;
				अन्यथा
					res_cur = res_cur->nextRange;
				kमुक्त(res_पंचांगp);
				res_पंचांगp = शून्य;
			पूर्ण
			bus_cur->firstIO = शून्य;
		पूर्ण
		अगर (bus_cur->firstMem) अणु
			res_cur = bus_cur->firstMem;
			जबतक (res_cur) अणु
				res_पंचांगp = res_cur;
				अगर (res_cur->next)
					res_cur = res_cur->next;
				अन्यथा
					res_cur = res_cur->nextRange;
				kमुक्त(res_पंचांगp);
				res_पंचांगp = शून्य;
			पूर्ण
			bus_cur->firstMem = शून्य;
		पूर्ण
		अगर (bus_cur->firstPFMem) अणु
			res_cur = bus_cur->firstPFMem;
			जबतक (res_cur) अणु
				res_पंचांगp = res_cur;
				अगर (res_cur->next)
					res_cur = res_cur->next;
				अन्यथा
					res_cur = res_cur->nextRange;
				kमुक्त(res_पंचांगp);
				res_पंचांगp = शून्य;
			पूर्ण
			bus_cur->firstPFMem = शून्य;
		पूर्ण

		अगर (bus_cur->firstPFMemFromMem) अणु
			res_cur = bus_cur->firstPFMemFromMem;
			जबतक (res_cur) अणु
				res_पंचांगp = res_cur;
				res_cur = res_cur->next;

				kमुक्त(res_पंचांगp);
				res_पंचांगp = शून्य;
			पूर्ण
			bus_cur->firstPFMemFromMem = शून्य;
		पूर्ण

		bus_पंचांगp = bus_cur;
		list_del(&bus_cur->bus_list);
		kमुक्त(bus_पंचांगp);
		bus_पंचांगp = शून्य;
	पूर्ण
पूर्ण

/*********************************************************************************
 * This function will go over the PFmem resources to check अगर the EBDA allocated
 * pfmem out of memory buckets of the bus.  If so, it will change the range numbers
 * and a flag to indicate that this resource is out of memory. It will also move the
 * Pfmem out of the pfmem resource list to the PFMemFromMem list, and will create
 * a new Mem node
 * This routine is called right after initialization
 *******************************************************************************/
अटल पूर्णांक __init once_over(व्योम)
अणु
	काष्ठा resource_node *pfmem_cur;
	काष्ठा resource_node *pfmem_prev;
	काष्ठा resource_node *mem;
	काष्ठा bus_node *bus_cur;

	list_क्रम_each_entry(bus_cur, &gbuses, bus_list) अणु
		अगर ((!bus_cur->rangePFMem) && (bus_cur->firstPFMem)) अणु
			क्रम (pfmem_cur = bus_cur->firstPFMem, pfmem_prev = शून्य; pfmem_cur; pfmem_prev = pfmem_cur, pfmem_cur = pfmem_cur->next) अणु
				pfmem_cur->fromMem = 1;
				अगर (pfmem_prev)
					pfmem_prev->next = pfmem_cur->next;
				अन्यथा
					bus_cur->firstPFMem = pfmem_cur->next;

				अगर (!bus_cur->firstPFMemFromMem)
					pfmem_cur->next = शून्य;
				अन्यथा
					/* we करोn't need to sort PFMemFromMem since we're using mem node क्रम
					   all the real work anyways, so just insert at the beginning of the
					   list
					 */
					pfmem_cur->next = bus_cur->firstPFMemFromMem;

				bus_cur->firstPFMemFromMem = pfmem_cur;

				mem = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
				अगर (!mem)
					वापस -ENOMEM;

				mem->type = MEM;
				mem->busno = pfmem_cur->busno;
				mem->devfunc = pfmem_cur->devfunc;
				mem->start = pfmem_cur->start;
				mem->end = pfmem_cur->end;
				mem->len = pfmem_cur->len;
				अगर (ibmphp_add_resource(mem) < 0)
					err("Trouble...trouble... EBDA allocated pfmem from mem, but system doesn't display it has this space... unless not PCI device...\n");
				pfmem_cur->rangeno = mem->rangeno;
			पूर्ण	/* end क्रम pfmem */
		पूर्ण	/* end अगर */
	पूर्ण	/* end list_क्रम_each bus */
	वापस 0;
पूर्ण

पूर्णांक ibmphp_add_pfmem_from_mem(काष्ठा resource_node *pfmem)
अणु
	काष्ठा bus_node *bus_cur = find_bus_wprev(pfmem->busno, शून्य, 0);

	अगर (!bus_cur) अणु
		err("cannot find bus of pfmem to add...\n");
		वापस -ENODEV;
	पूर्ण

	अगर (bus_cur->firstPFMemFromMem)
		pfmem->next = bus_cur->firstPFMemFromMem;
	अन्यथा
		pfmem->next = शून्य;

	bus_cur->firstPFMemFromMem = pfmem;

	वापस 0;
पूर्ण

/* This routine just goes through the buses to see अगर the bus alपढ़ोy exists.
 * It is called from ibmphp_find_sec_number, to find out a secondary bus number क्रम
 * bridged cards
 * Parameters: bus_number
 * Returns: Bus poपूर्णांकer or शून्य
 */
काष्ठा bus_node *ibmphp_find_res_bus(u8 bus_number)
अणु
	वापस find_bus_wprev(bus_number, शून्य, 0);
पूर्ण

अटल काष्ठा bus_node *find_bus_wprev(u8 bus_number, काष्ठा bus_node **prev, u8 flag)
अणु
	काष्ठा bus_node *bus_cur;

	list_क्रम_each_entry(bus_cur, &gbuses, bus_list) अणु
		अगर (flag)
			*prev = list_prev_entry(bus_cur, bus_list);
		अगर (bus_cur->busno == bus_number)
			वापस bus_cur;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम ibmphp_prपूर्णांक_test(व्योम)
अणु
	पूर्णांक i = 0;
	काष्ठा bus_node *bus_cur = शून्य;
	काष्ठा range_node *range;
	काष्ठा resource_node *res;

	debug_pci("*****************START**********************\n");

	अगर ((!list_empty(&gbuses)) && flags) अणु
		err("The GBUSES is not NULL?!?!?!?!?\n");
		वापस;
	पूर्ण

	list_क्रम_each_entry(bus_cur, &gbuses, bus_list) अणु
		debug_pci ("This is bus # %d.  There are\n", bus_cur->busno);
		debug_pci ("IORanges = %d\t", bus_cur->noIORanges);
		debug_pci ("MemRanges = %d\t", bus_cur->noMemRanges);
		debug_pci ("PFMemRanges = %d\n", bus_cur->noPFMemRanges);
		debug_pci ("The IO Ranges are as follows:\n");
		अगर (bus_cur->rangeIO) अणु
			range = bus_cur->rangeIO;
			क्रम (i = 0; i < bus_cur->noIORanges; i++) अणु
				debug_pci("rangeno is %d\n", range->rangeno);
				debug_pci("[%x - %x]\n", range->start, range->end);
				range = range->next;
			पूर्ण
		पूर्ण

		debug_pci("The Mem Ranges are as follows:\n");
		अगर (bus_cur->rangeMem) अणु
			range = bus_cur->rangeMem;
			क्रम (i = 0; i < bus_cur->noMemRanges; i++) अणु
				debug_pci("rangeno is %d\n", range->rangeno);
				debug_pci("[%x - %x]\n", range->start, range->end);
				range = range->next;
			पूर्ण
		पूर्ण

		debug_pci("The PFMem Ranges are as follows:\n");

		अगर (bus_cur->rangePFMem) अणु
			range = bus_cur->rangePFMem;
			क्रम (i = 0; i < bus_cur->noPFMemRanges; i++) अणु
				debug_pci("rangeno is %d\n", range->rangeno);
				debug_pci("[%x - %x]\n", range->start, range->end);
				range = range->next;
			पूर्ण
		पूर्ण

		debug_pci("The resources on this bus are as follows\n");

		debug_pci("IO...\n");
		अगर (bus_cur->firstIO) अणु
			res = bus_cur->firstIO;
			जबतक (res) अणु
				debug_pci("The range # is %d\n", res->rangeno);
				debug_pci("The bus, devfnc is %d, %x\n", res->busno, res->devfunc);
				debug_pci("[%x - %x], len=%x\n", res->start, res->end, res->len);
				अगर (res->next)
					res = res->next;
				अन्यथा अगर (res->nextRange)
					res = res->nextRange;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण
		debug_pci("Mem...\n");
		अगर (bus_cur->firstMem) अणु
			res = bus_cur->firstMem;
			जबतक (res) अणु
				debug_pci("The range # is %d\n", res->rangeno);
				debug_pci("The bus, devfnc is %d, %x\n", res->busno, res->devfunc);
				debug_pci("[%x - %x], len=%x\n", res->start, res->end, res->len);
				अगर (res->next)
					res = res->next;
				अन्यथा अगर (res->nextRange)
					res = res->nextRange;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण
		debug_pci("PFMem...\n");
		अगर (bus_cur->firstPFMem) अणु
			res = bus_cur->firstPFMem;
			जबतक (res) अणु
				debug_pci("The range # is %d\n", res->rangeno);
				debug_pci("The bus, devfnc is %d, %x\n", res->busno, res->devfunc);
				debug_pci("[%x - %x], len=%x\n", res->start, res->end, res->len);
				अगर (res->next)
					res = res->next;
				अन्यथा अगर (res->nextRange)
					res = res->nextRange;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण

		debug_pci("PFMemFromMem...\n");
		अगर (bus_cur->firstPFMemFromMem) अणु
			res = bus_cur->firstPFMemFromMem;
			जबतक (res) अणु
				debug_pci("The range # is %d\n", res->rangeno);
				debug_pci("The bus, devfnc is %d, %x\n", res->busno, res->devfunc);
				debug_pci("[%x - %x], len=%x\n", res->start, res->end, res->len);
				res = res->next;
			पूर्ण
		पूर्ण
	पूर्ण
	debug_pci("***********************END***********************\n");
पूर्ण

अटल पूर्णांक range_exists_alपढ़ोy(काष्ठा range_node *range, काष्ठा bus_node *bus_cur, u8 type)
अणु
	काष्ठा range_node *range_cur = शून्य;
	चयन (type) अणु
		हाल IO:
			range_cur = bus_cur->rangeIO;
			अवरोध;
		हाल MEM:
			range_cur = bus_cur->rangeMem;
			अवरोध;
		हाल PFMEM:
			range_cur = bus_cur->rangePFMem;
			अवरोध;
		शेष:
			err("wrong type passed to find out if range already exists\n");
			वापस -ENODEV;
	पूर्ण

	जबतक (range_cur) अणु
		अगर ((range_cur->start == range->start) && (range_cur->end == range->end))
			वापस 1;
		range_cur = range_cur->next;
	पूर्ण

	वापस 0;
पूर्ण

/* This routine will पढ़ो the winकरोws क्रम any PPB we have and update the
 * range info क्रम the secondary bus, and will also input this info पूर्णांकo
 * primary bus, since BIOS करोesn't. This is क्रम PPB that are in the प्रणाली
 * on bootup.  For bridged cards that were added during previous load of the
 * driver, only the ranges and the bus काष्ठाure are added, the devices are
 * added from NVRAM
 * Input: primary busno
 * Returns: none
 * Note: this function करोesn't take पूर्णांकo account IO restrictions etc,
 *	 so will only work क्रम bridges with no video/ISA devices behind them It
 *	 also will not work क्रम onboard PPBs that can have more than 1 *bus
 *	 behind them All these are TO DO.
 *	 Also need to add more error checkings... (from fnc वापसs etc)
 */
अटल पूर्णांक __init update_bridge_ranges(काष्ठा bus_node **bus)
अणु
	u8 sec_busno, device, function, hdr_type, start_io_address, end_io_address;
	u16 venकरोr_id, upper_io_start, upper_io_end, start_mem_address, end_mem_address;
	u32 start_address, end_address, upper_start, upper_end;
	काष्ठा bus_node *bus_sec;
	काष्ठा bus_node *bus_cur;
	काष्ठा resource_node *io;
	काष्ठा resource_node *mem;
	काष्ठा resource_node *pfmem;
	काष्ठा range_node *range;
	अचिन्हित पूर्णांक devfn;

	bus_cur = *bus;
	अगर (!bus_cur)
		वापस -ENODEV;
	ibmphp_pci_bus->number = bus_cur->busno;

	debug("inside %s\n", __func__);
	debug("bus_cur->busno = %x\n", bus_cur->busno);

	क्रम (device = 0; device < 32; device++) अणु
		क्रम (function = 0x00; function < 0x08; function++) अणु
			devfn = PCI_DEVFN(device, function);
			pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_VENDOR_ID, &venकरोr_id);

			अगर (venकरोr_id != PCI_VENDOR_ID_NOTVALID) अणु
				/* found correct device!!! */
				pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_HEADER_TYPE, &hdr_type);

				चयन (hdr_type) अणु
					हाल PCI_HEADER_TYPE_NORMAL:
						function = 0x8;
						अवरोध;
					हाल PCI_HEADER_TYPE_MULTIDEVICE:
						अवरोध;
					हाल PCI_HEADER_TYPE_BRIDGE:
						function = 0x8;
						fallthrough;
					हाल PCI_HEADER_TYPE_MULTIBRIDGE:
						/* We assume here that only 1 bus behind the bridge
						   TO DO: add functionality क्रम several:
						   temp = secondary;
						   जबतक (temp < subordinate) अणु
						   ...
						   temp++;
						   पूर्ण
						 */
						pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, &sec_busno);
						bus_sec = find_bus_wprev(sec_busno, शून्य, 0);
						/* this bus काष्ठाure करोesn't exist yet, PPB was configured during previous loading of ibmphp */
						अगर (!bus_sec) अणु
							bus_sec = alloc_error_bus(शून्य, sec_busno, 1);
							/* the rest will be populated during NVRAM call */
							वापस 0;
						पूर्ण
						pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, &start_io_address);
						pci_bus_पढ़ो_config_byte(ibmphp_pci_bus, devfn, PCI_IO_LIMIT, &end_io_address);
						pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_IO_BASE_UPPER16, &upper_io_start);
						pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_IO_LIMIT_UPPER16, &upper_io_end);
						start_address = (start_io_address & PCI_IO_RANGE_MASK) << 8;
						start_address |= (upper_io_start << 16);
						end_address = (end_io_address & PCI_IO_RANGE_MASK) << 8;
						end_address |= (upper_io_end << 16);

						अगर ((start_address) && (start_address <= end_address)) अणु
							range = kzalloc(माप(काष्ठा range_node), GFP_KERNEL);
							अगर (!range)
								वापस -ENOMEM;

							range->start = start_address;
							range->end = end_address + 0xfff;

							अगर (bus_sec->noIORanges > 0) अणु
								अगर (!range_exists_alपढ़ोy(range, bus_sec, IO)) अणु
									add_bus_range(IO, range, bus_sec);
									++bus_sec->noIORanges;
								पूर्ण अन्यथा अणु
									kमुक्त(range);
									range = शून्य;
								पूर्ण
							पूर्ण अन्यथा अणु
								/* 1st IO Range on the bus */
								range->rangeno = 1;
								bus_sec->rangeIO = range;
								++bus_sec->noIORanges;
							पूर्ण
							fix_resources(bus_sec);

							अगर (ibmphp_find_resource(bus_cur, start_address, &io, IO)) अणु
								io = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
								अगर (!io) अणु
									kमुक्त(range);
									वापस -ENOMEM;
								पूर्ण
								io->type = IO;
								io->busno = bus_cur->busno;
								io->devfunc = ((device << 3) | (function & 0x7));
								io->start = start_address;
								io->end = end_address + 0xfff;
								io->len = io->end - io->start + 1;
								ibmphp_add_resource(io);
							पूर्ण
						पूर्ण

						pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_BASE, &start_mem_address);
						pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_MEMORY_LIMIT, &end_mem_address);

						start_address = 0x00000000 | (start_mem_address & PCI_MEMORY_RANGE_MASK) << 16;
						end_address = 0x00000000 | (end_mem_address & PCI_MEMORY_RANGE_MASK) << 16;

						अगर ((start_address) && (start_address <= end_address)) अणु

							range = kzalloc(माप(काष्ठा range_node), GFP_KERNEL);
							अगर (!range)
								वापस -ENOMEM;

							range->start = start_address;
							range->end = end_address + 0xfffff;

							अगर (bus_sec->noMemRanges > 0) अणु
								अगर (!range_exists_alपढ़ोy(range, bus_sec, MEM)) अणु
									add_bus_range(MEM, range, bus_sec);
									++bus_sec->noMemRanges;
								पूर्ण अन्यथा अणु
									kमुक्त(range);
									range = शून्य;
								पूर्ण
							पूर्ण अन्यथा अणु
								/* 1st Mem Range on the bus */
								range->rangeno = 1;
								bus_sec->rangeMem = range;
								++bus_sec->noMemRanges;
							पूर्ण

							fix_resources(bus_sec);

							अगर (ibmphp_find_resource(bus_cur, start_address, &mem, MEM)) अणु
								mem = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
								अगर (!mem) अणु
									kमुक्त(range);
									वापस -ENOMEM;
								पूर्ण
								mem->type = MEM;
								mem->busno = bus_cur->busno;
								mem->devfunc = ((device << 3) | (function & 0x7));
								mem->start = start_address;
								mem->end = end_address + 0xfffff;
								mem->len = mem->end - mem->start + 1;
								ibmphp_add_resource(mem);
							पूर्ण
						पूर्ण
						pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_BASE, &start_mem_address);
						pci_bus_पढ़ो_config_word(ibmphp_pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, &end_mem_address);
						pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, PCI_PREF_BASE_UPPER32, &upper_start);
						pci_bus_पढ़ो_config_dword(ibmphp_pci_bus, devfn, PCI_PREF_LIMIT_UPPER32, &upper_end);
						start_address = 0x00000000 | (start_mem_address & PCI_MEMORY_RANGE_MASK) << 16;
						end_address = 0x00000000 | (end_mem_address & PCI_MEMORY_RANGE_MASK) << 16;
#अगर BITS_PER_LONG == 64
						start_address |= ((दीर्घ) upper_start) << 32;
						end_address |= ((दीर्घ) upper_end) << 32;
#पूर्ण_अगर

						अगर ((start_address) && (start_address <= end_address)) अणु

							range = kzalloc(माप(काष्ठा range_node), GFP_KERNEL);
							अगर (!range)
								वापस -ENOMEM;

							range->start = start_address;
							range->end = end_address + 0xfffff;

							अगर (bus_sec->noPFMemRanges > 0) अणु
								अगर (!range_exists_alपढ़ोy(range, bus_sec, PFMEM)) अणु
									add_bus_range(PFMEM, range, bus_sec);
									++bus_sec->noPFMemRanges;
								पूर्ण अन्यथा अणु
									kमुक्त(range);
									range = शून्य;
								पूर्ण
							पूर्ण अन्यथा अणु
								/* 1st PFMem Range on the bus */
								range->rangeno = 1;
								bus_sec->rangePFMem = range;
								++bus_sec->noPFMemRanges;
							पूर्ण

							fix_resources(bus_sec);
							अगर (ibmphp_find_resource(bus_cur, start_address, &pfmem, PFMEM)) अणु
								pfmem = kzalloc(माप(काष्ठा resource_node), GFP_KERNEL);
								अगर (!pfmem) अणु
									kमुक्त(range);
									वापस -ENOMEM;
								पूर्ण
								pfmem->type = PFMEM;
								pfmem->busno = bus_cur->busno;
								pfmem->devfunc = ((device << 3) | (function & 0x7));
								pfmem->start = start_address;
								pfmem->end = end_address + 0xfffff;
								pfmem->len = pfmem->end - pfmem->start + 1;
								pfmem->fromMem = 0;

								ibmphp_add_resource(pfmem);
							पूर्ण
						पूर्ण
						अवरोध;
				पूर्ण	/* end of चयन */
			पूर्ण	/* end अगर venकरोr */
		पूर्ण	/* end क्रम function */
	पूर्ण	/* end क्रम device */

	bus = &bus_cur;
	वापस 0;
पूर्ण
