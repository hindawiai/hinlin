<शैली गुरु>
/*
 *  PCM Interface - misc routines
 *  Copyright (c) 1998 by Jaroslav Kysela <perex@perex.cz>
 *
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
  
#समावेश <linux/समय.स>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "pcm_local.h"

#घोषणा SND_PCM_FORMAT_UNKNOWN (-1)

/* NOTE: "signed" prefix must be given below since the शेष अक्षर is
 *       अचिन्हित on some architectures!
 */
काष्ठा pcm_क्रमmat_data अणु
	अचिन्हित अक्षर width;	/* bit width */
	अचिन्हित अक्षर phys;	/* physical bit width */
	चिन्हित अक्षर le;	/* 0 = big-endian, 1 = little-endian, -1 = others */
	चिन्हित अक्षर signd;	/* 0 = अचिन्हित, 1 = चिन्हित, -1 = others */
	अचिन्हित अक्षर silence[8];	/* silence data to fill */
पूर्ण;

/* we करो lots of calculations on snd_pcm_क्रमmat_t; shut up sparse */
#घोषणा INT	__क्रमce पूर्णांक

अटल bool valid_क्रमmat(snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस (INT)क्रमmat >= 0 && (INT)क्रमmat <= (INT)SNDRV_PCM_FORMAT_LAST;
पूर्ण

अटल स्थिर काष्ठा pcm_क्रमmat_data pcm_क्रमmats[(INT)SNDRV_PCM_FORMAT_LAST+1] = अणु
	[SNDRV_PCM_FORMAT_S8] = अणु
		.width = 8, .phys = 8, .le = -1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U8] = अणु
		.width = 8, .phys = 8, .le = -1, .signd = 0,
		.silence = अणु 0x80 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S16_LE] = अणु
		.width = 16, .phys = 16, .le = 1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S16_BE] = अणु
		.width = 16, .phys = 16, .le = 0, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U16_LE] = अणु
		.width = 16, .phys = 16, .le = 1, .signd = 0,
		.silence = अणु 0x00, 0x80 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U16_BE] = अणु
		.width = 16, .phys = 16, .le = 0, .signd = 0,
		.silence = अणु 0x80, 0x00 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S24_LE] = अणु
		.width = 24, .phys = 32, .le = 1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S24_BE] = अणु
		.width = 24, .phys = 32, .le = 0, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U24_LE] = अणु
		.width = 24, .phys = 32, .le = 1, .signd = 0,
		.silence = अणु 0x00, 0x00, 0x80 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U24_BE] = अणु
		.width = 24, .phys = 32, .le = 0, .signd = 0,
		.silence = अणु 0x00, 0x80, 0x00, 0x00 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S32_LE] = अणु
		.width = 32, .phys = 32, .le = 1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S32_BE] = अणु
		.width = 32, .phys = 32, .le = 0, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U32_LE] = अणु
		.width = 32, .phys = 32, .le = 1, .signd = 0,
		.silence = अणु 0x00, 0x00, 0x00, 0x80 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U32_BE] = अणु
		.width = 32, .phys = 32, .le = 0, .signd = 0,
		.silence = अणु 0x80, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_FLOAT_LE] = अणु
		.width = 32, .phys = 32, .le = 1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_FLOAT_BE] = अणु
		.width = 32, .phys = 32, .le = 0, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_FLOAT64_LE] = अणु
		.width = 64, .phys = 64, .le = 1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_FLOAT64_BE] = अणु
		.width = 64, .phys = 64, .le = 0, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE] = अणु
		.width = 32, .phys = 32, .le = 1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE] = अणु
		.width = 32, .phys = 32, .le = 0, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_MU_LAW] = अणु
		.width = 8, .phys = 8, .le = -1, .signd = -1,
		.silence = अणु 0x7f पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_A_LAW] = अणु
		.width = 8, .phys = 8, .le = -1, .signd = -1,
		.silence = अणु 0x55 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_IMA_ADPCM] = अणु
		.width = 4, .phys = 4, .le = -1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_G723_24] = अणु
		.width = 3, .phys = 3, .le = -1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_G723_40] = अणु
		.width = 5, .phys = 5, .le = -1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_DSD_U8] = अणु
		.width = 8, .phys = 8, .le = 1, .signd = 0,
		.silence = अणु 0x69 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_DSD_U16_LE] = अणु
		.width = 16, .phys = 16, .le = 1, .signd = 0,
		.silence = अणु 0x69, 0x69 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_DSD_U32_LE] = अणु
		.width = 32, .phys = 32, .le = 1, .signd = 0,
		.silence = अणु 0x69, 0x69, 0x69, 0x69 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_DSD_U16_BE] = अणु
		.width = 16, .phys = 16, .le = 0, .signd = 0,
		.silence = अणु 0x69, 0x69 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_DSD_U32_BE] = अणु
		.width = 32, .phys = 32, .le = 0, .signd = 0,
		.silence = अणु 0x69, 0x69, 0x69, 0x69 पूर्ण,
	पूर्ण,
	/* FIXME: the following two क्रमmats are not defined properly yet */
	[SNDRV_PCM_FORMAT_MPEG] = अणु
		.le = -1, .signd = -1,
	पूर्ण,
	[SNDRV_PCM_FORMAT_GSM] = अणु
		.le = -1, .signd = -1,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S20_LE] = अणु
		.width = 20, .phys = 32, .le = 1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S20_BE] = अणु
		.width = 20, .phys = 32, .le = 0, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U20_LE] = अणु
		.width = 20, .phys = 32, .le = 1, .signd = 0,
		.silence = अणु 0x00, 0x00, 0x08, 0x00 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U20_BE] = अणु
		.width = 20, .phys = 32, .le = 0, .signd = 0,
		.silence = अणु 0x00, 0x08, 0x00, 0x00 पूर्ण,
	पूर्ण,
	/* FIXME: the following क्रमmat is not defined properly yet */
	[SNDRV_PCM_FORMAT_SPECIAL] = अणु
		.le = -1, .signd = -1,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S24_3LE] = अणु
		.width = 24, .phys = 24, .le = 1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S24_3BE] = अणु
		.width = 24, .phys = 24, .le = 0, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U24_3LE] = अणु
		.width = 24, .phys = 24, .le = 1, .signd = 0,
		.silence = अणु 0x00, 0x00, 0x80 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U24_3BE] = अणु
		.width = 24, .phys = 24, .le = 0, .signd = 0,
		.silence = अणु 0x80, 0x00, 0x00 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S20_3LE] = अणु
		.width = 20, .phys = 24, .le = 1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S20_3BE] = अणु
		.width = 20, .phys = 24, .le = 0, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U20_3LE] = अणु
		.width = 20, .phys = 24, .le = 1, .signd = 0,
		.silence = अणु 0x00, 0x00, 0x08 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U20_3BE] = अणु
		.width = 20, .phys = 24, .le = 0, .signd = 0,
		.silence = अणु 0x08, 0x00, 0x00 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S18_3LE] = अणु
		.width = 18, .phys = 24, .le = 1, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_S18_3BE] = अणु
		.width = 18, .phys = 24, .le = 0, .signd = 1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U18_3LE] = अणु
		.width = 18, .phys = 24, .le = 1, .signd = 0,
		.silence = अणु 0x00, 0x00, 0x02 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_U18_3BE] = अणु
		.width = 18, .phys = 24, .le = 0, .signd = 0,
		.silence = अणु 0x02, 0x00, 0x00 पूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_G723_24_1B] = अणु
		.width = 3, .phys = 8, .le = -1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
	[SNDRV_PCM_FORMAT_G723_40_1B] = अणु
		.width = 5, .phys = 8, .le = -1, .signd = -1,
		.silence = अणुपूर्ण,
	पूर्ण,
