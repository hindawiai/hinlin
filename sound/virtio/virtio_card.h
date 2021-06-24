<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#अगर_अघोषित VIRTIO_SND_CARD_H
#घोषणा VIRTIO_SND_CARD_H

#समावेश <linux/slab.h>
#समावेश <linux/virtपन.स>
#समावेश <sound/core.h>
#समावेश <uapi/linux/virtio_snd.h>

#समावेश "virtio_ctl_msg.h"
#समावेश "virtio_pcm.h"

#घोषणा VIRTIO_SND_CARD_DRIVER	"virtio-snd"
#घोषणा VIRTIO_SND_CARD_NAME	"VirtIO SoundCard"
#घोषणा VIRTIO_SND_PCM_NAME	"VirtIO PCM"

काष्ठा virtio_jack;
काष्ठा virtio_pcm_substream;

/**
 * काष्ठा virtio_snd_queue - Virtqueue wrapper काष्ठाure.
 * @lock: Used to synchronize access to a virtqueue.
 * @vqueue: Underlying virtqueue.
 */
काष्ठा virtio_snd_queue अणु
	spinlock_t lock;
	काष्ठा virtqueue *vqueue;
पूर्ण;

/**
 * काष्ठा virtio_snd - VirtIO sound card device.
 * @vdev: Underlying virtio device.
 * @queues: Virtqueue wrappers.
 * @card: ALSA sound card.
 * @ctl_msgs: Pending control request list.
 * @event_msgs: Device events.
 * @pcm_list: VirtIO PCM device list.
 * @jacks: VirtIO jacks.
 * @njacks: Number of jacks.
 * @substreams: VirtIO PCM substreams.
 * @nsubstreams: Number of PCM substreams.
 * @chmaps: VirtIO channel maps.
 * @nchmaps: Number of channel maps.
 */
काष्ठा virtio_snd अणु
	काष्ठा virtio_device *vdev;
	काष्ठा virtio_snd_queue queues[VIRTIO_SND_VQ_MAX];
	काष्ठा snd_card *card;
	काष्ठा list_head ctl_msgs;
	काष्ठा virtio_snd_event *event_msgs;
	काष्ठा list_head pcm_list;
	काष्ठा virtio_jack *jacks;
	u32 njacks;
	काष्ठा virtio_pcm_substream *substreams;
	u32 nsubstreams;
	काष्ठा virtio_snd_chmap_info *chmaps;
	u32 nchmaps;
पूर्ण;

/* Message completion समयout in milliseconds (module parameter). */
बाह्य u32 virtsnd_msg_समयout_ms;

अटल अंतरभूत काष्ठा virtio_snd_queue *
virtsnd_control_queue(काष्ठा virtio_snd *snd)
अणु
	वापस &snd->queues[VIRTIO_SND_VQ_CONTROL];
पूर्ण

अटल अंतरभूत काष्ठा virtio_snd_queue *
virtsnd_event_queue(काष्ठा virtio_snd *snd)
अणु
	वापस &snd->queues[VIRTIO_SND_VQ_EVENT];
पूर्ण

अटल अंतरभूत काष्ठा virtio_snd_queue *
virtsnd_tx_queue(काष्ठा virtio_snd *snd)
अणु
	वापस &snd->queues[VIRTIO_SND_VQ_TX];
पूर्ण

अटल अंतरभूत काष्ठा virtio_snd_queue *
virtsnd_rx_queue(काष्ठा virtio_snd *snd)
अणु
	वापस &snd->queues[VIRTIO_SND_VQ_RX];
पूर्ण

अटल अंतरभूत काष्ठा virtio_snd_queue *
virtsnd_pcm_queue(काष्ठा virtio_pcm_substream *vss)
अणु
	अगर (vss->direction == SNDRV_PCM_STREAM_PLAYBACK)
		वापस virtsnd_tx_queue(vss->snd);
	अन्यथा
		वापस virtsnd_rx_queue(vss->snd);
पूर्ण

पूर्णांक virtsnd_jack_parse_cfg(काष्ठा virtio_snd *snd);

पूर्णांक virtsnd_jack_build_devs(काष्ठा virtio_snd *snd);

व्योम virtsnd_jack_event(काष्ठा virtio_snd *snd,
			काष्ठा virtio_snd_event *event);

पूर्णांक virtsnd_chmap_parse_cfg(काष्ठा virtio_snd *snd);

पूर्णांक virtsnd_chmap_build_devs(काष्ठा virtio_snd *snd);

#पूर्ण_अगर /* VIRTIO_SND_CARD_H */
