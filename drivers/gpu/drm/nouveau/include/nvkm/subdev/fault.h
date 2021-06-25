<शैली गुरु>
#अगर_अघोषित __NVKM_FAULT_H__
#घोषणा __NVKM_FAULT_H__
#समावेश <core/subdev.h>
#समावेश <core/notअगरy.h>

काष्ठा nvkm_fault अणु
	स्थिर काष्ठा nvkm_fault_func *func;
	काष्ठा nvkm_subdev subdev;

	काष्ठा nvkm_fault_buffer *buffer[2];
	पूर्णांक buffer_nr;

	काष्ठा nvkm_event event;

	काष्ठा nvkm_notअगरy nrpfb;

	काष्ठा nvkm_device_oclass user;
पूर्ण;

काष्ठा nvkm_fault_data अणु
	u64  addr;
	u64  inst;
	u64  समय;
	u8 engine;
	u8  valid;
	u8    gpc;
	u8    hub;
	u8 access;
	u8 client;
	u8 reason;
पूर्ण;

पूर्णांक gp100_fault_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fault **);
पूर्णांक gp10b_fault_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fault **);
पूर्णांक gv100_fault_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fault **);
पूर्णांक tu102_fault_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fault **);
#पूर्ण_अगर
