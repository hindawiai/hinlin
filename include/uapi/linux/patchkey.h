<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
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

#अगर_अघोषित _LINUX_PATCHKEY_H_INसूचीECT
#त्रुटि "patchkey.h included directly"
#पूर्ण_अगर

#अगर_अघोषित _UAPI_LINUX_PATCHKEY_H
#घोषणा _UAPI_LINUX_PATCHKEY_H

/* Endian macros. */
#अगर_अघोषित __KERNEL__
#  include <endian.h>
#पूर्ण_अगर

#अगर !defined(__KERNEL__)
#अगर defined(__BYTE_ORDER)
#  अगर __BYTE_ORDER == __BIG_ENDIAN
#    define _PATCHKEY(id) (0xfd00|id)
#  elअगर __BYTE_ORDER == __LITTLE_ENDIAN
#    define _PATCHKEY(id) ((id<<8)|0x00fd)
#  अन्यथा
#    error "could not determine byte order"
#  endअगर
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_LINUX_PATCHKEY_H */
