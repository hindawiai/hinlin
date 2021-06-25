<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम the Prodikeys PC-MIDI Keyboard
 *  providing midi & extra mulसमयdia keys functionality
 *
 *  Copyright (c) 2009 Don Prince <dhprince.devel@yahoo.co.uk>
 *
 *  Controls क्रम Octave Shअगरt Up/Down, Channel, and
 *  Sustain Duration available via sysfs.
 */

/*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hid.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/rawmidi.h>
#समावेश "hid-ids.h"


#घोषणा pk_debug(क्रमmat, arg...) \
	pr_debug("hid-prodikeys: " क्रमmat "\n" , ## arg)
#घोषणा pk_error(क्रमmat, arg...) \
	pr_err("hid-prodikeys: " क्रमmat "\n" , ## arg)

काष्ठा pcmidi_snd;

काष्ठा pk_device अणु
	अचिन्हित दीर्घ		quirks;

	काष्ठा hid_device	*hdev;
	काष्ठा pcmidi_snd	*pm; /* pcmidi device context */
पूर्ण;

काष्ठा pcmidi_sustain अणु
	अचिन्हित दीर्घ		in_use;
	काष्ठा pcmidi_snd	*pm;
	काष्ठा समयr_list	समयr;
	अचिन्हित अक्षर		status;
	अचिन्हित अक्षर		note;
	अचिन्हित अक्षर		velocity;
पूर्ण;

#घोषणा PCMIDI_SUSTAINED_MAX	32
काष्ठा pcmidi_snd अणु
	काष्ठा pk_device		*pk;
	अचिन्हित लघु			अगरnum;
	काष्ठा hid_report		*pcmidi_report6;
	काष्ठा input_dev		*input_ep82;
	अचिन्हित लघु			midi_mode;
	अचिन्हित लघु			midi_sustain_mode;
	अचिन्हित लघु			midi_sustain;
	अचिन्हित लघु			midi_channel;
	लघु				midi_octave;
	काष्ठा pcmidi_sustain		sustained_notes[PCMIDI_SUSTAINED_MAX];
	अचिन्हित लघु			fn_state;
	अचिन्हित लघु			last_key[24];
	spinlock_t			rawmidi_in_lock;
	काष्ठा snd_card			*card;
	काष्ठा snd_rawmidi		*rwmidi;
	काष्ठा snd_rawmidi_substream	*in_substream;
	काष्ठा snd_rawmidi_substream	*out_substream;
	अचिन्हित दीर्घ			in_triggered;
	अचिन्हित दीर्घ			out_active;
पूर्ण;

#घोषणा PK_QUIRK_NOGET	0x00010000
#घोषणा PCMIDI_MIDDLE_C 60
#घोषणा PCMIDI_CHANNEL_MIN 0
#घोषणा PCMIDI_CHANNEL_MAX 15
#घोषणा PCMIDI_OCTAVE_MIN (-2)
#घोषणा PCMIDI_OCTAVE_MAX 2
#घोषणा PCMIDI_SUSTAIN_MIN 0
#घोषणा PCMIDI_SUSTAIN_MAX 5000

अटल स्थिर अक्षर लघुname[] = "PC-MIDI";
अटल स्थिर अक्षर दीर्घname[] = "Prodikeys PC-MIDI Keyboard";

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
module_param_array(id, अक्षरp, शून्य, 0444);
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the PC-MIDI virtual audio driver");
MODULE_PARM_DESC(id, "ID string for the PC-MIDI virtual audio driver");
MODULE_PARM_DESC(enable, "Enable for the PC-MIDI virtual audio driver");


/* Output routine क्रम the sysfs channel file */
अटल sमाप_प्रकार show_channel(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);

	dbg_hid("pcmidi sysfs read channel=%u\n", pk->pm->midi_channel);

	वापस प्र_लिखो(buf, "%u (min:%u, max:%u)\n", pk->pm->midi_channel,
		PCMIDI_CHANNEL_MIN, PCMIDI_CHANNEL_MAX);
पूर्ण

