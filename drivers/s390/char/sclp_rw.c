<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * driver: पढ़ोing from and writing to प्रणाली console on S/390 via SCLP
 *
 * Copyright IBM Corp. 1999, 2009
 *
 * Author(s): Martin Peschke <mpeschke@de.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kmod.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/uaccess.h>

#समावेश "sclp.h"
#समावेश "sclp_rw.h"

/*
 * The room क्रम the SCCB (only क्रम writing) is not equal to a pages size
 * (as it is specअगरied as the maximum size in the SCLP करोcumentation)
 * because of the additional data काष्ठाure described above.
 */
#घोषणा MAX_SCCB_ROOM (PAGE_SIZE - माप(काष्ठा sclp_buffer))

अटल व्योम sclp_rw_pm_event(काष्ठा sclp_रेजिस्टर *reg,
			     क्रमागत sclp_pm_event sclp_pm_event)
अणु
	sclp_console_pm_event(sclp_pm_event);
पूर्ण

/* Event type काष्ठाure क्रम ग_लिखो message and ग_लिखो priority message */
अटल काष्ठा sclp_रेजिस्टर sclp_rw_event = अणु
	.send_mask = EVTYP_MSG_MASK,
	.pm_event_fn = sclp_rw_pm_event,
पूर्ण;

/*
 * Setup a sclp ग_लिखो buffer. Gets a page as input (4K) and वापसs
 * a poपूर्णांकer to a काष्ठा sclp_buffer काष्ठाure that is located at the
 * end of the input page. This reduces the buffer space by a few
 * bytes but simplअगरies things.
 */
काष्ठा sclp_buffer *
sclp_make_buffer(व्योम *page, अचिन्हित लघु columns, अचिन्हित लघु htab)
अणु
	काष्ठा sclp_buffer *buffer;
	काष्ठा sccb_header *sccb;

	sccb = (काष्ठा sccb_header *) page;
	/*
	 * We keep the काष्ठा sclp_buffer काष्ठाure at the end
	 * of the sccb page.
	 */
	buffer = ((काष्ठा sclp_buffer *) ((addr_t) sccb + PAGE_SIZE)) - 1;
	buffer->sccb = sccb;
	buffer->retry_count = 0;
	buffer->messages = 0;
	buffer->अक्षर_sum = 0;
	buffer->current_line = शून्य;
	buffer->current_length = 0;
	buffer->columns = columns;
	buffer->htab = htab;

	/* initialize sccb */
	स_रखो(sccb, 0, माप(काष्ठा sccb_header));
	sccb->length = माप(काष्ठा sccb_header);

	वापस buffer;
पूर्ण

/*
 * Return a poपूर्णांकer to the original page that has been used to create
 * the buffer.
 */
व्योम *
sclp_unmake_buffer(काष्ठा sclp_buffer *buffer)
अणु
	वापस buffer->sccb;
पूर्ण

/*
 * Initialize a new message the end of the provided buffer with
 * enough room क्रम max_len अक्षरacters. Return 0 on success.
 */
अटल पूर्णांक
sclp_initialize_mto(काष्ठा sclp_buffer *buffer, पूर्णांक max_len)
अणु
	काष्ठा sccb_header *sccb;
	काष्ठा msg_buf *msg;
	काष्ठा mdb *mdb;
	काष्ठा go *go;
	काष्ठा mto *mto;
	पूर्णांक msg_size;

	/* max size of new message including message text  */
	msg_size = माप(काष्ठा msg_buf) + max_len;

	/* check अगर current buffer sccb can contain the mto */
	sccb = buffer->sccb;
	अगर ((MAX_SCCB_ROOM - sccb->length) < msg_size)
		वापस -ENOMEM;

	msg = (काष्ठा msg_buf *)((addr_t) sccb + sccb->length);
	स_रखो(msg, 0, माप(काष्ठा msg_buf));
	msg->header.length = माप(काष्ठा msg_buf);
	msg->header.type = EVTYP_MSG;

	mdb = &msg->mdb;
	mdb->header.length = माप(काष्ठा mdb);
	mdb->header.type = 1;
	mdb->header.tag = 0xD4C4C240;	/* ebcdic "MDB " */
	mdb->header.revision_code = 1;

	go = &mdb->go;
	go->length = माप(काष्ठा go);
	go->type = 1;

	mto = &mdb->mto;
	mto->length = माप(काष्ठा mto);
	mto->type = 4;	/* message text object */
	mto->line_type_flags = LNTPFLGS_ENDTEXT; /* end text */

	/* set poपूर्णांकer to first byte after काष्ठा mto. */
	buffer->current_msg = msg;
	buffer->current_line = (अक्षर *) (mto + 1);
	buffer->current_length = 0;

	वापस 0;
