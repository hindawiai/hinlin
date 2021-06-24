<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  OSLEC - A line echo canceller.  This code is being developed
 *          against and partially complies with G168. Using code from SpanDSP
 *
 * Written by Steve Underwood <steveu@coppice.org>
 *         and David Rowe <david_at_rowetel_करोt_com>
 *
 * Copyright (C) 2001 Steve Underwood and 2007-2008 David Rowe
 *
 * All rights reserved.
 */

#अगर_अघोषित __OSLEC_H
#घोषणा __OSLEC_H

/* Mask bits क्रम the adaption mode */
#घोषणा ECHO_CAN_USE_ADAPTION	0x01
#घोषणा ECHO_CAN_USE_NLP	0x02
#घोषणा ECHO_CAN_USE_CNG	0x04
#घोषणा ECHO_CAN_USE_CLIP	0x08
#घोषणा ECHO_CAN_USE_TX_HPF	0x10
#घोषणा ECHO_CAN_USE_RX_HPF	0x20
#घोषणा ECHO_CAN_DISABLE	0x40

/**
 * oslec_state: G.168 echo canceller descriptor.
 *
 * This defines the working state क्रम a line echo canceller.
 */
काष्ठा oslec_state;

/**
 * oslec_create - Create a voice echo canceller context.
 * @len: The length of the canceller, in samples.
 * @वापस: The new canceller context, or शून्य अगर the canceller could not be
 * created.
 */
काष्ठा oslec_state *oslec_create(पूर्णांक len, पूर्णांक adaption_mode);

/**
 * oslec_मुक्त - Free a voice echo canceller context.
 * @ec: The echo canceller context.
 */
व्योम oslec_मुक्त(काष्ठा oslec_state *ec);

/**
 * oslec_flush - Flush (reinitialise) a voice echo canceller context.
 * @ec: The echo canceller context.
 */
व्योम oslec_flush(काष्ठा oslec_state *ec);

/**
 * oslec_adaption_mode - set the adaption mode of a voice echo canceller context.
 * @ec The echo canceller context.
 * @adaption_mode: The mode.
 */
व्योम oslec_adaption_mode(काष्ठा oslec_state *ec, पूर्णांक adaption_mode);

व्योम oslec_snapshot(काष्ठा oslec_state *ec);

/**
 * oslec_update: Process a sample through a voice echo canceller.
 * @ec: The echo canceller context.
 * @tx: The transmitted audio sample.
 * @rx: The received audio sample.
 *
 * The वापस value is the clean (echo cancelled) received sample.
 */
पूर्णांक16_t oslec_update(काष्ठा oslec_state *ec, पूर्णांक16_t tx, पूर्णांक16_t rx);

/**
 * oslec_hpf_tx: Process to high pass filter the tx संकेत.
 * @ec: The echo canceller context.
 * @tx: The transmitted auio sample.
 *
 * The वापस value is the HP filtered transmit sample, send this to your D/A.
 */
पूर्णांक16_t oslec_hpf_tx(काष्ठा oslec_state *ec, पूर्णांक16_t tx);

#पूर्ण_अगर /* __OSLEC_H */
