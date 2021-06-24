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
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश "cpqphp.h"

अटल u32 configure_new_device(काष्ठा controller *ctrl, काष्ठा pci_func *func,
			u8 behind_bridge, काष्ठा resource_lists *resources);
अटल पूर्णांक configure_new_function(काष्ठा controller *ctrl, काष्ठा pci_func *func,
			u8 behind_bridge, काष्ठा resource_lists *resources);
अटल व्योम पूर्णांकerrupt_event_handler(काष्ठा controller *ctrl);


अटल काष्ठा task_काष्ठा *cpqhp_event_thपढ़ो;
अटल काष्ठा समयr_list *pushbutton_pending;	/* = शून्य */

/* delay is in jअगरfies to रुको क्रम */
अटल व्योम दीर्घ_delay(पूर्णांक delay)
अणु
	/*
	 * XXX(hch): अगर someone is bored please convert all callers
	 * to call msleep_पूर्णांकerruptible directly.  They really want
	 * to specअगरy समयouts in natural units and spend a lot of
	 * efक्रमt converting them to jअगरfies..
	 */
	msleep_पूर्णांकerruptible(jअगरfies_to_msecs(delay));
पूर्ण


/* FIXME: The following line needs to be somewhere अन्यथा... */
#घोषणा WRONG_BUS_FREQUENCY 0x07
अटल u8 handle_चयन_change(u8 change, काष्ठा controller *ctrl)
अणु
	पूर्णांक hp_slot;
	u8 rc = 0;
	u16 temp_word;
	काष्ठा pci_func *func;
	काष्ठा event_info *taskInfo;

	अगर (!change)
		वापस 0;

	/* Switch Change */
	dbg("cpqsbd:  Switch interrupt received.\n");

	क्रम (hp_slot = 0; hp_slot < 6; hp_slot++) अणु
		अगर (change & (0x1L << hp_slot)) अणु
			/*
			 * this one changed.
			 */
			func = cpqhp_slot_find(ctrl->bus,
				(hp_slot + ctrl->slot_device_offset), 0);

			/* this is the काष्ठाure that tells the worker thपढ़ो
			 * what to करो
			 */
			taskInfo = &(ctrl->event_queue[ctrl->next_event]);
			ctrl->next_event = (ctrl->next_event + 1) % 10;
			taskInfo->hp_slot = hp_slot;

			rc++;

			temp_word = ctrl->ctrl_पूर्णांक_comp >> 16;
			func->presence_save = (temp_word >> hp_slot) & 0x01;
			func->presence_save |= (temp_word >> (hp_slot + 7)) & 0x02;

			अगर (ctrl->ctrl_पूर्णांक_comp & (0x1L << hp_slot)) अणु
				/*
				 * Switch खोलोed
				 */

				func->चयन_save = 0;

				taskInfo->event_type = INT_SWITCH_OPEN;
			पूर्ण अन्यथा अणु
				/*
				 * Switch बंदd
				 */

				func->चयन_save = 0x10;

				taskInfo->event_type = INT_SWITCH_CLOSE;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * cpqhp_find_slot - find the काष्ठा slot of given device
 * @ctrl: scan lots of this controller
 * @device: the device id to find
 */
अटल काष्ठा slot *cpqhp_find_slot(काष्ठा controller *ctrl, u8 device)
अणु
	काष्ठा slot *slot = ctrl->slot;

	जबतक (slot && (slot->device != device))
		slot = slot->next;

	वापस slot;
पूर्ण


अटल u8 handle_presence_change(u16 change, काष्ठा controller *ctrl)
अणु
	पूर्णांक hp_slot;
	u8 rc = 0;
	u8 temp_byte;
	u16 temp_word;
	काष्ठा pci_func *func;
	काष्ठा event_info *taskInfo;
	काष्ठा slot *p_slot;

	अगर (!change)
		वापस 0;

	/*
	 * Presence Change
	 */
	dbg("cpqsbd:  Presence/Notify input change.\n");
	dbg("         Changed bits are 0x%4.4x\n", change);

	क्रम (hp_slot = 0; hp_slot < 6; hp_slot++) अणु
		अगर (change & (0x0101 << hp_slot)) अणु
			/*
			 * this one changed.
			 */
			func = cpqhp_slot_find(ctrl->bus,
				(hp_slot + ctrl->slot_device_offset), 0);

			taskInfo = &(ctrl->event_queue[ctrl->next_event]);
			ctrl->next_event = (ctrl->next_event + 1) % 10;
			taskInfo->hp_slot = hp_slot;

			rc++;

			p_slot = cpqhp_find_slot(ctrl, hp_slot + (पढ़ोb(ctrl->hpc_reg + SLOT_MASK) >> 4));
			अगर (!p_slot)
				वापस 0;

			/* If the चयन बंदd, must be a button
			 * If not in button mode, nevermind
			 */
			अगर (func->चयन_save && (ctrl->push_button == 1)) अणु
				temp_word = ctrl->ctrl_पूर्णांक_comp >> 16;
				temp_byte = (temp_word >> hp_slot) & 0x01;
				temp_byte |= (temp_word >> (hp_slot + 7)) & 0x02;

				अगर (temp_byte != func->presence_save) अणु
					/*
					 * button Pressed (करोesn't करो anything)
					 */
					dbg("hp_slot %d button pressed\n", hp_slot);
					taskInfo->event_type = INT_BUTTON_PRESS;
				पूर्ण अन्यथा अणु
					/*
					 * button Released - TAKE ACTION!!!!
					 */
					dbg("hp_slot %d button released\n", hp_slot);
					taskInfo->event_type = INT_BUTTON_RELEASE;

					/* Cancel अगर we are still blinking */
					अगर ((p_slot->state == BLINKINGON_STATE)
					    || (p_slot->state == BLINKINGOFF_STATE)) अणु
						taskInfo->event_type = INT_BUTTON_CANCEL;
						dbg("hp_slot %d button cancel\n", hp_slot);
					पूर्ण अन्यथा अगर ((p_slot->state == POWERON_STATE)
						   || (p_slot->state == POWEROFF_STATE)) अणु
						/* info(msg_button_ignore, p_slot->number); */
						taskInfo->event_type = INT_BUTTON_IGNORE;
						dbg("hp_slot %d button ignore\n", hp_slot);
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Switch is खोलो, assume a presence change
				 * Save the presence state
				 */
				temp_word = ctrl->ctrl_पूर्णांक_comp >> 16;
				func->presence_save = (temp_word >> hp_slot) & 0x01;
				func->presence_save |= (temp_word >> (hp_slot + 7)) & 0x02;

				अगर ((!(ctrl->ctrl_पूर्णांक_comp & (0x010000 << hp_slot))) ||
				    (!(ctrl->ctrl_पूर्णांक_comp & (0x01000000 << hp_slot)))) अणु
					/* Present */
					taskInfo->event_type = INT_PRESENCE_ON;
				पूर्ण अन्यथा अणु
					/* Not Present */
					taskInfo->event_type = INT_PRESENCE_OFF;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण


अटल u8 handle_घातer_fault(u8 change, काष्ठा controller *ctrl)
अणु
	पूर्णांक hp_slot;
	u8 rc = 0;
	काष्ठा pci_func *func;
	काष्ठा event_info *taskInfo;

	अगर (!change)
		वापस 0;

	/*
	 * घातer fault
	 */

	info("power fault interrupt\n");

	क्रम (hp_slot = 0; hp_slot < 6; hp_slot++) अणु
		अगर (change & (0x01 << hp_slot)) अणु
			/*
			 * this one changed.
			 */
			func = cpqhp_slot_find(ctrl->bus,
				(hp_slot + ctrl->slot_device_offset), 0);

			taskInfo = &(ctrl->event_queue[ctrl->next_event]);
			ctrl->next_event = (ctrl->next_event + 1) % 10;
			taskInfo->hp_slot = hp_slot;

			rc++;

			अगर (ctrl->ctrl_पूर्णांक_comp & (0x00000100 << hp_slot)) अणु
				/*
				 * घातer fault Cleared
				 */
				func->status = 0x00;

				taskInfo->event_type = INT_POWER_FAULT_CLEAR;
			पूर्ण अन्यथा अणु
				/*
				 * घातer fault
				 */
				taskInfo->event_type = INT_POWER_FAULT;

				अगर (ctrl->rev < 4) अणु
					amber_LED_on(ctrl, hp_slot);
					green_LED_off(ctrl, hp_slot);
					set_SOGO(ctrl);

					/* this is a fatal condition, we want
					 * to crash the machine to protect from
					 * data corruption. simulated_NMI
					 * shouldn't ever वापस */
					/* FIXME
					simulated_NMI(hp_slot, ctrl); */

					/* The following code causes a software
					 * crash just in हाल simulated_NMI did
					 * वापस */
					/*FIXME
					panic(msg_घातer_fault); */
				पूर्ण अन्यथा अणु
					/* set घातer fault status क्रम this board */
					func->status = 0xFF;
					info("power fault bit %x set\n", hp_slot);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण


/**
 * sort_by_size - sort nodes on the list by their length, smallest first.
 * @head: list to sort
 */
अटल पूर्णांक sort_by_size(काष्ठा pci_resource **head)
अणु
	काष्ठा pci_resource *current_res;
	काष्ठा pci_resource *next_res;
	पूर्णांक out_of_order = 1;

	अगर (!(*head))
		वापस 1;

	अगर (!((*head)->next))
		वापस 0;

	जबतक (out_of_order) अणु
		out_of_order = 0;

		/* Special हाल क्रम swapping list head */
		अगर (((*head)->next) &&
		    ((*head)->length > (*head)->next->length)) अणु
			out_of_order++;
			current_res = *head;
			*head = (*head)->next;
			current_res->next = (*head)->next;
			(*head)->next = current_res;
		पूर्ण

		current_res = *head;

		जबतक (current_res->next && current_res->next->next) अणु
			अगर (current_res->next->length > current_res->next->next->length) अणु
				out_of_order++;
				next_res = current_res->next;
				current_res->next = current_res->next->next;
				current_res = current_res->next;
				next_res->next = current_res->next;
				current_res->next = next_res;
			पूर्ण अन्यथा
				current_res = current_res->next;
		पूर्ण
	पूर्ण  /* End of out_of_order loop */

	वापस 0;
पूर्ण


/**
 * sort_by_max_size - sort nodes on the list by their length, largest first.
 * @head: list to sort
 */
अटल पूर्णांक sort_by_max_size(काष्ठा pci_resource **head)
अणु
	काष्ठा pci_resource *current_res;
	काष्ठा pci_resource *next_res;
	पूर्णांक out_of_order = 1;

	अगर (!(*head))
		वापस 1;

	अगर (!((*head)->next))
		वापस 0;

	जबतक (out_of_order) अणु
		out_of_order = 0;

		/* Special हाल क्रम swapping list head */
		अगर (((*head)->next) &&
		    ((*head)->length < (*head)->next->length)) अणु
			out_of_order++;
			current_res = *head;
			*head = (*head)->next;
			current_res->next = (*head)->next;
			(*head)->next = current_res;
		पूर्ण

		current_res = *head;

		जबतक (current_res->next && current_res->next->next) अणु
			अगर (current_res->next->length < current_res->next->next->length) अणु
				out_of_order++;
				next_res = current_res->next;
				current_res->next = current_res->next->next;
				current_res = current_res->next;
				next_res->next = current_res->next;
				current_res->next = next_res;
			पूर्ण अन्यथा
				current_res = current_res->next;
		पूर्ण
	पूर्ण  /* End of out_of_order loop */

	वापस 0;
पूर्ण


/**
 * करो_pre_bridge_resource_split - find node of resources that are unused
 * @head: new list head
 * @orig_head: original list head
 * @alignment: max node size (?)
 */
अटल काष्ठा pci_resource *करो_pre_bridge_resource_split(काष्ठा pci_resource **head,
				काष्ठा pci_resource **orig_head, u32 alignment)
