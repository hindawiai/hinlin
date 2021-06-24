<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/dmi.h>
#समावेश <linux/efi.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश "../../include/linux/atomisp_platform.h"
#समावेश "../../include/linux/atomisp_gmin_platform.h"

#घोषणा MAX_SUBDEVS 8

क्रमागत घड़ी_rate अणु
	VLV2_CLK_XTAL_25_0MHz = 0,
	VLV2_CLK_PLL_19P2MHZ = 1
पूर्ण;

#घोषणा CLK_RATE_19_2MHZ	19200000
#घोषणा CLK_RATE_25_0MHZ	25000000

/* Valid घड़ी number range from 0 to 5 */
#घोषणा MAX_CLK_COUNT                   5

/* X-Powers AXP288 रेजिस्टर set */
#घोषणा ALDO1_SEL_REG	0x28
#घोषणा ALDO1_CTRL3_REG	0x13
#घोषणा ALDO1_2P8V	0x16
#घोषणा ALDO1_CTRL3_SHIFT 0x05

#घोषणा ELDO_CTRL_REG   0x12

#घोषणा ELDO1_SEL_REG	0x19
#घोषणा ELDO1_1P8V	0x16
#घोषणा ELDO1_CTRL_SHIFT 0x00

#घोषणा ELDO2_SEL_REG	0x1a
#घोषणा ELDO2_1P8V	0x16
#घोषणा ELDO2_CTRL_SHIFT 0x01

/* TI SND9039 PMIC रेजिस्टर set */
#घोषणा LDO9_REG	0x49
#घोषणा LDO10_REG	0x4a
#घोषणा LDO11_REG	0x4b

#घोषणा LDO_2P8V_ON	0x2f /* 0x2e selects 2.85V ...      */
#घोषणा LDO_2P8V_OFF	0x2e /* ... bottom bit is "enabled" */

#घोषणा LDO_1P8V_ON	0x59 /* 0x58 selects 1.80V ...      */
#घोषणा LDO_1P8V_OFF	0x58 /* ... bottom bit is "enabled" */

/* CRYSTAL COVE PMIC रेजिस्टर set */
#घोषणा CRYSTAL_1P8V_REG	0x57
#घोषणा CRYSTAL_2P8V_REG	0x5d
#घोषणा CRYSTAL_ON		0x63
#घोषणा CRYSTAL_OFF		0x62

काष्ठा gmin_subdev अणु
	काष्ठा v4l2_subdev *subdev;
	क्रमागत घड़ी_rate घड़ी_src;
	काष्ठा clk *pmc_clk;
	काष्ठा gpio_desc *gpio0;
	काष्ठा gpio_desc *gpio1;
	काष्ठा regulator *v1p8_reg;
	काष्ठा regulator *v2p8_reg;
	काष्ठा regulator *v1p2_reg;
	काष्ठा regulator *v2p8_vcm_reg;
	क्रमागत atomisp_camera_port csi_port;
	अचिन्हित पूर्णांक csi_lanes;
	क्रमागत atomisp_input_क्रमmat csi_fmt;
	क्रमागत atomisp_bayer_order csi_bayer;

	bool घड़ी_on;
	bool v1p8_on;
	bool v2p8_on;
	bool v1p2_on;
	bool v2p8_vcm_on;

	पूर्णांक v1p8_gpio;
	पूर्णांक v2p8_gpio;

	u8 pwm_i2c_addr;

	/* For PMIC AXP */
	पूर्णांक elकरो1_sel_reg, elकरो1_1p8v, elकरो1_ctrl_shअगरt;
	पूर्णांक elकरो2_sel_reg, elकरो2_1p8v, elकरो2_ctrl_shअगरt;
पूर्ण;

अटल काष्ठा gmin_subdev gmin_subdevs[MAX_SUBDEVS];

/* ACPI HIDs क्रम the PMICs that could be used by this driver */
#घोषणा PMIC_ACPI_AXP		"INT33F4"	/* XPower AXP288 PMIC */
#घोषणा PMIC_ACPI_TI		"INT33F5"	/* Dollar Cove TI PMIC */
#घोषणा PMIC_ACPI_CRYSTALCOVE	"INT33FD"	/* Crystal Cove PMIC */

#घोषणा PMIC_PLATFORM_TI	"intel_soc_pmic_chtdc_ti"

अटल क्रमागत अणु
	PMIC_UNSET = 0,
	PMIC_REGULATOR,
	PMIC_AXP,
	PMIC_TI,
	PMIC_CRYSTALCOVE
पूर्ण pmic_id;

अटल स्थिर अक्षर *pmic_name[] = अणु
	[PMIC_UNSET]		= "ACPI device PM",
	[PMIC_REGULATOR]	= "regulator driver",
	[PMIC_AXP]		= "XPower AXP288 PMIC",
	[PMIC_TI]		= "Dollar Cove TI PMIC",
	[PMIC_CRYSTALCOVE]	= "Crystal Cove PMIC",
पूर्ण;

/* The atomisp uses type==0 क्रम the end-of-list marker, so leave space. */
अटल काष्ठा पूर्णांकel_v4l2_subdev_table pdata_subdevs[MAX_SUBDEVS + 1];

अटल स्थिर काष्ठा atomisp_platक्रमm_data pdata = अणु
	.subdevs = pdata_subdevs,
पूर्ण;

अटल LIST_HEAD(vcm_devices);
अटल DEFINE_MUTEX(vcm_lock);

अटल काष्ठा gmin_subdev *find_gmin_subdev(काष्ठा v4l2_subdev *subdev);

/*
 * Legacy/stub behavior copied from upstream platक्रमm_camera.c.  The
 * atomisp driver relies on these values being non-शून्य in a few
 * places, even though they are hard-coded in all current
 * implementations.
 */
स्थिर काष्ठा atomisp_camera_caps *atomisp_get_शेष_camera_caps(व्योम)
अणु
	अटल स्थिर काष्ठा atomisp_camera_caps caps = अणु
		.sensor_num = 1,
		.sensor = अणु
			अणु .stream_num = 1, पूर्ण,
		पूर्ण,
	पूर्ण;
	वापस &caps;
पूर्ण
EXPORT_SYMBOL_GPL(atomisp_get_शेष_camera_caps);

स्थिर काष्ठा atomisp_platक्रमm_data *atomisp_get_platक्रमm_data(व्योम)
अणु
	वापस &pdata;
