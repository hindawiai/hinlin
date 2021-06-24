<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/kernel/dma-ebsa285.c
 *
 *  Copyright (C) 1998 Phil Blundell
 *
 * DMA functions specअगरic to EBSA-285/CATS architectures
 *
 *  Changelog:
 *   09-Nov-1998 RMK	Split out ISA DMA functions to dma-isa.c
 *   17-Mar-1999 RMK	Allow any EBSA285-like architecture to have
 *			ISA DMA controllers.
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/dma.h>

#समावेश <यंत्र/mach/dma.h>
#समावेश <यंत्र/hardware/dec21285.h>

#अगर 0
अटल पूर्णांक fb_dma_request(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम fb_dma_enable(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
पूर्ण

अटल व्योम fb_dma_disable(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
पूर्ण

अटल काष्ठा dma_ops fb_dma_ops = अणु
	.type		= "fb",
	.request	= fb_dma_request,
	.enable		= fb_dma_enable,
	.disable	= fb_dma_disable,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init fb_dma_init(व्योम)
अणु
#अगर 0
	dma[_DC21285_DMA(0)].d_ops = &fb_dma_ops;
	dma[_DC21285_DMA(1)].d_ops = &fb_dma_ops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ISA_DMA
	अगर (footbridge_cfn_mode())
		isa_init_dma();
#पूर्ण_अगर
	वापस 0;
पूर्ण
core_initcall(fb_dma_init);
