<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// DVB USB compliant linux driver क्रम Conexant USB reference design -
// (analog part).
//
// Copyright (C) 2011, 2017, 2018
//	Maciej S. Szmigiero (mail@maciej.szmigiero.name)
//
// In हाल there are new analog / DVB-T hybrid devices released in the market
// using the same general design as Medion MD95700: a CX25840 video decoder
// outputting a BT.656 stream to a USB bridge chip which then क्रमwards it to
// the host in isochronous USB packets this code should be made generic, with
// board specअगरic bits implemented via separate card काष्ठाures.
//
// This is, however, unlikely as the Medion model was released
// years ago (in 2005).
//
// TODO:
//  * audio support,
//  * finish radio support (requires audio of course),
//  * VBI support,
//  * controls support

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <media/drv-पूर्णांकf/cx25840.h>
#समावेश <media/tuner.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "cxusb.h"

अटल पूर्णांक cxusb_medion_v_queue_setup(काष्ठा vb2_queue *q,
				      अचिन्हित पूर्णांक *num_buffers,
				      अचिन्हित पूर्णांक *num_planes,
				      अचिन्हित पूर्णांक sizes[],
				      काष्ठा device *alloc_devs[])
अणु
	काष्ठा dvb_usb_device *dvbdev = vb2_get_drv_priv(q);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	अचिन्हित पूर्णांक size = cxdev->width * cxdev->height * 2;

	अगर (*num_planes > 0) अणु
		अगर (*num_planes != 1)
			वापस -EINVAL;

		अगर (sizes[0] < size)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		*num_planes = 1;
		sizes[0] = size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_v_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा dvb_usb_device *dvbdev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "buffer init\n");

	अगर (vb2_plane_size(vb, 0) < cxdev->width * cxdev->height * 2)
		वापस -ENOMEM;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "buffer OK\n");

	वापस 0;
पूर्ण

अटल व्योम cxusb_auxbuf_init(काष्ठा dvb_usb_device *dvbdev,
			      काष्ठा cxusb_medion_auxbuf *auxbuf,
			      u8 *buf, अचिन्हित पूर्णांक len)
अणु
	cxusb_vprपूर्णांकk(dvbdev, AUXB, "initializing auxbuf of len %u\n", len);

	auxbuf->buf = buf;
	auxbuf->len = len;
	auxbuf->paylen = 0;
पूर्ण

अटल व्योम cxusb_auxbuf_head_trim(काष्ठा dvb_usb_device *dvbdev,
				   काष्ठा cxusb_medion_auxbuf *auxbuf,
				   अचिन्हित पूर्णांक pos)
अणु
	अगर (pos == 0)
		वापस;

	अगर (WARN_ON(pos > auxbuf->paylen))
		वापस;

	cxusb_vprपूर्णांकk(dvbdev, AUXB,
		      "trimming auxbuf len by %u to %u\n",
		      pos, auxbuf->paylen - pos);

	स_हटाओ(auxbuf->buf, auxbuf->buf + pos, auxbuf->paylen - pos);
	auxbuf->paylen -= pos;
पूर्ण

अटल अचिन्हित पूर्णांक cxusb_auxbuf_paylen(काष्ठा cxusb_medion_auxbuf *auxbuf)
अणु
	वापस auxbuf->paylen;
पूर्ण

अटल bool cxusb_auxbuf_make_space(काष्ठा dvb_usb_device *dvbdev,
				    काष्ठा cxusb_medion_auxbuf *auxbuf,
				    अचिन्हित पूर्णांक howmuch)
अणु
	अचिन्हित पूर्णांक मुक्तspace;

	अगर (WARN_ON(howmuch >= auxbuf->len))
		howmuch = auxbuf->len - 1;

	मुक्तspace = auxbuf->len - cxusb_auxbuf_paylen(auxbuf);

	cxusb_vprपूर्णांकk(dvbdev, AUXB, "freespace is %u\n", मुक्तspace);

	अगर (मुक्तspace >= howmuch)
		वापस true;

	howmuch -= मुक्तspace;

	cxusb_vprपूर्णांकk(dvbdev, AUXB, "will overwrite %u bytes of buffer\n",
		      howmuch);

	cxusb_auxbuf_head_trim(dvbdev, auxbuf, howmuch);

	वापस false;
पूर्ण

