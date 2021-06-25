<शैली गुरु>
/*
 *
 * Handle TWL4030 Power initialization
 *
 * Copyright (C) 2008 Nokia Corporation
 * Copyright (C) 2006 Texas Instruments, Inc
 *
 * Written by 	Kalle Jokiniemi
 *		Peter De Schrijver <peter.de-schrijver@nokia.com>
 * Several fixes by Amit Kucheria <amit.kucheria@verdurent.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/mach-types.h>

अटल u8 twl4030_start_script_address = 0x2b;

/* Register bits क्रम P1, P2 and P3_SW_EVENTS */
#घोषणा PWR_STOPON_PRWON	BIT(6)
#घोषणा PWR_STOPON_SYSEN	BIT(5)
#घोषणा PWR_ENABLE_WARMRESET	BIT(4)
#घोषणा PWR_LVL_WAKEUP		BIT(3)
#घोषणा PWR_DEVACT		BIT(2)
#घोषणा PWR_DEVSLP		BIT(1)
#घोषणा PWR_DEVOFF		BIT(0)

/* Register bits क्रम CFG_P1_TRANSITION (also क्रम P2 and P3) */
#घोषणा STARTON_SWBUG		BIT(7)	/* Start on watchकरोg */
#घोषणा STARTON_VBUS		BIT(5)	/* Start on VBUS */
#घोषणा STARTON_VBAT		BIT(4)	/* Start on battery insert */
#घोषणा STARTON_RTC		BIT(3)	/* Start on RTC */
#घोषणा STARTON_USB		BIT(2)	/* Start on USB host */
#घोषणा STARTON_CHG		BIT(1)	/* Start on अक्षरger */
#घोषणा STARTON_PWON		BIT(0)	/* Start on PWRON button */

#घोषणा SEQ_OFFSYNC		(1 << 0)

#घोषणा PHY_TO_OFF_PM_MASTER(p)		(p - 0x36)
#घोषणा PHY_TO_OFF_PM_RECEIVER(p)	(p - 0x5b)

/* resource - hfclk */
#घोषणा R_HFCLKOUT_DEV_GRP 	PHY_TO_OFF_PM_RECEIVER(0xe6)

/* PM events */
#घोषणा R_P1_SW_EVENTS		PHY_TO_OFF_PM_MASTER(0x46)
#घोषणा R_P2_SW_EVENTS		PHY_TO_OFF_PM_MASTER(0x47)
#घोषणा R_P3_SW_EVENTS		PHY_TO_OFF_PM_MASTER(0x48)
#घोषणा R_CFG_P1_TRANSITION	PHY_TO_OFF_PM_MASTER(0x36)
#घोषणा R_CFG_P2_TRANSITION	PHY_TO_OFF_PM_MASTER(0x37)
#घोषणा R_CFG_P3_TRANSITION	PHY_TO_OFF_PM_MASTER(0x38)

#घोषणा END_OF_SCRIPT		0x3f

#घोषणा R_SEQ_ADD_A2S		PHY_TO_OFF_PM_MASTER(0x55)
#घोषणा R_SEQ_ADD_S2A12		PHY_TO_OFF_PM_MASTER(0x56)
#घोषणा	R_SEQ_ADD_S2A3		PHY_TO_OFF_PM_MASTER(0x57)
#घोषणा	R_SEQ_ADD_WARM		PHY_TO_OFF_PM_MASTER(0x58)
#घोषणा R_MEMORY_ADDRESS	PHY_TO_OFF_PM_MASTER(0x59)
#घोषणा R_MEMORY_DATA		PHY_TO_OFF_PM_MASTER(0x5a)

/* resource configuration रेजिस्टरs
   <RESOURCE>_DEV_GRP   at address 'n+0'
   <RESOURCE>_TYPE      at address 'n+1'
   <RESOURCE>_REMAP     at address 'n+2'
   <RESOURCE>_DEDICATED at address 'n+3'
*/
#घोषणा DEV_GRP_OFFSET		0
#घोषणा TYPE_OFFSET		1
#घोषणा REMAP_OFFSET		2
#घोषणा DEDICATED_OFFSET	3

/* Bit positions in the रेजिस्टरs */

/* <RESOURCE>_DEV_GRP */
#घोषणा DEV_GRP_SHIFT		5
#घोषणा DEV_GRP_MASK		(7 << DEV_GRP_SHIFT)

/* <RESOURCE>_TYPE */
#घोषणा TYPE_SHIFT		0
#घोषणा TYPE_MASK		(7 << TYPE_SHIFT)
#घोषणा TYPE2_SHIFT		3
#घोषणा TYPE2_MASK		(3 << TYPE2_SHIFT)

