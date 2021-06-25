<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * (C) Copyright 2009 Intel Corporation
 * Author: Jacob Pan (jacob.jun.pan@पूर्णांकel.com)
 *
 * Shared with ARM platक्रमms, Jamie Iles, Picochip 2011
 *
 * Support क्रम the Synopsys DesignWare APB Timers.
 */
#अगर_अघोषित __DW_APB_TIMER_H__
#घोषणा __DW_APB_TIMER_H__

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा APBTMRS_REG_SIZE       0x14

काष्ठा dw_apb_समयr अणु
	व्योम __iomem				*base;
	अचिन्हित दीर्घ				freq;
	पूर्णांक					irq;
पूर्ण;

काष्ठा dw_apb_घड़ी_event_device अणु
	काष्ठा घड़ी_event_device		ced;
	काष्ठा dw_apb_समयr			समयr;
	व्योम					(*eoi)(काष्ठा dw_apb_समयr *);
पूर्ण;

काष्ठा dw_apb_घड़ीsource अणु
	काष्ठा dw_apb_समयr			समयr;
	काष्ठा घड़ीsource			cs;
पूर्ण;

व्योम dw_apb_घड़ीevent_रेजिस्टर(काष्ठा dw_apb_घड़ी_event_device *dw_ced);
व्योम dw_apb_घड़ीevent_छोड़ो(काष्ठा dw_apb_घड़ी_event_device *dw_ced);
व्योम dw_apb_घड़ीevent_resume(काष्ठा dw_apb_घड़ी_event_device *dw_ced);
व्योम dw_apb_घड़ीevent_stop(काष्ठा dw_apb_घड़ी_event_device *dw_ced);

काष्ठा dw_apb_घड़ी_event_device *
dw_apb_घड़ीevent_init(पूर्णांक cpu, स्थिर अक्षर *name, अचिन्हित rating,
		       व्योम __iomem *base, पूर्णांक irq, अचिन्हित दीर्घ freq);
काष्ठा dw_apb_घड़ीsource *
dw_apb_घड़ीsource_init(अचिन्हित rating, स्थिर अक्षर *name, व्योम __iomem *base,
			अचिन्हित दीर्घ freq);
व्योम dw_apb_घड़ीsource_रेजिस्टर(काष्ठा dw_apb_घड़ीsource *dw_cs);
व्योम dw_apb_घड़ीsource_start(काष्ठा dw_apb_घड़ीsource *dw_cs);
u64 dw_apb_घड़ीsource_पढ़ो(काष्ठा dw_apb_घड़ीsource *dw_cs);

#पूर्ण_अगर /* __DW_APB_TIMER_H__ */
