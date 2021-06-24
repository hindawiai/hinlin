<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Midi synth routines क्रम the Emu8k/Emu10k1
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Contains code based on awe_wave.c by Takashi Iwai
 */

#समावेश "emux_voice.h"
#समावेश <linux/slab.h>

#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
/*
 * effects table
 */

#घोषणा xदुरत्व(type,tag)	((दीर्घ)(&((type)शून्य)->tag) - (दीर्घ)(शून्य))

#घोषणा parm_offset(tag)	xदुरत्व(काष्ठा soundfont_voice_parm *, tag)

#घोषणा PARM_IS_BYTE		(1 << 0)
#घोषणा PARM_IS_WORD		(1 << 1)
#घोषणा PARM_IS_ALIGNED		(3 << 2)
#घोषणा PARM_IS_ALIGN_HI	(1 << 2)
#घोषणा PARM_IS_ALIGN_LO	(2 << 2)
#घोषणा PARM_IS_SIGNED		(1 << 4)

#घोषणा PARM_WORD	(PARM_IS_WORD)
#घोषणा PARM_BYTE_LO	(PARM_IS_BYTE|PARM_IS_ALIGN_LO)
#घोषणा PARM_BYTE_HI	(PARM_IS_BYTE|PARM_IS_ALIGN_HI)
#घोषणा PARM_BYTE	(PARM_IS_BYTE)
#घोषणा PARM_SIGN_LO	(PARM_IS_BYTE|PARM_IS_ALIGN_LO|PARM_IS_SIGNED)
#घोषणा PARM_SIGN_HI	(PARM_IS_BYTE|PARM_IS_ALIGN_HI|PARM_IS_SIGNED)

अटल काष्ठा emux_parm_defs अणु
	पूर्णांक type;	/* byte or word */
	पूर्णांक low, high;	/* value range */
	दीर्घ offset;	/* offset in parameter record (-1 = not written) */
	पूर्णांक update;	/* flgas क्रम real-समय update */
पूर्ण parm_defs[EMUX_NUM_EFFECTS] = अणु
	अणुPARM_WORD, 0, 0x8000, parm_offset(moddelay), 0पूर्ण,	/* env1 delay */
	अणुPARM_BYTE_LO, 1, 0x80, parm_offset(modatkhld), 0पूर्ण,	/* env1 attack */
	अणुPARM_BYTE_HI, 0, 0x7e, parm_offset(modatkhld), 0पूर्ण,	/* env1 hold */
	अणुPARM_BYTE_LO, 1, 0x7f, parm_offset(moddcysus), 0पूर्ण,	/* env1 decay */
	अणुPARM_BYTE_LO, 1, 0x7f, parm_offset(modrelease), 0पूर्ण,	/* env1 release */
	अणुPARM_BYTE_HI, 0, 0x7f, parm_offset(moddcysus), 0पूर्ण,	/* env1 sustain */
	अणुPARM_BYTE_HI, 0, 0xff, parm_offset(pefe), 0पूर्ण,	/* env1 pitch */
	अणुPARM_BYTE_LO, 0, 0xff, parm_offset(pefe), 0पूर्ण,	/* env1 fc */

	अणुPARM_WORD, 0, 0x8000, parm_offset(voldelay), 0पूर्ण,	/* env2 delay */
	अणुPARM_BYTE_LO, 1, 0x80, parm_offset(volatkhld), 0पूर्ण,	/* env2 attack */
	अणुPARM_BYTE_HI, 0, 0x7e, parm_offset(volatkhld), 0पूर्ण,	/* env2 hold */
	अणुPARM_BYTE_LO, 1, 0x7f, parm_offset(voldcysus), 0पूर्ण,	/* env2 decay */
	अणुPARM_BYTE_LO, 1, 0x7f, parm_offset(volrelease), 0पूर्ण,	/* env2 release */
	अणुPARM_BYTE_HI, 0, 0x7f, parm_offset(voldcysus), 0पूर्ण,	/* env2 sustain */

	अणुPARM_WORD, 0, 0x8000, parm_offset(lfo1delay), 0पूर्ण,	/* lfo1 delay */
	अणुPARM_BYTE_LO, 0, 0xff, parm_offset(tremfrq), SNDRV_EMUX_UPDATE_TREMFREQपूर्ण,	/* lfo1 freq */
	अणुPARM_SIGN_HI, -128, 127, parm_offset(tremfrq), SNDRV_EMUX_UPDATE_TREMFREQपूर्ण,	/* lfo1 vol */
	अणुPARM_SIGN_HI, -128, 127, parm_offset(fmmod), SNDRV_EMUX_UPDATE_FMMODपूर्ण,	/* lfo1 pitch */
	अणुPARM_BYTE_LO, 0, 0xff, parm_offset(fmmod), SNDRV_EMUX_UPDATE_FMMODपूर्ण,	/* lfo1 cutoff */

	अणुPARM_WORD, 0, 0x8000, parm_offset(lfo2delay), 0पूर्ण,	/* lfo2 delay */
	अणुPARM_BYTE_LO, 0, 0xff, parm_offset(fm2frq2), SNDRV_EMUX_UPDATE_FM2FRQ2पूर्ण,	/* lfo2 freq */
	अणुPARM_SIGN_HI, -128, 127, parm_offset(fm2frq2), SNDRV_EMUX_UPDATE_FM2FRQ2पूर्ण,	/* lfo2 pitch */

	अणुPARM_WORD, 0, 0xffff, -1, SNDRV_EMUX_UPDATE_PITCHपूर्ण,	/* initial pitch */
	अणुPARM_BYTE, 0, 0xff, parm_offset(chorus), 0पूर्ण,	/* chorus */
	अणुPARM_BYTE, 0, 0xff, parm_offset(reverb), 0पूर्ण,	/* reverb */
	अणुPARM_BYTE, 0, 0xff, parm_offset(cutoff), SNDRV_EMUX_UPDATE_VOLUMEपूर्ण,	/* cutoff */
	अणुPARM_BYTE, 0, 15, parm_offset(filterQ), SNDRV_EMUX_UPDATE_Qपूर्ण,	/* resonance */

	अणुPARM_WORD, 0, 0xffff, -1, 0पूर्ण,	/* sample start */
	अणुPARM_WORD, 0, 0xffff, -1, 0पूर्ण,	/* loop start */
	अणुPARM_WORD, 0, 0xffff, -1, 0पूर्ण,	/* loop end */
	अणुPARM_WORD, 0, 0xffff, -1, 0पूर्ण,	/* coarse sample start */
	अणुPARM_WORD, 0, 0xffff, -1, 0पूर्ण,	/* coarse loop start */
	अणुPARM_WORD, 0, 0xffff, -1, 0पूर्ण,	/* coarse loop end */
	अणुPARM_BYTE, 0, 0xff, -1, SNDRV_EMUX_UPDATE_VOLUMEपूर्ण,	/* initial attenuation */
