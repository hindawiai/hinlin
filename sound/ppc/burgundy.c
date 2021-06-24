<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PMac Burgundy lowlevel functions
 *
 * Copyright (c) by Takashi Iwai <tiwai@suse.de>
 * code based on dmasound.c.
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश "pmac.h"
#समावेश "burgundy.h"


/* Waits क्रम busy flag to clear */
अटल अंतरभूत व्योम
snd_pmac_burgundy_busy_रुको(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक समयout = 50;
	जबतक ((in_le32(&chip->awacs->codec_ctrl) & MASK_NEWECMD) && समयout--)
		udelay(1);
	अगर (समयout < 0)
		prपूर्णांकk(KERN_DEBUG "burgundy_busy_wait: timeout\n");
पूर्ण

अटल अंतरभूत व्योम
snd_pmac_burgundy_extend_रुको(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक समयout;
	समयout = 50;
	जबतक (!(in_le32(&chip->awacs->codec_stat) & MASK_EXTEND) && समयout--)
		udelay(1);
	अगर (समयout < 0)
		prपूर्णांकk(KERN_DEBUG "burgundy_extend_wait: timeout #1\n");
	समयout = 50;
	जबतक ((in_le32(&chip->awacs->codec_stat) & MASK_EXTEND) && समयout--)
		udelay(1);
	अगर (समयout < 0)
		prपूर्णांकk(KERN_DEBUG "burgundy_extend_wait: timeout #2\n");
पूर्ण

अटल व्योम
snd_pmac_burgundy_wcw(काष्ठा snd_pmac *chip, अचिन्हित addr, अचिन्हित val)
अणु
	out_le32(&chip->awacs->codec_ctrl, addr + 0x200c00 + (val & 0xff));
	snd_pmac_burgundy_busy_रुको(chip);
	out_le32(&chip->awacs->codec_ctrl, addr + 0x200d00 +((val>>8) & 0xff));
	snd_pmac_burgundy_busy_रुको(chip);
	out_le32(&chip->awacs->codec_ctrl, addr + 0x200e00 +((val>>16) & 0xff));
	snd_pmac_burgundy_busy_रुको(chip);
	out_le32(&chip->awacs->codec_ctrl, addr + 0x200f00 +((val>>24) & 0xff));
	snd_pmac_burgundy_busy_रुको(chip);
पूर्ण

अटल अचिन्हित
snd_pmac_burgundy_rcw(काष्ठा snd_pmac *chip, अचिन्हित addr)
अणु
	अचिन्हित val = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);

	out_le32(&chip->awacs->codec_ctrl, addr + 0x100000);
	snd_pmac_burgundy_busy_रुको(chip);
	snd_pmac_burgundy_extend_रुको(chip);
	val += (in_le32(&chip->awacs->codec_stat) >> 4) & 0xff;

	out_le32(&chip->awacs->codec_ctrl, addr + 0x100100);
	snd_pmac_burgundy_busy_रुको(chip);
	snd_pmac_burgundy_extend_रुको(chip);
	val += ((in_le32(&chip->awacs->codec_stat)>>4) & 0xff) <<8;

	out_le32(&chip->awacs->codec_ctrl, addr + 0x100200);
	snd_pmac_burgundy_busy_रुको(chip);
	snd_pmac_burgundy_extend_रुको(chip);
	val += ((in_le32(&chip->awacs->codec_stat)>>4) & 0xff) <<16;

	out_le32(&chip->awacs->codec_ctrl, addr + 0x100300);
	snd_pmac_burgundy_busy_रुको(chip);
	snd_pmac_burgundy_extend_रुको(chip);
	val += ((in_le32(&chip->awacs->codec_stat)>>4) & 0xff) <<24;

	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस val;
पूर्ण

अटल व्योम
snd_pmac_burgundy_wcb(काष्ठा snd_pmac *chip, अचिन्हित पूर्णांक addr,
		      अचिन्हित पूर्णांक val)
अणु
	out_le32(&chip->awacs->codec_ctrl, addr + 0x300000 + (val & 0xff));
	snd_pmac_burgundy_busy_रुको(chip);
पूर्ण

अटल अचिन्हित
snd_pmac_burgundy_rcb(काष्ठा snd_pmac *chip, अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित val = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);

	out_le32(&chip->awacs->codec_ctrl, addr + 0x100000);
	snd_pmac_burgundy_busy_रुको(chip);
	snd_pmac_burgundy_extend_रुको(chip);
	val += (in_le32(&chip->awacs->codec_stat) >> 4) & 0xff;

	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस val;
पूर्ण

#घोषणा BASE2ADDR(base)	((base) << 12)
#घोषणा ADDR2BASE(addr)	((addr) >> 12)

/*
 * Burgundy volume: 0 - 100, stereo, word reg
 */
अटल व्योम
snd_pmac_burgundy_ग_लिखो_volume(काष्ठा snd_pmac *chip, अचिन्हित पूर्णांक address,
			       दीर्घ *volume, पूर्णांक shअगरt)
अणु
	पूर्णांक hardvolume, lvolume, rvolume;

	अगर (volume[0] < 0 || volume[0] > 100 ||
	    volume[1] < 0 || volume[1] > 100)
		वापस; /* -EINVAL */
	lvolume = volume[0] ? volume[0] + BURGUNDY_VOLUME_OFFSET : 0;
	rvolume = volume[1] ? volume[1] + BURGUNDY_VOLUME_OFFSET : 0;

	hardvolume = lvolume + (rvolume << shअगरt);
	अगर (shअगरt == 8)
		hardvolume |= hardvolume << 16;

	snd_pmac_burgundy_wcw(chip, address, hardvolume);
पूर्ण

अटल व्योम
snd_pmac_burgundy_पढ़ो_volume(काष्ठा snd_pmac *chip, अचिन्हित पूर्णांक address,
			      दीर्घ *volume, पूर्णांक shअगरt)
अणु
	पूर्णांक wvolume;

	wvolume = snd_pmac_burgundy_rcw(chip, address);

	volume[0] = wvolume & 0xff;
	अगर (volume[0] >= BURGUNDY_VOLUME_OFFSET)
		volume[0] -= BURGUNDY_VOLUME_OFFSET;
	अन्यथा
		volume[0] = 0;
	volume[1] = (wvolume >> shअगरt) & 0xff;
	अगर (volume[1] >= BURGUNDY_VOLUME_OFFSET)
		volume[1] -= BURGUNDY_VOLUME_OFFSET;
	अन्यथा
		volume[1] = 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_info_volume(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 100;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_get_volume(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR(kcontrol->निजी_value & 0xff);
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	snd_pmac_burgundy_पढ़ो_volume(chip, addr,
				      ucontrol->value.पूर्णांकeger.value, shअगरt);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_put_volume(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR(kcontrol->निजी_value & 0xff);
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	दीर्घ nvoices[2];

	snd_pmac_burgundy_ग_लिखो_volume(chip, addr,
				       ucontrol->value.पूर्णांकeger.value, shअगरt);
	snd_pmac_burgundy_पढ़ो_volume(chip, addr, nvoices, shअगरt);
	वापस (nvoices[0] != ucontrol->value.पूर्णांकeger.value[0] ||
		nvoices[1] != ucontrol->value.पूर्णांकeger.value[1]);
पूर्ण

#घोषणा BURGUNDY_VOLUME_W(xname, xindex, addr, shअगरt) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex,\
  .info = snd_pmac_burgundy_info_volume,\
  .get = snd_pmac_burgundy_get_volume,\
  .put = snd_pmac_burgundy_put_volume,\
  .निजी_value = ((ADDR2BASE(addr) & 0xff) | ((shअगरt) << 8)) पूर्ण

/*
 * Burgundy volume: 0 - 100, stereo, 2-byte reg
 */
अटल व्योम
snd_pmac_burgundy_ग_लिखो_volume_2b(काष्ठा snd_pmac *chip, अचिन्हित पूर्णांक address,
				  दीर्घ *volume, पूर्णांक off)
अणु
	पूर्णांक lvolume, rvolume;

	off |= off << 2;
	lvolume = volume[0] ? volume[0] + BURGUNDY_VOLUME_OFFSET : 0;
	rvolume = volume[1] ? volume[1] + BURGUNDY_VOLUME_OFFSET : 0;

	snd_pmac_burgundy_wcb(chip, address + off, lvolume);
	snd_pmac_burgundy_wcb(chip, address + off + 0x500, rvolume);
पूर्ण

अटल व्योम
snd_pmac_burgundy_पढ़ो_volume_2b(काष्ठा snd_pmac *chip, अचिन्हित पूर्णांक address,
				 दीर्घ *volume, पूर्णांक off)
अणु
	volume[0] = snd_pmac_burgundy_rcb(chip, address + off);
	अगर (volume[0] >= BURGUNDY_VOLUME_OFFSET)
		volume[0] -= BURGUNDY_VOLUME_OFFSET;
	अन्यथा
		volume[0] = 0;
	volume[1] = snd_pmac_burgundy_rcb(chip, address + off + 0x100);
	अगर (volume[1] >= BURGUNDY_VOLUME_OFFSET)
		volume[1] -= BURGUNDY_VOLUME_OFFSET;
	अन्यथा
		volume[1] = 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_info_volume_2b(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 100;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_get_volume_2b(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR(kcontrol->निजी_value & 0xff);
	पूर्णांक off = kcontrol->निजी_value & 0x300;
	snd_pmac_burgundy_पढ़ो_volume_2b(chip, addr,
			ucontrol->value.पूर्णांकeger.value, off);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_put_volume_2b(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR(kcontrol->निजी_value & 0xff);
	पूर्णांक off = kcontrol->निजी_value & 0x300;
	दीर्घ nvoices[2];

	snd_pmac_burgundy_ग_लिखो_volume_2b(chip, addr,
			ucontrol->value.पूर्णांकeger.value, off);
	snd_pmac_burgundy_पढ़ो_volume_2b(chip, addr, nvoices, off);
	वापस (nvoices[0] != ucontrol->value.पूर्णांकeger.value[0] ||
		nvoices[1] != ucontrol->value.पूर्णांकeger.value[1]);
पूर्ण

#घोषणा BURGUNDY_VOLUME_2B(xname, xindex, addr, off) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex,\
  .info = snd_pmac_burgundy_info_volume_2b,\
  .get = snd_pmac_burgundy_get_volume_2b,\
  .put = snd_pmac_burgundy_put_volume_2b,\
  .निजी_value = ((ADDR2BASE(addr) & 0xff) | ((off) << 8)) पूर्ण

/*
 * Burgundy gain/attenuation: 0 - 15, mono/stereo, byte reg
 */
अटल पूर्णांक snd_pmac_burgundy_info_gain(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = stereo + 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 15;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_get_gain(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR(kcontrol->निजी_value & 0xff);
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	पूर्णांक atten = (kcontrol->निजी_value >> 25) & 1;
	पूर्णांक oval;

	oval = snd_pmac_burgundy_rcb(chip, addr);
	अगर (atten)
		oval = ~oval & 0xff;
	ucontrol->value.पूर्णांकeger.value[0] = oval & 0xf;
	अगर (stereo)
		ucontrol->value.पूर्णांकeger.value[1] = (oval >> 4) & 0xf;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_put_gain(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR(kcontrol->निजी_value & 0xff);
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	पूर्णांक atten = (kcontrol->निजी_value >> 25) & 1;
	पूर्णांक oval, val;

	oval = snd_pmac_burgundy_rcb(chip, addr);
	अगर (atten)
		oval = ~oval & 0xff;
	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (stereo)
		val |= ucontrol->value.पूर्णांकeger.value[1] << 4;
	अन्यथा
		val |= ucontrol->value.पूर्णांकeger.value[0] << 4;
	अगर (atten)
		val = ~val & 0xff;
	snd_pmac_burgundy_wcb(chip, addr, val);
	वापस val != oval;
पूर्ण

#घोषणा BURGUNDY_VOLUME_B(xname, xindex, addr, stereo, atten) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex,\
  .info = snd_pmac_burgundy_info_gain,\
  .get = snd_pmac_burgundy_get_gain,\
  .put = snd_pmac_burgundy_put_gain,\
  .निजी_value = (ADDR2BASE(addr) | ((stereo) << 24) | ((atten) << 25)) पूर्ण

/*
 * Burgundy चयन: 0/1, mono/stereo, word reg
 */
अटल पूर्णांक snd_pmac_burgundy_info_चयन_w(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = stereo + 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_get_चयन_w(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR((kcontrol->निजी_value >> 16) & 0xff);
	पूर्णांक lmask = 1 << (kcontrol->निजी_value & 0xff);
	पूर्णांक rmask = 1 << ((kcontrol->निजी_value >> 8) & 0xff);
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	पूर्णांक val = snd_pmac_burgundy_rcw(chip, addr);
	ucontrol->value.पूर्णांकeger.value[0] = (val & lmask) ? 1 : 0;
	अगर (stereo)
		ucontrol->value.पूर्णांकeger.value[1] = (val & rmask) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_put_चयन_w(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR((kcontrol->निजी_value >> 16) & 0xff);
	पूर्णांक lmask = 1 << (kcontrol->निजी_value & 0xff);
	पूर्णांक rmask = 1 << ((kcontrol->निजी_value >> 8) & 0xff);
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	पूर्णांक val, oval;
	oval = snd_pmac_burgundy_rcw(chip, addr);
	val = oval & ~(lmask | (stereo ? rmask : 0));
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= lmask;
	अगर (stereo && ucontrol->value.पूर्णांकeger.value[1])
		val |= rmask;
	snd_pmac_burgundy_wcw(chip, addr, val);
	वापस val != oval;
पूर्ण

#घोषणा BURGUNDY_SWITCH_W(xname, xindex, addr, lbit, rbit, stereo) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex,\
  .info = snd_pmac_burgundy_info_चयन_w,\
  .get = snd_pmac_burgundy_get_चयन_w,\
  .put = snd_pmac_burgundy_put_चयन_w,\
  .निजी_value = ((lbit) | ((rbit) << 8)\
		| (ADDR2BASE(addr) << 16) | ((stereo) << 24)) पूर्ण

/*
 * Burgundy चयन: 0/1, mono/stereo, byte reg, bit mask
 */
अटल पूर्णांक snd_pmac_burgundy_info_चयन_b(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = stereo + 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_get_चयन_b(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR((kcontrol->निजी_value >> 16) & 0xff);
	पूर्णांक lmask = kcontrol->निजी_value & 0xff;
	पूर्णांक rmask = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	पूर्णांक val = snd_pmac_burgundy_rcb(chip, addr);
	ucontrol->value.पूर्णांकeger.value[0] = (val & lmask) ? 1 : 0;
	अगर (stereo)
		ucontrol->value.पूर्णांकeger.value[1] = (val & rmask) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_burgundy_put_चयन_b(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक addr = BASE2ADDR((kcontrol->निजी_value >> 16) & 0xff);
	पूर्णांक lmask = kcontrol->निजी_value & 0xff;
	पूर्णांक rmask = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक stereo = (kcontrol->निजी_value >> 24) & 1;
	पूर्णांक val, oval;
	oval = snd_pmac_burgundy_rcb(chip, addr);
	val = oval & ~(lmask | rmask);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= lmask;
	अगर (stereo && ucontrol->value.पूर्णांकeger.value[1])
		val |= rmask;
	snd_pmac_burgundy_wcb(chip, addr, val);
	वापस val != oval;
पूर्ण

#घोषणा BURGUNDY_SWITCH_B(xname, xindex, addr, lmask, rmask, stereo) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex,\
  .info = snd_pmac_burgundy_info_चयन_b,\
  .get = snd_pmac_burgundy_get_चयन_b,\
  .put = snd_pmac_burgundy_put_चयन_b,\
  .निजी_value = ((lmask) | ((rmask) << 8)\
		| (ADDR2BASE(addr) << 16) | ((stereo) << 24)) पूर्ण

/*
 * Burgundy mixers
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_mixers[] = अणु
	BURGUNDY_VOLUME_W("Master Playback Volume", 0,
			MASK_ADDR_BURGUNDY_MASTER_VOLUME, 8),
	BURGUNDY_VOLUME_W("CD Capture Volume", 0,
			MASK_ADDR_BURGUNDY_VOLCD, 16),
	BURGUNDY_VOLUME_2B("Input Capture Volume", 0,
			MASK_ADDR_BURGUNDY_VOLMIX01, 2),
	BURGUNDY_VOLUME_2B("Mixer Playback Volume", 0,
			MASK_ADDR_BURGUNDY_VOLMIX23, 0),
	BURGUNDY_VOLUME_B("CD Gain Capture Volume", 0,
			MASK_ADDR_BURGUNDY_GAINCD, 1, 0),
	BURGUNDY_SWITCH_W("Master Capture Switch", 0,
			MASK_ADDR_BURGUNDY_OUTPUTENABLES, 24, 0, 0),
	BURGUNDY_SWITCH_W("CD Capture Switch", 0,
			MASK_ADDR_BURGUNDY_CAPTURESELECTS, 0, 16, 1),
	BURGUNDY_SWITCH_W("CD Playback Switch", 0,
			MASK_ADDR_BURGUNDY_OUTPUTSELECTS, 0, 16, 1),
/*	BURGUNDY_SWITCH_W("Loop Capture Switch", 0,
 *		MASK_ADDR_BURGUNDY_CAPTURESELECTS, 8, 24, 1),
 *	BURGUNDY_SWITCH_B("Mixer out Capture Switch", 0,
 *		MASK_ADDR_BURGUNDY_HOSTIFAD, 0x02, 0, 0),
 *	BURGUNDY_SWITCH_B("Mixer Capture Switch", 0,
 *		MASK_ADDR_BURGUNDY_HOSTIFAD, 0x01, 0, 0),
 *	BURGUNDY_SWITCH_B("PCM out Capture Switch", 0,
 *		MASK_ADDR_BURGUNDY_HOSTIFEH, 0x02, 0, 0),
 */	BURGUNDY_SWITCH_B("PCM Capture Switch", 0,
			MASK_ADDR_BURGUNDY_HOSTIFEH, 0x01, 0, 0)
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_mixers_imac[] = अणु
	BURGUNDY_VOLUME_W("Line in Capture Volume", 0,
			MASK_ADDR_BURGUNDY_VOLLINE, 16),
	BURGUNDY_VOLUME_W("Mic Capture Volume", 0,
			MASK_ADDR_BURGUNDY_VOLMIC, 16),
	BURGUNDY_VOLUME_B("Line in Gain Capture Volume", 0,
			MASK_ADDR_BURGUNDY_GAINLINE, 1, 0),
	BURGUNDY_VOLUME_B("Mic Gain Capture Volume", 0,
			MASK_ADDR_BURGUNDY_GAINMIC, 1, 0),
	BURGUNDY_VOLUME_B("Speaker Playback Volume", 0,
			MASK_ADDR_BURGUNDY_ATTENSPEAKER, 1, 1),
	BURGUNDY_VOLUME_B("Line out Playback Volume", 0,
			MASK_ADDR_BURGUNDY_ATTENLINEOUT, 1, 1),
	BURGUNDY_VOLUME_B("Headphone Playback Volume", 0,
			MASK_ADDR_BURGUNDY_ATTENHP, 1, 1),
	BURGUNDY_SWITCH_W("Line in Capture Switch", 0,
			MASK_ADDR_BURGUNDY_CAPTURESELECTS, 1, 17, 1),
	BURGUNDY_SWITCH_W("Mic Capture Switch", 0,
			MASK_ADDR_BURGUNDY_CAPTURESELECTS, 2, 18, 1),
	BURGUNDY_SWITCH_W("Line in Playback Switch", 0,
			MASK_ADDR_BURGUNDY_OUTPUTSELECTS, 1, 17, 1),
	BURGUNDY_SWITCH_W("Mic Playback Switch", 0,
			MASK_ADDR_BURGUNDY_OUTPUTSELECTS, 2, 18, 1),
	BURGUNDY_SWITCH_B("Mic Boost Capture Switch", 0,
			MASK_ADDR_BURGUNDY_INPBOOST, 0x40, 0x80, 1)
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_mixers_pmac[] = अणु
	BURGUNDY_VOLUME_W("Line in Capture Volume", 0,
			MASK_ADDR_BURGUNDY_VOLMIC, 16),
	BURGUNDY_VOLUME_B("Line in Gain Capture Volume", 0,
			MASK_ADDR_BURGUNDY_GAINMIC, 1, 0),
	BURGUNDY_VOLUME_B("Speaker Playback Volume", 0,
			MASK_ADDR_BURGUNDY_ATTENMONO, 0, 1),
	BURGUNDY_VOLUME_B("Line out Playback Volume", 0,
			MASK_ADDR_BURGUNDY_ATTENSPEAKER, 1, 1),
	BURGUNDY_SWITCH_W("Line in Capture Switch", 0,
			MASK_ADDR_BURGUNDY_CAPTURESELECTS, 2, 18, 1),
	BURGUNDY_SWITCH_W("Line in Playback Switch", 0,
			MASK_ADDR_BURGUNDY_OUTPUTSELECTS, 2, 18, 1),
/*	BURGUNDY_SWITCH_B("Line in Boost Capture Switch", 0,
 *		MASK_ADDR_BURGUNDY_INPBOOST, 0x40, 0x80, 1) */
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_master_sw_imac =
BURGUNDY_SWITCH_B("Master Playback Switch", 0,
	MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
	BURGUNDY_OUTPUT_LEFT | BURGUNDY_LINEOUT_LEFT | BURGUNDY_HP_LEFT,
	BURGUNDY_OUTPUT_RIGHT | BURGUNDY_LINEOUT_RIGHT | BURGUNDY_HP_RIGHT, 1);
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_master_sw_pmac =
BURGUNDY_SWITCH_B("Master Playback Switch", 0,
	MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
	BURGUNDY_OUTPUT_INTERN
	| BURGUNDY_OUTPUT_LEFT, BURGUNDY_OUTPUT_RIGHT, 1);
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_speaker_sw_imac =
BURGUNDY_SWITCH_B("Speaker Playback Switch", 0,
	MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
	BURGUNDY_OUTPUT_LEFT, BURGUNDY_OUTPUT_RIGHT, 1);
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_speaker_sw_pmac =
BURGUNDY_SWITCH_B("Speaker Playback Switch", 0,
	MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
	BURGUNDY_OUTPUT_INTERN, 0, 0);
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_line_sw_imac =
BURGUNDY_SWITCH_B("Line out Playback Switch", 0,
	MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
	BURGUNDY_LINEOUT_LEFT, BURGUNDY_LINEOUT_RIGHT, 1);
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_line_sw_pmac =
BURGUNDY_SWITCH_B("Line out Playback Switch", 0,
	MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
	BURGUNDY_OUTPUT_LEFT, BURGUNDY_OUTPUT_RIGHT, 1);
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_burgundy_hp_sw_imac =
BURGUNDY_SWITCH_B("Headphone Playback Switch", 0,
	MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
	BURGUNDY_HP_LEFT, BURGUNDY_HP_RIGHT, 1);


#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
/*
 * स्वतः-mute stuffs
 */
अटल पूर्णांक snd_pmac_burgundy_detect_headphone(काष्ठा snd_pmac *chip)
अणु
	वापस (in_le32(&chip->awacs->codec_stat) & chip->hp_stat_mask) ? 1 : 0;
पूर्ण

अटल व्योम snd_pmac_burgundy_update_स्वतःmute(काष्ठा snd_pmac *chip, पूर्णांक करो_notअगरy)
अणु
	अगर (chip->स्वतः_mute) अणु
		पूर्णांक imac = of_machine_is_compatible("iMac");
		पूर्णांक reg, oreg;
		reg = oreg = snd_pmac_burgundy_rcb(chip,
				MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES);
		reg &= imac ? ~(BURGUNDY_OUTPUT_LEFT | BURGUNDY_OUTPUT_RIGHT
				| BURGUNDY_HP_LEFT | BURGUNDY_HP_RIGHT)
			: ~(BURGUNDY_OUTPUT_LEFT | BURGUNDY_OUTPUT_RIGHT
				| BURGUNDY_OUTPUT_INTERN);
		अगर (snd_pmac_burgundy_detect_headphone(chip))
			reg |= imac ? (BURGUNDY_HP_LEFT | BURGUNDY_HP_RIGHT)
				: (BURGUNDY_OUTPUT_LEFT
					| BURGUNDY_OUTPUT_RIGHT);
		अन्यथा
			reg |= imac ? (BURGUNDY_OUTPUT_LEFT
					| BURGUNDY_OUTPUT_RIGHT)
				: (BURGUNDY_OUTPUT_INTERN);
		अगर (करो_notअगरy && reg == oreg)
			वापस;
		snd_pmac_burgundy_wcb(chip,
				MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES, reg);
		अगर (करो_notअगरy) अणु
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->master_sw_ctl->id);
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->speaker_sw_ctl->id);
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->hp_detect_ctl->id);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* PMAC_SUPPORT_AUTOMUTE */


/*
 * initialize burgundy
 */
पूर्णांक snd_pmac_burgundy_init(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक imac = of_machine_is_compatible("iMac");
	पूर्णांक i, err;

	/* Checks to see the chip is alive and kicking */
	अगर ((in_le32(&chip->awacs->codec_ctrl) & MASK_ERRCODE) == 0xf0000) अणु
		prपूर्णांकk(KERN_WARNING "pmac burgundy: disabled by MacOS :-(\n");
		वापस 1;
	पूर्ण

	snd_pmac_burgundy_wcw(chip, MASK_ADDR_BURGUNDY_OUTPUTENABLES,
			   DEF_BURGUNDY_OUTPUTENABLES);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES,
			   DEF_BURGUNDY_MORE_OUTPUTENABLES);
	snd_pmac_burgundy_wcw(chip, MASK_ADDR_BURGUNDY_OUTPUTSELECTS,
			   DEF_BURGUNDY_OUTPUTSELECTS);

	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_INPSEL21,
			   DEF_BURGUNDY_INPSEL21);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_INPSEL3,
			   imac ? DEF_BURGUNDY_INPSEL3_IMAC
			   : DEF_BURGUNDY_INPSEL3_PMAC);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_GAINCD,
			   DEF_BURGUNDY_GAINCD);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_GAINLINE,
			   DEF_BURGUNDY_GAINLINE);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_GAINMIC,
			   DEF_BURGUNDY_GAINMIC);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_GAINMODEM,
			   DEF_BURGUNDY_GAINMODEM);

	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_ATTENSPEAKER,
			   DEF_BURGUNDY_ATTENSPEAKER);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_ATTENLINEOUT,
			   DEF_BURGUNDY_ATTENLINEOUT);
	snd_pmac_burgundy_wcb(chip, MASK_ADDR_BURGUNDY_ATTENHP,
			   DEF_BURGUNDY_ATTENHP);

	snd_pmac_burgundy_wcw(chip, MASK_ADDR_BURGUNDY_MASTER_VOLUME,
			   DEF_BURGUNDY_MASTER_VOLUME);
	snd_pmac_burgundy_wcw(chip, MASK_ADDR_BURGUNDY_VOLCD,
			   DEF_BURGUNDY_VOLCD);
	snd_pmac_burgundy_wcw(chip, MASK_ADDR_BURGUNDY_VOLLINE,
			   DEF_BURGUNDY_VOLLINE);
	snd_pmac_burgundy_wcw(chip, MASK_ADDR_BURGUNDY_VOLMIC,
			   DEF_BURGUNDY_VOLMIC);

	अगर (chip->hp_stat_mask == 0) अणु
		/* set headphone-jack detection bit */
		अगर (imac)
			chip->hp_stat_mask = BURGUNDY_HPDETECT_IMAC_UPPER
				| BURGUNDY_HPDETECT_IMAC_LOWER
				| BURGUNDY_HPDETECT_IMAC_SIDE;
		अन्यथा
			chip->hp_stat_mask = BURGUNDY_HPDETECT_PMAC_BACK;
	पूर्ण
	/*
	 * build burgundy mixers
	 */
	म_नकल(chip->card->mixername, "PowerMac Burgundy");

	क्रम (i = 0; i < ARRAY_SIZE(snd_pmac_burgundy_mixers); i++) अणु
		err = snd_ctl_add(chip->card,
		    snd_ctl_new1(&snd_pmac_burgundy_mixers[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < (imac ? ARRAY_SIZE(snd_pmac_burgundy_mixers_imac)
			: ARRAY_SIZE(snd_pmac_burgundy_mixers_pmac)); i++) अणु
		err = snd_ctl_add(chip->card,
		    snd_ctl_new1(imac ? &snd_pmac_burgundy_mixers_imac[i]
		    : &snd_pmac_burgundy_mixers_pmac[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	chip->master_sw_ctl = snd_ctl_new1(imac
			? &snd_pmac_burgundy_master_sw_imac
			: &snd_pmac_burgundy_master_sw_pmac, chip);
	err = snd_ctl_add(chip->card, chip->master_sw_ctl);
	अगर (err < 0)
		वापस err;
	chip->master_sw_ctl = snd_ctl_new1(imac
			? &snd_pmac_burgundy_line_sw_imac
			: &snd_pmac_burgundy_line_sw_pmac, chip);
	err = snd_ctl_add(chip->card, chip->master_sw_ctl);
	अगर (err < 0)
		वापस err;
	अगर (imac) अणु
		chip->master_sw_ctl = snd_ctl_new1(
				&snd_pmac_burgundy_hp_sw_imac, chip);
		err = snd_ctl_add(chip->card, chip->master_sw_ctl);
		अगर (err < 0)
			वापस err;
	पूर्ण
	chip->speaker_sw_ctl = snd_ctl_new1(imac
			? &snd_pmac_burgundy_speaker_sw_imac
			: &snd_pmac_burgundy_speaker_sw_pmac, chip);
	err = snd_ctl_add(chip->card, chip->speaker_sw_ctl);
	अगर (err < 0)
		वापस err;
#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
	err = snd_pmac_add_स्वतःmute(chip);
	अगर (err < 0)
		वापस err;

	chip->detect_headphone = snd_pmac_burgundy_detect_headphone;
	chip->update_स्वतःmute = snd_pmac_burgundy_update_स्वतःmute;
	snd_pmac_burgundy_update_स्वतःmute(chip, 0); /* update the status only */
#पूर्ण_अगर

	वापस 0;
पूर्ण
