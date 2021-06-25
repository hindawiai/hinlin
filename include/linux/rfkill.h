<शैली गुरु>
/*
 * Copyright (C) 2006 - 2007 Ivo van Doorn
 * Copyright (C) 2007 Dmitry Torokhov
 * Copyright 2009 Johannes Berg <johannes@sipsolutions.net>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#अगर_अघोषित __RFKILL_H
#घोषणा __RFKILL_H

#समावेश <uapi/linux/rfसमाप्त.h>

/* करोn't allow anyone to use these in the kernel */
क्रमागत rfसमाप्त_user_states अणु
	RFKILL_USER_STATE_SOFT_BLOCKED	= RFKILL_STATE_SOFT_BLOCKED,
	RFKILL_USER_STATE_UNBLOCKED	= RFKILL_STATE_UNBLOCKED,
	RFKILL_USER_STATE_HARD_BLOCKED	= RFKILL_STATE_HARD_BLOCKED,
पूर्ण;
#अघोषित RFKILL_STATE_SOFT_BLOCKED
#अघोषित RFKILL_STATE_UNBLOCKED
#अघोषित RFKILL_STATE_HARD_BLOCKED

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>

काष्ठा device;
/* this is opaque */
काष्ठा rfसमाप्त;

/**
 * काष्ठा rfसमाप्त_ops - rfसमाप्त driver methods
 *
 * @poll: poll the rfसमाप्त block state(s) -- only assign this method
 *	when you need polling. When called, simply call one of the
 *	rfसमाप्त_setअणु,_hw,_swपूर्ण_state family of functions. If the hw
 *	is getting unblocked you need to take पूर्णांकo account the वापस
 *	value of those functions to make sure the software block is
 *	properly used.
 * @query: query the rfसमाप्त block state(s) and call exactly one of the
 *	rfसमाप्त_setअणु,_hw,_swपूर्ण_state family of functions. Assign this
 *	method अगर input events can cause hardware state changes to make
 *	the rfसमाप्त core query your driver beक्रमe setting a requested
 *	block.
 * @set_block: turn the transmitter on (blocked == false) or off
 *	(blocked == true) -- ignore and वापस 0 when hard blocked.
 *	This callback must be asचिन्हित.
 */
काष्ठा rfसमाप्त_ops अणु
	व्योम	(*poll)(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data);
	व्योम	(*query)(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data);
	पूर्णांक	(*set_block)(व्योम *data, bool blocked);
पूर्ण;

#अगर defined(CONFIG_RFKILL) || defined(CONFIG_RFKILL_MODULE)
/**
 * rfसमाप्त_alloc - Allocate rfसमाप्त काष्ठाure
 * @name: name of the काष्ठा -- the string is not copied पूर्णांकernally
 * @parent: device that has rf चयन on it
 * @type: type of the चयन (RFKILL_TYPE_*)
 * @ops: rfसमाप्त methods
 * @ops_data: data passed to each method
 *
 * This function should be called by the transmitter driver to allocate an
 * rfसमाप्त काष्ठाure. Returns %शून्य on failure.
 */
काष्ठा rfसमाप्त * __must_check rfसमाप्त_alloc(स्थिर अक्षर *name,
					  काष्ठा device *parent,
					  स्थिर क्रमागत rfसमाप्त_type type,
					  स्थिर काष्ठा rfसमाप्त_ops *ops,
					  व्योम *ops_data);

/**
 * rfसमाप्त_रेजिस्टर - Register a rfसमाप्त काष्ठाure.
 * @rfसमाप्त: rfसमाप्त काष्ठाure to be रेजिस्टरed
 *
 * This function should be called by the transmitter driver to रेजिस्टर
 * the rfसमाप्त काष्ठाure. Beक्रमe calling this function the driver needs
 * to be पढ़ोy to service method calls from rfसमाप्त.
 *
 * If rfसमाप्त_init_sw_state() is not called beक्रमe registration,
 * set_block() will be called to initialize the software blocked state
 * to a शेष value.
 *
 * If the hardware blocked state is not set beक्रमe registration,
 * it is assumed to be unblocked.
 */
पूर्णांक __must_check rfसमाप्त_रेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त);

/**
 * rfसमाप्त_छोड़ो_polling(काष्ठा rfसमाप्त *rfसमाप्त)
 *
 * Pause polling -- say transmitter is off क्रम other reasons.
 * NOTE: not necessary क्रम suspend/resume -- in that हाल the
 * core stops polling anyway (but will also correctly handle
 * the हाल of polling having been छोड़ोd beक्रमe suspend.)
 */
