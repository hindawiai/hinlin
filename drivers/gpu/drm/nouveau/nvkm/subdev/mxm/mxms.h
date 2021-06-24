<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVMXM_MXMS_H__
#घोषणा __NVMXM_MXMS_H__
#समावेश "priv.h"

काष्ठा mxms_odev अणु
	u8 outp_type;
	u8 conn_type;
	u8 ddc_port;
	u8 dig_conn;
पूर्ण;

व्योम mxms_output_device(काष्ठा nvkm_mxm *, u8 *, काष्ठा mxms_odev *);

u16  mxms_version(काष्ठा nvkm_mxm *);
u16  mxms_headerlen(काष्ठा nvkm_mxm *);
u16  mxms_काष्ठाlen(काष्ठा nvkm_mxm *);
bool mxms_checksum(काष्ठा nvkm_mxm *);
bool mxms_valid(काष्ठा nvkm_mxm *);

bool mxms_क्रमeach(काष्ठा nvkm_mxm *, u8,
		  bool (*)(काष्ठा nvkm_mxm *, u8 *, व्योम *), व्योम *);
#पूर्ण_अगर
