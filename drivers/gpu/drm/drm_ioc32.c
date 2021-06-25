<शैली गुरु>
/*
 * \पile drm_ioc32.c
 *
 * 32-bit ioctl compatibility routines क्रम the DRM.
 *
 * \चuthor Paul Mackerras <paulus@samba.org>
 *
 * Copyright (C) Paul Mackerras 2005.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#समावेश <linux/compat.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/export.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

#घोषणा DRM_IOCTL_VERSION32		DRM_IOWR(0x00, drm_version32_t)
#घोषणा DRM_IOCTL_GET_UNIQUE32		DRM_IOWR(0x01, drm_unique32_t)
#घोषणा DRM_IOCTL_GET_MAP32		DRM_IOWR(0x04, drm_map32_t)
#घोषणा DRM_IOCTL_GET_CLIENT32		DRM_IOWR(0x05, drm_client32_t)
#घोषणा DRM_IOCTL_GET_STATS32		DRM_IOR( 0x06, drm_stats32_t)

#घोषणा DRM_IOCTL_SET_UNIQUE32		DRM_IOW( 0x10, drm_unique32_t)
#घोषणा DRM_IOCTL_ADD_MAP32		DRM_IOWR(0x15, drm_map32_t)
#घोषणा DRM_IOCTL_ADD_BUFS32		DRM_IOWR(0x16, drm_buf_desc32_t)
#घोषणा DRM_IOCTL_MARK_BUFS32		DRM_IOW( 0x17, drm_buf_desc32_t)
#घोषणा DRM_IOCTL_INFO_BUFS32		DRM_IOWR(0x18, drm_buf_info32_t)
#घोषणा DRM_IOCTL_MAP_BUFS32		DRM_IOWR(0x19, drm_buf_map32_t)
#घोषणा DRM_IOCTL_FREE_BUFS32		DRM_IOW( 0x1a, drm_buf_मुक्त32_t)

#घोषणा DRM_IOCTL_RM_MAP32		DRM_IOW( 0x1b, drm_map32_t)

#घोषणा DRM_IOCTL_SET_SAREA_CTX32	DRM_IOW( 0x1c, drm_ctx_priv_map32_t)
#घोषणा DRM_IOCTL_GET_SAREA_CTX32	DRM_IOWR(0x1d, drm_ctx_priv_map32_t)

#घोषणा DRM_IOCTL_RES_CTX32		DRM_IOWR(0x26, drm_ctx_res32_t)
#घोषणा DRM_IOCTL_DMA32			DRM_IOWR(0x29, drm_dma32_t)

#घोषणा DRM_IOCTL_AGP_ENABLE32		DRM_IOW( 0x32, drm_agp_mode32_t)
#घोषणा DRM_IOCTL_AGP_INFO32		DRM_IOR( 0x33, drm_agp_info32_t)
#घोषणा DRM_IOCTL_AGP_ALLOC32		DRM_IOWR(0x34, drm_agp_buffer32_t)
#घोषणा DRM_IOCTL_AGP_FREE32		DRM_IOW( 0x35, drm_agp_buffer32_t)
#घोषणा DRM_IOCTL_AGP_BIND32		DRM_IOW( 0x36, drm_agp_binding32_t)
#घोषणा DRM_IOCTL_AGP_UNBIND32		DRM_IOW( 0x37, drm_agp_binding32_t)

#घोषणा DRM_IOCTL_SG_ALLOC32		DRM_IOW( 0x38, drm_scatter_gather32_t)
#घोषणा DRM_IOCTL_SG_FREE32		DRM_IOW( 0x39, drm_scatter_gather32_t)

#घोषणा DRM_IOCTL_UPDATE_DRAW32		DRM_IOW( 0x3f, drm_update_draw32_t)

#घोषणा DRM_IOCTL_WAIT_VBLANK32		DRM_IOWR(0x3a, drm_रुको_vblank32_t)

#घोषणा DRM_IOCTL_MODE_ADDFB232		DRM_IOWR(0xb8, drm_mode_fb_cmd232_t)

प्रकार काष्ठा drm_version_32 अणु
	पूर्णांक version_major;	  /* Major version */
	पूर्णांक version_minor;	  /* Minor version */
	पूर्णांक version_patchlevel;	   /* Patch level */
	u32 name_len;		  /* Length of name buffer */
	u32 name;		  /* Name of driver */
	u32 date_len;		  /* Length of date buffer */
	u32 date;		  /* User-space buffer to hold date */
	u32 desc_len;		  /* Length of desc buffer */
	u32 desc;		  /* User-space buffer to hold desc */
