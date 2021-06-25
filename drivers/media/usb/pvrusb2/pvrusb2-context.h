<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_CONTEXT_H
#घोषणा __PVRUSB2_CONTEXT_H

#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>

काष्ठा pvr2_hdw;     /* hardware पूर्णांकerface - defined अन्यथाwhere */
काष्ठा pvr2_stream;  /* stream पूर्णांकerface - defined अन्यथाwhere */

काष्ठा pvr2_context;        /* All central state */
काष्ठा pvr2_channel;        /* One I/O pathway to a user */
काष्ठा pvr2_context_stream; /* Wrapper क्रम a stream */
काष्ठा pvr2_ioपढ़ो;         /* Low level stream काष्ठाure */

काष्ठा pvr2_context_stream अणु
	काष्ठा pvr2_channel *user;
	काष्ठा pvr2_stream *stream;
पूर्ण;

काष्ठा pvr2_context अणु
	काष्ठा pvr2_channel *mc_first;
	काष्ठा pvr2_channel *mc_last;
	काष्ठा pvr2_context *exist_next;
	काष्ठा pvr2_context *exist_prev;
	काष्ठा pvr2_context *notअगरy_next;
	काष्ठा pvr2_context *notअगरy_prev;
	काष्ठा pvr2_hdw *hdw;
	काष्ठा pvr2_context_stream video_stream;
	काष्ठा mutex mutex;
	पूर्णांक notअगरy_flag;
	पूर्णांक initialized_flag;
	पूर्णांक disconnect_flag;

	/* Called after pvr2_context initialization is complete */
	व्योम (*setup_func)(काष्ठा pvr2_context *);

पूर्ण;

काष्ठा pvr2_channel अणु
	काष्ठा pvr2_context *mc_head;
	काष्ठा pvr2_channel *mc_next;
	काष्ठा pvr2_channel *mc_prev;
	काष्ठा pvr2_context_stream *stream;
	काष्ठा pvr2_hdw *hdw;
	अचिन्हित पूर्णांक input_mask;
	व्योम (*check_func)(काष्ठा pvr2_channel *);
पूर्ण;

काष्ठा pvr2_context *pvr2_context_create(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					 स्थिर काष्ठा usb_device_id *devid,
					 व्योम (*setup_func)(काष्ठा pvr2_context *));
व्योम pvr2_context_disconnect(काष्ठा pvr2_context *);

व्योम pvr2_channel_init(काष्ठा pvr2_channel *,काष्ठा pvr2_context *);
व्योम pvr2_channel_करोne(काष्ठा pvr2_channel *);
पूर्णांक pvr2_channel_limit_inमाला_दो(काष्ठा pvr2_channel *,अचिन्हित पूर्णांक);
अचिन्हित पूर्णांक pvr2_channel_get_limited_inमाला_दो(काष्ठा pvr2_channel *);
पूर्णांक pvr2_channel_claim_stream(काष्ठा pvr2_channel *,
			      काष्ठा pvr2_context_stream *);
काष्ठा pvr2_ioपढ़ो *pvr2_channel_create_mpeg_stream(
	काष्ठा pvr2_context_stream *);

पूर्णांक pvr2_context_global_init(व्योम);
व्योम pvr2_context_global_करोne(व्योम);

#पूर्ण_अगर /* __PVRUSB2_CONTEXT_H */