व्योम rfसमाप्त_छोड़ो_polling(काष्ठा rfसमाप्त *rfसमाप्त);

/**
 * rfसमाप्त_resume_polling(काष्ठा rfसमाप्त *rfसमाप्त)
 *
 * Resume polling
 * NOTE: not necessary क्रम suspend/resume -- in that हाल the
 * core stops polling anyway
 */
व्योम rfसमाप्त_resume_polling(काष्ठा rfसमाप्त *rfसमाप्त);


/**
 * rfसमाप्त_unरेजिस्टर - Unरेजिस्टर a rfसमाप्त काष्ठाure.
 * @rfसमाप्त: rfसमाप्त काष्ठाure to be unरेजिस्टरed
 *
 * This function should be called by the network driver during device
 * tearकरोwn to destroy rfसमाप्त काष्ठाure. Until it वापसs, the driver
 * needs to be able to service method calls.
 */
व्योम rfसमाप्त_unरेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त);

/**
 * rfसमाप्त_destroy - Free rfसमाप्त काष्ठाure
 * @rfसमाप्त: rfसमाप्त काष्ठाure to be destroyed
 *
 * Destroys the rfसमाप्त काष्ठाure.
 */
व्योम rfसमाप्त_destroy(काष्ठा rfसमाप्त *rfसमाप्त);

/**
 * rfसमाप्त_set_hw_state_reason - Set the पूर्णांकernal rfसमाप्त hardware block state
 *	with a reason
 * @rfसमाप्त: poपूर्णांकer to the rfसमाप्त class to modअगरy.
 * @blocked: the current hardware block state to set
 * @reason: one of &क्रमागत rfसमाप्त_hard_block_reasons
 *
 * Prefer to use rfसमाप्त_set_hw_state अगर you करोn't need any special reason.
 */
bool rfसमाप्त_set_hw_state_reason(काष्ठा rfसमाप्त *rfसमाप्त,
				bool blocked, अचिन्हित दीर्घ reason);
/**
 * rfसमाप्त_set_hw_state - Set the पूर्णांकernal rfसमाप्त hardware block state
 * @rfसमाप्त: poपूर्णांकer to the rfसमाप्त class to modअगरy.
 * @blocked: the current hardware block state to set
 *
 * rfसमाप्त drivers that get events when the hard-blocked state changes
 * use this function to notअगरy the rfसमाप्त core (and through that also
 * userspace) of the current state.  They should also use this after
 * resume अगर the state could have changed.
 *
 * You need not (but may) call this function अगर poll_state is asचिन्हित.
 *
 * This function can be called in any context, even from within rfसमाप्त
 * callbacks.
 *
 * The function वापसs the combined block state (true अगर transmitter
 * should be blocked) so that drivers need not keep track of the soft
 * block state -- which they might not be able to.
 */
अटल अंतरभूत bool rfसमाप्त_set_hw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	वापस rfसमाप्त_set_hw_state_reason(rfसमाप्त, blocked,
					  RFKILL_HARD_BLOCK_SIGNAL);
पूर्ण

/**
 * rfसमाप्त_set_sw_state - Set the पूर्णांकernal rfसमाप्त software block state
 * @rfसमाप्त: poपूर्णांकer to the rfसमाप्त class to modअगरy.
 * @blocked: the current software block state to set
 *
 * rfसमाप्त drivers that get events when the soft-blocked state changes
 * (yes, some platक्रमms directly act on input but allow changing again)
 * use this function to notअगरy the rfसमाप्त core (and through that also
 * userspace) of the current state.
 *
 * Drivers should also call this function after resume अगर the state has
 * been changed by the user.  This only makes sense क्रम "persistent"
 * devices (see rfसमाप्त_init_sw_state()).
 *
 * This function can be called in any context, even from within rfसमाप्त
 * callbacks.
 *
 * The function वापसs the combined block state (true अगर transmitter
 * should be blocked).
 */
bool rfसमाप्त_set_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked);

/**
 * rfसमाप्त_init_sw_state - Initialize persistent software block state
 * @rfसमाप्त: poपूर्णांकer to the rfसमाप्त class to modअगरy.
 * @blocked: the current software block state to set
 *
 * rfसमाप्त drivers that preserve their software block state over घातer off
 * use this function to notअगरy the rfसमाप्त core (and through that also
 * userspace) of their initial state.  It should only be used beक्रमe
 * registration.
 *
 * In addition, it marks the device as "persistent", an attribute which
 * can be पढ़ो by userspace.  Persistent devices are expected to preserve
 * their own state when suspended.
 */
