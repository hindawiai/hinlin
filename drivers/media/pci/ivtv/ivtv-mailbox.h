<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    mailbox functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_MAILBOX_H
#घोषणा IVTV_MAILBOX_H

#घोषणा IVTV_MBOX_DMA_END         8
#घोषणा IVTV_MBOX_DMA             9

व्योम ivtv_api_get_data(काष्ठा ivtv_mailbox_data *mbdata, पूर्णांक mb,
		       पूर्णांक argc, u32 data[]);
पूर्णांक ivtv_api(काष्ठा ivtv *itv, पूर्णांक cmd, पूर्णांक args, u32 data[]);
पूर्णांक ivtv_vapi_result(काष्ठा ivtv *itv, u32 data[CX2341X_MBOX_MAX_DATA], पूर्णांक cmd, पूर्णांक args, ...);
पूर्णांक ivtv_vapi(काष्ठा ivtv *itv, पूर्णांक cmd, पूर्णांक args, ...);
पूर्णांक ivtv_api_func(व्योम *priv, u32 cmd, पूर्णांक in, पूर्णांक out, u32 data[CX2341X_MBOX_MAX_DATA]);
व्योम ivtv_mailbox_cache_invalidate(काष्ठा ivtv *itv);

#पूर्ण_अगर
