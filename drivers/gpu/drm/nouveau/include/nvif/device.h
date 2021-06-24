<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_DEVICE_H__
#घोषणा __NVIF_DEVICE_H__

#समावेश <nvअगर/object.h>
#समावेश <nvअगर/cl0080.h>
#समावेश <nvअगर/user.h>

काष्ठा nvअगर_device अणु
	काष्ठा nvअगर_object object;
	काष्ठा nv_device_info_v0 info;

	काष्ठा nvअगर_fअगरo_runlist अणु
		u64 engines;
	पूर्ण *runlist;
	पूर्णांक runlists;

	काष्ठा nvअगर_user user;
पूर्ण;

पूर्णांक  nvअगर_device_ctor(काष्ठा nvअगर_object *, स्थिर अक्षर *name, u32 handle,
		      s32 oclass, व्योम *, u32, काष्ठा nvअगर_device *);
व्योम nvअगर_device_dtor(काष्ठा nvअगर_device *);
u64  nvअगर_device_समय(काष्ठा nvअगर_device *);

/*XXX*/
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/fb.h>
#समावेश <subdev/bar.h>
#समावेश <subdev/gpपन.स>
#समावेश <subdev/clk.h>
#समावेश <subdev/i2c.h>
#समावेश <subdev/समयr.h>
#समावेश <subdev/therm.h>
#समावेश <subdev/pci.h>

#घोषणा nvxx_device(a) (अणु                                                      \
	काष्ठा nvअगर_device *_device = (a);                                     \
	काष्ठा अणु                                                               \
		काष्ठा nvkm_object object;                                     \
		काष्ठा nvkm_device *device;                                    \
	पूर्ण *_udevice = _device->object.priv;                                    \
	_udevice->device;                                                      \
पूर्ण)
#घोषणा nvxx_bios(a) nvxx_device(a)->bios
#घोषणा nvxx_fb(a) nvxx_device(a)->fb
#घोषणा nvxx_gpio(a) nvxx_device(a)->gpio
#घोषणा nvxx_clk(a) nvxx_device(a)->clk
#घोषणा nvxx_i2c(a) nvxx_device(a)->i2c
#घोषणा nvxx_iccsense(a) nvxx_device(a)->iccsense
#घोषणा nvxx_therm(a) nvxx_device(a)->therm
#घोषणा nvxx_volt(a) nvxx_device(a)->volt

#समावेश <engine/fअगरo.h>
#समावेश <engine/gr.h>

#घोषणा nvxx_gr(a) nvxx_device(a)->gr
#पूर्ण_अगर
