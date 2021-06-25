<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"
#समावेश "acpi.h"

#समावेश <core/notअगरy.h>
#समावेश <core/option.h>

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/therm.h>

अटल DEFINE_MUTEX(nv_devices_mutex);
अटल LIST_HEAD(nv_devices);

अटल काष्ठा nvkm_device *
nvkm_device_find_locked(u64 handle)
अणु
	काष्ठा nvkm_device *device;
	list_क्रम_each_entry(device, &nv_devices, head) अणु
		अगर (device->handle == handle)
			वापस device;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा nvkm_device *
nvkm_device_find(u64 handle)
अणु
	काष्ठा nvkm_device *device;
	mutex_lock(&nv_devices_mutex);
	device = nvkm_device_find_locked(handle);
	mutex_unlock(&nv_devices_mutex);
	वापस device;
पूर्ण

पूर्णांक
nvkm_device_list(u64 *name, पूर्णांक size)
अणु
	काष्ठा nvkm_device *device;
	पूर्णांक nr = 0;
	mutex_lock(&nv_devices_mutex);
	list_क्रम_each_entry(device, &nv_devices, head) अणु
		अगर (nr++ < size)
			name[nr - 1] = device->handle;
	पूर्ण
	mutex_unlock(&nv_devices_mutex);
	वापस nr;
पूर्ण

