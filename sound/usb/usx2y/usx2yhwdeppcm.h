<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा MAXPACK 50
#घोषणा MAXBUFFERMS 100
#घोषणा MAXSTRIDE 3

#घोषणा SSS (((MAXPACK*MAXBUFFERMS*MAXSTRIDE + 4096) / 4096) * 4096)
काष्ठा snd_usX2Y_hwdep_pcm_shm अणु
	अक्षर playback[SSS];
	अक्षर capture0x8[SSS];
	अक्षर capture0xA[SSS];
	अस्थिर पूर्णांक playback_iso_head;
	पूर्णांक playback_iso_start;
	काष्ठा अणु
		पूर्णांक	frame,
			offset,
			length;
	पूर्ण captured_iso[128];
	अस्थिर पूर्णांक captured_iso_head;
	अस्थिर अचिन्हित captured_iso_frames;
	पूर्णांक capture_iso_start;
पूर्ण;

पूर्णांक usX2Y_hwdep_pcm_new(काष्ठा snd_card *card);
