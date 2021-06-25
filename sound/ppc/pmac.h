<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम PowerMac onboard soundchips
 * Copyright (c) 2001 by Takashi Iwai <tiwai@suse.de>
 *   based on dmasound.c.
 */


#अगर_अघोषित __PMAC_H
#घोषणा __PMAC_H

#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश "awacs.h"

#समावेश <linux/adb.h>
#अगर_घोषित CONFIG_ADB_CUDA
#समावेश <linux/cuda.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
#समावेश <linux/pmu.h>
#पूर्ण_अगर
#समावेश <linux/nvram.h>
#समावेश <linux/tty.h>
#समावेश <linux/vt_kern.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>

/* maximum number of fragments */
#घोषणा PMAC_MAX_FRAGS		32


#घोषणा PMAC_SUPPORT_AUTOMUTE

/*
 * DBDMA space
 */
काष्ठा pmac_dbdma अणु
	dma_addr_t dma_base;
	dma_addr_t addr;
	काष्ठा dbdma_cmd __iomem *cmds;
	व्योम *space;
	पूर्णांक size;
पूर्ण;

/*
 * playback/capture stream
 */
काष्ठा pmac_stream अणु
	पूर्णांक running;	/* boolean */

	पूर्णांक stream;	/* PLAYBACK/CAPTURE */

	पूर्णांक dma_size; /* in bytes */
	पूर्णांक period_size; /* in bytes */
	पूर्णांक buffer_size; /* in kbytes */
	पूर्णांक nperiods, cur_period;

	काष्ठा pmac_dbdma cmd;
	अस्थिर काष्ठा dbdma_regs __iomem *dma;

	काष्ठा snd_pcm_substream *substream;

	अचिन्हित पूर्णांक cur_freqs;		/* currently available frequencies */
	अचिन्हित पूर्णांक cur_क्रमmats;	/* currently available क्रमmats */
पूर्ण;


/*
 */

क्रमागत snd_pmac_model अणु
	PMAC_AWACS, PMAC_SCREAMER, PMAC_BURGUNDY, PMAC_DACA, PMAC_TUMBLER,
	PMAC_SNAPPER
पूर्ण;

काष्ठा snd_pmac अणु
	काष्ठा snd_card *card;

	/* h/w info */
	काष्ठा device_node *node;
	काष्ठा pci_dev *pdev;
	अचिन्हित पूर्णांक revision;
	अचिन्हित पूर्णांक manufacturer;
	अचिन्हित पूर्णांक subframe;
	अचिन्हित पूर्णांक device_id;
	क्रमागत snd_pmac_model model;

	अचिन्हित पूर्णांक has_iic : 1;
	अचिन्हित पूर्णांक is_pbook_3400 : 1;
	अचिन्हित पूर्णांक is_pbook_G3 : 1;
	अचिन्हित पूर्णांक is_k2 : 1;

	अचिन्हित पूर्णांक can_byte_swap : 1;
	अचिन्हित पूर्णांक can_duplex : 1;
	अचिन्हित पूर्णांक can_capture : 1;

	अचिन्हित पूर्णांक स्वतः_mute : 1;
	अचिन्हित पूर्णांक initialized : 1;
	अचिन्हित पूर्णांक feature_is_set : 1;

	अचिन्हित पूर्णांक requested;
	काष्ठा resource rsrc[3];

	पूर्णांक num_freqs;
	स्थिर पूर्णांक *freq_table;
	अचिन्हित पूर्णांक freqs_ok;		/* bit flags */
	अचिन्हित पूर्णांक क्रमmats_ok;	/* pcm hwinfo */
	पूर्णांक active;
	पूर्णांक rate_index;
	पूर्णांक क्रमmat;			/* current क्रमmat */

	spinlock_t reg_lock;
	अस्थिर काष्ठा awacs_regs __iomem *awacs;
	पूर्णांक awacs_reg[8]; /* रेजिस्टर cache */
	अचिन्हित पूर्णांक hp_stat_mask;

	अचिन्हित अक्षर __iomem *latch_base;
	अचिन्हित अक्षर __iomem *macio_base;

	काष्ठा pmac_stream playback;
	काष्ठा pmac_stream capture;

	काष्ठा pmac_dbdma extra_dma;

	पूर्णांक irq, tx_irq, rx_irq;

	काष्ठा snd_pcm *pcm;

	काष्ठा pmac_beep *beep;

	अचिन्हित पूर्णांक control_mask;	/* control mask */

	/* mixer stuffs */
	व्योम *mixer_data;
	व्योम (*mixer_मुक्त)(काष्ठा snd_pmac *);
	काष्ठा snd_kcontrol *master_sw_ctl;
	काष्ठा snd_kcontrol *speaker_sw_ctl;
	काष्ठा snd_kcontrol *drc_sw_ctl;	/* only used क्रम tumbler -ReneR */
	काष्ठा snd_kcontrol *hp_detect_ctl;
	काष्ठा snd_kcontrol *lineout_sw_ctl;

	/* lowlevel callbacks */
	व्योम (*set_क्रमmat)(काष्ठा snd_pmac *chip);
	व्योम (*update_स्वतःmute)(काष्ठा snd_pmac *chip, पूर्णांक करो_notअगरy);
	पूर्णांक (*detect_headphone)(काष्ठा snd_pmac *chip);