अटल स्थिर काष्ठा nvkm_device_chip
null_chipset = अणु
	.name = "NULL",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv4_chipset = अणु
	.name = "NV04",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv04_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv04_fb_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv04_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv04_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv04_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv04_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv5_chipset = अणु
	.name = "NV05",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv05_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv04_fb_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv04_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv04_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv04_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv04_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv10_chipset = अणु
	.name = "NV10",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv10_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv10_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv04_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.gr       = अणु 0x00000001, nv10_gr_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv11_chipset = अणु
	.name = "NV11",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv10_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv10_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv11_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv10_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv15_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv15_chipset = अणु
	.name = "NV15",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv10_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv10_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv04_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv10_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv15_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv17_chipset = अणु
	.name = "NV17",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv10_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv10_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv17_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv18_chipset = अणु
	.name = "NV18",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv10_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv10_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv17_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv1a_chipset = अणु
	.name = "nForce",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv1a_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv04_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv10_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv15_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv1f_chipset = अणु
	.name = "nForce2",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv1a_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv17_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv20_chipset = अणु
	.name = "NV20",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv20_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv20_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv25_chipset = अणु
	.name = "NV25",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv25_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv25_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv28_chipset = अणु
	.name = "NV28",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv25_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv25_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv2a_chipset = अणु
	.name = "NV2A",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv25_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv2a_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv30_chipset = अणु
	.name = "NV30",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv30_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv30_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv31_chipset = अणु
	.name = "NV31",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv30_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv30_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv31_mpeg_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv34_chipset = अणु
	.name = "NV34",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv10_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv10_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv34_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv31_mpeg_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv35_chipset = अणु
	.name = "NV35",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv04_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv35_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv35_gr_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv36_chipset = अणु
	.name = "NV36",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv04_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv20_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv36_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv04_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv04_pci_new पूर्ण,
	.समयr    = अणु 0x00000001, nv04_समयr_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv17_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv35_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv31_mpeg_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv40_chipset = अणु
	.name = "NV40",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv40_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv40_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv40_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv41_chipset = अणु
	.name = "NV41",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv41_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv41_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv40_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv42_chipset = अणु
	.name = "NV42",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv41_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv41_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv40_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv43_chipset = अणु
	.name = "NV43",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv41_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv41_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv40_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv44_chipset = अणु
	.name = "NV44",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv44_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv44_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv45_chipset = अणु
	.name = "NV45",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv40_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv46_chipset = अणु
	.name = "G72",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv46_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv44_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv46_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv47_chipset = अणु
	.name = "G70",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv47_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv41_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv49_chipset = अणु
	.name = "G71",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv49_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv41_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv4a_chipset = अणु
	.name = "NV44A",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv44_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv04_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv4b_chipset = अणु
	.name = "G73",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv49_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv17_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv41_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv40_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv40_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv4c_chipset = अणु
	.name = "C61",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv46_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv44_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv4c_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv4e_chipset = अणु
	.name = "C51",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv4e_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv4e_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv44_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv4c_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv50_chipset = अणु
	.name = "G80",
	.bar      = अणु 0x00000001, nv50_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv50_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv50_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv50_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv50_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, nv50_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv50_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv50_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv50_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, nv46_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv50_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv50_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv50_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv50_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv50_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv50_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv63_chipset = अणु
	.name = "C73",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv46_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv44_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv4c_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv67_chipset = अणु
	.name = "C67",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv46_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv44_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv4c_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv68_chipset = अणु
	.name = "C68",
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv31_bus_new पूर्ण,
	.clk      = अणु 0x00000001, nv40_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, nv1a_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, nv46_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, nv10_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv04_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv40_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, nv44_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, nv44_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, nv4c_pci_new पूर्ण,
	.therm    = अणु 0x00000001, nv40_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, nv04_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv04_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, nv40_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, nv44_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, nv44_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, nv40_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv10_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv84_chipset = अणु
	.name = "G84",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv50_bus_new पूर्ण,
	.clk      = अणु 0x00000001, g84_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g84_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, g84_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, nv50_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv50_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g84_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g84_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.bsp      = अणु 0x00000001, g84_bsp_new पूर्ण,
	.cipher   = अणु 0x00000001, g84_cipher_new पूर्ण,
	.disp     = अणु 0x00000001, g84_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, g84_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, g84_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
	.vp       = अणु 0x00000001, g84_vp_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv86_chipset = अणु
	.name = "G86",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv50_bus_new पूर्ण,
	.clk      = अणु 0x00000001, g84_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g84_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, g84_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, nv50_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv50_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g84_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g84_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.bsp      = अणु 0x00000001, g84_bsp_new पूर्ण,
	.cipher   = अणु 0x00000001, g84_cipher_new पूर्ण,
	.disp     = अणु 0x00000001, g84_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, g84_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, g84_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
	.vp       = अणु 0x00000001, g84_vp_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv92_chipset = अणु
	.name = "G92",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, nv50_bus_new पूर्ण,
	.clk      = अणु 0x00000001, g84_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g84_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, g84_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, nv50_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv50_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g84_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g92_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.bsp      = अणु 0x00000001, g84_bsp_new पूर्ण,
	.cipher   = अणु 0x00000001, g84_cipher_new पूर्ण,
	.disp     = अणु 0x00000001, g84_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, g84_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, g84_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
	.vp       = अणु 0x00000001, g84_vp_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv94_chipset = अणु
	.name = "G94",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, g84_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g84_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, g84_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g84_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.bsp      = अणु 0x00000001, g84_bsp_new पूर्ण,
	.cipher   = अणु 0x00000001, g84_cipher_new पूर्ण,
	.disp     = अणु 0x00000001, g94_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, g84_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, g84_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
	.vp       = अणु 0x00000001, g84_vp_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv96_chipset = अणु
	.name = "G96",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, g84_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g84_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, g84_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g84_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.bsp      = अणु 0x00000001, g84_bsp_new पूर्ण,
	.cipher   = अणु 0x00000001, g84_cipher_new पूर्ण,
	.disp     = अणु 0x00000001, g94_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, g84_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, g84_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
	.vp       = अणु 0x00000001, g84_vp_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv98_chipset = अणु
	.name = "G98",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, g84_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g98_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, g84_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g98_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, g94_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, g84_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, g98_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, g98_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, g98_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sec      = अणु 0x00000001, g98_sec_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nva0_chipset = अणु
	.name = "GT200",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, g84_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g84_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, g84_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, nv50_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g84_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.bsp      = अणु 0x00000001, g84_bsp_new पूर्ण,
	.cipher   = अणु 0x00000001, g84_cipher_new पूर्ण,
	.disp     = अणु 0x00000001, gt200_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gt200_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, g84_mpeg_new पूर्ण,
	.pm       = अणु 0x00000001, gt200_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
	.vp       = अणु 0x00000001, g84_vp_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nva3_chipset = अणु
	.name = "GT215",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gt215_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gt215_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gt215_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, gt215_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gt215_pmu_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gt215_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gt215_gr_new पूर्ण,
	.mpeg     = अणु 0x00000001, g84_mpeg_new पूर्ण,
	.mspdec   = अणु 0x00000001, gt215_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gt215_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gt215_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gt215_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nva5_chipset = अणु
	.name = "GT216",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gt215_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gt215_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gt215_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, gt215_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gt215_pmu_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gt215_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gt215_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gt215_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gt215_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gt215_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gt215_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nva8_chipset = अणु
	.name = "GT218",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gt215_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gt215_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gt215_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, gt215_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, g84_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gt215_pmu_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gt215_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gt215_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gt215_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gt215_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gt215_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gt215_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvaa_chipset = अणु
	.name = "MCP77/MCP78",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, mcp77_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g98_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, mcp77_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g98_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, mcp77_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, mcp77_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gt200_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, g98_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, g98_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, g98_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sec      = अणु 0x00000001, g98_sec_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvac_chipset = अणु
	.name = "MCP79/MCP7A",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, mcp77_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, g98_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, mcp77_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, g98_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, mcp77_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.therm    = अणु 0x00000001, g84_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.disp     = अणु 0x00000001, mcp77_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, mcp79_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, g98_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, g98_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, g98_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, g84_pm_new पूर्ण,
	.sec      = अणु 0x00000001, g98_sec_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvaf_chipset = अणु
	.name = "MCP89",
	.bar      = अणु 0x00000001, g84_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, g94_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gt215_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, mcp89_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, mcp89_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, nv50_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, gt215_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, mcp77_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, g94_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gt215_pmu_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, nv40_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gt215_ce_new पूर्ण,
	.disp     = अणु 0x00000001, mcp89_disp_new पूर्ण,
	.dma      = अणु 0x00000001, nv50_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, g84_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, mcp89_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gt215_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gt215_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, mcp89_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gt215_pm_new पूर्ण,
	.sw       = अणु 0x00000001, nv50_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvc0_chipset = अणु
	.name = "GF100",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf100_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf100_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000003, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf100_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf100_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvc1_chipset = अणु
	.name = "GF108",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf108_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf106_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf100_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf100_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf108_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf108_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvc3_chipset = अणु
	.name = "GF106",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf106_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf100_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf100_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf104_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf100_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvc4_chipset = अणु
	.name = "GF104",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf100_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf100_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000003, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf104_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf100_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvc8_chipset = अणु
	.name = "GF110",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf100_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf100_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000003, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf110_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf100_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvce_chipset = अणु
	.name = "GF114",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf100_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf100_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000003, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf104_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf100_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvcf_chipset = अणु
	.name = "GF116",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, g94_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, g94_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf106_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf100_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf100_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gt215_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gt215_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf104_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf100_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvd7_chipset = अणु
	.name = "GF117",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gf119_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gf117_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf106_pci_new पूर्ण,
	.privring = अणु 0x00000001, gf117_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gf119_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf117_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gf119_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf117_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf117_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvd9_chipset = अणु
	.name = "GF119",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gf100_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gf100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gf119_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gf119_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gf100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gf100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gf100_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gf106_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gf119_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gf117_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gf119_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.volt     = अणु 0x00000001, gf100_volt_new पूर्ण,
	.ce       = अणु 0x00000001, gf100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gf119_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gf100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gf119_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gf100_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gf100_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gf117_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nve4_chipset = अणु
	.name = "GK104",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gk104_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk104_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk104_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gk104_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gk104_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gk104_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gk104_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk104_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk104_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gk104_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gk104_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gk104_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nve6_chipset = अणु
	.name = "GK106",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gk104_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk104_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk104_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gk104_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gk104_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gk104_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gk104_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk104_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk104_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gk104_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gk104_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gk104_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nve7_chipset = अणु
	.name = "GK107",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gk104_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk104_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk104_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gk104_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gk104_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gk104_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gk104_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk104_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk104_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gk104_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gk104_msvld_new पूर्ण,
	.pm       = अणु 0x00000001, gk104_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvea_chipset = अणु
	.name = "GK20A",
	.bar      = अणु 0x00000001, gk20a_bar_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk20a_clk_new पूर्ण,
	.fb       = अणु 0x00000001, gk20a_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.imem     = अणु 0x00000001, gk20a_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk20a_mmu_new पूर्ण,
	.pmu      = अणु 0x00000001, gk20a_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk20a_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk20a_volt_new पूर्ण,
	.ce       = अणु 0x00000004, gk104_ce_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk20a_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk20a_gr_new पूर्ण,
	.pm       = अणु 0x00000001, gk104_pm_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvf0_chipset = अणु
	.name = "GK110",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gk110_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk110_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk104_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gk110_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gk104_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gk104_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gk110_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk110_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk110_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gk104_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gk104_msvld_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nvf1_chipset = अणु
	.name = "GK110B",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gk110_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk110_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk104_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gk110_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gk104_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gk104_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gk110_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk110_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk110b_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gk104_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gk104_msvld_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv106_chipset = अणु
	.name = "GK208B",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gk110_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk110_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gk208_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gk104_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gk104_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gk110_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk208_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk208_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gk104_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gk104_msvld_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv108_chipset = अणु
	.name = "GK208",
	.bar      = अणु 0x00000001, gf100_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gf100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gk110_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gf100_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk110_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gk104_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gk208_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gk104_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, nv41_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gk104_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gk110_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gk208_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gk208_gr_new पूर्ण,
	.mspdec   = अणु 0x00000001, gk104_mspdec_new पूर्ण,
	.msppp    = अणु 0x00000001, gf100_msppp_new पूर्ण,
	.msvld    = अणु 0x00000001, gk104_msvld_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv117_chipset = अणु
	.name = "GM107",
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gm107_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gm107_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk110_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gm107_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gm107_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gm107_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000005, gm107_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gm107_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gm107_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gm107_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv118_chipset = अणु
	.name = "GM108",
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gk104_clk_new पूर्ण,
	.devinit  = अणु 0x00000001, gm107_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gm107_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gk110_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gm107_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gk104_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gm107_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk104_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gm107_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000005, gm107_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gm107_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gm107_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gm107_gr_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv120_chipset = अणु
	.name = "GM200",
	.acr      = अणु 0x00000001, gm200_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gm200_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gm200_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gm200_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gm200_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gm200_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gm200_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gm200_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gm200_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gm200_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000003, gm107_nvenc_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv124_chipset = अणु
	.name = "GM204",
	.acr      = अणु 0x00000001, gm200_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gm200_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gm200_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gm200_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gm200_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gm200_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gm200_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gm200_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gm200_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gm200_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000003, gm107_nvenc_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv126_chipset = अणु
	.name = "GM206",
	.acr      = अणु 0x00000001, gm200_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, gm200_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.iccsense = अणु 0x00000001, gf100_iccsense_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gm200_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gm200_mmu_new पूर्ण,
	.mxm      = अणु 0x00000001, nv50_mxm_new पूर्ण,
	.pci      = अणु 0x00000001, gk104_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gm200_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gm200_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gk104_volt_new पूर्ण,
	.ce       = अणु 0x00000007, gm200_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gm200_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gm200_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gm200_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv12b_chipset = अणु
	.name = "GM20B",
	.acr      = अणु 0x00000001, gm20b_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm20b_bar_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.clk      = अणु 0x00000001, gm20b_clk_new पूर्ण,
	.fb       = अणु 0x00000001, gm20b_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.imem     = अणु 0x00000001, gk20a_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gm200_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gk20a_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gm20b_mmu_new पूर्ण,
	.pmu      = अणु 0x00000001, gm20b_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gk20a_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.volt     = अणु 0x00000001, gm20b_volt_new पूर्ण,
	.ce       = अणु 0x00000004, gm200_ce_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gm20b_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gm20b_gr_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv130_chipset = अणु
	.name = "GP100",
	.acr      = अणु 0x00000001, gm200_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, gp100_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gp100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp100_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gp100_mmu_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gm200_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000003f, gp100_ce_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.disp     = अणु 0x00000001, gp100_disp_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gp100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gp100_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000007, gm107_nvenc_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv132_chipset = अणु
	.name = "GP102",
	.acr      = अणु 0x00000001, gp102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, gp100_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gp102_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gp100_mmu_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000000f, gp102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gp102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gp100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gp102_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000003, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, gp102_sec2_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv134_chipset = अणु
	.name = "GP104",
	.acr      = अणु 0x00000001, gp102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, gp100_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gp102_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gp100_mmu_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000000f, gp102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gp102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gp100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gp104_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000003, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, gp102_sec2_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv136_chipset = अणु
	.name = "GP106",
	.acr      = अणु 0x00000001, gp102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, gp100_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gp102_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gp100_mmu_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000000f, gp102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gp102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gp100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gp104_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, gp102_sec2_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv137_chipset = अणु
	.name = "GP107",
	.acr      = अणु 0x00000001, gp102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, gp100_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gp102_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gp100_mmu_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000000f, gp102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gp102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gp100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gp107_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000003, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, gp102_sec2_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv138_chipset = अणु
	.name = "GP108",
	.acr      = अणु 0x00000001, gp108_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gm200_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, gp100_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gp102_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gp100_mmu_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000000f, gp102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gp102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gp100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gp108_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.sec2     = अणु 0x00000001, gp108_sec2_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv13b_chipset = अणु
	.name = "GP10B",
	.acr      = अणु 0x00000001, gp10b_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm20b_bar_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.fault    = अणु 0x00000001, gp10b_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gp10b_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.imem     = अणु 0x00000001, gk20a_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp10b_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp10b_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gp10b_mmu_new पूर्ण,
	.pmu      = अणु 0x00000001, gp10b_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gp10b_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x00000001, gp100_ce_new पूर्ण,
	.dma      = अणु 0x00000001, gf119_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gp10b_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gp10b_gr_new पूर्ण,
	.sw       = अणु 0x00000001, gf100_sw_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv140_chipset = अणु
	.name = "GV100",
	.acr      = अणु 0x00000001, gp108_acr_new पूर्ण,
	.bar      = अणु 0x00000001, gm107_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, gv100_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, gv100_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gv100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.gsp      = अणु 0x00000001, gv100_gsp_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, gp100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, gv100_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x000001ff, gv100_ce_new पूर्ण,
	.disp     = अणु 0x00000001, gv100_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, gv100_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, gv100_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000007, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, gp108_sec2_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv162_chipset = अणु
	.name = "TU102",
	.acr      = अणु 0x00000001, tu102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, tu102_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, tu102_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gv100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.gsp      = अणु 0x00000001, gv100_gsp_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, tu102_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000001f, tu102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, tu102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, tu102_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, tu102_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, tu102_sec2_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv164_chipset = अणु
	.name = "TU104",
	.acr      = अणु 0x00000001, tu102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, tu102_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, tu102_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gv100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.gsp      = अणु 0x00000001, gv100_gsp_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, tu102_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000001f, tu102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, tu102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, tu102_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, tu102_gr_new पूर्ण,
	.nvdec    = अणु 0x00000003, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, tu102_sec2_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv166_chipset = अणु
	.name = "TU106",
	.acr      = अणु 0x00000001, tu102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, tu102_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, tu102_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gv100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.gsp      = अणु 0x00000001, gv100_gsp_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, tu102_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000001f, tu102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, tu102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, tu102_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, tu102_gr_new पूर्ण,
	.nvdec    = अणु 0x00000007, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, tu102_sec2_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv167_chipset = अणु
	.name = "TU117",
	.acr      = अणु 0x00000001, tu102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, tu102_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, tu102_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gv100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.gsp      = अणु 0x00000001, gv100_gsp_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, tu102_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000001f, tu102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, tu102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, tu102_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, tu102_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, tu102_sec2_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv168_chipset = अणु
	.name = "TU116",
	.acr      = अणु 0x00000001, tu102_acr_new पूर्ण,
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.bus      = अणु 0x00000001, gf100_bus_new पूर्ण,
	.devinit  = अणु 0x00000001, tu102_devinit_new पूर्ण,
	.fault    = अणु 0x00000001, tu102_fault_new पूर्ण,
	.fb       = अणु 0x00000001, gv100_fb_new पूर्ण,
	.fuse     = अणु 0x00000001, gm107_fuse_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.gsp      = अणु 0x00000001, gv100_gsp_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.ltc      = अणु 0x00000001, gp102_ltc_new पूर्ण,
	.mc       = अणु 0x00000001, tu102_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.pmu      = अणु 0x00000001, gp102_pmu_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.therm    = अणु 0x00000001, gp100_therm_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, gk104_top_new पूर्ण,
	.ce       = अणु 0x0000001f, tu102_ce_new पूर्ण,
	.disp     = अणु 0x00000001, tu102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
	.fअगरo     = अणु 0x00000001, tu102_fअगरo_new पूर्ण,
	.gr       = अणु 0x00000001, tu102_gr_new पूर्ण,
	.nvdec    = अणु 0x00000001, gm107_nvdec_new पूर्ण,
	.nvenc    = अणु 0x00000001, gm107_nvenc_new पूर्ण,
	.sec2     = अणु 0x00000001, tu102_sec2_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv170_chipset = अणु
	.name = "GA100",
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.devinit  = अणु 0x00000001, ga100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, ga100_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, gk104_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, ga100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, ga100_top_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv172_chipset = अणु
	.name = "GA102",
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.devinit  = अणु 0x00000001, ga100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, ga102_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, ga102_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, ga100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, ga100_top_new पूर्ण,
	.disp     = अणु 0x00000001, ga102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_chip
