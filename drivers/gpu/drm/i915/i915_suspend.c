<शैली गुरु>
/*
 *
 * Copyright 2008 (c) Intel Corporation
 *   Jesse Barnes <jbarnes@virtuousgeek.org>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश "display/intel_de.h"
#समावेश "display/intel_fbc.h"
#समावेश "display/intel_gmbus.h"
#समावेश "display/intel_vga.h"

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "i915_suspend.h"

अटल व्योम पूर्णांकel_save_swf(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक i;

	/* Scratch space */
	अगर (IS_GEN(dev_priv, 2) && IS_MOBILE(dev_priv)) अणु
		क्रम (i = 0; i < 7; i++) अणु
			dev_priv->regfile.saveSWF0[i] = पूर्णांकel_de_पढ़ो(dev_priv, SWF0(i));
			dev_priv->regfile.saveSWF1[i] = पूर्णांकel_de_पढ़ो(dev_priv, SWF1(i));
		पूर्ण
		क्रम (i = 0; i < 3; i++)
			dev_priv->regfile.saveSWF3[i] = पूर्णांकel_de_पढ़ो(dev_priv, SWF3(i));
	पूर्ण अन्यथा अगर (IS_GEN(dev_priv, 2)) अणु
		क्रम (i = 0; i < 7; i++)
			dev_priv->regfile.saveSWF1[i] = पूर्णांकel_de_पढ़ो(dev_priv, SWF1(i));
	पूर्ण अन्यथा अगर (HAS_GMCH(dev_priv)) अणु
		क्रम (i = 0; i < 16; i++) अणु
			dev_priv->regfile.saveSWF0[i] = पूर्णांकel_de_पढ़ो(dev_priv, SWF0(i));
			dev_priv->regfile.saveSWF1[i] = पूर्णांकel_de_पढ़ो(dev_priv, SWF1(i));
		पूर्ण
		क्रम (i = 0; i < 3; i++)
			dev_priv->regfile.saveSWF3[i] = पूर्णांकel_de_पढ़ो(dev_priv, SWF3(i));
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_restore_swf(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक i;

	/* Scratch space */
	अगर (IS_GEN(dev_priv, 2) && IS_MOBILE(dev_priv)) अणु
		क्रम (i = 0; i < 7; i++) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, SWF0(i), dev_priv->regfile.saveSWF0[i]);
			पूर्णांकel_de_ग_लिखो(dev_priv, SWF1(i), dev_priv->regfile.saveSWF1[i]);
		पूर्ण
		क्रम (i = 0; i < 3; i++)
			पूर्णांकel_de_ग_लिखो(dev_priv, SWF3(i), dev_priv->regfile.saveSWF3[i]);
	पूर्ण अन्यथा अगर (IS_GEN(dev_priv, 2)) अणु
		क्रम (i = 0; i < 7; i++)
			पूर्णांकel_de_ग_लिखो(dev_priv, SWF1(i), dev_priv->regfile.saveSWF1[i]);
	पूर्ण अन्यथा अगर (HAS_GMCH(dev_priv)) अणु
		क्रम (i = 0; i < 16; i++) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, SWF0(i), dev_priv->regfile.saveSWF0[i]);
			पूर्णांकel_de_ग_लिखो(dev_priv, SWF1(i), dev_priv->regfile.saveSWF1[i]);
		पूर्ण
		क्रम (i = 0; i < 3; i++)
			पूर्णांकel_de_ग_लिखो(dev_priv, SWF3(i), dev_priv->regfile.saveSWF3[i]);
	पूर्ण
पूर्ण

व्योम i915_save_display(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);

	/* Display arbitration control */
	अगर (INTEL_GEN(dev_priv) <= 4)
		dev_priv->regfile.saveDSPARB = पूर्णांकel_de_पढ़ो(dev_priv, DSPARB);

	अगर (IS_GEN(dev_priv, 4))
		pci_पढ़ो_config_word(pdev, GCDGMBUS,
				     &dev_priv->regfile.saveGCDGMBUS);

	पूर्णांकel_save_swf(dev_priv);
पूर्ण

व्योम i915_restore_display(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);

	पूर्णांकel_restore_swf(dev_priv);

	अगर (IS_GEN(dev_priv, 4))
		pci_ग_लिखो_config_word(pdev, GCDGMBUS,
				      dev_priv->regfile.saveGCDGMBUS);

	/* Display arbitration */
	अगर (INTEL_GEN(dev_priv) <= 4)
		पूर्णांकel_de_ग_लिखो(dev_priv, DSPARB, dev_priv->regfile.saveDSPARB);

	/* only restore FBC info on the platक्रमm that supports FBC*/
	पूर्णांकel_fbc_global_disable(dev_priv);

	पूर्णांकel_vga_redisable(dev_priv);

	पूर्णांकel_gmbus_reset(dev_priv);
पूर्ण
