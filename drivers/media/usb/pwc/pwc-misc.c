<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Linux driver क्रम Philips webcam
   Various miscellaneous functions and tables.
   (C) 1999-2003 Nemosoft Unv.
   (C) 2004-2006 Luc Saillard (luc@saillard.org)

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.

*/


#समावेश "pwc.h"

स्थिर पूर्णांक pwc_image_sizes[PSZ_MAX][2] =
अणु
	अणु 128,  96 पूर्ण, /* sqcअगर */
	अणु 160, 120 पूर्ण, /* qsअगर */
	अणु 176, 144 पूर्ण, /* qcअगर */
	अणु 320, 240 पूर्ण, /* sअगर */
	अणु 352, 288 पूर्ण, /* cअगर */
	अणु 640, 480 पूर्ण, /* vga */
पूर्ण;

/* x,y -> PSZ_ */
पूर्णांक pwc_get_size(काष्ठा pwc_device *pdev, पूर्णांक width, पूर्णांक height)
अणु
	पूर्णांक i;

	/* Find the largest size supported by the camera that fits पूर्णांकo the
	   requested size. */
	क्रम (i = PSZ_MAX - 1; i >= 0; i--) अणु
		अगर (!(pdev->image_mask & (1 << i)))
			जारी;

		अगर (pwc_image_sizes[i][0] <= width &&
		    pwc_image_sizes[i][1] <= height)
			वापस i;
	पूर्ण

	/* No mode found, वापस the smallest mode we have */
	क्रम (i = 0; i < PSZ_MAX; i++) अणु
		अगर (pdev->image_mask & (1 << i))
			वापस i;
	पूर्ण

	/* Never reached there always is at least one supported mode */
	वापस 0;
पूर्ण

/* initialize variables depending on type and decompressor */
व्योम pwc_स्थिरruct(काष्ठा pwc_device *pdev)
अणु
	अगर (DEVICE_USE_CODEC1(pdev->type)) अणु

		pdev->image_mask = 1 << PSZ_SQCIF | 1 << PSZ_QCIF | 1 << PSZ_CIF;
		pdev->vcपूर्णांकerface = 2;
		pdev->vendpoपूर्णांक = 4;
		pdev->frame_header_size = 0;
		pdev->frame_trailer_size = 0;

	पूर्ण अन्यथा अगर (DEVICE_USE_CODEC3(pdev->type)) अणु

		pdev->image_mask = 1 << PSZ_QSIF | 1 << PSZ_SIF | 1 << PSZ_VGA;
		pdev->vcपूर्णांकerface = 3;
		pdev->vendpoपूर्णांक = 5;
		pdev->frame_header_size = TOUCAM_HEADER_SIZE;
		pdev->frame_trailer_size = TOUCAM_TRAILER_SIZE;

	पूर्ण अन्यथा /* अगर (DEVICE_USE_CODEC2(pdev->type)) */ अणु

		pdev->image_mask = 1 << PSZ_SQCIF | 1 << PSZ_QSIF | 1 << PSZ_QCIF | 1 << PSZ_SIF | 1 << PSZ_CIF | 1 << PSZ_VGA;
		pdev->vcपूर्णांकerface = 3;
		pdev->vendpoपूर्णांक = 4;
		pdev->frame_header_size = 0;
		pdev->frame_trailer_size = 0;
	पूर्ण
पूर्ण
