<शैली गुरु>
/**************************************************************************

Copyright तऊ 2006 Dave Airlie

All Rights Reserved.

Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
copy of this software and associated करोcumentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modअगरy, merge, publish,
distribute, sub license, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to करो so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

#समावेश "intel_display_types.h"
#समावेश "intel_dvo_dev.h"

#घोषणा CH7xxx_REG_VID		0x4a
#घोषणा CH7xxx_REG_DID		0x4b

#घोषणा CH7011_VID		0x83 /* 7010 as well */
#घोषणा CH7010B_VID		0x05
#घोषणा CH7009A_VID		0x84
#घोषणा CH7009B_VID		0x85
#घोषणा CH7301_VID		0x95

#घोषणा CH7xxx_VID		0x84
#घोषणा CH7xxx_DID		0x17
#घोषणा CH7010_DID		0x16

#घोषणा CH7xxx_NUM_REGS		0x4c

#घोषणा CH7xxx_CM		0x1c
#घोषणा CH7xxx_CM_XCM		(1<<0)
#घोषणा CH7xxx_CM_MCP		(1<<2)
#घोषणा CH7xxx_INPUT_CLOCK	0x1d
#घोषणा CH7xxx_GPIO		0x1e
#घोषणा CH7xxx_GPIO_HPIR	(1<<3)
#घोषणा CH7xxx_IDF		0x1f

#घोषणा CH7xxx_IDF_HSP		(1<<3)
#घोषणा CH7xxx_IDF_VSP		(1<<4)

#घोषणा CH7xxx_CONNECTION_DETECT 0x20
#घोषणा CH7xxx_CDET_DVI		(1<<5)

#घोषणा CH7301_DAC_CNTL		0x21
#घोषणा CH7301_HOTPLUG		0x23
#घोषणा CH7xxx_TCTL		0x31
#घोषणा CH7xxx_TVCO		0x32
#घोषणा CH7xxx_TPCP		0x33
#घोषणा CH7xxx_TPD		0x34
#घोषणा CH7xxx_TPVT		0x35
#घोषणा CH7xxx_TLPF		0x36
#घोषणा CH7xxx_TCT		0x37
#घोषणा CH7301_TEST_PATTERN	0x48

#घोषणा CH7xxx_PM		0x49
#घोषणा CH7xxx_PM_FPD		(1<<0)
#घोषणा CH7301_PM_DACPD0	(1<<1)
#घोषणा CH7301_PM_DACPD1	(1<<2)
#घोषणा CH7301_PM_DACPD2	(1<<3)
#घोषणा CH7xxx_PM_DVIL		(1<<6)
#घोषणा CH7xxx_PM_DVIP		(1<<7)

#घोषणा CH7301_SYNC_POLARITY	0x56
#घोषणा CH7301_SYNC_RGB_YUV	(1<<0)
#घोषणा CH7301_SYNC_POL_DVI	(1<<5)

/** @file
 * driver क्रम the Chrontel 7xxx DVI chip over DVO.
 */

अटल काष्ठा ch7xxx_id_काष्ठा अणु
	u8 vid;
	अक्षर *name;
पूर्ण ch7xxx_ids[] = अणु
	अणु CH7011_VID, "CH7011" पूर्ण,
	अणु CH7010B_VID, "CH7010B" पूर्ण,
	अणु CH7009A_VID, "CH7009A" पूर्ण,
	अणु CH7009B_VID, "CH7009B" पूर्ण,
	अणु CH7301_VID, "CH7301" पूर्ण,
पूर्ण;

अटल काष्ठा ch7xxx_did_काष्ठा अणु
	u8 did;
	अक्षर *name;
पूर्ण ch7xxx_dids[] = अणु
	अणु CH7xxx_DID, "CH7XXX" पूर्ण,
	अणु CH7010_DID, "CH7010B" पूर्ण,
पूर्ण;

काष्ठा ch7xxx_priv अणु
	bool quiet;
पूर्ण;

अटल अक्षर *ch7xxx_get_id(u8 vid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ch7xxx_ids); i++) अणु
		अगर (ch7xxx_ids[i].vid == vid)
			वापस ch7xxx_ids[i].name;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अक्षर *ch7xxx_get_did(u8 did)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ch7xxx_dids); i++) अणु
		अगर (ch7xxx_dids[i].did == did)
			वापस ch7xxx_dids[i].name;
	पूर्ण

	वापस शून्य;
पूर्ण

