<शैली गुरु>
/* via_dmablit.h -- PCI DMA BitBlt support क्रम the VIA Unichrome/Pro
 *
 * Copyright 2005 Thomas Hellstrom.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Thomas Hellstrom.
 *    Register info from Digeo Inc.
 */

#अगर_अघोषित _VIA_DMABLIT_H
#घोषणा _VIA_DMABLIT_H

#समावेश <linux/dma-mapping.h>

#घोषणा VIA_NUM_BLIT_ENGINES 2
#घोषणा VIA_NUM_BLIT_SLOTS 8

काष्ठा _drm_via_descriptor;

प्रकार काष्ठा _drm_via_sg_info अणु
	काष्ठा page **pages;
	अचिन्हित दीर्घ num_pages;
	काष्ठा _drm_via_descriptor **desc_pages;
	पूर्णांक num_desc_pages;
	पूर्णांक num_desc;
	क्रमागत dma_data_direction direction;
	अचिन्हित अक्षर *bounce_buffer;
	dma_addr_t chain_start;
	uपूर्णांक32_t मुक्त_on_sequence;
	अचिन्हित पूर्णांक descriptors_per_page;
	पूर्णांक पातed;
	क्रमागत अणु
		dr_via_device_mapped,
		dr_via_desc_pages_alloc,
		dr_via_pages_locked,
		dr_via_pages_alloc,
		dr_via_sg_init
	पूर्ण state;
पूर्ण drm_via_sg_info_t;

प्रकार काष्ठा _drm_via_blitq अणु
	काष्ठा drm_device *dev;
	uपूर्णांक32_t cur_blit_handle;
	uपूर्णांक32_t करोne_blit_handle;
	अचिन्हित serviced;
	अचिन्हित head;
	अचिन्हित cur;
	अचिन्हित num_मुक्त;
	अचिन्हित num_outstanding;
	अचिन्हित दीर्घ end;
	पूर्णांक पातing;
	पूर्णांक is_active;
	drm_via_sg_info_t *blits[VIA_NUM_BLIT_SLOTS];
	spinlock_t blit_lock;
	रुको_queue_head_t blit_queue[VIA_NUM_BLIT_SLOTS];
	रुको_queue_head_t busy_queue;
	काष्ठा work_काष्ठा wq;
	काष्ठा समयr_list poll_समयr;
पूर्ण drm_via_blitq_t;


/*
 *  PCI DMA Registers
 *  Channels 2 & 3 करोn't seem to be implemented in hardware.
 */

#घोषणा VIA_PCI_DMA_MAR0            0xE40   /* Memory Address Register of Channel 0 */
#घोषणा VIA_PCI_DMA_DAR0            0xE44   /* Device Address Register of Channel 0 */
#घोषणा VIA_PCI_DMA_BCR0            0xE48   /* Byte Count Register of Channel 0 */
#घोषणा VIA_PCI_DMA_DPR0            0xE4C   /* Descriptor Poपूर्णांकer Register of Channel 0 */

#घोषणा VIA_PCI_DMA_MAR1            0xE50   /* Memory Address Register of Channel 1 */
#घोषणा VIA_PCI_DMA_DAR1            0xE54   /* Device Address Register of Channel 1 */
#घोषणा VIA_PCI_DMA_BCR1            0xE58   /* Byte Count Register of Channel 1 */
#घोषणा VIA_PCI_DMA_DPR1            0xE5C   /* Descriptor Poपूर्णांकer Register of Channel 1 */

#घोषणा VIA_PCI_DMA_MAR2            0xE60   /* Memory Address Register of Channel 2 */
#घोषणा VIA_PCI_DMA_DAR2            0xE64   /* Device Address Register of Channel 2 */
#घोषणा VIA_PCI_DMA_BCR2            0xE68   /* Byte Count Register of Channel 2 */
#घोषणा VIA_PCI_DMA_DPR2            0xE6C   /* Descriptor Poपूर्णांकer Register of Channel 2 */

#घोषणा VIA_PCI_DMA_MAR3            0xE70   /* Memory Address Register of Channel 3 */
#घोषणा VIA_PCI_DMA_DAR3            0xE74   /* Device Address Register of Channel 3 */
#घोषणा VIA_PCI_DMA_BCR3            0xE78   /* Byte Count Register of Channel 3 */
#घोषणा VIA_PCI_DMA_DPR3            0xE7C   /* Descriptor Poपूर्णांकer Register of Channel 3 */

#घोषणा VIA_PCI_DMA_MR0             0xE80   /* Mode Register of Channel 0 */
#घोषणा VIA_PCI_DMA_MR1             0xE84   /* Mode Register of Channel 1 */
#घोषणा VIA_PCI_DMA_MR2             0xE88   /* Mode Register of Channel 2 */
#घोषणा VIA_PCI_DMA_MR3             0xE8C   /* Mode Register of Channel 3 */

#घोषणा VIA_PCI_DMA_CSR0            0xE90   /* Command/Status Register of Channel 0 */
#घोषणा VIA_PCI_DMA_CSR1            0xE94   /* Command/Status Register of Channel 1 */
#घोषणा VIA_PCI_DMA_CSR2            0xE98   /* Command/Status Register of Channel 2 */
#घोषणा VIA_PCI_DMA_CSR3            0xE9C   /* Command/Status Register of Channel 3 */

#घोषणा VIA_PCI_DMA_PTR             0xEA0   /* Priority Type Register */

/* Define क्रम DMA engine */
/* DPR */
#घोषणा VIA_DMA_DPR_EC		(1<<1)	/* end of chain */
#घोषणा VIA_DMA_DPR_DDIE	(1<<2)	/* descriptor करोne पूर्णांकerrupt enable */
#घोषणा VIA_DMA_DPR_DT		(1<<3)	/* direction of transfer (RO) */

/* MR */
#घोषणा VIA_DMA_MR_CM		(1<<0)	/* chaining mode */
#घोषणा VIA_DMA_MR_TDIE		(1<<1)	/* transfer करोne पूर्णांकerrupt enable */
#घोषणा VIA_DMA_MR_HENDMACMD		(1<<7) /* ? */

/* CSR */
#घोषणा VIA_DMA_CSR_DE		(1<<0)	/* DMA enable */
#घोषणा VIA_DMA_CSR_TS		(1<<1)	/* transfer start */
#घोषणा VIA_DMA_CSR_TA		(1<<2)	/* transfer पात */
#घोषणा VIA_DMA_CSR_TD		(1<<3)	/* transfer करोne */
#घोषणा VIA_DMA_CSR_DD		(1<<4)	/* descriptor करोne */
#घोषणा VIA_DMA_DPR_EC          (1<<1)  /* end of chain */



#पूर्ण_अगर