/* <RESOURCE>_REMAP */
#घोषणा SLEEP_STATE_SHIFT	0
#घोषणा SLEEP_STATE_MASK	(0xf << SLEEP_STATE_SHIFT)
#घोषणा OFF_STATE_SHIFT		4
#घोषणा OFF_STATE_MASK		(0xf << OFF_STATE_SHIFT)

अटल u8 res_config_addrs[] = अणु
	[RES_VAUX1]	= 0x17,
	[RES_VAUX2]	= 0x1b,
	[RES_VAUX3]	= 0x1f,
	[RES_VAUX4]	= 0x23,
	[RES_VMMC1]	= 0x27,
	[RES_VMMC2]	= 0x2b,
	[RES_VPLL1]	= 0x2f,
	[RES_VPLL2]	= 0x33,
	[RES_VSIM]	= 0x37,
	[RES_VDAC]	= 0x3b,
	[RES_VINTANA1]	= 0x3f,
	[RES_VINTANA2]	= 0x43,
	[RES_VINTDIG]	= 0x47,
	[RES_VIO]	= 0x4b,
	[RES_VDD1]	= 0x55,
	[RES_VDD2]	= 0x63,
	[RES_VUSB_1V5]	= 0x71,
	[RES_VUSB_1V8]	= 0x74,
	[RES_VUSB_3V1]	= 0x77,
	[RES_VUSBCP]	= 0x7a,
	[RES_REGEN]	= 0x7f,
	[RES_NRES_PWRON] = 0x82,
	[RES_CLKEN]	= 0x85,
	[RES_SYSEN]	= 0x88,
	[RES_HFCLKOUT]	= 0x8b,
	[RES_32KCLKOUT]	= 0x8e,
	[RES_RESET]	= 0x91,
	[RES_MAIN_REF]	= 0x94,
पूर्ण;

/*
 * Usable values क्रम .remap_sleep and .remap_off
 * Based on table "5.3.3 Resource Operating modes"
 */
क्रमागत अणु
	TWL_REMAP_OFF = 0,
	TWL_REMAP_SLEEP = 8,
	TWL_REMAP_ACTIVE = 9,
पूर्ण;

/*
 * Macros to configure the PM रेजिस्टर states क्रम various resources.
 * Note that we can make MSG_SINGULAR etc निजी to this driver once
 * omap3 has been made DT only.
 */
#घोषणा TWL_DFLT_DELAY		2	/* typically 2 32 KiHz cycles */
#घोषणा TWL_DEV_GRP_P123	(DEV_GRP_P1 | DEV_GRP_P2 | DEV_GRP_P3)
#घोषणा TWL_RESOURCE_SET(res, state)					\
	अणु MSG_SINGULAR(DEV_GRP_शून्य, (res), (state)), TWL_DFLT_DELAY पूर्ण
#घोषणा TWL_RESOURCE_ON(res)	TWL_RESOURCE_SET(res, RES_STATE_ACTIVE)
#घोषणा TWL_RESOURCE_OFF(res)	TWL_RESOURCE_SET(res, RES_STATE_OFF)
#घोषणा TWL_RESOURCE_RESET(res)	TWL_RESOURCE_SET(res, RES_STATE_WRST)
/*
 * It seems that type1 and type2 is just the resource init order
 * number क्रम the type1 and type2 group.
 */
#घोषणा TWL_RESOURCE_SET_ACTIVE(res, state)			       	\
	अणु MSG_SINGULAR(DEV_GRP_शून्य, (res), RES_STATE_ACTIVE), (state) पूर्ण
#घोषणा TWL_RESOURCE_GROUP_RESET(group, type1, type2)			\
	अणु MSG_BROADCAST(DEV_GRP_शून्य, (group), (type1), (type2),	\
		RES_STATE_WRST), TWL_DFLT_DELAY पूर्ण
#घोषणा TWL_RESOURCE_GROUP_SLEEP(group, type, type2)			\
	अणु MSG_BROADCAST(DEV_GRP_शून्य, (group), (type), (type2),		\
		RES_STATE_SLEEP), TWL_DFLT_DELAY पूर्ण
#घोषणा TWL_RESOURCE_GROUP_ACTIVE(group, type, type2)			\
	अणु MSG_BROADCAST(DEV_GRP_शून्य, (group), (type), (type2),		\
		RES_STATE_ACTIVE), TWL_DFLT_DELAY पूर्ण
#घोषणा TWL_REMAP_SLEEP(res, devgrp, typ, typ2)				\
	अणु .resource = (res), .devgroup = (devgrp),			\
	  .type = (typ), .type2 = (typ2),				\
	  .remap_off = TWL_REMAP_OFF,					\
	  .remap_sleep = TWL_REMAP_SLEEP, पूर्ण
