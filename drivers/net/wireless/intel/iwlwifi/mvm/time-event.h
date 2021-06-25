<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2019-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 */
#अगर_अघोषित __समय_event_h__
#घोषणा __समय_event_h__

#समावेश "fw-api.h"

#समावेश "mvm.h"

/**
 * DOC: Time Events - what is it?
 *
 * Time Events are a fw feature that allows the driver to control the presence
 * of the device on the channel. Since the fw supports multiple channels
 * concurrently, the fw may choose to jump to another channel at any समय.
 * In order to make sure that the fw is on a specअगरic channel at a certain समय
 * and क्रम a certain duration, the driver needs to issue a समय event.
 *
 * The simplest example is क्रम BSS association. The driver issues a समय event,
 * रुकोs क्रम it to start, and only then tells mac80211 that we can start the
 * association. This way, we make sure that the association will be करोne
 * smoothly and won't be पूर्णांकerrupted by channel चयन decided within the fw.
 */

 /**
 * DOC: The flow against the fw
 *
 * When the driver needs to make sure we are in a certain channel, at a certain
 * समय and क्रम a certain duration, it sends a Time Event. The flow against the
 * fw goes like this:
 *	1) Driver sends a TIME_EVENT_CMD to the fw
 *	2) Driver माला_लो the response क्रम that command. This response contains the
 *	   Unique ID (UID) of the event.
 *	3) The fw sends notअगरication when the event starts.
 *
 * Of course the API provides various options that allow to cover parameters
 * of the flow.
 *	What is the duration of the event?
 *	What is the start समय of the event?
 *	Is there an end-समय क्रम the event?
 *	How much can the event be delayed?
 *	Can the event be split?
 *	If yes what is the maximal number of chunks?
 *	etc...
 */

/**
 * DOC: Abstraction to the driver
 *
 * In order to simplअगरy the use of समय events to the rest of the driver,
 * we असलtract the use of समय events. This component provides the functions
 * needed by the driver.
 */

#घोषणा IWL_MVM_TE_SESSION_PROTECTION_MAX_TIME_MS 600
#घोषणा IWL_MVM_TE_SESSION_PROTECTION_MIN_TIME_MS 400

/**
 * iwl_mvm_protect_session - start / extend the session protection.
 * @mvm: the mvm component
 * @vअगर: the भव पूर्णांकerface क्रम which the session is issued
 * @duration: the duration of the session in TU.
 * @min_duration: will start a new session अगर the current session will end
 *	in less than min_duration.
 * @max_delay: maximum delay beक्रमe starting the समय event (in TU)
 * @रुको_क्रम_notअगर: true अगर it is required that a समय event notअगरication be
 *	रुकोed क्रम (that the समय event has been scheduled beक्रमe वापसing)
 *
 * This function can be used to start a session protection which means that the
 * fw will stay on the channel क्रम %duration_ms milliseconds. This function
 * can block (sleep) until the session starts. This function can also be used
 * to extend a currently running session.
 * This function is meant to be used क्रम BSS association क्रम example, where we
 * want to make sure that the fw stays on the channel during the association.
 */
व्योम iwl_mvm_protect_session(काष्ठा iwl_mvm *mvm,
			     काष्ठा ieee80211_vअगर *vअगर,
			     u32 duration, u32 min_duration,
			     u32 max_delay, bool रुको_क्रम_notअगर);

/**
 * iwl_mvm_stop_session_protection - cancel the session protection.
 * @mvm: the mvm component
 * @vअगर: the भव पूर्णांकerface क्रम which the session is issued
 *
 * This functions cancels the session protection which is an act of good
 * citizenship. If it is not needed any more it should be canceled because
 * the other bindings रुको क्रम the medium during that समय.
 * This funtions करोesn't sleep.
 */
व्योम iwl_mvm_stop_session_protection(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_vअगर *vअगर);

/*
 * iwl_mvm_rx_समय_event_notअगर - handles %TIME_EVENT_NOTIFICATION.
 */
व्योम iwl_mvm_rx_समय_event_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb);