/** Reads an 8 bit रेजिस्टर */
अटल bool ch7xxx_पढ़ोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 *ch)
अणु
	काष्ठा ch7xxx_priv *ch7xxx = dvo->dev_priv;
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

	अगर (!ch7xxx->quiet) अणु
		DRM_DEBUG_KMS("Unable to read register 0x%02x from %s:%02x.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण
	वापस false;
पूर्ण

/** Writes an 8 bit रेजिस्टर */
अटल bool ch7xxx_ग_लिखोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 ch)
अणु
	काष्ठा ch7xxx_priv *ch7xxx = dvo->dev_priv;
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

	अगर (!ch7xxx->quiet) अणु
		DRM_DEBUG_KMS("Unable to write register 0x%02x to %s:%d.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण

	वापस false;
पूर्ण

अटल bool ch7xxx_init(काष्ठा पूर्णांकel_dvo_device *dvo,
			काष्ठा i2c_adapter *adapter)
अणु
	/* this will detect the CH7xxx chip on the specअगरied i2c bus */
	काष्ठा ch7xxx_priv *ch7xxx;
	u8 venकरोr, device;
	अक्षर *name, *devid;

	ch7xxx = kzalloc(माप(काष्ठा ch7xxx_priv), GFP_KERNEL);
	अगर (ch7xxx == शून्य)
		वापस false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = ch7xxx;
	ch7xxx->quiet = true;

	अगर (!ch7xxx_पढ़ोb(dvo, CH7xxx_REG_VID, &venकरोr))
		जाओ out;

	name = ch7xxx_get_id(venकरोr);
	अगर (!name) अणु
		DRM_DEBUG_KMS("ch7xxx not detected; got VID 0x%02x from %s slave %d.\n",
			      venकरोr, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण


	अगर (!ch7xxx_पढ़ोb(dvo, CH7xxx_REG_DID, &device))
		जाओ out;

	devid = ch7xxx_get_did(device);
	अगर (!devid) अणु
		DRM_DEBUG_KMS("ch7xxx not detected; got DID 0x%02x from %s slave %d.\n",
			      device, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण

	ch7xxx->quiet = false;
	DRM_DEBUG_KMS("Detected %s chipset, vendor/device ID 0x%02x/0x%02x\n",
		  name, venकरोr, device);
	वापस true;
out:
	kमुक्त(ch7xxx);
	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status ch7xxx_detect(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 cdet, orig_pm, pm;

	ch7xxx_पढ़ोb(dvo, CH7xxx_PM, &orig_pm);

	pm = orig_pm;
	pm &= ~CH7xxx_PM_FPD;
	pm |= CH7xxx_PM_DVIL | CH7xxx_PM_DVIP;

	ch7xxx_ग_लिखोb(dvo, CH7xxx_PM, pm);

	ch7xxx_पढ़ोb(dvo, CH7xxx_CONNECTION_DETECT, &cdet);

	ch7xxx_ग_लिखोb(dvo, CH7xxx_PM, orig_pm);

	अगर (cdet & CH7xxx_CDET_DVI)
		वापस connector_status_connected;
	वापस connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_mode_status ch7xxx_mode_valid(काष्ठा पूर्णांकel_dvo_device *dvo,
					      काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 165000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम ch7xxx_mode_set(काष्ठा पूर्णांकel_dvo_device *dvo,
			    स्थिर काष्ठा drm_display_mode *mode,
			    स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	u8 tvco, tpcp, tpd, tlpf, idf;

	अगर (mode->घड़ी <= 65000) अणु
		tvco = 0x23;
		tpcp = 0x08;
		tpd = 0x16;
		tlpf = 0x60;
	पूर्ण अन्यथा अणु
		tvco = 0x2d;
		tpcp = 0x06;
		tpd = 0x26;
		tlpf = 0xa0;
	पूर्ण

	ch7xxx_ग_लिखोb(dvo, CH7xxx_TCTL, 0x00);
	ch7xxx_ग_लिखोb(dvo, CH7xxx_TVCO, tvco);
	ch7xxx_ग_लिखोb(dvo, CH7xxx_TPCP, tpcp);
	ch7xxx_ग_लिखोb(dvo, CH7xxx_TPD, tpd);
	ch7xxx_ग_लिखोb(dvo, CH7xxx_TPVT, 0x30);
	ch7xxx_ग_लिखोb(dvo, CH7xxx_TLPF, tlpf);
	ch7xxx_ग_लिखोb(dvo, CH7xxx_TCT, 0x00);

	ch7xxx_पढ़ोb(dvo, CH7xxx_IDF, &idf);

	idf &= ~(CH7xxx_IDF_HSP | CH7xxx_IDF_VSP);
	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		idf |= CH7xxx_IDF_HSP;

	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		idf |= CH7xxx_IDF_VSP;

	ch7xxx_ग_लिखोb(dvo, CH7xxx_IDF, idf);
पूर्ण

/* set the CH7xxx घातer state */
अटल व्योम ch7xxx_dpms(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable)
अणु
	अगर (enable)
		ch7xxx_ग_लिखोb(dvo, CH7xxx_PM, CH7xxx_PM_DVIL | CH7xxx_PM_DVIP);
	अन्यथा
		ch7xxx_ग_लिखोb(dvo, CH7xxx_PM, CH7xxx_PM_FPD);
पूर्ण

अटल bool ch7xxx_get_hw_state(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 val;

	ch7xxx_पढ़ोb(dvo, CH7xxx_PM, &val);

	अगर (val & (CH7xxx_PM_DVIL | CH7xxx_PM_DVIP))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम ch7xxx_dump_regs(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CH7xxx_NUM_REGS; i++) अणु
		u8 val;
		अगर ((i % 8) == 0)
			DRM_DEBUG_KMS("\n %02X: ", i);
		ch7xxx_पढ़ोb(dvo, i, &val);
		DRM_DEBUG_KMS("%02X ", val);
	पूर्ण
पूर्ण

अटल व्योम ch7xxx_destroy(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	काष्ठा ch7xxx_priv *ch7xxx = dvo->dev_priv;

	अगर (ch7xxx) अणु
		kमुक्त(ch7xxx);
		dvo->dev_priv = शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ch7xxx_ops = अणु
	.init = ch7xxx_init,
	.detect = ch7xxx_detect,
	.mode_valid = ch7xxx_mode_valid,
	.mode_set = ch7xxx_mode_set,
	.dpms = ch7xxx_dpms,
	.get_hw_state = ch7xxx_get_hw_state,
	.dump_regs = ch7xxx_dump_regs,
	.destroy = ch7xxx_destroy,
पूर्ण;
