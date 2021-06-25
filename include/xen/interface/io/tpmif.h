<शैली गुरु>
/******************************************************************************
 * tpmअगर.h
 *
 * TPM I/O पूर्णांकerface क्रम Xen guest OSes, v2
 *
 * This file is in the खुला करोमुख्य.
 *
 */

#अगर_अघोषित __XEN_PUBLIC_IO_TPMIF_H__
#घोषणा __XEN_PUBLIC_IO_TPMIF_H__

/*
 * Xenbus state machine
 *
 * Device खोलो:
 *   1. Both ends start in XenbusStateInitialising
 *   2. Backend transitions to InitWait (frontend करोes not रुको on this step)
 *   3. Frontend populates ring-ref, event-channel, feature-protocol-v2
 *   4. Frontend transitions to Initialised
 *   5. Backend maps grant and event channel, verअगरies feature-protocol-v2
 *   6. Backend transitions to Connected
 *   7. Frontend verअगरies feature-protocol-v2, transitions to Connected
 *
 * Device बंद:
 *   1. State is changed to XenbusStateClosing
 *   2. Frontend transitions to Closed
 *   3. Backend unmaps grant and event, changes state to InitWait
 */

क्रमागत vtpm_shared_page_state अणु
	VTPM_STATE_IDLE,         /* no contents / vTPM idle / cancel complete */
	VTPM_STATE_SUBMIT,       /* request पढ़ोy / vTPM working */
	VTPM_STATE_FINISH,       /* response पढ़ोy / vTPM idle */
	VTPM_STATE_CANCEL,       /* cancel requested / vTPM working */
पूर्ण;
/* The backend should only change state to IDLE or FINISH, जबतक the
 * frontend should only change to SUBMIT or CANCEL. */


काष्ठा vtpm_shared_page अणु
	uपूर्णांक32_t length;         /* request/response length in bytes */

	uपूर्णांक8_t state;           /* क्रमागत vtpm_shared_page_state */
	uपूर्णांक8_t locality;        /* क्रम the current request */
	uपूर्णांक8_t pad;

	uपूर्णांक8_t nr_extra_pages;  /* extra pages क्रम दीर्घ packets; may be zero */
	uपूर्णांक32_t extra_pages[]; /* grant IDs; length in nr_extra_pages */
पूर्ण;

#पूर्ण_अगर
