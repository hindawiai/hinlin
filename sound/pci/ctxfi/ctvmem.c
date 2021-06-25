<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File    ctvmem.c
 *
 * @Brief
 * This file contains the implementation of भव memory management object
 * क्रम card device.
 *
 * @Author Liu Chun
 * @Date Apr 1 2008
 */

#समावेश "ctvmem.h"
#समावेश "ctatc.h"
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <sound/pcm.h>

#घोषणा CT_PTES_PER_PAGE (CT_PAGE_SIZE / माप(व्योम *))
#घोषणा CT_ADDRS_PER_PAGE (CT_PTES_PER_PAGE * CT_PAGE_SIZE)

/* *
 * Find or create vm block based on requested @size.
 * @size must be page aligned.
 * */
अटल काष्ठा ct_vm_block *
get_vm_block(काष्ठा ct_vm *vm, अचिन्हित पूर्णांक size, काष्ठा ct_atc *atc)
अणु
	काष्ठा ct_vm_block *block = शून्य, *entry;
	काष्ठा list_head *pos;

	size = CT_PAGE_ALIGN(size);
	अगर (size > vm->size) अणु
		dev_err(atc->card->dev,
			"Fail! No sufficient device virtual memory space available!\n");
		वापस शून्य;
	पूर्ण

	mutex_lock(&vm->lock);
	list_क्रम_each(pos, &vm->unused) अणु
		entry = list_entry(pos, काष्ठा ct_vm_block, list);
		अगर (entry->size >= size)
			अवरोध; /* found a block that is big enough */
	पूर्ण
	अगर (pos == &vm->unused)
		जाओ out;

	अगर (entry->size == size) अणु
		/* Move the vm node from unused list to used list directly */
		list_move(&entry->list, &vm->used);
		vm->size -= size;
		block = entry;
		जाओ out;
	पूर्ण

	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (!block)
		जाओ out;

	block->addr = entry->addr;
	block->size = size;
	list_add(&block->list, &vm->used);
	entry->addr += size;
	entry->size -= size;
	vm->size -= size;

 out:
	mutex_unlock(&vm->lock);
	वापस block;
पूर्ण

अटल व्योम put_vm_block(काष्ठा ct_vm *vm, काष्ठा ct_vm_block *block)
अणु
	काष्ठा ct_vm_block *entry, *pre_ent;
	काष्ठा list_head *pos, *pre;

	block->size = CT_PAGE_ALIGN(block->size);

	mutex_lock(&vm->lock);
	list_del(&block->list);
	vm->size += block->size;

	list_क्रम_each(pos, &vm->unused) अणु
		entry = list_entry(pos, काष्ठा ct_vm_block, list);
		अगर (entry->addr >= (block->addr + block->size))
			अवरोध; /* found a position */
	पूर्ण
	अगर (pos == &vm->unused) अणु
		list_add_tail(&block->list, &vm->unused);
		entry = block;
	पूर्ण अन्यथा अणु
		अगर ((block->addr + block->size) == entry->addr) अणु
			entry->addr = block->addr;
			entry->size += block->size;
			kमुक्त(block);
		पूर्ण अन्यथा अणु
			__list_add(&block->list, pos->prev, pos);
			entry = block;
		पूर्ण
	पूर्ण

	pos = &entry->list;
	pre = pos->prev;
	जबतक (pre != &vm->unused) अणु
		entry = list_entry(pos, काष्ठा ct_vm_block, list);
		pre_ent = list_entry(pre, काष्ठा ct_vm_block, list);
		अगर ((pre_ent->addr + pre_ent->size) > entry->addr)
			अवरोध;

		pre_ent->size += entry->size;
		list_del(pos);
		kमुक्त(entry);
		pos = pre;
		pre = pos->prev;
	पूर्ण
	mutex_unlock(&vm->lock);
पूर्ण

