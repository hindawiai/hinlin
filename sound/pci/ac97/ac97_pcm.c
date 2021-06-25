<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.2
 *  by Intel Corporation (http://developer.पूर्णांकel.com) and to datasheets
 *  क्रम specअगरic codecs.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/asoundef.h>
#समावेश "ac97_id.h"
#समावेश "ac97_local.h"

/*
 *  PCM support
 */

अटल स्थिर अचिन्हित अक्षर rate_reg_tables[2][4][9] = अणु
अणु
  /* standard rates */
  अणु
  	/* 3&4 front, 7&8 rear, 6&9 center/lfe */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 3 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 4 */
	0xff,				/* slot 5 */
	AC97_PCM_LFE_DAC_RATE,		/* slot 6 */
	AC97_PCM_SURR_DAC_RATE,		/* slot 7 */
	AC97_PCM_SURR_DAC_RATE,		/* slot 8 */
	AC97_PCM_LFE_DAC_RATE,		/* slot 9 */
	0xff,				/* slot 10 */
	0xff,				/* slot 11 */
  पूर्ण,
  अणु
  	/* 7&8 front, 6&9 rear, 10&11 center/lfe */
	0xff,				/* slot 3 */
	0xff,				/* slot 4 */
	0xff,				/* slot 5 */
	AC97_PCM_SURR_DAC_RATE,		/* slot 6 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 7 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 8 */
	AC97_PCM_SURR_DAC_RATE,		/* slot 9 */
	AC97_PCM_LFE_DAC_RATE,		/* slot 10 */
	AC97_PCM_LFE_DAC_RATE,		/* slot 11 */
  पूर्ण,
  अणु
  	/* 6&9 front, 10&11 rear, 3&4 center/lfe */
	AC97_PCM_LFE_DAC_RATE,		/* slot 3 */
	AC97_PCM_LFE_DAC_RATE,		/* slot 4 */
	0xff,				/* slot 5 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 6 */
	0xff,				/* slot 7 */
	0xff,				/* slot 8 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 9 */
	AC97_PCM_SURR_DAC_RATE,		/* slot 10 */
	AC97_PCM_SURR_DAC_RATE,		/* slot 11 */
  पूर्ण,
  अणु
  	/* 10&11 front, 3&4 rear, 7&8 center/lfe */
	AC97_PCM_SURR_DAC_RATE,		/* slot 3 */
	AC97_PCM_SURR_DAC_RATE,		/* slot 4 */
	0xff,				/* slot 5 */
	0xff,				/* slot 6 */
	AC97_PCM_LFE_DAC_RATE,		/* slot 7 */
	AC97_PCM_LFE_DAC_RATE,		/* slot 8 */
	0xff,				/* slot 9 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 10 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 11 */
  पूर्ण,
पूर्ण,
अणु
  /* द्विगुन rates */
  अणु
  	/* 3&4 front, 7&8 front (t+1) */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 3 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 4 */
	0xff,				/* slot 5 */
	0xff,				/* slot 6 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 7 */
	AC97_PCM_FRONT_DAC_RATE,	/* slot 8 */
	0xff,				/* slot 9 */
	0xff,				/* slot 10 */
	0xff,				/* slot 11 */
  पूर्ण,
  अणु
	/* not specअगरied in the specअगरication */
	0xff,				/* slot 3 */
	0xff,				/* slot 4 */
	0xff,				/* slot 5 */
	0xff,				/* slot 6 */
	0xff,				/* slot 7 */
	0xff,				/* slot 8 */
	0xff,				/* slot 9 */
	0xff,				/* slot 10 */
	0xff,				/* slot 11 */
  पूर्ण,
  अणु
	0xff,				/* slot 3 */
	0xff,				/* slot 4 */
	0xff,				/* slot 5 */
	0xff,				/* slot 6 */
	0xff,				/* slot 7 */
	0xff,				/* slot 8 */
	0xff,				/* slot 9 */
	0xff,				/* slot 10 */
	0xff,				/* slot 11 */
  पूर्ण,
  अणु
	0xff,				/* slot 3 */
	0xff,				/* slot 4 */
	0xff,				/* slot 5 */
	0xff,				/* slot 6 */
	0xff,				/* slot 7 */
	0xff,				/* slot 8 */
	0xff,				/* slot 9 */
	0xff,				/* slot 10 */
	0xff,				/* slot 11 */
  पूर्ण
पूर्णपूर्ण;

/* FIXME: more various mappings क्रम ADC? */
अटल स्थिर अचिन्हित अक्षर rate_cregs[9] = अणु
	AC97_PCM_LR_ADC_RATE,	/* 3 */
	AC97_PCM_LR_ADC_RATE,	/* 4 */
	0xff,			/* 5 */
	AC97_PCM_MIC_ADC_RATE,	/* 6 */
	0xff,			/* 7 */
	0xff,			/* 8 */
	0xff,			/* 9 */
	0xff,			/* 10 */
	0xff,			/* 11 */
पूर्ण;

अटल अचिन्हित अक्षर get_slot_reg(काष्ठा ac97_pcm *pcm, अचिन्हित लघु cidx,
				  अचिन्हित लघु slot, पूर्णांक dbl)
अणु
	अगर (slot < 3)
		वापस 0xff;
	अगर (slot > 11)
		वापस 0xff;
	अगर (pcm->spdअगर)
		वापस AC97_SPDIF; /* pseuकरो रेजिस्टर */
	अगर (pcm->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस rate_reg_tables[dbl][pcm->r[dbl].rate_table[cidx]][slot - 3];
	अन्यथा
		वापस rate_cregs[slot - 3];
पूर्ण

अटल पूर्णांक set_spdअगर_rate(काष्ठा snd_ac97 *ac97, अचिन्हित लघु rate)
अणु
	अचिन्हित लघु old, bits, reg, mask;
	अचिन्हित पूर्णांक sbits;

	अगर (! (ac97->ext_id & AC97_EI_SPDIF))
		वापस -ENODEV;

	/* TODO: द्विगुन rate support */
	अगर (ac97->flags & AC97_CS_SPDIF) अणु
		चयन (rate) अणु
		हाल 48000: bits = 0; अवरोध;
		हाल 44100: bits = 1 << AC97_SC_SPSR_SHIFT; अवरोध;
		शेष: /* invalid - disable output */
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			वापस -EINVAL;
		पूर्ण
		reg = AC97_CSR_SPDIF;
		mask = 1 << AC97_SC_SPSR_SHIFT;
	पूर्ण अन्यथा अणु
		अगर (ac97->id == AC97_ID_CM9739 && rate != 48000) अणु
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			वापस -EINVAL;
		पूर्ण
		चयन (rate) अणु
		हाल 44100: bits = AC97_SC_SPSR_44K; अवरोध;
		हाल 48000: bits = AC97_SC_SPSR_48K; अवरोध;
		हाल 32000: bits = AC97_SC_SPSR_32K; अवरोध;
		शेष: /* invalid - disable output */
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			वापस -EINVAL;
		पूर्ण
		reg = AC97_SPDIF;
		mask = AC97_SC_SPSR_MASK;
	पूर्ण

	mutex_lock(&ac97->reg_mutex);
	old = snd_ac97_पढ़ो(ac97, reg) & mask;
	अगर (old != bits) अणु
		snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
		snd_ac97_update_bits_nolock(ac97, reg, mask, bits);
		/* update the पूर्णांकernal spdअगर bits */
		sbits = ac97->spdअगर_status;
		अगर (sbits & IEC958_AES0_PROFESSIONAL) अणु
			sbits &= ~IEC958_AES0_PRO_FS;
			चयन (rate) अणु
			हाल 44100: sbits |= IEC958_AES0_PRO_FS_44100; अवरोध;
			हाल 48000: sbits |= IEC958_AES0_PRO_FS_48000; अवरोध;
			हाल 32000: sbits |= IEC958_AES0_PRO_FS_32000; अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			sbits &= ~(IEC958_AES3_CON_FS << 24);
			चयन (rate) अणु
			हाल 44100: sbits |= IEC958_AES3_CON_FS_44100<<24; अवरोध;
			हाल 48000: sbits |= IEC958_AES3_CON_FS_48000<<24; अवरोध;
			हाल 32000: sbits |= IEC958_AES3_CON_FS_32000<<24; अवरोध;
			पूर्ण
		पूर्ण
		ac97->spdअगर_status = sbits;
	पूर्ण
	snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF);
	mutex_unlock(&ac97->reg_mutex);
	वापस 0;
पूर्ण

/**
 * snd_ac97_set_rate - change the rate of the given input/output.
 * @ac97: the ac97 instance
 * @reg: the रेजिस्टर to change
 * @rate: the sample rate to set
 *
 * Changes the rate of the given input/output on the codec.
 * If the codec करोesn't support VAR, the rate must be 48000 (except
 * क्रम SPDIF).
 *
 * The valid रेजिस्टरs are AC97_PMC_MIC_ADC_RATE,
 * AC97_PCM_FRONT_DAC_RATE, AC97_PCM_LR_ADC_RATE.
 * AC97_PCM_SURR_DAC_RATE and AC97_PCM_LFE_DAC_RATE are accepted
 * अगर the codec supports them.
 * AC97_SPDIF is accepted as a pseuकरो रेजिस्टर to modअगरy the SPDIF
 * status bits.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ac97_set_rate(काष्ठा snd_ac97 *ac97, पूर्णांक reg, अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक dbl;
	अचिन्हित पूर्णांक पंचांगp;
	
	dbl = rate > 48000;
	अगर (dbl) अणु
		अगर (!(ac97->flags & AC97_DOUBLE_RATE))
			वापस -EINVAL;
		अगर (reg != AC97_PCM_FRONT_DAC_RATE)
			वापस -EINVAL;
	पूर्ण

	snd_ac97_update_घातer(ac97, reg, 1);
	चयन (reg) अणु
	हाल AC97_PCM_MIC_ADC_RATE:
		अगर ((ac97->regs[AC97_EXTENDED_STATUS] & AC97_EA_VRM) == 0)	/* MIC VRA */
			अगर (rate != 48000)
				वापस -EINVAL;
		अवरोध;
	हाल AC97_PCM_FRONT_DAC_RATE:
	हाल AC97_PCM_LR_ADC_RATE:
		अगर ((ac97->regs[AC97_EXTENDED_STATUS] & AC97_EA_VRA) == 0)	/* VRA */
			अगर (rate != 48000 && rate != 96000)
				वापस -EINVAL;
		अवरोध;
	हाल AC97_PCM_SURR_DAC_RATE:
		अगर (! (ac97->scaps & AC97_SCAP_SURROUND_DAC))
			वापस -EINVAL;
		अवरोध;
	हाल AC97_PCM_LFE_DAC_RATE:
		अगर (! (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC))
			वापस -EINVAL;
		अवरोध;
	हाल AC97_SPDIF:
		/* special हाल */
		वापस set_spdअगर_rate(ac97, rate);
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (dbl)
		rate /= 2;
	पंचांगp = (rate * ac97->bus->घड़ी) / 48000;
	अगर (पंचांगp > 65535)
		वापस -EINVAL;
	अगर ((ac97->ext_id & AC97_EI_DRA) && reg == AC97_PCM_FRONT_DAC_RATE)
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, dbl ? AC97_EA_DRA : 0);
	snd_ac97_update(ac97, reg, पंचांगp & 0xffff);
	snd_ac97_पढ़ो(ac97, reg);
	अगर ((ac97->ext_id & AC97_EI_DRA) && reg == AC97_PCM_FRONT_DAC_RATE) अणु
		/* Intel controllers require द्विगुन rate data to be put in
		 * slots 7+8
		 */
		snd_ac97_update_bits(ac97, AC97_GENERAL_PURPOSE,
				     AC97_GP_DRSS_MASK,
				     dbl ? AC97_GP_DRSS_78 : 0);
		snd_ac97_पढ़ो(ac97, AC97_GENERAL_PURPOSE);
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ac97_set_rate);