#घोषणा TWL_REMAP_OFF(res, devgrp, typ, typ2)				\
	अणु .resource = (res), .devgroup = (devgrp),			\
	  .type = (typ), .type2 = (typ2),				\
	  .remap_off = TWL_REMAP_OFF, .remap_sleep = TWL_REMAP_OFF, पूर्ण

अटल पूर्णांक twl4030_ग_लिखो_script_byte(u8 address, u8 byte)
अणु
	पूर्णांक err;

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, address, R_MEMORY_ADDRESS);
	अगर (err)
		जाओ out;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, byte, R_MEMORY_DATA);
out:
	वापस err;
पूर्ण

अटल पूर्णांक twl4030_ग_लिखो_script_ins(u8 address, u16 pmb_message,
					   u8 delay, u8 next)
अणु
	पूर्णांक err;

	address *= 4;
	err = twl4030_ग_लिखो_script_byte(address++, pmb_message >> 8);
	अगर (err)
		जाओ out;
	err = twl4030_ग_लिखो_script_byte(address++, pmb_message & 0xff);
	अगर (err)
		जाओ out;
	err = twl4030_ग_लिखो_script_byte(address++, delay);
	अगर (err)
		जाओ out;
	err = twl4030_ग_लिखो_script_byte(address++, next);
out:
	वापस err;
पूर्ण

अटल पूर्णांक twl4030_ग_लिखो_script(u8 address, काष्ठा twl4030_ins *script,
				       पूर्णांक len)
अणु
	पूर्णांक err = -EINVAL;

	क्रम (; len; len--, address++, script++) अणु
		अगर (len == 1) अणु
			err = twl4030_ग_लिखो_script_ins(address,
						script->pmb_message,
						script->delay,
						END_OF_SCRIPT);
			अगर (err)
				अवरोध;
		पूर्ण अन्यथा अणु
			err = twl4030_ग_लिखो_script_ins(address,
						script->pmb_message,
						script->delay,
						address + 1);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक twl4030_config_wakeup3_sequence(u8 address)
अणु
	पूर्णांक err;
	u8 data;

	/* Set SLEEP to ACTIVE SEQ address क्रम P3 */
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, address, R_SEQ_ADD_S2A3);
	अगर (err)
		जाओ out;

	/* P3 LVL_WAKEUP should be on LEVEL */
	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &data, R_P3_SW_EVENTS);
	अगर (err)
		जाओ out;
	data |= PWR_LVL_WAKEUP;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, data, R_P3_SW_EVENTS);
out:
	अगर (err)
		pr_err("TWL4030 wakeup sequence for P3 config error\n");
	वापस err;
पूर्ण

अटल पूर्णांक
twl4030_config_wakeup12_sequence(स्थिर काष्ठा twl4030_घातer_data *pdata,
				 u8 address)
अणु
	पूर्णांक err = 0;
	u8 data;

	/* Set SLEEP to ACTIVE SEQ address क्रम P1 and P2 */
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, address, R_SEQ_ADD_S2A12);
	अगर (err)
		जाओ out;

	/* P1/P2 LVL_WAKEUP should be on LEVEL */
	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &data, R_P1_SW_EVENTS);
	अगर (err)
		जाओ out;

	data |= PWR_LVL_WAKEUP;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, data, R_P1_SW_EVENTS);
	अगर (err)
		जाओ out;

	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &data, R_P2_SW_EVENTS);
	अगर (err)
		जाओ out;

	data |= PWR_LVL_WAKEUP;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, data, R_P2_SW_EVENTS);
	अगर (err)
		जाओ out;

	अगर (pdata->ac_अक्षरger_quirk || machine_is_omap_3430sdp() ||
	    machine_is_omap_ldp()) अणु
		/* Disabling AC अक्षरger effect on sleep-active transitions */
		err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &data,
				      R_CFG_P1_TRANSITION);
		अगर (err)
			जाओ out;
		data &= ~STARTON_CHG;
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, data,
				       R_CFG_P1_TRANSITION);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	अगर (err)
		pr_err("TWL4030 wakeup sequence for P1 and P2" \
			"config error\n");
	वापस err;
पूर्ण

अटल पूर्णांक twl4030_config_sleep_sequence(u8 address)
अणु
	पूर्णांक err;

	/* Set ACTIVE to SLEEP SEQ address in T2 memory*/
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, address, R_SEQ_ADD_A2S);

	अगर (err)
		pr_err("TWL4030 sleep sequence config error\n");

	वापस err;
पूर्ण