/* Map host addr (kदो_स्मृतिed/vदो_स्मृतिed) to device logical addr. */
अटल काष्ठा ct_vm_block *
ct_vm_map(काष्ठा ct_vm *vm, काष्ठा snd_pcm_substream *substream, पूर्णांक size)
अणु
	काष्ठा ct_vm_block *block;
	अचिन्हित पूर्णांक pte_start;
	अचिन्हित i, pages;
	अचिन्हित दीर्घ *ptp;
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);

	block = get_vm_block(vm, size, atc);
	अगर (block == शून्य) अणु
		dev_err(atc->card->dev,
			"No virtual memory block that is big enough to allocate!\n");
		वापस शून्य;
	पूर्ण

	ptp = (अचिन्हित दीर्घ *)vm->ptp[0].area;
	pte_start = (block->addr >> CT_PAGE_SHIFT);
	pages = block->size >> CT_PAGE_SHIFT;
	क्रम (i = 0; i < pages; i++) अणु
		अचिन्हित दीर्घ addr;
		addr = snd_pcm_sgbuf_get_addr(substream, i << CT_PAGE_SHIFT);
		ptp[pte_start + i] = addr;
	पूर्ण

	block->size = size;
	वापस block;
पूर्ण

अटल व्योम ct_vm_unmap(काष्ठा ct_vm *vm, काष्ठा ct_vm_block *block)
अणु
	/* करो unmapping */
	put_vm_block(vm, block);
पूर्ण

/* *
 * वापस the host physical addr of the @index-th device
 * page table page on success, or ~0UL on failure.
 * The first वापसed ~0UL indicates the termination.
 * */
अटल dma_addr_t
ct_get_ptp_phys(काष्ठा ct_vm *vm, पूर्णांक index)
अणु
	वापस (index >= CT_PTP_NUM) ? ~0UL : vm->ptp[index].addr;
पूर्ण

पूर्णांक ct_vm_create(काष्ठा ct_vm **rvm, काष्ठा pci_dev *pci)
अणु
	काष्ठा ct_vm *vm;
	काष्ठा ct_vm_block *block;
	पूर्णांक i, err = 0;

	*rvm = शून्य;

	vm = kzalloc(माप(*vm), GFP_KERNEL);
	अगर (!vm)
		वापस -ENOMEM;

	mutex_init(&vm->lock);

	/* Allocate page table pages */
	क्रम (i = 0; i < CT_PTP_NUM; i++) अणु
		err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
					  &pci->dev,
					  PAGE_SIZE, &vm->ptp[i]);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	अगर (err < 0) अणु
		/* no page table pages are allocated */
		ct_vm_destroy(vm);
		वापस -ENOMEM;
	पूर्ण
	vm->size = CT_ADDRS_PER_PAGE * i;
	vm->map = ct_vm_map;
	vm->unmap = ct_vm_unmap;
	vm->get_ptp_phys = ct_get_ptp_phys;
	INIT_LIST_HEAD(&vm->unused);
	INIT_LIST_HEAD(&vm->used);
	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (शून्य != block) अणु
		block->addr = 0;
		block->size = vm->size;
		list_add(&block->list, &vm->unused);
	पूर्ण

	*rvm = vm;
	वापस 0;
पूर्ण

/* The caller must ensure no mapping pages are being used
 * by hardware beक्रमe calling this function */
व्योम ct_vm_destroy(काष्ठा ct_vm *vm)
अणु
	पूर्णांक i;
	काष्ठा list_head *pos;
	काष्ठा ct_vm_block *entry;

	/* मुक्त used and unused list nodes */
	जबतक (!list_empty(&vm->used)) अणु
		pos = vm->used.next;
		list_del(pos);
		entry = list_entry(pos, काष्ठा ct_vm_block, list);
		kमुक्त(entry);
	पूर्ण
	जबतक (!list_empty(&vm->unused)) अणु
		pos = vm->unused.next;
		list_del(pos);
		entry = list_entry(pos, काष्ठा ct_vm_block, list);
		kमुक्त(entry);
	पूर्ण

	/* मुक्त allocated page table pages */
	क्रम (i = 0; i < CT_PTP_NUM; i++)
		snd_dma_मुक्त_pages(&vm->ptp[i]);

	vm->size = 0;

	kमुक्त(vm);
पूर्ण
