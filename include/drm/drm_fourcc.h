<शैली गुरु>
/*
 * Copyright (c) 2016 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */
#अगर_अघोषित __DRM_FOURCC_H__
#घोषणा __DRM_FOURCC_H__

#समावेश <linux/types.h>
#समावेश <uapi/drm/drm_fourcc.h>

/*
 * DRM क्रमmats are little endian.  Define host endian variants क्रम the
 * most common क्रमmats here, to reduce the #अगर_घोषितs needed in drivers.
 *
 * Note that the DRM_FORMAT_BIG_ENDIAN flag should only be used in
 * हाल the क्रमmat can't be specified otherwise, so we don't end up
 * with two values describing the same क्रमmat.
 */
#अगर_घोषित __BIG_ENDIAN
# define DRM_FORMAT_HOST_XRGB1555     (DRM_FORMAT_XRGB1555         |	\
				       DRM_FORMAT_BIG_ENDIAN)
# define DRM_FORMAT_HOST_RGB565       (DRM_FORMAT_RGB565           |	\
				       DRM_FORMAT_BIG_ENDIAN)
# define DRM_FORMAT_HOST_XRGB8888     DRM_FORMAT_BGRX8888
# define DRM_FORMAT_HOST_ARGB8888     DRM_FORMAT_BGRA8888
#अन्यथा
# define DRM_FORMAT_HOST_XRGB1555     DRM_FORMAT_XRGB1555
# define DRM_FORMAT_HOST_RGB565       DRM_FORMAT_RGB565
# define DRM_FORMAT_HOST_XRGB8888     DRM_FORMAT_XRGB8888
# define DRM_FORMAT_HOST_ARGB8888     DRM_FORMAT_ARGB8888
#पूर्ण_अगर

काष्ठा drm_device;
काष्ठा drm_mode_fb_cmd2;

/**
 * काष्ठा drm_क्रमmat_info - inक्रमmation about a DRM क्रमmat
 */
काष्ठा drm_क्रमmat_info अणु
	/** @क्रमmat: 4CC क्रमmat identअगरier (DRM_FORMAT_*) */
	u32 क्रमmat;

	/**
	 * @depth:
	 *
	 * Color depth (number of bits per pixel excluding padding bits),
	 * valid क्रम a subset of RGB क्रमmats only. This is a legacy field, करो
	 * not use in new code and set to 0 क्रम new क्रमmats.
	 */
	u8 depth;

	/** @num_planes: Number of color planes (1 to 3) */
	u8 num_planes;

	जोड़ अणु
		/**
		 * @cpp:
		 *
		 * Number of bytes per pixel (per plane), this is aliased with
		 * @अक्षर_per_block. It is deprecated in favour of using the
		 * triplet @अक्षर_per_block, @block_w, @block_h क्रम better
		 * describing the pixel क्रमmat.
		 */
		u8 cpp[4];

		/**
		 * @अक्षर_per_block:
		 *
		 * Number of bytes per block (per plane), where blocks are
		 * defined as a rectangle of pixels which are stored next to
		 * each other in a byte aligned memory region. Together with
		 * @block_w and @block_h this is used to properly describe tiles
		 * in tiled क्रमmats or to describe groups of pixels in packed
		 * क्रमmats क्रम which the memory needed क्रम a single pixel is not
		 * byte aligned.
		 *
		 * @cpp has been kept क्रम historical reasons because there are
		 * a lot of places in drivers where it's used. In drm core क्रम
		 * generic code paths the preferred way is to use
		 * @अक्षर_per_block, drm_क्रमmat_info_block_width() and
		 * drm_क्रमmat_info_block_height() which allows handling both
		 * block and non-block क्रमmats in the same way.
		 *
		 * For क्रमmats that are पूर्णांकended to be used only with non-linear
		 * modअगरiers both @cpp and @अक्षर_per_block must be 0 in the
		 * generic क्रमmat table. Drivers could supply accurate
		 * inक्रमmation from their drm_mode_config.get_क्रमmat_info hook
		 * अगर they want the core to be validating the pitch.
		 */
		u8 अक्षर_per_block[4];
	पूर्ण;

	/**
	 * @block_w:
	 *
	 * Block width in pixels, this is पूर्णांकended to be accessed through
	 * drm_क्रमmat_info_block_width()
	 */
	u8 block_w[4];

	/**
	 * @block_h:
	 *
	 * Block height in pixels, this is पूर्णांकended to be accessed through
	 * drm_क्रमmat_info_block_height()
	 */
	u8 block_h[4];

	/** @hsub: Horizontal chroma subsampling factor */
	u8 hsub;
	/** @vsub: Vertical chroma subsampling factor */
	u8 vsub;

	/** @has_alpha: Does the क्रमmat embeds an alpha component? */
	bool has_alpha;

	/** @is_yuv: Is it a YUV क्रमmat? */
	bool is_yuv;
पूर्ण;

/**
 * काष्ठा drm_क्रमmat_name_buf - name of a DRM क्रमmat
 * @str: string buffer containing the क्रमmat name
 */
काष्ठा drm_क्रमmat_name_buf अणु
	अक्षर str[32];
पूर्ण;