/* वापसs false अगर some data was overwritten */
अटल bool cxusb_auxbuf_append_urb(काष्ठा dvb_usb_device *dvbdev,
				    काष्ठा cxusb_medion_auxbuf *auxbuf,
				    काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ len;
	पूर्णांक i;
	bool ret;

	क्रम (i = 0, len = 0; i < urb->number_of_packets; i++)
		len += urb->iso_frame_desc[i].actual_length;

	ret = cxusb_auxbuf_make_space(dvbdev, auxbuf, len);

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		अचिन्हित पूर्णांक to_copy;

		to_copy = urb->iso_frame_desc[i].actual_length;

		स_नकल(auxbuf->buf + auxbuf->paylen, urb->transfer_buffer +
		       urb->iso_frame_desc[i].offset, to_copy);

		auxbuf->paylen += to_copy;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool cxusb_auxbuf_copy(काष्ठा cxusb_medion_auxbuf *auxbuf,
			      अचिन्हित पूर्णांक pos, अचिन्हित अक्षर *dest,
			      अचिन्हित पूर्णांक len)
अणु
	अगर (pos + len > auxbuf->paylen)
		वापस false;

	स_नकल(dest, auxbuf->buf + pos, len);

	वापस true;
पूर्ण

अटल bool cxusb_medion_cf_refc_fld_chg(काष्ठा dvb_usb_device *dvbdev,
					 काष्ठा cxusb_bt656_params *bt656,
					 bool firstfield,
					 अचिन्हित पूर्णांक maxlines,
					 अचिन्हित पूर्णांक maxlinesamples,
					 अचिन्हित अक्षर buf[4])
अणु
	bool firstfield_code = (buf[3] & CXUSB_BT656_FIELD_MASK) ==
		CXUSB_BT656_FIELD_1;
	अचिन्हित पूर्णांक remlines;

	अगर (bt656->line == 0 || firstfield == firstfield_code)
		वापस false;

	अगर (bt656->भ_शेषe == LINE_SAMPLES) अणु
		अचिन्हित पूर्णांक remsamples = maxlinesamples -
			bt656->linesamples;

		cxusb_vprपूर्णांकk(dvbdev, BT656,
			      "field %c after line %u field change\n",
			      firstfield ? '1' : '2', bt656->line);

		अगर (bt656->buf && remsamples > 0) अणु
			स_रखो(bt656->buf, 0, remsamples);
			bt656->buf += remsamples;

			cxusb_vprपूर्णांकk(dvbdev, BT656,
				      "field %c line %u %u samples still remaining (of %u)\n",
				      firstfield ? '1' : '2',
				      bt656->line, remsamples,
				      maxlinesamples);
		पूर्ण

		bt656->line++;
	पूर्ण

	remlines = maxlines - bt656->line;
	अगर (bt656->buf && remlines > 0) अणु
		स_रखो(bt656->buf, 0, remlines * maxlinesamples);
		bt656->buf += remlines * maxlinesamples;

		cxusb_vprपूर्णांकk(dvbdev, BT656,
			      "field %c %u lines still remaining (of %u)\n",
			      firstfield ? '1' : '2', remlines,
			      maxlines);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम cxusb_medion_cf_refc_start_sch(काष्ठा dvb_usb_device *dvbdev,
					   काष्ठा cxusb_bt656_params *bt656,
					   bool firstfield,
					   अचिन्हित अक्षर buf[4])
अणु
	bool firstfield_code = (buf[3] & CXUSB_BT656_FIELD_MASK) ==
		CXUSB_BT656_FIELD_1;
	bool sav_code = (buf[3] & CXUSB_BT656_SEAV_MASK) ==
		CXUSB_BT656_SEAV_SAV;
	bool vbi_code = (buf[3] & CXUSB_BT656_VBI_MASK) ==
		CXUSB_BT656_VBI_ON;

	अगर (!sav_code || firstfield != firstfield_code)
		वापस;

	अगर (!vbi_code) अणु
		cxusb_vprपूर्णांकk(dvbdev, BT656, "line start @ pos %u\n",
			      bt656->pos);

		bt656->linesamples = 0;
		bt656->भ_शेषe = LINE_SAMPLES;
	पूर्ण अन्यथा अणु
		cxusb_vprपूर्णांकk(dvbdev, BT656, "VBI start @ pos %u\n",
			      bt656->pos);

		bt656->भ_शेषe = VBI_SAMPLES;
	पूर्ण
पूर्ण

अटल व्योम cxusb_medion_cf_refc_line_smpl(काष्ठा dvb_usb_device *dvbdev,
					   काष्ठा cxusb_bt656_params *bt656,
					   bool firstfield,
					   अचिन्हित पूर्णांक maxlinesamples,
					   अचिन्हित अक्षर buf[4])
अणु
	bool sav_code = (buf[3] & CXUSB_BT656_SEAV_MASK) ==
		CXUSB_BT656_SEAV_SAV;
	अचिन्हित पूर्णांक remsamples;

	अगर (sav_code)
		cxusb_vprपूर्णांकk(dvbdev, BT656,
			      "SAV in line samples @ line %u, pos %u\n",
			      bt656->line, bt656->pos);

	remsamples = maxlinesamples - bt656->linesamples;
	अगर (bt656->buf && remsamples > 0) अणु
		स_रखो(bt656->buf, 0, remsamples);
		bt656->buf += remsamples;

		cxusb_vprपूर्णांकk(dvbdev, BT656,
			      "field %c line %u %u samples still remaining (of %u)\n",
			      firstfield ? '1' : '2', bt656->line, remsamples,
			      maxlinesamples);
	पूर्ण

	bt656->भ_शेषe = START_SEARCH;
	bt656->line++;
पूर्ण

अटल व्योम cxusb_medion_cf_refc_vbi_smpl(काष्ठा dvb_usb_device *dvbdev,
					  काष्ठा cxusb_bt656_params *bt656,
					  अचिन्हित अक्षर buf[4])
अणु
	bool sav_code = (buf[3] & CXUSB_BT656_SEAV_MASK) ==
		CXUSB_BT656_SEAV_SAV;

	अगर (sav_code)
		cxusb_vprपूर्णांकk(dvbdev, BT656, "SAV in VBI samples @ pos %u\n",
			      bt656->pos);

	bt656->भ_शेषe = START_SEARCH;
पूर्ण

/* वापसs whether the whole 4-byte code should be skipped in the buffer */
अटल bool cxusb_medion_cf_ref_code(काष्ठा dvb_usb_device *dvbdev,
				     काष्ठा cxusb_bt656_params *bt656,
				     bool firstfield,
				     अचिन्हित पूर्णांक maxlines,
				     अचिन्हित पूर्णांक maxlinesamples,
				     अचिन्हित अक्षर buf[4])
अणु
	अगर (bt656->भ_शेषe == START_SEARCH) अणु
		cxusb_medion_cf_refc_start_sch(dvbdev, bt656, firstfield, buf);
	पूर्ण अन्यथा अगर (bt656->भ_शेषe == LINE_SAMPLES) अणु
		cxusb_medion_cf_refc_line_smpl(dvbdev, bt656, firstfield,
					       maxlinesamples, buf);
		वापस false;
	पूर्ण अन्यथा अगर (bt656->भ_शेषe == VBI_SAMPLES) अणु
		cxusb_medion_cf_refc_vbi_smpl(dvbdev, bt656, buf);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool cxusb_medion_cs_start_sch(काष्ठा dvb_usb_device *dvbdev,
				      काष्ठा cxusb_medion_auxbuf *auxbuf,
				      काष्ठा cxusb_bt656_params *bt656,
				      अचिन्हित पूर्णांक maxlinesamples)
अणु
	अचिन्हित अक्षर buf[64];
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक tocheck = clamp_t(माप_प्रकार, maxlinesamples / 4, 3,
				       माप(buf));

	अगर (!cxusb_auxbuf_copy(auxbuf, bt656->pos + 1, buf, tocheck))
		वापस false;

	क्रम (idx = 0; idx <= tocheck - 3; idx++)
		अगर (स_भेद(buf + idx, CXUSB_BT656_PREAMBLE, 3) == 0) अणु
			bt656->pos += (1 + idx);
			वापस true;
		पूर्ण

	cxusb_vprपूर्णांकk(dvbdev, BT656, "line %u early start, pos %u\n",
		      bt656->line, bt656->pos);

	bt656->linesamples = 0;
	bt656->भ_शेषe = LINE_SAMPLES;

	वापस true;
पूर्ण

अटल व्योम cxusb_medion_cs_line_smpl(काष्ठा cxusb_bt656_params *bt656,
				      अचिन्हित पूर्णांक maxlinesamples,
				      अचिन्हित अक्षर val)
अणु
	अगर (bt656->buf)
		*(bt656->buf++) = val;

	bt656->linesamples++;
	bt656->pos++;

	अगर (bt656->linesamples >= maxlinesamples) अणु
		bt656->भ_शेषe = START_SEARCH;
		bt656->line++;
	पूर्ण
पूर्ण

अटल bool cxusb_medion_copy_samples(काष्ठा dvb_usb_device *dvbdev,
				      काष्ठा cxusb_medion_auxbuf *auxbuf,
				      काष्ठा cxusb_bt656_params *bt656,
				      अचिन्हित पूर्णांक maxlinesamples,
				      अचिन्हित अक्षर val)
अणु
	अगर (bt656->भ_शेषe == START_SEARCH && bt656->line > 0)
		वापस cxusb_medion_cs_start_sch(dvbdev, auxbuf, bt656,
						 maxlinesamples);
	अन्यथा अगर (bt656->भ_शेषe == LINE_SAMPLES)
		cxusb_medion_cs_line_smpl(bt656, maxlinesamples, val);
	अन्यथा /* TODO: copy VBI samples */
		bt656->pos++;

	वापस true;
पूर्ण

अटल bool cxusb_medion_copy_field(काष्ठा dvb_usb_device *dvbdev,
				    काष्ठा cxusb_medion_auxbuf *auxbuf,
				    काष्ठा cxusb_bt656_params *bt656,
				    bool firstfield,
				    अचिन्हित पूर्णांक maxlines,
				    अचिन्हित पूर्णांक maxlinesmpls)
अणु
	जबतक (bt656->line < maxlines) अणु
		अचिन्हित अक्षर val;

		अगर (!cxusb_auxbuf_copy(auxbuf, bt656->pos, &val, 1))
			अवरोध;

		अगर (val == CXUSB_BT656_PREAMBLE[0]) अणु
			अचिन्हित अक्षर buf[4];

			buf[0] = val;
			अगर (!cxusb_auxbuf_copy(auxbuf, bt656->pos + 1,
					       buf + 1, 3))
				अवरोध;

			अगर (buf[1] == CXUSB_BT656_PREAMBLE[1] &&
			    buf[2] == CXUSB_BT656_PREAMBLE[2]) अणु
				/*
				 * is this a field change?
				 * अगर so, terminate copying the current field
				 */
				अगर (cxusb_medion_cf_refc_fld_chg(dvbdev,
								 bt656,
								 firstfield,
								 maxlines,
								 maxlinesmpls,
								 buf))
					वापस true;

				अगर (cxusb_medion_cf_ref_code(dvbdev, bt656,
							     firstfield,
							     maxlines,
							     maxlinesmpls,
							     buf))
					bt656->pos += 4;

				जारी;
			पूर्ण
		पूर्ण

		अगर (!cxusb_medion_copy_samples(dvbdev, auxbuf, bt656,
					       maxlinesmpls, val))
			अवरोध;
	पूर्ण

	अगर (bt656->line < maxlines) अणु
		cxusb_vprपूर्णांकk(dvbdev, BT656,
			      "end of buffer pos = %u, line = %u\n",
			      bt656->pos, bt656->line);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool cxusb_medion_v_process_auxbuf(काष्ठा cxusb_medion_dev *cxdev,
					  bool reset)
अणु
	काष्ठा dvb_usb_device *dvbdev = cxdev->dvbdev;
	काष्ठा cxusb_bt656_params *bt656 = &cxdev->bt656;

	/*
	 * अगर this is a new frame
	 * fetch a buffer from list
	 */
	अगर (bt656->mode == NEW_FRAME) अणु
		अगर (!list_empty(&cxdev->buflist)) अणु
			cxdev->vbuf =
				list_first_entry(&cxdev->buflist,
						 काष्ठा cxusb_medion_vbuffer,
						 list);
			list_del(&cxdev->vbuf->list);
		पूर्ण अन्यथा अणु
			dev_warn(&dvbdev->udev->dev, "no free buffers\n");
		पूर्ण
	पूर्ण

	अगर (bt656->mode == NEW_FRAME || reset) अणु
		cxusb_vprपूर्णांकk(dvbdev, URB, "will copy field 1\n");
		bt656->pos = 0;
		bt656->mode = FIRST_FIELD;
		bt656->भ_शेषe = START_SEARCH;
		bt656->line = 0;

		अगर (cxdev->vbuf) अणु
			cxdev->vbuf->vb2.vb2_buf.बारtamp = kसमय_get_ns();
			bt656->buf = vb2_plane_vaddr(&cxdev->vbuf->vb2.vb2_buf,
						     0);
		पूर्ण
	पूर्ण

	अगर (bt656->mode == FIRST_FIELD) अणु
		अगर (!cxusb_medion_copy_field(dvbdev, &cxdev->auxbuf, bt656,
					     true, cxdev->height / 2,
					     cxdev->width * 2))
			वापस false;

		/*
		 * करो not trim buffer there in हाल
		 * we need to reset the search later
		 */

		cxusb_vprपूर्णांकk(dvbdev, URB, "will copy field 2\n");
		bt656->mode = SECOND_FIELD;
		bt656->भ_शेषe = START_SEARCH;
		bt656->line = 0;
	पूर्ण

	अगर (bt656->mode == SECOND_FIELD) अणु
		अगर (!cxusb_medion_copy_field(dvbdev, &cxdev->auxbuf, bt656,
					     false, cxdev->height / 2,
					     cxdev->width * 2))
			वापस false;

		cxusb_auxbuf_head_trim(dvbdev, &cxdev->auxbuf, bt656->pos);

		bt656->mode = NEW_FRAME;

		अगर (cxdev->vbuf) अणु
			vb2_set_plane_payload(&cxdev->vbuf->vb2.vb2_buf, 0,
					      cxdev->width * cxdev->height * 2);

			cxdev->vbuf->vb2.field = cxdev->field_order;
			cxdev->vbuf->vb2.sequence = cxdev->vbuf_sequence++;

			vb2_buffer_करोne(&cxdev->vbuf->vb2.vb2_buf,
					VB2_BUF_STATE_DONE);

			cxdev->vbuf = शून्य;
			cxdev->bt656.buf = शून्य;

			cxusb_vprपूर्णांकk(dvbdev, URB, "frame done\n");
		पूर्ण अन्यथा अणु
			cxusb_vprपूर्णांकk(dvbdev, URB, "frame skipped\n");
			cxdev->vbuf_sequence++;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool cxusb_medion_v_complete_handle_urb(काष्ठा cxusb_medion_dev *cxdev,
					       bool *auxbuf_reset)
अणु
	काष्ठा dvb_usb_device *dvbdev = cxdev->dvbdev;
	अचिन्हित पूर्णांक urbn;
	काष्ठा urb *urb;
	पूर्णांक ret;

	*auxbuf_reset = false;

	urbn = cxdev->nexturb;
	अगर (!test_bit(urbn, &cxdev->urbcomplete))
		वापस false;

	clear_bit(urbn, &cxdev->urbcomplete);

	करो अणु
		cxdev->nexturb++;
		cxdev->nexturb %= CXUSB_VIDEO_URBS;
		urb = cxdev->streamurbs[cxdev->nexturb];
	पूर्ण जबतक (!urb);

	urb = cxdev->streamurbs[urbn];
	cxusb_vprपूर्णांकk(dvbdev, URB, "URB %u status = %d\n", urbn, urb->status);

	अगर (urb->status == 0 || urb->status == -EXDEV) अणु
		पूर्णांक i;
		अचिन्हित दीर्घ len;

		क्रम (i = 0, len = 0; i < urb->number_of_packets; i++)
			len += urb->iso_frame_desc[i].actual_length;

		cxusb_vprपूर्णांकk(dvbdev, URB, "URB %u data len = %lu\n", urbn,
			      len);

		अगर (len > 0) अणु
			cxusb_vprपूर्णांकk(dvbdev, URB, "appending URB\n");

			/*
			 * append new data to auxbuf जबतक
			 * overwriting old data अगर necessary
			 *
			 * अगर any overग_लिखो happens then we can no
			 * दीर्घer rely on consistency of the whole
			 * data so let's start again the current
			 * auxbuf frame assembling process from
			 * the beginning
			 */
			*auxbuf_reset =
				!cxusb_auxbuf_append_urb(dvbdev,
							 &cxdev->auxbuf,
							 urb);
		पूर्ण
	पूर्ण

	cxusb_vprपूर्णांकk(dvbdev, URB, "URB %u resubmit\n", urbn);

	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret != 0)
		dev_err(&dvbdev->udev->dev,
			"unable to resubmit URB %u (%d), you'll have to restart streaming\n",
			urbn, ret);

	/* next URB is complete alपढ़ोy? reschedule us then to handle it */
	वापस test_bit(cxdev->nexturb, &cxdev->urbcomplete);
