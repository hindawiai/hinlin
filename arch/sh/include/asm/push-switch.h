<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PUSH_SWITCH_H
#घोषणा __ASM_SH_PUSH_SWITCH_H

#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा push_चयन अणु
	/* चयन state */
	अचिन्हित पूर्णांक		state:1;
	/* debounce समयr */
	काष्ठा समयr_list	debounce;
	/* workqueue */
	काष्ठा work_काष्ठा	work;
	/* platक्रमm device, क्रम workqueue handler */
	काष्ठा platक्रमm_device	*pdev;
पूर्ण;

काष्ठा push_चयन_platक्रमm_info अणु
	/* IRQ handler */
	irqवापस_t		(*irq_handler)(पूर्णांक irq, व्योम *data);
	/* Special IRQ flags */
	अचिन्हित पूर्णांक		irq_flags;
	/* Bit location of चयन */
	अचिन्हित पूर्णांक		bit;
	/* Symbolic चयन name */
	स्थिर अक्षर		*name;
पूर्ण;

#पूर्ण_अगर /* __ASM_SH_PUSH_SWITCH_H */
