<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Configuration file क्रम O32 and N32 binaries.
 * Note: To be included beक्रमe lib/vdso/समय_लोofday.c
 */
#अगर defined(CONFIG_MIPS32_O32) || defined(CONFIG_MIPS32_N32)
/*
 * In हाल of a 32 bit VDSO क्रम a 64 bit kernel fake a 32 bit kernel
 * configuration.
 */
#अघोषित CONFIG_64BIT

#घोषणा BUILD_VDSO32
#घोषणा CONFIG_32BIT 1
#घोषणा CONFIG_GENERIC_ATOMIC64 1
#घोषणा BUILD_VDSO32_64

#पूर्ण_अगर