अणु
	काष्ठा pci_resource *prevnode = शून्य;
	काष्ठा pci_resource *node;
	काष्ठा pci_resource *split_node;
	u32 rc;
	u32 temp_dword;
	dbg("do_pre_bridge_resource_split\n");

	अगर (!(*head) || !(*orig_head))
		वापस शून्य;

	rc = cpqhp_resource_sort_and_combine(head);

	अगर (rc)
		वापस शून्य;

	अगर ((*head)->base != (*orig_head)->base)
		वापस शून्य;

	अगर ((*head)->length == (*orig_head)->length)
		वापस शून्य;


	/* If we got here, there the bridge requires some of the resource, but
	 * we may be able to split some off of the front
	 */

	node = *head;

	अगर (node->length & (alignment - 1)) अणु
		/* this one isn't an aligned length, so we'll make a new entry
		 * and split it up.
		 */
		split_node = kदो_स्मृति(माप(*split_node), GFP_KERNEL);

		अगर (!split_node)
			वापस शून्य;

		temp_dword = (node->length | (alignment-1)) + 1 - alignment;

		split_node->base = node->base;
		split_node->length = temp_dword;

		node->length -= temp_dword;
		node->base += split_node->length;

		/* Put it in the list */
		*head = split_node;
		split_node->next = node;
	पूर्ण

	अगर (node->length < alignment)
		वापस शून्य;

	/* Now unlink it */
	अगर (*head == node) अणु
		*head = node->next;
	पूर्ण अन्यथा अणु
		prevnode = *head;
		जबतक (prevnode->next != node)
			prevnode = prevnode->next;

		prevnode->next = node->next;
	पूर्ण
	node->next = शून्य;

	वापस node;
पूर्ण


/**
 * करो_bridge_resource_split - find one node of resources that aren't in use
 * @head: list head
 * @alignment: max node size (?)
 */
अटल काष्ठा pci_resource *करो_bridge_resource_split(काष्ठा pci_resource **head, u32 alignment)
अणु
	काष्ठा pci_resource *prevnode = शून्य;
	काष्ठा pci_resource *node;
	u32 rc;
	u32 temp_dword;

	rc = cpqhp_resource_sort_and_combine(head);

	अगर (rc)
		वापस शून्य;

	node = *head;

	जबतक (node->next) अणु
		prevnode = node;
		node = node->next;
		kमुक्त(prevnode);
	पूर्ण

	अगर (node->length < alignment)
		जाओ error;

	अगर (node->base & (alignment - 1)) अणु
		/* Short circuit अगर adjusted size is too small */
		temp_dword = (node->base | (alignment-1)) + 1;
		अगर ((node->length - (temp_dword - node->base)) < alignment)
			जाओ error;

		node->length -= (temp_dword - node->base);
		node->base = temp_dword;
	पूर्ण

	अगर (node->length & (alignment - 1))
		/* There's stuff in use after this node */
		जाओ error;

	वापस node;
error:
	kमुक्त(node);
	वापस शून्य;
पूर्ण


/**
 * get_io_resource - find first node of given size not in ISA aliasing winकरोw.
 * @head: list to search
 * @size: size of node to find, must be a घातer of two.
 *
 * Description: This function sorts the resource list by size and then वापसs
 * वापसs the first node of "size" length that is not in the ISA aliasing
 * winकरोw.  If it finds a node larger than "size" it will split it up.
 */
अटल काष्ठा pci_resource *get_io_resource(काष्ठा pci_resource **head, u32 size)
अणु
	काष्ठा pci_resource *prevnode;
	काष्ठा pci_resource *node;
	काष्ठा pci_resource *split_node;
	u32 temp_dword;

	अगर (!(*head))
		वापस शून्य;

	अगर (cpqhp_resource_sort_and_combine(head))
		वापस शून्य;

	अगर (sort_by_size(head))
		वापस शून्य;

	क्रम (node = *head; node; node = node->next) अणु
		अगर (node->length < size)
			जारी;

		अगर (node->base & (size - 1)) अणु
			/* this one isn't base aligned properly
			 * so we'll make a new entry and split it up
			 */
			temp_dword = (node->base | (size-1)) + 1;

			/* Short circuit अगर adjusted size is too small */
			अगर ((node->length - (temp_dword - node->base)) < size)
				जारी;

			split_node = kदो_स्मृति(माप(*split_node), GFP_KERNEL);

			अगर (!split_node)
				वापस शून्य;

			split_node->base = node->base;
			split_node->length = temp_dword - node->base;
			node->base = temp_dword;
			node->length -= split_node->length;

			/* Put it in the list */
			split_node->next = node->next;
			node->next = split_node;
		पूर्ण /* End of non-aligned base */

		/* Don't need to check अगर too small since we alपढ़ोy did */
		अगर (node->length > size) अणु
			/* this one is दीर्घer than we need
			 * so we'll make a new entry and split it up
			 */
			split_node = kदो_स्मृति(माप(*split_node), GFP_KERNEL);

			अगर (!split_node)
				वापस शून्य;

			split_node->base = node->base + size;
			split_node->length = node->length - size;
			node->length = size;

			/* Put it in the list */
			split_node->next = node->next;
			node->next = split_node;
		पूर्ण  /* End of too big on top end */

		/* For IO make sure it's not in the ISA aliasing space */
		अगर (node->base & 0x300L)
			जारी;

		/* If we got here, then it is the right size
		 * Now take it out of the list and अवरोध
		 */
		अगर (*head == node) अणु
			*head = node->next;
		पूर्ण अन्यथा अणु
			prevnode = *head;
			जबतक (prevnode->next != node)
				prevnode = prevnode->next;

			prevnode->next = node->next;
		पूर्ण
		node->next = शून्य;
		अवरोध;
	पूर्ण

	वापस node;
पूर्ण


/**
 * get_max_resource - get largest node which has at least the given size.
 * @head: the list to search the node in
 * @size: the minimum size of the node to find
 *
 * Description: Gets the largest node that is at least "size" big from the
 * list poपूर्णांकed to by head.  It aligns the node on top and bottom
 * to "size" alignment beक्रमe वापसing it.
 */
अटल काष्ठा pci_resource *get_max_resource(काष्ठा pci_resource **head, u32 size)
अणु
	काष्ठा pci_resource *max;
	काष्ठा pci_resource *temp;
	काष्ठा pci_resource *split_node;
	u32 temp_dword;

	अगर (cpqhp_resource_sort_and_combine(head))
		वापस शून्य;

	अगर (sort_by_max_size(head))
		वापस शून्य;

	क्रम (max = *head; max; max = max->next) अणु
		/* If not big enough we could probably just bail,
		 * instead we'll जारी to the next.
		 */
		अगर (max->length < size)
			जारी;

		अगर (max->base & (size - 1)) अणु
			/* this one isn't base aligned properly
			 * so we'll make a new entry and split it up
			 */
			temp_dword = (max->base | (size-1)) + 1;

			/* Short circuit अगर adjusted size is too small */
			अगर ((max->length - (temp_dword - max->base)) < size)
				जारी;

			split_node = kदो_स्मृति(माप(*split_node), GFP_KERNEL);

			अगर (!split_node)
				वापस शून्य;

			split_node->base = max->base;
			split_node->length = temp_dword - max->base;
			max->base = temp_dword;
			max->length -= split_node->length;

			split_node->next = max->next;
			max->next = split_node;
		पूर्ण

		अगर ((max->base + max->length) & (size - 1)) अणु
			/* this one isn't end aligned properly at the top
			 * so we'll make a new entry and split it up
			 */
			split_node = kदो_स्मृति(माप(*split_node), GFP_KERNEL);

			अगर (!split_node)
				वापस शून्य;
			temp_dword = ((max->base + max->length) & ~(size - 1));
			split_node->base = temp_dword;
			split_node->length = max->length + max->base
					     - split_node->base;
			max->length -= split_node->length;

			split_node->next = max->next;
			max->next = split_node;
		पूर्ण

		/* Make sure it didn't shrink too much when we aligned it */
		अगर (max->length < size)
			जारी;

		/* Now take it out of the list */
		temp = *head;
		अगर (temp == max) अणु
			*head = max->next;
		पूर्ण अन्यथा अणु
			जबतक (temp && temp->next != max)
				temp = temp->next;

			अगर (temp)
				temp->next = max->next;
		पूर्ण

		max->next = शून्य;
		अवरोध;
	पूर्ण

	वापस max;
पूर्ण


/**
 * get_resource - find resource of given size and split up larger ones.
 * @head: the list to search क्रम resources
 * @size: the size limit to use
 *
 * Description: This function sorts the resource list by size and then
 * वापसs the first node of "size" length.  If it finds a node
 * larger than "size" it will split it up.
 *
 * size must be a घातer of two.
 */
अटल काष्ठा pci_resource *get_resource(काष्ठा pci_resource **head, u32 size)
अणु
	काष्ठा pci_resource *prevnode;
	काष्ठा pci_resource *node;
	काष्ठा pci_resource *split_node;
	u32 temp_dword;

	अगर (cpqhp_resource_sort_and_combine(head))
		वापस शून्य;

	अगर (sort_by_size(head))
		वापस शून्य;

	क्रम (node = *head; node; node = node->next) अणु
		dbg("%s: req_size =%x node=%p, base=%x, length=%x\n",
		    __func__, size, node, node->base, node->length);
		अगर (node->length < size)
			जारी;

		अगर (node->base & (size - 1)) अणु
			dbg("%s: not aligned\n", __func__);
			/* this one isn't base aligned properly
			 * so we'll make a new entry and split it up
			 */
			temp_dword = (node->base | (size-1)) + 1;

			/* Short circuit अगर adjusted size is too small */
			अगर ((node->length - (temp_dword - node->base)) < size)
				जारी;

			split_node = kदो_स्मृति(माप(*split_node), GFP_KERNEL);

			अगर (!split_node)
				वापस शून्य;

			split_node->base = node->base;
			split_node->length = temp_dword - node->base;
			node->base = temp_dword;
			node->length -= split_node->length;

			split_node->next = node->next;
			node->next = split_node;
		पूर्ण /* End of non-aligned base */

		/* Don't need to check अगर too small since we alपढ़ोy did */
		अगर (node->length > size) अणु
			dbg("%s: too big\n", __func__);
			/* this one is दीर्घer than we need
			 * so we'll make a new entry and split it up
			 */
			split_node = kदो_स्मृति(माप(*split_node), GFP_KERNEL);

			अगर (!split_node)
				वापस शून्य;

			split_node->base = node->base + size;
			split_node->length = node->length - size;
			node->length = size;

			/* Put it in the list */
			split_node->next = node->next;
			node->next = split_node;
		पूर्ण  /* End of too big on top end */

		dbg("%s: got one!!!\n", __func__);
		/* If we got here, then it is the right size
		 * Now take it out of the list */
		अगर (*head == node) अणु
			*head = node->next;
		पूर्ण अन्यथा अणु
			prevnode = *head;
			जबतक (prevnode->next != node)
				prevnode = prevnode->next;

			prevnode->next = node->next;
		पूर्ण
		node->next = शून्य;
		अवरोध;
	पूर्ण
	वापस node;
पूर्ण


/**
 * cpqhp_resource_sort_and_combine - sort nodes by base addresses and clean up
 * @head: the list to sort and clean up
 *
 * Description: Sorts all of the nodes in the list in ascending order by
 * their base addresses.  Also करोes garbage collection by
 * combining adjacent nodes.
 *
 * Returns %0 अगर success.
 */
पूर्णांक cpqhp_resource_sort_and_combine(काष्ठा pci_resource **head)
अणु
	काष्ठा pci_resource *node1;
	काष्ठा pci_resource *node2;
	पूर्णांक out_of_order = 1;

	dbg("%s: head = %p, *head = %p\n", __func__, head, *head);

	अगर (!(*head))
		वापस 1;

	dbg("*head->next = %p\n", (*head)->next);

	अगर (!(*head)->next)
		वापस 0;	/* only one item on the list, alपढ़ोy sorted! */

	dbg("*head->base = 0x%x\n", (*head)->base);
	dbg("*head->next->base = 0x%x\n", (*head)->next->base);
	जबतक (out_of_order) अणु
		out_of_order = 0;

		/* Special हाल क्रम swapping list head */
		अगर (((*head)->next) &&
		    ((*head)->base > (*head)->next->base)) अणु
			node1 = *head;
			(*head) = (*head)->next;
			node1->next = (*head)->next;
			(*head)->next = node1;
			out_of_order++;
		पूर्ण

		node1 = (*head);

		जबतक (node1->next && node1->next->next) अणु
			अगर (node1->next->base > node1->next->next->base) अणु
				out_of_order++;
				node2 = node1->next;
				node1->next = node1->next->next;
				node1 = node1->next;
				node2->next = node1->next;
				node1->next = node2;
			पूर्ण अन्यथा
				node1 = node1->next;
		पूर्ण
	पूर्ण  /* End of out_of_order loop */

	node1 = *head;

	जबतक (node1 && node1->next) अणु
		अगर ((node1->base + node1->length) == node1->next->base) अणु
			/* Combine */
			dbg("8..\n");
			node1->length += node1->next->length;
			node2 = node1->next;
			node1->next = node1->next->next;
			kमुक्त(node2);
		पूर्ण अन्यथा
			node1 = node1->next;
	पूर्ण

	वापस 0;
