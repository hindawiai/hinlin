<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*-
 * Finger Sensing Pad PS/2 mouse driver.
 *
 * Copyright (C) 2005-2007 Asia Vital Components Co., Ltd.
 * Copyright (C) 2005-2012 Tai-hwa Liang, Sentelic Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/libps2.h>
#समावेश <linux/serपन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>

#समावेश "psmouse.h"
#समावेश "sentelic.h"

/*
 * Timeout क्रम FSP PS/2 command only (in milliseconds).
 */
#घोषणा	FSP_CMD_TIMEOUT		200
#घोषणा	FSP_CMD_TIMEOUT2	30

#घोषणा	GET_ABS_X(packet)	((packet[1] << 2) | ((packet[3] >> 2) & 0x03))
#घोषणा	GET_ABS_Y(packet)	((packet[2] << 2) | (packet[3] & 0x03))

/** Driver version. */
अटल स्थिर अक्षर fsp_drv_ver[] = "1.1.0-K";

/*
 * Make sure that the value being sent to FSP will not conflict with
 * possible sample rate values.
 */
अटल अचिन्हित अक्षर fsp_test_swap_cmd(अचिन्हित अक्षर reg_val)
अणु
	चयन (reg_val) अणु
	हाल 10: हाल 20: हाल 40: हाल 60: हाल 80: हाल 100: हाल 200:
		/*
		 * The requested value being sent to FSP matched to possible
		 * sample rates, swap the given value such that the hardware
		 * wouldn't get confused.
		 */
		वापस (reg_val >> 4) | (reg_val << 4);
	शेष:
		वापस reg_val;	/* swap isn't necessary */
	पूर्ण
पूर्ण

/*
 * Make sure that the value being sent to FSP will not conflict with certain
 * commands.
 */
अटल अचिन्हित अक्षर fsp_test_invert_cmd(अचिन्हित अक्षर reg_val)
अणु
	चयन (reg_val) अणु
	हाल 0xe9: हाल 0xee: हाल 0xf2: हाल 0xff:
		/*
		 * The requested value being sent to FSP matched to certain
		 * commands, inverse the given value such that the hardware
		 * wouldn't get confused.
		 */
		वापस ~reg_val;
	शेष:
		वापस reg_val;	/* inversion isn't necessary */
	पूर्ण
पूर्ण

