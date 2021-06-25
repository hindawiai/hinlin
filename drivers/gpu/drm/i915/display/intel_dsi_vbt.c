<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Author: Shobhit Kumar <shobhit.kumar@पूर्णांकel.com>
 *
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पूर्णांकel-mid.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>

#समावेश <video/mipi_display.h>

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dsi.h"
#समावेश "intel_sideband.h"

#घोषणा MIPI_TRANSFER_MODE_SHIFT	0
#घोषणा MIPI_VIRTUAL_CHANNEL_SHIFT	1
#घोषणा MIPI_PORT_SHIFT			3

/* base offsets क्रम gpio pads */
#घोषणा VLV_GPIO_NC_0_HV_DDI0_HPD	0x4130
#घोषणा VLV_GPIO_NC_1_HV_DDI0_DDC_SDA	0x4120
#घोषणा VLV_GPIO_NC_2_HV_DDI0_DDC_SCL	0x4110
#घोषणा VLV_GPIO_NC_3_PANEL0_VDDEN	0x4140
#घोषणा VLV_GPIO_NC_4_PANEL0_BKLTEN	0x4150
#घोषणा VLV_GPIO_NC_5_PANEL0_BKLTCTL	0x4160
#घोषणा VLV_GPIO_NC_6_HV_DDI1_HPD	0x4180
#घोषणा VLV_GPIO_NC_7_HV_DDI1_DDC_SDA	0x4190
#घोषणा VLV_GPIO_NC_8_HV_DDI1_DDC_SCL	0x4170
#घोषणा VLV_GPIO_NC_9_PANEL1_VDDEN	0x4100
#घोषणा VLV_GPIO_NC_10_PANEL1_BKLTEN	0x40E0
#घोषणा VLV_GPIO_NC_11_PANEL1_BKLTCTL	0x40F0

#घोषणा VLV_GPIO_PCONF0(base_offset)	(base_offset)
#घोषणा VLV_GPIO_PAD_VAL(base_offset)	((base_offset) + 8)

काष्ठा gpio_map अणु
	u16 base_offset;
	bool init;
पूर्ण;

अटल काष्ठा gpio_map vlv_gpio_table[] = अणु
	अणु VLV_GPIO_NC_0_HV_DDI0_HPD पूर्ण,
	अणु VLV_GPIO_NC_1_HV_DDI0_DDC_SDA पूर्ण,
	अणु VLV_GPIO_NC_2_HV_DDI0_DDC_SCL पूर्ण,
	अणु VLV_GPIO_NC_3_PANEL0_VDDEN पूर्ण,
	अणु VLV_GPIO_NC_4_PANEL0_BKLTEN पूर्ण,
	अणु VLV_GPIO_NC_5_PANEL0_BKLTCTL पूर्ण,
	अणु VLV_GPIO_NC_6_HV_DDI1_HPD पूर्ण,
	अणु VLV_GPIO_NC_7_HV_DDI1_DDC_SDA पूर्ण,
	अणु VLV_GPIO_NC_8_HV_DDI1_DDC_SCL पूर्ण,
	अणु VLV_GPIO_NC_9_PANEL1_VDDEN पूर्ण,
	अणु VLV_GPIO_NC_10_PANEL1_BKLTEN पूर्ण,
	अणु VLV_GPIO_NC_11_PANEL1_BKLTCTL पूर्ण,
पूर्ण;

काष्ठा i2c_adapter_lookup अणु
	u16 slave_addr;
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi;
	acpi_handle dev_handle;
पूर्ण;

#घोषणा CHV_GPIO_IDX_START_N		0
#घोषणा CHV_GPIO_IDX_START_E		73
#घोषणा CHV_GPIO_IDX_START_SW		100
#घोषणा CHV_GPIO_IDX_START_SE		198

#घोषणा CHV_VBT_MAX_PINS_PER_FMLY	15

#घोषणा CHV_GPIO_PAD_CFG0(f, i)		(0x4400 + (f) * 0x400 + (i) * 8)
#घोषणा  CHV_GPIO_GPIOEN		(1 << 15)
#घोषणा  CHV_GPIO_GPIOCFG_GPIO		(0 << 8)
#घोषणा  CHV_GPIO_GPIOCFG_GPO		(1 << 8)
#घोषणा  CHV_GPIO_GPIOCFG_GPI		(2 << 8)
#घोषणा  CHV_GPIO_GPIOCFG_HIZ		(3 << 8)
#घोषणा  CHV_GPIO_GPIOTXSTATE(state)	((!!(state)) << 1)

#घोषणा CHV_GPIO_PAD_CFG1(f, i)		(0x4400 + (f) * 0x400 + (i) * 8 + 4)
#घोषणा  CHV_GPIO_CFGLOCK		(1 << 31)

/* ICL DSI Display GPIO Pins */
#घोषणा  ICL_GPIO_DDSP_HPD_A		0
#घोषणा  ICL_GPIO_L_VDDEN_1		1
#घोषणा  ICL_GPIO_L_BKLTEN_1		2
#घोषणा  ICL_GPIO_DDPA_CTRLCLK_1	3
#घोषणा  ICL_GPIO_DDPA_CTRLDATA_1	4
#घोषणा  ICL_GPIO_DDSP_HPD_B		5
#घोषणा  ICL_GPIO_L_VDDEN_2		6
#घोषणा  ICL_GPIO_L_BKLTEN_2		7
#घोषणा  ICL_GPIO_DDPA_CTRLCLK_2	8
#घोषणा  ICL_GPIO_DDPA_CTRLDATA_2	9

