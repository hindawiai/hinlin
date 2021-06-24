<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <linux/export.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_edid.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_i2c.h"
#समावेश "amdgpu_atombios.h"
#समावेश "atom.h"
#समावेश "atombios_dp.h"
#समावेश "atombios_i2c.h"

/* bit banging i2c */
अटल पूर्णांक amdgpu_i2c_pre_xfer(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा amdgpu_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा amdgpu_device *adev = drm_to_adev(i2c->dev);
	काष्ठा amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t temp;

	mutex_lock(&i2c->mutex);

	/* चयन the pads to ddc mode */
	अगर (rec->hw_capable) अणु
		temp = RREG32(rec->mask_clk_reg);
		temp &= ~(1 << 16);
		WREG32(rec->mask_clk_reg, temp);
	पूर्ण

	/* clear the output pin values */
	temp = RREG32(rec->a_clk_reg) & ~rec->a_clk_mask;
	WREG32(rec->a_clk_reg, temp);

	temp = RREG32(rec->a_data_reg) & ~rec->a_data_mask;
	WREG32(rec->a_data_reg, temp);

	/* set the pins to input */
	temp = RREG32(rec->en_clk_reg) & ~rec->en_clk_mask;
	WREG32(rec->en_clk_reg, temp);

	temp = RREG32(rec->en_data_reg) & ~rec->en_data_mask;
	WREG32(rec->en_data_reg, temp);

	/* mask the gpio pins क्रम software use */
	temp = RREG32(rec->mask_clk_reg) | rec->mask_clk_mask;
	WREG32(rec->mask_clk_reg, temp);
	temp = RREG32(rec->mask_clk_reg);

	temp = RREG32(rec->mask_data_reg) | rec->mask_data_mask;
	WREG32(rec->mask_data_reg, temp);
	temp = RREG32(rec->mask_data_reg);

	वापस 0;
पूर्ण

अटल व्योम amdgpu_i2c_post_xfer(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा amdgpu_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा amdgpu_device *adev = drm_to_adev(i2c->dev);
	काष्ठा amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t temp;

	/* unmask the gpio pins क्रम software use */
	temp = RREG32(rec->mask_clk_reg) & ~rec->mask_clk_mask;
	WREG32(rec->mask_clk_reg, temp);
	temp = RREG32(rec->mask_clk_reg);

	temp = RREG32(rec->mask_data_reg) & ~rec->mask_data_mask;
	WREG32(rec->mask_data_reg, temp);
	temp = RREG32(rec->mask_data_reg);

	mutex_unlock(&i2c->mutex);
पूर्ण

अटल पूर्णांक amdgpu_i2c_get_घड़ी(व्योम *i2c_priv)
अणु
	काष्ठा amdgpu_i2c_chan *i2c = i2c_priv;
	काष्ठा amdgpu_device *adev = drm_to_adev(i2c->dev);
	काष्ठा amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* पढ़ो the value off the pin */
	val = RREG32(rec->y_clk_reg);
	val &= rec->y_clk_mask;

	वापस (val != 0);
पूर्ण


अटल पूर्णांक amdgpu_i2c_get_data(व्योम *i2c_priv)
अणु
	काष्ठा amdgpu_i2c_chan *i2c = i2c_priv;
	काष्ठा amdgpu_device *adev = drm_to_adev(i2c->dev);
	काष्ठा amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* पढ़ो the value off the pin */
	val = RREG32(rec->y_data_reg);
	val &= rec->y_data_mask;

	वापस (val != 0);
पूर्ण

अटल व्योम amdgpu_i2c_set_घड़ी(व्योम *i2c_priv, पूर्णांक घड़ी)
अणु
	काष्ठा amdgpu_i2c_chan *i2c = i2c_priv;
	काष्ठा amdgpu_device *adev = drm_to_adev(i2c->dev);
	काष्ठा amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* set pin direction */
	val = RREG32(rec->en_clk_reg) & ~rec->en_clk_mask;
	val |= घड़ी ? 0 : rec->en_clk_mask;
	WREG32(rec->en_clk_reg, val);
पूर्ण

अटल व्योम amdgpu_i2c_set_data(व्योम *i2c_priv, पूर्णांक data)
अणु
	काष्ठा amdgpu_i2c_chan *i2c = i2c_priv;
	काष्ठा amdgpu_device *adev = drm_to_adev(i2c->dev);
	काष्ठा amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* set pin direction */
	val = RREG32(rec->en_data_reg) & ~rec->en_data_mask;
	val |= data ? 0 : rec->en_data_mask;
	WREG32(rec->en_data_reg, val);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm amdgpu_atombios_i2c_algo = अणु
	.master_xfer = amdgpu_atombios_i2c_xfer,
	.functionality = amdgpu_atombios_i2c_func,
पूर्ण;

काष्ठा amdgpu_i2c_chan *amdgpu_i2c_create(काष्ठा drm_device *dev,
					  स्थिर काष्ठा amdgpu_i2c_bus_rec *rec,
					  स्थिर अक्षर *name)
अणु
	काष्ठा amdgpu_i2c_chan *i2c;
	पूर्णांक ret;

	/* करोn't add the mm_i2c bus unless hw_i2c is enabled */
	अगर (rec->mm_i2c && (amdgpu_hw_i2c == 0))
		वापस शून्य;

	i2c = kzalloc(माप(काष्ठा amdgpu_i2c_chan), GFP_KERNEL);
	अगर (i2c == शून्य)
		वापस शून्य;

	i2c->rec = *rec;
	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = dev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adapter, i2c);
	mutex_init(&i2c->mutex);
	अगर (rec->hw_capable &&
	    amdgpu_hw_i2c) अणु
		/* hw i2c using atom */
		snम_लिखो(i2c->adapter.name, माप(i2c->adapter.name),
			 "AMDGPU i2c hw bus %s", name);
		i2c->adapter.algo = &amdgpu_atombios_i2c_algo;
		ret = i2c_add_adapter(&i2c->adapter);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अणु
		/* set the amdgpu bit adapter */
		snम_लिखो(i2c->adapter.name, माप(i2c->adapter.name),
			 "AMDGPU i2c bit bus %s", name);
		i2c->adapter.algo_data = &i2c->bit;
		i2c->bit.pre_xfer = amdgpu_i2c_pre_xfer;
		i2c->bit.post_xfer = amdgpu_i2c_post_xfer;
		i2c->bit.setsda = amdgpu_i2c_set_data;
		i2c->bit.setscl = amdgpu_i2c_set_घड़ी;
		i2c->bit.माला_लोda = amdgpu_i2c_get_data;
		i2c->bit.माला_लोcl = amdgpu_i2c_get_घड़ी;
		i2c->bit.udelay = 10;
		i2c->bit.समयout = usecs_to_jअगरfies(2200);	/* from VESA */
		i2c->bit.data = i2c;
		ret = i2c_bit_add_bus(&i2c->adapter);
		अगर (ret) अणु
			DRM_ERROR("Failed to register bit i2c %s\n", name);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	वापस i2c;
out_मुक्त:
	kमुक्त(i2c);
	वापस शून्य;

पूर्ण

व्योम amdgpu_i2c_destroy(काष्ठा amdgpu_i2c_chan *i2c)
अणु
	अगर (!i2c)
		वापस;
	WARN_ON(i2c->has_aux);
	i2c_del_adapter(&i2c->adapter);
	kमुक्त(i2c);
पूर्ण

/* Add the शेष buses */
व्योम amdgpu_i2c_init(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_hw_i2c)
		DRM_INFO("hw_i2c forced on, you may experience display detection problems!\n");

	amdgpu_atombios_i2c_init(adev);
पूर्ण

/* हटाओ all the buses */
व्योम amdgpu_i2c_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AMDGPU_MAX_I2C_BUS; i++) अणु
		अगर (adev->i2c_bus[i]) अणु
			amdgpu_i2c_destroy(adev->i2c_bus[i]);
			adev->i2c_bus[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Add additional buses */
व्योम amdgpu_i2c_add(काष्ठा amdgpu_device *adev,
		    स्थिर काष्ठा amdgpu_i2c_bus_rec *rec,
		    स्थिर अक्षर *name)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	पूर्णांक i;

	क्रम (i = 0; i < AMDGPU_MAX_I2C_BUS; i++) अणु
		अगर (!adev->i2c_bus[i]) अणु
			adev->i2c_bus[i] = amdgpu_i2c_create(dev, rec, name);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/* looks up bus based on id */
काष्ठा amdgpu_i2c_chan *
amdgpu_i2c_lookup(काष्ठा amdgpu_device *adev,
		  स्थिर काष्ठा amdgpu_i2c_bus_rec *i2c_bus)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AMDGPU_MAX_I2C_BUS; i++) अणु
		अगर (adev->i2c_bus[i] &&
		    (adev->i2c_bus[i]->rec.i2c_id == i2c_bus->i2c_id)) अणु
			वापस adev->i2c_bus[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम amdgpu_i2c_get_byte(काष्ठा amdgpu_i2c_chan *i2c_bus,
				 u8 slave_addr,
				 u8 addr,
				 u8 *val)
अणु
	u8 out_buf[2];
	u8 in_buf[2];
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = slave_addr,
			.flags = 0,
			.len = 1,
			.buf = out_buf,
		पूर्ण,
		अणु
			.addr = slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = in_buf,
		पूर्ण
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = 0;

	अगर (i2c_transfer(&i2c_bus->adapter, msgs, 2) == 2) अणु
		*val = in_buf[0];
		DRM_DEBUG("val = 0x%02x\n", *val);
	पूर्ण अन्यथा अणु
		DRM_DEBUG("i2c 0x%02x 0x%02x read failed\n",
			  addr, *val);
	पूर्ण
पूर्ण

अटल व्योम amdgpu_i2c_put_byte(काष्ठा amdgpu_i2c_chan *i2c_bus,
				 u8 slave_addr,
				 u8 addr,
				 u8 val)
अणु
	uपूर्णांक8_t out_buf[2];
	काष्ठा i2c_msg msg = अणु
		.addr = slave_addr,
		.flags = 0,
		.len = 2,
		.buf = out_buf,
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = val;

	अगर (i2c_transfer(&i2c_bus->adapter, &msg, 1) != 1)
		DRM_DEBUG("i2c 0x%02x 0x%02x write failed\n",
			  addr, val);
पूर्ण

/* ddc router चयनing */
व्योम
amdgpu_i2c_router_select_ddc_port(स्थिर काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	u8 val;

	अगर (!amdgpu_connector->router.ddc_valid)
		वापस;

	अगर (!amdgpu_connector->router_bus)
		वापस;

	amdgpu_i2c_get_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x3, &val);
	val &= ~amdgpu_connector->router.ddc_mux_control_pin;
	amdgpu_i2c_put_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x3, val);
	amdgpu_i2c_get_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x1, &val);
	val &= ~amdgpu_connector->router.ddc_mux_control_pin;
	val |= amdgpu_connector->router.ddc_mux_state;
	amdgpu_i2c_put_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x1, val);
पूर्ण

/* घड़ी/data router चयनing */
व्योम
amdgpu_i2c_router_select_cd_port(स्थिर काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	u8 val;

	अगर (!amdgpu_connector->router.cd_valid)
		वापस;

	अगर (!amdgpu_connector->router_bus)
		वापस;

	amdgpu_i2c_get_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x3, &val);
	val &= ~amdgpu_connector->router.cd_mux_control_pin;
	amdgpu_i2c_put_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x3, val);
	amdgpu_i2c_get_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x1, &val);
	val &= ~amdgpu_connector->router.cd_mux_control_pin;
	val |= amdgpu_connector->router.cd_mux_state;
	amdgpu_i2c_put_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x1, val);
पूर्ण
