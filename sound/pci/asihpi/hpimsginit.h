<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


 Hardware Programming Interface (HPI) Utility functions

 (C) Copyright AudioScience Inc. 2007
*******************************************************************************/
/* Initialise response headers, or msg/response pairs.
Note that it is valid to just init a response e.g. when a lower level is
preparing a response to a message.
However, when sending a message, a matching response buffer must always be
prepared.
*/

#अगर_अघोषित _HPIMSGINIT_H_
#घोषणा _HPIMSGINIT_H_

व्योम hpi_init_response(काष्ठा hpi_response *phr, u16 object, u16 function,
	u16 error);

व्योम hpi_init_message_response(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr, u16 object, u16 function);

व्योम hpi_init_responseV1(काष्ठा hpi_response_header *phr, u16 size,
	u16 object, u16 function);

व्योम hpi_init_message_responseV1(काष्ठा hpi_message_header *phm, u16 msg_size,
	काष्ठा hpi_response_header *phr, u16 res_size, u16 object,
	u16 function);

#पूर्ण_अगर				/* _HPIMSGINIT_H_ */