अटल क्रमागत port पूर्णांकel_dsi_seq_port_to_port(u8 port)
अणु
	वापस port ? PORT_C : PORT_A;
पूर्ण

अटल स्थिर u8 *mipi_exec_send_packet(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
				       स्थिर u8 *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_dsi->base.base.dev);
	काष्ठा mipi_dsi_device *dsi_device;
	u8 type, flags, seq_port;
	u16 len;
	क्रमागत port port;

	drm_dbg_kms(&dev_priv->drm, "\n");

	flags = *data++;
	type = *data++;

	len = *((u16 *) data);
	data += 2;

	seq_port = (flags >> MIPI_PORT_SHIFT) & 3;

	/* For DSI single link on Port A & C, the seq_port value which is
	 * parsed from Sequence Block#53 of VBT has been set to 0
	 * Now, पढ़ो/ग_लिखो of packets क्रम the DSI single link on Port A and
	 * Port C will based on the DVO port from VBT block 2.
	 */
	अगर (पूर्णांकel_dsi->ports == (1 << PORT_C))
		port = PORT_C;
	अन्यथा
		port = पूर्णांकel_dsi_seq_port_to_port(seq_port);

	dsi_device = पूर्णांकel_dsi->dsi_hosts[port]->device;
	अगर (!dsi_device) अणु
		drm_dbg_kms(&dev_priv->drm, "no dsi device for port %c\n",
			    port_name(port));
		जाओ out;
	पूर्ण

	अगर ((flags >> MIPI_TRANSFER_MODE_SHIFT) & 1)
		dsi_device->mode_flags &= ~MIPI_DSI_MODE_LPM;
	अन्यथा
		dsi_device->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_device->channel = (flags >> MIPI_VIRTUAL_CHANNEL_SHIFT) & 3;

	चयन (type) अणु
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
		mipi_dsi_generic_ग_लिखो(dsi_device, शून्य, 0);
		अवरोध;
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
		mipi_dsi_generic_ग_लिखो(dsi_device, data, 1);
		अवरोध;
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
		mipi_dsi_generic_ग_लिखो(dsi_device, data, 2);
		अवरोध;
	हाल MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
	हाल MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
	हाल MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
		drm_dbg(&dev_priv->drm,
			"Generic Read not yet implemented or used\n");
		अवरोध;
	हाल MIPI_DSI_GENERIC_LONG_WRITE:
		mipi_dsi_generic_ग_लिखो(dsi_device, data, len);
		अवरोध;
	हाल MIPI_DSI_DCS_SHORT_WRITE:
		mipi_dsi_dcs_ग_लिखो_buffer(dsi_device, data, 1);
		अवरोध;
	हाल MIPI_DSI_DCS_SHORT_WRITE_PARAM:
		mipi_dsi_dcs_ग_लिखो_buffer(dsi_device, data, 2);
		अवरोध;
	हाल MIPI_DSI_DCS_READ:
		drm_dbg(&dev_priv->drm,
			"DCS Read not yet implemented or used\n");
		अवरोध;
	हाल MIPI_DSI_DCS_LONG_WRITE:
		mipi_dsi_dcs_ग_लिखो_buffer(dsi_device, data, len);
		अवरोध;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) < 11)
		vlv_dsi_रुको_क्रम_fअगरo_empty(पूर्णांकel_dsi, port);

out:
	data += len;

	वापस data;
पूर्ण

अटल स्थिर u8 *mipi_exec_delay(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, स्थिर u8 *data)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_dsi->base.base.dev);
	u32 delay = *((स्थिर u32 *) data);

	drm_dbg_kms(&i915->drm, "\n");

	usleep_range(delay, delay + 10);
	data += 4;

	वापस data;
पूर्ण

अटल व्योम vlv_exec_gpio(काष्ठा drm_i915_निजी *dev_priv,
			  u8 gpio_source, u8 gpio_index, bool value)
अणु
	काष्ठा gpio_map *map;
	u16 pconf0, padval;
	u32 पंचांगp;
	u8 port;

	अगर (gpio_index >= ARRAY_SIZE(vlv_gpio_table)) अणु
		drm_dbg_kms(&dev_priv->drm, "unknown gpio index %u\n",
			    gpio_index);
		वापस;
	पूर्ण

	map = &vlv_gpio_table[gpio_index];

	अगर (dev_priv->vbt.dsi.seq_version >= 3) अणु
		/* XXX: this assumes vlv_gpio_table only has NC GPIOs. */
		port = IOSF_PORT_GPIO_NC;
	पूर्ण अन्यथा अणु
		अगर (gpio_source == 0) अणु
			port = IOSF_PORT_GPIO_NC;
		पूर्ण अन्यथा अगर (gpio_source == 1) अणु
			drm_dbg_kms(&dev_priv->drm, "SC gpio not supported\n");
			वापस;
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&dev_priv->drm,
				    "unknown gpio source %u\n", gpio_source);
			वापस;
		पूर्ण
	पूर्ण

	pconf0 = VLV_GPIO_PCONF0(map->base_offset);
	padval = VLV_GPIO_PAD_VAL(map->base_offset);

	vlv_iosf_sb_get(dev_priv, BIT(VLV_IOSF_SB_GPIO));
	अगर (!map->init) अणु
		/* FIXME: हटाओ स्थिरant below */
		vlv_iosf_sb_ग_लिखो(dev_priv, port, pconf0, 0x2000CC00);
		map->init = true;
	पूर्ण

	पंचांगp = 0x4 | value;
	vlv_iosf_sb_ग_लिखो(dev_priv, port, padval, पंचांगp);
	vlv_iosf_sb_put(dev_priv, BIT(VLV_IOSF_SB_GPIO));