पूर्ण

अटल व्योम cxusb_medion_v_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cxusb_medion_dev *cxdev = container_of(work,
						      काष्ठा cxusb_medion_dev,
						      urbwork);
	काष्ठा dvb_usb_device *dvbdev = cxdev->dvbdev;
	bool auxbuf_reset;
	bool reschedule;

	mutex_lock(cxdev->videodev->lock);

	cxusb_vprपूर्णांकk(dvbdev, URB, "worker called, stop_streaming = %d\n",
		      (पूर्णांक)cxdev->stop_streaming);

	अगर (cxdev->stop_streaming)
		जाओ unlock;

	reschedule = cxusb_medion_v_complete_handle_urb(cxdev, &auxbuf_reset);

	अगर (cxusb_medion_v_process_auxbuf(cxdev, auxbuf_reset))
		/* reschedule us until auxbuf no दीर्घer can produce any frame */
		reschedule = true;

	अगर (reschedule) अणु
		cxusb_vprपूर्णांकk(dvbdev, URB, "rescheduling worker\n");
		schedule_work(&cxdev->urbwork);
	पूर्ण

unlock:
	mutex_unlock(cxdev->videodev->lock);
पूर्ण

अटल व्योम cxusb_medion_v_complete(काष्ठा urb *u)
अणु
	काष्ठा dvb_usb_device *dvbdev = u->context;
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < CXUSB_VIDEO_URBS; i++)
		अगर (cxdev->streamurbs[i] == u)
			अवरोध;

	अगर (i >= CXUSB_VIDEO_URBS) अणु
		dev_err(&dvbdev->udev->dev,
			"complete on unknown URB\n");
		वापस;
	पूर्ण

	cxusb_vprपूर्णांकk(dvbdev, URB, "URB %u complete\n", i);

	set_bit(i, &cxdev->urbcomplete);
	schedule_work(&cxdev->urbwork);
पूर्ण

अटल व्योम cxusb_medion_urbs_मुक्त(काष्ठा cxusb_medion_dev *cxdev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < CXUSB_VIDEO_URBS; i++)
		अगर (cxdev->streamurbs[i]) अणु
			kमुक्त(cxdev->streamurbs[i]->transfer_buffer);
			usb_मुक्त_urb(cxdev->streamurbs[i]);
			cxdev->streamurbs[i] = शून्य;
		पूर्ण
पूर्ण

अटल व्योम cxusb_medion_वापस_buffers(काष्ठा cxusb_medion_dev *cxdev,
					bool requeue)
अणु
	काष्ठा cxusb_medion_vbuffer *vbuf, *vbuf_पंचांगp;

	list_क्रम_each_entry_safe(vbuf, vbuf_पंचांगp, &cxdev->buflist,
				 list) अणु
		list_del(&vbuf->list);
		vb2_buffer_करोne(&vbuf->vb2.vb2_buf,
				requeue ? VB2_BUF_STATE_QUEUED :
				VB2_BUF_STATE_ERROR);
	पूर्ण

	अगर (cxdev->vbuf) अणु
		vb2_buffer_करोne(&cxdev->vbuf->vb2.vb2_buf,
				requeue ? VB2_BUF_STATE_QUEUED :
				VB2_BUF_STATE_ERROR);

		cxdev->vbuf = शून्य;
		cxdev->bt656.buf = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक cxusb_medion_v_ss_auxbuf_alloc(काष्ठा cxusb_medion_dev *cxdev,
					  पूर्णांक *npackets)
अणु
	काष्ठा dvb_usb_device *dvbdev = cxdev->dvbdev;
	u8 *buf;
	अचिन्हित पूर्णांक framelen, urblen, auxbuflen;

	framelen = (cxdev->width * 2 + 4 + 4) *
		(cxdev->height + 50 /* VBI lines */);

	/*
	 * try to fit a whole frame पूर्णांकo each URB, as दीर्घ as करोing so
	 * करोes not require very high order memory allocations
	 */
	BUILD_BUG_ON(CXUSB_VIDEO_URB_MAX_SIZE / CXUSB_VIDEO_PKT_SIZE >
		     CXUSB_VIDEO_MAX_FRAME_PKTS);
	*npackets = min_t(पूर्णांक, (framelen + CXUSB_VIDEO_PKT_SIZE - 1) /
			  CXUSB_VIDEO_PKT_SIZE,
			  CXUSB_VIDEO_URB_MAX_SIZE / CXUSB_VIDEO_PKT_SIZE);
	urblen = *npackets * CXUSB_VIDEO_PKT_SIZE;

	cxusb_vprपूर्णांकk(dvbdev, URB,
		      "each URB will have %d packets for total of %u bytes (%u x %u @ %u)\n",
		      *npackets, urblen, (अचिन्हित पूर्णांक)cxdev->width,
		      (अचिन्हित पूर्णांक)cxdev->height, framelen);

	auxbuflen = framelen + urblen;

	buf = vदो_स्मृति(auxbuflen);
	अगर (!buf)
		वापस -ENOMEM;

	cxusb_auxbuf_init(dvbdev, &cxdev->auxbuf, buf, auxbuflen);

	वापस 0;
पूर्ण

अटल u32 cxusb_medion_norm2field_order(v4l2_std_id norm)
अणु
	bool is625 = norm & V4L2_STD_625_50;
	bool is525 = norm & V4L2_STD_525_60;

	अगर (!is625 && !is525)
		वापस V4L2_FIELD_NONE;

	अगर (is625 && is525)
		वापस V4L2_FIELD_NONE;

	अगर (is625)
		वापस V4L2_FIELD_SEQ_TB;
	अन्यथा /* is525 */
		वापस V4L2_FIELD_SEQ_BT;
पूर्ण

अटल u32 cxusb_medion_field_order(काष्ठा cxusb_medion_dev *cxdev)
अणु
	काष्ठा dvb_usb_device *dvbdev = cxdev->dvbdev;
	u32 field;
	पूर्णांक ret;
	v4l2_std_id norm;

	/* TV tuner is PAL-only so it is always TB */
	अगर (cxdev->input == 0)
		वापस V4L2_FIELD_SEQ_TB;

	field = cxusb_medion_norm2field_order(cxdev->norm);
	अगर (field != V4L2_FIELD_NONE)
		वापस field;

	ret = v4l2_subdev_call(cxdev->cx25840, video, g_std, &norm);
	अगर (ret != 0) अणु
		cxusb_vprपूर्णांकk(dvbdev, OPS,
			      "cannot get current standard for input %u\n",
			      (अचिन्हित पूर्णांक)cxdev->input);
	पूर्ण अन्यथा अणु
		field = cxusb_medion_norm2field_order(norm);
		अगर (field != V4L2_FIELD_NONE)
			वापस field;
	पूर्ण

	dev_warn(&dvbdev->udev->dev,
		 "cannot determine field order for the current standard setup and received signal, using TB\n");
	वापस V4L2_FIELD_SEQ_TB;
पूर्ण

अटल पूर्णांक cxusb_medion_v_start_streaming(काष्ठा vb2_queue *q,
					  अचिन्हित पूर्णांक count)
अणु
	काष्ठा dvb_usb_device *dvbdev = vb2_get_drv_priv(q);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	u8 streamon_params[2] = अणु 0x03, 0x00 पूर्ण;
	पूर्णांक npackets, i;
	पूर्णांक ret;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "should start streaming\n");

	अगर (cxdev->stop_streaming) अणु
		/* stream is being stopped */
		ret = -EBUSY;
		जाओ ret_retbufs;
	पूर्ण

	cxdev->field_order = cxusb_medion_field_order(cxdev);

	ret = v4l2_subdev_call(cxdev->cx25840, video, s_stream, 1);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev,
			"unable to start stream (%d)\n", ret);
		जाओ ret_retbufs;
	पूर्ण

	ret = cxusb_ctrl_msg(dvbdev, CMD_STREAMING_ON, streamon_params, 2,
			     शून्य, 0);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev,
			"unable to start streaming (%d)\n", ret);
		जाओ ret_unstream_cx;
	पूर्ण

	ret = cxusb_medion_v_ss_auxbuf_alloc(cxdev, &npackets);
	अगर (ret != 0)
		जाओ ret_unstream_md;

	क्रम (i = 0; i < CXUSB_VIDEO_URBS; i++) अणु
		पूर्णांक framen;
		u8 *streambuf;
		काष्ठा urb *surb;

		/*
		 * TODO: change this to an array of single pages to aव्योम
		 * करोing a large continuous allocation when (अगर)
		 * s-g isochronous USB transfers are supported
		 */
		streambuf = kदो_स्मृति(npackets * CXUSB_VIDEO_PKT_SIZE,
				    GFP_KERNEL);
		अगर (!streambuf) अणु
			अगर (i < 2) अणु
				ret = -ENOMEM;
				जाओ ret_मुक्तab;
			पूर्ण
			अवरोध;
		पूर्ण

		surb = usb_alloc_urb(npackets, GFP_KERNEL);
		अगर (!surb) अणु
			kमुक्त(streambuf);
			ret = -ENOMEM;
			जाओ ret_मुक्तu;
		पूर्ण

		cxdev->streamurbs[i] = surb;
		surb->dev = dvbdev->udev;
		surb->context = dvbdev;
		surb->pipe = usb_rcvisocpipe(dvbdev->udev, 2);

		surb->पूर्णांकerval = 1;
		surb->transfer_flags = URB_ISO_ASAP;

		surb->transfer_buffer = streambuf;

		surb->complete = cxusb_medion_v_complete;
		surb->number_of_packets = npackets;
		surb->transfer_buffer_length = npackets * CXUSB_VIDEO_PKT_SIZE;

		क्रम (framen = 0; framen < npackets; framen++) अणु
			surb->iso_frame_desc[framen].offset =
				CXUSB_VIDEO_PKT_SIZE * framen;

			surb->iso_frame_desc[framen].length =
				CXUSB_VIDEO_PKT_SIZE;
		पूर्ण
	पूर्ण

	cxdev->urbcomplete = 0;
	cxdev->nexturb = 0;
	cxdev->vbuf_sequence = 0;

	cxdev->vbuf = शून्य;
	cxdev->bt656.mode = NEW_FRAME;
	cxdev->bt656.buf = शून्य;

	क्रम (i = 0; i < CXUSB_VIDEO_URBS; i++)
		अगर (cxdev->streamurbs[i]) अणु
			ret = usb_submit_urb(cxdev->streamurbs[i],
					     GFP_KERNEL);
			अगर (ret != 0)
				dev_err(&dvbdev->udev->dev,
					"URB %d submission failed (%d)\n", i,
					ret);
		पूर्ण

	वापस 0;

