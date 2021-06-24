<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __VIDEO_EP93XX_H
#घोषणा __VIDEO_EP93XX_H

काष्ठा platक्रमm_device;
काष्ठा fb_info;

/* VideoAttributes flags */
#घोषणा EP93XXFB_STATE_MACHINE_ENABLE	(1 << 0)
#घोषणा EP93XXFB_PIXEL_CLOCK_ENABLE	(1 << 1)
#घोषणा EP93XXFB_VSYNC_ENABLE		(1 << 2)
#घोषणा EP93XXFB_PIXEL_DATA_ENABLE	(1 << 3)
#घोषणा EP93XXFB_COMPOSITE_SYNC		(1 << 4)
#घोषणा EP93XXFB_SYNC_VERT_HIGH		(1 << 5)
#घोषणा EP93XXFB_SYNC_HORIZ_HIGH	(1 << 6)
#घोषणा EP93XXFB_SYNC_BLANK_HIGH	(1 << 7)
#घोषणा EP93XXFB_PCLK_FALLING		(1 << 8)
#घोषणा EP93XXFB_ENABLE_AC		(1 << 9)
#घोषणा EP93XXFB_ENABLE_LCD		(1 << 10)
#घोषणा EP93XXFB_ENABLE_CCIR		(1 << 12)
#घोषणा EP93XXFB_USE_PARALLEL_INTERFACE	(1 << 13)
#घोषणा EP93XXFB_ENABLE_INTERRUPT	(1 << 14)
#घोषणा EP93XXFB_USB_INTERLACE		(1 << 16)
#घोषणा EP93XXFB_USE_EQUALIZATION	(1 << 17)
#घोषणा EP93XXFB_USE_DOUBLE_HORZ	(1 << 18)
#घोषणा EP93XXFB_USE_DOUBLE_VERT	(1 << 19)
#घोषणा EP93XXFB_USE_BLANK_PIXEL	(1 << 20)
#घोषणा EP93XXFB_USE_SDCSN0		(0 << 21)
#घोषणा EP93XXFB_USE_SDCSN1		(1 << 21)
#घोषणा EP93XXFB_USE_SDCSN2		(2 << 21)
#घोषणा EP93XXFB_USE_SDCSN3		(3 << 21)

#घोषणा EP93XXFB_ENABLE			(EP93XXFB_STATE_MACHINE_ENABLE	| \
					 EP93XXFB_PIXEL_CLOCK_ENABLE	| \
					 EP93XXFB_VSYNC_ENABLE		| \
					 EP93XXFB_PIXEL_DATA_ENABLE)

काष्ठा ep93xxfb_mach_info अणु
	अचिन्हित पूर्णांक			flags;
	पूर्णांक	(*setup)(काष्ठा platक्रमm_device *pdev);
	व्योम	(*tearकरोwn)(काष्ठा platक्रमm_device *pdev);
	व्योम	(*blank)(पूर्णांक blank_mode, काष्ठा fb_info *info);
पूर्ण;

#पूर्ण_अगर /* __VIDEO_EP93XX_H */