पूर्ण

अटल व्योम chv_exec_gpio(काष्ठा drm_i915_निजी *dev_priv,
			  u8 gpio_source, u8 gpio_index, bool value)
अणु
	u16 cfg0, cfg1;
	u16 family_num;
	u8 port;

	अगर (dev_priv->vbt.dsi.seq_version >= 3) अणु
		अगर (gpio_index >= CHV_GPIO_IDX_START_SE) अणु
			/* XXX: it's unclear whether 255->57 is part of SE. */
			gpio_index -= CHV_GPIO_IDX_START_SE;
			port = CHV_IOSF_PORT_GPIO_SE;
		पूर्ण अन्यथा अगर (gpio_index >= CHV_GPIO_IDX_START_SW) अणु
			gpio_index -= CHV_GPIO_IDX_START_SW;
			port = CHV_IOSF_PORT_GPIO_SW;
		पूर्ण अन्यथा अगर (gpio_index >= CHV_GPIO_IDX_START_E) अणु
			gpio_index -= CHV_GPIO_IDX_START_E;
			port = CHV_IOSF_PORT_GPIO_E;
		पूर्ण अन्यथा अणु
			port = CHV_IOSF_PORT_GPIO_N;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* XXX: The spec is unclear about CHV GPIO on seq v2 */
		अगर (gpio_source != 0) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "unknown gpio source %u\n", gpio_source);
			वापस;
		पूर्ण

		अगर (gpio_index >= CHV_GPIO_IDX_START_E) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "invalid gpio index %u for GPIO N\n",
				    gpio_index);
			वापस;
		पूर्ण

		port = CHV_IOSF_PORT_GPIO_N;
	पूर्ण

	family_num = gpio_index / CHV_VBT_MAX_PINS_PER_FMLY;
	gpio_index = gpio_index % CHV_VBT_MAX_PINS_PER_FMLY;

	cfg0 = CHV_GPIO_PAD_CFG0(family_num, gpio_index);
	cfg1 = CHV_GPIO_PAD_CFG1(family_num, gpio_index);

	vlv_iosf_sb_get(dev_priv, BIT(VLV_IOSF_SB_GPIO));
	vlv_iosf_sb_ग_लिखो(dev_priv, port, cfg1, 0);
	vlv_iosf_sb_ग_लिखो(dev_priv, port, cfg0,
			  CHV_GPIO_GPIOEN | CHV_GPIO_GPIOCFG_GPO |
			  CHV_GPIO_GPIOTXSTATE(value));
	vlv_iosf_sb_put(dev_priv, BIT(VLV_IOSF_SB_GPIO));
पूर्ण

अटल व्योम bxt_exec_gpio(काष्ठा drm_i915_निजी *dev_priv,
			  u8 gpio_source, u8 gpio_index, bool value)
अणु
	/* XXX: this table is a quick ugly hack. */
	अटल काष्ठा gpio_desc *bxt_gpio_table[U8_MAX + 1];
	काष्ठा gpio_desc *gpio_desc = bxt_gpio_table[gpio_index];

	अगर (!gpio_desc) अणु
		gpio_desc = devm_gpiod_get_index(dev_priv->drm.dev,
						 शून्य, gpio_index,
						 value ? GPIOD_OUT_LOW :
						 GPIOD_OUT_HIGH);

		अगर (IS_ERR_OR_शून्य(gpio_desc)) अणु
			drm_err(&dev_priv->drm,
				"GPIO index %u request failed (%ld)\n",
				gpio_index, PTR_ERR(gpio_desc));
			वापस;
		पूर्ण

		bxt_gpio_table[gpio_index] = gpio_desc;
	पूर्ण

	gpiod_set_value(gpio_desc, value);
पूर्ण

अटल व्योम icl_exec_gpio(काष्ठा drm_i915_निजी *dev_priv,
			  u8 gpio_source, u8 gpio_index, bool value)
अणु
	drm_dbg_kms(&dev_priv->drm, "Skipping ICL GPIO element execution\n");
पूर्ण