अटल अचिन्हित लघु get_pslots(काष्ठा snd_ac97 *ac97, अचिन्हित अक्षर *rate_table, अचिन्हित लघु *spdअगर_slots)
अणु
	अगर (!ac97_is_audio(ac97))
		वापस 0;
	अगर (ac97_is_rev22(ac97) || ac97_can_amap(ac97)) अणु
		अचिन्हित लघु slots = 0;
		अगर (ac97_is_rev22(ac97)) अणु
			/* Note: it's simply emulation of AMAP behaviour */
			u16 es;
			es = ac97->regs[AC97_EXTENDED_ID] &= ~AC97_EI_DACS_SLOT_MASK;
			चयन (ac97->addr) अणु
			हाल 1:
			हाल 2: es |= (1<<AC97_EI_DACS_SLOT_SHIFT); अवरोध;
			हाल 3: es |= (2<<AC97_EI_DACS_SLOT_SHIFT); अवरोध;
			पूर्ण
			snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_ID, es);
		पूर्ण
		चयन (ac97->addr) अणु
		हाल 0:
			slots |= (1<<AC97_SLOT_PCM_LEFT)|(1<<AC97_SLOT_PCM_RIGHT);
			अगर (ac97->scaps & AC97_SCAP_SURROUND_DAC)
				slots |= (1<<AC97_SLOT_PCM_SLEFT)|(1<<AC97_SLOT_PCM_SRIGHT);
			अगर (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC)
				slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
			अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
				अगर (!(ac97->scaps & AC97_SCAP_SURROUND_DAC))
					*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT)|(1<<AC97_SLOT_SPDIF_RIGHT);
				अन्यथा अगर (!(ac97->scaps & AC97_SCAP_CENTER_LFE_DAC))
					*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT1)|(1<<AC97_SLOT_SPDIF_RIGHT1);
				अन्यथा
					*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
			पूर्ण
			*rate_table = 0;
			अवरोध;
		हाल 1:
		हाल 2:
			slots |= (1<<AC97_SLOT_PCM_SLEFT)|(1<<AC97_SLOT_PCM_SRIGHT);
			अगर (ac97->scaps & AC97_SCAP_SURROUND_DAC)
				slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
			अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
				अगर (!(ac97->scaps & AC97_SCAP_SURROUND_DAC))
					*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT1)|(1<<AC97_SLOT_SPDIF_RIGHT1);
				अन्यथा
					*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
			पूर्ण
			*rate_table = 1;
			अवरोध;
		हाल 3:
			slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
			अगर (ac97->ext_id & AC97_EI_SPDIF)
				*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
			*rate_table = 2;
			अवरोध;
		पूर्ण
		वापस slots;
	पूर्ण अन्यथा अणु
		अचिन्हित लघु slots;
		slots = (1<<AC97_SLOT_PCM_LEFT)|(1<<AC97_SLOT_PCM_RIGHT);
		अगर (ac97->scaps & AC97_SCAP_SURROUND_DAC)
			slots |= (1<<AC97_SLOT_PCM_SLEFT)|(1<<AC97_SLOT_PCM_SRIGHT);
		अगर (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC)
			slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
		अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
			अगर (!(ac97->scaps & AC97_SCAP_SURROUND_DAC))
				*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT)|(1<<AC97_SLOT_SPDIF_RIGHT);
			अन्यथा अगर (!(ac97->scaps & AC97_SCAP_CENTER_LFE_DAC))
				*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT1)|(1<<AC97_SLOT_SPDIF_RIGHT1);
			अन्यथा
				*spdअगर_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
		पूर्ण
		*rate_table = 0;
		वापस slots;
	पूर्ण
