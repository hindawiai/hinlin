<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ioctl32.c: Conversion between 32bit and 64bit native ioctls.
 *	Separated from fs stuff by Arnd Bergmann <arnd@arndb.de>
 *
 * Copyright (C) 1997-2000  Jakub Jelinek  (jakub@redhat.com)
 * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 2001,2002  Andi Kleen, SuSE Lअसल
 * Copyright (C) 2003       Pavel Machek (pavel@ucw.cz)
 * Copyright (C) 2005       Philippe De Muyter (phdm@macqel.be)
 * Copyright (C) 2008       Hans Verkuil <hverkuil@xs4all.nl>
 *
 * These routines मुख्यtain argument size conversion between 32bit and 64bit
 * ioctls.
 */

#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-subdev.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-ioctl.h>

/*
 * Per-ioctl data copy handlers.
 *
 * Those come in pairs, with a get_v4l2_foo() and a put_v4l2_foo() routine,
 * where "v4l2_foo" is the name of the V4L2 काष्ठा.
 *
 * They basically get two __user poपूर्णांकers, one with a 32-bits काष्ठा that
 * came from the userspace call and a 64-bits काष्ठा, also allocated as
 * userspace, but filled पूर्णांकernally by करो_video_ioctl().
 *
 * For ioctls that have poपूर्णांकers inside it, the functions will also
 * receive an ancillary buffer with extra space, used to pass extra
 * data to the routine.
 */

काष्ठा v4l2_clip32 अणु
	काष्ठा v4l2_rect        c;
	compat_caddr_t		next;
पूर्ण;

काष्ठा v4l2_winकरोw32 अणु
	काष्ठा v4l2_rect        w;
	__u32			field;	/* क्रमागत v4l2_field */
	__u32			chromakey;
	compat_caddr_t		clips; /* actually काष्ठा v4l2_clip32 * */
	__u32			clipcount;
	compat_caddr_t		biपंचांगap;
	__u8                    global_alpha;
पूर्ण;

अटल पूर्णांक get_v4l2_winकरोw32(काष्ठा v4l2_winकरोw *p64,
			     काष्ठा v4l2_winकरोw32 __user *p32)
अणु
	काष्ठा v4l2_winकरोw32 w32;

	अगर (copy_from_user(&w32, p32, माप(w32)))
		वापस -EFAULT;

	*p64 = (काष्ठा v4l2_winकरोw) अणु
		.w		= w32.w,
		.field		= w32.field,
		.chromakey	= w32.chromakey,
		.clips		= (व्योम __क्रमce *)compat_ptr(w32.clips),
		.clipcount	= w32.clipcount,
		.biपंचांगap		= compat_ptr(w32.biपंचांगap),
		.global_alpha	= w32.global_alpha,
	पूर्ण;

	अगर (p64->clipcount > 2048)
		वापस -EINVAL;
	अगर (!p64->clipcount)
		p64->clips = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक put_v4l2_winकरोw32(काष्ठा v4l2_winकरोw *p64,
			     काष्ठा v4l2_winकरोw32 __user *p32)