पूर्ण

/*
 * Finalize message initialized by sclp_initialize_mto(),
 * updating the sizes of MTO, enclosing MDB, event buffer and SCCB.
 */
अटल व्योम
sclp_finalize_mto(काष्ठा sclp_buffer *buffer)
अणु
	काष्ठा sccb_header *sccb;
	काष्ठा msg_buf *msg;

	/*
	 * update values of sizes
	 * (SCCB, Event(Message) Buffer, Message Data Block)
	 */
	sccb = buffer->sccb;
	msg = buffer->current_msg;
	msg->header.length += buffer->current_length;
	msg->mdb.header.length += buffer->current_length;
	msg->mdb.mto.length += buffer->current_length;
	sccb->length += msg->header.length;

	/*
	 * count number of buffered messages (= number of Message Text
	 * Objects) and number of buffered अक्षरacters
	 * क्रम the SCCB currently used क्रम buffering and at all
	 */
	buffer->messages++;
	buffer->अक्षर_sum += buffer->current_length;

	buffer->current_line = शून्य;
	buffer->current_length = 0;
	buffer->current_msg = शून्य;
पूर्ण

/*
 * processing of a message including escape अक्षरacters,
 * वापसs number of अक्षरacters written to the output sccb
 * ("processed" means that is not guaranteed that the अक्षरacter have alपढ़ोy
 *  been sent to the SCLP but that it will be करोne at least next समय the SCLP
 *  is not busy)
 */
