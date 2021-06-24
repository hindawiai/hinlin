<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TRIGGER_H_
#घोषणा __TRIGGER_H_ 1

#समावेश "asm/bug.h"

/*
 * Use trigger to model operations which need to be executed when
 * an event (a संकेत, क्रम example) is observed.
 *
 * States and transits:
 *
 *
 *  OFF--> ON --> READY --(hit)--> HIT
 *                 ^               |
 *                 |            (पढ़ोy)
 *                 |               |
 *                  \_____________/
 *
 * is_hit and is_पढ़ोy are two key functions to query the state of
 * a trigger. is_hit means the event alपढ़ोy happen; is_पढ़ोy means the
 * trigger is रुकोing क्रम the event.
 */

काष्ठा trigger अणु
	अस्थिर क्रमागत अणु
		TRIGGER_ERROR		= -2,
		TRIGGER_OFF		= -1,
		TRIGGER_ON		= 0,
		TRIGGER_READY		= 1,
		TRIGGER_HIT		= 2,
	पूर्ण state;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा TRIGGER_WARN_ONCE(t, exp) \
	WARN_ONCE(t->state != exp, "trigger '%s' state transist error: %d in %s()\n", \
		  t->name, t->state, __func__)

अटल अंतरभूत bool trigger_is_available(काष्ठा trigger *t)
अणु
	वापस t->state >= 0;
पूर्ण

अटल अंतरभूत bool trigger_is_error(काष्ठा trigger *t)
अणु
	वापस t->state <= TRIGGER_ERROR;
पूर्ण

अटल अंतरभूत व्योम trigger_on(काष्ठा trigger *t)
अणु
	TRIGGER_WARN_ONCE(t, TRIGGER_OFF);
	t->state = TRIGGER_ON;
पूर्ण

अटल अंतरभूत व्योम trigger_पढ़ोy(काष्ठा trigger *t)
अणु
	अगर (!trigger_is_available(t))
		वापस;
	t->state = TRIGGER_READY;
पूर्ण

अटल अंतरभूत व्योम trigger_hit(काष्ठा trigger *t)
अणु
	अगर (!trigger_is_available(t))
		वापस;
	TRIGGER_WARN_ONCE(t, TRIGGER_READY);
	t->state = TRIGGER_HIT;
पूर्ण

अटल अंतरभूत व्योम trigger_off(काष्ठा trigger *t)
अणु
	अगर (!trigger_is_available(t))
		वापस;
	t->state = TRIGGER_OFF;
पूर्ण

अटल अंतरभूत व्योम trigger_error(काष्ठा trigger *t)
अणु
	t->state = TRIGGER_ERROR;
पूर्ण

अटल अंतरभूत bool trigger_is_पढ़ोy(काष्ठा trigger *t)
अणु
	वापस t->state == TRIGGER_READY;
पूर्ण

अटल अंतरभूत bool trigger_is_hit(काष्ठा trigger *t)
अणु
	वापस t->state == TRIGGER_HIT;
पूर्ण

#घोषणा DEFINE_TRIGGER(n) \
काष्ठा trigger n = अणु.state = TRIGGER_OFF, .name = #nपूर्ण
#पूर्ण_अगर
