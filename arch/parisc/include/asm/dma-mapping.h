<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_DMA_MAPPING_H
#घोषणा _PARISC_DMA_MAPPING_H

/*
** We need to support 4 dअगरferent coherent dma models with one binary:
**
**     I/O MMU        consistent method           dma_sync behavior
**  =============   ======================       =======================
**  a) PA-7x00LC    uncachable host memory          flush/purge
**  b) U2/Uturn      cachable host memory              NOP
**  c) Ike/Astro     cachable host memory              NOP
**  d) EPIC/SAGA     memory on EPIC/SAGA         flush/reset DMA channel
**
** PA-7[13]00LC processors have a GSC bus पूर्णांकerface and no I/O MMU.
**
** Systems (eg PCX-T workstations) that करोn't fall पूर्णांकo the above
** categories will need to modअगरy the needed drivers to perक्रमm
** flush/purge and allocate "regular" cacheable pages क्रम everything.
*/

बाह्य स्थिर काष्ठा dma_map_ops *hppa_dma_ops;

अटल अंतरभूत स्थिर काष्ठा dma_map_ops *get_arch_dma_ops(काष्ठा bus_type *bus)
अणु
	वापस hppa_dma_ops;
पूर्ण

#पूर्ण_अगर
