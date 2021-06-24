<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Tascam US-X2Y USB soundcards
 *
 * Copyright (c) 2003 by Karsten Wiese <annabellesgarden@yahoo.de>
 */

#अगर_अघोषित __SOUND_USX2Y_COMMON_H
#घोषणा __SOUND_USX2Y_COMMON_H


#घोषणा USX2Y_DRIVER_VERSION	0x0100	/* 0.1.0 */


/* hwdep id string */
#घोषणा SND_USX2Y_LOADER_ID		"USX2Y Loader"
#घोषणा SND_USX2Y_USBPCM_ID		"USX2Y USBPCM"

/* hardware type */
क्रमागत अणु
	USX2Y_TYPE_122,
	USX2Y_TYPE_224,
	USX2Y_TYPE_428,
	USX2Y_TYPE_NUMS
पूर्ण;

#घोषणा USB_ID_US122 0x8007
#घोषणा USB_ID_US224 0x8005
#घोषणा USB_ID_US428 0x8001

/* chip status */
क्रमागत अणु
	USX2Y_STAT_CHIP_INIT	=	(1 << 0),	/* all operational */
	USX2Y_STAT_CHIP_MMAP_PCM_URBS = (1 << 1),	/* pcm transport over mmaped urbs */
	USX2Y_STAT_CHIP_HUP	=	(1 << 31),	/* all operational */
पूर्ण;

#पूर्ण_अगर /* __SOUND_USX2Y_COMMON_H */
