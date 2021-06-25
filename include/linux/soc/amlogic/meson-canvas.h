<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 BayLibre, SAS
 */
#अगर_अघोषित __SOC_MESON_CANVAS_H
#घोषणा __SOC_MESON_CANVAS_H

#समावेश <linux/kernel.h>

#घोषणा MESON_CANVAS_WRAP_NONE	0x00
#घोषणा MESON_CANVAS_WRAP_X	0x01
#घोषणा MESON_CANVAS_WRAP_Y	0x02

#घोषणा MESON_CANVAS_BLKMODE_LINEAR	0x00
#घोषणा MESON_CANVAS_BLKMODE_32x32	0x01
#घोषणा MESON_CANVAS_BLKMODE_64x64	0x02

#घोषणा MESON_CANVAS_ENDIAN_SWAP16	0x1
#घोषणा MESON_CANVAS_ENDIAN_SWAP32	0x3
#घोषणा MESON_CANVAS_ENDIAN_SWAP64	0x7
#घोषणा MESON_CANVAS_ENDIAN_SWAP128	0xf

काष्ठा device;
काष्ठा meson_canvas;

/**
 * meson_canvas_get() - get a canvas provider instance
 *
 * @dev: consumer device poपूर्णांकer
 */
काष्ठा meson_canvas *meson_canvas_get(काष्ठा device *dev);

/**
 * meson_canvas_alloc() - take ownership of a canvas
 *
 * @canvas: canvas provider instance retrieved from meson_canvas_get()
 * @canvas_index: will be filled with the canvas ID
 */
पूर्णांक meson_canvas_alloc(काष्ठा meson_canvas *canvas, u8 *canvas_index);

/**
 * meson_canvas_मुक्त() - हटाओ ownership from a canvas
 *
 * @canvas: canvas provider instance retrieved from meson_canvas_get()
 * @canvas_index: canvas ID that was obtained via meson_canvas_alloc()
 */
पूर्णांक meson_canvas_मुक्त(काष्ठा meson_canvas *canvas, u8 canvas_index);

/**
 * meson_canvas_config() - configure a canvas
 *
 * @canvas: canvas provider instance retrieved from meson_canvas_get()
 * @canvas_index: canvas ID that was obtained via meson_canvas_alloc()
 * @addr: physical address to the pixel buffer
 * @stride: width of the buffer
 * @height: height of the buffer
 * @wrap: unकरोcumented
 * @blkmode: block mode (linear, 32x32, 64x64)
 * @endian: byte swapping (swap16, swap32, swap64, swap128)
 */
पूर्णांक meson_canvas_config(काष्ठा meson_canvas *canvas, u8 canvas_index,
			u32 addr, u32 stride, u32 height,
			अचिन्हित पूर्णांक wrap, अचिन्हित पूर्णांक blkmode,
			अचिन्हित पूर्णांक endian);

#पूर्ण_अगर
