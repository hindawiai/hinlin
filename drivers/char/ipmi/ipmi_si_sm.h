<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ipmi_si_sm.h
 *
 * State machine पूर्णांकerface क्रम low-level IPMI प्रणाली management
 * पूर्णांकerface state machines.  This code is the पूर्णांकerface between
 * the ipmi_smi code (that handles the policy of a KCS, SMIC, or
 * BT पूर्णांकerface) and the actual low-level state machine.
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 */

#अगर_अघोषित __IPMI_SI_SM_H__
#घोषणा __IPMI_SI_SM_H__

#समावेश "ipmi_si.h"

/*
 * This is defined by the state machines themselves, it is an opaque
 * data type क्रम them to use.
 */
काष्ठा si_sm_data;

/* Results of SMI events. */
क्रमागत si_sm_result अणु
	SI_SM_CALL_WITHOUT_DELAY, /* Call the driver again immediately */
	SI_SM_CALL_WITH_DELAY,	/* Delay some beक्रमe calling again. */
	SI_SM_CALL_WITH_TICK_DELAY,/* Delay >=1 tick beक्रमe calling again. */
	SI_SM_TRANSACTION_COMPLETE, /* A transaction is finished. */
	SI_SM_IDLE,		/* The SM is in idle state. */
	SI_SM_HOSED,		/* The hardware violated the state machine. */

	/*
	 * The hardware is निश्चितing attn and the state machine is
	 * idle.
	 */
	SI_SM_ATTN
पूर्ण;

/* Handlers क्रम the SMI state machine. */
काष्ठा si_sm_handlers अणु
	/*
	 * Put the version number of the state machine here so the
	 * upper layer can prपूर्णांक it.
	 */
	अक्षर *version;

	/*
	 * Initialize the data and वापस the amount of I/O space to
	 * reserve क्रम the space.
	 */
	अचिन्हित पूर्णांक (*init_data)(काष्ठा si_sm_data *smi,
				  काष्ठा si_sm_io   *io);

	/*
	 * Start a new transaction in the state machine.  This will
	 * वापस -2 अगर the state machine is not idle, -1 अगर the size
	 * is invalid (to large or too small), or 0 अगर the transaction
	 * is successfully completed.
	 */
	पूर्णांक (*start_transaction)(काष्ठा si_sm_data *smi,
				 अचिन्हित अक्षर *data, अचिन्हित पूर्णांक size);

	/*
	 * Return the results after the transaction.  This will वापस
	 * -1 अगर the buffer is too small, zero अगर no transaction is
	 * present, or the actual length of the result data.
	 */
	पूर्णांक (*get_result)(काष्ठा si_sm_data *smi,
			  अचिन्हित अक्षर *data, अचिन्हित पूर्णांक length);

	/*
	 * Call this periodically (क्रम a polled पूर्णांकerface) or upon
	 * receiving an पूर्णांकerrupt (क्रम a पूर्णांकerrupt-driven पूर्णांकerface).
	 * If पूर्णांकerrupt driven, you should probably poll this
	 * periodically when not in idle state.  This should be called
	 * with the समय that passed since the last call, अगर it is
	 * signअगरicant.  Time is in microseconds.
	 */
	क्रमागत si_sm_result (*event)(काष्ठा si_sm_data *smi, दीर्घ समय);

	/*
	 * Attempt to detect an SMI.  Returns 0 on success or nonzero
	 * on failure.
	 */
	पूर्णांक (*detect)(काष्ठा si_sm_data *smi);

	/* The पूर्णांकerface is shutting करोwn, so clean it up. */
	व्योम (*cleanup)(काष्ठा si_sm_data *smi);

	/* Return the size of the SMI काष्ठाure in bytes. */
	पूर्णांक (*size)(व्योम);
पूर्ण;

/* Current state machines that we can use. */
बाह्य स्थिर काष्ठा si_sm_handlers kcs_smi_handlers;
बाह्य स्थिर काष्ठा si_sm_handlers smic_smi_handlers;
बाह्य स्थिर काष्ठा si_sm_handlers bt_smi_handlers;

#पूर्ण_अगर /* __IPMI_SI_SM_H__ */