ret_मुक्तu:
	cxusb_medion_urbs_मुक्त(cxdev);

ret_मुक्तab:
	vमुक्त(cxdev->auxbuf.buf);

ret_unstream_md:
	cxusb_ctrl_msg(dvbdev, CMD_STREAMING_OFF, शून्य, 0, शून्य, 0);

ret_unstream_cx:
	v4l2_subdev_call(cxdev->cx25840, video, s_stream, 0);

ret_retbufs:
	cxusb_medion_वापस_buffers(cxdev, true);

	वापस ret;
पूर्ण

अटल व्योम cxusb_medion_v_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा dvb_usb_device *dvbdev = vb2_get_drv_priv(q);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "should stop streaming\n");

	अगर (WARN_ON(cxdev->stop_streaming))
		वापस;

	cxdev->stop_streaming = true;

	cxusb_ctrl_msg(dvbdev, CMD_STREAMING_OFF, शून्य, 0, शून्य, 0);

	ret = v4l2_subdev_call(cxdev->cx25840, video, s_stream, 0);
	अगर (ret != 0)
		dev_err(&dvbdev->udev->dev, "unable to stop stream (%d)\n",
			ret);

	/* let URB completion run */
	mutex_unlock(cxdev->videodev->lock);

	क्रम (i = 0; i < CXUSB_VIDEO_URBS; i++)
		अगर (cxdev->streamurbs[i])
			usb_समाप्त_urb(cxdev->streamurbs[i]);

	flush_work(&cxdev->urbwork);

	mutex_lock(cxdev->videodev->lock);

	/* मुक्त transfer buffer and URB */
	vमुक्त(cxdev->auxbuf.buf);

	cxusb_medion_urbs_मुक्त(cxdev);

	cxusb_medion_वापस_buffers(cxdev, false);

	cxdev->stop_streaming = false;
पूर्ण

अटल व्योम cxusub_medion_v_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *v4l2buf = to_vb2_v4l2_buffer(vb);
	काष्ठा cxusb_medion_vbuffer *vbuf =
		container_of(v4l2buf, काष्ठा cxusb_medion_vbuffer, vb2);
	काष्ठा dvb_usb_device *dvbdev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	/* cxusb_vprपूर्णांकk(dvbdev, OPS, "mmmm.. a fresh buffer...\n"); */

	list_add_tail(&vbuf->list, &cxdev->buflist);
पूर्ण

अटल स्थिर काष्ठा vb2_ops cxdev_video_qops = अणु
	.queue_setup = cxusb_medion_v_queue_setup,
	.buf_init = cxusb_medion_v_buf_init,
	.start_streaming = cxusb_medion_v_start_streaming,
	.stop_streaming = cxusb_medion_v_stop_streaming,
	.buf_queue = cxusub_medion_v_buf_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish
पूर्ण;

अटल स्थिर __u32 videocaps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER |
	V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
अटल स्थिर __u32 radiocaps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;

अटल पूर्णांक cxusb_medion_v_querycap(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);

	strscpy(cap->driver, dvbdev->udev->dev.driver->name,
		माप(cap->driver));
	strscpy(cap->card, "Medion 95700", माप(cap->card));
	usb_make_path(dvbdev->udev, cap->bus_info, माप(cap->bus_info));

	cap->capabilities = videocaps | radiocaps | V4L2_CAP_DEVICE_CAPS;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_v_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_UYVY;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	f->fmt.pix.width = cxdev->width;
	f->fmt.pix.height = cxdev->height;
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	f->fmt.pix.field = vb2_start_streaming_called(&cxdev->videoqueue) ?
		cxdev->field_order : cxusb_medion_field_order(cxdev);
	f->fmt.pix.bytesperline = cxdev->width * 2;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * f->fmt.pix.height;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_try_s_fmt_vid_cap(काष्ठा file *file,
					  काष्ठा v4l2_क्रमmat *f,
					  bool isset)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	काष्ठा v4l2_subdev_क्रमmat subfmt;
	u32 field;
	पूर्णांक ret;

	अगर (isset && vb2_is_busy(&cxdev->videoqueue))
		वापस -EBUSY;

	field = vb2_start_streaming_called(&cxdev->videoqueue) ?
		cxdev->field_order : cxusb_medion_field_order(cxdev);

	स_रखो(&subfmt, 0, माप(subfmt));
	subfmt.which = isset ? V4L2_SUBDEV_FORMAT_ACTIVE :
		V4L2_SUBDEV_FORMAT_TRY;
	subfmt.क्रमmat.width = f->fmt.pix.width & ~1;
	subfmt.क्रमmat.height = f->fmt.pix.height & ~1;
	subfmt.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
	subfmt.क्रमmat.field = field;
	subfmt.क्रमmat.colorspace = V4L2_COLORSPACE_SMPTE170M;

	ret = v4l2_subdev_call(cxdev->cx25840, pad, set_fmt, शून्य, &subfmt);
	अगर (ret != 0)
		वापस ret;

	f->fmt.pix.width = subfmt.क्रमmat.width;
	f->fmt.pix.height = subfmt.क्रमmat.height;
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	f->fmt.pix.field = field;
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * f->fmt.pix.height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	अगर (isset) अणु
		cxdev->width = f->fmt.pix.width;
		cxdev->height = f->fmt.pix.height;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	वापस cxusb_medion_try_s_fmt_vid_cap(file, f, false);
पूर्ण

अटल पूर्णांक cxusb_medion_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	वापस cxusb_medion_try_s_fmt_vid_cap(file, f, true);
पूर्ण

अटल स्थिर काष्ठा अणु
	काष्ठा v4l2_input input;
	u32 inअ_दोfg;
पूर्ण cxusb_medion_inमाला_दो[] = अणु
	अणु .input = अणु .name = "TV tuner", .type = V4L2_INPUT_TYPE_TUNER,
		     .tuner = 0, .std = V4L2_STD_PAL पूर्ण,
	  .inअ_दोfg = CX25840_COMPOSITE2, पूर्ण,

	अणु  .input = अणु .name = "Composite", .type = V4L2_INPUT_TYPE_CAMERA,
		     .std = V4L2_STD_ALL पूर्ण,
	   .inअ_दोfg = CX25840_COMPOSITE1, पूर्ण,

	अणु  .input = अणु .name = "S-Video", .type = V4L2_INPUT_TYPE_CAMERA,
		      .std = V4L2_STD_ALL पूर्ण,
	   .inअ_दोfg = CX25840_SVIDEO_LUMA3 | CX25840_SVIDEO_CHROMA4 पूर्ण
पूर्ण;

#घोषणा CXUSB_INPUT_CNT ARRAY_SIZE(cxusb_medion_inमाला_दो)