पूर्णांक
sclp_ग_लिखो(काष्ठा sclp_buffer *buffer, स्थिर अचिन्हित अक्षर *msg, पूर्णांक count)
अणु
	पूर्णांक spaces, i_msg;
	पूर्णांक rc;

	/*
	 * parse msg क्रम escape sequences (\ट,\ख ...) and put क्रमmated
	 * msg पूर्णांकo an mto (created by sclp_initialize_mto).
	 *
	 * We have to करो this work ourselfs because there is no support क्रम
	 * these अक्षरacters on the native machine and only partial support
	 * under VM (Why करोes VM पूर्णांकerpret \न but the native machine करोesn't ?)
	 *
	 * Depending on i/o-control setting the message is always written
	 * immediately or we रुको क्रम a final new line maybe coming with the
	 * next message. Besides we aव्योम a buffer overrun by writing its
	 * content.
	 *
	 * RESTRICTIONS:
	 *
	 * \ल and \म work within one line because we are not able to modअगरy
	 * previous output that have alपढ़ोy been accepted by the SCLP.
	 *
	 * \ट combined with following \ल is not correctly represented because
	 * \ट is expanded to some spaces but \ल करोes not know about a
	 * previous \ट and decreases the current position by one column.
	 * This is in order to a slim and quick implementation.
	 */
	क्रम (i_msg = 0; i_msg < count; i_msg++) अणु
		चयन (msg[i_msg]) अणु
		हाल '\n':	/* new line, line feed (ASCII)	*/
			/* check अगर new mto needs to be created */
			अगर (buffer->current_line == शून्य) अणु
				rc = sclp_initialize_mto(buffer, 0);
				अगर (rc)
					वापस i_msg;
			पूर्ण
			sclp_finalize_mto(buffer);
			अवरोध;
		हाल '\a':	/* bell, one क्रम several बार	*/
			/* set SCLP sound alarm bit in General Object */
			अगर (buffer->current_line == शून्य) अणु
				rc = sclp_initialize_mto(buffer,
							 buffer->columns);
				अगर (rc)
					वापस i_msg;
			पूर्ण
			buffer->current_msg->mdb.go.general_msg_flags |=
				GNRLMSGFLGS_SNDALRM;
			अवरोध;
		हाल '\t':	/* horizontal tabulator	 */
			/* check अगर new mto needs to be created */
			अगर (buffer->current_line == शून्य) अणु
				rc = sclp_initialize_mto(buffer,
							 buffer->columns);
				अगर (rc)
					वापस i_msg;
			पूर्ण
			/* "go to (next htab-boundary + 1, same line)" */
			करो अणु
				अगर (buffer->current_length >= buffer->columns)
					अवरोध;
				/* ok, add a blank */
				*buffer->current_line++ = 0x40;
				buffer->current_length++;
			पूर्ण जबतक (buffer->current_length % buffer->htab);
			अवरोध;
		हाल '\f':	/* क्रमm feed  */
		हाल '\v':	/* vertical tabulator  */
			/* "go to (actual column, actual line + 1)" */
			/* = new line, leading spaces */
			अगर (buffer->current_line != शून्य) अणु
				spaces = buffer->current_length;
				sclp_finalize_mto(buffer);
				rc = sclp_initialize_mto(buffer,
							 buffer->columns);
				अगर (rc)
					वापस i_msg;
				स_रखो(buffer->current_line, 0x40, spaces);
				buffer->current_line += spaces;
				buffer->current_length = spaces;
			पूर्ण अन्यथा अणु
				/* one an empty line this is the same as \न */
				rc = sclp_initialize_mto(buffer,
							 buffer->columns);
				अगर (rc)
					वापस i_msg;
				sclp_finalize_mto(buffer);
			पूर्ण
			अवरोध;
		हाल '\b':	/* backspace  */
			/* "go to (actual column - 1, actual line)" */
			/* decrement counter indicating position, */
			/* करो not हटाओ last अक्षरacter */
			अगर (buffer->current_line != शून्य &&
			    buffer->current_length > 0) अणु
				buffer->current_length--;
				buffer->current_line--;
			पूर्ण
			अवरोध;
		हाल 0x00:	/* end of string  */
			/* transfer current line to SCCB */
			अगर (buffer->current_line != शून्य)
				sclp_finalize_mto(buffer);
			/* skip the rest of the message including the 0 byte */
			i_msg = count - 1;
			अवरोध;
		शेष:	/* no escape अक्षरacter	*/
			/* करो not output unprपूर्णांकable अक्षरacters */
			अगर (!है_छाप(msg[i_msg]))
				अवरोध;
			/* check अगर new mto needs to be created */
			अगर (buffer->current_line == शून्य) अणु
				rc = sclp_initialize_mto(buffer,
							 buffer->columns);
				अगर (rc)
					वापस i_msg;
			पूर्ण
			*buffer->current_line++ = sclp_ascebc(msg[i_msg]);
			buffer->current_length++;
			अवरोध;
		पूर्ण
		/* check अगर current mto is full */
		अगर (buffer->current_line != शून्य &&
		    buffer->current_length >= buffer->columns)
			sclp_finalize_mto(buffer);
	पूर्ण

	/* वापस number of processed अक्षरacters */
	वापस i_msg;
पूर्ण

/*
 * Return the number of मुक्त bytes in the sccb
 */
पूर्णांक
sclp_buffer_space(काष्ठा sclp_buffer *buffer)
अणु
	काष्ठा sccb_header *sccb;
	पूर्णांक count;

	sccb = buffer->sccb;
	count = MAX_SCCB_ROOM - sccb->length;
	अगर (buffer->current_line != शून्य)
		count -= माप(काष्ठा msg_buf) + buffer->current_length;
	वापस count;
पूर्ण

/*
 * Return number of अक्षरacters in buffer
 */
