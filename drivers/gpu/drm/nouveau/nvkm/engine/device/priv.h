<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DEVICE_PRIV_H__
#घोषणा __NVKM_DEVICE_PRIV_H__
#समावेश <core/device.h>

#समावेश <subdev/acr.h>
#समावेश <subdev/bar.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bus.h>
#समावेश <subdev/clk.h>
#समावेश <subdev/devinit.h>
#समावेश <subdev/fault.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/fuse.h>
#समावेश <subdev/gpपन.स>
#समावेश <subdev/gsp.h>
#समावेश <subdev/i2c.h>
#समावेश <subdev/iccsense.h>
#समावेश <subdev/insपंचांगem.h>
#समावेश <subdev/ltc.h>
#समावेश <subdev/mc.h>
#समावेश <subdev/mmu.h>
#समावेश <subdev/mxm.h>
#समावेश <subdev/pci.h>
#समावेश <subdev/pmu.h>
#समावेश <subdev/privring.h>
#समावेश <subdev/therm.h>
#समावेश <subdev/समयr.h>
#समावेश <subdev/top.h>
#समावेश <subdev/volt.h>

#समावेश <engine/bsp.h>
#समावेश <engine/ce.h>
#समावेश <engine/cipher.h>
#समावेश <engine/disp.h>
#समावेश <engine/dma.h>
#समावेश <engine/fअगरo.h>
#समावेश <engine/gr.h>
#समावेश <engine/mpeg.h>
#समावेश <engine/mspdec.h>
#समावेश <engine/msppp.h>
#समावेश <engine/msvld.h>
#समावेश <engine/nvenc.h>
#समावेश <engine/nvdec.h>
#समावेश <engine/pm.h>
#समावेश <engine/sec.h>
#समावेश <engine/sec2.h>
#समावेश <engine/sw.h>
#समावेश <engine/vic.h>
#समावेश <engine/vp.h>

पूर्णांक  nvkm_device_ctor(स्थिर काष्ठा nvkm_device_func *,
		      स्थिर काष्ठा nvkm_device_quirk *,
		      काष्ठा device *, क्रमागत nvkm_device_type, u64 handle,
		      स्थिर अक्षर *name, स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
		      bool detect, bool mmio, u64 subdev_mask,
		      काष्ठा nvkm_device *);
पूर्णांक  nvkm_device_init(काष्ठा nvkm_device *);
पूर्णांक  nvkm_device_fini(काष्ठा nvkm_device *, bool suspend);
#पूर्ण_अगर
