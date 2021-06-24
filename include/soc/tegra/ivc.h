<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __TEGRA_IVC_H

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/types.h>

काष्ठा tegra_ivc_header;

काष्ठा tegra_ivc अणु
	काष्ठा device *peer;

	काष्ठा अणु
		काष्ठा tegra_ivc_header *channel;
		अचिन्हित पूर्णांक position;
		dma_addr_t phys;
	पूर्ण rx, tx;

	व्योम (*notअगरy)(काष्ठा tegra_ivc *ivc, व्योम *data);
	व्योम *notअगरy_data;

	अचिन्हित पूर्णांक num_frames;
	माप_प्रकार frame_size;
पूर्ण;

/**
 * tegra_ivc_पढ़ो_get_next_frame - Peek at the next frame to receive
 * @ivc		poपूर्णांकer of the IVC channel
 *
 * Peek at the next frame to be received, without removing it from
 * the queue.
 *
 * Returns a poपूर्णांकer to the frame, or an error encoded poपूर्णांकer.
 */
व्योम *tegra_ivc_पढ़ो_get_next_frame(काष्ठा tegra_ivc *ivc);

/**
 * tegra_ivc_पढ़ो_advance - Advance the पढ़ो queue
 * @ivc		poपूर्णांकer of the IVC channel
 *
 * Advance the पढ़ो queue
 *
 * Returns 0, or a negative error value अगर failed.
 */
पूर्णांक tegra_ivc_पढ़ो_advance(काष्ठा tegra_ivc *ivc);

/**
 * tegra_ivc_ग_लिखो_get_next_frame - Poke at the next frame to transmit
 * @ivc		poपूर्णांकer of the IVC channel
 *
 * Get access to the next frame.
 *
 * Returns a poपूर्णांकer to the frame, or an error encoded poपूर्णांकer.
 */
व्योम *tegra_ivc_ग_लिखो_get_next_frame(काष्ठा tegra_ivc *ivc);

/**
 * tegra_ivc_ग_लिखो_advance - Advance the ग_लिखो queue
 * @ivc		poपूर्णांकer of the IVC channel
 *
 * Advance the ग_लिखो queue
 *
 * Returns 0, or a negative error value अगर failed.
 */
पूर्णांक tegra_ivc_ग_लिखो_advance(काष्ठा tegra_ivc *ivc);

/**
 * tegra_ivc_notअगरied - handle पूर्णांकernal messages
 * @ivc		poपूर्णांकer of the IVC channel
 *
 * This function must be called following every notअगरication.
 *
 * Returns 0 अगर the channel is पढ़ोy क्रम communication, or -EAGAIN अगर a channel
 * reset is in progress.
 */
पूर्णांक tegra_ivc_notअगरied(काष्ठा tegra_ivc *ivc);

/**
 * tegra_ivc_reset - initiates a reset of the shared memory state
 * @ivc		poपूर्णांकer of the IVC channel
 *
 * This function must be called after a channel is reserved beक्रमe it is used
 * क्रम communication. The channel will be पढ़ोy क्रम use when a subsequent call
 * to notअगरy the remote of the channel reset.
 */
व्योम tegra_ivc_reset(काष्ठा tegra_ivc *ivc);

माप_प्रकार tegra_ivc_align(माप_प्रकार size);
अचिन्हित tegra_ivc_total_queue_size(अचिन्हित queue_size);
पूर्णांक tegra_ivc_init(काष्ठा tegra_ivc *ivc, काष्ठा device *peer, व्योम *rx,
		   dma_addr_t rx_phys, व्योम *tx, dma_addr_t tx_phys,
		   अचिन्हित पूर्णांक num_frames, माप_प्रकार frame_size,
		   व्योम (*notअगरy)(काष्ठा tegra_ivc *ivc, व्योम *data),
		   व्योम *data);
व्योम tegra_ivc_cleanup(काष्ठा tegra_ivc *ivc);

#पूर्ण_अगर /* __TEGRA_IVC_H */