पूर्णांक
sclp_अक्षरs_in_buffer(काष्ठा sclp_buffer *buffer)
अणु
	पूर्णांक count;

	count = buffer->अक्षर_sum;
	अगर (buffer->current_line != शून्य)
		count += buffer->current_length;
	वापस count;
पूर्ण

/*
 * called by sclp_console_init and/or sclp_tty_init
 */
पूर्णांक
sclp_rw_init(व्योम)
अणु
	अटल पूर्णांक init_करोne = 0;
	पूर्णांक rc;

	अगर (init_करोne)
		वापस 0;

	rc = sclp_रेजिस्टर(&sclp_rw_event);
	अगर (rc == 0)
		init_करोne = 1;
	वापस rc;
पूर्ण

#घोषणा SCLP_BUFFER_MAX_RETRY		1

/*
 * second half of Write Event Data-function that has to be करोne after
 * पूर्णांकerruption indicating completion of Service Call.
 */
अटल व्योम
sclp_ग_लिखोdata_callback(काष्ठा sclp_req *request, व्योम *data)
अणु
	पूर्णांक rc;
	काष्ठा sclp_buffer *buffer;
	काष्ठा sccb_header *sccb;

	buffer = (काष्ठा sclp_buffer *) data;
	sccb = buffer->sccb;

	अगर (request->status == SCLP_REQ_FAILED) अणु
		अगर (buffer->callback != शून्य)
			buffer->callback(buffer, -EIO);
		वापस;
	पूर्ण
	/* check SCLP response code and choose suitable action	*/
	चयन (sccb->response_code) अणु
	हाल 0x0020 :
		/* Normal completion, buffer processed, message(s) sent */
		rc = 0;
		अवरोध;

	हाल 0x0340: /* Contained SCLP equipment check */
		अगर (++buffer->retry_count > SCLP_BUFFER_MAX_RETRY) अणु
			rc = -EIO;
			अवरोध;
		पूर्ण
		/* हटाओ processed buffers and requeue rest */
		अगर (sclp_हटाओ_processed((काष्ठा sccb_header *) sccb) > 0) अणु
			/* not all buffers were processed */
			sccb->response_code = 0x0000;
			buffer->request.status = SCLP_REQ_FILLED;
			rc = sclp_add_request(request);
			अगर (rc == 0)
				वापस;
		पूर्ण अन्यथा
			rc = 0;
		अवरोध;

	हाल 0x0040: /* SCLP equipment check */
	हाल 0x05f0: /* Target resource in improper state */
		अगर (++buffer->retry_count > SCLP_BUFFER_MAX_RETRY) अणु
			rc = -EIO;
			अवरोध;
		पूर्ण
		/* retry request */
		sccb->response_code = 0x0000;
		buffer->request.status = SCLP_REQ_FILLED;
		rc = sclp_add_request(request);
		अगर (rc == 0)
			वापस;
		अवरोध;
	शेष:
		अगर (sccb->response_code == 0x71f0)
			rc = -ENOMEM;
		अन्यथा
			rc = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (buffer->callback != शून्य)
		buffer->callback(buffer, rc);
पूर्ण

/*
 * Setup the request काष्ठाure in the काष्ठा sclp_buffer to करो SCLP Write
 * Event Data and pass the request to the core SCLP loop. Return zero on
 * success, non-zero otherwise.
 */
पूर्णांक
sclp_emit_buffer(काष्ठा sclp_buffer *buffer,
		 व्योम (*callback)(काष्ठा sclp_buffer *, पूर्णांक))
अणु
	/* add current line अगर there is one */
	अगर (buffer->current_line != शून्य)
		sclp_finalize_mto(buffer);

	/* Are there messages in the output buffer ? */
	अगर (buffer->messages == 0)
		वापस -EIO;

	buffer->request.command = SCLP_CMDW_WRITE_EVENT_DATA;
	buffer->request.status = SCLP_REQ_FILLED;
	buffer->request.callback = sclp_ग_लिखोdata_callback;
	buffer->request.callback_data = buffer;
	buffer->request.sccb = buffer->sccb;
	buffer->callback = callback;
	वापस sclp_add_request(&buffer->request);
पूर्ण
