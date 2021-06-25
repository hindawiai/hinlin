<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DDK750_MODE_H__
#घोषणा DDK750_MODE_H__

#समावेश "ddk750_chip.h"

क्रमागत spolarity अणु
	POS = 0, /* positive */
	NEG, /* negative */
पूर्ण;

काष्ठा mode_parameter अणु
	/* Horizontal timing. */
	अचिन्हित दीर्घ horizontal_total;
	अचिन्हित दीर्घ horizontal_display_end;
	अचिन्हित दीर्घ horizontal_sync_start;
	अचिन्हित दीर्घ horizontal_sync_width;
	क्रमागत spolarity horizontal_sync_polarity;

	/* Vertical timing. */
	अचिन्हित दीर्घ vertical_total;
	अचिन्हित दीर्घ vertical_display_end;
	अचिन्हित दीर्घ vertical_sync_start;
	अचिन्हित दीर्घ vertical_sync_height;
	क्रमागत spolarity vertical_sync_polarity;

	/* Refresh timing. */
	अचिन्हित दीर्घ pixel_घड़ी;
	अचिन्हित दीर्घ horizontal_frequency;
	अचिन्हित दीर्घ vertical_frequency;

	/* Clock Phase. This घड़ी phase only applies to Panel. */
	क्रमागत spolarity घड़ी_phase_polarity;
पूर्ण;

पूर्णांक ddk750_setModeTiming(काष्ठा mode_parameter *parm, क्रमागत घड़ी_प्रकारype घड़ी);
#पूर्ण_अगर