पूर्ण

अटल अचिन्हित लघु get_cslots(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित लघु slots;

	अगर (!ac97_is_audio(ac97))
		वापस 0;
	slots = (1<<AC97_SLOT_PCM_LEFT)|(1<<AC97_SLOT_PCM_RIGHT);
	slots |= (1<<AC97_SLOT_MIC);
	वापस slots;
पूर्ण

अटल अचिन्हित पूर्णांक get_rates(काष्ठा ac97_pcm *pcm, अचिन्हित पूर्णांक cidx, अचिन्हित लघु slots, पूर्णांक dbl)
अणु
	पूर्णांक i, idx;
	अचिन्हित पूर्णांक rates = ~0;
	अचिन्हित अक्षर reg;

	क्रम (i = 3; i < 12; i++) अणु
		अगर (!(slots & (1 << i)))
			जारी;
		reg = get_slot_reg(pcm, cidx, i, dbl);
		चयन (reg) अणु
		हाल AC97_PCM_FRONT_DAC_RATE:	idx = AC97_RATES_FRONT_DAC; अवरोध;
		हाल AC97_PCM_SURR_DAC_RATE:	idx = AC97_RATES_SURR_DAC; अवरोध;
		हाल AC97_PCM_LFE_DAC_RATE:	idx = AC97_RATES_LFE_DAC; अवरोध;
		हाल AC97_PCM_LR_ADC_RATE:	idx = AC97_RATES_ADC; अवरोध;
		हाल AC97_PCM_MIC_ADC_RATE:	idx = AC97_RATES_MIC_ADC; अवरोध;
		शेष:			idx = AC97_RATES_SPDIF; अवरोध;
		पूर्ण
		rates &= pcm->r[dbl].codec[cidx]->rates[idx];
	पूर्ण
	अगर (!dbl)
		rates &= ~(SNDRV_PCM_RATE_64000 | SNDRV_PCM_RATE_88200 |
			   SNDRV_PCM_RATE_96000);
	वापस rates;
पूर्ण

/**
 * snd_ac97_pcm_assign - assign AC97 slots to given PCM streams
 * @bus: the ac97 bus instance
 * @pcms_count: count of PCMs to be asचिन्हित
 * @pcms: PCMs to be asचिन्हित
 *
 * It assigns available AC97 slots क्रम given PCMs. If none or only
 * some slots are available, pcm->xxx.slots and pcm->xxx.rslots[] members
 * are reduced and might be zero.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ac97_pcm_assign(काष्ठा snd_ac97_bus *bus,
			अचिन्हित लघु pcms_count,
			स्थिर काष्ठा ac97_pcm *pcms)
अणु
	पूर्णांक i, j, k;
	स्थिर काष्ठा ac97_pcm *pcm;
	काष्ठा ac97_pcm *rpcms, *rpcm;
	अचिन्हित लघु avail_slots[2][4];
	अचिन्हित अक्षर rate_table[2][4];
	अचिन्हित लघु पंचांगp, slots;
	अचिन्हित लघु spdअगर_slots[4];
	अचिन्हित पूर्णांक rates;
	काष्ठा snd_ac97 *codec;

	rpcms = kसुस्मृति(pcms_count, माप(काष्ठा ac97_pcm), GFP_KERNEL);
	अगर (rpcms == शून्य)
		वापस -ENOMEM;
	स_रखो(avail_slots, 0, माप(avail_slots));
	स_रखो(rate_table, 0, माप(rate_table));
	स_रखो(spdअगर_slots, 0, माप(spdअगर_slots));
	क्रम (i = 0; i < 4; i++) अणु
		codec = bus->codec[i];
		अगर (!codec)
			जारी;
		avail_slots[0][i] = get_pslots(codec, &rate_table[0][i], &spdअगर_slots[i]);
		avail_slots[1][i] = get_cslots(codec);
		अगर (!(codec->scaps & AC97_SCAP_INDEP_SDIN)) अणु
			क्रम (j = 0; j < i; j++) अणु
				अगर (bus->codec[j])
					avail_slots[1][i] &= ~avail_slots[1][j];
			पूर्ण
		पूर्ण
	पूर्ण
	/* first step - exclusive devices */
	क्रम (i = 0; i < pcms_count; i++) अणु
		pcm = &pcms[i];
		rpcm = &rpcms[i];
		/* low-level driver thinks that it's more clever */
		अगर (pcm->copy_flag) अणु
			*rpcm = *pcm;
			जारी;
		पूर्ण
		rpcm->stream = pcm->stream;
		rpcm->exclusive = pcm->exclusive;
		rpcm->spdअगर = pcm->spdअगर;
		rpcm->निजी_value = pcm->निजी_value;
		rpcm->bus = bus;
		rpcm->rates = ~0;
		slots = pcm->r[0].slots;
		क्रम (j = 0; j < 4 && slots; j++) अणु
			अगर (!bus->codec[j])
				जारी;
			rates = ~0;
			अगर (pcm->spdअगर && pcm->stream == 0)
				पंचांगp = spdअगर_slots[j];
			अन्यथा
				पंचांगp = avail_slots[pcm->stream][j];
			अगर (pcm->exclusive) अणु
				/* exclusive access */
				पंचांगp &= slots;
				क्रम (k = 0; k < i; k++) अणु
					अगर (rpcm->stream == rpcms[k].stream)
						पंचांगp &= ~rpcms[k].r[0].rslots[j];
				पूर्ण
			पूर्ण अन्यथा अणु
				/* non-exclusive access */
				पंचांगp &= pcm->r[0].slots;
			पूर्ण
			अगर (पंचांगp) अणु
				rpcm->r[0].rslots[j] = पंचांगp;
				rpcm->r[0].codec[j] = bus->codec[j];
				rpcm->r[0].rate_table[j] = rate_table[pcm->stream][j];
				अगर (bus->no_vra)
					rates = SNDRV_PCM_RATE_48000;
				अन्यथा
					rates = get_rates(rpcm, j, पंचांगp, 0);
				अगर (pcm->exclusive)
					avail_slots[pcm->stream][j] &= ~पंचांगp;
			पूर्ण
			slots &= ~पंचांगp;
			rpcm->r[0].slots |= पंचांगp;
			rpcm->rates &= rates;
		पूर्ण
		/* क्रम द्विगुन rate, we check the first codec only */
		अगर (pcm->stream == SNDRV_PCM_STREAM_PLAYBACK &&
		    bus->codec[0] && (bus->codec[0]->flags & AC97_DOUBLE_RATE) &&
		    rate_table[pcm->stream][0] == 0) अणु
			पंचांगp = (1<<AC97_SLOT_PCM_LEFT) | (1<<AC97_SLOT_PCM_RIGHT) |
			      (1<<AC97_SLOT_PCM_LEFT_0) | (1<<AC97_SLOT_PCM_RIGHT_0);
			अगर ((पंचांगp & pcm->r[1].slots) == पंचांगp) अणु
				rpcm->r[1].slots = पंचांगp;
				rpcm->r[1].rslots[0] = पंचांगp;
				rpcm->r[1].rate_table[0] = 0;
				rpcm->r[1].codec[0] = bus->codec[0];
				अगर (pcm->exclusive)
					avail_slots[pcm->stream][0] &= ~पंचांगp;
				अगर (bus->no_vra)
					rates = SNDRV_PCM_RATE_96000;
				अन्यथा
					rates = get_rates(rpcm, 0, पंचांगp, 1);
				rpcm->rates |= rates;
			पूर्ण
		पूर्ण
		अगर (rpcm->rates == ~0)
			rpcm->rates = 0; /* not used */
	पूर्ण
	bus->pcms_count = pcms_count;
	bus->pcms = rpcms;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ac97_pcm_assign);

