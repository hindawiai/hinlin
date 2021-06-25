<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * MIPI Display Bus Interface (DBI) LCD controller support
 *
 * Copyright 2016 Noralf Trथचnnes
 */

#अगर_अघोषित __LINUX_MIPI_DBI_H
#घोषणा __LINUX_MIPI_DBI_H

#समावेश <linux/mutex.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_simple_kms_helper.h>

काष्ठा drm_rect;
काष्ठा spi_device;
काष्ठा gpio_desc;
काष्ठा regulator;

/**
 * काष्ठा mipi_dbi - MIPI DBI पूर्णांकerface
 */
काष्ठा mipi_dbi अणु
	/**
	 * @cmdlock: Command lock
	 */
	काष्ठा mutex cmdlock;

	/**
	 * @command: Bus specअगरic callback executing commands.
	 */
	पूर्णांक (*command)(काष्ठा mipi_dbi *dbi, u8 *cmd, u8 *param, माप_प्रकार num);

	/**
	 * @पढ़ो_commands: Array of पढ़ो commands terminated by a zero entry.
	 *                 Reading is disabled अगर this is शून्य.
	 */
	स्थिर u8 *पढ़ो_commands;

	/**
	 * @swap_bytes: Swap bytes in buffer beक्रमe transfer
	 */
	bool swap_bytes;

	/**
	 * @reset: Optional reset gpio
	 */
	काष्ठा gpio_desc *reset;

	/* Type C specअगरic */

	/**
	 * @spi: SPI device
	 */
	काष्ठा spi_device *spi;

	/**
	 * @dc: Optional D/C gpio.
	 */
	काष्ठा gpio_desc *dc;

	/**
	 * @tx_buf9: Buffer used क्रम Option 1 9-bit conversion
	 */
	व्योम *tx_buf9;

	/**
	 * @tx_buf9_len: Size of tx_buf9.
	 */
	माप_प्रकार tx_buf9_len;
पूर्ण;

/**
 * काष्ठा mipi_dbi_dev - MIPI DBI device
 */
काष्ठा mipi_dbi_dev अणु
	/**
	 * @drm: DRM device
	 */
	काष्ठा drm_device drm;

	/**
	 * @pipe: Display pipe काष्ठाure
	 */
	काष्ठा drm_simple_display_pipe pipe;

	/**
	 * @connector: Connector
	 */
	काष्ठा drm_connector connector;

	/**
	 * @mode: Fixed display mode
	 */
	काष्ठा drm_display_mode mode;

	/**
	 * @tx_buf: Buffer used क्रम transfer (copy clip rect area)
	 */
	u16 *tx_buf;

	/**
	 * @rotation: initial rotation in degrees Counter Clock Wise
	 */
	अचिन्हित पूर्णांक rotation;

	/**
	 * @left_offset: Horizontal offset of the display relative to the
	 *               controller's driver array
	 */
	अचिन्हित पूर्णांक left_offset;

	/**
	 * @top_offset: Vertical offset of the display relative to the
	 *              controller's driver array
	 */
	अचिन्हित पूर्णांक top_offset;

	/**
	 * @backlight: backlight device (optional)
	 */
	काष्ठा backlight_device *backlight;

	/**
	 * @regulator: घातer regulator (optional)
	 */
	काष्ठा regulator *regulator;

	/**
	 * @dbi: MIPI DBI पूर्णांकerface
	 */
	काष्ठा mipi_dbi dbi;
पूर्ण;

अटल अंतरभूत काष्ठा mipi_dbi_dev *drm_to_mipi_dbi_dev(काष्ठा drm_device *drm)
अणु
	वापस container_of(drm, काष्ठा mipi_dbi_dev, drm);
पूर्ण

पूर्णांक mipi_dbi_spi_init(काष्ठा spi_device *spi, काष्ठा mipi_dbi *dbi,
		      काष्ठा gpio_desc *dc);
पूर्णांक mipi_dbi_dev_init_with_क्रमmats(काष्ठा mipi_dbi_dev *dbidev,
				   स्थिर काष्ठा drm_simple_display_pipe_funcs *funcs,
				   स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
				   स्थिर काष्ठा drm_display_mode *mode,
				   अचिन्हित पूर्णांक rotation, माप_प्रकार tx_buf_size);
पूर्णांक mipi_dbi_dev_init(काष्ठा mipi_dbi_dev *dbidev,
		      स्थिर काष्ठा drm_simple_display_pipe_funcs *funcs,
		      स्थिर काष्ठा drm_display_mode *mode, अचिन्हित पूर्णांक rotation);
व्योम mipi_dbi_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
			  काष्ठा drm_plane_state *old_state);
व्योम mipi_dbi_enable_flush(काष्ठा mipi_dbi_dev *dbidev,
			   काष्ठा drm_crtc_state *crtc_state,
			   काष्ठा drm_plane_state *plan_state);
व्योम mipi_dbi_pipe_disable(काष्ठा drm_simple_display_pipe *pipe);
व्योम mipi_dbi_hw_reset(काष्ठा mipi_dbi *dbi);
bool mipi_dbi_display_is_on(काष्ठा mipi_dbi *dbi);
पूर्णांक mipi_dbi_घातeron_reset(काष्ठा mipi_dbi_dev *dbidev);
पूर्णांक mipi_dbi_घातeron_conditional_reset(काष्ठा mipi_dbi_dev *dbidev);

u32 mipi_dbi_spi_cmd_max_speed(काष्ठा spi_device *spi, माप_प्रकार len);
पूर्णांक mipi_dbi_spi_transfer(काष्ठा spi_device *spi, u32 speed_hz,
			  u8 bpw, स्थिर व्योम *buf, माप_प्रकार len);

पूर्णांक mipi_dbi_command_पढ़ो(काष्ठा mipi_dbi *dbi, u8 cmd, u8 *val);
पूर्णांक mipi_dbi_command_buf(काष्ठा mipi_dbi *dbi, u8 cmd, u8 *data, माप_प्रकार len);
पूर्णांक mipi_dbi_command_stackbuf(काष्ठा mipi_dbi *dbi, u8 cmd, स्थिर u8 *data,
			      माप_प्रकार len);
पूर्णांक mipi_dbi_buf_copy(व्योम *dst, काष्ठा drm_framebuffer *fb,
		      काष्ठा drm_rect *clip, bool swap);
/**
 * mipi_dbi_command - MIPI DCS command with optional parameter(s)
 * @dbi: MIPI DBI काष्ठाure
 * @cmd: Command
 * @seq: Optional parameter(s)
 *
 * Send MIPI DCS command to the controller. Use mipi_dbi_command_पढ़ो() क्रम
 * get/पढ़ो.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
#घोषणा mipi_dbi_command(dbi, cmd, seq...) \
(अणु \
	स्थिर u8 d[] = अणु seq पूर्ण; \
	mipi_dbi_command_stackbuf(dbi, cmd, d, ARRAY_SIZE(d)); \
पूर्ण)

#अगर_घोषित CONFIG_DEBUG_FS
व्योम mipi_dbi_debugfs_init(काष्ठा drm_minor *minor);
#अन्यथा
#घोषणा mipi_dbi_debugfs_init		शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_MIPI_DBI_H */
