<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_OBJECT_H__
#घोषणा __NVIF_OBJECT_H__
#समावेश <nvअगर/os.h>

काष्ठा nvअगर_sclass अणु
	s32 oclass;
	पूर्णांक minver;
	पूर्णांक maxver;
पूर्ण;

काष्ठा nvअगर_object अणु
	काष्ठा nvअगर_parent *parent;
	काष्ठा nvअगर_client *client;
	स्थिर अक्षर *name;
	u32 handle;
	s32 oclass;
	व्योम *priv; /*XXX: hack */
	काष्ठा अणु
		व्योम __iomem *ptr;
		u64 size;
	पूर्ण map;
पूर्ण;

पूर्णांक  nvअगर_object_ctor(काष्ठा nvअगर_object *, स्थिर अक्षर *name, u32 handle,
		      s32 oclass, व्योम *, u32, काष्ठा nvअगर_object *);
व्योम nvअगर_object_dtor(काष्ठा nvअगर_object *);
पूर्णांक  nvअगर_object_ioctl(काष्ठा nvअगर_object *, व्योम *, u32, व्योम **);
पूर्णांक  nvअगर_object_sclass_get(काष्ठा nvअगर_object *, काष्ठा nvअगर_sclass **);
व्योम nvअगर_object_sclass_put(काष्ठा nvअगर_sclass **);
u32  nvअगर_object_rd(काष्ठा nvअगर_object *, पूर्णांक, u64);
व्योम nvअगर_object_wr(काष्ठा nvअगर_object *, पूर्णांक, u64, u32);
पूर्णांक  nvअगर_object_mthd(काष्ठा nvअगर_object *, u32, व्योम *, u32);
पूर्णांक  nvअगर_object_map_handle(काष्ठा nvअगर_object *, व्योम *, u32,
			    u64 *handle, u64 *length);
व्योम nvअगर_object_unmap_handle(काष्ठा nvअगर_object *);
पूर्णांक  nvअगर_object_map(काष्ठा nvअगर_object *, व्योम *, u32);
व्योम nvअगर_object_unmap(काष्ठा nvअगर_object *);

#घोषणा nvअगर_handle(a) (अचिन्हित दीर्घ)(व्योम *)(a)
#घोषणा nvअगर_object(a) (a)->object

#घोषणा nvअगर_rd(a,f,b,c) (अणु                                                    \
	काष्ठा nvअगर_object *_object = (a);                                     \
	u32 _data;                                                             \
	अगर (likely(_object->map.ptr))                                          \
		_data = f((u8 __iomem *)_object->map.ptr + (c));               \
	अन्यथा                                                                   \
		_data = nvअगर_object_rd(_object, (b), (c));                     \
	_data;                                                                 \
पूर्ण)
#घोषणा nvअगर_wr(a,f,b,c,d) (अणु                                                  \
	काष्ठा nvअगर_object *_object = (a);                                     \
	अगर (likely(_object->map.ptr))                                          \
		f((d), (u8 __iomem *)_object->map.ptr + (c));                  \
	अन्यथा                                                                   \
		nvअगर_object_wr(_object, (b), (c), (d));                        \
पूर्ण)
#घोषणा nvअगर_rd08(a,b) (अणु ((u8)nvअगर_rd((a), ioपढ़ो8, 1, (b))); पूर्ण)
#घोषणा nvअगर_rd16(a,b) (अणु ((u16)nvअगर_rd((a), ioपढ़ो16_native, 2, (b))); पूर्ण)
#घोषणा nvअगर_rd32(a,b) (अणु ((u32)nvअगर_rd((a), ioपढ़ो32_native, 4, (b))); पूर्ण)
#घोषणा nvअगर_wr08(a,b,c) nvअगर_wr((a), ioग_लिखो8, 1, (b), (u8)(c))
#घोषणा nvअगर_wr16(a,b,c) nvअगर_wr((a), ioग_लिखो16_native, 2, (b), (u16)(c))
#घोषणा nvअगर_wr32(a,b,c) nvअगर_wr((a), ioग_लिखो32_native, 4, (b), (u32)(c))
#घोषणा nvअगर_mask(a,b,c,d) (अणु                                                  \
	काष्ठा nvअगर_object *__object = (a);                                    \
	u32 _addr = (b), _data = nvअगर_rd32(__object, _addr);                   \
	nvअगर_wr32(__object, _addr, (_data & ~(c)) | (d));                      \
	_data;                                                                 \
