<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011 Broadcom Corporation.  All rights reserved. */

#अगर_अघोषित _VC_AUDIO_DEFS_H_
#घोषणा _VC_AUDIO_DEFS_H_

#घोषणा VC_AUDIOSERV_MIN_VER 1
#घोषणा VC_AUDIOSERV_VER 2

/* FourCC codes used क्रम VCHI communication */
#घोषणा VC_AUDIO_WRITE_COOKIE1 VCHIQ_MAKE_FOURCC('B', 'C', 'M', 'A')
#घोषणा VC_AUDIO_WRITE_COOKIE2 VCHIQ_MAKE_FOURCC('D', 'A', 'T', 'A')

/*
 *  List of screens that are currently supported
 *  All message types supported क्रम HOST->VC direction
 */

क्रमागत vc_audio_msg_type अणु
	VC_AUDIO_MSG_TYPE_RESULT, // Generic result
	VC_AUDIO_MSG_TYPE_COMPLETE, // Generic result
	VC_AUDIO_MSG_TYPE_CONFIG, // Configure audio
	VC_AUDIO_MSG_TYPE_CONTROL, // Configure audio
	VC_AUDIO_MSG_TYPE_OPEN, // Configure audio
	VC_AUDIO_MSG_TYPE_CLOSE, // Configure audio
	VC_AUDIO_MSG_TYPE_START, // Configure audio
	VC_AUDIO_MSG_TYPE_STOP, // Configure audio
	VC_AUDIO_MSG_TYPE_WRITE, // Configure audio
	VC_AUDIO_MSG_TYPE_MAX
पूर्ण;

/* configure the audio */

काष्ठा vc_audio_config अणु
	u32 channels;
	u32 samplerate;
	u32 bps;
पूर्ण;

काष्ठा vc_audio_control अणु
	u32 volume;
	u32 dest;
पूर्ण;

काष्ठा vc_audio_खोलो अणु
	u32 dummy;
पूर्ण;

काष्ठा vc_audio_बंद अणु
	u32 dummy;
पूर्ण;

काष्ठा vc_audio_start अणु
	u32 dummy;
पूर्ण;

काष्ठा vc_audio_stop अणु
	u32 draining;
पूर्ण;

/* configure the ग_लिखो audio samples */
काष्ठा vc_audio_ग_लिखो अणु
	u32 count; // in bytes
	u32 cookie1;
	u32 cookie2;
	s16 silence;
	s16 max_packet;
पूर्ण;

/* Generic result क्रम a request (VC->HOST) */
काष्ठा vc_audio_result अणु
	s32 success; // Success value
पूर्ण;

/* Generic result क्रम a request (VC->HOST) */
काष्ठा vc_audio_complete अणु
	s32 count; // Success value
	u32 cookie1;
	u32 cookie2;
पूर्ण;

/* Message header क्रम all messages in HOST->VC direction */
काष्ठा vc_audio_msg अणु
	s32 type; /* Message type (VC_AUDIO_MSG_TYPE) */
	जोड़ अणु
		काष्ठा vc_audio_config config;
		काष्ठा vc_audio_control control;
		काष्ठा vc_audio_खोलो खोलो;
		काष्ठा vc_audio_बंद बंद;
		काष्ठा vc_audio_start start;
		काष्ठा vc_audio_stop stop;
		काष्ठा vc_audio_ग_लिखो ग_लिखो;
		काष्ठा vc_audio_result result;
		काष्ठा vc_audio_complete complete;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* _VC_AUDIO_DEFS_H_ */
