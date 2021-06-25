<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPARC_EBUS_DMA_H
#घोषणा __ASM_SPARC_EBUS_DMA_H

काष्ठा ebus_dma_info अणु
	spinlock_t	lock;
	व्योम __iomem	*regs;

	अचिन्हित पूर्णांक	flags;
#घोषणा EBUS_DMA_FLAG_USE_EBDMA_HANDLER		0x00000001
#घोषणा EBUS_DMA_FLAG_TCI_DISABLE		0x00000002

	/* These are only valid is EBUS_DMA_FLAG_USE_EBDMA_HANDLER is
	 * set.
	 */
	व्योम (*callback)(काष्ठा ebus_dma_info *p, पूर्णांक event, व्योम *cookie);
	व्योम *client_cookie;
	अचिन्हित पूर्णांक	irq;
#घोषणा EBUS_DMA_EVENT_ERROR	1
#घोषणा EBUS_DMA_EVENT_DMA	2
#घोषणा EBUS_DMA_EVENT_DEVICE	4

	अचिन्हित अक्षर	name[64];
पूर्ण;

पूर्णांक ebus_dma_रेजिस्टर(काष्ठा ebus_dma_info *p);
पूर्णांक ebus_dma_irq_enable(काष्ठा ebus_dma_info *p, पूर्णांक on);
व्योम ebus_dma_unरेजिस्टर(काष्ठा ebus_dma_info *p);
पूर्णांक ebus_dma_request(काष्ठा ebus_dma_info *p, dma_addr_t bus_addr,
			    माप_प्रकार len);
व्योम ebus_dma_prepare(काष्ठा ebus_dma_info *p, पूर्णांक ग_लिखो);
अचिन्हित पूर्णांक ebus_dma_residue(काष्ठा ebus_dma_info *p);
अचिन्हित पूर्णांक ebus_dma_addr(काष्ठा ebus_dma_info *p);
व्योम ebus_dma_enable(काष्ठा ebus_dma_info *p, पूर्णांक on);

#पूर्ण_अगर /* __ASM_SPARC_EBUS_DMA_H */
