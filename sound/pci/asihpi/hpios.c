<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2012  AudioScience Inc. <support@audioscience.com>


HPI Operating System function implementation क्रम Linux

(C) Copyright AudioScience Inc. 1997-2003
******************************************************************************/
#घोषणा SOURCEखाता_NAME "hpios.c"
#समावेश "hpi_internal.h"
#समावेश "hpidebug.h"
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>

व्योम hpios_delay_micro_seconds(u32 num_micro_sec)
अणु
	अगर ((usecs_to_jअगरfies(num_micro_sec) > 1) && !in_पूर्णांकerrupt()) अणु
		/* MUST NOT SCHEDULE IN INTERRUPT CONTEXT! */
		schedule_समयout_unपूर्णांकerruptible(usecs_to_jअगरfies
			(num_micro_sec));
	पूर्ण अन्यथा अगर (num_micro_sec <= 2000)
		udelay(num_micro_sec);
	अन्यथा
		mdelay(num_micro_sec / 1000);

पूर्ण

/** Allocate an area of locked memory क्रम bus master DMA operations.

If allocation fails, वापस 1, and *pMemArea.size = 0
*/
u16 hpios_locked_mem_alloc(काष्ठा consistent_dma_area *p_mem_area, u32 size,
	काष्ठा pci_dev *pdev)
अणु
	/*?? any benefit in using managed dmam_alloc_coherent? */
	p_mem_area->vaddr =
		dma_alloc_coherent(&pdev->dev, size, &p_mem_area->dma_handle,
		GFP_KERNEL);

	अगर (p_mem_area->vaddr) अणु
		HPI_DEBUG_LOG(DEBUG, "allocated %d bytes, dma 0x%x vma %p\n",
			size, (अचिन्हित पूर्णांक)p_mem_area->dma_handle,
			p_mem_area->vaddr);
		p_mem_area->pdev = &pdev->dev;
		p_mem_area->size = size;
		वापस 0;
	पूर्ण अन्यथा अणु
		HPI_DEBUG_LOG(WARNING,
			"failed to allocate %d bytes locked memory\n", size);
		p_mem_area->size = 0;
		वापस 1;
	पूर्ण
पूर्ण

u16 hpios_locked_mem_मुक्त(काष्ठा consistent_dma_area *p_mem_area)
अणु
	अगर (p_mem_area->size) अणु
		dma_मुक्त_coherent(p_mem_area->pdev, p_mem_area->size,
			p_mem_area->vaddr, p_mem_area->dma_handle);
		HPI_DEBUG_LOG(DEBUG, "freed %lu bytes, dma 0x%x vma %p\n",
			(अचिन्हित दीर्घ)p_mem_area->size,
			(अचिन्हित पूर्णांक)p_mem_area->dma_handle,
			p_mem_area->vaddr);
		p_mem_area->size = 0;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण
पूर्ण
