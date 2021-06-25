<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#अगर_अघोषित BRCMF_CHIP_H
#घोषणा BRCMF_CHIP_H

#समावेश <linux/types.h>

#घोषणा CORE_CC_REG(base, field) \
		(base + दुरत्व(काष्ठा chipcregs, field))

/**
 * काष्ठा brcmf_chip - chip level inक्रमmation.
 *
 * @chip: chip identअगरier.
 * @chiprev: chip revision.
 * @cc_caps: chipcommon core capabilities.
 * @cc_caps_ext: chipcommon core extended capabilities.
 * @pmucaps: PMU capabilities.
 * @pmurev: PMU revision.
 * @rambase: RAM base address (only applicable क्रम ARM CR4 chips).
 * @ramsize: amount of RAM on chip including retention.
 * @srsize: amount of retention RAM on chip.
 * @name: string representation of the chip identअगरier.
 */
काष्ठा brcmf_chip अणु
	u32 chip;
	u32 chiprev;
	u32 cc_caps;
	u32 cc_caps_ext;
	u32 pmucaps;
	u32 pmurev;
	u32 rambase;
	u32 ramsize;
	u32 srsize;
	अक्षर name[12];
पूर्ण;

/**
 * काष्ठा brcmf_core - core related inक्रमmation.
 *
 * @id: core identअगरier.
 * @rev: core revision.
 * @base: base address of core रेजिस्टर space.
 */
काष्ठा brcmf_core अणु
	u16 id;
	u16 rev;
	u32 base;
पूर्ण;

/**
 * काष्ठा brcmf_buscore_ops - buscore specअगरic callbacks.
 *
 * @पढ़ो32: पढ़ो 32-bit value over bus.
 * @ग_लिखो32: ग_लिखो 32-bit value over bus.
 * @prepare: prepare bus क्रम core configuration.
 * @setup: bus-specअगरic core setup.
 * @active: chip becomes active.
 *	The callback should use the provided @rstvec when non-zero.
 */
काष्ठा brcmf_buscore_ops अणु
	u32 (*पढ़ो32)(व्योम *ctx, u32 addr);
	व्योम (*ग_लिखो32)(व्योम *ctx, u32 addr, u32 value);
	पूर्णांक (*prepare)(व्योम *ctx);
	पूर्णांक (*reset)(व्योम *ctx, काष्ठा brcmf_chip *chip);
	पूर्णांक (*setup)(व्योम *ctx, काष्ठा brcmf_chip *chip);
	व्योम (*activate)(व्योम *ctx, काष्ठा brcmf_chip *chip, u32 rstvec);
पूर्ण;

पूर्णांक brcmf_chip_get_raminfo(काष्ठा brcmf_chip *pub);
काष्ठा brcmf_chip *brcmf_chip_attach(व्योम *ctx,
				     स्थिर काष्ठा brcmf_buscore_ops *ops);
व्योम brcmf_chip_detach(काष्ठा brcmf_chip *chip);
काष्ठा brcmf_core *brcmf_chip_get_core(काष्ठा brcmf_chip *chip, u16 coreid);
काष्ठा brcmf_core *brcmf_chip_get_d11core(काष्ठा brcmf_chip *pub, u8 unit);
काष्ठा brcmf_core *brcmf_chip_get_chipcommon(काष्ठा brcmf_chip *chip);
काष्ठा brcmf_core *brcmf_chip_get_pmu(काष्ठा brcmf_chip *pub);
bool brcmf_chip_iscoreup(काष्ठा brcmf_core *core);
व्योम brcmf_chip_coredisable(काष्ठा brcmf_core *core, u32 prereset, u32 reset);
व्योम brcmf_chip_resetcore(काष्ठा brcmf_core *core, u32 prereset, u32 reset,
			  u32 postreset);
व्योम brcmf_chip_set_passive(काष्ठा brcmf_chip *ci);
bool brcmf_chip_set_active(काष्ठा brcmf_chip *ci, u32 rstvec);
bool brcmf_chip_sr_capable(काष्ठा brcmf_chip *pub);
अक्षर *brcmf_chip_name(u32 chipid, u32 chiprev, अक्षर *buf, uपूर्णांक len);

#पूर्ण_अगर /* BRCMF_AXIDMP_H */
