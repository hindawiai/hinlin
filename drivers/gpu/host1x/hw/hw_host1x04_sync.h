<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 NVIDIA Corporation.
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

#अगर_अघोषित HOST1X_HW_HOST1X04_SYNC_H
#घोषणा HOST1X_HW_HOST1X04_SYNC_H

#घोषणा REGISTER_STRIDE	4

अटल अंतरभूत u32 host1x_sync_syncpt_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0xf80 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_SYNCPT(id) \
	host1x_sync_syncpt_r(id)
अटल अंतरभूत u32 host1x_sync_syncpt_thresh_cpu0_पूर्णांक_status_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0xe80 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS(id) \
	host1x_sync_syncpt_thresh_cpu0_पूर्णांक_status_r(id)
अटल अंतरभूत u32 host1x_sync_syncpt_thresh_पूर्णांक_disable_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0xf00 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE(id) \
	host1x_sync_syncpt_thresh_पूर्णांक_disable_r(id)
अटल अंतरभूत u32 host1x_sync_syncpt_thresh_पूर्णांक_enable_cpu0_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0xf20 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_SYNCPT_THRESH_INT_ENABLE_CPU0(id) \
	host1x_sync_syncpt_thresh_पूर्णांक_enable_cpu0_r(id)
अटल अंतरभूत u32 host1x_sync_cf_setup_r(अचिन्हित पूर्णांक channel)
अणु
	वापस 0xc00 + channel * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_CF_SETUP(channel) \
	host1x_sync_cf_setup_r(channel)
अटल अंतरभूत u32 host1x_sync_cf_setup_base_v(u32 r)
अणु
	वापस (r >> 0) & 0x3ff;
पूर्ण
#घोषणा HOST1X_SYNC_CF_SETUP_BASE_V(r) \
	host1x_sync_cf_setup_base_v(r)
अटल अंतरभूत u32 host1x_sync_cf_setup_limit_v(u32 r)
अणु
	वापस (r >> 16) & 0x3ff;
पूर्ण
#घोषणा HOST1X_SYNC_CF_SETUP_LIMIT_V(r) \
	host1x_sync_cf_setup_limit_v(r)
अटल अंतरभूत u32 host1x_sync_cmdproc_stop_r(व्योम)
अणु
	वापस 0xac;
पूर्ण
#घोषणा HOST1X_SYNC_CMDPROC_STOP \
	host1x_sync_cmdproc_stop_r()
अटल अंतरभूत u32 host1x_sync_ch_tearकरोwn_r(व्योम)
अणु
	वापस 0xb0;
पूर्ण
#घोषणा HOST1X_SYNC_CH_TEARDOWN \
	host1x_sync_ch_tearकरोwn_r()
अटल अंतरभूत u32 host1x_sync_usec_clk_r(व्योम)
अणु
	वापस 0x1a4;
पूर्ण
#घोषणा HOST1X_SYNC_USEC_CLK \
	host1x_sync_usec_clk_r()
अटल अंतरभूत u32 host1x_sync_ctxsw_समयout_cfg_r(व्योम)
अणु
	वापस 0x1a8;
पूर्ण
#घोषणा HOST1X_SYNC_CTXSW_TIMEOUT_CFG \
	host1x_sync_ctxsw_समयout_cfg_r()
अटल अंतरभूत u32 host1x_sync_ip_busy_समयout_r(व्योम)
अणु
	वापस 0x1bc;
पूर्ण
#घोषणा HOST1X_SYNC_IP_BUSY_TIMEOUT \
	host1x_sync_ip_busy_समयout_r()
अटल अंतरभूत u32 host1x_sync_mlock_owner_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0x340 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_MLOCK_OWNER(id) \
	host1x_sync_mlock_owner_r(id)
अटल अंतरभूत u32 host1x_sync_mlock_owner_chid_v(u32 v)
अणु
	वापस (v >> 8) & 0xf;
पूर्ण
#घोषणा HOST1X_SYNC_MLOCK_OWNER_CHID_V(v) \
	host1x_sync_mlock_owner_chid_v(v)
अटल अंतरभूत u32 host1x_sync_mlock_owner_cpu_owns_v(u32 r)
अणु
	वापस (r >> 1) & 0x1;
पूर्ण
#घोषणा HOST1X_SYNC_MLOCK_OWNER_CPU_OWNS_V(r) \
	host1x_sync_mlock_owner_cpu_owns_v(r)
