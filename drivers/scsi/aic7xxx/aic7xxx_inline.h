<शैली गुरु>
/*
 * Inline routines shareable across OS platक्रमms.
 *
 * Copyright (c) 1994-2001 Justin T. Gibbs.
 * Copyright (c) 2000-2001 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_अंतरभूत.h#43 $
 *
 * $FreeBSD$
 */

#अगर_अघोषित _AIC7XXX_INLINE_H_
#घोषणा _AIC7XXX_INLINE_H_

/************************* Sequencer Execution Control ************************/
पूर्णांक  ahc_is_छोड़ोd(काष्ठा ahc_softc *ahc);
व्योम ahc_छोड़ो(काष्ठा ahc_softc *ahc);
व्योम ahc_unछोड़ो(काष्ठा ahc_softc *ahc);

/************************** Memory mapping routines ***************************/
व्योम	ahc_sync_sglist(काष्ठा ahc_softc *ahc,
			काष्ठा scb *scb, पूर्णांक op);

/******************************** Debugging ***********************************/
अटल अंतरभूत अक्षर *ahc_name(काष्ठा ahc_softc *ahc);

अटल अंतरभूत अक्षर *ahc_name(काष्ठा ahc_softc *ahc)
अणु
	वापस (ahc->name);
पूर्ण

/*********************** Miscellaneous Support Functions ***********************/

काष्ठा ahc_initiator_tinfo *
	ahc_fetch_transinfo(काष्ठा ahc_softc *ahc,
			    अक्षर channel, u_पूर्णांक our_id,
			    u_पूर्णांक remote_id,
			    काष्ठा ahc_पंचांगode_tstate **tstate);
uपूर्णांक16_t
	ahc_inw(काष्ठा ahc_softc *ahc, u_पूर्णांक port);
व्योम	ahc_outw(काष्ठा ahc_softc *ahc, u_पूर्णांक port,
		 u_पूर्णांक value);
uपूर्णांक32_t
	ahc_inl(काष्ठा ahc_softc *ahc, u_पूर्णांक port);
व्योम	ahc_outl(काष्ठा ahc_softc *ahc, u_पूर्णांक port,
		 uपूर्णांक32_t value);
uपूर्णांक64_t
	ahc_inq(काष्ठा ahc_softc *ahc, u_पूर्णांक port);
व्योम	ahc_outq(काष्ठा ahc_softc *ahc, u_पूर्णांक port,
		 uपूर्णांक64_t value);
काष्ठा scb*
	ahc_get_scb(काष्ठा ahc_softc *ahc);
व्योम	ahc_मुक्त_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb);
काष्ठा scb *
	ahc_lookup_scb(काष्ठा ahc_softc *ahc, u_पूर्णांक tag);
व्योम	ahc_queue_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb);
काष्ठा scsi_sense_data *
	ahc_get_sense_buf(काष्ठा ahc_softc *ahc,
			  काष्ठा scb *scb);

/************************** Interrupt Processing ******************************/
पूर्णांक	ahc_पूर्णांकr(काष्ठा ahc_softc *ahc);

#पूर्ण_अगर  /* _AIC7XXX_INLINE_H_ */