पूर्ण;


/**
 * snd_pcm_क्रमmat_चिन्हित - Check the PCM क्रमmat is चिन्हित linear
 * @क्रमmat: the क्रमmat to check
 *
 * Return: 1 अगर the given PCM क्रमmat is चिन्हित linear, 0 अगर अचिन्हित
 * linear, and a negative error code क्रम non-linear क्रमmats.
 */
पूर्णांक snd_pcm_क्रमmat_चिन्हित(snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक val;
	अगर (!valid_क्रमmat(क्रमmat))
		वापस -EINVAL;
	अगर ((val = pcm_क्रमmats[(INT)क्रमmat].signd) < 0)
		वापस -EINVAL;
	वापस val;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_चिन्हित);

/**
 * snd_pcm_क्रमmat_अचिन्हित - Check the PCM क्रमmat is अचिन्हित linear
 * @क्रमmat: the क्रमmat to check
 *
 * Return: 1 अगर the given PCM क्रमmat is अचिन्हित linear, 0 अगर चिन्हित
 * linear, and a negative error code क्रम non-linear क्रमmats.
 */
पूर्णांक snd_pcm_क्रमmat_अचिन्हित(snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक val;

	val = snd_pcm_क्रमmat_चिन्हित(क्रमmat);
	अगर (val < 0)
		वापस val;
	वापस !val;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_अचिन्हित);