पूर्ण


irqवापस_t cpqhp_ctrl_पूर्णांकr(पूर्णांक IRQ, व्योम *data)
अणु
	काष्ठा controller *ctrl = data;
	u8 schedule_flag = 0;
	u8 reset;
	u16 misc;
	u32 Dअगरf;
	u32 temp_dword;


	misc = पढ़ोw(ctrl->hpc_reg + MISC);
	/*
	 * Check to see अगर it was our पूर्णांकerrupt
	 */
	अगर (!(misc & 0x000C))
		वापस IRQ_NONE;

	अगर (misc & 0x0004) अणु
		/*
		 * Serial Output पूर्णांकerrupt Pending
		 */

		/* Clear the पूर्णांकerrupt */
		misc |= 0x0004;
		ग_लिखोw(misc, ctrl->hpc_reg + MISC);

		/* Read to clear posted ग_लिखोs */
		misc = पढ़ोw(ctrl->hpc_reg + MISC);

		dbg("%s - waking up\n", __func__);
		wake_up_पूर्णांकerruptible(&ctrl->queue);
	पूर्ण

	अगर (misc & 0x0008) अणु
		/* General-पूर्णांकerrupt-input पूर्णांकerrupt Pending */
		Dअगरf = पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR) ^ ctrl->ctrl_पूर्णांक_comp;

		ctrl->ctrl_पूर्णांक_comp = पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR);

		/* Clear the पूर्णांकerrupt */
		ग_लिखोl(Dअगरf, ctrl->hpc_reg + INT_INPUT_CLEAR);

		/* Read it back to clear any posted ग_लिखोs */
		temp_dword = पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR);

		अगर (!Dअगरf)
			/* Clear all पूर्णांकerrupts */
			ग_लिखोl(0xFFFFFFFF, ctrl->hpc_reg + INT_INPUT_CLEAR);

		schedule_flag += handle_चयन_change((u8)(Dअगरf & 0xFFL), ctrl);
		schedule_flag += handle_presence_change((u16)((Dअगरf & 0xFFFF0000L) >> 16), ctrl);
		schedule_flag += handle_घातer_fault((u8)((Dअगरf & 0xFF00L) >> 8), ctrl);
	पूर्ण

	reset = पढ़ोb(ctrl->hpc_reg + RESET_FREQ_MODE);
	अगर (reset & 0x40) अणु
		/* Bus reset has completed */
		reset &= 0xCF;
		ग_लिखोb(reset, ctrl->hpc_reg + RESET_FREQ_MODE);
		reset = पढ़ोb(ctrl->hpc_reg + RESET_FREQ_MODE);
		wake_up_पूर्णांकerruptible(&ctrl->queue);
	पूर्ण

	अगर (schedule_flag) अणु
		wake_up_process(cpqhp_event_thपढ़ो);
		dbg("Waking even thread");
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


/**
 * cpqhp_slot_create - Creates a node and adds it to the proper bus.
 * @busnumber: bus where new node is to be located
 *
 * Returns poपूर्णांकer to the new node or %शून्य अगर unsuccessful.
 */
काष्ठा pci_func *cpqhp_slot_create(u8 busnumber)
अणु
	काष्ठा pci_func *new_slot;
	काष्ठा pci_func *next;

	new_slot = kzalloc(माप(*new_slot), GFP_KERNEL);
	अगर (new_slot == शून्य)
		वापस new_slot;

	new_slot->next = शून्य;
	new_slot->configured = 1;

	अगर (cpqhp_slot_list[busnumber] == शून्य) अणु
		cpqhp_slot_list[busnumber] = new_slot;
	पूर्ण अन्यथा अणु
		next = cpqhp_slot_list[busnumber];
		जबतक (next->next != शून्य)
			next = next->next;
		next->next = new_slot;
	पूर्ण
	वापस new_slot;
पूर्ण


/**
 * slot_हटाओ - Removes a node from the linked list of slots.
 * @old_slot: slot to हटाओ
 *
 * Returns %0 अगर successful, !0 otherwise.
 */
अटल पूर्णांक slot_हटाओ(काष्ठा pci_func *old_slot)
अणु
	काष्ठा pci_func *next;

	अगर (old_slot == शून्य)
		वापस 1;

	next = cpqhp_slot_list[old_slot->bus];
	अगर (next == शून्य)
		वापस 1;

	अगर (next == old_slot) अणु
		cpqhp_slot_list[old_slot->bus] = old_slot->next;
		cpqhp_destroy_board_resources(old_slot);
		kमुक्त(old_slot);
		वापस 0;
	पूर्ण

	जबतक ((next->next != old_slot) && (next->next != शून्य))
		next = next->next;

	अगर (next->next == old_slot) अणु
		next->next = old_slot->next;
		cpqhp_destroy_board_resources(old_slot);
		kमुक्त(old_slot);
		वापस 0;
	पूर्ण अन्यथा
		वापस 2;
पूर्ण


/**
 * bridge_slot_हटाओ - Removes a node from the linked list of slots.
 * @bridge: bridge to हटाओ
 *
 * Returns %0 अगर successful, !0 otherwise.
 */
अटल पूर्णांक bridge_slot_हटाओ(काष्ठा pci_func *bridge)
अणु
	u8 subordinateBus, secondaryBus;
	u8 tempBus;
	काष्ठा pci_func *next;

	secondaryBus = (bridge->config_space[0x06] >> 8) & 0xFF;
	subordinateBus = (bridge->config_space[0x06] >> 16) & 0xFF;

	क्रम (tempBus = secondaryBus; tempBus <= subordinateBus; tempBus++) अणु
		next = cpqhp_slot_list[tempBus];

		जबतक (!slot_हटाओ(next))
			next = cpqhp_slot_list[tempBus];
	पूर्ण

	next = cpqhp_slot_list[bridge->bus];

	अगर (next == शून्य)
		वापस 1;

	अगर (next == bridge) अणु
		cpqhp_slot_list[bridge->bus] = bridge->next;
		जाओ out;
	पूर्ण

	जबतक ((next->next != bridge) && (next->next != शून्य))
		next = next->next;

	अगर (next->next != bridge)
		वापस 2;
	next->next = bridge->next;
out:
	kमुक्त(bridge);
	वापस 0;
पूर्ण


/**
 * cpqhp_slot_find - Looks क्रम a node by bus, and device, multiple functions accessed
 * @bus: bus to find
 * @device: device to find
 * @index: is %0 क्रम first function found, %1 क्रम the second...
 *
 * Returns poपूर्णांकer to the node अगर successful, %शून्य otherwise.
 */
काष्ठा pci_func *cpqhp_slot_find(u8 bus, u8 device, u8 index)
अणु
	पूर्णांक found = -1;
	काष्ठा pci_func *func;

	func = cpqhp_slot_list[bus];

	अगर ((func == शून्य) || ((func->device == device) && (index == 0)))
		वापस func;

	अगर (func->device == device)
		found++;

	जबतक (func->next != शून्य) अणु
		func = func->next;

		अगर (func->device == device)
			found++;

		अगर (found == index)
			वापस func;
	पूर्ण

	वापस शून्य;
पूर्ण


/* DJZ: I करोn't think is_bridge will work as is.
 * FIXME */
अटल पूर्णांक is_bridge(काष्ठा pci_func *func)
अणु
	/* Check the header type */
	अगर (((func->config_space[0x03] >> 16) & 0xFF) == 0x01)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण


/**
 * set_controller_speed - set the frequency and/or mode of a specअगरic controller segment.
 * @ctrl: controller to change frequency/mode क्रम.
 * @adapter_speed: the speed of the adapter we want to match.
 * @hp_slot: the slot number where the adapter is installed.
 *
 * Returns %0 अगर we successfully change frequency and/or mode to match the
 * adapter speed.
 */
अटल u8 set_controller_speed(काष्ठा controller *ctrl, u8 adapter_speed, u8 hp_slot)
अणु
	काष्ठा slot *slot;
	काष्ठा pci_bus *bus = ctrl->pci_bus;
	u8 reg;
	u8 slot_घातer = पढ़ोb(ctrl->hpc_reg + SLOT_POWER);
	u16 reg16;
	u32 leds = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);

	अगर (bus->cur_bus_speed == adapter_speed)
		वापस 0;

	/* We करोn't allow freq/mode changes अगर we find another adapter running
	 * in another slot on this controller
	 */
	क्रम (slot = ctrl->slot; slot; slot = slot->next) अणु
		अगर (slot->device == (hp_slot + ctrl->slot_device_offset))
			जारी;
		अगर (get_presence_status(ctrl, slot) == 0)
			जारी;
		/* If another adapter is running on the same segment but at a
		 * lower speed/mode, we allow the new adapter to function at
		 * this rate अगर supported
		 */
		अगर (bus->cur_bus_speed < adapter_speed)
			वापस 0;

		वापस 1;
	पूर्ण

	/* If the controller करोesn't support freq/mode changes and the
	 * controller is running at a higher mode, we bail
	 */
	अगर ((bus->cur_bus_speed > adapter_speed) && (!ctrl->pcix_speed_capability))
		वापस 1;

	/* But we allow the adapter to run at a lower rate अगर possible */
	अगर ((bus->cur_bus_speed < adapter_speed) && (!ctrl->pcix_speed_capability))
		वापस 0;

	/* We try to set the max speed supported by both the adapter and
	 * controller
	 */
	अगर (bus->max_bus_speed < adapter_speed) अणु
		अगर (bus->cur_bus_speed == bus->max_bus_speed)
			वापस 0;
		adapter_speed = bus->max_bus_speed;
	पूर्ण

	ग_लिखोl(0x0L, ctrl->hpc_reg + LED_CONTROL);
	ग_लिखोb(0x00, ctrl->hpc_reg + SLOT_ENABLE);

	set_SOGO(ctrl);
	रुको_क्रम_ctrl_irq(ctrl);

	अगर (adapter_speed != PCI_SPEED_133MHz_PCIX)
		reg = 0xF5;
	अन्यथा
		reg = 0xF4;
	pci_ग_लिखो_config_byte(ctrl->pci_dev, 0x41, reg);

	reg16 = पढ़ोw(ctrl->hpc_reg + NEXT_CURR_FREQ);
	reg16 &= ~0x000F;
	चयन (adapter_speed) अणु
		हाल(PCI_SPEED_133MHz_PCIX):
			reg = 0x75;
			reg16 |= 0xB;
			अवरोध;
		हाल(PCI_SPEED_100MHz_PCIX):
			reg = 0x74;
			reg16 |= 0xA;
			अवरोध;
		हाल(PCI_SPEED_66MHz_PCIX):
			reg = 0x73;
			reg16 |= 0x9;
			अवरोध;
		हाल(PCI_SPEED_66MHz):
			reg = 0x73;
			reg16 |= 0x1;
			अवरोध;
		शेष: /* 33MHz PCI 2.2 */
			reg = 0x71;
			अवरोध;

	पूर्ण
	reg16 |= 0xB << 12;
	ग_लिखोw(reg16, ctrl->hpc_reg + NEXT_CURR_FREQ);

	mdelay(5);

	/* Reenable पूर्णांकerrupts */
	ग_लिखोl(0, ctrl->hpc_reg + INT_MASK);

	pci_ग_लिखो_config_byte(ctrl->pci_dev, 0x41, reg);

	/* Restart state machine */
	reg = ~0xF;
	pci_पढ़ो_config_byte(ctrl->pci_dev, 0x43, &reg);
	pci_ग_लिखो_config_byte(ctrl->pci_dev, 0x43, reg);

	/* Only अगर mode change...*/
	अगर (((bus->cur_bus_speed == PCI_SPEED_66MHz) && (adapter_speed == PCI_SPEED_66MHz_PCIX)) ||
		((bus->cur_bus_speed == PCI_SPEED_66MHz_PCIX) && (adapter_speed == PCI_SPEED_66MHz)))
			set_SOGO(ctrl);

	रुको_क्रम_ctrl_irq(ctrl);
	mdelay(1100);

	/* Restore LED/Slot state */
	ग_लिखोl(leds, ctrl->hpc_reg + LED_CONTROL);
	ग_लिखोb(slot_घातer, ctrl->hpc_reg + SLOT_ENABLE);

	set_SOGO(ctrl);
	रुको_क्रम_ctrl_irq(ctrl);

	bus->cur_bus_speed = adapter_speed;
	slot = cpqhp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);

	info("Successfully changed frequency/mode for adapter in slot %d\n",
			slot->number);
	वापस 0;
