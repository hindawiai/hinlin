<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TIMER_OF_H__
#घोषणा __TIMER_OF_H__

#समावेश <linux/घड़ीchips.h>

#घोषणा TIMER_OF_BASE	0x1
#घोषणा TIMER_OF_CLOCK	0x2
#घोषणा TIMER_OF_IRQ	0x4

काष्ठा of_समयr_irq अणु
	पूर्णांक irq;
	पूर्णांक index;
	पूर्णांक percpu;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ flags;
	irq_handler_t handler;
पूर्ण;

काष्ठा of_समयr_base अणु
	व्योम __iomem *base;
	स्थिर अक्षर *name;
	पूर्णांक index;
पूर्ण;

काष्ठा of_समयr_clk अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *name;
	पूर्णांक index;
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ period;
पूर्ण;

काष्ठा समयr_of अणु
	अचिन्हित पूर्णांक flags;
	काष्ठा device_node *np;
	काष्ठा घड़ी_event_device clkevt;
	काष्ठा of_समयr_base of_base;
	काष्ठा of_समयr_irq  of_irq;
	काष्ठा of_समयr_clk  of_clk;
	व्योम *निजी_data;
पूर्ण;

अटल अंतरभूत काष्ठा समयr_of *to_समयr_of(काष्ठा घड़ी_event_device *clkevt)
अणु
	वापस container_of(clkevt, काष्ठा समयr_of, clkevt);
पूर्ण

अटल अंतरभूत व्योम __iomem *समयr_of_base(काष्ठा समयr_of *to)
अणु
	वापस to->of_base.base;
पूर्ण

अटल अंतरभूत पूर्णांक समयr_of_irq(काष्ठा समयr_of *to)
अणु
	वापस to->of_irq.irq;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ समयr_of_rate(काष्ठा समयr_of *to)
अणु
	वापस to->of_clk.rate;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ समयr_of_period(काष्ठा समयr_of *to)
अणु
	वापस to->of_clk.period;
पूर्ण

बाह्य पूर्णांक __init समयr_of_init(काष्ठा device_node *np,
				काष्ठा समयr_of *to);

बाह्य व्योम __init समयr_of_cleanup(काष्ठा समयr_of *to);

#पूर्ण_अगर
