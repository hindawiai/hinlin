<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vimc-streamer.c Virtual Media Controller Driver
 *
 * Copyright (C) 2018 Lucas A. M. Magalhथःes <lucmaga@gmail.com>
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "vimc-streamer.h"

/**
 * vimc_get_source_entity - get the entity connected with the first sink pad
 *
 * @ent:	reference media_entity
 *
 * Helper function that वापसs the media entity containing the source pad
 * linked with the first sink pad from the given media entity pad list.
 *
 * Return: The source pad or शून्य, अगर it wasn't found.
 */
अटल काष्ठा media_entity *vimc_get_source_entity(काष्ठा media_entity *ent)
अणु
	काष्ठा media_pad *pad;
	पूर्णांक i;

	क्रम (i = 0; i < ent->num_pads; i++) अणु
		अगर (ent->pads[i].flags & MEDIA_PAD_FL_SOURCE)
			जारी;
		pad = media_entity_remote_pad(&ent->pads[i]);
		वापस pad ? pad->entity : शून्य;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * vimc_streamer_pipeline_terminate - Disable stream in all ved in stream
 *
 * @stream: the poपूर्णांकer to the stream काष्ठाure with the pipeline to be
 *	    disabled.
 *
 * Calls s_stream to disable the stream in each entity of the pipeline
 *
 */
अटल व्योम vimc_streamer_pipeline_terminate(काष्ठा vimc_stream *stream)
अणु
	काष्ठा vimc_ent_device *ved;
	काष्ठा v4l2_subdev *sd;

	जबतक (stream->pipe_size) अणु
		stream->pipe_size--;
		ved = stream->ved_pipeline[stream->pipe_size];
		stream->ved_pipeline[stream->pipe_size] = शून्य;

		अगर (!is_media_entity_v4l2_subdev(ved->ent))
			जारी;

		sd = media_entity_to_v4l2_subdev(ved->ent);
		v4l2_subdev_call(sd, video, s_stream, 0);
	पूर्ण
पूर्ण

/**
 * vimc_streamer_pipeline_init - Initializes the stream काष्ठाure
 *
 * @stream: the poपूर्णांकer to the stream काष्ठाure to be initialized
 * @ved:    the poपूर्णांकer to the vimc entity initializing the stream
 *
 * Initializes the stream काष्ठाure. Walks through the entity graph to
 * स्थिरruct the pipeline used later on the streamer thपढ़ो.
 * Calls vimc_streamer_s_stream() to enable stream in all entities of
 * the pipeline.
 *
 * Return: 0 अगर success, error code otherwise.
 */
अटल पूर्णांक vimc_streamer_pipeline_init(काष्ठा vimc_stream *stream,
				       काष्ठा vimc_ent_device *ved)
अणु
	काष्ठा media_entity *entity;
	काष्ठा video_device *vdev;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret = 0;

	stream->pipe_size = 0;
	जबतक (stream->pipe_size < VIMC_STREAMER_PIPELINE_MAX_SIZE) अणु
		अगर (!ved) अणु
			vimc_streamer_pipeline_terminate(stream);
			वापस -EINVAL;
		पूर्ण
		stream->ved_pipeline[stream->pipe_size++] = ved;

		अगर (is_media_entity_v4l2_subdev(ved->ent)) अणु
			sd = media_entity_to_v4l2_subdev(ved->ent);
			ret = v4l2_subdev_call(sd, video, s_stream, 1);
			अगर (ret && ret != -ENOIOCTLCMD) अणु
				dev_err(ved->dev, "subdev_call error %s\n",
					ved->ent->name);
				vimc_streamer_pipeline_terminate(stream);
				वापस ret;
			पूर्ण
		पूर्ण

		entity = vimc_get_source_entity(ved->ent);
		/* Check अगर the end of the pipeline was reached */
		अगर (!entity) अणु
			/* the first entity of the pipe should be source only */
			अगर (!vimc_is_source(ved->ent)) अणु
				dev_err(ved->dev,
					"first entity in the pipe '%s' is not a source\n",
					ved->ent->name);
				vimc_streamer_pipeline_terminate(stream);
				वापस -EPIPE;
			पूर्ण
			वापस 0;
		पूर्ण

		/* Get the next device in the pipeline */
		अगर (is_media_entity_v4l2_subdev(entity)) अणु
			sd = media_entity_to_v4l2_subdev(entity);
			ved = v4l2_get_subdevdata(sd);
		पूर्ण अन्यथा अणु
			vdev = container_of(entity,
					    काष्ठा video_device,
					    entity);
			ved = video_get_drvdata(vdev);
		पूर्ण
	पूर्ण

	vimc_streamer_pipeline_terminate(stream);
	वापस -EINVAL;
