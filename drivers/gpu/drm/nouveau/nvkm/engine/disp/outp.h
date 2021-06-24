<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_OUTP_H__
#घोषणा __NVKM_DISP_OUTP_H__
#समावेश <engine/disp.h>

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/dcb.h>

काष्ठा nvkm_outp अणु
	स्थिर काष्ठा nvkm_outp_func *func;
	काष्ठा nvkm_disp *disp;
	पूर्णांक index;
	काष्ठा dcb_output info;

	काष्ठा nvkm_i2c_bus *i2c;

	काष्ठा list_head head;
	काष्ठा nvkm_conn *conn;
	bool identity;

	/* Assembly state. */
#घोषणा NVKM_OUTP_PRIV 1
#घोषणा NVKM_OUTP_USER 2
	u8 acquired:2;
	काष्ठा nvkm_ior *ior;
पूर्ण;

पूर्णांक nvkm_outp_ctor(स्थिर काष्ठा nvkm_outp_func *, काष्ठा nvkm_disp *,
		   पूर्णांक index, काष्ठा dcb_output *, काष्ठा nvkm_outp *);
पूर्णांक nvkm_outp_new(काष्ठा nvkm_disp *, पूर्णांक index, काष्ठा dcb_output *,
		  काष्ठा nvkm_outp **);
व्योम nvkm_outp_del(काष्ठा nvkm_outp **);
व्योम nvkm_outp_init(काष्ठा nvkm_outp *);
व्योम nvkm_outp_fini(काष्ठा nvkm_outp *);
पूर्णांक nvkm_outp_acquire(काष्ठा nvkm_outp *, u8 user, bool hda);
व्योम nvkm_outp_release(काष्ठा nvkm_outp *, u8 user);
व्योम nvkm_outp_route(काष्ठा nvkm_disp *);

काष्ठा nvkm_outp_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_outp *);
	व्योम (*init)(काष्ठा nvkm_outp *);
	व्योम (*fini)(काष्ठा nvkm_outp *);
	पूर्णांक (*acquire)(काष्ठा nvkm_outp *);
	व्योम (*release)(काष्ठा nvkm_outp *);
	व्योम (*disable)(काष्ठा nvkm_outp *, काष्ठा nvkm_ior *);
पूर्ण;

#घोषणा OUTP_MSG(o,l,f,a...) करो अणु                                              \
	काष्ठा nvkm_outp *_outp = (o);                                         \
	nvkm_##l(&_outp->disp->engine.subdev, "outp %02x:%04x:%04x: "f"\n",    \
		 _outp->index, _outp->info.hasht, _outp->info.hashm, ##a);     \
पूर्ण जबतक(0)
#घोषणा OUTP_ERR(o,f,a...) OUTP_MSG((o), error, f, ##a)
#घोषणा OUTP_DBG(o,f,a...) OUTP_MSG((o), debug, f, ##a)
#घोषणा OUTP_TRACE(o,f,a...) OUTP_MSG((o), trace, f, ##a)
#पूर्ण_अगर
