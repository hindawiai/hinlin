<शैली गुरु>
/*
 * Copyright (C) ST-Ericsson AB 2012
 * Author: Sjur Brथइndeland <sjur.bअक्रमeland@stericsson.com>
 *
 * This header is BSD licensed so
 * anyone can use the definitions to implement compatible remote processors
 */

#अगर_अघोषित VIRTIO_CAIF_H
#घोषणा VIRTIO_CAIF_H

#समावेश <linux/types.h>
काष्ठा virtio_caअगर_transf_config अणु
	__virtio16 headroom;
	__virtio16 tailroom;
	__virtio32 mtu;
	u8 reserved[4];
पूर्ण;

काष्ठा virtio_caअगर_config अणु
	काष्ठा virtio_caअगर_transf_config uplink, करोwnlink;
	u8 reserved[8];
पूर्ण;
#पूर्ण_अगर