/**
 * snd_ac97_pcm_खोलो - खोलोs the given AC97 pcm
 * @pcm: the ac97 pcm instance
 * @rate: rate in Hz, अगर codec करोes not support VRA, this value must be 48000Hz
 * @cfg: output stream अक्षरacteristics
 * @slots: a subset of allocated slots (snd_ac97_pcm_assign) क्रम this pcm
 *
 * It locks the specअगरied slots and sets the given rate to AC97 रेजिस्टरs.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ac97_pcm_खोलो(काष्ठा ac97_pcm *pcm, अचिन्हित पूर्णांक rate,
		      क्रमागत ac97_pcm_cfg cfg, अचिन्हित लघु slots)
अणु
	काष्ठा snd_ac97_bus *bus;
	पूर्णांक i, cidx, r, ok_flag;
	अचिन्हित पूर्णांक reg_ok[4] = अणु0,0,0,0पूर्ण;
	अचिन्हित अक्षर reg;
	पूर्णांक err = 0;

	r = rate > 48000;
	bus = pcm->bus;
	अगर (cfg == AC97_PCM_CFG_SPDIF) अणु
		क्रम (cidx = 0; cidx < 4; cidx++)
			अगर (bus->codec[cidx] && (bus->codec[cidx]->ext_id & AC97_EI_SPDIF)) अणु
				err = set_spdअगर_rate(bus->codec[cidx], rate);
				अगर (err < 0)
					वापस err;
			पूर्ण
	पूर्ण
	spin_lock_irq(&pcm->bus->bus_lock);
	क्रम (i = 3; i < 12; i++) अणु
		अगर (!(slots & (1 << i)))
			जारी;
		ok_flag = 0;
		क्रम (cidx = 0; cidx < 4; cidx++) अणु
			अगर (bus->used_slots[pcm->stream][cidx] & (1 << i)) अणु
				spin_unlock_irq(&pcm->bus->bus_lock);
				err = -EBUSY;
				जाओ error;
			पूर्ण
			अगर (pcm->r[r].rslots[cidx] & (1 << i)) अणु
				bus->used_slots[pcm->stream][cidx] |= (1 << i);
				ok_flag++;
			पूर्ण
		पूर्ण
		अगर (!ok_flag) अणु
			spin_unlock_irq(&pcm->bus->bus_lock);
			dev_err(bus->card->dev,
				"cannot find configuration for AC97 slot %i\n",
				i);
			err = -EAGAIN;
			जाओ error;
		पूर्ण
	पूर्ण
	pcm->cur_dbl = r;
	spin_unlock_irq(&pcm->bus->bus_lock);
	क्रम (i = 3; i < 12; i++) अणु
		अगर (!(slots & (1 << i)))
			जारी;
		क्रम (cidx = 0; cidx < 4; cidx++) अणु
			अगर (pcm->r[r].rslots[cidx] & (1 << i)) अणु
				reg = get_slot_reg(pcm, cidx, i, r);
				अगर (reg == 0xff) अणु
					dev_err(bus->card->dev,
						"invalid AC97 slot %i?\n", i);
					जारी;
				पूर्ण
				अगर (reg_ok[cidx] & (1 << (reg - AC97_PCM_FRONT_DAC_RATE)))
					जारी;
				dev_dbg(bus->card->dev,
					"setting ac97 reg 0x%x to rate %d\n",
					reg, rate);
				err = snd_ac97_set_rate(pcm->r[r].codec[cidx], reg, rate);
				अगर (err < 0)
					dev_err(bus->card->dev,
						"error in snd_ac97_set_rate: cidx=%d, reg=0x%x, rate=%d, err=%d\n",
						cidx, reg, rate, err);
				अन्यथा
					reg_ok[cidx] |= (1 << (reg - AC97_PCM_FRONT_DAC_RATE));
			पूर्ण
		पूर्ण
	पूर्ण
	pcm->aslots = slots;
	वापस 0;

 error:
	pcm->aslots = slots;
	snd_ac97_pcm_बंद(pcm);
	वापस err;
पूर्ण

EXPORT_SYMBOL(snd_ac97_pcm_खोलो);

/**
 * snd_ac97_pcm_बंद - बंदs the given AC97 pcm
 * @pcm: the ac97 pcm instance
 *
 * It मुक्तs the locked AC97 slots.
 *
 * Return: Zero.
 */
