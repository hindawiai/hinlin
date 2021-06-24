<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vimc-streamer.h Virtual Media Controller Driver
 *
 * Copyright (C) 2018 Lucas A. M. Magalhथःes <lucmaga@gmail.com>
 *
 */

#अगर_अघोषित _VIMC_STREAMER_H_
#घोषणा _VIMC_STREAMER_H_

#समावेश <media/media-device.h>

#समावेश "vimc-common.h"

#घोषणा VIMC_STREAMER_PIPELINE_MAX_SIZE 16

/**
 * काष्ठा vimc_stream - काष्ठा that represents a stream in the pipeline
 *
 * @pipe:		the media pipeline object associated with this stream
 * @ved_pipeline:	array containing all the entities participating in the
 * 			stream. The order is from a video device (usually a
 *			capture device) where stream_on was called, to the
 *			entity generating the first base image to be
 *			processed in the pipeline.
 * @pipe_size:		size of @ved_pipeline
 * @kthपढ़ो:		thपढ़ो that generates the frames of the stream.
 *
 * When the user call stream_on in a video device, काष्ठा vimc_stream is
 * used to keep track of all entities and subdevices that generates and
 * process frames क्रम the stream.
 */
काष्ठा vimc_stream अणु
	काष्ठा media_pipeline pipe;
	काष्ठा vimc_ent_device *ved_pipeline[VIMC_STREAMER_PIPELINE_MAX_SIZE];
	अचिन्हित पूर्णांक pipe_size;
	काष्ठा task_काष्ठा *kthपढ़ो;
पूर्ण;

पूर्णांक vimc_streamer_s_stream(काष्ठा vimc_stream *stream,
			   काष्ठा vimc_ent_device *ved,
			   पूर्णांक enable);

#पूर्ण_अगर  //_VIMC_STREAMER_H_
