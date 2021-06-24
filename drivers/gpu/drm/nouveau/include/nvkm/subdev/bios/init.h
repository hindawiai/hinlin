<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_INIT_H__
#घोषणा __NVBIOS_INIT_H__

काष्ठा nvbios_init अणु
	काष्ठा nvkm_subdev *subdev;
	u32 offset;

	काष्ठा dcb_output *outp;
	पूर्णांक or;
	पूर्णांक link;
	पूर्णांक head;

	/* पूर्णांकernal state used during parsing */
	u8 execute;
	u32 nested;
	u32 repeat;
	u32 repend;
	u32 ramcfg;
पूर्ण;

#घोषणा nvbios_init(s,o,ARGS...) (अणु                                            \
	काष्ठा nvbios_init init = अणु                                            \
		.subdev = (s),                                                 \
		.offset = (o),                                                 \
		.or = -1,                                                      \
		.link = 0,                                                     \
		.head = -1,                                                    \
		.execute = 1,                                                  \
	पूर्ण;                                                                     \
	ARGS                                                                   \
	nvbios_exec(&init);                                                    \
पूर्ण)
पूर्णांक nvbios_exec(काष्ठा nvbios_init *);

पूर्णांक nvbios_post(काष्ठा nvkm_subdev *, bool execute);
#पूर्ण_अगर
