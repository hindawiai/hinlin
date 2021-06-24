<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * <linux/patchkey.h> -- definition of _PATCHKEY macro
 *
 * Copyright (C) 2005 Stuart Brady
 *
 * This exists because awe_voice.h defined its own _PATCHKEY and it wasn't
 * clear whether removing this would अवरोध anything in userspace.
 *
 * Do not include this file directly.  Please use <sys/soundcard.h> instead.
 * For kernel code, use <linux/soundcard.h>
 */
#अगर_अघोषित _LINUX_PATCHKEY_H
#घोषणा _LINUX_PATCHKEY_H

#  include <यंत्र/byteorder.h>
#समावेश <uapi/linux/patchkey.h>

#  अगर defined(__BIG_ENDIAN)
#    define _PATCHKEY(id) (0xfd00|id)
#  elअगर defined(__LITTLE_ENDIAN)
#    define _PATCHKEY(id) ((id<<8)|0x00fd)
#  अन्यथा
#    error "could not determine byte order"
#  endअगर
#पूर्ण_अगर /* _LINUX_PATCHKEY_H */