पूर्ण

/* the following routines स्थिरitute the bulk of the
 * hotplug controller logic
 */


/**
 * board_replaced - Called after a board has been replaced in the प्रणाली.
 * @func: PCI device/function inक्रमmation
 * @ctrl: hotplug controller
 *
 * This is only used अगर we करोn't have resources क्रम hot add.
 * Turns घातer on क्रम the board.
 * Checks to see अगर board is the same.
 * If board is same, reconfigures it.
 * If board isn't same, turns it back off.
 */
अटल u32 board_replaced(काष्ठा pci_func *func, काष्ठा controller *ctrl)
अणु
	काष्ठा pci_bus *bus = ctrl->pci_bus;
	u8 hp_slot;
	u8 temp_byte;
	u8 adapter_speed;
	u32 rc = 0;

	hp_slot = func->device - ctrl->slot_device_offset;

	/*
	 * The चयन is खोलो.
	 */
	अगर (पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR) & (0x01L << hp_slot))
		rc = INTERLOCK_OPEN;
	/*
	 * The board is alपढ़ोy on
	 */
	अन्यथा अगर (is_slot_enabled(ctrl, hp_slot))
		rc = CARD_FUNCTIONING;
	अन्यथा अणु
		mutex_lock(&ctrl->crit_sect);

		/* turn on board without attaching to the bus */
		enable_slot_घातer(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);

		/* Change bits in slot घातer रेजिस्टर to क्रमce another shअगरt out
		 * NOTE: this is to work around the समयr bug */
		temp_byte = पढ़ोb(ctrl->hpc_reg + SLOT_POWER);
		ग_लिखोb(0x00, ctrl->hpc_reg + SLOT_POWER);
		ग_लिखोb(temp_byte, ctrl->hpc_reg + SLOT_POWER);

		set_SOGO(ctrl);

		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);

		adapter_speed = get_adapter_speed(ctrl, hp_slot);
		अगर (bus->cur_bus_speed != adapter_speed)
			अगर (set_controller_speed(ctrl, adapter_speed, hp_slot))
				rc = WRONG_BUS_FREQUENCY;

		/* turn off board without attaching to the bus */
		disable_slot_घातer(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);

		mutex_unlock(&ctrl->crit_sect);

		अगर (rc)
			वापस rc;

		mutex_lock(&ctrl->crit_sect);

		slot_enable(ctrl, hp_slot);
		green_LED_blink(ctrl, hp_slot);

		amber_LED_off(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);

		mutex_unlock(&ctrl->crit_sect);

		/* Wait क्रम ~1 second because of hot plug spec */
		दीर्घ_delay(1*HZ);

		/* Check क्रम a घातer fault */
		अगर (func->status == 0xFF) अणु
			/* घातer fault occurred, but it was benign */
			rc = POWER_FAILURE;
			func->status = 0;
		पूर्ण अन्यथा
			rc = cpqhp_valid_replace(ctrl, func);

		अगर (!rc) अणु
			/* It must be the same board */

			rc = cpqhp_configure_board(ctrl, func);

			/* If configuration fails, turn it off
			 * Get slot won't work क्रम devices behind
			 * bridges, but in this हाल it will always be
			 * called क्रम the "base" bus/dev/func of an
			 * adapter.
			 */

			mutex_lock(&ctrl->crit_sect);

			amber_LED_on(ctrl, hp_slot);
			green_LED_off(ctrl, hp_slot);
			slot_disable(ctrl, hp_slot);

			set_SOGO(ctrl);

			/* Wait क्रम SOBS to be unset */
			रुको_क्रम_ctrl_irq(ctrl);

			mutex_unlock(&ctrl->crit_sect);

			अगर (rc)
				वापस rc;
			अन्यथा
				वापस 1;

		पूर्ण अन्यथा अणु
			/* Something is wrong

			 * Get slot won't work क्रम devices behind bridges, but
			 * in this हाल it will always be called क्रम the "base"
			 * bus/dev/func of an adapter.
			 */

			mutex_lock(&ctrl->crit_sect);

			amber_LED_on(ctrl, hp_slot);
			green_LED_off(ctrl, hp_slot);
			slot_disable(ctrl, hp_slot);

			set_SOGO(ctrl);

			/* Wait क्रम SOBS to be unset */
			रुको_क्रम_ctrl_irq(ctrl);

			mutex_unlock(&ctrl->crit_sect);
		पूर्ण

	पूर्ण
	वापस rc;

पूर्ण


/**
 * board_added - Called after a board has been added to the प्रणाली.
 * @func: PCI device/function info
 * @ctrl: hotplug controller
 *
 * Turns घातer on क्रम the board.
 * Configures board.
 */
अटल u32 board_added(काष्ठा pci_func *func, काष्ठा controller *ctrl)
अणु
	u8 hp_slot;
	u8 temp_byte;
	u8 adapter_speed;
	पूर्णांक index;
	u32 temp_रेजिस्टर = 0xFFFFFFFF;
	u32 rc = 0;
	काष्ठा pci_func *new_slot = शून्य;
	काष्ठा pci_bus *bus = ctrl->pci_bus;
	काष्ठा slot *p_slot;
	काष्ठा resource_lists res_lists;

	hp_slot = func->device - ctrl->slot_device_offset;
	dbg("%s: func->device, slot_offset, hp_slot = %d, %d ,%d\n",
	    __func__, func->device, ctrl->slot_device_offset, hp_slot);

	mutex_lock(&ctrl->crit_sect);

	/* turn on board without attaching to the bus */
	enable_slot_घातer(ctrl, hp_slot);

	set_SOGO(ctrl);

	/* Wait क्रम SOBS to be unset */
	रुको_क्रम_ctrl_irq(ctrl);

	/* Change bits in slot घातer रेजिस्टर to क्रमce another shअगरt out
	 * NOTE: this is to work around the समयr bug
	 */
	temp_byte = पढ़ोb(ctrl->hpc_reg + SLOT_POWER);
	ग_लिखोb(0x00, ctrl->hpc_reg + SLOT_POWER);
	ग_लिखोb(temp_byte, ctrl->hpc_reg + SLOT_POWER);

	set_SOGO(ctrl);

	/* Wait क्रम SOBS to be unset */
	रुको_क्रम_ctrl_irq(ctrl);

	adapter_speed = get_adapter_speed(ctrl, hp_slot);
	अगर (bus->cur_bus_speed != adapter_speed)
		अगर (set_controller_speed(ctrl, adapter_speed, hp_slot))
			rc = WRONG_BUS_FREQUENCY;

	/* turn off board without attaching to the bus */
	disable_slot_घातer(ctrl, hp_slot);

	set_SOGO(ctrl);

	/* Wait क्रम SOBS to be unset */
	रुको_क्रम_ctrl_irq(ctrl);

	mutex_unlock(&ctrl->crit_sect);

	अगर (rc)
		वापस rc;

	p_slot = cpqhp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);

	/* turn on board and blink green LED */

	dbg("%s: before down\n", __func__);
	mutex_lock(&ctrl->crit_sect);
	dbg("%s: after down\n", __func__);

	dbg("%s: before slot_enable\n", __func__);
	slot_enable(ctrl, hp_slot);

	dbg("%s: before green_LED_blink\n", __func__);
	green_LED_blink(ctrl, hp_slot);

	dbg("%s: before amber_LED_blink\n", __func__);
	amber_LED_off(ctrl, hp_slot);

	dbg("%s: before set_SOGO\n", __func__);
	set_SOGO(ctrl);

	/* Wait क्रम SOBS to be unset */
	dbg("%s: before wait_for_ctrl_irq\n", __func__);
	रुको_क्रम_ctrl_irq(ctrl);
	dbg("%s: after wait_for_ctrl_irq\n", __func__);

	dbg("%s: before up\n", __func__);
	mutex_unlock(&ctrl->crit_sect);
	dbg("%s: after up\n", __func__);

	/* Wait क्रम ~1 second because of hot plug spec */
	dbg("%s: before long_delay\n", __func__);
	दीर्घ_delay(1*HZ);
	dbg("%s: after long_delay\n", __func__);

	dbg("%s: func status = %x\n", __func__, func->status);
	/* Check क्रम a घातer fault */
	अगर (func->status == 0xFF) अणु
		/* घातer fault occurred, but it was benign */
		temp_रेजिस्टर = 0xFFFFFFFF;
		dbg("%s: temp register set to %x by power fault\n", __func__, temp_रेजिस्टर);
		rc = POWER_FAILURE;
		func->status = 0;
	पूर्ण अन्यथा अणु
		/* Get venकरोr/device ID u32 */
		ctrl->pci_bus->number = func->bus;
		rc = pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(func->device, func->function), PCI_VENDOR_ID, &temp_रेजिस्टर);
		dbg("%s: pci_read_config_dword returns %d\n", __func__, rc);
		dbg("%s: temp_register is %x\n", __func__, temp_रेजिस्टर);

		अगर (rc != 0) अणु
			/* Something's wrong here */
			temp_रेजिस्टर = 0xFFFFFFFF;
			dbg("%s: temp register set to %x by error\n", __func__, temp_रेजिस्टर);
		पूर्ण
		/* Preset वापस code.  It will be changed later अगर things go okay. */
		rc = NO_ADAPTER_PRESENT;
	पूर्ण

	/* All F's is an empty slot or an invalid board */
	अगर (temp_रेजिस्टर != 0xFFFFFFFF) अणु
		res_lists.io_head = ctrl->io_head;
		res_lists.mem_head = ctrl->mem_head;
		res_lists.p_mem_head = ctrl->p_mem_head;
		res_lists.bus_head = ctrl->bus_head;
		res_lists.irqs = शून्य;

		rc = configure_new_device(ctrl, func, 0, &res_lists);

		dbg("%s: back from configure_new_device\n", __func__);
		ctrl->io_head = res_lists.io_head;
		ctrl->mem_head = res_lists.mem_head;
		ctrl->p_mem_head = res_lists.p_mem_head;
		ctrl->bus_head = res_lists.bus_head;

		cpqhp_resource_sort_and_combine(&(ctrl->mem_head));
		cpqhp_resource_sort_and_combine(&(ctrl->p_mem_head));
		cpqhp_resource_sort_and_combine(&(ctrl->io_head));
		cpqhp_resource_sort_and_combine(&(ctrl->bus_head));

		अगर (rc) अणु
			mutex_lock(&ctrl->crit_sect);

			amber_LED_on(ctrl, hp_slot);
			green_LED_off(ctrl, hp_slot);
			slot_disable(ctrl, hp_slot);

			set_SOGO(ctrl);

			/* Wait क्रम SOBS to be unset */
			रुको_क्रम_ctrl_irq(ctrl);

			mutex_unlock(&ctrl->crit_sect);
			वापस rc;
		पूर्ण अन्यथा अणु
			cpqhp_save_slot_config(ctrl, func);
		पूर्ण


		func->status = 0;
		func->चयन_save = 0x10;
		func->is_a_board = 0x01;

		/* next, we will instantiate the linux pci_dev काष्ठाures (with
		 * appropriate driver notअगरication, अगर alपढ़ोy present) */
		dbg("%s: configure linux pci_dev structure\n", __func__);
		index = 0;
		करो अणु
			new_slot = cpqhp_slot_find(ctrl->bus, func->device, index++);
			अगर (new_slot && !new_slot->pci_dev)
				cpqhp_configure_device(ctrl, new_slot);
		पूर्ण जबतक (new_slot);

		mutex_lock(&ctrl->crit_sect);

		green_LED_on(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);

		mutex_unlock(&ctrl->crit_sect);
	पूर्ण अन्यथा अणु
		mutex_lock(&ctrl->crit_sect);

		amber_LED_on(ctrl, hp_slot);
		green_LED_off(ctrl, hp_slot);
		slot_disable(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);

		mutex_unlock(&ctrl->crit_sect);

		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण


