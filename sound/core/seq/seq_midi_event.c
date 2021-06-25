<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  MIDI byte <-> sequencer event coder
 *
 *  Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>,
 *                        Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/seq_kernel.h>
#समावेश <sound/seq_midi_event.h>
#समावेश <sound/asoundef.h>

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>, Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("MIDI byte <-> sequencer event coder");
MODULE_LICENSE("GPL");

/* event type, index पूर्णांकo status_event[] */
/* from 0 to 6 are normal commands (note off, on, etc.) क्रम 0x9?-0xe? */
#घोषणा ST_INVALID	7
#घोषणा ST_SPECIAL	8
#घोषणा ST_SYSEX	ST_SPECIAL
/* from 8 to 15 are events क्रम 0xf0-0xf7 */


/*
 * prototypes
 */
अटल व्योम note_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev);
अटल व्योम one_param_ctrl_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev);
अटल व्योम pitchbend_ctrl_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev);
अटल व्योम two_param_ctrl_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev);
अटल व्योम one_param_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev);
अटल व्योम songpos_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev);
अटल व्योम note_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf);
अटल व्योम one_param_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf);
अटल व्योम pitchbend_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf);
अटल व्योम two_param_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf);
अटल व्योम songpos_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf);

/*
 * event list
 */
अटल काष्ठा status_event_list अणु
	पूर्णांक event;
	पूर्णांक qlen;
	व्योम (*encode)(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev);
	व्योम (*decode)(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf);
पूर्ण status_event[] = अणु
	/* 0x80 - 0xef */
	अणुSNDRV_SEQ_EVENT_NOTखातापूर्णF,	 2, note_event, note_decodeपूर्ण,
	अणुSNDRV_SEQ_EVENT_NOTEON,	 2, note_event, note_decodeपूर्ण,
	अणुSNDRV_SEQ_EVENT_KEYPRESS,	 2, note_event, note_decodeपूर्ण,
	अणुSNDRV_SEQ_EVENT_CONTROLLER,	 2, two_param_ctrl_event, two_param_decodeपूर्ण,
	अणुSNDRV_SEQ_EVENT_PGMCHANGE,	 1, one_param_ctrl_event, one_param_decodeपूर्ण,
	अणुSNDRV_SEQ_EVENT_CHANPRESS,	 1, one_param_ctrl_event, one_param_decodeपूर्ण,
	अणुSNDRV_SEQ_EVENT_PITCHBEND,	 2, pitchbend_ctrl_event, pitchbend_decodeपूर्ण,
	/* invalid */
	अणुSNDRV_SEQ_EVENT_NONE,		-1, शून्य, शून्यपूर्ण,
	/* 0xf0 - 0xff */
	अणुSNDRV_SEQ_EVENT_SYSEX,		 1, शून्य, शून्यपूर्ण, /* sysex: 0xf0 */
	अणुSNDRV_SEQ_EVENT_QFRAME,	 1, one_param_event, one_param_decodeपूर्ण, /* 0xf1 */
	अणुSNDRV_SEQ_EVENT_SONGPOS,	 2, songpos_event, songpos_decodeपूर्ण, /* 0xf2 */
	अणुSNDRV_SEQ_EVENT_SONGSEL,	 1, one_param_event, one_param_decodeपूर्ण, /* 0xf3 */
	अणुSNDRV_SEQ_EVENT_NONE,		-1, शून्य, शून्यपूर्ण, /* 0xf4 */
	अणुSNDRV_SEQ_EVENT_NONE,		-1, शून्य, शून्यपूर्ण, /* 0xf5 */
	अणुSNDRV_SEQ_EVENT_TUNE_REQUEST,	 0, शून्य, शून्यपूर्ण, /* 0xf6 */
	अणुSNDRV_SEQ_EVENT_NONE,		-1, शून्य, शून्यपूर्ण, /* 0xf7 */
	अणुSNDRV_SEQ_EVENT_CLOCK,		 0, शून्य, शून्यपूर्ण, /* 0xf8 */
	अणुSNDRV_SEQ_EVENT_NONE,		-1, शून्य, शून्यपूर्ण, /* 0xf9 */
	अणुSNDRV_SEQ_EVENT_START,		 0, शून्य, शून्यपूर्ण, /* 0xfa */
	अणुSNDRV_SEQ_EVENT_CONTINUE,	 0, शून्य, शून्यपूर्ण, /* 0xfb */
	अणुSNDRV_SEQ_EVENT_STOP, 		 0, शून्य, शून्यपूर्ण, /* 0xfc */
	अणुSNDRV_SEQ_EVENT_NONE, 		-1, शून्य, शून्यपूर्ण, /* 0xfd */
	अणुSNDRV_SEQ_EVENT_SENSING, 	 0, शून्य, शून्यपूर्ण, /* 0xfe */
	अणुSNDRV_SEQ_EVENT_RESET, 	 0, शून्य, शून्यपूर्ण, /* 0xff */