अटल पूर्णांक twl4030_config_warmreset_sequence(u8 address)
अणु
	पूर्णांक err;
	u8 rd_data;

	/* Set WARM RESET SEQ address क्रम P1 */
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, address, R_SEQ_ADD_WARM);
	अगर (err)
		जाओ out;

	/* P1/P2/P3 enable WARMRESET */
	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &rd_data, R_P1_SW_EVENTS);
	अगर (err)
		जाओ out;

	rd_data |= PWR_ENABLE_WARMRESET;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, rd_data, R_P1_SW_EVENTS);
	अगर (err)
		जाओ out;

	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &rd_data, R_P2_SW_EVENTS);
	अगर (err)
		जाओ out;

	rd_data |= PWR_ENABLE_WARMRESET;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, rd_data, R_P2_SW_EVENTS);
	अगर (err)
		जाओ out;

	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &rd_data, R_P3_SW_EVENTS);
	अगर (err)
		जाओ out;

	rd_data |= PWR_ENABLE_WARMRESET;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, rd_data, R_P3_SW_EVENTS);
out:
	अगर (err)
		pr_err("TWL4030 warmreset seq config error\n");
	वापस err;
पूर्ण

अटल पूर्णांक twl4030_configure_resource(काष्ठा twl4030_resconfig *rconfig)
अणु
	पूर्णांक rconfig_addr;
	पूर्णांक err;
	u8 type;
	u8 grp;
	u8 remap;

	अगर (rconfig->resource > TOTAL_RESOURCES) अणु
		pr_err("TWL4030 Resource %d does not exist\n",
			rconfig->resource);
		वापस -EINVAL;
	पूर्ण

	rconfig_addr = res_config_addrs[rconfig->resource];

	/* Set resource group */
	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_RECEIVER, &grp,
			      rconfig_addr + DEV_GRP_OFFSET);
	अगर (err) अणु
		pr_err("TWL4030 Resource %d group could not be read\n",
			rconfig->resource);
		वापस err;
	पूर्ण

	अगर (rconfig->devgroup != TWL4030_RESCONFIG_UNDEF) अणु
		grp &= ~DEV_GRP_MASK;
		grp |= rconfig->devgroup << DEV_GRP_SHIFT;
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER,
				       grp, rconfig_addr + DEV_GRP_OFFSET);
		अगर (err < 0) अणु
			pr_err("TWL4030 failed to program devgroup\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* Set resource types */
	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_RECEIVER, &type,
				rconfig_addr + TYPE_OFFSET);
	अगर (err < 0) अणु
		pr_err("TWL4030 Resource %d type could not be read\n",
			rconfig->resource);
		वापस err;
	पूर्ण

	अगर (rconfig->type != TWL4030_RESCONFIG_UNDEF) अणु
		type &= ~TYPE_MASK;
		type |= rconfig->type << TYPE_SHIFT;
	पूर्ण

	अगर (rconfig->type2 != TWL4030_RESCONFIG_UNDEF) अणु
		type &= ~TYPE2_MASK;
		type |= rconfig->type2 << TYPE2_SHIFT;
	पूर्ण

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER,
				type, rconfig_addr + TYPE_OFFSET);
	अगर (err < 0) अणु
		pr_err("TWL4030 failed to program resource type\n");
		वापस err;
	पूर्ण

	/* Set remap states */
	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_RECEIVER, &remap,
			      rconfig_addr + REMAP_OFFSET);
	अगर (err < 0) अणु
		pr_err("TWL4030 Resource %d remap could not be read\n",
			rconfig->resource);
		वापस err;
	पूर्ण

	अगर (rconfig->remap_off != TWL4030_RESCONFIG_UNDEF) अणु
		remap &= ~OFF_STATE_MASK;
		remap |= rconfig->remap_off << OFF_STATE_SHIFT;
	पूर्ण

	अगर (rconfig->remap_sleep != TWL4030_RESCONFIG_UNDEF) अणु
		remap &= ~SLEEP_STATE_MASK;
		remap |= rconfig->remap_sleep << SLEEP_STATE_SHIFT;
	पूर्ण

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER,
			       remap,
			       rconfig_addr + REMAP_OFFSET);
	अगर (err < 0) अणु
		pr_err("TWL4030 failed to program remap\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक load_twl4030_script(स्थिर काष्ठा twl4030_घातer_data *pdata,
			       काष्ठा twl4030_script *tscript,
			       u8 address)