अटल स्थिर u8 *mipi_exec_gpio(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, स्थिर u8 *data)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u8 gpio_source, gpio_index = 0, gpio_number;
	bool value;

	drm_dbg_kms(&dev_priv->drm, "\n");

	अगर (dev_priv->vbt.dsi.seq_version >= 3)
		gpio_index = *data++;

	gpio_number = *data++;

	/* gpio source in sequence v2 only */
	अगर (dev_priv->vbt.dsi.seq_version == 2)
		gpio_source = (*data >> 1) & 3;
	अन्यथा
		gpio_source = 0;

	/* pull up/करोwn */
	value = *data++ & 1;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		icl_exec_gpio(dev_priv, gpio_source, gpio_index, value);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		vlv_exec_gpio(dev_priv, gpio_source, gpio_number, value);
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		chv_exec_gpio(dev_priv, gpio_source, gpio_number, value);
	अन्यथा
		bxt_exec_gpio(dev_priv, gpio_source, gpio_index, value);

	वापस data;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक i2c_adapter_lookup(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा i2c_adapter_lookup *lookup = data;
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = lookup->पूर्णांकel_dsi;
	काष्ठा acpi_resource_i2c_serialbus *sb;
	काष्ठा i2c_adapter *adapter;
	acpi_handle adapter_handle;
	acpi_status status;

	अगर (!i2c_acpi_get_i2c_resource(ares, &sb))
		वापस 1;

	अगर (lookup->slave_addr != sb->slave_address)
		वापस 1;

	status = acpi_get_handle(lookup->dev_handle,
				 sb->resource_source.string_ptr,
				 &adapter_handle);
	अगर (ACPI_FAILURE(status))
		वापस 1;

	adapter = i2c_acpi_find_adapter_by_handle(adapter_handle);
	अगर (adapter)
		पूर्णांकel_dsi->i2c_bus_num = adapter->nr;

	वापस 1;
पूर्ण

अटल व्योम i2c_acpi_find_adapter(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
				  स्थिर u16 slave_addr)
अणु
	काष्ठा drm_device *drm_dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा device *dev = drm_dev->dev;
	काष्ठा acpi_device *acpi_dev;
	काष्ठा list_head resource_list;
	काष्ठा i2c_adapter_lookup lookup;

	acpi_dev = ACPI_COMPANION(dev);
	अगर (acpi_dev) अणु
		स_रखो(&lookup, 0, माप(lookup));
		lookup.slave_addr = slave_addr;
		lookup.पूर्णांकel_dsi = पूर्णांकel_dsi;
		lookup.dev_handle = acpi_device_handle(acpi_dev);

		INIT_LIST_HEAD(&resource_list);
		acpi_dev_get_resources(acpi_dev, &resource_list,
				       i2c_adapter_lookup,
				       &lookup);
		acpi_dev_मुक्त_resource_list(&resource_list);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम i2c_acpi_find_adapter(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
					 स्थिर u16 slave_addr)
अणु
पूर्ण
#पूर्ण_अगर

अटल स्थिर u8 *mipi_exec_i2c(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, स्थिर u8 *data)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_dsi->base.base.dev);
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_msg msg;
	पूर्णांक ret;
	u8 vbt_i2c_bus_num = *(data + 2);
	u16 slave_addr = *(u16 *)(data + 3);
	u8 reg_offset = *(data + 5);
	u8 payload_size = *(data + 6);
	u8 *payload_data;

	अगर (पूर्णांकel_dsi->i2c_bus_num < 0) अणु
		पूर्णांकel_dsi->i2c_bus_num = vbt_i2c_bus_num;
		i2c_acpi_find_adapter(पूर्णांकel_dsi, slave_addr);
	पूर्ण

	adapter = i2c_get_adapter(पूर्णांकel_dsi->i2c_bus_num);
	अगर (!adapter) अणु
		drm_err(&i915->drm, "Cannot find a valid i2c bus for xfer\n");
		जाओ err_bus;
	पूर्ण

	payload_data = kzalloc(payload_size + 1, GFP_KERNEL);
	अगर (!payload_data)
		जाओ err_alloc;

	payload_data[0] = reg_offset;
	स_नकल(&payload_data[1], (data + 7), payload_size);

	msg.addr = slave_addr;
	msg.flags = 0;
	msg.len = payload_size + 1;
	msg.buf = payload_data;

	ret = i2c_transfer(adapter, &msg, 1);
	अगर (ret < 0)
		drm_err(&i915->drm,
			"Failed to xfer payload of size (%u) to reg (%u)\n",
			payload_size, reg_offset);

	kमुक्त(payload_data);
err_alloc:
	i2c_put_adapter(adapter);
err_bus:
	वापस data + payload_size + 7;
पूर्ण

अटल स्थिर u8 *mipi_exec_spi(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, स्थिर u8 *data)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_dsi->base.base.dev);

	drm_dbg_kms(&i915->drm, "Skipping SPI element execution\n");

	वापस data + *(data + 5) + 6;
पूर्ण

अटल स्थिर u8 *mipi_exec_pmic(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, स्थिर u8 *data)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_dsi->base.base.dev);
#अगर_घोषित CONFIG_PMIC_OPREGION
	u32 value, mask, reg_address;
	u16 i2c_address;
	पूर्णांक ret;

	/* byte 0 aka PMIC Flag is reserved */
	i2c_address	= get_unaligned_le16(data + 1);
	reg_address	= get_unaligned_le32(data + 3);
	value		= get_unaligned_le32(data + 7);
	mask		= get_unaligned_le32(data + 11);

	ret = पूर्णांकel_soc_pmic_exec_mipi_pmic_seq_element(i2c_address,
							reg_address,
							value, mask);
	अगर (ret)
		drm_err(&i915->drm, "%s failed, error: %d\n", __func__, ret);
