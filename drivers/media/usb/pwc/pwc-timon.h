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



/* This tables contains entries क्रम the 675/680/690 (Timon) camera, with
   4 dअगरferent qualities (no compression, low, medium, high).
   It lists the bandwidth requirements क्रम said mode by its alternate पूर्णांकerface
   number. An alternate of 0 means that the mode is unavailable.

   There are 6 * 4 * 4 entries:
     6 dअगरferent resolutions subqcअगर, qsअगर, qcअगर, sअगर, cअगर, vga
     6 framerates: 5, 10, 15, 20, 25, 30
     4 compression modi: none, low, medium, high

   When an uncompressed mode is not available, the next available compressed mode
   will be chosen (unless the decompressor is असलent). Someबार there are only
   1 or 2 compressed modes available; in that हाल entries are duplicated.
*/

#अगर_अघोषित PWC_TIMON_H
#घोषणा PWC_TIMON_H

#समावेश "pwc.h"

#घोषणा PWC_FPS_MAX_TIMON 6

काष्ठा Timon_table_entry
अणु
	अक्षर alternate;			/* USB alternate पूर्णांकerface */
	अचिन्हित लघु packetsize;	/* Normal packet size */
	अचिन्हित लघु bandlength;	/* Bandlength when decompressing */
	अचिन्हित अक्षर mode[13];		/* precomputed mode settings क्रम cam */
पूर्ण;

बाह्य स्थिर काष्ठा Timon_table_entry Timon_table[PSZ_MAX][PWC_FPS_MAX_TIMON][4];
बाह्य स्थिर अचिन्हित पूर्णांक TimonRomTable [16][2][16][8];
बाह्य स्थिर अचिन्हित पूर्णांक Timon_fps_vector[PWC_FPS_MAX_TIMON];

#पूर्ण_अगर