/* Input routine क्रम the sysfs channel file */
अटल sमाप_प्रकार store_channel(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);

	अचिन्हित channel = 0;

	अगर (माला_पूछो(buf, "%u", &channel) > 0 && channel <= PCMIDI_CHANNEL_MAX) अणु
		dbg_hid("pcmidi sysfs write channel=%u\n", channel);
		pk->pm->midi_channel = channel;
		वापस म_माप(buf);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल DEVICE_ATTR(channel, S_IRUGO | S_IWUSR | S_IWGRP , show_channel,
		store_channel);

अटल काष्ठा device_attribute *sysfs_device_attr_channel = अणु
		&dev_attr_channel,
		पूर्ण;

/* Output routine क्रम the sysfs sustain file */
अटल sमाप_प्रकार show_sustain(काष्ठा device *dev,
 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);

	dbg_hid("pcmidi sysfs read sustain=%u\n", pk->pm->midi_sustain);

	वापस प्र_लिखो(buf, "%u (off:%u, max:%u (ms))\n", pk->pm->midi_sustain,
		PCMIDI_SUSTAIN_MIN, PCMIDI_SUSTAIN_MAX);
पूर्ण

/* Input routine क्रम the sysfs sustain file */
अटल sमाप_प्रकार store_sustain(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);

	अचिन्हित sustain = 0;

	अगर (माला_पूछो(buf, "%u", &sustain) > 0 && sustain <= PCMIDI_SUSTAIN_MAX) अणु
		dbg_hid("pcmidi sysfs write sustain=%u\n", sustain);
		pk->pm->midi_sustain = sustain;
		pk->pm->midi_sustain_mode =
			(0 == sustain || !pk->pm->midi_mode) ? 0 : 1;
		वापस म_माप(buf);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल DEVICE_ATTR(sustain, S_IRUGO | S_IWUSR | S_IWGRP, show_sustain,
		store_sustain);

अटल काष्ठा device_attribute *sysfs_device_attr_sustain = अणु
		&dev_attr_sustain,
		पूर्ण;

/* Output routine क्रम the sysfs octave file */
अटल sमाप_प्रकार show_octave(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);

	dbg_hid("pcmidi sysfs read octave=%d\n", pk->pm->midi_octave);

	वापस प्र_लिखो(buf, "%d (min:%d, max:%d)\n", pk->pm->midi_octave,
		PCMIDI_OCTAVE_MIN, PCMIDI_OCTAVE_MAX);
पूर्ण

/* Input routine क्रम the sysfs octave file */
अटल sमाप_प्रकार store_octave(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);

	पूर्णांक octave = 0;

	अगर (माला_पूछो(buf, "%d", &octave) > 0 &&
		octave >= PCMIDI_OCTAVE_MIN && octave <= PCMIDI_OCTAVE_MAX) अणु
		dbg_hid("pcmidi sysfs write octave=%d\n", octave);
		pk->pm->midi_octave = octave;
		वापस म_माप(buf);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल DEVICE_ATTR(octave, S_IRUGO | S_IWUSR | S_IWGRP, show_octave,
		store_octave);

अटल काष्ठा device_attribute *sysfs_device_attr_octave = अणु
		&dev_attr_octave,
		पूर्ण;


अटल व्योम pcmidi_send_note(काष्ठा pcmidi_snd *pm,
	अचिन्हित अक्षर status, अचिन्हित अक्षर note, अचिन्हित अक्षर velocity)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर buffer[3];

	buffer[0] = status;
	buffer[1] = note;
	buffer[2] = velocity;

	spin_lock_irqsave(&pm->rawmidi_in_lock, flags);

	अगर (!pm->in_substream)
		जाओ drop_note;
	अगर (!test_bit(pm->in_substream->number, &pm->in_triggered))
		जाओ drop_note;

	snd_rawmidi_receive(pm->in_substream, buffer, 3);

drop_note:
	spin_unlock_irqrestore(&pm->rawmidi_in_lock, flags);

	वापस;
पूर्ण

