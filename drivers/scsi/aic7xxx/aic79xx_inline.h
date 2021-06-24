<शैली गुरु>
/*
 * Inline routines shareable across OS platक्रमms.
 *
 * Copyright (c) 1994-2001 Justin T. Gibbs.
 * Copyright (c) 2000-2003 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx_अंतरभूत.h#59 $
 *
 * $FreeBSD$
 */

#अगर_अघोषित _AIC79XX_INLINE_H_
#घोषणा _AIC79XX_INLINE_H_

/******************************** Debugging ***********************************/
अटल अंतरभूत अक्षर *ahd_name(काष्ठा ahd_softc *ahd);

अटल अंतरभूत अक्षर *ahd_name(काष्ठा ahd_softc *ahd)
अणु
	वापस (ahd->name);
पूर्ण

/************************ Sequencer Execution Control *************************/
अटल अंतरभूत व्योम ahd_known_modes(काष्ठा ahd_softc *ahd,
				     ahd_mode src, ahd_mode dst);
अटल अंतरभूत ahd_mode_state ahd_build_mode_state(काष्ठा ahd_softc *ahd,
						    ahd_mode src,
						    ahd_mode dst);
अटल अंतरभूत व्योम ahd_extract_mode_state(काष्ठा ahd_softc *ahd,
					    ahd_mode_state state,
					    ahd_mode *src, ahd_mode *dst);

व्योम ahd_set_modes(काष्ठा ahd_softc *ahd, ahd_mode src,
		   ahd_mode dst);
ahd_mode_state ahd_save_modes(काष्ठा ahd_softc *ahd);
व्योम ahd_restore_modes(काष्ठा ahd_softc *ahd,
		       ahd_mode_state state);
पूर्णांक  ahd_is_छोड़ोd(काष्ठा ahd_softc *ahd);
व्योम ahd_छोड़ो(काष्ठा ahd_softc *ahd);
व्योम ahd_unछोड़ो(काष्ठा ahd_softc *ahd);

अटल अंतरभूत व्योम
ahd_known_modes(काष्ठा ahd_softc *ahd, ahd_mode src, ahd_mode dst)
अणु
	ahd->src_mode = src;
	ahd->dst_mode = dst;
	ahd->saved_src_mode = src;
	ahd->saved_dst_mode = dst;
पूर्ण

अटल अंतरभूत ahd_mode_state
ahd_build_mode_state(काष्ठा ahd_softc *ahd, ahd_mode src, ahd_mode dst)
अणु
	वापस ((src << SRC_MODE_SHIFT) | (dst << DST_MODE_SHIFT));
पूर्ण

अटल अंतरभूत व्योम
ahd_extract_mode_state(काष्ठा ahd_softc *ahd, ahd_mode_state state,
		       ahd_mode *src, ahd_mode *dst)
अणु
	*src = (state & SRC_MODE) >> SRC_MODE_SHIFT;
	*dst = (state & DST_MODE) >> DST_MODE_SHIFT;
पूर्ण

/*********************** Scatter Gather List Handling *************************/
व्योम	*ahd_sg_setup(काष्ठा ahd_softc *ahd, काष्ठा scb *scb,
		      व्योम *sgptr, dma_addr_t addr,
		      bus_माप_प्रकार len, पूर्णांक last);

/************************** Memory mapping routines ***************************/
अटल अंतरभूत माप_प्रकार	ahd_sg_size(काष्ठा ahd_softc *ahd);

व्योम	ahd_sync_sglist(काष्ठा ahd_softc *ahd,
			काष्ठा scb *scb, पूर्णांक op);

अटल अंतरभूत माप_प्रकार ahd_sg_size(काष्ठा ahd_softc *ahd)
अणु
	अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0)
		वापस (माप(काष्ठा ahd_dma64_seg));
	वापस (माप(काष्ठा ahd_dma_seg));
पूर्ण

/*********************** Miscellaneous Support Functions ***********************/
काष्ठा ahd_initiator_tinfo *
	ahd_fetch_transinfo(काष्ठा ahd_softc *ahd,
			    अक्षर channel, u_पूर्णांक our_id,
			    u_पूर्णांक remote_id,
			    काष्ठा ahd_पंचांगode_tstate **tstate);
uपूर्णांक16_t
	ahd_inw(काष्ठा ahd_softc *ahd, u_पूर्णांक port);
व्योम	ahd_outw(काष्ठा ahd_softc *ahd, u_पूर्णांक port,
		 u_पूर्णांक value);
uपूर्णांक32_t
	ahd_inl(काष्ठा ahd_softc *ahd, u_पूर्णांक port);
व्योम	ahd_outl(काष्ठा ahd_softc *ahd, u_पूर्णांक port,
		 uपूर्णांक32_t value);
uपूर्णांक64_t
	ahd_inq(काष्ठा ahd_softc *ahd, u_पूर्णांक port);
व्योम	ahd_outq(काष्ठा ahd_softc *ahd, u_पूर्णांक port,
		 uपूर्णांक64_t value);
u_पूर्णांक	ahd_get_scbptr(काष्ठा ahd_softc *ahd);
व्योम	ahd_set_scbptr(काष्ठा ahd_softc *ahd, u_पूर्णांक scbptr);
u_पूर्णांक	ahd_inb_scbram(काष्ठा ahd_softc *ahd, u_पूर्णांक offset);
u_पूर्णांक	ahd_inw_scbram(काष्ठा ahd_softc *ahd, u_पूर्णांक offset);
काष्ठा scb *
	ahd_lookup_scb(काष्ठा ahd_softc *ahd, u_पूर्णांक tag);
व्योम	ahd_queue_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb);

अटल अंतरभूत uपूर्णांक8_t *ahd_get_sense_buf(काष्ठा ahd_softc *ahd,
					  काष्ठा scb *scb);
अटल अंतरभूत uपूर्णांक32_t ahd_get_sense_bufaddr(काष्ठा ahd_softc *ahd,
					      काष्ठा scb *scb);

#अगर 0 /* unused */

#घोषणा AHD_COPY_COL_IDX(dst, src)				\
करो अणु								\
	dst->hscb->scsiid = src->hscb->scsiid;			\
	dst->hscb->lun = src->hscb->lun;			\
पूर्ण जबतक (0)

#पूर्ण_अगर

अटल अंतरभूत uपूर्णांक8_t *
ahd_get_sense_buf(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	वापस (scb->sense_data);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
ahd_get_sense_bufaddr(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	वापस (scb->sense_busaddr);
पूर्ण

/************************** Interrupt Processing ******************************/
पूर्णांक	ahd_पूर्णांकr(काष्ठा ahd_softc *ahd);

#पूर्ण_अगर  /* _AIC79XX_INLINE_H_ */
