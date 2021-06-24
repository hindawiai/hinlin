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

#अगर_अघोषित PWC_DEC1_H
#घोषणा PWC_DEC1_H

#समावेश <linux/mutex.h>

काष्ठा pwc_device;

काष्ठा pwc_dec1_निजी
अणु
	पूर्णांक version;
पूर्ण;

व्योम pwc_dec1_init(काष्ठा pwc_device *pdev, स्थिर अचिन्हित अक्षर *cmd);

#पूर्ण_अगर
