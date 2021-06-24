<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ov772x Camera
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 */

#अगर_अघोषित __OV772X_H__
#घोषणा __OV772X_H__

/* क्रम flags */
#घोषणा OV772X_FLAG_VFLIP	(1 << 0) /* Vertical flip image */
#घोषणा OV772X_FLAG_HFLIP	(1 << 1) /* Horizontal flip image */

/*
 * क्रम Edge ctrl
 *
 * strength also control Auto or Manual Edge Control Mode
 * see also OV772X_MANUAL_EDGE_CTRL
 */
काष्ठा ov772x_edge_ctrl अणु
	अचिन्हित अक्षर strength;
	अचिन्हित अक्षर threshold;
	अचिन्हित अक्षर upper;
	अचिन्हित अक्षर lower;
पूर्ण;

#घोषणा OV772X_MANUAL_EDGE_CTRL		0x80 /* un-used bit of strength */
#घोषणा OV772X_EDGE_STRENGTH_MASK	0x1F
#घोषणा OV772X_EDGE_THRESHOLD_MASK	0x0F
#घोषणा OV772X_EDGE_UPPER_MASK		0xFF
#घोषणा OV772X_EDGE_LOWER_MASK		0xFF

#घोषणा OV772X_AUTO_EDGECTRL(u, l)	\
अणु					\
	.upper = (u & OV772X_EDGE_UPPER_MASK),	\
	.lower = (l & OV772X_EDGE_LOWER_MASK),	\
पूर्ण

#घोषणा OV772X_MANUAL_EDGECTRL(s, t)			\
अणु							\
	.strength  = (s & OV772X_EDGE_STRENGTH_MASK) |	\
			OV772X_MANUAL_EDGE_CTRL,	\
	.threshold = (t & OV772X_EDGE_THRESHOLD_MASK),	\
पूर्ण

/**
 * काष्ठा ov772x_camera_info -	ov772x driver पूर्णांकerface काष्ठाure
 * @flags:		Sensor configuration flags
 * @edgectrl:		Sensor edge control
 */
काष्ठा ov772x_camera_info अणु
	अचिन्हित दीर्घ		flags;
	काष्ठा ov772x_edge_ctrl	edgectrl;
पूर्ण;

#पूर्ण_अगर /* __OV772X_H__ */
