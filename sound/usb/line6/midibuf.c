<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#समावेश <linux/slab.h>

#समावेश "midibuf.h"

अटल पूर्णांक midibuf_message_length(अचिन्हित अक्षर code)
अणु
	पूर्णांक message_length;

	अगर (code < 0x80)
		message_length = -1;
	अन्यथा अगर (code < 0xf0) अणु
		अटल स्थिर पूर्णांक length[] = अणु 3, 3, 3, 3, 2, 2, 3 पूर्ण;

		message_length = length[(code >> 4) - 8];
	पूर्ण अन्यथा अणु
		/*
		   Note that according to the MIDI specअगरication 0xf2 is
		   the "Song Position Pointer", but this is used by Line 6
		   to send sysex messages to the host.
		 */
		अटल स्थिर पूर्णांक length[] = अणु -1, 2, -1, 2, -1, -1, 1, 1, 1, 1,
			1, 1, 1, -1, 1, 1
		पूर्ण;
		message_length = length[code & 0x0f];
	पूर्ण

	वापस message_length;
पूर्ण

अटल पूर्णांक midibuf_is_empty(काष्ठा midi_buffer *this)
अणु
	वापस (this->pos_पढ़ो == this->pos_ग_लिखो) && !this->full;
पूर्ण

अटल पूर्णांक midibuf_is_full(काष्ठा midi_buffer *this)
अणु
	वापस this->full;
पूर्ण

व्योम line6_midibuf_reset(काष्ठा midi_buffer *this)
अणु
	this->pos_पढ़ो = this->pos_ग_लिखो = this->full = 0;
	this->command_prev = -1;
पूर्ण

पूर्णांक line6_midibuf_init(काष्ठा midi_buffer *this, पूर्णांक size, पूर्णांक split)
अणु
	this->buf = kदो_स्मृति(size, GFP_KERNEL);

	अगर (this->buf == शून्य)
		वापस -ENOMEM;

	this->size = size;
	this->split = split;
	line6_midibuf_reset(this);
	वापस 0;
पूर्ण

पूर्णांक line6_midibuf_bytes_मुक्त(काष्ठा midi_buffer *this)
अणु
	वापस
	    midibuf_is_full(this) ?
	    0 :
	    (this->pos_पढ़ो - this->pos_ग_लिखो + this->size - 1) % this->size +
	    1;
पूर्ण

पूर्णांक line6_midibuf_bytes_used(काष्ठा midi_buffer *this)
अणु
	वापस
	    midibuf_is_empty(this) ?
	    0 :
	    (this->pos_ग_लिखो - this->pos_पढ़ो + this->size - 1) % this->size +
	    1;
पूर्ण

पूर्णांक line6_midibuf_ग_लिखो(काष्ठा midi_buffer *this, अचिन्हित अक्षर *data,
			पूर्णांक length)
अणु
	पूर्णांक bytes_मुक्त;
	पूर्णांक length1, length2;
	पूर्णांक skip_active_sense = 0;

	अगर (midibuf_is_full(this) || (length <= 0))
		वापस 0;

	/* skip trailing active sense */
	अगर (data[length - 1] == 0xfe) अणु
		--length;
		skip_active_sense = 1;
	पूर्ण

	bytes_मुक्त = line6_midibuf_bytes_मुक्त(this);

	अगर (length > bytes_मुक्त)
		length = bytes_मुक्त;

	अगर (length > 0) अणु
		length1 = this->size - this->pos_ग_लिखो;

		अगर (length < length1) अणु
			/* no buffer wraparound */
			स_नकल(this->buf + this->pos_ग_लिखो, data, length);
			this->pos_ग_लिखो += length;
		पूर्ण अन्यथा अणु
			/* buffer wraparound */
			length2 = length - length1;
			स_नकल(this->buf + this->pos_ग_लिखो, data, length1);
			स_नकल(this->buf, data + length1, length2);
			this->pos_ग_लिखो = length2;
		पूर्ण

		अगर (this->pos_ग_लिखो == this->pos_पढ़ो)
			this->full = 1;
	पूर्ण

	वापस length + skip_active_sense;