/**
 * snd_pcm_क्रमmat_linear - Check the PCM क्रमmat is linear
 * @क्रमmat: the क्रमmat to check
 *
 * Return: 1 अगर the given PCM क्रमmat is linear, 0 अगर not.
 */
पूर्णांक snd_pcm_क्रमmat_linear(snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस snd_pcm_क्रमmat_चिन्हित(क्रमmat) >= 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_linear);

/**
 * snd_pcm_क्रमmat_little_endian - Check the PCM क्रमmat is little-endian
 * @क्रमmat: the क्रमmat to check
 *
 * Return: 1 अगर the given PCM क्रमmat is little-endian, 0 अगर
 * big-endian, or a negative error code अगर endian not specअगरied.
 */
पूर्णांक snd_pcm_क्रमmat_little_endian(snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक val;
	अगर (!valid_क्रमmat(क्रमmat))
		वापस -EINVAL;
	अगर ((val = pcm_क्रमmats[(INT)क्रमmat].le) < 0)
		वापस -EINVAL;
	वापस val;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_little_endian);

/**
 * snd_pcm_क्रमmat_big_endian - Check the PCM क्रमmat is big-endian
 * @क्रमmat: the क्रमmat to check
 *
 * Return: 1 अगर the given PCM क्रमmat is big-endian, 0 अगर
 * little-endian, or a negative error code अगर endian not specअगरied.
 */
पूर्णांक snd_pcm_क्रमmat_big_endian(snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक val;

	val = snd_pcm_क्रमmat_little_endian(क्रमmat);
	अगर (val < 0)
		वापस val;
	वापस !val;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_big_endian);

/**
 * snd_pcm_क्रमmat_width - वापस the bit-width of the क्रमmat
 * @क्रमmat: the क्रमmat to check
 *
 * Return: The bit-width of the क्रमmat, or a negative error code
 * अगर unknown क्रमmat.
 */
पूर्णांक snd_pcm_क्रमmat_width(snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक val;
	अगर (!valid_क्रमmat(क्रमmat))
		वापस -EINVAL;
	अगर ((val = pcm_क्रमmats[(INT)क्रमmat].width) == 0)
		वापस -EINVAL;
	वापस val;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_width);

/**
 * snd_pcm_क्रमmat_physical_width - वापस the physical bit-width of the क्रमmat
 * @क्रमmat: the क्रमmat to check
 *
 * Return: The physical bit-width of the क्रमmat, or a negative error code
 * अगर unknown क्रमmat.
 */
पूर्णांक snd_pcm_क्रमmat_physical_width(snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक val;
	अगर (!valid_क्रमmat(क्रमmat))
		वापस -EINVAL;
	अगर ((val = pcm_क्रमmats[(INT)क्रमmat].phys) == 0)
		वापस -EINVAL;
	वापस val;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_physical_width);

/**
 * snd_pcm_क्रमmat_size - वापस the byte size of samples on the given क्रमmat
 * @क्रमmat: the क्रमmat to check
 * @samples: sampling rate
 *
 * Return: The byte size of the given samples क्रम the क्रमmat, or a
 * negative error code अगर unknown क्रमmat.
 */
sमाप_प्रकार snd_pcm_क्रमmat_size(snd_pcm_क्रमmat_t क्रमmat, माप_प्रकार samples)
अणु
	पूर्णांक phys_width = snd_pcm_क्रमmat_physical_width(क्रमmat);
	अगर (phys_width < 0)
		वापस -EINVAL;
	वापस samples * phys_width / 8;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_size);

