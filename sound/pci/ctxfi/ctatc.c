<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File    ctatc.c
 *
 * @Brief
 * This file contains the implementation of the device resource management
 * object.
 *
 * @Author Liu Chun
 * @Date Mar 28 2008
 */

#समावेश "ctatc.h"
#समावेश "ctpcm.h"
#समावेश "ctmixer.h"
#समावेश "ctsrc.h"
#समावेश "ctamixer.h"
#समावेश "ctdaio.h"
#समावेश "cttimer.h"
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>
#समावेश <sound/asoundef.h>

#घोषणा MONO_SUM_SCALE	0x19a8	/* 2^(-0.5) in 14-bit भग्नing क्रमmat */
#घोषणा MAX_MULTI_CHN	8

#घोषणा IEC958_DEFAULT_CON ((IEC958_AES0_NONAUDIO \
			    | IEC958_AES0_CON_NOT_COPYRIGHT) \
			    | ((IEC958_AES1_CON_MIXER \
			    | IEC958_AES1_CON_ORIGINAL) << 8) \
			    | (0x10 << 16) \
			    | ((IEC958_AES3_CON_FS_48000) << 24))

अटल स्थिर काष्ठा snd_pci_quirk subsys_20k1_list[] = अणु
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, 0x0022, "SB055x", CTSB055X),
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, 0x002f, "SB055x", CTSB055X),
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, 0x0029, "SB073x", CTSB073X),
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, 0x0031, "SB073x", CTSB073X),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_CREATIVE, 0xf000, 0x6000,
			   "UAA", CTUAA),
	अणु पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk subsys_20k2_list[] = अणु
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, PCI_SUBDEVICE_ID_CREATIVE_SB0760,
		      "SB0760", CTSB0760),
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, PCI_SUBDEVICE_ID_CREATIVE_SB1270,
		      "SB1270", CTSB1270),
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, PCI_SUBDEVICE_ID_CREATIVE_SB08801,
		      "SB0880", CTSB0880),
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, PCI_SUBDEVICE_ID_CREATIVE_SB08802,
		      "SB0880", CTSB0880),
	SND_PCI_QUIRK(PCI_VENDOR_ID_CREATIVE, PCI_SUBDEVICE_ID_CREATIVE_SB08803,
		      "SB0880", CTSB0880),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_CREATIVE, 0xf000,
			   PCI_SUBDEVICE_ID_CREATIVE_HENDRIX, "HENDRIX",
			   CTHENDRIX),
	अणु पूर्ण /* terminator */
पूर्ण;

अटल स्थिर अक्षर *ct_subsys_name[NUM_CTCARDS] = अणु
	/* 20k1 models */
	[CTSB055X]	= "SB055x",
	[CTSB073X]	= "SB073x",
	[CTUAA]		= "UAA",
	[CT20K1_UNKNOWN] = "Unknown",
	/* 20k2 models */
	[CTSB0760]	= "SB076x",
	[CTHENDRIX]	= "Hendrix",
	[CTSB0880]	= "SB0880",
	[CTSB1270]      = "SB1270",
	[CT20K2_UNKNOWN] = "Unknown",
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक (*create)(काष्ठा ct_atc *atc,
			क्रमागत CTALSADEVS device, स्थिर अक्षर *device_name);
	पूर्णांक (*destroy)(व्योम *alsa_dev);
	स्थिर अक्षर *खुला_name;
पूर्ण alsa_dev_funcs[NUM_CTALSADEVS] = अणु
	[FRONT]		= अणु .create = ct_alsa_pcm_create,
			    .destroy = शून्य,
			    .खुला_name = "Front/WaveIn"पूर्ण,
	[SURROUND]	= अणु .create = ct_alsa_pcm_create,
			    .destroy = शून्य,
			    .खुला_name = "Surround"पूर्ण,
	[CLFE]		= अणु .create = ct_alsa_pcm_create,
			    .destroy = शून्य,
			    .खुला_name = "Center/LFE"पूर्ण,
	[SIDE]		= अणु .create = ct_alsa_pcm_create,
			    .destroy = शून्य,
			    .खुला_name = "Side"पूर्ण,
	[IEC958]	= अणु .create = ct_alsa_pcm_create,
			    .destroy = शून्य,
			    .खुला_name = "IEC958 Non-audio"पूर्ण,

	[MIXER]		= अणु .create = ct_alsa_mix_create,
			    .destroy = शून्य,
			    .खुला_name = "Mixer"पूर्ण
पूर्ण;

प्रकार पूर्णांक (*create_t)(काष्ठा hw *, व्योम **);
प्रकार पूर्णांक (*destroy_t)(व्योम *);

अटल काष्ठा अणु
	पूर्णांक (*create)(काष्ठा hw *hw, व्योम **rmgr);
	पूर्णांक (*destroy)(व्योम *mgr);
पूर्ण rsc_mgr_funcs[NUM_RSCTYP] = अणु
	[SRC] 		= अणु .create 	= (create_t)src_mgr_create,
			    .destroy 	= (destroy_t)src_mgr_destroy	पूर्ण,
	[SRCIMP] 	= अणु .create 	= (create_t)srcimp_mgr_create,
			    .destroy 	= (destroy_t)srcimp_mgr_destroy	पूर्ण,
	[AMIXER]	= अणु .create	= (create_t)amixer_mgr_create,
			    .destroy	= (destroy_t)amixer_mgr_destroy	पूर्ण,
	[SUM]		= अणु .create	= (create_t)sum_mgr_create,
			    .destroy	= (destroy_t)sum_mgr_destroy	पूर्ण,
	[DAIO]		= अणु .create	= (create_t)daio_mgr_create,
			    .destroy	= (destroy_t)daio_mgr_destroy	पूर्ण
पूर्ण;

अटल पूर्णांक
atc_pcm_release_resources(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm);

/* *
 * Only mono and पूर्णांकerleaved modes are supported now.
 * Always allocates a contiguous channel block.
 * */

