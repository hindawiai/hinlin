<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBMIDI_H
#घोषणा __USBMIDI_H

/* maximum number of endpoपूर्णांकs per पूर्णांकerface */
#घोषणा MIDI_MAX_ENDPOINTS 2

/* data क्रम QUIRK_MIDI_FIXED_ENDPOINT */
काष्ठा snd_usb_midi_endpoपूर्णांक_info अणु
	पूर्णांक8_t   out_ep;	/* ep number, 0 स्वतःdetect */
	uपूर्णांक8_t  out_पूर्णांकerval;	/* पूर्णांकerval क्रम पूर्णांकerrupt endpoपूर्णांकs */
	पूर्णांक8_t   in_ep;
	uपूर्णांक8_t  in_पूर्णांकerval;
	uपूर्णांक16_t out_cables;	/* biपंचांगask */
	uपूर्णांक16_t in_cables;	/* biपंचांगask */
	पूर्णांक16_t  assoc_in_jacks[16];
	पूर्णांक16_t  assoc_out_jacks[16];
पूर्ण;

/* क्रम QUIRK_MIDI_YAMAHA, data is शून्य */

/* क्रम QUIRK_MIDI_MIDIMAN, data poपूर्णांकs to a snd_usb_midi_endpoपूर्णांक_info
 * काष्ठाure (out_cables and in_cables only) */

/* क्रम QUIRK_COMPOSITE, data poपूर्णांकs to an array of snd_usb_audio_quirk
 * काष्ठाures, terminated with .अगरnum = -1 */

/* क्रम QUIRK_AUDIO_FIXED_ENDPOINT, data poपूर्णांकs to an audioक्रमmat काष्ठाure */

/* क्रम QUIRK_AUDIO/MIDI_STANDARD_INTERFACE, data is शून्य */

/* क्रम QUIRK_AUDIO_EसूचीOL_UA700_UA25/UA1000, data is शून्य */

/* क्रम QUIRK_IGNORE_INTERFACE, data is शून्य */

/* क्रम QUIRK_MIDI_NOVATION and _RAW, data is शून्य */

/* क्रम QUIRK_MIDI_EMAGIC, data poपूर्णांकs to a snd_usb_midi_endpoपूर्णांक_info
 * काष्ठाure (out_cables and in_cables only) */

/* क्रम QUIRK_MIDI_CME, data is शून्य */

/* क्रम QUIRK_MIDI_AKAI, data is शून्य */

पूर्णांक __snd_usbmidi_create(काष्ठा snd_card *card,
			 काष्ठा usb_पूर्णांकerface *अगरace,
			 काष्ठा list_head *midi_list,
			 स्थिर काष्ठा snd_usb_audio_quirk *quirk,
			 अचिन्हित पूर्णांक usb_id);

अटल अंतरभूत पूर्णांक snd_usbmidi_create(काष्ठा snd_card *card,
		       काष्ठा usb_पूर्णांकerface *अगरace,
		       काष्ठा list_head *midi_list,
		       स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	वापस __snd_usbmidi_create(card, अगरace, midi_list, quirk, 0);
पूर्ण

व्योम snd_usbmidi_input_stop(काष्ठा list_head *p);
व्योम snd_usbmidi_input_start(काष्ठा list_head *p);
व्योम snd_usbmidi_disconnect(काष्ठा list_head *p);
व्योम snd_usbmidi_suspend(काष्ठा list_head *p);
व्योम snd_usbmidi_resume(काष्ठा list_head *p);

#पूर्ण_अगर /* __USBMIDI_H */
