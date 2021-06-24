<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_IO_H
#घोषणा __PVRUSB2_IO_H

#समावेश <linux/usb.h>
#समावेश <linux/list.h>

प्रकार व्योम (*pvr2_stream_callback)(व्योम *);

क्रमागत pvr2_buffer_state अणु
	pvr2_buffer_state_none = 0,   // Not on any list
	pvr2_buffer_state_idle = 1,   // Buffer is पढ़ोy to be used again
	pvr2_buffer_state_queued = 2, // Buffer has been queued क्रम filling
	pvr2_buffer_state_पढ़ोy = 3,  // Buffer has data available
पूर्ण;

काष्ठा pvr2_stream;
काष्ठा pvr2_buffer;

काष्ठा pvr2_stream_stats अणु
	अचिन्हित पूर्णांक buffers_in_queue;
	अचिन्हित पूर्णांक buffers_in_idle;
	अचिन्हित पूर्णांक buffers_in_पढ़ोy;
	अचिन्हित पूर्णांक buffers_processed;
	अचिन्हित पूर्णांक buffers_failed;
	अचिन्हित पूर्णांक bytes_processed;
पूर्ण;

/* Initialize / tear करोwn stream काष्ठाure */
काष्ठा pvr2_stream *pvr2_stream_create(व्योम);
व्योम pvr2_stream_destroy(काष्ठा pvr2_stream *);
व्योम pvr2_stream_setup(काष्ठा pvr2_stream *,
		       काष्ठा usb_device *dev,पूर्णांक endpoपूर्णांक,
		       अचिन्हित पूर्णांक tolerance);
व्योम pvr2_stream_set_callback(काष्ठा pvr2_stream *,
			      pvr2_stream_callback func,
			      व्योम *data);
व्योम pvr2_stream_get_stats(काष्ठा pvr2_stream *,
			   काष्ठा pvr2_stream_stats *,
			   पूर्णांक zero_counts);

/* Query / set the nominal buffer count */
पूर्णांक pvr2_stream_get_buffer_count(काष्ठा pvr2_stream *);
पूर्णांक pvr2_stream_set_buffer_count(काष्ठा pvr2_stream *,अचिन्हित पूर्णांक);

/* Get a poपूर्णांकer to a buffer that is either idle, पढ़ोy, or is specअगरied
   named. */
काष्ठा pvr2_buffer *pvr2_stream_get_idle_buffer(काष्ठा pvr2_stream *);
काष्ठा pvr2_buffer *pvr2_stream_get_पढ़ोy_buffer(काष्ठा pvr2_stream *);
काष्ठा pvr2_buffer *pvr2_stream_get_buffer(काष्ठा pvr2_stream *sp,पूर्णांक id);

/* Find out how many buffers are idle or पढ़ोy */
पूर्णांक pvr2_stream_get_पढ़ोy_count(काष्ठा pvr2_stream *);


/* Kill all pending buffers and throw away any पढ़ोy buffers as well */
व्योम pvr2_stream_समाप्त(काष्ठा pvr2_stream *);

/* Set up the actual storage क्रम a buffer */
पूर्णांक pvr2_buffer_set_buffer(काष्ठा pvr2_buffer *,व्योम *ptr,अचिन्हित पूर्णांक cnt);

/* Find out size of data in the given पढ़ोy buffer */
अचिन्हित पूर्णांक pvr2_buffer_get_count(काष्ठा pvr2_buffer *);

/* Retrieve completion code क्रम given पढ़ोy buffer */
पूर्णांक pvr2_buffer_get_status(काष्ठा pvr2_buffer *);

/* Retrieve ID of given buffer */
पूर्णांक pvr2_buffer_get_id(काष्ठा pvr2_buffer *);

/* Start पढ़ोing पूर्णांकo given buffer (समाप्त it अगर needed) */
पूर्णांक pvr2_buffer_queue(काष्ठा pvr2_buffer *);

#पूर्ण_अगर /* __PVRUSB2_IO_H */
