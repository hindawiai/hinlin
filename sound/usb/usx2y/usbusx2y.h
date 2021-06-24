<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित USBUSX2Y_H
#घोषणा USBUSX2Y_H
#समावेश "../usbaudio.h"
#समावेश "../midi.h"
#समावेश "usbus428ctldefs.h" 

#घोषणा NRURBS	        2	


#घोषणा URBS_AsyncSeq 10
#घोषणा URB_DataLen_AsyncSeq 32
काष्ठा snd_usX2Y_AsyncSeq अणु
	काष्ठा urb	*urb[URBS_AsyncSeq];
	अक्षर		*buffer;
पूर्ण;

काष्ठा snd_usX2Y_urbSeq अणु
	पूर्णांक	submitted;
	पूर्णांक	len;
	काष्ठा urb	*urb[];
पूर्ण;

#समावेश "usx2yhwdeppcm.h"

काष्ठा usX2Ydev अणु
	काष्ठा usb_device	*dev;
	पूर्णांक			card_index;
	पूर्णांक			stride;
	काष्ठा urb		*In04urb;
	व्योम			*In04Buf;
	अक्षर			In04Last[24];
	अचिन्हित		In04IntCalls;
	काष्ठा snd_usX2Y_urbSeq	*US04;
	रुको_queue_head_t	In04WaitQueue;
	काष्ठा snd_usX2Y_AsyncSeq	AS04;
	अचिन्हित पूर्णांक		rate,
				क्रमmat;
	पूर्णांक			chip_status;
	काष्ठा mutex		pcm_mutex;
	काष्ठा us428ctls_sharedmem	*us428ctls_sharedmem;
	पूर्णांक			रुको_iso_frame;
	रुको_queue_head_t	us428ctls_रुको_queue_head;
	काष्ठा snd_usX2Y_hwdep_pcm_shm	*hwdep_pcm_shm;
	काष्ठा snd_usX2Y_substream	*subs[4];
	काष्ठा snd_usX2Y_substream	* अस्थिर  prepare_subs;
	रुको_queue_head_t	prepare_रुको_queue;
	काष्ठा list_head	midi_list;
	काष्ठा list_head	pcm_list;
	पूर्णांक			pcm_devs;
पूर्ण;


काष्ठा snd_usX2Y_substream अणु
	काष्ठा usX2Ydev	*usX2Y;
	काष्ठा snd_pcm_substream *pcm_substream;

	पूर्णांक			endpoपूर्णांक;		
	अचिन्हित पूर्णांक		maxpacksize;		/* max packet size in bytes */

	atomic_t		state;
#घोषणा state_STOPPED	0
#घोषणा state_STARTING1 1
#घोषणा state_STARTING2 2
#घोषणा state_STARTING3 3
#घोषणा state_PREPARED	4
#घोषणा state_PRERUNNING  6
#घोषणा state_RUNNING	8

	पूर्णांक			hwptr;			/* मुक्त frame position in the buffer (only क्रम playback) */
	पूर्णांक			hwptr_करोne;		/* processed frame position in the buffer */
	पूर्णांक			transfer_करोne;		/* processed frames since last period update */

	काष्ठा urb		*urb[NRURBS];	/* data urb table */
	काष्ठा urb		*completed_urb;
	अक्षर			*पंचांगpbuf;			/* temporary buffer क्रम playback */
पूर्ण;


#घोषणा usX2Y(c) ((काष्ठा usX2Ydev *)(c)->निजी_data)

पूर्णांक usX2Y_audio_create(काष्ठा snd_card *card);

पूर्णांक usX2Y_AsyncSeq04_init(काष्ठा usX2Ydev *usX2Y);
पूर्णांक usX2Y_In04_init(काष्ठा usX2Ydev *usX2Y);

#घोषणा NAME_ALLCAPS "US-X2Y"

#पूर्ण_अगर