पूर्ण;

/* set byte effect value */
अटल व्योम
effect_set_byte(अचिन्हित अक्षर *valp, काष्ठा snd_midi_channel *chan, पूर्णांक type)
अणु
	लघु effect;
	काष्ठा snd_emux_effect_table *fx = chan->निजी;

	effect = fx->val[type];
	अगर (fx->flag[type] == EMUX_FX_FLAG_ADD) अणु
		अगर (parm_defs[type].type & PARM_IS_SIGNED)
			effect += *(अक्षर*)valp;
		अन्यथा
			effect += *valp;
	पूर्ण
	अगर (effect < parm_defs[type].low)
		effect = parm_defs[type].low;
	अन्यथा अगर (effect > parm_defs[type].high)
		effect = parm_defs[type].high;
	*valp = (अचिन्हित अक्षर)effect;
पूर्ण

/* set word effect value */
अटल व्योम
effect_set_word(अचिन्हित लघु *valp, काष्ठा snd_midi_channel *chan, पूर्णांक type)
अणु
	पूर्णांक effect;
	काष्ठा snd_emux_effect_table *fx = chan->निजी;

	effect = *(अचिन्हित लघु*)&fx->val[type];
	अगर (fx->flag[type] == EMUX_FX_FLAG_ADD)
		effect += *valp;
	अगर (effect < parm_defs[type].low)
		effect = parm_defs[type].low;
	अन्यथा अगर (effect > parm_defs[type].high)
		effect = parm_defs[type].high;
	*valp = (अचिन्हित लघु)effect;
पूर्ण

/* address offset */
अटल पूर्णांक
effect_get_offset(काष्ठा snd_midi_channel *chan, पूर्णांक lo, पूर्णांक hi, पूर्णांक mode)
अणु
	पूर्णांक addr = 0;
	काष्ठा snd_emux_effect_table *fx = chan->निजी;

	अगर (fx->flag[hi])
		addr = (लघु)fx->val[hi];
	addr = addr << 15;
	अगर (fx->flag[lo])
		addr += (लघु)fx->val[lo];
	अगर (!(mode & SNDRV_SFNT_SAMPLE_8BITS))
		addr /= 2;
	वापस addr;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
/* change effects - क्रम OSS sequencer compatibility */
व्योम
snd_emux_send_effect_oss(काष्ठा snd_emux_port *port,
			 काष्ठा snd_midi_channel *chan, पूर्णांक type, पूर्णांक val)
अणु
	पूर्णांक mode;

	अगर (type & 0x40)
		mode = EMUX_FX_FLAG_OFF;
	अन्यथा अगर (type & 0x80)
		mode = EMUX_FX_FLAG_ADD;
	अन्यथा
		mode = EMUX_FX_FLAG_SET;
	type &= 0x3f;

	snd_emux_send_effect(port, chan, type, val, mode);
पूर्ण
#पूर्ण_अगर

/* Modअगरy the effect value.
 * अगर update is necessary, call emu8000_control
 */
व्योम
snd_emux_send_effect(काष्ठा snd_emux_port *port, काष्ठा snd_midi_channel *chan,
		     पूर्णांक type, पूर्णांक val, पूर्णांक mode)
