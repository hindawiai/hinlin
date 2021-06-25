<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 NVIDIA Corporation.
 */

 /*
  * Function naming determines पूर्णांकended use:
  *
  *     <x>_r(व्योम) : Returns the offset क्रम रेजिस्टर <x>.
  *
  *     <x>_w(व्योम) : Returns the word offset क्रम word (4 byte) element <x>.
  *
  *     <x>_<y>_s(व्योम) : Returns size of field <y> of रेजिस्टर <x> in bits.
  *
  *     <x>_<y>_f(u32 v) : Returns a value based on 'v' which has been shअगरted
  *         and masked to place it at field <y> of रेजिस्टर <x>.  This value
  *         can be |'d with others to produce a full रेजिस्टर value क्रम
  *         रेजिस्टर <x>.
  *
  *     <x>_<y>_m(व्योम) : Returns a mask क्रम field <y> of रेजिस्टर <x>.  This
  *         value can be ~'d and then &'d to clear the value of field <y> क्रम
  *         रेजिस्टर <x>.
  *
  *     <x>_<y>_<z>_f(व्योम) : Returns the स्थिरant value <z> after being shअगरted
  *         to place it at field <y> of रेजिस्टर <x>.  This value can be |'d
  *         with others to produce a full रेजिस्टर value क्रम <x>.
  *
  *     <x>_<y>_v(u32 r) : Returns the value of field <y> from a full रेजिस्टर
  *         <x> value 'r' after being shअगरted to place its LSB at bit 0.
  *         This value is suitable क्रम direct comparison with other unshअगरted
  *         values appropriate क्रम use in field <y> of रेजिस्टर <x>.
  *
  *     <x>_<y>_<z>_v(व्योम) : Returns the स्थिरant value क्रम <z> defined क्रम
  *         field <y> of रेजिस्टर <x>.  This value is suitable क्रम direct
  *         comparison with unshअगरted values appropriate क्रम use in field <y>
  *         of रेजिस्टर <x>.
  */

#अगर_अघोषित HOST1X_HW_HOST1X05_UCLASS_H
#घोषणा HOST1X_HW_HOST1X05_UCLASS_H

अटल अंतरभूत u32 host1x_uclass_incr_syncpt_r(व्योम)
अणु
	वापस 0x0;
पूर्ण
#घोषणा HOST1X_UCLASS_INCR_SYNCPT \
	host1x_uclass_incr_syncpt_r()
अटल अंतरभूत u32 host1x_uclass_incr_syncpt_cond_f(u32 v)
अणु
	वापस (v & 0xff) << 8;
पूर्ण
#घोषणा HOST1X_UCLASS_INCR_SYNCPT_COND_F(v) \
	host1x_uclass_incr_syncpt_cond_f(v)
अटल अंतरभूत u32 host1x_uclass_incr_syncpt_indx_f(u32 v)
अणु
	वापस (v & 0xff) << 0;
पूर्ण
#घोषणा HOST1X_UCLASS_INCR_SYNCPT_INDX_F(v) \
	host1x_uclass_incr_syncpt_indx_f(v)
अटल अंतरभूत u32 host1x_uclass_रुको_syncpt_r(व्योम)
अणु
	वापस 0x8;
पूर्ण
#घोषणा HOST1X_UCLASS_WAIT_SYNCPT \
	host1x_uclass_रुको_syncpt_r()
अटल अंतरभूत u32 host1x_uclass_रुको_syncpt_indx_f(u32 v)
अणु
	वापस (v & 0xff) << 24;
पूर्ण
#घोषणा HOST1X_UCLASS_WAIT_SYNCPT_INDX_F(v) \
	host1x_uclass_रुको_syncpt_indx_f(v)
अटल अंतरभूत u32 host1x_uclass_रुको_syncpt_thresh_f(u32 v)
अणु
	वापस (v & 0xffffff) << 0;
पूर्ण
#घोषणा HOST1X_UCLASS_WAIT_SYNCPT_THRESH_F(v) \
	host1x_uclass_रुको_syncpt_thresh_f(v)
अटल अंतरभूत u32 host1x_uclass_रुको_syncpt_base_r(व्योम)
अणु
	वापस 0x9;
पूर्ण
#घोषणा HOST1X_UCLASS_WAIT_SYNCPT_BASE \
	host1x_uclass_रुको_syncpt_base_r()
अटल अंतरभूत u32 host1x_uclass_रुको_syncpt_base_indx_f(u32 v)
अणु
	वापस (v & 0xff) << 24;
