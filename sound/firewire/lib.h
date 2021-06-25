<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_LIB_H_INCLUDED
#घोषणा SOUND_FIREWIRE_LIB_H_INCLUDED

#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <sound/rawmidi.h>

काष्ठा fw_unit;

#घोषणा FW_GENERATION_MASK	0x00ff
#घोषणा FW_FIXED_GENERATION	0x0100
#घोषणा FW_QUIET		0x0200

पूर्णांक snd_fw_transaction(काष्ठा fw_unit *unit, पूर्णांक tcode,
		       u64 offset, व्योम *buffer, माप_प्रकार length,
		       अचिन्हित पूर्णांक flags);

/* वापसs true अगर retrying the transaction would not make sense */
अटल अंतरभूत bool rcode_is_permanent_error(पूर्णांक rcode)
अणु
	वापस rcode == RCODE_TYPE_ERROR || rcode == RCODE_ADDRESS_ERROR;
पूर्ण

व्योम snd_fw_schedule_registration(काष्ठा fw_unit *unit,
				  काष्ठा delayed_work *dwork);

#पूर्ण_अगर
