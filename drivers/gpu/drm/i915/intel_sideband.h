<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

#अगर_अघोषित _INTEL_SIDEBAND_H_
#घोषणा _INTEL_SIDEBAND_H_

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
क्रमागत pipe;

क्रमागत पूर्णांकel_sbi_destination अणु
	SBI_ICLK,
	SBI_MPHY,
पूर्ण;

क्रमागत अणु
	VLV_IOSF_SB_BUNIT,
	VLV_IOSF_SB_CCK,
	VLV_IOSF_SB_CCU,
	VLV_IOSF_SB_DPIO,
	VLV_IOSF_SB_FLISDSI,
	VLV_IOSF_SB_GPIO,
	VLV_IOSF_SB_NC,
	VLV_IOSF_SB_PUNIT,
पूर्ण;

व्योम vlv_iosf_sb_get(काष्ठा drm_i915_निजी *i915, अचिन्हित दीर्घ ports);
u32 vlv_iosf_sb_पढ़ो(काष्ठा drm_i915_निजी *i915, u8 port, u32 reg);
व्योम vlv_iosf_sb_ग_लिखो(काष्ठा drm_i915_निजी *i915,
		       u8 port, u32 reg, u32 val);
व्योम vlv_iosf_sb_put(काष्ठा drm_i915_निजी *i915, अचिन्हित दीर्घ ports);

अटल अंतरभूत व्योम vlv_bunit_get(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_get(i915, BIT(VLV_IOSF_SB_BUNIT));
पूर्ण

u32 vlv_bunit_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg);
व्योम vlv_bunit_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val);

अटल अंतरभूत व्योम vlv_bunit_put(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_BUNIT));
पूर्ण

अटल अंतरभूत व्योम vlv_cck_get(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_get(i915, BIT(VLV_IOSF_SB_CCK));
पूर्ण

u32 vlv_cck_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg);
व्योम vlv_cck_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val);

अटल अंतरभूत व्योम vlv_cck_put(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_CCK));
पूर्ण

अटल अंतरभूत व्योम vlv_ccu_get(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_get(i915, BIT(VLV_IOSF_SB_CCU));
पूर्ण

u32 vlv_ccu_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg);
व्योम vlv_ccu_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val);

अटल अंतरभूत व्योम vlv_ccu_put(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_CCU));
पूर्ण

अटल अंतरभूत व्योम vlv_dpio_get(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_get(i915, BIT(VLV_IOSF_SB_DPIO));
पूर्ण

u32 vlv_dpio_पढ़ो(काष्ठा drm_i915_निजी *i915, क्रमागत pipe pipe, पूर्णांक reg);
व्योम vlv_dpio_ग_लिखो(काष्ठा drm_i915_निजी *i915,
		    क्रमागत pipe pipe, पूर्णांक reg, u32 val);

अटल अंतरभूत व्योम vlv_dpio_put(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_DPIO));
पूर्ण

अटल अंतरभूत व्योम vlv_flisdsi_get(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_get(i915, BIT(VLV_IOSF_SB_FLISDSI));
पूर्ण

u32 vlv_flisdsi_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg);
व्योम vlv_flisdsi_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val);

अटल अंतरभूत व्योम vlv_flisdsi_put(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_FLISDSI));
पूर्ण

अटल अंतरभूत व्योम vlv_nc_get(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_get(i915, BIT(VLV_IOSF_SB_NC));
पूर्ण

u32 vlv_nc_पढ़ो(काष्ठा drm_i915_निजी *i915, u8 addr);

अटल अंतरभूत व्योम vlv_nc_put(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_NC));
पूर्ण

अटल अंतरभूत व्योम vlv_punit_get(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_get(i915, BIT(VLV_IOSF_SB_PUNIT));
पूर्ण

u32 vlv_punit_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 addr);
पूर्णांक vlv_punit_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 addr, u32 val);

अटल अंतरभूत व्योम vlv_punit_put(काष्ठा drm_i915_निजी *i915)
अणु
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_PUNIT));
पूर्ण

u32 पूर्णांकel_sbi_पढ़ो(काष्ठा drm_i915_निजी *i915, u16 reg,
		   क्रमागत पूर्णांकel_sbi_destination destination);
व्योम पूर्णांकel_sbi_ग_लिखो(काष्ठा drm_i915_निजी *i915, u16 reg, u32 value,
		     क्रमागत पूर्णांकel_sbi_destination destination);

पूर्णांक sandybridge_pcode_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 mbox,
			   u32 *val, u32 *val1);
पूर्णांक sandybridge_pcode_ग_लिखो_समयout(काष्ठा drm_i915_निजी *i915, u32 mbox,
				    u32 val, पूर्णांक fast_समयout_us,
				    पूर्णांक slow_समयout_ms);
#घोषणा sandybridge_pcode_ग_लिखो(i915, mbox, val)	\
	sandybridge_pcode_ग_लिखो_समयout(i915, mbox, val, 500, 0)

पूर्णांक skl_pcode_request(काष्ठा drm_i915_निजी *i915, u32 mbox, u32 request,
		      u32 reply_mask, u32 reply, पूर्णांक समयout_base_ms);

व्योम पूर्णांकel_pcode_init(काष्ठा drm_i915_निजी *i915);

#पूर्ण_अगर /* _INTEL_SIDEBAND_H */