/**
 * हटाओ_board - Turns off slot and LEDs
 * @func: PCI device/function info
 * @replace_flag: whether replacing or adding a new device
 * @ctrl: target controller
 */
अटल u32 हटाओ_board(काष्ठा pci_func *func, u32 replace_flag, काष्ठा controller *ctrl)
अणु
	पूर्णांक index;
	u8 skip = 0;
	u8 device;
	u8 hp_slot;
	u8 temp_byte;
	u32 rc;
	काष्ठा resource_lists res_lists;
	काष्ठा pci_func *temp_func;

	अगर (cpqhp_unconfigure_device(func))
		वापस 1;

	device = func->device;

	hp_slot = func->device - ctrl->slot_device_offset;
	dbg("In %s, hp_slot = %d\n", __func__, hp_slot);

	/* When we get here, it is safe to change base address रेजिस्टरs.
	 * We will attempt to save the base address रेजिस्टर lengths */
	अगर (replace_flag || !ctrl->add_support)
		rc = cpqhp_save_base_addr_length(ctrl, func);
	अन्यथा अगर (!func->bus_head && !func->mem_head &&
		 !func->p_mem_head && !func->io_head) अणु
		/* Here we check to see अगर we've saved any of the board's
		 * resources alपढ़ोy.  If so, we'll skip the attempt to
		 * determine what's being used. */
		index = 0;
		temp_func = cpqhp_slot_find(func->bus, func->device, index++);
		जबतक (temp_func) अणु
			अगर (temp_func->bus_head || temp_func->mem_head
			    || temp_func->p_mem_head || temp_func->io_head) अणु
				skip = 1;
				अवरोध;
			पूर्ण
			temp_func = cpqhp_slot_find(temp_func->bus, temp_func->device, index++);
		पूर्ण

		अगर (!skip)
			rc = cpqhp_save_used_resources(ctrl, func);
	पूर्ण
	/* Change status to shutकरोwn */
	अगर (func->is_a_board)
		func->status = 0x01;
	func->configured = 0;

	mutex_lock(&ctrl->crit_sect);

	green_LED_off(ctrl, hp_slot);
	slot_disable(ctrl, hp_slot);

	set_SOGO(ctrl);

	/* turn off SERR क्रम slot */
	temp_byte = पढ़ोb(ctrl->hpc_reg + SLOT_SERR);
	temp_byte &= ~(0x01 << hp_slot);
	ग_लिखोb(temp_byte, ctrl->hpc_reg + SLOT_SERR);

	/* Wait क्रम SOBS to be unset */
	रुको_क्रम_ctrl_irq(ctrl);

	mutex_unlock(&ctrl->crit_sect);

	अगर (!replace_flag && ctrl->add_support) अणु
		जबतक (func) अणु
			res_lists.io_head = ctrl->io_head;
			res_lists.mem_head = ctrl->mem_head;
			res_lists.p_mem_head = ctrl->p_mem_head;
			res_lists.bus_head = ctrl->bus_head;

			cpqhp_वापस_board_resources(func, &res_lists);

			ctrl->io_head = res_lists.io_head;
			ctrl->mem_head = res_lists.mem_head;
			ctrl->p_mem_head = res_lists.p_mem_head;
			ctrl->bus_head = res_lists.bus_head;

			cpqhp_resource_sort_and_combine(&(ctrl->mem_head));
			cpqhp_resource_sort_and_combine(&(ctrl->p_mem_head));
			cpqhp_resource_sort_and_combine(&(ctrl->io_head));
			cpqhp_resource_sort_and_combine(&(ctrl->bus_head));

			अगर (is_bridge(func)) अणु
				bridge_slot_हटाओ(func);
			पूर्ण अन्यथा
				slot_हटाओ(func);

			func = cpqhp_slot_find(ctrl->bus, device, 0);
		पूर्ण

		/* Setup slot काष्ठाure with entry क्रम empty slot */
		func = cpqhp_slot_create(ctrl->bus);

		अगर (func == शून्य)
			वापस 1;

		func->bus = ctrl->bus;
		func->device = device;
		func->function = 0;
		func->configured = 0;
		func->चयन_save = 0x10;
		func->is_a_board = 0;
		func->p_task_event = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pushbutton_helper_thपढ़ो(काष्ठा समयr_list *t)
अणु
	pushbutton_pending = t;

	wake_up_process(cpqhp_event_thपढ़ो);
पूर्ण


/* this is the मुख्य worker thपढ़ो */
अटल पूर्णांक event_thपढ़ो(व्योम *data)
अणु
	काष्ठा controller *ctrl;

	जबतक (1) अणु
		dbg("!!!!event_thread sleeping\n");
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();

		अगर (kthपढ़ो_should_stop())
			अवरोध;
		/* Do stuff here */
		अगर (pushbutton_pending)
			cpqhp_pushbutton_thपढ़ो(pushbutton_pending);
		अन्यथा
			क्रम (ctrl = cpqhp_ctrl_list; ctrl; ctrl = ctrl->next)
				पूर्णांकerrupt_event_handler(ctrl);
	पूर्ण
	dbg("event_thread signals exit\n");
	वापस 0;
पूर्ण

पूर्णांक cpqhp_event_start_thपढ़ो(व्योम)
अणु
	cpqhp_event_thपढ़ो = kthपढ़ो_run(event_thपढ़ो, शून्य, "phpd_event");
	अगर (IS_ERR(cpqhp_event_thपढ़ो)) अणु
		err("Can't start up our event thread\n");
		वापस PTR_ERR(cpqhp_event_thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण


व्योम cpqhp_event_stop_thपढ़ो(व्योम)
अणु
	kthपढ़ो_stop(cpqhp_event_thपढ़ो);
पूर्ण


अटल व्योम पूर्णांकerrupt_event_handler(काष्ठा controller *ctrl)
अणु
	पूर्णांक loop = 0;
	पूर्णांक change = 1;
	काष्ठा pci_func *func;
	u8 hp_slot;
	काष्ठा slot *p_slot;

	जबतक (change) अणु
		change = 0;

		क्रम (loop = 0; loop < 10; loop++) अणु
			/* dbg("loop %d\n", loop); */
			अगर (ctrl->event_queue[loop].event_type != 0) अणु
				hp_slot = ctrl->event_queue[loop].hp_slot;

				func = cpqhp_slot_find(ctrl->bus, (hp_slot + ctrl->slot_device_offset), 0);
				अगर (!func)
					वापस;

				p_slot = cpqhp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);
				अगर (!p_slot)
					वापस;

				dbg("hp_slot %d, func %p, p_slot %p\n",
				    hp_slot, func, p_slot);

				अगर (ctrl->event_queue[loop].event_type == INT_BUTTON_PRESS) अणु
					dbg("button pressed\n");
				पूर्ण अन्यथा अगर (ctrl->event_queue[loop].event_type ==
					   INT_BUTTON_CANCEL) अणु
					dbg("button cancel\n");
					del_समयr(&p_slot->task_event);

					mutex_lock(&ctrl->crit_sect);

					अगर (p_slot->state == BLINKINGOFF_STATE) अणु
						/* slot is on */
						dbg("turn on green LED\n");
						green_LED_on(ctrl, hp_slot);
					पूर्ण अन्यथा अगर (p_slot->state == BLINKINGON_STATE) अणु
						/* slot is off */
						dbg("turn off green LED\n");
						green_LED_off(ctrl, hp_slot);
					पूर्ण

					info(msg_button_cancel, p_slot->number);

					p_slot->state = STATIC_STATE;

					amber_LED_off(ctrl, hp_slot);

					set_SOGO(ctrl);

					/* Wait क्रम SOBS to be unset */
					रुको_क्रम_ctrl_irq(ctrl);

					mutex_unlock(&ctrl->crit_sect);
				पूर्ण
				/*** button Released (No action on press...) */
				अन्यथा अगर (ctrl->event_queue[loop].event_type == INT_BUTTON_RELEASE) अणु
					dbg("button release\n");

					अगर (is_slot_enabled(ctrl, hp_slot)) अणु
						dbg("slot is on\n");
						p_slot->state = BLINKINGOFF_STATE;
						info(msg_button_off, p_slot->number);
					पूर्ण अन्यथा अणु
						dbg("slot is off\n");
						p_slot->state = BLINKINGON_STATE;
						info(msg_button_on, p_slot->number);
					पूर्ण
					mutex_lock(&ctrl->crit_sect);

					dbg("blink green LED and turn off amber\n");

					amber_LED_off(ctrl, hp_slot);
					green_LED_blink(ctrl, hp_slot);

					set_SOGO(ctrl);

					/* Wait क्रम SOBS to be unset */
					रुको_क्रम_ctrl_irq(ctrl);

					mutex_unlock(&ctrl->crit_sect);
					समयr_setup(&p_slot->task_event,
						    pushbutton_helper_thपढ़ो,
						    0);
					p_slot->hp_slot = hp_slot;
					p_slot->ctrl = ctrl;
/*					p_slot->physical_slot = physical_slot; */
					p_slot->task_event.expires = jअगरfies + 5 * HZ;   /* 5 second delay */

					dbg("add_timer p_slot = %p\n", p_slot);
					add_समयr(&p_slot->task_event);
				पूर्ण
				/***********POWER FAULT */
				अन्यथा अगर (ctrl->event_queue[loop].event_type == INT_POWER_FAULT) अणु
					dbg("power fault\n");
				पूर्ण

				ctrl->event_queue[loop].event_type = 0;

				change = 1;
			पूर्ण
		पूर्ण		/* End of FOR loop */
	पूर्ण
पूर्ण


/**
 * cpqhp_pushbutton_thपढ़ो - handle pushbutton events
 * @slot: target slot (काष्ठा)
 *
 * Scheduled procedure to handle blocking stuff क्रम the pushbuttons.
 * Handles all pending events and निकासs.
 */
व्योम cpqhp_pushbutton_thपढ़ो(काष्ठा समयr_list *t)
अणु
	u8 hp_slot;
	u8 device;
	काष्ठा pci_func *func;
	काष्ठा slot *p_slot = from_समयr(p_slot, t, task_event);
	काष्ठा controller *ctrl = (काष्ठा controller *) p_slot->ctrl;

	pushbutton_pending = शून्य;
	hp_slot = p_slot->hp_slot;

	device = p_slot->device;

	अगर (is_slot_enabled(ctrl, hp_slot)) अणु
		p_slot->state = POWEROFF_STATE;
		/* घातer Down board */
		func = cpqhp_slot_find(p_slot->bus, p_slot->device, 0);
		dbg("In power_down_board, func = %p, ctrl = %p\n", func, ctrl);
		अगर (!func) अणु
			dbg("Error! func NULL in %s\n", __func__);
			वापस;
		पूर्ण

		अगर (cpqhp_process_SS(ctrl, func) != 0) अणु
			amber_LED_on(ctrl, hp_slot);
			green_LED_on(ctrl, hp_slot);

			set_SOGO(ctrl);

			/* Wait क्रम SOBS to be unset */
			रुको_क्रम_ctrl_irq(ctrl);
		पूर्ण

		p_slot->state = STATIC_STATE;
	पूर्ण अन्यथा अणु
		p_slot->state = POWERON_STATE;
		/* slot is off */

		func = cpqhp_slot_find(p_slot->bus, p_slot->device, 0);
		dbg("In add_board, func = %p, ctrl = %p\n", func, ctrl);
		अगर (!func) अणु
			dbg("Error! func NULL in %s\n", __func__);
			वापस;
		पूर्ण

		अगर (ctrl != शून्य) अणु
			अगर (cpqhp_process_SI(ctrl, func) != 0) अणु
				amber_LED_on(ctrl, hp_slot);
				green_LED_off(ctrl, hp_slot);

				set_SOGO(ctrl);

				/* Wait क्रम SOBS to be unset */
				रुको_क्रम_ctrl_irq(ctrl);
			पूर्ण
		पूर्ण

		p_slot->state = STATIC_STATE;
	पूर्ण
