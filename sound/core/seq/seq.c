<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA sequencer मुख्य module
 *  Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>

#समावेश <sound/seq_kernel.h>
#समावेश "seq_clientmgr.h"
#समावेश "seq_memory.h"
#समावेश "seq_queue.h"
#समावेश "seq_lock.h"
#समावेश "seq_timer.h"
#समावेश "seq_system.h"
#समावेश "seq_info.h"
#समावेश <sound/minors.h>
#समावेश <sound/seq_device.h>

#अगर defined(CONFIG_SND_SEQ_DUMMY_MODULE)
पूर्णांक seq_client_load[15] = अणु[0] = SNDRV_SEQ_CLIENT_DUMMY, [1 ... 14] = -1पूर्ण;
#अन्यथा
पूर्णांक seq_client_load[15] = अणु[0 ... 14] = -1पूर्ण;
#पूर्ण_अगर
पूर्णांक seq_शेष_समयr_class = SNDRV_TIMER_CLASS_GLOBAL;
पूर्णांक seq_शेष_समयr_sclass = SNDRV_TIMER_SCLASS_NONE;
पूर्णांक seq_शेष_समयr_card = -1;
पूर्णांक seq_शेष_समयr_device =
#अगर_घोषित CONFIG_SND_SEQ_HRTIMER_DEFAULT
	SNDRV_TIMER_GLOBAL_HRTIMER
#अन्यथा
	SNDRV_TIMER_GLOBAL_SYSTEM
#पूर्ण_अगर
	;
पूर्णांक seq_शेष_समयr_subdevice = 0;
पूर्णांक seq_शेष_समयr_resolution = 0;	/* Hz */

MODULE_AUTHOR("Frank van de Pol <fvdpol@coil.demon.nl>, Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Advanced Linux Sound Architecture sequencer.");
MODULE_LICENSE("GPL");

module_param_array(seq_client_load, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(seq_client_load, "The numbers of global (system) clients to load through kmod.");
module_param(seq_शेष_समयr_class, पूर्णांक, 0644);
MODULE_PARM_DESC(seq_शेष_समयr_class, "The default timer class.");
module_param(seq_शेष_समयr_sclass, पूर्णांक, 0644);
MODULE_PARM_DESC(seq_शेष_समयr_sclass, "The default timer slave class.");
module_param(seq_शेष_समयr_card, पूर्णांक, 0644);
MODULE_PARM_DESC(seq_शेष_समयr_card, "The default timer card number.");
module_param(seq_शेष_समयr_device, पूर्णांक, 0644);
MODULE_PARM_DESC(seq_शेष_समयr_device, "The default timer device number.");
module_param(seq_शेष_समयr_subdevice, पूर्णांक, 0644);
MODULE_PARM_DESC(seq_शेष_समयr_subdevice, "The default timer subdevice number.");
module_param(seq_शेष_समयr_resolution, पूर्णांक, 0644);
MODULE_PARM_DESC(seq_शेष_समयr_resolution, "The default timer resolution in Hz.");

MODULE_ALIAS_CHARDEV(CONFIG_SND_MAJOR, SNDRV_MINOR_SEQUENCER);
MODULE_ALIAS("devname:snd/seq");

/*
 *  INIT PART
 */

अटल पूर्णांक __init alsa_seq_init(व्योम)
अणु
	पूर्णांक err;

	err = client_init_data();
	अगर (err < 0)
		जाओ error;

	/* रेजिस्टर sequencer device */
	err = snd_sequencer_device_init();
	अगर (err < 0)
		जाओ error;

	/* रेजिस्टर proc पूर्णांकerface */
	err = snd_seq_info_init();
	अगर (err < 0)
		जाओ error_device;

	/* रेजिस्टर our पूर्णांकernal client */
	err = snd_seq_प्रणाली_client_init();
	अगर (err < 0)
		जाओ error_info;

	snd_seq_स्वतःload_init();
	वापस 0;

 error_info:
	snd_seq_info_करोne();
 error_device:
	snd_sequencer_device_करोne();
 error:
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_seq_निकास(व्योम)
अणु
	/* unरेजिस्टर our पूर्णांकernal client */
	snd_seq_प्रणाली_client_करोne();

	/* unरेजिस्टर proc पूर्णांकerface */
	snd_seq_info_करोne();
	
	/* delete timing queues */
	snd_seq_queues_delete();

	/* unरेजिस्टर sequencer device */
	snd_sequencer_device_करोne();

	snd_seq_स्वतःload_निकास();
पूर्ण

module_init(alsa_seq_init)
module_निकास(alsa_seq_निकास)
