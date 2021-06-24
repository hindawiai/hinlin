<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2009 Freescale Semiconductor, Inc.
 *
 * Cache SRAM handling क्रम QorIQ platक्रमm
 *
 * Author: Vivek Mahajan <vivek.mahajan@मुक्तscale.com>

 * This file is derived from the original work करोne
 * by Sylvain Munaut क्रम the Bestcomm SRAM allocator.
 */

#अगर_अघोषित __ASM_POWERPC_FSL_85XX_CACHE_SRAM_H__
#घोषणा __ASM_POWERPC_FSL_85XX_CACHE_SRAM_H__

#समावेश <यंत्र/rheap.h>
#समावेश <linux/spinlock.h>

/*
 * Cache-SRAM
 */

काष्ठा mpc85xx_cache_sram अणु
	phys_addr_t base_phys;
	व्योम *base_virt;
	अचिन्हित पूर्णांक size;
	rh_info_t *rh;
	spinlock_t lock;
पूर्ण;

बाह्य व्योम mpc85xx_cache_sram_मुक्त(व्योम *ptr);
बाह्य व्योम *mpc85xx_cache_sram_alloc(अचिन्हित पूर्णांक size,
				  phys_addr_t *phys, अचिन्हित पूर्णांक align);

#पूर्ण_अगर /* __AMS_POWERPC_FSL_85XX_CACHE_SRAM_H__ */
