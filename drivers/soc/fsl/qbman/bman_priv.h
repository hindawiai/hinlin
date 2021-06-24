<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "dpaa_sys.h"

#समावेश <soc/fsl/bman.h>

/* Portal processing (पूर्णांकerrupt) sources */
#घोषणा BM_PIRQ_RCRI	0x00000002	/* RCR Ring (below threshold) */

/* Revision info (क्रम errata and feature handling) */
#घोषणा BMAN_REV10 0x0100
#घोषणा BMAN_REV20 0x0200
#घोषणा BMAN_REV21 0x0201
बाह्य u16 bman_ip_rev;	/* 0 अगर uninitialised, otherwise BMAN_REVx */

बाह्य काष्ठा gen_pool *bm_bpalloc;

काष्ठा bm_portal_config अणु
	/* Portal addresses */
	व्योम  *addr_virt_ce;
	व्योम __iomem *addr_virt_ci;
	/* Allow these to be joined in lists */
	काष्ठा list_head list;
	काष्ठा device *dev;
	/* User-visible portal configuration settings */
	/* portal is affined to this cpu */
	पूर्णांक cpu;
	/* portal पूर्णांकerrupt line */
	पूर्णांक irq;
पूर्ण;

काष्ठा bman_portal *bman_create_affine_portal(
			स्थिर काष्ठा bm_portal_config *config);
/*
 * The below bman_p_***() variant might be called in a situation that the cpu
 * which the portal affine to is not online yet.
 * @bman_portal specअगरies which portal the API will use.
 */
पूर्णांक bman_p_irqsource_add(काष्ठा bman_portal *p, u32 bits);

/*
 * Used by all portal पूर्णांकerrupt रेजिस्टरs except 'inhibit'
 * This mask contains all the "irqsource" bits visible to API users
 */
#घोषणा BM_PIRQ_VISIBLE	BM_PIRQ_RCRI

स्थिर काष्ठा bm_portal_config *
bman_get_bm_portal_config(स्थिर काष्ठा bman_portal *portal);

पूर्णांक bman_requires_cleanup(व्योम);
व्योम bman_करोne_cleanup(व्योम);

पूर्णांक bm_shutकरोwn_pool(u32 bpid);