#अन्यथा
	drm_err(&i915->drm,
		"Your hardware requires CONFIG_PMIC_OPREGION and it is not set\n");
#पूर्ण_अगर

	वापस data + 15;
पूर्ण

प्रकार स्थिर u8 * (*fn_mipi_elem_exec)(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
					स्थिर u8 *data);
अटल स्थिर fn_mipi_elem_exec exec_elem[] = अणु
	[MIPI_SEQ_ELEM_SEND_PKT] = mipi_exec_send_packet,
	[MIPI_SEQ_ELEM_DELAY] = mipi_exec_delay,
	[MIPI_SEQ_ELEM_GPIO] = mipi_exec_gpio,
	[MIPI_SEQ_ELEM_I2C] = mipi_exec_i2c,
	[MIPI_SEQ_ELEM_SPI] = mipi_exec_spi,
	[MIPI_SEQ_ELEM_PMIC] = mipi_exec_pmic,
पूर्ण;

/*
 * MIPI Sequence from VBT #53 parsing logic
 * We have alपढ़ोy separated each seqence during bios parsing
 * Following is generic execution function क्रम any sequence
 */

अटल स्थिर अक्षर * स्थिर seq_name[] = अणु
	[MIPI_SEQ_DEASSERT_RESET] = "MIPI_SEQ_DEASSERT_RESET",
	[MIPI_SEQ_INIT_OTP] = "MIPI_SEQ_INIT_OTP",
	[MIPI_SEQ_DISPLAY_ON] = "MIPI_SEQ_DISPLAY_ON",
	[MIPI_SEQ_DISPLAY_OFF]  = "MIPI_SEQ_DISPLAY_OFF",
	[MIPI_SEQ_ASSERT_RESET] = "MIPI_SEQ_ASSERT_RESET",
	[MIPI_SEQ_BACKLIGHT_ON] = "MIPI_SEQ_BACKLIGHT_ON",
	[MIPI_SEQ_BACKLIGHT_OFF] = "MIPI_SEQ_BACKLIGHT_OFF",
	[MIPI_SEQ_TEAR_ON] = "MIPI_SEQ_TEAR_ON",
	[MIPI_SEQ_TEAR_OFF] = "MIPI_SEQ_TEAR_OFF",
	[MIPI_SEQ_POWER_ON] = "MIPI_SEQ_POWER_ON",
	[MIPI_SEQ_POWER_OFF] = "MIPI_SEQ_POWER_OFF",
पूर्ण;

अटल स्थिर अक्षर *sequence_name(क्रमागत mipi_seq seq_id)
अणु
	अगर (seq_id < ARRAY_SIZE(seq_name) && seq_name[seq_id])
		वापस seq_name[seq_id];
	अन्यथा
		वापस "(unknown)";
पूर्ण

अटल व्योम पूर्णांकel_dsi_vbt_exec(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
			       क्रमागत mipi_seq seq_id)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_dsi->base.base.dev);
	स्थिर u8 *data;
	fn_mipi_elem_exec mipi_elem_exec;

	अगर (drm_WARN_ON(&dev_priv->drm,
			seq_id >= ARRAY_SIZE(dev_priv->vbt.dsi.sequence)))
		वापस;

	data = dev_priv->vbt.dsi.sequence[seq_id];
	अगर (!data)
		वापस;

	drm_WARN_ON(&dev_priv->drm, *data != seq_id);

	drm_dbg_kms(&dev_priv->drm, "Starting MIPI sequence %d - %s\n",
		    seq_id, sequence_name(seq_id));

	/* Skip Sequence Byte. */
	data++;

	/* Skip Size of Sequence. */
	अगर (dev_priv->vbt.dsi.seq_version >= 3)
		data += 4;

	जबतक (1) अणु
		u8 operation_byte = *data++;
		u8 operation_size = 0;

		अगर (operation_byte == MIPI_SEQ_ELEM_END)
			अवरोध;

		अगर (operation_byte < ARRAY_SIZE(exec_elem))
			mipi_elem_exec = exec_elem[operation_byte];
		अन्यथा
			mipi_elem_exec = शून्य;

		/* Size of Operation. */
		अगर (dev_priv->vbt.dsi.seq_version >= 3)
			operation_size = *data++;

		अगर (mipi_elem_exec) अणु
			स्थिर u8 *next = data + operation_size;

			data = mipi_elem_exec(पूर्णांकel_dsi, data);

			/* Consistency check अगर we have size. */
			अगर (operation_size && data != next) अणु
				drm_err(&dev_priv->drm,
					"Inconsistent operation size\n");
				वापस;
			पूर्ण
		पूर्ण अन्यथा अगर (operation_size) अणु
			/* We have size, skip. */
			drm_dbg_kms(&dev_priv->drm,
				    "Unsupported MIPI operation byte %u\n",
				    operation_byte);
			data += operation_size;
		पूर्ण अन्यथा अणु
			/* No size, can't skip without parsing. */
			drm_err(&dev_priv->drm,
				"Unsupported MIPI operation byte %u\n",
				operation_byte);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम पूर्णांकel_dsi_vbt_exec_sequence(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
				 क्रमागत mipi_seq seq_id)
