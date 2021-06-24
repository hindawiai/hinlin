<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#अगर_अघोषित __DEBUG_H__
#घोषणा __DEBUG_H__

#समावेश <linux/prपूर्णांकk.h>

#अगर_अघोषित VIAFB_DEBUG
#घोषणा VIAFB_DEBUG 0
#पूर्ण_अगर

#अगर VIAFB_DEBUG
#घोषणा DEBUG_MSG(f, a...)   prपूर्णांकk(f, ## a)
#अन्यथा
#घोषणा DEBUG_MSG(f, a...)   no_prपूर्णांकk(f, ## a)
#पूर्ण_अगर

#घोषणा VIAFB_WARN 0
#अगर VIAFB_WARN
#घोषणा WARN_MSG(f, a...)   prपूर्णांकk(f, ## a)
#अन्यथा
#घोषणा WARN_MSG(f, a...)   no_prपूर्णांकk(f, ## a)
#पूर्ण_अगर

#पूर्ण_अगर /* __DEBUG_H__ */