पूर्ण

पूर्णांक line6_midibuf_पढ़ो(काष्ठा midi_buffer *this, अचिन्हित अक्षर *data,
		       पूर्णांक length)
अणु
	पूर्णांक bytes_used;
	पूर्णांक length1, length2;
	पूर्णांक command;
	पूर्णांक midi_length;
	पूर्णांक repeat = 0;
	पूर्णांक i;

	/* we need to be able to store at least a 3 byte MIDI message */
	अगर (length < 3)
		वापस -EINVAL;

	अगर (midibuf_is_empty(this))
		वापस 0;

	bytes_used = line6_midibuf_bytes_used(this);

	अगर (length > bytes_used)
		length = bytes_used;

	length1 = this->size - this->pos_पढ़ो;

	/* check MIDI command length */
	command = this->buf[this->pos_पढ़ो];

	अगर (command & 0x80) अणु
		midi_length = midibuf_message_length(command);
		this->command_prev = command;
	पूर्ण अन्यथा अणु
		अगर (this->command_prev > 0) अणु
			पूर्णांक midi_length_prev =
			    midibuf_message_length(this->command_prev);

			अगर (midi_length_prev > 1) अणु
				midi_length = midi_length_prev - 1;
				repeat = 1;
			पूर्ण अन्यथा
				midi_length = -1;
		पूर्ण अन्यथा
			midi_length = -1;
	पूर्ण

	अगर (midi_length < 0) अणु
		/* search क्रम end of message */
		अगर (length < length1) अणु
			/* no buffer wraparound */
			क्रम (i = 1; i < length; ++i)
				अगर (this->buf[this->pos_पढ़ो + i] & 0x80)
					अवरोध;

			midi_length = i;
		पूर्ण अन्यथा अणु
			/* buffer wraparound */
			length2 = length - length1;

			क्रम (i = 1; i < length1; ++i)
				अगर (this->buf[this->pos_पढ़ो + i] & 0x80)
					अवरोध;

			अगर (i < length1)
				midi_length = i;
			अन्यथा अणु
				क्रम (i = 0; i < length2; ++i)
					अगर (this->buf[i] & 0x80)
						अवरोध;

				midi_length = length1 + i;
			पूर्ण
		पूर्ण

		अगर (midi_length == length)
			midi_length = -1;	/* end of message not found */
	पूर्ण

	अगर (midi_length < 0) अणु
		अगर (!this->split)
			वापस 0;	/* command is not yet complete */
	पूर्ण अन्यथा अणु
		अगर (length < midi_length)
			वापस 0;	/* command is not yet complete */

		length = midi_length;
	पूर्ण

	अगर (length < length1) अणु
		/* no buffer wraparound */
		स_नकल(data + repeat, this->buf + this->pos_पढ़ो, length);
		this->pos_पढ़ो += length;
	पूर्ण अन्यथा अणु
		/* buffer wraparound */
		length2 = length - length1;
		स_नकल(data + repeat, this->buf + this->pos_पढ़ो, length1);
		स_नकल(data + repeat + length1, this->buf, length2);
		this->pos_पढ़ो = length2;
	पूर्ण

	अगर (repeat)
		data[0] = this->command_prev;

	this->full = 0;
	वापस length + repeat;
पूर्ण

पूर्णांक line6_midibuf_ignore(काष्ठा midi_buffer *this, पूर्णांक length)
अणु
	पूर्णांक bytes_used = line6_midibuf_bytes_used(this);

	अगर (length > bytes_used)
		length = bytes_used;

	this->pos_पढ़ो = (this->pos_पढ़ो + length) % this->size;
	this->full = 0;
	वापस length;
पूर्ण

व्योम line6_midibuf_destroy(काष्ठा midi_buffer *this)
अणु
	kमुक्त(this->buf);
	this->buf = शून्य;
पूर्ण