अणु
	अगर (seq_id == MIPI_SEQ_POWER_ON && पूर्णांकel_dsi->gpio_panel)
		gpiod_set_value_cansleep(पूर्णांकel_dsi->gpio_panel, 1);
	अगर (seq_id == MIPI_SEQ_BACKLIGHT_ON && पूर्णांकel_dsi->gpio_backlight)
		gpiod_set_value_cansleep(पूर्णांकel_dsi->gpio_backlight, 1);

	पूर्णांकel_dsi_vbt_exec(पूर्णांकel_dsi, seq_id);

	अगर (seq_id == MIPI_SEQ_POWER_OFF && पूर्णांकel_dsi->gpio_panel)
		gpiod_set_value_cansleep(पूर्णांकel_dsi->gpio_panel, 0);
	अगर (seq_id == MIPI_SEQ_BACKLIGHT_OFF && पूर्णांकel_dsi->gpio_backlight)
		gpiod_set_value_cansleep(पूर्णांकel_dsi->gpio_backlight, 0);
पूर्ण

व्योम पूर्णांकel_dsi_msleep(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, पूर्णांक msec)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_dsi->base.base.dev);

	/* For v3 VBTs in vid-mode the delays are part of the VBT sequences */
	अगर (is_vid_mode(पूर्णांकel_dsi) && dev_priv->vbt.dsi.seq_version >= 3)
		वापस;

	msleep(msec);
पूर्ण

व्योम पूर्णांकel_dsi_log_params(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_dsi->base.base.dev);

	drm_dbg_kms(&i915->drm, "Pclk %d\n", पूर्णांकel_dsi->pclk);
	drm_dbg_kms(&i915->drm, "Pixel overlap %d\n",
		    पूर्णांकel_dsi->pixel_overlap);
	drm_dbg_kms(&i915->drm, "Lane count %d\n", पूर्णांकel_dsi->lane_count);
	drm_dbg_kms(&i915->drm, "DPHY param reg 0x%x\n", पूर्णांकel_dsi->dphy_reg);
	drm_dbg_kms(&i915->drm, "Video mode format %s\n",
		    पूर्णांकel_dsi->video_mode_क्रमmat == VIDEO_MODE_NON_BURST_WITH_SYNC_PULSE ?
		    "non-burst with sync pulse" :
		    पूर्णांकel_dsi->video_mode_क्रमmat == VIDEO_MODE_NON_BURST_WITH_SYNC_EVENTS ?
		    "non-burst with sync events" :
		    पूर्णांकel_dsi->video_mode_क्रमmat == VIDEO_MODE_BURST ?
		    "burst" : "<unknown>");
	drm_dbg_kms(&i915->drm, "Burst mode ratio %d\n",
		    पूर्णांकel_dsi->burst_mode_ratio);
	drm_dbg_kms(&i915->drm, "Reset timer %d\n", पूर्णांकel_dsi->rst_समयr_val);
	drm_dbg_kms(&i915->drm, "Eot %s\n",
		    enableddisabled(पूर्णांकel_dsi->eotp_pkt));
	drm_dbg_kms(&i915->drm, "Clockstop %s\n",
		    enableddisabled(!पूर्णांकel_dsi->घड़ी_stop));
	drm_dbg_kms(&i915->drm, "Mode %s\n",
		    पूर्णांकel_dsi->operation_mode ? "command" : "video");
	अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK)
		drm_dbg_kms(&i915->drm,
			    "Dual link: DSI_DUAL_LINK_FRONT_BACK\n");
	अन्यथा अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_PIXEL_ALT)
		drm_dbg_kms(&i915->drm,
			    "Dual link: DSI_DUAL_LINK_PIXEL_ALT\n");
	अन्यथा
		drm_dbg_kms(&i915->drm, "Dual link: NONE\n");
	drm_dbg_kms(&i915->drm, "Pixel Format %d\n", पूर्णांकel_dsi->pixel_क्रमmat);
	drm_dbg_kms(&i915->drm, "TLPX %d\n", पूर्णांकel_dsi->escape_clk_भाग);
	drm_dbg_kms(&i915->drm, "LP RX Timeout 0x%x\n",
		    पूर्णांकel_dsi->lp_rx_समयout);
	drm_dbg_kms(&i915->drm, "Turnaround Timeout 0x%x\n",
		    पूर्णांकel_dsi->turn_arnd_val);
	drm_dbg_kms(&i915->drm, "Init Count 0x%x\n", पूर्णांकel_dsi->init_count);
	drm_dbg_kms(&i915->drm, "HS to LP Count 0x%x\n",
		    पूर्णांकel_dsi->hs_to_lp_count);
	drm_dbg_kms(&i915->drm, "LP Byte Clock %d\n", पूर्णांकel_dsi->lp_byte_clk);
	drm_dbg_kms(&i915->drm, "DBI BW Timer 0x%x\n", पूर्णांकel_dsi->bw_समयr);
	drm_dbg_kms(&i915->drm, "LP to HS Clock Count 0x%x\n",
		    पूर्णांकel_dsi->clk_lp_to_hs_count);
	drm_dbg_kms(&i915->drm, "HS to LP Clock Count 0x%x\n",
		    पूर्णांकel_dsi->clk_hs_to_lp_count);
	drm_dbg_kms(&i915->drm, "BTA %s\n",
		    enableddisabled(!(पूर्णांकel_dsi->video_frmt_cfg_bits & DISABLE_VIDEO_BTA)));