पूर्ण
EXPORT_SYMBOL_GPL(atomisp_get_platक्रमm_data);

पूर्णांक atomisp_रेजिस्टर_i2c_module(काष्ठा v4l2_subdev *subdev,
				काष्ठा camera_sensor_platक्रमm_data *plat_data,
				क्रमागत पूर्णांकel_v4l2_subdev_type type)
अणु
	पूर्णांक i;
	काष्ठा i2c_board_info *bi;
	काष्ठा gmin_subdev *gs;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा acpi_device *adev = ACPI_COMPANION(&client->dev);

	dev_info(&client->dev, "register atomisp i2c module type %d\n", type);

	/* The winकरोws driver model (and thus most BIOSes by शेष)
	 * uses ACPI runसमय घातer management क्रम camera devices, but
	 * we करोn't.  Disable it, or अन्यथा the rails will be needlessly
	 * tickled during suspend/resume.  This has caused घातer and
	 * perक्रमmance issues on multiple devices.
	 */
	adev->घातer.flags.घातer_resources = 0;

	क्रम (i = 0; i < MAX_SUBDEVS; i++)
		अगर (!pdata.subdevs[i].type)
			अवरोध;

	अगर (pdata.subdevs[i].type)
		वापस -ENOMEM;

	/* Note subtlety of initialization order: at the poपूर्णांक where
	 * this registration API माला_लो called, the platक्रमm data
	 * callbacks have probably alपढ़ोy been invoked, so the
	 * gmin_subdev काष्ठा is alपढ़ोy initialized क्रम us.
	 */
	gs = find_gmin_subdev(subdev);
	अगर (!gs)
		वापस -ENODEV;

	pdata.subdevs[i].type = type;
	pdata.subdevs[i].port = gs->csi_port;
	pdata.subdevs[i].subdev = subdev;
	pdata.subdevs[i].v4l2_subdev.i2c_adapter_id = client->adapter->nr;

	/* Convert i2c_client to i2c_board_info */
	bi = &pdata.subdevs[i].v4l2_subdev.board_info;
	स_नकल(bi->type, client->name, I2C_NAME_SIZE);
	bi->flags = client->flags;
	bi->addr = client->addr;
	bi->irq = client->irq;
	bi->platक्रमm_data = plat_data;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(atomisp_रेजिस्टर_i2c_module);

काष्ठा v4l2_subdev *atomisp_gmin_find_subdev(काष्ठा i2c_adapter *adapter,
	काष्ठा i2c_board_info *board_info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_SUBDEVS && pdata.subdevs[i].type; i++) अणु
		काष्ठा पूर्णांकel_v4l2_subdev_table *sd = &pdata.subdevs[i];

		अगर (sd->v4l2_subdev.i2c_adapter_id == adapter->nr &&
		    sd->v4l2_subdev.board_info.addr == board_info->addr)
			वापस sd->subdev;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(atomisp_gmin_find_subdev);

पूर्णांक atomisp_gmin_हटाओ_subdev(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक i, j;

	अगर (!sd)
		वापस 0;

	क्रम (i = 0; i < MAX_SUBDEVS; i++) अणु
		अगर (pdata.subdevs[i].subdev == sd) अणु
			क्रम (j = i + 1; j <= MAX_SUBDEVS; j++)
				pdata.subdevs[j - 1] = pdata.subdevs[j];
		पूर्ण
		अगर (gmin_subdevs[i].subdev == sd) अणु
			अगर (gmin_subdevs[i].gpio0)
				gpiod_put(gmin_subdevs[i].gpio0);
			gmin_subdevs[i].gpio0 = शून्य;
			अगर (gmin_subdevs[i].gpio1)
				gpiod_put(gmin_subdevs[i].gpio1);
			gmin_subdevs[i].gpio1 = शून्य;
			अगर (pmic_id == PMIC_REGULATOR) अणु
				regulator_put(gmin_subdevs[i].v1p8_reg);
				regulator_put(gmin_subdevs[i].v2p8_reg);
				regulator_put(gmin_subdevs[i].v1p2_reg);
				regulator_put(gmin_subdevs[i].v2p8_vcm_reg);
			पूर्ण
			gmin_subdevs[i].subdev = शून्य;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(atomisp_gmin_हटाओ_subdev);

काष्ठा gmin_cfg_var अणु
	स्थिर अक्षर *name, *val;
पूर्ण;

अटल काष्ठा gmin_cfg_var ffrd8_vars[] = अणु
	अणु "INTCF1B:00_ImxId",    "0x134" पूर्ण,
	अणु "INTCF1B:00_CsiPort",  "1" पूर्ण,
	अणु "INTCF1B:00_CsiLanes", "4" पूर्ण,
	अणु "INTCF1B:00_CamClk", "0" पूर्ण,
	अणुपूर्ण,
पूर्ण;

/* Cribbed from MCG शेषs in the mt9m114 driver, not actually verअगरied
 * vs. T100 hardware
 */
अटल काष्ठा gmin_cfg_var t100_vars[] = अणु
	अणु "INT33F0:00_CsiPort",  "0" पूर्ण,
	अणु "INT33F0:00_CsiLanes", "1" पूर्ण,
	अणु "INT33F0:00_CamClk",   "1" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा gmin_cfg_var mrd7_vars[] = अणु
	अणु"INT33F8:00_CamType", "1"पूर्ण,
	अणु"INT33F8:00_CsiPort", "1"पूर्ण,
	अणु"INT33F8:00_CsiLanes", "2"पूर्ण,
	अणु"INT33F8:00_CsiFmt", "13"पूर्ण,
	अणु"INT33F8:00_CsiBayer", "0"पूर्ण,
	अणु"INT33F8:00_CamClk", "0"पूर्ण,

	अणु"INT33F9:00_CamType", "1"पूर्ण,
	अणु"INT33F9:00_CsiPort", "0"पूर्ण,
	अणु"INT33F9:00_CsiLanes", "1"पूर्ण,
	अणु"INT33F9:00_CsiFmt", "13"पूर्ण,
	अणु"INT33F9:00_CsiBayer", "0"पूर्ण,
	अणु"INT33F9:00_CamClk", "1"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा gmin_cfg_var ecs7_vars[] = अणु
	अणु"INT33BE:00_CsiPort", "1"पूर्ण,
	अणु"INT33BE:00_CsiLanes", "2"पूर्ण,
	अणु"INT33BE:00_CsiFmt", "13"पूर्ण,
	अणु"INT33BE:00_CsiBayer", "2"पूर्ण,
	अणु"INT33BE:00_CamClk", "0"पूर्ण,

	अणु"INT33F0:00_CsiPort", "0"पूर्ण,
	अणु"INT33F0:00_CsiLanes", "1"पूर्ण,
	अणु"INT33F0:00_CsiFmt", "13"पूर्ण,
	अणु"INT33F0:00_CsiBayer", "0"पूर्ण,
	अणु"INT33F0:00_CamClk", "1"पूर्ण,
	अणु"gmin_V2P8GPIO", "402"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा gmin_cfg_var i8880_vars[] = अणु
	अणु"XXOV2680:00_CsiPort", "1"पूर्ण,
	अणु"XXOV2680:00_CsiLanes", "1"पूर्ण,
	अणु"XXOV2680:00_CamClk", "0"पूर्ण,

	अणु"XXGC0310:00_CsiPort", "0"पूर्ण,
	अणु"XXGC0310:00_CsiLanes", "1"पूर्ण,
	अणु"XXGC0310:00_CamClk", "1"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id gmin_vars[] = अणु
	अणु
		.ident = "BYT-T FFD8",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "BYT-T FFD8"),
		पूर्ण,
		.driver_data = ffrd8_vars,
	पूर्ण,
	अणु
		.ident = "T100TA",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "T100TA"),
		पूर्ण,
		.driver_data = t100_vars,
	पूर्ण,
	अणु
		.ident = "MRD7",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "TABLET"),
			DMI_MATCH(DMI_BOARD_VERSION, "MRD 7"),
		पूर्ण,
		.driver_data = mrd7_vars,
	पूर्ण,
	अणु
		.ident = "ST70408",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "ST70408"),
		पूर्ण,
		.driver_data = ecs7_vars,
	पूर्ण,
	अणु
		.ident = "VTA0803",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VTA0803"),
		पूर्ण,
		.driver_data = i8880_vars,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