पूर्णांक snd_ac97_pcm_बंद(काष्ठा ac97_pcm *pcm)
अणु
	काष्ठा snd_ac97_bus *bus;
	अचिन्हित लघु slots = pcm->aslots;
	पूर्णांक i, cidx;

#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
	पूर्णांक r = pcm->cur_dbl;
	क्रम (i = 3; i < 12; i++) अणु
		अगर (!(slots & (1 << i)))
			जारी;
		क्रम (cidx = 0; cidx < 4; cidx++) अणु
			अगर (pcm->r[r].rslots[cidx] & (1 << i)) अणु
				पूर्णांक reg = get_slot_reg(pcm, cidx, i, r);
				snd_ac97_update_घातer(pcm->r[r].codec[cidx],
						      reg, 0);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	bus = pcm->bus;
	spin_lock_irq(&pcm->bus->bus_lock);
	क्रम (i = 3; i < 12; i++) अणु
		अगर (!(slots & (1 << i)))
			जारी;
		क्रम (cidx = 0; cidx < 4; cidx++)
			bus->used_slots[pcm->stream][cidx] &= ~(1 << i);
	पूर्ण
	pcm->aslots = 0;
	pcm->cur_dbl = 0;
	spin_unlock_irq(&pcm->bus->bus_lock);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ac97_pcm_बंद);

