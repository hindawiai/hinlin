<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_NOTIFY_H__
#घोषणा __NVIF_NOTIFY_H__

काष्ठा nvअगर_notअगरy अणु
	काष्ठा nvअगर_object *object;
	स्थिर अक्षर *name;
	पूर्णांक index;

#घोषणा NVIF_NOTIFY_USER 0
#घोषणा NVIF_NOTIFY_WORK 1
	अचिन्हित दीर्घ flags;
	atomic_t अ_दोnt;
	व्योम (*dtor)(काष्ठा nvअगर_notअगरy *);
#घोषणा NVIF_NOTIFY_DROP 0
#घोषणा NVIF_NOTIFY_KEEP 1
	पूर्णांक  (*func)(काष्ठा nvअगर_notअगरy *);

	/* this is स्थिर क्रम a *very* good reason - the data might be on the
	 * stack from an irq handler.  अगर you're not nvअगर/notअगरy.c then you
	 * should probably think twice beक्रमe casting it away...
	 */
	स्थिर व्योम *data;
	u32 size;
	काष्ठा work_काष्ठा work;
पूर्ण;

पूर्णांक  nvअगर_notअगरy_ctor(काष्ठा nvअगर_object *, स्थिर अक्षर *name,
		      पूर्णांक (*func)(काष्ठा nvअगर_notअगरy *), bool work, u8 type,
		      व्योम *data, u32 size, u32 reply, काष्ठा nvअगर_notअगरy *);
पूर्णांक  nvअगर_notअगरy_dtor(काष्ठा nvअगर_notअगरy *);
पूर्णांक  nvअगर_notअगरy_get(काष्ठा nvअगर_notअगरy *);
पूर्णांक  nvअगर_notअगरy_put(काष्ठा nvअगर_notअगरy *);
पूर्णांक  nvअगर_notअगरy(स्थिर व्योम *, u32, स्थिर व्योम *, u32);
#पूर्ण_अगर