अटल व्योम pcmidi_sustained_note_release(काष्ठा समयr_list *t)
अणु
	काष्ठा pcmidi_sustain *pms = from_समयr(pms, t, समयr);

	pcmidi_send_note(pms->pm, pms->status, pms->note, pms->velocity);
	pms->in_use = 0;
पूर्ण

अटल व्योम init_sustain_समयrs(काष्ठा pcmidi_snd *pm)
अणु
	काष्ठा pcmidi_sustain *pms;
	अचिन्हित i;

	क्रम (i = 0; i < PCMIDI_SUSTAINED_MAX; i++) अणु
		pms = &pm->sustained_notes[i];
		pms->in_use = 0;
		pms->pm = pm;
		समयr_setup(&pms->समयr, pcmidi_sustained_note_release, 0);
	पूर्ण
पूर्ण

अटल व्योम stop_sustain_समयrs(काष्ठा pcmidi_snd *pm)
अणु
	काष्ठा pcmidi_sustain *pms;
	अचिन्हित i;

	क्रम (i = 0; i < PCMIDI_SUSTAINED_MAX; i++) अणु
		pms = &pm->sustained_notes[i];
		pms->in_use = 1;
		del_समयr_sync(&pms->समयr);
	पूर्ण
पूर्ण

अटल पूर्णांक pcmidi_get_output_report(काष्ठा pcmidi_snd *pm)
अणु
	काष्ठा hid_device *hdev = pm->pk->hdev;
	काष्ठा hid_report *report;

	list_क्रम_each_entry(report,
		&hdev->report_क्रमागत[HID_OUTPUT_REPORT].report_list, list) अणु
		अगर (!(6 == report->id))
			जारी;

		अगर (report->maxfield < 1) अणु
			hid_err(hdev, "output report is empty\n");
			अवरोध;
		पूर्ण
		अगर (report->field[0]->report_count != 2) अणु
			hid_err(hdev, "field count too low\n");
			अवरोध;
		पूर्ण
		pm->pcmidi_report6 = report;
		वापस 0;
	पूर्ण
	/* should never get here */
	वापस -ENODEV;
पूर्ण

अटल व्योम pcmidi_submit_output_report(काष्ठा pcmidi_snd *pm, पूर्णांक state)
अणु
	काष्ठा hid_device *hdev = pm->pk->hdev;
	काष्ठा hid_report *report = pm->pcmidi_report6;
	report->field[0]->value[0] = 0x01;
	report->field[0]->value[1] = state;

	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
पूर्ण

अटल पूर्णांक pcmidi_handle_report1(काष्ठा pcmidi_snd *pm, u8 *data)
अणु
	u32 bit_mask;

	bit_mask = data[1];
	bit_mask = (bit_mask << 8) | data[2];
	bit_mask = (bit_mask << 8) | data[3];

	dbg_hid("pcmidi mode: %d\n", pm->midi_mode);

	/*KEY_MAIL or octave करोwn*/
	अगर (pm->midi_mode && bit_mask == 0x004000) अणु
		/* octave करोwn */
		pm->midi_octave--;
		अगर (pm->midi_octave < -2)
			pm->midi_octave = -2;
		dbg_hid("pcmidi mode: %d octave: %d\n",
			pm->midi_mode, pm->midi_octave);
		वापस 1;
	पूर्ण
	/*KEY_WWW or sustain*/
	अन्यथा अगर (pm->midi_mode && bit_mask == 0x000004) अणु
		/* sustain on/off*/
		pm->midi_sustain_mode ^= 0x1;
		वापस 1;
	पूर्ण

	वापस 0; /* जारी key processing */
पूर्ण

