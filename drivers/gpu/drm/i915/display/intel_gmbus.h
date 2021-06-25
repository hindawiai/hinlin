<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_GMBUS_H__
#घोषणा __INTEL_GMBUS_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा i2c_adapter;

#घोषणा GMBUS_PIN_DISABLED	0
#घोषणा GMBUS_PIN_SSC		1
#घोषणा GMBUS_PIN_VGADDC	2
#घोषणा GMBUS_PIN_PANEL		3
#घोषणा GMBUS_PIN_DPD_CHV	3 /* HDMID_CHV */
#घोषणा GMBUS_PIN_DPC		4 /* HDMIC */
#घोषणा GMBUS_PIN_DPB		5 /* SDVO, HDMIB */
#घोषणा GMBUS_PIN_DPD		6 /* HDMID */
#घोषणा GMBUS_PIN_RESERVED	7 /* 7 reserved */
#घोषणा GMBUS_PIN_1_BXT		1 /* BXT+ (atom) and CNP+ (big core) */
#घोषणा GMBUS_PIN_2_BXT		2
#घोषणा GMBUS_PIN_3_BXT		3
#घोषणा GMBUS_PIN_4_CNP		4
#घोषणा GMBUS_PIN_9_TC1_ICP	9
#घोषणा GMBUS_PIN_10_TC2_ICP	10
#घोषणा GMBUS_PIN_11_TC3_ICP	11
#घोषणा GMBUS_PIN_12_TC4_ICP	12
#घोषणा GMBUS_PIN_13_TC5_TGP	13
#घोषणा GMBUS_PIN_14_TC6_TGP	14

#घोषणा GMBUS_NUM_PINS	15 /* including 0 */

पूर्णांक पूर्णांकel_gmbus_setup(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_gmbus_tearकरोwn(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_gmbus_is_valid_pin(काष्ठा drm_i915_निजी *dev_priv,
			      अचिन्हित पूर्णांक pin);
पूर्णांक पूर्णांकel_gmbus_output_aksv(काष्ठा i2c_adapter *adapter);

काष्ठा i2c_adapter *
पूर्णांकel_gmbus_get_adapter(काष्ठा drm_i915_निजी *dev_priv, अचिन्हित पूर्णांक pin);
व्योम पूर्णांकel_gmbus_set_speed(काष्ठा i2c_adapter *adapter, पूर्णांक speed);
व्योम पूर्णांकel_gmbus_क्रमce_bit(काष्ठा i2c_adapter *adapter, bool क्रमce_bit);
bool पूर्णांकel_gmbus_is_क्रमced_bit(काष्ठा i2c_adapter *adapter);
व्योम पूर्णांकel_gmbus_reset(काष्ठा drm_i915_निजी *dev_priv);

#पूर्ण_अगर /* __INTEL_GMBUS_H__ */
