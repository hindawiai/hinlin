<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 *         Rick Chang <rick.chang@mediatek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>

#समावेश "mtk_jpeg_dec_parse.h"

#घोषणा TEM	0x01
#घोषणा SOF0	0xc0
#घोषणा RST	0xd0
#घोषणा SOI	0xd8
#घोषणा EOI	0xd9

काष्ठा mtk_jpeg_stream अणु
	u8 *addr;
	u32 size;
	u32 curr;
पूर्ण;

अटल पूर्णांक पढ़ो_byte(काष्ठा mtk_jpeg_stream *stream)
अणु
	अगर (stream->curr >= stream->size)
		वापस -1;
	वापस stream->addr[stream->curr++];
पूर्ण

अटल पूर्णांक पढ़ो_word_be(काष्ठा mtk_jpeg_stream *stream, u32 *word)
अणु
	u32 temp;
	पूर्णांक byte;

	byte = पढ़ो_byte(stream);
	अगर (byte == -1)
		वापस -1;
	temp = byte << 8;
	byte = पढ़ो_byte(stream);
	अगर (byte == -1)
		वापस -1;
	*word = (u32)byte | temp;

	वापस 0;
पूर्ण

अटल व्योम पढ़ो_skip(काष्ठा mtk_jpeg_stream *stream, दीर्घ len)
अणु
	अगर (len <= 0)
		वापस;
	जबतक (len--)
		पढ़ो_byte(stream);
पूर्ण

अटल bool mtk_jpeg_करो_parse(काष्ठा mtk_jpeg_dec_param *param, u8 *src_addr_va,
			      u32 src_size)
अणु
	bool notfound = true;
	काष्ठा mtk_jpeg_stream stream;

	stream.addr = src_addr_va;
	stream.size = src_size;
	stream.curr = 0;

	जबतक (notfound) अणु
		पूर्णांक i, length, byte;
		u32 word;

		byte = पढ़ो_byte(&stream);
		अगर (byte == -1)
			वापस false;
		अगर (byte != 0xff)
			जारी;
		करो
			byte = पढ़ो_byte(&stream);
		जबतक (byte == 0xff);
		अगर (byte == -1)
			वापस false;
		अगर (byte == 0)
			जारी;

		length = 0;
		चयन (byte) अणु
		हाल SOF0:
			/* length */
			अगर (पढ़ो_word_be(&stream, &word))
				अवरोध;

			/* precision */
			अगर (पढ़ो_byte(&stream) == -1)
				अवरोध;

			अगर (पढ़ो_word_be(&stream, &word))
				अवरोध;
			param->pic_h = word;

			अगर (पढ़ो_word_be(&stream, &word))
				अवरोध;
			param->pic_w = word;

			param->comp_num = पढ़ो_byte(&stream);
			अगर (param->comp_num != 1 && param->comp_num != 3)
				अवरोध;

			क्रम (i = 0; i < param->comp_num; i++) अणु
				param->comp_id[i] = पढ़ो_byte(&stream);
				अगर (param->comp_id[i] == -1)
					अवरोध;

				/* sampling */
				byte = पढ़ो_byte(&stream);
				अगर (byte == -1)
					अवरोध;
				param->sampling_w[i] = (byte >> 4) & 0x0F;
				param->sampling_h[i] = byte & 0x0F;

				param->qtbl_num[i] = पढ़ो_byte(&stream);
				अगर (param->qtbl_num[i] == -1)
					अवरोध;
			पूर्ण

			notfound = !(i == param->comp_num);
			अवरोध;
		हाल RST ... RST + 7:
		हाल SOI:
		हाल EOI:
		हाल TEM:
			अवरोध;
		शेष:
			अगर (पढ़ो_word_be(&stream, &word))
				अवरोध;
			length = (दीर्घ)word - 2;
			पढ़ो_skip(&stream, length);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस !notfound;
पूर्ण

bool mtk_jpeg_parse(काष्ठा mtk_jpeg_dec_param *param, u8 *src_addr_va,
		    u32 src_size)
अणु
	अगर (!mtk_jpeg_करो_parse(param, src_addr_va, src_size))
		वापस false;
	अगर (mtk_jpeg_dec_fill_param(param))
		वापस false;

	वापस true;
पूर्ण
