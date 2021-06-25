<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Private header क्रम the mmc subप्रणाली
 *
 * Copyright (C) 2016 Linaro Ltd
 *
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#अगर_अघोषित _MMC_CORE_CARD_H
#घोषणा _MMC_CORE_CARD_H

#समावेश <linux/mmc/card.h>

#घोषणा mmc_card_name(c)	((c)->cid.prod_name)
#घोषणा mmc_card_id(c)		(dev_name(&(c)->dev))
#घोषणा mmc_dev_to_card(d)	container_of(d, काष्ठा mmc_card, dev)

/* Card states */
#घोषणा MMC_STATE_PRESENT	(1<<0)		/* present in sysfs */
#घोषणा MMC_STATE_READONLY	(1<<1)		/* card is पढ़ो-only */
#घोषणा MMC_STATE_BLOCKADDR	(1<<2)		/* card uses block-addressing */
#घोषणा MMC_CARD_SDXC		(1<<3)		/* card is SDXC */
#घोषणा MMC_CARD_REMOVED	(1<<4)		/* card has been हटाओd */
#घोषणा MMC_STATE_SUSPENDED	(1<<5)		/* card is suspended */

#घोषणा mmc_card_present(c)	((c)->state & MMC_STATE_PRESENT)
#घोषणा mmc_card_पढ़ोonly(c)	((c)->state & MMC_STATE_READONLY)
#घोषणा mmc_card_blockaddr(c)	((c)->state & MMC_STATE_BLOCKADDR)
#घोषणा mmc_card_ext_capacity(c) ((c)->state & MMC_CARD_SDXC)
#घोषणा mmc_card_हटाओd(c)	((c) && ((c)->state & MMC_CARD_REMOVED))
#घोषणा mmc_card_suspended(c)	((c)->state & MMC_STATE_SUSPENDED)

#घोषणा mmc_card_set_present(c)	((c)->state |= MMC_STATE_PRESENT)
#घोषणा mmc_card_set_पढ़ोonly(c) ((c)->state |= MMC_STATE_READONLY)
#घोषणा mmc_card_set_blockaddr(c) ((c)->state |= MMC_STATE_BLOCKADDR)
#घोषणा mmc_card_set_ext_capacity(c) ((c)->state |= MMC_CARD_SDXC)
#घोषणा mmc_card_set_हटाओd(c) ((c)->state |= MMC_CARD_REMOVED)
#घोषणा mmc_card_set_suspended(c) ((c)->state |= MMC_STATE_SUSPENDED)
#घोषणा mmc_card_clr_suspended(c) ((c)->state &= ~MMC_STATE_SUSPENDED)

/*
 * The world is not perfect and supplies us with broken mmc/sdio devices.
 * For at least some of these bugs we need a work-around.
 */
काष्ठा mmc_fixup अणु
	/* CID-specअगरic fields. */
	स्थिर अक्षर *name;

	/* Valid revision range */
	u64 rev_start, rev_end;

	अचिन्हित पूर्णांक manfid;
	अचिन्हित लघु oemid;

	/* SDIO-specअगरic fields. You can use SDIO_ANY_ID here of course */
	u16 cis_venकरोr, cis_device;

	/* क्रम MMC cards */
	अचिन्हित पूर्णांक ext_csd_rev;

	व्योम (*venकरोr_fixup)(काष्ठा mmc_card *card, पूर्णांक data);
	पूर्णांक data;
पूर्ण;

#घोषणा CID_MANFID_ANY (-1u)
#घोषणा CID_OEMID_ANY ((अचिन्हित लघु) -1)
#घोषणा CID_NAME_ANY (शून्य)

#घोषणा EXT_CSD_REV_ANY (-1u)

#घोषणा CID_MANFID_SANDISK      0x2
#घोषणा CID_MANFID_ATP          0x9
#घोषणा CID_MANFID_TOSHIBA      0x11
#घोषणा CID_MANFID_MICRON       0x13
#घोषणा CID_MANFID_SAMSUNG      0x15
#घोषणा CID_MANFID_APACER       0x27
#घोषणा CID_MANFID_KINGSTON     0x70
#घोषणा CID_MANFID_HYNIX	0x90
#घोषणा CID_MANFID_NUMONYX	0xFE

#घोषणा END_FIXUP अणु शून्य पूर्ण

