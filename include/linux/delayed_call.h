<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DELAYED_CALL_H
#घोषणा _DELAYED_CALL_H

/*
 * Poor man's closures; I wish we could've करोne them sanely polymorphic,
 * but...
 */

काष्ठा delayed_call अणु
	व्योम (*fn)(व्योम *);
	व्योम *arg;
पूर्ण;

#घोषणा DEFINE_DELAYED_CALL(name) काष्ठा delayed_call name = अणुशून्य, शून्यपूर्ण

/* I really wish we had closures with sane typechecking... */
अटल अंतरभूत व्योम set_delayed_call(काष्ठा delayed_call *call,
		व्योम (*fn)(व्योम *), व्योम *arg)
अणु
	call->fn = fn;
	call->arg = arg;
पूर्ण

अटल अंतरभूत व्योम करो_delayed_call(काष्ठा delayed_call *call)
अणु
	अगर (call->fn)
		call->fn(call->arg);
पूर्ण

अटल अंतरभूत व्योम clear_delayed_call(काष्ठा delayed_call *call)
अणु
	call->fn = शून्य;
पूर्ण
#पूर्ण_अगर