अणु
	काष्ठा v4l2_winकरोw32 w32;

	स_रखो(&w32, 0, माप(w32));
	w32 = (काष्ठा v4l2_winकरोw32) अणु
		.w		= p64->w,
		.field		= p64->field,
		.chromakey	= p64->chromakey,
		.clips		= (uपूर्णांकptr_t)p64->clips,
		.clipcount	= p64->clipcount,
		.biपंचांगap		= ptr_to_compat(p64->biपंचांगap),
		.global_alpha	= p64->global_alpha,
	पूर्ण;

	/* copy everything except the clips poपूर्णांकer */
	अगर (copy_to_user(p32, &w32, दुरत्व(काष्ठा v4l2_winकरोw32, clips)) ||
	    copy_to_user(&p32->clipcount, &w32.clipcount,
			 माप(w32) - दुरत्व(काष्ठा v4l2_winकरोw32, clipcount)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

काष्ठा v4l2_क्रमmat32 अणु
	__u32	type;	/* क्रमागत v4l2_buf_type */
	जोड़ अणु
		काष्ठा v4l2_pix_क्रमmat	pix;
		काष्ठा v4l2_pix_क्रमmat_mplane	pix_mp;
		काष्ठा v4l2_winकरोw32	win;
		काष्ठा v4l2_vbi_क्रमmat	vbi;
		काष्ठा v4l2_sliced_vbi_क्रमmat	sliced;
		काष्ठा v4l2_sdr_क्रमmat	sdr;
		काष्ठा v4l2_meta_क्रमmat	meta;
		__u8	raw_data[200];        /* user-defined */
	पूर्ण fmt;
पूर्ण;

/**
 * काष्ठा v4l2_create_buffers32 - VIDIOC_CREATE_BUFS32 argument
 * @index:	on वापस, index of the first created buffer
 * @count:	entry: number of requested buffers,
 *		वापस: number of created buffers
 * @memory:	buffer memory type
 * @क्रमmat:	frame क्रमmat, क्रम which buffers are requested
 * @capabilities: capabilities of this buffer type.
 * @reserved:	future extensions
 */
काष्ठा v4l2_create_buffers32 अणु
	__u32			index;
	__u32			count;
	__u32			memory;	/* क्रमागत v4l2_memory */
	काष्ठा v4l2_क्रमmat32	क्रमmat;
	__u32			capabilities;
	__u32			reserved[7];
पूर्ण;

अटल पूर्णांक get_v4l2_क्रमmat32(काष्ठा v4l2_क्रमmat *p64,
			     काष्ठा v4l2_क्रमmat32 __user *p32)
अणु
	अगर (get_user(p64->type, &p32->type))
		वापस -EFAULT;

	चयन (p64->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस copy_from_user(&p64->fmt.pix, &p32->fmt.pix,
				      माप(p64->fmt.pix)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		वापस copy_from_user(&p64->fmt.pix_mp, &p32->fmt.pix_mp,
				      माप(p64->fmt.pix_mp)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		वापस get_v4l2_winकरोw32(&p64->fmt.win, &p32->fmt.win);
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		वापस copy_from_user(&p64->fmt.vbi, &p32->fmt.vbi,
				      माप(p64->fmt.vbi)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		वापस copy_from_user(&p64->fmt.sliced, &p32->fmt.sliced,
				      माप(p64->fmt.sliced)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		वापस copy_from_user(&p64->fmt.sdr, &p32->fmt.sdr,
				      माप(p64->fmt.sdr)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_META_CAPTURE:
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		वापस copy_from_user(&p64->fmt.meta, &p32->fmt.meta,
				      माप(p64->fmt.meta)) ? -EFAULT : 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक get_v4l2_create32(काष्ठा v4l2_create_buffers *p64,
			     काष्ठा v4l2_create_buffers32 __user *p32)
अणु
	अगर (copy_from_user(p64, p32,
			   दुरत्व(काष्ठा v4l2_create_buffers32, क्रमmat)))
		वापस -EFAULT;
	वापस get_v4l2_क्रमmat32(&p64->क्रमmat, &p32->क्रमmat);
पूर्ण

अटल पूर्णांक put_v4l2_क्रमmat32(काष्ठा v4l2_क्रमmat *p64,
			     काष्ठा v4l2_क्रमmat32 __user *p32)
अणु
	चयन (p64->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस copy_to_user(&p32->fmt.pix, &p64->fmt.pix,
				    माप(p64->fmt.pix)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		वापस copy_to_user(&p32->fmt.pix_mp, &p64->fmt.pix_mp,
				    माप(p64->fmt.pix_mp)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		वापस put_v4l2_winकरोw32(&p64->fmt.win, &p32->fmt.win);
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		वापस copy_to_user(&p32->fmt.vbi, &p64->fmt.vbi,
				    माप(p64->fmt.vbi)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		वापस copy_to_user(&p32->fmt.sliced, &p64->fmt.sliced,
				    माप(p64->fmt.sliced)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		वापस copy_to_user(&p32->fmt.sdr, &p64->fmt.sdr,
				    माप(p64->fmt.sdr)) ? -EFAULT : 0;
	हाल V4L2_BUF_TYPE_META_CAPTURE:
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		वापस copy_to_user(&p32->fmt.meta, &p64->fmt.meta,
				    माप(p64->fmt.meta)) ? -EFAULT : 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक put_v4l2_create32(काष्ठा v4l2_create_buffers *p64,
			     काष्ठा v4l2_create_buffers32 __user *p32)
अणु
	अगर (copy_to_user(p32, p64,
			 दुरत्व(काष्ठा v4l2_create_buffers32, क्रमmat)) ||
	    put_user(p64->capabilities, &p32->capabilities) ||
	    copy_to_user(p32->reserved, p64->reserved, माप(p64->reserved)))
		वापस -EFAULT;
	वापस put_v4l2_क्रमmat32(&p64->क्रमmat, &p32->क्रमmat);
पूर्ण

काष्ठा v4l2_standard32 अणु
	__u32		     index;
	compat_u64	     id;
	__u8		     name[24];
	काष्ठा v4l2_fract    frameperiod; /* Frames, not fields */
	__u32		     framelines;
	__u32		     reserved[4];
पूर्ण;

अटल पूर्णांक get_v4l2_standard32(काष्ठा v4l2_standard *p64,
			       काष्ठा v4l2_standard32 __user *p32)
अणु
	/* other fields are not set by the user, nor used by the driver */
	वापस get_user(p64->index, &p32->index);
पूर्ण

अटल पूर्णांक put_v4l2_standard32(काष्ठा v4l2_standard *p64,
			       काष्ठा v4l2_standard32 __user *p32)
अणु
	अगर (put_user(p64->index, &p32->index) ||
	    put_user(p64->id, &p32->id) ||
	    copy_to_user(p32->name, p64->name, माप(p32->name)) ||
	    copy_to_user(&p32->frameperiod, &p64->frameperiod,
			 माप(p32->frameperiod)) ||
	    put_user(p64->framelines, &p32->framelines) ||
	    copy_to_user(p32->reserved, p64->reserved, माप(p32->reserved)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

काष्ठा v4l2_plane32 अणु
	__u32			bytesused;
	__u32			length;
	जोड़ अणु
		__u32		mem_offset;
		compat_दीर्घ_t	userptr;
		__s32		fd;
	पूर्ण m;
	__u32			data_offset;
	__u32			reserved[11];
पूर्ण;

/*
 * This is correct क्रम all architectures including i386, but not x32,
 * which has dअगरferent alignment requirements क्रम बारtamp
 */
काष्ठा v4l2_buffer32 अणु
	__u32			index;
	__u32			type;	/* क्रमागत v4l2_buf_type */
	__u32			bytesused;
	__u32			flags;
	__u32			field;	/* क्रमागत v4l2_field */
	काष्ठा अणु
		compat_s64	tv_sec;
		compat_s64	tv_usec;
	पूर्ण			बारtamp;
	काष्ठा v4l2_समयcode	समयcode;
	__u32			sequence;

	/* memory location */
	__u32			memory;	/* क्रमागत v4l2_memory */
	जोड़ अणु
		__u32           offset;
		compat_दीर्घ_t   userptr;
		compat_caddr_t  planes;
		__s32		fd;
	पूर्ण m;
	__u32			length;
	__u32			reserved2;
	__s32			request_fd;
पूर्ण;

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
काष्ठा v4l2_buffer32_समय32 अणु
	__u32			index;
	__u32			type;	/* क्रमागत v4l2_buf_type */
	__u32			bytesused;
	__u32			flags;
	__u32			field;	/* क्रमागत v4l2_field */
	काष्ठा old_समयval32	बारtamp;
	काष्ठा v4l2_समयcode	समयcode;
	__u32			sequence;

	/* memory location */
	__u32			memory;	/* क्रमागत v4l2_memory */
	जोड़ अणु
		__u32           offset;
		compat_दीर्घ_t   userptr;
		compat_caddr_t  planes;
		__s32		fd;
	पूर्ण m;
	__u32			length;
	__u32			reserved2;
	__s32			request_fd;
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक get_v4l2_plane32(काष्ठा v4l2_plane *p64,
			    काष्ठा v4l2_plane32 __user *p32,
			    क्रमागत v4l2_memory memory)
अणु
	काष्ठा v4l2_plane32 plane32;
	typeof(p64->m) m = अणुपूर्ण;

	अगर (copy_from_user(&plane32, p32, माप(plane32)))
		वापस -EFAULT;

	चयन (memory) अणु
	हाल V4L2_MEMORY_MMAP:
	हाल V4L2_MEMORY_OVERLAY:
		m.mem_offset = plane32.m.mem_offset;
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		m.userptr = (अचिन्हित दीर्घ)compat_ptr(plane32.m.userptr);
		अवरोध;
	हाल V4L2_MEMORY_DMABUF:
		m.fd = plane32.m.fd;
		अवरोध;
	पूर्ण

	स_रखो(p64, 0, माप(*p64));
	*p64 = (काष्ठा v4l2_plane) अणु
		.bytesused	= plane32.bytesused,
		.length		= plane32.length,
		.m		= m,
		.data_offset	= plane32.data_offset,
	पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक put_v4l2_plane32(काष्ठा v4l2_plane *p64,
			    काष्ठा v4l2_plane32 __user *p32,
			    क्रमागत v4l2_memory memory)
अणु
	काष्ठा v4l2_plane32 plane32;

	स_रखो(&plane32, 0, माप(plane32));
	plane32 = (काष्ठा v4l2_plane32) अणु
		.bytesused	= p64->bytesused,
		.length		= p64->length,
		.data_offset	= p64->data_offset,
	पूर्ण;

	चयन (memory) अणु
	हाल V4L2_MEMORY_MMAP:
	हाल V4L2_MEMORY_OVERLAY:
		plane32.m.mem_offset = p64->m.mem_offset;
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		plane32.m.userptr = (uपूर्णांकptr_t)(p64->m.userptr);
		अवरोध;
	हाल V4L2_MEMORY_DMABUF:
		plane32.m.fd = p64->m.fd;
		अवरोध;
	पूर्ण

	अगर (copy_to_user(p32, &plane32, माप(plane32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_v4l2_buffer32(काष्ठा v4l2_buffer *vb,
			     काष्ठा v4l2_buffer32 __user *arg)
अणु
	काष्ठा v4l2_buffer32 vb32;

	अगर (copy_from_user(&vb32, arg, माप(vb32)))
		वापस -EFAULT;

	स_रखो(vb, 0, माप(*vb));
	*vb = (काष्ठा v4l2_buffer) अणु
		.index		= vb32.index,
		.type		= vb32.type,
		.bytesused	= vb32.bytesused,
		.flags		= vb32.flags,
		.field		= vb32.field,
		.बारtamp.tv_sec	= vb32.बारtamp.tv_sec,
		.बारtamp.tv_usec	= vb32.बारtamp.tv_usec,
		.समयcode	= vb32.समयcode,
		.sequence	= vb32.sequence,
		.memory		= vb32.memory,
		.m.offset	= vb32.m.offset,
		.length		= vb32.length,
		.request_fd	= vb32.request_fd,
	पूर्ण;

	चयन (vb->memory) अणु
	हाल V4L2_MEMORY_MMAP:
	हाल V4L2_MEMORY_OVERLAY:
		vb->m.offset = vb32.m.offset;
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		vb->m.userptr = (अचिन्हित दीर्घ)compat_ptr(vb32.m.userptr);
		अवरोध;
	हाल V4L2_MEMORY_DMABUF:
		vb->m.fd = vb32.m.fd;
		अवरोध;
	पूर्ण

	अगर (V4L2_TYPE_IS_MULTIPLANAR(vb->type))
		vb->m.planes = (व्योम __क्रमce *)
				compat_ptr(vb32.m.planes);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
अटल पूर्णांक get_v4l2_buffer32_समय32(काष्ठा v4l2_buffer *vb,
				    काष्ठा v4l2_buffer32_समय32 __user *arg)
अणु
	काष्ठा v4l2_buffer32_समय32 vb32;

	अगर (copy_from_user(&vb32, arg, माप(vb32)))
		वापस -EFAULT;

	*vb = (काष्ठा v4l2_buffer) अणु
		.index		= vb32.index,
		.type		= vb32.type,
		.bytesused	= vb32.bytesused,
		.flags		= vb32.flags,
		.field		= vb32.field,
		.बारtamp.tv_sec	= vb32.बारtamp.tv_sec,
		.बारtamp.tv_usec	= vb32.बारtamp.tv_usec,
		.समयcode	= vb32.समयcode,
		.sequence	= vb32.sequence,
		.memory		= vb32.memory,
		.m.offset	= vb32.m.offset,
		.length		= vb32.length,
		.request_fd	= vb32.request_fd,
	पूर्ण;
	चयन (vb->memory) अणु
	हाल V4L2_MEMORY_MMAP:
	हाल V4L2_MEMORY_OVERLAY:
		vb->m.offset = vb32.m.offset;
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		vb->m.userptr = (अचिन्हित दीर्घ)compat_ptr(vb32.m.userptr);
		अवरोध;
	हाल V4L2_MEMORY_DMABUF:
		vb->m.fd = vb32.m.fd;
		अवरोध;
	पूर्ण

	अगर (V4L2_TYPE_IS_MULTIPLANAR(vb->type))
		vb->m.planes = (व्योम __क्रमce *)
				compat_ptr(vb32.m.planes);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक put_v4l2_buffer32(काष्ठा v4l2_buffer *vb,
			     काष्ठा v4l2_buffer32 __user *arg)
अणु
	काष्ठा v4l2_buffer32 vb32;

	स_रखो(&vb32, 0, माप(vb32));
	vb32 = (काष्ठा v4l2_buffer32) अणु
		.index		= vb->index,
		.type		= vb->type,
		.bytesused	= vb->bytesused,
		.flags		= vb->flags,
		.field		= vb->field,
		.बारtamp.tv_sec	= vb->बारtamp.tv_sec,
		.बारtamp.tv_usec	= vb->बारtamp.tv_usec,
		.समयcode	= vb->समयcode,
		.sequence	= vb->sequence,
		.memory		= vb->memory,
		.m.offset	= vb->m.offset,
		.length		= vb->length,
		.request_fd	= vb->request_fd,
	पूर्ण;

	चयन (vb->memory) अणु
	हाल V4L2_MEMORY_MMAP:
	हाल V4L2_MEMORY_OVERLAY:
		vb32.m.offset = vb->m.offset;
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		vb32.m.userptr = (uपूर्णांकptr_t)(vb->m.userptr);
		अवरोध;
	हाल V4L2_MEMORY_DMABUF:
		vb32.m.fd = vb->m.fd;
		अवरोध;
	पूर्ण

	अगर (V4L2_TYPE_IS_MULTIPLANAR(vb->type))
		vb32.m.planes = (uपूर्णांकptr_t)vb->m.planes;

	अगर (copy_to_user(arg, &vb32, माप(vb32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
अटल पूर्णांक put_v4l2_buffer32_समय32(काष्ठा v4l2_buffer *vb,
				    काष्ठा v4l2_buffer32_समय32 __user *arg)
अणु
	काष्ठा v4l2_buffer32_समय32 vb32;

	स_रखो(&vb32, 0, माप(vb32));
	vb32 = (काष्ठा v4l2_buffer32_समय32) अणु
		.index		= vb->index,
		.type		= vb->type,
		.bytesused	= vb->bytesused,
		.flags		= vb->flags,
		.field		= vb->field,
		.बारtamp.tv_sec	= vb->बारtamp.tv_sec,
		.बारtamp.tv_usec	= vb->बारtamp.tv_usec,
		.समयcode	= vb->समयcode,
		.sequence	= vb->sequence,
		.memory		= vb->memory,
		.m.offset	= vb->m.offset,
		.length		= vb->length,
		.request_fd	= vb->request_fd,
	पूर्ण;
	चयन (vb->memory) अणु
	हाल V4L2_MEMORY_MMAP:
	हाल V4L2_MEMORY_OVERLAY:
		vb32.m.offset = vb->m.offset;
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		vb32.m.userptr = (uपूर्णांकptr_t)(vb->m.userptr);
		अवरोध;
	हाल V4L2_MEMORY_DMABUF:
		vb32.m.fd = vb->m.fd;
		अवरोध;
	पूर्ण

	अगर (V4L2_TYPE_IS_MULTIPLANAR(vb->type))
		vb32.m.planes = (uपूर्णांकptr_t)vb->m.planes;

	अगर (copy_to_user(arg, &vb32, माप(vb32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा v4l2_framebuffer32 अणु
	__u32			capability;
	__u32			flags;
	compat_caddr_t		base;
	काष्ठा अणु
		__u32		width;
		__u32		height;
		__u32		pixelक्रमmat;
		__u32		field;
		__u32		bytesperline;
		__u32		sizeimage;
		__u32		colorspace;
		__u32		priv;
	पूर्ण fmt;
पूर्ण;

अटल पूर्णांक get_v4l2_framebuffer32(काष्ठा v4l2_framebuffer *p64,
				  काष्ठा v4l2_framebuffer32 __user *p32)
अणु
	compat_caddr_t पंचांगp;

	अगर (get_user(पंचांगp, &p32->base) ||
	    get_user(p64->capability, &p32->capability) ||
	    get_user(p64->flags, &p32->flags) ||
	    copy_from_user(&p64->fmt, &p32->fmt, माप(p64->fmt)))
		वापस -EFAULT;
	p64->base = (व्योम __क्रमce *)compat_ptr(पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक put_v4l2_framebuffer32(काष्ठा v4l2_framebuffer *p64,
				  काष्ठा v4l2_framebuffer32 __user *p32)
अणु
	अगर (put_user((uपूर्णांकptr_t)p64->base, &p32->base) ||
	    put_user(p64->capability, &p32->capability) ||
	    put_user(p64->flags, &p32->flags) ||
	    copy_to_user(&p32->fmt, &p64->fmt, माप(p64->fmt)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

काष्ठा v4l2_input32 अणु
	__u32	     index;		/*  Which input */
	__u8	     name[32];		/*  Label */
	__u32	     type;		/*  Type of input */
	__u32	     audioset;		/*  Associated audios (bitfield) */
	__u32        tuner;             /*  Associated tuner */
	compat_u64   std;
	__u32	     status;
	__u32	     capabilities;
	__u32	     reserved[3];
पूर्ण;

/*
 * The 64-bit v4l2_input काष्ठा has extra padding at the end of the काष्ठा.
 * Otherwise it is identical to the 32-bit version.
 */
अटल अंतरभूत पूर्णांक get_v4l2_input32(काष्ठा v4l2_input *p64,
				   काष्ठा v4l2_input32 __user *p32)
अणु
	अगर (copy_from_user(p64, p32, माप(*p32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक put_v4l2_input32(काष्ठा v4l2_input *p64,
				   काष्ठा v4l2_input32 __user *p32)
अणु
	अगर (copy_to_user(p32, p64, माप(*p32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

काष्ठा v4l2_ext_controls32 अणु
	__u32 which;
	__u32 count;
	__u32 error_idx;
	__s32 request_fd;
	__u32 reserved[1];
	compat_caddr_t controls; /* actually काष्ठा v4l2_ext_control32 * */
पूर्ण;

काष्ठा v4l2_ext_control32 अणु
	__u32 id;
	__u32 size;
	__u32 reserved2[1];
	जोड़ अणु
		__s32 value;
		__s64 value64;
		compat_caddr_t string; /* actually अक्षर * */
	पूर्ण;
पूर्ण __attribute__ ((packed));

/* Return true अगर this control is a poपूर्णांकer type. */
अटल अंतरभूत bool ctrl_is_poपूर्णांकer(काष्ठा file *file, u32 id)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा v4l2_fh *fh = शून्य;
	काष्ठा v4l2_ctrl_handler *hdl = शून्य;
	काष्ठा v4l2_query_ext_ctrl qec = अणु id पूर्ण;
	स्थिर काष्ठा v4l2_ioctl_ops *ops = vdev->ioctl_ops;

	अगर (test_bit(V4L2_FL_USES_V4L2_FH, &vdev->flags))
		fh = file->निजी_data;

	अगर (fh && fh->ctrl_handler)
		hdl = fh->ctrl_handler;
	अन्यथा अगर (vdev->ctrl_handler)
		hdl = vdev->ctrl_handler;

	अगर (hdl) अणु
		काष्ठा v4l2_ctrl *ctrl = v4l2_ctrl_find(hdl, id);

		वापस ctrl && ctrl->is_ptr;
	पूर्ण

	अगर (!ops || !ops->vidioc_query_ext_ctrl)
		वापस false;

	वापस !ops->vidioc_query_ext_ctrl(file, fh, &qec) &&
		(qec.flags & V4L2_CTRL_FLAG_HAS_PAYLOAD);
पूर्ण

अटल पूर्णांक get_v4l2_ext_controls32(काष्ठा v4l2_ext_controls *p64,
				   काष्ठा v4l2_ext_controls32 __user *p32)
अणु
	काष्ठा v4l2_ext_controls32 ec32;

	अगर (copy_from_user(&ec32, p32, माप(ec32)))
		वापस -EFAULT;

	*p64 = (काष्ठा v4l2_ext_controls) अणु
		.which		= ec32.which,
		.count		= ec32.count,
		.error_idx	= ec32.error_idx,
		.request_fd	= ec32.request_fd,
		.reserved[0]	= ec32.reserved[0],
		.controls	= (व्योम __क्रमce *)compat_ptr(ec32.controls),
	पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक put_v4l2_ext_controls32(काष्ठा v4l2_ext_controls *p64,
				   काष्ठा v4l2_ext_controls32 __user *p32)
अणु
	काष्ठा v4l2_ext_controls32 ec32;

	स_रखो(&ec32, 0, माप(ec32));
	ec32 = (काष्ठा v4l2_ext_controls32) अणु
		.which		= p64->which,
		.count		= p64->count,
		.error_idx	= p64->error_idx,
		.request_fd	= p64->request_fd,
		.reserved[0]	= p64->reserved[0],
		.controls	= (uपूर्णांकptr_t)p64->controls,
	पूर्ण;

	अगर (copy_to_user(p32, &ec32, माप(ec32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_64
/*
 * x86 is the only compat architecture with dअगरferent काष्ठा alignment
 * between 32-bit and 64-bit tasks.
 *
 * On all other architectures, v4l2_event32 and v4l2_event32_समय32 are
 * the same as v4l2_event and v4l2_event_समय32, so we can use the native
 * handlers, converting v4l2_event to v4l2_event_समय32 अगर necessary.
 */
काष्ठा v4l2_event32 अणु
	__u32				type;
	जोड़ अणु
		compat_s64		value64;
		__u8			data[64];
	पूर्ण u;
	__u32				pending;
	__u32				sequence;
	काष्ठा अणु
		compat_s64		tv_sec;
		compat_s64		tv_nsec;
	पूर्ण बारtamp;
	__u32				id;
	__u32				reserved[8];
पूर्ण;

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
काष्ठा v4l2_event32_समय32 अणु
	__u32				type;
	जोड़ अणु
		compat_s64		value64;
		__u8			data[64];
	पूर्ण u;
	__u32				pending;
	__u32				sequence;
	काष्ठा old_बारpec32		बारtamp;
	__u32				id;
	__u32				reserved[8];
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक put_v4l2_event32(काष्ठा v4l2_event *p64,
			    काष्ठा v4l2_event32 __user *p32)
अणु
	अगर (put_user(p64->type, &p32->type) ||
	    copy_to_user(&p32->u, &p64->u, माप(p64->u)) ||
	    put_user(p64->pending, &p32->pending) ||
	    put_user(p64->sequence, &p32->sequence) ||
	    put_user(p64->बारtamp.tv_sec, &p32->बारtamp.tv_sec) ||
	    put_user(p64->बारtamp.tv_nsec, &p32->बारtamp.tv_nsec) ||
	    put_user(p64->id, &p32->id) ||
	    copy_to_user(p32->reserved, p64->reserved, माप(p32->reserved)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
अटल पूर्णांक put_v4l2_event32_समय32(काष्ठा v4l2_event *p64,
				   काष्ठा v4l2_event32_समय32 __user *p32)
अणु
	अगर (put_user(p64->type, &p32->type) ||
	    copy_to_user(&p32->u, &p64->u, माप(p64->u)) ||
	    put_user(p64->pending, &p32->pending) ||
	    put_user(p64->sequence, &p32->sequence) ||
	    put_user(p64->बारtamp.tv_sec, &p32->बारtamp.tv_sec) ||
	    put_user(p64->बारtamp.tv_nsec, &p32->बारtamp.tv_nsec) ||
	    put_user(p64->id, &p32->id) ||
	    copy_to_user(p32->reserved, p64->reserved, माप(p32->reserved)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

काष्ठा v4l2_edid32 अणु
	__u32 pad;
	__u32 start_block;
	__u32 blocks;
	__u32 reserved[5];
	compat_caddr_t edid;
पूर्ण;

अटल पूर्णांक get_v4l2_edid32(काष्ठा v4l2_edid *p64,
			   काष्ठा v4l2_edid32 __user *p32)
अणु
	compat_uptr_t edid;

	अगर (copy_from_user(p64, p32, दुरत्व(काष्ठा v4l2_edid32, edid)) ||
	    get_user(edid, &p32->edid))
		वापस -EFAULT;

	p64->edid = (व्योम __क्रमce *)compat_ptr(edid);
	वापस 0;
पूर्ण

अटल पूर्णांक put_v4l2_edid32(काष्ठा v4l2_edid *p64,
			   काष्ठा v4l2_edid32 __user *p32)
अणु
	अगर (copy_to_user(p32, p64, दुरत्व(काष्ठा v4l2_edid32, edid)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * List of ioctls that require 32-bits/64-bits conversion
 *
 * The V4L2 ioctls that aren't listed there don't have poपूर्णांकer arguments
 * and the काष्ठा size is identical क्रम both 32 and 64 bits versions, so
 * they करोn't need translations.
 */

#घोषणा VIDIOC_G_FMT32		_IOWR('V',  4, काष्ठा v4l2_क्रमmat32)
#घोषणा VIDIOC_S_FMT32		_IOWR('V',  5, काष्ठा v4l2_क्रमmat32)
#घोषणा VIDIOC_QUERYBUF32	_IOWR('V',  9, काष्ठा v4l2_buffer32)
#घोषणा VIDIOC_G_FBUF32		_IOR ('V', 10, काष्ठा v4l2_framebuffer32)
#घोषणा VIDIOC_S_FBUF32		_IOW ('V', 11, काष्ठा v4l2_framebuffer32)
#घोषणा VIDIOC_QBUF32		_IOWR('V', 15, काष्ठा v4l2_buffer32)
#घोषणा VIDIOC_DQBUF32		_IOWR('V', 17, काष्ठा v4l2_buffer32)
#घोषणा VIDIOC_ENUMSTD32	_IOWR('V', 25, काष्ठा v4l2_standard32)
#घोषणा VIDIOC_ENUMINPUT32	_IOWR('V', 26, काष्ठा v4l2_input32)
#घोषणा VIDIOC_G_EDID32		_IOWR('V', 40, काष्ठा v4l2_edid32)
#घोषणा VIDIOC_S_EDID32		_IOWR('V', 41, काष्ठा v4l2_edid32)
#घोषणा VIDIOC_TRY_FMT32	_IOWR('V', 64, काष्ठा v4l2_क्रमmat32)
#घोषणा VIDIOC_G_EXT_CTRLS32    _IOWR('V', 71, काष्ठा v4l2_ext_controls32)
#घोषणा VIDIOC_S_EXT_CTRLS32    _IOWR('V', 72, काष्ठा v4l2_ext_controls32)
#घोषणा VIDIOC_TRY_EXT_CTRLS32  _IOWR('V', 73, काष्ठा v4l2_ext_controls32)
#घोषणा	VIDIOC_DQEVENT32	_IOR ('V', 89, काष्ठा v4l2_event32)
#घोषणा VIDIOC_CREATE_BUFS32	_IOWR('V', 92, काष्ठा v4l2_create_buffers32)
#घोषणा VIDIOC_PREPARE_BUF32	_IOWR('V', 93, काष्ठा v4l2_buffer32)

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
#घोषणा VIDIOC_QUERYBUF32_TIME32	_IOWR('V',  9, काष्ठा v4l2_buffer32_समय32)
#घोषणा VIDIOC_QBUF32_TIME32		_IOWR('V', 15, काष्ठा v4l2_buffer32_समय32)
#घोषणा VIDIOC_DQBUF32_TIME32		_IOWR('V', 17, काष्ठा v4l2_buffer32_समय32)
#अगर_घोषित CONFIG_X86_64
#घोषणा	VIDIOC_DQEVENT32_TIME32		_IOR ('V', 89, काष्ठा v4l2_event32_समय32)
#पूर्ण_अगर
#घोषणा VIDIOC_PREPARE_BUF32_TIME32	_IOWR('V', 93, काष्ठा v4l2_buffer32_समय32)
#पूर्ण_अगर

अचिन्हित पूर्णांक v4l2_compat_translate_cmd(अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल VIDIOC_G_FMT32:
		वापस VIDIOC_G_FMT;
	हाल VIDIOC_S_FMT32:
		वापस VIDIOC_S_FMT;
	हाल VIDIOC_TRY_FMT32:
		वापस VIDIOC_TRY_FMT;
	हाल VIDIOC_G_FBUF32:
		वापस VIDIOC_G_FBUF;
	हाल VIDIOC_S_FBUF32:
		वापस VIDIOC_S_FBUF;
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_QUERYBUF32_TIME32:
		वापस VIDIOC_QUERYBUF;
	हाल VIDIOC_QBUF32_TIME32:
		वापस VIDIOC_QBUF;
	हाल VIDIOC_DQBUF32_TIME32:
		वापस VIDIOC_DQBUF;
	हाल VIDIOC_PREPARE_BUF32_TIME32:
		वापस VIDIOC_PREPARE_BUF;
#पूर्ण_अगर
	हाल VIDIOC_QUERYBUF32:
		वापस VIDIOC_QUERYBUF;
	हाल VIDIOC_QBUF32:
		वापस VIDIOC_QBUF;
	हाल VIDIOC_DQBUF32:
		वापस VIDIOC_DQBUF;
	हाल VIDIOC_CREATE_BUFS32:
		वापस VIDIOC_CREATE_BUFS;
	हाल VIDIOC_G_EXT_CTRLS32:
		वापस VIDIOC_G_EXT_CTRLS;
	हाल VIDIOC_S_EXT_CTRLS32:
		वापस VIDIOC_S_EXT_CTRLS;
	हाल VIDIOC_TRY_EXT_CTRLS32:
		वापस VIDIOC_TRY_EXT_CTRLS;
	हाल VIDIOC_PREPARE_BUF32:
		वापस VIDIOC_PREPARE_BUF;
	हाल VIDIOC_ENUMSTD32:
		वापस VIDIOC_ENUMSTD;
	हाल VIDIOC_ENUMINPUT32:
		वापस VIDIOC_ENUMINPUT;
	हाल VIDIOC_G_EDID32:
		वापस VIDIOC_G_EDID;
	हाल VIDIOC_S_EDID32:
		वापस VIDIOC_S_EDID;
#अगर_घोषित CONFIG_X86_64
	हाल VIDIOC_DQEVENT32:
		वापस VIDIOC_DQEVENT;
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_DQEVENT32_TIME32:
		वापस VIDIOC_DQEVENT;
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण
	वापस cmd;
पूर्ण

पूर्णांक v4l2_compat_get_user(व्योम __user *arg, व्योम *parg, अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल VIDIOC_G_FMT32:
	हाल VIDIOC_S_FMT32:
	हाल VIDIOC_TRY_FMT32:
		वापस get_v4l2_क्रमmat32(parg, arg);

	हाल VIDIOC_S_FBUF32:
		वापस get_v4l2_framebuffer32(parg, arg);
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_QUERYBUF32_TIME32:
	हाल VIDIOC_QBUF32_TIME32:
	हाल VIDIOC_DQBUF32_TIME32:
	हाल VIDIOC_PREPARE_BUF32_TIME32:
		वापस get_v4l2_buffer32_समय32(parg, arg);
#पूर्ण_अगर
	हाल VIDIOC_QUERYBUF32:
	हाल VIDIOC_QBUF32:
	हाल VIDIOC_DQBUF32:
	हाल VIDIOC_PREPARE_BUF32:
		वापस get_v4l2_buffer32(parg, arg);

	हाल VIDIOC_G_EXT_CTRLS32:
	हाल VIDIOC_S_EXT_CTRLS32:
	हाल VIDIOC_TRY_EXT_CTRLS32:
		वापस get_v4l2_ext_controls32(parg, arg);

	हाल VIDIOC_CREATE_BUFS32:
		वापस get_v4l2_create32(parg, arg);

	हाल VIDIOC_ENUMSTD32:
		वापस get_v4l2_standard32(parg, arg);

	हाल VIDIOC_ENUMINPUT32:
		वापस get_v4l2_input32(parg, arg);

	हाल VIDIOC_G_EDID32:
	हाल VIDIOC_S_EDID32:
		वापस get_v4l2_edid32(parg, arg);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक v4l2_compat_put_user(व्योम __user *arg, व्योम *parg, अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल VIDIOC_G_FMT32:
	हाल VIDIOC_S_FMT32:
	हाल VIDIOC_TRY_FMT32:
		वापस put_v4l2_क्रमmat32(parg, arg);

	हाल VIDIOC_G_FBUF32:
		वापस put_v4l2_framebuffer32(parg, arg);
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_QUERYBUF32_TIME32:
	हाल VIDIOC_QBUF32_TIME32:
	हाल VIDIOC_DQBUF32_TIME32:
	हाल VIDIOC_PREPARE_BUF32_TIME32:
		वापस put_v4l2_buffer32_समय32(parg, arg);
#पूर्ण_अगर
	हाल VIDIOC_QUERYBUF32:
	हाल VIDIOC_QBUF32:
	हाल VIDIOC_DQBUF32:
	हाल VIDIOC_PREPARE_BUF32:
		वापस put_v4l2_buffer32(parg, arg);

	हाल VIDIOC_G_EXT_CTRLS32:
	हाल VIDIOC_S_EXT_CTRLS32:
	हाल VIDIOC_TRY_EXT_CTRLS32:
		वापस put_v4l2_ext_controls32(parg, arg);

	हाल VIDIOC_CREATE_BUFS32:
		वापस put_v4l2_create32(parg, arg);

	हाल VIDIOC_ENUMSTD32:
		वापस put_v4l2_standard32(parg, arg);

	हाल VIDIOC_ENUMINPUT32:
		वापस put_v4l2_input32(parg, arg);

	हाल VIDIOC_G_EDID32:
	हाल VIDIOC_S_EDID32:
		वापस put_v4l2_edid32(parg, arg);
#अगर_घोषित CONFIG_X86_64
	हाल VIDIOC_DQEVENT32:
		वापस put_v4l2_event32(parg, arg);
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_DQEVENT32_TIME32:
		वापस put_v4l2_event32_समय32(parg, arg);
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक v4l2_compat_get_array_args(काष्ठा file *file, व्योम *mbuf,
			       व्योम __user *user_ptr, माप_प्रकार array_size,
			       अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल VIDIOC_G_FMT32:
	हाल VIDIOC_S_FMT32:
	हाल VIDIOC_TRY_FMT32: अणु
		काष्ठा v4l2_क्रमmat *f64 = arg;
		काष्ठा v4l2_clip *c64 = mbuf;
		काष्ठा v4l2_clip32 __user *c32 = user_ptr;
		u32 clipcount = f64->fmt.win.clipcount;

		अगर ((f64->type != V4L2_BUF_TYPE_VIDEO_OVERLAY &&
		     f64->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY) ||
		    clipcount == 0)
			वापस 0;
		अगर (clipcount > 2048)
			वापस -EINVAL;
		जबतक (clipcount--) अणु
			अगर (copy_from_user(c64, c32, माप(c64->c)))
				वापस -EFAULT;
			c64->next = शून्य;
			c64++;
			c32++;
		पूर्ण
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_QUERYBUF32_TIME32:
	हाल VIDIOC_QBUF32_TIME32:
	हाल VIDIOC_DQBUF32_TIME32:
	हाल VIDIOC_PREPARE_BUF32_TIME32:
#पूर्ण_अगर
	हाल VIDIOC_QUERYBUF32:
	हाल VIDIOC_QBUF32:
	हाल VIDIOC_DQBUF32:
	हाल VIDIOC_PREPARE_BUF32: अणु
		काष्ठा v4l2_buffer *b64 = arg;
		काष्ठा v4l2_plane *p64 = mbuf;
		काष्ठा v4l2_plane32 __user *p32 = user_ptr;

		अगर (V4L2_TYPE_IS_MULTIPLANAR(b64->type)) अणु
			u32 num_planes = b64->length;

			अगर (num_planes == 0)
				वापस 0;

			जबतक (num_planes--) अणु
				err = get_v4l2_plane32(p64, p32, b64->memory);
				अगर (err)
					वापस err;
				++p64;
				++p32;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल VIDIOC_G_EXT_CTRLS32:
	हाल VIDIOC_S_EXT_CTRLS32:
	हाल VIDIOC_TRY_EXT_CTRLS32: अणु
		काष्ठा v4l2_ext_controls *ecs64 = arg;
		काष्ठा v4l2_ext_control *ec64 = mbuf;
		काष्ठा v4l2_ext_control32 __user *ec32 = user_ptr;
		पूर्णांक n;

		क्रम (n = 0; n < ecs64->count; n++) अणु
			अगर (copy_from_user(ec64, ec32, माप(*ec32)))
				वापस -EFAULT;

			अगर (ctrl_is_poपूर्णांकer(file, ec64->id)) अणु
				compat_uptr_t p;

				अगर (get_user(p, &ec32->string))
					वापस -EFAULT;
				ec64->string = compat_ptr(p);
			पूर्ण
			ec32++;
			ec64++;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		अगर (copy_from_user(mbuf, user_ptr, array_size))
			err = -EFAULT;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक v4l2_compat_put_array_args(काष्ठा file *file, व्योम __user *user_ptr,
			       व्योम *mbuf, माप_प्रकार array_size,
			       अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल VIDIOC_G_FMT32:
	हाल VIDIOC_S_FMT32:
	हाल VIDIOC_TRY_FMT32: अणु
		काष्ठा v4l2_क्रमmat *f64 = arg;
		काष्ठा v4l2_clip *c64 = mbuf;
		काष्ठा v4l2_clip32 __user *c32 = user_ptr;
		u32 clipcount = f64->fmt.win.clipcount;

		अगर ((f64->type != V4L2_BUF_TYPE_VIDEO_OVERLAY &&
		     f64->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY) ||
		    clipcount == 0)
			वापस 0;
		अगर (clipcount > 2048)
			वापस -EINVAL;
		जबतक (clipcount--) अणु
			अगर (copy_to_user(c32, c64, माप(c64->c)))
				वापस -EFAULT;
			c64++;
			c32++;
		पूर्ण
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_QUERYBUF32_TIME32:
	हाल VIDIOC_QBUF32_TIME32:
	हाल VIDIOC_DQBUF32_TIME32:
	हाल VIDIOC_PREPARE_BUF32_TIME32:
#पूर्ण_अगर
	हाल VIDIOC_QUERYBUF32:
	हाल VIDIOC_QBUF32:
	हाल VIDIOC_DQBUF32:
	हाल VIDIOC_PREPARE_BUF32: अणु
		काष्ठा v4l2_buffer *b64 = arg;
		काष्ठा v4l2_plane *p64 = mbuf;
		काष्ठा v4l2_plane32 __user *p32 = user_ptr;

		अगर (V4L2_TYPE_IS_MULTIPLANAR(b64->type)) अणु
			u32 num_planes = b64->length;

			अगर (num_planes == 0)
				वापस 0;

			जबतक (num_planes--) अणु
				err = put_v4l2_plane32(p64, p32, b64->memory);
				अगर (err)
					वापस err;
				++p64;
				++p32;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल VIDIOC_G_EXT_CTRLS32:
	हाल VIDIOC_S_EXT_CTRLS32:
	हाल VIDIOC_TRY_EXT_CTRLS32: अणु
		काष्ठा v4l2_ext_controls *ecs64 = arg;
		काष्ठा v4l2_ext_control *ec64 = mbuf;
		काष्ठा v4l2_ext_control32 __user *ec32 = user_ptr;
		पूर्णांक n;

		क्रम (n = 0; n < ecs64->count; n++) अणु
			अचिन्हित पूर्णांक size = माप(*ec32);
			/*
			 * Do not modअगरy the poपूर्णांकer when copying a poपूर्णांकer
			 * control.  The contents of the poपूर्णांकer was changed,
			 * not the poपूर्णांकer itself.
			 * The काष्ठाures are otherwise compatible.
			 */
			अगर (ctrl_is_poपूर्णांकer(file, ec64->id))
				size -= माप(ec32->value64);

			अगर (copy_to_user(ec32, ec64, size))
				वापस -EFAULT;

			ec32++;
			ec64++;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		अगर (copy_to_user(user_ptr, mbuf, array_size))
			err = -EFAULT;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * v4l2_compat_ioctl32() - Handles a compat32 ioctl call
 *
 * @file: poपूर्णांकer to &काष्ठा file with the file handler
 * @cmd: ioctl to be called
 * @arg: arguments passed from/to the ioctl handler
 *
 * This function is meant to be used as .compat_ioctl fops at v4l2-dev.c
 * in order to deal with 32-bit calls on a 64-bits Kernel.
 *
 * This function calls करो_video_ioctl() क्रम non-निजी V4L2 ioctls.
 * If the function is a निजी one it calls vdev->fops->compat_ioctl32
 * instead.
 */
दीर्घ v4l2_compat_ioctl32(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	दीर्घ ret = -ENOIOCTLCMD;

	अगर (!file->f_op->unlocked_ioctl)
		वापस ret;

	अगर (_IOC_TYPE(cmd) == 'V' && _IOC_NR(cmd) < BASE_VIDIOC_PRIVATE)
		ret = file->f_op->unlocked_ioctl(file, cmd,
					(अचिन्हित दीर्घ)compat_ptr(arg));
	अन्यथा अगर (vdev->fops->compat_ioctl32)
		ret = vdev->fops->compat_ioctl32(file, cmd, arg);

	अगर (ret == -ENOIOCTLCMD)
		pr_debug("compat_ioctl32: unknown ioctl '%c', dir=%d, #%d (0x%08x)\n",
			 _IOC_TYPE(cmd), _IOC_सूची(cmd), _IOC_NR(cmd), cmd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_compat_ioctl32);
