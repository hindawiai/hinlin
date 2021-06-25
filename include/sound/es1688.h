<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_ES1688_H
#घोषणा __SOUND_ES1688_H

/*
 *  Header file क्रम ES488/ES1688
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा ES1688_HW_AUTO		0x0000
#घोषणा ES1688_HW_688		0x0001
#घोषणा ES1688_HW_1688		0x0002
#घोषणा ES1688_HW_UNDEF	0x0003

काष्ठा snd_es1688 अणु
	अचिन्हित दीर्घ port;		/* port of ESS chip */
	काष्ठा resource *res_port;
	अचिन्हित दीर्घ mpu_port;		/* MPU-401 port of ESS chip */
	पूर्णांक irq;			/* IRQ number of ESS chip */
	पूर्णांक mpu_irq;			/* MPU IRQ */
	पूर्णांक dma8;			/* 8-bit DMA */
	अचिन्हित लघु version;		/* version of ESS chip */
	अचिन्हित लघु hardware;	/* see to ES1688_HW_XXXX */

	अचिन्हित लघु trigger_value;
	अचिन्हित अक्षर pad;
	अचिन्हित पूर्णांक dma_size;

	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;

	spinlock_t reg_lock;
	spinlock_t mixer_lock;
पूर्ण;

/* I/O ports */

#घोषणा ES1688P(codec, x) ((codec)->port + e_s_s_ESS1688##x)

#घोषणा e_s_s_ESS1688RESET	0x6
#घोषणा e_s_s_ESS1688READ	0xa
#घोषणा e_s_s_ESS1688WRITE	0xc
#घोषणा e_s_s_ESS1688COMMAND	0xc
#घोषणा e_s_s_ESS1688STATUS	0xc
#घोषणा e_s_s_ESS1688DATA_AVAIL	0xe
#घोषणा e_s_s_ESS1688DATA_AVAIL_16 0xf
#घोषणा e_s_s_ESS1688MIXER_ADDR	0x4
#घोषणा e_s_s_ESS1688MIXER_DATA	0x5
#घोषणा e_s_s_ESS1688OPL3_LEFT	0x0
#घोषणा e_s_s_ESS1688OPL3_RIGHT	0x2
#घोषणा e_s_s_ESS1688OPL3_BOTH	0x8
#घोषणा e_s_s_ESS1688ENABLE0	0x0
#घोषणा e_s_s_ESS1688ENABLE1	0x9
#घोषणा e_s_s_ESS1688ENABLE2	0xb
#घोषणा e_s_s_ESS1688INIT1	0x7

#घोषणा ES1688_DSP_CMD_DMAOFF	0xd0
#घोषणा ES1688_DSP_CMD_SPKON	0xd1
#घोषणा ES1688_DSP_CMD_SPKOFF	0xd3
#घोषणा ES1688_DSP_CMD_DMAON	0xd4

#घोषणा ES1688_PCM_DEV		0x14
#घोषणा ES1688_MIC_DEV		0x1a
#घोषणा ES1688_REC_DEV		0x1c
#घोषणा ES1688_MASTER_DEV	0x32
#घोषणा ES1688_FM_DEV		0x36
#घोषणा ES1688_CD_DEV		0x38
#घोषणा ES1688_AUX_DEV		0x3a
#घोषणा ES1688_SPEAKER_DEV	0x3c
#घोषणा ES1688_LINE_DEV		0x3e
#घोषणा ES1688_RECLEV_DEV	0xb4

#घोषणा ES1688_MIXS_MASK	0x17
#घोषणा ES1688_MIXS_MIC		0x00
#घोषणा ES1688_MIXS_MIC_MASTER	0x01
#घोषणा ES1688_MIXS_CD		0x02
#घोषणा ES1688_MIXS_AOUT	0x03
#घोषणा ES1688_MIXS_MIC1	0x04
#घोषणा ES1688_MIXS_REC_MIX	0x05
#घोषणा ES1688_MIXS_LINE	0x06
#घोषणा ES1688_MIXS_MASTER	0x07
#घोषणा ES1688_MIXS_MUTE	0x10

/*

 */

व्योम snd_es1688_mixer_ग_लिखो(काष्ठा snd_es1688 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर data);

पूर्णांक snd_es1688_create(काष्ठा snd_card *card,
		      काष्ठा snd_es1688 *chip,
		      अचिन्हित दीर्घ port,
		      अचिन्हित दीर्घ mpu_port,
		      पूर्णांक irq,
		      पूर्णांक mpu_irq,
		      पूर्णांक dma8,
		      अचिन्हित लघु hardware);
पूर्णांक snd_es1688_pcm(काष्ठा snd_card *card, काष्ठा snd_es1688 *chip, पूर्णांक device);
पूर्णांक snd_es1688_mixer(काष्ठा snd_card *card, काष्ठा snd_es1688 *chip);
पूर्णांक snd_es1688_reset(काष्ठा snd_es1688 *chip);

#पूर्ण_अगर /* __SOUND_ES1688_H */