अटल पूर्णांक fsp_reg_पढ़ो(काष्ठा psmouse *psmouse, पूर्णांक reg_addr, पूर्णांक *reg_val)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[3];
	अचिन्हित अक्षर addr;
	पूर्णांक rc = -1;

	/*
	 * We need to shut off the device and चयन it पूर्णांकo command
	 * mode so we करोn't confuse our protocol handler. We don't need
	 * to करो that क्रम ग_लिखोs because sysfs set helper करोes this क्रम
	 * us.
	 */
	psmouse_deactivate(psmouse);

	ps2_begin_command(ps2dev);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	/* should वापस 0xfe(request क्रम resending) */
	ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
	/* should वापस 0xfc(failed) */
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	अगर ((addr = fsp_test_invert_cmd(reg_addr)) != reg_addr) अणु
		ps2_sendbyte(ps2dev, 0x68, FSP_CMD_TIMEOUT2);
	पूर्ण अन्यथा अगर ((addr = fsp_test_swap_cmd(reg_addr)) != reg_addr) अणु
		/* swapping is required */
		ps2_sendbyte(ps2dev, 0xcc, FSP_CMD_TIMEOUT2);
		/* expect 0xfe */
	पूर्ण अन्यथा अणु
		/* swapping isn't necessary */
		ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
		/* expect 0xfe */
	पूर्ण
	/* should वापस 0xfc(failed) */
	ps2_sendbyte(ps2dev, addr, FSP_CMD_TIMEOUT);

	अगर (__ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO) < 0)
		जाओ out;

	*reg_val = param[2];
	rc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_activate(psmouse);
	psmouse_dbg(psmouse,
		    "READ REG: 0x%02x is 0x%02x (rc = %d)\n",
		    reg_addr, *reg_val, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक fsp_reg_ग_लिखो(काष्ठा psmouse *psmouse, पूर्णांक reg_addr, पूर्णांक reg_val)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर v;
	पूर्णांक rc = -1;

	ps2_begin_command(ps2dev);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	अगर ((v = fsp_test_invert_cmd(reg_addr)) != reg_addr) अणु
		/* inversion is required */
		ps2_sendbyte(ps2dev, 0x74, FSP_CMD_TIMEOUT2);
	पूर्ण अन्यथा अणु
		अगर ((v = fsp_test_swap_cmd(reg_addr)) != reg_addr) अणु
			/* swapping is required */
			ps2_sendbyte(ps2dev, 0x77, FSP_CMD_TIMEOUT2);
		पूर्ण अन्यथा अणु
			/* swapping isn't necessary */
			ps2_sendbyte(ps2dev, 0x55, FSP_CMD_TIMEOUT2);
		पूर्ण
	पूर्ण
	/* ग_लिखो the रेजिस्टर address in correct order */
	ps2_sendbyte(ps2dev, v, FSP_CMD_TIMEOUT2);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	अगर ((v = fsp_test_invert_cmd(reg_val)) != reg_val) अणु
		/* inversion is required */
		ps2_sendbyte(ps2dev, 0x47, FSP_CMD_TIMEOUT2);
	पूर्ण अन्यथा अगर ((v = fsp_test_swap_cmd(reg_val)) != reg_val) अणु
		/* swapping is required */
		ps2_sendbyte(ps2dev, 0x44, FSP_CMD_TIMEOUT2);
	पूर्ण अन्यथा अणु
		/* swapping isn't necessary */
		ps2_sendbyte(ps2dev, 0x33, FSP_CMD_TIMEOUT2);
	पूर्ण

	/* ग_लिखो the रेजिस्टर value in correct order */
	ps2_sendbyte(ps2dev, v, FSP_CMD_TIMEOUT2);
	rc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_dbg(psmouse,
		    "WRITE REG: 0x%02x to 0x%02x (rc = %d)\n",
		    reg_addr, reg_val, rc);
	वापस rc;
पूर्ण

/* Enable रेजिस्टर घड़ी gating क्रम writing certain रेजिस्टरs */
अटल पूर्णांक fsp_reg_ग_लिखो_enable(काष्ठा psmouse *psmouse, bool enable)
अणु
	पूर्णांक v, nv;

	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_SYSCTL1, &v) == -1)
		वापस -1;

	अगर (enable)
		nv = v | FSP_BIT_EN_REG_CLK;
	अन्यथा
		nv = v & ~FSP_BIT_EN_REG_CLK;

	/* only ग_लिखो अगर necessary */
	अगर (nv != v)
		अगर (fsp_reg_ग_लिखो(psmouse, FSP_REG_SYSCTL1, nv) == -1)
			वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक fsp_page_reg_पढ़ो(काष्ठा psmouse *psmouse, पूर्णांक *reg_val)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[3];
	पूर्णांक rc = -1;

	psmouse_deactivate(psmouse);

	ps2_begin_command(ps2dev);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	ps2_sendbyte(ps2dev, 0x83, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	/* get the वापसed result */
	अगर (__ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		जाओ out;

	*reg_val = param[2];
	rc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_activate(psmouse);
	psmouse_dbg(psmouse,
		    "READ PAGE REG: 0x%02x (rc = %d)\n",
		    *reg_val, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक fsp_page_reg_ग_लिखो(काष्ठा psmouse *psmouse, पूर्णांक reg_val)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर v;
	पूर्णांक rc = -1;

	ps2_begin_command(ps2dev);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	ps2_sendbyte(ps2dev, 0x38, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	अगर (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		जाओ out;

	अगर ((v = fsp_test_invert_cmd(reg_val)) != reg_val) अणु
		ps2_sendbyte(ps2dev, 0x47, FSP_CMD_TIMEOUT2);
	पूर्ण अन्यथा अगर ((v = fsp_test_swap_cmd(reg_val)) != reg_val) अणु
		/* swapping is required */
		ps2_sendbyte(ps2dev, 0x44, FSP_CMD_TIMEOUT2);
	पूर्ण अन्यथा अणु
		/* swapping isn't necessary */
		ps2_sendbyte(ps2dev, 0x33, FSP_CMD_TIMEOUT2);
	पूर्ण

	ps2_sendbyte(ps2dev, v, FSP_CMD_TIMEOUT2);
	rc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_dbg(psmouse,
		    "WRITE PAGE REG: to 0x%02x (rc = %d)\n",
		    reg_val, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक fsp_get_version(काष्ठा psmouse *psmouse, पूर्णांक *version)
अणु
	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_VERSION, version))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक fsp_get_revision(काष्ठा psmouse *psmouse, पूर्णांक *rev)
अणु
	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_REVISION, rev))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक fsp_get_sn(काष्ठा psmouse *psmouse, पूर्णांक *sn)
अणु
	पूर्णांक v0, v1, v2;
	पूर्णांक rc = -EIO;

	/* production number since Cx is available at: 0x0b40 ~ 0x0b42 */
	अगर (fsp_page_reg_ग_लिखो(psmouse, FSP_PAGE_0B))
		जाओ out;
	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_SN0, &v0))
		जाओ out;
	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_SN1, &v1))
		जाओ out;
	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_SN2, &v2))
		जाओ out;
	*sn = (v0 << 16) | (v1 << 8) | v2;
	rc = 0;
