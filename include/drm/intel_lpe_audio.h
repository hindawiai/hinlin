<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
 */

#अगर_अघोषित _INTEL_LPE_AUDIO_H_
#घोषणा _INTEL_LPE_AUDIO_H_

#समावेश <linux/types.h>
#समावेश <linux/spinlock_types.h>

काष्ठा platक्रमm_device;

#घोषणा HDMI_MAX_ELD_BYTES	128

काष्ठा पूर्णांकel_hdmi_lpe_audio_port_pdata अणु
	u8 eld[HDMI_MAX_ELD_BYTES];
	पूर्णांक port;
	पूर्णांक pipe;
	पूर्णांक ls_घड़ी;
	bool dp_output;
पूर्ण;

काष्ठा पूर्णांकel_hdmi_lpe_audio_pdata अणु
	काष्ठा पूर्णांकel_hdmi_lpe_audio_port_pdata port[3]; /* क्रम ports B,C,D */
	पूर्णांक num_ports;
	पूर्णांक num_pipes;

	व्योम (*notअगरy_audio_lpe)(काष्ठा platक्रमm_device *pdev, पूर्णांक port); /* port: 0==B,1==C,2==D */
	spinlock_t lpe_audio_slock;
पूर्ण;

#पूर्ण_अगर /* _I915_LPE_AUDIO_H_ */
