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

#घोषणा SIL164_VID 0x0001
#घोषणा SIL164_DID 0x0006

#घोषणा SIL164_VID_LO 0x00
#घोषणा SIL164_VID_HI 0x01
#घोषणा SIL164_DID_LO 0x02
#घोषणा SIL164_DID_HI 0x03
#घोषणा SIL164_REV    0x04
#घोषणा SIL164_RSVD   0x05
#घोषणा SIL164_FREQ_LO 0x06
#घोषणा SIL164_FREQ_HI 0x07

#घोषणा SIL164_REG8 0x08
#घोषणा SIL164_8_VEN (1<<5)
#घोषणा SIL164_8_HEN (1<<4)
#घोषणा SIL164_8_DSEL (1<<3)
#घोषणा SIL164_8_BSEL (1<<2)
#घोषणा SIL164_8_EDGE (1<<1)
#घोषणा SIL164_8_PD   (1<<0)

#घोषणा SIL164_REG9 0x09
#घोषणा SIL164_9_VLOW (1<<7)
#घोषणा SIL164_9_MSEL_MASK (0x7<<4)
#घोषणा SIL164_9_TSEL (1<<3)
#घोषणा SIL164_9_RSEN (1<<2)
#घोषणा SIL164_9_HTPLG (1<<1)
#घोषणा SIL164_9_MDI (1<<0)

#घोषणा SIL164_REGC 0x0c

काष्ठा sil164_priv अणु
	//I2CDevRec d;
	bool quiet;
पूर्ण;

#घोषणा SILPTR(d) ((SIL164Ptr)(d->DriverPrivate.ptr))

अटल bool sil164_पढ़ोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 *ch)
अणु
	काष्ठा sil164_priv *sil = dvo->dev_priv;
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

	अगर (!sil->quiet) अणु
		DRM_DEBUG_KMS("Unable to read register 0x%02x from %s:%02x.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण
	वापस false;
पूर्ण

अटल bool sil164_ग_लिखोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 ch)
अणु
	काष्ठा sil164_priv *sil = dvo->dev_priv;
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

	अगर (!sil->quiet) अणु
		DRM_DEBUG_KMS("Unable to write register 0x%02x to %s:%d.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण

	वापस false;
पूर्ण

/* Silicon Image 164 driver क्रम chip on i2c bus */
अटल bool sil164_init(काष्ठा पूर्णांकel_dvo_device *dvo,
			काष्ठा i2c_adapter *adapter)
अणु
	/* this will detect the SIL164 chip on the specअगरied i2c bus */
	काष्ठा sil164_priv *sil;
	अचिन्हित अक्षर ch;

	sil = kzalloc(माप(काष्ठा sil164_priv), GFP_KERNEL);
	अगर (sil == शून्य)
		वापस false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = sil;
	sil->quiet = true;

	अगर (!sil164_पढ़ोb(dvo, SIL164_VID_LO, &ch))
		जाओ out;

	अगर (ch != (SIL164_VID & 0xff)) अणु
		DRM_DEBUG_KMS("sil164 not detected got %d: from %s Slave %d.\n",
			  ch, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण

	अगर (!sil164_पढ़ोb(dvo, SIL164_DID_LO, &ch))
		जाओ out;

	अगर (ch != (SIL164_DID & 0xff)) अणु
		DRM_DEBUG_KMS("sil164 not detected got %d: from %s Slave %d.\n",
			  ch, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण
	sil->quiet = false;

	DRM_DEBUG_KMS("init sil164 dvo controller successfully!\n");
	वापस true;

out:
	kमुक्त(sil);
	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status sil164_detect(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 reg9;

	sil164_पढ़ोb(dvo, SIL164_REG9, &reg9);

	अगर (reg9 & SIL164_9_HTPLG)
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_mode_status sil164_mode_valid(काष्ठा पूर्णांकel_dvo_device *dvo,
					      काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल व्योम sil164_mode_set(काष्ठा पूर्णांकel_dvo_device *dvo,
			    स्थिर काष्ठा drm_display_mode *mode,
			    स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* As दीर्घ as the basics are set up, since we करोn't have घड़ी
	 * dependencies in the mode setup, we can just leave the
	 * रेजिस्टरs alone and everything will work fine.
	 */
	/* recommended programming sequence from करोc */
	/*sil164_ग_लिखोb(sil, 0x08, 0x30);
	  sil164_ग_लिखोb(sil, 0x09, 0x00);
	  sil164_ग_लिखोb(sil, 0x0a, 0x90);
	  sil164_ग_लिखोb(sil, 0x0c, 0x89);
	  sil164_ग_लिखोb(sil, 0x08, 0x31);*/
	/* करोn't करो much */
	वापस;
पूर्ण

/* set the SIL164 घातer state */
अटल व्योम sil164_dpms(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर ch;

	ret = sil164_पढ़ोb(dvo, SIL164_REG8, &ch);
	अगर (ret == false)
		वापस;

	अगर (enable)
		ch |= SIL164_8_PD;
	अन्यथा
		ch &= ~SIL164_8_PD;

	sil164_ग_लिखोb(dvo, SIL164_REG8, ch);
	वापस;
पूर्ण

अटल bool sil164_get_hw_state(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर ch;

	ret = sil164_पढ़ोb(dvo, SIL164_REG8, &ch);
	अगर (ret == false)
		वापस false;

	अगर (ch & SIL164_8_PD)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम sil164_dump_regs(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 val;

	sil164_पढ़ोb(dvo, SIL164_FREQ_LO, &val);
	DRM_DEBUG_KMS("SIL164_FREQ_LO: 0x%02x\n", val);
	sil164_पढ़ोb(dvo, SIL164_FREQ_HI, &val);
	DRM_DEBUG_KMS("SIL164_FREQ_HI: 0x%02x\n", val);
	sil164_पढ़ोb(dvo, SIL164_REG8, &val);
	DRM_DEBUG_KMS("SIL164_REG8: 0x%02x\n", val);
	sil164_पढ़ोb(dvo, SIL164_REG9, &val);
	DRM_DEBUG_KMS("SIL164_REG9: 0x%02x\n", val);
	sil164_पढ़ोb(dvo, SIL164_REGC, &val);
	DRM_DEBUG_KMS("SIL164_REGC: 0x%02x\n", val);
पूर्ण

अटल व्योम sil164_destroy(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	काष्ठा sil164_priv *sil = dvo->dev_priv;

	अगर (sil) अणु
		kमुक्त(sil);
		dvo->dev_priv = शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा पूर्णांकel_dvo_dev_ops sil164_ops = अणु
	.init = sil164_init,
	.detect = sil164_detect,
	.mode_valid = sil164_mode_valid,
	.mode_set = sil164_mode_set,
	.dpms = sil164_dpms,
	.get_hw_state = sil164_get_hw_state,
	.dump_regs = sil164_dump_regs,
	.destroy = sil164_destroy,
पूर्ण;
