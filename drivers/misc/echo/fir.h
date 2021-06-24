<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SpanDSP - a series of DSP components क्रम telephony
 *
 * fir.h - General telephony FIR routines
 *
 * Written by Steve Underwood <steveu@coppice.org>
 *
 * Copyright (C) 2002 Steve Underwood
 *
 * All rights reserved.
 */

#अगर !defined(_FIR_H_)
#घोषणा _FIR_H_

/*
   Ideas क्रम improvement:

   1/ Reग_लिखो filter क्रम dual MAC inner loop.  The issue here is handling
   history sample offsets that are 16 bit aligned - the dual MAC needs
   32 bit aligmnent.  There are some good examples in libbfdsp.

   2/ Use the hardware circular buffer facility tohalve memory usage.

   3/ Consider using पूर्णांकernal memory.

   Using less memory might also improve speed as cache misses will be
   reduced. A drop in MIPs and memory approaching 50% should be
   possible.

   The क्रमeground and background filters currenlty use a total of
   about 10 MIPs/ch as measured with speedtest.c on a 256 TAP echo
   can.
*/

/*
 * 16 bit पूर्णांकeger FIR descriptor. This defines the working state क्रम a single
 * instance of an FIR filter using 16 bit पूर्णांकeger coefficients.
 */
काष्ठा fir16_state_t अणु
	पूर्णांक taps;
	पूर्णांक curr_pos;
	स्थिर पूर्णांक16_t *coeffs;
	पूर्णांक16_t *history;
पूर्ण;

/*
 * 32 bit पूर्णांकeger FIR descriptor. This defines the working state क्रम a single
 * instance of an FIR filter using 32 bit पूर्णांकeger coefficients, and filtering
 * 16 bit पूर्णांकeger data.
 */
काष्ठा fir32_state_t अणु
	पूर्णांक taps;
	पूर्णांक curr_pos;
	स्थिर पूर्णांक32_t *coeffs;
	पूर्णांक16_t *history;
पूर्ण;

/*
 * Floating poपूर्णांक FIR descriptor. This defines the working state क्रम a single
 * instance of an FIR filter using भग्नing poपूर्णांक coefficients and data.
 */
काष्ठा fir_भग्न_state_t अणु
	पूर्णांक taps;
	पूर्णांक curr_pos;
	स्थिर भग्न *coeffs;
	भग्न *history;
पूर्ण;

अटल अंतरभूत स्थिर पूर्णांक16_t *fir16_create(काष्ठा fir16_state_t *fir,
					      स्थिर पूर्णांक16_t *coeffs, पूर्णांक taps)
अणु
	fir->taps = taps;
	fir->curr_pos = taps - 1;
	fir->coeffs = coeffs;
	fir->history = kसुस्मृति(taps, माप(पूर्णांक16_t), GFP_KERNEL);
	वापस fir->history;
पूर्ण

अटल अंतरभूत व्योम fir16_flush(काष्ठा fir16_state_t *fir)
अणु
	स_रखो(fir->history, 0, fir->taps * माप(पूर्णांक16_t));
पूर्ण

अटल अंतरभूत व्योम fir16_मुक्त(काष्ठा fir16_state_t *fir)
अणु
	kमुक्त(fir->history);
पूर्ण

अटल अंतरभूत पूर्णांक16_t fir16(काष्ठा fir16_state_t *fir, पूर्णांक16_t sample)
अणु
	पूर्णांक32_t y;
	पूर्णांक i;
	पूर्णांक offset1;
	पूर्णांक offset2;

	fir->history[fir->curr_pos] = sample;

	offset2 = fir->curr_pos;
	offset1 = fir->taps - offset2;
	y = 0;
	क्रम (i = fir->taps - 1; i >= offset1; i--)
		y += fir->coeffs[i] * fir->history[i - offset1];
	क्रम (; i >= 0; i--)
		y += fir->coeffs[i] * fir->history[i + offset2];
	अगर (fir->curr_pos <= 0)
		fir->curr_pos = fir->taps;
	fir->curr_pos--;
	वापस (पूर्णांक16_t) (y >> 15);
पूर्ण

अटल अंतरभूत स्थिर पूर्णांक16_t *fir32_create(काष्ठा fir32_state_t *fir,
					      स्थिर पूर्णांक32_t *coeffs, पूर्णांक taps)
अणु
	fir->taps = taps;
	fir->curr_pos = taps - 1;
	fir->coeffs = coeffs;
	fir->history = kसुस्मृति(taps, माप(पूर्णांक16_t), GFP_KERNEL);
	वापस fir->history;
पूर्ण

अटल अंतरभूत व्योम fir32_flush(काष्ठा fir32_state_t *fir)
अणु
	स_रखो(fir->history, 0, fir->taps * माप(पूर्णांक16_t));
पूर्ण

अटल अंतरभूत व्योम fir32_मुक्त(काष्ठा fir32_state_t *fir)
अणु
	kमुक्त(fir->history);
पूर्ण

अटल अंतरभूत पूर्णांक16_t fir32(काष्ठा fir32_state_t *fir, पूर्णांक16_t sample)
अणु
	पूर्णांक i;
	पूर्णांक32_t y;
	पूर्णांक offset1;
	पूर्णांक offset2;

	fir->history[fir->curr_pos] = sample;
	offset2 = fir->curr_pos;
	offset1 = fir->taps - offset2;
	y = 0;
	क्रम (i = fir->taps - 1; i >= offset1; i--)
		y += fir->coeffs[i] * fir->history[i - offset1];
	क्रम (; i >= 0; i--)
		y += fir->coeffs[i] * fir->history[i + offset2];
	अगर (fir->curr_pos <= 0)
		fir->curr_pos = fir->taps;
	fir->curr_pos--;
	वापस (पूर्णांक16_t) (y >> 15);
पूर्ण

#पूर्ण_अगर
