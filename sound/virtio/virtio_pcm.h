<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#अगर_अघोषित VIRTIO_SND_PCM_H
#घोषणा VIRTIO_SND_PCM_H

#समावेश <linux/atomic.h>
#समावेश <linux/virtio_config.h>
#समावेश <sound/pcm.h>

काष्ठा virtio_pcm;
काष्ठा virtio_pcm_msg;

/**
 * काष्ठा virtio_pcm_substream - VirtIO PCM substream.
 * @snd: VirtIO sound device.
 * @nid: Function group node identअगरier.
 * @sid: Stream identअगरier.
 * @direction: Stream data flow direction (SNDRV_PCM_STREAM_XXX).
 * @features: Stream VirtIO feature bit map (1 << VIRTIO_SND_PCM_F_XXX).
 * @substream: Kernel ALSA substream.
 * @hw: Kernel ALSA substream hardware descriptor.
 * @elapsed_period: Kernel work to handle the elapsed period state.
 * @lock: Spinlock that protects fields shared by पूर्णांकerrupt handlers and
 *        substream चालकs.
 * @buffer_bytes: Current buffer size in bytes.
 * @hw_ptr: Substream hardware poपूर्णांकer value in bytes [0 ... buffer_bytes).
 * @xfer_enabled: Data transfer state (0 - off, 1 - on).
 * @xfer_xrun: Data underflow/overflow state (0 - no xrun, 1 - xrun).
 * @stopped: True अगर the substream is stopped and must be released on the device
 *           side.
 * @suspended: True अगर the substream is suspended and must be reconfigured on
 *             the device side at resume.
 * @msgs: Allocated I/O messages.
 * @nmsgs: Number of allocated I/O messages.
 * @msg_last_enqueued: Index of the last I/O message added to the virtqueue.
 * @msg_count: Number of pending I/O messages in the virtqueue.
 * @msg_empty: Notअगरy when msg_count is zero.
 */
काष्ठा virtio_pcm_substream अणु
	काष्ठा virtio_snd *snd;
	u32 nid;
	u32 sid;
	u32 direction;
	u32 features;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_hardware hw;
	काष्ठा work_काष्ठा elapsed_period;
	spinlock_t lock;
	माप_प्रकार buffer_bytes;
	माप_प्रकार hw_ptr;
	bool xfer_enabled;
	bool xfer_xrun;
	bool stopped;
	bool suspended;
	काष्ठा virtio_pcm_msg **msgs;
	अचिन्हित पूर्णांक nmsgs;
	पूर्णांक msg_last_enqueued;
	अचिन्हित पूर्णांक msg_count;
	रुको_queue_head_t msg_empty;
पूर्ण;

/**
 * काष्ठा virtio_pcm_stream - VirtIO PCM stream.
 * @substreams: VirtIO substreams beदीर्घing to the stream.
 * @nsubstreams: Number of substreams.
 * @chmaps: Kernel channel maps beदीर्घing to the stream.
 * @nchmaps: Number of channel maps.
 */
काष्ठा virtio_pcm_stream अणु
	काष्ठा virtio_pcm_substream **substreams;
	u32 nsubstreams;
	काष्ठा snd_pcm_chmap_elem *chmaps;
	u32 nchmaps;
पूर्ण;

/**
 * काष्ठा virtio_pcm - VirtIO PCM device.
 * @list: VirtIO PCM list entry.
 * @nid: Function group node identअगरier.
 * @pcm: Kernel PCM device.
 * @streams: VirtIO PCM streams (playback and capture).
 */
काष्ठा virtio_pcm अणु
	काष्ठा list_head list;
	u32 nid;
	काष्ठा snd_pcm *pcm;
	काष्ठा virtio_pcm_stream streams[SNDRV_PCM_STREAM_LAST + 1];
पूर्ण;

बाह्य स्थिर काष्ठा snd_pcm_ops virtsnd_pcm_ops;

पूर्णांक virtsnd_pcm_validate(काष्ठा virtio_device *vdev);

पूर्णांक virtsnd_pcm_parse_cfg(काष्ठा virtio_snd *snd);

पूर्णांक virtsnd_pcm_build_devs(काष्ठा virtio_snd *snd);

व्योम virtsnd_pcm_event(काष्ठा virtio_snd *snd, काष्ठा virtio_snd_event *event);

व्योम virtsnd_pcm_tx_notअगरy_cb(काष्ठा virtqueue *vqueue);

व्योम virtsnd_pcm_rx_notअगरy_cb(काष्ठा virtqueue *vqueue);

काष्ठा virtio_pcm *virtsnd_pcm_find(काष्ठा virtio_snd *snd, u32 nid);

काष्ठा virtio_pcm *virtsnd_pcm_find_or_create(काष्ठा virtio_snd *snd, u32 nid);

काष्ठा virtio_snd_msg *
virtsnd_pcm_ctl_msg_alloc(काष्ठा virtio_pcm_substream *vss,
			  अचिन्हित पूर्णांक command, gfp_t gfp);

पूर्णांक virtsnd_pcm_msg_alloc(काष्ठा virtio_pcm_substream *vss,
			  अचिन्हित पूर्णांक periods, अचिन्हित पूर्णांक period_bytes);

व्योम virtsnd_pcm_msg_मुक्त(काष्ठा virtio_pcm_substream *vss);

पूर्णांक virtsnd_pcm_msg_send(काष्ठा virtio_pcm_substream *vss);

अचिन्हित पूर्णांक virtsnd_pcm_msg_pending_num(काष्ठा virtio_pcm_substream *vss);

#पूर्ण_अगर /* VIRTIO_SND_PCM_H */
