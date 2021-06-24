<शैली गुरु>
/*
 * videobuf2-memops.h - generic memory handling routines क्रम videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *	   Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित _MEDIA_VIDEOBUF2_MEMOPS_H
#घोषणा _MEDIA_VIDEOBUF2_MEMOPS_H

#समावेश <media/videobuf2-v4l2.h>
#समावेश <linux/mm.h>
#समावेश <linux/refcount.h>

/**
 * काष्ठा vb2_vmarea_handler - common vma refcount tracking handler.
 *
 * @refcount:	poपूर्णांकer to &refcount_t entry in the buffer.
 * @put:	callback to function that decreases buffer refcount.
 * @arg:	argument क्रम @put callback.
 */
काष्ठा vb2_vmarea_handler अणु
	refcount_t		*refcount;
	व्योम			(*put)(व्योम *arg);
	व्योम			*arg;
पूर्ण;

बाह्य स्थिर काष्ठा vm_operations_काष्ठा vb2_common_vm_ops;

काष्ठा frame_vector *vb2_create_framevec(अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ length);
व्योम vb2_destroy_framevec(काष्ठा frame_vector *vec);

#पूर्ण_अगर