पूर्ण
#घोषणा HOST1X_UCLASS_WAIT_SYNCPT_BASE_INDX_F(v) \
	host1x_uclass_रुको_syncpt_base_indx_f(v)
अटल अंतरभूत u32 host1x_uclass_रुको_syncpt_base_base_indx_f(u32 v)
अणु
	वापस (v & 0xff) << 16;
पूर्ण
#घोषणा HOST1X_UCLASS_WAIT_SYNCPT_BASE_BASE_INDX_F(v) \
	host1x_uclass_रुको_syncpt_base_base_indx_f(v)
अटल अंतरभूत u32 host1x_uclass_रुको_syncpt_base_offset_f(u32 v)
अणु
	वापस (v & 0xffff) << 0;
पूर्ण
#घोषणा HOST1X_UCLASS_WAIT_SYNCPT_BASE_OFFSET_F(v) \
	host1x_uclass_रुको_syncpt_base_offset_f(v)
अटल अंतरभूत u32 host1x_uclass_load_syncpt_base_r(व्योम)
अणु
	वापस 0xb;
पूर्ण
#घोषणा HOST1X_UCLASS_LOAD_SYNCPT_BASE \
	host1x_uclass_load_syncpt_base_r()
अटल अंतरभूत u32 host1x_uclass_load_syncpt_base_base_indx_f(u32 v)
अणु
	वापस (v & 0xff) << 24;
पूर्ण
#घोषणा HOST1X_UCLASS_LOAD_SYNCPT_BASE_BASE_INDX_F(v) \
	host1x_uclass_load_syncpt_base_base_indx_f(v)
अटल अंतरभूत u32 host1x_uclass_load_syncpt_base_value_f(u32 v)
अणु
	वापस (v & 0xffffff) << 0;
पूर्ण
#घोषणा HOST1X_UCLASS_LOAD_SYNCPT_BASE_VALUE_F(v) \
	host1x_uclass_load_syncpt_base_value_f(v)
अटल अंतरभूत u32 host1x_uclass_incr_syncpt_base_base_indx_f(u32 v)
अणु
	वापस (v & 0xff) << 24;
पूर्ण
#घोषणा HOST1X_UCLASS_INCR_SYNCPT_BASE_BASE_INDX_F(v) \
	host1x_uclass_incr_syncpt_base_base_indx_f(v)
अटल अंतरभूत u32 host1x_uclass_incr_syncpt_base_offset_f(u32 v)
अणु
	वापस (v & 0xffffff) << 0;
पूर्ण
#घोषणा HOST1X_UCLASS_INCR_SYNCPT_BASE_OFFSET_F(v) \
	host1x_uclass_incr_syncpt_base_offset_f(v)
अटल अंतरभूत u32 host1x_uclass_inकरोff_r(व्योम)
अणु
	वापस 0x2d;
पूर्ण
#घोषणा HOST1X_UCLASS_INDOFF \
	host1x_uclass_inकरोff_r()
अटल अंतरभूत u32 host1x_uclass_inकरोff_indbe_f(u32 v)
अणु
	वापस (v & 0xf) << 28;
पूर्ण
#घोषणा HOST1X_UCLASS_INDOFF_INDBE_F(v) \
	host1x_uclass_inकरोff_indbe_f(v)
अटल अंतरभूत u32 host1x_uclass_inकरोff_स्वतःinc_f(u32 v)
अणु
	वापस (v & 0x1) << 27;
पूर्ण
#घोषणा HOST1X_UCLASS_INDOFF_AUTOINC_F(v) \
	host1x_uclass_inकरोff_स्वतःinc_f(v)
अटल अंतरभूत u32 host1x_uclass_inकरोff_indmodid_f(u32 v)
अणु
	वापस (v & 0xff) << 18;
पूर्ण
#घोषणा HOST1X_UCLASS_INDOFF_INDMODID_F(v) \
	host1x_uclass_inकरोff_indmodid_f(v)
अटल अंतरभूत u32 host1x_uclass_inकरोff_indroffset_f(u32 v)
अणु
	वापस (v & 0xffff) << 2;
पूर्ण
#घोषणा HOST1X_UCLASS_INDOFF_INDROFFSET_F(v) \
	host1x_uclass_inकरोff_indroffset_f(v)
अटल अंतरभूत u32 host1x_uclass_inकरोff_rwn_पढ़ो_v(व्योम)
अणु
	वापस 1;
पूर्ण
#घोषणा HOST1X_UCLASS_INDOFF_INDROFFSET_F(v) \
	host1x_uclass_inकरोff_indroffset_f(v)

#पूर्ण_अगर
