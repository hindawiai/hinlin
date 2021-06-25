<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    v4l2 common पूर्णांकernal API header

    This header contains पूर्णांकernal shared ioctl definitions क्रम use by the
    पूर्णांकernal low-level v4l2 drivers.
    Each ioctl begins with VIDIOC_INT_ to clearly mark that it is an पूर्णांकernal
    define,

    Copyright (C) 2005  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित V4L2_COMMON_H_
#घोषणा V4L2_COMMON_H_

#समावेश <linux/समय.स>
#समावेश <media/v4l2-dev.h>

/* Common prपूर्णांकk स्थिरructs क्रम v4l-i2c drivers. These macros create a unique
   prefix consisting of the driver name, the adapter number and the i2c
   address. */
#घोषणा v4l_prपूर्णांकk(level, name, adapter, addr, fmt, arg...) \
	prपूर्णांकk(level "%s %d-%04x: " fmt, name, i2c_adapter_id(adapter), addr , ## arg)

#घोषणा v4l_client_prपूर्णांकk(level, client, fmt, arg...)			    \
	v4l_prपूर्णांकk(level, (client)->dev.driver->name, (client)->adapter, \
		   (client)->addr, fmt , ## arg)

#घोषणा v4l_err(client, fmt, arg...) \
	v4l_client_prपूर्णांकk(KERN_ERR, client, fmt , ## arg)

#घोषणा v4l_warn(client, fmt, arg...) \
	v4l_client_prपूर्णांकk(KERN_WARNING, client, fmt , ## arg)

#घोषणा v4l_info(client, fmt, arg...) \
	v4l_client_prपूर्णांकk(KERN_INFO, client, fmt , ## arg)

/* These three macros assume that the debug level is set with a module
   parameter called 'debug'. */
#घोषणा v4l_dbg(level, debug, client, fmt, arg...)			     \
	करो अणु								     \
		अगर (debug >= (level))					     \
			v4l_client_prपूर्णांकk(KERN_DEBUG, client, fmt , ## arg); \
	पूर्ण जबतक (0)

/* Add a version of v4l_dbg to be used on drivers using dev_foo() macros */
#घोषणा dev_dbg_lvl(__dev, __level, __debug, __fmt, __arg...)		\
	करो अणु								\
		अगर (__debug >= (__level))				\
			dev_prपूर्णांकk(KERN_DEBUG, __dev, __fmt, ##__arg);	\
	पूर्ण जबतक (0)

/* ------------------------------------------------------------------------- */

/* These prपूर्णांकk स्थिरructs can be used with v4l2_device and v4l2_subdev */
#घोषणा v4l2_prपूर्णांकk(level, dev, fmt, arg...) \
	prपूर्णांकk(level "%s: " fmt, (dev)->name , ## arg)

#घोषणा v4l2_err(dev, fmt, arg...) \
	v4l2_prपूर्णांकk(KERN_ERR, dev, fmt , ## arg)

#घोषणा v4l2_warn(dev, fmt, arg...) \
	v4l2_prपूर्णांकk(KERN_WARNING, dev, fmt , ## arg)

#घोषणा v4l2_info(dev, fmt, arg...) \
	v4l2_prपूर्णांकk(KERN_INFO, dev, fmt , ## arg)

/* These three macros assume that the debug level is set with a module
   parameter called 'debug'. */
#घोषणा v4l2_dbg(level, debug, dev, fmt, arg...)			\
	करो अणु								\
		अगर (debug >= (level))					\
			v4l2_prपूर्णांकk(KERN_DEBUG, dev, fmt , ## arg);	\
	पूर्ण जबतक (0)

/**
 * v4l2_ctrl_query_fill- Fill in a काष्ठा v4l2_queryctrl
 *
 * @qctrl: poपूर्णांकer to the &काष्ठा v4l2_queryctrl to be filled
 * @min: minimum value क्रम the control
 * @max: maximum value क्रम the control
 * @step: control step
 * @def: शेष value क्रम the control
 *
 * Fills the &काष्ठा v4l2_queryctrl fields क्रम the query control.
 *
 * .. note::
 *
 *    This function assumes that the @qctrl->id field is filled.
 *
 * Returns -EINVAL अगर the control is not known by the V4L2 core, 0 on success.
 */

पूर्णांक v4l2_ctrl_query_fill(काष्ठा v4l2_queryctrl *qctrl,
			 s32 min, s32 max, s32 step, s32 def);

/* ------------------------------------------------------------------------- */

काष्ठा v4l2_device;
काष्ठा v4l2_subdev;
काष्ठा v4l2_subdev_ops;

/* I2C Helper functions */
#समावेश <linux/i2c.h>

/**
 * क्रमागत v4l2_i2c_tuner_type - specअगरies the range of tuner address that
 *	should be used when seeking क्रम I2C devices.
 *
 * @ADDRS_RADIO:		Radio tuner addresses.
 *				Represent the following I2C addresses:
 *				0x10 (अगर compiled with tea5761 support)
 *				and 0x60.
 * @ADDRS_DEMOD:		Demod tuner addresses.
 *				Represent the following I2C addresses:
 *				0x42, 0x43, 0x4a and 0x4b.
 * @ADDRS_TV:			TV tuner addresses.
 *				Represent the following I2C addresses:
 *				0x42, 0x43, 0x4a, 0x4b, 0x60, 0x61, 0x62,
 *				0x63 and 0x64.
 * @ADDRS_TV_WITH_DEMOD:	TV tuner addresses अगर demod is present, this
 *				excludes addresses used by the demodulator
 *				from the list of candidates.
 *				Represent the following I2C addresses:
 *				0x60, 0x61, 0x62, 0x63 and 0x64.
 *
 * NOTE: All I2C addresses above use the 7-bit notation.
 */
क्रमागत v4l2_i2c_tuner_type अणु
	ADDRS_RADIO,
	ADDRS_DEMOD,
	ADDRS_TV,
	ADDRS_TV_WITH_DEMOD,
पूर्ण;

#अगर defined(CONFIG_VIDEO_V4L2_I2C)

/**
 * v4l2_i2c_new_subdev - Load an i2c module and वापस an initialized
 *	&काष्ठा v4l2_subdev.
 *
 * @v4l2_dev: poपूर्णांकer to &काष्ठा v4l2_device
 * @adapter: poपूर्णांकer to काष्ठा i2c_adapter
 * @client_type:  name of the chip that's on the adapter.
 * @addr: I2C address. If zero, it will use @probe_addrs
 * @probe_addrs: array with a list of address. The last entry at such
 *	array should be %I2C_CLIENT_END.
 *
 * वापसs a &काष्ठा v4l2_subdev poपूर्णांकer.
 */
काष्ठा v4l2_subdev *v4l2_i2c_new_subdev(काष्ठा v4l2_device *v4l2_dev,
		काष्ठा i2c_adapter *adapter, स्थिर अक्षर *client_type,
		u8 addr, स्थिर अचिन्हित लघु *probe_addrs);

/**
 * v4l2_i2c_new_subdev_board - Load an i2c module and वापस an initialized
 *	&काष्ठा v4l2_subdev.
 *
 * @v4l2_dev: poपूर्णांकer to &काष्ठा v4l2_device
 * @adapter: poपूर्णांकer to काष्ठा i2c_adapter
 * @info: poपूर्णांकer to काष्ठा i2c_board_info used to replace the irq,
 *	 platक्रमm_data and addr arguments.
 * @probe_addrs: array with a list of address. The last entry at such
 *	array should be %I2C_CLIENT_END.
 *
 * वापसs a &काष्ठा v4l2_subdev poपूर्णांकer.
 */
काष्ठा v4l2_subdev *v4l2_i2c_new_subdev_board(काष्ठा v4l2_device *v4l2_dev,
		काष्ठा i2c_adapter *adapter, काष्ठा i2c_board_info *info,
		स्थिर अचिन्हित लघु *probe_addrs);

/**
 * v4l2_i2c_subdev_set_name - Set name क्रम an IतऑC sub-device
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @client: poपूर्णांकer to काष्ठा i2c_client
 * @devname: the name of the device; अगर शून्य, the IतऑC device's name will be used
 * @postfix: sub-device specअगरic string to put right after the IतऑC device name;
 *	     may be शून्य
 */
व्योम v4l2_i2c_subdev_set_name(काष्ठा v4l2_subdev *sd, काष्ठा i2c_client *client,
			      स्थिर अक्षर *devname, स्थिर अक्षर *postfix);

/**
 * v4l2_i2c_subdev_init - Initializes a &काष्ठा v4l2_subdev with data from
 *	an i2c_client काष्ठा.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @client: poपूर्णांकer to काष्ठा i2c_client
 * @ops: poपूर्णांकer to &काष्ठा v4l2_subdev_ops
 */
व्योम v4l2_i2c_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा i2c_client *client,
		स्थिर काष्ठा v4l2_subdev_ops *ops);

/**
 * v4l2_i2c_subdev_addr - वापसs i2c client address of &काष्ठा v4l2_subdev.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 *
 * Returns the address of an I2C sub-device
 */
अचिन्हित लघु v4l2_i2c_subdev_addr(काष्ठा v4l2_subdev *sd);

/**
 * v4l2_i2c_tuner_addrs - Return a list of I2C tuner addresses to probe.
 *
 * @type: type of the tuner to seek, as defined by
 *	  &क्रमागत v4l2_i2c_tuner_type.
 *
 * NOTE: Use only अगर the tuner addresses are unknown.
 */
स्थिर अचिन्हित लघु *v4l2_i2c_tuner_addrs(क्रमागत v4l2_i2c_tuner_type type);

/**
 * v4l2_i2c_subdev_unरेजिस्टर - Unरेजिस्टर a v4l2_subdev
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 */
व्योम v4l2_i2c_subdev_unरेजिस्टर(काष्ठा v4l2_subdev *sd);

#अन्यथा

अटल अंतरभूत काष्ठा v4l2_subdev *
v4l2_i2c_new_subdev(काष्ठा v4l2_device *v4l2_dev,
		    काष्ठा i2c_adapter *adapter, स्थिर अक्षर *client_type,
		    u8 addr, स्थिर अचिन्हित लघु *probe_addrs)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *
v4l2_i2c_new_subdev_board(काष्ठा v4l2_device *v4l2_dev,
			  काष्ठा i2c_adapter *adapter, काष्ठा i2c_board_info *info,
			  स्थिर अचिन्हित लघु *probe_addrs)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
v4l2_i2c_subdev_set_name(काष्ठा v4l2_subdev *sd, काष्ठा i2c_client *client,
			 स्थिर अक्षर *devname, स्थिर अक्षर *postfix)
अणुपूर्ण

अटल अंतरभूत व्योम
v4l2_i2c_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा i2c_client *client,
		     स्थिर काष्ठा v4l2_subdev_ops *ops)
अणुपूर्ण

अटल अंतरभूत अचिन्हित लघु v4l2_i2c_subdev_addr(काष्ठा v4l2_subdev *sd)
अणु
	वापस I2C_CLIENT_END;
पूर्ण

अटल अंतरभूत स्थिर अचिन्हित लघु *
v4l2_i2c_tuner_addrs(क्रमागत v4l2_i2c_tuner_type type)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम v4l2_i2c_subdev_unरेजिस्टर(काष्ठा v4l2_subdev *sd)
अणुपूर्ण

#पूर्ण_अगर

/* ------------------------------------------------------------------------- */

/* SPI Helper functions */

#समावेश <linux/spi/spi.h>

#अगर defined(CONFIG_SPI)

/**
 *  v4l2_spi_new_subdev - Load an spi module and वापस an initialized
 *	&काष्ठा v4l2_subdev.
 *
 *
 * @v4l2_dev: poपूर्णांकer to &काष्ठा v4l2_device.
 * @master: poपूर्णांकer to काष्ठा spi_master.
 * @info: poपूर्णांकer to काष्ठा spi_board_info.
 *
 * वापसs a &काष्ठा v4l2_subdev poपूर्णांकer.
 */
काष्ठा v4l2_subdev *v4l2_spi_new_subdev(काष्ठा v4l2_device *v4l2_dev,
		काष्ठा spi_master *master, काष्ठा spi_board_info *info);

/**
 * v4l2_spi_subdev_init - Initialize a v4l2_subdev with data from an
 *	spi_device काष्ठा.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @spi: poपूर्णांकer to काष्ठा spi_device.
 * @ops: poपूर्णांकer to &काष्ठा v4l2_subdev_ops
 */
व्योम v4l2_spi_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा spi_device *spi,
		स्थिर काष्ठा v4l2_subdev_ops *ops);

/**
 * v4l2_spi_subdev_unरेजिस्टर - Unरेजिस्टर a v4l2_subdev
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 */
व्योम v4l2_spi_subdev_unरेजिस्टर(काष्ठा v4l2_subdev *sd);

#अन्यथा

अटल अंतरभूत काष्ठा v4l2_subdev *
v4l2_spi_new_subdev(काष्ठा v4l2_device *v4l2_dev,
		    काष्ठा spi_master *master, काष्ठा spi_board_info *info)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
v4l2_spi_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा spi_device *spi,
		     स्थिर काष्ठा v4l2_subdev_ops *ops)
अणुपूर्ण

अटल अंतरभूत व्योम v4l2_spi_subdev_unरेजिस्टर(काष्ठा v4l2_subdev *sd)
अणुपूर्ण
#पूर्ण_अगर

/* ------------------------------------------------------------------------- */

/*
 * FIXME: these reमुख्यing ioctls/काष्ठाs should be हटाओd as well, but they
 * are still used in tuner-simple.c (TUNER_SET_CONFIG) and cx18/ivtv (RESET).
 * To हटाओ these ioctls some more cleanup is needed in those modules.
 *
 * It करोesn't make much sense on करोcumenting them, as what we really want is
 * to get rid of them.
 */

/* s_config */
काष्ठा v4l2_priv_tun_config अणु
	पूर्णांक tuner;
	व्योम *priv;
पूर्ण;
#घोषणा TUNER_SET_CONFIG           _IOW('d', 92, काष्ठा v4l2_priv_tun_config)

#घोषणा VIDIOC_INT_RESET		_IOW ('d', 102, u32)

/* ------------------------------------------------------------------------- */

/* Miscellaneous helper functions */

/**
 * v4l_bound_align_image - adjust video dimensions according to
 *	a given स्थिरraपूर्णांकs.
 *
 * @width:	poपूर्णांकer to width that will be adjusted अगर needed.
 * @wmin:	minimum width.
 * @wmax:	maximum width.
 * @walign:	least signअगरicant bit on width.
 * @height:	poपूर्णांकer to height that will be adjusted अगर needed.
 * @hmin:	minimum height.
 * @hmax:	maximum height.
 * @halign:	least signअगरicant bit on height.
 * @salign:	least signअगरicant bit क्रम the image size (e. g.
 *		:math:`width * height`).
 *
 * Clip an image to have @width between @wmin and @wmax, and @height between
 * @hmin and @hmax, inclusive.
 *
 * Additionally, the @width will be a multiple of :math:`2^अणुwalignपूर्ण`,
 * the @height will be a multiple of :math:`2^अणुhalignपूर्ण`, and the overall
 * size :math:`width * height` will be a multiple of :math:`2^अणुsalignपूर्ण`.
 *
 * .. note::
 *
 *    #. The clipping rectangle may be shrunk or enlarged to fit the alignment
 *       स्थिरraपूर्णांकs.
 *    #. @wmax must not be smaller than @wmin.
 *    #. @hmax must not be smaller than @hmin.
 *    #. The alignments must not be so high there are no possible image
 *       sizes within the allowed bounds.
 *    #. @wmin and @hmin must be at least 1 (करोn't use 0).
 *    #. For @walign, @halign and @salign, अगर you करोn't care about a certain
 *       alignment, specअगरy ``0``, as :math:`2^0 = 1` and one byte alignment
 *       is equivalent to no alignment.
 *    #. If you only want to adjust करोwnward, specअगरy a maximum that's the
 *       same as the initial value.
 */
व्योम v4l_bound_align_image(अचिन्हित पूर्णांक *width, अचिन्हित पूर्णांक wmin,
			   अचिन्हित पूर्णांक wmax, अचिन्हित पूर्णांक walign,
			   अचिन्हित पूर्णांक *height, अचिन्हित पूर्णांक hmin,
			   अचिन्हित पूर्णांक hmax, अचिन्हित पूर्णांक halign,
			   अचिन्हित पूर्णांक salign);

/**
 * v4l2_find_nearest_size - Find the nearest size among a discrete
 *	set of resolutions contained in an array of a driver specअगरic काष्ठा.
 *
 * @array: a driver specअगरic array of image sizes
 * @array_size: the length of the driver specअगरic array of image sizes
 * @width_field: the name of the width field in the driver specअगरic काष्ठा
 * @height_field: the name of the height field in the driver specअगरic काष्ठा
 * @width: desired width.
 * @height: desired height.
 *
 * Finds the बंदst resolution to minimize the width and height dअगरferences
 * between what requested and the supported resolutions. The size of the width
 * and height fields in the driver specअगरic must equal to that of u32, i.e. four
 * bytes.
 *
 * Returns the best match or शून्य अगर the length of the array is zero.
 */
#घोषणा v4l2_find_nearest_size(array, array_size, width_field, height_field, \
			       width, height)				\
	(अणु								\
		BUILD_BUG_ON(माप((array)->width_field) != माप(u32) || \
			     माप((array)->height_field) != माप(u32)); \
		(typeof(&(array)[0]))__v4l2_find_nearest_size(		\
			(array), array_size, माप(*(array)),		\
			दुरत्व(typeof(*(array)), width_field),	\
			दुरत्व(typeof(*(array)), height_field),	\
			width, height);					\
	पूर्ण)
स्थिर व्योम *
__v4l2_find_nearest_size(स्थिर व्योम *array, माप_प्रकार array_size,
			 माप_प्रकार entry_size, माप_प्रकार width_offset,
			 माप_प्रकार height_offset, s32 width, s32 height);

/**
 * v4l2_g_parm_cap - helper routine क्रम vidioc_g_parm to fill this in by
 *      calling the g_frame_पूर्णांकerval op of the given subdev. It only works
 *      क्रम V4L2_BUF_TYPE_VIDEO_CAPTURE(_MPLANE), hence the _cap in the
 *      function name.
 *
 * @vdev: the काष्ठा video_device poपूर्णांकer. Used to determine the device caps.
 * @sd: the sub-device poपूर्णांकer.
 * @a: the VIDIOC_G_PARM argument.
 */
पूर्णांक v4l2_g_parm_cap(काष्ठा video_device *vdev,
		    काष्ठा v4l2_subdev *sd, काष्ठा v4l2_streamparm *a);

/**
 * v4l2_s_parm_cap - helper routine क्रम vidioc_s_parm to fill this in by
 *      calling the s_frame_पूर्णांकerval op of the given subdev. It only works
 *      क्रम V4L2_BUF_TYPE_VIDEO_CAPTURE(_MPLANE), hence the _cap in the
 *      function name.
 *
 * @vdev: the काष्ठा video_device poपूर्णांकer. Used to determine the device caps.
 * @sd: the sub-device poपूर्णांकer.
 * @a: the VIDIOC_S_PARM argument.
 */
पूर्णांक v4l2_s_parm_cap(काष्ठा video_device *vdev,
		    काष्ठा v4l2_subdev *sd, काष्ठा v4l2_streamparm *a);

/* Compare two v4l2_fract काष्ठाs */
#घोषणा V4L2_FRACT_COMPARE(a, OP, b)			\
	((u64)(a).numerator * (b).denominator OP	\
	(u64)(b).numerator * (a).denominator)

/* ------------------------------------------------------------------------- */

/* Pixel क्रमmat and FourCC helpers */

/**
 * क्रमागत v4l2_pixel_encoding - specअगरies the pixel encoding value
 *
 * @V4L2_PIXEL_ENC_UNKNOWN:	Pixel encoding is unknown/un-initialized
 * @V4L2_PIXEL_ENC_YUV:		Pixel encoding is YUV
 * @V4L2_PIXEL_ENC_RGB:		Pixel encoding is RGB
 * @V4L2_PIXEL_ENC_BAYER:	Pixel encoding is Bayer
 */
क्रमागत v4l2_pixel_encoding अणु
	V4L2_PIXEL_ENC_UNKNOWN = 0,
	V4L2_PIXEL_ENC_YUV = 1,
	V4L2_PIXEL_ENC_RGB = 2,
	V4L2_PIXEL_ENC_BAYER = 3,
पूर्ण;

/**
 * काष्ठा v4l2_क्रमmat_info - inक्रमmation about a V4L2 क्रमmat
 * @क्रमmat: 4CC क्रमmat identअगरier (V4L2_PIX_FMT_*)
 * @pixel_enc: Pixel encoding (see क्रमागत v4l2_pixel_encoding above)
 * @mem_planes: Number of memory planes, which includes the alpha plane (1 to 4).
 * @comp_planes: Number of component planes, which includes the alpha plane (1 to 4).
 * @bpp: Array of per-plane bytes per pixel
 * @hभाग: Horizontal chroma subsampling factor
 * @vभाग: Vertical chroma subsampling factor
 * @block_w: Per-plane macroblock pixel width (optional)
 * @block_h: Per-plane macroblock pixel height (optional)
 */
काष्ठा v4l2_क्रमmat_info अणु
	u32 क्रमmat;
	u8 pixel_enc;
	u8 mem_planes;
	u8 comp_planes;
	u8 bpp[4];
	u8 hभाग;
	u8 vभाग;
	u8 block_w[4];
	u8 block_h[4];
पूर्ण;

अटल अंतरभूत bool v4l2_is_क्रमmat_rgb(स्थिर काष्ठा v4l2_क्रमmat_info *f)
अणु
	वापस f && f->pixel_enc == V4L2_PIXEL_ENC_RGB;
पूर्ण

अटल अंतरभूत bool v4l2_is_क्रमmat_yuv(स्थिर काष्ठा v4l2_क्रमmat_info *f)
अणु
	वापस f && f->pixel_enc == V4L2_PIXEL_ENC_YUV;
पूर्ण

अटल अंतरभूत bool v4l2_is_क्रमmat_bayer(स्थिर काष्ठा v4l2_क्रमmat_info *f)
अणु
	वापस f && f->pixel_enc == V4L2_PIXEL_ENC_BAYER;
पूर्ण

स्थिर काष्ठा v4l2_क्रमmat_info *v4l2_क्रमmat_info(u32 क्रमmat);
व्योम v4l2_apply_frmsize_स्थिरraपूर्णांकs(u32 *width, u32 *height,
				    स्थिर काष्ठा v4l2_frmsize_stepwise *frmsize);
पूर्णांक v4l2_fill_pixfmt(काष्ठा v4l2_pix_क्रमmat *pixfmt, u32 pixelक्रमmat,
		     u32 width, u32 height);
पूर्णांक v4l2_fill_pixfmt_mp(काष्ठा v4l2_pix_क्रमmat_mplane *pixfmt, u32 pixelक्रमmat,
			u32 width, u32 height);

/**
 * v4l2_get_link_freq - Get link rate from transmitter
 *
 * @handler: The transmitter's control handler
 * @mul: The multiplier between pixel rate and link frequency. Bits per pixel on
 *	 D-PHY, samples per घड़ी on parallel. 0 otherwise.
 * @भाग: The भागisor between pixel rate and link frequency. Number of data lanes
 *	 बार two on D-PHY, 1 on parallel. 0 otherwise.
 *
 * This function is पूर्णांकended क्रम obtaining the link frequency from the
 * transmitter sub-devices. It वापसs the link rate, either from the
 * V4L2_CID_LINK_FREQ control implemented by the transmitter, or value
 * calculated based on the V4L2_CID_PIXEL_RATE implemented by the transmitter.
 *
 * Returns link frequency on success, otherwise a negative error code:
 *	-ENOENT: Link frequency or pixel rate control not found
 *	-EINVAL: Invalid link frequency value
 */
s64 v4l2_get_link_freq(काष्ठा v4l2_ctrl_handler *handler, अचिन्हित पूर्णांक mul,
		       अचिन्हित पूर्णांक भाग);

अटल अंतरभूत u64 v4l2_buffer_get_बारtamp(स्थिर काष्ठा v4l2_buffer *buf)
अणु
	/*
	 * When the बारtamp comes from 32-bit user space, there may be
	 * uninitialized data in tv_usec, so cast it to u32.
	 * Otherwise allow invalid input क्रम backwards compatibility.
	 */
	वापस buf->बारtamp.tv_sec * NSEC_PER_SEC +
		(u32)buf->बारtamp.tv_usec * NSEC_PER_USEC;
पूर्ण

अटल अंतरभूत व्योम v4l2_buffer_set_बारtamp(काष्ठा v4l2_buffer *buf,
					     u64 बारtamp)
अणु
	काष्ठा बारpec64 ts = ns_to_बारpec64(बारtamp);

	buf->बारtamp.tv_sec  = ts.tv_sec;
	buf->बारtamp.tv_usec = ts.tv_nsec / NSEC_PER_USEC;
पूर्ण

अटल अंतरभूत bool v4l2_is_colorspace_valid(__u32 colorspace)
अणु
	वापस colorspace > V4L2_COLORSPACE_DEFAULT &&
	       colorspace <= V4L2_COLORSPACE_DCI_P3;
पूर्ण

अटल अंतरभूत bool v4l2_is_xfer_func_valid(__u32 xfer_func)
अणु
	वापस xfer_func > V4L2_XFER_FUNC_DEFAULT &&
	       xfer_func <= V4L2_XFER_FUNC_SMPTE2084;
पूर्ण

अटल अंतरभूत bool v4l2_is_ycbcr_enc_valid(__u8 ycbcr_enc)
अणु
	वापस ycbcr_enc > V4L2_YCBCR_ENC_DEFAULT &&
	       ycbcr_enc <= V4L2_YCBCR_ENC_SMPTE240M;
पूर्ण

अटल अंतरभूत bool v4l2_is_hsv_enc_valid(__u8 hsv_enc)
अणु
	वापस hsv_enc == V4L2_HSV_ENC_180 || hsv_enc == V4L2_HSV_ENC_256;
पूर्ण

अटल अंतरभूत bool v4l2_is_quant_valid(__u8 quantization)
अणु
	वापस quantization == V4L2_QUANTIZATION_FULL_RANGE ||
	       quantization == V4L2_QUANTIZATION_LIM_RANGE;
पूर्ण

#पूर्ण_अगर /* V4L2_COMMON_H_ */
