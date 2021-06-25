<शैली गुरु>
/*
 * Copyright तऊ 2007 Dave Mueller
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Dave Mueller <dave.mueller@gmx.ch>
 *
 */

#समावेश "intel_display_types.h"
#समावेश "intel_dvo_dev.h"

/* रेजिस्टर definitions according to the TFP410 data sheet */
#घोषणा TFP410_VID		0x014C
#घोषणा TFP410_DID		0x0410

#घोषणा TFP410_VID_LO		0x00
#घोषणा TFP410_VID_HI		0x01
#घोषणा TFP410_DID_LO		0x02
#घोषणा TFP410_DID_HI		0x03
#घोषणा TFP410_REV		0x04

#घोषणा TFP410_CTL_1		0x08
#घोषणा TFP410_CTL_1_TDIS	(1<<6)
#घोषणा TFP410_CTL_1_VEN	(1<<5)
#घोषणा TFP410_CTL_1_HEN	(1<<4)
#घोषणा TFP410_CTL_1_DSEL	(1<<3)
#घोषणा TFP410_CTL_1_BSEL	(1<<2)
#घोषणा TFP410_CTL_1_EDGE	(1<<1)
#घोषणा TFP410_CTL_1_PD		(1<<0)

#घोषणा TFP410_CTL_2		0x09
#घोषणा TFP410_CTL_2_VLOW	(1<<7)
#घोषणा TFP410_CTL_2_MSEL_MASK	(0x7<<4)
#घोषणा TFP410_CTL_2_MSEL	(1<<4)
#घोषणा TFP410_CTL_2_TSEL	(1<<3)
#घोषणा TFP410_CTL_2_RSEN	(1<<2)
#घोषणा TFP410_CTL_2_HTPLG	(1<<1)
#घोषणा TFP410_CTL_2_MDI	(1<<0)

#घोषणा TFP410_CTL_3		0x0A
#घोषणा TFP410_CTL_3_DK_MASK	(0x7<<5)
#घोषणा TFP410_CTL_3_DK		(1<<5)
#घोषणा TFP410_CTL_3_DKEN	(1<<4)
#घोषणा TFP410_CTL_3_CTL_MASK	(0x7<<1)
#घोषणा TFP410_CTL_3_CTL	(1<<1)

#घोषणा TFP410_USERCFG		0x0B

#घोषणा TFP410_DE_DLY		0x32

#घोषणा TFP410_DE_CTL		0x33
#घोषणा TFP410_DE_CTL_DEGEN	(1<<6)
#घोषणा TFP410_DE_CTL_VSPOL	(1<<5)
#घोषणा TFP410_DE_CTL_HSPOL	(1<<4)
#घोषणा TFP410_DE_CTL_DEDLY8	(1<<0)

#घोषणा TFP410_DE_TOP		0x34

#घोषणा TFP410_DE_CNT_LO	0x36
#घोषणा TFP410_DE_CNT_HI	0x37

#घोषणा TFP410_DE_LIN_LO	0x38
#घोषणा TFP410_DE_LIN_HI	0x39

#घोषणा TFP410_H_RES_LO		0x3A
#घोषणा TFP410_H_RES_HI		0x3B

#घोषणा TFP410_V_RES_LO		0x3C
#घोषणा TFP410_V_RES_HI		0x3D

काष्ठा tfp410_priv अणु
	bool quiet;
पूर्ण;

