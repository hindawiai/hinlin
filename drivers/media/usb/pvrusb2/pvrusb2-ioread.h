<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_IOREAD_H
#घोषणा __PVRUSB2_IOREAD_H

#समावेश "pvrusb2-io.h"

काष्ठा pvr2_ioपढ़ो;

काष्ठा pvr2_ioपढ़ो *pvr2_ioपढ़ो_create(व्योम);
व्योम pvr2_ioपढ़ो_destroy(काष्ठा pvr2_ioपढ़ो *);
पूर्णांक pvr2_ioपढ़ो_setup(काष्ठा pvr2_ioपढ़ो *,काष्ठा pvr2_stream *);
काष्ठा pvr2_stream *pvr2_ioपढ़ो_get_stream(काष्ठा pvr2_ioपढ़ो *);
व्योम pvr2_ioपढ़ो_set_sync_key(काष्ठा pvr2_ioपढ़ो *,
			      स्थिर अक्षर *sync_key_ptr,
			      अचिन्हित पूर्णांक sync_key_len);
पूर्णांक pvr2_ioपढ़ो_set_enabled(काष्ठा pvr2_ioपढ़ो *,पूर्णांक fl);
पूर्णांक pvr2_ioपढ़ो_पढ़ो(काष्ठा pvr2_ioपढ़ो *,व्योम __user *buf,अचिन्हित पूर्णांक cnt);
पूर्णांक pvr2_ioपढ़ो_avail(काष्ठा pvr2_ioपढ़ो *);

#पूर्ण_अगर /* __PVRUSB2_IOREAD_H */
