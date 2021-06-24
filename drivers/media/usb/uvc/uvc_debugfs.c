<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_debugfs.c --  USB Video Class driver - Debugging support
 *
 *      Copyright (C) 2011
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "uvcvideo.h"

/* -----------------------------------------------------------------------------
 * Statistics
 */

#घोषणा UVC_DEBUGFS_BUF_SIZE	1024

काष्ठा uvc_debugfs_buffer अणु
	माप_प्रकार count;
	अक्षर data[UVC_DEBUGFS_BUF_SIZE];
पूर्ण;

अटल पूर्णांक uvc_debugfs_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uvc_streaming *stream = inode->i_निजी;
	काष्ठा uvc_debugfs_buffer *buf;

	buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf->count = uvc_video_stats_dump(stream, buf->data, माप(buf->data));

	file->निजी_data = buf;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार uvc_debugfs_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा uvc_debugfs_buffer *buf = file->निजी_data;

	वापस simple_पढ़ो_from_buffer(user_buf, nbytes, ppos, buf->data,
				       buf->count);
पूर्ण

अटल पूर्णांक uvc_debugfs_stats_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	file->निजी_data = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations uvc_debugfs_stats_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = uvc_debugfs_stats_खोलो,
	.llseek = no_llseek,
	.पढ़ो = uvc_debugfs_stats_पढ़ो,
	.release = uvc_debugfs_stats_release,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Global and stream initialization/cleanup
 */

अटल काष्ठा dentry *uvc_debugfs_root_dir;

व्योम uvc_debugfs_init_stream(काष्ठा uvc_streaming *stream)
अणु
	काष्ठा usb_device *udev = stream->dev->udev;
	अक्षर dir_name[33];

	अगर (uvc_debugfs_root_dir == शून्य)
		वापस;

	snम_लिखो(dir_name, माप(dir_name), "%u-%u-%u", udev->bus->busnum,
		 udev->devnum, stream->पूर्णांकfnum);

	stream->debugfs_dir = debugfs_create_dir(dir_name,
						 uvc_debugfs_root_dir);

	debugfs_create_file("stats", 0444, stream->debugfs_dir, stream,
			    &uvc_debugfs_stats_fops);
पूर्ण

व्योम uvc_debugfs_cleanup_stream(काष्ठा uvc_streaming *stream)
अणु
	debugfs_हटाओ_recursive(stream->debugfs_dir);
	stream->debugfs_dir = शून्य;
पूर्ण

व्योम uvc_debugfs_init(व्योम)
अणु
	uvc_debugfs_root_dir = debugfs_create_dir("uvcvideo", usb_debug_root);
पूर्ण

व्योम uvc_debugfs_cleanup(व्योम)
अणु
	debugfs_हटाओ_recursive(uvc_debugfs_root_dir);
पूर्ण