#घोषणा GMIN_CFG_VAR_EFI_GUID EFI_GUID(0xecb54cd9, 0xe5ae, 0x4fdc, \
				       0xa9, 0x71, 0xe8, 0x77,	   \
				       0x75, 0x60, 0x68, 0xf7)

अटल स्थिर guid_t atomisp_dsm_guid = GUID_INIT(0xdc2f6c4f, 0x045b, 0x4f1d,
						 0x97, 0xb9, 0x88, 0x2a,
						 0x68, 0x60, 0xa4, 0xbe);

#घोषणा CFG_VAR_NAME_MAX 64

#घोषणा GMIN_PMC_CLK_NAME 14 /* "pmc_plt_clk_[0..5]" */
अटल अक्षर gmin_pmc_clk_name[GMIN_PMC_CLK_NAME];

अटल काष्ठा i2c_client *gmin_i2c_dev_exists(काष्ठा device *dev, अक्षर *name,
					      काष्ठा i2c_client **client)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा device *d;

	adev = acpi_dev_get_first_match_dev(name, शून्य, -1);
	अगर (!adev)
		वापस शून्य;

	d = bus_find_device_by_acpi_dev(&i2c_bus_type, adev);
	acpi_dev_put(adev);
	अगर (!d)
		वापस शून्य;

	*client = i2c_verअगरy_client(d);
	put_device(d);

	dev_dbg(dev, "found '%s' at address 0x%02x, adapter %d\n",
		(*client)->name, (*client)->addr, (*client)->adapter->nr);
	वापस *client;
पूर्ण

अटल पूर्णांक gmin_i2c_ग_लिखो(काष्ठा device *dev, u16 i2c_addr, u8 reg,
			  u32 value, u32 mask)