पूर्ण


पूर्णांक cpqhp_process_SI(काष्ठा controller *ctrl, काष्ठा pci_func *func)
अणु
	u8 device, hp_slot;
	u16 temp_word;
	u32 tempdword;
	पूर्णांक rc;
	काष्ठा slot *p_slot;
	पूर्णांक physical_slot = 0;

	tempdword = 0;

	device = func->device;
	hp_slot = device - ctrl->slot_device_offset;
	p_slot = cpqhp_find_slot(ctrl, device);
	अगर (p_slot)
		physical_slot = p_slot->number;

	/* Check to see अगर the पूर्णांकerlock is बंदd */
	tempdword = पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR);

	अगर (tempdword & (0x01 << hp_slot))
		वापस 1;

	अगर (func->is_a_board) अणु
		rc = board_replaced(func, ctrl);
	पूर्ण अन्यथा अणु
		/* add board */
		slot_हटाओ(func);

		func = cpqhp_slot_create(ctrl->bus);
		अगर (func == शून्य)
			वापस 1;

		func->bus = ctrl->bus;
		func->device = device;
		func->function = 0;
		func->configured = 0;
		func->is_a_board = 1;

		/* We have to save the presence info क्रम these slots */
		temp_word = ctrl->ctrl_पूर्णांक_comp >> 16;
		func->presence_save = (temp_word >> hp_slot) & 0x01;
		func->presence_save |= (temp_word >> (hp_slot + 7)) & 0x02;

		अगर (ctrl->ctrl_पूर्णांक_comp & (0x1L << hp_slot)) अणु
			func->चयन_save = 0;
		पूर्ण अन्यथा अणु
			func->चयन_save = 0x10;
		पूर्ण

		rc = board_added(func, ctrl);
		अगर (rc) अणु
			अगर (is_bridge(func)) अणु
				bridge_slot_हटाओ(func);
			पूर्ण अन्यथा
				slot_हटाओ(func);

			/* Setup slot काष्ठाure with entry क्रम empty slot */
			func = cpqhp_slot_create(ctrl->bus);

			अगर (func == शून्य)
				वापस 1;

			func->bus = ctrl->bus;
			func->device = device;
			func->function = 0;
			func->configured = 0;
			func->is_a_board = 0;

			/* We have to save the presence info क्रम these slots */
			temp_word = ctrl->ctrl_पूर्णांक_comp >> 16;
			func->presence_save = (temp_word >> hp_slot) & 0x01;
			func->presence_save |=
			(temp_word >> (hp_slot + 7)) & 0x02;

			अगर (ctrl->ctrl_पूर्णांक_comp & (0x1L << hp_slot)) अणु
				func->चयन_save = 0;
			पूर्ण अन्यथा अणु
				func->चयन_save = 0x10;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rc)
		dbg("%s: rc = %d\n", __func__, rc);

	वापस rc;
पूर्ण


पूर्णांक cpqhp_process_SS(काष्ठा controller *ctrl, काष्ठा pci_func *func)
अणु
	u8 device, class_code, header_type, BCR;
	u8 index = 0;
	u8 replace_flag;
	u32 rc = 0;
	अचिन्हित पूर्णांक devfn;
	काष्ठा slot *p_slot;
	काष्ठा pci_bus *pci_bus = ctrl->pci_bus;
	पूर्णांक physical_slot = 0;

	device = func->device;
	func = cpqhp_slot_find(ctrl->bus, device, index++);
	p_slot = cpqhp_find_slot(ctrl, device);
	अगर (p_slot)
		physical_slot = p_slot->number;

	/* Make sure there are no video controllers here */
	जबतक (func && !rc) अणु
		pci_bus->number = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		/* Check the Class Code */
		rc = pci_bus_पढ़ो_config_byte(pci_bus, devfn, 0x0B, &class_code);
		अगर (rc)
			वापस rc;

		अगर (class_code == PCI_BASE_CLASS_DISPLAY) अणु
			/* Display/Video adapter (not supported) */
			rc = REMOVE_NOT_SUPPORTED;
		पूर्ण अन्यथा अणु
			/* See अगर it's a bridge */
			rc = pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_HEADER_TYPE, &header_type);
			अगर (rc)
				वापस rc;

			/* If it's a bridge, check the VGA Enable bit */
			अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
				rc = pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_BRIDGE_CONTROL, &BCR);
				अगर (rc)
					वापस rc;

				/* If the VGA Enable bit is set, हटाओ isn't
				 * supported */
				अगर (BCR & PCI_BRIDGE_CTL_VGA)
					rc = REMOVE_NOT_SUPPORTED;
			पूर्ण
		पूर्ण

		func = cpqhp_slot_find(ctrl->bus, device, index++);
	पूर्ण

	func = cpqhp_slot_find(ctrl->bus, device, 0);
	अगर ((func != शून्य) && !rc) अणु
		/* FIXME: Replace flag should be passed पूर्णांकo process_SS */
		replace_flag = !(ctrl->add_support);
		rc = हटाओ_board(func, replace_flag, ctrl);
	पूर्ण अन्यथा अगर (!rc) अणु
		rc = 1;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * चयन_leds - चयन the leds, go from one site to the other.
 * @ctrl: controller to use
 * @num_of_slots: number of slots to use
 * @work_LED: LED control value
 * @direction: 1 to start from the left side, 0 to start right.
 */
अटल व्योम चयन_leds(काष्ठा controller *ctrl, स्थिर पूर्णांक num_of_slots,
			u32 *work_LED, स्थिर पूर्णांक direction)
अणु
	पूर्णांक loop;

	क्रम (loop = 0; loop < num_of_slots; loop++) अणु
		अगर (direction)
			*work_LED = *work_LED >> 1;
		अन्यथा
			*work_LED = *work_LED << 1;
		ग_लिखोl(*work_LED, ctrl->hpc_reg + LED_CONTROL);

		set_SOGO(ctrl);

		/* Wait क्रम SOGO पूर्णांकerrupt */
		रुको_क्रम_ctrl_irq(ctrl);

		/* Get पढ़ोy क्रम next iteration */
		दीर्घ_delay((2*HZ)/10);
	पूर्ण
पूर्ण

/**
 * cpqhp_hardware_test - runs hardware tests
 * @ctrl: target controller
 * @test_num: the number written to the "test" file in sysfs.
 *
 * For hot plug ctrl folks to play with.
 */
पूर्णांक cpqhp_hardware_test(काष्ठा controller *ctrl, पूर्णांक test_num)
अणु
	u32 save_LED;
	u32 work_LED;
	पूर्णांक loop;
	पूर्णांक num_of_slots;

	num_of_slots = पढ़ोb(ctrl->hpc_reg + SLOT_MASK) & 0x0f;

	चयन (test_num) अणु
	हाल 1:
		/* Do stuff here! */

		/* Do that funky LED thing */
		/* so we can restore them later */
		save_LED = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);
		work_LED = 0x01010101;
		चयन_leds(ctrl, num_of_slots, &work_LED, 0);
		चयन_leds(ctrl, num_of_slots, &work_LED, 1);
		चयन_leds(ctrl, num_of_slots, &work_LED, 0);
		चयन_leds(ctrl, num_of_slots, &work_LED, 1);

		work_LED = 0x01010000;
		ग_लिखोl(work_LED, ctrl->hpc_reg + LED_CONTROL);
		चयन_leds(ctrl, num_of_slots, &work_LED, 0);
		चयन_leds(ctrl, num_of_slots, &work_LED, 1);
		work_LED = 0x00000101;
		ग_लिखोl(work_LED, ctrl->hpc_reg + LED_CONTROL);
		चयन_leds(ctrl, num_of_slots, &work_LED, 0);
		चयन_leds(ctrl, num_of_slots, &work_LED, 1);

		work_LED = 0x01010000;
		ग_लिखोl(work_LED, ctrl->hpc_reg + LED_CONTROL);
		क्रम (loop = 0; loop < num_of_slots; loop++) अणु
			set_SOGO(ctrl);

			/* Wait क्रम SOGO पूर्णांकerrupt */
			रुको_क्रम_ctrl_irq(ctrl);

			/* Get पढ़ोy क्रम next iteration */
			दीर्घ_delay((3*HZ)/10);
			work_LED = work_LED >> 16;
			ग_लिखोl(work_LED, ctrl->hpc_reg + LED_CONTROL);

			set_SOGO(ctrl);

			/* Wait क्रम SOGO पूर्णांकerrupt */
			रुको_क्रम_ctrl_irq(ctrl);

			/* Get पढ़ोy क्रम next iteration */
			दीर्घ_delay((3*HZ)/10);
			work_LED = work_LED << 16;
			ग_लिखोl(work_LED, ctrl->hpc_reg + LED_CONTROL);
			work_LED = work_LED << 1;
			ग_लिखोl(work_LED, ctrl->hpc_reg + LED_CONTROL);
		पूर्ण

		/* put it back the way it was */
		ग_लिखोl(save_LED, ctrl->hpc_reg + LED_CONTROL);

		set_SOGO(ctrl);

		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);
		अवरोध;
	हाल 2:
		/* Do other stuff here! */
		अवरोध;
	हाल 3:
		/* and more... */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


/**
 * configure_new_device - Configures the PCI header inक्रमmation of one board.
 * @ctrl: poपूर्णांकer to controller काष्ठाure
 * @func: poपूर्णांकer to function काष्ठाure
 * @behind_bridge: 1 अगर this is a recursive call, 0 अगर not
 * @resources: poपूर्णांकer to set of resource lists
 *
 * Returns 0 अगर success.
 */
अटल u32 configure_new_device(काष्ठा controller  *ctrl, काष्ठा pci_func  *func,
				 u8 behind_bridge, काष्ठा resource_lists  *resources)
अणु
	u8 temp_byte, function, max_functions, stop_it;
	पूर्णांक rc;
	u32 ID;
	काष्ठा pci_func *new_slot;
	पूर्णांक index;

	new_slot = func;

	dbg("%s\n", __func__);
	/* Check क्रम Multi-function device */
	ctrl->pci_bus->number = func->bus;
	rc = pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(func->device, func->function), 0x0E, &temp_byte);
	अगर (rc) अणु
		dbg("%s: rc = %d\n", __func__, rc);
		वापस rc;
	पूर्ण

	अगर (temp_byte & 0x80)	/* Multi-function device */
		max_functions = 8;
	अन्यथा
		max_functions = 1;

	function = 0;

	करो अणु
		rc = configure_new_function(ctrl, new_slot, behind_bridge, resources);

		अगर (rc) अणु
			dbg("configure_new_function failed %d\n", rc);
			index = 0;

			जबतक (new_slot) अणु
				new_slot = cpqhp_slot_find(new_slot->bus, new_slot->device, index++);

				अगर (new_slot)
					cpqhp_वापस_board_resources(new_slot, resources);
			पूर्ण

			वापस rc;
		पूर्ण

		function++;

		stop_it = 0;

		/* The following loop skips to the next present function
		 * and creates a board काष्ठाure */

		जबतक ((function < max_functions) && (!stop_it)) अणु
			pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(func->device, function), 0x00, &ID);

			अगर (ID == 0xFFFFFFFF) अणु
				function++;
			पूर्ण अन्यथा अणु
				/* Setup slot काष्ठाure. */
				new_slot = cpqhp_slot_create(func->bus);

				अगर (new_slot == शून्य)
					वापस 1;

				new_slot->bus = func->bus;
				new_slot->device = func->device;
				new_slot->function = function;
				new_slot->is_a_board = 1;
				new_slot->status = 0;

				stop_it++;
			पूर्ण
		पूर्ण

	पूर्ण जबतक (function < max_functions);
	dbg("returning from configure_new_device\n");

	वापस 0;
पूर्ण


/*
 * Configuration logic that involves the hotplug data काष्ठाures and
 * their bookkeeping
 */


/**
 * configure_new_function - Configures the PCI header inक्रमmation of one device
 * @ctrl: poपूर्णांकer to controller काष्ठाure
 * @func: poपूर्णांकer to function काष्ठाure
 * @behind_bridge: 1 अगर this is a recursive call, 0 अगर not
 * @resources: poपूर्णांकer to set of resource lists
 *
 * Calls itself recursively क्रम bridged devices.
 * Returns 0 अगर success.
 */