#अगर_घोषित CONFIG_PM
	व्योम (*suspend)(काष्ठा snd_pmac *chip);
	व्योम (*resume)(काष्ठा snd_pmac *chip);
#पूर्ण_अगर

पूर्ण;


/* exported functions */
पूर्णांक snd_pmac_new(काष्ठा snd_card *card, काष्ठा snd_pmac **chip_वापस);
पूर्णांक snd_pmac_pcm_new(काष्ठा snd_pmac *chip);
पूर्णांक snd_pmac_attach_beep(काष्ठा snd_pmac *chip);
व्योम snd_pmac_detach_beep(काष्ठा snd_pmac *chip);
व्योम snd_pmac_beep_stop(काष्ठा snd_pmac *chip);
अचिन्हित पूर्णांक snd_pmac_rate_index(काष्ठा snd_pmac *chip, काष्ठा pmac_stream *rec, अचिन्हित पूर्णांक rate);

व्योम snd_pmac_beep_dma_start(काष्ठा snd_pmac *chip, पूर्णांक bytes, अचिन्हित दीर्घ addr, पूर्णांक speed);
व्योम snd_pmac_beep_dma_stop(काष्ठा snd_pmac *chip);

#अगर_घोषित CONFIG_PM
व्योम snd_pmac_suspend(काष्ठा snd_pmac *chip);
व्योम snd_pmac_resume(काष्ठा snd_pmac *chip);
#पूर्ण_अगर

/* initialize mixer */
पूर्णांक snd_pmac_awacs_init(काष्ठा snd_pmac *chip);
पूर्णांक snd_pmac_burgundy_init(काष्ठा snd_pmac *chip);
पूर्णांक snd_pmac_daca_init(काष्ठा snd_pmac *chip);
पूर्णांक snd_pmac_tumbler_init(काष्ठा snd_pmac *chip);
पूर्णांक snd_pmac_tumbler_post_init(व्योम);

/* i2c functions */
काष्ठा pmac_keywest अणु
	पूर्णांक addr;
	काष्ठा i2c_client *client;
	पूर्णांक id;
	पूर्णांक (*init_client)(काष्ठा pmac_keywest *i2c);
	अक्षर *name;
पूर्ण;

पूर्णांक snd_pmac_keywest_init(काष्ठा pmac_keywest *i2c);
व्योम snd_pmac_keywest_cleanup(काष्ठा pmac_keywest *i2c);

/* misc */
#घोषणा snd_pmac_boolean_stereo_info	snd_ctl_boolean_stereo_info
#घोषणा snd_pmac_boolean_mono_info	snd_ctl_boolean_mono_info

पूर्णांक snd_pmac_add_स्वतःmute(काष्ठा snd_pmac *chip);

#पूर्ण_अगर /* __PMAC_H */
