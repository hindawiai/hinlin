<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_SOUND_FIREWIRE_H_INCLUDED
#घोषणा _UAPI_SOUND_FIREWIRE_H_INCLUDED

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/* events can be पढ़ो() from the hwdep device */

#घोषणा SNDRV_FIREWIRE_EVENT_LOCK_STATUS	0x000010cc
#घोषणा SNDRV_FIREWIRE_EVENT_DICE_NOTIFICATION	0xd1ce004e
#घोषणा SNDRV_FIREWIRE_EVENT_EFW_RESPONSE	0x4e617475
#घोषणा SNDRV_FIREWIRE_EVENT_DIGI00X_MESSAGE	0x746e736c
#घोषणा SNDRV_FIREWIRE_EVENT_MOTU_NOTIFICATION	0x64776479
#घोषणा SNDRV_FIREWIRE_EVENT_TASCAM_CONTROL	0x7473636d

काष्ठा snd_firewire_event_common अणु
	अचिन्हित पूर्णांक type; /* SNDRV_FIREWIRE_EVENT_xxx */
पूर्ण;

काष्ठा snd_firewire_event_lock_status अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक status; /* 0/1 = unlocked/locked */
पूर्ण;

काष्ठा snd_firewire_event_dice_notअगरication अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक notअगरication; /* DICE-specअगरic bits */
पूर्ण;

#घोषणा SND_EFW_TRANSACTION_USER_SEQNUM_MAX	((__u32)((__u16)~0) - 1)
/* each field should be in big endian */
काष्ठा snd_efw_transaction अणु
	__be32 length;
	__be32 version;
	__be32 seqnum;
	__be32 category;
	__be32 command;
	__be32 status;
	__be32 params[0];
पूर्ण;
काष्ठा snd_firewire_event_efw_response अणु
	अचिन्हित पूर्णांक type;
	__be32 response[0];	/* some responses */
पूर्ण;

काष्ठा snd_firewire_event_digi00x_message अणु
	अचिन्हित पूर्णांक type;
	__u32 message;	/* Digi00x-specअगरic message */
पूर्ण;

काष्ठा snd_firewire_event_motu_notअगरication अणु
	अचिन्हित पूर्णांक type;
	__u32 message;	/* MOTU-specअगरic bits. */
पूर्ण;

काष्ठा snd_firewire_tascam_change अणु
	अचिन्हित पूर्णांक index;
	__be32 beक्रमe;
	__be32 after;
पूर्ण;

काष्ठा snd_firewire_event_tascam_control अणु
	अचिन्हित पूर्णांक type;
	काष्ठा snd_firewire_tascam_change changes[0];
पूर्ण;

जोड़ snd_firewire_event अणु
	काष्ठा snd_firewire_event_common            common;
	काष्ठा snd_firewire_event_lock_status       lock_status;
	काष्ठा snd_firewire_event_dice_notअगरication dice_notअगरication;
	काष्ठा snd_firewire_event_efw_response      efw_response;
	काष्ठा snd_firewire_event_digi00x_message   digi00x_message;
	काष्ठा snd_firewire_event_tascam_control    tascam_control;
	काष्ठा snd_firewire_event_motu_notअगरication motu_notअगरication;
पूर्ण;


#घोषणा SNDRV_FIREWIRE_IOCTL_GET_INFO _IOR('H', 0xf8, काष्ठा snd_firewire_get_info)
#घोषणा SNDRV_FIREWIRE_IOCTL_LOCK      _IO('H', 0xf9)
#घोषणा SNDRV_FIREWIRE_IOCTL_UNLOCK    _IO('H', 0xfa)
#घोषणा SNDRV_FIREWIRE_IOCTL_TASCAM_STATE _IOR('H', 0xfb, काष्ठा snd_firewire_tascam_state)

#घोषणा SNDRV_FIREWIRE_TYPE_DICE	1
#घोषणा SNDRV_FIREWIRE_TYPE_FIREWORKS	2
#घोषणा SNDRV_FIREWIRE_TYPE_BEBOB	3
#घोषणा SNDRV_FIREWIRE_TYPE_OXFW	4
#घोषणा SNDRV_FIREWIRE_TYPE_DIGI00X	5
#घोषणा SNDRV_FIREWIRE_TYPE_TASCAM	6
#घोषणा SNDRV_FIREWIRE_TYPE_MOTU	7
#घोषणा SNDRV_FIREWIRE_TYPE_FIREFACE	8

काष्ठा snd_firewire_get_info अणु
	अचिन्हित पूर्णांक type; /* SNDRV_FIREWIRE_TYPE_xxx */
	अचिन्हित पूर्णांक card; /* same as fw_cdev_get_info.card */
	अचिन्हित अक्षर guid[8];
	अक्षर device_name[16]; /* device node in /dev */
पूर्ण;

/*
 * SNDRV_FIREWIRE_IOCTL_LOCK prevents the driver from streaming.
 * Returns -EBUSY अगर the driver is alपढ़ोy streaming.
 */

#घोषणा SNDRV_FIREWIRE_TASCAM_STATE_COUNT	64

काष्ठा snd_firewire_tascam_state अणु
	__be32 data[SNDRV_FIREWIRE_TASCAM_STATE_COUNT];
पूर्ण;

#पूर्ण_अगर /* _UAPI_SOUND_FIREWIRE_H_INCLUDED */