पूर्ण;

अटल पूर्णांक extra_decode_ctrl14(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर *buf, पूर्णांक len,
			       काष्ठा snd_seq_event *ev);
अटल पूर्णांक extra_decode_xrpn(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर *buf, पूर्णांक count,
			     काष्ठा snd_seq_event *ev);

अटल काष्ठा extra_event_list अणु
	पूर्णांक event;
	पूर्णांक (*decode)(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर *buf, पूर्णांक len,
		      काष्ठा snd_seq_event *ev);
पूर्ण extra_event[] = अणु
	अणुSNDRV_SEQ_EVENT_CONTROL14, extra_decode_ctrl14पूर्ण,
	अणुSNDRV_SEQ_EVENT_NONREGPARAM, extra_decode_xrpnपूर्ण,
	अणुSNDRV_SEQ_EVENT_REGPARAM, extra_decode_xrpnपूर्ण,
पूर्ण;

/*
 *  new/delete record
 */

पूर्णांक snd_midi_event_new(पूर्णांक bufsize, काष्ठा snd_midi_event **rdev)
अणु
	काष्ठा snd_midi_event *dev;

	*rdev = शून्य;
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य)
		वापस -ENOMEM;
	अगर (bufsize > 0) अणु
		dev->buf = kदो_स्मृति(bufsize, GFP_KERNEL);
		अगर (dev->buf == शून्य) अणु
			kमुक्त(dev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	dev->bufsize = bufsize;
	dev->lastcmd = 0xff;
	dev->type = ST_INVALID;
	spin_lock_init(&dev->lock);
	*rdev = dev;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_midi_event_new);

व्योम snd_midi_event_मुक्त(काष्ठा snd_midi_event *dev)
अणु
	अगर (dev != शून्य) अणु
		kमुक्त(dev->buf);
		kमुक्त(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_midi_event_मुक्त);

/*
 * initialize record
 */
अटल अंतरभूत व्योम reset_encode(काष्ठा snd_midi_event *dev)
अणु
	dev->पढ़ो = 0;
	dev->qlen = 0;
	dev->type = ST_INVALID;
पूर्ण

