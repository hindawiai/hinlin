<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	dma.c -- Freescale ColdFire DMA support
 *
 *	Copyright (C) 2007, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfdma.h>

/***************************************************************************/

/*
 *      DMA channel base address table.
 */
अचिन्हित पूर्णांक dma_base_addr[MAX_M68K_DMA_CHANNELS] = अणु
#अगर_घोषित MCFDMA_BASE0
	MCFDMA_BASE0,
#पूर्ण_अगर
#अगर_घोषित MCFDMA_BASE1
	MCFDMA_BASE1,
#पूर्ण_अगर
#अगर_घोषित MCFDMA_BASE2
	MCFDMA_BASE2,
#पूर्ण_अगर
#अगर_घोषित MCFDMA_BASE3
	MCFDMA_BASE3,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(dma_base_addr);

अचिन्हित पूर्णांक dma_device_address[MAX_M68K_DMA_CHANNELS];
EXPORT_SYMBOL(dma_device_address);

/***************************************************************************/
