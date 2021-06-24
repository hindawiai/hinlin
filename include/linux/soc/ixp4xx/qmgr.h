<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007 Krzysztof Halasa <khc@pm.waw.pl>
 */

#अगर_अघोषित IXP4XX_QMGR_H
#घोषणा IXP4XX_QMGR_H

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>

#घोषणा DEBUG_QMGR	0

#घोषणा HALF_QUEUES	32
#घोषणा QUEUES		64
#घोषणा MAX_QUEUE_LENGTH 4	/* in dwords */

#घोषणा QUEUE_STAT1_EMPTY		1 /* queue status bits */
#घोषणा QUEUE_STAT1_NEARLY_EMPTY	2
#घोषणा QUEUE_STAT1_NEARLY_FULL		4
#घोषणा QUEUE_STAT1_FULL		8
#घोषणा QUEUE_STAT2_UNDERFLOW		1
#घोषणा QUEUE_STAT2_OVERFLOW		2

#घोषणा QUEUE_WATERMARK_0_ENTRIES	0
#घोषणा QUEUE_WATERMARK_1_ENTRY		1
#घोषणा QUEUE_WATERMARK_2_ENTRIES	2
#घोषणा QUEUE_WATERMARK_4_ENTRIES	3
#घोषणा QUEUE_WATERMARK_8_ENTRIES	4
#घोषणा QUEUE_WATERMARK_16_ENTRIES	5
#घोषणा QUEUE_WATERMARK_32_ENTRIES	6
#घोषणा QUEUE_WATERMARK_64_ENTRIES	7

/* queue पूर्णांकerrupt request conditions */
#घोषणा QUEUE_IRQ_SRC_EMPTY		0
#घोषणा QUEUE_IRQ_SRC_NEARLY_EMPTY	1
#घोषणा QUEUE_IRQ_SRC_NEARLY_FULL	2
#घोषणा QUEUE_IRQ_SRC_FULL		3
#घोषणा QUEUE_IRQ_SRC_NOT_EMPTY		4
#घोषणा QUEUE_IRQ_SRC_NOT_NEARLY_EMPTY	5
#घोषणा QUEUE_IRQ_SRC_NOT_NEARLY_FULL	6
#घोषणा QUEUE_IRQ_SRC_NOT_FULL		7

काष्ठा qmgr_regs अणु
	u32 acc[QUEUES][MAX_QUEUE_LENGTH]; /* 0x000 - 0x3FF */
	u32 stat1[4];		/* 0x400 - 0x40F */
	u32 stat2[2];		/* 0x410 - 0x417 */
	u32 statne_h;		/* 0x418 - queue nearly empty */
	u32 statf_h;		/* 0x41C - queue full */
	u32 irqsrc[4];		/* 0x420 - 0x42F IRC source */
	u32 irqen[2];		/* 0x430 - 0x437 IRQ enabled */
	u32 irqstat[2];		/* 0x438 - 0x43F - IRQ access only */
	u32 reserved[1776];
	u32 sram[2048];		/* 0x2000 - 0x3FFF - config and buffer */
पूर्ण;

व्योम qmgr_put_entry(अचिन्हित पूर्णांक queue, u32 val);
u32 qmgr_get_entry(अचिन्हित पूर्णांक queue);
पूर्णांक qmgr_stat_empty(अचिन्हित पूर्णांक queue);
पूर्णांक qmgr_stat_below_low_watermark(अचिन्हित पूर्णांक queue);
पूर्णांक qmgr_stat_full(अचिन्हित पूर्णांक queue);
पूर्णांक qmgr_stat_overflow(अचिन्हित पूर्णांक queue);
व्योम qmgr_release_queue(अचिन्हित पूर्णांक queue);
व्योम qmgr_set_irq(अचिन्हित पूर्णांक queue, पूर्णांक src,
		  व्योम (*handler)(व्योम *pdev), व्योम *pdev);
व्योम qmgr_enable_irq(अचिन्हित पूर्णांक queue);
व्योम qmgr_disable_irq(अचिन्हित पूर्णांक queue);

/* request_ and release_queue() must be called from non-IRQ context */

#अगर DEBUG_QMGR
बाह्य अक्षर qmgr_queue_descs[QUEUES][32];

पूर्णांक qmgr_request_queue(अचिन्हित पूर्णांक queue, अचिन्हित पूर्णांक len /* dwords */,
		       अचिन्हित पूर्णांक nearly_empty_watermark,
		       अचिन्हित पूर्णांक nearly_full_watermark,
		       स्थिर अक्षर *desc_क्रमmat, स्थिर अक्षर* name);
#अन्यथा
पूर्णांक __qmgr_request_queue(अचिन्हित पूर्णांक queue, अचिन्हित पूर्णांक len /* dwords */,
			 अचिन्हित पूर्णांक nearly_empty_watermark,
			 अचिन्हित पूर्णांक nearly_full_watermark);
#घोषणा qmgr_request_queue(queue, len, nearly_empty_watermark,		\
			   nearly_full_watermark, desc_क्रमmat, name)	\
	__qmgr_request_queue(queue, len, nearly_empty_watermark,	\
			     nearly_full_watermark)
#पूर्ण_अगर

#पूर्ण_अगर