पूर्ण

bool पूर्णांकel_dsi_vbt_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, u16 panel_id)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा mipi_config *mipi_config = dev_priv->vbt.dsi.config;
	काष्ठा mipi_pps_data *pps = dev_priv->vbt.dsi.pps;
	काष्ठा drm_display_mode *mode = dev_priv->vbt.lfp_lvds_vbt_mode;
	u16 burst_mode_ratio;
	क्रमागत port port;

	drm_dbg_kms(&dev_priv->drm, "\n");

	पूर्णांकel_dsi->eotp_pkt = mipi_config->eot_pkt_disabled ? 0 : 1;
	पूर्णांकel_dsi->घड़ी_stop = mipi_config->enable_clk_stop ? 1 : 0;
	पूर्णांकel_dsi->lane_count = mipi_config->lane_cnt + 1;
	पूर्णांकel_dsi->pixel_क्रमmat =
			pixel_क्रमmat_from_रेजिस्टर_bits(
				mipi_config->videomode_color_क्रमmat << 7);

	पूर्णांकel_dsi->dual_link = mipi_config->dual_link;
	पूर्णांकel_dsi->pixel_overlap = mipi_config->pixel_overlap;
	पूर्णांकel_dsi->operation_mode = mipi_config->is_cmd_mode;
	पूर्णांकel_dsi->video_mode_क्रमmat = mipi_config->video_transfer_mode;
	पूर्णांकel_dsi->escape_clk_भाग = mipi_config->byte_clk_sel;
	पूर्णांकel_dsi->lp_rx_समयout = mipi_config->lp_rx_समयout;
	पूर्णांकel_dsi->hs_tx_समयout = mipi_config->hs_tx_समयout;
	पूर्णांकel_dsi->turn_arnd_val = mipi_config->turn_around_समयout;
	पूर्णांकel_dsi->rst_समयr_val = mipi_config->device_reset_समयr;
	पूर्णांकel_dsi->init_count = mipi_config->master_init_समयr;
	पूर्णांकel_dsi->bw_समयr = mipi_config->dbi_bw_समयr;
	पूर्णांकel_dsi->video_frmt_cfg_bits =
		mipi_config->bta_enabled ? DISABLE_VIDEO_BTA : 0;
	पूर्णांकel_dsi->bgr_enabled = mipi_config->rgb_flip;

	/* Starting poपूर्णांक, adjusted depending on dual link and burst mode */
	पूर्णांकel_dsi->pclk = mode->घड़ी;

	/* In dual link mode each port needs half of pixel घड़ी */
	अगर (पूर्णांकel_dsi->dual_link) अणु
		पूर्णांकel_dsi->pclk /= 2;

		/* we can enable pixel_overlap अगर needed by panel. In this
		 * हाल we need to increase the pixelघड़ी क्रम extra pixels
		 */
		अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK) अणु
			पूर्णांकel_dsi->pclk += DIV_ROUND_UP(mode->vtotal * पूर्णांकel_dsi->pixel_overlap * 60, 1000);
		पूर्ण
	पूर्ण

	/* Burst Mode Ratio
	 * Target ddr frequency from VBT / non burst ddr freq
	 * multiply by 100 to preserve reमुख्यder
	 */
	अगर (पूर्णांकel_dsi->video_mode_क्रमmat == VIDEO_MODE_BURST) अणु
		अगर (mipi_config->target_burst_mode_freq) अणु
			u32 bitrate = पूर्णांकel_dsi_bitrate(पूर्णांकel_dsi);

			/*
			 * Someबार the VBT contains a slightly lower घड़ी,
			 * then the bitrate we have calculated, in this हाल
			 * just replace it with the calculated bitrate.
			 */
			अगर (mipi_config->target_burst_mode_freq < bitrate &&
			    पूर्णांकel_fuzzy_घड़ी_check(
					mipi_config->target_burst_mode_freq,
					bitrate))
				mipi_config->target_burst_mode_freq = bitrate;

			अगर (mipi_config->target_burst_mode_freq < bitrate) अणु
				drm_err(&dev_priv->drm,
					"Burst mode freq is less than computed\n");
				वापस false;
			पूर्ण

			burst_mode_ratio = DIV_ROUND_UP(
				mipi_config->target_burst_mode_freq * 100,
				bitrate);

			पूर्णांकel_dsi->pclk = DIV_ROUND_UP(पूर्णांकel_dsi->pclk * burst_mode_ratio, 100);
		पूर्ण अन्यथा अणु
			drm_err(&dev_priv->drm,
				"Burst mode target is not set\n");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा
		burst_mode_ratio = 100;

	पूर्णांकel_dsi->burst_mode_ratio = burst_mode_ratio;

	/* delays in VBT are in unit of 100us, so need to convert
	 * here in ms
	 * Delay (100us) * 100 /1000 = Delay / 10 (ms) */
	पूर्णांकel_dsi->backlight_off_delay = pps->bl_disable_delay / 10;
	पूर्णांकel_dsi->backlight_on_delay = pps->bl_enable_delay / 10;
	पूर्णांकel_dsi->panel_on_delay = pps->panel_on_delay / 10;
	पूर्णांकel_dsi->panel_off_delay = pps->panel_off_delay / 10;
	पूर्णांकel_dsi->panel_pwr_cycle_delay = pps->panel_घातer_cycle_delay / 10;

	पूर्णांकel_dsi->i2c_bus_num = -1;

	/* a regular driver would get the device in probe */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		mipi_dsi_attach(पूर्णांकel_dsi->dsi_hosts[port]->device);
	पूर्ण

	वापस true;