nv174_chipset = अणु
	.name = "GA104",
	.bar      = अणु 0x00000001, tu102_bar_new पूर्ण,
	.bios     = अणु 0x00000001, nvkm_bios_new पूर्ण,
	.devinit  = अणु 0x00000001, ga100_devinit_new पूर्ण,
	.fb       = अणु 0x00000001, ga102_fb_new पूर्ण,
	.gpio     = अणु 0x00000001, ga102_gpio_new पूर्ण,
	.i2c      = अणु 0x00000001, gm200_i2c_new पूर्ण,
	.imem     = अणु 0x00000001, nv50_insपंचांगem_new पूर्ण,
	.mc       = अणु 0x00000001, ga100_mc_new पूर्ण,
	.mmu      = अणु 0x00000001, tu102_mmu_new पूर्ण,
	.pci      = अणु 0x00000001, gp100_pci_new पूर्ण,
	.privring = अणु 0x00000001, gm200_privring_new पूर्ण,
	.समयr    = अणु 0x00000001, gk20a_समयr_new पूर्ण,
	.top      = अणु 0x00000001, ga100_top_new पूर्ण,
	.disp     = अणु 0x00000001, ga102_disp_new पूर्ण,
	.dma      = अणु 0x00000001, gv100_dma_new पूर्ण,
