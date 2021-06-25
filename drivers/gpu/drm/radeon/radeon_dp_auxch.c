<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
 */

#समावेश <drm/radeon_drm.h>
#समावेश "radeon.h"
#समावेश "nid.h"

#घोषणा AUX_RX_ERROR_FLAGS (AUX_SW_RX_OVERFLOW |	     \
			    AUX_SW_RX_HPD_DISCON |	     \
			    AUX_SW_RX_PARTIAL_BYTE |	     \
			    AUX_SW_NON_AUX_MODE |	     \
			    AUX_SW_RX_SYNC_INVALID_L |	     \
			    AUX_SW_RX_SYNC_INVALID_H |	     \
			    AUX_SW_RX_INVALID_START |	     \
			    AUX_SW_RX_RECV_NO_DET |	     \
			    AUX_SW_RX_RECV_INVALID_H |	     \
			    AUX_SW_RX_RECV_INVALID_V)

#घोषणा AUX_SW_REPLY_GET_BYTE_COUNT(x) (((x) >> 24) & 0x1f)

#घोषणा BARE_ADDRESS_SIZE 3

अटल स्थिर u32 aux_offset[] =
अणु
	0x6200 - 0x6200,
	0x6250 - 0x6200,
	0x62a0 - 0x6200,
	0x6300 - 0x6200,
	0x6350 - 0x6200,
	0x63a0 - 0x6200,
पूर्ण;

sमाप_प्रकार
radeon_dp_aux_transfer_native(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा radeon_i2c_chan *chan =
		container_of(aux, काष्ठा radeon_i2c_chan, aux);
	काष्ठा drm_device *dev = chan->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक ret = 0, i;
	uपूर्णांक32_t पंचांगp, ack = 0;
	पूर्णांक instance = chan->rec.i2c_id & 0xf;
	u8 byte;
	u8 *buf = msg->buffer;
	पूर्णांक retry_count = 0;
	पूर्णांक bytes;
	पूर्णांक msize;
	bool is_ग_लिखो = false;

	अगर (WARN_ON(msg->size > 16))
		वापस -E2BIG;

	चयन (msg->request & ~DP_AUX_I2C_MOT) अणु
	हाल DP_AUX_NATIVE_WRITE:
	हाल DP_AUX_I2C_WRITE:
		is_ग_लिखो = true;
		अवरोध;
	हाल DP_AUX_NATIVE_READ:
	हाल DP_AUX_I2C_READ:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* work out two sizes required */
	msize = 0;
	bytes = BARE_ADDRESS_SIZE;
	अगर (msg->size) अणु
		msize = msg->size - 1;
		bytes++;
		अगर (is_ग_लिखो)
			bytes += msg->size;
	पूर्ण

	mutex_lock(&chan->mutex);

	/* चयन the pad to aux mode */
	पंचांगp = RREG32(chan->rec.mask_clk_reg);
	पंचांगp |= (1 << 16);
	WREG32(chan->rec.mask_clk_reg, पंचांगp);

	/* setup AUX control रेजिस्टर with correct HPD pin */
	पंचांगp = RREG32(AUX_CONTROL + aux_offset[instance]);

	पंचांगp &= AUX_HPD_SEL(0x7);
	पंचांगp |= AUX_HPD_SEL(chan->rec.hpd);
	पंचांगp |= AUX_EN | AUX_LS_READ_EN;

	WREG32(AUX_CONTROL + aux_offset[instance], पंचांगp);

	/* atombios appears to ग_लिखो this twice lets copy it */
	WREG32(AUX_SW_CONTROL + aux_offset[instance],
	       AUX_SW_WR_BYTES(bytes));
	WREG32(AUX_SW_CONTROL + aux_offset[instance],
	       AUX_SW_WR_BYTES(bytes));

	/* ग_लिखो the data header पूर्णांकo the रेजिस्टरs */
	/* request, address, msg size */
	byte = (msg->request << 4) | ((msg->address >> 16) & 0xf);
	WREG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte) | AUX_SW_AUTOINCREMENT_DISABLE);

	byte = (msg->address >> 8) & 0xff;
	WREG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte));

	byte = msg->address & 0xff;
	WREG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte));

	byte = msize;
	WREG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte));

	/* अगर we are writing - ग_लिखो the msg buffer */
	अगर (is_ग_लिखो) अणु
		क्रम (i = 0; i < msg->size; i++) अणु
			WREG32(AUX_SW_DATA + aux_offset[instance],
			       AUX_SW_DATA_MASK(buf[i]));
		पूर्ण
	पूर्ण

	/* clear the ACK */
	WREG32(AUX_SW_INTERRUPT_CONTROL + aux_offset[instance], AUX_SW_DONE_ACK);

	/* ग_लिखो the size and GO bits */
	WREG32(AUX_SW_CONTROL + aux_offset[instance],
	       AUX_SW_WR_BYTES(bytes) | AUX_SW_GO);

	/* poll the status रेजिस्टरs - TODO irq support */
	करो अणु
		पंचांगp = RREG32(AUX_SW_STATUS + aux_offset[instance]);
		अगर (पंचांगp & AUX_SW_DONE) अणु
			अवरोध;
		पूर्ण
		usleep_range(100, 200);
	पूर्ण जबतक (retry_count++ < 1000);

	अगर (retry_count >= 1000) अणु
		DRM_ERROR("auxch hw never signalled completion, error %08x\n", पंचांगp);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (पंचांगp & AUX_SW_RX_TIMEOUT) अणु
		ret = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण
	अगर (पंचांगp & AUX_RX_ERROR_FLAGS) अणु
		DRM_DEBUG_KMS_RATELIMITED("dp_aux_ch flags not zero: %08x\n",
					  पंचांगp);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	bytes = AUX_SW_REPLY_GET_BYTE_COUNT(पंचांगp);
	अगर (bytes) अणु
		WREG32(AUX_SW_DATA + aux_offset[instance],
		       AUX_SW_DATA_RW | AUX_SW_AUTOINCREMENT_DISABLE);

		पंचांगp = RREG32(AUX_SW_DATA + aux_offset[instance]);
		ack = (पंचांगp >> 8) & 0xff;

		क्रम (i = 0; i < bytes - 1; i++) अणु
			पंचांगp = RREG32(AUX_SW_DATA + aux_offset[instance]);
			अगर (buf)
				buf[i] = (पंचांगp >> 8) & 0xff;
		पूर्ण
		अगर (buf)
			ret = bytes - 1;
	पूर्ण

	WREG32(AUX_SW_INTERRUPT_CONTROL + aux_offset[instance], AUX_SW_DONE_ACK);

	अगर (is_ग_लिखो)
		ret = msg->size;
करोne:
	mutex_unlock(&chan->mutex);

	अगर (ret >= 0)
		msg->reply = ack >> 4;
	वापस ret;
पूर्ण