अटल पूर्णांक cxusb_medion_क्रमागत_input(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_input *inp)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	u32 index = inp->index;

	अगर (index >= CXUSB_INPUT_CNT)
		वापस -EINVAL;

	*inp = cxusb_medion_inमाला_दो[index].input;
	inp->index = index;
	inp->capabilities |= V4L2_IN_CAP_STD;

	अगर (index == cxdev->input) अणु
		पूर्णांक ret;
		u32 status = 0;

		ret = v4l2_subdev_call(cxdev->cx25840, video, g_input_status,
				       &status);
		अगर (ret != 0)
			dev_warn(&dvbdev->udev->dev,
				 "cx25840 input status query failed (%d)\n",
				 ret);
		अन्यथा
			inp->status = status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_g_input(काष्ठा file *file, व्योम *fh,
				अचिन्हित पूर्णांक *i)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	*i = cxdev->input;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_set_norm(काष्ठा cxusb_medion_dev *cxdev,
				 v4l2_std_id norm)
अणु
	काष्ठा dvb_usb_device *dvbdev = cxdev->dvbdev;
	पूर्णांक ret;

	cxusb_vprपूर्णांकk(dvbdev, OPS,
		      "trying to set standard for input %u to %lx\n",
		      (अचिन्हित पूर्णांक)cxdev->input,
		      (अचिन्हित दीर्घ)norm);

	/* no स्वतःdetection support */
	अगर (norm == V4L2_STD_UNKNOWN)
		वापस -EINVAL;

	/* on composite or S-Video any std is acceptable */
	अगर (cxdev->input != 0) अणु
		ret = v4l2_subdev_call(cxdev->cx25840, video, s_std, norm);
		अगर (ret)
			वापस ret;

		जाओ ret_savenorm;
	पूर्ण

	/* TV tuner is only able to demodulate PAL */
	अगर ((norm & ~V4L2_STD_PAL) != 0)
		वापस -EINVAL;

	ret = v4l2_subdev_call(cxdev->tda9887, video, s_std, norm);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev,
			"tda9887 norm setup failed (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = v4l2_subdev_call(cxdev->tuner, video, s_std, norm);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev,
			"tuner norm setup failed (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = v4l2_subdev_call(cxdev->cx25840, video, s_std, norm);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev,
			"cx25840 norm setup failed (%d)\n",
			ret);
		वापस ret;
	पूर्ण

