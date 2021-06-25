<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NTP_INTERNAL_H
#घोषणा _LINUX_NTP_INTERNAL_H

बाह्य व्योम ntp_init(व्योम);
बाह्य व्योम ntp_clear(व्योम);
/* Returns how दीर्घ ticks are at present, in ns / 2^NTP_SCALE_SHIFT. */
बाह्य u64 ntp_tick_length(व्योम);
बाह्य kसमय_प्रकार ntp_get_next_leap(व्योम);
बाह्य पूर्णांक second_overflow(समय64_t secs);
बाह्य पूर्णांक __करो_adjसमयx(काष्ठा __kernel_समयx *txc,
			 स्थिर काष्ठा बारpec64 *ts,
			 s32 *समय_प्रकारai, काष्ठा audit_ntp_data *ad);
बाह्य व्योम __hardpps(स्थिर काष्ठा बारpec64 *phase_ts, स्थिर काष्ठा बारpec64 *raw_ts);

#अगर defined(CONFIG_GENERIC_CMOS_UPDATE) || defined(CONFIG_RTC_SYSTOHC)
बाह्य व्योम ntp_notअगरy_cmos_समयr(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ntp_notअगरy_cmos_समयr(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_NTP_INTERNAL_H */
