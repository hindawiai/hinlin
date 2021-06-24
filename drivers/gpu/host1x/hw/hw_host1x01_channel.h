<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2013, NVIDIA Corporation.
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

#अगर_अघोषित __hw_host1x_channel_host1x_h__
#घोषणा __hw_host1x_channel_host1x_h__

अटल अंतरभूत u32 host1x_channel_fअगरostat_r(व्योम)
अणु
	वापस 0x0;
पूर्ण
#घोषणा HOST1X_CHANNEL_FIFOSTAT \
	host1x_channel_fअगरostat_r()
अटल अंतरभूत u32 host1x_channel_fअगरostat_cfempty_v(u32 r)
अणु
	वापस (r >> 10) & 0x1;
पूर्ण
#घोषणा HOST1X_CHANNEL_FIFOSTAT_CFEMPTY_V(r) \
	host1x_channel_fअगरostat_cfempty_v(r)
अटल अंतरभूत u32 host1x_channel_dmastart_r(व्योम)
अणु
	वापस 0x14;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMASTART \
	host1x_channel_dmastart_r()
अटल अंतरभूत u32 host1x_channel_dmaput_r(व्योम)
अणु
	वापस 0x18;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMAPUT \
	host1x_channel_dmaput_r()
अटल अंतरभूत u32 host1x_channel_dmaget_r(व्योम)
अणु
	वापस 0x1c;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMAGET \
	host1x_channel_dmaget_r()
अटल अंतरभूत u32 host1x_channel_dmaend_r(व्योम)
अणु
	वापस 0x20;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMAEND \
	host1x_channel_dmaend_r()
अटल अंतरभूत u32 host1x_channel_dmactrl_r(व्योम)
अणु
	वापस 0x24;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMACTRL \
	host1x_channel_dmactrl_r()
अटल अंतरभूत u32 host1x_channel_dmactrl_dmastop(व्योम)
अणु
	वापस 1 << 0;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMACTRL_DMASTOP \
	host1x_channel_dmactrl_dmastop()
अटल अंतरभूत u32 host1x_channel_dmactrl_dmastop_v(u32 r)
अणु
	वापस (r >> 0) & 0x1;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMACTRL_DMASTOP_V(r) \
	host1x_channel_dmactrl_dmastop_v(r)
अटल अंतरभूत u32 host1x_channel_dmactrl_dmagetrst(व्योम)
अणु
	वापस 1 << 1;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMACTRL_DMAGETRST \
	host1x_channel_dmactrl_dmagetrst()
अटल अंतरभूत u32 host1x_channel_dmactrl_dमुख्यitget(व्योम)
अणु
	वापस 1 << 2;
पूर्ण
#घोषणा HOST1X_CHANNEL_DMACTRL_DMAINITGET \
	host1x_channel_dmactrl_dमुख्यitget()
#पूर्ण_अगर
