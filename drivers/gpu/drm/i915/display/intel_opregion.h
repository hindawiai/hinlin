<शैली गुरु>
/*
 * Copyright तऊ 2008-2017 Intel Corporation
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
 */

#अगर_अघोषित _INTEL_OPREGION_H_
#घोषणा _INTEL_OPREGION_H_

#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_encoder;

काष्ठा opregion_header;
काष्ठा opregion_acpi;
काष्ठा opregion_swsci;
काष्ठा opregion_asle;

काष्ठा पूर्णांकel_opregion अणु
	काष्ठा opregion_header *header;
	काष्ठा opregion_acpi *acpi;
	काष्ठा opregion_swsci *swsci;
	u32 swsci_gbda_sub_functions;
	u32 swsci_sbcb_sub_functions;
	काष्ठा opregion_asle *asle;
	व्योम *rvda;
	व्योम *vbt_firmware;
	स्थिर व्योम *vbt;
	u32 vbt_size;
	u32 *lid_state;
	काष्ठा work_काष्ठा asle_work;
	काष्ठा notअगरier_block acpi_notअगरier;
पूर्ण;

#घोषणा OPREGION_SIZE            (8 * 1024)

#अगर_घोषित CONFIG_ACPI

पूर्णांक पूर्णांकel_opregion_setup(काष्ठा drm_i915_निजी *dev_priv);

व्योम पूर्णांकel_opregion_रेजिस्टर(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_opregion_unरेजिस्टर(काष्ठा drm_i915_निजी *dev_priv);

व्योम पूर्णांकel_opregion_resume(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_opregion_suspend(काष्ठा drm_i915_निजी *dev_priv,
			    pci_घातer_t state);

व्योम पूर्णांकel_opregion_asle_पूर्णांकr(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_opregion_notअगरy_encoder(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
				  bool enable);
पूर्णांक पूर्णांकel_opregion_notअगरy_adapter(काष्ठा drm_i915_निजी *dev_priv,
				  pci_घातer_t state);
पूर्णांक पूर्णांकel_opregion_get_panel_type(काष्ठा drm_i915_निजी *dev_priv);

#अन्यथा /* CONFIG_ACPI*/

अटल अंतरभूत पूर्णांक पूर्णांकel_opregion_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_opregion_रेजिस्टर(काष्ठा drm_i915_निजी *dev_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_opregion_unरेजिस्टर(काष्ठा drm_i915_निजी *dev_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_opregion_resume(काष्ठा drm_i915_निजी *dev_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_opregion_suspend(काष्ठा drm_i915_निजी *dev_priv,
					  pci_घातer_t state)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_opregion_asle_पूर्णांकr(काष्ठा drm_i915_निजी *dev_priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
पूर्णांकel_opregion_notअगरy_encoder(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder, bool enable)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
पूर्णांकel_opregion_notअगरy_adapter(काष्ठा drm_i915_निजी *dev, pci_घातer_t state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_opregion_get_panel_type(काष्ठा drm_i915_निजी *dev)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_ACPI */

#पूर्ण_अगर