/**
 * snd_pcm_क्रमmat_silence_64 - वापस the silent data in 8 bytes array
 * @क्रमmat: the क्रमmat to check
 *
 * Return: The क्रमmat pattern to fill or %शून्य अगर error.
 */
स्थिर अचिन्हित अक्षर *snd_pcm_क्रमmat_silence_64(snd_pcm_क्रमmat_t क्रमmat)
अणु
	अगर (!valid_क्रमmat(क्रमmat))
		वापस शून्य;
	अगर (! pcm_क्रमmats[(INT)क्रमmat].phys)
		वापस शून्य;
	वापस pcm_क्रमmats[(INT)क्रमmat].silence;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_silence_64);

/**
 * snd_pcm_क्रमmat_set_silence - set the silence data on the buffer
 * @क्रमmat: the PCM क्रमmat
 * @data: the buffer poपूर्णांकer
 * @samples: the number of samples to set silence
 *
 * Sets the silence data on the buffer क्रम the given samples.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_क्रमmat_set_silence(snd_pcm_क्रमmat_t क्रमmat, व्योम *data, अचिन्हित पूर्णांक samples)
अणु
	पूर्णांक width;
	अचिन्हित अक्षर *dst;
	स्थिर अचिन्हित अक्षर *pat;

	अगर (!valid_क्रमmat(क्रमmat))
		वापस -EINVAL;
	अगर (samples == 0)
		वापस 0;
	width = pcm_क्रमmats[(INT)क्रमmat].phys; /* physical width */
	pat = pcm_क्रमmats[(INT)क्रमmat].silence;
	अगर (! width)
		वापस -EINVAL;
	/* चिन्हित or 1 byte data */
	अगर (pcm_क्रमmats[(INT)क्रमmat].signd == 1 || width <= 8) अणु
		अचिन्हित पूर्णांक bytes = samples * width / 8;
		स_रखो(data, *pat, bytes);
		वापस 0;
	पूर्ण
	/* non-zero samples, fill using a loop */
	width /= 8;
	dst = data;
#अगर 0
	जबतक (samples--) अणु
		स_नकल(dst, pat, width);
		dst += width;
	पूर्ण
#अन्यथा
	/* a bit optimization क्रम स्थिरant width */
	चयन (width) अणु
	हाल 2:
		जबतक (samples--) अणु
			स_नकल(dst, pat, 2);
			dst += 2;
		पूर्ण
		अवरोध;
	हाल 3:
		जबतक (samples--) अणु
			स_नकल(dst, pat, 3);
			dst += 3;
		पूर्ण
		अवरोध;
	हाल 4:
		जबतक (samples--) अणु
			स_नकल(dst, pat, 4);
			dst += 4;
		पूर्ण
		अवरोध;
	हाल 8:
		जबतक (samples--) अणु
			स_नकल(dst, pat, 8);
			dst += 8;
		पूर्ण
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_क्रमmat_set_silence);

/**
 * snd_pcm_hw_limit_rates - determine rate_min/rate_max fields
 * @hw: the pcm hw instance
 *
 * Determines the rate_min and rate_max fields from the rates bits of
 * the given hw.
 *
 * Return: Zero अगर successful.
 */
पूर्णांक snd_pcm_hw_limit_rates(काष्ठा snd_pcm_hardware *hw)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < (पूर्णांक)snd_pcm_known_rates.count; i++) अणु
		अगर (hw->rates & (1 << i)) अणु
			hw->rate_min = snd_pcm_known_rates.list[i];
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = (पूर्णांक)snd_pcm_known_rates.count - 1; i >= 0; i--) अणु
		अगर (hw->rates & (1 << i)) अणु
			hw->rate_max = snd_pcm_known_rates.list[i];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_limit_rates);

/**
 * snd_pcm_rate_to_rate_bit - converts sample rate to SNDRV_PCM_RATE_xxx bit
 * @rate: the sample rate to convert
 *
 * Return: The SNDRV_PCM_RATE_xxx flag that corresponds to the given rate, or
 * SNDRV_PCM_RATE_KNOT क्रम an unknown rate.
 */