पूर्ण)

#घोषणा nvअगर_mthd(a,b,c,d) nvअगर_object_mthd((a), (b), (c), (d))

काष्ठा nvअगर_mclass अणु
	s32 oclass;
	पूर्णांक version;
पूर्ण;

#घोषणा nvअगर_mclass(o,m) (अणु                                                    \
	काष्ठा nvअगर_object *object = (o);                                      \
	काष्ठा nvअगर_sclass *sclass;                                            \
	typeof(m[0]) *mclass = (m);                                            \
	पूर्णांक ret = -ENODEV;                                                     \
	पूर्णांक cnt, i, j;                                                         \
                                                                               \
	cnt = nvअगर_object_sclass_get(object, &sclass);                         \
	अगर (cnt >= 0) अणु                                                        \
		क्रम (i = 0; ret < 0 && mclass[i].oclass; i++) अणु                \
			क्रम (j = 0; j < cnt; j++) अणु                            \
				अगर (mclass[i].oclass  == sclass[j].oclass &&   \
				    mclass[i].version >= sclass[j].minver &&   \
				    mclass[i].version <= sclass[j].maxver) अणु   \
					ret = i;                               \
					अवरोध;                                 \
				पूर्ण                                              \
			पूर्ण                                                      \
		पूर्ण                                                              \
		nvअगर_object_sclass_put(&sclass);                               \
	पूर्ण                                                                      \
	ret;                                                                   \
पूर्ण)

#घोषणा nvअगर_sclass(o,m,u) (अणु                                                  \
	स्थिर typeof(m[0]) *_mclass = (m);                                     \
	s32 _oclass = (u);                                                     \
	पूर्णांक _cid;                                                              \
	अगर (_oclass) अणु                                                         \
		क्रम (_cid = 0; _mclass[_cid].oclass; _cid++) अणु                 \
			अगर (_mclass[_cid].oclass == _oclass)                   \
				अवरोध;                                         \
		पूर्ण                                                              \
		_cid = _mclass[_cid].oclass ? _cid : -ENOSYS;                  \
	पूर्ण अन्यथा अणु                                                               \
		_cid = nvअगर_mclass((o), _mclass);                              \
	पूर्ण                                                                      \
	_cid;                                                                  \
पूर्ण)

#घोषणा NVIF_RD32_(p,o,dr)   nvअगर_rd32((p), (o) + (dr))
#घोषणा NVIF_WR32_(p,o,dr,f) nvअगर_wr32((p), (o) + (dr), (f))
#घोषणा NVIF_RD32(p,A...) DRF_RD(NVIF_RD32_,                  (p), 0, ##A)
#घोषणा NVIF_RV32(p,A...) DRF_RV(NVIF_RD32_,                  (p), 0, ##A)
#घोषणा NVIF_TV32(p,A...) DRF_TV(NVIF_RD32_,                  (p), 0, ##A)
#घोषणा NVIF_TD32(p,A...) DRF_TD(NVIF_RD32_,                  (p), 0, ##A)
#घोषणा NVIF_WR32(p,A...) DRF_WR(            NVIF_WR32_,      (p), 0, ##A)
#घोषणा NVIF_WV32(p,A...) DRF_WV(            NVIF_WR32_,      (p), 0, ##A)
#घोषणा NVIF_WD32(p,A...) DRF_WD(            NVIF_WR32_,      (p), 0, ##A)
#घोषणा NVIF_MR32(p,A...) DRF_MR(NVIF_RD32_, NVIF_WR32_, u32, (p), 0, ##A)
#घोषणा NVIF_MV32(p,A...) DRF_MV(NVIF_RD32_, NVIF_WR32_, u32, (p), 0, ##A)
#घोषणा NVIF_MD32(p,A...) DRF_MD(NVIF_RD32_, NVIF_WR32_, u32, (p), 0, ##A)

/*XXX*/
#समावेश <core/object.h>
#घोषणा nvxx_object(a) (अणु                                                      \
	काष्ठा nvअगर_object *_object = (a);                                     \
	(काष्ठा nvkm_object *)_object->priv;                                   \
पूर्ण)
#पूर्ण_अगर
