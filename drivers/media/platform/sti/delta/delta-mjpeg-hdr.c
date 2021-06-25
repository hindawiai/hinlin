<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2013
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#समावेश "delta.h"
#समावेश "delta-mjpeg.h"

#घोषणा MJPEG_SOF_0  0xc0
#घोषणा MJPEG_SOF_1  0xc1
#घोषणा MJPEG_SOI    0xd8
#घोषणा MJPEG_MARKER 0xff

अटल अक्षर *header_str(काष्ठा mjpeg_header *header,
			अक्षर *str,
			अचिन्हित पूर्णांक len)
अणु
	अक्षर *cur = str;
	अचिन्हित पूर्णांक left = len;

	अगर (!header)
		वापस "";

	snम_लिखो(cur, left, "[MJPEG header]\n"
			"|- length     = %d\n"
			"|- precision  = %d\n"
			"|- width      = %d\n"
			"|- height     = %d\n"
			"|- components = %d\n",
			header->length,
			header->sample_precision,
			header->frame_width,
			header->frame_height,
			header->nb_of_components);

	वापस str;
पूर्ण

अटल पूर्णांक delta_mjpeg_पढ़ो_sof(काष्ठा delta_ctx *pctx,
				अचिन्हित अक्षर *data, अचिन्हित पूर्णांक size,
				काष्ठा mjpeg_header *header)
अणु
	काष्ठा delta_dev *delta = pctx->dev;
	अचिन्हित पूर्णांक offset = 0;

	अगर (size < 64)
		जाओ err_no_more;

	स_रखो(header, 0, माप(*header));
	header->length           = be16_to_cpu(*(__be16 *)(data + offset));
	offset += माप(u16);
	header->sample_precision = *(u8 *)(data + offset);
	offset += माप(u8);
	header->frame_height     = be16_to_cpu(*(__be16 *)(data + offset));
	offset += माप(u16);
	header->frame_width      = be16_to_cpu(*(__be16 *)(data + offset));
	offset += माप(u16);
	header->nb_of_components = *(u8 *)(data + offset);
	offset += माप(u8);

	अगर (header->nb_of_components >= MJPEG_MAX_COMPONENTS) अणु
		dev_err(delta->dev,
			"%s   unsupported number of components (%d > %d)\n",
			pctx->name, header->nb_of_components,
			MJPEG_MAX_COMPONENTS);
		वापस -EINVAL;
	पूर्ण

	अगर ((offset + header->nb_of_components *
	     माप(header->components[0])) > size)
		जाओ err_no_more;

	वापस 0;

err_no_more:
	dev_err(delta->dev,
		"%s   sof: reached end of %d size input stream\n",
		pctx->name, size);
	वापस -ENODATA;
पूर्ण

पूर्णांक delta_mjpeg_पढ़ो_header(काष्ठा delta_ctx *pctx,
			    अचिन्हित अक्षर *data, अचिन्हित पूर्णांक size,
			    काष्ठा mjpeg_header *header,
			    अचिन्हित पूर्णांक *data_offset)
अणु
	काष्ठा delta_dev *delta = pctx->dev;
	अचिन्हित अक्षर str[200];

	अचिन्हित पूर्णांक ret = 0;
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित पूर्णांक soi = 0;

	अगर (size < 2)
		जाओ err_no_more;

	offset = 0;
	जबतक (1) अणु
		अगर (data[offset] == MJPEG_MARKER)
			चयन (data[offset + 1]) अणु
			हाल MJPEG_SOI:
				soi = 1;
				*data_offset = offset;
				अवरोध;

			हाल MJPEG_SOF_0:
			हाल MJPEG_SOF_1:
				अगर (!soi) अणु
					dev_err(delta->dev,
						"%s   wrong sequence, got SOF while SOI not seen\n",
						pctx->name);
					वापस -EINVAL;
				पूर्ण

				ret = delta_mjpeg_पढ़ो_sof(pctx,
							   &data[offset + 2],
							   size - (offset + 2),
							   header);
				अगर (ret)
					जाओ err;

				जाओ करोne;

			शेष:
				अवरोध;
			पूर्ण

		offset++;
		अगर ((offset + 2) >= size)
			जाओ err_no_more;
	पूर्ण

करोne:
	dev_dbg(delta->dev,
		"%s   found header @ offset %d:\n%s", pctx->name,
		*data_offset,
		header_str(header, str, माप(str)));
	वापस 0;

err_no_more:
	dev_err(delta->dev,
		"%s   no header found within %d bytes input stream\n",
		pctx->name, size);
	वापस -ENODATA;

err:
	वापस ret;
पूर्ण