अटल अंतरभूत u32 host1x_sync_mlock_owner_ch_owns_v(u32 r)
अणु
	वापस (r >> 0) & 0x1;
पूर्ण
#घोषणा HOST1X_SYNC_MLOCK_OWNER_CH_OWNS_V(r) \
	host1x_sync_mlock_owner_ch_owns_v(r)
अटल अंतरभूत u32 host1x_sync_syncpt_पूर्णांक_thresh_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0x1380 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_SYNCPT_INT_THRESH(id) \
	host1x_sync_syncpt_पूर्णांक_thresh_r(id)
अटल अंतरभूत u32 host1x_sync_syncpt_base_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0x600 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_SYNCPT_BASE(id) \
	host1x_sync_syncpt_base_r(id)
अटल अंतरभूत u32 host1x_sync_syncpt_cpu_incr_r(अचिन्हित पूर्णांक id)
अणु
	वापस 0xf60 + id * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_SYNCPT_CPU_INCR(id) \
	host1x_sync_syncpt_cpu_incr_r(id)
अटल अंतरभूत u32 host1x_sync_cbपढ़ो_r(अचिन्हित पूर्णांक channel)
अणु
	वापस 0xc80 + channel * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_CBREAD(channel) \
	host1x_sync_cbपढ़ो_r(channel)
अटल अंतरभूत u32 host1x_sync_cfpeek_ctrl_r(व्योम)
अणु
	वापस 0x74c;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_CTRL \
	host1x_sync_cfpeek_ctrl_r()
अटल अंतरभूत u32 host1x_sync_cfpeek_ctrl_addr_f(u32 v)
अणु
	वापस (v & 0x3ff) << 0;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_CTRL_ADDR_F(v) \
	host1x_sync_cfpeek_ctrl_addr_f(v)
अटल अंतरभूत u32 host1x_sync_cfpeek_ctrl_channr_f(u32 v)
अणु
	वापस (v & 0xf) << 16;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_CTRL_CHANNR_F(v) \
	host1x_sync_cfpeek_ctrl_channr_f(v)
अटल अंतरभूत u32 host1x_sync_cfpeek_ctrl_ena_f(u32 v)
अणु
	वापस (v & 0x1) << 31;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_CTRL_ENA_F(v) \
	host1x_sync_cfpeek_ctrl_ena_f(v)
अटल अंतरभूत u32 host1x_sync_cfpeek_पढ़ो_r(व्योम)
अणु
	वापस 0x750;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_READ \
	host1x_sync_cfpeek_पढ़ो_r()
अटल अंतरभूत u32 host1x_sync_cfpeek_ptrs_r(व्योम)
अणु
	वापस 0x754;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_PTRS \
	host1x_sync_cfpeek_ptrs_r()
अटल अंतरभूत u32 host1x_sync_cfpeek_ptrs_cf_rd_ptr_v(u32 r)
अणु
	वापस (r >> 0) & 0x3ff;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_PTRS_CF_RD_PTR_V(r) \
	host1x_sync_cfpeek_ptrs_cf_rd_ptr_v(r)
अटल अंतरभूत u32 host1x_sync_cfpeek_ptrs_cf_wr_ptr_v(u32 r)
अणु
	वापस (r >> 16) & 0x3ff;
पूर्ण
#घोषणा HOST1X_SYNC_CFPEEK_PTRS_CF_WR_PTR_V(r) \
	host1x_sync_cfpeek_ptrs_cf_wr_ptr_v(r)
अटल अंतरभूत u32 host1x_sync_cbstat_r(अचिन्हित पूर्णांक channel)
अणु
	वापस 0xcc0 + channel * REGISTER_STRIDE;
पूर्ण
#घोषणा HOST1X_SYNC_CBSTAT(channel) \
	host1x_sync_cbstat_r(channel)
अटल अंतरभूत u32 host1x_sync_cbstat_cboffset_v(u32 r)
अणु
	वापस (r >> 0) & 0xffff;
पूर्ण
#घोषणा HOST1X_SYNC_CBSTAT_CBOFFSET_V(r) \
	host1x_sync_cbstat_cboffset_v(r)
अटल अंतरभूत u32 host1x_sync_cbstat_cbclass_v(u32 r)
अणु
	वापस (r >> 16) & 0x3ff;
पूर्ण
#घोषणा HOST1X_SYNC_CBSTAT_CBCLASS_V(r) \
	host1x_sync_cbstat_cbclass_v(r)

#पूर्ण_अगर
