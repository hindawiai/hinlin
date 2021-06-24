<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Hewlett-Packard Harmony audio driver
 * Copyright (C) 2004, Kyle McMartin <kyle@parisc-linux.org>
 */

#अगर_अघोषित __HARMONY_H__
#घोषणा __HARMONY_H__

काष्ठा harmony_buffer अणु
        अचिन्हित दीर्घ addr;
        पूर्णांक buf;
        पूर्णांक count;
        पूर्णांक size;
        पूर्णांक coherent;
पूर्ण;

काष्ठा snd_harmony अणु
        पूर्णांक irq;

        अचिन्हित दीर्घ hpa; /* hard physical address */
        व्योम __iomem *iobase; /* remapped io address */

        काष्ठा parisc_device *dev;

        काष्ठा अणु
                u32 gain;
                u32 rate;
                u32 क्रमmat;
                u32 stereo;
		पूर्णांक playing;
		पूर्णांक capturing;
        पूर्ण st;

        काष्ठा snd_dma_device dma; /* playback/capture */
        काष्ठा harmony_buffer pbuf;
	काष्ठा harmony_buffer cbuf;

        काष्ठा snd_dma_buffer gdma; /* graveyard */
        काष्ठा snd_dma_buffer sdma; /* silence */

        काष्ठा अणु
                अचिन्हित दीर्घ play_पूर्णांकr;
	        अचिन्हित दीर्घ rec_पूर्णांकr;
                अचिन्हित दीर्घ graveyard_पूर्णांकr;
                अचिन्हित दीर्घ silence_पूर्णांकr;
        पूर्ण stats;

        काष्ठा snd_pcm *pcm;
        काष्ठा snd_card *card;
        काष्ठा snd_pcm_substream *psubs;
	काष्ठा snd_pcm_substream *csubs;
        काष्ठा snd_info_entry *proc;

        spinlock_t lock;
        spinlock_t mixer_lock;
पूर्ण;

#घोषणा MAX_PCM_DEVICES     1
#घोषणा MAX_PCM_SUBSTREAMS  4
#घोषणा MAX_MIDI_DEVICES    0

#घोषणा HARMONY_SIZE       64

#घोषणा BUF_SIZE     PAGE_SIZE
#घोषणा MAX_BUFS     16
#घोषणा MAX_BUF_SIZE (MAX_BUFS * BUF_SIZE)

#घोषणा PLAYBACK_BUFS    MAX_BUFS
#घोषणा RECORD_BUFS      MAX_BUFS
#घोषणा GRAVEYARD_BUFS   1
#घोषणा GRAVEYARD_BUFSZ  (GRAVEYARD_BUFS*BUF_SIZE)
#घोषणा SILENCE_BUFS     1
#घोषणा SILENCE_BUFSZ    (SILENCE_BUFS*BUF_SIZE)

#घोषणा HARMONY_ID       0x000
#घोषणा HARMONY_RESET    0x004
#घोषणा HARMONY_CNTL     0x008
#घोषणा HARMONY_GAINCTL  0x00c
#घोषणा HARMONY_PNXTADD  0x010
#घोषणा HARMONY_PCURADD  0x014
#घोषणा HARMONY_RNXTADD  0x018
#घोषणा HARMONY_RCURADD  0x01c
#घोषणा HARMONY_DSTATUS  0x020
#घोषणा HARMONY_OV       0x024
#घोषणा HARMONY_PIO      0x028
#घोषणा HARMONY_DIAG     0x03c

#घोषणा HARMONY_CNTL_C          0x80000000
#घोषणा HARMONY_CNTL_ST         0x00000020
#घोषणा HARMONY_CNTL_44100      0x00000015      /* HARMONY_SR_44KHZ */
#घोषणा HARMONY_CNTL_8000       0x00000008      /* HARMONY_SR_8KHZ */

#घोषणा HARMONY_DSTATUS_ID      0x00000000 /* पूर्णांकerrupts off */
#घोषणा HARMONY_DSTATUS_PN      0x00000200 /* playback fill */
#घोषणा HARMONY_DSTATUS_RN      0x00000002 /* record fill */
#घोषणा HARMONY_DSTATUS_IE      0x80000000 /* पूर्णांकerrupts on */