out:
	fsp_page_reg_ग_लिखो(psmouse, FSP_PAGE_DEFAULT);
	वापस rc;
पूर्ण

अटल पूर्णांक fsp_get_buttons(काष्ठा psmouse *psmouse, पूर्णांक *btn)
अणु
	अटल स्थिर पूर्णांक buttons[] = अणु
		0x16, /* Left/Middle/Right/Forward/Backward & Scroll Up/Down */
		0x06, /* Left/Middle/Right & Scroll Up/Down/Right/Left */
		0x04, /* Left/Middle/Right & Scroll Up/Down */
		0x02, /* Left/Middle/Right */
	पूर्ण;
	पूर्णांक val;

	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_TMOD_STATUS, &val) == -1)
		वापस -EIO;

	*btn = buttons[(val & 0x30) >> 4];
	वापस 0;
पूर्ण

/* Enable on-pad command tag output */
अटल पूर्णांक fsp_opc_tag_enable(काष्ठा psmouse *psmouse, bool enable)
अणु
	पूर्णांक v, nv;
	पूर्णांक res = 0;

	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_OPC_QDOWN, &v) == -1) अणु
		psmouse_err(psmouse, "Unable get OPC state.\n");
		वापस -EIO;
	पूर्ण

	अगर (enable)
		nv = v | FSP_BIT_EN_OPC_TAG;
	अन्यथा
		nv = v & ~FSP_BIT_EN_OPC_TAG;

	/* only ग_लिखो अगर necessary */
	अगर (nv != v) अणु
		fsp_reg_ग_लिखो_enable(psmouse, true);
		res = fsp_reg_ग_लिखो(psmouse, FSP_REG_OPC_QDOWN, nv);
		fsp_reg_ग_लिखो_enable(psmouse, false);
	पूर्ण

	अगर (res != 0) अणु
		psmouse_err(psmouse, "Unable to enable OPC tag.\n");
		res = -EIO;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक fsp_onpad_vscr(काष्ठा psmouse *psmouse, bool enable)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;
	पूर्णांक val;

	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_ONPAD_CTL, &val))
		वापस -EIO;

	pad->vscroll = enable;

	अगर (enable)
		val |= (FSP_BIT_FIX_VSCR | FSP_BIT_ONPAD_ENABLE);
	अन्यथा
		val &= ~FSP_BIT_FIX_VSCR;

	अगर (fsp_reg_ग_लिखो(psmouse, FSP_REG_ONPAD_CTL, val))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक fsp_onpad_hscr(काष्ठा psmouse *psmouse, bool enable)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;
	पूर्णांक val, v2;

	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_ONPAD_CTL, &val))
		वापस -EIO;

	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_SYSCTL5, &v2))
		वापस -EIO;

	pad->hscroll = enable;

	अगर (enable) अणु
		val |= (FSP_BIT_FIX_HSCR | FSP_BIT_ONPAD_ENABLE);
		v2 |= FSP_BIT_EN_MSID6;
	पूर्ण अन्यथा अणु
		val &= ~FSP_BIT_FIX_HSCR;
		v2 &= ~(FSP_BIT_EN_MSID6 | FSP_BIT_EN_MSID7 | FSP_BIT_EN_MSID8);
	पूर्ण

	अगर (fsp_reg_ग_लिखो(psmouse, FSP_REG_ONPAD_CTL, val))
		वापस -EIO;

	/* reconfigure horizontal scrolling packet output */
	अगर (fsp_reg_ग_लिखो(psmouse, FSP_REG_SYSCTL5, v2))
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Write device specअगरic initial parameters.
 *
 * ex: 0xab 0xcd - ग_लिखो oxcd पूर्णांकo रेजिस्टर 0xab
 */