अचिन्हित पूर्णांक snd_pcm_rate_to_rate_bit(अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < snd_pcm_known_rates.count; i++)
		अगर (snd_pcm_known_rates.list[i] == rate)
			वापस 1u << i;
	वापस SNDRV_PCM_RATE_KNOT;
पूर्ण
EXPORT_SYMBOL(snd_pcm_rate_to_rate_bit);

/**
 * snd_pcm_rate_bit_to_rate - converts SNDRV_PCM_RATE_xxx bit to sample rate
 * @rate_bit: the rate bit to convert
 *
 * Return: The sample rate that corresponds to the given SNDRV_PCM_RATE_xxx flag
 * or 0 क्रम an unknown rate bit.
 */
अचिन्हित पूर्णांक snd_pcm_rate_bit_to_rate(अचिन्हित पूर्णांक rate_bit)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < snd_pcm_known_rates.count; i++)
		अगर ((1u << i) == rate_bit)
			वापस snd_pcm_known_rates.list[i];
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_rate_bit_to_rate);

अटल अचिन्हित पूर्णांक snd_pcm_rate_mask_sanitize(अचिन्हित पूर्णांक rates)
अणु
	अगर (rates & SNDRV_PCM_RATE_CONTINUOUS)
		वापस SNDRV_PCM_RATE_CONTINUOUS;
	अन्यथा अगर (rates & SNDRV_PCM_RATE_KNOT)
		वापस SNDRV_PCM_RATE_KNOT;
	वापस rates;
पूर्ण

/**
 * snd_pcm_rate_mask_पूर्णांकersect - computes the पूर्णांकersection between two rate masks
 * @rates_a: The first rate mask
 * @rates_b: The second rate mask
 *
 * This function computes the rates that are supported by both rate masks passed
 * to the function. It will take care of the special handling of
 * SNDRV_PCM_RATE_CONTINUOUS and SNDRV_PCM_RATE_KNOT.
 *
 * Return: A rate mask containing the rates that are supported by both rates_a
 * and rates_b.
 */
अचिन्हित पूर्णांक snd_pcm_rate_mask_पूर्णांकersect(अचिन्हित पूर्णांक rates_a,
	अचिन्हित पूर्णांक rates_b)
अणु
	rates_a = snd_pcm_rate_mask_sanitize(rates_a);
	rates_b = snd_pcm_rate_mask_sanitize(rates_b);

	अगर (rates_a & SNDRV_PCM_RATE_CONTINUOUS)
		वापस rates_b;
	अन्यथा अगर (rates_b & SNDRV_PCM_RATE_CONTINUOUS)
		वापस rates_a;
	अन्यथा अगर (rates_a & SNDRV_PCM_RATE_KNOT)
		वापस rates_b;
	अन्यथा अगर (rates_b & SNDRV_PCM_RATE_KNOT)
		वापस rates_a;
	वापस rates_a & rates_b;
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_rate_mask_पूर्णांकersect);

/**
 * snd_pcm_rate_range_to_bits - converts rate range to SNDRV_PCM_RATE_xxx bit
 * @rate_min: the minimum sample rate
 * @rate_max: the maximum sample rate
 *
 * This function has an implicit assumption: the rates in the given range have
 * only the pre-defined rates like 44100 or 16000.
 *
 * Return: The SNDRV_PCM_RATE_xxx flag that corresponds to the given rate range,
 * or SNDRV_PCM_RATE_KNOT क्रम an unknown range.
 */
अचिन्हित पूर्णांक snd_pcm_rate_range_to_bits(अचिन्हित पूर्णांक rate_min,
	अचिन्हित पूर्णांक rate_max)
अणु
	अचिन्हित पूर्णांक rates = 0;
	पूर्णांक i;

	क्रम (i = 0; i < snd_pcm_known_rates.count; i++) अणु
		अगर (snd_pcm_known_rates.list[i] >= rate_min
			&& snd_pcm_known_rates.list[i] <= rate_max)
			rates |= 1 << i;
	पूर्ण

	अगर (!rates)
		rates = SNDRV_PCM_RATE_KNOT;

	वापस rates;
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_rate_range_to_bits);