अणु
	पूर्णांक err;
	अटल पूर्णांक order;

	/* Make sure the script isn't going beyond last valid address (0x3f) */
	अगर ((address + tscript->size) > END_OF_SCRIPT) अणु
		pr_err("TWL4030 scripts too big error\n");
		वापस -EINVAL;
	पूर्ण

	err = twl4030_ग_लिखो_script(address, tscript->script, tscript->size);
	अगर (err)
		जाओ out;

	अगर (tscript->flags & TWL4030_WRST_SCRIPT) अणु
		err = twl4030_config_warmreset_sequence(address);
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (tscript->flags & TWL4030_WAKEUP12_SCRIPT) अणु
		/* Reset any existing sleep script to aव्योम hangs on reboot */
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, END_OF_SCRIPT,
				       R_SEQ_ADD_A2S);
		अगर (err)
			जाओ out;

		err = twl4030_config_wakeup12_sequence(pdata, address);
		अगर (err)
			जाओ out;
		order = 1;
	पूर्ण
	अगर (tscript->flags & TWL4030_WAKEUP3_SCRIPT) अणु
		err = twl4030_config_wakeup3_sequence(address);
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (tscript->flags & TWL4030_SLEEP_SCRIPT) अणु
		अगर (!order)
			pr_warn("TWL4030: Bad order of scripts (sleep script before wakeup) Leads to boot failure on some boards\n");
		err = twl4030_config_sleep_sequence(address);
	पूर्ण
out:
	वापस err;
पूर्ण

पूर्णांक twl4030_हटाओ_script(u8 flags)
अणु
	पूर्णांक err = 0;

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG1,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	अगर (err) अणु
		pr_err("twl4030: unable to unlock PROTECT_KEY\n");
		वापस err;
	पूर्ण

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG2,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	अगर (err) अणु
		pr_err("twl4030: unable to unlock PROTECT_KEY\n");
		वापस err;
	पूर्ण

	अगर (flags & TWL4030_WRST_SCRIPT) अणु
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, END_OF_SCRIPT,
				       R_SEQ_ADD_WARM);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (flags & TWL4030_WAKEUP12_SCRIPT) अणु
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, END_OF_SCRIPT,
				       R_SEQ_ADD_S2A12);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (flags & TWL4030_WAKEUP3_SCRIPT) अणु
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, END_OF_SCRIPT,
				       R_SEQ_ADD_S2A3);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (flags & TWL4030_SLEEP_SCRIPT) अणु
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, END_OF_SCRIPT,
				       R_SEQ_ADD_A2S);
		अगर (err)
			वापस err;
	पूर्ण

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, 0,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	अगर (err)
		pr_err("TWL4030 Unable to relock registers\n");

	वापस err;
पूर्ण

अटल पूर्णांक
twl4030_घातer_configure_scripts(स्थिर काष्ठा twl4030_घातer_data *pdata)
अणु
	पूर्णांक err;
	पूर्णांक i;
	u8 address = twl4030_start_script_address;

	क्रम (i = 0; i < pdata->num; i++) अणु
		err = load_twl4030_script(pdata, pdata->scripts[i], address);
		अगर (err)
			वापस err;
		address += pdata->scripts[i]->size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twl4030_patch_rconfig(काष्ठा twl4030_resconfig *common,
				  काष्ठा twl4030_resconfig *board)
अणु
	जबतक (common->resource) अणु
		काष्ठा twl4030_resconfig *b = board;

		जबतक (b->resource) अणु
			अगर (b->resource == common->resource) अणु
				*common = *b;
				अवरोध;
			पूर्ण
			b++;
		पूर्ण
		common++;
	पूर्ण
पूर्ण

अटल पूर्णांक
twl4030_घातer_configure_resources(स्थिर काष्ठा twl4030_घातer_data *pdata)
अणु
	काष्ठा twl4030_resconfig *resconfig = pdata->resource_config;
	काष्ठा twl4030_resconfig *boardconf = pdata->board_config;
	पूर्णांक err;

	अगर (resconfig) अणु
		अगर (boardconf)
			twl4030_patch_rconfig(resconfig, boardconf);

		जबतक (resconfig->resource) अणु
			err = twl4030_configure_resource(resconfig);
			अगर (err)
				वापस err;
			resconfig++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_starton_mask_and_set(u8 biपंचांगask, u8 bitvalues)
अणु
	u8 regs[3] = अणु TWL4030_PM_MASTER_CFG_P1_TRANSITION,
		       TWL4030_PM_MASTER_CFG_P2_TRANSITION,
		       TWL4030_PM_MASTER_CFG_P3_TRANSITION, पूर्ण;
	u8 val;
	पूर्णांक i, err;

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG1,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	अगर (err)
		जाओ relock;
	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER,
			       TWL4030_PM_MASTER_KEY_CFG2,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	अगर (err)
		जाओ relock;

	क्रम (i = 0; i < माप(regs); i++) अणु
		err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER,
				      &val, regs[i]);
		अगर (err)
			अवरोध;
		val = (~biपंचांगask & val) | (biपंचांगask & bitvalues);
		err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER,
				       val, regs[i]);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (err)
		pr_err("TWL4030 Register access failed: %i\n", err);

