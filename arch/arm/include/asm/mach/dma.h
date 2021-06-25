<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/mach/dma.h
 *
 *  Copyright (C) 1998-2000 Russell King
 *
 *  This header file describes the पूर्णांकerface between the generic DMA handler
 *  (dma.c) and the architecture-specअगरic DMA backends (dma-*.c)
 */

काष्ठा dma_काष्ठा;
प्रकार काष्ठा dma_काष्ठा dma_t;

काष्ठा dma_ops अणु
	पूर्णांक	(*request)(अचिन्हित पूर्णांक, dma_t *);		/* optional */
	व्योम	(*मुक्त)(अचिन्हित पूर्णांक, dma_t *);			/* optional */
	व्योम	(*enable)(अचिन्हित पूर्णांक, dma_t *);		/* mandatory */
	व्योम 	(*disable)(अचिन्हित पूर्णांक, dma_t *);		/* mandatory */
	पूर्णांक	(*residue)(अचिन्हित पूर्णांक, dma_t *);		/* optional */
	पूर्णांक	(*setspeed)(अचिन्हित पूर्णांक, dma_t *, पूर्णांक);	/* optional */
	स्थिर अक्षर *type;
पूर्ण;

काष्ठा dma_काष्ठा अणु
	व्योम		*addr;		/* single DMA address		*/
	अचिन्हित दीर्घ	count;		/* single DMA size		*/
	काष्ठा scatterlist buf;		/* single DMA			*/
	पूर्णांक		sgcount;	/* number of DMA SG		*/
	काष्ठा scatterlist *sg;		/* DMA Scatter-Gather List	*/

	अचिन्हित पूर्णांक	active:1;	/* Transfer active		*/
	अचिन्हित पूर्णांक	invalid:1;	/* Address/Count changed	*/

	अचिन्हित पूर्णांक	dma_mode;	/* DMA mode			*/
	पूर्णांक		speed;		/* DMA speed			*/

	अचिन्हित पूर्णांक	lock;		/* Device is allocated		*/
	स्थिर अक्षर	*device_id;	/* Device name			*/

	स्थिर काष्ठा dma_ops *d_ops;
पूर्ण;

/*
 * isa_dma_add - add an ISA-style DMA channel
 */
बाह्य पूर्णांक isa_dma_add(अचिन्हित पूर्णांक, dma_t *dma);

/*
 * Add the ISA DMA controller.  Always takes channels 0-7.
 */
बाह्य व्योम isa_init_dma(व्योम);