ret_savenorm:
	cxdev->norm = norm;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_s_input(काष्ठा file *file, व्योम *fh,
				अचिन्हित पूर्णांक i)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	पूर्णांक ret;
	v4l2_std_id norm;

	अगर (i >= CXUSB_INPUT_CNT)
		वापस -EINVAL;

	ret = v4l2_subdev_call(cxdev->cx25840, video, s_routing,
			       cxusb_medion_inमाला_दो[i].inअ_दोfg, 0, 0);
	अगर (ret != 0)
		वापस ret;

	cxdev->input = i;
	cxdev->videodev->tvnorms = cxusb_medion_inमाला_दो[i].input.std;

	norm = cxdev->norm & cxusb_medion_inमाला_दो[i].input.std;
	अगर (norm == 0)
		norm = cxusb_medion_inमाला_दो[i].input.std;

	cxusb_medion_set_norm(cxdev, norm);

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_g_tuner(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक ret;

	अगर (tuner->index != 0)
		वापस -EINVAL;

	अगर (vdev->vfl_type == VFL_TYPE_VIDEO)
		tuner->type = V4L2_TUNER_ANALOG_TV;
	अन्यथा
		tuner->type = V4L2_TUNER_RADIO;

	tuner->capability = 0;
	tuner->afc = 0;

	/*
	 * fills:
	 * always: capability (अटल), rangelow (अटल), rangehigh (अटल)
	 * radio mode: afc (may fail silently), rxsubchans (अटल), audmode
	 */
	ret = v4l2_subdev_call(cxdev->tda9887, tuner, g_tuner, tuner);
	अगर (ret != 0)
		वापस ret;

	/*
	 * fills:
	 * always: capability (अटल), rangelow (अटल), rangehigh (अटल)
	 * radio mode: rxsubchans (always stereo), audmode,
	 * संकेत (might be wrong)
	 */
	ret = v4l2_subdev_call(cxdev->tuner, tuner, g_tuner, tuner);
	अगर (ret != 0)
		वापस ret;

	tuner->संकेत = 0;

	/*
	 * fills: TV mode: capability, rxsubchans, audmode, संकेत
	 */
	ret = v4l2_subdev_call(cxdev->cx25840, tuner, g_tuner, tuner);
	अगर (ret != 0)
		वापस ret;

	अगर (vdev->vfl_type == VFL_TYPE_VIDEO)
		strscpy(tuner->name, "TV tuner", माप(tuner->name));
	अन्यथा
		strscpy(tuner->name, "Radio tuner", माप(tuner->name));

	स_रखो(tuner->reserved, 0, माप(tuner->reserved));

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_s_tuner(काष्ठा file *file, व्योम *fh,
				स्थिर काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक ret;

	अगर (tuner->index != 0)
		वापस -EINVAL;

	ret = v4l2_subdev_call(cxdev->tda9887, tuner, s_tuner, tuner);
	अगर (ret != 0)
		वापस ret;

	ret = v4l2_subdev_call(cxdev->tuner, tuner, s_tuner, tuner);
	अगर (ret != 0)
		वापस ret;

	/*
	 * make sure that cx25840 is in a correct TV / radio mode,
	 * since calls above may have changed it क्रम tuner / IF demod
	 */
	अगर (vdev->vfl_type == VFL_TYPE_VIDEO)
		v4l2_subdev_call(cxdev->cx25840, video, s_std, cxdev->norm);
	अन्यथा
		v4l2_subdev_call(cxdev->cx25840, tuner, s_radio);

	वापस v4l2_subdev_call(cxdev->cx25840, tuner, s_tuner, tuner);
पूर्ण

अटल पूर्णांक cxusb_medion_g_frequency(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	अगर (freq->tuner != 0)
		वापस -EINVAL;

	वापस v4l2_subdev_call(cxdev->tuner, tuner, g_frequency, freq);
पूर्ण

अटल पूर्णांक cxusb_medion_s_frequency(काष्ठा file *file, व्योम *fh,
				    स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक ret;

	अगर (freq->tuner != 0)
		वापस -EINVAL;

	ret = v4l2_subdev_call(cxdev->tda9887, tuner, s_frequency, freq);
	अगर (ret != 0)
		वापस ret;

	ret = v4l2_subdev_call(cxdev->tuner, tuner, s_frequency, freq);
	अगर (ret != 0)
		वापस ret;

	/*
	 * make sure that cx25840 is in a correct TV / radio mode,
	 * since calls above may have changed it क्रम tuner / IF demod
	 */
	अगर (vdev->vfl_type == VFL_TYPE_VIDEO)
		v4l2_subdev_call(cxdev->cx25840, video, s_std, cxdev->norm);
	अन्यथा
		v4l2_subdev_call(cxdev->cx25840, tuner, s_radio);

	वापस v4l2_subdev_call(cxdev->cx25840, tuner, s_frequency, freq);
पूर्ण

अटल पूर्णांक cxusb_medion_g_std(काष्ठा file *file, व्योम *fh,
			      v4l2_std_id *norm)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	*norm = cxdev->norm;

	अगर (*norm == V4L2_STD_UNKNOWN)
		वापस -ENODATA;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_s_std(काष्ठा file *file, व्योम *fh,
			      v4l2_std_id norm)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	वापस cxusb_medion_set_norm(cxdev, norm);
पूर्ण

अटल पूर्णांक cxusb_medion_querystd(काष्ठा file *file, व्योम *fh,
				 v4l2_std_id *norm)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	v4l2_std_id norm_mask;
	पूर्णांक ret;

	/*
	 * make sure we करोn't have improper std bits set क्रम the TV tuner
	 * (could happen when no संकेत was present yet after reset)
	 */
	अगर (cxdev->input == 0)
		norm_mask = V4L2_STD_PAL;
	अन्यथा
		norm_mask = V4L2_STD_ALL;

	ret = v4l2_subdev_call(cxdev->cx25840, video, querystd, norm);
	अगर (ret != 0) अणु
		cxusb_vprपूर्णांकk(dvbdev, OPS,
			      "cannot get detected standard for input %u\n",
			      (अचिन्हित पूर्णांक)cxdev->input);
		वापस ret;
	पूर्ण

	cxusb_vprपूर्णांकk(dvbdev, OPS, "input %u detected standard is %lx\n",
		      (अचिन्हित पूर्णांक)cxdev->input, (अचिन्हित दीर्घ)*norm);
	*norm &= norm_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_log_status(काष्ठा file *file, व्योम *fh)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(file);
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	v4l2_device_call_all(&cxdev->v4l2dev, 0, core, log_status);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops cxusb_video_ioctl = अणु
	.vidioc_querycap = cxusb_medion_v_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = cxusb_medion_v_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = cxusb_medion_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = cxusb_medion_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = cxusb_medion_try_fmt_vid_cap,
	.vidioc_क्रमागत_input = cxusb_medion_क्रमागत_input,
	.vidioc_g_input = cxusb_medion_g_input,
	.vidioc_s_input = cxusb_medion_s_input,
	.vidioc_g_tuner = cxusb_medion_g_tuner,
	.vidioc_s_tuner = cxusb_medion_s_tuner,
	.vidioc_g_frequency = cxusb_medion_g_frequency,
	.vidioc_s_frequency = cxusb_medion_s_frequency,
	.vidioc_g_std = cxusb_medion_g_std,
	.vidioc_s_std = cxusb_medion_s_std,
	.vidioc_querystd = cxusb_medion_querystd,
	.vidioc_log_status = cxusb_medion_log_status,
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops cxusb_radio_ioctl = अणु
	.vidioc_querycap = cxusb_medion_v_querycap,
	.vidioc_g_tuner = cxusb_medion_g_tuner,
	.vidioc_s_tuner = cxusb_medion_s_tuner,
	.vidioc_g_frequency = cxusb_medion_g_frequency,
	.vidioc_s_frequency = cxusb_medion_s_frequency,
	.vidioc_log_status = cxusb_medion_log_status
पूर्ण;

/*
 * in principle, this should be स्थिर, but s_io_pin_config is declared
 * to take non-स्थिर, and gcc complains
 */
अटल काष्ठा v4l2_subdev_io_pin_config cxusub_medion_pin_config[] = अणु
	अणु .pin = CX25840_PIN_DVALID_PRGM0, .function = CX25840_PAD_DEFAULT,
	  .strength = CX25840_PIN_DRIVE_MEDIUM पूर्ण,
	अणु .pin = CX25840_PIN_PLL_CLK_PRGM7, .function = CX25840_PAD_AUX_PLL पूर्ण,
	अणु .pin = CX25840_PIN_HRESET_PRGM2, .function = CX25840_PAD_ACTIVE,
	  .strength = CX25840_PIN_DRIVE_MEDIUM पूर्ण
पूर्ण;

पूर्णांक cxusb_medion_analog_init(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	u8 tuner_analog_msg_data[] = अणु 0x9c, 0x60, 0x85, 0x54 पूर्ण;
	काष्ठा i2c_msg tuner_analog_msg = अणु .addr = 0x61, .flags = 0,
					    .buf = tuner_analog_msg_data,
					    .len =
					    माप(tuner_analog_msg_data) पूर्ण;
	काष्ठा v4l2_subdev_क्रमmat subfmt;
	पूर्णांक ret;

	/* चयन tuner to analog mode so IF demod will become accessible */
	ret = i2c_transfer(&dvbdev->i2c_adap, &tuner_analog_msg, 1);
	अगर (ret != 1)
		dev_warn(&dvbdev->udev->dev,
			 "tuner analog switch failed (%d)\n", ret);

	/*
	 * cx25840 might have lost घातer during mode चयनing so we need
	 * to set it again
	 */
	ret = v4l2_subdev_call(cxdev->cx25840, core, reset, 0);
	अगर (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 reset failed (%d)\n", ret);

	ret = v4l2_subdev_call(cxdev->cx25840, video, s_routing,
			       CX25840_COMPOSITE1, 0, 0);
	अगर (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 initial input setting failed (%d)\n", ret);

	/* composite */
	cxdev->input = 1;
	cxdev->videodev->tvnorms = V4L2_STD_ALL;
	cxdev->norm = V4L2_STD_PAL;

	/* TODO: setup audio samples insertion */

	ret = v4l2_subdev_call(cxdev->cx25840, core, s_io_pin_config,
			       ARRAY_SIZE(cxusub_medion_pin_config),
			       cxusub_medion_pin_config);
	अगर (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 pin config failed (%d)\n", ret);

	/* make sure that we aren't in radio mode */
	v4l2_subdev_call(cxdev->tda9887, video, s_std, cxdev->norm);
	v4l2_subdev_call(cxdev->tuner, video, s_std, cxdev->norm);
	v4l2_subdev_call(cxdev->cx25840, video, s_std, cxdev->norm);

	स_रखो(&subfmt, 0, माप(subfmt));
	subfmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	subfmt.क्रमmat.width = cxdev->width;
	subfmt.क्रमmat.height = cxdev->height;
	subfmt.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
	subfmt.क्रमmat.field = V4L2_FIELD_SEQ_TB;
	subfmt.क्रमmat.colorspace = V4L2_COLORSPACE_SMPTE170M;

	ret = v4l2_subdev_call(cxdev->cx25840, pad, set_fmt, शून्य, &subfmt);
	अगर (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 format set failed (%d)\n", ret);

	अगर (ret == 0) अणु
		cxdev->width = subfmt.क्रमmat.width;
		cxdev->height = subfmt.क्रमmat.height;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_videoradio_खोलो(काष्ठा file *f)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(f);
	पूर्णांक ret;

	/*
	 * no locking needed since this call only modअगरies analog
	 * state अगर there are no other analog handles currenly
	 * खोलोed so ops करोne via them cannot create a conflict
	 */
	ret = cxusb_medion_get(dvbdev, CXUSB_OPEN_ANALOG);
	अगर (ret != 0)
		वापस ret;

	ret = v4l2_fh_खोलो(f);
	अगर (ret != 0)
		जाओ ret_release;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "got open\n");

	वापस 0;

ret_release:
	cxusb_medion_put(dvbdev);

	वापस ret;
पूर्ण

अटल पूर्णांक cxusb_videoradio_release(काष्ठा file *f)
अणु
	काष्ठा video_device *vdev = video_devdata(f);
	काष्ठा dvb_usb_device *dvbdev = video_drvdata(f);
	पूर्णांक ret;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "got release\n");

	अगर (vdev->vfl_type == VFL_TYPE_VIDEO)
		ret = vb2_fop_release(f);
	अन्यथा
		ret = v4l2_fh_release(f);

	cxusb_medion_put(dvbdev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations cxusb_video_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = vb2_fop_पढ़ो,
	.poll = vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap = vb2_fop_mmap,
	.खोलो = cxusb_videoradio_खोलो,
	.release = cxusb_videoradio_release
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations cxusb_radio_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = cxusb_videoradio_खोलो,
	.release = cxusb_videoradio_release
पूर्ण;

अटल व्योम cxusb_medion_v4l2_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा cxusb_medion_dev *cxdev =
		container_of(v4l2_dev, काष्ठा cxusb_medion_dev, v4l2dev);
	काष्ठा dvb_usb_device *dvbdev = cxdev->dvbdev;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "v4l2 device release\n");

	v4l2_device_unरेजिस्टर(&cxdev->v4l2dev);

	mutex_destroy(&cxdev->dev_lock);

	जबतक (completion_करोne(&cxdev->v4l2_release))
		schedule();

	complete(&cxdev->v4l2_release);
पूर्ण

अटल व्योम cxusb_medion_videodev_release(काष्ठा video_device *vdev)
अणु
	काष्ठा dvb_usb_device *dvbdev = video_get_drvdata(vdev);

	cxusb_vprपूर्णांकk(dvbdev, OPS, "video device release\n");

	video_device_release(vdev);
पूर्ण

अटल पूर्णांक cxusb_medion_रेजिस्टर_analog_video(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	पूर्णांक ret;

	cxdev->videoqueue.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	cxdev->videoqueue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ |
		VB2_DMABUF;
	cxdev->videoqueue.ops = &cxdev_video_qops;
	cxdev->videoqueue.mem_ops = &vb2_vदो_स्मृति_memops;
	cxdev->videoqueue.drv_priv = dvbdev;
	cxdev->videoqueue.buf_काष्ठा_size =
		माप(काष्ठा cxusb_medion_vbuffer);
	cxdev->videoqueue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	cxdev->videoqueue.min_buffers_needed = 6;
	cxdev->videoqueue.lock = &cxdev->dev_lock;

	ret = vb2_queue_init(&cxdev->videoqueue);
	अगर (ret) अणु
		dev_err(&dvbdev->udev->dev,
			"video queue init failed, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	cxdev->videodev = video_device_alloc();
	अगर (!cxdev->videodev) अणु
		dev_err(&dvbdev->udev->dev, "video device alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	cxdev->videodev->device_caps = videocaps;
	cxdev->videodev->fops = &cxusb_video_fops;
	cxdev->videodev->v4l2_dev = &cxdev->v4l2dev;
	cxdev->videodev->queue = &cxdev->videoqueue;
	strscpy(cxdev->videodev->name, "cxusb", माप(cxdev->videodev->name));
	cxdev->videodev->vfl_dir = VFL_सूची_RX;
	cxdev->videodev->ioctl_ops = &cxusb_video_ioctl;
	cxdev->videodev->tvnorms = V4L2_STD_ALL;
	cxdev->videodev->release = cxusb_medion_videodev_release;
	cxdev->videodev->lock = &cxdev->dev_lock;
	video_set_drvdata(cxdev->videodev, dvbdev);

	ret = video_रेजिस्टर_device(cxdev->videodev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(&dvbdev->udev->dev,
			"video device register failed, ret = %d\n", ret);
		जाओ ret_vrelease;
	पूर्ण

	वापस 0;

ret_vrelease:
	video_device_release(cxdev->videodev);
	वापस ret;
पूर्ण

अटल पूर्णांक cxusb_medion_रेजिस्टर_analog_radio(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	पूर्णांक ret;

	cxdev->radiodev = video_device_alloc();
	अगर (!cxdev->radiodev) अणु
		dev_err(&dvbdev->udev->dev, "radio device alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	cxdev->radiodev->device_caps = radiocaps;
	cxdev->radiodev->fops = &cxusb_radio_fops;
	cxdev->radiodev->v4l2_dev = &cxdev->v4l2dev;
	strscpy(cxdev->radiodev->name, "cxusb", माप(cxdev->radiodev->name));
	cxdev->radiodev->vfl_dir = VFL_सूची_RX;
	cxdev->radiodev->ioctl_ops = &cxusb_radio_ioctl;
	cxdev->radiodev->release = video_device_release;
	cxdev->radiodev->lock = &cxdev->dev_lock;
	video_set_drvdata(cxdev->radiodev, dvbdev);

	ret = video_रेजिस्टर_device(cxdev->radiodev, VFL_TYPE_RADIO, -1);
	अगर (ret) अणु
		dev_err(&dvbdev->udev->dev,
			"radio device register failed, ret = %d\n", ret);
		video_device_release(cxdev->radiodev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_रेजिस्टर_analog_subdevs(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	पूर्णांक ret;
	काष्ठा tuner_setup tun_setup;

	/* attach cx25840 capture chip */
	cxdev->cx25840 = v4l2_i2c_new_subdev(&cxdev->v4l2dev,
					     &dvbdev->i2c_adap,
					     "cx25840", 0x44, शून्य);
	अगर (!cxdev->cx25840) अणु
		dev_err(&dvbdev->udev->dev, "cx25840 not found\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Initialize cx25840 chip by calling its subdevice init core op.
	 *
	 * This चयनes it पूर्णांकo the generic mode that disables some of
	 * ivtv-related hacks in the cx25840 driver जबतक allowing setting
	 * of the chip video output configuration (passed in the call below
	 * as the last argument).
	 */
	ret = v4l2_subdev_call(cxdev->cx25840, core, init,
			       CX25840_VCONFIG_FMT_BT656 |
			       CX25840_VCONFIG_RES_8BIT |
			       CX25840_VCONFIG_VBIRAW_DISABLED |
			       CX25840_VCONFIG_ANCDATA_DISABLED |
			       CX25840_VCONFIG_ACTIVE_COMPOSITE |
			       CX25840_VCONFIG_VALID_ANDACTIVE |
			       CX25840_VCONFIG_HRESETW_NORMAL |
			       CX25840_VCONFIG_CLKGATE_NONE |
			       CX25840_VCONFIG_DCMODE_DWORDS);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev,
			"cx25840 init failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* attach analog tuner */
	cxdev->tuner = v4l2_i2c_new_subdev(&cxdev->v4l2dev,
					   &dvbdev->i2c_adap,
					   "tuner", 0x61, शून्य);
	अगर (!cxdev->tuner) अणु
		dev_err(&dvbdev->udev->dev, "tuner not found\n");
		वापस -ENODEV;
	पूर्ण

	/* configure it */
	स_रखो(&tun_setup, 0, माप(tun_setup));
	tun_setup.addr = 0x61;
	tun_setup.type = TUNER_PHILIPS_FMD1216ME_MK3;
	tun_setup.mode_mask = T_RADIO | T_ANALOG_TV;
	v4l2_subdev_call(cxdev->tuner, tuner, s_type_addr, &tun_setup);

	/* attach IF demod */
	cxdev->tda9887 = v4l2_i2c_new_subdev(&cxdev->v4l2dev,
					     &dvbdev->i2c_adap,
					     "tuner", 0x43, शून्य);
	अगर (!cxdev->tda9887) अणु
		dev_err(&dvbdev->udev->dev, "tda9887 not found\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxusb_medion_रेजिस्टर_analog(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	पूर्णांक ret;

	mutex_init(&cxdev->dev_lock);

	init_completion(&cxdev->v4l2_release);

	cxdev->v4l2dev.release = cxusb_medion_v4l2_release;

	ret = v4l2_device_रेजिस्टर(&dvbdev->udev->dev, &cxdev->v4l2dev);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev,
			"V4L2 device registration failed, ret = %d\n", ret);
		mutex_destroy(&cxdev->dev_lock);
		वापस ret;
	पूर्ण

	ret = cxusb_medion_रेजिस्टर_analog_subdevs(dvbdev);
	अगर (ret)
		जाओ ret_unरेजिस्टर;

	INIT_WORK(&cxdev->urbwork, cxusb_medion_v_complete_work);
	INIT_LIST_HEAD(&cxdev->buflist);

	cxdev->width = 320;
	cxdev->height = 240;

	ret = cxusb_medion_रेजिस्टर_analog_video(dvbdev);
	अगर (ret)
		जाओ ret_unरेजिस्टर;

	ret = cxusb_medion_रेजिस्टर_analog_radio(dvbdev);
	अगर (ret)
		जाओ ret_vunreg;

	वापस 0;

ret_vunreg:
	vb2_video_unरेजिस्टर_device(cxdev->videodev);

ret_unरेजिस्टर:
	v4l2_device_put(&cxdev->v4l2dev);
	रुको_क्रम_completion(&cxdev->v4l2_release);

	वापस ret;
पूर्ण

व्योम cxusb_medion_unरेजिस्टर_analog(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	cxusb_vprपूर्णांकk(dvbdev, OPS, "unregistering analog\n");

	video_unरेजिस्टर_device(cxdev->radiodev);
	vb2_video_unरेजिस्टर_device(cxdev->videodev);

	v4l2_device_put(&cxdev->v4l2dev);
	रुको_क्रम_completion(&cxdev->v4l2_release);

	cxusb_vprपूर्णांकk(dvbdev, OPS, "analog unregistered\n");
पूर्ण