relock:
	वापस twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, 0,
				TWL4030_PM_MASTER_PROTECT_KEY);
पूर्ण

/*
 * In master mode, start the घातer off sequence.
 * After a successful execution, TWL shuts करोwn the घातer to the SoC
 * and all peripherals connected to it.
 */
व्योम twl4030_घातer_off(व्योम)
अणु
	पूर्णांक err;

	/* Disable start on अक्षरger or VBUS as it can अवरोध घातeroff */
	err = twl4030_starton_mask_and_set(STARTON_VBUS | STARTON_CHG, 0);
	अगर (err)
		pr_err("TWL4030 Unable to configure start-up\n");

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, PWR_DEVOFF,
			       TWL4030_PM_MASTER_P1_SW_EVENTS);
	अगर (err)
		pr_err("TWL4030 Unable to power off\n");
पूर्ण

अटल bool twl4030_घातer_use_घातeroff(स्थिर काष्ठा twl4030_घातer_data *pdata,
					काष्ठा device_node *node)
अणु
	अगर (pdata && pdata->use_घातeroff)
		वापस true;

	अगर (of_property_पढ़ो_bool(node, "ti,system-power-controller"))
		वापस true;

	अगर (of_property_पढ़ो_bool(node, "ti,use_poweroff"))
		वापस true;

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_OF

/* Generic warm reset configuration क्रम omap3 */

अटल काष्ठा twl4030_ins omap3_wrst_seq[] = अणु
	TWL_RESOURCE_OFF(RES_NRES_PWRON),
	TWL_RESOURCE_OFF(RES_RESET),
	TWL_RESOURCE_RESET(RES_MAIN_REF),
	TWL_RESOURCE_GROUP_RESET(RES_GRP_ALL, RES_TYPE_R0, RES_TYPE2_R2),
	TWL_RESOURCE_RESET(RES_VUSB_3V1),
	TWL_RESOURCE_RESET(RES_VMMC1),
	TWL_RESOURCE_GROUP_RESET(RES_GRP_ALL, RES_TYPE_R0, RES_TYPE2_R1),
	TWL_RESOURCE_GROUP_RESET(RES_GRP_RC, RES_TYPE_ALL, RES_TYPE2_R0),
	TWL_RESOURCE_ON(RES_RESET),
	TWL_RESOURCE_ON(RES_NRES_PWRON),
पूर्ण;

अटल काष्ठा twl4030_script omap3_wrst_script = अणु
	.script	= omap3_wrst_seq,
	.size	= ARRAY_SIZE(omap3_wrst_seq),
	.flags	= TWL4030_WRST_SCRIPT,
पूर्ण;

अटल काष्ठा twl4030_script *omap3_reset_scripts[] = अणु
	&omap3_wrst_script,
पूर्ण;

अटल काष्ठा twl4030_resconfig omap3_rconfig[] = अणु
	TWL_REMAP_SLEEP(RES_HFCLKOUT, DEV_GRP_P3, -1, -1),
	TWL_REMAP_SLEEP(RES_VDD1, DEV_GRP_P1, -1, -1),
	TWL_REMAP_SLEEP(RES_VDD2, DEV_GRP_P1, -1, -1),
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा twl4030_घातer_data omap3_reset = अणु
	.scripts		= omap3_reset_scripts,
	.num			= ARRAY_SIZE(omap3_reset_scripts),
	.resource_config	= omap3_rconfig,
पूर्ण;

/* Recommended generic शेष idle configuration क्रम off-idle */

/* Broadcast message to put res to sleep */
अटल काष्ठा twl4030_ins omap3_idle_sleep_on_seq[] = अणु
	TWL_RESOURCE_GROUP_SLEEP(RES_GRP_ALL, RES_TYPE_ALL, 0),
पूर्ण;

अटल काष्ठा twl4030_script omap3_idle_sleep_on_script = अणु
	.script	= omap3_idle_sleep_on_seq,
	.size	= ARRAY_SIZE(omap3_idle_sleep_on_seq),
	.flags	= TWL4030_SLEEP_SCRIPT,
पूर्ण;

/* Broadcast message to put res to active */
अटल काष्ठा twl4030_ins omap3_idle_wakeup_p12_seq[] = अणु
	TWL_RESOURCE_GROUP_ACTIVE(RES_GRP_ALL, RES_TYPE_ALL, 0),
पूर्ण;

अटल काष्ठा twl4030_script omap3_idle_wakeup_p12_script = अणु
	.script	= omap3_idle_wakeup_p12_seq,
	.size	= ARRAY_SIZE(omap3_idle_wakeup_p12_seq),
	.flags	= TWL4030_WAKEUP12_SCRIPT,
