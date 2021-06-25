<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम Sound Blaster mixer control
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>
#समावेश <sound/control.h>

#अघोषित IO_DEBUG

व्योम snd_sbmixer_ग_लिखो(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	outb(reg, SBP(chip, MIXER_ADDR));
	udelay(10);
	outb(data, SBP(chip, MIXER_DATA));
	udelay(10);
#अगर_घोषित IO_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "mixer_write 0x%x 0x%x\n", reg, data);
#पूर्ण_अगर
पूर्ण

अचिन्हित अक्षर snd_sbmixer_पढ़ो(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर result;

	outb(reg, SBP(chip, MIXER_ADDR));
	udelay(10);
	result = inb(SBP(chip, MIXER_DATA));
	udelay(10);
#अगर_घोषित IO_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "mixer_read 0x%x 0x%x\n", reg, result);
#पूर्ण_अगर
	वापस result;
पूर्ण

/*
 * Single channel mixer element
 */

अटल पूर्णांक snd_sbmixer_info_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sbmixer_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	अचिन्हित अक्षर val;

	spin_lock_irqsave(&sb->mixer_lock, flags);
	val = (snd_sbmixer_पढ़ो(sb, reg) >> shअगरt) & mask;
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sbmixer_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित अक्षर val, oval;

	val = (ucontrol->value.पूर्णांकeger.value[0] & mask) << shअगरt;
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_पढ़ो(sb, reg);
	val = (oval & ~(mask << shअगरt)) | val;
	change = val != oval;
	अगर (change)
		snd_sbmixer_ग_लिखो(sb, reg, val);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	वापस change;
पूर्ण

/*
 * Double channel mixer element
 */

अटल पूर्णांक snd_sbmixer_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sbmixer_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	अचिन्हित अक्षर left, right;

	spin_lock_irqsave(&sb->mixer_lock, flags);
	left = (snd_sbmixer_पढ़ो(sb, left_reg) >> left_shअगरt) & mask;
	right = (snd_sbmixer_पढ़ो(sb, right_reg) >> right_shअगरt) & mask;
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = left;
	ucontrol->value.पूर्णांकeger.value[1] = right;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sbmixer_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित अक्षर left, right, oleft, oright;

	left = (ucontrol->value.पूर्णांकeger.value[0] & mask) << left_shअगरt;
	right = (ucontrol->value.पूर्णांकeger.value[1] & mask) << right_shअगरt;
	spin_lock_irqsave(&sb->mixer_lock, flags);
	अगर (left_reg == right_reg) अणु
		oleft = snd_sbmixer_पढ़ो(sb, left_reg);
		left = (oleft & ~((mask << left_shअगरt) | (mask << right_shअगरt))) | left | right;
		change = left != oleft;
		अगर (change)
			snd_sbmixer_ग_लिखो(sb, left_reg, left);
	पूर्ण अन्यथा अणु
		oleft = snd_sbmixer_पढ़ो(sb, left_reg);
		oright = snd_sbmixer_पढ़ो(sb, right_reg);
		left = (oleft & ~(mask << left_shअगरt)) | left;
		right = (oright & ~(mask << right_shअगरt)) | right;
		change = left != oleft || right != oright;
		अगर (change) अणु
			snd_sbmixer_ग_लिखो(sb, left_reg, left);
			snd_sbmixer_ग_लिखो(sb, right_reg, right);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	वापस change;
पूर्ण

/*
 * DT-019x / ALS-007 capture/input चयन
 */

अटल पूर्णांक snd_dt019x_input_sw_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[5] = अणु
		"CD", "Mic", "Line", "Synth", "Master"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 5, texts);
पूर्ण

अटल पूर्णांक snd_dt019x_input_sw_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर oval;
	
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_पढ़ो(sb, SB_DT019X_CAPTURE_SW);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	चयन (oval & 0x07) अणु
	हाल SB_DT019X_CAP_CD:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	हाल SB_DT019X_CAP_MIC:
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	हाल SB_DT019X_CAP_LINE:
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	हाल SB_DT019X_CAP_MAIN:
		ucontrol->value.क्रमागतerated.item[0] = 4;
		अवरोध;
	/* To record the synth on these cards you must record the मुख्य.   */
	/* Thus SB_DT019X_CAP_SYNTH == SB_DT019X_CAP_MAIN and would cause */
	/* duplicate हाल labels अगर left uncommented. */
	/* हाल SB_DT019X_CAP_SYNTH:
	 *	ucontrol->value.क्रमागतerated.item[0] = 3;
	 *	अवरोध;
	 */
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 4;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_dt019x_input_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित अक्षर nval, oval;
	
	अगर (ucontrol->value.क्रमागतerated.item[0] > 4)
		वापस -EINVAL;
	चयन (ucontrol->value.क्रमागतerated.item[0]) अणु
	हाल 0:
		nval = SB_DT019X_CAP_CD;
		अवरोध;
	हाल 1:
		nval = SB_DT019X_CAP_MIC;
		अवरोध;
	हाल 2:
		nval = SB_DT019X_CAP_LINE;
		अवरोध;
	हाल 3:
		nval = SB_DT019X_CAP_SYNTH;
		अवरोध;
	हाल 4:
		nval = SB_DT019X_CAP_MAIN;
		अवरोध;
	शेष:
		nval = SB_DT019X_CAP_MAIN;
	पूर्ण
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_पढ़ो(sb, SB_DT019X_CAPTURE_SW);
	change = nval != oval;
	अगर (change)
		snd_sbmixer_ग_लिखो(sb, SB_DT019X_CAPTURE_SW, nval);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	वापस change;
पूर्ण

/*
 * ALS4000 mono recording control चयन
 */

अटल पूर्णांक snd_als4k_mono_capture_route_info(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"L chan only", "R chan only", "L ch/2 + R ch/2"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_als4k_mono_capture_route_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर oval;

	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_पढ़ो(sb, SB_ALS4000_MONO_IO_CTRL);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	oval >>= 6;
	अगर (oval > 2)
		oval = 2;

	ucontrol->value.क्रमागतerated.item[0] = oval;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als4k_mono_capture_route_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित अक्षर nval, oval;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_पढ़ो(sb, SB_ALS4000_MONO_IO_CTRL);

	nval = (oval & ~(3 << 6))
	     | (ucontrol->value.क्रमागतerated.item[0] << 6);
	change = nval != oval;
	अगर (change)
		snd_sbmixer_ग_लिखो(sb, SB_ALS4000_MONO_IO_CTRL, nval);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	वापस change;
पूर्ण

/*
 * SBPRO input multiplexer
 */

अटल पूर्णांक snd_sb8mixer_info_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"Mic", "CD", "Line"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण


अटल पूर्णांक snd_sb8mixer_get_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर oval;
	
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_पढ़ो(sb, SB_DSP_CAPTURE_SOURCE);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	चयन ((oval >> 0x01) & 0x03) अणु
	हाल SB_DSP_MIXS_CD:
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	हाल SB_DSP_MIXS_LINE:
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8mixer_put_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित अक्षर nval, oval;
	
	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	चयन (ucontrol->value.क्रमागतerated.item[0]) अणु
	हाल 1:
		nval = SB_DSP_MIXS_CD;
		अवरोध;
	हाल 2:
		nval = SB_DSP_MIXS_LINE;
		अवरोध;
	शेष:
		nval = SB_DSP_MIXS_MIC;
	पूर्ण
	nval <<= 1;
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_पढ़ो(sb, SB_DSP_CAPTURE_SOURCE);
	nval |= oval & ~0x06;
	change = nval != oval;
	अगर (change)
		snd_sbmixer_ग_लिखो(sb, SB_DSP_CAPTURE_SOURCE, nval);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	वापस change;
पूर्ण

/*
 * SB16 input चयन
 */

अटल पूर्णांक snd_sb16mixer_info_input_sw(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 4;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16mixer_get_input_sw(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg1 = kcontrol->निजी_value & 0xff;
	पूर्णांक reg2 = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x0f;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 24) & 0x0f;
	अचिन्हित अक्षर val1, val2;

	spin_lock_irqsave(&sb->mixer_lock, flags);
	val1 = snd_sbmixer_पढ़ो(sb, reg1);
	val2 = snd_sbmixer_पढ़ो(sb, reg2);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (val1 >> left_shअगरt) & 0x01;
	ucontrol->value.पूर्णांकeger.value[1] = (val2 >> left_shअगरt) & 0x01;
	ucontrol->value.पूर्णांकeger.value[2] = (val1 >> right_shअगरt) & 0x01;
	ucontrol->value.पूर्णांकeger.value[3] = (val2 >> right_shअगरt) & 0x01;
	वापस 0;
पूर्ण                                                                                                                   

अटल पूर्णांक snd_sb16mixer_put_input_sw(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *sb = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg1 = kcontrol->निजी_value & 0xff;
	पूर्णांक reg2 = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x0f;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 24) & 0x0f;
	पूर्णांक change;
	अचिन्हित अक्षर val1, val2, oval1, oval2;

	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval1 = snd_sbmixer_पढ़ो(sb, reg1);
	oval2 = snd_sbmixer_पढ़ो(sb, reg2);
	val1 = oval1 & ~((1 << left_shअगरt) | (1 << right_shअगरt));
	val2 = oval2 & ~((1 << left_shअगरt) | (1 << right_shअगरt));
	val1 |= (ucontrol->value.पूर्णांकeger.value[0] & 1) << left_shअगरt;
	val2 |= (ucontrol->value.पूर्णांकeger.value[1] & 1) << left_shअगरt;
	val1 |= (ucontrol->value.पूर्णांकeger.value[2] & 1) << right_shअगरt;
	val2 |= (ucontrol->value.पूर्णांकeger.value[3] & 1) << right_shअगरt;
	change = val1 != oval1 || val2 != oval2;
	अगर (change) अणु
		snd_sbmixer_ग_लिखो(sb, reg1, val1);
		snd_sbmixer_ग_लिखो(sb, reg2, val2);
	पूर्ण
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	वापस change;
पूर्ण


/*
 */
/*
 */
पूर्णांक snd_sbmixer_add_ctl(काष्ठा snd_sb *chip, स्थिर अक्षर *name, पूर्णांक index, पूर्णांक type, अचिन्हित दीर्घ value)
अणु
	अटल स्थिर काष्ठा snd_kcontrol_new newctls[] = अणु
		[SB_MIX_SINGLE] = अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.info = snd_sbmixer_info_single,
			.get = snd_sbmixer_get_single,
			.put = snd_sbmixer_put_single,
		पूर्ण,
		[SB_MIX_DOUBLE] = अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.info = snd_sbmixer_info_द्विगुन,
			.get = snd_sbmixer_get_द्विगुन,
			.put = snd_sbmixer_put_द्विगुन,
		पूर्ण,
		[SB_MIX_INPUT_SW] = अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.info = snd_sb16mixer_info_input_sw,
			.get = snd_sb16mixer_get_input_sw,
			.put = snd_sb16mixer_put_input_sw,
		पूर्ण,
		[SB_MIX_CAPTURE_PRO] = अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.info = snd_sb8mixer_info_mux,
			.get = snd_sb8mixer_get_mux,
			.put = snd_sb8mixer_put_mux,
		पूर्ण,
		[SB_MIX_CAPTURE_DT019X] = अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.info = snd_dt019x_input_sw_info,
			.get = snd_dt019x_input_sw_get,
			.put = snd_dt019x_input_sw_put,
		पूर्ण,
		[SB_MIX_MONO_CAPTURE_ALS4K] = अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.info = snd_als4k_mono_capture_route_info,
			.get = snd_als4k_mono_capture_route_get,
			.put = snd_als4k_mono_capture_route_put,
		पूर्ण,
	पूर्ण;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक err;

	ctl = snd_ctl_new1(&newctls[type], chip);
	अगर (! ctl)
		वापस -ENOMEM;
	strscpy(ctl->id.name, name, माप(ctl->id.name));
	ctl->id.index = index;
	ctl->निजी_value = value;
	अगर ((err = snd_ctl_add(chip->card, ctl)) < 0)
		वापस err;
	वापस 0;
पूर्ण

/*
 * SB 2.0 specअगरic mixer elements
 */

अटल स्थिर काष्ठा sbmix_elem snd_sb20_controls[] = अणु
	SB_SINGLE("Master Playback Volume", SB_DSP20_MASTER_DEV, 1, 7),
	SB_SINGLE("PCM Playback Volume", SB_DSP20_PCM_DEV, 1, 3),
	SB_SINGLE("Synth Playback Volume", SB_DSP20_FM_DEV, 1, 7),
	SB_SINGLE("CD Playback Volume", SB_DSP20_CD_DEV, 1, 7)
पूर्ण;

अटल स्थिर अचिन्हित अक्षर snd_sb20_init_values[][2] = अणु
	अणु SB_DSP20_MASTER_DEV, 0 पूर्ण,
	अणु SB_DSP20_FM_DEV, 0 पूर्ण,
पूर्ण;

/*
 * SB Pro specअगरic mixer elements
 */
अटल स्थिर काष्ठा sbmix_elem snd_sbpro_controls[] = अणु
	SB_DOUBLE("Master Playback Volume",
		  SB_DSP_MASTER_DEV, SB_DSP_MASTER_DEV, 5, 1, 7),
	SB_DOUBLE("PCM Playback Volume",
		  SB_DSP_PCM_DEV, SB_DSP_PCM_DEV, 5, 1, 7),
	SB_SINGLE("PCM Playback Filter", SB_DSP_PLAYBACK_FILT, 5, 1),
	SB_DOUBLE("Synth Playback Volume",
		  SB_DSP_FM_DEV, SB_DSP_FM_DEV, 5, 1, 7),
	SB_DOUBLE("CD Playback Volume", SB_DSP_CD_DEV, SB_DSP_CD_DEV, 5, 1, 7),
	SB_DOUBLE("Line Playback Volume",
		  SB_DSP_LINE_DEV, SB_DSP_LINE_DEV, 5, 1, 7),
	SB_SINGLE("Mic Playback Volume", SB_DSP_MIC_DEV, 1, 3),
	अणु
		.name = "Capture Source",
		.type = SB_MIX_CAPTURE_PRO
	पूर्ण,
	SB_SINGLE("Capture Filter", SB_DSP_CAPTURE_FILT, 5, 1),
	SB_SINGLE("Capture Low-Pass Filter", SB_DSP_CAPTURE_FILT, 3, 1)
पूर्ण;

अटल स्थिर अचिन्हित अक्षर snd_sbpro_init_values[][2] = अणु
	अणु SB_DSP_MASTER_DEV, 0 पूर्ण,
	अणु SB_DSP_PCM_DEV, 0 पूर्ण,
	अणु SB_DSP_FM_DEV, 0 पूर्ण,
पूर्ण;

/*
 * SB16 specअगरic mixer elements
 */
अटल स्थिर काष्ठा sbmix_elem snd_sb16_controls[] = अणु
	SB_DOUBLE("Master Playback Volume",
		  SB_DSP4_MASTER_DEV, (SB_DSP4_MASTER_DEV + 1), 3, 3, 31),
	SB_DOUBLE("PCM Playback Volume",
		  SB_DSP4_PCM_DEV, (SB_DSP4_PCM_DEV + 1), 3, 3, 31),
	SB16_INPUT_SW("Synth Capture Route",
		      SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT, 6, 5),
	SB_DOUBLE("Synth Playback Volume",
		  SB_DSP4_SYNTH_DEV, (SB_DSP4_SYNTH_DEV + 1), 3, 3, 31),
	SB16_INPUT_SW("CD Capture Route",
		      SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT, 2, 1),
	SB_DOUBLE("CD Playback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 2, 1, 1),
	SB_DOUBLE("CD Playback Volume",
		  SB_DSP4_CD_DEV, (SB_DSP4_CD_DEV + 1), 3, 3, 31),
	SB16_INPUT_SW("Mic Capture Route",
		      SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT, 0, 0),
	SB_SINGLE("Mic Playback Switch", SB_DSP4_OUTPUT_SW, 0, 1),
	SB_SINGLE("Mic Playback Volume", SB_DSP4_MIC_DEV, 3, 31),
	SB_SINGLE("Beep Volume", SB_DSP4_SPEAKER_DEV, 6, 3),
	SB_DOUBLE("Capture Volume",
		  SB_DSP4_IGAIN_DEV, (SB_DSP4_IGAIN_DEV + 1), 6, 6, 3),
	SB_DOUBLE("Playback Volume",
		  SB_DSP4_OGAIN_DEV, (SB_DSP4_OGAIN_DEV + 1), 6, 6, 3),
	SB16_INPUT_SW("Line Capture Route",
		      SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT, 4, 3),
	SB_DOUBLE("Line Playback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 4, 3, 1),
	SB_DOUBLE("Line Playback Volume",
		  SB_DSP4_LINE_DEV, (SB_DSP4_LINE_DEV + 1), 3, 3, 31),
	SB_SINGLE("Mic Auto Gain", SB_DSP4_MIC_AGC, 0, 1),
	SB_SINGLE("3D Enhancement Switch", SB_DSP4_3DSE, 0, 1),
	SB_DOUBLE("Tone Control - Bass",
		  SB_DSP4_BASS_DEV, (SB_DSP4_BASS_DEV + 1), 4, 4, 15),
	SB_DOUBLE("Tone Control - Treble",
		  SB_DSP4_TREBLE_DEV, (SB_DSP4_TREBLE_DEV + 1), 4, 4, 15)
पूर्ण;

अटल स्थिर अचिन्हित अक्षर snd_sb16_init_values[][2] = अणु
	अणु SB_DSP4_MASTER_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_MASTER_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_PCM_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_PCM_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_SYNTH_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_SYNTH_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_INPUT_LEFT, 0 पूर्ण,
	अणु SB_DSP4_INPUT_RIGHT, 0 पूर्ण,
	अणु SB_DSP4_OUTPUT_SW, 0 पूर्ण,
	अणु SB_DSP4_SPEAKER_DEV, 0 पूर्ण,
पूर्ण;

/*
 * DT019x specअगरic mixer elements
 */
अटल स्थिर काष्ठा sbmix_elem snd_dt019x_controls[] = अणु
	/* ALS4000 below has some parts which we might be lacking,
	 * e.g. snd_als4000_ctl_mono_playback_चयन - check it! */
	SB_DOUBLE("Master Playback Volume",
		  SB_DT019X_MASTER_DEV, SB_DT019X_MASTER_DEV, 4, 0, 15),
	SB_DOUBLE("PCM Playback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 2, 1, 1),
	SB_DOUBLE("PCM Playback Volume",
		  SB_DT019X_PCM_DEV, SB_DT019X_PCM_DEV, 4, 0, 15),
	SB_DOUBLE("Synth Playback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 4, 3, 1),
	SB_DOUBLE("Synth Playback Volume",
		  SB_DT019X_SYNTH_DEV, SB_DT019X_SYNTH_DEV, 4, 0, 15),
	SB_DOUBLE("CD Playback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 2, 1, 1),
	SB_DOUBLE("CD Playback Volume",
		  SB_DT019X_CD_DEV, SB_DT019X_CD_DEV, 4, 0, 15),
	SB_SINGLE("Mic Playback Switch", SB_DSP4_OUTPUT_SW, 0, 1),
	SB_SINGLE("Mic Playback Volume", SB_DT019X_MIC_DEV, 4, 7),
	SB_SINGLE("Beep Volume", SB_DT019X_SPKR_DEV, 0,  7),
	SB_DOUBLE("Line Playback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 4, 3, 1),
	SB_DOUBLE("Line Playback Volume",
		  SB_DT019X_LINE_DEV, SB_DT019X_LINE_DEV, 4, 0, 15),
	अणु
		.name = "Capture Source",
		.type = SB_MIX_CAPTURE_DT019X
	पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर snd_dt019x_init_values[][2] = अणु
        अणु SB_DT019X_MASTER_DEV, 0 पूर्ण,
        अणु SB_DT019X_PCM_DEV, 0 पूर्ण,
        अणु SB_DT019X_SYNTH_DEV, 0 पूर्ण,
        अणु SB_DT019X_CD_DEV, 0 पूर्ण,
        अणु SB_DT019X_MIC_DEV, 0 पूर्ण,	/* Includes PC-speaker in high nibble */
        अणु SB_DT019X_LINE_DEV, 0 पूर्ण,
        अणु SB_DSP4_OUTPUT_SW, 0 पूर्ण,
        अणु SB_DT019X_OUTPUT_SW2, 0 पूर्ण,
        अणु SB_DT019X_CAPTURE_SW, 0x06 पूर्ण,
पूर्ण;

/*
 * ALS4000 specअगरic mixer elements
 */
अटल स्थिर काष्ठा sbmix_elem snd_als4000_controls[] = अणु
	SB_DOUBLE("PCM Playback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 2, 1, 1),
	SB_DOUBLE("Synth Playback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 4, 3, 1),
	SB_SINGLE("Mic Boost (+20dB)", SB_ALS4000_MIC_IN_GAIN, 0, 0x03),
	SB_SINGLE("Master Mono Playback Switch", SB_ALS4000_MONO_IO_CTRL, 5, 1),
	अणु
		.name = "Master Mono Capture Route",
		.type = SB_MIX_MONO_CAPTURE_ALS4K
	पूर्ण,
	SB_SINGLE("Mono Playback Switch", SB_DT019X_OUTPUT_SW2, 0, 1),
	SB_SINGLE("Analog Loopback Switch", SB_ALS4000_MIC_IN_GAIN, 7, 0x01),
	SB_SINGLE("3D Control - Switch", SB_ALS4000_3D_SND_FX, 6, 0x01),
	SB_SINGLE("Digital Loopback Switch",
		  SB_ALS4000_CR3_CONFIGURATION, 7, 0x01),
	/* FIXME: functionality of 3D controls might be swapped, I didn't find
	 * a description of how to identअगरy what is supposed to be what */
	SB_SINGLE("3D Control - Level", SB_ALS4000_3D_SND_FX, 0, 0x07),
	/* FIXME: maybe there's actually some standard 3D ctrl name क्रम it?? */
	SB_SINGLE("3D Control - Freq", SB_ALS4000_3D_SND_FX, 4, 0x03),
	/* FIXME: ALS4000a.pdf mentions BBD (Bucket Brigade Device) समय delay,
	 * but what ALSA 3D attribute is that actually? "Center", "Depth",
	 * "Wide" or "Space" or even "Level"? Assuming "Wide" क्रम now... */
	SB_SINGLE("3D Control - Wide", SB_ALS4000_3D_TIME_DELAY, 0, 0x0f),
	SB_SINGLE("3D PowerOff Switch", SB_ALS4000_3D_TIME_DELAY, 4, 0x01),
	SB_SINGLE("Master Playback 8kHz / 20kHz LPF Switch",
		  SB_ALS4000_FMDAC, 5, 0x01),
#अगर_घोषित NOT_AVAILABLE
	SB_SINGLE("FMDAC Switch (Option ?)", SB_ALS4000_FMDAC, 0, 0x01),
	SB_SINGLE("QSound Mode", SB_ALS4000_QSOUND, 1, 0x1f),
#पूर्ण_अगर
पूर्ण;

अटल स्थिर अचिन्हित अक्षर snd_als4000_init_values[][2] = अणु
	अणु SB_DSP4_MASTER_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_MASTER_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_PCM_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_PCM_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_SYNTH_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_SYNTH_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_SPEAKER_DEV, 0 पूर्ण,
	अणु SB_DSP4_OUTPUT_SW, 0 पूर्ण,
	अणु SB_DSP4_INPUT_LEFT, 0 पूर्ण,
	अणु SB_DSP4_INPUT_RIGHT, 0 पूर्ण,
	अणु SB_DT019X_OUTPUT_SW2, 0 पूर्ण,
	अणु SB_ALS4000_MIC_IN_GAIN, 0 पूर्ण,
पूर्ण;

/*
 */
अटल पूर्णांक snd_sbmixer_init(काष्ठा snd_sb *chip,
			    स्थिर काष्ठा sbmix_elem *controls,
			    पूर्णांक controls_count,
			    स्थिर अचिन्हित अक्षर map[][2],
			    पूर्णांक map_count,
			    अक्षर *name)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_card *card = chip->card;
	पूर्णांक idx, err;

	/* mixer reset */
	spin_lock_irqsave(&chip->mixer_lock, flags);
	snd_sbmixer_ग_लिखो(chip, 0x00, 0x00);
	spin_unlock_irqrestore(&chip->mixer_lock, flags);

	/* mute and zero volume channels */
	क्रम (idx = 0; idx < map_count; idx++) अणु
		spin_lock_irqsave(&chip->mixer_lock, flags);
		snd_sbmixer_ग_लिखो(chip, map[idx][0], map[idx][1]);
		spin_unlock_irqrestore(&chip->mixer_lock, flags);
	पूर्ण

	क्रम (idx = 0; idx < controls_count; idx++) अणु
		err = snd_sbmixer_add_ctl_elem(chip, &controls[idx]);
		अगर (err < 0)
			वापस err;
	पूर्ण
	snd_component_add(card, name);
	म_नकल(card->mixername, name);
	वापस 0;
पूर्ण

पूर्णांक snd_sbmixer_new(काष्ठा snd_sb *chip)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (snd_BUG_ON(!chip || !chip->card))
		वापस -EINVAL;

	card = chip->card;

	चयन (chip->hardware) अणु
	हाल SB_HW_10:
		वापस 0; /* no mixer chip on SB1.x */
	हाल SB_HW_20:
	हाल SB_HW_201:
		अगर ((err = snd_sbmixer_init(chip,
					    snd_sb20_controls,
					    ARRAY_SIZE(snd_sb20_controls),
					    snd_sb20_init_values,
					    ARRAY_SIZE(snd_sb20_init_values),
					    "CTL1335")) < 0)
			वापस err;
		अवरोध;
	हाल SB_HW_PRO:
	हाल SB_HW_JAZZ16:
		अगर ((err = snd_sbmixer_init(chip,
					    snd_sbpro_controls,
					    ARRAY_SIZE(snd_sbpro_controls),
					    snd_sbpro_init_values,
					    ARRAY_SIZE(snd_sbpro_init_values),
					    "CTL1345")) < 0)
			वापस err;
		अवरोध;
	हाल SB_HW_16:
	हाल SB_HW_ALS100:
	हाल SB_HW_CS5530:
		अगर ((err = snd_sbmixer_init(chip,
					    snd_sb16_controls,
					    ARRAY_SIZE(snd_sb16_controls),
					    snd_sb16_init_values,
					    ARRAY_SIZE(snd_sb16_init_values),
					    "CTL1745")) < 0)
			वापस err;
		अवरोध;
	हाल SB_HW_ALS4000:
		/* use only the first 16 controls from SB16 */
		err = snd_sbmixer_init(chip,
					snd_sb16_controls,
					16,
					snd_sb16_init_values,
					ARRAY_SIZE(snd_sb16_init_values),
					"ALS4000");
		अगर (err < 0)
			वापस err;
		अगर ((err = snd_sbmixer_init(chip,
					    snd_als4000_controls,
					    ARRAY_SIZE(snd_als4000_controls),
					    snd_als4000_init_values,
					    ARRAY_SIZE(snd_als4000_init_values),
					    "ALS4000")) < 0)
			वापस err;
		अवरोध;
	हाल SB_HW_DT019X:
		err = snd_sbmixer_init(chip,
				       snd_dt019x_controls,
				       ARRAY_SIZE(snd_dt019x_controls),
				       snd_dt019x_init_values,
				       ARRAY_SIZE(snd_dt019x_init_values),
				       "DT019X");
		अगर (err < 0)
			वापस err;
		अवरोध;
	शेष:
		म_नकल(card->mixername, "???");
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल स्थिर अचिन्हित अक्षर sb20_saved_regs[] = अणु
	SB_DSP20_MASTER_DEV,
	SB_DSP20_PCM_DEV,
	SB_DSP20_FM_DEV,
	SB_DSP20_CD_DEV,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर sbpro_saved_regs[] = अणु
	SB_DSP_MASTER_DEV,
	SB_DSP_PCM_DEV,
	SB_DSP_PLAYBACK_FILT,
	SB_DSP_FM_DEV,
	SB_DSP_CD_DEV,
	SB_DSP_LINE_DEV,
	SB_DSP_MIC_DEV,
	SB_DSP_CAPTURE_SOURCE,
	SB_DSP_CAPTURE_FILT,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर sb16_saved_regs[] = अणु
	SB_DSP4_MASTER_DEV, SB_DSP4_MASTER_DEV + 1,
	SB_DSP4_3DSE,
	SB_DSP4_BASS_DEV, SB_DSP4_BASS_DEV + 1,
	SB_DSP4_TREBLE_DEV, SB_DSP4_TREBLE_DEV + 1,
	SB_DSP4_PCM_DEV, SB_DSP4_PCM_DEV + 1,
	SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT,
	SB_DSP4_SYNTH_DEV, SB_DSP4_SYNTH_DEV + 1,
	SB_DSP4_OUTPUT_SW,
	SB_DSP4_CD_DEV, SB_DSP4_CD_DEV + 1,
	SB_DSP4_LINE_DEV, SB_DSP4_LINE_DEV + 1,
	SB_DSP4_MIC_DEV,
	SB_DSP4_SPEAKER_DEV,
	SB_DSP4_IGAIN_DEV, SB_DSP4_IGAIN_DEV + 1,
	SB_DSP4_OGAIN_DEV, SB_DSP4_OGAIN_DEV + 1,
	SB_DSP4_MIC_AGC
पूर्ण;

अटल स्थिर अचिन्हित अक्षर dt019x_saved_regs[] = अणु
	SB_DT019X_MASTER_DEV,
	SB_DT019X_PCM_DEV,
	SB_DT019X_SYNTH_DEV,
	SB_DT019X_CD_DEV,
	SB_DT019X_MIC_DEV,
	SB_DT019X_SPKR_DEV,
	SB_DT019X_LINE_DEV,
	SB_DSP4_OUTPUT_SW,
	SB_DT019X_OUTPUT_SW2,
	SB_DT019X_CAPTURE_SW,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर als4000_saved_regs[] = अणु
	/* please verअगरy in dsheet whether regs to be added
	   are actually real H/W or just dummy */
	SB_DSP4_MASTER_DEV, SB_DSP4_MASTER_DEV + 1,
	SB_DSP4_OUTPUT_SW,
	SB_DSP4_PCM_DEV, SB_DSP4_PCM_DEV + 1,
	SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT,
	SB_DSP4_SYNTH_DEV, SB_DSP4_SYNTH_DEV + 1,
	SB_DSP4_CD_DEV, SB_DSP4_CD_DEV + 1,
	SB_DSP4_MIC_DEV,
	SB_DSP4_SPEAKER_DEV,
	SB_DSP4_IGAIN_DEV, SB_DSP4_IGAIN_DEV + 1,
	SB_DSP4_OGAIN_DEV, SB_DSP4_OGAIN_DEV + 1,
	SB_DT019X_OUTPUT_SW2,
	SB_ALS4000_MONO_IO_CTRL,
	SB_ALS4000_MIC_IN_GAIN,
	SB_ALS4000_FMDAC,
	SB_ALS4000_3D_SND_FX,
	SB_ALS4000_3D_TIME_DELAY,
	SB_ALS4000_CR3_CONFIGURATION,
पूर्ण;

अटल व्योम save_mixer(काष्ठा snd_sb *chip, स्थिर अचिन्हित अक्षर *regs, पूर्णांक num_regs)
अणु
	अचिन्हित अक्षर *val = chip->saved_regs;
	अगर (snd_BUG_ON(num_regs > ARRAY_SIZE(chip->saved_regs)))
		वापस;
	क्रम (; num_regs; num_regs--)
		*val++ = snd_sbmixer_पढ़ो(chip, *regs++);
पूर्ण

अटल व्योम restore_mixer(काष्ठा snd_sb *chip, स्थिर अचिन्हित अक्षर *regs, पूर्णांक num_regs)
अणु
	अचिन्हित अक्षर *val = chip->saved_regs;
	अगर (snd_BUG_ON(num_regs > ARRAY_SIZE(chip->saved_regs)))
		वापस;
	क्रम (; num_regs; num_regs--)
		snd_sbmixer_ग_लिखो(chip, *regs++, *val++);
पूर्ण

व्योम snd_sbmixer_suspend(काष्ठा snd_sb *chip)
अणु
	चयन (chip->hardware) अणु
	हाल SB_HW_20:
	हाल SB_HW_201:
		save_mixer(chip, sb20_saved_regs, ARRAY_SIZE(sb20_saved_regs));
		अवरोध;
	हाल SB_HW_PRO:
	हाल SB_HW_JAZZ16:
		save_mixer(chip, sbpro_saved_regs, ARRAY_SIZE(sbpro_saved_regs));
		अवरोध;
	हाल SB_HW_16:
	हाल SB_HW_ALS100:
	हाल SB_HW_CS5530:
		save_mixer(chip, sb16_saved_regs, ARRAY_SIZE(sb16_saved_regs));
		अवरोध;
	हाल SB_HW_ALS4000:
		save_mixer(chip, als4000_saved_regs, ARRAY_SIZE(als4000_saved_regs));
		अवरोध;
	हाल SB_HW_DT019X:
		save_mixer(chip, dt019x_saved_regs, ARRAY_SIZE(dt019x_saved_regs));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम snd_sbmixer_resume(काष्ठा snd_sb *chip)
अणु
	चयन (chip->hardware) अणु
	हाल SB_HW_20:
	हाल SB_HW_201:
		restore_mixer(chip, sb20_saved_regs, ARRAY_SIZE(sb20_saved_regs));
		अवरोध;
	हाल SB_HW_PRO:
	हाल SB_HW_JAZZ16:
		restore_mixer(chip, sbpro_saved_regs, ARRAY_SIZE(sbpro_saved_regs));
		अवरोध;
	हाल SB_HW_16:
	हाल SB_HW_ALS100:
	हाल SB_HW_CS5530:
		restore_mixer(chip, sb16_saved_regs, ARRAY_SIZE(sb16_saved_regs));
		अवरोध;
	हाल SB_HW_ALS4000:
		restore_mixer(chip, als4000_saved_regs, ARRAY_SIZE(als4000_saved_regs));
		अवरोध;
	हाल SB_HW_DT019X:
		restore_mixer(chip, dt019x_saved_regs, ARRAY_SIZE(dt019x_saved_regs));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर
