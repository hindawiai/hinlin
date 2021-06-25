<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   UAC3 Power Doमुख्य state management functions
 */

#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/usb/audio-v3.h>

#समावेश "usbaudio.h"
#समावेश "helper.h"
#समावेश "power.h"

काष्ठा snd_usb_घातer_करोमुख्य *
snd_usb_find_घातer_करोमुख्य(काष्ठा usb_host_पूर्णांकerface *ctrl_अगरace,
			  अचिन्हित अक्षर id)
अणु
	काष्ठा snd_usb_घातer_करोमुख्य *pd;
	व्योम *p;

	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस शून्य;

	p = शून्य;
	जबतक ((p = snd_usb_find_csपूर्णांक_desc(ctrl_अगरace->extra,
					    ctrl_अगरace->extralen,
					    p, UAC3_POWER_DOMAIN)) != शून्य) अणु
		काष्ठा uac3_घातer_करोमुख्य_descriptor *pd_desc = p;
		पूर्णांक i;

		अगर (!snd_usb_validate_audio_desc(p, UAC_VERSION_3))
			जारी;
		क्रम (i = 0; i < pd_desc->bNrEntities; i++) अणु
			अगर (pd_desc->baEntityID[i] == id) अणु
				pd->pd_id = pd_desc->bPowerDoमुख्यID;
				pd->pd_d1d0_rec =
					le16_to_cpu(pd_desc->waRecoveryTime1);
				pd->pd_d2d0_rec =
					le16_to_cpu(pd_desc->waRecoveryTime2);
				वापस pd;
			पूर्ण
		पूर्ण
	पूर्ण

	kमुक्त(pd);
	वापस शून्य;
पूर्ण

पूर्णांक snd_usb_घातer_करोमुख्य_set(काष्ठा snd_usb_audio *chip,
			     काष्ठा snd_usb_घातer_करोमुख्य *pd,
			     अचिन्हित अक्षर state)
अणु
	काष्ठा usb_device *dev = chip->dev;
	अचिन्हित अक्षर current_state;
	पूर्णांक err, idx;

	idx = snd_usb_ctrl_पूर्णांकf(chip) | (pd->pd_id << 8);

	err = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0),
			      UAC2_CS_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
			      UAC3_AC_POWER_DOMAIN_CONTROL << 8, idx,
			      &current_state, माप(current_state));
	अगर (err < 0) अणु
		dev_err(&dev->dev, "Can't get UAC3 power state for id %d\n",
			pd->pd_id);
		वापस err;
	पूर्ण

	अगर (current_state == state) अणु
		dev_dbg(&dev->dev, "UAC3 power domain id %d already in state %d\n",
			pd->pd_id, state);
		वापस 0;
	पूर्ण

	err = snd_usb_ctl_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0), UAC2_CS_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT,
			      UAC3_AC_POWER_DOMAIN_CONTROL << 8, idx,
			      &state, माप(state));
	अगर (err < 0) अणु
		dev_err(&dev->dev, "Can't set UAC3 power state to %d for id %d\n",
			state, pd->pd_id);
		वापस err;
	पूर्ण

	अगर (state == UAC3_PD_STATE_D0) अणु
		चयन (current_state) अणु
		हाल UAC3_PD_STATE_D2:
			udelay(pd->pd_d2d0_rec * 50);
			अवरोध;
		हाल UAC3_PD_STATE_D1:
			udelay(pd->pd_d1d0_rec * 50);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(&dev->dev, "UAC3 power domain id %d change to state %d\n",
		pd->pd_id, state);

	वापस 0;
पूर्ण