#घोषणा _FIXUP_EXT(_name, _manfid, _oemid, _rev_start, _rev_end,	\
		   _cis_venकरोr, _cis_device,				\
		   _fixup, _data, _ext_csd_rev)				\
	अणु						\
		.name = (_name),			\
		.manfid = (_manfid),			\
		.oemid = (_oemid),			\
		.rev_start = (_rev_start),		\
		.rev_end = (_rev_end),			\
		.cis_venकरोr = (_cis_venकरोr),		\
		.cis_device = (_cis_device),		\
		.venकरोr_fixup = (_fixup),		\
		.data = (_data),			\
		.ext_csd_rev = (_ext_csd_rev),		\
	पूर्ण

#घोषणा MMC_FIXUP_REV(_name, _manfid, _oemid, _rev_start, _rev_end,	\
		      _fixup, _data, _ext_csd_rev)			\
	_FIXUP_EXT(_name, _manfid,					\
		   _oemid, _rev_start, _rev_end,			\
		   SDIO_ANY_ID, SDIO_ANY_ID,				\
		   _fixup, _data, _ext_csd_rev)				\

#घोषणा MMC_FIXUP(_name, _manfid, _oemid, _fixup, _data) \
	MMC_FIXUP_REV(_name, _manfid, _oemid, 0, -1ull, _fixup, _data,	\
		      EXT_CSD_REV_ANY)

#घोषणा MMC_FIXUP_EXT_CSD_REV(_name, _manfid, _oemid, _fixup, _data,	\
			      _ext_csd_rev)				\
	MMC_FIXUP_REV(_name, _manfid, _oemid, 0, -1ull, _fixup, _data,	\
		      _ext_csd_rev)

#घोषणा SDIO_FIXUP(_venकरोr, _device, _fixup, _data)			\
	_FIXUP_EXT(CID_NAME_ANY, CID_MANFID_ANY,			\
		    CID_OEMID_ANY, 0, -1ull,				\
		   _venकरोr, _device,					\
		   _fixup, _data, EXT_CSD_REV_ANY)			\

#घोषणा cid_rev(hwrev, fwrev, year, month)	\
	(((u64) hwrev) << 40 |			\
	 ((u64) fwrev) << 32 |			\
	 ((u64) year) << 16 |			\
	 ((u64) month))

#घोषणा cid_rev_card(card)			\
	cid_rev(card->cid.hwrev,		\
		    card->cid.fwrev,		\
		    card->cid.year,		\
		    card->cid.month)

/*
 * Unconditionally quirk add/हटाओ.
 */
अटल अंतरभूत व्योम __maybe_unused add_quirk(काष्ठा mmc_card *card, पूर्णांक data)
अणु
	card->quirks |= data;
पूर्ण

अटल अंतरभूत व्योम __maybe_unused हटाओ_quirk(काष्ठा mmc_card *card, पूर्णांक data)
अणु
	card->quirks &= ~data;
पूर्ण

अटल अंतरभूत व्योम __maybe_unused add_limit_rate_quirk(काष्ठा mmc_card *card,
						       पूर्णांक data)
अणु
	card->quirk_max_rate = data;
पूर्ण

/*
 * Quirk add/हटाओ क्रम MMC products.
 */
अटल अंतरभूत व्योम __maybe_unused add_quirk_mmc(काष्ठा mmc_card *card, पूर्णांक data)
अणु
	अगर (mmc_card_mmc(card))
		card->quirks |= data;
पूर्ण

अटल अंतरभूत व्योम __maybe_unused हटाओ_quirk_mmc(काष्ठा mmc_card *card,
						   पूर्णांक data)
अणु
	अगर (mmc_card_mmc(card))
		card->quirks &= ~data;
पूर्ण

/*
 * Quirk add/हटाओ क्रम SD products.
 */
अटल अंतरभूत व्योम __maybe_unused add_quirk_sd(काष्ठा mmc_card *card, पूर्णांक data)
अणु
	अगर (mmc_card_sd(card))
		card->quirks |= data;
पूर्ण

अटल अंतरभूत व्योम __maybe_unused हटाओ_quirk_sd(काष्ठा mmc_card *card,
						   पूर्णांक data)
अणु
	अगर (mmc_card_sd(card))
		card->quirks &= ~data;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_lenient_fn0(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_LENIENT_FN0;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_blksz_क्रम_byte_mode(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_BLKSZ_FOR_BYTE_MODE;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_disable_cd(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_DISABLE_CD;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_nonstd_func_पूर्णांकerface(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_NONSTD_FUNC_IF;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_broken_byte_mode_512(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_BROKEN_BYTE_MODE_512;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_दीर्घ_पढ़ो_समय(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_LONG_READ_TIME;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_broken_irq_polling(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_BROKEN_IRQ_POLLING;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_broken_hpi(स्थिर काष्ठा mmc_card *c)
अणु
	वापस c->quirks & MMC_QUIRK_BROKEN_HPI;
पूर्ण

#पूर्ण_अगर
