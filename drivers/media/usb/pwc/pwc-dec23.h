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

#अगर_अघोषित PWC_DEC23_H
#घोषणा PWC_DEC23_H

काष्ठा pwc_device;

काष्ठा pwc_dec23_निजी
अणु
	काष्ठा mutex lock;

	अचिन्हित अक्षर last_cmd, last_cmd_valid;

  अचिन्हित पूर्णांक scalebits;
  अचिन्हित पूर्णांक nbitsmask, nbits; /* Number of bits of a color in the compressed stream */

  अचिन्हित पूर्णांक reservoir;
  अचिन्हित पूर्णांक nbits_in_reservoir;

  स्थिर अचिन्हित अक्षर *stream;
  पूर्णांक temp_colors[16];

  अचिन्हित अक्षर table_0004_pass1[16][1024];
  अचिन्हित अक्षर table_0004_pass2[16][1024];
  अचिन्हित अक्षर table_8004_pass1[16][256];
  अचिन्हित अक्षर table_8004_pass2[16][256];
  अचिन्हित पूर्णांक  table_subblock[256][12];

  अचिन्हित अक्षर table_bitघातermask[8][256];
  अचिन्हित पूर्णांक  table_d800[256];
  अचिन्हित पूर्णांक  table_dc00[256];

पूर्ण;

व्योम pwc_dec23_init(काष्ठा pwc_device *pdev, स्थिर अचिन्हित अक्षर *cmd);
व्योम pwc_dec23_decompress(काष्ठा pwc_device *pdev,
			  स्थिर व्योम *src,
			  व्योम *dst);
#पूर्ण_अगर