#घोषणा HARMONY_DF_16BIT_LINEAR 0x00000000
#घोषणा HARMONY_DF_8BIT_ULAW    0x00000001
#घोषणा HARMONY_DF_8BIT_ALAW    0x00000002

#घोषणा HARMONY_SS_MONO         0x00000000
#घोषणा HARMONY_SS_STEREO       0x00000001

#घोषणा HARMONY_GAIN_SILENCE    0x01F00FFF
#घोषणा HARMONY_GAIN_DEFAULT    0x01F00FFF

#घोषणा HARMONY_GAIN_HE_SHIFT   27 /* headphones enabled */
#घोषणा HARMONY_GAIN_HE_MASK    (1 << HARMONY_GAIN_HE_SHIFT)
#घोषणा HARMONY_GAIN_LE_SHIFT   26 /* line-out enabled */
#घोषणा HARMONY_GAIN_LE_MASK    (1 << HARMONY_GAIN_LE_SHIFT)
#घोषणा HARMONY_GAIN_SE_SHIFT   25 /* पूर्णांकernal-speaker enabled */
#घोषणा HARMONY_GAIN_SE_MASK    (1 << HARMONY_GAIN_SE_SHIFT)
#घोषणा HARMONY_GAIN_IS_SHIFT   24 /* input select - 0 क्रम line, 1 क्रम mic */
#घोषणा HARMONY_GAIN_IS_MASK    (1 << HARMONY_GAIN_IS_SHIFT)

/* monitor attenuation */
#घोषणा HARMONY_GAIN_MA         0x0f
#घोषणा HARMONY_GAIN_MA_SHIFT   20
#घोषणा HARMONY_GAIN_MA_MASK    (HARMONY_GAIN_MA << HARMONY_GAIN_MA_SHIFT)

/* input gain */
#घोषणा HARMONY_GAIN_IN         0x0f
#घोषणा HARMONY_GAIN_LI_SHIFT   16
#घोषणा HARMONY_GAIN_LI_MASK    (HARMONY_GAIN_IN << HARMONY_GAIN_LI_SHIFT)
#घोषणा HARMONY_GAIN_RI_SHIFT   12
#घोषणा HARMONY_GAIN_RI_MASK    (HARMONY_GAIN_IN << HARMONY_GAIN_RI_SHIFT)

/* output gain (master volume) */
#घोषणा HARMONY_GAIN_OUT        0x3f
#घोषणा HARMONY_GAIN_LO_SHIFT   6
#घोषणा HARMONY_GAIN_LO_MASK    (HARMONY_GAIN_OUT << HARMONY_GAIN_LO_SHIFT)
#घोषणा HARMONY_GAIN_RO_SHIFT   0
#घोषणा HARMONY_GAIN_RO_MASK    (HARMONY_GAIN_OUT << HARMONY_GAIN_RO_SHIFT)

#घोषणा HARMONY_MAX_OUT (HARMONY_GAIN_RO_MASK >> HARMONY_GAIN_RO_SHIFT)
#घोषणा HARMONY_MAX_IN  (HARMONY_GAIN_RI_MASK >> HARMONY_GAIN_RI_SHIFT)
#घोषणा HARMONY_MAX_MON (HARMONY_GAIN_MA_MASK >> HARMONY_GAIN_MA_SHIFT)

#घोषणा HARMONY_SR_8KHZ         0x08
#घोषणा HARMONY_SR_16KHZ        0x09
#घोषणा HARMONY_SR_27KHZ        0x0A
#घोषणा HARMONY_SR_32KHZ        0x0B
#घोषणा HARMONY_SR_48KHZ        0x0E
#घोषणा HARMONY_SR_9KHZ         0x0F
#घोषणा HARMONY_SR_5KHZ         0x10
#घोषणा HARMONY_SR_11KHZ        0x11
#घोषणा HARMONY_SR_18KHZ        0x12
#घोषणा HARMONY_SR_22KHZ        0x13
#घोषणा HARMONY_SR_37KHZ        0x14
#घोषणा HARMONY_SR_44KHZ        0x15
#घोषणा HARMONY_SR_33KHZ        0x16
#घोषणा HARMONY_SR_6KHZ         0x17

#पूर्ण_अगर /* __HARMONY_H__ */
