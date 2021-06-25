<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Linux driver क्रम Philips webcam
   Decompression frontend.
   (C) 1999-2003 Nemosoft Unv.
   (C) 2004-2006 Luc Saillard (luc@saillard.org)

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.
*/

#समावेश <यंत्र/current.h>
#समावेश <यंत्र/types.h>

#समावेश "pwc.h"
#समावेश "pwc-dec1.h"
#समावेश "pwc-dec23.h"

पूर्णांक pwc_decompress(काष्ठा pwc_device *pdev, काष्ठा pwc_frame_buf *fbuf)
अणु
	पूर्णांक n, line, col;
	व्योम *yuv, *image;
	u16 *src;
	u16 *dsty, *dstu, *dstv;

	image = vb2_plane_vaddr(&fbuf->vb.vb2_buf, 0);

	yuv = fbuf->data + pdev->frame_header_size;  /* Skip header */

	/* Raw क्रमmat; that's easy... */
	अगर (pdev->pixfmt != V4L2_PIX_FMT_YUV420)
	अणु
		काष्ठा pwc_raw_frame *raw_frame = image;
		raw_frame->type = cpu_to_le16(pdev->type);
		raw_frame->vbandlength = cpu_to_le16(pdev->vbandlength);
			/* cmd_buf is always 4 bytes, but someबार, only the
			 * first 3 bytes is filled (Nala हाल). We can
			 * determine this using the type of the webcam */
		स_नकल(raw_frame->cmd, pdev->cmd_buf, 4);
		स_नकल(raw_frame+1, yuv, pdev->frame_size);
		vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0,
			pdev->frame_size + माप(काष्ठा pwc_raw_frame));
		वापस 0;
	पूर्ण

	vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0,
			      pdev->width * pdev->height * 3 / 2);

	अगर (pdev->vbandlength == 0) अणु
		/* Uncompressed mode.
		 *
		 * We करो some byte shuffling here to go from the
		 * native क्रमmat to YUV420P.
		 */
		src = (u16 *)yuv;
		n = pdev->width * pdev->height;
		dsty = (u16 *)(image);
		dstu = (u16 *)(image + n);
		dstv = (u16 *)(image + n + n / 4);

		क्रम (line = 0; line < pdev->height; line++) अणु
			क्रम (col = 0; col < pdev->width; col += 4) अणु
				*dsty++ = *src++;
				*dsty++ = *src++;
				अगर (line & 1)
					*dstv++ = *src++;
				अन्यथा
					*dstu++ = *src++;
			पूर्ण
		पूर्ण

		वापस 0;
	पूर्ण

	/*
	 * Compressed;
	 * the decompressor routines will ग_लिखो the data in planar क्रमmat
	 * immediately.
	 */
	अगर (DEVICE_USE_CODEC1(pdev->type)) अणु

		/* TODO & FIXME */
		PWC_ERROR("This chipset is not supported for now\n");
		वापस -ENXIO; /* No such device or address: missing decompressor */

	पूर्ण अन्यथा अणु
		pwc_dec23_decompress(pdev, yuv, image);
	पूर्ण
	वापस 0;
पूर्ण