व्योम snd_midi_event_reset_encode(काष्ठा snd_midi_event *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	reset_encode(dev);
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण
EXPORT_SYMBOL(snd_midi_event_reset_encode);

व्योम snd_midi_event_reset_decode(काष्ठा snd_midi_event *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	dev->lastcmd = 0xff;
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण
EXPORT_SYMBOL(snd_midi_event_reset_decode);

व्योम snd_midi_event_no_status(काष्ठा snd_midi_event *dev, पूर्णांक on)
अणु
	dev->nostat = on ? 1 : 0;
पूर्ण
EXPORT_SYMBOL(snd_midi_event_no_status);

/*
 *  पढ़ो one byte and encode to sequencer event:
 *  वापस true अगर MIDI bytes are encoded to an event
 *         false data is not finished
 */
bool snd_midi_event_encode_byte(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर c,
				काष्ठा snd_seq_event *ev)
अणु
	bool rc = false;
	अचिन्हित दीर्घ flags;

	अगर (c >= MIDI_CMD_COMMON_CLOCK) अणु
		/* real-समय event */
		ev->type = status_event[ST_SPECIAL + c - 0xf0].event;
		ev->flags &= ~SNDRV_SEQ_EVENT_LENGTH_MASK;
		ev->flags |= SNDRV_SEQ_EVENT_LENGTH_FIXED;
		वापस ev->type != SNDRV_SEQ_EVENT_NONE;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	अगर ((c & 0x80) &&
	    (c != MIDI_CMD_COMMON_SYSEX_END || dev->type != ST_SYSEX)) अणु
		/* new command */
		dev->buf[0] = c;
		अगर ((c & 0xf0) == 0xf0) /* प्रणाली messages */
			dev->type = (c & 0x0f) + ST_SPECIAL;
		अन्यथा
			dev->type = (c >> 4) & 0x07;
		dev->पढ़ो = 1;
		dev->qlen = status_event[dev->type].qlen;
	पूर्ण अन्यथा अणु
		अगर (dev->qlen > 0) अणु
			/* rest of command */
			dev->buf[dev->पढ़ो++] = c;
			अगर (dev->type != ST_SYSEX)
				dev->qlen--;
		पूर्ण अन्यथा अणु
			/* running status */
			dev->buf[1] = c;
			dev->qlen = status_event[dev->type].qlen - 1;
			dev->पढ़ो = 2;
		पूर्ण
	पूर्ण
	अगर (dev->qlen == 0) अणु
		ev->type = status_event[dev->type].event;
		ev->flags &= ~SNDRV_SEQ_EVENT_LENGTH_MASK;
		ev->flags |= SNDRV_SEQ_EVENT_LENGTH_FIXED;
		अगर (status_event[dev->type].encode) /* set data values */
			status_event[dev->type].encode(dev, ev);
		अगर (dev->type >= ST_SPECIAL)
			dev->type = ST_INVALID;
		rc = true;
	पूर्ण अन्यथा 	अगर (dev->type == ST_SYSEX) अणु
		अगर (c == MIDI_CMD_COMMON_SYSEX_END ||
		    dev->पढ़ो >= dev->bufsize) अणु
			ev->flags &= ~SNDRV_SEQ_EVENT_LENGTH_MASK;
			ev->flags |= SNDRV_SEQ_EVENT_LENGTH_VARIABLE;
			ev->type = SNDRV_SEQ_EVENT_SYSEX;
			ev->data.ext.len = dev->पढ़ो;
			ev->data.ext.ptr = dev->buf;
			अगर (c != MIDI_CMD_COMMON_SYSEX_END)
				dev->पढ़ो = 0; /* जारी to parse */
			अन्यथा
				reset_encode(dev); /* all parsed */
			rc = true;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(snd_midi_event_encode_byte);

/* encode note event */
अटल व्योम note_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev)
अणु
	ev->data.note.channel = dev->buf[0] & 0x0f;
	ev->data.note.note = dev->buf[1];
	ev->data.note.velocity = dev->buf[2];
पूर्ण

/* encode one parameter controls */
अटल व्योम one_param_ctrl_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev)
अणु
	ev->data.control.channel = dev->buf[0] & 0x0f;
	ev->data.control.value = dev->buf[1];
पूर्ण

/* encode pitch wheel change */
अटल व्योम pitchbend_ctrl_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev)
अणु
	ev->data.control.channel = dev->buf[0] & 0x0f;
	ev->data.control.value = (पूर्णांक)dev->buf[2] * 128 + (पूर्णांक)dev->buf[1] - 8192;
पूर्ण

