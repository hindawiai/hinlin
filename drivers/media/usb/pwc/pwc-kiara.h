<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Linux driver क्रम Philips webcam
   (C) 2004-2006 Luc Saillard (luc@saillard.org)

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.

*/

/* Entries क्रम the Kiara (730/740/750) camera */

#अगर_अघोषित PWC_KIARA_H
#घोषणा PWC_KIARA_H

#समावेश "pwc.h"

#घोषणा PWC_FPS_MAX_KIARA 6

काष्ठा Kiara_table_entry
अणु
	अक्षर alternate;			/* USB alternate पूर्णांकerface */
	अचिन्हित लघु packetsize;	/* Normal packet size */
	अचिन्हित लघु bandlength;	/* Bandlength when decompressing */
	अचिन्हित अक्षर mode[12];		/* precomputed mode settings क्रम cam */
पूर्ण;

बाह्य स्थिर काष्ठा Kiara_table_entry Kiara_table[PSZ_MAX][PWC_FPS_MAX_KIARA][4];
बाह्य स्थिर अचिन्हित पूर्णांक KiaraRomTable[8][2][16][8];
बाह्य स्थिर अचिन्हित पूर्णांक Kiara_fps_vector[PWC_FPS_MAX_KIARA];

#पूर्ण_अगर


