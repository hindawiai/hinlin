<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * v4l2-fh.h
 *
 * V4L2 file handle. Store per file handle data क्रम the V4L2
 * framework. Using file handles is optional क्रम the drivers.
 *
 * Copyright (C) 2009--2010 Nokia Corporation.
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित V4L2_FH_H
#घोषणा V4L2_FH_H

#समावेश <linux/fs.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/list.h>
#समावेश <linux/videodev2.h>

काष्ठा video_device;
काष्ठा v4l2_ctrl_handler;

/**
 * काष्ठा v4l2_fh - Describes a V4L2 file handler
 *
 * @list: list of file handlers
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 * @ctrl_handler: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @prio: priority of the file handler, as defined by &क्रमागत v4l2_priority
 *
 * @रुको: event' s रुको queue
 * @subscribe_lock: serialise changes to the subscribed list; guarantee that
 *		    the add and del event callbacks are orderly called
 * @subscribed: list of subscribed events
 * @available: list of events रुकोing to be dequeued
 * @navailable: number of available events at @available list
 * @sequence: event sequence number
 *
 * @m2m_ctx: poपूर्णांकer to &काष्ठा v4l2_m2m_ctx
 */
काष्ठा v4l2_fh अणु
	काष्ठा list_head	list;
	काष्ठा video_device	*vdev;
	काष्ठा v4l2_ctrl_handler *ctrl_handler;
	क्रमागत v4l2_priority	prio;

	/* Events */
	रुको_queue_head_t	रुको;
	काष्ठा mutex		subscribe_lock;
	काष्ठा list_head	subscribed;
	काष्ठा list_head	available;
	अचिन्हित पूर्णांक		navailable;
	u32			sequence;

	काष्ठा v4l2_m2m_ctx	*m2m_ctx;
पूर्ण;

/**
 * v4l2_fh_init - Initialise the file handle.
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 *
 * Parts of the V4L2 framework using the
 * file handles should be initialised in this function. Must be called
 * from driver's v4l2_file_operations->खोलो\(\) handler अगर the driver
 * uses &काष्ठा v4l2_fh.
 */
व्योम v4l2_fh_init(काष्ठा v4l2_fh *fh, काष्ठा video_device *vdev);

/**
 * v4l2_fh_add - Add the fh to the list of file handles on a video_device.
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 *
 * .. note::
 *    The @fh file handle must be initialised first.
 */
व्योम v4l2_fh_add(काष्ठा v4l2_fh *fh);

/**
 * v4l2_fh_खोलो - Ancillary routine that can be used as the खोलो\(\) op
 *	of v4l2_file_operations.
 *
 * @filp: poपूर्णांकer to काष्ठा file
 *
 * It allocates a v4l2_fh and inits and adds it to the &काष्ठा video_device
 * associated with the file poपूर्णांकer.
 */
पूर्णांक v4l2_fh_खोलो(काष्ठा file *filp);

/**
 * v4l2_fh_del - Remove file handle from the list of file handles.
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 *
 * On error filp->निजी_data will be %शून्य, otherwise it will poपूर्णांक to
 * the &काष्ठा v4l2_fh.
 *
 * .. note::
 *    Must be called in v4l2_file_operations->release\(\) handler अगर the driver
 *    uses &काष्ठा v4l2_fh.
 */
व्योम v4l2_fh_del(काष्ठा v4l2_fh *fh);

/**
 * v4l2_fh_निकास - Release resources related to a file handle.
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 *
 * Parts of the V4L2 framework using the v4l2_fh must release their
 * resources here, too.
 *
 * .. note::
 *    Must be called in v4l2_file_operations->release\(\) handler अगर the
 *    driver uses &काष्ठा v4l2_fh.
 */
व्योम v4l2_fh_निकास(काष्ठा v4l2_fh *fh);

/**
 * v4l2_fh_release - Ancillary routine that can be used as the release\(\) op
 *	of v4l2_file_operations.
 *
 * @filp: poपूर्णांकer to काष्ठा file
 *
 * It deletes and निकासs the v4l2_fh associated with the file poपूर्णांकer and
 * मुक्तs it. It will करो nothing अगर filp->निजी_data (the poपूर्णांकer to the
 * v4l2_fh काष्ठा) is %शून्य.
 *
 * This function always वापसs 0.
 */
पूर्णांक v4l2_fh_release(काष्ठा file *filp);

/**
 * v4l2_fh_is_singular - Returns 1 अगर this filehandle is the only filehandle
 *	 खोलोed क्रम the associated video_device.
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 *
 * If @fh is शून्य, then it वापसs 0.
 */
पूर्णांक v4l2_fh_is_singular(काष्ठा v4l2_fh *fh);

/**
 * v4l2_fh_is_singular_file - Returns 1 अगर this filehandle is the only
 *	filehandle खोलोed क्रम the associated video_device.
 *
 * @filp: poपूर्णांकer to काष्ठा file
 *
 * This is a helper function variant of v4l2_fh_is_singular() with uses
 * काष्ठा file as argument.
 *
 * If filp->निजी_data is %शून्य, then it will वापस 0.
 */
अटल अंतरभूत पूर्णांक v4l2_fh_is_singular_file(काष्ठा file *filp)
अणु
	वापस v4l2_fh_is_singular(filp->निजी_data);
पूर्ण

#पूर्ण_अगर /* V4L2_EVENT_H */
