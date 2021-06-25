<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_AMDTP_AM824_H_INCLUDED
#घोषणा SOUND_FIREWIRE_AMDTP_AM824_H_INCLUDED

#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>

#समावेश "amdtp-stream.h"

#घोषणा AM824_IN_PCM_FORMAT_BITS	SNDRV_PCM_FMTBIT_S32

#घोषणा AM824_OUT_PCM_FORMAT_BITS	SNDRV_PCM_FMTBIT_S32

/*
 * This module supports maximum 64 PCM channels क्रम one PCM stream
 * This is क्रम our convenience.
 */
#घोषणा AM824_MAX_CHANNELS_FOR_PCM	64

/*
 * AMDTP packet can include channels क्रम MIDI conक्रमmant data.
 * Each MIDI conक्रमmant data channel includes 8 MPX-MIDI data stream.
 * Each MPX-MIDI data stream includes one data stream from/to MIDI ports.
 *
 * This module supports maximum 1 MIDI conक्रमmant data channels.
 * Then this AMDTP packets can transfer maximum 8 MIDI data streams.
 */
#घोषणा AM824_MAX_CHANNELS_FOR_MIDI	1

पूर्णांक amdtp_am824_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			       अचिन्हित पूर्णांक pcm_channels,
			       अचिन्हित पूर्णांक midi_ports,
			       bool द्विगुन_pcm_frames);

व्योम amdtp_am824_set_pcm_position(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक index,
				 अचिन्हित पूर्णांक position);

व्योम amdtp_am824_set_midi_position(काष्ठा amdtp_stream *s,
				   अचिन्हित पूर्णांक position);

पूर्णांक amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				       काष्ठा snd_pcm_runसमय *runसमय);

व्योम amdtp_am824_midi_trigger(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port,
			      काष्ठा snd_rawmidi_substream *midi);

पूर्णांक amdtp_am824_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		     क्रमागत amdtp_stream_direction dir, क्रमागत cip_flags flags);
#पूर्ण_अगर