पूर्ण

/**
 * vimc_streamer_thपढ़ो - Process frames through the pipeline
 *
 * @data:	vimc_stream काष्ठा of the current stream
 *
 * From the source to the sink, माला_लो a frame from each subdevice and send to
 * the next one of the pipeline at a fixed framerate.
 *
 * Return:
 * Always zero (created as ``पूर्णांक`` instead of ``व्योम`` to comply with
 * kthपढ़ो API).
 */
अटल पूर्णांक vimc_streamer_thपढ़ो(व्योम *data)
अणु
	काष्ठा vimc_stream *stream = data;
	u8 *frame = शून्य;
	पूर्णांक i;

	set_मुक्तzable();

	क्रम (;;) अणु
		try_to_मुक्तze();
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		क्रम (i = stream->pipe_size - 1; i >= 0; i--) अणु
			frame = stream->ved_pipeline[i]->process_frame(
					stream->ved_pipeline[i], frame);
			अगर (!frame || IS_ERR(frame))
				अवरोध;
		पूर्ण
		//रुको क्रम 60hz
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(HZ / 60);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vimc_streamer_s_stream - Start/stop the streaming on the media pipeline
 *
 * @stream:	the poपूर्णांकer to the stream काष्ठाure of the current stream
 * @ved:	poपूर्णांकer to the vimc entity of the entity of the stream
 * @enable:	flag to determine अगर stream should start/stop
 *
 * When starting, check अगर there is no ``stream->kthपढ़ो`` allocated. This
 * should indicate that a stream is alपढ़ोy running. Then, it initializes the
 * pipeline, creates and runs a kthपढ़ो to consume buffers through the pipeline.
 * When stopping, analogously check अगर there is a stream running, stop the
 * thपढ़ो and terminates the pipeline.
 *
 * Return: 0 अगर success, error code otherwise.
 */
पूर्णांक vimc_streamer_s_stream(काष्ठा vimc_stream *stream,
			   काष्ठा vimc_ent_device *ved,
			   पूर्णांक enable)
अणु
	पूर्णांक ret;

	अगर (!stream || !ved)
		वापस -EINVAL;

	अगर (enable) अणु
		अगर (stream->kthपढ़ो)
			वापस 0;

		ret = vimc_streamer_pipeline_init(stream, ved);
		अगर (ret)
			वापस ret;

		stream->kthपढ़ो = kthपढ़ो_run(vimc_streamer_thपढ़ो, stream,
					      "vimc-streamer thread");

		अगर (IS_ERR(stream->kthपढ़ो)) अणु
			ret = PTR_ERR(stream->kthपढ़ो);
			dev_err(ved->dev, "kthread_run failed with %d\n", ret);
			vimc_streamer_pipeline_terminate(stream);
			stream->kthपढ़ो = शून्य;
			वापस ret;
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (!stream->kthपढ़ो)
			वापस 0;

		ret = kthपढ़ो_stop(stream->kthपढ़ो);
		/*
		 * kthपढ़ो_stop वापसs -EINTR in हालs when streamon was
		 * immediately followed by streamoff, and the thपढ़ो didn't had
		 * a chance to run. Ignore errors to stop the stream in the
		 * pipeline.
		 */
		अगर (ret)
			dev_dbg(ved->dev, "kthread_stop returned '%d'\n", ret);

		stream->kthपढ़ो = शून्य;

		vimc_streamer_pipeline_terminate(stream);
	पूर्ण

	वापस 0;
पूर्ण