अटल पूर्णांक configure_new_function(काष्ठा controller *ctrl, काष्ठा pci_func *func,
				   u8 behind_bridge,
				   काष्ठा resource_lists *resources)
अणु
	पूर्णांक cloop;
	u8 IRQ = 0;
	u8 temp_byte;
	u8 device;
	u8 class_code;
	u16 command;
	u16 temp_word;
	u32 temp_dword;
	u32 rc;
	u32 temp_रेजिस्टर;
	u32 base;
	u32 ID;
	अचिन्हित पूर्णांक devfn;
	काष्ठा pci_resource *mem_node;
	काष्ठा pci_resource *p_mem_node;
	काष्ठा pci_resource *io_node;
	काष्ठा pci_resource *bus_node;
	काष्ठा pci_resource *hold_mem_node;
	काष्ठा pci_resource *hold_p_mem_node;
	काष्ठा pci_resource *hold_IO_node;
	काष्ठा pci_resource *hold_bus_node;
	काष्ठा irq_mapping irqs;
	काष्ठा pci_func *new_slot;
	काष्ठा pci_bus *pci_bus;
	काष्ठा resource_lists temp_resources;

	pci_bus = ctrl->pci_bus;
	pci_bus->number = func->bus;
	devfn = PCI_DEVFN(func->device, func->function);

	/* Check क्रम Bridge */
	rc = pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_HEADER_TYPE, &temp_byte);
	अगर (rc)
		वापस rc;

	अगर ((temp_byte & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
		/* set Primary bus */
		dbg("set Primary bus = %d\n", func->bus);
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_PRIMARY_BUS, func->bus);
		अगर (rc)
			वापस rc;

		/* find range of buses to use */
		dbg("find ranges of buses to use\n");
		bus_node = get_max_resource(&(resources->bus_head), 1);

		/* If we करोn't have any buses to allocate, we can't जारी */
		अगर (!bus_node)
			वापस -ENOMEM;

		/* set Secondary bus */
		temp_byte = bus_node->base;
		dbg("set Secondary bus = %d\n", bus_node->base);
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_SECONDARY_BUS, temp_byte);
		अगर (rc)
			वापस rc;

		/* set subordinate bus */
		temp_byte = bus_node->base + bus_node->length - 1;
		dbg("set subordinate bus = %d\n", bus_node->base + bus_node->length - 1);
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_SUBORDINATE_BUS, temp_byte);
		अगर (rc)
			वापस rc;

		/* set subordinate Latency Timer and base Latency Timer */
		temp_byte = 0x40;
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_SEC_LATENCY_TIMER, temp_byte);
		अगर (rc)
			वापस rc;
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_LATENCY_TIMER, temp_byte);
		अगर (rc)
			वापस rc;

		/* set Cache Line size */
		temp_byte = 0x08;
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_CACHE_LINE_SIZE, temp_byte);
		अगर (rc)
			वापस rc;

		/* Setup the IO, memory, and prefetchable winकरोws */
		io_node = get_max_resource(&(resources->io_head), 0x1000);
		अगर (!io_node)
			वापस -ENOMEM;
		mem_node = get_max_resource(&(resources->mem_head), 0x100000);
		अगर (!mem_node)
			वापस -ENOMEM;
		p_mem_node = get_max_resource(&(resources->p_mem_head), 0x100000);
		अगर (!p_mem_node)
			वापस -ENOMEM;
		dbg("Setup the IO, memory, and prefetchable windows\n");
		dbg("io_node\n");
		dbg("(base, len, next) (%x, %x, %p)\n", io_node->base,
					io_node->length, io_node->next);
		dbg("mem_node\n");
		dbg("(base, len, next) (%x, %x, %p)\n", mem_node->base,
					mem_node->length, mem_node->next);
		dbg("p_mem_node\n");
		dbg("(base, len, next) (%x, %x, %p)\n", p_mem_node->base,
					p_mem_node->length, p_mem_node->next);

		/* set up the IRQ info */
		अगर (!resources->irqs) अणु
			irqs.barber_pole = 0;
			irqs.पूर्णांकerrupt[0] = 0;
			irqs.पूर्णांकerrupt[1] = 0;
			irqs.पूर्णांकerrupt[2] = 0;
			irqs.पूर्णांकerrupt[3] = 0;
			irqs.valid_INT = 0;
		पूर्ण अन्यथा अणु
			irqs.barber_pole = resources->irqs->barber_pole;
			irqs.पूर्णांकerrupt[0] = resources->irqs->पूर्णांकerrupt[0];
			irqs.पूर्णांकerrupt[1] = resources->irqs->पूर्णांकerrupt[1];
			irqs.पूर्णांकerrupt[2] = resources->irqs->पूर्णांकerrupt[2];
			irqs.पूर्णांकerrupt[3] = resources->irqs->पूर्णांकerrupt[3];
			irqs.valid_INT = resources->irqs->valid_INT;
		पूर्ण

		/* set up resource lists that are now aligned on top and bottom
		 * क्रम anything behind the bridge. */
		temp_resources.bus_head = bus_node;
		temp_resources.io_head = io_node;
		temp_resources.mem_head = mem_node;
		temp_resources.p_mem_head = p_mem_node;
		temp_resources.irqs = &irqs;

		/* Make copies of the nodes we are going to pass करोwn so that
		 * अगर there is a problem,we can just use these to मुक्त resources
		 */
		hold_bus_node = kदो_स्मृति(माप(*hold_bus_node), GFP_KERNEL);
		hold_IO_node = kदो_स्मृति(माप(*hold_IO_node), GFP_KERNEL);
		hold_mem_node = kदो_स्मृति(माप(*hold_mem_node), GFP_KERNEL);
		hold_p_mem_node = kदो_स्मृति(माप(*hold_p_mem_node), GFP_KERNEL);

		अगर (!hold_bus_node || !hold_IO_node || !hold_mem_node || !hold_p_mem_node) अणु
			kमुक्त(hold_bus_node);
			kमुक्त(hold_IO_node);
			kमुक्त(hold_mem_node);
			kमुक्त(hold_p_mem_node);

			वापस 1;
		पूर्ण

		स_नकल(hold_bus_node, bus_node, माप(काष्ठा pci_resource));

		bus_node->base += 1;
		bus_node->length -= 1;
		bus_node->next = शून्य;

		/* If we have IO resources copy them and fill in the bridge's
		 * IO range रेजिस्टरs */
		स_नकल(hold_IO_node, io_node, माप(काष्ठा pci_resource));
		io_node->next = शून्य;

		/* set IO base and Limit रेजिस्टरs */
		temp_byte = io_node->base >> 8;
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_IO_BASE, temp_byte);

		temp_byte = (io_node->base + io_node->length - 1) >> 8;
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_IO_LIMIT, temp_byte);

		/* Copy the memory resources and fill in the bridge's memory
		 * range रेजिस्टरs.
		 */
		स_नकल(hold_mem_node, mem_node, माप(काष्ठा pci_resource));
		mem_node->next = शून्य;

		/* set Mem base and Limit रेजिस्टरs */
		temp_word = mem_node->base >> 16;
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_MEMORY_BASE, temp_word);

		temp_word = (mem_node->base + mem_node->length - 1) >> 16;
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_MEMORY_LIMIT, temp_word);

		स_नकल(hold_p_mem_node, p_mem_node, माप(काष्ठा pci_resource));
		p_mem_node->next = शून्य;

		/* set Pre Mem base and Limit रेजिस्टरs */
		temp_word = p_mem_node->base >> 16;
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_PREF_MEMORY_BASE, temp_word);

		temp_word = (p_mem_node->base + p_mem_node->length - 1) >> 16;
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, temp_word);

		/* Adjust this to compensate क्रम extra adjusपंचांगent in first loop
		 */
		irqs.barber_pole--;

		rc = 0;

		/* Here we actually find the devices and configure them */
		क्रम (device = 0; (device <= 0x1F) && !rc; device++) अणु
			irqs.barber_pole = (irqs.barber_pole + 1) & 0x03;

			ID = 0xFFFFFFFF;
			pci_bus->number = hold_bus_node->base;
			pci_bus_पढ़ो_config_dword(pci_bus, PCI_DEVFN(device, 0), 0x00, &ID);
			pci_bus->number = func->bus;

			अगर (ID != 0xFFFFFFFF) अणु	  /*  device present */
				/* Setup slot काष्ठाure. */
				new_slot = cpqhp_slot_create(hold_bus_node->base);

				अगर (new_slot == शून्य) अणु
					rc = -ENOMEM;
					जारी;
				पूर्ण

				new_slot->bus = hold_bus_node->base;
				new_slot->device = device;
				new_slot->function = 0;
				new_slot->is_a_board = 1;
				new_slot->status = 0;

				rc = configure_new_device(ctrl, new_slot, 1, &temp_resources);
				dbg("configure_new_device rc=0x%x\n", rc);
			पूर्ण	/* End of IF (device in slot?) */
		पूर्ण		/* End of FOR loop */

		अगर (rc)
			जाओ मुक्त_and_out;
		/* save the पूर्णांकerrupt routing inक्रमmation */
		अगर (resources->irqs) अणु
			resources->irqs->पूर्णांकerrupt[0] = irqs.पूर्णांकerrupt[0];
			resources->irqs->पूर्णांकerrupt[1] = irqs.पूर्णांकerrupt[1];
			resources->irqs->पूर्णांकerrupt[2] = irqs.पूर्णांकerrupt[2];
			resources->irqs->पूर्णांकerrupt[3] = irqs.पूर्णांकerrupt[3];
			resources->irqs->valid_INT = irqs.valid_INT;
		पूर्ण अन्यथा अगर (!behind_bridge) अणु
			/* We need to hook up the पूर्णांकerrupts here */
			क्रम (cloop = 0; cloop < 4; cloop++) अणु
				अगर (irqs.valid_INT & (0x01 << cloop)) अणु
					rc = cpqhp_set_irq(func->bus, func->device,
							   cloop + 1, irqs.पूर्णांकerrupt[cloop]);
					अगर (rc)
						जाओ मुक्त_and_out;
				पूर्ण
			पूर्ण	/* end of क्रम loop */
		पूर्ण
		/* Return unused bus resources
		 * First use the temporary node to store inक्रमmation क्रम
		 * the board */
		अगर (bus_node && temp_resources.bus_head) अणु
			hold_bus_node->length = bus_node->base - hold_bus_node->base;

			hold_bus_node->next = func->bus_head;
			func->bus_head = hold_bus_node;

			temp_byte = temp_resources.bus_head->base - 1;

			/* set subordinate bus */
			rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_SUBORDINATE_BUS, temp_byte);

			अगर (temp_resources.bus_head->length == 0) अणु
				kमुक्त(temp_resources.bus_head);
				temp_resources.bus_head = शून्य;
			पूर्ण अन्यथा अणु
				वापस_resource(&(resources->bus_head), temp_resources.bus_head);
			पूर्ण
		पूर्ण

		/* If we have IO space available and there is some left,
		 * वापस the unused portion */
		अगर (hold_IO_node && temp_resources.io_head) अणु
			io_node = करो_pre_bridge_resource_split(&(temp_resources.io_head),
							       &hold_IO_node, 0x1000);

			/* Check अगर we were able to split something off */
			अगर (io_node) अणु
				hold_IO_node->base = io_node->base + io_node->length;

				temp_byte = (hold_IO_node->base) >> 8;
				rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_IO_BASE, temp_byte);

				वापस_resource(&(resources->io_head), io_node);
			पूर्ण

			io_node = करो_bridge_resource_split(&(temp_resources.io_head), 0x1000);

			/* Check अगर we were able to split something off */
			अगर (io_node) अणु
				/* First use the temporary node to store
				 * inक्रमmation क्रम the board */
				hold_IO_node->length = io_node->base - hold_IO_node->base;

				/* If we used any, add it to the board's list */
				अगर (hold_IO_node->length) अणु
					hold_IO_node->next = func->io_head;
					func->io_head = hold_IO_node;

					temp_byte = (io_node->base - 1) >> 8;
					rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_IO_LIMIT, temp_byte);

					वापस_resource(&(resources->io_head), io_node);
				पूर्ण अन्यथा अणु
					/* it करोesn't need any IO */
					temp_word = 0x0000;
					rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_IO_LIMIT, temp_word);

					वापस_resource(&(resources->io_head), io_node);
					kमुक्त(hold_IO_node);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* it used most of the range */
				hold_IO_node->next = func->io_head;
				func->io_head = hold_IO_node;
			पूर्ण
		पूर्ण अन्यथा अगर (hold_IO_node) अणु
			/* it used the whole range */
			hold_IO_node->next = func->io_head;
			func->io_head = hold_IO_node;
		पूर्ण
		/* If we have memory space available and there is some left,
		 * वापस the unused portion */
		अगर (hold_mem_node && temp_resources.mem_head) अणु
			mem_node = करो_pre_bridge_resource_split(&(temp_resources.  mem_head),
								&hold_mem_node, 0x100000);

			/* Check अगर we were able to split something off */
			अगर (mem_node) अणु
				hold_mem_node->base = mem_node->base + mem_node->length;

				temp_word = (hold_mem_node->base) >> 16;
				rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_MEMORY_BASE, temp_word);

				वापस_resource(&(resources->mem_head), mem_node);
			पूर्ण

			mem_node = करो_bridge_resource_split(&(temp_resources.mem_head), 0x100000);

			/* Check अगर we were able to split something off */
			अगर (mem_node) अणु
				/* First use the temporary node to store
				 * inक्रमmation क्रम the board */
				hold_mem_node->length = mem_node->base - hold_mem_node->base;

				अगर (hold_mem_node->length) अणु
					hold_mem_node->next = func->mem_head;
					func->mem_head = hold_mem_node;

					/* configure end address */
					temp_word = (mem_node->base - 1) >> 16;
					rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_MEMORY_LIMIT, temp_word);

					/* Return unused resources to the pool */
					वापस_resource(&(resources->mem_head), mem_node);
				पूर्ण अन्यथा अणु
					/* it करोesn't need any Mem */
					temp_word = 0x0000;
					rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_MEMORY_LIMIT, temp_word);

					वापस_resource(&(resources->mem_head), mem_node);
					kमुक्त(hold_mem_node);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* it used most of the range */
				hold_mem_node->next = func->mem_head;
				func->mem_head = hold_mem_node;
			पूर्ण
		पूर्ण अन्यथा अगर (hold_mem_node) अणु
			/* it used the whole range */
			hold_mem_node->next = func->mem_head;
			func->mem_head = hold_mem_node;
		पूर्ण
		/* If we have prefetchable memory space available and there
		 * is some left at the end, वापस the unused portion */
		अगर (temp_resources.p_mem_head) अणु
			p_mem_node = करो_pre_bridge_resource_split(&(temp_resources.p_mem_head),
								  &hold_p_mem_node, 0x100000);

			/* Check अगर we were able to split something off */
			अगर (p_mem_node) अणु
				hold_p_mem_node->base = p_mem_node->base + p_mem_node->length;

				temp_word = (hold_p_mem_node->base) >> 16;
				rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_PREF_MEMORY_BASE, temp_word);

				वापस_resource(&(resources->p_mem_head), p_mem_node);
			पूर्ण

			p_mem_node = करो_bridge_resource_split(&(temp_resources.p_mem_head), 0x100000);

			/* Check अगर we were able to split something off */
			अगर (p_mem_node) अणु
				/* First use the temporary node to store
				 * inक्रमmation क्रम the board */
				hold_p_mem_node->length = p_mem_node->base - hold_p_mem_node->base;

				/* If we used any, add it to the board's list */
				अगर (hold_p_mem_node->length) अणु
					hold_p_mem_node->next = func->p_mem_head;
					func->p_mem_head = hold_p_mem_node;

					temp_word = (p_mem_node->base - 1) >> 16;
					rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, temp_word);

					वापस_resource(&(resources->p_mem_head), p_mem_node);
				पूर्ण अन्यथा अणु
					/* it करोesn't need any PMem */
					temp_word = 0x0000;
					rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, temp_word);

					वापस_resource(&(resources->p_mem_head), p_mem_node);
					kमुक्त(hold_p_mem_node);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* it used the most of the range */
				hold_p_mem_node->next = func->p_mem_head;
				func->p_mem_head = hold_p_mem_node;
			पूर्ण
		पूर्ण अन्यथा अगर (hold_p_mem_node) अणु
			/* it used the whole range */
			hold_p_mem_node->next = func->p_mem_head;
			func->p_mem_head = hold_p_mem_node;
		पूर्ण
		/* We should be configuring an IRQ and the bridge's base address
		 * रेजिस्टरs अगर it needs them.  Although we have never seen such
		 * a device */

		/* enable card */
		command = 0x0157;	/* = PCI_COMMAND_IO |
					 *   PCI_COMMAND_MEMORY |
					 *   PCI_COMMAND_MASTER |
					 *   PCI_COMMAND_INVALIDATE |
					 *   PCI_COMMAND_PARITY |
					 *   PCI_COMMAND_SERR */
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_COMMAND, command);

		/* set Bridge Control Register */
		command = 0x07;		/* = PCI_BRIDGE_CTL_PARITY |
					 *   PCI_BRIDGE_CTL_SERR |
					 *   PCI_BRIDGE_CTL_NO_ISA */
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_BRIDGE_CONTROL, command);
	पूर्ण अन्यथा अगर ((temp_byte & 0x7F) == PCI_HEADER_TYPE_NORMAL) अणु
		/* Standard device */
		rc = pci_bus_पढ़ो_config_byte(pci_bus, devfn, 0x0B, &class_code);

		अगर (class_code == PCI_BASE_CLASS_DISPLAY) अणु
			/* Display (video) adapter (not supported) */
			वापस DEVICE_TYPE_NOT_SUPPORTED;
		पूर्ण
		/* Figure out IO and memory needs */
		क्रम (cloop = 0x10; cloop <= 0x24; cloop += 4) अणु
			temp_रेजिस्टर = 0xFFFFFFFF;

			dbg("CND: bus=%d, devfn=%d, offset=%d\n", pci_bus->number, devfn, cloop);
			rc = pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, temp_रेजिस्टर);

			rc = pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &temp_रेजिस्टर);
			dbg("CND: base = 0x%x\n", temp_रेजिस्टर);

			अगर (temp_रेजिस्टर) अणु	  /* If this रेजिस्टर is implemented */
				अगर ((temp_रेजिस्टर & 0x03L) == 0x01) अणु
					/* Map IO */

					/* set base = amount of IO space */
					base = temp_रेजिस्टर & 0xFFFFFFFC;
					base = ~base + 1;

					dbg("CND:      length = 0x%x\n", base);
					io_node = get_io_resource(&(resources->io_head), base);
					अगर (!io_node)
						वापस -ENOMEM;
					dbg("Got io_node start = %8.8x, length = %8.8x next (%p)\n",
					    io_node->base, io_node->length, io_node->next);
					dbg("func (%p) io_head (%p)\n", func, func->io_head);

					/* allocate the resource to the board */
					base = io_node->base;
					io_node->next = func->io_head;
					func->io_head = io_node;
				पूर्ण अन्यथा अगर ((temp_रेजिस्टर & 0x0BL) == 0x08) अणु
					/* Map prefetchable memory */
					base = temp_रेजिस्टर & 0xFFFFFFF0;
					base = ~base + 1;

					dbg("CND:      length = 0x%x\n", base);
					p_mem_node = get_resource(&(resources->p_mem_head), base);

					/* allocate the resource to the board */
					अगर (p_mem_node) अणु
						base = p_mem_node->base;

						p_mem_node->next = func->p_mem_head;
						func->p_mem_head = p_mem_node;
					पूर्ण अन्यथा
						वापस -ENOMEM;
				पूर्ण अन्यथा अगर ((temp_रेजिस्टर & 0x0BL) == 0x00) अणु
					/* Map memory */
					base = temp_रेजिस्टर & 0xFFFFFFF0;
					base = ~base + 1;

					dbg("CND:      length = 0x%x\n", base);
					mem_node = get_resource(&(resources->mem_head), base);

					/* allocate the resource to the board */
					अगर (mem_node) अणु
						base = mem_node->base;

						mem_node->next = func->mem_head;
						func->mem_head = mem_node;
					पूर्ण अन्यथा
						वापस -ENOMEM;
				पूर्ण अन्यथा अणु
					/* Reserved bits or requesting space below 1M */
					वापस NOT_ENOUGH_RESOURCES;
				पूर्ण

				rc = pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, base);

				/* Check क्रम 64-bit base */
				अगर ((temp_रेजिस्टर & 0x07L) == 0x04) अणु
					cloop += 4;

					/* Upper 32 bits of address always zero
					 * on today's प्रणालीs */
					/* FIXME this is probably not true on
					 * Alpha and ia64??? */
					base = 0;
					rc = pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, base);
				पूर्ण
			पूर्ण
		पूर्ण		/* End of base रेजिस्टर loop */
		अगर (cpqhp_legacy_mode) अणु
			/* Figure out which पूर्णांकerrupt pin this function uses */
			rc = pci_bus_पढ़ो_config_byte(pci_bus, devfn,
				PCI_INTERRUPT_PIN, &temp_byte);

			/* If this function needs an पूर्णांकerrupt and we are behind
			 * a bridge and the pin is tied to something that's
			 * alपढ़ोy mapped, set this one the same */
			अगर (temp_byte && resources->irqs &&
			    (resources->irqs->valid_INT &
			     (0x01 << ((temp_byte + resources->irqs->barber_pole - 1) & 0x03)))) अणु
				/* We have to share with something alपढ़ोy set up */
				IRQ = resources->irqs->पूर्णांकerrupt[(temp_byte +
					resources->irqs->barber_pole - 1) & 0x03];
			पूर्ण अन्यथा अणु
				/* Program IRQ based on card type */
				rc = pci_bus_पढ़ो_config_byte(pci_bus, devfn, 0x0B, &class_code);

				अगर (class_code == PCI_BASE_CLASS_STORAGE)
					IRQ = cpqhp_disk_irq;
				अन्यथा
					IRQ = cpqhp_nic_irq;
			पूर्ण

			/* IRQ Line */
			rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn, PCI_INTERRUPT_LINE, IRQ);
		पूर्ण

		अगर (!behind_bridge) अणु
			rc = cpqhp_set_irq(func->bus, func->device, temp_byte, IRQ);
			अगर (rc)
				वापस 1;
		पूर्ण अन्यथा अणु
			/* TBD - this code may also beदीर्घ in the other clause
			 * of this If statement */
			resources->irqs->पूर्णांकerrupt[(temp_byte + resources->irqs->barber_pole - 1) & 0x03] = IRQ;
			resources->irqs->valid_INT |= 0x01 << (temp_byte + resources->irqs->barber_pole - 1) & 0x03;
		पूर्ण

		/* Latency Timer */
		temp_byte = 0x40;
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn,
					PCI_LATENCY_TIMER, temp_byte);

		/* Cache Line size */
		temp_byte = 0x08;
		rc = pci_bus_ग_लिखो_config_byte(pci_bus, devfn,
					PCI_CACHE_LINE_SIZE, temp_byte);

		/* disable ROM base Address */
		temp_dword = 0x00L;
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn,
					PCI_ROM_ADDRESS, temp_dword);

		/* enable card */
		temp_word = 0x0157;	/* = PCI_COMMAND_IO |
					 *   PCI_COMMAND_MEMORY |
					 *   PCI_COMMAND_MASTER |
					 *   PCI_COMMAND_INVALIDATE |
					 *   PCI_COMMAND_PARITY |
					 *   PCI_COMMAND_SERR */
		rc = pci_bus_ग_लिखो_config_word(pci_bus, devfn,
					PCI_COMMAND, temp_word);
	पूर्ण अन्यथा अणु		/* End of Not-A-Bridge अन्यथा */
		/* It's some strange type of PCI adapter (Cardbus?) */
		वापस DEVICE_TYPE_NOT_SUPPORTED;
	पूर्ण

	func->configured = 1;

	वापस 0;
मुक्त_and_out:
	cpqhp_destroy_resource_list(&temp_resources);

	वापस_resource(&(resources->bus_head), hold_bus_node);
	वापस_resource(&(resources->io_head), hold_IO_node);
	वापस_resource(&(resources->mem_head), hold_mem_node);
	वापस_resource(&(resources->p_mem_head), hold_p_mem_node);
	वापस rc;
पूर्ण