अटल पूर्णांक द्विगुन_rate_hw_स्थिरraपूर्णांक_rate(काष्ठा snd_pcm_hw_params *params,
					  काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	अगर (channels->min > 2) अणु
		अटल स्थिर काष्ठा snd_पूर्णांकerval single_rates = अणु
			.min = 1,
			.max = 48000,
		पूर्ण;
		काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
		वापस snd_पूर्णांकerval_refine(rate, &single_rates);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक द्विगुन_rate_hw_स्थिरraपूर्णांक_channels(काष्ठा snd_pcm_hw_params *params,
					      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (rate->min > 48000) अणु
		अटल स्थिर काष्ठा snd_पूर्णांकerval द्विगुन_rate_channels = अणु
			.min = 2,
			.max = 2,
		पूर्ण;
		काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
		वापस snd_पूर्णांकerval_refine(channels, &द्विगुन_rate_channels);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * snd_ac97_pcm_द्विगुन_rate_rules - set द्विगुन rate स्थिरraपूर्णांकs
 * @runसमय: the runसमय of the ac97 front playback pcm
 *
 * Installs the hardware स्थिरraपूर्णांक rules to prevent using द्विगुन rates and
 * more than two channels at the same समय.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ac97_pcm_द्विगुन_rate_rules(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक err;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  द्विगुन_rate_hw_स्थिरraपूर्णांक_rate, शून्य,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  द्विगुन_rate_hw_स्थिरraपूर्णांक_channels, शून्य,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	वापस err;
पूर्ण

EXPORT_SYMBOL(snd_ac97_pcm_द्विगुन_rate_rules);
