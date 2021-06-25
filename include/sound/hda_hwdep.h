<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * HWDEP Interface क्रम HD-audio codec
 *
 * Copyright (c) 2007 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SOUND_HDA_HWDEP_H
#घोषणा __SOUND_HDA_HWDEP_H

#घोषणा HDA_HWDEP_VERSION	((1 << 16) | (0 << 8) | (0 << 0)) /* 1.0.0 */

/* verb */
#घोषणा HDA_REG_NID_SHIFT	24
#घोषणा HDA_REG_VERB_SHIFT	8
#घोषणा HDA_REG_VAL_SHIFT	0
#घोषणा HDA_VERB(nid,verb,param)	((nid)<<24 | (verb)<<8 | (param))

काष्ठा hda_verb_ioctl अणु
	u32 verb;	/* HDA_VERB() */
	u32 res;	/* response */
पूर्ण;

/*
 * ioctls
 */
#घोषणा HDA_IOCTL_PVERSION		_IOR('H', 0x10, पूर्णांक)
#घोषणा HDA_IOCTL_VERB_WRITE		_IOWR('H', 0x11, काष्ठा hda_verb_ioctl)
#घोषणा HDA_IOCTL_GET_WCAP		_IOWR('H', 0x12, काष्ठा hda_verb_ioctl)

#पूर्ण_अगर
