<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_VGA_H__
#घोषणा __NOUVEAU_VGA_H__
#समावेश <core/subdev.h>

/* access to various legacy io ports */
u8   nvkm_rdport(काष्ठा nvkm_device *, पूर्णांक head, u16 port);
व्योम nvkm_wrport(काष्ठा nvkm_device *, पूर्णांक head, u16 port, u8 value);

/* VGA Sequencer */
u8   nvkm_rdvgas(काष्ठा nvkm_device *, पूर्णांक head, u8 index);
व्योम nvkm_wrvgas(काष्ठा nvkm_device *, पूर्णांक head, u8 index, u8 value);

/* VGA Graphics */
u8   nvkm_rdvgag(काष्ठा nvkm_device *, पूर्णांक head, u8 index);
व्योम nvkm_wrvgag(काष्ठा nvkm_device *, पूर्णांक head, u8 index, u8 value);

/* VGA CRTC */
u8   nvkm_rdvgac(काष्ठा nvkm_device *, पूर्णांक head, u8 index);
व्योम nvkm_wrvgac(काष्ठा nvkm_device *, पूर्णांक head, u8 index, u8 value);

/* VGA indexed port access dispatcher */
u8   nvkm_rdvgai(काष्ठा nvkm_device *, पूर्णांक head, u16 port, u8 index);
व्योम nvkm_wrvgai(काष्ठा nvkm_device *, पूर्णांक head, u16 port, u8 index, u8 value);

bool nvkm_lockvgac(काष्ठा nvkm_device *, bool lock);
u8   nvkm_rdvgaowner(काष्ठा nvkm_device *);
व्योम nvkm_wrvgaowner(काष्ठा nvkm_device *, u8);
#पूर्ण_अगर
