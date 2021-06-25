<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctatc.h
 *
 * @Brief
 * This file contains the definition of the device resource management object.
 *
 * @Author	Liu Chun
 * @Date 	Mar 28 2008
 */

#अगर_अघोषित CTATC_H
#घोषणा CTATC_H

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयr.h>
#समावेश <sound/core.h>

#समावेश "ctvmem.h"
#समावेश "cthardware.h"
#समावेश "ctresource.h"

क्रमागत CTALSADEVS अणु		/* Types of alsa devices */
	FRONT,
	SURROUND,
	CLFE,
	SIDE,
	IEC958,
	MIXER,
	NUM_CTALSADEVS		/* This should always be the last */
पूर्ण;

काष्ठा ct_atc_chip_sub_details अणु
	u16 subsys;
	स्थिर अक्षर *nm_model;
पूर्ण;

काष्ठा ct_atc_chip_details अणु
	u16 venकरोr;
	u16 device;
	स्थिर काष्ठा ct_atc_chip_sub_details *sub_details;
	स्थिर अक्षर *nm_card;
पूर्ण;

काष्ठा ct_atc;
काष्ठा ct_समयr;
काष्ठा ct_समयr_instance;

/* alsa pcm stream descriptor */
काष्ठा ct_atc_pcm अणु
	काष्ठा snd_pcm_substream *substream;
	व्योम (*पूर्णांकerrupt)(काष्ठा ct_atc_pcm *apcm);
	काष्ठा ct_समयr_instance *समयr;
	अचिन्हित पूर्णांक started:1;

	/* Only mono and पूर्णांकerleaved modes are supported now. */
	काष्ठा ct_vm_block *vm_block;
	व्योम *src;		/* SRC क्रम पूर्णांकeracting with host memory */
	व्योम **srccs;		/* SRCs क्रम sample rate conversion */
	व्योम **srcimps;		/* SRC Input Mappers */
	व्योम **amixers;		/* AMIXERs क्रम routing converted data */
	व्योम *mono;		/* A SUM resource क्रम mixing chs to one */
	अचिन्हित अक्षर n_srcc;	/* Number of converting SRCs */
	अचिन्हित अक्षर n_srcimp;	/* Number of SRC Input Mappers */
	अचिन्हित अक्षर n_amixer;	/* Number of AMIXERs */
पूर्ण;

/* Chip resource management object */
काष्ठा ct_atc अणु
	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक rsr; /* reference sample rate in Hz */
	अचिन्हित पूर्णांक msr; /* master sample rate in rsr */
	अचिन्हित पूर्णांक pll_rate; /* current rate of Phase Lock Loop */

	पूर्णांक chip_type;
	पूर्णांक model;
	स्थिर अक्षर *chip_name;
	स्थिर अक्षर *model_name;

	काष्ठा ct_vm *vm; /* device भव memory manager क्रम this card */
	पूर्णांक (*map_audio_buffer)(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);
	व्योम (*unmap_audio_buffer)(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);
	अचिन्हित दीर्घ (*get_ptp_phys)(काष्ठा ct_atc *atc, पूर्णांक index);

	काष्ठा mutex atc_mutex;

	पूर्णांक (*pcm_playback_prepare)(काष्ठा ct_atc *atc,
				    काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_playback_start)(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_playback_stop)(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_playback_position)(काष्ठा ct_atc *atc,
				     काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*spdअगर_passthru_playback_prepare)(काष्ठा ct_atc *atc,
					       काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_capture_prepare)(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_capture_start)(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_capture_stop)(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_capture_position)(काष्ठा ct_atc *atc,
				    काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*pcm_release_resources)(काष्ठा ct_atc *atc,
				     काष्ठा ct_atc_pcm *apcm);
	पूर्णांक (*select_line_in)(काष्ठा ct_atc *atc);
	पूर्णांक (*select_mic_in)(काष्ठा ct_atc *atc);
	पूर्णांक (*select_digit_io)(काष्ठा ct_atc *atc);
	पूर्णांक (*line_front_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*line_surround_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*line_clfe_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*line_rear_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*line_in_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*mic_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*spdअगर_out_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*spdअगर_in_unmute)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	पूर्णांक (*spdअगर_out_get_status)(काष्ठा ct_atc *atc, अचिन्हित पूर्णांक *status);
	पूर्णांक (*spdअगर_out_set_status)(काष्ठा ct_atc *atc, अचिन्हित पूर्णांक status);
	पूर्णांक (*spdअगर_out_passthru)(काष्ठा ct_atc *atc, अचिन्हित अक्षर state);
	काष्ठा capabilities (*capabilities)(काष्ठा ct_atc *atc);
	पूर्णांक (*output_चयन_get)(काष्ठा ct_atc *atc);
	पूर्णांक (*output_चयन_put)(काष्ठा ct_atc *atc, पूर्णांक position);
	पूर्णांक (*mic_source_चयन_get)(काष्ठा ct_atc *atc);
	पूर्णांक (*mic_source_चयन_put)(काष्ठा ct_atc *atc, पूर्णांक position);

	/* Don't touch! Used क्रम पूर्णांकernal object. */
	व्योम *rsc_mgrs[NUM_RSCTYP]; /* chip resource managers */
	व्योम *mixer;		/* पूर्णांकernal mixer object */
	काष्ठा hw *hw;		/* chip specअगरic hardware access object */
	व्योम **daios;		/* digital audio io resources */
	व्योम **pcm;		/* SUMs क्रम collecting all pcm stream */
	व्योम **srcs;		/* Sample Rate Converters क्रम input संकेत */
	व्योम **srcimps;		/* input mappers क्रम SRCs */
	अचिन्हित अक्षर n_daio;
	अचिन्हित अक्षर n_src;
	अचिन्हित अक्षर n_srcimp;
	अचिन्हित अक्षर n_pcm;

	काष्ठा ct_समयr *समयr;

#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक (*suspend)(काष्ठा ct_atc *atc);
	पूर्णांक (*resume)(काष्ठा ct_atc *atc);
#घोषणा NUM_PCMS (NUM_CTALSADEVS - 1)
	काष्ठा snd_pcm *pcms[NUM_PCMS];
#पूर्ण_अगर
पूर्ण;


पूर्णांक ct_atc_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
		  अचिन्हित पूर्णांक rsr, अचिन्हित पूर्णांक msr, पूर्णांक chip_type,
		  अचिन्हित पूर्णांक subsysid, काष्ठा ct_atc **ratc);
पूर्णांक ct_atc_create_alsa_devs(काष्ठा ct_atc *atc);

#पूर्ण_अगर /* CTATC_H */