अटल bool tfp410_पढ़ोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 *ch)
अणु
	काष्ठा tfp410_priv *tfp = dvo->dev_priv;
	काष्ठा i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[2];
	u8 in_buf[2];

	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = dvo->slave_addr,
			.flags = 0,
			.len = 1,
			.buf = out_buf,
		पूर्ण,
		अणु
			.addr = dvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = in_buf,
		पूर्ण
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = 0;

	अगर (i2c_transfer(adapter, msgs, 2) == 2) अणु
		*ch = in_buf[0];
		वापस true;
	पूर्ण

	अगर (!tfp->quiet) अणु
		DRM_DEBUG_KMS("Unable to read register 0x%02x from %s:%02x.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण
	वापस false;
पूर्ण

अटल bool tfp410_ग_लिखोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 ch)
अणु
	काष्ठा tfp410_priv *tfp = dvo->dev_priv;
	काष्ठा i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[2];
	काष्ठा i2c_msg msg = अणु
		.addr = dvo->slave_addr,
		.flags = 0,
		.len = 2,
		.buf = out_buf,
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = ch;

	अगर (i2c_transfer(adapter, &msg, 1) == 1)
		वापस true;

	अगर (!tfp->quiet) अणु
		DRM_DEBUG_KMS("Unable to write register 0x%02x to %s:%d.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tfp410_getid(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr)
अणु
	u8 ch1, ch2;

	अगर (tfp410_पढ़ोb(dvo, addr+0, &ch1) &&
	    tfp410_पढ़ोb(dvo, addr+1, &ch2))
		वापस ((ch2 << 8) & 0xFF00) | (ch1 & 0x00FF);

	वापस -1;
पूर्ण

/* Ti TFP410 driver क्रम chip on i2c bus */
अटल bool tfp410_init(काष्ठा पूर्णांकel_dvo_device *dvo,
			काष्ठा i2c_adapter *adapter)
अणु
	/* this will detect the tfp410 chip on the specअगरied i2c bus */
	काष्ठा tfp410_priv *tfp;
	पूर्णांक id;

	tfp = kzalloc(माप(काष्ठा tfp410_priv), GFP_KERNEL);
	अगर (tfp == शून्य)
		वापस false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = tfp;
	tfp->quiet = true;

	अगर ((id = tfp410_getid(dvo, TFP410_VID_LO)) != TFP410_VID) अणु
		DRM_DEBUG_KMS("tfp410 not detected got VID %X: from %s "
				"Slave %d.\n",
			  id, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण

	अगर ((id = tfp410_getid(dvo, TFP410_DID_LO)) != TFP410_DID) अणु
		DRM_DEBUG_KMS("tfp410 not detected got DID %X: from %s "
				"Slave %d.\n",
			  id, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण
	tfp->quiet = false;
	वापस true;
out:
	kमुक्त(tfp);
	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status tfp410_detect(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	क्रमागत drm_connector_status ret = connector_status_disconnected;
	u8 ctl2;

	अगर (tfp410_पढ़ोb(dvo, TFP410_CTL_2, &ctl2)) अणु
		अगर (ctl2 & TFP410_CTL_2_RSEN)
			ret = connector_status_connected;
		अन्यथा
			ret = connector_status_disconnected;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status tfp410_mode_valid(काष्ठा पूर्णांकel_dvo_device *dvo,
					      काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल व्योम tfp410_mode_set(काष्ठा पूर्णांकel_dvo_device *dvo,
			    स्थिर काष्ठा drm_display_mode *mode,
			    स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* As दीर्घ as the basics are set up, since we करोn't have घड़ी dependencies
	* in the mode setup, we can just leave the रेजिस्टरs alone and everything
	* will work fine.
	*/
	/* करोn't करो much */
	वापस;
पूर्ण

/* set the tfp410 घातer state */
अटल व्योम tfp410_dpms(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable)
अणु
	u8 ctl1;

	अगर (!tfp410_पढ़ोb(dvo, TFP410_CTL_1, &ctl1))
		वापस;

	अगर (enable)
		ctl1 |= TFP410_CTL_1_PD;
	अन्यथा
		ctl1 &= ~TFP410_CTL_1_PD;

	tfp410_ग_लिखोb(dvo, TFP410_CTL_1, ctl1);
पूर्ण

अटल bool tfp410_get_hw_state(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 ctl1;

	अगर (!tfp410_पढ़ोb(dvo, TFP410_CTL_1, &ctl1))
		वापस false;

	अगर (ctl1 & TFP410_CTL_1_PD)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम tfp410_dump_regs(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 val, val2;

	tfp410_पढ़ोb(dvo, TFP410_REV, &val);
	DRM_DEBUG_KMS("TFP410_REV: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_CTL_1, &val);
	DRM_DEBUG_KMS("TFP410_CTL1: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_CTL_2, &val);
	DRM_DEBUG_KMS("TFP410_CTL2: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_CTL_3, &val);
	DRM_DEBUG_KMS("TFP410_CTL3: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_USERCFG, &val);
	DRM_DEBUG_KMS("TFP410_USERCFG: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_DE_DLY, &val);
	DRM_DEBUG_KMS("TFP410_DE_DLY: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_DE_CTL, &val);
	DRM_DEBUG_KMS("TFP410_DE_CTL: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_DE_TOP, &val);
	DRM_DEBUG_KMS("TFP410_DE_TOP: 0x%02X\n", val);
	tfp410_पढ़ोb(dvo, TFP410_DE_CNT_LO, &val);
	tfp410_पढ़ोb(dvo, TFP410_DE_CNT_HI, &val2);
	DRM_DEBUG_KMS("TFP410_DE_CNT: 0x%02X%02X\n", val2, val);
	tfp410_पढ़ोb(dvo, TFP410_DE_LIN_LO, &val);
	tfp410_पढ़ोb(dvo, TFP410_DE_LIN_HI, &val2);
	DRM_DEBUG_KMS("TFP410_DE_LIN: 0x%02X%02X\n", val2, val);
	tfp410_पढ़ोb(dvo, TFP410_H_RES_LO, &val);
	tfp410_पढ़ोb(dvo, TFP410_H_RES_HI, &val2);
	DRM_DEBUG_KMS("TFP410_H_RES: 0x%02X%02X\n", val2, val);
	tfp410_पढ़ोb(dvo, TFP410_V_RES_LO, &val);
	tfp410_पढ़ोb(dvo, TFP410_V_RES_HI, &val2);
	DRM_DEBUG_KMS("TFP410_V_RES: 0x%02X%02X\n", val2, val);
पूर्ण

अटल व्योम tfp410_destroy(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	काष्ठा tfp410_priv *tfp = dvo->dev_priv;

	अगर (tfp) अणु
		kमुक्त(tfp);
		dvo->dev_priv = शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा पूर्णांकel_dvo_dev_ops tfp410_ops = अणु
	.init = tfp410_init,
	.detect = tfp410_detect,
	.mode_valid = tfp410_mode_valid,
	.mode_set = tfp410_mode_set,
	.dpms = tfp410_dpms,
	.get_hw_state = tfp410_get_hw_state,
	.dump_regs = tfp410_dump_regs,
	.destroy = tfp410_destroy,
पूर्ण;