अटल पूर्णांक pcmidi_handle_report3(काष्ठा pcmidi_snd *pm, u8 *data, पूर्णांक size)
अणु
	काष्ठा pcmidi_sustain *pms;
	अचिन्हित i, j;
	अचिन्हित अक्षर status, note, velocity;

	अचिन्हित num_notes = (size-1)/2;
	क्रम (j = 0; j < num_notes; j++)	अणु
		note = data[j*2+1];
		velocity = data[j*2+2];

		अगर (note < 0x81) अणु /* note on */
			status = 128 + 16 + pm->midi_channel; /* 1001nnnn */
			note = note - 0x54 + PCMIDI_MIDDLE_C +
				(pm->midi_octave * 12);
			अगर (0 == velocity)
				velocity = 1; /* क्रमce note on */
		पूर्ण अन्यथा अणु /* note off */
			status = 128 + pm->midi_channel; /* 1000nnnn */
			note = note - 0x94 + PCMIDI_MIDDLE_C +
				(pm->midi_octave*12);

			अगर (pm->midi_sustain_mode) अणु
				क्रम (i = 0; i < PCMIDI_SUSTAINED_MAX; i++) अणु
					pms = &pm->sustained_notes[i];
					अगर (!pms->in_use) अणु
						pms->status = status;
						pms->note = note;
						pms->velocity = velocity;
						pms->in_use = 1;

						mod_समयr(&pms->समयr,
							jअगरfies +
					msecs_to_jअगरfies(pm->midi_sustain));
						वापस 1;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		pcmidi_send_note(pm, status, note, velocity);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक pcmidi_handle_report4(काष्ठा pcmidi_snd *pm, u8 *data)
अणु
	अचिन्हित	key;
	u32		bit_mask;
	u32		bit_index;

	bit_mask = data[1];
	bit_mask = (bit_mask << 8) | data[2];
	bit_mask = (bit_mask << 8) | data[3];

	/* अवरोध keys */
	क्रम (bit_index = 0; bit_index < 24; bit_index++) अणु
		अगर (!((0x01 << bit_index) & bit_mask)) अणु
			input_event(pm->input_ep82, EV_KEY,
				pm->last_key[bit_index], 0);
			pm->last_key[bit_index] = 0;
		पूर्ण
	पूर्ण

	/* make keys */
	क्रम (bit_index = 0; bit_index < 24; bit_index++) अणु
		key = 0;
		चयन ((0x01 << bit_index) & bit_mask) अणु
		हाल 0x000010: /* Fn lock*/
			pm->fn_state ^= 0x000010;
			अगर (pm->fn_state)
				pcmidi_submit_output_report(pm, 0xc5);
			अन्यथा
				pcmidi_submit_output_report(pm, 0xc6);
			जारी;
		हाल 0x020000: /* midi launcher..send a key (qwerty) or not? */
			pcmidi_submit_output_report(pm, 0xc1);
			pm->midi_mode ^= 0x01;

			dbg_hid("pcmidi mode: %d\n", pm->midi_mode);
			जारी;
		हाल 0x100000: /* KEY_MESSENGER or octave up */
			dbg_hid("pcmidi mode: %d\n", pm->midi_mode);
			अगर (pm->midi_mode) अणु
				pm->midi_octave++;
				अगर (pm->midi_octave > 2)
					pm->midi_octave = 2;
				dbg_hid("pcmidi mode: %d octave: %d\n",
					pm->midi_mode, pm->midi_octave);
				जारी;
			पूर्ण अन्यथा
				key = KEY_MESSENGER;
			अवरोध;
		हाल 0x400000:
			key = KEY_CALENDAR;
			अवरोध;
		हाल 0x080000:
			key = KEY_ADDRESSBOOK;
			अवरोध;
		हाल 0x040000:
			key = KEY_DOCUMENTS;
			अवरोध;
		हाल 0x800000:
			key = KEY_WORDPROCESSOR;
			अवरोध;
		हाल 0x200000:
			key = KEY_SPREADSHEET;
			अवरोध;
		हाल 0x010000:
			key = KEY_COFFEE;
			अवरोध;
		हाल 0x000100:
			key = KEY_HELP;
			अवरोध;
		हाल 0x000200:
			key = KEY_SEND;
			अवरोध;
		हाल 0x000400:
			key = KEY_REPLY;
			अवरोध;
		हाल 0x000800:
			key = KEY_FORWARDMAIL;
			अवरोध;
		हाल 0x001000:
			key = KEY_NEW;
			अवरोध;
		हाल 0x002000:
			key = KEY_OPEN;
			अवरोध;
		हाल 0x004000:
			key = KEY_CLOSE;
			अवरोध;
		हाल 0x008000:
			key = KEY_SAVE;
			अवरोध;
		हाल 0x000001:
			key = KEY_UNDO;
			अवरोध;
		हाल 0x000002:
			key = KEY_REDO;
			अवरोध;
		हाल 0x000004:
			key = KEY_SPELLCHECK;
			अवरोध;
		हाल 0x000008:
			key = KEY_PRINT;
			अवरोध;
		पूर्ण
		अगर (key) अणु
			input_event(pm->input_ep82, EV_KEY, key, 1);
			pm->last_key[bit_index] = key;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक pcmidi_handle_report(
	काष्ठा pcmidi_snd *pm, अचिन्हित report_id, u8 *data, पूर्णांक size)