/* encode midi control change */
अटल व्योम two_param_ctrl_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev)
अणु
	ev->data.control.channel = dev->buf[0] & 0x0f;
	ev->data.control.param = dev->buf[1];
	ev->data.control.value = dev->buf[2];
पूर्ण

/* encode one parameter value*/
अटल व्योम one_param_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev)
अणु
	ev->data.control.value = dev->buf[1];
पूर्ण

/* encode song position */
अटल व्योम songpos_event(काष्ठा snd_midi_event *dev, काष्ठा snd_seq_event *ev)
अणु
	ev->data.control.value = (पूर्णांक)dev->buf[2] * 128 + (पूर्णांक)dev->buf[1];
पूर्ण

/*
 * decode from a sequencer event to midi bytes
 * वापस the size of decoded midi events
 */
दीर्घ snd_midi_event_decode(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर *buf, दीर्घ count,
			   काष्ठा snd_seq_event *ev)
अणु
	अचिन्हित पूर्णांक cmd, type;

	अगर (ev->type == SNDRV_SEQ_EVENT_NONE)
		वापस -ENOENT;

	क्रम (type = 0; type < ARRAY_SIZE(status_event); type++) अणु
		अगर (ev->type == status_event[type].event)
			जाओ __found;
	पूर्ण
	क्रम (type = 0; type < ARRAY_SIZE(extra_event); type++) अणु
		अगर (ev->type == extra_event[type].event)
			वापस extra_event[type].decode(dev, buf, count, ev);
	पूर्ण
	वापस -ENOENT;

      __found:
	अगर (type >= ST_SPECIAL)
		cmd = 0xf0 + (type - ST_SPECIAL);
	अन्यथा
		/* data.note.channel and data.control.channel is identical */
		cmd = 0x80 | (type << 4) | (ev->data.note.channel & 0x0f);


	अगर (cmd == MIDI_CMD_COMMON_SYSEX) अणु
		snd_midi_event_reset_decode(dev);
		वापस snd_seq_expand_var_event(ev, count, buf, 1, 0);
	पूर्ण अन्यथा अणु
		पूर्णांक qlen;
		अचिन्हित अक्षर xbuf[4];
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dev->lock, flags);
		अगर ((cmd & 0xf0) == 0xf0 || dev->lastcmd != cmd || dev->nostat) अणु
			dev->lastcmd = cmd;
			spin_unlock_irqrestore(&dev->lock, flags);
			xbuf[0] = cmd;
			अगर (status_event[type].decode)
				status_event[type].decode(ev, xbuf + 1);
			qlen = status_event[type].qlen + 1;
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&dev->lock, flags);
			अगर (status_event[type].decode)
				status_event[type].decode(ev, xbuf + 0);
			qlen = status_event[type].qlen;
		पूर्ण
		अगर (count < qlen)
			वापस -ENOMEM;
		स_नकल(buf, xbuf, qlen);
		वापस qlen;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_midi_event_decode);


/* decode note event */
अटल व्योम note_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf)
अणु
	buf[0] = ev->data.note.note & 0x7f;
	buf[1] = ev->data.note.velocity & 0x7f;
पूर्ण

/* decode one parameter controls */
अटल व्योम one_param_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf)
अणु
	buf[0] = ev->data.control.value & 0x7f;
पूर्ण

/* decode pitch wheel change */
अटल व्योम pitchbend_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक value = ev->data.control.value + 8192;
	buf[0] = value & 0x7f;
	buf[1] = (value >> 7) & 0x7f;
पूर्ण

/* decode midi control change */
अटल व्योम two_param_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf)
अणु
	buf[0] = ev->data.control.param & 0x7f;
	buf[1] = ev->data.control.value & 0x7f;
पूर्ण

/* decode song position */
अटल व्योम songpos_decode(काष्ठा snd_seq_event *ev, अचिन्हित अक्षर *buf)
अणु
	buf[0] = ev->data.control.value & 0x7f;
	buf[1] = (ev->data.control.value >> 7) & 0x7f;
