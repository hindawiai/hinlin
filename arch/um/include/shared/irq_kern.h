<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)
 */

#अगर_अघोषित __IRQ_KERN_H__
#घोषणा __IRQ_KERN_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय-पूर्णांकernal.h>
#समावेश <यंत्र/ptrace.h>
#समावेश "irq_user.h"

#घोषणा UM_IRQ_ALLOC	-1

पूर्णांक um_request_irq(पूर्णांक irq, पूर्णांक fd, क्रमागत um_irq_type type,
		   irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		   स्थिर अक्षर *devname, व्योम *dev_id);

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
/**
 * um_request_irq_tt - request an IRQ with समयtravel handler
 *
 * @irq: the IRQ number, or %UM_IRQ_ALLOC
 * @fd: The file descriptor to request an IRQ क्रम
 * @type: पढ़ो or ग_लिखो
 * @handler: the (generic style) IRQ handler
 * @irqflags: Linux IRQ flags
 * @devname: name क्रम this to show
 * @dev_id: data poपूर्णांकer to pass to the IRQ handler
 * @समयtravel_handler: the समयtravel पूर्णांकerrupt handler, invoked with the IRQ
 *	number, fd, dev_id and समय-travel event poपूर्णांकer.
 *
 * Returns: The पूर्णांकerrupt number asचिन्हित or a negative error.
 *
 * Note that the समयtravel handler is invoked only अगर the समय_प्रकारravel_mode is
 * %TT_MODE_EXTERNAL, and then it is invoked even जबतक the प्रणाली is suspended!
 * This function must call समय_प्रकारravel_add_irq_event() क्रम the event passed with
 * an appropriate delay, beक्रमe sending an ACK on the socket it was invoked क्रम.
 *
 * If this was called जबतक the प्रणाली is suspended, then adding the event will
 * cause the प्रणाली to resume.
 *
 * Since this function will almost certainly have to handle the FD's condition,
 * a पढ़ो will consume the message, and after that it is up to the code using
 * it to pass such a message to the @handler in whichever way it can.
 *
 * If समय_प्रकारravel_mode is not %TT_MODE_EXTERNAL the @समयtravel_handler will
 * not be invoked at all and the @handler must handle the FD becoming
 * पढ़ोable (or writable) instead. Use um_irq_समयtravel_handler_used() to
 * distinguish these हालs.
 *
 * See virtio_uml.c क्रम an example.
 */
पूर्णांक um_request_irq_tt(पूर्णांक irq, पूर्णांक fd, क्रमागत um_irq_type type,
		      irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		      स्थिर अक्षर *devname, व्योम *dev_id,
		      व्योम (*समयtravel_handler)(पूर्णांक, पूर्णांक, व्योम *,
						 काष्ठा समय_प्रकारravel_event *));
#अन्यथा
अटल अंतरभूत
पूर्णांक um_request_irq_tt(पूर्णांक irq, पूर्णांक fd, क्रमागत um_irq_type type,
		      irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		      स्थिर अक्षर *devname, व्योम *dev_id,
		      व्योम (*समयtravel_handler)(पूर्णांक, पूर्णांक, व्योम *,
						 काष्ठा समय_प्रकारravel_event *))
अणु
	वापस um_request_irq(irq, fd, type, handler, irqflags,
			      devname, dev_id);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool um_irq_समयtravel_handler_used(व्योम)
अणु
	वापस समय_प्रकारravel_mode == TT_MODE_EXTERNAL;
पूर्ण

व्योम um_मुक्त_irq(पूर्णांक irq, व्योम *dev_id);
#पूर्ण_अगर