व्योम rfसमाप्त_init_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked);

/**
 * rfसमाप्त_set_states - Set the पूर्णांकernal rfसमाप्त block states
 * @rfसमाप्त: poपूर्णांकer to the rfसमाप्त class to modअगरy.
 * @sw: the current software block state to set
 * @hw: the current hardware block state to set
 *
 * This function can be called in any context, even from within rfसमाप्त
 * callbacks.
 */
व्योम rfसमाप्त_set_states(काष्ठा rfसमाप्त *rfसमाप्त, bool sw, bool hw);

/**
 * rfसमाप्त_blocked - Query rfसमाप्त block state
 *
 * @rfसमाप्त: rfसमाप्त काष्ठा to query
 */
bool rfसमाप्त_blocked(काष्ठा rfसमाप्त *rfसमाप्त);

/**
 * rfसमाप्त_find_type - Helper क्रम finding rfसमाप्त type by name
 * @name: the name of the type
 *
 * Returns क्रमागत rfसमाप्त_type that corresponds to the name.
 */
क्रमागत rfसमाप्त_type rfसमाप्त_find_type(स्थिर अक्षर *name);

#अन्यथा /* !RFKILL */
अटल अंतरभूत काष्ठा rfसमाप्त * __must_check
rfसमाप्त_alloc(स्थिर अक्षर *name,
	     काष्ठा device *parent,
	     स्थिर क्रमागत rfसमाप्त_type type,
	     स्थिर काष्ठा rfसमाप्त_ops *ops,
	     व्योम *ops_data)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check rfसमाप्त_रेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	अगर (rfसमाप्त == ERR_PTR(-ENODEV))
		वापस 0;
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम rfसमाप्त_छोड़ो_polling(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
पूर्ण

अटल अंतरभूत व्योम rfसमाप्त_resume_polling(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
पूर्ण

अटल अंतरभूत व्योम rfसमाप्त_unरेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
पूर्ण

अटल अंतरभूत व्योम rfसमाप्त_destroy(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
पूर्ण

अटल अंतरभूत bool rfसमाप्त_set_hw_state_reason(काष्ठा rfसमाप्त *rfसमाप्त,
					      bool blocked,
					      अचिन्हित दीर्घ reason)
अणु
	वापस blocked;
पूर्ण

अटल अंतरभूत bool rfसमाप्त_set_hw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	वापस blocked;
पूर्ण

अटल अंतरभूत bool rfसमाप्त_set_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	वापस blocked;
पूर्ण

अटल अंतरभूत व्योम rfसमाप्त_init_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
पूर्ण

अटल अंतरभूत व्योम rfसमाप्त_set_states(काष्ठा rfसमाप्त *rfसमाप्त, bool sw, bool hw)
अणु
पूर्ण

अटल अंतरभूत bool rfसमाप्त_blocked(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत क्रमागत rfसमाप्त_type rfसमाप्त_find_type(स्थिर अक्षर *name)
अणु
	वापस RFKILL_TYPE_ALL;
पूर्ण

#पूर्ण_अगर /* RFKILL || RFKILL_MODULE */


#अगर_घोषित CONFIG_RFKILL_LEDS
/**
 * rfसमाप्त_get_led_trigger_name - Get the LED trigger name क्रम the button's LED.
 * This function might वापस a शून्य poपूर्णांकer अगर रेजिस्टरing of the
 * LED trigger failed. Use this as "default_trigger" क्रम the LED.
 */
स्थिर अक्षर *rfसमाप्त_get_led_trigger_name(काष्ठा rfसमाप्त *rfसमाप्त);

/**
 * rfसमाप्त_set_led_trigger_name - Set the LED trigger name
 * @rfसमाप्त: rfसमाप्त काष्ठा
 * @name: LED trigger name
 *
 * This function sets the LED trigger name of the radio LED
 * trigger that rfसमाप्त creates. It is optional, but अगर called
 * must be called beक्रमe rfसमाप्त_रेजिस्टर() to be effective.
 */
व्योम rfसमाप्त_set_led_trigger_name(काष्ठा rfसमाप्त *rfसमाप्त, स्थिर अक्षर *name);
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *rfसमाप्त_get_led_trigger_name(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
rfसमाप्त_set_led_trigger_name(काष्ठा rfसमाप्त *rfसमाप्त, स्थिर अक्षर *name)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* RFKILL_H */
