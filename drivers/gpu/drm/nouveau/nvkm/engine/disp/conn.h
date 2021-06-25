<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_CONN_H__
#घोषणा __NVKM_DISP_CONN_H__
#समावेश <engine/disp.h>

#समावेश <core/notअगरy.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/conn.h>

काष्ठा nvkm_conn अणु
	काष्ठा nvkm_disp *disp;
	पूर्णांक index;
	काष्ठा nvbios_connE info;

	काष्ठा nvkm_notअगरy hpd;

	काष्ठा list_head head;
पूर्ण;

पूर्णांक nvkm_conn_new(काष्ठा nvkm_disp *, पूर्णांक index, काष्ठा nvbios_connE *,
		  काष्ठा nvkm_conn **);
व्योम nvkm_conn_del(काष्ठा nvkm_conn **);
व्योम nvkm_conn_init(काष्ठा nvkm_conn *);
व्योम nvkm_conn_fini(काष्ठा nvkm_conn *);

#घोषणा CONN_MSG(c,l,f,a...) करो अणु                                              \
	काष्ठा nvkm_conn *_conn = (c);                                    \
	nvkm_##l(&_conn->disp->engine.subdev, "conn %02x:%02x%02x: "f"\n",     \
		 _conn->index, _conn->info.location, _conn->info.type, ##a);   \
पूर्ण जबतक(0)
#घोषणा CONN_ERR(c,f,a...) CONN_MSG((c), error, f, ##a)
#घोषणा CONN_DBG(c,f,a...) CONN_MSG((c), debug, f, ##a)
#घोषणा CONN_TRACE(c,f,a...) CONN_MSG((c), trace, f, ##a)
#पूर्ण_अगर
