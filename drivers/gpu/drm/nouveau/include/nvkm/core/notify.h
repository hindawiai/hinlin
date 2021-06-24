<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_NOTIFY_H__
#घोषणा __NVKM_NOTIFY_H__
#समावेश <core/os.h>
काष्ठा nvkm_object;

काष्ठा nvkm_notअगरy अणु
	काष्ठा nvkm_event *event;
	काष्ठा list_head head;
#घोषणा NVKM_NOTIFY_USER 0
#घोषणा NVKM_NOTIFY_WORK 1
	अचिन्हित दीर्घ flags;
	पूर्णांक block;
#घोषणा NVKM_NOTIFY_DROP 0
#घोषणा NVKM_NOTIFY_KEEP 1
	पूर्णांक (*func)(काष्ठा nvkm_notअगरy *);

	/* set by nvkm_event ctor */
	u32 types;
	पूर्णांक index;
	u32 size;

	काष्ठा work_काष्ठा work;
	/* this is स्थिर क्रम a *very* good reason - the data might be on the
	 * stack from an irq handler.  अगर you're not core/notअगरy.c then you
	 * should probably think twice beक्रमe casting it away...
	 */
	स्थिर व्योम *data;
पूर्ण;

पूर्णांक  nvkm_notअगरy_init(काष्ठा nvkm_object *, काष्ठा nvkm_event *,
		      पूर्णांक (*func)(काष्ठा nvkm_notअगरy *), bool work,
		      व्योम *data, u32 size, u32 reply,
		      काष्ठा nvkm_notअगरy *);
व्योम nvkm_notअगरy_fini(काष्ठा nvkm_notअगरy *);
व्योम nvkm_notअगरy_get(काष्ठा nvkm_notअगरy *);
व्योम nvkm_notअगरy_put(काष्ठा nvkm_notअगरy *);
व्योम nvkm_notअगरy_send(काष्ठा nvkm_notअगरy *, व्योम *data, u32 size);
#पूर्ण_अगर