अणु
	पूर्णांक ret = 0;

	चयन (report_id) अणु
	हाल 0x01: /* midi keys (qwerty)*/
		ret = pcmidi_handle_report1(pm, data);
		अवरोध;
	हाल 0x03: /* midi keyboard (musical)*/
		ret = pcmidi_handle_report3(pm, data, size);
		अवरोध;
	हाल 0x04: /* mulसमयdia/midi keys (qwerty)*/
		ret = pcmidi_handle_report4(pm, data);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम pcmidi_setup_extra_keys(
	काष्ठा pcmidi_snd *pm, काष्ठा input_dev *input)
अणु
	/* reasचिन्हित functionality क्रम N/A keys
		MY PICTURES =>	KEY_WORDPROCESSOR
		MY MUSIC=>	KEY_SPREADSHEET
	*/
	अटल स्थिर अचिन्हित पूर्णांक keys[] = अणु
		KEY_FN,
		KEY_MESSENGER, KEY_CALENDAR,
		KEY_ADDRESSBOOK, KEY_DOCUMENTS,
		KEY_WORDPROCESSOR,
		KEY_SPREADSHEET,
		KEY_COFFEE,
		KEY_HELP, KEY_SEND,
		KEY_REPLY, KEY_FORWARDMAIL,
		KEY_NEW, KEY_OPEN,
		KEY_CLOSE, KEY_SAVE,
		KEY_UNDO, KEY_REDO,
		KEY_SPELLCHECK,	KEY_PRINT,
		0
	पूर्ण;

	स्थिर अचिन्हित पूर्णांक *pkeys = &keys[0];
	अचिन्हित लघु i;

	अगर (pm->अगरnum != 1)  /* only set up ONCE क्रम पूर्णांकerace 1 */
		वापस;

	pm->input_ep82 = input;

	क्रम (i = 0; i < 24; i++)
		pm->last_key[i] = 0;

	जबतक (*pkeys != 0) अणु
		set_bit(*pkeys, pm->input_ep82->keybit);
		++pkeys;
	पूर्ण
पूर्ण

अटल पूर्णांक pcmidi_set_operational(काष्ठा pcmidi_snd *pm)
अणु
	पूर्णांक rc;

	अगर (pm->अगरnum != 1)
		वापस 0; /* only set up ONCE क्रम पूर्णांकerace 1 */

	rc = pcmidi_get_output_report(pm);
	अगर (rc < 0)
		वापस rc;
	pcmidi_submit_output_report(pm, 0xc1);
	वापस 0;
पूर्ण

