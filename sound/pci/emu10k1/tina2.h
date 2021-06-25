<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) by James Courtier-Dutton <James@superbug.demon.co.uk>
 *  Driver tina2 chips
 *  Version: 0.1
 */

/********************************************************************************************************/
/* Audigy2 Tina2 (notebook) poपूर्णांकer-offset रेजिस्टर set, accessed through the PTR2 and DATA2 रेजिस्टरs  */
/********************************************************************************************************/

#घोषणा TINA2_VOLUME	0x71	/* Attenuate playback volume to prevent distortion. */
				/* The winकरोws driver करोes not use this रेजिस्टर,
				 * so it must use some other attenuation method.
				 * Without this, the output is 12dB too loud,
				 * resulting in distortion.
				 */