अणु
	पूर्णांक ret;

	/*
	 * FIXME: Right now, the पूर्णांकel_pmic driver just ग_लिखो values
	 * directly at the regmap, instead of properly implementing
	 * i2c_transfer() mechanism. Let's use the same पूर्णांकerface here,
	 * as otherwise we may face issues.
	 */

	dev_dbg(dev,
		"I2C write, addr: 0x%02x, reg: 0x%02x, value: 0x%02x, mask: 0x%02x\n",
		i2c_addr, reg, value, mask);

	ret = पूर्णांकel_soc_pmic_exec_mipi_pmic_seq_element(i2c_addr, reg, value, mask);
	अगर (ret == -EOPNOTSUPP)
		dev_err(dev,
			"ACPI didn't mapped the OpRegion needed to access I2C address 0x%02x.\n"
			"Need to compile the kernel using CONFIG_*_PMIC_OPREGION settings\n",
			i2c_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_get_acpi_घातer(काष्ठा device *dev)
अणु
	अक्षर name[5];
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer b_name = अणु माप(name), name पूर्ण;
	जोड़ acpi_object *package, *element;
	acpi_handle handle = ACPI_HANDLE(dev);
	acpi_handle rhandle;
	acpi_status status;
	पूर्णांक घड़ी_num = -1;
	पूर्णांक i;

	status = acpi_evaluate_object(handle, "_PR0", शून्य, &buffer);
	अगर (!ACPI_SUCCESS(status))
		वापस -1;

	package = buffer.poपूर्णांकer;

	अगर (!buffer.length || !package
	    || package->type != ACPI_TYPE_PACKAGE
	    || !package->package.count)
		जाओ fail;

	क्रम (i = 0; i < package->package.count; i++) अणु
		element = &package->package.elements[i];

		अगर (element->type != ACPI_TYPE_LOCAL_REFERENCE)
			जारी;

		rhandle = element->reference.handle;
		अगर (!rhandle)
			जाओ fail;

		acpi_get_name(rhandle, ACPI_SINGLE_NAME, &b_name);

		dev_dbg(dev, "Found PM resource '%s'\n", name);
		अगर (म_माप(name) == 4 && !म_भेदन(name, "CLK", 3)) अणु
			अगर (name[3] >= '0' && name[3] <= '4')
				घड़ी_num = name[3] - '0';
#अगर 0
			/*
			 * We could पात here, but let's parse all resources,
			 * as this is helpful क्रम debugging purposes
			 */
			अगर (घड़ी_num >= 0)
				अवरोध;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

fail:
	ACPI_FREE(buffer.poपूर्णांकer);

	वापस घड़ी_num;
पूर्ण

अटल u8 gmin_get_pmic_id_and_addr(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *घातer;
	अटल u8 pmic_i2c_addr;

	अगर (pmic_id)
		वापस pmic_i2c_addr;

	अगर (gmin_i2c_dev_exists(dev, PMIC_ACPI_TI, &घातer))
		pmic_id = PMIC_TI;
	अन्यथा अगर (gmin_i2c_dev_exists(dev, PMIC_ACPI_AXP, &घातer))
		pmic_id = PMIC_AXP;
	अन्यथा अगर (gmin_i2c_dev_exists(dev, PMIC_ACPI_CRYSTALCOVE, &घातer))
		pmic_id = PMIC_CRYSTALCOVE;
	अन्यथा
		pmic_id = PMIC_REGULATOR;

	pmic_i2c_addr = घातer ? घातer->addr : 0;
	वापस pmic_i2c_addr;
पूर्ण

अटल पूर्णांक gmin_detect_pmic(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा device *dev = &client->dev;
	u8 pmic_i2c_addr;

	pmic_i2c_addr = gmin_get_pmic_id_and_addr(dev);
	dev_info(dev, "gmin: power management provided via %s (i2c addr 0x%02x)\n",
		 pmic_name[pmic_id], pmic_i2c_addr);
	वापस pmic_i2c_addr;
पूर्ण

अटल पूर्णांक gmin_subdev_add(काष्ठा gmin_subdev *gs)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(gs->subdev);
	काष्ठा device *dev = &client->dev;
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	पूर्णांक ret, घड़ी_num = -1;

	dev_info(dev, "%s: ACPI path is %pfw\n", __func__, dev_fwnode(dev));

	/*WA:CHT requires XTAL घड़ी as PLL is not stable.*/
	gs->घड़ी_src = gmin_get_var_पूर्णांक(dev, false, "ClkSrc",
				         VLV2_CLK_PLL_19P2MHZ);

	gs->csi_port = gmin_get_var_पूर्णांक(dev, false, "CsiPort", 0);
	gs->csi_lanes = gmin_get_var_पूर्णांक(dev, false, "CsiLanes", 1);

	gs->gpio0 = gpiod_get_index(dev, शून्य, 0, GPIOD_OUT_LOW);
	अगर (IS_ERR(gs->gpio0))
		gs->gpio0 = शून्य;
	अन्यथा
		dev_info(dev, "will handle gpio0 via ACPI\n");

	gs->gpio1 = gpiod_get_index(dev, शून्य, 1, GPIOD_OUT_LOW);
	अगर (IS_ERR(gs->gpio1))
		gs->gpio1 = शून्य;
	अन्यथा
		dev_info(dev, "will handle gpio1 via ACPI\n");

	/*
	 * Those are used only when there is an बाह्यal regulator apart
	 * from the PMIC that would be providing घातer supply, like on the
	 * two हालs below:
	 *
	 * The ECS E7 board drives camera 2.8v from an बाह्यal regulator
	 * instead of the PMIC.  There's a gmin_CamV2P8 config variable
	 * that specअगरies the GPIO to handle this particular हाल,
	 * but this needs a broader architecture क्रम handling camera घातer.
	 *
	 * The CHT RVP board drives camera 1.8v from an* बाह्यal regulator
	 * instead of the PMIC just like ECS E7 board.
	 */

	gs->v1p8_gpio = gmin_get_var_पूर्णांक(dev, true, "V1P8GPIO", -1);
	gs->v2p8_gpio = gmin_get_var_पूर्णांक(dev, true, "V2P8GPIO", -1);

	/*
	 * FIXME:
	 *
	 * The ACPI handling code checks क्रम the _PR? tables in order to
	 * know what is required to चयन the device from घातer state
	 * D0 (_PR0) up to D3COLD (_PR3).
	 *
	 * The adev->flags.घातer_manageable is set to true अगर the device
	 * has a _PR0 table, which can be checked by calling
	 * acpi_device_घातer_manageable(adev).
	 *
	 * However, this only says that the device can be set to घातer off
	 * mode.
	 *
	 * At least on the DSDT tables we've seen so far, there's no _PR3,
	 * nor _PS3 (which would have a somewhat similar effect).
	 * So, using ACPI क्रम घातer management won't work, except अगर adding
	 * an ACPI override logic somewhere.
	 *
	 * So, at least क्रम the existing devices we know, the check below
	 * will always be false.
	 */
	अगर (acpi_device_can_wakeup(adev) &&
	    acpi_device_can_घातeroff(adev)) अणु
		dev_info(dev,
			 "gmin: power management provided via device PM\n");
		वापस 0;
	पूर्ण

	/*
	 * The code below is here due to backward compatibility with devices
	 * whose ACPI BIOS may not contain everything that would be needed
	 * in order to set घड़ीs and करो घातer management.
	 */

	/*
	 * According with :
	 *   https://github.com/projectcelaकरोn/hardware-पूर्णांकel-kernelflinger/blob/master/करोc/fastboot.md
	 *
	 * The "CamClk" EFI var is set via fastboot on some Android devices,
	 * and seems to contain the number of the घड़ी used to feed the
	 * sensor.
	 *
	 * On प्रणालीs with a proper ACPI table, this is given via the _PR0
	 * घातer resource table. The logic below should first check अगर there
	 * is a घातer resource alपढ़ोy, falling back to the EFI vars detection
	 * otherwise.
	 */

	/* Try first to use ACPI to get the घड़ी resource */
	अगर (acpi_device_घातer_manageable(adev))
		घड़ी_num = atomisp_get_acpi_घातer(dev);

	/* Fall-back use EFI and/or DMI match */
	अगर (घड़ी_num < 0)
		घड़ी_num = gmin_get_var_पूर्णांक(dev, false, "CamClk", 0);

	अगर (घड़ी_num < 0 || घड़ी_num > MAX_CLK_COUNT) अणु
		dev_err(dev, "Invalid clock number\n");
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(gmin_pmc_clk_name, माप(gmin_pmc_clk_name),
		 "%s_%d", "pmc_plt_clk", घड़ी_num);

	gs->pmc_clk = devm_clk_get(dev, gmin_pmc_clk_name);
	अगर (IS_ERR(gs->pmc_clk)) अणु
		ret = PTR_ERR(gs->pmc_clk);
		dev_err(dev, "Failed to get clk from %s: %d\n", gmin_pmc_clk_name, ret);
		वापस ret;
	पूर्ण
	dev_info(dev, "Will use CLK%d (%s)\n", घड़ी_num, gmin_pmc_clk_name);

	/*
	 * The firmware might enable the घड़ी at
	 * boot (this inक्रमmation may or may not
	 * be reflected in the enable घड़ी रेजिस्टर).
	 * To change the rate we must disable the घड़ी
	 * first to cover these हालs. Due to common
	 * घड़ी framework restrictions that करो not allow
	 * to disable a घड़ी that has not been enabled,
	 * we need to enable the घड़ी first.
	 */
	ret = clk_prepare_enable(gs->pmc_clk);
	अगर (!ret)
		clk_disable_unprepare(gs->pmc_clk);

	चयन (pmic_id) अणु
	हाल PMIC_REGULATOR:
		gs->v1p8_reg = regulator_get(dev, "V1P8SX");
		gs->v2p8_reg = regulator_get(dev, "V2P8SX");

		gs->v1p2_reg = regulator_get(dev, "V1P2A");
		gs->v2p8_vcm_reg = regulator_get(dev, "VPROG4B");

		/* Note: ideally we would initialize v[12]p8_on to the
		 * output of regulator_is_enabled(), but sadly that
		 * API is broken with the current drivers, वापसing
		 * "1" क्रम a regulator that will then emit a
		 * "unbalanced disable" WARNing अगर we try to disable
		 * it.
		 */
		अवरोध;

	हाल PMIC_AXP:
		gs->elकरो1_1p8v = gmin_get_var_पूर्णांक(dev, false,
						  "eldo1_1p8v",
						  ELDO1_1P8V);
		gs->elकरो1_sel_reg = gmin_get_var_पूर्णांक(dev, false,
						     "eldo1_sel_reg",
						     ELDO1_SEL_REG);
		gs->elकरो1_ctrl_shअगरt = gmin_get_var_पूर्णांक(dev, false,
							"eldo1_ctrl_shift",
							ELDO1_CTRL_SHIFT);
		gs->elकरो2_1p8v = gmin_get_var_पूर्णांक(dev, false,
						  "eldo2_1p8v",
						  ELDO2_1P8V);
		gs->elकरो2_sel_reg = gmin_get_var_पूर्णांक(dev, false,
						     "eldo2_sel_reg",
						     ELDO2_SEL_REG);
		gs->elकरो2_ctrl_shअगरt = gmin_get_var_पूर्णांक(dev, false,
							"eldo2_ctrl_shift",
							ELDO2_CTRL_SHIFT);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा gmin_subdev *find_gmin_subdev(काष्ठा v4l2_subdev *subdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_SUBDEVS; i++)
		अगर (gmin_subdevs[i].subdev == subdev)
			वापस &gmin_subdevs[i];
	वापस शून्य;
पूर्ण

अटल काष्ठा gmin_subdev *find_मुक्त_gmin_subdev_slot(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_SUBDEVS; i++)
		अगर (gmin_subdevs[i].subdev == शून्य)
			वापस &gmin_subdevs[i];
	वापस शून्य;
पूर्ण

अटल पूर्णांक axp_regulator_set(काष्ठा device *dev, काष्ठा gmin_subdev *gs,
			     पूर्णांक sel_reg, u8 setting,
			     पूर्णांक ctrl_reg, पूर्णांक shअगरt, bool on)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	ret = gmin_i2c_ग_लिखो(dev, gs->pwm_i2c_addr, sel_reg, setting, 0xff);
	अगर (ret)
		वापस ret;

	val = on ? 1 << shअगरt : 0;

	ret = gmin_i2c_ग_लिखो(dev, gs->pwm_i2c_addr, sel_reg, val, 1 << shअगरt);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक axp_v1p8_on(काष्ठा device *dev, काष्ठा gmin_subdev *gs)
अणु
	पूर्णांक ret;

	ret = axp_regulator_set(dev, gs, gs->elकरो2_sel_reg, gs->elकरो2_1p8v,
				ELDO_CTRL_REG, gs->elकरो2_ctrl_shअगरt, true);
	अगर (ret)
		वापस ret;

	/*
	 * This sleep comes out of the gc2235 driver, which is the
	 * only one I currently see that wants to set both 1.8v rails.
	 */
	usleep_range(110, 150);

	ret = axp_regulator_set(dev, gs, gs->elकरो1_sel_reg, gs->elकरो1_1p8v,
		ELDO_CTRL_REG, gs->elकरो1_ctrl_shअगरt, true);
	अगर (ret)
		वापस ret;

	ret = axp_regulator_set(dev, gs, gs->elकरो2_sel_reg, gs->elकरो2_1p8v,
				ELDO_CTRL_REG, gs->elकरो2_ctrl_shअगरt, false);
	वापस ret;
पूर्ण

अटल पूर्णांक axp_v1p8_off(काष्ठा device *dev, काष्ठा gmin_subdev *gs)
अणु
	पूर्णांक ret;

	ret = axp_regulator_set(dev, gs, gs->elकरो1_sel_reg, gs->elकरो1_1p8v,
				ELDO_CTRL_REG, gs->elकरो1_ctrl_shअगरt, false);
	अगर (ret)
		वापस ret;

	ret = axp_regulator_set(dev, gs, gs->elकरो2_sel_reg, gs->elकरो2_1p8v,
				ELDO_CTRL_REG, gs->elकरो2_ctrl_shअगरt, false);
	वापस ret;
पूर्ण

अटल पूर्णांक gmin_gpio0_ctrl(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);

	अगर (gs) अणु
		gpiod_set_value(gs->gpio0, on);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gmin_gpio1_ctrl(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);

	अगर (gs) अणु
		gpiod_set_value(gs->gpio1, on);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gmin_v1p2_ctrl(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);

	अगर (!gs || gs->v1p2_on == on)
		वापस 0;
	gs->v1p2_on = on;

	/* use regulator क्रम PMIC */
	अगर (gs->v1p2_reg) अणु
		अगर (on)
			वापस regulator_enable(gs->v1p2_reg);
		अन्यथा
			वापस regulator_disable(gs->v1p2_reg);
	पूर्ण

	/* TODO:v1p2 may need to extend to other PMICs */

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gmin_v1p8_ctrl(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);
	पूर्णांक ret;
	पूर्णांक value;

	अगर (!gs || gs->v1p8_on == on)
		वापस 0;

	अगर (gs->v1p8_gpio >= 0) अणु
		pr_info("atomisp_gmin_platform: 1.8v power on GPIO %d\n",
			gs->v1p8_gpio);
		ret = gpio_request(gs->v1p8_gpio, "camera_v1p8_en");
		अगर (!ret)
			ret = gpio_direction_output(gs->v1p8_gpio, 0);
		अगर (ret)
			pr_err("V1P8 GPIO initialization failed\n");
	पूर्ण

	gs->v1p8_on = on;

	अगर (gs->v1p8_gpio >= 0)
		gpio_set_value(gs->v1p8_gpio, on);

	अगर (gs->v1p8_reg) अणु
		regulator_set_voltage(gs->v1p8_reg, 1800000, 1800000);
		अगर (on)
			वापस regulator_enable(gs->v1p8_reg);
		अन्यथा
			वापस regulator_disable(gs->v1p8_reg);
	पूर्ण

	चयन (pmic_id) अणु
	हाल PMIC_AXP:
		अगर (on)
			वापस axp_v1p8_on(subdev->dev, gs);
		अन्यथा
			वापस axp_v1p8_off(subdev->dev, gs);
	हाल PMIC_TI:
		value = on ? LDO_1P8V_ON : LDO_1P8V_OFF;

		वापस gmin_i2c_ग_लिखो(subdev->dev, gs->pwm_i2c_addr,
				      LDO10_REG, value, 0xff);
	हाल PMIC_CRYSTALCOVE:
		value = on ? CRYSTAL_ON : CRYSTAL_OFF;

		वापस gmin_i2c_ग_लिखो(subdev->dev, gs->pwm_i2c_addr,
				      CRYSTAL_1P8V_REG, value, 0xff);
	शेष:
		dev_err(subdev->dev, "Couldn't set power mode for v1p2\n");
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gmin_v2p8_ctrl(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);
	पूर्णांक ret;
	पूर्णांक value;

	अगर (WARN_ON(!gs))
		वापस -ENODEV;

	अगर (gs->v2p8_gpio >= 0) अणु
		pr_info("atomisp_gmin_platform: 2.8v power on GPIO %d\n",
			gs->v2p8_gpio);
		ret = gpio_request(gs->v2p8_gpio, "camera_v2p8");
		अगर (!ret)
			ret = gpio_direction_output(gs->v2p8_gpio, 0);
		अगर (ret)
			pr_err("V2P8 GPIO initialization failed\n");
	पूर्ण

	अगर (gs->v2p8_on == on)
		वापस 0;
	gs->v2p8_on = on;

	अगर (gs->v2p8_gpio >= 0)
		gpio_set_value(gs->v2p8_gpio, on);

	अगर (gs->v2p8_reg) अणु
		regulator_set_voltage(gs->v2p8_reg, 2900000, 2900000);
		अगर (on)
			वापस regulator_enable(gs->v2p8_reg);
		अन्यथा
			वापस regulator_disable(gs->v2p8_reg);
	पूर्ण

	चयन (pmic_id) अणु
	हाल PMIC_AXP:
		वापस axp_regulator_set(subdev->dev, gs, ALDO1_SEL_REG,
					 ALDO1_2P8V, ALDO1_CTRL3_REG,
					 ALDO1_CTRL3_SHIFT, on);
	हाल PMIC_TI:
		value = on ? LDO_2P8V_ON : LDO_2P8V_OFF;

		वापस gmin_i2c_ग_लिखो(subdev->dev, gs->pwm_i2c_addr,
				      LDO9_REG, value, 0xff);
	हाल PMIC_CRYSTALCOVE:
		value = on ? CRYSTAL_ON : CRYSTAL_OFF;

		वापस gmin_i2c_ग_लिखो(subdev->dev, gs->pwm_i2c_addr,
				      CRYSTAL_2P8V_REG, value, 0xff);
	शेष:
		dev_err(subdev->dev, "Couldn't set power mode for v1p2\n");
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gmin_acpi_pm_ctrl(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	पूर्णांक ret = 0;
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा acpi_device *adev = ACPI_COMPANION(&client->dev);

	/* Use the ACPI घातer management to control it */
	on = !!on;
	अगर (gs->घड़ी_on == on)
		वापस 0;

	dev_dbg(subdev->dev, "Setting power state to %s\n",
		on ? "on" : "off");

	अगर (on)
		ret = acpi_device_set_घातer(adev,
					    ACPI_STATE_D0);
	अन्यथा
		ret = acpi_device_set_घातer(adev,
					    ACPI_STATE_D3_COLD);

	अगर (!ret)
		gs->घड़ी_on = on;
	अन्यथा
		dev_err(subdev->dev, "Couldn't set power state to %s\n",
			on ? "on" : "off");

	वापस ret;
पूर्ण

अटल पूर्णांक gmin_flisclk_ctrl(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	पूर्णांक ret = 0;
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);

	अगर (gs->घड़ी_on == !!on)
		वापस 0;

	अगर (on) अणु
		ret = clk_set_rate(gs->pmc_clk,
				   gs->घड़ी_src ? CLK_RATE_19_2MHZ : CLK_RATE_25_0MHZ);

		अगर (ret)
			dev_err(&client->dev, "unable to set PMC rate %d\n",
				gs->घड़ी_src);

		ret = clk_prepare_enable(gs->pmc_clk);
		अगर (ret == 0)
			gs->घड़ी_on = true;
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(gs->pmc_clk);
		gs->घड़ी_on = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gmin_csi_cfg(काष्ठा v4l2_subdev *sd, पूर्णांक flag)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा gmin_subdev *gs = find_gmin_subdev(sd);

	अगर (!client || !gs)
		वापस -ENODEV;

	वापस camera_sensor_csi(sd, gs->csi_port, gs->csi_lanes,
				 gs->csi_fmt, gs->csi_bayer, flag);
पूर्ण

अटल काष्ठा camera_vcm_control *gmin_get_vcm_ctrl(काष्ठा v4l2_subdev *subdev,
	अक्षर *camera_module)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा gmin_subdev *gs = find_gmin_subdev(subdev);
	काष्ठा camera_vcm_control *vcm;

	अगर (!client || !gs)
		वापस शून्य;

	अगर (!camera_module)
		वापस शून्य;

	mutex_lock(&vcm_lock);
	list_क्रम_each_entry(vcm, &vcm_devices, list) अणु
		अगर (!म_भेद(camera_module, vcm->camera_module)) अणु
			mutex_unlock(&vcm_lock);
			वापस vcm;
		पूर्ण
	पूर्ण

	mutex_unlock(&vcm_lock);
	वापस शून्य;
पूर्ण

अटल काष्ठा camera_sensor_platक्रमm_data pmic_gmin_plat = अणु
	.gpio0_ctrl = gmin_gpio0_ctrl,
	.gpio1_ctrl = gmin_gpio1_ctrl,
	.v1p8_ctrl = gmin_v1p8_ctrl,
	.v2p8_ctrl = gmin_v2p8_ctrl,
	.v1p2_ctrl = gmin_v1p2_ctrl,
	.flisclk_ctrl = gmin_flisclk_ctrl,
	.csi_cfg = gmin_csi_cfg,
	.get_vcm_ctrl = gmin_get_vcm_ctrl,
पूर्ण;

अटल काष्ठा camera_sensor_platक्रमm_data acpi_gmin_plat = अणु
	.gpio0_ctrl = gmin_gpio0_ctrl,
	.gpio1_ctrl = gmin_gpio1_ctrl,
	.v1p8_ctrl = gmin_acpi_pm_ctrl,
	.v2p8_ctrl = gmin_acpi_pm_ctrl,
	.v1p2_ctrl = gmin_acpi_pm_ctrl,
	.flisclk_ctrl = gmin_acpi_pm_ctrl,
	.csi_cfg = gmin_csi_cfg,
	.get_vcm_ctrl = gmin_get_vcm_ctrl,
पूर्ण;

काष्ठा camera_sensor_platक्रमm_data *gmin_camera_platक्रमm_data(
    काष्ठा v4l2_subdev *subdev,
    क्रमागत atomisp_input_क्रमmat csi_क्रमmat,
    क्रमागत atomisp_bayer_order csi_bayer)
अणु
	u8 pmic_i2c_addr = gmin_detect_pmic(subdev);
	काष्ठा gmin_subdev *gs;

	gs = find_मुक्त_gmin_subdev_slot();
	gs->subdev = subdev;
	gs->csi_fmt = csi_क्रमmat;
	gs->csi_bayer = csi_bayer;
	gs->pwm_i2c_addr = pmic_i2c_addr;

	gmin_subdev_add(gs);
	अगर (gs->pmc_clk)
		वापस &pmic_gmin_plat;
	अन्यथा
		वापस &acpi_gmin_plat;
पूर्ण
EXPORT_SYMBOL_GPL(gmin_camera_platक्रमm_data);

पूर्णांक atomisp_gmin_रेजिस्टर_vcm_control(काष्ठा camera_vcm_control *vcmCtrl)
अणु
	अगर (!vcmCtrl)
		वापस -EINVAL;

	mutex_lock(&vcm_lock);
	list_add_tail(&vcmCtrl->list, &vcm_devices);
	mutex_unlock(&vcm_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(atomisp_gmin_रेजिस्टर_vcm_control);

अटल पूर्णांक gmin_get_hardcoded_var(काष्ठा device *dev,
				  काष्ठा gmin_cfg_var *varlist,
				  स्थिर अक्षर *var8, अक्षर *out, माप_प्रकार *out_len)
अणु
	काष्ठा gmin_cfg_var *gv;

	क्रम (gv = varlist; gv->name; gv++) अणु
		माप_प्रकार vl;

		अगर (म_भेद(var8, gv->name))
			जारी;

		dev_info(dev, "Found DMI entry for '%s'\n", var8);

		vl = म_माप(gv->val);
		अगर (vl > *out_len - 1)
			वापस -ENOSPC;

		strscpy(out, gv->val, *out_len);
		*out_len = vl;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक gmin_get_config_dsm_var(काष्ठा device *dev,
				   स्थिर अक्षर *var,
				   अक्षर *out, माप_प्रकार *out_len)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object *obj, *cur = शून्य;
	पूर्णांक i;

	/*
	 * The data reported by "CamClk" seems to be either 0 or 1 at the
	 * _DSM table.
	 *
	 * At the ACPI tables we looked so far, this is not related to the
	 * actual घड़ी source क्रम the sensor, which is given by the
	 * _PR0 ACPI table. So, ignore it, as otherwise this will be
	 * set to a wrong value.
	 */
	अगर (!म_भेद(var, "CamClk"))
		वापस -EINVAL;

	obj = acpi_evaluate_dsm(handle, &atomisp_dsm_guid, 0, 0, शून्य);
	अगर (!obj) अणु
		dev_info_once(dev, "Didn't find ACPI _DSM table.\n");
		वापस -EINVAL;
	पूर्ण

	/* Return on unexpected object type */
	अगर (obj->type != ACPI_TYPE_PACKAGE)
		वापस -EINVAL;

#अगर 0 /* Just क्रम debugging purposes */
	क्रम (i = 0; i < obj->package.count; i++) अणु
		जोड़ acpi_object *cur = &obj->package.elements[i];

		अगर (cur->type == ACPI_TYPE_INTEGER)
			dev_info(dev, "object #%d, type %d, value: %lld\n",
				 i, cur->type, cur->पूर्णांकeger.value);
		अन्यथा अगर (cur->type == ACPI_TYPE_STRING)
			dev_info(dev, "object #%d, type %d, string: %s\n",
				 i, cur->type, cur->string.poपूर्णांकer);
		अन्यथा
			dev_info(dev, "object #%d, type %d\n",
				 i, cur->type);
	पूर्ण
#पूर्ण_अगर

	/* Seek क्रम the desired var */
	क्रम (i = 0; i < obj->package.count - 1; i += 2) अणु
		अगर (obj->package.elements[i].type == ACPI_TYPE_STRING &&
		    !म_भेद(obj->package.elements[i].string.poपूर्णांकer, var)) अणु
			/* Next element should be the required value */
			cur = &obj->package.elements[i + 1];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!cur) अणु
		dev_info(dev, "didn't found _DSM entry for '%s'\n", var);
		ACPI_FREE(obj);
		वापस -EINVAL;
	पूर्ण

	/*
	 * While it could be possible to have an ACPI_TYPE_INTEGER,
	 * and पढ़ो the value from cur->पूर्णांकeger.value, the table
	 * seen so far uses the string type. So, produce a warning
	 * अगर it founds something dअगरferent than string, letting it
	 * to fall back to the old code.
	 */
	अगर (cur && cur->type != ACPI_TYPE_STRING) अणु
		dev_info(dev, "found non-string _DSM entry for '%s'\n", var);
		ACPI_FREE(obj);
		वापस -EINVAL;
	पूर्ण

	dev_info(dev, "found _DSM entry for '%s': %s\n", var,
		 cur->string.poपूर्णांकer);
	strscpy(out, cur->string.poपूर्णांकer, *out_len);
	*out_len = म_माप(cur->string.poपूर्णांकer);

	ACPI_FREE(obj);
	वापस 0;
पूर्ण

/* Retrieves a device-specअगरic configuration variable.  The dev
 * argument should be a device with an ACPI companion, as all
 * configuration is based on firmware ID.
 */
अटल पूर्णांक gmin_get_config_var(काष्ठा device *मुख्यdev,
			       bool is_gmin,
			       स्थिर अक्षर *var,
			       अक्षर *out, माप_प्रकार *out_len)
अणु
	efi_अक्षर16_t var16[CFG_VAR_NAME_MAX];
	स्थिर काष्ठा dmi_प्रणाली_id *id;
	काष्ठा device *dev = मुख्यdev;
	अक्षर var8[CFG_VAR_NAME_MAX];
	काष्ठा efivar_entry *ev;
	पूर्णांक i, ret;

	/* For sensors, try first to use the _DSM table */
	अगर (!is_gmin) अणु
		ret = gmin_get_config_dsm_var(मुख्यdev, var, out, out_len);
		अगर (!ret)
			वापस 0;
	पूर्ण

	/* Fall-back to other approaches */

	अगर (!is_gmin && ACPI_COMPANION(dev))
		dev = &ACPI_COMPANION(dev)->dev;

	अगर (!is_gmin)
		ret = snम_लिखो(var8, माप(var8), "%s_%s", dev_name(dev), var);
	अन्यथा
		ret = snम_लिखो(var8, माप(var8), "gmin_%s", var);

	अगर (ret < 0 || ret >= माप(var8) - 1)
		वापस -EINVAL;

	/* First check a hard-coded list of board-specअगरic variables.
	 * Some device firmwares lack the ability to set EFI variables at
	 * runसमय.
	 */
	id = dmi_first_match(gmin_vars);
	अगर (id) अणु
		ret = gmin_get_hardcoded_var(मुख्यdev, id->driver_data, var8,
					     out, out_len);
		अगर (!ret)
			वापस 0;
	पूर्ण

	/* Our variable names are ASCII by स्थिरruction, but EFI names
	 * are wide अक्षरs.  Convert and zero-pad.
	 */
	स_रखो(var16, 0, माप(var16));
	क्रम (i = 0; i < माप(var8) && var8[i]; i++)
		var16[i] = var8[i];

	/* Not sure this API usage is kosher; efivar_entry_get()'s
	 * implementation simply uses VariableName and VenकरोrGuid from
	 * the काष्ठा and ignores the rest, but it seems like there
	 * ought to be an "official" efivar_entry रेजिस्टरed
	 * somewhere?
	 */
	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev)
		वापस -ENOMEM;
	स_नकल(&ev->var.VariableName, var16, माप(var16));
	ev->var.VenकरोrGuid = GMIN_CFG_VAR_EFI_GUID;
	ev->var.DataSize = *out_len;

	ret = efivar_entry_get(ev, &ev->var.Attributes,
			       &ev->var.DataSize, ev->var.Data);
	अगर (ret == 0) अणु
		स_नकल(out, ev->var.Data, ev->var.DataSize);
		*out_len = ev->var.DataSize;
		dev_info(मुख्यdev, "found EFI entry for '%s'\n", var8);
	पूर्ण अन्यथा अगर (is_gmin) अणु
		dev_info(मुख्यdev, "Failed to find EFI gmin variable %s\n", var8);
	पूर्ण अन्यथा अणु
		dev_info(मुख्यdev, "Failed to find EFI variable %s\n", var8);
	पूर्ण

	kमुक्त(ev);

	वापस ret;
पूर्ण

पूर्णांक gmin_get_var_पूर्णांक(काष्ठा device *dev, bool is_gmin, स्थिर अक्षर *var, पूर्णांक def)
अणु
	अक्षर val[CFG_VAR_NAME_MAX];
	माप_प्रकार len = माप(val);
	दीर्घ result;
	पूर्णांक ret;

	ret = gmin_get_config_var(dev, is_gmin, var, val, &len);
	अगर (!ret) अणु
		val[len] = 0;
		ret = kम_से_दीर्घ(val, 0, &result);
	पूर्ण अन्यथा अणु
		dev_info(dev, "%s: using default (%d)\n", var, def);
	पूर्ण

	वापस ret ? def : result;
पूर्ण
EXPORT_SYMBOL_GPL(gmin_get_var_पूर्णांक);

पूर्णांक camera_sensor_csi(काष्ठा v4l2_subdev *sd, u32 port,
		      u32 lanes, u32 क्रमmat, u32 bayer_order, पूर्णांक flag)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा camera_mipi_info *csi = शून्य;

	अगर (flag) अणु
		csi = kzalloc(माप(*csi), GFP_KERNEL);
		अगर (!csi)
			वापस -ENOMEM;
		csi->port = port;
		csi->num_lanes = lanes;
		csi->input_क्रमmat = क्रमmat;
		csi->raw_bayer_order = bayer_order;
		v4l2_set_subdev_hostdata(sd, (व्योम *)csi);
		csi->metadata_क्रमmat = ATOMISP_INPUT_FORMAT_EMBEDDED;
		csi->metadata_effective_width = शून्य;
		dev_info(&client->dev,
			 "camera pdata: port: %d lanes: %d order: %8.8x\n",
			 port, lanes, bayer_order);
	पूर्ण अन्यथा अणु
		csi = v4l2_get_subdev_hostdata(sd);
		kमुक्त(csi);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(camera_sensor_csi);

/* PCI quirk: The BYT ISP advertises PCI runसमय PM but it करोesn't
 * work.  Disable so the kernel framework करोesn't hang the device
 * trying.  The driver itself करोes direct calls to the PUNIT to manage
 * ISP घातer.
 */
अटल व्योम isp_pm_cap_fixup(काष्ठा pci_dev *pdev)
अणु
	dev_info(&pdev->dev, "Disabling PCI power management on camera ISP\n");
	pdev->pm_cap = 0;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0f38, isp_pm_cap_fixup);

MODULE_DESCRIPTION("Ancillary routines for binding ACPI devices");
MODULE_LICENSE("GPL");