अटल पूर्णांक pcmidi_snd_मुक्त(काष्ठा snd_device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pcmidi_in_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा pcmidi_snd *pm = substream->rmidi->निजी_data;

	dbg_hid("pcmidi in open\n");
	pm->in_substream = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक pcmidi_in_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	dbg_hid("pcmidi in close\n");
	वापस 0;
पूर्ण

अटल व्योम pcmidi_in_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा pcmidi_snd *pm = substream->rmidi->निजी_data;

	dbg_hid("pcmidi in trigger %d\n", up);

	pm->in_triggered = up;
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops pcmidi_in_ops = अणु
	.खोलो = pcmidi_in_खोलो,
	.बंद = pcmidi_in_बंद,
	.trigger = pcmidi_in_trigger
पूर्ण;

अटल पूर्णांक pcmidi_snd_initialise(काष्ठा pcmidi_snd *pm)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_rawmidi *rwmidi;
	पूर्णांक err;

	अटल काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = pcmidi_snd_मुक्त,
	पूर्ण;

	अगर (pm->अगरnum != 1)
		वापस 0; /* only set up midi device ONCE क्रम पूर्णांकerace 1 */

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	/* Setup sound card */

	err = snd_card_new(&pm->pk->hdev->dev, index[dev], id[dev],
			   THIS_MODULE, 0, &card);
	अगर (err < 0) अणु
		pk_error("failed to create pc-midi sound card\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण
	pm->card = card;

	/* Setup sound device */
	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, pm, &ops);
	अगर (err < 0) अणु
		pk_error("failed to create pc-midi sound device: error %d\n",
			err);
		जाओ fail;
	पूर्ण

	म_नकलन(card->driver, लघुname, माप(card->driver));
	म_नकलन(card->लघुname, लघुname, माप(card->लघुname));
	म_नकलन(card->दीर्घname, दीर्घname, माप(card->दीर्घname));

	/* Set up rawmidi */
	err = snd_rawmidi_new(card, card->लघुname, 0,
			      0, 1, &rwmidi);
	अगर (err < 0) अणु
		pk_error("failed to create pc-midi rawmidi device: error %d\n",
			err);
		जाओ fail;
	पूर्ण
	pm->rwmidi = rwmidi;
	म_नकलन(rwmidi->name, card->लघुname, माप(rwmidi->name));
	rwmidi->info_flags = SNDRV_RAWMIDI_INFO_INPUT;
	rwmidi->निजी_data = pm;

	snd_rawmidi_set_ops(rwmidi, SNDRV_RAWMIDI_STREAM_INPUT,
		&pcmidi_in_ops);

	/* create sysfs variables */
	err = device_create_file(&pm->pk->hdev->dev,
				 sysfs_device_attr_channel);
	अगर (err < 0) अणु
		pk_error("failed to create sysfs attribute channel: error %d\n",
			err);
		जाओ fail;
	पूर्ण

	err = device_create_file(&pm->pk->hdev->dev,
				sysfs_device_attr_sustain);
	अगर (err < 0) अणु
		pk_error("failed to create sysfs attribute sustain: error %d\n",
			err);
		जाओ fail_attr_sustain;
	पूर्ण

	err = device_create_file(&pm->pk->hdev->dev,
			 sysfs_device_attr_octave);
	अगर (err < 0) अणु
		pk_error("failed to create sysfs attribute octave: error %d\n",
			err);
		जाओ fail_attr_octave;
	पूर्ण

	spin_lock_init(&pm->rawmidi_in_lock);

	init_sustain_समयrs(pm);
	err = pcmidi_set_operational(pm);
	अगर (err < 0) अणु
		pk_error("failed to find output report\n");
		जाओ fail_रेजिस्टर;
	पूर्ण

	/* रेजिस्टर it */
	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		pk_error("failed to register pc-midi sound card: error %d\n",
			 err);
		जाओ fail_रेजिस्टर;
	पूर्ण

	dbg_hid("pcmidi_snd_initialise finished ok\n");
	वापस 0;

fail_रेजिस्टर:
	stop_sustain_समयrs(pm);
	device_हटाओ_file(&pm->pk->hdev->dev, sysfs_device_attr_octave);
fail_attr_octave:
	device_हटाओ_file(&pm->pk->hdev->dev, sysfs_device_attr_sustain);
fail_attr_sustain:
	device_हटाओ_file(&pm->pk->hdev->dev, sysfs_device_attr_channel);
fail:
	अगर (pm->card) अणु
		snd_card_मुक्त(pm->card);
		pm->card = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक pcmidi_snd_terminate(काष्ठा pcmidi_snd *pm)
अणु
	अगर (pm->card) अणु
		stop_sustain_समयrs(pm);

		device_हटाओ_file(&pm->pk->hdev->dev,
			sysfs_device_attr_channel);
		device_हटाओ_file(&pm->pk->hdev->dev,
			sysfs_device_attr_sustain);
		device_हटाओ_file(&pm->pk->hdev->dev,
			sysfs_device_attr_octave);

		snd_card_disconnect(pm->card);
		snd_card_मुक्त_when_बंदd(pm->card);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * PC-MIDI report descriptor क्रम report id is wrong.
 */
अटल __u8 *pk_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize == 178 &&
	      rdesc[111] == 0x06 && rdesc[112] == 0x00 &&
	      rdesc[113] == 0xff) अणु
		hid_info(hdev,
			 "fixing up pc-midi keyboard report descriptor\n");

		rdesc[144] = 0x18; /* report 4: was 0x10 report count */
	पूर्ण
	वापस rdesc;
