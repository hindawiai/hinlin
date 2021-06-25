<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File    ctvस्मृति.स
 *
 * @Brief
 * This file contains the definition of भव memory management object
 * क्रम card device.
 *
 * @Author Liu Chun
 * @Date Mar 28 2008
 */

#अगर_अघोषित CTVMEM_H
#घोषणा CTVMEM_H

#घोषणा CT_PTP_NUM	4	/* num of device page table pages */

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <sound/meदो_स्मृति.h>

/* The chip can handle the page table of 4k pages
 * (emu20k1 can handle even 8k pages, but we करोn't use it right now)
 */
#घोषणा CT_PAGE_SIZE	4096
#घोषणा CT_PAGE_SHIFT	12
#घोषणा CT_PAGE_MASK	(~(PAGE_SIZE - 1))
#घोषणा CT_PAGE_ALIGN(addr)	ALIGN(addr, CT_PAGE_SIZE)

काष्ठा ct_vm_block अणु
	अचिन्हित पूर्णांक addr;	/* starting logical addr of this block */
	अचिन्हित पूर्णांक size;	/* size of this device भव mem block */
	काष्ठा list_head list;
पूर्ण;

काष्ठा snd_pcm_substream;

/* Virtual memory management object क्रम card device */
काष्ठा ct_vm अणु
	काष्ठा snd_dma_buffer ptp[CT_PTP_NUM];	/* Device page table pages */
	अचिन्हित पूर्णांक size;		/* Available addr space in bytes */
	काष्ठा list_head unused;	/* List of unused blocks */
	काष्ठा list_head used;		/* List of used blocks */
	काष्ठा mutex lock;

	/* Map host addr (kदो_स्मृतिed/vदो_स्मृतिed) to device logical addr. */
	काष्ठा ct_vm_block *(*map)(काष्ठा ct_vm *, काष्ठा snd_pcm_substream *,
				   पूर्णांक size);
	/* Unmap device logical addr area. */
	व्योम (*unmap)(काष्ठा ct_vm *, काष्ठा ct_vm_block *block);
	dma_addr_t (*get_ptp_phys)(काष्ठा ct_vm *vm, पूर्णांक index);
पूर्ण;

पूर्णांक ct_vm_create(काष्ठा ct_vm **rvm, काष्ठा pci_dev *pci);
व्योम ct_vm_destroy(काष्ठा ct_vm *vm);

#पूर्ण_अगर /* CTVMEM_H */
