<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Freescale General-purpose Timers Module
 *
 * Copyright 2006 Freescale Semiconductor, Inc.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#अगर_अघोषित __ASM_FSL_GTM_H
#घोषणा __ASM_FSL_GTM_H

#समावेश <linux/types.h>

काष्ठा gपंचांग;

काष्ठा gपंचांग_समयr अणु
	अचिन्हित पूर्णांक irq;

	काष्ठा gपंचांग *gपंचांग;
	bool requested;
	u8 __iomem *gtcfr;
	__be16 __iomem *gपंचांगdr;
	__be16 __iomem *gtpsr;
	__be16 __iomem *gtcnr;
	__be16 __iomem *gtrfr;
	__be16 __iomem *gtevr;
पूर्ण;

बाह्य काष्ठा gपंचांग_समयr *gपंचांग_get_समयr16(व्योम);
बाह्य काष्ठा gपंचांग_समयr *gपंचांग_get_specअगरic_समयr16(काष्ठा gपंचांग *gपंचांग,
						  अचिन्हित पूर्णांक समयr);
बाह्य व्योम gपंचांग_put_समयr16(काष्ठा gपंचांग_समयr *पंचांगr);
बाह्य पूर्णांक gपंचांग_set_समयr16(काष्ठा gपंचांग_समयr *पंचांगr, अचिन्हित दीर्घ usec,
			     bool reload);
बाह्य पूर्णांक gपंचांग_set_exact_समयr16(काष्ठा gपंचांग_समयr *पंचांगr, u16 usec,
				 bool reload);
बाह्य व्योम gपंचांग_stop_समयr16(काष्ठा gपंचांग_समयr *पंचांगr);
बाह्य व्योम gपंचांग_ack_समयr16(काष्ठा gपंचांग_समयr *पंचांगr, u16 events);

#पूर्ण_अगर /* __ASM_FSL_GTM_H */
