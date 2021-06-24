<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Linux driver क्रम Philips webcam
   Decompression क्रम chipset version 1
   (C) 2004-2006 Luc Saillard (luc@saillard.org)

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.

*/
#समावेश "pwc.h"

व्योम pwc_dec1_init(काष्ठा pwc_device *pdev, स्थिर अचिन्हित अक्षर *cmd)
अणु
	काष्ठा pwc_dec1_निजी *pdec = &pdev->dec1;

	pdec->version = pdev->release;
पूर्ण