अटल sमाप_प्रकार fsp_attr_set_setreg(काष्ठा psmouse *psmouse, व्योम *data,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक reg, val;
	अक्षर *rest;
	sमाप_प्रकार retval;

	reg = simple_म_से_अदीर्घ(buf, &rest, 16);
	अगर (rest == buf || *rest != ' ' || reg > 0xff)
		वापस -EINVAL;

	retval = kstrtouपूर्णांक(rest + 1, 16, &val);
	अगर (retval)
		वापस retval;

	अगर (val > 0xff)
		वापस -EINVAL;

	अगर (fsp_reg_ग_लिखो_enable(psmouse, true))
		वापस -EIO;

	retval = fsp_reg_ग_लिखो(psmouse, reg, val) < 0 ? -EIO : count;

	fsp_reg_ग_लिखो_enable(psmouse, false);

	वापस retval;
पूर्ण

PSMOUSE_DEFINE_WO_ATTR(setreg, S_IWUSR, शून्य, fsp_attr_set_setreg);

अटल sमाप_प्रकार fsp_attr_show_getreg(काष्ठा psmouse *psmouse,
					व्योम *data, अक्षर *buf)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;

	वापस प्र_लिखो(buf, "%02x%02x\n", pad->last_reg, pad->last_val);
पूर्ण

/*
 * Read a रेजिस्टर from device.
 *
 * ex: 0xab -- पढ़ो content from रेजिस्टर 0xab
 */
अटल sमाप_प्रकार fsp_attr_set_getreg(काष्ठा psmouse *psmouse, व्योम *data,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 16, &reg);
	अगर (err)
		वापस err;

	अगर (reg > 0xff)
		वापस -EINVAL;

	अगर (fsp_reg_पढ़ो(psmouse, reg, &val))
		वापस -EIO;

	pad->last_reg = reg;
	pad->last_val = val;

	वापस count;
पूर्ण

PSMOUSE_DEFINE_ATTR(getreg, S_IWUSR | S_IRUGO, शून्य,
			fsp_attr_show_getreg, fsp_attr_set_getreg);

अटल sमाप_प्रकार fsp_attr_show_pagereg(काष्ठा psmouse *psmouse,
					व्योम *data, अक्षर *buf)
अणु
	पूर्णांक val = 0;

	अगर (fsp_page_reg_पढ़ो(psmouse, &val))
		वापस -EIO;

	वापस प्र_लिखो(buf, "%02x\n", val);
पूर्ण

अटल sमाप_प्रकार fsp_attr_set_pagereg(काष्ठा psmouse *psmouse, व्योम *data,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 16, &val);
	अगर (err)
		वापस err;

	अगर (val > 0xff)
		वापस -EINVAL;

	अगर (fsp_page_reg_ग_लिखो(psmouse, val))
		वापस -EIO;

	वापस count;
पूर्ण

PSMOUSE_DEFINE_ATTR(page, S_IWUSR | S_IRUGO, शून्य,
			fsp_attr_show_pagereg, fsp_attr_set_pagereg);

अटल sमाप_प्रकार fsp_attr_show_vscroll(काष्ठा psmouse *psmouse,
					व्योम *data, अक्षर *buf)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;

	वापस प्र_लिखो(buf, "%d\n", pad->vscroll);
पूर्ण

अटल sमाप_प्रकार fsp_attr_set_vscroll(काष्ठा psmouse *psmouse, व्योम *data,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;

	fsp_onpad_vscr(psmouse, val);

	वापस count;
पूर्ण

PSMOUSE_DEFINE_ATTR(vscroll, S_IWUSR | S_IRUGO, शून्य,
			fsp_attr_show_vscroll, fsp_attr_set_vscroll);

अटल sमाप_प्रकार fsp_attr_show_hscroll(काष्ठा psmouse *psmouse,
					व्योम *data, अक्षर *buf)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;

	वापस प्र_लिखो(buf, "%d\n", pad->hscroll);
पूर्ण

अटल sमाप_प्रकार fsp_attr_set_hscroll(काष्ठा psmouse *psmouse, व्योम *data,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;

	fsp_onpad_hscr(psmouse, val);

	वापस count;
पूर्ण

PSMOUSE_DEFINE_ATTR(hscroll, S_IWUSR | S_IRUGO, शून्य,
			fsp_attr_show_hscroll, fsp_attr_set_hscroll);

अटल sमाप_प्रकार fsp_attr_show_flags(काष्ठा psmouse *psmouse,
					व्योम *data, अक्षर *buf)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;

	वापस प्र_लिखो(buf, "%c\n",
			pad->flags & FSPDRV_FLAG_EN_OPC ? 'C' : 'c');
पूर्ण

अटल sमाप_प्रकार fsp_attr_set_flags(काष्ठा psmouse *psmouse, व्योम *data,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;
	माप_प्रकार i;

	क्रम (i = 0; i < count; i++) अणु
		चयन (buf[i]) अणु
		हाल 'C':
			pad->flags |= FSPDRV_FLAG_EN_OPC;
			अवरोध;
		हाल 'c':
			pad->flags &= ~FSPDRV_FLAG_EN_OPC;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

PSMOUSE_DEFINE_ATTR(flags, S_IWUSR | S_IRUGO, शून्य,
			fsp_attr_show_flags, fsp_attr_set_flags);

अटल sमाप_प्रकार fsp_attr_show_ver(काष्ठा psmouse *psmouse,
					व्योम *data, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "Sentelic FSP kernel module %s\n", fsp_drv_ver);
पूर्ण

PSMOUSE_DEFINE_RO_ATTR(ver, S_IRUGO, शून्य, fsp_attr_show_ver);

अटल काष्ठा attribute *fsp_attributes[] = अणु
	&psmouse_attr_setreg.dattr.attr,
	&psmouse_attr_getreg.dattr.attr,
	&psmouse_attr_page.dattr.attr,
	&psmouse_attr_vscroll.dattr.attr,
	&psmouse_attr_hscroll.dattr.attr,
	&psmouse_attr_flags.dattr.attr,
	&psmouse_attr_ver.dattr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group fsp_attribute_group = अणु
	.attrs = fsp_attributes,
पूर्ण;

#अगर_घोषित	FSP_DEBUG
अटल व्योम fsp_packet_debug(काष्ठा psmouse *psmouse, अचिन्हित अक्षर packet[])
अणु
	अटल अचिन्हित पूर्णांक ps2_packet_cnt;
	अटल अचिन्हित पूर्णांक ps2_last_second;
	अचिन्हित पूर्णांक jअगरfies_msec;
	स्थिर अक्षर *packet_type = "UNKNOWN";
	अचिन्हित लघु असल_x = 0, असल_y = 0;

	/* Interpret & dump the packet data. */
	चयन (packet[0] >> FSP_PKT_TYPE_SHIFT) अणु
	हाल FSP_PKT_TYPE_ABS:
		packet_type = "Absolute";
		असल_x = GET_ABS_X(packet);
		असल_y = GET_ABS_Y(packet);
		अवरोध;
	हाल FSP_PKT_TYPE_NORMAL:
		packet_type = "Normal";
		अवरोध;
	हाल FSP_PKT_TYPE_NOTIFY:
		packet_type = "Notify";
		अवरोध;
	हाल FSP_PKT_TYPE_NORMAL_OPC:
		packet_type = "Normal-OPC";
		अवरोध;
	पूर्ण

	ps2_packet_cnt++;
	jअगरfies_msec = jअगरfies_to_msecs(jअगरfies);
	psmouse_dbg(psmouse,
		    "%08dms %s packets: %02x, %02x, %02x, %02x; "
		    "abs_x: %d, abs_y: %d\n",
		    jअगरfies_msec, packet_type,
		    packet[0], packet[1], packet[2], packet[3], असल_x, असल_y);

	अगर (jअगरfies_msec - ps2_last_second > 1000) अणु
		psmouse_dbg(psmouse, "PS/2 packets/sec = %d\n", ps2_packet_cnt);
		ps2_packet_cnt = 0;
		ps2_last_second = jअगरfies_msec;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम fsp_packet_debug(काष्ठा psmouse *psmouse, अचिन्हित अक्षर packet[])
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम fsp_set_slot(काष्ठा input_dev *dev, पूर्णांक slot, bool active,
			 अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	input_mt_slot(dev, slot);
	input_mt_report_slot_state(dev, MT_TOOL_FINGER, active);
	अगर (active) अणु
		input_report_असल(dev, ABS_MT_POSITION_X, x);
		input_report_असल(dev, ABS_MT_POSITION_Y, y);
	पूर्ण
पूर्ण

अटल psmouse_ret_t fsp_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा fsp_data *ad = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	अचिन्हित अक्षर button_status = 0, lscroll = 0, rscroll = 0;
	अचिन्हित लघु असल_x, असल_y, fgrs = 0;

	अगर (psmouse->pktcnt < 4)
		वापस PSMOUSE_GOOD_DATA;

	/*
	 * Full packet accumulated, process it
	 */

	fsp_packet_debug(psmouse, packet);

	चयन (psmouse->packet[0] >> FSP_PKT_TYPE_SHIFT) अणु
	हाल FSP_PKT_TYPE_ABS:

		अगर ((packet[0] == 0x48 || packet[0] == 0x49) &&
		    packet[1] == 0 && packet[2] == 0) अणु
			/*
			 * Ignore coordinate noise when finger leaving the
			 * surface, otherwise cursor may jump to upper-left
			 * corner.
			 */
			packet[3] &= 0xf0;
		पूर्ण

		असल_x = GET_ABS_X(packet);
		असल_y = GET_ABS_Y(packet);

		अगर (packet[0] & FSP_PB0_MFMC) अणु
			/*
			 * MFMC packet: assume that there are two fingers on
			 * pad
			 */
			fgrs = 2;

			/* MFMC packet */
			अगर (packet[0] & FSP_PB0_MFMC_FGR2) अणु
				/* 2nd finger */
				अगर (ad->last_mt_fgr == 2) अणु
					/*
					 * workaround क्रम buggy firmware
					 * which करोesn't clear MFMC bit अगर
					 * the 1st finger is up
					 */
					fgrs = 1;
					fsp_set_slot(dev, 0, false, 0, 0);
				पूर्ण
				ad->last_mt_fgr = 2;

				fsp_set_slot(dev, 1, fgrs == 2, असल_x, असल_y);
			पूर्ण अन्यथा अणु
				/* 1st finger */
				अगर (ad->last_mt_fgr == 1) अणु
					/*
					 * workaround क्रम buggy firmware
					 * which करोesn't clear MFMC bit अगर
					 * the 2nd finger is up
					 */
					fgrs = 1;
					fsp_set_slot(dev, 1, false, 0, 0);
				पूर्ण
				ad->last_mt_fgr = 1;
				fsp_set_slot(dev, 0, fgrs != 0, असल_x, असल_y);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* SFAC packet */
			अगर ((packet[0] & (FSP_PB0_LBTN|FSP_PB0_PHY_BTN)) ==
				FSP_PB0_LBTN) अणु
				/* On-pad click in SFAC mode should be handled
				 * by userspace.  On-pad clicks in MFMC mode
				 * are real clickpad clicks, and not ignored.
				 */
				packet[0] &= ~FSP_PB0_LBTN;
			पूर्ण

			/* no multi-finger inक्रमmation */
			ad->last_mt_fgr = 0;

			अगर (असल_x != 0 && असल_y != 0)
				fgrs = 1;

			fsp_set_slot(dev, 0, fgrs > 0, असल_x, असल_y);
			fsp_set_slot(dev, 1, false, 0, 0);
		पूर्ण
		अगर (fgrs == 1 || (fgrs == 2 && !(packet[0] & FSP_PB0_MFMC_FGR2))) अणु
			input_report_असल(dev, ABS_X, असल_x);
			input_report_असल(dev, ABS_Y, असल_y);
		पूर्ण
		input_report_key(dev, BTN_LEFT, packet[0] & 0x01);
		input_report_key(dev, BTN_RIGHT, packet[0] & 0x02);
		input_report_key(dev, BTN_TOUCH, fgrs);
		input_report_key(dev, BTN_TOOL_FINGER, fgrs == 1);
		input_report_key(dev, BTN_TOOL_DOUBLETAP, fgrs == 2);
		अवरोध;

	हाल FSP_PKT_TYPE_NORMAL_OPC:
		/* on-pad click, filter it अगर necessary */
		अगर ((ad->flags & FSPDRV_FLAG_EN_OPC) != FSPDRV_FLAG_EN_OPC)
			packet[0] &= ~FSP_PB0_LBTN;
		fallthrough;

	हाल FSP_PKT_TYPE_NORMAL:
		/* normal packet */
		/* special packet data translation from on-pad packets */
		अगर (packet[3] != 0) अणु
			अगर (packet[3] & BIT(0))
				button_status |= 0x01;	/* wheel करोwn */
			अगर (packet[3] & BIT(1))
				button_status |= 0x0f;	/* wheel up */
			अगर (packet[3] & BIT(2))
				button_status |= BIT(4);/* horizontal left */
			अगर (packet[3] & BIT(3))
				button_status |= BIT(5);/* horizontal right */
			/* push back to packet queue */
			अगर (button_status != 0)
				packet[3] = button_status;
			rscroll = (packet[3] >> 4) & 1;
			lscroll = (packet[3] >> 5) & 1;
		पूर्ण
		/*
		 * Processing wheel up/करोwn and extra button events
		 */
		input_report_rel(dev, REL_WHEEL,
				 (पूर्णांक)(packet[3] & 8) - (पूर्णांक)(packet[3] & 7));
		input_report_rel(dev, REL_HWHEEL, lscroll - rscroll);
		input_report_key(dev, BTN_BACK, lscroll);
		input_report_key(dev, BTN_FORWARD, rscroll);

		/*
		 * Standard PS/2 Mouse
		 */
		psmouse_report_standard_packet(dev, packet);
		अवरोध;
	पूर्ण

	input_sync(dev);

	वापस PSMOUSE_FULL_PACKET;
पूर्ण

अटल पूर्णांक fsp_activate_protocol(काष्ठा psmouse *psmouse)
अणु
	काष्ठा fsp_data *pad = psmouse->निजी;
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[2];
	पूर्णांक val;

	/*
	 * Standard procedure to enter FSP Intellimouse mode
	 * (scrolling wheel, 4th and 5th buttons)
	 */
	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] =  80;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);

	ps2_command(ps2dev, param, PSMOUSE_CMD_GETID);
	अगर (param[0] != 0x04) अणु
		psmouse_err(psmouse,
			    "Unable to enable 4 bytes packet format.\n");
		वापस -EIO;
	पूर्ण

	अगर (pad->ver < FSP_VER_STL3888_C0) अणु
		/* Preparing relative coordinates output क्रम older hardware */
		अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_SYSCTL5, &val)) अणु
			psmouse_err(psmouse,
				    "Unable to read SYSCTL5 register.\n");
			वापस -EIO;
		पूर्ण

		अगर (fsp_get_buttons(psmouse, &pad->buttons)) अणु
			psmouse_err(psmouse,
				    "Unable to retrieve number of buttons.\n");
			वापस -EIO;
		पूर्ण

		val &= ~(FSP_BIT_EN_MSID7 | FSP_BIT_EN_MSID8 | FSP_BIT_EN_AUTO_MSID8);
		/* Ensure we are not in असलolute mode */
		val &= ~FSP_BIT_EN_PKT_G0;
		अगर (pad->buttons == 0x06) अणु
			/* Left/Middle/Right & Scroll Up/Down/Right/Left */
			val |= FSP_BIT_EN_MSID6;
		पूर्ण

		अगर (fsp_reg_ग_लिखो(psmouse, FSP_REG_SYSCTL5, val)) अणु
			psmouse_err(psmouse,
				    "Unable to set up required mode bits.\n");
			वापस -EIO;
		पूर्ण

		/*
		 * Enable OPC tags such that driver can tell the dअगरference
		 * between on-pad and real button click
		 */
		अगर (fsp_opc_tag_enable(psmouse, true))
			psmouse_warn(psmouse,
				     "Failed to enable OPC tag mode.\n");
		/* enable on-pad click by शेष */
		pad->flags |= FSPDRV_FLAG_EN_OPC;

		/* Enable on-pad vertical and horizontal scrolling */
		fsp_onpad_vscr(psmouse, true);
		fsp_onpad_hscr(psmouse, true);
	पूर्ण अन्यथा अणु
		/* Enable असलolute coordinates output क्रम Cx/Dx hardware */
		अगर (fsp_reg_ग_लिखो(psmouse, FSP_REG_SWC1,
				  FSP_BIT_SWC1_EN_ABS_1F |
				  FSP_BIT_SWC1_EN_ABS_2F |
				  FSP_BIT_SWC1_EN_FUP_OUT |
				  FSP_BIT_SWC1_EN_ABS_CON)) अणु
			psmouse_err(psmouse,
				    "Unable to enable absolute coordinates output.\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsp_set_input_params(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा fsp_data *pad = psmouse->निजी;

	अगर (pad->ver < FSP_VER_STL3888_C0) अणु
		__set_bit(BTN_MIDDLE, dev->keybit);
		__set_bit(BTN_BACK, dev->keybit);
		__set_bit(BTN_FORWARD, dev->keybit);
		__set_bit(REL_WHEEL, dev->relbit);
		__set_bit(REL_HWHEEL, dev->relbit);
	पूर्ण अन्यथा अणु
		/*
		 * Hardware prior to Cx perक्रमms much better in relative mode;
		 * hence, only enable असलolute coordinates output as well as
		 * multi-touch output क्रम the newer hardware.
		 *
		 * Maximum coordinates can be computed as:
		 *
		 *	number of scanlines * 64 - 57
		 *
		 * where number of X/Y scanline lines are 16/12.
		 */
		पूर्णांक असल_x = 967, असल_y = 711;

		__set_bit(EV_ABS, dev->evbit);
		__clear_bit(EV_REL, dev->evbit);
		__set_bit(BTN_TOUCH, dev->keybit);
		__set_bit(BTN_TOOL_FINGER, dev->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
		__set_bit(INPUT_PROP_SEMI_MT, dev->propbit);

		input_set_असल_params(dev, ABS_X, 0, असल_x, 0, 0);
		input_set_असल_params(dev, ABS_Y, 0, असल_y, 0, 0);
		input_mt_init_slots(dev, 2, 0);
		input_set_असल_params(dev, ABS_MT_POSITION_X, 0, असल_x, 0, 0);
		input_set_असल_params(dev, ABS_MT_POSITION_Y, 0, असल_y, 0, 0);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक fsp_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	पूर्णांक id;

	अगर (fsp_reg_पढ़ो(psmouse, FSP_REG_DEVICE_ID, &id))
		वापस -EIO;

	अगर (id != 0x01)
		वापस -ENODEV;

	अगर (set_properties) अणु
		psmouse->venकरोr = "Sentelic";
		psmouse->name = "FingerSensingPad";
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsp_reset(काष्ठा psmouse *psmouse)
अणु
	fsp_opc_tag_enable(psmouse, false);
	fsp_onpad_vscr(psmouse, false);
	fsp_onpad_hscr(psmouse, false);
पूर्ण

अटल व्योम fsp_disconnect(काष्ठा psmouse *psmouse)
अणु
	sysfs_हटाओ_group(&psmouse->ps2dev.serio->dev.kobj,
			   &fsp_attribute_group);

	fsp_reset(psmouse);
	kमुक्त(psmouse->निजी);
पूर्ण

अटल पूर्णांक fsp_reconnect(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक version;

	अगर (fsp_detect(psmouse, 0))
		वापस -ENODEV;

	अगर (fsp_get_version(psmouse, &version))
		वापस -ENODEV;

	अगर (fsp_activate_protocol(psmouse))
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक fsp_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा fsp_data *priv;
	पूर्णांक ver, rev, sn = 0;
	पूर्णांक error;

	अगर (fsp_get_version(psmouse, &ver) ||
	    fsp_get_revision(psmouse, &rev)) अणु
		वापस -ENODEV;
	पूर्ण
	अगर (ver >= FSP_VER_STL3888_C0) अणु
		/* firmware inक्रमmation is only available since C0 */
		fsp_get_sn(psmouse, &sn);
	पूर्ण

	psmouse_info(psmouse,
		     "Finger Sensing Pad, hw: %d.%d.%d, sn: %x, sw: %s\n",
		     ver >> 4, ver & 0x0F, rev, sn, fsp_drv_ver);

	psmouse->निजी = priv = kzalloc(माप(काष्ठा fsp_data), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->ver = ver;
	priv->rev = rev;

	psmouse->protocol_handler = fsp_process_byte;
	psmouse->disconnect = fsp_disconnect;
	psmouse->reconnect = fsp_reconnect;
	psmouse->cleanup = fsp_reset;
	psmouse->pktsize = 4;

	error = fsp_activate_protocol(psmouse);
	अगर (error)
		जाओ err_out;

	/* Set up various supported input event bits */
	error = fsp_set_input_params(psmouse);
	अगर (error)
		जाओ err_out;

	error = sysfs_create_group(&psmouse->ps2dev.serio->dev.kobj,
				   &fsp_attribute_group);
	अगर (error) अणु
		psmouse_err(psmouse,
			    "Failed to create sysfs attributes (%d)", error);
		जाओ err_out;
	पूर्ण

	वापस 0;

 err_out:
	kमुक्त(psmouse->निजी);
	psmouse->निजी = शून्य;
	वापस error;
पूर्ण