अटल पूर्णांक ct_map_audio_buffer(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा ct_vm *vm;

	अगर (!apcm->substream)
		वापस 0;

	runसमय = apcm->substream->runसमय;
	vm = atc->vm;

	apcm->vm_block = vm->map(vm, apcm->substream, runसमय->dma_bytes);

	अगर (!apcm->vm_block)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल व्योम ct_unmap_audio_buffer(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा ct_vm *vm;

	अगर (!apcm->vm_block)
		वापस;

	vm = atc->vm;

	vm->unmap(vm, apcm->vm_block);

	apcm->vm_block = शून्य;
पूर्ण

अटल अचिन्हित दीर्घ atc_get_ptp_phys(काष्ठा ct_atc *atc, पूर्णांक index)
अणु
	वापस atc->vm->get_ptp_phys(atc->vm, index);
पूर्ण

अटल अचिन्हित पूर्णांक convert_क्रमmat(snd_pcm_क्रमmat_t snd_क्रमmat,
				   काष्ठा snd_card *card)
अणु
	चयन (snd_क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_U8:
		वापस SRC_SF_U8;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		वापस SRC_SF_S16;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		वापस SRC_SF_S24;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		वापस SRC_SF_S32;
	हाल SNDRV_PCM_FORMAT_FLOAT_LE:
		वापस SRC_SF_F32;
	शेष:
		dev_err(card->dev, "not recognized snd format is %d\n",
			snd_क्रमmat);
		वापस SRC_SF_S16;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
atc_get_pitch(अचिन्हित पूर्णांक input_rate, अचिन्हित पूर्णांक output_rate)
अणु
	अचिन्हित पूर्णांक pitch;
	पूर्णांक b;

	/* get pitch and convert to fixed-poपूर्णांक 8.24 क्रमmat. */
	pitch = (input_rate / output_rate) << 24;
	input_rate %= output_rate;
	input_rate /= 100;
	output_rate /= 100;
	क्रम (b = 31; ((b >= 0) && !(input_rate >> b)); )
		b--;

	अगर (b >= 0) अणु
		input_rate <<= (31 - b);
		input_rate /= output_rate;
		b = 24 - (31 - b);
		अगर (b >= 0)
			input_rate <<= b;
		अन्यथा
			input_rate >>= -b;

		pitch |= input_rate;
	पूर्ण

	वापस pitch;
पूर्ण

अटल पूर्णांक select_rom(अचिन्हित पूर्णांक pitch)
अणु
	अगर (pitch > 0x00428f5c && pitch < 0x01b851ec) अणु
		/* 0.26 <= pitch <= 1.72 */
		वापस 1;
	पूर्ण अन्यथा अगर (pitch == 0x01d66666 || pitch == 0x01d66667) अणु
		/* pitch == 1.8375 */
		वापस 2;
	पूर्ण अन्यथा अगर (pitch == 0x02000000) अणु
		/* pitch == 2 */
		वापस 3;
	पूर्ण अन्यथा अगर (pitch <= 0x08000000) अणु
		/* 0 <= pitch <= 8 */
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल पूर्णांक atc_pcm_playback_prepare(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	काष्ठा amixer_mgr *amixer_mgr = atc->rsc_mgrs[AMIXER];
	काष्ठा src_desc desc = अणु0पूर्ण;
	काष्ठा amixer_desc mix_dsc = अणु0पूर्ण;
	काष्ठा src *src;
	काष्ठा amixer *amixer;
	पूर्णांक err;
	पूर्णांक n_amixer = apcm->substream->runसमय->channels, i = 0;
	पूर्णांक device = apcm->substream->pcm->device;
	अचिन्हित पूर्णांक pitch;

	/* first release old resources */
	atc_pcm_release_resources(atc, apcm);

	/* Get SRC resource */
	desc.multi = apcm->substream->runसमय->channels;
	desc.msr = atc->msr;
	desc.mode = MEMRD;
	err = src_mgr->get_src(src_mgr, &desc, (काष्ठा src **)&apcm->src);
	अगर (err)
		जाओ error1;

	pitch = atc_get_pitch(apcm->substream->runसमय->rate,
						(atc->rsr * atc->msr));
	src = apcm->src;
	src->ops->set_pitch(src, pitch);
	src->ops->set_rom(src, select_rom(pitch));
	src->ops->set_sf(src, convert_क्रमmat(apcm->substream->runसमय->क्रमmat,
					     atc->card));
	src->ops->set_pm(src, (src->ops->next_पूर्णांकerleave(src) != शून्य));

	/* Get AMIXER resource */
	n_amixer = (n_amixer < 2) ? 2 : n_amixer;
	apcm->amixers = kसुस्मृति(n_amixer, माप(व्योम *), GFP_KERNEL);
	अगर (!apcm->amixers) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण
	mix_dsc.msr = atc->msr;
	क्रम (i = 0, apcm->n_amixer = 0; i < n_amixer; i++) अणु
		err = amixer_mgr->get_amixer(amixer_mgr, &mix_dsc,
					(काष्ठा amixer **)&apcm->amixers[i]);
		अगर (err)
			जाओ error1;

		apcm->n_amixer++;
	पूर्ण

	/* Set up device भव mem map */
	err = ct_map_audio_buffer(atc, apcm);
	अगर (err < 0)
		जाओ error1;

	/* Connect resources */
	src = apcm->src;
	क्रम (i = 0; i < n_amixer; i++) अणु
		amixer = apcm->amixers[i];
		mutex_lock(&atc->atc_mutex);
		amixer->ops->setup(amixer, &src->rsc,
					INIT_VOL, atc->pcm[i+device*2]);
		mutex_unlock(&atc->atc_mutex);
		src = src->ops->next_पूर्णांकerleave(src);
		अगर (!src)
			src = apcm->src;
	पूर्ण

	ct_समयr_prepare(apcm->समयr);

	वापस 0;

error1:
	atc_pcm_release_resources(atc, apcm);
	वापस err;
पूर्ण

अटल पूर्णांक
atc_pcm_release_resources(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	काष्ठा srcimp_mgr *srcimp_mgr = atc->rsc_mgrs[SRCIMP];
	काष्ठा amixer_mgr *amixer_mgr = atc->rsc_mgrs[AMIXER];
	काष्ठा sum_mgr *sum_mgr = atc->rsc_mgrs[SUM];
	काष्ठा srcimp *srcimp;
	पूर्णांक i;

	अगर (apcm->srcimps) अणु
		क्रम (i = 0; i < apcm->n_srcimp; i++) अणु
			srcimp = apcm->srcimps[i];
			srcimp->ops->unmap(srcimp);
			srcimp_mgr->put_srcimp(srcimp_mgr, srcimp);
			apcm->srcimps[i] = शून्य;
		पूर्ण
		kमुक्त(apcm->srcimps);
		apcm->srcimps = शून्य;
	पूर्ण

	अगर (apcm->srccs) अणु
		क्रम (i = 0; i < apcm->n_srcc; i++) अणु
			src_mgr->put_src(src_mgr, apcm->srccs[i]);
			apcm->srccs[i] = शून्य;
		पूर्ण
		kमुक्त(apcm->srccs);
		apcm->srccs = शून्य;
	पूर्ण

	अगर (apcm->amixers) अणु
		क्रम (i = 0; i < apcm->n_amixer; i++) अणु
			amixer_mgr->put_amixer(amixer_mgr, apcm->amixers[i]);
			apcm->amixers[i] = शून्य;
		पूर्ण
		kमुक्त(apcm->amixers);
		apcm->amixers = शून्य;
	पूर्ण

	अगर (apcm->mono) अणु
		sum_mgr->put_sum(sum_mgr, apcm->mono);
		apcm->mono = शून्य;
	पूर्ण

	अगर (apcm->src) अणु
		src_mgr->put_src(src_mgr, apcm->src);
		apcm->src = शून्य;
	पूर्ण

	अगर (apcm->vm_block) अणु
		/* Unकरो device भव mem map */
		ct_unmap_audio_buffer(atc, apcm);
		apcm->vm_block = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atc_pcm_playback_start(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	अचिन्हित पूर्णांक max_cisz;
	काष्ठा src *src = apcm->src;

	अगर (apcm->started)
		वापस 0;
	apcm->started = 1;

	max_cisz = src->multi * src->rsc.msr;
	max_cisz = 0x80 * (max_cisz < 8 ? max_cisz : 8);

	src->ops->set_sa(src, apcm->vm_block->addr);
	src->ops->set_la(src, apcm->vm_block->addr + apcm->vm_block->size);
	src->ops->set_ca(src, apcm->vm_block->addr + max_cisz);
	src->ops->set_cisz(src, max_cisz);

	src->ops->set_bm(src, 1);
	src->ops->set_state(src, SRC_STATE_INIT);
	src->ops->commit_ग_लिखो(src);

	ct_समयr_start(apcm->समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक atc_pcm_stop(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src *src;
	पूर्णांक i;

	ct_समयr_stop(apcm->समयr);

	src = apcm->src;
	src->ops->set_bm(src, 0);
	src->ops->set_state(src, SRC_STATE_OFF);
	src->ops->commit_ग_लिखो(src);

	अगर (apcm->srccs) अणु
		क्रम (i = 0; i < apcm->n_srcc; i++) अणु
			src = apcm->srccs[i];
			src->ops->set_bm(src, 0);
			src->ops->set_state(src, SRC_STATE_OFF);
			src->ops->commit_ग_लिखो(src);
		पूर्ण
	पूर्ण

	apcm->started = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
atc_pcm_playback_position(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src *src = apcm->src;
	u32 size, max_cisz;
	पूर्णांक position;

	अगर (!src)
		वापस 0;
	position = src->ops->get_ca(src);

	अगर (position < apcm->vm_block->addr) अणु
		dev_dbg(atc->card->dev,
			"bad ca - ca=0x%08x, vba=0x%08x, vbs=0x%08x\n",
			position, apcm->vm_block->addr, apcm->vm_block->size);
		position = apcm->vm_block->addr;
	पूर्ण

	size = apcm->vm_block->size;
	max_cisz = src->multi * src->rsc.msr;
	max_cisz = 128 * (max_cisz < 8 ? max_cisz : 8);

	वापस (position + size - max_cisz - apcm->vm_block->addr) % size;
पूर्ण

काष्ठा src_node_conf_t अणु
	अचिन्हित पूर्णांक pitch;
	अचिन्हित पूर्णांक msr:8;
	अचिन्हित पूर्णांक mix_msr:8;
	अचिन्हित पूर्णांक imp_msr:8;
	अचिन्हित पूर्णांक vo:1;
पूर्ण;

अटल व्योम setup_src_node_conf(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm,
				काष्ठा src_node_conf_t *conf, पूर्णांक *n_srcc)
अणु
	अचिन्हित पूर्णांक pitch;

	/* get pitch and convert to fixed-poपूर्णांक 8.24 क्रमmat. */
	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runसमय->rate);
	*n_srcc = 0;

	अगर (1 == atc->msr) अणु /* FIXME: करो we really need SRC here अगर pitch==1 */
		*n_srcc = apcm->substream->runसमय->channels;
		conf[0].pitch = pitch;
		conf[0].mix_msr = conf[0].imp_msr = conf[0].msr = 1;
		conf[0].vo = 1;
	पूर्ण अन्यथा अगर (2 <= atc->msr) अणु
		अगर (0x8000000 < pitch) अणु
			/* Need two-stage SRCs, SRCIMPs and
			 * AMIXERs क्रम converting क्रमmat */
			conf[0].pitch = (atc->msr << 24);
			conf[0].msr = conf[0].mix_msr = 1;
			conf[0].imp_msr = atc->msr;
			conf[0].vo = 0;
			conf[1].pitch = atc_get_pitch(atc->rsr,
					apcm->substream->runसमय->rate);
			conf[1].msr = conf[1].mix_msr = conf[1].imp_msr = 1;
			conf[1].vo = 1;
			*n_srcc = apcm->substream->runसमय->channels * 2;
		पूर्ण अन्यथा अगर (0x1000000 < pitch) अणु
			/* Need one-stage SRCs, SRCIMPs and
			 * AMIXERs क्रम converting क्रमmat */
			conf[0].pitch = pitch;
			conf[0].msr = conf[0].mix_msr
				    = conf[0].imp_msr = atc->msr;
			conf[0].vo = 1;
			*n_srcc = apcm->substream->runसमय->channels;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
atc_pcm_capture_get_resources(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	काष्ठा srcimp_mgr *srcimp_mgr = atc->rsc_mgrs[SRCIMP];
	काष्ठा amixer_mgr *amixer_mgr = atc->rsc_mgrs[AMIXER];
	काष्ठा sum_mgr *sum_mgr = atc->rsc_mgrs[SUM];
	काष्ठा src_desc src_dsc = अणु0पूर्ण;
	काष्ठा src *src;
	काष्ठा srcimp_desc srcimp_dsc = अणु0पूर्ण;
	काष्ठा srcimp *srcimp;
	काष्ठा amixer_desc mix_dsc = अणु0पूर्ण;
	काष्ठा sum_desc sum_dsc = अणु0पूर्ण;
	अचिन्हित पूर्णांक pitch;
	पूर्णांक multi, err, i;
	पूर्णांक n_srcimp, n_amixer, n_srcc, n_sum;
	काष्ठा src_node_conf_t src_node_conf[2] = अणुअणु0पूर्ण पूर्ण;

	/* first release old resources */
	atc_pcm_release_resources(atc, apcm);

	/* The numbers of converting SRCs and SRCIMPs should be determined
	 * by pitch value. */

	multi = apcm->substream->runसमय->channels;

	/* get pitch and convert to fixed-poपूर्णांक 8.24 क्रमmat. */
	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runसमय->rate);

	setup_src_node_conf(atc, apcm, src_node_conf, &n_srcc);
	n_sum = (1 == multi) ? 1 : 0;
	n_amixer = n_sum * 2 + n_srcc;
	n_srcimp = n_srcc;
	अगर ((multi > 1) && (0x8000000 >= pitch)) अणु
		/* Need extra AMIXERs and SRCIMPs क्रम special treaपंचांगent
		 * of पूर्णांकerleaved recording of conjugate channels */
		n_amixer += multi * atc->msr;
		n_srcimp += multi * atc->msr;
	पूर्ण अन्यथा अणु
		n_srcimp += multi;
	पूर्ण

	अगर (n_srcc) अणु
		apcm->srccs = kसुस्मृति(n_srcc, माप(व्योम *), GFP_KERNEL);
		अगर (!apcm->srccs)
			वापस -ENOMEM;
	पूर्ण
	अगर (n_amixer) अणु
		apcm->amixers = kसुस्मृति(n_amixer, माप(व्योम *), GFP_KERNEL);
		अगर (!apcm->amixers) अणु
			err = -ENOMEM;
			जाओ error1;
		पूर्ण
	पूर्ण
	apcm->srcimps = kसुस्मृति(n_srcimp, माप(व्योम *), GFP_KERNEL);
	अगर (!apcm->srcimps) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण

	/* Allocate SRCs क्रम sample rate conversion अगर needed */
	src_dsc.multi = 1;
	src_dsc.mode = ARCRW;
	क्रम (i = 0, apcm->n_srcc = 0; i < n_srcc; i++) अणु
		src_dsc.msr = src_node_conf[i/multi].msr;
		err = src_mgr->get_src(src_mgr, &src_dsc,
					(काष्ठा src **)&apcm->srccs[i]);
		अगर (err)
			जाओ error1;

		src = apcm->srccs[i];
		pitch = src_node_conf[i/multi].pitch;
		src->ops->set_pitch(src, pitch);
		src->ops->set_rom(src, select_rom(pitch));
		src->ops->set_vo(src, src_node_conf[i/multi].vo);

		apcm->n_srcc++;
	पूर्ण

	/* Allocate AMIXERs क्रम routing SRCs of conversion अगर needed */
	क्रम (i = 0, apcm->n_amixer = 0; i < n_amixer; i++) अणु
		अगर (i < (n_sum*2))
			mix_dsc.msr = atc->msr;
		अन्यथा अगर (i < (n_sum*2+n_srcc))
			mix_dsc.msr = src_node_conf[(i-n_sum*2)/multi].mix_msr;
		अन्यथा
			mix_dsc.msr = 1;

		err = amixer_mgr->get_amixer(amixer_mgr, &mix_dsc,
					(काष्ठा amixer **)&apcm->amixers[i]);
		अगर (err)
			जाओ error1;

		apcm->n_amixer++;
	पूर्ण

	/* Allocate a SUM resource to mix all input channels together */
	sum_dsc.msr = atc->msr;
	err = sum_mgr->get_sum(sum_mgr, &sum_dsc, (काष्ठा sum **)&apcm->mono);
	अगर (err)
		जाओ error1;

	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runसमय->rate);
	/* Allocate SRCIMP resources */
	क्रम (i = 0, apcm->n_srcimp = 0; i < n_srcimp; i++) अणु
		अगर (i < (n_srcc))
			srcimp_dsc.msr = src_node_conf[i/multi].imp_msr;
		अन्यथा अगर (1 == multi)
			srcimp_dsc.msr = (pitch <= 0x8000000) ? atc->msr : 1;
		अन्यथा
			srcimp_dsc.msr = 1;

		err = srcimp_mgr->get_srcimp(srcimp_mgr, &srcimp_dsc, &srcimp);
		अगर (err)
			जाओ error1;

		apcm->srcimps[i] = srcimp;
		apcm->n_srcimp++;
	पूर्ण

	/* Allocate a SRC क्रम writing data to host memory */
	src_dsc.multi = apcm->substream->runसमय->channels;
	src_dsc.msr = 1;
	src_dsc.mode = MEMWR;
	err = src_mgr->get_src(src_mgr, &src_dsc, (काष्ठा src **)&apcm->src);
	अगर (err)
		जाओ error1;

	src = apcm->src;
	src->ops->set_pitch(src, pitch);

	/* Set up device भव mem map */
	err = ct_map_audio_buffer(atc, apcm);
	अगर (err < 0)
		जाओ error1;

	वापस 0;

error1:
	atc_pcm_release_resources(atc, apcm);
	वापस err;
पूर्ण

अटल पूर्णांक atc_pcm_capture_prepare(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src *src;
	काष्ठा amixer *amixer;
	काष्ठा srcimp *srcimp;
	काष्ठा ct_mixer *mixer = atc->mixer;
	काष्ठा sum *mono;
	काष्ठा rsc *out_ports[8] = अणुशून्यपूर्ण;
	पूर्णांक err, i, j, n_sum, multi;
	अचिन्हित पूर्णांक pitch;
	पूर्णांक mix_base = 0, imp_base = 0;

	atc_pcm_release_resources(atc, apcm);

	/* Get needed resources. */
	err = atc_pcm_capture_get_resources(atc, apcm);
	अगर (err)
		वापस err;

	/* Connect resources */
	mixer->get_output_ports(mixer, MIX_PCMO_FRONT,
				&out_ports[0], &out_ports[1]);

	multi = apcm->substream->runसमय->channels;
	अगर (1 == multi) अणु
		mono = apcm->mono;
		क्रम (i = 0; i < 2; i++) अणु
			amixer = apcm->amixers[i];
			amixer->ops->setup(amixer, out_ports[i],
						MONO_SUM_SCALE, mono);
		पूर्ण
		out_ports[0] = &mono->rsc;
		n_sum = 1;
		mix_base = n_sum * 2;
	पूर्ण

	क्रम (i = 0; i < apcm->n_srcc; i++) अणु
		src = apcm->srccs[i];
		srcimp = apcm->srcimps[imp_base+i];
		amixer = apcm->amixers[mix_base+i];
		srcimp->ops->map(srcimp, src, out_ports[i%multi]);
		amixer->ops->setup(amixer, &src->rsc, INIT_VOL, शून्य);
		out_ports[i%multi] = &amixer->rsc;
	पूर्ण

	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runसमय->rate);

	अगर ((multi > 1) && (pitch <= 0x8000000)) अणु
		/* Special connection क्रम पूर्णांकerleaved
		 * recording with conjugate channels */
		क्रम (i = 0; i < multi; i++) अणु
			out_ports[i]->ops->master(out_ports[i]);
			क्रम (j = 0; j < atc->msr; j++) अणु
				amixer = apcm->amixers[apcm->n_srcc+j*multi+i];
				amixer->ops->set_input(amixer, out_ports[i]);
				amixer->ops->set_scale(amixer, INIT_VOL);
				amixer->ops->set_sum(amixer, शून्य);
				amixer->ops->commit_raw_ग_लिखो(amixer);
				out_ports[i]->ops->next_conj(out_ports[i]);

				srcimp = apcm->srcimps[apcm->n_srcc+j*multi+i];
				srcimp->ops->map(srcimp, apcm->src,
							&amixer->rsc);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < multi; i++) अणु
			srcimp = apcm->srcimps[apcm->n_srcc+i];
			srcimp->ops->map(srcimp, apcm->src, out_ports[i]);
		पूर्ण
	पूर्ण

	ct_समयr_prepare(apcm->समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_pcm_capture_start(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src *src;
	काष्ठा src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	पूर्णांक i, multi;

	अगर (apcm->started)
		वापस 0;

	apcm->started = 1;
	multi = apcm->substream->runसमय->channels;
	/* Set up converting SRCs */
	क्रम (i = 0; i < apcm->n_srcc; i++) अणु
		src = apcm->srccs[i];
		src->ops->set_pm(src, ((i%multi) != (multi-1)));
		src_mgr->src_disable(src_mgr, src);
	पूर्ण

	/*  Set up recording SRC */
	src = apcm->src;
	src->ops->set_sf(src, convert_क्रमmat(apcm->substream->runसमय->क्रमmat,
					     atc->card));
	src->ops->set_sa(src, apcm->vm_block->addr);
	src->ops->set_la(src, apcm->vm_block->addr + apcm->vm_block->size);
	src->ops->set_ca(src, apcm->vm_block->addr);
	src_mgr->src_disable(src_mgr, src);

	/* Disable relevant SRCs firstly */
	src_mgr->commit_ग_लिखो(src_mgr);

	/* Enable SRCs respectively */
	क्रम (i = 0; i < apcm->n_srcc; i++) अणु
		src = apcm->srccs[i];
		src->ops->set_state(src, SRC_STATE_RUN);
		src->ops->commit_ग_लिखो(src);
		src_mgr->src_enable_s(src_mgr, src);
	पूर्ण
	src = apcm->src;
	src->ops->set_bm(src, 1);
	src->ops->set_state(src, SRC_STATE_RUN);
	src->ops->commit_ग_लिखो(src);
	src_mgr->src_enable_s(src_mgr, src);

	/* Enable relevant SRCs synchronously */
	src_mgr->commit_ग_लिखो(src_mgr);

	ct_समयr_start(apcm->समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक
atc_pcm_capture_position(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src *src = apcm->src;

	अगर (!src)
		वापस 0;
	वापस src->ops->get_ca(src) - apcm->vm_block->addr;
पूर्ण

अटल पूर्णांक spdअगर_passthru_playback_get_resources(काष्ठा ct_atc *atc,
						 काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	काष्ठा amixer_mgr *amixer_mgr = atc->rsc_mgrs[AMIXER];
	काष्ठा src_desc desc = अणु0पूर्ण;
	काष्ठा amixer_desc mix_dsc = अणु0पूर्ण;
	काष्ठा src *src;
	पूर्णांक err;
	पूर्णांक n_amixer = apcm->substream->runसमय->channels, i;
	अचिन्हित पूर्णांक pitch, rsr = atc->pll_rate;

	/* first release old resources */
	atc_pcm_release_resources(atc, apcm);

	/* Get SRC resource */
	desc.multi = apcm->substream->runसमय->channels;
	desc.msr = 1;
	जबतक (apcm->substream->runसमय->rate > (rsr * desc.msr))
		desc.msr <<= 1;

	desc.mode = MEMRD;
	err = src_mgr->get_src(src_mgr, &desc, (काष्ठा src **)&apcm->src);
	अगर (err)
		जाओ error1;

	pitch = atc_get_pitch(apcm->substream->runसमय->rate, (rsr * desc.msr));
	src = apcm->src;
	src->ops->set_pitch(src, pitch);
	src->ops->set_rom(src, select_rom(pitch));
	src->ops->set_sf(src, convert_क्रमmat(apcm->substream->runसमय->क्रमmat,
					     atc->card));
	src->ops->set_pm(src, (src->ops->next_पूर्णांकerleave(src) != शून्य));
	src->ops->set_bp(src, 1);

	/* Get AMIXER resource */
	n_amixer = (n_amixer < 2) ? 2 : n_amixer;
	apcm->amixers = kसुस्मृति(n_amixer, माप(व्योम *), GFP_KERNEL);
	अगर (!apcm->amixers) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण
	mix_dsc.msr = desc.msr;
	क्रम (i = 0, apcm->n_amixer = 0; i < n_amixer; i++) अणु
		err = amixer_mgr->get_amixer(amixer_mgr, &mix_dsc,
					(काष्ठा amixer **)&apcm->amixers[i]);
		अगर (err)
			जाओ error1;

		apcm->n_amixer++;
	पूर्ण

	/* Set up device भव mem map */
	err = ct_map_audio_buffer(atc, apcm);
	अगर (err < 0)
		जाओ error1;

	वापस 0;

error1:
	atc_pcm_release_resources(atc, apcm);
	वापस err;
पूर्ण

अटल पूर्णांक atc_pll_init(काष्ठा ct_atc *atc, पूर्णांक rate)
अणु
	काष्ठा hw *hw = atc->hw;
	पूर्णांक err;
	err = hw->pll_init(hw, rate);
	atc->pll_rate = err ? 0 : rate;
	वापस err;
पूर्ण

अटल पूर्णांक
spdअगर_passthru_playback_setup(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा dao *dao = container_of(atc->daios[SPDIFOO], काष्ठा dao, daio);
	अचिन्हित पूर्णांक rate = apcm->substream->runसमय->rate;
	अचिन्हित पूर्णांक status;
	पूर्णांक err = 0;
	अचिन्हित अक्षर iec958_con_fs;

	चयन (rate) अणु
	हाल 48000:
		iec958_con_fs = IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 44100:
		iec958_con_fs = IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 32000:
		iec958_con_fs = IEC958_AES3_CON_FS_32000;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	mutex_lock(&atc->atc_mutex);
	dao->ops->get_spos(dao, &status);
	अगर (((status >> 24) & IEC958_AES3_CON_FS) != iec958_con_fs) अणु
		status &= ~(IEC958_AES3_CON_FS << 24);
		status |= (iec958_con_fs << 24);
		dao->ops->set_spos(dao, status);
		dao->ops->commit_ग_लिखो(dao);
	पूर्ण
	अगर ((rate != atc->pll_rate) && (32000 != rate))
		err = atc_pll_init(atc, rate);
	mutex_unlock(&atc->atc_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक
spdअगर_passthru_playback_prepare(काष्ठा ct_atc *atc, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा src *src;
	काष्ठा amixer *amixer;
	काष्ठा dao *dao;
	पूर्णांक err;
	पूर्णांक i;

	atc_pcm_release_resources(atc, apcm);

	/* Configure SPDIFOO and PLL to passthrough mode;
	 * determine pll_rate. */
	err = spdअगर_passthru_playback_setup(atc, apcm);
	अगर (err)
		वापस err;

	/* Get needed resources. */
	err = spdअगर_passthru_playback_get_resources(atc, apcm);
	अगर (err)
		वापस err;

	/* Connect resources */
	src = apcm->src;
	क्रम (i = 0; i < apcm->n_amixer; i++) अणु
		amixer = apcm->amixers[i];
		amixer->ops->setup(amixer, &src->rsc, INIT_VOL, शून्य);
		src = src->ops->next_पूर्णांकerleave(src);
		अगर (!src)
			src = apcm->src;
	पूर्ण
	/* Connect to SPDIFOO */
	mutex_lock(&atc->atc_mutex);
	dao = container_of(atc->daios[SPDIFOO], काष्ठा dao, daio);
	amixer = apcm->amixers[0];
	dao->ops->set_left_input(dao, &amixer->rsc);
	amixer = apcm->amixers[1];
	dao->ops->set_right_input(dao, &amixer->rsc);
	mutex_unlock(&atc->atc_mutex);

	ct_समयr_prepare(apcm->समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_select_line_in(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;
	काष्ठा ct_mixer *mixer = atc->mixer;
	काष्ठा src *src;

	अगर (hw->is_adc_source_selected(hw, ADC_LINEIN))
		वापस 0;

	mixer->set_input_left(mixer, MIX_MIC_IN, शून्य);
	mixer->set_input_right(mixer, MIX_MIC_IN, शून्य);

	hw->select_adc_source(hw, ADC_LINEIN);

	src = atc->srcs[2];
	mixer->set_input_left(mixer, MIX_LINE_IN, &src->rsc);
	src = atc->srcs[3];
	mixer->set_input_right(mixer, MIX_LINE_IN, &src->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_select_mic_in(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;
	काष्ठा ct_mixer *mixer = atc->mixer;
	काष्ठा src *src;

	अगर (hw->is_adc_source_selected(hw, ADC_MICIN))
		वापस 0;

	mixer->set_input_left(mixer, MIX_LINE_IN, शून्य);
	mixer->set_input_right(mixer, MIX_LINE_IN, शून्य);

	hw->select_adc_source(hw, ADC_MICIN);

	src = atc->srcs[2];
	mixer->set_input_left(mixer, MIX_MIC_IN, &src->rsc);
	src = atc->srcs[3];
	mixer->set_input_right(mixer, MIX_MIC_IN, &src->rsc);

	वापस 0;
पूर्ण

अटल काष्ठा capabilities atc_capabilities(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;

	वापस hw->capabilities(hw);
पूर्ण

अटल पूर्णांक atc_output_चयन_get(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;

	वापस hw->output_चयन_get(hw);
पूर्ण

अटल पूर्णांक atc_output_चयन_put(काष्ठा ct_atc *atc, पूर्णांक position)
अणु
	काष्ठा hw *hw = atc->hw;

	वापस hw->output_चयन_put(hw, position);
पूर्ण

अटल पूर्णांक atc_mic_source_चयन_get(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;

	वापस hw->mic_source_चयन_get(hw);
पूर्ण

अटल पूर्णांक atc_mic_source_चयन_put(काष्ठा ct_atc *atc, पूर्णांक position)
अणु
	काष्ठा hw *hw = atc->hw;

	वापस hw->mic_source_चयन_put(hw, position);
पूर्ण

अटल पूर्णांक atc_select_digit_io(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;

	अगर (hw->is_adc_source_selected(hw, ADC_NONE))
		वापस 0;

	hw->select_adc_source(hw, ADC_NONE);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_daio_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state, पूर्णांक type)
अणु
	काष्ठा daio_mgr *daio_mgr = atc->rsc_mgrs[DAIO];

	अगर (state)
		daio_mgr->daio_enable(daio_mgr, atc->daios[type]);
	अन्यथा
		daio_mgr->daio_disable(daio_mgr, atc->daios[type]);

	daio_mgr->commit_ग_लिखो(daio_mgr);

	वापस 0;
पूर्ण

अटल पूर्णांक
atc_dao_get_status(काष्ठा ct_atc *atc, अचिन्हित पूर्णांक *status, पूर्णांक type)
अणु
	काष्ठा dao *dao = container_of(atc->daios[type], काष्ठा dao, daio);
	वापस dao->ops->get_spos(dao, status);
पूर्ण

अटल पूर्णांक
atc_dao_set_status(काष्ठा ct_atc *atc, अचिन्हित पूर्णांक status, पूर्णांक type)
अणु
	काष्ठा dao *dao = container_of(atc->daios[type], काष्ठा dao, daio);

	dao->ops->set_spos(dao, status);
	dao->ops->commit_ग_लिखो(dao);
	वापस 0;
पूर्ण

अटल पूर्णांक atc_line_front_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, LINEO1);
पूर्ण

अटल पूर्णांक atc_line_surround_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, LINEO2);
पूर्ण

अटल पूर्णांक atc_line_clfe_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, LINEO3);
पूर्ण

अटल पूर्णांक atc_line_rear_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, LINEO4);
पूर्ण

अटल पूर्णांक atc_line_in_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, LINEIM);
पूर्ण

अटल पूर्णांक atc_mic_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, MIC);
पूर्ण

अटल पूर्णांक atc_spdअगर_out_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, SPDIFOO);
पूर्ण

अटल पूर्णांक atc_spdअगर_in_unmute(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	वापस atc_daio_unmute(atc, state, SPDIFIO);
पूर्ण

अटल पूर्णांक atc_spdअगर_out_get_status(काष्ठा ct_atc *atc, अचिन्हित पूर्णांक *status)
अणु
	वापस atc_dao_get_status(atc, status, SPDIFOO);
पूर्ण

अटल पूर्णांक atc_spdअगर_out_set_status(काष्ठा ct_atc *atc, अचिन्हित पूर्णांक status)
अणु
	वापस atc_dao_set_status(atc, status, SPDIFOO);
पूर्ण

अटल पूर्णांक atc_spdअगर_out_passthru(काष्ठा ct_atc *atc, अचिन्हित अक्षर state)
अणु
	काष्ठा dao_desc da_dsc = अणु0पूर्ण;
	काष्ठा dao *dao;
	पूर्णांक err;
	काष्ठा ct_mixer *mixer = atc->mixer;
	काष्ठा rsc *rscs[2] = अणुशून्यपूर्ण;
	अचिन्हित पूर्णांक spos = 0;

	mutex_lock(&atc->atc_mutex);
	dao = container_of(atc->daios[SPDIFOO], काष्ठा dao, daio);
	da_dsc.msr = state ? 1 : atc->msr;
	da_dsc.passthru = state ? 1 : 0;
	err = dao->ops->reinit(dao, &da_dsc);
	अगर (state) अणु
		spos = IEC958_DEFAULT_CON;
	पूर्ण अन्यथा अणु
		mixer->get_output_ports(mixer, MIX_SPDIF_OUT,
					&rscs[0], &rscs[1]);
		dao->ops->set_left_input(dao, rscs[0]);
		dao->ops->set_right_input(dao, rscs[1]);
		/* Restore PLL to atc->rsr अगर needed. */
		अगर (atc->pll_rate != atc->rsr)
			err = atc_pll_init(atc, atc->rsr);
	पूर्ण
	dao->ops->set_spos(dao, spos);
	dao->ops->commit_ग_लिखो(dao);
	mutex_unlock(&atc->atc_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक atc_release_resources(काष्ठा ct_atc *atc)
अणु
	पूर्णांक i;
	काष्ठा daio_mgr *daio_mgr = शून्य;
	काष्ठा dao *dao = शून्य;
	काष्ठा daio *daio = शून्य;
	काष्ठा sum_mgr *sum_mgr = शून्य;
	काष्ठा src_mgr *src_mgr = शून्य;
	काष्ठा srcimp_mgr *srcimp_mgr = शून्य;
	काष्ठा srcimp *srcimp = शून्य;
	काष्ठा ct_mixer *mixer = शून्य;

	/* disconnect पूर्णांकernal mixer objects */
	अगर (atc->mixer) अणु
		mixer = atc->mixer;
		mixer->set_input_left(mixer, MIX_LINE_IN, शून्य);
		mixer->set_input_right(mixer, MIX_LINE_IN, शून्य);
		mixer->set_input_left(mixer, MIX_MIC_IN, शून्य);
		mixer->set_input_right(mixer, MIX_MIC_IN, शून्य);
		mixer->set_input_left(mixer, MIX_SPDIF_IN, शून्य);
		mixer->set_input_right(mixer, MIX_SPDIF_IN, शून्य);
	पूर्ण

	अगर (atc->daios) अणु
		daio_mgr = (काष्ठा daio_mgr *)atc->rsc_mgrs[DAIO];
		क्रम (i = 0; i < atc->n_daio; i++) अणु
			daio = atc->daios[i];
			अगर (daio->type < LINEIM) अणु
				dao = container_of(daio, काष्ठा dao, daio);
				dao->ops->clear_left_input(dao);
				dao->ops->clear_right_input(dao);
			पूर्ण
			daio_mgr->put_daio(daio_mgr, daio);
		पूर्ण
		kमुक्त(atc->daios);
		atc->daios = शून्य;
	पूर्ण

	अगर (atc->pcm) अणु
		sum_mgr = atc->rsc_mgrs[SUM];
		क्रम (i = 0; i < atc->n_pcm; i++)
			sum_mgr->put_sum(sum_mgr, atc->pcm[i]);

		kमुक्त(atc->pcm);
		atc->pcm = शून्य;
	पूर्ण

	अगर (atc->srcs) अणु
		src_mgr = atc->rsc_mgrs[SRC];
		क्रम (i = 0; i < atc->n_src; i++)
			src_mgr->put_src(src_mgr, atc->srcs[i]);

		kमुक्त(atc->srcs);
		atc->srcs = शून्य;
	पूर्ण

	अगर (atc->srcimps) अणु
		srcimp_mgr = atc->rsc_mgrs[SRCIMP];
		क्रम (i = 0; i < atc->n_srcimp; i++) अणु
			srcimp = atc->srcimps[i];
			srcimp->ops->unmap(srcimp);
			srcimp_mgr->put_srcimp(srcimp_mgr, atc->srcimps[i]);
		पूर्ण
		kमुक्त(atc->srcimps);
		atc->srcimps = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ct_atc_destroy(काष्ठा ct_atc *atc)
अणु
	पूर्णांक i = 0;

	अगर (!atc)
		वापस 0;

	अगर (atc->समयr) अणु
		ct_समयr_मुक्त(atc->समयr);
		atc->समयr = शून्य;
	पूर्ण

	atc_release_resources(atc);

	/* Destroy पूर्णांकernal mixer objects */
	अगर (atc->mixer)
		ct_mixer_destroy(atc->mixer);

	क्रम (i = 0; i < NUM_RSCTYP; i++) अणु
		अगर (rsc_mgr_funcs[i].destroy && atc->rsc_mgrs[i])
			rsc_mgr_funcs[i].destroy(atc->rsc_mgrs[i]);

	पूर्ण

	अगर (atc->hw)
		destroy_hw_obj(atc->hw);

	/* Destroy device भव memory manager object */
	अगर (atc->vm) अणु
		ct_vm_destroy(atc->vm);
		atc->vm = शून्य;
	पूर्ण

	kमुक्त(atc);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_dev_मुक्त(काष्ठा snd_device *dev)
अणु
	काष्ठा ct_atc *atc = dev->device_data;
	वापस ct_atc_destroy(atc);
पूर्ण

अटल पूर्णांक atc_identअगरy_card(काष्ठा ct_atc *atc, अचिन्हित पूर्णांक ssid)
अणु
	स्थिर काष्ठा snd_pci_quirk *p;
	स्थिर काष्ठा snd_pci_quirk *list;
	u16 venकरोr_id, device_id;

	चयन (atc->chip_type) अणु
	हाल ATC20K1:
		atc->chip_name = "20K1";
		list = subsys_20k1_list;
		अवरोध;
	हाल ATC20K2:
		atc->chip_name = "20K2";
		list = subsys_20k2_list;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण
	अगर (ssid) अणु
		venकरोr_id = ssid >> 16;
		device_id = ssid & 0xffff;
	पूर्ण अन्यथा अणु
		venकरोr_id = atc->pci->subप्रणाली_venकरोr;
		device_id = atc->pci->subप्रणाली_device;
	पूर्ण
	p = snd_pci_quirk_lookup_id(venकरोr_id, device_id, list);
	अगर (p) अणु
		अगर (p->value < 0) अणु
			dev_err(atc->card->dev,
				"Device %04x:%04x is on the denylist\n",
				venकरोr_id, device_id);
			वापस -ENOENT;
		पूर्ण
		atc->model = p->value;
	पूर्ण अन्यथा अणु
		अगर (atc->chip_type == ATC20K1)
			atc->model = CT20K1_UNKNOWN;
		अन्यथा
			atc->model = CT20K2_UNKNOWN;
	पूर्ण
	atc->model_name = ct_subsys_name[atc->model];
	dev_info(atc->card->dev, "chip %s model %s (%04x:%04x) is found\n",
		   atc->chip_name, atc->model_name,
		   venकरोr_id, device_id);
	वापस 0;
पूर्ण

पूर्णांक ct_atc_create_alsa_devs(काष्ठा ct_atc *atc)
अणु
	क्रमागत CTALSADEVS i;
	पूर्णांक err;

	alsa_dev_funcs[MIXER].खुला_name = atc->chip_name;

	क्रम (i = 0; i < NUM_CTALSADEVS; i++) अणु
		अगर (!alsa_dev_funcs[i].create)
			जारी;

		err = alsa_dev_funcs[i].create(atc, i,
				alsa_dev_funcs[i].खुला_name);
		अगर (err) अणु
			dev_err(atc->card->dev,
				"Creating alsa device %d failed!\n", i);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atc_create_hw_devs(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw;
	काष्ठा card_conf info = अणु0पूर्ण;
	पूर्णांक i, err;

	err = create_hw_obj(atc->pci, atc->chip_type, atc->model, &hw);
	अगर (err) अणु
		dev_err(atc->card->dev, "Failed to create hw obj!!!\n");
		वापस err;
	पूर्ण
	hw->card = atc->card;
	atc->hw = hw;

	/* Initialize card hardware. */
	info.rsr = atc->rsr;
	info.msr = atc->msr;
	info.vm_pgt_phys = atc_get_ptp_phys(atc, 0);
	err = hw->card_init(hw, &info);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < NUM_RSCTYP; i++) अणु
		अगर (!rsc_mgr_funcs[i].create)
			जारी;

		err = rsc_mgr_funcs[i].create(atc->hw, &atc->rsc_mgrs[i]);
		अगर (err) अणु
			dev_err(atc->card->dev,
				"Failed to create rsc_mgr %d!!!\n", i);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atc_get_resources(काष्ठा ct_atc *atc)
अणु
	काष्ठा daio_desc da_desc = अणु0पूर्ण;
	काष्ठा daio_mgr *daio_mgr;
	काष्ठा src_desc src_dsc = अणु0पूर्ण;
	काष्ठा src_mgr *src_mgr;
	काष्ठा srcimp_desc srcimp_dsc = अणु0पूर्ण;
	काष्ठा srcimp_mgr *srcimp_mgr;
	काष्ठा sum_desc sum_dsc = अणु0पूर्ण;
	काष्ठा sum_mgr *sum_mgr;
	पूर्णांक err, i, num_srcs, num_daios;

	num_daios = ((atc->model == CTSB1270) ? 8 : 7);
	num_srcs = ((atc->model == CTSB1270) ? 6 : 4);

	atc->daios = kसुस्मृति(num_daios, माप(व्योम *), GFP_KERNEL);
	अगर (!atc->daios)
		वापस -ENOMEM;

	atc->srcs = kसुस्मृति(num_srcs, माप(व्योम *), GFP_KERNEL);
	अगर (!atc->srcs)
		वापस -ENOMEM;

	atc->srcimps = kसुस्मृति(num_srcs, माप(व्योम *), GFP_KERNEL);
	अगर (!atc->srcimps)
		वापस -ENOMEM;

	atc->pcm = kसुस्मृति(2 * 4, माप(व्योम *), GFP_KERNEL);
	अगर (!atc->pcm)
		वापस -ENOMEM;

	daio_mgr = (काष्ठा daio_mgr *)atc->rsc_mgrs[DAIO];
	da_desc.msr = atc->msr;
	क्रम (i = 0, atc->n_daio = 0; i < num_daios; i++) अणु
		da_desc.type = (atc->model != CTSB073X) ? i :
			     ((i == SPDIFIO) ? SPDIFI1 : i);
		err = daio_mgr->get_daio(daio_mgr, &da_desc,
					(काष्ठा daio **)&atc->daios[i]);
		अगर (err) अणु
			dev_err(atc->card->dev,
				"Failed to get DAIO resource %d!!!\n",
				i);
			वापस err;
		पूर्ण
		atc->n_daio++;
	पूर्ण

	src_mgr = atc->rsc_mgrs[SRC];
	src_dsc.multi = 1;
	src_dsc.msr = atc->msr;
	src_dsc.mode = ARCRW;
	क्रम (i = 0, atc->n_src = 0; i < num_srcs; i++) अणु
		err = src_mgr->get_src(src_mgr, &src_dsc,
					(काष्ठा src **)&atc->srcs[i]);
		अगर (err)
			वापस err;

		atc->n_src++;
	पूर्ण

	srcimp_mgr = atc->rsc_mgrs[SRCIMP];
	srcimp_dsc.msr = 8;
	क्रम (i = 0, atc->n_srcimp = 0; i < num_srcs; i++) अणु
		err = srcimp_mgr->get_srcimp(srcimp_mgr, &srcimp_dsc,
					(काष्ठा srcimp **)&atc->srcimps[i]);
		अगर (err)
			वापस err;

		atc->n_srcimp++;
	पूर्ण

	sum_mgr = atc->rsc_mgrs[SUM];
	sum_dsc.msr = atc->msr;
	क्रम (i = 0, atc->n_pcm = 0; i < (2*4); i++) अणु
		err = sum_mgr->get_sum(sum_mgr, &sum_dsc,
					(काष्ठा sum **)&atc->pcm[i]);
		अगर (err)
			वापस err;

		atc->n_pcm++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
atc_connect_dai(काष्ठा src_mgr *src_mgr, काष्ठा dai *dai,
		काष्ठा src **srcs, काष्ठा srcimp **srcimps)
अणु
	काष्ठा rsc *rscs[2] = अणुशून्यपूर्ण;
	काष्ठा src *src;
	काष्ठा srcimp *srcimp;
	पूर्णांक i = 0;

	rscs[0] = &dai->daio.rscl;
	rscs[1] = &dai->daio.rscr;
	क्रम (i = 0; i < 2; i++) अणु
		src = srcs[i];
		srcimp = srcimps[i];
		srcimp->ops->map(srcimp, src, rscs[i]);
		src_mgr->src_disable(src_mgr, src);
	पूर्ण

	src_mgr->commit_ग_लिखो(src_mgr); /* Actually disable SRCs */

	src = srcs[0];
	src->ops->set_pm(src, 1);
	क्रम (i = 0; i < 2; i++) अणु
		src = srcs[i];
		src->ops->set_state(src, SRC_STATE_RUN);
		src->ops->commit_ग_लिखो(src);
		src_mgr->src_enable_s(src_mgr, src);
	पूर्ण

	dai->ops->set_srt_srcl(dai, &(srcs[0]->rsc));
	dai->ops->set_srt_srcr(dai, &(srcs[1]->rsc));

	dai->ops->set_enb_src(dai, 1);
	dai->ops->set_enb_srt(dai, 1);
	dai->ops->commit_ग_लिखो(dai);

	src_mgr->commit_ग_लिखो(src_mgr); /* Synchronously enable SRCs */
पूर्ण

अटल व्योम atc_connect_resources(काष्ठा ct_atc *atc)
अणु
	काष्ठा dai *dai;
	काष्ठा dao *dao;
	काष्ठा src *src;
	काष्ठा sum *sum;
	काष्ठा ct_mixer *mixer;
	काष्ठा rsc *rscs[2] = अणुशून्यपूर्ण;
	पूर्णांक i, j;

	mixer = atc->mixer;

	क्रम (i = MIX_WAVE_FRONT, j = LINEO1; i <= MIX_SPDIF_OUT; i++, j++) अणु
		mixer->get_output_ports(mixer, i, &rscs[0], &rscs[1]);
		dao = container_of(atc->daios[j], काष्ठा dao, daio);
		dao->ops->set_left_input(dao, rscs[0]);
		dao->ops->set_right_input(dao, rscs[1]);
	पूर्ण

	dai = container_of(atc->daios[LINEIM], काष्ठा dai, daio);
	atc_connect_dai(atc->rsc_mgrs[SRC], dai,
			(काष्ठा src **)&atc->srcs[2],
			(काष्ठा srcimp **)&atc->srcimps[2]);
	src = atc->srcs[2];
	mixer->set_input_left(mixer, MIX_LINE_IN, &src->rsc);
	src = atc->srcs[3];
	mixer->set_input_right(mixer, MIX_LINE_IN, &src->rsc);

	अगर (atc->model == CTSB1270) अणु
		/* Titanium HD has a dedicated ADC क्रम the Mic. */
		dai = container_of(atc->daios[MIC], काष्ठा dai, daio);
		atc_connect_dai(atc->rsc_mgrs[SRC], dai,
			(काष्ठा src **)&atc->srcs[4],
			(काष्ठा srcimp **)&atc->srcimps[4]);
		src = atc->srcs[4];
		mixer->set_input_left(mixer, MIX_MIC_IN, &src->rsc);
		src = atc->srcs[5];
		mixer->set_input_right(mixer, MIX_MIC_IN, &src->rsc);
	पूर्ण

	dai = container_of(atc->daios[SPDIFIO], काष्ठा dai, daio);
	atc_connect_dai(atc->rsc_mgrs[SRC], dai,
			(काष्ठा src **)&atc->srcs[0],
			(काष्ठा srcimp **)&atc->srcimps[0]);

	src = atc->srcs[0];
	mixer->set_input_left(mixer, MIX_SPDIF_IN, &src->rsc);
	src = atc->srcs[1];
	mixer->set_input_right(mixer, MIX_SPDIF_IN, &src->rsc);

	क्रम (i = MIX_PCMI_FRONT, j = 0; i <= MIX_PCMI_SURROUND; i++, j += 2) अणु
		sum = atc->pcm[j];
		mixer->set_input_left(mixer, i, &sum->rsc);
		sum = atc->pcm[j+1];
		mixer->set_input_right(mixer, i, &sum->rsc);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक atc_suspend(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;

	snd_घातer_change_state(atc->card, SNDRV_CTL_POWER_D3hot);

	atc_release_resources(atc);

	hw->suspend(hw);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_hw_resume(काष्ठा ct_atc *atc)
अणु
	काष्ठा hw *hw = atc->hw;
	काष्ठा card_conf info = अणु0पूर्ण;

	/* Re-initialize card hardware. */
	info.rsr = atc->rsr;
	info.msr = atc->msr;
	info.vm_pgt_phys = atc_get_ptp_phys(atc, 0);
	वापस hw->resume(hw, &info);
पूर्ण

अटल पूर्णांक atc_resources_resume(काष्ठा ct_atc *atc)
अणु
	काष्ठा ct_mixer *mixer;
	पूर्णांक err = 0;

	/* Get resources */
	err = atc_get_resources(atc);
	अगर (err < 0) अणु
		atc_release_resources(atc);
		वापस err;
	पूर्ण

	/* Build topology */
	atc_connect_resources(atc);

	mixer = atc->mixer;
	mixer->resume(mixer);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_resume(काष्ठा ct_atc *atc)
अणु
	पूर्णांक err = 0;

	/* Do hardware resume. */
	err = atc_hw_resume(atc);
	अगर (err < 0) अणु
		dev_err(atc->card->dev,
			"pci_enable_device failed, disabling device\n");
		snd_card_disconnect(atc->card);
		वापस err;
	पूर्ण

	err = atc_resources_resume(atc);
	अगर (err < 0)
		वापस err;

	snd_घातer_change_state(atc->card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा ct_atc atc_preset = अणु
	.map_audio_buffer = ct_map_audio_buffer,
	.unmap_audio_buffer = ct_unmap_audio_buffer,
	.pcm_playback_prepare = atc_pcm_playback_prepare,
	.pcm_release_resources = atc_pcm_release_resources,
	.pcm_playback_start = atc_pcm_playback_start,
	.pcm_playback_stop = atc_pcm_stop,
	.pcm_playback_position = atc_pcm_playback_position,
	.pcm_capture_prepare = atc_pcm_capture_prepare,
	.pcm_capture_start = atc_pcm_capture_start,
	.pcm_capture_stop = atc_pcm_stop,
	.pcm_capture_position = atc_pcm_capture_position,
	.spdअगर_passthru_playback_prepare = spdअगर_passthru_playback_prepare,
	.get_ptp_phys = atc_get_ptp_phys,
	.select_line_in = atc_select_line_in,
	.select_mic_in = atc_select_mic_in,
	.select_digit_io = atc_select_digit_io,
	.line_front_unmute = atc_line_front_unmute,
	.line_surround_unmute = atc_line_surround_unmute,
	.line_clfe_unmute = atc_line_clfe_unmute,
	.line_rear_unmute = atc_line_rear_unmute,
	.line_in_unmute = atc_line_in_unmute,
	.mic_unmute = atc_mic_unmute,
	.spdअगर_out_unmute = atc_spdअगर_out_unmute,
	.spdअगर_in_unmute = atc_spdअगर_in_unmute,
	.spdअगर_out_get_status = atc_spdअगर_out_get_status,
	.spdअगर_out_set_status = atc_spdअगर_out_set_status,
	.spdअगर_out_passthru = atc_spdअगर_out_passthru,
	.capabilities = atc_capabilities,
	.output_चयन_get = atc_output_चयन_get,
	.output_चयन_put = atc_output_चयन_put,
	.mic_source_चयन_get = atc_mic_source_चयन_get,
	.mic_source_चयन_put = atc_mic_source_चयन_put,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend = atc_suspend,
	.resume = atc_resume,
#पूर्ण_अगर
पूर्ण;

/**
 *  ct_atc_create - create and initialize a hardware manager
 *  @card: corresponding alsa card object
 *  @pci: corresponding kernel pci device object
 *  @rsr: reference sampling rate
 *  @msr: master sampling rate
 *  @chip_type: CHIPTYP क्रमागत values
 *  @ssid: venकरोr ID (upper 16 bits) and device ID (lower 16 bits)
 *  @ratc: वापस created object address in it
 *
 *  Creates and initializes a hardware manager.
 *
 *  Creates kदो_स्मृतिated ct_atc काष्ठाure. Initializes hardware.
 *  Returns 0 अगर succeeds, or negative error code अगर fails.
 */

पूर्णांक ct_atc_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
		  अचिन्हित पूर्णांक rsr, अचिन्हित पूर्णांक msr,
		  पूर्णांक chip_type, अचिन्हित पूर्णांक ssid,
		  काष्ठा ct_atc **ratc)
अणु
	काष्ठा ct_atc *atc;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = atc_dev_मुक्त,
	पूर्ण;
	पूर्णांक err;

	*ratc = शून्य;

	atc = kzalloc(माप(*atc), GFP_KERNEL);
	अगर (!atc)
		वापस -ENOMEM;

	/* Set operations */
	*atc = atc_preset;

	atc->card = card;
	atc->pci = pci;
	atc->rsr = rsr;
	atc->msr = msr;
	atc->chip_type = chip_type;

	mutex_init(&atc->atc_mutex);

	/* Find card model */
	err = atc_identअगरy_card(atc, ssid);
	अगर (err < 0) अणु
		dev_err(card->dev, "ctatc: Card not recognised\n");
		जाओ error1;
	पूर्ण

	/* Set up device भव memory management object */
	err = ct_vm_create(&atc->vm, pci);
	अगर (err < 0)
		जाओ error1;

	/* Create all atc hw devices */
	err = atc_create_hw_devs(atc);
	अगर (err < 0)
		जाओ error1;

	err = ct_mixer_create(atc, (काष्ठा ct_mixer **)&atc->mixer);
	अगर (err) अणु
		dev_err(card->dev, "Failed to create mixer obj!!!\n");
		जाओ error1;
	पूर्ण

	/* Get resources */
	err = atc_get_resources(atc);
	अगर (err < 0)
		जाओ error1;

	/* Build topology */
	atc_connect_resources(atc);

	atc->समयr = ct_समयr_new(atc);
	अगर (!atc->समयr) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, atc, &ops);
	अगर (err < 0)
		जाओ error1;

	*ratc = atc;
	वापस 0;

error1:
	ct_atc_destroy(atc);
	dev_err(card->dev, "Something wrong!!!\n");
	वापस err;
पूर्ण