पूर्ण;

/* Broadcast message to put res to active */
अटल काष्ठा twl4030_ins omap3_idle_wakeup_p3_seq[] = अणु
	TWL_RESOURCE_SET_ACTIVE(RES_CLKEN, 0x37),
	TWL_RESOURCE_GROUP_ACTIVE(RES_GRP_ALL, RES_TYPE_ALL, 0),
पूर्ण;

अटल काष्ठा twl4030_script omap3_idle_wakeup_p3_script = अणु
	.script	= omap3_idle_wakeup_p3_seq,
	.size	= ARRAY_SIZE(omap3_idle_wakeup_p3_seq),
	.flags	= TWL4030_WAKEUP3_SCRIPT,
पूर्ण;

अटल काष्ठा twl4030_script *omap3_idle_scripts[] = अणु
	&omap3_idle_wakeup_p12_script,
	&omap3_idle_wakeup_p3_script,
	&omap3_wrst_script,
	&omap3_idle_sleep_on_script,
पूर्ण;

/*
 * Recommended configuration based on "Recommended Sleep
 * Sequences क्रम the Zoom Platक्रमm":
 * http://omappedia.com/wiki/File:Recommended_Sleep_Sequences_Zoom.pdf
 * Note that the type1 and type2 seem to be just the init order number
 * क्रम type1 and type2 groups as specअगरied in the करोcument mentioned
 * above.
 */
अटल काष्ठा twl4030_resconfig omap3_idle_rconfig[] = अणु
	TWL_REMAP_SLEEP(RES_VAUX1, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VAUX2, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VAUX3, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VAUX4, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VMMC1, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VMMC2, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_OFF(RES_VPLL1, DEV_GRP_P1, 3, 1),
	TWL_REMAP_SLEEP(RES_VPLL2, DEV_GRP_P1, 0, 0),
	TWL_REMAP_SLEEP(RES_VSIM, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VDAC, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VINTANA1, TWL_DEV_GRP_P123, 1, 2),
	TWL_REMAP_SLEEP(RES_VINTANA2, TWL_DEV_GRP_P123, 0, 2),
	TWL_REMAP_SLEEP(RES_VINTDIG, TWL_DEV_GRP_P123, 1, 2),
	TWL_REMAP_SLEEP(RES_VIO, TWL_DEV_GRP_P123, 2, 2),
	TWL_REMAP_OFF(RES_VDD1, DEV_GRP_P1, 4, 1),
	TWL_REMAP_OFF(RES_VDD2, DEV_GRP_P1, 3, 1),
	TWL_REMAP_SLEEP(RES_VUSB_1V5, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VUSB_1V8, TWL4030_RESCONFIG_UNDEF, 0, 0),
	TWL_REMAP_SLEEP(RES_VUSB_3V1, TWL_DEV_GRP_P123, 0, 0),
	/* Resource #20 USB अक्षरge pump skipped */
	TWL_REMAP_SLEEP(RES_REGEN, TWL_DEV_GRP_P123, 2, 1),
	TWL_REMAP_SLEEP(RES_NRES_PWRON, TWL_DEV_GRP_P123, 0, 1),
	TWL_REMAP_SLEEP(RES_CLKEN, TWL_DEV_GRP_P123, 3, 2),
	TWL_REMAP_SLEEP(RES_SYSEN, TWL_DEV_GRP_P123, 6, 1),
	TWL_REMAP_SLEEP(RES_HFCLKOUT, DEV_GRP_P3, 0, 2),
	TWL_REMAP_SLEEP(RES_32KCLKOUT, TWL_DEV_GRP_P123, 0, 0),
	TWL_REMAP_SLEEP(RES_RESET, TWL_DEV_GRP_P123, 6, 0),
	TWL_REMAP_SLEEP(RES_MAIN_REF, TWL_DEV_GRP_P123, 0, 0),
	अणु /* Terminator */ पूर्ण,
पूर्ण;

अटल काष्ठा twl4030_घातer_data omap3_idle = अणु
	.scripts		= omap3_idle_scripts,
	.num			= ARRAY_SIZE(omap3_idle_scripts),
	.resource_config	= omap3_idle_rconfig,
पूर्ण;

/* Disable 32 KiHz oscillator during idle */
अटल काष्ठा twl4030_resconfig osc_off_rconfig[] = अणु
	TWL_REMAP_OFF(RES_CLKEN, DEV_GRP_P1 | DEV_GRP_P3, 3, 2),
	अणु /* Terminator */ पूर्ण,
पूर्ण;

अटल काष्ठा twl4030_घातer_data osc_off_idle = अणु
	.scripts		= omap3_idle_scripts,
	.num			= ARRAY_SIZE(omap3_idle_scripts),
	.resource_config	= omap3_idle_rconfig,
	.board_config		= osc_off_rconfig,
पूर्ण;

अटल काष्ठा twl4030_घातer_data omap3_idle_ac_quirk = अणु
	.scripts		= omap3_idle_scripts,
	.num			= ARRAY_SIZE(omap3_idle_scripts),
	.resource_config	= omap3_idle_rconfig,
	.ac_अक्षरger_quirk	= true,
पूर्ण;

अटल काष्ठा twl4030_घातer_data omap3_idle_ac_quirk_osc_off = अणु
	.scripts		= omap3_idle_scripts,
	.num			= ARRAY_SIZE(omap3_idle_scripts),
	.resource_config	= omap3_idle_rconfig,
	.board_config		= osc_off_rconfig,
	.ac_अक्षरger_quirk	= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id twl4030_घातer_of_match[] = अणु
	अणु
		.compatible = "ti,twl4030-power",
	पूर्ण,
	अणु
		.compatible = "ti,twl4030-power-reset",
		.data = &omap3_reset,
	पूर्ण,
	अणु
		.compatible = "ti,twl4030-power-idle",
		.data = &omap3_idle,
	पूर्ण,
	अणु
		.compatible = "ti,twl4030-power-idle-osc-off",
		.data = &osc_off_idle,
	पूर्ण,
	अणु
		.compatible = "ti,twl4030-power-omap3-sdp",
		.data = &omap3_idle_ac_quirk,
	पूर्ण,
	अणु
		.compatible = "ti,twl4030-power-omap3-ldp",
		.data = &omap3_idle_ac_quirk_osc_off,
	पूर्ण,
	अणु
		.compatible = "ti,twl4030-power-omap3-evm",
		.data = &omap3_idle_ac_quirk,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl4030_घातer_of_match);