/**
 * iwl_mvm_start_p2p_roc - start reमुख्य on channel क्रम p2p device functionality
 * @mvm: the mvm component
 * @vअगर: the भव पूर्णांकerface क्रम which the roc is requested. It is assumed
 * that the vअगर type is NL80211_IFTYPE_P2P_DEVICE
 * @duration: the requested duration in millisecond क्रम the fw to be on the
 * channel that is bound to the vअगर.
 * @type: the reमुख्य on channel request type
 *
 * This function can be used to issue a reमुख्य on channel session,
 * which means that the fw will stay in the channel क्रम the request %duration
 * milliseconds. The function is async, meaning that it only issues the ROC
 * request but करोes not रुको क्रम it to start. Once the FW is पढ़ोy to serve the
 * ROC request, it will issue a notअगरication to the driver that it is on the
 * requested channel. Once the FW completes the ROC request it will issue
 * another notअगरication to the driver.
 */
पूर्णांक iwl_mvm_start_p2p_roc(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			  पूर्णांक duration, क्रमागत ieee80211_roc_type type);

/**
 * iwl_mvm_stop_roc - stop reमुख्य on channel functionality
 * @mvm: the mvm component
 * @vअगर: the भव पूर्णांकerface क्रम which the roc is stopped
 *
 * This function can be used to cancel an ongoing ROC session.
 * The function is async, it will inकाष्ठा the FW to stop serving the ROC
 * session, but will not रुको क्रम the actual stopping of the session.
 */
व्योम iwl_mvm_stop_roc(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);

/**
 * iwl_mvm_हटाओ_समय_event - general function to clean up of समय event
 * @mvm: the mvm component
 * @vअगर: the vअगर to which the समय event beदीर्घs
 * @te_data: the समय event data that corresponds to that समय event
 *
 * This function can be used to cancel a समय event regardless its type.
 * It is useful क्रम cleaning up समय events running beक्रमe removing an
 * पूर्णांकerface.
 */
व्योम iwl_mvm_हटाओ_समय_event(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_mvm_vअगर *mvmvअगर,
			       काष्ठा iwl_mvm_समय_event_data *te_data);

/**
 * iwl_mvm_te_clear_data - हटाओ समय event from list
 * @mvm: the mvm component
 * @te_data: the समय event data to हटाओ
 *
 * This function is mostly पूर्णांकernal, it is made available here only
 * क्रम firmware restart purposes.
 */
व्योम iwl_mvm_te_clear_data(काष्ठा iwl_mvm *mvm,
			   काष्ठा iwl_mvm_समय_event_data *te_data);

व्योम iwl_mvm_cleanup_roc_te(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_roc_करोne_wk(काष्ठा work_काष्ठा *wk);

व्योम iwl_mvm_हटाओ_csa_period(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_vअगर *vअगर);

/**
 * iwl_mvm_schedule_csa_period - request channel चयन असलence period
 * @mvm: the mvm component
 * @vअगर: the भव पूर्णांकerface क्रम which the channel चयन is issued
 * @duration: the duration of the NoA in TU.
 * @apply_समय: NoA start समय in GP2.
 *
 * This function is used to schedule NoA समय event and is used to perक्रमm
 * the channel चयन flow.
 */
पूर्णांक iwl_mvm_schedule_csa_period(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_vअगर *vअगर,
				u32 duration, u32 apply_समय);

/**
 * iwl_mvm_te_scheduled - check अगर the fw received the TE cmd
 * @te_data: the समय event data that corresponds to that समय event
 *
 * This function वापसs true अगरf this TE is added to the fw.
 */
अटल अंतरभूत bool
iwl_mvm_te_scheduled(काष्ठा iwl_mvm_समय_event_data *te_data)
अणु
	अगर (!te_data)
		वापस false;

	वापस !!te_data->uid;
पूर्ण

/**
 * iwl_mvm_schedule_session_protection - schedule a session protection
 * @mvm: the mvm component
 * @vअगर: the भव पूर्णांकerface क्रम which the protection issued
 * @duration: the duration of the protection
 * @रुको_क्रम_notअगर: अगर true, will block until the start of the protection
 */
व्योम iwl_mvm_schedule_session_protection(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 u32 duration, u32 min_duration,
					 bool रुको_क्रम_notअगर);

/**
 * iwl_mvm_rx_session_protect_notअगर - handles %SESSION_PROTECTION_NOTIF
 */
व्योम iwl_mvm_rx_session_protect_notअगर(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_rx_cmd_buffer *rxb);

#पूर्ण_अगर /* __समय_event_h__ */
