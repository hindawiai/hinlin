<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
 * lib/minmax.c: winकरोwed min/max tracker by Kathleen Nichols.
 *
 */
#अगर_अघोषित MINMAX_H
#घोषणा MINMAX_H

#समावेश <linux/types.h>

/* A single data poपूर्णांक क्रम our parameterized min-max tracker */
काष्ठा minmax_sample अणु
	u32	t;	/* समय measurement was taken */
	u32	v;	/* value measured */
पूर्ण;

/* State क्रम the parameterized min-max tracker */
काष्ठा minmax अणु
	काष्ठा minmax_sample s[3];
पूर्ण;

अटल अंतरभूत u32 minmax_get(स्थिर काष्ठा minmax *m)
अणु
	वापस m->s[0].v;
पूर्ण

अटल अंतरभूत u32 minmax_reset(काष्ठा minmax *m, u32 t, u32 meas)
अणु
	काष्ठा minmax_sample val = अणु .t = t, .v = meas पूर्ण;

	m->s[2] = m->s[1] = m->s[0] = val;
	वापस m->s[0].v;
पूर्ण

u32 minmax_running_max(काष्ठा minmax *m, u32 win, u32 t, u32 meas);
u32 minmax_running_min(काष्ठा minmax *m, u32 win, u32 t, u32 meas);

#पूर्ण_अगर