#पूर्ण_अगर	/* CONFIG_OF */

अटल पूर्णांक twl4030_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा twl4030_घातer_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक err = 0;
	पूर्णांक err2 = 0;
	u8 val;

	अगर (!pdata && !node) अणु
		dev_err(&pdev->dev, "Platform data is missing\n");
		वापस -EINVAL;
	पूर्ण

	err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG1,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	err |= twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER,
			       TWL4030_PM_MASTER_KEY_CFG2,
			       TWL4030_PM_MASTER_PROTECT_KEY);

	अगर (err) अणु
		pr_err("TWL4030 Unable to unlock registers\n");
		वापस err;
	पूर्ण

	match = of_match_device(of_match_ptr(twl4030_घातer_of_match),
				&pdev->dev);
	अगर (match && match->data)
		pdata = match->data;

	अगर (pdata) अणु
		err = twl4030_घातer_configure_scripts(pdata);
		अगर (err) अणु
			pr_err("TWL4030 failed to load scripts\n");
			जाओ relock;
		पूर्ण
		err = twl4030_घातer_configure_resources(pdata);
		अगर (err) अणु
			pr_err("TWL4030 failed to configure resource\n");
			जाओ relock;
		पूर्ण
	पूर्ण

	/* Board has to be wired properly to use this feature */
	अगर (twl4030_घातer_use_घातeroff(pdata, node) && !pm_घातer_off) अणु
		/* Default क्रम SEQ_OFFSYNC is set, lets ensure this */
		err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &val,
				      TWL4030_PM_MASTER_CFG_P123_TRANSITION);
		अगर (err) अणु
			pr_warn("TWL4030 Unable to read registers\n");
		पूर्ण अन्यथा अगर (!(val & SEQ_OFFSYNC)) अणु
			val |= SEQ_OFFSYNC;
			err = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, val,
					TWL4030_PM_MASTER_CFG_P123_TRANSITION);
			अगर (err) अणु
				pr_err("TWL4030 Unable to setup SEQ_OFFSYNC\n");
				जाओ relock;
			पूर्ण
		पूर्ण

		pm_घातer_off = twl4030_घातer_off;
	पूर्ण

relock:
	err2 = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, 0,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	अगर (err2) अणु
		pr_err("TWL4030 Unable to relock registers\n");
		वापस err2;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक twl4030_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver twl4030_घातer_driver = अणु
	.driver = अणु
		.name	= "twl4030_power",
		.of_match_table = of_match_ptr(twl4030_घातer_of_match),
	पूर्ण,
	.probe		= twl4030_घातer_probe,
	.हटाओ		= twl4030_घातer_हटाओ,
पूर्ण;

module_platक्रमm_driver(twl4030_घातer_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_AUTHOR("Texas Instruments, Inc.");
MODULE_DESCRIPTION("Power management for TWL4030");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:twl4030_power");
