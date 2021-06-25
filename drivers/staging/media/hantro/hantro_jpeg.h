<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#घोषणा JPEG_HEADER_SIZE	601

काष्ठा hantro_jpeg_ctx अणु
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक quality;
	अचिन्हित अक्षर *buffer;
पूर्ण;

अचिन्हित अक्षर *hantro_jpeg_get_qtable(पूर्णांक index);
व्योम hantro_jpeg_header_assemble(काष्ठा hantro_jpeg_ctx *ctx);
