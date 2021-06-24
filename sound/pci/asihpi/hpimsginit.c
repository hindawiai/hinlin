<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2014  AudioScience Inc. <support@audioscience.com>


 Hardware Programming Interface (HPI) Utility functions.

 (C) Copyright AudioScience Inc. 2007
*******************************************************************************/

#समावेश "hpi_internal.h"
#समावेश "hpimsginit.h"
#समावेश <linux/nospec.h>

/* The actual message size क्रम each object type */
अटल u16 msg_size[HPI_OBJ_MAXINDEX + 1] = HPI_MESSAGE_SIZE_BY_OBJECT;
/* The actual response size क्रम each object type */
अटल u16 res_size[HPI_OBJ_MAXINDEX + 1] = HPI_RESPONSE_SIZE_BY_OBJECT;
/* Flag to enable alternate message type क्रम SSX2 bypass. */
अटल u16 gwSSX2_bypass;

/** \पूर्णांकernal
  * initialize the HPI message काष्ठाure
  */
अटल व्योम hpi_init_message(काष्ठा hpi_message *phm, u16 object,
	u16 function)
अणु
	u16 size;

	अगर ((object > 0) && (object <= HPI_OBJ_MAXINDEX)) अणु
		object = array_index_nospec(object, HPI_OBJ_MAXINDEX + 1);
		size = msg_size[object];
	पूर्ण अन्यथा अणु
		size = माप(*phm);
	पूर्ण

	स_रखो(phm, 0, size);
	phm->size = size;

	अगर (gwSSX2_bypass)
		phm->type = HPI_TYPE_SSX2BYPASS_MESSAGE;
	अन्यथा
		phm->type = HPI_TYPE_REQUEST;
	phm->object = object;
	phm->function = function;
	phm->version = 0;
	phm->adapter_index = HPI_ADAPTER_INDEX_INVALID;
	/* Expect actual adapter index to be set by caller */
पूर्ण

/** \पूर्णांकernal
  * initialize the HPI response काष्ठाure
  */
व्योम hpi_init_response(काष्ठा hpi_response *phr, u16 object, u16 function,
	u16 error)
अणु
	u16 size;

	अगर ((object > 0) && (object <= HPI_OBJ_MAXINDEX)) अणु
		object = array_index_nospec(object, HPI_OBJ_MAXINDEX + 1);
		size = res_size[object];
	पूर्ण अन्यथा अणु
		size = माप(*phr);
	पूर्ण

	स_रखो(phr, 0, माप(*phr));
	phr->size = size;
	phr->type = HPI_TYPE_RESPONSE;
	phr->object = object;
	phr->function = function;
	phr->error = error;
	phr->specअगरic_error = 0;
	phr->version = 0;
पूर्ण

व्योम hpi_init_message_response(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr, u16 object, u16 function)
अणु
	hpi_init_message(phm, object, function);
	/* शेष error वापस अगर the response is
	   not filled in by the callee */
	hpi_init_response(phr, object, function,
		HPI_ERROR_PROCESSING_MESSAGE);
पूर्ण

अटल व्योम hpi_init_messageV1(काष्ठा hpi_message_header *phm, u16 size,
	u16 object, u16 function)
अणु
	स_रखो(phm, 0, size);
	अगर ((object > 0) && (object <= HPI_OBJ_MAXINDEX)) अणु
		phm->size = size;
		phm->type = HPI_TYPE_REQUEST;
		phm->object = object;
		phm->function = function;
		phm->version = 1;
		/* Expect adapter index to be set by caller */
	पूर्ण
पूर्ण

व्योम hpi_init_responseV1(काष्ठा hpi_response_header *phr, u16 size,
	u16 object, u16 function)
अणु
	(व्योम)object;
	(व्योम)function;
	स_रखो(phr, 0, size);
	phr->size = size;
	phr->version = 1;
	phr->type = HPI_TYPE_RESPONSE;
	phr->error = HPI_ERROR_PROCESSING_MESSAGE;
पूर्ण

व्योम hpi_init_message_responseV1(काष्ठा hpi_message_header *phm, u16 msg_size,
	काष्ठा hpi_response_header *phr, u16 res_size, u16 object,
	u16 function)
अणु
	hpi_init_messageV1(phm, msg_size, object, function);
	hpi_init_responseV1(phr, res_size, object, function);
पूर्ण