पूर्ण drm_version32_t;

अटल पूर्णांक compat_drm_version(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	drm_version32_t v32;
	काष्ठा drm_version v;
	पूर्णांक err;

	अगर (copy_from_user(&v32, (व्योम __user *)arg, माप(v32)))
		वापस -EFAULT;

	स_रखो(&v, 0, माप(v));

	v = (काष्ठा drm_version) अणु
		.name_len = v32.name_len,
		.name = compat_ptr(v32.name),
		.date_len = v32.date_len,
		.date = compat_ptr(v32.date),
		.desc_len = v32.desc_len,
		.desc = compat_ptr(v32.desc),
	पूर्ण;
	err = drm_ioctl_kernel(file, drm_version, &v,
			       DRM_RENDER_ALLOW);
	अगर (err)
		वापस err;

	v32.version_major = v.version_major;
	v32.version_minor = v.version_minor;
	v32.version_patchlevel = v.version_patchlevel;
	v32.name_len = v.name_len;
	v32.date_len = v.date_len;
	v32.desc_len = v.desc_len;
	अगर (copy_to_user((व्योम __user *)arg, &v32, माप(v32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

प्रकार काष्ठा drm_unique32 अणु
	u32 unique_len;	/* Length of unique */
	u32 unique;	/* Unique name क्रम driver instantiation */
पूर्ण drm_unique32_t;

अटल पूर्णांक compat_drm_getunique(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	drm_unique32_t uq32;
	काष्ठा drm_unique uq;
	पूर्णांक err;

	अगर (copy_from_user(&uq32, (व्योम __user *)arg, माप(uq32)))
		वापस -EFAULT;

	स_रखो(&uq, 0, माप(uq));

	uq = (काष्ठा drm_unique)अणु
		.unique_len = uq32.unique_len,
		.unique = compat_ptr(uq32.unique),
	पूर्ण;

	err = drm_ioctl_kernel(file, drm_getunique, &uq, 0);
	अगर (err)
		वापस err;

	uq32.unique_len = uq.unique_len;
	अगर (copy_to_user((व्योम __user *)arg, &uq32, माप(uq32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_drm_setunique(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	/* it's dead */
	वापस -EINVAL;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
प्रकार काष्ठा drm_map32 अणु
	u32 offset;		/* Requested physical address (0 क्रम SAREA) */
	u32 size;		/* Requested physical size (bytes) */
	क्रमागत drm_map_type type;	/* Type of memory to map */
	क्रमागत drm_map_flags flags;	/* Flags */
	u32 handle;		/* User-space: "Handle" to pass to mmap() */
	पूर्णांक mtrr;		/* MTRR slot used */
पूर्ण drm_map32_t;

अटल पूर्णांक compat_drm_geपंचांगap(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	drm_map32_t __user *argp = (व्योम __user *)arg;
	drm_map32_t m32;
	काष्ठा drm_map map;
	पूर्णांक err;

	अगर (copy_from_user(&m32, argp, माप(m32)))
		वापस -EFAULT;

	map.offset = m32.offset;
	err = drm_ioctl_kernel(file, drm_legacy_geपंचांगap_ioctl, &map, 0);
	अगर (err)
		वापस err;

	m32.offset = map.offset;
	m32.size = map.size;
	m32.type = map.type;
	m32.flags = map.flags;
	m32.handle = ptr_to_compat((व्योम __user *)map.handle);
	m32.mtrr = map.mtrr;
	अगर (copy_to_user(argp, &m32, माप(m32)))
		वापस -EFAULT;
	वापस 0;

पूर्ण

अटल पूर्णांक compat_drm_addmap(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	drm_map32_t __user *argp = (व्योम __user *)arg;
	drm_map32_t m32;
	काष्ठा drm_map map;
	पूर्णांक err;

	अगर (copy_from_user(&m32, argp, माप(m32)))
		वापस -EFAULT;

	map.offset = m32.offset;
	map.size = m32.size;
	map.type = m32.type;
	map.flags = m32.flags;

	err = drm_ioctl_kernel(file, drm_legacy_addmap_ioctl, &map,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
	अगर (err)
		वापस err;

	m32.offset = map.offset;
	m32.mtrr = map.mtrr;
	m32.handle = ptr_to_compat((व्योम __user *)map.handle);
	अगर (map.handle != compat_ptr(m32.handle))
		pr_err_ratelimited("compat_drm_addmap truncated handle %p for type %d offset %x\n",
				   map.handle, m32.type, m32.offset);

	अगर (copy_to_user(argp, &m32, माप(m32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक compat_drm_rmmap(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	drm_map32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_map map;
	u32 handle;

	अगर (get_user(handle, &argp->handle))
		वापस -EFAULT;
	map.handle = compat_ptr(handle);
	वापस drm_ioctl_kernel(file, drm_legacy_rmmap_ioctl, &map, DRM_AUTH);
पूर्ण
#पूर्ण_अगर

प्रकार काष्ठा drm_client32 अणु
	पूर्णांक idx;	/* Which client desired? */
	पूर्णांक auth;	/* Is client authenticated? */
	u32 pid;	/* Process ID */
	u32 uid;	/* User ID */
	u32 magic;	/* Magic */
	u32 iocs;	/* Ioctl count */
पूर्ण drm_client32_t;

अटल पूर्णांक compat_drm_अ_लोlient(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	drm_client32_t c32;
	drm_client32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_client client;
	पूर्णांक err;

	अगर (copy_from_user(&c32, argp, माप(c32)))
		वापस -EFAULT;

	स_रखो(&client, 0, माप(client));

	client.idx = c32.idx;

	err = drm_ioctl_kernel(file, drm_अ_लोlient, &client, 0);
	अगर (err)
		वापस err;

	c32.idx = client.idx;
	c32.auth = client.auth;
	c32.pid = client.pid;
	c32.uid = client.uid;
	c32.magic = client.magic;
	c32.iocs = client.iocs;

	अगर (copy_to_user(argp, &c32, माप(c32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

प्रकार काष्ठा drm_stats32 अणु
	u32 count;
	काष्ठा अणु
		u32 value;
		क्रमागत drm_stat_type type;
	पूर्ण data[15];
पूर्ण drm_stats32_t;

अटल पूर्णांक compat_drm_माला_लोtats(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_stats32_t __user *argp = (व्योम __user *)arg;

	/* माला_लोtats is defunct, just clear */
	अगर (clear_user(argp, माप(drm_stats32_t)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
प्रकार काष्ठा drm_buf_desc32 अणु
	पूर्णांक count;		 /* Number of buffers of this size */
	पूर्णांक size;		 /* Size in bytes */
	पूर्णांक low_mark;		 /* Low water mark */
	पूर्णांक high_mark;		 /* High water mark */
	पूर्णांक flags;
	u32 agp_start;		 /* Start address in the AGP aperture */
पूर्ण drm_buf_desc32_t;

अटल पूर्णांक compat_drm_addbufs(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	drm_buf_desc32_t __user *argp = (व्योम __user *)arg;
	drm_buf_desc32_t desc32;
	काष्ठा drm_buf_desc desc;
	पूर्णांक err;

	अगर (copy_from_user(&desc32, argp, माप(drm_buf_desc32_t)))
		वापस -EFAULT;

	desc = (काष्ठा drm_buf_desc)अणु
		desc32.count, desc32.size, desc32.low_mark, desc32.high_mark,
		desc32.flags, desc32.agp_start
	पूर्ण;

	err = drm_ioctl_kernel(file, drm_legacy_addbufs, &desc,
				   DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
	अगर (err)
		वापस err;

	desc32 = (drm_buf_desc32_t)अणु
		desc.count, desc.size, desc.low_mark, desc.high_mark,
		desc.flags, desc.agp_start
	पूर्ण;
	अगर (copy_to_user(argp, &desc32, माप(drm_buf_desc32_t)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक compat_drm_markbufs(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_buf_desc32_t b32;
	drm_buf_desc32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_buf_desc buf;

	अगर (copy_from_user(&b32, argp, माप(b32)))
		वापस -EFAULT;

	buf.size = b32.size;
	buf.low_mark = b32.low_mark;
	buf.high_mark = b32.high_mark;

	वापस drm_ioctl_kernel(file, drm_legacy_markbufs, &buf,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण

प्रकार काष्ठा drm_buf_info32 अणु
	पूर्णांक count;		/**< Entries in list */
	u32 list;
पूर्ण drm_buf_info32_t;

अटल पूर्णांक copy_one_buf32(व्योम *data, पूर्णांक count, काष्ठा drm_buf_entry *from)
अणु
	drm_buf_info32_t *request = data;
	drm_buf_desc32_t __user *to = compat_ptr(request->list);
	drm_buf_desc32_t v = अणु.count = from->buf_count,
			      .size = from->buf_size,
			      .low_mark = from->low_mark,
			      .high_mark = from->high_markपूर्ण;

	अगर (copy_to_user(to + count, &v, दुरत्व(drm_buf_desc32_t, flags)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक drm_legacy_infobufs32(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	drm_buf_info32_t *request = data;

	वापस __drm_legacy_infobufs(dev, data, &request->count, copy_one_buf32);
पूर्ण

अटल पूर्णांक compat_drm_infobufs(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_buf_info32_t req32;
	drm_buf_info32_t __user *argp = (व्योम __user *)arg;
	पूर्णांक err;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;

	अगर (req32.count < 0)
		req32.count = 0;

	err = drm_ioctl_kernel(file, drm_legacy_infobufs32, &req32, DRM_AUTH);
	अगर (err)
		वापस err;

	अगर (put_user(req32.count, &argp->count))
		वापस -EFAULT;

	वापस 0;
पूर्ण

प्रकार काष्ठा drm_buf_pub32 अणु
	पूर्णांक idx;		/**< Index पूर्णांकo the master buffer list */
	पूर्णांक total;		/**< Buffer size */
	पूर्णांक used;		/**< Amount of buffer in use (क्रम DMA) */
	u32 address;		/**< Address of buffer */
पूर्ण drm_buf_pub32_t;

प्रकार काष्ठा drm_buf_map32 अणु
	पूर्णांक count;		/**< Length of the buffer list */
	u32 भव;		/**< Mmap'd area in user-भव */
	u32 list;		/**< Buffer inक्रमmation */
पूर्ण drm_buf_map32_t;

अटल पूर्णांक map_one_buf32(व्योम *data, पूर्णांक idx, अचिन्हित दीर्घ भव,
			काष्ठा drm_buf *buf)
अणु
	drm_buf_map32_t *request = data;
	drm_buf_pub32_t __user *to = compat_ptr(request->list) + idx;
	drm_buf_pub32_t v;

	v.idx = buf->idx;
	v.total = buf->total;
	v.used = 0;
	v.address = भव + buf->offset;
	अगर (copy_to_user(to, &v, माप(v)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक drm_legacy_mapbufs32(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	drm_buf_map32_t *request = data;
	व्योम __user *v;
	पूर्णांक err = __drm_legacy_mapbufs(dev, data, &request->count,
				    &v, map_one_buf32,
				    file_priv);
	request->भव = ptr_to_compat(v);
	वापस err;
पूर्ण

अटल पूर्णांक compat_drm_mapbufs(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	drm_buf_map32_t __user *argp = (व्योम __user *)arg;
	drm_buf_map32_t req32;
	पूर्णांक err;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;
	अगर (req32.count < 0)
		वापस -EINVAL;

	err = drm_ioctl_kernel(file, drm_legacy_mapbufs32, &req32, DRM_AUTH);
	अगर (err)
		वापस err;

	अगर (put_user(req32.count, &argp->count)
	    || put_user(req32.भव, &argp->भव))
		वापस -EFAULT;

	वापस 0;
पूर्ण

प्रकार काष्ठा drm_buf_मुक्त32 अणु
	पूर्णांक count;
	u32 list;
पूर्ण drm_buf_मुक्त32_t;

अटल पूर्णांक compat_drm_मुक्तbufs(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_buf_मुक्त32_t req32;
	काष्ठा drm_buf_मुक्त request;
	drm_buf_मुक्त32_t __user *argp = (व्योम __user *)arg;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;

	request.count = req32.count;
	request.list = compat_ptr(req32.list);
	वापस drm_ioctl_kernel(file, drm_legacy_मुक्तbufs, &request, DRM_AUTH);
पूर्ण

प्रकार काष्ठा drm_ctx_priv_map32 अणु
	अचिन्हित पूर्णांक ctx_id;	 /**< Context requesting निजी mapping */
	u32 handle;		/**< Handle of map */
पूर्ण drm_ctx_priv_map32_t;

अटल पूर्णांक compat_drm_setsareactx(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	drm_ctx_priv_map32_t req32;
	काष्ठा drm_ctx_priv_map request;
	drm_ctx_priv_map32_t __user *argp = (व्योम __user *)arg;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;

	request.ctx_id = req32.ctx_id;
	request.handle = compat_ptr(req32.handle);
	वापस drm_ioctl_kernel(file, drm_legacy_setsareactx, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण

अटल पूर्णांक compat_drm_माला_लोareactx(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_ctx_priv_map req;
	drm_ctx_priv_map32_t req32;
	drm_ctx_priv_map32_t __user *argp = (व्योम __user *)arg;
	पूर्णांक err;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;

	req.ctx_id = req32.ctx_id;
	err = drm_ioctl_kernel(file, drm_legacy_माला_लोareactx, &req, DRM_AUTH);
	अगर (err)
		वापस err;

	req32.handle = ptr_to_compat((व्योम __user *)req.handle);
	अगर (copy_to_user(argp, &req32, माप(req32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

प्रकार काष्ठा drm_ctx_res32 अणु
	पूर्णांक count;
	u32 contexts;
पूर्ण drm_ctx_res32_t;

अटल पूर्णांक compat_drm_resctx(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	drm_ctx_res32_t __user *argp = (व्योम __user *)arg;
	drm_ctx_res32_t res32;
	काष्ठा drm_ctx_res res;
	पूर्णांक err;

	अगर (copy_from_user(&res32, argp, माप(res32)))
		वापस -EFAULT;

	res.count = res32.count;
	res.contexts = compat_ptr(res32.contexts);
	err = drm_ioctl_kernel(file, drm_legacy_resctx, &res, DRM_AUTH);
	अगर (err)
		वापस err;

	res32.count = res.count;
	अगर (copy_to_user(argp, &res32, माप(res32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

प्रकार काष्ठा drm_dma32 अणु
	पूर्णांक context;		  /**< Context handle */
	पूर्णांक send_count;		  /**< Number of buffers to send */
	u32 send_indices;	  /**< List of handles to buffers */
	u32 send_sizes;		  /**< Lengths of data to send */
	क्रमागत drm_dma_flags flags;		  /**< Flags */
	पूर्णांक request_count;	  /**< Number of buffers requested */
	पूर्णांक request_size;	  /**< Desired size क्रम buffers */
	u32 request_indices;	  /**< Buffer inक्रमmation */
	u32 request_sizes;
	पूर्णांक granted_count;	  /**< Number of buffers granted */
पूर्ण drm_dma32_t;

अटल पूर्णांक compat_drm_dma(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	drm_dma32_t d32;
	drm_dma32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_dma d;
	पूर्णांक err;

	अगर (copy_from_user(&d32, argp, माप(d32)))
		वापस -EFAULT;

	d.context = d32.context;
	d.send_count = d32.send_count;
	d.send_indices = compat_ptr(d32.send_indices);
	d.send_sizes = compat_ptr(d32.send_sizes);
	d.flags = d32.flags;
	d.request_count = d32.request_count;
	d.request_indices = compat_ptr(d32.request_indices);
	d.request_sizes = compat_ptr(d32.request_sizes);
	err = drm_ioctl_kernel(file, drm_legacy_dma_ioctl, &d, DRM_AUTH);
	अगर (err)
		वापस err;

	अगर (put_user(d.request_size, &argp->request_size)
	    || put_user(d.granted_count, &argp->granted_count))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_AGP)
प्रकार काष्ठा drm_agp_mode32 अणु
	u32 mode;	/**< AGP mode */
पूर्ण drm_agp_mode32_t;

अटल पूर्णांक compat_drm_agp_enable(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	drm_agp_mode32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_agp_mode mode;

	अगर (get_user(mode.mode, &argp->mode))
		वापस -EFAULT;

	वापस drm_ioctl_kernel(file,  drm_agp_enable_ioctl, &mode,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण

प्रकार काष्ठा drm_agp_info32 अणु
	पूर्णांक agp_version_major;
	पूर्णांक agp_version_minor;
	u32 mode;
	u32 aperture_base;	/* physical address */
	u32 aperture_size;	/* bytes */
	u32 memory_allowed;	/* bytes */
	u32 memory_used;

	/* PCI inक्रमmation */
	अचिन्हित लघु id_venकरोr;
	अचिन्हित लघु id_device;
पूर्ण drm_agp_info32_t;

अटल पूर्णांक compat_drm_agp_info(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_agp_info32_t __user *argp = (व्योम __user *)arg;
	drm_agp_info32_t i32;
	काष्ठा drm_agp_info info;
	पूर्णांक err;

	err = drm_ioctl_kernel(file, drm_agp_info_ioctl, &info, DRM_AUTH);
	अगर (err)
		वापस err;

	i32.agp_version_major = info.agp_version_major;
	i32.agp_version_minor = info.agp_version_minor;
	i32.mode = info.mode;
	i32.aperture_base = info.aperture_base;
	i32.aperture_size = info.aperture_size;
	i32.memory_allowed = info.memory_allowed;
	i32.memory_used = info.memory_used;
	i32.id_venकरोr = info.id_venकरोr;
	i32.id_device = info.id_device;
	अगर (copy_to_user(argp, &i32, माप(i32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

प्रकार काष्ठा drm_agp_buffer32 अणु
	u32 size;	/**< In bytes -- will round to page boundary */
	u32 handle;	/**< Used क्रम binding / unbinding */
	u32 type;	/**< Type of memory to allocate */
	u32 physical;	/**< Physical used by i810 */
पूर्ण drm_agp_buffer32_t;

अटल पूर्णांक compat_drm_agp_alloc(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	drm_agp_buffer32_t __user *argp = (व्योम __user *)arg;
	drm_agp_buffer32_t req32;
	काष्ठा drm_agp_buffer request;
	पूर्णांक err;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;

	request.size = req32.size;
	request.type = req32.type;
	err = drm_ioctl_kernel(file, drm_agp_alloc_ioctl, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
	अगर (err)
		वापस err;

	req32.handle = request.handle;
	req32.physical = request.physical;
	अगर (copy_to_user(argp, &req32, माप(req32))) अणु
		drm_ioctl_kernel(file, drm_agp_मुक्त_ioctl, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक compat_drm_agp_मुक्त(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_agp_buffer32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_agp_buffer request;

	अगर (get_user(request.handle, &argp->handle))
		वापस -EFAULT;

	वापस drm_ioctl_kernel(file, drm_agp_मुक्त_ioctl, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण

प्रकार काष्ठा drm_agp_binding32 अणु
	u32 handle;	/**< From drm_agp_buffer */
	u32 offset;	/**< In bytes -- will round to page boundary */
पूर्ण drm_agp_binding32_t;

अटल पूर्णांक compat_drm_agp_bind(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_agp_binding32_t __user *argp = (व्योम __user *)arg;
	drm_agp_binding32_t req32;
	काष्ठा drm_agp_binding request;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;

	request.handle = req32.handle;
	request.offset = req32.offset;
	वापस drm_ioctl_kernel(file, drm_agp_bind_ioctl, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण

अटल पूर्णांक compat_drm_agp_unbind(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	drm_agp_binding32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_agp_binding request;

	अगर (get_user(request.handle, &argp->handle))
		वापस -EFAULT;

	वापस drm_ioctl_kernel(file, drm_agp_unbind_ioctl, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण
#पूर्ण_अगर /* CONFIG_AGP */

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
प्रकार काष्ठा drm_scatter_gather32 अणु
	u32 size;	/**< In bytes -- will round to page boundary */
	u32 handle;	/**< Used क्रम mapping / unmapping */
पूर्ण drm_scatter_gather32_t;

अटल पूर्णांक compat_drm_sg_alloc(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_scatter_gather32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_scatter_gather request;
	पूर्णांक err;

	अगर (get_user(request.size, &argp->size))
		वापस -EFAULT;

	err = drm_ioctl_kernel(file, drm_legacy_sg_alloc, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
	अगर (err)
		वापस err;

	/* XXX not sure about the handle conversion here... */
	अगर (put_user(request.handle >> PAGE_SHIFT, &argp->handle))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक compat_drm_sg_मुक्त(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	drm_scatter_gather32_t __user *argp = (व्योम __user *)arg;
	काष्ठा drm_scatter_gather request;
	अचिन्हित दीर्घ x;

	अगर (get_user(x, &argp->handle))
		वापस -EFAULT;
	request.handle = x << PAGE_SHIFT;
	वापस drm_ioctl_kernel(file, drm_legacy_sg_मुक्त, &request,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_X86)
प्रकार काष्ठा drm_update_draw32 अणु
	drm_drawable_t handle;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक num;
	/* 64-bit version has a 32-bit pad here */
	u64 data;	/**< Poपूर्णांकer */
पूर्ण __attribute__((packed)) drm_update_draw32_t;

अटल पूर्णांक compat_drm_update_draw(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	/* update_draw is defunct */
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा drm_रुको_vblank_request32 अणु
	क्रमागत drm_vblank_seq_type type;
	अचिन्हित पूर्णांक sequence;
	u32 संकेत;
पूर्ण;

काष्ठा drm_रुको_vblank_reply32 अणु
	क्रमागत drm_vblank_seq_type type;
	अचिन्हित पूर्णांक sequence;
	s32 tval_sec;
	s32 tval_usec;
पूर्ण;

प्रकार जोड़ drm_रुको_vblank32 अणु
	काष्ठा drm_रुको_vblank_request32 request;
	काष्ठा drm_रुको_vblank_reply32 reply;
पूर्ण drm_रुको_vblank32_t;

अटल पूर्णांक compat_drm_रुको_vblank(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	drm_रुको_vblank32_t __user *argp = (व्योम __user *)arg;
	drm_रुको_vblank32_t req32;
	जोड़ drm_रुको_vblank req;
	पूर्णांक err;

	अगर (copy_from_user(&req32, argp, माप(req32)))
		वापस -EFAULT;

	स_रखो(&req, 0, माप(req));

	req.request.type = req32.request.type;
	req.request.sequence = req32.request.sequence;
	req.request.संकेत = req32.request.संकेत;
	err = drm_ioctl_kernel(file, drm_रुको_vblank_ioctl, &req, DRM_UNLOCKED);
	अगर (err)
		वापस err;

	req32.reply.type = req.reply.type;
	req32.reply.sequence = req.reply.sequence;
	req32.reply.tval_sec = req.reply.tval_sec;
	req32.reply.tval_usec = req.reply.tval_usec;
	अगर (copy_to_user(argp, &req32, माप(req32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_X86)
प्रकार काष्ठा drm_mode_fb_cmd232 अणु
	u32 fb_id;
	u32 width;
	u32 height;
	u32 pixel_क्रमmat;
	u32 flags;
	u32 handles[4];
	u32 pitches[4];
	u32 offsets[4];
	u64 modअगरier[4];
पूर्ण __attribute__((packed)) drm_mode_fb_cmd232_t;

अटल पूर्णांक compat_drm_mode_addfb2(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_mode_fb_cmd232 __user *argp = (व्योम __user *)arg;
	काष्ठा drm_mode_fb_cmd2 req64;
	पूर्णांक err;

	स_रखो(&req64, 0, माप(req64));

	अगर (copy_from_user(&req64, argp,
			   दुरत्व(drm_mode_fb_cmd232_t, modअगरier)))
		वापस -EFAULT;

	अगर (copy_from_user(&req64.modअगरier, &argp->modअगरier,
			   माप(req64.modअगरier)))
		वापस -EFAULT;

	err = drm_ioctl_kernel(file, drm_mode_addfb2, &req64, 0);
	अगर (err)
		वापस err;

	अगर (put_user(req64.fb_id, &argp->fb_id))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा अणु
	drm_ioctl_compat_t *fn;
	अक्षर *name;
पूर्ण drm_compat_ioctls[] = अणु
#घोषणा DRM_IOCTL32_DEF(n, f) [DRM_IOCTL_NR(n##32)] = अणु.fn = f, .name = #nपूर्ण
	DRM_IOCTL32_DEF(DRM_IOCTL_VERSION, compat_drm_version),
	DRM_IOCTL32_DEF(DRM_IOCTL_GET_UNIQUE, compat_drm_getunique),
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
	DRM_IOCTL32_DEF(DRM_IOCTL_GET_MAP, compat_drm_geपंचांगap),
#पूर्ण_अगर
	DRM_IOCTL32_DEF(DRM_IOCTL_GET_CLIENT, compat_drm_अ_लोlient),
	DRM_IOCTL32_DEF(DRM_IOCTL_GET_STATS, compat_drm_माला_लोtats),
	DRM_IOCTL32_DEF(DRM_IOCTL_SET_UNIQUE, compat_drm_setunique),
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
	DRM_IOCTL32_DEF(DRM_IOCTL_ADD_MAP, compat_drm_addmap),
	DRM_IOCTL32_DEF(DRM_IOCTL_ADD_BUFS, compat_drm_addbufs),
	DRM_IOCTL32_DEF(DRM_IOCTL_MARK_BUFS, compat_drm_markbufs),
	DRM_IOCTL32_DEF(DRM_IOCTL_INFO_BUFS, compat_drm_infobufs),
	DRM_IOCTL32_DEF(DRM_IOCTL_MAP_BUFS, compat_drm_mapbufs),
	DRM_IOCTL32_DEF(DRM_IOCTL_FREE_BUFS, compat_drm_मुक्तbufs),
	DRM_IOCTL32_DEF(DRM_IOCTL_RM_MAP, compat_drm_rmmap),
	DRM_IOCTL32_DEF(DRM_IOCTL_SET_SAREA_CTX, compat_drm_setsareactx),
	DRM_IOCTL32_DEF(DRM_IOCTL_GET_SAREA_CTX, compat_drm_माला_लोareactx),
	DRM_IOCTL32_DEF(DRM_IOCTL_RES_CTX, compat_drm_resctx),
	DRM_IOCTL32_DEF(DRM_IOCTL_DMA, compat_drm_dma),
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_AGP)
	DRM_IOCTL32_DEF(DRM_IOCTL_AGP_ENABLE, compat_drm_agp_enable),
	DRM_IOCTL32_DEF(DRM_IOCTL_AGP_INFO, compat_drm_agp_info),
	DRM_IOCTL32_DEF(DRM_IOCTL_AGP_ALLOC, compat_drm_agp_alloc),
	DRM_IOCTL32_DEF(DRM_IOCTL_AGP_FREE, compat_drm_agp_मुक्त),
	DRM_IOCTL32_DEF(DRM_IOCTL_AGP_BIND, compat_drm_agp_bind),
	DRM_IOCTL32_DEF(DRM_IOCTL_AGP_UNBIND, compat_drm_agp_unbind),
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
	DRM_IOCTL32_DEF(DRM_IOCTL_SG_ALLOC, compat_drm_sg_alloc),
	DRM_IOCTL32_DEF(DRM_IOCTL_SG_FREE, compat_drm_sg_मुक्त),
#पूर्ण_अगर
#अगर defined(CONFIG_X86) || defined(CONFIG_IA64)
	DRM_IOCTL32_DEF(DRM_IOCTL_UPDATE_DRAW, compat_drm_update_draw),
#पूर्ण_अगर
	DRM_IOCTL32_DEF(DRM_IOCTL_WAIT_VBLANK, compat_drm_रुको_vblank),
#अगर defined(CONFIG_X86) || defined(CONFIG_IA64)
	DRM_IOCTL32_DEF(DRM_IOCTL_MODE_ADDFB2, compat_drm_mode_addfb2),
#पूर्ण_अगर
पूर्ण;

/**
 * drm_compat_ioctl - 32bit IOCTL compatibility handler क्रम DRM drivers
 * @filp: file this ioctl is called on
 * @cmd: ioctl cmd number
 * @arg: user argument
 *
 * Compatibility handler क्रम 32 bit userspace running on 64 kernels. All actual
 * IOCTL handling is क्रमwarded to drm_ioctl(), जबतक marshalling काष्ठाures as
 * appropriate. Note that this only handles DRM core IOCTLs, अगर the driver has
 * botched IOCTL itself, it must handle those by wrapping this function.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
दीर्घ drm_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	काष्ठा drm_file *file_priv = filp->निजी_data;
	drm_ioctl_compat_t *fn;
	पूर्णांक ret;

	/* Assume that ioctls without an explicit compat routine will just
	 * work.  This may not always be a good assumption, but it's better
	 * than always failing.
	 */
	अगर (nr >= ARRAY_SIZE(drm_compat_ioctls))
		वापस drm_ioctl(filp, cmd, arg);

	fn = drm_compat_ioctls[nr].fn;
	अगर (!fn)
		वापस drm_ioctl(filp, cmd, arg);

	DRM_DEBUG("comm=\"%s\", pid=%d, dev=0x%lx, auth=%d, %s\n",
		  current->comm, task_pid_nr(current),
		  (दीर्घ)old_encode_dev(file_priv->minor->kdev->devt),
		  file_priv->authenticated,
		  drm_compat_ioctls[nr].name);
	ret = (*fn)(filp, cmd, arg);
	अगर (ret)
		DRM_DEBUG("ret = %d\n", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_compat_ioctl);