अणु
	पूर्णांक i;
	पूर्णांक offset;
	अचिन्हित अक्षर *srcp, *origp;
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_effect_table *fx;
	अचिन्हित दीर्घ flags;

	emu = port->emu;
	fx = chan->निजी;
	अगर (emu == शून्य || fx == शून्य)
		वापस;
	अगर (type < 0 || type >= EMUX_NUM_EFFECTS)
		वापस;

	fx->val[type] = val;
	fx->flag[type] = mode;

	/* करो we need to modअगरy the रेजिस्टर in realसमय ? */
	अगर (! parm_defs[type].update || (offset = parm_defs[type].offset) < 0)
		वापस;

#अगर_घोषित SNDRV_LITTLE_ENDIAN
	अगर (parm_defs[type].type & PARM_IS_ALIGN_HI)
		offset++;
#अन्यथा
	अगर (parm_defs[type].type & PARM_IS_ALIGN_LO)
		offset++;
#पूर्ण_अगर
	/* modअगरy the रेजिस्टर values */
	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		काष्ठा snd_emux_voice *vp = &emu->voices[i];
		अगर (!STATE_IS_PLAYING(vp->state) || vp->chan != chan)
			जारी;
		srcp = (अचिन्हित अक्षर*)&vp->reg.parm + offset;
		origp = (अचिन्हित अक्षर*)&vp->zone->v.parm + offset;
		अगर (parm_defs[i].type & PARM_IS_BYTE) अणु
			*srcp = *origp;
			effect_set_byte(srcp, chan, type);
		पूर्ण अन्यथा अणु
			*(अचिन्हित लघु*)srcp = *(अचिन्हित लघु*)origp;
			effect_set_word((अचिन्हित लघु*)srcp, chan, type);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);

	/* activate them */
	snd_emux_update_channel(port, chan, parm_defs[type].update);
पूर्ण


/* copy wavetable रेजिस्टरs to voice table */
व्योम
snd_emux_setup_effect(काष्ठा snd_emux_voice *vp)
अणु
	काष्ठा snd_midi_channel *chan = vp->chan;
	काष्ठा snd_emux_effect_table *fx;
	अचिन्हित अक्षर *srcp;
	पूर्णांक i;

	अगर (! (fx = chan->निजी))
		वापस;

	/* modअगरy the रेजिस्टर values via effect table */
	क्रम (i = 0; i < EMUX_FX_END; i++) अणु
		पूर्णांक offset;
		अगर (! fx->flag[i] || (offset = parm_defs[i].offset) < 0)
			जारी;
#अगर_घोषित SNDRV_LITTLE_ENDIAN
		अगर (parm_defs[i].type & PARM_IS_ALIGN_HI)
			offset++;
#अन्यथा
		अगर (parm_defs[i].type & PARM_IS_ALIGN_LO)
			offset++;
#पूर्ण_अगर
		srcp = (अचिन्हित अक्षर*)&vp->reg.parm + offset;
		अगर (parm_defs[i].type & PARM_IS_BYTE)
			effect_set_byte(srcp, chan, i);
		अन्यथा
			effect_set_word((अचिन्हित लघु*)srcp, chan, i);
	पूर्ण

	/* correct sample and loop poपूर्णांकs */
	vp->reg.start += effect_get_offset(chan, EMUX_FX_SAMPLE_START,
					   EMUX_FX_COARSE_SAMPLE_START,
					   vp->reg.sample_mode);

	vp->reg.loopstart += effect_get_offset(chan, EMUX_FX_LOOP_START,
					       EMUX_FX_COARSE_LOOP_START,
					       vp->reg.sample_mode);

	vp->reg.loखोलोd += effect_get_offset(chan, EMUX_FX_LOOP_END,
					     EMUX_FX_COARSE_LOOP_END,
					     vp->reg.sample_mode);
पूर्ण

/*
 * effect table
 */
व्योम
snd_emux_create_effect(काष्ठा snd_emux_port *p)
अणु
	पूर्णांक i;
	p->effect = kसुस्मृति(p->chset.max_channels,
			    माप(काष्ठा snd_emux_effect_table), GFP_KERNEL);
	अगर (p->effect) अणु
		क्रम (i = 0; i < p->chset.max_channels; i++)
			p->chset.channels[i].निजी = p->effect + i;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < p->chset.max_channels; i++)
			p->chset.channels[i].निजी = शून्य;
	पूर्ण
पूर्ण

व्योम
snd_emux_delete_effect(काष्ठा snd_emux_port *p)
अणु
	kमुक्त(p->effect);
	p->effect = शून्य;
पूर्ण

व्योम
snd_emux_clear_effect(काष्ठा snd_emux_port *p)
अणु
	अगर (p->effect) अणु
		स_रखो(p->effect, 0, माप(काष्ठा snd_emux_effect_table) *
		       p->chset.max_channels);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* SNDRV_EMUX_USE_RAW_EFFECT */