पूर्ण;

अटल पूर्णांक
nvkm_device_event_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		       काष्ठा nvkm_notअगरy *notअगरy)
अणु
	अगर (!WARN_ON(size != 0)) अणु
		notअगरy->size  = 0;
		notअगरy->types = 1;
		notअगरy->index = 0;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_device_event_func = अणु
	.ctor = nvkm_device_event_ctor,
पूर्ण;

काष्ठा nvkm_subdev *
nvkm_device_subdev(काष्ठा nvkm_device *device, पूर्णांक type, पूर्णांक inst)
अणु
	काष्ठा nvkm_subdev *subdev;

	list_क्रम_each_entry(subdev, &device->subdev, head) अणु
		अगर (subdev->type == type && subdev->inst == inst)
			वापस subdev;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा nvkm_engine *
nvkm_device_engine(काष्ठा nvkm_device *device, पूर्णांक type, पूर्णांक inst)
अणु
	काष्ठा nvkm_subdev *subdev = nvkm_device_subdev(device, type, inst);
	अगर (subdev && subdev->func == &nvkm_engine)
		वापस container_of(subdev, काष्ठा nvkm_engine, subdev);
	वापस शून्य;
पूर्ण

पूर्णांक
nvkm_device_fini(काष्ठा nvkm_device *device, bool suspend)
अणु
	स्थिर अक्षर *action = suspend ? "suspend" : "fini";
	काष्ठा nvkm_subdev *subdev;
	पूर्णांक ret;
	s64 समय;

	nvdev_trace(device, "%s running...\n", action);
	समय = kसमय_प्रकारo_us(kसमय_get());

	nvkm_acpi_fini(device);

	list_क्रम_each_entry_reverse(subdev, &device->subdev, head) अणु
		ret = nvkm_subdev_fini(subdev, suspend);
		अगर (ret && suspend)
			जाओ fail;
	पूर्ण

	nvkm_therm_clkgate_fini(device->therm, suspend);

	अगर (device->func->fini)
		device->func->fini(device, suspend);

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvdev_trace(device, "%s completed in %lldus...\n", action, समय);
	वापस 0;

