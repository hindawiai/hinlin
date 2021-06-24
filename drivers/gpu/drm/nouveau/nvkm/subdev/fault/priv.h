<शैली गुरु>
#अगर_अघोषित __NVKM_FAULT_PRIV_H__
#घोषणा __NVKM_FAULT_PRIV_H__
#घोषणा nvkm_fault_buffer(p) container_of((p), काष्ठा nvkm_fault_buffer, object)
#घोषणा nvkm_fault(p) container_of((p), काष्ठा nvkm_fault, subdev)
#समावेश <subdev/fault.h>

#समावेश <core/event.h>
#समावेश <core/object.h>

काष्ठा nvkm_fault_buffer अणु
	काष्ठा nvkm_object object;
	काष्ठा nvkm_fault *fault;
	पूर्णांक id;
	पूर्णांक entries;
	u32 get;
	u32 put;
	काष्ठा nvkm_memory *mem;
	u64 addr;
पूर्ण;

पूर्णांक nvkm_fault_new_(स्थिर काष्ठा nvkm_fault_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		    पूर्णांक inst, काष्ठा nvkm_fault **);

काष्ठा nvkm_fault_func अणु
	पूर्णांक (*oneinit)(काष्ठा nvkm_fault *);
	व्योम (*init)(काष्ठा nvkm_fault *);
	व्योम (*fini)(काष्ठा nvkm_fault *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_fault *);
	काष्ठा अणु
		पूर्णांक nr;
		u32 entry_size;
		व्योम (*info)(काष्ठा nvkm_fault_buffer *);
		u64 (*pin)(काष्ठा nvkm_fault_buffer *);
		व्योम (*init)(काष्ठा nvkm_fault_buffer *);
		व्योम (*fini)(काष्ठा nvkm_fault_buffer *);
		व्योम (*पूर्णांकr)(काष्ठा nvkm_fault_buffer *, bool enable);
	पूर्ण buffer;
	काष्ठा अणु
		काष्ठा nvkm_sclass base;
		पूर्णांक rp;
	पूर्ण user;
पूर्ण;

व्योम gp100_fault_buffer_पूर्णांकr(काष्ठा nvkm_fault_buffer *, bool enable);
व्योम gp100_fault_buffer_fini(काष्ठा nvkm_fault_buffer *);
व्योम gp100_fault_buffer_init(काष्ठा nvkm_fault_buffer *);
u64 gp100_fault_buffer_pin(काष्ठा nvkm_fault_buffer *);
व्योम gp100_fault_buffer_info(काष्ठा nvkm_fault_buffer *);
व्योम gp100_fault_पूर्णांकr(काष्ठा nvkm_fault *);

u64 gp10b_fault_buffer_pin(काष्ठा nvkm_fault_buffer *);

पूर्णांक gv100_fault_oneinit(काष्ठा nvkm_fault *);

पूर्णांक nvkm_ufault_new(काष्ठा nvkm_device *, स्थिर काष्ठा nvkm_oclass *,
		    व्योम *, u32, काष्ठा nvkm_object **);
#पूर्ण_अगर