/**
 * drm_क्रमmat_info_is_yuv_packed - check that the क्रमmat info matches a YUV
 * क्रमmat with data laid in a single plane
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a packed YUV क्रमmat.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_packed(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->num_planes == 1;
पूर्ण

/**
 * drm_क्रमmat_info_is_yuv_semiplanar - check that the क्रमmat info matches a YUV
 * क्रमmat with data laid in two planes (luminance and chrominance)
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a semiplanar YUV क्रमmat.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_semiplanar(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->num_planes == 2;
पूर्ण

/**
 * drm_क्रमmat_info_is_yuv_planar - check that the क्रमmat info matches a YUV
 * क्रमmat with data laid in three planes (one क्रम each YUV component)
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a planar YUV क्रमmat.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_planar(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->num_planes == 3;
पूर्ण

/**
 * drm_क्रमmat_info_is_yuv_sampling_410 - check that the क्रमmat info matches a
 * YUV क्रमmat with 4:1:0 sub-sampling
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a YUV क्रमmat with 4:1:0
 * sub-sampling.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_sampling_410(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->hsub == 4 && info->vsub == 4;
पूर्ण

/**
 * drm_क्रमmat_info_is_yuv_sampling_411 - check that the क्रमmat info matches a
 * YUV क्रमmat with 4:1:1 sub-sampling
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a YUV क्रमmat with 4:1:1
 * sub-sampling.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_sampling_411(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->hsub == 4 && info->vsub == 1;
पूर्ण

/**
 * drm_क्रमmat_info_is_yuv_sampling_420 - check that the क्रमmat info matches a
 * YUV क्रमmat with 4:2:0 sub-sampling
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a YUV क्रमmat with 4:2:0
 * sub-sampling.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_sampling_420(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->hsub == 2 && info->vsub == 2;
पूर्ण

/**
 * drm_क्रमmat_info_is_yuv_sampling_422 - check that the क्रमmat info matches a
 * YUV क्रमmat with 4:2:2 sub-sampling
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a YUV क्रमmat with 4:2:2
 * sub-sampling.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_sampling_422(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->hsub == 2 && info->vsub == 1;
पूर्ण

/**
 * drm_क्रमmat_info_is_yuv_sampling_444 - check that the क्रमmat info matches a
 * YUV क्रमmat with 4:4:4 sub-sampling
 * @info: क्रमmat info
 *
 * Returns:
 * A boolean indicating whether the क्रमmat info matches a YUV क्रमmat with 4:4:4
 * sub-sampling.
 */
अटल अंतरभूत bool
drm_क्रमmat_info_is_yuv_sampling_444(स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	वापस info->is_yuv && info->hsub == 1 && info->vsub == 1;
पूर्ण

/**
 * drm_क्रमmat_info_plane_width - width of the plane given the first plane
 * @info: pixel क्रमmat info
 * @width: width of the first plane
 * @plane: plane index
 *
 * Returns:
 * The width of @plane, given that the width of the first plane is @width.
 */
अटल अंतरभूत
पूर्णांक drm_क्रमmat_info_plane_width(स्थिर काष्ठा drm_क्रमmat_info *info, पूर्णांक width,
				पूर्णांक plane)
अणु
	अगर (!info || plane >= info->num_planes)
		वापस 0;

	अगर (plane == 0)
		वापस width;

	वापस width / info->hsub;
पूर्ण

/**
 * drm_क्रमmat_info_plane_height - height of the plane given the first plane
 * @info: pixel क्रमmat info
 * @height: height of the first plane
 * @plane: plane index
 *
 * Returns:
 * The height of @plane, given that the height of the first plane is @height.
 */
अटल अंतरभूत
पूर्णांक drm_क्रमmat_info_plane_height(स्थिर काष्ठा drm_क्रमmat_info *info, पूर्णांक height,
				 पूर्णांक plane)
अणु
	अगर (!info || plane >= info->num_planes)
		वापस 0;

	अगर (plane == 0)
		वापस height;

	वापस height / info->vsub;
पूर्ण

स्थिर काष्ठा drm_क्रमmat_info *__drm_क्रमmat_info(u32 क्रमmat);
स्थिर काष्ठा drm_क्रमmat_info *drm_क्रमmat_info(u32 क्रमmat);
स्थिर काष्ठा drm_क्रमmat_info *
drm_get_क्रमmat_info(काष्ठा drm_device *dev,
		    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);
uपूर्णांक32_t drm_mode_legacy_fb_क्रमmat(uपूर्णांक32_t bpp, uपूर्णांक32_t depth);
uपूर्णांक32_t drm_driver_legacy_fb_क्रमmat(काष्ठा drm_device *dev,
				     uपूर्णांक32_t bpp, uपूर्णांक32_t depth);
अचिन्हित पूर्णांक drm_क्रमmat_info_block_width(स्थिर काष्ठा drm_क्रमmat_info *info,
					 पूर्णांक plane);
अचिन्हित पूर्णांक drm_क्रमmat_info_block_height(स्थिर काष्ठा drm_क्रमmat_info *info,
					  पूर्णांक plane);
uपूर्णांक64_t drm_क्रमmat_info_min_pitch(स्थिर काष्ठा drm_क्रमmat_info *info,
				   पूर्णांक plane, अचिन्हित पूर्णांक buffer_width);
स्थिर अक्षर *drm_get_क्रमmat_name(uपूर्णांक32_t क्रमmat, काष्ठा drm_क्रमmat_name_buf *buf);

#पूर्ण_अगर /* __DRM_FOURCC_H__ */