fail:
	list_क्रम_each_entry_from(subdev, &device->subdev, head) अणु
		पूर्णांक rret = nvkm_subdev_init(subdev);
		अगर (rret)
			nvkm_fatal(subdev, "failed restart, %d\n", ret);
	पूर्ण

	nvdev_trace(device, "%s failed with %d\n", action, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_device_preinit(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_subdev *subdev;
	पूर्णांक ret;
	s64 समय;

	nvdev_trace(device, "preinit running...\n");
	समय = kसमय_प्रकारo_us(kसमय_get());

	अगर (device->func->preinit) अणु
		ret = device->func->preinit(device);
		अगर (ret)
			जाओ fail;
	पूर्ण

	list_क्रम_each_entry(subdev, &device->subdev, head) अणु
		ret = nvkm_subdev_preinit(subdev);
		अगर (ret)
			जाओ fail;
	पूर्ण

	ret = nvkm_devinit_post(device->devinit);
	अगर (ret)
		जाओ fail;

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvdev_trace(device, "preinit completed in %lldus\n", समय);
	वापस 0;

fail:
	nvdev_error(device, "preinit failed with %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक
nvkm_device_init(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_subdev *subdev;
	पूर्णांक ret;
	s64 समय;

	ret = nvkm_device_preinit(device);
	अगर (ret)
		वापस ret;

	nvkm_device_fini(device, false);

	nvdev_trace(device, "init running...\n");
	समय = kसमय_प्रकारo_us(kसमय_get());

	अगर (device->func->init) अणु
		ret = device->func->init(device);
		अगर (ret)
			जाओ fail;
	पूर्ण

	list_क्रम_each_entry(subdev, &device->subdev, head) अणु
		ret = nvkm_subdev_init(subdev);
		अगर (ret)
			जाओ fail_subdev;
	पूर्ण

	nvkm_acpi_init(device);
	nvkm_therm_clkgate_enable(device->therm);

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvdev_trace(device, "init completed in %lldus\n", समय);
	वापस 0;

fail_subdev:
	list_क्रम_each_entry_from(subdev, &device->subdev, head)
		nvkm_subdev_fini(subdev, false);
fail:
	nvkm_device_fini(device, false);

	nvdev_error(device, "init failed with %d\n", ret);
	वापस ret;
पूर्ण

व्योम
nvkm_device_del(काष्ठा nvkm_device **pdevice)
अणु
	काष्ठा nvkm_device *device = *pdevice;
	काष्ठा nvkm_subdev *subdev, *subपंचांगp;
	अगर (device) अणु
		mutex_lock(&nv_devices_mutex);

		list_क्रम_each_entry_safe_reverse(subdev, subपंचांगp, &device->subdev, head)
			nvkm_subdev_del(&subdev);

		nvkm_event_fini(&device->event);

		अगर (device->pri)
			iounmap(device->pri);
		list_del(&device->head);

		अगर (device->func->dtor)
			*pdevice = device->func->dtor(device);
		mutex_unlock(&nv_devices_mutex);

		kमुक्त(*pdevice);
		*pdevice = शून्य;
	पूर्ण
पूर्ण

/* वापसs true अगर the GPU is in the CPU native byte order */
अटल अंतरभूत bool
nvkm_device_endianness(काष्ठा nvkm_device *device)
अणु
#अगर_घोषित __BIG_ENDIAN
	स्थिर bool big_endian = true;
#अन्यथा
	स्थिर bool big_endian = false;
#पूर्ण_अगर

	/* Read NV_PMC_BOOT_1, and assume non-functional endian चयन अगर it
	 * करोesn't contain the expected values.
	 */
	u32 pmc_boot_1 = nvkm_rd32(device, 0x000004);
	अगर (pmc_boot_1 && pmc_boot_1 != 0x01000001)
		वापस !big_endian; /* Assume GPU is LE in this हाल. */

	/* 0 means LE and 0x01000001 means BE GPU. Condition is true when
	 * GPU/CPU endianness करोn't match.
	 */
	अगर (big_endian == !pmc_boot_1) अणु
		nvkm_wr32(device, 0x000004, 0x01000001);
		nvkm_rd32(device, 0x000000);
		अगर (nvkm_rd32(device, 0x000004) != (big_endian ? 0x01000001 : 0x00000000))
			वापस !big_endian; /* Assume GPU is LE on any unexpected पढ़ो-back. */
	पूर्ण

	/* CPU/GPU endianness should (hopefully) match. */
	वापस true;
पूर्ण

पूर्णांक
nvkm_device_ctor(स्थिर काष्ठा nvkm_device_func *func,
		 स्थिर काष्ठा nvkm_device_quirk *quirk,
		 काष्ठा device *dev, क्रमागत nvkm_device_type type, u64 handle,
		 स्थिर अक्षर *name, स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
		 bool detect, bool mmio, u64 subdev_mask,
		 काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_subdev *subdev;
	u64 mmio_base, mmio_size;
	u32 boot0, boot1, strap;
	पूर्णांक ret = -EEXIST, j;
	अचिन्हित chipset;

	mutex_lock(&nv_devices_mutex);
	अगर (nvkm_device_find_locked(handle))
		जाओ करोne;

	device->func = func;
	device->quirk = quirk;
	device->dev = dev;
	device->type = type;
	device->handle = handle;
	device->cfgopt = cfg;
	device->dbgopt = dbg;
	device->name = name;
	list_add_tail(&device->head, &nv_devices);
	device->debug = nvkm_dbgopt(device->dbgopt, "device");
	INIT_LIST_HEAD(&device->subdev);

	ret = nvkm_event_init(&nvkm_device_event_func, 1, 1, &device->event);
	अगर (ret)
		जाओ करोne;

	mmio_base = device->func->resource_addr(device, 0);
	mmio_size = device->func->resource_size(device, 0);

	अगर (detect || mmio) अणु
		device->pri = ioremap(mmio_base, mmio_size);
		अगर (device->pri == शून्य) अणु
			nvdev_error(device, "unable to map PRI\n");
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* identअगरy the chipset, and determine classes of subdev/engines */
	अगर (detect) अणु
		/* चयन mmio to cpu's native endianness */
		अगर (!nvkm_device_endianness(device)) अणु
			nvdev_error(device,
				    "Couldn't switch GPU to CPUs endianess\n");
			ret = -ENOSYS;
			जाओ करोne;
		पूर्ण

		boot0 = nvkm_rd32(device, 0x000000);

		/* chipset can be overridden क्रम devel/testing purposes */
		chipset = nvkm_दीर्घopt(device->cfgopt, "NvChipset", 0);
		अगर (chipset) अणु
			u32 override_boot0;

			अगर (chipset >= 0x10) अणु
				override_boot0  = ((chipset & 0x1ff) << 20);
				override_boot0 |= 0x000000a1;
			पूर्ण अन्यथा अणु
				अगर (chipset != 0x04)
					override_boot0 = 0x20104000;
				अन्यथा
					override_boot0 = 0x20004000;
			पूर्ण

			nvdev_warn(device, "CHIPSET OVERRIDE: %08x -> %08x\n",
				   boot0, override_boot0);
			boot0 = override_boot0;
		पूर्ण

		/* determine chipset and derive architecture from it */
		अगर ((boot0 & 0x1f000000) > 0) अणु
			device->chipset = (boot0 & 0x1ff00000) >> 20;
			device->chiprev = (boot0 & 0x000000ff);
			चयन (device->chipset & 0x1f0) अणु
			हाल 0x010: अणु
				अगर (0x461 & (1 << (device->chipset & 0xf)))
					device->card_type = NV_10;
				अन्यथा
					device->card_type = NV_11;
				device->chiprev = 0x00;
				अवरोध;
			पूर्ण
			हाल 0x020: device->card_type = NV_20; अवरोध;
			हाल 0x030: device->card_type = NV_30; अवरोध;
			हाल 0x040:
			हाल 0x060: device->card_type = NV_40; अवरोध;
			हाल 0x050:
			हाल 0x080:
			हाल 0x090:
			हाल 0x0a0: device->card_type = NV_50; अवरोध;
			हाल 0x0c0:
			हाल 0x0d0: device->card_type = NV_C0; अवरोध;
			हाल 0x0e0:
			हाल 0x0f0:
			हाल 0x100: device->card_type = NV_E0; अवरोध;
			हाल 0x110:
			हाल 0x120: device->card_type = GM100; अवरोध;
			हाल 0x130: device->card_type = GP100; अवरोध;
			हाल 0x140: device->card_type = GV100; अवरोध;
			हाल 0x160: device->card_type = TU100; अवरोध;
			हाल 0x170: device->card_type = GA100; अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
		अगर ((boot0 & 0xff00fff0) == 0x20004000) अणु
			अगर (boot0 & 0x00f00000)
				device->chipset = 0x05;
			अन्यथा
				device->chipset = 0x04;
			device->card_type = NV_04;
		पूर्ण

		चयन (device->chipset) अणु
		हाल 0x004: device->chip = &nv4_chipset; अवरोध;
		हाल 0x005: device->chip = &nv5_chipset; अवरोध;
		हाल 0x010: device->chip = &nv10_chipset; अवरोध;
		हाल 0x011: device->chip = &nv11_chipset; अवरोध;
		हाल 0x015: device->chip = &nv15_chipset; अवरोध;
		हाल 0x017: device->chip = &nv17_chipset; अवरोध;
		हाल 0x018: device->chip = &nv18_chipset; अवरोध;
		हाल 0x01a: device->chip = &nv1a_chipset; अवरोध;
		हाल 0x01f: device->chip = &nv1f_chipset; अवरोध;
		हाल 0x020: device->chip = &nv20_chipset; अवरोध;
		हाल 0x025: device->chip = &nv25_chipset; अवरोध;
		हाल 0x028: device->chip = &nv28_chipset; अवरोध;
		हाल 0x02a: device->chip = &nv2a_chipset; अवरोध;
		हाल 0x030: device->chip = &nv30_chipset; अवरोध;
		हाल 0x031: device->chip = &nv31_chipset; अवरोध;
		हाल 0x034: device->chip = &nv34_chipset; अवरोध;
		हाल 0x035: device->chip = &nv35_chipset; अवरोध;
		हाल 0x036: device->chip = &nv36_chipset; अवरोध;
		हाल 0x040: device->chip = &nv40_chipset; अवरोध;
		हाल 0x041: device->chip = &nv41_chipset; अवरोध;
		हाल 0x042: device->chip = &nv42_chipset; अवरोध;
		हाल 0x043: device->chip = &nv43_chipset; अवरोध;
		हाल 0x044: device->chip = &nv44_chipset; अवरोध;
		हाल 0x045: device->chip = &nv45_chipset; अवरोध;
		हाल 0x046: device->chip = &nv46_chipset; अवरोध;
		हाल 0x047: device->chip = &nv47_chipset; अवरोध;
		हाल 0x049: device->chip = &nv49_chipset; अवरोध;
		हाल 0x04a: device->chip = &nv4a_chipset; अवरोध;
		हाल 0x04b: device->chip = &nv4b_chipset; अवरोध;
		हाल 0x04c: device->chip = &nv4c_chipset; अवरोध;
		हाल 0x04e: device->chip = &nv4e_chipset; अवरोध;
		हाल 0x050: device->chip = &nv50_chipset; अवरोध;
		हाल 0x063: device->chip = &nv63_chipset; अवरोध;
		हाल 0x067: device->chip = &nv67_chipset; अवरोध;
		हाल 0x068: device->chip = &nv68_chipset; अवरोध;
		हाल 0x084: device->chip = &nv84_chipset; अवरोध;
		हाल 0x086: device->chip = &nv86_chipset; अवरोध;
		हाल 0x092: device->chip = &nv92_chipset; अवरोध;
		हाल 0x094: device->chip = &nv94_chipset; अवरोध;
		हाल 0x096: device->chip = &nv96_chipset; अवरोध;
		हाल 0x098: device->chip = &nv98_chipset; अवरोध;
		हाल 0x0a0: device->chip = &nva0_chipset; अवरोध;
		हाल 0x0a3: device->chip = &nva3_chipset; अवरोध;
		हाल 0x0a5: device->chip = &nva5_chipset; अवरोध;
		हाल 0x0a8: device->chip = &nva8_chipset; अवरोध;
		हाल 0x0aa: device->chip = &nvaa_chipset; अवरोध;
		हाल 0x0ac: device->chip = &nvac_chipset; अवरोध;
		हाल 0x0af: device->chip = &nvaf_chipset; अवरोध;
		हाल 0x0c0: device->chip = &nvc0_chipset; अवरोध;
		हाल 0x0c1: device->chip = &nvc1_chipset; अवरोध;
		हाल 0x0c3: device->chip = &nvc3_chipset; अवरोध;
		हाल 0x0c4: device->chip = &nvc4_chipset; अवरोध;
		हाल 0x0c8: device->chip = &nvc8_chipset; अवरोध;
		हाल 0x0ce: device->chip = &nvce_chipset; अवरोध;
		हाल 0x0cf: device->chip = &nvcf_chipset; अवरोध;
		हाल 0x0d7: device->chip = &nvd7_chipset; अवरोध;
		हाल 0x0d9: device->chip = &nvd9_chipset; अवरोध;
		हाल 0x0e4: device->chip = &nve4_chipset; अवरोध;
		हाल 0x0e6: device->chip = &nve6_chipset; अवरोध;
		हाल 0x0e7: device->chip = &nve7_chipset; अवरोध;
		हाल 0x0ea: device->chip = &nvea_chipset; अवरोध;
		हाल 0x0f0: device->chip = &nvf0_chipset; अवरोध;
		हाल 0x0f1: device->chip = &nvf1_chipset; अवरोध;
		हाल 0x106: device->chip = &nv106_chipset; अवरोध;
		हाल 0x108: device->chip = &nv108_chipset; अवरोध;
		हाल 0x117: device->chip = &nv117_chipset; अवरोध;
		हाल 0x118: device->chip = &nv118_chipset; अवरोध;
		हाल 0x120: device->chip = &nv120_chipset; अवरोध;
		हाल 0x124: device->chip = &nv124_chipset; अवरोध;
		हाल 0x126: device->chip = &nv126_chipset; अवरोध;
		हाल 0x12b: device->chip = &nv12b_chipset; अवरोध;
		हाल 0x130: device->chip = &nv130_chipset; अवरोध;
		हाल 0x132: device->chip = &nv132_chipset; अवरोध;
		हाल 0x134: device->chip = &nv134_chipset; अवरोध;
		हाल 0x136: device->chip = &nv136_chipset; अवरोध;
		हाल 0x137: device->chip = &nv137_chipset; अवरोध;
		हाल 0x138: device->chip = &nv138_chipset; अवरोध;
		हाल 0x13b: device->chip = &nv13b_chipset; अवरोध;
		हाल 0x140: device->chip = &nv140_chipset; अवरोध;
		हाल 0x162: device->chip = &nv162_chipset; अवरोध;
		हाल 0x164: device->chip = &nv164_chipset; अवरोध;
		हाल 0x166: device->chip = &nv166_chipset; अवरोध;
		हाल 0x167: device->chip = &nv167_chipset; अवरोध;
		हाल 0x168: device->chip = &nv168_chipset; अवरोध;
		हाल 0x172: device->chip = &nv172_chipset; अवरोध;
		हाल 0x174: device->chip = &nv174_chipset; अवरोध;
		शेष:
			अगर (nvkm_boolopt(device->cfgopt, "NvEnableUnsupportedChipsets", false)) अणु
				चयन (device->chipset) अणु
				हाल 0x170: device->chip = &nv170_chipset; अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!device->chip) अणु
				nvdev_error(device, "unknown chipset (%08x)\n", boot0);
				ret = -ENODEV;
				जाओ करोne;
			पूर्ण
			अवरोध;
		पूर्ण

		nvdev_info(device, "NVIDIA %s (%08x)\n",
			   device->chip->name, boot0);

		/* vGPU detection */
		boot1 = nvkm_rd32(device, 0x0000004);
		अगर (device->card_type >= TU100 && (boot1 & 0x00030000)) अणु
			nvdev_info(device, "vGPUs are not supported\n");
			ret = -ENODEV;
			जाओ करोne;
		पूर्ण

		/* पढ़ो strapping inक्रमmation */
		strap = nvkm_rd32(device, 0x101000);

		/* determine frequency of timing crystal */
		अगर ( device->card_type <= NV_10 || device->chipset < 0x17 ||
		    (device->chipset >= 0x20 && device->chipset < 0x25))
			strap &= 0x00000040;
		अन्यथा
			strap &= 0x00400040;

		चयन (strap) अणु
		हाल 0x00000000: device->crystal = 13500; अवरोध;
		हाल 0x00000040: device->crystal = 14318; अवरोध;
		हाल 0x00400000: device->crystal = 27000; अवरोध;
		हाल 0x00400040: device->crystal = 25000; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		device->chip = &null_chipset;
	पूर्ण

	अगर (!device->name)
		device->name = device->chip->name;

	mutex_init(&device->mutex);

#घोषणा NVKM_LAYOUT_ONCE(type,data,ptr)                                                      \
	अगर (device->chip->ptr.inst && (subdev_mask & (BIT_ULL(type)))) अणु                     \
		WARN_ON(device->chip->ptr.inst != 0x00000001);                               \
		ret = device->chip->ptr.ctor(device, (type), -1, &device->ptr);              \
		subdev = nvkm_device_subdev(device, (type), 0);                              \
		अगर (ret) अणु                                                                   \
			nvkm_subdev_del(&subdev);                                            \
			device->ptr = शून्य;                                                  \
			अगर (ret != -ENODEV) अणु                                                \
				nvdev_error(device, "%s ctor failed: %d\n",                  \
					    nvkm_subdev_type[(type)], ret);                  \
				जाओ करोne;                                                   \
			पूर्ण                                                                    \
		पूर्ण अन्यथा अणु                                                                     \
			subdev->pself = (व्योम **)&device->ptr;                               \
		पूर्ण                                                                            \
	पूर्ण
#घोषणा NVKM_LAYOUT_INST(type,data,ptr,cnt)                                                  \
	WARN_ON(device->chip->ptr.inst & ~((1 << ARRAY_SIZE(device->ptr)) - 1));             \
	क्रम (j = 0; device->chip->ptr.inst && j < ARRAY_SIZE(device->ptr); j++) अणु            \
		अगर ((device->chip->ptr.inst & BIT(j)) && (subdev_mask & BIT_ULL(type))) अणु    \
			पूर्णांक inst = (device->chip->ptr.inst == 1) ? -1 : (j);                 \
			ret = device->chip->ptr.ctor(device, (type), inst, &device->ptr[j]); \
			subdev = nvkm_device_subdev(device, (type), (j));                    \
			अगर (ret) अणु                                                           \
				nvkm_subdev_del(&subdev);                                    \
				device->ptr[j] = शून्य;                                       \
				अगर (ret != -ENODEV) अणु                                        \
					nvdev_error(device, "%s%d ctor failed: %d\n",        \
						    nvkm_subdev_type[(type)], (j), ret);     \
					जाओ करोne;                                           \
				पूर्ण                                                            \
			पूर्ण अन्यथा अणु                                                             \
				subdev->pself = (व्योम **)&device->ptr[j];                    \
			पूर्ण                                                                    \
		पूर्ण                                                                            \
	पूर्ण
#समावेश <core/layout.h>
#अघोषित NVKM_LAYOUT_INST
#अघोषित NVKM_LAYOUT_ONCE

	ret = 0;
करोne:
	अगर (device->pri && (!mmio || ret)) अणु
		iounmap(device->pri);
		device->pri = शून्य;
	पूर्ण
	mutex_unlock(&nv_devices_mutex);
	वापस ret;
पूर्ण