पूर्ण

/*
 * On some BYT/CHT devs some sequences are incomplete and we need to manually
 * control some GPIOs. We need to add a GPIO lookup table beक्रमe we get these.
 * If the GOP did not initialize the panel (HDMI inserted) we may need to also
 * change the pinmux क्रम the SoC's PWM0 pin from GPIO to PWM.
 */
अटल काष्ठा gpiod_lookup_table pmic_panel_gpio_table = अणु
	/* Intel GFX is consumer */
	.dev_id = "0000:00:02.0",
	.table = अणु
		/* Panel EN/DISABLE */
		GPIO_LOOKUP("gpio_crystalcove", 94, "panel", GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table soc_panel_gpio_table = अणु
	.dev_id = "0000:00:02.0",
	.table = अणु
		GPIO_LOOKUP("INT33FC:01", 10, "backlight", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("INT33FC:01", 11, "panel", GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_map soc_pwm_pinctrl_map[] = अणु
	PIN_MAP_MUX_GROUP("0000:00:02.0", "soc_pwm0", "INT33FC:00",
			  "pwm0_grp", "pwm"),
पूर्ण;

व्योम पूर्णांकel_dsi_vbt_gpio_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, bool panel_is_on)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा mipi_config *mipi_config = dev_priv->vbt.dsi.config;
	क्रमागत gpiod_flags flags = panel_is_on ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	bool want_backlight_gpio = false;
	bool want_panel_gpio = false;
	काष्ठा pinctrl *pinctrl;
	पूर्णांक ret;

	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    mipi_config->pwm_blc == PPS_BLC_PMIC) अणु
		gpiod_add_lookup_table(&pmic_panel_gpio_table);
		want_panel_gpio = true;
	पूर्ण

	अगर (IS_VALLEYVIEW(dev_priv) && mipi_config->pwm_blc == PPS_BLC_SOC) अणु
		gpiod_add_lookup_table(&soc_panel_gpio_table);
		want_panel_gpio = true;
		want_backlight_gpio = true;

		/* Ensure PWM0 pin is muxed as PWM instead of GPIO */
		ret = pinctrl_रेजिस्टर_mappings(soc_pwm_pinctrl_map,
					     ARRAY_SIZE(soc_pwm_pinctrl_map));
		अगर (ret)
			drm_err(&dev_priv->drm,
				"Failed to register pwm0 pinmux mapping\n");

		pinctrl = devm_pinctrl_get_select(dev->dev, "soc_pwm0");
		अगर (IS_ERR(pinctrl))
			drm_err(&dev_priv->drm,
				"Failed to set pinmux to PWM\n");
	पूर्ण

	अगर (want_panel_gpio) अणु
		पूर्णांकel_dsi->gpio_panel = gpiod_get(dev->dev, "panel", flags);
		अगर (IS_ERR(पूर्णांकel_dsi->gpio_panel)) अणु
			drm_err(&dev_priv->drm,
				"Failed to own gpio for panel control\n");
			पूर्णांकel_dsi->gpio_panel = शून्य;
		पूर्ण
	पूर्ण

	अगर (want_backlight_gpio) अणु
		पूर्णांकel_dsi->gpio_backlight =
			gpiod_get(dev->dev, "backlight", flags);
		अगर (IS_ERR(पूर्णांकel_dsi->gpio_backlight)) अणु
			drm_err(&dev_priv->drm,
				"Failed to own gpio for backlight control\n");
			पूर्णांकel_dsi->gpio_backlight = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम पूर्णांकel_dsi_vbt_gpio_cleanup(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा mipi_config *mipi_config = dev_priv->vbt.dsi.config;

	अगर (पूर्णांकel_dsi->gpio_panel) अणु
		gpiod_put(पूर्णांकel_dsi->gpio_panel);
		पूर्णांकel_dsi->gpio_panel = शून्य;
	पूर्ण

	अगर (पूर्णांकel_dsi->gpio_backlight) अणु
		gpiod_put(पूर्णांकel_dsi->gpio_backlight);
		पूर्णांकel_dsi->gpio_backlight = शून्य;
	पूर्ण

	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    mipi_config->pwm_blc == PPS_BLC_PMIC)
		gpiod_हटाओ_lookup_table(&pmic_panel_gpio_table);

	अगर (IS_VALLEYVIEW(dev_priv) && mipi_config->pwm_blc == PPS_BLC_SOC) अणु
		pinctrl_unरेजिस्टर_mappings(soc_pwm_pinctrl_map);
		gpiod_हटाओ_lookup_table(&soc_panel_gpio_table);
	पूर्ण
पूर्ण