पूर्ण

/* decode 14bit control */
अटल पूर्णांक extra_decode_ctrl14(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर *buf,
			       पूर्णांक count, काष्ठा snd_seq_event *ev)
अणु
	अचिन्हित अक्षर cmd;
	पूर्णांक idx = 0;

	cmd = MIDI_CMD_CONTROL|(ev->data.control.channel & 0x0f);
	अगर (ev->data.control.param < 0x20) अणु
		अगर (count < 4)
			वापस -ENOMEM;
		अगर (dev->nostat && count < 6)
			वापस -ENOMEM;
		अगर (cmd != dev->lastcmd || dev->nostat) अणु
			अगर (count < 5)
				वापस -ENOMEM;
			buf[idx++] = dev->lastcmd = cmd;
		पूर्ण
		buf[idx++] = ev->data.control.param;
		buf[idx++] = (ev->data.control.value >> 7) & 0x7f;
		अगर (dev->nostat)
			buf[idx++] = cmd;
		buf[idx++] = ev->data.control.param + 0x20;
		buf[idx++] = ev->data.control.value & 0x7f;
	पूर्ण अन्यथा अणु
		अगर (count < 2)
			वापस -ENOMEM;
		अगर (cmd != dev->lastcmd || dev->nostat) अणु
			अगर (count < 3)
				वापस -ENOMEM;
			buf[idx++] = dev->lastcmd = cmd;
		पूर्ण
		buf[idx++] = ev->data.control.param & 0x7f;
		buf[idx++] = ev->data.control.value & 0x7f;
	पूर्ण
	वापस idx;
पूर्ण

/* decode reg/nonreg param */
अटल पूर्णांक extra_decode_xrpn(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर *buf,
			     पूर्णांक count, काष्ठा snd_seq_event *ev)
अणु
	अचिन्हित अक्षर cmd;
	स्थिर अक्षर *cbytes;
	अटल स्थिर अक्षर cbytes_nrpn[4] = अणु MIDI_CTL_NONREG_PARM_NUM_MSB,
				       MIDI_CTL_NONREG_PARM_NUM_LSB,
				       MIDI_CTL_MSB_DATA_ENTRY,
				       MIDI_CTL_LSB_DATA_ENTRY पूर्ण;
	अटल स्थिर अक्षर cbytes_rpn[4] =  अणु MIDI_CTL_REGIST_PARM_NUM_MSB,
				       MIDI_CTL_REGIST_PARM_NUM_LSB,
				       MIDI_CTL_MSB_DATA_ENTRY,
				       MIDI_CTL_LSB_DATA_ENTRY पूर्ण;
	अचिन्हित अक्षर bytes[4];
	पूर्णांक idx = 0, i;

	अगर (count < 8)
		वापस -ENOMEM;
	अगर (dev->nostat && count < 12)
		वापस -ENOMEM;
	cmd = MIDI_CMD_CONTROL|(ev->data.control.channel & 0x0f);
	bytes[0] = (ev->data.control.param & 0x3f80) >> 7;
	bytes[1] = ev->data.control.param & 0x007f;
	bytes[2] = (ev->data.control.value & 0x3f80) >> 7;
	bytes[3] = ev->data.control.value & 0x007f;
	अगर (cmd != dev->lastcmd && !dev->nostat) अणु
		अगर (count < 9)
			वापस -ENOMEM;
		buf[idx++] = dev->lastcmd = cmd;
	पूर्ण
	cbytes = ev->type == SNDRV_SEQ_EVENT_NONREGPARAM ? cbytes_nrpn : cbytes_rpn;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (dev->nostat)
			buf[idx++] = dev->lastcmd = cmd;
		buf[idx++] = cbytes[i];
		buf[idx++] = bytes[i];
	पूर्ण
	वापस idx;
पूर्ण