पूर्ण

अटल पूर्णांक pk_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);
	काष्ठा pcmidi_snd *pm;

	pm = pk->pm;

	अगर (HID_UP_MSVENDOR == (usage->hid & HID_USAGE_PAGE) &&
		1 == pm->अगरnum) अणु
		pcmidi_setup_extra_keys(pm, hi->input);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक pk_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
	u8 *data, पूर्णांक size)
अणु
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);
	पूर्णांक ret = 0;

	अगर (1 == pk->pm->अगरnum) अणु
		अगर (report->id == data[0])
			चयन (report->id) अणु
			हाल 0x01: /* midi keys (qwerty)*/
			हाल 0x03: /* midi keyboard (musical)*/
			हाल 0x04: /* extra/midi keys (qwerty)*/
				ret = pcmidi_handle_report(pk->pm,
						report->id, data, size);
				अवरोध;
			पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pk_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	अचिन्हित लघु अगरnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	अचिन्हित दीर्घ quirks = id->driver_data;
	काष्ठा pk_device *pk;
	काष्ठा pcmidi_snd *pm = शून्य;

	pk = kzalloc(माप(*pk), GFP_KERNEL);
	अगर (pk == शून्य) अणु
		hid_err(hdev, "can't alloc descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	pk->hdev = hdev;

	pm = kzalloc(माप(*pm), GFP_KERNEL);
	अगर (pm == शून्य) अणु
		hid_err(hdev, "can't alloc descriptor\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_pk;
	पूर्ण

	pm->pk = pk;
	pk->pm = pm;
	pm->अगरnum = अगरnum;

	hid_set_drvdata(hdev, pk);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "hid parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (quirks & PK_QUIRK_NOGET) अणु /* hid_parse cleared all the quirks */
		hdev->quirks |= HID_QUIRK_NOGET;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = pcmidi_snd_initialise(pm);
	अगर (ret < 0)
		जाओ err_stop;

	वापस 0;
err_stop:
	hid_hw_stop(hdev);
err_मुक्त:
	kमुक्त(pm);
err_मुक्त_pk:
	kमुक्त(pk);

	वापस ret;
पूर्ण

अटल व्योम pk_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा pk_device *pk = hid_get_drvdata(hdev);
	काष्ठा pcmidi_snd *pm;

	pm = pk->pm;
	अगर (pm) अणु
		pcmidi_snd_terminate(pm);
		kमुक्त(pm);
	पूर्ण

	hid_hw_stop(hdev);

	kमुक्त(pk);
पूर्ण

अटल स्थिर काष्ठा hid_device_id pk_devices[] = अणु
	अणुHID_USB_DEVICE(USB_VENDOR_ID_CREATIVELABS,
		USB_DEVICE_ID_PRODIKEYS_PCMIDI),
	    .driver_data = PK_QUIRK_NOGETपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, pk_devices);

अटल काष्ठा hid_driver pk_driver = अणु
	.name = "prodikeys",
	.id_table = pk_devices,
	.report_fixup = pk_report_fixup,
	.input_mapping = pk_input_mapping,
	.raw_event = pk_raw_event,
	.probe = pk_probe,
	.हटाओ = pk_हटाओ,
पूर्ण;
module_hid_driver(pk_driver);

MODULE_LICENSE("GPL");
