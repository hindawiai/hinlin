<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __VDSO_DATAPAGE_H
#घोषणा __VDSO_DATAPAGE_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <uapi/linux/समय.स>
#समावेश <uapi/linux/types.h>
#समावेश <uapi/यंत्र-generic/त्रुटि_सं-base.h>

#समावेश <vdso/bits.h>
#समावेश <vdso/घड़ीsource.h>
#समावेश <vdso/kसमय.स>
#समावेश <vdso/सीमा.स>
#समावेश <vdso/math64.h>
#समावेश <vdso/processor.h>
#समावेश <vdso/समय.स>
#समावेश <vdso/समय32.h>
#समावेश <vdso/समय64.h>

#अगर_घोषित CONFIG_ARCH_HAS_VDSO_DATA
#समावेश <यंत्र/vdso/data.h>
#अन्यथा
काष्ठा arch_vdso_data अणुपूर्ण;
#पूर्ण_अगर

#घोषणा VDSO_BASES	(CLOCK_TAI + 1)
#घोषणा VDSO_HRES	(BIT(CLOCK_REALTIME)		| \
			 BIT(CLOCK_MONOTONIC)		| \
			 BIT(CLOCK_BOOTTIME)		| \
			 BIT(CLOCK_TAI))
#घोषणा VDSO_COARSE	(BIT(CLOCK_REALTIME_COARSE)	| \
			 BIT(CLOCK_MONOTONIC_COARSE))
#घोषणा VDSO_RAW	(BIT(CLOCK_MONOTONIC_RAW))

#घोषणा CS_HRES_COARSE	0
#घोषणा CS_RAW		1
#घोषणा CS_BASES	(CS_RAW + 1)

/**
 * काष्ठा vdso_बारtamp - baseसमय per घड़ी_id
 * @sec:	seconds
 * @nsec:	nanoseconds
 *
 * There is one vdso_बारtamp object in vvar क्रम each vDSO-accelerated
 * घड़ी_id. For high-resolution घड़ीs, this encodes the समय
 * corresponding to vdso_data.cycle_last. For coarse घड़ीs this encodes
 * the actual समय.
 *
 * To be noticed that क्रम highres घड़ीs nsec is left-shअगरted by
 * vdso_data.cs[x].shअगरt.
 */
काष्ठा vdso_बारtamp अणु
	u64	sec;
	u64	nsec;
पूर्ण;

/**
 * काष्ठा vdso_data - vdso datapage representation
 * @seq:		समयbase sequence counter
 * @घड़ी_mode:		घड़ी mode
 * @cycle_last:		समयbase at घड़ीsource init
 * @mask:		घड़ीsource mask
 * @mult:		घड़ीsource multiplier
 * @shअगरt:		घड़ीsource shअगरt
 * @baseसमय[घड़ी_id]:	baseसमय per घड़ी_id
 * @offset[घड़ी_id]:	समय namespace offset per घड़ी_id
 * @tz_minuteswest:	minutes west of Greenwich
 * @tz_dstसमय:		type of DST correction
 * @hrसमयr_res:	hrसमयr resolution
 * @__unused:		unused
 * @arch_data:		architecture specअगरic data (optional, शेषs
 *			to an empty काष्ठा)
 *
 * vdso_data will be accessed by 64 bit and compat code at the same समय
 * so we should be careful beक्रमe modअगरying this काष्ठाure.
 *
 * @baseसमय is used to store the base समय क्रम the प्रणाली wide समय getter
 * VVAR page.
 *
 * @offset is used by the special समय namespace VVAR pages which are
 * installed instead of the real VVAR page. These namespace pages must set
 * @seq to 1 and @घड़ी_mode to VDSO_CLOCKMODE_TIMENS to क्रमce the code पूर्णांकo
 * the समय namespace slow path. The namespace aware functions retrieve the
 * real प्रणाली wide VVAR page, पढ़ो host समय and add the per घड़ी offset.
 * For घड़ीs which are not affected by समय namespace adjusपंचांगent the
 * offset must be zero.
 */
काष्ठा vdso_data अणु
	u32			seq;

	s32			घड़ी_mode;
	u64			cycle_last;
	u64			mask;
	u32			mult;
	u32			shअगरt;

	जोड़ अणु
		काष्ठा vdso_बारtamp	baseसमय[VDSO_BASES];
		काष्ठा समयns_offset	offset[VDSO_BASES];
	पूर्ण;

	s32			tz_minuteswest;
	s32			tz_dstसमय;
	u32			hrसमयr_res;
	u32			__unused;

	काष्ठा arch_vdso_data	arch_data;
पूर्ण;

/*
 * We use the hidden visibility to prevent the compiler from generating a GOT
 * relocation. Not only is going through a GOT useless (the entry couldn't and
 * must not be overridden by another library), it करोes not even work: the linker
 * cannot generate an असलolute address to the data page.
 *
 * With the hidden visibility, the compiler simply generates a PC-relative
 * relocation, and this is what we need.
 */
बाह्य काष्ठा vdso_data _vdso_data[CS_BASES] __attribute__((visibility("hidden")));
बाह्य काष्ठा vdso_data _समयns_data[CS_BASES] __attribute__((visibility("hidden")));

/*
 * The generic vDSO implementation requires that समय_लोofday.h
 * provides:
 * - __arch_get_vdso_data(): to get the vdso datapage.
 * - __arch_get_hw_counter(): to get the hw counter based on the
 *   घड़ी_mode.
 * - समय_लोofday_fallback(): fallback क्रम समय_लोofday.
 * - घड़ी_समय_लो_fallback(): fallback क्रम घड़ी_समय_लो.
 * - घड़ी_getres_fallback(): fallback क्रम घड़ी_getres.
 */
#अगर_घोषित ENABLE_COMPAT_VDSO
#समावेश <यंत्र/vdso/compat_समय_लोofday.h>
#अन्यथा
#समावेश <यंत्र/vdso/समय_लोofday.h>
#पूर्ण_अगर /* ENABLE_COMPAT_VDSO */

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __VDSO_DATAPAGE_H */
