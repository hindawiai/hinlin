<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PC-Speaker driver क्रम Linux
 *
 * Copyright (C) 1993-1997  Michael Beck
 * Copyright (C) 1997-2001  David Woodhouse
 * Copyright (C) 2001-2008  Stas Sergeev
 */

#अगर_अघोषित __PCSP_H__
#घोषणा __PCSP_H__

#समावेश <linux/hrसमयr.h>
#समावेश <linux/i8253.h>
#समावेश <linux/समयx.h>

#घोषणा PCSP_SOUND_VERSION 0x400	/* पढ़ो 4.00 */
#घोषणा PCSP_DEBUG 0

/* शेष समयr freq क्रम PC-Speaker: 18643 Hz */
#घोषणा DIV_18KHZ 64
#घोषणा MAX_DIV DIV_18KHZ
#घोषणा CALC_DIV(d) (MAX_DIV >> (d))
#घोषणा CUR_DIV() CALC_DIV(chip->treble)
#घोषणा PCSP_MAX_TREBLE 1

/* unक्रमtunately, with hrसमयrs 37KHz करोes not work very well :( */
#घोषणा PCSP_DEFAULT_TREBLE 0
#घोषणा MIN_DIV (MAX_DIV >> PCSP_MAX_TREBLE)

/* wild guess */
#घोषणा PCSP_MIN_LPJ 1000000
#घोषणा PCSP_DEFAULT_SDIV (DIV_18KHZ >> 1)
#घोषणा PCSP_DEFAULT_SRATE (PIT_TICK_RATE / PCSP_DEFAULT_SDIV)
#घोषणा PCSP_INDEX_INC() (1 << (PCSP_MAX_TREBLE - chip->treble))
#घोषणा PCSP_CALC_RATE(i) (PIT_TICK_RATE / CALC_DIV(i))
#घोषणा PCSP_RATE() PCSP_CALC_RATE(chip->treble)
#घोषणा PCSP_MIN_RATE__1 MAX_DIV/PIT_TICK_RATE
#घोषणा PCSP_MAX_RATE__1 MIN_DIV/PIT_TICK_RATE
#घोषणा PCSP_MAX_PERIOD_NS (1000000000ULL * PCSP_MIN_RATE__1)
#घोषणा PCSP_MIN_PERIOD_NS (1000000000ULL * PCSP_MAX_RATE__1)
#घोषणा PCSP_CALC_NS(भाग) (अणु \
	u64 __val = 1000000000ULL * (भाग); \
	करो_भाग(__val, PIT_TICK_RATE); \
	__val; \
पूर्ण)
#घोषणा PCSP_PERIOD_NS() PCSP_CALC_NS(CUR_DIV())

#घोषणा PCSP_MAX_PERIOD_SIZE	(64*1024)
#घोषणा PCSP_MAX_PERIODS	512
#घोषणा PCSP_BUFFER_SIZE	(128*1024)

काष्ठा snd_pcsp अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा input_dev *input_dev;
	काष्ठा hrसमयr समयr;
	अचिन्हित लघु port, irq, dma;
	spinlock_t substream_lock;
	काष्ठा snd_pcm_substream *playback_substream;
	अचिन्हित पूर्णांक fmt_size;
	अचिन्हित पूर्णांक is_चिन्हित;
	माप_प्रकार playback_ptr;
	माप_प्रकार period_ptr;
	atomic_t समयr_active;
	पूर्णांक thalf;
	u64 ns_rem;
	अचिन्हित अक्षर val61;
	पूर्णांक enable;
	पूर्णांक max_treble;
	पूर्णांक treble;
	पूर्णांक pcspkr;
पूर्ण;

बाह्य काष्ठा snd_pcsp pcsp_chip;

बाह्य क्रमागत hrसमयr_restart pcsp_करो_समयr(काष्ठा hrसमयr *handle);
बाह्य व्योम pcsp_sync_stop(काष्ठा snd_pcsp *chip);

बाह्य पूर्णांक snd_pcsp_new_pcm(काष्ठा snd_pcsp *chip);
बाह्य पूर्णांक snd_pcsp_new_mixer(काष्ठा snd_pcsp *chip, पूर्णांक nopcm);

#पूर्ण_अगर
